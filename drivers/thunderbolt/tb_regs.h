<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Thunderbolt driver - Port/Switch config area रेजिस्टरs
 *
 * Every thunderbolt device consists (logically) of a चयन with multiple
 * ports. Every port contains up to four config regions (HOPS, PORT, SWITCH,
 * COUNTERS) which are used to configure the device.
 *
 * Copyright (c) 2014 Andreas Noever <andreas.noever@gmail.com>
 * Copyright (C) 2018, Intel Corporation
 */

#अगर_अघोषित _TB_REGS
#घोषणा _TB_REGS

#समावेश <linux/types.h>


#घोषणा TB_ROUTE_SHIFT 8  /* number of bits in a port entry of a route */


/*
 * TODO: should be 63? But we करो not know how to receive frames larger than 256
 * bytes at the frame level. (header + checksum = 16, 60*4 = 240)
 */
#घोषणा TB_MAX_CONFIG_RW_LENGTH 60

क्रमागत tb_चयन_cap अणु
	TB_SWITCH_CAP_TMU		= 0x03,
	TB_SWITCH_CAP_VSE		= 0x05,
पूर्ण;

क्रमागत tb_चयन_vse_cap अणु
	TB_VSE_CAP_PLUG_EVENTS		= 0x01, /* also EEPROM */
	TB_VSE_CAP_TIME2		= 0x03,
	TB_VSE_CAP_IECS			= 0x04,
	TB_VSE_CAP_LINK_CONTROLLER	= 0x06, /* also IECS */
पूर्ण;

क्रमागत tb_port_cap अणु
	TB_PORT_CAP_PHY			= 0x01,
	TB_PORT_CAP_POWER		= 0x02,
	TB_PORT_CAP_TIME1		= 0x03,
	TB_PORT_CAP_ADAP		= 0x04,
	TB_PORT_CAP_VSE			= 0x05,
	TB_PORT_CAP_USB4		= 0x06,
पूर्ण;

क्रमागत tb_port_state अणु
	TB_PORT_DISABLED	= 0, /* tb_cap_phy.disable == 1 */
	TB_PORT_CONNECTING	= 1, /* retry */
	TB_PORT_UP		= 2,
	TB_PORT_UNPLUGGED	= 7,
पूर्ण;

/* capability headers */

काष्ठा tb_cap_basic अणु
	u8 next;
	/* क्रमागत tb_cap cap:8; prevent "narrower than values of its type" */
	u8 cap; /* अगर cap == 0x05 then we have a extended capability */
पूर्ण __packed;

/**
 * काष्ठा tb_cap_extended_लघु - Switch extended लघु capability
 * @next: Poपूर्णांकer to the next capability. If @next and @length are zero
 *	  then we have a दीर्घ cap.
 * @cap: Base capability ID (see &क्रमागत tb_चयन_cap)
 * @vsec_id: Venकरोr specअगरic capability ID (see &क्रमागत चयन_vse_cap)
 * @length: Length of this capability
 */
काष्ठा tb_cap_extended_लघु अणु
	u8 next;
	u8 cap;
	u8 vsec_id;
	u8 length;
पूर्ण __packed;

/**
 * काष्ठा tb_cap_extended_दीर्घ - Switch extended दीर्घ capability
 * @zero1: This field should be zero
 * @cap: Base capability ID (see &क्रमागत tb_चयन_cap)
 * @vsec_id: Venकरोr specअगरic capability ID (see &क्रमागत चयन_vse_cap)
 * @zero2: This field should be zero
 * @next: Poपूर्णांकer to the next capability
 * @length: Length of this capability
 */
काष्ठा tb_cap_extended_दीर्घ अणु
	u8 zero1;
	u8 cap;
	u8 vsec_id;
	u8 zero2;
	u16 next;
	u16 length;
पूर्ण __packed;

/**
 * काष्ठा tb_cap_any - Structure capable of hold every capability
 * @basic: Basic capability
 * @extended_लघु: Venकरोr specअगरic capability
 * @extended_दीर्घ: Venकरोr specअगरic extended capability
 */
काष्ठा tb_cap_any अणु
	जोड़ अणु
		काष्ठा tb_cap_basic basic;
		काष्ठा tb_cap_extended_लघु extended_लघु;
		काष्ठा tb_cap_extended_दीर्घ extended_दीर्घ;
	पूर्ण;
पूर्ण __packed;

/* capabilities */

काष्ठा tb_cap_link_controller अणु
	काष्ठा tb_cap_extended_दीर्घ cap_header;
	u32 count:4; /* number of link controllers */
	u32 unknown1:4;
	u32 base_offset:8; /*
			    * offset (पूर्णांकo this capability) of the configuration
			    * area of the first link controller
			    */
	u32 length:12; /* link controller configuration area length */
	u32 unknown2:4; /* TODO check that length is correct */
पूर्ण __packed;

काष्ठा tb_cap_phy अणु
	काष्ठा tb_cap_basic cap_header;
	u32 unknown1:16;
	u32 unknown2:14;
	bool disable:1;
	u32 unknown3:11;
	क्रमागत tb_port_state state:4;
	u32 unknown4:2;
पूर्ण __packed;

काष्ठा tb_eeprom_ctl अणु
	bool घड़ी:1; /* send pulse to transfer one bit */
	bool access_low:1; /* set to 0 beक्रमe access */
	bool data_out:1; /* to eeprom */
	bool data_in:1; /* from eeprom */
	bool access_high:1; /* set to 1 beक्रमe access */
	bool not_present:1; /* should be 0 */
	bool unknown1:1;
	bool present:1; /* should be 1 */
	u32 unknown2:24;
पूर्ण __packed;

काष्ठा tb_cap_plug_events अणु
	काष्ठा tb_cap_extended_लघु cap_header;
	u32 __unknown1:2;
	u32 plug_events:5;
	u32 __unknown2:25;
	u32 __unknown3;
	u32 __unknown4;
	काष्ठा tb_eeprom_ctl eeprom_ctl;
	u32 __unknown5[7];
	u32 drom_offset; /* 32 bit रेजिस्टर, but eeprom addresses are 16 bit */
पूर्ण __packed;

/* device headers */

/* Present on port 0 in TB_CFG_SWITCH at address zero. */
काष्ठा tb_regs_चयन_header अणु
	/* DWORD 0 */
	u16 venकरोr_id;
	u16 device_id;
	/* DWORD 1 */
	u32 first_cap_offset:8;
	u32 upstream_port_number:6;
	u32 max_port_number:6;
	u32 depth:3;
	u32 __unknown1:1;
	u32 revision:8;
	/* DWORD 2 */
	u32 route_lo;
	/* DWORD 3 */
	u32 route_hi:31;
	bool enabled:1;
	/* DWORD 4 */
	u32 plug_events_delay:8; /*
				  * RW, छोड़ो between plug events in
				  * milliseconds. Writing 0x00 is पूर्णांकerpreted
				  * as 255ms.
				  */
	u32 cmuv:8;
	u32 __unknown4:8;
	u32 thunderbolt_version:8;
पूर्ण __packed;

/* USB4 version 1.0 */
#घोषणा USB4_VERSION_1_0			0x20

#घोषणा ROUTER_CS_1				0x01
#घोषणा ROUTER_CS_4				0x04
#घोषणा ROUTER_CS_5				0x05
#घोषणा ROUTER_CS_5_SLP				BIT(0)
#घोषणा ROUTER_CS_5_WOP				BIT(1)
#घोषणा ROUTER_CS_5_WOU				BIT(2)
#घोषणा ROUTER_CS_5_C3S				BIT(23)
#घोषणा ROUTER_CS_5_PTO				BIT(24)
#घोषणा ROUTER_CS_5_UTO				BIT(25)
#घोषणा ROUTER_CS_5_HCO				BIT(26)
#घोषणा ROUTER_CS_5_CV				BIT(31)
#घोषणा ROUTER_CS_6				0x06
#घोषणा ROUTER_CS_6_SLPR			BIT(0)
#घोषणा ROUTER_CS_6_TNS				BIT(1)
#घोषणा ROUTER_CS_6_WOPS			BIT(2)
#घोषणा ROUTER_CS_6_WOUS			BIT(3)
#घोषणा ROUTER_CS_6_HCI				BIT(18)
#घोषणा ROUTER_CS_6_CR				BIT(25)
#घोषणा ROUTER_CS_7				0x07
#घोषणा ROUTER_CS_9				0x09
#घोषणा ROUTER_CS_25				0x19
#घोषणा ROUTER_CS_26				0x1a
#घोषणा ROUTER_CS_26_OPCODE_MASK		GENMASK(15, 0)
#घोषणा ROUTER_CS_26_STATUS_MASK		GENMASK(29, 24)
#घोषणा ROUTER_CS_26_STATUS_SHIFT		24
#घोषणा ROUTER_CS_26_ONS			BIT(30)
#घोषणा ROUTER_CS_26_OV				BIT(31)

/* USB4 router operations opcodes */
क्रमागत usb4_चयन_op अणु
	USB4_SWITCH_OP_QUERY_DP_RESOURCE = 0x10,
	USB4_SWITCH_OP_ALLOC_DP_RESOURCE = 0x11,
	USB4_SWITCH_OP_DEALLOC_DP_RESOURCE = 0x12,
	USB4_SWITCH_OP_NVM_WRITE = 0x20,
	USB4_SWITCH_OP_NVM_AUTH = 0x21,
	USB4_SWITCH_OP_NVM_READ = 0x22,
	USB4_SWITCH_OP_NVM_SET_OFFSET = 0x23,
	USB4_SWITCH_OP_DROM_READ = 0x24,
	USB4_SWITCH_OP_NVM_SECTOR_SIZE = 0x25,
पूर्ण;

/* Router TMU configuration */
#घोषणा TMU_RTR_CS_0				0x00
#घोषणा TMU_RTR_CS_0_TD				BIT(27)
#घोषणा TMU_RTR_CS_0_UCAP			BIT(30)
#घोषणा TMU_RTR_CS_1				0x01
#घोषणा TMU_RTR_CS_1_LOCAL_TIME_NS_MASK		GENMASK(31, 16)
#घोषणा TMU_RTR_CS_1_LOCAL_TIME_NS_SHIFT	16
#घोषणा TMU_RTR_CS_2				0x02
#घोषणा TMU_RTR_CS_3				0x03
#घोषणा TMU_RTR_CS_3_LOCAL_TIME_NS_MASK		GENMASK(15, 0)
#घोषणा TMU_RTR_CS_3_TS_PACKET_INTERVAL_MASK	GENMASK(31, 16)
#घोषणा TMU_RTR_CS_3_TS_PACKET_INTERVAL_SHIFT	16
#घोषणा TMU_RTR_CS_22				0x16
#घोषणा TMU_RTR_CS_24				0x18

क्रमागत tb_port_type अणु
	TB_TYPE_INACTIVE	= 0x000000,
	TB_TYPE_PORT		= 0x000001,
	TB_TYPE_NHI		= 0x000002,
	/* TB_TYPE_ETHERNET	= 0x020000, lower order bits are not known */
	/* TB_TYPE_SATA		= 0x080000, lower order bits are not known */
	TB_TYPE_DP_HDMI_IN	= 0x0e0101,
	TB_TYPE_DP_HDMI_OUT	= 0x0e0102,
	TB_TYPE_PCIE_DOWN	= 0x100101,
	TB_TYPE_PCIE_UP		= 0x100102,
	TB_TYPE_USB3_DOWN	= 0x200101,
	TB_TYPE_USB3_UP		= 0x200102,
पूर्ण;

/* Present on every port in TB_CF_PORT at address zero. */
काष्ठा tb_regs_port_header अणु
	/* DWORD 0 */
	u16 venकरोr_id;
	u16 device_id;
	/* DWORD 1 */
	u32 first_cap_offset:8;
	u32 max_counters:11;
	u32 counters_support:1;
	u32 __unknown1:4;
	u32 revision:8;
	/* DWORD 2 */
	क्रमागत tb_port_type type:24;
	u32 thunderbolt_version:8;
	/* DWORD 3 */
	u32 __unknown2:20;
	u32 port_number:6;
	u32 __unknown3:6;
	/* DWORD 4 */
	u32 nfc_credits;
	/* DWORD 5 */
	u32 max_in_hop_id:11;
	u32 max_out_hop_id:11;
	u32 __unknown4:10;
	/* DWORD 6 */
	u32 __unknown5;
	/* DWORD 7 */
	u32 __unknown6;

पूर्ण __packed;

/* Basic adapter configuration रेजिस्टरs */
#घोषणा ADP_CS_4				0x04
#घोषणा ADP_CS_4_NFC_BUFFERS_MASK		GENMASK(9, 0)
#घोषणा ADP_CS_4_TOTAL_BUFFERS_MASK		GENMASK(29, 20)
#घोषणा ADP_CS_4_TOTAL_BUFFERS_SHIFT		20
#घोषणा ADP_CS_4_LCK				BIT(31)
#घोषणा ADP_CS_5				0x05
#घोषणा ADP_CS_5_LCA_MASK			GENMASK(28, 22)
#घोषणा ADP_CS_5_LCA_SHIFT			22

/* TMU adapter रेजिस्टरs */
#घोषणा TMU_ADP_CS_3				0x03
#घोषणा TMU_ADP_CS_3_UDM			BIT(29)

/* Lane adapter रेजिस्टरs */
#घोषणा LANE_ADP_CS_0				0x00
#घोषणा LANE_ADP_CS_0_SUPPORTED_WIDTH_MASK	GENMASK(25, 20)
#घोषणा LANE_ADP_CS_0_SUPPORTED_WIDTH_SHIFT	20
#घोषणा LANE_ADP_CS_1				0x01
#घोषणा LANE_ADP_CS_1_TARGET_WIDTH_MASK		GENMASK(9, 4)
#घोषणा LANE_ADP_CS_1_TARGET_WIDTH_SHIFT	4
#घोषणा LANE_ADP_CS_1_TARGET_WIDTH_SINGLE	0x1
#घोषणा LANE_ADP_CS_1_TARGET_WIDTH_DUAL		0x3
#घोषणा LANE_ADP_CS_1_LD			BIT(14)
#घोषणा LANE_ADP_CS_1_LB			BIT(15)
#घोषणा LANE_ADP_CS_1_CURRENT_SPEED_MASK	GENMASK(19, 16)
#घोषणा LANE_ADP_CS_1_CURRENT_SPEED_SHIFT	16
#घोषणा LANE_ADP_CS_1_CURRENT_SPEED_GEN2	0x8
#घोषणा LANE_ADP_CS_1_CURRENT_SPEED_GEN3	0x4
#घोषणा LANE_ADP_CS_1_CURRENT_WIDTH_MASK	GENMASK(25, 20)
#घोषणा LANE_ADP_CS_1_CURRENT_WIDTH_SHIFT	20

/* USB4 port रेजिस्टरs */
#घोषणा PORT_CS_1				0x01
#घोषणा PORT_CS_1_LENGTH_SHIFT			8
#घोषणा PORT_CS_1_TARGET_MASK			GENMASK(18, 16)
#घोषणा PORT_CS_1_TARGET_SHIFT			16
#घोषणा PORT_CS_1_RETIMER_INDEX_SHIFT		20
#घोषणा PORT_CS_1_WNR_WRITE			BIT(24)
#घोषणा PORT_CS_1_NR				BIT(25)
#घोषणा PORT_CS_1_RC				BIT(26)
#घोषणा PORT_CS_1_PND				BIT(31)
#घोषणा PORT_CS_2				0x02
#घोषणा PORT_CS_18				0x12
#घोषणा PORT_CS_18_BE				BIT(8)
#घोषणा PORT_CS_18_TCM				BIT(9)
#घोषणा PORT_CS_18_WOU4S			BIT(18)
#घोषणा PORT_CS_19				0x13
#घोषणा PORT_CS_19_PC				BIT(3)
#घोषणा PORT_CS_19_PID				BIT(4)
#घोषणा PORT_CS_19_WOC				BIT(16)
#घोषणा PORT_CS_19_WOD				BIT(17)
#घोषणा PORT_CS_19_WOU4				BIT(18)

/* Display Port adapter रेजिस्टरs */
#घोषणा ADP_DP_CS_0				0x00
#घोषणा ADP_DP_CS_0_VIDEO_HOPID_MASK		GENMASK(26, 16)
#घोषणा ADP_DP_CS_0_VIDEO_HOPID_SHIFT		16
#घोषणा ADP_DP_CS_0_AE				BIT(30)
#घोषणा ADP_DP_CS_0_VE				BIT(31)
#घोषणा ADP_DP_CS_1_AUX_TX_HOPID_MASK		GENMASK(10, 0)
#घोषणा ADP_DP_CS_1_AUX_RX_HOPID_MASK		GENMASK(21, 11)
#घोषणा ADP_DP_CS_1_AUX_RX_HOPID_SHIFT		11
#घोषणा ADP_DP_CS_2				0x02
#घोषणा ADP_DP_CS_2_HDP				BIT(6)
#घोषणा ADP_DP_CS_3				0x03
#घोषणा ADP_DP_CS_3_HDPC			BIT(9)
#घोषणा DP_LOCAL_CAP				0x04
#घोषणा DP_REMOTE_CAP				0x05
#घोषणा DP_STATUS_CTRL				0x06
#घोषणा DP_STATUS_CTRL_CMHS			BIT(25)
#घोषणा DP_STATUS_CTRL_UF			BIT(26)
#घोषणा DP_COMMON_CAP				0x07
/*
 * DP_COMMON_CAP offsets work also क्रम DP_LOCAL_CAP and DP_REMOTE_CAP
 * with exception of DPRX करोne.
 */
#घोषणा DP_COMMON_CAP_RATE_MASK			GENMASK(11, 8)
#घोषणा DP_COMMON_CAP_RATE_SHIFT		8
#घोषणा DP_COMMON_CAP_RATE_RBR			0x0
#घोषणा DP_COMMON_CAP_RATE_HBR			0x1
#घोषणा DP_COMMON_CAP_RATE_HBR2			0x2
#घोषणा DP_COMMON_CAP_RATE_HBR3			0x3
#घोषणा DP_COMMON_CAP_LANES_MASK		GENMASK(14, 12)
#घोषणा DP_COMMON_CAP_LANES_SHIFT		12
#घोषणा DP_COMMON_CAP_1_LANE			0x0
#घोषणा DP_COMMON_CAP_2_LANES			0x1
#घोषणा DP_COMMON_CAP_4_LANES			0x2
#घोषणा DP_COMMON_CAP_DPRX_DONE			BIT(31)

/* PCIe adapter रेजिस्टरs */
#घोषणा ADP_PCIE_CS_0				0x00
#घोषणा ADP_PCIE_CS_0_PE			BIT(31)

/* USB adapter रेजिस्टरs */
#घोषणा ADP_USB3_CS_0				0x00
#घोषणा ADP_USB3_CS_0_V				BIT(30)
#घोषणा ADP_USB3_CS_0_PE			BIT(31)
#घोषणा ADP_USB3_CS_1				0x01
#घोषणा ADP_USB3_CS_1_CUBW_MASK			GENMASK(11, 0)
#घोषणा ADP_USB3_CS_1_CDBW_MASK			GENMASK(23, 12)
#घोषणा ADP_USB3_CS_1_CDBW_SHIFT		12
#घोषणा ADP_USB3_CS_1_HCA			BIT(31)
#घोषणा ADP_USB3_CS_2				0x02
#घोषणा ADP_USB3_CS_2_AUBW_MASK			GENMASK(11, 0)
#घोषणा ADP_USB3_CS_2_ADBW_MASK			GENMASK(23, 12)
#घोषणा ADP_USB3_CS_2_ADBW_SHIFT		12
#घोषणा ADP_USB3_CS_2_CMR			BIT(31)
#घोषणा ADP_USB3_CS_3				0x03
#घोषणा ADP_USB3_CS_3_SCALE_MASK		GENMASK(5, 0)
#घोषणा ADP_USB3_CS_4				0x04
#घोषणा ADP_USB3_CS_4_ALR_MASK			GENMASK(6, 0)
#घोषणा ADP_USB3_CS_4_ALR_20G			0x1
#घोषणा ADP_USB3_CS_4_ULV			BIT(7)
#घोषणा ADP_USB3_CS_4_MSLR_MASK			GENMASK(18, 12)
#घोषणा ADP_USB3_CS_4_MSLR_SHIFT		12
#घोषणा ADP_USB3_CS_4_MSLR_20G			0x1

/* Hop रेजिस्टर from TB_CFG_HOPS. 8 byte per entry. */
काष्ठा tb_regs_hop अणु
	/* DWORD 0 */
	u32 next_hop:11; /*
			  * hop to take after sending the packet through
			  * out_port (on the incoming port of the next चयन)
			  */
	u32 out_port:6; /* next port of the path (on the same चयन) */
	u32 initial_credits:8;
	u32 unknown1:6; /* set to zero */
	bool enable:1;

	/* DWORD 1 */
	u32 weight:4;
	u32 unknown2:4; /* set to zero */
	u32 priority:3;
	bool drop_packages:1;
	u32 counter:11; /* index पूर्णांकo TB_CFG_COUNTERS on this port */
	bool counter_enable:1;
	bool ingress_fc:1;
	bool egress_fc:1;
	bool ingress_shared_buffer:1;
	bool egress_shared_buffer:1;
	bool pending:1;
	u32 unknown3:3; /* set to zero */
पूर्ण __packed;

/* Common link controller रेजिस्टरs */
#घोषणा TB_LC_DESC			0x02
#घोषणा TB_LC_DESC_NLC_MASK		GENMASK(3, 0)
#घोषणा TB_LC_DESC_SIZE_SHIFT		8
#घोषणा TB_LC_DESC_SIZE_MASK		GENMASK(15, 8)
#घोषणा TB_LC_DESC_PORT_SIZE_SHIFT	16
#घोषणा TB_LC_DESC_PORT_SIZE_MASK	GENMASK(27, 16)
#घोषणा TB_LC_FUSE			0x03
#घोषणा TB_LC_SNK_ALLOCATION		0x10
#घोषणा TB_LC_SNK_ALLOCATION_SNK0_MASK	GENMASK(3, 0)
#घोषणा TB_LC_SNK_ALLOCATION_SNK0_CM	0x1
#घोषणा TB_LC_SNK_ALLOCATION_SNK1_SHIFT	4
#घोषणा TB_LC_SNK_ALLOCATION_SNK1_MASK	GENMASK(7, 4)
#घोषणा TB_LC_SNK_ALLOCATION_SNK1_CM	0x1
#घोषणा TB_LC_POWER			0x740

/* Link controller रेजिस्टरs */
#घोषणा TB_LC_PORT_ATTR			0x8d
#घोषणा TB_LC_PORT_ATTR_BE		BIT(12)

#घोषणा TB_LC_SX_CTRL			0x96
#घोषणा TB_LC_SX_CTRL_WOC		BIT(1)
#घोषणा TB_LC_SX_CTRL_WOD		BIT(2)
#घोषणा TB_LC_SX_CTRL_WOU4		BIT(5)
#घोषणा TB_LC_SX_CTRL_WOP		BIT(6)
#घोषणा TB_LC_SX_CTRL_L1C		BIT(16)
#घोषणा TB_LC_SX_CTRL_L1D		BIT(17)
#घोषणा TB_LC_SX_CTRL_L2C		BIT(20)
#घोषणा TB_LC_SX_CTRL_L2D		BIT(21)
#घोषणा TB_LC_SX_CTRL_SLI		BIT(29)
#घोषणा TB_LC_SX_CTRL_UPSTREAM		BIT(30)
#घोषणा TB_LC_SX_CTRL_SLP		BIT(31)

#पूर्ण_अगर
