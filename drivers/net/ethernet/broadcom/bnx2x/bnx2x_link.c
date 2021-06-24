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

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mutex.h>

#समावेश "bnx2x.h"
#समावेश "bnx2x_cmn.h"

प्रकार पूर्णांक (*पढ़ो_sfp_module_eeprom_func_p)(काष्ठा bnx2x_phy *phy,
					     काष्ठा link_params *params,
					     u8 dev_addr, u16 addr, u8 byte_cnt,
					     u8 *o_buf, u8);
/********************************************************/
#घोषणा MDIO_ACCESS_TIMEOUT		1000
#घोषणा WC_LANE_MAX			4
#घोषणा I2C_SWITCH_WIDTH		2
#घोषणा I2C_BSC0			0
#घोषणा I2C_BSC1			1
#घोषणा I2C_WA_RETRY_CNT		3
#घोषणा I2C_WA_PWR_ITER			(I2C_WA_RETRY_CNT - 1)
#घोषणा MCPR_IMC_COMMAND_READ_OP	1
#घोषणा MCPR_IMC_COMMAND_WRITE_OP	2

/* LED Blink rate that will achieve ~15.9Hz */
#घोषणा LED_BLINK_RATE_VAL_E3		354
#घोषणा LED_BLINK_RATE_VAL_E1X_E2	480
/***********************************************************/
/*			Shortcut definitions		   */
/***********************************************************/

#घोषणा NIG_LATCH_BC_ENABLE_MI_INT 0

#घोषणा NIG_STATUS_EMAC0_MI_INT \
		NIG_STATUS_INTERRUPT_PORT0_REG_STATUS_EMAC0_MISC_MI_INT
#घोषणा NIG_STATUS_XGXS0_LINK10G \
		NIG_STATUS_INTERRUPT_PORT0_REG_STATUS_XGXS0_LINK10G
#घोषणा NIG_STATUS_XGXS0_LINK_STATUS \
		NIG_STATUS_INTERRUPT_PORT0_REG_STATUS_XGXS0_LINK_STATUS
#घोषणा NIG_STATUS_XGXS0_LINK_STATUS_SIZE \
		NIG_STATUS_INTERRUPT_PORT0_REG_STATUS_XGXS0_LINK_STATUS_SIZE
#घोषणा NIG_STATUS_SERDES0_LINK_STATUS \
		NIG_STATUS_INTERRUPT_PORT0_REG_STATUS_SERDES0_LINK_STATUS
#घोषणा NIG_MASK_MI_INT \
		NIG_MASK_INTERRUPT_PORT0_REG_MASK_EMAC0_MISC_MI_INT
#घोषणा NIG_MASK_XGXS0_LINK10G \
		NIG_MASK_INTERRUPT_PORT0_REG_MASK_XGXS0_LINK10G
#घोषणा NIG_MASK_XGXS0_LINK_STATUS \
		NIG_MASK_INTERRUPT_PORT0_REG_MASK_XGXS0_LINK_STATUS
#घोषणा NIG_MASK_SERDES0_LINK_STATUS \
		NIG_MASK_INTERRUPT_PORT0_REG_MASK_SERDES0_LINK_STATUS

#घोषणा MDIO_AN_CL73_OR_37_COMPLETE \
		(MDIO_GP_STATUS_TOP_AN_STATUS1_CL73_AUTONEG_COMPLETE | \
		 MDIO_GP_STATUS_TOP_AN_STATUS1_CL37_AUTONEG_COMPLETE)

#घोषणा XGXS_RESET_BITS \
	(MISC_REGISTERS_RESET_REG_3_MISC_NIG_MUX_XGXS0_RSTB_HW |   \
	 MISC_REGISTERS_RESET_REG_3_MISC_NIG_MUX_XGXS0_IDDQ |      \
	 MISC_REGISTERS_RESET_REG_3_MISC_NIG_MUX_XGXS0_PWRDWN |    \
	 MISC_REGISTERS_RESET_REG_3_MISC_NIG_MUX_XGXS0_PWRDWN_SD | \
	 MISC_REGISTERS_RESET_REG_3_MISC_NIG_MUX_XGXS0_TXD_FIFO_RSTB)

#घोषणा SERDES_RESET_BITS \
	(MISC_REGISTERS_RESET_REG_3_MISC_NIG_MUX_SERDES0_RSTB_HW | \
	 MISC_REGISTERS_RESET_REG_3_MISC_NIG_MUX_SERDES0_IDDQ |    \
	 MISC_REGISTERS_RESET_REG_3_MISC_NIG_MUX_SERDES0_PWRDWN |  \
	 MISC_REGISTERS_RESET_REG_3_MISC_NIG_MUX_SERDES0_PWRDWN_SD)

#घोषणा AUTONEG_CL37		SHARED_HW_CFG_AN_ENABLE_CL37
#घोषणा AUTONEG_CL73		SHARED_HW_CFG_AN_ENABLE_CL73
#घोषणा AUTONEG_BAM		SHARED_HW_CFG_AN_ENABLE_BAM
#घोषणा AUTONEG_PARALLEL \
				SHARED_HW_CFG_AN_ENABLE_PARALLEL_DETECTION
#घोषणा AUTONEG_SGMII_FIBER_AUTODET \
				SHARED_HW_CFG_AN_EN_SGMII_FIBER_AUTO_DETECT
#घोषणा AUTONEG_REMOTE_PHY	SHARED_HW_CFG_AN_ENABLE_REMOTE_PHY

#घोषणा GP_STATUS_PAUSE_RSOLUTION_TXSIDE \
			MDIO_GP_STATUS_TOP_AN_STATUS1_PAUSE_RSOLUTION_TXSIDE
#घोषणा GP_STATUS_PAUSE_RSOLUTION_RXSIDE \
			MDIO_GP_STATUS_TOP_AN_STATUS1_PAUSE_RSOLUTION_RXSIDE
#घोषणा GP_STATUS_SPEED_MASK \
			MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_MASK
#घोषणा GP_STATUS_10M	MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_10M
#घोषणा GP_STATUS_100M	MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_100M
#घोषणा GP_STATUS_1G	MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_1G
#घोषणा GP_STATUS_2_5G	MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_2_5G
#घोषणा GP_STATUS_5G	MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_5G
#घोषणा GP_STATUS_6G	MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_6G
#घोषणा GP_STATUS_10G_HIG \
			MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_10G_HIG
#घोषणा GP_STATUS_10G_CX4 \
			MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_10G_CX4
#घोषणा GP_STATUS_1G_KX MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_1G_KX
#घोषणा GP_STATUS_10G_KX4 \
			MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_10G_KX4
#घोषणा	GP_STATUS_10G_KR MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_10G_KR
#घोषणा	GP_STATUS_10G_XFI   MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_10G_XFI
#घोषणा	GP_STATUS_20G_DXGXS MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_20G_DXGXS
#घोषणा	GP_STATUS_10G_SFI   MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_10G_SFI
#घोषणा	GP_STATUS_20G_KR2 MDIO_GP_STATUS_TOP_AN_STATUS1_ACTUAL_SPEED_20G_KR2
#घोषणा LINK_10THD		LINK_STATUS_SPEED_AND_DUPLEX_10THD
#घोषणा LINK_10TFD		LINK_STATUS_SPEED_AND_DUPLEX_10TFD
#घोषणा LINK_100TXHD		LINK_STATUS_SPEED_AND_DUPLEX_100TXHD
#घोषणा LINK_100T4		LINK_STATUS_SPEED_AND_DUPLEX_100T4
#घोषणा LINK_100TXFD		LINK_STATUS_SPEED_AND_DUPLEX_100TXFD
#घोषणा LINK_1000THD		LINK_STATUS_SPEED_AND_DUPLEX_1000THD
#घोषणा LINK_1000TFD		LINK_STATUS_SPEED_AND_DUPLEX_1000TFD
#घोषणा LINK_1000XFD		LINK_STATUS_SPEED_AND_DUPLEX_1000XFD
#घोषणा LINK_2500THD		LINK_STATUS_SPEED_AND_DUPLEX_2500THD
#घोषणा LINK_2500TFD		LINK_STATUS_SPEED_AND_DUPLEX_2500TFD
#घोषणा LINK_2500XFD		LINK_STATUS_SPEED_AND_DUPLEX_2500XFD
#घोषणा LINK_10GTFD		LINK_STATUS_SPEED_AND_DUPLEX_10GTFD
#घोषणा LINK_10GXFD		LINK_STATUS_SPEED_AND_DUPLEX_10GXFD
#घोषणा LINK_20GTFD		LINK_STATUS_SPEED_AND_DUPLEX_20GTFD
#घोषणा LINK_20GXFD		LINK_STATUS_SPEED_AND_DUPLEX_20GXFD

#घोषणा LINK_UPDATE_MASK \
			(LINK_STATUS_SPEED_AND_DUPLEX_MASK | \
			 LINK_STATUS_LINK_UP | \
			 LINK_STATUS_PHYSICAL_LINK_FLAG | \
			 LINK_STATUS_AUTO_NEGOTIATE_COMPLETE | \
			 LINK_STATUS_RX_FLOW_CONTROL_FLAG_MASK | \
			 LINK_STATUS_TX_FLOW_CONTROL_FLAG_MASK | \
			 LINK_STATUS_PARALLEL_DETECTION_FLAG_MASK | \
			 LINK_STATUS_LINK_PARTNER_SYMMETRIC_PAUSE | \
			 LINK_STATUS_LINK_PARTNER_ASYMMETRIC_PAUSE)

#घोषणा SFP_EEPROM_CON_TYPE_ADDR		0x2
	#घोषणा SFP_EEPROM_CON_TYPE_VAL_UNKNOWN	0x0
	#घोषणा SFP_EEPROM_CON_TYPE_VAL_LC	0x7
	#घोषणा SFP_EEPROM_CON_TYPE_VAL_COPPER	0x21
	#घोषणा SFP_EEPROM_CON_TYPE_VAL_RJ45	0x22


#घोषणा SFP_EEPROM_10G_COMP_CODE_ADDR		0x3
	#घोषणा SFP_EEPROM_10G_COMP_CODE_SR_MASK	(1<<4)
	#घोषणा SFP_EEPROM_10G_COMP_CODE_LR_MASK	(1<<5)
	#घोषणा SFP_EEPROM_10G_COMP_CODE_LRM_MASK	(1<<6)

#घोषणा SFP_EEPROM_1G_COMP_CODE_ADDR		0x6
	#घोषणा SFP_EEPROM_1G_COMP_CODE_SX	(1<<0)
	#घोषणा SFP_EEPROM_1G_COMP_CODE_LX	(1<<1)
	#घोषणा SFP_EEPROM_1G_COMP_CODE_CX	(1<<2)
	#घोषणा SFP_EEPROM_1G_COMP_CODE_BASE_T	(1<<3)

#घोषणा SFP_EEPROM_FC_TX_TECH_ADDR		0x8
	#घोषणा SFP_EEPROM_FC_TX_TECH_BITMASK_COPPER_PASSIVE 0x4
	#घोषणा SFP_EEPROM_FC_TX_TECH_BITMASK_COPPER_ACTIVE  0x8

#घोषणा SFP_EEPROM_OPTIONS_ADDR			0x40
	#घोषणा SFP_EEPROM_OPTIONS_LINEAR_RX_OUT_MASK 0x1
#घोषणा SFP_EEPROM_OPTIONS_SIZE			2

#घोषणा EDC_MODE_LINEAR				0x0022
#घोषणा EDC_MODE_LIMITING				0x0044
#घोषणा EDC_MODE_PASSIVE_DAC			0x0055
#घोषणा EDC_MODE_ACTIVE_DAC			0x0066

/* ETS defines*/
#घोषणा DCBX_INVALID_COS					(0xFF)

#घोषणा ETS_BW_LIMIT_CREDIT_UPPER_BOUND		(0x5000)
#घोषणा ETS_BW_LIMIT_CREDIT_WEIGHT		(0x5000)
#घोषणा ETS_E3B0_NIG_MIN_W_VAL_UP_TO_10GBPS		(1360)
#घोषणा ETS_E3B0_NIG_MIN_W_VAL_20GBPS			(2720)
#घोषणा ETS_E3B0_PBF_MIN_W_VAL				(10000)

#घोषणा MAX_PACKET_SIZE					(9700)
#घोषणा MAX_KR_LINK_RETRY				4
#घोषणा DEFAULT_TX_DRV_BRDCT		2
#घोषणा DEFAULT_TX_DRV_IFIR		0
#घोषणा DEFAULT_TX_DRV_POST2		3
#घोषणा DEFAULT_TX_DRV_IPRE_DRIVER	6

/**********************************************************/
/*                     INTERFACE                          */
/**********************************************************/

#घोषणा CL22_WR_OVER_CL45(_bp, _phy, _bank, _addr, _val) \
	bnx2x_cl45_ग_लिखो(_bp, _phy, \
		(_phy)->def_md_devad, \
		(_bank + (_addr & 0xf)), \
		_val)

#घोषणा CL22_RD_OVER_CL45(_bp, _phy, _bank, _addr, _val) \
	bnx2x_cl45_पढ़ो(_bp, _phy, \
		(_phy)->def_md_devad, \
		(_bank + (_addr & 0xf)), \
		_val)

अटल पूर्णांक bnx2x_check_half_खोलो_conn(काष्ठा link_params *params,
				      काष्ठा link_vars *vars, u8 notअगरy);
अटल पूर्णांक bnx2x_sfp_module_detection(काष्ठा bnx2x_phy *phy,
				      काष्ठा link_params *params);

अटल u32 bnx2x_bits_en(काष्ठा bnx2x *bp, u32 reg, u32 bits)
अणु
	u32 val = REG_RD(bp, reg);

	val |= bits;
	REG_WR(bp, reg, val);
	वापस val;
पूर्ण

अटल u32 bnx2x_bits_dis(काष्ठा bnx2x *bp, u32 reg, u32 bits)
अणु
	u32 val = REG_RD(bp, reg);

	val &= ~bits;
	REG_WR(bp, reg, val);
	वापस val;
पूर्ण

/*
 * bnx2x_check_lfa - This function checks अगर link reinitialization is required,
 *                   or link flap can be aव्योमed.
 *
 * @params:	link parameters
 * Returns 0 अगर Link Flap Aव्योमance conditions are met otherwise, the failed
 *         condition code.
 */
अटल पूर्णांक bnx2x_check_lfa(काष्ठा link_params *params)
अणु
	u32 link_status, cfg_idx, lfa_mask, cfg_size;
	u32 cur_speed_cap_mask, cur_req_fc_स्वतः_adv, additional_config;
	u32 saved_val, req_val, eee_status;
	काष्ठा bnx2x *bp = params->bp;

	additional_config =
		REG_RD(bp, params->lfa_base +
			   दुरत्व(काष्ठा shmem_lfa, additional_config));

	/* NOTE: must be first condition checked -
	* to verअगरy DCC bit is cleared in any हाल!
	*/
	अगर (additional_config & NO_LFA_DUE_TO_DCC_MASK) अणु
		DP(NETIF_MSG_LINK, "No LFA due to DCC flap after clp exit\n");
		REG_WR(bp, params->lfa_base +
			   दुरत्व(काष्ठा shmem_lfa, additional_config),
		       additional_config & ~NO_LFA_DUE_TO_DCC_MASK);
		वापस LFA_DCC_LFA_DISABLED;
	पूर्ण

	/* Verअगरy that link is up */
	link_status = REG_RD(bp, params->shmem_base +
			     दुरत्व(काष्ठा shmem_region,
				      port_mb[params->port].link_status));
	अगर (!(link_status & LINK_STATUS_LINK_UP))
		वापस LFA_LINK_DOWN;

	/* अगर loaded after BOOT from SAN, करोn't flap the link in any हाल and
	 * rely on link set by preboot driver
	 */
	अगर (params->feature_config_flags & FEATURE_CONFIG_BOOT_FROM_SAN)
		वापस 0;

	/* Verअगरy that loopback mode is not set */
	अगर (params->loopback_mode)
		वापस LFA_LOOPBACK_ENABLED;

	/* Verअगरy that MFW supports LFA */
	अगर (!params->lfa_base)
		वापस LFA_MFW_IS_TOO_OLD;

	अगर (params->num_phys == 3) अणु
		cfg_size = 2;
		lfa_mask = 0xffffffff;
	पूर्ण अन्यथा अणु
		cfg_size = 1;
		lfa_mask = 0xffff;
	पूर्ण

	/* Compare Duplex */
	saved_val = REG_RD(bp, params->lfa_base +
			   दुरत्व(काष्ठा shmem_lfa, req_duplex));
	req_val = params->req_duplex[0] | (params->req_duplex[1] << 16);
	अगर ((saved_val & lfa_mask) != (req_val & lfa_mask)) अणु
		DP(NETIF_MSG_LINK, "Duplex mismatch %x vs. %x\n",
			       (saved_val & lfa_mask), (req_val & lfa_mask));
		वापस LFA_DUPLEX_MISMATCH;
	पूर्ण
	/* Compare Flow Control */
	saved_val = REG_RD(bp, params->lfa_base +
			   दुरत्व(काष्ठा shmem_lfa, req_flow_ctrl));
	req_val = params->req_flow_ctrl[0] | (params->req_flow_ctrl[1] << 16);
	अगर ((saved_val & lfa_mask) != (req_val & lfa_mask)) अणु
		DP(NETIF_MSG_LINK, "Flow control mismatch %x vs. %x\n",
			       (saved_val & lfa_mask), (req_val & lfa_mask));
		वापस LFA_FLOW_CTRL_MISMATCH;
	पूर्ण
	/* Compare Link Speed */
	saved_val = REG_RD(bp, params->lfa_base +
			   दुरत्व(काष्ठा shmem_lfa, req_line_speed));
	req_val = params->req_line_speed[0] | (params->req_line_speed[1] << 16);
	अगर ((saved_val & lfa_mask) != (req_val & lfa_mask)) अणु
		DP(NETIF_MSG_LINK, "Link speed mismatch %x vs. %x\n",
			       (saved_val & lfa_mask), (req_val & lfa_mask));
		वापस LFA_LINK_SPEED_MISMATCH;
	पूर्ण

	क्रम (cfg_idx = 0; cfg_idx < cfg_size; cfg_idx++) अणु
		cur_speed_cap_mask = REG_RD(bp, params->lfa_base +
					    दुरत्व(काष्ठा shmem_lfa,
						     speed_cap_mask[cfg_idx]));

		अगर (cur_speed_cap_mask != params->speed_cap_mask[cfg_idx]) अणु
			DP(NETIF_MSG_LINK, "Speed Cap mismatch %x vs. %x\n",
				       cur_speed_cap_mask,
				       params->speed_cap_mask[cfg_idx]);
			वापस LFA_SPEED_CAP_MISMATCH;
		पूर्ण
	पूर्ण

	cur_req_fc_स्वतः_adv =
		REG_RD(bp, params->lfa_base +
		       दुरत्व(काष्ठा shmem_lfa, additional_config)) &
		REQ_FC_AUTO_ADV_MASK;

	अगर ((u16)cur_req_fc_स्वतः_adv != params->req_fc_स्वतः_adv) अणु
		DP(NETIF_MSG_LINK, "Flow Ctrl AN mismatch %x vs. %x\n",
			       cur_req_fc_स्वतः_adv, params->req_fc_स्वतः_adv);
		वापस LFA_FLOW_CTRL_MISMATCH;
	पूर्ण

	eee_status = REG_RD(bp, params->shmem2_base +
			    दुरत्व(काष्ठा shmem2_region,
				     eee_status[params->port]));

	अगर (((eee_status & SHMEM_EEE_LPI_REQUESTED_BIT) ^
	     (params->eee_mode & EEE_MODE_ENABLE_LPI)) ||
	    ((eee_status & SHMEM_EEE_REQUESTED_BIT) ^
	     (params->eee_mode & EEE_MODE_ADV_LPI))) अणु
		DP(NETIF_MSG_LINK, "EEE mismatch %x vs. %x\n", params->eee_mode,
			       eee_status);
		वापस LFA_EEE_MISMATCH;
	पूर्ण

	/* LFA conditions are met */
	वापस 0;
पूर्ण
/******************************************************************/
/*			EPIO/GPIO section			  */
/******************************************************************/
अटल व्योम bnx2x_get_epio(काष्ठा bnx2x *bp, u32 epio_pin, u32 *en)
अणु
	u32 epio_mask, gp_oenable;
	*en = 0;
	/* Sanity check */
	अगर (epio_pin > 31) अणु
		DP(NETIF_MSG_LINK, "Invalid EPIO pin %d to get\n", epio_pin);
		वापस;
	पूर्ण

	epio_mask = 1 << epio_pin;
	/* Set this EPIO to output */
	gp_oenable = REG_RD(bp, MCP_REG_MCPR_GP_OENABLE);
	REG_WR(bp, MCP_REG_MCPR_GP_OENABLE, gp_oenable & ~epio_mask);

	*en = (REG_RD(bp, MCP_REG_MCPR_GP_INPUTS) & epio_mask) >> epio_pin;
पूर्ण
अटल व्योम bnx2x_set_epio(काष्ठा bnx2x *bp, u32 epio_pin, u32 en)
अणु
	u32 epio_mask, gp_output, gp_oenable;

	/* Sanity check */
	अगर (epio_pin > 31) अणु
		DP(NETIF_MSG_LINK, "Invalid EPIO pin %d to set\n", epio_pin);
		वापस;
	पूर्ण
	DP(NETIF_MSG_LINK, "Setting EPIO pin %d to %d\n", epio_pin, en);
	epio_mask = 1 << epio_pin;
	/* Set this EPIO to output */
	gp_output = REG_RD(bp, MCP_REG_MCPR_GP_OUTPUTS);
	अगर (en)
		gp_output |= epio_mask;
	अन्यथा
		gp_output &= ~epio_mask;

	REG_WR(bp, MCP_REG_MCPR_GP_OUTPUTS, gp_output);

	/* Set the value क्रम this EPIO */
	gp_oenable = REG_RD(bp, MCP_REG_MCPR_GP_OENABLE);
	REG_WR(bp, MCP_REG_MCPR_GP_OENABLE, gp_oenable | epio_mask);
पूर्ण

अटल व्योम bnx2x_set_cfg_pin(काष्ठा bnx2x *bp, u32 pin_cfg, u32 val)
अणु
	अगर (pin_cfg == PIN_CFG_NA)
		वापस;
	अगर (pin_cfg >= PIN_CFG_EPIO0) अणु
		bnx2x_set_epio(bp, pin_cfg - PIN_CFG_EPIO0, val);
	पूर्ण अन्यथा अणु
		u8 gpio_num = (pin_cfg - PIN_CFG_GPIO0_P0) & 0x3;
		u8 gpio_port = (pin_cfg - PIN_CFG_GPIO0_P0) >> 2;
		bnx2x_set_gpio(bp, gpio_num, (u8)val, gpio_port);
	पूर्ण
पूर्ण

अटल u32 bnx2x_get_cfg_pin(काष्ठा bnx2x *bp, u32 pin_cfg, u32 *val)
अणु
	अगर (pin_cfg == PIN_CFG_NA)
		वापस -EINVAL;
	अगर (pin_cfg >= PIN_CFG_EPIO0) अणु
		bnx2x_get_epio(bp, pin_cfg - PIN_CFG_EPIO0, val);
	पूर्ण अन्यथा अणु
		u8 gpio_num = (pin_cfg - PIN_CFG_GPIO0_P0) & 0x3;
		u8 gpio_port = (pin_cfg - PIN_CFG_GPIO0_P0) >> 2;
		*val = bnx2x_get_gpio(bp, gpio_num, gpio_port);
	पूर्ण
	वापस 0;

पूर्ण
/******************************************************************/
/*				ETS section			  */
/******************************************************************/
अटल व्योम bnx2x_ets_e2e3a0_disabled(काष्ठा link_params *params)
अणु
	/* ETS disabled configuration*/
	काष्ठा bnx2x *bp = params->bp;

	DP(NETIF_MSG_LINK, "ETS E2E3 disabled configuration\n");

	/* mapping between entry  priority to client number (0,1,2 -debug and
	 * management clients, 3 - COS0 client, 4 - COS client)(HIGHEST)
	 * 3bits client num.
	 *   PRI4    |    PRI3    |    PRI2    |    PRI1    |    PRI0
	 * cos1-100     cos0-011     dbg1-010     dbg0-001     MCP-000
	 */

	REG_WR(bp, NIG_REG_P0_TX_ARB_PRIORITY_CLIENT, 0x4688);
	/* Biपंचांगap of 5bits length. Each bit specअगरies whether the entry behaves
	 * as strict.  Bits 0,1,2 - debug and management entries, 3 -
	 * COS0 entry, 4 - COS1 entry.
	 * COS1 | COS0 | DEBUG1 | DEBUG0 | MGMT
	 * bit4   bit3	  bit2   bit1	  bit0
	 * MCP and debug are strict
	 */

	REG_WR(bp, NIG_REG_P0_TX_ARB_CLIENT_IS_STRICT, 0x7);
	/* defines which entries (clients) are subjected to WFQ arbitration */
	REG_WR(bp, NIG_REG_P0_TX_ARB_CLIENT_IS_SUBJECT2WFQ, 0);
	/* For strict priority entries defines the number of consecutive
	 * slots क्रम the highest priority.
	 */
	REG_WR(bp, NIG_REG_P0_TX_ARB_NUM_STRICT_ARB_SLOTS, 0x100);
	/* mapping between the CREDIT_WEIGHT रेजिस्टरs and actual client
	 * numbers
	 */
	REG_WR(bp, NIG_REG_P0_TX_ARB_CLIENT_CREDIT_MAP, 0);
	REG_WR(bp, NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_0, 0);
	REG_WR(bp, NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_1, 0);

	REG_WR(bp, NIG_REG_P0_TX_ARB_CREDIT_UPPER_BOUND_0, 0);
	REG_WR(bp, NIG_REG_P0_TX_ARB_CREDIT_UPPER_BOUND_1, 0);
	REG_WR(bp, PBF_REG_HIGH_PRIORITY_COS_NUM, 0);
	/* ETS mode disable */
	REG_WR(bp, PBF_REG_ETS_ENABLED, 0);
	/* If ETS mode is enabled (there is no strict priority) defines a WFQ
	 * weight क्रम COS0/COS1.
	 */
	REG_WR(bp, PBF_REG_COS0_WEIGHT, 0x2710);
	REG_WR(bp, PBF_REG_COS1_WEIGHT, 0x2710);
	/* Upper bound that COS0_WEIGHT can reach in the WFQ arbiter */
	REG_WR(bp, PBF_REG_COS0_UPPER_BOUND, 0x989680);
	REG_WR(bp, PBF_REG_COS1_UPPER_BOUND, 0x989680);
	/* Defines the number of consecutive slots क्रम the strict priority */
	REG_WR(bp, PBF_REG_NUM_STRICT_ARB_SLOTS, 0);
पूर्ण
/******************************************************************************
* Description:
*	Getting min_w_val will be set according to line speed .
*.
******************************************************************************/
अटल u32 bnx2x_ets_get_min_w_val_nig(स्थिर काष्ठा link_vars *vars)
अणु
	u32 min_w_val = 0;
	/* Calculate min_w_val.*/
	अगर (vars->link_up) अणु
		अगर (vars->line_speed == SPEED_20000)
			min_w_val = ETS_E3B0_NIG_MIN_W_VAL_20GBPS;
		अन्यथा
			min_w_val = ETS_E3B0_NIG_MIN_W_VAL_UP_TO_10GBPS;
	पूर्ण अन्यथा
		min_w_val = ETS_E3B0_NIG_MIN_W_VAL_20GBPS;
	/* If the link isn't up (अटल configuration क्रम example ) The
	 * link will be according to 20GBPS.
	 */
	वापस min_w_val;
पूर्ण
/******************************************************************************
* Description:
*	Getting credit upper bound क्रमm min_w_val.
*.
******************************************************************************/
अटल u32 bnx2x_ets_get_credit_upper_bound(स्थिर u32 min_w_val)
अणु
	स्थिर u32 credit_upper_bound = (u32)MAXVAL((150 * min_w_val),
						MAX_PACKET_SIZE);
	वापस credit_upper_bound;
पूर्ण
/******************************************************************************
* Description:
*	Set credit upper bound क्रम NIG.
*.
******************************************************************************/
अटल व्योम bnx2x_ets_e3b0_set_credit_upper_bound_nig(
	स्थिर काष्ठा link_params *params,
	स्थिर u32 min_w_val)
अणु
	काष्ठा bnx2x *bp = params->bp;
	स्थिर u8 port = params->port;
	स्थिर u32 credit_upper_bound =
	    bnx2x_ets_get_credit_upper_bound(min_w_val);

	REG_WR(bp, (port) ? NIG_REG_P1_TX_ARB_CREDIT_UPPER_BOUND_0 :
		NIG_REG_P0_TX_ARB_CREDIT_UPPER_BOUND_0, credit_upper_bound);
	REG_WR(bp, (port) ? NIG_REG_P1_TX_ARB_CREDIT_UPPER_BOUND_1 :
		   NIG_REG_P0_TX_ARB_CREDIT_UPPER_BOUND_1, credit_upper_bound);
	REG_WR(bp, (port) ? NIG_REG_P1_TX_ARB_CREDIT_UPPER_BOUND_2 :
		   NIG_REG_P0_TX_ARB_CREDIT_UPPER_BOUND_2, credit_upper_bound);
	REG_WR(bp, (port) ? NIG_REG_P1_TX_ARB_CREDIT_UPPER_BOUND_3 :
		   NIG_REG_P0_TX_ARB_CREDIT_UPPER_BOUND_3, credit_upper_bound);
	REG_WR(bp, (port) ? NIG_REG_P1_TX_ARB_CREDIT_UPPER_BOUND_4 :
		   NIG_REG_P0_TX_ARB_CREDIT_UPPER_BOUND_4, credit_upper_bound);
	REG_WR(bp, (port) ? NIG_REG_P1_TX_ARB_CREDIT_UPPER_BOUND_5 :
		   NIG_REG_P0_TX_ARB_CREDIT_UPPER_BOUND_5, credit_upper_bound);

	अगर (!port) अणु
		REG_WR(bp, NIG_REG_P0_TX_ARB_CREDIT_UPPER_BOUND_6,
			credit_upper_bound);
		REG_WR(bp, NIG_REG_P0_TX_ARB_CREDIT_UPPER_BOUND_7,
			credit_upper_bound);
		REG_WR(bp, NIG_REG_P0_TX_ARB_CREDIT_UPPER_BOUND_8,
			credit_upper_bound);
	पूर्ण
पूर्ण
/******************************************************************************
* Description:
*	Will वापस the NIG ETS रेजिस्टरs to init values.Except
*	credit_upper_bound.
*	That isn't used in this configuration (No WFQ is enabled) and will be
*	configured according to spec
*.
******************************************************************************/
अटल व्योम bnx2x_ets_e3b0_nig_disabled(स्थिर काष्ठा link_params *params,
					स्थिर काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	स्थिर u8 port = params->port;
	स्थिर u32 min_w_val = bnx2x_ets_get_min_w_val_nig(vars);
	/* Mapping between entry  priority to client number (0,1,2 -debug and
	 * management clients, 3 - COS0 client, 4 - COS1, ... 8 -
	 * COS5)(HIGHEST) 4bits client num.TODO_ETS - Should be करोne by
	 * reset value or init tool
	 */
	अगर (port) अणु
		REG_WR(bp, NIG_REG_P1_TX_ARB_PRIORITY_CLIENT2_LSB, 0x543210);
		REG_WR(bp, NIG_REG_P1_TX_ARB_PRIORITY_CLIENT2_MSB, 0x0);
	पूर्ण अन्यथा अणु
		REG_WR(bp, NIG_REG_P0_TX_ARB_PRIORITY_CLIENT2_LSB, 0x76543210);
		REG_WR(bp, NIG_REG_P0_TX_ARB_PRIORITY_CLIENT2_MSB, 0x8);
	पूर्ण
	/* For strict priority entries defines the number of consecutive
	 * slots क्रम the highest priority.
	 */
	REG_WR(bp, (port) ? NIG_REG_P1_TX_ARB_NUM_STRICT_ARB_SLOTS :
		   NIG_REG_P0_TX_ARB_NUM_STRICT_ARB_SLOTS, 0x100);
	/* Mapping between the CREDIT_WEIGHT रेजिस्टरs and actual client
	 * numbers
	 */
	अगर (port) अणु
		/*Port 1 has 6 COS*/
		REG_WR(bp, NIG_REG_P1_TX_ARB_CLIENT_CREDIT_MAP2_LSB, 0x210543);
		REG_WR(bp, NIG_REG_P1_TX_ARB_CLIENT_CREDIT_MAP2_MSB, 0x0);
	पूर्ण अन्यथा अणु
		/*Port 0 has 9 COS*/
		REG_WR(bp, NIG_REG_P0_TX_ARB_CLIENT_CREDIT_MAP2_LSB,
		       0x43210876);
		REG_WR(bp, NIG_REG_P0_TX_ARB_CLIENT_CREDIT_MAP2_MSB, 0x5);
	पूर्ण

	/* Biपंचांगap of 5bits length. Each bit specअगरies whether the entry behaves
	 * as strict.  Bits 0,1,2 - debug and management entries, 3 -
	 * COS0 entry, 4 - COS1 entry.
	 * COS1 | COS0 | DEBUG1 | DEBUG0 | MGMT
	 * bit4   bit3	  bit2   bit1	  bit0
	 * MCP and debug are strict
	 */
	अगर (port)
		REG_WR(bp, NIG_REG_P1_TX_ARB_CLIENT_IS_STRICT, 0x3f);
	अन्यथा
		REG_WR(bp, NIG_REG_P0_TX_ARB_CLIENT_IS_STRICT, 0x1ff);
	/* defines which entries (clients) are subjected to WFQ arbitration */
	REG_WR(bp, (port) ? NIG_REG_P1_TX_ARB_CLIENT_IS_SUBJECT2WFQ :
		   NIG_REG_P0_TX_ARB_CLIENT_IS_SUBJECT2WFQ, 0);

	/* Please notice the रेजिस्टर address are note continuous and a
	 * क्रम here is note appropriate.In 2 port mode port0 only COS0-5
	 * can be used. DEBUG1,DEBUG1,MGMT are never used क्रम WFQ* In 4
	 * port mode port1 only COS0-2 can be used. DEBUG1,DEBUG1,MGMT
	 * are never used क्रम WFQ
	 */
	REG_WR(bp, (port) ? NIG_REG_P1_TX_ARB_CREDIT_WEIGHT_0 :
		   NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_0, 0x0);
	REG_WR(bp, (port) ? NIG_REG_P1_TX_ARB_CREDIT_WEIGHT_1 :
		   NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_1, 0x0);
	REG_WR(bp, (port) ? NIG_REG_P1_TX_ARB_CREDIT_WEIGHT_2 :
		   NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_2, 0x0);
	REG_WR(bp, (port) ? NIG_REG_P1_TX_ARB_CREDIT_WEIGHT_3 :
		   NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_3, 0x0);
	REG_WR(bp, (port) ? NIG_REG_P1_TX_ARB_CREDIT_WEIGHT_4 :
		   NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_4, 0x0);
	REG_WR(bp, (port) ? NIG_REG_P1_TX_ARB_CREDIT_WEIGHT_5 :
		   NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_5, 0x0);
	अगर (!port) अणु
		REG_WR(bp, NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_6, 0x0);
		REG_WR(bp, NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_7, 0x0);
		REG_WR(bp, NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_8, 0x0);
	पूर्ण

	bnx2x_ets_e3b0_set_credit_upper_bound_nig(params, min_w_val);
पूर्ण
/******************************************************************************
* Description:
*	Set credit upper bound क्रम PBF.
*.
******************************************************************************/
अटल व्योम bnx2x_ets_e3b0_set_credit_upper_bound_pbf(
	स्थिर काष्ठा link_params *params,
	स्थिर u32 min_w_val)
अणु
	काष्ठा bnx2x *bp = params->bp;
	स्थिर u32 credit_upper_bound =
	    bnx2x_ets_get_credit_upper_bound(min_w_val);
	स्थिर u8 port = params->port;
	u32 base_upper_bound = 0;
	u8 max_cos = 0;
	u8 i = 0;
	/* In 2 port mode port0 has COS0-5 that can be used क्रम WFQ.In 4
	 * port mode port1 has COS0-2 that can be used क्रम WFQ.
	 */
	अगर (!port) अणु
		base_upper_bound = PBF_REG_COS0_UPPER_BOUND_P0;
		max_cos = DCBX_E3B0_MAX_NUM_COS_PORT0;
	पूर्ण अन्यथा अणु
		base_upper_bound = PBF_REG_COS0_UPPER_BOUND_P1;
		max_cos = DCBX_E3B0_MAX_NUM_COS_PORT1;
	पूर्ण

	क्रम (i = 0; i < max_cos; i++)
		REG_WR(bp, base_upper_bound + (i << 2), credit_upper_bound);
पूर्ण

/******************************************************************************
* Description:
*	Will वापस the PBF ETS रेजिस्टरs to init values.Except
*	credit_upper_bound.
*	That isn't used in this configuration (No WFQ is enabled) and will be
*	configured according to spec
*.
******************************************************************************/
अटल व्योम bnx2x_ets_e3b0_pbf_disabled(स्थिर काष्ठा link_params *params)
अणु
	काष्ठा bnx2x *bp = params->bp;
	स्थिर u8 port = params->port;
	स्थिर u32 min_w_val_pbf = ETS_E3B0_PBF_MIN_W_VAL;
	u8 i = 0;
	u32 base_weight = 0;
	u8 max_cos = 0;

	/* Mapping between entry  priority to client number 0 - COS0
	 * client, 2 - COS1, ... 5 - COS5)(HIGHEST) 4bits client num.
	 * TODO_ETS - Should be करोne by reset value or init tool
	 */
	अगर (port)
		/*  0x688 (|011|0 10|00 1|000) */
		REG_WR(bp, PBF_REG_ETS_ARB_PRIORITY_CLIENT_P1 , 0x688);
	अन्यथा
		/*  (10 1|100 |011|0 10|00 1|000) */
		REG_WR(bp, PBF_REG_ETS_ARB_PRIORITY_CLIENT_P0 , 0x2C688);

	/* TODO_ETS - Should be करोne by reset value or init tool */
	अगर (port)
		/* 0x688 (|011|0 10|00 1|000)*/
		REG_WR(bp, PBF_REG_ETS_ARB_CLIENT_CREDIT_MAP_P1, 0x688);
	अन्यथा
	/* 0x2C688 (10 1|100 |011|0 10|00 1|000) */
	REG_WR(bp, PBF_REG_ETS_ARB_CLIENT_CREDIT_MAP_P0, 0x2C688);

	REG_WR(bp, (port) ? PBF_REG_ETS_ARB_NUM_STRICT_ARB_SLOTS_P1 :
		   PBF_REG_ETS_ARB_NUM_STRICT_ARB_SLOTS_P0 , 0x100);


	REG_WR(bp, (port) ? PBF_REG_ETS_ARB_CLIENT_IS_STRICT_P1 :
		   PBF_REG_ETS_ARB_CLIENT_IS_STRICT_P0 , 0);

	REG_WR(bp, (port) ? PBF_REG_ETS_ARB_CLIENT_IS_SUBJECT2WFQ_P1 :
		   PBF_REG_ETS_ARB_CLIENT_IS_SUBJECT2WFQ_P0 , 0);
	/* In 2 port mode port0 has COS0-5 that can be used क्रम WFQ.
	 * In 4 port mode port1 has COS0-2 that can be used क्रम WFQ.
	 */
	अगर (!port) अणु
		base_weight = PBF_REG_COS0_WEIGHT_P0;
		max_cos = DCBX_E3B0_MAX_NUM_COS_PORT0;
	पूर्ण अन्यथा अणु
		base_weight = PBF_REG_COS0_WEIGHT_P1;
		max_cos = DCBX_E3B0_MAX_NUM_COS_PORT1;
	पूर्ण

	क्रम (i = 0; i < max_cos; i++)
		REG_WR(bp, base_weight + (0x4 * i), 0);

	bnx2x_ets_e3b0_set_credit_upper_bound_pbf(params, min_w_val_pbf);
पूर्ण
/******************************************************************************
* Description:
*	E3B0 disable will वापस basically the values to init values.
*.
******************************************************************************/
अटल पूर्णांक bnx2x_ets_e3b0_disabled(स्थिर काष्ठा link_params *params,
				   स्थिर काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;

	अगर (!CHIP_IS_E3B0(bp)) अणु
		DP(NETIF_MSG_LINK,
		   "bnx2x_ets_e3b0_disabled the chip isn't E3B0\n");
		वापस -EINVAL;
	पूर्ण

	bnx2x_ets_e3b0_nig_disabled(params, vars);

	bnx2x_ets_e3b0_pbf_disabled(params);

	वापस 0;
पूर्ण

/******************************************************************************
* Description:
*	Disable will वापस basically the values to init values.
*
******************************************************************************/
पूर्णांक bnx2x_ets_disabled(काष्ठा link_params *params,
		      काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	पूर्णांक bnx2x_status = 0;

	अगर ((CHIP_IS_E2(bp)) || (CHIP_IS_E3A0(bp)))
		bnx2x_ets_e2e3a0_disabled(params);
	अन्यथा अगर (CHIP_IS_E3B0(bp))
		bnx2x_status = bnx2x_ets_e3b0_disabled(params, vars);
	अन्यथा अणु
		DP(NETIF_MSG_LINK, "bnx2x_ets_disabled - chip not supported\n");
		वापस -EINVAL;
	पूर्ण

	वापस bnx2x_status;
पूर्ण

/******************************************************************************
* Description
*	Set the COS mappimg to SP and BW until this poपूर्णांक all the COS are not
*	set as SP or BW.
******************************************************************************/
अटल पूर्णांक bnx2x_ets_e3b0_cli_map(स्थिर काष्ठा link_params *params,
				  स्थिर काष्ठा bnx2x_ets_params *ets_params,
				  स्थिर u8 cos_sp_biपंचांगap,
				  स्थिर u8 cos_bw_biपंचांगap)
अणु
	काष्ठा bnx2x *bp = params->bp;
	स्थिर u8 port = params->port;
	स्थिर u8 nig_cli_sp_biपंचांगap = 0x7 | (cos_sp_biपंचांगap << 3);
	स्थिर u8 pbf_cli_sp_biपंचांगap = cos_sp_biपंचांगap;
	स्थिर u8 nig_cli_subject2wfq_biपंचांगap = cos_bw_biपंचांगap << 3;
	स्थिर u8 pbf_cli_subject2wfq_biपंचांगap = cos_bw_biपंचांगap;

	REG_WR(bp, (port) ? NIG_REG_P1_TX_ARB_CLIENT_IS_STRICT :
	       NIG_REG_P0_TX_ARB_CLIENT_IS_STRICT, nig_cli_sp_biपंचांगap);

	REG_WR(bp, (port) ? PBF_REG_ETS_ARB_CLIENT_IS_STRICT_P1 :
	       PBF_REG_ETS_ARB_CLIENT_IS_STRICT_P0 , pbf_cli_sp_biपंचांगap);

	REG_WR(bp, (port) ? NIG_REG_P1_TX_ARB_CLIENT_IS_SUBJECT2WFQ :
	       NIG_REG_P0_TX_ARB_CLIENT_IS_SUBJECT2WFQ,
	       nig_cli_subject2wfq_biपंचांगap);

	REG_WR(bp, (port) ? PBF_REG_ETS_ARB_CLIENT_IS_SUBJECT2WFQ_P1 :
	       PBF_REG_ETS_ARB_CLIENT_IS_SUBJECT2WFQ_P0,
	       pbf_cli_subject2wfq_biपंचांगap);

	वापस 0;
पूर्ण

/******************************************************************************
* Description:
*	This function is needed because NIG ARB_CREDIT_WEIGHT_X are
*	not जारीs and ARB_CREDIT_WEIGHT_0 + offset is suitable.
******************************************************************************/
अटल पूर्णांक bnx2x_ets_e3b0_set_cos_bw(काष्ठा bnx2x *bp,
				     स्थिर u8 cos_entry,
				     स्थिर u32 min_w_val_nig,
				     स्थिर u32 min_w_val_pbf,
				     स्थिर u16 total_bw,
				     स्थिर u8 bw,
				     स्थिर u8 port)
अणु
	u32 nig_reg_adress_crd_weight = 0;
	u32 pbf_reg_adress_crd_weight = 0;
	/* Calculate and set BW क्रम this COS - use 1 instead of 0 क्रम BW */
	स्थिर u32 cos_bw_nig = ((bw ? bw : 1) * min_w_val_nig) / total_bw;
	स्थिर u32 cos_bw_pbf = ((bw ? bw : 1) * min_w_val_pbf) / total_bw;

	चयन (cos_entry) अणु
	हाल 0:
		nig_reg_adress_crd_weight =
			(port) ? NIG_REG_P1_TX_ARB_CREDIT_WEIGHT_0 :
			NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_0;
		pbf_reg_adress_crd_weight = (port) ?
		    PBF_REG_COS0_WEIGHT_P1 : PBF_REG_COS0_WEIGHT_P0;
		अवरोध;
	हाल 1:
		nig_reg_adress_crd_weight = (port) ?
			NIG_REG_P1_TX_ARB_CREDIT_WEIGHT_1 :
			NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_1;
		pbf_reg_adress_crd_weight = (port) ?
			PBF_REG_COS1_WEIGHT_P1 : PBF_REG_COS1_WEIGHT_P0;
		अवरोध;
	हाल 2:
		nig_reg_adress_crd_weight = (port) ?
			NIG_REG_P1_TX_ARB_CREDIT_WEIGHT_2 :
			NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_2;

		pbf_reg_adress_crd_weight = (port) ?
			PBF_REG_COS2_WEIGHT_P1 : PBF_REG_COS2_WEIGHT_P0;
		अवरोध;
	हाल 3:
		अगर (port)
			वापस -EINVAL;
		nig_reg_adress_crd_weight = NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_3;
		pbf_reg_adress_crd_weight = PBF_REG_COS3_WEIGHT_P0;
		अवरोध;
	हाल 4:
		अगर (port)
			वापस -EINVAL;
		nig_reg_adress_crd_weight = NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_4;
		pbf_reg_adress_crd_weight = PBF_REG_COS4_WEIGHT_P0;
		अवरोध;
	हाल 5:
		अगर (port)
			वापस -EINVAL;
		nig_reg_adress_crd_weight = NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_5;
		pbf_reg_adress_crd_weight = PBF_REG_COS5_WEIGHT_P0;
		अवरोध;
	पूर्ण

	REG_WR(bp, nig_reg_adress_crd_weight, cos_bw_nig);

	REG_WR(bp, pbf_reg_adress_crd_weight, cos_bw_pbf);

	वापस 0;
पूर्ण
/******************************************************************************
* Description:
*	Calculate the total BW.A value of 0 isn't legal.
*
******************************************************************************/
अटल पूर्णांक bnx2x_ets_e3b0_get_total_bw(
	स्थिर काष्ठा link_params *params,
	काष्ठा bnx2x_ets_params *ets_params,
	u16 *total_bw)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u8 cos_idx = 0;
	u8 is_bw_cos_exist = 0;

	*total_bw = 0 ;
	/* Calculate total BW requested */
	क्रम (cos_idx = 0; cos_idx < ets_params->num_of_cos; cos_idx++) अणु
		अगर (ets_params->cos[cos_idx].state == bnx2x_cos_state_bw) अणु
			is_bw_cos_exist = 1;
			अगर (!ets_params->cos[cos_idx].params.bw_params.bw) अणु
				DP(NETIF_MSG_LINK, "bnx2x_ets_E3B0_config BW"
						   "was set to 0\n");
				/* This is to prevent a state when ramrods
				 * can't be sent
				 */
				ets_params->cos[cos_idx].params.bw_params.bw
					 = 1;
			पूर्ण
			*total_bw +=
				ets_params->cos[cos_idx].params.bw_params.bw;
		पूर्ण
	पूर्ण

	/* Check total BW is valid */
	अगर ((is_bw_cos_exist == 1) && (*total_bw != 100)) अणु
		अगर (*total_bw == 0) अणु
			DP(NETIF_MSG_LINK,
			   "bnx2x_ets_E3B0_config total BW shouldn't be 0\n");
			वापस -EINVAL;
		पूर्ण
		DP(NETIF_MSG_LINK,
		   "bnx2x_ets_E3B0_config total BW should be 100\n");
		/* We can handle a हाल whre the BW isn't 100 this can happen
		 * अगर the TC are joined.
		 */
	पूर्ण
	वापस 0;
पूर्ण

/******************************************************************************
* Description:
*	Invalidate all the sp_pri_to_cos.
*
******************************************************************************/
अटल व्योम bnx2x_ets_e3b0_sp_pri_to_cos_init(u8 *sp_pri_to_cos)
अणु
	u8 pri = 0;
	क्रम (pri = 0; pri < DCBX_MAX_NUM_COS; pri++)
		sp_pri_to_cos[pri] = DCBX_INVALID_COS;
पूर्ण
/******************************************************************************
* Description:
*	Calculate and set the SP (ARB_PRIORITY_CLIENT) NIG and PBF रेजिस्टरs
*	according to sp_pri_to_cos.
*
******************************************************************************/
अटल पूर्णांक bnx2x_ets_e3b0_sp_pri_to_cos_set(स्थिर काष्ठा link_params *params,
					    u8 *sp_pri_to_cos, स्थिर u8 pri,
					    स्थिर u8 cos_entry)
अणु
	काष्ठा bnx2x *bp = params->bp;
	स्थिर u8 port = params->port;
	स्थिर u8 max_num_of_cos = (port) ? DCBX_E3B0_MAX_NUM_COS_PORT1 :
		DCBX_E3B0_MAX_NUM_COS_PORT0;

	अगर (pri >= max_num_of_cos) अणु
		DP(NETIF_MSG_LINK, "bnx2x_ets_e3b0_sp_pri_to_cos_set invalid "
		   "parameter Illegal strict priority\n");
		वापस -EINVAL;
	पूर्ण

	अगर (sp_pri_to_cos[pri] != DCBX_INVALID_COS) अणु
		DP(NETIF_MSG_LINK, "bnx2x_ets_e3b0_sp_pri_to_cos_set invalid "
				   "parameter There can't be two COS's with "
				   "the same strict pri\n");
		वापस -EINVAL;
	पूर्ण

	sp_pri_to_cos[pri] = cos_entry;
	वापस 0;

पूर्ण

/******************************************************************************
* Description:
*	Returns the correct value according to COS and priority in
*	the sp_pri_cli रेजिस्टर.
*
******************************************************************************/
अटल u64 bnx2x_e3b0_sp_get_pri_cli_reg(स्थिर u8 cos, स्थिर u8 cos_offset,
					 स्थिर u8 pri_set,
					 स्थिर u8 pri_offset,
					 स्थिर u8 entry_size)
अणु
	u64 pri_cli_nig = 0;
	pri_cli_nig = ((u64)(cos + cos_offset)) << (entry_size *
						    (pri_set + pri_offset));

	वापस pri_cli_nig;
पूर्ण
/******************************************************************************
* Description:
*	Returns the correct value according to COS and priority in the
*	sp_pri_cli रेजिस्टर क्रम NIG.
*
******************************************************************************/
अटल u64 bnx2x_e3b0_sp_get_pri_cli_reg_nig(स्थिर u8 cos, स्थिर u8 pri_set)
अणु
	/* MCP Dbg0 and dbg1 are always with higher strict pri*/
	स्थिर u8 nig_cos_offset = 3;
	स्थिर u8 nig_pri_offset = 3;

	वापस bnx2x_e3b0_sp_get_pri_cli_reg(cos, nig_cos_offset, pri_set,
		nig_pri_offset, 4);

पूर्ण
/******************************************************************************
* Description:
*	Returns the correct value according to COS and priority in the
*	sp_pri_cli रेजिस्टर क्रम PBF.
*
******************************************************************************/
अटल u64 bnx2x_e3b0_sp_get_pri_cli_reg_pbf(स्थिर u8 cos, स्थिर u8 pri_set)
अणु
	स्थिर u8 pbf_cos_offset = 0;
	स्थिर u8 pbf_pri_offset = 0;

	वापस bnx2x_e3b0_sp_get_pri_cli_reg(cos, pbf_cos_offset, pri_set,
		pbf_pri_offset, 3);

पूर्ण

/******************************************************************************
* Description:
*	Calculate and set the SP (ARB_PRIORITY_CLIENT) NIG and PBF रेजिस्टरs
*	according to sp_pri_to_cos.(which COS has higher priority)
*
******************************************************************************/
अटल पूर्णांक bnx2x_ets_e3b0_sp_set_pri_cli_reg(स्थिर काष्ठा link_params *params,
					     u8 *sp_pri_to_cos)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u8 i = 0;
	स्थिर u8 port = params->port;
	/* MCP Dbg0 and dbg1 are always with higher strict pri*/
	u64 pri_cli_nig = 0x210;
	u32 pri_cli_pbf = 0x0;
	u8 pri_set = 0;
	u8 pri_biपंचांगask = 0;
	स्थिर u8 max_num_of_cos = (port) ? DCBX_E3B0_MAX_NUM_COS_PORT1 :
		DCBX_E3B0_MAX_NUM_COS_PORT0;

	u8 cos_bit_to_set = (1 << max_num_of_cos) - 1;

	/* Set all the strict priority first */
	क्रम (i = 0; i < max_num_of_cos; i++) अणु
		अगर (sp_pri_to_cos[i] != DCBX_INVALID_COS) अणु
			अगर (sp_pri_to_cos[i] >= DCBX_MAX_NUM_COS) अणु
				DP(NETIF_MSG_LINK,
					   "bnx2x_ets_e3b0_sp_set_pri_cli_reg "
					   "invalid cos entry\n");
				वापस -EINVAL;
			पूर्ण

			pri_cli_nig |= bnx2x_e3b0_sp_get_pri_cli_reg_nig(
			    sp_pri_to_cos[i], pri_set);

			pri_cli_pbf |= bnx2x_e3b0_sp_get_pri_cli_reg_pbf(
			    sp_pri_to_cos[i], pri_set);
			pri_biपंचांगask = 1 << sp_pri_to_cos[i];
			/* COS is used हटाओ it from biपंचांगap.*/
			अगर (!(pri_biपंचांगask & cos_bit_to_set)) अणु
				DP(NETIF_MSG_LINK,
					"bnx2x_ets_e3b0_sp_set_pri_cli_reg "
					"invalid There can't be two COS's with"
					" the same strict pri\n");
				वापस -EINVAL;
			पूर्ण
			cos_bit_to_set &= ~pri_biपंचांगask;
			pri_set++;
		पूर्ण
	पूर्ण

	/* Set all the Non strict priority i= COS*/
	क्रम (i = 0; i < max_num_of_cos; i++) अणु
		pri_biपंचांगask = 1 << i;
		/* Check अगर COS was alपढ़ोy used क्रम SP */
		अगर (pri_biपंचांगask & cos_bit_to_set) अणु
			/* COS wasn't used क्रम SP */
			pri_cli_nig |= bnx2x_e3b0_sp_get_pri_cli_reg_nig(
			    i, pri_set);

			pri_cli_pbf |= bnx2x_e3b0_sp_get_pri_cli_reg_pbf(
			    i, pri_set);
			/* COS is used हटाओ it from biपंचांगap.*/
			cos_bit_to_set &= ~pri_biपंचांगask;
			pri_set++;
		पूर्ण
	पूर्ण

	अगर (pri_set != max_num_of_cos) अणु
		DP(NETIF_MSG_LINK, "bnx2x_ets_e3b0_sp_set_pri_cli_reg not all "
				   "entries were set\n");
		वापस -EINVAL;
	पूर्ण

	अगर (port) अणु
		/* Only 6 usable clients*/
		REG_WR(bp, NIG_REG_P1_TX_ARB_PRIORITY_CLIENT2_LSB,
		       (u32)pri_cli_nig);

		REG_WR(bp, PBF_REG_ETS_ARB_PRIORITY_CLIENT_P1 , pri_cli_pbf);
	पूर्ण अन्यथा अणु
		/* Only 9 usable clients*/
		स्थिर u32 pri_cli_nig_lsb = (u32) (pri_cli_nig);
		स्थिर u32 pri_cli_nig_msb = (u32) ((pri_cli_nig >> 32) & 0xF);

		REG_WR(bp, NIG_REG_P0_TX_ARB_PRIORITY_CLIENT2_LSB,
		       pri_cli_nig_lsb);
		REG_WR(bp, NIG_REG_P0_TX_ARB_PRIORITY_CLIENT2_MSB,
		       pri_cli_nig_msb);

		REG_WR(bp, PBF_REG_ETS_ARB_PRIORITY_CLIENT_P0 , pri_cli_pbf);
	पूर्ण
	वापस 0;
पूर्ण

/******************************************************************************
* Description:
*	Configure the COS to ETS according to BW and SP settings.
******************************************************************************/
पूर्णांक bnx2x_ets_e3b0_config(स्थिर काष्ठा link_params *params,
			 स्थिर काष्ठा link_vars *vars,
			 काष्ठा bnx2x_ets_params *ets_params)
अणु
	काष्ठा bnx2x *bp = params->bp;
	पूर्णांक bnx2x_status = 0;
	स्थिर u8 port = params->port;
	u16 total_bw = 0;
	स्थिर u32 min_w_val_nig = bnx2x_ets_get_min_w_val_nig(vars);
	स्थिर u32 min_w_val_pbf = ETS_E3B0_PBF_MIN_W_VAL;
	u8 cos_bw_biपंचांगap = 0;
	u8 cos_sp_biपंचांगap = 0;
	u8 sp_pri_to_cos[DCBX_MAX_NUM_COS] = अणु0पूर्ण;
	स्थिर u8 max_num_of_cos = (port) ? DCBX_E3B0_MAX_NUM_COS_PORT1 :
		DCBX_E3B0_MAX_NUM_COS_PORT0;
	u8 cos_entry = 0;

	अगर (!CHIP_IS_E3B0(bp)) अणु
		DP(NETIF_MSG_LINK,
		   "bnx2x_ets_e3b0_disabled the chip isn't E3B0\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((ets_params->num_of_cos > max_num_of_cos)) अणु
		DP(NETIF_MSG_LINK, "bnx2x_ets_E3B0_config the number of COS "
				   "isn't supported\n");
		वापस -EINVAL;
	पूर्ण

	/* Prepare sp strict priority parameters*/
	bnx2x_ets_e3b0_sp_pri_to_cos_init(sp_pri_to_cos);

	/* Prepare BW parameters*/
	bnx2x_status = bnx2x_ets_e3b0_get_total_bw(params, ets_params,
						   &total_bw);
	अगर (bnx2x_status) अणु
		DP(NETIF_MSG_LINK,
		   "bnx2x_ets_E3B0_config get_total_bw failed\n");
		वापस -EINVAL;
	पूर्ण

	/* Upper bound is set according to current link speed (min_w_val
	 * should be the same क्रम upper bound and COS credit val).
	 */
	bnx2x_ets_e3b0_set_credit_upper_bound_nig(params, min_w_val_nig);
	bnx2x_ets_e3b0_set_credit_upper_bound_pbf(params, min_w_val_pbf);


	क्रम (cos_entry = 0; cos_entry < ets_params->num_of_cos; cos_entry++) अणु
		अगर (bnx2x_cos_state_bw == ets_params->cos[cos_entry].state) अणु
			cos_bw_biपंचांगap |= (1 << cos_entry);
			/* The function also sets the BW in HW(not the mappin
			 * yet)
			 */
			bnx2x_status = bnx2x_ets_e3b0_set_cos_bw(
				bp, cos_entry, min_w_val_nig, min_w_val_pbf,
				total_bw,
				ets_params->cos[cos_entry].params.bw_params.bw,
				 port);
		पूर्ण अन्यथा अगर (bnx2x_cos_state_strict ==
			ets_params->cos[cos_entry].state)अणु
			cos_sp_biपंचांगap |= (1 << cos_entry);

			bnx2x_status = bnx2x_ets_e3b0_sp_pri_to_cos_set(
				params,
				sp_pri_to_cos,
				ets_params->cos[cos_entry].params.sp_params.pri,
				cos_entry);

		पूर्ण अन्यथा अणु
			DP(NETIF_MSG_LINK,
			   "bnx2x_ets_e3b0_config cos state not valid\n");
			वापस -EINVAL;
		पूर्ण
		अगर (bnx2x_status) अणु
			DP(NETIF_MSG_LINK,
			   "bnx2x_ets_e3b0_config set cos bw failed\n");
			वापस bnx2x_status;
		पूर्ण
	पूर्ण

	/* Set SP रेजिस्टर (which COS has higher priority) */
	bnx2x_status = bnx2x_ets_e3b0_sp_set_pri_cli_reg(params,
							 sp_pri_to_cos);

	अगर (bnx2x_status) अणु
		DP(NETIF_MSG_LINK,
		   "bnx2x_ets_E3B0_config set_pri_cli_reg failed\n");
		वापस bnx2x_status;
	पूर्ण

	/* Set client mapping of BW and strict */
	bnx2x_status = bnx2x_ets_e3b0_cli_map(params, ets_params,
					      cos_sp_biपंचांगap,
					      cos_bw_biपंचांगap);

	अगर (bnx2x_status) अणु
		DP(NETIF_MSG_LINK, "bnx2x_ets_E3B0_config SP failed\n");
		वापस bnx2x_status;
	पूर्ण
	वापस 0;
पूर्ण
अटल व्योम bnx2x_ets_bw_limit_common(स्थिर काष्ठा link_params *params)
अणु
	/* ETS disabled configuration */
	काष्ठा bnx2x *bp = params->bp;
	DP(NETIF_MSG_LINK, "ETS enabled BW limit configuration\n");
	/* Defines which entries (clients) are subjected to WFQ arbitration
	 * COS0 0x8
	 * COS1 0x10
	 */
	REG_WR(bp, NIG_REG_P0_TX_ARB_CLIENT_IS_SUBJECT2WFQ, 0x18);
	/* Mapping between the ARB_CREDIT_WEIGHT रेजिस्टरs and actual
	 * client numbers (WEIGHT_0 करोes not actually have to represent
	 * client 0)
	 *    PRI4    |    PRI3    |    PRI2    |    PRI1    |    PRI0
	 *  cos1-001     cos0-000     dbg1-100     dbg0-011     MCP-010
	 */
	REG_WR(bp, NIG_REG_P0_TX_ARB_CLIENT_CREDIT_MAP, 0x111A);

	REG_WR(bp, NIG_REG_P0_TX_ARB_CREDIT_UPPER_BOUND_0,
	       ETS_BW_LIMIT_CREDIT_UPPER_BOUND);
	REG_WR(bp, NIG_REG_P0_TX_ARB_CREDIT_UPPER_BOUND_1,
	       ETS_BW_LIMIT_CREDIT_UPPER_BOUND);

	/* ETS mode enabled*/
	REG_WR(bp, PBF_REG_ETS_ENABLED, 1);

	/* Defines the number of consecutive slots क्रम the strict priority */
	REG_WR(bp, PBF_REG_NUM_STRICT_ARB_SLOTS, 0);
	/* Biपंचांगap of 5bits length. Each bit specअगरies whether the entry behaves
	 * as strict.  Bits 0,1,2 - debug and management entries, 3 - COS0
	 * entry, 4 - COS1 entry.
	 * COS1 | COS0 | DEBUG21 | DEBUG0 | MGMT
	 * bit4   bit3	  bit2     bit1	   bit0
	 * MCP and debug are strict
	 */
	REG_WR(bp, NIG_REG_P0_TX_ARB_CLIENT_IS_STRICT, 0x7);

	/* Upper bound that COS0_WEIGHT can reach in the WFQ arbiter.*/
	REG_WR(bp, PBF_REG_COS0_UPPER_BOUND,
	       ETS_BW_LIMIT_CREDIT_UPPER_BOUND);
	REG_WR(bp, PBF_REG_COS1_UPPER_BOUND,
	       ETS_BW_LIMIT_CREDIT_UPPER_BOUND);
पूर्ण

व्योम bnx2x_ets_bw_limit(स्थिर काष्ठा link_params *params, स्थिर u32 cos0_bw,
			स्थिर u32 cos1_bw)
अणु
	/* ETS disabled configuration*/
	काष्ठा bnx2x *bp = params->bp;
	स्थिर u32 total_bw = cos0_bw + cos1_bw;
	u32 cos0_credit_weight = 0;
	u32 cos1_credit_weight = 0;

	DP(NETIF_MSG_LINK, "ETS enabled BW limit configuration\n");

	अगर ((!total_bw) ||
	    (!cos0_bw) ||
	    (!cos1_bw)) अणु
		DP(NETIF_MSG_LINK, "Total BW can't be zero\n");
		वापस;
	पूर्ण

	cos0_credit_weight = (cos0_bw * ETS_BW_LIMIT_CREDIT_WEIGHT)/
		total_bw;
	cos1_credit_weight = (cos1_bw * ETS_BW_LIMIT_CREDIT_WEIGHT)/
		total_bw;

	bnx2x_ets_bw_limit_common(params);

	REG_WR(bp, NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_0, cos0_credit_weight);
	REG_WR(bp, NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_1, cos1_credit_weight);

	REG_WR(bp, PBF_REG_COS0_WEIGHT, cos0_credit_weight);
	REG_WR(bp, PBF_REG_COS1_WEIGHT, cos1_credit_weight);
पूर्ण

पूर्णांक bnx2x_ets_strict(स्थिर काष्ठा link_params *params, स्थिर u8 strict_cos)
अणु
	/* ETS disabled configuration*/
	काष्ठा bnx2x *bp = params->bp;
	u32 val	= 0;

	DP(NETIF_MSG_LINK, "ETS enabled strict configuration\n");
	/* Biपंचांगap of 5bits length. Each bit specअगरies whether the entry behaves
	 * as strict.  Bits 0,1,2 - debug and management entries,
	 * 3 - COS0 entry, 4 - COS1 entry.
	 *  COS1 | COS0 | DEBUG21 | DEBUG0 | MGMT
	 *  bit4   bit3	  bit2      bit1     bit0
	 * MCP and debug are strict
	 */
	REG_WR(bp, NIG_REG_P0_TX_ARB_CLIENT_IS_STRICT, 0x1F);
	/* For strict priority entries defines the number of consecutive slots
	 * क्रम the highest priority.
	 */
	REG_WR(bp, NIG_REG_P0_TX_ARB_NUM_STRICT_ARB_SLOTS, 0x100);
	/* ETS mode disable */
	REG_WR(bp, PBF_REG_ETS_ENABLED, 0);
	/* Defines the number of consecutive slots क्रम the strict priority */
	REG_WR(bp, PBF_REG_NUM_STRICT_ARB_SLOTS, 0x100);

	/* Defines the number of consecutive slots क्रम the strict priority */
	REG_WR(bp, PBF_REG_HIGH_PRIORITY_COS_NUM, strict_cos);

	/* Mapping between entry  priority to client number (0,1,2 -debug and
	 * management clients, 3 - COS0 client, 4 - COS client)(HIGHEST)
	 * 3bits client num.
	 *   PRI4    |    PRI3    |    PRI2    |    PRI1    |    PRI0
	 * dbg0-010     dbg1-001     cos1-100     cos0-011     MCP-000
	 * dbg0-010     dbg1-001     cos0-011     cos1-100     MCP-000
	 */
	val = (!strict_cos) ? 0x2318 : 0x22E0;
	REG_WR(bp, NIG_REG_P0_TX_ARB_PRIORITY_CLIENT, val);

	वापस 0;
पूर्ण

/******************************************************************/
/*			PFC section				  */
/******************************************************************/
अटल व्योम bnx2x_update_pfc_xmac(काष्ठा link_params *params,
				  काष्ठा link_vars *vars,
				  u8 is_lb)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u32 xmac_base;
	u32 छोड़ो_val, pfc0_val, pfc1_val;

	/* XMAC base adrr */
	xmac_base = (params->port) ? GRCBASE_XMAC1 : GRCBASE_XMAC0;

	/* Initialize छोड़ो and pfc रेजिस्टरs */
	छोड़ो_val = 0x18000;
	pfc0_val = 0xFFFF8000;
	pfc1_val = 0x2;

	/* No PFC support */
	अगर (!(params->feature_config_flags &
	      FEATURE_CONFIG_PFC_ENABLED)) अणु

		/* RX flow control - Process छोड़ो frame in receive direction
		 */
		अगर (vars->flow_ctrl & BNX2X_FLOW_CTRL_RX)
			छोड़ो_val |= XMAC_PAUSE_CTRL_REG_RX_PAUSE_EN;

		/* TX flow control - Send छोड़ो packet when buffer is full */
		अगर (vars->flow_ctrl & BNX2X_FLOW_CTRL_TX)
			छोड़ो_val |= XMAC_PAUSE_CTRL_REG_TX_PAUSE_EN;
	पूर्ण अन्यथा अणु/* PFC support */
		pfc1_val |= XMAC_PFC_CTRL_HI_REG_PFC_REFRESH_EN |
			XMAC_PFC_CTRL_HI_REG_PFC_STATS_EN |
			XMAC_PFC_CTRL_HI_REG_RX_PFC_EN |
			XMAC_PFC_CTRL_HI_REG_TX_PFC_EN |
			XMAC_PFC_CTRL_HI_REG_FORCE_PFC_XON;
		/* Write छोड़ो and PFC रेजिस्टरs */
		REG_WR(bp, xmac_base + XMAC_REG_PAUSE_CTRL, छोड़ो_val);
		REG_WR(bp, xmac_base + XMAC_REG_PFC_CTRL, pfc0_val);
		REG_WR(bp, xmac_base + XMAC_REG_PFC_CTRL_HI, pfc1_val);
		pfc1_val &= ~XMAC_PFC_CTRL_HI_REG_FORCE_PFC_XON;

	पूर्ण

	/* Write छोड़ो and PFC रेजिस्टरs */
	REG_WR(bp, xmac_base + XMAC_REG_PAUSE_CTRL, छोड़ो_val);
	REG_WR(bp, xmac_base + XMAC_REG_PFC_CTRL, pfc0_val);
	REG_WR(bp, xmac_base + XMAC_REG_PFC_CTRL_HI, pfc1_val);


	/* Set MAC address क्रम source TX Pause/PFC frames */
	REG_WR(bp, xmac_base + XMAC_REG_CTRL_SA_LO,
	       ((params->mac_addr[2] << 24) |
		(params->mac_addr[3] << 16) |
		(params->mac_addr[4] << 8) |
		(params->mac_addr[5])));
	REG_WR(bp, xmac_base + XMAC_REG_CTRL_SA_HI,
	       ((params->mac_addr[0] << 8) |
		(params->mac_addr[1])));

	udelay(30);
पूर्ण

/******************************************************************/
/*			MAC/PBF section				  */
/******************************************************************/
अटल व्योम bnx2x_set_mdio_clk(काष्ठा bnx2x *bp, u32 chip_id,
			       u32 emac_base)
अणु
	u32 new_mode, cur_mode;
	u32 clc_cnt;
	/* Set clause 45 mode, slow करोwn the MDIO घड़ी to 2.5MHz
	 * (a value of 49==0x31) and make sure that the AUTO poll is off
	 */
	cur_mode = REG_RD(bp, emac_base + EMAC_REG_EMAC_MDIO_MODE);

	अगर (USES_WARPCORE(bp))
		clc_cnt = 74L << EMAC_MDIO_MODE_CLOCK_CNT_BITSHIFT;
	अन्यथा
		clc_cnt = 49L << EMAC_MDIO_MODE_CLOCK_CNT_BITSHIFT;

	अगर (((cur_mode & EMAC_MDIO_MODE_CLOCK_CNT) == clc_cnt) &&
	    (cur_mode & (EMAC_MDIO_MODE_CLAUSE_45)))
		वापस;

	new_mode = cur_mode &
		~(EMAC_MDIO_MODE_AUTO_POLL | EMAC_MDIO_MODE_CLOCK_CNT);
	new_mode |= clc_cnt;
	new_mode |= (EMAC_MDIO_MODE_CLAUSE_45);

	DP(NETIF_MSG_LINK, "Changing emac_mode from 0x%x to 0x%x\n",
	   cur_mode, new_mode);
	REG_WR(bp, emac_base + EMAC_REG_EMAC_MDIO_MODE, new_mode);
	udelay(40);
पूर्ण

अटल व्योम bnx2x_set_mdio_emac_per_phy(काष्ठा bnx2x *bp,
					काष्ठा link_params *params)
अणु
	u8 phy_index;
	/* Set mdio घड़ी per phy */
	क्रम (phy_index = INT_PHY; phy_index < params->num_phys;
	      phy_index++)
		bnx2x_set_mdio_clk(bp, params->chip_id,
				   params->phy[phy_index].mdio_ctrl);
पूर्ण

अटल u8 bnx2x_is_4_port_mode(काष्ठा bnx2x *bp)
अणु
	u32 port4mode_ovwr_val;
	/* Check 4-port override enabled */
	port4mode_ovwr_val = REG_RD(bp, MISC_REG_PORT4MODE_EN_OVWR);
	अगर (port4mode_ovwr_val & (1<<0)) अणु
		/* Return 4-port mode override value */
		वापस ((port4mode_ovwr_val & (1<<1)) == (1<<1));
	पूर्ण
	/* Return 4-port mode from input pin */
	वापस (u8)REG_RD(bp, MISC_REG_PORT4MODE_EN);
पूर्ण

अटल व्योम bnx2x_emac_init(काष्ठा link_params *params,
			    काष्ठा link_vars *vars)
अणु
	/* reset and unreset the emac core */
	काष्ठा bnx2x *bp = params->bp;
	u8 port = params->port;
	u32 emac_base = port ? GRCBASE_EMAC1 : GRCBASE_EMAC0;
	u32 val;
	u16 समयout;

	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_2_CLEAR,
	       (MISC_REGISTERS_RESET_REG_2_RST_EMAC0_HARD_CORE << port));
	udelay(5);
	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_2_SET,
	       (MISC_REGISTERS_RESET_REG_2_RST_EMAC0_HARD_CORE << port));

	/* init emac - use पढ़ो-modअगरy-ग_लिखो */
	/* self clear reset */
	val = REG_RD(bp, emac_base + EMAC_REG_EMAC_MODE);
	EMAC_WR(bp, EMAC_REG_EMAC_MODE, (val | EMAC_MODE_RESET));

	समयout = 200;
	करो अणु
		val = REG_RD(bp, emac_base + EMAC_REG_EMAC_MODE);
		DP(NETIF_MSG_LINK, "EMAC reset reg is %u\n", val);
		अगर (!समयout) अणु
			DP(NETIF_MSG_LINK, "EMAC timeout!\n");
			वापस;
		पूर्ण
		समयout--;
	पूर्ण जबतक (val & EMAC_MODE_RESET);

	bnx2x_set_mdio_emac_per_phy(bp, params);
	/* Set mac address */
	val = ((params->mac_addr[0] << 8) |
		params->mac_addr[1]);
	EMAC_WR(bp, EMAC_REG_EMAC_MAC_MATCH, val);

	val = ((params->mac_addr[2] << 24) |
	       (params->mac_addr[3] << 16) |
	       (params->mac_addr[4] << 8) |
		params->mac_addr[5]);
	EMAC_WR(bp, EMAC_REG_EMAC_MAC_MATCH + 4, val);
पूर्ण

अटल व्योम bnx2x_set_xumac_nig(काष्ठा link_params *params,
				u16 tx_छोड़ो_en,
				u8 enable)
अणु
	काष्ठा bnx2x *bp = params->bp;

	REG_WR(bp, params->port ? NIG_REG_P1_MAC_IN_EN : NIG_REG_P0_MAC_IN_EN,
	       enable);
	REG_WR(bp, params->port ? NIG_REG_P1_MAC_OUT_EN : NIG_REG_P0_MAC_OUT_EN,
	       enable);
	REG_WR(bp, params->port ? NIG_REG_P1_MAC_PAUSE_OUT_EN :
	       NIG_REG_P0_MAC_PAUSE_OUT_EN, tx_छोड़ो_en);
पूर्ण

अटल व्योम bnx2x_set_umac_rxtx(काष्ठा link_params *params, u8 en)
अणु
	u32 umac_base = params->port ? GRCBASE_UMAC1 : GRCBASE_UMAC0;
	u32 val;
	काष्ठा bnx2x *bp = params->bp;
	अगर (!(REG_RD(bp, MISC_REG_RESET_REG_2) &
		   (MISC_REGISTERS_RESET_REG_2_UMAC0 << params->port)))
		वापस;
	val = REG_RD(bp, umac_base + UMAC_REG_COMMAND_CONFIG);
	अगर (en)
		val |= (UMAC_COMMAND_CONFIG_REG_TX_ENA |
			UMAC_COMMAND_CONFIG_REG_RX_ENA);
	अन्यथा
		val &= ~(UMAC_COMMAND_CONFIG_REG_TX_ENA |
			 UMAC_COMMAND_CONFIG_REG_RX_ENA);
	/* Disable RX and TX */
	REG_WR(bp, umac_base + UMAC_REG_COMMAND_CONFIG, val);
पूर्ण

अटल व्योम bnx2x_umac_enable(काष्ठा link_params *params,
			    काष्ठा link_vars *vars, u8 lb)
अणु
	u32 val;
	u32 umac_base = params->port ? GRCBASE_UMAC1 : GRCBASE_UMAC0;
	काष्ठा bnx2x *bp = params->bp;
	/* Reset UMAC */
	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_2_CLEAR,
	       (MISC_REGISTERS_RESET_REG_2_UMAC0 << params->port));
	usleep_range(1000, 2000);

	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_2_SET,
	       (MISC_REGISTERS_RESET_REG_2_UMAC0 << params->port));

	DP(NETIF_MSG_LINK, "enabling UMAC\n");

	/* This रेजिस्टर खोलोs the gate क्रम the UMAC despite its name */
	REG_WR(bp, NIG_REG_EGRESS_EMAC0_PORT + params->port*4, 1);

	val = UMAC_COMMAND_CONFIG_REG_PROMIS_EN |
		UMAC_COMMAND_CONFIG_REG_PAD_EN |
		UMAC_COMMAND_CONFIG_REG_SW_RESET |
		UMAC_COMMAND_CONFIG_REG_NO_LGTH_CHECK;
	चयन (vars->line_speed) अणु
	हाल SPEED_10:
		val |= (0<<2);
		अवरोध;
	हाल SPEED_100:
		val |= (1<<2);
		अवरोध;
	हाल SPEED_1000:
		val |= (2<<2);
		अवरोध;
	हाल SPEED_2500:
		val |= (3<<2);
		अवरोध;
	शेष:
		DP(NETIF_MSG_LINK, "Invalid speed for UMAC %d\n",
			       vars->line_speed);
		अवरोध;
	पूर्ण
	अगर (!(vars->flow_ctrl & BNX2X_FLOW_CTRL_TX))
		val |= UMAC_COMMAND_CONFIG_REG_IGNORE_TX_PAUSE;

	अगर (!(vars->flow_ctrl & BNX2X_FLOW_CTRL_RX))
		val |= UMAC_COMMAND_CONFIG_REG_PAUSE_IGNORE;

	अगर (vars->duplex == DUPLEX_HALF)
		val |= UMAC_COMMAND_CONFIG_REG_HD_ENA;

	REG_WR(bp, umac_base + UMAC_REG_COMMAND_CONFIG, val);
	udelay(50);

	/* Configure UMAC क्रम EEE */
	अगर (vars->eee_status & SHMEM_EEE_ADV_STATUS_MASK) अणु
		DP(NETIF_MSG_LINK, "configured UMAC for EEE\n");
		REG_WR(bp, umac_base + UMAC_REG_UMAC_EEE_CTRL,
		       UMAC_UMAC_EEE_CTRL_REG_EEE_EN);
		REG_WR(bp, umac_base + UMAC_REG_EEE_WAKE_TIMER, 0x11);
	पूर्ण अन्यथा अणु
		REG_WR(bp, umac_base + UMAC_REG_UMAC_EEE_CTRL, 0x0);
	पूर्ण

	/* Set MAC address क्रम source TX Pause/PFC frames (under SW reset) */
	REG_WR(bp, umac_base + UMAC_REG_MAC_ADDR0,
	       ((params->mac_addr[2] << 24) |
		(params->mac_addr[3] << 16) |
		(params->mac_addr[4] << 8) |
		(params->mac_addr[5])));
	REG_WR(bp, umac_base + UMAC_REG_MAC_ADDR1,
	       ((params->mac_addr[0] << 8) |
		(params->mac_addr[1])));

	/* Enable RX and TX */
	val &= ~UMAC_COMMAND_CONFIG_REG_PAD_EN;
	val |= UMAC_COMMAND_CONFIG_REG_TX_ENA |
		UMAC_COMMAND_CONFIG_REG_RX_ENA;
	REG_WR(bp, umac_base + UMAC_REG_COMMAND_CONFIG, val);
	udelay(50);

	/* Remove SW Reset */
	val &= ~UMAC_COMMAND_CONFIG_REG_SW_RESET;

	/* Check loopback mode */
	अगर (lb)
		val |= UMAC_COMMAND_CONFIG_REG_LOOP_ENA;
	REG_WR(bp, umac_base + UMAC_REG_COMMAND_CONFIG, val);

	/* Maximum Frame Length (RW). Defines a 14-Bit maximum frame
	 * length used by the MAC receive logic to check frames.
	 */
	REG_WR(bp, umac_base + UMAC_REG_MAXFR, 0x2710);
	bnx2x_set_xumac_nig(params,
			    ((vars->flow_ctrl & BNX2X_FLOW_CTRL_TX) != 0), 1);
	vars->mac_type = MAC_TYPE_UMAC;

पूर्ण

/* Define the XMAC mode */
अटल व्योम bnx2x_xmac_init(काष्ठा link_params *params, u32 max_speed)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u32 is_port4mode = bnx2x_is_4_port_mode(bp);

	/* In 4-port mode, need to set the mode only once, so अगर XMAC is
	 * alपढ़ोy out of reset, it means the mode has alपढ़ोy been set,
	 * and it must not* reset the XMAC again, since it controls both
	 * ports of the path
	 */

	अगर (((CHIP_NUM(bp) == CHIP_NUM_57840_4_10) ||
	     (CHIP_NUM(bp) == CHIP_NUM_57840_2_20) ||
	     (CHIP_NUM(bp) == CHIP_NUM_57840_OBSOLETE)) &&
	    is_port4mode &&
	    (REG_RD(bp, MISC_REG_RESET_REG_2) &
	     MISC_REGISTERS_RESET_REG_2_XMAC)) अणु
		DP(NETIF_MSG_LINK,
		   "XMAC already out of reset in 4-port mode\n");
		वापस;
	पूर्ण

	/* Hard reset */
	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_2_CLEAR,
	       MISC_REGISTERS_RESET_REG_2_XMAC);
	usleep_range(1000, 2000);

	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_2_SET,
	       MISC_REGISTERS_RESET_REG_2_XMAC);
	अगर (is_port4mode) अणु
		DP(NETIF_MSG_LINK, "Init XMAC to 2 ports x 10G per path\n");

		/* Set the number of ports on the प्रणाली side to up to 2 */
		REG_WR(bp, MISC_REG_XMAC_CORE_PORT_MODE, 1);

		/* Set the number of ports on the Warp Core to 10G */
		REG_WR(bp, MISC_REG_XMAC_PHY_PORT_MODE, 3);
	पूर्ण अन्यथा अणु
		/* Set the number of ports on the प्रणाली side to 1 */
		REG_WR(bp, MISC_REG_XMAC_CORE_PORT_MODE, 0);
		अगर (max_speed == SPEED_10000) अणु
			DP(NETIF_MSG_LINK,
			   "Init XMAC to 10G x 1 port per path\n");
			/* Set the number of ports on the Warp Core to 10G */
			REG_WR(bp, MISC_REG_XMAC_PHY_PORT_MODE, 3);
		पूर्ण अन्यथा अणु
			DP(NETIF_MSG_LINK,
			   "Init XMAC to 20G x 2 ports per path\n");
			/* Set the number of ports on the Warp Core to 20G */
			REG_WR(bp, MISC_REG_XMAC_PHY_PORT_MODE, 1);
		पूर्ण
	पूर्ण
	/* Soft reset */
	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_2_CLEAR,
	       MISC_REGISTERS_RESET_REG_2_XMAC_SOFT);
	usleep_range(1000, 2000);

	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_2_SET,
	       MISC_REGISTERS_RESET_REG_2_XMAC_SOFT);

पूर्ण

अटल व्योम bnx2x_set_xmac_rxtx(काष्ठा link_params *params, u8 en)
अणु
	u8 port = params->port;
	काष्ठा bnx2x *bp = params->bp;
	u32 pfc_ctrl, xmac_base = (port) ? GRCBASE_XMAC1 : GRCBASE_XMAC0;
	u32 val;

	अगर (REG_RD(bp, MISC_REG_RESET_REG_2) &
	    MISC_REGISTERS_RESET_REG_2_XMAC) अणु
		/* Send an indication to change the state in the NIG back to XON
		 * Clearing this bit enables the next set of this bit to get
		 * rising edge
		 */
		pfc_ctrl = REG_RD(bp, xmac_base + XMAC_REG_PFC_CTRL_HI);
		REG_WR(bp, xmac_base + XMAC_REG_PFC_CTRL_HI,
		       (pfc_ctrl & ~(1<<1)));
		REG_WR(bp, xmac_base + XMAC_REG_PFC_CTRL_HI,
		       (pfc_ctrl | (1<<1)));
		DP(NETIF_MSG_LINK, "Disable XMAC on port %x\n", port);
		val = REG_RD(bp, xmac_base + XMAC_REG_CTRL);
		अगर (en)
			val |= (XMAC_CTRL_REG_TX_EN | XMAC_CTRL_REG_RX_EN);
		अन्यथा
			val &= ~(XMAC_CTRL_REG_TX_EN | XMAC_CTRL_REG_RX_EN);
		REG_WR(bp, xmac_base + XMAC_REG_CTRL, val);
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_xmac_enable(काष्ठा link_params *params,
			     काष्ठा link_vars *vars, u8 lb)
अणु
	u32 val, xmac_base;
	काष्ठा bnx2x *bp = params->bp;
	DP(NETIF_MSG_LINK, "enabling XMAC\n");

	xmac_base = (params->port) ? GRCBASE_XMAC1 : GRCBASE_XMAC0;

	bnx2x_xmac_init(params, vars->line_speed);

	/* This रेजिस्टर determines on which events the MAC will निश्चित
	 * error on the i/f to the NIG aदीर्घ w/ EOP.
	 */

	/* This रेजिस्टर tells the NIG whether to send traffic to UMAC
	 * or XMAC
	 */
	REG_WR(bp, NIG_REG_EGRESS_EMAC0_PORT + params->port*4, 0);

	/* When XMAC is in XLGMII mode, disable sending idles क्रम fault
	 * detection.
	 */
	अगर (!(params->phy[INT_PHY].flags & FLAGS_TX_ERROR_CHECK)) अणु
		REG_WR(bp, xmac_base + XMAC_REG_RX_LSS_CTRL,
		       (XMAC_RX_LSS_CTRL_REG_LOCAL_FAULT_DISABLE |
			XMAC_RX_LSS_CTRL_REG_REMOTE_FAULT_DISABLE));
		REG_WR(bp, xmac_base + XMAC_REG_CLEAR_RX_LSS_STATUS, 0);
		REG_WR(bp, xmac_base + XMAC_REG_CLEAR_RX_LSS_STATUS,
		       XMAC_CLEAR_RX_LSS_STATUS_REG_CLEAR_LOCAL_FAULT_STATUS |
		       XMAC_CLEAR_RX_LSS_STATUS_REG_CLEAR_REMOTE_FAULT_STATUS);
	पूर्ण
	/* Set Max packet size */
	REG_WR(bp, xmac_base + XMAC_REG_RX_MAX_SIZE, 0x2710);

	/* CRC append क्रम Tx packets */
	REG_WR(bp, xmac_base + XMAC_REG_TX_CTRL, 0xC800);

	/* update PFC */
	bnx2x_update_pfc_xmac(params, vars, 0);

	अगर (vars->eee_status & SHMEM_EEE_ADV_STATUS_MASK) अणु
		DP(NETIF_MSG_LINK, "Setting XMAC for EEE\n");
		REG_WR(bp, xmac_base + XMAC_REG_EEE_TIMERS_HI, 0x1380008);
		REG_WR(bp, xmac_base + XMAC_REG_EEE_CTRL, 0x1);
	पूर्ण अन्यथा अणु
		REG_WR(bp, xmac_base + XMAC_REG_EEE_CTRL, 0x0);
	पूर्ण

	/* Enable TX and RX */
	val = XMAC_CTRL_REG_TX_EN | XMAC_CTRL_REG_RX_EN;

	/* Set MAC in XLGMII mode क्रम dual-mode */
	अगर ((vars->line_speed == SPEED_20000) &&
	    (params->phy[INT_PHY].supported &
	     SUPPORTED_20000baseKR2_Full))
		val |= XMAC_CTRL_REG_XLGMII_ALIGN_ENB;

	/* Check loopback mode */
	अगर (lb)
		val |= XMAC_CTRL_REG_LINE_LOCAL_LPBK;
	REG_WR(bp, xmac_base + XMAC_REG_CTRL, val);
	bnx2x_set_xumac_nig(params,
			    ((vars->flow_ctrl & BNX2X_FLOW_CTRL_TX) != 0), 1);

	vars->mac_type = MAC_TYPE_XMAC;

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_emac_enable(काष्ठा link_params *params,
			     काष्ठा link_vars *vars, u8 lb)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u8 port = params->port;
	u32 emac_base = port ? GRCBASE_EMAC1 : GRCBASE_EMAC0;
	u32 val;

	DP(NETIF_MSG_LINK, "enabling EMAC\n");

	/* Disable BMAC */
	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_2_CLEAR,
	       (MISC_REGISTERS_RESET_REG_2_RST_BMAC0 << port));

	/* enable emac and not bmac */
	REG_WR(bp, NIG_REG_EGRESS_EMAC0_PORT + port*4, 1);

	/* ASIC */
	अगर (vars->phy_flags & PHY_XGXS_FLAG) अणु
		u32 ser_lane = ((params->lane_config &
				 PORT_HW_CFG_LANE_SWAP_CFG_MASTER_MASK) >>
				PORT_HW_CFG_LANE_SWAP_CFG_MASTER_SHIFT);

		DP(NETIF_MSG_LINK, "XGXS\n");
		/* select the master lanes (out of 0-3) */
		REG_WR(bp, NIG_REG_XGXS_LANE_SEL_P0 + port*4, ser_lane);
		/* select XGXS */
		REG_WR(bp, NIG_REG_XGXS_SERDES0_MODE_SEL + port*4, 1);

	पूर्ण अन्यथा अणु /* SerDes */
		DP(NETIF_MSG_LINK, "SerDes\n");
		/* select SerDes */
		REG_WR(bp, NIG_REG_XGXS_SERDES0_MODE_SEL + port*4, 0);
	पूर्ण

	bnx2x_bits_en(bp, emac_base + EMAC_REG_EMAC_RX_MODE,
		      EMAC_RX_MODE_RESET);
	bnx2x_bits_en(bp, emac_base + EMAC_REG_EMAC_TX_MODE,
		      EMAC_TX_MODE_RESET);

	/* छोड़ो enable/disable */
	bnx2x_bits_dis(bp, emac_base + EMAC_REG_EMAC_RX_MODE,
		       EMAC_RX_MODE_FLOW_EN);

	bnx2x_bits_dis(bp,  emac_base + EMAC_REG_EMAC_TX_MODE,
		       (EMAC_TX_MODE_EXT_PAUSE_EN |
			EMAC_TX_MODE_FLOW_EN));
	अगर (!(params->feature_config_flags &
	      FEATURE_CONFIG_PFC_ENABLED)) अणु
		अगर (vars->flow_ctrl & BNX2X_FLOW_CTRL_RX)
			bnx2x_bits_en(bp, emac_base +
				      EMAC_REG_EMAC_RX_MODE,
				      EMAC_RX_MODE_FLOW_EN);

		अगर (vars->flow_ctrl & BNX2X_FLOW_CTRL_TX)
			bnx2x_bits_en(bp, emac_base +
				      EMAC_REG_EMAC_TX_MODE,
				      (EMAC_TX_MODE_EXT_PAUSE_EN |
				       EMAC_TX_MODE_FLOW_EN));
	पूर्ण अन्यथा
		bnx2x_bits_en(bp, emac_base + EMAC_REG_EMAC_TX_MODE,
			      EMAC_TX_MODE_FLOW_EN);

	/* KEEP_VLAN_TAG, promiscuous */
	val = REG_RD(bp, emac_base + EMAC_REG_EMAC_RX_MODE);
	val |= EMAC_RX_MODE_KEEP_VLAN_TAG | EMAC_RX_MODE_PROMISCUOUS;

	/* Setting this bit causes MAC control frames (except क्रम छोड़ो
	 * frames) to be passed on क्रम processing. This setting has no
	 * affect on the operation of the छोड़ो frames. This bit effects
	 * all packets regardless of RX Parser packet sorting logic.
	 * Turn the PFC off to make sure we are in Xon state beक्रमe
	 * enabling it.
	 */
	EMAC_WR(bp, EMAC_REG_RX_PFC_MODE, 0);
	अगर (params->feature_config_flags & FEATURE_CONFIG_PFC_ENABLED) अणु
		DP(NETIF_MSG_LINK, "PFC is enabled\n");
		/* Enable PFC again */
		EMAC_WR(bp, EMAC_REG_RX_PFC_MODE,
			EMAC_REG_RX_PFC_MODE_RX_EN |
			EMAC_REG_RX_PFC_MODE_TX_EN |
			EMAC_REG_RX_PFC_MODE_PRIORITIES);

		EMAC_WR(bp, EMAC_REG_RX_PFC_PARAM,
			((0x0101 <<
			  EMAC_REG_RX_PFC_PARAM_OPCODE_BITSHIFT) |
			 (0x00ff <<
			  EMAC_REG_RX_PFC_PARAM_PRIORITY_EN_BITSHIFT)));
		val |= EMAC_RX_MODE_KEEP_MAC_CONTROL;
	पूर्ण
	EMAC_WR(bp, EMAC_REG_EMAC_RX_MODE, val);

	/* Set Loopback */
	val = REG_RD(bp, emac_base + EMAC_REG_EMAC_MODE);
	अगर (lb)
		val |= 0x810;
	अन्यथा
		val &= ~0x810;
	EMAC_WR(bp, EMAC_REG_EMAC_MODE, val);

	/* Enable emac */
	REG_WR(bp, NIG_REG_NIG_EMAC0_EN + port*4, 1);

	/* Enable emac क्रम jumbo packets */
	EMAC_WR(bp, EMAC_REG_EMAC_RX_MTU_SIZE,
		(EMAC_RX_MTU_SIZE_JUMBO_ENA |
		 (ETH_MAX_JUMBO_PACKET_SIZE + ETH_OVERHEAD)));

	/* Strip CRC */
	REG_WR(bp, NIG_REG_NIG_INGRESS_EMAC0_NO_CRC + port*4, 0x1);

	/* Disable the NIG in/out to the bmac */
	REG_WR(bp, NIG_REG_BMAC0_IN_EN + port*4, 0x0);
	REG_WR(bp, NIG_REG_BMAC0_PAUSE_OUT_EN + port*4, 0x0);
	REG_WR(bp, NIG_REG_BMAC0_OUT_EN + port*4, 0x0);

	/* Enable the NIG in/out to the emac */
	REG_WR(bp, NIG_REG_EMAC0_IN_EN + port*4, 0x1);
	val = 0;
	अगर ((params->feature_config_flags &
	      FEATURE_CONFIG_PFC_ENABLED) ||
	    (vars->flow_ctrl & BNX2X_FLOW_CTRL_TX))
		val = 1;

	REG_WR(bp, NIG_REG_EMAC0_PAUSE_OUT_EN + port*4, val);
	REG_WR(bp, NIG_REG_EGRESS_EMAC0_OUT_EN + port*4, 0x1);

	REG_WR(bp, NIG_REG_BMAC0_REGS_OUT_EN + port*4, 0x0);

	vars->mac_type = MAC_TYPE_EMAC;
	वापस 0;
पूर्ण

अटल व्योम bnx2x_update_pfc_bmac1(काष्ठा link_params *params,
				   काष्ठा link_vars *vars)
अणु
	u32 wb_data[2];
	काष्ठा bnx2x *bp = params->bp;
	u32 bmac_addr =  params->port ? NIG_REG_INGRESS_BMAC1_MEM :
		NIG_REG_INGRESS_BMAC0_MEM;

	u32 val = 0x14;
	अगर ((!(params->feature_config_flags &
	      FEATURE_CONFIG_PFC_ENABLED)) &&
		(vars->flow_ctrl & BNX2X_FLOW_CTRL_RX))
		/* Enable BigMAC to react on received Pause packets */
		val |= (1<<5);
	wb_data[0] = val;
	wb_data[1] = 0;
	REG_WR_DMAE(bp, bmac_addr + BIGMAC_REGISTER_RX_CONTROL, wb_data, 2);

	/* TX control */
	val = 0xc0;
	अगर (!(params->feature_config_flags &
	      FEATURE_CONFIG_PFC_ENABLED) &&
		(vars->flow_ctrl & BNX2X_FLOW_CTRL_TX))
		val |= 0x800000;
	wb_data[0] = val;
	wb_data[1] = 0;
	REG_WR_DMAE(bp, bmac_addr + BIGMAC_REGISTER_TX_CONTROL, wb_data, 2);
पूर्ण

अटल व्योम bnx2x_update_pfc_bmac2(काष्ठा link_params *params,
				   काष्ठा link_vars *vars,
				   u8 is_lb)
अणु
	/* Set rx control: Strip CRC and enable BigMAC to relay
	 * control packets to the प्रणाली as well
	 */
	u32 wb_data[2];
	काष्ठा bnx2x *bp = params->bp;
	u32 bmac_addr = params->port ? NIG_REG_INGRESS_BMAC1_MEM :
		NIG_REG_INGRESS_BMAC0_MEM;
	u32 val = 0x14;

	अगर ((!(params->feature_config_flags &
	      FEATURE_CONFIG_PFC_ENABLED)) &&
		(vars->flow_ctrl & BNX2X_FLOW_CTRL_RX))
		/* Enable BigMAC to react on received Pause packets */
		val |= (1<<5);
	wb_data[0] = val;
	wb_data[1] = 0;
	REG_WR_DMAE(bp, bmac_addr + BIGMAC2_REGISTER_RX_CONTROL, wb_data, 2);
	udelay(30);

	/* Tx control */
	val = 0xc0;
	अगर (!(params->feature_config_flags &
				FEATURE_CONFIG_PFC_ENABLED) &&
	    (vars->flow_ctrl & BNX2X_FLOW_CTRL_TX))
		val |= 0x800000;
	wb_data[0] = val;
	wb_data[1] = 0;
	REG_WR_DMAE(bp, bmac_addr + BIGMAC2_REGISTER_TX_CONTROL, wb_data, 2);

	अगर (params->feature_config_flags & FEATURE_CONFIG_PFC_ENABLED) अणु
		DP(NETIF_MSG_LINK, "PFC is enabled\n");
		/* Enable PFC RX & TX & STATS and set 8 COS  */
		wb_data[0] = 0x0;
		wb_data[0] |= (1<<0);  /* RX */
		wb_data[0] |= (1<<1);  /* TX */
		wb_data[0] |= (1<<2);  /* Force initial Xon */
		wb_data[0] |= (1<<3);  /* 8 cos */
		wb_data[0] |= (1<<5);  /* STATS */
		wb_data[1] = 0;
		REG_WR_DMAE(bp, bmac_addr + BIGMAC2_REGISTER_PFC_CONTROL,
			    wb_data, 2);
		/* Clear the क्रमce Xon */
		wb_data[0] &= ~(1<<2);
	पूर्ण अन्यथा अणु
		DP(NETIF_MSG_LINK, "PFC is disabled\n");
		/* Disable PFC RX & TX & STATS and set 8 COS */
		wb_data[0] = 0x8;
		wb_data[1] = 0;
	पूर्ण

	REG_WR_DMAE(bp, bmac_addr + BIGMAC2_REGISTER_PFC_CONTROL, wb_data, 2);

	/* Set Time (based unit is 512 bit समय) between स्वतःmatic
	 * re-sending of PP packets amd enable स्वतःmatic re-send of
	 * Per-Priroity Packet as दीर्घ as pp_gen is निश्चितed and
	 * pp_disable is low.
	 */
	val = 0x8000;
	अगर (params->feature_config_flags & FEATURE_CONFIG_PFC_ENABLED)
		val |= (1<<16); /* enable स्वतःmatic re-send */

	wb_data[0] = val;
	wb_data[1] = 0;
	REG_WR_DMAE(bp, bmac_addr + BIGMAC2_REGISTER_TX_PAUSE_CONTROL,
		    wb_data, 2);

	/* mac control */
	val = 0x3; /* Enable RX and TX */
	अगर (is_lb) अणु
		val |= 0x4; /* Local loopback */
		DP(NETIF_MSG_LINK, "enable bmac loopback\n");
	पूर्ण
	/* When PFC enabled, Pass छोड़ो frames towards the NIG. */
	अगर (params->feature_config_flags & FEATURE_CONFIG_PFC_ENABLED)
		val |= ((1<<6)|(1<<5));

	wb_data[0] = val;
	wb_data[1] = 0;
	REG_WR_DMAE(bp, bmac_addr + BIGMAC2_REGISTER_BMAC_CONTROL, wb_data, 2);
पूर्ण

/******************************************************************************
* Description:
*  This function is needed because NIG ARB_CREDIT_WEIGHT_X are
*  not जारीs and ARB_CREDIT_WEIGHT_0 + offset is suitable.
******************************************************************************/
अटल पूर्णांक bnx2x_pfc_nig_rx_priority_mask(काष्ठा bnx2x *bp,
					   u8 cos_entry,
					   u32 priority_mask, u8 port)
अणु
	u32 nig_reg_rx_priority_mask_add = 0;

	चयन (cos_entry) अणु
	हाल 0:
	     nig_reg_rx_priority_mask_add = (port) ?
		 NIG_REG_P1_RX_COS0_PRIORITY_MASK :
		 NIG_REG_P0_RX_COS0_PRIORITY_MASK;
	     अवरोध;
	हाल 1:
	    nig_reg_rx_priority_mask_add = (port) ?
		NIG_REG_P1_RX_COS1_PRIORITY_MASK :
		NIG_REG_P0_RX_COS1_PRIORITY_MASK;
	    अवरोध;
	हाल 2:
	    nig_reg_rx_priority_mask_add = (port) ?
		NIG_REG_P1_RX_COS2_PRIORITY_MASK :
		NIG_REG_P0_RX_COS2_PRIORITY_MASK;
	    अवरोध;
	हाल 3:
	    अगर (port)
		वापस -EINVAL;
	    nig_reg_rx_priority_mask_add = NIG_REG_P0_RX_COS3_PRIORITY_MASK;
	    अवरोध;
	हाल 4:
	    अगर (port)
		वापस -EINVAL;
	    nig_reg_rx_priority_mask_add = NIG_REG_P0_RX_COS4_PRIORITY_MASK;
	    अवरोध;
	हाल 5:
	    अगर (port)
		वापस -EINVAL;
	    nig_reg_rx_priority_mask_add = NIG_REG_P0_RX_COS5_PRIORITY_MASK;
	    अवरोध;
	पूर्ण

	REG_WR(bp, nig_reg_rx_priority_mask_add, priority_mask);

	वापस 0;
पूर्ण
अटल व्योम bnx2x_update_mng(काष्ठा link_params *params, u32 link_status)
अणु
	काष्ठा bnx2x *bp = params->bp;

	REG_WR(bp, params->shmem_base +
	       दुरत्व(काष्ठा shmem_region,
			port_mb[params->port].link_status), link_status);
पूर्ण

अटल व्योम bnx2x_update_link_attr(काष्ठा link_params *params, u32 link_attr)
अणु
	काष्ठा bnx2x *bp = params->bp;

	अगर (SHMEM2_HAS(bp, link_attr_sync))
		REG_WR(bp, params->shmem2_base +
		       दुरत्व(काष्ठा shmem2_region,
				link_attr_sync[params->port]), link_attr);
पूर्ण

अटल व्योम bnx2x_update_pfc_nig(काष्ठा link_params *params,
		काष्ठा link_vars *vars,
		काष्ठा bnx2x_nig_brb_pfc_port_params *nig_params)
अणु
	u32 xcm_mask = 0, ppp_enable = 0, छोड़ो_enable = 0, llfc_out_en = 0;
	u32 llfc_enable = 0, xcm_out_en = 0, hwpfc_enable = 0;
	u32 pkt_priority_to_cos = 0;
	काष्ठा bnx2x *bp = params->bp;
	u8 port = params->port;

	पूर्णांक set_pfc = params->feature_config_flags &
		FEATURE_CONFIG_PFC_ENABLED;
	DP(NETIF_MSG_LINK, "updating pfc nig parameters\n");

	/* When NIG_LLH0_XCM_MASK_REG_LLHX_XCM_MASK_BCN bit is set
	 * MAC control frames (that are not छोड़ो packets)
	 * will be क्रमwarded to the XCM.
	 */
	xcm_mask = REG_RD(bp, port ? NIG_REG_LLH1_XCM_MASK :
			  NIG_REG_LLH0_XCM_MASK);
	/* NIG params will override non PFC params, since it's possible to
	 * करो transition from PFC to SAFC
	 */
	अगर (set_pfc) अणु
		छोड़ो_enable = 0;
		llfc_out_en = 0;
		llfc_enable = 0;
		अगर (CHIP_IS_E3(bp))
			ppp_enable = 0;
		अन्यथा
			ppp_enable = 1;
		xcm_mask &= ~(port ? NIG_LLH1_XCM_MASK_REG_LLH1_XCM_MASK_BCN :
				     NIG_LLH0_XCM_MASK_REG_LLH0_XCM_MASK_BCN);
		xcm_out_en = 0;
		hwpfc_enable = 1;
	पूर्ण अन्यथा  अणु
		अगर (nig_params) अणु
			llfc_out_en = nig_params->llfc_out_en;
			llfc_enable = nig_params->llfc_enable;
			छोड़ो_enable = nig_params->छोड़ो_enable;
		पूर्ण अन्यथा  /* Default non PFC mode - PAUSE */
			छोड़ो_enable = 1;

		xcm_mask |= (port ? NIG_LLH1_XCM_MASK_REG_LLH1_XCM_MASK_BCN :
			NIG_LLH0_XCM_MASK_REG_LLH0_XCM_MASK_BCN);
		xcm_out_en = 1;
	पूर्ण

	अगर (CHIP_IS_E3(bp))
		REG_WR(bp, port ? NIG_REG_BRB1_PAUSE_IN_EN :
		       NIG_REG_BRB0_PAUSE_IN_EN, छोड़ो_enable);
	REG_WR(bp, port ? NIG_REG_LLFC_OUT_EN_1 :
	       NIG_REG_LLFC_OUT_EN_0, llfc_out_en);
	REG_WR(bp, port ? NIG_REG_LLFC_ENABLE_1 :
	       NIG_REG_LLFC_ENABLE_0, llfc_enable);
	REG_WR(bp, port ? NIG_REG_PAUSE_ENABLE_1 :
	       NIG_REG_PAUSE_ENABLE_0, छोड़ो_enable);

	REG_WR(bp, port ? NIG_REG_PPP_ENABLE_1 :
	       NIG_REG_PPP_ENABLE_0, ppp_enable);

	REG_WR(bp, port ? NIG_REG_LLH1_XCM_MASK :
	       NIG_REG_LLH0_XCM_MASK, xcm_mask);

	REG_WR(bp, port ? NIG_REG_LLFC_EGRESS_SRC_ENABLE_1 :
	       NIG_REG_LLFC_EGRESS_SRC_ENABLE_0, 0x7);

	/* Output enable क्रम RX_XCM # IF */
	REG_WR(bp, port ? NIG_REG_XCM1_OUT_EN :
	       NIG_REG_XCM0_OUT_EN, xcm_out_en);

	/* HW PFC TX enable */
	REG_WR(bp, port ? NIG_REG_P1_HWPFC_ENABLE :
	       NIG_REG_P0_HWPFC_ENABLE, hwpfc_enable);

	अगर (nig_params) अणु
		u8 i = 0;
		pkt_priority_to_cos = nig_params->pkt_priority_to_cos;

		क्रम (i = 0; i < nig_params->num_of_rx_cos_priority_mask; i++)
			bnx2x_pfc_nig_rx_priority_mask(bp, i,
		nig_params->rx_cos_priority_mask[i], port);

		REG_WR(bp, port ? NIG_REG_LLFC_HIGH_PRIORITY_CLASSES_1 :
		       NIG_REG_LLFC_HIGH_PRIORITY_CLASSES_0,
		       nig_params->llfc_high_priority_classes);

		REG_WR(bp, port ? NIG_REG_LLFC_LOW_PRIORITY_CLASSES_1 :
		       NIG_REG_LLFC_LOW_PRIORITY_CLASSES_0,
		       nig_params->llfc_low_priority_classes);
	पूर्ण
	REG_WR(bp, port ? NIG_REG_P1_PKT_PRIORITY_TO_COS :
	       NIG_REG_P0_PKT_PRIORITY_TO_COS,
	       pkt_priority_to_cos);
पूर्ण

पूर्णांक bnx2x_update_pfc(काष्ठा link_params *params,
		      काष्ठा link_vars *vars,
		      काष्ठा bnx2x_nig_brb_pfc_port_params *pfc_params)
अणु
	/* The PFC and छोड़ो are orthogonal to one another, meaning when
	 * PFC is enabled, the छोड़ो are disabled, and when PFC is
	 * disabled, छोड़ो are set according to the छोड़ो result.
	 */
	u32 val;
	काष्ठा bnx2x *bp = params->bp;
	u8 bmac_loopback = (params->loopback_mode == LOOPBACK_BMAC);

	अगर (params->feature_config_flags & FEATURE_CONFIG_PFC_ENABLED)
		vars->link_status |= LINK_STATUS_PFC_ENABLED;
	अन्यथा
		vars->link_status &= ~LINK_STATUS_PFC_ENABLED;

	bnx2x_update_mng(params, vars->link_status);

	/* Update NIG params */
	bnx2x_update_pfc_nig(params, vars, pfc_params);

	अगर (!vars->link_up)
		वापस 0;

	DP(NETIF_MSG_LINK, "About to update PFC in BMAC\n");

	अगर (CHIP_IS_E3(bp)) अणु
		अगर (vars->mac_type == MAC_TYPE_XMAC)
			bnx2x_update_pfc_xmac(params, vars, 0);
	पूर्ण अन्यथा अणु
		val = REG_RD(bp, MISC_REG_RESET_REG_2);
		अगर ((val &
		     (MISC_REGISTERS_RESET_REG_2_RST_BMAC0 << params->port))
		    == 0) अणु
			DP(NETIF_MSG_LINK, "About to update PFC in EMAC\n");
			bnx2x_emac_enable(params, vars, 0);
			वापस 0;
		पूर्ण
		अगर (CHIP_IS_E2(bp))
			bnx2x_update_pfc_bmac2(params, vars, bmac_loopback);
		अन्यथा
			bnx2x_update_pfc_bmac1(params, vars);

		val = 0;
		अगर ((params->feature_config_flags &
		     FEATURE_CONFIG_PFC_ENABLED) ||
		    (vars->flow_ctrl & BNX2X_FLOW_CTRL_TX))
			val = 1;
		REG_WR(bp, NIG_REG_BMAC0_PAUSE_OUT_EN + params->port*4, val);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_bmac1_enable(काष्ठा link_params *params,
			      काष्ठा link_vars *vars,
			      u8 is_lb)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u8 port = params->port;
	u32 bmac_addr = port ? NIG_REG_INGRESS_BMAC1_MEM :
			       NIG_REG_INGRESS_BMAC0_MEM;
	u32 wb_data[2];
	u32 val;

	DP(NETIF_MSG_LINK, "Enabling BigMAC1\n");

	/* XGXS control */
	wb_data[0] = 0x3c;
	wb_data[1] = 0;
	REG_WR_DMAE(bp, bmac_addr + BIGMAC_REGISTER_BMAC_XGXS_CONTROL,
		    wb_data, 2);

	/* TX MAC SA */
	wb_data[0] = ((params->mac_addr[2] << 24) |
		       (params->mac_addr[3] << 16) |
		       (params->mac_addr[4] << 8) |
			params->mac_addr[5]);
	wb_data[1] = ((params->mac_addr[0] << 8) |
			params->mac_addr[1]);
	REG_WR_DMAE(bp, bmac_addr + BIGMAC_REGISTER_TX_SOURCE_ADDR, wb_data, 2);

	/* MAC control */
	val = 0x3;
	अगर (is_lb) अणु
		val |= 0x4;
		DP(NETIF_MSG_LINK, "enable bmac loopback\n");
	पूर्ण
	wb_data[0] = val;
	wb_data[1] = 0;
	REG_WR_DMAE(bp, bmac_addr + BIGMAC_REGISTER_BMAC_CONTROL, wb_data, 2);

	/* Set rx mtu */
	wb_data[0] = ETH_MAX_JUMBO_PACKET_SIZE + ETH_OVERHEAD;
	wb_data[1] = 0;
	REG_WR_DMAE(bp, bmac_addr + BIGMAC_REGISTER_RX_MAX_SIZE, wb_data, 2);

	bnx2x_update_pfc_bmac1(params, vars);

	/* Set tx mtu */
	wb_data[0] = ETH_MAX_JUMBO_PACKET_SIZE + ETH_OVERHEAD;
	wb_data[1] = 0;
	REG_WR_DMAE(bp, bmac_addr + BIGMAC_REGISTER_TX_MAX_SIZE, wb_data, 2);

	/* Set cnt max size */
	wb_data[0] = ETH_MAX_JUMBO_PACKET_SIZE + ETH_OVERHEAD;
	wb_data[1] = 0;
	REG_WR_DMAE(bp, bmac_addr + BIGMAC_REGISTER_CNT_MAX_SIZE, wb_data, 2);

	/* Configure SAFC */
	wb_data[0] = 0x1000200;
	wb_data[1] = 0;
	REG_WR_DMAE(bp, bmac_addr + BIGMAC_REGISTER_RX_LLFC_MSG_FLDS,
		    wb_data, 2);

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_bmac2_enable(काष्ठा link_params *params,
			      काष्ठा link_vars *vars,
			      u8 is_lb)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u8 port = params->port;
	u32 bmac_addr = port ? NIG_REG_INGRESS_BMAC1_MEM :
			       NIG_REG_INGRESS_BMAC0_MEM;
	u32 wb_data[2];

	DP(NETIF_MSG_LINK, "Enabling BigMAC2\n");

	wb_data[0] = 0;
	wb_data[1] = 0;
	REG_WR_DMAE(bp, bmac_addr + BIGMAC2_REGISTER_BMAC_CONTROL, wb_data, 2);
	udelay(30);

	/* XGXS control: Reset phy HW, MDIO रेजिस्टरs, PHY PLL and BMAC */
	wb_data[0] = 0x3c;
	wb_data[1] = 0;
	REG_WR_DMAE(bp, bmac_addr + BIGMAC2_REGISTER_BMAC_XGXS_CONTROL,
		    wb_data, 2);

	udelay(30);

	/* TX MAC SA */
	wb_data[0] = ((params->mac_addr[2] << 24) |
		       (params->mac_addr[3] << 16) |
		       (params->mac_addr[4] << 8) |
			params->mac_addr[5]);
	wb_data[1] = ((params->mac_addr[0] << 8) |
			params->mac_addr[1]);
	REG_WR_DMAE(bp, bmac_addr + BIGMAC2_REGISTER_TX_SOURCE_ADDR,
		    wb_data, 2);

	udelay(30);

	/* Configure SAFC */
	wb_data[0] = 0x1000200;
	wb_data[1] = 0;
	REG_WR_DMAE(bp, bmac_addr + BIGMAC2_REGISTER_RX_LLFC_MSG_FLDS,
		    wb_data, 2);
	udelay(30);

	/* Set RX MTU */
	wb_data[0] = ETH_MAX_JUMBO_PACKET_SIZE + ETH_OVERHEAD;
	wb_data[1] = 0;
	REG_WR_DMAE(bp, bmac_addr + BIGMAC2_REGISTER_RX_MAX_SIZE, wb_data, 2);
	udelay(30);

	/* Set TX MTU */
	wb_data[0] = ETH_MAX_JUMBO_PACKET_SIZE + ETH_OVERHEAD;
	wb_data[1] = 0;
	REG_WR_DMAE(bp, bmac_addr + BIGMAC2_REGISTER_TX_MAX_SIZE, wb_data, 2);
	udelay(30);
	/* Set cnt max size */
	wb_data[0] = ETH_MAX_JUMBO_PACKET_SIZE + ETH_OVERHEAD - 2;
	wb_data[1] = 0;
	REG_WR_DMAE(bp, bmac_addr + BIGMAC2_REGISTER_CNT_MAX_SIZE, wb_data, 2);
	udelay(30);
	bnx2x_update_pfc_bmac2(params, vars, is_lb);

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_bmac_enable(काष्ठा link_params *params,
			     काष्ठा link_vars *vars,
			     u8 is_lb, u8 reset_bmac)
अणु
	पूर्णांक rc = 0;
	u8 port = params->port;
	काष्ठा bnx2x *bp = params->bp;
	u32 val;
	/* Reset and unreset the BigMac */
	अगर (reset_bmac) अणु
		REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_2_CLEAR,
		       (MISC_REGISTERS_RESET_REG_2_RST_BMAC0 << port));
		usleep_range(1000, 2000);
	पूर्ण

	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_2_SET,
	       (MISC_REGISTERS_RESET_REG_2_RST_BMAC0 << port));

	/* Enable access क्रम bmac रेजिस्टरs */
	REG_WR(bp, NIG_REG_BMAC0_REGS_OUT_EN + port*4, 0x1);

	/* Enable BMAC according to BMAC type*/
	अगर (CHIP_IS_E2(bp))
		rc = bnx2x_bmac2_enable(params, vars, is_lb);
	अन्यथा
		rc = bnx2x_bmac1_enable(params, vars, is_lb);
	REG_WR(bp, NIG_REG_XGXS_SERDES0_MODE_SEL + port*4, 0x1);
	REG_WR(bp, NIG_REG_XGXS_LANE_SEL_P0 + port*4, 0x0);
	REG_WR(bp, NIG_REG_EGRESS_EMAC0_PORT + port*4, 0x0);
	val = 0;
	अगर ((params->feature_config_flags &
	      FEATURE_CONFIG_PFC_ENABLED) ||
	    (vars->flow_ctrl & BNX2X_FLOW_CTRL_TX))
		val = 1;
	REG_WR(bp, NIG_REG_BMAC0_PAUSE_OUT_EN + port*4, val);
	REG_WR(bp, NIG_REG_EGRESS_EMAC0_OUT_EN + port*4, 0x0);
	REG_WR(bp, NIG_REG_EMAC0_IN_EN + port*4, 0x0);
	REG_WR(bp, NIG_REG_EMAC0_PAUSE_OUT_EN + port*4, 0x0);
	REG_WR(bp, NIG_REG_BMAC0_IN_EN + port*4, 0x1);
	REG_WR(bp, NIG_REG_BMAC0_OUT_EN + port*4, 0x1);

	vars->mac_type = MAC_TYPE_BMAC;
	वापस rc;
पूर्ण

अटल व्योम bnx2x_set_bmac_rx(काष्ठा bnx2x *bp, u32 chip_id, u8 port, u8 en)
अणु
	u32 bmac_addr = port ? NIG_REG_INGRESS_BMAC1_MEM :
			NIG_REG_INGRESS_BMAC0_MEM;
	u32 wb_data[2];
	u32 nig_bmac_enable = REG_RD(bp, NIG_REG_BMAC0_REGS_OUT_EN + port*4);

	अगर (CHIP_IS_E2(bp))
		bmac_addr += BIGMAC2_REGISTER_BMAC_CONTROL;
	अन्यथा
		bmac_addr += BIGMAC_REGISTER_BMAC_CONTROL;
	/* Only अगर the bmac is out of reset */
	अगर (REG_RD(bp, MISC_REG_RESET_REG_2) &
			(MISC_REGISTERS_RESET_REG_2_RST_BMAC0 << port) &&
	    nig_bmac_enable) अणु
		/* Clear Rx Enable bit in BMAC_CONTROL रेजिस्टर */
		REG_RD_DMAE(bp, bmac_addr, wb_data, 2);
		अगर (en)
			wb_data[0] |= BMAC_CONTROL_RX_ENABLE;
		अन्यथा
			wb_data[0] &= ~BMAC_CONTROL_RX_ENABLE;
		REG_WR_DMAE(bp, bmac_addr, wb_data, 2);
		usleep_range(1000, 2000);
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_pbf_update(काष्ठा link_params *params, u32 flow_ctrl,
			    u32 line_speed)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u8 port = params->port;
	u32 init_crd, crd;
	u32 count = 1000;

	/* Disable port */
	REG_WR(bp, PBF_REG_DISABLE_NEW_TASK_PROC_P0 + port*4, 0x1);

	/* Wait क्रम init credit */
	init_crd = REG_RD(bp, PBF_REG_P0_INIT_CRD + port*4);
	crd = REG_RD(bp, PBF_REG_P0_CREDIT + port*8);
	DP(NETIF_MSG_LINK, "init_crd 0x%x  crd 0x%x\n", init_crd, crd);

	जबतक ((init_crd != crd) && count) अणु
		usleep_range(5000, 10000);
		crd = REG_RD(bp, PBF_REG_P0_CREDIT + port*8);
		count--;
	पूर्ण
	crd = REG_RD(bp, PBF_REG_P0_CREDIT + port*8);
	अगर (init_crd != crd) अणु
		DP(NETIF_MSG_LINK, "BUG! init_crd 0x%x != crd 0x%x\n",
			  init_crd, crd);
		वापस -EINVAL;
	पूर्ण

	अगर (flow_ctrl & BNX2X_FLOW_CTRL_RX ||
	    line_speed == SPEED_10 ||
	    line_speed == SPEED_100 ||
	    line_speed == SPEED_1000 ||
	    line_speed == SPEED_2500) अणु
		REG_WR(bp, PBF_REG_P0_PAUSE_ENABLE + port*4, 1);
		/* Update threshold */
		REG_WR(bp, PBF_REG_P0_ARB_THRSH + port*4, 0);
		/* Update init credit */
		init_crd = 778;		/* (800-18-4) */

	पूर्ण अन्यथा अणु
		u32 thresh = (ETH_MAX_JUMBO_PACKET_SIZE +
			      ETH_OVERHEAD)/16;
		REG_WR(bp, PBF_REG_P0_PAUSE_ENABLE + port*4, 0);
		/* Update threshold */
		REG_WR(bp, PBF_REG_P0_ARB_THRSH + port*4, thresh);
		/* Update init credit */
		चयन (line_speed) अणु
		हाल SPEED_10000:
			init_crd = thresh + 553 - 22;
			अवरोध;
		शेष:
			DP(NETIF_MSG_LINK, "Invalid line_speed 0x%x\n",
				  line_speed);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	REG_WR(bp, PBF_REG_P0_INIT_CRD + port*4, init_crd);
	DP(NETIF_MSG_LINK, "PBF updated to speed %d credit %d\n",
		 line_speed, init_crd);

	/* Probe the credit changes */
	REG_WR(bp, PBF_REG_INIT_P0 + port*4, 0x1);
	usleep_range(5000, 10000);
	REG_WR(bp, PBF_REG_INIT_P0 + port*4, 0x0);

	/* Enable port */
	REG_WR(bp, PBF_REG_DISABLE_NEW_TASK_PROC_P0 + port*4, 0x0);
	वापस 0;
पूर्ण

/**
 * bnx2x_get_emac_base - retrive emac base address
 *
 * @bp:			driver handle
 * @mdc_mdio_access:	access type
 * @port:		port id
 *
 * This function selects the MDC/MDIO access (through emac0 or
 * emac1) depend on the mdc_mdio_access, port, port swapped. Each
 * phy has a शेष access mode, which could also be overridden
 * by nvram configuration. This parameter, whether this is the
 * शेष phy configuration, or the nvram overrun
 * configuration, is passed here as mdc_mdio_access and selects
 * the emac_base क्रम the CL45 पढ़ो/ग_लिखोs operations
 */
अटल u32 bnx2x_get_emac_base(काष्ठा bnx2x *bp,
			       u32 mdc_mdio_access, u8 port)
अणु
	u32 emac_base = 0;
	चयन (mdc_mdio_access) अणु
	हाल SHARED_HW_CFG_MDC_MDIO_ACCESS1_PHY_TYPE:
		अवरोध;
	हाल SHARED_HW_CFG_MDC_MDIO_ACCESS1_EMAC0:
		अगर (REG_RD(bp, NIG_REG_PORT_SWAP))
			emac_base = GRCBASE_EMAC1;
		अन्यथा
			emac_base = GRCBASE_EMAC0;
		अवरोध;
	हाल SHARED_HW_CFG_MDC_MDIO_ACCESS1_EMAC1:
		अगर (REG_RD(bp, NIG_REG_PORT_SWAP))
			emac_base = GRCBASE_EMAC0;
		अन्यथा
			emac_base = GRCBASE_EMAC1;
		अवरोध;
	हाल SHARED_HW_CFG_MDC_MDIO_ACCESS1_BOTH:
		emac_base = (port) ? GRCBASE_EMAC1 : GRCBASE_EMAC0;
		अवरोध;
	हाल SHARED_HW_CFG_MDC_MDIO_ACCESS1_SWAPPED:
		emac_base = (port) ? GRCBASE_EMAC0 : GRCBASE_EMAC1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस emac_base;

पूर्ण

/******************************************************************/
/*			CL22 access functions			  */
/******************************************************************/
अटल पूर्णांक bnx2x_cl22_ग_लिखो(काष्ठा bnx2x *bp,
				       काष्ठा bnx2x_phy *phy,
				       u16 reg, u16 val)
अणु
	u32 पंचांगp, mode;
	u8 i;
	पूर्णांक rc = 0;
	/* Switch to CL22 */
	mode = REG_RD(bp, phy->mdio_ctrl + EMAC_REG_EMAC_MDIO_MODE);
	REG_WR(bp, phy->mdio_ctrl + EMAC_REG_EMAC_MDIO_MODE,
	       mode & ~EMAC_MDIO_MODE_CLAUSE_45);

	/* Address */
	पंचांगp = ((phy->addr << 21) | (reg << 16) | val |
	       EMAC_MDIO_COMM_COMMAND_WRITE_22 |
	       EMAC_MDIO_COMM_START_BUSY);
	REG_WR(bp, phy->mdio_ctrl + EMAC_REG_EMAC_MDIO_COMM, पंचांगp);

	क्रम (i = 0; i < 50; i++) अणु
		udelay(10);

		पंचांगp = REG_RD(bp, phy->mdio_ctrl + EMAC_REG_EMAC_MDIO_COMM);
		अगर (!(पंचांगp & EMAC_MDIO_COMM_START_BUSY)) अणु
			udelay(5);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (पंचांगp & EMAC_MDIO_COMM_START_BUSY) अणु
		DP(NETIF_MSG_LINK, "write phy register failed\n");
		rc = -EFAULT;
	पूर्ण
	REG_WR(bp, phy->mdio_ctrl + EMAC_REG_EMAC_MDIO_MODE, mode);
	वापस rc;
पूर्ण

अटल पूर्णांक bnx2x_cl22_पढ़ो(काष्ठा bnx2x *bp,
				      काष्ठा bnx2x_phy *phy,
				      u16 reg, u16 *ret_val)
अणु
	u32 val, mode;
	u16 i;
	पूर्णांक rc = 0;

	/* Switch to CL22 */
	mode = REG_RD(bp, phy->mdio_ctrl + EMAC_REG_EMAC_MDIO_MODE);
	REG_WR(bp, phy->mdio_ctrl + EMAC_REG_EMAC_MDIO_MODE,
	       mode & ~EMAC_MDIO_MODE_CLAUSE_45);

	/* Address */
	val = ((phy->addr << 21) | (reg << 16) |
	       EMAC_MDIO_COMM_COMMAND_READ_22 |
	       EMAC_MDIO_COMM_START_BUSY);
	REG_WR(bp, phy->mdio_ctrl + EMAC_REG_EMAC_MDIO_COMM, val);

	क्रम (i = 0; i < 50; i++) अणु
		udelay(10);

		val = REG_RD(bp, phy->mdio_ctrl + EMAC_REG_EMAC_MDIO_COMM);
		अगर (!(val & EMAC_MDIO_COMM_START_BUSY)) अणु
			*ret_val = (u16)(val & EMAC_MDIO_COMM_DATA);
			udelay(5);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (val & EMAC_MDIO_COMM_START_BUSY) अणु
		DP(NETIF_MSG_LINK, "read phy register failed\n");

		*ret_val = 0;
		rc = -EFAULT;
	पूर्ण
	REG_WR(bp, phy->mdio_ctrl + EMAC_REG_EMAC_MDIO_MODE, mode);
	वापस rc;
पूर्ण

/******************************************************************/
/*			CL45 access functions			  */
/******************************************************************/
अटल पूर्णांक bnx2x_cl45_पढ़ो(काष्ठा bnx2x *bp, काष्ठा bnx2x_phy *phy,
			   u8 devad, u16 reg, u16 *ret_val)
अणु
	u32 val;
	u16 i;
	पूर्णांक rc = 0;
	u32 chip_id;
	अगर (phy->flags & FLAGS_MDC_MDIO_WA_G) अणु
		chip_id = (REG_RD(bp, MISC_REG_CHIP_NUM) << 16) |
			  ((REG_RD(bp, MISC_REG_CHIP_REV) & 0xf) << 12);
		bnx2x_set_mdio_clk(bp, chip_id, phy->mdio_ctrl);
	पूर्ण

	अगर (phy->flags & FLAGS_MDC_MDIO_WA_B0)
		bnx2x_bits_en(bp, phy->mdio_ctrl + EMAC_REG_EMAC_MDIO_STATUS,
			      EMAC_MDIO_STATUS_10MB);
	/* Address */
	val = ((phy->addr << 21) | (devad << 16) | reg |
	       EMAC_MDIO_COMM_COMMAND_ADDRESS |
	       EMAC_MDIO_COMM_START_BUSY);
	REG_WR(bp, phy->mdio_ctrl + EMAC_REG_EMAC_MDIO_COMM, val);

	क्रम (i = 0; i < 50; i++) अणु
		udelay(10);

		val = REG_RD(bp, phy->mdio_ctrl + EMAC_REG_EMAC_MDIO_COMM);
		अगर (!(val & EMAC_MDIO_COMM_START_BUSY)) अणु
			udelay(5);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (val & EMAC_MDIO_COMM_START_BUSY) अणु
		DP(NETIF_MSG_LINK, "read phy register failed\n");
		netdev_err(bp->dev,  "MDC/MDIO access timeout\n");
		*ret_val = 0;
		rc = -EFAULT;
	पूर्ण अन्यथा अणु
		/* Data */
		val = ((phy->addr << 21) | (devad << 16) |
		       EMAC_MDIO_COMM_COMMAND_READ_45 |
		       EMAC_MDIO_COMM_START_BUSY);
		REG_WR(bp, phy->mdio_ctrl + EMAC_REG_EMAC_MDIO_COMM, val);

		क्रम (i = 0; i < 50; i++) अणु
			udelay(10);

			val = REG_RD(bp, phy->mdio_ctrl +
				     EMAC_REG_EMAC_MDIO_COMM);
			अगर (!(val & EMAC_MDIO_COMM_START_BUSY)) अणु
				*ret_val = (u16)(val & EMAC_MDIO_COMM_DATA);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (val & EMAC_MDIO_COMM_START_BUSY) अणु
			DP(NETIF_MSG_LINK, "read phy register failed\n");
			netdev_err(bp->dev,  "MDC/MDIO access timeout\n");
			*ret_val = 0;
			rc = -EFAULT;
		पूर्ण
	पूर्ण
	/* Work around क्रम E3 A0 */
	अगर (phy->flags & FLAGS_MDC_MDIO_WA) अणु
		phy->flags ^= FLAGS_DUMMY_READ;
		अगर (phy->flags & FLAGS_DUMMY_READ) अणु
			u16 temp_val;
			bnx2x_cl45_पढ़ो(bp, phy, devad, 0xf, &temp_val);
		पूर्ण
	पूर्ण

	अगर (phy->flags & FLAGS_MDC_MDIO_WA_B0)
		bnx2x_bits_dis(bp, phy->mdio_ctrl + EMAC_REG_EMAC_MDIO_STATUS,
			       EMAC_MDIO_STATUS_10MB);
	वापस rc;
पूर्ण

अटल पूर्णांक bnx2x_cl45_ग_लिखो(काष्ठा bnx2x *bp, काष्ठा bnx2x_phy *phy,
			    u8 devad, u16 reg, u16 val)
अणु
	u32 पंचांगp;
	u8 i;
	पूर्णांक rc = 0;
	u32 chip_id;
	अगर (phy->flags & FLAGS_MDC_MDIO_WA_G) अणु
		chip_id = (REG_RD(bp, MISC_REG_CHIP_NUM) << 16) |
			  ((REG_RD(bp, MISC_REG_CHIP_REV) & 0xf) << 12);
		bnx2x_set_mdio_clk(bp, chip_id, phy->mdio_ctrl);
	पूर्ण

	अगर (phy->flags & FLAGS_MDC_MDIO_WA_B0)
		bnx2x_bits_en(bp, phy->mdio_ctrl + EMAC_REG_EMAC_MDIO_STATUS,
			      EMAC_MDIO_STATUS_10MB);

	/* Address */
	पंचांगp = ((phy->addr << 21) | (devad << 16) | reg |
	       EMAC_MDIO_COMM_COMMAND_ADDRESS |
	       EMAC_MDIO_COMM_START_BUSY);
	REG_WR(bp, phy->mdio_ctrl + EMAC_REG_EMAC_MDIO_COMM, पंचांगp);

	क्रम (i = 0; i < 50; i++) अणु
		udelay(10);

		पंचांगp = REG_RD(bp, phy->mdio_ctrl + EMAC_REG_EMAC_MDIO_COMM);
		अगर (!(पंचांगp & EMAC_MDIO_COMM_START_BUSY)) अणु
			udelay(5);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (पंचांगp & EMAC_MDIO_COMM_START_BUSY) अणु
		DP(NETIF_MSG_LINK, "write phy register failed\n");
		netdev_err(bp->dev,  "MDC/MDIO access timeout\n");
		rc = -EFAULT;
	पूर्ण अन्यथा अणु
		/* Data */
		पंचांगp = ((phy->addr << 21) | (devad << 16) | val |
		       EMAC_MDIO_COMM_COMMAND_WRITE_45 |
		       EMAC_MDIO_COMM_START_BUSY);
		REG_WR(bp, phy->mdio_ctrl + EMAC_REG_EMAC_MDIO_COMM, पंचांगp);

		क्रम (i = 0; i < 50; i++) अणु
			udelay(10);

			पंचांगp = REG_RD(bp, phy->mdio_ctrl +
				     EMAC_REG_EMAC_MDIO_COMM);
			अगर (!(पंचांगp & EMAC_MDIO_COMM_START_BUSY)) अणु
				udelay(5);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (पंचांगp & EMAC_MDIO_COMM_START_BUSY) अणु
			DP(NETIF_MSG_LINK, "write phy register failed\n");
			netdev_err(bp->dev,  "MDC/MDIO access timeout\n");
			rc = -EFAULT;
		पूर्ण
	पूर्ण
	/* Work around क्रम E3 A0 */
	अगर (phy->flags & FLAGS_MDC_MDIO_WA) अणु
		phy->flags ^= FLAGS_DUMMY_READ;
		अगर (phy->flags & FLAGS_DUMMY_READ) अणु
			u16 temp_val;
			bnx2x_cl45_पढ़ो(bp, phy, devad, 0xf, &temp_val);
		पूर्ण
	पूर्ण
	अगर (phy->flags & FLAGS_MDC_MDIO_WA_B0)
		bnx2x_bits_dis(bp, phy->mdio_ctrl + EMAC_REG_EMAC_MDIO_STATUS,
			       EMAC_MDIO_STATUS_10MB);
	वापस rc;
पूर्ण

/******************************************************************/
/*			EEE section				   */
/******************************************************************/
अटल u8 bnx2x_eee_has_cap(काष्ठा link_params *params)
अणु
	काष्ठा bnx2x *bp = params->bp;

	अगर (REG_RD(bp, params->shmem2_base) <=
		   दुरत्व(काष्ठा shmem2_region, eee_status[params->port]))
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक bnx2x_eee_nvram_to_समय(u32 nvram_mode, u32 *idle_समयr)
अणु
	चयन (nvram_mode) अणु
	हाल PORT_FEAT_CFG_EEE_POWER_MODE_BALANCED:
		*idle_समयr = EEE_MODE_NVRAM_BALANCED_TIME;
		अवरोध;
	हाल PORT_FEAT_CFG_EEE_POWER_MODE_AGGRESSIVE:
		*idle_समयr = EEE_MODE_NVRAM_AGGRESSIVE_TIME;
		अवरोध;
	हाल PORT_FEAT_CFG_EEE_POWER_MODE_LOW_LATENCY:
		*idle_समयr = EEE_MODE_NVRAM_LATENCY_TIME;
		अवरोध;
	शेष:
		*idle_समयr = 0;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_eee_समय_प्रकारo_nvram(u32 idle_समयr, u32 *nvram_mode)
अणु
	चयन (idle_समयr) अणु
	हाल EEE_MODE_NVRAM_BALANCED_TIME:
		*nvram_mode = PORT_FEAT_CFG_EEE_POWER_MODE_BALANCED;
		अवरोध;
	हाल EEE_MODE_NVRAM_AGGRESSIVE_TIME:
		*nvram_mode = PORT_FEAT_CFG_EEE_POWER_MODE_AGGRESSIVE;
		अवरोध;
	हाल EEE_MODE_NVRAM_LATENCY_TIME:
		*nvram_mode = PORT_FEAT_CFG_EEE_POWER_MODE_LOW_LATENCY;
		अवरोध;
	शेष:
		*nvram_mode = PORT_FEAT_CFG_EEE_POWER_MODE_DISABLED;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 bnx2x_eee_calc_समयr(काष्ठा link_params *params)
अणु
	u32 eee_mode, eee_idle;
	काष्ठा bnx2x *bp = params->bp;

	अगर (params->eee_mode & EEE_MODE_OVERRIDE_NVRAM) अणु
		अगर (params->eee_mode & EEE_MODE_OUTPUT_TIME) अणु
			/* समय value in eee_mode --> used directly*/
			eee_idle = params->eee_mode & EEE_MODE_TIMER_MASK;
		पूर्ण अन्यथा अणु
			/* hsi value in eee_mode --> समय */
			अगर (bnx2x_eee_nvram_to_समय(params->eee_mode &
						    EEE_MODE_NVRAM_MASK,
						    &eee_idle))
				वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* hsi values in nvram --> समय*/
		eee_mode = ((REG_RD(bp, params->shmem_base +
				    दुरत्व(काष्ठा shmem_region, dev_info.
				    port_feature_config[params->port].
				    eee_घातer_mode)) &
			     PORT_FEAT_CFG_EEE_POWER_MODE_MASK) >>
			    PORT_FEAT_CFG_EEE_POWER_MODE_SHIFT);

		अगर (bnx2x_eee_nvram_to_समय(eee_mode, &eee_idle))
			वापस 0;
	पूर्ण

	वापस eee_idle;
पूर्ण

अटल पूर्णांक bnx2x_eee_set_समयrs(काष्ठा link_params *params,
				   काष्ठा link_vars *vars)
अणु
	u32 eee_idle = 0, eee_mode;
	काष्ठा bnx2x *bp = params->bp;

	eee_idle = bnx2x_eee_calc_समयr(params);

	अगर (eee_idle) अणु
		REG_WR(bp, MISC_REG_CPMU_LP_IDLE_THR_P0 + (params->port << 2),
		       eee_idle);
	पूर्ण अन्यथा अगर ((params->eee_mode & EEE_MODE_ENABLE_LPI) &&
		   (params->eee_mode & EEE_MODE_OVERRIDE_NVRAM) &&
		   (params->eee_mode & EEE_MODE_OUTPUT_TIME)) अणु
		DP(NETIF_MSG_LINK, "Error: Tx LPI is enabled with timer 0\n");
		वापस -EINVAL;
	पूर्ण

	vars->eee_status &= ~(SHMEM_EEE_TIMER_MASK | SHMEM_EEE_TIME_OUTPUT_BIT);
	अगर (params->eee_mode & EEE_MODE_OUTPUT_TIME) अणु
		/* eee_idle in 1u --> eee_status in 16u */
		eee_idle >>= 4;
		vars->eee_status |= (eee_idle & SHMEM_EEE_TIMER_MASK) |
				    SHMEM_EEE_TIME_OUTPUT_BIT;
	पूर्ण अन्यथा अणु
		अगर (bnx2x_eee_समय_प्रकारo_nvram(eee_idle, &eee_mode))
			वापस -EINVAL;
		vars->eee_status |= eee_mode;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_eee_initial_config(काष्ठा link_params *params,
				     काष्ठा link_vars *vars, u8 mode)
अणु
	vars->eee_status |= ((u32) mode) << SHMEM_EEE_SUPPORTED_SHIFT;

	/* Propagate params' bits --> vars (क्रम migration exposure) */
	अगर (params->eee_mode & EEE_MODE_ENABLE_LPI)
		vars->eee_status |= SHMEM_EEE_LPI_REQUESTED_BIT;
	अन्यथा
		vars->eee_status &= ~SHMEM_EEE_LPI_REQUESTED_BIT;

	अगर (params->eee_mode & EEE_MODE_ADV_LPI)
		vars->eee_status |= SHMEM_EEE_REQUESTED_BIT;
	अन्यथा
		vars->eee_status &= ~SHMEM_EEE_REQUESTED_BIT;

	वापस bnx2x_eee_set_समयrs(params, vars);
पूर्ण

अटल पूर्णांक bnx2x_eee_disable(काष्ठा bnx2x_phy *phy,
				काष्ठा link_params *params,
				काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;

	/* Make Certain LPI is disabled */
	REG_WR(bp, MISC_REG_CPMU_LP_FW_ENABLE_P0 + (params->port << 2), 0);

	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_AN_DEVAD, MDIO_AN_REG_EEE_ADV, 0x0);

	vars->eee_status &= ~SHMEM_EEE_ADV_STATUS_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_eee_advertise(काष्ठा bnx2x_phy *phy,
				  काष्ठा link_params *params,
				  काष्ठा link_vars *vars, u8 modes)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 val = 0;

	/* Mask events preventing LPI generation */
	REG_WR(bp, MISC_REG_CPMU_LP_MASK_EXT_P0 + (params->port << 2), 0xfc20);

	अगर (modes & SHMEM_EEE_10G_ADV) अणु
		DP(NETIF_MSG_LINK, "Advertise 10GBase-T EEE\n");
		val |= 0x8;
	पूर्ण
	अगर (modes & SHMEM_EEE_1G_ADV) अणु
		DP(NETIF_MSG_LINK, "Advertise 1GBase-T EEE\n");
		val |= 0x4;
	पूर्ण

	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_AN_DEVAD, MDIO_AN_REG_EEE_ADV, val);

	vars->eee_status &= ~SHMEM_EEE_ADV_STATUS_MASK;
	vars->eee_status |= (modes << SHMEM_EEE_ADV_STATUS_SHIFT);

	वापस 0;
पूर्ण

अटल व्योम bnx2x_update_mng_eee(काष्ठा link_params *params, u32 eee_status)
अणु
	काष्ठा bnx2x *bp = params->bp;

	अगर (bnx2x_eee_has_cap(params))
		REG_WR(bp, params->shmem2_base +
		       दुरत्व(काष्ठा shmem2_region,
				eee_status[params->port]), eee_status);
पूर्ण

अटल व्योम bnx2x_eee_an_resolve(काष्ठा bnx2x_phy *phy,
				  काष्ठा link_params *params,
				  काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 adv = 0, lp = 0;
	u32 lp_adv = 0;
	u8 neg = 0;

	bnx2x_cl45_पढ़ो(bp, phy, MDIO_AN_DEVAD, MDIO_AN_REG_EEE_ADV, &adv);
	bnx2x_cl45_पढ़ो(bp, phy, MDIO_AN_DEVAD, MDIO_AN_REG_LP_EEE_ADV, &lp);

	अगर (lp & 0x2) अणु
		lp_adv |= SHMEM_EEE_100M_ADV;
		अगर (adv & 0x2) अणु
			अगर (vars->line_speed == SPEED_100)
				neg = 1;
			DP(NETIF_MSG_LINK, "EEE negotiated - 100M\n");
		पूर्ण
	पूर्ण
	अगर (lp & 0x14) अणु
		lp_adv |= SHMEM_EEE_1G_ADV;
		अगर (adv & 0x14) अणु
			अगर (vars->line_speed == SPEED_1000)
				neg = 1;
			DP(NETIF_MSG_LINK, "EEE negotiated - 1G\n");
		पूर्ण
	पूर्ण
	अगर (lp & 0x68) अणु
		lp_adv |= SHMEM_EEE_10G_ADV;
		अगर (adv & 0x68) अणु
			अगर (vars->line_speed == SPEED_10000)
				neg = 1;
			DP(NETIF_MSG_LINK, "EEE negotiated - 10G\n");
		पूर्ण
	पूर्ण

	vars->eee_status &= ~SHMEM_EEE_LP_ADV_STATUS_MASK;
	vars->eee_status |= (lp_adv << SHMEM_EEE_LP_ADV_STATUS_SHIFT);

	अगर (neg) अणु
		DP(NETIF_MSG_LINK, "EEE is active\n");
		vars->eee_status |= SHMEM_EEE_ACTIVE_BIT;
	पूर्ण

पूर्ण

/******************************************************************/
/*			BSC access functions from E3	          */
/******************************************************************/
अटल व्योम bnx2x_bsc_module_sel(काष्ठा link_params *params)
अणु
	पूर्णांक idx;
	u32 board_cfg, sfp_ctrl;
	u32 i2c_pins[I2C_SWITCH_WIDTH], i2c_val[I2C_SWITCH_WIDTH];
	काष्ठा bnx2x *bp = params->bp;
	u8 port = params->port;
	/* Read I2C output PINs */
	board_cfg = REG_RD(bp, params->shmem_base +
			   दुरत्व(काष्ठा shmem_region,
				    dev_info.shared_hw_config.board));
	i2c_pins[I2C_BSC0] = board_cfg & SHARED_HW_CFG_E3_I2C_MUX0_MASK;
	i2c_pins[I2C_BSC1] = (board_cfg & SHARED_HW_CFG_E3_I2C_MUX1_MASK) >>
			SHARED_HW_CFG_E3_I2C_MUX1_SHIFT;

	/* Read I2C output value */
	sfp_ctrl = REG_RD(bp, params->shmem_base +
			  दुरत्व(काष्ठा shmem_region,
				 dev_info.port_hw_config[port].e3_cmn_pin_cfg));
	i2c_val[I2C_BSC0] = (sfp_ctrl & PORT_HW_CFG_E3_I2C_MUX0_MASK) > 0;
	i2c_val[I2C_BSC1] = (sfp_ctrl & PORT_HW_CFG_E3_I2C_MUX1_MASK) > 0;
	DP(NETIF_MSG_LINK, "Setting BSC switch\n");
	क्रम (idx = 0; idx < I2C_SWITCH_WIDTH; idx++)
		bnx2x_set_cfg_pin(bp, i2c_pins[idx], i2c_val[idx]);
पूर्ण

अटल पूर्णांक bnx2x_bsc_पढ़ो(काष्ठा link_params *params,
			  काष्ठा bnx2x *bp,
			  u8 sl_devid,
			  u16 sl_addr,
			  u8 lc_addr,
			  u8 xfer_cnt,
			  u32 *data_array)
अणु
	u64 t0, delta;
	u32 val, i;
	पूर्णांक rc = 0;

	अगर (xfer_cnt > 16) अणु
		DP(NETIF_MSG_LINK, "invalid xfer_cnt %d. Max is 16 bytes\n",
					xfer_cnt);
		वापस -EINVAL;
	पूर्ण
	bnx2x_bsc_module_sel(params);

	xfer_cnt = 16 - lc_addr;

	/* Enable the engine */
	val = REG_RD(bp, MCP_REG_MCPR_IMC_COMMAND);
	val |= MCPR_IMC_COMMAND_ENABLE;
	REG_WR(bp, MCP_REG_MCPR_IMC_COMMAND, val);

	/* Program slave device ID */
	val = (sl_devid << 16) | sl_addr;
	REG_WR(bp, MCP_REG_MCPR_IMC_SLAVE_CONTROL, val);

	/* Start xfer with 0 byte to update the address poपूर्णांकer ???*/
	val = (MCPR_IMC_COMMAND_ENABLE) |
	      (MCPR_IMC_COMMAND_WRITE_OP <<
		MCPR_IMC_COMMAND_OPERATION_BITSHIFT) |
		(lc_addr << MCPR_IMC_COMMAND_TRANSFER_ADDRESS_BITSHIFT) | (0);
	REG_WR(bp, MCP_REG_MCPR_IMC_COMMAND, val);

	/* Poll क्रम completion */
	t0 = kसमय_get_ns();
	val = REG_RD(bp, MCP_REG_MCPR_IMC_COMMAND);
	जबतक (((val >> MCPR_IMC_COMMAND_IMC_STATUS_BITSHIFT) & 0x3) != 1) अणु
		delta = kसमय_get_ns() - t0;
		अगर (delta > 10 * NSEC_PER_MSEC) अणु
			DP(NETIF_MSG_LINK, "wr 0 byte timed out after %Lu ns\n",
					   delta);
			rc = -EFAULT;
			अवरोध;
		पूर्ण
		usleep_range(10, 20);
		val = REG_RD(bp, MCP_REG_MCPR_IMC_COMMAND);
	पूर्ण
	अगर (rc == -EFAULT)
		वापस rc;

	/* Start xfer with पढ़ो op */
	val = (MCPR_IMC_COMMAND_ENABLE) |
		(MCPR_IMC_COMMAND_READ_OP <<
		MCPR_IMC_COMMAND_OPERATION_BITSHIFT) |
		(lc_addr << MCPR_IMC_COMMAND_TRANSFER_ADDRESS_BITSHIFT) |
		  (xfer_cnt);
	REG_WR(bp, MCP_REG_MCPR_IMC_COMMAND, val);

	/* Poll क्रम completion */
	t0 = kसमय_get_ns();
	val = REG_RD(bp, MCP_REG_MCPR_IMC_COMMAND);
	जबतक (((val >> MCPR_IMC_COMMAND_IMC_STATUS_BITSHIFT) & 0x3) != 1) अणु
		delta = kसमय_get_ns() - t0;
		अगर (delta > 10 * NSEC_PER_MSEC) अणु
			DP(NETIF_MSG_LINK, "rd op timed out after %Lu ns\n",
					   delta);
			rc = -EFAULT;
			अवरोध;
		पूर्ण
		usleep_range(10, 20);
		val = REG_RD(bp, MCP_REG_MCPR_IMC_COMMAND);
	पूर्ण
	अगर (rc == -EFAULT)
		वापस rc;

	क्रम (i = (lc_addr >> 2); i < 4; i++) अणु
		data_array[i] = REG_RD(bp, (MCP_REG_MCPR_IMC_DATAREG0 + i*4));
#अगर_घोषित __BIG_ENDIAN
		data_array[i] = ((data_array[i] & 0x000000ff) << 24) |
				((data_array[i] & 0x0000ff00) << 8) |
				((data_array[i] & 0x00ff0000) >> 8) |
				((data_array[i] & 0xff000000) >> 24);
#पूर्ण_अगर
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम bnx2x_cl45_पढ़ो_or_ग_लिखो(काष्ठा bnx2x *bp, काष्ठा bnx2x_phy *phy,
				     u8 devad, u16 reg, u16 or_val)
अणु
	u16 val;
	bnx2x_cl45_पढ़ो(bp, phy, devad, reg, &val);
	bnx2x_cl45_ग_लिखो(bp, phy, devad, reg, val | or_val);
पूर्ण

अटल व्योम bnx2x_cl45_पढ़ो_and_ग_लिखो(काष्ठा bnx2x *bp,
				      काष्ठा bnx2x_phy *phy,
				      u8 devad, u16 reg, u16 and_val)
अणु
	u16 val;
	bnx2x_cl45_पढ़ो(bp, phy, devad, reg, &val);
	bnx2x_cl45_ग_लिखो(bp, phy, devad, reg, val & and_val);
पूर्ण

पूर्णांक bnx2x_phy_पढ़ो(काष्ठा link_params *params, u8 phy_addr,
		   u8 devad, u16 reg, u16 *ret_val)
अणु
	u8 phy_index;
	/* Probe क्रम the phy according to the given phy_addr, and execute
	 * the पढ़ो request on it
	 */
	क्रम (phy_index = 0; phy_index < params->num_phys; phy_index++) अणु
		अगर (params->phy[phy_index].addr == phy_addr) अणु
			वापस bnx2x_cl45_पढ़ो(params->bp,
					       &params->phy[phy_index], devad,
					       reg, ret_val);
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

पूर्णांक bnx2x_phy_ग_लिखो(काष्ठा link_params *params, u8 phy_addr,
		    u8 devad, u16 reg, u16 val)
अणु
	u8 phy_index;
	/* Probe क्रम the phy according to the given phy_addr, and execute
	 * the ग_लिखो request on it
	 */
	क्रम (phy_index = 0; phy_index < params->num_phys; phy_index++) अणु
		अगर (params->phy[phy_index].addr == phy_addr) अणु
			वापस bnx2x_cl45_ग_लिखो(params->bp,
						&params->phy[phy_index], devad,
						reg, val);
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण
अटल u8 bnx2x_get_warpcore_lane(काष्ठा bnx2x_phy *phy,
				  काष्ठा link_params *params)
अणु
	u8 lane = 0;
	काष्ठा bnx2x *bp = params->bp;
	u32 path_swap, path_swap_ovr;
	u8 path, port;

	path = BP_PATH(bp);
	port = params->port;

	अगर (bnx2x_is_4_port_mode(bp)) अणु
		u32 port_swap, port_swap_ovr;

		/* Figure out path swap value */
		path_swap_ovr = REG_RD(bp, MISC_REG_FOUR_PORT_PATH_SWAP_OVWR);
		अगर (path_swap_ovr & 0x1)
			path_swap = (path_swap_ovr & 0x2);
		अन्यथा
			path_swap = REG_RD(bp, MISC_REG_FOUR_PORT_PATH_SWAP);

		अगर (path_swap)
			path = path ^ 1;

		/* Figure out port swap value */
		port_swap_ovr = REG_RD(bp, MISC_REG_FOUR_PORT_PORT_SWAP_OVWR);
		अगर (port_swap_ovr & 0x1)
			port_swap = (port_swap_ovr & 0x2);
		अन्यथा
			port_swap = REG_RD(bp, MISC_REG_FOUR_PORT_PORT_SWAP);

		अगर (port_swap)
			port = port ^ 1;

		lane = (port<<1) + path;
	पूर्ण अन्यथा अणु /* Two port mode - no port swap */

		/* Figure out path swap value */
		path_swap_ovr =
			REG_RD(bp, MISC_REG_TWO_PORT_PATH_SWAP_OVWR);
		अगर (path_swap_ovr & 0x1) अणु
			path_swap = (path_swap_ovr & 0x2);
		पूर्ण अन्यथा अणु
			path_swap =
				REG_RD(bp, MISC_REG_TWO_PORT_PATH_SWAP);
		पूर्ण
		अगर (path_swap)
			path = path ^ 1;

		lane = path << 1 ;
	पूर्ण
	वापस lane;
पूर्ण

अटल व्योम bnx2x_set_aer_mmd(काष्ठा link_params *params,
			      काष्ठा bnx2x_phy *phy)
अणु
	u32 ser_lane;
	u16 offset, aer_val;
	काष्ठा bnx2x *bp = params->bp;
	ser_lane = ((params->lane_config &
		     PORT_HW_CFG_LANE_SWAP_CFG_MASTER_MASK) >>
		     PORT_HW_CFG_LANE_SWAP_CFG_MASTER_SHIFT);

	offset = (phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_सूचीECT) ?
		(phy->addr + ser_lane) : 0;

	अगर (USES_WARPCORE(bp)) अणु
		aer_val = bnx2x_get_warpcore_lane(phy, params);
		/* In Dual-lane mode, two lanes are joined together,
		 * so in order to configure them, the AER broadcast method is
		 * used here.
		 * 0x200 is the broadcast address क्रम lanes 0,1
		 * 0x201 is the broadcast address क्रम lanes 2,3
		 */
		अगर (phy->flags & FLAGS_WC_DUAL_MODE)
			aer_val = (aer_val >> 1) | 0x200;
	पूर्ण अन्यथा अगर (CHIP_IS_E2(bp))
		aer_val = 0x3800 + offset - 1;
	अन्यथा
		aer_val = 0x3800 + offset;

	CL22_WR_OVER_CL45(bp, phy, MDIO_REG_BANK_AER_BLOCK,
			  MDIO_AER_BLOCK_AER_REG, aer_val);

पूर्ण

/******************************************************************/
/*			Internal phy section			  */
/******************************************************************/

अटल व्योम bnx2x_set_serdes_access(काष्ठा bnx2x *bp, u8 port)
अणु
	u32 emac_base = (port) ? GRCBASE_EMAC1 : GRCBASE_EMAC0;

	/* Set Clause 22 */
	REG_WR(bp, NIG_REG_SERDES0_CTRL_MD_ST + port*0x10, 1);
	REG_WR(bp, emac_base + EMAC_REG_EMAC_MDIO_COMM, 0x245f8000);
	udelay(500);
	REG_WR(bp, emac_base + EMAC_REG_EMAC_MDIO_COMM, 0x245d000f);
	udelay(500);
	 /* Set Clause 45 */
	REG_WR(bp, NIG_REG_SERDES0_CTRL_MD_ST + port*0x10, 0);
पूर्ण

अटल व्योम bnx2x_serdes_deनिश्चित(काष्ठा bnx2x *bp, u8 port)
अणु
	u32 val;

	DP(NETIF_MSG_LINK, "bnx2x_serdes_deassert\n");

	val = SERDES_RESET_BITS << (port*16);

	/* Reset and unreset the SerDes/XGXS */
	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_3_CLEAR, val);
	udelay(500);
	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_3_SET, val);

	bnx2x_set_serdes_access(bp, port);

	REG_WR(bp, NIG_REG_SERDES0_CTRL_MD_DEVAD + port*0x10,
	       DEFAULT_PHY_DEV_ADDR);
पूर्ण

अटल व्योम bnx2x_xgxs_specअगरic_func(काष्ठा bnx2x_phy *phy,
				     काष्ठा link_params *params,
				     u32 action)
अणु
	काष्ठा bnx2x *bp = params->bp;
	चयन (action) अणु
	हाल PHY_INIT:
		/* Set correct devad */
		REG_WR(bp, NIG_REG_XGXS0_CTRL_MD_ST + params->port*0x18, 0);
		REG_WR(bp, NIG_REG_XGXS0_CTRL_MD_DEVAD + params->port*0x18,
		       phy->def_md_devad);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम bnx2x_xgxs_deनिश्चित(काष्ठा link_params *params)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u8 port;
	u32 val;
	DP(NETIF_MSG_LINK, "bnx2x_xgxs_deassert\n");
	port = params->port;

	val = XGXS_RESET_BITS << (port*16);

	/* Reset and unreset the SerDes/XGXS */
	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_3_CLEAR, val);
	udelay(500);
	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_3_SET, val);
	bnx2x_xgxs_specअगरic_func(&params->phy[INT_PHY], params,
				 PHY_INIT);
पूर्ण

अटल व्योम bnx2x_calc_ieee_aneg_adv(काष्ठा bnx2x_phy *phy,
				     काष्ठा link_params *params, u16 *ieee_fc)
अणु
	काष्ठा bnx2x *bp = params->bp;
	*ieee_fc = MDIO_COMBO_IEEE0_AUTO_NEG_ADV_FULL_DUPLEX;
	/* Resolve छोड़ो mode and advertisement Please refer to Table
	 * 28B-3 of the 802.3ab-1999 spec
	 */

	चयन (phy->req_flow_ctrl) अणु
	हाल BNX2X_FLOW_CTRL_AUTO:
		चयन (params->req_fc_स्वतः_adv) अणु
		हाल BNX2X_FLOW_CTRL_BOTH:
		हाल BNX2X_FLOW_CTRL_RX:
			*ieee_fc |= MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH;
			अवरोध;
		हाल BNX2X_FLOW_CTRL_TX:
			*ieee_fc |=
				MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_ASYMMETRIC;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल BNX2X_FLOW_CTRL_TX:
		*ieee_fc |= MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_ASYMMETRIC;
		अवरोध;

	हाल BNX2X_FLOW_CTRL_RX:
	हाल BNX2X_FLOW_CTRL_BOTH:
		*ieee_fc |= MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH;
		अवरोध;

	हाल BNX2X_FLOW_CTRL_NONE:
	शेष:
		*ieee_fc |= MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_NONE;
		अवरोध;
	पूर्ण
	DP(NETIF_MSG_LINK, "ieee_fc = 0x%x\n", *ieee_fc);
पूर्ण

अटल व्योम set_phy_vars(काष्ठा link_params *params,
			 काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u8 actual_phy_idx, phy_index, link_cfg_idx;
	u8 phy_config_swapped = params->multi_phy_config &
			PORT_HW_CFG_PHY_SWAPPED_ENABLED;
	क्रम (phy_index = INT_PHY; phy_index < params->num_phys;
	      phy_index++) अणु
		link_cfg_idx = LINK_CONFIG_IDX(phy_index);
		actual_phy_idx = phy_index;
		अगर (phy_config_swapped) अणु
			अगर (phy_index == EXT_PHY1)
				actual_phy_idx = EXT_PHY2;
			अन्यथा अगर (phy_index == EXT_PHY2)
				actual_phy_idx = EXT_PHY1;
		पूर्ण
		params->phy[actual_phy_idx].req_flow_ctrl =
			params->req_flow_ctrl[link_cfg_idx];

		params->phy[actual_phy_idx].req_line_speed =
			params->req_line_speed[link_cfg_idx];

		params->phy[actual_phy_idx].speed_cap_mask =
			params->speed_cap_mask[link_cfg_idx];

		params->phy[actual_phy_idx].req_duplex =
			params->req_duplex[link_cfg_idx];

		अगर (params->req_line_speed[link_cfg_idx] ==
		    SPEED_AUTO_NEG)
			vars->link_status |= LINK_STATUS_AUTO_NEGOTIATE_ENABLED;

		DP(NETIF_MSG_LINK, "req_flow_ctrl %x, req_line_speed %x,"
			   " speed_cap_mask %x\n",
			   params->phy[actual_phy_idx].req_flow_ctrl,
			   params->phy[actual_phy_idx].req_line_speed,
			   params->phy[actual_phy_idx].speed_cap_mask);
	पूर्ण
पूर्ण

अटल व्योम bnx2x_ext_phy_set_छोड़ो(काष्ठा link_params *params,
				    काष्ठा bnx2x_phy *phy,
				    काष्ठा link_vars *vars)
अणु
	u16 val;
	काष्ठा bnx2x *bp = params->bp;
	/* Read modअगरy ग_लिखो छोड़ो advertizing */
	bnx2x_cl45_पढ़ो(bp, phy, MDIO_AN_DEVAD, MDIO_AN_REG_ADV_PAUSE, &val);

	val &= ~MDIO_AN_REG_ADV_PAUSE_BOTH;

	/* Please refer to Table 28B-3 of 802.3ab-1999 spec. */
	bnx2x_calc_ieee_aneg_adv(phy, params, &vars->ieee_fc);
	अगर ((vars->ieee_fc &
	    MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_ASYMMETRIC) ==
	    MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_ASYMMETRIC) अणु
		val |= MDIO_AN_REG_ADV_PAUSE_ASYMMETRIC;
	पूर्ण
	अगर ((vars->ieee_fc &
	    MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH) ==
	    MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH) अणु
		val |= MDIO_AN_REG_ADV_PAUSE_PAUSE;
	पूर्ण
	DP(NETIF_MSG_LINK, "Ext phy AN advertize 0x%x\n", val);
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_AN_DEVAD, MDIO_AN_REG_ADV_PAUSE, val);
पूर्ण

अटल व्योम bnx2x_छोड़ो_resolve(काष्ठा bnx2x_phy *phy,
				काष्ठा link_params *params,
				काष्ठा link_vars *vars,
				u32 छोड़ो_result)
अणु
	काष्ठा bnx2x *bp = params->bp;
						/*  LD	    LP	 */
	चयन (छोड़ो_result) अणु			/* ASYM P ASYM P */
	हाल 0xb:				/*   1  0   1  1 */
		DP(NETIF_MSG_LINK, "Flow Control: TX only\n");
		vars->flow_ctrl = BNX2X_FLOW_CTRL_TX;
		अवरोध;

	हाल 0xe:				/*   1  1   1  0 */
		DP(NETIF_MSG_LINK, "Flow Control: RX only\n");
		vars->flow_ctrl = BNX2X_FLOW_CTRL_RX;
		अवरोध;

	हाल 0x5:				/*   0  1   0  1 */
	हाल 0x7:				/*   0  1   1  1 */
	हाल 0xd:				/*   1  1   0  1 */
	हाल 0xf:				/*   1  1   1  1 */
		/* If the user selected to advertise RX ONLY,
		 * although we advertised both, need to enable
		 * RX only.
		 */
		अगर (params->req_fc_स्वतः_adv == BNX2X_FLOW_CTRL_BOTH) अणु
			DP(NETIF_MSG_LINK, "Flow Control: RX & TX\n");
			vars->flow_ctrl = BNX2X_FLOW_CTRL_BOTH;
		पूर्ण अन्यथा अणु
			DP(NETIF_MSG_LINK, "Flow Control: RX only\n");
			vars->flow_ctrl = BNX2X_FLOW_CTRL_RX;
		पूर्ण
		अवरोध;

	शेष:
		DP(NETIF_MSG_LINK, "Flow Control: None\n");
		vars->flow_ctrl = BNX2X_FLOW_CTRL_NONE;
		अवरोध;
	पूर्ण
	अगर (छोड़ो_result & (1<<0))
		vars->link_status |= LINK_STATUS_LINK_PARTNER_SYMMETRIC_PAUSE;
	अगर (छोड़ो_result & (1<<1))
		vars->link_status |= LINK_STATUS_LINK_PARTNER_ASYMMETRIC_PAUSE;

पूर्ण

अटल व्योम bnx2x_ext_phy_update_adv_fc(काष्ठा bnx2x_phy *phy,
					काष्ठा link_params *params,
					काष्ठा link_vars *vars)
अणु
	u16 ld_छोड़ो;		/* local */
	u16 lp_छोड़ो;		/* link partner */
	u16 छोड़ो_result;
	काष्ठा bnx2x *bp = params->bp;
	अगर (phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM54618SE) अणु
		bnx2x_cl22_पढ़ो(bp, phy, 0x4, &ld_छोड़ो);
		bnx2x_cl22_पढ़ो(bp, phy, 0x5, &lp_छोड़ो);
	पूर्ण अन्यथा अगर (CHIP_IS_E3(bp) &&
		SINGLE_MEDIA_सूचीECT(params)) अणु
		u8 lane = bnx2x_get_warpcore_lane(phy, params);
		u16 gp_status, gp_mask;
		bnx2x_cl45_पढ़ो(bp, phy,
				MDIO_AN_DEVAD, MDIO_WC_REG_GP2_STATUS_GP_2_4,
				&gp_status);
		gp_mask = (MDIO_WC_REG_GP2_STATUS_GP_2_4_CL73_AN_CMPL |
			   MDIO_WC_REG_GP2_STATUS_GP_2_4_CL37_LP_AN_CAP) <<
			lane;
		अगर ((gp_status & gp_mask) == gp_mask) अणु
			bnx2x_cl45_पढ़ो(bp, phy, MDIO_AN_DEVAD,
					MDIO_AN_REG_ADV_PAUSE, &ld_छोड़ो);
			bnx2x_cl45_पढ़ो(bp, phy, MDIO_AN_DEVAD,
					MDIO_AN_REG_LP_AUTO_NEG, &lp_छोड़ो);
		पूर्ण अन्यथा अणु
			bnx2x_cl45_पढ़ो(bp, phy, MDIO_AN_DEVAD,
					MDIO_AN_REG_CL37_FC_LD, &ld_छोड़ो);
			bnx2x_cl45_पढ़ो(bp, phy, MDIO_AN_DEVAD,
					MDIO_AN_REG_CL37_FC_LP, &lp_छोड़ो);
			ld_छोड़ो = ((ld_छोड़ो &
				     MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH)
				    << 3);
			lp_छोड़ो = ((lp_छोड़ो &
				     MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH)
				    << 3);
		पूर्ण
	पूर्ण अन्यथा अणु
		bnx2x_cl45_पढ़ो(bp, phy,
				MDIO_AN_DEVAD,
				MDIO_AN_REG_ADV_PAUSE, &ld_छोड़ो);
		bnx2x_cl45_पढ़ो(bp, phy,
				MDIO_AN_DEVAD,
				MDIO_AN_REG_LP_AUTO_NEG, &lp_छोड़ो);
	पूर्ण
	छोड़ो_result = (ld_छोड़ो &
			MDIO_AN_REG_ADV_PAUSE_MASK) >> 8;
	छोड़ो_result |= (lp_छोड़ो &
			 MDIO_AN_REG_ADV_PAUSE_MASK) >> 10;
	DP(NETIF_MSG_LINK, "Ext PHY pause result 0x%x\n", छोड़ो_result);
	bnx2x_छोड़ो_resolve(phy, params, vars, छोड़ो_result);

पूर्ण

अटल u8 bnx2x_ext_phy_resolve_fc(काष्ठा bnx2x_phy *phy,
				   काष्ठा link_params *params,
				   काष्ठा link_vars *vars)
अणु
	u8 ret = 0;
	vars->flow_ctrl = BNX2X_FLOW_CTRL_NONE;
	अगर (phy->req_flow_ctrl != BNX2X_FLOW_CTRL_AUTO) अणु
		/* Update the advertised flow-controled of LD/LP in AN */
		अगर (phy->req_line_speed == SPEED_AUTO_NEG)
			bnx2x_ext_phy_update_adv_fc(phy, params, vars);
		/* But set the flow-control result as the requested one */
		vars->flow_ctrl = phy->req_flow_ctrl;
	पूर्ण अन्यथा अगर (phy->req_line_speed != SPEED_AUTO_NEG)
		vars->flow_ctrl = params->req_fc_स्वतः_adv;
	अन्यथा अगर (vars->link_status & LINK_STATUS_AUTO_NEGOTIATE_COMPLETE) अणु
		ret = 1;
		bnx2x_ext_phy_update_adv_fc(phy, params, vars);
	पूर्ण
	वापस ret;
पूर्ण
/******************************************************************/
/*			Warpcore section			  */
/******************************************************************/
/* The init_पूर्णांकernal_warpcore should mirror the xgxs,
 * i.e. reset the lane (अगर needed), set aer क्रम the
 * init configuration, and set/clear SGMII flag. Internal
 * phy init is करोne purely in phy_init stage.
 */
#घोषणा WC_TX_DRIVER(post2, idriver, ipre, अगरir) \
	((post2 << MDIO_WC_REG_TX0_TX_DRIVER_POST2_COEFF_OFFSET) | \
	 (idriver << MDIO_WC_REG_TX0_TX_DRIVER_IDRIVER_OFFSET) | \
	 (ipre << MDIO_WC_REG_TX0_TX_DRIVER_IPRE_DRIVER_OFFSET) | \
	 (अगरir << MDIO_WC_REG_TX0_TX_DRIVER_IFIR_OFFSET))

#घोषणा WC_TX_FIR(post, मुख्य, pre) \
	((post << MDIO_WC_REG_TX_FIR_TAP_POST_TAP_OFFSET) | \
	 (मुख्य << MDIO_WC_REG_TX_FIR_TAP_MAIN_TAP_OFFSET) | \
	 (pre << MDIO_WC_REG_TX_FIR_TAP_PRE_TAP_OFFSET))

अटल व्योम bnx2x_warpcore_enable_AN_KR2(काष्ठा bnx2x_phy *phy,
					 काष्ठा link_params *params,
					 काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 i;
	अटल काष्ठा bnx2x_reg_set reg_set[] = अणु
		/* Step 1 - Program the TX/RX alignment markers */
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_CL82_USERB1_TX_CTRL5, 0xa157पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_CL82_USERB1_TX_CTRL7, 0xcbe2पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_CL82_USERB1_TX_CTRL6, 0x7537पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_CL82_USERB1_TX_CTRL9, 0xa157पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_CL82_USERB1_RX_CTRL11, 0xcbe2पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_CL82_USERB1_RX_CTRL10, 0x7537पूर्ण,
		/* Step 2 - Configure the NP रेजिस्टरs */
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_CL73_USERB0_CTRL, 0x000aपूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_CL73_BAM_CTRL1, 0x6400पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_CL73_BAM_CTRL3, 0x0620पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_CL73_BAM_CODE_FIELD, 0x0157पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_ETA_CL73_OUI1, 0x6464पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_ETA_CL73_OUI2, 0x3150पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_ETA_CL73_OUI3, 0x3150पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_ETA_CL73_LD_BAM_CODE, 0x0157पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_ETA_CL73_LD_UD_CODE, 0x0620पूर्ण
	पूर्ण;
	DP(NETIF_MSG_LINK, "Enabling 20G-KR2\n");

	bnx2x_cl45_पढ़ो_or_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
				 MDIO_WC_REG_CL49_USERB0_CTRL, (3<<6));

	क्रम (i = 0; i < ARRAY_SIZE(reg_set); i++)
		bnx2x_cl45_ग_लिखो(bp, phy, reg_set[i].devad, reg_set[i].reg,
				 reg_set[i].val);

	/* Start KR2 work-around समयr which handles BCM8073 link-parner */
	params->link_attr_sync |= LINK_ATTR_SYNC_KR2_ENABLE;
	bnx2x_update_link_attr(params, params->link_attr_sync);
पूर्ण

अटल व्योम bnx2x_disable_kr2(काष्ठा link_params *params,
			      काष्ठा link_vars *vars,
			      काष्ठा bnx2x_phy *phy)
अणु
	काष्ठा bnx2x *bp = params->bp;
	पूर्णांक i;
	अटल काष्ठा bnx2x_reg_set reg_set[] = अणु
		/* Step 1 - Program the TX/RX alignment markers */
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_CL82_USERB1_TX_CTRL5, 0x7690पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_CL82_USERB1_TX_CTRL7, 0xe647पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_CL82_USERB1_TX_CTRL6, 0xc4f0पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_CL82_USERB1_TX_CTRL9, 0x7690पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_CL82_USERB1_RX_CTRL11, 0xe647पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_CL82_USERB1_RX_CTRL10, 0xc4f0पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_CL73_USERB0_CTRL, 0x000cपूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_CL73_BAM_CTRL1, 0x6000पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_CL73_BAM_CTRL3, 0x0000पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_CL73_BAM_CODE_FIELD, 0x0002पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_ETA_CL73_OUI1, 0x0000पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_ETA_CL73_OUI2, 0x0af7पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_ETA_CL73_OUI3, 0x0af7पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_ETA_CL73_LD_BAM_CODE, 0x0002पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_ETA_CL73_LD_UD_CODE, 0x0000पूर्ण
	पूर्ण;
	DP(NETIF_MSG_LINK, "Disabling 20G-KR2\n");

	क्रम (i = 0; i < ARRAY_SIZE(reg_set); i++)
		bnx2x_cl45_ग_लिखो(bp, phy, reg_set[i].devad, reg_set[i].reg,
				 reg_set[i].val);
	params->link_attr_sync &= ~LINK_ATTR_SYNC_KR2_ENABLE;
	bnx2x_update_link_attr(params, params->link_attr_sync);

	vars->check_kr2_recovery_cnt = CHECK_KR2_RECOVERY_CNT;
पूर्ण

अटल व्योम bnx2x_warpcore_set_lpi_passthrough(काष्ठा bnx2x_phy *phy,
					       काष्ठा link_params *params)
अणु
	काष्ठा bnx2x *bp = params->bp;

	DP(NETIF_MSG_LINK, "Configure WC for LPI pass through\n");
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_EEE_COMBO_CONTROL0, 0x7c);
	bnx2x_cl45_पढ़ो_or_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
				 MDIO_WC_REG_DIGITAL4_MISC5, 0xc000);
पूर्ण

अटल व्योम bnx2x_warpcore_restart_AN_KR(काष्ठा bnx2x_phy *phy,
					 काष्ठा link_params *params)
अणु
	/* Restart स्वतःneg on the leading lane only */
	काष्ठा bnx2x *bp = params->bp;
	u16 lane = bnx2x_get_warpcore_lane(phy, params);
	CL22_WR_OVER_CL45(bp, phy, MDIO_REG_BANK_AER_BLOCK,
			  MDIO_AER_BLOCK_AER_REG, lane);
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_AN_DEVAD,
			 MDIO_WC_REG_IEEE0BLK_MIICNTL, 0x1200);

	/* Restore AER */
	bnx2x_set_aer_mmd(params, phy);
पूर्ण

अटल व्योम bnx2x_warpcore_enable_AN_KR(काष्ठा bnx2x_phy *phy,
					काष्ठा link_params *params,
					काष्ठा link_vars *vars) अणु
	u16 lane, i, cl72_ctrl, an_adv = 0, val;
	u32 wc_lane_config;
	काष्ठा bnx2x *bp = params->bp;
	अटल काष्ठा bnx2x_reg_set reg_set[] = अणु
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X2, 0x7पूर्ण,
		अणुMDIO_PMA_DEVAD, MDIO_WC_REG_IEEE0BLK_AUTONEGNP, 0x0पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_RX66_CONTROL, 0x7415पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_SERDESDIGITAL_MISC2, 0x6190पूर्ण,
		/* Disable Autoneg: re-enable it after adv is करोne. */
		अणुMDIO_AN_DEVAD, MDIO_WC_REG_IEEE0BLK_MIICNTL, 0पूर्ण,
		अणुMDIO_PMA_DEVAD, MDIO_WC_REG_PMD_KR_CONTROL, 0x2पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_CL72_USERB0_CL72_TX_FIR_TAP, 0पूर्ण,
	पूर्ण;
	DP(NETIF_MSG_LINK, "Enable Auto Negotiation for KR\n");
	/* Set to शेष रेजिस्टरs that may be overriden by 10G क्रमce */
	क्रम (i = 0; i < ARRAY_SIZE(reg_set); i++)
		bnx2x_cl45_ग_लिखो(bp, phy, reg_set[i].devad, reg_set[i].reg,
				 reg_set[i].val);

	bnx2x_cl45_पढ़ो(bp, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_CL72_USERB0_CL72_MISC1_CONTROL, &cl72_ctrl);
	cl72_ctrl &= 0x08ff;
	cl72_ctrl |= 0x3800;
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_CL72_USERB0_CL72_MISC1_CONTROL, cl72_ctrl);

	/* Check adding advertisement क्रम 1G KX */
	अगर (((vars->line_speed == SPEED_AUTO_NEG) &&
	     (phy->speed_cap_mask & PORT_HW_CFG_SPEED_CAPABILITY_D0_1G)) ||
	    (vars->line_speed == SPEED_1000)) अणु
		u16 addr = MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X2;
		an_adv |= (1<<5);

		/* Enable CL37 1G Parallel Detect */
		bnx2x_cl45_पढ़ो_or_ग_लिखो(bp, phy, MDIO_WC_DEVAD, addr, 0x1);
		DP(NETIF_MSG_LINK, "Advertize 1G\n");
	पूर्ण
	अगर (((vars->line_speed == SPEED_AUTO_NEG) &&
	     (phy->speed_cap_mask & PORT_HW_CFG_SPEED_CAPABILITY_D0_10G)) ||
	    (vars->line_speed ==  SPEED_10000)) अणु
		/* Check adding advertisement क्रम 10G KR */
		an_adv |= (1<<7);
		/* Enable 10G Parallel Detect */
		CL22_WR_OVER_CL45(bp, phy, MDIO_REG_BANK_AER_BLOCK,
				  MDIO_AER_BLOCK_AER_REG, 0);

		bnx2x_cl45_ग_लिखो(bp, phy, MDIO_AN_DEVAD,
				 MDIO_WC_REG_PAR_DET_10G_CTRL, 1);
		bnx2x_set_aer_mmd(params, phy);
		DP(NETIF_MSG_LINK, "Advertize 10G\n");
	पूर्ण

	/* Set Transmit PMD settings */
	lane = bnx2x_get_warpcore_lane(phy, params);
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_TX0_TX_DRIVER + 0x10*lane,
			 WC_TX_DRIVER(0x02, 0x06, 0x09, 0));
	/* Configure the next lane अगर dual mode */
	अगर (phy->flags & FLAGS_WC_DUAL_MODE)
		bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
				 MDIO_WC_REG_TX0_TX_DRIVER + 0x10*(lane+1),
				 WC_TX_DRIVER(0x02, 0x06, 0x09, 0));
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_CL72_USERB0_CL72_OS_DEF_CTRL,
			 0x03f0);
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_CL72_USERB0_CL72_2P5_DEF_CTRL,
			 0x03f0);

	/* Advertised speeds */
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_AN_DEVAD,
			 MDIO_WC_REG_AN_IEEE1BLK_AN_ADVERTISEMENT1, an_adv);

	/* Advertised and set FEC (Forward Error Correction) */
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_AN_DEVAD,
			 MDIO_WC_REG_AN_IEEE1BLK_AN_ADVERTISEMENT2,
			 (MDIO_WC_REG_AN_IEEE1BLK_AN_ADV2_FEC_ABILITY |
			  MDIO_WC_REG_AN_IEEE1BLK_AN_ADV2_FEC_REQ));

	/* Enable CL37 BAM */
	अगर (REG_RD(bp, params->shmem_base +
		   दुरत्व(काष्ठा shmem_region, dev_info.
			    port_hw_config[params->port].शेष_cfg)) &
	    PORT_HW_CFG_ENABLE_BAM_ON_KR_ENABLED) अणु
		bnx2x_cl45_पढ़ो_or_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
					 MDIO_WC_REG_DIGITAL6_MP5_NEXTPAGECTRL,
					 1);
		DP(NETIF_MSG_LINK, "Enable CL37 BAM on KR\n");
	पूर्ण

	/* Advertise छोड़ो */
	bnx2x_ext_phy_set_छोड़ो(params, phy, vars);
	vars->rx_tx_asic_rst = MAX_KR_LINK_RETRY;
	bnx2x_cl45_पढ़ो_or_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
				 MDIO_WC_REG_DIGITAL5_MISC7, 0x100);

	/* Over 1G - AN local device user page 1 */
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_DIGITAL3_UP1, 0x1f);

	अगर (((phy->req_line_speed == SPEED_AUTO_NEG) &&
	     (phy->speed_cap_mask & PORT_HW_CFG_SPEED_CAPABILITY_D0_20G)) ||
	    (phy->req_line_speed == SPEED_20000)) अणु

		CL22_WR_OVER_CL45(bp, phy, MDIO_REG_BANK_AER_BLOCK,
				  MDIO_AER_BLOCK_AER_REG, lane);

		bnx2x_cl45_पढ़ो_or_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
					 MDIO_WC_REG_RX1_PCI_CTRL + (0x10*lane),
					 (1<<11));

		bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
				 MDIO_WC_REG_XGXS_X2_CONTROL3, 0x7);
		bnx2x_set_aer_mmd(params, phy);

		bnx2x_warpcore_enable_AN_KR2(phy, params, vars);
	पूर्ण अन्यथा अणु
		/* Enable Auto-Detect to support 1G over CL37 as well */
		bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
				 MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X1, 0x10);
		wc_lane_config = REG_RD(bp, params->shmem_base +
					दुरत्व(काष्ठा shmem_region, dev_info.
					shared_hw_config.wc_lane_config));
		bnx2x_cl45_पढ़ो(bp, phy, MDIO_WC_DEVAD,
				MDIO_WC_REG_RX0_PCI_CTRL + (lane << 4), &val);
		/* Force cl48 sync_status LOW to aव्योम getting stuck in CL73
		 * parallel-detect loop when CL73 and CL37 are enabled.
		 */
		val |= 1 << 11;

		/* Restore Polarity settings in हाल it was run over by
		 * previous link owner
		 */
		अगर (wc_lane_config &
		    (SHARED_HW_CFG_RX_LANE0_POL_FLIP_ENABLED << lane))
			val |= 3 << 2;
		अन्यथा
			val &= ~(3 << 2);
		bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
				 MDIO_WC_REG_RX0_PCI_CTRL + (lane << 4),
				 val);

		bnx2x_disable_kr2(params, vars, phy);
	पूर्ण

	/* Enable Autoneg: only on the मुख्य lane */
	bnx2x_warpcore_restart_AN_KR(phy, params);
पूर्ण

अटल व्योम bnx2x_warpcore_set_10G_KR(काष्ठा bnx2x_phy *phy,
				      काष्ठा link_params *params,
				      काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 val16, i, lane;
	अटल काष्ठा bnx2x_reg_set reg_set[] = अणु
		/* Disable Autoneg */
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X2, 0x7पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_CL72_USERB0_CL72_MISC1_CONTROL,
			0x3f00पूर्ण,
		अणुMDIO_AN_DEVAD, MDIO_WC_REG_AN_IEEE1BLK_AN_ADVERTISEMENT1, 0पूर्ण,
		अणुMDIO_AN_DEVAD, MDIO_WC_REG_IEEE0BLK_MIICNTL, 0x0पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_DIGITAL3_UP1, 0x1पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_DIGITAL5_MISC7, 0xaपूर्ण,
		/* Leave cl72 training enable, needed क्रम KR */
		अणुMDIO_PMA_DEVAD, MDIO_WC_REG_PMD_KR_CONTROL, 0x2पूर्ण
	पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(reg_set); i++)
		bnx2x_cl45_ग_लिखो(bp, phy, reg_set[i].devad, reg_set[i].reg,
				 reg_set[i].val);

	lane = bnx2x_get_warpcore_lane(phy, params);
	/* Global रेजिस्टरs */
	CL22_WR_OVER_CL45(bp, phy, MDIO_REG_BANK_AER_BLOCK,
			  MDIO_AER_BLOCK_AER_REG, 0);
	/* Disable CL36 PCS Tx */
	bnx2x_cl45_पढ़ो(bp, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_XGXSBLK1_LANECTRL0, &val16);
	val16 &= ~(0x0011 << lane);
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_XGXSBLK1_LANECTRL0, val16);

	bnx2x_cl45_पढ़ो(bp, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_XGXSBLK1_LANECTRL1, &val16);
	val16 |= (0x0303 << (lane << 1));
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_XGXSBLK1_LANECTRL1, val16);
	/* Restore AER */
	bnx2x_set_aer_mmd(params, phy);
	/* Set speed via PMA/PMD रेजिस्टर */
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_PMA_DEVAD,
			 MDIO_WC_REG_IEEE0BLK_MIICNTL, 0x2040);

	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_PMA_DEVAD,
			 MDIO_WC_REG_IEEE0BLK_AUTONEGNP, 0xB);

	/* Enable encoded क्रमced speed */
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_SERDESDIGITAL_MISC2, 0x30);

	/* Turn TX scramble payload only the 64/66 scrambler */
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_TX66_CONTROL, 0x9);

	/* Turn RX scramble payload only the 64/66 scrambler */
	bnx2x_cl45_पढ़ो_or_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
				 MDIO_WC_REG_RX66_CONTROL, 0xF9);

	/* Set and clear loopback to cause a reset to 64/66 decoder */
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_IEEE0BLK_MIICNTL, 0x4000);
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_IEEE0BLK_MIICNTL, 0x0);

पूर्ण

अटल व्योम bnx2x_warpcore_set_10G_XFI(काष्ठा bnx2x_phy *phy,
				       काष्ठा link_params *params,
				       u8 is_xfi)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 misc1_val, tap_val, tx_driver_val, lane, val;
	u32 cfg_tap_val, tx_drv_brdct, tx_equal;
	u32 अगरir_val, ipost2_val, ipre_driver_val;

	/* Hold rxSeqStart */
	bnx2x_cl45_पढ़ो_or_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
				 MDIO_WC_REG_DSC2B0_DSC_MISC_CTRL0, 0x8000);

	/* Hold tx_fअगरo_reset */
	bnx2x_cl45_पढ़ो_or_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
				 MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X3, 0x1);

	/* Disable CL73 AN */
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_AN_DEVAD, MDIO_AN_REG_CTRL, 0);

	/* Disable 100FX Enable and Auto-Detect */
	bnx2x_cl45_पढ़ो_and_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
				  MDIO_WC_REG_FX100_CTRL1, 0xFFFA);

	/* Disable 100FX Idle detect */
	bnx2x_cl45_पढ़ो_or_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
				 MDIO_WC_REG_FX100_CTRL3, 0x0080);

	/* Set Block address to Remote PHY & Clear क्रमced_speed[5] */
	bnx2x_cl45_पढ़ो_and_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
				  MDIO_WC_REG_DIGITAL4_MISC3, 0xFF7F);

	/* Turn off स्वतः-detect & fiber mode */
	bnx2x_cl45_पढ़ो_and_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
				  MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X1,
				  0xFFEE);

	/* Set filter_क्रमce_link, disable_false_link and parallel_detect */
	bnx2x_cl45_पढ़ो(bp, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X2, &val);
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X2,
			 ((val | 0x0006) & 0xFFFE));

	/* Set XFI / SFI */
	bnx2x_cl45_पढ़ो(bp, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_SERDESDIGITAL_MISC1, &misc1_val);

	misc1_val &= ~(0x1f);

	अगर (is_xfi) अणु
		misc1_val |= 0x5;
		tap_val = WC_TX_FIR(0x08, 0x37, 0x00);
		tx_driver_val = WC_TX_DRIVER(0x00, 0x02, 0x03, 0);
	पूर्ण अन्यथा अणु
		cfg_tap_val = REG_RD(bp, params->shmem_base +
				     दुरत्व(काष्ठा shmem_region, dev_info.
					      port_hw_config[params->port].
					      sfi_tap_values));

		tx_equal = cfg_tap_val & PORT_HW_CFG_TX_EQUALIZATION_MASK;

		misc1_val |= 0x9;

		/* TAP values are controlled by nvram, अगर value there isn't 0 */
		अगर (tx_equal)
			tap_val = (u16)tx_equal;
		अन्यथा
			tap_val = WC_TX_FIR(0x0f, 0x2b, 0x02);

		अगरir_val = DEFAULT_TX_DRV_IFIR;
		ipost2_val = DEFAULT_TX_DRV_POST2;
		ipre_driver_val = DEFAULT_TX_DRV_IPRE_DRIVER;
		tx_drv_brdct = DEFAULT_TX_DRV_BRDCT;

		/* If any of the IFIR/IPRE_DRIVER/POST@ is set, apply all
		 * configuration.
		 */
		अगर (cfg_tap_val & (PORT_HW_CFG_TX_DRV_IFIR_MASK |
				   PORT_HW_CFG_TX_DRV_IPREDRIVER_MASK |
				   PORT_HW_CFG_TX_DRV_POST2_MASK)) अणु
			अगरir_val = (cfg_tap_val &
				    PORT_HW_CFG_TX_DRV_IFIR_MASK) >>
				PORT_HW_CFG_TX_DRV_IFIR_SHIFT;
			ipre_driver_val = (cfg_tap_val &
					   PORT_HW_CFG_TX_DRV_IPREDRIVER_MASK)
			>> PORT_HW_CFG_TX_DRV_IPREDRIVER_SHIFT;
			ipost2_val = (cfg_tap_val &
				      PORT_HW_CFG_TX_DRV_POST2_MASK) >>
				PORT_HW_CFG_TX_DRV_POST2_SHIFT;
		पूर्ण

		अगर (cfg_tap_val & PORT_HW_CFG_TX_DRV_BROADCAST_MASK) अणु
			tx_drv_brdct = (cfg_tap_val &
					PORT_HW_CFG_TX_DRV_BROADCAST_MASK) >>
				PORT_HW_CFG_TX_DRV_BROADCAST_SHIFT;
		पूर्ण

		tx_driver_val = WC_TX_DRIVER(ipost2_val, tx_drv_brdct,
					     ipre_driver_val, अगरir_val);
	पूर्ण
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_SERDESDIGITAL_MISC1, misc1_val);

	/* Set Transmit PMD settings */
	lane = bnx2x_get_warpcore_lane(phy, params);
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_TX_FIR_TAP,
			 tap_val | MDIO_WC_REG_TX_FIR_TAP_ENABLE);
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_TX0_TX_DRIVER + 0x10*lane,
			 tx_driver_val);

	/* Enable fiber mode, enable and invert sig_det */
	bnx2x_cl45_पढ़ो_or_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
				 MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X1, 0xd);

	/* Set Block address to Remote PHY & Set क्रमced_speed[5], 40bit mode */
	bnx2x_cl45_पढ़ो_or_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
				 MDIO_WC_REG_DIGITAL4_MISC3, 0x8080);

	bnx2x_warpcore_set_lpi_passthrough(phy, params);

	/* 10G XFI Full Duplex */
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_IEEE0BLK_MIICNTL, 0x100);

	/* Release tx_fअगरo_reset */
	bnx2x_cl45_पढ़ो_and_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
				  MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X3,
				  0xFFFE);
	/* Release rxSeqStart */
	bnx2x_cl45_पढ़ो_and_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
				  MDIO_WC_REG_DSC2B0_DSC_MISC_CTRL0, 0x7FFF);
पूर्ण

अटल व्योम bnx2x_warpcore_set_20G_क्रमce_KR2(काष्ठा bnx2x_phy *phy,
					     काष्ठा link_params *params)
अणु
	u16 val;
	काष्ठा bnx2x *bp = params->bp;
	/* Set global रेजिस्टरs, so set AER lane to 0 */
	CL22_WR_OVER_CL45(bp, phy, MDIO_REG_BANK_AER_BLOCK,
			  MDIO_AER_BLOCK_AER_REG, 0);

	/* Disable sequencer */
	bnx2x_cl45_पढ़ो_and_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
				  MDIO_WC_REG_XGXSBLK0_XGXSCONTROL, ~(1<<13));

	bnx2x_set_aer_mmd(params, phy);

	bnx2x_cl45_पढ़ो_and_ग_लिखो(bp, phy, MDIO_PMA_DEVAD,
				  MDIO_WC_REG_PMD_KR_CONTROL, ~(1<<1));
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_AN_DEVAD,
			 MDIO_AN_REG_CTRL, 0);
	/* Turn off CL73 */
	bnx2x_cl45_पढ़ो(bp, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_CL73_USERB0_CTRL, &val);
	val &= ~(1<<5);
	val |= (1<<6);
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_CL73_USERB0_CTRL, val);

	/* Set 20G KR2 क्रमce speed */
	bnx2x_cl45_पढ़ो_or_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
				 MDIO_WC_REG_SERDESDIGITAL_MISC1, 0x1f);

	bnx2x_cl45_पढ़ो_or_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
				 MDIO_WC_REG_DIGITAL4_MISC3, (1<<7));

	bnx2x_cl45_पढ़ो(bp, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_CL72_USERB0_CL72_MISC1_CONTROL, &val);
	val &= ~(3<<14);
	val |= (1<<15);
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_CL72_USERB0_CL72_MISC1_CONTROL, val);
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_CL72_USERB0_CL72_TX_FIR_TAP, 0x835A);

	/* Enable sequencer (over lane 0) */
	CL22_WR_OVER_CL45(bp, phy, MDIO_REG_BANK_AER_BLOCK,
			  MDIO_AER_BLOCK_AER_REG, 0);

	bnx2x_cl45_पढ़ो_or_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
				 MDIO_WC_REG_XGXSBLK0_XGXSCONTROL, (1<<13));

	bnx2x_set_aer_mmd(params, phy);
पूर्ण

अटल व्योम bnx2x_warpcore_set_20G_DXGXS(काष्ठा bnx2x *bp,
					 काष्ठा bnx2x_phy *phy,
					 u16 lane)
अणु
	/* Rx0 anaRxControl1G */
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_RX0_ANARXCONTROL1G, 0x90);

	/* Rx2 anaRxControl1G */
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_RX2_ANARXCONTROL1G, 0x90);

	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_RX66_SCW0, 0xE070);

	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_RX66_SCW1, 0xC0D0);

	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_RX66_SCW2, 0xA0B0);

	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_RX66_SCW3, 0x8090);

	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_RX66_SCW0_MASK, 0xF0F0);

	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_RX66_SCW1_MASK, 0xF0F0);

	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_RX66_SCW2_MASK, 0xF0F0);

	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_RX66_SCW3_MASK, 0xF0F0);

	/* Serdes Digital Misc1 */
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_SERDESDIGITAL_MISC1, 0x6008);

	/* Serdes Digital4 Misc3 */
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_DIGITAL4_MISC3, 0x8088);

	/* Set Transmit PMD settings */
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_TX_FIR_TAP,
			 (WC_TX_FIR(0x12, 0x2d, 0x00) |
			  MDIO_WC_REG_TX_FIR_TAP_ENABLE));
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_TX0_TX_DRIVER + 0x10*lane,
			 WC_TX_DRIVER(0x02, 0x02, 0x02, 0));
पूर्ण

अटल व्योम bnx2x_warpcore_set_sgmii_speed(काष्ठा bnx2x_phy *phy,
					   काष्ठा link_params *params,
					   u8 fiber_mode,
					   u8 always_स्वतःneg)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 val16, digctrl_kx1, digctrl_kx2;

	/* Clear XFI घड़ी comp in non-10G single lane mode. */
	bnx2x_cl45_पढ़ो_and_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
				  MDIO_WC_REG_RX66_CONTROL, ~(3<<13));

	bnx2x_warpcore_set_lpi_passthrough(phy, params);

	अगर (always_स्वतःneg || phy->req_line_speed == SPEED_AUTO_NEG) अणु
		/* SGMII Autoneg */
		bnx2x_cl45_पढ़ो_or_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
					 MDIO_WC_REG_COMBO_IEEE0_MIICTRL,
					 0x1000);
		DP(NETIF_MSG_LINK, "set SGMII AUTONEG\n");
	पूर्ण अन्यथा अणु
		bnx2x_cl45_पढ़ो(bp, phy, MDIO_WC_DEVAD,
				MDIO_WC_REG_COMBO_IEEE0_MIICTRL, &val16);
		val16 &= 0xcebf;
		चयन (phy->req_line_speed) अणु
		हाल SPEED_10:
			अवरोध;
		हाल SPEED_100:
			val16 |= 0x2000;
			अवरोध;
		हाल SPEED_1000:
			val16 |= 0x0040;
			अवरोध;
		शेष:
			DP(NETIF_MSG_LINK,
			   "Speed not supported: 0x%x\n", phy->req_line_speed);
			वापस;
		पूर्ण

		अगर (phy->req_duplex == DUPLEX_FULL)
			val16 |= 0x0100;

		bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
				MDIO_WC_REG_COMBO_IEEE0_MIICTRL, val16);

		DP(NETIF_MSG_LINK, "set SGMII force speed %d\n",
			       phy->req_line_speed);
		bnx2x_cl45_पढ़ो(bp, phy, MDIO_WC_DEVAD,
				MDIO_WC_REG_COMBO_IEEE0_MIICTRL, &val16);
		DP(NETIF_MSG_LINK, "  (readback) %x\n", val16);
	पूर्ण

	/* SGMII Slave mode and disable संकेत detect */
	bnx2x_cl45_पढ़ो(bp, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X1, &digctrl_kx1);
	अगर (fiber_mode)
		digctrl_kx1 = 1;
	अन्यथा
		digctrl_kx1 &= 0xff4a;

	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X1,
			digctrl_kx1);

	/* Turn off parallel detect */
	bnx2x_cl45_पढ़ो(bp, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X2, &digctrl_kx2);
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X2,
			(digctrl_kx2 & ~(1<<2)));

	/* Re-enable parallel detect */
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X2,
			(digctrl_kx2 | (1<<2)));

	/* Enable स्वतःdet */
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X1,
			(digctrl_kx1 | 0x10));
पूर्ण

अटल व्योम bnx2x_warpcore_reset_lane(काष्ठा bnx2x *bp,
				      काष्ठा bnx2x_phy *phy,
				      u8 reset)
अणु
	u16 val;
	/* Take lane out of reset after configuration is finished */
	bnx2x_cl45_पढ़ो(bp, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_DIGITAL5_MISC6, &val);
	अगर (reset)
		val |= 0xC000;
	अन्यथा
		val &= 0x3FFF;
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_DIGITAL5_MISC6, val);
	bnx2x_cl45_पढ़ो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_DIGITAL5_MISC6, &val);
पूर्ण
/* Clear SFI/XFI link settings रेजिस्टरs */
अटल व्योम bnx2x_warpcore_clear_regs(काष्ठा bnx2x_phy *phy,
				      काष्ठा link_params *params,
				      u16 lane)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 i;
	अटल काष्ठा bnx2x_reg_set wc_regs[] = अणु
		अणुMDIO_AN_DEVAD, MDIO_AN_REG_CTRL, 0पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_FX100_CTRL1, 0x014aपूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_FX100_CTRL3, 0x0800पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_DIGITAL4_MISC3, 0x8008पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X1,
			0x0195पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X2,
			0x0007पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_SERDESDIGITAL_CONTROL1000X3,
			0x0002पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_SERDESDIGITAL_MISC1, 0x6000पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_TX_FIR_TAP, 0x0000पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_IEEE0BLK_MIICNTL, 0x2040पूर्ण,
		अणुMDIO_WC_DEVAD, MDIO_WC_REG_COMBO_IEEE0_MIICTRL, 0x0140पूर्ण
	पूर्ण;
	/* Set XFI घड़ी comp as शेष. */
	bnx2x_cl45_पढ़ो_or_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
				 MDIO_WC_REG_RX66_CONTROL, (3<<13));

	क्रम (i = 0; i < ARRAY_SIZE(wc_regs); i++)
		bnx2x_cl45_ग_लिखो(bp, phy, wc_regs[i].devad, wc_regs[i].reg,
				 wc_regs[i].val);

	lane = bnx2x_get_warpcore_lane(phy, params);
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_TX0_TX_DRIVER + 0x10*lane, 0x0990);

पूर्ण

अटल पूर्णांक bnx2x_get_mod_असल_पूर्णांक_cfg(काष्ठा bnx2x *bp,
						u32 chip_id,
						u32 shmem_base, u8 port,
						u8 *gpio_num, u8 *gpio_port)
अणु
	u32 cfg_pin;
	*gpio_num = 0;
	*gpio_port = 0;
	अगर (CHIP_IS_E3(bp)) अणु
		cfg_pin = (REG_RD(bp, shmem_base +
				दुरत्व(काष्ठा shmem_region,
				dev_info.port_hw_config[port].e3_sfp_ctrl)) &
				PORT_HW_CFG_E3_MOD_ABS_MASK) >>
				PORT_HW_CFG_E3_MOD_ABS_SHIFT;

		/* Should not happen. This function called upon पूर्णांकerrupt
		 * triggered by GPIO ( since EPIO can only generate पूर्णांकerrupts
		 * to MCP).
		 * So अगर this function was called and none of the GPIOs was set,
		 * it means the shit hit the fan.
		 */
		अगर ((cfg_pin < PIN_CFG_GPIO0_P0) ||
		    (cfg_pin > PIN_CFG_GPIO3_P1)) अणु
			DP(NETIF_MSG_LINK,
			   "No cfg pin %x for module detect indication\n",
			   cfg_pin);
			वापस -EINVAL;
		पूर्ण

		*gpio_num = (cfg_pin - PIN_CFG_GPIO0_P0) & 0x3;
		*gpio_port = (cfg_pin - PIN_CFG_GPIO0_P0) >> 2;
	पूर्ण अन्यथा अणु
		*gpio_num = MISC_REGISTERS_GPIO_3;
		*gpio_port = port;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_is_sfp_module_plugged(काष्ठा bnx2x_phy *phy,
				       काष्ठा link_params *params)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u8 gpio_num, gpio_port;
	u32 gpio_val;
	अगर (bnx2x_get_mod_असल_पूर्णांक_cfg(bp, params->chip_id,
				      params->shmem_base, params->port,
				      &gpio_num, &gpio_port) != 0)
		वापस 0;
	gpio_val = bnx2x_get_gpio(bp, gpio_num, gpio_port);

	/* Call the handling function in हाल module is detected */
	अगर (gpio_val == 0)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण
अटल पूर्णांक bnx2x_warpcore_get_sigdet(काष्ठा bnx2x_phy *phy,
				     काष्ठा link_params *params)
अणु
	u16 gp2_status_reg0, lane;
	काष्ठा bnx2x *bp = params->bp;

	lane = bnx2x_get_warpcore_lane(phy, params);

	bnx2x_cl45_पढ़ो(bp, phy, MDIO_WC_DEVAD, MDIO_WC_REG_GP2_STATUS_GP_2_0,
				 &gp2_status_reg0);

	वापस (gp2_status_reg0 >> (8+lane)) & 0x1;
पूर्ण

अटल व्योम bnx2x_warpcore_config_runसमय(काष्ठा bnx2x_phy *phy,
					  काष्ठा link_params *params,
					  काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u32 serdes_net_अगर;
	u16 gp_status1 = 0, lnkup = 0, lnkup_kr = 0;

	vars->turn_to_run_wc_rt = vars->turn_to_run_wc_rt ? 0 : 1;

	अगर (!vars->turn_to_run_wc_rt)
		वापस;

	अगर (vars->rx_tx_asic_rst) अणु
		u16 lane = bnx2x_get_warpcore_lane(phy, params);
		serdes_net_अगर = (REG_RD(bp, params->shmem_base +
				दुरत्व(काष्ठा shmem_region, dev_info.
				port_hw_config[params->port].शेष_cfg)) &
				PORT_HW_CFG_NET_SERDES_IF_MASK);

		चयन (serdes_net_अगर) अणु
		हाल PORT_HW_CFG_NET_SERDES_IF_KR:
			/* Do we get link yet? */
			bnx2x_cl45_पढ़ो(bp, phy, MDIO_WC_DEVAD, 0x81d1,
					&gp_status1);
			lnkup = (gp_status1 >> (8+lane)) & 0x1;/* 1G */
				/*10G KR*/
			lnkup_kr = (gp_status1 >> (12+lane)) & 0x1;

			अगर (lnkup_kr || lnkup) अणु
				vars->rx_tx_asic_rst = 0;
			पूर्ण अन्यथा अणु
				/* Reset the lane to see अगर link comes up.*/
				bnx2x_warpcore_reset_lane(bp, phy, 1);
				bnx2x_warpcore_reset_lane(bp, phy, 0);

				/* Restart Autoneg */
				bnx2x_cl45_ग_लिखो(bp, phy, MDIO_AN_DEVAD,
					MDIO_WC_REG_IEEE0BLK_MIICNTL, 0x1200);

				vars->rx_tx_asic_rst--;
				DP(NETIF_MSG_LINK, "0x%x retry left\n",
				vars->rx_tx_asic_rst);
			पूर्ण
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण

	पूर्ण /*params->rx_tx_asic_rst*/

पूर्ण
अटल व्योम bnx2x_warpcore_config_sfi(काष्ठा bnx2x_phy *phy,
				      काष्ठा link_params *params)
अणु
	u16 lane = bnx2x_get_warpcore_lane(phy, params);
	काष्ठा bnx2x *bp = params->bp;
	bnx2x_warpcore_clear_regs(phy, params, lane);
	अगर ((params->req_line_speed[LINK_CONFIG_IDX(INT_PHY)] ==
	     SPEED_10000) &&
	    (phy->media_type != ETH_PHY_SFP_1G_FIBER)) अणु
		DP(NETIF_MSG_LINK, "Setting 10G SFI\n");
		bnx2x_warpcore_set_10G_XFI(phy, params, 0);
	पूर्ण अन्यथा अणु
		DP(NETIF_MSG_LINK, "Setting 1G Fiber\n");
		bnx2x_warpcore_set_sgmii_speed(phy, params, 1, 0);
	पूर्ण
पूर्ण

अटल व्योम bnx2x_sfp_e3_set_transmitter(काष्ठा link_params *params,
					 काष्ठा bnx2x_phy *phy,
					 u8 tx_en)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u32 cfg_pin;
	u8 port = params->port;

	cfg_pin = REG_RD(bp, params->shmem_base +
			 दुरत्व(काष्ठा shmem_region,
				  dev_info.port_hw_config[port].e3_sfp_ctrl)) &
		PORT_HW_CFG_E3_TX_LASER_MASK;
	/* Set the !tx_en since this pin is DISABLE_TX_LASER */
	DP(NETIF_MSG_LINK, "Setting WC TX to %d\n", tx_en);

	/* For 20G, the expected pin to be used is 3 pins after the current */
	bnx2x_set_cfg_pin(bp, cfg_pin, tx_en ^ 1);
	अगर (phy->speed_cap_mask & PORT_HW_CFG_SPEED_CAPABILITY_D0_20G)
		bnx2x_set_cfg_pin(bp, cfg_pin + 3, tx_en ^ 1);
पूर्ण

अटल व्योम bnx2x_warpcore_config_init(काष्ठा bnx2x_phy *phy,
				       काष्ठा link_params *params,
				       काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u32 serdes_net_अगर;
	u8 fiber_mode;
	u16 lane = bnx2x_get_warpcore_lane(phy, params);
	serdes_net_अगर = (REG_RD(bp, params->shmem_base +
			 दुरत्व(काष्ठा shmem_region, dev_info.
				  port_hw_config[params->port].शेष_cfg)) &
			 PORT_HW_CFG_NET_SERDES_IF_MASK);
	DP(NETIF_MSG_LINK, "Begin Warpcore init, link_speed %d, "
			   "serdes_net_if = 0x%x\n",
		       vars->line_speed, serdes_net_अगर);
	bnx2x_set_aer_mmd(params, phy);
	bnx2x_warpcore_reset_lane(bp, phy, 1);
	vars->phy_flags |= PHY_XGXS_FLAG;
	अगर ((serdes_net_अगर == PORT_HW_CFG_NET_SERDES_IF_SGMII) ||
	    (phy->req_line_speed &&
	     ((phy->req_line_speed == SPEED_100) ||
	      (phy->req_line_speed == SPEED_10)))) अणु
		vars->phy_flags |= PHY_SGMII_FLAG;
		DP(NETIF_MSG_LINK, "Setting SGMII mode\n");
		bnx2x_warpcore_clear_regs(phy, params, lane);
		bnx2x_warpcore_set_sgmii_speed(phy, params, 0, 1);
	पूर्ण अन्यथा अणु
		चयन (serdes_net_अगर) अणु
		हाल PORT_HW_CFG_NET_SERDES_IF_KR:
			/* Enable KR Auto Neg */
			अगर (params->loopback_mode != LOOPBACK_EXT)
				bnx2x_warpcore_enable_AN_KR(phy, params, vars);
			अन्यथा अणु
				DP(NETIF_MSG_LINK, "Setting KR 10G-Force\n");
				bnx2x_warpcore_set_10G_KR(phy, params, vars);
			पूर्ण
			अवरोध;

		हाल PORT_HW_CFG_NET_SERDES_IF_XFI:
			bnx2x_warpcore_clear_regs(phy, params, lane);
			अगर (vars->line_speed == SPEED_10000) अणु
				DP(NETIF_MSG_LINK, "Setting 10G XFI\n");
				bnx2x_warpcore_set_10G_XFI(phy, params, 1);
			पूर्ण अन्यथा अणु
				अगर (SINGLE_MEDIA_सूचीECT(params)) अणु
					DP(NETIF_MSG_LINK, "1G Fiber\n");
					fiber_mode = 1;
				पूर्ण अन्यथा अणु
					DP(NETIF_MSG_LINK, "10/100/1G SGMII\n");
					fiber_mode = 0;
				पूर्ण
				bnx2x_warpcore_set_sgmii_speed(phy,
								params,
								fiber_mode,
								0);
			पूर्ण

			अवरोध;

		हाल PORT_HW_CFG_NET_SERDES_IF_SFI:
			/* Issue Module detection अगर module is plugged, or
			 * enabled transmitter to aव्योम current leakage in हाल
			 * no module is connected
			 */
			अगर ((params->loopback_mode == LOOPBACK_NONE) ||
			    (params->loopback_mode == LOOPBACK_EXT)) अणु
				अगर (bnx2x_is_sfp_module_plugged(phy, params))
					bnx2x_sfp_module_detection(phy, params);
				अन्यथा
					bnx2x_sfp_e3_set_transmitter(params,
								     phy, 1);
			पूर्ण

			bnx2x_warpcore_config_sfi(phy, params);
			अवरोध;

		हाल PORT_HW_CFG_NET_SERDES_IF_DXGXS:
			अगर (vars->line_speed != SPEED_20000) अणु
				DP(NETIF_MSG_LINK, "Speed not supported yet\n");
				वापस;
			पूर्ण
			DP(NETIF_MSG_LINK, "Setting 20G DXGXS\n");
			bnx2x_warpcore_set_20G_DXGXS(bp, phy, lane);
			/* Issue Module detection */

			bnx2x_sfp_module_detection(phy, params);
			अवरोध;
		हाल PORT_HW_CFG_NET_SERDES_IF_KR2:
			अगर (!params->loopback_mode) अणु
				bnx2x_warpcore_enable_AN_KR(phy, params, vars);
			पूर्ण अन्यथा अणु
				DP(NETIF_MSG_LINK, "Setting KR 20G-Force\n");
				bnx2x_warpcore_set_20G_क्रमce_KR2(phy, params);
			पूर्ण
			अवरोध;
		शेष:
			DP(NETIF_MSG_LINK,
			   "Unsupported Serdes Net Interface 0x%x\n",
			   serdes_net_अगर);
			वापस;
		पूर्ण
	पूर्ण

	/* Take lane out of reset after configuration is finished */
	bnx2x_warpcore_reset_lane(bp, phy, 0);
	DP(NETIF_MSG_LINK, "Exit config init\n");
पूर्ण

अटल व्योम bnx2x_warpcore_link_reset(काष्ठा bnx2x_phy *phy,
				      काष्ठा link_params *params)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 val16, lane;
	bnx2x_sfp_e3_set_transmitter(params, phy, 0);
	bnx2x_set_mdio_emac_per_phy(bp, params);
	bnx2x_set_aer_mmd(params, phy);
	/* Global रेजिस्टर */
	bnx2x_warpcore_reset_lane(bp, phy, 1);

	/* Clear loopback settings (अगर any) */
	/* 10G & 20G */
	bnx2x_cl45_पढ़ो_and_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
				  MDIO_WC_REG_COMBO_IEEE0_MIICTRL, 0xBFFF);

	bnx2x_cl45_पढ़ो_and_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
				  MDIO_WC_REG_IEEE0BLK_MIICNTL, 0xfffe);

	/* Update those 1-copy रेजिस्टरs */
	CL22_WR_OVER_CL45(bp, phy, MDIO_REG_BANK_AER_BLOCK,
			  MDIO_AER_BLOCK_AER_REG, 0);
	/* Enable 1G MDIO (1-copy) */
	bnx2x_cl45_पढ़ो_and_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
				  MDIO_WC_REG_XGXSBLK0_XGXSCONTROL,
				  ~0x10);

	bnx2x_cl45_पढ़ो_and_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
				  MDIO_WC_REG_XGXSBLK1_LANECTRL2, 0xff00);
	lane = bnx2x_get_warpcore_lane(phy, params);
	/* Disable CL36 PCS Tx */
	bnx2x_cl45_पढ़ो(bp, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_XGXSBLK1_LANECTRL0, &val16);
	val16 |= (0x11 << lane);
	अगर (phy->flags & FLAGS_WC_DUAL_MODE)
		val16 |= (0x22 << lane);
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_XGXSBLK1_LANECTRL0, val16);

	bnx2x_cl45_पढ़ो(bp, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_XGXSBLK1_LANECTRL1, &val16);
	val16 &= ~(0x0303 << (lane << 1));
	val16 |= (0x0101 << (lane << 1));
	अगर (phy->flags & FLAGS_WC_DUAL_MODE) अणु
		val16 &= ~(0x0c0c << (lane << 1));
		val16 |= (0x0404 << (lane << 1));
	पूर्ण

	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_XGXSBLK1_LANECTRL1, val16);
	/* Restore AER */
	bnx2x_set_aer_mmd(params, phy);

पूर्ण

अटल व्योम bnx2x_set_warpcore_loopback(काष्ठा bnx2x_phy *phy,
					काष्ठा link_params *params)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 val16;
	u32 lane;
	DP(NETIF_MSG_LINK, "Setting Warpcore loopback type %x, speed %d\n",
		       params->loopback_mode, phy->req_line_speed);

	अगर (phy->req_line_speed < SPEED_10000 ||
	    phy->supported & SUPPORTED_20000baseKR2_Full) अणु
		/* 10/100/1000/20G-KR2 */

		/* Update those 1-copy रेजिस्टरs */
		CL22_WR_OVER_CL45(bp, phy, MDIO_REG_BANK_AER_BLOCK,
				  MDIO_AER_BLOCK_AER_REG, 0);
		/* Enable 1G MDIO (1-copy) */
		bnx2x_cl45_पढ़ो_or_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
					 MDIO_WC_REG_XGXSBLK0_XGXSCONTROL,
					 0x10);
		/* Set 1G loopback based on lane (1-copy) */
		lane = bnx2x_get_warpcore_lane(phy, params);
		bnx2x_cl45_पढ़ो(bp, phy, MDIO_WC_DEVAD,
				MDIO_WC_REG_XGXSBLK1_LANECTRL2, &val16);
		val16 |= (1<<lane);
		अगर (phy->flags & FLAGS_WC_DUAL_MODE)
			val16 |= (2<<lane);
		bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
				 MDIO_WC_REG_XGXSBLK1_LANECTRL2,
				 val16);

		/* Switch back to 4-copy रेजिस्टरs */
		bnx2x_set_aer_mmd(params, phy);
	पूर्ण अन्यथा अणु
		/* 10G / 20G-DXGXS */
		bnx2x_cl45_पढ़ो_or_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
					 MDIO_WC_REG_COMBO_IEEE0_MIICTRL,
					 0x4000);
		bnx2x_cl45_पढ़ो_or_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
					 MDIO_WC_REG_IEEE0BLK_MIICNTL, 0x1);
	पूर्ण
पूर्ण



अटल व्योम bnx2x_sync_link(काष्ठा link_params *params,
			     काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u8 link_10g_plus;
	अगर (vars->link_status & LINK_STATUS_PHYSICAL_LINK_FLAG)
		vars->phy_flags |= PHY_PHYSICAL_LINK_FLAG;
	vars->link_up = (vars->link_status & LINK_STATUS_LINK_UP);
	अगर (vars->link_up) अणु
		DP(NETIF_MSG_LINK, "phy link up\n");

		vars->phy_link_up = 1;
		vars->duplex = DUPLEX_FULL;
		चयन (vars->link_status &
			LINK_STATUS_SPEED_AND_DUPLEX_MASK) अणु
		हाल LINK_10THD:
			vars->duplex = DUPLEX_HALF;
			fallthrough;
		हाल LINK_10TFD:
			vars->line_speed = SPEED_10;
			अवरोध;

		हाल LINK_100TXHD:
			vars->duplex = DUPLEX_HALF;
			fallthrough;
		हाल LINK_100T4:
		हाल LINK_100TXFD:
			vars->line_speed = SPEED_100;
			अवरोध;

		हाल LINK_1000THD:
			vars->duplex = DUPLEX_HALF;
			fallthrough;
		हाल LINK_1000TFD:
			vars->line_speed = SPEED_1000;
			अवरोध;

		हाल LINK_2500THD:
			vars->duplex = DUPLEX_HALF;
			fallthrough;
		हाल LINK_2500TFD:
			vars->line_speed = SPEED_2500;
			अवरोध;

		हाल LINK_10GTFD:
			vars->line_speed = SPEED_10000;
			अवरोध;
		हाल LINK_20GTFD:
			vars->line_speed = SPEED_20000;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		vars->flow_ctrl = 0;
		अगर (vars->link_status & LINK_STATUS_TX_FLOW_CONTROL_ENABLED)
			vars->flow_ctrl |= BNX2X_FLOW_CTRL_TX;

		अगर (vars->link_status & LINK_STATUS_RX_FLOW_CONTROL_ENABLED)
			vars->flow_ctrl |= BNX2X_FLOW_CTRL_RX;

		अगर (!vars->flow_ctrl)
			vars->flow_ctrl = BNX2X_FLOW_CTRL_NONE;

		अगर (vars->line_speed &&
		    ((vars->line_speed == SPEED_10) ||
		     (vars->line_speed == SPEED_100))) अणु
			vars->phy_flags |= PHY_SGMII_FLAG;
		पूर्ण अन्यथा अणु
			vars->phy_flags &= ~PHY_SGMII_FLAG;
		पूर्ण
		अगर (vars->line_speed &&
		    USES_WARPCORE(bp) &&
		    (vars->line_speed == SPEED_1000))
			vars->phy_flags |= PHY_SGMII_FLAG;
		/* Anything 10 and over uses the bmac */
		link_10g_plus = (vars->line_speed >= SPEED_10000);

		अगर (link_10g_plus) अणु
			अगर (USES_WARPCORE(bp))
				vars->mac_type = MAC_TYPE_XMAC;
			अन्यथा
				vars->mac_type = MAC_TYPE_BMAC;
		पूर्ण अन्यथा अणु
			अगर (USES_WARPCORE(bp))
				vars->mac_type = MAC_TYPE_UMAC;
			अन्यथा
				vars->mac_type = MAC_TYPE_EMAC;
		पूर्ण
	पूर्ण अन्यथा अणु /* Link करोwn */
		DP(NETIF_MSG_LINK, "phy link down\n");

		vars->phy_link_up = 0;

		vars->line_speed = 0;
		vars->duplex = DUPLEX_FULL;
		vars->flow_ctrl = BNX2X_FLOW_CTRL_NONE;

		/* Indicate no mac active */
		vars->mac_type = MAC_TYPE_NONE;
		अगर (vars->link_status & LINK_STATUS_PHYSICAL_LINK_FLAG)
			vars->phy_flags |= PHY_HALF_OPEN_CONN_FLAG;
		अगर (vars->link_status & LINK_STATUS_SFP_TX_FAULT)
			vars->phy_flags |= PHY_SFP_TX_FAULT_FLAG;
	पूर्ण
पूर्ण

व्योम bnx2x_link_status_update(काष्ठा link_params *params,
			      काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u8 port = params->port;
	u32 sync_offset, media_types;
	/* Update PHY configuration */
	set_phy_vars(params, vars);

	vars->link_status = REG_RD(bp, params->shmem_base +
				   दुरत्व(काष्ठा shmem_region,
					    port_mb[port].link_status));

	/* Force link UP in non LOOPBACK_EXT loopback mode(s) */
	अगर (params->loopback_mode != LOOPBACK_NONE &&
	    params->loopback_mode != LOOPBACK_EXT)
		vars->link_status |= LINK_STATUS_LINK_UP;

	अगर (bnx2x_eee_has_cap(params))
		vars->eee_status = REG_RD(bp, params->shmem2_base +
					  दुरत्व(काष्ठा shmem2_region,
						   eee_status[params->port]));

	vars->phy_flags = PHY_XGXS_FLAG;
	bnx2x_sync_link(params, vars);
	/* Sync media type */
	sync_offset = params->shmem_base +
			दुरत्व(काष्ठा shmem_region,
				 dev_info.port_hw_config[port].media_type);
	media_types = REG_RD(bp, sync_offset);

	params->phy[INT_PHY].media_type =
		(media_types & PORT_HW_CFG_MEDIA_TYPE_PHY0_MASK) >>
		PORT_HW_CFG_MEDIA_TYPE_PHY0_SHIFT;
	params->phy[EXT_PHY1].media_type =
		(media_types & PORT_HW_CFG_MEDIA_TYPE_PHY1_MASK) >>
		PORT_HW_CFG_MEDIA_TYPE_PHY1_SHIFT;
	params->phy[EXT_PHY2].media_type =
		(media_types & PORT_HW_CFG_MEDIA_TYPE_PHY2_MASK) >>
		PORT_HW_CFG_MEDIA_TYPE_PHY2_SHIFT;
	DP(NETIF_MSG_LINK, "media_types = 0x%x\n", media_types);

	/* Sync AEU offset */
	sync_offset = params->shmem_base +
			दुरत्व(काष्ठा shmem_region,
				 dev_info.port_hw_config[port].aeu_पूर्णांक_mask);

	vars->aeu_पूर्णांक_mask = REG_RD(bp, sync_offset);

	/* Sync PFC status */
	अगर (vars->link_status & LINK_STATUS_PFC_ENABLED)
		params->feature_config_flags |=
					FEATURE_CONFIG_PFC_ENABLED;
	अन्यथा
		params->feature_config_flags &=
					~FEATURE_CONFIG_PFC_ENABLED;

	अगर (SHMEM2_HAS(bp, link_attr_sync))
		params->link_attr_sync = SHMEM2_RD(bp,
						 link_attr_sync[params->port]);

	DP(NETIF_MSG_LINK, "link_status 0x%x  phy_link_up %x int_mask 0x%x\n",
		 vars->link_status, vars->phy_link_up, vars->aeu_पूर्णांक_mask);
	DP(NETIF_MSG_LINK, "line_speed %x  duplex %x  flow_ctrl 0x%x\n",
		 vars->line_speed, vars->duplex, vars->flow_ctrl);
पूर्ण

अटल व्योम bnx2x_set_master_ln(काष्ठा link_params *params,
				काष्ठा bnx2x_phy *phy)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 new_master_ln, ser_lane;
	ser_lane = ((params->lane_config &
		     PORT_HW_CFG_LANE_SWAP_CFG_MASTER_MASK) >>
		    PORT_HW_CFG_LANE_SWAP_CFG_MASTER_SHIFT);

	/* Set the master_ln क्रम AN */
	CL22_RD_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_XGXS_BLOCK2,
			  MDIO_XGXS_BLOCK2_TEST_MODE_LANE,
			  &new_master_ln);

	CL22_WR_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_XGXS_BLOCK2 ,
			  MDIO_XGXS_BLOCK2_TEST_MODE_LANE,
			  (new_master_ln | ser_lane));
पूर्ण

अटल पूर्णांक bnx2x_reset_unicore(काष्ठा link_params *params,
			       काष्ठा bnx2x_phy *phy,
			       u8 set_serdes)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 mii_control;
	u16 i;
	CL22_RD_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_COMBO_IEEE0,
			  MDIO_COMBO_IEEE0_MII_CONTROL, &mii_control);

	/* Reset the unicore */
	CL22_WR_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_COMBO_IEEE0,
			  MDIO_COMBO_IEEE0_MII_CONTROL,
			  (mii_control |
			   MDIO_COMBO_IEEO_MII_CONTROL_RESET));
	अगर (set_serdes)
		bnx2x_set_serdes_access(bp, params->port);

	/* Wait क्रम the reset to self clear */
	क्रम (i = 0; i < MDIO_ACCESS_TIMEOUT; i++) अणु
		udelay(5);

		/* The reset erased the previous bank value */
		CL22_RD_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_COMBO_IEEE0,
				  MDIO_COMBO_IEEE0_MII_CONTROL,
				  &mii_control);

		अगर (!(mii_control & MDIO_COMBO_IEEO_MII_CONTROL_RESET)) अणु
			udelay(5);
			वापस 0;
		पूर्ण
	पूर्ण

	netdev_err(bp->dev,  "Warning: PHY was not initialized,"
			      " Port %d\n",
			 params->port);
	DP(NETIF_MSG_LINK, "BUG! XGXS is still in reset!\n");
	वापस -EINVAL;

पूर्ण

अटल व्योम bnx2x_set_swap_lanes(काष्ठा link_params *params,
				 काष्ठा bnx2x_phy *phy)
अणु
	काष्ठा bnx2x *bp = params->bp;
	/* Each two bits represents a lane number:
	 * No swap is 0123 => 0x1b no need to enable the swap
	 */
	u16 rx_lane_swap, tx_lane_swap;

	rx_lane_swap = ((params->lane_config &
			 PORT_HW_CFG_LANE_SWAP_CFG_RX_MASK) >>
			PORT_HW_CFG_LANE_SWAP_CFG_RX_SHIFT);
	tx_lane_swap = ((params->lane_config &
			 PORT_HW_CFG_LANE_SWAP_CFG_TX_MASK) >>
			PORT_HW_CFG_LANE_SWAP_CFG_TX_SHIFT);

	अगर (rx_lane_swap != 0x1b) अणु
		CL22_WR_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_XGXS_BLOCK2,
				  MDIO_XGXS_BLOCK2_RX_LN_SWAP,
				  (rx_lane_swap |
				   MDIO_XGXS_BLOCK2_RX_LN_SWAP_ENABLE |
				   MDIO_XGXS_BLOCK2_RX_LN_SWAP_FORCE_ENABLE));
	पूर्ण अन्यथा अणु
		CL22_WR_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_XGXS_BLOCK2,
				  MDIO_XGXS_BLOCK2_RX_LN_SWAP, 0);
	पूर्ण

	अगर (tx_lane_swap != 0x1b) अणु
		CL22_WR_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_XGXS_BLOCK2,
				  MDIO_XGXS_BLOCK2_TX_LN_SWAP,
				  (tx_lane_swap |
				   MDIO_XGXS_BLOCK2_TX_LN_SWAP_ENABLE));
	पूर्ण अन्यथा अणु
		CL22_WR_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_XGXS_BLOCK2,
				  MDIO_XGXS_BLOCK2_TX_LN_SWAP, 0);
	पूर्ण
पूर्ण

अटल व्योम bnx2x_set_parallel_detection(काष्ठा bnx2x_phy *phy,
					 काष्ठा link_params *params)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 control2;
	CL22_RD_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_SERDES_DIGITAL,
			  MDIO_SERDES_DIGITAL_A_1000X_CONTROL2,
			  &control2);
	अगर (phy->speed_cap_mask & PORT_HW_CFG_SPEED_CAPABILITY_D0_1G)
		control2 |= MDIO_SERDES_DIGITAL_A_1000X_CONTROL2_PRL_DT_EN;
	अन्यथा
		control2 &= ~MDIO_SERDES_DIGITAL_A_1000X_CONTROL2_PRL_DT_EN;
	DP(NETIF_MSG_LINK, "phy->speed_cap_mask = 0x%x, control2 = 0x%x\n",
		phy->speed_cap_mask, control2);
	CL22_WR_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_SERDES_DIGITAL,
			  MDIO_SERDES_DIGITAL_A_1000X_CONTROL2,
			  control2);

	अगर ((phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_सूचीECT) &&
	     (phy->speed_cap_mask &
		    PORT_HW_CFG_SPEED_CAPABILITY_D0_10G)) अणु
		DP(NETIF_MSG_LINK, "XGXS\n");

		CL22_WR_OVER_CL45(bp, phy,
				 MDIO_REG_BANK_10G_PARALLEL_DETECT,
				 MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_LINK,
				 MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_LINK_CNT);

		CL22_RD_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_10G_PARALLEL_DETECT,
				  MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_CONTROL,
				  &control2);


		control2 |=
		    MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_CONTROL_PARDET10G_EN;

		CL22_WR_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_10G_PARALLEL_DETECT,
				  MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_CONTROL,
				  control2);

		/* Disable parallel detection of HiG */
		CL22_WR_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_XGXS_BLOCK2,
				  MDIO_XGXS_BLOCK2_UNICORE_MODE_10G,
				  MDIO_XGXS_BLOCK2_UNICORE_MODE_10G_CX4_XGXS |
				  MDIO_XGXS_BLOCK2_UNICORE_MODE_10G_HIGIG_XGXS);
	पूर्ण
पूर्ण

अटल व्योम bnx2x_set_स्वतःneg(काष्ठा bnx2x_phy *phy,
			      काष्ठा link_params *params,
			      काष्ठा link_vars *vars,
			      u8 enable_cl73)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 reg_val;

	/* CL37 Autoneg */
	CL22_RD_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_COMBO_IEEE0,
			  MDIO_COMBO_IEEE0_MII_CONTROL, &reg_val);

	/* CL37 Autoneg Enabled */
	अगर (vars->line_speed == SPEED_AUTO_NEG)
		reg_val |= MDIO_COMBO_IEEO_MII_CONTROL_AN_EN;
	अन्यथा /* CL37 Autoneg Disabled */
		reg_val &= ~(MDIO_COMBO_IEEO_MII_CONTROL_AN_EN |
			     MDIO_COMBO_IEEO_MII_CONTROL_RESTART_AN);

	CL22_WR_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_COMBO_IEEE0,
			  MDIO_COMBO_IEEE0_MII_CONTROL, reg_val);

	/* Enable/Disable Autodetection */

	CL22_RD_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_SERDES_DIGITAL,
			  MDIO_SERDES_DIGITAL_A_1000X_CONTROL1, &reg_val);
	reg_val &= ~(MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_SIGNAL_DETECT_EN |
		    MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_INVERT_SIGNAL_DETECT);
	reg_val |= MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_FIBER_MODE;
	अगर (vars->line_speed == SPEED_AUTO_NEG)
		reg_val |= MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_AUTODET;
	अन्यथा
		reg_val &= ~MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_AUTODET;

	CL22_WR_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_SERDES_DIGITAL,
			  MDIO_SERDES_DIGITAL_A_1000X_CONTROL1, reg_val);

	/* Enable TetonII and BAM स्वतःneg */
	CL22_RD_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_BAM_NEXT_PAGE,
			  MDIO_BAM_NEXT_PAGE_MP5_NEXT_PAGE_CTRL,
			  &reg_val);
	अगर (vars->line_speed == SPEED_AUTO_NEG) अणु
		/* Enable BAM aneg Mode and TetonII aneg Mode */
		reg_val |= (MDIO_BAM_NEXT_PAGE_MP5_NEXT_PAGE_CTRL_BAM_MODE |
			    MDIO_BAM_NEXT_PAGE_MP5_NEXT_PAGE_CTRL_TETON_AN);
	पूर्ण अन्यथा अणु
		/* TetonII and BAM Autoneg Disabled */
		reg_val &= ~(MDIO_BAM_NEXT_PAGE_MP5_NEXT_PAGE_CTRL_BAM_MODE |
			     MDIO_BAM_NEXT_PAGE_MP5_NEXT_PAGE_CTRL_TETON_AN);
	पूर्ण
	CL22_WR_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_BAM_NEXT_PAGE,
			  MDIO_BAM_NEXT_PAGE_MP5_NEXT_PAGE_CTRL,
			  reg_val);

	अगर (enable_cl73) अणु
		/* Enable Cl73 FSM status bits */
		CL22_WR_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_CL73_USERB0,
				  MDIO_CL73_USERB0_CL73_UCTRL,
				  0xe);

		/* Enable BAM Station Manager*/
		CL22_WR_OVER_CL45(bp, phy,
			MDIO_REG_BANK_CL73_USERB0,
			MDIO_CL73_USERB0_CL73_BAM_CTRL1,
			MDIO_CL73_USERB0_CL73_BAM_CTRL1_BAM_EN |
			MDIO_CL73_USERB0_CL73_BAM_CTRL1_BAM_STATION_MNGR_EN |
			MDIO_CL73_USERB0_CL73_BAM_CTRL1_BAM_NP_AFTER_BP_EN);

		/* Advertise CL73 link speeds */
		CL22_RD_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_CL73_IEEEB1,
				  MDIO_CL73_IEEEB1_AN_ADV2,
				  &reg_val);
		अगर (phy->speed_cap_mask &
		    PORT_HW_CFG_SPEED_CAPABILITY_D0_10G)
			reg_val |= MDIO_CL73_IEEEB1_AN_ADV2_ADVR_10G_KX4;
		अगर (phy->speed_cap_mask &
		    PORT_HW_CFG_SPEED_CAPABILITY_D0_1G)
			reg_val |= MDIO_CL73_IEEEB1_AN_ADV2_ADVR_1000M_KX;

		CL22_WR_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_CL73_IEEEB1,
				  MDIO_CL73_IEEEB1_AN_ADV2,
				  reg_val);

		/* CL73 Autoneg Enabled */
		reg_val = MDIO_CL73_IEEEB0_CL73_AN_CONTROL_AN_EN;

	पूर्ण अन्यथा /* CL73 Autoneg Disabled */
		reg_val = 0;

	CL22_WR_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_CL73_IEEEB0,
			  MDIO_CL73_IEEEB0_CL73_AN_CONTROL, reg_val);
पूर्ण

/* Program SerDes, क्रमced speed */
अटल व्योम bnx2x_program_serdes(काष्ठा bnx2x_phy *phy,
				 काष्ठा link_params *params,
				 काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 reg_val;

	/* Program duplex, disable स्वतःneg and sgmii*/
	CL22_RD_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_COMBO_IEEE0,
			  MDIO_COMBO_IEEE0_MII_CONTROL, &reg_val);
	reg_val &= ~(MDIO_COMBO_IEEO_MII_CONTROL_FULL_DUPLEX |
		     MDIO_COMBO_IEEO_MII_CONTROL_AN_EN |
		     MDIO_COMBO_IEEO_MII_CONTROL_MAN_SGMII_SP_MASK);
	अगर (phy->req_duplex == DUPLEX_FULL)
		reg_val |= MDIO_COMBO_IEEO_MII_CONTROL_FULL_DUPLEX;
	CL22_WR_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_COMBO_IEEE0,
			  MDIO_COMBO_IEEE0_MII_CONTROL, reg_val);

	/* Program speed
	 *  - needed only अगर the speed is greater than 1G (2.5G or 10G)
	 */
	CL22_RD_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_SERDES_DIGITAL,
			  MDIO_SERDES_DIGITAL_MISC1, &reg_val);
	/* Clearing the speed value beक्रमe setting the right speed */
	DP(NETIF_MSG_LINK, "MDIO_REG_BANK_SERDES_DIGITAL = 0x%x\n", reg_val);

	reg_val &= ~(MDIO_SERDES_DIGITAL_MISC1_FORCE_SPEED_MASK |
		     MDIO_SERDES_DIGITAL_MISC1_FORCE_SPEED_SEL);

	अगर (!((vars->line_speed == SPEED_1000) ||
	      (vars->line_speed == SPEED_100) ||
	      (vars->line_speed == SPEED_10))) अणु

		reg_val |= (MDIO_SERDES_DIGITAL_MISC1_REFCLK_SEL_156_25M |
			    MDIO_SERDES_DIGITAL_MISC1_FORCE_SPEED_SEL);
		अगर (vars->line_speed == SPEED_10000)
			reg_val |=
				MDIO_SERDES_DIGITAL_MISC1_FORCE_SPEED_10G_CX4;
	पूर्ण

	CL22_WR_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_SERDES_DIGITAL,
			  MDIO_SERDES_DIGITAL_MISC1, reg_val);

पूर्ण

अटल व्योम bnx2x_set_brcm_cl37_advertisement(काष्ठा bnx2x_phy *phy,
					      काष्ठा link_params *params)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 val = 0;

	/* Set extended capabilities */
	अगर (phy->speed_cap_mask & PORT_HW_CFG_SPEED_CAPABILITY_D0_2_5G)
		val |= MDIO_OVER_1G_UP1_2_5G;
	अगर (phy->speed_cap_mask & PORT_HW_CFG_SPEED_CAPABILITY_D0_10G)
		val |= MDIO_OVER_1G_UP1_10G;
	CL22_WR_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_OVER_1G,
			  MDIO_OVER_1G_UP1, val);

	CL22_WR_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_OVER_1G,
			  MDIO_OVER_1G_UP3, 0x400);
पूर्ण

अटल व्योम bnx2x_set_ieee_aneg_advertisement(काष्ठा bnx2x_phy *phy,
					      काष्ठा link_params *params,
					      u16 ieee_fc)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 val;
	/* For AN, we are always publishing full duplex */

	CL22_WR_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_COMBO_IEEE0,
			  MDIO_COMBO_IEEE0_AUTO_NEG_ADV, ieee_fc);
	CL22_RD_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_CL73_IEEEB1,
			  MDIO_CL73_IEEEB1_AN_ADV1, &val);
	val &= ~MDIO_CL73_IEEEB1_AN_ADV1_PAUSE_BOTH;
	val |= ((ieee_fc<<3) & MDIO_CL73_IEEEB1_AN_ADV1_PAUSE_MASK);
	CL22_WR_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_CL73_IEEEB1,
			  MDIO_CL73_IEEEB1_AN_ADV1, val);
पूर्ण

अटल व्योम bnx2x_restart_स्वतःneg(काष्ठा bnx2x_phy *phy,
				  काष्ठा link_params *params,
				  u8 enable_cl73)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 mii_control;

	DP(NETIF_MSG_LINK, "bnx2x_restart_autoneg\n");
	/* Enable and restart BAM/CL37 aneg */

	अगर (enable_cl73) अणु
		CL22_RD_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_CL73_IEEEB0,
				  MDIO_CL73_IEEEB0_CL73_AN_CONTROL,
				  &mii_control);

		CL22_WR_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_CL73_IEEEB0,
				  MDIO_CL73_IEEEB0_CL73_AN_CONTROL,
				  (mii_control |
				  MDIO_CL73_IEEEB0_CL73_AN_CONTROL_AN_EN |
				  MDIO_CL73_IEEEB0_CL73_AN_CONTROL_RESTART_AN));
	पूर्ण अन्यथा अणु

		CL22_RD_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_COMBO_IEEE0,
				  MDIO_COMBO_IEEE0_MII_CONTROL,
				  &mii_control);
		DP(NETIF_MSG_LINK,
			 "bnx2x_restart_autoneg mii_control before = 0x%x\n",
			 mii_control);
		CL22_WR_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_COMBO_IEEE0,
				  MDIO_COMBO_IEEE0_MII_CONTROL,
				  (mii_control |
				   MDIO_COMBO_IEEO_MII_CONTROL_AN_EN |
				   MDIO_COMBO_IEEO_MII_CONTROL_RESTART_AN));
	पूर्ण
पूर्ण

अटल व्योम bnx2x_initialize_sgmii_process(काष्ठा bnx2x_phy *phy,
					   काष्ठा link_params *params,
					   काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 control1;

	/* In SGMII mode, the unicore is always slave */

	CL22_RD_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_SERDES_DIGITAL,
			  MDIO_SERDES_DIGITAL_A_1000X_CONTROL1,
			  &control1);
	control1 |= MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_INVERT_SIGNAL_DETECT;
	/* Set sgmii mode (and not fiber) */
	control1 &= ~(MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_FIBER_MODE |
		      MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_AUTODET |
		      MDIO_SERDES_DIGITAL_A_1000X_CONTROL1_MSTR_MODE);
	CL22_WR_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_SERDES_DIGITAL,
			  MDIO_SERDES_DIGITAL_A_1000X_CONTROL1,
			  control1);

	/* If क्रमced speed */
	अगर (!(vars->line_speed == SPEED_AUTO_NEG)) अणु
		/* Set speed, disable स्वतःneg */
		u16 mii_control;

		CL22_RD_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_COMBO_IEEE0,
				  MDIO_COMBO_IEEE0_MII_CONTROL,
				  &mii_control);
		mii_control &= ~(MDIO_COMBO_IEEO_MII_CONTROL_AN_EN |
				 MDIO_COMBO_IEEO_MII_CONTROL_MAN_SGMII_SP_MASK|
				 MDIO_COMBO_IEEO_MII_CONTROL_FULL_DUPLEX);

		चयन (vars->line_speed) अणु
		हाल SPEED_100:
			mii_control |=
				MDIO_COMBO_IEEO_MII_CONTROL_MAN_SGMII_SP_100;
			अवरोध;
		हाल SPEED_1000:
			mii_control |=
				MDIO_COMBO_IEEO_MII_CONTROL_MAN_SGMII_SP_1000;
			अवरोध;
		हाल SPEED_10:
			/* There is nothing to set क्रम 10M */
			अवरोध;
		शेष:
			/* Invalid speed क्रम SGMII */
			DP(NETIF_MSG_LINK, "Invalid line_speed 0x%x\n",
				  vars->line_speed);
			अवरोध;
		पूर्ण

		/* Setting the full duplex */
		अगर (phy->req_duplex == DUPLEX_FULL)
			mii_control |=
				MDIO_COMBO_IEEO_MII_CONTROL_FULL_DUPLEX;
		CL22_WR_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_COMBO_IEEE0,
				  MDIO_COMBO_IEEE0_MII_CONTROL,
				  mii_control);

	पूर्ण अन्यथा अणु /* AN mode */
		/* Enable and restart AN */
		bnx2x_restart_स्वतःneg(phy, params, 0);
	पूर्ण
पूर्ण

/* Link management
 */
अटल पूर्णांक bnx2x_direct_parallel_detect_used(काष्ठा bnx2x_phy *phy,
					     काष्ठा link_params *params)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 pd_10g, status2_1000x;
	अगर (phy->req_line_speed != SPEED_AUTO_NEG)
		वापस 0;
	CL22_RD_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_SERDES_DIGITAL,
			  MDIO_SERDES_DIGITAL_A_1000X_STATUS2,
			  &status2_1000x);
	CL22_RD_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_SERDES_DIGITAL,
			  MDIO_SERDES_DIGITAL_A_1000X_STATUS2,
			  &status2_1000x);
	अगर (status2_1000x & MDIO_SERDES_DIGITAL_A_1000X_STATUS2_AN_DISABLED) अणु
		DP(NETIF_MSG_LINK, "1G parallel detect link on port %d\n",
			 params->port);
		वापस 1;
	पूर्ण

	CL22_RD_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_10G_PARALLEL_DETECT,
			  MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_STATUS,
			  &pd_10g);

	अगर (pd_10g & MDIO_10G_PARALLEL_DETECT_PAR_DET_10G_STATUS_PD_LINK) अणु
		DP(NETIF_MSG_LINK, "10G parallel detect link on port %d\n",
			 params->port);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम bnx2x_update_adv_fc(काष्ठा bnx2x_phy *phy,
				काष्ठा link_params *params,
				काष्ठा link_vars *vars,
				u32 gp_status)
अणु
	u16 ld_छोड़ो;   /* local driver */
	u16 lp_छोड़ो;   /* link partner */
	u16 छोड़ो_result;
	काष्ठा bnx2x *bp = params->bp;
	अगर ((gp_status &
	     (MDIO_GP_STATUS_TOP_AN_STATUS1_CL73_AUTONEG_COMPLETE |
	      MDIO_GP_STATUS_TOP_AN_STATUS1_CL73_MR_LP_NP_AN_ABLE)) ==
	    (MDIO_GP_STATUS_TOP_AN_STATUS1_CL73_AUTONEG_COMPLETE |
	     MDIO_GP_STATUS_TOP_AN_STATUS1_CL73_MR_LP_NP_AN_ABLE)) अणु

		CL22_RD_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_CL73_IEEEB1,
				  MDIO_CL73_IEEEB1_AN_ADV1,
				  &ld_छोड़ो);
		CL22_RD_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_CL73_IEEEB1,
				  MDIO_CL73_IEEEB1_AN_LP_ADV1,
				  &lp_छोड़ो);
		छोड़ो_result = (ld_छोड़ो &
				MDIO_CL73_IEEEB1_AN_ADV1_PAUSE_MASK) >> 8;
		छोड़ो_result |= (lp_छोड़ो &
				 MDIO_CL73_IEEEB1_AN_LP_ADV1_PAUSE_MASK) >> 10;
		DP(NETIF_MSG_LINK, "pause_result CL73 0x%x\n", छोड़ो_result);
	पूर्ण अन्यथा अणु
		CL22_RD_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_COMBO_IEEE0,
				  MDIO_COMBO_IEEE0_AUTO_NEG_ADV,
				  &ld_छोड़ो);
		CL22_RD_OVER_CL45(bp, phy,
			MDIO_REG_BANK_COMBO_IEEE0,
			MDIO_COMBO_IEEE0_AUTO_NEG_LINK_PARTNER_ABILITY1,
			&lp_छोड़ो);
		छोड़ो_result = (ld_छोड़ो &
				MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_MASK)>>5;
		छोड़ो_result |= (lp_छोड़ो &
				 MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_MASK)>>7;
		DP(NETIF_MSG_LINK, "pause_result CL37 0x%x\n", छोड़ो_result);
	पूर्ण
	bnx2x_छोड़ो_resolve(phy, params, vars, छोड़ो_result);

पूर्ण

अटल व्योम bnx2x_flow_ctrl_resolve(काष्ठा bnx2x_phy *phy,
				    काष्ठा link_params *params,
				    काष्ठा link_vars *vars,
				    u32 gp_status)
अणु
	काष्ठा bnx2x *bp = params->bp;
	vars->flow_ctrl = BNX2X_FLOW_CTRL_NONE;

	/* Resolve from gp_status in हाल of AN complete and not sgmii */
	अगर (phy->req_flow_ctrl != BNX2X_FLOW_CTRL_AUTO) अणु
		/* Update the advertised flow-controled of LD/LP in AN */
		अगर (phy->req_line_speed == SPEED_AUTO_NEG)
			bnx2x_update_adv_fc(phy, params, vars, gp_status);
		/* But set the flow-control result as the requested one */
		vars->flow_ctrl = phy->req_flow_ctrl;
	पूर्ण अन्यथा अगर (phy->req_line_speed != SPEED_AUTO_NEG)
		vars->flow_ctrl = params->req_fc_स्वतः_adv;
	अन्यथा अगर ((gp_status & MDIO_AN_CL73_OR_37_COMPLETE) &&
		 (!(vars->phy_flags & PHY_SGMII_FLAG))) अणु
		अगर (bnx2x_direct_parallel_detect_used(phy, params)) अणु
			vars->flow_ctrl = params->req_fc_स्वतः_adv;
			वापस;
		पूर्ण
		bnx2x_update_adv_fc(phy, params, vars, gp_status);
	पूर्ण
	DP(NETIF_MSG_LINK, "flow_ctrl 0x%x\n", vars->flow_ctrl);
पूर्ण

अटल व्योम bnx2x_check_fallback_to_cl37(काष्ठा bnx2x_phy *phy,
					 काष्ठा link_params *params)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 rx_status, ustat_val, cl37_fsm_received;
	DP(NETIF_MSG_LINK, "bnx2x_check_fallback_to_cl37\n");
	/* Step 1: Make sure संकेत is detected */
	CL22_RD_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_RX0,
			  MDIO_RX0_RX_STATUS,
			  &rx_status);
	अगर ((rx_status & MDIO_RX0_RX_STATUS_SIGDET) !=
	    (MDIO_RX0_RX_STATUS_SIGDET)) अणु
		DP(NETIF_MSG_LINK, "Signal is not detected. Restoring CL73."
			     "rx_status(0x80b0) = 0x%x\n", rx_status);
		CL22_WR_OVER_CL45(bp, phy,
				  MDIO_REG_BANK_CL73_IEEEB0,
				  MDIO_CL73_IEEEB0_CL73_AN_CONTROL,
				  MDIO_CL73_IEEEB0_CL73_AN_CONTROL_AN_EN);
		वापस;
	पूर्ण
	/* Step 2: Check CL73 state machine */
	CL22_RD_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_CL73_USERB0,
			  MDIO_CL73_USERB0_CL73_USTAT1,
			  &ustat_val);
	अगर ((ustat_val &
	     (MDIO_CL73_USERB0_CL73_USTAT1_LINK_STATUS_CHECK |
	      MDIO_CL73_USERB0_CL73_USTAT1_AN_GOOD_CHECK_BAM37)) !=
	    (MDIO_CL73_USERB0_CL73_USTAT1_LINK_STATUS_CHECK |
	      MDIO_CL73_USERB0_CL73_USTAT1_AN_GOOD_CHECK_BAM37)) अणु
		DP(NETIF_MSG_LINK, "CL73 state-machine is not stable. "
			     "ustat_val(0x8371) = 0x%x\n", ustat_val);
		वापस;
	पूर्ण
	/* Step 3: Check CL37 Message Pages received to indicate LP
	 * supports only CL37
	 */
	CL22_RD_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_REMOTE_PHY,
			  MDIO_REMOTE_PHY_MISC_RX_STATUS,
			  &cl37_fsm_received);
	अगर ((cl37_fsm_received &
	     (MDIO_REMOTE_PHY_MISC_RX_STATUS_CL37_FSM_RECEIVED_OVER1G_MSG |
	     MDIO_REMOTE_PHY_MISC_RX_STATUS_CL37_FSM_RECEIVED_BRCM_OUI_MSG)) !=
	    (MDIO_REMOTE_PHY_MISC_RX_STATUS_CL37_FSM_RECEIVED_OVER1G_MSG |
	      MDIO_REMOTE_PHY_MISC_RX_STATUS_CL37_FSM_RECEIVED_BRCM_OUI_MSG)) अणु
		DP(NETIF_MSG_LINK, "No CL37 FSM were received. "
			     "misc_rx_status(0x8330) = 0x%x\n",
			 cl37_fsm_received);
		वापस;
	पूर्ण
	/* The combined cl37/cl73 fsm state inक्रमmation indicating that
	 * we are connected to a device which करोes not support cl73, but
	 * करोes support cl37 BAM. In this हाल we disable cl73 and
	 * restart cl37 स्वतः-neg
	 */

	/* Disable CL73 */
	CL22_WR_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_CL73_IEEEB0,
			  MDIO_CL73_IEEEB0_CL73_AN_CONTROL,
			  0);
	/* Restart CL37 स्वतःneg */
	bnx2x_restart_स्वतःneg(phy, params, 0);
	DP(NETIF_MSG_LINK, "Disabling CL73, and restarting CL37 autoneg\n");
पूर्ण

अटल व्योम bnx2x_xgxs_an_resolve(काष्ठा bnx2x_phy *phy,
				  काष्ठा link_params *params,
				  काष्ठा link_vars *vars,
				  u32 gp_status)
अणु
	अगर (gp_status & MDIO_AN_CL73_OR_37_COMPLETE)
		vars->link_status |=
			LINK_STATUS_AUTO_NEGOTIATE_COMPLETE;

	अगर (bnx2x_direct_parallel_detect_used(phy, params))
		vars->link_status |=
			LINK_STATUS_PARALLEL_DETECTION_USED;
पूर्ण
अटल पूर्णांक bnx2x_get_link_speed_duplex(काष्ठा bnx2x_phy *phy,
				     काष्ठा link_params *params,
				      काष्ठा link_vars *vars,
				      u16 is_link_up,
				      u16 speed_mask,
				      u16 is_duplex)
अणु
	काष्ठा bnx2x *bp = params->bp;
	अगर (phy->req_line_speed == SPEED_AUTO_NEG)
		vars->link_status |= LINK_STATUS_AUTO_NEGOTIATE_ENABLED;
	अगर (is_link_up) अणु
		DP(NETIF_MSG_LINK, "phy link up\n");

		vars->phy_link_up = 1;
		vars->link_status |= LINK_STATUS_LINK_UP;

		चयन (speed_mask) अणु
		हाल GP_STATUS_10M:
			vars->line_speed = SPEED_10;
			अगर (is_duplex == DUPLEX_FULL)
				vars->link_status |= LINK_10TFD;
			अन्यथा
				vars->link_status |= LINK_10THD;
			अवरोध;

		हाल GP_STATUS_100M:
			vars->line_speed = SPEED_100;
			अगर (is_duplex == DUPLEX_FULL)
				vars->link_status |= LINK_100TXFD;
			अन्यथा
				vars->link_status |= LINK_100TXHD;
			अवरोध;

		हाल GP_STATUS_1G:
		हाल GP_STATUS_1G_KX:
			vars->line_speed = SPEED_1000;
			अगर (is_duplex == DUPLEX_FULL)
				vars->link_status |= LINK_1000TFD;
			अन्यथा
				vars->link_status |= LINK_1000THD;
			अवरोध;

		हाल GP_STATUS_2_5G:
			vars->line_speed = SPEED_2500;
			अगर (is_duplex == DUPLEX_FULL)
				vars->link_status |= LINK_2500TFD;
			अन्यथा
				vars->link_status |= LINK_2500THD;
			अवरोध;

		हाल GP_STATUS_5G:
		हाल GP_STATUS_6G:
			DP(NETIF_MSG_LINK,
				 "link speed unsupported  gp_status 0x%x\n",
				  speed_mask);
			वापस -EINVAL;

		हाल GP_STATUS_10G_KX4:
		हाल GP_STATUS_10G_HIG:
		हाल GP_STATUS_10G_CX4:
		हाल GP_STATUS_10G_KR:
		हाल GP_STATUS_10G_SFI:
		हाल GP_STATUS_10G_XFI:
			vars->line_speed = SPEED_10000;
			vars->link_status |= LINK_10GTFD;
			अवरोध;
		हाल GP_STATUS_20G_DXGXS:
		हाल GP_STATUS_20G_KR2:
			vars->line_speed = SPEED_20000;
			vars->link_status |= LINK_20GTFD;
			अवरोध;
		शेष:
			DP(NETIF_MSG_LINK,
				  "link speed unsupported gp_status 0x%x\n",
				  speed_mask);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु /* link_करोwn */
		DP(NETIF_MSG_LINK, "phy link down\n");

		vars->phy_link_up = 0;

		vars->duplex = DUPLEX_FULL;
		vars->flow_ctrl = BNX2X_FLOW_CTRL_NONE;
		vars->mac_type = MAC_TYPE_NONE;
	पूर्ण
	DP(NETIF_MSG_LINK, " phy_link_up %x line_speed %d\n",
		    vars->phy_link_up, vars->line_speed);
	वापस 0;
पूर्ण

अटल u8 bnx2x_link_settings_status(काष्ठा bnx2x_phy *phy,
				     काष्ठा link_params *params,
				     काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;

	u16 gp_status, duplex = DUPLEX_HALF, link_up = 0, speed_mask;
	पूर्णांक rc = 0;

	/* Read gp_status */
	CL22_RD_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_GP_STATUS,
			  MDIO_GP_STATUS_TOP_AN_STATUS1,
			  &gp_status);
	अगर (gp_status & MDIO_GP_STATUS_TOP_AN_STATUS1_DUPLEX_STATUS)
		duplex = DUPLEX_FULL;
	अगर (gp_status & MDIO_GP_STATUS_TOP_AN_STATUS1_LINK_STATUS)
		link_up = 1;
	speed_mask = gp_status & GP_STATUS_SPEED_MASK;
	DP(NETIF_MSG_LINK, "gp_status 0x%x, is_link_up %d, speed_mask 0x%x\n",
		       gp_status, link_up, speed_mask);
	rc = bnx2x_get_link_speed_duplex(phy, params, vars, link_up, speed_mask,
					 duplex);
	अगर (rc == -EINVAL)
		वापस rc;

	अगर (gp_status & MDIO_GP_STATUS_TOP_AN_STATUS1_LINK_STATUS) अणु
		अगर (SINGLE_MEDIA_सूचीECT(params)) अणु
			vars->duplex = duplex;
			bnx2x_flow_ctrl_resolve(phy, params, vars, gp_status);
			अगर (phy->req_line_speed == SPEED_AUTO_NEG)
				bnx2x_xgxs_an_resolve(phy, params, vars,
						      gp_status);
		पूर्ण
	पूर्ण अन्यथा अणु /* Link_करोwn */
		अगर ((phy->req_line_speed == SPEED_AUTO_NEG) &&
		    SINGLE_MEDIA_सूचीECT(params)) अणु
			/* Check संकेत is detected */
			bnx2x_check_fallback_to_cl37(phy, params);
		पूर्ण
	पूर्ण

	/* Read LP advertised speeds*/
	अगर (SINGLE_MEDIA_सूचीECT(params) &&
	    (vars->link_status & LINK_STATUS_AUTO_NEGOTIATE_COMPLETE)) अणु
		u16 val;

		CL22_RD_OVER_CL45(bp, phy, MDIO_REG_BANK_CL73_IEEEB1,
				  MDIO_CL73_IEEEB1_AN_LP_ADV2, &val);

		अगर (val & MDIO_CL73_IEEEB1_AN_ADV2_ADVR_1000M_KX)
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_1000TFD_CAPABLE;
		अगर (val & (MDIO_CL73_IEEEB1_AN_ADV2_ADVR_10G_KX4 |
			   MDIO_CL73_IEEEB1_AN_ADV2_ADVR_10G_KR))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_10GXFD_CAPABLE;

		CL22_RD_OVER_CL45(bp, phy, MDIO_REG_BANK_OVER_1G,
				  MDIO_OVER_1G_LP_UP1, &val);

		अगर (val & MDIO_OVER_1G_UP1_2_5G)
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_2500XFD_CAPABLE;
		अगर (val & (MDIO_OVER_1G_UP1_10G | MDIO_OVER_1G_UP1_10GH))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_10GXFD_CAPABLE;
	पूर्ण

	DP(NETIF_MSG_LINK, "duplex %x  flow_ctrl 0x%x link_status 0x%x\n",
		   vars->duplex, vars->flow_ctrl, vars->link_status);
	वापस rc;
पूर्ण

अटल u8 bnx2x_warpcore_पढ़ो_status(काष्ठा bnx2x_phy *phy,
				     काष्ठा link_params *params,
				     काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u8 lane;
	u16 gp_status1, gp_speed, link_up, duplex = DUPLEX_FULL;
	पूर्णांक rc = 0;
	lane = bnx2x_get_warpcore_lane(phy, params);
	/* Read gp_status */
	अगर ((params->loopback_mode) &&
	    (phy->flags & FLAGS_WC_DUAL_MODE)) अणु
		bnx2x_cl45_पढ़ो(bp, phy, MDIO_WC_DEVAD,
				MDIO_WC_REG_DIGITAL5_LINK_STATUS, &link_up);
		bnx2x_cl45_पढ़ो(bp, phy, MDIO_WC_DEVAD,
				MDIO_WC_REG_DIGITAL5_LINK_STATUS, &link_up);
		link_up &= 0x1;
	पूर्ण अन्यथा अगर ((phy->req_line_speed > SPEED_10000) &&
		(phy->supported & SUPPORTED_20000baseMLD2_Full)) अणु
		u16 temp_link_up;
		bnx2x_cl45_पढ़ो(bp, phy, MDIO_WC_DEVAD,
				1, &temp_link_up);
		bnx2x_cl45_पढ़ो(bp, phy, MDIO_WC_DEVAD,
				1, &link_up);
		DP(NETIF_MSG_LINK, "PCS RX link status = 0x%x-->0x%x\n",
			       temp_link_up, link_up);
		link_up &= (1<<2);
		अगर (link_up)
			bnx2x_ext_phy_resolve_fc(phy, params, vars);
	पूर्ण अन्यथा अणु
		bnx2x_cl45_पढ़ो(bp, phy, MDIO_WC_DEVAD,
				MDIO_WC_REG_GP2_STATUS_GP_2_1,
				&gp_status1);
		DP(NETIF_MSG_LINK, "0x81d1 = 0x%x\n", gp_status1);
		/* Check क्रम either KR, 1G, or AN up. */
		link_up = ((gp_status1 >> 8) |
			   (gp_status1 >> 12) |
			   (gp_status1)) &
			(1 << lane);
		अगर (phy->supported & SUPPORTED_20000baseKR2_Full) अणु
			u16 an_link;
			bnx2x_cl45_पढ़ो(bp, phy, MDIO_AN_DEVAD,
					MDIO_AN_REG_STATUS, &an_link);
			bnx2x_cl45_पढ़ो(bp, phy, MDIO_AN_DEVAD,
					MDIO_AN_REG_STATUS, &an_link);
			link_up |= (an_link & (1<<2));
		पूर्ण
		अगर (link_up && SINGLE_MEDIA_सूचीECT(params)) अणु
			u16 pd, gp_status4;
			अगर (phy->req_line_speed == SPEED_AUTO_NEG) अणु
				/* Check Autoneg complete */
				bnx2x_cl45_पढ़ो(bp, phy, MDIO_WC_DEVAD,
						MDIO_WC_REG_GP2_STATUS_GP_2_4,
						&gp_status4);
				अगर (gp_status4 & ((1<<12)<<lane))
					vars->link_status |=
					LINK_STATUS_AUTO_NEGOTIATE_COMPLETE;

				/* Check parallel detect used */
				bnx2x_cl45_पढ़ो(bp, phy, MDIO_WC_DEVAD,
						MDIO_WC_REG_PAR_DET_10G_STATUS,
						&pd);
				अगर (pd & (1<<15))
					vars->link_status |=
					LINK_STATUS_PARALLEL_DETECTION_USED;
			पूर्ण
			bnx2x_ext_phy_resolve_fc(phy, params, vars);
			vars->duplex = duplex;
		पूर्ण
	पूर्ण

	अगर ((vars->link_status & LINK_STATUS_AUTO_NEGOTIATE_COMPLETE) &&
	    SINGLE_MEDIA_सूचीECT(params)) अणु
		u16 val;

		bnx2x_cl45_पढ़ो(bp, phy, MDIO_AN_DEVAD,
				MDIO_AN_REG_LP_AUTO_NEG2, &val);

		अगर (val & MDIO_CL73_IEEEB1_AN_ADV2_ADVR_1000M_KX)
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_1000TFD_CAPABLE;
		अगर (val & (MDIO_CL73_IEEEB1_AN_ADV2_ADVR_10G_KX4 |
			   MDIO_CL73_IEEEB1_AN_ADV2_ADVR_10G_KR))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_10GXFD_CAPABLE;

		bnx2x_cl45_पढ़ो(bp, phy, MDIO_WC_DEVAD,
				MDIO_WC_REG_DIGITAL3_LP_UP1, &val);

		अगर (val & MDIO_OVER_1G_UP1_2_5G)
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_2500XFD_CAPABLE;
		अगर (val & (MDIO_OVER_1G_UP1_10G | MDIO_OVER_1G_UP1_10GH))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_10GXFD_CAPABLE;

	पूर्ण


	अगर (lane < 2) अणु
		bnx2x_cl45_पढ़ो(bp, phy, MDIO_WC_DEVAD,
				MDIO_WC_REG_GP2_STATUS_GP_2_2, &gp_speed);
	पूर्ण अन्यथा अणु
		bnx2x_cl45_पढ़ो(bp, phy, MDIO_WC_DEVAD,
				MDIO_WC_REG_GP2_STATUS_GP_2_3, &gp_speed);
	पूर्ण
	DP(NETIF_MSG_LINK, "lane %d gp_speed 0x%x\n", lane, gp_speed);

	अगर ((lane & 1) == 0)
		gp_speed <<= 8;
	gp_speed &= 0x3f00;
	link_up = !!link_up;

	rc = bnx2x_get_link_speed_duplex(phy, params, vars, link_up, gp_speed,
					 duplex);

	/* In हाल of KR link करोwn, start up the recovering procedure */
	अगर ((!link_up) && (phy->media_type == ETH_PHY_KR) &&
	    (!(phy->flags & FLAGS_WC_DUAL_MODE)))
		vars->rx_tx_asic_rst = MAX_KR_LINK_RETRY;

	DP(NETIF_MSG_LINK, "duplex %x  flow_ctrl 0x%x link_status 0x%x\n",
		   vars->duplex, vars->flow_ctrl, vars->link_status);
	वापस rc;
पूर्ण
अटल व्योम bnx2x_set_gmii_tx_driver(काष्ठा link_params *params)
अणु
	काष्ठा bnx2x *bp = params->bp;
	काष्ठा bnx2x_phy *phy = &params->phy[INT_PHY];
	u16 lp_up2;
	u16 tx_driver;
	u16 bank;

	/* Read precomp */
	CL22_RD_OVER_CL45(bp, phy,
			  MDIO_REG_BANK_OVER_1G,
			  MDIO_OVER_1G_LP_UP2, &lp_up2);

	/* Bits [10:7] at lp_up2, positioned at [15:12] */
	lp_up2 = (((lp_up2 & MDIO_OVER_1G_LP_UP2_PREEMPHASIS_MASK) >>
		   MDIO_OVER_1G_LP_UP2_PREEMPHASIS_SHIFT) <<
		  MDIO_TX0_TX_DRIVER_PREEMPHASIS_SHIFT);

	अगर (lp_up2 == 0)
		वापस;

	क्रम (bank = MDIO_REG_BANK_TX0; bank <= MDIO_REG_BANK_TX3;
	      bank += (MDIO_REG_BANK_TX1 - MDIO_REG_BANK_TX0)) अणु
		CL22_RD_OVER_CL45(bp, phy,
				  bank,
				  MDIO_TX0_TX_DRIVER, &tx_driver);

		/* Replace tx_driver bits [15:12] */
		अगर (lp_up2 !=
		    (tx_driver & MDIO_TX0_TX_DRIVER_PREEMPHASIS_MASK)) अणु
			tx_driver &= ~MDIO_TX0_TX_DRIVER_PREEMPHASIS_MASK;
			tx_driver |= lp_up2;
			CL22_WR_OVER_CL45(bp, phy,
					  bank,
					  MDIO_TX0_TX_DRIVER, tx_driver);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_emac_program(काष्ठा link_params *params,
			      काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u8 port = params->port;
	u16 mode = 0;

	DP(NETIF_MSG_LINK, "setting link speed & duplex\n");
	bnx2x_bits_dis(bp, GRCBASE_EMAC0 + port*0x400 +
		       EMAC_REG_EMAC_MODE,
		       (EMAC_MODE_25G_MODE |
			EMAC_MODE_PORT_MII_10M |
			EMAC_MODE_HALF_DUPLEX));
	चयन (vars->line_speed) अणु
	हाल SPEED_10:
		mode |= EMAC_MODE_PORT_MII_10M;
		अवरोध;

	हाल SPEED_100:
		mode |= EMAC_MODE_PORT_MII;
		अवरोध;

	हाल SPEED_1000:
		mode |= EMAC_MODE_PORT_GMII;
		अवरोध;

	हाल SPEED_2500:
		mode |= (EMAC_MODE_25G_MODE | EMAC_MODE_PORT_GMII);
		अवरोध;

	शेष:
		/* 10G not valid क्रम EMAC */
		DP(NETIF_MSG_LINK, "Invalid line_speed 0x%x\n",
			   vars->line_speed);
		वापस -EINVAL;
	पूर्ण

	अगर (vars->duplex == DUPLEX_HALF)
		mode |= EMAC_MODE_HALF_DUPLEX;
	bnx2x_bits_en(bp,
		      GRCBASE_EMAC0 + port*0x400 + EMAC_REG_EMAC_MODE,
		      mode);

	bnx2x_set_led(params, vars, LED_MODE_OPER, vars->line_speed);
	वापस 0;
पूर्ण

अटल व्योम bnx2x_set_preemphasis(काष्ठा bnx2x_phy *phy,
				  काष्ठा link_params *params)
अणु

	u16 bank, i = 0;
	काष्ठा bnx2x *bp = params->bp;

	क्रम (bank = MDIO_REG_BANK_RX0, i = 0; bank <= MDIO_REG_BANK_RX3;
	      bank += (MDIO_REG_BANK_RX1-MDIO_REG_BANK_RX0), i++) अणु
			CL22_WR_OVER_CL45(bp, phy,
					  bank,
					  MDIO_RX0_RX_EQ_BOOST,
					  phy->rx_preemphasis[i]);
	पूर्ण

	क्रम (bank = MDIO_REG_BANK_TX0, i = 0; bank <= MDIO_REG_BANK_TX3;
		      bank += (MDIO_REG_BANK_TX1 - MDIO_REG_BANK_TX0), i++) अणु
			CL22_WR_OVER_CL45(bp, phy,
					  bank,
					  MDIO_TX0_TX_DRIVER,
					  phy->tx_preemphasis[i]);
	पूर्ण
पूर्ण

अटल व्योम bnx2x_xgxs_config_init(काष्ठा bnx2x_phy *phy,
				   काष्ठा link_params *params,
				   काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u8 enable_cl73 = (SINGLE_MEDIA_सूचीECT(params) ||
			  (params->loopback_mode == LOOPBACK_XGXS));
	अगर (!(vars->phy_flags & PHY_SGMII_FLAG)) अणु
		अगर (SINGLE_MEDIA_सूचीECT(params) &&
		    (params->feature_config_flags &
		     FEATURE_CONFIG_OVERRIDE_PREEMPHASIS_ENABLED))
			bnx2x_set_preemphasis(phy, params);

		/* Forced speed requested? */
		अगर (vars->line_speed != SPEED_AUTO_NEG ||
		    (SINGLE_MEDIA_सूचीECT(params) &&
		     params->loopback_mode == LOOPBACK_EXT)) अणु
			DP(NETIF_MSG_LINK, "not SGMII, no AN\n");

			/* Disable स्वतःneg */
			bnx2x_set_स्वतःneg(phy, params, vars, 0);

			/* Program speed and duplex */
			bnx2x_program_serdes(phy, params, vars);

		पूर्ण अन्यथा अणु /* AN_mode */
			DP(NETIF_MSG_LINK, "not SGMII, AN\n");

			/* AN enabled */
			bnx2x_set_brcm_cl37_advertisement(phy, params);

			/* Program duplex & छोड़ो advertisement (क्रम aneg) */
			bnx2x_set_ieee_aneg_advertisement(phy, params,
							  vars->ieee_fc);

			/* Enable स्वतःneg */
			bnx2x_set_स्वतःneg(phy, params, vars, enable_cl73);

			/* Enable and restart AN */
			bnx2x_restart_स्वतःneg(phy, params, enable_cl73);
		पूर्ण

	पूर्ण अन्यथा अणु /* SGMII mode */
		DP(NETIF_MSG_LINK, "SGMII\n");

		bnx2x_initialize_sgmii_process(phy, params, vars);
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_prepare_xgxs(काष्ठा bnx2x_phy *phy,
			  काष्ठा link_params *params,
			  काष्ठा link_vars *vars)
अणु
	पूर्णांक rc;
	vars->phy_flags |= PHY_XGXS_FLAG;
	अगर ((phy->req_line_speed &&
	     ((phy->req_line_speed == SPEED_100) ||
	      (phy->req_line_speed == SPEED_10))) ||
	    (!phy->req_line_speed &&
	     (phy->speed_cap_mask >=
	      PORT_HW_CFG_SPEED_CAPABILITY_D0_10M_FULL) &&
	     (phy->speed_cap_mask <
	      PORT_HW_CFG_SPEED_CAPABILITY_D0_1G)) ||
	    (phy->type == PORT_HW_CFG_SERDES_EXT_PHY_TYPE_सूचीECT_SD))
		vars->phy_flags |= PHY_SGMII_FLAG;
	अन्यथा
		vars->phy_flags &= ~PHY_SGMII_FLAG;

	bnx2x_calc_ieee_aneg_adv(phy, params, &vars->ieee_fc);
	bnx2x_set_aer_mmd(params, phy);
	अगर (phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_सूचीECT)
		bnx2x_set_master_ln(params, phy);

	rc = bnx2x_reset_unicore(params, phy, 0);
	/* Reset the SerDes and रुको क्रम reset bit वापस low */
	अगर (rc)
		वापस rc;

	bnx2x_set_aer_mmd(params, phy);
	/* Setting the masterLn_def again after the reset */
	अगर (phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_सूचीECT) अणु
		bnx2x_set_master_ln(params, phy);
		bnx2x_set_swap_lanes(params, phy);
	पूर्ण

	वापस rc;
पूर्ण

अटल u16 bnx2x_रुको_reset_complete(काष्ठा bnx2x *bp,
				     काष्ठा bnx2x_phy *phy,
				     काष्ठा link_params *params)
अणु
	u16 cnt, ctrl;
	/* Wait क्रम soft reset to get cleared up to 1 sec */
	क्रम (cnt = 0; cnt < 1000; cnt++) अणु
		अगर (phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM54618SE)
			bnx2x_cl22_पढ़ो(bp, phy,
				MDIO_PMA_REG_CTRL, &ctrl);
		अन्यथा
			bnx2x_cl45_पढ़ो(bp, phy,
				MDIO_PMA_DEVAD,
				MDIO_PMA_REG_CTRL, &ctrl);
		अगर (!(ctrl & (1<<15)))
			अवरोध;
		usleep_range(1000, 2000);
	पूर्ण

	अगर (cnt == 1000)
		netdev_err(bp->dev,  "Warning: PHY was not initialized,"
				      " Port %d\n",
			 params->port);
	DP(NETIF_MSG_LINK, "control reg 0x%x (after %d ms)\n", ctrl, cnt);
	वापस cnt;
पूर्ण

अटल व्योम bnx2x_link_पूर्णांक_enable(काष्ठा link_params *params)
अणु
	u8 port = params->port;
	u32 mask;
	काष्ठा bnx2x *bp = params->bp;

	/* Setting the status to report on link up क्रम either XGXS or SerDes */
	अगर (CHIP_IS_E3(bp)) अणु
		mask = NIG_MASK_XGXS0_LINK_STATUS;
		अगर (!(SINGLE_MEDIA_सूचीECT(params)))
			mask |= NIG_MASK_MI_INT;
	पूर्ण अन्यथा अगर (params->चयन_cfg == SWITCH_CFG_10G) अणु
		mask = (NIG_MASK_XGXS0_LINK10G |
			NIG_MASK_XGXS0_LINK_STATUS);
		DP(NETIF_MSG_LINK, "enabled XGXS interrupt\n");
		अगर (!(SINGLE_MEDIA_सूचीECT(params)) &&
			params->phy[INT_PHY].type !=
				PORT_HW_CFG_XGXS_EXT_PHY_TYPE_FAILURE) अणु
			mask |= NIG_MASK_MI_INT;
			DP(NETIF_MSG_LINK, "enabled external phy int\n");
		पूर्ण

	पूर्ण अन्यथा अणु /* SerDes */
		mask = NIG_MASK_SERDES0_LINK_STATUS;
		DP(NETIF_MSG_LINK, "enabled SerDes interrupt\n");
		अगर (!(SINGLE_MEDIA_सूचीECT(params)) &&
			params->phy[INT_PHY].type !=
				PORT_HW_CFG_SERDES_EXT_PHY_TYPE_NOT_CONN) अणु
			mask |= NIG_MASK_MI_INT;
			DP(NETIF_MSG_LINK, "enabled external phy int\n");
		पूर्ण
	पूर्ण
	bnx2x_bits_en(bp,
		      NIG_REG_MASK_INTERRUPT_PORT0 + port*4,
		      mask);

	DP(NETIF_MSG_LINK, "port %x, is_xgxs %x, int_status 0x%x\n", port,
		 (params->चयन_cfg == SWITCH_CFG_10G),
		 REG_RD(bp, NIG_REG_STATUS_INTERRUPT_PORT0 + port*4));
	DP(NETIF_MSG_LINK, " int_mask 0x%x, MI_INT %x, SERDES_LINK %x\n",
		 REG_RD(bp, NIG_REG_MASK_INTERRUPT_PORT0 + port*4),
		 REG_RD(bp, NIG_REG_EMAC0_STATUS_MISC_MI_INT + port*0x18),
		 REG_RD(bp, NIG_REG_SERDES0_STATUS_LINK_STATUS+port*0x3c));
	DP(NETIF_MSG_LINK, " 10G %x, XGXS_LINK %x\n",
	   REG_RD(bp, NIG_REG_XGXS0_STATUS_LINK10G + port*0x68),
	   REG_RD(bp, NIG_REG_XGXS0_STATUS_LINK_STATUS + port*0x68));
पूर्ण

अटल व्योम bnx2x_rearm_latch_संकेत(काष्ठा bnx2x *bp, u8 port,
				     u8 exp_mi_पूर्णांक)
अणु
	u32 latch_status = 0;

	/* Disable the MI INT ( बाह्यal phy पूर्णांक ) by writing 1 to the
	 * status रेजिस्टर. Link करोwn indication is high-active-संकेत,
	 * so in this हाल we need to ग_लिखो the status to clear the XOR
	 */
	/* Read Latched संकेतs */
	latch_status = REG_RD(bp,
				    NIG_REG_LATCH_STATUS_0 + port*8);
	DP(NETIF_MSG_LINK, "latch_status = 0x%x\n", latch_status);
	/* Handle only those with latched-संकेत=up.*/
	अगर (exp_mi_पूर्णांक)
		bnx2x_bits_en(bp,
			      NIG_REG_STATUS_INTERRUPT_PORT0
			      + port*4,
			      NIG_STATUS_EMAC0_MI_INT);
	अन्यथा
		bnx2x_bits_dis(bp,
			       NIG_REG_STATUS_INTERRUPT_PORT0
			       + port*4,
			       NIG_STATUS_EMAC0_MI_INT);

	अगर (latch_status & 1) अणु

		/* For all latched-संकेत=up : Re-Arm Latch संकेतs */
		REG_WR(bp, NIG_REG_LATCH_STATUS_0 + port*8,
		       (latch_status & 0xfffe) | (latch_status & 1));
	पूर्ण
	/* For all latched-संकेत=up,Write original_संकेत to status */
पूर्ण

अटल व्योम bnx2x_link_पूर्णांक_ack(काष्ठा link_params *params,
			       काष्ठा link_vars *vars, u8 is_10g_plus)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u8 port = params->port;
	u32 mask;
	/* First reset all status we assume only one line will be
	 * change at a समय
	 */
	bnx2x_bits_dis(bp, NIG_REG_STATUS_INTERRUPT_PORT0 + port*4,
		       (NIG_STATUS_XGXS0_LINK10G |
			NIG_STATUS_XGXS0_LINK_STATUS |
			NIG_STATUS_SERDES0_LINK_STATUS));
	अगर (vars->phy_link_up) अणु
		अगर (USES_WARPCORE(bp))
			mask = NIG_STATUS_XGXS0_LINK_STATUS;
		अन्यथा अणु
			अगर (is_10g_plus)
				mask = NIG_STATUS_XGXS0_LINK10G;
			अन्यथा अगर (params->चयन_cfg == SWITCH_CFG_10G) अणु
				/* Disable the link पूर्णांकerrupt by writing 1 to
				 * the relevant lane in the status रेजिस्टर
				 */
				u32 ser_lane =
					((params->lane_config &
				    PORT_HW_CFG_LANE_SWAP_CFG_MASTER_MASK) >>
				    PORT_HW_CFG_LANE_SWAP_CFG_MASTER_SHIFT);
				mask = ((1 << ser_lane) <<
				       NIG_STATUS_XGXS0_LINK_STATUS_SIZE);
			पूर्ण अन्यथा
				mask = NIG_STATUS_SERDES0_LINK_STATUS;
		पूर्ण
		DP(NETIF_MSG_LINK, "Ack link up interrupt with mask 0x%x\n",
			       mask);
		bnx2x_bits_en(bp,
			      NIG_REG_STATUS_INTERRUPT_PORT0 + port*4,
			      mask);
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_null_क्रमmat_ver(u32 spirom_ver, u8 *str, u16 *len)
अणु
	str[0] = '\0';
	(*len)--;
	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_क्रमmat_ver(u32 num, u8 *str, u16 *len)
अणु
	u16 ret;

	अगर (*len < 10) अणु
		/* Need more than 10अक्षरs क्रम this क्रमmat */
		bnx2x_null_क्रमmat_ver(num, str, len);
		वापस -EINVAL;
	पूर्ण

	ret = scnम_लिखो(str, *len, "%hx.%hx", num >> 16, num);
	*len -= ret;
	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_3_seq_क्रमmat_ver(u32 num, u8 *str, u16 *len)
अणु
	u16 ret;

	अगर (*len < 10) अणु
		/* Need more than 10अक्षरs क्रम this क्रमmat */
		bnx2x_null_क्रमmat_ver(num, str, len);
		वापस -EINVAL;
	पूर्ण

	ret = scnम_लिखो(str, *len, "%hhx.%hhx.%hhx", num >> 16, num >> 8, num);
	*len -= ret;
	वापस 0;
पूर्ण

पूर्णांक bnx2x_get_ext_phy_fw_version(काष्ठा link_params *params, u8 *version,
				 u16 len)
अणु
	काष्ठा bnx2x *bp;
	u32 spirom_ver = 0;
	पूर्णांक status = 0;
	u8 *ver_p = version;
	u16 reमुख्य_len = len;
	अगर (version == शून्य || params == शून्य)
		वापस -EINVAL;
	bp = params->bp;

	/* Extract first बाह्यal phy*/
	version[0] = '\0';
	spirom_ver = REG_RD(bp, params->phy[EXT_PHY1].ver_addr);

	अगर (params->phy[EXT_PHY1].क्रमmat_fw_ver) अणु
		status |= params->phy[EXT_PHY1].क्रमmat_fw_ver(spirom_ver,
							      ver_p,
							      &reमुख्य_len);
		ver_p += (len - reमुख्य_len);
	पूर्ण
	अगर ((params->num_phys == MAX_PHYS) &&
	    (params->phy[EXT_PHY2].ver_addr != 0)) अणु
		spirom_ver = REG_RD(bp, params->phy[EXT_PHY2].ver_addr);
		अगर (params->phy[EXT_PHY2].क्रमmat_fw_ver) अणु
			*ver_p = '/';
			ver_p++;
			reमुख्य_len--;
			status |= params->phy[EXT_PHY2].क्रमmat_fw_ver(
				spirom_ver,
				ver_p,
				&reमुख्य_len);
			ver_p = version + (len - reमुख्य_len);
		पूर्ण
	पूर्ण
	*ver_p = '\0';
	वापस status;
पूर्ण

अटल व्योम bnx2x_set_xgxs_loopback(काष्ठा bnx2x_phy *phy,
				    काष्ठा link_params *params)
अणु
	u8 port = params->port;
	काष्ठा bnx2x *bp = params->bp;

	अगर (phy->req_line_speed != SPEED_1000) अणु
		u32 md_devad = 0;

		DP(NETIF_MSG_LINK, "XGXS 10G loopback enable\n");

		अगर (!CHIP_IS_E3(bp)) अणु
			/* Change the uni_phy_addr in the nig */
			md_devad = REG_RD(bp, (NIG_REG_XGXS0_CTRL_MD_DEVAD +
					       port*0x18));

			REG_WR(bp, NIG_REG_XGXS0_CTRL_MD_DEVAD + port*0x18,
			       0x5);
		पूर्ण

		bnx2x_cl45_ग_लिखो(bp, phy,
				 5,
				 (MDIO_REG_BANK_AER_BLOCK +
				  (MDIO_AER_BLOCK_AER_REG & 0xf)),
				 0x2800);

		bnx2x_cl45_ग_लिखो(bp, phy,
				 5,
				 (MDIO_REG_BANK_CL73_IEEEB0 +
				  (MDIO_CL73_IEEEB0_CL73_AN_CONTROL & 0xf)),
				 0x6041);
		msleep(200);
		/* Set aer mmd back */
		bnx2x_set_aer_mmd(params, phy);

		अगर (!CHIP_IS_E3(bp)) अणु
			/* And md_devad */
			REG_WR(bp, NIG_REG_XGXS0_CTRL_MD_DEVAD + port*0x18,
			       md_devad);
		पूर्ण
	पूर्ण अन्यथा अणु
		u16 mii_ctrl;
		DP(NETIF_MSG_LINK, "XGXS 1G loopback enable\n");
		bnx2x_cl45_पढ़ो(bp, phy, 5,
				(MDIO_REG_BANK_COMBO_IEEE0 +
				(MDIO_COMBO_IEEE0_MII_CONTROL & 0xf)),
				&mii_ctrl);
		bnx2x_cl45_ग_लिखो(bp, phy, 5,
				 (MDIO_REG_BANK_COMBO_IEEE0 +
				 (MDIO_COMBO_IEEE0_MII_CONTROL & 0xf)),
				 mii_ctrl |
				 MDIO_COMBO_IEEO_MII_CONTROL_LOOPBACK);
	पूर्ण
पूर्ण

पूर्णांक bnx2x_set_led(काष्ठा link_params *params,
		  काष्ठा link_vars *vars, u8 mode, u32 speed)
अणु
	u8 port = params->port;
	u16 hw_led_mode = params->hw_led_mode;
	पूर्णांक rc = 0;
	u8 phy_idx;
	u32 पंचांगp;
	u32 emac_base = port ? GRCBASE_EMAC1 : GRCBASE_EMAC0;
	काष्ठा bnx2x *bp = params->bp;
	DP(NETIF_MSG_LINK, "bnx2x_set_led: port %x, mode %d\n", port, mode);
	DP(NETIF_MSG_LINK, "speed 0x%x, hw_led_mode 0x%x\n",
		 speed, hw_led_mode);
	/* In हाल */
	क्रम (phy_idx = EXT_PHY1; phy_idx < MAX_PHYS; phy_idx++) अणु
		अगर (params->phy[phy_idx].set_link_led) अणु
			params->phy[phy_idx].set_link_led(
				&params->phy[phy_idx], params, mode);
		पूर्ण
	पूर्ण

	चयन (mode) अणु
	हाल LED_MODE_FRONT_PANEL_OFF:
	हाल LED_MODE_OFF:
		REG_WR(bp, NIG_REG_LED_10G_P0 + port*4, 0);
		REG_WR(bp, NIG_REG_LED_MODE_P0 + port*4,
		       SHARED_HW_CFG_LED_MAC1);

		पंचांगp = EMAC_RD(bp, EMAC_REG_EMAC_LED);
		अगर (params->phy[EXT_PHY1].type ==
			PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM54618SE)
			पंचांगp &= ~(EMAC_LED_1000MB_OVERRIDE |
				EMAC_LED_100MB_OVERRIDE |
				EMAC_LED_10MB_OVERRIDE);
		अन्यथा
			पंचांगp |= EMAC_LED_OVERRIDE;

		EMAC_WR(bp, EMAC_REG_EMAC_LED, पंचांगp);
		अवरोध;

	हाल LED_MODE_OPER:
		/* For all other phys, OPER mode is same as ON, so in हाल
		 * link is करोwn, करो nothing
		 */
		अगर (!vars->link_up)
			अवरोध;
		fallthrough;
	हाल LED_MODE_ON:
		अगर (((params->phy[EXT_PHY1].type ==
			  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8727) ||
			 (params->phy[EXT_PHY1].type ==
			  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8722)) &&
		    CHIP_IS_E2(bp) && params->num_phys == 2) अणु
			/* This is a work-around क्रम E2+8727 Configurations */
			अगर (mode == LED_MODE_ON ||
				speed == SPEED_10000)अणु
				REG_WR(bp, NIG_REG_LED_MODE_P0 + port*4, 0);
				REG_WR(bp, NIG_REG_LED_10G_P0 + port*4, 1);

				पंचांगp = EMAC_RD(bp, EMAC_REG_EMAC_LED);
				EMAC_WR(bp, EMAC_REG_EMAC_LED,
					(पंचांगp | EMAC_LED_OVERRIDE));
				/* Return here without enabling traffic
				 * LED blink and setting rate in ON mode.
				 * In oper mode, enabling LED blink
				 * and setting rate is needed.
				 */
				अगर (mode == LED_MODE_ON)
					वापस rc;
			पूर्ण
		पूर्ण अन्यथा अगर (SINGLE_MEDIA_सूचीECT(params)) अणु
			/* This is a work-around क्रम HW issue found when link
			 * is up in CL73
			 */
			अगर ((!CHIP_IS_E3(bp)) ||
			    (CHIP_IS_E3(bp) &&
			     mode == LED_MODE_ON))
				REG_WR(bp, NIG_REG_LED_10G_P0 + port*4, 1);

			अगर (CHIP_IS_E1x(bp) ||
			    CHIP_IS_E2(bp) ||
			    (mode == LED_MODE_ON))
				REG_WR(bp, NIG_REG_LED_MODE_P0 + port*4, 0);
			अन्यथा
				REG_WR(bp, NIG_REG_LED_MODE_P0 + port*4,
				       hw_led_mode);
		पूर्ण अन्यथा अगर ((params->phy[EXT_PHY1].type ==
			    PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM54618SE) &&
			   (mode == LED_MODE_ON)) अणु
			REG_WR(bp, NIG_REG_LED_MODE_P0 + port*4, 0);
			पंचांगp = EMAC_RD(bp, EMAC_REG_EMAC_LED);
			EMAC_WR(bp, EMAC_REG_EMAC_LED, पंचांगp |
				EMAC_LED_OVERRIDE | EMAC_LED_1000MB_OVERRIDE);
			/* Break here; otherwise, it'll disable the
			 * पूर्णांकended override.
			 */
			अवरोध;
		पूर्ण अन्यथा अणु
			u32 nig_led_mode = ((params->hw_led_mode <<
					     SHARED_HW_CFG_LED_MODE_SHIFT) ==
					    SHARED_HW_CFG_LED_EXTPHY2) ?
				(SHARED_HW_CFG_LED_PHY1 >>
				 SHARED_HW_CFG_LED_MODE_SHIFT) : hw_led_mode;
			REG_WR(bp, NIG_REG_LED_MODE_P0 + port*4,
			       nig_led_mode);
		पूर्ण

		REG_WR(bp, NIG_REG_LED_CONTROL_OVERRIDE_TRAFFIC_P0 + port*4, 0);
		/* Set blinking rate to ~15.9Hz */
		अगर (CHIP_IS_E3(bp))
			REG_WR(bp, NIG_REG_LED_CONTROL_BLINK_RATE_P0 + port*4,
			       LED_BLINK_RATE_VAL_E3);
		अन्यथा
			REG_WR(bp, NIG_REG_LED_CONTROL_BLINK_RATE_P0 + port*4,
			       LED_BLINK_RATE_VAL_E1X_E2);
		REG_WR(bp, NIG_REG_LED_CONTROL_BLINK_RATE_ENA_P0 +
		       port*4, 1);
		पंचांगp = EMAC_RD(bp, EMAC_REG_EMAC_LED);
		EMAC_WR(bp, EMAC_REG_EMAC_LED,
			(पंचांगp & (~EMAC_LED_OVERRIDE)));

		अगर (CHIP_IS_E1(bp) &&
		    ((speed == SPEED_2500) ||
		     (speed == SPEED_1000) ||
		     (speed == SPEED_100) ||
		     (speed == SPEED_10))) अणु
			/* For speeds less than 10G LED scheme is dअगरferent */
			REG_WR(bp, NIG_REG_LED_CONTROL_OVERRIDE_TRAFFIC_P0
			       + port*4, 1);
			REG_WR(bp, NIG_REG_LED_CONTROL_TRAFFIC_P0 +
			       port*4, 0);
			REG_WR(bp, NIG_REG_LED_CONTROL_BLINK_TRAFFIC_P0 +
			       port*4, 1);
		पूर्ण
		अवरोध;

	शेष:
		rc = -EINVAL;
		DP(NETIF_MSG_LINK, "bnx2x_set_led: Invalid led mode %d\n",
			 mode);
		अवरोध;
	पूर्ण
	वापस rc;

पूर्ण

/* This function comes to reflect the actual link state पढ़ो सूचीECTLY from the
 * HW
 */
पूर्णांक bnx2x_test_link(काष्ठा link_params *params, काष्ठा link_vars *vars,
		    u8 is_serdes)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 gp_status = 0, phy_index = 0;
	u8 ext_phy_link_up = 0, serdes_phy_type;
	काष्ठा link_vars temp_vars;
	काष्ठा bnx2x_phy *पूर्णांक_phy = &params->phy[INT_PHY];

	अगर (CHIP_IS_E3(bp)) अणु
		u16 link_up;
		अगर (params->req_line_speed[LINK_CONFIG_IDX(INT_PHY)]
		    > SPEED_10000) अणु
			/* Check 20G link */
			bnx2x_cl45_पढ़ो(bp, पूर्णांक_phy, MDIO_WC_DEVAD,
					1, &link_up);
			bnx2x_cl45_पढ़ो(bp, पूर्णांक_phy, MDIO_WC_DEVAD,
					1, &link_up);
			link_up &= (1<<2);
		पूर्ण अन्यथा अणु
			/* Check 10G link and below*/
			u8 lane = bnx2x_get_warpcore_lane(पूर्णांक_phy, params);
			bnx2x_cl45_पढ़ो(bp, पूर्णांक_phy, MDIO_WC_DEVAD,
					MDIO_WC_REG_GP2_STATUS_GP_2_1,
					&gp_status);
			gp_status = ((gp_status >> 8) & 0xf) |
				((gp_status >> 12) & 0xf);
			link_up = gp_status & (1 << lane);
		पूर्ण
		अगर (!link_up)
			वापस -ESRCH;
	पूर्ण अन्यथा अणु
		CL22_RD_OVER_CL45(bp, पूर्णांक_phy,
			  MDIO_REG_BANK_GP_STATUS,
			  MDIO_GP_STATUS_TOP_AN_STATUS1,
			  &gp_status);
		/* Link is up only अगर both local phy and बाह्यal phy are up */
		अगर (!(gp_status & MDIO_GP_STATUS_TOP_AN_STATUS1_LINK_STATUS))
			वापस -ESRCH;
	पूर्ण
	/* In XGXS loopback mode, करो not check बाह्यal PHY */
	अगर (params->loopback_mode == LOOPBACK_XGXS)
		वापस 0;

	चयन (params->num_phys) अणु
	हाल 1:
		/* No बाह्यal PHY */
		वापस 0;
	हाल 2:
		ext_phy_link_up = params->phy[EXT_PHY1].पढ़ो_status(
			&params->phy[EXT_PHY1],
			params, &temp_vars);
		अवरोध;
	हाल 3: /* Dual Media */
		क्रम (phy_index = EXT_PHY1; phy_index < params->num_phys;
		      phy_index++) अणु
			serdes_phy_type = ((params->phy[phy_index].media_type ==
					    ETH_PHY_SFPP_10G_FIBER) ||
					   (params->phy[phy_index].media_type ==
					    ETH_PHY_SFP_1G_FIBER) ||
					   (params->phy[phy_index].media_type ==
					    ETH_PHY_XFP_FIBER) ||
					   (params->phy[phy_index].media_type ==
					    ETH_PHY_DA_TWINAX));

			अगर (is_serdes != serdes_phy_type)
				जारी;
			अगर (params->phy[phy_index].पढ़ो_status) अणु
				ext_phy_link_up |=
					params->phy[phy_index].पढ़ो_status(
						&params->phy[phy_index],
						params, &temp_vars);
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
	अगर (ext_phy_link_up)
		वापस 0;
	वापस -ESRCH;
पूर्ण

अटल पूर्णांक bnx2x_link_initialize(काष्ठा link_params *params,
				 काष्ठा link_vars *vars)
अणु
	u8 phy_index, non_ext_phy;
	काष्ठा bnx2x *bp = params->bp;
	/* In हाल of बाह्यal phy existence, the line speed would be the
	 * line speed linked up by the बाह्यal phy. In हाल it is direct
	 * only, then the line_speed during initialization will be
	 * equal to the req_line_speed
	 */
	vars->line_speed = params->phy[INT_PHY].req_line_speed;

	/* Initialize the पूर्णांकernal phy in हाल this is a direct board
	 * (no बाह्यal phys), or this board has बाह्यal phy which requires
	 * to first.
	 */
	अगर (!USES_WARPCORE(bp))
		bnx2x_prepare_xgxs(&params->phy[INT_PHY], params, vars);
	/* init ext phy and enable link state पूर्णांक */
	non_ext_phy = (SINGLE_MEDIA_सूचीECT(params) ||
		       (params->loopback_mode == LOOPBACK_XGXS));

	अगर (non_ext_phy ||
	    (params->phy[EXT_PHY1].flags & FLAGS_INIT_XGXS_FIRST) ||
	    (params->loopback_mode == LOOPBACK_EXT_PHY)) अणु
		काष्ठा bnx2x_phy *phy = &params->phy[INT_PHY];
		अगर (vars->line_speed == SPEED_AUTO_NEG &&
		    (CHIP_IS_E1x(bp) ||
		     CHIP_IS_E2(bp)))
			bnx2x_set_parallel_detection(phy, params);
		अगर (params->phy[INT_PHY].config_init)
			params->phy[INT_PHY].config_init(phy, params, vars);
	पूर्ण

	/* Re-पढ़ो this value in हाल it was changed inside config_init due to
	 * limitations of optic module
	 */
	vars->line_speed = params->phy[INT_PHY].req_line_speed;

	/* Init बाह्यal phy*/
	अगर (non_ext_phy) अणु
		अगर (params->phy[INT_PHY].supported &
		    SUPPORTED_FIBRE)
			vars->link_status |= LINK_STATUS_SERDES_LINK;
	पूर्ण अन्यथा अणु
		क्रम (phy_index = EXT_PHY1; phy_index < params->num_phys;
		      phy_index++) अणु
			/* No need to initialize second phy in हाल of first
			 * phy only selection. In हाल of second phy, we करो
			 * need to initialize the first phy, since they are
			 * connected.
			 */
			अगर (params->phy[phy_index].supported &
			    SUPPORTED_FIBRE)
				vars->link_status |= LINK_STATUS_SERDES_LINK;

			अगर (phy_index == EXT_PHY2 &&
			    (bnx2x_phy_selection(params) ==
			     PORT_HW_CFG_PHY_SELECTION_FIRST_PHY)) अणु
				DP(NETIF_MSG_LINK,
				   "Not initializing second phy\n");
				जारी;
			पूर्ण
			params->phy[phy_index].config_init(
				&params->phy[phy_index],
				params, vars);
		पूर्ण
	पूर्ण
	/* Reset the पूर्णांकerrupt indication after phy was initialized */
	bnx2x_bits_dis(bp, NIG_REG_STATUS_INTERRUPT_PORT0 +
		       params->port*4,
		       (NIG_STATUS_XGXS0_LINK10G |
			NIG_STATUS_XGXS0_LINK_STATUS |
			NIG_STATUS_SERDES0_LINK_STATUS |
			NIG_MASK_MI_INT));
	वापस 0;
पूर्ण

अटल व्योम bnx2x_पूर्णांक_link_reset(काष्ठा bnx2x_phy *phy,
				 काष्ठा link_params *params)
अणु
	/* Reset the SerDes/XGXS */
	REG_WR(params->bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_3_CLEAR,
	       (0x1ff << (params->port*16)));
पूर्ण

अटल व्योम bnx2x_common_ext_link_reset(काष्ठा bnx2x_phy *phy,
					काष्ठा link_params *params)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u8 gpio_port;
	/* HW reset */
	अगर (CHIP_IS_E2(bp))
		gpio_port = BP_PATH(bp);
	अन्यथा
		gpio_port = params->port;
	bnx2x_set_gpio(bp, MISC_REGISTERS_GPIO_1,
		       MISC_REGISTERS_GPIO_OUTPUT_LOW,
		       gpio_port);
	bnx2x_set_gpio(bp, MISC_REGISTERS_GPIO_2,
		       MISC_REGISTERS_GPIO_OUTPUT_LOW,
		       gpio_port);
	DP(NETIF_MSG_LINK, "reset external PHY\n");
पूर्ण

अटल पूर्णांक bnx2x_update_link_करोwn(काष्ठा link_params *params,
				  काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u8 port = params->port;

	DP(NETIF_MSG_LINK, "Port %x: Link is down\n", port);
	bnx2x_set_led(params, vars, LED_MODE_OFF, 0);
	vars->phy_flags &= ~PHY_PHYSICAL_LINK_FLAG;
	/* Indicate no mac active */
	vars->mac_type = MAC_TYPE_NONE;

	/* Update shared memory */
	vars->link_status &= ~LINK_UPDATE_MASK;
	vars->line_speed = 0;
	bnx2x_update_mng(params, vars->link_status);

	/* Activate nig drain */
	REG_WR(bp, NIG_REG_EGRESS_DRAIN0_MODE + port*4, 1);

	/* Disable emac */
	अगर (!CHIP_IS_E3(bp))
		REG_WR(bp, NIG_REG_NIG_EMAC0_EN + port*4, 0);

	usleep_range(10000, 20000);
	/* Reset BigMac/Xmac */
	अगर (CHIP_IS_E1x(bp) ||
	    CHIP_IS_E2(bp))
		bnx2x_set_bmac_rx(bp, params->chip_id, params->port, 0);

	अगर (CHIP_IS_E3(bp)) अणु
		/* Prevent LPI Generation by chip */
		REG_WR(bp, MISC_REG_CPMU_LP_FW_ENABLE_P0 + (params->port << 2),
		       0);
		REG_WR(bp, MISC_REG_CPMU_LP_MASK_ENT_P0 + (params->port << 2),
		       0);
		vars->eee_status &= ~(SHMEM_EEE_LP_ADV_STATUS_MASK |
				      SHMEM_EEE_ACTIVE_BIT);

		bnx2x_update_mng_eee(params, vars->eee_status);
		bnx2x_set_xmac_rxtx(params, 0);
		bnx2x_set_umac_rxtx(params, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_update_link_up(काष्ठा link_params *params,
				काष्ठा link_vars *vars,
				u8 link_10g)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u8 phy_idx, port = params->port;
	पूर्णांक rc = 0;

	vars->link_status |= (LINK_STATUS_LINK_UP |
			      LINK_STATUS_PHYSICAL_LINK_FLAG);
	vars->phy_flags |= PHY_PHYSICAL_LINK_FLAG;

	अगर (vars->flow_ctrl & BNX2X_FLOW_CTRL_TX)
		vars->link_status |=
			LINK_STATUS_TX_FLOW_CONTROL_ENABLED;

	अगर (vars->flow_ctrl & BNX2X_FLOW_CTRL_RX)
		vars->link_status |=
			LINK_STATUS_RX_FLOW_CONTROL_ENABLED;
	अगर (USES_WARPCORE(bp)) अणु
		अगर (link_10g) अणु
			अगर (bnx2x_xmac_enable(params, vars, 0) ==
			    -ESRCH) अणु
				DP(NETIF_MSG_LINK, "Found errors on XMAC\n");
				vars->link_up = 0;
				vars->phy_flags |= PHY_HALF_OPEN_CONN_FLAG;
				vars->link_status &= ~LINK_STATUS_LINK_UP;
			पूर्ण
		पूर्ण अन्यथा
			bnx2x_umac_enable(params, vars, 0);
		bnx2x_set_led(params, vars,
			      LED_MODE_OPER, vars->line_speed);

		अगर ((vars->eee_status & SHMEM_EEE_ACTIVE_BIT) &&
		    (vars->eee_status & SHMEM_EEE_LPI_REQUESTED_BIT)) अणु
			DP(NETIF_MSG_LINK, "Enabling LPI assertion\n");
			REG_WR(bp, MISC_REG_CPMU_LP_FW_ENABLE_P0 +
			       (params->port << 2), 1);
			REG_WR(bp, MISC_REG_CPMU_LP_DR_ENABLE, 1);
			REG_WR(bp, MISC_REG_CPMU_LP_MASK_ENT_P0 +
			       (params->port << 2), 0xfc20);
		पूर्ण
	पूर्ण
	अगर ((CHIP_IS_E1x(bp) ||
	     CHIP_IS_E2(bp))) अणु
		अगर (link_10g) अणु
			अगर (bnx2x_bmac_enable(params, vars, 0, 1) ==
			    -ESRCH) अणु
				DP(NETIF_MSG_LINK, "Found errors on BMAC\n");
				vars->link_up = 0;
				vars->phy_flags |= PHY_HALF_OPEN_CONN_FLAG;
				vars->link_status &= ~LINK_STATUS_LINK_UP;
			पूर्ण

			bnx2x_set_led(params, vars,
				      LED_MODE_OPER, SPEED_10000);
		पूर्ण अन्यथा अणु
			rc = bnx2x_emac_program(params, vars);
			bnx2x_emac_enable(params, vars, 0);

			/* AN complete? */
			अगर ((vars->link_status &
			     LINK_STATUS_AUTO_NEGOTIATE_COMPLETE)
			    && (!(vars->phy_flags & PHY_SGMII_FLAG)) &&
			    SINGLE_MEDIA_सूचीECT(params))
				bnx2x_set_gmii_tx_driver(params);
		पूर्ण
	पूर्ण

	/* PBF - link up */
	अगर (CHIP_IS_E1x(bp))
		rc |= bnx2x_pbf_update(params, vars->flow_ctrl,
				       vars->line_speed);

	/* Disable drain */
	REG_WR(bp, NIG_REG_EGRESS_DRAIN0_MODE + port*4, 0);

	/* Update shared memory */
	bnx2x_update_mng(params, vars->link_status);
	bnx2x_update_mng_eee(params, vars->eee_status);
	/* Check remote fault */
	क्रम (phy_idx = INT_PHY; phy_idx < MAX_PHYS; phy_idx++) अणु
		अगर (params->phy[phy_idx].flags & FLAGS_TX_ERROR_CHECK) अणु
			bnx2x_check_half_खोलो_conn(params, vars, 0);
			अवरोध;
		पूर्ण
	पूर्ण
	msleep(20);
	वापस rc;
पूर्ण

अटल व्योम bnx2x_chng_link_count(काष्ठा link_params *params, bool clear)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u32 addr, val;

	/* Verअगरy the link_change_count is supported by the MFW */
	अगर (!(SHMEM2_HAS(bp, link_change_count)))
		वापस;

	addr = params->shmem2_base +
		दुरत्व(काष्ठा shmem2_region, link_change_count[params->port]);
	अगर (clear)
		val = 0;
	अन्यथा
		val = REG_RD(bp, addr) + 1;
	REG_WR(bp, addr, val);
पूर्ण

/* The bnx2x_link_update function should be called upon link
 * पूर्णांकerrupt.
 * Link is considered up as follows:
 * - सूचीECT_SINGLE_MEDIA - Only XGXS link (पूर्णांकernal link) needs
 *   to be up
 * - SINGLE_MEDIA - The link between the 577xx and the बाह्यal
 *   phy (XGXS) need to up as well as the बाह्यal link of the
 *   phy (PHY_EXT1)
 * - DUAL_MEDIA - The link between the 577xx and the first
 *   बाह्यal phy needs to be up, and at least one of the 2
 *   बाह्यal phy link must be up.
 */
पूर्णांक bnx2x_link_update(काष्ठा link_params *params, काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	काष्ठा link_vars phy_vars[MAX_PHYS];
	u8 port = params->port;
	u8 link_10g_plus, phy_index;
	u32 prev_link_status = vars->link_status;
	u8 ext_phy_link_up = 0, cur_link_up;
	पूर्णांक rc = 0;
	u8 is_mi_पूर्णांक = 0;
	u16 ext_phy_line_speed = 0, prev_line_speed = vars->line_speed;
	u8 active_बाह्यal_phy = INT_PHY;
	vars->phy_flags &= ~PHY_HALF_OPEN_CONN_FLAG;
	vars->link_status &= ~LINK_UPDATE_MASK;
	क्रम (phy_index = INT_PHY; phy_index < params->num_phys;
	      phy_index++) अणु
		phy_vars[phy_index].flow_ctrl = 0;
		phy_vars[phy_index].link_status = 0;
		phy_vars[phy_index].line_speed = 0;
		phy_vars[phy_index].duplex = DUPLEX_FULL;
		phy_vars[phy_index].phy_link_up = 0;
		phy_vars[phy_index].link_up = 0;
		phy_vars[phy_index].fault_detected = 0;
		/* dअगरferent consideration, since vars holds inner state */
		phy_vars[phy_index].eee_status = vars->eee_status;
	पूर्ण

	अगर (USES_WARPCORE(bp))
		bnx2x_set_aer_mmd(params, &params->phy[INT_PHY]);

	DP(NETIF_MSG_LINK, "port %x, XGXS?%x, int_status 0x%x\n",
		 port, (vars->phy_flags & PHY_XGXS_FLAG),
		 REG_RD(bp, NIG_REG_STATUS_INTERRUPT_PORT0 + port*4));

	is_mi_पूर्णांक = (u8)(REG_RD(bp, NIG_REG_EMAC0_STATUS_MISC_MI_INT +
				port*0x18) > 0);
	DP(NETIF_MSG_LINK, "int_mask 0x%x MI_INT %x, SERDES_LINK %x\n",
		 REG_RD(bp, NIG_REG_MASK_INTERRUPT_PORT0 + port*4),
		 is_mi_पूर्णांक,
		 REG_RD(bp, NIG_REG_SERDES0_STATUS_LINK_STATUS + port*0x3c));

	DP(NETIF_MSG_LINK, " 10G %x, XGXS_LINK %x\n",
	  REG_RD(bp, NIG_REG_XGXS0_STATUS_LINK10G + port*0x68),
	  REG_RD(bp, NIG_REG_XGXS0_STATUS_LINK_STATUS + port*0x68));

	/* Disable emac */
	अगर (!CHIP_IS_E3(bp))
		REG_WR(bp, NIG_REG_NIG_EMAC0_EN + port*4, 0);

	/* Step 1:
	 * Check बाह्यal link change only क्रम बाह्यal phys, and apply
	 * priority selection between them in हाल the link on both phys
	 * is up. Note that instead of the common vars, a temporary
	 * vars argument is used since each phy may have dअगरferent link/
	 * speed/duplex result
	 */
	क्रम (phy_index = EXT_PHY1; phy_index < params->num_phys;
	      phy_index++) अणु
		काष्ठा bnx2x_phy *phy = &params->phy[phy_index];
		अगर (!phy->पढ़ो_status)
			जारी;
		/* Read link status and params of this ext phy */
		cur_link_up = phy->पढ़ो_status(phy, params,
					       &phy_vars[phy_index]);
		अगर (cur_link_up) अणु
			DP(NETIF_MSG_LINK, "phy in index %d link is up\n",
				   phy_index);
		पूर्ण अन्यथा अणु
			DP(NETIF_MSG_LINK, "phy in index %d link is down\n",
				   phy_index);
			जारी;
		पूर्ण

		अगर (!ext_phy_link_up) अणु
			ext_phy_link_up = 1;
			active_बाह्यal_phy = phy_index;
		पूर्ण अन्यथा अणु
			चयन (bnx2x_phy_selection(params)) अणु
			हाल PORT_HW_CFG_PHY_SELECTION_HARDWARE_DEFAULT:
			हाल PORT_HW_CFG_PHY_SELECTION_FIRST_PHY_PRIORITY:
			/* In this option, the first PHY makes sure to pass the
			 * traffic through itself only.
			 * It's not clear how to reset the link on the second
			 * phy.
			 */
				active_बाह्यal_phy = EXT_PHY1;
				अवरोध;
			हाल PORT_HW_CFG_PHY_SELECTION_SECOND_PHY_PRIORITY:
			/* In this option, the first PHY makes sure to pass the
			 * traffic through the second PHY.
			 */
				active_बाह्यal_phy = EXT_PHY2;
				अवरोध;
			शेष:
			/* Link indication on both PHYs with the following हालs
			 * is invalid:
			 * - FIRST_PHY means that second phy wasn't initialized,
			 * hence its link is expected to be करोwn
			 * - SECOND_PHY means that first phy should not be able
			 * to link up by itself (using configuration)
			 * - DEFAULT should be overridden during initialization
			 */
				DP(NETIF_MSG_LINK, "Invalid link indication"
					   "mpc=0x%x. DISABLING LINK !!!\n",
					   params->multi_phy_config);
				ext_phy_link_up = 0;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	prev_line_speed = vars->line_speed;
	/* Step 2:
	 * Read the status of the पूर्णांकernal phy. In हाल of
	 * सूचीECT_SINGLE_MEDIA board, this link is the बाह्यal link,
	 * otherwise this is the link between the 577xx and the first
	 * बाह्यal phy
	 */
	अगर (params->phy[INT_PHY].पढ़ो_status)
		params->phy[INT_PHY].पढ़ो_status(
			&params->phy[INT_PHY],
			params, vars);
	/* The INT_PHY flow control reside in the vars. This include the
	 * हाल where the speed or flow control are not set to AUTO.
	 * Otherwise, the active बाह्यal phy flow control result is set
	 * to the vars. The ext_phy_line_speed is needed to check अगर the
	 * speed is dअगरferent between the पूर्णांकernal phy and बाह्यal phy.
	 * This हाल may be result of पूर्णांकermediate link speed change.
	 */
	अगर (active_बाह्यal_phy > INT_PHY) अणु
		vars->flow_ctrl = phy_vars[active_बाह्यal_phy].flow_ctrl;
		/* Link speed is taken from the XGXS. AN and FC result from
		 * the बाह्यal phy.
		 */
		vars->link_status |= phy_vars[active_बाह्यal_phy].link_status;

		/* अगर active_बाह्यal_phy is first PHY and link is up - disable
		 * disable TX on second बाह्यal PHY
		 */
		अगर (active_बाह्यal_phy == EXT_PHY1) अणु
			अगर (params->phy[EXT_PHY2].phy_specअगरic_func) अणु
				DP(NETIF_MSG_LINK,
				   "Disabling TX on EXT_PHY2\n");
				params->phy[EXT_PHY2].phy_specअगरic_func(
					&params->phy[EXT_PHY2],
					params, DISABLE_TX);
			पूर्ण
		पूर्ण

		ext_phy_line_speed = phy_vars[active_बाह्यal_phy].line_speed;
		vars->duplex = phy_vars[active_बाह्यal_phy].duplex;
		अगर (params->phy[active_बाह्यal_phy].supported &
		    SUPPORTED_FIBRE)
			vars->link_status |= LINK_STATUS_SERDES_LINK;
		अन्यथा
			vars->link_status &= ~LINK_STATUS_SERDES_LINK;

		vars->eee_status = phy_vars[active_बाह्यal_phy].eee_status;

		DP(NETIF_MSG_LINK, "Active external phy selected: %x\n",
			   active_बाह्यal_phy);
	पूर्ण

	क्रम (phy_index = EXT_PHY1; phy_index < params->num_phys;
	      phy_index++) अणु
		अगर (params->phy[phy_index].flags &
		    FLAGS_REARM_LATCH_SIGNAL) अणु
			bnx2x_rearm_latch_संकेत(bp, port,
						 phy_index ==
						 active_बाह्यal_phy);
			अवरोध;
		पूर्ण
	पूर्ण
	DP(NETIF_MSG_LINK, "vars->flow_ctrl = 0x%x, vars->link_status = 0x%x,"
		   " ext_phy_line_speed = %d\n", vars->flow_ctrl,
		   vars->link_status, ext_phy_line_speed);
	/* Upon link speed change set the NIG पूर्णांकo drain mode. Comes to
	 * deals with possible FIFO glitch due to clk change when speed
	 * is decreased without link करोwn indicator
	 */

	अगर (vars->phy_link_up) अणु
		अगर (!(SINGLE_MEDIA_सूचीECT(params)) && ext_phy_link_up &&
		    (ext_phy_line_speed != vars->line_speed)) अणु
			DP(NETIF_MSG_LINK, "Internal link speed %d is"
				   " different than the external"
				   " link speed %d\n", vars->line_speed,
				   ext_phy_line_speed);
			vars->phy_link_up = 0;
		पूर्ण अन्यथा अगर (prev_line_speed != vars->line_speed) अणु
			REG_WR(bp, NIG_REG_EGRESS_DRAIN0_MODE + params->port*4,
			       0);
			usleep_range(1000, 2000);
		पूर्ण
	पूर्ण

	/* Anything 10 and over uses the bmac */
	link_10g_plus = (vars->line_speed >= SPEED_10000);

	bnx2x_link_पूर्णांक_ack(params, vars, link_10g_plus);

	/* In हाल बाह्यal phy link is up, and पूर्णांकernal link is करोwn
	 * (not initialized yet probably after link initialization, it
	 * needs to be initialized.
	 * Note that after link करोwn-up as result of cable plug, the xgxs
	 * link would probably become up again without the need
	 * initialize it
	 */
	अगर (!(SINGLE_MEDIA_सूचीECT(params))) अणु
		DP(NETIF_MSG_LINK, "ext_phy_link_up = %d, int_link_up = %d,"
			   " init_preceding = %d\n", ext_phy_link_up,
			   vars->phy_link_up,
			   params->phy[EXT_PHY1].flags &
			   FLAGS_INIT_XGXS_FIRST);
		अगर (!(params->phy[EXT_PHY1].flags &
		      FLAGS_INIT_XGXS_FIRST)
		    && ext_phy_link_up && !vars->phy_link_up) अणु
			vars->line_speed = ext_phy_line_speed;
			अगर (vars->line_speed < SPEED_1000)
				vars->phy_flags |= PHY_SGMII_FLAG;
			अन्यथा
				vars->phy_flags &= ~PHY_SGMII_FLAG;

			अगर (params->phy[INT_PHY].config_init)
				params->phy[INT_PHY].config_init(
					&params->phy[INT_PHY], params,
						vars);
		पूर्ण
	पूर्ण
	/* Link is up only अगर both local phy and बाह्यal phy (in हाल of
	 * non-direct board) are up and no fault detected on active PHY.
	 */
	vars->link_up = (vars->phy_link_up &&
			 (ext_phy_link_up ||
			  SINGLE_MEDIA_सूचीECT(params)) &&
			 (phy_vars[active_बाह्यal_phy].fault_detected == 0));

	/* Update the PFC configuration in हाल it was changed */
	अगर (params->feature_config_flags & FEATURE_CONFIG_PFC_ENABLED)
		vars->link_status |= LINK_STATUS_PFC_ENABLED;
	अन्यथा
		vars->link_status &= ~LINK_STATUS_PFC_ENABLED;

	अगर (vars->link_up)
		rc = bnx2x_update_link_up(params, vars, link_10g_plus);
	अन्यथा
		rc = bnx2x_update_link_करोwn(params, vars);

	अगर ((prev_link_status ^ vars->link_status) & LINK_STATUS_LINK_UP)
		bnx2x_chng_link_count(params, false);

	/* Update MCP link status was changed */
	अगर (params->feature_config_flags & FEATURE_CONFIG_BC_SUPPORTS_AFEX)
		bnx2x_fw_command(bp, DRV_MSG_CODE_LINK_STATUS_CHANGED, 0);

	वापस rc;
पूर्ण

/*****************************************************************************/
/*			    External Phy section			     */
/*****************************************************************************/
व्योम bnx2x_ext_phy_hw_reset(काष्ठा bnx2x *bp, u8 port)
अणु
	bnx2x_set_gpio(bp, MISC_REGISTERS_GPIO_1,
		       MISC_REGISTERS_GPIO_OUTPUT_LOW, port);
	usleep_range(1000, 2000);
	bnx2x_set_gpio(bp, MISC_REGISTERS_GPIO_1,
		       MISC_REGISTERS_GPIO_OUTPUT_HIGH, port);
पूर्ण

अटल व्योम bnx2x_save_spirom_version(काष्ठा bnx2x *bp, u8 port,
				      u32 spirom_ver, u32 ver_addr)
अणु
	DP(NETIF_MSG_LINK, "FW version 0x%x:0x%x for port %d\n",
		 (u16)(spirom_ver>>16), (u16)spirom_ver, port);

	अगर (ver_addr)
		REG_WR(bp, ver_addr, spirom_ver);
पूर्ण

अटल व्योम bnx2x_save_bcm_spirom_ver(काष्ठा bnx2x *bp,
				      काष्ठा bnx2x_phy *phy,
				      u8 port)
अणु
	u16 fw_ver1, fw_ver2;

	bnx2x_cl45_पढ़ो(bp, phy, MDIO_PMA_DEVAD,
			MDIO_PMA_REG_ROM_VER1, &fw_ver1);
	bnx2x_cl45_पढ़ो(bp, phy, MDIO_PMA_DEVAD,
			MDIO_PMA_REG_ROM_VER2, &fw_ver2);
	bnx2x_save_spirom_version(bp, port, (u32)(fw_ver1<<16 | fw_ver2),
				  phy->ver_addr);
पूर्ण

अटल व्योम bnx2x_ext_phy_10G_an_resolve(काष्ठा bnx2x *bp,
				       काष्ठा bnx2x_phy *phy,
				       काष्ठा link_vars *vars)
अणु
	u16 val;
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_AN_DEVAD,
			MDIO_AN_REG_STATUS, &val);
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_AN_DEVAD,
			MDIO_AN_REG_STATUS, &val);
	अगर (val & (1<<5))
		vars->link_status |= LINK_STATUS_AUTO_NEGOTIATE_COMPLETE;
	अगर ((val & (1<<0)) == 0)
		vars->link_status |= LINK_STATUS_PARALLEL_DETECTION_USED;
पूर्ण

/******************************************************************/
/*		common BCM8073/BCM8727 PHY SECTION		  */
/******************************************************************/
अटल व्योम bnx2x_8073_resolve_fc(काष्ठा bnx2x_phy *phy,
				  काष्ठा link_params *params,
				  काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	अगर (phy->req_line_speed == SPEED_10 ||
	    phy->req_line_speed == SPEED_100) अणु
		vars->flow_ctrl = phy->req_flow_ctrl;
		वापस;
	पूर्ण

	अगर (bnx2x_ext_phy_resolve_fc(phy, params, vars) &&
	    (vars->flow_ctrl == BNX2X_FLOW_CTRL_NONE)) अणु
		u16 छोड़ो_result;
		u16 ld_छोड़ो;		/* local */
		u16 lp_छोड़ो;		/* link partner */
		bnx2x_cl45_पढ़ो(bp, phy,
				MDIO_AN_DEVAD,
				MDIO_AN_REG_CL37_FC_LD, &ld_छोड़ो);

		bnx2x_cl45_पढ़ो(bp, phy,
				MDIO_AN_DEVAD,
				MDIO_AN_REG_CL37_FC_LP, &lp_छोड़ो);
		छोड़ो_result = (ld_छोड़ो &
				MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH) >> 5;
		छोड़ो_result |= (lp_छोड़ो &
				 MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH) >> 7;

		bnx2x_छोड़ो_resolve(phy, params, vars, छोड़ो_result);
		DP(NETIF_MSG_LINK, "Ext PHY CL37 pause result 0x%x\n",
			   छोड़ो_result);
	पूर्ण
पूर्ण
अटल पूर्णांक bnx2x_8073_8727_बाह्यal_rom_boot(काष्ठा bnx2x *bp,
					     काष्ठा bnx2x_phy *phy,
					     u8 port)
अणु
	u32 count = 0;
	u16 fw_ver1, fw_msgout;
	पूर्णांक rc = 0;

	/* Boot port from बाह्यal ROM  */
	/* EDC grst */
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_GEN_CTRL,
			 0x0001);

	/* Ucode reboot and rst */
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_GEN_CTRL,
			 0x008c);

	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_MISC_CTRL1, 0x0001);

	/* Reset पूर्णांकernal microprocessor */
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_GEN_CTRL,
			 MDIO_PMA_REG_GEN_CTRL_ROM_MICRO_RESET);

	/* Release srst bit */
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_GEN_CTRL,
			 MDIO_PMA_REG_GEN_CTRL_ROM_RESET_INTERNAL_MP);

	/* Delay 100ms per the PHY specअगरications */
	msleep(100);

	/* 8073 someबार taking दीर्घer to करोwnload */
	करो अणु
		count++;
		अगर (count > 300) अणु
			DP(NETIF_MSG_LINK,
				 "bnx2x_8073_8727_external_rom_boot port %x:"
				 "Download failed. fw version = 0x%x\n",
				 port, fw_ver1);
			rc = -EINVAL;
			अवरोध;
		पूर्ण

		bnx2x_cl45_पढ़ो(bp, phy,
				MDIO_PMA_DEVAD,
				MDIO_PMA_REG_ROM_VER1, &fw_ver1);
		bnx2x_cl45_पढ़ो(bp, phy,
				MDIO_PMA_DEVAD,
				MDIO_PMA_REG_M8051_MSGOUT_REG, &fw_msgout);

		usleep_range(1000, 2000);
	पूर्ण जबतक (fw_ver1 == 0 || fw_ver1 == 0x4321 ||
			((fw_msgout & 0xff) != 0x03 && (phy->type ==
			PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8073)));

	/* Clear ser_boot_ctl bit */
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_MISC_CTRL1, 0x0000);
	bnx2x_save_bcm_spirom_ver(bp, phy, port);

	DP(NETIF_MSG_LINK,
		 "bnx2x_8073_8727_external_rom_boot port %x:"
		 "Download complete. fw version = 0x%x\n",
		 port, fw_ver1);

	वापस rc;
पूर्ण

/******************************************************************/
/*			BCM8073 PHY SECTION			  */
/******************************************************************/
अटल पूर्णांक bnx2x_8073_is_snr_needed(काष्ठा bnx2x *bp, काष्ठा bnx2x_phy *phy)
अणु
	/* This is only required क्रम 8073A1, version 102 only */
	u16 val;

	/* Read 8073 HW revision*/
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD,
			MDIO_PMA_REG_8073_CHIP_REV, &val);

	अगर (val != 1) अणु
		/* No need to workaround in 8073 A1 */
		वापस 0;
	पूर्ण

	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD,
			MDIO_PMA_REG_ROM_VER2, &val);

	/* SNR should be applied only क्रम version 0x102 */
	अगर (val != 0x102)
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक bnx2x_8073_xaui_wa(काष्ठा bnx2x *bp, काष्ठा bnx2x_phy *phy)
अणु
	u16 val, cnt, cnt1 ;

	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD,
			MDIO_PMA_REG_8073_CHIP_REV, &val);

	अगर (val > 0) अणु
		/* No need to workaround in 8073 A1 */
		वापस 0;
	पूर्ण
	/* XAUI workaround in 8073 A0: */

	/* After loading the boot ROM and restarting Autoneg, poll
	 * Dev1, Reg $C820:
	 */

	क्रम (cnt = 0; cnt < 1000; cnt++) अणु
		bnx2x_cl45_पढ़ो(bp, phy,
				MDIO_PMA_DEVAD,
				MDIO_PMA_REG_8073_SPEED_LINK_STATUS,
				&val);
		  /* If bit [14] = 0 or bit [13] = 0, जारी on with
		   * प्रणाली initialization (XAUI work-around not required, as
		   * these bits indicate 2.5G or 1G link up).
		   */
		अगर (!(val & (1<<14)) || !(val & (1<<13))) अणु
			DP(NETIF_MSG_LINK, "XAUI work-around not required\n");
			वापस 0;
		पूर्ण अन्यथा अगर (!(val & (1<<15))) अणु
			DP(NETIF_MSG_LINK, "bit 15 went off\n");
			/* If bit 15 is 0, then poll Dev1, Reg $C841 until it's
			 * MSB (bit15) goes to 1 (indicating that the XAUI
			 * workaround has completed), then जारी on with
			 * प्रणाली initialization.
			 */
			क्रम (cnt1 = 0; cnt1 < 1000; cnt1++) अणु
				bnx2x_cl45_पढ़ो(bp, phy,
					MDIO_PMA_DEVAD,
					MDIO_PMA_REG_8073_XAUI_WA, &val);
				अगर (val & (1<<15)) अणु
					DP(NETIF_MSG_LINK,
					  "XAUI workaround has completed\n");
					वापस 0;
				पूर्ण
				usleep_range(3000, 6000);
			पूर्ण
			अवरोध;
		पूर्ण
		usleep_range(3000, 6000);
	पूर्ण
	DP(NETIF_MSG_LINK, "Warning: XAUI work-around timeout !!!\n");
	वापस -EINVAL;
पूर्ण

अटल व्योम bnx2x_807x_क्रमce_10G(काष्ठा bnx2x *bp, काष्ठा bnx2x_phy *phy)
अणु
	/* Force KR or KX */
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD, MDIO_PMA_REG_CTRL, 0x2040);
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD, MDIO_PMA_REG_10G_CTRL2, 0x000b);
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD, MDIO_PMA_REG_BCM_CTRL, 0x0000);
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_AN_DEVAD, MDIO_AN_REG_CTRL, 0x0000);
पूर्ण

अटल व्योम bnx2x_8073_set_छोड़ो_cl37(काष्ठा link_params *params,
				      काष्ठा bnx2x_phy *phy,
				      काष्ठा link_vars *vars)
अणु
	u16 cl37_val;
	काष्ठा bnx2x *bp = params->bp;
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_AN_DEVAD, MDIO_AN_REG_CL37_FC_LD, &cl37_val);

	cl37_val &= ~MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH;
	/* Please refer to Table 28B-3 of 802.3ab-1999 spec. */
	bnx2x_calc_ieee_aneg_adv(phy, params, &vars->ieee_fc);
	अगर ((vars->ieee_fc &
	    MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_SYMMETRIC) ==
	    MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_SYMMETRIC) अणु
		cl37_val |=  MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_SYMMETRIC;
	पूर्ण
	अगर ((vars->ieee_fc &
	    MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_ASYMMETRIC) ==
	    MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_ASYMMETRIC) अणु
		cl37_val |=  MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_ASYMMETRIC;
	पूर्ण
	अगर ((vars->ieee_fc &
	    MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH) ==
	    MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH) अणु
		cl37_val |= MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH;
	पूर्ण
	DP(NETIF_MSG_LINK,
		 "Ext phy AN advertize cl37 0x%x\n", cl37_val);

	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_AN_DEVAD, MDIO_AN_REG_CL37_FC_LD, cl37_val);
	msleep(500);
पूर्ण

अटल व्योम bnx2x_8073_specअगरic_func(काष्ठा bnx2x_phy *phy,
				     काष्ठा link_params *params,
				     u32 action)
अणु
	काष्ठा bnx2x *bp = params->bp;
	चयन (action) अणु
	हाल PHY_INIT:
		/* Enable LASI */
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_LASI_RXCTRL, (1<<2));
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_LASI_CTRL,  0x0004);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम bnx2x_8073_config_init(काष्ठा bnx2x_phy *phy,
				   काष्ठा link_params *params,
				   काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 val = 0, पंचांगp1;
	u8 gpio_port;
	DP(NETIF_MSG_LINK, "Init 8073\n");

	अगर (CHIP_IS_E2(bp))
		gpio_port = BP_PATH(bp);
	अन्यथा
		gpio_port = params->port;
	/* Restore normal घातer mode*/
	bnx2x_set_gpio(bp, MISC_REGISTERS_GPIO_2,
		       MISC_REGISTERS_GPIO_OUTPUT_HIGH, gpio_port);

	bnx2x_set_gpio(bp, MISC_REGISTERS_GPIO_1,
		       MISC_REGISTERS_GPIO_OUTPUT_HIGH, gpio_port);

	bnx2x_8073_specअगरic_func(phy, params, PHY_INIT);
	bnx2x_8073_set_छोड़ो_cl37(params, phy, vars);

	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_M8051_MSGOUT_REG, &पंचांगp1);

	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_LASI_RXSTAT, &पंचांगp1);

	DP(NETIF_MSG_LINK, "Before rom RX_ALARM(port1): 0x%x\n", पंचांगp1);

	/* Swap polarity अगर required - Must be करोne only in non-1G mode */
	अगर (params->lane_config & PORT_HW_CFG_SWAP_PHY_POLARITY_ENABLED) अणु
		/* Configure the 8073 to swap _P and _N of the KR lines */
		DP(NETIF_MSG_LINK, "Swapping polarity for the 8073\n");
		/* 10G Rx/Tx and 1G Tx संकेत polarity swap */
		bnx2x_cl45_पढ़ो(bp, phy,
				MDIO_PMA_DEVAD,
				MDIO_PMA_REG_8073_OPT_DIGITAL_CTRL, &val);
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD,
				 MDIO_PMA_REG_8073_OPT_DIGITAL_CTRL,
				 (val | (3<<9)));
	पूर्ण


	/* Enable CL37 BAM */
	अगर (REG_RD(bp, params->shmem_base +
			 दुरत्व(काष्ठा shmem_region, dev_info.
				  port_hw_config[params->port].शेष_cfg)) &
	    PORT_HW_CFG_ENABLE_BAM_ON_KR_ENABLED) अणु

		bnx2x_cl45_पढ़ो(bp, phy,
				MDIO_AN_DEVAD,
				MDIO_AN_REG_8073_BAM, &val);
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_AN_DEVAD,
				 MDIO_AN_REG_8073_BAM, val | 1);
		DP(NETIF_MSG_LINK, "Enable CL37 BAM on KR\n");
	पूर्ण
	अगर (params->loopback_mode == LOOPBACK_EXT) अणु
		bnx2x_807x_क्रमce_10G(bp, phy);
		DP(NETIF_MSG_LINK, "Forced speed 10G on 807X\n");
		वापस;
	पूर्ण अन्यथा अणु
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_REG_BCM_CTRL, 0x0002);
	पूर्ण
	अगर (phy->req_line_speed != SPEED_AUTO_NEG) अणु
		अगर (phy->req_line_speed == SPEED_10000) अणु
			val = (1<<7);
		पूर्ण अन्यथा अगर (phy->req_line_speed ==  SPEED_2500) अणु
			val = (1<<5);
			/* Note that 2.5G works only when used with 1G
			 * advertisement
			 */
		पूर्ण अन्यथा
			val = (1<<5);
	पूर्ण अन्यथा अणु
		val = 0;
		अगर (phy->speed_cap_mask &
			PORT_HW_CFG_SPEED_CAPABILITY_D0_10G)
			val |= (1<<7);

		/* Note that 2.5G works only when used with 1G advertisement */
		अगर (phy->speed_cap_mask &
			(PORT_HW_CFG_SPEED_CAPABILITY_D0_1G |
			 PORT_HW_CFG_SPEED_CAPABILITY_D0_2_5G))
			val |= (1<<5);
		DP(NETIF_MSG_LINK, "807x autoneg val = 0x%x\n", val);
	पूर्ण

	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_AN_DEVAD, MDIO_AN_REG_ADV, val);
	bnx2x_cl45_पढ़ो(bp, phy, MDIO_AN_DEVAD, MDIO_AN_REG_8073_2_5G, &पंचांगp1);

	अगर (((phy->speed_cap_mask & PORT_HW_CFG_SPEED_CAPABILITY_D0_2_5G) &&
	     (phy->req_line_speed == SPEED_AUTO_NEG)) ||
	    (phy->req_line_speed == SPEED_2500)) अणु
		u16 phy_ver;
		/* Allow 2.5G क्रम A1 and above */
		bnx2x_cl45_पढ़ो(bp, phy,
				MDIO_PMA_DEVAD, MDIO_PMA_REG_8073_CHIP_REV,
				&phy_ver);
		DP(NETIF_MSG_LINK, "Add 2.5G\n");
		अगर (phy_ver > 0)
			पंचांगp1 |= 1;
		अन्यथा
			पंचांगp1 &= 0xfffe;
	पूर्ण अन्यथा अणु
		DP(NETIF_MSG_LINK, "Disable 2.5G\n");
		पंचांगp1 &= 0xfffe;
	पूर्ण

	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_AN_DEVAD, MDIO_AN_REG_8073_2_5G, पंचांगp1);
	/* Add support क्रम CL37 (passive mode) II */

	bnx2x_cl45_पढ़ो(bp, phy, MDIO_AN_DEVAD, MDIO_AN_REG_CL37_FC_LD, &पंचांगp1);
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_AN_DEVAD, MDIO_AN_REG_CL37_FC_LD,
			 (पंचांगp1 | ((phy->req_duplex == DUPLEX_FULL) ?
				  0x20 : 0x40)));

	/* Add support क्रम CL37 (passive mode) III */
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_AN_DEVAD, MDIO_AN_REG_CL37_AN, 0x1000);

	/* The SNR will improve about 2db by changing BW and FEE मुख्य
	 * tap. Rest commands are executed after link is up
	 * Change FFE मुख्य cursor to 5 in EDC रेजिस्टर
	 */
	अगर (bnx2x_8073_is_snr_needed(bp, phy))
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_REG_EDC_FFE_MAIN,
				 0xFB0C);

	/* Enable FEC (Forware Error Correction) Request in the AN */
	bnx2x_cl45_पढ़ो(bp, phy, MDIO_AN_DEVAD, MDIO_AN_REG_ADV2, &पंचांगp1);
	पंचांगp1 |= (1<<15);
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_AN_DEVAD, MDIO_AN_REG_ADV2, पंचांगp1);

	bnx2x_ext_phy_set_छोड़ो(params, phy, vars);

	/* Restart स्वतःneg */
	msleep(500);
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_AN_DEVAD, MDIO_AN_REG_CTRL, 0x1200);
	DP(NETIF_MSG_LINK, "807x Autoneg Restart: Advertise 1G=%x, 10G=%x\n",
		   ((val & (1<<5)) > 0), ((val & (1<<7)) > 0));
पूर्ण

अटल u8 bnx2x_8073_पढ़ो_status(काष्ठा bnx2x_phy *phy,
				 काष्ठा link_params *params,
				 काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u8 link_up = 0;
	u16 val1, val2;
	u16 link_status = 0;
	u16 an1000_status = 0;

	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_LASI_STAT, &val1);

	DP(NETIF_MSG_LINK, "8703 LASI status 0x%x\n", val1);

	/* Clear the पूर्णांकerrupt LASI status रेजिस्टर */
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PCS_DEVAD, MDIO_PCS_REG_STATUS, &val2);
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PCS_DEVAD, MDIO_PCS_REG_STATUS, &val1);
	DP(NETIF_MSG_LINK, "807x PCS status 0x%x->0x%x\n", val2, val1);
	/* Clear MSG-OUT */
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_M8051_MSGOUT_REG, &val1);

	/* Check the LASI */
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_LASI_RXSTAT, &val2);

	DP(NETIF_MSG_LINK, "KR 0x9003 0x%x\n", val2);

	/* Check the link status */
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PCS_DEVAD, MDIO_PCS_REG_STATUS, &val2);
	DP(NETIF_MSG_LINK, "KR PCS status 0x%x\n", val2);

	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_STATUS, &val2);
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_STATUS, &val1);
	link_up = ((val1 & 4) == 4);
	DP(NETIF_MSG_LINK, "PMA_REG_STATUS=0x%x\n", val1);

	अगर (link_up &&
	     ((phy->req_line_speed != SPEED_10000))) अणु
		अगर (bnx2x_8073_xaui_wa(bp, phy) != 0)
			वापस 0;
	पूर्ण
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_AN_DEVAD, MDIO_AN_REG_LINK_STATUS, &an1000_status);
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_AN_DEVAD, MDIO_AN_REG_LINK_STATUS, &an1000_status);

	/* Check the link status on 1.1.2 */
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_STATUS, &val2);
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_STATUS, &val1);
	DP(NETIF_MSG_LINK, "KR PMA status 0x%x->0x%x,"
		   "an_link_status=0x%x\n", val2, val1, an1000_status);

	link_up = (((val1 & 4) == 4) || (an1000_status & (1<<1)));
	अगर (link_up && bnx2x_8073_is_snr_needed(bp, phy)) अणु
		/* The SNR will improve about 2dbby changing the BW and FEE मुख्य
		 * tap. The 1st ग_लिखो to change FFE मुख्य tap is set beक्रमe
		 * restart AN. Change PLL Bandwidth in EDC रेजिस्टर
		 */
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_REG_PLL_BANDWIDTH,
				 0x26BC);

		/* Change CDR Bandwidth in EDC रेजिस्टर */
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_REG_CDR_BANDWIDTH,
				 0x0333);
	पूर्ण
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_8073_SPEED_LINK_STATUS,
			&link_status);

	/* Bits 0..2 --> speed detected, bits 13..15--> link is करोwn */
	अगर ((link_status & (1<<2)) && (!(link_status & (1<<15)))) अणु
		link_up = 1;
		vars->line_speed = SPEED_10000;
		DP(NETIF_MSG_LINK, "port %x: External link up in 10G\n",
			   params->port);
	पूर्ण अन्यथा अगर ((link_status & (1<<1)) && (!(link_status & (1<<14)))) अणु
		link_up = 1;
		vars->line_speed = SPEED_2500;
		DP(NETIF_MSG_LINK, "port %x: External link up in 2.5G\n",
			   params->port);
	पूर्ण अन्यथा अगर ((link_status & (1<<0)) && (!(link_status & (1<<13)))) अणु
		link_up = 1;
		vars->line_speed = SPEED_1000;
		DP(NETIF_MSG_LINK, "port %x: External link up in 1G\n",
			   params->port);
	पूर्ण अन्यथा अणु
		link_up = 0;
		DP(NETIF_MSG_LINK, "port %x: External link is down\n",
			   params->port);
	पूर्ण

	अगर (link_up) अणु
		/* Swap polarity अगर required */
		अगर (params->lane_config &
		    PORT_HW_CFG_SWAP_PHY_POLARITY_ENABLED) अणु
			/* Configure the 8073 to swap P and N of the KR lines */
			bnx2x_cl45_पढ़ो(bp, phy,
					MDIO_XS_DEVAD,
					MDIO_XS_REG_8073_RX_CTRL_PCIE, &val1);
			/* Set bit 3 to invert Rx in 1G mode and clear this bit
			 * when it`s in 10G mode.
			 */
			अगर (vars->line_speed == SPEED_1000) अणु
				DP(NETIF_MSG_LINK, "Swapping 1G polarity for"
					      "the 8073\n");
				val1 |= (1<<3);
			पूर्ण अन्यथा
				val1 &= ~(1<<3);

			bnx2x_cl45_ग_लिखो(bp, phy,
					 MDIO_XS_DEVAD,
					 MDIO_XS_REG_8073_RX_CTRL_PCIE,
					 val1);
		पूर्ण
		bnx2x_ext_phy_10G_an_resolve(bp, phy, vars);
		bnx2x_8073_resolve_fc(phy, params, vars);
		vars->duplex = DUPLEX_FULL;
	पूर्ण

	अगर (vars->link_status & LINK_STATUS_AUTO_NEGOTIATE_COMPLETE) अणु
		bnx2x_cl45_पढ़ो(bp, phy, MDIO_AN_DEVAD,
				MDIO_AN_REG_LP_AUTO_NEG2, &val1);

		अगर (val1 & (1<<5))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_1000TFD_CAPABLE;
		अगर (val1 & (1<<7))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_10GXFD_CAPABLE;
	पूर्ण

	वापस link_up;
पूर्ण

अटल व्योम bnx2x_8073_link_reset(काष्ठा bnx2x_phy *phy,
				  काष्ठा link_params *params)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u8 gpio_port;
	अगर (CHIP_IS_E2(bp))
		gpio_port = BP_PATH(bp);
	अन्यथा
		gpio_port = params->port;
	DP(NETIF_MSG_LINK, "Setting 8073 port %d into low power mode\n",
	   gpio_port);
	bnx2x_set_gpio(bp, MISC_REGISTERS_GPIO_2,
		       MISC_REGISTERS_GPIO_OUTPUT_LOW,
		       gpio_port);
पूर्ण

/******************************************************************/
/*			BCM8705 PHY SECTION			  */
/******************************************************************/
अटल व्योम bnx2x_8705_config_init(काष्ठा bnx2x_phy *phy,
				   काष्ठा link_params *params,
				   काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	DP(NETIF_MSG_LINK, "init 8705\n");
	/* Restore normal घातer mode*/
	bnx2x_set_gpio(bp, MISC_REGISTERS_GPIO_2,
		       MISC_REGISTERS_GPIO_OUTPUT_HIGH, params->port);
	/* HW reset */
	bnx2x_ext_phy_hw_reset(bp, params->port);
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_PMA_DEVAD, MDIO_PMA_REG_CTRL, 0xa040);
	bnx2x_रुको_reset_complete(bp, phy, params);

	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD, MDIO_PMA_REG_MISC_CTRL, 0x8288);
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD, MDIO_PMA_REG_PHY_IDENTIFIER, 0x7fbf);
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD, MDIO_PMA_REG_CMU_PLL_BYPASS, 0x0100);
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_WIS_DEVAD, MDIO_WIS_REG_LASI_CNTL, 0x1);
	/* BCM8705 करोesn't have microcode, hence the 0 */
	bnx2x_save_spirom_version(bp, params->port, params->shmem_base, 0);
पूर्ण

अटल u8 bnx2x_8705_पढ़ो_status(काष्ठा bnx2x_phy *phy,
				 काष्ठा link_params *params,
				 काष्ठा link_vars *vars)
अणु
	u8 link_up = 0;
	u16 val1, rx_sd;
	काष्ठा bnx2x *bp = params->bp;
	DP(NETIF_MSG_LINK, "read status 8705\n");
	bnx2x_cl45_पढ़ो(bp, phy,
		      MDIO_WIS_DEVAD, MDIO_WIS_REG_LASI_STATUS, &val1);
	DP(NETIF_MSG_LINK, "8705 LASI status 0x%x\n", val1);

	bnx2x_cl45_पढ़ो(bp, phy,
		      MDIO_WIS_DEVAD, MDIO_WIS_REG_LASI_STATUS, &val1);
	DP(NETIF_MSG_LINK, "8705 LASI status 0x%x\n", val1);

	bnx2x_cl45_पढ़ो(bp, phy,
		      MDIO_PMA_DEVAD, MDIO_PMA_REG_RX_SD, &rx_sd);

	bnx2x_cl45_पढ़ो(bp, phy,
		      MDIO_PMA_DEVAD, 0xc809, &val1);
	bnx2x_cl45_पढ़ो(bp, phy,
		      MDIO_PMA_DEVAD, 0xc809, &val1);

	DP(NETIF_MSG_LINK, "8705 1.c809 val=0x%x\n", val1);
	link_up = ((rx_sd & 0x1) && (val1 & (1<<9)) && ((val1 & (1<<8)) == 0));
	अगर (link_up) अणु
		vars->line_speed = SPEED_10000;
		bnx2x_ext_phy_resolve_fc(phy, params, vars);
	पूर्ण
	वापस link_up;
पूर्ण

/******************************************************************/
/*			SFP+ module Section			  */
/******************************************************************/
अटल व्योम bnx2x_set_disable_pmd_transmit(काष्ठा link_params *params,
					   काष्ठा bnx2x_phy *phy,
					   u8 pmd_dis)
अणु
	काष्ठा bnx2x *bp = params->bp;
	/* Disable transmitter only क्रम bootcodes which can enable it afterwards
	 * (क्रम D3 link)
	 */
	अगर (pmd_dis) अणु
		अगर (params->feature_config_flags &
		     FEATURE_CONFIG_BC_SUPPORTS_SFP_TX_DISABLED)
			DP(NETIF_MSG_LINK, "Disabling PMD transmitter\n");
		अन्यथा अणु
			DP(NETIF_MSG_LINK, "NOT disabling PMD transmitter\n");
			वापस;
		पूर्ण
	पूर्ण अन्यथा
		DP(NETIF_MSG_LINK, "Enabling PMD transmitter\n");
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_TX_DISABLE, pmd_dis);
पूर्ण

अटल u8 bnx2x_get_gpio_port(काष्ठा link_params *params)
अणु
	u8 gpio_port;
	u32 swap_val, swap_override;
	काष्ठा bnx2x *bp = params->bp;
	अगर (CHIP_IS_E2(bp))
		gpio_port = BP_PATH(bp);
	अन्यथा
		gpio_port = params->port;
	swap_val = REG_RD(bp, NIG_REG_PORT_SWAP);
	swap_override = REG_RD(bp, NIG_REG_STRAP_OVERRIDE);
	वापस gpio_port ^ (swap_val && swap_override);
पूर्ण

अटल व्योम bnx2x_sfp_e1e2_set_transmitter(काष्ठा link_params *params,
					   काष्ठा bnx2x_phy *phy,
					   u8 tx_en)
अणु
	u16 val;
	u8 port = params->port;
	काष्ठा bnx2x *bp = params->bp;
	u32 tx_en_mode;

	/* Disable/Enable transmitter ( TX laser of the SFP+ module.)*/
	tx_en_mode = REG_RD(bp, params->shmem_base +
			    दुरत्व(काष्ठा shmem_region,
				     dev_info.port_hw_config[port].sfp_ctrl)) &
		PORT_HW_CFG_TX_LASER_MASK;
	DP(NETIF_MSG_LINK, "Setting transmitter tx_en=%x for port %x "
			   "mode = %x\n", tx_en, port, tx_en_mode);
	चयन (tx_en_mode) अणु
	हाल PORT_HW_CFG_TX_LASER_MDIO:

		bnx2x_cl45_पढ़ो(bp, phy,
				MDIO_PMA_DEVAD,
				MDIO_PMA_REG_PHY_IDENTIFIER,
				&val);

		अगर (tx_en)
			val &= ~(1<<15);
		अन्यथा
			val |= (1<<15);

		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD,
				 MDIO_PMA_REG_PHY_IDENTIFIER,
				 val);
	अवरोध;
	हाल PORT_HW_CFG_TX_LASER_GPIO0:
	हाल PORT_HW_CFG_TX_LASER_GPIO1:
	हाल PORT_HW_CFG_TX_LASER_GPIO2:
	हाल PORT_HW_CFG_TX_LASER_GPIO3:
	अणु
		u16 gpio_pin;
		u8 gpio_port, gpio_mode;
		अगर (tx_en)
			gpio_mode = MISC_REGISTERS_GPIO_OUTPUT_HIGH;
		अन्यथा
			gpio_mode = MISC_REGISTERS_GPIO_OUTPUT_LOW;

		gpio_pin = tx_en_mode - PORT_HW_CFG_TX_LASER_GPIO0;
		gpio_port = bnx2x_get_gpio_port(params);
		bnx2x_set_gpio(bp, gpio_pin, gpio_mode, gpio_port);
		अवरोध;
	पूर्ण
	शेष:
		DP(NETIF_MSG_LINK, "Invalid TX_LASER_MDIO 0x%x\n", tx_en_mode);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम bnx2x_sfp_set_transmitter(काष्ठा link_params *params,
				      काष्ठा bnx2x_phy *phy,
				      u8 tx_en)
अणु
	काष्ठा bnx2x *bp = params->bp;
	DP(NETIF_MSG_LINK, "Setting SFP+ transmitter to %d\n", tx_en);
	अगर (CHIP_IS_E3(bp))
		bnx2x_sfp_e3_set_transmitter(params, phy, tx_en);
	अन्यथा
		bnx2x_sfp_e1e2_set_transmitter(params, phy, tx_en);
पूर्ण

अटल पूर्णांक bnx2x_8726_पढ़ो_sfp_module_eeprom(काष्ठा bnx2x_phy *phy,
					     काष्ठा link_params *params,
					     u8 dev_addr, u16 addr, u8 byte_cnt,
					     u8 *o_buf, u8 is_init)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 val = 0;
	u16 i;
	अगर (byte_cnt > SFP_EEPROM_PAGE_SIZE) अणु
		DP(NETIF_MSG_LINK,
		   "Reading from eeprom is limited to 0xf\n");
		वापस -EINVAL;
	पूर्ण
	/* Set the पढ़ो command byte count */
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD, MDIO_PMA_REG_SFP_TWO_WIRE_BYTE_CNT,
			 (byte_cnt | (dev_addr << 8)));

	/* Set the पढ़ो command address */
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD, MDIO_PMA_REG_SFP_TWO_WIRE_MEM_ADDR,
			 addr);

	/* Activate पढ़ो command */
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD, MDIO_PMA_REG_SFP_TWO_WIRE_CTRL,
			 0x2c0f);

	/* Wait up to 500us क्रम command complete status */
	क्रम (i = 0; i < 100; i++) अणु
		bnx2x_cl45_पढ़ो(bp, phy,
				MDIO_PMA_DEVAD,
				MDIO_PMA_REG_SFP_TWO_WIRE_CTRL, &val);
		अगर ((val & MDIO_PMA_REG_SFP_TWO_WIRE_CTRL_STATUS_MASK) ==
		    MDIO_PMA_REG_SFP_TWO_WIRE_STATUS_COMPLETE)
			अवरोध;
		udelay(5);
	पूर्ण

	अगर ((val & MDIO_PMA_REG_SFP_TWO_WIRE_CTRL_STATUS_MASK) !=
		    MDIO_PMA_REG_SFP_TWO_WIRE_STATUS_COMPLETE) अणु
		DP(NETIF_MSG_LINK,
			 "Got bad status 0x%x when reading from SFP+ EEPROM\n",
			 (val & MDIO_PMA_REG_SFP_TWO_WIRE_CTRL_STATUS_MASK));
		वापस -EINVAL;
	पूर्ण

	/* Read the buffer */
	क्रम (i = 0; i < byte_cnt; i++) अणु
		bnx2x_cl45_पढ़ो(bp, phy,
				MDIO_PMA_DEVAD,
				MDIO_PMA_REG_8726_TWO_WIRE_DATA_BUF + i, &val);
		o_buf[i] = (u8)(val & MDIO_PMA_REG_8726_TWO_WIRE_DATA_MASK);
	पूर्ण

	क्रम (i = 0; i < 100; i++) अणु
		bnx2x_cl45_पढ़ो(bp, phy,
				MDIO_PMA_DEVAD,
				MDIO_PMA_REG_SFP_TWO_WIRE_CTRL, &val);
		अगर ((val & MDIO_PMA_REG_SFP_TWO_WIRE_CTRL_STATUS_MASK) ==
		    MDIO_PMA_REG_SFP_TWO_WIRE_STATUS_IDLE)
			वापस 0;
		usleep_range(1000, 2000);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल व्योम bnx2x_warpcore_घातer_module(काष्ठा link_params *params,
					u8 घातer)
अणु
	u32 pin_cfg;
	काष्ठा bnx2x *bp = params->bp;

	pin_cfg = (REG_RD(bp, params->shmem_base +
			  दुरत्व(काष्ठा shmem_region,
			dev_info.port_hw_config[params->port].e3_sfp_ctrl)) &
			PORT_HW_CFG_E3_PWR_DIS_MASK) >>
			PORT_HW_CFG_E3_PWR_DIS_SHIFT;

	अगर (pin_cfg == PIN_CFG_NA)
		वापस;
	DP(NETIF_MSG_LINK, "Setting SFP+ module power to %d using pin cfg %d\n",
		       घातer, pin_cfg);
	/* Low ==> corresponding SFP+ module is घातered
	 * high ==> the SFP+ module is घातered करोwn
	 */
	bnx2x_set_cfg_pin(bp, pin_cfg, घातer ^ 1);
पूर्ण
अटल पूर्णांक bnx2x_warpcore_पढ़ो_sfp_module_eeprom(काष्ठा bnx2x_phy *phy,
						 काष्ठा link_params *params,
						 u8 dev_addr,
						 u16 addr, u8 byte_cnt,
						 u8 *o_buf, u8 is_init)
अणु
	पूर्णांक rc = 0;
	u8 i, j = 0, cnt = 0;
	u32 data_array[4];
	u16 addr32;
	काष्ठा bnx2x *bp = params->bp;

	अगर (byte_cnt > SFP_EEPROM_PAGE_SIZE) अणु
		DP(NETIF_MSG_LINK,
		   "Reading from eeprom is limited to 16 bytes\n");
		वापस -EINVAL;
	पूर्ण

	/* 4 byte aligned address */
	addr32 = addr & (~0x3);
	करो अणु
		अगर ((!is_init) && (cnt == I2C_WA_PWR_ITER)) अणु
			bnx2x_warpcore_घातer_module(params, 0);
			/* Note that 100us are not enough here */
			usleep_range(1000, 2000);
			bnx2x_warpcore_घातer_module(params, 1);
		पूर्ण
		rc = bnx2x_bsc_पढ़ो(params, bp, dev_addr, addr32, 0, byte_cnt,
				    data_array);
	पूर्ण जबतक ((rc != 0) && (++cnt < I2C_WA_RETRY_CNT));

	अगर (rc == 0) अणु
		क्रम (i = (addr - addr32); i < byte_cnt + (addr - addr32); i++) अणु
			o_buf[j] = *((u8 *)data_array + i);
			j++;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक bnx2x_8727_पढ़ो_sfp_module_eeprom(काष्ठा bnx2x_phy *phy,
					     काष्ठा link_params *params,
					     u8 dev_addr, u16 addr, u8 byte_cnt,
					     u8 *o_buf, u8 is_init)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 val, i;

	अगर (byte_cnt > SFP_EEPROM_PAGE_SIZE) अणु
		DP(NETIF_MSG_LINK,
		   "Reading from eeprom is limited to 0xf\n");
		वापस -EINVAL;
	पूर्ण

	/* Set 2-wire transfer rate of SFP+ module EEPROM
	 * to 100Khz since some DACs(direct attached cables) करो
	 * not work at 400Khz.
	 */
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_8727_TWO_WIRE_SLAVE_ADDR,
			 ((dev_addr << 8) | 1));

	/* Need to पढ़ो from 1.8000 to clear it */
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD,
			MDIO_PMA_REG_SFP_TWO_WIRE_CTRL,
			&val);

	/* Set the पढ़ो command byte count */
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_SFP_TWO_WIRE_BYTE_CNT,
			 ((byte_cnt < 2) ? 2 : byte_cnt));

	/* Set the पढ़ो command address */
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_SFP_TWO_WIRE_MEM_ADDR,
			 addr);
	/* Set the destination address */
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD,
			 0x8004,
			 MDIO_PMA_REG_8727_TWO_WIRE_DATA_BUF);

	/* Activate पढ़ो command */
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_SFP_TWO_WIRE_CTRL,
			 0x8002);
	/* Wait appropriate समय क्रम two-wire command to finish beक्रमe
	 * polling the status रेजिस्टर
	 */
	usleep_range(1000, 2000);

	/* Wait up to 500us क्रम command complete status */
	क्रम (i = 0; i < 100; i++) अणु
		bnx2x_cl45_पढ़ो(bp, phy,
				MDIO_PMA_DEVAD,
				MDIO_PMA_REG_SFP_TWO_WIRE_CTRL, &val);
		अगर ((val & MDIO_PMA_REG_SFP_TWO_WIRE_CTRL_STATUS_MASK) ==
		    MDIO_PMA_REG_SFP_TWO_WIRE_STATUS_COMPLETE)
			अवरोध;
		udelay(5);
	पूर्ण

	अगर ((val & MDIO_PMA_REG_SFP_TWO_WIRE_CTRL_STATUS_MASK) !=
		    MDIO_PMA_REG_SFP_TWO_WIRE_STATUS_COMPLETE) अणु
		DP(NETIF_MSG_LINK,
			 "Got bad status 0x%x when reading from SFP+ EEPROM\n",
			 (val & MDIO_PMA_REG_SFP_TWO_WIRE_CTRL_STATUS_MASK));
		वापस -EFAULT;
	पूर्ण

	/* Read the buffer */
	क्रम (i = 0; i < byte_cnt; i++) अणु
		bnx2x_cl45_पढ़ो(bp, phy,
				MDIO_PMA_DEVAD,
				MDIO_PMA_REG_8727_TWO_WIRE_DATA_BUF + i, &val);
		o_buf[i] = (u8)(val & MDIO_PMA_REG_8727_TWO_WIRE_DATA_MASK);
	पूर्ण

	क्रम (i = 0; i < 100; i++) अणु
		bnx2x_cl45_पढ़ो(bp, phy,
				MDIO_PMA_DEVAD,
				MDIO_PMA_REG_SFP_TWO_WIRE_CTRL, &val);
		अगर ((val & MDIO_PMA_REG_SFP_TWO_WIRE_CTRL_STATUS_MASK) ==
		    MDIO_PMA_REG_SFP_TWO_WIRE_STATUS_IDLE)
			वापस 0;
		usleep_range(1000, 2000);
	पूर्ण

	वापस -EINVAL;
पूर्ण
पूर्णांक bnx2x_पढ़ो_sfp_module_eeprom(काष्ठा bnx2x_phy *phy,
				 काष्ठा link_params *params, u8 dev_addr,
				 u16 addr, u16 byte_cnt, u8 *o_buf)
अणु
	पूर्णांक rc = 0;
	काष्ठा bnx2x *bp = params->bp;
	u8 xfer_size;
	u8 *user_data = o_buf;
	पढ़ो_sfp_module_eeprom_func_p पढ़ो_func;

	अगर ((dev_addr != 0xa0) && (dev_addr != 0xa2)) अणु
		DP(NETIF_MSG_LINK, "invalid dev_addr 0x%x\n", dev_addr);
		वापस -EINVAL;
	पूर्ण

	चयन (phy->type) अणु
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8726:
		पढ़ो_func = bnx2x_8726_पढ़ो_sfp_module_eeprom;
		अवरोध;
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8727:
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8722:
		पढ़ो_func = bnx2x_8727_पढ़ो_sfp_module_eeprom;
		अवरोध;
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_सूचीECT:
		पढ़ो_func = bnx2x_warpcore_पढ़ो_sfp_module_eeprom;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	जबतक (!rc && (byte_cnt > 0)) अणु
		xfer_size = (byte_cnt > SFP_EEPROM_PAGE_SIZE) ?
			SFP_EEPROM_PAGE_SIZE : byte_cnt;
		rc = पढ़ो_func(phy, params, dev_addr, addr, xfer_size,
			       user_data, 0);
		byte_cnt -= xfer_size;
		user_data += xfer_size;
		addr += xfer_size;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक bnx2x_get_edc_mode(काष्ठा bnx2x_phy *phy,
			      काष्ठा link_params *params,
			      u16 *edc_mode)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u32 sync_offset = 0, phy_idx, media_types;
	u8 val[SFP_EEPROM_FC_TX_TECH_ADDR + 1], check_limiting_mode = 0;
	*edc_mode = EDC_MODE_LIMITING;
	phy->media_type = ETH_PHY_UNSPECIFIED;
	/* First check क्रम copper cable */
	अगर (bnx2x_पढ़ो_sfp_module_eeprom(phy,
					 params,
					 I2C_DEV_ADDR_A0,
					 0,
					 SFP_EEPROM_FC_TX_TECH_ADDR + 1,
					 (u8 *)val) != 0) अणु
		DP(NETIF_MSG_LINK, "Failed to read from SFP+ module EEPROM\n");
		वापस -EINVAL;
	पूर्ण
	params->link_attr_sync &= ~LINK_SFP_EEPROM_COMP_CODE_MASK;
	params->link_attr_sync |= val[SFP_EEPROM_10G_COMP_CODE_ADDR] <<
		LINK_SFP_EEPROM_COMP_CODE_SHIFT;
	bnx2x_update_link_attr(params, params->link_attr_sync);
	चयन (val[SFP_EEPROM_CON_TYPE_ADDR]) अणु
	हाल SFP_EEPROM_CON_TYPE_VAL_COPPER:
	अणु
		u8 copper_module_type;
		phy->media_type = ETH_PHY_DA_TWINAX;
		/* Check अगर its active cable (includes SFP+ module)
		 * of passive cable
		 */
		copper_module_type = val[SFP_EEPROM_FC_TX_TECH_ADDR];

		अगर (copper_module_type &
		    SFP_EEPROM_FC_TX_TECH_BITMASK_COPPER_ACTIVE) अणु
			DP(NETIF_MSG_LINK, "Active Copper cable detected\n");
			अगर (phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_सूचीECT)
				*edc_mode = EDC_MODE_ACTIVE_DAC;
			अन्यथा
				check_limiting_mode = 1;
		पूर्ण अन्यथा अणु
			*edc_mode = EDC_MODE_PASSIVE_DAC;
			/* Even in हाल PASSIVE_DAC indication is not set,
			 * treat it as a passive DAC cable, since some cables
			 * करोn't have this indication.
			 */
			अगर (copper_module_type &
			    SFP_EEPROM_FC_TX_TECH_BITMASK_COPPER_PASSIVE) अणु
				DP(NETIF_MSG_LINK,
				   "Passive Copper cable detected\n");
			पूर्ण अन्यथा अणु
				DP(NETIF_MSG_LINK,
				   "Unknown copper-cable-type\n");
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
	हाल SFP_EEPROM_CON_TYPE_VAL_UNKNOWN:
	हाल SFP_EEPROM_CON_TYPE_VAL_LC:
	हाल SFP_EEPROM_CON_TYPE_VAL_RJ45:
		check_limiting_mode = 1;
		अगर (((val[SFP_EEPROM_10G_COMP_CODE_ADDR] &
		     (SFP_EEPROM_10G_COMP_CODE_SR_MASK |
		      SFP_EEPROM_10G_COMP_CODE_LR_MASK |
		       SFP_EEPROM_10G_COMP_CODE_LRM_MASK)) == 0) &&
		    (val[SFP_EEPROM_1G_COMP_CODE_ADDR] != 0)) अणु
			DP(NETIF_MSG_LINK, "1G SFP module detected\n");
			phy->media_type = ETH_PHY_SFP_1G_FIBER;
			अगर (phy->req_line_speed != SPEED_1000) अणु
				u8 gport = params->port;
				phy->req_line_speed = SPEED_1000;
				अगर (!CHIP_IS_E1x(bp)) अणु
					gport = BP_PATH(bp) +
					(params->port << 1);
				पूर्ण
				netdev_err(bp->dev,
					   "Warning: Link speed was forced to 1000Mbps. Current SFP module in port %d is not compliant with 10G Ethernet\n",
					   gport);
			पूर्ण
			अगर (val[SFP_EEPROM_1G_COMP_CODE_ADDR] &
			    SFP_EEPROM_1G_COMP_CODE_BASE_T) अणु
				bnx2x_sfp_set_transmitter(params, phy, 0);
				msleep(40);
				bnx2x_sfp_set_transmitter(params, phy, 1);
			पूर्ण
		पूर्ण अन्यथा अणु
			पूर्णांक idx, cfg_idx = 0;
			DP(NETIF_MSG_LINK, "10G Optic module detected\n");
			क्रम (idx = INT_PHY; idx < MAX_PHYS; idx++) अणु
				अगर (params->phy[idx].type == phy->type) अणु
					cfg_idx = LINK_CONFIG_IDX(idx);
					अवरोध;
				पूर्ण
			पूर्ण
			phy->media_type = ETH_PHY_SFPP_10G_FIBER;
			phy->req_line_speed = params->req_line_speed[cfg_idx];
		पूर्ण
		अवरोध;
	शेष:
		DP(NETIF_MSG_LINK, "Unable to determine module type 0x%x !!!\n",
			 val[SFP_EEPROM_CON_TYPE_ADDR]);
		वापस -EINVAL;
	पूर्ण
	sync_offset = params->shmem_base +
		दुरत्व(काष्ठा shmem_region,
			 dev_info.port_hw_config[params->port].media_type);
	media_types = REG_RD(bp, sync_offset);
	/* Update media type क्रम non-PMF sync */
	क्रम (phy_idx = INT_PHY; phy_idx < MAX_PHYS; phy_idx++) अणु
		अगर (&(params->phy[phy_idx]) == phy) अणु
			media_types &= ~(PORT_HW_CFG_MEDIA_TYPE_PHY0_MASK <<
				(PORT_HW_CFG_MEDIA_TYPE_PHY1_SHIFT * phy_idx));
			media_types |= ((phy->media_type &
					PORT_HW_CFG_MEDIA_TYPE_PHY0_MASK) <<
				(PORT_HW_CFG_MEDIA_TYPE_PHY1_SHIFT * phy_idx));
			अवरोध;
		पूर्ण
	पूर्ण
	REG_WR(bp, sync_offset, media_types);
	अगर (check_limiting_mode) अणु
		u8 options[SFP_EEPROM_OPTIONS_SIZE];
		अगर (bnx2x_पढ़ो_sfp_module_eeprom(phy,
						 params,
						 I2C_DEV_ADDR_A0,
						 SFP_EEPROM_OPTIONS_ADDR,
						 SFP_EEPROM_OPTIONS_SIZE,
						 options) != 0) अणु
			DP(NETIF_MSG_LINK,
			   "Failed to read Option field from module EEPROM\n");
			वापस -EINVAL;
		पूर्ण
		अगर ((options[0] & SFP_EEPROM_OPTIONS_LINEAR_RX_OUT_MASK))
			*edc_mode = EDC_MODE_LINEAR;
		अन्यथा
			*edc_mode = EDC_MODE_LIMITING;
	पूर्ण
	DP(NETIF_MSG_LINK, "EDC mode is set to 0x%x\n", *edc_mode);
	वापस 0;
पूर्ण
/* This function पढ़ो the relevant field from the module (SFP+), and verअगरy it
 * is compliant with this board
 */
अटल पूर्णांक bnx2x_verअगरy_sfp_module(काष्ठा bnx2x_phy *phy,
				   काष्ठा link_params *params)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u32 val, cmd;
	u32 fw_resp, fw_cmd_param;
	अक्षर venकरोr_name[SFP_EEPROM_VENDOR_NAME_SIZE+1];
	अक्षर venकरोr_pn[SFP_EEPROM_PART_NO_SIZE+1];
	phy->flags &= ~FLAGS_SFP_NOT_APPROVED;
	val = REG_RD(bp, params->shmem_base +
			 दुरत्व(काष्ठा shmem_region, dev_info.
				  port_feature_config[params->port].config));
	अगर ((val & PORT_FEAT_CFG_OPT_MDL_ENFRCMNT_MASK) ==
	    PORT_FEAT_CFG_OPT_MDL_ENFRCMNT_NO_ENFORCEMENT) अणु
		DP(NETIF_MSG_LINK, "NOT enforcing module verification\n");
		वापस 0;
	पूर्ण

	अगर (params->feature_config_flags &
	    FEATURE_CONFIG_BC_SUPPORTS_DUAL_PHY_OPT_MDL_VRFY) अणु
		/* Use specअगरic phy request */
		cmd = DRV_MSG_CODE_VRFY_SPECIFIC_PHY_OPT_MDL;
	पूर्ण अन्यथा अगर (params->feature_config_flags &
		   FEATURE_CONFIG_BC_SUPPORTS_OPT_MDL_VRFY) अणु
		/* Use first phy request only in हाल of non-dual media*/
		अगर (DUAL_MEDIA(params)) अणु
			DP(NETIF_MSG_LINK,
			   "FW does not support OPT MDL verification\n");
			वापस -EINVAL;
		पूर्ण
		cmd = DRV_MSG_CODE_VRFY_FIRST_PHY_OPT_MDL;
	पूर्ण अन्यथा अणु
		/* No support in OPT MDL detection */
		DP(NETIF_MSG_LINK,
		   "FW does not support OPT MDL verification\n");
		वापस -EINVAL;
	पूर्ण

	fw_cmd_param = FW_PARAM_SET(phy->addr, phy->type, phy->mdio_ctrl);
	fw_resp = bnx2x_fw_command(bp, cmd, fw_cmd_param);
	अगर (fw_resp == FW_MSG_CODE_VRFY_OPT_MDL_SUCCESS) अणु
		DP(NETIF_MSG_LINK, "Approved module\n");
		वापस 0;
	पूर्ण

	/* Format the warning message */
	अगर (bnx2x_पढ़ो_sfp_module_eeprom(phy,
					 params,
					 I2C_DEV_ADDR_A0,
					 SFP_EEPROM_VENDOR_NAME_ADDR,
					 SFP_EEPROM_VENDOR_NAME_SIZE,
					 (u8 *)venकरोr_name))
		venकरोr_name[0] = '\0';
	अन्यथा
		venकरोr_name[SFP_EEPROM_VENDOR_NAME_SIZE] = '\0';
	अगर (bnx2x_पढ़ो_sfp_module_eeprom(phy,
					 params,
					 I2C_DEV_ADDR_A0,
					 SFP_EEPROM_PART_NO_ADDR,
					 SFP_EEPROM_PART_NO_SIZE,
					 (u8 *)venकरोr_pn))
		venकरोr_pn[0] = '\0';
	अन्यथा
		venकरोr_pn[SFP_EEPROM_PART_NO_SIZE] = '\0';

	netdev_err(bp->dev,  "Warning: Unqualified SFP+ module detected,"
			      " Port %d from %s part number %s\n",
			 params->port, venकरोr_name, venकरोr_pn);
	अगर ((val & PORT_FEAT_CFG_OPT_MDL_ENFRCMNT_MASK) !=
	    PORT_FEAT_CFG_OPT_MDL_ENFRCMNT_WARNING_MSG)
		phy->flags |= FLAGS_SFP_NOT_APPROVED;
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक bnx2x_रुको_क्रम_sfp_module_initialized(काष्ठा bnx2x_phy *phy,
						 काष्ठा link_params *params)

अणु
	u8 val;
	पूर्णांक rc;
	काष्ठा bnx2x *bp = params->bp;
	u16 समयout;
	/* Initialization समय after hot-plug may take up to 300ms क्रम
	 * some phys type ( e.g. JDSU )
	 */

	क्रम (समयout = 0; समयout < 60; समयout++) अणु
		अगर (phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_सूचीECT)
			rc = bnx2x_warpcore_पढ़ो_sfp_module_eeprom(
				phy, params, I2C_DEV_ADDR_A0, 1, 1, &val,
				1);
		अन्यथा
			rc = bnx2x_पढ़ो_sfp_module_eeprom(phy, params,
							  I2C_DEV_ADDR_A0,
							  1, 1, &val);
		अगर (rc == 0) अणु
			DP(NETIF_MSG_LINK,
			   "SFP+ module initialization took %d ms\n",
			   समयout * 5);
			वापस 0;
		पूर्ण
		usleep_range(5000, 10000);
	पूर्ण
	rc = bnx2x_पढ़ो_sfp_module_eeprom(phy, params, I2C_DEV_ADDR_A0,
					  1, 1, &val);
	वापस rc;
पूर्ण

अटल व्योम bnx2x_8727_घातer_module(काष्ठा bnx2x *bp,
				    काष्ठा bnx2x_phy *phy,
				    u8 is_घातer_up) अणु
	/* Make sure GPIOs are not using क्रम LED mode */
	u16 val;
	/* In the GPIO रेजिस्टर, bit 4 is use to determine अगर the GPIOs are
	 * operating as INPUT or as OUTPUT. Bit 1 is क्रम input, and 0 क्रम
	 * output
	 * Bits 0-1 determine the GPIOs value क्रम OUTPUT in हाल bit 4 val is 0
	 * Bits 8-9 determine the GPIOs value क्रम INPUT in हाल bit 4 val is 1
	 * where the 1st bit is the over-current(only input), and 2nd bit is
	 * क्रम घातer( only output )
	 *
	 * In हाल of NOC feature is disabled and घातer is up, set GPIO control
	 *  as input to enable listening of over-current indication
	 */
	अगर (phy->flags & FLAGS_NOC)
		वापस;
	अगर (is_घातer_up)
		val = (1<<4);
	अन्यथा
		/* Set GPIO control to OUTPUT, and set the घातer bit
		 * to according to the is_घातer_up
		 */
		val = (1<<1);

	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_8727_GPIO_CTRL,
			 val);
पूर्ण

अटल पूर्णांक bnx2x_8726_set_limiting_mode(काष्ठा bnx2x *bp,
					काष्ठा bnx2x_phy *phy,
					u16 edc_mode)
अणु
	u16 cur_limiting_mode;

	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD,
			MDIO_PMA_REG_ROM_VER2,
			&cur_limiting_mode);
	DP(NETIF_MSG_LINK, "Current Limiting mode is 0x%x\n",
		 cur_limiting_mode);

	अगर (edc_mode == EDC_MODE_LIMITING) अणु
		DP(NETIF_MSG_LINK, "Setting LIMITING MODE\n");
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD,
				 MDIO_PMA_REG_ROM_VER2,
				 EDC_MODE_LIMITING);
	पूर्ण अन्यथा अणु /* LRM mode ( शेष )*/

		DP(NETIF_MSG_LINK, "Setting LRM MODE\n");

		/* Changing to LRM mode takes quite few seconds. So करो it only
		 * अगर current mode is limiting (शेष is LRM)
		 */
		अगर (cur_limiting_mode != EDC_MODE_LIMITING)
			वापस 0;

		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD,
				 MDIO_PMA_REG_LRM_MODE,
				 0);
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD,
				 MDIO_PMA_REG_ROM_VER2,
				 0x128);
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD,
				 MDIO_PMA_REG_MISC_CTRL0,
				 0x4008);
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD,
				 MDIO_PMA_REG_LRM_MODE,
				 0xaaaa);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_8727_set_limiting_mode(काष्ठा bnx2x *bp,
					काष्ठा bnx2x_phy *phy,
					u16 edc_mode)
अणु
	u16 phy_identअगरier;
	u16 rom_ver2_val;
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD,
			MDIO_PMA_REG_PHY_IDENTIFIER,
			&phy_identअगरier);

	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_PHY_IDENTIFIER,
			 (phy_identअगरier & ~(1<<9)));

	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD,
			MDIO_PMA_REG_ROM_VER2,
			&rom_ver2_val);
	/* Keep the MSB 8-bits, and set the LSB 8-bits with the edc_mode */
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_ROM_VER2,
			 (rom_ver2_val & 0xff00) | (edc_mode & 0x00ff));

	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_PHY_IDENTIFIER,
			 (phy_identअगरier | (1<<9)));

	वापस 0;
पूर्ण

अटल व्योम bnx2x_8727_specअगरic_func(काष्ठा bnx2x_phy *phy,
				     काष्ठा link_params *params,
				     u32 action)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 val;
	चयन (action) अणु
	हाल DISABLE_TX:
		bnx2x_sfp_set_transmitter(params, phy, 0);
		अवरोध;
	हाल ENABLE_TX:
		अगर (!(phy->flags & FLAGS_SFP_NOT_APPROVED))
			bnx2x_sfp_set_transmitter(params, phy, 1);
		अवरोध;
	हाल PHY_INIT:
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_LASI_RXCTRL,
				 (1<<2) | (1<<5));
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_LASI_TXCTRL,
				 0);
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_LASI_CTRL, 0x0006);
		/* Make MOD_ABS give पूर्णांकerrupt on change */
		bnx2x_cl45_पढ़ो(bp, phy, MDIO_PMA_DEVAD,
				MDIO_PMA_REG_8727_PCS_OPT_CTRL,
				&val);
		val |= (1<<12);
		अगर (phy->flags & FLAGS_NOC)
			val |= (3<<5);
		/* Set 8727 GPIOs to input to allow पढ़ोing from the 8727 GPIO0
		 * status which reflect SFP+ module over-current
		 */
		अगर (!(phy->flags & FLAGS_NOC))
			val &= 0xff8f; /* Reset bits 4-6 */
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_REG_8727_PCS_OPT_CTRL,
				 val);
		अवरोध;
	शेष:
		DP(NETIF_MSG_LINK, "Function 0x%x not supported by 8727\n",
		   action);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम bnx2x_set_e1e2_module_fault_led(काष्ठा link_params *params,
					   u8 gpio_mode)
अणु
	काष्ठा bnx2x *bp = params->bp;

	u32 fault_led_gpio = REG_RD(bp, params->shmem_base +
			    दुरत्व(काष्ठा shmem_region,
			dev_info.port_hw_config[params->port].sfp_ctrl)) &
		PORT_HW_CFG_FAULT_MODULE_LED_MASK;
	चयन (fault_led_gpio) अणु
	हाल PORT_HW_CFG_FAULT_MODULE_LED_DISABLED:
		वापस;
	हाल PORT_HW_CFG_FAULT_MODULE_LED_GPIO0:
	हाल PORT_HW_CFG_FAULT_MODULE_LED_GPIO1:
	हाल PORT_HW_CFG_FAULT_MODULE_LED_GPIO2:
	हाल PORT_HW_CFG_FAULT_MODULE_LED_GPIO3:
	अणु
		u8 gpio_port = bnx2x_get_gpio_port(params);
		u16 gpio_pin = fault_led_gpio -
			PORT_HW_CFG_FAULT_MODULE_LED_GPIO0;
		DP(NETIF_MSG_LINK, "Set fault module-detected led "
				   "pin %x port %x mode %x\n",
			       gpio_pin, gpio_port, gpio_mode);
		bnx2x_set_gpio(bp, gpio_pin, gpio_mode, gpio_port);
	पूर्ण
	अवरोध;
	शेष:
		DP(NETIF_MSG_LINK, "Error: Invalid fault led mode 0x%x\n",
			       fault_led_gpio);
	पूर्ण
पूर्ण

अटल व्योम bnx2x_set_e3_module_fault_led(काष्ठा link_params *params,
					  u8 gpio_mode)
अणु
	u32 pin_cfg;
	u8 port = params->port;
	काष्ठा bnx2x *bp = params->bp;
	pin_cfg = (REG_RD(bp, params->shmem_base +
			 दुरत्व(काष्ठा shmem_region,
				  dev_info.port_hw_config[port].e3_sfp_ctrl)) &
		PORT_HW_CFG_E3_FAULT_MDL_LED_MASK) >>
		PORT_HW_CFG_E3_FAULT_MDL_LED_SHIFT;
	DP(NETIF_MSG_LINK, "Setting Fault LED to %d using pin cfg %d\n",
		       gpio_mode, pin_cfg);
	bnx2x_set_cfg_pin(bp, pin_cfg, gpio_mode);
पूर्ण

अटल व्योम bnx2x_set_sfp_module_fault_led(काष्ठा link_params *params,
					   u8 gpio_mode)
अणु
	काष्ठा bnx2x *bp = params->bp;
	DP(NETIF_MSG_LINK, "Setting SFP+ module fault LED to %d\n", gpio_mode);
	अगर (CHIP_IS_E3(bp)) अणु
		/* Low ==> अगर SFP+ module is supported otherwise
		 * High ==> अगर SFP+ module is not on the approved venकरोr list
		 */
		bnx2x_set_e3_module_fault_led(params, gpio_mode);
	पूर्ण अन्यथा
		bnx2x_set_e1e2_module_fault_led(params, gpio_mode);
पूर्ण

अटल व्योम bnx2x_warpcore_hw_reset(काष्ठा bnx2x_phy *phy,
				    काष्ठा link_params *params)
अणु
	काष्ठा bnx2x *bp = params->bp;
	bnx2x_warpcore_घातer_module(params, 0);
	/* Put Warpcore in low घातer mode */
	REG_WR(bp, MISC_REG_WC0_RESET, 0x0c0e);

	/* Put LCPLL in low घातer mode */
	REG_WR(bp, MISC_REG_LCPLL_E40_PWRDWN, 1);
	REG_WR(bp, MISC_REG_LCPLL_E40_RESETB_ANA, 0);
	REG_WR(bp, MISC_REG_LCPLL_E40_RESETB_DIG, 0);
पूर्ण

अटल व्योम bnx2x_घातer_sfp_module(काष्ठा link_params *params,
				   काष्ठा bnx2x_phy *phy,
				   u8 घातer)
अणु
	काष्ठा bnx2x *bp = params->bp;
	DP(NETIF_MSG_LINK, "Setting SFP+ power to %x\n", घातer);

	चयन (phy->type) अणु
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8727:
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8722:
		bnx2x_8727_घातer_module(params->bp, phy, घातer);
		अवरोध;
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_सूचीECT:
		bnx2x_warpcore_घातer_module(params, घातer);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण
अटल व्योम bnx2x_warpcore_set_limiting_mode(काष्ठा link_params *params,
					     काष्ठा bnx2x_phy *phy,
					     u16 edc_mode)
अणु
	u16 val = 0;
	u16 mode = MDIO_WC_REG_UC_INFO_B1_FIRMWARE_MODE_DEFAULT;
	काष्ठा bnx2x *bp = params->bp;

	u8 lane = bnx2x_get_warpcore_lane(phy, params);
	/* This is a global रेजिस्टर which controls all lanes */
	bnx2x_cl45_पढ़ो(bp, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_UC_INFO_B1_FIRMWARE_MODE, &val);
	val &= ~(0xf << (lane << 2));

	चयन (edc_mode) अणु
	हाल EDC_MODE_LINEAR:
	हाल EDC_MODE_LIMITING:
		mode = MDIO_WC_REG_UC_INFO_B1_FIRMWARE_MODE_DEFAULT;
		अवरोध;
	हाल EDC_MODE_PASSIVE_DAC:
	हाल EDC_MODE_ACTIVE_DAC:
		mode = MDIO_WC_REG_UC_INFO_B1_FIRMWARE_MODE_SFP_DAC;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	val |= (mode << (lane << 2));
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_WC_DEVAD,
			 MDIO_WC_REG_UC_INFO_B1_FIRMWARE_MODE, val);
	/* A must पढ़ो */
	bnx2x_cl45_पढ़ो(bp, phy, MDIO_WC_DEVAD,
			MDIO_WC_REG_UC_INFO_B1_FIRMWARE_MODE, &val);

	/* Restart microcode to re-पढ़ो the new mode */
	bnx2x_warpcore_reset_lane(bp, phy, 1);
	bnx2x_warpcore_reset_lane(bp, phy, 0);

पूर्ण

अटल व्योम bnx2x_set_limiting_mode(काष्ठा link_params *params,
				    काष्ठा bnx2x_phy *phy,
				    u16 edc_mode)
अणु
	चयन (phy->type) अणु
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8726:
		bnx2x_8726_set_limiting_mode(params->bp, phy, edc_mode);
		अवरोध;
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8727:
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8722:
		bnx2x_8727_set_limiting_mode(params->bp, phy, edc_mode);
		अवरोध;
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_सूचीECT:
		bnx2x_warpcore_set_limiting_mode(params, phy, edc_mode);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_sfp_module_detection(काष्ठा bnx2x_phy *phy,
				      काष्ठा link_params *params)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 edc_mode;
	पूर्णांक rc = 0;

	u32 val = REG_RD(bp, params->shmem_base +
			     दुरत्व(काष्ठा shmem_region, dev_info.
				     port_feature_config[params->port].config));
	/* Enabled transmitter by शेष */
	bnx2x_sfp_set_transmitter(params, phy, 1);
	DP(NETIF_MSG_LINK, "SFP+ module plugged in/out detected on port %d\n",
		 params->port);
	/* Power up module */
	bnx2x_घातer_sfp_module(params, phy, 1);
	अगर (bnx2x_get_edc_mode(phy, params, &edc_mode) != 0) अणु
		DP(NETIF_MSG_LINK, "Failed to get valid module type\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (bnx2x_verअगरy_sfp_module(phy, params) != 0) अणु
		/* Check SFP+ module compatibility */
		DP(NETIF_MSG_LINK, "Module verification failed!!\n");
		rc = -EINVAL;
		/* Turn on fault module-detected led */
		bnx2x_set_sfp_module_fault_led(params,
					       MISC_REGISTERS_GPIO_HIGH);

		/* Check अगर need to घातer करोwn the SFP+ module */
		अगर ((val & PORT_FEAT_CFG_OPT_MDL_ENFRCMNT_MASK) ==
		     PORT_FEAT_CFG_OPT_MDL_ENFRCMNT_POWER_DOWN) अणु
			DP(NETIF_MSG_LINK, "Shutdown SFP+ module!!\n");
			bnx2x_घातer_sfp_module(params, phy, 0);
			वापस rc;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Turn off fault module-detected led */
		bnx2x_set_sfp_module_fault_led(params, MISC_REGISTERS_GPIO_LOW);
	पूर्ण

	/* Check and set limiting mode / LRM mode on 8726. On 8727 it
	 * is करोne स्वतःmatically
	 */
	bnx2x_set_limiting_mode(params, phy, edc_mode);

	/* Disable transmit क्रम this module अगर the module is not approved, and
	 * laser needs to be disabled.
	 */
	अगर ((rc) &&
	    ((val & PORT_FEAT_CFG_OPT_MDL_ENFRCMNT_MASK) ==
	     PORT_FEAT_CFG_OPT_MDL_ENFRCMNT_DISABLE_TX_LASER))
		bnx2x_sfp_set_transmitter(params, phy, 0);

	वापस rc;
पूर्ण

व्योम bnx2x_handle_module_detect_पूर्णांक(काष्ठा link_params *params)
अणु
	काष्ठा bnx2x *bp = params->bp;
	काष्ठा bnx2x_phy *phy;
	u32 gpio_val;
	u8 gpio_num, gpio_port;
	अगर (CHIP_IS_E3(bp)) अणु
		phy = &params->phy[INT_PHY];
		/* Always enable TX laser,will be disabled in हाल of fault */
		bnx2x_sfp_set_transmitter(params, phy, 1);
	पूर्ण अन्यथा अणु
		phy = &params->phy[EXT_PHY1];
	पूर्ण
	अगर (bnx2x_get_mod_असल_पूर्णांक_cfg(bp, params->chip_id, params->shmem_base,
				      params->port, &gpio_num, &gpio_port) ==
	    -EINVAL) अणु
		DP(NETIF_MSG_LINK, "Failed to get MOD_ABS interrupt config\n");
		वापस;
	पूर्ण

	/* Set valid module led off */
	bnx2x_set_sfp_module_fault_led(params, MISC_REGISTERS_GPIO_HIGH);

	/* Get current gpio val reflecting module plugged in / out*/
	gpio_val = bnx2x_get_gpio(bp, gpio_num, gpio_port);

	/* Call the handling function in हाल module is detected */
	अगर (gpio_val == 0) अणु
		bnx2x_set_mdio_emac_per_phy(bp, params);
		bnx2x_set_aer_mmd(params, phy);

		bnx2x_घातer_sfp_module(params, phy, 1);
		bnx2x_set_gpio_पूर्णांक(bp, gpio_num,
				   MISC_REGISTERS_GPIO_INT_OUTPUT_CLR,
				   gpio_port);
		अगर (bnx2x_रुको_क्रम_sfp_module_initialized(phy, params) == 0) अणु
			bnx2x_sfp_module_detection(phy, params);
			अगर (CHIP_IS_E3(bp)) अणु
				u16 rx_tx_in_reset;
				/* In हाल WC is out of reset, reconfigure the
				 * link speed जबतक taking पूर्णांकo account 1G
				 * module limitation.
				 */
				bnx2x_cl45_पढ़ो(bp, phy,
						MDIO_WC_DEVAD,
						MDIO_WC_REG_DIGITAL5_MISC6,
						&rx_tx_in_reset);
				अगर ((!rx_tx_in_reset) &&
				    (params->link_flags &
				     PHY_INITIALIZED)) अणु
					bnx2x_warpcore_reset_lane(bp, phy, 1);
					bnx2x_warpcore_config_sfi(phy, params);
					bnx2x_warpcore_reset_lane(bp, phy, 0);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			DP(NETIF_MSG_LINK, "SFP+ module is not initialized\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		bnx2x_set_gpio_पूर्णांक(bp, gpio_num,
				   MISC_REGISTERS_GPIO_INT_OUTPUT_SET,
				   gpio_port);
		/* Module was plugged out.
		 * Disable transmit क्रम this module
		 */
		phy->media_type = ETH_PHY_NOT_PRESENT;
	पूर्ण
पूर्ण

/******************************************************************/
/*		Used by 8706 and 8727                             */
/******************************************************************/
अटल व्योम bnx2x_sfp_mask_fault(काष्ठा bnx2x *bp,
				 काष्ठा bnx2x_phy *phy,
				 u16 alarm_status_offset,
				 u16 alarm_ctrl_offset)
अणु
	u16 alarm_status, val;
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD, alarm_status_offset,
			&alarm_status);
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD, alarm_status_offset,
			&alarm_status);
	/* Mask or enable the fault event. */
	bnx2x_cl45_पढ़ो(bp, phy, MDIO_PMA_DEVAD, alarm_ctrl_offset, &val);
	अगर (alarm_status & (1<<0))
		val &= ~(1<<0);
	अन्यथा
		val |= (1<<0);
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_PMA_DEVAD, alarm_ctrl_offset, val);
पूर्ण
/******************************************************************/
/*		common BCM8706/BCM8726 PHY SECTION		  */
/******************************************************************/
अटल u8 bnx2x_8706_8726_पढ़ो_status(काष्ठा bnx2x_phy *phy,
				      काष्ठा link_params *params,
				      काष्ठा link_vars *vars)
अणु
	u8 link_up = 0;
	u16 val1, val2, rx_sd, pcs_status;
	काष्ठा bnx2x *bp = params->bp;
	DP(NETIF_MSG_LINK, "XGXS 8706/8726\n");
	/* Clear RX Alarm*/
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_LASI_RXSTAT, &val2);

	bnx2x_sfp_mask_fault(bp, phy, MDIO_PMA_LASI_TXSTAT,
			     MDIO_PMA_LASI_TXCTRL);

	/* Clear LASI indication*/
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_LASI_STAT, &val1);
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_LASI_STAT, &val2);
	DP(NETIF_MSG_LINK, "8706/8726 LASI status 0x%x--> 0x%x\n", val1, val2);

	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_RX_SD, &rx_sd);
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PCS_DEVAD, MDIO_PCS_REG_STATUS, &pcs_status);
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_AN_DEVAD, MDIO_AN_REG_LINK_STATUS, &val2);
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_AN_DEVAD, MDIO_AN_REG_LINK_STATUS, &val2);

	DP(NETIF_MSG_LINK, "8706/8726 rx_sd 0x%x pcs_status 0x%x 1Gbps"
			" link_status 0x%x\n", rx_sd, pcs_status, val2);
	/* Link is up अगर both bit 0 of pmd_rx_sd and bit 0 of pcs_status
	 * are set, or अगर the स्वतःneg bit 1 is set
	 */
	link_up = ((rx_sd & pcs_status & 0x1) || (val2 & (1<<1)));
	अगर (link_up) अणु
		अगर (val2 & (1<<1))
			vars->line_speed = SPEED_1000;
		अन्यथा
			vars->line_speed = SPEED_10000;
		bnx2x_ext_phy_resolve_fc(phy, params, vars);
		vars->duplex = DUPLEX_FULL;
	पूर्ण

	/* Capture 10G link fault. Read twice to clear stale value. */
	अगर (vars->line_speed == SPEED_10000) अणु
		bnx2x_cl45_पढ़ो(bp, phy, MDIO_PMA_DEVAD,
			    MDIO_PMA_LASI_TXSTAT, &val1);
		bnx2x_cl45_पढ़ो(bp, phy, MDIO_PMA_DEVAD,
			    MDIO_PMA_LASI_TXSTAT, &val1);
		अगर (val1 & (1<<0))
			vars->fault_detected = 1;
	पूर्ण

	वापस link_up;
पूर्ण

/******************************************************************/
/*			BCM8706 PHY SECTION			  */
/******************************************************************/
अटल व्योम bnx2x_8706_config_init(काष्ठा bnx2x_phy *phy,
				   काष्ठा link_params *params,
				   काष्ठा link_vars *vars)
अणु
	u32 tx_en_mode;
	u16 cnt, val, पंचांगp1;
	काष्ठा bnx2x *bp = params->bp;

	bnx2x_set_gpio(bp, MISC_REGISTERS_GPIO_2,
		       MISC_REGISTERS_GPIO_OUTPUT_HIGH, params->port);
	/* HW reset */
	bnx2x_ext_phy_hw_reset(bp, params->port);
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_PMA_DEVAD, MDIO_PMA_REG_CTRL, 0xa040);
	bnx2x_रुको_reset_complete(bp, phy, params);

	/* Wait until fw is loaded */
	क्रम (cnt = 0; cnt < 100; cnt++) अणु
		bnx2x_cl45_पढ़ो(bp, phy,
				MDIO_PMA_DEVAD, MDIO_PMA_REG_ROM_VER1, &val);
		अगर (val)
			अवरोध;
		usleep_range(10000, 20000);
	पूर्ण
	DP(NETIF_MSG_LINK, "XGXS 8706 is initialized after %d ms\n", cnt);
	अगर ((params->feature_config_flags &
	     FEATURE_CONFIG_OVERRIDE_PREEMPHASIS_ENABLED)) अणु
		u8 i;
		u16 reg;
		क्रम (i = 0; i < 4; i++) अणु
			reg = MDIO_XS_8706_REG_BANK_RX0 +
				i*(MDIO_XS_8706_REG_BANK_RX1 -
				   MDIO_XS_8706_REG_BANK_RX0);
			bnx2x_cl45_पढ़ो(bp, phy, MDIO_XS_DEVAD, reg, &val);
			/* Clear first 3 bits of the control */
			val &= ~0x7;
			/* Set control bits according to configuration */
			val |= (phy->rx_preemphasis[i] & 0x7);
			DP(NETIF_MSG_LINK, "Setting RX Equalizer to BCM8706"
				   " reg 0x%x <-- val 0x%x\n", reg, val);
			bnx2x_cl45_ग_लिखो(bp, phy, MDIO_XS_DEVAD, reg, val);
		पूर्ण
	पूर्ण
	/* Force speed */
	अगर (phy->req_line_speed == SPEED_10000) अणु
		DP(NETIF_MSG_LINK, "XGXS 8706 force 10Gbps\n");

		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD,
				 MDIO_PMA_REG_DIGITAL_CTRL, 0x400);
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_LASI_TXCTRL,
				 0);
		/* Arm LASI क्रम link and Tx fault. */
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_LASI_CTRL, 3);
	पूर्ण अन्यथा अणु
		/* Force 1Gbps using स्वतःneg with 1G advertisement */

		/* Allow CL37 through CL73 */
		DP(NETIF_MSG_LINK, "XGXS 8706 AutoNeg\n");
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_AN_DEVAD, MDIO_AN_REG_CL37_CL73, 0x040c);

		/* Enable Full-Duplex advertisement on CL37 */
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_AN_DEVAD, MDIO_AN_REG_CL37_FC_LP, 0x0020);
		/* Enable CL37 AN */
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_AN_DEVAD, MDIO_AN_REG_CL37_AN, 0x1000);
		/* 1G support */
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_AN_DEVAD, MDIO_AN_REG_ADV, (1<<5));

		/* Enable clause 73 AN */
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_AN_DEVAD, MDIO_AN_REG_CTRL, 0x1200);
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_LASI_RXCTRL,
				 0x0400);
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_LASI_CTRL,
				 0x0004);
	पूर्ण
	bnx2x_save_bcm_spirom_ver(bp, phy, params->port);

	/* If TX Laser is controlled by GPIO_0, करो not let PHY go पूर्णांकo low
	 * घातer mode, अगर TX Laser is disabled
	 */

	tx_en_mode = REG_RD(bp, params->shmem_base +
			    दुरत्व(काष्ठा shmem_region,
				dev_info.port_hw_config[params->port].sfp_ctrl))
			& PORT_HW_CFG_TX_LASER_MASK;

	अगर (tx_en_mode == PORT_HW_CFG_TX_LASER_GPIO0) अणु
		DP(NETIF_MSG_LINK, "Enabling TXONOFF_PWRDN_DIS\n");
		bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_DIGITAL_CTRL, &पंचांगp1);
		पंचांगp1 |= 0x1;
		bnx2x_cl45_ग_लिखो(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_DIGITAL_CTRL, पंचांगp1);
	पूर्ण
पूर्ण

अटल u8 bnx2x_8706_पढ़ो_status(काष्ठा bnx2x_phy *phy,
				 काष्ठा link_params *params,
				 काष्ठा link_vars *vars)
अणु
	वापस bnx2x_8706_8726_पढ़ो_status(phy, params, vars);
पूर्ण

/******************************************************************/
/*			BCM8726 PHY SECTION			  */
/******************************************************************/
अटल व्योम bnx2x_8726_config_loopback(काष्ठा bnx2x_phy *phy,
				       काष्ठा link_params *params)
अणु
	काष्ठा bnx2x *bp = params->bp;
	DP(NETIF_MSG_LINK, "PMA/PMD ext_phy_loopback: 8726\n");
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_PMA_DEVAD, MDIO_PMA_REG_CTRL, 0x0001);
पूर्ण

अटल व्योम bnx2x_8726_बाह्यal_rom_boot(काष्ठा bnx2x_phy *phy,
					 काष्ठा link_params *params)
अणु
	काष्ठा bnx2x *bp = params->bp;
	/* Need to रुको 100ms after reset */
	msleep(100);

	/* Micro controller re-boot */
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD, MDIO_PMA_REG_GEN_CTRL, 0x018B);

	/* Set soft reset */
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_GEN_CTRL,
			 MDIO_PMA_REG_GEN_CTRL_ROM_MICRO_RESET);

	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_MISC_CTRL1, 0x0001);

	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_GEN_CTRL,
			 MDIO_PMA_REG_GEN_CTRL_ROM_RESET_INTERNAL_MP);

	/* Wait क्रम 150ms क्रम microcode load */
	msleep(150);

	/* Disable serial boot control, tristates pins SS_N, SCK, MOSI, MISO */
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_MISC_CTRL1, 0x0000);

	msleep(200);
	bnx2x_save_bcm_spirom_ver(bp, phy, params->port);
पूर्ण

अटल u8 bnx2x_8726_पढ़ो_status(काष्ठा bnx2x_phy *phy,
				 काष्ठा link_params *params,
				 काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 val1;
	u8 link_up = bnx2x_8706_8726_पढ़ो_status(phy, params, vars);
	अगर (link_up) अणु
		bnx2x_cl45_पढ़ो(bp, phy,
				MDIO_PMA_DEVAD, MDIO_PMA_REG_PHY_IDENTIFIER,
				&val1);
		अगर (val1 & (1<<15)) अणु
			DP(NETIF_MSG_LINK, "Tx is disabled\n");
			link_up = 0;
			vars->line_speed = 0;
		पूर्ण
	पूर्ण
	वापस link_up;
पूर्ण


अटल व्योम bnx2x_8726_config_init(काष्ठा bnx2x_phy *phy,
				   काष्ठा link_params *params,
				   काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	DP(NETIF_MSG_LINK, "Initializing BCM8726\n");

	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_PMA_DEVAD, MDIO_PMA_REG_CTRL, 1<<15);
	bnx2x_रुको_reset_complete(bp, phy, params);

	bnx2x_8726_बाह्यal_rom_boot(phy, params);

	/* Need to call module detected on initialization since the module
	 * detection triggered by actual module insertion might occur beक्रमe
	 * driver is loaded, and when driver is loaded, it reset all
	 * रेजिस्टरs, including the transmitter
	 */
	bnx2x_sfp_module_detection(phy, params);

	अगर (phy->req_line_speed == SPEED_1000) अणु
		DP(NETIF_MSG_LINK, "Setting 1G force\n");
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_REG_CTRL, 0x40);
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_REG_10G_CTRL2, 0xD);
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_LASI_CTRL, 0x5);
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_LASI_RXCTRL,
				 0x400);
	पूर्ण अन्यथा अगर ((phy->req_line_speed == SPEED_AUTO_NEG) &&
		   (phy->speed_cap_mask &
		      PORT_HW_CFG_SPEED_CAPABILITY_D0_1G) &&
		   ((phy->speed_cap_mask &
		      PORT_HW_CFG_SPEED_CAPABILITY_D0_10G) !=
		    PORT_HW_CFG_SPEED_CAPABILITY_D0_10G)) अणु
		DP(NETIF_MSG_LINK, "Setting 1G clause37\n");
		/* Set Flow control */
		bnx2x_ext_phy_set_छोड़ो(params, phy, vars);
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_AN_DEVAD, MDIO_AN_REG_ADV, 0x20);
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_AN_DEVAD, MDIO_AN_REG_CL37_CL73, 0x040c);
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_AN_DEVAD, MDIO_AN_REG_CL37_FC_LD, 0x0020);
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_AN_DEVAD, MDIO_AN_REG_CL37_AN, 0x1000);
		bnx2x_cl45_ग_लिखो(bp, phy,
				MDIO_AN_DEVAD, MDIO_AN_REG_CTRL, 0x1200);
		/* Enable RX-ALARM control to receive पूर्णांकerrupt क्रम 1G speed
		 * change
		 */
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_LASI_CTRL, 0x4);
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_LASI_RXCTRL,
				 0x400);

	पूर्ण अन्यथा अणु /* Default 10G. Set only LASI control */
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_LASI_CTRL, 1);
	पूर्ण

	/* Set TX PreEmphasis अगर needed */
	अगर ((params->feature_config_flags &
	     FEATURE_CONFIG_OVERRIDE_PREEMPHASIS_ENABLED)) अणु
		DP(NETIF_MSG_LINK,
		   "Setting TX_CTRL1 0x%x, TX_CTRL2 0x%x\n",
			 phy->tx_preemphasis[0],
			 phy->tx_preemphasis[1]);
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD,
				 MDIO_PMA_REG_8726_TX_CTRL1,
				 phy->tx_preemphasis[0]);

		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD,
				 MDIO_PMA_REG_8726_TX_CTRL2,
				 phy->tx_preemphasis[1]);
	पूर्ण
पूर्ण

अटल व्योम bnx2x_8726_link_reset(काष्ठा bnx2x_phy *phy,
				  काष्ठा link_params *params)
अणु
	काष्ठा bnx2x *bp = params->bp;
	DP(NETIF_MSG_LINK, "bnx2x_8726_link_reset port %d\n", params->port);
	/* Set serial boot control क्रम बाह्यal load */
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_GEN_CTRL, 0x0001);
पूर्ण

/******************************************************************/
/*			BCM8727 PHY SECTION			  */
/******************************************************************/

अटल व्योम bnx2x_8727_set_link_led(काष्ठा bnx2x_phy *phy,
				    काष्ठा link_params *params, u8 mode)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 led_mode_biपंचांगask = 0;
	u16 gpio_pins_biपंचांगask = 0;
	u16 val;
	/* Only NOC flavor requires to set the LED specअगरically */
	अगर (!(phy->flags & FLAGS_NOC))
		वापस;
	चयन (mode) अणु
	हाल LED_MODE_FRONT_PANEL_OFF:
	हाल LED_MODE_OFF:
		led_mode_biपंचांगask = 0;
		gpio_pins_biपंचांगask = 0x03;
		अवरोध;
	हाल LED_MODE_ON:
		led_mode_biपंचांगask = 0;
		gpio_pins_biपंचांगask = 0x02;
		अवरोध;
	हाल LED_MODE_OPER:
		led_mode_biपंचांगask = 0x60;
		gpio_pins_biपंचांगask = 0x11;
		अवरोध;
	पूर्ण
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD,
			MDIO_PMA_REG_8727_PCS_OPT_CTRL,
			&val);
	val &= 0xff8f;
	val |= led_mode_biपंचांगask;
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_8727_PCS_OPT_CTRL,
			 val);
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD,
			MDIO_PMA_REG_8727_GPIO_CTRL,
			&val);
	val &= 0xffe0;
	val |= gpio_pins_biपंचांगask;
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_8727_GPIO_CTRL,
			 val);
पूर्ण
अटल व्योम bnx2x_8727_hw_reset(काष्ठा bnx2x_phy *phy,
				काष्ठा link_params *params) अणु
	u32 swap_val, swap_override;
	u8 port;
	/* The PHY reset is controlled by GPIO 1. Fake the port number
	 * to cancel the swap करोne in set_gpio()
	 */
	काष्ठा bnx2x *bp = params->bp;
	swap_val = REG_RD(bp, NIG_REG_PORT_SWAP);
	swap_override = REG_RD(bp, NIG_REG_STRAP_OVERRIDE);
	port = (swap_val && swap_override) ^ 1;
	bnx2x_set_gpio(bp, MISC_REGISTERS_GPIO_1,
		       MISC_REGISTERS_GPIO_OUTPUT_LOW, port);
पूर्ण

अटल व्योम bnx2x_8727_config_speed(काष्ठा bnx2x_phy *phy,
				    काष्ठा link_params *params)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 पंचांगp1, val;
	/* Set option 1G speed */
	अगर ((phy->req_line_speed == SPEED_1000) ||
	    (phy->media_type == ETH_PHY_SFP_1G_FIBER)) अणु
		DP(NETIF_MSG_LINK, "Setting 1G force\n");
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_REG_CTRL, 0x40);
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_REG_10G_CTRL2, 0xD);
		bnx2x_cl45_पढ़ो(bp, phy,
				MDIO_PMA_DEVAD, MDIO_PMA_REG_10G_CTRL2, &पंचांगp1);
		DP(NETIF_MSG_LINK, "1.7 = 0x%x\n", पंचांगp1);
		/* Power करोwn the XAUI until link is up in हाल of dual-media
		 * and 1G
		 */
		अगर (DUAL_MEDIA(params)) अणु
			bnx2x_cl45_पढ़ो(bp, phy,
					MDIO_PMA_DEVAD,
					MDIO_PMA_REG_8727_PCS_GP, &val);
			val |= (3<<10);
			bnx2x_cl45_ग_लिखो(bp, phy,
					 MDIO_PMA_DEVAD,
					 MDIO_PMA_REG_8727_PCS_GP, val);
		पूर्ण
	पूर्ण अन्यथा अगर ((phy->req_line_speed == SPEED_AUTO_NEG) &&
		   ((phy->speed_cap_mask &
		     PORT_HW_CFG_SPEED_CAPABILITY_D0_1G)) &&
		   ((phy->speed_cap_mask &
		      PORT_HW_CFG_SPEED_CAPABILITY_D0_10G) !=
		   PORT_HW_CFG_SPEED_CAPABILITY_D0_10G)) अणु

		DP(NETIF_MSG_LINK, "Setting 1G clause37\n");
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_AN_DEVAD, MDIO_AN_REG_8727_MISC_CTRL, 0);
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_AN_DEVAD, MDIO_AN_REG_CL37_AN, 0x1300);
	पूर्ण अन्यथा अणु
		/* Since the 8727 has only single reset pin, need to set the 10G
		 * रेजिस्टरs although it is शेष
		 */
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_AN_DEVAD, MDIO_AN_REG_8727_MISC_CTRL,
				 0x0020);
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_AN_DEVAD, MDIO_AN_REG_CL37_AN, 0x0100);
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_REG_CTRL, 0x2040);
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_REG_10G_CTRL2,
				 0x0008);
	पूर्ण
पूर्ण

अटल व्योम bnx2x_8727_config_init(काष्ठा bnx2x_phy *phy,
				   काष्ठा link_params *params,
				   काष्ठा link_vars *vars)
अणु
	u32 tx_en_mode;
	u16 पंचांगp1, mod_असल, पंचांगp2;
	काष्ठा bnx2x *bp = params->bp;
	/* Enable PMD link, MOD_ABS_FLT, and 1G link alarm */

	bnx2x_रुको_reset_complete(bp, phy, params);

	DP(NETIF_MSG_LINK, "Initializing BCM8727\n");

	bnx2x_8727_specअगरic_func(phy, params, PHY_INIT);
	/* Initially configure MOD_ABS to पूर्णांकerrupt when module is
	 * presence( bit 8)
	 */
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_PHY_IDENTIFIER, &mod_असल);
	/* Set EDC off by setting OPTXLOS संकेत input to low (bit 9).
	 * When the EDC is off it locks onto a reference घड़ी and aव्योमs
	 * becoming 'lost'
	 */
	mod_असल &= ~(1<<8);
	अगर (!(phy->flags & FLAGS_NOC))
		mod_असल &= ~(1<<9);
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD, MDIO_PMA_REG_PHY_IDENTIFIER, mod_असल);

	/* Enable/Disable PHY transmitter output */
	bnx2x_set_disable_pmd_transmit(params, phy, 0);

	bnx2x_8727_घातer_module(bp, phy, 1);

	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_M8051_MSGOUT_REG, &पंचांगp1);

	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_LASI_RXSTAT, &पंचांगp1);

	bnx2x_8727_config_speed(phy, params);


	/* Set TX PreEmphasis अगर needed */
	अगर ((params->feature_config_flags &
	     FEATURE_CONFIG_OVERRIDE_PREEMPHASIS_ENABLED)) अणु
		DP(NETIF_MSG_LINK, "Setting TX_CTRL1 0x%x, TX_CTRL2 0x%x\n",
			   phy->tx_preemphasis[0],
			   phy->tx_preemphasis[1]);
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_REG_8727_TX_CTRL1,
				 phy->tx_preemphasis[0]);

		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_REG_8727_TX_CTRL2,
				 phy->tx_preemphasis[1]);
	पूर्ण

	/* If TX Laser is controlled by GPIO_0, करो not let PHY go पूर्णांकo low
	 * घातer mode, अगर TX Laser is disabled
	 */
	tx_en_mode = REG_RD(bp, params->shmem_base +
			    दुरत्व(काष्ठा shmem_region,
				dev_info.port_hw_config[params->port].sfp_ctrl))
			& PORT_HW_CFG_TX_LASER_MASK;

	अगर (tx_en_mode == PORT_HW_CFG_TX_LASER_GPIO0) अणु

		DP(NETIF_MSG_LINK, "Enabling TXONOFF_PWRDN_DIS\n");
		bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_8727_OPT_CFG_REG, &पंचांगp2);
		पंचांगp2 |= 0x1000;
		पंचांगp2 &= 0xFFEF;
		bnx2x_cl45_ग_लिखो(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_8727_OPT_CFG_REG, पंचांगp2);
		bnx2x_cl45_पढ़ो(bp, phy,
				MDIO_PMA_DEVAD, MDIO_PMA_REG_PHY_IDENTIFIER,
				&पंचांगp2);
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_REG_PHY_IDENTIFIER,
				 (पंचांगp2 & 0x7fff));
	पूर्ण
पूर्ण

अटल व्योम bnx2x_8727_handle_mod_असल(काष्ठा bnx2x_phy *phy,
				      काष्ठा link_params *params)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 mod_असल, rx_alarm_status;
	u32 val = REG_RD(bp, params->shmem_base +
			     दुरत्व(काष्ठा shmem_region, dev_info.
				      port_feature_config[params->port].
				      config));
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD,
			MDIO_PMA_REG_PHY_IDENTIFIER, &mod_असल);
	अगर (mod_असल & (1<<8)) अणु

		/* Module is असलent */
		DP(NETIF_MSG_LINK,
		   "MOD_ABS indication show module is absent\n");
		phy->media_type = ETH_PHY_NOT_PRESENT;
		/* 1. Set mod_असल to detect next module
		 *    presence event
		 * 2. Set EDC off by setting OPTXLOS संकेत input to low
		 *    (bit 9).
		 *    When the EDC is off it locks onto a reference घड़ी and
		 *    aव्योमs becoming 'lost'.
		 */
		mod_असल &= ~(1<<8);
		अगर (!(phy->flags & FLAGS_NOC))
			mod_असल &= ~(1<<9);
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD,
				 MDIO_PMA_REG_PHY_IDENTIFIER, mod_असल);

		/* Clear RX alarm since it stays up as दीर्घ as
		 * the mod_असल wasn't changed
		 */
		bnx2x_cl45_पढ़ो(bp, phy,
				MDIO_PMA_DEVAD,
				MDIO_PMA_LASI_RXSTAT, &rx_alarm_status);

	पूर्ण अन्यथा अणु
		/* Module is present */
		DP(NETIF_MSG_LINK,
		   "MOD_ABS indication show module is present\n");
		/* First disable transmitter, and अगर the module is ok, the
		 * module_detection will enable it
		 * 1. Set mod_असल to detect next module असलent event ( bit 8)
		 * 2. Restore the शेष polarity of the OPRXLOS संकेत and
		 * this संकेत will then correctly indicate the presence or
		 * असलence of the Rx संकेत. (bit 9)
		 */
		mod_असल |= (1<<8);
		अगर (!(phy->flags & FLAGS_NOC))
			mod_असल |= (1<<9);
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD,
				 MDIO_PMA_REG_PHY_IDENTIFIER, mod_असल);

		/* Clear RX alarm since it stays up as दीर्घ as the mod_असल
		 * wasn't changed. This is need to be करोne beक्रमe calling the
		 * module detection, otherwise it will clear* the link update
		 * alarm
		 */
		bnx2x_cl45_पढ़ो(bp, phy,
				MDIO_PMA_DEVAD,
				MDIO_PMA_LASI_RXSTAT, &rx_alarm_status);


		अगर ((val & PORT_FEAT_CFG_OPT_MDL_ENFRCMNT_MASK) ==
		    PORT_FEAT_CFG_OPT_MDL_ENFRCMNT_DISABLE_TX_LASER)
			bnx2x_sfp_set_transmitter(params, phy, 0);

		अगर (bnx2x_रुको_क्रम_sfp_module_initialized(phy, params) == 0)
			bnx2x_sfp_module_detection(phy, params);
		अन्यथा
			DP(NETIF_MSG_LINK, "SFP+ module is not initialized\n");

		/* Reconfigure link speed based on module type limitations */
		bnx2x_8727_config_speed(phy, params);
	पूर्ण

	DP(NETIF_MSG_LINK, "8727 RX_ALARM_STATUS 0x%x\n",
		   rx_alarm_status);
	/* No need to check link status in हाल of module plugged in/out */
पूर्ण

अटल u8 bnx2x_8727_पढ़ो_status(काष्ठा bnx2x_phy *phy,
				 काष्ठा link_params *params,
				 काष्ठा link_vars *vars)

अणु
	काष्ठा bnx2x *bp = params->bp;
	u8 link_up = 0, oc_port = params->port;
	u16 link_status = 0;
	u16 rx_alarm_status, lasi_ctrl, val1;

	/* If PHY is not initialized, करो not check link status */
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_LASI_CTRL,
			&lasi_ctrl);
	अगर (!lasi_ctrl)
		वापस 0;

	/* Check the LASI on Rx */
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_LASI_RXSTAT,
			&rx_alarm_status);
	vars->line_speed = 0;
	DP(NETIF_MSG_LINK, "8727 RX_ALARM_STATUS  0x%x\n", rx_alarm_status);

	bnx2x_sfp_mask_fault(bp, phy, MDIO_PMA_LASI_TXSTAT,
			     MDIO_PMA_LASI_TXCTRL);

	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_LASI_STAT, &val1);

	DP(NETIF_MSG_LINK, "8727 LASI status 0x%x\n", val1);

	/* Clear MSG-OUT */
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_M8051_MSGOUT_REG, &val1);

	/* If a module is present and there is need to check
	 * क्रम over current
	 */
	अगर (!(phy->flags & FLAGS_NOC) && !(rx_alarm_status & (1<<5))) अणु
		/* Check over-current using 8727 GPIO0 input*/
		bnx2x_cl45_पढ़ो(bp, phy,
				MDIO_PMA_DEVAD, MDIO_PMA_REG_8727_GPIO_CTRL,
				&val1);

		अगर ((val1 & (1<<8)) == 0) अणु
			अगर (!CHIP_IS_E1x(bp))
				oc_port = BP_PATH(bp) + (params->port << 1);
			DP(NETIF_MSG_LINK,
			   "8727 Power fault has been detected on port %d\n",
			   oc_port);
			netdev_err(bp->dev, "Error: Power fault on Port %d has "
					    "been detected and the power to "
					    "that SFP+ module has been removed "
					    "to prevent failure of the card. "
					    "Please remove the SFP+ module and "
					    "restart the system to clear this "
					    "error.\n",
			 oc_port);
			/* Disable all RX_ALARMs except क्रम mod_असल */
			bnx2x_cl45_ग_लिखो(bp, phy,
					 MDIO_PMA_DEVAD,
					 MDIO_PMA_LASI_RXCTRL, (1<<5));

			bnx2x_cl45_पढ़ो(bp, phy,
					MDIO_PMA_DEVAD,
					MDIO_PMA_REG_PHY_IDENTIFIER, &val1);
			/* Wait क्रम module_असलent_event */
			val1 |= (1<<8);
			bnx2x_cl45_ग_लिखो(bp, phy,
					 MDIO_PMA_DEVAD,
					 MDIO_PMA_REG_PHY_IDENTIFIER, val1);
			/* Clear RX alarm */
			bnx2x_cl45_पढ़ो(bp, phy,
				MDIO_PMA_DEVAD,
				MDIO_PMA_LASI_RXSTAT, &rx_alarm_status);
			bnx2x_8727_घातer_module(params->bp, phy, 0);
			वापस 0;
		पूर्ण
	पूर्ण /* Over current check */

	/* When module असलent bit is set, check module */
	अगर (rx_alarm_status & (1<<5)) अणु
		bnx2x_8727_handle_mod_असल(phy, params);
		/* Enable all mod_असल and link detection bits */
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_LASI_RXCTRL,
				 ((1<<5) | (1<<2)));
	पूर्ण

	अगर (!(phy->flags & FLAGS_SFP_NOT_APPROVED)) अणु
		DP(NETIF_MSG_LINK, "Enabling 8727 TX laser\n");
		bnx2x_sfp_set_transmitter(params, phy, 1);
	पूर्ण अन्यथा अणु
		DP(NETIF_MSG_LINK, "Tx is disabled\n");
		वापस 0;
	पूर्ण

	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD,
			MDIO_PMA_REG_8073_SPEED_LINK_STATUS, &link_status);

	/* Bits 0..2 --> speed detected,
	 * Bits 13..15--> link is करोwn
	 */
	अगर ((link_status & (1<<2)) && (!(link_status & (1<<15)))) अणु
		link_up = 1;
		vars->line_speed = SPEED_10000;
		DP(NETIF_MSG_LINK, "port %x: External link up in 10G\n",
			   params->port);
	पूर्ण अन्यथा अगर ((link_status & (1<<0)) && (!(link_status & (1<<13)))) अणु
		link_up = 1;
		vars->line_speed = SPEED_1000;
		DP(NETIF_MSG_LINK, "port %x: External link up in 1G\n",
			   params->port);
	पूर्ण अन्यथा अणु
		link_up = 0;
		DP(NETIF_MSG_LINK, "port %x: External link is down\n",
			   params->port);
	पूर्ण

	/* Capture 10G link fault. */
	अगर (vars->line_speed == SPEED_10000) अणु
		bnx2x_cl45_पढ़ो(bp, phy, MDIO_PMA_DEVAD,
			    MDIO_PMA_LASI_TXSTAT, &val1);

		bnx2x_cl45_पढ़ो(bp, phy, MDIO_PMA_DEVAD,
			    MDIO_PMA_LASI_TXSTAT, &val1);

		अगर (val1 & (1<<0)) अणु
			vars->fault_detected = 1;
		पूर्ण
	पूर्ण

	अगर (link_up) अणु
		bnx2x_ext_phy_resolve_fc(phy, params, vars);
		vars->duplex = DUPLEX_FULL;
		DP(NETIF_MSG_LINK, "duplex = 0x%x\n", vars->duplex);
	पूर्ण

	अगर ((DUAL_MEDIA(params)) &&
	    (phy->req_line_speed == SPEED_1000)) अणु
		bnx2x_cl45_पढ़ो(bp, phy,
				MDIO_PMA_DEVAD,
				MDIO_PMA_REG_8727_PCS_GP, &val1);
		/* In हाल of dual-media board and 1G, घातer up the XAUI side,
		 * otherwise घातer it करोwn. For 10G it is करोne स्वतःmatically
		 */
		अगर (link_up)
			val1 &= ~(3<<10);
		अन्यथा
			val1 |= (3<<10);
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD,
				 MDIO_PMA_REG_8727_PCS_GP, val1);
	पूर्ण
	वापस link_up;
पूर्ण

अटल व्योम bnx2x_8727_link_reset(काष्ठा bnx2x_phy *phy,
				  काष्ठा link_params *params)
अणु
	काष्ठा bnx2x *bp = params->bp;

	/* Enable/Disable PHY transmitter output */
	bnx2x_set_disable_pmd_transmit(params, phy, 1);

	/* Disable Transmitter */
	bnx2x_sfp_set_transmitter(params, phy, 0);
	/* Clear LASI */
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_PMA_DEVAD, MDIO_PMA_LASI_CTRL, 0);

पूर्ण

/******************************************************************/
/*		BCM8481/BCM84823/BCM84833 PHY SECTION	          */
/******************************************************************/
अटल पूर्णांक bnx2x_is_8483x_8485x(काष्ठा bnx2x_phy *phy)
अणु
	वापस ((phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84833) ||
		(phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84834) ||
		(phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84858));
पूर्ण

अटल व्योम bnx2x_save_848xx_spirom_version(काष्ठा bnx2x_phy *phy,
					    काष्ठा bnx2x *bp,
					    u8 port)
अणु
	u16 val, fw_ver2, cnt, i;
	अटल काष्ठा bnx2x_reg_set reg_set[] = अणु
		अणुMDIO_PMA_DEVAD, 0xA819, 0x0014पूर्ण,
		अणुMDIO_PMA_DEVAD, 0xA81A, 0xc200पूर्ण,
		अणुMDIO_PMA_DEVAD, 0xA81B, 0x0000पूर्ण,
		अणुMDIO_PMA_DEVAD, 0xA81C, 0x0300पूर्ण,
		अणुMDIO_PMA_DEVAD, 0xA817, 0x0009पूर्ण
	पूर्ण;
	u16 fw_ver1;

	अगर (bnx2x_is_8483x_8485x(phy)) अणु
		bnx2x_cl45_पढ़ो(bp, phy, MDIO_CTL_DEVAD, 0x400f, &fw_ver1);
		अगर (phy->type != PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84858)
			fw_ver1 &= 0xfff;
		bnx2x_save_spirom_version(bp, port, fw_ver1, phy->ver_addr);
	पूर्ण अन्यथा अणु
		/* For 32-bit रेजिस्टरs in 848xx, access via MDIO2ARM i/f. */
		/* (1) set reg 0xc200_0014(SPI_BRIDGE_CTRL_2) to 0x03000000 */
		क्रम (i = 0; i < ARRAY_SIZE(reg_set); i++)
			bnx2x_cl45_ग_लिखो(bp, phy, reg_set[i].devad,
					 reg_set[i].reg, reg_set[i].val);

		क्रम (cnt = 0; cnt < 100; cnt++) अणु
			bnx2x_cl45_पढ़ो(bp, phy, MDIO_PMA_DEVAD, 0xA818, &val);
			अगर (val & 1)
				अवरोध;
			udelay(5);
		पूर्ण
		अगर (cnt == 100) अणु
			DP(NETIF_MSG_LINK, "Unable to read 848xx "
					"phy fw version(1)\n");
			bnx2x_save_spirom_version(bp, port, 0,
						  phy->ver_addr);
			वापस;
		पूर्ण


		/* 2) पढ़ो रेजिस्टर 0xc200_0000 (SPI_FW_STATUS) */
		bnx2x_cl45_ग_लिखो(bp, phy, MDIO_PMA_DEVAD, 0xA819, 0x0000);
		bnx2x_cl45_ग_लिखो(bp, phy, MDIO_PMA_DEVAD, 0xA81A, 0xc200);
		bnx2x_cl45_ग_लिखो(bp, phy, MDIO_PMA_DEVAD, 0xA817, 0x000A);
		क्रम (cnt = 0; cnt < 100; cnt++) अणु
			bnx2x_cl45_पढ़ो(bp, phy, MDIO_PMA_DEVAD, 0xA818, &val);
			अगर (val & 1)
				अवरोध;
			udelay(5);
		पूर्ण
		अगर (cnt == 100) अणु
			DP(NETIF_MSG_LINK, "Unable to read 848xx phy fw "
					"version(2)\n");
			bnx2x_save_spirom_version(bp, port, 0,
						  phy->ver_addr);
			वापस;
		पूर्ण

		/* lower 16 bits of the रेजिस्टर SPI_FW_STATUS */
		bnx2x_cl45_पढ़ो(bp, phy, MDIO_PMA_DEVAD, 0xA81B, &fw_ver1);
		/* upper 16 bits of रेजिस्टर SPI_FW_STATUS */
		bnx2x_cl45_पढ़ो(bp, phy, MDIO_PMA_DEVAD, 0xA81C, &fw_ver2);

		bnx2x_save_spirom_version(bp, port, (fw_ver2<<16) | fw_ver1,
					  phy->ver_addr);
	पूर्ण

पूर्ण
अटल व्योम bnx2x_848xx_set_led(काष्ठा bnx2x *bp,
				काष्ठा bnx2x_phy *phy)
अणु
	u16 val, led3_blink_rate, offset, i;
	अटल काष्ठा bnx2x_reg_set reg_set[] = अणु
		अणुMDIO_PMA_DEVAD, MDIO_PMA_REG_8481_LED1_MASK, 0x0080पूर्ण,
		अणुMDIO_PMA_DEVAD, MDIO_PMA_REG_8481_LED2_MASK, 0x0018पूर्ण,
		अणुMDIO_PMA_DEVAD, MDIO_PMA_REG_8481_LED3_MASK, 0x0006पूर्ण,
		अणुMDIO_PMA_DEVAD, MDIO_PMA_REG_84823_CTL_SLOW_CLK_CNT_HIGH,
			MDIO_PMA_REG_84823_BLINK_RATE_VAL_15P9HZपूर्ण,
		अणुMDIO_AN_DEVAD, 0xFFFB, 0xFFFDपूर्ण
	पूर्ण;

	अगर (phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84858) अणु
		/* Set LED5 source */
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD,
				 MDIO_PMA_REG_8481_LED5_MASK,
				 0x90);
		led3_blink_rate = 0x000f;
	पूर्ण अन्यथा अणु
		led3_blink_rate = 0x0000;
	पूर्ण
	/* Set LED3 BLINK */
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_8481_LED3_BLINK,
			 led3_blink_rate);

	/* PHYC_CTL_LED_CTL */
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD,
			MDIO_PMA_REG_8481_LINK_SIGNAL, &val);
	val &= 0xFE00;
	val |= 0x0092;

	अगर (phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84858)
		val |= 2 << 12; /* LED5 ON based on source */

	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_8481_LINK_SIGNAL, val);

	क्रम (i = 0; i < ARRAY_SIZE(reg_set); i++)
		bnx2x_cl45_ग_लिखो(bp, phy, reg_set[i].devad, reg_set[i].reg,
				 reg_set[i].val);

	अगर (bnx2x_is_8483x_8485x(phy))
		offset = MDIO_PMA_REG_84833_CTL_LED_CTL_1;
	अन्यथा
		offset = MDIO_PMA_REG_84823_CTL_LED_CTL_1;

	अगर (phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84858)
		val = MDIO_PMA_REG_84858_ALLOW_GPHY_ACT |
		      MDIO_PMA_REG_84823_LED3_STRETCH_EN;
	अन्यथा
		val = MDIO_PMA_REG_84823_LED3_STRETCH_EN;

	/* stretch_en क्रम LEDs */
	bnx2x_cl45_पढ़ो_or_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD,
				 offset,
				 val);
पूर्ण

अटल व्योम bnx2x_848xx_specअगरic_func(काष्ठा bnx2x_phy *phy,
				      काष्ठा link_params *params,
				      u32 action)
अणु
	काष्ठा bnx2x *bp = params->bp;
	चयन (action) अणु
	हाल PHY_INIT:
		अगर (bnx2x_is_8483x_8485x(phy)) अणु
			/* Save spirom version */
			bnx2x_save_848xx_spirom_version(phy, bp, params->port);
		पूर्ण
		/* This phy uses the NIG latch mechanism since link indication
		 * arrives through its LED4 and not via its LASI संकेत, so we
		 * get steady संकेत instead of clear on पढ़ो
		 */
		bnx2x_bits_en(bp, NIG_REG_LATCH_BC_0 + params->port*4,
			      1 << NIG_LATCH_BC_ENABLE_MI_INT);

		bnx2x_848xx_set_led(bp, phy);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_848xx_cmn_config_init(काष्ठा bnx2x_phy *phy,
				       काष्ठा link_params *params,
				       काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 स्वतःneg_val, an_1000_val, an_10_100_val;

	bnx2x_848xx_specअगरic_func(phy, params, PHY_INIT);
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD, MDIO_PMA_REG_CTRL, 0x0000);

	/* set 1000 speed advertisement */
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_AN_DEVAD, MDIO_AN_REG_8481_1000T_CTRL,
			&an_1000_val);

	bnx2x_ext_phy_set_छोड़ो(params, phy, vars);
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_AN_DEVAD,
			MDIO_AN_REG_8481_LEGACY_AN_ADV,
			&an_10_100_val);
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_AN_DEVAD, MDIO_AN_REG_8481_LEGACY_MII_CTRL,
			&स्वतःneg_val);
	/* Disable क्रमced speed */
	स्वतःneg_val &= ~((1<<6) | (1<<8) | (1<<9) | (1<<12) | (1<<13));
	an_10_100_val &= ~((1<<5) | (1<<6) | (1<<7) | (1<<8));

	अगर (((phy->req_line_speed == SPEED_AUTO_NEG) &&
	     (phy->speed_cap_mask &
	     PORT_HW_CFG_SPEED_CAPABILITY_D0_1G)) ||
	    (phy->req_line_speed == SPEED_1000)) अणु
		an_1000_val |= (1<<8);
		स्वतःneg_val |= (1<<9 | 1<<12);
		अगर (phy->req_duplex == DUPLEX_FULL)
			an_1000_val |= (1<<9);
		DP(NETIF_MSG_LINK, "Advertising 1G\n");
	पूर्ण अन्यथा
		an_1000_val &= ~((1<<8) | (1<<9));

	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_AN_DEVAD, MDIO_AN_REG_8481_1000T_CTRL,
			 an_1000_val);

	/* Set 10/100 speed advertisement */
	अगर (phy->req_line_speed == SPEED_AUTO_NEG) अणु
		अगर (phy->speed_cap_mask &
		    PORT_HW_CFG_SPEED_CAPABILITY_D0_100M_FULL) अणु
			/* Enable स्वतःneg and restart स्वतःneg क्रम legacy speeds
			 */
			स्वतःneg_val |= (1<<9 | 1<<12);
			an_10_100_val |= (1<<8);
			DP(NETIF_MSG_LINK, "Advertising 100M-FD\n");
		पूर्ण

		अगर (phy->speed_cap_mask &
		    PORT_HW_CFG_SPEED_CAPABILITY_D0_100M_HALF) अणु
			/* Enable स्वतःneg and restart स्वतःneg क्रम legacy speeds
			 */
			स्वतःneg_val |= (1<<9 | 1<<12);
			an_10_100_val |= (1<<7);
			DP(NETIF_MSG_LINK, "Advertising 100M-HD\n");
		पूर्ण

		अगर ((phy->speed_cap_mask &
		     PORT_HW_CFG_SPEED_CAPABILITY_D0_10M_FULL) &&
		    (phy->supported & SUPPORTED_10baseT_Full)) अणु
			an_10_100_val |= (1<<6);
			स्वतःneg_val |= (1<<9 | 1<<12);
			DP(NETIF_MSG_LINK, "Advertising 10M-FD\n");
		पूर्ण

		अगर ((phy->speed_cap_mask &
		     PORT_HW_CFG_SPEED_CAPABILITY_D0_10M_HALF) &&
		    (phy->supported & SUPPORTED_10baseT_Half)) अणु
			an_10_100_val |= (1<<5);
			स्वतःneg_val |= (1<<9 | 1<<12);
			DP(NETIF_MSG_LINK, "Advertising 10M-HD\n");
		पूर्ण
	पूर्ण

	/* Only 10/100 are allowed to work in FORCE mode */
	अगर ((phy->req_line_speed == SPEED_100) &&
	    (phy->supported &
	     (SUPPORTED_100baseT_Half |
	      SUPPORTED_100baseT_Full))) अणु
		स्वतःneg_val |= (1<<13);
		/* Enabled AUTO-MDIX when स्वतःneg is disabled */
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_AN_DEVAD, MDIO_AN_REG_8481_AUX_CTRL,
				 (1<<15 | 1<<9 | 7<<0));
		/* The PHY needs this set even क्रम क्रमced link. */
		an_10_100_val |= (1<<8) | (1<<7);
		DP(NETIF_MSG_LINK, "Setting 100M force\n");
	पूर्ण
	अगर ((phy->req_line_speed == SPEED_10) &&
	    (phy->supported &
	     (SUPPORTED_10baseT_Half |
	      SUPPORTED_10baseT_Full))) अणु
		/* Enabled AUTO-MDIX when स्वतःneg is disabled */
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_AN_DEVAD, MDIO_AN_REG_8481_AUX_CTRL,
				 (1<<15 | 1<<9 | 7<<0));
		DP(NETIF_MSG_LINK, "Setting 10M force\n");
	पूर्ण

	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_AN_DEVAD, MDIO_AN_REG_8481_LEGACY_AN_ADV,
			 an_10_100_val);

	अगर (phy->req_duplex == DUPLEX_FULL)
		स्वतःneg_val |= (1<<8);

	/* Always ग_लिखो this अगर this is not 84833/4.
	 * For 84833/4, ग_लिखो it only when it's a क्रमced speed.
	 */
	अगर (!bnx2x_is_8483x_8485x(phy) ||
	    ((स्वतःneg_val & (1<<12)) == 0))
		bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_AN_DEVAD,
			 MDIO_AN_REG_8481_LEGACY_MII_CTRL, स्वतःneg_val);

	अगर (((phy->req_line_speed == SPEED_AUTO_NEG) &&
	    (phy->speed_cap_mask &
	     PORT_HW_CFG_SPEED_CAPABILITY_D0_10G)) ||
		(phy->req_line_speed == SPEED_10000)) अणु
			DP(NETIF_MSG_LINK, "Advertising 10G\n");
			/* Restart स्वतःneg क्रम 10G*/

			bnx2x_cl45_पढ़ो_or_ग_लिखो(
				bp, phy,
				MDIO_AN_DEVAD,
				MDIO_AN_REG_8481_10GBASE_T_AN_CTRL,
				0x1000);
			bnx2x_cl45_ग_लिखो(bp, phy,
					 MDIO_AN_DEVAD, MDIO_AN_REG_CTRL,
					 0x3200);
	पूर्ण अन्यथा
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_AN_DEVAD,
				 MDIO_AN_REG_8481_10GBASE_T_AN_CTRL,
				 1);

	वापस 0;
पूर्ण

अटल व्योम bnx2x_8481_config_init(काष्ठा bnx2x_phy *phy,
				   काष्ठा link_params *params,
				   काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	/* Restore normal घातer mode*/
	bnx2x_set_gpio(bp, MISC_REGISTERS_GPIO_2,
		       MISC_REGISTERS_GPIO_OUTPUT_HIGH, params->port);

	/* HW reset */
	bnx2x_ext_phy_hw_reset(bp, params->port);
	bnx2x_रुको_reset_complete(bp, phy, params);

	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_PMA_DEVAD, MDIO_PMA_REG_CTRL, 1<<15);
	bnx2x_848xx_cmn_config_init(phy, params, vars);
पूर्ण

#घोषणा PHY848xx_CMDHDLR_WAIT 300
#घोषणा PHY848xx_CMDHDLR_MAX_ARGS 5

अटल पूर्णांक bnx2x_84858_cmd_hdlr(काष्ठा bnx2x_phy *phy,
				काष्ठा link_params *params,
				u16 fw_cmd,
				u16 cmd_args[], पूर्णांक argc)
अणु
	पूर्णांक idx;
	u16 val;
	काष्ठा bnx2x *bp = params->bp;

	/* Step 1: Poll the STATUS रेजिस्टर to see whether the previous command
	 * is in progress or the प्रणाली is busy (CMD_IN_PROGRESS or
	 * SYSTEM_BUSY). If previous command is in progress or प्रणाली is busy,
	 * check again until the previous command finishes execution and the
	 * प्रणाली is available क्रम taking command
	 */

	क्रम (idx = 0; idx < PHY848xx_CMDHDLR_WAIT; idx++) अणु
		bnx2x_cl45_पढ़ो(bp, phy, MDIO_CTL_DEVAD,
				MDIO_848xx_CMD_HDLR_STATUS, &val);
		अगर ((val != PHY84858_STATUS_CMD_IN_PROGRESS) &&
		    (val != PHY84858_STATUS_CMD_SYSTEM_BUSY))
			अवरोध;
		usleep_range(1000, 2000);
	पूर्ण
	अगर (idx >= PHY848xx_CMDHDLR_WAIT) अणु
		DP(NETIF_MSG_LINK, "FW cmd: FW not ready.\n");
		वापस -EINVAL;
	पूर्ण

	/* Step2: If any parameters are required क्रम the function, ग_लिखो them
	 * to the required DATA रेजिस्टरs
	 */

	क्रम (idx = 0; idx < argc; idx++) अणु
		bnx2x_cl45_ग_लिखो(bp, phy, MDIO_CTL_DEVAD,
				 MDIO_848xx_CMD_HDLR_DATA1 + idx,
				 cmd_args[idx]);
	पूर्ण

	/* Step3: When the firmware is पढ़ोy क्रम commands, ग_लिखो the 'Command
	 * code' to the CMD रेजिस्टर
	 */
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_CTL_DEVAD,
			 MDIO_848xx_CMD_HDLR_COMMAND, fw_cmd);

	/* Step4: Once the command has been written, poll the STATUS रेजिस्टर
	 * to check whether the command has completed (CMD_COMPLETED_PASS/
	 * CMD_FOR_CMDS or CMD_COMPLETED_ERROR).
	 */

	क्रम (idx = 0; idx < PHY848xx_CMDHDLR_WAIT; idx++) अणु
		bnx2x_cl45_पढ़ो(bp, phy, MDIO_CTL_DEVAD,
				MDIO_848xx_CMD_HDLR_STATUS, &val);
		अगर ((val == PHY84858_STATUS_CMD_COMPLETE_PASS) ||
		    (val == PHY84858_STATUS_CMD_COMPLETE_ERROR))
			अवरोध;
		usleep_range(1000, 2000);
	पूर्ण
	अगर ((idx >= PHY848xx_CMDHDLR_WAIT) ||
	    (val == PHY84858_STATUS_CMD_COMPLETE_ERROR)) अणु
		DP(NETIF_MSG_LINK, "FW cmd failed.\n");
		वापस -EINVAL;
	पूर्ण
	/* Step5: Once the command has completed, पढ़ो the specficied DATA
	 * रेजिस्टरs क्रम any saved results क्रम the command, अगर applicable
	 */

	/* Gather वापसing data */
	क्रम (idx = 0; idx < argc; idx++) अणु
		bnx2x_cl45_पढ़ो(bp, phy, MDIO_CTL_DEVAD,
				MDIO_848xx_CMD_HDLR_DATA1 + idx,
				&cmd_args[idx]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_84833_cmd_hdlr(काष्ठा bnx2x_phy *phy,
				काष्ठा link_params *params, u16 fw_cmd,
				u16 cmd_args[], पूर्णांक argc, पूर्णांक process)
अणु
	पूर्णांक idx;
	u16 val;
	काष्ठा bnx2x *bp = params->bp;
	पूर्णांक rc = 0;

	अगर (process == PHY84833_MB_PROCESS2) अणु
		/* Write CMD_OPEN_OVERRIDE to STATUS reg */
		bnx2x_cl45_ग_लिखो(bp, phy, MDIO_CTL_DEVAD,
				 MDIO_848xx_CMD_HDLR_STATUS,
				 PHY84833_STATUS_CMD_OPEN_OVERRIDE);
	पूर्ण

	क्रम (idx = 0; idx < PHY848xx_CMDHDLR_WAIT; idx++) अणु
		bnx2x_cl45_पढ़ो(bp, phy, MDIO_CTL_DEVAD,
				MDIO_848xx_CMD_HDLR_STATUS, &val);
		अगर (val == PHY84833_STATUS_CMD_OPEN_FOR_CMDS)
			अवरोध;
		usleep_range(1000, 2000);
	पूर्ण
	अगर (idx >= PHY848xx_CMDHDLR_WAIT) अणु
		DP(NETIF_MSG_LINK, "FW cmd: FW not ready.\n");
		/* अगर the status is CMD_COMPLETE_PASS or CMD_COMPLETE_ERROR
		 * clear the status to CMD_CLEAR_COMPLETE
		 */
		अगर (val == PHY84833_STATUS_CMD_COMPLETE_PASS ||
		    val == PHY84833_STATUS_CMD_COMPLETE_ERROR) अणु
			bnx2x_cl45_ग_लिखो(bp, phy, MDIO_CTL_DEVAD,
					 MDIO_848xx_CMD_HDLR_STATUS,
					 PHY84833_STATUS_CMD_CLEAR_COMPLETE);
		पूर्ण
		वापस -EINVAL;
	पूर्ण
	अगर (process == PHY84833_MB_PROCESS1 ||
	    process == PHY84833_MB_PROCESS2) अणु
		/* Prepare argument(s) */
		क्रम (idx = 0; idx < argc; idx++) अणु
			bnx2x_cl45_ग_लिखो(bp, phy, MDIO_CTL_DEVAD,
					 MDIO_848xx_CMD_HDLR_DATA1 + idx,
					 cmd_args[idx]);
		पूर्ण
	पूर्ण

	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_CTL_DEVAD,
			MDIO_848xx_CMD_HDLR_COMMAND, fw_cmd);
	क्रम (idx = 0; idx < PHY848xx_CMDHDLR_WAIT; idx++) अणु
		bnx2x_cl45_पढ़ो(bp, phy, MDIO_CTL_DEVAD,
				MDIO_848xx_CMD_HDLR_STATUS, &val);
		अगर ((val == PHY84833_STATUS_CMD_COMPLETE_PASS) ||
		    (val == PHY84833_STATUS_CMD_COMPLETE_ERROR))
			अवरोध;
		usleep_range(1000, 2000);
	पूर्ण
	अगर ((idx >= PHY848xx_CMDHDLR_WAIT) ||
	    (val == PHY84833_STATUS_CMD_COMPLETE_ERROR)) अणु
		DP(NETIF_MSG_LINK, "FW cmd failed.\n");
		rc = -EINVAL;
	पूर्ण
	अगर (process == PHY84833_MB_PROCESS3 && rc == 0) अणु
		/* Gather वापसing data */
		क्रम (idx = 0; idx < argc; idx++) अणु
			bnx2x_cl45_पढ़ो(bp, phy, MDIO_CTL_DEVAD,
					MDIO_848xx_CMD_HDLR_DATA1 + idx,
					&cmd_args[idx]);
		पूर्ण
	पूर्ण
	अगर (val == PHY84833_STATUS_CMD_COMPLETE_ERROR ||
	    val == PHY84833_STATUS_CMD_COMPLETE_PASS) अणु
		bnx2x_cl45_ग_लिखो(bp, phy, MDIO_CTL_DEVAD,
				 MDIO_848xx_CMD_HDLR_STATUS,
				 PHY84833_STATUS_CMD_CLEAR_COMPLETE);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक bnx2x_848xx_cmd_hdlr(काष्ठा bnx2x_phy *phy,
				काष्ठा link_params *params,
				u16 fw_cmd,
					   u16 cmd_args[], पूर्णांक argc,
					   पूर्णांक process)
अणु
	काष्ठा bnx2x *bp = params->bp;

	अगर ((phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84858) ||
	    (REG_RD(bp, params->shmem2_base +
		    दुरत्व(काष्ठा shmem2_region,
			     link_attr_sync[params->port])) &
	     LINK_ATTR_84858)) अणु
		वापस bnx2x_84858_cmd_hdlr(phy, params, fw_cmd, cmd_args,
					    argc);
	पूर्ण अन्यथा अणु
		वापस bnx2x_84833_cmd_hdlr(phy, params, fw_cmd, cmd_args,
					    argc, process);
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_848xx_pair_swap_cfg(काष्ठा bnx2x_phy *phy,
				     काष्ठा link_params *params,
				     काष्ठा link_vars *vars)
अणु
	u32 pair_swap;
	u16 data[PHY848xx_CMDHDLR_MAX_ARGS];
	पूर्णांक status;
	काष्ठा bnx2x *bp = params->bp;

	/* Check क्रम configuration. */
	pair_swap = REG_RD(bp, params->shmem_base +
			   दुरत्व(काष्ठा shmem_region,
			dev_info.port_hw_config[params->port].xgbt_phy_cfg)) &
		PORT_HW_CFG_RJ45_PAIR_SWAP_MASK;

	अगर (pair_swap == 0)
		वापस 0;

	/* Only the second argument is used क्रम this command */
	data[1] = (u16)pair_swap;

	status = bnx2x_848xx_cmd_hdlr(phy, params,
				      PHY848xx_CMD_SET_PAIR_SWAP, data,
				      2, PHY84833_MB_PROCESS2);
	अगर (status == 0)
		DP(NETIF_MSG_LINK, "Pairswap OK, val=0x%x\n", data[1]);

	वापस status;
पूर्ण

अटल u8 bnx2x_84833_get_reset_gpios(काष्ठा bnx2x *bp,
				      u32 shmem_base_path[],
				      u32 chip_id)
अणु
	u32 reset_pin[2];
	u32 idx;
	u8 reset_gpios;
	अगर (CHIP_IS_E3(bp)) अणु
		/* Assume that these will be GPIOs, not EPIOs. */
		क्रम (idx = 0; idx < 2; idx++) अणु
			/* Map config param to रेजिस्टर bit. */
			reset_pin[idx] = REG_RD(bp, shmem_base_path[idx] +
				दुरत्व(काष्ठा shmem_region,
				dev_info.port_hw_config[0].e3_cmn_pin_cfg));
			reset_pin[idx] = (reset_pin[idx] &
				PORT_HW_CFG_E3_PHY_RESET_MASK) >>
				PORT_HW_CFG_E3_PHY_RESET_SHIFT;
			reset_pin[idx] -= PIN_CFG_GPIO0_P0;
			reset_pin[idx] = (1 << reset_pin[idx]);
		पूर्ण
		reset_gpios = (u8)(reset_pin[0] | reset_pin[1]);
	पूर्ण अन्यथा अणु
		/* E2, look from dअगरf place of shmem. */
		क्रम (idx = 0; idx < 2; idx++) अणु
			reset_pin[idx] = REG_RD(bp, shmem_base_path[idx] +
				दुरत्व(काष्ठा shmem_region,
				dev_info.port_hw_config[0].शेष_cfg));
			reset_pin[idx] &= PORT_HW_CFG_EXT_PHY_GPIO_RST_MASK;
			reset_pin[idx] -= PORT_HW_CFG_EXT_PHY_GPIO_RST_GPIO0_P0;
			reset_pin[idx] >>= PORT_HW_CFG_EXT_PHY_GPIO_RST_SHIFT;
			reset_pin[idx] = (1 << reset_pin[idx]);
		पूर्ण
		reset_gpios = (u8)(reset_pin[0] | reset_pin[1]);
	पूर्ण

	वापस reset_gpios;
पूर्ण

अटल व्योम bnx2x_84833_hw_reset_phy(काष्ठा bnx2x_phy *phy,
				     काष्ठा link_params *params)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u8 reset_gpios;
	u32 other_shmem_base_addr = REG_RD(bp, params->shmem2_base +
				दुरत्व(काष्ठा shmem2_region,
				other_shmem_base_addr));

	u32 shmem_base_path[2];

	/* Work around क्रम 84833 LED failure inside RESET status */
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_AN_DEVAD,
		MDIO_AN_REG_8481_LEGACY_MII_CTRL,
		MDIO_AN_REG_8481_MII_CTRL_FORCE_1G);
	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_AN_DEVAD,
		MDIO_AN_REG_8481_1G_100T_EXT_CTRL,
		MIDO_AN_REG_8481_EXT_CTRL_FORCE_LEDS_OFF);

	shmem_base_path[0] = params->shmem_base;
	shmem_base_path[1] = other_shmem_base_addr;

	reset_gpios = bnx2x_84833_get_reset_gpios(bp, shmem_base_path,
						  params->chip_id);

	bnx2x_set_mult_gpio(bp, reset_gpios, MISC_REGISTERS_GPIO_OUTPUT_LOW);
	udelay(10);
	DP(NETIF_MSG_LINK, "84833 hw reset on pin values 0x%x\n",
		reset_gpios);
पूर्ण

अटल पूर्णांक bnx2x_8483x_disable_eee(काष्ठा bnx2x_phy *phy,
				   काष्ठा link_params *params,
				   काष्ठा link_vars *vars)
अणु
	पूर्णांक rc;
	काष्ठा bnx2x *bp = params->bp;
	u16 cmd_args = 0;

	DP(NETIF_MSG_LINK, "Don't Advertise 10GBase-T EEE\n");

	/* Prevent Phy from working in EEE and advertising it */
	rc = bnx2x_848xx_cmd_hdlr(phy, params, PHY848xx_CMD_SET_EEE_MODE,
				  &cmd_args, 1, PHY84833_MB_PROCESS1);
	अगर (rc) अणु
		DP(NETIF_MSG_LINK, "EEE disable failed.\n");
		वापस rc;
	पूर्ण

	वापस bnx2x_eee_disable(phy, params, vars);
पूर्ण

अटल पूर्णांक bnx2x_8483x_enable_eee(काष्ठा bnx2x_phy *phy,
				   काष्ठा link_params *params,
				   काष्ठा link_vars *vars)
अणु
	पूर्णांक rc;
	काष्ठा bnx2x *bp = params->bp;
	u16 cmd_args = 1;

	rc = bnx2x_848xx_cmd_hdlr(phy, params, PHY848xx_CMD_SET_EEE_MODE,
				  &cmd_args, 1, PHY84833_MB_PROCESS1);
	अगर (rc) अणु
		DP(NETIF_MSG_LINK, "EEE enable failed.\n");
		वापस rc;
	पूर्ण

	वापस bnx2x_eee_advertise(phy, params, vars, SHMEM_EEE_10G_ADV);
पूर्ण

#घोषणा PHY84833_CONSTANT_LATENCY 1193
अटल व्योम bnx2x_848x3_config_init(काष्ठा bnx2x_phy *phy,
				    काष्ठा link_params *params,
				    काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u8 port, initialize = 1;
	u16 val;
	u32 actual_phy_selection;
	u16 cmd_args[PHY848xx_CMDHDLR_MAX_ARGS];
	पूर्णांक rc = 0;

	usleep_range(1000, 2000);

	अगर (!(CHIP_IS_E1x(bp)))
		port = BP_PATH(bp);
	अन्यथा
		port = params->port;

	अगर (phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84823) अणु
		bnx2x_set_gpio(bp, MISC_REGISTERS_GPIO_3,
			       MISC_REGISTERS_GPIO_OUTPUT_HIGH,
			       port);
	पूर्ण अन्यथा अणु
		/* MDIO reset */
		bnx2x_cl45_ग_लिखो(bp, phy,
				MDIO_PMA_DEVAD,
				MDIO_PMA_REG_CTRL, 0x8000);
	पूर्ण

	bnx2x_रुको_reset_complete(bp, phy, params);

	/* Wait क्रम GPHY to come out of reset */
	msleep(50);
	अगर (!bnx2x_is_8483x_8485x(phy)) अणु
		/* BCM84823 requires that XGXS links up first @ 10G क्रम normal
		 * behavior.
		 */
		u16 temp;
		temp = vars->line_speed;
		vars->line_speed = SPEED_10000;
		bnx2x_set_स्वतःneg(&params->phy[INT_PHY], params, vars, 0);
		bnx2x_program_serdes(&params->phy[INT_PHY], params, vars);
		vars->line_speed = temp;
	पूर्ण
	/* Check अगर this is actually BCM84858 */
	अगर (phy->type != PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84858) अणु
		u16 hw_rev;

		bnx2x_cl45_पढ़ो(bp, phy, MDIO_AN_DEVAD,
				MDIO_AN_REG_848xx_ID_MSB, &hw_rev);
		अगर (hw_rev == BCM84858_PHY_ID) अणु
			params->link_attr_sync |= LINK_ATTR_84858;
			bnx2x_update_link_attr(params, params->link_attr_sync);
		पूर्ण
	पूर्ण

	/* Set dual-media configuration according to configuration */
	bnx2x_cl45_पढ़ो(bp, phy, MDIO_CTL_DEVAD,
			MDIO_CTL_REG_84823_MEDIA, &val);
	val &= ~(MDIO_CTL_REG_84823_MEDIA_MAC_MASK |
		 MDIO_CTL_REG_84823_MEDIA_LINE_MASK |
		 MDIO_CTL_REG_84823_MEDIA_COPPER_CORE_DOWN |
		 MDIO_CTL_REG_84823_MEDIA_PRIORITY_MASK |
		 MDIO_CTL_REG_84823_MEDIA_FIBER_1G);

	अगर (CHIP_IS_E3(bp)) अणु
		val &= ~(MDIO_CTL_REG_84823_MEDIA_MAC_MASK |
			 MDIO_CTL_REG_84823_MEDIA_LINE_MASK);
	पूर्ण अन्यथा अणु
		val |= (MDIO_CTL_REG_84823_CTRL_MAC_XFI |
			MDIO_CTL_REG_84823_MEDIA_LINE_XAUI_L);
	पूर्ण

	actual_phy_selection = bnx2x_phy_selection(params);

	चयन (actual_phy_selection) अणु
	हाल PORT_HW_CFG_PHY_SELECTION_HARDWARE_DEFAULT:
		/* Do nothing. Essentially this is like the priority copper */
		अवरोध;
	हाल PORT_HW_CFG_PHY_SELECTION_FIRST_PHY_PRIORITY:
		val |= MDIO_CTL_REG_84823_MEDIA_PRIORITY_COPPER;
		अवरोध;
	हाल PORT_HW_CFG_PHY_SELECTION_SECOND_PHY_PRIORITY:
		val |= MDIO_CTL_REG_84823_MEDIA_PRIORITY_FIBER;
		अवरोध;
	हाल PORT_HW_CFG_PHY_SELECTION_FIRST_PHY:
		/* Do nothing here. The first PHY won't be initialized at all */
		अवरोध;
	हाल PORT_HW_CFG_PHY_SELECTION_SECOND_PHY:
		val |= MDIO_CTL_REG_84823_MEDIA_COPPER_CORE_DOWN;
		initialize = 0;
		अवरोध;
	पूर्ण
	अगर (params->phy[EXT_PHY2].req_line_speed == SPEED_1000)
		val |= MDIO_CTL_REG_84823_MEDIA_FIBER_1G;

	bnx2x_cl45_ग_लिखो(bp, phy, MDIO_CTL_DEVAD,
			 MDIO_CTL_REG_84823_MEDIA, val);
	DP(NETIF_MSG_LINK, "Multi_phy config = 0x%x, Media control = 0x%x\n",
		   params->multi_phy_config, val);

	अगर (bnx2x_is_8483x_8485x(phy)) अणु
		bnx2x_848xx_pair_swap_cfg(phy, params, vars);

		/* Keep AutogrEEEn disabled. */
		cmd_args[0] = 0x0;
		cmd_args[1] = 0x0;
		cmd_args[2] = PHY84833_CONSTANT_LATENCY + 1;
		cmd_args[3] = PHY84833_CONSTANT_LATENCY;
		rc = bnx2x_848xx_cmd_hdlr(phy, params,
					  PHY848xx_CMD_SET_EEE_MODE, cmd_args,
					  4, PHY84833_MB_PROCESS1);
		अगर (rc)
			DP(NETIF_MSG_LINK, "Cfg AutogrEEEn failed.\n");
	पूर्ण
	अगर (initialize)
		rc = bnx2x_848xx_cmn_config_init(phy, params, vars);
	अन्यथा
		bnx2x_save_848xx_spirom_version(phy, bp, params->port);
	/* 84833 PHY has a better feature and करोesn't need to support this. */
	अगर (phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84823) अणु
		u32 cms_enable = REG_RD(bp, params->shmem_base +
			दुरत्व(काष्ठा shmem_region,
			dev_info.port_hw_config[params->port].शेष_cfg)) &
			PORT_HW_CFG_ENABLE_CMS_MASK;

		bnx2x_cl45_पढ़ो(bp, phy, MDIO_CTL_DEVAD,
				MDIO_CTL_REG_84823_USER_CTRL_REG, &val);
		अगर (cms_enable)
			val |= MDIO_CTL_REG_84823_USER_CTRL_CMS;
		अन्यथा
			val &= ~MDIO_CTL_REG_84823_USER_CTRL_CMS;
		bnx2x_cl45_ग_लिखो(bp, phy, MDIO_CTL_DEVAD,
				 MDIO_CTL_REG_84823_USER_CTRL_REG, val);
	पूर्ण

	bnx2x_cl45_पढ़ो(bp, phy, MDIO_CTL_DEVAD,
			MDIO_84833_TOP_CFG_FW_REV, &val);

	/* Configure EEE support */
	अगर ((val >= MDIO_84833_TOP_CFG_FW_EEE) &&
	    (val != MDIO_84833_TOP_CFG_FW_NO_EEE) &&
	    bnx2x_eee_has_cap(params)) अणु
		rc = bnx2x_eee_initial_config(params, vars, SHMEM_EEE_10G_ADV);
		अगर (rc) अणु
			DP(NETIF_MSG_LINK, "Failed to configure EEE timers\n");
			bnx2x_8483x_disable_eee(phy, params, vars);
			वापस;
		पूर्ण

		अगर ((phy->req_duplex == DUPLEX_FULL) &&
		    (params->eee_mode & EEE_MODE_ADV_LPI) &&
		    (bnx2x_eee_calc_समयr(params) ||
		     !(params->eee_mode & EEE_MODE_ENABLE_LPI)))
			rc = bnx2x_8483x_enable_eee(phy, params, vars);
		अन्यथा
			rc = bnx2x_8483x_disable_eee(phy, params, vars);
		अगर (rc) अणु
			DP(NETIF_MSG_LINK, "Failed to set EEE advertisement\n");
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		vars->eee_status &= ~SHMEM_EEE_SUPPORTED_MASK;
	पूर्ण

	अगर (phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84833) अणु
		/* Additional settings क्रम jumbo packets in 1000BASE-T mode */
		/* Allow rx extended length */
		bnx2x_cl45_पढ़ो(bp, phy, MDIO_AN_DEVAD,
				MDIO_AN_REG_8481_AUX_CTRL, &val);
		val |= 0x4000;
		bnx2x_cl45_ग_लिखो(bp, phy, MDIO_AN_DEVAD,
				 MDIO_AN_REG_8481_AUX_CTRL, val);
		/* TX FIFO Elasticity LSB */
		bnx2x_cl45_पढ़ो(bp, phy, MDIO_AN_DEVAD,
				MDIO_AN_REG_8481_1G_100T_EXT_CTRL, &val);
		val |= 0x1;
		bnx2x_cl45_ग_लिखो(bp, phy, MDIO_AN_DEVAD,
				 MDIO_AN_REG_8481_1G_100T_EXT_CTRL, val);
		/* TX FIFO Elasticity MSB */
		/* Enable expansion रेजिस्टर 0x46 (Pattern Generator status) */
		bnx2x_cl45_ग_लिखो(bp, phy, MDIO_AN_DEVAD,
				 MDIO_AN_REG_8481_EXPANSION_REG_ACCESS, 0xf46);

		bnx2x_cl45_पढ़ो(bp, phy, MDIO_AN_DEVAD,
				MDIO_AN_REG_8481_EXPANSION_REG_RD_RW, &val);
		val |= 0x4000;
		bnx2x_cl45_ग_लिखो(bp, phy, MDIO_AN_DEVAD,
				 MDIO_AN_REG_8481_EXPANSION_REG_RD_RW, val);
	पूर्ण

	अगर (bnx2x_is_8483x_8485x(phy)) अणु
		/* Bring PHY out of super isolate mode as the final step. */
		bnx2x_cl45_पढ़ो_and_ग_लिखो(bp, phy,
					  MDIO_CTL_DEVAD,
					  MDIO_84833_TOP_CFG_XGPHY_STRAP1,
					  (u16)~MDIO_84833_SUPER_ISOLATE);
	पूर्ण
पूर्ण

अटल u8 bnx2x_848xx_पढ़ो_status(काष्ठा bnx2x_phy *phy,
				  काष्ठा link_params *params,
				  काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 val, val1, val2;
	u8 link_up = 0;


	/* Check 10G-BaseT link status */
	/* Check PMD संकेत ok */
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_AN_DEVAD, 0xFFFA, &val1);
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_8481_PMD_SIGNAL,
			&val2);
	DP(NETIF_MSG_LINK, "BCM848xx: PMD_SIGNAL 1.a811 = 0x%x\n", val2);

	/* Check link 10G */
	अगर (val2 & (1<<11)) अणु
		vars->line_speed = SPEED_10000;
		vars->duplex = DUPLEX_FULL;
		link_up = 1;
		bnx2x_ext_phy_10G_an_resolve(bp, phy, vars);
	पूर्ण अन्यथा अणु /* Check Legacy speed link */
		u16 legacy_status, legacy_speed;

		/* Enable expansion रेजिस्टर 0x42 (Operation mode status) */
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_AN_DEVAD,
				 MDIO_AN_REG_8481_EXPANSION_REG_ACCESS, 0xf42);

		/* Get legacy speed operation status */
		bnx2x_cl45_पढ़ो(bp, phy,
				MDIO_AN_DEVAD,
				MDIO_AN_REG_8481_EXPANSION_REG_RD_RW,
				&legacy_status);

		DP(NETIF_MSG_LINK, "Legacy speed status = 0x%x\n",
		   legacy_status);
		link_up = ((legacy_status & (1<<11)) == (1<<11));
		legacy_speed = (legacy_status & (3<<9));
		अगर (legacy_speed == (0<<9))
			vars->line_speed = SPEED_10;
		अन्यथा अगर (legacy_speed == (1<<9))
			vars->line_speed = SPEED_100;
		अन्यथा अगर (legacy_speed == (2<<9))
			vars->line_speed = SPEED_1000;
		अन्यथा अणु /* Should not happen: Treat as link करोwn */
			vars->line_speed = 0;
			link_up = 0;
		पूर्ण

		अगर (link_up) अणु
			अगर (legacy_status & (1<<8))
				vars->duplex = DUPLEX_FULL;
			अन्यथा
				vars->duplex = DUPLEX_HALF;

			DP(NETIF_MSG_LINK,
			   "Link is up in %dMbps, is_duplex_full= %d\n",
			   vars->line_speed,
			   (vars->duplex == DUPLEX_FULL));
			/* Check legacy speed AN resolution */
			bnx2x_cl45_पढ़ो(bp, phy,
					MDIO_AN_DEVAD,
					MDIO_AN_REG_8481_LEGACY_MII_STATUS,
					&val);
			अगर (val & (1<<5))
				vars->link_status |=
					LINK_STATUS_AUTO_NEGOTIATE_COMPLETE;
			bnx2x_cl45_पढ़ो(bp, phy,
					MDIO_AN_DEVAD,
					MDIO_AN_REG_8481_LEGACY_AN_EXPANSION,
					&val);
			अगर ((val & (1<<0)) == 0)
				vars->link_status |=
					LINK_STATUS_PARALLEL_DETECTION_USED;
		पूर्ण
	पूर्ण
	अगर (link_up) अणु
		DP(NETIF_MSG_LINK, "BCM848x3: link speed is %d\n",
			   vars->line_speed);
		bnx2x_ext_phy_resolve_fc(phy, params, vars);

		/* Read LP advertised speeds */
		bnx2x_cl45_पढ़ो(bp, phy, MDIO_AN_DEVAD,
				MDIO_AN_REG_CL37_FC_LP, &val);
		अगर (val & (1<<5))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_10THD_CAPABLE;
		अगर (val & (1<<6))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_10TFD_CAPABLE;
		अगर (val & (1<<7))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_100TXHD_CAPABLE;
		अगर (val & (1<<8))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_100TXFD_CAPABLE;
		अगर (val & (1<<9))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_100T4_CAPABLE;

		bnx2x_cl45_पढ़ो(bp, phy, MDIO_AN_DEVAD,
				MDIO_AN_REG_1000T_STATUS, &val);

		अगर (val & (1<<10))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_1000THD_CAPABLE;
		अगर (val & (1<<11))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_1000TFD_CAPABLE;

		bnx2x_cl45_पढ़ो(bp, phy, MDIO_AN_DEVAD,
				MDIO_AN_REG_MASTER_STATUS, &val);

		अगर (val & (1<<11))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_10GXFD_CAPABLE;

		/* Determine अगर EEE was negotiated */
		अगर (bnx2x_is_8483x_8485x(phy))
			bnx2x_eee_an_resolve(phy, params, vars);
	पूर्ण

	वापस link_up;
पूर्ण

अटल पूर्णांक bnx2x_8485x_क्रमmat_ver(u32 raw_ver, u8 *str, u16 *len)
अणु
	u32 num;

	num = ((raw_ver & 0xF80) >> 7) << 16 | ((raw_ver & 0x7F) << 8) |
	      ((raw_ver & 0xF000) >> 12);
	वापस bnx2x_3_seq_क्रमmat_ver(num, str, len);
पूर्ण

अटल पूर्णांक bnx2x_848xx_क्रमmat_ver(u32 raw_ver, u8 *str, u16 *len)
अणु
	u32 spirom_ver;

	spirom_ver = ((raw_ver & 0xF80) >> 7) << 16 | (raw_ver & 0x7F);
	वापस bnx2x_क्रमmat_ver(spirom_ver, str, len);
पूर्ण

अटल व्योम bnx2x_8481_hw_reset(काष्ठा bnx2x_phy *phy,
				काष्ठा link_params *params)
अणु
	bnx2x_set_gpio(params->bp, MISC_REGISTERS_GPIO_1,
		       MISC_REGISTERS_GPIO_OUTPUT_LOW, 0);
	bnx2x_set_gpio(params->bp, MISC_REGISTERS_GPIO_1,
		       MISC_REGISTERS_GPIO_OUTPUT_LOW, 1);
पूर्ण

अटल व्योम bnx2x_8481_link_reset(काष्ठा bnx2x_phy *phy,
					काष्ठा link_params *params)
अणु
	bnx2x_cl45_ग_लिखो(params->bp, phy,
			 MDIO_AN_DEVAD, MDIO_AN_REG_CTRL, 0x0000);
	bnx2x_cl45_ग_लिखो(params->bp, phy,
			 MDIO_PMA_DEVAD, MDIO_PMA_REG_CTRL, 1);
पूर्ण

अटल व्योम bnx2x_848x3_link_reset(काष्ठा bnx2x_phy *phy,
				   काष्ठा link_params *params)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u8 port;
	u16 val16;

	अगर (!(CHIP_IS_E1x(bp)))
		port = BP_PATH(bp);
	अन्यथा
		port = params->port;

	अगर (phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84823) अणु
		bnx2x_set_gpio(bp, MISC_REGISTERS_GPIO_3,
			       MISC_REGISTERS_GPIO_OUTPUT_LOW,
			       port);
	पूर्ण अन्यथा अणु
		bnx2x_cl45_पढ़ो(bp, phy,
				MDIO_CTL_DEVAD,
				MDIO_84833_TOP_CFG_XGPHY_STRAP1, &val16);
		val16 |= MDIO_84833_SUPER_ISOLATE;
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_CTL_DEVAD,
				 MDIO_84833_TOP_CFG_XGPHY_STRAP1, val16);
	पूर्ण
पूर्ण

अटल व्योम bnx2x_848xx_set_link_led(काष्ठा bnx2x_phy *phy,
				     काष्ठा link_params *params, u8 mode)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 val;
	u8 port;

	अगर (!(CHIP_IS_E1x(bp)))
		port = BP_PATH(bp);
	अन्यथा
		port = params->port;

	चयन (mode) अणु
	हाल LED_MODE_OFF:

		DP(NETIF_MSG_LINK, "Port 0x%x: LED MODE OFF\n", port);

		अगर ((params->hw_led_mode << SHARED_HW_CFG_LED_MODE_SHIFT) ==
		    SHARED_HW_CFG_LED_EXTPHY1) अणु

			/* Set LED masks */
			bnx2x_cl45_ग_लिखो(bp, phy,
					MDIO_PMA_DEVAD,
					MDIO_PMA_REG_8481_LED1_MASK,
					0x0);

			bnx2x_cl45_ग_लिखो(bp, phy,
					MDIO_PMA_DEVAD,
					MDIO_PMA_REG_8481_LED2_MASK,
					0x0);

			bnx2x_cl45_ग_लिखो(bp, phy,
					MDIO_PMA_DEVAD,
					MDIO_PMA_REG_8481_LED3_MASK,
					0x0);

			bnx2x_cl45_ग_लिखो(bp, phy,
					MDIO_PMA_DEVAD,
					MDIO_PMA_REG_8481_LED5_MASK,
					0x0);

		पूर्ण अन्यथा अणु
			/* LED 1 OFF */
			bnx2x_cl45_ग_लिखो(bp, phy,
					 MDIO_PMA_DEVAD,
					 MDIO_PMA_REG_8481_LED1_MASK,
					 0x0);

			अगर (phy->type ==
				PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84858) अणु
				/* LED 2 OFF */
				bnx2x_cl45_ग_लिखो(bp, phy,
						 MDIO_PMA_DEVAD,
						 MDIO_PMA_REG_8481_LED2_MASK,
						 0x0);
				/* LED 3 OFF */
				bnx2x_cl45_ग_लिखो(bp, phy,
						 MDIO_PMA_DEVAD,
						 MDIO_PMA_REG_8481_LED3_MASK,
						 0x0);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल LED_MODE_FRONT_PANEL_OFF:

		DP(NETIF_MSG_LINK, "Port 0x%x: LED MODE FRONT PANEL OFF\n",
		   port);

		अगर ((params->hw_led_mode << SHARED_HW_CFG_LED_MODE_SHIFT) ==
		    SHARED_HW_CFG_LED_EXTPHY1) अणु

			/* Set LED masks */
			bnx2x_cl45_ग_लिखो(bp, phy,
					 MDIO_PMA_DEVAD,
					 MDIO_PMA_REG_8481_LED1_MASK,
					 0x0);

			bnx2x_cl45_ग_लिखो(bp, phy,
					 MDIO_PMA_DEVAD,
					 MDIO_PMA_REG_8481_LED2_MASK,
					 0x0);

			bnx2x_cl45_ग_लिखो(bp, phy,
					 MDIO_PMA_DEVAD,
					 MDIO_PMA_REG_8481_LED3_MASK,
					 0x0);

			bnx2x_cl45_ग_लिखो(bp, phy,
					 MDIO_PMA_DEVAD,
					 MDIO_PMA_REG_8481_LED5_MASK,
					 0x20);

		पूर्ण अन्यथा अणु
			bnx2x_cl45_ग_लिखो(bp, phy,
					 MDIO_PMA_DEVAD,
					 MDIO_PMA_REG_8481_LED1_MASK,
					 0x0);
			अगर (phy->type ==
			    PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84834) अणु
				/* Disable MI_INT पूर्णांकerrupt beक्रमe setting LED4
				 * source to स्थिरant off.
				 */
				अगर (REG_RD(bp, NIG_REG_MASK_INTERRUPT_PORT0 +
					   params->port*4) &
				    NIG_MASK_MI_INT) अणु
					params->link_flags |=
					LINK_FLAGS_INT_DISABLED;

					bnx2x_bits_dis(
						bp,
						NIG_REG_MASK_INTERRUPT_PORT0 +
						params->port*4,
						NIG_MASK_MI_INT);
				पूर्ण
				bnx2x_cl45_ग_लिखो(bp, phy,
						 MDIO_PMA_DEVAD,
						 MDIO_PMA_REG_8481_SIGNAL_MASK,
						 0x0);
			पूर्ण
			अगर (phy->type ==
				PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84858) अणु
				/* LED 2 OFF */
				bnx2x_cl45_ग_लिखो(bp, phy,
						 MDIO_PMA_DEVAD,
						 MDIO_PMA_REG_8481_LED2_MASK,
						 0x0);
				/* LED 3 OFF */
				bnx2x_cl45_ग_लिखो(bp, phy,
						 MDIO_PMA_DEVAD,
						 MDIO_PMA_REG_8481_LED3_MASK,
						 0x0);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल LED_MODE_ON:

		DP(NETIF_MSG_LINK, "Port 0x%x: LED MODE ON\n", port);

		अगर ((params->hw_led_mode << SHARED_HW_CFG_LED_MODE_SHIFT) ==
		    SHARED_HW_CFG_LED_EXTPHY1) अणु
			/* Set control reg */
			bnx2x_cl45_पढ़ो(bp, phy,
					MDIO_PMA_DEVAD,
					MDIO_PMA_REG_8481_LINK_SIGNAL,
					&val);
			val &= 0x8000;
			val |= 0x2492;

			bnx2x_cl45_ग_लिखो(bp, phy,
					 MDIO_PMA_DEVAD,
					 MDIO_PMA_REG_8481_LINK_SIGNAL,
					 val);

			/* Set LED masks */
			bnx2x_cl45_ग_लिखो(bp, phy,
					 MDIO_PMA_DEVAD,
					 MDIO_PMA_REG_8481_LED1_MASK,
					 0x0);

			bnx2x_cl45_ग_लिखो(bp, phy,
					 MDIO_PMA_DEVAD,
					 MDIO_PMA_REG_8481_LED2_MASK,
					 0x20);

			bnx2x_cl45_ग_लिखो(bp, phy,
					 MDIO_PMA_DEVAD,
					 MDIO_PMA_REG_8481_LED3_MASK,
					 0x20);

			bnx2x_cl45_ग_लिखो(bp, phy,
					 MDIO_PMA_DEVAD,
					 MDIO_PMA_REG_8481_LED5_MASK,
					 0x0);
		पूर्ण अन्यथा अणु
			bnx2x_cl45_ग_लिखो(bp, phy,
					 MDIO_PMA_DEVAD,
					 MDIO_PMA_REG_8481_LED1_MASK,
					 0x20);
			अगर (phy->type ==
			    PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84834) अणु
				/* Disable MI_INT पूर्णांकerrupt beक्रमe setting LED4
				 * source to स्थिरant on.
				 */
				अगर (REG_RD(bp, NIG_REG_MASK_INTERRUPT_PORT0 +
					   params->port*4) &
				    NIG_MASK_MI_INT) अणु
					params->link_flags |=
					LINK_FLAGS_INT_DISABLED;

					bnx2x_bits_dis(
						bp,
						NIG_REG_MASK_INTERRUPT_PORT0 +
						params->port*4,
						NIG_MASK_MI_INT);
				पूर्ण
			पूर्ण
			अगर (phy->type ==
			    PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84858) अणु
				/* Tell LED3 to स्थिरant on */
				bnx2x_cl45_पढ़ो(bp, phy,
						MDIO_PMA_DEVAD,
						MDIO_PMA_REG_8481_LINK_SIGNAL,
						&val);
				val &= ~(7<<6);
				val |= (2<<6);  /* A83B[8:6]= 2 */
				bnx2x_cl45_ग_लिखो(bp, phy,
						 MDIO_PMA_DEVAD,
						 MDIO_PMA_REG_8481_LINK_SIGNAL,
						 val);
				bnx2x_cl45_ग_लिखो(bp, phy,
						 MDIO_PMA_DEVAD,
						 MDIO_PMA_REG_8481_LED3_MASK,
						 0x20);
			पूर्ण अन्यथा अणु
				bnx2x_cl45_ग_लिखो(bp, phy,
						 MDIO_PMA_DEVAD,
						 MDIO_PMA_REG_8481_SIGNAL_MASK,
						 0x20);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल LED_MODE_OPER:

		DP(NETIF_MSG_LINK, "Port 0x%x: LED MODE OPER\n", port);

		अगर ((params->hw_led_mode << SHARED_HW_CFG_LED_MODE_SHIFT) ==
		    SHARED_HW_CFG_LED_EXTPHY1) अणु

			/* Set control reg */
			bnx2x_cl45_पढ़ो(bp, phy,
					MDIO_PMA_DEVAD,
					MDIO_PMA_REG_8481_LINK_SIGNAL,
					&val);

			अगर (!((val &
			       MDIO_PMA_REG_8481_LINK_SIGNAL_LED4_ENABLE_MASK)
			  >> MDIO_PMA_REG_8481_LINK_SIGNAL_LED4_ENABLE_SHIFT)) अणु
				DP(NETIF_MSG_LINK, "Setting LINK_SIGNAL\n");
				bnx2x_cl45_ग_लिखो(bp, phy,
						 MDIO_PMA_DEVAD,
						 MDIO_PMA_REG_8481_LINK_SIGNAL,
						 0xa492);
			पूर्ण

			/* Set LED masks */
			bnx2x_cl45_ग_लिखो(bp, phy,
					 MDIO_PMA_DEVAD,
					 MDIO_PMA_REG_8481_LED1_MASK,
					 0x10);

			bnx2x_cl45_ग_लिखो(bp, phy,
					 MDIO_PMA_DEVAD,
					 MDIO_PMA_REG_8481_LED2_MASK,
					 0x80);

			bnx2x_cl45_ग_लिखो(bp, phy,
					 MDIO_PMA_DEVAD,
					 MDIO_PMA_REG_8481_LED3_MASK,
					 0x98);

			bnx2x_cl45_ग_लिखो(bp, phy,
					 MDIO_PMA_DEVAD,
					 MDIO_PMA_REG_8481_LED5_MASK,
					 0x40);

		पूर्ण अन्यथा अणु
			/* EXTPHY2 LED mode indicate that the 100M/1G/10G LED
			 * sources are all wired through LED1, rather than only
			 * 10G in other modes.
			 */
			val = ((params->hw_led_mode <<
				SHARED_HW_CFG_LED_MODE_SHIFT) ==
			       SHARED_HW_CFG_LED_EXTPHY2) ? 0x98 : 0x80;

			bnx2x_cl45_ग_लिखो(bp, phy,
					 MDIO_PMA_DEVAD,
					 MDIO_PMA_REG_8481_LED1_MASK,
					 val);

			/* Tell LED3 to blink on source */
			bnx2x_cl45_पढ़ो(bp, phy,
					MDIO_PMA_DEVAD,
					MDIO_PMA_REG_8481_LINK_SIGNAL,
					&val);
			val &= ~(7<<6);
			val |= (1<<6); /* A83B[8:6]= 1 */
			bnx2x_cl45_ग_लिखो(bp, phy,
					 MDIO_PMA_DEVAD,
					 MDIO_PMA_REG_8481_LINK_SIGNAL,
					 val);
			अगर (phy->type ==
			    PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84858) अणु
				bnx2x_cl45_ग_लिखो(bp, phy,
						 MDIO_PMA_DEVAD,
						 MDIO_PMA_REG_8481_LED2_MASK,
						 0x18);
				bnx2x_cl45_ग_लिखो(bp, phy,
						 MDIO_PMA_DEVAD,
						 MDIO_PMA_REG_8481_LED3_MASK,
						 0x06);
			पूर्ण
			अगर (phy->type ==
			    PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84834) अणु
				/* Restore LED4 source to बाह्यal link,
				 * and re-enable पूर्णांकerrupts.
				 */
				bnx2x_cl45_ग_लिखो(bp, phy,
						 MDIO_PMA_DEVAD,
						 MDIO_PMA_REG_8481_SIGNAL_MASK,
						 0x40);
				अगर (params->link_flags &
				    LINK_FLAGS_INT_DISABLED) अणु
					bnx2x_link_पूर्णांक_enable(params);
					params->link_flags &=
						~LINK_FLAGS_INT_DISABLED;
				पूर्ण
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

	/* This is a workaround क्रम E3+84833 until स्वतःneg
	 * restart is fixed in f/w
	 */
	अगर (CHIP_IS_E3(bp)) अणु
		bnx2x_cl45_पढ़ो(bp, phy, MDIO_WC_DEVAD,
				MDIO_WC_REG_GP2_STATUS_GP_2_1, &val);
	पूर्ण
पूर्ण

/******************************************************************/
/*			54618SE PHY SECTION			  */
/******************************************************************/
अटल व्योम bnx2x_54618se_specअगरic_func(काष्ठा bnx2x_phy *phy,
					काष्ठा link_params *params,
					u32 action)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 temp;
	चयन (action) अणु
	हाल PHY_INIT:
		/* Configure LED4: set to INTR (0x6). */
		/* Accessing shaकरोw रेजिस्टर 0xe. */
		bnx2x_cl22_ग_लिखो(bp, phy,
				 MDIO_REG_GPHY_SHADOW,
				 MDIO_REG_GPHY_SHADOW_LED_SEL2);
		bnx2x_cl22_पढ़ो(bp, phy,
				MDIO_REG_GPHY_SHADOW,
				&temp);
		temp &= ~(0xf << 4);
		temp |= (0x6 << 4);
		bnx2x_cl22_ग_लिखो(bp, phy,
				 MDIO_REG_GPHY_SHADOW,
				 MDIO_REG_GPHY_SHADOW_WR_ENA | temp);
		/* Configure INTR based on link status change. */
		bnx2x_cl22_ग_लिखो(bp, phy,
				 MDIO_REG_INTR_MASK,
				 ~MDIO_REG_INTR_MASK_LINK_STATUS);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम bnx2x_54618se_config_init(काष्ठा bnx2x_phy *phy,
				      काष्ठा link_params *params,
				      काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u8 port;
	u16 स्वतःneg_val, an_1000_val, an_10_100_val, fc_val, temp;
	u32 cfg_pin;

	DP(NETIF_MSG_LINK, "54618SE cfg init\n");
	usleep_range(1000, 2000);

	/* This works with E3 only, no need to check the chip
	 * beक्रमe determining the port.
	 */
	port = params->port;

	cfg_pin = (REG_RD(bp, params->shmem_base +
			दुरत्व(काष्ठा shmem_region,
			dev_info.port_hw_config[port].e3_cmn_pin_cfg)) &
			PORT_HW_CFG_E3_PHY_RESET_MASK) >>
			PORT_HW_CFG_E3_PHY_RESET_SHIFT;

	/* Drive pin high to bring the GPHY out of reset. */
	bnx2x_set_cfg_pin(bp, cfg_pin, 1);

	/* रुको क्रम GPHY to reset */
	msleep(50);

	/* reset phy */
	bnx2x_cl22_ग_लिखो(bp, phy,
			 MDIO_PMA_REG_CTRL, 0x8000);
	bnx2x_रुको_reset_complete(bp, phy, params);

	/* Wait क्रम GPHY to reset */
	msleep(50);


	bnx2x_54618se_specअगरic_func(phy, params, PHY_INIT);
	/* Flip the संकेत detect polarity (set 0x1c.0x1e[8]). */
	bnx2x_cl22_ग_लिखो(bp, phy,
			MDIO_REG_GPHY_SHADOW,
			MDIO_REG_GPHY_SHADOW_AUTO_DET_MED);
	bnx2x_cl22_पढ़ो(bp, phy,
			MDIO_REG_GPHY_SHADOW,
			&temp);
	temp |= MDIO_REG_GPHY_SHADOW_INVERT_FIB_SD;
	bnx2x_cl22_ग_लिखो(bp, phy,
			MDIO_REG_GPHY_SHADOW,
			MDIO_REG_GPHY_SHADOW_WR_ENA | temp);

	/* Set up fc */
	/* Please refer to Table 28B-3 of 802.3ab-1999 spec. */
	bnx2x_calc_ieee_aneg_adv(phy, params, &vars->ieee_fc);
	fc_val = 0;
	अगर ((vars->ieee_fc & MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_ASYMMETRIC) ==
			MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_ASYMMETRIC)
		fc_val |= MDIO_AN_REG_ADV_PAUSE_ASYMMETRIC;

	अगर ((vars->ieee_fc & MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH) ==
			MDIO_COMBO_IEEE0_AUTO_NEG_ADV_PAUSE_BOTH)
		fc_val |= MDIO_AN_REG_ADV_PAUSE_PAUSE;

	/* Read all advertisement */
	bnx2x_cl22_पढ़ो(bp, phy,
			0x09,
			&an_1000_val);

	bnx2x_cl22_पढ़ो(bp, phy,
			0x04,
			&an_10_100_val);

	bnx2x_cl22_पढ़ो(bp, phy,
			MDIO_PMA_REG_CTRL,
			&स्वतःneg_val);

	/* Disable क्रमced speed */
	स्वतःneg_val &= ~((1<<6) | (1<<8) | (1<<9) | (1<<12) | (1<<13));
	an_10_100_val &= ~((1<<5) | (1<<6) | (1<<7) | (1<<8) | (1<<10) |
			   (1<<11));

	अगर (((phy->req_line_speed == SPEED_AUTO_NEG) &&
	     (phy->speed_cap_mask &
	      PORT_HW_CFG_SPEED_CAPABILITY_D0_1G)) ||
	    (phy->req_line_speed == SPEED_1000)) अणु
		an_1000_val |= (1<<8);
		स्वतःneg_val |= (1<<9 | 1<<12);
		अगर (phy->req_duplex == DUPLEX_FULL)
			an_1000_val |= (1<<9);
		DP(NETIF_MSG_LINK, "Advertising 1G\n");
	पूर्ण अन्यथा
		an_1000_val &= ~((1<<8) | (1<<9));

	bnx2x_cl22_ग_लिखो(bp, phy,
			0x09,
			an_1000_val);
	bnx2x_cl22_पढ़ो(bp, phy,
			0x09,
			&an_1000_val);

	/* Advertise 10/100 link speed */
	अगर (phy->req_line_speed == SPEED_AUTO_NEG) अणु
		अगर (phy->speed_cap_mask &
		    PORT_HW_CFG_SPEED_CAPABILITY_D0_10M_HALF) अणु
			an_10_100_val |= (1<<5);
			स्वतःneg_val |= (1<<9 | 1<<12);
			DP(NETIF_MSG_LINK, "Advertising 10M-HD\n");
		पूर्ण
		अगर (phy->speed_cap_mask &
		    PORT_HW_CFG_SPEED_CAPABILITY_D0_10M_FULL) अणु
			an_10_100_val |= (1<<6);
			स्वतःneg_val |= (1<<9 | 1<<12);
			DP(NETIF_MSG_LINK, "Advertising 10M-FD\n");
		पूर्ण
		अगर (phy->speed_cap_mask &
		    PORT_HW_CFG_SPEED_CAPABILITY_D0_100M_HALF) अणु
			an_10_100_val |= (1<<7);
			स्वतःneg_val |= (1<<9 | 1<<12);
			DP(NETIF_MSG_LINK, "Advertising 100M-HD\n");
		पूर्ण
		अगर (phy->speed_cap_mask &
		    PORT_HW_CFG_SPEED_CAPABILITY_D0_100M_FULL) अणु
			an_10_100_val |= (1<<8);
			स्वतःneg_val |= (1<<9 | 1<<12);
			DP(NETIF_MSG_LINK, "Advertising 100M-FD\n");
		पूर्ण
	पूर्ण

	/* Only 10/100 are allowed to work in FORCE mode */
	अगर (phy->req_line_speed == SPEED_100) अणु
		स्वतःneg_val |= (1<<13);
		/* Enabled AUTO-MDIX when स्वतःneg is disabled */
		bnx2x_cl22_ग_लिखो(bp, phy,
				0x18,
				(1<<15 | 1<<9 | 7<<0));
		DP(NETIF_MSG_LINK, "Setting 100M force\n");
	पूर्ण
	अगर (phy->req_line_speed == SPEED_10) अणु
		/* Enabled AUTO-MDIX when स्वतःneg is disabled */
		bnx2x_cl22_ग_लिखो(bp, phy,
				0x18,
				(1<<15 | 1<<9 | 7<<0));
		DP(NETIF_MSG_LINK, "Setting 10M force\n");
	पूर्ण

	अगर ((phy->flags & FLAGS_EEE) && bnx2x_eee_has_cap(params)) अणु
		पूर्णांक rc;

		bnx2x_cl22_ग_लिखो(bp, phy, MDIO_REG_GPHY_EXP_ACCESS,
				 MDIO_REG_GPHY_EXP_ACCESS_TOP |
				 MDIO_REG_GPHY_EXP_TOP_2K_BUF);
		bnx2x_cl22_पढ़ो(bp, phy, MDIO_REG_GPHY_EXP_ACCESS_GATE, &temp);
		temp &= 0xfffe;
		bnx2x_cl22_ग_लिखो(bp, phy, MDIO_REG_GPHY_EXP_ACCESS_GATE, temp);

		rc = bnx2x_eee_initial_config(params, vars, SHMEM_EEE_1G_ADV);
		अगर (rc) अणु
			DP(NETIF_MSG_LINK, "Failed to configure EEE timers\n");
			bnx2x_eee_disable(phy, params, vars);
		पूर्ण अन्यथा अगर ((params->eee_mode & EEE_MODE_ADV_LPI) &&
			   (phy->req_duplex == DUPLEX_FULL) &&
			   (bnx2x_eee_calc_समयr(params) ||
			    !(params->eee_mode & EEE_MODE_ENABLE_LPI))) अणु
			/* Need to advertise EEE only when requested,
			 * and either no LPI निश्चितion was requested,
			 * or it was requested and a valid समयr was set.
			 * Also notice full duplex is required क्रम EEE.
			 */
			bnx2x_eee_advertise(phy, params, vars,
					    SHMEM_EEE_1G_ADV);
		पूर्ण अन्यथा अणु
			DP(NETIF_MSG_LINK, "Don't Advertise 1GBase-T EEE\n");
			bnx2x_eee_disable(phy, params, vars);
		पूर्ण
	पूर्ण अन्यथा अणु
		vars->eee_status &= ~SHMEM_EEE_1G_ADV <<
				    SHMEM_EEE_SUPPORTED_SHIFT;

		अगर (phy->flags & FLAGS_EEE) अणु
			/* Handle legacy स्वतः-grEEEn */
			अगर (params->feature_config_flags &
			    FEATURE_CONFIG_AUTOGREEEN_ENABLED) अणु
				temp = 6;
				DP(NETIF_MSG_LINK, "Enabling Auto-GrEEEn\n");
			पूर्ण अन्यथा अणु
				temp = 0;
				DP(NETIF_MSG_LINK, "Don't Adv. EEE\n");
			पूर्ण
			bnx2x_cl45_ग_लिखो(bp, phy, MDIO_AN_DEVAD,
					 MDIO_AN_REG_EEE_ADV, temp);
		पूर्ण
	पूर्ण

	bnx2x_cl22_ग_लिखो(bp, phy,
			0x04,
			an_10_100_val | fc_val);

	अगर (phy->req_duplex == DUPLEX_FULL)
		स्वतःneg_val |= (1<<8);

	bnx2x_cl22_ग_लिखो(bp, phy,
			MDIO_PMA_REG_CTRL, स्वतःneg_val);
पूर्ण


अटल व्योम bnx2x_5461x_set_link_led(काष्ठा bnx2x_phy *phy,
				       काष्ठा link_params *params, u8 mode)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 temp;

	bnx2x_cl22_ग_लिखो(bp, phy,
		MDIO_REG_GPHY_SHADOW,
		MDIO_REG_GPHY_SHADOW_LED_SEL1);
	bnx2x_cl22_पढ़ो(bp, phy,
		MDIO_REG_GPHY_SHADOW,
		&temp);
	temp &= 0xff00;

	DP(NETIF_MSG_LINK, "54618x set link led (mode=%x)\n", mode);
	चयन (mode) अणु
	हाल LED_MODE_FRONT_PANEL_OFF:
	हाल LED_MODE_OFF:
		temp |= 0x00ee;
		अवरोध;
	हाल LED_MODE_OPER:
		temp |= 0x0001;
		अवरोध;
	हाल LED_MODE_ON:
		temp |= 0x00ff;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	bnx2x_cl22_ग_लिखो(bp, phy,
		MDIO_REG_GPHY_SHADOW,
		MDIO_REG_GPHY_SHADOW_WR_ENA | temp);
	वापस;
पूर्ण


अटल व्योम bnx2x_54618se_link_reset(काष्ठा bnx2x_phy *phy,
				     काष्ठा link_params *params)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u32 cfg_pin;
	u8 port;

	/* In हाल of no EPIO routed to reset the GPHY, put it
	 * in low घातer mode.
	 */
	bnx2x_cl22_ग_लिखो(bp, phy, MDIO_PMA_REG_CTRL, 0x800);
	/* This works with E3 only, no need to check the chip
	 * beक्रमe determining the port.
	 */
	port = params->port;
	cfg_pin = (REG_RD(bp, params->shmem_base +
			दुरत्व(काष्ठा shmem_region,
			dev_info.port_hw_config[port].e3_cmn_pin_cfg)) &
			PORT_HW_CFG_E3_PHY_RESET_MASK) >>
			PORT_HW_CFG_E3_PHY_RESET_SHIFT;

	/* Drive pin low to put GPHY in reset. */
	bnx2x_set_cfg_pin(bp, cfg_pin, 0);
पूर्ण

अटल u8 bnx2x_54618se_पढ़ो_status(काष्ठा bnx2x_phy *phy,
				    काष्ठा link_params *params,
				    काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 val;
	u8 link_up = 0;
	u16 legacy_status, legacy_speed;

	/* Get speed operation status */
	bnx2x_cl22_पढ़ो(bp, phy,
			MDIO_REG_GPHY_AUX_STATUS,
			&legacy_status);
	DP(NETIF_MSG_LINK, "54618SE read_status: 0x%x\n", legacy_status);

	/* Read status to clear the PHY पूर्णांकerrupt. */
	bnx2x_cl22_पढ़ो(bp, phy,
			MDIO_REG_INTR_STATUS,
			&val);

	link_up = ((legacy_status & (1<<2)) == (1<<2));

	अगर (link_up) अणु
		legacy_speed = (legacy_status & (7<<8));
		अगर (legacy_speed == (7<<8)) अणु
			vars->line_speed = SPEED_1000;
			vars->duplex = DUPLEX_FULL;
		पूर्ण अन्यथा अगर (legacy_speed == (6<<8)) अणु
			vars->line_speed = SPEED_1000;
			vars->duplex = DUPLEX_HALF;
		पूर्ण अन्यथा अगर (legacy_speed == (5<<8)) अणु
			vars->line_speed = SPEED_100;
			vars->duplex = DUPLEX_FULL;
		पूर्ण
		/* Omitting 100Base-T4 क्रम now */
		अन्यथा अगर (legacy_speed == (3<<8)) अणु
			vars->line_speed = SPEED_100;
			vars->duplex = DUPLEX_HALF;
		पूर्ण अन्यथा अगर (legacy_speed == (2<<8)) अणु
			vars->line_speed = SPEED_10;
			vars->duplex = DUPLEX_FULL;
		पूर्ण अन्यथा अगर (legacy_speed == (1<<8)) अणु
			vars->line_speed = SPEED_10;
			vars->duplex = DUPLEX_HALF;
		पूर्ण अन्यथा /* Should not happen */
			vars->line_speed = 0;

		DP(NETIF_MSG_LINK,
		   "Link is up in %dMbps, is_duplex_full= %d\n",
		   vars->line_speed,
		   (vars->duplex == DUPLEX_FULL));

		/* Check legacy speed AN resolution */
		bnx2x_cl22_पढ़ो(bp, phy,
				0x01,
				&val);
		अगर (val & (1<<5))
			vars->link_status |=
				LINK_STATUS_AUTO_NEGOTIATE_COMPLETE;
		bnx2x_cl22_पढ़ो(bp, phy,
				0x06,
				&val);
		अगर ((val & (1<<0)) == 0)
			vars->link_status |=
				LINK_STATUS_PARALLEL_DETECTION_USED;

		DP(NETIF_MSG_LINK, "BCM54618SE: link speed is %d\n",
			   vars->line_speed);

		bnx2x_ext_phy_resolve_fc(phy, params, vars);

		अगर (vars->link_status & LINK_STATUS_AUTO_NEGOTIATE_COMPLETE) अणु
			/* Report LP advertised speeds */
			bnx2x_cl22_पढ़ो(bp, phy, 0x5, &val);

			अगर (val & (1<<5))
				vars->link_status |=
				  LINK_STATUS_LINK_PARTNER_10THD_CAPABLE;
			अगर (val & (1<<6))
				vars->link_status |=
				  LINK_STATUS_LINK_PARTNER_10TFD_CAPABLE;
			अगर (val & (1<<7))
				vars->link_status |=
				  LINK_STATUS_LINK_PARTNER_100TXHD_CAPABLE;
			अगर (val & (1<<8))
				vars->link_status |=
				  LINK_STATUS_LINK_PARTNER_100TXFD_CAPABLE;
			अगर (val & (1<<9))
				vars->link_status |=
				  LINK_STATUS_LINK_PARTNER_100T4_CAPABLE;

			bnx2x_cl22_पढ़ो(bp, phy, 0xa, &val);
			अगर (val & (1<<10))
				vars->link_status |=
				  LINK_STATUS_LINK_PARTNER_1000THD_CAPABLE;
			अगर (val & (1<<11))
				vars->link_status |=
				  LINK_STATUS_LINK_PARTNER_1000TFD_CAPABLE;

			अगर ((phy->flags & FLAGS_EEE) &&
			    bnx2x_eee_has_cap(params))
				bnx2x_eee_an_resolve(phy, params, vars);
		पूर्ण
	पूर्ण
	वापस link_up;
पूर्ण

अटल व्योम bnx2x_54618se_config_loopback(काष्ठा bnx2x_phy *phy,
					  काष्ठा link_params *params)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 val;
	u32 umac_base = params->port ? GRCBASE_UMAC1 : GRCBASE_UMAC0;

	DP(NETIF_MSG_LINK, "2PMA/PMD ext_phy_loopback: 54618se\n");

	/* Enable master/slave manual mmode and set to master */
	/* mii ग_लिखो 9 [bits set 11 12] */
	bnx2x_cl22_ग_लिखो(bp, phy, 0x09, 3<<11);

	/* क्रमced 1G and disable स्वतःneg */
	/* set val [mii पढ़ो 0] */
	/* set val [expr $val & [bits clear 6 12 13]] */
	/* set val [expr $val | [bits set 6 8]] */
	/* mii ग_लिखो 0 $val */
	bnx2x_cl22_पढ़ो(bp, phy, 0x00, &val);
	val &= ~((1<<6) | (1<<12) | (1<<13));
	val |= (1<<6) | (1<<8);
	bnx2x_cl22_ग_लिखो(bp, phy, 0x00, val);

	/* Set बाह्यal loopback and Tx using 6dB coding */
	/* mii ग_लिखो 0x18 7 */
	/* set val [mii पढ़ो 0x18] */
	/* mii ग_लिखो 0x18 [expr $val | [bits set 10 15]] */
	bnx2x_cl22_ग_लिखो(bp, phy, 0x18, 7);
	bnx2x_cl22_पढ़ो(bp, phy, 0x18, &val);
	bnx2x_cl22_ग_लिखो(bp, phy, 0x18, val | (1<<10) | (1<<15));

	/* This रेजिस्टर खोलोs the gate क्रम the UMAC despite its name */
	REG_WR(bp, NIG_REG_EGRESS_EMAC0_PORT + params->port*4, 1);

	/* Maximum Frame Length (RW). Defines a 14-Bit maximum frame
	 * length used by the MAC receive logic to check frames.
	 */
	REG_WR(bp, umac_base + UMAC_REG_MAXFR, 0x2710);
पूर्ण

/******************************************************************/
/*			SFX7101 PHY SECTION			  */
/******************************************************************/
अटल व्योम bnx2x_7101_config_loopback(काष्ठा bnx2x_phy *phy,
				       काष्ठा link_params *params)
अणु
	काष्ठा bnx2x *bp = params->bp;
	/* SFX7101_XGXS_TEST1 */
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_XS_DEVAD, MDIO_XS_SFX7101_XGXS_TEST1, 0x100);
पूर्ण

अटल व्योम bnx2x_7101_config_init(काष्ठा bnx2x_phy *phy,
				   काष्ठा link_params *params,
				   काष्ठा link_vars *vars)
अणु
	u16 fw_ver1, fw_ver2, val;
	काष्ठा bnx2x *bp = params->bp;
	DP(NETIF_MSG_LINK, "Setting the SFX7101 LASI indication\n");

	/* Restore normal घातer mode*/
	bnx2x_set_gpio(bp, MISC_REGISTERS_GPIO_2,
		       MISC_REGISTERS_GPIO_OUTPUT_HIGH, params->port);
	/* HW reset */
	bnx2x_ext_phy_hw_reset(bp, params->port);
	bnx2x_रुको_reset_complete(bp, phy, params);

	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD, MDIO_PMA_LASI_CTRL, 0x1);
	DP(NETIF_MSG_LINK, "Setting the SFX7101 LED to blink on traffic\n");
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD, MDIO_PMA_REG_7107_LED_CNTL, (1<<3));

	bnx2x_ext_phy_set_छोड़ो(params, phy, vars);
	/* Restart स्वतःneg */
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_AN_DEVAD, MDIO_AN_REG_CTRL, &val);
	val |= 0x200;
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_AN_DEVAD, MDIO_AN_REG_CTRL, val);

	/* Save spirom version */
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_7101_VER1, &fw_ver1);

	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_7101_VER2, &fw_ver2);
	bnx2x_save_spirom_version(bp, params->port,
				  (u32)(fw_ver1<<16 | fw_ver2), phy->ver_addr);
पूर्ण

अटल u8 bnx2x_7101_पढ़ो_status(काष्ठा bnx2x_phy *phy,
				 काष्ठा link_params *params,
				 काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u8 link_up;
	u16 val1, val2;
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_LASI_STAT, &val2);
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_LASI_STAT, &val1);
	DP(NETIF_MSG_LINK, "10G-base-T LASI status 0x%x->0x%x\n",
		   val2, val1);
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_STATUS, &val2);
	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD, MDIO_PMA_REG_STATUS, &val1);
	DP(NETIF_MSG_LINK, "10G-base-T PMA status 0x%x->0x%x\n",
		   val2, val1);
	link_up = ((val1 & 4) == 4);
	/* If link is up prपूर्णांक the AN outcome of the SFX7101 PHY */
	अगर (link_up) अणु
		bnx2x_cl45_पढ़ो(bp, phy,
				MDIO_AN_DEVAD, MDIO_AN_REG_MASTER_STATUS,
				&val2);
		vars->line_speed = SPEED_10000;
		vars->duplex = DUPLEX_FULL;
		DP(NETIF_MSG_LINK, "SFX7101 AN status 0x%x->Master=%x\n",
			   val2, (val2 & (1<<14)));
		bnx2x_ext_phy_10G_an_resolve(bp, phy, vars);
		bnx2x_ext_phy_resolve_fc(phy, params, vars);

		/* Read LP advertised speeds */
		अगर (val2 & (1<<11))
			vars->link_status |=
				LINK_STATUS_LINK_PARTNER_10GXFD_CAPABLE;
	पूर्ण
	वापस link_up;
पूर्ण

अटल पूर्णांक bnx2x_7101_क्रमmat_ver(u32 spirom_ver, u8 *str, u16 *len)
अणु
	अगर (*len < 5)
		वापस -EINVAL;
	str[0] = (spirom_ver & 0xFF);
	str[1] = (spirom_ver & 0xFF00) >> 8;
	str[2] = (spirom_ver & 0xFF0000) >> 16;
	str[3] = (spirom_ver & 0xFF000000) >> 24;
	str[4] = '\0';
	*len -= 5;
	वापस 0;
पूर्ण

व्योम bnx2x_sfx7101_sp_sw_reset(काष्ठा bnx2x *bp, काष्ठा bnx2x_phy *phy)
अणु
	u16 val, cnt;

	bnx2x_cl45_पढ़ो(bp, phy,
			MDIO_PMA_DEVAD,
			MDIO_PMA_REG_7101_RESET, &val);

	क्रम (cnt = 0; cnt < 10; cnt++) अणु
		msleep(50);
		/* Writes a self-clearing reset */
		bnx2x_cl45_ग_लिखो(bp, phy,
				 MDIO_PMA_DEVAD,
				 MDIO_PMA_REG_7101_RESET,
				 (val | (1<<15)));
		/* Wait क्रम clear */
		bnx2x_cl45_पढ़ो(bp, phy,
				MDIO_PMA_DEVAD,
				MDIO_PMA_REG_7101_RESET, &val);

		अगर ((val & (1<<15)) == 0)
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम bnx2x_7101_hw_reset(काष्ठा bnx2x_phy *phy,
				काष्ठा link_params *params) अणु
	/* Low घातer mode is controlled by GPIO 2 */
	bnx2x_set_gpio(params->bp, MISC_REGISTERS_GPIO_2,
		       MISC_REGISTERS_GPIO_OUTPUT_LOW, params->port);
	/* The PHY reset is controlled by GPIO 1 */
	bnx2x_set_gpio(params->bp, MISC_REGISTERS_GPIO_1,
		       MISC_REGISTERS_GPIO_OUTPUT_LOW, params->port);
पूर्ण

अटल व्योम bnx2x_7101_set_link_led(काष्ठा bnx2x_phy *phy,
				    काष्ठा link_params *params, u8 mode)
अणु
	u16 val = 0;
	काष्ठा bnx2x *bp = params->bp;
	चयन (mode) अणु
	हाल LED_MODE_FRONT_PANEL_OFF:
	हाल LED_MODE_OFF:
		val = 2;
		अवरोध;
	हाल LED_MODE_ON:
		val = 1;
		अवरोध;
	हाल LED_MODE_OPER:
		val = 0;
		अवरोध;
	पूर्ण
	bnx2x_cl45_ग_लिखो(bp, phy,
			 MDIO_PMA_DEVAD,
			 MDIO_PMA_REG_7107_LINK_LED_CNTL,
			 val);
पूर्ण

/******************************************************************/
/*			STATIC PHY DECLARATION			  */
/******************************************************************/

अटल स्थिर काष्ठा bnx2x_phy phy_null = अणु
	.type		= PORT_HW_CFG_XGXS_EXT_PHY_TYPE_NOT_CONN,
	.addr		= 0,
	.def_md_devad	= 0,
	.flags		= FLAGS_INIT_XGXS_FIRST,
	.rx_preemphasis	= अणु0xffff, 0xffff, 0xffff, 0xffffपूर्ण,
	.tx_preemphasis	= अणु0xffff, 0xffff, 0xffff, 0xffffपूर्ण,
	.mdio_ctrl	= 0,
	.supported	= 0,
	.media_type	= ETH_PHY_NOT_PRESENT,
	.ver_addr	= 0,
	.req_flow_ctrl	= 0,
	.req_line_speed	= 0,
	.speed_cap_mask	= 0,
	.req_duplex	= 0,
	.rsrv		= 0,
	.config_init	= शून्य,
	.पढ़ो_status	= शून्य,
	.link_reset	= शून्य,
	.config_loopback = शून्य,
	.क्रमmat_fw_ver	= शून्य,
	.hw_reset	= शून्य,
	.set_link_led	= शून्य,
	.phy_specअगरic_func = शून्य
पूर्ण;

अटल स्थिर काष्ठा bnx2x_phy phy_serdes = अणु
	.type		= PORT_HW_CFG_SERDES_EXT_PHY_TYPE_सूचीECT,
	.addr		= 0xff,
	.def_md_devad	= 0,
	.flags		= 0,
	.rx_preemphasis	= अणु0xffff, 0xffff, 0xffff, 0xffffपूर्ण,
	.tx_preemphasis	= अणु0xffff, 0xffff, 0xffff, 0xffffपूर्ण,
	.mdio_ctrl	= 0,
	.supported	= (SUPPORTED_10baseT_Half |
			   SUPPORTED_10baseT_Full |
			   SUPPORTED_100baseT_Half |
			   SUPPORTED_100baseT_Full |
			   SUPPORTED_1000baseT_Full |
			   SUPPORTED_2500baseX_Full |
			   SUPPORTED_TP |
			   SUPPORTED_Autoneg |
			   SUPPORTED_Pause |
			   SUPPORTED_Asym_Pause),
	.media_type	= ETH_PHY_BASE_T,
	.ver_addr	= 0,
	.req_flow_ctrl	= 0,
	.req_line_speed	= 0,
	.speed_cap_mask	= 0,
	.req_duplex	= 0,
	.rsrv		= 0,
	.config_init	= bnx2x_xgxs_config_init,
	.पढ़ो_status	= bnx2x_link_settings_status,
	.link_reset	= bnx2x_पूर्णांक_link_reset,
	.config_loopback = शून्य,
	.क्रमmat_fw_ver	= शून्य,
	.hw_reset	= शून्य,
	.set_link_led	= शून्य,
	.phy_specअगरic_func = शून्य
पूर्ण;

अटल स्थिर काष्ठा bnx2x_phy phy_xgxs = अणु
	.type		= PORT_HW_CFG_XGXS_EXT_PHY_TYPE_सूचीECT,
	.addr		= 0xff,
	.def_md_devad	= 0,
	.flags		= 0,
	.rx_preemphasis	= अणु0xffff, 0xffff, 0xffff, 0xffffपूर्ण,
	.tx_preemphasis	= अणु0xffff, 0xffff, 0xffff, 0xffffपूर्ण,
	.mdio_ctrl	= 0,
	.supported	= (SUPPORTED_10baseT_Half |
			   SUPPORTED_10baseT_Full |
			   SUPPORTED_100baseT_Half |
			   SUPPORTED_100baseT_Full |
			   SUPPORTED_1000baseT_Full |
			   SUPPORTED_2500baseX_Full |
			   SUPPORTED_10000baseT_Full |
			   SUPPORTED_FIBRE |
			   SUPPORTED_Autoneg |
			   SUPPORTED_Pause |
			   SUPPORTED_Asym_Pause),
	.media_type	= ETH_PHY_CX4,
	.ver_addr	= 0,
	.req_flow_ctrl	= 0,
	.req_line_speed	= 0,
	.speed_cap_mask	= 0,
	.req_duplex	= 0,
	.rsrv		= 0,
	.config_init	= bnx2x_xgxs_config_init,
	.पढ़ो_status	= bnx2x_link_settings_status,
	.link_reset	= bnx2x_पूर्णांक_link_reset,
	.config_loopback = bnx2x_set_xgxs_loopback,
	.क्रमmat_fw_ver	= शून्य,
	.hw_reset	= शून्य,
	.set_link_led	= शून्य,
	.phy_specअगरic_func = bnx2x_xgxs_specअगरic_func
पूर्ण;
अटल स्थिर काष्ठा bnx2x_phy phy_warpcore = अणु
	.type		= PORT_HW_CFG_XGXS_EXT_PHY_TYPE_सूचीECT,
	.addr		= 0xff,
	.def_md_devad	= 0,
	.flags		= FLAGS_TX_ERROR_CHECK,
	.rx_preemphasis	= अणु0xffff, 0xffff, 0xffff, 0xffffपूर्ण,
	.tx_preemphasis	= अणु0xffff, 0xffff, 0xffff, 0xffffपूर्ण,
	.mdio_ctrl	= 0,
	.supported	= (SUPPORTED_10baseT_Half |
			   SUPPORTED_10baseT_Full |
			   SUPPORTED_100baseT_Half |
			   SUPPORTED_100baseT_Full |
			   SUPPORTED_1000baseT_Full |
			   SUPPORTED_1000baseKX_Full |
			   SUPPORTED_10000baseT_Full |
			   SUPPORTED_10000baseKR_Full |
			   SUPPORTED_20000baseKR2_Full |
			   SUPPORTED_20000baseMLD2_Full |
			   SUPPORTED_FIBRE |
			   SUPPORTED_Autoneg |
			   SUPPORTED_Pause |
			   SUPPORTED_Asym_Pause),
	.media_type	= ETH_PHY_UNSPECIFIED,
	.ver_addr	= 0,
	.req_flow_ctrl	= 0,
	.req_line_speed	= 0,
	.speed_cap_mask	= 0,
	/* req_duplex = */0,
	/* rsrv = */0,
	.config_init	= bnx2x_warpcore_config_init,
	.पढ़ो_status	= bnx2x_warpcore_पढ़ो_status,
	.link_reset	= bnx2x_warpcore_link_reset,
	.config_loopback = bnx2x_set_warpcore_loopback,
	.क्रमmat_fw_ver	= शून्य,
	.hw_reset	= bnx2x_warpcore_hw_reset,
	.set_link_led	= शून्य,
	.phy_specअगरic_func = शून्य
पूर्ण;


अटल स्थिर काष्ठा bnx2x_phy phy_7101 = अणु
	.type		= PORT_HW_CFG_XGXS_EXT_PHY_TYPE_SFX7101,
	.addr		= 0xff,
	.def_md_devad	= 0,
	.flags		= FLAGS_FAN_FAILURE_DET_REQ,
	.rx_preemphasis	= अणु0xffff, 0xffff, 0xffff, 0xffffपूर्ण,
	.tx_preemphasis	= अणु0xffff, 0xffff, 0xffff, 0xffffपूर्ण,
	.mdio_ctrl	= 0,
	.supported	= (SUPPORTED_10000baseT_Full |
			   SUPPORTED_TP |
			   SUPPORTED_Autoneg |
			   SUPPORTED_Pause |
			   SUPPORTED_Asym_Pause),
	.media_type	= ETH_PHY_BASE_T,
	.ver_addr	= 0,
	.req_flow_ctrl	= 0,
	.req_line_speed	= 0,
	.speed_cap_mask	= 0,
	.req_duplex	= 0,
	.rsrv		= 0,
	.config_init	= bnx2x_7101_config_init,
	.पढ़ो_status	= bnx2x_7101_पढ़ो_status,
	.link_reset	= bnx2x_common_ext_link_reset,
	.config_loopback = bnx2x_7101_config_loopback,
	.क्रमmat_fw_ver	= bnx2x_7101_क्रमmat_ver,
	.hw_reset	= bnx2x_7101_hw_reset,
	.set_link_led	= bnx2x_7101_set_link_led,
	.phy_specअगरic_func = शून्य
पूर्ण;
अटल स्थिर काष्ठा bnx2x_phy phy_8073 = अणु
	.type		= PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8073,
	.addr		= 0xff,
	.def_md_devad	= 0,
	.flags		= 0,
	.rx_preemphasis	= अणु0xffff, 0xffff, 0xffff, 0xffffपूर्ण,
	.tx_preemphasis	= अणु0xffff, 0xffff, 0xffff, 0xffffपूर्ण,
	.mdio_ctrl	= 0,
	.supported	= (SUPPORTED_10000baseT_Full |
			   SUPPORTED_2500baseX_Full |
			   SUPPORTED_1000baseT_Full |
			   SUPPORTED_FIBRE |
			   SUPPORTED_Autoneg |
			   SUPPORTED_Pause |
			   SUPPORTED_Asym_Pause),
	.media_type	= ETH_PHY_KR,
	.ver_addr	= 0,
	.req_flow_ctrl	= 0,
	.req_line_speed	= 0,
	.speed_cap_mask	= 0,
	.req_duplex	= 0,
	.rsrv		= 0,
	.config_init	= bnx2x_8073_config_init,
	.पढ़ो_status	= bnx2x_8073_पढ़ो_status,
	.link_reset	= bnx2x_8073_link_reset,
	.config_loopback = शून्य,
	.क्रमmat_fw_ver	= bnx2x_क्रमmat_ver,
	.hw_reset	= शून्य,
	.set_link_led	= शून्य,
	.phy_specअगरic_func = bnx2x_8073_specअगरic_func
पूर्ण;
अटल स्थिर काष्ठा bnx2x_phy phy_8705 = अणु
	.type		= PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8705,
	.addr		= 0xff,
	.def_md_devad	= 0,
	.flags		= FLAGS_INIT_XGXS_FIRST,
	.rx_preemphasis	= अणु0xffff, 0xffff, 0xffff, 0xffffपूर्ण,
	.tx_preemphasis	= अणु0xffff, 0xffff, 0xffff, 0xffffपूर्ण,
	.mdio_ctrl	= 0,
	.supported	= (SUPPORTED_10000baseT_Full |
			   SUPPORTED_FIBRE |
			   SUPPORTED_Pause |
			   SUPPORTED_Asym_Pause),
	.media_type	= ETH_PHY_XFP_FIBER,
	.ver_addr	= 0,
	.req_flow_ctrl	= 0,
	.req_line_speed	= 0,
	.speed_cap_mask	= 0,
	.req_duplex	= 0,
	.rsrv		= 0,
	.config_init	= bnx2x_8705_config_init,
	.पढ़ो_status	= bnx2x_8705_पढ़ो_status,
	.link_reset	= bnx2x_common_ext_link_reset,
	.config_loopback = शून्य,
	.क्रमmat_fw_ver	= bnx2x_null_क्रमmat_ver,
	.hw_reset	= शून्य,
	.set_link_led	= शून्य,
	.phy_specअगरic_func = शून्य
पूर्ण;
अटल स्थिर काष्ठा bnx2x_phy phy_8706 = अणु
	.type		= PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8706,
	.addr		= 0xff,
	.def_md_devad	= 0,
	.flags		= FLAGS_INIT_XGXS_FIRST,
	.rx_preemphasis	= अणु0xffff, 0xffff, 0xffff, 0xffffपूर्ण,
	.tx_preemphasis	= अणु0xffff, 0xffff, 0xffff, 0xffffपूर्ण,
	.mdio_ctrl	= 0,
	.supported	= (SUPPORTED_10000baseT_Full |
			   SUPPORTED_1000baseT_Full |
			   SUPPORTED_FIBRE |
			   SUPPORTED_Pause |
			   SUPPORTED_Asym_Pause),
	.media_type	= ETH_PHY_SFPP_10G_FIBER,
	.ver_addr	= 0,
	.req_flow_ctrl	= 0,
	.req_line_speed	= 0,
	.speed_cap_mask	= 0,
	.req_duplex	= 0,
	.rsrv		= 0,
	.config_init	= bnx2x_8706_config_init,
	.पढ़ो_status	= bnx2x_8706_पढ़ो_status,
	.link_reset	= bnx2x_common_ext_link_reset,
	.config_loopback = शून्य,
	.क्रमmat_fw_ver	= bnx2x_क्रमmat_ver,
	.hw_reset	= शून्य,
	.set_link_led	= शून्य,
	.phy_specअगरic_func = शून्य
पूर्ण;

अटल स्थिर काष्ठा bnx2x_phy phy_8726 = अणु
	.type		= PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8726,
	.addr		= 0xff,
	.def_md_devad	= 0,
	.flags		= (FLAGS_INIT_XGXS_FIRST |
			   FLAGS_TX_ERROR_CHECK),
	.rx_preemphasis	= अणु0xffff, 0xffff, 0xffff, 0xffffपूर्ण,
	.tx_preemphasis	= अणु0xffff, 0xffff, 0xffff, 0xffffपूर्ण,
	.mdio_ctrl	= 0,
	.supported	= (SUPPORTED_10000baseT_Full |
			   SUPPORTED_1000baseT_Full |
			   SUPPORTED_Autoneg |
			   SUPPORTED_FIBRE |
			   SUPPORTED_Pause |
			   SUPPORTED_Asym_Pause),
	.media_type	= ETH_PHY_NOT_PRESENT,
	.ver_addr	= 0,
	.req_flow_ctrl	= 0,
	.req_line_speed	= 0,
	.speed_cap_mask	= 0,
	.req_duplex	= 0,
	.rsrv		= 0,
	.config_init	= bnx2x_8726_config_init,
	.पढ़ो_status	= bnx2x_8726_पढ़ो_status,
	.link_reset	= bnx2x_8726_link_reset,
	.config_loopback = bnx2x_8726_config_loopback,
	.क्रमmat_fw_ver	= bnx2x_क्रमmat_ver,
	.hw_reset	= शून्य,
	.set_link_led	= शून्य,
	.phy_specअगरic_func = शून्य
पूर्ण;

अटल स्थिर काष्ठा bnx2x_phy phy_8727 = अणु
	.type		= PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8727,
	.addr		= 0xff,
	.def_md_devad	= 0,
	.flags		= (FLAGS_FAN_FAILURE_DET_REQ |
			   FLAGS_TX_ERROR_CHECK),
	.rx_preemphasis	= अणु0xffff, 0xffff, 0xffff, 0xffffपूर्ण,
	.tx_preemphasis	= अणु0xffff, 0xffff, 0xffff, 0xffffपूर्ण,
	.mdio_ctrl	= 0,
	.supported	= (SUPPORTED_10000baseT_Full |
			   SUPPORTED_1000baseT_Full |
			   SUPPORTED_FIBRE |
			   SUPPORTED_Pause |
			   SUPPORTED_Asym_Pause),
	.media_type	= ETH_PHY_NOT_PRESENT,
	.ver_addr	= 0,
	.req_flow_ctrl	= 0,
	.req_line_speed	= 0,
	.speed_cap_mask	= 0,
	.req_duplex	= 0,
	.rsrv		= 0,
	.config_init	= bnx2x_8727_config_init,
	.पढ़ो_status	= bnx2x_8727_पढ़ो_status,
	.link_reset	= bnx2x_8727_link_reset,
	.config_loopback = शून्य,
	.क्रमmat_fw_ver	= bnx2x_क्रमmat_ver,
	.hw_reset	= bnx2x_8727_hw_reset,
	.set_link_led	= bnx2x_8727_set_link_led,
	.phy_specअगरic_func = bnx2x_8727_specअगरic_func
पूर्ण;
अटल स्थिर काष्ठा bnx2x_phy phy_8481 = अणु
	.type		= PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8481,
	.addr		= 0xff,
	.def_md_devad	= 0,
	.flags		= FLAGS_FAN_FAILURE_DET_REQ |
			  FLAGS_REARM_LATCH_SIGNAL,
	.rx_preemphasis	= अणु0xffff, 0xffff, 0xffff, 0xffffपूर्ण,
	.tx_preemphasis	= अणु0xffff, 0xffff, 0xffff, 0xffffपूर्ण,
	.mdio_ctrl	= 0,
	.supported	= (SUPPORTED_10baseT_Half |
			   SUPPORTED_10baseT_Full |
			   SUPPORTED_100baseT_Half |
			   SUPPORTED_100baseT_Full |
			   SUPPORTED_1000baseT_Full |
			   SUPPORTED_10000baseT_Full |
			   SUPPORTED_TP |
			   SUPPORTED_Autoneg |
			   SUPPORTED_Pause |
			   SUPPORTED_Asym_Pause),
	.media_type	= ETH_PHY_BASE_T,
	.ver_addr	= 0,
	.req_flow_ctrl	= 0,
	.req_line_speed	= 0,
	.speed_cap_mask	= 0,
	.req_duplex	= 0,
	.rsrv		= 0,
	.config_init	= bnx2x_8481_config_init,
	.पढ़ो_status	= bnx2x_848xx_पढ़ो_status,
	.link_reset	= bnx2x_8481_link_reset,
	.config_loopback = शून्य,
	.क्रमmat_fw_ver	= bnx2x_848xx_क्रमmat_ver,
	.hw_reset	= bnx2x_8481_hw_reset,
	.set_link_led	= bnx2x_848xx_set_link_led,
	.phy_specअगरic_func = शून्य
पूर्ण;

अटल स्थिर काष्ठा bnx2x_phy phy_84823 = अणु
	.type		= PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84823,
	.addr		= 0xff,
	.def_md_devad	= 0,
	.flags		= (FLAGS_FAN_FAILURE_DET_REQ |
			   FLAGS_REARM_LATCH_SIGNAL |
			   FLAGS_TX_ERROR_CHECK),
	.rx_preemphasis	= अणु0xffff, 0xffff, 0xffff, 0xffffपूर्ण,
	.tx_preemphasis	= अणु0xffff, 0xffff, 0xffff, 0xffffपूर्ण,
	.mdio_ctrl	= 0,
	.supported	= (SUPPORTED_10baseT_Half |
			   SUPPORTED_10baseT_Full |
			   SUPPORTED_100baseT_Half |
			   SUPPORTED_100baseT_Full |
			   SUPPORTED_1000baseT_Full |
			   SUPPORTED_10000baseT_Full |
			   SUPPORTED_TP |
			   SUPPORTED_Autoneg |
			   SUPPORTED_Pause |
			   SUPPORTED_Asym_Pause),
	.media_type	= ETH_PHY_BASE_T,
	.ver_addr	= 0,
	.req_flow_ctrl	= 0,
	.req_line_speed	= 0,
	.speed_cap_mask	= 0,
	.req_duplex	= 0,
	.rsrv		= 0,
	.config_init	= bnx2x_848x3_config_init,
	.पढ़ो_status	= bnx2x_848xx_पढ़ो_status,
	.link_reset	= bnx2x_848x3_link_reset,
	.config_loopback = शून्य,
	.क्रमmat_fw_ver	= bnx2x_848xx_क्रमmat_ver,
	.hw_reset	= शून्य,
	.set_link_led	= bnx2x_848xx_set_link_led,
	.phy_specअगरic_func = bnx2x_848xx_specअगरic_func
पूर्ण;

अटल स्थिर काष्ठा bnx2x_phy phy_84833 = अणु
	.type		= PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84833,
	.addr		= 0xff,
	.def_md_devad	= 0,
	.flags		= (FLAGS_FAN_FAILURE_DET_REQ |
			   FLAGS_REARM_LATCH_SIGNAL |
			   FLAGS_TX_ERROR_CHECK),
	.rx_preemphasis	= अणु0xffff, 0xffff, 0xffff, 0xffffपूर्ण,
	.tx_preemphasis	= अणु0xffff, 0xffff, 0xffff, 0xffffपूर्ण,
	.mdio_ctrl	= 0,
	.supported	= (SUPPORTED_100baseT_Half |
			   SUPPORTED_100baseT_Full |
			   SUPPORTED_1000baseT_Full |
			   SUPPORTED_10000baseT_Full |
			   SUPPORTED_TP |
			   SUPPORTED_Autoneg |
			   SUPPORTED_Pause |
			   SUPPORTED_Asym_Pause),
	.media_type	= ETH_PHY_BASE_T,
	.ver_addr	= 0,
	.req_flow_ctrl	= 0,
	.req_line_speed	= 0,
	.speed_cap_mask	= 0,
	.req_duplex	= 0,
	.rsrv		= 0,
	.config_init	= bnx2x_848x3_config_init,
	.पढ़ो_status	= bnx2x_848xx_पढ़ो_status,
	.link_reset	= bnx2x_848x3_link_reset,
	.config_loopback = शून्य,
	.क्रमmat_fw_ver	= bnx2x_848xx_क्रमmat_ver,
	.hw_reset	= bnx2x_84833_hw_reset_phy,
	.set_link_led	= bnx2x_848xx_set_link_led,
	.phy_specअगरic_func = bnx2x_848xx_specअगरic_func
पूर्ण;

अटल स्थिर काष्ठा bnx2x_phy phy_84834 = अणु
	.type		= PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84834,
	.addr		= 0xff,
	.def_md_devad	= 0,
	.flags		= FLAGS_FAN_FAILURE_DET_REQ |
			    FLAGS_REARM_LATCH_SIGNAL,
	.rx_preemphasis	= अणु0xffff, 0xffff, 0xffff, 0xffffपूर्ण,
	.tx_preemphasis	= अणु0xffff, 0xffff, 0xffff, 0xffffपूर्ण,
	.mdio_ctrl	= 0,
	.supported	= (SUPPORTED_100baseT_Half |
			   SUPPORTED_100baseT_Full |
			   SUPPORTED_1000baseT_Full |
			   SUPPORTED_10000baseT_Full |
			   SUPPORTED_TP |
			   SUPPORTED_Autoneg |
			   SUPPORTED_Pause |
			   SUPPORTED_Asym_Pause),
	.media_type	= ETH_PHY_BASE_T,
	.ver_addr	= 0,
	.req_flow_ctrl	= 0,
	.req_line_speed	= 0,
	.speed_cap_mask	= 0,
	.req_duplex	= 0,
	.rsrv		= 0,
	.config_init	= bnx2x_848x3_config_init,
	.पढ़ो_status	= bnx2x_848xx_पढ़ो_status,
	.link_reset	= bnx2x_848x3_link_reset,
	.config_loopback = शून्य,
	.क्रमmat_fw_ver	= bnx2x_848xx_क्रमmat_ver,
	.hw_reset	= bnx2x_84833_hw_reset_phy,
	.set_link_led	= bnx2x_848xx_set_link_led,
	.phy_specअगरic_func = bnx2x_848xx_specअगरic_func
पूर्ण;

अटल स्थिर काष्ठा bnx2x_phy phy_84858 = अणु
	.type		= PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84858,
	.addr		= 0xff,
	.def_md_devad	= 0,
	.flags		= FLAGS_FAN_FAILURE_DET_REQ |
			    FLAGS_REARM_LATCH_SIGNAL,
	.rx_preemphasis	= अणु0xffff, 0xffff, 0xffff, 0xffffपूर्ण,
	.tx_preemphasis	= अणु0xffff, 0xffff, 0xffff, 0xffffपूर्ण,
	.mdio_ctrl	= 0,
	.supported	= (SUPPORTED_100baseT_Half |
			   SUPPORTED_100baseT_Full |
			   SUPPORTED_1000baseT_Full |
			   SUPPORTED_10000baseT_Full |
			   SUPPORTED_TP |
			   SUPPORTED_Autoneg |
			   SUPPORTED_Pause |
			   SUPPORTED_Asym_Pause),
	.media_type	= ETH_PHY_BASE_T,
	.ver_addr	= 0,
	.req_flow_ctrl	= 0,
	.req_line_speed	= 0,
	.speed_cap_mask	= 0,
	.req_duplex	= 0,
	.rsrv		= 0,
	.config_init	= bnx2x_848x3_config_init,
	.पढ़ो_status	= bnx2x_848xx_पढ़ो_status,
	.link_reset	= bnx2x_848x3_link_reset,
	.config_loopback = शून्य,
	.क्रमmat_fw_ver	= bnx2x_8485x_क्रमmat_ver,
	.hw_reset	= bnx2x_84833_hw_reset_phy,
	.set_link_led	= bnx2x_848xx_set_link_led,
	.phy_specअगरic_func = bnx2x_848xx_specअगरic_func
पूर्ण;

अटल स्थिर काष्ठा bnx2x_phy phy_54618se = अणु
	.type		= PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM54618SE,
	.addr		= 0xff,
	.def_md_devad	= 0,
	.flags		= FLAGS_INIT_XGXS_FIRST,
	.rx_preemphasis	= अणु0xffff, 0xffff, 0xffff, 0xffffपूर्ण,
	.tx_preemphasis	= अणु0xffff, 0xffff, 0xffff, 0xffffपूर्ण,
	.mdio_ctrl	= 0,
	.supported	= (SUPPORTED_10baseT_Half |
			   SUPPORTED_10baseT_Full |
			   SUPPORTED_100baseT_Half |
			   SUPPORTED_100baseT_Full |
			   SUPPORTED_1000baseT_Full |
			   SUPPORTED_TP |
			   SUPPORTED_Autoneg |
			   SUPPORTED_Pause |
			   SUPPORTED_Asym_Pause),
	.media_type	= ETH_PHY_BASE_T,
	.ver_addr	= 0,
	.req_flow_ctrl	= 0,
	.req_line_speed	= 0,
	.speed_cap_mask	= 0,
	/* req_duplex = */0,
	/* rsrv = */0,
	.config_init	= bnx2x_54618se_config_init,
	.पढ़ो_status	= bnx2x_54618se_पढ़ो_status,
	.link_reset	= bnx2x_54618se_link_reset,
	.config_loopback = bnx2x_54618se_config_loopback,
	.क्रमmat_fw_ver	= शून्य,
	.hw_reset	= शून्य,
	.set_link_led	= bnx2x_5461x_set_link_led,
	.phy_specअगरic_func = bnx2x_54618se_specअगरic_func
पूर्ण;
/*****************************************************************/
/*                                                               */
/* Populate the phy according. Main function: bnx2x_populate_phy   */
/*                                                               */
/*****************************************************************/

अटल व्योम bnx2x_populate_preemphasis(काष्ठा bnx2x *bp, u32 shmem_base,
				     काष्ठा bnx2x_phy *phy, u8 port,
				     u8 phy_index)
अणु
	/* Get the 4 lanes xgxs config rx and tx */
	u32 rx = 0, tx = 0, i;
	क्रम (i = 0; i < 2; i++) अणु
		/* INT_PHY and EXT_PHY1 share the same value location in
		 * the shmem. When num_phys is greater than 1, than this value
		 * applies only to EXT_PHY1
		 */
		अगर (phy_index == INT_PHY || phy_index == EXT_PHY1) अणु
			rx = REG_RD(bp, shmem_base +
				    दुरत्व(काष्ठा shmem_region,
			  dev_info.port_hw_config[port].xgxs_config_rx[i<<1]));

			tx = REG_RD(bp, shmem_base +
				    दुरत्व(काष्ठा shmem_region,
			  dev_info.port_hw_config[port].xgxs_config_tx[i<<1]));
		पूर्ण अन्यथा अणु
			rx = REG_RD(bp, shmem_base +
				    दुरत्व(काष्ठा shmem_region,
			 dev_info.port_hw_config[port].xgxs_config2_rx[i<<1]));

			tx = REG_RD(bp, shmem_base +
				    दुरत्व(काष्ठा shmem_region,
			 dev_info.port_hw_config[port].xgxs_config2_rx[i<<1]));
		पूर्ण

		phy->rx_preemphasis[i << 1] = ((rx>>16) & 0xffff);
		phy->rx_preemphasis[(i << 1) + 1] = (rx & 0xffff);

		phy->tx_preemphasis[i << 1] = ((tx>>16) & 0xffff);
		phy->tx_preemphasis[(i << 1) + 1] = (tx & 0xffff);
	पूर्ण
पूर्ण

अटल u32 bnx2x_get_ext_phy_config(काष्ठा bnx2x *bp, u32 shmem_base,
				    u8 phy_index, u8 port)
अणु
	u32 ext_phy_config = 0;
	चयन (phy_index) अणु
	हाल EXT_PHY1:
		ext_phy_config = REG_RD(bp, shmem_base +
					      दुरत्व(काष्ठा shmem_region,
			dev_info.port_hw_config[port].बाह्यal_phy_config));
		अवरोध;
	हाल EXT_PHY2:
		ext_phy_config = REG_RD(bp, shmem_base +
					      दुरत्व(काष्ठा shmem_region,
			dev_info.port_hw_config[port].बाह्यal_phy_config2));
		अवरोध;
	शेष:
		DP(NETIF_MSG_LINK, "Invalid phy_index %d\n", phy_index);
		वापस -EINVAL;
	पूर्ण

	वापस ext_phy_config;
पूर्ण
अटल पूर्णांक bnx2x_populate_पूर्णांक_phy(काष्ठा bnx2x *bp, u32 shmem_base, u8 port,
				  काष्ठा bnx2x_phy *phy)
अणु
	u32 phy_addr;
	u32 chip_id;
	u32 चयन_cfg = (REG_RD(bp, shmem_base +
				       दुरत्व(काष्ठा shmem_region,
			dev_info.port_feature_config[port].link_config)) &
			  PORT_FEATURE_CONNECTED_SWITCH_MASK);
	chip_id = (REG_RD(bp, MISC_REG_CHIP_NUM) << 16) |
		((REG_RD(bp, MISC_REG_CHIP_REV) & 0xf) << 12);

	DP(NETIF_MSG_LINK, ":chip_id = 0x%x\n", chip_id);
	अगर (USES_WARPCORE(bp)) अणु
		u32 serdes_net_अगर;
		phy_addr = REG_RD(bp,
				  MISC_REG_WC0_CTRL_PHY_ADDR);
		*phy = phy_warpcore;
		अगर (REG_RD(bp, MISC_REG_PORT4MODE_EN_OVWR) == 0x3)
			phy->flags |= FLAGS_4_PORT_MODE;
		अन्यथा
			phy->flags &= ~FLAGS_4_PORT_MODE;
			/* Check Dual mode */
		serdes_net_अगर = (REG_RD(bp, shmem_base +
					दुरत्व(काष्ठा shmem_region, dev_info.
					port_hw_config[port].शेष_cfg)) &
				 PORT_HW_CFG_NET_SERDES_IF_MASK);
		/* Set the appropriate supported and flags indications per
		 * पूर्णांकerface type of the chip
		 */
		चयन (serdes_net_अगर) अणु
		हाल PORT_HW_CFG_NET_SERDES_IF_SGMII:
			phy->supported &= (SUPPORTED_10baseT_Half |
					   SUPPORTED_10baseT_Full |
					   SUPPORTED_100baseT_Half |
					   SUPPORTED_100baseT_Full |
					   SUPPORTED_1000baseT_Full |
					   SUPPORTED_FIBRE |
					   SUPPORTED_Autoneg |
					   SUPPORTED_Pause |
					   SUPPORTED_Asym_Pause);
			phy->media_type = ETH_PHY_BASE_T;
			अवरोध;
		हाल PORT_HW_CFG_NET_SERDES_IF_XFI:
			phy->supported &= (SUPPORTED_1000baseT_Full |
					   SUPPORTED_10000baseT_Full |
					   SUPPORTED_FIBRE |
					   SUPPORTED_Pause |
					   SUPPORTED_Asym_Pause);
			phy->media_type = ETH_PHY_XFP_FIBER;
			अवरोध;
		हाल PORT_HW_CFG_NET_SERDES_IF_SFI:
			phy->supported &= (SUPPORTED_1000baseT_Full |
					   SUPPORTED_10000baseT_Full |
					   SUPPORTED_FIBRE |
					   SUPPORTED_Pause |
					   SUPPORTED_Asym_Pause);
			phy->media_type = ETH_PHY_SFPP_10G_FIBER;
			अवरोध;
		हाल PORT_HW_CFG_NET_SERDES_IF_KR:
			phy->media_type = ETH_PHY_KR;
			phy->supported &= (SUPPORTED_1000baseKX_Full |
					   SUPPORTED_10000baseKR_Full |
					   SUPPORTED_FIBRE |
					   SUPPORTED_Autoneg |
					   SUPPORTED_Pause |
					   SUPPORTED_Asym_Pause);
			अवरोध;
		हाल PORT_HW_CFG_NET_SERDES_IF_DXGXS:
			phy->media_type = ETH_PHY_KR;
			phy->flags |= FLAGS_WC_DUAL_MODE;
			phy->supported &= (SUPPORTED_20000baseMLD2_Full |
					   SUPPORTED_FIBRE |
					   SUPPORTED_Pause |
					   SUPPORTED_Asym_Pause);
			अवरोध;
		हाल PORT_HW_CFG_NET_SERDES_IF_KR2:
			phy->media_type = ETH_PHY_KR;
			phy->flags |= FLAGS_WC_DUAL_MODE;
			phy->supported &= (SUPPORTED_20000baseKR2_Full |
					   SUPPORTED_10000baseKR_Full |
					   SUPPORTED_1000baseKX_Full |
					   SUPPORTED_Autoneg |
					   SUPPORTED_FIBRE |
					   SUPPORTED_Pause |
					   SUPPORTED_Asym_Pause);
			phy->flags &= ~FLAGS_TX_ERROR_CHECK;
			अवरोध;
		शेष:
			DP(NETIF_MSG_LINK, "Unknown WC interface type 0x%x\n",
				       serdes_net_अगर);
			अवरोध;
		पूर्ण

		/* Enable MDC/MDIO work-around क्रम E3 A0 since मुक्त running MDC
		 * was not set as expected. For B0, ECO will be enabled so there
		 * won't be an issue there
		 */
		अगर (CHIP_REV(bp) == CHIP_REV_Ax)
			phy->flags |= FLAGS_MDC_MDIO_WA;
		अन्यथा
			phy->flags |= FLAGS_MDC_MDIO_WA_B0;
	पूर्ण अन्यथा अणु
		चयन (चयन_cfg) अणु
		हाल SWITCH_CFG_1G:
			phy_addr = REG_RD(bp,
					  NIG_REG_SERDES0_CTRL_PHY_ADDR +
					  port * 0x10);
			*phy = phy_serdes;
			अवरोध;
		हाल SWITCH_CFG_10G:
			phy_addr = REG_RD(bp,
					  NIG_REG_XGXS0_CTRL_PHY_ADDR +
					  port * 0x18);
			*phy = phy_xgxs;
			अवरोध;
		शेष:
			DP(NETIF_MSG_LINK, "Invalid switch_cfg\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	phy->addr = (u8)phy_addr;
	phy->mdio_ctrl = bnx2x_get_emac_base(bp,
					    SHARED_HW_CFG_MDC_MDIO_ACCESS1_BOTH,
					    port);
	अगर (CHIP_IS_E2(bp))
		phy->def_md_devad = E2_DEFAULT_PHY_DEV_ADDR;
	अन्यथा
		phy->def_md_devad = DEFAULT_PHY_DEV_ADDR;

	DP(NETIF_MSG_LINK, "Internal phy port=%d, addr=0x%x, mdio_ctl=0x%x\n",
		   port, phy->addr, phy->mdio_ctrl);

	bnx2x_populate_preemphasis(bp, shmem_base, phy, port, INT_PHY);
	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_populate_ext_phy(काष्ठा bnx2x *bp,
				  u8 phy_index,
				  u32 shmem_base,
				  u32 shmem2_base,
				  u8 port,
				  काष्ठा bnx2x_phy *phy)
अणु
	u32 ext_phy_config, phy_type, config2;
	u32 mdc_mdio_access = SHARED_HW_CFG_MDC_MDIO_ACCESS1_BOTH;
	ext_phy_config = bnx2x_get_ext_phy_config(bp, shmem_base,
						  phy_index, port);
	phy_type = XGXS_EXT_PHY_TYPE(ext_phy_config);
	/* Select the phy type */
	चयन (phy_type) अणु
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8073:
		mdc_mdio_access = SHARED_HW_CFG_MDC_MDIO_ACCESS1_SWAPPED;
		*phy = phy_8073;
		अवरोध;
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8705:
		*phy = phy_8705;
		अवरोध;
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8706:
		*phy = phy_8706;
		अवरोध;
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8726:
		mdc_mdio_access = SHARED_HW_CFG_MDC_MDIO_ACCESS1_EMAC1;
		*phy = phy_8726;
		अवरोध;
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8727_NOC:
		/* BCM8727_NOC => BCM8727 no over current */
		mdc_mdio_access = SHARED_HW_CFG_MDC_MDIO_ACCESS1_EMAC1;
		*phy = phy_8727;
		phy->flags |= FLAGS_NOC;
		अवरोध;
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8722:
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8727:
		mdc_mdio_access = SHARED_HW_CFG_MDC_MDIO_ACCESS1_EMAC1;
		*phy = phy_8727;
		अवरोध;
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8481:
		*phy = phy_8481;
		अवरोध;
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84823:
		*phy = phy_84823;
		अवरोध;
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84833:
		*phy = phy_84833;
		अवरोध;
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84834:
		*phy = phy_84834;
		अवरोध;
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84858:
		*phy = phy_84858;
		अवरोध;
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM54616:
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM54618SE:
		*phy = phy_54618se;
		अगर (phy_type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM54618SE)
			phy->flags |= FLAGS_EEE;
		अवरोध;
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_SFX7101:
		*phy = phy_7101;
		अवरोध;
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_FAILURE:
		*phy = phy_null;
		वापस -EINVAL;
	शेष:
		*phy = phy_null;
		/* In हाल बाह्यal PHY wasn't found */
		अगर ((phy_type != PORT_HW_CFG_XGXS_EXT_PHY_TYPE_सूचीECT) &&
		    (phy_type != PORT_HW_CFG_XGXS_EXT_PHY_TYPE_NOT_CONN))
			वापस -EINVAL;
		वापस 0;
	पूर्ण

	phy->addr = XGXS_EXT_PHY_ADDR(ext_phy_config);
	bnx2x_populate_preemphasis(bp, shmem_base, phy, port, phy_index);

	/* The shmem address of the phy version is located on dअगरferent
	 * काष्ठाures. In हाल this काष्ठाure is too old, करो not set
	 * the address
	 */
	config2 = REG_RD(bp, shmem_base + दुरत्व(काष्ठा shmem_region,
					dev_info.shared_hw_config.config2));
	अगर (phy_index == EXT_PHY1) अणु
		phy->ver_addr = shmem_base + दुरत्व(काष्ठा shmem_region,
				port_mb[port].ext_phy_fw_version);

		/* Check specअगरic mdc mdio settings */
		अगर (config2 & SHARED_HW_CFG_MDC_MDIO_ACCESS1_MASK)
			mdc_mdio_access = config2 &
			SHARED_HW_CFG_MDC_MDIO_ACCESS1_MASK;
	पूर्ण अन्यथा अणु
		u32 size = REG_RD(bp, shmem2_base);

		अगर (size >
		    दुरत्व(काष्ठा shmem2_region, ext_phy_fw_version2)) अणु
			phy->ver_addr = shmem2_base +
			    दुरत्व(काष्ठा shmem2_region,
				     ext_phy_fw_version2[port]);
		पूर्ण
		/* Check specअगरic mdc mdio settings */
		अगर (config2 & SHARED_HW_CFG_MDC_MDIO_ACCESS2_MASK)
			mdc_mdio_access = (config2 &
			SHARED_HW_CFG_MDC_MDIO_ACCESS2_MASK) >>
			(SHARED_HW_CFG_MDC_MDIO_ACCESS2_SHIFT -
			 SHARED_HW_CFG_MDC_MDIO_ACCESS1_SHIFT);
	पूर्ण
	phy->mdio_ctrl = bnx2x_get_emac_base(bp, mdc_mdio_access, port);

	अगर (bnx2x_is_8483x_8485x(phy) && (phy->ver_addr)) अणु
		/* Remove 100Mb link supported क्रम BCM84833/4 when phy fw
		 * version lower than or equal to 1.39
		 */
		u32 raw_ver = REG_RD(bp, phy->ver_addr);
		अगर (((raw_ver & 0x7F) <= 39) &&
		    (((raw_ver & 0xF80) >> 7) <= 1))
			phy->supported &= ~(SUPPORTED_100baseT_Half |
					    SUPPORTED_100baseT_Full);
	पूर्ण

	DP(NETIF_MSG_LINK, "phy_type 0x%x port %d found in index %d\n",
		   phy_type, port, phy_index);
	DP(NETIF_MSG_LINK, "             addr=0x%x, mdio_ctl=0x%x\n",
		   phy->addr, phy->mdio_ctrl);
	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_populate_phy(काष्ठा bnx2x *bp, u8 phy_index, u32 shmem_base,
			      u32 shmem2_base, u8 port, काष्ठा bnx2x_phy *phy)
अणु
	phy->type = PORT_HW_CFG_XGXS_EXT_PHY_TYPE_NOT_CONN;
	अगर (phy_index == INT_PHY)
		वापस bnx2x_populate_पूर्णांक_phy(bp, shmem_base, port, phy);

	वापस bnx2x_populate_ext_phy(bp, phy_index, shmem_base, shmem2_base,
					port, phy);
पूर्ण

अटल व्योम bnx2x_phy_def_cfg(काष्ठा link_params *params,
			      काष्ठा bnx2x_phy *phy,
			      u8 phy_index)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u32 link_config;
	/* Populate the शेष phy configuration क्रम MF mode */
	अगर (phy_index == EXT_PHY2) अणु
		link_config = REG_RD(bp, params->shmem_base +
				     दुरत्व(काष्ठा shmem_region, dev_info.
			port_feature_config[params->port].link_config2));
		phy->speed_cap_mask = REG_RD(bp, params->shmem_base +
					     दुरत्व(काष्ठा shmem_region,
						      dev_info.
			port_hw_config[params->port].speed_capability_mask2));
	पूर्ण अन्यथा अणु
		link_config = REG_RD(bp, params->shmem_base +
				     दुरत्व(काष्ठा shmem_region, dev_info.
				port_feature_config[params->port].link_config));
		phy->speed_cap_mask = REG_RD(bp, params->shmem_base +
					     दुरत्व(काष्ठा shmem_region,
						      dev_info.
			port_hw_config[params->port].speed_capability_mask));
	पूर्ण
	DP(NETIF_MSG_LINK,
	   "Default config phy idx %x cfg 0x%x speed_cap_mask 0x%x\n",
	   phy_index, link_config, phy->speed_cap_mask);

	phy->req_duplex = DUPLEX_FULL;
	चयन (link_config  & PORT_FEATURE_LINK_SPEED_MASK) अणु
	हाल PORT_FEATURE_LINK_SPEED_10M_HALF:
		phy->req_duplex = DUPLEX_HALF;
		fallthrough;
	हाल PORT_FEATURE_LINK_SPEED_10M_FULL:
		phy->req_line_speed = SPEED_10;
		अवरोध;
	हाल PORT_FEATURE_LINK_SPEED_100M_HALF:
		phy->req_duplex = DUPLEX_HALF;
		fallthrough;
	हाल PORT_FEATURE_LINK_SPEED_100M_FULL:
		phy->req_line_speed = SPEED_100;
		अवरोध;
	हाल PORT_FEATURE_LINK_SPEED_1G:
		phy->req_line_speed = SPEED_1000;
		अवरोध;
	हाल PORT_FEATURE_LINK_SPEED_2_5G:
		phy->req_line_speed = SPEED_2500;
		अवरोध;
	हाल PORT_FEATURE_LINK_SPEED_10G_CX4:
		phy->req_line_speed = SPEED_10000;
		अवरोध;
	शेष:
		phy->req_line_speed = SPEED_AUTO_NEG;
		अवरोध;
	पूर्ण

	चयन (link_config  & PORT_FEATURE_FLOW_CONTROL_MASK) अणु
	हाल PORT_FEATURE_FLOW_CONTROL_AUTO:
		phy->req_flow_ctrl = BNX2X_FLOW_CTRL_AUTO;
		अवरोध;
	हाल PORT_FEATURE_FLOW_CONTROL_TX:
		phy->req_flow_ctrl = BNX2X_FLOW_CTRL_TX;
		अवरोध;
	हाल PORT_FEATURE_FLOW_CONTROL_RX:
		phy->req_flow_ctrl = BNX2X_FLOW_CTRL_RX;
		अवरोध;
	हाल PORT_FEATURE_FLOW_CONTROL_BOTH:
		phy->req_flow_ctrl = BNX2X_FLOW_CTRL_BOTH;
		अवरोध;
	शेष:
		phy->req_flow_ctrl = BNX2X_FLOW_CTRL_NONE;
		अवरोध;
	पूर्ण
पूर्ण

u32 bnx2x_phy_selection(काष्ठा link_params *params)
अणु
	u32 phy_config_swapped, prio_cfg;
	u32 वापस_cfg = PORT_HW_CFG_PHY_SELECTION_HARDWARE_DEFAULT;

	phy_config_swapped = params->multi_phy_config &
		PORT_HW_CFG_PHY_SWAPPED_ENABLED;

	prio_cfg = params->multi_phy_config &
			PORT_HW_CFG_PHY_SELECTION_MASK;

	अगर (phy_config_swapped) अणु
		चयन (prio_cfg) अणु
		हाल PORT_HW_CFG_PHY_SELECTION_FIRST_PHY_PRIORITY:
		     वापस_cfg = PORT_HW_CFG_PHY_SELECTION_SECOND_PHY_PRIORITY;
		     अवरोध;
		हाल PORT_HW_CFG_PHY_SELECTION_SECOND_PHY_PRIORITY:
		     वापस_cfg = PORT_HW_CFG_PHY_SELECTION_FIRST_PHY_PRIORITY;
		     अवरोध;
		हाल PORT_HW_CFG_PHY_SELECTION_SECOND_PHY:
		     वापस_cfg = PORT_HW_CFG_PHY_SELECTION_FIRST_PHY;
		     अवरोध;
		हाल PORT_HW_CFG_PHY_SELECTION_FIRST_PHY:
		     वापस_cfg = PORT_HW_CFG_PHY_SELECTION_SECOND_PHY;
		     अवरोध;
		पूर्ण
	पूर्ण अन्यथा
		वापस_cfg = prio_cfg;

	वापस वापस_cfg;
पूर्ण

पूर्णांक bnx2x_phy_probe(काष्ठा link_params *params)
अणु
	u8 phy_index, actual_phy_idx;
	u32 phy_config_swapped, sync_offset, media_types;
	काष्ठा bnx2x *bp = params->bp;
	काष्ठा bnx2x_phy *phy;
	params->num_phys = 0;
	DP(NETIF_MSG_LINK, "Begin phy probe\n");
	phy_config_swapped = params->multi_phy_config &
		PORT_HW_CFG_PHY_SWAPPED_ENABLED;

	क्रम (phy_index = INT_PHY; phy_index < MAX_PHYS;
	      phy_index++) अणु
		actual_phy_idx = phy_index;
		अगर (phy_config_swapped) अणु
			अगर (phy_index == EXT_PHY1)
				actual_phy_idx = EXT_PHY2;
			अन्यथा अगर (phy_index == EXT_PHY2)
				actual_phy_idx = EXT_PHY1;
		पूर्ण
		DP(NETIF_MSG_LINK, "phy_config_swapped %x, phy_index %x,"
			       " actual_phy_idx %x\n", phy_config_swapped,
			   phy_index, actual_phy_idx);
		phy = &params->phy[actual_phy_idx];
		अगर (bnx2x_populate_phy(bp, phy_index, params->shmem_base,
				       params->shmem2_base, params->port,
				       phy) != 0) अणु
			params->num_phys = 0;
			DP(NETIF_MSG_LINK, "phy probe failed in phy index %d\n",
				   phy_index);
			क्रम (phy_index = INT_PHY;
			      phy_index < MAX_PHYS;
			      phy_index++)
				*phy = phy_null;
			वापस -EINVAL;
		पूर्ण
		अगर (phy->type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_NOT_CONN)
			अवरोध;

		अगर (params->feature_config_flags &
		    FEATURE_CONFIG_DISABLE_REMOTE_FAULT_DET)
			phy->flags &= ~FLAGS_TX_ERROR_CHECK;

		अगर (!(params->feature_config_flags &
		      FEATURE_CONFIG_MT_SUPPORT))
			phy->flags |= FLAGS_MDC_MDIO_WA_G;

		sync_offset = params->shmem_base +
			दुरत्व(काष्ठा shmem_region,
			dev_info.port_hw_config[params->port].media_type);
		media_types = REG_RD(bp, sync_offset);

		/* Update media type क्रम non-PMF sync only क्रम the first समय
		 * In हाल the media type changes afterwards, it will be updated
		 * using the update_status function
		 */
		अगर ((media_types & (PORT_HW_CFG_MEDIA_TYPE_PHY0_MASK <<
				    (PORT_HW_CFG_MEDIA_TYPE_PHY1_SHIFT *
				     actual_phy_idx))) == 0) अणु
			media_types |= ((phy->media_type &
					PORT_HW_CFG_MEDIA_TYPE_PHY0_MASK) <<
				(PORT_HW_CFG_MEDIA_TYPE_PHY1_SHIFT *
				 actual_phy_idx));
		पूर्ण
		REG_WR(bp, sync_offset, media_types);

		bnx2x_phy_def_cfg(params, phy, phy_index);
		params->num_phys++;
	पूर्ण

	DP(NETIF_MSG_LINK, "End phy probe. #phys found %x\n", params->num_phys);
	वापस 0;
पूर्ण

अटल व्योम bnx2x_init_bmac_loopback(काष्ठा link_params *params,
				     काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	vars->link_up = 1;
	vars->line_speed = SPEED_10000;
	vars->duplex = DUPLEX_FULL;
	vars->flow_ctrl = BNX2X_FLOW_CTRL_NONE;
	vars->mac_type = MAC_TYPE_BMAC;

	vars->phy_flags = PHY_XGXS_FLAG;

	bnx2x_xgxs_deनिश्चित(params);

	/* Set bmac loopback */
	bnx2x_bmac_enable(params, vars, 1, 1);

	REG_WR(bp, NIG_REG_EGRESS_DRAIN0_MODE + params->port * 4, 0);
पूर्ण

अटल व्योम bnx2x_init_emac_loopback(काष्ठा link_params *params,
				     काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	vars->link_up = 1;
	vars->line_speed = SPEED_1000;
	vars->duplex = DUPLEX_FULL;
	vars->flow_ctrl = BNX2X_FLOW_CTRL_NONE;
	vars->mac_type = MAC_TYPE_EMAC;

	vars->phy_flags = PHY_XGXS_FLAG;

	bnx2x_xgxs_deनिश्चित(params);
	/* Set bmac loopback */
	bnx2x_emac_enable(params, vars, 1);
	bnx2x_emac_program(params, vars);
	REG_WR(bp, NIG_REG_EGRESS_DRAIN0_MODE + params->port * 4, 0);
पूर्ण

अटल व्योम bnx2x_init_xmac_loopback(काष्ठा link_params *params,
				     काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	vars->link_up = 1;
	अगर (!params->req_line_speed[0])
		vars->line_speed = SPEED_10000;
	अन्यथा
		vars->line_speed = params->req_line_speed[0];
	vars->duplex = DUPLEX_FULL;
	vars->flow_ctrl = BNX2X_FLOW_CTRL_NONE;
	vars->mac_type = MAC_TYPE_XMAC;
	vars->phy_flags = PHY_XGXS_FLAG;
	/* Set WC to loopback mode since link is required to provide घड़ी
	 * to the XMAC in 20G mode
	 */
	bnx2x_set_aer_mmd(params, &params->phy[0]);
	bnx2x_warpcore_reset_lane(bp, &params->phy[0], 0);
	params->phy[INT_PHY].config_loopback(
			&params->phy[INT_PHY],
			params);

	bnx2x_xmac_enable(params, vars, 1);
	REG_WR(bp, NIG_REG_EGRESS_DRAIN0_MODE + params->port*4, 0);
पूर्ण

अटल व्योम bnx2x_init_umac_loopback(काष्ठा link_params *params,
				     काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	vars->link_up = 1;
	vars->line_speed = SPEED_1000;
	vars->duplex = DUPLEX_FULL;
	vars->flow_ctrl = BNX2X_FLOW_CTRL_NONE;
	vars->mac_type = MAC_TYPE_UMAC;
	vars->phy_flags = PHY_XGXS_FLAG;
	bnx2x_umac_enable(params, vars, 1);

	REG_WR(bp, NIG_REG_EGRESS_DRAIN0_MODE + params->port*4, 0);
पूर्ण

अटल व्योम bnx2x_init_xgxs_loopback(काष्ठा link_params *params,
				     काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	काष्ठा bnx2x_phy *पूर्णांक_phy = &params->phy[INT_PHY];
	vars->link_up = 1;
	vars->flow_ctrl = BNX2X_FLOW_CTRL_NONE;
	vars->duplex = DUPLEX_FULL;
	अगर (params->req_line_speed[0] == SPEED_1000)
		vars->line_speed = SPEED_1000;
	अन्यथा अगर ((params->req_line_speed[0] == SPEED_20000) ||
		 (पूर्णांक_phy->flags & FLAGS_WC_DUAL_MODE))
		vars->line_speed = SPEED_20000;
	अन्यथा
		vars->line_speed = SPEED_10000;

	अगर (!USES_WARPCORE(bp))
		bnx2x_xgxs_deनिश्चित(params);
	bnx2x_link_initialize(params, vars);

	अगर (params->req_line_speed[0] == SPEED_1000) अणु
		अगर (USES_WARPCORE(bp))
			bnx2x_umac_enable(params, vars, 0);
		अन्यथा अणु
			bnx2x_emac_program(params, vars);
			bnx2x_emac_enable(params, vars, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (USES_WARPCORE(bp))
			bnx2x_xmac_enable(params, vars, 0);
		अन्यथा
			bnx2x_bmac_enable(params, vars, 0, 1);
	पूर्ण

	अगर (params->loopback_mode == LOOPBACK_XGXS) अणु
		/* Set 10G XGXS loopback */
		पूर्णांक_phy->config_loopback(पूर्णांक_phy, params);
	पूर्ण अन्यथा अणु
		/* Set बाह्यal phy loopback */
		u8 phy_index;
		क्रम (phy_index = EXT_PHY1;
		      phy_index < params->num_phys; phy_index++)
			अगर (params->phy[phy_index].config_loopback)
				params->phy[phy_index].config_loopback(
					&params->phy[phy_index],
					params);
	पूर्ण
	REG_WR(bp, NIG_REG_EGRESS_DRAIN0_MODE + params->port*4, 0);

	bnx2x_set_led(params, vars, LED_MODE_OPER, vars->line_speed);
पूर्ण

व्योम bnx2x_set_rx_filter(काष्ठा link_params *params, u8 en)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u8 val = en * 0x1F;

	/* Open / बंद the gate between the NIG and the BRB */
	अगर (!CHIP_IS_E1x(bp))
		val |= en * 0x20;
	REG_WR(bp, NIG_REG_LLH0_BRB1_DRV_MASK + params->port*4, val);

	अगर (!CHIP_IS_E1(bp)) अणु
		REG_WR(bp, NIG_REG_LLH0_BRB1_DRV_MASK_MF + params->port*4,
		       en*0x3);
	पूर्ण

	REG_WR(bp, (params->port ? NIG_REG_LLH1_BRB1_NOT_MCP :
		    NIG_REG_LLH0_BRB1_NOT_MCP), en);
पूर्ण
अटल पूर्णांक bnx2x_aव्योम_link_flap(काष्ठा link_params *params,
					    काष्ठा link_vars *vars)
अणु
	u32 phy_idx;
	u32 करोnt_clear_stat, lfa_sts;
	काष्ठा bnx2x *bp = params->bp;

	bnx2x_set_mdio_emac_per_phy(bp, params);
	/* Sync the link parameters */
	bnx2x_link_status_update(params, vars);

	/*
	 * The module verअगरication was alपढ़ोy करोne by previous link owner,
	 * so this call is meant only to get warning message
	 */

	क्रम (phy_idx = INT_PHY; phy_idx < params->num_phys; phy_idx++) अणु
		काष्ठा bnx2x_phy *phy = &params->phy[phy_idx];
		अगर (phy->phy_specअगरic_func) अणु
			DP(NETIF_MSG_LINK, "Calling PHY specific func\n");
			phy->phy_specअगरic_func(phy, params, PHY_INIT);
		पूर्ण
		अगर ((phy->media_type == ETH_PHY_SFPP_10G_FIBER) ||
		    (phy->media_type == ETH_PHY_SFP_1G_FIBER) ||
		    (phy->media_type == ETH_PHY_DA_TWINAX))
			bnx2x_verअगरy_sfp_module(phy, params);
	पूर्ण
	lfa_sts = REG_RD(bp, params->lfa_base +
			 दुरत्व(काष्ठा shmem_lfa,
				  lfa_sts));

	करोnt_clear_stat = lfa_sts & SHMEM_LFA_DONT_CLEAR_STAT;

	/* Re-enable the NIG/MAC */
	अगर (CHIP_IS_E3(bp)) अणु
		अगर (!करोnt_clear_stat) अणु
			REG_WR(bp, GRCBASE_MISC +
			       MISC_REGISTERS_RESET_REG_2_CLEAR,
			       (MISC_REGISTERS_RESET_REG_2_MSTAT0 <<
				params->port));
			REG_WR(bp, GRCBASE_MISC +
			       MISC_REGISTERS_RESET_REG_2_SET,
			       (MISC_REGISTERS_RESET_REG_2_MSTAT0 <<
				params->port));
		पूर्ण
		अगर (vars->line_speed < SPEED_10000)
			bnx2x_umac_enable(params, vars, 0);
		अन्यथा
			bnx2x_xmac_enable(params, vars, 0);
	पूर्ण अन्यथा अणु
		अगर (vars->line_speed < SPEED_10000)
			bnx2x_emac_enable(params, vars, 0);
		अन्यथा
			bnx2x_bmac_enable(params, vars, 0, !करोnt_clear_stat);
	पूर्ण

	/* Increment LFA count */
	lfa_sts = ((lfa_sts & ~LINK_FLAP_AVOIDANCE_COUNT_MASK) |
		   (((((lfa_sts & LINK_FLAP_AVOIDANCE_COUNT_MASK) >>
		       LINK_FLAP_AVOIDANCE_COUNT_OFFSET) + 1) & 0xff)
		    << LINK_FLAP_AVOIDANCE_COUNT_OFFSET));
	/* Clear link flap reason */
	lfa_sts &= ~LFA_LINK_FLAP_REASON_MASK;

	REG_WR(bp, params->lfa_base +
	       दुरत्व(काष्ठा shmem_lfa, lfa_sts), lfa_sts);

	/* Disable NIG DRAIN */
	REG_WR(bp, NIG_REG_EGRESS_DRAIN0_MODE + params->port*4, 0);

	/* Enable पूर्णांकerrupts */
	bnx2x_link_पूर्णांक_enable(params);
	वापस 0;
पूर्ण

अटल व्योम bnx2x_cannot_aव्योम_link_flap(काष्ठा link_params *params,
					 काष्ठा link_vars *vars,
					 पूर्णांक lfa_status)
अणु
	u32 lfa_sts, cfg_idx, पंचांगp_val;
	काष्ठा bnx2x *bp = params->bp;

	bnx2x_link_reset(params, vars, 1);

	अगर (!params->lfa_base)
		वापस;
	/* Store the new link parameters */
	REG_WR(bp, params->lfa_base +
	       दुरत्व(काष्ठा shmem_lfa, req_duplex),
	       params->req_duplex[0] | (params->req_duplex[1] << 16));

	REG_WR(bp, params->lfa_base +
	       दुरत्व(काष्ठा shmem_lfa, req_flow_ctrl),
	       params->req_flow_ctrl[0] | (params->req_flow_ctrl[1] << 16));

	REG_WR(bp, params->lfa_base +
	       दुरत्व(काष्ठा shmem_lfa, req_line_speed),
	       params->req_line_speed[0] | (params->req_line_speed[1] << 16));

	क्रम (cfg_idx = 0; cfg_idx < SHMEM_LINK_CONFIG_SIZE; cfg_idx++) अणु
		REG_WR(bp, params->lfa_base +
		       दुरत्व(काष्ठा shmem_lfa,
				speed_cap_mask[cfg_idx]),
		       params->speed_cap_mask[cfg_idx]);
	पूर्ण

	पंचांगp_val = REG_RD(bp, params->lfa_base +
			 दुरत्व(काष्ठा shmem_lfa, additional_config));
	पंचांगp_val &= ~REQ_FC_AUTO_ADV_MASK;
	पंचांगp_val |= params->req_fc_स्वतः_adv;

	REG_WR(bp, params->lfa_base +
	       दुरत्व(काष्ठा shmem_lfa, additional_config), पंचांगp_val);

	lfa_sts = REG_RD(bp, params->lfa_base +
			 दुरत्व(काष्ठा shmem_lfa, lfa_sts));

	/* Clear the "Don't Clear Statistics" bit, and set reason */
	lfa_sts &= ~SHMEM_LFA_DONT_CLEAR_STAT;

	/* Set link flap reason */
	lfa_sts &= ~LFA_LINK_FLAP_REASON_MASK;
	lfa_sts |= ((lfa_status & LFA_LINK_FLAP_REASON_MASK) <<
		    LFA_LINK_FLAP_REASON_OFFSET);

	/* Increment link flap counter */
	lfa_sts = ((lfa_sts & ~LINK_FLAP_COUNT_MASK) |
		   (((((lfa_sts & LINK_FLAP_COUNT_MASK) >>
		       LINK_FLAP_COUNT_OFFSET) + 1) & 0xff)
		    << LINK_FLAP_COUNT_OFFSET));
	REG_WR(bp, params->lfa_base +
	       दुरत्व(काष्ठा shmem_lfa, lfa_sts), lfa_sts);
	/* Proceed with regular link initialization */
पूर्ण

पूर्णांक bnx2x_phy_init(काष्ठा link_params *params, काष्ठा link_vars *vars)
अणु
	पूर्णांक lfa_status;
	काष्ठा bnx2x *bp = params->bp;
	DP(NETIF_MSG_LINK, "Phy Initialization started\n");
	DP(NETIF_MSG_LINK, "(1) req_speed %d, req_flowctrl %d\n",
		   params->req_line_speed[0], params->req_flow_ctrl[0]);
	DP(NETIF_MSG_LINK, "(2) req_speed %d, req_flowctrl %d\n",
		   params->req_line_speed[1], params->req_flow_ctrl[1]);
	DP(NETIF_MSG_LINK, "req_adv_flow_ctrl 0x%x\n", params->req_fc_स्वतः_adv);
	vars->link_status = 0;
	vars->phy_link_up = 0;
	vars->link_up = 0;
	vars->line_speed = 0;
	vars->duplex = DUPLEX_FULL;
	vars->flow_ctrl = BNX2X_FLOW_CTRL_NONE;
	vars->mac_type = MAC_TYPE_NONE;
	vars->phy_flags = 0;
	vars->check_kr2_recovery_cnt = 0;
	params->link_flags = PHY_INITIALIZED;
	/* Driver खोलोs NIG-BRB filters */
	bnx2x_set_rx_filter(params, 1);
	bnx2x_chng_link_count(params, true);
	/* Check अगर link flap can be aव्योमed */
	lfa_status = bnx2x_check_lfa(params);

	अगर (lfa_status == 0) अणु
		DP(NETIF_MSG_LINK, "Link Flap Avoidance in progress\n");
		वापस bnx2x_aव्योम_link_flap(params, vars);
	पूर्ण

	DP(NETIF_MSG_LINK, "Cannot avoid link flap lfa_sta=0x%x\n",
		       lfa_status);
	bnx2x_cannot_aव्योम_link_flap(params, vars, lfa_status);

	/* Disable attentions */
	bnx2x_bits_dis(bp, NIG_REG_MASK_INTERRUPT_PORT0 + params->port*4,
		       (NIG_MASK_XGXS0_LINK_STATUS |
			NIG_MASK_XGXS0_LINK10G |
			NIG_MASK_SERDES0_LINK_STATUS |
			NIG_MASK_MI_INT));

	bnx2x_emac_init(params, vars);

	अगर (params->feature_config_flags & FEATURE_CONFIG_PFC_ENABLED)
		vars->link_status |= LINK_STATUS_PFC_ENABLED;

	अगर (params->num_phys == 0) अणु
		DP(NETIF_MSG_LINK, "No phy found for initialization !!\n");
		वापस -EINVAL;
	पूर्ण
	set_phy_vars(params, vars);

	DP(NETIF_MSG_LINK, "Num of phys on board: %d\n", params->num_phys);
	चयन (params->loopback_mode) अणु
	हाल LOOPBACK_BMAC:
		bnx2x_init_bmac_loopback(params, vars);
		अवरोध;
	हाल LOOPBACK_EMAC:
		bnx2x_init_emac_loopback(params, vars);
		अवरोध;
	हाल LOOPBACK_XMAC:
		bnx2x_init_xmac_loopback(params, vars);
		अवरोध;
	हाल LOOPBACK_UMAC:
		bnx2x_init_umac_loopback(params, vars);
		अवरोध;
	हाल LOOPBACK_XGXS:
	हाल LOOPBACK_EXT_PHY:
		bnx2x_init_xgxs_loopback(params, vars);
		अवरोध;
	शेष:
		अगर (!CHIP_IS_E3(bp)) अणु
			अगर (params->चयन_cfg == SWITCH_CFG_10G)
				bnx2x_xgxs_deनिश्चित(params);
			अन्यथा
				bnx2x_serdes_deनिश्चित(bp, params->port);
		पूर्ण
		bnx2x_link_initialize(params, vars);
		msleep(30);
		bnx2x_link_पूर्णांक_enable(params);
		अवरोध;
	पूर्ण
	bnx2x_update_mng(params, vars->link_status);

	bnx2x_update_mng_eee(params, vars->eee_status);
	वापस 0;
पूर्ण

पूर्णांक bnx2x_link_reset(काष्ठा link_params *params, काष्ठा link_vars *vars,
		     u8 reset_ext_phy)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u8 phy_index, port = params->port, clear_latch_ind = 0;
	DP(NETIF_MSG_LINK, "Resetting the link of port %d\n", port);
	/* Disable attentions */
	vars->link_status = 0;
	bnx2x_chng_link_count(params, true);
	bnx2x_update_mng(params, vars->link_status);
	vars->eee_status &= ~(SHMEM_EEE_LP_ADV_STATUS_MASK |
			      SHMEM_EEE_ACTIVE_BIT);
	bnx2x_update_mng_eee(params, vars->eee_status);
	bnx2x_bits_dis(bp, NIG_REG_MASK_INTERRUPT_PORT0 + port*4,
		       (NIG_MASK_XGXS0_LINK_STATUS |
			NIG_MASK_XGXS0_LINK10G |
			NIG_MASK_SERDES0_LINK_STATUS |
			NIG_MASK_MI_INT));

	/* Activate nig drain */
	REG_WR(bp, NIG_REG_EGRESS_DRAIN0_MODE + port*4, 1);

	/* Disable nig egress पूर्णांकerface */
	अगर (!CHIP_IS_E3(bp)) अणु
		REG_WR(bp, NIG_REG_BMAC0_OUT_EN + port*4, 0);
		REG_WR(bp, NIG_REG_EGRESS_EMAC0_OUT_EN + port*4, 0);
	पूर्ण

	अगर (!CHIP_IS_E3(bp)) अणु
		bnx2x_set_bmac_rx(bp, params->chip_id, port, 0);
	पूर्ण अन्यथा अणु
		bnx2x_set_xmac_rxtx(params, 0);
		bnx2x_set_umac_rxtx(params, 0);
	पूर्ण
	/* Disable emac */
	अगर (!CHIP_IS_E3(bp))
		REG_WR(bp, NIG_REG_NIG_EMAC0_EN + port*4, 0);

	usleep_range(10000, 20000);
	/* The PHY reset is controlled by GPIO 1
	 * Hold it as vars low
	 */
	 /* Clear link led */
	bnx2x_set_mdio_emac_per_phy(bp, params);
	bnx2x_set_led(params, vars, LED_MODE_OFF, 0);

	अगर (reset_ext_phy) अणु
		क्रम (phy_index = EXT_PHY1; phy_index < params->num_phys;
		      phy_index++) अणु
			अगर (params->phy[phy_index].link_reset) अणु
				bnx2x_set_aer_mmd(params,
						  &params->phy[phy_index]);
				params->phy[phy_index].link_reset(
					&params->phy[phy_index],
					params);
			पूर्ण
			अगर (params->phy[phy_index].flags &
			    FLAGS_REARM_LATCH_SIGNAL)
				clear_latch_ind = 1;
		पूर्ण
	पूर्ण

	अगर (clear_latch_ind) अणु
		/* Clear latching indication */
		bnx2x_rearm_latch_संकेत(bp, port, 0);
		bnx2x_bits_dis(bp, NIG_REG_LATCH_BC_0 + port*4,
			       1 << NIG_LATCH_BC_ENABLE_MI_INT);
	पूर्ण
	अगर (params->phy[INT_PHY].link_reset)
		params->phy[INT_PHY].link_reset(
			&params->phy[INT_PHY], params);

	/* Disable nig ingress पूर्णांकerface */
	अगर (!CHIP_IS_E3(bp)) अणु
		/* Reset BigMac */
		REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_2_CLEAR,
		       (MISC_REGISTERS_RESET_REG_2_RST_BMAC0 << port));
		REG_WR(bp, NIG_REG_BMAC0_IN_EN + port*4, 0);
		REG_WR(bp, NIG_REG_EMAC0_IN_EN + port*4, 0);
	पूर्ण अन्यथा अणु
		u32 xmac_base = (params->port) ? GRCBASE_XMAC1 : GRCBASE_XMAC0;
		bnx2x_set_xumac_nig(params, 0, 0);
		अगर (REG_RD(bp, MISC_REG_RESET_REG_2) &
		    MISC_REGISTERS_RESET_REG_2_XMAC)
			REG_WR(bp, xmac_base + XMAC_REG_CTRL,
			       XMAC_CTRL_REG_SOFT_RESET);
	पूर्ण
	vars->link_up = 0;
	vars->phy_flags = 0;
	वापस 0;
पूर्ण
पूर्णांक bnx2x_lfa_reset(काष्ठा link_params *params,
			       काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	vars->link_up = 0;
	vars->phy_flags = 0;
	params->link_flags &= ~PHY_INITIALIZED;
	अगर (!params->lfa_base)
		वापस bnx2x_link_reset(params, vars, 1);
	/*
	 * Activate NIG drain so that during this समय the device won't send
	 * anything जबतक it is unable to response.
	 */
	REG_WR(bp, NIG_REG_EGRESS_DRAIN0_MODE + params->port*4, 1);

	/*
	 * Close gracefully the gate from BMAC to NIG such that no half packets
	 * are passed.
	 */
	अगर (!CHIP_IS_E3(bp))
		bnx2x_set_bmac_rx(bp, params->chip_id, params->port, 0);

	अगर (CHIP_IS_E3(bp)) अणु
		bnx2x_set_xmac_rxtx(params, 0);
		bnx2x_set_umac_rxtx(params, 0);
	पूर्ण
	/* Wait 10ms क्रम the pipe to clean up*/
	usleep_range(10000, 20000);

	/* Clean the NIG-BRB using the network filters in a way that will
	 * not cut a packet in the middle.
	 */
	bnx2x_set_rx_filter(params, 0);

	/*
	 * Re-खोलो the gate between the BMAC and the NIG, after verअगरying the
	 * gate to the BRB is बंदd, otherwise packets may arrive to the
	 * firmware beक्रमe driver had initialized it. The target is to achieve
	 * minimum management protocol करोwn समय.
	 */
	अगर (!CHIP_IS_E3(bp))
		bnx2x_set_bmac_rx(bp, params->chip_id, params->port, 1);

	अगर (CHIP_IS_E3(bp)) अणु
		bnx2x_set_xmac_rxtx(params, 1);
		bnx2x_set_umac_rxtx(params, 1);
	पूर्ण
	/* Disable NIG drain */
	REG_WR(bp, NIG_REG_EGRESS_DRAIN0_MODE + params->port*4, 0);
	वापस 0;
पूर्ण

/****************************************************************************/
/*				Common function				    */
/****************************************************************************/
अटल पूर्णांक bnx2x_8073_common_init_phy(काष्ठा bnx2x *bp,
				      u32 shmem_base_path[],
				      u32 shmem2_base_path[], u8 phy_index,
				      u32 chip_id)
अणु
	काष्ठा bnx2x_phy phy[PORT_MAX];
	काष्ठा bnx2x_phy *phy_blk[PORT_MAX];
	u16 val;
	s8 port = 0;
	s8 port_of_path = 0;
	u32 swap_val, swap_override;
	swap_val = REG_RD(bp,  NIG_REG_PORT_SWAP);
	swap_override = REG_RD(bp,  NIG_REG_STRAP_OVERRIDE);
	port ^= (swap_val && swap_override);
	bnx2x_ext_phy_hw_reset(bp, port);
	/* PART1 - Reset both phys */
	क्रम (port = PORT_MAX - 1; port >= PORT_0; port--) अणु
		u32 shmem_base, shmem2_base;
		/* In E2, same phy is using क्रम port0 of the two paths */
		अगर (CHIP_IS_E1x(bp)) अणु
			shmem_base = shmem_base_path[0];
			shmem2_base = shmem2_base_path[0];
			port_of_path = port;
		पूर्ण अन्यथा अणु
			shmem_base = shmem_base_path[port];
			shmem2_base = shmem2_base_path[port];
			port_of_path = 0;
		पूर्ण

		/* Extract the ext phy address क्रम the port */
		अगर (bnx2x_populate_phy(bp, phy_index, shmem_base, shmem2_base,
				       port_of_path, &phy[port]) !=
		    0) अणु
			DP(NETIF_MSG_LINK, "populate_phy failed\n");
			वापस -EINVAL;
		पूर्ण
		/* Disable attentions */
		bnx2x_bits_dis(bp, NIG_REG_MASK_INTERRUPT_PORT0 +
			       port_of_path*4,
			       (NIG_MASK_XGXS0_LINK_STATUS |
				NIG_MASK_XGXS0_LINK10G |
				NIG_MASK_SERDES0_LINK_STATUS |
				NIG_MASK_MI_INT));

		/* Need to take the phy out of low घातer mode in order
		 * to ग_लिखो to access its रेजिस्टरs
		 */
		bnx2x_set_gpio(bp, MISC_REGISTERS_GPIO_2,
			       MISC_REGISTERS_GPIO_OUTPUT_HIGH,
			       port);

		/* Reset the phy */
		bnx2x_cl45_ग_लिखो(bp, &phy[port],
				 MDIO_PMA_DEVAD,
				 MDIO_PMA_REG_CTRL,
				 1<<15);
	पूर्ण

	/* Add delay of 150ms after reset */
	msleep(150);

	अगर (phy[PORT_0].addr & 0x1) अणु
		phy_blk[PORT_0] = &(phy[PORT_1]);
		phy_blk[PORT_1] = &(phy[PORT_0]);
	पूर्ण अन्यथा अणु
		phy_blk[PORT_0] = &(phy[PORT_0]);
		phy_blk[PORT_1] = &(phy[PORT_1]);
	पूर्ण

	/* PART2 - Download firmware to both phys */
	क्रम (port = PORT_MAX - 1; port >= PORT_0; port--) अणु
		अगर (CHIP_IS_E1x(bp))
			port_of_path = port;
		अन्यथा
			port_of_path = 0;

		DP(NETIF_MSG_LINK, "Loading spirom for phy address 0x%x\n",
			   phy_blk[port]->addr);
		अगर (bnx2x_8073_8727_बाह्यal_rom_boot(bp, phy_blk[port],
						      port_of_path))
			वापस -EINVAL;

		/* Only set bit 10 = 1 (Tx घातer करोwn) */
		bnx2x_cl45_पढ़ो(bp, phy_blk[port],
				MDIO_PMA_DEVAD,
				MDIO_PMA_REG_TX_POWER_DOWN, &val);

		/* Phase1 of TX_POWER_DOWN reset */
		bnx2x_cl45_ग_लिखो(bp, phy_blk[port],
				 MDIO_PMA_DEVAD,
				 MDIO_PMA_REG_TX_POWER_DOWN,
				 (val | 1<<10));
	पूर्ण

	/* Toggle Transmitter: Power करोwn and then up with 600ms delay
	 * between
	 */
	msleep(600);

	/* PART3 - complete TX_POWER_DOWN process, and set GPIO2 back to low */
	क्रम (port = PORT_MAX - 1; port >= PORT_0; port--) अणु
		/* Phase2 of POWER_DOWN_RESET */
		/* Release bit 10 (Release Tx घातer करोwn) */
		bnx2x_cl45_पढ़ो(bp, phy_blk[port],
				MDIO_PMA_DEVAD,
				MDIO_PMA_REG_TX_POWER_DOWN, &val);

		bnx2x_cl45_ग_लिखो(bp, phy_blk[port],
				MDIO_PMA_DEVAD,
				MDIO_PMA_REG_TX_POWER_DOWN, (val & (~(1<<10))));
		usleep_range(15000, 30000);

		/* Read modअगरy ग_लिखो the SPI-ROM version select रेजिस्टर */
		bnx2x_cl45_पढ़ो(bp, phy_blk[port],
				MDIO_PMA_DEVAD,
				MDIO_PMA_REG_EDC_FFE_MAIN, &val);
		bnx2x_cl45_ग_लिखो(bp, phy_blk[port],
				 MDIO_PMA_DEVAD,
				 MDIO_PMA_REG_EDC_FFE_MAIN, (val | (1<<12)));

		/* set GPIO2 back to LOW */
		bnx2x_set_gpio(bp, MISC_REGISTERS_GPIO_2,
			       MISC_REGISTERS_GPIO_OUTPUT_LOW, port);
	पूर्ण
	वापस 0;
पूर्ण
अटल पूर्णांक bnx2x_8726_common_init_phy(काष्ठा bnx2x *bp,
				      u32 shmem_base_path[],
				      u32 shmem2_base_path[], u8 phy_index,
				      u32 chip_id)
अणु
	u32 val;
	s8 port;
	काष्ठा bnx2x_phy phy;
	/* Use port1 because of the अटल port-swap */
	/* Enable the module detection पूर्णांकerrupt */
	val = REG_RD(bp, MISC_REG_GPIO_EVENT_EN);
	val |= ((1<<MISC_REGISTERS_GPIO_3)|
		(1<<(MISC_REGISTERS_GPIO_3 + MISC_REGISTERS_GPIO_PORT_SHIFT)));
	REG_WR(bp, MISC_REG_GPIO_EVENT_EN, val);

	bnx2x_ext_phy_hw_reset(bp, 0);
	usleep_range(5000, 10000);
	क्रम (port = 0; port < PORT_MAX; port++) अणु
		u32 shmem_base, shmem2_base;

		/* In E2, same phy is using क्रम port0 of the two paths */
		अगर (CHIP_IS_E1x(bp)) अणु
			shmem_base = shmem_base_path[0];
			shmem2_base = shmem2_base_path[0];
		पूर्ण अन्यथा अणु
			shmem_base = shmem_base_path[port];
			shmem2_base = shmem2_base_path[port];
		पूर्ण
		/* Extract the ext phy address क्रम the port */
		अगर (bnx2x_populate_phy(bp, phy_index, shmem_base, shmem2_base,
				       port, &phy) !=
		    0) अणु
			DP(NETIF_MSG_LINK, "populate phy failed\n");
			वापस -EINVAL;
		पूर्ण

		/* Reset phy*/
		bnx2x_cl45_ग_लिखो(bp, &phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_REG_GEN_CTRL, 0x0001);


		/* Set fault module detected LED on */
		bnx2x_set_gpio(bp, MISC_REGISTERS_GPIO_0,
			       MISC_REGISTERS_GPIO_HIGH,
			       port);
	पूर्ण

	वापस 0;
पूर्ण
अटल व्योम bnx2x_get_ext_phy_reset_gpio(काष्ठा bnx2x *bp, u32 shmem_base,
					 u8 *io_gpio, u8 *io_port)
अणु

	u32 phy_gpio_reset = REG_RD(bp, shmem_base +
					  दुरत्व(काष्ठा shmem_region,
				dev_info.port_hw_config[PORT_0].शेष_cfg));
	चयन (phy_gpio_reset) अणु
	हाल PORT_HW_CFG_EXT_PHY_GPIO_RST_GPIO0_P0:
		*io_gpio = 0;
		*io_port = 0;
		अवरोध;
	हाल PORT_HW_CFG_EXT_PHY_GPIO_RST_GPIO1_P0:
		*io_gpio = 1;
		*io_port = 0;
		अवरोध;
	हाल PORT_HW_CFG_EXT_PHY_GPIO_RST_GPIO2_P0:
		*io_gpio = 2;
		*io_port = 0;
		अवरोध;
	हाल PORT_HW_CFG_EXT_PHY_GPIO_RST_GPIO3_P0:
		*io_gpio = 3;
		*io_port = 0;
		अवरोध;
	हाल PORT_HW_CFG_EXT_PHY_GPIO_RST_GPIO0_P1:
		*io_gpio = 0;
		*io_port = 1;
		अवरोध;
	हाल PORT_HW_CFG_EXT_PHY_GPIO_RST_GPIO1_P1:
		*io_gpio = 1;
		*io_port = 1;
		अवरोध;
	हाल PORT_HW_CFG_EXT_PHY_GPIO_RST_GPIO2_P1:
		*io_gpio = 2;
		*io_port = 1;
		अवरोध;
	हाल PORT_HW_CFG_EXT_PHY_GPIO_RST_GPIO3_P1:
		*io_gpio = 3;
		*io_port = 1;
		अवरोध;
	शेष:
		/* Don't override the io_gpio and io_port */
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_8727_common_init_phy(काष्ठा bnx2x *bp,
				      u32 shmem_base_path[],
				      u32 shmem2_base_path[], u8 phy_index,
				      u32 chip_id)
अणु
	s8 port, reset_gpio;
	u32 swap_val, swap_override;
	काष्ठा bnx2x_phy phy[PORT_MAX];
	काष्ठा bnx2x_phy *phy_blk[PORT_MAX];
	s8 port_of_path;
	swap_val = REG_RD(bp, NIG_REG_PORT_SWAP);
	swap_override = REG_RD(bp, NIG_REG_STRAP_OVERRIDE);

	reset_gpio = MISC_REGISTERS_GPIO_1;
	port = 1;

	/* Retrieve the reset gpio/port which control the reset.
	 * Default is GPIO1, PORT1
	 */
	bnx2x_get_ext_phy_reset_gpio(bp, shmem_base_path[0],
				     (u8 *)&reset_gpio, (u8 *)&port);

	/* Calculate the port based on port swap */
	port ^= (swap_val && swap_override);

	/* Initiate PHY reset*/
	bnx2x_set_gpio(bp, reset_gpio, MISC_REGISTERS_GPIO_OUTPUT_LOW,
		       port);
	usleep_range(1000, 2000);
	bnx2x_set_gpio(bp, reset_gpio, MISC_REGISTERS_GPIO_OUTPUT_HIGH,
		       port);

	usleep_range(5000, 10000);

	/* PART1 - Reset both phys */
	क्रम (port = PORT_MAX - 1; port >= PORT_0; port--) अणु
		u32 shmem_base, shmem2_base;

		/* In E2, same phy is using क्रम port0 of the two paths */
		अगर (CHIP_IS_E1x(bp)) अणु
			shmem_base = shmem_base_path[0];
			shmem2_base = shmem2_base_path[0];
			port_of_path = port;
		पूर्ण अन्यथा अणु
			shmem_base = shmem_base_path[port];
			shmem2_base = shmem2_base_path[port];
			port_of_path = 0;
		पूर्ण

		/* Extract the ext phy address क्रम the port */
		अगर (bnx2x_populate_phy(bp, phy_index, shmem_base, shmem2_base,
				       port_of_path, &phy[port]) !=
				       0) अणु
			DP(NETIF_MSG_LINK, "populate phy failed\n");
			वापस -EINVAL;
		पूर्ण
		/* disable attentions */
		bnx2x_bits_dis(bp, NIG_REG_MASK_INTERRUPT_PORT0 +
			       port_of_path*4,
			       (NIG_MASK_XGXS0_LINK_STATUS |
				NIG_MASK_XGXS0_LINK10G |
				NIG_MASK_SERDES0_LINK_STATUS |
				NIG_MASK_MI_INT));


		/* Reset the phy */
		bnx2x_cl45_ग_लिखो(bp, &phy[port],
				 MDIO_PMA_DEVAD, MDIO_PMA_REG_CTRL, 1<<15);
	पूर्ण

	/* Add delay of 150ms after reset */
	msleep(150);
	अगर (phy[PORT_0].addr & 0x1) अणु
		phy_blk[PORT_0] = &(phy[PORT_1]);
		phy_blk[PORT_1] = &(phy[PORT_0]);
	पूर्ण अन्यथा अणु
		phy_blk[PORT_0] = &(phy[PORT_0]);
		phy_blk[PORT_1] = &(phy[PORT_1]);
	पूर्ण
	/* PART2 - Download firmware to both phys */
	क्रम (port = PORT_MAX - 1; port >= PORT_0; port--) अणु
		अगर (CHIP_IS_E1x(bp))
			port_of_path = port;
		अन्यथा
			port_of_path = 0;
		DP(NETIF_MSG_LINK, "Loading spirom for phy address 0x%x\n",
			   phy_blk[port]->addr);
		अगर (bnx2x_8073_8727_बाह्यal_rom_boot(bp, phy_blk[port],
						      port_of_path))
			वापस -EINVAL;
		/* Disable PHY transmitter output */
		bnx2x_cl45_ग_लिखो(bp, phy_blk[port],
				 MDIO_PMA_DEVAD,
				 MDIO_PMA_REG_TX_DISABLE, 1);

	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_84833_common_init_phy(काष्ठा bnx2x *bp,
						u32 shmem_base_path[],
						u32 shmem2_base_path[],
						u8 phy_index,
						u32 chip_id)
अणु
	u8 reset_gpios;
	reset_gpios = bnx2x_84833_get_reset_gpios(bp, shmem_base_path, chip_id);
	bnx2x_set_mult_gpio(bp, reset_gpios, MISC_REGISTERS_GPIO_OUTPUT_LOW);
	udelay(10);
	bnx2x_set_mult_gpio(bp, reset_gpios, MISC_REGISTERS_GPIO_OUTPUT_HIGH);
	DP(NETIF_MSG_LINK, "84833 reset pulse on pin values 0x%x\n",
		reset_gpios);
	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_ext_phy_common_init(काष्ठा bnx2x *bp, u32 shmem_base_path[],
				     u32 shmem2_base_path[], u8 phy_index,
				     u32 ext_phy_type, u32 chip_id)
अणु
	पूर्णांक rc = 0;

	चयन (ext_phy_type) अणु
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8073:
		rc = bnx2x_8073_common_init_phy(bp, shmem_base_path,
						shmem2_base_path,
						phy_index, chip_id);
		अवरोध;
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8722:
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8727:
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8727_NOC:
		rc = bnx2x_8727_common_init_phy(bp, shmem_base_path,
						shmem2_base_path,
						phy_index, chip_id);
		अवरोध;

	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8726:
		/* GPIO1 affects both ports, so there's need to pull
		 * it क्रम single port alone
		 */
		rc = bnx2x_8726_common_init_phy(bp, shmem_base_path,
						shmem2_base_path,
						phy_index, chip_id);
		अवरोध;
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84833:
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84834:
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84858:
		/* GPIO3's are linked, and so both need to be toggled
		 * to obtain required 2us pulse.
		 */
		rc = bnx2x_84833_common_init_phy(bp, shmem_base_path,
						shmem2_base_path,
						phy_index, chip_id);
		अवरोध;
	हाल PORT_HW_CFG_XGXS_EXT_PHY_TYPE_FAILURE:
		rc = -EINVAL;
		अवरोध;
	शेष:
		DP(NETIF_MSG_LINK,
			   "ext_phy 0x%x common init not required\n",
			   ext_phy_type);
		अवरोध;
	पूर्ण

	अगर (rc)
		netdev_err(bp->dev,  "Warning: PHY was not initialized,"
				      " Port %d\n",
			 0);
	वापस rc;
पूर्ण

पूर्णांक bnx2x_common_init_phy(काष्ठा bnx2x *bp, u32 shmem_base_path[],
			  u32 shmem2_base_path[], u32 chip_id)
अणु
	पूर्णांक rc = 0;
	u32 phy_ver, val;
	u8 phy_index = 0;
	u32 ext_phy_type, ext_phy_config;

	bnx2x_set_mdio_clk(bp, chip_id, GRCBASE_EMAC0);
	bnx2x_set_mdio_clk(bp, chip_id, GRCBASE_EMAC1);
	DP(NETIF_MSG_LINK, "Begin common phy init\n");
	अगर (CHIP_IS_E3(bp)) अणु
		/* Enable EPIO */
		val = REG_RD(bp, MISC_REG_GEN_PURP_HWG);
		REG_WR(bp, MISC_REG_GEN_PURP_HWG, val | 1);
	पूर्ण
	/* Check अगर common init was alपढ़ोy करोne */
	phy_ver = REG_RD(bp, shmem_base_path[0] +
			 दुरत्व(काष्ठा shmem_region,
				  port_mb[PORT_0].ext_phy_fw_version));
	अगर (phy_ver) अणु
		DP(NETIF_MSG_LINK, "Not doing common init; phy ver is 0x%x\n",
			       phy_ver);
		वापस 0;
	पूर्ण

	/* Read the ext_phy_type क्रम arbitrary port(0) */
	क्रम (phy_index = EXT_PHY1; phy_index < MAX_PHYS;
	      phy_index++) अणु
		ext_phy_config = bnx2x_get_ext_phy_config(bp,
							  shmem_base_path[0],
							  phy_index, 0);
		ext_phy_type = XGXS_EXT_PHY_TYPE(ext_phy_config);
		rc |= bnx2x_ext_phy_common_init(bp, shmem_base_path,
						shmem2_base_path,
						phy_index, ext_phy_type,
						chip_id);
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम bnx2x_check_over_curr(काष्ठा link_params *params,
				  काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u32 cfg_pin;
	u8 port = params->port;
	u32 pin_val;

	cfg_pin = (REG_RD(bp, params->shmem_base +
			  दुरत्व(काष्ठा shmem_region,
			       dev_info.port_hw_config[port].e3_cmn_pin_cfg1)) &
		   PORT_HW_CFG_E3_OVER_CURRENT_MASK) >>
		PORT_HW_CFG_E3_OVER_CURRENT_SHIFT;

	/* Ignore check अगर no बाह्यal input PIN available */
	अगर (bnx2x_get_cfg_pin(bp, cfg_pin, &pin_val) != 0)
		वापस;

	अगर (!pin_val) अणु
		अगर ((vars->phy_flags & PHY_OVER_CURRENT_FLAG) == 0) अणु
			netdev_err(bp->dev, "Error:  Power fault on Port %d has"
					    " been detected and the power to "
					    "that SFP+ module has been removed"
					    " to prevent failure of the card."
					    " Please remove the SFP+ module and"
					    " restart the system to clear this"
					    " error.\n",
			 params->port);
			vars->phy_flags |= PHY_OVER_CURRENT_FLAG;
			bnx2x_warpcore_घातer_module(params, 0);
		पूर्ण
	पूर्ण अन्यथा
		vars->phy_flags &= ~PHY_OVER_CURRENT_FLAG;
पूर्ण

/* Returns 0 अगर no change occurred since last check; 1 otherwise. */
अटल u8 bnx2x_analyze_link_error(काष्ठा link_params *params,
				    काष्ठा link_vars *vars, u32 status,
				    u32 phy_flag, u32 link_flag, u8 notअगरy)
अणु
	काष्ठा bnx2x *bp = params->bp;
	/* Compare new value with previous value */
	u8 led_mode;
	u32 old_status = (vars->phy_flags & phy_flag) ? 1 : 0;

	अगर ((status ^ old_status) == 0)
		वापस 0;

	/* If values dअगरfer */
	चयन (phy_flag) अणु
	हाल PHY_HALF_OPEN_CONN_FLAG:
		DP(NETIF_MSG_LINK, "Analyze Remote Fault\n");
		अवरोध;
	हाल PHY_SFP_TX_FAULT_FLAG:
		DP(NETIF_MSG_LINK, "Analyze TX Fault\n");
		अवरोध;
	शेष:
		DP(NETIF_MSG_LINK, "Analyze UNKNOWN\n");
	पूर्ण
	DP(NETIF_MSG_LINK, "Link changed:[%x %x]->%x\n", vars->link_up,
	   old_status, status);

	/* Do not touch the link in हाल physical link करोwn */
	अगर ((vars->phy_flags & PHY_PHYSICAL_LINK_FLAG) == 0)
		वापस 1;

	/* a. Update shmem->link_status accordingly
	 * b. Update link_vars->link_up
	 */
	अगर (status) अणु
		vars->link_status &= ~LINK_STATUS_LINK_UP;
		vars->link_status |= link_flag;
		vars->link_up = 0;
		vars->phy_flags |= phy_flag;

		/* activate nig drain */
		REG_WR(bp, NIG_REG_EGRESS_DRAIN0_MODE + params->port*4, 1);
		/* Set LED mode to off since the PHY करोesn't know about these
		 * errors
		 */
		led_mode = LED_MODE_OFF;
	पूर्ण अन्यथा अणु
		vars->link_status |= LINK_STATUS_LINK_UP;
		vars->link_status &= ~link_flag;
		vars->link_up = 1;
		vars->phy_flags &= ~phy_flag;
		led_mode = LED_MODE_OPER;

		/* Clear nig drain */
		REG_WR(bp, NIG_REG_EGRESS_DRAIN0_MODE + params->port*4, 0);
	पूर्ण
	bnx2x_sync_link(params, vars);
	/* Update the LED according to the link state */
	bnx2x_set_led(params, vars, led_mode, SPEED_10000);

	/* Update link status in the shared memory */
	bnx2x_update_mng(params, vars->link_status);

	/* C. Trigger General Attention */
	vars->periodic_flags |= PERIODIC_FLAGS_LINK_EVENT;
	अगर (notअगरy)
		bnx2x_notअगरy_link_changed(bp);

	वापस 1;
पूर्ण

/******************************************************************************
* Description:
*	This function checks क्रम half खोलोed connection change indication.
*	When such change occurs, it calls the bnx2x_analyze_link_error
*	to check अगर Remote Fault is set or cleared. Reception of remote fault
*	status message in the MAC indicates that the peer's MAC has detected
*	a fault, क्रम example, due to अवरोध in the TX side of fiber.
*
******************************************************************************/
अटल पूर्णांक bnx2x_check_half_खोलो_conn(काष्ठा link_params *params,
				      काष्ठा link_vars *vars,
				      u8 notअगरy)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u32 lss_status = 0;
	u32 mac_base;
	/* In हाल link status is physically up @ 10G करो */
	अगर (((vars->phy_flags & PHY_PHYSICAL_LINK_FLAG) == 0) ||
	    (REG_RD(bp, NIG_REG_EGRESS_EMAC0_PORT + params->port*4)))
		वापस 0;

	अगर (CHIP_IS_E3(bp) &&
	    (REG_RD(bp, MISC_REG_RESET_REG_2) &
	      (MISC_REGISTERS_RESET_REG_2_XMAC))) अणु
		/* Check E3 XMAC */
		/* Note that link speed cannot be queried here, since it may be
		 * zero जबतक link is करोwn. In हाल UMAC is active, LSS will
		 * simply not be set
		 */
		mac_base = (params->port) ? GRCBASE_XMAC1 : GRCBASE_XMAC0;

		/* Clear stick bits (Requires rising edge) */
		REG_WR(bp, mac_base + XMAC_REG_CLEAR_RX_LSS_STATUS, 0);
		REG_WR(bp, mac_base + XMAC_REG_CLEAR_RX_LSS_STATUS,
		       XMAC_CLEAR_RX_LSS_STATUS_REG_CLEAR_LOCAL_FAULT_STATUS |
		       XMAC_CLEAR_RX_LSS_STATUS_REG_CLEAR_REMOTE_FAULT_STATUS);
		अगर (REG_RD(bp, mac_base + XMAC_REG_RX_LSS_STATUS))
			lss_status = 1;

		bnx2x_analyze_link_error(params, vars, lss_status,
					 PHY_HALF_OPEN_CONN_FLAG,
					 LINK_STATUS_NONE, notअगरy);
	पूर्ण अन्यथा अगर (REG_RD(bp, MISC_REG_RESET_REG_2) &
		   (MISC_REGISTERS_RESET_REG_2_RST_BMAC0 << params->port)) अणु
		/* Check E1X / E2 BMAC */
		u32 lss_status_reg;
		u32 wb_data[2];
		mac_base = params->port ? NIG_REG_INGRESS_BMAC1_MEM :
			NIG_REG_INGRESS_BMAC0_MEM;
		/*  Read BIGMAC_REGISTER_RX_LSS_STATUS */
		अगर (CHIP_IS_E2(bp))
			lss_status_reg = BIGMAC2_REGISTER_RX_LSS_STAT;
		अन्यथा
			lss_status_reg = BIGMAC_REGISTER_RX_LSS_STATUS;

		REG_RD_DMAE(bp, mac_base + lss_status_reg, wb_data, 2);
		lss_status = (wb_data[0] > 0);

		bnx2x_analyze_link_error(params, vars, lss_status,
					 PHY_HALF_OPEN_CONN_FLAG,
					 LINK_STATUS_NONE, notअगरy);
	पूर्ण
	वापस 0;
पूर्ण
अटल व्योम bnx2x_sfp_tx_fault_detection(काष्ठा bnx2x_phy *phy,
					 काष्ठा link_params *params,
					 काष्ठा link_vars *vars)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u32 cfg_pin, value = 0;
	u8 led_change, port = params->port;

	/* Get The SFP+ TX_Fault controlling pin ([eg]pio) */
	cfg_pin = (REG_RD(bp, params->shmem_base + दुरत्व(काष्ठा shmem_region,
			  dev_info.port_hw_config[port].e3_cmn_pin_cfg)) &
		   PORT_HW_CFG_E3_TX_FAULT_MASK) >>
		  PORT_HW_CFG_E3_TX_FAULT_SHIFT;

	अगर (bnx2x_get_cfg_pin(bp, cfg_pin, &value)) अणु
		DP(NETIF_MSG_LINK, "Failed to read pin 0x%02x\n", cfg_pin);
		वापस;
	पूर्ण

	led_change = bnx2x_analyze_link_error(params, vars, value,
					      PHY_SFP_TX_FAULT_FLAG,
					      LINK_STATUS_SFP_TX_FAULT, 1);

	अगर (led_change) अणु
		/* Change TX_Fault led, set link status क्रम further syncs */
		u8 led_mode;

		अगर (vars->phy_flags & PHY_SFP_TX_FAULT_FLAG) अणु
			led_mode = MISC_REGISTERS_GPIO_HIGH;
			vars->link_status |= LINK_STATUS_SFP_TX_FAULT;
		पूर्ण अन्यथा अणु
			led_mode = MISC_REGISTERS_GPIO_LOW;
			vars->link_status &= ~LINK_STATUS_SFP_TX_FAULT;
		पूर्ण

		/* If module is unapproved, led should be on regardless */
		अगर (!(phy->flags & FLAGS_SFP_NOT_APPROVED)) अणु
			DP(NETIF_MSG_LINK, "Change TX_Fault LED: ->%x\n",
			   led_mode);
			bnx2x_set_e3_module_fault_led(params, led_mode);
		पूर्ण
	पूर्ण
पूर्ण
अटल व्योम bnx2x_kr2_recovery(काष्ठा link_params *params,
			       काष्ठा link_vars *vars,
			       काष्ठा bnx2x_phy *phy)
अणु
	काष्ठा bnx2x *bp = params->bp;
	DP(NETIF_MSG_LINK, "KR2 recovery\n");
	bnx2x_warpcore_enable_AN_KR2(phy, params, vars);
	bnx2x_warpcore_restart_AN_KR(phy, params);
पूर्ण

अटल व्योम bnx2x_check_kr2_wa(काष्ठा link_params *params,
			       काष्ठा link_vars *vars,
			       काष्ठा bnx2x_phy *phy)
अणु
	काष्ठा bnx2x *bp = params->bp;
	u16 base_page, next_page, not_kr2_device, lane;
	पूर्णांक sigdet;

	/* Once KR2 was disabled, रुको 5 seconds beक्रमe checking KR2 recovery
	 * Since some चयनes tend to reinit the AN process and clear the
	 * the advertised BP/NP after ~2 seconds causing the KR2 to be disabled
	 * and recovered many बार
	 */
	अगर (vars->check_kr2_recovery_cnt > 0) अणु
		vars->check_kr2_recovery_cnt--;
		वापस;
	पूर्ण

	sigdet = bnx2x_warpcore_get_sigdet(phy, params);
	अगर (!sigdet) अणु
		अगर (!(params->link_attr_sync & LINK_ATTR_SYNC_KR2_ENABLE)) अणु
			bnx2x_kr2_recovery(params, vars, phy);
			DP(NETIF_MSG_LINK, "No sigdet\n");
		पूर्ण
		वापस;
	पूर्ण

	lane = bnx2x_get_warpcore_lane(phy, params);
	CL22_WR_OVER_CL45(bp, phy, MDIO_REG_BANK_AER_BLOCK,
			  MDIO_AER_BLOCK_AER_REG, lane);
	bnx2x_cl45_पढ़ो(bp, phy, MDIO_AN_DEVAD,
			MDIO_AN_REG_LP_AUTO_NEG, &base_page);
	bnx2x_cl45_पढ़ो(bp, phy, MDIO_AN_DEVAD,
			MDIO_AN_REG_LP_AUTO_NEG2, &next_page);
	bnx2x_set_aer_mmd(params, phy);

	/* CL73 has not begun yet */
	अगर (base_page == 0) अणु
		अगर (!(params->link_attr_sync & LINK_ATTR_SYNC_KR2_ENABLE)) अणु
			bnx2x_kr2_recovery(params, vars, phy);
			DP(NETIF_MSG_LINK, "No BP\n");
		पूर्ण
		वापस;
	पूर्ण

	/* In हाल NP bit is not set in the BasePage, or it is set,
	 * but only KX is advertised, declare this link partner as non-KR2
	 * device.
	 */
	not_kr2_device = (((base_page & 0x8000) == 0) ||
			  (((base_page & 0x8000) &&
			    ((next_page & 0xe0) == 0x20))));

	/* In हाल KR2 is alपढ़ोy disabled, check अगर we need to re-enable it */
	अगर (!(params->link_attr_sync & LINK_ATTR_SYNC_KR2_ENABLE)) अणु
		अगर (!not_kr2_device) अणु
			DP(NETIF_MSG_LINK, "BP=0x%x, NP=0x%x\n", base_page,
			   next_page);
			bnx2x_kr2_recovery(params, vars, phy);
		पूर्ण
		वापस;
	पूर्ण
	/* KR2 is enabled, but not KR2 device */
	अगर (not_kr2_device) अणु
		/* Disable KR2 on both lanes */
		DP(NETIF_MSG_LINK, "BP=0x%x, NP=0x%x\n", base_page, next_page);
		bnx2x_disable_kr2(params, vars, phy);
		/* Restart AN on leading lane */
		bnx2x_warpcore_restart_AN_KR(phy, params);
		वापस;
	पूर्ण
पूर्ण

व्योम bnx2x_period_func(काष्ठा link_params *params, काष्ठा link_vars *vars)
अणु
	u16 phy_idx;
	काष्ठा bnx2x *bp = params->bp;
	क्रम (phy_idx = INT_PHY; phy_idx < MAX_PHYS; phy_idx++) अणु
		अगर (params->phy[phy_idx].flags & FLAGS_TX_ERROR_CHECK) अणु
			bnx2x_set_aer_mmd(params, &params->phy[phy_idx]);
			अगर (bnx2x_check_half_खोलो_conn(params, vars, 1) !=
			    0)
				DP(NETIF_MSG_LINK, "Fault detection failed\n");
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (CHIP_IS_E3(bp)) अणु
		काष्ठा bnx2x_phy *phy = &params->phy[INT_PHY];
		bnx2x_set_aer_mmd(params, phy);
		अगर (((phy->req_line_speed == SPEED_AUTO_NEG) &&
		     (phy->speed_cap_mask &
		      PORT_HW_CFG_SPEED_CAPABILITY_D0_20G)) ||
		    (phy->req_line_speed == SPEED_20000))
			bnx2x_check_kr2_wa(params, vars, phy);
		bnx2x_check_over_curr(params, vars);
		अगर (vars->rx_tx_asic_rst)
			bnx2x_warpcore_config_runसमय(phy, params, vars);

		अगर ((REG_RD(bp, params->shmem_base +
			    दुरत्व(काष्ठा shmem_region, dev_info.
				port_hw_config[params->port].शेष_cfg))
		    & PORT_HW_CFG_NET_SERDES_IF_MASK) ==
		    PORT_HW_CFG_NET_SERDES_IF_SFI) अणु
			अगर (bnx2x_is_sfp_module_plugged(phy, params)) अणु
				bnx2x_sfp_tx_fault_detection(phy, params, vars);
			पूर्ण अन्यथा अगर (vars->link_status &
				LINK_STATUS_SFP_TX_FAULT) अणु
				/* Clean trail, पूर्णांकerrupt corrects the leds */
				vars->link_status &= ~LINK_STATUS_SFP_TX_FAULT;
				vars->phy_flags &= ~PHY_SFP_TX_FAULT_FLAG;
				/* Update link status in the shared memory */
				bnx2x_update_mng(params, vars->link_status);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

u8 bnx2x_fan_failure_det_req(काष्ठा bnx2x *bp,
			     u32 shmem_base,
			     u32 shmem2_base,
			     u8 port)
अणु
	u8 phy_index, fan_failure_det_req = 0;
	काष्ठा bnx2x_phy phy;
	क्रम (phy_index = EXT_PHY1; phy_index < MAX_PHYS;
	      phy_index++) अणु
		अगर (bnx2x_populate_phy(bp, phy_index, shmem_base, shmem2_base,
				       port, &phy)
		    != 0) अणु
			DP(NETIF_MSG_LINK, "populate phy failed\n");
			वापस 0;
		पूर्ण
		fan_failure_det_req |= (phy.flags &
					FLAGS_FAN_FAILURE_DET_REQ);
	पूर्ण
	वापस fan_failure_det_req;
पूर्ण

व्योम bnx2x_hw_reset_phy(काष्ठा link_params *params)
अणु
	u8 phy_index;
	काष्ठा bnx2x *bp = params->bp;
	bnx2x_update_mng(params, 0);
	bnx2x_bits_dis(bp, NIG_REG_MASK_INTERRUPT_PORT0 + params->port*4,
		       (NIG_MASK_XGXS0_LINK_STATUS |
			NIG_MASK_XGXS0_LINK10G |
			NIG_MASK_SERDES0_LINK_STATUS |
			NIG_MASK_MI_INT));

	क्रम (phy_index = INT_PHY; phy_index < MAX_PHYS;
	      phy_index++) अणु
		अगर (params->phy[phy_index].hw_reset) अणु
			params->phy[phy_index].hw_reset(
				&params->phy[phy_index],
				params);
			params->phy[phy_index] = phy_null;
		पूर्ण
	पूर्ण
पूर्ण

व्योम bnx2x_init_mod_असल_पूर्णांक(काष्ठा bnx2x *bp, काष्ठा link_vars *vars,
			    u32 chip_id, u32 shmem_base, u32 shmem2_base,
			    u8 port)
अणु
	u8 gpio_num = 0xff, gpio_port = 0xff, phy_index;
	u32 val;
	u32 offset, aeu_mask, swap_val, swap_override, sync_offset;
	अगर (CHIP_IS_E3(bp)) अणु
		अगर (bnx2x_get_mod_असल_पूर्णांक_cfg(bp, chip_id,
					      shmem_base,
					      port,
					      &gpio_num,
					      &gpio_port) != 0)
			वापस;
	पूर्ण अन्यथा अणु
		काष्ठा bnx2x_phy phy;
		क्रम (phy_index = EXT_PHY1; phy_index < MAX_PHYS;
		      phy_index++) अणु
			अगर (bnx2x_populate_phy(bp, phy_index, shmem_base,
					       shmem2_base, port, &phy)
			    != 0) अणु
				DP(NETIF_MSG_LINK, "populate phy failed\n");
				वापस;
			पूर्ण
			अगर (phy.type == PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8726) अणु
				gpio_num = MISC_REGISTERS_GPIO_3;
				gpio_port = port;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (gpio_num == 0xff)
		वापस;

	/* Set GPIO3 to trigger SFP+ module insertion/removal */
	bnx2x_set_gpio(bp, gpio_num, MISC_REGISTERS_GPIO_INPUT_HI_Z, gpio_port);

	swap_val = REG_RD(bp, NIG_REG_PORT_SWAP);
	swap_override = REG_RD(bp, NIG_REG_STRAP_OVERRIDE);
	gpio_port ^= (swap_val && swap_override);

	vars->aeu_पूर्णांक_mask = AEU_INPUTS_ATTN_BITS_GPIO0_FUNCTION_0 <<
		(gpio_num + (gpio_port << 2));

	sync_offset = shmem_base +
		दुरत्व(काष्ठा shmem_region,
			 dev_info.port_hw_config[port].aeu_पूर्णांक_mask);
	REG_WR(bp, sync_offset, vars->aeu_पूर्णांक_mask);

	DP(NETIF_MSG_LINK, "Setting MOD_ABS (GPIO%d_P%d) AEU to 0x%x\n",
		       gpio_num, gpio_port, vars->aeu_पूर्णांक_mask);

	अगर (port == 0)
		offset = MISC_REG_AEU_ENABLE1_FUNC_0_OUT_0;
	अन्यथा
		offset = MISC_REG_AEU_ENABLE1_FUNC_1_OUT_0;

	/* Open appropriate AEU क्रम पूर्णांकerrupts */
	aeu_mask = REG_RD(bp, offset);
	aeu_mask |= vars->aeu_पूर्णांक_mask;
	REG_WR(bp, offset, aeu_mask);

	/* Enable the GPIO to trigger पूर्णांकerrupt */
	val = REG_RD(bp, MISC_REG_GPIO_EVENT_EN);
	val |= 1 << (gpio_num + (gpio_port << 2));
	REG_WR(bp, MISC_REG_GPIO_EVENT_EN, val);
पूर्ण
