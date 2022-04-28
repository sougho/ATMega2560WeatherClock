#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 14
#define DHTTYPE DHT22

struct DHT22Data {
  
  float temp;
  float rh;
  char* msg;

  public: 
    DHT22Data(float _t, float _r, char* _m = NULL) {
      temp = _t;
      rh = _r;
      msg = _m;
    }
};

class DHT22Utils {

  private:
    DHT * _m_dht = new DHT(DHTPIN, DHTTYPE);
  public:
    void init();
    DHT22Data readRHValue();
};
