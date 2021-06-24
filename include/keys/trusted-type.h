<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2010 IBM Corporation
 * Author: David Safक्रमd <safक्रमd@us.ibm.com>
 */

#अगर_अघोषित _KEYS_TRUSTED_TYPE_H
#घोषणा _KEYS_TRUSTED_TYPE_H

#समावेश <linux/key.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/tpm.h>

#अगर_घोषित pr_fmt
#अघोषित pr_fmt
#पूर्ण_अगर

#घोषणा pr_fmt(fmt) "trusted_key: " fmt

#घोषणा MIN_KEY_SIZE			32
#घोषणा MAX_KEY_SIZE			128
#घोषणा MAX_BLOB_SIZE			512
#घोषणा MAX_PCRINFO_SIZE		64
#घोषणा MAX_DIGEST_SIZE			64

काष्ठा trusted_key_payload अणु
	काष्ठा rcu_head rcu;
	अचिन्हित पूर्णांक key_len;
	अचिन्हित पूर्णांक blob_len;
	अचिन्हित अक्षर migratable;
	अचिन्हित अक्षर old_क्रमmat;
	अचिन्हित अक्षर key[MAX_KEY_SIZE + 1];
	अचिन्हित अक्षर blob[MAX_BLOB_SIZE];
पूर्ण;

काष्ठा trusted_key_options अणु
	uपूर्णांक16_t keytype;
	uपूर्णांक32_t keyhandle;
	अचिन्हित अक्षर keyauth[TPM_DIGEST_SIZE];
	uपूर्णांक32_t blobauth_len;
	अचिन्हित अक्षर blobauth[TPM_DIGEST_SIZE];
	uपूर्णांक32_t pcrinfo_len;
	अचिन्हित अक्षर pcrinfo[MAX_PCRINFO_SIZE];
	पूर्णांक pcrlock;
	uपूर्णांक32_t hash;
	uपूर्णांक32_t policydigest_len;
	अचिन्हित अक्षर policydigest[MAX_DIGEST_SIZE];
	uपूर्णांक32_t policyhandle;
पूर्ण;

काष्ठा trusted_key_ops अणु
	/*
	 * flag to indicate अगर trusted key implementation supports migration
	 * or not.
	 */
	अचिन्हित अक्षर migratable;

	/* Initialize key पूर्णांकerface. */
	पूर्णांक (*init)(व्योम);

	/* Seal a key. */
	पूर्णांक (*seal)(काष्ठा trusted_key_payload *p, अक्षर *datablob);

	/* Unseal a key. */
	पूर्णांक (*unseal)(काष्ठा trusted_key_payload *p, अक्षर *datablob);

	/* Get a अक्रमomized key. */
	पूर्णांक (*get_अक्रमom)(अचिन्हित अक्षर *key, माप_प्रकार key_len);

	/* Exit key पूर्णांकerface. */
	व्योम (*निकास)(व्योम);
पूर्ण;

काष्ठा trusted_key_source अणु
	अक्षर *name;
	काष्ठा trusted_key_ops *ops;
पूर्ण;

बाह्य काष्ठा key_type key_type_trusted;

#घोषणा TRUSTED_DEBUG 0

#अगर TRUSTED_DEBUG
अटल अंतरभूत व्योम dump_payload(काष्ठा trusted_key_payload *p)
अणु
	pr_info("key_len %d\n", p->key_len);
	prपूर्णांक_hex_dump(KERN_INFO, "key ", DUMP_PREFIX_NONE,
		       16, 1, p->key, p->key_len, 0);
	pr_info("bloblen %d\n", p->blob_len);
	prपूर्णांक_hex_dump(KERN_INFO, "blob ", DUMP_PREFIX_NONE,
		       16, 1, p->blob, p->blob_len, 0);
	pr_info("migratable %d\n", p->migratable);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम dump_payload(काष्ठा trusted_key_payload *p)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _KEYS_TRUSTED_TYPE_H */
