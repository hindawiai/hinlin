<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR MIT) */
/* Copyright (c) 2017 Microsemi Corporation
 */

#अगर_अघोषित _SOC_MSCC_OCELOT_H
#घोषणा _SOC_MSCC_OCELOT_H

#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/regmap.h>
#समावेश <net/dsa.h>

/* Port Group IDs (PGID) are masks of destination ports.
 *
 * For L2 क्रमwarding, the चयन perक्रमms 3 lookups in the PGID table क्रम each
 * frame, and क्रमwards the frame to the ports that are present in the logical
 * AND of all 3 PGIDs.
 *
 * These PGID lookups are:
 * - In one of PGID[0-63]: क्रम the destination masks. There are 2 paths by
 *   which the चयन selects a destination PGID:
 *     - The अणुDMAC, VIDपूर्ण is present in the MAC table. In that हाल, the
 *       destination PGID is given by the DEST_IDX field of the MAC table entry
 *       that matched.
 *     - The अणुDMAC, VIDपूर्ण is not present in the MAC table (it is unknown). The
 *       frame is disseminated as being either unicast, multicast or broadcast,
 *       and according to that, the destination PGID is chosen as being the
 *       value contained by ANA_FLOODING_FLD_UNICAST,
 *       ANA_FLOODING_FLD_MULTICAST or ANA_FLOODING_FLD_BROADCAST.
 *   The destination PGID can be an unicast set: the first PGIDs, 0 to
 *   ocelot->num_phys_ports - 1, or a multicast set: the PGIDs from
 *   ocelot->num_phys_ports to 63. By convention, a unicast PGID corresponds to
 *   a physical port and has a single bit set in the destination ports mask:
 *   that corresponding to the port number itself. In contrast, a multicast
 *   PGID will have potentially more than one single bit set in the destination
 *   ports mask.
 * - In one of PGID[64-79]: क्रम the aggregation mask. The चयन classअगरier
 *   dissects each frame and generates a 4-bit Link Aggregation Code which is
 *   used क्रम this second PGID table lookup. The goal of link aggregation is to
 *   hash multiple flows within the same LAG on to dअगरferent destination ports.
 *   The first lookup will result in a PGID with all the LAG members present in
 *   the destination ports mask, and the second lookup, by Link Aggregation
 *   Code, will ensure that each flow माला_लो क्रमwarded only to a single port out
 *   of that mask (there are no duplicates).
 * - In one of PGID[80-90]: क्रम the source mask. The third समय, the PGID table
 *   is indexed with the ingress port (plus 80). These PGIDs answer the
 *   question "is port i allowed to forward traffic to port j?" If yes, then
 *   BIT(j) of PGID 80+i will be found set. The third PGID lookup can be used
 *   to enक्रमce the L2 क्रमwarding matrix imposed by e.g. a Linux bridge.
 */

/* Reserve some destination PGIDs at the end of the range:
 * PGID_BLACKHOLE: used क्रम not क्रमwarding the frames
 * PGID_CPU: used क्रम whitelisting certain MAC addresses, such as the addresses
 *           of the चयन port net devices, towards the CPU port module.
 * PGID_UC: the flooding destinations क्रम unknown unicast traffic.
 * PGID_MC: the flooding destinations क्रम non-IP multicast traffic.
 * PGID_MCIPV4: the flooding destinations क्रम IPv4 multicast traffic.
 * PGID_MCIPV6: the flooding destinations क्रम IPv6 multicast traffic.
 * PGID_BC: the flooding destinations क्रम broadcast traffic.
 */
#घोषणा PGID_BLACKHOLE			57
#घोषणा PGID_CPU			58
#घोषणा PGID_UC				59
#घोषणा PGID_MC				60
#घोषणा PGID_MCIPV4			61
#घोषणा PGID_MCIPV6			62
#घोषणा PGID_BC				63

#घोषणा क्रम_each_unicast_dest_pgid(ocelot, pgid)		\
	क्रम ((pgid) = 0;					\
	     (pgid) < (ocelot)->num_phys_ports;			\
	     (pgid)++)

#घोषणा क्रम_each_nonreserved_multicast_dest_pgid(ocelot, pgid)	\
	क्रम ((pgid) = (ocelot)->num_phys_ports + 1;		\
	     (pgid) < PGID_BLACKHOLE;				\
	     (pgid)++)

#घोषणा क्रम_each_aggr_pgid(ocelot, pgid)			\
	क्रम ((pgid) = PGID_AGGR;				\
	     (pgid) < PGID_SRC;					\
	     (pgid)++)

/* Aggregation PGIDs, one per Link Aggregation Code */
#घोषणा PGID_AGGR			64

/* Source PGIDs, one per physical port */
#घोषणा PGID_SRC			80

#घोषणा IFH_TAG_TYPE_C			0
#घोषणा IFH_TAG_TYPE_S			1

#घोषणा IFH_REW_OP_NOOP			0x0
#घोषणा IFH_REW_OP_DSCP			0x1
#घोषणा IFH_REW_OP_ONE_STEP_PTP		0x2
#घोषणा IFH_REW_OP_TWO_STEP_PTP		0x3
#घोषणा IFH_REW_OP_ORIGIN_PTP		0x5

#घोषणा OCELOT_NUM_TC			8

#घोषणा OCELOT_SPEED_2500		0
#घोषणा OCELOT_SPEED_1000		1
#घोषणा OCELOT_SPEED_100		2
#घोषणा OCELOT_SPEED_10			3

#घोषणा OCELOT_PTP_PINS_NUM		4

#घोषणा TARGET_OFFSET			24
#घोषणा REG_MASK			GENMASK(TARGET_OFFSET - 1, 0)
#घोषणा REG(reg, offset)		[reg & REG_MASK] = offset

#घोषणा REG_RESERVED_ADDR		0xffffffff
#घोषणा REG_RESERVED(reg)		REG(reg, REG_RESERVED_ADDR)

#घोषणा OCELOT_MRP_CPUQ			7

क्रमागत ocelot_target अणु
	ANA = 1,
	QS,
	QSYS,
	REW,
	SYS,
	S0,
	S1,
	S2,
	HSIO,
	PTP,
	GCB,
	DEV_GMII,
	TARGET_MAX,
पूर्ण;

क्रमागत ocelot_reg अणु
	ANA_ADVLEARN = ANA << TARGET_OFFSET,
	ANA_VLANMASK,
	ANA_PORT_B_DOMAIN,
	ANA_ANAGEFIL,
	ANA_ANEVENTS,
	ANA_STORMLIMIT_BURST,
	ANA_STORMLIMIT_CFG,
	ANA_ISOLATED_PORTS,
	ANA_COMMUNITY_PORTS,
	ANA_AUTOAGE,
	ANA_MACTOPTIONS,
	ANA_LEARNDISC,
	ANA_AGENCTRL,
	ANA_MIRRORPORTS,
	ANA_EMIRRORPORTS,
	ANA_FLOODING,
	ANA_FLOODING_IPMC,
	ANA_SFLOW_CFG,
	ANA_PORT_MODE,
	ANA_CUT_THRU_CFG,
	ANA_PGID_PGID,
	ANA_TABLES_ANMOVED,
	ANA_TABLES_MACHDATA,
	ANA_TABLES_MACLDATA,
	ANA_TABLES_STREAMDATA,
	ANA_TABLES_MACACCESS,
	ANA_TABLES_MACTINDX,
	ANA_TABLES_VLANACCESS,
	ANA_TABLES_VLANTIDX,
	ANA_TABLES_ISDXACCESS,
	ANA_TABLES_ISDXTIDX,
	ANA_TABLES_ENTRYLIM,
	ANA_TABLES_PTP_ID_HIGH,
	ANA_TABLES_PTP_ID_LOW,
	ANA_TABLES_STREAMACCESS,
	ANA_TABLES_STREAMTIDX,
	ANA_TABLES_SEQ_HISTORY,
	ANA_TABLES_SEQ_MASK,
	ANA_TABLES_SFID_MASK,
	ANA_TABLES_SFIDACCESS,
	ANA_TABLES_SFIDTIDX,
	ANA_MSTI_STATE,
	ANA_OAM_UPM_LM_CNT,
	ANA_SG_ACCESS_CTRL,
	ANA_SG_CONFIG_REG_1,
	ANA_SG_CONFIG_REG_2,
	ANA_SG_CONFIG_REG_3,
	ANA_SG_CONFIG_REG_4,
	ANA_SG_CONFIG_REG_5,
	ANA_SG_GCL_GS_CONFIG,
	ANA_SG_GCL_TI_CONFIG,
	ANA_SG_STATUS_REG_1,
	ANA_SG_STATUS_REG_2,
	ANA_SG_STATUS_REG_3,
	ANA_PORT_VLAN_CFG,
	ANA_PORT_DROP_CFG,
	ANA_PORT_QOS_CFG,
	ANA_PORT_VCAP_CFG,
	ANA_PORT_VCAP_S1_KEY_CFG,
	ANA_PORT_VCAP_S2_CFG,
	ANA_PORT_PCP_DEI_MAP,
	ANA_PORT_CPU_FWD_CFG,
	ANA_PORT_CPU_FWD_BPDU_CFG,
	ANA_PORT_CPU_FWD_GARP_CFG,
	ANA_PORT_CPU_FWD_CCM_CFG,
	ANA_PORT_PORT_CFG,
	ANA_PORT_POL_CFG,
	ANA_PORT_PTP_CFG,
	ANA_PORT_PTP_DLY1_CFG,
	ANA_PORT_PTP_DLY2_CFG,
	ANA_PORT_SFID_CFG,
	ANA_PFC_PFC_CFG,
	ANA_PFC_PFC_TIMER,
	ANA_IPT_OAM_MEP_CFG,
	ANA_IPT_IPT,
	ANA_PPT_PPT,
	ANA_FID_MAP_FID_MAP,
	ANA_AGGR_CFG,
	ANA_CPUQ_CFG,
	ANA_CPUQ_CFG2,
	ANA_CPUQ_8021_CFG,
	ANA_DSCP_CFG,
	ANA_DSCP_REWR_CFG,
	ANA_VCAP_RNG_TYPE_CFG,
	ANA_VCAP_RNG_VAL_CFG,
	ANA_VRAP_CFG,
	ANA_VRAP_HDR_DATA,
	ANA_VRAP_HDR_MASK,
	ANA_DISCARD_CFG,
	ANA_FID_CFG,
	ANA_POL_PIR_CFG,
	ANA_POL_CIR_CFG,
	ANA_POL_MODE_CFG,
	ANA_POL_PIR_STATE,
	ANA_POL_CIR_STATE,
	ANA_POL_STATE,
	ANA_POL_FLOWC,
	ANA_POL_HYST,
	ANA_POL_MISC_CFG,
	QS_XTR_GRP_CFG = QS << TARGET_OFFSET,
	QS_XTR_RD,
	QS_XTR_FRM_PRUNING,
	QS_XTR_FLUSH,
	QS_XTR_DATA_PRESENT,
	QS_XTR_CFG,
	QS_INJ_GRP_CFG,
	QS_INJ_WR,
	QS_INJ_CTRL,
	QS_INJ_STATUS,
	QS_INJ_ERR,
	QS_INH_DBG,
	QSYS_PORT_MODE = QSYS << TARGET_OFFSET,
	QSYS_SWITCH_PORT_MODE,
	QSYS_STAT_CNT_CFG,
	QSYS_EEE_CFG,
	QSYS_EEE_THRES,
	QSYS_IGR_NO_SHARING,
	QSYS_EGR_NO_SHARING,
	QSYS_SW_STATUS,
	QSYS_EXT_CPU_CFG,
	QSYS_PAD_CFG,
	QSYS_CPU_GROUP_MAP,
	QSYS_QMAP,
	QSYS_ISDX_SGRP,
	QSYS_TIMED_FRAME_ENTRY,
	QSYS_TFRM_MISC,
	QSYS_TFRM_PORT_DLY,
	QSYS_TFRM_TIMER_CFG_1,
	QSYS_TFRM_TIMER_CFG_2,
	QSYS_TFRM_TIMER_CFG_3,
	QSYS_TFRM_TIMER_CFG_4,
	QSYS_TFRM_TIMER_CFG_5,
	QSYS_TFRM_TIMER_CFG_6,
	QSYS_TFRM_TIMER_CFG_7,
	QSYS_TFRM_TIMER_CFG_8,
	QSYS_RED_PROखाता,
	QSYS_RES_QOS_MODE,
	QSYS_RES_CFG,
	QSYS_RES_STAT,
	QSYS_EGR_DROP_MODE,
	QSYS_EQ_CTRL,
	QSYS_EVENTS_CORE,
	QSYS_QMAXSDU_CFG_0,
	QSYS_QMAXSDU_CFG_1,
	QSYS_QMAXSDU_CFG_2,
	QSYS_QMAXSDU_CFG_3,
	QSYS_QMAXSDU_CFG_4,
	QSYS_QMAXSDU_CFG_5,
	QSYS_QMAXSDU_CFG_6,
	QSYS_QMAXSDU_CFG_7,
	QSYS_PREEMPTION_CFG,
	QSYS_CIR_CFG,
	QSYS_EIR_CFG,
	QSYS_SE_CFG,
	QSYS_SE_DWRR_CFG,
	QSYS_SE_CONNECT,
	QSYS_SE_DLB_SENSE,
	QSYS_CIR_STATE,
	QSYS_EIR_STATE,
	QSYS_SE_STATE,
	QSYS_HSCH_MISC_CFG,
	QSYS_TAG_CONFIG,
	QSYS_TAS_PARAM_CFG_CTRL,
	QSYS_PORT_MAX_SDU,
	QSYS_PARAM_CFG_REG_1,
	QSYS_PARAM_CFG_REG_2,
	QSYS_PARAM_CFG_REG_3,
	QSYS_PARAM_CFG_REG_4,
	QSYS_PARAM_CFG_REG_5,
	QSYS_GCL_CFG_REG_1,
	QSYS_GCL_CFG_REG_2,
	QSYS_PARAM_STATUS_REG_1,
	QSYS_PARAM_STATUS_REG_2,
	QSYS_PARAM_STATUS_REG_3,
	QSYS_PARAM_STATUS_REG_4,
	QSYS_PARAM_STATUS_REG_5,
	QSYS_PARAM_STATUS_REG_6,
	QSYS_PARAM_STATUS_REG_7,
	QSYS_PARAM_STATUS_REG_8,
	QSYS_PARAM_STATUS_REG_9,
	QSYS_GCL_STATUS_REG_1,
	QSYS_GCL_STATUS_REG_2,
	REW_PORT_VLAN_CFG = REW << TARGET_OFFSET,
	REW_TAG_CFG,
	REW_PORT_CFG,
	REW_DSCP_CFG,
	REW_PCP_DEI_QOS_MAP_CFG,
	REW_PTP_CFG,
	REW_PTP_DLY1_CFG,
	REW_RED_TAG_CFG,
	REW_DSCP_REMAP_DP1_CFG,
	REW_DSCP_REMAP_CFG,
	REW_STAT_CFG,
	REW_REW_STICKY,
	REW_PPT,
	SYS_COUNT_RX_OCTETS = SYS << TARGET_OFFSET,
	SYS_COUNT_RX_UNICAST,
	SYS_COUNT_RX_MULTICAST,
	SYS_COUNT_RX_BROADCAST,
	SYS_COUNT_RX_SHORTS,
	SYS_COUNT_RX_FRAGMENTS,
	SYS_COUNT_RX_JABBERS,
	SYS_COUNT_RX_CRC_ALIGN_ERRS,
	SYS_COUNT_RX_SYM_ERRS,
	SYS_COUNT_RX_64,
	SYS_COUNT_RX_65_127,
	SYS_COUNT_RX_128_255,
	SYS_COUNT_RX_256_1023,
	SYS_COUNT_RX_1024_1526,
	SYS_COUNT_RX_1527_MAX,
	SYS_COUNT_RX_PAUSE,
	SYS_COUNT_RX_CONTROL,
	SYS_COUNT_RX_LONGS,
	SYS_COUNT_RX_CLASSIFIED_DROPS,
	SYS_COUNT_TX_OCTETS,
	SYS_COUNT_TX_UNICAST,
	SYS_COUNT_TX_MULTICAST,
	SYS_COUNT_TX_BROADCAST,
	SYS_COUNT_TX_COLLISION,
	SYS_COUNT_TX_DROPS,
	SYS_COUNT_TX_PAUSE,
	SYS_COUNT_TX_64,
	SYS_COUNT_TX_65_127,
	SYS_COUNT_TX_128_511,
	SYS_COUNT_TX_512_1023,
	SYS_COUNT_TX_1024_1526,
	SYS_COUNT_TX_1527_MAX,
	SYS_COUNT_TX_AGING,
	SYS_RESET_CFG,
	SYS_SR_ETYPE_CFG,
	SYS_VLAN_ETYPE_CFG,
	SYS_PORT_MODE,
	SYS_FRONT_PORT_MODE,
	SYS_FRM_AGING,
	SYS_STAT_CFG,
	SYS_SW_STATUS,
	SYS_MISC_CFG,
	SYS_REW_MAC_HIGH_CFG,
	SYS_REW_MAC_LOW_CFG,
	SYS_TIMESTAMP_OFFSET,
	SYS_CMID,
	SYS_PAUSE_CFG,
	SYS_PAUSE_TOT_CFG,
	SYS_ATOP,
	SYS_ATOP_TOT_CFG,
	SYS_MAC_FC_CFG,
	SYS_MMGT,
	SYS_MMGT_FAST,
	SYS_EVENTS_DIF,
	SYS_EVENTS_CORE,
	SYS_CNT,
	SYS_PTP_STATUS,
	SYS_PTP_TXSTAMP,
	SYS_PTP_NXT,
	SYS_PTP_CFG,
	SYS_RAM_INIT,
	SYS_CM_ADDR,
	SYS_CM_DATA_WR,
	SYS_CM_DATA_RD,
	SYS_CM_OP,
	SYS_CM_DATA,
	PTP_PIN_CFG = PTP << TARGET_OFFSET,
	PTP_PIN_TOD_SEC_MSB,
	PTP_PIN_TOD_SEC_LSB,
	PTP_PIN_TOD_NSEC,
	PTP_PIN_WF_HIGH_PERIOD,
	PTP_PIN_WF_LOW_PERIOD,
	PTP_CFG_MISC,
	PTP_CLK_CFG_ADJ_CFG,
	PTP_CLK_CFG_ADJ_FREQ,
	GCB_SOFT_RST = GCB << TARGET_OFFSET,
	GCB_MIIM_MII_STATUS,
	GCB_MIIM_MII_CMD,
	GCB_MIIM_MII_DATA,
	DEV_CLOCK_CFG = DEV_GMII << TARGET_OFFSET,
	DEV_PORT_MISC,
	DEV_EVENTS,
	DEV_EEE_CFG,
	DEV_RX_PATH_DELAY,
	DEV_TX_PATH_DELAY,
	DEV_PTP_PREDICT_CFG,
	DEV_MAC_ENA_CFG,
	DEV_MAC_MODE_CFG,
	DEV_MAC_MAXLEN_CFG,
	DEV_MAC_TAGS_CFG,
	DEV_MAC_ADV_CHK_CFG,
	DEV_MAC_IFG_CFG,
	DEV_MAC_HDX_CFG,
	DEV_MAC_DBG_CFG,
	DEV_MAC_FC_MAC_LOW_CFG,
	DEV_MAC_FC_MAC_HIGH_CFG,
	DEV_MAC_STICKY,
	PCS1G_CFG,
	PCS1G_MODE_CFG,
	PCS1G_SD_CFG,
	PCS1G_ANEG_CFG,
	PCS1G_ANEG_NP_CFG,
	PCS1G_LB_CFG,
	PCS1G_DBG_CFG,
	PCS1G_CDET_CFG,
	PCS1G_ANEG_STATUS,
	PCS1G_ANEG_NP_STATUS,
	PCS1G_LINK_STATUS,
	PCS1G_LINK_DOWN_CNT,
	PCS1G_STICKY,
	PCS1G_DEBUG_STATUS,
	PCS1G_LPI_CFG,
	PCS1G_LPI_WAKE_ERROR_CNT,
	PCS1G_LPI_STATUS,
	PCS1G_TSTPAT_MODE_CFG,
	PCS1G_TSTPAT_STATUS,
	DEV_PCS_FX100_CFG,
	DEV_PCS_FX100_STATUS,
पूर्ण;

क्रमागत ocelot_regfield अणु
	ANA_ADVLEARN_VLAN_CHK,
	ANA_ADVLEARN_LEARN_MIRROR,
	ANA_ANEVENTS_FLOOD_DISCARD,
	ANA_ANEVENTS_MSTI_DROP,
	ANA_ANEVENTS_ACLKILL,
	ANA_ANEVENTS_ACLUSED,
	ANA_ANEVENTS_AUTOAGE,
	ANA_ANEVENTS_VS2TTL1,
	ANA_ANEVENTS_STORM_DROP,
	ANA_ANEVENTS_LEARN_DROP,
	ANA_ANEVENTS_AGED_ENTRY,
	ANA_ANEVENTS_CPU_LEARN_FAILED,
	ANA_ANEVENTS_AUTO_LEARN_FAILED,
	ANA_ANEVENTS_LEARN_REMOVE,
	ANA_ANEVENTS_AUTO_LEARNED,
	ANA_ANEVENTS_AUTO_MOVED,
	ANA_ANEVENTS_DROPPED,
	ANA_ANEVENTS_CLASSIFIED_DROP,
	ANA_ANEVENTS_CLASSIFIED_COPY,
	ANA_ANEVENTS_VLAN_DISCARD,
	ANA_ANEVENTS_FWD_DISCARD,
	ANA_ANEVENTS_MULTICAST_FLOOD,
	ANA_ANEVENTS_UNICAST_FLOOD,
	ANA_ANEVENTS_DEST_KNOWN,
	ANA_ANEVENTS_BUCKET3_MATCH,
	ANA_ANEVENTS_BUCKET2_MATCH,
	ANA_ANEVENTS_BUCKET1_MATCH,
	ANA_ANEVENTS_BUCKET0_MATCH,
	ANA_ANEVENTS_CPU_OPERATION,
	ANA_ANEVENTS_DMAC_LOOKUP,
	ANA_ANEVENTS_SMAC_LOOKUP,
	ANA_ANEVENTS_SEQ_GEN_ERR_0,
	ANA_ANEVENTS_SEQ_GEN_ERR_1,
	ANA_TABLES_MACACCESS_B_DOM,
	ANA_TABLES_MACTINDX_BUCKET,
	ANA_TABLES_MACTINDX_M_INDEX,
	QSYS_SWITCH_PORT_MODE_PORT_ENA,
	QSYS_SWITCH_PORT_MODE_SCH_NEXT_CFG,
	QSYS_SWITCH_PORT_MODE_YEL_RSRVD,
	QSYS_SWITCH_PORT_MODE_INGRESS_DROP_MODE,
	QSYS_SWITCH_PORT_MODE_TX_PFC_ENA,
	QSYS_SWITCH_PORT_MODE_TX_PFC_MODE,
	QSYS_TIMED_FRAME_ENTRY_TFRM_VLD,
	QSYS_TIMED_FRAME_ENTRY_TFRM_FP,
	QSYS_TIMED_FRAME_ENTRY_TFRM_PORTNO,
	QSYS_TIMED_FRAME_ENTRY_TFRM_TM_SEL,
	QSYS_TIMED_FRAME_ENTRY_TFRM_TM_T,
	SYS_PORT_MODE_DATA_WO_TS,
	SYS_PORT_MODE_INCL_INJ_HDR,
	SYS_PORT_MODE_INCL_XTR_HDR,
	SYS_PORT_MODE_INCL_HDR_ERR,
	SYS_RESET_CFG_CORE_ENA,
	SYS_RESET_CFG_MEM_ENA,
	SYS_RESET_CFG_MEM_INIT,
	GCB_SOFT_RST_SWC_RST,
	GCB_MIIM_MII_STATUS_PENDING,
	GCB_MIIM_MII_STATUS_BUSY,
	SYS_PAUSE_CFG_PAUSE_START,
	SYS_PAUSE_CFG_PAUSE_STOP,
	SYS_PAUSE_CFG_PAUSE_ENA,
	REGFIELD_MAX
पूर्ण;

क्रमागत अणु
	/* VCAP_CORE_CFG */
	VCAP_CORE_UPDATE_CTRL,
	VCAP_CORE_MV_CFG,
	/* VCAP_CORE_CACHE */
	VCAP_CACHE_ENTRY_DAT,
	VCAP_CACHE_MASK_DAT,
	VCAP_CACHE_ACTION_DAT,
	VCAP_CACHE_CNT_DAT,
	VCAP_CACHE_TG_DAT,
	/* VCAP_CONST */
	VCAP_CONST_VCAP_VER,
	VCAP_CONST_ENTRY_WIDTH,
	VCAP_CONST_ENTRY_CNT,
	VCAP_CONST_ENTRY_SWCNT,
	VCAP_CONST_ENTRY_TG_WIDTH,
	VCAP_CONST_ACTION_DEF_CNT,
	VCAP_CONST_ACTION_WIDTH,
	VCAP_CONST_CNT_WIDTH,
	VCAP_CONST_CORE_CNT,
	VCAP_CONST_IF_CNT,
पूर्ण;

क्रमागत ocelot_ptp_pins अणु
	PTP_PIN_0,
	PTP_PIN_1,
	PTP_PIN_2,
	PTP_PIN_3,
	TOD_ACC_PIN
पूर्ण;

काष्ठा ocelot_stat_layout अणु
	u32 offset;
	अक्षर name[ETH_GSTRING_LEN];
पूर्ण;

क्रमागत ocelot_tag_prefix अणु
	OCELOT_TAG_PREFIX_DISABLED	= 0,
	OCELOT_TAG_PREFIX_NONE,
	OCELOT_TAG_PREFIX_SHORT,
	OCELOT_TAG_PREFIX_LONG,
पूर्ण;

काष्ठा ocelot;

काष्ठा ocelot_ops अणु
	काष्ठा net_device *(*port_to_netdev)(काष्ठा ocelot *ocelot, पूर्णांक port);
	पूर्णांक (*netdev_to_port)(काष्ठा net_device *dev);
	पूर्णांक (*reset)(काष्ठा ocelot *ocelot);
	u16 (*wm_enc)(u16 value);
	u16 (*wm_dec)(u16 value);
	व्योम (*wm_stat)(u32 val, u32 *inuse, u32 *maxuse);
पूर्ण;

काष्ठा ocelot_vcap_block अणु
	काष्ठा list_head rules;
	पूर्णांक count;
	पूर्णांक pol_lpr;
पूर्ण;

काष्ठा ocelot_vlan अणु
	bool valid;
	u16 vid;
पूर्ण;

क्रमागत ocelot_sb अणु
	OCELOT_SB_BUF,
	OCELOT_SB_REF,
	OCELOT_SB_NUM,
पूर्ण;

क्रमागत ocelot_sb_pool अणु
	OCELOT_SB_POOL_ING,
	OCELOT_SB_POOL_EGR,
	OCELOT_SB_POOL_NUM,
पूर्ण;

काष्ठा ocelot_port अणु
	काष्ठा ocelot			*ocelot;

	काष्ठा regmap			*target;

	bool				vlan_aware;
	/* VLAN that untagged frames are classअगरied to, on ingress */
	काष्ठा ocelot_vlan		pvid_vlan;
	/* The VLAN ID that will be transmitted as untagged, on egress */
	काष्ठा ocelot_vlan		native_vlan;

	u8				ptp_cmd;
	काष्ठा sk_buff_head		tx_skbs;
	u8				ts_id;
	spinlock_t			ts_id_lock;

	phy_पूर्णांकerface_t			phy_mode;

	u8				*xmit_ढाँचा;
	bool				is_dsa_8021q_cpu;
	bool				learn_ena;

	काष्ठा net_device		*bond;
	bool				lag_tx_active;

	u16				mrp_ring_id;

	काष्ठा net_device		*bridge;
	u8				stp_state;
पूर्ण;

काष्ठा ocelot अणु
	काष्ठा device			*dev;
	काष्ठा devlink			*devlink;
	काष्ठा devlink_port		*devlink_ports;

	स्थिर काष्ठा ocelot_ops		*ops;
	काष्ठा regmap			*tarमाला_लो[TARGET_MAX];
	काष्ठा regmap_field		*regfields[REGFIELD_MAX];
	स्थिर u32 *स्थिर		*map;
	स्थिर काष्ठा ocelot_stat_layout	*stats_layout;
	अचिन्हित पूर्णांक			num_stats;

	u32				pool_size[OCELOT_SB_NUM][OCELOT_SB_POOL_NUM];
	पूर्णांक				packet_buffer_size;
	पूर्णांक				num_frame_refs;
	पूर्णांक				num_mact_rows;

	काष्ठा ocelot_port		**ports;

	u8				base_mac[ETH_ALEN];

	/* Keep track of the vlan port masks */
	u32				vlan_mask[VLAN_N_VID];

	/* Switches like VSC9959 have flooding per traffic class */
	पूर्णांक				num_flooding_pgids;

	/* In tables like ANA:PORT and the ANA:PGID:PGID mask,
	 * the CPU is located after the physical ports (at the
	 * num_phys_ports index).
	 */
	u8				num_phys_ports;

	पूर्णांक				npi;

	क्रमागत ocelot_tag_prefix		npi_inj_prefix;
	क्रमागत ocelot_tag_prefix		npi_xtr_prefix;

	काष्ठा list_head		multicast;
	काष्ठा list_head		pgids;

	काष्ठा list_head		dummy_rules;
	काष्ठा ocelot_vcap_block	block[3];
	काष्ठा vcap_props		*vcap;

	/* Workqueue to check statistics क्रम overflow with its lock */
	काष्ठा mutex			stats_lock;
	u64				*stats;
	काष्ठा delayed_work		stats_work;
	काष्ठा workqueue_काष्ठा		*stats_queue;

	काष्ठा workqueue_काष्ठा		*owq;

	u8				ptp:1;
	काष्ठा ptp_घड़ी		*ptp_घड़ी;
	काष्ठा ptp_घड़ी_info		ptp_info;
	काष्ठा hwtstamp_config		hwtstamp_config;
	/* Protects the PTP पूर्णांकerface state */
	काष्ठा mutex			ptp_lock;
	/* Protects the PTP घड़ी */
	spinlock_t			ptp_घड़ी_lock;
	काष्ठा ptp_pin_desc		ptp_pins[OCELOT_PTP_PINS_NUM];
पूर्ण;

काष्ठा ocelot_policer अणु
	u32 rate; /* kilobit per second */
	u32 burst; /* bytes */
पूर्ण;

काष्ठा ocelot_skb_cb अणु
	काष्ठा sk_buff *clone;
	u8 ptp_cmd;
	u8 ts_id;
पूर्ण;

#घोषणा OCELOT_SKB_CB(skb) \
	((काष्ठा ocelot_skb_cb *)((skb)->cb))

#घोषणा ocelot_पढ़ो_ix(ocelot, reg, gi, ri) __ocelot_पढ़ो_ix(ocelot, reg, reg##_GSZ * (gi) + reg##_RSZ * (ri))
#घोषणा ocelot_पढ़ो_gix(ocelot, reg, gi) __ocelot_पढ़ो_ix(ocelot, reg, reg##_GSZ * (gi))
#घोषणा ocelot_पढ़ो_rix(ocelot, reg, ri) __ocelot_पढ़ो_ix(ocelot, reg, reg##_RSZ * (ri))
#घोषणा ocelot_पढ़ो(ocelot, reg) __ocelot_पढ़ो_ix(ocelot, reg, 0)

#घोषणा ocelot_ग_लिखो_ix(ocelot, val, reg, gi, ri) __ocelot_ग_लिखो_ix(ocelot, val, reg, reg##_GSZ * (gi) + reg##_RSZ * (ri))
#घोषणा ocelot_ग_लिखो_gix(ocelot, val, reg, gi) __ocelot_ग_लिखो_ix(ocelot, val, reg, reg##_GSZ * (gi))
#घोषणा ocelot_ग_लिखो_rix(ocelot, val, reg, ri) __ocelot_ग_लिखो_ix(ocelot, val, reg, reg##_RSZ * (ri))
#घोषणा ocelot_ग_लिखो(ocelot, val, reg) __ocelot_ग_लिखो_ix(ocelot, val, reg, 0)

#घोषणा ocelot_rmw_ix(ocelot, val, m, reg, gi, ri) __ocelot_rmw_ix(ocelot, val, m, reg, reg##_GSZ * (gi) + reg##_RSZ * (ri))
#घोषणा ocelot_rmw_gix(ocelot, val, m, reg, gi) __ocelot_rmw_ix(ocelot, val, m, reg, reg##_GSZ * (gi))
#घोषणा ocelot_rmw_rix(ocelot, val, m, reg, ri) __ocelot_rmw_ix(ocelot, val, m, reg, reg##_RSZ * (ri))
#घोषणा ocelot_rmw(ocelot, val, m, reg) __ocelot_rmw_ix(ocelot, val, m, reg, 0)

#घोषणा ocelot_field_ग_लिखो(ocelot, reg, val) regmap_field_ग_लिखो((ocelot)->regfields[(reg)], (val))
#घोषणा ocelot_field_पढ़ो(ocelot, reg, val) regmap_field_पढ़ो((ocelot)->regfields[(reg)], (val))
#घोषणा ocelot_fields_ग_लिखो(ocelot, id, reg, val) regmap_fields_ग_लिखो((ocelot)->regfields[(reg)], (id), (val))
#घोषणा ocelot_fields_पढ़ो(ocelot, id, reg, val) regmap_fields_पढ़ो((ocelot)->regfields[(reg)], (id), (val))

#घोषणा ocelot_target_पढ़ो_ix(ocelot, target, reg, gi, ri) \
	__ocelot_target_पढ़ो_ix(ocelot, target, reg, reg##_GSZ * (gi) + reg##_RSZ * (ri))
#घोषणा ocelot_target_पढ़ो_gix(ocelot, target, reg, gi) \
	__ocelot_target_पढ़ो_ix(ocelot, target, reg, reg##_GSZ * (gi))
#घोषणा ocelot_target_पढ़ो_rix(ocelot, target, reg, ri) \
	__ocelot_target_पढ़ो_ix(ocelot, target, reg, reg##_RSZ * (ri))
#घोषणा ocelot_target_पढ़ो(ocelot, target, reg) \
	__ocelot_target_पढ़ो_ix(ocelot, target, reg, 0)

#घोषणा ocelot_target_ग_लिखो_ix(ocelot, target, val, reg, gi, ri) \
	__ocelot_target_ग_लिखो_ix(ocelot, target, val, reg, reg##_GSZ * (gi) + reg##_RSZ * (ri))
#घोषणा ocelot_target_ग_लिखो_gix(ocelot, target, val, reg, gi) \
	__ocelot_target_ग_लिखो_ix(ocelot, target, val, reg, reg##_GSZ * (gi))
#घोषणा ocelot_target_ग_लिखो_rix(ocelot, target, val, reg, ri) \
	__ocelot_target_ग_लिखो_ix(ocelot, target, val, reg, reg##_RSZ * (ri))
#घोषणा ocelot_target_ग_लिखो(ocelot, target, val, reg) \
	__ocelot_target_ग_लिखो_ix(ocelot, target, val, reg, 0)

/* I/O */
u32 ocelot_port_पढ़ोl(काष्ठा ocelot_port *port, u32 reg);
व्योम ocelot_port_ग_लिखोl(काष्ठा ocelot_port *port, u32 val, u32 reg);
व्योम ocelot_port_rmwl(काष्ठा ocelot_port *port, u32 val, u32 mask, u32 reg);
u32 __ocelot_पढ़ो_ix(काष्ठा ocelot *ocelot, u32 reg, u32 offset);
व्योम __ocelot_ग_लिखो_ix(काष्ठा ocelot *ocelot, u32 val, u32 reg, u32 offset);
व्योम __ocelot_rmw_ix(काष्ठा ocelot *ocelot, u32 val, u32 mask, u32 reg,
		     u32 offset);
u32 __ocelot_target_पढ़ो_ix(काष्ठा ocelot *ocelot, क्रमागत ocelot_target target,
			    u32 reg, u32 offset);
व्योम __ocelot_target_ग_लिखो_ix(काष्ठा ocelot *ocelot, क्रमागत ocelot_target target,
			      u32 val, u32 reg, u32 offset);

#अगर IS_ENABLED(CONFIG_MSCC_OCELOT_SWITCH_LIB)

/* Packet I/O */
bool ocelot_can_inject(काष्ठा ocelot *ocelot, पूर्णांक grp);
व्योम ocelot_port_inject_frame(काष्ठा ocelot *ocelot, पूर्णांक port, पूर्णांक grp,
			      u32 rew_op, काष्ठा sk_buff *skb);
पूर्णांक ocelot_xtr_poll_frame(काष्ठा ocelot *ocelot, पूर्णांक grp, काष्ठा sk_buff **skb);
व्योम ocelot_drain_cpu_queue(काष्ठा ocelot *ocelot, पूर्णांक grp);

u32 ocelot_ptp_rew_op(काष्ठा sk_buff *skb);
#अन्यथा

अटल अंतरभूत bool ocelot_can_inject(काष्ठा ocelot *ocelot, पूर्णांक grp)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम ocelot_port_inject_frame(काष्ठा ocelot *ocelot, पूर्णांक port,
					    पूर्णांक grp, u32 rew_op,
					    काष्ठा sk_buff *skb)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक ocelot_xtr_poll_frame(काष्ठा ocelot *ocelot, पूर्णांक grp,
					काष्ठा sk_buff **skb)
अणु
	वापस -EIO;
पूर्ण

अटल अंतरभूत व्योम ocelot_drain_cpu_queue(काष्ठा ocelot *ocelot, पूर्णांक grp)
अणु
पूर्ण

अटल अंतरभूत u32 ocelot_ptp_rew_op(काष्ठा sk_buff *skb)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/* Hardware initialization */
पूर्णांक ocelot_regfields_init(काष्ठा ocelot *ocelot,
			  स्थिर काष्ठा reg_field *स्थिर regfields);
काष्ठा regmap *ocelot_regmap_init(काष्ठा ocelot *ocelot, काष्ठा resource *res);
पूर्णांक ocelot_init(काष्ठा ocelot *ocelot);
व्योम ocelot_deinit(काष्ठा ocelot *ocelot);
व्योम ocelot_init_port(काष्ठा ocelot *ocelot, पूर्णांक port);
व्योम ocelot_deinit_port(काष्ठा ocelot *ocelot, पूर्णांक port);

/* DSA callbacks */
व्योम ocelot_port_enable(काष्ठा ocelot *ocelot, पूर्णांक port,
			काष्ठा phy_device *phy);
व्योम ocelot_port_disable(काष्ठा ocelot *ocelot, पूर्णांक port);
व्योम ocelot_get_strings(काष्ठा ocelot *ocelot, पूर्णांक port, u32 sset, u8 *data);
व्योम ocelot_get_ethtool_stats(काष्ठा ocelot *ocelot, पूर्णांक port, u64 *data);
पूर्णांक ocelot_get_sset_count(काष्ठा ocelot *ocelot, पूर्णांक port, पूर्णांक sset);
पूर्णांक ocelot_get_ts_info(काष्ठा ocelot *ocelot, पूर्णांक port,
		       काष्ठा ethtool_ts_info *info);
व्योम ocelot_set_ageing_समय(काष्ठा ocelot *ocelot, अचिन्हित पूर्णांक msecs);
पूर्णांक ocelot_port_flush(काष्ठा ocelot *ocelot, पूर्णांक port);
व्योम ocelot_adjust_link(काष्ठा ocelot *ocelot, पूर्णांक port,
			काष्ठा phy_device *phydev);
पूर्णांक ocelot_port_vlan_filtering(काष्ठा ocelot *ocelot, पूर्णांक port, bool enabled);
व्योम ocelot_bridge_stp_state_set(काष्ठा ocelot *ocelot, पूर्णांक port, u8 state);
व्योम ocelot_apply_bridge_fwd_mask(काष्ठा ocelot *ocelot);
पूर्णांक ocelot_port_pre_bridge_flags(काष्ठा ocelot *ocelot, पूर्णांक port,
				 काष्ठा चयनdev_brport_flags val);
व्योम ocelot_port_bridge_flags(काष्ठा ocelot *ocelot, पूर्णांक port,
			      काष्ठा चयनdev_brport_flags val);
व्योम ocelot_port_bridge_join(काष्ठा ocelot *ocelot, पूर्णांक port,
			     काष्ठा net_device *bridge);
व्योम ocelot_port_bridge_leave(काष्ठा ocelot *ocelot, पूर्णांक port,
			      काष्ठा net_device *bridge);
पूर्णांक ocelot_fdb_dump(काष्ठा ocelot *ocelot, पूर्णांक port,
		    dsa_fdb_dump_cb_t *cb, व्योम *data);
पूर्णांक ocelot_fdb_add(काष्ठा ocelot *ocelot, पूर्णांक port,
		   स्थिर अचिन्हित अक्षर *addr, u16 vid);
पूर्णांक ocelot_fdb_del(काष्ठा ocelot *ocelot, पूर्णांक port,
		   स्थिर अचिन्हित अक्षर *addr, u16 vid);
पूर्णांक ocelot_vlan_prepare(काष्ठा ocelot *ocelot, पूर्णांक port, u16 vid, bool pvid,
			bool untagged);
पूर्णांक ocelot_vlan_add(काष्ठा ocelot *ocelot, पूर्णांक port, u16 vid, bool pvid,
		    bool untagged);
पूर्णांक ocelot_vlan_del(काष्ठा ocelot *ocelot, पूर्णांक port, u16 vid);
पूर्णांक ocelot_hwstamp_get(काष्ठा ocelot *ocelot, पूर्णांक port, काष्ठा अगरreq *अगरr);
पूर्णांक ocelot_hwstamp_set(काष्ठा ocelot *ocelot, पूर्णांक port, काष्ठा अगरreq *अगरr);
पूर्णांक ocelot_port_txtstamp_request(काष्ठा ocelot *ocelot, पूर्णांक port,
				 काष्ठा sk_buff *skb,
				 काष्ठा sk_buff **clone);
व्योम ocelot_get_txtstamp(काष्ठा ocelot *ocelot);
व्योम ocelot_port_set_maxlen(काष्ठा ocelot *ocelot, पूर्णांक port, माप_प्रकार sdu);
पूर्णांक ocelot_get_max_mtu(काष्ठा ocelot *ocelot, पूर्णांक port);
पूर्णांक ocelot_port_policer_add(काष्ठा ocelot *ocelot, पूर्णांक port,
			    काष्ठा ocelot_policer *pol);
पूर्णांक ocelot_port_policer_del(काष्ठा ocelot *ocelot, पूर्णांक port);
पूर्णांक ocelot_cls_flower_replace(काष्ठा ocelot *ocelot, पूर्णांक port,
			      काष्ठा flow_cls_offload *f, bool ingress);
पूर्णांक ocelot_cls_flower_destroy(काष्ठा ocelot *ocelot, पूर्णांक port,
			      काष्ठा flow_cls_offload *f, bool ingress);
पूर्णांक ocelot_cls_flower_stats(काष्ठा ocelot *ocelot, पूर्णांक port,
			    काष्ठा flow_cls_offload *f, bool ingress);
पूर्णांक ocelot_port_mdb_add(काष्ठा ocelot *ocelot, पूर्णांक port,
			स्थिर काष्ठा चयनdev_obj_port_mdb *mdb);
पूर्णांक ocelot_port_mdb_del(काष्ठा ocelot *ocelot, पूर्णांक port,
			स्थिर काष्ठा चयनdev_obj_port_mdb *mdb);
पूर्णांक ocelot_port_lag_join(काष्ठा ocelot *ocelot, पूर्णांक port,
			 काष्ठा net_device *bond,
			 काष्ठा netdev_lag_upper_info *info);
व्योम ocelot_port_lag_leave(काष्ठा ocelot *ocelot, पूर्णांक port,
			   काष्ठा net_device *bond);
व्योम ocelot_port_lag_change(काष्ठा ocelot *ocelot, पूर्णांक port, bool lag_tx_active);

पूर्णांक ocelot_devlink_sb_रेजिस्टर(काष्ठा ocelot *ocelot);
व्योम ocelot_devlink_sb_unरेजिस्टर(काष्ठा ocelot *ocelot);
पूर्णांक ocelot_sb_pool_get(काष्ठा ocelot *ocelot, अचिन्हित पूर्णांक sb_index,
		       u16 pool_index,
		       काष्ठा devlink_sb_pool_info *pool_info);
पूर्णांक ocelot_sb_pool_set(काष्ठा ocelot *ocelot, अचिन्हित पूर्णांक sb_index,
		       u16 pool_index, u32 size,
		       क्रमागत devlink_sb_threshold_type threshold_type,
		       काष्ठा netlink_ext_ack *extack);
पूर्णांक ocelot_sb_port_pool_get(काष्ठा ocelot *ocelot, पूर्णांक port,
			    अचिन्हित पूर्णांक sb_index, u16 pool_index,
			    u32 *p_threshold);
पूर्णांक ocelot_sb_port_pool_set(काष्ठा ocelot *ocelot, पूर्णांक port,
			    अचिन्हित पूर्णांक sb_index, u16 pool_index,
			    u32 threshold, काष्ठा netlink_ext_ack *extack);
पूर्णांक ocelot_sb_tc_pool_bind_get(काष्ठा ocelot *ocelot, पूर्णांक port,
			       अचिन्हित पूर्णांक sb_index, u16 tc_index,
			       क्रमागत devlink_sb_pool_type pool_type,
			       u16 *p_pool_index, u32 *p_threshold);
पूर्णांक ocelot_sb_tc_pool_bind_set(काष्ठा ocelot *ocelot, पूर्णांक port,
			       अचिन्हित पूर्णांक sb_index, u16 tc_index,
			       क्रमागत devlink_sb_pool_type pool_type,
			       u16 pool_index, u32 threshold,
			       काष्ठा netlink_ext_ack *extack);
पूर्णांक ocelot_sb_occ_snapshot(काष्ठा ocelot *ocelot, अचिन्हित पूर्णांक sb_index);
पूर्णांक ocelot_sb_occ_max_clear(काष्ठा ocelot *ocelot, अचिन्हित पूर्णांक sb_index);
पूर्णांक ocelot_sb_occ_port_pool_get(काष्ठा ocelot *ocelot, पूर्णांक port,
				अचिन्हित पूर्णांक sb_index, u16 pool_index,
				u32 *p_cur, u32 *p_max);
पूर्णांक ocelot_sb_occ_tc_port_bind_get(काष्ठा ocelot *ocelot, पूर्णांक port,
				   अचिन्हित पूर्णांक sb_index, u16 tc_index,
				   क्रमागत devlink_sb_pool_type pool_type,
				   u32 *p_cur, u32 *p_max);

#अगर IS_ENABLED(CONFIG_BRIDGE_MRP)
पूर्णांक ocelot_mrp_add(काष्ठा ocelot *ocelot, पूर्णांक port,
		   स्थिर काष्ठा चयनdev_obj_mrp *mrp);
पूर्णांक ocelot_mrp_del(काष्ठा ocelot *ocelot, पूर्णांक port,
		   स्थिर काष्ठा चयनdev_obj_mrp *mrp);
पूर्णांक ocelot_mrp_add_ring_role(काष्ठा ocelot *ocelot, पूर्णांक port,
			     स्थिर काष्ठा चयनdev_obj_ring_role_mrp *mrp);
पूर्णांक ocelot_mrp_del_ring_role(काष्ठा ocelot *ocelot, पूर्णांक port,
			     स्थिर काष्ठा चयनdev_obj_ring_role_mrp *mrp);
#अन्यथा
अटल अंतरभूत पूर्णांक ocelot_mrp_add(काष्ठा ocelot *ocelot, पूर्णांक port,
				 स्थिर काष्ठा चयनdev_obj_mrp *mrp)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक ocelot_mrp_del(काष्ठा ocelot *ocelot, पूर्णांक port,
				 स्थिर काष्ठा चयनdev_obj_mrp *mrp)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक
ocelot_mrp_add_ring_role(काष्ठा ocelot *ocelot, पूर्णांक port,
			 स्थिर काष्ठा चयनdev_obj_ring_role_mrp *mrp)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक
ocelot_mrp_del_ring_role(काष्ठा ocelot *ocelot, पूर्णांक port,
			 स्थिर काष्ठा चयनdev_obj_ring_role_mrp *mrp)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
