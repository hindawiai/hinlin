<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2015, The Linux Foundation. All rights reserved.
 */
#अगर_अघोषित LINUX_MMC_CQHCI_H
#घोषणा LINUX_MMC_CQHCI_H

#समावेश <linux/compiler.h>
#समावेश <linux/bitops.h>
#समावेश <linux/spinlock_types.h>
#समावेश <linux/types.h>
#समावेश <linux/completion.h>
#समावेश <linux/रुको.h>
#समावेश <linux/irqवापस.h>
#समावेश <यंत्र/पन.स>

/* रेजिस्टरs */
/* version */
#घोषणा CQHCI_VER			0x00
#घोषणा CQHCI_VER_MAJOR(x)		(((x) & GENMASK(11, 8)) >> 8)
#घोषणा CQHCI_VER_MINOR1(x)		(((x) & GENMASK(7, 4)) >> 4)
#घोषणा CQHCI_VER_MINOR2(x)		((x) & GENMASK(3, 0))

/* capabilities */
#घोषणा CQHCI_CAP			0x04
#घोषणा CQHCI_CAP_CS			0x10000000 /* Crypto Support */

/* configuration */
#घोषणा CQHCI_CFG			0x08
#घोषणा CQHCI_DCMD			0x00001000
#घोषणा CQHCI_TASK_DESC_SZ		0x00000100
#घोषणा CQHCI_CRYPTO_GENERAL_ENABLE	0x00000002
#घोषणा CQHCI_ENABLE			0x00000001

/* control */
#घोषणा CQHCI_CTL			0x0C
#घोषणा CQHCI_CLEAR_ALL_TASKS		0x00000100
#घोषणा CQHCI_HALT			0x00000001

/* पूर्णांकerrupt status */
#घोषणा CQHCI_IS			0x10
#घोषणा CQHCI_IS_HAC			BIT(0)
#घोषणा CQHCI_IS_TCC			BIT(1)
#घोषणा CQHCI_IS_RED			BIT(2)
#घोषणा CQHCI_IS_TCL			BIT(3)
#घोषणा CQHCI_IS_GCE			BIT(4) /* General Crypto Error */
#घोषणा CQHCI_IS_ICCE			BIT(5) /* Invalid Crypto Config Error */

#घोषणा CQHCI_IS_MASK (CQHCI_IS_TCC | CQHCI_IS_RED | \
		       CQHCI_IS_GCE | CQHCI_IS_ICCE)

/* पूर्णांकerrupt status enable */
#घोषणा CQHCI_ISTE			0x14

/* पूर्णांकerrupt संकेत enable */
#घोषणा CQHCI_ISGE			0x18

/* पूर्णांकerrupt coalescing */
#घोषणा CQHCI_IC			0x1C
#घोषणा CQHCI_IC_ENABLE			BIT(31)
#घोषणा CQHCI_IC_RESET			BIT(16)
#घोषणा CQHCI_IC_ICCTHWEN		BIT(15)
#घोषणा CQHCI_IC_ICCTH(x)		(((x) & 0x1F) << 8)
#घोषणा CQHCI_IC_ICTOVALWEN		BIT(7)
#घोषणा CQHCI_IC_ICTOVAL(x)		((x) & 0x7F)

/* task list base address */
#घोषणा CQHCI_TDLBA			0x20

/* task list base address upper */
#घोषणा CQHCI_TDLBAU			0x24

/* करोor-bell */
#घोषणा CQHCI_TDBR			0x28

/* task completion notअगरication */
#घोषणा CQHCI_TCN			0x2C

/* device queue status */
#घोषणा CQHCI_DQS			0x30

/* device pending tasks */
#घोषणा CQHCI_DPT			0x34

/* task clear */
#घोषणा CQHCI_TCLR			0x38

/* task descriptor processing error */
#घोषणा CQHCI_TDPE			0x3c

/* send status config 1 */
#घोषणा CQHCI_SSC1			0x40
#घोषणा CQHCI_SSC1_CBC_MASK		GENMASK(19, 16)

/* send status config 2 */
#घोषणा CQHCI_SSC2			0x44

/* response क्रम dcmd */
#घोषणा CQHCI_CRDCT			0x48

/* response mode error mask */
#घोषणा CQHCI_RMEM			0x50

/* task error info */
#घोषणा CQHCI_TERRI			0x54

#घोषणा CQHCI_TERRI_C_INDEX(x)		((x) & GENMASK(5, 0))
#घोषणा CQHCI_TERRI_C_TASK(x)		(((x) & GENMASK(12, 8)) >> 8)
#घोषणा CQHCI_TERRI_C_VALID(x)		((x) & BIT(15))
#घोषणा CQHCI_TERRI_D_INDEX(x)		(((x) & GENMASK(21, 16)) >> 16)
#घोषणा CQHCI_TERRI_D_TASK(x)		(((x) & GENMASK(28, 24)) >> 24)
#घोषणा CQHCI_TERRI_D_VALID(x)		((x) & BIT(31))

/* command response index */
#घोषणा CQHCI_CRI			0x58

/* command response argument */
#घोषणा CQHCI_CRA			0x5C

/* crypto capabilities */
#घोषणा CQHCI_CCAP			0x100
#घोषणा CQHCI_CRYPTOCAP			0x104

#घोषणा CQHCI_INT_ALL			0xF
#घोषणा CQHCI_IC_DEFAULT_ICCTH		31
#घोषणा CQHCI_IC_DEFAULT_ICTOVAL	1

/* attribute fields */
#घोषणा CQHCI_VALID(x)			(((x) & 1) << 0)
#घोषणा CQHCI_END(x)			(((x) & 1) << 1)
#घोषणा CQHCI_INT(x)			(((x) & 1) << 2)
#घोषणा CQHCI_ACT(x)			(((x) & 0x7) << 3)

/* data command task descriptor fields */
#घोषणा CQHCI_FORCED_PROG(x)		(((x) & 1) << 6)
#घोषणा CQHCI_CONTEXT(x)		(((x) & 0xF) << 7)
#घोषणा CQHCI_DATA_TAG(x)		(((x) & 1) << 11)
#घोषणा CQHCI_DATA_सूची(x)		(((x) & 1) << 12)
#घोषणा CQHCI_PRIORITY(x)		(((x) & 1) << 13)
#घोषणा CQHCI_QBAR(x)			(((x) & 1) << 14)
#घोषणा CQHCI_REL_WRITE(x)		(((x) & 1) << 15)
#घोषणा CQHCI_BLK_COUNT(x)		(((x) & 0xFFFF) << 16)
#घोषणा CQHCI_BLK_ADDR(x)		(((x) & 0xFFFFFFFF) << 32)

/* direct command task descriptor fields */
#घोषणा CQHCI_CMD_INDEX(x)		(((x) & 0x3F) << 16)
#घोषणा CQHCI_CMD_TIMING(x)		(((x) & 1) << 22)
#घोषणा CQHCI_RESP_TYPE(x)		(((x) & 0x3) << 23)

/* crypto task descriptor fields (क्रम bits 64-127 of task descriptor) */
#घोषणा CQHCI_CRYPTO_ENABLE_BIT		(1ULL << 47)
#घोषणा CQHCI_CRYPTO_KEYSLOT(x)		((u64)(x) << 32)

/* transfer descriptor fields */
#घोषणा CQHCI_DAT_LENGTH(x)		(((x) & 0xFFFF) << 16)
#घोषणा CQHCI_DAT_ADDR_LO(x)		(((x) & 0xFFFFFFFF) << 32)
#घोषणा CQHCI_DAT_ADDR_HI(x)		(((x) & 0xFFFFFFFF) << 0)

/* CCAP - Crypto Capability 100h */
जोड़ cqhci_crypto_capabilities अणु
	__le32 reg_val;
	काष्ठा अणु
		u8 num_crypto_cap;
		u8 config_count;
		u8 reserved;
		u8 config_array_ptr;
	पूर्ण;
पूर्ण;

क्रमागत cqhci_crypto_key_size अणु
	CQHCI_CRYPTO_KEY_SIZE_INVALID	= 0,
	CQHCI_CRYPTO_KEY_SIZE_128	= 1,
	CQHCI_CRYPTO_KEY_SIZE_192	= 2,
	CQHCI_CRYPTO_KEY_SIZE_256	= 3,
	CQHCI_CRYPTO_KEY_SIZE_512	= 4,
पूर्ण;

क्रमागत cqhci_crypto_alg अणु
	CQHCI_CRYPTO_ALG_AES_XTS		= 0,
	CQHCI_CRYPTO_ALG_BITLOCKER_AES_CBC	= 1,
	CQHCI_CRYPTO_ALG_AES_ECB		= 2,
	CQHCI_CRYPTO_ALG_ESSIV_AES_CBC		= 3,
पूर्ण;

/* x-CRYPTOCAP - Crypto Capability X */
जोड़ cqhci_crypto_cap_entry अणु
	__le32 reg_val;
	काष्ठा अणु
		u8 algorithm_id;
		u8 sdus_mask; /* Supported data unit size mask */
		u8 key_size;
		u8 reserved;
	पूर्ण;
पूर्ण;

#घोषणा CQHCI_CRYPTO_CONFIGURATION_ENABLE (1 << 7)
#घोषणा CQHCI_CRYPTO_KEY_MAX_SIZE 64
/* x-CRYPTOCFG - Crypto Configuration X */
जोड़ cqhci_crypto_cfg_entry अणु
	__le32 reg_val[32];
	काष्ठा अणु
		u8 crypto_key[CQHCI_CRYPTO_KEY_MAX_SIZE];
		u8 data_unit_size;
		u8 crypto_cap_idx;
		u8 reserved_1;
		u8 config_enable;
		u8 reserved_multi_host;
		u8 reserved_2;
		u8 vsb[2];
		u8 reserved_3[56];
	पूर्ण;
पूर्ण;

काष्ठा cqhci_host_ops;
काष्ठा mmc_host;
काष्ठा mmc_request;
काष्ठा cqhci_slot;

काष्ठा cqhci_host अणु
	स्थिर काष्ठा cqhci_host_ops *ops;
	व्योम __iomem *mmio;
	काष्ठा mmc_host *mmc;

	spinlock_t lock;

	/* relative card address of device */
	अचिन्हित पूर्णांक rca;

	/* 64 bit DMA */
	bool dma64;
	पूर्णांक num_slots;
	पूर्णांक qcnt;

	u32 dcmd_slot;
	u32 caps;
#घोषणा CQHCI_TASK_DESC_SZ_128		0x1

	u32 quirks;
#घोषणा CQHCI_QUIRK_SHORT_TXFR_DESC_SZ	0x1

	bool enabled;
	bool halted;
	bool init_करोne;
	bool activated;
	bool रुकोing_क्रम_idle;
	bool recovery_halt;

	माप_प्रकार desc_size;
	माप_प्रकार data_size;

	u8 *desc_base;

	/* total descriptor size */
	u8 slot_sz;

	/* 64/128 bit depends on CQHCI_CFG */
	u8 task_desc_len;

	/* 64 bit on 32-bit arch, 128 bit on 64-bit */
	u8 link_desc_len;

	u8 *trans_desc_base;
	/* same length as transfer descriptor */
	u8 trans_desc_len;

	dma_addr_t desc_dma_base;
	dma_addr_t trans_desc_dma_base;

	काष्ठा completion halt_comp;
	रुको_queue_head_t रुको_queue;
	काष्ठा cqhci_slot *slot;

#अगर_घोषित CONFIG_MMC_CRYPTO
	जोड़ cqhci_crypto_capabilities crypto_capabilities;
	जोड़ cqhci_crypto_cap_entry *crypto_cap_array;
	u32 crypto_cfg_रेजिस्टर;
#पूर्ण_अगर
पूर्ण;

काष्ठा cqhci_host_ops अणु
	व्योम (*dumpregs)(काष्ठा mmc_host *mmc);
	व्योम (*ग_लिखो_l)(काष्ठा cqhci_host *host, u32 val, पूर्णांक reg);
	u32 (*पढ़ो_l)(काष्ठा cqhci_host *host, पूर्णांक reg);
	व्योम (*enable)(काष्ठा mmc_host *mmc);
	व्योम (*disable)(काष्ठा mmc_host *mmc, bool recovery);
	व्योम (*update_dcmd_desc)(काष्ठा mmc_host *mmc, काष्ठा mmc_request *mrq,
				 u64 *data);
	व्योम (*pre_enable)(काष्ठा mmc_host *mmc);
	व्योम (*post_disable)(काष्ठा mmc_host *mmc);
#अगर_घोषित CONFIG_MMC_CRYPTO
	पूर्णांक (*program_key)(काष्ठा cqhci_host *cq_host,
			   स्थिर जोड़ cqhci_crypto_cfg_entry *cfg, पूर्णांक slot);
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत व्योम cqhci_ग_लिखोl(काष्ठा cqhci_host *host, u32 val, पूर्णांक reg)
अणु
	अगर (unlikely(host->ops->ग_लिखो_l))
		host->ops->ग_लिखो_l(host, val, reg);
	अन्यथा
		ग_लिखोl_relaxed(val, host->mmio + reg);
पूर्ण

अटल अंतरभूत u32 cqhci_पढ़ोl(काष्ठा cqhci_host *host, पूर्णांक reg)
अणु
	अगर (unlikely(host->ops->पढ़ो_l))
		वापस host->ops->पढ़ो_l(host, reg);
	अन्यथा
		वापस पढ़ोl_relaxed(host->mmio + reg);
पूर्ण

काष्ठा platक्रमm_device;

irqवापस_t cqhci_irq(काष्ठा mmc_host *mmc, u32 पूर्णांकmask, पूर्णांक cmd_error,
		      पूर्णांक data_error);
पूर्णांक cqhci_init(काष्ठा cqhci_host *cq_host, काष्ठा mmc_host *mmc, bool dma64);
काष्ठा cqhci_host *cqhci_pltfm_init(काष्ठा platक्रमm_device *pdev);
पूर्णांक cqhci_deactivate(काष्ठा mmc_host *mmc);
अटल अंतरभूत पूर्णांक cqhci_suspend(काष्ठा mmc_host *mmc)
अणु
	वापस cqhci_deactivate(mmc);
पूर्ण
पूर्णांक cqhci_resume(काष्ठा mmc_host *mmc);

#पूर्ण_अगर
