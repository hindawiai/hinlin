<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 */

#अगर_अघोषित __CHACHA20POLY1305_H
#घोषणा __CHACHA20POLY1305_H

#समावेश <linux/types.h>
#समावेश <linux/scatterlist.h>

क्रमागत chacha20poly1305_lengths अणु
	XCHACHA20POLY1305_NONCE_SIZE = 24,
	CHACHA20POLY1305_KEY_SIZE = 32,
	CHACHA20POLY1305_AUTHTAG_SIZE = 16
पूर्ण;

व्योम chacha20poly1305_encrypt(u8 *dst, स्थिर u8 *src, स्थिर माप_प्रकार src_len,
			      स्थिर u8 *ad, स्थिर माप_प्रकार ad_len,
			      स्थिर u64 nonce,
			      स्थिर u8 key[CHACHA20POLY1305_KEY_SIZE]);

bool __must_check
chacha20poly1305_decrypt(u8 *dst, स्थिर u8 *src, स्थिर माप_प्रकार src_len,
			 स्थिर u8 *ad, स्थिर माप_प्रकार ad_len, स्थिर u64 nonce,
			 स्थिर u8 key[CHACHA20POLY1305_KEY_SIZE]);

व्योम xchacha20poly1305_encrypt(u8 *dst, स्थिर u8 *src, स्थिर माप_प्रकार src_len,
			       स्थिर u8 *ad, स्थिर माप_प्रकार ad_len,
			       स्थिर u8 nonce[XCHACHA20POLY1305_NONCE_SIZE],
			       स्थिर u8 key[CHACHA20POLY1305_KEY_SIZE]);

bool __must_check xchacha20poly1305_decrypt(
	u8 *dst, स्थिर u8 *src, स्थिर माप_प्रकार src_len, स्थिर u8 *ad,
	स्थिर माप_प्रकार ad_len, स्थिर u8 nonce[XCHACHA20POLY1305_NONCE_SIZE],
	स्थिर u8 key[CHACHA20POLY1305_KEY_SIZE]);

bool chacha20poly1305_encrypt_sg_inplace(काष्ठा scatterlist *src, माप_प्रकार src_len,
					 स्थिर u8 *ad, स्थिर माप_प्रकार ad_len,
					 स्थिर u64 nonce,
					 स्थिर u8 key[CHACHA20POLY1305_KEY_SIZE]);

bool chacha20poly1305_decrypt_sg_inplace(काष्ठा scatterlist *src, माप_प्रकार src_len,
					 स्थिर u8 *ad, स्थिर माप_प्रकार ad_len,
					 स्थिर u64 nonce,
					 स्थिर u8 key[CHACHA20POLY1305_KEY_SIZE]);

bool chacha20poly1305_selftest(व्योम);

#पूर्ण_अगर /* __CHACHA20POLY1305_H */
