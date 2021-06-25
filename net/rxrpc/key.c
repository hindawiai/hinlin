<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* RxRPC key management
 *
 * Copyright (C) 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 *
 * RxRPC keys should have a description of describing their purpose:
 *	"afs@example.com"
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <crypto/skcipher.h>
#समावेश <linux/module.h>
#समावेश <linux/net.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/key-type.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/slab.h>
#समावेश <net/sock.h>
#समावेश <net/af_rxrpc.h>
#समावेश <keys/rxrpc-type.h>
#समावेश <keys/user-type.h>
#समावेश "ar-internal.h"

अटल पूर्णांक rxrpc_preparse(काष्ठा key_preparsed_payload *);
अटल व्योम rxrpc_मुक्त_preparse(काष्ठा key_preparsed_payload *);
अटल व्योम rxrpc_destroy(काष्ठा key *);
अटल व्योम rxrpc_describe(स्थिर काष्ठा key *, काष्ठा seq_file *);
अटल दीर्घ rxrpc_पढ़ो(स्थिर काष्ठा key *, अक्षर *, माप_प्रकार);

/*
 * rxrpc defined keys take an arbitrary string as the description and an
 * arbitrary blob of data as the payload
 */
काष्ठा key_type key_type_rxrpc = अणु
	.name		= "rxrpc",
	.flags		= KEY_TYPE_NET_DOMAIN,
	.preparse	= rxrpc_preparse,
	.मुक्त_preparse	= rxrpc_मुक्त_preparse,
	.instantiate	= generic_key_instantiate,
	.destroy	= rxrpc_destroy,
	.describe	= rxrpc_describe,
	.पढ़ो		= rxrpc_पढ़ो,
पूर्ण;
EXPORT_SYMBOL(key_type_rxrpc);

/*
 * parse an RxKAD type XDR क्रमmat token
 * - the caller guarantees we have at least 4 words
 */
अटल पूर्णांक rxrpc_preparse_xdr_rxkad(काष्ठा key_preparsed_payload *prep,
				    माप_प्रकार datalen,
				    स्थिर __be32 *xdr, अचिन्हित पूर्णांक toklen)
अणु
	काष्ठा rxrpc_key_token *token, **pptoken;
	समय64_t expiry;
	माप_प्रकार plen;
	u32 tktlen;

	_enter(",{%x,%x,%x,%x},%u",
	       ntohl(xdr[0]), ntohl(xdr[1]), ntohl(xdr[2]), ntohl(xdr[3]),
	       toklen);

	अगर (toklen <= 8 * 4)
		वापस -EKEYREJECTED;
	tktlen = ntohl(xdr[7]);
	_debug("tktlen: %x", tktlen);
	अगर (tktlen > AFSTOKEN_RK_TIX_MAX)
		वापस -EKEYREJECTED;
	अगर (toklen < 8 * 4 + tktlen)
		वापस -EKEYREJECTED;

	plen = माप(*token) + माप(*token->kad) + tktlen;
	prep->quotalen = datalen + plen;

	plen -= माप(*token);
	token = kzalloc(माप(*token), GFP_KERNEL);
	अगर (!token)
		वापस -ENOMEM;

	token->kad = kzalloc(plen, GFP_KERNEL);
	अगर (!token->kad) अणु
		kमुक्त(token);
		वापस -ENOMEM;
	पूर्ण

	token->security_index	= RXRPC_SECURITY_RXKAD;
	token->kad->ticket_len	= tktlen;
	token->kad->vice_id	= ntohl(xdr[0]);
	token->kad->kvno	= ntohl(xdr[1]);
	token->kad->start	= ntohl(xdr[4]);
	token->kad->expiry	= ntohl(xdr[5]);
	token->kad->primary_flag = ntohl(xdr[6]);
	स_नकल(&token->kad->session_key, &xdr[2], 8);
	स_नकल(&token->kad->ticket, &xdr[8], tktlen);

	_debug("SCIX: %u", token->security_index);
	_debug("TLEN: %u", token->kad->ticket_len);
	_debug("EXPY: %x", token->kad->expiry);
	_debug("KVNO: %u", token->kad->kvno);
	_debug("PRIM: %u", token->kad->primary_flag);
	_debug("SKEY: %02x%02x%02x%02x%02x%02x%02x%02x",
	       token->kad->session_key[0], token->kad->session_key[1],
	       token->kad->session_key[2], token->kad->session_key[3],
	       token->kad->session_key[4], token->kad->session_key[5],
	       token->kad->session_key[6], token->kad->session_key[7]);
	अगर (token->kad->ticket_len >= 8)
		_debug("TCKT: %02x%02x%02x%02x%02x%02x%02x%02x",
		       token->kad->ticket[0], token->kad->ticket[1],
		       token->kad->ticket[2], token->kad->ticket[3],
		       token->kad->ticket[4], token->kad->ticket[5],
		       token->kad->ticket[6], token->kad->ticket[7]);

	/* count the number of tokens attached */
	prep->payload.data[1] = (व्योम *)((अचिन्हित दीर्घ)prep->payload.data[1] + 1);

	/* attach the data */
	क्रम (pptoken = (काष्ठा rxrpc_key_token **)&prep->payload.data[0];
	     *pptoken;
	     pptoken = &(*pptoken)->next)
		जारी;
	*pptoken = token;
	expiry = rxrpc_u32_to_समय64(token->kad->expiry);
	अगर (expiry < prep->expiry)
		prep->expiry = expiry;

	_leave(" = 0");
	वापस 0;
पूर्ण

/*
 * attempt to parse the data as the XDR क्रमmat
 * - the caller guarantees we have more than 7 words
 */
अटल पूर्णांक rxrpc_preparse_xdr(काष्ठा key_preparsed_payload *prep)
अणु
	स्थिर __be32 *xdr = prep->data, *token, *p;
	स्थिर अक्षर *cp;
	अचिन्हित पूर्णांक len, paddedlen, loop, ntoken, toklen, sec_ix;
	माप_प्रकार datalen = prep->datalen;
	पूर्णांक ret, ret2;

	_enter(",{%x,%x,%x,%x},%zu",
	       ntohl(xdr[0]), ntohl(xdr[1]), ntohl(xdr[2]), ntohl(xdr[3]),
	       prep->datalen);

	अगर (datalen > AFSTOKEN_LENGTH_MAX)
		जाओ not_xdr;

	/* XDR is an array of __be32's */
	अगर (datalen & 3)
		जाओ not_xdr;

	/* the flags should be 0 (the setpag bit must be handled by
	 * userspace) */
	अगर (ntohl(*xdr++) != 0)
		जाओ not_xdr;
	datalen -= 4;

	/* check the cell name */
	len = ntohl(*xdr++);
	अगर (len < 1 || len > AFSTOKEN_CELL_MAX)
		जाओ not_xdr;
	datalen -= 4;
	paddedlen = (len + 3) & ~3;
	अगर (paddedlen > datalen)
		जाओ not_xdr;

	cp = (स्थिर अक्षर *) xdr;
	क्रम (loop = 0; loop < len; loop++)
		अगर (!है_छाप(cp[loop]))
			जाओ not_xdr;
	क्रम (; loop < paddedlen; loop++)
		अगर (cp[loop])
			जाओ not_xdr;
	_debug("cellname: [%u/%u] '%*.*s'",
	       len, paddedlen, len, len, (स्थिर अक्षर *) xdr);
	datalen -= paddedlen;
	xdr += paddedlen >> 2;

	/* get the token count */
	अगर (datalen < 12)
		जाओ not_xdr;
	ntoken = ntohl(*xdr++);
	datalen -= 4;
	_debug("ntoken: %x", ntoken);
	अगर (ntoken < 1 || ntoken > AFSTOKEN_MAX)
		जाओ not_xdr;

	/* check each token wrapper */
	p = xdr;
	loop = ntoken;
	करो अणु
		अगर (datalen < 8)
			जाओ not_xdr;
		toklen = ntohl(*p++);
		sec_ix = ntohl(*p);
		datalen -= 4;
		_debug("token: [%x/%zx] %x", toklen, datalen, sec_ix);
		paddedlen = (toklen + 3) & ~3;
		अगर (toklen < 20 || toklen > datalen || paddedlen > datalen)
			जाओ not_xdr;
		datalen -= paddedlen;
		p += paddedlen >> 2;

	पूर्ण जबतक (--loop > 0);

	_debug("remainder: %zu", datalen);
	अगर (datalen != 0)
		जाओ not_xdr;

	/* okay: we're going to assume it's valid XDR क्रमmat
	 * - we ignore the cellname, relying on the key to be correctly named
	 */
	ret = -EPROTONOSUPPORT;
	करो अणु
		toklen = ntohl(*xdr++);
		token = xdr;
		xdr += (toklen + 3) / 4;

		sec_ix = ntohl(*token++);
		toklen -= 4;

		_debug("TOKEN type=%x len=%x", sec_ix, toklen);

		चयन (sec_ix) अणु
		हाल RXRPC_SECURITY_RXKAD:
			ret2 = rxrpc_preparse_xdr_rxkad(prep, datalen, token, toklen);
			अवरोध;
		शेष:
			ret2 = -EPROTONOSUPPORT;
			अवरोध;
		पूर्ण

		चयन (ret2) अणु
		हाल 0:
			ret = 0;
			अवरोध;
		हाल -EPROTONOSUPPORT:
			अवरोध;
		हाल -ENOPKG:
			अगर (ret != 0)
				ret = -ENOPKG;
			अवरोध;
		शेष:
			ret = ret2;
			जाओ error;
		पूर्ण

	पूर्ण जबतक (--ntoken > 0);

error:
	_leave(" = %d", ret);
	वापस ret;

not_xdr:
	_leave(" = -EPROTO");
	वापस -EPROTO;
पूर्ण

/*
 * Preparse an rxrpc defined key.
 *
 * Data should be of the क्रमm:
 *	OFFSET	LEN	CONTENT
 *	0	4	key पूर्णांकerface version number
 *	4	2	security index (type)
 *	6	2	ticket length
 *	8	4	key expiry समय (समय_प्रकार)
 *	12	4	kvno
 *	16	8	session key
 *	24	[len]	ticket
 *
 * अगर no data is provided, then a no-security key is made
 */
अटल पूर्णांक rxrpc_preparse(काष्ठा key_preparsed_payload *prep)
अणु
	स्थिर काष्ठा rxrpc_key_data_v1 *v1;
	काष्ठा rxrpc_key_token *token, **pp;
	समय64_t expiry;
	माप_प्रकार plen;
	u32 kver;
	पूर्णांक ret;

	_enter("%zu", prep->datalen);

	/* handle a no-security key */
	अगर (!prep->data && prep->datalen == 0)
		वापस 0;

	/* determine अगर the XDR payload क्रमmat is being used */
	अगर (prep->datalen > 7 * 4) अणु
		ret = rxrpc_preparse_xdr(prep);
		अगर (ret != -EPROTO)
			वापस ret;
	पूर्ण

	/* get the key पूर्णांकerface version number */
	ret = -EINVAL;
	अगर (prep->datalen <= 4 || !prep->data)
		जाओ error;
	स_नकल(&kver, prep->data, माप(kver));
	prep->data += माप(kver);
	prep->datalen -= माप(kver);

	_debug("KEY I/F VERSION: %u", kver);

	ret = -EKEYREJECTED;
	अगर (kver != 1)
		जाओ error;

	/* deal with a version 1 key */
	ret = -EINVAL;
	अगर (prep->datalen < माप(*v1))
		जाओ error;

	v1 = prep->data;
	अगर (prep->datalen != माप(*v1) + v1->ticket_length)
		जाओ error;

	_debug("SCIX: %u", v1->security_index);
	_debug("TLEN: %u", v1->ticket_length);
	_debug("EXPY: %x", v1->expiry);
	_debug("KVNO: %u", v1->kvno);
	_debug("SKEY: %02x%02x%02x%02x%02x%02x%02x%02x",
	       v1->session_key[0], v1->session_key[1],
	       v1->session_key[2], v1->session_key[3],
	       v1->session_key[4], v1->session_key[5],
	       v1->session_key[6], v1->session_key[7]);
	अगर (v1->ticket_length >= 8)
		_debug("TCKT: %02x%02x%02x%02x%02x%02x%02x%02x",
		       v1->ticket[0], v1->ticket[1],
		       v1->ticket[2], v1->ticket[3],
		       v1->ticket[4], v1->ticket[5],
		       v1->ticket[6], v1->ticket[7]);

	ret = -EPROTONOSUPPORT;
	अगर (v1->security_index != RXRPC_SECURITY_RXKAD)
		जाओ error;

	plen = माप(*token->kad) + v1->ticket_length;
	prep->quotalen = plen + माप(*token);

	ret = -ENOMEM;
	token = kzalloc(माप(*token), GFP_KERNEL);
	अगर (!token)
		जाओ error;
	token->kad = kzalloc(plen, GFP_KERNEL);
	अगर (!token->kad)
		जाओ error_मुक्त;

	token->security_index		= RXRPC_SECURITY_RXKAD;
	token->kad->ticket_len		= v1->ticket_length;
	token->kad->expiry		= v1->expiry;
	token->kad->kvno		= v1->kvno;
	स_नकल(&token->kad->session_key, &v1->session_key, 8);
	स_नकल(&token->kad->ticket, v1->ticket, v1->ticket_length);

	/* count the number of tokens attached */
	prep->payload.data[1] = (व्योम *)((अचिन्हित दीर्घ)prep->payload.data[1] + 1);

	/* attach the data */
	pp = (काष्ठा rxrpc_key_token **)&prep->payload.data[0];
	जबतक (*pp)
		pp = &(*pp)->next;
	*pp = token;
	expiry = rxrpc_u32_to_समय64(token->kad->expiry);
	अगर (expiry < prep->expiry)
		prep->expiry = expiry;
	token = शून्य;
	ret = 0;

error_मुक्त:
	kमुक्त(token);
error:
	वापस ret;
पूर्ण

/*
 * Free token list.
 */
अटल व्योम rxrpc_मुक्त_token_list(काष्ठा rxrpc_key_token *token)
अणु
	काष्ठा rxrpc_key_token *next;

	क्रम (; token; token = next) अणु
		next = token->next;
		चयन (token->security_index) अणु
		हाल RXRPC_SECURITY_RXKAD:
			kमुक्त(token->kad);
			अवरोध;
		शेष:
			pr_err("Unknown token type %x on rxrpc key\n",
			       token->security_index);
			BUG();
		पूर्ण

		kमुक्त(token);
	पूर्ण
पूर्ण

/*
 * Clean up preparse data.
 */
अटल व्योम rxrpc_मुक्त_preparse(काष्ठा key_preparsed_payload *prep)
अणु
	rxrpc_मुक्त_token_list(prep->payload.data[0]);
पूर्ण

/*
 * dispose of the data dangling from the corpse of a rxrpc key
 */
अटल व्योम rxrpc_destroy(काष्ठा key *key)
अणु
	rxrpc_मुक्त_token_list(key->payload.data[0]);
पूर्ण

/*
 * describe the rxrpc key
 */
अटल व्योम rxrpc_describe(स्थिर काष्ठा key *key, काष्ठा seq_file *m)
अणु
	स्थिर काष्ठा rxrpc_key_token *token;
	स्थिर अक्षर *sep = ": ";

	seq_माला_दो(m, key->description);

	क्रम (token = key->payload.data[0]; token; token = token->next) अणु
		seq_माला_दो(m, sep);

		चयन (token->security_index) अणु
		हाल RXRPC_SECURITY_RXKAD:
			seq_माला_दो(m, "ka");
			अवरोध;
		शेष: /* we have a ticket we can't encode */
			seq_म_लिखो(m, "%u", token->security_index);
			अवरोध;
		पूर्ण

		sep = " ";
	पूर्ण
पूर्ण

/*
 * grab the security key क्रम a socket
 */
पूर्णांक rxrpc_request_key(काष्ठा rxrpc_sock *rx, sockptr_t optval, पूर्णांक optlen)
अणु
	काष्ठा key *key;
	अक्षर *description;

	_enter("");

	अगर (optlen <= 0 || optlen > PAGE_SIZE - 1 || rx->securities)
		वापस -EINVAL;

	description = memdup_sockptr_nul(optval, optlen);
	अगर (IS_ERR(description))
		वापस PTR_ERR(description);

	key = request_key_net(&key_type_rxrpc, description, sock_net(&rx->sk), शून्य);
	अगर (IS_ERR(key)) अणु
		kमुक्त(description);
		_leave(" = %ld", PTR_ERR(key));
		वापस PTR_ERR(key);
	पूर्ण

	rx->key = key;
	kमुक्त(description);
	_leave(" = 0 [key %x]", key->serial);
	वापस 0;
पूर्ण

/*
 * generate a server data key
 */
पूर्णांक rxrpc_get_server_data_key(काष्ठा rxrpc_connection *conn,
			      स्थिर व्योम *session_key,
			      समय64_t expiry,
			      u32 kvno)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	काष्ठा key *key;
	पूर्णांक ret;

	काष्ठा अणु
		u32 kver;
		काष्ठा rxrpc_key_data_v1 v1;
	पूर्ण data;

	_enter("");

	key = key_alloc(&key_type_rxrpc, "x",
			GLOBAL_ROOT_UID, GLOBAL_ROOT_GID, cred, 0,
			KEY_ALLOC_NOT_IN_QUOTA, शून्य);
	अगर (IS_ERR(key)) अणु
		_leave(" = -ENOMEM [alloc %ld]", PTR_ERR(key));
		वापस -ENOMEM;
	पूर्ण

	_debug("key %d", key_serial(key));

	data.kver = 1;
	data.v1.security_index = RXRPC_SECURITY_RXKAD;
	data.v1.ticket_length = 0;
	data.v1.expiry = rxrpc_समय64_to_u32(expiry);
	data.v1.kvno = 0;

	स_नकल(&data.v1.session_key, session_key, माप(data.v1.session_key));

	ret = key_instantiate_and_link(key, &data, माप(data), शून्य, शून्य);
	अगर (ret < 0)
		जाओ error;

	conn->params.key = key;
	_leave(" = 0 [%d]", key_serial(key));
	वापस 0;

error:
	key_revoke(key);
	key_put(key);
	_leave(" = -ENOMEM [ins %d]", ret);
	वापस -ENOMEM;
पूर्ण
EXPORT_SYMBOL(rxrpc_get_server_data_key);

/**
 * rxrpc_get_null_key - Generate a null RxRPC key
 * @keyname: The name to give the key.
 *
 * Generate a null RxRPC key that can be used to indicate anonymous security is
 * required क्रम a particular करोमुख्य.
 */
काष्ठा key *rxrpc_get_null_key(स्थिर अक्षर *keyname)
अणु
	स्थिर काष्ठा cred *cred = current_cred();
	काष्ठा key *key;
	पूर्णांक ret;

	key = key_alloc(&key_type_rxrpc, keyname,
			GLOBAL_ROOT_UID, GLOBAL_ROOT_GID, cred,
			KEY_POS_SEARCH, KEY_ALLOC_NOT_IN_QUOTA, शून्य);
	अगर (IS_ERR(key))
		वापस key;

	ret = key_instantiate_and_link(key, शून्य, 0, शून्य, शून्य);
	अगर (ret < 0) अणु
		key_revoke(key);
		key_put(key);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस key;
पूर्ण
EXPORT_SYMBOL(rxrpc_get_null_key);

/*
 * पढ़ो the contents of an rxrpc key
 * - this वापसs the result in XDR क्रमm
 */
अटल दीर्घ rxrpc_पढ़ो(स्थिर काष्ठा key *key,
		       अक्षर *buffer, माप_प्रकार buflen)
अणु
	स्थिर काष्ठा rxrpc_key_token *token;
	माप_प्रकार size;
	__be32 *xdr, *oldxdr;
	u32 cnlen, toksize, ntoks, tok, zero;
	u16 toksizes[AFSTOKEN_MAX];

	_enter("");

	/* we करोn't know what क्रमm we should वापस non-AFS keys in */
	अगर (स_भेद(key->description, "afs@", 4) != 0)
		वापस -EOPNOTSUPP;
	cnlen = म_माप(key->description + 4);

#घोषणा RND(X) (((X) + 3) & ~3)

	/* AFS keys we वापस in XDR क्रमm, so we need to work out the size of
	 * the XDR */
	size = 2 * 4;	/* flags, cellname len */
	size += RND(cnlen);	/* cellname */
	size += 1 * 4;	/* token count */

	ntoks = 0;
	क्रम (token = key->payload.data[0]; token; token = token->next) अणु
		toksize = 4;	/* sec index */

		चयन (token->security_index) अणु
		हाल RXRPC_SECURITY_RXKAD:
			toksize += 8 * 4;	/* viceid, kvno, key*2, begin,
						 * end, primary, tktlen */
			अगर (!token->no_leak_key)
				toksize += RND(token->kad->ticket_len);
			अवरोध;

		शेष: /* we have a ticket we can't encode */
			pr_err("Unsupported key token type (%u)\n",
			       token->security_index);
			वापस -ENOPKG;
		पूर्ण

		_debug("token[%u]: toksize=%u", ntoks, toksize);
		ASSERTCMP(toksize, <=, AFSTOKEN_LENGTH_MAX);

		toksizes[ntoks++] = toksize;
		size += toksize + 4; /* each token has a length word */
	पूर्ण

#अघोषित RND

	अगर (!buffer || buflen < size)
		वापस size;

	xdr = (__be32 *)buffer;
	zero = 0;
#घोषणा ENCODE(x)				\
	करो अणु					\
		*xdr++ = htonl(x);		\
	पूर्ण जबतक(0)
#घोषणा ENCODE_DATA(l, s)						\
	करो अणु								\
		u32 _l = (l);						\
		ENCODE(l);						\
		स_नकल(xdr, (s), _l);					\
		अगर (_l & 3)						\
			स_नकल((u8 *)xdr + _l, &zero, 4 - (_l & 3));	\
		xdr += (_l + 3) >> 2;					\
	पूर्ण जबतक(0)
#घोषणा ENCODE_BYTES(l, s)						\
	करो अणु								\
		u32 _l = (l);						\
		स_नकल(xdr, (s), _l);					\
		अगर (_l & 3)						\
			स_नकल((u8 *)xdr + _l, &zero, 4 - (_l & 3));	\
		xdr += (_l + 3) >> 2;					\
	पूर्ण जबतक(0)
#घोषणा ENCODE64(x)					\
	करो अणु						\
		__be64 y = cpu_to_be64(x);		\
		स_नकल(xdr, &y, 8);			\
		xdr += 8 >> 2;				\
	पूर्ण जबतक(0)
#घोषणा ENCODE_STR(s)				\
	करो अणु					\
		स्थिर अक्षर *_s = (s);		\
		ENCODE_DATA(म_माप(_s), _s);	\
	पूर्ण जबतक(0)

	ENCODE(0);					/* flags */
	ENCODE_DATA(cnlen, key->description + 4);	/* cellname */
	ENCODE(ntoks);

	tok = 0;
	क्रम (token = key->payload.data[0]; token; token = token->next) अणु
		toksize = toksizes[tok++];
		ENCODE(toksize);
		oldxdr = xdr;
		ENCODE(token->security_index);

		चयन (token->security_index) अणु
		हाल RXRPC_SECURITY_RXKAD:
			ENCODE(token->kad->vice_id);
			ENCODE(token->kad->kvno);
			ENCODE_BYTES(8, token->kad->session_key);
			ENCODE(token->kad->start);
			ENCODE(token->kad->expiry);
			ENCODE(token->kad->primary_flag);
			अगर (token->no_leak_key)
				ENCODE(0);
			अन्यथा
				ENCODE_DATA(token->kad->ticket_len, token->kad->ticket);
			अवरोध;

		शेष:
			pr_err("Unsupported key token type (%u)\n",
			       token->security_index);
			वापस -ENOPKG;
		पूर्ण

		ASSERTCMP((अचिन्हित दीर्घ)xdr - (अचिन्हित दीर्घ)oldxdr, ==,
			  toksize);
	पूर्ण

#अघोषित ENCODE_STR
#अघोषित ENCODE_DATA
#अघोषित ENCODE64
#अघोषित ENCODE

	ASSERTCMP(tok, ==, ntoks);
	ASSERTCMP((अक्षर __user *) xdr - buffer, ==, size);
	_leave(" = %zu", size);
	वापस size;
पूर्ण
