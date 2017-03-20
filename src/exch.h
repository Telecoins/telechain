//#include <string>
//#include <vector>

#include "rpcprotocol.h"

using namespace std;

//-----------------------------------------------------
class Exch {
  public:
  Exch(const string &retAddr); 
  virtual ~Exch() {};

  virtual const string& Name() const = 0;
  virtual const string& Host() const = 0;
  
  // Get currency for exchnagge to, like btc, ltc, etc
  // Fill MarketInfo from exchange.
  // Returns the empty string if OK, or error message, if error
  virtual string MarketInfo(const string &currency) = 0;

  // Create SEND exchange channel for 
  // Send "amount" in external currecny "to" address
  // Fills m_depAddr..m_txKey, and updates m_rate
  // Returns error text, or an empty string, if OK
  virtual string Send(const string &to, double amount) = 0;

  // Check status of existing transaction.
  // If key is empty, used the last key
  // Returns status (including err), or minus "-", if "not my" key
  virtual string TxStat(const string &txkey, UniValue &details) = 0;

  string m_retAddr; // Return EMC Addr

  // MarketInfo fills these params
  string m_pair;
  double m_rate;
  double m_limit;
  double m_min;
  double m_minerFee;

  // Send fills these params + m_rate above
  string m_depAddr;	// Address to pay EMC
  string m_outAddr;	// Address to pay from exchange
  double m_depAmo;	// amount in EMC
  double m_outAmo;	// Amount transferred to BTC
  string m_txKey;	// TX reference key

  protected:
  // Connect to the server by https, fetch JSON and parse to UniValue
  // Throws exception if error
  UniValue httpsFetch(const char *get, const UniValue *post);

  // Get input path within server, like: /api/marketinfo/emc_btc.json
  // Called from exchange-specific MarketInfo()
  // Fill MarketInfo from exchange.
  // Throws exception if error
  const UniValue RawMarketInfo(const string &path);

  // Check JSON-answer for "error" key, and throw error
  // message, if exists
  virtual void CheckERR(const UniValue &reply) const;


}; // class Exch

//-----------------------------------------------------
class ExchCoinReform : public Exch {
  public:
  ExchCoinReform(const string &retAddr);

  virtual ~ExchCoinReform();

  virtual const string& Name() const;
  virtual const string& Host() const;

  // Get currency for exchnagge to, like btc, ltc, etc
  // Fill MarketInfo from exchange.
  // Returns the empty string if OK, or error message, if error
  virtual string MarketInfo(const string &currency);

  // Creatse SEND exchange channel for 
  // Send "amount" in external currecny "to" address
  // Fills m_depAddr..m_txKey, and updates m_rate
  virtual string Send(const string &to, double amount);

  // Check status of existing transaction.
  // If key is empty, used the last key
  // Returns status (including err), or minus "-", if "not my" key
  virtual string TxStat(const string &txkey, UniValue &details);
 
}; // class ExchCoinReform

//-----------------------------------------------------
class ExchBox {
  public:
  ExchBox(const string &retAddr);
  ~ExchBox();

  vector<Exch*> m_v_exch;
}; // class exchbox

//-----------------------------------------------------