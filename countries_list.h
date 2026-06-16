#ifndef COUNTRIES_LIST_H
#define COUNTRIES_LIST_H

#include <string>
#include <unordered_set>

/**
 * Class to validate country codes from a predefined set and return associated values
 */
class CCountriesList {
private:
    // Predefined set of countries
    std::unordered_set<std::string> countrySet;

public:
    /**
     * Checks if a country exists in the predefined set
     * @param country The country to check
     * @return true if country exists, false otherwise
     */
    bool isPresent(const std::string& country) const {
        return countrySet.find(country) != countrySet.end();
    }

    /**
     * Adds a country to the set
     * @param country The country to add
     */
    void addCountry(const std::string& country) {
        countrySet.insert(country);
    }

    /**
     * Removes a country from the set
     * @param country The country to remove
     * @return true if country was removed, false otherwise
     */
    bool removeCountry(const std::string& country) {
        return countrySet.erase(country) > 0;
    }

    /**
     * Gets the number of predefined countries
     * @return Size of the predefined country set
     */
    size_t size() const {
        return countrySet.size();
    }

    /**
     * Clears the set of predefined countries
     */
    void clear() {
        countrySet.clear();
    }
};

#endif // COUNTRIES_LIST_H
