<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _FS_CEPH_CRYPTO_H
#घोषणा _FS_CEPH_CRYPTO_H

#समावेश <linux/ceph/types.h>
#समावेश <linux/ceph/buffer.h>

#घोषणा CEPH_KEY_LEN			16
#घोषणा CEPH_MAX_CON_SECRET_LEN		64

/*
 * cryptographic secret
 */
काष्ठा ceph_crypto_key अणु
	पूर्णांक type;
	काष्ठा ceph_बारpec created;
	पूर्णांक len;
	व्योम *key;
	काष्ठा crypto_sync_skcipher *tfm;
पूर्ण;

पूर्णांक ceph_crypto_key_clone(काष्ठा ceph_crypto_key *dst,
			  स्थिर काष्ठा ceph_crypto_key *src);
पूर्णांक ceph_crypto_key_encode(काष्ठा ceph_crypto_key *key, व्योम **p, व्योम *end);
पूर्णांक ceph_crypto_key_decode(काष्ठा ceph_crypto_key *key, व्योम **p, व्योम *end);
पूर्णांक ceph_crypto_key_unarmor(काष्ठा ceph_crypto_key *key, स्थिर अक्षर *in);
व्योम ceph_crypto_key_destroy(काष्ठा ceph_crypto_key *key);

/* crypto.c */
पूर्णांक ceph_crypt(स्थिर काष्ठा ceph_crypto_key *key, bool encrypt,
	       व्योम *buf, पूर्णांक buf_len, पूर्णांक in_len, पूर्णांक *pout_len);
पूर्णांक ceph_crypto_init(व्योम);
व्योम ceph_crypto_shutकरोwn(व्योम);

/* armor.c */
पूर्णांक ceph_armor(अक्षर *dst, स्थिर अक्षर *src, स्थिर अक्षर *end);
पूर्णांक ceph_unarmor(अक्षर *dst, स्थिर अक्षर *src, स्थिर अक्षर *end);

#पूर्ण_अगर
