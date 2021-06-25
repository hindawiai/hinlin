<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __NX_H__
#घोषणा __NX_H__

#समावेश <crypto/ctr.h>

#घोषणा NX_NAME		"nx-crypto"
#घोषणा NX_STRING	"IBM Power7+ Nest Accelerator Crypto Driver"
#घोषणा NX_VERSION	"1.0"

/* a scatterlist in the क्रमmat PHYP is expecting */
काष्ठा nx_sg अणु
	u64 addr;
	u32 rsvd;
	u32 len;
पूर्ण __attribute((packed));

#घोषणा NX_PAGE_SIZE		(4096)
#घोषणा NX_MAX_SG_ENTRIES	(NX_PAGE_SIZE/(माप(काष्ठा nx_sg)))

क्रमागत nx_status अणु
	NX_DISABLED,
	NX_WAITING,
	NX_OKAY
पूर्ण;

/* msc_triplet and max_sync_cop are used only to assist in parsing the
 * खोलोFirmware property */
काष्ठा msc_triplet अणु
	u32 keybitlen;
	u32 databytelen;
	u32 sglen;
पूर्ण __packed;

काष्ठा max_sync_cop अणु
	u32 fc;
	u32 mode;
	u32 triplets;
	काष्ठा msc_triplet trip[];
पूर्ण __packed;

काष्ठा alg_props अणु
	u32 databytelen;
	u32 sglen;
पूर्ण;

#घोषणा NX_OF_FLAG_MAXSGLEN_SET		(1)
#घोषणा NX_OF_FLAG_STATUS_SET		(2)
#घोषणा NX_OF_FLAG_MAXSYNCCOP_SET	(4)
#घोषणा NX_OF_FLAG_MASK_READY		(NX_OF_FLAG_MAXSGLEN_SET | \
					 NX_OF_FLAG_STATUS_SET |   \
					 NX_OF_FLAG_MAXSYNCCOP_SET)
काष्ठा nx_of अणु
	u32 flags;
	u32 max_sg_len;
	क्रमागत nx_status status;
	काष्ठा alg_props ap[NX_MAX_FC][NX_MAX_MODE][3];
पूर्ण;

काष्ठा nx_stats अणु
	atomic_t aes_ops;
	atomic64_t aes_bytes;
	atomic_t sha256_ops;
	atomic64_t sha256_bytes;
	atomic_t sha512_ops;
	atomic64_t sha512_bytes;

	atomic_t sync_ops;

	atomic_t errors;
	atomic_t last_error;
	atomic_t last_error_pid;
पूर्ण;

काष्ठा nx_crypto_driver अणु
	काष्ठा nx_stats    stats;
	काष्ठा nx_of       of;
	काष्ठा vio_dev    *viodev;
	काष्ठा vio_driver  viodriver;
	काष्ठा dentry     *dfs_root;
पूर्ण;

#घोषणा NX_GCM4106_NONCE_LEN		(4)
#घोषणा NX_GCM_CTR_OFFSET		(12)
काष्ठा nx_gcm_rctx अणु
	u8 iv[16];
पूर्ण;

काष्ठा nx_gcm_priv अणु
	u8 iauth_tag[16];
	u8 nonce[NX_GCM4106_NONCE_LEN];
पूर्ण;

#घोषणा NX_CCM_AES_KEY_LEN		(16)
#घोषणा NX_CCM4309_AES_KEY_LEN		(19)
#घोषणा NX_CCM4309_NONCE_LEN		(3)
काष्ठा nx_ccm_rctx अणु
	u8 iv[16];
पूर्ण;

काष्ठा nx_ccm_priv अणु
	u8 b0[16];
	u8 iauth_tag[16];
	u8 oauth_tag[16];
	u8 nonce[NX_CCM4309_NONCE_LEN];
पूर्ण;

काष्ठा nx_xcbc_priv अणु
	u8 key[16];
पूर्ण;

काष्ठा nx_ctr_priv अणु
	u8 nonce[CTR_RFC3686_NONCE_SIZE];
पूर्ण;

काष्ठा nx_crypto_ctx अणु
	spinlock_t lock;	  /* synchronize access to the context */
	व्योम *kmem;		  /* unaligned, kदो_स्मृति'd buffer */
	माप_प्रकार kmem_len;	  /* length of kmem */
	काष्ठा nx_csbcpb *csbcpb; /* aligned page given to phyp @ hcall समय */
	काष्ठा vio_pfo_op op;     /* operation काष्ठा with hcall parameters */
	काष्ठा nx_csbcpb *csbcpb_aead; /* secondary csbcpb used by AEAD algs */
	काष्ठा vio_pfo_op op_aead;/* operation काष्ठा क्रम csbcpb_aead */

	काष्ठा nx_sg *in_sg;      /* aligned poपूर्णांकer पूर्णांकo kmem to an sg list */
	काष्ठा nx_sg *out_sg;     /* aligned poपूर्णांकer पूर्णांकo kmem to an sg list */

	काष्ठा alg_props *ap;	  /* poपूर्णांकer पूर्णांकo props based on our key size */
	काष्ठा alg_props props[3];/* खोलोFirmware properties क्रम requests */
	काष्ठा nx_stats *stats;   /* poपूर्णांकer पूर्णांकo an nx_crypto_driver क्रम stats
				     reporting */

	जोड़ अणु
		काष्ठा nx_gcm_priv gcm;
		काष्ठा nx_ccm_priv ccm;
		काष्ठा nx_xcbc_priv xcbc;
		काष्ठा nx_ctr_priv ctr;
	पूर्ण priv;
पूर्ण;

काष्ठा crypto_aead;

/* prototypes */
पूर्णांक nx_crypto_ctx_aes_ccm_init(काष्ठा crypto_aead *tfm);
पूर्णांक nx_crypto_ctx_aes_gcm_init(काष्ठा crypto_aead *tfm);
पूर्णांक nx_crypto_ctx_aes_xcbc_init(काष्ठा crypto_tfm *tfm);
पूर्णांक nx_crypto_ctx_aes_ctr_init(काष्ठा crypto_skcipher *tfm);
पूर्णांक nx_crypto_ctx_aes_cbc_init(काष्ठा crypto_skcipher *tfm);
पूर्णांक nx_crypto_ctx_aes_ecb_init(काष्ठा crypto_skcipher *tfm);
पूर्णांक nx_crypto_ctx_sha_init(काष्ठा crypto_tfm *tfm);
व्योम nx_crypto_ctx_निकास(काष्ठा crypto_tfm *tfm);
व्योम nx_crypto_ctx_skcipher_निकास(काष्ठा crypto_skcipher *tfm);
व्योम nx_crypto_ctx_aead_निकास(काष्ठा crypto_aead *tfm);
व्योम nx_ctx_init(काष्ठा nx_crypto_ctx *nx_ctx, अचिन्हित पूर्णांक function);
पूर्णांक nx_hcall_sync(काष्ठा nx_crypto_ctx *ctx, काष्ठा vio_pfo_op *op,
		  u32 may_sleep);
काष्ठा nx_sg *nx_build_sg_list(काष्ठा nx_sg *, u8 *, अचिन्हित पूर्णांक *, u32);
पूर्णांक nx_build_sg_lists(काष्ठा nx_crypto_ctx *nx_ctx, स्थिर u8 *iv,
		      काष्ठा scatterlist *dst, काष्ठा scatterlist *src,
		      अचिन्हित पूर्णांक *nbytes, अचिन्हित पूर्णांक offset, u8 *oiv);
काष्ठा nx_sg *nx_walk_and_build(काष्ठा nx_sg *, अचिन्हित पूर्णांक,
				काष्ठा scatterlist *, अचिन्हित पूर्णांक,
				अचिन्हित पूर्णांक *);

#अगर_घोषित CONFIG_DEBUG_FS
#घोषणा NX_DEBUGFS_INIT(drv)	nx_debugfs_init(drv)
#घोषणा NX_DEBUGFS_FINI(drv)	nx_debugfs_fini(drv)

व्योम nx_debugfs_init(काष्ठा nx_crypto_driver *);
व्योम nx_debugfs_fini(काष्ठा nx_crypto_driver *);
#अन्यथा
#घोषणा NX_DEBUGFS_INIT(drv)	(0)
#घोषणा NX_DEBUGFS_FINI(drv)	(0)
#पूर्ण_अगर

#घोषणा NX_PAGE_NUM(x)		((u64)(x) & 0xfffffffffffff000ULL)

बाह्य काष्ठा skcipher_alg nx_cbc_aes_alg;
बाह्य काष्ठा skcipher_alg nx_ecb_aes_alg;
बाह्य काष्ठा aead_alg nx_gcm_aes_alg;
बाह्य काष्ठा aead_alg nx_gcm4106_aes_alg;
बाह्य काष्ठा skcipher_alg nx_ctr3686_aes_alg;
बाह्य काष्ठा aead_alg nx_ccm_aes_alg;
बाह्य काष्ठा aead_alg nx_ccm4309_aes_alg;
बाह्य काष्ठा shash_alg nx_shash_aes_xcbc_alg;
बाह्य काष्ठा shash_alg nx_shash_sha512_alg;
बाह्य काष्ठा shash_alg nx_shash_sha256_alg;

बाह्य काष्ठा nx_crypto_driver nx_driver;

#घोषणा SCATTERWALK_TO_SG	1
#घोषणा SCATTERWALK_FROM_SG	0

#पूर्ण_अगर
