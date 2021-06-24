<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * The ASB.1/BER parsing code is derived from ip_nat_snmp_basic.c which was in
 * turn derived from the gxsnmp package by Gregory McLean & Jochen Friedrich
 *
 * Copyright (c) 2000 RP Internet (www.rpi.net.au).
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश "cifspdu.h"
#समावेश "cifsglob.h"
#समावेश "cifs_debug.h"
#समावेश "cifsproto.h"

/*****************************************************************************
 *
 * Basic ASN.1 decoding routines (gxsnmp author Dirk Wisse)
 *
 *****************************************************************************/

/* Class */
#घोषणा ASN1_UNI	0	/* Universal */
#घोषणा ASN1_APL	1	/* Application */
#घोषणा ASN1_CTX	2	/* Context */
#घोषणा ASN1_PRV	3	/* Private */

/* Tag */
#घोषणा ASN1_EOC	0	/* End Of Contents or N/A */
#घोषणा ASN1_BOL	1	/* Boolean */
#घोषणा ASN1_INT	2	/* Integer */
#घोषणा ASN1_BTS	3	/* Bit String */
#घोषणा ASN1_OTS	4	/* Octet String */
#घोषणा ASN1_NUL	5	/* Null */
#घोषणा ASN1_OJI	6	/* Object Identअगरier  */
#घोषणा ASN1_OJD	7	/* Object Description */
#घोषणा ASN1_EXT	8	/* External */
#घोषणा ASN1_ENUM	10	/* Enumerated */
#घोषणा ASN1_SEQ	16	/* Sequence */
#घोषणा ASN1_SET	17	/* Set */
#घोषणा ASN1_NUMSTR	18	/* Numerical String */
#घोषणा ASN1_PRNSTR	19	/* Prपूर्णांकable String */
#घोषणा ASN1_TEXSTR	20	/* Teletext String */
#घोषणा ASN1_VIDSTR	21	/* Video String */
#घोषणा ASN1_IA5STR	22	/* IA5 String */
#घोषणा ASN1_UNITIM	23	/* Universal Time */
#घोषणा ASN1_GENTIM	24	/* General Time */
#घोषणा ASN1_GRASTR	25	/* Graphical String */
#घोषणा ASN1_VISSTR	26	/* Visible String */
#घोषणा ASN1_GENSTR	27	/* General String */

/* Primitive / Conकाष्ठाed methods*/
#घोषणा ASN1_PRI	0	/* Primitive */
#घोषणा ASN1_CON	1	/* Conकाष्ठाed */

/*
 * Error codes.
 */
#घोषणा ASN1_ERR_NOERROR		0
#घोषणा ASN1_ERR_DEC_EMPTY		2
#घोषणा ASN1_ERR_DEC_EOC_MISMATCH	3
#घोषणा ASN1_ERR_DEC_LENGTH_MISMATCH	4
#घोषणा ASN1_ERR_DEC_BADVALUE		5

#घोषणा SPNEGO_OID_LEN 7
#घोषणा NTLMSSP_OID_LEN  10
#घोषणा KRB5_OID_LEN  7
#घोषणा KRB5U2U_OID_LEN  8
#घोषणा MSKRB5_OID_LEN  7
अटल अचिन्हित दीर्घ SPNEGO_OID[7] = अणु 1, 3, 6, 1, 5, 5, 2 पूर्ण;
अटल अचिन्हित दीर्घ NTLMSSP_OID[10] = अणु 1, 3, 6, 1, 4, 1, 311, 2, 2, 10 पूर्ण;
अटल अचिन्हित दीर्घ KRB5_OID[7] = अणु 1, 2, 840, 113554, 1, 2, 2 पूर्ण;
अटल अचिन्हित दीर्घ KRB5U2U_OID[8] = अणु 1, 2, 840, 113554, 1, 2, 2, 3 पूर्ण;
अटल अचिन्हित दीर्घ MSKRB5_OID[7] = अणु 1, 2, 840, 48018, 1, 2, 2 पूर्ण;

/*
 * ASN.1 context.
 */
काष्ठा asn1_ctx अणु
	पूर्णांक error;		/* Error condition */
	अचिन्हित अक्षर *poपूर्णांकer;	/* Octet just to be decoded */
	अचिन्हित अक्षर *begin;	/* First octet */
	अचिन्हित अक्षर *end;	/* Octet after last octet */
पूर्ण;

/*
 * Octet string (not null terminated)
 */
काष्ठा asn1_octstr अणु
	अचिन्हित अक्षर *data;
	अचिन्हित पूर्णांक len;
पूर्ण;

अटल व्योम
asn1_खोलो(काष्ठा asn1_ctx *ctx, अचिन्हित अक्षर *buf, अचिन्हित पूर्णांक len)
अणु
	ctx->begin = buf;
	ctx->end = buf + len;
	ctx->poपूर्णांकer = buf;
	ctx->error = ASN1_ERR_NOERROR;
पूर्ण

अटल अचिन्हित अक्षर
asn1_octet_decode(काष्ठा asn1_ctx *ctx, अचिन्हित अक्षर *ch)
अणु
	अगर (ctx->poपूर्णांकer >= ctx->end) अणु
		ctx->error = ASN1_ERR_DEC_EMPTY;
		वापस 0;
	पूर्ण
	*ch = *(ctx->poपूर्णांकer)++;
	वापस 1;
पूर्ण

#अगर 0 /* will be needed later by spnego decoding/encoding of ntlmssp */
अटल अचिन्हित अक्षर
asn1_क्रमागत_decode(काष्ठा asn1_ctx *ctx, __le32 *val)
अणु
	अचिन्हित अक्षर ch;

	अगर (ctx->poपूर्णांकer >= ctx->end) अणु
		ctx->error = ASN1_ERR_DEC_EMPTY;
		वापस 0;
	पूर्ण

	ch = *(ctx->poपूर्णांकer)++; /* ch has 0xa, ptr poपूर्णांकs to length octet */
	अगर ((ch) == ASN1_ENUM)  /* अगर ch value is ENUM, 0xa */
		*val = *(++(ctx->poपूर्णांकer)); /* value has क्रमागत value */
	अन्यथा
		वापस 0;

	ctx->poपूर्णांकer++;
	वापस 1;
पूर्ण
#पूर्ण_अगर

अटल अचिन्हित अक्षर
asn1_tag_decode(काष्ठा asn1_ctx *ctx, अचिन्हित पूर्णांक *tag)
अणु
	अचिन्हित अक्षर ch;

	*tag = 0;

	करो अणु
		अगर (!asn1_octet_decode(ctx, &ch))
			वापस 0;
		*tag <<= 7;
		*tag |= ch & 0x7F;
	पूर्ण जबतक ((ch & 0x80) == 0x80);
	वापस 1;
पूर्ण

अटल अचिन्हित अक्षर
asn1_id_decode(काष्ठा asn1_ctx *ctx,
	       अचिन्हित पूर्णांक *cls, अचिन्हित पूर्णांक *con, अचिन्हित पूर्णांक *tag)
अणु
	अचिन्हित अक्षर ch;

	अगर (!asn1_octet_decode(ctx, &ch))
		वापस 0;

	*cls = (ch & 0xC0) >> 6;
	*con = (ch & 0x20) >> 5;
	*tag = (ch & 0x1F);

	अगर (*tag == 0x1F) अणु
		अगर (!asn1_tag_decode(ctx, tag))
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल अचिन्हित अक्षर
asn1_length_decode(काष्ठा asn1_ctx *ctx, अचिन्हित पूर्णांक *def, अचिन्हित पूर्णांक *len)
अणु
	अचिन्हित अक्षर ch, cnt;

	अगर (!asn1_octet_decode(ctx, &ch))
		वापस 0;

	अगर (ch == 0x80)
		*def = 0;
	अन्यथा अणु
		*def = 1;

		अगर (ch < 0x80)
			*len = ch;
		अन्यथा अणु
			cnt = (अचिन्हित अक्षर) (ch & 0x7F);
			*len = 0;

			जबतक (cnt > 0) अणु
				अगर (!asn1_octet_decode(ctx, &ch))
					वापस 0;
				*len <<= 8;
				*len |= ch;
				cnt--;
			पूर्ण
		पूर्ण
	पूर्ण

	/* करोn't trust len bigger than ctx buffer */
	अगर (*len > ctx->end - ctx->poपूर्णांकer)
		वापस 0;

	वापस 1;
पूर्ण

अटल अचिन्हित अक्षर
asn1_header_decode(काष्ठा asn1_ctx *ctx,
		   अचिन्हित अक्षर **eoc,
		   अचिन्हित पूर्णांक *cls, अचिन्हित पूर्णांक *con, अचिन्हित पूर्णांक *tag)
अणु
	अचिन्हित पूर्णांक def = 0;
	अचिन्हित पूर्णांक len = 0;

	अगर (!asn1_id_decode(ctx, cls, con, tag))
		वापस 0;

	अगर (!asn1_length_decode(ctx, &def, &len))
		वापस 0;

	/* primitive shall be definite, indefinite shall be स्थिरructed */
	अगर (*con == ASN1_PRI && !def)
		वापस 0;

	अगर (def)
		*eoc = ctx->poपूर्णांकer + len;
	अन्यथा
		*eoc = शून्य;
	वापस 1;
पूर्ण

अटल अचिन्हित अक्षर
asn1_eoc_decode(काष्ठा asn1_ctx *ctx, अचिन्हित अक्षर *eoc)
अणु
	अचिन्हित अक्षर ch;

	अगर (eoc == शून्य) अणु
		अगर (!asn1_octet_decode(ctx, &ch))
			वापस 0;

		अगर (ch != 0x00) अणु
			ctx->error = ASN1_ERR_DEC_EOC_MISMATCH;
			वापस 0;
		पूर्ण

		अगर (!asn1_octet_decode(ctx, &ch))
			वापस 0;

		अगर (ch != 0x00) अणु
			ctx->error = ASN1_ERR_DEC_EOC_MISMATCH;
			वापस 0;
		पूर्ण
		वापस 1;
	पूर्ण अन्यथा अणु
		अगर (ctx->poपूर्णांकer != eoc) अणु
			ctx->error = ASN1_ERR_DEC_LENGTH_MISMATCH;
			वापस 0;
		पूर्ण
		वापस 1;
	पूर्ण
पूर्ण

/* अटल अचिन्हित अक्षर asn1_null_decode(काष्ठा asn1_ctx *ctx,
				      अचिन्हित अक्षर *eoc)
अणु
	ctx->poपूर्णांकer = eoc;
	वापस 1;
पूर्ण

अटल अचिन्हित अक्षर asn1_दीर्घ_decode(काष्ठा asn1_ctx *ctx,
				      अचिन्हित अक्षर *eoc, दीर्घ *पूर्णांकeger)
अणु
	अचिन्हित अक्षर ch;
	अचिन्हित पूर्णांक len;

	अगर (!asn1_octet_decode(ctx, &ch))
		वापस 0;

	*पूर्णांकeger = (चिन्हित अक्षर) ch;
	len = 1;

	जबतक (ctx->poपूर्णांकer < eoc) अणु
		अगर (++len > माप(दीर्घ)) अणु
			ctx->error = ASN1_ERR_DEC_BADVALUE;
			वापस 0;
		पूर्ण

		अगर (!asn1_octet_decode(ctx, &ch))
			वापस 0;

		*पूर्णांकeger <<= 8;
		*पूर्णांकeger |= ch;
	पूर्ण
	वापस 1;
पूर्ण

अटल अचिन्हित अक्षर asn1_uपूर्णांक_decode(काष्ठा asn1_ctx *ctx,
				      अचिन्हित अक्षर *eoc,
				      अचिन्हित पूर्णांक *पूर्णांकeger)
अणु
	अचिन्हित अक्षर ch;
	अचिन्हित पूर्णांक len;

	अगर (!asn1_octet_decode(ctx, &ch))
		वापस 0;

	*पूर्णांकeger = ch;
	अगर (ch == 0)
		len = 0;
	अन्यथा
		len = 1;

	जबतक (ctx->poपूर्णांकer < eoc) अणु
		अगर (++len > माप(अचिन्हित पूर्णांक)) अणु
			ctx->error = ASN1_ERR_DEC_BADVALUE;
			वापस 0;
		पूर्ण

		अगर (!asn1_octet_decode(ctx, &ch))
			वापस 0;

		*पूर्णांकeger <<= 8;
		*पूर्णांकeger |= ch;
	पूर्ण
	वापस 1;
पूर्ण

अटल अचिन्हित अक्षर asn1_uदीर्घ_decode(काष्ठा asn1_ctx *ctx,
				       अचिन्हित अक्षर *eoc,
				       अचिन्हित दीर्घ *पूर्णांकeger)
अणु
	अचिन्हित अक्षर ch;
	अचिन्हित पूर्णांक len;

	अगर (!asn1_octet_decode(ctx, &ch))
		वापस 0;

	*पूर्णांकeger = ch;
	अगर (ch == 0)
		len = 0;
	अन्यथा
		len = 1;

	जबतक (ctx->poपूर्णांकer < eoc) अणु
		अगर (++len > माप(अचिन्हित दीर्घ)) अणु
			ctx->error = ASN1_ERR_DEC_BADVALUE;
			वापस 0;
		पूर्ण

		अगर (!asn1_octet_decode(ctx, &ch))
			वापस 0;

		*पूर्णांकeger <<= 8;
		*पूर्णांकeger |= ch;
	पूर्ण
	वापस 1;
पूर्ण

अटल अचिन्हित अक्षर
asn1_octets_decode(काष्ठा asn1_ctx *ctx,
		   अचिन्हित अक्षर *eoc,
		   अचिन्हित अक्षर **octets, अचिन्हित पूर्णांक *len)
अणु
	अचिन्हित अक्षर *ptr;

	*len = 0;

	*octets = kदो_स्मृति(eoc - ctx->poपूर्णांकer, GFP_ATOMIC);
	अगर (*octets == शून्य) अणु
		वापस 0;
	पूर्ण

	ptr = *octets;
	जबतक (ctx->poपूर्णांकer < eoc) अणु
		अगर (!asn1_octet_decode(ctx, (अचिन्हित अक्षर *) ptr++)) अणु
			kमुक्त(*octets);
			*octets = शून्य;
			वापस 0;
		पूर्ण
		(*len)++;
	पूर्ण
	वापस 1;
पूर्ण */

अटल अचिन्हित अक्षर
asn1_subid_decode(काष्ठा asn1_ctx *ctx, अचिन्हित दीर्घ *subid)
अणु
	अचिन्हित अक्षर ch;

	*subid = 0;

	करो अणु
		अगर (!asn1_octet_decode(ctx, &ch))
			वापस 0;

		*subid <<= 7;
		*subid |= ch & 0x7F;
	पूर्ण जबतक ((ch & 0x80) == 0x80);
	वापस 1;
पूर्ण

अटल पूर्णांक
asn1_oid_decode(काष्ठा asn1_ctx *ctx,
		अचिन्हित अक्षर *eoc, अचिन्हित दीर्घ **oid, अचिन्हित पूर्णांक *len)
अणु
	अचिन्हित दीर्घ subid;
	अचिन्हित पूर्णांक size;
	अचिन्हित दीर्घ *optr;

	size = eoc - ctx->poपूर्णांकer + 1;

	/* first subid actually encodes first two subids */
	अगर (size < 2 || size > अच_पूर्णांक_उच्च/माप(अचिन्हित दीर्घ))
		वापस 0;

	*oid = kदो_स्मृति_array(size, माप(अचिन्हित दीर्घ), GFP_ATOMIC);
	अगर (*oid == शून्य)
		वापस 0;

	optr = *oid;

	अगर (!asn1_subid_decode(ctx, &subid)) अणु
		kमुक्त(*oid);
		*oid = शून्य;
		वापस 0;
	पूर्ण

	अगर (subid < 40) अणु
		optr[0] = 0;
		optr[1] = subid;
	पूर्ण अन्यथा अगर (subid < 80) अणु
		optr[0] = 1;
		optr[1] = subid - 40;
	पूर्ण अन्यथा अणु
		optr[0] = 2;
		optr[1] = subid - 80;
	पूर्ण

	*len = 2;
	optr += 2;

	जबतक (ctx->poपूर्णांकer < eoc) अणु
		अगर (++(*len) > size) अणु
			ctx->error = ASN1_ERR_DEC_BADVALUE;
			kमुक्त(*oid);
			*oid = शून्य;
			वापस 0;
		पूर्ण

		अगर (!asn1_subid_decode(ctx, optr++)) अणु
			kमुक्त(*oid);
			*oid = शून्य;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक
compare_oid(अचिन्हित दीर्घ *oid1, अचिन्हित पूर्णांक oid1len,
	    अचिन्हित दीर्घ *oid2, अचिन्हित पूर्णांक oid2len)
अणु
	अचिन्हित पूर्णांक i;

	अगर (oid1len != oid2len)
		वापस 0;
	अन्यथा अणु
		क्रम (i = 0; i < oid1len; i++) अणु
			अगर (oid1[i] != oid2[i])
				वापस 0;
		पूर्ण
		वापस 1;
	पूर्ण
पूर्ण

	/* BB check क्रम endian conversion issues here */

पूर्णांक
decode_negTokenInit(अचिन्हित अक्षर *security_blob, पूर्णांक length,
		    काष्ठा TCP_Server_Info *server)
अणु
	काष्ठा asn1_ctx ctx;
	अचिन्हित अक्षर *end;
	अचिन्हित अक्षर *sequence_end;
	अचिन्हित दीर्घ *oid = शून्य;
	अचिन्हित पूर्णांक cls, con, tag, oidlen, rc;

	/* cअगरs_dump_mem(" Received SecBlob ", security_blob, length); */

	asn1_खोलो(&ctx, security_blob, length);

	/* GSSAPI header */
	अगर (asn1_header_decode(&ctx, &end, &cls, &con, &tag) == 0) अणु
		cअगरs_dbg(FYI, "Error decoding negTokenInit header\n");
		वापस 0;
	पूर्ण अन्यथा अगर ((cls != ASN1_APL) || (con != ASN1_CON)
		   || (tag != ASN1_EOC)) अणु
		cअगरs_dbg(FYI, "cls = %d con = %d tag = %d\n", cls, con, tag);
		वापस 0;
	पूर्ण

	/* Check क्रम SPNEGO OID -- remember to मुक्त obj->oid */
	rc = asn1_header_decode(&ctx, &end, &cls, &con, &tag);
	अगर (rc) अणु
		अगर ((tag == ASN1_OJI) && (con == ASN1_PRI) &&
		    (cls == ASN1_UNI)) अणु
			rc = asn1_oid_decode(&ctx, end, &oid, &oidlen);
			अगर (rc) अणु
				rc = compare_oid(oid, oidlen, SPNEGO_OID,
						 SPNEGO_OID_LEN);
				kमुक्त(oid);
			पूर्ण
		पूर्ण अन्यथा
			rc = 0;
	पूर्ण

	/* SPNEGO OID not present or garbled -- bail out */
	अगर (!rc) अणु
		cअगरs_dbg(FYI, "Error decoding negTokenInit header\n");
		वापस 0;
	पूर्ण

	/* SPNEGO */
	अगर (asn1_header_decode(&ctx, &end, &cls, &con, &tag) == 0) अणु
		cअगरs_dbg(FYI, "Error decoding negTokenInit\n");
		वापस 0;
	पूर्ण अन्यथा अगर ((cls != ASN1_CTX) || (con != ASN1_CON)
		   || (tag != ASN1_EOC)) अणु
		cअगरs_dbg(FYI, "cls = %d con = %d tag = %d end = %p exit 0\n",
			 cls, con, tag, end);
		वापस 0;
	पूर्ण

	/* negTokenInit */
	अगर (asn1_header_decode(&ctx, &end, &cls, &con, &tag) == 0) अणु
		cअगरs_dbg(FYI, "Error decoding negTokenInit\n");
		वापस 0;
	पूर्ण अन्यथा अगर ((cls != ASN1_UNI) || (con != ASN1_CON)
		   || (tag != ASN1_SEQ)) अणु
		cअगरs_dbg(FYI, "cls = %d con = %d tag = %d end = %p exit 1\n",
			 cls, con, tag, end);
		वापस 0;
	पूर्ण

	/* sequence */
	अगर (asn1_header_decode(&ctx, &end, &cls, &con, &tag) == 0) अणु
		cअगरs_dbg(FYI, "Error decoding 2nd part of negTokenInit\n");
		वापस 0;
	पूर्ण अन्यथा अगर ((cls != ASN1_CTX) || (con != ASN1_CON)
		   || (tag != ASN1_EOC)) अणु
		cअगरs_dbg(FYI, "cls = %d con = %d tag = %d end = %p exit 0\n",
			 cls, con, tag, end);
		वापस 0;
	पूर्ण

	/* sequence of */
	अगर (asn1_header_decode
	    (&ctx, &sequence_end, &cls, &con, &tag) == 0) अणु
		cअगरs_dbg(FYI, "Error decoding 2nd part of negTokenInit\n");
		वापस 0;
	पूर्ण अन्यथा अगर ((cls != ASN1_UNI) || (con != ASN1_CON)
		   || (tag != ASN1_SEQ)) अणु
		cअगरs_dbg(FYI, "cls = %d con = %d tag = %d sequence_end = %p exit 1\n",
			 cls, con, tag, sequence_end);
		वापस 0;
	पूर्ण

	/* list of security mechanisms */
	जबतक (!asn1_eoc_decode(&ctx, sequence_end)) अणु
		rc = asn1_header_decode(&ctx, &end, &cls, &con, &tag);
		अगर (!rc) अणु
			cअगरs_dbg(FYI, "Error decoding negTokenInit hdr exit2\n");
			वापस 0;
		पूर्ण
		अगर ((tag == ASN1_OJI) && (con == ASN1_PRI)) अणु
			अगर (asn1_oid_decode(&ctx, end, &oid, &oidlen)) अणु

				cअगरs_dbg(FYI, "OID len = %d oid = 0x%lx 0x%lx 0x%lx 0x%lx\n",
					 oidlen, *oid, *(oid + 1), *(oid + 2),
					 *(oid + 3));

				अगर (compare_oid(oid, oidlen, MSKRB5_OID,
						MSKRB5_OID_LEN))
					server->sec_mskerberos = true;
				अन्यथा अगर (compare_oid(oid, oidlen, KRB5U2U_OID,
						     KRB5U2U_OID_LEN))
					server->sec_kerberosu2u = true;
				अन्यथा अगर (compare_oid(oid, oidlen, KRB5_OID,
						     KRB5_OID_LEN))
					server->sec_kerberos = true;
				अन्यथा अगर (compare_oid(oid, oidlen, NTLMSSP_OID,
						     NTLMSSP_OID_LEN))
					server->sec_ntlmssp = true;

				kमुक्त(oid);
			पूर्ण
		पूर्ण अन्यथा अणु
			cअगरs_dbg(FYI, "Should be an oid what is going on?\n");
		पूर्ण
	पूर्ण

	/*
	 * We currently ignore anything at the end of the SPNEGO blob after
	 * the mechTypes have been parsed, since none of that info is
	 * used at the moment.
	 */
	वापस 1;
पूर्ण
