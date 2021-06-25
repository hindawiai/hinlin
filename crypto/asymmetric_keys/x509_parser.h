<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* X.509 certअगरicate parser पूर्णांकernal definitions
 *
 * Copyright (C) 2012 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/समय.स>
#समावेश <crypto/खुला_key.h>
#समावेश <keys/asymmetric-type.h>

काष्ठा x509_certअगरicate अणु
	काष्ठा x509_certअगरicate *next;
	काष्ठा x509_certअगरicate *signer;	/* Certअगरicate that चिन्हित this one */
	काष्ठा खुला_key *pub;			/* Public key details */
	काष्ठा खुला_key_signature *sig;	/* Signature parameters */
	अक्षर		*issuer;		/* Name of certअगरicate issuer */
	अक्षर		*subject;		/* Name of certअगरicate subject */
	काष्ठा asymmetric_key_id *id;		/* Issuer + Serial number */
	काष्ठा asymmetric_key_id *skid;		/* Subject + subjectKeyId (optional) */
	समय64_t	valid_from;
	समय64_t	valid_to;
	स्थिर व्योम	*tbs;			/* Signed data */
	अचिन्हित	tbs_size;		/* Size of चिन्हित data */
	अचिन्हित	raw_sig_size;		/* Size of sigature */
	स्थिर व्योम	*raw_sig;		/* Signature data */
	स्थिर व्योम	*raw_serial;		/* Raw serial number in ASN.1 */
	अचिन्हित	raw_serial_size;
	अचिन्हित	raw_issuer_size;
	स्थिर व्योम	*raw_issuer;		/* Raw issuer name in ASN.1 */
	स्थिर व्योम	*raw_subject;		/* Raw subject name in ASN.1 */
	अचिन्हित	raw_subject_size;
	अचिन्हित	raw_skid_size;
	स्थिर व्योम	*raw_skid;		/* Raw subjectKeyId in ASN.1 */
	अचिन्हित	index;
	bool		seen;			/* Infinite recursion prevention */
	bool		verअगरied;
	bool		self_चिन्हित;		/* T अगर self-चिन्हित (check unsupported_sig too) */
	bool		unsupported_key;	/* T अगर key uses unsupported crypto */
	bool		unsupported_sig;	/* T अगर signature uses unsupported crypto */
	bool		blacklisted;
पूर्ण;

/*
 * x509_cert_parser.c
 */
बाह्य व्योम x509_मुक्त_certअगरicate(काष्ठा x509_certअगरicate *cert);
बाह्य काष्ठा x509_certअगरicate *x509_cert_parse(स्थिर व्योम *data, माप_प्रकार datalen);
बाह्य पूर्णांक x509_decode_समय(समय64_t *_t,  माप_प्रकार hdrlen,
			    अचिन्हित अक्षर tag,
			    स्थिर अचिन्हित अक्षर *value, माप_प्रकार vlen);

/*
 * x509_खुला_key.c
 */
बाह्य पूर्णांक x509_get_sig_params(काष्ठा x509_certअगरicate *cert);
बाह्य पूर्णांक x509_check_क्रम_self_चिन्हित(काष्ठा x509_certअगरicate *cert);
