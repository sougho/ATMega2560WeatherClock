#include <BMP180I2C.h>
#define I2C_ADDRESS 0x77

struct BMPData {
  float temp;
  float pressure;
  char* msg;

  public: 
    BMPData(float _t, float _p, char* _m = NULL) {
      temp = _t;
      pressure = _p;
      msg = _m;
    }
};

class BMPUtils {
  private :
    BMP180I2C  *_m_bmpSensor = new BMP180I2C(I2C_ADDRESS);
  public:
    BMPData initBMP();
    BMPData getPressureTempData();
};
