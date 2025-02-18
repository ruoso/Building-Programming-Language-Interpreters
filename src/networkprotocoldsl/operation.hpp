#ifndef NETWORKPROTOCOLDSL_OPERATION_HPP
#define NETWORKPROTOCOLDSL_OPERATION_HPP

#include <networkprotocoldsl/operation/add.hpp>
#include <networkprotocoldsl/operation/dictionaryget.hpp>
#include <networkprotocoldsl/operation/dictionaryinitialize.hpp>
#include <networkprotocoldsl/operation/dictionaryset.hpp>
#include <networkprotocoldsl/operation/dynamiclist.hpp>
#include <networkprotocoldsl/operation/eq.hpp>
#include <networkprotocoldsl/operation/functioncall.hpp>
#include <networkprotocoldsl/operation/functioncallforeach.hpp>
#include <networkprotocoldsl/operation/generatelist.hpp>
#include <networkprotocoldsl/operation/if.hpp>
#include <networkprotocoldsl/operation/int32literal.hpp>
#include <networkprotocoldsl/operation/inttoascii.hpp>
#include <networkprotocoldsl/operation/lesserequal.hpp>
#include <networkprotocoldsl/operation/lexicalpadasdict.hpp>
#include <networkprotocoldsl/operation/lexicalpadget.hpp>
#include <networkprotocoldsl/operation/lexicalpadinitialize.hpp>
#include <networkprotocoldsl/operation/lexicalpadinitializeglobal.hpp>
#include <networkprotocoldsl/operation/lexicalpadset.hpp>
#include <networkprotocoldsl/operation/multiply.hpp>
#include <networkprotocoldsl/operation/opsequence.hpp>
#include <networkprotocoldsl/operation/readint32native.hpp>
#include <networkprotocoldsl/operation/readintfromascii.hpp>
#include <networkprotocoldsl/operation/readoctetsuntilterminator.hpp>
#include <networkprotocoldsl/operation/readstaticoctets.hpp>
#include <networkprotocoldsl/operation/statemachineoperation.hpp>
#include <networkprotocoldsl/operation/staticcallable.hpp>
#include <networkprotocoldsl/operation/subtract.hpp>
#include <networkprotocoldsl/operation/terminatelistifreadahead.hpp>
#include <networkprotocoldsl/operation/transitionlookahead.hpp>
#include <networkprotocoldsl/operation/unarycallback.hpp>
#include <networkprotocoldsl/operation/writeint32native.hpp>
#include <networkprotocoldsl/operation/writeoctets.hpp>
#include <networkprotocoldsl/operation/writestaticoctets.hpp>

#include <variant>

namespace networkprotocoldsl {

/**
 * Operation is a variant of all known operation types.
 *
 * This allows us to implement a type-safe dispatch on all the
 * operations that may happen in the execution of the interpreted
 * code.
 */
using Operation = std::variant<
    operation::Add, operation::DynamicList, operation::Eq,
    operation::FunctionCall, operation::FunctionCallForEach,
    operation::GenerateList, operation::If, operation::Int32Literal,
    operation::IntToAscii, operation::LesserEqual, operation::LexicalPadGet,
    operation::LexicalPadInitialize, operation::LexicalPadInitializeGlobal,
    operation::LexicalPadSet, operation::Multiply, operation::OpSequence,
    operation::ReadInt32Native, operation::ReadIntFromAscii,
    operation::ReadOctetsUntilTerminator, operation::ReadStaticOctets,
    operation::StaticCallable, operation::Subtract,
    operation::TerminateListIfReadAhead, operation::UnaryCallback,
    operation::WriteInt32Native, operation::WriteOctets,
    operation::WriteStaticOctets, operation::DictionaryInitialize,
    operation::DictionarySet, operation::DictionaryGet,
    operation::LexicalPadAsDict, operation::TransitionLookahead,
    operation::StateMachineOperation>;

} // namespace networkprotocoldsl

#endif // NETWORKPROTOCOLDSL_OPERATION_HPP
