<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ OR BSD-2-Clause */
/*
 * Copyright (c) 2013 Alexey Degtyarev <alexey@renataप्रणालीs.org>
 * Copyright (c) 2018 Vitaly Chikunov <vt@altlinux.org>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#अगर_अघोषित _CRYPTO_STREEBOG_H_
#घोषणा _CRYPTO_STREEBOG_H_

#समावेश <linux/types.h>

#घोषणा STREEBOG256_DIGEST_SIZE	32
#घोषणा STREEBOG512_DIGEST_SIZE	64
#घोषणा STREEBOG_BLOCK_SIZE	64

काष्ठा streebog_uपूर्णांक512 अणु
	__le64 qword[8];
पूर्ण;

काष्ठा streebog_state अणु
	जोड़ अणु
		u8 buffer[STREEBOG_BLOCK_SIZE];
		काष्ठा streebog_uपूर्णांक512 m;
	पूर्ण;
	काष्ठा streebog_uपूर्णांक512 hash;
	काष्ठा streebog_uपूर्णांक512 h;
	काष्ठा streebog_uपूर्णांक512 N;
	काष्ठा streebog_uपूर्णांक512 Sigma;
	माप_प्रकार fillsize;
पूर्ण;

#पूर्ण_अगर /* !_CRYPTO_STREEBOG_H_ */
