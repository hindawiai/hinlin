<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2012-2019 ARM Limited (or its affiliates). */

/* \पile cc_driver.h
 * ARM CryptoCell Linux Crypto Driver
 */

#अगर_अघोषित __CC_DRIVER_H__
#घोषणा __CC_DRIVER_H__

#अगर_घोषित COMP_IN_WQ
#समावेश <linux/workqueue.h>
#अन्यथा
#समावेश <linux/पूर्णांकerrupt.h>
#पूर्ण_अगर
#समावेश <linux/dma-mapping.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/aead.h>
#समावेश <crypto/authenc.h>
#समावेश <crypto/hash.h>
#समावेश <crypto/skcipher.h>
#समावेश <linux/clk.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "cc_host_regs.h"
#समावेश "cc_crypto_ctx.h"
#समावेश "cc_hw_queue_defs.h"
#समावेश "cc_sram_mgr.h"

बाह्य bool cc_dump_desc;
बाह्य bool cc_dump_bytes;

#घोषणा DRV_MODULE_VERSION "5.0"

क्रमागत cc_hw_rev अणु
	CC_HW_REV_630 = 630,
	CC_HW_REV_710 = 710,
	CC_HW_REV_712 = 712,
	CC_HW_REV_713 = 713
पूर्ण;

क्रमागत cc_std_body अणु
	CC_STD_NIST = 0x1,
	CC_STD_OSCCA = 0x2,
	CC_STD_ALL = 0x3
पूर्ण;

#घोषणा CC_PINS_FULL	0x0
#घोषणा CC_PINS_SLIM	0x9F

/* Maximum DMA mask supported by IP */
#घोषणा DMA_BIT_MASK_LEN 48

#घोषणा CC_AXI_IRQ_MASK ((1 << CC_AXIM_CFG_BRESPMASK_BIT_SHIFT) | \
			  (1 << CC_AXIM_CFG_RRESPMASK_BIT_SHIFT) | \
			  (1 << CC_AXIM_CFG_INFLTMASK_BIT_SHIFT) | \
			  (1 << CC_AXIM_CFG_COMPMASK_BIT_SHIFT))

#घोषणा CC_AXI_ERR_IRQ_MASK BIT(CC_HOST_IRR_AXI_ERR_INT_BIT_SHIFT)

#घोषणा CC_COMP_IRQ_MASK BIT(CC_HOST_IRR_AXIM_COMP_INT_BIT_SHIFT)

#घोषणा CC_SECURITY_DISABLED_MASK BIT(CC_SECURITY_DISABLED_VALUE_BIT_SHIFT)

#घोषणा CC_NVM_IS_IDLE_MASK BIT(CC_NVM_IS_IDLE_VALUE_BIT_SHIFT)

#घोषणा AXIM_MON_COMP_VALUE CC_GENMASK(CC_AXIM_MON_COMP_VALUE)

#घोषणा CC_CPP_AES_ABORT_MASK ( \
	BIT(CC_HOST_IMR_REE_OP_ABORTED_AES_0_MASK_BIT_SHIFT) | \
	BIT(CC_HOST_IMR_REE_OP_ABORTED_AES_1_MASK_BIT_SHIFT) | \
	BIT(CC_HOST_IMR_REE_OP_ABORTED_AES_2_MASK_BIT_SHIFT) | \
	BIT(CC_HOST_IMR_REE_OP_ABORTED_AES_3_MASK_BIT_SHIFT) | \
	BIT(CC_HOST_IMR_REE_OP_ABORTED_AES_4_MASK_BIT_SHIFT) | \
	BIT(CC_HOST_IMR_REE_OP_ABORTED_AES_5_MASK_BIT_SHIFT) | \
	BIT(CC_HOST_IMR_REE_OP_ABORTED_AES_6_MASK_BIT_SHIFT) | \
	BIT(CC_HOST_IMR_REE_OP_ABORTED_AES_7_MASK_BIT_SHIFT))

#घोषणा CC_CPP_SM4_ABORT_MASK ( \
	BIT(CC_HOST_IMR_REE_OP_ABORTED_SM_0_MASK_BIT_SHIFT) | \
	BIT(CC_HOST_IMR_REE_OP_ABORTED_SM_1_MASK_BIT_SHIFT) | \
	BIT(CC_HOST_IMR_REE_OP_ABORTED_SM_2_MASK_BIT_SHIFT) | \
	BIT(CC_HOST_IMR_REE_OP_ABORTED_SM_3_MASK_BIT_SHIFT) | \
	BIT(CC_HOST_IMR_REE_OP_ABORTED_SM_4_MASK_BIT_SHIFT) | \
	BIT(CC_HOST_IMR_REE_OP_ABORTED_SM_5_MASK_BIT_SHIFT) | \
	BIT(CC_HOST_IMR_REE_OP_ABORTED_SM_6_MASK_BIT_SHIFT) | \
	BIT(CC_HOST_IMR_REE_OP_ABORTED_SM_7_MASK_BIT_SHIFT))

/* Register name mangling macro */
#घोषणा CC_REG(reg_name) CC_ ## reg_name ## _REG_OFFSET

/* TEE FIPS status पूर्णांकerrupt */
#घोषणा CC_GPR0_IRQ_MASK BIT(CC_HOST_IRR_GPR0_BIT_SHIFT)

#घोषणा CC_CRA_PRIO 400

#घोषणा MIN_HW_QUEUE_SIZE 50 /* Minimum size required क्रम proper function */

#घोषणा MAX_REQUEST_QUEUE_SIZE 4096
#घोषणा MAX_MLLI_BUFF_SIZE 2080

/* Definitions क्रम HW descriptors DIN/DOUT fields */
#घोषणा NS_BIT 1
#घोषणा AXI_ID 0
/* AXI_ID is not actually the AXI ID of the transaction but the value of AXI_ID
 * field in the HW descriptor. The DMA engine +8 that value.
 */

काष्ठा cc_cpp_req अणु
	bool is_cpp;
	क्रमागत cc_cpp_alg alg;
	u8 slot;
पूर्ण;

#घोषणा CC_MAX_IVGEN_DMA_ADDRESSES	3
काष्ठा cc_crypto_req अणु
	व्योम (*user_cb)(काष्ठा device *dev, व्योम *req, पूर्णांक err);
	व्योम *user_arg;
	काष्ठा completion seq_compl; /* request completion */
	काष्ठा cc_cpp_req cpp;
पूर्ण;

/**
 * काष्ठा cc_drvdata - driver निजी data context
 * @cc_base:	virt address of the CC रेजिस्टरs
 * @irq:	biपंचांगap indicating source of last पूर्णांकerrupt
 */
काष्ठा cc_drvdata अणु
	व्योम __iomem *cc_base;
	पूर्णांक irq;
	काष्ठा completion hw_queue_avail; /* रुको क्रम HW queue availability */
	काष्ठा platक्रमm_device *plat_dev;
	u32 mlli_sram_addr;
	काष्ठा dma_pool *mlli_buffs_pool;
	काष्ठा list_head alg_list;
	व्योम *hash_handle;
	व्योम *aead_handle;
	व्योम *request_mgr_handle;
	व्योम *fips_handle;
	u32 sram_मुक्त_offset;	/* offset to non-allocated area in SRAM */
	काष्ठा dentry *dir;	/* क्रम debugfs */
	काष्ठा clk *clk;
	bool coherent;
	अक्षर *hw_rev_name;
	क्रमागत cc_hw_rev hw_rev;
	u32 axim_mon_offset;
	u32 sig_offset;
	u32 ver_offset;
	पूर्णांक std_bodies;
	bool sec_disabled;
	u32 comp_mask;
	u32 cache_params;
	u32 ace_स्थिर;
पूर्ण;

काष्ठा cc_crypto_alg अणु
	काष्ठा list_head entry;
	पूर्णांक cipher_mode;
	पूर्णांक flow_mode; /* Note: currently, refers to the cipher mode only. */
	पूर्णांक auth_mode;
	काष्ठा cc_drvdata *drvdata;
	काष्ठा skcipher_alg skcipher_alg;
	काष्ठा aead_alg aead_alg;
पूर्ण;

काष्ठा cc_alg_ढाँचा अणु
	अक्षर name[CRYPTO_MAX_ALG_NAME];
	अक्षर driver_name[CRYPTO_MAX_ALG_NAME];
	अचिन्हित पूर्णांक blocksize;
	जोड़ अणु
		काष्ठा skcipher_alg skcipher;
		काष्ठा aead_alg aead;
	पूर्ण ढाँचा_u;
	पूर्णांक cipher_mode;
	पूर्णांक flow_mode; /* Note: currently, refers to the cipher mode only. */
	पूर्णांक auth_mode;
	u32 min_hw_rev;
	क्रमागत cc_std_body std_body;
	bool sec_func;
	अचिन्हित पूर्णांक data_unit;
	काष्ठा cc_drvdata *drvdata;
पूर्ण;

काष्ठा async_gen_req_ctx अणु
	dma_addr_t iv_dma_addr;
	u8 *iv;
	क्रमागत drv_crypto_direction op_type;
पूर्ण;

अटल अंतरभूत काष्ठा device *drvdata_to_dev(काष्ठा cc_drvdata *drvdata)
अणु
	वापस &drvdata->plat_dev->dev;
पूर्ण

व्योम __dump_byte_array(स्थिर अक्षर *name, स्थिर u8 *buf, माप_प्रकार len);
अटल अंतरभूत व्योम dump_byte_array(स्थिर अक्षर *name, स्थिर u8 *the_array,
				   माप_प्रकार size)
अणु
	अगर (cc_dump_bytes)
		__dump_byte_array(name, the_array, size);
पूर्ण

bool cc_रुको_क्रम_reset_completion(काष्ठा cc_drvdata *drvdata);
पूर्णांक init_cc_regs(काष्ठा cc_drvdata *drvdata);
व्योम fini_cc_regs(काष्ठा cc_drvdata *drvdata);
अचिन्हित पूर्णांक cc_get_शेष_hash_len(काष्ठा cc_drvdata *drvdata);

अटल अंतरभूत व्योम cc_ioग_लिखो(काष्ठा cc_drvdata *drvdata, u32 reg, u32 val)
अणु
	ioग_लिखो32(val, (drvdata->cc_base + reg));
पूर्ण

अटल अंतरभूत u32 cc_ioपढ़ो(काष्ठा cc_drvdata *drvdata, u32 reg)
अणु
	वापस ioपढ़ो32(drvdata->cc_base + reg);
पूर्ण

अटल अंतरभूत gfp_t cc_gfp_flags(काष्ठा crypto_async_request *req)
अणु
	वापस (req->flags & CRYPTO_TFM_REQ_MAY_SLEEP) ?
			GFP_KERNEL : GFP_ATOMIC;
पूर्ण

अटल अंतरभूत व्योम set_queue_last_ind(काष्ठा cc_drvdata *drvdata,
				      काष्ठा cc_hw_desc *pdesc)
अणु
	अगर (drvdata->hw_rev >= CC_HW_REV_712)
		set_queue_last_ind_bit(pdesc);
पूर्ण

#पूर्ण_अगर /*__CC_DRIVER_H__*/
