<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2005-2014, 2018-2020 Intel Corporation
 * Copyright (C) 2015-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_fh_h__
#घोषणा __iwl_fh_h__

#समावेश <linux/types.h>
#समावेश <linux/bitfield.h>

#समावेश "iwl-trans.h"

/****************************/
/* Flow Handler Definitions */
/****************************/

/**
 * This I/O area is directly पढ़ो/writable by driver (e.g. Linux uses ग_लिखोl())
 * Addresses are offsets from device's PCI hardware base address.
 */
#घोषणा FH_MEM_LOWER_BOUND                   (0x1000)
#घोषणा FH_MEM_UPPER_BOUND                   (0x2000)
#घोषणा FH_MEM_LOWER_BOUND_GEN2              (0xa06000)
#घोषणा FH_MEM_UPPER_BOUND_GEN2              (0xa08000)

/**
 * Keep-Warm (KW) buffer base address.
 *
 * Driver must allocate a 4KByte buffer that is क्रम keeping the
 * host DRAM घातered on (via dummy accesses to DRAM) to मुख्यtain low-latency
 * DRAM access when करोing Txing or Rxing.  The dummy accesses prevent host
 * from going पूर्णांकo a घातer-savings mode that would cause higher DRAM latency,
 * and possible data over/under-runs, beक्रमe all Tx/Rx is complete.
 *
 * Driver loads FH_KW_MEM_ADDR_REG with the physical address (bits 35:4)
 * of the buffer, which must be 4K aligned.  Once this is set up, the device
 * स्वतःmatically invokes keep-warm accesses when normal accesses might not
 * be sufficient to मुख्यtain fast DRAM response.
 *
 * Bit fields:
 *  31-0:  Keep-warm buffer physical base address [35:4], must be 4K aligned
 */
#घोषणा FH_KW_MEM_ADDR_REG		     (FH_MEM_LOWER_BOUND + 0x97C)


/**
 * TFD Circular Buffers Base (CBBC) addresses
 *
 * Device has 16 base poपूर्णांकer रेजिस्टरs, one क्रम each of 16 host-DRAM-resident
 * circular buffers (CBs/queues) containing Transmit Frame Descriptors (TFDs)
 * (see काष्ठा iwl_tfd_frame).  These 16 poपूर्णांकer रेजिस्टरs are offset by 0x04
 * bytes from one another.  Each TFD circular buffer in DRAM must be 256-byte
 * aligned (address bits 0-7 must be 0).
 * Later devices have 20 (5000 series) or 30 (higher) queues, but the रेजिस्टरs
 * क्रम them are in dअगरferent places.
 *
 * Bit fields in each poपूर्णांकer रेजिस्टर:
 *  27-0: TFD CB physical base address [35:8], must be 256-byte aligned
 */
#घोषणा FH_MEM_CBBC_0_15_LOWER_BOUND		(FH_MEM_LOWER_BOUND + 0x9D0)
#घोषणा FH_MEM_CBBC_0_15_UPPER_BOUND		(FH_MEM_LOWER_BOUND + 0xA10)
#घोषणा FH_MEM_CBBC_16_19_LOWER_BOUND		(FH_MEM_LOWER_BOUND + 0xBF0)
#घोषणा FH_MEM_CBBC_16_19_UPPER_BOUND		(FH_MEM_LOWER_BOUND + 0xC00)
#घोषणा FH_MEM_CBBC_20_31_LOWER_BOUND		(FH_MEM_LOWER_BOUND + 0xB20)
#घोषणा FH_MEM_CBBC_20_31_UPPER_BOUND		(FH_MEM_LOWER_BOUND + 0xB80)
/* 22000 TFD table address, 64 bit */
#घोषणा TFH_TFDQ_CBB_TABLE			(0x1C00)

/* Find TFD CB base poपूर्णांकer क्रम given queue */
अटल अंतरभूत अचिन्हित पूर्णांक FH_MEM_CBBC_QUEUE(काष्ठा iwl_trans *trans,
					     अचिन्हित पूर्णांक chnl)
अणु
	अगर (trans->trans_cfg->use_tfh) अणु
		WARN_ON_ONCE(chnl >= 64);
		वापस TFH_TFDQ_CBB_TABLE + 8 * chnl;
	पूर्ण
	अगर (chnl < 16)
		वापस FH_MEM_CBBC_0_15_LOWER_BOUND + 4 * chnl;
	अगर (chnl < 20)
		वापस FH_MEM_CBBC_16_19_LOWER_BOUND + 4 * (chnl - 16);
	WARN_ON_ONCE(chnl >= 32);
	वापस FH_MEM_CBBC_20_31_LOWER_BOUND + 4 * (chnl - 20);
पूर्ण

/* 22000 configuration रेजिस्टरs */

/*
 * TFH Configuration रेजिस्टर.
 *
 * BIT fields:
 *
 * Bits 3:0:
 * Define the maximum number of pending पढ़ो requests.
 * Maximum configuration value allowed is 0xC
 * Bits 9:8:
 * Define the maximum transfer size. (64 / 128 / 256)
 * Bit 10:
 * When bit is set and transfer size is set to 128B, the TFH will enable
 * पढ़ोing chunks of more than 64B only अगर the पढ़ो address is aligned to 128B.
 * In हाल of DRAM पढ़ो address which is not aligned to 128B, the TFH will
 * enable transfer size which करोesn't cross 64B DRAM address boundary.
*/
#घोषणा TFH_TRANSFER_MODE		(0x1F40)
#घोषणा TFH_TRANSFER_MAX_PENDING_REQ	0xc
#घोषणा TFH_CHUNK_SIZE_128			BIT(8)
#घोषणा TFH_CHUNK_SPLIT_MODE		BIT(10)
/*
 * Defines the offset address in dwords referring from the beginning of the
 * Tx CMD which will be updated in DRAM.
 * Note that the TFH offset address क्रम Tx CMD update is always referring to
 * the start of the TFD first TB.
 * In हाल of a DRAM Tx CMD update the TFH will update PN and Key ID
 */
#घोषणा TFH_TXCMD_UPDATE_CFG		(0x1F48)
/*
 * Controls TX DMA operation
 *
 * BIT fields:
 *
 * Bits 31:30: Enable the SRAM DMA channel.
 * Turning on bit 31 will kick the SRAM2DRAM DMA.
 * Note that the sram2dram may be enabled only after configuring the DRAM and
 * SRAM addresses रेजिस्टरs and the byte count रेजिस्टर.
 * Bits 25:24: Defines the पूर्णांकerrupt target upon dram2sram transfer करोne. When
 * set to 1 - पूर्णांकerrupt is sent to the driver
 * Bit 0: Indicates the snoop configuration
*/
#घोषणा TFH_SRV_DMA_CHNL0_CTRL	(0x1F60)
#घोषणा TFH_SRV_DMA_SNOOP	BIT(0)
#घोषणा TFH_SRV_DMA_TO_DRIVER	BIT(24)
#घोषणा TFH_SRV_DMA_START	BIT(31)

/* Defines the DMA SRAM ग_लिखो start address to transfer a data block */
#घोषणा TFH_SRV_DMA_CHNL0_SRAM_ADDR	(0x1F64)

/* Defines the 64bits DRAM start address to पढ़ो the DMA data block from */
#घोषणा TFH_SRV_DMA_CHNL0_DRAM_ADDR	(0x1F68)

/*
 * Defines the number of bytes to transfer from DRAM to SRAM.
 * Note that this रेजिस्टर may be configured with non-dword aligned size.
 */
#घोषणा TFH_SRV_DMA_CHNL0_BC	(0x1F70)

/**
 * Rx SRAM Control and Status Registers (RSCSR)
 *
 * These रेजिस्टरs provide handshake between driver and device क्रम the Rx queue
 * (this queue handles *all* command responses, notअगरications, Rx data, etc.
 * sent from uCode to host driver).  Unlike Tx, there is only one Rx
 * queue, and only one Rx DMA/FIFO channel.  Also unlike Tx, which can
 * concatenate up to 20 DRAM buffers to क्रमm a Tx frame, each Receive Buffer
 * Descriptor (RBD) poपूर्णांकs to only one Rx Buffer (RB); there is a 1:1
 * mapping between RBDs and RBs.
 *
 * Driver must allocate host DRAM memory क्रम the following, and set the
 * physical address of each पूर्णांकo device रेजिस्टरs:
 *
 * 1)  Receive Buffer Descriptor (RBD) circular buffer (CB), typically with 256
 *     entries (although any घातer of 2, up to 4096, is selectable by driver).
 *     Each entry (1 dword) poपूर्णांकs to a receive buffer (RB) of consistent size
 *     (typically 4K, although 8K or 16K are also selectable by driver).
 *     Driver sets up RB size and number of RBDs in the CB via Rx config
 *     रेजिस्टर FH_MEM_RCSR_CHNL0_CONFIG_REG.
 *
 *     Bit fields within one RBD:
 *     27-0:  Receive Buffer physical address bits [35:8], 256-byte aligned
 *
 *     Driver sets physical address [35:8] of base of RBD circular buffer
 *     पूर्णांकo FH_RSCSR_CHNL0_RBDCB_BASE_REG [27:0].
 *
 * 2)  Rx status buffer, 8 bytes, in which uCode indicates which Rx Buffers
 *     (RBs) have been filled, via a "write pointer", actually the index of
 *     the RB's corresponding RBD within the circular buffer.  Driver sets
 *     physical address [35:4] पूर्णांकo FH_RSCSR_CHNL0_STTS_WPTR_REG [31:0].
 *
 *     Bit fields in lower dword of Rx status buffer (upper dword not used
 *     by driver:
 *     31-12:  Not used by driver
 *     11- 0:  Index of last filled Rx buffer descriptor
 *             (device ग_लिखोs, driver पढ़ोs this value)
 *
 * As the driver prepares Receive Buffers (RBs) क्रम device to fill, driver must
 * enter poपूर्णांकers to these RBs पूर्णांकo contiguous RBD circular buffer entries,
 * and update the device's "write" index रेजिस्टर,
 * FH_RSCSR_CHNL0_RBDCB_WPTR_REG.
 *
 * This "write" index corresponds to the *next* RBD that the driver will make
 * available, i.e. one RBD past the tail of the पढ़ोy-to-fill RBDs within
 * the circular buffer.  This value should initially be 0 (beक्रमe preparing any
 * RBs), should be 8 after preparing the first 8 RBs (क्रम example), and must
 * wrap back to 0 at the end of the circular buffer (but करोn't wrap beक्रमe
 * "read" index has advanced past 1!  See below).
 * NOTE:  DEVICE EXPECTS THE WRITE INDEX TO BE INCREMENTED IN MULTIPLES OF 8.
 *
 * As the device fills RBs (referenced from contiguous RBDs within the circular
 * buffer), it updates the Rx status buffer in host DRAM, 2) described above,
 * to tell the driver the index of the latest filled RBD.  The driver must
 * पढ़ो this "read" index from DRAM after receiving an Rx पूर्णांकerrupt from device
 *
 * The driver must also पूर्णांकernally keep track of a third index, which is the
 * next RBD to process.  When receiving an Rx पूर्णांकerrupt, driver should process
 * all filled but unprocessed RBs up to, but not including, the RB
 * corresponding to the "read" index.  For example, अगर "read" index becomes "1",
 * driver may process the RB poपूर्णांकed to by RBD 0.  Depending on volume of
 * traffic, there may be many RBs to process.
 *
 * If पढ़ो index == ग_लिखो index, device thinks there is no room to put new data.
 * Due to this, the maximum number of filled RBs is 255, instead of 256.  To
 * be safe, make sure that there is a gap of at least 2 RBDs between "write"
 * and "read" indexes; that is, make sure that there are no more than 254
 * buffers रुकोing to be filled.
 */
#घोषणा FH_MEM_RSCSR_LOWER_BOUND	(FH_MEM_LOWER_BOUND + 0xBC0)
#घोषणा FH_MEM_RSCSR_UPPER_BOUND	(FH_MEM_LOWER_BOUND + 0xC00)
#घोषणा FH_MEM_RSCSR_CHNL0		(FH_MEM_RSCSR_LOWER_BOUND)

/**
 * Physical base address of 8-byte Rx Status buffer.
 * Bit fields:
 *  31-0: Rx status buffer physical base address [35:4], must 16-byte aligned.
 */
#घोषणा FH_RSCSR_CHNL0_STTS_WPTR_REG	(FH_MEM_RSCSR_CHNL0)

/**
 * Physical base address of Rx Buffer Descriptor Circular Buffer.
 * Bit fields:
 *  27-0:  RBD CD physical base address [35:8], must be 256-byte aligned.
 */
#घोषणा FH_RSCSR_CHNL0_RBDCB_BASE_REG	(FH_MEM_RSCSR_CHNL0 + 0x004)

/**
 * Rx ग_लिखो poपूर्णांकer (index, really!).
 * Bit fields:
 *  11-0:  Index of driver's most recent prepared-to-be-filled RBD, + 1.
 *         NOTE:  For 256-entry circular buffer, use only bits [7:0].
 */
#घोषणा FH_RSCSR_CHNL0_RBDCB_WPTR_REG	(FH_MEM_RSCSR_CHNL0 + 0x008)
#घोषणा FH_RSCSR_CHNL0_WPTR        (FH_RSCSR_CHNL0_RBDCB_WPTR_REG)

#घोषणा FW_RSCSR_CHNL0_RXDCB_RDPTR_REG	(FH_MEM_RSCSR_CHNL0 + 0x00c)
#घोषणा FH_RSCSR_CHNL0_RDPTR		FW_RSCSR_CHNL0_RXDCB_RDPTR_REG

/**
 * Rx Config/Status Registers (RCSR)
 * Rx Config Reg क्रम channel 0 (only channel used)
 *
 * Driver must initialize FH_MEM_RCSR_CHNL0_CONFIG_REG as follows क्रम
 * normal operation (see bit fields).
 *
 * Clearing FH_MEM_RCSR_CHNL0_CONFIG_REG to 0 turns off Rx DMA.
 * Driver should poll FH_MEM_RSSR_RX_STATUS_REG	क्रम
 * FH_RSSR_CHNL0_RX_STATUS_CHNL_IDLE (bit 24) beक्रमe continuing.
 *
 * Bit fields:
 * 31-30: Rx DMA channel enable: '00' off/pause, '01' छोड़ो at end of frame,
 *        '10' operate normally
 * 29-24: reserved
 * 23-20: # RBDs in circular buffer = 2^value; use "8" क्रम 256 RBDs (normal),
 *        min "5" क्रम 32 RBDs, max "12" क्रम 4096 RBDs.
 * 19-18: reserved
 * 17-16: size of each receive buffer; '00' 4K (normal), '01' 8K,
 *        '10' 12K, '11' 16K.
 * 15-14: reserved
 * 13-12: IRQ destination; '00' none, '01' host driver (normal operation)
 * 11- 4: समयout क्रम closing Rx buffer and पूर्णांकerrupting host (units 32 usec)
 *        typical value 0x10 (about 1/2 msec)
 *  3- 0: reserved
 */
#घोषणा FH_MEM_RCSR_LOWER_BOUND      (FH_MEM_LOWER_BOUND + 0xC00)
#घोषणा FH_MEM_RCSR_UPPER_BOUND      (FH_MEM_LOWER_BOUND + 0xCC0)
#घोषणा FH_MEM_RCSR_CHNL0            (FH_MEM_RCSR_LOWER_BOUND)

#घोषणा FH_MEM_RCSR_CHNL0_CONFIG_REG	(FH_MEM_RCSR_CHNL0)
#घोषणा FH_MEM_RCSR_CHNL0_RBDCB_WPTR	(FH_MEM_RCSR_CHNL0 + 0x8)
#घोषणा FH_MEM_RCSR_CHNL0_FLUSH_RB_REQ	(FH_MEM_RCSR_CHNL0 + 0x10)

#घोषणा FH_RCSR_CHNL0_RX_CONFIG_RB_TIMEOUT_MSK (0x00000FF0) /* bits 4-11 */
#घोषणा FH_RCSR_CHNL0_RX_CONFIG_IRQ_DEST_MSK   (0x00001000) /* bits 12 */
#घोषणा FH_RCSR_CHNL0_RX_CONFIG_SINGLE_FRAME_MSK (0x00008000) /* bit 15 */
#घोषणा FH_RCSR_CHNL0_RX_CONFIG_RB_SIZE_MSK   (0x00030000) /* bits 16-17 */
#घोषणा FH_RCSR_CHNL0_RX_CONFIG_RBDBC_SIZE_MSK (0x00F00000) /* bits 20-23 */
#घोषणा FH_RCSR_CHNL0_RX_CONFIG_DMA_CHNL_EN_MSK (0xC0000000) /* bits 30-31*/

#घोषणा FH_RCSR_RX_CONFIG_RBDCB_SIZE_POS	(20)
#घोषणा FH_RCSR_RX_CONFIG_REG_IRQ_RBTH_POS	(4)
#घोषणा RX_RB_TIMEOUT	(0x11)

#घोषणा FH_RCSR_RX_CONFIG_CHNL_EN_PAUSE_VAL         (0x00000000)
#घोषणा FH_RCSR_RX_CONFIG_CHNL_EN_PAUSE_खातापूर्ण_VAL     (0x40000000)
#घोषणा FH_RCSR_RX_CONFIG_CHNL_EN_ENABLE_VAL        (0x80000000)

#घोषणा FH_RCSR_RX_CONFIG_REG_VAL_RB_SIZE_4K    (0x00000000)
#घोषणा FH_RCSR_RX_CONFIG_REG_VAL_RB_SIZE_8K    (0x00010000)
#घोषणा FH_RCSR_RX_CONFIG_REG_VAL_RB_SIZE_12K   (0x00020000)
#घोषणा FH_RCSR_RX_CONFIG_REG_VAL_RB_SIZE_16K   (0x00030000)

#घोषणा FH_RCSR_CHNL0_RX_IGNORE_RXF_EMPTY              (0x00000004)
#घोषणा FH_RCSR_CHNL0_RX_CONFIG_IRQ_DEST_NO_INT_VAL    (0x00000000)
#घोषणा FH_RCSR_CHNL0_RX_CONFIG_IRQ_DEST_INT_HOST_VAL  (0x00001000)

/**
 * Rx Shared Status Registers (RSSR)
 *
 * After stopping Rx DMA channel (writing 0 to
 * FH_MEM_RCSR_CHNL0_CONFIG_REG), driver must poll
 * FH_MEM_RSSR_RX_STATUS_REG until Rx channel is idle.
 *
 * Bit fields:
 *  24:  1 = Channel 0 is idle
 *
 * FH_MEM_RSSR_SHARED_CTRL_REG and FH_MEM_RSSR_RX_ENABLE_ERR_IRQ2DRV
 * contain शेष values that should not be altered by the driver.
 */
#घोषणा FH_MEM_RSSR_LOWER_BOUND           (FH_MEM_LOWER_BOUND + 0xC40)
#घोषणा FH_MEM_RSSR_UPPER_BOUND           (FH_MEM_LOWER_BOUND + 0xD00)

#घोषणा FH_MEM_RSSR_SHARED_CTRL_REG       (FH_MEM_RSSR_LOWER_BOUND)
#घोषणा FH_MEM_RSSR_RX_STATUS_REG	(FH_MEM_RSSR_LOWER_BOUND + 0x004)
#घोषणा FH_MEM_RSSR_RX_ENABLE_ERR_IRQ2DRV\
					(FH_MEM_RSSR_LOWER_BOUND + 0x008)

#घोषणा FH_RSSR_CHNL0_RX_STATUS_CHNL_IDLE	(0x01000000)

#घोषणा FH_MEM_TFDIB_REG1_ADDR_BITSHIFT	28
#घोषणा FH_MEM_TB_MAX_LENGTH			(0x00020000)

/* 9000 rx series रेजिस्टरs */

#घोषणा RFH_Q0_FRBDCB_BA_LSB 0xA08000 /* 64 bit address */
#घोषणा RFH_Q_FRBDCB_BA_LSB(q) (RFH_Q0_FRBDCB_BA_LSB + (q) * 8)
/* Write index table */
#घोषणा RFH_Q0_FRBDCB_WIDX 0xA08080
#घोषणा RFH_Q_FRBDCB_WIDX(q) (RFH_Q0_FRBDCB_WIDX + (q) * 4)
/* Write index table - shaकरोw रेजिस्टरs */
#घोषणा RFH_Q0_FRBDCB_WIDX_TRG 0x1C80
#घोषणा RFH_Q_FRBDCB_WIDX_TRG(q) (RFH_Q0_FRBDCB_WIDX_TRG + (q) * 4)
/* Read index table */
#घोषणा RFH_Q0_FRBDCB_RIDX 0xA080C0
#घोषणा RFH_Q_FRBDCB_RIDX(q) (RFH_Q0_FRBDCB_RIDX + (q) * 4)
/* Used list table */
#घोषणा RFH_Q0_URBDCB_BA_LSB 0xA08100 /* 64 bit address */
#घोषणा RFH_Q_URBDCB_BA_LSB(q) (RFH_Q0_URBDCB_BA_LSB + (q) * 8)
/* Write index table */
#घोषणा RFH_Q0_URBDCB_WIDX 0xA08180
#घोषणा RFH_Q_URBDCB_WIDX(q) (RFH_Q0_URBDCB_WIDX + (q) * 4)
#घोषणा RFH_Q0_URBDCB_VAID 0xA081C0
#घोषणा RFH_Q_URBDCB_VAID(q) (RFH_Q0_URBDCB_VAID + (q) * 4)
/* stts */
#घोषणा RFH_Q0_URBD_STTS_WPTR_LSB 0xA08200 /*64 bits address */
#घोषणा RFH_Q_URBD_STTS_WPTR_LSB(q) (RFH_Q0_URBD_STTS_WPTR_LSB + (q) * 8)

#घोषणा RFH_Q0_ORB_WPTR_LSB 0xA08280
#घोषणा RFH_Q_ORB_WPTR_LSB(q) (RFH_Q0_ORB_WPTR_LSB + (q) * 8)
#घोषणा RFH_RBDBUF_RBD0_LSB 0xA08300
#घोषणा RFH_RBDBUF_RBD_LSB(q) (RFH_RBDBUF_RBD0_LSB + (q) * 8)

/**
 * RFH Status Register
 *
 * Bit fields:
 *
 * Bit 29: RBD_FETCH_IDLE
 * This status flag is set by the RFH when there is no active RBD fetch from
 * DRAM.
 * Once the RFH RBD controller starts fetching (or when there is a pending
 * RBD पढ़ो response from DRAM), this flag is immediately turned off.
 *
 * Bit 30: SRAM_DMA_IDLE
 * This status flag is set by the RFH when there is no active transaction from
 * SRAM to DRAM.
 * Once the SRAM to DRAM DMA is active, this flag is immediately turned off.
 *
 * Bit 31: RXF_DMA_IDLE
 * This status flag is set by the RFH when there is no active transaction from
 * RXF to DRAM.
 * Once the RXF-to-DRAM DMA is active, this flag is immediately turned off.
 */
#घोषणा RFH_GEN_STATUS		0xA09808
#घोषणा RFH_GEN_STATUS_GEN3	0xA07824
#घोषणा RBD_FETCH_IDLE	BIT(29)
#घोषणा SRAM_DMA_IDLE	BIT(30)
#घोषणा RXF_DMA_IDLE	BIT(31)

/* DMA configuration */
#घोषणा RFH_RXF_DMA_CFG		0xA09820
#घोषणा RFH_RXF_DMA_CFG_GEN3	0xA07880
/* RB size */
#घोषणा RFH_RXF_DMA_RB_SIZE_MASK (0x000F0000) /* bits 16-19 */
#घोषणा RFH_RXF_DMA_RB_SIZE_POS 16
#घोषणा RFH_RXF_DMA_RB_SIZE_1K	(0x1 << RFH_RXF_DMA_RB_SIZE_POS)
#घोषणा RFH_RXF_DMA_RB_SIZE_2K	(0x2 << RFH_RXF_DMA_RB_SIZE_POS)
#घोषणा RFH_RXF_DMA_RB_SIZE_4K	(0x4 << RFH_RXF_DMA_RB_SIZE_POS)
#घोषणा RFH_RXF_DMA_RB_SIZE_8K	(0x8 << RFH_RXF_DMA_RB_SIZE_POS)
#घोषणा RFH_RXF_DMA_RB_SIZE_12K	(0x9 << RFH_RXF_DMA_RB_SIZE_POS)
#घोषणा RFH_RXF_DMA_RB_SIZE_16K	(0xA << RFH_RXF_DMA_RB_SIZE_POS)
#घोषणा RFH_RXF_DMA_RB_SIZE_20K	(0xB << RFH_RXF_DMA_RB_SIZE_POS)
#घोषणा RFH_RXF_DMA_RB_SIZE_24K	(0xC << RFH_RXF_DMA_RB_SIZE_POS)
#घोषणा RFH_RXF_DMA_RB_SIZE_28K	(0xD << RFH_RXF_DMA_RB_SIZE_POS)
#घोषणा RFH_RXF_DMA_RB_SIZE_32K	(0xE << RFH_RXF_DMA_RB_SIZE_POS)
/* RB Circular Buffer size:defines the table sizes in RBD units */
#घोषणा RFH_RXF_DMA_RBDCB_SIZE_MASK (0x00F00000) /* bits 20-23 */
#घोषणा RFH_RXF_DMA_RBDCB_SIZE_POS 20
#घोषणा RFH_RXF_DMA_RBDCB_SIZE_8	(0x3 << RFH_RXF_DMA_RBDCB_SIZE_POS)
#घोषणा RFH_RXF_DMA_RBDCB_SIZE_16	(0x4 << RFH_RXF_DMA_RBDCB_SIZE_POS)
#घोषणा RFH_RXF_DMA_RBDCB_SIZE_32	(0x5 << RFH_RXF_DMA_RBDCB_SIZE_POS)
#घोषणा RFH_RXF_DMA_RBDCB_SIZE_64	(0x7 << RFH_RXF_DMA_RBDCB_SIZE_POS)
#घोषणा RFH_RXF_DMA_RBDCB_SIZE_128	(0x7 << RFH_RXF_DMA_RBDCB_SIZE_POS)
#घोषणा RFH_RXF_DMA_RBDCB_SIZE_256	(0x8 << RFH_RXF_DMA_RBDCB_SIZE_POS)
#घोषणा RFH_RXF_DMA_RBDCB_SIZE_512	(0x9 << RFH_RXF_DMA_RBDCB_SIZE_POS)
#घोषणा RFH_RXF_DMA_RBDCB_SIZE_1024	(0xA << RFH_RXF_DMA_RBDCB_SIZE_POS)
#घोषणा RFH_RXF_DMA_RBDCB_SIZE_2048	(0xB << RFH_RXF_DMA_RBDCB_SIZE_POS)
#घोषणा RFH_RXF_DMA_MIN_RB_SIZE_MASK	(0x03000000) /* bit 24-25 */
#घोषणा RFH_RXF_DMA_MIN_RB_SIZE_POS	24
#घोषणा RFH_RXF_DMA_MIN_RB_4_8		(3 << RFH_RXF_DMA_MIN_RB_SIZE_POS)
#घोषणा RFH_RXF_DMA_DROP_TOO_LARGE_MASK	(0x04000000) /* bit 26 */
#घोषणा RFH_RXF_DMA_SINGLE_FRAME_MASK	(0x20000000) /* bit 29 */
#घोषणा RFH_DMA_EN_MASK			(0xC0000000) /* bits 30-31*/
#घोषणा RFH_DMA_EN_ENABLE_VAL		BIT(31)

#घोषणा RFH_RXF_RXQ_ACTIVE 0xA0980C

#घोषणा RFH_GEN_CFG	0xA09800
#घोषणा RFH_GEN_CFG_SERVICE_DMA_SNOOP	BIT(0)
#घोषणा RFH_GEN_CFG_RFH_DMA_SNOOP	BIT(1)
#घोषणा RFH_GEN_CFG_RB_CHUNK_SIZE	BIT(4)
#घोषणा RFH_GEN_CFG_RB_CHUNK_SIZE_128	1
#घोषणा RFH_GEN_CFG_RB_CHUNK_SIZE_64	0
/* the driver assumes everywhere that the शेष RXQ is 0 */
#घोषणा RFH_GEN_CFG_DEFAULT_RXQ_NUM	0xF00
#घोषणा RFH_GEN_CFG_VAL(_n, _v)		FIELD_PREP(RFH_GEN_CFG_ ## _n, _v)

/* end of 9000 rx series रेजिस्टरs */

/* TFDB  Area - TFDs buffer table */
#घोषणा FH_MEM_TFDIB_DRAM_ADDR_LSB_MSK      (0xFFFFFFFF)
#घोषणा FH_TFDIB_LOWER_BOUND       (FH_MEM_LOWER_BOUND + 0x900)
#घोषणा FH_TFDIB_UPPER_BOUND       (FH_MEM_LOWER_BOUND + 0x958)
#घोषणा FH_TFDIB_CTRL0_REG(_chnl)  (FH_TFDIB_LOWER_BOUND + 0x8 * (_chnl))
#घोषणा FH_TFDIB_CTRL1_REG(_chnl)  (FH_TFDIB_LOWER_BOUND + 0x8 * (_chnl) + 0x4)

/**
 * Transmit DMA Channel Control/Status Registers (TCSR)
 *
 * Device has one configuration रेजिस्टर क्रम each of 8 Tx DMA/FIFO channels
 * supported in hardware (करोn't confuse these with the 16 Tx queues in DRAM,
 * which feed the DMA/FIFO channels); config regs are separated by 0x20 bytes.
 *
 * To use a Tx DMA channel, driver must initialize its
 * FH_TCSR_CHNL_TX_CONFIG_REG(chnl) with:
 *
 * FH_TCSR_TX_CONFIG_REG_VAL_DMA_CHNL_ENABLE |
 * FH_TCSR_TX_CONFIG_REG_VAL_DMA_CREDIT_ENABLE_VAL
 *
 * All other bits should be 0.
 *
 * Bit fields:
 * 31-30: Tx DMA channel enable: '00' off/pause, '01' छोड़ो at end of frame,
 *        '10' operate normally
 * 29- 4: Reserved, set to "0"
 *     3: Enable पूर्णांकernal DMA requests (1, normal operation), disable (0)
 *  2- 0: Reserved, set to "0"
 */
#घोषणा FH_TCSR_LOWER_BOUND  (FH_MEM_LOWER_BOUND + 0xD00)
#घोषणा FH_TCSR_UPPER_BOUND  (FH_MEM_LOWER_BOUND + 0xE60)

/* Find Control/Status reg क्रम given Tx DMA/FIFO channel */
#घोषणा FH_TCSR_CHNL_NUM                            (8)

/* TCSR: tx_config रेजिस्टर values */
#घोषणा FH_TCSR_CHNL_TX_CONFIG_REG(_chnl)	\
		(FH_TCSR_LOWER_BOUND + 0x20 * (_chnl))
#घोषणा FH_TCSR_CHNL_TX_CREDIT_REG(_chnl)	\
		(FH_TCSR_LOWER_BOUND + 0x20 * (_chnl) + 0x4)
#घोषणा FH_TCSR_CHNL_TX_BUF_STS_REG(_chnl)	\
		(FH_TCSR_LOWER_BOUND + 0x20 * (_chnl) + 0x8)

#घोषणा FH_TCSR_TX_CONFIG_REG_VAL_MSG_MODE_TXF		(0x00000000)
#घोषणा FH_TCSR_TX_CONFIG_REG_VAL_MSG_MODE_DRV		(0x00000001)

#घोषणा FH_TCSR_TX_CONFIG_REG_VAL_DMA_CREDIT_DISABLE	(0x00000000)
#घोषणा FH_TCSR_TX_CONFIG_REG_VAL_DMA_CREDIT_ENABLE	(0x00000008)

#घोषणा FH_TCSR_TX_CONFIG_REG_VAL_CIRQ_HOST_NOINT	(0x00000000)
#घोषणा FH_TCSR_TX_CONFIG_REG_VAL_CIRQ_HOST_ENDTFD	(0x00100000)
#घोषणा FH_TCSR_TX_CONFIG_REG_VAL_CIRQ_HOST_IFTFD	(0x00200000)

#घोषणा FH_TCSR_TX_CONFIG_REG_VAL_CIRQ_RTC_NOINT	(0x00000000)
#घोषणा FH_TCSR_TX_CONFIG_REG_VAL_CIRQ_RTC_ENDTFD	(0x00400000)
#घोषणा FH_TCSR_TX_CONFIG_REG_VAL_CIRQ_RTC_IFTFD	(0x00800000)

#घोषणा FH_TCSR_TX_CONFIG_REG_VAL_DMA_CHNL_PAUSE	(0x00000000)
#घोषणा FH_TCSR_TX_CONFIG_REG_VAL_DMA_CHNL_PAUSE_खातापूर्ण	(0x40000000)
#घोषणा FH_TCSR_TX_CONFIG_REG_VAL_DMA_CHNL_ENABLE	(0x80000000)

#घोषणा FH_TCSR_CHNL_TX_BUF_STS_REG_VAL_TFDB_EMPTY	(0x00000000)
#घोषणा FH_TCSR_CHNL_TX_BUF_STS_REG_VAL_TFDB_WAIT	(0x00002000)
#घोषणा FH_TCSR_CHNL_TX_BUF_STS_REG_VAL_TFDB_VALID	(0x00000003)

#घोषणा FH_TCSR_CHNL_TX_BUF_STS_REG_POS_TB_NUM		(20)
#घोषणा FH_TCSR_CHNL_TX_BUF_STS_REG_POS_TB_IDX		(12)

/**
 * Tx Shared Status Registers (TSSR)
 *
 * After stopping Tx DMA channel (writing 0 to
 * FH_TCSR_CHNL_TX_CONFIG_REG(chnl)), driver must poll
 * FH_TSSR_TX_STATUS_REG until selected Tx channel is idle
 * (channel's buffers empty | no pending requests).
 *
 * Bit fields:
 * 31-24:  1 = Channel buffers empty (channel 7:0)
 * 23-16:  1 = No pending requests (channel 7:0)
 */
#घोषणा FH_TSSR_LOWER_BOUND		(FH_MEM_LOWER_BOUND + 0xEA0)
#घोषणा FH_TSSR_UPPER_BOUND		(FH_MEM_LOWER_BOUND + 0xEC0)

#घोषणा FH_TSSR_TX_STATUS_REG		(FH_TSSR_LOWER_BOUND + 0x010)

/**
 * Bit fields क्रम TSSR(Tx Shared Status & Control) error status रेजिस्टर:
 * 31:  Indicates an address error when accessed to पूर्णांकernal memory
 *	uCode/driver must ग_लिखो "1" in order to clear this flag
 * 30:  Indicates that Host did not send the expected number of dwords to FH
 *	uCode/driver must ग_लिखो "1" in order to clear this flag
 * 16-9:Each status bit is क्रम one channel. Indicates that an (Error) ActDMA
 *	command was received from the scheduler जबतक the TRB was alपढ़ोy full
 *	with previous command
 *	uCode/driver must ग_लिखो "1" in order to clear this flag
 * 7-0: Each status bit indicates a channel's TxCredit error. When an error
 *	bit is set, it indicates that the FH has received a full indication
 *	from the RTC TxFIFO and the current value of the TxCredit counter was
 *	not equal to zero. This mean that the credit mechanism was not
 *	synchronized to the TxFIFO status
 *	uCode/driver must ग_लिखो "1" in order to clear this flag
 */
#घोषणा FH_TSSR_TX_ERROR_REG		(FH_TSSR_LOWER_BOUND + 0x018)
#घोषणा FH_TSSR_TX_MSG_CONFIG_REG	(FH_TSSR_LOWER_BOUND + 0x008)

#घोषणा FH_TSSR_TX_STATUS_REG_MSK_CHNL_IDLE(_chnl) ((1 << (_chnl)) << 16)

/* Tx service channels */
#घोषणा FH_SRVC_CHNL		(9)
#घोषणा FH_SRVC_LOWER_BOUND	(FH_MEM_LOWER_BOUND + 0x9C8)
#घोषणा FH_SRVC_UPPER_BOUND	(FH_MEM_LOWER_BOUND + 0x9D0)
#घोषणा FH_SRVC_CHNL_SRAM_ADDR_REG(_chnl) \
		(FH_SRVC_LOWER_BOUND + ((_chnl) - 9) * 0x4)

#घोषणा FH_TX_CHICKEN_BITS_REG	(FH_MEM_LOWER_BOUND + 0xE98)
#घोषणा FH_TX_TRB_REG(_chan)	(FH_MEM_LOWER_BOUND + 0x958 + (_chan) * 4)

/* Inकाष्ठा FH to increment the retry count of a packet when
 * it is brought from the memory to TX-FIFO
 */
#घोषणा FH_TX_CHICKEN_BITS_SCD_AUTO_RETRY_EN	(0x00000002)

#घोषणा RX_POOL_SIZE(rbds)	((rbds) - 1 +	\
				 IWL_MAX_RX_HW_QUEUES *	\
				 (RX_CLAIM_REQ_ALLOC - RX_POST_REQ_ALLOC))
/* cb size is the exponent */
#घोषणा RX_QUEUE_CB_SIZE(x)	ilog2(x)

#घोषणा RX_QUEUE_SIZE                         256
#घोषणा RX_QUEUE_MASK                         255
#घोषणा RX_QUEUE_SIZE_LOG                     8

/**
 * काष्ठा iwl_rb_status - reserve buffer status
 * 	host memory mapped FH रेजिस्टरs
 * @बंदd_rb_num [0:11] - Indicates the index of the RB which was बंदd
 * @बंदd_fr_num [0:11] - Indicates the index of the RX Frame which was बंदd
 * @finished_rb_num [0:11] - Indicates the index of the current RB
 * 	in which the last frame was written to
 * @finished_fr_num [0:11] - Indicates the index of the RX Frame
 * 	which was transferred
 */
काष्ठा iwl_rb_status अणु
	__le16 बंदd_rb_num;
	__le16 बंदd_fr_num;
	__le16 finished_rb_num;
	__le16 finished_fr_nam;
	__le32 __unused;
पूर्ण __packed;


#घोषणा TFD_QUEUE_SIZE_MAX      (256)
#घोषणा TFD_QUEUE_SIZE_MAX_GEN3 (65536)
/* cb size is the exponent - 3 */
#घोषणा TFD_QUEUE_CB_SIZE(x)	(ilog2(x) - 3)
#घोषणा TFD_QUEUE_SIZE_BC_DUP	(64)
#घोषणा TFD_QUEUE_BC_SIZE	(TFD_QUEUE_SIZE_MAX + TFD_QUEUE_SIZE_BC_DUP)
#घोषणा TFD_QUEUE_BC_SIZE_GEN3	1024
#घोषणा IWL_TX_DMA_MASK        DMA_BIT_MASK(36)
#घोषणा IWL_NUM_OF_TBS		20
#घोषणा IWL_TFH_NUM_TBS		25

अटल अंतरभूत u8 iwl_get_dma_hi_addr(dma_addr_t addr)
अणु
	वापस (माप(addr) > माप(u32) ? upper_32_bits(addr) : 0) & 0xF;
पूर्ण

/**
 * क्रमागत iwl_tfd_tb_hi_n_len - TB hi_n_len bits
 * @TB_HI_N_LEN_ADDR_HI_MSK: high 4 bits (to make it 36) of DMA address
 * @TB_HI_N_LEN_LEN_MSK: length of the TB
 */
क्रमागत iwl_tfd_tb_hi_n_len अणु
	TB_HI_N_LEN_ADDR_HI_MSK	= 0xf,
	TB_HI_N_LEN_LEN_MSK	= 0xfff0,
पूर्ण;

/**
 * काष्ठा iwl_tfd_tb transmit buffer descriptor within transmit frame descriptor
 *
 * This काष्ठाure contains dma address and length of transmission address
 *
 * @lo: low [31:0] portion of the dma address of TX buffer
 * 	every even is unaligned on 16 bit boundary
 * @hi_n_len: &क्रमागत iwl_tfd_tb_hi_n_len
 */
काष्ठा iwl_tfd_tb अणु
	__le32 lo;
	__le16 hi_n_len;
पूर्ण __packed;

/**
 * काष्ठा iwl_tfh_tb transmit buffer descriptor within transmit frame descriptor
 *
 * This काष्ठाure contains dma address and length of transmission address
 *
 * @tb_len length of the tx buffer
 * @addr 64 bits dma address
 */
काष्ठा iwl_tfh_tb अणु
	__le16 tb_len;
	__le64 addr;
पूर्ण __packed;

/**
 * Each Tx queue uses a circular buffer of 256 TFDs stored in host DRAM.
 * Both driver and device share these circular buffers, each of which must be
 * contiguous 256 TFDs.
 * For pre 22000 HW it is 256 x 128 bytes-per-TFD = 32 KBytes
 * For 22000 HW and on it is 256 x 256 bytes-per-TFD = 65 KBytes
 *
 * Driver must indicate the physical address of the base of each
 * circular buffer via the FH_MEM_CBBC_QUEUE रेजिस्टरs.
 *
 * Each TFD contains poपूर्णांकer/size inक्रमmation क्रम up to 20 / 25 data buffers
 * in host DRAM.  These buffers collectively contain the (one) frame described
 * by the TFD.  Each buffer must be a single contiguous block of memory within
 * itself, but buffers may be scattered in host DRAM.  Each buffer has max size
 * of (4K - 4).  The concatenates all of a TFD's buffers पूर्णांकo a single
 * Tx frame, up to 8 KBytes in size.
 *
 * A maximum of 255 (not 256!) TFDs may be on a queue रुकोing क्रम Tx.
 */

/**
 * काष्ठा iwl_tfd - Transmit Frame Descriptor (TFD)
 * @ __reserved1[3] reserved
 * @ num_tbs 0-4 number of active tbs
 *	     5   reserved
 *	     6-7 padding (not used)
 * @ tbs[20]	transmit frame buffer descriptors
 * @ __pad	padding
 */
काष्ठा iwl_tfd अणु
	u8 __reserved1[3];
	u8 num_tbs;
	काष्ठा iwl_tfd_tb tbs[IWL_NUM_OF_TBS];
	__le32 __pad;
पूर्ण __packed;

/**
 * काष्ठा iwl_tfh_tfd - Transmit Frame Descriptor (TFD)
 * @ num_tbs 0-4 number of active tbs
 *	     5 -15   reserved
 * @ tbs[25]	transmit frame buffer descriptors
 * @ __pad	padding
 */
काष्ठा iwl_tfh_tfd अणु
	__le16 num_tbs;
	काष्ठा iwl_tfh_tb tbs[IWL_TFH_NUM_TBS];
	__le32 __pad;
पूर्ण __packed;

/* Keep Warm Size */
#घोषणा IWL_KW_SIZE 0x1000	/* 4k */

/* Fixed (non-configurable) rx data from phy */

/**
 * काष्ठा iwlagn_schedq_bc_tbl scheduler byte count table
 *	base physical address provided by SCD_DRAM_BASE_ADDR
 * For devices up to 22000:
 * @tfd_offset  0-12 - tx command byte count
 *		12-16 - station index
 * For 22000:
 * @tfd_offset  0-12 - tx command byte count
 *		12-13 - number of 64 byte chunks
 *		14-16 - reserved
 */
काष्ठा iwlagn_scd_bc_tbl अणु
	__le16 tfd_offset[TFD_QUEUE_BC_SIZE];
पूर्ण __packed;

/**
 * काष्ठा iwl_gen3_bc_tbl scheduler byte count table gen3
 * For AX210 and on:
 * @tfd_offset: 0-12 - tx command byte count
 *		12-13 - number of 64 byte chunks
 *		14-16 - reserved
 */
काष्ठा iwl_gen3_bc_tbl अणु
	__le16 tfd_offset[TFD_QUEUE_BC_SIZE_GEN3];
पूर्ण __packed;

#पूर्ण_अगर /* !__iwl_fh_h__ */
