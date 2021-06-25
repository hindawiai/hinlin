<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* PKCS#7 crypto data parser पूर्णांकernal definitions
 *
 * Copyright (C) 2012 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/oid_registry.h>
#समावेश <crypto/pkcs7.h>
#समावेश "x509_parser.h"

#घोषणा kenter(FMT, ...) \
	pr_devel("==> %s("FMT")\n", __func__, ##__VA_ARGS__)
#घोषणा kleave(FMT, ...) \
	pr_devel("<== %s()"FMT"\n", __func__, ##__VA_ARGS__)

काष्ठा pkcs7_चिन्हित_info अणु
	काष्ठा pkcs7_चिन्हित_info *next;
	काष्ठा x509_certअगरicate *signer; /* Signing certअगरicate (in msg->certs) */
	अचिन्हित	index;
	bool		unsupported_crypto;	/* T अगर not usable due to missing crypto */
	bool		blacklisted;

	/* Message digest - the digest of the Content Data (or शून्य) */
	स्थिर व्योम	*msgdigest;
	अचिन्हित	msgdigest_len;

	/* Authenticated Attribute data (or शून्य) */
	अचिन्हित	authattrs_len;
	स्थिर व्योम	*authattrs;
	अचिन्हित दीर्घ	aa_set;
#घोषणा	sinfo_has_content_type		0
#घोषणा	sinfo_has_signing_समय		1
#घोषणा	sinfo_has_message_digest	2
#घोषणा sinfo_has_smime_caps		3
#घोषणा	sinfo_has_ms_opus_info		4
#घोषणा	sinfo_has_ms_statement_type	5
	समय64_t	signing_समय;

	/* Message signature.
	 *
	 * This contains the generated digest of _either_ the Content Data or
	 * the Authenticated Attributes [RFC2315 9.3].  If the latter, one of
	 * the attributes contains the digest of the Content Data within it.
	 *
	 * This also contains the issuing cert serial number and issuer's name
	 * [PKCS#7 or CMS ver 1] or issuing cert's SKID [CMS ver 3].
	 */
	काष्ठा खुला_key_signature *sig;
पूर्ण;

काष्ठा pkcs7_message अणु
	काष्ठा x509_certअगरicate *certs;	/* Certअगरicate list */
	काष्ठा x509_certअगरicate *crl;	/* Revocation list */
	काष्ठा pkcs7_चिन्हित_info *चिन्हित_infos;
	u8		version;	/* Version of cert (1 -> PKCS#7 or CMS; 3 -> CMS) */
	bool		have_authattrs;	/* T अगर have authattrs */

	/* Content Data (or शून्य) */
	क्रमागत OID	data_type;	/* Type of Data */
	माप_प्रकार		data_len;	/* Length of Data */
	माप_प्रकार		data_hdrlen;	/* Length of Data ASN.1 header */
	स्थिर व्योम	*data;		/* Content Data (or 0) */
पूर्ण;
