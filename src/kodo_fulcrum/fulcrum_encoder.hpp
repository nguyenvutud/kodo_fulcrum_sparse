// Copyright Steinwurf ApS 2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <kodo_core/common_encoder_layers.hpp>
#include <kodo_core/nested_payload_size.hpp>
#include <kodo_core/nested_systematic.hpp>
#include <kodo_core/nested_write_payload.hpp>
#include <kodo_core/payload_precoder.hpp>
#include <kodo_core/select_storage_layers.hpp>
#include <kodo_core/systematic_precoder.hpp>
#include <kodo_core/trace_layer.hpp>
#include <kodo_core/trace_nested_stack.hpp>
#include <kodo_core/uniform_generator_layers.hpp>

#include <kodo_rlnc/shallow_full_vector_encoder.hpp>

#include "trace_systematic_coefficient_mapper.hpp"
#include "systematic_coefficient_mapper.hpp"
#include "fulcrum_info.hpp"
#include "fulcrum_nested_stack.hpp"

namespace kodo_fulcrum
{
/// @ingroup fec_stacks
///
/// @brief The fulcrum encoder supports the concatenated code
///        structure with an "outer" and "inner" code.
///
/// For a detailed description of the fulcrum codec see the
/// following paper on arxiv: http://arxiv.org/abs/1404.6620 by
/// Lucani et. al.
///
template
<
    class Field,
    class Features = meta::typelist<>
>
class fulcrum_encoder : public
    // Payload Codec API
    kodo_core::nested_systematic<
    kodo_core::payload_precoder<
    kodo_core::systematic_precoder<
    trace_systematic_coefficient_mapper<
    kodo_core::find_enable_trace<Features>,
    systematic_coefficient_mapper<
    kodo_core::nested_write_payload<
    kodo_core::nested_payload_size<
    kodo_core::trace_nested_stack<kodo_core::find_enable_trace<Features>,
    fulcrum_nested_stack<
    kodo_rlnc::shallow_full_vector_encoder<fifi::binary, Features>,
    // Coefficient Generator API
    kodo_core::uniform_generator_layers::type<Features,
    // Codec API
    kodo_core::common_encoder_layers<Features,
    // Coefficient Storage API
    kodo_core::coefficient_value_access<
    kodo_core::coefficient_info<
    // Symbol Storage API
    kodo_core::select_storage_layers<
    kodo_core::deep_storage_layers, Features,
    // Finite Field API
    kodo_core::finite_field_layers<Field,
    // Fulcrum API
    fulcrum_info<
    std::integral_constant<uint32_t,10>, // MaxExpansion
    std::integral_constant<uint32_t,4>,  // DefaultExpansion
    // Trace Layer
    kodo_core::trace_layer<kodo_core::find_enable_trace<Features>,
    // Final Layer
    kodo_core::final_layer
    >>>>>>>>>>>>>>>>>
{
public:
    using factory = kodo_core::pool_factory<fulcrum_encoder>;
};
}
