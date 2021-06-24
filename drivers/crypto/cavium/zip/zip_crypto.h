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

#अगर_अघोषित __ZIP_CRYPTO_H__
#घोषणा __ZIP_CRYPTO_H__

#समावेश <linux/crypto.h>
#समावेश <crypto/पूर्णांकernal/scompress.h>
#समावेश "common.h"
#समावेश "zip_deflate.h"
#समावेश "zip_inflate.h"

काष्ठा zip_kernel_ctx अणु
	काष्ठा zip_operation zip_comp;
	काष्ठा zip_operation zip_decomp;
पूर्ण;

पूर्णांक  zip_alloc_comp_ctx_deflate(काष्ठा crypto_tfm *tfm);
पूर्णांक  zip_alloc_comp_ctx_lzs(काष्ठा crypto_tfm *tfm);
व्योम zip_मुक्त_comp_ctx(काष्ठा crypto_tfm *tfm);
पूर्णांक  zip_comp_compress(काष्ठा crypto_tfm *tfm,
		       स्थिर u8 *src, अचिन्हित पूर्णांक slen,
		       u8 *dst, अचिन्हित पूर्णांक *dlen);
पूर्णांक  zip_comp_decompress(काष्ठा crypto_tfm *tfm,
			 स्थिर u8 *src, अचिन्हित पूर्णांक slen,
			 u8 *dst, अचिन्हित पूर्णांक *dlen);

व्योम *zip_alloc_scomp_ctx_deflate(काष्ठा crypto_scomp *tfm);
व्योम *zip_alloc_scomp_ctx_lzs(काष्ठा crypto_scomp *tfm);
व्योम  zip_मुक्त_scomp_ctx(काष्ठा crypto_scomp *tfm, व्योम *zip_ctx);
पूर्णांक   zip_scomp_compress(काष्ठा crypto_scomp *tfm,
			 स्थिर u8 *src, अचिन्हित पूर्णांक slen,
			 u8 *dst, अचिन्हित पूर्णांक *dlen, व्योम *ctx);
पूर्णांक   zip_scomp_decompress(काष्ठा crypto_scomp *tfm,
			   स्थिर u8 *src, अचिन्हित पूर्णांक slen,
			   u8 *dst, अचिन्हित पूर्णांक *dlen, व्योम *ctx);
#पूर्ण_अगर
