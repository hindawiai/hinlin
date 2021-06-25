<शैली गुरु>
/*
 *  linux/net/sunrpc/gss_krb5_seqnum.c
 *
 *  Adapted from MIT Kerberos 5-1.2.1 lib/gssapi/krb5/util_seqnum.c
 *
 *  Copyright (c) 2000 The Regents of the University of Michigan.
 *  All rights reserved.
 *
 *  Andy Adamson   <andros@umich.edu>
 */

/*
 * Copyright 1993 by OpenVision Technologies, Inc.
 *
 * Permission to use, copy, modअगरy, distribute, and sell this software
 * and its करोcumentation क्रम any purpose is hereby granted without fee,
 * provided that the above copyright notice appears in all copies and
 * that both that copyright notice and this permission notice appear in
 * supporting करोcumentation, and that the name of OpenVision not be used
 * in advertising or खुलाity pertaining to distribution of the software
 * without specअगरic, written prior permission. OpenVision makes no
 * representations about the suitability of this software क्रम any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 * OPENVISION DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL OPENVISION BE LIABLE FOR ANY SPECIAL, INसूचीECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
 * USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश <crypto/skcipher.h>
#समावेश <linux/types.h>
#समावेश <linux/sunrpc/gss_krb5.h>

#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
# define RPCDBG_FACILITY        RPCDBG_AUTH
#पूर्ण_अगर

s32
krb5_make_seq_num(काष्ठा krb5_ctx *kctx,
		काष्ठा crypto_sync_skcipher *key,
		पूर्णांक direction,
		u32 seqnum,
		अचिन्हित अक्षर *cksum, अचिन्हित अक्षर *buf)
अणु
	अचिन्हित अक्षर *plain;
	s32 code;

	plain = kदो_स्मृति(8, GFP_NOFS);
	अगर (!plain)
		वापस -ENOMEM;

	plain[0] = (अचिन्हित अक्षर) (seqnum & 0xff);
	plain[1] = (अचिन्हित अक्षर) ((seqnum >> 8) & 0xff);
	plain[2] = (अचिन्हित अक्षर) ((seqnum >> 16) & 0xff);
	plain[3] = (अचिन्हित अक्षर) ((seqnum >> 24) & 0xff);

	plain[4] = direction;
	plain[5] = direction;
	plain[6] = direction;
	plain[7] = direction;

	code = krb5_encrypt(key, cksum, plain, buf, 8);
	kमुक्त(plain);
	वापस code;
पूर्ण

s32
krb5_get_seq_num(काष्ठा krb5_ctx *kctx,
	       अचिन्हित अक्षर *cksum,
	       अचिन्हित अक्षर *buf,
	       पूर्णांक *direction, u32 *seqnum)
अणु
	s32 code;
	अचिन्हित अक्षर *plain;
	काष्ठा crypto_sync_skcipher *key = kctx->seq;

	dprपूर्णांकk("RPC:       krb5_get_seq_num:\n");

	plain = kदो_स्मृति(8, GFP_NOFS);
	अगर (!plain)
		वापस -ENOMEM;

	अगर ((code = krb5_decrypt(key, cksum, buf, plain, 8)))
		जाओ out;

	अगर ((plain[4] != plain[5]) || (plain[4] != plain[6]) ||
	    (plain[4] != plain[7])) अणु
		code = (s32)KG_BAD_SEQ;
		जाओ out;
	पूर्ण

	*direction = plain[4];

	*seqnum = ((plain[0]) |
		   (plain[1] << 8) | (plain[2] << 16) | (plain[3] << 24));

out:
	kमुक्त(plain);
	वापस code;
पूर्ण
