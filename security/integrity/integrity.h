<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2009-2010 IBM Corporation
 *
 * Authors:
 * Mimi Zohar <zohar@us.ibm.com>
 */

#अगर_घोषित pr_fmt
#अघोषित pr_fmt
#पूर्ण_अगर

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकegrity.h>
#समावेश <crypto/sha1.h>
#समावेश <linux/key.h>
#समावेश <linux/audit.h>

/* iपूर्णांक action cache flags */
#घोषणा IMA_MEASURE		0x00000001
#घोषणा IMA_MEASURED		0x00000002
#घोषणा IMA_APPRAISE		0x00000004
#घोषणा IMA_APPRAISED		0x00000008
/*#घोषणा IMA_COLLECT		0x00000010  करो not use this flag */
#घोषणा IMA_COLLECTED		0x00000020
#घोषणा IMA_AUDIT		0x00000040
#घोषणा IMA_AUDITED		0x00000080
#घोषणा IMA_HASH		0x00000100
#घोषणा IMA_HASHED		0x00000200

/* iपूर्णांक cache flags */
#घोषणा IMA_ACTION_FLAGS	0xff000000
#घोषणा IMA_DIGSIG_REQUIRED	0x01000000
#घोषणा IMA_PERMIT_सूचीECTIO	0x02000000
#घोषणा IMA_NEW_खाता		0x04000000
#घोषणा EVM_IMMUTABLE_DIGSIG	0x08000000
#घोषणा IMA_FAIL_UNVERIFIABLE_SIGS	0x10000000
#घोषणा IMA_MODSIG_ALLOWED	0x20000000
#घोषणा IMA_CHECK_BLACKLIST	0x40000000

#घोषणा IMA_DO_MASK		(IMA_MEASURE | IMA_APPRAISE | IMA_AUDIT | \
				 IMA_HASH | IMA_APPRAISE_SUBMASK)
#घोषणा IMA_DONE_MASK		(IMA_MEASURED | IMA_APPRAISED | IMA_AUDITED | \
				 IMA_HASHED | IMA_COLLECTED | \
				 IMA_APPRAISED_SUBMASK)

/* iपूर्णांक subaction appउठाओ cache flags */
#घोषणा IMA_खाता_APPRAISE	0x00001000
#घोषणा IMA_खाता_APPRAISED	0x00002000
#घोषणा IMA_MMAP_APPRAISE	0x00004000
#घोषणा IMA_MMAP_APPRAISED	0x00008000
#घोषणा IMA_BPRM_APPRAISE	0x00010000
#घोषणा IMA_BPRM_APPRAISED	0x00020000
#घोषणा IMA_READ_APPRAISE	0x00040000
#घोषणा IMA_READ_APPRAISED	0x00080000
#घोषणा IMA_CREDS_APPRAISE	0x00100000
#घोषणा IMA_CREDS_APPRAISED	0x00200000
#घोषणा IMA_APPRAISE_SUBMASK	(IMA_खाता_APPRAISE | IMA_MMAP_APPRAISE | \
				 IMA_BPRM_APPRAISE | IMA_READ_APPRAISE | \
				 IMA_CREDS_APPRAISE)
#घोषणा IMA_APPRAISED_SUBMASK	(IMA_खाता_APPRAISED | IMA_MMAP_APPRAISED | \
				 IMA_BPRM_APPRAISED | IMA_READ_APPRAISED | \
				 IMA_CREDS_APPRAISED)

/* iपूर्णांक cache atomic_flags */
#घोषणा IMA_CHANGE_XATTR	0
#घोषणा IMA_UPDATE_XATTR	1
#घोषणा IMA_CHANGE_ATTR		2
#घोषणा IMA_DIGSIG		3
#घोषणा IMA_MUST_MEASURE	4

क्रमागत evm_ima_xattr_type अणु
	IMA_XATTR_DIGEST = 0x01,
	EVM_XATTR_HMAC,
	EVM_IMA_XATTR_DIGSIG,
	IMA_XATTR_DIGEST_NG,
	EVM_XATTR_PORTABLE_DIGSIG,
	IMA_XATTR_LAST
पूर्ण;

काष्ठा evm_ima_xattr_data अणु
	u8 type;
	u8 data[];
पूर्ण __packed;

/* Only used in the EVM HMAC code. */
काष्ठा evm_xattr अणु
	काष्ठा evm_ima_xattr_data data;
	u8 digest[SHA1_DIGEST_SIZE];
पूर्ण __packed;

#घोषणा IMA_MAX_DIGEST_SIZE	64

काष्ठा ima_digest_data अणु
	u8 algo;
	u8 length;
	जोड़ अणु
		काष्ठा अणु
			u8 unused;
			u8 type;
		पूर्ण sha1;
		काष्ठा अणु
			u8 type;
			u8 algo;
		पूर्ण ng;
		u8 data[2];
	पूर्ण xattr;
	u8 digest[];
पूर्ण __packed;

/*
 * signature क्रमmat v2 - क्रम using with asymmetric keys
 */
काष्ठा signature_v2_hdr अणु
	uपूर्णांक8_t type;		/* xattr type */
	uपूर्णांक8_t version;	/* signature क्रमmat version */
	uपूर्णांक8_t	hash_algo;	/* Digest algorithm [क्रमागत hash_algo] */
	__be32 keyid;		/* IMA key identअगरier - not X509/PGP specअगरic */
	__be16 sig_size;	/* signature size */
	uपूर्णांक8_t sig[];		/* signature payload */
पूर्ण __packed;

/* पूर्णांकegrity data associated with an inode */
काष्ठा पूर्णांकegrity_iपूर्णांक_cache अणु
	काष्ठा rb_node rb_node;	/* rooted in पूर्णांकegrity_iपूर्णांक_tree */
	काष्ठा mutex mutex;	/* protects: version, flags, digest */
	काष्ठा inode *inode;	/* back poपूर्णांकer to inode in question */
	u64 version;		/* track inode changes */
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ measured_pcrs;
	अचिन्हित दीर्घ atomic_flags;
	क्रमागत पूर्णांकegrity_status ima_file_status:4;
	क्रमागत पूर्णांकegrity_status ima_mmap_status:4;
	क्रमागत पूर्णांकegrity_status ima_bprm_status:4;
	क्रमागत पूर्णांकegrity_status ima_पढ़ो_status:4;
	क्रमागत पूर्णांकegrity_status ima_creds_status:4;
	क्रमागत पूर्णांकegrity_status evm_status:4;
	काष्ठा ima_digest_data *ima_hash;
पूर्ण;

/* rbtree tree calls to lookup, insert, delete
 * पूर्णांकegrity data associated with an inode.
 */
काष्ठा पूर्णांकegrity_iपूर्णांक_cache *पूर्णांकegrity_iपूर्णांक_find(काष्ठा inode *inode);

पूर्णांक पूर्णांकegrity_kernel_पढ़ो(काष्ठा file *file, loff_t offset,
			  व्योम *addr, अचिन्हित दीर्घ count);

#घोषणा INTEGRITY_KEYRING_EVM		0
#घोषणा INTEGRITY_KEYRING_IMA		1
#घोषणा INTEGRITY_KEYRING_PLATFORM	2
#घोषणा INTEGRITY_KEYRING_MAX		3

बाह्य काष्ठा dentry *पूर्णांकegrity_dir;

काष्ठा modsig;

#अगर_घोषित CONFIG_INTEGRITY_SIGNATURE

पूर्णांक पूर्णांकegrity_digsig_verअगरy(स्थिर अचिन्हित पूर्णांक id, स्थिर अक्षर *sig, पूर्णांक siglen,
			    स्थिर अक्षर *digest, पूर्णांक digestlen);
पूर्णांक पूर्णांकegrity_modsig_verअगरy(अचिन्हित पूर्णांक id, स्थिर काष्ठा modsig *modsig);

पूर्णांक __init पूर्णांकegrity_init_keyring(स्थिर अचिन्हित पूर्णांक id);
पूर्णांक __init पूर्णांकegrity_load_x509(स्थिर अचिन्हित पूर्णांक id, स्थिर अक्षर *path);
पूर्णांक __init पूर्णांकegrity_load_cert(स्थिर अचिन्हित पूर्णांक id, स्थिर अक्षर *source,
			       स्थिर व्योम *data, माप_प्रकार len, key_perm_t perm);
#अन्यथा

अटल अंतरभूत पूर्णांक पूर्णांकegrity_digsig_verअगरy(स्थिर अचिन्हित पूर्णांक id,
					  स्थिर अक्षर *sig, पूर्णांक siglen,
					  स्थिर अक्षर *digest, पूर्णांक digestlen)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक पूर्णांकegrity_modsig_verअगरy(अचिन्हित पूर्णांक id,
					  स्थिर काष्ठा modsig *modsig)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक पूर्णांकegrity_init_keyring(स्थिर अचिन्हित पूर्णांक id)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक __init पूर्णांकegrity_load_cert(स्थिर अचिन्हित पूर्णांक id,
					     स्थिर अक्षर *source,
					     स्थिर व्योम *data, माप_प्रकार len,
					     key_perm_t perm)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_INTEGRITY_SIGNATURE */

#अगर_घोषित CONFIG_INTEGRITY_ASYMMETRIC_KEYS
पूर्णांक asymmetric_verअगरy(काष्ठा key *keyring, स्थिर अक्षर *sig,
		      पूर्णांक siglen, स्थिर अक्षर *data, पूर्णांक datalen);
#अन्यथा
अटल अंतरभूत पूर्णांक asymmetric_verअगरy(काष्ठा key *keyring, स्थिर अक्षर *sig,
				    पूर्णांक siglen, स्थिर अक्षर *data, पूर्णांक datalen)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_IMA_APPRAISE_MODSIG
पूर्णांक ima_modsig_verअगरy(काष्ठा key *keyring, स्थिर काष्ठा modsig *modsig);
#अन्यथा
अटल अंतरभूत पूर्णांक ima_modsig_verअगरy(काष्ठा key *keyring,
				    स्थिर काष्ठा modsig *modsig)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_IMA_LOAD_X509
व्योम __init ima_load_x509(व्योम);
#अन्यथा
अटल अंतरभूत व्योम ima_load_x509(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_EVM_LOAD_X509
व्योम __init evm_load_x509(व्योम);
#अन्यथा
अटल अंतरभूत व्योम evm_load_x509(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_INTEGRITY_AUDIT
/* declarations */
व्योम पूर्णांकegrity_audit_msg(पूर्णांक audit_msgno, काष्ठा inode *inode,
			 स्थिर अचिन्हित अक्षर *fname, स्थिर अक्षर *op,
			 स्थिर अक्षर *cause, पूर्णांक result, पूर्णांक info);

व्योम पूर्णांकegrity_audit_message(पूर्णांक audit_msgno, काष्ठा inode *inode,
			     स्थिर अचिन्हित अक्षर *fname, स्थिर अक्षर *op,
			     स्थिर अक्षर *cause, पूर्णांक result, पूर्णांक info,
			     पूर्णांक त्रुटि_सं);

अटल अंतरभूत काष्ठा audit_buffer *
पूर्णांकegrity_audit_log_start(काष्ठा audit_context *ctx, gfp_t gfp_mask, पूर्णांक type)
अणु
	वापस audit_log_start(ctx, gfp_mask, type);
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम पूर्णांकegrity_audit_msg(पूर्णांक audit_msgno, काष्ठा inode *inode,
				       स्थिर अचिन्हित अक्षर *fname,
				       स्थिर अक्षर *op, स्थिर अक्षर *cause,
				       पूर्णांक result, पूर्णांक info)
अणु
पूर्ण

अटल अंतरभूत व्योम पूर्णांकegrity_audit_message(पूर्णांक audit_msgno,
					   काष्ठा inode *inode,
					   स्थिर अचिन्हित अक्षर *fname,
					   स्थिर अक्षर *op, स्थिर अक्षर *cause,
					   पूर्णांक result, पूर्णांक info, पूर्णांक त्रुटि_सं)
अणु
पूर्ण

अटल अंतरभूत काष्ठा audit_buffer *
पूर्णांकegrity_audit_log_start(काष्ठा audit_context *ctx, gfp_t gfp_mask, पूर्णांक type)
अणु
	वापस शून्य;
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_INTEGRITY_PLATFORM_KEYRING
व्योम __init add_to_platक्रमm_keyring(स्थिर अक्षर *source, स्थिर व्योम *data,
				    माप_प्रकार len);
#अन्यथा
अटल अंतरभूत व्योम __init add_to_platक्रमm_keyring(स्थिर अक्षर *source,
						  स्थिर व्योम *data, माप_प्रकार len)
अणु
पूर्ण
#पूर्ण_अगर
