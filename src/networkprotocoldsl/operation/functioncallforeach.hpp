#ifndef INCLUDED_NETWORKPROTOCOLDSL_OPERATION_FUNCTIONCALLFOREACH_HPP
#define INCLUDED_NETWORKPROTOCOLDSL_OPERATION_FUNCTIONCALLFOREACH_HPP

#include <networkprotocoldsl/operationconcepts.hpp>

namespace networkprotocoldsl::operation {

class FunctionCallForEach {
public:
  using Arguments = std::tuple<Value, Value>;
  OperationResult operator()(ControlFlowOperationContext &ctx,
                             Arguments a) const;
  Value get_callable(ControlFlowOperationContext &ctx) const;
  std::shared_ptr<const std::vector<Value>>
  get_argument_list(ControlFlowOperationContext &ctx) const;
  void set_callable_invoked(ControlFlowOperationContext &ctx) const;
  void set_callable_return(ControlFlowOperationContext &ctx, Value v) const;
};
static_assert(ControlFlowOperationConcept<FunctionCallForEach>);

} // namespace networkprotocoldsl::operation

#endif