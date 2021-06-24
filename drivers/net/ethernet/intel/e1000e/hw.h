<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#अगर_अघोषित _E1000E_HW_H_
#घोषणा _E1000E_HW_H_

#समावेश "regs.h"
#समावेश "defines.h"

काष्ठा e1000_hw;

#घोषणा E1000_DEV_ID_82571EB_COPPER		0x105E
#घोषणा E1000_DEV_ID_82571EB_FIBER		0x105F
#घोषणा E1000_DEV_ID_82571EB_SERDES		0x1060
#घोषणा E1000_DEV_ID_82571EB_QUAD_COPPER	0x10A4
#घोषणा E1000_DEV_ID_82571PT_QUAD_COPPER	0x10D5
#घोषणा E1000_DEV_ID_82571EB_QUAD_FIBER		0x10A5
#घोषणा E1000_DEV_ID_82571EB_QUAD_COPPER_LP	0x10BC
#घोषणा E1000_DEV_ID_82571EB_SERDES_DUAL	0x10D9
#घोषणा E1000_DEV_ID_82571EB_SERDES_QUAD	0x10DA
#घोषणा E1000_DEV_ID_82572EI_COPPER		0x107D
#घोषणा E1000_DEV_ID_82572EI_FIBER		0x107E
#घोषणा E1000_DEV_ID_82572EI_SERDES		0x107F
#घोषणा E1000_DEV_ID_82572EI			0x10B9
#घोषणा E1000_DEV_ID_82573E			0x108B
#घोषणा E1000_DEV_ID_82573E_IAMT		0x108C
#घोषणा E1000_DEV_ID_82573L			0x109A
#घोषणा E1000_DEV_ID_82574L			0x10D3
#घोषणा E1000_DEV_ID_82574LA			0x10F6
#घोषणा E1000_DEV_ID_82583V			0x150C
#घोषणा E1000_DEV_ID_80003ES2LAN_COPPER_DPT	0x1096
#घोषणा E1000_DEV_ID_80003ES2LAN_SERDES_DPT	0x1098
#घोषणा E1000_DEV_ID_80003ES2LAN_COPPER_SPT	0x10BA
#घोषणा E1000_DEV_ID_80003ES2LAN_SERDES_SPT	0x10BB
#घोषणा E1000_DEV_ID_ICH8_82567V_3		0x1501
#घोषणा E1000_DEV_ID_ICH8_IGP_M_AMT		0x1049
#घोषणा E1000_DEV_ID_ICH8_IGP_AMT		0x104A
#घोषणा E1000_DEV_ID_ICH8_IGP_C			0x104B
#घोषणा E1000_DEV_ID_ICH8_IFE			0x104C
#घोषणा E1000_DEV_ID_ICH8_IFE_GT		0x10C4
#घोषणा E1000_DEV_ID_ICH8_IFE_G			0x10C5
#घोषणा E1000_DEV_ID_ICH8_IGP_M			0x104D
#घोषणा E1000_DEV_ID_ICH9_IGP_AMT		0x10BD
#घोषणा E1000_DEV_ID_ICH9_BM			0x10E5
#घोषणा E1000_DEV_ID_ICH9_IGP_M_AMT		0x10F5
#घोषणा E1000_DEV_ID_ICH9_IGP_M			0x10BF
#घोषणा E1000_DEV_ID_ICH9_IGP_M_V		0x10CB
#घोषणा E1000_DEV_ID_ICH9_IGP_C			0x294C
#घोषणा E1000_DEV_ID_ICH9_IFE			0x10C0
#घोषणा E1000_DEV_ID_ICH9_IFE_GT		0x10C3
#घोषणा E1000_DEV_ID_ICH9_IFE_G			0x10C2
#घोषणा E1000_DEV_ID_ICH10_R_BM_LM		0x10CC
#घोषणा E1000_DEV_ID_ICH10_R_BM_LF		0x10CD
#घोषणा E1000_DEV_ID_ICH10_R_BM_V		0x10CE
#घोषणा E1000_DEV_ID_ICH10_D_BM_LM		0x10DE
#घोषणा E1000_DEV_ID_ICH10_D_BM_LF		0x10DF
#घोषणा E1000_DEV_ID_ICH10_D_BM_V		0x1525
#घोषणा E1000_DEV_ID_PCH_M_HV_LM		0x10EA
#घोषणा E1000_DEV_ID_PCH_M_HV_LC		0x10EB
#घोषणा E1000_DEV_ID_PCH_D_HV_DM		0x10EF
#घोषणा E1000_DEV_ID_PCH_D_HV_DC		0x10F0
#घोषणा E1000_DEV_ID_PCH2_LV_LM			0x1502
#घोषणा E1000_DEV_ID_PCH2_LV_V			0x1503
#घोषणा E1000_DEV_ID_PCH_LPT_I217_LM		0x153A
#घोषणा E1000_DEV_ID_PCH_LPT_I217_V		0x153B
#घोषणा E1000_DEV_ID_PCH_LPTLP_I218_LM		0x155A
#घोषणा E1000_DEV_ID_PCH_LPTLP_I218_V		0x1559
#घोषणा E1000_DEV_ID_PCH_I218_LM2		0x15A0
#घोषणा E1000_DEV_ID_PCH_I218_V2		0x15A1
#घोषणा E1000_DEV_ID_PCH_I218_LM3		0x15A2	/* Wildcat Poपूर्णांक PCH */
#घोषणा E1000_DEV_ID_PCH_I218_V3		0x15A3	/* Wildcat Poपूर्णांक PCH */
#घोषणा E1000_DEV_ID_PCH_SPT_I219_LM		0x156F	/* SPT PCH */
#घोषणा E1000_DEV_ID_PCH_SPT_I219_V		0x1570	/* SPT PCH */
#घोषणा E1000_DEV_ID_PCH_SPT_I219_LM2		0x15B7	/* SPT-H PCH */
#घोषणा E1000_DEV_ID_PCH_SPT_I219_V2		0x15B8	/* SPT-H PCH */
#घोषणा E1000_DEV_ID_PCH_LBG_I219_LM3		0x15B9	/* LBG PCH */
#घोषणा E1000_DEV_ID_PCH_SPT_I219_LM4		0x15D7
#घोषणा E1000_DEV_ID_PCH_SPT_I219_V4		0x15D8
#घोषणा E1000_DEV_ID_PCH_SPT_I219_LM5		0x15E3
#घोषणा E1000_DEV_ID_PCH_SPT_I219_V5		0x15D6
#घोषणा E1000_DEV_ID_PCH_CNP_I219_LM6		0x15BD
#घोषणा E1000_DEV_ID_PCH_CNP_I219_V6		0x15BE
#घोषणा E1000_DEV_ID_PCH_CNP_I219_LM7		0x15BB
#घोषणा E1000_DEV_ID_PCH_CNP_I219_V7		0x15BC
#घोषणा E1000_DEV_ID_PCH_ICP_I219_LM8		0x15DF
#घोषणा E1000_DEV_ID_PCH_ICP_I219_V8		0x15E0
#घोषणा E1000_DEV_ID_PCH_ICP_I219_LM9		0x15E1
#घोषणा E1000_DEV_ID_PCH_ICP_I219_V9		0x15E2
#घोषणा E1000_DEV_ID_PCH_CMP_I219_LM10		0x0D4E
#घोषणा E1000_DEV_ID_PCH_CMP_I219_V10		0x0D4F
#घोषणा E1000_DEV_ID_PCH_CMP_I219_LM11		0x0D4C
#घोषणा E1000_DEV_ID_PCH_CMP_I219_V11		0x0D4D
#घोषणा E1000_DEV_ID_PCH_CMP_I219_LM12		0x0D53
#घोषणा E1000_DEV_ID_PCH_CMP_I219_V12		0x0D55
#घोषणा E1000_DEV_ID_PCH_TGP_I219_LM13		0x15FB
#घोषणा E1000_DEV_ID_PCH_TGP_I219_V13		0x15FC
#घोषणा E1000_DEV_ID_PCH_TGP_I219_LM14		0x15F9
#घोषणा E1000_DEV_ID_PCH_TGP_I219_V14		0x15FA
#घोषणा E1000_DEV_ID_PCH_TGP_I219_LM15		0x15F4
#घोषणा E1000_DEV_ID_PCH_TGP_I219_V15		0x15F5
#घोषणा E1000_DEV_ID_PCH_ADP_I219_LM16		0x1A1E
#घोषणा E1000_DEV_ID_PCH_ADP_I219_V16		0x1A1F
#घोषणा E1000_DEV_ID_PCH_ADP_I219_LM17		0x1A1C
#घोषणा E1000_DEV_ID_PCH_ADP_I219_V17		0x1A1D
#घोषणा E1000_DEV_ID_PCH_MTP_I219_LM18		0x550A
#घोषणा E1000_DEV_ID_PCH_MTP_I219_V18		0x550B
#घोषणा E1000_DEV_ID_PCH_MTP_I219_LM19		0x550C
#घोषणा E1000_DEV_ID_PCH_MTP_I219_V19		0x550D

#घोषणा E1000_REVISION_4	4

#घोषणा E1000_FUNC_1		1

#घोषणा E1000_ALT_MAC_ADDRESS_OFFSET_LAN0	0
#घोषणा E1000_ALT_MAC_ADDRESS_OFFSET_LAN1	3

क्रमागत e1000_mac_type अणु
	e1000_82571,
	e1000_82572,
	e1000_82573,
	e1000_82574,
	e1000_82583,
	e1000_80003es2lan,
	e1000_ich8lan,
	e1000_ich9lan,
	e1000_ich10lan,
	e1000_pchlan,
	e1000_pch2lan,
	e1000_pch_lpt,
	e1000_pch_spt,
	e1000_pch_cnp,
	e1000_pch_tgp,
	e1000_pch_adp,
	e1000_pch_mtp,
पूर्ण;

क्रमागत e1000_media_type अणु
	e1000_media_type_unknown = 0,
	e1000_media_type_copper = 1,
	e1000_media_type_fiber = 2,
	e1000_media_type_पूर्णांकernal_serdes = 3,
	e1000_num_media_types
पूर्ण;

क्रमागत e1000_nvm_type अणु
	e1000_nvm_unknown = 0,
	e1000_nvm_none,
	e1000_nvm_eeprom_spi,
	e1000_nvm_flash_hw,
	e1000_nvm_flash_sw
पूर्ण;

क्रमागत e1000_nvm_override अणु
	e1000_nvm_override_none = 0,
	e1000_nvm_override_spi_small,
	e1000_nvm_override_spi_large
पूर्ण;

क्रमागत e1000_phy_type अणु
	e1000_phy_unknown = 0,
	e1000_phy_none,
	e1000_phy_m88,
	e1000_phy_igp,
	e1000_phy_igp_2,
	e1000_phy_gg82563,
	e1000_phy_igp_3,
	e1000_phy_अगरe,
	e1000_phy_bm,
	e1000_phy_82578,
	e1000_phy_82577,
	e1000_phy_82579,
	e1000_phy_i217,
पूर्ण;

क्रमागत e1000_bus_width अणु
	e1000_bus_width_unknown = 0,
	e1000_bus_width_pcie_x1,
	e1000_bus_width_pcie_x2,
	e1000_bus_width_pcie_x4 = 4,
	e1000_bus_width_pcie_x8 = 8,
	e1000_bus_width_32,
	e1000_bus_width_64,
	e1000_bus_width_reserved
पूर्ण;

क्रमागत e1000_1000t_rx_status अणु
	e1000_1000t_rx_status_not_ok = 0,
	e1000_1000t_rx_status_ok,
	e1000_1000t_rx_status_undefined = 0xFF
पूर्ण;

क्रमागत e1000_rev_polarity अणु
	e1000_rev_polarity_normal = 0,
	e1000_rev_polarity_reversed,
	e1000_rev_polarity_undefined = 0xFF
पूर्ण;

क्रमागत e1000_fc_mode अणु
	e1000_fc_none = 0,
	e1000_fc_rx_छोड़ो,
	e1000_fc_tx_छोड़ो,
	e1000_fc_full,
	e1000_fc_शेष = 0xFF
पूर्ण;

क्रमागत e1000_ms_type अणु
	e1000_ms_hw_शेष = 0,
	e1000_ms_क्रमce_master,
	e1000_ms_क्रमce_slave,
	e1000_ms_स्वतः
पूर्ण;

क्रमागत e1000_smart_speed अणु
	e1000_smart_speed_शेष = 0,
	e1000_smart_speed_on,
	e1000_smart_speed_off
पूर्ण;

क्रमागत e1000_serdes_link_state अणु
	e1000_serdes_link_करोwn = 0,
	e1000_serdes_link_स्वतःneg_progress,
	e1000_serdes_link_स्वतःneg_complete,
	e1000_serdes_link_क्रमced_up
पूर्ण;

/* Receive Descriptor - Extended */
जोड़ e1000_rx_desc_extended अणु
	काष्ठा अणु
		__le64 buffer_addr;
		__le64 reserved;
	पूर्ण पढ़ो;
	काष्ठा अणु
		काष्ठा अणु
			__le32 mrq;	      /* Multiple Rx Queues */
			जोड़ अणु
				__le32 rss;	    /* RSS Hash */
				काष्ठा अणु
					__le16 ip_id;  /* IP id */
					__le16 csum;   /* Packet Checksum */
				पूर्ण csum_ip;
			पूर्ण hi_dword;
		पूर्ण lower;
		काष्ठा अणु
			__le32 status_error;     /* ext status/error */
			__le16 length;
			__le16 vlan;	     /* VLAN tag */
		पूर्ण upper;
	पूर्ण wb;  /* ग_लिखोback */
पूर्ण;

#घोषणा MAX_PS_BUFFERS 4

/* Number of packet split data buffers (not including the header buffer) */
#घोषणा PS_PAGE_BUFFERS	(MAX_PS_BUFFERS - 1)

/* Receive Descriptor - Packet Split */
जोड़ e1000_rx_desc_packet_split अणु
	काष्ठा अणु
		/* one buffer क्रम protocol header(s), three data buffers */
		__le64 buffer_addr[MAX_PS_BUFFERS];
	पूर्ण पढ़ो;
	काष्ठा अणु
		काष्ठा अणु
			__le32 mrq;	      /* Multiple Rx Queues */
			जोड़ अणु
				__le32 rss;	      /* RSS Hash */
				काष्ठा अणु
					__le16 ip_id;    /* IP id */
					__le16 csum;     /* Packet Checksum */
				पूर्ण csum_ip;
			पूर्ण hi_dword;
		पूर्ण lower;
		काष्ठा अणु
			__le32 status_error;     /* ext status/error */
			__le16 length0;	  /* length of buffer 0 */
			__le16 vlan;	     /* VLAN tag */
		पूर्ण middle;
		काष्ठा अणु
			__le16 header_status;
			/* length of buffers 1-3 */
			__le16 length[PS_PAGE_BUFFERS];
		पूर्ण upper;
		__le64 reserved;
	पूर्ण wb; /* ग_लिखोback */
पूर्ण;

/* Transmit Descriptor */
काष्ठा e1000_tx_desc अणु
	__le64 buffer_addr;      /* Address of the descriptor's data buffer */
	जोड़ अणु
		__le32 data;
		काष्ठा अणु
			__le16 length;    /* Data buffer length */
			u8 cso;	/* Checksum offset */
			u8 cmd;	/* Descriptor control */
		पूर्ण flags;
	पूर्ण lower;
	जोड़ अणु
		__le32 data;
		काष्ठा अणु
			u8 status;     /* Descriptor status */
			u8 css;	/* Checksum start */
			__le16 special;
		पूर्ण fields;
	पूर्ण upper;
पूर्ण;

/* Offload Context Descriptor */
काष्ठा e1000_context_desc अणु
	जोड़ अणु
		__le32 ip_config;
		काष्ठा अणु
			u8 ipcss;      /* IP checksum start */
			u8 ipcso;      /* IP checksum offset */
			__le16 ipcse;     /* IP checksum end */
		पूर्ण ip_fields;
	पूर्ण lower_setup;
	जोड़ अणु
		__le32 tcp_config;
		काष्ठा अणु
			u8 tucss;      /* TCP checksum start */
			u8 tucso;      /* TCP checksum offset */
			__le16 tucse;     /* TCP checksum end */
		पूर्ण tcp_fields;
	पूर्ण upper_setup;
	__le32 cmd_and_length;
	जोड़ अणु
		__le32 data;
		काष्ठा अणु
			u8 status;     /* Descriptor status */
			u8 hdr_len;    /* Header length */
			__le16 mss;       /* Maximum segment size */
		पूर्ण fields;
	पूर्ण tcp_seg_setup;
पूर्ण;

/* Offload data descriptor */
काष्ठा e1000_data_desc अणु
	__le64 buffer_addr;   /* Address of the descriptor's buffer address */
	जोड़ अणु
		__le32 data;
		काष्ठा अणु
			__le16 length;    /* Data buffer length */
			u8 typ_len_ext;
			u8 cmd;
		पूर्ण flags;
	पूर्ण lower;
	जोड़ अणु
		__le32 data;
		काष्ठा अणु
			u8 status;     /* Descriptor status */
			u8 popts;      /* Packet Options */
			__le16 special;
		पूर्ण fields;
	पूर्ण upper;
पूर्ण;

/* Statistics counters collected by the MAC */
काष्ठा e1000_hw_stats अणु
	u64 crcerrs;
	u64 algnerrc;
	u64 symerrs;
	u64 rxerrc;
	u64 mpc;
	u64 scc;
	u64 ecol;
	u64 mcc;
	u64 latecol;
	u64 colc;
	u64 dc;
	u64 tncrs;
	u64 sec;
	u64 cexterr;
	u64 rlec;
	u64 xonrxc;
	u64 xontxc;
	u64 xoffrxc;
	u64 xofftxc;
	u64 fcruc;
	u64 prc64;
	u64 prc127;
	u64 prc255;
	u64 prc511;
	u64 prc1023;
	u64 prc1522;
	u64 gprc;
	u64 bprc;
	u64 mprc;
	u64 gptc;
	u64 gorc;
	u64 gotc;
	u64 rnbc;
	u64 ruc;
	u64 rfc;
	u64 roc;
	u64 rjc;
	u64 mgprc;
	u64 mgpdc;
	u64 mgptc;
	u64 tor;
	u64 tot;
	u64 tpr;
	u64 tpt;
	u64 ptc64;
	u64 ptc127;
	u64 ptc255;
	u64 ptc511;
	u64 ptc1023;
	u64 ptc1522;
	u64 mptc;
	u64 bptc;
	u64 tsctc;
	u64 tsctfc;
	u64 iac;
	u64 icrxptc;
	u64 icrxatc;
	u64 ictxptc;
	u64 ictxatc;
	u64 ictxqec;
	u64 ictxqmtc;
	u64 icrxdmtc;
	u64 icrxoc;
पूर्ण;

काष्ठा e1000_phy_stats अणु
	u32 idle_errors;
	u32 receive_errors;
पूर्ण;

काष्ठा e1000_host_mng_dhcp_cookie अणु
	u32 signature;
	u8 status;
	u8 reserved0;
	u16 vlan_id;
	u32 reserved1;
	u16 reserved2;
	u8 reserved3;
	u8 checksum;
पूर्ण;

/* Host Interface "Rev 1" */
काष्ठा e1000_host_command_header अणु
	u8 command_id;
	u8 command_length;
	u8 command_options;
	u8 checksum;
पूर्ण;

#घोषणा E1000_HI_MAX_DATA_LENGTH	252
काष्ठा e1000_host_command_info अणु
	काष्ठा e1000_host_command_header command_header;
	u8 command_data[E1000_HI_MAX_DATA_LENGTH];
पूर्ण;

/* Host Interface "Rev 2" */
काष्ठा e1000_host_mng_command_header अणु
	u8 command_id;
	u8 checksum;
	u16 reserved1;
	u16 reserved2;
	u16 command_length;
पूर्ण;

#घोषणा E1000_HI_MAX_MNG_DATA_LENGTH	0x6F8
काष्ठा e1000_host_mng_command_info अणु
	काष्ठा e1000_host_mng_command_header command_header;
	u8 command_data[E1000_HI_MAX_MNG_DATA_LENGTH];
पूर्ण;

#समावेश "mac.h"
#समावेश "phy.h"
#समावेश "nvm.h"
#समावेश "manage.h"

/* Function poपूर्णांकers क्रम the MAC. */
काष्ठा e1000_mac_operations अणु
	s32  (*id_led_init)(काष्ठा e1000_hw *);
	s32  (*blink_led)(काष्ठा e1000_hw *);
	bool (*check_mng_mode)(काष्ठा e1000_hw *);
	s32  (*check_क्रम_link)(काष्ठा e1000_hw *);
	s32  (*cleanup_led)(काष्ठा e1000_hw *);
	व्योम (*clear_hw_cntrs)(काष्ठा e1000_hw *);
	व्योम (*clear_vfta)(काष्ठा e1000_hw *);
	s32  (*get_bus_info)(काष्ठा e1000_hw *);
	व्योम (*set_lan_id)(काष्ठा e1000_hw *);
	s32  (*get_link_up_info)(काष्ठा e1000_hw *, u16 *, u16 *);
	s32  (*led_on)(काष्ठा e1000_hw *);
	s32  (*led_off)(काष्ठा e1000_hw *);
	व्योम (*update_mc_addr_list)(काष्ठा e1000_hw *, u8 *, u32);
	s32  (*reset_hw)(काष्ठा e1000_hw *);
	s32  (*init_hw)(काष्ठा e1000_hw *);
	s32  (*setup_link)(काष्ठा e1000_hw *);
	s32  (*setup_physical_पूर्णांकerface)(काष्ठा e1000_hw *);
	s32  (*setup_led)(काष्ठा e1000_hw *);
	व्योम (*ग_लिखो_vfta)(काष्ठा e1000_hw *, u32, u32);
	व्योम (*config_collision_dist)(काष्ठा e1000_hw *);
	पूर्णांक  (*rar_set)(काष्ठा e1000_hw *, u8 *, u32);
	s32  (*पढ़ो_mac_addr)(काष्ठा e1000_hw *);
	u32  (*rar_get_count)(काष्ठा e1000_hw *);
पूर्ण;

/* When to use various PHY रेजिस्टर access functions:
 *
 *                 Func   Caller
 *   Function      Does   Does    When to use
 *   ~~~~~~~~~~~~  ~~~~~  ~~~~~~  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *   X_reg         L,P,A  n/a     क्रम simple PHY reg accesses
 *   X_reg_locked  P,A    L       क्रम multiple accesses of dअगरferent regs
 *                                on dअगरferent pages
 *   X_reg_page    A      L,P     क्रम multiple accesses of dअगरferent regs
 *                                on the same page
 *
 * Where X=[पढ़ो|ग_लिखो], L=locking, P=sets page, A=रेजिस्टर access
 *
 */
काष्ठा e1000_phy_operations अणु
	s32  (*acquire)(काष्ठा e1000_hw *);
	s32  (*cfg_on_link_up)(काष्ठा e1000_hw *);
	s32  (*check_polarity)(काष्ठा e1000_hw *);
	s32  (*check_reset_block)(काष्ठा e1000_hw *);
	s32  (*commit)(काष्ठा e1000_hw *);
	s32  (*क्रमce_speed_duplex)(काष्ठा e1000_hw *);
	s32  (*get_cfg_करोne)(काष्ठा e1000_hw *hw);
	s32  (*get_cable_length)(काष्ठा e1000_hw *);
	s32  (*get_info)(काष्ठा e1000_hw *);
	s32  (*set_page)(काष्ठा e1000_hw *, u16);
	s32  (*पढ़ो_reg)(काष्ठा e1000_hw *, u32, u16 *);
	s32  (*पढ़ो_reg_locked)(काष्ठा e1000_hw *, u32, u16 *);
	s32  (*पढ़ो_reg_page)(काष्ठा e1000_hw *, u32, u16 *);
	व्योम (*release)(काष्ठा e1000_hw *);
	s32  (*reset)(काष्ठा e1000_hw *);
	s32  (*set_d0_lplu_state)(काष्ठा e1000_hw *, bool);
	s32  (*set_d3_lplu_state)(काष्ठा e1000_hw *, bool);
	s32  (*ग_लिखो_reg)(काष्ठा e1000_hw *, u32, u16);
	s32  (*ग_लिखो_reg_locked)(काष्ठा e1000_hw *, u32, u16);
	s32  (*ग_लिखो_reg_page)(काष्ठा e1000_hw *, u32, u16);
	व्योम (*घातer_up)(काष्ठा e1000_hw *);
	व्योम (*घातer_करोwn)(काष्ठा e1000_hw *);
पूर्ण;

/* Function poपूर्णांकers क्रम the NVM. */
काष्ठा e1000_nvm_operations अणु
	s32  (*acquire)(काष्ठा e1000_hw *);
	s32  (*पढ़ो)(काष्ठा e1000_hw *, u16, u16, u16 *);
	व्योम (*release)(काष्ठा e1000_hw *);
	व्योम (*reload)(काष्ठा e1000_hw *);
	s32  (*update)(काष्ठा e1000_hw *);
	s32  (*valid_led_शेष)(काष्ठा e1000_hw *, u16 *);
	s32  (*validate)(काष्ठा e1000_hw *);
	s32  (*ग_लिखो)(काष्ठा e1000_hw *, u16, u16, u16 *);
पूर्ण;

काष्ठा e1000_mac_info अणु
	काष्ठा e1000_mac_operations ops;
	u8 addr[ETH_ALEN];
	u8 perm_addr[ETH_ALEN];

	क्रमागत e1000_mac_type type;

	u32 collision_delta;
	u32 ledctl_शेष;
	u32 ledctl_mode1;
	u32 ledctl_mode2;
	u32 mc_filter_type;
	u32 tx_packet_delta;
	u32 txcw;

	u16 current_अगरs_val;
	u16 अगरs_max_val;
	u16 अगरs_min_val;
	u16 अगरs_ratio;
	u16 अगरs_step_size;
	u16 mta_reg_count;

	/* Maximum size of the MTA रेजिस्टर table in all supported adapters */
#घोषणा MAX_MTA_REG 128
	u32 mta_shaकरोw[MAX_MTA_REG];
	u16 rar_entry_count;

	u8 क्रमced_speed_duplex;

	bool adaptive_अगरs;
	bool has_fwsm;
	bool arc_subप्रणाली_valid;
	bool स्वतःneg;
	bool स्वतःneg_failed;
	bool get_link_status;
	bool in_अगरs_mode;
	bool serdes_has_link;
	bool tx_pkt_filtering;
	क्रमागत e1000_serdes_link_state serdes_link_state;
पूर्ण;

काष्ठा e1000_phy_info अणु
	काष्ठा e1000_phy_operations ops;

	क्रमागत e1000_phy_type type;

	क्रमागत e1000_1000t_rx_status local_rx;
	क्रमागत e1000_1000t_rx_status remote_rx;
	क्रमागत e1000_ms_type ms_type;
	क्रमागत e1000_ms_type original_ms_type;
	क्रमागत e1000_rev_polarity cable_polarity;
	क्रमागत e1000_smart_speed smart_speed;

	u32 addr;
	u32 id;
	u32 reset_delay_us;	/* in usec */
	u32 revision;

	क्रमागत e1000_media_type media_type;

	u16 स्वतःneg_advertised;
	u16 स्वतःneg_mask;
	u16 cable_length;
	u16 max_cable_length;
	u16 min_cable_length;

	u8 mdix;

	bool disable_polarity_correction;
	bool is_mdix;
	bool polarity_correction;
	bool speed_करोwngraded;
	bool स्वतःneg_रुको_to_complete;
पूर्ण;

काष्ठा e1000_nvm_info अणु
	काष्ठा e1000_nvm_operations ops;

	क्रमागत e1000_nvm_type type;
	क्रमागत e1000_nvm_override override;

	u32 flash_bank_size;
	u32 flash_base_addr;

	u16 word_size;
	u16 delay_usec;
	u16 address_bits;
	u16 opcode_bits;
	u16 page_size;
पूर्ण;

काष्ठा e1000_bus_info अणु
	क्रमागत e1000_bus_width width;

	u16 func;
पूर्ण;

काष्ठा e1000_fc_info अणु
	u32 high_water;          /* Flow control high-water mark */
	u32 low_water;           /* Flow control low-water mark */
	u16 छोड़ो_समय;          /* Flow control छोड़ो समयr */
	u16 refresh_समय;        /* Flow control refresh समयr */
	bool send_xon;           /* Flow control send XON */
	bool strict_ieee;        /* Strict IEEE mode */
	क्रमागत e1000_fc_mode current_mode; /* FC mode in effect */
	क्रमागत e1000_fc_mode requested_mode; /* FC mode requested by caller */
पूर्ण;

काष्ठा e1000_dev_spec_82571 अणु
	bool laa_is_present;
	u32 smb_counter;
पूर्ण;

काष्ठा e1000_dev_spec_80003es2lan अणु
	bool mdic_wa_enable;
पूर्ण;

काष्ठा e1000_shaकरोw_ram अणु
	u16 value;
	bool modअगरied;
पूर्ण;

#घोषणा E1000_ICH8_SHADOW_RAM_WORDS		2048

/* I218 PHY Ultra Low Power (ULP) states */
क्रमागत e1000_ulp_state अणु
	e1000_ulp_state_unknown,
	e1000_ulp_state_off,
	e1000_ulp_state_on,
पूर्ण;

काष्ठा e1000_dev_spec_ich8lan अणु
	bool kmrn_lock_loss_workaround_enabled;
	काष्ठा e1000_shaकरोw_ram shaकरोw_ram[E1000_ICH8_SHADOW_RAM_WORDS];
	bool nvm_k1_enabled;
	bool eee_disable;
	u16 eee_lp_ability;
	क्रमागत e1000_ulp_state ulp_state;
पूर्ण;

काष्ठा e1000_hw अणु
	काष्ठा e1000_adapter *adapter;

	व्योम __iomem *hw_addr;
	व्योम __iomem *flash_address;

	काष्ठा e1000_mac_info mac;
	काष्ठा e1000_fc_info fc;
	काष्ठा e1000_phy_info phy;
	काष्ठा e1000_nvm_info nvm;
	काष्ठा e1000_bus_info bus;
	काष्ठा e1000_host_mng_dhcp_cookie mng_cookie;

	जोड़ अणु
		काष्ठा e1000_dev_spec_82571 e82571;
		काष्ठा e1000_dev_spec_80003es2lan e80003es2lan;
		काष्ठा e1000_dev_spec_ich8lan ich8lan;
	पूर्ण dev_spec;
पूर्ण;

#समावेश "82571.h"
#समावेश "80003es2lan.h"
#समावेश "ich8lan.h"

#पूर्ण_अगर /* _E1000E_HW_H_ */
