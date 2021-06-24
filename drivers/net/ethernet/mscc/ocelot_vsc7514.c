<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/*
 * Microsemi Ocelot Switch driver
 *
 * Copyright (c) 2017 Microsemi Corporation
 */
#समावेश <linux/dsa/ocelot.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of_net.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/skbuff.h>
#समावेश <net/चयनdev.h>

#समावेश <soc/mscc/ocelot_vcap.h>
#समावेश <soc/mscc/ocelot_hsपन.स>
#समावेश "ocelot.h"

अटल स्थिर u32 ocelot_ana_regmap[] = अणु
	REG(ANA_ADVLEARN,				0x009000),
	REG(ANA_VLANMASK,				0x009004),
	REG(ANA_PORT_B_DOMAIN,				0x009008),
	REG(ANA_ANAGEFIL,				0x00900c),
	REG(ANA_ANEVENTS,				0x009010),
	REG(ANA_STORMLIMIT_BURST,			0x009014),
	REG(ANA_STORMLIMIT_CFG,				0x009018),
	REG(ANA_ISOLATED_PORTS,				0x009028),
	REG(ANA_COMMUNITY_PORTS,			0x00902c),
	REG(ANA_AUTOAGE,				0x009030),
	REG(ANA_MACTOPTIONS,				0x009034),
	REG(ANA_LEARNDISC,				0x009038),
	REG(ANA_AGENCTRL,				0x00903c),
	REG(ANA_MIRRORPORTS,				0x009040),
	REG(ANA_EMIRRORPORTS,				0x009044),
	REG(ANA_FLOODING,				0x009048),
	REG(ANA_FLOODING_IPMC,				0x00904c),
	REG(ANA_SFLOW_CFG,				0x009050),
	REG(ANA_PORT_MODE,				0x009080),
	REG(ANA_PGID_PGID,				0x008c00),
	REG(ANA_TABLES_ANMOVED,				0x008b30),
	REG(ANA_TABLES_MACHDATA,			0x008b34),
	REG(ANA_TABLES_MACLDATA,			0x008b38),
	REG(ANA_TABLES_MACACCESS,			0x008b3c),
	REG(ANA_TABLES_MACTINDX,			0x008b40),
	REG(ANA_TABLES_VLANACCESS,			0x008b44),
	REG(ANA_TABLES_VLANTIDX,			0x008b48),
	REG(ANA_TABLES_ISDXACCESS,			0x008b4c),
	REG(ANA_TABLES_ISDXTIDX,			0x008b50),
	REG(ANA_TABLES_ENTRYLIM,			0x008b00),
	REG(ANA_TABLES_PTP_ID_HIGH,			0x008b54),
	REG(ANA_TABLES_PTP_ID_LOW,			0x008b58),
	REG(ANA_MSTI_STATE,				0x008e00),
	REG(ANA_PORT_VLAN_CFG,				0x007000),
	REG(ANA_PORT_DROP_CFG,				0x007004),
	REG(ANA_PORT_QOS_CFG,				0x007008),
	REG(ANA_PORT_VCAP_CFG,				0x00700c),
	REG(ANA_PORT_VCAP_S1_KEY_CFG,			0x007010),
	REG(ANA_PORT_VCAP_S2_CFG,			0x00701c),
	REG(ANA_PORT_PCP_DEI_MAP,			0x007020),
	REG(ANA_PORT_CPU_FWD_CFG,			0x007060),
	REG(ANA_PORT_CPU_FWD_BPDU_CFG,			0x007064),
	REG(ANA_PORT_CPU_FWD_GARP_CFG,			0x007068),
	REG(ANA_PORT_CPU_FWD_CCM_CFG,			0x00706c),
	REG(ANA_PORT_PORT_CFG,				0x007070),
	REG(ANA_PORT_POL_CFG,				0x007074),
	REG(ANA_PORT_PTP_CFG,				0x007078),
	REG(ANA_PORT_PTP_DLY1_CFG,			0x00707c),
	REG(ANA_OAM_UPM_LM_CNT,				0x007c00),
	REG(ANA_PORT_PTP_DLY2_CFG,			0x007080),
	REG(ANA_PFC_PFC_CFG,				0x008800),
	REG(ANA_PFC_PFC_TIMER,				0x008804),
	REG(ANA_IPT_OAM_MEP_CFG,			0x008000),
	REG(ANA_IPT_IPT,				0x008004),
	REG(ANA_PPT_PPT,				0x008ac0),
	REG(ANA_FID_MAP_FID_MAP,			0x000000),
	REG(ANA_AGGR_CFG,				0x0090b4),
	REG(ANA_CPUQ_CFG,				0x0090b8),
	REG(ANA_CPUQ_CFG2,				0x0090bc),
	REG(ANA_CPUQ_8021_CFG,				0x0090c0),
	REG(ANA_DSCP_CFG,				0x009100),
	REG(ANA_DSCP_REWR_CFG,				0x009200),
	REG(ANA_VCAP_RNG_TYPE_CFG,			0x009240),
	REG(ANA_VCAP_RNG_VAL_CFG,			0x009260),
	REG(ANA_VRAP_CFG,				0x009280),
	REG(ANA_VRAP_HDR_DATA,				0x009284),
	REG(ANA_VRAP_HDR_MASK,				0x009288),
	REG(ANA_DISCARD_CFG,				0x00928c),
	REG(ANA_FID_CFG,				0x009290),
	REG(ANA_POL_PIR_CFG,				0x004000),
	REG(ANA_POL_CIR_CFG,				0x004004),
	REG(ANA_POL_MODE_CFG,				0x004008),
	REG(ANA_POL_PIR_STATE,				0x00400c),
	REG(ANA_POL_CIR_STATE,				0x004010),
	REG(ANA_POL_STATE,				0x004014),
	REG(ANA_POL_FLOWC,				0x008b80),
	REG(ANA_POL_HYST,				0x008bec),
	REG(ANA_POL_MISC_CFG,				0x008bf0),
पूर्ण;

अटल स्थिर u32 ocelot_qs_regmap[] = अणु
	REG(QS_XTR_GRP_CFG,				0x000000),
	REG(QS_XTR_RD,					0x000008),
	REG(QS_XTR_FRM_PRUNING,				0x000010),
	REG(QS_XTR_FLUSH,				0x000018),
	REG(QS_XTR_DATA_PRESENT,			0x00001c),
	REG(QS_XTR_CFG,					0x000020),
	REG(QS_INJ_GRP_CFG,				0x000024),
	REG(QS_INJ_WR,					0x00002c),
	REG(QS_INJ_CTRL,				0x000034),
	REG(QS_INJ_STATUS,				0x00003c),
	REG(QS_INJ_ERR,					0x000040),
	REG(QS_INH_DBG,					0x000048),
पूर्ण;

अटल स्थिर u32 ocelot_qsys_regmap[] = अणु
	REG(QSYS_PORT_MODE,				0x011200),
	REG(QSYS_SWITCH_PORT_MODE,			0x011234),
	REG(QSYS_STAT_CNT_CFG,				0x011264),
	REG(QSYS_EEE_CFG,				0x011268),
	REG(QSYS_EEE_THRES,				0x011294),
	REG(QSYS_IGR_NO_SHARING,			0x011298),
	REG(QSYS_EGR_NO_SHARING,			0x01129c),
	REG(QSYS_SW_STATUS,				0x0112a0),
	REG(QSYS_EXT_CPU_CFG,				0x0112d0),
	REG(QSYS_PAD_CFG,				0x0112d4),
	REG(QSYS_CPU_GROUP_MAP,				0x0112d8),
	REG(QSYS_QMAP,					0x0112dc),
	REG(QSYS_ISDX_SGRP,				0x011400),
	REG(QSYS_TIMED_FRAME_ENTRY,			0x014000),
	REG(QSYS_TFRM_MISC,				0x011310),
	REG(QSYS_TFRM_PORT_DLY,				0x011314),
	REG(QSYS_TFRM_TIMER_CFG_1,			0x011318),
	REG(QSYS_TFRM_TIMER_CFG_2,			0x01131c),
	REG(QSYS_TFRM_TIMER_CFG_3,			0x011320),
	REG(QSYS_TFRM_TIMER_CFG_4,			0x011324),
	REG(QSYS_TFRM_TIMER_CFG_5,			0x011328),
	REG(QSYS_TFRM_TIMER_CFG_6,			0x01132c),
	REG(QSYS_TFRM_TIMER_CFG_7,			0x011330),
	REG(QSYS_TFRM_TIMER_CFG_8,			0x011334),
	REG(QSYS_RED_PROखाता,				0x011338),
	REG(QSYS_RES_QOS_MODE,				0x011378),
	REG(QSYS_RES_CFG,				0x012000),
	REG(QSYS_RES_STAT,				0x012004),
	REG(QSYS_EGR_DROP_MODE,				0x01137c),
	REG(QSYS_EQ_CTRL,				0x011380),
	REG(QSYS_EVENTS_CORE,				0x011384),
	REG(QSYS_CIR_CFG,				0x000000),
	REG(QSYS_EIR_CFG,				0x000004),
	REG(QSYS_SE_CFG,				0x000008),
	REG(QSYS_SE_DWRR_CFG,				0x00000c),
	REG(QSYS_SE_CONNECT,				0x00003c),
	REG(QSYS_SE_DLB_SENSE,				0x000040),
	REG(QSYS_CIR_STATE,				0x000044),
	REG(QSYS_EIR_STATE,				0x000048),
	REG(QSYS_SE_STATE,				0x00004c),
	REG(QSYS_HSCH_MISC_CFG,				0x011388),
पूर्ण;

अटल स्थिर u32 ocelot_rew_regmap[] = अणु
	REG(REW_PORT_VLAN_CFG,				0x000000),
	REG(REW_TAG_CFG,				0x000004),
	REG(REW_PORT_CFG,				0x000008),
	REG(REW_DSCP_CFG,				0x00000c),
	REG(REW_PCP_DEI_QOS_MAP_CFG,			0x000010),
	REG(REW_PTP_CFG,				0x000050),
	REG(REW_PTP_DLY1_CFG,				0x000054),
	REG(REW_DSCP_REMAP_DP1_CFG,			0x000690),
	REG(REW_DSCP_REMAP_CFG,				0x000790),
	REG(REW_STAT_CFG,				0x000890),
	REG(REW_PPT,					0x000680),
पूर्ण;

अटल स्थिर u32 ocelot_sys_regmap[] = अणु
	REG(SYS_COUNT_RX_OCTETS,			0x000000),
	REG(SYS_COUNT_RX_UNICAST,			0x000004),
	REG(SYS_COUNT_RX_MULTICAST,			0x000008),
	REG(SYS_COUNT_RX_BROADCAST,			0x00000c),
	REG(SYS_COUNT_RX_SHORTS,			0x000010),
	REG(SYS_COUNT_RX_FRAGMENTS,			0x000014),
	REG(SYS_COUNT_RX_JABBERS,			0x000018),
	REG(SYS_COUNT_RX_CRC_ALIGN_ERRS,		0x00001c),
	REG(SYS_COUNT_RX_SYM_ERRS,			0x000020),
	REG(SYS_COUNT_RX_64,				0x000024),
	REG(SYS_COUNT_RX_65_127,			0x000028),
	REG(SYS_COUNT_RX_128_255,			0x00002c),
	REG(SYS_COUNT_RX_256_1023,			0x000030),
	REG(SYS_COUNT_RX_1024_1526,			0x000034),
	REG(SYS_COUNT_RX_1527_MAX,			0x000038),
	REG(SYS_COUNT_RX_PAUSE,				0x00003c),
	REG(SYS_COUNT_RX_CONTROL,			0x000040),
	REG(SYS_COUNT_RX_LONGS,				0x000044),
	REG(SYS_COUNT_RX_CLASSIFIED_DROPS,		0x000048),
	REG(SYS_COUNT_TX_OCTETS,			0x000100),
	REG(SYS_COUNT_TX_UNICAST,			0x000104),
	REG(SYS_COUNT_TX_MULTICAST,			0x000108),
	REG(SYS_COUNT_TX_BROADCAST,			0x00010c),
	REG(SYS_COUNT_TX_COLLISION,			0x000110),
	REG(SYS_COUNT_TX_DROPS,				0x000114),
	REG(SYS_COUNT_TX_PAUSE,				0x000118),
	REG(SYS_COUNT_TX_64,				0x00011c),
	REG(SYS_COUNT_TX_65_127,			0x000120),
	REG(SYS_COUNT_TX_128_511,			0x000124),
	REG(SYS_COUNT_TX_512_1023,			0x000128),
	REG(SYS_COUNT_TX_1024_1526,			0x00012c),
	REG(SYS_COUNT_TX_1527_MAX,			0x000130),
	REG(SYS_COUNT_TX_AGING,				0x000170),
	REG(SYS_RESET_CFG,				0x000508),
	REG(SYS_CMID,					0x00050c),
	REG(SYS_VLAN_ETYPE_CFG,				0x000510),
	REG(SYS_PORT_MODE,				0x000514),
	REG(SYS_FRONT_PORT_MODE,			0x000548),
	REG(SYS_FRM_AGING,				0x000574),
	REG(SYS_STAT_CFG,				0x000578),
	REG(SYS_SW_STATUS,				0x00057c),
	REG(SYS_MISC_CFG,				0x0005ac),
	REG(SYS_REW_MAC_HIGH_CFG,			0x0005b0),
	REG(SYS_REW_MAC_LOW_CFG,			0x0005dc),
	REG(SYS_CM_ADDR,				0x000500),
	REG(SYS_CM_DATA,				0x000504),
	REG(SYS_PAUSE_CFG,				0x000608),
	REG(SYS_PAUSE_TOT_CFG,				0x000638),
	REG(SYS_ATOP,					0x00063c),
	REG(SYS_ATOP_TOT_CFG,				0x00066c),
	REG(SYS_MAC_FC_CFG,				0x000670),
	REG(SYS_MMGT,					0x00069c),
	REG(SYS_MMGT_FAST,				0x0006a0),
	REG(SYS_EVENTS_DIF,				0x0006a4),
	REG(SYS_EVENTS_CORE,				0x0006b4),
	REG(SYS_CNT,					0x000000),
	REG(SYS_PTP_STATUS,				0x0006b8),
	REG(SYS_PTP_TXSTAMP,				0x0006bc),
	REG(SYS_PTP_NXT,				0x0006c0),
	REG(SYS_PTP_CFG,				0x0006c4),
पूर्ण;

अटल स्थिर u32 ocelot_vcap_regmap[] = अणु
	/* VCAP_CORE_CFG */
	REG(VCAP_CORE_UPDATE_CTRL,			0x000000),
	REG(VCAP_CORE_MV_CFG,				0x000004),
	/* VCAP_CORE_CACHE */
	REG(VCAP_CACHE_ENTRY_DAT,			0x000008),
	REG(VCAP_CACHE_MASK_DAT,			0x000108),
	REG(VCAP_CACHE_ACTION_DAT,			0x000208),
	REG(VCAP_CACHE_CNT_DAT,				0x000308),
	REG(VCAP_CACHE_TG_DAT,				0x000388),
	/* VCAP_CONST */
	REG(VCAP_CONST_VCAP_VER,			0x000398),
	REG(VCAP_CONST_ENTRY_WIDTH,			0x00039c),
	REG(VCAP_CONST_ENTRY_CNT,			0x0003a0),
	REG(VCAP_CONST_ENTRY_SWCNT,			0x0003a4),
	REG(VCAP_CONST_ENTRY_TG_WIDTH,			0x0003a8),
	REG(VCAP_CONST_ACTION_DEF_CNT,			0x0003ac),
	REG(VCAP_CONST_ACTION_WIDTH,			0x0003b0),
	REG(VCAP_CONST_CNT_WIDTH,			0x0003b4),
	REG(VCAP_CONST_CORE_CNT,			0x0003b8),
	REG(VCAP_CONST_IF_CNT,				0x0003bc),
पूर्ण;

अटल स्थिर u32 ocelot_ptp_regmap[] = अणु
	REG(PTP_PIN_CFG,				0x000000),
	REG(PTP_PIN_TOD_SEC_MSB,			0x000004),
	REG(PTP_PIN_TOD_SEC_LSB,			0x000008),
	REG(PTP_PIN_TOD_NSEC,				0x00000c),
	REG(PTP_PIN_WF_HIGH_PERIOD,			0x000014),
	REG(PTP_PIN_WF_LOW_PERIOD,			0x000018),
	REG(PTP_CFG_MISC,				0x0000a0),
	REG(PTP_CLK_CFG_ADJ_CFG,			0x0000a4),
	REG(PTP_CLK_CFG_ADJ_FREQ,			0x0000a8),
पूर्ण;

अटल स्थिर u32 ocelot_dev_gmii_regmap[] = अणु
	REG(DEV_CLOCK_CFG,				0x0),
	REG(DEV_PORT_MISC,				0x4),
	REG(DEV_EVENTS,					0x8),
	REG(DEV_EEE_CFG,				0xc),
	REG(DEV_RX_PATH_DELAY,				0x10),
	REG(DEV_TX_PATH_DELAY,				0x14),
	REG(DEV_PTP_PREDICT_CFG,			0x18),
	REG(DEV_MAC_ENA_CFG,				0x1c),
	REG(DEV_MAC_MODE_CFG,				0x20),
	REG(DEV_MAC_MAXLEN_CFG,				0x24),
	REG(DEV_MAC_TAGS_CFG,				0x28),
	REG(DEV_MAC_ADV_CHK_CFG,			0x2c),
	REG(DEV_MAC_IFG_CFG,				0x30),
	REG(DEV_MAC_HDX_CFG,				0x34),
	REG(DEV_MAC_DBG_CFG,				0x38),
	REG(DEV_MAC_FC_MAC_LOW_CFG,			0x3c),
	REG(DEV_MAC_FC_MAC_HIGH_CFG,			0x40),
	REG(DEV_MAC_STICKY,				0x44),
	REG(PCS1G_CFG,					0x48),
	REG(PCS1G_MODE_CFG,				0x4c),
	REG(PCS1G_SD_CFG,				0x50),
	REG(PCS1G_ANEG_CFG,				0x54),
	REG(PCS1G_ANEG_NP_CFG,				0x58),
	REG(PCS1G_LB_CFG,				0x5c),
	REG(PCS1G_DBG_CFG,				0x60),
	REG(PCS1G_CDET_CFG,				0x64),
	REG(PCS1G_ANEG_STATUS,				0x68),
	REG(PCS1G_ANEG_NP_STATUS,			0x6c),
	REG(PCS1G_LINK_STATUS,				0x70),
	REG(PCS1G_LINK_DOWN_CNT,			0x74),
	REG(PCS1G_STICKY,				0x78),
	REG(PCS1G_DEBUG_STATUS,				0x7c),
	REG(PCS1G_LPI_CFG,				0x80),
	REG(PCS1G_LPI_WAKE_ERROR_CNT,			0x84),
	REG(PCS1G_LPI_STATUS,				0x88),
	REG(PCS1G_TSTPAT_MODE_CFG,			0x8c),
	REG(PCS1G_TSTPAT_STATUS,			0x90),
	REG(DEV_PCS_FX100_CFG,				0x94),
	REG(DEV_PCS_FX100_STATUS,			0x98),
पूर्ण;

अटल स्थिर u32 *ocelot_regmap[TARGET_MAX] = अणु
	[ANA] = ocelot_ana_regmap,
	[QS] = ocelot_qs_regmap,
	[QSYS] = ocelot_qsys_regmap,
	[REW] = ocelot_rew_regmap,
	[SYS] = ocelot_sys_regmap,
	[S0] = ocelot_vcap_regmap,
	[S1] = ocelot_vcap_regmap,
	[S2] = ocelot_vcap_regmap,
	[PTP] = ocelot_ptp_regmap,
	[DEV_GMII] = ocelot_dev_gmii_regmap,
पूर्ण;

अटल स्थिर काष्ठा reg_field ocelot_regfields[REGFIELD_MAX] = अणु
	[ANA_ADVLEARN_VLAN_CHK] = REG_FIELD(ANA_ADVLEARN, 11, 11),
	[ANA_ADVLEARN_LEARN_MIRROR] = REG_FIELD(ANA_ADVLEARN, 0, 10),
	[ANA_ANEVENTS_MSTI_DROP] = REG_FIELD(ANA_ANEVENTS, 27, 27),
	[ANA_ANEVENTS_ACLKILL] = REG_FIELD(ANA_ANEVENTS, 26, 26),
	[ANA_ANEVENTS_ACLUSED] = REG_FIELD(ANA_ANEVENTS, 25, 25),
	[ANA_ANEVENTS_AUTOAGE] = REG_FIELD(ANA_ANEVENTS, 24, 24),
	[ANA_ANEVENTS_VS2TTL1] = REG_FIELD(ANA_ANEVENTS, 23, 23),
	[ANA_ANEVENTS_STORM_DROP] = REG_FIELD(ANA_ANEVENTS, 22, 22),
	[ANA_ANEVENTS_LEARN_DROP] = REG_FIELD(ANA_ANEVENTS, 21, 21),
	[ANA_ANEVENTS_AGED_ENTRY] = REG_FIELD(ANA_ANEVENTS, 20, 20),
	[ANA_ANEVENTS_CPU_LEARN_FAILED] = REG_FIELD(ANA_ANEVENTS, 19, 19),
	[ANA_ANEVENTS_AUTO_LEARN_FAILED] = REG_FIELD(ANA_ANEVENTS, 18, 18),
	[ANA_ANEVENTS_LEARN_REMOVE] = REG_FIELD(ANA_ANEVENTS, 17, 17),
	[ANA_ANEVENTS_AUTO_LEARNED] = REG_FIELD(ANA_ANEVENTS, 16, 16),
	[ANA_ANEVENTS_AUTO_MOVED] = REG_FIELD(ANA_ANEVENTS, 15, 15),
	[ANA_ANEVENTS_DROPPED] = REG_FIELD(ANA_ANEVENTS, 14, 14),
	[ANA_ANEVENTS_CLASSIFIED_DROP] = REG_FIELD(ANA_ANEVENTS, 13, 13),
	[ANA_ANEVENTS_CLASSIFIED_COPY] = REG_FIELD(ANA_ANEVENTS, 12, 12),
	[ANA_ANEVENTS_VLAN_DISCARD] = REG_FIELD(ANA_ANEVENTS, 11, 11),
	[ANA_ANEVENTS_FWD_DISCARD] = REG_FIELD(ANA_ANEVENTS, 10, 10),
	[ANA_ANEVENTS_MULTICAST_FLOOD] = REG_FIELD(ANA_ANEVENTS, 9, 9),
	[ANA_ANEVENTS_UNICAST_FLOOD] = REG_FIELD(ANA_ANEVENTS, 8, 8),
	[ANA_ANEVENTS_DEST_KNOWN] = REG_FIELD(ANA_ANEVENTS, 7, 7),
	[ANA_ANEVENTS_BUCKET3_MATCH] = REG_FIELD(ANA_ANEVENTS, 6, 6),
	[ANA_ANEVENTS_BUCKET2_MATCH] = REG_FIELD(ANA_ANEVENTS, 5, 5),
	[ANA_ANEVENTS_BUCKET1_MATCH] = REG_FIELD(ANA_ANEVENTS, 4, 4),
	[ANA_ANEVENTS_BUCKET0_MATCH] = REG_FIELD(ANA_ANEVENTS, 3, 3),
	[ANA_ANEVENTS_CPU_OPERATION] = REG_FIELD(ANA_ANEVENTS, 2, 2),
	[ANA_ANEVENTS_DMAC_LOOKUP] = REG_FIELD(ANA_ANEVENTS, 1, 1),
	[ANA_ANEVENTS_SMAC_LOOKUP] = REG_FIELD(ANA_ANEVENTS, 0, 0),
	[ANA_TABLES_MACACCESS_B_DOM] = REG_FIELD(ANA_TABLES_MACACCESS, 18, 18),
	[ANA_TABLES_MACTINDX_BUCKET] = REG_FIELD(ANA_TABLES_MACTINDX, 10, 11),
	[ANA_TABLES_MACTINDX_M_INDEX] = REG_FIELD(ANA_TABLES_MACTINDX, 0, 9),
	[QSYS_TIMED_FRAME_ENTRY_TFRM_VLD] = REG_FIELD(QSYS_TIMED_FRAME_ENTRY, 20, 20),
	[QSYS_TIMED_FRAME_ENTRY_TFRM_FP] = REG_FIELD(QSYS_TIMED_FRAME_ENTRY, 8, 19),
	[QSYS_TIMED_FRAME_ENTRY_TFRM_PORTNO] = REG_FIELD(QSYS_TIMED_FRAME_ENTRY, 4, 7),
	[QSYS_TIMED_FRAME_ENTRY_TFRM_TM_SEL] = REG_FIELD(QSYS_TIMED_FRAME_ENTRY, 1, 3),
	[QSYS_TIMED_FRAME_ENTRY_TFRM_TM_T] = REG_FIELD(QSYS_TIMED_FRAME_ENTRY, 0, 0),
	[SYS_RESET_CFG_CORE_ENA] = REG_FIELD(SYS_RESET_CFG, 2, 2),
	[SYS_RESET_CFG_MEM_ENA] = REG_FIELD(SYS_RESET_CFG, 1, 1),
	[SYS_RESET_CFG_MEM_INIT] = REG_FIELD(SYS_RESET_CFG, 0, 0),
	/* Replicated per number of ports (12), रेजिस्टर size 4 per port */
	[QSYS_SWITCH_PORT_MODE_PORT_ENA] = REG_FIELD_ID(QSYS_SWITCH_PORT_MODE, 14, 14, 12, 4),
	[QSYS_SWITCH_PORT_MODE_SCH_NEXT_CFG] = REG_FIELD_ID(QSYS_SWITCH_PORT_MODE, 11, 13, 12, 4),
	[QSYS_SWITCH_PORT_MODE_YEL_RSRVD] = REG_FIELD_ID(QSYS_SWITCH_PORT_MODE, 10, 10, 12, 4),
	[QSYS_SWITCH_PORT_MODE_INGRESS_DROP_MODE] = REG_FIELD_ID(QSYS_SWITCH_PORT_MODE, 9, 9, 12, 4),
	[QSYS_SWITCH_PORT_MODE_TX_PFC_ENA] = REG_FIELD_ID(QSYS_SWITCH_PORT_MODE, 1, 8, 12, 4),
	[QSYS_SWITCH_PORT_MODE_TX_PFC_MODE] = REG_FIELD_ID(QSYS_SWITCH_PORT_MODE, 0, 0, 12, 4),
	[SYS_PORT_MODE_DATA_WO_TS] = REG_FIELD_ID(SYS_PORT_MODE, 5, 6, 12, 4),
	[SYS_PORT_MODE_INCL_INJ_HDR] = REG_FIELD_ID(SYS_PORT_MODE, 3, 4, 12, 4),
	[SYS_PORT_MODE_INCL_XTR_HDR] = REG_FIELD_ID(SYS_PORT_MODE, 1, 2, 12, 4),
	[SYS_PORT_MODE_INCL_HDR_ERR] = REG_FIELD_ID(SYS_PORT_MODE, 0, 0, 12, 4),
	[SYS_PAUSE_CFG_PAUSE_START] = REG_FIELD_ID(SYS_PAUSE_CFG, 10, 18, 12, 4),
	[SYS_PAUSE_CFG_PAUSE_STOP] = REG_FIELD_ID(SYS_PAUSE_CFG, 1, 9, 12, 4),
	[SYS_PAUSE_CFG_PAUSE_ENA] = REG_FIELD_ID(SYS_PAUSE_CFG, 0, 1, 12, 4),
पूर्ण;

अटल स्थिर काष्ठा ocelot_stat_layout ocelot_stats_layout[] = अणु
	अणु .name = "rx_octets", .offset = 0x00, पूर्ण,
	अणु .name = "rx_unicast", .offset = 0x01, पूर्ण,
	अणु .name = "rx_multicast", .offset = 0x02, पूर्ण,
	अणु .name = "rx_broadcast", .offset = 0x03, पूर्ण,
	अणु .name = "rx_shorts", .offset = 0x04, पूर्ण,
	अणु .name = "rx_fragments", .offset = 0x05, पूर्ण,
	अणु .name = "rx_jabbers", .offset = 0x06, पूर्ण,
	अणु .name = "rx_crc_align_errs", .offset = 0x07, पूर्ण,
	अणु .name = "rx_sym_errs", .offset = 0x08, पूर्ण,
	अणु .name = "rx_frames_below_65_octets", .offset = 0x09, पूर्ण,
	अणु .name = "rx_frames_65_to_127_octets", .offset = 0x0A, पूर्ण,
	अणु .name = "rx_frames_128_to_255_octets", .offset = 0x0B, पूर्ण,
	अणु .name = "rx_frames_256_to_511_octets", .offset = 0x0C, पूर्ण,
	अणु .name = "rx_frames_512_to_1023_octets", .offset = 0x0D, पूर्ण,
	अणु .name = "rx_frames_1024_to_1526_octets", .offset = 0x0E, पूर्ण,
	अणु .name = "rx_frames_over_1526_octets", .offset = 0x0F, पूर्ण,
	अणु .name = "rx_pause", .offset = 0x10, पूर्ण,
	अणु .name = "rx_control", .offset = 0x11, पूर्ण,
	अणु .name = "rx_longs", .offset = 0x12, पूर्ण,
	अणु .name = "rx_classified_drops", .offset = 0x13, पूर्ण,
	अणु .name = "rx_red_prio_0", .offset = 0x14, पूर्ण,
	अणु .name = "rx_red_prio_1", .offset = 0x15, पूर्ण,
	अणु .name = "rx_red_prio_2", .offset = 0x16, पूर्ण,
	अणु .name = "rx_red_prio_3", .offset = 0x17, पूर्ण,
	अणु .name = "rx_red_prio_4", .offset = 0x18, पूर्ण,
	अणु .name = "rx_red_prio_5", .offset = 0x19, पूर्ण,
	अणु .name = "rx_red_prio_6", .offset = 0x1A, पूर्ण,
	अणु .name = "rx_red_prio_7", .offset = 0x1B, पूर्ण,
	अणु .name = "rx_yellow_prio_0", .offset = 0x1C, पूर्ण,
	अणु .name = "rx_yellow_prio_1", .offset = 0x1D, पूर्ण,
	अणु .name = "rx_yellow_prio_2", .offset = 0x1E, पूर्ण,
	अणु .name = "rx_yellow_prio_3", .offset = 0x1F, पूर्ण,
	अणु .name = "rx_yellow_prio_4", .offset = 0x20, पूर्ण,
	अणु .name = "rx_yellow_prio_5", .offset = 0x21, पूर्ण,
	अणु .name = "rx_yellow_prio_6", .offset = 0x22, पूर्ण,
	अणु .name = "rx_yellow_prio_7", .offset = 0x23, पूर्ण,
	अणु .name = "rx_green_prio_0", .offset = 0x24, पूर्ण,
	अणु .name = "rx_green_prio_1", .offset = 0x25, पूर्ण,
	अणु .name = "rx_green_prio_2", .offset = 0x26, पूर्ण,
	अणु .name = "rx_green_prio_3", .offset = 0x27, पूर्ण,
	अणु .name = "rx_green_prio_4", .offset = 0x28, पूर्ण,
	अणु .name = "rx_green_prio_5", .offset = 0x29, पूर्ण,
	अणु .name = "rx_green_prio_6", .offset = 0x2A, पूर्ण,
	अणु .name = "rx_green_prio_7", .offset = 0x2B, पूर्ण,
	अणु .name = "tx_octets", .offset = 0x40, पूर्ण,
	अणु .name = "tx_unicast", .offset = 0x41, पूर्ण,
	अणु .name = "tx_multicast", .offset = 0x42, पूर्ण,
	अणु .name = "tx_broadcast", .offset = 0x43, पूर्ण,
	अणु .name = "tx_collision", .offset = 0x44, पूर्ण,
	अणु .name = "tx_drops", .offset = 0x45, पूर्ण,
	अणु .name = "tx_pause", .offset = 0x46, पूर्ण,
	अणु .name = "tx_frames_below_65_octets", .offset = 0x47, पूर्ण,
	अणु .name = "tx_frames_65_to_127_octets", .offset = 0x48, पूर्ण,
	अणु .name = "tx_frames_128_255_octets", .offset = 0x49, पूर्ण,
	अणु .name = "tx_frames_256_511_octets", .offset = 0x4A, पूर्ण,
	अणु .name = "tx_frames_512_1023_octets", .offset = 0x4B, पूर्ण,
	अणु .name = "tx_frames_1024_1526_octets", .offset = 0x4C, पूर्ण,
	अणु .name = "tx_frames_over_1526_octets", .offset = 0x4D, पूर्ण,
	अणु .name = "tx_yellow_prio_0", .offset = 0x4E, पूर्ण,
	अणु .name = "tx_yellow_prio_1", .offset = 0x4F, पूर्ण,
	अणु .name = "tx_yellow_prio_2", .offset = 0x50, पूर्ण,
	अणु .name = "tx_yellow_prio_3", .offset = 0x51, पूर्ण,
	अणु .name = "tx_yellow_prio_4", .offset = 0x52, पूर्ण,
	अणु .name = "tx_yellow_prio_5", .offset = 0x53, पूर्ण,
	अणु .name = "tx_yellow_prio_6", .offset = 0x54, पूर्ण,
	अणु .name = "tx_yellow_prio_7", .offset = 0x55, पूर्ण,
	अणु .name = "tx_green_prio_0", .offset = 0x56, पूर्ण,
	अणु .name = "tx_green_prio_1", .offset = 0x57, पूर्ण,
	अणु .name = "tx_green_prio_2", .offset = 0x58, पूर्ण,
	अणु .name = "tx_green_prio_3", .offset = 0x59, पूर्ण,
	अणु .name = "tx_green_prio_4", .offset = 0x5A, पूर्ण,
	अणु .name = "tx_green_prio_5", .offset = 0x5B, पूर्ण,
	अणु .name = "tx_green_prio_6", .offset = 0x5C, पूर्ण,
	अणु .name = "tx_green_prio_7", .offset = 0x5D, पूर्ण,
	अणु .name = "tx_aged", .offset = 0x5E, पूर्ण,
	अणु .name = "drop_local", .offset = 0x80, पूर्ण,
	अणु .name = "drop_tail", .offset = 0x81, पूर्ण,
	अणु .name = "drop_yellow_prio_0", .offset = 0x82, पूर्ण,
	अणु .name = "drop_yellow_prio_1", .offset = 0x83, पूर्ण,
	अणु .name = "drop_yellow_prio_2", .offset = 0x84, पूर्ण,
	अणु .name = "drop_yellow_prio_3", .offset = 0x85, पूर्ण,
	अणु .name = "drop_yellow_prio_4", .offset = 0x86, पूर्ण,
	अणु .name = "drop_yellow_prio_5", .offset = 0x87, पूर्ण,
	अणु .name = "drop_yellow_prio_6", .offset = 0x88, पूर्ण,
	अणु .name = "drop_yellow_prio_7", .offset = 0x89, पूर्ण,
	अणु .name = "drop_green_prio_0", .offset = 0x8A, पूर्ण,
	अणु .name = "drop_green_prio_1", .offset = 0x8B, पूर्ण,
	अणु .name = "drop_green_prio_2", .offset = 0x8C, पूर्ण,
	अणु .name = "drop_green_prio_3", .offset = 0x8D, पूर्ण,
	अणु .name = "drop_green_prio_4", .offset = 0x8E, पूर्ण,
	अणु .name = "drop_green_prio_5", .offset = 0x8F, पूर्ण,
	अणु .name = "drop_green_prio_6", .offset = 0x90, पूर्ण,
	अणु .name = "drop_green_prio_7", .offset = 0x91, पूर्ण,
पूर्ण;

अटल व्योम ocelot_pll5_init(काष्ठा ocelot *ocelot)
अणु
	/* Configure PLL5. This will need a proper CCF driver
	 * The values are coming from the VTSS API क्रम Ocelot
	 */
	regmap_ग_लिखो(ocelot->tarमाला_लो[HSIO], HSIO_PLL5G_CFG4,
		     HSIO_PLL5G_CFG4_IB_CTRL(0x7600) |
		     HSIO_PLL5G_CFG4_IB_BIAS_CTRL(0x8));
	regmap_ग_लिखो(ocelot->tarमाला_लो[HSIO], HSIO_PLL5G_CFG0,
		     HSIO_PLL5G_CFG0_CORE_CLK_DIV(0x11) |
		     HSIO_PLL5G_CFG0_CPU_CLK_DIV(2) |
		     HSIO_PLL5G_CFG0_ENA_BIAS |
		     HSIO_PLL5G_CFG0_ENA_VCO_BUF |
		     HSIO_PLL5G_CFG0_ENA_CP1 |
		     HSIO_PLL5G_CFG0_SELCPI(2) |
		     HSIO_PLL5G_CFG0_LOOP_BW_RES(0xe) |
		     HSIO_PLL5G_CFG0_SELBGV820(4) |
		     HSIO_PLL5G_CFG0_DIV4 |
		     HSIO_PLL5G_CFG0_ENA_CLKTREE |
		     HSIO_PLL5G_CFG0_ENA_LANE);
	regmap_ग_लिखो(ocelot->tarमाला_लो[HSIO], HSIO_PLL5G_CFG2,
		     HSIO_PLL5G_CFG2_EN_RESET_FRQ_DET |
		     HSIO_PLL5G_CFG2_EN_RESET_OVERRUN |
		     HSIO_PLL5G_CFG2_GAIN_TEST(0x8) |
		     HSIO_PLL5G_CFG2_ENA_AMPCTRL |
		     HSIO_PLL5G_CFG2_PWD_AMPCTRL_N |
		     HSIO_PLL5G_CFG2_AMPC_SEL(0x10));
पूर्ण

अटल पूर्णांक ocelot_chip_init(काष्ठा ocelot *ocelot, स्थिर काष्ठा ocelot_ops *ops)
अणु
	पूर्णांक ret;

	ocelot->map = ocelot_regmap;
	ocelot->stats_layout = ocelot_stats_layout;
	ocelot->num_stats = ARRAY_SIZE(ocelot_stats_layout);
	ocelot->num_mact_rows = 1024;
	ocelot->ops = ops;

	ret = ocelot_regfields_init(ocelot, ocelot_regfields);
	अगर (ret)
		वापस ret;

	ocelot_pll5_init(ocelot);

	eth_अक्रमom_addr(ocelot->base_mac);
	ocelot->base_mac[5] &= 0xf0;

	वापस 0;
पूर्ण

अटल irqवापस_t ocelot_xtr_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा ocelot *ocelot = arg;
	पूर्णांक grp = 0, err;

	जबतक (ocelot_पढ़ो(ocelot, QS_XTR_DATA_PRESENT) & BIT(grp)) अणु
		काष्ठा sk_buff *skb;

		err = ocelot_xtr_poll_frame(ocelot, grp, &skb);
		अगर (err)
			जाओ out;

		skb->dev->stats.rx_bytes += skb->len;
		skb->dev->stats.rx_packets++;

		अगर (!skb_defer_rx_बारtamp(skb))
			netअगर_rx(skb);
	पूर्ण

out:
	अगर (err < 0)
		ocelot_drain_cpu_queue(ocelot, 0);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t ocelot_ptp_rdy_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा ocelot *ocelot = arg;

	ocelot_get_txtstamp(ocelot);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा of_device_id mscc_ocelot_match[] = अणु
	अणु .compatible = "mscc,vsc7514-switch" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mscc_ocelot_match);

अटल पूर्णांक ocelot_reset(काष्ठा ocelot *ocelot)
अणु
	पूर्णांक retries = 100;
	u32 val;

	regmap_field_ग_लिखो(ocelot->regfields[SYS_RESET_CFG_MEM_INIT], 1);
	regmap_field_ग_लिखो(ocelot->regfields[SYS_RESET_CFG_MEM_ENA], 1);

	करो अणु
		msleep(1);
		regmap_field_पढ़ो(ocelot->regfields[SYS_RESET_CFG_MEM_INIT],
				  &val);
	पूर्ण जबतक (val && --retries);

	अगर (!retries)
		वापस -ETIMEDOUT;

	regmap_field_ग_लिखो(ocelot->regfields[SYS_RESET_CFG_MEM_ENA], 1);
	regmap_field_ग_लिखो(ocelot->regfields[SYS_RESET_CFG_CORE_ENA], 1);

	वापस 0;
पूर्ण

/* Watermark encode
 * Bit 8:   Unit; 0:1, 1:16
 * Bit 7-0: Value to be multiplied with unit
 */
अटल u16 ocelot_wm_enc(u16 value)
अणु
	WARN_ON(value >= 16 * BIT(8));

	अगर (value >= BIT(8))
		वापस BIT(8) | (value / 16);

	वापस value;
पूर्ण

अटल u16 ocelot_wm_dec(u16 wm)
अणु
	अगर (wm & BIT(8))
		वापस (wm & GENMASK(7, 0)) * 16;

	वापस wm;
पूर्ण

अटल व्योम ocelot_wm_stat(u32 val, u32 *inuse, u32 *maxuse)
अणु
	*inuse = (val & GENMASK(23, 12)) >> 12;
	*maxuse = val & GENMASK(11, 0);
पूर्ण

अटल स्थिर काष्ठा ocelot_ops ocelot_ops = अणु
	.reset			= ocelot_reset,
	.wm_enc			= ocelot_wm_enc,
	.wm_dec			= ocelot_wm_dec,
	.wm_stat		= ocelot_wm_stat,
	.port_to_netdev		= ocelot_port_to_netdev,
	.netdev_to_port		= ocelot_netdev_to_port,
पूर्ण;

अटल स्थिर काष्ठा vcap_field vsc7514_vcap_es0_keys[] = अणु
	[VCAP_ES0_EGR_PORT]			= अणु  0,  4पूर्ण,
	[VCAP_ES0_IGR_PORT]			= अणु  4,  4पूर्ण,
	[VCAP_ES0_RSV]				= अणु  8,  2पूर्ण,
	[VCAP_ES0_L2_MC]			= अणु 10,  1पूर्ण,
	[VCAP_ES0_L2_BC]			= अणु 11,  1पूर्ण,
	[VCAP_ES0_VID]				= अणु 12, 12पूर्ण,
	[VCAP_ES0_DP]				= अणु 24,  1पूर्ण,
	[VCAP_ES0_PCP]				= अणु 25,  3पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vcap_field vsc7514_vcap_es0_actions[] = अणु
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
	[VCAP_ES0_ACT_RSV]			= अणु 49, 24पूर्ण,
	[VCAP_ES0_ACT_HIT_STICKY]		= अणु 73,  1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vcap_field vsc7514_vcap_is1_keys[] = अणु
	[VCAP_IS1_HK_TYPE]			= अणु  0,   1पूर्ण,
	[VCAP_IS1_HK_LOOKUP]			= अणु  1,   2पूर्ण,
	[VCAP_IS1_HK_IGR_PORT_MASK]		= अणु  3,  12पूर्ण,
	[VCAP_IS1_HK_RSV]			= अणु 15,   9पूर्ण,
	[VCAP_IS1_HK_OAM_Y1731]			= अणु 24,   1पूर्ण,
	[VCAP_IS1_HK_L2_MC]			= अणु 25,   1पूर्ण,
	[VCAP_IS1_HK_L2_BC]			= अणु 26,   1पूर्ण,
	[VCAP_IS1_HK_IP_MC]			= अणु 27,   1पूर्ण,
	[VCAP_IS1_HK_VLAN_TAGGED]		= अणु 28,   1पूर्ण,
	[VCAP_IS1_HK_VLAN_DBL_TAGGED]		= अणु 29,   1पूर्ण,
	[VCAP_IS1_HK_TPID]			= अणु 30,   1पूर्ण,
	[VCAP_IS1_HK_VID]			= अणु 31,  12पूर्ण,
	[VCAP_IS1_HK_DEI]			= अणु 43,   1पूर्ण,
	[VCAP_IS1_HK_PCP]			= अणु 44,   3पूर्ण,
	/* Specअगरic Fields क्रम IS1 Half Key S1_NORMAL */
	[VCAP_IS1_HK_L2_SMAC]			= अणु 47,  48पूर्ण,
	[VCAP_IS1_HK_ETYPE_LEN]			= अणु 95,   1पूर्ण,
	[VCAP_IS1_HK_ETYPE]			= अणु 96,  16पूर्ण,
	[VCAP_IS1_HK_IP_SNAP]			= अणु112,   1पूर्ण,
	[VCAP_IS1_HK_IP4]			= अणु113,   1पूर्ण,
	/* Layer-3 Inक्रमmation */
	[VCAP_IS1_HK_L3_FRAGMENT]		= अणु114,   1पूर्ण,
	[VCAP_IS1_HK_L3_FRAG_OFS_GT0]		= अणु115,   1पूर्ण,
	[VCAP_IS1_HK_L3_OPTIONS]		= अणु116,   1पूर्ण,
	[VCAP_IS1_HK_L3_DSCP]			= अणु117,   6पूर्ण,
	[VCAP_IS1_HK_L3_IP4_SIP]		= अणु123,  32पूर्ण,
	/* Layer-4 Inक्रमmation */
	[VCAP_IS1_HK_TCP_UDP]			= अणु155,   1पूर्ण,
	[VCAP_IS1_HK_TCP]			= अणु156,   1पूर्ण,
	[VCAP_IS1_HK_L4_SPORT]			= अणु157,  16पूर्ण,
	[VCAP_IS1_HK_L4_RNG]			= अणु173,   8पूर्ण,
	/* Specअगरic Fields क्रम IS1 Half Key S1_5TUPLE_IP4 */
	[VCAP_IS1_HK_IP4_INNER_TPID]            = अणु 47,   1पूर्ण,
	[VCAP_IS1_HK_IP4_INNER_VID]		= अणु 48,  12पूर्ण,
	[VCAP_IS1_HK_IP4_INNER_DEI]		= अणु 60,   1पूर्ण,
	[VCAP_IS1_HK_IP4_INNER_PCP]		= अणु 61,   3पूर्ण,
	[VCAP_IS1_HK_IP4_IP4]			= अणु 64,   1पूर्ण,
	[VCAP_IS1_HK_IP4_L3_FRAGMENT]		= अणु 65,   1पूर्ण,
	[VCAP_IS1_HK_IP4_L3_FRAG_OFS_GT0]	= अणु 66,   1पूर्ण,
	[VCAP_IS1_HK_IP4_L3_OPTIONS]		= अणु 67,   1पूर्ण,
	[VCAP_IS1_HK_IP4_L3_DSCP]		= अणु 68,   6पूर्ण,
	[VCAP_IS1_HK_IP4_L3_IP4_DIP]		= अणु 74,  32पूर्ण,
	[VCAP_IS1_HK_IP4_L3_IP4_SIP]		= अणु106,  32पूर्ण,
	[VCAP_IS1_HK_IP4_L3_PROTO]		= अणु138,   8पूर्ण,
	[VCAP_IS1_HK_IP4_TCP_UDP]		= अणु146,   1पूर्ण,
	[VCAP_IS1_HK_IP4_TCP]			= अणु147,   1पूर्ण,
	[VCAP_IS1_HK_IP4_L4_RNG]		= अणु148,   8पूर्ण,
	[VCAP_IS1_HK_IP4_IP_PAYLOAD_S1_5TUPLE]	= अणु156,  32पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vcap_field vsc7514_vcap_is1_actions[] = अणु
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

अटल स्थिर काष्ठा vcap_field vsc7514_vcap_is2_keys[] = अणु
	/* Common: 46 bits */
	[VCAP_IS2_TYPE]				= अणु  0,   4पूर्ण,
	[VCAP_IS2_HK_FIRST]			= अणु  4,   1पूर्ण,
	[VCAP_IS2_HK_PAG]			= अणु  5,   8पूर्ण,
	[VCAP_IS2_HK_IGR_PORT_MASK]		= अणु 13,  12पूर्ण,
	[VCAP_IS2_HK_RSV2]			= अणु 25,   1पूर्ण,
	[VCAP_IS2_HK_HOST_MATCH]		= अणु 26,   1पूर्ण,
	[VCAP_IS2_HK_L2_MC]			= अणु 27,   1पूर्ण,
	[VCAP_IS2_HK_L2_BC]			= अणु 28,   1पूर्ण,
	[VCAP_IS2_HK_VLAN_TAGGED]		= अणु 29,   1पूर्ण,
	[VCAP_IS2_HK_VID]			= अणु 30,  12पूर्ण,
	[VCAP_IS2_HK_DEI]			= अणु 42,   1पूर्ण,
	[VCAP_IS2_HK_PCP]			= अणु 43,   3पूर्ण,
	/* MAC_ETYPE / MAC_LLC / MAC_SNAP / OAM common */
	[VCAP_IS2_HK_L2_DMAC]			= अणु 46,  48पूर्ण,
	[VCAP_IS2_HK_L2_SMAC]			= अणु 94,  48पूर्ण,
	/* MAC_ETYPE (TYPE=000) */
	[VCAP_IS2_HK_MAC_ETYPE_ETYPE]		= अणु142,  16पूर्ण,
	[VCAP_IS2_HK_MAC_ETYPE_L2_PAYLOAD0]	= अणु158,  16पूर्ण,
	[VCAP_IS2_HK_MAC_ETYPE_L2_PAYLOAD1]	= अणु174,   8पूर्ण,
	[VCAP_IS2_HK_MAC_ETYPE_L2_PAYLOAD2]	= अणु182,   3पूर्ण,
	/* MAC_LLC (TYPE=001) */
	[VCAP_IS2_HK_MAC_LLC_L2_LLC]		= अणु142,  40पूर्ण,
	/* MAC_SNAP (TYPE=010) */
	[VCAP_IS2_HK_MAC_SNAP_L2_SNAP]		= अणु142,  40पूर्ण,
	/* MAC_ARP (TYPE=011) */
	[VCAP_IS2_HK_MAC_ARP_SMAC]		= अणु 46,  48पूर्ण,
	[VCAP_IS2_HK_MAC_ARP_ADDR_SPACE_OK]	= अणु 94,   1पूर्ण,
	[VCAP_IS2_HK_MAC_ARP_PROTO_SPACE_OK]	= अणु 95,   1पूर्ण,
	[VCAP_IS2_HK_MAC_ARP_LEN_OK]		= अणु 96,   1पूर्ण,
	[VCAP_IS2_HK_MAC_ARP_TARGET_MATCH]	= अणु 97,   1पूर्ण,
	[VCAP_IS2_HK_MAC_ARP_SENDER_MATCH]	= अणु 98,   1पूर्ण,
	[VCAP_IS2_HK_MAC_ARP_OPCODE_UNKNOWN]	= अणु 99,   1पूर्ण,
	[VCAP_IS2_HK_MAC_ARP_OPCODE]		= अणु100,   2पूर्ण,
	[VCAP_IS2_HK_MAC_ARP_L3_IP4_DIP]	= अणु102,  32पूर्ण,
	[VCAP_IS2_HK_MAC_ARP_L3_IP4_SIP]	= अणु134,  32पूर्ण,
	[VCAP_IS2_HK_MAC_ARP_DIP_EQ_SIP]	= अणु166,   1पूर्ण,
	/* IP4_TCP_UDP / IP4_OTHER common */
	[VCAP_IS2_HK_IP4]			= अणु 46,   1पूर्ण,
	[VCAP_IS2_HK_L3_FRAGMENT]		= अणु 47,   1पूर्ण,
	[VCAP_IS2_HK_L3_FRAG_OFS_GT0]		= अणु 48,   1पूर्ण,
	[VCAP_IS2_HK_L3_OPTIONS]		= अणु 49,   1पूर्ण,
	[VCAP_IS2_HK_IP4_L3_TTL_GT0]		= अणु 50,   1पूर्ण,
	[VCAP_IS2_HK_L3_TOS]			= अणु 51,   8पूर्ण,
	[VCAP_IS2_HK_L3_IP4_DIP]		= अणु 59,  32पूर्ण,
	[VCAP_IS2_HK_L3_IP4_SIP]		= अणु 91,  32पूर्ण,
	[VCAP_IS2_HK_DIP_EQ_SIP]		= अणु123,   1पूर्ण,
	/* IP4_TCP_UDP (TYPE=100) */
	[VCAP_IS2_HK_TCP]			= अणु124,   1पूर्ण,
	[VCAP_IS2_HK_L4_DPORT]			= अणु125,  16पूर्ण,
	[VCAP_IS2_HK_L4_SPORT]			= अणु141,  16पूर्ण,
	[VCAP_IS2_HK_L4_RNG]			= अणु157,   8पूर्ण,
	[VCAP_IS2_HK_L4_SPORT_EQ_DPORT]		= अणु165,   1पूर्ण,
	[VCAP_IS2_HK_L4_SEQUENCE_EQ0]		= अणु166,   1पूर्ण,
	[VCAP_IS2_HK_L4_FIN]			= अणु167,   1पूर्ण,
	[VCAP_IS2_HK_L4_SYN]			= अणु168,   1पूर्ण,
	[VCAP_IS2_HK_L4_RST]			= अणु169,   1पूर्ण,
	[VCAP_IS2_HK_L4_PSH]			= अणु170,   1पूर्ण,
	[VCAP_IS2_HK_L4_ACK]			= अणु171,   1पूर्ण,
	[VCAP_IS2_HK_L4_URG]			= अणु172,   1पूर्ण,
	[VCAP_IS2_HK_L4_1588_DOM]		= अणु173,   8पूर्ण,
	[VCAP_IS2_HK_L4_1588_VER]		= अणु181,   4पूर्ण,
	/* IP4_OTHER (TYPE=101) */
	[VCAP_IS2_HK_IP4_L3_PROTO]		= अणु124,   8पूर्ण,
	[VCAP_IS2_HK_L3_PAYLOAD]		= अणु132,  56पूर्ण,
	/* IP6_STD (TYPE=110) */
	[VCAP_IS2_HK_IP6_L3_TTL_GT0]		= अणु 46,   1पूर्ण,
	[VCAP_IS2_HK_L3_IP6_SIP]		= अणु 47, 128पूर्ण,
	[VCAP_IS2_HK_IP6_L3_PROTO]		= अणु175,   8पूर्ण,
	/* OAM (TYPE=111) */
	[VCAP_IS2_HK_OAM_MEL_FLAGS]		= अणु142,   7पूर्ण,
	[VCAP_IS2_HK_OAM_VER]			= अणु149,   5पूर्ण,
	[VCAP_IS2_HK_OAM_OPCODE]		= अणु154,   8पूर्ण,
	[VCAP_IS2_HK_OAM_FLAGS]			= अणु162,   8पूर्ण,
	[VCAP_IS2_HK_OAM_MEPID]			= अणु170,  16पूर्ण,
	[VCAP_IS2_HK_OAM_CCM_CNTS_EQ0]		= अणु186,   1पूर्ण,
	[VCAP_IS2_HK_OAM_IS_Y1731]		= अणु187,   1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा vcap_field vsc7514_vcap_is2_actions[] = अणु
	[VCAP_IS2_ACT_HIT_ME_ONCE]		= अणु  0,  1पूर्ण,
	[VCAP_IS2_ACT_CPU_COPY_ENA]		= अणु  1,  1पूर्ण,
	[VCAP_IS2_ACT_CPU_QU_NUM]		= अणु  2,  3पूर्ण,
	[VCAP_IS2_ACT_MASK_MODE]		= अणु  5,  2पूर्ण,
	[VCAP_IS2_ACT_MIRROR_ENA]		= अणु  7,  1पूर्ण,
	[VCAP_IS2_ACT_LRN_DIS]			= अणु  8,  1पूर्ण,
	[VCAP_IS2_ACT_POLICE_ENA]		= अणु  9,  1पूर्ण,
	[VCAP_IS2_ACT_POLICE_IDX]		= अणु 10,  9पूर्ण,
	[VCAP_IS2_ACT_POLICE_VCAP_ONLY]		= अणु 19,  1पूर्ण,
	[VCAP_IS2_ACT_PORT_MASK]		= अणु 20, 11पूर्ण,
	[VCAP_IS2_ACT_REW_OP]			= अणु 31,  9पूर्ण,
	[VCAP_IS2_ACT_SMAC_REPLACE_ENA]		= अणु 40,  1पूर्ण,
	[VCAP_IS2_ACT_RSV]			= अणु 41,  2पूर्ण,
	[VCAP_IS2_ACT_ACL_ID]			= अणु 43,  6पूर्ण,
	[VCAP_IS2_ACT_HIT_CNT]			= अणु 49, 32पूर्ण,
पूर्ण;

अटल काष्ठा vcap_props vsc7514_vcap_props[] = अणु
	[VCAP_ES0] = अणु
		.action_type_width = 0,
		.action_table = अणु
			[ES0_ACTION_TYPE_NORMAL] = अणु
				.width = 73, /* HIT_STICKY not included */
				.count = 1,
			पूर्ण,
		पूर्ण,
		.target = S0,
		.keys = vsc7514_vcap_es0_keys,
		.actions = vsc7514_vcap_es0_actions,
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
		.keys = vsc7514_vcap_is1_keys,
		.actions = vsc7514_vcap_is1_actions,
	पूर्ण,
	[VCAP_IS2] = अणु
		.action_type_width = 1,
		.action_table = अणु
			[IS2_ACTION_TYPE_NORMAL] = अणु
				.width = 49,
				.count = 2
			पूर्ण,
			[IS2_ACTION_TYPE_SMAC_SIP] = अणु
				.width = 6,
				.count = 4
			पूर्ण,
		पूर्ण,
		.target = S2,
		.keys = vsc7514_vcap_is2_keys,
		.actions = vsc7514_vcap_is2_actions,
	पूर्ण,
पूर्ण;

अटल काष्ठा ptp_घड़ी_info ocelot_ptp_घड़ी_info = अणु
	.owner		= THIS_MODULE,
	.name		= "ocelot ptp",
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

अटल व्योम mscc_ocelot_tearकरोwn_devlink_ports(काष्ठा ocelot *ocelot)
अणु
	पूर्णांक port;

	क्रम (port = 0; port < ocelot->num_phys_ports; port++)
		ocelot_port_devlink_tearकरोwn(ocelot, port);
पूर्ण

अटल व्योम mscc_ocelot_release_ports(काष्ठा ocelot *ocelot)
अणु
	पूर्णांक port;

	क्रम (port = 0; port < ocelot->num_phys_ports; port++) अणु
		काष्ठा ocelot_port *ocelot_port;

		ocelot_port = ocelot->ports[port];
		अगर (!ocelot_port)
			जारी;

		ocelot_deinit_port(ocelot, port);
		ocelot_release_port(ocelot_port);
	पूर्ण
पूर्ण

अटल पूर्णांक mscc_ocelot_init_ports(काष्ठा platक्रमm_device *pdev,
				  काष्ठा device_node *ports)
अणु
	काष्ठा ocelot *ocelot = platक्रमm_get_drvdata(pdev);
	u32 devlink_ports_रेजिस्टरed = 0;
	काष्ठा device_node *portnp;
	पूर्णांक port, err;
	u32 reg;

	ocelot->ports = devm_kसुस्मृति(ocelot->dev, ocelot->num_phys_ports,
				     माप(काष्ठा ocelot_port *), GFP_KERNEL);
	अगर (!ocelot->ports)
		वापस -ENOMEM;

	ocelot->devlink_ports = devm_kसुस्मृति(ocelot->dev,
					     ocelot->num_phys_ports,
					     माप(*ocelot->devlink_ports),
					     GFP_KERNEL);
	अगर (!ocelot->devlink_ports)
		वापस -ENOMEM;

	क्रम_each_available_child_of_node(ports, portnp) अणु
		काष्ठा ocelot_port_निजी *priv;
		काष्ठा ocelot_port *ocelot_port;
		काष्ठा device_node *phy_node;
		काष्ठा devlink_port *dlp;
		phy_पूर्णांकerface_t phy_mode;
		काष्ठा phy_device *phy;
		काष्ठा regmap *target;
		काष्ठा resource *res;
		काष्ठा phy *serdes;
		अक्षर res_name[8];

		अगर (of_property_पढ़ो_u32(portnp, "reg", &reg))
			जारी;

		port = reg;
		अगर (port < 0 || port >= ocelot->num_phys_ports) अणु
			dev_err(ocelot->dev,
				"invalid port number: %d >= %d\n", port,
				ocelot->num_phys_ports);
			जारी;
		पूर्ण

		snम_लिखो(res_name, माप(res_name), "port%d", port);

		res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						   res_name);
		target = ocelot_regmap_init(ocelot, res);
		अगर (IS_ERR(target)) अणु
			err = PTR_ERR(target);
			जाओ out_tearकरोwn;
		पूर्ण

		phy_node = of_parse_phandle(portnp, "phy-handle", 0);
		अगर (!phy_node)
			जारी;

		phy = of_phy_find_device(phy_node);
		of_node_put(phy_node);
		अगर (!phy)
			जारी;

		err = ocelot_port_devlink_init(ocelot, port,
					       DEVLINK_PORT_FLAVOUR_PHYSICAL);
		अगर (err) अणु
			of_node_put(portnp);
			जाओ out_tearकरोwn;
		पूर्ण
		devlink_ports_रेजिस्टरed |= BIT(port);

		err = ocelot_probe_port(ocelot, port, target, phy);
		अगर (err) अणु
			of_node_put(portnp);
			जाओ out_tearकरोwn;
		पूर्ण

		ocelot_port = ocelot->ports[port];
		priv = container_of(ocelot_port, काष्ठा ocelot_port_निजी,
				    port);
		dlp = &ocelot->devlink_ports[port];
		devlink_port_type_eth_set(dlp, priv->dev);

		of_get_phy_mode(portnp, &phy_mode);

		ocelot_port->phy_mode = phy_mode;

		चयन (ocelot_port->phy_mode) अणु
		हाल PHY_INTERFACE_MODE_NA:
			जारी;
		हाल PHY_INTERFACE_MODE_SGMII:
			अवरोध;
		हाल PHY_INTERFACE_MODE_QSGMII:
			/* Ensure घड़ी संकेतs and speed is set on all
			 * QSGMII links
			 */
			ocelot_port_ग_लिखोl(ocelot_port,
					   DEV_CLOCK_CFG_LINK_SPEED
					   (OCELOT_SPEED_1000),
					   DEV_CLOCK_CFG);
			अवरोध;
		शेष:
			dev_err(ocelot->dev,
				"invalid phy mode for port%d, (Q)SGMII only\n",
				port);
			of_node_put(portnp);
			err = -EINVAL;
			जाओ out_tearकरोwn;
		पूर्ण

		serdes = devm_of_phy_get(ocelot->dev, portnp, शून्य);
		अगर (IS_ERR(serdes)) अणु
			err = PTR_ERR(serdes);
			अगर (err == -EPROBE_DEFER)
				dev_dbg(ocelot->dev, "deferring probe\n");
			अन्यथा
				dev_err(ocelot->dev,
					"missing SerDes phys for port%d\n",
					port);

			of_node_put(portnp);
			जाओ out_tearकरोwn;
		पूर्ण

		priv->serdes = serdes;
	पूर्ण

	/* Initialize unused devlink ports at the end */
	क्रम (port = 0; port < ocelot->num_phys_ports; port++) अणु
		अगर (devlink_ports_रेजिस्टरed & BIT(port))
			जारी;

		err = ocelot_port_devlink_init(ocelot, port,
					       DEVLINK_PORT_FLAVOUR_UNUSED);
		अगर (err)
			जाओ out_tearकरोwn;

		devlink_ports_रेजिस्टरed |= BIT(port);
	पूर्ण

	वापस 0;

out_tearकरोwn:
	/* Unरेजिस्टर the network पूर्णांकerfaces */
	mscc_ocelot_release_ports(ocelot);
	/* Tear करोwn devlink ports क्रम the रेजिस्टरed network पूर्णांकerfaces */
	क्रम (port = 0; port < ocelot->num_phys_ports; port++) अणु
		अगर (devlink_ports_रेजिस्टरed & BIT(port))
			ocelot_port_devlink_tearकरोwn(ocelot, port);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक mscc_ocelot_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक err, irq_xtr, irq_ptp_rdy;
	काष्ठा device_node *ports;
	काष्ठा devlink *devlink;
	काष्ठा ocelot *ocelot;
	काष्ठा regmap *hsio;
	अचिन्हित पूर्णांक i;

	काष्ठा अणु
		क्रमागत ocelot_target id;
		अक्षर *name;
		u8 optional:1;
	पूर्ण io_target[] = अणु
		अणु SYS, "sys" पूर्ण,
		अणु REW, "rew" पूर्ण,
		अणु QSYS, "qsys" पूर्ण,
		अणु ANA, "ana" पूर्ण,
		अणु QS, "qs" पूर्ण,
		अणु S0, "s0" पूर्ण,
		अणु S1, "s1" पूर्ण,
		अणु S2, "s2" पूर्ण,
		अणु PTP, "ptp", 1 पूर्ण,
	पूर्ण;

	अगर (!np && !pdev->dev.platक्रमm_data)
		वापस -ENODEV;

	devlink = devlink_alloc(&ocelot_devlink_ops, माप(*ocelot));
	अगर (!devlink)
		वापस -ENOMEM;

	ocelot = devlink_priv(devlink);
	ocelot->devlink = priv_to_devlink(ocelot);
	platक्रमm_set_drvdata(pdev, ocelot);
	ocelot->dev = &pdev->dev;

	क्रम (i = 0; i < ARRAY_SIZE(io_target); i++) अणु
		काष्ठा regmap *target;
		काष्ठा resource *res;

		res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
						   io_target[i].name);

		target = ocelot_regmap_init(ocelot, res);
		अगर (IS_ERR(target)) अणु
			अगर (io_target[i].optional) अणु
				ocelot->tarमाला_लो[io_target[i].id] = शून्य;
				जारी;
			पूर्ण
			err = PTR_ERR(target);
			जाओ out_मुक्त_devlink;
		पूर्ण

		ocelot->tarमाला_लो[io_target[i].id] = target;
	पूर्ण

	hsio = syscon_regmap_lookup_by_compatible("mscc,ocelot-hsio");
	अगर (IS_ERR(hsio)) अणु
		dev_err(&pdev->dev, "missing hsio syscon\n");
		err = PTR_ERR(hsio);
		जाओ out_मुक्त_devlink;
	पूर्ण

	ocelot->tarमाला_लो[HSIO] = hsio;

	err = ocelot_chip_init(ocelot, &ocelot_ops);
	अगर (err)
		जाओ out_मुक्त_devlink;

	irq_xtr = platक्रमm_get_irq_byname(pdev, "xtr");
	अगर (irq_xtr < 0) अणु
		err = irq_xtr;
		जाओ out_मुक्त_devlink;
	पूर्ण

	err = devm_request_thपढ़ोed_irq(&pdev->dev, irq_xtr, शून्य,
					ocelot_xtr_irq_handler, IRQF_ONESHOT,
					"frame extraction", ocelot);
	अगर (err)
		जाओ out_मुक्त_devlink;

	irq_ptp_rdy = platक्रमm_get_irq_byname(pdev, "ptp_rdy");
	अगर (irq_ptp_rdy > 0 && ocelot->tarमाला_लो[PTP]) अणु
		err = devm_request_thपढ़ोed_irq(&pdev->dev, irq_ptp_rdy, शून्य,
						ocelot_ptp_rdy_irq_handler,
						IRQF_ONESHOT, "ptp ready",
						ocelot);
		अगर (err)
			जाओ out_मुक्त_devlink;

		/* Both the PTP पूर्णांकerrupt and the PTP bank are available */
		ocelot->ptp = 1;
	पूर्ण

	ports = of_get_child_by_name(np, "ethernet-ports");
	अगर (!ports) अणु
		dev_err(ocelot->dev, "no ethernet-ports child node found\n");
		err = -ENODEV;
		जाओ out_मुक्त_devlink;
	पूर्ण

	ocelot->num_phys_ports = of_get_child_count(ports);
	ocelot->num_flooding_pgids = 1;

	ocelot->vcap = vsc7514_vcap_props;
	ocelot->npi = -1;

	err = ocelot_init(ocelot);
	अगर (err)
		जाओ out_put_ports;

	err = devlink_रेजिस्टर(devlink, ocelot->dev);
	अगर (err)
		जाओ out_ocelot_deinit;

	err = mscc_ocelot_init_ports(pdev, ports);
	अगर (err)
		जाओ out_ocelot_devlink_unरेजिस्टर;

	err = ocelot_devlink_sb_रेजिस्टर(ocelot);
	अगर (err)
		जाओ out_ocelot_release_ports;

	अगर (ocelot->ptp) अणु
		err = ocelot_init_बारtamp(ocelot, &ocelot_ptp_घड़ी_info);
		अगर (err) अणु
			dev_err(ocelot->dev,
				"Timestamp initialization failed\n");
			ocelot->ptp = 0;
		पूर्ण
	पूर्ण

	रेजिस्टर_netdevice_notअगरier(&ocelot_netdevice_nb);
	रेजिस्टर_चयनdev_notअगरier(&ocelot_चयनdev_nb);
	रेजिस्टर_चयनdev_blocking_notअगरier(&ocelot_चयनdev_blocking_nb);

	of_node_put(ports);

	dev_info(&pdev->dev, "Ocelot switch probed\n");

	वापस 0;

out_ocelot_release_ports:
	mscc_ocelot_release_ports(ocelot);
	mscc_ocelot_tearकरोwn_devlink_ports(ocelot);
out_ocelot_devlink_unरेजिस्टर:
	devlink_unरेजिस्टर(devlink);
out_ocelot_deinit:
	ocelot_deinit(ocelot);
out_put_ports:
	of_node_put(ports);
out_मुक्त_devlink:
	devlink_मुक्त(devlink);
	वापस err;
पूर्ण

अटल पूर्णांक mscc_ocelot_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ocelot *ocelot = platक्रमm_get_drvdata(pdev);

	ocelot_deinit_बारtamp(ocelot);
	ocelot_devlink_sb_unरेजिस्टर(ocelot);
	mscc_ocelot_release_ports(ocelot);
	mscc_ocelot_tearकरोwn_devlink_ports(ocelot);
	devlink_unरेजिस्टर(ocelot->devlink);
	ocelot_deinit(ocelot);
	unरेजिस्टर_चयनdev_blocking_notअगरier(&ocelot_चयनdev_blocking_nb);
	unरेजिस्टर_चयनdev_notअगरier(&ocelot_चयनdev_nb);
	unरेजिस्टर_netdevice_notअगरier(&ocelot_netdevice_nb);
	devlink_मुक्त(ocelot->devlink);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mscc_ocelot_driver = अणु
	.probe = mscc_ocelot_probe,
	.हटाओ = mscc_ocelot_हटाओ,
	.driver = अणु
		.name = "ocelot-switch",
		.of_match_table = mscc_ocelot_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mscc_ocelot_driver);

MODULE_DESCRIPTION("Microsemi Ocelot switch driver");
MODULE_AUTHOR("Alexandre Belloni <alexandre.belloni@bootlin.com>");
MODULE_LICENSE("Dual MIT/GPL");
