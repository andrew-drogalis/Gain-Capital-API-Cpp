
# Gain Capital API C++

## Table of Contents

* [Instructions](#Instructions)
    - [Downloading Dependencies](#Downloading-Dependencies)
    - [Initializing API](#Initializing-API)
    - [Authenticating Session](#Authenticating-Session)
    - [Account & Margin Information](#Account-&-Margin-Information)
    - [Market IDs & Information](#Market-IDs-&-Information)
    - [Fetching OHLC Data](#Fetching-OHLC-Data)
    - [Placing Trades](#Placing-Trades)
    - [Monitoring Trades](#Monitoring-Trades)
    - [Canceling Active Orders](#Canceling-Active-Orders)
* [Installing](#Installing)
* [Dependencies](#Dependencies)
* [Lightstreamer](#Lightstreamer)
* [License](#License)
* [Contributing](#Contribution)

## Instructions

This library is dependent upon the API from Gain Capital's Forex.com. To make an account visit their website [Forex.com](https://www.forex.com). Once an account is made you will need to send them an email and request an API key.

### Downloading Dependencies

Please see a link to required dependencies [below](#Dependencies). If you are using Linux, Boost can be installed with the following commands below.

```
    Fedora:
        dnf install boost-devel libmicrohttpd-devel
    Debian:
        apt-get install libboost-all-dev libmicrohttpd-devel
    Arch: 
        pacman -Ss boost libmicrohttpd
```

### Initializing API

```c
    #include <gain_capital_api.h>

    string username = "Username", password = "Password", apikey = "ApiKey";

    // List of Currencies to Trade
    vector<string> currency_pairs = {"USD/CHF", "EUR/USD", "GBP/USD"};

    // Initalize GCapiClient
    gaincapital::GCapiClient gc_api = gaincapital::GCapiClient(username, password, apikey);
```

### Authenticating Session

```c
    // Required for First Authentication
    bool success = gc_api.authenticate_session();

    // Authenticates Session Token if Expired
    bool success = gc_api.validate_session();
```


### Account & Margin Information

```c
    // Get Account Information
    nlohmann::json account_response = gc_api.get_account_info();

    // Get Margin Information
    nlohmann::json margin_response = gc_api.get_margin_info();

```

### Market IDs & Information

```c
    // Get Market IDs
    // Sets Class Map with Market IDs
    std::map<std::string, int> market_ids_response = gc_api.get_market_ids(currency_pairs);
```

### Fetching OHLC Data

```c
    // Get OHLC Bars
    string interval = "MINUTE";
    int num_ticks = 10;
    std::map<std::string, nlohmann::json> ohlc_response = gc_api.get_ohlc(currency_pairs, interval, num_ticks);
```

### Placing Trades

```c
    // Place Market Order
    nlohmann::json trades_map_market = {};
    for (string const &symbol : currency_pairs) {
        trades_map_market[symbol] = {{"Direction", "sell"}, {"Quantity", 1000}};
    }
    
    std::vector<std::string> market_order_response = gc_api.trade_order(trades_map_market, "MARKET");

    // Place Limit Order
    nlohmann::json trades_map_limit = {};
    for (string const &symbol : currency_pairs) {
        float mid_price = price_response[symbol][0]["Price"];
        float trigger_price = mid_price * 1.1;
        float stop_price = mid_price * 0.9;

        trades_map_limit[symbol] = {{"Direction", "buy"}, {"Quantity", 1000}, {"TriggerPrice", trigger_price}, {"StopPrice", stop_price}};
    }

    std::vector<std::string> limit_order_response = gc_api.trade_order(trades_map_limit, "LIMIT");
```

### Monitoring Trades

```c
    // Order Management
    nlohmann::json active_order_response = gc_api.list_active_orders();

    nlohmann::json open_position_response = gc_api.list_open_positions();
```

### Canceling Active Orders

```c
    // Cancel Active Orders
    for (nlohmann::json active_order : active_order_response)  {
        
        // Cancel Market Orders
        if (active_order.contains("TradeOrder")) {
            string order_id = active_order['TradeOrder']['OrderId'];
            gc_api.cancel_order(order_id);
        }

        // Cancel Limit Orders
        if (active_order.contains("StopLimitOrder")) {
            string order_id = active_order['StopLimitOrder']['OrderId'];
            gc_api.cancel_order(order_id);
        }
    }
```

## Installing

To build the shared library and header files, run the commands below.

```
    $ mkdir gcapi_library
    $ cmake -S . -B gcapi_library
    $ cmake --build gcapi_library --target gain_capital_api
    $ cmake install gcapi_library
```

## Dependencies

- [Boost](https://www.boost.org/) - *Must be installed by user*
- [libmicrohttpd](https://www.gnu.org/software/libmicrohttpd/) - Required for Tests Only - *Must be installed by user*
- [CPR](https://github.com/libcpr/cpr) - Included in CMake Fetch Content
- [JSON](https://github.com/nlohmann/json) - .hpp file included in repository

## Lightstreamer

Live data streaming is provided by the Lightstreamer client, currently this feature is not integrated into this repository. In the future, I hope to incorporate this feature, but please see the C++ Lightstreamer repository provided below. This will be the jumping off point for future integration into this repository.

- [Lightstreamer for C++](https://github.com/AndrewCarterUK/LightstreamerCpp)

## License

This software is distributed under the GNU license. Please read [LICENSE](https://github.com/andrew-drogalis/Gain-Capital-API-Cpp/blob/main/LICENSE) for information on the software availability and distribution.


## Contribution

Please open an issue of if you have any questions, suggestions, or feedback.

Please submit bug reports, suggestions, and pull requests to the [GitHub issue tracker](https://github.com/andrew-drogalis/Gain-Capital-API-Cpp/issues).
