// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <cstdint>

#include <fifi/binary.hpp>

#include <kodo_core/basic_symbol_decoder.hpp>
#include <kodo_core/coefficient_storage_layers.hpp>
#include <kodo_core/common_decoder_layers.hpp>
#include <kodo_core/elimination_decoder.hpp>
#include <kodo_core/final_layer.hpp>
#include <kodo_core/finite_field_layers.hpp>
#include <kodo_core/nested_payload_size.hpp>
#include <kodo_core/nested_read_payload.hpp>
#include <kodo_core/pool_factory.hpp>
#include <kodo_core/proxy_args.hpp>
#include <kodo_core/select_storage_layers.hpp>
#include <kodo_core/is_storage_layers.hpp>
#include <kodo_core/trace_layer.hpp>
#include <kodo_core/uniform_generator.hpp>

#include "trace_systematic_coefficient_mapper.hpp"
#include "systematic_coefficient_mapper.hpp"
#include "fulcrum_info.hpp"
#include "fulcrum_payload_decoder.hpp"
#include "fulcrum_proxy_stack.hpp"
#include "fulcrum_two_stage_decoder.hpp"
#include "trace_fulcrum_two_stage_decoder.hpp"

namespace kodo_fulcrum
{
/// @ingroup fec_stacks
///
/// @brief The fulcrum combined decoder tries to decode as much as
///        possible in the inner code before passing symbols to
///        the outer code.
///
/// The main component of the combined decoder is implemented in
/// the fulcrum_two_stage_decoder layer. Which implements decoding
/// in the inner code, as soon as a full decoding is deemed
/// possible symbols are taken from the fulcrum_two_stage_decoder
/// and pass to the main decoder (which decodes in the outer
/// code).
///
/// For a detailed description of the fulcrum codec see the
/// following paper on arxiv: http://arxiv.org/abs/1404.6620 by
/// Lucani et. al.
///
/// @tparam Field @copydoc layer_types::Field
///
template
<
    class Field,
    class Features = meta::typelist<>
>
class fulcrum_combined_decoder : public
    // Payload API
    kodo_core::nested_read_payload<
    kodo_core::nested_payload_size<
    fulcrum_proxy_stack<kodo_core::proxy_args<>, fulcrum_payload_decoder,
    // Codec Header API
    //  - implemented in outer decoder
    // Symbol ID API
    //  - implemented in outer decoder
    // Coefficient Generator API
    trace_fulcrum_two_stage_decoder<kodo_core::find_enable_trace<Features>,
    fulcrum_two_stage_decoder<
    kodo_core::elimination_decoder<fifi::binary,
    typename Features::template remove<kodo_core::is_storage_layers>>,
    kodo_core::basic_symbol_decoder<fifi::binary,
    typename Features::template remove<kodo_core::is_storage_layers>>,
    trace_systematic_coefficient_mapper<
    kodo_core::find_enable_trace<Features>,
    systematic_coefficient_mapper<
    kodo_core::uniform_generator<
    // Decoder API
    kodo_core::common_decoder_layers<Features,
    // Coefficient Storage API
    kodo_core::coefficient_storage_layers<
    // Storage API
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
    >>>>>>>>>>>>>>
{
public:

    static_assert(!std::is_same<Field,fifi::prime2325>::value,
                  "The mapping between inner and outer code requires "
                  "that both are binary extension fields");

    using factory = kodo_core::pool_factory<fulcrum_combined_decoder>;
};
}
