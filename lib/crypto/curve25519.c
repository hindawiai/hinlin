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
#समावेश <linux/init.h>

अटल पूर्णांक __init mod_init(व्योम)
अणु
	अगर (!IS_ENABLED(CONFIG_CRYPTO_MANAGER_DISABLE_TESTS) &&
	    WARN_ON(!curve25519_selftest()))
		वापस -ENODEV;
	वापस 0;
पूर्ण

अटल व्योम __निकास mod_निकास(व्योम)
अणु
पूर्ण

module_init(mod_init);
module_निकास(mod_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Curve25519 scalar multiplication");
MODULE_AUTHOR("Jason A. Donenfeld <Jason@zx2c4.com>");
