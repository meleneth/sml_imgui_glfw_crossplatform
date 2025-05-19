#pragma once

#include "quadrant_fsm_definition.hpp"
#include <boost/sml.hpp>
#include <string>

class QuadrantFsm {
public:
  QuadrantFsm();

  void tick();
  void toggle();

  std::string label_name() const;
  int counter() const;

private:
  FsmContext context;
  boost::sml::sm<QuadrantFsmDefinition> sm;
};
