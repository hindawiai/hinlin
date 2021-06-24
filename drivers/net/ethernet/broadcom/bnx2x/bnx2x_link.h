<शैली गुरु>
/* Copyright 2008-2013 Broadcom Corporation
 * Copyright (c) 2014 QLogic Corporation
 * All rights reserved
 *
 * Unless you and QLogic execute a separate written software license
 * agreement governing use of this software, this software is licensed to you
 * under the terms of the GNU General Public License version 2, available
 * at http://www.gnu.org/licenses/gpl-2.0.hपंचांगl (the "GPL").
 *
 * Notwithstanding the above, under no circumstances may you combine this
 * software in any way with any other Qlogic software provided under a
 * license other than the GPL, without Qlogic's express prior written
 * consent.
 *
 * Written by Yaniv Rosner
 *
 */

#अगर_अघोषित BNX2X_LINK_H
#घोषणा BNX2X_LINK_H



/***********************************************************/
/*                         Defines                         */
/***********************************************************/
#घोषणा DEFAULT_PHY_DEV_ADDR	3
#घोषणा E2_DEFAULT_PHY_DEV_ADDR	5



#घोषणा BNX2X_FLOW_CTRL_AUTO		PORT_FEATURE_FLOW_CONTROL_AUTO
#घोषणा BNX2X_FLOW_CTRL_TX		PORT_FEATURE_FLOW_CONTROL_TX
#घोषणा BNX2X_FLOW_CTRL_RX		PORT_FEATURE_FLOW_CONTROL_RX
#घोषणा BNX2X_FLOW_CTRL_BOTH		PORT_FEATURE_FLOW_CONTROL_BOTH
#घोषणा BNX2X_FLOW_CTRL_NONE		PORT_FEATURE_FLOW_CONTROL_NONE

#घोषणा NET_SERDES_IF_XFI		1
#घोषणा NET_SERDES_IF_SFI		2
#घोषणा NET_SERDES_IF_KR		3
#घोषणा NET_SERDES_IF_DXGXS	4

#घोषणा SPEED_AUTO_NEG		0
#घोषणा SPEED_20000		20000

#घोषणा I2C_DEV_ADDR_A0			0xa0
#घोषणा I2C_DEV_ADDR_A2			0xa2

#घोषणा SFP_EEPROM_PAGE_SIZE			16
#घोषणा SFP_EEPROM_VENDOR_NAME_ADDR		0x14
#घोषणा SFP_EEPROM_VENDOR_NAME_SIZE		16
#घोषणा SFP_EEPROM_VENDOR_OUI_ADDR		0x25
#घोषणा SFP_EEPROM_VENDOR_OUI_SIZE		3
#घोषणा SFP_EEPROM_PART_NO_ADDR			0x28
#घोषणा SFP_EEPROM_PART_NO_SIZE			16
#घोषणा SFP_EEPROM_REVISION_ADDR		0x38
#घोषणा SFP_EEPROM_REVISION_SIZE		4
#घोषणा SFP_EEPROM_SERIAL_ADDR			0x44
#घोषणा SFP_EEPROM_SERIAL_SIZE			16
#घोषणा SFP_EEPROM_DATE_ADDR			0x54 /* ASCII YYMMDD */
#घोषणा SFP_EEPROM_DATE_SIZE			6
#घोषणा SFP_EEPROM_DIAG_TYPE_ADDR		0x5c
#घोषणा SFP_EEPROM_DIAG_TYPE_SIZE		1
#घोषणा SFP_EEPROM_DIAG_ADDR_CHANGE_REQ		(1<<2)
#घोषणा SFP_EEPROM_DDM_IMPLEMENTED		(1<<6)
#घोषणा SFP_EEPROM_SFF_8472_COMP_ADDR		0x5e
#घोषणा SFP_EEPROM_SFF_8472_COMP_SIZE		1

#घोषणा SFP_EEPROM_A2_CHECKSUM_RANGE		0x5e
#घोषणा SFP_EEPROM_A2_CC_DMI_ADDR		0x5f

#घोषणा PWR_FLT_ERR_MSG_LEN			250

#घोषणा XGXS_EXT_PHY_TYPE(ext_phy_config) \
		((ext_phy_config) & PORT_HW_CFG_XGXS_EXT_PHY_TYPE_MASK)
#घोषणा XGXS_EXT_PHY_ADDR(ext_phy_config) \
		(((ext_phy_config) & PORT_HW_CFG_XGXS_EXT_PHY_ADDR_MASK) >> \
		 PORT_HW_CFG_XGXS_EXT_PHY_ADDR_SHIFT)
#घोषणा SERDES_EXT_PHY_TYPE(ext_phy_config) \
		((ext_phy_config) & PORT_HW_CFG_SERDES_EXT_PHY_TYPE_MASK)

/* Single Media Direct board is the plain 577xx board with CX4/RJ45 jacks */
#घोषणा SINGLE_MEDIA_सूचीECT(params)	(params->num_phys == 1)
/* Single Media board contains single बाह्यal phy */
#घोषणा SINGLE_MEDIA(params)		(params->num_phys == 2)
/* Dual Media board contains two बाह्यal phy with dअगरferent media */
#घोषणा DUAL_MEDIA(params)		(params->num_phys == 3)

#घोषणा FW_PARAM_PHY_ADDR_MASK		0x000000FF
#घोषणा FW_PARAM_PHY_TYPE_MASK		0x0000FF00
#घोषणा FW_PARAM_MDIO_CTRL_MASK		0xFFFF0000
#घोषणा FW_PARAM_MDIO_CTRL_OFFSET		16
#घोषणा FW_PARAM_PHY_ADDR(fw_param) (fw_param & \
					   FW_PARAM_PHY_ADDR_MASK)
#घोषणा FW_PARAM_PHY_TYPE(fw_param) (fw_param & \
					   FW_PARAM_PHY_TYPE_MASK)
#घोषणा FW_PARAM_MDIO_CTRL(fw_param) ((fw_param & \
					    FW_PARAM_MDIO_CTRL_MASK) >> \
					    FW_PARAM_MDIO_CTRL_OFFSET)
#घोषणा FW_PARAM_SET(phy_addr, phy_type, mdio_access) \
	(phy_addr | phy_type | mdio_access << FW_PARAM_MDIO_CTRL_OFFSET)


#घोषणा PFC_BRB_FULL_LB_XOFF_THRESHOLD				170
#घोषणा PFC_BRB_FULL_LB_XON_THRESHOLD				250

#घोषणा MAXVAL(a, b) (((a) > (b)) ? (a) : (b))

#घोषणा BMAC_CONTROL_RX_ENABLE		2
/***********************************************************/
/*                         Structs                         */
/***********************************************************/
#घोषणा INT_PHY		0
#घोषणा EXT_PHY1	1
#घोषणा EXT_PHY2	2
#घोषणा MAX_PHYS	3

/* Same configuration is shared between the XGXS and the first बाह्यal phy */
#घोषणा LINK_CONFIG_SIZE (MAX_PHYS - 1)
#घोषणा LINK_CONFIG_IDX(_phy_idx) ((_phy_idx == INT_PHY) ? \
					 0 : (_phy_idx - 1))
/***********************************************************/
/*                      bnx2x_phy काष्ठा                     */
/*  Defines the required arguments and function per phy    */
/***********************************************************/
काष्ठा link_vars;
काष्ठा link_params;
काष्ठा bnx2x_phy;

प्रकार व्योम (*config_init_t)(काष्ठा bnx2x_phy *phy, काष्ठा link_params *params,
			      काष्ठा link_vars *vars);
प्रकार u8 (*पढ़ो_status_t)(काष्ठा bnx2x_phy *phy, काष्ठा link_params *params,
			    काष्ठा link_vars *vars);
प्रकार व्योम (*link_reset_t)(काष्ठा bnx2x_phy *phy,
			     काष्ठा link_params *params);
प्रकार व्योम (*config_loopback_t)(काष्ठा bnx2x_phy *phy,
				  काष्ठा link_params *params);
प्रकार पूर्णांक (*क्रमmat_fw_ver_t)(u32 raw, u8 *str, u16 *len);
प्रकार व्योम (*hw_reset_t)(काष्ठा bnx2x_phy *phy, काष्ठा link_params *params);
प्रकार व्योम (*set_link_led_t)(काष्ठा bnx2x_phy *phy,
			       काष्ठा link_params *params, u8 mode);
प्रकार व्योम (*phy_specअगरic_func_t)(काष्ठा bnx2x_phy *phy,
				    काष्ठा link_params *params, u32 action);
काष्ठा bnx2x_reg_set अणु
	u8  devad;
	u16 reg;
	u16 val;
पूर्ण;

काष्ठा bnx2x_phy अणु
	u32 type;

	/* Loaded during init */
	u8 addr;
	u8 def_md_devad;
	u16 flags;
	/* No Over-Current detection */
#घोषणा FLAGS_NOC			(1<<1)
	/* Fan failure detection required */
#घोषणा FLAGS_FAN_FAILURE_DET_REQ	(1<<2)
	/* Initialize first the XGXS and only then the phy itself */
#घोषणा FLAGS_INIT_XGXS_FIRST		(1<<3)
#घोषणा FLAGS_WC_DUAL_MODE		(1<<4)
#घोषणा FLAGS_4_PORT_MODE		(1<<5)
#घोषणा FLAGS_REARM_LATCH_SIGNAL	(1<<6)
#घोषणा FLAGS_SFP_NOT_APPROVED		(1<<7)
#घोषणा FLAGS_MDC_MDIO_WA		(1<<8)
#घोषणा FLAGS_DUMMY_READ		(1<<9)
#घोषणा FLAGS_MDC_MDIO_WA_B0		(1<<10)
#घोषणा FLAGS_TX_ERROR_CHECK		(1<<12)
#घोषणा FLAGS_EEE			(1<<13)
#घोषणा FLAGS_MDC_MDIO_WA_G		(1<<15)

	/* preemphasis values क्रम the rx side */
	u16 rx_preemphasis[4];

	/* preemphasis values क्रम the tx side */
	u16 tx_preemphasis[4];

	/* EMAC address क्रम access MDIO */
	u32 mdio_ctrl;

	u32 supported;

	u32 media_type;
#घोषणा	ETH_PHY_UNSPECIFIED	0x0
#घोषणा	ETH_PHY_SFPP_10G_FIBER	0x1
#घोषणा	ETH_PHY_XFP_FIBER		0x2
#घोषणा	ETH_PHY_DA_TWINAX		0x3
#घोषणा	ETH_PHY_BASE_T		0x4
#घोषणा	ETH_PHY_SFP_1G_FIBER	0x5
#घोषणा	ETH_PHY_KR		0xf0
#घोषणा	ETH_PHY_CX4		0xf1
#घोषणा	ETH_PHY_NOT_PRESENT	0xff

	/* The address in which version is located*/
	u32 ver_addr;

	u16 req_flow_ctrl;

	u16 req_line_speed;

	u32 speed_cap_mask;

	u16 req_duplex;
	u16 rsrv;
	/* Called per phy/port init, and it configures LASI, speed, स्वतःneg,
	 duplex, flow control negotiation, etc. */
	config_init_t config_init;

	/* Called due to पूर्णांकerrupt. It determines the link, speed */
	पढ़ो_status_t पढ़ो_status;

	/* Called when driver is unloading. Should reset the phy */
	link_reset_t link_reset;

	/* Set the loopback configuration क्रम the phy */
	config_loopback_t config_loopback;

	/* Format the given raw number पूर्णांकo str up to len */
	क्रमmat_fw_ver_t क्रमmat_fw_ver;

	/* Reset the phy (both ports) */
	hw_reset_t hw_reset;

	/* Set link led mode (on/off/oper)*/
	set_link_led_t set_link_led;

	/* PHY Specअगरic tasks */
	phy_specअगरic_func_t phy_specअगरic_func;
#घोषणा DISABLE_TX	1
#घोषणा ENABLE_TX	2
#घोषणा PHY_INIT	3
पूर्ण;

/* Inमाला_दो parameters to the CLC */
काष्ठा link_params अणु

	u8 port;

	/* Default / User Configuration */
	u8 loopback_mode;
#घोषणा LOOPBACK_NONE		0
#घोषणा LOOPBACK_EMAC		1
#घोषणा LOOPBACK_BMAC		2
#घोषणा LOOPBACK_XGXS		3
#घोषणा LOOPBACK_EXT_PHY	4
#घोषणा LOOPBACK_EXT		5
#घोषणा LOOPBACK_UMAC		6
#घोषणा LOOPBACK_XMAC		7

	/* Device parameters */
	u8 mac_addr[6];

	u16 req_duplex[LINK_CONFIG_SIZE];
	u16 req_flow_ctrl[LINK_CONFIG_SIZE];

	u16 req_line_speed[LINK_CONFIG_SIZE]; /* Also determine AutoNeg */

	/* shmem parameters */
	u32 shmem_base;
	u32 shmem2_base;
	u32 speed_cap_mask[LINK_CONFIG_SIZE];
	u32 चयन_cfg;
#घोषणा SWITCH_CFG_1G		PORT_FEATURE_CON_SWITCH_1G_SWITCH
#घोषणा SWITCH_CFG_10G		PORT_FEATURE_CON_SWITCH_10G_SWITCH
#घोषणा SWITCH_CFG_AUTO_DETECT	PORT_FEATURE_CON_SWITCH_AUTO_DETECT

	u32 lane_config;

	/* Phy रेजिस्टर parameter */
	u32 chip_id;

	/* features */
	u32 feature_config_flags;
#घोषणा FEATURE_CONFIG_OVERRIDE_PREEMPHASIS_ENABLED	(1<<0)
#घोषणा FEATURE_CONFIG_PFC_ENABLED			(1<<1)
#घोषणा FEATURE_CONFIG_BC_SUPPORTS_OPT_MDL_VRFY		(1<<2)
#घोषणा FEATURE_CONFIG_BC_SUPPORTS_DUAL_PHY_OPT_MDL_VRFY	(1<<3)
#घोषणा FEATURE_CONFIG_BC_SUPPORTS_AFEX			(1<<8)
#घोषणा FEATURE_CONFIG_AUTOGREEEN_ENABLED			(1<<9)
#घोषणा FEATURE_CONFIG_BC_SUPPORTS_SFP_TX_DISABLED		(1<<10)
#घोषणा FEATURE_CONFIG_DISABLE_REMOTE_FAULT_DET		(1<<11)
#घोषणा FEATURE_CONFIG_MT_SUPPORT			(1<<13)
#घोषणा FEATURE_CONFIG_BOOT_FROM_SAN			(1<<14)

	/* Will be populated during common init */
	काष्ठा bnx2x_phy phy[MAX_PHYS];

	/* Will be populated during common init */
	u8 num_phys;

	u8 rsrv;

	/* Used to configure the EEE Tx LPI समयr, has several modes of
	 * operation, according to bits 29:28 -
	 * 2'b00: Timer will be configured by nvram, output will be the value
	 *        from nvram.
	 * 2'b01: Timer will be configured by nvram, output will be in
	 *        microseconds.
	 * 2'b10: bits 1:0 contain an nvram value which will be used instead
	 *        of the one located in the nvram. Output will be that value.
	 * 2'b11: bits 19:0 contain the idle समयr in microseconds; output
	 *        will be in microseconds.
	 * Bits 31:30 should be 2'b11 in order क्रम EEE to be enabled.
	 */
	u32 eee_mode;
#घोषणा EEE_MODE_NVRAM_BALANCED_TIME		(0xa00)
#घोषणा EEE_MODE_NVRAM_AGGRESSIVE_TIME		(0x100)
#घोषणा EEE_MODE_NVRAM_LATENCY_TIME		(0x6000)
#घोषणा EEE_MODE_NVRAM_MASK		(0x3)
#घोषणा EEE_MODE_TIMER_MASK		(0xfffff)
#घोषणा EEE_MODE_OUTPUT_TIME		(1<<28)
#घोषणा EEE_MODE_OVERRIDE_NVRAM		(1<<29)
#घोषणा EEE_MODE_ENABLE_LPI		(1<<30)
#घोषणा EEE_MODE_ADV_LPI			(1<<31)

	u16 hw_led_mode; /* part of the hw_config पढ़ो from the shmem */
	u32 multi_phy_config;

	/* Device poपूर्णांकer passed to all callback functions */
	काष्ठा bnx2x *bp;
	u16 req_fc_स्वतः_adv; /* Should be set to TX / BOTH when
				req_flow_ctrl is set to AUTO */
	u16 link_flags;
#घोषणा LINK_FLAGS_INT_DISABLED		(1<<0)
#घोषणा PHY_INITIALIZED		(1<<1)
	u32 lfa_base;

	/* The same definitions as the shmem2 parameter */
	u32 link_attr_sync;
पूर्ण;

/* Output parameters */
काष्ठा link_vars अणु
	u8 phy_flags;
#घोषणा PHY_XGXS_FLAG			(1<<0)
#घोषणा PHY_SGMII_FLAG			(1<<1)
#घोषणा PHY_PHYSICAL_LINK_FLAG		(1<<2)
#घोषणा PHY_HALF_OPEN_CONN_FLAG		(1<<3)
#घोषणा PHY_OVER_CURRENT_FLAG		(1<<4)
#घोषणा PHY_SFP_TX_FAULT_FLAG		(1<<5)

	u8 mac_type;
#घोषणा MAC_TYPE_NONE		0
#घोषणा MAC_TYPE_EMAC		1
#घोषणा MAC_TYPE_BMAC		2
#घोषणा MAC_TYPE_UMAC		3
#घोषणा MAC_TYPE_XMAC		4

	u8 phy_link_up; /* पूर्णांकernal phy link indication */
	u8 link_up;

	u16 line_speed;
	u16 duplex;

	u16 flow_ctrl;
	u16 ieee_fc;

	/* The same definitions as the shmem parameter */
	u32 link_status;
	u32 eee_status;
	u8 fault_detected;
	u8 check_kr2_recovery_cnt;
#घोषणा CHECK_KR2_RECOVERY_CNT	5
	u16 periodic_flags;
#घोषणा PERIODIC_FLAGS_LINK_EVENT	0x0001

	u32 aeu_पूर्णांक_mask;
	u8 rx_tx_asic_rst;
	u8 turn_to_run_wc_rt;
	u16 rsrv2;
पूर्ण;

/***********************************************************/
/*                         Functions                       */
/***********************************************************/
पूर्णांक bnx2x_phy_init(काष्ठा link_params *params, काष्ठा link_vars *vars);

/* Reset the link. Should be called when driver or पूर्णांकerface goes करोwn
   Beक्रमe calling phy firmware upgrade, the reset_ext_phy should be set
   to 0 */
पूर्णांक bnx2x_link_reset(काष्ठा link_params *params, काष्ठा link_vars *vars,
		     u8 reset_ext_phy);
पूर्णांक bnx2x_lfa_reset(काष्ठा link_params *params, काष्ठा link_vars *vars);
/* bnx2x_link_update should be called upon link पूर्णांकerrupt */
पूर्णांक bnx2x_link_update(काष्ठा link_params *params, काष्ठा link_vars *vars);

/* use the following phy functions to पढ़ो/ग_लिखो from बाह्यal_phy
  In order to use it to पढ़ो/ग_लिखो पूर्णांकernal phy रेजिस्टरs, use
  DEFAULT_PHY_DEV_ADDR as devad, and (_bank + (_addr & 0xf)) as
  the रेजिस्टर */
पूर्णांक bnx2x_phy_पढ़ो(काष्ठा link_params *params, u8 phy_addr,
		   u8 devad, u16 reg, u16 *ret_val);

पूर्णांक bnx2x_phy_ग_लिखो(काष्ठा link_params *params, u8 phy_addr,
		    u8 devad, u16 reg, u16 val);

/* Reads the link_status from the shmem,
   and update the link vars accordingly */
व्योम bnx2x_link_status_update(काष्ठा link_params *input,
			    काष्ठा link_vars *output);
/* वापसs string representing the fw_version of the बाह्यal phy */
पूर्णांक bnx2x_get_ext_phy_fw_version(काष्ठा link_params *params, u8 *version,
				 u16 len);

/* Set/Unset the led
   Basically, the CLC takes care of the led क्रम the link, but in हाल one needs
   to set/unset the led unnaturally, set the "mode" to LED_MODE_OPER to
   blink the led, and LED_MODE_OFF to set the led off.*/
पूर्णांक bnx2x_set_led(काष्ठा link_params *params,
		  काष्ठा link_vars *vars, u8 mode, u32 speed);
#घोषणा LED_MODE_OFF			0
#घोषणा LED_MODE_ON			1
#घोषणा LED_MODE_OPER			2
#घोषणा LED_MODE_FRONT_PANEL_OFF	3

/* bnx2x_handle_module_detect_पूर्णांक should be called upon module detection
   पूर्णांकerrupt */
व्योम bnx2x_handle_module_detect_पूर्णांक(काष्ठा link_params *params);

/* Get the actual link status. In हाल it वापसs 0, link is up,
	otherwise link is करोwn*/
पूर्णांक bnx2x_test_link(काष्ठा link_params *params, काष्ठा link_vars *vars,
		    u8 is_serdes);

/* One-समय initialization क्रम बाह्यal phy after घातer up */
पूर्णांक bnx2x_common_init_phy(काष्ठा bnx2x *bp, u32 shmem_base_path[],
			  u32 shmem2_base_path[], u32 chip_id);

/* Reset the बाह्यal PHY using GPIO */
व्योम bnx2x_ext_phy_hw_reset(काष्ठा bnx2x *bp, u8 port);

/* Reset the बाह्यal of SFX7101 */
व्योम bnx2x_sfx7101_sp_sw_reset(काष्ठा bnx2x *bp, काष्ठा bnx2x_phy *phy);

/* Read "byte_cnt" bytes from address "addr" from the SFP+ EEPROM */
पूर्णांक bnx2x_पढ़ो_sfp_module_eeprom(काष्ठा bnx2x_phy *phy,
				 काष्ठा link_params *params, u8 dev_addr,
				 u16 addr, u16 byte_cnt, u8 *o_buf);

व्योम bnx2x_hw_reset_phy(काष्ठा link_params *params);

/* Check swap bit and adjust PHY order */
u32 bnx2x_phy_selection(काष्ठा link_params *params);

/* Probe the phys on board, and populate them in "params" */
पूर्णांक bnx2x_phy_probe(काष्ठा link_params *params);

/* Checks अगर fan failure detection is required on one of the phys on board */
u8 bnx2x_fan_failure_det_req(काष्ठा bnx2x *bp, u32 shmem_base,
			     u32 shmem2_base, u8 port);

/* Open / बंद the gate between the NIG and the BRB */
व्योम bnx2x_set_rx_filter(काष्ठा link_params *params, u8 en);

/* DCBX काष्ठाs */

/* Number of maximum COS per chip */
#घोषणा DCBX_E2E3_MAX_NUM_COS		(2)
#घोषणा DCBX_E3B0_MAX_NUM_COS_PORT0	(6)
#घोषणा DCBX_E3B0_MAX_NUM_COS_PORT1	(3)
#घोषणा DCBX_E3B0_MAX_NUM_COS		( \
			MAXVAL(DCBX_E3B0_MAX_NUM_COS_PORT0, \
			    DCBX_E3B0_MAX_NUM_COS_PORT1))

#घोषणा DCBX_MAX_NUM_COS			( \
			MAXVAL(DCBX_E3B0_MAX_NUM_COS, \
			    DCBX_E2E3_MAX_NUM_COS))

/* PFC port configuration params */
काष्ठा bnx2x_nig_brb_pfc_port_params अणु
	/* NIG */
	u32 छोड़ो_enable;
	u32 llfc_out_en;
	u32 llfc_enable;
	u32 pkt_priority_to_cos;
	u8 num_of_rx_cos_priority_mask;
	u32 rx_cos_priority_mask[DCBX_MAX_NUM_COS];
	u32 llfc_high_priority_classes;
	u32 llfc_low_priority_classes;
पूर्ण;


/* ETS port configuration params */
काष्ठा bnx2x_ets_bw_params अणु
	u8 bw;
पूर्ण;

काष्ठा bnx2x_ets_sp_params अणु
	/**
	 * valid values are 0 - 5. 0 is highest strict priority.
	 * There can't be two COS's with the same pri.
	 */
	u8 pri;
पूर्ण;

क्रमागत bnx2x_cos_state अणु
	bnx2x_cos_state_strict = 0,
	bnx2x_cos_state_bw = 1,
पूर्ण;

काष्ठा bnx2x_ets_cos_params अणु
	क्रमागत bnx2x_cos_state state ;
	जोड़ अणु
		काष्ठा bnx2x_ets_bw_params bw_params;
		काष्ठा bnx2x_ets_sp_params sp_params;
	पूर्ण params;
पूर्ण;

काष्ठा bnx2x_ets_params अणु
	u8 num_of_cos; /* Number of valid COS entries*/
	काष्ठा bnx2x_ets_cos_params cos[DCBX_MAX_NUM_COS];
पूर्ण;

/* Used to update the PFC attributes in EMAC, BMAC, NIG and BRB
 * when link is alपढ़ोy up
 */
पूर्णांक bnx2x_update_pfc(काष्ठा link_params *params,
		      काष्ठा link_vars *vars,
		      काष्ठा bnx2x_nig_brb_pfc_port_params *pfc_params);


/* Used to configure the ETS to disable */
पूर्णांक bnx2x_ets_disabled(काष्ठा link_params *params,
		       काष्ठा link_vars *vars);

/* Used to configure the ETS to BW limited */
व्योम bnx2x_ets_bw_limit(स्थिर काष्ठा link_params *params, स्थिर u32 cos0_bw,
			स्थिर u32 cos1_bw);

/* Used to configure the ETS to strict */
पूर्णांक bnx2x_ets_strict(स्थिर काष्ठा link_params *params, स्थिर u8 strict_cos);


/*  Configure the COS to ETS according to BW and SP settings.*/
पूर्णांक bnx2x_ets_e3b0_config(स्थिर काष्ठा link_params *params,
			 स्थिर काष्ठा link_vars *vars,
			 काष्ठा bnx2x_ets_params *ets_params);

व्योम bnx2x_init_mod_असल_पूर्णांक(काष्ठा bnx2x *bp, काष्ठा link_vars *vars,
			    u32 chip_id, u32 shmem_base, u32 shmem2_base,
			    u8 port);

व्योम bnx2x_period_func(काष्ठा link_params *params, काष्ठा link_vars *vars);

#पूर्ण_अगर /* BNX2X_LINK_H */
