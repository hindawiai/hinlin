<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2012-2019 ARM Limited (or its affiliates). */

/* \पile cc_cipher.h
 * ARM CryptoCell Cipher Crypto API
 */

#अगर_अघोषित __CC_CIPHER_H__
#घोषणा __CC_CIPHER_H__

#समावेश <linux/kernel.h>
#समावेश <crypto/algapi.h>
#समावेश "cc_driver.h"
#समावेश "cc_buffer_mgr.h"

काष्ठा cipher_req_ctx अणु
	काष्ठा async_gen_req_ctx gen_ctx;
	क्रमागत cc_req_dma_buf_type dma_buf_type;
	u32 in_nents;
	u32 in_mlli_nents;
	u32 out_nents;
	u32 out_mlli_nents;
	u8 *iv;
	काष्ठा mlli_params mlli_params;
पूर्ण;

पूर्णांक cc_cipher_alloc(काष्ठा cc_drvdata *drvdata);

पूर्णांक cc_cipher_मुक्त(काष्ठा cc_drvdata *drvdata);

काष्ठा cc_hkey_info अणु
	u16 keylen;
	u8 hw_key1;
	u8 hw_key2;
पूर्ण __packed;

#घोषणा CC_HW_KEY_SIZE माप(काष्ठा cc_hkey_info)

#पूर्ण_अगर /*__CC_CIPHER_H__*/
