// Copyright Steinwurf ApS 2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <kodo_core/nested_decoder_api.hpp>
#include <kodo_core/nested_payload_size.hpp>
#include <kodo_core/nested_read_payload.hpp>
#include <kodo_core/trace_layer.hpp>
#include <kodo_core/trace_nested_stack.hpp>

#include <kodo_rlnc/shallow_full_vector_decoder.hpp>

#include <kodo_fulcrum/fulcrum_expansion_storage.hpp>
#include <kodo_fulcrum/fulcrum_info.hpp>
#include <kodo_fulcrum/fulcrum_nested_inner_decoder.hpp>
#include <kodo_fulcrum/fulcrum_nested_stack.hpp>

namespace kodo_fulcrum
{
/// @ingroup fec_stacks
///
/// @brief The fulcrum inner decoder only decodes the inner code
///        discarding the extension symbols. It will only work if
///        the outer code is systematic.
///
/// The Field template argument therefore refers to the finite
/// field used in the inner code (typically binary).
///
/// The basic idea behind this design is to forward all encoded
/// payloads into the nested shallow_full_rlnc_decoder, which
/// takes care of the actual decoding.
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
class fulcrum_sparse_inner_decoder : public
    // Coefficient Generator API
    // Codec API
    fulcrum_nested_inner_decoder<
    // Storage API
    fulcrum_expansion_storage<
    kodo_core::deep_symbol_storage<
    kodo_core::storage_bytes_used<
    kodo_core::storage_block_info<
    // Finite Field API
    kodo_core::finite_field<Field,
    // Fulcrum API
    kodo_core::nested_read_payload<
    kodo_core::nested_payload_size<
    kodo_core::nested_decoder_api<
    kodo_core::trace_nested_stack<kodo_core::find_enable_trace<Features>,
    fulcrum_nested_stack<
    kodo_rlnc::shallow_full_vector_decoder<Field, Features>,
    fulcrum_info<
    std::integral_constant<uint32_t,10>, // MaxExpansion
    std::integral_constant<uint32_t,4>,  // DefaultExpansion
    // Trace Layer
    kodo_core::trace_layer<kodo_core::find_enable_trace<Features>,
    // Final Layer
    kodo_core::final_layer
    >>>>>>>>>>>>>
{
public:
    using factory = kodo_core::pool_factory<fulcrum_sparse_inner_decoder>;
};
}
