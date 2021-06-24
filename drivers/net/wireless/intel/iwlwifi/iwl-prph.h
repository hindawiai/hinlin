<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2005-2014, 2018-2020 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016 Intel Deutschland GmbH
 */
#अगर_अघोषित	__iwl_prph_h__
#घोषणा __iwl_prph_h__
#समावेश <linux/bitfield.h>

/*
 * Registers in this file are पूर्णांकernal, not PCI bus memory mapped.
 * Driver accesses these via HBUS_TARG_PRPH_* रेजिस्टरs.
 */
#घोषणा PRPH_BASE	(0x00000)
#घोषणा PRPH_END	(0xFFFFF)

/* APMG (घातer management) स्थिरants */
#घोषणा APMG_BASE			(PRPH_BASE + 0x3000)
#घोषणा APMG_CLK_CTRL_REG		(APMG_BASE + 0x0000)
#घोषणा APMG_CLK_EN_REG			(APMG_BASE + 0x0004)
#घोषणा APMG_CLK_DIS_REG		(APMG_BASE + 0x0008)
#घोषणा APMG_PS_CTRL_REG		(APMG_BASE + 0x000c)
#घोषणा APMG_PCIDEV_STT_REG		(APMG_BASE + 0x0010)
#घोषणा APMG_RFKILL_REG			(APMG_BASE + 0x0014)
#घोषणा APMG_RTC_INT_STT_REG		(APMG_BASE + 0x001c)
#घोषणा APMG_RTC_INT_MSK_REG		(APMG_BASE + 0x0020)
#घोषणा APMG_DIGITAL_SVR_REG		(APMG_BASE + 0x0058)
#घोषणा APMG_ANALOG_SVR_REG		(APMG_BASE + 0x006C)

#घोषणा APMS_CLK_VAL_MRB_FUNC_MODE	(0x00000001)
#घोषणा APMG_CLK_VAL_DMA_CLK_RQT	(0x00000200)
#घोषणा APMG_CLK_VAL_BSM_CLK_RQT	(0x00000800)

#घोषणा APMG_PS_CTRL_EARLY_PWR_OFF_RESET_DIS	(0x00400000)
#घोषणा APMG_PS_CTRL_VAL_RESET_REQ		(0x04000000)
#घोषणा APMG_PS_CTRL_MSK_PWR_SRC		(0x03000000)
#घोषणा APMG_PS_CTRL_VAL_PWR_SRC_VMAIN		(0x00000000)
#घोषणा APMG_PS_CTRL_VAL_PWR_SRC_VAUX		(0x02000000)
#घोषणा APMG_SVR_VOLTAGE_CONFIG_BIT_MSK	(0x000001E0) /* bit 8:5 */
#घोषणा APMG_SVR_DIGITAL_VOLTAGE_1_32		(0x00000060)

#घोषणा APMG_PCIDEV_STT_VAL_PERSIST_DIS	(0x00000200)
#घोषणा APMG_PCIDEV_STT_VAL_L1_ACT_DIS	(0x00000800)
#घोषणा APMG_PCIDEV_STT_VAL_WAKE_ME	(0x00004000)

#घोषणा APMG_RTC_INT_STT_RFKILL		(0x10000000)

/* Device प्रणाली समय */
#घोषणा DEVICE_SYSTEM_TIME_REG 0xA0206C

/* Device NMI रेजिस्टर and value क्रम 8000 family and lower hw's */
#घोषणा DEVICE_SET_NMI_REG 0x00a01c30
#घोषणा DEVICE_SET_NMI_VAL_DRV BIT(7)
/* Device NMI रेजिस्टर and value क्रम 9000 family and above hw's */
#घोषणा UREG_NIC_SET_NMI_DRIVER 0x00a05c10
#घोषणा UREG_NIC_SET_NMI_DRIVER_NMI_FROM_DRIVER BIT(24)
#घोषणा UREG_NIC_SET_NMI_DRIVER_RESET_HANDSHAKE (BIT(24) | BIT(25))

/* Shared रेजिस्टरs (0x0..0x3ff, via target indirect or periphery */
#घोषणा SHR_BASE	0x00a10000

/* Shared GP1 रेजिस्टर */
#घोषणा SHR_APMG_GP1_REG		0x01dc
#घोषणा SHR_APMG_GP1_REG_PRPH		(SHR_BASE + SHR_APMG_GP1_REG)
#घोषणा SHR_APMG_GP1_WF_XTAL_LP_EN	0x00000004
#घोषणा SHR_APMG_GP1_CHICKEN_BIT_SELECT	0x80000000

/* Shared DL_CFG रेजिस्टर */
#घोषणा SHR_APMG_DL_CFG_REG			0x01c4
#घोषणा SHR_APMG_DL_CFG_REG_PRPH		(SHR_BASE + SHR_APMG_DL_CFG_REG)
#घोषणा SHR_APMG_DL_CFG_RTCS_CLK_SELECTOR_MSK	0x000000c0
#घोषणा SHR_APMG_DL_CFG_RTCS_CLK_INTERNAL_XTAL	0x00000080
#घोषणा SHR_APMG_DL_CFG_DL_CLOCK_POWER_UP	0x00000100

/* Shared APMG_XTAL_CFG रेजिस्टर */
#घोषणा SHR_APMG_XTAL_CFG_REG		0x1c0
#घोषणा SHR_APMG_XTAL_CFG_XTAL_ON_REQ	0x80000000

/*
 * Device reset क्रम family 8000
 * ग_लिखो to bit 24 in order to reset the CPU
*/
#घोषणा RELEASE_CPU_RESET		(0x300C)
#घोषणा RELEASE_CPU_RESET_BIT		BIT(24)

/*****************************************************************************
 *                        7000/3000 series SHR DTS addresses                 *
 *****************************************************************************/

#घोषणा SHR_MISC_WFM_DTS_EN	(0x00a10024)
#घोषणा DTSC_CFG_MODE		(0x00a10604)
#घोषणा DTSC_VREF_AVG		(0x00a10648)
#घोषणा DTSC_VREF5_AVG		(0x00a1064c)
#घोषणा DTSC_CFG_MODE_PERIODIC	(0x2)
#घोषणा DTSC_PTAT_AVG		(0x00a10650)


/**
 * Tx Scheduler
 *
 * The Tx Scheduler selects the next frame to be transmitted, choosing TFDs
 * (Transmit Frame Descriptors) from up to 16 circular Tx queues resident in
 * host DRAM.  It steers each frame's Tx command (which contains the frame
 * data) पूर्णांकo one of up to 7 prioritized Tx DMA FIFO channels within the
 * device.  A queue maps to only one (selectable by driver) Tx DMA channel,
 * but one DMA channel may take input from several queues.
 *
 * Tx DMA FIFOs have dedicated purposes.
 *
 * For 5000 series and up, they are used dअगरferently
 * (cf. iwl5000_शेष_queue_to_tx_fअगरo in iwl-5000.c):
 *
 * 0 -- EDCA BK (background) frames, lowest priority
 * 1 -- EDCA BE (best efक्रमt) frames, normal priority
 * 2 -- EDCA VI (video) frames, higher priority
 * 3 -- EDCA VO (voice) and management frames, highest priority
 * 4 -- unused
 * 5 -- unused
 * 6 -- unused
 * 7 -- Commands
 *
 * Driver should normally map queues 0-6 to Tx DMA/FIFO channels 0-6.
 * In addition, driver can map the reमुख्यing queues to Tx DMA/FIFO
 * channels 0-3 to support 11n aggregation via EDCA DMA channels.
 *
 * The driver sets up each queue to work in one of two modes:
 *
 * 1)  Scheduler-Ack, in which the scheduler स्वतःmatically supports a
 *     block-ack (BA) winकरोw of up to 64 TFDs.  In this mode, each queue
 *     contains TFDs क्रम a unique combination of Recipient Address (RA)
 *     and Traffic Identअगरier (TID), that is, traffic of a given
 *     Quality-Of-Service (QOS) priority, destined क्रम a single station.
 *
 *     In scheduler-ack mode, the scheduler keeps track of the Tx status of
 *     each frame within the BA winकरोw, including whether it's been transmitted,
 *     and whether it's been acknowledged by the receiving station.  The device
 *     स्वतःmatically processes block-acks received from the receiving STA,
 *     and reschedules un-acked frames to be retransmitted (successful
 *     Tx completion may end up being out-of-order).
 *
 *     The driver must मुख्यtain the queue's Byte Count table in host DRAM
 *     क्रम this mode.
 *     This mode करोes not support fragmentation.
 *
 * 2)  FIFO (a.k.a. non-Scheduler-ACK), in which each TFD is processed in order.
 *     The device may स्वतःmatically retry Tx, but will retry only one frame
 *     at a समय, until receiving ACK from receiving station, or reaching
 *     retry limit and giving up.
 *
 *     The command queue (#4/#9) must use this mode!
 *     This mode करोes not require use of the Byte Count table in host DRAM.
 *
 * Driver controls scheduler operation via 3 means:
 * 1)  Scheduler रेजिस्टरs
 * 2)  Shared scheduler data base in पूर्णांकernal SRAM
 * 3)  Shared data in host DRAM
 *
 * Initialization:
 *
 * When loading, driver should allocate memory क्रम:
 * 1)  16 TFD circular buffers, each with space क्रम (typically) 256 TFDs.
 * 2)  16 Byte Count circular buffers in 16 KBytes contiguous memory
 *     (1024 bytes क्रम each queue).
 *
 * After receiving "Alive" response from uCode, driver must initialize
 * the scheduler (especially क्रम queue #4/#9, the command queue, otherwise
 * the driver can't issue commands!):
 */
#घोषणा SCD_MEM_LOWER_BOUND		(0x0000)

/**
 * Max Tx winकरोw size is the max number of contiguous TFDs that the scheduler
 * can keep track of at one समय when creating block-ack chains of frames.
 * Note that "64" matches the number of ack bits in a block-ack packet.
 */
#घोषणा SCD_WIN_SIZE				64
#घोषणा SCD_FRAME_LIMIT				64

#घोषणा SCD_TXFIFO_POS_TID			(0)
#घोषणा SCD_TXFIFO_POS_RA			(4)
#घोषणा SCD_QUEUE_RA_TID_MAP_RATID_MSK	(0x01FF)

/* agn SCD */
#घोषणा SCD_QUEUE_STTS_REG_POS_TXF	(0)
#घोषणा SCD_QUEUE_STTS_REG_POS_ACTIVE	(3)
#घोषणा SCD_QUEUE_STTS_REG_POS_WSL	(4)
#घोषणा SCD_QUEUE_STTS_REG_POS_SCD_ACT_EN (19)
#घोषणा SCD_QUEUE_STTS_REG_MSK		(0x017F0000)

#घोषणा SCD_QUEUE_CTX_REG1_CREDIT		(0x00FFFF00)
#घोषणा SCD_QUEUE_CTX_REG1_SUPER_CREDIT		(0xFF000000)
#घोषणा SCD_QUEUE_CTX_REG1_VAL(_n, _v)		FIELD_PREP(SCD_QUEUE_CTX_REG1_ ## _n, _v)

#घोषणा SCD_QUEUE_CTX_REG2_WIN_SIZE		(0x0000007F)
#घोषणा SCD_QUEUE_CTX_REG2_FRAME_LIMIT		(0x007F0000)
#घोषणा SCD_QUEUE_CTX_REG2_VAL(_n, _v)		FIELD_PREP(SCD_QUEUE_CTX_REG2_ ## _n, _v)

#घोषणा SCD_GP_CTRL_ENABLE_31_QUEUES		BIT(0)
#घोषणा SCD_GP_CTRL_AUTO_ACTIVE_MODE		BIT(18)

/* Context Data */
#घोषणा SCD_CONTEXT_MEM_LOWER_BOUND	(SCD_MEM_LOWER_BOUND + 0x600)
#घोषणा SCD_CONTEXT_MEM_UPPER_BOUND	(SCD_MEM_LOWER_BOUND + 0x6A0)

/* Tx status */
#घोषणा SCD_TX_STTS_MEM_LOWER_BOUND	(SCD_MEM_LOWER_BOUND + 0x6A0)
#घोषणा SCD_TX_STTS_MEM_UPPER_BOUND	(SCD_MEM_LOWER_BOUND + 0x7E0)

/* Translation Data */
#घोषणा SCD_TRANS_TBL_MEM_LOWER_BOUND	(SCD_MEM_LOWER_BOUND + 0x7E0)
#घोषणा SCD_TRANS_TBL_MEM_UPPER_BOUND	(SCD_MEM_LOWER_BOUND + 0x808)

#घोषणा SCD_CONTEXT_QUEUE_OFFSET(x)\
	(SCD_CONTEXT_MEM_LOWER_BOUND + ((x) * 8))

#घोषणा SCD_TX_STTS_QUEUE_OFFSET(x)\
	(SCD_TX_STTS_MEM_LOWER_BOUND + ((x) * 16))

#घोषणा SCD_TRANS_TBL_OFFSET_QUEUE(x) \
	((SCD_TRANS_TBL_MEM_LOWER_BOUND + ((x) * 2)) & 0xfffc)

#घोषणा SCD_BASE			(PRPH_BASE + 0xa02c00)

#घोषणा SCD_SRAM_BASE_ADDR	(SCD_BASE + 0x0)
#घोषणा SCD_DRAM_BASE_ADDR	(SCD_BASE + 0x8)
#घोषणा SCD_AIT			(SCD_BASE + 0x0c)
#घोषणा SCD_TXFACT		(SCD_BASE + 0x10)
#घोषणा SCD_ACTIVE		(SCD_BASE + 0x14)
#घोषणा SCD_QUEUECHAIN_SEL	(SCD_BASE + 0xe8)
#घोषणा SCD_CHAINEXT_EN		(SCD_BASE + 0x244)
#घोषणा SCD_AGGR_SEL		(SCD_BASE + 0x248)
#घोषणा SCD_INTERRUPT_MASK	(SCD_BASE + 0x108)
#घोषणा SCD_GP_CTRL		(SCD_BASE + 0x1a8)
#घोषणा SCD_EN_CTRL		(SCD_BASE + 0x254)

/*********************** END TX SCHEDULER *************************************/

/* Oscillator घड़ी */
#घोषणा OSC_CLK				(0xa04068)
#घोषणा OSC_CLK_FORCE_CONTROL		(0x8)

#घोषणा FH_UCODE_LOAD_STATUS		(0x1AF0)

/*
 * Replacing FH_UCODE_LOAD_STATUS
 * This रेजिस्टर is ग_लिखोn by driver and is पढ़ो by uCode during boot flow.
 * Note this address is cleared after MAC reset.
 */
#घोषणा UREG_UCODE_LOAD_STATUS		(0xa05c40)
#घोषणा UREG_CPU_INIT_RUN		(0xa05c44)

#घोषणा LMPM_SECURE_UCODE_LOAD_CPU1_HDR_ADDR	(0x1E78)
#घोषणा LMPM_SECURE_UCODE_LOAD_CPU2_HDR_ADDR	(0x1E7C)

#घोषणा LMPM_SECURE_CPU1_HDR_MEM_SPACE		(0x420000)
#घोषणा LMPM_SECURE_CPU2_HDR_MEM_SPACE		(0x420400)

#घोषणा LMAC2_PRPH_OFFSET		(0x100000)

/* Rx FIFO */
#घोषणा RXF_SIZE_ADDR			(0xa00c88)
#घोषणा RXF_RD_D_SPACE			(0xa00c40)
#घोषणा RXF_RD_WR_PTR			(0xa00c50)
#घोषणा RXF_RD_RD_PTR			(0xa00c54)
#घोषणा RXF_RD_FENCE_PTR		(0xa00c4c)
#घोषणा RXF_SET_FENCE_MODE		(0xa00c14)
#घोषणा RXF_LD_WR2FENCE		(0xa00c1c)
#घोषणा RXF_FIFO_RD_FENCE_INC		(0xa00c68)
#घोषणा RXF_SIZE_BYTE_CND_POS		(7)
#घोषणा RXF_SIZE_BYTE_CNT_MSK		(0x3ff << RXF_SIZE_BYTE_CND_POS)
#घोषणा RXF_DIFF_FROM_PREV		(0x200)
#घोषणा RXF2C_DIFF_FROM_PREV		(0x4e00)

#घोषणा RXF_LD_FENCE_OFFSET_ADDR	(0xa00c10)
#घोषणा RXF_FIFO_RD_FENCE_ADDR		(0xa00c0c)

/* Tx FIFO */
#घोषणा TXF_FIFO_ITEM_CNT		(0xa00438)
#घोषणा TXF_WR_PTR			(0xa00414)
#घोषणा TXF_RD_PTR			(0xa00410)
#घोषणा TXF_FENCE_PTR			(0xa00418)
#घोषणा TXF_LOCK_FENCE			(0xa00424)
#घोषणा TXF_LARC_NUM			(0xa0043c)
#घोषणा TXF_READ_MODIFY_DATA		(0xa00448)
#घोषणा TXF_READ_MODIFY_ADDR		(0xa0044c)

/* UMAC Internal Tx Fअगरo */
#घोषणा TXF_CPU2_FIFO_ITEM_CNT		(0xA00538)
#घोषणा TXF_CPU2_WR_PTR		(0xA00514)
#घोषणा TXF_CPU2_RD_PTR		(0xA00510)
#घोषणा TXF_CPU2_FENCE_PTR		(0xA00518)
#घोषणा TXF_CPU2_LOCK_FENCE		(0xA00524)
#घोषणा TXF_CPU2_NUM			(0xA0053C)
#घोषणा TXF_CPU2_READ_MODIFY_DATA	(0xA00548)
#घोषणा TXF_CPU2_READ_MODIFY_ADDR	(0xA0054C)

/* Radio रेजिस्टरs access */
#घोषणा RSP_RADIO_CMD			(0xa02804)
#घोषणा RSP_RADIO_RDDAT			(0xa02814)
#घोषणा RADIO_RSP_ADDR_POS		(6)
#घोषणा RADIO_RSP_RD_CMD		(3)

/* LTR control (Qu only) */
#घोषणा HPM_MAC_LTR_CSR			0xa0348c
#घोषणा HPM_MAC_LRT_ENABLE_ALL		0xf
/* also uses CSR_LTR_* क्रम values */
#घोषणा HPM_UMAC_LTR			0xa03480

/* FW monitor */
#घोषणा MON_BUFF_SAMPLE_CTL		(0xa03c00)
#घोषणा MON_BUFF_BASE_ADDR		(0xa03c1c)
#घोषणा MON_BUFF_END_ADDR		(0xa03c40)
#घोषणा MON_BUFF_WRPTR			(0xa03c44)
#घोषणा MON_BUFF_CYCLE_CNT		(0xa03c48)
/* FW monitor family 8000 and on */
#घोषणा MON_BUFF_BASE_ADDR_VER2		(0xa03c1c)
#घोषणा MON_BUFF_END_ADDR_VER2		(0xa03c20)
#घोषणा MON_BUFF_WRPTR_VER2		(0xa03c24)
#घोषणा MON_BUFF_CYCLE_CNT_VER2		(0xa03c28)
#घोषणा MON_BUFF_SHIFT_VER2		(0x8)
/* FW monitor familiy AX210 and on */
#घोषणा DBGC_CUR_DBGBUF_BASE_ADDR_LSB		(0xd03c20)
#घोषणा DBGC_CUR_DBGBUF_BASE_ADDR_MSB		(0xd03c24)
#घोषणा DBGC_CUR_DBGBUF_STATUS			(0xd03c1c)
#घोषणा DBGC_DBGBUF_WRAP_AROUND			(0xd03c2c)
#घोषणा DBGC_CUR_DBGBUF_STATUS_OFFSET_MSK	(0x00ffffff)
#घोषणा DBGC_CUR_DBGBUF_STATUS_IDX_MSK		(0x0f000000)

#घोषणा MON_DMARB_RD_CTL_ADDR		(0xa03c60)
#घोषणा MON_DMARB_RD_DATA_ADDR		(0xa03c5c)

#घोषणा DBGC_IN_SAMPLE			(0xa03c00)
#घोषणा DBGC_OUT_CTRL			(0xa03c0c)

/* M2S रेजिस्टरs */
#घोषणा LDBG_M2S_BUF_WPTR			(0xa0476c)
#घोषणा LDBG_M2S_BUF_WRAP_CNT			(0xa04774)
#घोषणा LDBG_M2S_BUF_WPTR_VAL_MSK		(0x000fffff)
#घोषणा LDBG_M2S_BUF_WRAP_CNT_VAL_MSK		(0x000fffff)

/* enable the ID buf क्रम पढ़ो */
#घोषणा WFPM_PS_CTL_CLR			0xA0300C
#घोषणा WFMP_MAC_ADDR_0			0xA03080
#घोषणा WFMP_MAC_ADDR_1			0xA03084
#घोषणा LMPM_PMG_EN			0xA01CEC
#घोषणा RADIO_REG_SYS_MANUAL_DFT_0	0xAD4078
#घोषणा RFIC_REG_RD			0xAD0470
#घोषणा WFPM_CTRL_REG			0xA03030
#घोषणा WFPM_GP2			0xA030B4
क्रमागत अणु
	ENABLE_WFPM = BIT(31),
	WFPM_AUX_CTL_AUX_IF_MAC_OWNER_MSK	= 0x80000000,
पूर्ण;

#घोषणा CNVI_AUX_MISC_CHIP				0xA200B0
#घोषणा CNVR_AUX_MISC_CHIP				0xA2B800
#घोषणा CNVR_SCU_SD_REGS_SD_REG_DIG_DCDC_VTRIM		0xA29890
#घोषणा CNVR_SCU_SD_REGS_SD_REG_ACTIVE_VDIG_MIRROR	0xA29938

#घोषणा PREG_AUX_BUS_WPROT_0		0xA04CC0

/* device family 9000 WPROT रेजिस्टर */
#घोषणा PREG_PRPH_WPROT_9000		0xA04CE0
/* device family 22000 WPROT रेजिस्टर */
#घोषणा PREG_PRPH_WPROT_22000		0xA04D00

#घोषणा SB_MODIFY_CFG_FLAG		0xA03088
#घोषणा SB_CPU_1_STATUS			0xA01E30
#घोषणा SB_CPU_2_STATUS			0xA01E34
#घोषणा UMAG_SB_CPU_1_STATUS		0xA038C0
#घोषणा UMAG_SB_CPU_2_STATUS		0xA038C4
#घोषणा UMAG_GEN_HW_STATUS		0xA038C8
#घोषणा UREG_UMAC_CURRENT_PC		0xa05c18
#घोषणा UREG_LMAC1_CURRENT_PC		0xa05c1c
#घोषणा UREG_LMAC2_CURRENT_PC		0xa05c20

/* For UMAG_GEN_HW_STATUS reg check */
क्रमागत अणु
	UMAG_GEN_HW_IS_FPGA = BIT(1),
पूर्ण;

/* FW chicken bits */
#घोषणा LMPM_CHICK			0xA01FF8
क्रमागत अणु
	LMPM_CHICK_EXTENDED_ADDR_SPACE = BIT(0),
पूर्ण;

/* FW chicken bits */
#घोषणा LMPM_PAGE_PASS_NOTIF			0xA03824
क्रमागत अणु
	LMPM_PAGE_PASS_NOTIF_POS = BIT(20),
पूर्ण;

#घोषणा UREG_CHICK		(0xA05C00)
#घोषणा UREG_CHICK_MSI_ENABLE	BIT(24)
#घोषणा UREG_CHICK_MSIX_ENABLE	BIT(25)

#घोषणा HPM_DEBUG			0xA03440
#घोषणा PERSISTENCE_BIT			BIT(12)
#घोषणा PREG_WFPM_ACCESS		BIT(12)

#घोषणा HPM_HIPM_GEN_CFG			0xA03458
#घोषणा HPM_HIPM_GEN_CFG_CR_PG_EN		BIT(0)
#घोषणा HPM_HIPM_GEN_CFG_CR_SLP_EN		BIT(1)
#घोषणा HPM_HIPM_GEN_CFG_CR_FORCE_ACTIVE	BIT(10)

#घोषणा UREG_DOORBELL_TO_ISR6		0xA05C04
#घोषणा UREG_DOORBELL_TO_ISR6_NMI_BIT	BIT(0)
#घोषणा UREG_DOORBELL_TO_ISR6_RESET_HANDSHAKE (BIT(0) | BIT(1))
#घोषणा UREG_DOORBELL_TO_ISR6_SUSPEND	BIT(18)
#घोषणा UREG_DOORBELL_TO_ISR6_RESUME	BIT(19)
#घोषणा UREG_DOORBELL_TO_ISR6_PNVM	BIT(20)

#घोषणा FSEQ_ERROR_CODE			0xA340C8
#घोषणा FSEQ_TOP_INIT_VERSION		0xA34038
#घोषणा FSEQ_CNVIO_INIT_VERSION		0xA3403C
#घोषणा FSEQ_OTP_VERSION		0xA340FC
#घोषणा FSEQ_TOP_CONTENT_VERSION	0xA340F4
#घोषणा FSEQ_ALIVE_TOKEN		0xA340F0
#घोषणा FSEQ_CNVI_ID			0xA3408C
#घोषणा FSEQ_CNVR_ID			0xA34090

#घोषणा IWL_D3_SLEEP_STATUS_SUSPEND	0xD3
#घोषणा IWL_D3_SLEEP_STATUS_RESUME	0xD0

#घोषणा WMAL_INDRCT_RD_CMD1_OPMOD_POS 28
#घोषणा WMAL_INDRCT_RD_CMD1_BYTE_ADDRESS_MSK 0xFFFFF
#घोषणा WMAL_CMD_READ_BURST_ACCESS 2
#घोषणा WMAL_MRSPF_1 0xADFC20
#घोषणा WMAL_INDRCT_RD_CMD1 0xADFD44
#घोषणा WMAL_INDRCT_CMD1 0xADFC14
#घोषणा WMAL_INDRCT_CMD(addr) \
	((WMAL_CMD_READ_BURST_ACCESS << WMAL_INDRCT_RD_CMD1_OPMOD_POS) | \
	 ((addr) & WMAL_INDRCT_RD_CMD1_BYTE_ADDRESS_MSK))

#घोषणा WFPM_LMAC1_PS_CTL_RW 0xA03380
#घोषणा WFPM_LMAC2_PS_CTL_RW 0xA033C0
#घोषणा WFPM_PS_CTL_RW_PHYRF_PD_FSM_CURSTATE_MSK 0x0000000F
#घोषणा WFPM_PHYRF_STATE_ON 5
#घोषणा HBUS_TIMEOUT 0xA5A5A5A1
#घोषणा WFPM_DPHY_OFF 0xDF10FF

#पूर्ण_अगर				/* __iwl_prph_h__ */
