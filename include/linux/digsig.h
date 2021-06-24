<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2011 Nokia Corporation
 * Copyright (C) 2011 Intel Corporation
 *
 * Author:
 * Dmitry Kasatkin <dmitry.kasatkin@nokia.com>
 *                 <dmitry.kasatkin@पूर्णांकel.com>
 */

#अगर_अघोषित _DIGSIG_H
#घोषणा _DIGSIG_H

#समावेश <linux/key.h>

क्रमागत pubkey_algo अणु
	PUBKEY_ALGO_RSA,
	PUBKEY_ALGO_MAX,
पूर्ण;

क्रमागत digest_algo अणु
	DIGEST_ALGO_SHA1,
	DIGEST_ALGO_SHA256,
	DIGEST_ALGO_MAX
पूर्ण;

काष्ठा pubkey_hdr अणु
	uपूर्णांक8_t		version;	/* key क्रमmat version */
	uपूर्णांक32_t	बारtamp;	/* key made, always 0 क्रम now */
	uपूर्णांक8_t		algo;
	uपूर्णांक8_t		nmpi;
	अक्षर		mpi[];
पूर्ण __packed;

काष्ठा signature_hdr अणु
	uपूर्णांक8_t		version;	/* signature क्रमmat version */
	uपूर्णांक32_t	बारtamp;	/* signature made */
	uपूर्णांक8_t		algo;
	uपूर्णांक8_t		hash;
	uपूर्णांक8_t		keyid[8];
	uपूर्णांक8_t		nmpi;
	अक्षर		mpi[];
पूर्ण __packed;

#अगर defined(CONFIG_SIGNATURE) || defined(CONFIG_SIGNATURE_MODULE)

पूर्णांक digsig_verअगरy(काष्ठा key *keyring, स्थिर अक्षर *sig, पूर्णांक siglen,
					स्थिर अक्षर *digest, पूर्णांक digestlen);

#अन्यथा

अटल अंतरभूत पूर्णांक digsig_verअगरy(काष्ठा key *keyring, स्थिर अक्षर *sig,
				पूर्णांक siglen, स्थिर अक्षर *digest, पूर्णांक digestlen)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

#पूर्ण_अगर /* CONFIG_SIGNATURE */

#पूर्ण_अगर /* _DIGSIG_H */
