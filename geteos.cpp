#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>

using namespace eosio;

CONTRACT geteos: public contract {
    public:
      using contract::contract;

      ACTION getbalance(name user, asset token) {//사용자의 잔액을 확인
         accounts mytoken("eosio.token"_n, user.value);
         symbol sym = token.symbol;
         auto itr = mytoken.require_find(sym.code().raw(), "no balance");

         print(itr->balance);
      }
      //소수점 몇자린지 출력하는 action
      ACTION gettokeninfo(asset token){
          //print token symbol
          //print token precision
          print(token.symbol.code().to_string());
          print(token.symbol.precision());
      }
    private://eosio token 테이블에 조율
      struct [[eosio::table]] account {
            asset    balance; //asset: Token타입

            uint64_t primary_key()const { return balance.symbol.code().raw(); }
         };

         struct [[eosio::table]] currency_stats {
            asset    supply;
            asset    max_supply;
            name     issuer;

            uint64_t primary_key()const { return supply.symbol.code().raw(); }
         };

         typedef eosio::multi_index< "accounts"_n, account > accounts;
         typedef eosio::multi_index< "stat"_n, currency_stats > stats;
};