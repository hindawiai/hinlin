<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* PE Binary parser bits
 *
 * Copyright (C) 2014 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <crypto/pkcs7.h>
#समावेश <crypto/hash_info.h>

काष्ठा pefile_context अणु
	अचिन्हित	header_size;
	अचिन्हित	image_checksum_offset;
	अचिन्हित	cert_dirent_offset;
	अचिन्हित	n_data_dirents;
	अचिन्हित	n_sections;
	अचिन्हित	certs_size;
	अचिन्हित	sig_offset;
	अचिन्हित	sig_len;
	स्थिर काष्ठा section_header *secs;

	/* PKCS#7 MS Inभागidual Code Signing content */
	स्थिर व्योम	*digest;		/* Digest */
	अचिन्हित	digest_len;		/* Digest length */
	स्थिर अक्षर	*digest_algo;		/* Digest algorithm */
पूर्ण;

#घोषणा kenter(FMT, ...)					\
	pr_devel("==> %s("FMT")\n", __func__, ##__VA_ARGS__)
#घोषणा kleave(FMT, ...) \
	pr_devel("<== %s()"FMT"\n", __func__, ##__VA_ARGS__)

/*
 * mscode_parser.c
 */
बाह्य पूर्णांक mscode_parse(व्योम *_ctx, स्थिर व्योम *content_data, माप_प्रकार data_len,
			माप_प्रकार asn1hdrlen);
