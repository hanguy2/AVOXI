# IP Country Validation Service

## Overview

This service validates whether a client IP address belongs to a customer-defined list of allowed countries. The service is designed as a simple HTTP API that receives an IP address and a list of whitelisted countries, performs a GeoIP lookup, and returns an allow/deny decision.

---

## Request / Response Flow

### Request Flow

1. The API Gateway receives a user request and extracts the client IP address.
2. The API Gateway retrieves the customer's configured list of allowed countries.
3. The API Gateway sends an HTTP POST request to the IP Validation Service host:port/validateip with a JSON payload containing:

   * Client IP address
   * List of allowed countries

Example request:

```json
{
    "ip": "8.8.8.8",
    "allowedCountries": ["United States", "Canada"]
}
```

### Processing Flow

1. Validate the request payload.
2. Validate the supplied IP address (IPv4 or IPv6).
3. Perform a GeoIP lookup to determine the country associated with the IP address.
4. Check whether the country exists in the configured whitelist.
5. Generate the response.

### Response

If the IP belongs to one of the allowed countries:

```json
{
    "Access": "Allowed"
}
```

Otherwise:

```json
{
    "Access": "Denied"
}
```

---

## Code Implementation

### Logger

A lightweight logging component is provided for debugging and operational visibility.

Features:

* Multiple log levels (DEBUG, INFO, WARN, ERROR, CRITICAL)
* Timestamped log messages
* Output directed to stdout
* Simple interface suitable for command-line execution and containerized deployment

---

### IP Validator

Responsible for validating incoming IP addresses before processing.

Features:

* IPv4 validation
* IPv6 validation
* Detection of malformed or unsupported addresses
* Prevents unnecessary GeoIP lookups for invalid requests

---

### Countries List

The list of allowed countries is internally stored using a hash set (`std::unordered_set`).

Benefits:

* O(1) average lookup time
* Efficient membership testing
* Suitable for large country lists

---

### GeoIP Database Wrapper

A dedicated GeoIP component encapsulates all interactions with the GeoLite2 database.

Responsibilities:

* Database initialization
* Country lookup by IP address
* Error handling
* Isolation of third-party API details from business logic

This abstraction allows the GeoIP implementation to be replaced in the future without affecting the service interface.

---

### HTTP Server

A lightweight HTTP server implementation (`httpsrv`) is used to simulate the complete service.

Responsibilities:

* Receive HTTP POST requests
* Parse JSON payloads
* Invoke validation logic
* Return JSON responses

---

## External Libraries

### cpp-httplib

Used as the HTTP 1.1 server framework.

Benefits:

* Header-only library
* Easy integration
* Minimal dependencies
* Suitable for lightweight REST APIs

### nlohmann/json

Used for JSON serialization and parsing.

Benefits:

* Simple API
* Header-only implementation
* Strong C++ STL integration

---

## Unit Testing

Unit tests are included as a single test source file.

Covered scenarios include:

* Valid IPv4 addresses
* Valid IPv6 addresses
* Invalid IP addresses
* Allowed country validation
* Denied country validation
* GeoIP lookup handling
* HTTP request/response validation

---

## How to Build and Test

### Build

Compile the project using:

```bash
make
```

### Run the Service

Start the HTTP server:

```bash
./httpsrv
```

The service listens on port `8080`.

### Test Using curl

Open another terminal and execute:

```bash
curl --json '{"ip": "8.8.8.8", "allowedCountries": ["United States", "Canada"]}' http://localhost:8080/validateip -vvv
```

Expected response:

```json
{
    "Access": "Allowed"
}
```

You can also test with IP addresses from countries outside the allowed list and verify that the service returns:

```json
{
    "Access": "Denied"
}
```

---

## Future Enhancements

### Country List Management

The current implementation supports a whitelist model and creates a country hash set from the request payload for each validation request.

Possible improvements include:

* Support both **Whitelist** and **Blacklist** modes.
* Support **IP exception lists** to explicitly allow or deny specific IP addresses regardless of country policy.
* Store country policies per customer and maintain a hash-based lookup indexed by Customer ID.
* Cache customer country policies in memory to avoid rebuilding country sets on every request.
* Add support for dynamic policy updates without restarting the service.

---

### GeoIP Database Management

The GeoLite2 database must be kept up to date to ensure accurate country lookups.

A possible solution is:

1. Use a scheduled shell script (cron job) to periodically check for GeoLite2 database updates.
2. Download the latest database when a new version becomes available.
3. Replace the existing database file atomically.
4. The service monitors the database file for modification events and automatically reloads the database when changes are detected.

This functionality can be implemented relatively easily in Go using the `fsnotify` library.

For C++, there is no standard file-watching library available. A production implementation would likely require:

* Platform-specific file notification APIs (e.g., `inotify` on Linux, `ReadDirectoryChangesW` on Windows, or `kqueue` on BSD/macOS), or
* Evaluation of third-party file monitoring libraries.

---

### gRPC Support

The current implementation uses a lightweight HTTP 1.1 REST API.

Future versions could provide a gRPC interface for improved performance and stronger API contracts.

gRPC support was not implemented in this project because it requires:

* HTTP/2 support
* Protocol Buffers (protobuf) schema definitions
* Additional build and runtime dependencies
* Generation of client/server stubs

The current HTTP/JSON implementation was selected to keep the solution lightweight and focused on the core country validation functionality.

---

### Additional Enhancements

* VPN and proxy detection
* GeoIP lookup result caching
* Metrics and monitoring integration
* Rate limiting
* Configuration management
* High-availability deployment
* Country lookup performance benchmarking
* Audit logging and reporting
* Distributed cache support for multi-instance deployments

---

## Project Structure Note

Normally, I organize source code and third-party libraries using the following structure:

```text
src/        - Application source files
library/    - Third-party libraries and dependencies
test/       - Unit tests
```

However, during development I mistakenly pushed the current directory layout to GitHub. To avoid unnecessary repository restructuring and preserve commit history, I kept the existing organization unchanged for this submission.

In a production codebase, I would typically separate application code, external dependencies, and test code into dedicated directories to improve maintainability and scalability.
