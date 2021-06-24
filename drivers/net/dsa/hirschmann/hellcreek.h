<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 or MIT) */
/*
 * DSA driver क्रम:
 * Hirschmann Hellcreek TSN चयन.
 *
 * Copyright (C) 2019-2021 Linutronix GmbH
 * Author Kurt Kanzenbach <kurt@linutronix.de>
 */

#अगर_अघोषित _HELLCREEK_H_
#घोषणा _HELLCREEK_H_

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mutex.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/leds.h>
#समावेश <linux/platक्रमm_data/hirschmann-hellcreek.h>
#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <linux/समयcounter.h>
#समावेश <net/dsa.h>
#समावेश <net/pkt_sched.h>

/* Ports:
 *  - 0: CPU
 *  - 1: Tunnel
 *  - 2: TSN front port 1
 *  - 3: TSN front port 2
 *  - ...
 */
#घोषणा CPU_PORT			0
#घोषणा TUNNEL_PORT			1

#घोषणा HELLCREEK_VLAN_NO_MEMBER	0x0
#घोषणा HELLCREEK_VLAN_UNTAGGED_MEMBER	0x1
#घोषणा HELLCREEK_VLAN_TAGGED_MEMBER	0x3
#घोषणा HELLCREEK_NUM_EGRESS_QUEUES	8

/* Register definitions */
#घोषणा HR_MODID_C			(0 * 2)
#घोषणा HR_REL_L_C			(1 * 2)
#घोषणा HR_REL_H_C			(2 * 2)
#घोषणा HR_BLD_L_C			(3 * 2)
#घोषणा HR_BLD_H_C			(4 * 2)
#घोषणा HR_CTRL_C			(5 * 2)
#घोषणा HR_CTRL_C_READY			BIT(14)
#घोषणा HR_CTRL_C_TRANSITION		BIT(13)
#घोषणा HR_CTRL_C_ENABLE		BIT(0)

#घोषणा HR_PSEL				(0xa6 * 2)
#घोषणा HR_PSEL_PTWSEL_SHIFT		4
#घोषणा HR_PSEL_PTWSEL_MASK		GENMASK(5, 4)
#घोषणा HR_PSEL_PRTCWSEL_SHIFT		0
#घोषणा HR_PSEL_PRTCWSEL_MASK		GENMASK(2, 0)

#घोषणा HR_PTCFG			(0xa7 * 2)
#घोषणा HR_PTCFG_MLIMIT_EN		BIT(13)
#घोषणा HR_PTCFG_UMC_FLT		BIT(10)
#घोषणा HR_PTCFG_UUC_FLT		BIT(9)
#घोषणा HR_PTCFG_UNTRUST		BIT(8)
#घोषणा HR_PTCFG_TAG_REQUIRED		BIT(7)
#घोषणा HR_PTCFG_PPRIO_SHIFT		4
#घोषणा HR_PTCFG_PPRIO_MASK		GENMASK(6, 4)
#घोषणा HR_PTCFG_INGRESSFLT		BIT(3)
#घोषणा HR_PTCFG_BLOCKED		BIT(2)
#घोषणा HR_PTCFG_LEARNING_EN		BIT(1)
#घोषणा HR_PTCFG_ADMIN_EN		BIT(0)

#घोषणा HR_PRTCCFG			(0xa8 * 2)
#घोषणा HR_PRTCCFG_PCP_TC_MAP_SHIFT	0
#घोषणा HR_PRTCCFG_PCP_TC_MAP_MASK	GENMASK(2, 0)

#घोषणा HR_CSEL				(0x8d * 2)
#घोषणा HR_CSEL_SHIFT			0
#घोषणा HR_CSEL_MASK			GENMASK(7, 0)
#घोषणा HR_CRDL				(0x8e * 2)
#घोषणा HR_CRDH				(0x8f * 2)

#घोषणा HR_SWTRC_CFG			(0x90 * 2)
#घोषणा HR_SWTRC0			(0x91 * 2)
#घोषणा HR_SWTRC1			(0x92 * 2)
#घोषणा HR_PFREE			(0x93 * 2)
#घोषणा HR_MFREE			(0x94 * 2)

#घोषणा HR_FDBAGE			(0x97 * 2)
#घोषणा HR_FDBMAX			(0x98 * 2)
#घोषणा HR_FDBRDL			(0x99 * 2)
#घोषणा HR_FDBRDM			(0x9a * 2)
#घोषणा HR_FDBRDH			(0x9b * 2)

#घोषणा HR_FDBMDRD			(0x9c * 2)
#घोषणा HR_FDBMDRD_PORTMASK_SHIFT	0
#घोषणा HR_FDBMDRD_PORTMASK_MASK	GENMASK(3, 0)
#घोषणा HR_FDBMDRD_AGE_SHIFT		4
#घोषणा HR_FDBMDRD_AGE_MASK		GENMASK(7, 4)
#घोषणा HR_FDBMDRD_OBT			BIT(8)
#घोषणा HR_FDBMDRD_PASS_BLOCKED		BIT(9)
#घोषणा HR_FDBMDRD_STATIC		BIT(11)
#घोषणा HR_FDBMDRD_REPRIO_TC_SHIFT	12
#घोषणा HR_FDBMDRD_REPRIO_TC_MASK	GENMASK(14, 12)
#घोषणा HR_FDBMDRD_REPRIO_EN		BIT(15)

#घोषणा HR_FDBWDL			(0x9d * 2)
#घोषणा HR_FDBWDM			(0x9e * 2)
#घोषणा HR_FDBWDH			(0x9f * 2)
#घोषणा HR_FDBWRM0			(0xa0 * 2)
#घोषणा HR_FDBWRM0_PORTMASK_SHIFT	0
#घोषणा HR_FDBWRM0_PORTMASK_MASK	GENMASK(3, 0)
#घोषणा HR_FDBWRM0_OBT			BIT(8)
#घोषणा HR_FDBWRM0_PASS_BLOCKED		BIT(9)
#घोषणा HR_FDBWRM0_REPRIO_TC_SHIFT	12
#घोषणा HR_FDBWRM0_REPRIO_TC_MASK	GENMASK(14, 12)
#घोषणा HR_FDBWRM0_REPRIO_EN		BIT(15)
#घोषणा HR_FDBWRM1			(0xa1 * 2)

#घोषणा HR_FDBWRCMD			(0xa2 * 2)
#घोषणा HR_FDBWRCMD_FDBDEL		BIT(9)

#घोषणा HR_SWCFG			(0xa3 * 2)
#घोषणा HR_SWCFG_GM_STATEMD		BIT(15)
#घोषणा HR_SWCFG_LAS_MODE_SHIFT		12
#घोषणा HR_SWCFG_LAS_MODE_MASK		GENMASK(13, 12)
#घोषणा HR_SWCFG_LAS_OFF		(0x00)
#घोषणा HR_SWCFG_LAS_ON			(0x01)
#घोषणा HR_SWCFG_LAS_STATIC		(0x10)
#घोषणा HR_SWCFG_CT_EN			BIT(11)
#घोषणा HR_SWCFG_VLAN_UNAWARE		BIT(10)
#घोषणा HR_SWCFG_ALWAYS_OBT		BIT(9)
#घोषणा HR_SWCFG_FDBAGE_EN		BIT(5)
#घोषणा HR_SWCFG_FDBLRN_EN		BIT(4)

#घोषणा HR_SWSTAT			(0xa4 * 2)
#घोषणा HR_SWSTAT_FAIL			BIT(4)
#घोषणा HR_SWSTAT_BUSY			BIT(0)

#घोषणा HR_SWCMD			(0xa5 * 2)
#घोषणा HW_SWCMD_FLUSH			BIT(0)

#घोषणा HR_VIDCFG			(0xaa * 2)
#घोषणा HR_VIDCFG_VID_SHIFT		0
#घोषणा HR_VIDCFG_VID_MASK		GENMASK(11, 0)
#घोषणा HR_VIDCFG_PVID			BIT(12)

#घोषणा HR_VIDMBRCFG			(0xab * 2)
#घोषणा HR_VIDMBRCFG_P0MBR_SHIFT	0
#घोषणा HR_VIDMBRCFG_P0MBR_MASK		GENMASK(1, 0)
#घोषणा HR_VIDMBRCFG_P1MBR_SHIFT	2
#घोषणा HR_VIDMBRCFG_P1MBR_MASK		GENMASK(3, 2)
#घोषणा HR_VIDMBRCFG_P2MBR_SHIFT	4
#घोषणा HR_VIDMBRCFG_P2MBR_MASK		GENMASK(5, 4)
#घोषणा HR_VIDMBRCFG_P3MBR_SHIFT	6
#घोषणा HR_VIDMBRCFG_P3MBR_MASK		GENMASK(7, 6)

#घोषणा HR_FEABITS0			(0xac * 2)
#घोषणा HR_FEABITS0_FDBBINS_SHIFT	4
#घोषणा HR_FEABITS0_FDBBINS_MASK	GENMASK(7, 4)
#घोषणा HR_FEABITS0_PCNT_SHIFT		8
#घोषणा HR_FEABITS0_PCNT_MASK		GENMASK(11, 8)
#घोषणा HR_FEABITS0_MCNT_SHIFT		12
#घोषणा HR_FEABITS0_MCNT_MASK		GENMASK(15, 12)

#घोषणा TR_QTRACK			(0xb1 * 2)
#घोषणा TR_TGDVER			(0xb3 * 2)
#घोषणा TR_TGDVER_REV_MIN_MASK		GENMASK(7, 0)
#घोषणा TR_TGDVER_REV_MIN_SHIFT		0
#घोषणा TR_TGDVER_REV_MAJ_MASK		GENMASK(15, 8)
#घोषणा TR_TGDVER_REV_MAJ_SHIFT		8
#घोषणा TR_TGDSEL			(0xb4 * 2)
#घोषणा TR_TGDSEL_TDGSEL_MASK		GENMASK(1, 0)
#घोषणा TR_TGDSEL_TDGSEL_SHIFT		0
#घोषणा TR_TGDCTRL			(0xb5 * 2)
#घोषणा TR_TGDCTRL_GATE_EN		BIT(0)
#घोषणा TR_TGDCTRL_CYC_SNAP		BIT(4)
#घोषणा TR_TGDCTRL_SNAP_EST		BIT(5)
#घोषणा TR_TGDCTRL_ADMINGATESTATES_MASK	GENMASK(15, 8)
#घोषणा TR_TGDCTRL_ADMINGATESTATES_SHIFT	8
#घोषणा TR_TGDSTAT0			(0xb6 * 2)
#घोषणा TR_TGDSTAT1			(0xb7 * 2)
#घोषणा TR_ESTWRL			(0xb8 * 2)
#घोषणा TR_ESTWRH			(0xb9 * 2)
#घोषणा TR_ESTCMD			(0xba * 2)
#घोषणा TR_ESTCMD_ESTSEC_MASK		GENMASK(2, 0)
#घोषणा TR_ESTCMD_ESTSEC_SHIFT		0
#घोषणा TR_ESTCMD_ESTARM		BIT(4)
#घोषणा TR_ESTCMD_ESTSWCFG		BIT(5)
#घोषणा TR_EETWRL			(0xbb * 2)
#घोषणा TR_EETWRH			(0xbc * 2)
#घोषणा TR_EETCMD			(0xbd * 2)
#घोषणा TR_EETCMD_EETSEC_MASK		GEMASK(2, 0)
#घोषणा TR_EETCMD_EETSEC_SHIFT		0
#घोषणा TR_EETCMD_EETARM		BIT(4)
#घोषणा TR_CTWRL			(0xbe * 2)
#घोषणा TR_CTWRH			(0xbf * 2)
#घोषणा TR_LCNSL			(0xc1 * 2)
#घोषणा TR_LCNSH			(0xc2 * 2)
#घोषणा TR_LCS				(0xc3 * 2)
#घोषणा TR_GCLDAT			(0xc4 * 2)
#घोषणा TR_GCLDAT_GCLWRGATES_MASK	GENMASK(7, 0)
#घोषणा TR_GCLDAT_GCLWRGATES_SHIFT	0
#घोषणा TR_GCLDAT_GCLWRLAST		BIT(8)
#घोषणा TR_GCLDAT_GCLOVRI		BIT(9)
#घोषणा TR_GCLTIL			(0xc5 * 2)
#घोषणा TR_GCLTIH			(0xc6 * 2)
#घोषणा TR_GCLCMD			(0xc7 * 2)
#घोषणा TR_GCLCMD_GCLWRADR_MASK		GENMASK(7, 0)
#घोषणा TR_GCLCMD_GCLWRADR_SHIFT	0
#घोषणा TR_GCLCMD_INIT_GATE_STATES_MASK	GENMASK(15, 8)
#घोषणा TR_GCLCMD_INIT_GATE_STATES_SHIFT	8

काष्ठा hellcreek_counter अणु
	u8 offset;
	स्थिर अक्षर *name;
पूर्ण;

काष्ठा hellcreek;

/* State flags क्रम hellcreek_port_hwtstamp::state */
क्रमागत अणु
	HELLCREEK_HWTSTAMP_ENABLED,
	HELLCREEK_HWTSTAMP_TX_IN_PROGRESS,
पूर्ण;

/* A काष्ठाure to hold hardware बारtamping inक्रमmation per port */
काष्ठा hellcreek_port_hwtstamp अणु
	/* Timestamping state */
	अचिन्हित दीर्घ state;

	/* Resources क्रम receive बारtamping */
	काष्ठा sk_buff_head rx_queue; /* For synchronization messages */

	/* Resources क्रम transmit बारtamping */
	अचिन्हित दीर्घ tx_tstamp_start;
	काष्ठा sk_buff *tx_skb;

	/* Current बारtamp configuration */
	काष्ठा hwtstamp_config tstamp_config;
पूर्ण;

काष्ठा hellcreek_port अणु
	काष्ठा hellcreek *hellcreek;
	अचिन्हित दीर्घ *vlan_dev_biपंचांगap;
	पूर्णांक port;
	u16 ptcfg;		/* ptcfg shaकरोw */
	u64 *counter_values;

	/* Per-port बारtamping resources */
	काष्ठा hellcreek_port_hwtstamp port_hwtstamp;

	/* Per-port Qbv schedule inक्रमmation */
	काष्ठा tc_taprio_qopt_offload *current_schedule;
	काष्ठा delayed_work schedule_work;
पूर्ण;

काष्ठा hellcreek_fdb_entry अणु
	माप_प्रकार idx;
	अचिन्हित अक्षर mac[ETH_ALEN];
	u8 porपंचांगask;
	u8 age;
	u8 is_obt;
	u8 pass_blocked;
	u8 is_अटल;
	u8 reprio_tc;
	u8 reprio_en;
पूर्ण;

काष्ठा hellcreek अणु
	स्थिर काष्ठा hellcreek_platक्रमm_data *pdata;
	काष्ठा device *dev;
	काष्ठा dsa_चयन *ds;
	काष्ठा ptp_घड़ी *ptp_घड़ी;
	काष्ठा ptp_घड़ी_info ptp_घड़ी_info;
	काष्ठा hellcreek_port *ports;
	काष्ठा delayed_work overflow_work;
	काष्ठा led_classdev led_is_gm;
	काष्ठा led_classdev led_sync_good;
	काष्ठा mutex reg_lock;	/* Switch IP रेजिस्टर lock */
	काष्ठा mutex vlan_lock;	/* VLAN biपंचांगaps lock */
	काष्ठा mutex ptp_lock;	/* PTP IP रेजिस्टर lock */
	काष्ठा devlink_region *vlan_region;
	काष्ठा devlink_region *fdb_region;
	व्योम __iomem *base;
	व्योम __iomem *ptp_base;
	u16 swcfg;		/* swcfg shaकरोw */
	u8 *vidmbrcfg;		/* vidmbrcfg shaकरोw */
	u64 seconds;		/* PTP seconds */
	u64 last_ts;		/* Used क्रम overflow detection */
	u16 status_out;		/* ptp.status_out shaकरोw */
	माप_प्रकार fdb_entries;
पूर्ण;

/* A Qbv schedule can only started up to 8 seconds in the future. If the delta
 * between the base समय and the current ptp समय is larger than 8 seconds, then
 * use periodic work to check क्रम the schedule to be started. The delayed work
 * cannot be armed directly to $base_समय - 8 + X, because क्रम large deltas the
 * PTP frequency matters.
 */
#घोषणा HELLCREEK_SCHEDULE_PERIOD	(2 * HZ)
#घोषणा dw_to_hellcreek_port(dw)				\
	container_of(dw, काष्ठा hellcreek_port, schedule_work)

/* Devlink resources */
क्रमागत hellcreek_devlink_resource_id अणु
	HELLCREEK_DEVLINK_PARAM_ID_VLAN_TABLE,
	HELLCREEK_DEVLINK_PARAM_ID_FDB_TABLE,
पूर्ण;

काष्ठा hellcreek_devlink_vlan_entry अणु
	u16 vid;
	u16 member;
पूर्ण;

#पूर्ण_अगर /* _HELLCREEK_H_ */
