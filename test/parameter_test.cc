#include <dmlc/parameter.h>

// this is actual pice of code
struct Param : public dmlc::Parameter<Param> {
  float learning_rate;
  int num_hidden;
  int act;
  std::string name;
  // declare parameters in header file
  DMLC_DECLARE_PARAMETER(Param) {
    DMLC_DECLARE_FIELD(num_hidden).set_range(0, 1000)
        .describe("Number of hidden unit in the fully connected layer.");
    DMLC_DECLARE_FIELD(learning_rate).set_default(0.01f)
        .describe("Learning rate of SGD optimization.");
    DMLC_DECLARE_FIELD(act).add_enum("relu", 1).add_enum("sigmoid", 2)
        .describe("Activation function type.");
    DMLC_DECLARE_FIELD(name).set_default("A")
        .describe("Name of the net.");
  }
};
// register it in cc file
DMLC_REGISTER_PARAMETER(Param);

int main(int argc, char *argv[]) {
  Param param;
  std::map<std::string, std::string> kwargs;
  for (int i = 0; i < argc; ++i) {
    char name[256], val[256];
    if (sscanf(argv[i], "%[^=]=%[^\n]", name, val) == 2) {
      printf("call set %s=%s\n", name, val);
      kwargs[name] = val;
    }
  }
  printf("Parameters\n-----------\n%s", Param::__DOC__().c_str());
  param.Init(kwargs);
  printf("-----\n");
  printf("param.num_hidden=%d\n", param.num_hidden);
  printf("param.learning_rate=%f\n", param.learning_rate);
  printf("param.name=%s\n", param.name.c_str());
  printf("param.act=%d\n", param.act);
  printf("param.size=%lu\n", sizeof(param));
  return 0;
}
