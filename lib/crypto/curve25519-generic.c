<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 *
 * This is an implementation of the Curve25519 ECDH algorithm, using either
 * a 32-bit implementation or a 64-bit implementation with 128-bit पूर्णांकegers,
 * depending on what is supported by the target compiler.
 *
 * Inक्रमmation: https://cr.yp.to/ecdh.hपंचांगl
 */

#समावेश <crypto/curve25519.h>
#समावेश <linux/module.h>

स्थिर u8 curve25519_null_poपूर्णांक[CURVE25519_KEY_SIZE] __aligned(32) = अणु 0 पूर्ण;
स्थिर u8 curve25519_base_poपूर्णांक[CURVE25519_KEY_SIZE] __aligned(32) = अणु 9 पूर्ण;

EXPORT_SYMBOL(curve25519_null_poपूर्णांक);
EXPORT_SYMBOL(curve25519_base_poपूर्णांक);
EXPORT_SYMBOL(curve25519_generic);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Curve25519 scalar multiplication");
MODULE_AUTHOR("Jason A. Donenfeld <Jason@zx2c4.com>");
