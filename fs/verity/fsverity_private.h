<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * fs-verity: पढ़ो-only file-based authenticity protection
 *
 * Copyright 2019 Google LLC
 */

#अगर_अघोषित _FSVERITY_PRIVATE_H
#घोषणा _FSVERITY_PRIVATE_H

#अगर_घोषित CONFIG_FS_VERITY_DEBUG
#घोषणा DEBUG
#पूर्ण_अगर

#घोषणा pr_fmt(fmt) "fs-verity: " fmt

#समावेश <crypto/sha2.h>
#समावेश <linux/fsverity.h>
#समावेश <linux/mempool.h>

काष्ठा ahash_request;

/*
 * Implementation limit: maximum depth of the Merkle tree.  For now 8 is plenty;
 * it's enough क्रम over U64_MAX bytes of data using SHA-256 and 4K blocks.
 */
#घोषणा FS_VERITY_MAX_LEVELS		8

/*
 * Largest digest size among all hash algorithms supported by fs-verity.
 * Currently assumed to be <= size of fsverity_descriptor::root_hash.
 */
#घोषणा FS_VERITY_MAX_DIGEST_SIZE	SHA512_DIGEST_SIZE

/* A hash algorithm supported by fs-verity */
काष्ठा fsverity_hash_alg अणु
	काष्ठा crypto_ahash *tfm; /* hash tfm, allocated on demand */
	स्थिर अक्षर *name;	  /* crypto API name, e.g. sha256 */
	अचिन्हित पूर्णांक digest_size; /* digest size in bytes, e.g. 32 क्रम SHA-256 */
	अचिन्हित पूर्णांक block_size;  /* block size in bytes, e.g. 64 क्रम SHA-256 */
	mempool_t req_pool;	  /* mempool with a pपुनः_स्मृतिated hash request */
पूर्ण;

/* Merkle tree parameters: hash algorithm, initial hash state, and topology */
काष्ठा merkle_tree_params अणु
	काष्ठा fsverity_hash_alg *hash_alg; /* the hash algorithm */
	स्थिर u8 *hashstate;		/* initial hash state or शून्य */
	अचिन्हित पूर्णांक digest_size;	/* same as hash_alg->digest_size */
	अचिन्हित पूर्णांक block_size;	/* size of data and tree blocks */
	अचिन्हित पूर्णांक hashes_per_block;	/* number of hashes per tree block */
	अचिन्हित पूर्णांक log_blocksize;	/* log2(block_size) */
	अचिन्हित पूर्णांक log_arity;		/* log2(hashes_per_block) */
	अचिन्हित पूर्णांक num_levels;	/* number of levels in Merkle tree */
	u64 tree_size;			/* Merkle tree size in bytes */
	अचिन्हित दीर्घ level0_blocks;	/* number of blocks in tree level 0 */

	/*
	 * Starting block index क्रम each tree level, ordered from leaf level (0)
	 * to root level ('num_levels - 1')
	 */
	u64 level_start[FS_VERITY_MAX_LEVELS];
पूर्ण;

/*
 * fsverity_info - cached verity metadata क्रम an inode
 *
 * When a verity file is first खोलोed, an instance of this काष्ठा is allocated
 * and stored in ->i_verity_info; it reमुख्यs until the inode is evicted.  It
 * caches inक्रमmation about the Merkle tree that's needed to efficiently verअगरy
 * data पढ़ो from the file.  It also caches the file digest.  The Merkle tree
 * pages themselves are not cached here, but the fileप्रणाली may cache them.
 */
काष्ठा fsverity_info अणु
	काष्ठा merkle_tree_params tree_params;
	u8 root_hash[FS_VERITY_MAX_DIGEST_SIZE];
	u8 file_digest[FS_VERITY_MAX_DIGEST_SIZE];
	स्थिर काष्ठा inode *inode;
पूर्ण;

/* Arbitrary limit to bound the kदो_स्मृति() size.  Can be changed. */
#घोषणा FS_VERITY_MAX_DESCRIPTOR_SIZE	16384

#घोषणा FS_VERITY_MAX_SIGNATURE_SIZE	(FS_VERITY_MAX_DESCRIPTOR_SIZE - \
					 माप(काष्ठा fsverity_descriptor))

/* hash_algs.c */

बाह्य काष्ठा fsverity_hash_alg fsverity_hash_algs[];

काष्ठा fsverity_hash_alg *fsverity_get_hash_alg(स्थिर काष्ठा inode *inode,
						अचिन्हित पूर्णांक num);
काष्ठा ahash_request *fsverity_alloc_hash_request(काष्ठा fsverity_hash_alg *alg,
						  gfp_t gfp_flags);
व्योम fsverity_मुक्त_hash_request(काष्ठा fsverity_hash_alg *alg,
				काष्ठा ahash_request *req);
स्थिर u8 *fsverity_prepare_hash_state(काष्ठा fsverity_hash_alg *alg,
				      स्थिर u8 *salt, माप_प्रकार salt_size);
पूर्णांक fsverity_hash_page(स्थिर काष्ठा merkle_tree_params *params,
		       स्थिर काष्ठा inode *inode,
		       काष्ठा ahash_request *req, काष्ठा page *page, u8 *out);
पूर्णांक fsverity_hash_buffer(काष्ठा fsverity_hash_alg *alg,
			 स्थिर व्योम *data, माप_प्रकार size, u8 *out);
व्योम __init fsverity_check_hash_algs(व्योम);

/* init.c */

व्योम __म_लिखो(3, 4) __cold
fsverity_msg(स्थिर काष्ठा inode *inode, स्थिर अक्षर *level,
	     स्थिर अक्षर *fmt, ...);

#घोषणा fsverity_warn(inode, fmt, ...)		\
	fsverity_msg((inode), KERN_WARNING, fmt, ##__VA_ARGS__)
#घोषणा fsverity_err(inode, fmt, ...)		\
	fsverity_msg((inode), KERN_ERR, fmt, ##__VA_ARGS__)

/* खोलो.c */

पूर्णांक fsverity_init_merkle_tree_params(काष्ठा merkle_tree_params *params,
				     स्थिर काष्ठा inode *inode,
				     अचिन्हित पूर्णांक hash_algorithm,
				     अचिन्हित पूर्णांक log_blocksize,
				     स्थिर u8 *salt, माप_प्रकार salt_size);

काष्ठा fsverity_info *fsverity_create_info(स्थिर काष्ठा inode *inode,
					   काष्ठा fsverity_descriptor *desc,
					   माप_प्रकार desc_size);

व्योम fsverity_set_info(काष्ठा inode *inode, काष्ठा fsverity_info *vi);

व्योम fsverity_मुक्त_info(काष्ठा fsverity_info *vi);

पूर्णांक fsverity_get_descriptor(काष्ठा inode *inode,
			    काष्ठा fsverity_descriptor **desc_ret,
			    माप_प्रकार *desc_size_ret);

पूर्णांक __init fsverity_init_info_cache(व्योम);
व्योम __init fsverity_निकास_info_cache(व्योम);

/* signature.c */

#अगर_घोषित CONFIG_FS_VERITY_BUILTIN_SIGNATURES
पूर्णांक fsverity_verअगरy_signature(स्थिर काष्ठा fsverity_info *vi,
			      स्थिर u8 *signature, माप_प्रकार sig_size);

पूर्णांक __init fsverity_init_signature(व्योम);
#अन्यथा /* !CONFIG_FS_VERITY_BUILTIN_SIGNATURES */
अटल अंतरभूत पूर्णांक
fsverity_verअगरy_signature(स्थिर काष्ठा fsverity_info *vi,
			  स्थिर u8 *signature, माप_प्रकार sig_size)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक fsverity_init_signature(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* !CONFIG_FS_VERITY_BUILTIN_SIGNATURES */

/* verअगरy.c */

पूर्णांक __init fsverity_init_workqueue(व्योम);
व्योम __init fsverity_निकास_workqueue(व्योम);

#पूर्ण_अगर /* _FSVERITY_PRIVATE_H */
