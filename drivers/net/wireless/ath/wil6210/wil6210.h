<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (c) 2012-2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2018-2019, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित __WIL6210_H__
#घोषणा __WIL6210_H__

#समावेश <linux/etherdevice.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/wireless.h>
#समावेश <net/cfg80211.h>
#समावेश <linux/समयx.h>
#समावेश <linux/types.h>
#समावेश <linux/irqवापस.h>
#समावेश "wmi.h"
#समावेश "wil_platform.h"
#समावेश "fw.h"

बाह्य bool no_fw_recovery;
बाह्य अचिन्हित पूर्णांक mtu_max;
बाह्य अचिन्हित लघु rx_ring_overflow_thrsh;
बाह्य पूर्णांक agg_wsize;
बाह्य bool rx_align_2;
बाह्य bool rx_large_buf;
बाह्य bool debug_fw;
बाह्य bool disable_ap_sme;
बाह्य bool fपंचांग_mode;
बाह्य bool drop_अगर_ring_full;
बाह्य uपूर्णांक max_assoc_sta;

काष्ठा wil6210_priv;
काष्ठा wil6210_vअगर;
जोड़ wil_tx_desc;

#घोषणा WIL_NAME "wil6210"

#घोषणा WIL_FW_NAME_DEFAULT "wil6210.fw"
#घोषणा WIL_FW_NAME_FTM_DEFAULT "wil6210_ftm.fw"

#घोषणा WIL_FW_NAME_SPARROW_PLUS "wil6210_sparrow_plus.fw"
#घोषणा WIL_FW_NAME_FTM_SPARROW_PLUS "wil6210_sparrow_plus_ftm.fw"

#घोषणा WIL_FW_NAME_TALYN "wil6436.fw"
#घोषणा WIL_FW_NAME_FTM_TALYN "wil6436_ftm.fw"
#घोषणा WIL_BRD_NAME_TALYN "wil6436.brd"

#घोषणा WIL_BOARD_खाता_NAME "wil6210.brd" /* board & radio parameters */

#घोषणा WIL_DEFAULT_BUS_REQUEST_KBPS 128000 /* ~1Gbps */
#घोषणा WIL_MAX_BUS_REQUEST_KBPS 800000 /* ~6.1Gbps */

#घोषणा WIL_NUM_LATENCY_BINS 200

/* maximum number of भव पूर्णांकerfaces the driver supports
 * (including the मुख्य पूर्णांकerface)
 */
#घोषणा WIL_MAX_VIFS 4

/**
 * extract bits [@b0:@b1] (inclusive) from the value @x
 * it should be @b0 <= @b1, or result is incorrect
 */
अटल अंतरभूत u32 WIL_GET_BITS(u32 x, पूर्णांक b0, पूर्णांक b1)
अणु
	वापस (x >> b0) & ((1 << (b1 - b0 + 1)) - 1);
पूर्ण

#घोषणा WIL6210_MIN_MEM_SIZE (2 * 1024 * 1024UL)
#घोषणा WIL6210_MAX_MEM_SIZE (4 * 1024 * 1024UL)

#घोषणा WIL_TX_Q_LEN_DEFAULT		(4000)
#घोषणा WIL_RX_RING_SIZE_ORDER_DEFAULT	(10)
#घोषणा WIL_RX_RING_SIZE_ORDER_TALYN_DEFAULT	(11)
#घोषणा WIL_TX_RING_SIZE_ORDER_DEFAULT	(12)
#घोषणा WIL_BCAST_RING_SIZE_ORDER_DEFAULT	(7)
#घोषणा WIL_BCAST_MCS0_LIMIT		(1024) /* limit क्रम MCS0 frame size */
/* limit ring size in range [32..32k] */
#घोषणा WIL_RING_SIZE_ORDER_MIN	(5)
#घोषणा WIL_RING_SIZE_ORDER_MAX	(15)
#घोषणा WIL6210_MAX_TX_RINGS	(24) /* HW limit */
#घोषणा WIL6210_MAX_CID		(20) /* max number of stations */
#घोषणा WIL6210_RX_DESC_MAX_CID	(8)  /* HW limit */
#घोषणा WIL6210_NAPI_BUDGET	(16) /* arbitrary */
#घोषणा WIL_MAX_AMPDU_SIZE	(64 * 1024) /* FW/HW limit */
#घोषणा WIL_MAX_AGG_WSIZE	(32) /* FW/HW limit */
#घोषणा WIL_MAX_AMPDU_SIZE_128	(128 * 1024) /* FW/HW limit */
#घोषणा WIL_MAX_AGG_WSIZE_64	(64) /* FW/HW limit */
#घोषणा WIL6210_MAX_STATUS_RINGS	(8)
#घोषणा WIL_WMI_CALL_GENERAL_TO_MS 100
#घोषणा WIL_EXTENDED_MCS_26 (26) /* FW reports MCS 12.1 to driver as "26" */
#घोषणा WIL_BASE_MCS_FOR_EXTENDED_26 (7) /* MCS 7 is base MCS क्रम MCS 12.1 */
#घोषणा WIL_EXTENDED_MCS_CHECK(x) (((x) == WIL_EXTENDED_MCS_26) ? "12.1" : #x)

/* Hardware offload block adds the following:
 * 26 bytes - 3-address QoS data header
 *  8 bytes - IV + EIV (क्रम GCMP)
 *  8 bytes - SNAP
 * 16 bytes - MIC (क्रम GCMP)
 *  4 bytes - CRC
 */
#घोषणा WIL_MAX_MPDU_OVERHEAD	(62)

काष्ठा wil_suspend_count_stats अणु
	अचिन्हित दीर्घ successful_suspends;
	अचिन्हित दीर्घ successful_resumes;
	अचिन्हित दीर्घ failed_suspends;
	अचिन्हित दीर्घ failed_resumes;
पूर्ण;

काष्ठा wil_suspend_stats अणु
	काष्ठा wil_suspend_count_stats r_off;
	काष्ठा wil_suspend_count_stats r_on;
	अचिन्हित दीर्घ rejected_by_device; /* only radio on */
	अचिन्हित दीर्घ rejected_by_host;
पूर्ण;

/* Calculate MAC buffer size क्रम the firmware. It includes all overhead,
 * as it will go over the air, and need to be 8 byte aligned
 */
अटल अंतरभूत u32 wil_mtu2macbuf(u32 mtu)
अणु
	वापस ALIGN(mtu + WIL_MAX_MPDU_OVERHEAD, 8);
पूर्ण

/* MTU क्रम Ethernet need to take पूर्णांकo account 8-byte SNAP header
 * to be added when encapsulating Ethernet frame पूर्णांकo 802.11
 */
#घोषणा WIL_MAX_ETH_MTU		(IEEE80211_MAX_DATA_LEN_DMG - 8)
/* Max supported by wil6210 value क्रम पूर्णांकerrupt threshold is 5sec. */
#घोषणा WIL6210_ITR_TRSH_MAX (5000000)
#घोषणा WIL6210_ITR_TX_INTERFRAME_TIMEOUT_DEFAULT (13) /* usec */
#घोषणा WIL6210_ITR_RX_INTERFRAME_TIMEOUT_DEFAULT (13) /* usec */
#घोषणा WIL6210_ITR_TX_MAX_BURST_DURATION_DEFAULT (500) /* usec */
#घोषणा WIL6210_ITR_RX_MAX_BURST_DURATION_DEFAULT (500) /* usec */
#घोषणा WIL6210_FW_RECOVERY_RETRIES	(5) /* try to recover this many बार */
#घोषणा WIL6210_FW_RECOVERY_TO	msecs_to_jअगरfies(5000)
#घोषणा WIL6210_SCAN_TO		msecs_to_jअगरfies(10000)
#घोषणा WIL6210_DISCONNECT_TO_MS (2000)
#घोषणा WIL6210_RX_HIGH_TRSH_INIT		(0)
#घोषणा WIL6210_RX_HIGH_TRSH_DEFAULT \
				(1 << (WIL_RX_RING_SIZE_ORDER_DEFAULT - 3))
#घोषणा WIL_MAX_DMG_AID 254 /* क्रम DMG only 1-254 allowed (see
			     * 802.11REVmc/D5.0, section 9.4.1.8)
			     */
/* Hardware definitions begin */

/*
 * Mapping
 * RGF File      | Host addr    |  FW addr
 *               |              |
 * user_rgf      | 0x000000     | 0x880000
 *  dma_rgf      | 0x001000     | 0x881000
 * pcie_rgf      | 0x002000     | 0x882000
 *               |              |
 */

/* Where various काष्ठाures placed in host address space */
#घोषणा WIL6210_FW_HOST_OFF      (0x880000UL)

#घोषणा HOSTADDR(fwaddr)        (fwaddr - WIL6210_FW_HOST_OFF)

/*
 * Interrupt control रेजिस्टरs block
 *
 * each पूर्णांकerrupt controlled by the same bit in all रेजिस्टरs
 */
काष्ठा RGF_ICR अणु
	u32 ICC; /* Cause Control, RW: 0 - W1C, 1 - COR */
	u32 ICR; /* Cause, W1C/COR depending on ICC */
	u32 ICM; /* Cause masked (ICR & ~IMV), W1C/COR depending on ICC */
	u32 ICS; /* Cause Set, WO */
	u32 IMV; /* Mask, RW+S/C */
	u32 IMS; /* Mask Set, ग_लिखो 1 to set */
	u32 IMC; /* Mask Clear, ग_लिखो 1 to clear */
पूर्ण __packed;

/* रेजिस्टरs - FW addresses */
#घोषणा RGF_USER_USAGE_1		(0x880004)
#घोषणा RGF_USER_USAGE_2		(0x880008)
#घोषणा RGF_USER_USAGE_6		(0x880018)
	#घोषणा BIT_USER_OOB_MODE		BIT(31)
	#घोषणा BIT_USER_OOB_R2_MODE		BIT(30)
#घोषणा RGF_USER_USAGE_8		(0x880020)
	#घोषणा BIT_USER_PREVENT_DEEP_SLEEP	BIT(0)
	#घोषणा BIT_USER_SUPPORT_T_POWER_ON_0	BIT(1)
	#घोषणा BIT_USER_EXT_CLK		BIT(2)
#घोषणा RGF_USER_HW_MACHINE_STATE	(0x8801dc)
	#घोषणा HW_MACHINE_BOOT_DONE	(0x3fffffd)
#घोषणा RGF_USER_USER_CPU_0		(0x8801e0)
	#घोषणा BIT_USER_USER_CPU_MAN_RST	BIT(1) /* user_cpu_man_rst */
#घोषणा RGF_USER_CPU_PC			(0x8801e8)
#घोषणा RGF_USER_MAC_CPU_0		(0x8801fc)
	#घोषणा BIT_USER_MAC_CPU_MAN_RST	BIT(1) /* mac_cpu_man_rst */
#घोषणा RGF_USER_USER_SCRATCH_PAD	(0x8802bc)
#घोषणा RGF_USER_BL			(0x880A3C) /* Boot Loader */
#घोषणा RGF_USER_FW_REV_ID		(0x880a8c) /* chip revision */
#घोषणा RGF_USER_FW_CALIB_RESULT	(0x880a90) /* b0-7:result
						    * b8-15:signature
						    */
	#घोषणा CALIB_RESULT_SIGNATURE	(0x11)
#घोषणा RGF_USER_CLKS_CTL_0		(0x880abc)
	#घोषणा BIT_USER_CLKS_CAR_AHB_SW_SEL	BIT(1) /* ref clk/PLL */
	#घोषणा BIT_USER_CLKS_RST_PWGD	BIT(11) /* reset on "power good" */
#घोषणा RGF_USER_CLKS_CTL_SW_RST_VEC_0	(0x880b04)
#घोषणा RGF_USER_CLKS_CTL_SW_RST_VEC_1	(0x880b08)
#घोषणा RGF_USER_CLKS_CTL_SW_RST_VEC_2	(0x880b0c)
#घोषणा RGF_USER_CLKS_CTL_SW_RST_VEC_3	(0x880b10)
#घोषणा RGF_USER_CLKS_CTL_SW_RST_MASK_0	(0x880b14)
	#घोषणा BIT_HPAL_PERST_FROM_PAD	BIT(6)
	#घोषणा BIT_CAR_PERST_RST	BIT(7)
#घोषणा RGF_USER_USER_ICR		(0x880b4c) /* काष्ठा RGF_ICR */
	#घोषणा BIT_USER_USER_ICR_SW_INT_2	BIT(18)
#घोषणा RGF_USER_CLKS_CTL_EXT_SW_RST_VEC_0	(0x880c18)
#घोषणा RGF_USER_CLKS_CTL_EXT_SW_RST_VEC_1	(0x880c2c)
#घोषणा RGF_USER_SPARROW_M_4			(0x880c50) /* Sparrow */
	#घोषणा BIT_SPARROW_M_4_SEL_SLEEP_OR_REF	BIT(2)
#घोषणा RGF_USER_OTP_HW_RD_MACHINE_1	(0x880ce0)
	#घोषणा BIT_OTP_SIGNATURE_ERR_TALYN_MB		BIT(0)
	#घोषणा BIT_OTP_HW_SECTION_DONE_TALYN_MB	BIT(2)
	#घोषणा BIT_NO_FLASH_INDICATION			BIT(8)
#घोषणा RGF_USER_XPM_IFC_RD_TIME1	(0x880cec)
#घोषणा RGF_USER_XPM_IFC_RD_TIME2	(0x880cf0)
#घोषणा RGF_USER_XPM_IFC_RD_TIME3	(0x880cf4)
#घोषणा RGF_USER_XPM_IFC_RD_TIME4	(0x880cf8)
#घोषणा RGF_USER_XPM_IFC_RD_TIME5	(0x880cfc)
#घोषणा RGF_USER_XPM_IFC_RD_TIME6	(0x880d00)
#घोषणा RGF_USER_XPM_IFC_RD_TIME7	(0x880d04)
#घोषणा RGF_USER_XPM_IFC_RD_TIME8	(0x880d08)
#घोषणा RGF_USER_XPM_IFC_RD_TIME9	(0x880d0c)
#घोषणा RGF_USER_XPM_IFC_RD_TIME10	(0x880d10)
#घोषणा RGF_USER_XPM_RD_DOUT_SAMPLE_TIME (0x880d64)

#घोषणा RGF_DMA_EP_TX_ICR		(0x881bb4) /* काष्ठा RGF_ICR */
	#घोषणा BIT_DMA_EP_TX_ICR_TX_DONE	BIT(0)
	#घोषणा BIT_DMA_EP_TX_ICR_TX_DONE_N(n)	BIT(n+1) /* n = [0..23] */
#घोषणा RGF_DMA_EP_RX_ICR		(0x881bd0) /* काष्ठा RGF_ICR */
	#घोषणा BIT_DMA_EP_RX_ICR_RX_DONE	BIT(0)
	#घोषणा BIT_DMA_EP_RX_ICR_RX_HTRSH	BIT(1)
#घोषणा RGF_DMA_EP_MISC_ICR		(0x881bec) /* काष्ठा RGF_ICR */
	#घोषणा BIT_DMA_EP_MISC_ICR_RX_HTRSH	BIT(0)
	#घोषणा BIT_DMA_EP_MISC_ICR_TX_NO_ACT	BIT(1)
	#घोषणा BIT_DMA_EP_MISC_ICR_HALP	BIT(27)
	#घोषणा BIT_DMA_EP_MISC_ICR_FW_INT(n)	BIT(28+n) /* n = [0..3] */

/* Legacy पूर्णांकerrupt moderation control (beक्रमe Sparrow v2)*/
#घोषणा RGF_DMA_ITR_CNT_TRSH		(0x881c5c)
#घोषणा RGF_DMA_ITR_CNT_DATA		(0x881c60)
#घोषणा RGF_DMA_ITR_CNT_CRL		(0x881c64)
	#घोषणा BIT_DMA_ITR_CNT_CRL_EN		BIT(0)
	#घोषणा BIT_DMA_ITR_CNT_CRL_EXT_TICK	BIT(1)
	#घोषणा BIT_DMA_ITR_CNT_CRL_FOREVER	BIT(2)
	#घोषणा BIT_DMA_ITR_CNT_CRL_CLR		BIT(3)
	#घोषणा BIT_DMA_ITR_CNT_CRL_REACH_TRSH	BIT(4)

/* Offload control (Sparrow B0+) */
#घोषणा RGF_DMA_OFUL_NID_0		(0x881cd4)
	#घोषणा BIT_DMA_OFUL_NID_0_RX_EXT_TR_EN		BIT(0)
	#घोषणा BIT_DMA_OFUL_NID_0_TX_EXT_TR_EN		BIT(1)
	#घोषणा BIT_DMA_OFUL_NID_0_RX_EXT_A3_SRC	BIT(2)
	#घोषणा BIT_DMA_OFUL_NID_0_TX_EXT_A3_SRC	BIT(3)

/* New (sparrow v2+) पूर्णांकerrupt moderation control */
#घोषणा RGF_DMA_ITR_TX_DESQ_NO_MOD		(0x881d40)
#घोषणा RGF_DMA_ITR_TX_CNT_TRSH			(0x881d34)
#घोषणा RGF_DMA_ITR_TX_CNT_DATA			(0x881d38)
#घोषणा RGF_DMA_ITR_TX_CNT_CTL			(0x881d3c)
	#घोषणा BIT_DMA_ITR_TX_CNT_CTL_EN		BIT(0)
	#घोषणा BIT_DMA_ITR_TX_CNT_CTL_EXT_TIC_SEL	BIT(1)
	#घोषणा BIT_DMA_ITR_TX_CNT_CTL_FOREVER		BIT(2)
	#घोषणा BIT_DMA_ITR_TX_CNT_CTL_CLR		BIT(3)
	#घोषणा BIT_DMA_ITR_TX_CNT_CTL_REACHED_TRESH	BIT(4)
	#घोषणा BIT_DMA_ITR_TX_CNT_CTL_CROSS_EN		BIT(5)
	#घोषणा BIT_DMA_ITR_TX_CNT_CTL_FREE_RUNNIG	BIT(6)
#घोषणा RGF_DMA_ITR_TX_IDL_CNT_TRSH			(0x881d60)
#घोषणा RGF_DMA_ITR_TX_IDL_CNT_DATA			(0x881d64)
#घोषणा RGF_DMA_ITR_TX_IDL_CNT_CTL			(0x881d68)
	#घोषणा BIT_DMA_ITR_TX_IDL_CNT_CTL_EN			BIT(0)
	#घोषणा BIT_DMA_ITR_TX_IDL_CNT_CTL_EXT_TIC_SEL		BIT(1)
	#घोषणा BIT_DMA_ITR_TX_IDL_CNT_CTL_FOREVER		BIT(2)
	#घोषणा BIT_DMA_ITR_TX_IDL_CNT_CTL_CLR			BIT(3)
	#घोषणा BIT_DMA_ITR_TX_IDL_CNT_CTL_REACHED_TRESH	BIT(4)
#घोषणा RGF_DMA_ITR_RX_DESQ_NO_MOD		(0x881d50)
#घोषणा RGF_DMA_ITR_RX_CNT_TRSH			(0x881d44)
#घोषणा RGF_DMA_ITR_RX_CNT_DATA			(0x881d48)
#घोषणा RGF_DMA_ITR_RX_CNT_CTL			(0x881d4c)
	#घोषणा BIT_DMA_ITR_RX_CNT_CTL_EN		BIT(0)
	#घोषणा BIT_DMA_ITR_RX_CNT_CTL_EXT_TIC_SEL	BIT(1)
	#घोषणा BIT_DMA_ITR_RX_CNT_CTL_FOREVER		BIT(2)
	#घोषणा BIT_DMA_ITR_RX_CNT_CTL_CLR		BIT(3)
	#घोषणा BIT_DMA_ITR_RX_CNT_CTL_REACHED_TRESH	BIT(4)
	#घोषणा BIT_DMA_ITR_RX_CNT_CTL_CROSS_EN		BIT(5)
	#घोषणा BIT_DMA_ITR_RX_CNT_CTL_FREE_RUNNIG	BIT(6)
#घोषणा RGF_DMA_ITR_RX_IDL_CNT_TRSH			(0x881d54)
#घोषणा RGF_DMA_ITR_RX_IDL_CNT_DATA			(0x881d58)
#घोषणा RGF_DMA_ITR_RX_IDL_CNT_CTL			(0x881d5c)
	#घोषणा BIT_DMA_ITR_RX_IDL_CNT_CTL_EN			BIT(0)
	#घोषणा BIT_DMA_ITR_RX_IDL_CNT_CTL_EXT_TIC_SEL		BIT(1)
	#घोषणा BIT_DMA_ITR_RX_IDL_CNT_CTL_FOREVER		BIT(2)
	#घोषणा BIT_DMA_ITR_RX_IDL_CNT_CTL_CLR			BIT(3)
	#घोषणा BIT_DMA_ITR_RX_IDL_CNT_CTL_REACHED_TRESH	BIT(4)
#घोषणा RGF_DMA_MISC_CTL				(0x881d6c)
	#घोषणा BIT_OFUL34_RDY_VALID_BUG_FIX_EN			BIT(7)

#घोषणा RGF_DMA_PSEUDO_CAUSE		(0x881c68)
#घोषणा RGF_DMA_PSEUDO_CAUSE_MASK_SW	(0x881c6c)
#घोषणा RGF_DMA_PSEUDO_CAUSE_MASK_FW	(0x881c70)
	#घोषणा BIT_DMA_PSEUDO_CAUSE_RX		BIT(0)
	#घोषणा BIT_DMA_PSEUDO_CAUSE_TX		BIT(1)
	#घोषणा BIT_DMA_PSEUDO_CAUSE_MISC	BIT(2)

#घोषणा RGF_HP_CTRL			(0x88265c)
#घोषणा RGF_PAL_UNIT_ICR		(0x88266c) /* काष्ठा RGF_ICR */
#घोषणा RGF_PCIE_LOS_COUNTER_CTL	(0x882dc4)

/* MAC समयr, usec, क्रम packet lअगरeसमय */
#घोषणा RGF_MAC_MTRL_COUNTER_0		(0x886aa8)

#घोषणा RGF_CAF_ICR_TALYN_MB		(0x8893d4) /* काष्ठा RGF_ICR */
#घोषणा RGF_CAF_ICR			(0x88946c) /* काष्ठा RGF_ICR */
#घोषणा RGF_CAF_OSC_CONTROL		(0x88afa4)
	#घोषणा BIT_CAF_OSC_XTAL_EN		BIT(0)
#घोषणा RGF_CAF_PLL_LOCK_STATUS		(0x88afec)
	#घोषणा BIT_CAF_OSC_DIG_XTAL_STABLE	BIT(0)

#घोषणा RGF_OTP_QC_SECURED		(0x8a0038)
	#घोषणा BIT_BOOT_FROM_ROM		BIT(31)

/* eDMA */
#घोषणा RGF_SCM_PTRS_SUBQ_RD_PTR	(0x8b4000)
#घोषणा RGF_SCM_PTRS_COMPQ_RD_PTR	(0x8b4100)
#घोषणा RGF_DMA_SCM_SUBQ_CONS		(0x8b60ec)
#घोषणा RGF_DMA_SCM_COMPQ_PROD		(0x8b616c)

#घोषणा RGF_INT_COUNT_ON_SPECIAL_EVT	(0x8b62d8)

#घोषणा RGF_INT_CTRL_INT_GEN_CFG_0	(0x8bc000)
#घोषणा RGF_INT_CTRL_INT_GEN_CFG_1	(0x8bc004)
#घोषणा RGF_INT_GEN_TIME_UNIT_LIMIT	(0x8bc0c8)

#घोषणा RGF_INT_GEN_CTRL		(0x8bc0ec)
	#घोषणा BIT_CONTROL_0			BIT(0)

/* eDMA status पूर्णांकerrupts */
#घोषणा RGF_INT_GEN_RX_ICR		(0x8bc0f4)
	#घोषणा BIT_RX_STATUS_IRQ BIT(WIL_RX_STATUS_IRQ_IDX)
#घोषणा RGF_INT_GEN_TX_ICR		(0x8bc110)
	#घोषणा BIT_TX_STATUS_IRQ BIT(WIL_TX_STATUS_IRQ_IDX)
#घोषणा RGF_INT_CTRL_RX_INT_MASK	(0x8bc12c)
#घोषणा RGF_INT_CTRL_TX_INT_MASK	(0x8bc130)

#घोषणा RGF_INT_GEN_IDLE_TIME_LIMIT	(0x8bc134)

#घोषणा USER_EXT_USER_PMU_3		(0x88d00c)
	#घोषणा BIT_PMU_DEVICE_RDY		BIT(0)

#घोषणा RGF_USER_JTAG_DEV_ID	(0x880b34) /* device ID */
	#घोषणा JTAG_DEV_ID_SPARROW	(0x2632072f)
	#घोषणा JTAG_DEV_ID_TALYN	(0x7e0e1)
	#घोषणा JTAG_DEV_ID_TALYN_MB	(0x1007e0e1)

#घोषणा RGF_USER_REVISION_ID		(0x88afe4)
#घोषणा RGF_USER_REVISION_ID_MASK	(3)
	#घोषणा REVISION_ID_SPARROW_B0	(0x0)
	#घोषणा REVISION_ID_SPARROW_D0	(0x3)

#घोषणा RGF_OTP_MAC_TALYN_MB		(0x8a0304)
#घोषणा RGF_OTP_OEM_MAC			(0x8a0334)
#घोषणा RGF_OTP_MAC			(0x8a0620)

/* Talyn-MB */
#घोषणा RGF_USER_USER_CPU_0_TALYN_MB	(0x8c0138)
#घोषणा RGF_USER_MAC_CPU_0_TALYN_MB	(0x8c0154)

/* crash codes क्रम FW/Ucode stored here */

/* ASSERT RGFs */
#घोषणा SPARROW_RGF_FW_ASSERT_CODE	(0x91f020)
#घोषणा SPARROW_RGF_UCODE_ASSERT_CODE	(0x91f028)
#घोषणा TALYN_RGF_FW_ASSERT_CODE	(0xa37020)
#घोषणा TALYN_RGF_UCODE_ASSERT_CODE	(0xa37028)

क्रमागत अणु
	HW_VER_UNKNOWN,
	HW_VER_SPARROW_B0, /* REVISION_ID_SPARROW_B0 */
	HW_VER_SPARROW_D0, /* REVISION_ID_SPARROW_D0 */
	HW_VER_TALYN,	/* JTAG_DEV_ID_TALYN */
	HW_VER_TALYN_MB	/* JTAG_DEV_ID_TALYN_MB */
पूर्ण;

/* popular locations */
#घोषणा RGF_MBOX   RGF_USER_USER_SCRATCH_PAD
#घोषणा HOST_MBOX   HOSTADDR(RGF_MBOX)
#घोषणा SW_INT_MBOX BIT_USER_USER_ICR_SW_INT_2

/* ISR रेजिस्टर bits */
#घोषणा ISR_MISC_FW_READY	BIT_DMA_EP_MISC_ICR_FW_INT(0)
#घोषणा ISR_MISC_MBOX_EVT	BIT_DMA_EP_MISC_ICR_FW_INT(1)
#घोषणा ISR_MISC_FW_ERROR	BIT_DMA_EP_MISC_ICR_FW_INT(3)

#घोषणा WIL_DATA_COMPLETION_TO_MS 200

/* Hardware definitions end */
#घोषणा SPARROW_FW_MAPPING_TABLE_SIZE 10
#घोषणा TALYN_FW_MAPPING_TABLE_SIZE 13
#घोषणा TALYN_MB_FW_MAPPING_TABLE_SIZE 19
#घोषणा MAX_FW_MAPPING_TABLE_SIZE 19

/* Common representation of physical address in wil ring */
काष्ठा wil_ring_dma_addr अणु
	__le32 addr_low;
	__le16 addr_high;
पूर्ण __packed;

काष्ठा fw_map अणु
	u32 from; /* linker address - from, inclusive */
	u32 to;   /* linker address - to, exclusive */
	u32 host; /* PCI/Host address - BAR0 + 0x880000 */
	स्थिर अक्षर *name; /* क्रम debugfs */
	bool fw; /* true अगर FW mapping, false अगर UCODE mapping */
	bool crash_dump; /* true अगर should be dumped during crash dump */
पूर्ण;

/* array size should be in sync with actual definition in the wmi.c */
बाह्य स्थिर काष्ठा fw_map sparrow_fw_mapping[SPARROW_FW_MAPPING_TABLE_SIZE];
बाह्य स्थिर काष्ठा fw_map sparrow_d0_mac_rgf_ext;
बाह्य स्थिर काष्ठा fw_map talyn_fw_mapping[TALYN_FW_MAPPING_TABLE_SIZE];
बाह्य स्थिर काष्ठा fw_map talyn_mb_fw_mapping[TALYN_MB_FW_MAPPING_TABLE_SIZE];
बाह्य काष्ठा fw_map fw_mapping[MAX_FW_MAPPING_TABLE_SIZE];

/**
 * mk_cidxtid - स्थिरruct @cidxtid field
 * @cid: CID value
 * @tid: TID value
 *
 * @cidxtid field encoded as bits 0..3 - CID; 4..7 - TID
 */
अटल अंतरभूत u8 mk_cidxtid(u8 cid, u8 tid)
अणु
	वापस ((tid & 0xf) << 4) | (cid & 0xf);
पूर्ण

/**
 * parse_cidxtid - parse @cidxtid field
 * @cid: store CID value here
 * @tid: store TID value here
 *
 * @cidxtid field encoded as bits 0..3 - CID; 4..7 - TID
 */
अटल अंतरभूत व्योम parse_cidxtid(u8 cidxtid, u8 *cid, u8 *tid)
अणु
	*cid = cidxtid & 0xf;
	*tid = (cidxtid >> 4) & 0xf;
पूर्ण

काष्ठा wil6210_mbox_ring अणु
	u32 base;
	u16 entry_size; /* max. size of mbox entry, incl. all headers */
	u16 size;
	u32 tail;
	u32 head;
पूर्ण __packed;

काष्ठा wil6210_mbox_ring_desc अणु
	__le32 sync;
	__le32 addr;
पूर्ण __packed;

/* at HOST_OFF_WIL6210_MBOX_CTL */
काष्ठा wil6210_mbox_ctl अणु
	काष्ठा wil6210_mbox_ring tx;
	काष्ठा wil6210_mbox_ring rx;
पूर्ण __packed;

काष्ठा wil6210_mbox_hdr अणु
	__le16 seq;
	__le16 len; /* payload, bytes after this header */
	__le16 type;
	u8 flags;
	u8 reserved;
पूर्ण __packed;

#घोषणा WIL_MBOX_HDR_TYPE_WMI (0)

/* max. value क्रम wil6210_mbox_hdr.len */
#घोषणा MAX_MBOXITEM_SIZE   (240)

काष्ठा pending_wmi_event अणु
	काष्ठा list_head list;
	काष्ठा अणु
		काष्ठा wil6210_mbox_hdr hdr;
		काष्ठा wmi_cmd_hdr wmi;
		u8 data[0];
	पूर्ण __packed event;
पूर्ण;

क्रमागत अणु /* क्रम wil_ctx.mapped_as */
	wil_mapped_as_none = 0,
	wil_mapped_as_single = 1,
	wil_mapped_as_page = 2,
पूर्ण;

/**
 * काष्ठा wil_ctx - software context क्रम ring descriptor
 */
काष्ठा wil_ctx अणु
	काष्ठा sk_buff *skb;
	u8 nr_frags;
	u8 mapped_as;
पूर्ण;

काष्ठा wil_desc_ring_rx_swtail अणु /* relevant क्रम enhanced DMA only */
	u32 *va;
	dma_addr_t pa;
पूर्ण;

/**
 * A general ring काष्ठाure, used क्रम RX and TX.
 * In legacy DMA it represents the vring,
 * In enahnced DMA it represents the descriptor ring (vrings are handled by FW)
 */
काष्ठा wil_ring अणु
	dma_addr_t pa;
	अस्थिर जोड़ wil_ring_desc *va;
	u16 size; /* number of wil_ring_desc elements */
	u32 swtail;
	u32 swhead;
	u32 hwtail; /* ग_लिखो here to inक्रमm hw */
	काष्ठा wil_ctx *ctx; /* ctx[size] - software context */
	काष्ठा wil_desc_ring_rx_swtail edma_rx_swtail;
	bool is_rx;
पूर्ण;

/**
 * Additional data क्रम Rx ring.
 * Used क्रम enhanced DMA RX chaining.
 */
काष्ठा wil_ring_rx_data अणु
	/* the skb being assembled */
	काष्ठा sk_buff *skb;
	/* true अगर we are skipping a bad fragmented packet */
	bool skipping;
	u16 buff_size;
पूर्ण;

/**
 * Status ring काष्ठाure, used क्रम enhanced DMA completions क्रम RX and TX.
 */
काष्ठा wil_status_ring अणु
	dma_addr_t pa;
	व्योम *va; /* poपूर्णांकer to ring_[tr]x_status elements */
	u16 size; /* number of status elements */
	माप_प्रकार elem_size; /* status element size in bytes */
	u32 swhead;
	u32 hwtail; /* ग_लिखो here to inक्रमm hw */
	bool is_rx;
	u8 desc_rdy_pol; /* Expected descriptor पढ़ोy bit polarity */
	काष्ठा wil_ring_rx_data rx_data;
	u32 invalid_buff_id_cnt; /* relevant only क्रम RX */
पूर्ण;

#घोषणा WIL_STA_TID_NUM (16)
#घोषणा WIL_MCS_MAX (15) /* Maximum MCS supported */

काष्ठा wil_net_stats अणु
	अचिन्हित दीर्घ	rx_packets;
	अचिन्हित दीर्घ	tx_packets;
	अचिन्हित दीर्घ	rx_bytes;
	अचिन्हित दीर्घ	tx_bytes;
	अचिन्हित दीर्घ	tx_errors;
	u32 tx_latency_min_us;
	u32 tx_latency_max_us;
	u64 tx_latency_total_us;
	अचिन्हित दीर्घ	rx_dropped;
	अचिन्हित दीर्घ	rx_non_data_frame;
	अचिन्हित दीर्घ	rx_लघु_frame;
	अचिन्हित दीर्घ	rx_large_frame;
	अचिन्हित दीर्घ	rx_replay;
	अचिन्हित दीर्घ	rx_mic_error;
	अचिन्हित दीर्घ	rx_key_error; /* eDMA specअगरic */
	अचिन्हित दीर्घ	rx_amsdu_error; /* eDMA specअगरic */
	अचिन्हित दीर्घ	rx_csum_err;
	u16 last_mcs_rx;
	u8 last_cb_mode_rx;
	u64 rx_per_mcs[WIL_MCS_MAX + 1];
	u32 ft_roams; /* relevant in STA mode */
पूर्ण;

/**
 * काष्ठा tx_rx_ops - dअगरferent TX/RX ops क्रम legacy and enhanced
 * DMA flow
 */
काष्ठा wil_txrx_ops अणु
	व्योम (*configure_पूर्णांकerrupt_moderation)(काष्ठा wil6210_priv *wil);
	/* TX ops */
	पूर्णांक (*ring_init_tx)(काष्ठा wil6210_vअगर *vअगर, पूर्णांक ring_id,
			    पूर्णांक size, पूर्णांक cid, पूर्णांक tid);
	व्योम (*ring_fini_tx)(काष्ठा wil6210_priv *wil, काष्ठा wil_ring *ring);
	पूर्णांक (*ring_init_bcast)(काष्ठा wil6210_vअगर *vअगर, पूर्णांक id, पूर्णांक size);
	पूर्णांक (*tx_init)(काष्ठा wil6210_priv *wil);
	व्योम (*tx_fini)(काष्ठा wil6210_priv *wil);
	पूर्णांक (*tx_desc_map)(जोड़ wil_tx_desc *desc, dma_addr_t pa,
			   u32 len, पूर्णांक ring_index);
	व्योम (*tx_desc_unmap)(काष्ठा device *dev,
			      जोड़ wil_tx_desc *desc,
			      काष्ठा wil_ctx *ctx);
	पूर्णांक (*tx_ring_tso)(काष्ठा wil6210_priv *wil, काष्ठा wil6210_vअगर *vअगर,
			   काष्ठा wil_ring *ring, काष्ठा sk_buff *skb);
	पूर्णांक (*tx_ring_modअगरy)(काष्ठा wil6210_vअगर *vअगर, पूर्णांक ring_id,
			      पूर्णांक cid, पूर्णांक tid);
	irqवापस_t (*irq_tx)(पूर्णांक irq, व्योम *cookie);
	/* RX ops */
	पूर्णांक (*rx_init)(काष्ठा wil6210_priv *wil, uपूर्णांक ring_order);
	व्योम (*rx_fini)(काष्ठा wil6210_priv *wil);
	पूर्णांक (*wmi_addba_rx_resp)(काष्ठा wil6210_priv *wil, u8 mid, u8 cid,
				 u8 tid, u8 token, u16 status, bool amsdu,
				 u16 agg_wsize, u16 समयout);
	व्योम (*get_reorder_params)(काष्ठा wil6210_priv *wil,
				   काष्ठा sk_buff *skb, पूर्णांक *tid, पूर्णांक *cid,
				   पूर्णांक *mid, u16 *seq, पूर्णांक *mcast, पूर्णांक *retry);
	व्योम (*get_netअगर_rx_params)(काष्ठा sk_buff *skb,
				    पूर्णांक *cid, पूर्णांक *security);
	पूर्णांक (*rx_crypto_check)(काष्ठा wil6210_priv *wil, काष्ठा sk_buff *skb);
	पूर्णांक (*rx_error_check)(काष्ठा wil6210_priv *wil, काष्ठा sk_buff *skb,
			      काष्ठा wil_net_stats *stats);
	bool (*is_rx_idle)(काष्ठा wil6210_priv *wil);
	irqवापस_t (*irq_rx)(पूर्णांक irq, व्योम *cookie);
पूर्ण;

/**
 * Additional data क्रम Tx ring
 */
काष्ठा wil_ring_tx_data अणु
	bool करोt1x_खोलो;
	पूर्णांक enabled;
	cycles_t idle, last_idle, begin;
	u8 agg_wsize; /* agreed aggregation winकरोw, 0 - no agg */
	u16 agg_समयout;
	u8 agg_amsdu;
	bool addba_in_progress; /* अगर set, agg_xxx is क्रम request in progress */
	u8 mid;
	spinlock_t lock;
पूर्ण;

क्रमागत अणु /* क्रम wil6210_priv.status */
	wil_status_fwपढ़ोy = 0, /* FW operational */
	wil_status_करोntscan,
	wil_status_mbox_पढ़ोy, /* MBOX काष्ठाures पढ़ोy */
	wil_status_irqen, /* पूर्णांकerrupts enabled - क्रम debug */
	wil_status_napi_en, /* NAPI enabled रक्षित by wil->mutex */
	wil_status_resetting, /* reset in progress */
	wil_status_suspending, /* suspend in progress */
	wil_status_suspended, /* suspend completed, device is suspended */
	wil_status_resuming, /* resume in progress */
	wil_status_last /* keep last */
पूर्ण;

काष्ठा pci_dev;

/**
 * काष्ठा tid_ampdu_rx - TID aggregation inक्रमmation (Rx).
 *
 * @reorder_buf: buffer to reorder incoming aggregated MPDUs
 * @last_rx: jअगरfies of last rx activity
 * @head_seq_num: head sequence number in reordering buffer.
 * @stored_mpdu_num: number of MPDUs in reordering buffer
 * @ssn: Starting Sequence Number expected to be aggregated.
 * @buf_size: buffer size क्रम incoming A-MPDUs
 * @ssn_last_drop: SSN of the last dropped frame
 * @total: total number of processed incoming frames
 * @drop_dup: duplicate frames dropped क्रम this reorder buffer
 * @drop_old: old frames dropped क्रम this reorder buffer
 * @first_समय: true when this buffer used 1-st समय
 * @mcast_last_seq: sequence number (SN) of last received multicast packet
 * @drop_dup_mcast: duplicate multicast frames dropped क्रम this reorder buffer
 */
काष्ठा wil_tid_ampdu_rx अणु
	काष्ठा sk_buff **reorder_buf;
	अचिन्हित दीर्घ last_rx;
	u16 head_seq_num;
	u16 stored_mpdu_num;
	u16 ssn;
	u16 buf_size;
	u16 ssn_last_drop;
	अचिन्हित दीर्घ दीर्घ total; /* frames processed */
	अचिन्हित दीर्घ दीर्घ drop_dup;
	अचिन्हित दीर्घ दीर्घ drop_old;
	bool first_समय; /* is it 1-st समय this buffer used? */
	u16 mcast_last_seq; /* multicast dup detection */
	अचिन्हित दीर्घ दीर्घ drop_dup_mcast;
पूर्ण;

/**
 * काष्ठा wil_tid_crypto_rx_single - TID crypto inक्रमmation (Rx).
 *
 * @pn: GCMP PN क्रम the session
 * @key_set: valid key present
 */
काष्ठा wil_tid_crypto_rx_single अणु
	u8 pn[IEEE80211_GCMP_PN_LEN];
	bool key_set;
पूर्ण;

काष्ठा wil_tid_crypto_rx अणु
	काष्ठा wil_tid_crypto_rx_single key_id[4];
पूर्ण;

काष्ठा wil_p2p_info अणु
	काष्ठा ieee80211_channel listen_chan;
	u8 discovery_started;
	u64 cookie;
	काष्ठा wireless_dev *pending_listen_wdev;
	अचिन्हित पूर्णांक listen_duration;
	काष्ठा समयr_list discovery_समयr; /* listen/search duration */
	काष्ठा work_काष्ठा discovery_expired_work; /* listen/search expire */
	काष्ठा work_काष्ठा delayed_listen_work; /* listen after scan करोne */
पूर्ण;

क्रमागत wil_sta_status अणु
	wil_sta_unused = 0,
	wil_sta_conn_pending = 1,
	wil_sta_connected = 2,
पूर्ण;

क्रमागत wil_rekey_state अणु
	WIL_REKEY_IDLE = 0,
	WIL_REKEY_M3_RECEIVED = 1,
	WIL_REKEY_WAIT_M4_SENT = 2,
पूर्ण;

/**
 * काष्ठा wil_sta_info - data क्रम peer
 *
 * Peer identअगरied by its CID (connection ID)
 * NIC perक्रमms beam क्रमming क्रम each peer;
 * अगर no beam क्रमming करोne, frame exchange is not
 * possible.
 */
काष्ठा wil_sta_info अणु
	u8 addr[ETH_ALEN];
	u8 mid;
	क्रमागत wil_sta_status status;
	काष्ठा wil_net_stats stats;
	/**
	 * 20 latency bins. 1st bin counts packets with latency
	 * of 0..tx_latency_res, last bin counts packets with latency
	 * of 19*tx_latency_res and above.
	 * tx_latency_res is configured from "tx_latency" debug-fs.
	 */
	u64 *tx_latency_bins;
	काष्ठा wmi_link_stats_basic fw_stats_basic;
	/* Rx BACK */
	काष्ठा wil_tid_ampdu_rx *tid_rx[WIL_STA_TID_NUM];
	spinlock_t tid_rx_lock; /* guarding tid_rx array */
	अचिन्हित दीर्घ tid_rx_समयr_expired[BITS_TO_LONGS(WIL_STA_TID_NUM)];
	अचिन्हित दीर्घ tid_rx_stop_requested[BITS_TO_LONGS(WIL_STA_TID_NUM)];
	काष्ठा wil_tid_crypto_rx tid_crypto_rx[WIL_STA_TID_NUM];
	काष्ठा wil_tid_crypto_rx group_crypto_rx;
	u8 aid; /* 1-254; 0 अगर unknown/not reported */
पूर्ण;

क्रमागत अणु
	fw_recovery_idle = 0,
	fw_recovery_pending = 1,
	fw_recovery_running = 2,
पूर्ण;

क्रमागत अणु
	hw_capa_no_flash,
	hw_capa_last
पूर्ण;

काष्ठा wil_probe_client_req अणु
	काष्ठा list_head list;
	u64 cookie;
	u8 cid;
पूर्ण;

काष्ठा pmc_ctx अणु
	/* alloc, मुक्त, and पढ़ो operations must own the lock */
	काष्ठा mutex		lock;
	काष्ठा vring_tx_desc	*pring_va;
	dma_addr_t		pring_pa;
	काष्ठा desc_alloc_info  *descriptors;
	पूर्णांक			last_cmd_status;
	पूर्णांक			num_descriptors;
	पूर्णांक			descriptor_size;
पूर्ण;

काष्ठा wil_halp अणु
	काष्ठा mutex		lock; /* protect halp ref_cnt */
	अचिन्हित पूर्णांक		ref_cnt;
	काष्ठा completion	comp;
	u8			handle_icr;
पूर्ण;

काष्ठा wil_blob_wrapper अणु
	काष्ठा wil6210_priv *wil;
	काष्ठा debugfs_blob_wrapper blob;
पूर्ण;

#घोषणा WIL_LED_MAX_ID			(2)
#घोषणा WIL_LED_INVALID_ID		(0xF)
#घोषणा WIL_LED_BLINK_ON_SLOW_MS	(300)
#घोषणा WIL_LED_BLINK_OFF_SLOW_MS	(300)
#घोषणा WIL_LED_BLINK_ON_MED_MS		(200)
#घोषणा WIL_LED_BLINK_OFF_MED_MS	(200)
#घोषणा WIL_LED_BLINK_ON_FAST_MS	(100)
#घोषणा WIL_LED_BLINK_OFF_FAST_MS	(100)
क्रमागत अणु
	WIL_LED_TIME_SLOW = 0,
	WIL_LED_TIME_MED,
	WIL_LED_TIME_FAST,
	WIL_LED_TIME_LAST,
पूर्ण;

काष्ठा blink_on_off_समय अणु
	u32 on_ms;
	u32 off_ms;
पूर्ण;

काष्ठा wil_debugfs_iomem_data अणु
	व्योम *offset;
	काष्ठा wil6210_priv *wil;
पूर्ण;

काष्ठा wil_debugfs_data अणु
	काष्ठा wil_debugfs_iomem_data *data_arr;
	पूर्णांक iomem_data_count;
पूर्ण;

बाह्य काष्ठा blink_on_off_समय led_blink_समय[WIL_LED_TIME_LAST];
बाह्य u8 led_id;
बाह्य u8 led_polarity;

क्रमागत wil6210_vअगर_status अणु
	wil_vअगर_fwconnecting,
	wil_vअगर_fwconnected,
	wil_vअगर_ft_roam,
	wil_vअगर_status_last /* keep last */
पूर्ण;

काष्ठा wil6210_vअगर अणु
	काष्ठा wireless_dev wdev;
	काष्ठा net_device *ndev;
	काष्ठा wil6210_priv *wil;
	u8 mid;
	DECLARE_BITMAP(status, wil_vअगर_status_last);
	u32 privacy; /* secure connection? */
	u16 channel; /* relevant in AP mode */
	u8 wmi_edmg_channel; /* relevant in AP mode */
	u8 hidden_ssid; /* relevant in AP mode */
	u32 ap_isolate; /* no पूर्णांकra-BSS communication */
	bool pbss;
	पूर्णांक bi;
	u8 *proberesp, *proberesp_ies, *assocresp_ies;
	माप_प्रकार proberesp_len, proberesp_ies_len, assocresp_ies_len;
	u8 ssid[IEEE80211_MAX_SSID_LEN];
	माप_प्रकार ssid_len;
	u8 gtk_index;
	u8 gtk[WMI_MAX_KEY_LEN];
	माप_प्रकार gtk_len;
	पूर्णांक bcast_ring;
	काष्ठा cfg80211_bss *bss; /* connected bss, relevant in STA mode */
	पूर्णांक locally_generated_disc; /* relevant in STA mode */
	काष्ठा समयr_list connect_समयr;
	काष्ठा work_काष्ठा disconnect_worker;
	/* scan */
	काष्ठा cfg80211_scan_request *scan_request;
	काष्ठा समयr_list scan_समयr; /* detect scan समयout */
	काष्ठा wil_p2p_info p2p;
	/* keep alive */
	काष्ठा list_head probe_client_pending;
	काष्ठा mutex probe_client_mutex; /* protect @probe_client_pending */
	काष्ठा work_काष्ठा probe_client_worker;
	पूर्णांक net_queue_stopped; /* netअगर_tx_stop_all_queues invoked */
	bool fw_stats_पढ़ोy; /* per-cid statistics are पढ़ोy inside sta_info */
	u64 fw_stats_tsf; /* measurement बारtamp */

	/* PTK rekey race prevention, this is relevant to station mode only */
	क्रमागत wil_rekey_state ptk_rekey_state;
	काष्ठा work_काष्ठा enable_tx_key_worker;
पूर्ण;

/**
 * RX buffer allocated क्रम enhanced DMA RX descriptors
 */
काष्ठा wil_rx_buff अणु
	काष्ठा sk_buff *skb;
	काष्ठा list_head list;
	पूर्णांक id;
पूर्ण;

/**
 * During Rx completion processing, the driver extracts a buffer ID which
 * is used as an index to the rx_buff_mgmt.buff_arr array and then the SKB
 * is given to the network stack and the buffer is moved from the 'active'
 * list to the 'free' list.
 * During Rx refill, SKBs are attached to मुक्त buffers and moved to the
 * 'active' list.
 */
काष्ठा wil_rx_buff_mgmt अणु
	काष्ठा wil_rx_buff *buff_arr;
	माप_प्रकार size; /* number of items in buff_arr */
	काष्ठा list_head active;
	काष्ठा list_head मुक्त;
	अचिन्हित दीर्घ मुक्त_list_empty_cnt; /* statistics */
पूर्ण;

काष्ठा wil_fw_stats_global अणु
	bool पढ़ोy;
	u64 tsf; /* measurement बारtamp */
	काष्ठा wmi_link_stats_global stats;
पूर्ण;

काष्ठा wil_brd_info अणु
	u32 file_addr;
	u32 file_max_size;
पूर्ण;

काष्ठा wil6210_priv अणु
	काष्ठा pci_dev *pdev;
	u32 bar_size;
	काष्ठा wiphy *wiphy;
	काष्ठा net_device *मुख्य_ndev;
	पूर्णांक n_msi;
	व्योम __iomem *csr;
	DECLARE_BITMAP(status, wil_status_last);
	u8 fw_version[ETHTOOL_FWVERS_LEN];
	u32 hw_version;
	u8 chip_revision;
	स्थिर अक्षर *hw_name;
	स्थिर अक्षर *wil_fw_name;
	अक्षर *board_file;
	u32 num_of_brd_entries;
	काष्ठा wil_brd_info *brd_info;
	DECLARE_BITMAP(hw_capa, hw_capa_last);
	DECLARE_BITMAP(fw_capabilities, WMI_FW_CAPABILITY_MAX);
	DECLARE_BITMAP(platक्रमm_capa, WIL_PLATFORM_CAPA_MAX);
	u32 recovery_count; /* num of FW recovery attempts in a लघु समय */
	u32 recovery_state; /* FW recovery state machine */
	अचिन्हित दीर्घ last_fw_recovery; /* jअगरfies of last fw recovery */
	रुको_queue_head_t wq; /* क्रम all रुको_event() use */
	u8 max_vअगरs; /* maximum number of पूर्णांकerfaces, including मुख्य */
	काष्ठा wil6210_vअगर *vअगरs[WIL_MAX_VIFS];
	काष्ठा mutex vअगर_mutex; /* protects access to VIF entries */
	atomic_t connected_vअगरs;
	u32 max_assoc_sta; /* max sta's supported by the driver and the FW */

	/* profile */
	काष्ठा cfg80211_chan_def monitor_chandef;
	u32 monitor_flags;
	पूर्णांक sinfo_gen;
	/* पूर्णांकerrupt moderation */
	u32 tx_max_burst_duration;
	u32 tx_पूर्णांकerframe_समयout;
	u32 rx_max_burst_duration;
	u32 rx_पूर्णांकerframe_समयout;
	/* cached ISR रेजिस्टरs */
	u32 isr_misc;
	/* mailbox related */
	काष्ठा mutex wmi_mutex;
	काष्ठा wil6210_mbox_ctl mbox_ctl;
	काष्ठा completion wmi_पढ़ोy;
	काष्ठा completion wmi_call;
	u16 wmi_seq;
	u16 reply_id; /**< रुको क्रम this WMI event */
	u8 reply_mid;
	व्योम *reply_buf;
	u16 reply_size;
	काष्ठा workqueue_काष्ठा *wmi_wq; /* क्रम deferred calls */
	काष्ठा work_काष्ठा wmi_event_worker;
	काष्ठा workqueue_काष्ठा *wq_service;
	काष्ठा work_काष्ठा fw_error_worker;	/* क्रम FW error recovery */
	काष्ठा list_head pending_wmi_ev;
	/*
	 * protect pending_wmi_ev
	 * - fill in IRQ from wil6210_irq_misc,
	 * - consumed in thपढ़ो by wmi_event_worker
	 */
	spinlock_t wmi_ev_lock;
	spinlock_t net_queue_lock; /* guarding stop/wake netअगर queue */
	spinlock_t eap_lock; /* guarding access to eap rekey fields */
	काष्ठा napi_काष्ठा napi_rx;
	काष्ठा napi_काष्ठा napi_tx;
	काष्ठा net_device napi_ndev; /* dummy net_device serving all VIFs */

	/* DMA related */
	काष्ठा wil_ring ring_rx;
	अचिन्हित पूर्णांक rx_buf_len;
	काष्ठा wil_ring ring_tx[WIL6210_MAX_TX_RINGS];
	काष्ठा wil_ring_tx_data ring_tx_data[WIL6210_MAX_TX_RINGS];
	काष्ठा wil_status_ring srings[WIL6210_MAX_STATUS_RINGS];
	u8 num_rx_status_rings;
	पूर्णांक tx_sring_idx;
	u8 ring2cid_tid[WIL6210_MAX_TX_RINGS][2]; /* [0] - CID, [1] - TID */
	काष्ठा wil_sta_info sta[WIL6210_MAX_CID];
	u32 ring_idle_trsh; /* HW fetches up to 16 descriptors at once  */
	u32 dma_addr_size; /* indicates dma addr size */
	काष्ठा wil_rx_buff_mgmt rx_buff_mgmt;
	bool use_enhanced_dma_hw;
	काष्ठा wil_txrx_ops txrx_ops;

	काष्ठा mutex mutex; /* क्रम wil6210_priv access in wil_अणुup|करोwnपूर्ण */
	/* क्रम synchronizing device memory access जबतक reset or suspend */
	काष्ठा rw_semaphore mem_lock;
	/* statistics */
	atomic_t isr_count_rx, isr_count_tx;
	/* debugfs */
	काष्ठा dentry *debug;
	काष्ठा wil_blob_wrapper blobs[MAX_FW_MAPPING_TABLE_SIZE];
	u8 discovery_mode;
	u8 abft_len;
	u8 wakeup_trigger;
	काष्ठा wil_suspend_stats suspend_stats;
	काष्ठा wil_debugfs_data dbg_data;
	bool tx_latency; /* collect TX latency measurements */
	माप_प्रकार tx_latency_res; /* bin resolution in usec */

	व्योम *platक्रमm_handle;
	काष्ठा wil_platक्रमm_ops platक्रमm_ops;
	bool keep_radio_on_during_sleep;

	काष्ठा pmc_ctx pmc;

	u8 p2p_dev_started;

	/* P2P_DEVICE vअगर */
	काष्ठा wireless_dev *p2p_wdev;
	काष्ठा wireless_dev *radio_wdev;

	/* High Access Latency Policy voting */
	काष्ठा wil_halp halp;

	क्रमागत wmi_ps_profile_type ps_profile;

	पूर्णांक fw_calib_result;

	काष्ठा notअगरier_block pm_notअगरy;

	bool suspend_resp_rcvd;
	bool suspend_resp_comp;
	u32 bus_request_kbps;
	u32 bus_request_kbps_pre_suspend;

	u32 rgf_fw_निश्चित_code_addr;
	u32 rgf_ucode_निश्चित_code_addr;
	u32 iccm_base;

	/* relevant only क्रम eDMA */
	bool use_compressed_rx_status;
	u32 rx_status_ring_order;
	u32 tx_status_ring_order;
	u32 rx_buff_id_count;
	bool amsdu_en;
	bool use_rx_hw_reordering;
	bool secured_boot;
	u8 boot_config;

	काष्ठा wil_fw_stats_global fw_stats_global;

	u32 max_agg_wsize;
	u32 max_ampdu_size;
	u8 multicast_to_unicast;
	s32 cqm_rssi_thold;
पूर्ण;

#घोषणा wil_to_wiphy(i) (i->wiphy)
#घोषणा wil_to_dev(i) (wiphy_dev(wil_to_wiphy(i)))
#घोषणा wiphy_to_wil(w) (काष्ठा wil6210_priv *)(wiphy_priv(w))
#घोषणा wdev_to_wil(w) (काष्ठा wil6210_priv *)(wdev_priv(w))
#घोषणा ndev_to_wil(n) (wdev_to_wil(n->ieee80211_ptr))
#घोषणा ndev_to_vअगर(n) (काष्ठा wil6210_vअगर *)(netdev_priv(n))
#घोषणा vअगर_to_wil(v) (v->wil)
#घोषणा vअगर_to_ndev(v) (v->ndev)
#घोषणा vअगर_to_wdev(v) (&v->wdev)
#घोषणा GET_MAX_VIFS(wil) min_t(पूर्णांक, (wil)->max_vअगरs, WIL_MAX_VIFS)

अटल अंतरभूत काष्ठा wil6210_vअगर *wdev_to_vअगर(काष्ठा wil6210_priv *wil,
					      काष्ठा wireless_dev *wdev)
अणु
	/* मुख्य पूर्णांकerface is shared with P2P device */
	अगर (wdev == wil->p2p_wdev)
		वापस ndev_to_vअगर(wil->मुख्य_ndev);
	अन्यथा
		वापस container_of(wdev, काष्ठा wil6210_vअगर, wdev);
पूर्ण

अटल अंतरभूत काष्ठा wireless_dev *
vअगर_to_radio_wdev(काष्ठा wil6210_priv *wil, काष्ठा wil6210_vअगर *vअगर)
अणु
	/* मुख्य पूर्णांकerface is shared with P2P device */
	अगर (vअगर->mid)
		वापस vअगर_to_wdev(vअगर);
	अन्यथा
		वापस wil->radio_wdev;
पूर्ण

__म_लिखो(2, 3)
व्योम wil_dbg_trace(काष्ठा wil6210_priv *wil, स्थिर अक्षर *fmt, ...);
__म_लिखो(2, 3)
व्योम __wil_err(काष्ठा wil6210_priv *wil, स्थिर अक्षर *fmt, ...);
__म_लिखो(2, 3)
व्योम __wil_err_ratelimited(काष्ठा wil6210_priv *wil, स्थिर अक्षर *fmt, ...);
__म_लिखो(2, 3)
व्योम __wil_info(काष्ठा wil6210_priv *wil, स्थिर अक्षर *fmt, ...);
__म_लिखो(2, 3)
व्योम wil_dbg_ratelimited(स्थिर काष्ठा wil6210_priv *wil, स्थिर अक्षर *fmt, ...);
#घोषणा wil_dbg(wil, fmt, arg...) करो अणु \
	netdev_dbg(wil->मुख्य_ndev, fmt, ##arg); \
	wil_dbg_trace(wil, fmt, ##arg); \
पूर्ण जबतक (0)

#घोषणा wil_dbg_irq(wil, fmt, arg...) wil_dbg(wil, "DBG[ IRQ]" fmt, ##arg)
#घोषणा wil_dbg_txrx(wil, fmt, arg...) wil_dbg(wil, "DBG[TXRX]" fmt, ##arg)
#घोषणा wil_dbg_wmi(wil, fmt, arg...) wil_dbg(wil, "DBG[ WMI]" fmt, ##arg)
#घोषणा wil_dbg_misc(wil, fmt, arg...) wil_dbg(wil, "DBG[MISC]" fmt, ##arg)
#घोषणा wil_dbg_pm(wil, fmt, arg...) wil_dbg(wil, "DBG[ PM ]" fmt, ##arg)
#घोषणा wil_err(wil, fmt, arg...) __wil_err(wil, "%s: " fmt, __func__, ##arg)
#घोषणा wil_info(wil, fmt, arg...) __wil_info(wil, "%s: " fmt, __func__, ##arg)
#घोषणा wil_err_ratelimited(wil, fmt, arg...) \
	__wil_err_ratelimited(wil, "%s: " fmt, __func__, ##arg)

/* target operations */
/* रेजिस्टर पढ़ो */
अटल अंतरभूत u32 wil_r(काष्ठा wil6210_priv *wil, u32 reg)
अणु
	वापस पढ़ोl(wil->csr + HOSTADDR(reg));
पूर्ण

/* रेजिस्टर ग_लिखो. wmb() to make sure it is completed */
अटल अंतरभूत व्योम wil_w(काष्ठा wil6210_priv *wil, u32 reg, u32 val)
अणु
	ग_लिखोl(val, wil->csr + HOSTADDR(reg));
	wmb(); /* रुको क्रम ग_लिखो to propagate to the HW */
पूर्ण

/* रेजिस्टर set = पढ़ो, OR, ग_लिखो */
अटल अंतरभूत व्योम wil_s(काष्ठा wil6210_priv *wil, u32 reg, u32 val)
अणु
	wil_w(wil, reg, wil_r(wil, reg) | val);
पूर्ण

/* रेजिस्टर clear = पढ़ो, AND with inverted, ग_लिखो */
अटल अंतरभूत व्योम wil_c(काष्ठा wil6210_priv *wil, u32 reg, u32 val)
अणु
	wil_w(wil, reg, wil_r(wil, reg) & ~val);
पूर्ण

/**
 * wil_cid_valid - check cid is valid
 */
अटल अंतरभूत bool wil_cid_valid(काष्ठा wil6210_priv *wil, पूर्णांक cid)
अणु
	वापस (cid >= 0 && cid < wil->max_assoc_sta && cid < WIL6210_MAX_CID);
पूर्ण

व्योम wil_get_board_file(काष्ठा wil6210_priv *wil, अक्षर *buf, माप_प्रकार len);

#अगर defined(CONFIG_DYNAMIC_DEBUG)
#घोषणा wil_hex_dump_txrx(prefix_str, prefix_type, rowsize,	\
			  groupsize, buf, len, ascii)		\
			  prपूर्णांक_hex_dump_debug("DBG[TXRX]" prefix_str,\
					 prefix_type, rowsize,	\
					 groupsize, buf, len, ascii)

#घोषणा wil_hex_dump_wmi(prefix_str, prefix_type, rowsize,	\
			 groupsize, buf, len, ascii)		\
			 prपूर्णांक_hex_dump_debug("DBG[ WMI]" prefix_str,\
					prefix_type, rowsize,	\
					groupsize, buf, len, ascii)

#घोषणा wil_hex_dump_misc(prefix_str, prefix_type, rowsize,	\
			  groupsize, buf, len, ascii)		\
			  prपूर्णांक_hex_dump_debug("DBG[MISC]" prefix_str,\
					prefix_type, rowsize,	\
					groupsize, buf, len, ascii)
#अन्यथा /* defined(CONFIG_DYNAMIC_DEBUG) */
अटल अंतरभूत
व्योम wil_hex_dump_txrx(स्थिर अक्षर *prefix_str, पूर्णांक prefix_type, पूर्णांक rowsize,
		       पूर्णांक groupsize, स्थिर व्योम *buf, माप_प्रकार len, bool ascii)
अणु
पूर्ण

अटल अंतरभूत
व्योम wil_hex_dump_wmi(स्थिर अक्षर *prefix_str, पूर्णांक prefix_type, पूर्णांक rowsize,
		      पूर्णांक groupsize, स्थिर व्योम *buf, माप_प्रकार len, bool ascii)
अणु
पूर्ण

अटल अंतरभूत
व्योम wil_hex_dump_misc(स्थिर अक्षर *prefix_str, पूर्णांक prefix_type, पूर्णांक rowsize,
		       पूर्णांक groupsize, स्थिर व्योम *buf, माप_प्रकार len, bool ascii)
अणु
पूर्ण
#पूर्ण_अगर /* defined(CONFIG_DYNAMIC_DEBUG) */

व्योम wil_स_नकल_fromio_32(व्योम *dst, स्थिर अस्थिर व्योम __iomem *src,
			  माप_प्रकार count);
व्योम wil_स_नकल_toio_32(अस्थिर व्योम __iomem *dst, स्थिर व्योम *src,
			माप_प्रकार count);
पूर्णांक wil_mem_access_lock(काष्ठा wil6210_priv *wil);
व्योम wil_mem_access_unlock(काष्ठा wil6210_priv *wil);

काष्ठा wil6210_vअगर *
wil_vअगर_alloc(काष्ठा wil6210_priv *wil, स्थिर अक्षर *name,
	      अचिन्हित अक्षर name_assign_type, क्रमागत nl80211_अगरtype अगरtype);
व्योम wil_vअगर_मुक्त(काष्ठा wil6210_vअगर *vअगर);
व्योम *wil_अगर_alloc(काष्ठा device *dev);
bool wil_has_other_active_अगरaces(काष्ठा wil6210_priv *wil,
				 काष्ठा net_device *ndev, bool up, bool ok);
bool wil_has_active_अगरaces(काष्ठा wil6210_priv *wil, bool up, bool ok);
व्योम wil_अगर_मुक्त(काष्ठा wil6210_priv *wil);
पूर्णांक wil_vअगर_add(काष्ठा wil6210_priv *wil, काष्ठा wil6210_vअगर *vअगर);
पूर्णांक wil_अगर_add(काष्ठा wil6210_priv *wil);
व्योम wil_vअगर_हटाओ(काष्ठा wil6210_priv *wil, u8 mid);
व्योम wil_अगर_हटाओ(काष्ठा wil6210_priv *wil);
पूर्णांक wil_priv_init(काष्ठा wil6210_priv *wil);
व्योम wil_priv_deinit(काष्ठा wil6210_priv *wil);
पूर्णांक wil_ps_update(काष्ठा wil6210_priv *wil,
		  क्रमागत wmi_ps_profile_type ps_profile);
पूर्णांक wil_reset(काष्ठा wil6210_priv *wil, bool no_fw);
व्योम wil_fw_error_recovery(काष्ठा wil6210_priv *wil);
व्योम wil_set_recovery_state(काष्ठा wil6210_priv *wil, पूर्णांक state);
bool wil_is_recovery_blocked(काष्ठा wil6210_priv *wil);
पूर्णांक wil_up(काष्ठा wil6210_priv *wil);
पूर्णांक __wil_up(काष्ठा wil6210_priv *wil);
पूर्णांक wil_करोwn(काष्ठा wil6210_priv *wil);
पूर्णांक __wil_करोwn(काष्ठा wil6210_priv *wil);
व्योम wil_refresh_fw_capabilities(काष्ठा wil6210_priv *wil);
व्योम wil_mbox_ring_le2cpus(काष्ठा wil6210_mbox_ring *r);
पूर्णांक wil_find_cid(काष्ठा wil6210_priv *wil, u8 mid, स्थिर u8 *mac);
पूर्णांक wil_find_cid_by_idx(काष्ठा wil6210_priv *wil, u8 mid, पूर्णांक idx);
व्योम wil_set_ethtoolops(काष्ठा net_device *ndev);

काष्ठा fw_map *wil_find_fw_mapping(स्थिर अक्षर *section);
व्योम __iomem *wmi_buffer_block(काष्ठा wil6210_priv *wil, __le32 ptr, u32 size);
व्योम __iomem *wmi_buffer(काष्ठा wil6210_priv *wil, __le32 ptr);
व्योम __iomem *wmi_addr(काष्ठा wil6210_priv *wil, u32 ptr);
पूर्णांक wmi_पढ़ो_hdr(काष्ठा wil6210_priv *wil, __le32 ptr,
		 काष्ठा wil6210_mbox_hdr *hdr);
पूर्णांक wmi_send(काष्ठा wil6210_priv *wil, u16 cmdid, u8 mid, व्योम *buf, u16 len);
व्योम wmi_recv_cmd(काष्ठा wil6210_priv *wil);
पूर्णांक wmi_call(काष्ठा wil6210_priv *wil, u16 cmdid, u8 mid, व्योम *buf, u16 len,
	     u16 reply_id, व्योम *reply, u16 reply_size, पूर्णांक to_msec);
व्योम wmi_event_worker(काष्ठा work_काष्ठा *work);
व्योम wmi_event_flush(काष्ठा wil6210_priv *wil);
पूर्णांक wmi_set_ssid(काष्ठा wil6210_vअगर *vअगर, u8 ssid_len, स्थिर व्योम *ssid);
पूर्णांक wmi_get_ssid(काष्ठा wil6210_vअगर *vअगर, u8 *ssid_len, व्योम *ssid);
पूर्णांक wmi_set_channel(काष्ठा wil6210_priv *wil, पूर्णांक channel);
पूर्णांक wmi_get_channel(काष्ठा wil6210_priv *wil, पूर्णांक *channel);
पूर्णांक wmi_del_cipher_key(काष्ठा wil6210_vअगर *vअगर, u8 key_index,
		       स्थिर व्योम *mac_addr, पूर्णांक key_usage);
पूर्णांक wmi_add_cipher_key(काष्ठा wil6210_vअगर *vअगर, u8 key_index,
		       स्थिर व्योम *mac_addr, पूर्णांक key_len, स्थिर व्योम *key,
		       पूर्णांक key_usage);
पूर्णांक wmi_echo(काष्ठा wil6210_priv *wil);
पूर्णांक wmi_set_ie(काष्ठा wil6210_vअगर *vअगर, u8 type, u16 ie_len, स्थिर व्योम *ie);
पूर्णांक wmi_rx_chain_add(काष्ठा wil6210_priv *wil, काष्ठा wil_ring *vring);
पूर्णांक wmi_update_ft_ies(काष्ठा wil6210_vअगर *vअगर, u16 ie_len, स्थिर व्योम *ie);
पूर्णांक wmi_rxon(काष्ठा wil6210_priv *wil, bool on);
पूर्णांक wmi_get_temperature(काष्ठा wil6210_priv *wil, u32 *t_m, u32 *t_r);
पूर्णांक wmi_get_all_temperatures(काष्ठा wil6210_priv *wil,
			     काष्ठा wmi_temp_sense_all_करोne_event
			     *sense_all_evt);
पूर्णांक wmi_disconnect_sta(काष्ठा wil6210_vअगर *vअगर, स्थिर u8 *mac, u16 reason,
		       bool del_sta);
पूर्णांक wmi_addba(काष्ठा wil6210_priv *wil, u8 mid,
	      u8 ringid, u8 size, u16 समयout);
पूर्णांक wmi_delba_tx(काष्ठा wil6210_priv *wil, u8 mid, u8 ringid, u16 reason);
पूर्णांक wmi_delba_rx(काष्ठा wil6210_priv *wil, u8 mid, u8 cid, u8 tid, u16 reason);
पूर्णांक wmi_addba_rx_resp(काष्ठा wil6210_priv *wil,
		      u8 mid, u8 cid, u8 tid, u8 token,
		      u16 status, bool amsdu, u16 agg_wsize, u16 समयout);
पूर्णांक wmi_ps_dev_profile_cfg(काष्ठा wil6210_priv *wil,
			   क्रमागत wmi_ps_profile_type ps_profile);
पूर्णांक wmi_set_mgmt_retry(काष्ठा wil6210_priv *wil, u8 retry_लघु);
पूर्णांक wmi_get_mgmt_retry(काष्ठा wil6210_priv *wil, u8 *retry_लघु);
पूर्णांक wmi_new_sta(काष्ठा wil6210_vअगर *vअगर, स्थिर u8 *mac, u8 aid);
पूर्णांक wmi_port_allocate(काष्ठा wil6210_priv *wil, u8 mid,
		      स्थिर u8 *mac, क्रमागत nl80211_अगरtype अगरtype);
पूर्णांक wmi_port_delete(काष्ठा wil6210_priv *wil, u8 mid);
पूर्णांक wmi_link_stats_cfg(काष्ठा wil6210_vअगर *vअगर, u32 type, u8 cid, u32 पूर्णांकerval);
पूर्णांक wil_addba_rx_request(काष्ठा wil6210_priv *wil, u8 mid, u8 cid, u8 tid,
			 u8 dialog_token, __le16 ba_param_set,
			 __le16 ba_समयout, __le16 ba_seq_ctrl);
पूर्णांक wil_addba_tx_request(काष्ठा wil6210_priv *wil, u8 ringid, u16 wsize);

व्योम wil6210_clear_irq(काष्ठा wil6210_priv *wil);
पूर्णांक wil6210_init_irq(काष्ठा wil6210_priv *wil, पूर्णांक irq);
व्योम wil6210_fini_irq(काष्ठा wil6210_priv *wil, पूर्णांक irq);
व्योम wil_mask_irq(काष्ठा wil6210_priv *wil);
व्योम wil_unmask_irq(काष्ठा wil6210_priv *wil);
व्योम wil_configure_पूर्णांकerrupt_moderation(काष्ठा wil6210_priv *wil);
व्योम wil_disable_irq(काष्ठा wil6210_priv *wil);
व्योम wil_enable_irq(काष्ठा wil6210_priv *wil);
व्योम wil6210_mask_halp(काष्ठा wil6210_priv *wil);

/* P2P */
bool wil_p2p_is_social_scan(काष्ठा cfg80211_scan_request *request);
पूर्णांक wil_p2p_search(काष्ठा wil6210_vअगर *vअगर,
		   काष्ठा cfg80211_scan_request *request);
पूर्णांक wil_p2p_listen(काष्ठा wil6210_priv *wil, काष्ठा wireless_dev *wdev,
		   अचिन्हित पूर्णांक duration, काष्ठा ieee80211_channel *chan,
		   u64 *cookie);
u8 wil_p2p_stop_discovery(काष्ठा wil6210_vअगर *vअगर);
पूर्णांक wil_p2p_cancel_listen(काष्ठा wil6210_vअगर *vअगर, u64 cookie);
व्योम wil_p2p_listen_expired(काष्ठा work_काष्ठा *work);
व्योम wil_p2p_search_expired(काष्ठा work_काष्ठा *work);
व्योम wil_p2p_stop_radio_operations(काष्ठा wil6210_priv *wil);
व्योम wil_p2p_delayed_listen_work(काष्ठा work_काष्ठा *work);

/* WMI क्रम P2P */
पूर्णांक wmi_p2p_cfg(काष्ठा wil6210_vअगर *vअगर, पूर्णांक channel, पूर्णांक bi);
पूर्णांक wmi_start_listen(काष्ठा wil6210_vअगर *vअगर);
पूर्णांक wmi_start_search(काष्ठा wil6210_vअगर *vअगर);
पूर्णांक wmi_stop_discovery(काष्ठा wil6210_vअगर *vअगर);

पूर्णांक wil_cfg80211_mgmt_tx(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
			 काष्ठा cfg80211_mgmt_tx_params *params,
			 u64 *cookie);
व्योम wil_cfg80211_ap_recovery(काष्ठा wil6210_priv *wil);
पूर्णांक wil_cfg80211_अगरace_combinations_from_fw(
	काष्ठा wil6210_priv *wil,
	स्थिर काष्ठा wil_fw_record_concurrency *conc);
पूर्णांक wil_vअगर_prepare_stop(काष्ठा wil6210_vअगर *vअगर);

#अगर defined(CONFIG_WIL6210_DEBUGFS)
पूर्णांक wil6210_debugfs_init(काष्ठा wil6210_priv *wil);
व्योम wil6210_debugfs_हटाओ(काष्ठा wil6210_priv *wil);
#अन्यथा
अटल अंतरभूत पूर्णांक wil6210_debugfs_init(काष्ठा wil6210_priv *wil) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम wil6210_debugfs_हटाओ(काष्ठा wil6210_priv *wil) अणुपूर्ण
#पूर्ण_अगर

पूर्णांक wil_cid_fill_sinfo(काष्ठा wil6210_vअगर *vअगर, पूर्णांक cid,
		       काष्ठा station_info *sinfo);

काष्ठा wil6210_priv *wil_cfg80211_init(काष्ठा device *dev);
व्योम wil_cfg80211_deinit(काष्ठा wil6210_priv *wil);
व्योम wil_p2p_wdev_मुक्त(काष्ठा wil6210_priv *wil);

पूर्णांक wmi_set_mac_address(काष्ठा wil6210_priv *wil, व्योम *addr);
पूर्णांक wmi_pcp_start(काष्ठा wil6210_vअगर *vअगर, पूर्णांक bi, u8 wmi_nettype, u8 chan,
		  u8 edmg_chan, u8 hidden_ssid, u8 is_go);
पूर्णांक wmi_pcp_stop(काष्ठा wil6210_vअगर *vअगर);
पूर्णांक wmi_led_cfg(काष्ठा wil6210_priv *wil, bool enable);
पूर्णांक wmi_पात_scan(काष्ठा wil6210_vअगर *vअगर);
व्योम wil_पात_scan(काष्ठा wil6210_vअगर *vअगर, bool sync);
व्योम wil_पात_scan_all_vअगरs(काष्ठा wil6210_priv *wil, bool sync);
व्योम wil6210_bus_request(काष्ठा wil6210_priv *wil, u32 kbps);
व्योम wil6210_disconnect(काष्ठा wil6210_vअगर *vअगर, स्थिर u8 *bssid,
			u16 reason_code);
व्योम wil6210_disconnect_complete(काष्ठा wil6210_vअगर *vअगर, स्थिर u8 *bssid,
				 u16 reason_code);
व्योम wil_probe_client_flush(काष्ठा wil6210_vअगर *vअगर);
व्योम wil_probe_client_worker(काष्ठा work_काष्ठा *work);
व्योम wil_disconnect_worker(काष्ठा work_काष्ठा *work);
व्योम wil_enable_tx_key_worker(काष्ठा work_काष्ठा *work);

व्योम wil_init_txrx_ops(काष्ठा wil6210_priv *wil);

/* TX API */
पूर्णांक wil_ring_init_tx(काष्ठा wil6210_vअगर *vअगर, पूर्णांक cid);
पूर्णांक wil_vring_init_bcast(काष्ठा wil6210_vअगर *vअगर, पूर्णांक id, पूर्णांक size);
पूर्णांक wil_bcast_init(काष्ठा wil6210_vअगर *vअगर);
व्योम wil_bcast_fini(काष्ठा wil6210_vअगर *vअगर);
व्योम wil_bcast_fini_all(काष्ठा wil6210_priv *wil);

व्योम wil_update_net_queues(काष्ठा wil6210_priv *wil, काष्ठा wil6210_vअगर *vअगर,
			   काष्ठा wil_ring *ring, bool should_stop);
व्योम wil_update_net_queues_bh(काष्ठा wil6210_priv *wil, काष्ठा wil6210_vअगर *vअगर,
			      काष्ठा wil_ring *ring, bool check_stop);
netdev_tx_t wil_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *ndev);
पूर्णांक wil_tx_complete(काष्ठा wil6210_vअगर *vअगर, पूर्णांक ringid);
व्योम wil_tx_complete_handle_eapol(काष्ठा wil6210_vअगर *vअगर,
				  काष्ठा sk_buff *skb);
व्योम wil6210_unmask_irq_tx(काष्ठा wil6210_priv *wil);
व्योम wil6210_unmask_irq_tx_edma(काष्ठा wil6210_priv *wil);

/* RX API */
व्योम wil_rx_handle(काष्ठा wil6210_priv *wil, पूर्णांक *quota);
व्योम wil6210_unmask_irq_rx(काष्ठा wil6210_priv *wil);
व्योम wil6210_unmask_irq_rx_edma(काष्ठा wil6210_priv *wil);
व्योम wil_set_crypto_rx(u8 key_index, क्रमागत wmi_key_usage key_usage,
		       काष्ठा wil_sta_info *cs,
		       काष्ठा key_params *params);

पूर्णांक wil_अगरtype_nl2wmi(क्रमागत nl80211_अगरtype type);

पूर्णांक wil_request_firmware(काष्ठा wil6210_priv *wil, स्थिर अक्षर *name,
			 bool load);
पूर्णांक wil_request_board(काष्ठा wil6210_priv *wil, स्थिर अक्षर *name);
bool wil_fw_verअगरy_file_exists(काष्ठा wil6210_priv *wil, स्थिर अक्षर *name);

व्योम wil_pm_runसमय_allow(काष्ठा wil6210_priv *wil);
व्योम wil_pm_runसमय_क्रमbid(काष्ठा wil6210_priv *wil);
पूर्णांक wil_pm_runसमय_get(काष्ठा wil6210_priv *wil);
व्योम wil_pm_runसमय_put(काष्ठा wil6210_priv *wil);

पूर्णांक wil_can_suspend(काष्ठा wil6210_priv *wil, bool is_runसमय);
पूर्णांक wil_suspend(काष्ठा wil6210_priv *wil, bool is_runसमय, bool keep_radio_on);
पूर्णांक wil_resume(काष्ठा wil6210_priv *wil, bool is_runसमय, bool keep_radio_on);
bool wil_is_wmi_idle(काष्ठा wil6210_priv *wil);
पूर्णांक wmi_resume(काष्ठा wil6210_priv *wil);
पूर्णांक wmi_suspend(काष्ठा wil6210_priv *wil);
bool wil_is_tx_idle(काष्ठा wil6210_priv *wil);

पूर्णांक wil_fw_copy_crash_dump(काष्ठा wil6210_priv *wil, व्योम *dest, u32 size);
व्योम wil_fw_core_dump(काष्ठा wil6210_priv *wil);

व्योम wil_halp_vote(काष्ठा wil6210_priv *wil);
व्योम wil_halp_unvote(काष्ठा wil6210_priv *wil);
व्योम wil6210_set_halp(काष्ठा wil6210_priv *wil);
व्योम wil6210_clear_halp(काष्ठा wil6210_priv *wil);

पूर्णांक wmi_start_sched_scan(काष्ठा wil6210_priv *wil,
			 काष्ठा cfg80211_sched_scan_request *request);
पूर्णांक wmi_stop_sched_scan(काष्ठा wil6210_priv *wil);
पूर्णांक wmi_mgmt_tx(काष्ठा wil6210_vअगर *vअगर, स्थिर u8 *buf, माप_प्रकार len);
पूर्णांक wmi_mgmt_tx_ext(काष्ठा wil6210_vअगर *vअगर, स्थिर u8 *buf, माप_प्रकार len,
		    u8 channel, u16 duration_ms);
पूर्णांक wmi_rbufcap_cfg(काष्ठा wil6210_priv *wil, bool enable, u16 threshold);

पूर्णांक wil_wmi2spec_ch(u8 wmi_ch, u8 *spec_ch);
पूर्णांक wil_spec2wmi_ch(u8 spec_ch, u8 *wmi_ch);
व्योम wil_update_supported_bands(काष्ठा wil6210_priv *wil);

पूर्णांक reverse_स_भेद(स्थिर व्योम *cs, स्थिर व्योम *ct, माप_प्रकार count);

/* WMI क्रम enhanced DMA */
पूर्णांक wil_wmi_tx_sring_cfg(काष्ठा wil6210_priv *wil, पूर्णांक ring_id);
पूर्णांक wil_wmi_cfg_def_rx_offload(काष्ठा wil6210_priv *wil,
			       u16 max_rx_pl_per_desc);
पूर्णांक wil_wmi_rx_sring_add(काष्ठा wil6210_priv *wil, u16 ring_id);
पूर्णांक wil_wmi_rx_desc_ring_add(काष्ठा wil6210_priv *wil, पूर्णांक status_ring_id);
पूर्णांक wil_wmi_tx_desc_ring_add(काष्ठा wil6210_vअगर *vअगर, पूर्णांक ring_id, पूर्णांक cid,
			     पूर्णांक tid);
पूर्णांक wil_wmi_bcast_desc_ring_add(काष्ठा wil6210_vअगर *vअगर, पूर्णांक ring_id);
पूर्णांक wmi_addba_rx_resp_edma(काष्ठा wil6210_priv *wil, u8 mid, u8 cid,
			   u8 tid, u8 token, u16 status, bool amsdu,
			   u16 agg_wsize, u16 समयout);

व्योम update_supported_bands(काष्ठा wil6210_priv *wil);

व्योम wil_clear_fw_log_addr(काष्ठा wil6210_priv *wil);
पूर्णांक wmi_set_cqm_rssi_config(काष्ठा wil6210_priv *wil,
			    s32 rssi_thold, u32 rssi_hyst);
#पूर्ण_अगर /* __WIL6210_H__ */
