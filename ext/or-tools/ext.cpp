#include <ortools/base/version.h>

#include <rice/Module.hpp>

void init_assignment(Rice::Module& m);
void init_bin_packing(Rice::Module& m);
void init_constraint(Rice::Module& m);
void init_network_flows(Rice::Module& m);
void init_routing(Rice::Module& m);

extern "C"
void Init_ext()
{
  Rice::Module m = Rice::define_module("ORTools");

  m.define_singleton_method(
    "lib_version",
    *[]() {
      return std::to_string(operations_research::OrToolsMajorVersion()) + "."
        + std::to_string(operations_research::OrToolsMinorVersion());
    });

  init_assignment(m);
  init_bin_packing(m);
  init_constraint(m);
  init_network_flows(m);
  init_routing(m);
}
