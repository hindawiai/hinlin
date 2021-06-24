<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ecryptfs_क्रमmat.h: helper functions क्रम the encrypted key type
 *
 * Copyright (C) 2006 International Business Machines Corp.
 * Copyright (C) 2010 Politecnico di Torino, Italy
 *                    TORSEC group -- https://security.polito.it
 *
 * Authors:
 * Michael A. Halcrow <mahalcro@us.ibm.com>
 * Tyler Hicks <tyhicks@ou.edu>
 * Roberto Sassu <roberto.sassu@polito.it>
 */

#अगर_अघोषित __KEYS_ECRYPTFS_H
#घोषणा __KEYS_ECRYPTFS_H

#समावेश <linux/ecryptfs.h>

#घोषणा PGP_DIGEST_ALGO_SHA512   10

u8 *ecryptfs_get_auth_tok_key(काष्ठा ecryptfs_auth_tok *auth_tok);
व्योम ecryptfs_get_versions(पूर्णांक *major, पूर्णांक *minor, पूर्णांक *file_version);
पूर्णांक ecryptfs_fill_auth_tok(काष्ठा ecryptfs_auth_tok *auth_tok,
			   स्थिर अक्षर *key_desc);

#पूर्ण_अगर /* __KEYS_ECRYPTFS_H */
