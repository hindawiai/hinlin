<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/* Copyright 2017 Microsemi Corporation
 * Copyright 2018-2019 NXP Semiconductors
 */
#समावेश <linux/fsl/enetc_mdपन.स>
#समावेश <soc/mscc/ocelot_qsys.h>
#समावेश <soc/mscc/ocelot_vcap.h>
#समावेश <soc/mscc/ocelot_ptp.h>
#समावेश <soc/mscc/ocelot_sys.h>
#समावेश <soc/mscc/ocelot.h>
#समावेश <linux/dsa/ocelot.h>
#समावेश <linux/pcs-lynx.h>
#समावेश <net/pkt_sched.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/pci.h>
#समावेश "felix.h"

#घोषणा VSC9959_TAS_GCL_ENTRY_MAX	63

अटल स्थिर u32 vsc9959_ana_regmap[] = अणु
	REG(ANA_ADVLEARN,			0x0089a0),
	REG(ANA_VLANMASK,			0x0089a4),
	REG_RESERVED(ANA_PORT_B_DOMAIN),
	REG(ANA_ANAGEFIL,			0x0089ac),
	REG(ANA_ANEVENTS,			0x0089b0),
	REG(ANA_STORMLIMIT_BURST,		0x0089b4),
	REG(ANA_STORMLIMIT_CFG,			0x0089b8),
	REG(ANA_ISOLATED_PORTS,			0x0089c8),
	REG(ANA_COMMUNITY_PORTS,		0x0089cc),
	REG(ANA_AUTOAGE,			0x0089d0),
	REG(ANA_MACTOPTIONS,			0x0089d4),
	REG(ANA_LEARNDISC,			0x0089d8),
	REG(ANA_AGENCTRL,			0x0089dc),
	REG(ANA_MIRRORPORTS,			0x0089e0),
	REG(ANA_EMIRRORPORTS,			0x0089e4),
	REG(ANA_FLOODING,			0x0089e8),
	REG(ANA_FLOODING_IPMC,			0x008a08),
	REG(ANA_SFLOW_CFG,			0x008a0c),
	REG(ANA_PORT_MODE,			0x008a28),
	REG(ANA_CUT_THRU_CFG,			0x008a48),
	REG(ANA_PGID_PGID,			0x008400),
	REG(ANA_TABLES_ANMOVED,			0x007f1c),
	REG(ANA_TABLES_MACHDATA,		0x007f20),
	REG(ANA_TABLES_MACLDATA,		0x007f24),
	REG(ANA_TABLES_STREAMDATA,		0x007f28),
	REG(ANA_TABLES_MACACCESS,		0x007f2c),
	REG(ANA_TABLES_MACTINDX,		0x007f30),
	REG(ANA_TABLES_VLANACCESS,		0x007f34),
	REG(ANA_TABLES_VLANTIDX,		0x007f38),
	REG(ANA_TABLES_ISDXACCESS,		0x007f3c),
	REG(ANA_TABLES_ISDXTIDX,		0x007f40),
	REG(ANA_TABLES_ENTRYLIM,		0x007f00),
	REG(ANA_TABLES_PTP_ID_HIGH,		0x007f44),
	REG(ANA_TABLES_PTP_ID_LOW,		0x007f48),
	REG(ANA_TABLES_STREAMACCESS,		0x007f4c),
	REG(ANA_TABLES_STREAMTIDX,		0x007f50),
	REG(ANA_TABLES_SEQ_HISTORY,		0x007f54),
	REG(ANA_TABLES_SEQ_MASK,		0x007f58),
	REG(ANA_TABLES_SFID_MASK,		0x007f5c),
	REG(ANA_TABLES_SFIDACCESS,		0x007f60),
	REG(ANA_TABLES_SFIDTIDX,		0x007f64),
	REG(ANA_MSTI_STATE,			0x008600),
	REG(ANA_OAM_UPM_LM_CNT,			0x008000),
	REG(ANA_SG_ACCESS_CTRL,			0x008a64),
	REG(ANA_SG_CONFIG_REG_1,		0x007fb0),
	REG(ANA_SG_CONFIG_REG_2,		0x007fb4),
	REG(ANA_SG_CONFIG_REG_3,		0x007fb8),
	REG(ANA_SG_CONFIG_REG_4,		0x007fbc),
	REG(ANA_SG_CONFIG_REG_5,		0x007fc0),
	REG(ANA_SG_GCL_GS_CONFIG,		0x007f80),
	REG(ANA_SG_GCL_TI_CONFIG,		0x007f90),
	REG(ANA_SG_STATUS_REG_1,		0x008980),
	REG(ANA_SG_STATUS_REG_2,		0x008984),
	REG(ANA_SG_STATUS_REG_3,		0x008988),
	REG(ANA_PORT_VLAN_CFG,			0x007800),
	REG(ANA_PORT_DROP_CFG,			0x007804),
	REG(ANA_PORT_QOS_CFG,			0x007808),
	REG(ANA_PORT_VCAP_CFG,			0x00780c),
	REG(ANA_PORT_VCAP_S1_KEY_CFG,		0x007810),
	REG(ANA_PORT_VCAP_S2_CFG,		0x00781c),
	REG(ANA_PORT_PCP_DEI_MAP,		0x007820),
	REG(ANA_PORT_CPU_FWD_CFG,		0x007860),
	REG(ANA_PORT_CPU_FWD_BPDU_CFG,		0x007864),
	REG(ANA_PORT_CPU_FWD_GARP_CFG,		0x007868),
	REG(ANA_PORT_CPU_FWD_CCM_CFG,		0x00786c),
	REG(ANA_PORT_PORT_CFG,			0x007870),
	REG(ANA_PORT_POL_CFG,			0x007874),
	REG(ANA_PORT_PTP_CFG,			0x007878),
	REG(ANA_PORT_PTP_DLY1_CFG,		0x00787c),
	REG(ANA_PORT_PTP_DLY2_CFG,		0x007880),
	REG(ANA_PORT_SFID_CFG,			0x007884),
	REG(ANA_PFC_PFC_CFG,			0x008800),
	REG_RESERVED(ANA_PFC_PFC_TIMER),
	REG_RESERVED(ANA_IPT_OAM_MEP_CFG),
	REG_RESERVED(ANA_IPT_IPT),
	REG_RESERVED(ANA_PPT_PPT),
	REG_RESERVED(ANA_FID_MAP_FID_MAP),
	REG(ANA_AGGR_CFG,			0x008a68),
	REG(ANA_CPUQ_CFG,			0x008a6c),
	REG_RESERVED(ANA_CPUQ_CFG2),
	REG(ANA_CPUQ_8021_CFG,			0x008a74),
	REG(ANA_DSCP_CFG,			0x008ab4),
	REG(ANA_DSCP_REWR_CFG,			0x008bb4),
	REG(ANA_VCAP_RNG_TYPE_CFG,		0x008bf4),
	REG(ANA_VCAP_RNG_VAL_CFG,		0x008c14),
	REG_RESERVED(ANA_VRAP_CFG),
	REG_RESERVED(ANA_VRAP_HDR_DATA),
	REG_RESERVED(ANA_VRAP_HDR_MASK),
	REG(ANA_DISCARD_CFG,			0x008c40),
	REG(ANA_FID_CFG,			0x008c44),
	REG(ANA_POL_PIR_CFG,			0x004000),
	REG(ANA_POL_CIR_CFG,			0x004004),
	REG(ANA_POL_MODE_CFG,			0x004008),
	REG(ANA_POL_PIR_STATE,			0x00400c),
	REG(ANA_POL_CIR_STATE,			0x004010),
	REG_RESERVED(ANA_POL_STATE),
	REG(ANA_POL_FLOWC,			0x008c48),
	REG(ANA_POL_HYST,			0x008cb4),
	REG_RESERVED(ANA_POL_MISC_CFG),
पूर्ण;

अटल स्थिर u32 vsc9959_qs_regmap[] = अणु
	REG(QS_XTR_GRP_CFG,			0x000000),
	REG(QS_XTR_RD,				0x000008),
	REG(QS_XTR_FRM_PRUNING,			0x000010),
	REG(QS_XTR_FLUSH,			0x000018),
	REG(QS_XTR_DATA_PRESENT,		0x00001c),
	REG(QS_XTR_CFG,				0x000020),
	REG(QS_INJ_GRP_CFG,			0x000024),
	REG(QS_INJ_WR,				0x00002c),
	REG(QS_INJ_CTRL,			0x000034),
	REG(QS_INJ_STATUS,			0x00003c),
	REG(QS_INJ_ERR,				0x000040),
	REG_RESERVED(QS_INH_DBG),
पूर्ण;

अटल स्थिर u32 vsc9959_vcap_regmap[] = अणु
	/* VCAP_CORE_CFG */
	REG(VCAP_CORE_UPDATE_CTRL,		0x000000),
	REG(VCAP_CORE_MV_CFG,			0x000004),
	/* VCAP_CORE_CACHE */
	REG(VCAP_CACHE_ENTRY_DAT,		0x000008),
	REG(VCAP_CACHE_MASK_DAT,		0x000108),
	REG(VCAP_CACHE_ACTION_DAT,		0x000208),
	REG(VCAP_CACHE_CNT_DAT,			0x000308),
	REG(VCAP_CACHE_TG_DAT,			0x000388),
	/* VCAP_CONST */
	REG(VCAP_CONST_VCAP_VER,		0x000398),
	REG(VCAP_CONST_ENTRY_WIDTH,		0x00039c),
	REG(VCAP_CONST_ENTRY_CNT,		0x0003a0),
	REG(VCAP_CONST_ENTRY_SWCNT,		0x0003a4),
	REG(VCAP_CONST_ENTRY_TG_WIDTH,		0x0003a8),
	REG(VCAP_CONST_ACTION_DEF_CNT,		0x0003ac),
	REG(VCAP_CONST_ACTION_WIDTH,		0x0003b0),
	REG(VCAP_CONST_CNT_WIDTH,		0x0003b4),
	REG(VCAP_CONST_CORE_CNT,		0x0003b8),
	REG(VCAP_CONST_IF_CNT,			0x0003bc),
पूर्ण;

अटल स्थिर u32 vsc9959_qsys_regmap[] = अणु
	REG(QSYS_PORT_MODE,			0x00f460),
	REG(QSYS_SWITCH_PORT_MODE,		0x00f480),
	REG(QSYS_STAT_CNT_CFG,			0x00f49c),
	REG(QSYS_EEE_CFG,			0x00f4a0),
	REG(QSYS_EEE_THRES,			0x00f4b8),
	REG(QSYS_IGR_NO_SHARING,		0x00f4bc),
	REG(QSYS_EGR_NO_SHARING,		0x00f4c0),
	REG(QSYS_SW_STATUS,			0x00f4c4),
	REG(QSYS_EXT_CPU_CFG,			0x00f4e0),
	REG_RESERVED(QSYS_PAD_CFG),
	REG(QSYS_CPU_GROUP_MAP,			0x00f4e8),
	REG_RESERVED(QSYS_QMAP),
	REG_RESERVED(QSYS_ISDX_SGRP),
	REG_RESERVED(QSYS_TIMED_FRAME_ENTRY),
	REG(QSYS_TFRM_MISC,			0x00f50c),
	REG(QSYS_TFRM_PORT_DLY,			0x00f510),
	REG(QSYS_TFRM_TIMER_CFG_1,		0x00f514),
	REG(QSYS_TFRM_TIMER_CFG_2,		0x00f518),
	REG(QSYS_TFRM_TIMER_CFG_3,		0x00f51c),
	REG(QSYS_TFRM_TIMER_CFG_4,		0x00f520),
	REG(QSYS_TFRM_TIMER_CFG_5,		0x00f524),
	REG(QSYS_TFRM_TIMER_CFG_6,		0x00f528),
	REG(QSYS_TFRM_TIMER_CFG_7,		0x00f52c),
	REG(QSYS_TFRM_TIMER_CFG_8,		0x00f530),
	REG(QSYS_RED_PROखाता,			0x00f534),
	REG(QSYS_RES_QOS_MODE,			0x00f574),
	REG(QSYS_RES_CFG,			0x00c000),
	REG(QSYS_RES_STAT,			0x00c004),
	REG(QSYS_EGR_DROP_MODE,			0x00f578),
	REG(QSYS_EQ_CTRL,			0x00f57c),
	REG_RESERVED(QSYS_EVENTS_CORE),
	REG(QSYS_QMAXSDU_CFG_0,			0x00f584),
	REG(QSYS_QMAXSDU_CFG_1,			0x00f5a0),
	REG(QSYS_QMAXSDU_CFG_2,			0x00f5bc),
	REG(QSYS_QMAXSDU_CFG_3,			0x00f5d8),
	REG(QSYS_QMAXSDU_CFG_4,			0x00f5f4),
	REG(QSYS_QMAXSDU_CFG_5,			0x00f610),
	REG(QSYS_QMAXSDU_CFG_6,			0x00f62c),
	REG(QSYS_QMAXSDU_CFG_7,			0x00f648),
	REG(QSYS_PREEMPTION_CFG,		0x00f664),
	REG(QSYS_CIR_CFG,			0x000000),
	REG(QSYS_EIR_CFG,			0x000004),
	REG(QSYS_SE_CFG,			0x000008),
	REG(QSYS_SE_DWRR_CFG,			0x00000c),
	REG_RESERVED(QSYS_SE_CONNECT),
	REG(QSYS_SE_DLB_SENSE,			0x000040),
	REG(QSYS_CIR_STATE,			0x000044),
	REG(QSYS_EIR_STATE,			0x000048),
	REG_RESERVED(QSYS_SE_STATE),
	REG(QSYS_HSCH_MISC_CFG,			0x00f67c),
	REG(QSYS_TAG_CONFIG,			0x00f680),
	REG(QSYS_TAS_PARAM_CFG_CTRL,		0x00f698),
	REG(QSYS_PORT_MAX_SDU,			0x00f69c),
	REG(QSYS_PARAM_CFG_REG_1,		0x00f440),
	REG(QSYS_PARAM_CFG_REG_2,		0x00f444),
	REG(QSYS_PARAM_CFG_REG_3,		0x00f448),
	REG(QSYS_PARAM_CFG_REG_4,		0x00f44c),
	REG(QSYS_PARAM_CFG_REG_5,		0x00f450),
	REG(QSYS_GCL_CFG_REG_1,			0x00f454),
	REG(QSYS_GCL_CFG_REG_2,			0x00f458),
	REG(QSYS_PARAM_STATUS_REG_1,		0x00f400),
	REG(QSYS_PARAM_STATUS_REG_2,		0x00f404),
	REG(QSYS_PARAM_STATUS_REG_3,		0x00f408),
	REG(QSYS_PARAM_STATUS_REG_4,		0x00f40c),
	REG(QSYS_PARAM_STATUS_REG_5,		0x00f410),
	REG(QSYS_PARAM_STATUS_REG_6,		0x00f414),
	REG(QSYS_PARAM_STATUS_REG_7,		0x00f418),
	REG(QSYS_PARAM_STATUS_REG_8,		0x00f41c),
	REG(QSYS_PARAM_STATUS_REG_9,		0x00f420),
	REG(QSYS_GCL_STATUS_REG_1,		0x00f424),
	REG(QSYS_GCL_STATUS_REG_2,		0x00f428),
पूर्ण;

अटल स्थिर u32 vsc9959_rew_regmap[] = अणु
	REG(REW_PORT_VLAN_CFG,			0x000000),
	REG(REW_TAG_CFG,			0x000004),
	REG(REW_PORT_CFG,			0x000008),
	REG(REW_DSCP_CFG,			0x00000c),
	REG(REW_PCP_DEI_QOS_MAP_CFG,		0x000010),
	REG(REW_PTP_CFG,			0x000050),
	REG(REW_PTP_DLY1_CFG,			0x000054),
	REG(REW_RED_TAG_CFG,			0x000058),
	REG(REW_DSCP_REMAP_DP1_CFG,		0x000410),
	REG(REW_DSCP_REMAP_CFG,			0x000510),
	REG_RESERVED(REW_STAT_CFG),
	REG_RESERVED(REW_REW_STICKY),
	REG_RESERVED(REW_PPT),
पूर्ण;

अटल स्थिर u32 vsc9959_sys_regmap[] = अणु
	REG(SYS_COUNT_RX_OCTETS,		0x000000),
	REG(SYS_COUNT_RX_MULTICAST,		0x000008),
	REG(SYS_COUNT_RX_SHORTS,		0x000010),
	REG(SYS_COUNT_RX_FRAGMENTS,		0x000014),
	REG(SYS_COUNT_RX_JABBERS,		0x000018),
	REG(SYS_COUNT_RX_64,			0x000024),
	REG(SYS_COUNT_RX_65_127,		0x000028),
	REG(SYS_COUNT_RX_128_255,		0x00002c),
	REG(SYS_COUNT_RX_256_1023,		0x000030),
	REG(SYS_COUNT_RX_1024_1526,		0x000034),
	REG(SYS_COUNT_RX_1527_MAX,		0x000038),
	REG(SYS_COUNT_RX_LONGS,			0x000044),
	REG(SYS_COUNT_TX_OCTETS,		0x000200),
	REG(SYS_COUNT_TX_COLLISION,		0x000210),
	REG(SYS_COUNT_TX_DROPS,			0x000214),
	REG(SYS_COUNT_TX_64,			0x00021c),
	REG(SYS_COUNT_TX_65_127,		0x000220),
	REG(SYS_COUNT_TX_128_511,		0x000224),
	REG(SYS_COUNT_TX_512_1023,		0x000228),
	REG(SYS_COUNT_TX_1024_1526,		0x00022c),
	REG(SYS_COUNT_TX_1527_MAX,		0x000230),
	REG(SYS_COUNT_TX_AGING,			0x000278),
	REG(SYS_RESET_CFG,			0x000e00),
	REG(SYS_SR_ETYPE_CFG,			0x000e04),
	REG(SYS_VLAN_ETYPE_CFG,			0x000e08),
	REG(SYS_PORT_MODE,			0x000e0c),
	REG(SYS_FRONT_PORT_MODE,		0x000e2c),
	REG(SYS_FRM_AGING,			0x000e44),
	REG(SYS_STAT_CFG,			0x000e48),
	REG(SYS_SW_STATUS,			0x000e4c),
	REG_RESERVED(SYS_MISC_CFG),
	REG(SYS_REW_MAC_HIGH_CFG,		0x000e6c),
	REG(SYS_REW_MAC_LOW_CFG,		0x000e84),
	REG(SYS_TIMESTAMP_OFFSET,		0x000e9c),
	REG(SYS_PAUSE_CFG,			0x000ea0),
	REG(SYS_PAUSE_TOT_CFG,			0x000ebc),
	REG(SYS_ATOP,				0x000ec0),
	REG(SYS_ATOP_TOT_CFG,			0x000edc),
	REG(SYS_MAC_FC_CFG,			0x000ee0),
	REG(SYS_MMGT,				0x000ef8),
	REG_RESERVED(SYS_MMGT_FAST),
	REG_RESERVED(SYS_EVENTS_DIF),
	REG_RESERVED(SYS_EVENTS_CORE),
	REG_RESERVED(SYS_CNT),
	REG(SYS_PTP_STATUS,			0x000f14),
	REG(SYS_PTP_TXSTAMP,			0x000f18),
	REG(SYS_PTP_NXT,			0x000f1c),
	REG(SYS_PTP_CFG,			0x000f20),
	REG(SYS_RAM_INIT,			0x000f24),
	REG_RESERVED(SYS_CM_ADDR),
	REG_RESERVED(SYS_CM_DATA_WR),
	REG_RESERVED(SYS_CM_DATA_RD),
	REG_RESERVED(SYS_CM_OP),
	REG_RESERVED(SYS_CM_DATA),
पूर्ण;

अटल स्थिर u32 vsc9959_ptp_regmap[] = अणु
	REG(PTP_PIN_CFG,			0x000000),
	REG(PTP_PIN_TOD_SEC_MSB,		0x000004),
	REG(PTP_PIN_TOD_SEC_LSB,		0x000008),
	REG(PTP_PIN_TOD_NSEC,			0x00000c),
	REG(PTP_PIN_WF_HIGH_PERIOD,		0x000014),
	REG(PTP_PIN_WF_LOW_PERIOD,		0x000018),
	REG(PTP_CFG_MISC,			0x0000a0),
	REG(PTP_CLK_CFG_ADJ_CFG,		0x0000a4),
	REG(PTP_CLK_CFG_ADJ_FREQ,		0x0000a8),
पूर्ण;

अटल स्थिर u32 vsc9959_gcb_regmap[] = अणु
	REG(GCB_SOFT_RST,			0x000004),
पूर्ण;

अटल स्थिर u32 vsc9959_dev_gmii_regmap[] = अणु
	REG(DEV_CLOCK_CFG,			0x0),
	REG(DEV_PORT_MISC,			0x4),
	REG(DEV_EVENTS,				0x8),
	REG(DEV_EEE_CFG,			0xc),
	REG(DEV_RX_PATH_DELAY,			0x10),
	REG(DEV_TX_PATH_DELAY,			0x14),
	REG(DEV_PTP_PREDICT_CFG,		0x18),
	REG(DEV_MAC_ENA_CFG,			0x1c),
	REG(DEV_MAC_MODE_CFG,			0x20),
	REG(DEV_MAC_MAXLEN_CFG,			0x24),
	REG(DEV_MAC_TAGS_CFG,			0x28),
	REG(DEV_MAC_ADV_CHK_CFG,		0x2c),
	REG(DEV_MAC_IFG_CFG,			0x30),
	REG(DEV_MAC_HDX_CFG,			0x34),
	REG(DEV_MAC_DBG_CFG,			0x38),
	REG(DEV_MAC_FC_MAC_LOW_CFG,		0x3c),
	REG(DEV_MAC_FC_MAC_HIGH_CFG,		0x40),
	REG(DEV_MAC_STICKY,			0x44),
	REG_RESERVED(PCS1G_CFG),
	REG_RESERVED(PCS1G_MODE_CFG),
	REG_RESERVED(PCS1G_SD_CFG),
	REG_RESERVED(PCS1G_ANEG_CFG),
	REG_RESERVED(PCS1G_ANEG_NP_CFG),
	REG_RESERVED(PCS1G_LB_CFG),
	REG_RESERVED(PCS1G_DBG_CFG),
	REG_RESERVED(PCS1G_CDET_CFG),
	REG_RESERVED(PCS1G_ANEG_STATUS),
	REG_RESERVED(PCS1G_ANEG_NP_STATUS),
	REG_RESERVED(PCS1G_LINK_STATUS),
	REG_RESERVED(PCS1G_LINK_DOWN_CNT),
	REG_RESERVED(PCS1G_STICKY),
	REG_RESERVED(PCS1G_DEBUG_STATUS),
	REG_RESERVED(PCS1G_LPI_CFG),
	REG_RESERVED(PCS1G_LPI_WAKE_ERROR_CNT),
	REG_RESERVED(PCS1G_LPI_STATUS),
	REG_RESERVED(PCS1G_TSTPAT_MODE_CFG),
	REG_RESERVED(PCS1G_TSTPAT_STATUS),
	REG_RESERVED(DEV_PCS_FX100_CFG),
	REG_RESERVED(DEV_PCS_FX100_STATUS),
पूर्ण;

अटल स्थिर u32 *vsc9959_regmap[TARGET_MAX] = अणु
	[ANA]	= vsc9959_ana_regmap,
	[QS]	= vsc9959_qs_regmap,
	[QSYS]	= vsc9959_qsys_regmap,
	[REW]	= vsc9959_rew_regmap,
	[SYS]	= vsc9959_sys_regmap,
	[S0]	= vsc9959_vcap_regmap,
	[S1]	= vsc9959_vcap_regmap,
	[S2]	= vsc9959_vcap_regmap,
	[PTP]	= vsc9959_ptp_regmap,
	[GCB]	= vsc9959_gcb_regmap,
	[DEV_GMII] = vsc9959_dev_gmii_regmap,
पूर्ण;

/* Addresses are relative to the PCI device's base address */
अटल स्थिर काष्ठा resource vsc9959_target_io_res[TARGET_MAX] = अणु
	[ANA] = अणु
		.start	= 0x0280000,
		.end	= 0x028ffff,
		.name	= "ana",
	पूर्ण,
	[QS] = अणु
		.start	= 0x0080000,
		.end	= 0x00800ff,
		.name	= "qs",
	पूर्ण,
	[QSYS] = अणु
		.start	= 0x0200000,
		.end	= 0x021ffff,
		.name	= "qsys",
	पूर्ण,
	[REW] = अणु
		.start	= 0x0030000,
		.end	= 0x003ffff,
		.name	= "rew",
	पूर्ण,
	[SYS] = अणु
		.start	= 0x0010000,
		.end	= 0x001ffff,
		.name	= "sys",
	पूर्ण,
	[S0] = अणु
		.start	= 0x0040000,
		.end	= 0x00403ff,
		.name	= "s0",
	पूर्ण,
	[S1] = अणु
		.start	= 0x0050000,
		.end	= 0x00503ff,
		.name	= "s1",
	पूर्ण,
	[S2] = अणु
		.start	= 0x0060000,
		.end	= 0x00603ff,
		.name	= "s2",
	पूर्ण,
	[PTP] = अणु
		.start	= 0x0090000,
		.end	= 0x00900cb,
		.name	= "ptp",
	पूर्ण,
	[GCB] = अणु
		.start	= 0x0070000,
		.end	= 0x00701ff,
		.name	= "devcpu_gcb",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resource vsc9959_port_io_res[] = अणु
	अणु
		.start	= 0x0100000,
		.end	= 0x010ffff,
		.name	= "port0",
	पूर्ण,
	अणु
		.start	= 0x0110000,
		.end	= 0x011ffff,
		.name	= "port1",
	पूर्ण,
	अणु
		.start	= 0x0120000,
		.end	= 0x012ffff,
		.name	= "port2",
	पूर्ण,
	अणु
		.start	= 0x0130000,
		.end	= 0x013ffff,
		.name	= "port3",
	पूर्ण,
	अणु
		.start	= 0x0140000,
		.end	= 0x014ffff,
		.name	= "port4",
	पूर्ण,
	अणु
		.start	= 0x0150000,
		.end	= 0x015ffff,
		.name	= "port5",
	पूर्ण,
पूर्ण;

/* Port MAC 0 Internal MDIO bus through which the SerDes acting as an
 * SGMII/QSGMII MAC PCS can be found.
 */
अटल स्थिर काष्ठा resource vsc9959_imdio_res = अणु
	.start		= 0x8030,
	.end		= 0x8040,
	.name		= "imdio",
पूर्ण;

अटल स्थिर काष्ठा reg_field vsc9959_regfields[REGFIELD_MAX] = अणु
	[ANA_ADVLEARN_VLAN_CHK] = REG_FIELD(ANA_ADVLEARN, 6, 6),
	[ANA_ADVLEARN_LEARN_MIRROR] = REG_FIELD(ANA_ADVLEARN, 0, 5),
	[ANA_ANEVENTS_FLOOD_DISCARD] = REG_FIELD(ANA_ANEVENTS, 30, 30),
	[ANA_ANEVENTS_AUTOAGE] = REG_FIELD(ANA_ANEVENTS, 26, 26),
	[ANA_ANEVENTS_STORM_DROP] = REG_FIELD(ANA_ANEVENTS, 24, 24),
	[ANA_ANEVENTS_LEARN_DROP] = REG_FIELD(ANA_ANEVENTS, 23, 23),
	[ANA_ANEVENTS_AGED_ENTRY] = REG_FIELD(ANA_ANEVENTS, 22, 22),
	[ANA_ANEVENTS_CPU_LEARN_FAILED] = REG_FIELD(ANA_ANEVENTS, 21, 21),
	[ANA_ANEVENTS_AUTO_LEARN_FAILED] = REG_FIELD(ANA_ANEVENTS, 20, 20),
	[ANA_ANEVENTS_LEARN_REMOVE] = REG_FIELD(ANA_ANEVENTS, 19, 19),
	[ANA_ANEVENTS_AUTO_LEARNED] = REG_FIELD(ANA_ANEVENTS, 18, 18),
	[ANA_ANEVENTS_AUTO_MOVED] = REG_FIELD(ANA_ANEVENTS, 17, 17),
	[ANA_ANEVENTS_CLASSIFIED_DROP] = REG_FIELD(ANA_ANEVENTS, 15, 15),
	[ANA_ANEVENTS_CLASSIFIED_COPY] = REG_FIELD(ANA_ANEVENTS, 14, 14),
	[ANA_ANEVENTS_VLAN_DISCARD] = REG_FIELD(ANA_ANEVENTS, 13, 13),
	[ANA_ANEVENTS_FWD_DISCARD] = REG_FIELD(ANA_ANEVENTS, 12, 12),
	[ANA_ANEVENTS_MULTICAST_FLOOD] = REG_FIELD(ANA_ANEVENTS, 11, 11),
	[ANA_ANEVENTS_UNICAST_FLOOD] = REG_FIELD(ANA_ANEVENTS, 10, 10),
	[ANA_ANEVENTS_DEST_KNOWN] = REG_FIELD(ANA_ANEVENTS, 9, 9),
	[ANA_ANEVENTS_BUCKET3_MATCH] = REG_FIELD(ANA_ANEVENTS, 8, 8),
	[ANA_ANEVENTS_BUCKET2_MATCH] = REG_FIELD(ANA_ANEVENTS, 7, 7),
	[ANA_ANEVENTS_BUCKET1_MATCH] = REG_FIELD(ANA_ANEVENTS, 6, 6),
	[ANA_ANEVENTS_BUCKET0_MATCH] = REG_FIELD(ANA_ANEVENTS, 5, 5),
	[ANA_ANEVENTS_CPU_OPERATION] = REG_FIELD(ANA_ANEVENTS, 4, 4),
	[ANA_ANEVENTS_DMAC_LOOKUP] = REG_FIELD(ANA_ANEVENTS, 3, 3),
	[ANA_ANEVENTS_SMAC_LOOKUP] = REG_FIELD(ANA_ANEVENTS, 2, 2),
	[ANA_ANEVENTS_SEQ_GEN_ERR_0] = REG_FIELD(ANA_ANEVENTS, 1, 1),
	[ANA_ANEVENTS_SEQ_GEN_ERR_1] = REG_FIELD(ANA_ANEVENTS, 0, 0),
	[ANA_TABLES_MACACCESS_B_DOM] = REG_FIELD(ANA_TABLES_MACACCESS, 16, 16),
	[ANA_TABLES_MACTINDX_BUCKET] = REG_FIELD(ANA_TABLES_MACTINDX, 11, 12),
	[ANA_TABLES_MACTINDX_M_INDEX] = REG_FIELD(ANA_TABLES_MACTINDX, 0, 10),
	[SYS_RESET_CFG_CORE_ENA] = REG_FIELD(SYS_RESET_CFG, 0, 0),
	[GCB_SOFT_RST_SWC_RST] = REG_FIELD(GCB_SOFT_RST, 0, 0),
	/* Replicated per number of ports (7), रेजिस्टर size 4 per port */
	[QSYS_SWITCH_PORT_MODE_PORT_ENA] = REG_FIELD_ID(QSYS_SWITCH_PORT_MODE, 14, 14, 7, 4),
	[QSYS_SWITCH_PORT_MODE_SCH_NEXT_CFG] = REG_FIELD_ID(QSYS_SWITCH_PORT_MODE, 11, 13, 7, 4),
	[QSYS_SWITCH_PORT_MODE_YEL_RSRVD] = REG_FIELD_ID(QSYS_SWITCH_PORT_MODE, 10, 10, 7, 4),
	[QSYS_SWITCH_PORT_MODE_INGRESS_DROP_MODE] = REG_FIELD_ID(QSYS_SWITCH_PORT_MODE, 9, 9, 7, 4),
	[QSYS_SWITCH_PORT_MODE_TX_PFC_ENA] = REG_FIELD_ID(QSYS_SWITCH_PORT_MODE, 1, 8, 7, 4),
	[QSYS_SWITCH_PORT_MODE_TX_PFC_MODE] = REG_FIELD_ID(QSYS_SWITCH_PORT_MODE, 0, 0, 7, 4),
	[SYS_PORT_MODE_DATA_WO_TS] = REG_FIELD_ID(SYS_PORT_MODE, 5, 6, 7, 4),
	[SYS_PORT_MODE_INCL_INJ_HDR] = REG_FIELD_ID(SYS_PORT_MODE, 3, 4, 7, 4),
	[SYS_PORT_MODE_INCL_XTR_HDR] = REG_FIELD_ID(SYS_PORT_MODE, 1, 2, 7, 4),
	[SYS_PORT_MODE_INCL_HDR_ERR] = REG_FIELD_ID(SYS_PORT_MODE, 0, 0, 7, 4),
	[SYS_PAUSE_CFG_PAUSE_START] = REG_FIELD_ID(SYS_PAUSE_CFG, 10, 18, 7, 4),
	[SYS_PAUSE_CFG_PAUSE_STOP] = REG_FIELD_ID(SYS_PAUSE_CFG, 1, 9, 7, 4),
	[SYS_PAUSE_CFG_PAUSE_ENA] = REG_FIELD_ID(SYS_PAUSE_CFG, 0, 1, 7, 4),
पूर्ण;

अटल स्थिर काष्ठा ocelot_stat_layout vsc9959_stats_layout[] = अणु
	अणु .offset = 0x00,	.name = "rx_octets", पूर्ण,
	अणु .offset = 0x01,	.name = "rx_unicast", पूर्ण,
	अणु .offset = 0x02,	.name = "rx_multicast", पूर्ण,
	अणु .offset = 0x03,	.name = "rx_broadcast", पूर्ण,
	अणु .offset = 0x04,	.name = "rx_shorts", पूर्ण,
	अणु .offset = 0x05,	.name = "rx_fragments", पूर्ण,
	अणु .offset = 0x06,	.name = "rx_jabbers", पूर्ण,
	अणु .offset = 0x07,	.name = "rx_crc_align_errs", पूर्ण,
	अणु .offset = 0x08,	.name = "rx_sym_errs", पूर्ण,
	अणु .offset = 0x09,	.name = "rx_frames_below_65_octets", पूर्ण,
	अणु .offset = 0x0A,	.name = "rx_frames_65_to_127_octets", पूर्ण,
	अणु .offset = 0x0B,	.name = "rx_frames_128_to_255_octets", पूर्ण,
	अणु .offset = 0x0C,	.name = "rx_frames_256_to_511_octets", पूर्ण,
	अणु .offset = 0x0D,	.name = "rx_frames_512_to_1023_octets", पूर्ण,
	अणु .offset = 0x0E,	.name = "rx_frames_1024_to_1526_octets", पूर्ण,
	अणु .offset = 0x0F,	.name = "rx_frames_over_1526_octets", पूर्ण,
	अणु .offset = 0x10,	.name = "rx_pause", पूर्ण,
	अणु .offset = 0x11,	.name = "rx_control", पूर्ण,
	अणु .offset = 0x12,	.name = "rx_longs", पूर्ण,
	अणु .offset = 0x13,	.name = "rx_classified_drops", पूर्ण,
	अणु .offset = 0x14,	.name = "rx_red_prio_0", पूर्ण,
	अणु .offset = 0x15,	.name = "rx_red_prio_1", पूर्ण,
	अणु .offset = 0x16,	.name = "rx_red_prio_2", पूर्ण,
	अणु .offset = 0x17,	.name = "rx_red_prio_3", पूर्ण,
	अणु .offset = 0x18,	.name = "rx_red_prio_4", पूर्ण,
	अणु .offset = 0x19,	.name = "rx_red_prio_5", पूर्ण,
	अणु .offset = 0x1A,	.name = "rx_red_prio_6", पूर्ण,
	अणु .offset = 0x1B,	.name = "rx_red_prio_7", पूर्ण,
	अणु .offset = 0x1C,	.name = "rx_yellow_prio_0", पूर्ण,
	अणु .offset = 0x1D,	.name = "rx_yellow_prio_1", पूर्ण,
	अणु .offset = 0x1E,	.name = "rx_yellow_prio_2", पूर्ण,
	अणु .offset = 0x1F,	.name = "rx_yellow_prio_3", पूर्ण,
	अणु .offset = 0x20,	.name = "rx_yellow_prio_4", पूर्ण,
	अणु .offset = 0x21,	.name = "rx_yellow_prio_5", पूर्ण,
	अणु .offset = 0x22,	.name = "rx_yellow_prio_6", पूर्ण,
	अणु .offset = 0x23,	.name = "rx_yellow_prio_7", पूर्ण,
	अणु .offset = 0x24,	.name = "rx_green_prio_0", पूर्ण,
	अणु .offset = 0x25,	.name = "rx_green_prio_1", पूर्ण,
	अणु .offset = 0x26,	.name = "rx_green_prio_2", पूर्ण,
	अणु .offset = 0x27,	.name = "rx_green_prio_3", पूर्ण,
	अणु .offset = 0x28,	.name = "rx_green_prio_4", पूर्ण,
	अणु .offset = 0x29,	.name = "rx_green_prio_5", पूर्ण,
	अणु .offset = 0x2A,	.name = "rx_green_prio_6", पूर्ण,
	अणु .offset = 0x2B,	.name = "rx_green_prio_7", पूर्ण,
	अणु .offset = 0x80,	.name = "tx_octets", पूर्ण,
	अणु .offset = 0x81,	.name = "tx_unicast", पूर्ण,
	अणु .offset = 0x82,	.name = "tx_multicast", पूर्ण,
	अणु .offset = 0x83,	.name = "tx_broadcast", पूर्ण,
	अणु .offset = 0x84,	.name = "tx_collision", पूर्ण,
	अणु .offset = 0x85,	.name = "tx_drops", पूर्ण,
	अणु .offset = 0x86,	.name = "tx_pause", पूर्ण,
	अणु .offset = 0x87,	.name = "tx_frames_below_65_octets", पूर्ण,
	अणु .offset = 0x88,	.name = "tx_frames_65_to_127_octets", पूर्ण,
	अणु .offset = 0x89,	.name = "tx_frames_128_255_octets", पूर्ण,
	अणु .offset = 0x8B,	.name = "tx_frames_256_511_octets", पूर्ण,
	अणु .offset = 0x8C,	.name = "tx_frames_1024_1526_octets", पूर्ण,
	अणु .offset = 0x8D,	.name = "tx_frames_over_1526_octets", पूर्ण,
	अणु .offset = 0x8E,	.name = "tx_yellow_prio_0", पूर्ण,
	अणु .offset = 0x8F,	.name = "tx_yellow_prio_1", पूर्ण,
	अणु .offset = 0x90,	.name = "tx_yellow_prio_2", पूर्ण,
	अणु .offset = 0x91,	.name = "tx_yellow_prio_3", पूर्ण,
	अणु .offset = 0x92,	.name = "tx_yellow_prio_4", पूर्ण,
	अणु .offset = 0x93,	.name = "tx_yellow_prio_5", पूर्ण,
	अणु .offset = 0x94,	.name = "tx_yellow_prio_6", पूर्ण,
	अणु .offset = 0x95,	.name = "tx_yellow_prio_7", पूर्ण,
	अणु .offset = 0x96,	.name = "tx_green_prio_0", पूर्ण,
	अणु .offset = 0x97,	.name = "tx_green_prio_1", पूर्ण,
	अणु .offset = 0x98,	.name = "tx_green_prio_2", पूर्ण,
	अणु .offset = 0x99,	.name = "tx_green_prio_3", पूर्ण,
	अणु .offset = 0x9A,	.name = "tx_green_prio_4", पूर्ण,
	अणु .offset = 0x9B,	.name = "tx_green_prio_5", पूर्ण,
	अणु .offset = 0x9C,	.name = "tx_green_prio_6", पूर्ण,
	अणु .offset = 0x9D,	.name = "tx_green_prio_7", पूर्ण,
	अणु .offset = 0x9E,	.name = "tx_aged", पूर्ण,
	अणु .offset = 0x100,	.name = "drop_local", पूर्ण,
	अणु .offset = 0x101,	.name = "drop_tail", पूर्ण,
	अणु .offset = 0x102,	.name = "drop_yellow_prio_0", पूर्ण,
	अणु .offset = 0x103,	.name = "drop_yellow_prio_1", पूर्ण,
	अणु .offset = 0x104,	.name = "drop_yellow_prio_2", पूर्ण,
	अणु .offset = 0x105,	.name = "drop_yellow_prio_3", पूर्ण,
	अणु .offset = 0x106,	.name = "drop_yellow_prio_4", पूर्ण,
	अणु .offset = 0x107,	.name = "drop_yellow_prio_5", पूर्ण,
	अणु .offset = 0x108,	.name = "drop_yellow_prio_6", पूर्ण,
	अणु .offset = 0x109,	.name = "drop_yellow_prio_7", पूर्ण,
	अणु .offset = 0x10A,	.name = "drop_green_prio_0", पूर्ण,
	अणु .offset = 0x10B,	.name = "drop_green_prio_1", पूर्ण,
	अणु .offset = 0x10C,	.name = "drop_green_prio_2", पूर्ण,
	अणु .offset = 0x10D,	.name = "drop_green_prio_3", पूर्ण,
	अणु .offset = 0x10E,	.name = "drop_green_prio_4", पूर्ण,
	अणु .offset = 0x10F,	.name = "drop_green_prio_5", पूर्ण,
	अणु .offset = 0x110,	.name = "drop_green_prio_6", पूर्ण,
	अणु .offset = 0x111,	.name = "drop_green_prio_7", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vcap_field vsc9959_vcap_es0_keys[] = अणु
	[VCAP_ES0_EGR_PORT]			= अणु  0,  3पूर्ण,
	[VCAP_ES0_IGR_PORT]			= अणु  3,  3पूर्ण,
	[VCAP_ES0_RSV]				= अणु  6,  2पूर्ण,
	[VCAP_ES0_L2_MC]			= अणु  8,  1पूर्ण,
	[VCAP_ES0_L2_BC]			= अणु  9,  1पूर्ण,
	[VCAP_ES0_VID]				= अणु 10, 12पूर्ण,
	[VCAP_ES0_DP]				= अणु 22,  1पूर्ण,
	[VCAP_ES0_PCP]				= अणु 23,  3पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vcap_field vsc9959_vcap_es0_actions[] = अणु
	[VCAP_ES0_ACT_PUSH_OUTER_TAG]		= अणु  0,  2पूर्ण,
	[VCAP_ES0_ACT_PUSH_INNER_TAG]		= अणु  2,  1पूर्ण,
	[VCAP_ES0_ACT_TAG_A_TPID_SEL]		= अणु  3,  2पूर्ण,
	[VCAP_ES0_ACT_TAG_A_VID_SEL]		= अणु  5,  1पूर्ण,
	[VCAP_ES0_ACT_TAG_A_PCP_SEL]		= अणु  6,  2पूर्ण,
	[VCAP_ES0_ACT_TAG_A_DEI_SEL]		= अणु  8,  2पूर्ण,
	[VCAP_ES0_ACT_TAG_B_TPID_SEL]		= अणु 10,  2पूर्ण,
	[VCAP_ES0_ACT_TAG_B_VID_SEL]		= अणु 12,  1पूर्ण,
	[VCAP_ES0_ACT_TAG_B_PCP_SEL]		= अणु 13,  2पूर्ण,
	[VCAP_ES0_ACT_TAG_B_DEI_SEL]		= अणु 15,  2पूर्ण,
	[VCAP_ES0_ACT_VID_A_VAL]		= अणु 17, 12पूर्ण,
	[VCAP_ES0_ACT_PCP_A_VAL]		= अणु 29,  3पूर्ण,
	[VCAP_ES0_ACT_DEI_A_VAL]		= अणु 32,  1पूर्ण,
	[VCAP_ES0_ACT_VID_B_VAL]		= अणु 33, 12पूर्ण,
	[VCAP_ES0_ACT_PCP_B_VAL]		= अणु 45,  3पूर्ण,
	[VCAP_ES0_ACT_DEI_B_VAL]		= अणु 48,  1पूर्ण,
	[VCAP_ES0_ACT_RSV]			= अणु 49, 23पूर्ण,
	[VCAP_ES0_ACT_HIT_STICKY]		= अणु 72,  1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vcap_field vsc9959_vcap_is1_keys[] = अणु
	[VCAP_IS1_HK_TYPE]			= अणु  0,   1पूर्ण,
	[VCAP_IS1_HK_LOOKUP]			= अणु  1,   2पूर्ण,
	[VCAP_IS1_HK_IGR_PORT_MASK]		= अणु  3,   7पूर्ण,
	[VCAP_IS1_HK_RSV]			= अणु 10,   9पूर्ण,
	[VCAP_IS1_HK_OAM_Y1731]			= अणु 19,   1पूर्ण,
	[VCAP_IS1_HK_L2_MC]			= अणु 20,   1पूर्ण,
	[VCAP_IS1_HK_L2_BC]			= अणु 21,   1पूर्ण,
	[VCAP_IS1_HK_IP_MC]			= अणु 22,   1पूर्ण,
	[VCAP_IS1_HK_VLAN_TAGGED]		= अणु 23,   1पूर्ण,
	[VCAP_IS1_HK_VLAN_DBL_TAGGED]		= अणु 24,   1पूर्ण,
	[VCAP_IS1_HK_TPID]			= अणु 25,   1पूर्ण,
	[VCAP_IS1_HK_VID]			= अणु 26,  12पूर्ण,
	[VCAP_IS1_HK_DEI]			= अणु 38,   1पूर्ण,
	[VCAP_IS1_HK_PCP]			= अणु 39,   3पूर्ण,
	/* Specअगरic Fields क्रम IS1 Half Key S1_NORMAL */
	[VCAP_IS1_HK_L2_SMAC]			= अणु 42,  48पूर्ण,
	[VCAP_IS1_HK_ETYPE_LEN]			= अणु 90,   1पूर्ण,
	[VCAP_IS1_HK_ETYPE]			= अणु 91,  16पूर्ण,
	[VCAP_IS1_HK_IP_SNAP]			= अणु107,   1पूर्ण,
	[VCAP_IS1_HK_IP4]			= अणु108,   1पूर्ण,
	/* Layer-3 Inक्रमmation */
	[VCAP_IS1_HK_L3_FRAGMENT]		= अणु109,   1पूर्ण,
	[VCAP_IS1_HK_L3_FRAG_OFS_GT0]		= अणु110,   1पूर्ण,
	[VCAP_IS1_HK_L3_OPTIONS]		= अणु111,   1पूर्ण,
	[VCAP_IS1_HK_L3_DSCP]			= अणु112,   6पूर्ण,
	[VCAP_IS1_HK_L3_IP4_SIP]		= अणु118,  32पूर्ण,
	/* Layer-4 Inक्रमmation */
	[VCAP_IS1_HK_TCP_UDP]			= अणु150,   1पूर्ण,
	[VCAP_IS1_HK_TCP]			= अणु151,   1पूर्ण,
	[VCAP_IS1_HK_L4_SPORT]			= अणु152,  16पूर्ण,
	[VCAP_IS1_HK_L4_RNG]			= अणु168,   8पूर्ण,
	/* Specअगरic Fields क्रम IS1 Half Key S1_5TUPLE_IP4 */
	[VCAP_IS1_HK_IP4_INNER_TPID]            = अणु 42,   1पूर्ण,
	[VCAP_IS1_HK_IP4_INNER_VID]		= अणु 43,  12पूर्ण,
	[VCAP_IS1_HK_IP4_INNER_DEI]		= अणु 55,   1पूर्ण,
	[VCAP_IS1_HK_IP4_INNER_PCP]		= अणु 56,   3पूर्ण,
	[VCAP_IS1_HK_IP4_IP4]			= अणु 59,   1पूर्ण,
	[VCAP_IS1_HK_IP4_L3_FRAGMENT]		= अणु 60,   1पूर्ण,
	[VCAP_IS1_HK_IP4_L3_FRAG_OFS_GT0]	= अणु 61,   1पूर्ण,
	[VCAP_IS1_HK_IP4_L3_OPTIONS]		= अणु 62,   1पूर्ण,
	[VCAP_IS1_HK_IP4_L3_DSCP]		= अणु 63,   6पूर्ण,
	[VCAP_IS1_HK_IP4_L3_IP4_DIP]		= अणु 69,  32पूर्ण,
	[VCAP_IS1_HK_IP4_L3_IP4_SIP]		= अणु101,  32पूर्ण,
	[VCAP_IS1_HK_IP4_L3_PROTO]		= अणु133,   8पूर्ण,
	[VCAP_IS1_HK_IP4_TCP_UDP]		= अणु141,   1पूर्ण,
	[VCAP_IS1_HK_IP4_TCP]			= अणु142,   1पूर्ण,
	[VCAP_IS1_HK_IP4_L4_RNG]		= अणु143,   8पूर्ण,
	[VCAP_IS1_HK_IP4_IP_PAYLOAD_S1_5TUPLE]	= अणु151,  32पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vcap_field vsc9959_vcap_is1_actions[] = अणु
	[VCAP_IS1_ACT_DSCP_ENA]			= अणु  0,  1पूर्ण,
	[VCAP_IS1_ACT_DSCP_VAL]			= अणु  1,  6पूर्ण,
	[VCAP_IS1_ACT_QOS_ENA]			= अणु  7,  1पूर्ण,
	[VCAP_IS1_ACT_QOS_VAL]			= अणु  8,  3पूर्ण,
	[VCAP_IS1_ACT_DP_ENA]			= अणु 11,  1पूर्ण,
	[VCAP_IS1_ACT_DP_VAL]			= अणु 12,  1पूर्ण,
	[VCAP_IS1_ACT_PAG_OVERRIDE_MASK]	= अणु 13,  8पूर्ण,
	[VCAP_IS1_ACT_PAG_VAL]			= अणु 21,  8पूर्ण,
	[VCAP_IS1_ACT_RSV]			= अणु 29,  9पूर्ण,
	/* The fields below are incorrectly shअगरted by 2 in the manual */
	[VCAP_IS1_ACT_VID_REPLACE_ENA]		= अणु 38,  1पूर्ण,
	[VCAP_IS1_ACT_VID_ADD_VAL]		= अणु 39, 12पूर्ण,
	[VCAP_IS1_ACT_FID_SEL]			= अणु 51,  2पूर्ण,
	[VCAP_IS1_ACT_FID_VAL]			= अणु 53, 13पूर्ण,
	[VCAP_IS1_ACT_PCP_DEI_ENA]		= अणु 66,  1पूर्ण,
	[VCAP_IS1_ACT_PCP_VAL]			= अणु 67,  3पूर्ण,
	[VCAP_IS1_ACT_DEI_VAL]			= अणु 70,  1पूर्ण,
	[VCAP_IS1_ACT_VLAN_POP_CNT_ENA]		= अणु 71,  1पूर्ण,
	[VCAP_IS1_ACT_VLAN_POP_CNT]		= अणु 72,  2पूर्ण,
	[VCAP_IS1_ACT_CUSTOM_ACE_TYPE_ENA]	= अणु 74,  4पूर्ण,
	[VCAP_IS1_ACT_HIT_STICKY]		= अणु 78,  1पूर्ण,
पूर्ण;

अटल काष्ठा vcap_field vsc9959_vcap_is2_keys[] = अणु
	/* Common: 41 bits */
	[VCAP_IS2_TYPE]				= अणु  0,   4पूर्ण,
	[VCAP_IS2_HK_FIRST]			= अणु  4,   1पूर्ण,
	[VCAP_IS2_HK_PAG]			= अणु  5,   8पूर्ण,
	[VCAP_IS2_HK_IGR_PORT_MASK]		= अणु 13,   7पूर्ण,
	[VCAP_IS2_HK_RSV2]			= अणु 20,   1पूर्ण,
	[VCAP_IS2_HK_HOST_MATCH]		= अणु 21,   1पूर्ण,
	[VCAP_IS2_HK_L2_MC]			= अणु 22,   1पूर्ण,
	[VCAP_IS2_HK_L2_BC]			= अणु 23,   1पूर्ण,
	[VCAP_IS2_HK_VLAN_TAGGED]		= अणु 24,   1पूर्ण,
	[VCAP_IS2_HK_VID]			= अणु 25,  12पूर्ण,
	[VCAP_IS2_HK_DEI]			= अणु 37,   1पूर्ण,
	[VCAP_IS2_HK_PCP]			= अणु 38,   3पूर्ण,
	/* MAC_ETYPE / MAC_LLC / MAC_SNAP / OAM common */
	[VCAP_IS2_HK_L2_DMAC]			= अणु 41,  48पूर्ण,
	[VCAP_IS2_HK_L2_SMAC]			= अणु 89,  48पूर्ण,
	/* MAC_ETYPE (TYPE=000) */
	[VCAP_IS2_HK_MAC_ETYPE_ETYPE]		= अणु137,  16पूर्ण,
	[VCAP_IS2_HK_MAC_ETYPE_L2_PAYLOAD0]	= अणु153,  16पूर्ण,
	[VCAP_IS2_HK_MAC_ETYPE_L2_PAYLOAD1]	= अणु169,   8पूर्ण,
	[VCAP_IS2_HK_MAC_ETYPE_L2_PAYLOAD2]	= अणु177,   3पूर्ण,
	/* MAC_LLC (TYPE=001) */
	[VCAP_IS2_HK_MAC_LLC_L2_LLC]		= अणु137,  40पूर्ण,
	/* MAC_SNAP (TYPE=010) */
	[VCAP_IS2_HK_MAC_SNAP_L2_SNAP]		= अणु137,  40पूर्ण,
	/* MAC_ARP (TYPE=011) */
	[VCAP_IS2_HK_MAC_ARP_SMAC]		= अणु 41,  48पूर्ण,
	[VCAP_IS2_HK_MAC_ARP_ADDR_SPACE_OK]	= अणु 89,   1पूर्ण,
	[VCAP_IS2_HK_MAC_ARP_PROTO_SPACE_OK]	= अणु 90,   1पूर्ण,
	[VCAP_IS2_HK_MAC_ARP_LEN_OK]		= अणु 91,   1पूर्ण,
	[VCAP_IS2_HK_MAC_ARP_TARGET_MATCH]	= अणु 92,   1पूर्ण,
	[VCAP_IS2_HK_MAC_ARP_SENDER_MATCH]	= अणु 93,   1पूर्ण,
	[VCAP_IS2_HK_MAC_ARP_OPCODE_UNKNOWN]	= अणु 94,   1पूर्ण,
	[VCAP_IS2_HK_MAC_ARP_OPCODE]		= अणु 95,   2पूर्ण,
	[VCAP_IS2_HK_MAC_ARP_L3_IP4_DIP]	= अणु 97,  32पूर्ण,
	[VCAP_IS2_HK_MAC_ARP_L3_IP4_SIP]	= अणु129,  32पूर्ण,
	[VCAP_IS2_HK_MAC_ARP_DIP_EQ_SIP]	= अणु161,   1पूर्ण,
	/* IP4_TCP_UDP / IP4_OTHER common */
	[VCAP_IS2_HK_IP4]			= अणु 41,   1पूर्ण,
	[VCAP_IS2_HK_L3_FRAGMENT]		= अणु 42,   1पूर्ण,
	[VCAP_IS2_HK_L3_FRAG_OFS_GT0]		= अणु 43,   1पूर्ण,
	[VCAP_IS2_HK_L3_OPTIONS]		= अणु 44,   1पूर्ण,
	[VCAP_IS2_HK_IP4_L3_TTL_GT0]		= अणु 45,   1पूर्ण,
	[VCAP_IS2_HK_L3_TOS]			= अणु 46,   8पूर्ण,
	[VCAP_IS2_HK_L3_IP4_DIP]		= अणु 54,  32पूर्ण,
	[VCAP_IS2_HK_L3_IP4_SIP]		= अणु 86,  32पूर्ण,
	[VCAP_IS2_HK_DIP_EQ_SIP]		= अणु118,   1पूर्ण,
	/* IP4_TCP_UDP (TYPE=100) */
	[VCAP_IS2_HK_TCP]			= अणु119,   1पूर्ण,
	[VCAP_IS2_HK_L4_DPORT]			= अणु120,  16पूर्ण,
	[VCAP_IS2_HK_L4_SPORT]			= अणु136,  16पूर्ण,
	[VCAP_IS2_HK_L4_RNG]			= अणु152,   8पूर्ण,
	[VCAP_IS2_HK_L4_SPORT_EQ_DPORT]		= अणु160,   1पूर्ण,
	[VCAP_IS2_HK_L4_SEQUENCE_EQ0]		= अणु161,   1पूर्ण,
	[VCAP_IS2_HK_L4_FIN]			= अणु162,   1पूर्ण,
	[VCAP_IS2_HK_L4_SYN]			= अणु163,   1पूर्ण,
	[VCAP_IS2_HK_L4_RST]			= अणु164,   1पूर्ण,
	[VCAP_IS2_HK_L4_PSH]			= अणु165,   1पूर्ण,
	[VCAP_IS2_HK_L4_ACK]			= अणु166,   1पूर्ण,
	[VCAP_IS2_HK_L4_URG]			= अणु167,   1पूर्ण,
	[VCAP_IS2_HK_L4_1588_DOM]		= अणु168,   8पूर्ण,
	[VCAP_IS2_HK_L4_1588_VER]		= अणु176,   4पूर्ण,
	/* IP4_OTHER (TYPE=101) */
	[VCAP_IS2_HK_IP4_L3_PROTO]		= अणु119,   8पूर्ण,
	[VCAP_IS2_HK_L3_PAYLOAD]		= अणु127,  56पूर्ण,
	/* IP6_STD (TYPE=110) */
	[VCAP_IS2_HK_IP6_L3_TTL_GT0]		= अणु 41,   1पूर्ण,
	[VCAP_IS2_HK_L3_IP6_SIP]		= अणु 42, 128पूर्ण,
	[VCAP_IS2_HK_IP6_L3_PROTO]		= अणु170,   8पूर्ण,
	/* OAM (TYPE=111) */
	[VCAP_IS2_HK_OAM_MEL_FLAGS]		= अणु137,   7पूर्ण,
	[VCAP_IS2_HK_OAM_VER]			= अणु144,   5पूर्ण,
	[VCAP_IS2_HK_OAM_OPCODE]		= अणु149,   8पूर्ण,
	[VCAP_IS2_HK_OAM_FLAGS]			= अणु157,   8पूर्ण,
	[VCAP_IS2_HK_OAM_MEPID]			= अणु165,  16पूर्ण,
	[VCAP_IS2_HK_OAM_CCM_CNTS_EQ0]		= अणु181,   1पूर्ण,
	[VCAP_IS2_HK_OAM_IS_Y1731]		= अणु182,   1पूर्ण,
पूर्ण;

अटल काष्ठा vcap_field vsc9959_vcap_is2_actions[] = अणु
	[VCAP_IS2_ACT_HIT_ME_ONCE]		= अणु  0,  1पूर्ण,
	[VCAP_IS2_ACT_CPU_COPY_ENA]		= अणु  1,  1पूर्ण,
	[VCAP_IS2_ACT_CPU_QU_NUM]		= अणु  2,  3पूर्ण,
	[VCAP_IS2_ACT_MASK_MODE]		= अणु  5,  2पूर्ण,
	[VCAP_IS2_ACT_MIRROR_ENA]		= अणु  7,  1पूर्ण,
	[VCAP_IS2_ACT_LRN_DIS]			= अणु  8,  1पूर्ण,
	[VCAP_IS2_ACT_POLICE_ENA]		= अणु  9,  1पूर्ण,
	[VCAP_IS2_ACT_POLICE_IDX]		= अणु 10,  9पूर्ण,
	[VCAP_IS2_ACT_POLICE_VCAP_ONLY]		= अणु 19,  1पूर्ण,
	[VCAP_IS2_ACT_PORT_MASK]		= अणु 20,  6पूर्ण,
	[VCAP_IS2_ACT_REW_OP]			= अणु 26,  9पूर्ण,
	[VCAP_IS2_ACT_SMAC_REPLACE_ENA]		= अणु 35,  1पूर्ण,
	[VCAP_IS2_ACT_RSV]			= अणु 36,  2पूर्ण,
	[VCAP_IS2_ACT_ACL_ID]			= अणु 38,  6पूर्ण,
	[VCAP_IS2_ACT_HIT_CNT]			= अणु 44, 32पूर्ण,
पूर्ण;

अटल काष्ठा vcap_props vsc9959_vcap_props[] = अणु
	[VCAP_ES0] = अणु
		.action_type_width = 0,
		.action_table = अणु
			[ES0_ACTION_TYPE_NORMAL] = अणु
				.width = 72, /* HIT_STICKY not included */
				.count = 1,
			पूर्ण,
		पूर्ण,
		.target = S0,
		.keys = vsc9959_vcap_es0_keys,
		.actions = vsc9959_vcap_es0_actions,
	पूर्ण,
	[VCAP_IS1] = अणु
		.action_type_width = 0,
		.action_table = अणु
			[IS1_ACTION_TYPE_NORMAL] = अणु
				.width = 78, /* HIT_STICKY not included */
				.count = 4,
			पूर्ण,
		पूर्ण,
		.target = S1,
		.keys = vsc9959_vcap_is1_keys,
		.actions = vsc9959_vcap_is1_actions,
	पूर्ण,
	[VCAP_IS2] = अणु
		.action_type_width = 1,
		.action_table = अणु
			[IS2_ACTION_TYPE_NORMAL] = अणु
				.width = 44,
				.count = 2
			पूर्ण,
			[IS2_ACTION_TYPE_SMAC_SIP] = अणु
				.width = 6,
				.count = 4
			पूर्ण,
		पूर्ण,
		.target = S2,
		.keys = vsc9959_vcap_is2_keys,
		.actions = vsc9959_vcap_is2_actions,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ptp_घड़ी_info vsc9959_ptp_caps = अणु
	.owner		= THIS_MODULE,
	.name		= "felix ptp",
	.max_adj	= 0x7fffffff,
	.n_alarm	= 0,
	.n_ext_ts	= 0,
	.n_per_out	= OCELOT_PTP_PINS_NUM,
	.n_pins		= OCELOT_PTP_PINS_NUM,
	.pps		= 0,
	.समय_लो64	= ocelot_ptp_समय_लो64,
	.समय_रखो64	= ocelot_ptp_समय_रखो64,
	.adjसमय	= ocelot_ptp_adjसमय,
	.adjfine	= ocelot_ptp_adjfine,
	.verअगरy		= ocelot_ptp_verअगरy,
	.enable		= ocelot_ptp_enable,
पूर्ण;

#घोषणा VSC9959_INIT_TIMEOUT			50000
#घोषणा VSC9959_GCB_RST_SLEEP			100
#घोषणा VSC9959_SYS_RAMINIT_SLEEP		80

अटल पूर्णांक vsc9959_gcb_soft_rst_status(काष्ठा ocelot *ocelot)
अणु
	पूर्णांक val;

	ocelot_field_पढ़ो(ocelot, GCB_SOFT_RST_SWC_RST, &val);

	वापस val;
पूर्ण

अटल पूर्णांक vsc9959_sys_ram_init_status(काष्ठा ocelot *ocelot)
अणु
	वापस ocelot_पढ़ो(ocelot, SYS_RAM_INIT);
पूर्ण

/* CORE_ENA is in SYS:SYSTEM:RESET_CFG
 * RAM_INIT is in SYS:RAM_CTRL:RAM_INIT
 */
अटल पूर्णांक vsc9959_reset(काष्ठा ocelot *ocelot)
अणु
	पूर्णांक val, err;

	/* soft-reset the चयन core */
	ocelot_field_ग_लिखो(ocelot, GCB_SOFT_RST_SWC_RST, 1);

	err = पढ़ोx_poll_समयout(vsc9959_gcb_soft_rst_status, ocelot, val, !val,
				 VSC9959_GCB_RST_SLEEP, VSC9959_INIT_TIMEOUT);
	अगर (err) अणु
		dev_err(ocelot->dev, "timeout: switch core reset\n");
		वापस err;
	पूर्ण

	/* initialize चयन mem ~40us */
	ocelot_ग_लिखो(ocelot, SYS_RAM_INIT_RAM_INIT, SYS_RAM_INIT);
	err = पढ़ोx_poll_समयout(vsc9959_sys_ram_init_status, ocelot, val, !val,
				 VSC9959_SYS_RAMINIT_SLEEP,
				 VSC9959_INIT_TIMEOUT);
	अगर (err) अणु
		dev_err(ocelot->dev, "timeout: switch sram init\n");
		वापस err;
	पूर्ण

	/* enable चयन core */
	ocelot_field_ग_लिखो(ocelot, SYS_RESET_CFG_CORE_ENA, 1);

	वापस 0;
पूर्ण

अटल व्योम vsc9959_phylink_validate(काष्ठा ocelot *ocelot, पूर्णांक port,
				     अचिन्हित दीर्घ *supported,
				     काष्ठा phylink_link_state *state)
अणु
	काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];
	__ETHTOOL_DECLARE_LINK_MODE_MASK(mask) = अणु 0, पूर्ण;

	अगर (state->पूर्णांकerface != PHY_INTERFACE_MODE_NA &&
	    state->पूर्णांकerface != ocelot_port->phy_mode) अणु
		biपंचांगap_zero(supported, __ETHTOOL_LINK_MODE_MASK_NBITS);
		वापस;
	पूर्ण

	phylink_set_port_modes(mask);
	phylink_set(mask, Autoneg);
	phylink_set(mask, Pause);
	phylink_set(mask, Asym_Pause);
	phylink_set(mask, 10baseT_Half);
	phylink_set(mask, 10baseT_Full);
	phylink_set(mask, 100baseT_Half);
	phylink_set(mask, 100baseT_Full);
	phylink_set(mask, 1000baseT_Half);
	phylink_set(mask, 1000baseT_Full);

	अगर (state->पूर्णांकerface == PHY_INTERFACE_MODE_INTERNAL ||
	    state->पूर्णांकerface == PHY_INTERFACE_MODE_2500BASEX ||
	    state->पूर्णांकerface == PHY_INTERFACE_MODE_USXGMII) अणु
		phylink_set(mask, 2500baseT_Full);
		phylink_set(mask, 2500baseX_Full);
	पूर्ण

	biपंचांगap_and(supported, supported, mask,
		   __ETHTOOL_LINK_MODE_MASK_NBITS);
	biपंचांगap_and(state->advertising, state->advertising, mask,
		   __ETHTOOL_LINK_MODE_MASK_NBITS);
पूर्ण

अटल पूर्णांक vsc9959_prevalidate_phy_mode(काष्ठा ocelot *ocelot, पूर्णांक port,
					phy_पूर्णांकerface_t phy_mode)
अणु
	चयन (phy_mode) अणु
	हाल PHY_INTERFACE_MODE_INTERNAL:
		अगर (port != 4 && port != 5)
			वापस -ENOTSUPP;
		वापस 0;
	हाल PHY_INTERFACE_MODE_SGMII:
	हाल PHY_INTERFACE_MODE_QSGMII:
	हाल PHY_INTERFACE_MODE_USXGMII:
	हाल PHY_INTERFACE_MODE_2500BASEX:
		/* Not supported on पूर्णांकernal to-CPU ports */
		अगर (port == 4 || port == 5)
			वापस -ENOTSUPP;
		वापस 0;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

/* Watermark encode
 * Bit 8:   Unit; 0:1, 1:16
 * Bit 7-0: Value to be multiplied with unit
 */
अटल u16 vsc9959_wm_enc(u16 value)
अणु
	WARN_ON(value >= 16 * BIT(8));

	अगर (value >= BIT(8))
		वापस BIT(8) | (value / 16);

	वापस value;
पूर्ण

अटल u16 vsc9959_wm_dec(u16 wm)
अणु
	WARN_ON(wm & ~GENMASK(8, 0));

	अगर (wm & BIT(8))
		वापस (wm & GENMASK(7, 0)) * 16;

	वापस wm;
पूर्ण

अटल व्योम vsc9959_wm_stat(u32 val, u32 *inuse, u32 *maxuse)
अणु
	*inuse = (val & GENMASK(23, 12)) >> 12;
	*maxuse = val & GENMASK(11, 0);
पूर्ण

अटल स्थिर काष्ठा ocelot_ops vsc9959_ops = अणु
	.reset			= vsc9959_reset,
	.wm_enc			= vsc9959_wm_enc,
	.wm_dec			= vsc9959_wm_dec,
	.wm_stat		= vsc9959_wm_stat,
	.port_to_netdev		= felix_port_to_netdev,
	.netdev_to_port		= felix_netdev_to_port,
पूर्ण;

अटल पूर्णांक vsc9959_mdio_bus_alloc(काष्ठा ocelot *ocelot)
अणु
	काष्ठा felix *felix = ocelot_to_felix(ocelot);
	काष्ठा enetc_mdio_priv *mdio_priv;
	काष्ठा device *dev = ocelot->dev;
	व्योम __iomem *imdio_regs;
	काष्ठा resource res;
	काष्ठा enetc_hw *hw;
	काष्ठा mii_bus *bus;
	पूर्णांक port;
	पूर्णांक rc;

	felix->pcs = devm_kसुस्मृति(dev, felix->info->num_ports,
				  माप(काष्ठा lynx_pcs *),
				  GFP_KERNEL);
	अगर (!felix->pcs) अणु
		dev_err(dev, "failed to allocate array for PCS PHYs\n");
		वापस -ENOMEM;
	पूर्ण

	स_नकल(&res, felix->info->imdio_res, माप(res));
	res.flags = IORESOURCE_MEM;
	res.start += felix->imdio_base;
	res.end += felix->imdio_base;

	imdio_regs = devm_ioremap_resource(dev, &res);
	अगर (IS_ERR(imdio_regs))
		वापस PTR_ERR(imdio_regs);

	hw = enetc_hw_alloc(dev, imdio_regs);
	अगर (IS_ERR(hw)) अणु
		dev_err(dev, "failed to allocate ENETC HW structure\n");
		वापस PTR_ERR(hw);
	पूर्ण

	bus = devm_mdiobus_alloc_size(dev, माप(*mdio_priv));
	अगर (!bus)
		वापस -ENOMEM;

	bus->name = "VSC9959 internal MDIO bus";
	bus->पढ़ो = enetc_mdio_पढ़ो;
	bus->ग_लिखो = enetc_mdio_ग_लिखो;
	bus->parent = dev;
	mdio_priv = bus->priv;
	mdio_priv->hw = hw;
	/* This माला_लो added to imdio_regs, which alपढ़ोy maps addresses
	 * starting with the proper offset.
	 */
	mdio_priv->mdio_base = 0;
	snम_लिखो(bus->id, MII_BUS_ID_SIZE, "%s-imdio", dev_name(dev));

	/* Needed in order to initialize the bus mutex lock */
	rc = mdiobus_रेजिस्टर(bus);
	अगर (rc < 0) अणु
		dev_err(dev, "failed to register MDIO bus\n");
		वापस rc;
	पूर्ण

	felix->imdio = bus;

	क्रम (port = 0; port < felix->info->num_ports; port++) अणु
		काष्ठा ocelot_port *ocelot_port = ocelot->ports[port];
		काष्ठा mdio_device *pcs;
		काष्ठा lynx_pcs *lynx;

		अगर (dsa_is_unused_port(felix->ds, port))
			जारी;

		अगर (ocelot_port->phy_mode == PHY_INTERFACE_MODE_INTERNAL)
			जारी;

		pcs = mdio_device_create(felix->imdio, port);
		अगर (IS_ERR(pcs))
			जारी;

		lynx = lynx_pcs_create(pcs);
		अगर (!lynx) अणु
			mdio_device_मुक्त(pcs);
			जारी;
		पूर्ण

		felix->pcs[port] = lynx;

		dev_info(dev, "Found PCS at internal MDIO address %d\n", port);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vsc9959_mdio_bus_मुक्त(काष्ठा ocelot *ocelot)
अणु
	काष्ठा felix *felix = ocelot_to_felix(ocelot);
	पूर्णांक port;

	क्रम (port = 0; port < ocelot->num_phys_ports; port++) अणु
		काष्ठा lynx_pcs *pcs = felix->pcs[port];

		अगर (!pcs)
			जारी;

		mdio_device_मुक्त(pcs->mdio);
		lynx_pcs_destroy(pcs);
	पूर्ण
	mdiobus_unरेजिस्टर(felix->imdio);
पूर्ण

अटल व्योम vsc9959_sched_speed_set(काष्ठा ocelot *ocelot, पूर्णांक port,
				    u32 speed)
अणु
	u8 tas_speed;

	चयन (speed) अणु
	हाल SPEED_10:
		tas_speed = OCELOT_SPEED_10;
		अवरोध;
	हाल SPEED_100:
		tas_speed = OCELOT_SPEED_100;
		अवरोध;
	हाल SPEED_1000:
		tas_speed = OCELOT_SPEED_1000;
		अवरोध;
	हाल SPEED_2500:
		tas_speed = OCELOT_SPEED_2500;
		अवरोध;
	शेष:
		tas_speed = OCELOT_SPEED_1000;
		अवरोध;
	पूर्ण

	ocelot_rmw_rix(ocelot,
		       QSYS_TAG_CONFIG_LINK_SPEED(tas_speed),
		       QSYS_TAG_CONFIG_LINK_SPEED_M,
		       QSYS_TAG_CONFIG, port);
पूर्ण

अटल व्योम vsc9959_new_base_समय(काष्ठा ocelot *ocelot, kसमय_प्रकार base_समय,
				  u64 cycle_समय,
				  काष्ठा बारpec64 *new_base_ts)
अणु
	काष्ठा बारpec64 ts;
	kसमय_प्रकार new_base_समय;
	kसमय_प्रकार current_समय;

	ocelot_ptp_समय_लो64(&ocelot->ptp_info, &ts);
	current_समय = बारpec64_to_kसमय(ts);
	new_base_समय = base_समय;

	अगर (base_समय < current_समय) अणु
		u64 nr_of_cycles = current_समय - base_समय;

		करो_भाग(nr_of_cycles, cycle_समय);
		new_base_समय += cycle_समय * (nr_of_cycles + 1);
	पूर्ण

	*new_base_ts = kसमय_प्रकारo_बारpec64(new_base_समय);
पूर्ण

अटल u32 vsc9959_tas_पढ़ो_cfg_status(काष्ठा ocelot *ocelot)
अणु
	वापस ocelot_पढ़ो(ocelot, QSYS_TAS_PARAM_CFG_CTRL);
पूर्ण

अटल व्योम vsc9959_tas_gcl_set(काष्ठा ocelot *ocelot, स्थिर u32 gcl_ix,
				काष्ठा tc_taprio_sched_entry *entry)
अणु
	ocelot_ग_लिखो(ocelot,
		     QSYS_GCL_CFG_REG_1_GCL_ENTRY_NUM(gcl_ix) |
		     QSYS_GCL_CFG_REG_1_GATE_STATE(entry->gate_mask),
		     QSYS_GCL_CFG_REG_1);
	ocelot_ग_लिखो(ocelot, entry->पूर्णांकerval, QSYS_GCL_CFG_REG_2);
पूर्ण

अटल पूर्णांक vsc9959_qos_port_tas_set(काष्ठा ocelot *ocelot, पूर्णांक port,
				    काष्ठा tc_taprio_qopt_offload *taprio)
अणु
	काष्ठा बारpec64 base_ts;
	पूर्णांक ret, i;
	u32 val;

	अगर (!taprio->enable) अणु
		ocelot_rmw_rix(ocelot,
			       QSYS_TAG_CONFIG_INIT_GATE_STATE(0xFF),
			       QSYS_TAG_CONFIG_ENABLE |
			       QSYS_TAG_CONFIG_INIT_GATE_STATE_M,
			       QSYS_TAG_CONFIG, port);

		वापस 0;
	पूर्ण

	अगर (taprio->cycle_समय > NSEC_PER_SEC ||
	    taprio->cycle_समय_extension >= NSEC_PER_SEC)
		वापस -EINVAL;

	अगर (taprio->num_entries > VSC9959_TAS_GCL_ENTRY_MAX)
		वापस -दुस्फल;

	/* Enable guard band. The चयन will schedule frames without taking
	 * their length पूर्णांकo account. Thus we'll always need to enable the
	 * guard band which reserves the समय of a maximum sized frame at the
	 * end of the समय winकरोw.
	 *
	 * Although the ALWAYS_GUARD_BAND_SCH_Q bit is global क्रम all ports, we
	 * need to set PORT_NUM, because subsequent ग_लिखोs to PARAM_CFG_REG_n
	 * operate on the port number.
	 */
	ocelot_rmw(ocelot, QSYS_TAS_PARAM_CFG_CTRL_PORT_NUM(port) |
		   QSYS_TAS_PARAM_CFG_CTRL_ALWAYS_GUARD_BAND_SCH_Q,
		   QSYS_TAS_PARAM_CFG_CTRL_PORT_NUM_M |
		   QSYS_TAS_PARAM_CFG_CTRL_ALWAYS_GUARD_BAND_SCH_Q,
		   QSYS_TAS_PARAM_CFG_CTRL);

	/* Hardware errata -  Admin config could not be overwritten अगर
	 * config is pending, need reset the TAS module
	 */
	val = ocelot_पढ़ो(ocelot, QSYS_PARAM_STATUS_REG_8);
	अगर (val & QSYS_PARAM_STATUS_REG_8_CONFIG_PENDING)
		वापस  -EBUSY;

	ocelot_rmw_rix(ocelot,
		       QSYS_TAG_CONFIG_ENABLE |
		       QSYS_TAG_CONFIG_INIT_GATE_STATE(0xFF) |
		       QSYS_TAG_CONFIG_SCH_TRAFFIC_QUEUES(0xFF),
		       QSYS_TAG_CONFIG_ENABLE |
		       QSYS_TAG_CONFIG_INIT_GATE_STATE_M |
		       QSYS_TAG_CONFIG_SCH_TRAFFIC_QUEUES_M,
		       QSYS_TAG_CONFIG, port);

	vsc9959_new_base_समय(ocelot, taprio->base_समय,
			      taprio->cycle_समय, &base_ts);
	ocelot_ग_लिखो(ocelot, base_ts.tv_nsec, QSYS_PARAM_CFG_REG_1);
	ocelot_ग_लिखो(ocelot, lower_32_bits(base_ts.tv_sec), QSYS_PARAM_CFG_REG_2);
	val = upper_32_bits(base_ts.tv_sec);
	ocelot_ग_लिखो(ocelot,
		     QSYS_PARAM_CFG_REG_3_BASE_TIME_SEC_MSB(val) |
		     QSYS_PARAM_CFG_REG_3_LIST_LENGTH(taprio->num_entries),
		     QSYS_PARAM_CFG_REG_3);
	ocelot_ग_लिखो(ocelot, taprio->cycle_समय, QSYS_PARAM_CFG_REG_4);
	ocelot_ग_लिखो(ocelot, taprio->cycle_समय_extension, QSYS_PARAM_CFG_REG_5);

	क्रम (i = 0; i < taprio->num_entries; i++)
		vsc9959_tas_gcl_set(ocelot, i, &taprio->entries[i]);

	ocelot_rmw(ocelot, QSYS_TAS_PARAM_CFG_CTRL_CONFIG_CHANGE,
		   QSYS_TAS_PARAM_CFG_CTRL_CONFIG_CHANGE,
		   QSYS_TAS_PARAM_CFG_CTRL);

	ret = पढ़ोx_poll_समयout(vsc9959_tas_पढ़ो_cfg_status, ocelot, val,
				 !(val & QSYS_TAS_PARAM_CFG_CTRL_CONFIG_CHANGE),
				 10, 100000);

	वापस ret;
पूर्ण

अटल पूर्णांक vsc9959_qos_port_cbs_set(काष्ठा dsa_चयन *ds, पूर्णांक port,
				    काष्ठा tc_cbs_qopt_offload *cbs_qopt)
अणु
	काष्ठा ocelot *ocelot = ds->priv;
	पूर्णांक port_ix = port * 8 + cbs_qopt->queue;
	u32 rate, burst;

	अगर (cbs_qopt->queue >= ds->num_tx_queues)
		वापस -EINVAL;

	अगर (!cbs_qopt->enable) अणु
		ocelot_ग_लिखो_gix(ocelot, QSYS_CIR_CFG_CIR_RATE(0) |
				 QSYS_CIR_CFG_CIR_BURST(0),
				 QSYS_CIR_CFG, port_ix);

		ocelot_rmw_gix(ocelot, 0, QSYS_SE_CFG_SE_AVB_ENA,
			       QSYS_SE_CFG, port_ix);

		वापस 0;
	पूर्ण

	/* Rate unit is 100 kbps */
	rate = DIV_ROUND_UP(cbs_qopt->idleslope, 100);
	/* Aव्योम using zero rate */
	rate = clamp_t(u32, rate, 1, GENMASK(14, 0));
	/* Burst unit is 4kB */
	burst = DIV_ROUND_UP(cbs_qopt->hicredit, 4096);
	/* Aव्योम using zero burst size */
	burst = clamp_t(u32, burst, 1, GENMASK(5, 0));
	ocelot_ग_लिखो_gix(ocelot,
			 QSYS_CIR_CFG_CIR_RATE(rate) |
			 QSYS_CIR_CFG_CIR_BURST(burst),
			 QSYS_CIR_CFG,
			 port_ix);

	ocelot_rmw_gix(ocelot,
		       QSYS_SE_CFG_SE_FRM_MODE(0) |
		       QSYS_SE_CFG_SE_AVB_ENA,
		       QSYS_SE_CFG_SE_AVB_ENA |
		       QSYS_SE_CFG_SE_FRM_MODE_M,
		       QSYS_SE_CFG,
		       port_ix);

	वापस 0;
पूर्ण

अटल पूर्णांक vsc9959_port_setup_tc(काष्ठा dsa_चयन *ds, पूर्णांक port,
				 क्रमागत tc_setup_type type,
				 व्योम *type_data)
अणु
	काष्ठा ocelot *ocelot = ds->priv;

	चयन (type) अणु
	हाल TC_SETUP_QDISC_TAPRIO:
		वापस vsc9959_qos_port_tas_set(ocelot, port, type_data);
	हाल TC_SETUP_QDISC_CBS:
		वापस vsc9959_qos_port_cbs_set(ds, port, type_data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा felix_info felix_info_vsc9959 = अणु
	.target_io_res		= vsc9959_target_io_res,
	.port_io_res		= vsc9959_port_io_res,
	.imdio_res		= &vsc9959_imdio_res,
	.regfields		= vsc9959_regfields,
	.map			= vsc9959_regmap,
	.ops			= &vsc9959_ops,
	.stats_layout		= vsc9959_stats_layout,
	.num_stats		= ARRAY_SIZE(vsc9959_stats_layout),
	.vcap			= vsc9959_vcap_props,
	.num_mact_rows		= 2048,
	.num_ports		= 6,
	.num_tx_queues		= OCELOT_NUM_TC,
	.चयन_pci_bar		= 4,
	.imdio_pci_bar		= 0,
	.quirk_no_xtr_irq	= true,
	.ptp_caps		= &vsc9959_ptp_caps,
	.mdio_bus_alloc		= vsc9959_mdio_bus_alloc,
	.mdio_bus_मुक्त		= vsc9959_mdio_bus_मुक्त,
	.phylink_validate	= vsc9959_phylink_validate,
	.prevalidate_phy_mode	= vsc9959_prevalidate_phy_mode,
	.port_setup_tc		= vsc9959_port_setup_tc,
	.port_sched_speed_set	= vsc9959_sched_speed_set,
पूर्ण;

अटल irqवापस_t felix_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ocelot *ocelot = (काष्ठा ocelot *)data;

	/* The INTB पूर्णांकerrupt is used क्रम both PTP TX बारtamp पूर्णांकerrupt
	 * and preemption status change पूर्णांकerrupt on each port.
	 *
	 * - Get txtstamp अगर have
	 * - TODO: handle preemption. Without handling it, driver may get
	 *   पूर्णांकerrupt storm.
	 */

	ocelot_get_txtstamp(ocelot);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक felix_pci_probe(काष्ठा pci_dev *pdev,
			   स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा dsa_चयन *ds;
	काष्ठा ocelot *ocelot;
	काष्ठा felix *felix;
	पूर्णांक err;

	अगर (pdev->dev.of_node && !of_device_is_available(pdev->dev.of_node)) अणु
		dev_info(&pdev->dev, "device is disabled, skipping\n");
		वापस -ENODEV;
	पूर्ण

	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "device enable failed\n");
		जाओ err_pci_enable;
	पूर्ण

	felix = kzalloc(माप(काष्ठा felix), GFP_KERNEL);
	अगर (!felix) अणु
		err = -ENOMEM;
		dev_err(&pdev->dev, "Failed to allocate driver memory\n");
		जाओ err_alloc_felix;
	पूर्ण

	pci_set_drvdata(pdev, felix);
	ocelot = &felix->ocelot;
	ocelot->dev = &pdev->dev;
	ocelot->num_flooding_pgids = OCELOT_NUM_TC;
	felix->info = &felix_info_vsc9959;
	felix->चयन_base = pci_resource_start(pdev,
						felix->info->चयन_pci_bar);
	felix->imdio_base = pci_resource_start(pdev,
					       felix->info->imdio_pci_bar);

	pci_set_master(pdev);

	err = devm_request_thपढ़ोed_irq(&pdev->dev, pdev->irq, शून्य,
					&felix_irq_handler, IRQF_ONESHOT,
					"felix-intb", ocelot);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to request irq\n");
		जाओ err_alloc_irq;
	पूर्ण

	ocelot->ptp = 1;

	ds = kzalloc(माप(काष्ठा dsa_चयन), GFP_KERNEL);
	अगर (!ds) अणु
		err = -ENOMEM;
		dev_err(&pdev->dev, "Failed to allocate DSA switch\n");
		जाओ err_alloc_ds;
	पूर्ण

	ds->dev = &pdev->dev;
	ds->num_ports = felix->info->num_ports;
	ds->num_tx_queues = felix->info->num_tx_queues;
	ds->ops = &felix_चयन_ops;
	ds->priv = ocelot;
	felix->ds = ds;
	felix->tag_proto = DSA_TAG_PROTO_OCELOT;

	err = dsa_रेजिस्टर_चयन(ds);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to register DSA switch: %d\n", err);
		जाओ err_रेजिस्टर_ds;
	पूर्ण

	वापस 0;

err_रेजिस्टर_ds:
	kमुक्त(ds);
err_alloc_ds:
err_alloc_irq:
	kमुक्त(felix);
err_alloc_felix:
	pci_disable_device(pdev);
err_pci_enable:
	वापस err;
पूर्ण

अटल व्योम felix_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा felix *felix;

	felix = pci_get_drvdata(pdev);

	dsa_unरेजिस्टर_चयन(felix->ds);

	kमुक्त(felix->ds);
	kमुक्त(felix);

	pci_disable_device(pdev);
पूर्ण

अटल काष्ठा pci_device_id felix_ids[] = अणु
	अणु
		/* NXP LS1028A */
		PCI_DEVICE(PCI_VENDOR_ID_FREESCALE, 0xEEF0),
	पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, felix_ids);

अटल काष्ठा pci_driver felix_vsc9959_pci_driver = अणु
	.name		= "mscc_felix",
	.id_table	= felix_ids,
	.probe		= felix_pci_probe,
	.हटाओ		= felix_pci_हटाओ,
पूर्ण;
module_pci_driver(felix_vsc9959_pci_driver);

MODULE_DESCRIPTION("Felix Switch driver");
MODULE_LICENSE("GPL v2");
