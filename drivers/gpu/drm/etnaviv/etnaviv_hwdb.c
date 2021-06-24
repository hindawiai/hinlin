<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Etnaviv Project
 */

#समावेश "etnaviv_gpu.h"

अटल स्थिर काष्ठा etnaviv_chip_identity etnaviv_chip_identities[] = अणु
	अणु
		.model = 0x400,
		.revision = 0x4652,
		.product_id = 0x70001,
		.customer_id = 0x100,
		.eco_id = 0,
		.stream_count = 4,
		.रेजिस्टर_max = 64,
		.thपढ़ो_count = 128,
		.shader_core_count = 1,
		.vertex_cache_size = 8,
		.vertex_output_buffer_size = 1024,
		.pixel_pipes = 1,
		.inकाष्ठाion_count = 256,
		.num_स्थिरants = 320,
		.buffer_size = 0,
		.varyings_count = 8,
		.features = 0xa0e9e004,
		.minor_features0 = 0xe1299fff,
		.minor_features1 = 0xbe13b219,
		.minor_features2 = 0xce110010,
		.minor_features3 = 0x8000001,
		.minor_features4 = 0x20102,
		.minor_features5 = 0x120000,
		.minor_features6 = 0x0,
		.minor_features7 = 0x0,
		.minor_features8 = 0x0,
		.minor_features9 = 0x0,
		.minor_features10 = 0x0,
		.minor_features11 = 0x0,
	पूर्ण,
	अणु
		.model = 0x7000,
		.revision = 0x6214,
		.product_id = ~0U,
		.customer_id = ~0U,
		.eco_id = ~0U,
		.stream_count = 16,
		.रेजिस्टर_max = 64,
		.thपढ़ो_count = 1024,
		.shader_core_count = 4,
		.vertex_cache_size = 16,
		.vertex_output_buffer_size = 1024,
		.pixel_pipes = 2,
		.inकाष्ठाion_count = 512,
		.num_स्थिरants = 320,
		.buffer_size = 0,
		.varyings_count = 16,
		.features = 0xe0287cad,
		.minor_features0 = 0xc1799eff,
		.minor_features1 = 0xfefbfad9,
		.minor_features2 = 0xeb9d4fbf,
		.minor_features3 = 0xedfffced,
		.minor_features4 = 0xdb0dafc7,
		.minor_features5 = 0xbb5ac333,
		.minor_features6 = 0xfc8ee200,
		.minor_features7 = 0x03fbfa6f,
		.minor_features8 = 0x00ef0ef0,
		.minor_features9 = 0x0edbf03c,
		.minor_features10 = 0x90044250,
		.minor_features11 = 0x00000024,
	पूर्ण,
पूर्ण;

bool etnaviv_fill_identity_from_hwdb(काष्ठा etnaviv_gpu *gpu)
अणु
	काष्ठा etnaviv_chip_identity *ident = &gpu->identity;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(etnaviv_chip_identities); i++) अणु
		अगर (etnaviv_chip_identities[i].model == ident->model &&
		    etnaviv_chip_identities[i].revision == ident->revision &&
		    (etnaviv_chip_identities[i].product_id == ident->product_id ||
			 etnaviv_chip_identities[i].product_id == ~0U) &&
		    (etnaviv_chip_identities[i].customer_id == ident->customer_id ||
			 etnaviv_chip_identities[i].customer_id == ~0U) &&
		    (etnaviv_chip_identities[i].eco_id == ident->eco_id ||
			 etnaviv_chip_identities[i].eco_id == ~0U)) अणु
			स_नकल(ident, &etnaviv_chip_identities[i],
			       माप(*ident));
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण
