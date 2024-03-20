// Copyright 2024, Andrew Drogalis
// GNU License

#ifndef GAIN_CAPITAL_API_H
#define GAIN_CAPITAL_API_H

#include <string>
#include <vector>
#include <map>

#include "json.hpp"
#include "cpr/cpr.h"

namespace gaincapital {

class GCapiClient {

    public:
        // User may want to access these elements
        std::string trading_account_id = "";
        std::string client_account_id = "";
        std::map<std::string, int> market_id_map;

        GCapiClient();

        ~GCapiClient();

        GCapiClient(std::string username, std::string password, std::string appkey);

        void authenticate_session();

        void validate_session();

        void validate_session_header();

        void validate_auth_payload();

        void validate_account_ids();

        void set_testing_rest_urls(std::string url);

        nlohmann::json get_account_info(std::string param = "");

        nlohmann::json get_margin_info(std::string param = "");

        std::map<std::string, int> get_market_ids(std::vector<std::string> positions);

        std::map<std::string, std::string> get_market_info(std::vector<std::string> market_name_list, std::string param = "");

        std::map<std::string, nlohmann::json> get_prices(std::vector<std::string> market_name_list, int num_ticks = 1, long unsigned int from_ts = 0, long unsigned int to_ts = 0, std::string price_type = "MID");

        std::map<std::string, nlohmann::json> get_ohlc(std::vector<std::string> market_name_list, std::string interval, int num_ticks = 1, int span = 1, long unsigned int from_ts = 0, long unsigned int to_ts = 0);

        std::vector<std::string> trade_market_order(nlohmann::json trade_map, std::string tr_account_id = "");

        std::vector<std::string> trade_limit_order(nlohmann::json trade_map, std::string tr_account_id = "");

        nlohmann::json list_open_positions(std::string tr_account_id = "");
        
        nlohmann::json list_active_orders(std::string tr_account_id = "");

        nlohmann::json cancel_order(std::string order_id, std::string tr_account_id = "");

    private:
        std::string rest_url_v2 = "https://ciapi.cityindex.com/v2";
        std::string rest_url = "https://ciapi.cityindex.com/TradingAPI";
        cpr::Header session_header;
        std::string session_username = "";
        nlohmann::json auth_payload;
        nlohmann::json session_payload;
};

} // namespace gaincapital

#endif