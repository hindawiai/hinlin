<शैली गुरु>
/*
 *  linux/net/sunrpc/gss_krb5_unseal.c
 *
 *  Adapted from MIT Kerberos 5-1.2.1 lib/gssapi/krb5/k5unseal.c
 *
 *  Copyright (c) 2000-2008 The Regents of the University of Michigan.
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

/*
 * Copyright (C) 1998 by the FundsXpress, INC.
 *
 * All rights reserved.
 *
 * Export of this software from the United States of America may require
 * a specअगरic license from the United States Government.  It is the
 * responsibility of any person or organization contemplating export to
 * obtain such a license beक्रमe exporting.
 *
 * WITHIN THAT CONSTRAINT, permission to use, copy, modअगरy, and
 * distribute this software and its करोcumentation क्रम any purpose and
 * without fee is hereby granted, provided that the above copyright
 * notice appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting करोcumentation, and that
 * the name of FundsXpress. not be used in advertising or खुलाity pertaining
 * to distribution of the software without specअगरic, written prior
 * permission.  FundsXpress makes no representations about the suitability of
 * this software क्रम any purpose.  It is provided "as is" without express
 * or implied warranty.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#समावेश <linux/types.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/sunrpc/gss_krb5.h>
#समावेश <linux/crypto.h>

#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
# define RPCDBG_FACILITY        RPCDBG_AUTH
#पूर्ण_अगर


/* पढ़ो_token is a mic token, and message_buffer is the data that the mic was
 * supposedly taken over. */

अटल u32
gss_verअगरy_mic_v1(काष्ठा krb5_ctx *ctx,
		काष्ठा xdr_buf *message_buffer, काष्ठा xdr_netobj *पढ़ो_token)
अणु
	पूर्णांक			संकेतg;
	पूर्णांक			sealalg;
	अक्षर			cksumdata[GSS_KRB5_MAX_CKSUM_LEN];
	काष्ठा xdr_netobj	md5cksum = अणु.len = माप(cksumdata),
					    .data = cksumdataपूर्ण;
	s32			now;
	पूर्णांक			direction;
	u32			seqnum;
	अचिन्हित अक्षर		*ptr = (अचिन्हित अक्षर *)पढ़ो_token->data;
	पूर्णांक			bodysize;
	u8			*cksumkey;

	dprपूर्णांकk("RPC:       krb5_read_token\n");

	अगर (g_verअगरy_token_header(&ctx->mech_used, &bodysize, &ptr,
					पढ़ो_token->len))
		वापस GSS_S_DEFECTIVE_TOKEN;

	अगर ((ptr[0] != ((KG_TOK_MIC_MSG >> 8) & 0xff)) ||
	    (ptr[1] !=  (KG_TOK_MIC_MSG & 0xff)))
		वापस GSS_S_DEFECTIVE_TOKEN;

	/* XXX sanity-check bodysize?? */

	संकेतg = ptr[2] + (ptr[3] << 8);
	अगर (संकेतg != ctx->gk5e->संकेतg)
		वापस GSS_S_DEFECTIVE_TOKEN;

	sealalg = ptr[4] + (ptr[5] << 8);
	अगर (sealalg != SEAL_ALG_NONE)
		वापस GSS_S_DEFECTIVE_TOKEN;

	अगर ((ptr[6] != 0xff) || (ptr[7] != 0xff))
		वापस GSS_S_DEFECTIVE_TOKEN;

	अगर (ctx->gk5e->keyed_cksum)
		cksumkey = ctx->cksum;
	अन्यथा
		cksumkey = शून्य;

	अगर (make_checksum(ctx, ptr, 8, message_buffer, 0,
			  cksumkey, KG_USAGE_SIGN, &md5cksum))
		वापस GSS_S_FAILURE;

	अगर (स_भेद(md5cksum.data, ptr + GSS_KRB5_TOK_HDR_LEN,
					ctx->gk5e->cksumlength))
		वापस GSS_S_BAD_SIG;

	/* it got through unscathed.  Make sure the context is unexpired */

	now = kसमय_get_real_seconds();

	अगर (now > ctx->endसमय)
		वापस GSS_S_CONTEXT_EXPIRED;

	/* करो sequencing checks */

	अगर (krb5_get_seq_num(ctx, ptr + GSS_KRB5_TOK_HDR_LEN, ptr + 8,
			     &direction, &seqnum))
		वापस GSS_S_FAILURE;

	अगर ((ctx->initiate && direction != 0xff) ||
	    (!ctx->initiate && direction != 0))
		वापस GSS_S_BAD_SIG;

	वापस GSS_S_COMPLETE;
पूर्ण

अटल u32
gss_verअगरy_mic_v2(काष्ठा krb5_ctx *ctx,
		काष्ठा xdr_buf *message_buffer, काष्ठा xdr_netobj *पढ़ो_token)
अणु
	अक्षर cksumdata[GSS_KRB5_MAX_CKSUM_LEN];
	काष्ठा xdr_netobj cksumobj = अणु.len = माप(cksumdata),
				      .data = cksumdataपूर्ण;
	समय64_t now;
	u8 *ptr = पढ़ो_token->data;
	u8 *cksumkey;
	u8 flags;
	पूर्णांक i;
	अचिन्हित पूर्णांक cksum_usage;
	__be16 be16_ptr;

	dprपूर्णांकk("RPC:       %s\n", __func__);

	स_नकल(&be16_ptr, (अक्षर *) ptr, 2);
	अगर (be16_to_cpu(be16_ptr) != KG2_TOK_MIC)
		वापस GSS_S_DEFECTIVE_TOKEN;

	flags = ptr[2];
	अगर ((!ctx->initiate && (flags & KG2_TOKEN_FLAG_SENTBYACCEPTOR)) ||
	    (ctx->initiate && !(flags & KG2_TOKEN_FLAG_SENTBYACCEPTOR)))
		वापस GSS_S_BAD_SIG;

	अगर (flags & KG2_TOKEN_FLAG_SEALED) अणु
		dprपूर्णांकk("%s: token has unexpected sealed flag\n", __func__);
		वापस GSS_S_FAILURE;
	पूर्ण

	क्रम (i = 3; i < 8; i++)
		अगर (ptr[i] != 0xff)
			वापस GSS_S_DEFECTIVE_TOKEN;

	अगर (ctx->initiate) अणु
		cksumkey = ctx->acceptor_sign;
		cksum_usage = KG_USAGE_ACCEPTOR_SIGN;
	पूर्ण अन्यथा अणु
		cksumkey = ctx->initiator_sign;
		cksum_usage = KG_USAGE_INITIATOR_SIGN;
	पूर्ण

	अगर (make_checksum_v2(ctx, ptr, GSS_KRB5_TOK_HDR_LEN, message_buffer, 0,
			     cksumkey, cksum_usage, &cksumobj))
		वापस GSS_S_FAILURE;

	अगर (स_भेद(cksumobj.data, ptr + GSS_KRB5_TOK_HDR_LEN,
				ctx->gk5e->cksumlength))
		वापस GSS_S_BAD_SIG;

	/* it got through unscathed.  Make sure the context is unexpired */
	now = kसमय_get_real_seconds();
	अगर (now > ctx->endसमय)
		वापस GSS_S_CONTEXT_EXPIRED;

	/*
	 * NOTE: the sequence number at ptr + 8 is skipped, rpcsec_gss
	 * करोesn't want it checked; see page 6 of rfc 2203.
	 */

	वापस GSS_S_COMPLETE;
पूर्ण

u32
gss_verअगरy_mic_kerberos(काष्ठा gss_ctx *gss_ctx,
			काष्ठा xdr_buf *message_buffer,
			काष्ठा xdr_netobj *पढ़ो_token)
अणु
	काष्ठा krb5_ctx *ctx = gss_ctx->पूर्णांकernal_ctx_id;

	चयन (ctx->enctype) अणु
	शेष:
		BUG();
	हाल ENCTYPE_DES_CBC_RAW:
	हाल ENCTYPE_DES3_CBC_RAW:
		वापस gss_verअगरy_mic_v1(ctx, message_buffer, पढ़ो_token);
	हाल ENCTYPE_AES128_CTS_HMAC_SHA1_96:
	हाल ENCTYPE_AES256_CTS_HMAC_SHA1_96:
		वापस gss_verअगरy_mic_v2(ctx, message_buffer, पढ़ो_token);
	पूर्ण
पूर्ण
