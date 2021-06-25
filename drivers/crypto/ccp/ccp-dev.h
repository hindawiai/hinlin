<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AMD Cryptographic Coprocessor (CCP) driver
 *
 * Copyright (C) 2013,2017 Advanced Micro Devices, Inc.
 *
 * Author: Tom Lendacky <thomas.lendacky@amd.com>
 * Author: Gary R Hook <gary.hook@amd.com>
 */

#अगर_अघोषित __CCP_DEV_H__
#घोषणा __CCP_DEV_H__

#समावेश <linux/device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <linux/रुको.h>
#समावेश <linux/dma-direction.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/dmaengine.h>

#समावेश "sp-dev.h"

#घोषणा MAX_CCP_NAME_LEN		16
#घोषणा MAX_DMAPOOL_NAME_LEN		32

#घोषणा MAX_HW_QUEUES			5
#घोषणा MAX_CMD_QLEN			100

#घोषणा TRNG_RETRIES			10

#घोषणा CACHE_NONE			0x00
#घोषणा CACHE_WB_NO_ALLOC		0xb7

/****** Register Mappings ******/
#घोषणा Q_MASK_REG			0x000
#घोषणा TRNG_OUT_REG			0x00c
#घोषणा IRQ_MASK_REG			0x040
#घोषणा IRQ_STATUS_REG			0x200

#घोषणा DEL_CMD_Q_JOB			0x124
#घोषणा DEL_Q_ACTIVE			0x00000200
#घोषणा DEL_Q_ID_SHIFT			6

#घोषणा CMD_REQ0			0x180
#घोषणा CMD_REQ_INCR			0x04

#घोषणा CMD_Q_STATUS_BASE		0x210
#घोषणा CMD_Q_INT_STATUS_BASE		0x214
#घोषणा CMD_Q_STATUS_INCR		0x20

#घोषणा CMD_Q_CACHE_BASE		0x228
#घोषणा CMD_Q_CACHE_INC			0x20

#घोषणा CMD_Q_ERROR(__qs)		((__qs) & 0x0000003f)
#घोषणा CMD_Q_DEPTH(__qs)		(((__qs) >> 12) & 0x0000000f)

/* ------------------------ CCP Version 5 Specअगरics ------------------------ */
#घोषणा CMD5_QUEUE_MASK_OFFSET		0x00
#घोषणा	CMD5_QUEUE_PRIO_OFFSET		0x04
#घोषणा CMD5_REQID_CONFIG_OFFSET	0x08
#घोषणा	CMD5_CMD_TIMEOUT_OFFSET		0x10
#घोषणा LSB_PUBLIC_MASK_LO_OFFSET	0x18
#घोषणा LSB_PUBLIC_MASK_HI_OFFSET	0x1C
#घोषणा LSB_PRIVATE_MASK_LO_OFFSET	0x20
#घोषणा LSB_PRIVATE_MASK_HI_OFFSET	0x24
#घोषणा CMD5_PSP_CCP_VERSION		0x100

#घोषणा CMD5_Q_CONTROL_BASE		0x0000
#घोषणा CMD5_Q_TAIL_LO_BASE		0x0004
#घोषणा CMD5_Q_HEAD_LO_BASE		0x0008
#घोषणा CMD5_Q_INT_ENABLE_BASE		0x000C
#घोषणा CMD5_Q_INTERRUPT_STATUS_BASE	0x0010

#घोषणा CMD5_Q_STATUS_BASE		0x0100
#घोषणा CMD5_Q_INT_STATUS_BASE		0x0104
#घोषणा CMD5_Q_DMA_STATUS_BASE		0x0108
#घोषणा CMD5_Q_DMA_READ_STATUS_BASE	0x010C
#घोषणा CMD5_Q_DMA_WRITE_STATUS_BASE	0x0110
#घोषणा CMD5_Q_ABORT_BASE		0x0114
#घोषणा CMD5_Q_AX_CACHE_BASE		0x0118

#घोषणा	CMD5_CONFIG_0_OFFSET		0x6000
#घोषणा	CMD5_TRNG_CTL_OFFSET		0x6008
#घोषणा	CMD5_AES_MASK_OFFSET		0x6010
#घोषणा	CMD5_CLK_GATE_CTL_OFFSET	0x603C

/* Address offset between two भव queue रेजिस्टरs */
#घोषणा CMD5_Q_STATUS_INCR		0x1000

/* Bit masks */
#घोषणा CMD5_Q_RUN			0x1
#घोषणा CMD5_Q_HALT			0x2
#घोषणा CMD5_Q_MEM_LOCATION		0x4
#घोषणा CMD5_Q_SIZE			0x1F
#घोषणा CMD5_Q_SHIFT			3
#घोषणा COMMANDS_PER_QUEUE		16
#घोषणा QUEUE_SIZE_VAL			((ffs(COMMANDS_PER_QUEUE) - 2) & \
					  CMD5_Q_SIZE)
#घोषणा Q_PTR_MASK			(2 << (QUEUE_SIZE_VAL + 5) - 1)
#घोषणा Q_DESC_SIZE			माप(काष्ठा ccp5_desc)
#घोषणा Q_SIZE(n)			(COMMANDS_PER_QUEUE*(n))

#घोषणा INT_COMPLETION			0x1
#घोषणा INT_ERROR			0x2
#घोषणा INT_QUEUE_STOPPED		0x4
#घोषणा	INT_EMPTY_QUEUE			0x8
#घोषणा SUPPORTED_INTERRUPTS		(INT_COMPLETION | INT_ERROR)

#घोषणा LSB_REGION_WIDTH		5
#घोषणा MAX_LSB_CNT			8

#घोषणा LSB_SIZE			16
#घोषणा LSB_ITEM_SIZE			32
#घोषणा PLSB_MAP_SIZE			(LSB_SIZE)
#घोषणा SLSB_MAP_SIZE			(MAX_LSB_CNT * LSB_SIZE)

#घोषणा LSB_ENTRY_NUMBER(LSB_ADDR)	(LSB_ADDR / LSB_ITEM_SIZE)

/* ------------------------ CCP Version 3 Specअगरics ------------------------ */
#घोषणा REQ0_WAIT_FOR_WRITE		0x00000004
#घोषणा REQ0_INT_ON_COMPLETE		0x00000002
#घोषणा REQ0_STOP_ON_COMPLETE		0x00000001

#घोषणा REQ0_CMD_Q_SHIFT		9
#घोषणा REQ0_JOBID_SHIFT		3

/****** REQ1 Related Values ******/
#घोषणा REQ1_PROTECT_SHIFT		27
#घोषणा REQ1_ENGINE_SHIFT		23
#घोषणा REQ1_KEY_KSB_SHIFT		2

#घोषणा REQ1_EOM			0x00000002
#घोषणा REQ1_INIT			0x00000001

/* AES Related Values */
#घोषणा REQ1_AES_TYPE_SHIFT		21
#घोषणा REQ1_AES_MODE_SHIFT		18
#घोषणा REQ1_AES_ACTION_SHIFT		17
#घोषणा REQ1_AES_CFB_SIZE_SHIFT		10

/* XTS-AES Related Values */
#घोषणा REQ1_XTS_AES_SIZE_SHIFT		10

/* SHA Related Values */
#घोषणा REQ1_SHA_TYPE_SHIFT		21

/* RSA Related Values */
#घोषणा REQ1_RSA_MOD_SIZE_SHIFT		10

/* Pass-Through Related Values */
#घोषणा REQ1_PT_BW_SHIFT		12
#घोषणा REQ1_PT_BS_SHIFT		10

/* ECC Related Values */
#घोषणा REQ1_ECC_AFFINE_CONVERT		0x00200000
#घोषणा REQ1_ECC_FUNCTION_SHIFT		18

/****** REQ4 Related Values ******/
#घोषणा REQ4_KSB_SHIFT			18
#घोषणा REQ4_MEMTYPE_SHIFT		16

/****** REQ6 Related Values ******/
#घोषणा REQ6_MEMTYPE_SHIFT		16

/****** Key Storage Block ******/
#घोषणा KSB_START			77
#घोषणा KSB_END				127
#घोषणा KSB_COUNT			(KSB_END - KSB_START + 1)
#घोषणा CCP_SB_BITS			256

#घोषणा CCP_JOBID_MASK			0x0000003f

/* ------------------------ General CCP Defines ------------------------ */

#घोषणा	CCP_DMA_DFLT			0x0
#घोषणा	CCP_DMA_PRIV			0x1
#घोषणा	CCP_DMA_PUB			0x2

#घोषणा CCP_DMAPOOL_MAX_SIZE		64
#घोषणा CCP_DMAPOOL_ALIGN		BIT(5)

#घोषणा CCP_REVERSE_BUF_SIZE		64

#घोषणा CCP_AES_KEY_SB_COUNT		1
#घोषणा CCP_AES_CTX_SB_COUNT		1

#घोषणा CCP_XTS_AES_KEY_SB_COUNT	1
#घोषणा CCP5_XTS_AES_KEY_SB_COUNT	2
#घोषणा CCP_XTS_AES_CTX_SB_COUNT	1

#घोषणा CCP_DES3_KEY_SB_COUNT		1
#घोषणा CCP_DES3_CTX_SB_COUNT		1

#घोषणा CCP_SHA_SB_COUNT		1

#घोषणा CCP_RSA_MAX_WIDTH		4096
#घोषणा CCP5_RSA_MAX_WIDTH		16384

#घोषणा CCP_PASSTHRU_BLOCKSIZE		256
#घोषणा CCP_PASSTHRU_MASKSIZE		32
#घोषणा CCP_PASSTHRU_SB_COUNT		1

#घोषणा CCP_ECC_MODULUS_BYTES		48      /* 384-bits */
#घोषणा CCP_ECC_MAX_OPERANDS		6
#घोषणा CCP_ECC_MAX_OUTPUTS		3
#घोषणा CCP_ECC_SRC_BUF_SIZE		448
#घोषणा CCP_ECC_DST_BUF_SIZE		192
#घोषणा CCP_ECC_OPERAND_SIZE		64
#घोषणा CCP_ECC_OUTPUT_SIZE		64
#घोषणा CCP_ECC_RESULT_OFFSET		60
#घोषणा CCP_ECC_RESULT_SUCCESS		0x0001

#घोषणा CCP_SB_BYTES			32

काष्ठा ccp_op;
काष्ठा ccp_device;
काष्ठा ccp_cmd;
काष्ठा ccp_fns;

काष्ठा ccp_dma_cmd अणु
	काष्ठा list_head entry;

	काष्ठा ccp_cmd ccp_cmd;
पूर्ण;

काष्ठा ccp_dma_desc अणु
	काष्ठा list_head entry;

	काष्ठा ccp_device *ccp;

	काष्ठा list_head pending;
	काष्ठा list_head active;

	क्रमागत dma_status status;
	काष्ठा dma_async_tx_descriptor tx_desc;
	माप_प्रकार len;
पूर्ण;

काष्ठा ccp_dma_chan अणु
	काष्ठा ccp_device *ccp;

	spinlock_t lock;
	काष्ठा list_head created;
	काष्ठा list_head pending;
	काष्ठा list_head active;
	काष्ठा list_head complete;

	काष्ठा tasklet_काष्ठा cleanup_tasklet;

	क्रमागत dma_status status;
	काष्ठा dma_chan dma_chan;
पूर्ण;

काष्ठा ccp_cmd_queue अणु
	काष्ठा ccp_device *ccp;

	/* Queue identअगरier */
	u32 id;

	/* Queue dma pool */
	काष्ठा dma_pool *dma_pool;

	/* Queue base address (not neccessarily aligned)*/
	काष्ठा ccp5_desc *qbase;

	/* Aligned queue start address (per requirement) */
	काष्ठा mutex q_mutex ____cacheline_aligned;
	अचिन्हित पूर्णांक qidx;

	/* Version 5 has dअगरferent requirements क्रम queue memory */
	अचिन्हित पूर्णांक qsize;
	dma_addr_t qbase_dma;
	dma_addr_t qdma_tail;

	/* Per-queue reserved storage block(s) */
	u32 sb_key;
	u32 sb_ctx;

	/* Biपंचांगap of LSBs that can be accessed by this queue */
	DECLARE_BITMAP(lsbmask, MAX_LSB_CNT);
	/* Private LSB that is asचिन्हित to this queue, or -1 अगर none.
	 * Biपंचांगap क्रम my निजी LSB, unused otherwise
	 */
	पूर्णांक lsb;
	DECLARE_BITMAP(lsbmap, PLSB_MAP_SIZE);

	/* Queue processing thपढ़ो */
	काष्ठा task_काष्ठा *kthपढ़ो;
	अचिन्हित पूर्णांक active;
	अचिन्हित पूर्णांक suspended;

	/* Number of मुक्त command slots available */
	अचिन्हित पूर्णांक मुक्त_slots;

	/* Interrupt masks */
	u32 पूर्णांक_ok;
	u32 पूर्णांक_err;

	/* Register addresses क्रम queue */
	व्योम __iomem *reg_control;
	व्योम __iomem *reg_tail_lo;
	व्योम __iomem *reg_head_lo;
	व्योम __iomem *reg_पूर्णांक_enable;
	व्योम __iomem *reg_पूर्णांकerrupt_status;
	व्योम __iomem *reg_status;
	व्योम __iomem *reg_पूर्णांक_status;
	व्योम __iomem *reg_dma_status;
	व्योम __iomem *reg_dma_पढ़ो_status;
	व्योम __iomem *reg_dma_ग_लिखो_status;
	u32 qcontrol; /* Cached control रेजिस्टर */

	/* Status values from job */
	u32 पूर्णांक_status;
	u32 q_status;
	u32 q_पूर्णांक_status;
	u32 cmd_error;

	/* Interrupt रुको queue */
	रुको_queue_head_t पूर्णांक_queue;
	अचिन्हित पूर्णांक पूर्णांक_rcvd;

	/* Per-queue Statistics */
	अचिन्हित दीर्घ total_ops;
	अचिन्हित दीर्घ total_aes_ops;
	अचिन्हित दीर्घ total_xts_aes_ops;
	अचिन्हित दीर्घ total_3des_ops;
	अचिन्हित दीर्घ total_sha_ops;
	अचिन्हित दीर्घ total_rsa_ops;
	अचिन्हित दीर्घ total_pt_ops;
	अचिन्हित दीर्घ total_ecc_ops;
पूर्ण ____cacheline_aligned;

काष्ठा ccp_device अणु
	काष्ठा list_head entry;

	काष्ठा ccp_vdata *vdata;
	अचिन्हित पूर्णांक ord;
	अक्षर name[MAX_CCP_NAME_LEN];
	अक्षर rngname[MAX_CCP_NAME_LEN];

	काष्ठा device *dev;
	काष्ठा sp_device *sp;

	/* Bus specअगरic device inक्रमmation
	 */
	व्योम *dev_specअगरic;
	अचिन्हित पूर्णांक qim;
	अचिन्हित पूर्णांक irq;
	bool use_tasklet;
	काष्ठा tasklet_काष्ठा irq_tasklet;

	/* I/O area used क्रम device communication. The रेजिस्टर mapping
	 * starts at an offset पूर्णांकo the mapped bar.
	 *   The CMD_REQx रेजिस्टरs and the Delete_Cmd_Queue_Job रेजिस्टर
	 *   need to be रक्षित जबतक a command queue thपढ़ो is accessing
	 *   them.
	 */
	काष्ठा mutex req_mutex ____cacheline_aligned;
	व्योम __iomem *io_regs;

	/* Master lists that all cmds are queued on. Because there can be
	 * more than one CCP command queue that can process a cmd a separate
	 * backlog list is neeeded so that the backlog completion call
	 * completes beक्रमe the cmd is available क्रम execution.
	 */
	spinlock_t cmd_lock ____cacheline_aligned;
	अचिन्हित पूर्णांक cmd_count;
	काष्ठा list_head cmd;
	काष्ठा list_head backlog;

	/* The command queues. These represent the queues available on the
	 * CCP that are available क्रम processing cmds
	 */
	काष्ठा ccp_cmd_queue cmd_q[MAX_HW_QUEUES];
	अचिन्हित पूर्णांक cmd_q_count;
	अचिन्हित पूर्णांक max_q_count;

	/* Support क्रम the CCP True RNG
	 */
	काष्ठा hwrng hwrng;
	अचिन्हित पूर्णांक hwrng_retries;

	/* Support क्रम the CCP DMA capabilities
	 */
	काष्ठा dma_device dma_dev;
	काष्ठा ccp_dma_chan *ccp_dma_chan;
	काष्ठा kmem_cache *dma_cmd_cache;
	काष्ठा kmem_cache *dma_desc_cache;

	/* A counter used to generate job-ids क्रम cmds submitted to the CCP
	 */
	atomic_t current_id ____cacheline_aligned;

	/* The v3 CCP uses key storage blocks (SB) to मुख्यtain context क्रम
	 * certain operations. To prevent multiple cmds from using the same
	 * SB range a command queue reserves an SB range क्रम the duration of
	 * the cmd. Each queue, will however, reserve 2 SB blocks क्रम
	 * operations that only require single SB entries (eg. AES context/iv
	 * and key) in order to aव्योम allocation contention.  This will reserve
	 * at most 10 SB entries, leaving 40 SB entries available क्रम dynamic
	 * allocation.
	 *
	 * The v5 CCP Local Storage Block (LSB) is broken up पूर्णांकo 8
	 * memrory ranges, each of which can be enabled क्रम access by one
	 * or more queues. Device initialization takes this पूर्णांकo account,
	 * and attempts to assign one region क्रम exclusive use by each
	 * available queue; the rest are then aggregated as "public" use.
	 * If there are fewer regions than queues, all regions are shared
	 * amongst all queues.
	 */
	काष्ठा mutex sb_mutex ____cacheline_aligned;
	DECLARE_BITMAP(sb, KSB_COUNT);
	रुको_queue_head_t sb_queue;
	अचिन्हित पूर्णांक sb_avail;
	अचिन्हित पूर्णांक sb_count;
	u32 sb_start;

	/* Biपंचांगap of shared LSBs, अगर any */
	DECLARE_BITMAP(lsbmap, SLSB_MAP_SIZE);

	/* Suspend support */
	अचिन्हित पूर्णांक suspending;
	रुको_queue_head_t suspend_queue;

	/* DMA caching attribute support */
	अचिन्हित पूर्णांक axcache;

	/* Device Statistics */
	अचिन्हित दीर्घ total_पूर्णांकerrupts;

	/* DebugFS info */
	काष्ठा dentry *debugfs_instance;
पूर्ण;

क्रमागत ccp_memtype अणु
	CCP_MEMTYPE_SYSTEM = 0,
	CCP_MEMTYPE_SB,
	CCP_MEMTYPE_LOCAL,
	CCP_MEMTYPE__LAST,
पूर्ण;
#घोषणा	CCP_MEMTYPE_LSB	CCP_MEMTYPE_KSB


काष्ठा ccp_dma_info अणु
	dma_addr_t address;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक length;
	क्रमागत dma_data_direction dir;
पूर्ण __packed __aligned(4);

काष्ठा ccp_dm_workarea अणु
	काष्ठा device *dev;
	काष्ठा dma_pool *dma_pool;

	u8 *address;
	काष्ठा ccp_dma_info dma;
	अचिन्हित पूर्णांक length;
पूर्ण;

काष्ठा ccp_sg_workarea अणु
	काष्ठा scatterlist *sg;
	पूर्णांक nents;
	अचिन्हित पूर्णांक sg_used;

	काष्ठा scatterlist *dma_sg;
	काष्ठा scatterlist *dma_sg_head;
	काष्ठा device *dma_dev;
	अचिन्हित पूर्णांक dma_count;
	क्रमागत dma_data_direction dma_dir;

	u64 bytes_left;
पूर्ण;

काष्ठा ccp_data अणु
	काष्ठा ccp_sg_workarea sg_wa;
	काष्ठा ccp_dm_workarea dm_wa;
पूर्ण;

काष्ठा ccp_mem अणु
	क्रमागत ccp_memtype type;
	जोड़ अणु
		काष्ठा ccp_dma_info dma;
		u32 sb;
	पूर्ण u;
पूर्ण;

काष्ठा ccp_aes_op अणु
	क्रमागत ccp_aes_type type;
	क्रमागत ccp_aes_mode mode;
	क्रमागत ccp_aes_action action;
	अचिन्हित पूर्णांक size;
पूर्ण;

काष्ठा ccp_xts_aes_op अणु
	क्रमागत ccp_aes_type type;
	क्रमागत ccp_aes_action action;
	क्रमागत ccp_xts_aes_unit_size unit_size;
पूर्ण;

काष्ठा ccp_des3_op अणु
	क्रमागत ccp_des3_type type;
	क्रमागत ccp_des3_mode mode;
	क्रमागत ccp_des3_action action;
पूर्ण;

काष्ठा ccp_sha_op अणु
	क्रमागत ccp_sha_type type;
	u64 msg_bits;
पूर्ण;

काष्ठा ccp_rsa_op अणु
	u32 mod_size;
	u32 input_len;
पूर्ण;

काष्ठा ccp_passthru_op अणु
	क्रमागत ccp_passthru_bitwise bit_mod;
	क्रमागत ccp_passthru_byteswap byte_swap;
पूर्ण;

काष्ठा ccp_ecc_op अणु
	क्रमागत ccp_ecc_function function;
पूर्ण;

काष्ठा ccp_op अणु
	काष्ठा ccp_cmd_queue *cmd_q;

	u32 jobid;
	u32 ioc;
	u32 soc;
	u32 sb_key;
	u32 sb_ctx;
	u32 init;
	u32 eom;

	काष्ठा ccp_mem src;
	काष्ठा ccp_mem dst;
	काष्ठा ccp_mem exp;

	जोड़ अणु
		काष्ठा ccp_aes_op aes;
		काष्ठा ccp_xts_aes_op xts;
		काष्ठा ccp_des3_op des3;
		काष्ठा ccp_sha_op sha;
		काष्ठा ccp_rsa_op rsa;
		काष्ठा ccp_passthru_op passthru;
		काष्ठा ccp_ecc_op ecc;
	पूर्ण u;
पूर्ण;

अटल अंतरभूत u32 ccp_addr_lo(काष्ठा ccp_dma_info *info)
अणु
	वापस lower_32_bits(info->address + info->offset);
पूर्ण

अटल अंतरभूत u32 ccp_addr_hi(काष्ठा ccp_dma_info *info)
अणु
	वापस upper_32_bits(info->address + info->offset) & 0x0000ffff;
पूर्ण

/**
 * descriptor क्रम version 5 CPP commands
 * 8 32-bit words:
 * word 0: function; engine; control bits
 * word 1: length of source data
 * word 2: low 32 bits of source poपूर्णांकer
 * word 3: upper 16 bits of source poपूर्णांकer; source memory type
 * word 4: low 32 bits of destination poपूर्णांकer
 * word 5: upper 16 bits of destination poपूर्णांकer; destination memory type
 * word 6: low 32 bits of key poपूर्णांकer
 * word 7: upper 16 bits of key poपूर्णांकer; key memory type
 */
काष्ठा dword0 अणु
	अचिन्हित पूर्णांक soc:1;
	अचिन्हित पूर्णांक ioc:1;
	अचिन्हित पूर्णांक rsvd1:1;
	अचिन्हित पूर्णांक init:1;
	अचिन्हित पूर्णांक eom:1;		/* AES/SHA only */
	अचिन्हित पूर्णांक function:15;
	अचिन्हित पूर्णांक engine:4;
	अचिन्हित पूर्णांक prot:1;
	अचिन्हित पूर्णांक rsvd2:7;
पूर्ण;

काष्ठा dword3 अणु
	अचिन्हित पूर्णांक  src_hi:16;
	अचिन्हित पूर्णांक  src_mem:2;
	अचिन्हित पूर्णांक  lsb_cxt_id:8;
	अचिन्हित पूर्णांक  rsvd1:5;
	अचिन्हित पूर्णांक  fixed:1;
पूर्ण;

जोड़ dword4 अणु
	u32 dst_lo;		/* NON-SHA	*/
	u32 sha_len_lo;		/* SHA		*/
पूर्ण;

जोड़ dword5 अणु
	काष्ठा अणु
		अचिन्हित पूर्णांक  dst_hi:16;
		अचिन्हित पूर्णांक  dst_mem:2;
		अचिन्हित पूर्णांक  rsvd1:13;
		अचिन्हित पूर्णांक  fixed:1;
	पूर्ण fields;
	u32 sha_len_hi;
पूर्ण;

काष्ठा dword7 अणु
	अचिन्हित पूर्णांक  key_hi:16;
	अचिन्हित पूर्णांक  key_mem:2;
	अचिन्हित पूर्णांक  rsvd1:14;
पूर्ण;

काष्ठा ccp5_desc अणु
	काष्ठा dword0 dw0;
	u32 length;
	u32 src_lo;
	काष्ठा dword3 dw3;
	जोड़ dword4 dw4;
	जोड़ dword5 dw5;
	u32 key_lo;
	काष्ठा dword7 dw7;
पूर्ण;

व्योम ccp_add_device(काष्ठा ccp_device *ccp);
व्योम ccp_del_device(काष्ठा ccp_device *ccp);

बाह्य व्योम ccp_log_error(काष्ठा ccp_device *, अचिन्हित पूर्णांक);

काष्ठा ccp_device *ccp_alloc_काष्ठा(काष्ठा sp_device *sp);
bool ccp_queues_suspended(काष्ठा ccp_device *ccp);
पूर्णांक ccp_cmd_queue_thपढ़ो(व्योम *data);
पूर्णांक ccp_trng_पढ़ो(काष्ठा hwrng *rng, व्योम *data, माप_प्रकार max, bool रुको);

पूर्णांक ccp_run_cmd(काष्ठा ccp_cmd_queue *cmd_q, काष्ठा ccp_cmd *cmd);

पूर्णांक ccp_रेजिस्टर_rng(काष्ठा ccp_device *ccp);
व्योम ccp_unरेजिस्टर_rng(काष्ठा ccp_device *ccp);
पूर्णांक ccp_dmaengine_रेजिस्टर(काष्ठा ccp_device *ccp);
व्योम ccp_dmaengine_unरेजिस्टर(काष्ठा ccp_device *ccp);

व्योम ccp5_debugfs_setup(काष्ठा ccp_device *ccp);
व्योम ccp5_debugfs_destroy(व्योम);

/* Structure क्रम computation functions that are device-specअगरic */
काष्ठा ccp_actions अणु
	पूर्णांक (*aes)(काष्ठा ccp_op *);
	पूर्णांक (*xts_aes)(काष्ठा ccp_op *);
	पूर्णांक (*des3)(काष्ठा ccp_op *);
	पूर्णांक (*sha)(काष्ठा ccp_op *);
	पूर्णांक (*rsa)(काष्ठा ccp_op *);
	पूर्णांक (*passthru)(काष्ठा ccp_op *);
	पूर्णांक (*ecc)(काष्ठा ccp_op *);
	u32 (*sballoc)(काष्ठा ccp_cmd_queue *, अचिन्हित पूर्णांक);
	व्योम (*sbमुक्त)(काष्ठा ccp_cmd_queue *, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);
	अचिन्हित पूर्णांक (*get_मुक्त_slots)(काष्ठा ccp_cmd_queue *);
	पूर्णांक (*init)(काष्ठा ccp_device *);
	व्योम (*destroy)(काष्ठा ccp_device *);
	irqवापस_t (*irqhandler)(पूर्णांक, व्योम *);
पूर्ण;

बाह्य स्थिर काष्ठा ccp_vdata ccpv3_platक्रमm;
बाह्य स्थिर काष्ठा ccp_vdata ccpv3;
बाह्य स्थिर काष्ठा ccp_vdata ccpv5a;
बाह्य स्थिर काष्ठा ccp_vdata ccpv5b;

#पूर्ण_अगर
