// Copyright 2024, Andrew Drogalis
// GNU License

#include "gain_capital_api.h"

#include <string>

#include "json.hpp"
#include "gtest/gtest.h"
#include "httpmockserver/mock_server.h"
#include "httpmockserver/test_environment.h"


class HTTPMock: public httpmock::MockServer {
  public:
    /// Create HTTP server on port 9200
    explicit HTTPMock(int port = 9200): MockServer(port) {}
  private:

    /// Handler called by MockServer on HTTP request.
    Response responseHandler(
            const std::string &url,
            const std::string &method,
            const std::string &data,
            const std::vector<UrlArg> &urlArguments,
            const std::vector<Header> &headers)
    {
        // Authenticate Session
        if (method == "POST" && matchesPrefix(url, "/Session")) {
            
            return Response(500, "Fake HTTP response");
        }
        // Validate Session
        else if (method == "POST" && matchesPrefix(url, "/Session/validate")) {
            
            return Response(500, "Fake HTTP response");
        }
        // Account Info
        else if (method == "GET" && matchesPrefix(url, "/userAccount/ClientAndTradingAccount")) {
            
            return Response(500, "Fake HTTP response");
        }
        // Margin Info
        else if (method == "GET" && matchesPrefix(url, "/margin/clientAccountMargin?clientAccountId=TEST")) {
            
            return Response(500, "Fake HTTP response");
        }
        // Market IDs & Market Info
        else if (method == "GET" && matchesPrefix(url, "/cfd/markets?MarketName=TEST_MARKET")) {
            
            return Response(500, "Fake HTTP response");
        }
        // Prices
        else if (method == "GET" && matchesPrefix(url, "/market/TEST_MARKET/tickhistory")) {
            
            return Response(500, "Fake HTTP response");
        }
        // OHLC
        else if (method == "GET" && matchesPrefix(url, "/market/TEST_MARKET/barhistory")) {
        
            return Response(500, "Fake HTTP response");
        }
        // Trade Market Order
        else if (method == "POST" && matchesPrefix(url, "/order/newtradeorder")) {
            
            return Response(500, "Fake HTTP response");
        }
        // Trade Limit Order
        else if (method == "POST" && matchesPrefix(url, "/order/newstoplimitorder")) {
            
            return Response(500, "Fake HTTP response");
        }
        // List Open Positons
        else if (method == "GET" && matchesPrefix(url, "/order/openpositions?TradingAccountId=TEST")) {
            
            return Response(500, "Fake HTTP response");
        }
        // List Active Orders
        else if (method == "POST" && matchesPrefix(url, "/order/activeorders")) {
            
            return Response(500, "Fake HTTP response");
        }
        // Cancel Order
        else if (method == "POST" && matchesPrefix(url, "/order/cancel")) {
            
            return Response(500, "Fake HTTP response");
        }
        // Return "URI not found" for the undefined methods
        return Response(404, "Not Found");
    }

    /// Return true if \p url starts with \p str.
    bool matchesPrefix(const std::string &url, const std::string &str) const {
        return url.substr(0, str.size()) == str;
    }
};


TEST(GainCapitalFunctional, Check_All_APIs_Base_Case) {
    // Here should be implementation of test case using HTTP server.
    // HTTP requests are processed by HTTPMock::responseHandler(...)
    // I. e.: when HTTP POST request is sent on localhost:9200/example, then
    // response with status code 500 and body "Fake HTTP response" is returned.
    const gaincapital::GCapiClient g{"TEST_USER", "TEST_PASSWORD", "TEST_APIKEY"};
    g.set_testing_rest_urls("http://localhost:9200");
    g.authenticate_session();
    g.validate_session();

}


int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new httpmock::TestEnvironment<HTTPMock>());
    return RUN_ALL_TESTS();
}
