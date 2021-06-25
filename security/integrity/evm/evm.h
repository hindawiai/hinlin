<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2005-2010 IBM Corporation
 *
 * Authors:
 * Mimi Zohar <zohar@us.ibm.com>
 * Kylene Hall <kjhall@us.ibm.com>
 *
 * File: evm.h
 */

#अगर_अघोषित __INTEGRITY_EVM_H
#घोषणा __INTEGRITY_EVM_H

#समावेश <linux/xattr.h>
#समावेश <linux/security.h>

#समावेश "../integrity.h"

#घोषणा EVM_INIT_HMAC	0x0001
#घोषणा EVM_INIT_X509	0x0002
#घोषणा EVM_ALLOW_METADATA_WRITES	0x0004
#घोषणा EVM_SETUP_COMPLETE 0x80000000 /* userland has संकेतed key load */

#घोषणा EVM_KEY_MASK (EVM_INIT_HMAC | EVM_INIT_X509)
#घोषणा EVM_INIT_MASK (EVM_INIT_HMAC | EVM_INIT_X509 | EVM_SETUP_COMPLETE | \
		       EVM_ALLOW_METADATA_WRITES)

काष्ठा xattr_list अणु
	काष्ठा list_head list;
	अक्षर *name;
पूर्ण;

बाह्य पूर्णांक evm_initialized;

#घोषणा EVM_ATTR_FSUUID		0x0001

बाह्य पूर्णांक evm_hmac_attrs;

बाह्य काष्ठा crypto_shash *hmac_tfm;
बाह्य काष्ठा crypto_shash *hash_tfm;

/* List of EVM रक्षित security xattrs */
बाह्य काष्ठा list_head evm_config_xattrnames;

काष्ठा evm_digest अणु
	काष्ठा ima_digest_data hdr;
	अक्षर digest[IMA_MAX_DIGEST_SIZE];
पूर्ण __packed;

पूर्णांक evm_init_key(व्योम);
पूर्णांक evm_update_evmxattr(काष्ठा dentry *dentry,
			स्थिर अक्षर *req_xattr_name,
			स्थिर अक्षर *req_xattr_value,
			माप_प्रकार req_xattr_value_len);
पूर्णांक evm_calc_hmac(काष्ठा dentry *dentry, स्थिर अक्षर *req_xattr_name,
		  स्थिर अक्षर *req_xattr_value,
		  माप_प्रकार req_xattr_value_len, काष्ठा evm_digest *data);
पूर्णांक evm_calc_hash(काष्ठा dentry *dentry, स्थिर अक्षर *req_xattr_name,
		  स्थिर अक्षर *req_xattr_value,
		  माप_प्रकार req_xattr_value_len, अक्षर type,
		  काष्ठा evm_digest *data);
पूर्णांक evm_init_hmac(काष्ठा inode *inode, स्थिर काष्ठा xattr *xattr,
		  अक्षर *hmac_val);
पूर्णांक evm_init_secfs(व्योम);

#पूर्ण_अगर
