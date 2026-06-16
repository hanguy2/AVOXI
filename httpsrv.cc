#include "httplib/httplib.h"
#include "validate_country_ip.h"
#include <iostream>

int main() {
    // Create the server instance
    httplib::Server svr;
    CValidateCountryIP validator ("./geodata/GeoLite2-Country.mmdb");

    // Define a route for the GET method at the root path
    svr.Post("/validateip", [&validator](const httplib::Request& req, httplib::Response& res) {
        std::cout << "Received POST request to /validateip" << " " << req.body << std::endl;
        json response = validator.validateAccess(req.body);
        res.set_content(response.dump(), "application/json");
    });

    std::cout << "Server starting on http://localhost:8080\n";
    
    // Bind to local port and listen
    svr.listen("0.0.0.0", 8080);
    return 0;
}