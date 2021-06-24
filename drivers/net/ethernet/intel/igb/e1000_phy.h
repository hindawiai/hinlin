<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2007 - 2018 Intel Corporation. */

#अगर_अघोषित _E1000_PHY_H_
#घोषणा _E1000_PHY_H_

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

s32  igb_check_करोwnshअगरt(काष्ठा e1000_hw *hw);
s32  igb_check_reset_block(काष्ठा e1000_hw *hw);
s32  igb_copper_link_setup_igp(काष्ठा e1000_hw *hw);
s32  igb_copper_link_setup_m88(काष्ठा e1000_hw *hw);
s32  igb_copper_link_setup_m88_gen2(काष्ठा e1000_hw *hw);
s32  igb_phy_क्रमce_speed_duplex_igp(काष्ठा e1000_hw *hw);
s32  igb_phy_क्रमce_speed_duplex_m88(काष्ठा e1000_hw *hw);
s32  igb_get_cable_length_m88(काष्ठा e1000_hw *hw);
s32  igb_get_cable_length_m88_gen2(काष्ठा e1000_hw *hw);
s32  igb_get_cable_length_igp_2(काष्ठा e1000_hw *hw);
s32  igb_get_phy_id(काष्ठा e1000_hw *hw);
s32  igb_get_phy_info_igp(काष्ठा e1000_hw *hw);
s32  igb_get_phy_info_m88(काष्ठा e1000_hw *hw);
s32  igb_phy_sw_reset(काष्ठा e1000_hw *hw);
s32  igb_phy_hw_reset(काष्ठा e1000_hw *hw);
s32  igb_पढ़ो_phy_reg_igp(काष्ठा e1000_hw *hw, u32 offset, u16 *data);
s32  igb_set_d3_lplu_state(काष्ठा e1000_hw *hw, bool active);
s32  igb_setup_copper_link(काष्ठा e1000_hw *hw);
s32  igb_ग_लिखो_phy_reg_igp(काष्ठा e1000_hw *hw, u32 offset, u16 data);
s32  igb_phy_has_link(काष्ठा e1000_hw *hw, u32 iterations,
				u32 usec_पूर्णांकerval, bool *success);
व्योम igb_घातer_up_phy_copper(काष्ठा e1000_hw *hw);
व्योम igb_घातer_करोwn_phy_copper(काष्ठा e1000_hw *hw);
s32  igb_phy_init_script_igp3(काष्ठा e1000_hw *hw);
s32  igb_initialize_M88E1512_phy(काष्ठा e1000_hw *hw);
s32  igb_initialize_M88E1543_phy(काष्ठा e1000_hw *hw);
s32  igb_पढ़ो_phy_reg_mdic(काष्ठा e1000_hw *hw, u32 offset, u16 *data);
s32  igb_ग_लिखो_phy_reg_mdic(काष्ठा e1000_hw *hw, u32 offset, u16 data);
s32  igb_पढ़ो_phy_reg_i2c(काष्ठा e1000_hw *hw, u32 offset, u16 *data);
s32  igb_ग_लिखो_phy_reg_i2c(काष्ठा e1000_hw *hw, u32 offset, u16 data);
s32  igb_पढ़ो_sfp_data_byte(काष्ठा e1000_hw *hw, u16 offset, u8 *data);
s32  igb_copper_link_setup_82580(काष्ठा e1000_hw *hw);
s32  igb_get_phy_info_82580(काष्ठा e1000_hw *hw);
s32  igb_phy_क्रमce_speed_duplex_82580(काष्ठा e1000_hw *hw);
s32  igb_get_cable_length_82580(काष्ठा e1000_hw *hw);
s32  igb_पढ़ो_phy_reg_82580(काष्ठा e1000_hw *hw, u32 offset, u16 *data);
s32  igb_ग_लिखो_phy_reg_82580(काष्ठा e1000_hw *hw, u32 offset, u16 data);
s32  igb_check_polarity_m88(काष्ठा e1000_hw *hw);

/* IGP01E1000 Specअगरic Registers */
#घोषणा IGP01E1000_PHY_PORT_CONFIG        0x10 /* Port Config */
#घोषणा IGP01E1000_PHY_PORT_STATUS        0x11 /* Status */
#घोषणा IGP01E1000_PHY_PORT_CTRL          0x12 /* Control */
#घोषणा IGP01E1000_PHY_LINK_HEALTH        0x13 /* PHY Link Health */
#घोषणा IGP02E1000_PHY_POWER_MGMT         0x19 /* Power Management */
#घोषणा IGP01E1000_PHY_PAGE_SELECT        0x1F /* Page Select */
#घोषणा IGP01E1000_PHY_PCS_INIT_REG       0x00B4
#घोषणा IGP01E1000_PHY_POLARITY_MASK      0x0078
#घोषणा IGP01E1000_PSCR_AUTO_MDIX         0x1000
#घोषणा IGP01E1000_PSCR_FORCE_MDI_MDIX    0x2000 /* 0=MDI, 1=MDIX */
#घोषणा IGP01E1000_PSCFR_SMART_SPEED      0x0080

#घोषणा I82580_ADDR_REG                   16
#घोषणा I82580_CFG_REG                    22
#घोषणा I82580_CFG_ASSERT_CRS_ON_TX       BIT(15)
#घोषणा I82580_CFG_ENABLE_DOWNSHIFT       (3u << 10) /* स्वतः करोwnshअगरt 100/10 */
#घोषणा I82580_CTRL_REG                   23
#घोषणा I82580_CTRL_DOWNSHIFT_MASK        (7u << 10)

/* 82580 specअगरic PHY रेजिस्टरs */
#घोषणा I82580_PHY_CTRL_2            18
#घोषणा I82580_PHY_LBK_CTRL          19
#घोषणा I82580_PHY_STATUS_2          26
#घोषणा I82580_PHY_DIAG_STATUS       31

/* I82580 PHY Status 2 */
#घोषणा I82580_PHY_STATUS2_REV_POLARITY   0x0400
#घोषणा I82580_PHY_STATUS2_MDIX           0x0800
#घोषणा I82580_PHY_STATUS2_SPEED_MASK     0x0300
#घोषणा I82580_PHY_STATUS2_SPEED_1000MBPS 0x0200
#घोषणा I82580_PHY_STATUS2_SPEED_100MBPS  0x0100

/* I82580 PHY Control 2 */
#घोषणा I82580_PHY_CTRL2_MANUAL_MDIX      0x0200
#घोषणा I82580_PHY_CTRL2_AUTO_MDI_MDIX    0x0400
#घोषणा I82580_PHY_CTRL2_MDIX_CFG_MASK    0x0600

/* I82580 PHY Diagnostics Status */
#घोषणा I82580_DSTATUS_CABLE_LENGTH       0x03FC
#घोषणा I82580_DSTATUS_CABLE_LENGTH_SHIFT 2

/* 82580 PHY Power Management */
#घोषणा E1000_82580_PHY_POWER_MGMT	0xE14
#घोषणा E1000_82580_PM_SPD		0x0001 /* Smart Power Down */
#घोषणा E1000_82580_PM_D0_LPLU		0x0002 /* For D0a states */
#घोषणा E1000_82580_PM_D3_LPLU		0x0004 /* For all other states */
#घोषणा E1000_82580_PM_GO_LINKD		0x0020 /* Go Link Disconnect */

/* Enable flexible speed on link-up */
#घोषणा IGP02E1000_PM_D0_LPLU             0x0002 /* For D0a states */
#घोषणा IGP02E1000_PM_D3_LPLU             0x0004 /* For all other states */
#घोषणा IGP01E1000_PLHR_SS_DOWNGRADE      0x8000
#घोषणा IGP01E1000_PSSR_POLARITY_REVERSED 0x0002
#घोषणा IGP01E1000_PSSR_MDIX              0x0800
#घोषणा IGP01E1000_PSSR_SPEED_MASK        0xC000
#घोषणा IGP01E1000_PSSR_SPEED_1000MBPS    0xC000
#घोषणा IGP02E1000_PHY_CHANNEL_NUM        4
#घोषणा IGP02E1000_PHY_AGC_A              0x11B1
#घोषणा IGP02E1000_PHY_AGC_B              0x12B1
#घोषणा IGP02E1000_PHY_AGC_C              0x14B1
#घोषणा IGP02E1000_PHY_AGC_D              0x18B1
#घोषणा IGP02E1000_AGC_LENGTH_SHIFT       9   /* Course - 15:13, Fine - 12:9 */
#घोषणा IGP02E1000_AGC_LENGTH_MASK        0x7F
#घोषणा IGP02E1000_AGC_RANGE              15

#घोषणा E1000_CABLE_LENGTH_UNDEFINED      0xFF

/* SFP modules ID memory locations */
#घोषणा E1000_SFF_IDENTIFIER_OFFSET	0x00
#घोषणा E1000_SFF_IDENTIFIER_SFF	0x02
#घोषणा E1000_SFF_IDENTIFIER_SFP	0x03

#घोषणा E1000_SFF_ETH_FLAGS_OFFSET	0x06
/* Flags क्रम SFP modules compatible with ETH up to 1Gb */
काष्ठा e1000_sfp_flags अणु
	u8 e1000_base_sx:1;
	u8 e1000_base_lx:1;
	u8 e1000_base_cx:1;
	u8 e1000_base_t:1;
	u8 e100_base_lx:1;
	u8 e100_base_fx:1;
	u8 e10_base_bx10:1;
	u8 e10_base_px:1;
पूर्ण;

#पूर्ण_अगर
