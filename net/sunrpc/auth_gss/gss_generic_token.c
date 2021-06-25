<शैली गुरु>
/*
 *  linux/net/sunrpc/gss_generic_token.c
 *
 *  Adapted from MIT Kerberos 5-1.2.1 lib/gssapi/generic/util_token.c
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

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/sunrpc/sched.h>
#समावेश <linux/sunrpc/gss_asn1.h>


#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
# define RPCDBG_FACILITY        RPCDBG_AUTH
#पूर्ण_अगर


/* TWRITE_STR from gssapiP_generic.h */
#घोषणा TWRITE_STR(ptr, str, len) \
	स_नकल((ptr), (अक्षर *) (str), (len)); \
	(ptr) += (len);

/* XXXX this code currently makes the assumption that a mech oid will
   never be दीर्घer than 127 bytes.  This assumption is not inherent in
   the पूर्णांकerfaces, so the code can be fixed अगर the OSI namespace
   balloons unexpectedly. */

/* Each token looks like this:

0x60				tag क्रम APPLICATION 0, SEQUENCE
					(स्थिरructed, definite-length)
	<length>		possible multiple bytes, need to parse/generate
	0x06			tag क्रम OBJECT IDENTIFIER
		<moid_length>	compile-समय स्थिरant string (assume 1 byte)
		<moid_bytes>	compile-समय स्थिरant string
	<inner_bytes>		the ANY containing the application token
					bytes 0,1 are the token type
					bytes 2,n are the token data

For the purposes of this असलtraction, the token "header" consists of
the sequence tag and length octets, the mech OID DER encoding, and the
first two inner bytes, which indicate the token type.  The token
"body" consists of everything अन्यथा.

*/

अटल पूर्णांक
der_length_size( पूर्णांक length)
अणु
	अगर (length < (1<<7))
		वापस 1;
	अन्यथा अगर (length < (1<<8))
		वापस 2;
#अगर (SIZखातापूर्ण_INT == 2)
	अन्यथा
		वापस 3;
#अन्यथा
	अन्यथा अगर (length < (1<<16))
		वापस 3;
	अन्यथा अगर (length < (1<<24))
		वापस 4;
	अन्यथा
		वापस 5;
#पूर्ण_अगर
पूर्ण

अटल व्योम
der_ग_लिखो_length(अचिन्हित अक्षर **buf, पूर्णांक length)
अणु
	अगर (length < (1<<7)) अणु
		*(*buf)++ = (अचिन्हित अक्षर) length;
	पूर्ण अन्यथा अणु
		*(*buf)++ = (अचिन्हित अक्षर) (der_length_size(length)+127);
#अगर (SIZखातापूर्ण_INT > 2)
		अगर (length >= (1<<24))
			*(*buf)++ = (अचिन्हित अक्षर) (length>>24);
		अगर (length >= (1<<16))
			*(*buf)++ = (अचिन्हित अक्षर) ((length>>16)&0xff);
#पूर्ण_अगर
		अगर (length >= (1<<8))
			*(*buf)++ = (अचिन्हित अक्षर) ((length>>8)&0xff);
		*(*buf)++ = (अचिन्हित अक्षर) (length&0xff);
	पूर्ण
पूर्ण

/* वापसs decoded length, or < 0 on failure.  Advances buf and
   decrements bufsize */

अटल पूर्णांक
der_पढ़ो_length(अचिन्हित अक्षर **buf, पूर्णांक *bufsize)
अणु
	अचिन्हित अक्षर sf;
	पूर्णांक ret;

	अगर (*bufsize < 1)
		वापस -1;
	sf = *(*buf)++;
	(*bufsize)--;
	अगर (sf & 0x80) अणु
		अगर ((sf &= 0x7f) > ((*bufsize)-1))
			वापस -1;
		अगर (sf > SIZखातापूर्ण_INT)
			वापस -1;
		ret = 0;
		क्रम (; sf; sf--) अणु
			ret = (ret<<8) + (*(*buf)++);
			(*bufsize)--;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = sf;
	पूर्ण

	वापस ret;
पूर्ण

/* वापसs the length of a token, given the mech oid and the body size */

पूर्णांक
g_token_size(काष्ठा xdr_netobj *mech, अचिन्हित पूर्णांक body_size)
अणु
	/* set body_size to sequence contents size */
	body_size += 2 + (पूर्णांक) mech->len;         /* NEED overflow check */
	वापस 1 + der_length_size(body_size) + body_size;
पूर्ण

EXPORT_SYMBOL_GPL(g_token_size);

/* fills in a buffer with the token header.  The buffer is assumed to
   be the right size.  buf is advanced past the token header */

व्योम
g_make_token_header(काष्ठा xdr_netobj *mech, पूर्णांक body_size, अचिन्हित अक्षर **buf)
अणु
	*(*buf)++ = 0x60;
	der_ग_लिखो_length(buf, 2 + mech->len + body_size);
	*(*buf)++ = 0x06;
	*(*buf)++ = (अचिन्हित अक्षर) mech->len;
	TWRITE_STR(*buf, mech->data, ((पूर्णांक) mech->len));
पूर्ण

EXPORT_SYMBOL_GPL(g_make_token_header);

/*
 * Given a buffer containing a token, पढ़ोs and verअगरies the token,
 * leaving buf advanced past the token header, and setting body_size
 * to the number of reमुख्यing bytes.  Returns 0 on success,
 * G_BAD_TOK_HEADER क्रम a variety of errors, and G_WRONG_MECH अगर the
 * mechanism in the token करोes not match the mech argument.  buf and
 * *body_size are left unmodअगरied on error.
 */
u32
g_verअगरy_token_header(काष्ठा xdr_netobj *mech, पूर्णांक *body_size,
		      अचिन्हित अक्षर **buf_in, पूर्णांक toksize)
अणु
	अचिन्हित अक्षर *buf = *buf_in;
	पूर्णांक seqsize;
	काष्ठा xdr_netobj toid;
	पूर्णांक ret = 0;

	अगर ((toksize-=1) < 0)
		वापस G_BAD_TOK_HEADER;
	अगर (*buf++ != 0x60)
		वापस G_BAD_TOK_HEADER;

	अगर ((seqsize = der_पढ़ो_length(&buf, &toksize)) < 0)
		वापस G_BAD_TOK_HEADER;

	अगर (seqsize != toksize)
		वापस G_BAD_TOK_HEADER;

	अगर ((toksize-=1) < 0)
		वापस G_BAD_TOK_HEADER;
	अगर (*buf++ != 0x06)
		वापस G_BAD_TOK_HEADER;

	अगर ((toksize-=1) < 0)
		वापस G_BAD_TOK_HEADER;
	toid.len = *buf++;

	अगर ((toksize-=toid.len) < 0)
		वापस G_BAD_TOK_HEADER;
	toid.data = buf;
	buf+=toid.len;

	अगर (! g_OID_equal(&toid, mech))
		ret = G_WRONG_MECH;

   /* G_WRONG_MECH is not वापसed immediately because it's more important
      to वापस G_BAD_TOK_HEADER अगर the token header is in fact bad */

	अगर ((toksize-=2) < 0)
		वापस G_BAD_TOK_HEADER;

	अगर (ret)
		वापस ret;

	अगर (!ret) अणु
		*buf_in = buf;
		*body_size = toksize;
	पूर्ण

	वापस ret;
पूर्ण

EXPORT_SYMBOL_GPL(g_verअगरy_token_header);
