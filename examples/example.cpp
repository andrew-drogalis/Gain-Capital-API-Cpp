
#include <gain_capital_api.h>
#include <json.hpp>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main () {
    // Forex.com Account Info
    string username = "BLANK";
    string password = "BLANK";
    string apikey = "BLANK";

    // List of Currencies to Trade
    vector<string> currency_pairs = {"USD/CHF", "EUR/USD", "GBP/USD"};

    // Initalize GCapiClient
    GCapiClient gc_api = GCapiClient(username, password, apikey);

    // Get Account Information
    // Sets Class Variable with Trading Account ID
    nlohmann::json account_response = gc_api.get_account_info();

    // Get Margin Information
    nlohmann::json margin_response = gc_api.get_margin_info();

    // Get Market IDs
    // Sets Class Map with Market IDs
    std::map<std::string, int> market_ids_response = gc_api.get_market_ids(currency_pairs);

    // Get Currency Prices
    std::map<std::string, nlohmann::json> price_response = gc_api.get_prices(currency_pairs);

    // Get OHLC Bars
    string interval = "MINUTE";
    int num_ticks = 10;
    std::map<std::string, nlohmann::json> ohlc_response = gc_api.get_ohlc(currency_pairs, interval, num_ticks);

    // Place Market Order
    nlohmann::json trades_map_market = {};
    for (string symbol : currency_pairs) {
        trades_map_market[symbol] = {{"Direction", "sell"}, {"Quantity", 1000}};
    }
    // std::vector<std::string> market_order_response = gc_api.trade_market_order(trades_map_market, currency_pairs);

    // Place Limit Order
    nlohmann::json trades_map_limit = {};
    for (string symbol : currency_pairs) {
        float mid_price = price_response[symbol][0]["Price"];
        float trigger_price = mid_price * 1.1;
        float stop_price = mid_price * 0.9;

        trades_map_limit[symbol] = {{"Direction", "buy"}, {"Quantity", 1000}, {"TriggerPrice", trigger_price}, {"StopPrice", stop_price}};
    }

    // std::vector<std::string> limit_order_response = gc_api.trade_limit_order(trades_map_limit, currency_pairs);

    // Order Management
    nlohmann::json active_order_response = gc_api.list_active_orders();

    nlohmann::json open_position_response = gc_api.list_open_positions();

}