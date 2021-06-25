<शैली गुरु>
/*
 *  linux/net/sunrpc/gss_krb5_seal.c
 *
 *  Adapted from MIT Kerberos 5-1.2.1 lib/gssapi/krb5/k5seal.c
 *
 *  Copyright (c) 2000-2008 The Regents of the University of Michigan.
 *  All rights reserved.
 *
 *  Andy Adamson	<andros@umich.edu>
 *  J. Bruce Fields	<bfields@umich.edu>
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
#समावेश <linux/अक्रमom.h>
#समावेश <linux/crypto.h>
#समावेश <linux/atomic.h>

#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
# define RPCDBG_FACILITY        RPCDBG_AUTH
#पूर्ण_अगर

अटल व्योम *
setup_token(काष्ठा krb5_ctx *ctx, काष्ठा xdr_netobj *token)
अणु
	u16 *ptr;
	व्योम *krb5_hdr;
	पूर्णांक body_size = GSS_KRB5_TOK_HDR_LEN + ctx->gk5e->cksumlength;

	token->len = g_token_size(&ctx->mech_used, body_size);

	ptr = (u16 *)token->data;
	g_make_token_header(&ctx->mech_used, body_size, (अचिन्हित अक्षर **)&ptr);

	/* ptr now at start of header described in rfc 1964, section 1.2.1: */
	krb5_hdr = ptr;
	*ptr++ = KG_TOK_MIC_MSG;
	/*
	 * संकेतg is stored as अगर it were converted from LE to host endian, even
	 * though it's an opaque pair of bytes according to the RFC.
	 */
	*ptr++ = (__क्रमce u16)cpu_to_le16(ctx->gk5e->संकेतg);
	*ptr++ = SEAL_ALG_NONE;
	*ptr = 0xffff;

	वापस krb5_hdr;
पूर्ण

अटल व्योम *
setup_token_v2(काष्ठा krb5_ctx *ctx, काष्ठा xdr_netobj *token)
अणु
	u16 *ptr;
	व्योम *krb5_hdr;
	u8 *p, flags = 0x00;

	अगर ((ctx->flags & KRB5_CTX_FLAG_INITIATOR) == 0)
		flags |= 0x01;
	अगर (ctx->flags & KRB5_CTX_FLAG_ACCEPTOR_SUBKEY)
		flags |= 0x04;

	/* Per rfc 4121, sec 4.2.6.1, there is no header,
	 * just start the token */
	krb5_hdr = ptr = (u16 *)token->data;

	*ptr++ = KG2_TOK_MIC;
	p = (u8 *)ptr;
	*p++ = flags;
	*p++ = 0xff;
	ptr = (u16 *)p;
	*ptr++ = 0xffff;
	*ptr = 0xffff;

	token->len = GSS_KRB5_TOK_HDR_LEN + ctx->gk5e->cksumlength;
	वापस krb5_hdr;
पूर्ण

अटल u32
gss_get_mic_v1(काष्ठा krb5_ctx *ctx, काष्ठा xdr_buf *text,
		काष्ठा xdr_netobj *token)
अणु
	अक्षर			cksumdata[GSS_KRB5_MAX_CKSUM_LEN];
	काष्ठा xdr_netobj	md5cksum = अणु.len = माप(cksumdata),
					    .data = cksumdataपूर्ण;
	व्योम			*ptr;
	समय64_t		now;
	u32			seq_send;
	u8			*cksumkey;

	dprपूर्णांकk("RPC:       %s\n", __func__);
	BUG_ON(ctx == शून्य);

	now = kसमय_get_real_seconds();

	ptr = setup_token(ctx, token);

	अगर (ctx->gk5e->keyed_cksum)
		cksumkey = ctx->cksum;
	अन्यथा
		cksumkey = शून्य;

	अगर (make_checksum(ctx, ptr, 8, text, 0, cksumkey,
			  KG_USAGE_SIGN, &md5cksum))
		वापस GSS_S_FAILURE;

	स_नकल(ptr + GSS_KRB5_TOK_HDR_LEN, md5cksum.data, md5cksum.len);

	seq_send = atomic_fetch_inc(&ctx->seq_send);

	अगर (krb5_make_seq_num(ctx, ctx->seq, ctx->initiate ? 0 : 0xff,
			      seq_send, ptr + GSS_KRB5_TOK_HDR_LEN, ptr + 8))
		वापस GSS_S_FAILURE;

	वापस (ctx->endसमय < now) ? GSS_S_CONTEXT_EXPIRED : GSS_S_COMPLETE;
पूर्ण

अटल u32
gss_get_mic_v2(काष्ठा krb5_ctx *ctx, काष्ठा xdr_buf *text,
		काष्ठा xdr_netobj *token)
अणु
	अक्षर cksumdata[GSS_KRB5_MAX_CKSUM_LEN];
	काष्ठा xdr_netobj cksumobj = अणु .len = माप(cksumdata),
				       .data = cksumdataपूर्ण;
	व्योम *krb5_hdr;
	समय64_t now;
	u8 *cksumkey;
	अचिन्हित पूर्णांक cksum_usage;
	__be64 seq_send_be64;

	dprपूर्णांकk("RPC:       %s\n", __func__);

	krb5_hdr = setup_token_v2(ctx, token);

	/* Set up the sequence number. Now 64-bits in clear
	 * text and w/o direction indicator */
	seq_send_be64 = cpu_to_be64(atomic64_fetch_inc(&ctx->seq_send64));
	स_नकल(krb5_hdr + 8, (अक्षर *) &seq_send_be64, 8);

	अगर (ctx->initiate) अणु
		cksumkey = ctx->initiator_sign;
		cksum_usage = KG_USAGE_INITIATOR_SIGN;
	पूर्ण अन्यथा अणु
		cksumkey = ctx->acceptor_sign;
		cksum_usage = KG_USAGE_ACCEPTOR_SIGN;
	पूर्ण

	अगर (make_checksum_v2(ctx, krb5_hdr, GSS_KRB5_TOK_HDR_LEN,
			     text, 0, cksumkey, cksum_usage, &cksumobj))
		वापस GSS_S_FAILURE;

	स_नकल(krb5_hdr + GSS_KRB5_TOK_HDR_LEN, cksumobj.data, cksumobj.len);

	now = kसमय_get_real_seconds();

	वापस (ctx->endसमय < now) ? GSS_S_CONTEXT_EXPIRED : GSS_S_COMPLETE;
पूर्ण

u32
gss_get_mic_kerberos(काष्ठा gss_ctx *gss_ctx, काष्ठा xdr_buf *text,
		     काष्ठा xdr_netobj *token)
अणु
	काष्ठा krb5_ctx		*ctx = gss_ctx->पूर्णांकernal_ctx_id;

	चयन (ctx->enctype) अणु
	शेष:
		BUG();
	हाल ENCTYPE_DES_CBC_RAW:
	हाल ENCTYPE_DES3_CBC_RAW:
		वापस gss_get_mic_v1(ctx, text, token);
	हाल ENCTYPE_AES128_CTS_HMAC_SHA1_96:
	हाल ENCTYPE_AES256_CTS_HMAC_SHA1_96:
		वापस gss_get_mic_v2(ctx, text, token);
	पूर्ण
पूर्ण
