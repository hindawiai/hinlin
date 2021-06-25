<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* 
 * CRC32C
 *@Articleअणुcastagnoli-crc,
 * author =       अणु Guy Castagnoli and Stefan Braeuer and Martin Herrmanपूर्ण,
 * title =        अणुअणुOptimization of Cyclic Redundancy-Check Codes with 24
 *                 and 32 Parity Bitsपूर्णपूर्ण,
 * journal =      IEEE Transactions on Communication,
 * year =         अणु1993पूर्ण,
 * volume =       अणु41पूर्ण,
 * number =       अणु6पूर्ण,
 * pages =        अणुपूर्ण,
 * month =        अणुJuneपूर्ण,
 *पूर्ण
 * Used by the iSCSI driver, possibly others, and derived from
 * the iscsi-crc.c module of the linux-iscsi driver at
 * http://linux-iscsi.sourceक्रमge.net.
 *
 * Following the example of lib/crc32, this function is पूर्णांकended to be
 * flexible and useful क्रम all users.  Modules that currently have their
 * own crc32c, but hopefully may be able to use this one are:
 *  net/sctp (please add all your करोco to here अगर you change to
 *            use this one!)
 *  <enकरोflist>
 *
 * Copyright (c) 2004 Cisco Systems, Inc.
 */

#समावेश <crypto/hash.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/crc32c.h>

अटल काष्ठा crypto_shash *tfm;

u32 crc32c(u32 crc, स्थिर व्योम *address, अचिन्हित पूर्णांक length)
अणु
	SHASH_DESC_ON_STACK(shash, tfm);
	u32 ret, *ctx = (u32 *)shash_desc_ctx(shash);
	पूर्णांक err;

	shash->tfm = tfm;
	*ctx = crc;

	err = crypto_shash_update(shash, address, length);
	BUG_ON(err);

	ret = *ctx;
	barrier_data(ctx);
	वापस ret;
पूर्ण

EXPORT_SYMBOL(crc32c);

अटल पूर्णांक __init libcrc32c_mod_init(व्योम)
अणु
	tfm = crypto_alloc_shash("crc32c", 0, 0);
	वापस PTR_ERR_OR_ZERO(tfm);
पूर्ण

अटल व्योम __निकास libcrc32c_mod_fini(व्योम)
अणु
	crypto_मुक्त_shash(tfm);
पूर्ण

स्थिर अक्षर *crc32c_impl(व्योम)
अणु
	वापस crypto_shash_driver_name(tfm);
पूर्ण
EXPORT_SYMBOL(crc32c_impl);

module_init(libcrc32c_mod_init);
module_निकास(libcrc32c_mod_fini);

MODULE_AUTHOR("Clay Haapala <chaapala@cisco.com>");
MODULE_DESCRIPTION("CRC32c (Castagnoli) calculations");
MODULE_LICENSE("GPL");
MODULE_SOFTDEP("pre: crc32c");
