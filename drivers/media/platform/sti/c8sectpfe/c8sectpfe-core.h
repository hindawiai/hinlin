<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * c8sectpfe-core.h - C8SECTPFE STi DVB driver
 *
 * Copyright (c) STMicroelectronics 2015
 *
 *   Author:Peter Bennett <peter.bennett@st.com>
 *	    Peter Grअगरfin <peter.grअगरfin@linaro.org>
 *
 */
#अगर_अघोषित _C8SECTPFE_CORE_H_
#घोषणा _C8SECTPFE_CORE_H_

#घोषणा C8SECTPFEI_MAXCHANNEL 16
#घोषणा C8SECTPFEI_MAXADAPTER 3

#घोषणा C8SECTPFE_MAX_TSIN_CHAN 8

काष्ठा channel_info अणु

	पूर्णांक tsin_id;
	bool invert_ts_clk;
	bool serial_not_parallel;
	bool async_not_sync;
	पूर्णांक i2c;
	पूर्णांक dvb_card;

	पूर्णांक rst_gpio;

	काष्ठा i2c_adapter  *i2c_adapter;
	काष्ठा i2c_adapter  *tuner_i2c;
	काष्ठा i2c_adapter  *lnb_i2c;
	काष्ठा i2c_client   *i2c_client;
	काष्ठा dvb_frontend *frontend;

	काष्ठा pinctrl_state *pstate;

	पूर्णांक demux_mapping;
	पूर्णांक active;

	व्योम *back_buffer_start;
	व्योम *back_buffer_aligned;
	dma_addr_t back_buffer_busaddr;

	व्योम *pid_buffer_start;
	व्योम *pid_buffer_aligned;
	dma_addr_t pid_buffer_busaddr;

	अचिन्हित दीर्घ  fअगरo;

	काष्ठा completion idle_completion;
	काष्ठा tasklet_काष्ठा tsklet;

	काष्ठा c8sectpfei *fei;
	व्योम __iomem *irec;

पूर्ण;

काष्ठा c8sectpfe_hw अणु
	पूर्णांक num_ib;
	पूर्णांक num_mib;
	पूर्णांक num_swts;
	पूर्णांक num_tsout;
	पूर्णांक num_ccsc;
	पूर्णांक num_ram;
	पूर्णांक num_tp;
पूर्ण;

काष्ठा c8sectpfei अणु

	काष्ठा device *dev;
	काष्ठा pinctrl *pinctrl;

	काष्ठा dentry *root;
	काष्ठा debugfs_regset32	*regset;
	काष्ठा completion fw_ack;
	atomic_t fw_loaded;

	पूर्णांक tsin_count;

	काष्ठा c8sectpfe_hw hw_stats;

	काष्ठा c8sectpfe *c8sectpfe[C8SECTPFEI_MAXADAPTER];

	पूर्णांक mapping[C8SECTPFEI_MAXCHANNEL];

	काष्ठा mutex lock;

	काष्ठा समयr_list समयr;	/* समयr पूर्णांकerrupts क्रम outमाला_दो */

	व्योम __iomem *io;
	व्योम __iomem *sram;

	अचिन्हित दीर्घ sram_size;

	काष्ठा channel_info *channel_data[C8SECTPFE_MAX_TSIN_CHAN];

	काष्ठा clk *c8sectpfeclk;
	पूर्णांक nima_rst_gpio;
	पूर्णांक nimb_rst_gpio;

	पूर्णांक idle_irq;
	पूर्णांक error_irq;

	पूर्णांक global_feed_count;
पूर्ण;

/* C8SECTPFE SYS Regs list */

#घोषणा SYS_INPUT_ERR_STATUS	0x0
#घोषणा SYS_OTHER_ERR_STATUS	0x8
#घोषणा SYS_INPUT_ERR_MASK	0x10
#घोषणा SYS_OTHER_ERR_MASK	0x18
#घोषणा SYS_DMA_ROUTE		0x20
#घोषणा SYS_INPUT_CLKEN		0x30
#घोषणा IBENABLE_MASK			0x7F

#घोषणा SYS_OTHER_CLKEN		0x38
#घोषणा TSDMAENABLE			BIT(1)
#घोषणा MEMDMAENABLE			BIT(0)

#घोषणा SYS_CFG_NUM_IB		0x200
#घोषणा SYS_CFG_NUM_MIB		0x204
#घोषणा SYS_CFG_NUM_SWTS	0x208
#घोषणा SYS_CFG_NUM_TSOUT	0x20C
#घोषणा SYS_CFG_NUM_CCSC	0x210
#घोषणा SYS_CFG_NUM_RAM		0x214
#घोषणा SYS_CFG_NUM_TP		0x218

/* Input Block Regs */

#घोषणा C8SECTPFE_INPUTBLK_OFFSET	0x1000
#घोषणा C8SECTPFE_CHANNEL_OFFSET(x)	((x*0x40) + C8SECTPFE_INPUTBLK_OFFSET)

#घोषणा C8SECTPFE_IB_IP_FMT_CFG(x)      (C8SECTPFE_CHANNEL_OFFSET(x) + 0x00)
#घोषणा C8SECTPFE_IGNORE_ERR_AT_SOP     BIT(7)
#घोषणा C8SECTPFE_IGNORE_ERR_IN_PKT     BIT(6)
#घोषणा C8SECTPFE_IGNORE_ERR_IN_BYTE    BIT(5)
#घोषणा C8SECTPFE_INVERT_TSCLK          BIT(4)
#घोषणा C8SECTPFE_ALIGN_BYTE_SOP        BIT(3)
#घोषणा C8SECTPFE_ASYNC_NOT_SYNC        BIT(2)
#घोषणा C8SECTPFE_BYTE_ENDIANNESS_MSB    BIT(1)
#घोषणा C8SECTPFE_SERIAL_NOT_PARALLEL   BIT(0)

#घोषणा C8SECTPFE_IB_SYNCLCKDRP_CFG(x)   (C8SECTPFE_CHANNEL_OFFSET(x) + 0x04)
#घोषणा C8SECTPFE_SYNC(x)                (x & 0xf)
#घोषणा C8SECTPFE_DROP(x)                ((x<<4) & 0xf)
#घोषणा C8SECTPFE_TOKEN(x)               ((x<<8) & 0xff00)
#घोषणा C8SECTPFE_SLDENDIANNESS          BIT(16)

#घोषणा C8SECTPFE_IB_TAGBYTES_CFG(x)     (C8SECTPFE_CHANNEL_OFFSET(x) + 0x08)
#घोषणा C8SECTPFE_TAG_HEADER(x)          (x << 16)
#घोषणा C8SECTPFE_TAG_COUNTER(x)         ((x<<1) & 0x7fff)
#घोषणा C8SECTPFE_TAG_ENABLE             BIT(0)

#घोषणा C8SECTPFE_IB_PID_SET(x)          (C8SECTPFE_CHANNEL_OFFSET(x) + 0x0C)
#घोषणा C8SECTPFE_PID_OFFSET(x)          (x & 0x3f)
#घोषणा C8SECTPFE_PID_NUMBITS(x)         ((x << 6) & 0xfff)
#घोषणा C8SECTPFE_PID_ENABLE             BIT(31)

#घोषणा C8SECTPFE_IB_PKT_LEN(x)          (C8SECTPFE_CHANNEL_OFFSET(x) + 0x10)

#घोषणा C8SECTPFE_IB_BUFF_STRT(x)        (C8SECTPFE_CHANNEL_OFFSET(x) + 0x14)
#घोषणा C8SECTPFE_IB_BUFF_END(x)         (C8SECTPFE_CHANNEL_OFFSET(x) + 0x18)
#घोषणा C8SECTPFE_IB_READ_PNT(x)         (C8SECTPFE_CHANNEL_OFFSET(x) + 0x1C)
#घोषणा C8SECTPFE_IB_WRT_PNT(x)          (C8SECTPFE_CHANNEL_OFFSET(x) + 0x20)

#घोषणा C8SECTPFE_IB_PRI_THRLD(x)        (C8SECTPFE_CHANNEL_OFFSET(x) + 0x24)
#घोषणा C8SECTPFE_PRI_VALUE(x)           (x & 0x7fffff)
#घोषणा C8SECTPFE_PRI_LOWPRI(x)          ((x & 0xf) << 24)
#घोषणा C8SECTPFE_PRI_HIGHPRI(x)         ((x & 0xf) << 28)

#घोषणा C8SECTPFE_IB_STAT(x)             (C8SECTPFE_CHANNEL_OFFSET(x) + 0x28)
#घोषणा C8SECTPFE_STAT_FIFO_OVERFLOW(x)  (x & 0x1)
#घोषणा C8SECTPFE_STAT_BUFFER_OVERFLOW(x) (x & 0x2)
#घोषणा C8SECTPFE_STAT_OUTOFORDERRP(x)   (x & 0x4)
#घोषणा C8SECTPFE_STAT_PID_OVERFLOW(x)   (x & 0x8)
#घोषणा C8SECTPFE_STAT_PKT_OVERFLOW(x)   (x & 0x10)
#घोषणा C8SECTPFE_STAT_ERROR_PACKETS(x)  ((x >> 8) & 0xf)
#घोषणा C8SECTPFE_STAT_SHORT_PACKETS(x)  ((x >> 12) & 0xf)

#घोषणा C8SECTPFE_IB_MASK(x)             (C8SECTPFE_CHANNEL_OFFSET(x) + 0x2C)
#घोषणा C8SECTPFE_MASK_FIFO_OVERFLOW     BIT(0)
#घोषणा C8SECTPFE_MASK_BUFFER_OVERFLOW   BIT(1)
#घोषणा C8SECTPFE_MASK_OUTOFORDERRP(x)   BIT(2)
#घोषणा C8SECTPFE_MASK_PID_OVERFLOW(x)   BIT(3)
#घोषणा C8SECTPFE_MASK_PKT_OVERFLOW(x)   BIT(4)
#घोषणा C8SECTPFE_MASK_ERROR_PACKETS(x)  ((x & 0xf) << 8)
#घोषणा C8SECTPFE_MASK_SHORT_PACKETS(x)  ((x & 0xf) >> 12)

#घोषणा C8SECTPFE_IB_SYS(x)              (C8SECTPFE_CHANNEL_OFFSET(x) + 0x30)
#घोषणा C8SECTPFE_SYS_RESET              BIT(1)
#घोषणा C8SECTPFE_SYS_ENABLE             BIT(0)

/*
 * Poपूर्णांकer record data काष्ठाure required क्रम each input block
 * see Table 82 on page 167 of functional specअगरication.
 */

#घोषणा DMA_PRDS_MEMBASE	0x0 /* Internal sram base address */
#घोषणा DMA_PRDS_MEMTOP		0x4 /* Internal sram top address */

/*
 * TS packet size, including tag bytes added by input block,
 * rounded up to the next multiple of 8 bytes. The packet size,
 * including any tagging bytes and rounded up to the nearest
 * multiple of 8 bytes must be less than 255 bytes.
 */
#घोषणा DMA_PRDS_PKTSIZE	0x8
#घोषणा DMA_PRDS_TPENABLE	0xc

#घोषणा TP0_OFFSET		0x10
#घोषणा DMA_PRDS_BUSBASE_TP(x)	((0x10*x) + TP0_OFFSET)
#घोषणा DMA_PRDS_BUSTOP_TP(x)	((0x10*x) + TP0_OFFSET + 0x4)
#घोषणा DMA_PRDS_BUSWP_TP(x)	((0x10*x) + TP0_OFFSET + 0x8)
#घोषणा DMA_PRDS_BUSRP_TP(x)	((0x10*x) + TP0_OFFSET + 0xc)

#घोषणा DMA_PRDS_SIZE		(0x20)

#घोषणा DMA_MEMDMA_OFFSET	0x4000
#घोषणा DMA_IMEM_OFFSET		0x0
#घोषणा DMA_DMEM_OFFSET		0x4000
#घोषणा DMA_CPU			0x8000
#घोषणा DMA_PER_OFFSET		0xb000

#घोषणा DMA_MEMDMA_DMEM (DMA_MEMDMA_OFFSET + DMA_DMEM_OFFSET)
#घोषणा DMA_MEMDMA_IMEM (DMA_MEMDMA_OFFSET + DMA_IMEM_OFFSET)

/* XP70 Slim core regs */
#घोषणा DMA_CPU_ID	(DMA_MEMDMA_OFFSET + DMA_CPU + 0x0)
#घोषणा DMA_CPU_VCR	(DMA_MEMDMA_OFFSET + DMA_CPU + 0x4)
#घोषणा DMA_CPU_RUN	(DMA_MEMDMA_OFFSET + DMA_CPU + 0x8)
#घोषणा DMA_CPU_CLOCKGATE	(DMA_MEMDMA_OFFSET + DMA_CPU + 0xc)
#घोषणा DMA_CPU_PC	(DMA_MEMDMA_OFFSET + DMA_CPU + 0x20)

/* Enable Interrupt क्रम a IB */
#घोषणा DMA_PER_TPn_DREQ_MASK	(DMA_MEMDMA_OFFSET + DMA_PER_OFFSET + 0xd00)
/* Ack पूर्णांकerrupt by setting corresponding bit */
#घोषणा DMA_PER_TPn_DACK_SET	(DMA_MEMDMA_OFFSET + DMA_PER_OFFSET + 0xd80)
#घोषणा DMA_PER_TPn_DREQ	(DMA_MEMDMA_OFFSET + DMA_PER_OFFSET + 0xe00)
#घोषणा DMA_PER_TPn_DACK	(DMA_MEMDMA_OFFSET + DMA_PER_OFFSET + 0xe80)
#घोषणा DMA_PER_DREQ_MODE	(DMA_MEMDMA_OFFSET + DMA_PER_OFFSET + 0xf80)
#घोषणा DMA_PER_STBUS_SYNC	(DMA_MEMDMA_OFFSET + DMA_PER_OFFSET + 0xf88)
#घोषणा DMA_PER_STBUS_ACCESS	(DMA_MEMDMA_OFFSET + DMA_PER_OFFSET + 0xf8c)
#घोषणा DMA_PER_STBUS_ADDRESS	(DMA_MEMDMA_OFFSET + DMA_PER_OFFSET + 0xf90)
#घोषणा DMA_PER_IDLE_INT	(DMA_MEMDMA_OFFSET + DMA_PER_OFFSET + 0xfa8)
#घोषणा DMA_PER_PRIORITY	(DMA_MEMDMA_OFFSET + DMA_PER_OFFSET + 0xfac)
#घोषणा DMA_PER_MAX_OPCODE	(DMA_MEMDMA_OFFSET + DMA_PER_OFFSET + 0xfb0)
#घोषणा DMA_PER_MAX_CHUNK	(DMA_MEMDMA_OFFSET + DMA_PER_OFFSET + 0xfb4)
#घोषणा DMA_PER_PAGE_SIZE	(DMA_MEMDMA_OFFSET + DMA_PER_OFFSET + 0xfbc)
#घोषणा DMA_PER_MBOX_STATUS	(DMA_MEMDMA_OFFSET + DMA_PER_OFFSET + 0xfc0)
#घोषणा DMA_PER_MBOX_SET	(DMA_MEMDMA_OFFSET + DMA_PER_OFFSET + 0xfc8)
#घोषणा DMA_PER_MBOX_CLEAR	(DMA_MEMDMA_OFFSET + DMA_PER_OFFSET + 0xfd0)
#घोषणा DMA_PER_MBOX_MASK	(DMA_MEMDMA_OFFSET + DMA_PER_OFFSET + 0xfd8)
#घोषणा DMA_PER_INJECT_PKT_SRC	(DMA_MEMDMA_OFFSET + DMA_PER_OFFSET + 0xfe0)
#घोषणा DMA_PER_INJECT_PKT_DEST	(DMA_MEMDMA_OFFSET + DMA_PER_OFFSET + 0xfe4)
#घोषणा DMA_PER_INJECT_PKT_ADDR	(DMA_MEMDMA_OFFSET + DMA_PER_OFFSET + 0xfe8)
#घोषणा DMA_PER_INJECT_PKT	(DMA_MEMDMA_OFFSET + DMA_PER_OFFSET + 0xfec)
#घोषणा DMA_PER_PAT_PTR_INIT	(DMA_MEMDMA_OFFSET + DMA_PER_OFFSET + 0xff0)
#घोषणा DMA_PER_PAT_PTR		(DMA_MEMDMA_OFFSET + DMA_PER_OFFSET + 0xff4)
#घोषणा DMA_PER_SLEEP_MASK	(DMA_MEMDMA_OFFSET + DMA_PER_OFFSET + 0xff8)
#घोषणा DMA_PER_SLEEP_COUNTER	(DMA_MEMDMA_OFFSET + DMA_PER_OFFSET + 0xffc)
/* #घोषणा DMA_RF_CPUREGn	DMA_RFBASEADDR n=0 to 15) slim regsa */

/* The following are from DMA_DMEM_BaseAddress */
#घोषणा DMA_FIRMWARE_VERSION	(DMA_MEMDMA_OFFSET + DMA_DMEM_OFFSET + 0x0)
#घोषणा DMA_PTRREC_BASE		(DMA_MEMDMA_OFFSET + DMA_DMEM_OFFSET + 0x4)
#घोषणा DMA_PTRREC_INPUT_OFFSET	(DMA_MEMDMA_OFFSET + DMA_DMEM_OFFSET + 0x8)
#घोषणा DMA_ERRREC_BASE		(DMA_MEMDMA_OFFSET + DMA_DMEM_OFFSET + 0xc)
#घोषणा DMA_ERROR_RECORD(n)	((n*4) + DMA_ERRREC_BASE + 0x4)
#घोषणा DMA_IDLE_REQ		(DMA_MEMDMA_OFFSET + DMA_DMEM_OFFSET + 0x10)
#घोषणा IDLEREQ			BIT(31)

#घोषणा DMA_FIRMWARE_CONFIG	(DMA_MEMDMA_OFFSET + DMA_DMEM_OFFSET + 0x14)

/* Regs क्रम PID Filter */

#घोषणा PIDF_OFFSET		0x2800
#घोषणा PIDF_BASE(n)		((n*4) + PIDF_OFFSET)
#घोषणा PIDF_LEAK_ENABLE	(PIDF_OFFSET + 0x100)
#घोषणा PIDF_LEAK_STATUS	(PIDF_OFFSET + 0x108)
#घोषणा PIDF_LEAK_COUNT_RESET	(PIDF_OFFSET + 0x110)
#घोषणा PIDF_LEAK_COUNTER	(PIDF_OFFSET + 0x114)

#पूर्ण_अगर /* _C8SECTPFE_CORE_H_ */
