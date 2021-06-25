<शैली गुरु>
/***********************license start************************************
 * Copyright (c) 2003-2017 Cavium, Inc.
 * All rights reserved.
 *
 * License: one of 'Cavium License' or 'GNU General Public License Version 2'
 *
 * This file is provided under the terms of the Cavium License (see below)
 * or under the terms of GNU General Public License, Version 2, as
 * published by the Free Software Foundation. When using or redistributing
 * this file, you may करो so under either license.
 *
 * Cavium License:  Redistribution and use in source and binary क्रमms, with
 * or without modअगरication, are permitted provided that the following
 * conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary क्रमm must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the करोcumentation and/or other materials provided
 *    with the distribution.
 *
 *  * Neither the name of Cavium Inc. nor the names of its contributors may be
 *    used to enकरोrse or promote products derived from this software without
 *    specअगरic prior written permission.
 *
 * This Software, including technical data, may be subject to U.S. export
 * control laws, including the U.S. Export Administration Act and its
 * associated regulations, and may be subject to export or import
 * regulations in other countries.
 *
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
 * AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS
 * OR WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH
 * RESPECT TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
 * REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
 * DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY)
 * WARRANTIES OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A
 * PARTICULAR PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET
 * ENJOYMENT, QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. THE
 * ENTIRE  RISK ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE LIES
 * WITH YOU.
 ***********************license end**************************************/

#समावेश "zip_crypto.h"

अटल व्योम zip_अटल_init_zip_ops(काष्ठा zip_operation *zip_ops,
				    पूर्णांक lzs_flag)
अणु
	zip_ops->flush        = ZIP_FLUSH_FINISH;

	/* equivalent to level 6 of खोलोsource zlib */
	zip_ops->speed          = 1;

	अगर (!lzs_flag) अणु
		zip_ops->ccode		= 0; /* Auto Huffman */
		zip_ops->lzs_flag	= 0;
		zip_ops->क्रमmat		= ZLIB_FORMAT;
	पूर्ण अन्यथा अणु
		zip_ops->ccode		= 3; /* LZS Encoding */
		zip_ops->lzs_flag	= 1;
		zip_ops->क्रमmat		= LZS_FORMAT;
	पूर्ण
	zip_ops->begin_file   = 1;
	zip_ops->history_len  = 0;
	zip_ops->end_file     = 1;
	zip_ops->compcode     = 0;
	zip_ops->csum	      = 1; /* Adler checksum desired */
पूर्ण

अटल पूर्णांक zip_ctx_init(काष्ठा zip_kernel_ctx *zip_ctx, पूर्णांक lzs_flag)
अणु
	काष्ठा zip_operation  *comp_ctx   = &zip_ctx->zip_comp;
	काष्ठा zip_operation  *decomp_ctx = &zip_ctx->zip_decomp;

	zip_अटल_init_zip_ops(comp_ctx, lzs_flag);
	zip_अटल_init_zip_ops(decomp_ctx, lzs_flag);

	comp_ctx->input  = zip_data_buf_alloc(MAX_INPUT_BUFFER_SIZE);
	अगर (!comp_ctx->input)
		वापस -ENOMEM;

	comp_ctx->output = zip_data_buf_alloc(MAX_OUTPUT_BUFFER_SIZE);
	अगर (!comp_ctx->output)
		जाओ err_comp_input;

	decomp_ctx->input  = zip_data_buf_alloc(MAX_INPUT_BUFFER_SIZE);
	अगर (!decomp_ctx->input)
		जाओ err_comp_output;

	decomp_ctx->output = zip_data_buf_alloc(MAX_OUTPUT_BUFFER_SIZE);
	अगर (!decomp_ctx->output)
		जाओ err_decomp_input;

	वापस 0;

err_decomp_input:
	zip_data_buf_मुक्त(decomp_ctx->input, MAX_INPUT_BUFFER_SIZE);

err_comp_output:
	zip_data_buf_मुक्त(comp_ctx->output, MAX_OUTPUT_BUFFER_SIZE);

err_comp_input:
	zip_data_buf_मुक्त(comp_ctx->input, MAX_INPUT_BUFFER_SIZE);

	वापस -ENOMEM;
पूर्ण

अटल व्योम zip_ctx_निकास(काष्ठा zip_kernel_ctx *zip_ctx)
अणु
	काष्ठा zip_operation  *comp_ctx   = &zip_ctx->zip_comp;
	काष्ठा zip_operation  *dec_ctx = &zip_ctx->zip_decomp;

	zip_data_buf_मुक्त(comp_ctx->input, MAX_INPUT_BUFFER_SIZE);
	zip_data_buf_मुक्त(comp_ctx->output, MAX_OUTPUT_BUFFER_SIZE);

	zip_data_buf_मुक्त(dec_ctx->input, MAX_INPUT_BUFFER_SIZE);
	zip_data_buf_मुक्त(dec_ctx->output, MAX_OUTPUT_BUFFER_SIZE);
पूर्ण

अटल पूर्णांक zip_compress(स्थिर u8 *src, अचिन्हित पूर्णांक slen,
		 u8 *dst, अचिन्हित पूर्णांक *dlen,
		 काष्ठा zip_kernel_ctx *zip_ctx)
अणु
	काष्ठा zip_operation  *zip_ops   = शून्य;
	काष्ठा zip_state      *zip_state;
	काष्ठा zip_device     *zip = शून्य;
	पूर्णांक ret;

	अगर (!zip_ctx || !src || !dst || !dlen)
		वापस -ENOMEM;

	zip = zip_get_device(zip_get_node_id());
	अगर (!zip)
		वापस -ENODEV;

	zip_state = kzalloc(माप(*zip_state), GFP_ATOMIC);
	अगर (!zip_state)
		वापस -ENOMEM;

	zip_ops = &zip_ctx->zip_comp;

	zip_ops->input_len  = slen;
	zip_ops->output_len = *dlen;
	स_नकल(zip_ops->input, src, slen);

	ret = zip_deflate(zip_ops, zip_state, zip);

	अगर (!ret) अणु
		*dlen = zip_ops->output_len;
		स_नकल(dst, zip_ops->output, *dlen);
	पूर्ण
	kमुक्त(zip_state);
	वापस ret;
पूर्ण

अटल पूर्णांक zip_decompress(स्थिर u8 *src, अचिन्हित पूर्णांक slen,
		   u8 *dst, अचिन्हित पूर्णांक *dlen,
		   काष्ठा zip_kernel_ctx *zip_ctx)
अणु
	काष्ठा zip_operation  *zip_ops   = शून्य;
	काष्ठा zip_state      *zip_state;
	काष्ठा zip_device     *zip = शून्य;
	पूर्णांक ret;

	अगर (!zip_ctx || !src || !dst || !dlen)
		वापस -ENOMEM;

	zip = zip_get_device(zip_get_node_id());
	अगर (!zip)
		वापस -ENODEV;

	zip_state = kzalloc(माप(*zip_state), GFP_ATOMIC);
	अगर (!zip_state)
		वापस -ENOMEM;

	zip_ops = &zip_ctx->zip_decomp;
	स_नकल(zip_ops->input, src, slen);

	/* Work around क्रम a bug in zlib which needs an extra bytes someबार */
	अगर (zip_ops->ccode != 3) /* Not LZS Encoding */
		zip_ops->input[slen++] = 0;

	zip_ops->input_len  = slen;
	zip_ops->output_len = *dlen;

	ret = zip_inflate(zip_ops, zip_state, zip);

	अगर (!ret) अणु
		*dlen = zip_ops->output_len;
		स_नकल(dst, zip_ops->output, *dlen);
	पूर्ण
	kमुक्त(zip_state);
	वापस ret;
पूर्ण

/* Legacy Compress framework start */
पूर्णांक zip_alloc_comp_ctx_deflate(काष्ठा crypto_tfm *tfm)
अणु
	पूर्णांक ret;
	काष्ठा zip_kernel_ctx *zip_ctx = crypto_tfm_ctx(tfm);

	ret = zip_ctx_init(zip_ctx, 0);

	वापस ret;
पूर्ण

पूर्णांक zip_alloc_comp_ctx_lzs(काष्ठा crypto_tfm *tfm)
अणु
	पूर्णांक ret;
	काष्ठा zip_kernel_ctx *zip_ctx = crypto_tfm_ctx(tfm);

	ret = zip_ctx_init(zip_ctx, 1);

	वापस ret;
पूर्ण

व्योम zip_मुक्त_comp_ctx(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा zip_kernel_ctx *zip_ctx = crypto_tfm_ctx(tfm);

	zip_ctx_निकास(zip_ctx);
पूर्ण

पूर्णांक  zip_comp_compress(काष्ठा crypto_tfm *tfm,
		       स्थिर u8 *src, अचिन्हित पूर्णांक slen,
		       u8 *dst, अचिन्हित पूर्णांक *dlen)
अणु
	पूर्णांक ret;
	काष्ठा zip_kernel_ctx *zip_ctx = crypto_tfm_ctx(tfm);

	ret = zip_compress(src, slen, dst, dlen, zip_ctx);

	वापस ret;
पूर्ण

पूर्णांक  zip_comp_decompress(काष्ठा crypto_tfm *tfm,
			 स्थिर u8 *src, अचिन्हित पूर्णांक slen,
			 u8 *dst, अचिन्हित पूर्णांक *dlen)
अणु
	पूर्णांक ret;
	काष्ठा zip_kernel_ctx *zip_ctx = crypto_tfm_ctx(tfm);

	ret = zip_decompress(src, slen, dst, dlen, zip_ctx);

	वापस ret;
पूर्ण /* Legacy compress framework end */

/* SCOMP framework start */
व्योम *zip_alloc_scomp_ctx_deflate(काष्ठा crypto_scomp *tfm)
अणु
	पूर्णांक ret;
	काष्ठा zip_kernel_ctx *zip_ctx;

	zip_ctx = kzalloc(माप(*zip_ctx), GFP_KERNEL);
	अगर (!zip_ctx)
		वापस ERR_PTR(-ENOMEM);

	ret = zip_ctx_init(zip_ctx, 0);

	अगर (ret) अणु
		kमुक्त_sensitive(zip_ctx);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस zip_ctx;
पूर्ण

व्योम *zip_alloc_scomp_ctx_lzs(काष्ठा crypto_scomp *tfm)
अणु
	पूर्णांक ret;
	काष्ठा zip_kernel_ctx *zip_ctx;

	zip_ctx = kzalloc(माप(*zip_ctx), GFP_KERNEL);
	अगर (!zip_ctx)
		वापस ERR_PTR(-ENOMEM);

	ret = zip_ctx_init(zip_ctx, 1);

	अगर (ret) अणु
		kमुक्त_sensitive(zip_ctx);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस zip_ctx;
पूर्ण

व्योम zip_मुक्त_scomp_ctx(काष्ठा crypto_scomp *tfm, व्योम *ctx)
अणु
	काष्ठा zip_kernel_ctx *zip_ctx = ctx;

	zip_ctx_निकास(zip_ctx);
	kमुक्त_sensitive(zip_ctx);
पूर्ण

पूर्णांक zip_scomp_compress(काष्ठा crypto_scomp *tfm,
		       स्थिर u8 *src, अचिन्हित पूर्णांक slen,
		       u8 *dst, अचिन्हित पूर्णांक *dlen, व्योम *ctx)
अणु
	पूर्णांक ret;
	काष्ठा zip_kernel_ctx *zip_ctx  = ctx;

	ret = zip_compress(src, slen, dst, dlen, zip_ctx);

	वापस ret;
पूर्ण

पूर्णांक zip_scomp_decompress(काष्ठा crypto_scomp *tfm,
			 स्थिर u8 *src, अचिन्हित पूर्णांक slen,
			 u8 *dst, अचिन्हित पूर्णांक *dlen, व्योम *ctx)
अणु
	पूर्णांक ret;
	काष्ठा zip_kernel_ctx *zip_ctx = ctx;

	ret = zip_decompress(src, slen, dst, dlen, zip_ctx);

	वापस ret;
पूर्ण /* SCOMP framework end */
