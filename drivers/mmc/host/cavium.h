<शैली गुरु>
/*
 * Driver क्रम MMC and SSD cards क्रम Cavium OCTEON and ThunderX SOCs.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2012-2017 Cavium Inc.
 */

#अगर_अघोषित _CAVIUM_MMC_H_
#घोषणा _CAVIUM_MMC_H_

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पन.स>
#समावेश <linux/mmc/host.h>
#समावेश <linux/of.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/semaphore.h>

#घोषणा CAVIUM_MAX_MMC		4

/* DMA रेजिस्टर addresses */
#घोषणा MIO_EMM_DMA_FIFO_CFG(x)	(0x00 + x->reg_off_dma)
#घोषणा MIO_EMM_DMA_FIFO_ADR(x)	(0x10 + x->reg_off_dma)
#घोषणा MIO_EMM_DMA_FIFO_CMD(x)	(0x18 + x->reg_off_dma)
#घोषणा MIO_EMM_DMA_CFG(x)	(0x20 + x->reg_off_dma)
#घोषणा MIO_EMM_DMA_ADR(x)	(0x28 + x->reg_off_dma)
#घोषणा MIO_EMM_DMA_INT(x)	(0x30 + x->reg_off_dma)
#घोषणा MIO_EMM_DMA_INT_W1S(x)	(0x38 + x->reg_off_dma)
#घोषणा MIO_EMM_DMA_INT_ENA_W1S(x) (0x40 + x->reg_off_dma)
#घोषणा MIO_EMM_DMA_INT_ENA_W1C(x) (0x48 + x->reg_off_dma)

/* रेजिस्टर addresses */
#घोषणा MIO_EMM_CFG(x)		(0x00 + x->reg_off)
#घोषणा MIO_EMM_SWITCH(x)	(0x48 + x->reg_off)
#घोषणा MIO_EMM_DMA(x)		(0x50 + x->reg_off)
#घोषणा MIO_EMM_CMD(x)		(0x58 + x->reg_off)
#घोषणा MIO_EMM_RSP_STS(x)	(0x60 + x->reg_off)
#घोषणा MIO_EMM_RSP_LO(x)	(0x68 + x->reg_off)
#घोषणा MIO_EMM_RSP_HI(x)	(0x70 + x->reg_off)
#घोषणा MIO_EMM_INT(x)		(0x78 + x->reg_off)
#घोषणा MIO_EMM_INT_EN(x)	(0x80 + x->reg_off)
#घोषणा MIO_EMM_WDOG(x)		(0x88 + x->reg_off)
#घोषणा MIO_EMM_SAMPLE(x)	(0x90 + x->reg_off)
#घोषणा MIO_EMM_STS_MASK(x)	(0x98 + x->reg_off)
#घोषणा MIO_EMM_RCA(x)		(0xa0 + x->reg_off)
#घोषणा MIO_EMM_INT_EN_SET(x)	(0xb0 + x->reg_off)
#घोषणा MIO_EMM_INT_EN_CLR(x)	(0xb8 + x->reg_off)
#घोषणा MIO_EMM_BUF_IDX(x)	(0xe0 + x->reg_off)
#घोषणा MIO_EMM_BUF_DAT(x)	(0xe8 + x->reg_off)

काष्ठा cvm_mmc_host अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	व्योम __iomem *dma_base;
	पूर्णांक reg_off;
	पूर्णांक reg_off_dma;
	u64 emm_cfg;
	u64 n_minus_one;	/* OCTEON II workaround location */
	पूर्णांक last_slot;
	काष्ठा clk *clk;
	पूर्णांक sys_freq;

	काष्ठा mmc_request *current_req;
	काष्ठा sg_mapping_iter smi;
	bool dma_active;
	bool use_sg;

	bool has_ciu3;
	bool big_dma_addr;
	bool need_irq_handler_lock;
	spinlock_t irq_handler_lock;
	काष्ठा semaphore mmc_serializer;

	काष्ठा gpio_desc *global_pwr_gpiod;
	atomic_t shared_घातer_users;

	काष्ठा cvm_mmc_slot *slot[CAVIUM_MAX_MMC];
	काष्ठा platक्रमm_device *slot_pdev[CAVIUM_MAX_MMC];

	व्योम (*set_shared_घातer)(काष्ठा cvm_mmc_host *, पूर्णांक);
	व्योम (*acquire_bus)(काष्ठा cvm_mmc_host *);
	व्योम (*release_bus)(काष्ठा cvm_mmc_host *);
	व्योम (*पूर्णांक_enable)(काष्ठा cvm_mmc_host *, u64);
	/* required on some MIPS models */
	व्योम (*dmar_fixup)(काष्ठा cvm_mmc_host *, काष्ठा mmc_command *,
			   काष्ठा mmc_data *, u64);
	व्योम (*dmar_fixup_करोne)(काष्ठा cvm_mmc_host *);
पूर्ण;

काष्ठा cvm_mmc_slot अणु
	काष्ठा mmc_host *mmc;		/* slot-level mmc_core object */
	काष्ठा cvm_mmc_host *host;	/* common hw क्रम all slots */

	u64 घड़ी;

	u64 cached_चयन;
	u64 cached_rca;

	अचिन्हित पूर्णांक cmd_cnt;		/* sample delay */
	अचिन्हित पूर्णांक dat_cnt;		/* sample delay */

	पूर्णांक bus_id;
पूर्ण;

काष्ठा cvm_mmc_cr_type अणु
	u8 ctype;
	u8 rtype;
पूर्ण;

काष्ठा cvm_mmc_cr_mods अणु
	u8 ctype_xor;
	u8 rtype_xor;
पूर्ण;

/* Bitfield definitions */
#घोषणा MIO_EMM_DMA_FIFO_CFG_CLR	BIT_ULL(16)
#घोषणा MIO_EMM_DMA_FIFO_CFG_INT_LVL	GENMASK_ULL(12, 8)
#घोषणा MIO_EMM_DMA_FIFO_CFG_COUNT	GENMASK_ULL(4, 0)

#घोषणा MIO_EMM_DMA_FIFO_CMD_RW		BIT_ULL(62)
#घोषणा MIO_EMM_DMA_FIFO_CMD_INTDIS	BIT_ULL(60)
#घोषणा MIO_EMM_DMA_FIFO_CMD_SWAP32	BIT_ULL(59)
#घोषणा MIO_EMM_DMA_FIFO_CMD_SWAP16	BIT_ULL(58)
#घोषणा MIO_EMM_DMA_FIFO_CMD_SWAP8	BIT_ULL(57)
#घोषणा MIO_EMM_DMA_FIFO_CMD_ENDIAN	BIT_ULL(56)
#घोषणा MIO_EMM_DMA_FIFO_CMD_SIZE	GENMASK_ULL(55, 36)

#घोषणा MIO_EMM_CMD_SKIP_BUSY		BIT_ULL(62)
#घोषणा MIO_EMM_CMD_BUS_ID		GENMASK_ULL(61, 60)
#घोषणा MIO_EMM_CMD_VAL			BIT_ULL(59)
#घोषणा MIO_EMM_CMD_DBUF		BIT_ULL(55)
#घोषणा MIO_EMM_CMD_OFFSET		GENMASK_ULL(54, 49)
#घोषणा MIO_EMM_CMD_CTYPE_XOR		GENMASK_ULL(42, 41)
#घोषणा MIO_EMM_CMD_RTYPE_XOR		GENMASK_ULL(40, 38)
#घोषणा MIO_EMM_CMD_IDX			GENMASK_ULL(37, 32)
#घोषणा MIO_EMM_CMD_ARG			GENMASK_ULL(31, 0)

#घोषणा MIO_EMM_DMA_SKIP_BUSY		BIT_ULL(62)
#घोषणा MIO_EMM_DMA_BUS_ID		GENMASK_ULL(61, 60)
#घोषणा MIO_EMM_DMA_VAL			BIT_ULL(59)
#घोषणा MIO_EMM_DMA_SECTOR		BIT_ULL(58)
#घोषणा MIO_EMM_DMA_DAT_शून्य		BIT_ULL(57)
#घोषणा MIO_EMM_DMA_THRES		GENMASK_ULL(56, 51)
#घोषणा MIO_EMM_DMA_REL_WR		BIT_ULL(50)
#घोषणा MIO_EMM_DMA_RW			BIT_ULL(49)
#घोषणा MIO_EMM_DMA_MULTI		BIT_ULL(48)
#घोषणा MIO_EMM_DMA_BLOCK_CNT		GENMASK_ULL(47, 32)
#घोषणा MIO_EMM_DMA_CARD_ADDR		GENMASK_ULL(31, 0)

#घोषणा MIO_EMM_DMA_CFG_EN		BIT_ULL(63)
#घोषणा MIO_EMM_DMA_CFG_RW		BIT_ULL(62)
#घोषणा MIO_EMM_DMA_CFG_CLR		BIT_ULL(61)
#घोषणा MIO_EMM_DMA_CFG_SWAP32		BIT_ULL(59)
#घोषणा MIO_EMM_DMA_CFG_SWAP16		BIT_ULL(58)
#घोषणा MIO_EMM_DMA_CFG_SWAP8		BIT_ULL(57)
#घोषणा MIO_EMM_DMA_CFG_ENDIAN		BIT_ULL(56)
#घोषणा MIO_EMM_DMA_CFG_SIZE		GENMASK_ULL(55, 36)
#घोषणा MIO_EMM_DMA_CFG_ADR		GENMASK_ULL(35, 0)

#घोषणा MIO_EMM_INT_SWITCH_ERR		BIT_ULL(6)
#घोषणा MIO_EMM_INT_SWITCH_DONE		BIT_ULL(5)
#घोषणा MIO_EMM_INT_DMA_ERR		BIT_ULL(4)
#घोषणा MIO_EMM_INT_CMD_ERR		BIT_ULL(3)
#घोषणा MIO_EMM_INT_DMA_DONE		BIT_ULL(2)
#घोषणा MIO_EMM_INT_CMD_DONE		BIT_ULL(1)
#घोषणा MIO_EMM_INT_BUF_DONE		BIT_ULL(0)

#घोषणा MIO_EMM_RSP_STS_BUS_ID		GENMASK_ULL(61, 60)
#घोषणा MIO_EMM_RSP_STS_CMD_VAL		BIT_ULL(59)
#घोषणा MIO_EMM_RSP_STS_SWITCH_VAL	BIT_ULL(58)
#घोषणा MIO_EMM_RSP_STS_DMA_VAL		BIT_ULL(57)
#घोषणा MIO_EMM_RSP_STS_DMA_PEND	BIT_ULL(56)
#घोषणा MIO_EMM_RSP_STS_DBUF_ERR	BIT_ULL(28)
#घोषणा MIO_EMM_RSP_STS_DBUF		BIT_ULL(23)
#घोषणा MIO_EMM_RSP_STS_BLK_TIMEOUT	BIT_ULL(22)
#घोषणा MIO_EMM_RSP_STS_BLK_CRC_ERR	BIT_ULL(21)
#घोषणा MIO_EMM_RSP_STS_RSP_BUSYBIT	BIT_ULL(20)
#घोषणा MIO_EMM_RSP_STS_STP_TIMEOUT	BIT_ULL(19)
#घोषणा MIO_EMM_RSP_STS_STP_CRC_ERR	BIT_ULL(18)
#घोषणा MIO_EMM_RSP_STS_STP_BAD_STS	BIT_ULL(17)
#घोषणा MIO_EMM_RSP_STS_STP_VAL		BIT_ULL(16)
#घोषणा MIO_EMM_RSP_STS_RSP_TIMEOUT	BIT_ULL(15)
#घोषणा MIO_EMM_RSP_STS_RSP_CRC_ERR	BIT_ULL(14)
#घोषणा MIO_EMM_RSP_STS_RSP_BAD_STS	BIT_ULL(13)
#घोषणा MIO_EMM_RSP_STS_RSP_VAL		BIT_ULL(12)
#घोषणा MIO_EMM_RSP_STS_RSP_TYPE	GENMASK_ULL(11, 9)
#घोषणा MIO_EMM_RSP_STS_CMD_TYPE	GENMASK_ULL(8, 7)
#घोषणा MIO_EMM_RSP_STS_CMD_IDX		GENMASK_ULL(6, 1)
#घोषणा MIO_EMM_RSP_STS_CMD_DONE	BIT_ULL(0)

#घोषणा MIO_EMM_SAMPLE_CMD_CNT		GENMASK_ULL(25, 16)
#घोषणा MIO_EMM_SAMPLE_DAT_CNT		GENMASK_ULL(9, 0)

#घोषणा MIO_EMM_SWITCH_BUS_ID		GENMASK_ULL(61, 60)
#घोषणा MIO_EMM_SWITCH_EXE		BIT_ULL(59)
#घोषणा MIO_EMM_SWITCH_ERR0		BIT_ULL(58)
#घोषणा MIO_EMM_SWITCH_ERR1		BIT_ULL(57)
#घोषणा MIO_EMM_SWITCH_ERR2		BIT_ULL(56)
#घोषणा MIO_EMM_SWITCH_HS_TIMING	BIT_ULL(48)
#घोषणा MIO_EMM_SWITCH_BUS_WIDTH	GENMASK_ULL(42, 40)
#घोषणा MIO_EMM_SWITCH_POWER_CLASS	GENMASK_ULL(35, 32)
#घोषणा MIO_EMM_SWITCH_CLK_HI		GENMASK_ULL(31, 16)
#घोषणा MIO_EMM_SWITCH_CLK_LO		GENMASK_ULL(15, 0)

/* Protoypes */
irqवापस_t cvm_mmc_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
पूर्णांक cvm_mmc_of_slot_probe(काष्ठा device *dev, काष्ठा cvm_mmc_host *host);
पूर्णांक cvm_mmc_of_slot_हटाओ(काष्ठा cvm_mmc_slot *slot);
बाह्य स्थिर अक्षर *cvm_mmc_irq_names[];

#पूर्ण_अगर
