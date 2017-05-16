// Copyright Steinwurf ApS 2015.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <algorithm>
#include <cstdint>
#include <ctime>
#include <iostream>
#include <vector>
#include <fstream>

#include <storage/storage.hpp>

#include "kodo_fulcrum_sparse/fulcrum_sparse_codes.hpp"
void none_zero_generated_statistic();
/// @example encode_decode_fulcrum.cpp
///
/// Simple example showing how to encode and decode a block of data using
/// the fulcrum codec.
/// For a detailed description of the fulcrum codec see the following paper
/// on arxiv: http://arxiv.org/abs/1404.6620 by Lucani et. al.

int main()
{
//	none_zero_generated_statistic();

	for(int i=0; i< 1; i++)
	{
	// Seed the random number generator to get different random data
	    srand(static_cast<uint32_t>(time(0)));

	    uint32_t symbols = 5;
	    uint32_t symbol_size = 1;
	    const uint32_t expansion = 10;

	    using encoder_type = kodo_fulcrum::fulcrum_sparse_encoder<fifi::binary8, meta::typelist<kodo_core::enable_trace>>;
	    using decoder_type = kodo_fulcrum::fulcrum_sparse_combined_decoder<fifi::binary8, meta::typelist<kodo_core::enable_trace>>;
	    using recoder_type = kodo_fulcrum::fulcrum_sparse_inner_decoder<fifi::binary, meta::typelist<kodo_core::enable_trace>>;

	    encoder_type::factory encoder_factory(symbols, symbol_size);
	    encoder_factory.set_expansion(expansion);

	    auto encoder = encoder_factory.build();
//	    std::cout << "Default density:" << encoder->density() << std::endl;

	    encoder->nested()->set_density(0.6);
	    encoder->set_systematic_off();

	    decoder_type::factory decoder_factory(symbols, symbol_size);
	    decoder_factory.set_expansion(expansion);

	    auto decoder = decoder_factory.build();

	    recoder_type::factory recoder_factory(symbols, symbol_size);
	    recoder_factory.set_expansion(expansion);
	    auto recoder = recoder_factory.build();

	    //Enable trace
	    encoder->set_trace_stdout();
	    encoder->set_zone_prefix("ENCODER");

	    decoder->set_trace_stdout();
	    decoder->set_zone_prefix("decoder");

	    recoder->set_trace_stdout();
	   	recoder->set_zone_prefix("**RECODER**");

	    std::vector<uint8_t> payload(encoder->payload_size());

	    std::vector<uint8_t> data_in(encoder->block_size());

//	    std::generate(data_in.begin(), data_in.end(), rand);
	    for(uint8_t i=0;i<data_in.size();i++)
	    	data_in[i]=i+10;

	    encoder->set_const_symbols(storage::storage(data_in));
	    uint32_t time=0;
	    while (!decoder->is_complete())
	    {
	    	std::cout<<"--------------------------------------"<<std::endl;
	        encoder->write_payload(payload.data());
	        time=time+1;
//	        if(rand()%2==0)
//	        {
//	           	std::cout<<"ERROR TOOK PLACE!"<<std::endl;
//	           	continue;
//	        }
	        recoder->read_payload(payload.data());
	        recoder->nested()->write_payload(payload.data());

	    	std::cout<<"--------------------------------------"<<std::endl;
	        decoder->read_payload(payload.data());
	    }

	    // The decoder is complete, now copy the symbols from the decoder
	    std::vector<uint8_t> data_out(decoder->block_size());
	    decoder->copy_from_symbols(storage::storage(data_out));

	    // Check if we properly decoded the data
	    if (std::equal(data_out.begin(), data_out.end(), data_in.begin()))
	    {
	        std::cout << "Data decoded correctly" << std::endl;
	    }
	    else
	    {
	        std::cout << "Unexpected failure to decode, "
	                  << "please file a bug report :)" << std::endl;
	    }
//	    std::cout << "Time to encode:" << time << std::endl;

	}
}

void none_zero_generated_statistic()
{
	std::ofstream myfile;
	myfile.open("fulcrumsparse_none_zero.csv");
	myfile << "time,density,nonezero,\n";
	int runs = 1;
	for (int density = 1; density < 10; density++)
		for (int run = 0; run < runs; run++) {
			// Seed the random number generator to get different random data
			srand(static_cast<uint32_t>(time(0)));

			// Set the number of symbols (i.e. the generation size in RLNC
			// terminology) and the size of a symbol in bytes
			uint32_t symbols = 200;
			uint32_t symbol_size = 1600;

		    // Set the number of symbols (i.e. the generation size in RLNC
		    // terminology) and the size of a symbol in bytes


		    // Define the fulcrum encoder/decoder types that we will use
		    using encoder_type = kodo_fulcrum::fulcrum_sparse_encoder<fifi::binary8, meta::typelist<kodo_core::enable_trace>>;
		    using decoder_type = kodo_fulcrum::fulcrum_sparse_outer_decoder<fifi::binary8, meta::typelist<kodo_core::enable_trace>>;
		   // using recoder_type = kodo_fulcrum::fulcrum_inner_decoder<fifi::binary>;


		    // In the following we will make an encoder/decoder factory.
		    // The factories are used to build actual encoders/decoders
		    encoder_type::factory encoder_factory(symbols, symbol_size);

		    // We query the maximum number of expansion symbols for the fulcrum factory
	//	    std::cout << "Max expansion of the encoder factory: "
	//	              << encoder_factory.max_expansion() << std::endl;

		    // Before building the encoder, you can change the number of expansion
		    // symbols like this:
		    //
		    encoder_factory.set_expansion(2);

		    //encoder_factory.set_density(0.1);
		    auto encoder = encoder_factory.build();
		    std::cout << "encoder built" << std::endl;
	//	    std::cout << "Default density:" << encoder->density() << std::endl;

		    // density of expansion symbols
		    //encoder->set_density((double)density/10);
		    // density of coded packets
		    encoder->nested()->set_density((double)density/10);

		    //encoder->initialize(encoder_factory);

		    encoder->set_systematic_off();

		    // Get the number of expansion symbols on the fulcrum encoder
	//	    std::cout << "Expansion symbols on the fulcrum encoder : "
	//	              << encoder->expansion() << std::endl;

		    decoder_type::factory decoder_factory(symbols, symbol_size);
		    decoder_factory.set_expansion(2);

		    // We query the maximum number of expansion symbols for the fulcrum factory
	//	    std::cout << "Max expansion of the decoder factory: "
	//	              << decoder_factory.max_expansion() << std::endl;

		    // Before building the decoder, you can change the number of expansion
		    // symbols like this:
		    //

		    auto decoder = decoder_factory.build();
		    std::cout << "decoder built" << std::endl;
//		    decoder->set_density(encoder->nested()->density());
//		    decoder->initialize(decoder_factory);
		    std::cout << "decoder initialized" << std::endl;

		    // Get the number of expansion symbols on the fulcrum decoder
	//	    std::cout << "Expansion symbols on the fulcrum decoder : "
	//	              << decoder->expansion() << std::endl;

		    // Allocate some storage for a "payload" the payload is what we would
		    // eventually send over a network
		    std::vector<uint8_t> payload(encoder->payload_size());

		    // Allocate some data to encode. In this case we make a buffer
		    // with the same size as the encoder's block size (the max.
		    // amount a single encoder can encode)
		    std::vector<uint8_t> data_in(encoder->block_size());

		    // Just for fun - fill the data with random data
		    std::generate(data_in.begin(), data_in.end(), rand);


		    // Assign the data buffer to the encoder so that we may start
		    // to produce encoded symbols
		    encoder->set_const_symbols(storage::storage(data_in));
		    //Count the number of times to decode
		    uint32_t time=0;
//		    uint8_t previous_rank=0;
		    // Generate packets until the decoder is complete
		    while (!decoder->is_complete())
		    {
		        // Encode a packet into the payload buffer
		        encoder->write_payload(payload.data());
		        //std::cout << "write_payload" << std::endl;
		        time=time+1;
//		        previous_rank = decoder->rank();
		        					myfile << time << "," << (double) density / 10 << ","
		        							<< (double) encoder->nested()->nonzeros_generated() / symbols
		        							<< "," << std::endl;
		        					std::cout << time << "," << (double) density / 10 << "," << encoder->nested()->density() << ","
		        							<<encoder->nested()->nonzeros_generated() <<","
		        							<< (double) encoder->nested()->nonzeros_generated() / symbols
		        							<< "," << std::endl;

		        // Pass that packet to the decoder
		        decoder->read_payload(payload.data());

		    }
		    	    std::vector<uint8_t> data_out(decoder->block_size());
		    	    decoder->copy_from_symbols(storage::storage(data_out));

		    	    // Check if we properly decoded the data
		    	    if (std::equal(data_out.begin(), data_out.end(), data_in.begin()))
		    	    {
		    	        std::cout << "Data decoded correctly" << std::endl;
		    	    }
		    	    else
		    	    {
		    	        std::cout << "Unexpected failure to decode, "
		    	                  << "please file a bug report :)" << std::endl;
		    	    }

		}
	myfile.close();
}
