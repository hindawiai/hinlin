<शैली गुरु>
/*
 * COPYRIGHT (c) 2008
 * The Regents of the University of Michigan
 * ALL RIGHTS RESERVED
 *
 * Permission is granted to use, copy, create derivative works
 * and redistribute this software and such derivative works
 * क्रम any purpose, so दीर्घ as the name of The University of
 * Michigan is not used in any advertising or खुलाity
 * pertaining to the use of distribution of this software
 * without specअगरic, written prior authorization.  If the
 * above copyright notice or any other identअगरication of the
 * University of Michigan is included in any copy of any
 * portion of this software, then the disclaimer below must
 * also be included.
 *
 * THIS SOFTWARE IS PROVIDED AS IS, WITHOUT REPRESENTATION
 * FROM THE UNIVERSITY OF MICHIGAN AS TO ITS FITNESS FOR ANY
 * PURPOSE, AND WITHOUT WARRANTY BY THE UNIVERSITY OF
 * MICHIGAN OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING
 * WITHOUT LIMITATION THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE
 * REGENTS OF THE UNIVERSITY OF MICHIGAN SHALL NOT BE LIABLE
 * FOR ANY DAMAGES, INCLUDING SPECIAL, INसूचीECT, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, WITH RESPECT TO ANY CLAIM ARISING
 * OUT OF OR IN CONNECTION WITH THE USE OF THE SOFTWARE, EVEN
 * IF IT HAS BEEN OR IS HEREAFTER ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGES.
 */

#समावेश <crypto/skcipher.h>
#समावेश <linux/types.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/sunrpc/gss_krb5.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/pagemap.h>

#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
# define RPCDBG_FACILITY	RPCDBG_AUTH
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक
gss_krb5_padding(पूर्णांक blocksize, पूर्णांक length)
अणु
	वापस blocksize - (length % blocksize);
पूर्ण

अटल अंतरभूत व्योम
gss_krb5_add_padding(काष्ठा xdr_buf *buf, पूर्णांक offset, पूर्णांक blocksize)
अणु
	पूर्णांक padding = gss_krb5_padding(blocksize, buf->len - offset);
	अक्षर *p;
	काष्ठा kvec *iov;

	अगर (buf->page_len || buf->tail[0].iov_len)
		iov = &buf->tail[0];
	अन्यथा
		iov = &buf->head[0];
	p = iov->iov_base + iov->iov_len;
	iov->iov_len += padding;
	buf->len += padding;
	स_रखो(p, padding, padding);
पूर्ण

अटल अंतरभूत पूर्णांक
gss_krb5_हटाओ_padding(काष्ठा xdr_buf *buf, पूर्णांक blocksize)
अणु
	u8 *ptr;
	u8 pad;
	माप_प्रकार len = buf->len;

	अगर (len <= buf->head[0].iov_len) अणु
		pad = *(u8 *)(buf->head[0].iov_base + len - 1);
		अगर (pad > buf->head[0].iov_len)
			वापस -EINVAL;
		buf->head[0].iov_len -= pad;
		जाओ out;
	पूर्ण अन्यथा
		len -= buf->head[0].iov_len;
	अगर (len <= buf->page_len) अणु
		अचिन्हित पूर्णांक last = (buf->page_base + len - 1)
					>>PAGE_SHIFT;
		अचिन्हित पूर्णांक offset = (buf->page_base + len - 1)
					& (PAGE_SIZE - 1);
		ptr = kmap_atomic(buf->pages[last]);
		pad = *(ptr + offset);
		kunmap_atomic(ptr);
		जाओ out;
	पूर्ण अन्यथा
		len -= buf->page_len;
	BUG_ON(len > buf->tail[0].iov_len);
	pad = *(u8 *)(buf->tail[0].iov_base + len - 1);
out:
	/* XXX: NOTE: we करो not adjust the page lengths--they represent
	 * a range of data in the real fileप्रणाली page cache, and we need
	 * to know that range so the xdr code can properly place पढ़ो data.
	 * However adjusting the head length, as we करो above, is harmless.
	 * In the हाल of a request that fits पूर्णांकo a single page, the server
	 * also uses length and head length together to determine the original
	 * start of the request to copy the request क्रम deferal; so it's
	 * easier on the server अगर we adjust head and tail length in tandem.
	 * It's not really a problem that we don't fool with the page and
	 * tail lengths, though--at worst badly क्रमmed xdr might lead the
	 * server to attempt to parse the padding.
	 * XXX: Document all these weird requirements क्रम gss mechanism
	 * wrap/unwrap functions. */
	अगर (pad > blocksize)
		वापस -EINVAL;
	अगर (buf->len > pad)
		buf->len -= pad;
	अन्यथा
		वापस -EINVAL;
	वापस 0;
पूर्ण

व्योम
gss_krb5_make_confounder(अक्षर *p, u32 conflen)
अणु
	अटल u64 i = 0;
	u64 *q = (u64 *)p;

	/* rfc1964 claims this should be "random".  But all that's really
	 * necessary is that it be unique.  And not even that is necessary in
	 * our हाल since our "gssapi" implementation exists only to support
	 * rpcsec_gss, so we know that the only buffers we will ever encrypt
	 * alपढ़ोy begin with a unique sequence number.  Just to hedge my bets
	 * I'll make a half-hearted attempt at something unique, but ensuring
	 * uniqueness would mean worrying about atomicity and rollover, and I
	 * करोn't care enough. */

	/* initialize to अक्रमom value */
	अगर (i == 0) अणु
		i = pअक्रमom_u32();
		i = (i << 32) | pअक्रमom_u32();
	पूर्ण

	चयन (conflen) अणु
	हाल 16:
		*q++ = i++;
		fallthrough;
	हाल 8:
		*q++ = i++;
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

/* Assumptions: the head and tail of inbuf are ours to play with.
 * The pages, however, may be real pages in the page cache and we replace
 * them with scratch pages from **pages beक्रमe writing to them. */
/* XXX: obviously the above should be करोcumentation of wrap पूर्णांकerface,
 * and shouldn't be in this kerberos-specअगरic file. */

/* XXX factor out common code with seal/unseal. */

अटल u32
gss_wrap_kerberos_v1(काष्ठा krb5_ctx *kctx, पूर्णांक offset,
		काष्ठा xdr_buf *buf, काष्ठा page **pages)
अणु
	अक्षर			cksumdata[GSS_KRB5_MAX_CKSUM_LEN];
	काष्ठा xdr_netobj	md5cksum = अणु.len = माप(cksumdata),
					    .data = cksumdataपूर्ण;
	पूर्णांक			blocksize = 0, plainlen;
	अचिन्हित अक्षर		*ptr, *msg_start;
	समय64_t		now;
	पूर्णांक			headlen;
	काष्ठा page		**पंचांगp_pages;
	u32			seq_send;
	u8			*cksumkey;
	u32			conflen = kctx->gk5e->conflen;

	dprपूर्णांकk("RPC:       %s\n", __func__);

	now = kसमय_get_real_seconds();

	blocksize = crypto_sync_skcipher_blocksize(kctx->enc);
	gss_krb5_add_padding(buf, offset, blocksize);
	BUG_ON((buf->len - offset) % blocksize);
	plainlen = conflen + buf->len - offset;

	headlen = g_token_size(&kctx->mech_used,
		GSS_KRB5_TOK_HDR_LEN + kctx->gk5e->cksumlength + plainlen) -
		(buf->len - offset);

	ptr = buf->head[0].iov_base + offset;
	/* shअगरt data to make room क्रम header. */
	xdr_extend_head(buf, offset, headlen);

	/* XXX Would be cleverer to encrypt जबतक copying. */
	BUG_ON((buf->len - offset - headlen) % blocksize);

	g_make_token_header(&kctx->mech_used,
				GSS_KRB5_TOK_HDR_LEN +
				kctx->gk5e->cksumlength + plainlen, &ptr);


	/* ptr now at header described in rfc 1964, section 1.2.1: */
	ptr[0] = (अचिन्हित अक्षर) ((KG_TOK_WRAP_MSG >> 8) & 0xff);
	ptr[1] = (अचिन्हित अक्षर) (KG_TOK_WRAP_MSG & 0xff);

	msg_start = ptr + GSS_KRB5_TOK_HDR_LEN + kctx->gk5e->cksumlength;

	/*
	 * संकेतg and sealalg are stored as अगर they were converted from LE
	 * to host endian, even though they're opaque pairs of bytes according
	 * to the RFC.
	 */
	*(__le16 *)(ptr + 2) = cpu_to_le16(kctx->gk5e->संकेतg);
	*(__le16 *)(ptr + 4) = cpu_to_le16(kctx->gk5e->sealalg);
	ptr[6] = 0xff;
	ptr[7] = 0xff;

	gss_krb5_make_confounder(msg_start, conflen);

	अगर (kctx->gk5e->keyed_cksum)
		cksumkey = kctx->cksum;
	अन्यथा
		cksumkey = शून्य;

	/* XXXJBF: UGH!: */
	पंचांगp_pages = buf->pages;
	buf->pages = pages;
	अगर (make_checksum(kctx, ptr, 8, buf, offset + headlen - conflen,
					cksumkey, KG_USAGE_SEAL, &md5cksum))
		वापस GSS_S_FAILURE;
	buf->pages = पंचांगp_pages;

	स_नकल(ptr + GSS_KRB5_TOK_HDR_LEN, md5cksum.data, md5cksum.len);

	seq_send = atomic_fetch_inc(&kctx->seq_send);

	/* XXX would probably be more efficient to compute checksum
	 * and encrypt at the same समय: */
	अगर ((krb5_make_seq_num(kctx, kctx->seq, kctx->initiate ? 0 : 0xff,
			       seq_send, ptr + GSS_KRB5_TOK_HDR_LEN, ptr + 8)))
		वापस GSS_S_FAILURE;

	अगर (gss_encrypt_xdr_buf(kctx->enc, buf,
				offset + headlen - conflen, pages))
		वापस GSS_S_FAILURE;

	वापस (kctx->endसमय < now) ? GSS_S_CONTEXT_EXPIRED : GSS_S_COMPLETE;
पूर्ण

अटल u32
gss_unwrap_kerberos_v1(काष्ठा krb5_ctx *kctx, पूर्णांक offset, पूर्णांक len,
		       काष्ठा xdr_buf *buf, अचिन्हित पूर्णांक *slack,
		       अचिन्हित पूर्णांक *align)
अणु
	पूर्णांक			संकेतg;
	पूर्णांक			sealalg;
	अक्षर			cksumdata[GSS_KRB5_MAX_CKSUM_LEN];
	काष्ठा xdr_netobj	md5cksum = अणु.len = माप(cksumdata),
					    .data = cksumdataपूर्ण;
	समय64_t		now;
	पूर्णांक			direction;
	s32			seqnum;
	अचिन्हित अक्षर		*ptr;
	पूर्णांक			bodysize;
	व्योम			*data_start, *orig_start;
	पूर्णांक			data_len;
	पूर्णांक			blocksize;
	u32			conflen = kctx->gk5e->conflen;
	पूर्णांक			crypt_offset;
	u8			*cksumkey;
	अचिन्हित पूर्णांक		saved_len = buf->len;

	dprपूर्णांकk("RPC:       gss_unwrap_kerberos\n");

	ptr = (u8 *)buf->head[0].iov_base + offset;
	अगर (g_verअगरy_token_header(&kctx->mech_used, &bodysize, &ptr,
					len - offset))
		वापस GSS_S_DEFECTIVE_TOKEN;

	अगर ((ptr[0] != ((KG_TOK_WRAP_MSG >> 8) & 0xff)) ||
	    (ptr[1] !=  (KG_TOK_WRAP_MSG & 0xff)))
		वापस GSS_S_DEFECTIVE_TOKEN;

	/* XXX sanity-check bodysize?? */

	/* get the sign and seal algorithms */

	संकेतg = ptr[2] + (ptr[3] << 8);
	अगर (संकेतg != kctx->gk5e->संकेतg)
		वापस GSS_S_DEFECTIVE_TOKEN;

	sealalg = ptr[4] + (ptr[5] << 8);
	अगर (sealalg != kctx->gk5e->sealalg)
		वापस GSS_S_DEFECTIVE_TOKEN;

	अगर ((ptr[6] != 0xff) || (ptr[7] != 0xff))
		वापस GSS_S_DEFECTIVE_TOKEN;

	/*
	 * Data starts after token header and checksum.  ptr poपूर्णांकs
	 * to the beginning of the token header
	 */
	crypt_offset = ptr + (GSS_KRB5_TOK_HDR_LEN + kctx->gk5e->cksumlength) -
					(अचिन्हित अक्षर *)buf->head[0].iov_base;

	buf->len = len;
	अगर (gss_decrypt_xdr_buf(kctx->enc, buf, crypt_offset))
		वापस GSS_S_DEFECTIVE_TOKEN;

	अगर (kctx->gk5e->keyed_cksum)
		cksumkey = kctx->cksum;
	अन्यथा
		cksumkey = शून्य;

	अगर (make_checksum(kctx, ptr, 8, buf, crypt_offset,
					cksumkey, KG_USAGE_SEAL, &md5cksum))
		वापस GSS_S_FAILURE;

	अगर (स_भेद(md5cksum.data, ptr + GSS_KRB5_TOK_HDR_LEN,
						kctx->gk5e->cksumlength))
		वापस GSS_S_BAD_SIG;

	/* it got through unscathed.  Make sure the context is unexpired */

	now = kसमय_get_real_seconds();

	अगर (now > kctx->endसमय)
		वापस GSS_S_CONTEXT_EXPIRED;

	/* करो sequencing checks */

	अगर (krb5_get_seq_num(kctx, ptr + GSS_KRB5_TOK_HDR_LEN,
			     ptr + 8, &direction, &seqnum))
		वापस GSS_S_BAD_SIG;

	अगर ((kctx->initiate && direction != 0xff) ||
	    (!kctx->initiate && direction != 0))
		वापस GSS_S_BAD_SIG;

	/* Copy the data back to the right position.  XXX: Would probably be
	 * better to copy and encrypt at the same समय. */

	blocksize = crypto_sync_skcipher_blocksize(kctx->enc);
	data_start = ptr + (GSS_KRB5_TOK_HDR_LEN + kctx->gk5e->cksumlength) +
					conflen;
	orig_start = buf->head[0].iov_base + offset;
	data_len = (buf->head[0].iov_base + buf->head[0].iov_len) - data_start;
	स_हटाओ(orig_start, data_start, data_len);
	buf->head[0].iov_len -= (data_start - orig_start);
	buf->len = len - (data_start - orig_start);

	अगर (gss_krb5_हटाओ_padding(buf, blocksize))
		वापस GSS_S_DEFECTIVE_TOKEN;

	/* slack must include room क्रम krb5 padding */
	*slack = XDR_QUADLEN(saved_len - buf->len);
	/* The GSS blob always precedes the RPC message payload */
	*align = *slack;
	वापस GSS_S_COMPLETE;
पूर्ण

/*
 * We can shअगरt data by up to LOCAL_BUF_LEN bytes in a pass.  If we need
 * to करो more than that, we shअगरt repeatedly.  Kevin Coffman reports
 * seeing 28 bytes as the value used by Microsoft clients and servers
 * with AES, so this स्थिरant is chosen to allow handling 28 in one pass
 * without using too much stack space.
 *
 * If that proves to a problem perhaps we could use a more clever
 * algorithm.
 */
#घोषणा LOCAL_BUF_LEN 32u

अटल व्योम rotate_buf_a_little(काष्ठा xdr_buf *buf, अचिन्हित पूर्णांक shअगरt)
अणु
	अक्षर head[LOCAL_BUF_LEN];
	अक्षर पंचांगp[LOCAL_BUF_LEN];
	अचिन्हित पूर्णांक this_len, i;

	BUG_ON(shअगरt > LOCAL_BUF_LEN);

	पढ़ो_bytes_from_xdr_buf(buf, 0, head, shअगरt);
	क्रम (i = 0; i + shअगरt < buf->len; i += LOCAL_BUF_LEN) अणु
		this_len = min(LOCAL_BUF_LEN, buf->len - (i + shअगरt));
		पढ़ो_bytes_from_xdr_buf(buf, i+shअगरt, पंचांगp, this_len);
		ग_लिखो_bytes_to_xdr_buf(buf, i, पंचांगp, this_len);
	पूर्ण
	ग_लिखो_bytes_to_xdr_buf(buf, buf->len - shअगरt, head, shअगरt);
पूर्ण

अटल व्योम _rotate_left(काष्ठा xdr_buf *buf, अचिन्हित पूर्णांक shअगरt)
अणु
	पूर्णांक shअगरted = 0;
	पूर्णांक this_shअगरt;

	shअगरt %= buf->len;
	जबतक (shअगरted < shअगरt) अणु
		this_shअगरt = min(shअगरt - shअगरted, LOCAL_BUF_LEN);
		rotate_buf_a_little(buf, this_shअगरt);
		shअगरted += this_shअगरt;
	पूर्ण
पूर्ण

अटल व्योम rotate_left(u32 base, काष्ठा xdr_buf *buf, अचिन्हित पूर्णांक shअगरt)
अणु
	काष्ठा xdr_buf subbuf;

	xdr_buf_subsegment(buf, &subbuf, base, buf->len - base);
	_rotate_left(&subbuf, shअगरt);
पूर्ण

अटल u32
gss_wrap_kerberos_v2(काष्ठा krb5_ctx *kctx, u32 offset,
		     काष्ठा xdr_buf *buf, काष्ठा page **pages)
अणु
	u8		*ptr, *plainhdr;
	समय64_t	now;
	u8		flags = 0x00;
	__be16		*be16ptr;
	__be64		*be64ptr;
	u32		err;

	dprपूर्णांकk("RPC:       %s\n", __func__);

	अगर (kctx->gk5e->encrypt_v2 == शून्य)
		वापस GSS_S_FAILURE;

	/* make room क्रम gss token header */
	अगर (xdr_extend_head(buf, offset, GSS_KRB5_TOK_HDR_LEN))
		वापस GSS_S_FAILURE;

	/* स्थिरruct gss token header */
	ptr = plainhdr = buf->head[0].iov_base + offset;
	*ptr++ = (अचिन्हित अक्षर) ((KG2_TOK_WRAP>>8) & 0xff);
	*ptr++ = (अचिन्हित अक्षर) (KG2_TOK_WRAP & 0xff);

	अगर ((kctx->flags & KRB5_CTX_FLAG_INITIATOR) == 0)
		flags |= KG2_TOKEN_FLAG_SENTBYACCEPTOR;
	अगर ((kctx->flags & KRB5_CTX_FLAG_ACCEPTOR_SUBKEY) != 0)
		flags |= KG2_TOKEN_FLAG_ACCEPTORSUBKEY;
	/* We always करो confidentiality in wrap tokens */
	flags |= KG2_TOKEN_FLAG_SEALED;

	*ptr++ = flags;
	*ptr++ = 0xff;
	be16ptr = (__be16 *)ptr;

	*be16ptr++ = 0;
	/* "inner" token header always uses 0 क्रम RRC */
	*be16ptr++ = 0;

	be64ptr = (__be64 *)be16ptr;
	*be64ptr = cpu_to_be64(atomic64_fetch_inc(&kctx->seq_send64));

	err = (*kctx->gk5e->encrypt_v2)(kctx, offset, buf, pages);
	अगर (err)
		वापस err;

	now = kसमय_get_real_seconds();
	वापस (kctx->endसमय < now) ? GSS_S_CONTEXT_EXPIRED : GSS_S_COMPLETE;
पूर्ण

अटल u32
gss_unwrap_kerberos_v2(काष्ठा krb5_ctx *kctx, पूर्णांक offset, पूर्णांक len,
		       काष्ठा xdr_buf *buf, अचिन्हित पूर्णांक *slack,
		       अचिन्हित पूर्णांक *align)
अणु
	समय64_t	now;
	u8		*ptr;
	u8		flags = 0x00;
	u16		ec, rrc;
	पूर्णांक		err;
	u32		headskip, tailskip;
	u8		decrypted_hdr[GSS_KRB5_TOK_HDR_LEN];
	अचिन्हित पूर्णांक	movelen;


	dprपूर्णांकk("RPC:       %s\n", __func__);

	अगर (kctx->gk5e->decrypt_v2 == शून्य)
		वापस GSS_S_FAILURE;

	ptr = buf->head[0].iov_base + offset;

	अगर (be16_to_cpu(*((__be16 *)ptr)) != KG2_TOK_WRAP)
		वापस GSS_S_DEFECTIVE_TOKEN;

	flags = ptr[2];
	अगर ((!kctx->initiate && (flags & KG2_TOKEN_FLAG_SENTBYACCEPTOR)) ||
	    (kctx->initiate && !(flags & KG2_TOKEN_FLAG_SENTBYACCEPTOR)))
		वापस GSS_S_BAD_SIG;

	अगर ((flags & KG2_TOKEN_FLAG_SEALED) == 0) अणु
		dprपूर्णांकk("%s: token missing expected sealed flag\n", __func__);
		वापस GSS_S_DEFECTIVE_TOKEN;
	पूर्ण

	अगर (ptr[3] != 0xff)
		वापस GSS_S_DEFECTIVE_TOKEN;

	ec = be16_to_cpup((__be16 *)(ptr + 4));
	rrc = be16_to_cpup((__be16 *)(ptr + 6));

	/*
	 * NOTE: the sequence number at ptr + 8 is skipped, rpcsec_gss
	 * करोesn't want it checked; see page 6 of rfc 2203.
	 */

	अगर (rrc != 0)
		rotate_left(offset + 16, buf, rrc);

	err = (*kctx->gk5e->decrypt_v2)(kctx, offset, len, buf,
					&headskip, &tailskip);
	अगर (err)
		वापस GSS_S_FAILURE;

	/*
	 * Retrieve the decrypted gss token header and verअगरy
	 * it against the original
	 */
	err = पढ़ो_bytes_from_xdr_buf(buf,
				len - GSS_KRB5_TOK_HDR_LEN - tailskip,
				decrypted_hdr, GSS_KRB5_TOK_HDR_LEN);
	अगर (err) अणु
		dprपूर्णांकk("%s: error %u getting decrypted_hdr\n", __func__, err);
		वापस GSS_S_FAILURE;
	पूर्ण
	अगर (स_भेद(ptr, decrypted_hdr, 6)
				|| स_भेद(ptr + 8, decrypted_hdr + 8, 8)) अणु
		dprपूर्णांकk("%s: token hdr, plaintext hdr mismatch!\n", __func__);
		वापस GSS_S_FAILURE;
	पूर्ण

	/* करो sequencing checks */

	/* it got through unscathed.  Make sure the context is unexpired */
	now = kसमय_get_real_seconds();
	अगर (now > kctx->endसमय)
		वापस GSS_S_CONTEXT_EXPIRED;

	/*
	 * Move the head data back to the right position in xdr_buf.
	 * We ignore any "ec" data since it might be in the head or
	 * the tail, and we really करोn't need to deal with it.
	 * Note that buf->head[0].iov_len may indicate the available
	 * head buffer space rather than that actually occupied.
	 */
	movelen = min_t(अचिन्हित पूर्णांक, buf->head[0].iov_len, len);
	movelen -= offset + GSS_KRB5_TOK_HDR_LEN + headskip;
	BUG_ON(offset + GSS_KRB5_TOK_HDR_LEN + headskip + movelen >
							buf->head[0].iov_len);
	स_हटाओ(ptr, ptr + GSS_KRB5_TOK_HDR_LEN + headskip, movelen);
	buf->head[0].iov_len -= GSS_KRB5_TOK_HDR_LEN + headskip;
	buf->len = len - (GSS_KRB5_TOK_HDR_LEN + headskip);

	/* Trim off the trailing "extra count" and checksum blob */
	xdr_buf_trim(buf, ec + GSS_KRB5_TOK_HDR_LEN + tailskip);

	*align = XDR_QUADLEN(GSS_KRB5_TOK_HDR_LEN + headskip);
	*slack = *align + XDR_QUADLEN(ec + GSS_KRB5_TOK_HDR_LEN + tailskip);
	वापस GSS_S_COMPLETE;
पूर्ण

u32
gss_wrap_kerberos(काष्ठा gss_ctx *gctx, पूर्णांक offset,
		  काष्ठा xdr_buf *buf, काष्ठा page **pages)
अणु
	काष्ठा krb5_ctx	*kctx = gctx->पूर्णांकernal_ctx_id;

	चयन (kctx->enctype) अणु
	शेष:
		BUG();
	हाल ENCTYPE_DES_CBC_RAW:
	हाल ENCTYPE_DES3_CBC_RAW:
		वापस gss_wrap_kerberos_v1(kctx, offset, buf, pages);
	हाल ENCTYPE_AES128_CTS_HMAC_SHA1_96:
	हाल ENCTYPE_AES256_CTS_HMAC_SHA1_96:
		वापस gss_wrap_kerberos_v2(kctx, offset, buf, pages);
	पूर्ण
पूर्ण

u32
gss_unwrap_kerberos(काष्ठा gss_ctx *gctx, पूर्णांक offset,
		    पूर्णांक len, काष्ठा xdr_buf *buf)
अणु
	काष्ठा krb5_ctx	*kctx = gctx->पूर्णांकernal_ctx_id;

	चयन (kctx->enctype) अणु
	शेष:
		BUG();
	हाल ENCTYPE_DES_CBC_RAW:
	हाल ENCTYPE_DES3_CBC_RAW:
		वापस gss_unwrap_kerberos_v1(kctx, offset, len, buf,
					      &gctx->slack, &gctx->align);
	हाल ENCTYPE_AES128_CTS_HMAC_SHA1_96:
	हाल ENCTYPE_AES256_CTS_HMAC_SHA1_96:
		वापस gss_unwrap_kerberos_v2(kctx, offset, len, buf,
					      &gctx->slack, &gctx->align);
	पूर्ण
पूर्ण
