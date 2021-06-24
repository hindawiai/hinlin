<शैली गुरु>
/* bnx2x_hsi.h: Qlogic Everest network driver.
 *
 * Copyright (c) 2007-2013 Broadcom Corporation
 * Copyright (c) 2014 QLogic Corporation
 * All rights reserved
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */
#अगर_अघोषित BNX2X_HSI_H
#घोषणा BNX2X_HSI_H

#समावेश "bnx2x_fw_defs.h"
#समावेश "bnx2x_mfw_req.h"

#घोषणा FW_ENCODE_32BIT_PATTERN         0x1e1e1e1e

काष्ठा license_key अणु
	u32 reserved[6];

	u32 max_iscsi_conn;
#घोषणा BNX2X_MAX_ISCSI_TRGT_CONN_MASK	0xFFFF
#घोषणा BNX2X_MAX_ISCSI_TRGT_CONN_SHIFT	0
#घोषणा BNX2X_MAX_ISCSI_INIT_CONN_MASK	0xFFFF0000
#घोषणा BNX2X_MAX_ISCSI_INIT_CONN_SHIFT	16

	u32 reserved_a;

	u32 max_fcoe_conn;
#घोषणा BNX2X_MAX_FCOE_TRGT_CONN_MASK	0xFFFF
#घोषणा BNX2X_MAX_FCOE_TRGT_CONN_SHIFT	0
#घोषणा BNX2X_MAX_FCOE_INIT_CONN_MASK	0xFFFF0000
#घोषणा BNX2X_MAX_FCOE_INIT_CONN_SHIFT	16

	u32 reserved_b[4];
पूर्ण;

/****************************************************************************
 * Shared HW configuration                                                  *
 ****************************************************************************/
#घोषणा PIN_CFG_NA                          0x00000000
#घोषणा PIN_CFG_GPIO0_P0                    0x00000001
#घोषणा PIN_CFG_GPIO1_P0                    0x00000002
#घोषणा PIN_CFG_GPIO2_P0                    0x00000003
#घोषणा PIN_CFG_GPIO3_P0                    0x00000004
#घोषणा PIN_CFG_GPIO0_P1                    0x00000005
#घोषणा PIN_CFG_GPIO1_P1                    0x00000006
#घोषणा PIN_CFG_GPIO2_P1                    0x00000007
#घोषणा PIN_CFG_GPIO3_P1                    0x00000008
#घोषणा PIN_CFG_EPIO0                       0x00000009
#घोषणा PIN_CFG_EPIO1                       0x0000000a
#घोषणा PIN_CFG_EPIO2                       0x0000000b
#घोषणा PIN_CFG_EPIO3                       0x0000000c
#घोषणा PIN_CFG_EPIO4                       0x0000000d
#घोषणा PIN_CFG_EPIO5                       0x0000000e
#घोषणा PIN_CFG_EPIO6                       0x0000000f
#घोषणा PIN_CFG_EPIO7                       0x00000010
#घोषणा PIN_CFG_EPIO8                       0x00000011
#घोषणा PIN_CFG_EPIO9                       0x00000012
#घोषणा PIN_CFG_EPIO10                      0x00000013
#घोषणा PIN_CFG_EPIO11                      0x00000014
#घोषणा PIN_CFG_EPIO12                      0x00000015
#घोषणा PIN_CFG_EPIO13                      0x00000016
#घोषणा PIN_CFG_EPIO14                      0x00000017
#घोषणा PIN_CFG_EPIO15                      0x00000018
#घोषणा PIN_CFG_EPIO16                      0x00000019
#घोषणा PIN_CFG_EPIO17                      0x0000001a
#घोषणा PIN_CFG_EPIO18                      0x0000001b
#घोषणा PIN_CFG_EPIO19                      0x0000001c
#घोषणा PIN_CFG_EPIO20                      0x0000001d
#घोषणा PIN_CFG_EPIO21                      0x0000001e
#घोषणा PIN_CFG_EPIO22                      0x0000001f
#घोषणा PIN_CFG_EPIO23                      0x00000020
#घोषणा PIN_CFG_EPIO24                      0x00000021
#घोषणा PIN_CFG_EPIO25                      0x00000022
#घोषणा PIN_CFG_EPIO26                      0x00000023
#घोषणा PIN_CFG_EPIO27                      0x00000024
#घोषणा PIN_CFG_EPIO28                      0x00000025
#घोषणा PIN_CFG_EPIO29                      0x00000026
#घोषणा PIN_CFG_EPIO30                      0x00000027
#घोषणा PIN_CFG_EPIO31                      0x00000028

/* EPIO definition */
#घोषणा EPIO_CFG_NA                         0x00000000
#घोषणा EPIO_CFG_EPIO0                      0x00000001
#घोषणा EPIO_CFG_EPIO1                      0x00000002
#घोषणा EPIO_CFG_EPIO2                      0x00000003
#घोषणा EPIO_CFG_EPIO3                      0x00000004
#घोषणा EPIO_CFG_EPIO4                      0x00000005
#घोषणा EPIO_CFG_EPIO5                      0x00000006
#घोषणा EPIO_CFG_EPIO6                      0x00000007
#घोषणा EPIO_CFG_EPIO7                      0x00000008
#घोषणा EPIO_CFG_EPIO8                      0x00000009
#घोषणा EPIO_CFG_EPIO9                      0x0000000a
#घोषणा EPIO_CFG_EPIO10                     0x0000000b
#घोषणा EPIO_CFG_EPIO11                     0x0000000c
#घोषणा EPIO_CFG_EPIO12                     0x0000000d
#घोषणा EPIO_CFG_EPIO13                     0x0000000e
#घोषणा EPIO_CFG_EPIO14                     0x0000000f
#घोषणा EPIO_CFG_EPIO15                     0x00000010
#घोषणा EPIO_CFG_EPIO16                     0x00000011
#घोषणा EPIO_CFG_EPIO17                     0x00000012
#घोषणा EPIO_CFG_EPIO18                     0x00000013
#घोषणा EPIO_CFG_EPIO19                     0x00000014
#घोषणा EPIO_CFG_EPIO20                     0x00000015
#घोषणा EPIO_CFG_EPIO21                     0x00000016
#घोषणा EPIO_CFG_EPIO22                     0x00000017
#घोषणा EPIO_CFG_EPIO23                     0x00000018
#घोषणा EPIO_CFG_EPIO24                     0x00000019
#घोषणा EPIO_CFG_EPIO25                     0x0000001a
#घोषणा EPIO_CFG_EPIO26                     0x0000001b
#घोषणा EPIO_CFG_EPIO27                     0x0000001c
#घोषणा EPIO_CFG_EPIO28                     0x0000001d
#घोषणा EPIO_CFG_EPIO29                     0x0000001e
#घोषणा EPIO_CFG_EPIO30                     0x0000001f
#घोषणा EPIO_CFG_EPIO31                     0x00000020

काष्ठा mac_addr अणु
	u32 upper;
	u32 lower;
पूर्ण;

काष्ठा shared_hw_cfg अणु			 /* NVRAM Offset */
	/* Up to 16 bytes of शून्य-terminated string */
	u8  part_num[16];		    /* 0x104 */

	u32 config;			/* 0x114 */
	#घोषणा SHARED_HW_CFG_MDIO_VOLTAGE_MASK             0x00000001
		#घोषणा SHARED_HW_CFG_MDIO_VOLTAGE_SHIFT             0
		#घोषणा SHARED_HW_CFG_MDIO_VOLTAGE_1_2V              0x00000000
		#घोषणा SHARED_HW_CFG_MDIO_VOLTAGE_2_5V              0x00000001
	#घोषणा SHARED_HW_CFG_MCP_RST_ON_CORE_RST_EN        0x00000002

	#घोषणा SHARED_HW_CFG_PORT_SWAP                     0x00000004

	#घोषणा SHARED_HW_CFG_BEACON_WOL_EN                 0x00000008

	#घोषणा SHARED_HW_CFG_PCIE_GEN3_DISABLED            0x00000000
	#घोषणा SHARED_HW_CFG_PCIE_GEN3_ENABLED             0x00000010

	#घोषणा SHARED_HW_CFG_MFW_SELECT_MASK               0x00000700
		#घोषणा SHARED_HW_CFG_MFW_SELECT_SHIFT               8
	/* Whatever MFW found in NVM
	   (अगर multiple found, priority order is: NC-SI, UMP, IPMI) */
		#घोषणा SHARED_HW_CFG_MFW_SELECT_DEFAULT             0x00000000
		#घोषणा SHARED_HW_CFG_MFW_SELECT_NC_SI               0x00000100
		#घोषणा SHARED_HW_CFG_MFW_SELECT_UMP                 0x00000200
		#घोषणा SHARED_HW_CFG_MFW_SELECT_IPMI                0x00000300
	/* Use SPIO4 as an arbiter between: 0-NC_SI, 1-IPMI
	  (can only be used when an add-in board, not BMC, pulls-करोwn SPIO4) */
		#घोषणा SHARED_HW_CFG_MFW_SELECT_SPIO4_NC_SI_IPMI    0x00000400
	/* Use SPIO4 as an arbiter between: 0-UMP, 1-IPMI
	  (can only be used when an add-in board, not BMC, pulls-करोwn SPIO4) */
		#घोषणा SHARED_HW_CFG_MFW_SELECT_SPIO4_UMP_IPMI      0x00000500
	/* Use SPIO4 as an arbiter between: 0-NC-SI, 1-UMP
	  (can only be used when an add-in board, not BMC, pulls-करोwn SPIO4) */
		#घोषणा SHARED_HW_CFG_MFW_SELECT_SPIO4_NC_SI_UMP     0x00000600

	#घोषणा SHARED_HW_CFG_LED_MODE_MASK                 0x000f0000
		#घोषणा SHARED_HW_CFG_LED_MODE_SHIFT                 16
		#घोषणा SHARED_HW_CFG_LED_MAC1                       0x00000000
		#घोषणा SHARED_HW_CFG_LED_PHY1                       0x00010000
		#घोषणा SHARED_HW_CFG_LED_PHY2                       0x00020000
		#घोषणा SHARED_HW_CFG_LED_PHY3                       0x00030000
		#घोषणा SHARED_HW_CFG_LED_MAC2                       0x00040000
		#घोषणा SHARED_HW_CFG_LED_PHY4                       0x00050000
		#घोषणा SHARED_HW_CFG_LED_PHY5                       0x00060000
		#घोषणा SHARED_HW_CFG_LED_PHY6                       0x00070000
		#घोषणा SHARED_HW_CFG_LED_MAC3                       0x00080000
		#घोषणा SHARED_HW_CFG_LED_PHY7                       0x00090000
		#घोषणा SHARED_HW_CFG_LED_PHY9                       0x000a0000
		#घोषणा SHARED_HW_CFG_LED_PHY11                      0x000b0000
		#घोषणा SHARED_HW_CFG_LED_MAC4                       0x000c0000
		#घोषणा SHARED_HW_CFG_LED_PHY8                       0x000d0000
		#घोषणा SHARED_HW_CFG_LED_EXTPHY1                    0x000e0000
		#घोषणा SHARED_HW_CFG_LED_EXTPHY2                    0x000f0000


	#घोषणा SHARED_HW_CFG_AN_ENABLE_MASK                0x3f000000
		#घोषणा SHARED_HW_CFG_AN_ENABLE_SHIFT                24
		#घोषणा SHARED_HW_CFG_AN_ENABLE_CL37                 0x01000000
		#घोषणा SHARED_HW_CFG_AN_ENABLE_CL73                 0x02000000
		#घोषणा SHARED_HW_CFG_AN_ENABLE_BAM                  0x04000000
		#घोषणा SHARED_HW_CFG_AN_ENABLE_PARALLEL_DETECTION   0x08000000
		#घोषणा SHARED_HW_CFG_AN_EN_SGMII_FIBER_AUTO_DETECT  0x10000000
		#घोषणा SHARED_HW_CFG_AN_ENABLE_REMOTE_PHY           0x20000000

	#घोषणा SHARED_HW_CFG_SRIOV_MASK                    0x40000000
		#घोषणा SHARED_HW_CFG_SRIOV_DISABLED                 0x00000000
		#घोषणा SHARED_HW_CFG_SRIOV_ENABLED                  0x40000000

	#घोषणा SHARED_HW_CFG_ATC_MASK                      0x80000000
		#घोषणा SHARED_HW_CFG_ATC_DISABLED                   0x00000000
		#घोषणा SHARED_HW_CFG_ATC_ENABLED                    0x80000000

	u32 config2;			    /* 0x118 */
	/* one समय स्वतः detect grace period (in sec) */
	#घोषणा SHARED_HW_CFG_GRACE_PERIOD_MASK             0x000000ff
	#घोषणा SHARED_HW_CFG_GRACE_PERIOD_SHIFT                     0

	#घोषणा SHARED_HW_CFG_PCIE_GEN2_ENABLED             0x00000100
	#घोषणा SHARED_HW_CFG_PCIE_GEN2_DISABLED            0x00000000

	/* The शेष value क्रम the core घड़ी is 250MHz and it is
	   achieved by setting the घड़ी change to 4 */
	#घोषणा SHARED_HW_CFG_CLOCK_CHANGE_MASK             0x00000e00
	#घोषणा SHARED_HW_CFG_CLOCK_CHANGE_SHIFT                     9

	#घोषणा SHARED_HW_CFG_SMBUS_TIMING_MASK             0x00001000
		#घोषणा SHARED_HW_CFG_SMBUS_TIMING_100KHZ            0x00000000
		#घोषणा SHARED_HW_CFG_SMBUS_TIMING_400KHZ            0x00001000

	#घोषणा SHARED_HW_CFG_HIDE_PORT1                    0x00002000

	#घोषणा SHARED_HW_CFG_WOL_CAPABLE_MASK              0x00004000
		#घोषणा SHARED_HW_CFG_WOL_CAPABLE_DISABLED           0x00000000
		#घोषणा SHARED_HW_CFG_WOL_CAPABLE_ENABLED            0x00004000

		/* Output low when PERST is निश्चितed */
	#घोषणा SHARED_HW_CFG_SPIO4_FOLLOW_PERST_MASK       0x00008000
		#घोषणा SHARED_HW_CFG_SPIO4_FOLLOW_PERST_DISABLED    0x00000000
		#घोषणा SHARED_HW_CFG_SPIO4_FOLLOW_PERST_ENABLED     0x00008000

	#घोषणा SHARED_HW_CFG_PCIE_GEN2_PREEMPHASIS_MASK    0x00070000
		#घोषणा SHARED_HW_CFG_PCIE_GEN2_PREEMPHASIS_SHIFT    16
		#घोषणा SHARED_HW_CFG_PCIE_GEN2_PREEMPHASIS_HW       0x00000000
		#घोषणा SHARED_HW_CFG_PCIE_GEN2_PREEMPHASIS_0DB      0x00010000
		#घोषणा SHARED_HW_CFG_PCIE_GEN2_PREEMPHASIS_3_5DB    0x00020000
		#घोषणा SHARED_HW_CFG_PCIE_GEN2_PREEMPHASIS_6_0DB    0x00030000

	/*  The fan failure mechanism is usually related to the PHY type
	      since the घातer consumption of the board is determined by the PHY.
	      Currently, fan is required क्रम most designs with SFX7101, BCM8727
	      and BCM8481. If a fan is not required क्रम a board which uses one
	      of those PHYs, this field should be set to "Disabled". If a fan is
	      required क्रम a dअगरferent PHY type, this option should be set to
	      "Enabled". The fan failure indication is expected on SPIO5 */
	#घोषणा SHARED_HW_CFG_FAN_FAILURE_MASK              0x00180000
		#घोषणा SHARED_HW_CFG_FAN_FAILURE_SHIFT              19
		#घोषणा SHARED_HW_CFG_FAN_FAILURE_PHY_TYPE           0x00000000
		#घोषणा SHARED_HW_CFG_FAN_FAILURE_DISABLED           0x00080000
		#घोषणा SHARED_HW_CFG_FAN_FAILURE_ENABLED            0x00100000

		/* ASPM Power Management support */
	#घोषणा SHARED_HW_CFG_ASPM_SUPPORT_MASK             0x00600000
		#घोषणा SHARED_HW_CFG_ASPM_SUPPORT_SHIFT             21
		#घोषणा SHARED_HW_CFG_ASPM_SUPPORT_L0S_L1_ENABLED    0x00000000
		#घोषणा SHARED_HW_CFG_ASPM_SUPPORT_L0S_DISABLED      0x00200000
		#घोषणा SHARED_HW_CFG_ASPM_SUPPORT_L1_DISABLED       0x00400000
		#घोषणा SHARED_HW_CFG_ASPM_SUPPORT_L0S_L1_DISABLED   0x00600000

	/* The value of PM_TL_IGNORE_REQS (bit0) in PCI रेजिस्टर
	   tl_control_0 (रेजिस्टर 0x2800) */
	#घोषणा SHARED_HW_CFG_PREVENT_L1_ENTRY_MASK         0x00800000
		#घोषणा SHARED_HW_CFG_PREVENT_L1_ENTRY_DISABLED      0x00000000
		#घोषणा SHARED_HW_CFG_PREVENT_L1_ENTRY_ENABLED       0x00800000

	#घोषणा SHARED_HW_CFG_PORT_MODE_MASK                0x01000000
		#घोषणा SHARED_HW_CFG_PORT_MODE_2                    0x00000000
		#घोषणा SHARED_HW_CFG_PORT_MODE_4                    0x01000000

	#घोषणा SHARED_HW_CFG_PATH_SWAP_MASK                0x02000000
		#घोषणा SHARED_HW_CFG_PATH_SWAP_DISABLED             0x00000000
		#घोषणा SHARED_HW_CFG_PATH_SWAP_ENABLED              0x02000000

	/*  Set the MDC/MDIO access क्रम the first बाह्यal phy */
	#घोषणा SHARED_HW_CFG_MDC_MDIO_ACCESS1_MASK         0x1C000000
		#घोषणा SHARED_HW_CFG_MDC_MDIO_ACCESS1_SHIFT         26
		#घोषणा SHARED_HW_CFG_MDC_MDIO_ACCESS1_PHY_TYPE      0x00000000
		#घोषणा SHARED_HW_CFG_MDC_MDIO_ACCESS1_EMAC0         0x04000000
		#घोषणा SHARED_HW_CFG_MDC_MDIO_ACCESS1_EMAC1         0x08000000
		#घोषणा SHARED_HW_CFG_MDC_MDIO_ACCESS1_BOTH          0x0c000000
		#घोषणा SHARED_HW_CFG_MDC_MDIO_ACCESS1_SWAPPED       0x10000000

	/*  Set the MDC/MDIO access क्रम the second बाह्यal phy */
	#घोषणा SHARED_HW_CFG_MDC_MDIO_ACCESS2_MASK         0xE0000000
		#घोषणा SHARED_HW_CFG_MDC_MDIO_ACCESS2_SHIFT         29
		#घोषणा SHARED_HW_CFG_MDC_MDIO_ACCESS2_PHY_TYPE      0x00000000
		#घोषणा SHARED_HW_CFG_MDC_MDIO_ACCESS2_EMAC0         0x20000000
		#घोषणा SHARED_HW_CFG_MDC_MDIO_ACCESS2_EMAC1         0x40000000
		#घोषणा SHARED_HW_CFG_MDC_MDIO_ACCESS2_BOTH          0x60000000
		#घोषणा SHARED_HW_CFG_MDC_MDIO_ACCESS2_SWAPPED       0x80000000

	u32 config_3;				/* 0x11C */
	#घोषणा SHARED_HW_CFG_EXTENDED_MF_MODE_MASK         0x00000F00
		#घोषणा SHARED_HW_CFG_EXTENDED_MF_MODE_SHIFT              8
		#घोषणा SHARED_HW_CFG_EXTENDED_MF_MODE_NPAR1_DOT_5        0x00000000
		#घोषणा SHARED_HW_CFG_EXTENDED_MF_MODE_NPAR2_DOT_0        0x00000100

	u32 ump_nc_si_config;			/* 0x120 */
	#घोषणा SHARED_HW_CFG_UMP_NC_SI_MII_MODE_MASK       0x00000003
		#घोषणा SHARED_HW_CFG_UMP_NC_SI_MII_MODE_SHIFT       0
		#घोषणा SHARED_HW_CFG_UMP_NC_SI_MII_MODE_MAC         0x00000000
		#घोषणा SHARED_HW_CFG_UMP_NC_SI_MII_MODE_PHY         0x00000001
		#घोषणा SHARED_HW_CFG_UMP_NC_SI_MII_MODE_MII         0x00000000
		#घोषणा SHARED_HW_CFG_UMP_NC_SI_MII_MODE_RMII        0x00000002

	#घोषणा SHARED_HW_CFG_UMP_NC_SI_NUM_DEVS_MASK       0x00000f00
		#घोषणा SHARED_HW_CFG_UMP_NC_SI_NUM_DEVS_SHIFT       8

	#घोषणा SHARED_HW_CFG_UMP_NC_SI_EXT_PHY_TYPE_MASK   0x00ff0000
		#घोषणा SHARED_HW_CFG_UMP_NC_SI_EXT_PHY_TYPE_SHIFT   16
		#घोषणा SHARED_HW_CFG_UMP_NC_SI_EXT_PHY_TYPE_NONE    0x00000000
		#घोषणा SHARED_HW_CFG_UMP_NC_SI_EXT_PHY_TYPE_BCM5221 0x00010000

	u32 board;			/* 0x124 */
	#घोषणा SHARED_HW_CFG_E3_I2C_MUX0_MASK              0x0000003F
	#घोषणा SHARED_HW_CFG_E3_I2C_MUX0_SHIFT                      0
	#घोषणा SHARED_HW_CFG_E3_I2C_MUX1_MASK              0x00000FC0
	#घोषणा SHARED_HW_CFG_E3_I2C_MUX1_SHIFT                      6
	/* Use the PIN_CFG_XXX defines on top */
	#घोषणा SHARED_HW_CFG_BOARD_REV_MASK                0x00ff0000
	#घोषणा SHARED_HW_CFG_BOARD_REV_SHIFT                        16

	#घोषणा SHARED_HW_CFG_BOARD_MAJOR_VER_MASK          0x0f000000
	#घोषणा SHARED_HW_CFG_BOARD_MAJOR_VER_SHIFT                  24

	#घोषणा SHARED_HW_CFG_BOARD_MINOR_VER_MASK          0xf0000000
	#घोषणा SHARED_HW_CFG_BOARD_MINOR_VER_SHIFT                  28

	u32 wc_lane_config;				    /* 0x128 */
	#घोषणा SHARED_HW_CFG_LANE_SWAP_CFG_MASK            0x0000FFFF
		#घोषणा SHARED_HW_CFG_LANE_SWAP_CFG_SHIFT            0
		#घोषणा SHARED_HW_CFG_LANE_SWAP_CFG_32103210         0x00001b1b
		#घोषणा SHARED_HW_CFG_LANE_SWAP_CFG_32100123         0x00001be4
		#घोषणा SHARED_HW_CFG_LANE_SWAP_CFG_01233210         0x0000e41b
		#घोषणा SHARED_HW_CFG_LANE_SWAP_CFG_01230123         0x0000e4e4
	#घोषणा SHARED_HW_CFG_LANE_SWAP_CFG_TX_MASK         0x000000FF
	#घोषणा SHARED_HW_CFG_LANE_SWAP_CFG_TX_SHIFT                 0
	#घोषणा SHARED_HW_CFG_LANE_SWAP_CFG_RX_MASK         0x0000FF00
	#घोषणा SHARED_HW_CFG_LANE_SWAP_CFG_RX_SHIFT                 8

	/* TX lane Polarity swap */
	#घोषणा SHARED_HW_CFG_TX_LANE0_POL_FLIP_ENABLED     0x00010000
	#घोषणा SHARED_HW_CFG_TX_LANE1_POL_FLIP_ENABLED     0x00020000
	#घोषणा SHARED_HW_CFG_TX_LANE2_POL_FLIP_ENABLED     0x00040000
	#घोषणा SHARED_HW_CFG_TX_LANE3_POL_FLIP_ENABLED     0x00080000
	/* TX lane Polarity swap */
	#घोषणा SHARED_HW_CFG_RX_LANE0_POL_FLIP_ENABLED     0x00100000
	#घोषणा SHARED_HW_CFG_RX_LANE1_POL_FLIP_ENABLED     0x00200000
	#घोषणा SHARED_HW_CFG_RX_LANE2_POL_FLIP_ENABLED     0x00400000
	#घोषणा SHARED_HW_CFG_RX_LANE3_POL_FLIP_ENABLED     0x00800000

	/*  Selects the port layout of the board */
	#घोषणा SHARED_HW_CFG_E3_PORT_LAYOUT_MASK           0x0F000000
		#घोषणा SHARED_HW_CFG_E3_PORT_LAYOUT_SHIFT           24
		#घोषणा SHARED_HW_CFG_E3_PORT_LAYOUT_2P_01           0x00000000
		#घोषणा SHARED_HW_CFG_E3_PORT_LAYOUT_2P_10           0x01000000
		#घोषणा SHARED_HW_CFG_E3_PORT_LAYOUT_4P_0123         0x02000000
		#घोषणा SHARED_HW_CFG_E3_PORT_LAYOUT_4P_1032         0x03000000
		#घोषणा SHARED_HW_CFG_E3_PORT_LAYOUT_4P_2301         0x04000000
		#घोषणा SHARED_HW_CFG_E3_PORT_LAYOUT_4P_3210         0x05000000
पूर्ण;


/****************************************************************************
 * Port HW configuration                                                    *
 ****************************************************************************/
काष्ठा port_hw_cfg अणु		    /* port 0: 0x12c  port 1: 0x2bc */

	u32 pci_id;
	#घोषणा PORT_HW_CFG_PCI_VENDOR_ID_MASK              0xffff0000
	#घोषणा PORT_HW_CFG_PCI_DEVICE_ID_MASK              0x0000ffff

	u32 pci_sub_id;
	#घोषणा PORT_HW_CFG_PCI_SUBSYS_DEVICE_ID_MASK       0xffff0000
	#घोषणा PORT_HW_CFG_PCI_SUBSYS_VENDOR_ID_MASK       0x0000ffff

	u32 घातer_dissipated;
	#घोषणा PORT_HW_CFG_POWER_DIS_D0_MASK               0x000000ff
	#घोषणा PORT_HW_CFG_POWER_DIS_D0_SHIFT                       0
	#घोषणा PORT_HW_CFG_POWER_DIS_D1_MASK               0x0000ff00
	#घोषणा PORT_HW_CFG_POWER_DIS_D1_SHIFT                       8
	#घोषणा PORT_HW_CFG_POWER_DIS_D2_MASK               0x00ff0000
	#घोषणा PORT_HW_CFG_POWER_DIS_D2_SHIFT                       16
	#घोषणा PORT_HW_CFG_POWER_DIS_D3_MASK               0xff000000
	#घोषणा PORT_HW_CFG_POWER_DIS_D3_SHIFT                       24

	u32 घातer_consumed;
	#घोषणा PORT_HW_CFG_POWER_CONS_D0_MASK              0x000000ff
	#घोषणा PORT_HW_CFG_POWER_CONS_D0_SHIFT                      0
	#घोषणा PORT_HW_CFG_POWER_CONS_D1_MASK              0x0000ff00
	#घोषणा PORT_HW_CFG_POWER_CONS_D1_SHIFT                      8
	#घोषणा PORT_HW_CFG_POWER_CONS_D2_MASK              0x00ff0000
	#घोषणा PORT_HW_CFG_POWER_CONS_D2_SHIFT                      16
	#घोषणा PORT_HW_CFG_POWER_CONS_D3_MASK              0xff000000
	#घोषणा PORT_HW_CFG_POWER_CONS_D3_SHIFT                      24

	u32 mac_upper;
	#घोषणा PORT_HW_CFG_UPPERMAC_MASK                   0x0000ffff
	#घोषणा PORT_HW_CFG_UPPERMAC_SHIFT                           0
	u32 mac_lower;

	u32 iscsi_mac_upper;  /* Upper 16 bits are always zeroes */
	u32 iscsi_mac_lower;

	u32 rdma_mac_upper;   /* Upper 16 bits are always zeroes */
	u32 rdma_mac_lower;

	u32 serdes_config;
	#घोषणा PORT_HW_CFG_SERDES_TX_DRV_PRE_EMPHASIS_MASK 0x0000ffff
	#घोषणा PORT_HW_CFG_SERDES_TX_DRV_PRE_EMPHASIS_SHIFT         0

	#घोषणा PORT_HW_CFG_SERDES_RX_DRV_EQUALIZER_MASK    0xffff0000
	#घोषणा PORT_HW_CFG_SERDES_RX_DRV_EQUALIZER_SHIFT            16


	/*  Default values: 2P-64, 4P-32 */
	u32 pf_config;					    /* 0x158 */
	#घोषणा PORT_HW_CFG_PF_NUM_VF_MASK                  0x0000007F
	#घोषणा PORT_HW_CFG_PF_NUM_VF_SHIFT                          0

	/*  Default values: 17 */
	#घोषणा PORT_HW_CFG_PF_NUM_MSIX_VECTORS_MASK        0x00007F00
	#घोषणा PORT_HW_CFG_PF_NUM_MSIX_VECTORS_SHIFT                8

	#घोषणा PORT_HW_CFG_ENABLE_FLR_MASK                 0x00010000
	#घोषणा PORT_HW_CFG_FLR_ENABLED                     0x00010000

	u32 vf_config;					    /* 0x15C */
	#घोषणा PORT_HW_CFG_VF_NUM_MSIX_VECTORS_MASK        0x0000007F
	#घोषणा PORT_HW_CFG_VF_NUM_MSIX_VECTORS_SHIFT                0

	#घोषणा PORT_HW_CFG_VF_PCI_DEVICE_ID_MASK           0xFFFF0000
	#घोषणा PORT_HW_CFG_VF_PCI_DEVICE_ID_SHIFT                   16

	u32 mf_pci_id;					    /* 0x160 */
	#घोषणा PORT_HW_CFG_MF_PCI_DEVICE_ID_MASK           0x0000FFFF
	#घोषणा PORT_HW_CFG_MF_PCI_DEVICE_ID_SHIFT                   0

	/*  Controls the TX laser of the SFP+ module */
	u32 sfp_ctrl;					    /* 0x164 */
	#घोषणा PORT_HW_CFG_TX_LASER_MASK                   0x000000FF
		#घोषणा PORT_HW_CFG_TX_LASER_SHIFT                   0
		#घोषणा PORT_HW_CFG_TX_LASER_MDIO                    0x00000000
		#घोषणा PORT_HW_CFG_TX_LASER_GPIO0                   0x00000001
		#घोषणा PORT_HW_CFG_TX_LASER_GPIO1                   0x00000002
		#घोषणा PORT_HW_CFG_TX_LASER_GPIO2                   0x00000003
		#घोषणा PORT_HW_CFG_TX_LASER_GPIO3                   0x00000004

	/*  Controls the fault module LED of the SFP+ */
	#घोषणा PORT_HW_CFG_FAULT_MODULE_LED_MASK           0x0000FF00
		#घोषणा PORT_HW_CFG_FAULT_MODULE_LED_SHIFT           8
		#घोषणा PORT_HW_CFG_FAULT_MODULE_LED_GPIO0           0x00000000
		#घोषणा PORT_HW_CFG_FAULT_MODULE_LED_GPIO1           0x00000100
		#घोषणा PORT_HW_CFG_FAULT_MODULE_LED_GPIO2           0x00000200
		#घोषणा PORT_HW_CFG_FAULT_MODULE_LED_GPIO3           0x00000300
		#घोषणा PORT_HW_CFG_FAULT_MODULE_LED_DISABLED        0x00000400

	/*  The output pin TX_DIS that controls the TX laser of the SFP+
	  module. Use the PIN_CFG_XXX defines on top */
	u32 e3_sfp_ctrl;				    /* 0x168 */
	#घोषणा PORT_HW_CFG_E3_TX_LASER_MASK                0x000000FF
	#घोषणा PORT_HW_CFG_E3_TX_LASER_SHIFT                        0

	/*  The output pin क्रम SFPP_TYPE which turns on the Fault module LED */
	#घोषणा PORT_HW_CFG_E3_FAULT_MDL_LED_MASK           0x0000FF00
	#घोषणा PORT_HW_CFG_E3_FAULT_MDL_LED_SHIFT                   8

	/*  The input pin MOD_ABS that indicates whether SFP+ module is
	  present or not. Use the PIN_CFG_XXX defines on top */
	#घोषणा PORT_HW_CFG_E3_MOD_ABS_MASK                 0x00FF0000
	#घोषणा PORT_HW_CFG_E3_MOD_ABS_SHIFT                         16

	/*  The output pin PWRDIS_SFP_X which disable the घातer of the SFP+
	  module. Use the PIN_CFG_XXX defines on top */
	#घोषणा PORT_HW_CFG_E3_PWR_DIS_MASK                 0xFF000000
	#घोषणा PORT_HW_CFG_E3_PWR_DIS_SHIFT                         24

	/*
	 * The input pin which संकेतs module transmit fault. Use the
	 * PIN_CFG_XXX defines on top
	 */
	u32 e3_cmn_pin_cfg;				    /* 0x16C */
	#घोषणा PORT_HW_CFG_E3_TX_FAULT_MASK                0x000000FF
	#घोषणा PORT_HW_CFG_E3_TX_FAULT_SHIFT                        0

	/*  The output pin which reset the PHY. Use the PIN_CFG_XXX defines on
	 top */
	#घोषणा PORT_HW_CFG_E3_PHY_RESET_MASK               0x0000FF00
	#घोषणा PORT_HW_CFG_E3_PHY_RESET_SHIFT                       8

	/*
	 * The output pin which घातers करोwn the PHY. Use the PIN_CFG_XXX
	 * defines on top
	 */
	#घोषणा PORT_HW_CFG_E3_PWR_DOWN_MASK                0x00FF0000
	#घोषणा PORT_HW_CFG_E3_PWR_DOWN_SHIFT                        16

	/*  The output pin values BSC_SEL which selects the I2C क्रम this port
	  in the I2C Mux */
	#घोषणा PORT_HW_CFG_E3_I2C_MUX0_MASK                0x01000000
	#घोषणा PORT_HW_CFG_E3_I2C_MUX1_MASK                0x02000000


	/*
	 * The input pin I_FAULT which indicate over-current has occurred.
	 * Use the PIN_CFG_XXX defines on top
	 */
	u32 e3_cmn_pin_cfg1;				    /* 0x170 */
	#घोषणा PORT_HW_CFG_E3_OVER_CURRENT_MASK            0x000000FF
	#घोषणा PORT_HW_CFG_E3_OVER_CURRENT_SHIFT                    0

	/*  छोड़ो on host ring */
	u32 generic_features;                               /* 0x174 */
	#घोषणा PORT_HW_CFG_PAUSE_ON_HOST_RING_MASK                   0x00000001
	#घोषणा PORT_HW_CFG_PAUSE_ON_HOST_RING_SHIFT                  0
	#घोषणा PORT_HW_CFG_PAUSE_ON_HOST_RING_DISABLED               0x00000000
	#घोषणा PORT_HW_CFG_PAUSE_ON_HOST_RING_ENABLED                0x00000001

	/* SFP+ Tx Equalization: NIC recommended and tested value is 0xBEB2
	 * LOM recommended and tested value is 0xBEB2. Using a dअगरferent
	 * value means using a value not tested by BRCM
	 */
	u32 sfi_tap_values;                                 /* 0x178 */
	#घोषणा PORT_HW_CFG_TX_EQUALIZATION_MASK                      0x0000FFFF
	#घोषणा PORT_HW_CFG_TX_EQUALIZATION_SHIFT                     0

	/* SFP+ Tx driver broadcast IDRIVER: NIC recommended and tested
	 * value is 0x2. LOM recommended and tested value is 0x2. Using a
	 * dअगरferent value means using a value not tested by BRCM
	 */
	#घोषणा PORT_HW_CFG_TX_DRV_BROADCAST_MASK                     0x000F0000
	#घोषणा PORT_HW_CFG_TX_DRV_BROADCAST_SHIFT                    16
	/*  Set non-शेष values क्रम TXFIR in SFP mode. */
	#घोषणा PORT_HW_CFG_TX_DRV_IFIR_MASK                          0x00F00000
	#घोषणा PORT_HW_CFG_TX_DRV_IFIR_SHIFT                         20

	/*  Set non-शेष values क्रम IPREDRIVER in SFP mode. */
	#घोषणा PORT_HW_CFG_TX_DRV_IPREDRIVER_MASK                    0x0F000000
	#घोषणा PORT_HW_CFG_TX_DRV_IPREDRIVER_SHIFT                   24

	/*  Set non-शेष values क्रम POST2 in SFP mode. */
	#घोषणा PORT_HW_CFG_TX_DRV_POST2_MASK                         0xF0000000
	#घोषणा PORT_HW_CFG_TX_DRV_POST2_SHIFT                        28

	u32 reserved0[5];				    /* 0x17c */

	u32 aeu_पूर्णांक_mask;				    /* 0x190 */

	u32 media_type;					    /* 0x194 */
	#घोषणा PORT_HW_CFG_MEDIA_TYPE_PHY0_MASK            0x000000FF
	#घोषणा PORT_HW_CFG_MEDIA_TYPE_PHY0_SHIFT                    0

	#घोषणा PORT_HW_CFG_MEDIA_TYPE_PHY1_MASK            0x0000FF00
	#घोषणा PORT_HW_CFG_MEDIA_TYPE_PHY1_SHIFT                    8

	#घोषणा PORT_HW_CFG_MEDIA_TYPE_PHY2_MASK            0x00FF0000
	#घोषणा PORT_HW_CFG_MEDIA_TYPE_PHY2_SHIFT                    16

	/*  4 बार 16 bits क्रम all 4 lanes. In हाल बाह्यal PHY is present
	      (not direct mode), those values will not take effect on the 4 XGXS
	      lanes. For some बाह्यal PHYs (such as 8706 and 8726) the values
	      will be used to configure the बाह्यal PHY  in those हालs, not
	      all 4 values are needed. */
	u16 xgxs_config_rx[4];			/* 0x198 */
	u16 xgxs_config_tx[4];			/* 0x1A0 */

	/* For storing FCOE mac on shared memory */
	u32 fcoe_fip_mac_upper;
	#घोषणा PORT_HW_CFG_FCOE_UPPERMAC_MASK              0x0000ffff
	#घोषणा PORT_HW_CFG_FCOE_UPPERMAC_SHIFT                      0
	u32 fcoe_fip_mac_lower;

	u32 fcoe_wwn_port_name_upper;
	u32 fcoe_wwn_port_name_lower;

	u32 fcoe_wwn_node_name_upper;
	u32 fcoe_wwn_node_name_lower;

	u32 Reserved1[49];				    /* 0x1C0 */

	/*  Enable RJ45 magjack pair swapping on 10GBase-T PHY (0=शेष),
	      84833 only */
	u32 xgbt_phy_cfg;				    /* 0x284 */
	#घोषणा PORT_HW_CFG_RJ45_PAIR_SWAP_MASK             0x000000FF
	#घोषणा PORT_HW_CFG_RJ45_PAIR_SWAP_SHIFT                     0

		u32 शेष_cfg;			    /* 0x288 */
	#घोषणा PORT_HW_CFG_GPIO0_CONFIG_MASK               0x00000003
		#घोषणा PORT_HW_CFG_GPIO0_CONFIG_SHIFT               0
		#घोषणा PORT_HW_CFG_GPIO0_CONFIG_NA                  0x00000000
		#घोषणा PORT_HW_CFG_GPIO0_CONFIG_LOW                 0x00000001
		#घोषणा PORT_HW_CFG_GPIO0_CONFIG_HIGH                0x00000002
		#घोषणा PORT_HW_CFG_GPIO0_CONFIG_INPUT               0x00000003

	#घोषणा PORT_HW_CFG_GPIO1_CONFIG_MASK               0x0000000C
		#घोषणा PORT_HW_CFG_GPIO1_CONFIG_SHIFT               2
		#घोषणा PORT_HW_CFG_GPIO1_CONFIG_NA                  0x00000000
		#घोषणा PORT_HW_CFG_GPIO1_CONFIG_LOW                 0x00000004
		#घोषणा PORT_HW_CFG_GPIO1_CONFIG_HIGH                0x00000008
		#घोषणा PORT_HW_CFG_GPIO1_CONFIG_INPUT               0x0000000c

	#घोषणा PORT_HW_CFG_GPIO2_CONFIG_MASK               0x00000030
		#घोषणा PORT_HW_CFG_GPIO2_CONFIG_SHIFT               4
		#घोषणा PORT_HW_CFG_GPIO2_CONFIG_NA                  0x00000000
		#घोषणा PORT_HW_CFG_GPIO2_CONFIG_LOW                 0x00000010
		#घोषणा PORT_HW_CFG_GPIO2_CONFIG_HIGH                0x00000020
		#घोषणा PORT_HW_CFG_GPIO2_CONFIG_INPUT               0x00000030

	#घोषणा PORT_HW_CFG_GPIO3_CONFIG_MASK               0x000000C0
		#घोषणा PORT_HW_CFG_GPIO3_CONFIG_SHIFT               6
		#घोषणा PORT_HW_CFG_GPIO3_CONFIG_NA                  0x00000000
		#घोषणा PORT_HW_CFG_GPIO3_CONFIG_LOW                 0x00000040
		#घोषणा PORT_HW_CFG_GPIO3_CONFIG_HIGH                0x00000080
		#घोषणा PORT_HW_CFG_GPIO3_CONFIG_INPUT               0x000000c0

	/*  When KR link is required to be set to क्रमce which is not
	      KR-compliant, this parameter determine what is the trigger क्रम it.
	      When GPIO is selected, low input will क्रमce the speed. Currently
	      शेष speed is 1G. In the future, it may be widen to select the
	      क्रमced speed in with another parameter. Note when क्रमce-1G is
	      enabled, it override option 56: Link Speed option. */
	#घोषणा PORT_HW_CFG_FORCE_KR_ENABLER_MASK           0x00000F00
		#घोषणा PORT_HW_CFG_FORCE_KR_ENABLER_SHIFT           8
		#घोषणा PORT_HW_CFG_FORCE_KR_ENABLER_NOT_FORCED      0x00000000
		#घोषणा PORT_HW_CFG_FORCE_KR_ENABLER_GPIO0_P0        0x00000100
		#घोषणा PORT_HW_CFG_FORCE_KR_ENABLER_GPIO1_P0        0x00000200
		#घोषणा PORT_HW_CFG_FORCE_KR_ENABLER_GPIO2_P0        0x00000300
		#घोषणा PORT_HW_CFG_FORCE_KR_ENABLER_GPIO3_P0        0x00000400
		#घोषणा PORT_HW_CFG_FORCE_KR_ENABLER_GPIO0_P1        0x00000500
		#घोषणा PORT_HW_CFG_FORCE_KR_ENABLER_GPIO1_P1        0x00000600
		#घोषणा PORT_HW_CFG_FORCE_KR_ENABLER_GPIO2_P1        0x00000700
		#घोषणा PORT_HW_CFG_FORCE_KR_ENABLER_GPIO3_P1        0x00000800
		#घोषणा PORT_HW_CFG_FORCE_KR_ENABLER_FORCED          0x00000900
	/*  Enable to determine with which GPIO to reset the बाह्यal phy */
	#घोषणा PORT_HW_CFG_EXT_PHY_GPIO_RST_MASK           0x000F0000
		#घोषणा PORT_HW_CFG_EXT_PHY_GPIO_RST_SHIFT           16
		#घोषणा PORT_HW_CFG_EXT_PHY_GPIO_RST_PHY_TYPE        0x00000000
		#घोषणा PORT_HW_CFG_EXT_PHY_GPIO_RST_GPIO0_P0        0x00010000
		#घोषणा PORT_HW_CFG_EXT_PHY_GPIO_RST_GPIO1_P0        0x00020000
		#घोषणा PORT_HW_CFG_EXT_PHY_GPIO_RST_GPIO2_P0        0x00030000
		#घोषणा PORT_HW_CFG_EXT_PHY_GPIO_RST_GPIO3_P0        0x00040000
		#घोषणा PORT_HW_CFG_EXT_PHY_GPIO_RST_GPIO0_P1        0x00050000
		#घोषणा PORT_HW_CFG_EXT_PHY_GPIO_RST_GPIO1_P1        0x00060000
		#घोषणा PORT_HW_CFG_EXT_PHY_GPIO_RST_GPIO2_P1        0x00070000
		#घोषणा PORT_HW_CFG_EXT_PHY_GPIO_RST_GPIO3_P1        0x00080000

	/*  Enable BAM on KR */
	#घोषणा PORT_HW_CFG_ENABLE_BAM_ON_KR_MASK           0x00100000
	#घोषणा PORT_HW_CFG_ENABLE_BAM_ON_KR_SHIFT                   20
	#घोषणा PORT_HW_CFG_ENABLE_BAM_ON_KR_DISABLED                0x00000000
	#घोषणा PORT_HW_CFG_ENABLE_BAM_ON_KR_ENABLED                 0x00100000

	/*  Enable Common Mode Sense */
	#घोषणा PORT_HW_CFG_ENABLE_CMS_MASK                 0x00200000
	#घोषणा PORT_HW_CFG_ENABLE_CMS_SHIFT                         21
	#घोषणा PORT_HW_CFG_ENABLE_CMS_DISABLED                      0x00000000
	#घोषणा PORT_HW_CFG_ENABLE_CMS_ENABLED                       0x00200000

	/*  Determine the Serdes electrical पूर्णांकerface   */
	#घोषणा PORT_HW_CFG_NET_SERDES_IF_MASK              0x0F000000
	#घोषणा PORT_HW_CFG_NET_SERDES_IF_SHIFT                      24
	#घोषणा PORT_HW_CFG_NET_SERDES_IF_SGMII                      0x00000000
	#घोषणा PORT_HW_CFG_NET_SERDES_IF_XFI                        0x01000000
	#घोषणा PORT_HW_CFG_NET_SERDES_IF_SFI                        0x02000000
	#घोषणा PORT_HW_CFG_NET_SERDES_IF_KR                         0x03000000
	#घोषणा PORT_HW_CFG_NET_SERDES_IF_DXGXS                      0x04000000
	#घोषणा PORT_HW_CFG_NET_SERDES_IF_KR2                        0x05000000


	u32 speed_capability_mask2;			    /* 0x28C */
	#घोषणा PORT_HW_CFG_SPEED_CAPABILITY2_D3_MASK       0x0000FFFF
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY2_D3_SHIFT       0
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY2_D3_10M_FULL    0x00000001
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY2_D3__           0x00000002
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY2_D3___          0x00000004
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY2_D3_100M_FULL   0x00000008
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY2_D3_1G          0x00000010
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY2_D3_2_DOT_5G    0x00000020
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY2_D3_10G         0x00000040
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY2_D3_20G         0x00000080

	#घोषणा PORT_HW_CFG_SPEED_CAPABILITY2_D0_MASK       0xFFFF0000
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY2_D0_SHIFT       16
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY2_D0_10M_FULL    0x00010000
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY2_D0__           0x00020000
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY2_D0___          0x00040000
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY2_D0_100M_FULL   0x00080000
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY2_D0_1G          0x00100000
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY2_D0_2_DOT_5G    0x00200000
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY2_D0_10G         0x00400000
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY2_D0_20G         0x00800000


	/*  In the हाल where two media types (e.g. copper and fiber) are
	      present and electrically active at the same समय, PHY Selection
	      will determine which of the two PHYs will be designated as the
	      Active PHY and used क्रम a connection to the network.  */
	u32 multi_phy_config;				    /* 0x290 */
	#घोषणा PORT_HW_CFG_PHY_SELECTION_MASK              0x00000007
		#घोषणा PORT_HW_CFG_PHY_SELECTION_SHIFT              0
		#घोषणा PORT_HW_CFG_PHY_SELECTION_HARDWARE_DEFAULT   0x00000000
		#घोषणा PORT_HW_CFG_PHY_SELECTION_FIRST_PHY          0x00000001
		#घोषणा PORT_HW_CFG_PHY_SELECTION_SECOND_PHY         0x00000002
		#घोषणा PORT_HW_CFG_PHY_SELECTION_FIRST_PHY_PRIORITY 0x00000003
		#घोषणा PORT_HW_CFG_PHY_SELECTION_SECOND_PHY_PRIORITY 0x00000004

	/*  When enabled, all second phy nvram parameters will be swapped
	      with the first phy parameters */
	#घोषणा PORT_HW_CFG_PHY_SWAPPED_MASK                0x00000008
		#घोषणा PORT_HW_CFG_PHY_SWAPPED_SHIFT                3
		#घोषणा PORT_HW_CFG_PHY_SWAPPED_DISABLED             0x00000000
		#घोषणा PORT_HW_CFG_PHY_SWAPPED_ENABLED              0x00000008


	/*  Address of the second बाह्यal phy */
	u32 बाह्यal_phy_config2;			    /* 0x294 */
	#घोषणा PORT_HW_CFG_XGXS_EXT_PHY2_ADDR_MASK         0x000000FF
	#घोषणा PORT_HW_CFG_XGXS_EXT_PHY2_ADDR_SHIFT                 0

	/*  The second XGXS बाह्यal PHY type */
	#घोषणा PORT_HW_CFG_XGXS_EXT_PHY2_TYPE_MASK         0x0000FF00
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY2_TYPE_SHIFT         8
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY2_TYPE_सूचीECT        0x00000000
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY2_TYPE_BCM8071       0x00000100
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY2_TYPE_BCM8072       0x00000200
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY2_TYPE_BCM8073       0x00000300
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY2_TYPE_BCM8705       0x00000400
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY2_TYPE_BCM8706       0x00000500
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY2_TYPE_BCM8726       0x00000600
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY2_TYPE_BCM8481       0x00000700
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY2_TYPE_SFX7101       0x00000800
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY2_TYPE_BCM8727       0x00000900
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY2_TYPE_BCM8727_NOC   0x00000a00
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY2_TYPE_BCM84823      0x00000b00
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY2_TYPE_BCM54640      0x00000c00
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY2_TYPE_BCM84833      0x00000d00
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY2_TYPE_BCM54618SE    0x00000e00
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY2_TYPE_BCM8722       0x00000f00
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY2_TYPE_BCM54616      0x00001000
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY2_TYPE_BCM84834      0x00001100
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY2_TYPE_BCM84858      0x00001200
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY2_TYPE_FAILURE       0x0000fd00
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY2_TYPE_NOT_CONN      0x0000ff00


	/*  4 बार 16 bits क्रम all 4 lanes. For some बाह्यal PHYs (such as
	      8706, 8726 and 8727) not all 4 values are needed. */
	u16 xgxs_config2_rx[4];				    /* 0x296 */
	u16 xgxs_config2_tx[4];				    /* 0x2A0 */

	u32 lane_config;
	#घोषणा PORT_HW_CFG_LANE_SWAP_CFG_MASK              0x0000ffff
		#घोषणा PORT_HW_CFG_LANE_SWAP_CFG_SHIFT              0
		/* AN and क्रमced */
		#घोषणा PORT_HW_CFG_LANE_SWAP_CFG_01230123           0x00001b1b
		/* क्रमced only */
		#घोषणा PORT_HW_CFG_LANE_SWAP_CFG_01233210           0x00001be4
		/* क्रमced only */
		#घोषणा PORT_HW_CFG_LANE_SWAP_CFG_31203120           0x0000d8d8
		/* क्रमced only */
		#घोषणा PORT_HW_CFG_LANE_SWAP_CFG_32103210           0x0000e4e4
	#घोषणा PORT_HW_CFG_LANE_SWAP_CFG_TX_MASK           0x000000ff
	#घोषणा PORT_HW_CFG_LANE_SWAP_CFG_TX_SHIFT                   0
	#घोषणा PORT_HW_CFG_LANE_SWAP_CFG_RX_MASK           0x0000ff00
	#घोषणा PORT_HW_CFG_LANE_SWAP_CFG_RX_SHIFT                   8
	#घोषणा PORT_HW_CFG_LANE_SWAP_CFG_MASTER_MASK       0x0000c000
	#घोषणा PORT_HW_CFG_LANE_SWAP_CFG_MASTER_SHIFT               14

	/*  Indicate whether to swap the बाह्यal phy polarity */
	#घोषणा PORT_HW_CFG_SWAP_PHY_POLARITY_MASK          0x00010000
		#घोषणा PORT_HW_CFG_SWAP_PHY_POLARITY_DISABLED       0x00000000
		#घोषणा PORT_HW_CFG_SWAP_PHY_POLARITY_ENABLED        0x00010000


	u32 बाह्यal_phy_config;
	#घोषणा PORT_HW_CFG_XGXS_EXT_PHY_ADDR_MASK          0x000000ff
	#घोषणा PORT_HW_CFG_XGXS_EXT_PHY_ADDR_SHIFT                  0

	#घोषणा PORT_HW_CFG_XGXS_EXT_PHY_TYPE_MASK          0x0000ff00
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY_TYPE_SHIFT          8
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY_TYPE_सूचीECT         0x00000000
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8071        0x00000100
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8072        0x00000200
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8073        0x00000300
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8705        0x00000400
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8706        0x00000500
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8726        0x00000600
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8481        0x00000700
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY_TYPE_SFX7101        0x00000800
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8727        0x00000900
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8727_NOC    0x00000a00
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84823       0x00000b00
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM54640       0x00000c00
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84833       0x00000d00
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM54618SE     0x00000e00
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8722        0x00000f00
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM54616       0x00001000
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84834       0x00001100
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84858       0x00001200
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY_TYPE_सूचीECT_WC      0x0000fc00
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY_TYPE_FAILURE        0x0000fd00
		#घोषणा PORT_HW_CFG_XGXS_EXT_PHY_TYPE_NOT_CONN       0x0000ff00

	#घोषणा PORT_HW_CFG_SERDES_EXT_PHY_ADDR_MASK        0x00ff0000
	#घोषणा PORT_HW_CFG_SERDES_EXT_PHY_ADDR_SHIFT                16

	#घोषणा PORT_HW_CFG_SERDES_EXT_PHY_TYPE_MASK        0xff000000
		#घोषणा PORT_HW_CFG_SERDES_EXT_PHY_TYPE_SHIFT        24
		#घोषणा PORT_HW_CFG_SERDES_EXT_PHY_TYPE_सूचीECT       0x00000000
		#घोषणा PORT_HW_CFG_SERDES_EXT_PHY_TYPE_BCM5482      0x01000000
		#घोषणा PORT_HW_CFG_SERDES_EXT_PHY_TYPE_सूचीECT_SD    0x02000000
		#घोषणा PORT_HW_CFG_SERDES_EXT_PHY_TYPE_NOT_CONN     0xff000000

	u32 speed_capability_mask;
	#घोषणा PORT_HW_CFG_SPEED_CAPABILITY_D3_MASK        0x0000ffff
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY_D3_SHIFT        0
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY_D3_10M_FULL     0x00000001
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY_D3_10M_HALF     0x00000002
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY_D3_100M_HALF    0x00000004
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY_D3_100M_FULL    0x00000008
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY_D3_1G           0x00000010
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY_D3_2_5G         0x00000020
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY_D3_10G          0x00000040
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY_D3_20G          0x00000080
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY_D3_RESERVED     0x0000f000

	#घोषणा PORT_HW_CFG_SPEED_CAPABILITY_D0_MASK        0xffff0000
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY_D0_SHIFT        16
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY_D0_10M_FULL     0x00010000
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY_D0_10M_HALF     0x00020000
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY_D0_100M_HALF    0x00040000
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY_D0_100M_FULL    0x00080000
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY_D0_1G           0x00100000
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY_D0_2_5G         0x00200000
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY_D0_10G          0x00400000
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY_D0_20G          0x00800000
		#घोषणा PORT_HW_CFG_SPEED_CAPABILITY_D0_RESERVED     0xf0000000

	/*  A place to hold the original MAC address as a backup */
	u32 backup_mac_upper;			/* 0x2B4 */
	u32 backup_mac_lower;			/* 0x2B8 */

पूर्ण;


/****************************************************************************
 * Shared Feature configuration                                             *
 ****************************************************************************/
काष्ठा shared_feat_cfg अणु		 /* NVRAM Offset */

	u32 config;			/* 0x450 */
	#घोषणा SHARED_FEATURE_BMC_ECHO_MODE_EN             0x00000001

	/* Use NVRAM values instead of HW शेष values */
	#घोषणा SHARED_FEAT_CFG_OVERRIDE_PREEMPHASIS_CFG_MASK \
							    0x00000002
		#घोषणा SHARED_FEAT_CFG_OVERRIDE_PREEMPHASIS_CFG_DISABLED \
								     0x00000000
		#घोषणा SHARED_FEAT_CFG_OVERRIDE_PREEMPHASIS_CFG_ENABLED \
								     0x00000002

	#घोषणा SHARED_FEAT_CFG_NCSI_ID_METHOD_MASK         0x00000008
		#घोषणा SHARED_FEAT_CFG_NCSI_ID_METHOD_SPIO          0x00000000
		#घोषणा SHARED_FEAT_CFG_NCSI_ID_METHOD_NVRAM         0x00000008

	#घोषणा SHARED_FEAT_CFG_NCSI_ID_MASK                0x00000030
	#घोषणा SHARED_FEAT_CFG_NCSI_ID_SHIFT                        4

	/*  Override the OTP back to single function mode. When using GPIO,
	      high means only SF, 0 is according to CLP configuration */
	#घोषणा SHARED_FEAT_CFG_FORCE_SF_MODE_MASK          0x00000700
		#घोषणा SHARED_FEAT_CFG_FORCE_SF_MODE_SHIFT          8
		#घोषणा SHARED_FEAT_CFG_FORCE_SF_MODE_MF_ALLOWED     0x00000000
		#घोषणा SHARED_FEAT_CFG_FORCE_SF_MODE_FORCED_SF      0x00000100
		#घोषणा SHARED_FEAT_CFG_FORCE_SF_MODE_SPIO4          0x00000200
		#घोषणा SHARED_FEAT_CFG_FORCE_SF_MODE_SWITCH_INDEPT  0x00000300
		#घोषणा SHARED_FEAT_CFG_FORCE_SF_MODE_AFEX_MODE      0x00000400
		#घोषणा SHARED_FEAT_CFG_FORCE_SF_MODE_BD_MODE        0x00000500
		#घोषणा SHARED_FEAT_CFG_FORCE_SF_MODE_UFP_MODE       0x00000600
		#घोषणा SHARED_FEAT_CFG_FORCE_SF_MODE_EXTENDED_MODE  0x00000700

	/* The पूर्णांकerval in seconds between sending LLDP packets. Set to zero
	   to disable the feature */
	#घोषणा SHARED_FEAT_CFG_LLDP_XMIT_INTERVAL_MASK     0x00ff0000
	#घोषणा SHARED_FEAT_CFG_LLDP_XMIT_INTERVAL_SHIFT             16

	/* The asचिन्हित device type ID क्रम LLDP usage */
	#घोषणा SHARED_FEAT_CFG_LLDP_DEVICE_TYPE_ID_MASK    0xff000000
	#घोषणा SHARED_FEAT_CFG_LLDP_DEVICE_TYPE_ID_SHIFT            24

पूर्ण;


/****************************************************************************
 * Port Feature configuration                                               *
 ****************************************************************************/
काष्ठा port_feat_cfg अणु		    /* port 0: 0x454  port 1: 0x4c8 */

	u32 config;
	#घोषणा PORT_FEATURE_BAR1_SIZE_MASK                 0x0000000f
		#घोषणा PORT_FEATURE_BAR1_SIZE_SHIFT                 0
		#घोषणा PORT_FEATURE_BAR1_SIZE_DISABLED              0x00000000
		#घोषणा PORT_FEATURE_BAR1_SIZE_64K                   0x00000001
		#घोषणा PORT_FEATURE_BAR1_SIZE_128K                  0x00000002
		#घोषणा PORT_FEATURE_BAR1_SIZE_256K                  0x00000003
		#घोषणा PORT_FEATURE_BAR1_SIZE_512K                  0x00000004
		#घोषणा PORT_FEATURE_BAR1_SIZE_1M                    0x00000005
		#घोषणा PORT_FEATURE_BAR1_SIZE_2M                    0x00000006
		#घोषणा PORT_FEATURE_BAR1_SIZE_4M                    0x00000007
		#घोषणा PORT_FEATURE_BAR1_SIZE_8M                    0x00000008
		#घोषणा PORT_FEATURE_BAR1_SIZE_16M                   0x00000009
		#घोषणा PORT_FEATURE_BAR1_SIZE_32M                   0x0000000a
		#घोषणा PORT_FEATURE_BAR1_SIZE_64M                   0x0000000b
		#घोषणा PORT_FEATURE_BAR1_SIZE_128M                  0x0000000c
		#घोषणा PORT_FEATURE_BAR1_SIZE_256M                  0x0000000d
		#घोषणा PORT_FEATURE_BAR1_SIZE_512M                  0x0000000e
		#घोषणा PORT_FEATURE_BAR1_SIZE_1G                    0x0000000f
	#घोषणा PORT_FEATURE_BAR2_SIZE_MASK                 0x000000f0
		#घोषणा PORT_FEATURE_BAR2_SIZE_SHIFT                 4
		#घोषणा PORT_FEATURE_BAR2_SIZE_DISABLED              0x00000000
		#घोषणा PORT_FEATURE_BAR2_SIZE_64K                   0x00000010
		#घोषणा PORT_FEATURE_BAR2_SIZE_128K                  0x00000020
		#घोषणा PORT_FEATURE_BAR2_SIZE_256K                  0x00000030
		#घोषणा PORT_FEATURE_BAR2_SIZE_512K                  0x00000040
		#घोषणा PORT_FEATURE_BAR2_SIZE_1M                    0x00000050
		#घोषणा PORT_FEATURE_BAR2_SIZE_2M                    0x00000060
		#घोषणा PORT_FEATURE_BAR2_SIZE_4M                    0x00000070
		#घोषणा PORT_FEATURE_BAR2_SIZE_8M                    0x00000080
		#घोषणा PORT_FEATURE_BAR2_SIZE_16M                   0x00000090
		#घोषणा PORT_FEATURE_BAR2_SIZE_32M                   0x000000a0
		#घोषणा PORT_FEATURE_BAR2_SIZE_64M                   0x000000b0
		#घोषणा PORT_FEATURE_BAR2_SIZE_128M                  0x000000c0
		#घोषणा PORT_FEATURE_BAR2_SIZE_256M                  0x000000d0
		#घोषणा PORT_FEATURE_BAR2_SIZE_512M                  0x000000e0
		#घोषणा PORT_FEATURE_BAR2_SIZE_1G                    0x000000f0

	#घोषणा PORT_FEAT_CFG_DCBX_MASK                     0x00000100
		#घोषणा PORT_FEAT_CFG_DCBX_DISABLED                  0x00000000
		#घोषणा PORT_FEAT_CFG_DCBX_ENABLED                   0x00000100

		#घोषणा PORT_FEAT_CFG_STORAGE_PERSONALITY_MASK        0x00000C00
		#घोषणा PORT_FEAT_CFG_STORAGE_PERSONALITY_FCOE        0x00000400
		#घोषणा PORT_FEAT_CFG_STORAGE_PERSONALITY_ISCSI       0x00000800

	#घोषणा PORT_FEATURE_EN_SIZE_MASK                   0x0f000000
	#घोषणा PORT_FEATURE_EN_SIZE_SHIFT                           24
	#घोषणा PORT_FEATURE_WOL_ENABLED                             0x01000000
	#घोषणा PORT_FEATURE_MBA_ENABLED                             0x02000000
	#घोषणा PORT_FEATURE_MFW_ENABLED                             0x04000000

	/* Advertise expansion ROM even अगर MBA is disabled */
	#घोषणा PORT_FEAT_CFG_FORCE_EXP_ROM_ADV_MASK        0x08000000
		#घोषणा PORT_FEAT_CFG_FORCE_EXP_ROM_ADV_DISABLED     0x00000000
		#घोषणा PORT_FEAT_CFG_FORCE_EXP_ROM_ADV_ENABLED      0x08000000

	/* Check the optic venकरोr via i2c against a list of approved modules
	   in a separate nvram image */
	#घोषणा PORT_FEAT_CFG_OPT_MDL_ENFRCMNT_MASK         0xe0000000
		#घोषणा PORT_FEAT_CFG_OPT_MDL_ENFRCMNT_SHIFT         29
		#घोषणा PORT_FEAT_CFG_OPT_MDL_ENFRCMNT_NO_ENFORCEMENT \
								     0x00000000
		#घोषणा PORT_FEAT_CFG_OPT_MDL_ENFRCMNT_DISABLE_TX_LASER \
								     0x20000000
		#घोषणा PORT_FEAT_CFG_OPT_MDL_ENFRCMNT_WARNING_MSG   0x40000000
		#घोषणा PORT_FEAT_CFG_OPT_MDL_ENFRCMNT_POWER_DOWN    0x60000000

	u32 wol_config;
	/* Default is used when driver sets to "auto" mode */
	#घोषणा PORT_FEATURE_WOL_DEFAULT_MASK               0x00000003
		#घोषणा PORT_FEATURE_WOL_DEFAULT_SHIFT               0
		#घोषणा PORT_FEATURE_WOL_DEFAULT_DISABLE             0x00000000
		#घोषणा PORT_FEATURE_WOL_DEFAULT_MAGIC               0x00000001
		#घोषणा PORT_FEATURE_WOL_DEFAULT_ACPI                0x00000002
		#घोषणा PORT_FEATURE_WOL_DEFAULT_MAGIC_AND_ACPI      0x00000003
	#घोषणा PORT_FEATURE_WOL_RES_PAUSE_CAP              0x00000004
	#घोषणा PORT_FEATURE_WOL_RES_ASYM_PAUSE_CAP         0x00000008
	#घोषणा PORT_FEATURE_WOL_ACPI_UPON_MGMT             0x00000010

	u32 mba_config;
	#घोषणा PORT_FEATURE_MBA_BOOT_AGENT_TYPE_MASK       0x00000007
		#घोषणा PORT_FEATURE_MBA_BOOT_AGENT_TYPE_SHIFT       0
		#घोषणा PORT_FEATURE_MBA_BOOT_AGENT_TYPE_PXE         0x00000000
		#घोषणा PORT_FEATURE_MBA_BOOT_AGENT_TYPE_RPL         0x00000001
		#घोषणा PORT_FEATURE_MBA_BOOT_AGENT_TYPE_BOOTP       0x00000002
		#घोषणा PORT_FEATURE_MBA_BOOT_AGENT_TYPE_ISCSIB      0x00000003
		#घोषणा PORT_FEATURE_MBA_BOOT_AGENT_TYPE_FCOE_BOOT   0x00000004
		#घोषणा PORT_FEATURE_MBA_BOOT_AGENT_TYPE_NONE        0x00000007

	#घोषणा PORT_FEATURE_MBA_BOOT_RETRY_MASK            0x00000038
	#घोषणा PORT_FEATURE_MBA_BOOT_RETRY_SHIFT                    3

	#घोषणा PORT_FEATURE_MBA_RES_PAUSE_CAP              0x00000100
	#घोषणा PORT_FEATURE_MBA_RES_ASYM_PAUSE_CAP         0x00000200
	#घोषणा PORT_FEATURE_MBA_SETUP_PROMPT_ENABLE        0x00000400
	#घोषणा PORT_FEATURE_MBA_HOTKEY_MASK                0x00000800
		#घोषणा PORT_FEATURE_MBA_HOTKEY_CTRL_S               0x00000000
		#घोषणा PORT_FEATURE_MBA_HOTKEY_CTRL_B               0x00000800
	#घोषणा PORT_FEATURE_MBA_EXP_ROM_SIZE_MASK          0x000ff000
		#घोषणा PORT_FEATURE_MBA_EXP_ROM_SIZE_SHIFT          12
		#घोषणा PORT_FEATURE_MBA_EXP_ROM_SIZE_DISABLED       0x00000000
		#घोषणा PORT_FEATURE_MBA_EXP_ROM_SIZE_2K             0x00001000
		#घोषणा PORT_FEATURE_MBA_EXP_ROM_SIZE_4K             0x00002000
		#घोषणा PORT_FEATURE_MBA_EXP_ROM_SIZE_8K             0x00003000
		#घोषणा PORT_FEATURE_MBA_EXP_ROM_SIZE_16K            0x00004000
		#घोषणा PORT_FEATURE_MBA_EXP_ROM_SIZE_32K            0x00005000
		#घोषणा PORT_FEATURE_MBA_EXP_ROM_SIZE_64K            0x00006000
		#घोषणा PORT_FEATURE_MBA_EXP_ROM_SIZE_128K           0x00007000
		#घोषणा PORT_FEATURE_MBA_EXP_ROM_SIZE_256K           0x00008000
		#घोषणा PORT_FEATURE_MBA_EXP_ROM_SIZE_512K           0x00009000
		#घोषणा PORT_FEATURE_MBA_EXP_ROM_SIZE_1M             0x0000a000
		#घोषणा PORT_FEATURE_MBA_EXP_ROM_SIZE_2M             0x0000b000
		#घोषणा PORT_FEATURE_MBA_EXP_ROM_SIZE_4M             0x0000c000
		#घोषणा PORT_FEATURE_MBA_EXP_ROM_SIZE_8M             0x0000d000
		#घोषणा PORT_FEATURE_MBA_EXP_ROM_SIZE_16M            0x0000e000
		#घोषणा PORT_FEATURE_MBA_EXP_ROM_SIZE_32M            0x0000f000
	#घोषणा PORT_FEATURE_MBA_MSG_TIMEOUT_MASK           0x00f00000
	#घोषणा PORT_FEATURE_MBA_MSG_TIMEOUT_SHIFT                   20
	#घोषणा PORT_FEATURE_MBA_BIOS_BOOTSTRAP_MASK        0x03000000
		#घोषणा PORT_FEATURE_MBA_BIOS_BOOTSTRAP_SHIFT        24
		#घोषणा PORT_FEATURE_MBA_BIOS_BOOTSTRAP_AUTO         0x00000000
		#घोषणा PORT_FEATURE_MBA_BIOS_BOOTSTRAP_BBS          0x01000000
		#घोषणा PORT_FEATURE_MBA_BIOS_BOOTSTRAP_INT18H       0x02000000
		#घोषणा PORT_FEATURE_MBA_BIOS_BOOTSTRAP_INT19H       0x03000000
	#घोषणा PORT_FEATURE_MBA_LINK_SPEED_MASK            0x3c000000
		#घोषणा PORT_FEATURE_MBA_LINK_SPEED_SHIFT            26
		#घोषणा PORT_FEATURE_MBA_LINK_SPEED_AUTO             0x00000000
		#घोषणा PORT_FEATURE_MBA_LINK_SPEED_10HD             0x04000000
		#घोषणा PORT_FEATURE_MBA_LINK_SPEED_10FD             0x08000000
		#घोषणा PORT_FEATURE_MBA_LINK_SPEED_100HD            0x0c000000
		#घोषणा PORT_FEATURE_MBA_LINK_SPEED_100FD            0x10000000
		#घोषणा PORT_FEATURE_MBA_LINK_SPEED_1GBPS            0x14000000
		#घोषणा PORT_FEATURE_MBA_LINK_SPEED_2_5GBPS          0x18000000
		#घोषणा PORT_FEATURE_MBA_LINK_SPEED_10GBPS_CX4       0x1c000000
		#घोषणा PORT_FEATURE_MBA_LINK_SPEED_20GBPS           0x20000000
	u32 bmc_config;
	#घोषणा PORT_FEATURE_BMC_LINK_OVERRIDE_MASK         0x00000001
		#घोषणा PORT_FEATURE_BMC_LINK_OVERRIDE_DEFAULT       0x00000000
		#घोषणा PORT_FEATURE_BMC_LINK_OVERRIDE_EN            0x00000001

	u32 mba_vlan_cfg;
	#घोषणा PORT_FEATURE_MBA_VLAN_TAG_MASK              0x0000ffff
	#घोषणा PORT_FEATURE_MBA_VLAN_TAG_SHIFT                      0
	#घोषणा PORT_FEATURE_MBA_VLAN_EN                    0x00010000

	u32 resource_cfg;
	#घोषणा PORT_FEATURE_RESOURCE_CFG_VALID             0x00000001
	#घोषणा PORT_FEATURE_RESOURCE_CFG_DIAG              0x00000002
	#घोषणा PORT_FEATURE_RESOURCE_CFG_L2                0x00000004
	#घोषणा PORT_FEATURE_RESOURCE_CFG_ISCSI             0x00000008
	#घोषणा PORT_FEATURE_RESOURCE_CFG_RDMA              0x00000010

	u32 smbus_config;
	#घोषणा PORT_FEATURE_SMBUS_ADDR_MASK                0x000000fe
	#घोषणा PORT_FEATURE_SMBUS_ADDR_SHIFT                        1

	u32 vf_config;
	#घोषणा PORT_FEAT_CFG_VF_BAR2_SIZE_MASK             0x0000000f
		#घोषणा PORT_FEAT_CFG_VF_BAR2_SIZE_SHIFT             0
		#घोषणा PORT_FEAT_CFG_VF_BAR2_SIZE_DISABLED          0x00000000
		#घोषणा PORT_FEAT_CFG_VF_BAR2_SIZE_4K                0x00000001
		#घोषणा PORT_FEAT_CFG_VF_BAR2_SIZE_8K                0x00000002
		#घोषणा PORT_FEAT_CFG_VF_BAR2_SIZE_16K               0x00000003
		#घोषणा PORT_FEAT_CFG_VF_BAR2_SIZE_32K               0x00000004
		#घोषणा PORT_FEAT_CFG_VF_BAR2_SIZE_64K               0x00000005
		#घोषणा PORT_FEAT_CFG_VF_BAR2_SIZE_128K              0x00000006
		#घोषणा PORT_FEAT_CFG_VF_BAR2_SIZE_256K              0x00000007
		#घोषणा PORT_FEAT_CFG_VF_BAR2_SIZE_512K              0x00000008
		#घोषणा PORT_FEAT_CFG_VF_BAR2_SIZE_1M                0x00000009
		#घोषणा PORT_FEAT_CFG_VF_BAR2_SIZE_2M                0x0000000a
		#घोषणा PORT_FEAT_CFG_VF_BAR2_SIZE_4M                0x0000000b
		#घोषणा PORT_FEAT_CFG_VF_BAR2_SIZE_8M                0x0000000c
		#घोषणा PORT_FEAT_CFG_VF_BAR2_SIZE_16M               0x0000000d
		#घोषणा PORT_FEAT_CFG_VF_BAR2_SIZE_32M               0x0000000e
		#घोषणा PORT_FEAT_CFG_VF_BAR2_SIZE_64M               0x0000000f

	u32 link_config;    /* Used as HW शेषs क्रम the driver */
	#घोषणा PORT_FEATURE_CONNECTED_SWITCH_MASK          0x03000000
		#घोषणा PORT_FEATURE_CONNECTED_SWITCH_SHIFT          24
		/* (क्रमced) low speed चयन (< 10G) */
		#घोषणा PORT_FEATURE_CON_SWITCH_1G_SWITCH            0x00000000
		/* (क्रमced) high speed चयन (>= 10G) */
		#घोषणा PORT_FEATURE_CON_SWITCH_10G_SWITCH           0x01000000
		#घोषणा PORT_FEATURE_CON_SWITCH_AUTO_DETECT          0x02000000
		#घोषणा PORT_FEATURE_CON_SWITCH_ONE_TIME_DETECT      0x03000000

	#घोषणा PORT_FEATURE_LINK_SPEED_MASK                0x000f0000
		#घोषणा PORT_FEATURE_LINK_SPEED_SHIFT                16
		#घोषणा PORT_FEATURE_LINK_SPEED_AUTO                 0x00000000
		#घोषणा PORT_FEATURE_LINK_SPEED_10M_FULL             0x00010000
		#घोषणा PORT_FEATURE_LINK_SPEED_10M_HALF             0x00020000
		#घोषणा PORT_FEATURE_LINK_SPEED_100M_HALF            0x00030000
		#घोषणा PORT_FEATURE_LINK_SPEED_100M_FULL            0x00040000
		#घोषणा PORT_FEATURE_LINK_SPEED_1G                   0x00050000
		#घोषणा PORT_FEATURE_LINK_SPEED_2_5G                 0x00060000
		#घोषणा PORT_FEATURE_LINK_SPEED_10G_CX4              0x00070000
		#घोषणा PORT_FEATURE_LINK_SPEED_20G                  0x00080000

	#घोषणा PORT_FEATURE_FLOW_CONTROL_MASK              0x00000700
		#घोषणा PORT_FEATURE_FLOW_CONTROL_SHIFT              8
		#घोषणा PORT_FEATURE_FLOW_CONTROL_AUTO               0x00000000
		#घोषणा PORT_FEATURE_FLOW_CONTROL_TX                 0x00000100
		#घोषणा PORT_FEATURE_FLOW_CONTROL_RX                 0x00000200
		#घोषणा PORT_FEATURE_FLOW_CONTROL_BOTH               0x00000300
		#घोषणा PORT_FEATURE_FLOW_CONTROL_NONE               0x00000400

	/* The शेष क्रम MCP link configuration,
	   uses the same defines as link_config */
	u32 mfw_wol_link_cfg;

	/* The शेष क्रम the driver of the second बाह्यal phy,
	   uses the same defines as link_config */
	u32 link_config2;				    /* 0x47C */

	/* The शेष क्रम MCP of the second बाह्यal phy,
	   uses the same defines as link_config */
	u32 mfw_wol_link_cfg2;				    /* 0x480 */


	/*  EEE घातer saving mode */
	u32 eee_घातer_mode;                                 /* 0x484 */
	#घोषणा PORT_FEAT_CFG_EEE_POWER_MODE_MASK                     0x000000FF
	#घोषणा PORT_FEAT_CFG_EEE_POWER_MODE_SHIFT                    0
	#घोषणा PORT_FEAT_CFG_EEE_POWER_MODE_DISABLED                 0x00000000
	#घोषणा PORT_FEAT_CFG_EEE_POWER_MODE_BALANCED                 0x00000001
	#घोषणा PORT_FEAT_CFG_EEE_POWER_MODE_AGGRESSIVE               0x00000002
	#घोषणा PORT_FEAT_CFG_EEE_POWER_MODE_LOW_LATENCY              0x00000003


	u32 Reserved2[16];                                  /* 0x488 */
पूर्ण;


/****************************************************************************
 * Device Inक्रमmation                                                       *
 ****************************************************************************/
काष्ठा shm_dev_info अणु				/* size */

	u32    bc_rev; /* 8 bits each: major, minor, build */	       /* 4 */

	काष्ठा shared_hw_cfg     shared_hw_config;	      /* 40 */

	काष्ठा port_hw_cfg       port_hw_config[PORT_MAX];     /* 400*2=800 */

	काष्ठा shared_feat_cfg   shared_feature_config;		   /* 4 */

	काष्ठा port_feat_cfg     port_feature_config[PORT_MAX];/* 116*2=232 */

पूर्ण;

काष्ठा extended_dev_info_shared_cfg अणु
	u32 reserved[18];
	u32 mbi_version;
	u32 mbi_date;
पूर्ण;

#अगर !defined(__LITTLE_ENDIAN) && !defined(__BIG_ENDIAN)
	#त्रुटि "Missing either LITTLE_ENDIAN or BIG_ENDIAN definition."
#पूर्ण_अगर

#घोषणा FUNC_0              0
#घोषणा FUNC_1              1
#घोषणा FUNC_2              2
#घोषणा FUNC_3              3
#घोषणा FUNC_4              4
#घोषणा FUNC_5              5
#घोषणा FUNC_6              6
#घोषणा FUNC_7              7
#घोषणा E1_FUNC_MAX         2
#घोषणा E1H_FUNC_MAX            8
#घोषणा E2_FUNC_MAX         4   /* per path */

#घोषणा VN_0                0
#घोषणा VN_1                1
#घोषणा VN_2                2
#घोषणा VN_3                3
#घोषणा E1VN_MAX            1
#घोषणा E1HVN_MAX           4

#घोषणा E2_VF_MAX           64  /* HC_REG_VF_CONFIGURATION_SIZE */
/* This value (in milliseconds) determines the frequency of the driver
 * issuing the PULSE message code.  The firmware monitors this periodic
 * pulse to determine when to चयन to an OS-असलent mode. */
#घोषणा DRV_PULSE_PERIOD_MS     250

/* This value (in milliseconds) determines how दीर्घ the driver should
 * रुको क्रम an acknowledgement from the firmware beक्रमe timing out.  Once
 * the firmware has समयd out, the driver will assume there is no firmware
 * running and there won't be any firmware-driver synchronization during a
 * driver reset. */
#घोषणा FW_ACK_TIME_OUT_MS      5000

#घोषणा FW_ACK_POLL_TIME_MS     1

#घोषणा FW_ACK_NUM_OF_POLL  (FW_ACK_TIME_OUT_MS/FW_ACK_POLL_TIME_MS)

#घोषणा MFW_TRACE_SIGNATURE     0x54524342

/****************************************************************************
 * Driver <-> FW Mailbox                                                    *
 ****************************************************************************/
काष्ठा drv_port_mb अणु

	u32 link_status;
	/* Driver should update this field on any link change event */

	#घोषणा LINK_STATUS_NONE				(0<<0)
	#घोषणा LINK_STATUS_LINK_FLAG_MASK			0x00000001
	#घोषणा LINK_STATUS_LINK_UP				0x00000001
	#घोषणा LINK_STATUS_SPEED_AND_DUPLEX_MASK		0x0000001E
	#घोषणा LINK_STATUS_SPEED_AND_DUPLEX_AN_NOT_COMPLETE	(0<<1)
	#घोषणा LINK_STATUS_SPEED_AND_DUPLEX_10THD		(1<<1)
	#घोषणा LINK_STATUS_SPEED_AND_DUPLEX_10TFD		(2<<1)
	#घोषणा LINK_STATUS_SPEED_AND_DUPLEX_100TXHD		(3<<1)
	#घोषणा LINK_STATUS_SPEED_AND_DUPLEX_100T4		(4<<1)
	#घोषणा LINK_STATUS_SPEED_AND_DUPLEX_100TXFD		(5<<1)
	#घोषणा LINK_STATUS_SPEED_AND_DUPLEX_1000THD		(6<<1)
	#घोषणा LINK_STATUS_SPEED_AND_DUPLEX_1000TFD		(7<<1)
	#घोषणा LINK_STATUS_SPEED_AND_DUPLEX_1000XFD		(7<<1)
	#घोषणा LINK_STATUS_SPEED_AND_DUPLEX_2500THD		(8<<1)
	#घोषणा LINK_STATUS_SPEED_AND_DUPLEX_2500TFD		(9<<1)
	#घोषणा LINK_STATUS_SPEED_AND_DUPLEX_2500XFD		(9<<1)
	#घोषणा LINK_STATUS_SPEED_AND_DUPLEX_10GTFD		(10<<1)
	#घोषणा LINK_STATUS_SPEED_AND_DUPLEX_10GXFD		(10<<1)
	#घोषणा LINK_STATUS_SPEED_AND_DUPLEX_20GTFD		(11<<1)
	#घोषणा LINK_STATUS_SPEED_AND_DUPLEX_20GXFD		(11<<1)

	#घोषणा LINK_STATUS_AUTO_NEGOTIATE_FLAG_MASK		0x00000020
	#घोषणा LINK_STATUS_AUTO_NEGOTIATE_ENABLED		0x00000020

	#घोषणा LINK_STATUS_AUTO_NEGOTIATE_COMPLETE		0x00000040
	#घोषणा LINK_STATUS_PARALLEL_DETECTION_FLAG_MASK	0x00000080
	#घोषणा LINK_STATUS_PARALLEL_DETECTION_USED		0x00000080

	#घोषणा LINK_STATUS_LINK_PARTNER_1000TFD_CAPABLE	0x00000200
	#घोषणा LINK_STATUS_LINK_PARTNER_1000THD_CAPABLE	0x00000400
	#घोषणा LINK_STATUS_LINK_PARTNER_100T4_CAPABLE		0x00000800
	#घोषणा LINK_STATUS_LINK_PARTNER_100TXFD_CAPABLE	0x00001000
	#घोषणा LINK_STATUS_LINK_PARTNER_100TXHD_CAPABLE	0x00002000
	#घोषणा LINK_STATUS_LINK_PARTNER_10TFD_CAPABLE		0x00004000
	#घोषणा LINK_STATUS_LINK_PARTNER_10THD_CAPABLE		0x00008000

	#घोषणा LINK_STATUS_TX_FLOW_CONTROL_FLAG_MASK		0x00010000
	#घोषणा LINK_STATUS_TX_FLOW_CONTROL_ENABLED		0x00010000

	#घोषणा LINK_STATUS_RX_FLOW_CONTROL_FLAG_MASK		0x00020000
	#घोषणा LINK_STATUS_RX_FLOW_CONTROL_ENABLED		0x00020000

	#घोषणा LINK_STATUS_LINK_PARTNER_FLOW_CONTROL_MASK	0x000C0000
	#घोषणा LINK_STATUS_LINK_PARTNER_NOT_PAUSE_CAPABLE	(0<<18)
	#घोषणा LINK_STATUS_LINK_PARTNER_SYMMETRIC_PAUSE	(1<<18)
	#घोषणा LINK_STATUS_LINK_PARTNER_ASYMMETRIC_PAUSE	(2<<18)
	#घोषणा LINK_STATUS_LINK_PARTNER_BOTH_PAUSE		(3<<18)

	#घोषणा LINK_STATUS_SERDES_LINK				0x00100000

	#घोषणा LINK_STATUS_LINK_PARTNER_2500XFD_CAPABLE	0x00200000
	#घोषणा LINK_STATUS_LINK_PARTNER_2500XHD_CAPABLE	0x00400000
	#घोषणा LINK_STATUS_LINK_PARTNER_10GXFD_CAPABLE		0x00800000
	#घोषणा LINK_STATUS_LINK_PARTNER_20GXFD_CAPABLE		0x10000000

	#घोषणा LINK_STATUS_PFC_ENABLED				0x20000000

	#घोषणा LINK_STATUS_PHYSICAL_LINK_FLAG			0x40000000
	#घोषणा LINK_STATUS_SFP_TX_FAULT			0x80000000

	u32 port_stx;

	u32 stat_nig_समयr;

	/* MCP firmware करोes not use this field */
	u32 ext_phy_fw_version;

पूर्ण;


काष्ठा drv_func_mb अणु

	u32 drv_mb_header;
	#घोषणा DRV_MSG_CODE_MASK                       0xffff0000
	#घोषणा DRV_MSG_CODE_LOAD_REQ                   0x10000000
	#घोषणा DRV_MSG_CODE_LOAD_DONE                  0x11000000
	#घोषणा DRV_MSG_CODE_UNLOAD_REQ_WOL_EN          0x20000000
	#घोषणा DRV_MSG_CODE_UNLOAD_REQ_WOL_DIS         0x20010000
	#घोषणा DRV_MSG_CODE_UNLOAD_REQ_WOL_MCP         0x20020000
	#घोषणा DRV_MSG_CODE_UNLOAD_DONE                0x21000000
	#घोषणा DRV_MSG_CODE_DCC_OK                     0x30000000
	#घोषणा DRV_MSG_CODE_DCC_FAILURE                0x31000000
	#घोषणा DRV_MSG_CODE_DIAG_ENTER_REQ             0x50000000
	#घोषणा DRV_MSG_CODE_DIAG_EXIT_REQ              0x60000000
	#घोषणा DRV_MSG_CODE_VALIDATE_KEY               0x70000000
	#घोषणा DRV_MSG_CODE_GET_CURR_KEY               0x80000000
	#घोषणा DRV_MSG_CODE_GET_UPGRADE_KEY            0x81000000
	#घोषणा DRV_MSG_CODE_GET_MANUF_KEY              0x82000000
	#घोषणा DRV_MSG_CODE_LOAD_L2B_PRAM              0x90000000
	#घोषणा DRV_MSG_CODE_OEM_OK			0x00010000
	#घोषणा DRV_MSG_CODE_OEM_FAILURE		0x00020000
	#घोषणा DRV_MSG_CODE_OEM_UPDATE_SVID_OK		0x00030000
	#घोषणा DRV_MSG_CODE_OEM_UPDATE_SVID_FAILURE	0x00040000
	/*
	 * The optic module verअगरication command requires bootcode
	 * v5.0.6 or later, te specअगरic optic module verअगरication command
	 * requires bootcode v5.2.12 or later
	 */
	#घोषणा DRV_MSG_CODE_VRFY_FIRST_PHY_OPT_MDL     0xa0000000
	#घोषणा REQ_BC_VER_4_VRFY_FIRST_PHY_OPT_MDL     0x00050006
	#घोषणा DRV_MSG_CODE_VRFY_SPECIFIC_PHY_OPT_MDL  0xa1000000
	#घोषणा REQ_BC_VER_4_VRFY_SPECIFIC_PHY_OPT_MDL  0x00050234
	#घोषणा DRV_MSG_CODE_VRFY_AFEX_SUPPORTED        0xa2000000
	#घोषणा REQ_BC_VER_4_VRFY_AFEX_SUPPORTED        0x00070002
	#घोषणा REQ_BC_VER_4_SFP_TX_DISABLE_SUPPORTED   0x00070014
	#घोषणा REQ_BC_VER_4_MT_SUPPORTED               0x00070201
	#घोषणा REQ_BC_VER_4_PFC_STATS_SUPPORTED        0x00070201
	#घोषणा REQ_BC_VER_4_FCOE_FEATURES              0x00070209

	#घोषणा DRV_MSG_CODE_DCBX_ADMIN_PMF_MSG         0xb0000000
	#घोषणा DRV_MSG_CODE_DCBX_PMF_DRV_OK            0xb2000000
	#घोषणा REQ_BC_VER_4_DCBX_ADMIN_MSG_NON_PMF     0x00070401

	#घोषणा DRV_MSG_CODE_VF_DISABLED_DONE           0xc0000000

	#घोषणा DRV_MSG_CODE_AFEX_DRIVER_SETMAC         0xd0000000
	#घोषणा DRV_MSG_CODE_AFEX_LISTGET_ACK           0xd1000000
	#घोषणा DRV_MSG_CODE_AFEX_LISTSET_ACK           0xd2000000
	#घोषणा DRV_MSG_CODE_AFEX_STATSGET_ACK          0xd3000000
	#घोषणा DRV_MSG_CODE_AFEX_VIFSET_ACK            0xd4000000

	#घोषणा DRV_MSG_CODE_DRV_INFO_ACK               0xd8000000
	#घोषणा DRV_MSG_CODE_DRV_INFO_NACK              0xd9000000

	#घोषणा DRV_MSG_CODE_EEE_RESULTS_ACK            0xda000000

	#घोषणा DRV_MSG_CODE_RMMOD                      0xdb000000
	#घोषणा REQ_BC_VER_4_RMMOD_CMD                  0x0007080f

	#घोषणा DRV_MSG_CODE_SET_MF_BW                  0xe0000000
	#घोषणा REQ_BC_VER_4_SET_MF_BW                  0x00060202
	#घोषणा DRV_MSG_CODE_SET_MF_BW_ACK              0xe1000000

	#घोषणा DRV_MSG_CODE_LINK_STATUS_CHANGED        0x01000000

	#घोषणा DRV_MSG_CODE_INITIATE_FLR               0x02000000
	#घोषणा REQ_BC_VER_4_INITIATE_FLR               0x00070213

	#घोषणा BIOS_MSG_CODE_LIC_CHALLENGE             0xff010000
	#घोषणा BIOS_MSG_CODE_LIC_RESPONSE              0xff020000
	#घोषणा BIOS_MSG_CODE_VIRT_MAC_PRIM             0xff030000
	#घोषणा BIOS_MSG_CODE_VIRT_MAC_ISCSI            0xff040000

	#घोषणा DRV_MSG_SEQ_NUMBER_MASK                 0x0000ffff

	u32 drv_mb_param;
	#घोषणा DRV_MSG_CODE_SET_MF_BW_MIN_MASK         0x00ff0000
	#घोषणा DRV_MSG_CODE_SET_MF_BW_MAX_MASK         0xff000000

	#घोषणा DRV_MSG_CODE_UNLOAD_SKIP_LINK_RESET     0x00000002

	#घोषणा DRV_MSG_CODE_LOAD_REQ_WITH_LFA          0x0000100a
	#घोषणा DRV_MSG_CODE_LOAD_REQ_FORCE_LFA         0x00002000

	u32 fw_mb_header;
	#घोषणा FW_MSG_CODE_MASK                        0xffff0000
	#घोषणा FW_MSG_CODE_DRV_LOAD_COMMON             0x10100000
	#घोषणा FW_MSG_CODE_DRV_LOAD_PORT               0x10110000
	#घोषणा FW_MSG_CODE_DRV_LOAD_FUNCTION           0x10120000
	/* Load common chip is supported from bc 6.0.0  */
	#घोषणा REQ_BC_VER_4_DRV_LOAD_COMMON_CHIP       0x00060000
	#घोषणा FW_MSG_CODE_DRV_LOAD_COMMON_CHIP        0x10130000

	#घोषणा FW_MSG_CODE_DRV_LOAD_REFUSED            0x10200000
	#घोषणा FW_MSG_CODE_DRV_LOAD_DONE               0x11100000
	#घोषणा FW_MSG_CODE_DRV_UNLOAD_COMMON           0x20100000
	#घोषणा FW_MSG_CODE_DRV_UNLOAD_PORT             0x20110000
	#घोषणा FW_MSG_CODE_DRV_UNLOAD_FUNCTION         0x20120000
	#घोषणा FW_MSG_CODE_DRV_UNLOAD_DONE             0x21100000
	#घोषणा FW_MSG_CODE_DCC_DONE                    0x30100000
	#घोषणा FW_MSG_CODE_LLDP_DONE                   0x40100000
	#घोषणा FW_MSG_CODE_DIAG_ENTER_DONE             0x50100000
	#घोषणा FW_MSG_CODE_DIAG_REFUSE                 0x50200000
	#घोषणा FW_MSG_CODE_DIAG_EXIT_DONE              0x60100000
	#घोषणा FW_MSG_CODE_VALIDATE_KEY_SUCCESS        0x70100000
	#घोषणा FW_MSG_CODE_VALIDATE_KEY_FAILURE        0x70200000
	#घोषणा FW_MSG_CODE_GET_KEY_DONE                0x80100000
	#घोषणा FW_MSG_CODE_NO_KEY                      0x80f00000
	#घोषणा FW_MSG_CODE_LIC_INFO_NOT_READY          0x80f80000
	#घोषणा FW_MSG_CODE_L2B_PRAM_LOADED             0x90100000
	#घोषणा FW_MSG_CODE_L2B_PRAM_T_LOAD_FAILURE     0x90210000
	#घोषणा FW_MSG_CODE_L2B_PRAM_C_LOAD_FAILURE     0x90220000
	#घोषणा FW_MSG_CODE_L2B_PRAM_X_LOAD_FAILURE     0x90230000
	#घोषणा FW_MSG_CODE_L2B_PRAM_U_LOAD_FAILURE     0x90240000
	#घोषणा FW_MSG_CODE_VRFY_OPT_MDL_SUCCESS        0xa0100000
	#घोषणा FW_MSG_CODE_VRFY_OPT_MDL_INVLD_IMG      0xa0200000
	#घोषणा FW_MSG_CODE_VRFY_OPT_MDL_UNAPPROVED     0xa0300000
	#घोषणा FW_MSG_CODE_VF_DISABLED_DONE            0xb0000000
	#घोषणा FW_MSG_CODE_HW_SET_INVALID_IMAGE        0xb0100000

	#घोषणा FW_MSG_CODE_AFEX_DRIVER_SETMAC_DONE     0xd0100000
	#घोषणा FW_MSG_CODE_AFEX_LISTGET_ACK            0xd1100000
	#घोषणा FW_MSG_CODE_AFEX_LISTSET_ACK            0xd2100000
	#घोषणा FW_MSG_CODE_AFEX_STATSGET_ACK           0xd3100000
	#घोषणा FW_MSG_CODE_AFEX_VIFSET_ACK             0xd4100000

	#घोषणा FW_MSG_CODE_DRV_INFO_ACK                0xd8100000
	#घोषणा FW_MSG_CODE_DRV_INFO_NACK               0xd9100000

	#घोषणा FW_MSG_CODE_EEE_RESULS_ACK              0xda100000

	#घोषणा FW_MSG_CODE_RMMOD_ACK                   0xdb100000

	#घोषणा FW_MSG_CODE_SET_MF_BW_SENT              0xe0000000
	#घोषणा FW_MSG_CODE_SET_MF_BW_DONE              0xe1000000

	#घोषणा FW_MSG_CODE_LINK_CHANGED_ACK            0x01100000

	#घोषणा FW_MSG_CODE_LIC_CHALLENGE               0xff010000
	#घोषणा FW_MSG_CODE_LIC_RESPONSE                0xff020000
	#घोषणा FW_MSG_CODE_VIRT_MAC_PRIM               0xff030000
	#घोषणा FW_MSG_CODE_VIRT_MAC_ISCSI              0xff040000

	#घोषणा FW_MSG_SEQ_NUMBER_MASK                  0x0000ffff

	u32 fw_mb_param;

	u32 drv_pulse_mb;
	#घोषणा DRV_PULSE_SEQ_MASK                      0x00007fff
	#घोषणा DRV_PULSE_SYSTEM_TIME_MASK              0xffff0000
	/*
	 * The प्रणाली समय is in the क्रमmat of
	 * (year-2001)*12*32 + month*32 + day.
	 */
	#घोषणा DRV_PULSE_ALWAYS_ALIVE                  0x00008000
	/*
	 * Indicate to the firmware not to go पूर्णांकo the
	 * OS-असलent when it is not getting driver pulse.
	 * This is used क्रम debugging as well क्रम PXE(MBA).
	 */

	u32 mcp_pulse_mb;
	#घोषणा MCP_PULSE_SEQ_MASK                      0x00007fff
	#घोषणा MCP_PULSE_ALWAYS_ALIVE                  0x00008000
	/* Indicates to the driver not to निश्चित due to lack
	 * of MCP response */
	#घोषणा MCP_EVENT_MASK                          0xffff0000
	#घोषणा MCP_EVENT_OTHER_DRIVER_RESET_REQ        0x00010000

	u32 iscsi_boot_signature;
	u32 iscsi_boot_block_offset;

	u32 drv_status;
	#घोषणा DRV_STATUS_PMF                          0x00000001
	#घोषणा DRV_STATUS_VF_DISABLED                  0x00000002
	#घोषणा DRV_STATUS_SET_MF_BW                    0x00000004
	#घोषणा DRV_STATUS_LINK_EVENT                   0x00000008

	#घोषणा DRV_STATUS_OEM_EVENT_MASK               0x00000070
	#घोषणा DRV_STATUS_OEM_DISABLE_ENABLE_PF        0x00000010
	#घोषणा DRV_STATUS_OEM_BANDWIDTH_ALLOCATION     0x00000020

	#घोषणा DRV_STATUS_OEM_UPDATE_SVID              0x00000080

	#घोषणा DRV_STATUS_DCC_EVENT_MASK               0x0000ff00
	#घोषणा DRV_STATUS_DCC_DISABLE_ENABLE_PF        0x00000100
	#घोषणा DRV_STATUS_DCC_BANDWIDTH_ALLOCATION     0x00000200
	#घोषणा DRV_STATUS_DCC_CHANGE_MAC_ADDRESS       0x00000400
	#घोषणा DRV_STATUS_DCC_RESERVED1                0x00000800
	#घोषणा DRV_STATUS_DCC_SET_PROTOCOL             0x00001000
	#घोषणा DRV_STATUS_DCC_SET_PRIORITY             0x00002000

	#घोषणा DRV_STATUS_DCBX_EVENT_MASK              0x000f0000
	#घोषणा DRV_STATUS_DCBX_NEGOTIATION_RESULTS     0x00010000
	#घोषणा DRV_STATUS_AFEX_EVENT_MASK              0x03f00000
	#घोषणा DRV_STATUS_AFEX_LISTGET_REQ             0x00100000
	#घोषणा DRV_STATUS_AFEX_LISTSET_REQ             0x00200000
	#घोषणा DRV_STATUS_AFEX_STATSGET_REQ            0x00400000
	#घोषणा DRV_STATUS_AFEX_VIFSET_REQ              0x00800000

	#घोषणा DRV_STATUS_DRV_INFO_REQ                 0x04000000

	#घोषणा DRV_STATUS_EEE_NEGOTIATION_RESULTS      0x08000000

	u32 virt_mac_upper;
	#घोषणा VIRT_MAC_SIGN_MASK                      0xffff0000
	#घोषणा VIRT_MAC_SIGNATURE                      0x564d0000
	u32 virt_mac_lower;

पूर्ण;


/****************************************************************************
 * Management firmware state                                                *
 ****************************************************************************/
/* Allocate 440 bytes क्रम management firmware */
#घोषणा MGMTFW_STATE_WORD_SIZE                          110

काष्ठा mgmtfw_state अणु
	u32 opaque[MGMTFW_STATE_WORD_SIZE];
पूर्ण;


/****************************************************************************
 * Multi-Function configuration                                             *
 ****************************************************************************/
काष्ठा shared_mf_cfg अणु

	u32 clp_mb;
	#घोषणा SHARED_MF_CLP_SET_DEFAULT               0x00000000
	/* set by CLP */
	#घोषणा SHARED_MF_CLP_EXIT                      0x00000001
	/* set by MCP */
	#घोषणा SHARED_MF_CLP_EXIT_DONE                 0x00010000

पूर्ण;

काष्ठा port_mf_cfg अणु

	u32 dynamic_cfg;    /* device control channel */
	#घोषणा PORT_MF_CFG_E1HOV_TAG_MASK              0x0000ffff
	#घोषणा PORT_MF_CFG_E1HOV_TAG_SHIFT             0
	#घोषणा PORT_MF_CFG_E1HOV_TAG_DEFAULT         PORT_MF_CFG_E1HOV_TAG_MASK

	u32 reserved[1];

पूर्ण;

काष्ठा func_mf_cfg अणु

	u32 config;
	/* E/R/I/D */
	/* function 0 of each port cannot be hidden */
	#घोषणा FUNC_MF_CFG_FUNC_HIDE                   0x00000001

	#घोषणा FUNC_MF_CFG_PROTOCOL_MASK               0x00000006
	#घोषणा FUNC_MF_CFG_PROTOCOL_FCOE               0x00000000
	#घोषणा FUNC_MF_CFG_PROTOCOL_ETHERNET           0x00000002
	#घोषणा FUNC_MF_CFG_PROTOCOL_ETHERNET_WITH_RDMA 0x00000004
	#घोषणा FUNC_MF_CFG_PROTOCOL_ISCSI              0x00000006
	#घोषणा FUNC_MF_CFG_PROTOCOL_DEFAULT \
				FUNC_MF_CFG_PROTOCOL_ETHERNET_WITH_RDMA

	#घोषणा FUNC_MF_CFG_FUNC_DISABLED               0x00000008
	#घोषणा FUNC_MF_CFG_FUNC_DELETED                0x00000010

	/* PRI */
	/* 0 - low priority, 3 - high priority */
	#घोषणा FUNC_MF_CFG_TRANSMIT_PRIORITY_MASK      0x00000300
	#घोषणा FUNC_MF_CFG_TRANSMIT_PRIORITY_SHIFT     8
	#घोषणा FUNC_MF_CFG_TRANSMIT_PRIORITY_DEFAULT   0x00000000

	/* MINBW, MAXBW */
	/* value range - 0..100, increments in 100Mbps */
	#घोषणा FUNC_MF_CFG_MIN_BW_MASK                 0x00ff0000
	#घोषणा FUNC_MF_CFG_MIN_BW_SHIFT                16
	#घोषणा FUNC_MF_CFG_MIN_BW_DEFAULT              0x00000000
	#घोषणा FUNC_MF_CFG_MAX_BW_MASK                 0xff000000
	#घोषणा FUNC_MF_CFG_MAX_BW_SHIFT                24
	#घोषणा FUNC_MF_CFG_MAX_BW_DEFAULT              0x64000000

	u32 mac_upper;	    /* MAC */
	#घोषणा FUNC_MF_CFG_UPPERMAC_MASK               0x0000ffff
	#घोषणा FUNC_MF_CFG_UPPERMAC_SHIFT              0
	#घोषणा FUNC_MF_CFG_UPPERMAC_DEFAULT           FUNC_MF_CFG_UPPERMAC_MASK
	u32 mac_lower;
	#घोषणा FUNC_MF_CFG_LOWERMAC_DEFAULT            0xffffffff

	u32 e1hov_tag;	/* VNI */
	#घोषणा FUNC_MF_CFG_E1HOV_TAG_MASK              0x0000ffff
	#घोषणा FUNC_MF_CFG_E1HOV_TAG_SHIFT             0
	#घोषणा FUNC_MF_CFG_E1HOV_TAG_DEFAULT         FUNC_MF_CFG_E1HOV_TAG_MASK

	/* afex शेष VLAN ID - 12 bits */
	#घोषणा FUNC_MF_CFG_AFEX_VLAN_MASK              0x0fff0000
	#घोषणा FUNC_MF_CFG_AFEX_VLAN_SHIFT             16

	u32 afex_config;
	#घोषणा FUNC_MF_CFG_AFEX_COS_FILTER_MASK                     0x000000ff
	#घोषणा FUNC_MF_CFG_AFEX_COS_FILTER_SHIFT                    0
	#घोषणा FUNC_MF_CFG_AFEX_MBA_ENABLED_MASK                    0x0000ff00
	#घोषणा FUNC_MF_CFG_AFEX_MBA_ENABLED_SHIFT                   8
	#घोषणा FUNC_MF_CFG_AFEX_MBA_ENABLED_VAL                     0x00000100
	#घोषणा FUNC_MF_CFG_AFEX_VLAN_MODE_MASK                      0x000f0000
	#घोषणा FUNC_MF_CFG_AFEX_VLAN_MODE_SHIFT                     16

	u32 reserved;
पूर्ण;

क्रमागत mf_cfg_afex_vlan_mode अणु
	FUNC_MF_CFG_AFEX_VLAN_TRUNK_MODE = 0,
	FUNC_MF_CFG_AFEX_VLAN_ACCESS_MODE,
	FUNC_MF_CFG_AFEX_VLAN_TRUNK_TAG_NATIVE_MODE
पूर्ण;

/* This काष्ठाure is not applicable and should not be accessed on 57711 */
काष्ठा func_ext_cfg अणु
	u32 func_cfg;
	#घोषणा MACP_FUNC_CFG_FLAGS_MASK                0x0000007F
	#घोषणा MACP_FUNC_CFG_FLAGS_SHIFT               0
	#घोषणा MACP_FUNC_CFG_FLAGS_ENABLED             0x00000001
	#घोषणा MACP_FUNC_CFG_FLAGS_ETHERNET            0x00000002
	#घोषणा MACP_FUNC_CFG_FLAGS_ISCSI_OFFLOAD       0x00000004
	#घोषणा MACP_FUNC_CFG_FLAGS_FCOE_OFFLOAD        0x00000008
	#घोषणा MACP_FUNC_CFG_PAUSE_ON_HOST_RING        0x00000080

	u32 iscsi_mac_addr_upper;
	u32 iscsi_mac_addr_lower;

	u32 fcoe_mac_addr_upper;
	u32 fcoe_mac_addr_lower;

	u32 fcoe_wwn_port_name_upper;
	u32 fcoe_wwn_port_name_lower;

	u32 fcoe_wwn_node_name_upper;
	u32 fcoe_wwn_node_name_lower;

	u32 preserve_data;
	#घोषणा MF_FUNC_CFG_PRESERVE_L2_MAC             (1<<0)
	#घोषणा MF_FUNC_CFG_PRESERVE_ISCSI_MAC          (1<<1)
	#घोषणा MF_FUNC_CFG_PRESERVE_FCOE_MAC           (1<<2)
	#घोषणा MF_FUNC_CFG_PRESERVE_FCOE_WWN_P         (1<<3)
	#घोषणा MF_FUNC_CFG_PRESERVE_FCOE_WWN_N         (1<<4)
	#घोषणा MF_FUNC_CFG_PRESERVE_TX_BW              (1<<5)
पूर्ण;

काष्ठा mf_cfg अणु

	काष्ठा shared_mf_cfg    shared_mf_config;       /* 0x4 */
							/* 0x8*2*2=0x20 */
	काष्ठा port_mf_cfg  port_mf_config[NVM_PATH_MAX][PORT_MAX];
	/* क्रम all chips, there are 8 mf functions */
	काष्ठा func_mf_cfg  func_mf_config[E1H_FUNC_MAX]; /* 0x18 * 8 = 0xc0 */
	/*
	 * Extended configuration per function  - this array करोes not exist and
	 * should not be accessed on 57711
	 */
	काष्ठा func_ext_cfg func_ext_config[E1H_FUNC_MAX]; /* 0x28 * 8 = 0x140*/
पूर्ण; /* 0x224 */

/****************************************************************************
 * Shared Memory Region                                                     *
 ****************************************************************************/
काष्ठा shmem_region अणु		       /*   SharedMem Offset (size) */

	u32         validity_map[PORT_MAX];  /* 0x0 (4*2 = 0x8) */
	#घोषणा SHR_MEM_FORMAT_REV_MASK                     0xff000000
	#घोषणा SHR_MEM_FORMAT_REV_ID                       ('A'<<24)
	/* validity bits */
	#घोषणा SHR_MEM_VALIDITY_PCI_CFG                    0x00100000
	#घोषणा SHR_MEM_VALIDITY_MB                         0x00200000
	#घोषणा SHR_MEM_VALIDITY_DEV_INFO                   0x00400000
	#घोषणा SHR_MEM_VALIDITY_RESERVED                   0x00000007
	/* One licensing bit should be set */
	#घोषणा SHR_MEM_VALIDITY_LIC_KEY_IN_EFFECT_MASK     0x00000038
	#घोषणा SHR_MEM_VALIDITY_LIC_MANUF_KEY_IN_EFFECT    0x00000008
	#घोषणा SHR_MEM_VALIDITY_LIC_UPGRADE_KEY_IN_EFFECT  0x00000010
	#घोषणा SHR_MEM_VALIDITY_LIC_NO_KEY_IN_EFFECT       0x00000020
	/* Active MFW */
	#घोषणा SHR_MEM_VALIDITY_ACTIVE_MFW_UNKNOWN         0x00000000
	#घोषणा SHR_MEM_VALIDITY_ACTIVE_MFW_MASK            0x000001c0
	#घोषणा SHR_MEM_VALIDITY_ACTIVE_MFW_IPMI            0x00000040
	#घोषणा SHR_MEM_VALIDITY_ACTIVE_MFW_UMP             0x00000080
	#घोषणा SHR_MEM_VALIDITY_ACTIVE_MFW_NCSI            0x000000c0
	#घोषणा SHR_MEM_VALIDITY_ACTIVE_MFW_NONE            0x000001c0

	काष्ठा shm_dev_info dev_info;	     /* 0x8     (0x438) */

	काष्ठा license_key       drv_lic_key[PORT_MAX]; /* 0x440 (52*2=0x68) */

	/* FW inक्रमmation (क्रम पूर्णांकernal FW use) */
	u32         fw_info_fio_offset;		/* 0x4a8       (0x4) */
	काष्ठा mgmtfw_state mgmtfw_state;	/* 0x4ac     (0x1b8) */

	काष्ठा drv_port_mb  port_mb[PORT_MAX];	/* 0x664 (16*2=0x20) */

#अगर_घोषित BMAPI
	/* This is a variable length array */
	/* the number of function depends on the chip type */
	काष्ठा drv_func_mb func_mb[1];	/* 0x684 (44*2/4/8=0x58/0xb0/0x160) */
#अन्यथा
	/* the number of function depends on the chip type */
	काष्ठा drv_func_mb  func_mb[];	/* 0x684 (44*2/4/8=0x58/0xb0/0x160) */
#पूर्ण_अगर /* BMAPI */

पूर्ण; /* 57710 = 0x6dc | 57711 = 0x7E4 | 57712 = 0x734 */

/****************************************************************************
 * Shared Memory 2 Region                                                   *
 ****************************************************************************/
/* The fw_flr_ack is actually built in the following way:                   */
/* 8 bit:  PF ack                                                           */
/* 64 bit: VF ack                                                           */
/* 8 bit:  ios_dis_ack                                                      */
/* In order to मुख्यtain endianity in the mailbox hsi, we want to keep using */
/* u32. The fw must have the VF right after the PF since this is how it     */
/* access arrays(it expects always the VF to reside after the PF, and that  */
/* makes the calculation much easier क्रम it. )                              */
/* In order to answer both limitations, and keep the काष्ठा small, the code */
/* will abuse the काष्ठाure defined here to achieve the actual partition    */
/* above                                                                    */
/****************************************************************************/
काष्ठा fw_flr_ack अणु
	u32         pf_ack;
	u32         vf_ack[1];
	u32         iov_dis_ack;
पूर्ण;

काष्ठा fw_flr_mb अणु
	u32         aggपूर्णांक;
	u32         opgen_addr;
	काष्ठा fw_flr_ack ack;
पूर्ण;

काष्ठा eee_remote_vals अणु
	u32         tx_tw;
	u32         rx_tw;
पूर्ण;

/**** SUPPORT FOR SHMEM ARRRAYS ***
 * The SHMEM HSI is aligned on 32 bit boundaries which makes it dअगरficult to
 * define arrays with storage types smaller then अचिन्हित dwords.
 * The macros below add generic support क्रम SHMEM arrays with numeric elements
 * that can span 2,4,8 or 16 bits. The array underlying type is a 32 bit dword
 * array with inभागidual bit-filed elements accessed using shअगरts and masks.
 *
 */

/* eb is the bitwidth of a single element */
#घोषणा SHMEM_ARRAY_MASK(eb)		((1<<(eb))-1)
#घोषणा SHMEM_ARRAY_ENTRY(i, eb)	((i)/(32/(eb)))

/* the bit-position macro allows the used to flip the order of the arrays
 * elements on a per byte or word boundary.
 *
 * example: an array with 8 entries each 4 bit wide. This array will fit पूर्णांकo
 * a single dword. The diagrmas below show the array order of the nibbles.
 *
 * SHMEM_ARRAY_BITPOS(i, 4, 4) defines the stadard ordering:
 *
 *                |                |                |               |
 *   0    |   1   |   2    |   3   |   4    |   5   |   6   |   7   |
 *                |                |                |               |
 *
 * SHMEM_ARRAY_BITPOS(i, 4, 8) defines a flip ordering per byte:
 *
 *                |                |                |               |
 *   1   |   0    |   3    |   2   |   5    |   4   |   7   |   6   |
 *                |                |                |               |
 *
 * SHMEM_ARRAY_BITPOS(i, 4, 16) defines a flip ordering per word:
 *
 *                |                |                |               |
 *   3   |   2    |   1   |   0    |   7   |   6    |   5   |   4   |
 *                |                |                |               |
 */
#घोषणा SHMEM_ARRAY_BITPOS(i, eb, fb)	\
	((((32/(fb)) - 1 - ((i)/((fb)/(eb))) % (32/(fb))) * (fb)) + \
	(((i)%((fb)/(eb))) * (eb)))

#घोषणा SHMEM_ARRAY_GET(a, i, eb, fb)					\
	((a[SHMEM_ARRAY_ENTRY(i, eb)] >> SHMEM_ARRAY_BITPOS(i, eb, fb)) &  \
	SHMEM_ARRAY_MASK(eb))

#घोषणा SHMEM_ARRAY_SET(a, i, eb, fb, val)				\
करो अणु									   \
	a[SHMEM_ARRAY_ENTRY(i, eb)] &= ~(SHMEM_ARRAY_MASK(eb) <<	   \
	SHMEM_ARRAY_BITPOS(i, eb, fb));					   \
	a[SHMEM_ARRAY_ENTRY(i, eb)] |= (((val) & SHMEM_ARRAY_MASK(eb)) <<  \
	SHMEM_ARRAY_BITPOS(i, eb, fb));					   \
पूर्ण जबतक (0)


/****START OF DCBX STRUCTURES DECLARATIONS****/
#घोषणा DCBX_MAX_NUM_PRI_PG_ENTRIES	8
#घोषणा DCBX_PRI_PG_BITWIDTH		4
#घोषणा DCBX_PRI_PG_FBITS		8
#घोषणा DCBX_PRI_PG_GET(a, i)		\
	SHMEM_ARRAY_GET(a, i, DCBX_PRI_PG_BITWIDTH, DCBX_PRI_PG_FBITS)
#घोषणा DCBX_PRI_PG_SET(a, i, val)	\
	SHMEM_ARRAY_SET(a, i, DCBX_PRI_PG_BITWIDTH, DCBX_PRI_PG_FBITS, val)
#घोषणा DCBX_MAX_NUM_PG_BW_ENTRIES	8
#घोषणा DCBX_BW_PG_BITWIDTH		8
#घोषणा DCBX_PG_BW_GET(a, i)		\
	SHMEM_ARRAY_GET(a, i, DCBX_BW_PG_BITWIDTH, DCBX_BW_PG_BITWIDTH)
#घोषणा DCBX_PG_BW_SET(a, i, val)	\
	SHMEM_ARRAY_SET(a, i, DCBX_BW_PG_BITWIDTH, DCBX_BW_PG_BITWIDTH, val)
#घोषणा DCBX_STRICT_PRI_PG		15
#घोषणा DCBX_MAX_APP_PROTOCOL		16
#घोषणा FCOE_APP_IDX			0
#घोषणा ISCSI_APP_IDX			1
#घोषणा PREDEFINED_APP_IDX_MAX		2


/* Big/Little endian have the same representation. */
काष्ठा dcbx_ets_feature अणु
	/*
	 * For Admin MIB - is this feature supported by the
	 * driver | For Local MIB - should this feature be enabled.
	 */
	u32 enabled;
	u32  pg_bw_tbl[2];
	u32  pri_pg_tbl[1];
पूर्ण;

/* Driver काष्ठाure in LE */
काष्ठा dcbx_pfc_feature अणु
#अगर_घोषित __BIG_ENDIAN
	u8 pri_en_biपंचांगap;
	#घोषणा DCBX_PFC_PRI_0 0x01
	#घोषणा DCBX_PFC_PRI_1 0x02
	#घोषणा DCBX_PFC_PRI_2 0x04
	#घोषणा DCBX_PFC_PRI_3 0x08
	#घोषणा DCBX_PFC_PRI_4 0x10
	#घोषणा DCBX_PFC_PRI_5 0x20
	#घोषणा DCBX_PFC_PRI_6 0x40
	#घोषणा DCBX_PFC_PRI_7 0x80
	u8 pfc_caps;
	u8 reserved;
	u8 enabled;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 enabled;
	u8 reserved;
	u8 pfc_caps;
	u8 pri_en_biपंचांगap;
	#घोषणा DCBX_PFC_PRI_0 0x01
	#घोषणा DCBX_PFC_PRI_1 0x02
	#घोषणा DCBX_PFC_PRI_2 0x04
	#घोषणा DCBX_PFC_PRI_3 0x08
	#घोषणा DCBX_PFC_PRI_4 0x10
	#घोषणा DCBX_PFC_PRI_5 0x20
	#घोषणा DCBX_PFC_PRI_6 0x40
	#घोषणा DCBX_PFC_PRI_7 0x80
#पूर्ण_अगर
पूर्ण;

काष्ठा dcbx_app_priority_entry अणु
#अगर_घोषित __BIG_ENDIAN
	u16  app_id;
	u8  pri_biपंचांगap;
	u8  appBitfield;
	#घोषणा DCBX_APP_ENTRY_VALID         0x01
	#घोषणा DCBX_APP_ENTRY_SF_MASK       0xF0
	#घोषणा DCBX_APP_ENTRY_SF_SHIFT      4
	#घोषणा DCBX_APP_SF_ETH_TYPE         0x10
	#घोषणा DCBX_APP_SF_PORT             0x20
	#घोषणा DCBX_APP_SF_UDP              0x40
	#घोषणा DCBX_APP_SF_DEFAULT          0x80
#या_अगर defined(__LITTLE_ENDIAN)
	u8 appBitfield;
	#घोषणा DCBX_APP_ENTRY_VALID         0x01
	#घोषणा DCBX_APP_ENTRY_SF_MASK       0xF0
	#घोषणा DCBX_APP_ENTRY_SF_SHIFT      4
	#घोषणा DCBX_APP_ENTRY_VALID         0x01
	#घोषणा DCBX_APP_SF_ETH_TYPE         0x10
	#घोषणा DCBX_APP_SF_PORT             0x20
	#घोषणा DCBX_APP_SF_UDP              0x40
	#घोषणा DCBX_APP_SF_DEFAULT          0x80
	u8  pri_biपंचांगap;
	u16  app_id;
#पूर्ण_अगर
पूर्ण;


/* FW काष्ठाure in BE */
काष्ठा dcbx_app_priority_feature अणु
#अगर_घोषित __BIG_ENDIAN
	u8 reserved;
	u8 शेष_pri;
	u8 tc_supported;
	u8 enabled;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 enabled;
	u8 tc_supported;
	u8 शेष_pri;
	u8 reserved;
#पूर्ण_अगर
	काष्ठा dcbx_app_priority_entry  app_pri_tbl[DCBX_MAX_APP_PROTOCOL];
पूर्ण;

/* FW काष्ठाure in BE */
काष्ठा dcbx_features अणु
	/* PG feature */
	काष्ठा dcbx_ets_feature ets;
	/* PFC feature */
	काष्ठा dcbx_pfc_feature pfc;
	/* APP feature */
	काष्ठा dcbx_app_priority_feature app;
पूर्ण;

/* LLDP protocol parameters */
/* FW काष्ठाure in BE */
काष्ठा lldp_params अणु
#अगर_घोषित __BIG_ENDIAN
	u8  msg_fast_tx_पूर्णांकerval;
	u8  msg_tx_hold;
	u8  msg_tx_पूर्णांकerval;
	u8  admin_status;
	#घोषणा LLDP_TX_ONLY  0x01
	#घोषणा LLDP_RX_ONLY  0x02
	#घोषणा LLDP_TX_RX    0x03
	#घोषणा LLDP_DISABLED 0x04
	u8  reserved1;
	u8  tx_fast;
	u8  tx_crd_max;
	u8  tx_crd;
#या_अगर defined(__LITTLE_ENDIAN)
	u8  admin_status;
	#घोषणा LLDP_TX_ONLY  0x01
	#घोषणा LLDP_RX_ONLY  0x02
	#घोषणा LLDP_TX_RX    0x03
	#घोषणा LLDP_DISABLED 0x04
	u8  msg_tx_पूर्णांकerval;
	u8  msg_tx_hold;
	u8  msg_fast_tx_पूर्णांकerval;
	u8  tx_crd;
	u8  tx_crd_max;
	u8  tx_fast;
	u8  reserved1;
#पूर्ण_अगर
	#घोषणा REM_CHASSIS_ID_STAT_LEN 4
	#घोषणा REM_PORT_ID_STAT_LEN 4
	/* Holds remote Chassis ID TLV header, subtype and 9B of payload. */
	u32 peer_chassis_id[REM_CHASSIS_ID_STAT_LEN];
	/* Holds remote Port ID TLV header, subtype and 9B of payload. */
	u32 peer_port_id[REM_PORT_ID_STAT_LEN];
पूर्ण;

काष्ठा lldp_dcbx_stat अणु
	#घोषणा LOCAL_CHASSIS_ID_STAT_LEN 2
	#घोषणा LOCAL_PORT_ID_STAT_LEN 2
	/* Holds local Chassis ID 8B payload of स्थिरant subtype 4. */
	u32 local_chassis_id[LOCAL_CHASSIS_ID_STAT_LEN];
	/* Holds local Port ID 8B payload of स्थिरant subtype 3. */
	u32 local_port_id[LOCAL_PORT_ID_STAT_LEN];
	/* Number of DCBX frames transmitted. */
	u32 num_tx_dcbx_pkts;
	/* Number of DCBX frames received. */
	u32 num_rx_dcbx_pkts;
पूर्ण;

/* ADMIN MIB - DCBX local machine शेष configuration. */
काष्ठा lldp_admin_mib अणु
	u32     ver_cfg_flags;
	#घोषणा DCBX_ETS_CONFIG_TX_ENABLED       0x00000001
	#घोषणा DCBX_PFC_CONFIG_TX_ENABLED       0x00000002
	#घोषणा DCBX_APP_CONFIG_TX_ENABLED       0x00000004
	#घोषणा DCBX_ETS_RECO_TX_ENABLED         0x00000008
	#घोषणा DCBX_ETS_RECO_VALID              0x00000010
	#घोषणा DCBX_ETS_WILLING                 0x00000020
	#घोषणा DCBX_PFC_WILLING                 0x00000040
	#घोषणा DCBX_APP_WILLING                 0x00000080
	#घोषणा DCBX_VERSION_CEE                 0x00000100
	#घोषणा DCBX_VERSION_IEEE                0x00000200
	#घोषणा DCBX_DCBX_ENABLED                0x00000400
	#घोषणा DCBX_CEE_VERSION_MASK            0x0000f000
	#घोषणा DCBX_CEE_VERSION_SHIFT           12
	#घोषणा DCBX_CEE_MAX_VERSION_MASK        0x000f0000
	#घोषणा DCBX_CEE_MAX_VERSION_SHIFT       16
	काष्ठा dcbx_features     features;
पूर्ण;

/* REMOTE MIB - remote machine DCBX configuration. */
काष्ठा lldp_remote_mib अणु
	u32 prefix_seq_num;
	u32 flags;
	#घोषणा DCBX_ETS_TLV_RX                  0x00000001
	#घोषणा DCBX_PFC_TLV_RX                  0x00000002
	#घोषणा DCBX_APP_TLV_RX                  0x00000004
	#घोषणा DCBX_ETS_RX_ERROR                0x00000010
	#घोषणा DCBX_PFC_RX_ERROR                0x00000020
	#घोषणा DCBX_APP_RX_ERROR                0x00000040
	#घोषणा DCBX_ETS_REM_WILLING             0x00000100
	#घोषणा DCBX_PFC_REM_WILLING             0x00000200
	#घोषणा DCBX_APP_REM_WILLING             0x00000400
	#घोषणा DCBX_REMOTE_ETS_RECO_VALID       0x00001000
	#घोषणा DCBX_REMOTE_MIB_VALID            0x00002000
	काष्ठा dcbx_features features;
	u32 suffix_seq_num;
पूर्ण;

/* LOCAL MIB - operational DCBX configuration - transmitted on Tx LLDPDU. */
काष्ठा lldp_local_mib अणु
	u32 prefix_seq_num;
	/* Indicates अगर there is mismatch with negotiation results. */
	u32 error;
	#घोषणा DCBX_LOCAL_ETS_ERROR             0x00000001
	#घोषणा DCBX_LOCAL_PFC_ERROR             0x00000002
	#घोषणा DCBX_LOCAL_APP_ERROR             0x00000004
	#घोषणा DCBX_LOCAL_PFC_MISMATCH          0x00000010
	#घोषणा DCBX_LOCAL_APP_MISMATCH          0x00000020
	#घोषणा DCBX_REMOTE_MIB_ERROR		 0x00000040
	#घोषणा DCBX_REMOTE_ETS_TLV_NOT_FOUND    0x00000080
	#घोषणा DCBX_REMOTE_PFC_TLV_NOT_FOUND    0x00000100
	#घोषणा DCBX_REMOTE_APP_TLV_NOT_FOUND    0x00000200
	काष्ठा dcbx_features   features;
	u32 suffix_seq_num;
पूर्ण;
/***END OF DCBX STRUCTURES DECLARATIONS***/

/***********************************************************/
/*                         Elink section                   */
/***********************************************************/
#घोषणा SHMEM_LINK_CONFIG_SIZE 2
काष्ठा shmem_lfa अणु
	u32 req_duplex;
	#घोषणा REQ_DUPLEX_PHY0_MASK        0x0000ffff
	#घोषणा REQ_DUPLEX_PHY0_SHIFT       0
	#घोषणा REQ_DUPLEX_PHY1_MASK        0xffff0000
	#घोषणा REQ_DUPLEX_PHY1_SHIFT       16
	u32 req_flow_ctrl;
	#घोषणा REQ_FLOW_CTRL_PHY0_MASK     0x0000ffff
	#घोषणा REQ_FLOW_CTRL_PHY0_SHIFT    0
	#घोषणा REQ_FLOW_CTRL_PHY1_MASK     0xffff0000
	#घोषणा REQ_FLOW_CTRL_PHY1_SHIFT    16
	u32 req_line_speed; /* Also determine AutoNeg */
	#घोषणा REQ_LINE_SPD_PHY0_MASK      0x0000ffff
	#घोषणा REQ_LINE_SPD_PHY0_SHIFT     0
	#घोषणा REQ_LINE_SPD_PHY1_MASK      0xffff0000
	#घोषणा REQ_LINE_SPD_PHY1_SHIFT     16
	u32 speed_cap_mask[SHMEM_LINK_CONFIG_SIZE];
	u32 additional_config;
	#घोषणा REQ_FC_AUTO_ADV_MASK        0x0000ffff
	#घोषणा REQ_FC_AUTO_ADV0_SHIFT      0
	#घोषणा NO_LFA_DUE_TO_DCC_MASK      0x00010000
	u32 lfa_sts;
	#घोषणा LFA_LINK_FLAP_REASON_OFFSET		0
	#घोषणा LFA_LINK_FLAP_REASON_MASK		0x000000ff
		#घोषणा LFA_LINK_DOWN			    0x1
		#घोषणा LFA_LOOPBACK_ENABLED		0x2
		#घोषणा LFA_DUPLEX_MISMATCH		    0x3
		#घोषणा LFA_MFW_IS_TOO_OLD		    0x4
		#घोषणा LFA_LINK_SPEED_MISMATCH		0x5
		#घोषणा LFA_FLOW_CTRL_MISMATCH		0x6
		#घोषणा LFA_SPEED_CAP_MISMATCH		0x7
		#घोषणा LFA_DCC_LFA_DISABLED		0x8
		#घोषणा LFA_EEE_MISMATCH		0x9

	#घोषणा LINK_FLAP_AVOIDANCE_COUNT_OFFSET	8
	#घोषणा LINK_FLAP_AVOIDANCE_COUNT_MASK		0x0000ff00

	#घोषणा LINK_FLAP_COUNT_OFFSET			16
	#घोषणा LINK_FLAP_COUNT_MASK			0x00ff0000

	#घोषणा LFA_FLAGS_MASK				0xff000000
	#घोषणा SHMEM_LFA_DONT_CLEAR_STAT		(1<<24)
पूर्ण;

/* Used to support NSCI get OS driver version
 * on driver load the version value will be set
 * on driver unload driver value of 0x0 will be set.
 */
काष्ठा os_drv_ver अणु
#घोषणा DRV_VER_NOT_LOADED			0

	/* personalties order is important */
#घोषणा DRV_PERS_ETHERNET			0
#घोषणा DRV_PERS_ISCSI				1
#घोषणा DRV_PERS_FCOE				2

	/* shmem2 काष्ठा is स्थिरant can't add more personalties here */
#घोषणा MAX_DRV_PERS				3
	u32 versions[MAX_DRV_PERS];
पूर्ण;

काष्ठा ncsi_oem_fcoe_features अणु
	u32 fcoe_features1;
	#घोषणा FCOE_FEATURES1_IOS_PER_CONNECTION_MASK          0x0000FFFF
	#घोषणा FCOE_FEATURES1_IOS_PER_CONNECTION_OFFSET        0

	#घोषणा FCOE_FEATURES1_LOGINS_PER_PORT_MASK             0xFFFF0000
	#घोषणा FCOE_FEATURES1_LOGINS_PER_PORT_OFFSET           16

	u32 fcoe_features2;
	#घोषणा FCOE_FEATURES2_EXCHANGES_MASK                   0x0000FFFF
	#घोषणा FCOE_FEATURES2_EXCHANGES_OFFSET                 0

	#घोषणा FCOE_FEATURES2_NPIV_WWN_PER_PORT_MASK           0xFFFF0000
	#घोषणा FCOE_FEATURES2_NPIV_WWN_PER_PORT_OFFSET         16

	u32 fcoe_features3;
	#घोषणा FCOE_FEATURES3_TARGETS_SUPPORTED_MASK           0x0000FFFF
	#घोषणा FCOE_FEATURES3_TARGETS_SUPPORTED_OFFSET         0

	#घोषणा FCOE_FEATURES3_OUTSTANDING_COMMANDS_MASK        0xFFFF0000
	#घोषणा FCOE_FEATURES3_OUTSTANDING_COMMANDS_OFFSET      16

	u32 fcoe_features4;
	#घोषणा FCOE_FEATURES4_FEATURE_SETTINGS_MASK            0x0000000F
	#घोषणा FCOE_FEATURES4_FEATURE_SETTINGS_OFFSET          0
पूर्ण;

क्रमागत curr_cfg_method_e अणु
	CURR_CFG_MET_NONE = 0,  /* शेष config */
	CURR_CFG_MET_OS = 1,
	CURR_CFG_MET_VENDOR_SPEC = 2,/* e.g. Option ROM, NPAR, O/S Cfg Utils */
पूर्ण;

#घोषणा FC_NPIV_WWPN_SIZE 8
#घोषणा FC_NPIV_WWNN_SIZE 8
काष्ठा bdn_npiv_settings अणु
	u8 npiv_wwpn[FC_NPIV_WWPN_SIZE];
	u8 npiv_wwnn[FC_NPIV_WWNN_SIZE];
पूर्ण;

काष्ठा bdn_fc_npiv_cfg अणु
	/* hdr used पूर्णांकernally by the MFW */
	u32 hdr;
	u32 num_of_npiv;
पूर्ण;

#घोषणा MAX_NUMBER_NPIV 64
काष्ठा bdn_fc_npiv_tbl अणु
	काष्ठा bdn_fc_npiv_cfg fc_npiv_cfg;
	काष्ठा bdn_npiv_settings settings[MAX_NUMBER_NPIV];
पूर्ण;

काष्ठा mdump_driver_info अणु
	u32 epoc;
	u32 drv_ver;
	u32 fw_ver;

	u32 valid_dump;
	#घोषणा FIRST_DUMP_VALID        (1 << 0)
	#घोषणा SECOND_DUMP_VALID       (1 << 1)

	u32 flags;
	#घोषणा ENABLE_ALL_TRIGGERS     (0x7fffffff)
	#घोषणा TRIGGER_MDUMP_ONCE      (1 << 31)
पूर्ण;

काष्ठा ncsi_oem_data अणु
	u32 driver_version[4];
	काष्ठा ncsi_oem_fcoe_features ncsi_oem_fcoe_features;
पूर्ण;

काष्ठा shmem2_region अणु

	u32 size;					/* 0x0000 */

	u32 dcc_support;				/* 0x0004 */
	#घोषणा SHMEM_DCC_SUPPORT_NONE                      0x00000000
	#घोषणा SHMEM_DCC_SUPPORT_DISABLE_ENABLE_PF_TLV     0x00000001
	#घोषणा SHMEM_DCC_SUPPORT_BANDWIDTH_ALLOCATION_TLV  0x00000004
	#घोषणा SHMEM_DCC_SUPPORT_CHANGE_MAC_ADDRESS_TLV    0x00000008
	#घोषणा SHMEM_DCC_SUPPORT_SET_PROTOCOL_TLV          0x00000040
	#घोषणा SHMEM_DCC_SUPPORT_SET_PRIORITY_TLV          0x00000080

	u32 ext_phy_fw_version2[PORT_MAX];		/* 0x0008 */
	/*
	 * For backwards compatibility, अगर the mf_cfg_addr करोes not exist
	 * (the size filed is smaller than 0xc) the mf_cfg resides at the
	 * end of काष्ठा shmem_region
	 */
	u32 mf_cfg_addr;				/* 0x0010 */
	#घोषणा SHMEM_MF_CFG_ADDR_NONE                  0x00000000

	काष्ठा fw_flr_mb flr_mb;			/* 0x0014 */
	u32 dcbx_lldp_params_offset;			/* 0x0028 */
	#घोषणा SHMEM_LLDP_DCBX_PARAMS_NONE             0x00000000
	u32 dcbx_neg_res_offset;			/* 0x002c */
	#घोषणा SHMEM_DCBX_NEG_RES_NONE			0x00000000
	u32 dcbx_remote_mib_offset;			/* 0x0030 */
	#घोषणा SHMEM_DCBX_REMOTE_MIB_NONE              0x00000000
	/*
	 * The other shmemX_base_addr holds the other path's shmem address
	 * required क्रम example in हाल of common phy init, or क्रम path1 to know
	 * the address of mcp debug trace which is located in offset from shmem
	 * of path0
	 */
	u32 other_shmem_base_addr;			/* 0x0034 */
	u32 other_shmem2_base_addr;			/* 0x0038 */
	/*
	 * mcp_vf_disabled is set by the MCP to indicate the driver about VFs
	 * which were disabled/flred
	 */
	u32 mcp_vf_disabled[E2_VF_MAX / 32];		/* 0x003c */

	/*
	 * drv_ack_vf_disabled is set by the PF driver to ack handled disabled
	 * VFs
	 */
	u32 drv_ack_vf_disabled[E2_FUNC_MAX][E2_VF_MAX / 32]; /* 0x0044 */

	u32 dcbx_lldp_dcbx_stat_offset;			/* 0x0064 */
	#घोषणा SHMEM_LLDP_DCBX_STAT_NONE               0x00000000

	/*
	 * edebug_driver_अगर field is used to transfer messages between edebug
	 * app to the driver through shmem2.
	 *
	 * message क्रमmat:
	 * bits 0-2 -  function number / instance of driver to perक्रमm request
	 * bits 3-5 -  op code / is_ack?
	 * bits 6-63 - data
	 */
	u32 edebug_driver_अगर[2];			/* 0x0068 */
	#घोषणा EDEBUG_DRIVER_IF_OP_CODE_GET_PHYS_ADDR  1
	#घोषणा EDEBUG_DRIVER_IF_OP_CODE_GET_BUS_ADDR   2
	#घोषणा EDEBUG_DRIVER_IF_OP_CODE_DISABLE_STAT   3

	u32 nvm_retain_biपंचांगap_addr;			/* 0x0070 */

	/* afex support of that driver */
	u32 afex_driver_support;			/* 0x0074 */
	#घोषणा SHMEM_AFEX_VERSION_MASK                  0x100f
	#घोषणा SHMEM_AFEX_SUPPORTED_VERSION_ONE         0x1001
	#घोषणा SHMEM_AFEX_REDUCED_DRV_LOADED            0x8000

	/* driver receives addr in scratchpad to which it should respond */
	u32 afex_scratchpad_addr_to_ग_लिखो[E2_FUNC_MAX];

	/* generic params from MCP to driver (value depends on the msg sent
	 * to driver
	 */
	u32 afex_param1_to_driver[E2_FUNC_MAX];		/* 0x0088 */
	u32 afex_param2_to_driver[E2_FUNC_MAX];		/* 0x0098 */

	u32 swim_base_addr;				/* 0x0108 */
	u32 swim_funcs;
	u32 swim_मुख्य_cb;

	/* biपंचांगap notअगरying which VIF profiles stored in nvram are enabled by
	 * चयन
	 */
	u32 afex_profiles_enabled[2];

	/* generic flags controlled by the driver */
	u32 drv_flags;
	#घोषणा DRV_FLAGS_DCB_CONFIGURED		0x0
	#घोषणा DRV_FLAGS_DCB_CONFIGURATION_ABORTED	0x1
	#घोषणा DRV_FLAGS_DCB_MFW_CONFIGURED	0x2

	#घोषणा DRV_FLAGS_PORT_MASK	((1 << DRV_FLAGS_DCB_CONFIGURED) | \
			(1 << DRV_FLAGS_DCB_CONFIGURATION_ABORTED) | \
			(1 << DRV_FLAGS_DCB_MFW_CONFIGURED))
	/* poपूर्णांकer to extended dev_info shared data copied from nvm image */
	u32 extended_dev_info_shared_addr;
	u32 ncsi_oem_data_addr;

	u32 ocsd_host_addr; /* initialized by option ROM */
	u32 ocbb_host_addr; /* initialized by option ROM */
	u32 ocsd_req_update_पूर्णांकerval; /* initialized by option ROM */
	u32 temperature_in_half_celsius;
	u32 glob_काष्ठा_in_host;

	u32 dcbx_neg_res_ext_offset;
#घोषणा SHMEM_DCBX_NEG_RES_EXT_NONE			0x00000000

	u32 drv_capabilities_flag[E2_FUNC_MAX];
#घोषणा DRV_FLAGS_CAPABILITIES_LOADED_SUPPORTED 0x00000001
#घोषणा DRV_FLAGS_CAPABILITIES_LOADED_L2        0x00000002
#घोषणा DRV_FLAGS_CAPABILITIES_LOADED_FCOE      0x00000004
#घोषणा DRV_FLAGS_CAPABILITIES_LOADED_ISCSI     0x00000008
#घोषणा DRV_FLAGS_MTU_MASK			0xffff0000
#घोषणा DRV_FLAGS_MTU_SHIFT			16

	u32 extended_dev_info_shared_cfg_size;

	u32 dcbx_en[PORT_MAX];

	/* The offset poपूर्णांकs to the multi thपढ़ोed meta काष्ठाure */
	u32 multi_thपढ़ो_data_offset;

	/* address of DMAable host address holding values from the drivers */
	u32 drv_info_host_addr_lo;
	u32 drv_info_host_addr_hi;

	/* general values written by the MFW (such as current version) */
	u32 drv_info_control;
#घोषणा DRV_INFO_CONTROL_VER_MASK          0x000000ff
#घोषणा DRV_INFO_CONTROL_VER_SHIFT         0
#घोषणा DRV_INFO_CONTROL_OP_CODE_MASK      0x0000ff00
#घोषणा DRV_INFO_CONTROL_OP_CODE_SHIFT     8
	u32 ibft_host_addr; /* initialized by option ROM */
	काष्ठा eee_remote_vals eee_remote_vals[PORT_MAX];
	u32 reserved[E2_FUNC_MAX];


	/* the status of EEE स्वतः-negotiation
	 * bits 15:0 the configured tx-lpi entry समयr value. Depends on bit 31.
	 * bits 19:16 the supported modes क्रम EEE.
	 * bits 23:20 the speeds advertised क्रम EEE.
	 * bits 27:24 the speeds the Link partner advertised क्रम EEE.
	 * The supported/adv. modes in bits 27:19 originate from the
	 * SHMEM_EEE_XXX_ADV definitions (where XXX is replaced by speed).
	 * bit 28 when 1'b1 EEE was requested.
	 * bit 29 when 1'b1 tx lpi was requested.
	 * bit 30 when 1'b1 EEE was negotiated. Tx lpi will be निश्चितed अगरf
	 * 30:29 are 2'b11.
	 * bit 31 when 1'b0 bits 15:0 contain a PORT_FEAT_CFG_EEE_ define as
	 * value. When 1'b1 those bits contains a value बार 16 microseconds.
	 */
	u32 eee_status[PORT_MAX];
	#घोषणा SHMEM_EEE_TIMER_MASK		   0x0000ffff
	#घोषणा SHMEM_EEE_SUPPORTED_MASK	   0x000f0000
	#घोषणा SHMEM_EEE_SUPPORTED_SHIFT	   16
	#घोषणा SHMEM_EEE_ADV_STATUS_MASK	   0x00f00000
		#घोषणा SHMEM_EEE_100M_ADV	   (1<<0)
		#घोषणा SHMEM_EEE_1G_ADV	   (1<<1)
		#घोषणा SHMEM_EEE_10G_ADV	   (1<<2)
	#घोषणा SHMEM_EEE_ADV_STATUS_SHIFT	   20
	#घोषणा	SHMEM_EEE_LP_ADV_STATUS_MASK	   0x0f000000
	#घोषणा SHMEM_EEE_LP_ADV_STATUS_SHIFT	   24
	#घोषणा SHMEM_EEE_REQUESTED_BIT		   0x10000000
	#घोषणा SHMEM_EEE_LPI_REQUESTED_BIT	   0x20000000
	#घोषणा SHMEM_EEE_ACTIVE_BIT		   0x40000000
	#घोषणा SHMEM_EEE_TIME_OUTPUT_BIT	   0x80000000

	u32 माप_port_stats;

	/* Link Flap Aव्योमance */
	u32 lfa_host_addr[PORT_MAX];
	u32 reserved1;

	u32 reserved2;				/* Offset 0x148 */
	u32 reserved3;				/* Offset 0x14C */
	u32 reserved4;				/* Offset 0x150 */
	u32 link_attr_sync[PORT_MAX];		/* Offset 0x154 */
	#घोषणा LINK_ATTR_SYNC_KR2_ENABLE	0x00000001
	#घोषणा LINK_ATTR_84858			0x00000002
	#घोषणा LINK_SFP_EEPROM_COMP_CODE_MASK	0x0000ff00
	#घोषणा LINK_SFP_EEPROM_COMP_CODE_SHIFT		 8
	#घोषणा LINK_SFP_EEPROM_COMP_CODE_SR	0x00001000
	#घोषणा LINK_SFP_EEPROM_COMP_CODE_LR	0x00002000
	#घोषणा LINK_SFP_EEPROM_COMP_CODE_LRM	0x00004000

	u32 reserved5[2];
	u32 link_change_count[PORT_MAX];        /* Offset 0x160-0x164 */
	#घोषणा LINK_CHANGE_COUNT_MASK 0xff     /* Offset 0x168 */
	/* driver version क्रम each personality */
	काष्ठा os_drv_ver func_os_drv_ver[E2_FUNC_MAX]; /* Offset 0x16c */

	/* Flag to the driver that PF's drv_info_host_addr buffer was पढ़ो  */
	u32 mfw_drv_indication;

	/* We use indication क्रम each PF (0..3) */
#घोषणा MFW_DRV_IND_READ_DONE_OFFSET(_pf_) (1 << (_pf_))
	जोड़ अणु /* For various OEMs */			/* Offset 0x1a0 */
		u8 storage_boot_prog[E2_FUNC_MAX];
	#घोषणा STORAGE_BOOT_PROG_MASK				0x000000FF
	#घोषणा STORAGE_BOOT_PROG_NONE				0x00000000
	#घोषणा STORAGE_BOOT_PROG_ISCSI_IP_ACQUIRED		0x00000002
	#घोषणा STORAGE_BOOT_PROG_FCOE_FABRIC_LOGIN_SUCCESS	0x00000002
	#घोषणा STORAGE_BOOT_PROG_TARGET_FOUND			0x00000004
	#घोषणा STORAGE_BOOT_PROG_ISCSI_CHAP_SUCCESS		0x00000008
	#घोषणा STORAGE_BOOT_PROG_FCOE_LUN_FOUND		0x00000008
	#घोषणा STORAGE_BOOT_PROG_LOGGED_INTO_TGT		0x00000010
	#घोषणा STORAGE_BOOT_PROG_IMG_DOWNLOADED		0x00000020
	#घोषणा STORAGE_BOOT_PROG_OS_HANDOFF			0x00000040
	#घोषणा STORAGE_BOOT_PROG_COMPLETED			0x00000080

		u32 oem_i2c_data_addr;
	पूर्ण;

	/* 9 entires क्रम the C2S PCP map क्रम each inner VLAN PCP + 1 शेष */
	/* For PCP values 0-3 use the map lower */
	/* 0xFF000000 - PCP 0, 0x00FF0000 - PCP 1,
	 * 0x0000FF00 - PCP 2, 0x000000FF PCP 3
	 */
	u32 c2s_pcp_map_lower[E2_FUNC_MAX];			/* 0x1a4 */

	/* For PCP values 4-7 use the map upper */
	/* 0xFF000000 - PCP 4, 0x00FF0000 - PCP 5,
	 * 0x0000FF00 - PCP 6, 0x000000FF PCP 7
	 */
	u32 c2s_pcp_map_upper[E2_FUNC_MAX];			/* 0x1b4 */

	/* For PCP शेष value get the MSB byte of the map शेष */
	u32 c2s_pcp_map_शेष[E2_FUNC_MAX];			/* 0x1c4 */

	/* FC_NPIV table offset in NVRAM */
	u32 fc_npiv_nvram_tbl_addr[PORT_MAX];			/* 0x1d4 */

	/* Shows last method that changed configuration of this device */
	क्रमागत curr_cfg_method_e curr_cfg;			/* 0x1dc */

	/* Storm FW version, shold be kept in the क्रमmat 0xMMmmbbdd:
	 * MM - Major, mm - Minor, bb - Build ,dd - Drop
	 */
	u32 netproc_fw_ver;					/* 0x1e0 */

	/* Option ROM SMASH CLP version */
	u32 clp_ver;						/* 0x1e4 */

	u32 pcie_bus_num;					/* 0x1e8 */

	u32 sriov_चयन_mode;					/* 0x1ec */
	#घोषणा SRIOV_SWITCH_MODE_NONE		0x0
	#घोषणा SRIOV_SWITCH_MODE_VEB		0x1
	#घोषणा SRIOV_SWITCH_MODE_VEPA		0x2

	u8  rsrv2[E2_FUNC_MAX];					/* 0x1f0 */

	u32 img_inv_table_addr;	/* Address to INV_TABLE_P */	/* 0x1f4 */

	u32 mtu_size[E2_FUNC_MAX];				/* 0x1f8 */

	u32 os_driver_state[E2_FUNC_MAX];			/* 0x208 */
	#घोषणा OS_DRIVER_STATE_NOT_LOADED	0 /* not installed */
	#घोषणा OS_DRIVER_STATE_LOADING		1 /* transition state */
	#घोषणा OS_DRIVER_STATE_DISABLED	2 /* installed but disabled */
	#घोषणा OS_DRIVER_STATE_ACTIVE		3 /* installed and active */

	/* mini dump driver info */
	काष्ठा mdump_driver_info drv_info;			/* 0x218 */
पूर्ण;


काष्ठा emac_stats अणु
	u32     rx_stat_अगरhcinoctets;
	u32     rx_stat_अगरhcinbaकरोctets;
	u32     rx_stat_etherstatsfragments;
	u32     rx_stat_अगरhcinucastpkts;
	u32     rx_stat_अगरhcinmulticastpkts;
	u32     rx_stat_अगरhcinbroadcastpkts;
	u32     rx_stat_करोt3statsfcserrors;
	u32     rx_stat_करोt3statsalignmenterrors;
	u32     rx_stat_करोt3statscarriersenseerrors;
	u32     rx_stat_xonछोड़ोframesreceived;
	u32     rx_stat_xoffछोड़ोframesreceived;
	u32     rx_stat_maccontrolframesreceived;
	u32     rx_stat_xofख_स्थितिeentered;
	u32     rx_stat_करोt3statsframestooदीर्घ;
	u32     rx_stat_etherstatsjabbers;
	u32     rx_stat_etherstatsundersizepkts;
	u32     rx_stat_etherstatspkts64octets;
	u32     rx_stat_etherstatspkts65octetsto127octets;
	u32     rx_stat_etherstatspkts128octetsto255octets;
	u32     rx_stat_etherstatspkts256octetsto511octets;
	u32     rx_stat_etherstatspkts512octetsto1023octets;
	u32     rx_stat_etherstatspkts1024octetsto1522octets;
	u32     rx_stat_etherstatspktsover1522octets;

	u32     rx_stat_falsecarriererrors;

	u32     tx_stat_अगरhcoutoctets;
	u32     tx_stat_अगरhcoutbaकरोctets;
	u32     tx_stat_etherstatscollisions;
	u32     tx_stat_outxonsent;
	u32     tx_stat_outxoffsent;
	u32     tx_stat_flowcontrolकरोne;
	u32     tx_stat_करोt3statssinglecollisionframes;
	u32     tx_stat_करोt3statsmultiplecollisionframes;
	u32     tx_stat_करोt3statsdeferredtransmissions;
	u32     tx_stat_करोt3statsexcessivecollisions;
	u32     tx_stat_करोt3statslatecollisions;
	u32     tx_stat_अगरhcoutucastpkts;
	u32     tx_stat_अगरhcouपंचांगulticastpkts;
	u32     tx_stat_अगरhcoutbroadcastpkts;
	u32     tx_stat_etherstatspkts64octets;
	u32     tx_stat_etherstatspkts65octetsto127octets;
	u32     tx_stat_etherstatspkts128octetsto255octets;
	u32     tx_stat_etherstatspkts256octetsto511octets;
	u32     tx_stat_etherstatspkts512octetsto1023octets;
	u32     tx_stat_etherstatspkts1024octetsto1522octets;
	u32     tx_stat_etherstatspktsover1522octets;
	u32     tx_stat_करोt3statsपूर्णांकernalmactransmiterrors;
पूर्ण;


काष्ठा bmac1_stats अणु
	u32	tx_stat_gtpkt_lo;
	u32	tx_stat_gtpkt_hi;
	u32	tx_stat_gtxpf_lo;
	u32	tx_stat_gtxpf_hi;
	u32	tx_stat_gtfcs_lo;
	u32	tx_stat_gtfcs_hi;
	u32	tx_stat_gपंचांगca_lo;
	u32	tx_stat_gपंचांगca_hi;
	u32	tx_stat_gtbca_lo;
	u32	tx_stat_gtbca_hi;
	u32	tx_stat_gtfrg_lo;
	u32	tx_stat_gtfrg_hi;
	u32	tx_stat_gtovr_lo;
	u32	tx_stat_gtovr_hi;
	u32	tx_stat_gt64_lo;
	u32	tx_stat_gt64_hi;
	u32	tx_stat_gt127_lo;
	u32	tx_stat_gt127_hi;
	u32	tx_stat_gt255_lo;
	u32	tx_stat_gt255_hi;
	u32	tx_stat_gt511_lo;
	u32	tx_stat_gt511_hi;
	u32	tx_stat_gt1023_lo;
	u32	tx_stat_gt1023_hi;
	u32	tx_stat_gt1518_lo;
	u32	tx_stat_gt1518_hi;
	u32	tx_stat_gt2047_lo;
	u32	tx_stat_gt2047_hi;
	u32	tx_stat_gt4095_lo;
	u32	tx_stat_gt4095_hi;
	u32	tx_stat_gt9216_lo;
	u32	tx_stat_gt9216_hi;
	u32	tx_stat_gt16383_lo;
	u32	tx_stat_gt16383_hi;
	u32	tx_stat_gपंचांगax_lo;
	u32	tx_stat_gपंचांगax_hi;
	u32	tx_stat_gtufl_lo;
	u32	tx_stat_gtufl_hi;
	u32	tx_stat_gterr_lo;
	u32	tx_stat_gterr_hi;
	u32	tx_stat_gtbyt_lo;
	u32	tx_stat_gtbyt_hi;

	u32	rx_stat_gr64_lo;
	u32	rx_stat_gr64_hi;
	u32	rx_stat_gr127_lo;
	u32	rx_stat_gr127_hi;
	u32	rx_stat_gr255_lo;
	u32	rx_stat_gr255_hi;
	u32	rx_stat_gr511_lo;
	u32	rx_stat_gr511_hi;
	u32	rx_stat_gr1023_lo;
	u32	rx_stat_gr1023_hi;
	u32	rx_stat_gr1518_lo;
	u32	rx_stat_gr1518_hi;
	u32	rx_stat_gr2047_lo;
	u32	rx_stat_gr2047_hi;
	u32	rx_stat_gr4095_lo;
	u32	rx_stat_gr4095_hi;
	u32	rx_stat_gr9216_lo;
	u32	rx_stat_gr9216_hi;
	u32	rx_stat_gr16383_lo;
	u32	rx_stat_gr16383_hi;
	u32	rx_stat_grmax_lo;
	u32	rx_stat_grmax_hi;
	u32	rx_stat_grpkt_lo;
	u32	rx_stat_grpkt_hi;
	u32	rx_stat_grfcs_lo;
	u32	rx_stat_grfcs_hi;
	u32	rx_stat_grmca_lo;
	u32	rx_stat_grmca_hi;
	u32	rx_stat_grbca_lo;
	u32	rx_stat_grbca_hi;
	u32	rx_stat_grxcf_lo;
	u32	rx_stat_grxcf_hi;
	u32	rx_stat_grxpf_lo;
	u32	rx_stat_grxpf_hi;
	u32	rx_stat_grxuo_lo;
	u32	rx_stat_grxuo_hi;
	u32	rx_stat_grjbr_lo;
	u32	rx_stat_grjbr_hi;
	u32	rx_stat_grovr_lo;
	u32	rx_stat_grovr_hi;
	u32	rx_stat_grflr_lo;
	u32	rx_stat_grflr_hi;
	u32	rx_stat_grmeg_lo;
	u32	rx_stat_grmeg_hi;
	u32	rx_stat_grmeb_lo;
	u32	rx_stat_grmeb_hi;
	u32	rx_stat_grbyt_lo;
	u32	rx_stat_grbyt_hi;
	u32	rx_stat_grund_lo;
	u32	rx_stat_grund_hi;
	u32	rx_stat_grfrg_lo;
	u32	rx_stat_grfrg_hi;
	u32	rx_stat_grerb_lo;
	u32	rx_stat_grerb_hi;
	u32	rx_stat_grfre_lo;
	u32	rx_stat_grfre_hi;
	u32	rx_stat_gripj_lo;
	u32	rx_stat_gripj_hi;
पूर्ण;

काष्ठा bmac2_stats अणु
	u32	tx_stat_gtpk_lo; /* gtpok */
	u32	tx_stat_gtpk_hi; /* gtpok */
	u32	tx_stat_gtxpf_lo; /* gtpf */
	u32	tx_stat_gtxpf_hi; /* gtpf */
	u32	tx_stat_gtpp_lo; /* NEW BMAC2 */
	u32	tx_stat_gtpp_hi; /* NEW BMAC2 */
	u32	tx_stat_gtfcs_lo;
	u32	tx_stat_gtfcs_hi;
	u32	tx_stat_gtuca_lo; /* NEW BMAC2 */
	u32	tx_stat_gtuca_hi; /* NEW BMAC2 */
	u32	tx_stat_gपंचांगca_lo;
	u32	tx_stat_gपंचांगca_hi;
	u32	tx_stat_gtbca_lo;
	u32	tx_stat_gtbca_hi;
	u32	tx_stat_gtovr_lo;
	u32	tx_stat_gtovr_hi;
	u32	tx_stat_gtfrg_lo;
	u32	tx_stat_gtfrg_hi;
	u32	tx_stat_gtpkt1_lo; /* gtpkt */
	u32	tx_stat_gtpkt1_hi; /* gtpkt */
	u32	tx_stat_gt64_lo;
	u32	tx_stat_gt64_hi;
	u32	tx_stat_gt127_lo;
	u32	tx_stat_gt127_hi;
	u32	tx_stat_gt255_lo;
	u32	tx_stat_gt255_hi;
	u32	tx_stat_gt511_lo;
	u32	tx_stat_gt511_hi;
	u32	tx_stat_gt1023_lo;
	u32	tx_stat_gt1023_hi;
	u32	tx_stat_gt1518_lo;
	u32	tx_stat_gt1518_hi;
	u32	tx_stat_gt2047_lo;
	u32	tx_stat_gt2047_hi;
	u32	tx_stat_gt4095_lo;
	u32	tx_stat_gt4095_hi;
	u32	tx_stat_gt9216_lo;
	u32	tx_stat_gt9216_hi;
	u32	tx_stat_gt16383_lo;
	u32	tx_stat_gt16383_hi;
	u32	tx_stat_gपंचांगax_lo;
	u32	tx_stat_gपंचांगax_hi;
	u32	tx_stat_gtufl_lo;
	u32	tx_stat_gtufl_hi;
	u32	tx_stat_gterr_lo;
	u32	tx_stat_gterr_hi;
	u32	tx_stat_gtbyt_lo;
	u32	tx_stat_gtbyt_hi;

	u32	rx_stat_gr64_lo;
	u32	rx_stat_gr64_hi;
	u32	rx_stat_gr127_lo;
	u32	rx_stat_gr127_hi;
	u32	rx_stat_gr255_lo;
	u32	rx_stat_gr255_hi;
	u32	rx_stat_gr511_lo;
	u32	rx_stat_gr511_hi;
	u32	rx_stat_gr1023_lo;
	u32	rx_stat_gr1023_hi;
	u32	rx_stat_gr1518_lo;
	u32	rx_stat_gr1518_hi;
	u32	rx_stat_gr2047_lo;
	u32	rx_stat_gr2047_hi;
	u32	rx_stat_gr4095_lo;
	u32	rx_stat_gr4095_hi;
	u32	rx_stat_gr9216_lo;
	u32	rx_stat_gr9216_hi;
	u32	rx_stat_gr16383_lo;
	u32	rx_stat_gr16383_hi;
	u32	rx_stat_grmax_lo;
	u32	rx_stat_grmax_hi;
	u32	rx_stat_grpkt_lo;
	u32	rx_stat_grpkt_hi;
	u32	rx_stat_grfcs_lo;
	u32	rx_stat_grfcs_hi;
	u32	rx_stat_gruca_lo;
	u32	rx_stat_gruca_hi;
	u32	rx_stat_grmca_lo;
	u32	rx_stat_grmca_hi;
	u32	rx_stat_grbca_lo;
	u32	rx_stat_grbca_hi;
	u32	rx_stat_grxpf_lo; /* grpf */
	u32	rx_stat_grxpf_hi; /* grpf */
	u32	rx_stat_grpp_lo;
	u32	rx_stat_grpp_hi;
	u32	rx_stat_grxuo_lo; /* gruo */
	u32	rx_stat_grxuo_hi; /* gruo */
	u32	rx_stat_grjbr_lo;
	u32	rx_stat_grjbr_hi;
	u32	rx_stat_grovr_lo;
	u32	rx_stat_grovr_hi;
	u32	rx_stat_grxcf_lo; /* grcf */
	u32	rx_stat_grxcf_hi; /* grcf */
	u32	rx_stat_grflr_lo;
	u32	rx_stat_grflr_hi;
	u32	rx_stat_grpok_lo;
	u32	rx_stat_grpok_hi;
	u32	rx_stat_grmeg_lo;
	u32	rx_stat_grmeg_hi;
	u32	rx_stat_grmeb_lo;
	u32	rx_stat_grmeb_hi;
	u32	rx_stat_grbyt_lo;
	u32	rx_stat_grbyt_hi;
	u32	rx_stat_grund_lo;
	u32	rx_stat_grund_hi;
	u32	rx_stat_grfrg_lo;
	u32	rx_stat_grfrg_hi;
	u32	rx_stat_grerb_lo; /* grerrbyt */
	u32	rx_stat_grerb_hi; /* grerrbyt */
	u32	rx_stat_grfre_lo; /* grfrerr */
	u32	rx_stat_grfre_hi; /* grfrerr */
	u32	rx_stat_gripj_lo;
	u32	rx_stat_gripj_hi;
पूर्ण;

काष्ठा mstat_stats अणु
	काष्ठा अणु
		/* OTE MSTAT on E3 has a bug where this रेजिस्टर's contents are
		 * actually tx_gtxpok + tx_gtxpf + (possibly)tx_gtxpp
		 */
		u32 tx_gtxpok_lo;
		u32 tx_gtxpok_hi;
		u32 tx_gtxpf_lo;
		u32 tx_gtxpf_hi;
		u32 tx_gtxpp_lo;
		u32 tx_gtxpp_hi;
		u32 tx_gtfcs_lo;
		u32 tx_gtfcs_hi;
		u32 tx_gtuca_lo;
		u32 tx_gtuca_hi;
		u32 tx_gपंचांगca_lo;
		u32 tx_gपंचांगca_hi;
		u32 tx_gtgca_lo;
		u32 tx_gtgca_hi;
		u32 tx_gtpkt_lo;
		u32 tx_gtpkt_hi;
		u32 tx_gt64_lo;
		u32 tx_gt64_hi;
		u32 tx_gt127_lo;
		u32 tx_gt127_hi;
		u32 tx_gt255_lo;
		u32 tx_gt255_hi;
		u32 tx_gt511_lo;
		u32 tx_gt511_hi;
		u32 tx_gt1023_lo;
		u32 tx_gt1023_hi;
		u32 tx_gt1518_lo;
		u32 tx_gt1518_hi;
		u32 tx_gt2047_lo;
		u32 tx_gt2047_hi;
		u32 tx_gt4095_lo;
		u32 tx_gt4095_hi;
		u32 tx_gt9216_lo;
		u32 tx_gt9216_hi;
		u32 tx_gt16383_lo;
		u32 tx_gt16383_hi;
		u32 tx_gtufl_lo;
		u32 tx_gtufl_hi;
		u32 tx_gterr_lo;
		u32 tx_gterr_hi;
		u32 tx_gtbyt_lo;
		u32 tx_gtbyt_hi;
		u32 tx_collisions_lo;
		u32 tx_collisions_hi;
		u32 tx_singlecollision_lo;
		u32 tx_singlecollision_hi;
		u32 tx_multiplecollisions_lo;
		u32 tx_multiplecollisions_hi;
		u32 tx_deferred_lo;
		u32 tx_deferred_hi;
		u32 tx_excessivecollisions_lo;
		u32 tx_excessivecollisions_hi;
		u32 tx_latecollisions_lo;
		u32 tx_latecollisions_hi;
	पूर्ण stats_tx;

	काष्ठा अणु
		u32 rx_gr64_lo;
		u32 rx_gr64_hi;
		u32 rx_gr127_lo;
		u32 rx_gr127_hi;
		u32 rx_gr255_lo;
		u32 rx_gr255_hi;
		u32 rx_gr511_lo;
		u32 rx_gr511_hi;
		u32 rx_gr1023_lo;
		u32 rx_gr1023_hi;
		u32 rx_gr1518_lo;
		u32 rx_gr1518_hi;
		u32 rx_gr2047_lo;
		u32 rx_gr2047_hi;
		u32 rx_gr4095_lo;
		u32 rx_gr4095_hi;
		u32 rx_gr9216_lo;
		u32 rx_gr9216_hi;
		u32 rx_gr16383_lo;
		u32 rx_gr16383_hi;
		u32 rx_grpkt_lo;
		u32 rx_grpkt_hi;
		u32 rx_grfcs_lo;
		u32 rx_grfcs_hi;
		u32 rx_gruca_lo;
		u32 rx_gruca_hi;
		u32 rx_grmca_lo;
		u32 rx_grmca_hi;
		u32 rx_grbca_lo;
		u32 rx_grbca_hi;
		u32 rx_grxpf_lo;
		u32 rx_grxpf_hi;
		u32 rx_grxpp_lo;
		u32 rx_grxpp_hi;
		u32 rx_grxuo_lo;
		u32 rx_grxuo_hi;
		u32 rx_grovr_lo;
		u32 rx_grovr_hi;
		u32 rx_grxcf_lo;
		u32 rx_grxcf_hi;
		u32 rx_grflr_lo;
		u32 rx_grflr_hi;
		u32 rx_grpok_lo;
		u32 rx_grpok_hi;
		u32 rx_grbyt_lo;
		u32 rx_grbyt_hi;
		u32 rx_grund_lo;
		u32 rx_grund_hi;
		u32 rx_grfrg_lo;
		u32 rx_grfrg_hi;
		u32 rx_grerb_lo;
		u32 rx_grerb_hi;
		u32 rx_grfre_lo;
		u32 rx_grfre_hi;

		u32 rx_alignmenterrors_lo;
		u32 rx_alignmenterrors_hi;
		u32 rx_falsecarrier_lo;
		u32 rx_falsecarrier_hi;
		u32 rx_llfcmsgcnt_lo;
		u32 rx_llfcmsgcnt_hi;
	पूर्ण stats_rx;
पूर्ण;

जोड़ mac_stats अणु
	काष्ठा emac_stats	emac_stats;
	काष्ठा bmac1_stats	bmac1_stats;
	काष्ठा bmac2_stats	bmac2_stats;
	काष्ठा mstat_stats	mstat_stats;
पूर्ण;


काष्ठा mac_stx अणु
	/* in_bad_octets */
	u32     rx_stat_अगरhcinbaकरोctets_hi;
	u32     rx_stat_अगरhcinbaकरोctets_lo;

	/* out_bad_octets */
	u32     tx_stat_अगरhcoutbaकरोctets_hi;
	u32     tx_stat_अगरhcoutbaकरोctets_lo;

	/* crc_receive_errors */
	u32     rx_stat_करोt3statsfcserrors_hi;
	u32     rx_stat_करोt3statsfcserrors_lo;
	/* alignment_errors */
	u32     rx_stat_करोt3statsalignmenterrors_hi;
	u32     rx_stat_करोt3statsalignmenterrors_lo;
	/* carrier_sense_errors */
	u32     rx_stat_करोt3statscarriersenseerrors_hi;
	u32     rx_stat_करोt3statscarriersenseerrors_lo;
	/* false_carrier_detections */
	u32     rx_stat_falsecarriererrors_hi;
	u32     rx_stat_falsecarriererrors_lo;

	/* runt_packets_received */
	u32     rx_stat_etherstatsundersizepkts_hi;
	u32     rx_stat_etherstatsundersizepkts_lo;
	/* jabber_packets_received */
	u32     rx_stat_करोt3statsframestooदीर्घ_hi;
	u32     rx_stat_करोt3statsframestooदीर्घ_lo;

	/* error_runt_packets_received */
	u32     rx_stat_etherstatsfragments_hi;
	u32     rx_stat_etherstatsfragments_lo;
	/* error_jabber_packets_received */
	u32     rx_stat_etherstatsjabbers_hi;
	u32     rx_stat_etherstatsjabbers_lo;

	/* control_frames_received */
	u32     rx_stat_maccontrolframesreceived_hi;
	u32     rx_stat_maccontrolframesreceived_lo;
	u32     rx_stat_mac_xpf_hi;
	u32     rx_stat_mac_xpf_lo;
	u32     rx_stat_mac_xcf_hi;
	u32     rx_stat_mac_xcf_lo;

	/* xoff_state_entered */
	u32     rx_stat_xofख_स्थितिeentered_hi;
	u32     rx_stat_xofख_स्थितिeentered_lo;
	/* छोड़ो_xon_frames_received */
	u32     rx_stat_xonछोड़ोframesreceived_hi;
	u32     rx_stat_xonछोड़ोframesreceived_lo;
	/* छोड़ो_xoff_frames_received */
	u32     rx_stat_xoffछोड़ोframesreceived_hi;
	u32     rx_stat_xoffछोड़ोframesreceived_lo;
	/* छोड़ो_xon_frames_transmitted */
	u32     tx_stat_outxonsent_hi;
	u32     tx_stat_outxonsent_lo;
	/* छोड़ो_xoff_frames_transmitted */
	u32     tx_stat_outxoffsent_hi;
	u32     tx_stat_outxoffsent_lo;
	/* flow_control_करोne */
	u32     tx_stat_flowcontrolकरोne_hi;
	u32     tx_stat_flowcontrolकरोne_lo;

	/* ether_stats_collisions */
	u32     tx_stat_etherstatscollisions_hi;
	u32     tx_stat_etherstatscollisions_lo;
	/* single_collision_transmit_frames */
	u32     tx_stat_करोt3statssinglecollisionframes_hi;
	u32     tx_stat_करोt3statssinglecollisionframes_lo;
	/* multiple_collision_transmit_frames */
	u32     tx_stat_करोt3statsmultiplecollisionframes_hi;
	u32     tx_stat_करोt3statsmultiplecollisionframes_lo;
	/* deferred_transmissions */
	u32     tx_stat_करोt3statsdeferredtransmissions_hi;
	u32     tx_stat_करोt3statsdeferredtransmissions_lo;
	/* excessive_collision_frames */
	u32     tx_stat_करोt3statsexcessivecollisions_hi;
	u32     tx_stat_करोt3statsexcessivecollisions_lo;
	/* late_collision_frames */
	u32     tx_stat_करोt3statslatecollisions_hi;
	u32     tx_stat_करोt3statslatecollisions_lo;

	/* frames_transmitted_64_bytes */
	u32     tx_stat_etherstatspkts64octets_hi;
	u32     tx_stat_etherstatspkts64octets_lo;
	/* frames_transmitted_65_127_bytes */
	u32     tx_stat_etherstatspkts65octetsto127octets_hi;
	u32     tx_stat_etherstatspkts65octetsto127octets_lo;
	/* frames_transmitted_128_255_bytes */
	u32     tx_stat_etherstatspkts128octetsto255octets_hi;
	u32     tx_stat_etherstatspkts128octetsto255octets_lo;
	/* frames_transmitted_256_511_bytes */
	u32     tx_stat_etherstatspkts256octetsto511octets_hi;
	u32     tx_stat_etherstatspkts256octetsto511octets_lo;
	/* frames_transmitted_512_1023_bytes */
	u32     tx_stat_etherstatspkts512octetsto1023octets_hi;
	u32     tx_stat_etherstatspkts512octetsto1023octets_lo;
	/* frames_transmitted_1024_1522_bytes */
	u32     tx_stat_etherstatspkts1024octetsto1522octets_hi;
	u32     tx_stat_etherstatspkts1024octetsto1522octets_lo;
	/* frames_transmitted_1523_9022_bytes */
	u32     tx_stat_etherstatspktsover1522octets_hi;
	u32     tx_stat_etherstatspktsover1522octets_lo;
	u32     tx_stat_mac_2047_hi;
	u32     tx_stat_mac_2047_lo;
	u32     tx_stat_mac_4095_hi;
	u32     tx_stat_mac_4095_lo;
	u32     tx_stat_mac_9216_hi;
	u32     tx_stat_mac_9216_lo;
	u32     tx_stat_mac_16383_hi;
	u32     tx_stat_mac_16383_lo;

	/* पूर्णांकernal_mac_transmit_errors */
	u32     tx_stat_करोt3statsपूर्णांकernalmactransmiterrors_hi;
	u32     tx_stat_करोt3statsपूर्णांकernalmactransmiterrors_lo;

	/* अगर_out_discards */
	u32     tx_stat_mac_ufl_hi;
	u32     tx_stat_mac_ufl_lo;
पूर्ण;


#घोषणा MAC_STX_IDX_MAX                     2

काष्ठा host_port_stats अणु
	u32            host_port_stats_counter;

	काष्ठा mac_stx mac_stx[MAC_STX_IDX_MAX];

	u32            brb_drop_hi;
	u32            brb_drop_lo;

	u32            not_used; /* obsolete */
	u32            pfc_frames_tx_hi;
	u32            pfc_frames_tx_lo;
	u32            pfc_frames_rx_hi;
	u32            pfc_frames_rx_lo;

	u32            eee_lpi_count_hi;
	u32            eee_lpi_count_lo;
पूर्ण;


काष्ठा host_func_stats अणु
	u32     host_func_stats_start;

	u32     total_bytes_received_hi;
	u32     total_bytes_received_lo;

	u32     total_bytes_transmitted_hi;
	u32     total_bytes_transmitted_lo;

	u32     total_unicast_packets_received_hi;
	u32     total_unicast_packets_received_lo;

	u32     total_multicast_packets_received_hi;
	u32     total_multicast_packets_received_lo;

	u32     total_broadcast_packets_received_hi;
	u32     total_broadcast_packets_received_lo;

	u32     total_unicast_packets_transmitted_hi;
	u32     total_unicast_packets_transmitted_lo;

	u32     total_multicast_packets_transmitted_hi;
	u32     total_multicast_packets_transmitted_lo;

	u32     total_broadcast_packets_transmitted_hi;
	u32     total_broadcast_packets_transmitted_lo;

	u32     valid_bytes_received_hi;
	u32     valid_bytes_received_lo;

	u32     host_func_stats_end;
पूर्ण;

/* VIC definitions */
#घोषणा VICSTATST_UIF_INDEX 2


/* stats collected क्रम afex.
 * NOTE: काष्ठाure is exactly as expected to be received by the चयन.
 *       order must reमुख्य exactly as is unless protocol changes !
 */
काष्ठा afex_stats अणु
	u32 tx_unicast_frames_hi;
	u32 tx_unicast_frames_lo;
	u32 tx_unicast_bytes_hi;
	u32 tx_unicast_bytes_lo;
	u32 tx_multicast_frames_hi;
	u32 tx_multicast_frames_lo;
	u32 tx_multicast_bytes_hi;
	u32 tx_multicast_bytes_lo;
	u32 tx_broadcast_frames_hi;
	u32 tx_broadcast_frames_lo;
	u32 tx_broadcast_bytes_hi;
	u32 tx_broadcast_bytes_lo;
	u32 tx_frames_discarded_hi;
	u32 tx_frames_discarded_lo;
	u32 tx_frames_dropped_hi;
	u32 tx_frames_dropped_lo;

	u32 rx_unicast_frames_hi;
	u32 rx_unicast_frames_lo;
	u32 rx_unicast_bytes_hi;
	u32 rx_unicast_bytes_lo;
	u32 rx_multicast_frames_hi;
	u32 rx_multicast_frames_lo;
	u32 rx_multicast_bytes_hi;
	u32 rx_multicast_bytes_lo;
	u32 rx_broadcast_frames_hi;
	u32 rx_broadcast_frames_lo;
	u32 rx_broadcast_bytes_hi;
	u32 rx_broadcast_bytes_lo;
	u32 rx_frames_discarded_hi;
	u32 rx_frames_discarded_lo;
	u32 rx_frames_dropped_hi;
	u32 rx_frames_dropped_lo;
पूर्ण;

#घोषणा BCM_5710_FW_MAJOR_VERSION			7
#घोषणा BCM_5710_FW_MINOR_VERSION			13
#घोषणा BCM_5710_FW_REVISION_VERSION		15
#घोषणा BCM_5710_FW_ENGINEERING_VERSION		0
#घोषणा BCM_5710_FW_COMPILE_FLAGS			1


/*
 * attention bits
 */
काष्ठा atten_sp_status_block अणु
	__le32 attn_bits;
	__le32 attn_bits_ack;
	u8 status_block_id;
	u8 reserved0;
	__le16 attn_bits_index;
	__le32 reserved1;
पूर्ण;


/*
 * The eth aggregative context of Cstorm
 */
काष्ठा cstorm_eth_ag_context अणु
	u32 __reserved0[10];
पूर्ण;


/*
 * dmae command काष्ठाure
 */
काष्ठा dmae_command अणु
	u32 opcode;
#घोषणा DMAE_COMMAND_SRC (0x1<<0)
#घोषणा DMAE_COMMAND_SRC_SHIFT 0
#घोषणा DMAE_COMMAND_DST (0x3<<1)
#घोषणा DMAE_COMMAND_DST_SHIFT 1
#घोषणा DMAE_COMMAND_C_DST (0x1<<3)
#घोषणा DMAE_COMMAND_C_DST_SHIFT 3
#घोषणा DMAE_COMMAND_C_TYPE_ENABLE (0x1<<4)
#घोषणा DMAE_COMMAND_C_TYPE_ENABLE_SHIFT 4
#घोषणा DMAE_COMMAND_C_TYPE_CRC_ENABLE (0x1<<5)
#घोषणा DMAE_COMMAND_C_TYPE_CRC_ENABLE_SHIFT 5
#घोषणा DMAE_COMMAND_C_TYPE_CRC_OFFSET (0x7<<6)
#घोषणा DMAE_COMMAND_C_TYPE_CRC_OFFSET_SHIFT 6
#घोषणा DMAE_COMMAND_ENDIANITY (0x3<<9)
#घोषणा DMAE_COMMAND_ENDIANITY_SHIFT 9
#घोषणा DMAE_COMMAND_PORT (0x1<<11)
#घोषणा DMAE_COMMAND_PORT_SHIFT 11
#घोषणा DMAE_COMMAND_CRC_RESET (0x1<<12)
#घोषणा DMAE_COMMAND_CRC_RESET_SHIFT 12
#घोषणा DMAE_COMMAND_SRC_RESET (0x1<<13)
#घोषणा DMAE_COMMAND_SRC_RESET_SHIFT 13
#घोषणा DMAE_COMMAND_DST_RESET (0x1<<14)
#घोषणा DMAE_COMMAND_DST_RESET_SHIFT 14
#घोषणा DMAE_COMMAND_E1HVN (0x3<<15)
#घोषणा DMAE_COMMAND_E1HVN_SHIFT 15
#घोषणा DMAE_COMMAND_DST_VN (0x3<<17)
#घोषणा DMAE_COMMAND_DST_VN_SHIFT 17
#घोषणा DMAE_COMMAND_C_FUNC (0x1<<19)
#घोषणा DMAE_COMMAND_C_FUNC_SHIFT 19
#घोषणा DMAE_COMMAND_ERR_POLICY (0x3<<20)
#घोषणा DMAE_COMMAND_ERR_POLICY_SHIFT 20
#घोषणा DMAE_COMMAND_RESERVED0 (0x3FF<<22)
#घोषणा DMAE_COMMAND_RESERVED0_SHIFT 22
	u32 src_addr_lo;
	u32 src_addr_hi;
	u32 dst_addr_lo;
	u32 dst_addr_hi;
#अगर defined(__BIG_ENDIAN)
	u16 opcode_iov;
#घोषणा DMAE_COMMAND_SRC_VFID (0x3F<<0)
#घोषणा DMAE_COMMAND_SRC_VFID_SHIFT 0
#घोषणा DMAE_COMMAND_SRC_VFPF (0x1<<6)
#घोषणा DMAE_COMMAND_SRC_VFPF_SHIFT 6
#घोषणा DMAE_COMMAND_RESERVED1 (0x1<<7)
#घोषणा DMAE_COMMAND_RESERVED1_SHIFT 7
#घोषणा DMAE_COMMAND_DST_VFID (0x3F<<8)
#घोषणा DMAE_COMMAND_DST_VFID_SHIFT 8
#घोषणा DMAE_COMMAND_DST_VFPF (0x1<<14)
#घोषणा DMAE_COMMAND_DST_VFPF_SHIFT 14
#घोषणा DMAE_COMMAND_RESERVED2 (0x1<<15)
#घोषणा DMAE_COMMAND_RESERVED2_SHIFT 15
	u16 len;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 len;
	u16 opcode_iov;
#घोषणा DMAE_COMMAND_SRC_VFID (0x3F<<0)
#घोषणा DMAE_COMMAND_SRC_VFID_SHIFT 0
#घोषणा DMAE_COMMAND_SRC_VFPF (0x1<<6)
#घोषणा DMAE_COMMAND_SRC_VFPF_SHIFT 6
#घोषणा DMAE_COMMAND_RESERVED1 (0x1<<7)
#घोषणा DMAE_COMMAND_RESERVED1_SHIFT 7
#घोषणा DMAE_COMMAND_DST_VFID (0x3F<<8)
#घोषणा DMAE_COMMAND_DST_VFID_SHIFT 8
#घोषणा DMAE_COMMAND_DST_VFPF (0x1<<14)
#घोषणा DMAE_COMMAND_DST_VFPF_SHIFT 14
#घोषणा DMAE_COMMAND_RESERVED2 (0x1<<15)
#घोषणा DMAE_COMMAND_RESERVED2_SHIFT 15
#पूर्ण_अगर
	u32 comp_addr_lo;
	u32 comp_addr_hi;
	u32 comp_val;
	u32 crc32;
	u32 crc32_c;
#अगर defined(__BIG_ENDIAN)
	u16 crc16_c;
	u16 crc16;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 crc16;
	u16 crc16_c;
#पूर्ण_अगर
#अगर defined(__BIG_ENDIAN)
	u16 reserved3;
	u16 crc_t10;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 crc_t10;
	u16 reserved3;
#पूर्ण_अगर
#अगर defined(__BIG_ENDIAN)
	u16 xsum8;
	u16 xsum16;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 xsum16;
	u16 xsum8;
#पूर्ण_अगर
पूर्ण;


/*
 * common data क्रम all protocols
 */
काष्ठा करोorbell_hdr अणु
	u8 header;
#घोषणा DOORBELL_HDR_RX (0x1<<0)
#घोषणा DOORBELL_HDR_RX_SHIFT 0
#घोषणा DOORBELL_HDR_DB_TYPE (0x1<<1)
#घोषणा DOORBELL_HDR_DB_TYPE_SHIFT 1
#घोषणा DOORBELL_HDR_DPM_SIZE (0x3<<2)
#घोषणा DOORBELL_HDR_DPM_SIZE_SHIFT 2
#घोषणा DOORBELL_HDR_CONN_TYPE (0xF<<4)
#घोषणा DOORBELL_HDR_CONN_TYPE_SHIFT 4
पूर्ण;

/*
 * Ethernet करोorbell
 */
काष्ठा eth_tx_करोorbell अणु
#अगर defined(__BIG_ENDIAN)
	u16 npackets;
	u8 params;
#घोषणा ETH_TX_DOORBELL_NUM_BDS (0x3F<<0)
#घोषणा ETH_TX_DOORBELL_NUM_BDS_SHIFT 0
#घोषणा ETH_TX_DOORBELL_RESERVED_TX_FIN_FLAG (0x1<<6)
#घोषणा ETH_TX_DOORBELL_RESERVED_TX_FIN_FLAG_SHIFT 6
#घोषणा ETH_TX_DOORBELL_SPARE (0x1<<7)
#घोषणा ETH_TX_DOORBELL_SPARE_SHIFT 7
	काष्ठा करोorbell_hdr hdr;
#या_अगर defined(__LITTLE_ENDIAN)
	काष्ठा करोorbell_hdr hdr;
	u8 params;
#घोषणा ETH_TX_DOORBELL_NUM_BDS (0x3F<<0)
#घोषणा ETH_TX_DOORBELL_NUM_BDS_SHIFT 0
#घोषणा ETH_TX_DOORBELL_RESERVED_TX_FIN_FLAG (0x1<<6)
#घोषणा ETH_TX_DOORBELL_RESERVED_TX_FIN_FLAG_SHIFT 6
#घोषणा ETH_TX_DOORBELL_SPARE (0x1<<7)
#घोषणा ETH_TX_DOORBELL_SPARE_SHIFT 7
	u16 npackets;
#पूर्ण_अगर
पूर्ण;


/*
 * 3 lines. status block
 */
काष्ठा hc_status_block_e1x अणु
	__le16 index_values[HC_SB_MAX_INDICES_E1X];
	__le16 running_index[HC_SB_MAX_SM];
	__le32 rsrv[11];
पूर्ण;

/*
 * host status block
 */
काष्ठा host_hc_status_block_e1x अणु
	काष्ठा hc_status_block_e1x sb;
पूर्ण;


/*
 * 3 lines. status block
 */
काष्ठा hc_status_block_e2 अणु
	__le16 index_values[HC_SB_MAX_INDICES_E2];
	__le16 running_index[HC_SB_MAX_SM];
	__le32 reserved[11];
पूर्ण;

/*
 * host status block
 */
काष्ठा host_hc_status_block_e2 अणु
	काष्ठा hc_status_block_e2 sb;
पूर्ण;


/*
 * 5 lines. slow-path status block
 */
काष्ठा hc_sp_status_block अणु
	__le16 index_values[HC_SP_SB_MAX_INDICES];
	__le16 running_index;
	__le16 rsrv;
	u32 rsrv1;
पूर्ण;

/*
 * host status block
 */
काष्ठा host_sp_status_block अणु
	काष्ठा atten_sp_status_block atten_status_block;
	काष्ठा hc_sp_status_block sp_sb;
पूर्ण;


/*
 * IGU driver acknowledgment रेजिस्टर
 */
काष्ठा igu_ack_रेजिस्टर अणु
#अगर defined(__BIG_ENDIAN)
	u16 sb_id_and_flags;
#घोषणा IGU_ACK_REGISTER_STATUS_BLOCK_ID (0x1F<<0)
#घोषणा IGU_ACK_REGISTER_STATUS_BLOCK_ID_SHIFT 0
#घोषणा IGU_ACK_REGISTER_STORM_ID (0x7<<5)
#घोषणा IGU_ACK_REGISTER_STORM_ID_SHIFT 5
#घोषणा IGU_ACK_REGISTER_UPDATE_INDEX (0x1<<8)
#घोषणा IGU_ACK_REGISTER_UPDATE_INDEX_SHIFT 8
#घोषणा IGU_ACK_REGISTER_INTERRUPT_MODE (0x3<<9)
#घोषणा IGU_ACK_REGISTER_INTERRUPT_MODE_SHIFT 9
#घोषणा IGU_ACK_REGISTER_RESERVED (0x1F<<11)
#घोषणा IGU_ACK_REGISTER_RESERVED_SHIFT 11
	u16 status_block_index;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 status_block_index;
	u16 sb_id_and_flags;
#घोषणा IGU_ACK_REGISTER_STATUS_BLOCK_ID (0x1F<<0)
#घोषणा IGU_ACK_REGISTER_STATUS_BLOCK_ID_SHIFT 0
#घोषणा IGU_ACK_REGISTER_STORM_ID (0x7<<5)
#घोषणा IGU_ACK_REGISTER_STORM_ID_SHIFT 5
#घोषणा IGU_ACK_REGISTER_UPDATE_INDEX (0x1<<8)
#घोषणा IGU_ACK_REGISTER_UPDATE_INDEX_SHIFT 8
#घोषणा IGU_ACK_REGISTER_INTERRUPT_MODE (0x3<<9)
#घोषणा IGU_ACK_REGISTER_INTERRUPT_MODE_SHIFT 9
#घोषणा IGU_ACK_REGISTER_RESERVED (0x1F<<11)
#घोषणा IGU_ACK_REGISTER_RESERVED_SHIFT 11
#पूर्ण_अगर
पूर्ण;


/*
 * IGU driver acknowledgement रेजिस्टर
 */
काष्ठा igu_backward_compatible अणु
	u32 sb_id_and_flags;
#घोषणा IGU_BACKWARD_COMPATIBLE_SB_INDEX (0xFFFF<<0)
#घोषणा IGU_BACKWARD_COMPATIBLE_SB_INDEX_SHIFT 0
#घोषणा IGU_BACKWARD_COMPATIBLE_SB_SELECT (0x1F<<16)
#घोषणा IGU_BACKWARD_COMPATIBLE_SB_SELECT_SHIFT 16
#घोषणा IGU_BACKWARD_COMPATIBLE_SEGMENT_ACCESS (0x7<<21)
#घोषणा IGU_BACKWARD_COMPATIBLE_SEGMENT_ACCESS_SHIFT 21
#घोषणा IGU_BACKWARD_COMPATIBLE_BUPDATE (0x1<<24)
#घोषणा IGU_BACKWARD_COMPATIBLE_BUPDATE_SHIFT 24
#घोषणा IGU_BACKWARD_COMPATIBLE_ENABLE_INT (0x3<<25)
#घोषणा IGU_BACKWARD_COMPATIBLE_ENABLE_INT_SHIFT 25
#घोषणा IGU_BACKWARD_COMPATIBLE_RESERVED_0 (0x1F<<27)
#घोषणा IGU_BACKWARD_COMPATIBLE_RESERVED_0_SHIFT 27
	u32 reserved_2;
पूर्ण;


/*
 * IGU driver acknowledgement रेजिस्टर
 */
काष्ठा igu_regular अणु
	u32 sb_id_and_flags;
#घोषणा IGU_REGULAR_SB_INDEX (0xFFFFF<<0)
#घोषणा IGU_REGULAR_SB_INDEX_SHIFT 0
#घोषणा IGU_REGULAR_RESERVED0 (0x1<<20)
#घोषणा IGU_REGULAR_RESERVED0_SHIFT 20
#घोषणा IGU_REGULAR_SEGMENT_ACCESS (0x7<<21)
#घोषणा IGU_REGULAR_SEGMENT_ACCESS_SHIFT 21
#घोषणा IGU_REGULAR_BUPDATE (0x1<<24)
#घोषणा IGU_REGULAR_BUPDATE_SHIFT 24
#घोषणा IGU_REGULAR_ENABLE_INT (0x3<<25)
#घोषणा IGU_REGULAR_ENABLE_INT_SHIFT 25
#घोषणा IGU_REGULAR_RESERVED_1 (0x1<<27)
#घोषणा IGU_REGULAR_RESERVED_1_SHIFT 27
#घोषणा IGU_REGULAR_CLEANUP_TYPE (0x3<<28)
#घोषणा IGU_REGULAR_CLEANUP_TYPE_SHIFT 28
#घोषणा IGU_REGULAR_CLEANUP_SET (0x1<<30)
#घोषणा IGU_REGULAR_CLEANUP_SET_SHIFT 30
#घोषणा IGU_REGULAR_BCLEANUP (0x1<<31)
#घोषणा IGU_REGULAR_BCLEANUP_SHIFT 31
	u32 reserved_2;
पूर्ण;

/*
 * IGU driver acknowledgement रेजिस्टर
 */
जोड़ igu_consprod_reg अणु
	काष्ठा igu_regular regular;
	काष्ठा igu_backward_compatible backward_compatible;
पूर्ण;


/*
 * Igu control commands
 */
क्रमागत igu_ctrl_cmd अणु
	IGU_CTRL_CMD_TYPE_RD,
	IGU_CTRL_CMD_TYPE_WR,
	MAX_IGU_CTRL_CMD
पूर्ण;


/*
 * Control रेजिस्टर क्रम the IGU command रेजिस्टर
 */
काष्ठा igu_ctrl_reg अणु
	u32 ctrl_data;
#घोषणा IGU_CTRL_REG_ADDRESS (0xFFF<<0)
#घोषणा IGU_CTRL_REG_ADDRESS_SHIFT 0
#घोषणा IGU_CTRL_REG_FID (0x7F<<12)
#घोषणा IGU_CTRL_REG_FID_SHIFT 12
#घोषणा IGU_CTRL_REG_RESERVED (0x1<<19)
#घोषणा IGU_CTRL_REG_RESERVED_SHIFT 19
#घोषणा IGU_CTRL_REG_TYPE (0x1<<20)
#घोषणा IGU_CTRL_REG_TYPE_SHIFT 20
#घोषणा IGU_CTRL_REG_UNUSED (0x7FF<<21)
#घोषणा IGU_CTRL_REG_UNUSED_SHIFT 21
पूर्ण;


/*
 * Igu पूर्णांकerrupt command
 */
क्रमागत igu_पूर्णांक_cmd अणु
	IGU_INT_ENABLE,
	IGU_INT_DISABLE,
	IGU_INT_NOP,
	IGU_INT_NOP2,
	MAX_IGU_INT_CMD
पूर्ण;


/*
 * Igu segments
 */
क्रमागत igu_seg_access अणु
	IGU_SEG_ACCESS_NORM,
	IGU_SEG_ACCESS_DEF,
	IGU_SEG_ACCESS_ATTN,
	MAX_IGU_SEG_ACCESS
पूर्ण;


/*
 * Parser parsing flags field
 */
काष्ठा parsing_flags अणु
	__le16 flags;
#घोषणा PARSING_FLAGS_ETHERNET_ADDRESS_TYPE (0x1<<0)
#घोषणा PARSING_FLAGS_ETHERNET_ADDRESS_TYPE_SHIFT 0
#घोषणा PARSING_FLAGS_VLAN (0x1<<1)
#घोषणा PARSING_FLAGS_VLAN_SHIFT 1
#घोषणा PARSING_FLAGS_EXTRA_VLAN (0x1<<2)
#घोषणा PARSING_FLAGS_EXTRA_VLAN_SHIFT 2
#घोषणा PARSING_FLAGS_OVER_ETHERNET_PROTOCOL (0x3<<3)
#घोषणा PARSING_FLAGS_OVER_ETHERNET_PROTOCOL_SHIFT 3
#घोषणा PARSING_FLAGS_IP_OPTIONS (0x1<<5)
#घोषणा PARSING_FLAGS_IP_OPTIONS_SHIFT 5
#घोषणा PARSING_FLAGS_FRAGMENTATION_STATUS (0x1<<6)
#घोषणा PARSING_FLAGS_FRAGMENTATION_STATUS_SHIFT 6
#घोषणा PARSING_FLAGS_OVER_IP_PROTOCOL (0x3<<7)
#घोषणा PARSING_FLAGS_OVER_IP_PROTOCOL_SHIFT 7
#घोषणा PARSING_FLAGS_PURE_ACK_INDICATION (0x1<<9)
#घोषणा PARSING_FLAGS_PURE_ACK_INDICATION_SHIFT 9
#घोषणा PARSING_FLAGS_TCP_OPTIONS_EXIST (0x1<<10)
#घोषणा PARSING_FLAGS_TCP_OPTIONS_EXIST_SHIFT 10
#घोषणा PARSING_FLAGS_TIME_STAMP_EXIST_FLAG (0x1<<11)
#घोषणा PARSING_FLAGS_TIME_STAMP_EXIST_FLAG_SHIFT 11
#घोषणा PARSING_FLAGS_CONNECTION_MATCH (0x1<<12)
#घोषणा PARSING_FLAGS_CONNECTION_MATCH_SHIFT 12
#घोषणा PARSING_FLAGS_LLC_SNAP (0x1<<13)
#घोषणा PARSING_FLAGS_LLC_SNAP_SHIFT 13
#घोषणा PARSING_FLAGS_RESERVED0 (0x3<<14)
#घोषणा PARSING_FLAGS_RESERVED0_SHIFT 14
पूर्ण;


/*
 * Parsing flags क्रम TCP ACK type
 */
क्रमागत prs_flags_ack_type अणु
	PRS_FLAG_PUREACK_PIGGY,
	PRS_FLAG_PUREACK_PURE,
	MAX_PRS_FLAGS_ACK_TYPE
पूर्ण;


/*
 * Parsing flags क्रम Ethernet address type
 */
क्रमागत prs_flags_eth_addr_type अणु
	PRS_FLAG_ETHTYPE_NON_UNICAST,
	PRS_FLAG_ETHTYPE_UNICAST,
	MAX_PRS_FLAGS_ETH_ADDR_TYPE
पूर्ण;


/*
 * Parsing flags क्रम over-ethernet protocol
 */
क्रमागत prs_flags_over_eth अणु
	PRS_FLAG_OVERETH_UNKNOWN,
	PRS_FLAG_OVERETH_IPV4,
	PRS_FLAG_OVERETH_IPV6,
	PRS_FLAG_OVERETH_LLCSNAP_UNKNOWN,
	MAX_PRS_FLAGS_OVER_ETH
पूर्ण;


/*
 * Parsing flags क्रम over-IP protocol
 */
क्रमागत prs_flags_over_ip अणु
	PRS_FLAG_OVERIP_UNKNOWN,
	PRS_FLAG_OVERIP_TCP,
	PRS_FLAG_OVERIP_UDP,
	MAX_PRS_FLAGS_OVER_IP
पूर्ण;


/*
 * SDM operation gen command (generate aggregative पूर्णांकerrupt)
 */
काष्ठा sdm_op_gen अणु
	__le32 command;
#घोषणा SDM_OP_GEN_COMP_PARAM (0x1F<<0)
#घोषणा SDM_OP_GEN_COMP_PARAM_SHIFT 0
#घोषणा SDM_OP_GEN_COMP_TYPE (0x7<<5)
#घोषणा SDM_OP_GEN_COMP_TYPE_SHIFT 5
#घोषणा SDM_OP_GEN_AGG_VECT_IDX (0xFF<<8)
#घोषणा SDM_OP_GEN_AGG_VECT_IDX_SHIFT 8
#घोषणा SDM_OP_GEN_AGG_VECT_IDX_VALID (0x1<<16)
#घोषणा SDM_OP_GEN_AGG_VECT_IDX_VALID_SHIFT 16
#घोषणा SDM_OP_GEN_RESERVED (0x7FFF<<17)
#घोषणा SDM_OP_GEN_RESERVED_SHIFT 17
पूर्ण;


/*
 * Timers connection context
 */
काष्ठा समयrs_block_context अणु
	u32 __reserved_0;
	u32 __reserved_1;
	u32 __reserved_2;
	u32 flags;
#घोषणा __TIMERS_BLOCK_CONTEXT_NUM_OF_ACTIVE_TIMERS (0x3<<0)
#घोषणा __TIMERS_BLOCK_CONTEXT_NUM_OF_ACTIVE_TIMERS_SHIFT 0
#घोषणा TIMERS_BLOCK_CONTEXT_CONN_VALID_FLG (0x1<<2)
#घोषणा TIMERS_BLOCK_CONTEXT_CONN_VALID_FLG_SHIFT 2
#घोषणा __TIMERS_BLOCK_CONTEXT_RESERVED0 (0x1FFFFFFF<<3)
#घोषणा __TIMERS_BLOCK_CONTEXT_RESERVED0_SHIFT 3
पूर्ण;


/*
 * The eth aggregative context of Tstorm
 */
काष्ठा tstorm_eth_ag_context अणु
	u32 __reserved0[14];
पूर्ण;


/*
 * The eth aggregative context of Ustorm
 */
काष्ठा ustorm_eth_ag_context अणु
	u32 __reserved0;
#अगर defined(__BIG_ENDIAN)
	u8 cdu_usage;
	u8 __reserved2;
	u16 __reserved1;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 __reserved1;
	u8 __reserved2;
	u8 cdu_usage;
#पूर्ण_अगर
	u32 __reserved3[6];
पूर्ण;


/*
 * The eth aggregative context of Xstorm
 */
काष्ठा xstorm_eth_ag_context अणु
	u32 reserved0;
#अगर defined(__BIG_ENDIAN)
	u8 cdu_reserved;
	u8 reserved2;
	u16 reserved1;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 reserved1;
	u8 reserved2;
	u8 cdu_reserved;
#पूर्ण_अगर
	u32 reserved3[30];
पूर्ण;


/*
 * करोorbell message sent to the chip
 */
काष्ठा करोorbell अणु
#अगर defined(__BIG_ENDIAN)
	u16 zero_fill2;
	u8 zero_fill1;
	काष्ठा करोorbell_hdr header;
#या_अगर defined(__LITTLE_ENDIAN)
	काष्ठा करोorbell_hdr header;
	u8 zero_fill1;
	u16 zero_fill2;
#पूर्ण_अगर
पूर्ण;


/*
 * करोorbell message sent to the chip
 */
काष्ठा करोorbell_set_prod अणु
#अगर defined(__BIG_ENDIAN)
	u16 prod;
	u8 zero_fill1;
	काष्ठा करोorbell_hdr header;
#या_अगर defined(__LITTLE_ENDIAN)
	काष्ठा करोorbell_hdr header;
	u8 zero_fill1;
	u16 prod;
#पूर्ण_अगर
पूर्ण;


काष्ठा regpair अणु
	__le32 lo;
	__le32 hi;
पूर्ण;

काष्ठा regpair_native अणु
	u32 lo;
	u32 hi;
पूर्ण;

/*
 * Classअगरy rule opcodes in E2/E3
 */
क्रमागत classअगरy_rule अणु
	CLASSIFY_RULE_OPCODE_MAC,
	CLASSIFY_RULE_OPCODE_VLAN,
	CLASSIFY_RULE_OPCODE_PAIR,
	CLASSIFY_RULE_OPCODE_IMAC_VNI,
	MAX_CLASSIFY_RULE
पूर्ण;


/*
 * Classअगरy rule types in E2/E3
 */
क्रमागत classअगरy_rule_action_type अणु
	CLASSIFY_RULE_REMOVE,
	CLASSIFY_RULE_ADD,
	MAX_CLASSIFY_RULE_ACTION_TYPE
पूर्ण;


/*
 * client init ramrod data
 */
काष्ठा client_init_general_data अणु
	u8 client_id;
	u8 statistics_counter_id;
	u8 statistics_en_flg;
	u8 is_fcoe_flg;
	u8 activate_flg;
	u8 sp_client_id;
	__le16 mtu;
	u8 statistics_zero_flg;
	u8 func_id;
	u8 cos;
	u8 traffic_type;
	u8 fp_hsi_ver;
	u8 reserved0[3];
पूर्ण;


/*
 * client init rx data
 */
काष्ठा client_init_rx_data अणु
	u8 tpa_en;
#घोषणा CLIENT_INIT_RX_DATA_TPA_EN_IPV4 (0x1<<0)
#घोषणा CLIENT_INIT_RX_DATA_TPA_EN_IPV4_SHIFT 0
#घोषणा CLIENT_INIT_RX_DATA_TPA_EN_IPV6 (0x1<<1)
#घोषणा CLIENT_INIT_RX_DATA_TPA_EN_IPV6_SHIFT 1
#घोषणा CLIENT_INIT_RX_DATA_TPA_MODE (0x1<<2)
#घोषणा CLIENT_INIT_RX_DATA_TPA_MODE_SHIFT 2
#घोषणा CLIENT_INIT_RX_DATA_TPA_OVER_VLAN_DISABLE (0x1<<3)
#घोषणा CLIENT_INIT_RX_DATA_TPA_OVER_VLAN_DISABLE_SHIFT 3
#घोषणा CLIENT_INIT_RX_DATA_RESERVED5 (0xF<<4)
#घोषणा CLIENT_INIT_RX_DATA_RESERVED5_SHIFT 4
	u8 vmqueue_mode_en_flg;
	u8 extra_data_over_sgl_en_flg;
	u8 cache_line_alignment_log_size;
	u8 enable_dynamic_hc;
	u8 max_sges_क्रम_packet;
	u8 client_qzone_id;
	u8 drop_ip_cs_err_flg;
	u8 drop_tcp_cs_err_flg;
	u8 drop_ttl0_flg;
	u8 drop_udp_cs_err_flg;
	u8 inner_vlan_removal_enable_flg;
	u8 outer_vlan_removal_enable_flg;
	u8 status_block_id;
	u8 rx_sb_index_number;
	u8 करोnt_verअगरy_rings_छोड़ो_thr_flg;
	u8 max_tpa_queues;
	u8 silent_vlan_removal_flg;
	__le16 max_bytes_on_bd;
	__le16 sge_buff_size;
	u8 approx_mcast_engine_id;
	u8 rss_engine_id;
	काष्ठा regpair bd_page_base;
	काष्ठा regpair sge_page_base;
	काष्ठा regpair cqe_page_base;
	u8 is_leading_rss;
	u8 is_approx_mcast;
	__le16 max_agg_size;
	__le16 state;
#घोषणा CLIENT_INIT_RX_DATA_UCAST_DROP_ALL (0x1<<0)
#घोषणा CLIENT_INIT_RX_DATA_UCAST_DROP_ALL_SHIFT 0
#घोषणा CLIENT_INIT_RX_DATA_UCAST_ACCEPT_ALL (0x1<<1)
#घोषणा CLIENT_INIT_RX_DATA_UCAST_ACCEPT_ALL_SHIFT 1
#घोषणा CLIENT_INIT_RX_DATA_UCAST_ACCEPT_UNMATCHED (0x1<<2)
#घोषणा CLIENT_INIT_RX_DATA_UCAST_ACCEPT_UNMATCHED_SHIFT 2
#घोषणा CLIENT_INIT_RX_DATA_MCAST_DROP_ALL (0x1<<3)
#घोषणा CLIENT_INIT_RX_DATA_MCAST_DROP_ALL_SHIFT 3
#घोषणा CLIENT_INIT_RX_DATA_MCAST_ACCEPT_ALL (0x1<<4)
#घोषणा CLIENT_INIT_RX_DATA_MCAST_ACCEPT_ALL_SHIFT 4
#घोषणा CLIENT_INIT_RX_DATA_BCAST_ACCEPT_ALL (0x1<<5)
#घोषणा CLIENT_INIT_RX_DATA_BCAST_ACCEPT_ALL_SHIFT 5
#घोषणा CLIENT_INIT_RX_DATA_ACCEPT_ANY_VLAN (0x1<<6)
#घोषणा CLIENT_INIT_RX_DATA_ACCEPT_ANY_VLAN_SHIFT 6
#घोषणा CLIENT_INIT_RX_DATA_RESERVED2 (0x1FF<<7)
#घोषणा CLIENT_INIT_RX_DATA_RESERVED2_SHIFT 7
	__le16 cqe_छोड़ो_thr_low;
	__le16 cqe_छोड़ो_thr_high;
	__le16 bd_छोड़ो_thr_low;
	__le16 bd_छोड़ो_thr_high;
	__le16 sge_छोड़ो_thr_low;
	__le16 sge_छोड़ो_thr_high;
	__le16 rx_cos_mask;
	__le16 silent_vlan_value;
	__le16 silent_vlan_mask;
	u8 handle_ptp_pkts_flg;
	u8 reserved6[3];
	__le32 reserved7;
पूर्ण;

/*
 * client init tx data
 */
काष्ठा client_init_tx_data अणु
	u8 enक्रमce_security_flg;
	u8 tx_status_block_id;
	u8 tx_sb_index_number;
	u8 tss_leading_client_id;
	u8 tx_चयनing_flg;
	u8 anti_spoofing_flg;
	__le16 शेष_vlan;
	काष्ठा regpair tx_bd_page_base;
	__le16 state;
#घोषणा CLIENT_INIT_TX_DATA_UCAST_ACCEPT_ALL (0x1<<0)
#घोषणा CLIENT_INIT_TX_DATA_UCAST_ACCEPT_ALL_SHIFT 0
#घोषणा CLIENT_INIT_TX_DATA_MCAST_ACCEPT_ALL (0x1<<1)
#घोषणा CLIENT_INIT_TX_DATA_MCAST_ACCEPT_ALL_SHIFT 1
#घोषणा CLIENT_INIT_TX_DATA_BCAST_ACCEPT_ALL (0x1<<2)
#घोषणा CLIENT_INIT_TX_DATA_BCAST_ACCEPT_ALL_SHIFT 2
#घोषणा CLIENT_INIT_TX_DATA_ACCEPT_ANY_VLAN (0x1<<3)
#घोषणा CLIENT_INIT_TX_DATA_ACCEPT_ANY_VLAN_SHIFT 3
#घोषणा CLIENT_INIT_TX_DATA_RESERVED0 (0xFFF<<4)
#घोषणा CLIENT_INIT_TX_DATA_RESERVED0_SHIFT 4
	u8 शेष_vlan_flg;
	u8 क्रमce_शेष_pri_flg;
	u8 tunnel_lso_inc_ip_id;
	u8 refuse_outband_vlan_flg;
	u8 tunnel_non_lso_pcsum_location;
	u8 tunnel_non_lso_outer_ip_csum_location;
पूर्ण;

/*
 * client init ramrod data
 */
काष्ठा client_init_ramrod_data अणु
	काष्ठा client_init_general_data general;
	काष्ठा client_init_rx_data rx;
	काष्ठा client_init_tx_data tx;
पूर्ण;


/*
 * client update ramrod data
 */
काष्ठा client_update_ramrod_data अणु
	u8 client_id;
	u8 func_id;
	u8 inner_vlan_removal_enable_flg;
	u8 inner_vlan_removal_change_flg;
	u8 outer_vlan_removal_enable_flg;
	u8 outer_vlan_removal_change_flg;
	u8 anti_spoofing_enable_flg;
	u8 anti_spoofing_change_flg;
	u8 activate_flg;
	u8 activate_change_flg;
	__le16 शेष_vlan;
	u8 शेष_vlan_enable_flg;
	u8 शेष_vlan_change_flg;
	__le16 silent_vlan_value;
	__le16 silent_vlan_mask;
	u8 silent_vlan_removal_flg;
	u8 silent_vlan_change_flg;
	u8 refuse_outband_vlan_flg;
	u8 refuse_outband_vlan_change_flg;
	u8 tx_चयनing_flg;
	u8 tx_चयनing_change_flg;
	u8 handle_ptp_pkts_flg;
	u8 handle_ptp_pkts_change_flg;
	__le16 reserved1;
	__le32 echo;
पूर्ण;


/*
 * The eth storm context of Cstorm
 */
काष्ठा cstorm_eth_st_context अणु
	u32 __reserved0[4];
पूर्ण;


काष्ठा द्विगुन_regpair अणु
	u32 regpair0_lo;
	u32 regpair0_hi;
	u32 regpair1_lo;
	u32 regpair1_hi;
पूर्ण;

/* 2nd parse bd type used in ethernet tx BDs */
क्रमागत eth_2nd_parse_bd_type अणु
	ETH_2ND_PARSE_BD_TYPE_LSO_TUNNEL,
	MAX_ETH_2ND_PARSE_BD_TYPE
पूर्ण;

/*
 * Ethernet address typesm used in ethernet tx BDs
 */
क्रमागत eth_addr_type अणु
	UNKNOWN_ADDRESS,
	UNICAST_ADDRESS,
	MULTICAST_ADDRESS,
	BROADCAST_ADDRESS,
	MAX_ETH_ADDR_TYPE
पूर्ण;


/*
 *
 */
काष्ठा eth_classअगरy_cmd_header अणु
	u8 cmd_general_data;
#घोषणा ETH_CLASSIFY_CMD_HEADER_RX_CMD (0x1<<0)
#घोषणा ETH_CLASSIFY_CMD_HEADER_RX_CMD_SHIFT 0
#घोषणा ETH_CLASSIFY_CMD_HEADER_TX_CMD (0x1<<1)
#घोषणा ETH_CLASSIFY_CMD_HEADER_TX_CMD_SHIFT 1
#घोषणा ETH_CLASSIFY_CMD_HEADER_OPCODE (0x3<<2)
#घोषणा ETH_CLASSIFY_CMD_HEADER_OPCODE_SHIFT 2
#घोषणा ETH_CLASSIFY_CMD_HEADER_IS_ADD (0x1<<4)
#घोषणा ETH_CLASSIFY_CMD_HEADER_IS_ADD_SHIFT 4
#घोषणा ETH_CLASSIFY_CMD_HEADER_RESERVED0 (0x7<<5)
#घोषणा ETH_CLASSIFY_CMD_HEADER_RESERVED0_SHIFT 5
	u8 func_id;
	u8 client_id;
	u8 reserved1;
पूर्ण;


/*
 * header क्रम eth classअगरication config ramrod
 */
काष्ठा eth_classअगरy_header अणु
	u8 rule_cnt;
	u8 warning_on_error;
	__le16 reserved1;
	__le32 echo;
पूर्ण;

/*
 * Command क्रम adding/removing a Inner-MAC/VNI classअगरication rule
 */
काष्ठा eth_classअगरy_imac_vni_cmd अणु
	काष्ठा eth_classअगरy_cmd_header header;
	__le32 vni;
	__le16 imac_lsb;
	__le16 imac_mid;
	__le16 imac_msb;
	__le16 reserved1;
पूर्ण;

/*
 * Command क्रम adding/removing a MAC classअगरication rule
 */
काष्ठा eth_classअगरy_mac_cmd अणु
	काष्ठा eth_classअगरy_cmd_header header;
	__le16 reserved0;
	__le16 inner_mac;
	__le16 mac_lsb;
	__le16 mac_mid;
	__le16 mac_msb;
	__le16 reserved1;
पूर्ण;


/*
 * Command क्रम adding/removing a MAC-VLAN pair classअगरication rule
 */
काष्ठा eth_classअगरy_pair_cmd अणु
	काष्ठा eth_classअगरy_cmd_header header;
	__le16 reserved0;
	__le16 inner_mac;
	__le16 mac_lsb;
	__le16 mac_mid;
	__le16 mac_msb;
	__le16 vlan;
पूर्ण;


/*
 * Command क्रम adding/removing a VLAN classअगरication rule
 */
काष्ठा eth_classअगरy_vlan_cmd अणु
	काष्ठा eth_classअगरy_cmd_header header;
	__le32 reserved0;
	__le32 reserved1;
	__le16 reserved2;
	__le16 vlan;
पूर्ण;

/*
 * Command क्रम adding/removing a VXLAN classअगरication rule
 */

/*
 * जोड़ क्रम eth classअगरication rule
 */
जोड़ eth_classअगरy_rule_cmd अणु
	काष्ठा eth_classअगरy_mac_cmd mac;
	काष्ठा eth_classअगरy_vlan_cmd vlan;
	काष्ठा eth_classअगरy_pair_cmd pair;
	काष्ठा eth_classअगरy_imac_vni_cmd imac_vni;
पूर्ण;

/*
 * parameters क्रम eth classअगरication configuration ramrod
 */
काष्ठा eth_classअगरy_rules_ramrod_data अणु
	काष्ठा eth_classअगरy_header header;
	जोड़ eth_classअगरy_rule_cmd rules[CLASSIFY_RULES_COUNT];
पूर्ण;


/*
 * The data contain client ID need to the ramrod
 */
काष्ठा eth_common_ramrod_data अणु
	__le32 client_id;
	__le32 reserved1;
पूर्ण;


/*
 * The eth storm context of Ustorm
 */
काष्ठा ustorm_eth_st_context अणु
	u32 reserved0[52];
पूर्ण;

/*
 * The eth storm context of Tstorm
 */
काष्ठा tstorm_eth_st_context अणु
	u32 __reserved0[28];
पूर्ण;

/*
 * The eth storm context of Xstorm
 */
काष्ठा xstorm_eth_st_context अणु
	u32 reserved0[60];
पूर्ण;

/*
 * Ethernet connection context
 */
काष्ठा eth_context अणु
	काष्ठा ustorm_eth_st_context ustorm_st_context;
	काष्ठा tstorm_eth_st_context tstorm_st_context;
	काष्ठा xstorm_eth_ag_context xstorm_ag_context;
	काष्ठा tstorm_eth_ag_context tstorm_ag_context;
	काष्ठा cstorm_eth_ag_context cstorm_ag_context;
	काष्ठा ustorm_eth_ag_context ustorm_ag_context;
	काष्ठा समयrs_block_context समयrs_context;
	काष्ठा xstorm_eth_st_context xstorm_st_context;
	काष्ठा cstorm_eth_st_context cstorm_st_context;
पूर्ण;


/*
 * जोड़ क्रम sgl and raw data.
 */
जोड़ eth_sgl_or_raw_data अणु
	__le16 sgl[8];
	u32 raw_data[4];
पूर्ण;

/*
 * eth FP end aggregation CQE parameters काष्ठा
 */
काष्ठा eth_end_agg_rx_cqe अणु
	u8 type_error_flags;
#घोषणा ETH_END_AGG_RX_CQE_TYPE (0x3<<0)
#घोषणा ETH_END_AGG_RX_CQE_TYPE_SHIFT 0
#घोषणा ETH_END_AGG_RX_CQE_SGL_RAW_SEL (0x1<<2)
#घोषणा ETH_END_AGG_RX_CQE_SGL_RAW_SEL_SHIFT 2
#घोषणा ETH_END_AGG_RX_CQE_RESERVED0 (0x1F<<3)
#घोषणा ETH_END_AGG_RX_CQE_RESERVED0_SHIFT 3
	u8 reserved1;
	u8 queue_index;
	u8 reserved2;
	__le32 बारtamp_delta;
	__le16 num_of_coalesced_segs;
	__le16 pkt_len;
	u8 pure_ack_count;
	u8 reserved3;
	__le16 reserved4;
	जोड़ eth_sgl_or_raw_data sgl_or_raw_data;
	__le32 reserved5[8];
पूर्ण;


/*
 * regular eth FP CQE parameters काष्ठा
 */
काष्ठा eth_fast_path_rx_cqe अणु
	u8 type_error_flags;
#घोषणा ETH_FAST_PATH_RX_CQE_TYPE (0x3<<0)
#घोषणा ETH_FAST_PATH_RX_CQE_TYPE_SHIFT 0
#घोषणा ETH_FAST_PATH_RX_CQE_SGL_RAW_SEL (0x1<<2)
#घोषणा ETH_FAST_PATH_RX_CQE_SGL_RAW_SEL_SHIFT 2
#घोषणा ETH_FAST_PATH_RX_CQE_PHY_DECODE_ERR_FLG (0x1<<3)
#घोषणा ETH_FAST_PATH_RX_CQE_PHY_DECODE_ERR_FLG_SHIFT 3
#घोषणा ETH_FAST_PATH_RX_CQE_IP_BAD_XSUM_FLG (0x1<<4)
#घोषणा ETH_FAST_PATH_RX_CQE_IP_BAD_XSUM_FLG_SHIFT 4
#घोषणा ETH_FAST_PATH_RX_CQE_L4_BAD_XSUM_FLG (0x1<<5)
#घोषणा ETH_FAST_PATH_RX_CQE_L4_BAD_XSUM_FLG_SHIFT 5
#घोषणा ETH_FAST_PATH_RX_CQE_PTP_PKT (0x1<<6)
#घोषणा ETH_FAST_PATH_RX_CQE_PTP_PKT_SHIFT 6
#घोषणा ETH_FAST_PATH_RX_CQE_RESERVED0 (0x1<<7)
#घोषणा ETH_FAST_PATH_RX_CQE_RESERVED0_SHIFT 7
	u8 status_flags;
#घोषणा ETH_FAST_PATH_RX_CQE_RSS_HASH_TYPE (0x7<<0)
#घोषणा ETH_FAST_PATH_RX_CQE_RSS_HASH_TYPE_SHIFT 0
#घोषणा ETH_FAST_PATH_RX_CQE_RSS_HASH_FLG (0x1<<3)
#घोषणा ETH_FAST_PATH_RX_CQE_RSS_HASH_FLG_SHIFT 3
#घोषणा ETH_FAST_PATH_RX_CQE_BROADCAST_FLG (0x1<<4)
#घोषणा ETH_FAST_PATH_RX_CQE_BROADCAST_FLG_SHIFT 4
#घोषणा ETH_FAST_PATH_RX_CQE_MAC_MATCH_FLG (0x1<<5)
#घोषणा ETH_FAST_PATH_RX_CQE_MAC_MATCH_FLG_SHIFT 5
#घोषणा ETH_FAST_PATH_RX_CQE_IP_XSUM_NO_VALIDATION_FLG (0x1<<6)
#घोषणा ETH_FAST_PATH_RX_CQE_IP_XSUM_NO_VALIDATION_FLG_SHIFT 6
#घोषणा ETH_FAST_PATH_RX_CQE_L4_XSUM_NO_VALIDATION_FLG (0x1<<7)
#घोषणा ETH_FAST_PATH_RX_CQE_L4_XSUM_NO_VALIDATION_FLG_SHIFT 7
	u8 queue_index;
	u8 placement_offset;
	__le32 rss_hash_result;
	__le16 vlan_tag;
	__le16 pkt_len_or_gro_seg_len;
	__le16 len_on_bd;
	काष्ठा parsing_flags pars_flags;
	जोड़ eth_sgl_or_raw_data sgl_or_raw_data;
	u8 tunn_type;
	u8 tunn_inner_hdrs_offset;
	__le16 reserved1;
	__le32 tunn_tenant_id;
	__le32 padding[5];
	u32 marker;
पूर्ण;


/*
 * Command क्रम setting classअगरication flags क्रम a client
 */
काष्ठा eth_filter_rules_cmd अणु
	u8 cmd_general_data;
#घोषणा ETH_FILTER_RULES_CMD_RX_CMD (0x1<<0)
#घोषणा ETH_FILTER_RULES_CMD_RX_CMD_SHIFT 0
#घोषणा ETH_FILTER_RULES_CMD_TX_CMD (0x1<<1)
#घोषणा ETH_FILTER_RULES_CMD_TX_CMD_SHIFT 1
#घोषणा ETH_FILTER_RULES_CMD_RESERVED0 (0x3F<<2)
#घोषणा ETH_FILTER_RULES_CMD_RESERVED0_SHIFT 2
	u8 func_id;
	u8 client_id;
	u8 reserved1;
	__le16 state;
#घोषणा ETH_FILTER_RULES_CMD_UCAST_DROP_ALL (0x1<<0)
#घोषणा ETH_FILTER_RULES_CMD_UCAST_DROP_ALL_SHIFT 0
#घोषणा ETH_FILTER_RULES_CMD_UCAST_ACCEPT_ALL (0x1<<1)
#घोषणा ETH_FILTER_RULES_CMD_UCAST_ACCEPT_ALL_SHIFT 1
#घोषणा ETH_FILTER_RULES_CMD_UCAST_ACCEPT_UNMATCHED (0x1<<2)
#घोषणा ETH_FILTER_RULES_CMD_UCAST_ACCEPT_UNMATCHED_SHIFT 2
#घोषणा ETH_FILTER_RULES_CMD_MCAST_DROP_ALL (0x1<<3)
#घोषणा ETH_FILTER_RULES_CMD_MCAST_DROP_ALL_SHIFT 3
#घोषणा ETH_FILTER_RULES_CMD_MCAST_ACCEPT_ALL (0x1<<4)
#घोषणा ETH_FILTER_RULES_CMD_MCAST_ACCEPT_ALL_SHIFT 4
#घोषणा ETH_FILTER_RULES_CMD_BCAST_ACCEPT_ALL (0x1<<5)
#घोषणा ETH_FILTER_RULES_CMD_BCAST_ACCEPT_ALL_SHIFT 5
#घोषणा ETH_FILTER_RULES_CMD_ACCEPT_ANY_VLAN (0x1<<6)
#घोषणा ETH_FILTER_RULES_CMD_ACCEPT_ANY_VLAN_SHIFT 6
#घोषणा ETH_FILTER_RULES_CMD_RESERVED2 (0x1FF<<7)
#घोषणा ETH_FILTER_RULES_CMD_RESERVED2_SHIFT 7
	__le16 reserved3;
	काष्ठा regpair reserved4;
पूर्ण;


/*
 * parameters क्रम eth classअगरication filters ramrod
 */
काष्ठा eth_filter_rules_ramrod_data अणु
	काष्ठा eth_classअगरy_header header;
	काष्ठा eth_filter_rules_cmd rules[FILTER_RULES_COUNT];
पूर्ण;

/* Hsi version */
क्रमागत eth_fp_hsi_ver अणु
	ETH_FP_HSI_VER_0,
	ETH_FP_HSI_VER_1,
	ETH_FP_HSI_VER_2,
	MAX_ETH_FP_HSI_VER
पूर्ण;

/*
 * parameters क्रम eth classअगरication configuration ramrod
 */
काष्ठा eth_general_rules_ramrod_data अणु
	काष्ठा eth_classअगरy_header header;
	जोड़ eth_classअगरy_rule_cmd rules[CLASSIFY_RULES_COUNT];
पूर्ण;


/*
 * The data क्रम Halt ramrod
 */
काष्ठा eth_halt_ramrod_data अणु
	__le32 client_id;
	__le32 reserved0;
पूर्ण;


/*
 * destination and source mac address.
 */
काष्ठा eth_mac_addresses अणु
#अगर defined(__BIG_ENDIAN)
	__le16 dst_mid;
	__le16 dst_lo;
#या_अगर defined(__LITTLE_ENDIAN)
	__le16 dst_lo;
	__le16 dst_mid;
#पूर्ण_अगर
#अगर defined(__BIG_ENDIAN)
	__le16 src_lo;
	__le16 dst_hi;
#या_अगर defined(__LITTLE_ENDIAN)
	__le16 dst_hi;
	__le16 src_lo;
#पूर्ण_अगर
#अगर defined(__BIG_ENDIAN)
	__le16 src_hi;
	__le16 src_mid;
#या_अगर defined(__LITTLE_ENDIAN)
	__le16 src_mid;
	__le16 src_hi;
#पूर्ण_अगर
पूर्ण;

/* tunneling related data */
काष्ठा eth_tunnel_data अणु
	__le16 dst_lo;
	__le16 dst_mid;
	__le16 dst_hi;
	__le16 fw_ip_hdr_csum;
	__le16 pseuकरो_csum;
	u8 ip_hdr_start_inner_w;
	u8 flags;
#घोषणा ETH_TUNNEL_DATA_IPV6_OUTER (0x1<<0)
#घोषणा ETH_TUNNEL_DATA_IPV6_OUTER_SHIFT 0
#घोषणा ETH_TUNNEL_DATA_RESERVED (0x7F<<1)
#घोषणा ETH_TUNNEL_DATA_RESERVED_SHIFT 1
पूर्ण;

/* जोड़ क्रम mac addresses and क्रम tunneling data.
 * considered as tunneling data only अगर (tunnel_exist == 1).
 */
जोड़ eth_mac_addr_or_tunnel_data अणु
	काष्ठा eth_mac_addresses mac_addr;
	काष्ठा eth_tunnel_data tunnel_data;
पूर्ण;

/*Command क्रम setting multicast classअगरication क्रम a client */
काष्ठा eth_multicast_rules_cmd अणु
	u8 cmd_general_data;
#घोषणा ETH_MULTICAST_RULES_CMD_RX_CMD (0x1<<0)
#घोषणा ETH_MULTICAST_RULES_CMD_RX_CMD_SHIFT 0
#घोषणा ETH_MULTICAST_RULES_CMD_TX_CMD (0x1<<1)
#घोषणा ETH_MULTICAST_RULES_CMD_TX_CMD_SHIFT 1
#घोषणा ETH_MULTICAST_RULES_CMD_IS_ADD (0x1<<2)
#घोषणा ETH_MULTICAST_RULES_CMD_IS_ADD_SHIFT 2
#घोषणा ETH_MULTICAST_RULES_CMD_RESERVED0 (0x1F<<3)
#घोषणा ETH_MULTICAST_RULES_CMD_RESERVED0_SHIFT 3
	u8 func_id;
	u8 bin_id;
	u8 engine_id;
	__le32 reserved2;
	काष्ठा regpair reserved3;
पूर्ण;

/*
 * parameters क्रम multicast classअगरication ramrod
 */
काष्ठा eth_multicast_rules_ramrod_data अणु
	काष्ठा eth_classअगरy_header header;
	काष्ठा eth_multicast_rules_cmd rules[MULTICAST_RULES_COUNT];
पूर्ण;

/*
 * Place holder क्रम ramrods protocol specअगरic data
 */
काष्ठा ramrod_data अणु
	__le32 data_lo;
	__le32 data_hi;
पूर्ण;

/*
 * जोड़ क्रम ramrod data क्रम Ethernet protocol (CQE) (क्रमce size of 16 bits)
 */
जोड़ eth_ramrod_data अणु
	काष्ठा ramrod_data general;
पूर्ण;


/*
 * RSS toeplitz hash type, as reported in CQE
 */
क्रमागत eth_rss_hash_type अणु
	DEFAULT_HASH_TYPE,
	IPV4_HASH_TYPE,
	TCP_IPV4_HASH_TYPE,
	IPV6_HASH_TYPE,
	TCP_IPV6_HASH_TYPE,
	VLAN_PRI_HASH_TYPE,
	E1HOV_PRI_HASH_TYPE,
	DSCP_HASH_TYPE,
	MAX_ETH_RSS_HASH_TYPE
पूर्ण;


/*
 * Ethernet RSS mode
 */
क्रमागत eth_rss_mode अणु
	ETH_RSS_MODE_DISABLED,
	ETH_RSS_MODE_REGULAR,
	ETH_RSS_MODE_VLAN_PRI,
	ETH_RSS_MODE_E1HOV_PRI,
	ETH_RSS_MODE_IP_DSCP,
	MAX_ETH_RSS_MODE
पूर्ण;


/*
 * parameters क्रम RSS update ramrod (E2)
 */
काष्ठा eth_rss_update_ramrod_data अणु
	u8 rss_engine_id;
	u8 rss_mode;
	__le16 capabilities;
#घोषणा ETH_RSS_UPDATE_RAMROD_DATA_IPV4_CAPABILITY (0x1<<0)
#घोषणा ETH_RSS_UPDATE_RAMROD_DATA_IPV4_CAPABILITY_SHIFT 0
#घोषणा ETH_RSS_UPDATE_RAMROD_DATA_IPV4_TCP_CAPABILITY (0x1<<1)
#घोषणा ETH_RSS_UPDATE_RAMROD_DATA_IPV4_TCP_CAPABILITY_SHIFT 1
#घोषणा ETH_RSS_UPDATE_RAMROD_DATA_IPV4_UDP_CAPABILITY (0x1<<2)
#घोषणा ETH_RSS_UPDATE_RAMROD_DATA_IPV4_UDP_CAPABILITY_SHIFT 2
#घोषणा ETH_RSS_UPDATE_RAMROD_DATA_IPV4_VXLAN_CAPABILITY (0x1<<3)
#घोषणा ETH_RSS_UPDATE_RAMROD_DATA_IPV4_VXLAN_CAPABILITY_SHIFT 3
#घोषणा ETH_RSS_UPDATE_RAMROD_DATA_IPV6_CAPABILITY (0x1<<4)
#घोषणा ETH_RSS_UPDATE_RAMROD_DATA_IPV6_CAPABILITY_SHIFT 4
#घोषणा ETH_RSS_UPDATE_RAMROD_DATA_IPV6_TCP_CAPABILITY (0x1<<5)
#घोषणा ETH_RSS_UPDATE_RAMROD_DATA_IPV6_TCP_CAPABILITY_SHIFT 5
#घोषणा ETH_RSS_UPDATE_RAMROD_DATA_IPV6_UDP_CAPABILITY (0x1<<6)
#घोषणा ETH_RSS_UPDATE_RAMROD_DATA_IPV6_UDP_CAPABILITY_SHIFT 6
#घोषणा ETH_RSS_UPDATE_RAMROD_DATA_IPV6_VXLAN_CAPABILITY (0x1<<7)
#घोषणा ETH_RSS_UPDATE_RAMROD_DATA_IPV6_VXLAN_CAPABILITY_SHIFT 7
#घोषणा ETH_RSS_UPDATE_RAMROD_DATA_TUNN_INNER_HDRS_CAPABILITY (0x1<<8)
#घोषणा ETH_RSS_UPDATE_RAMROD_DATA_TUNN_INNER_HDRS_CAPABILITY_SHIFT 8
#घोषणा ETH_RSS_UPDATE_RAMROD_DATA_UPDATE_RSS_KEY (0x1<<9)
#घोषणा ETH_RSS_UPDATE_RAMROD_DATA_UPDATE_RSS_KEY_SHIFT 9
#घोषणा ETH_RSS_UPDATE_RAMROD_DATA_RESERVED (0x3F<<10)
#घोषणा ETH_RSS_UPDATE_RAMROD_DATA_RESERVED_SHIFT 10
	u8 rss_result_mask;
	u8 reserved3;
	__le16 reserved4;
	u8 indirection_table[T_ETH_INसूचीECTION_TABLE_SIZE];
	__le32 rss_key[T_ETH_RSS_KEY];
	__le32 echo;
	__le32 reserved5;
पूर्ण;


/*
 * The eth Rx Buffer Descriptor
 */
काष्ठा eth_rx_bd अणु
	__le32 addr_lo;
	__le32 addr_hi;
पूर्ण;


/*
 * Eth Rx Cqe काष्ठाure- general काष्ठाure क्रम ramrods
 */
काष्ठा common_ramrod_eth_rx_cqe अणु
	u8 ramrod_type;
#घोषणा COMMON_RAMROD_ETH_RX_CQE_TYPE (0x3<<0)
#घोषणा COMMON_RAMROD_ETH_RX_CQE_TYPE_SHIFT 0
#घोषणा COMMON_RAMROD_ETH_RX_CQE_ERROR (0x1<<2)
#घोषणा COMMON_RAMROD_ETH_RX_CQE_ERROR_SHIFT 2
#घोषणा COMMON_RAMROD_ETH_RX_CQE_RESERVED0 (0x1F<<3)
#घोषणा COMMON_RAMROD_ETH_RX_CQE_RESERVED0_SHIFT 3
	u8 conn_type;
	__le16 reserved1;
	__le32 conn_and_cmd_data;
#घोषणा COMMON_RAMROD_ETH_RX_CQE_CID (0xFFFFFF<<0)
#घोषणा COMMON_RAMROD_ETH_RX_CQE_CID_SHIFT 0
#घोषणा COMMON_RAMROD_ETH_RX_CQE_CMD_ID (0xFF<<24)
#घोषणा COMMON_RAMROD_ETH_RX_CQE_CMD_ID_SHIFT 24
	काष्ठा ramrod_data protocol_data;
	__le32 echo;
	__le32 reserved2[11];
पूर्ण;

/*
 * Rx Last CQE in page (in ETH)
 */
काष्ठा eth_rx_cqe_next_page अणु
	__le32 addr_lo;
	__le32 addr_hi;
	__le32 reserved[14];
पूर्ण;

/*
 * जोड़ क्रम all eth rx cqe types (fix their sizes)
 */
जोड़ eth_rx_cqe अणु
	काष्ठा eth_fast_path_rx_cqe fast_path_cqe;
	काष्ठा common_ramrod_eth_rx_cqe ramrod_cqe;
	काष्ठा eth_rx_cqe_next_page next_page_cqe;
	काष्ठा eth_end_agg_rx_cqe end_agg_cqe;
पूर्ण;


/*
 * Values क्रम RX ETH CQE type field
 */
क्रमागत eth_rx_cqe_type अणु
	RX_ETH_CQE_TYPE_ETH_FASTPATH,
	RX_ETH_CQE_TYPE_ETH_RAMROD,
	RX_ETH_CQE_TYPE_ETH_START_AGG,
	RX_ETH_CQE_TYPE_ETH_STOP_AGG,
	MAX_ETH_RX_CQE_TYPE
पूर्ण;


/*
 * Type of SGL/Raw field in ETH RX fast path CQE
 */
क्रमागत eth_rx_fp_sel अणु
	ETH_FP_CQE_REGULAR,
	ETH_FP_CQE_RAW,
	MAX_ETH_RX_FP_SEL
पूर्ण;


/*
 * The eth Rx SGE Descriptor
 */
काष्ठा eth_rx_sge अणु
	__le32 addr_lo;
	__le32 addr_hi;
पूर्ण;


/*
 * common data क्रम all protocols
 */
काष्ठा spe_hdr अणु
	__le32 conn_and_cmd_data;
#घोषणा SPE_HDR_CID (0xFFFFFF<<0)
#घोषणा SPE_HDR_CID_SHIFT 0
#घोषणा SPE_HDR_CMD_ID (0xFF<<24)
#घोषणा SPE_HDR_CMD_ID_SHIFT 24
	__le16 type;
#घोषणा SPE_HDR_CONN_TYPE (0xFF<<0)
#घोषणा SPE_HDR_CONN_TYPE_SHIFT 0
#घोषणा SPE_HDR_FUNCTION_ID (0xFF<<8)
#घोषणा SPE_HDR_FUNCTION_ID_SHIFT 8
	__le16 reserved1;
पूर्ण;

/*
 * specअगरic data क्रम ethernet slow path element
 */
जोड़ eth_specअगरic_data अणु
	u8 protocol_data[8];
	काष्ठा regpair client_update_ramrod_data;
	काष्ठा regpair client_init_ramrod_init_data;
	काष्ठा eth_halt_ramrod_data halt_ramrod_data;
	काष्ठा regpair update_data_addr;
	काष्ठा eth_common_ramrod_data common_ramrod_data;
	काष्ठा regpair classअगरy_cfg_addr;
	काष्ठा regpair filter_cfg_addr;
	काष्ठा regpair mcast_cfg_addr;
पूर्ण;

/*
 * Ethernet slow path element
 */
काष्ठा eth_spe अणु
	काष्ठा spe_hdr hdr;
	जोड़ eth_specअगरic_data data;
पूर्ण;


/*
 * Ethernet command ID क्रम slow path elements
 */
क्रमागत eth_spqe_cmd_id अणु
	RAMROD_CMD_ID_ETH_UNUSED,
	RAMROD_CMD_ID_ETH_CLIENT_SETUP,
	RAMROD_CMD_ID_ETH_HALT,
	RAMROD_CMD_ID_ETH_FORWARD_SETUP,
	RAMROD_CMD_ID_ETH_TX_QUEUE_SETUP,
	RAMROD_CMD_ID_ETH_CLIENT_UPDATE,
	RAMROD_CMD_ID_ETH_EMPTY,
	RAMROD_CMD_ID_ETH_TERMINATE,
	RAMROD_CMD_ID_ETH_TPA_UPDATE,
	RAMROD_CMD_ID_ETH_CLASSIFICATION_RULES,
	RAMROD_CMD_ID_ETH_FILTER_RULES,
	RAMROD_CMD_ID_ETH_MULTICAST_RULES,
	RAMROD_CMD_ID_ETH_RSS_UPDATE,
	RAMROD_CMD_ID_ETH_SET_MAC,
	MAX_ETH_SPQE_CMD_ID
पूर्ण;


/*
 * eth tpa update command
 */
क्रमागत eth_tpa_update_command अणु
	TPA_UPDATE_NONE_COMMAND,
	TPA_UPDATE_ENABLE_COMMAND,
	TPA_UPDATE_DISABLE_COMMAND,
	MAX_ETH_TPA_UPDATE_COMMAND
पूर्ण;

/* In हाल of LSO over IPv4 tunnel, whether to increment
 * IP ID on बाह्यal IP header or पूर्णांकernal IP header
 */
क्रमागत eth_tunnel_lso_inc_ip_id अणु
	EXT_HEADER,
	INT_HEADER,
	MAX_ETH_TUNNEL_LSO_INC_IP_ID
पूर्ण;

/* In हाल tunnel exist and L4 checksum offload,
 * the pseuकरो checksum location, on packet or on BD.
 */
क्रमागत eth_tunnel_non_lso_csum_location अणु
	CSUM_ON_PKT,
	CSUM_ON_BD,
	MAX_ETH_TUNNEL_NON_LSO_CSUM_LOCATION
पूर्ण;

क्रमागत eth_tunn_type अणु
	TUNN_TYPE_NONE,
	TUNN_TYPE_VXLAN,
	TUNN_TYPE_L2_GRE,
	TUNN_TYPE_IPV4_GRE,
	TUNN_TYPE_IPV6_GRE,
	TUNN_TYPE_L2_GENEVE,
	TUNN_TYPE_IPV4_GENEVE,
	TUNN_TYPE_IPV6_GENEVE,
	MAX_ETH_TUNN_TYPE
पूर्ण;

/*
 * Tx regular BD काष्ठाure
 */
काष्ठा eth_tx_bd अणु
	__le32 addr_lo;
	__le32 addr_hi;
	__le16 total_pkt_bytes;
	__le16 nbytes;
	u8 reserved[4];
पूर्ण;


/*
 * काष्ठाure क्रम easy accessibility to assembler
 */
काष्ठा eth_tx_bd_flags अणु
	u8 as_bitfield;
#घोषणा ETH_TX_BD_FLAGS_IP_CSUM (0x1<<0)
#घोषणा ETH_TX_BD_FLAGS_IP_CSUM_SHIFT 0
#घोषणा ETH_TX_BD_FLAGS_L4_CSUM (0x1<<1)
#घोषणा ETH_TX_BD_FLAGS_L4_CSUM_SHIFT 1
#घोषणा ETH_TX_BD_FLAGS_VLAN_MODE (0x3<<2)
#घोषणा ETH_TX_BD_FLAGS_VLAN_MODE_SHIFT 2
#घोषणा ETH_TX_BD_FLAGS_START_BD (0x1<<4)
#घोषणा ETH_TX_BD_FLAGS_START_BD_SHIFT 4
#घोषणा ETH_TX_BD_FLAGS_IS_UDP (0x1<<5)
#घोषणा ETH_TX_BD_FLAGS_IS_UDP_SHIFT 5
#घोषणा ETH_TX_BD_FLAGS_SW_LSO (0x1<<6)
#घोषणा ETH_TX_BD_FLAGS_SW_LSO_SHIFT 6
#घोषणा ETH_TX_BD_FLAGS_IPV6 (0x1<<7)
#घोषणा ETH_TX_BD_FLAGS_IPV6_SHIFT 7
पूर्ण;

/*
 * The eth Tx Buffer Descriptor
 */
काष्ठा eth_tx_start_bd अणु
	__le32 addr_lo;
	__le32 addr_hi;
	__le16 nbd;
	__le16 nbytes;
	__le16 vlan_or_ethertype;
	काष्ठा eth_tx_bd_flags bd_flags;
	u8 general_data;
#घोषणा ETH_TX_START_BD_HDR_NBDS (0x7<<0)
#घोषणा ETH_TX_START_BD_HDR_NBDS_SHIFT 0
#घोषणा ETH_TX_START_BD_NO_ADDED_TAGS (0x1<<3)
#घोषणा ETH_TX_START_BD_NO_ADDED_TAGS_SHIFT 3
#घोषणा ETH_TX_START_BD_FORCE_VLAN_MODE (0x1<<4)
#घोषणा ETH_TX_START_BD_FORCE_VLAN_MODE_SHIFT 4
#घोषणा ETH_TX_START_BD_PARSE_NBDS (0x3<<5)
#घोषणा ETH_TX_START_BD_PARSE_NBDS_SHIFT 5
#घोषणा ETH_TX_START_BD_TUNNEL_EXIST (0x1<<7)
#घोषणा ETH_TX_START_BD_TUNNEL_EXIST_SHIFT 7
पूर्ण;

/*
 * Tx parsing BD काष्ठाure क्रम ETH E1/E1h
 */
काष्ठा eth_tx_parse_bd_e1x अणु
	__le16 global_data;
#घोषणा ETH_TX_PARSE_BD_E1X_IP_HDR_START_OFFSET_W (0xF<<0)
#घोषणा ETH_TX_PARSE_BD_E1X_IP_HDR_START_OFFSET_W_SHIFT 0
#घोषणा ETH_TX_PARSE_BD_E1X_ETH_ADDR_TYPE (0x3<<4)
#घोषणा ETH_TX_PARSE_BD_E1X_ETH_ADDR_TYPE_SHIFT 4
#घोषणा ETH_TX_PARSE_BD_E1X_PSEUDO_CS_WITHOUT_LEN (0x1<<6)
#घोषणा ETH_TX_PARSE_BD_E1X_PSEUDO_CS_WITHOUT_LEN_SHIFT 6
#घोषणा ETH_TX_PARSE_BD_E1X_LLC_SNAP_EN (0x1<<7)
#घोषणा ETH_TX_PARSE_BD_E1X_LLC_SNAP_EN_SHIFT 7
#घोषणा ETH_TX_PARSE_BD_E1X_NS_FLG (0x1<<8)
#घोषणा ETH_TX_PARSE_BD_E1X_NS_FLG_SHIFT 8
#घोषणा ETH_TX_PARSE_BD_E1X_RESERVED0 (0x7F<<9)
#घोषणा ETH_TX_PARSE_BD_E1X_RESERVED0_SHIFT 9
	u8 tcp_flags;
#घोषणा ETH_TX_PARSE_BD_E1X_FIN_FLG (0x1<<0)
#घोषणा ETH_TX_PARSE_BD_E1X_FIN_FLG_SHIFT 0
#घोषणा ETH_TX_PARSE_BD_E1X_SYN_FLG (0x1<<1)
#घोषणा ETH_TX_PARSE_BD_E1X_SYN_FLG_SHIFT 1
#घोषणा ETH_TX_PARSE_BD_E1X_RST_FLG (0x1<<2)
#घोषणा ETH_TX_PARSE_BD_E1X_RST_FLG_SHIFT 2
#घोषणा ETH_TX_PARSE_BD_E1X_PSH_FLG (0x1<<3)
#घोषणा ETH_TX_PARSE_BD_E1X_PSH_FLG_SHIFT 3
#घोषणा ETH_TX_PARSE_BD_E1X_ACK_FLG (0x1<<4)
#घोषणा ETH_TX_PARSE_BD_E1X_ACK_FLG_SHIFT 4
#घोषणा ETH_TX_PARSE_BD_E1X_URG_FLG (0x1<<5)
#घोषणा ETH_TX_PARSE_BD_E1X_URG_FLG_SHIFT 5
#घोषणा ETH_TX_PARSE_BD_E1X_ECE_FLG (0x1<<6)
#घोषणा ETH_TX_PARSE_BD_E1X_ECE_FLG_SHIFT 6
#घोषणा ETH_TX_PARSE_BD_E1X_CWR_FLG (0x1<<7)
#घोषणा ETH_TX_PARSE_BD_E1X_CWR_FLG_SHIFT 7
	u8 ip_hlen_w;
	__le16 total_hlen_w;
	__le16 tcp_pseuकरो_csum;
	__le16 lso_mss;
	__le16 ip_id;
	__le32 tcp_send_seq;
पूर्ण;

/*
 * Tx parsing BD काष्ठाure क्रम ETH E2
 */
काष्ठा eth_tx_parse_bd_e2 अणु
	जोड़ eth_mac_addr_or_tunnel_data data;
	__le32 parsing_data;
#घोषणा ETH_TX_PARSE_BD_E2_L4_HDR_START_OFFSET_W (0x7FF<<0)
#घोषणा ETH_TX_PARSE_BD_E2_L4_HDR_START_OFFSET_W_SHIFT 0
#घोषणा ETH_TX_PARSE_BD_E2_TCP_HDR_LENGTH_DW (0xF<<11)
#घोषणा ETH_TX_PARSE_BD_E2_TCP_HDR_LENGTH_DW_SHIFT 11
#घोषणा ETH_TX_PARSE_BD_E2_IPV6_WITH_EXT_HDR (0x1<<15)
#घोषणा ETH_TX_PARSE_BD_E2_IPV6_WITH_EXT_HDR_SHIFT 15
#घोषणा ETH_TX_PARSE_BD_E2_LSO_MSS (0x3FFF<<16)
#घोषणा ETH_TX_PARSE_BD_E2_LSO_MSS_SHIFT 16
#घोषणा ETH_TX_PARSE_BD_E2_ETH_ADDR_TYPE (0x3<<30)
#घोषणा ETH_TX_PARSE_BD_E2_ETH_ADDR_TYPE_SHIFT 30
पूर्ण;

/*
 * Tx 2nd parsing BD काष्ठाure क्रम ETH packet
 */
काष्ठा eth_tx_parse_2nd_bd अणु
	__le16 global_data;
#घोषणा ETH_TX_PARSE_2ND_BD_IP_HDR_START_OUTER_W (0xF<<0)
#घोषणा ETH_TX_PARSE_2ND_BD_IP_HDR_START_OUTER_W_SHIFT 0
#घोषणा ETH_TX_PARSE_2ND_BD_RESERVED0 (0x1<<4)
#घोषणा ETH_TX_PARSE_2ND_BD_RESERVED0_SHIFT 4
#घोषणा ETH_TX_PARSE_2ND_BD_LLC_SNAP_EN (0x1<<5)
#घोषणा ETH_TX_PARSE_2ND_BD_LLC_SNAP_EN_SHIFT 5
#घोषणा ETH_TX_PARSE_2ND_BD_NS_FLG (0x1<<6)
#घोषणा ETH_TX_PARSE_2ND_BD_NS_FLG_SHIFT 6
#घोषणा ETH_TX_PARSE_2ND_BD_TUNNEL_UDP_EXIST (0x1<<7)
#घोषणा ETH_TX_PARSE_2ND_BD_TUNNEL_UDP_EXIST_SHIFT 7
#घोषणा ETH_TX_PARSE_2ND_BD_IP_HDR_LEN_OUTER_W (0x1F<<8)
#घोषणा ETH_TX_PARSE_2ND_BD_IP_HDR_LEN_OUTER_W_SHIFT 8
#घोषणा ETH_TX_PARSE_2ND_BD_RESERVED1 (0x7<<13)
#घोषणा ETH_TX_PARSE_2ND_BD_RESERVED1_SHIFT 13
	u8 bd_type;
#घोषणा ETH_TX_PARSE_2ND_BD_TYPE (0xF<<0)
#घोषणा ETH_TX_PARSE_2ND_BD_TYPE_SHIFT 0
#घोषणा ETH_TX_PARSE_2ND_BD_RESERVED2 (0xF<<4)
#घोषणा ETH_TX_PARSE_2ND_BD_RESERVED2_SHIFT 4
	u8 reserved3;
	u8 tcp_flags;
#घोषणा ETH_TX_PARSE_2ND_BD_FIN_FLG (0x1<<0)
#घोषणा ETH_TX_PARSE_2ND_BD_FIN_FLG_SHIFT 0
#घोषणा ETH_TX_PARSE_2ND_BD_SYN_FLG (0x1<<1)
#घोषणा ETH_TX_PARSE_2ND_BD_SYN_FLG_SHIFT 1
#घोषणा ETH_TX_PARSE_2ND_BD_RST_FLG (0x1<<2)
#घोषणा ETH_TX_PARSE_2ND_BD_RST_FLG_SHIFT 2
#घोषणा ETH_TX_PARSE_2ND_BD_PSH_FLG (0x1<<3)
#घोषणा ETH_TX_PARSE_2ND_BD_PSH_FLG_SHIFT 3
#घोषणा ETH_TX_PARSE_2ND_BD_ACK_FLG (0x1<<4)
#घोषणा ETH_TX_PARSE_2ND_BD_ACK_FLG_SHIFT 4
#घोषणा ETH_TX_PARSE_2ND_BD_URG_FLG (0x1<<5)
#घोषणा ETH_TX_PARSE_2ND_BD_URG_FLG_SHIFT 5
#घोषणा ETH_TX_PARSE_2ND_BD_ECE_FLG (0x1<<6)
#घोषणा ETH_TX_PARSE_2ND_BD_ECE_FLG_SHIFT 6
#घोषणा ETH_TX_PARSE_2ND_BD_CWR_FLG (0x1<<7)
#घोषणा ETH_TX_PARSE_2ND_BD_CWR_FLG_SHIFT 7
	u8 reserved4;
	u8 tunnel_udp_hdr_start_w;
	u8 fw_ip_hdr_to_payload_w;
	__le16 fw_ip_csum_wo_len_flags_frag;
	__le16 hw_ip_id;
	__le32 tcp_send_seq;
पूर्ण;

/* The last BD in the BD memory will hold a poपूर्णांकer to the next BD memory */
काष्ठा eth_tx_next_bd अणु
	__le32 addr_lo;
	__le32 addr_hi;
	u8 reserved[8];
पूर्ण;

/*
 * जोड़ क्रम 4 Bd types
 */
जोड़ eth_tx_bd_types अणु
	काष्ठा eth_tx_start_bd start_bd;
	काष्ठा eth_tx_bd reg_bd;
	काष्ठा eth_tx_parse_bd_e1x parse_bd_e1x;
	काष्ठा eth_tx_parse_bd_e2 parse_bd_e2;
	काष्ठा eth_tx_parse_2nd_bd parse_2nd_bd;
	काष्ठा eth_tx_next_bd next_bd;
पूर्ण;

/*
 * array of 13 bds as appears in the eth xstorm context
 */
काष्ठा eth_tx_bds_array अणु
	जोड़ eth_tx_bd_types bds[13];
पूर्ण;


/*
 * VLAN mode on TX BDs
 */
क्रमागत eth_tx_vlan_type अणु
	X_ETH_NO_VLAN,
	X_ETH_OUTBAND_VLAN,
	X_ETH_INBAND_VLAN,
	X_ETH_FW_ADDED_VLAN,
	MAX_ETH_TX_VLAN_TYPE
पूर्ण;


/*
 * Ethernet VLAN filtering mode in E1x
 */
क्रमागत eth_vlan_filter_mode अणु
	ETH_VLAN_FILTER_ANY_VLAN,
	ETH_VLAN_FILTER_SPECIFIC_VLAN,
	ETH_VLAN_FILTER_CLASSIFY,
	MAX_ETH_VLAN_FILTER_MODE
पूर्ण;


/*
 * MAC filtering configuration command header
 */
काष्ठा mac_configuration_hdr अणु
	u8 length;
	u8 offset;
	__le16 client_id;
	__le32 echo;
पूर्ण;

/*
 * MAC address in list क्रम ramrod
 */
काष्ठा mac_configuration_entry अणु
	__le16 lsb_mac_addr;
	__le16 middle_mac_addr;
	__le16 msb_mac_addr;
	__le16 vlan_id;
	u8 pf_id;
	u8 flags;
#घोषणा MAC_CONFIGURATION_ENTRY_ACTION_TYPE (0x1<<0)
#घोषणा MAC_CONFIGURATION_ENTRY_ACTION_TYPE_SHIFT 0
#घोषणा MAC_CONFIGURATION_ENTRY_RDMA_MAC (0x1<<1)
#घोषणा MAC_CONFIGURATION_ENTRY_RDMA_MAC_SHIFT 1
#घोषणा MAC_CONFIGURATION_ENTRY_VLAN_FILTERING_MODE (0x3<<2)
#घोषणा MAC_CONFIGURATION_ENTRY_VLAN_FILTERING_MODE_SHIFT 2
#घोषणा MAC_CONFIGURATION_ENTRY_OVERRIDE_VLAN_REMOVAL (0x1<<4)
#घोषणा MAC_CONFIGURATION_ENTRY_OVERRIDE_VLAN_REMOVAL_SHIFT 4
#घोषणा MAC_CONFIGURATION_ENTRY_BROADCAST (0x1<<5)
#घोषणा MAC_CONFIGURATION_ENTRY_BROADCAST_SHIFT 5
#घोषणा MAC_CONFIGURATION_ENTRY_RESERVED1 (0x3<<6)
#घोषणा MAC_CONFIGURATION_ENTRY_RESERVED1_SHIFT 6
	__le16 reserved0;
	__le32 clients_bit_vector;
पूर्ण;

/*
 * MAC filtering configuration command
 */
काष्ठा mac_configuration_cmd अणु
	काष्ठा mac_configuration_hdr hdr;
	काष्ठा mac_configuration_entry config_table[64];
पूर्ण;


/*
 * Set-MAC command type (in E1x)
 */
क्रमागत set_mac_action_type अणु
	T_ETH_MAC_COMMAND_INVALIDATE,
	T_ETH_MAC_COMMAND_SET,
	MAX_SET_MAC_ACTION_TYPE
पूर्ण;


/*
 * Ethernet TPA Modes
 */
क्रमागत tpa_mode अणु
	TPA_LRO,
	TPA_GRO,
	MAX_TPA_MODEपूर्ण;


/*
 * tpa update ramrod data
 */
काष्ठा tpa_update_ramrod_data अणु
	u8 update_ipv4;
	u8 update_ipv6;
	u8 client_id;
	u8 max_tpa_queues;
	u8 max_sges_क्रम_packet;
	u8 complete_on_both_clients;
	u8 करोnt_verअगरy_rings_छोड़ो_thr_flg;
	u8 tpa_mode;
	__le16 sge_buff_size;
	__le16 max_agg_size;
	__le32 sge_page_base_lo;
	__le32 sge_page_base_hi;
	__le16 sge_छोड़ो_thr_low;
	__le16 sge_छोड़ो_thr_high;
	u8 tpa_over_vlan_disable;
	u8 reserved[7];
पूर्ण;


/*
 * approximate-match multicast filtering क्रम E1H per function in Tstorm
 */
काष्ठा tstorm_eth_approximate_match_multicast_filtering अणु
	u32 mcast_add_hash_bit_array[8];
पूर्ण;


/*
 * Common configuration parameters per function in Tstorm
 */
काष्ठा tstorm_eth_function_common_config अणु
	__le16 config_flags;
#घोषणा TSTORM_ETH_FUNCTION_COMMON_CONFIG_RSS_IPV4_CAPABILITY (0x1<<0)
#घोषणा TSTORM_ETH_FUNCTION_COMMON_CONFIG_RSS_IPV4_CAPABILITY_SHIFT 0
#घोषणा TSTORM_ETH_FUNCTION_COMMON_CONFIG_RSS_IPV4_TCP_CAPABILITY (0x1<<1)
#घोषणा TSTORM_ETH_FUNCTION_COMMON_CONFIG_RSS_IPV4_TCP_CAPABILITY_SHIFT 1
#घोषणा TSTORM_ETH_FUNCTION_COMMON_CONFIG_RSS_IPV6_CAPABILITY (0x1<<2)
#घोषणा TSTORM_ETH_FUNCTION_COMMON_CONFIG_RSS_IPV6_CAPABILITY_SHIFT 2
#घोषणा TSTORM_ETH_FUNCTION_COMMON_CONFIG_RSS_IPV6_TCP_CAPABILITY (0x1<<3)
#घोषणा TSTORM_ETH_FUNCTION_COMMON_CONFIG_RSS_IPV6_TCP_CAPABILITY_SHIFT 3
#घोषणा TSTORM_ETH_FUNCTION_COMMON_CONFIG_RSS_MODE (0x7<<4)
#घोषणा TSTORM_ETH_FUNCTION_COMMON_CONFIG_RSS_MODE_SHIFT 4
#घोषणा TSTORM_ETH_FUNCTION_COMMON_CONFIG_VLAN_FILTERING_ENABLE (0x1<<7)
#घोषणा TSTORM_ETH_FUNCTION_COMMON_CONFIG_VLAN_FILTERING_ENABLE_SHIFT 7
#घोषणा __TSTORM_ETH_FUNCTION_COMMON_CONFIG_RESERVED0 (0xFF<<8)
#घोषणा __TSTORM_ETH_FUNCTION_COMMON_CONFIG_RESERVED0_SHIFT 8
	u8 rss_result_mask;
	u8 reserved1;
	__le16 vlan_id[2];
पूर्ण;


/*
 * MAC filtering configuration parameters per port in Tstorm
 */
काष्ठा tstorm_eth_mac_filter_config अणु
	u32 ucast_drop_all;
	u32 ucast_accept_all;
	u32 mcast_drop_all;
	u32 mcast_accept_all;
	u32 bcast_accept_all;
	u32 vlan_filter[2];
	u32 unmatched_unicast;
पूर्ण;


/*
 * tx only queue init ramrod data
 */
काष्ठा tx_queue_init_ramrod_data अणु
	काष्ठा client_init_general_data general;
	काष्ठा client_init_tx_data tx;
पूर्ण;


/*
 * Three RX producers क्रम ETH
 */
काष्ठा ustorm_eth_rx_producers अणु
#अगर defined(__BIG_ENDIAN)
	u16 bd_prod;
	u16 cqe_prod;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 cqe_prod;
	u16 bd_prod;
#पूर्ण_अगर
#अगर defined(__BIG_ENDIAN)
	u16 reserved;
	u16 sge_prod;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 sge_prod;
	u16 reserved;
#पूर्ण_अगर
पूर्ण;


/*
 * FCoE RX statistics parameters section#0
 */
काष्ठा fcoe_rx_stat_params_section0 अणु
	__le32 fcoe_rx_pkt_cnt;
	__le32 fcoe_rx_byte_cnt;
पूर्ण;


/*
 * FCoE RX statistics parameters section#1
 */
काष्ठा fcoe_rx_stat_params_section1 अणु
	__le32 fcoe_ver_cnt;
	__le32 fcoe_rx_drop_pkt_cnt;
पूर्ण;


/*
 * FCoE RX statistics parameters section#2
 */
काष्ठा fcoe_rx_stat_params_section2 अणु
	__le32 fc_crc_cnt;
	__le32 eofa_del_cnt;
	__le32 miss_frame_cnt;
	__le32 seq_समयout_cnt;
	__le32 drop_seq_cnt;
	__le32 fcoe_rx_drop_pkt_cnt;
	__le32 fcp_rx_pkt_cnt;
	__le32 reserved0;
पूर्ण;


/*
 * FCoE TX statistics parameters
 */
काष्ठा fcoe_tx_stat_params अणु
	__le32 fcoe_tx_pkt_cnt;
	__le32 fcoe_tx_byte_cnt;
	__le32 fcp_tx_pkt_cnt;
	__le32 reserved0;
पूर्ण;

/*
 * FCoE statistics parameters
 */
काष्ठा fcoe_statistics_params अणु
	काष्ठा fcoe_tx_stat_params tx_stat;
	काष्ठा fcoe_rx_stat_params_section0 rx_stat0;
	काष्ठा fcoe_rx_stat_params_section1 rx_stat1;
	काष्ठा fcoe_rx_stat_params_section2 rx_stat2;
पूर्ण;


/*
 * The data afex vअगर list ramrod need
 */
काष्ठा afex_vअगर_list_ramrod_data अणु
	u8 afex_vअगर_list_command;
	u8 func_bit_map;
	__le16 vअगर_list_index;
	u8 func_to_clear;
	u8 echo;
	__le16 reserved1;
पूर्ण;

काष्ठा c2s_pri_trans_table_entry अणु
	u8 val[MAX_VLAN_PRIORITIES];
पूर्ण;

/*
 * cfc delete event data
 */
काष्ठा cfc_del_event_data अणु
	__le32 cid;
	__le32 reserved0;
	__le32 reserved1;
पूर्ण;


/*
 * per-port SAFC demo variables
 */
काष्ठा cmng_flags_per_port अणु
	u32 cmng_enables;
#घोषणा CMNG_FLAGS_PER_PORT_FAIRNESS_VN (0x1<<0)
#घोषणा CMNG_FLAGS_PER_PORT_FAIRNESS_VN_SHIFT 0
#घोषणा CMNG_FLAGS_PER_PORT_RATE_SHAPING_VN (0x1<<1)
#घोषणा CMNG_FLAGS_PER_PORT_RATE_SHAPING_VN_SHIFT 1
#घोषणा CMNG_FLAGS_PER_PORT_FAIRNESS_COS (0x1<<2)
#घोषणा CMNG_FLAGS_PER_PORT_FAIRNESS_COS_SHIFT 2
#घोषणा CMNG_FLAGS_PER_PORT_FAIRNESS_COS_MODE (0x1<<3)
#घोषणा CMNG_FLAGS_PER_PORT_FAIRNESS_COS_MODE_SHIFT 3
#घोषणा __CMNG_FLAGS_PER_PORT_RESERVED0 (0xFFFFFFF<<4)
#घोषणा __CMNG_FLAGS_PER_PORT_RESERVED0_SHIFT 4
	u32 __reserved1;
पूर्ण;


/*
 * per-port rate shaping variables
 */
काष्ठा rate_shaping_vars_per_port अणु
	u32 rs_periodic_समयout;
	u32 rs_threshold;
पूर्ण;

/*
 * per-port fairness variables
 */
काष्ठा fairness_vars_per_port अणु
	u32 upper_bound;
	u32 fair_threshold;
	u32 fairness_समयout;
	u32 माप_प्रकारhr;
पूर्ण;

/*
 * per-port SAFC variables
 */
काष्ठा safc_काष्ठा_per_port अणु
#अगर defined(__BIG_ENDIAN)
	u16 __reserved1;
	u8 __reserved0;
	u8 safc_समयout_usec;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 safc_समयout_usec;
	u8 __reserved0;
	u16 __reserved1;
#पूर्ण_अगर
	u8 cos_to_traffic_types[MAX_COS_NUMBER];
	u16 cos_to_छोड़ो_mask[NUM_OF_SAFC_BITS];
पूर्ण;

/*
 * Per-port congestion management variables
 */
काष्ठा cmng_काष्ठा_per_port अणु
	काष्ठा rate_shaping_vars_per_port rs_vars;
	काष्ठा fairness_vars_per_port fair_vars;
	काष्ठा safc_काष्ठा_per_port safc_vars;
	काष्ठा cmng_flags_per_port flags;
पूर्ण;

/*
 * a single rate shaping counter. can be used as protocol or vnic counter
 */
काष्ठा rate_shaping_counter अणु
	u32 quota;
#अगर defined(__BIG_ENDIAN)
	u16 __reserved0;
	u16 rate;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 rate;
	u16 __reserved0;
#पूर्ण_अगर
पूर्ण;

/*
 * per-vnic rate shaping variables
 */
काष्ठा rate_shaping_vars_per_vn अणु
	काष्ठा rate_shaping_counter vn_counter;
पूर्ण;

/*
 * per-vnic fairness variables
 */
काष्ठा fairness_vars_per_vn अणु
	u32 cos_credit_delta[MAX_COS_NUMBER];
	u32 vn_credit_delta;
	u32 __reserved0;
पूर्ण;

/*
 * cmng port init state
 */
काष्ठा cmng_vnic अणु
	काष्ठा rate_shaping_vars_per_vn vnic_max_rate[4];
	काष्ठा fairness_vars_per_vn vnic_min_rate[4];
पूर्ण;

/*
 * cmng port init state
 */
काष्ठा cmng_init अणु
	काष्ठा cmng_काष्ठा_per_port port;
	काष्ठा cmng_vnic vnic;
पूर्ण;


/*
 * driver parameters क्रम congestion management init, all rates are in Mbps
 */
काष्ठा cmng_init_input अणु
	u32 port_rate;
	u16 vnic_min_rate[4];
	u16 vnic_max_rate[4];
	u16 cos_min_rate[MAX_COS_NUMBER];
	u16 cos_to_छोड़ो_mask[MAX_COS_NUMBER];
	काष्ठा cmng_flags_per_port flags;
पूर्ण;


/*
 * Protocol-common command ID क्रम slow path elements
 */
क्रमागत common_spqe_cmd_id अणु
	RAMROD_CMD_ID_COMMON_UNUSED,
	RAMROD_CMD_ID_COMMON_FUNCTION_START,
	RAMROD_CMD_ID_COMMON_FUNCTION_STOP,
	RAMROD_CMD_ID_COMMON_FUNCTION_UPDATE,
	RAMROD_CMD_ID_COMMON_CFC_DEL,
	RAMROD_CMD_ID_COMMON_CFC_DEL_WB,
	RAMROD_CMD_ID_COMMON_STAT_QUERY,
	RAMROD_CMD_ID_COMMON_STOP_TRAFFIC,
	RAMROD_CMD_ID_COMMON_START_TRAFFIC,
	RAMROD_CMD_ID_COMMON_AFEX_VIF_LISTS,
	RAMROD_CMD_ID_COMMON_SET_TIMESYNC,
	MAX_COMMON_SPQE_CMD_ID
पूर्ण;

/*
 * Per-protocol connection types
 */
क्रमागत connection_type अणु
	ETH_CONNECTION_TYPE,
	TOE_CONNECTION_TYPE,
	RDMA_CONNECTION_TYPE,
	ISCSI_CONNECTION_TYPE,
	FCOE_CONNECTION_TYPE,
	RESERVED_CONNECTION_TYPE_0,
	RESERVED_CONNECTION_TYPE_1,
	RESERVED_CONNECTION_TYPE_2,
	NONE_CONNECTION_TYPE,
	MAX_CONNECTION_TYPE
पूर्ण;


/*
 * Cos modes
 */
क्रमागत cos_mode अणु
	OVERRIDE_COS,
	STATIC_COS,
	FW_WRR,
	MAX_COS_MODE
पूर्ण;


/*
 * Dynamic HC counters set by the driver
 */
काष्ठा hc_dynamic_drv_counter अणु
	u32 val[HC_SB_MAX_DYNAMIC_INDICES];
पूर्ण;

/*
 * zone A per-queue data
 */
काष्ठा cstorm_queue_zone_data अणु
	काष्ठा hc_dynamic_drv_counter hc_dyn_drv_cnt;
	काष्ठा regpair reserved[2];
पूर्ण;


/*
 * Vf-PF channel data in cstorm ram (non-triggered zone)
 */
काष्ठा vf_pf_channel_zone_data अणु
	u32 msg_addr_lo;
	u32 msg_addr_hi;
पूर्ण;

/*
 * zone क्रम VF non-triggered data
 */
काष्ठा non_trigger_vf_zone अणु
	काष्ठा vf_pf_channel_zone_data vf_pf_channel;
पूर्ण;

/*
 * Vf-PF channel trigger zone in cstorm ram
 */
काष्ठा vf_pf_channel_zone_trigger अणु
	u8 addr_valid;
पूर्ण;

/*
 * zone that triggers the in-bound पूर्णांकerrupt
 */
काष्ठा trigger_vf_zone अणु
	काष्ठा vf_pf_channel_zone_trigger vf_pf_channel;
	u8 reserved0;
	u16 reserved1;
	u32 reserved2;
पूर्ण;

/*
 * zone B per-VF data
 */
काष्ठा cstorm_vf_zone_data अणु
	काष्ठा non_trigger_vf_zone non_trigger;
	काष्ठा trigger_vf_zone trigger;
पूर्ण;


/*
 * Dynamic host coalescing init parameters, per state machine
 */
काष्ठा dynamic_hc_sm_config अणु
	u32 threshold[3];
	u8 shअगरt_per_protocol[HC_SB_MAX_DYNAMIC_INDICES];
	u8 hc_समयout0[HC_SB_MAX_DYNAMIC_INDICES];
	u8 hc_समयout1[HC_SB_MAX_DYNAMIC_INDICES];
	u8 hc_समयout2[HC_SB_MAX_DYNAMIC_INDICES];
	u8 hc_समयout3[HC_SB_MAX_DYNAMIC_INDICES];
पूर्ण;

/*
 * Dynamic host coalescing init parameters
 */
काष्ठा dynamic_hc_config अणु
	काष्ठा dynamic_hc_sm_config sm_config[HC_SB_MAX_SM];
पूर्ण;


काष्ठा e2_पूर्णांकeg_data अणु
#अगर defined(__BIG_ENDIAN)
	u8 flags;
#घोषणा E2_INTEG_DATA_TESTING_EN (0x1<<0)
#घोषणा E2_INTEG_DATA_TESTING_EN_SHIFT 0
#घोषणा E2_INTEG_DATA_LB_TX (0x1<<1)
#घोषणा E2_INTEG_DATA_LB_TX_SHIFT 1
#घोषणा E2_INTEG_DATA_COS_TX (0x1<<2)
#घोषणा E2_INTEG_DATA_COS_TX_SHIFT 2
#घोषणा E2_INTEG_DATA_OPPORTUNISTICQM (0x1<<3)
#घोषणा E2_INTEG_DATA_OPPORTUNISTICQM_SHIFT 3
#घोषणा E2_INTEG_DATA_DPMTESTRELEASEDQ (0x1<<4)
#घोषणा E2_INTEG_DATA_DPMTESTRELEASEDQ_SHIFT 4
#घोषणा E2_INTEG_DATA_RESERVED (0x7<<5)
#घोषणा E2_INTEG_DATA_RESERVED_SHIFT 5
	u8 cos;
	u8 voq;
	u8 pbf_queue;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 pbf_queue;
	u8 voq;
	u8 cos;
	u8 flags;
#घोषणा E2_INTEG_DATA_TESTING_EN (0x1<<0)
#घोषणा E2_INTEG_DATA_TESTING_EN_SHIFT 0
#घोषणा E2_INTEG_DATA_LB_TX (0x1<<1)
#घोषणा E2_INTEG_DATA_LB_TX_SHIFT 1
#घोषणा E2_INTEG_DATA_COS_TX (0x1<<2)
#घोषणा E2_INTEG_DATA_COS_TX_SHIFT 2
#घोषणा E2_INTEG_DATA_OPPORTUNISTICQM (0x1<<3)
#घोषणा E2_INTEG_DATA_OPPORTUNISTICQM_SHIFT 3
#घोषणा E2_INTEG_DATA_DPMTESTRELEASEDQ (0x1<<4)
#घोषणा E2_INTEG_DATA_DPMTESTRELEASEDQ_SHIFT 4
#घोषणा E2_INTEG_DATA_RESERVED (0x7<<5)
#घोषणा E2_INTEG_DATA_RESERVED_SHIFT 5
#पूर्ण_अगर
#अगर defined(__BIG_ENDIAN)
	u16 reserved3;
	u8 reserved2;
	u8 ramEn;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 ramEn;
	u8 reserved2;
	u16 reserved3;
#पूर्ण_अगर
पूर्ण;


/*
 * set mac event data
 */
काष्ठा eth_event_data अणु
	__le32 echo;
	__le32 reserved0;
	__le32 reserved1;
पूर्ण;


/*
 * pf-vf event data
 */
काष्ठा vf_pf_event_data अणु
	u8 vf_id;
	u8 reserved0;
	__le16 reserved1;
	__le32 msg_addr_lo;
	__le32 msg_addr_hi;
पूर्ण;

/*
 * VF FLR event data
 */
काष्ठा vf_flr_event_data अणु
	u8 vf_id;
	u8 reserved0;
	__le16 reserved1;
	__le32 reserved2;
	__le32 reserved3;
पूर्ण;

/*
 * malicious VF event data
 */
काष्ठा malicious_vf_event_data अणु
	u8 vf_id;
	u8 err_id;
	__le16 reserved1;
	__le32 reserved2;
	__le32 reserved3;
पूर्ण;

/*
 * vअगर list event data
 */
काष्ठा vअगर_list_event_data अणु
	u8 func_bit_map;
	u8 echo;
	__le16 reserved0;
	__le32 reserved1;
	__le32 reserved2;
पूर्ण;

/* function update event data */
काष्ठा function_update_event_data अणु
	u8 echo;
	u8 reserved;
	__le16 reserved0;
	__le32 reserved1;
	__le32 reserved2;
पूर्ण;


/* जोड़ क्रम all event ring message types */
जोड़ event_data अणु
	काष्ठा vf_pf_event_data vf_pf_event;
	काष्ठा eth_event_data eth_event;
	काष्ठा cfc_del_event_data cfc_del_event;
	काष्ठा vf_flr_event_data vf_flr_event;
	काष्ठा malicious_vf_event_data malicious_vf_event;
	काष्ठा vअगर_list_event_data vअगर_list_event;
	काष्ठा function_update_event_data function_update_event;
पूर्ण;


/*
 * per PF event ring data
 */
काष्ठा event_ring_data अणु
	काष्ठा regpair_native base_addr;
#अगर defined(__BIG_ENDIAN)
	u8 index_id;
	u8 sb_id;
	u16 producer;
#या_अगर defined(__LITTLE_ENDIAN)
	u16 producer;
	u8 sb_id;
	u8 index_id;
#पूर्ण_अगर
	u32 reserved0;
पूर्ण;


/*
 * event ring message element (each element is 128 bits)
 */
काष्ठा event_ring_msg अणु
	u8 opcode;
	u8 error;
	u16 reserved1;
	जोड़ event_data data;
पूर्ण;

/*
 * event ring next page element (128 bits)
 */
काष्ठा event_ring_next अणु
	काष्ठा regpair addr;
	u32 reserved[2];
पूर्ण;

/*
 * जोड़ क्रम event ring element types (each element is 128 bits)
 */
जोड़ event_ring_elem अणु
	काष्ठा event_ring_msg message;
	काष्ठा event_ring_next next_page;
पूर्ण;


/*
 * Common event ring opcodes
 */
क्रमागत event_ring_opcode अणु
	EVENT_RING_OPCODE_VF_PF_CHANNEL,
	EVENT_RING_OPCODE_FUNCTION_START,
	EVENT_RING_OPCODE_FUNCTION_STOP,
	EVENT_RING_OPCODE_CFC_DEL,
	EVENT_RING_OPCODE_CFC_DEL_WB,
	EVENT_RING_OPCODE_STAT_QUERY,
	EVENT_RING_OPCODE_STOP_TRAFFIC,
	EVENT_RING_OPCODE_START_TRAFFIC,
	EVENT_RING_OPCODE_VF_FLR,
	EVENT_RING_OPCODE_MALICIOUS_VF,
	EVENT_RING_OPCODE_FORWARD_SETUP,
	EVENT_RING_OPCODE_RSS_UPDATE_RULES,
	EVENT_RING_OPCODE_FUNCTION_UPDATE,
	EVENT_RING_OPCODE_AFEX_VIF_LISTS,
	EVENT_RING_OPCODE_SET_MAC,
	EVENT_RING_OPCODE_CLASSIFICATION_RULES,
	EVENT_RING_OPCODE_FILTERS_RULES,
	EVENT_RING_OPCODE_MULTICAST_RULES,
	EVENT_RING_OPCODE_SET_TIMESYNC,
	MAX_EVENT_RING_OPCODE
पूर्ण;

/*
 * Modes क्रम fairness algorithm
 */
क्रमागत fairness_mode अणु
	FAIRNESS_COS_WRR_MODE,
	FAIRNESS_COS_ETS_MODE,
	MAX_FAIRNESS_MODE
पूर्ण;


/*
 * Priority and cos
 */
काष्ठा priority_cos अणु
	u8 priority;
	u8 cos;
	__le16 reserved1;
पूर्ण;

/*
 * The data क्रम flow control configuration
 */
काष्ठा flow_control_configuration अणु
	काष्ठा priority_cos traffic_type_to_priority_cos[MAX_TRAFFIC_TYPES];
	u8 dcb_enabled;
	u8 dcb_version;
	u8 करोnt_add_pri_0_en;
	u8 reserved1;
	__le32 reserved2;
	u8 dcb_outer_pri[MAX_TRAFFIC_TYPES];
पूर्ण;


/*
 *
 */
काष्ठा function_start_data अणु
	u8 function_mode;
	u8 allow_npar_tx_चयनing;
	__le16 sd_vlan_tag;
	__le16 vअगर_id;
	u8 path_id;
	u8 network_cos_mode;
	u8 dmae_cmd_id;
	u8 no_added_tags;
	__le16 reserved0;
	__le32 reserved1;
	u8 inner_clss_vxlan;
	u8 inner_clss_l2gre;
	u8 inner_clss_l2geneve;
	u8 inner_rss;
	__le16 vxlan_dst_port;
	__le16 geneve_dst_port;
	u8 sd_accept_mf_clss_fail;
	u8 sd_accept_mf_clss_fail_match_ethtype;
	__le16 sd_accept_mf_clss_fail_ethtype;
	__le16 sd_vlan_eth_type;
	u8 sd_vlan_क्रमce_pri_flg;
	u8 sd_vlan_क्रमce_pri_val;
	u8 c2s_pri_tt_valid;
	u8 c2s_pri_शेष;
	u8 tx_vlan_filtering_enable;
	u8 tx_vlan_filtering_use_pvid;
	u8 reserved2[4];
	काष्ठा c2s_pri_trans_table_entry c2s_pri_trans_table;
पूर्ण;

काष्ठा function_update_data अणु
	u8 vअगर_id_change_flg;
	u8 afex_शेष_vlan_change_flg;
	u8 allowed_priorities_change_flg;
	u8 network_cos_mode_change_flg;
	__le16 vअगर_id;
	__le16 afex_शेष_vlan;
	u8 allowed_priorities;
	u8 network_cos_mode;
	u8 lb_mode_en_change_flg;
	u8 lb_mode_en;
	u8 tx_चयन_suspend_change_flg;
	u8 tx_चयन_suspend;
	u8 echo;
	u8 update_tunn_cfg_flg;
	u8 inner_clss_vxlan;
	u8 inner_clss_l2gre;
	u8 inner_clss_l2geneve;
	u8 inner_rss;
	__le16 vxlan_dst_port;
	__le16 geneve_dst_port;
	u8 sd_vlan_क्रमce_pri_change_flg;
	u8 sd_vlan_क्रमce_pri_flg;
	u8 sd_vlan_क्रमce_pri_val;
	u8 sd_vlan_tag_change_flg;
	u8 sd_vlan_eth_type_change_flg;
	u8 reserved1;
	__le16 sd_vlan_tag;
	__le16 sd_vlan_eth_type;
	u8 tx_vlan_filtering_pvid_change_flg;
	u8 reserved0;
	__le32 reserved2;
पूर्ण;

/*
 * FW version stored in the Xstorm RAM
 */
काष्ठा fw_version अणु
#अगर defined(__BIG_ENDIAN)
	u8 engineering;
	u8 revision;
	u8 minor;
	u8 major;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 major;
	u8 minor;
	u8 revision;
	u8 engineering;
#पूर्ण_अगर
	u32 flags;
#घोषणा FW_VERSION_OPTIMIZED (0x1<<0)
#घोषणा FW_VERSION_OPTIMIZED_SHIFT 0
#घोषणा FW_VERSION_BIG_ENDIEN (0x1<<1)
#घोषणा FW_VERSION_BIG_ENDIEN_SHIFT 1
#घोषणा FW_VERSION_CHIP_VERSION (0x3<<2)
#घोषणा FW_VERSION_CHIP_VERSION_SHIFT 2
#घोषणा __FW_VERSION_RESERVED (0xFFFFFFF<<4)
#घोषणा __FW_VERSION_RESERVED_SHIFT 4
पूर्ण;

/*
 * Dynamic Host-Coalescing - Driver(host) counters
 */
काष्ठा hc_dynamic_sb_drv_counters अणु
	u32 dynamic_hc_drv_counter[HC_SB_MAX_DYNAMIC_INDICES];
पूर्ण;


/*
 * 2 bytes. configuration/state parameters क्रम a single protocol index
 */
काष्ठा hc_index_data अणु
#अगर defined(__BIG_ENDIAN)
	u8 flags;
#घोषणा HC_INDEX_DATA_SM_ID (0x1<<0)
#घोषणा HC_INDEX_DATA_SM_ID_SHIFT 0
#घोषणा HC_INDEX_DATA_HC_ENABLED (0x1<<1)
#घोषणा HC_INDEX_DATA_HC_ENABLED_SHIFT 1
#घोषणा HC_INDEX_DATA_DYNAMIC_HC_ENABLED (0x1<<2)
#घोषणा HC_INDEX_DATA_DYNAMIC_HC_ENABLED_SHIFT 2
#घोषणा HC_INDEX_DATA_RESERVE (0x1F<<3)
#घोषणा HC_INDEX_DATA_RESERVE_SHIFT 3
	u8 समयout;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 समयout;
	u8 flags;
#घोषणा HC_INDEX_DATA_SM_ID (0x1<<0)
#घोषणा HC_INDEX_DATA_SM_ID_SHIFT 0
#घोषणा HC_INDEX_DATA_HC_ENABLED (0x1<<1)
#घोषणा HC_INDEX_DATA_HC_ENABLED_SHIFT 1
#घोषणा HC_INDEX_DATA_DYNAMIC_HC_ENABLED (0x1<<2)
#घोषणा HC_INDEX_DATA_DYNAMIC_HC_ENABLED_SHIFT 2
#घोषणा HC_INDEX_DATA_RESERVE (0x1F<<3)
#घोषणा HC_INDEX_DATA_RESERVE_SHIFT 3
#पूर्ण_अगर
पूर्ण;


/*
 * HC state-machine
 */
काष्ठा hc_status_block_sm अणु
#अगर defined(__BIG_ENDIAN)
	u8 igu_seg_id;
	u8 igu_sb_id;
	u8 समयr_value;
	u8 __flags;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 __flags;
	u8 समयr_value;
	u8 igu_sb_id;
	u8 igu_seg_id;
#पूर्ण_अगर
	u32 समय_प्रकारo_expire;
पूर्ण;

/*
 * hold PCI identअगरication variables- used in various places in firmware
 */
काष्ठा pci_entity अणु
#अगर defined(__BIG_ENDIAN)
	u8 vf_valid;
	u8 vf_id;
	u8 vnic_id;
	u8 pf_id;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 pf_id;
	u8 vnic_id;
	u8 vf_id;
	u8 vf_valid;
#पूर्ण_अगर
पूर्ण;

/*
 * The fast-path status block meta-data, common to all chips
 */
काष्ठा hc_sb_data अणु
	काष्ठा regpair_native host_sb_addr;
	काष्ठा hc_status_block_sm state_machine[HC_SB_MAX_SM];
	काष्ठा pci_entity p_func;
#अगर defined(__BIG_ENDIAN)
	u8 rsrv0;
	u8 state;
	u8 dhc_qzone_id;
	u8 same_igu_sb_1b;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 same_igu_sb_1b;
	u8 dhc_qzone_id;
	u8 state;
	u8 rsrv0;
#पूर्ण_अगर
	काष्ठा regpair_native rsrv1[2];
पूर्ण;


/*
 * Segment types क्रम host coaslescing
 */
क्रमागत hc_segment अणु
	HC_REGULAR_SEGMENT,
	HC_DEFAULT_SEGMENT,
	MAX_HC_SEGMENT
पूर्ण;


/*
 * The fast-path status block meta-data
 */
काष्ठा hc_sp_status_block_data अणु
	काष्ठा regpair_native host_sb_addr;
#अगर defined(__BIG_ENDIAN)
	u8 rsrv1;
	u8 state;
	u8 igu_seg_id;
	u8 igu_sb_id;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 igu_sb_id;
	u8 igu_seg_id;
	u8 state;
	u8 rsrv1;
#पूर्ण_अगर
	काष्ठा pci_entity p_func;
पूर्ण;


/*
 * The fast-path status block meta-data
 */
काष्ठा hc_status_block_data_e1x अणु
	काष्ठा hc_index_data index_data[HC_SB_MAX_INDICES_E1X];
	काष्ठा hc_sb_data common;
पूर्ण;


/*
 * The fast-path status block meta-data
 */
काष्ठा hc_status_block_data_e2 अणु
	काष्ठा hc_index_data index_data[HC_SB_MAX_INDICES_E2];
	काष्ठा hc_sb_data common;
पूर्ण;


/*
 * IGU block operartion modes (in Everest2)
 */
क्रमागत igu_mode अणु
	HC_IGU_BC_MODE,
	HC_IGU_NBC_MODE,
	MAX_IGU_MODE
पूर्ण;

/*
 * Inner Headers Classअगरication Type
 */
क्रमागत inner_clss_type अणु
	INNER_CLSS_DISABLED,
	INNER_CLSS_USE_VLAN,
	INNER_CLSS_USE_VNI,
	MAX_INNER_CLSS_TYPEपूर्ण;

/*
 * IP versions
 */
क्रमागत ip_ver अणु
	IP_V4,
	IP_V6,
	MAX_IP_VER
पूर्ण;

/*
 * Malicious VF error ID
 */
क्रमागत malicious_vf_error_id अणु
	MALICIOUS_VF_NO_ERROR,
	VF_PF_CHANNEL_NOT_READY,
	ETH_ILLEGAL_BD_LENGTHS,
	ETH_PACKET_TOO_SHORT,
	ETH_PAYLOAD_TOO_BIG,
	ETH_ILLEGAL_ETH_TYPE,
	ETH_ILLEGAL_LSO_HDR_LEN,
	ETH_TOO_MANY_BDS,
	ETH_ZERO_HDR_NBDS,
	ETH_START_BD_NOT_SET,
	ETH_ILLEGAL_PARSE_NBDS,
	ETH_IPV6_AND_CHECKSUM,
	ETH_VLAN_FLG_INCORRECT,
	ETH_ILLEGAL_LSO_MSS,
	ETH_TUNNEL_NOT_SUPPORTED,
	MAX_MALICIOUS_VF_ERROR_ID
पूर्ण;

/*
 * Multi-function modes
 */
क्रमागत mf_mode अणु
	SINGLE_FUNCTION,
	MULTI_FUNCTION_SD,
	MULTI_FUNCTION_SI,
	MULTI_FUNCTION_AFEX,
	MAX_MF_MODE
पूर्ण;

/*
 * Protocol-common statistics collected by the Tstorm (per pf)
 */
काष्ठा tstorm_per_pf_stats अणु
	काष्ठा regpair rcv_error_bytes;
पूर्ण;

/*
 *
 */
काष्ठा per_pf_stats अणु
	काष्ठा tstorm_per_pf_stats tstorm_pf_statistics;
पूर्ण;


/*
 * Protocol-common statistics collected by the Tstorm (per port)
 */
काष्ठा tstorm_per_port_stats अणु
	__le32 mac_discard;
	__le32 mac_filter_discard;
	__le32 brb_truncate_discard;
	__le32 mf_tag_discard;
	__le32 packet_drop;
	__le32 reserved;
पूर्ण;

/*
 *
 */
काष्ठा per_port_stats अणु
	काष्ठा tstorm_per_port_stats tstorm_port_statistics;
पूर्ण;


/*
 * Protocol-common statistics collected by the Tstorm (per client)
 */
काष्ठा tstorm_per_queue_stats अणु
	काष्ठा regpair rcv_ucast_bytes;
	__le32 rcv_ucast_pkts;
	__le32 checksum_discard;
	काष्ठा regpair rcv_bcast_bytes;
	__le32 rcv_bcast_pkts;
	__le32 pkts_too_big_discard;
	काष्ठा regpair rcv_mcast_bytes;
	__le32 rcv_mcast_pkts;
	__le32 ttl0_discard;
	__le16 no_buff_discard;
	__le16 reserved0;
	__le32 reserved1;
पूर्ण;

/*
 * Protocol-common statistics collected by the Ustorm (per client)
 */
काष्ठा ustorm_per_queue_stats अणु
	काष्ठा regpair ucast_no_buff_bytes;
	काष्ठा regpair mcast_no_buff_bytes;
	काष्ठा regpair bcast_no_buff_bytes;
	__le32 ucast_no_buff_pkts;
	__le32 mcast_no_buff_pkts;
	__le32 bcast_no_buff_pkts;
	__le32 coalesced_pkts;
	काष्ठा regpair coalesced_bytes;
	__le32 coalesced_events;
	__le32 coalesced_पातs;
पूर्ण;

/*
 * Protocol-common statistics collected by the Xstorm (per client)
 */
काष्ठा xstorm_per_queue_stats अणु
	काष्ठा regpair ucast_bytes_sent;
	काष्ठा regpair mcast_bytes_sent;
	काष्ठा regpair bcast_bytes_sent;
	__le32 ucast_pkts_sent;
	__le32 mcast_pkts_sent;
	__le32 bcast_pkts_sent;
	__le32 error_drop_pkts;
पूर्ण;

/*
 *
 */
काष्ठा per_queue_stats अणु
	काष्ठा tstorm_per_queue_stats tstorm_queue_statistics;
	काष्ठा ustorm_per_queue_stats ustorm_queue_statistics;
	काष्ठा xstorm_per_queue_stats xstorm_queue_statistics;
पूर्ण;


/*
 * FW version stored in first line of pram
 */
काष्ठा pram_fw_version अणु
	u8 major;
	u8 minor;
	u8 revision;
	u8 engineering;
	u8 flags;
#घोषणा PRAM_FW_VERSION_OPTIMIZED (0x1<<0)
#घोषणा PRAM_FW_VERSION_OPTIMIZED_SHIFT 0
#घोषणा PRAM_FW_VERSION_STORM_ID (0x3<<1)
#घोषणा PRAM_FW_VERSION_STORM_ID_SHIFT 1
#घोषणा PRAM_FW_VERSION_BIG_ENDIEN (0x1<<3)
#घोषणा PRAM_FW_VERSION_BIG_ENDIEN_SHIFT 3
#घोषणा PRAM_FW_VERSION_CHIP_VERSION (0x3<<4)
#घोषणा PRAM_FW_VERSION_CHIP_VERSION_SHIFT 4
#घोषणा __PRAM_FW_VERSION_RESERVED0 (0x3<<6)
#घोषणा __PRAM_FW_VERSION_RESERVED0_SHIFT 6
पूर्ण;


/*
 * Ethernet slow path element
 */
जोड़ protocol_common_specअगरic_data अणु
	u8 protocol_data[8];
	काष्ठा regpair phy_address;
	काष्ठा regpair mac_config_addr;
	काष्ठा afex_vअगर_list_ramrod_data afex_vअगर_list_data;
पूर्ण;

/*
 * The send queue element
 */
काष्ठा protocol_common_spe अणु
	काष्ठा spe_hdr hdr;
	जोड़ protocol_common_specअगरic_data data;
पूर्ण;

/* The data क्रम the Set Timesync Ramrod */
काष्ठा set_बारync_ramrod_data अणु
	u8 drअगरt_adjust_cmd;
	u8 offset_cmd;
	u8 add_sub_drअगरt_adjust_value;
	u8 drअगरt_adjust_value;
	u32 drअगरt_adjust_period;
	काष्ठा regpair offset_delta;
पूर्ण;

/*
 * The send queue element
 */
काष्ठा slow_path_element अणु
	काष्ठा spe_hdr hdr;
	काष्ठा regpair protocol_data;
पूर्ण;


/*
 * Protocol-common statistics counter
 */
काष्ठा stats_counter अणु
	__le16 xstats_counter;
	__le16 reserved0;
	__le32 reserved1;
	__le16 tstats_counter;
	__le16 reserved2;
	__le32 reserved3;
	__le16 ustats_counter;
	__le16 reserved4;
	__le32 reserved5;
	__le16 cstats_counter;
	__le16 reserved6;
	__le32 reserved7;
पूर्ण;


/*
 *
 */
काष्ठा stats_query_entry अणु
	u8 kind;
	u8 index;
	__le16 funcID;
	__le32 reserved;
	काष्ठा regpair address;
पूर्ण;

/*
 * statistic command
 */
काष्ठा stats_query_cmd_group अणु
	काष्ठा stats_query_entry query[STATS_QUERY_CMD_COUNT];
पूर्ण;


/*
 * statistic command header
 */
काष्ठा stats_query_header अणु
	u8 cmd_num;
	u8 reserved0;
	__le16 drv_stats_counter;
	__le32 reserved1;
	काष्ठा regpair stats_counters_addrs;
पूर्ण;


/*
 * Types of statistcis query entry
 */
क्रमागत stats_query_type अणु
	STATS_TYPE_QUEUE,
	STATS_TYPE_PORT,
	STATS_TYPE_PF,
	STATS_TYPE_TOE,
	STATS_TYPE_FCOE,
	MAX_STATS_QUERY_TYPE
पूर्ण;


/*
 * Indicate of the function status block state
 */
क्रमागत status_block_state अणु
	SB_DISABLED,
	SB_ENABLED,
	SB_CLEANED,
	MAX_STATUS_BLOCK_STATE
पूर्ण;


/*
 * Storm IDs (including attentions क्रम IGU related क्रमागतs)
 */
क्रमागत storm_id अणु
	USTORM_ID,
	CSTORM_ID,
	XSTORM_ID,
	TSTORM_ID,
	ATTENTION_ID,
	MAX_STORM_ID
पूर्ण;


/*
 * Taffic types used in ETS and flow control algorithms
 */
क्रमागत traffic_type अणु
	LLFC_TRAFFIC_TYPE_NW,
	LLFC_TRAFFIC_TYPE_FCOE,
	LLFC_TRAFFIC_TYPE_ISCSI,
	MAX_TRAFFIC_TYPE
पूर्ण;


/*
 * zone A per-queue data
 */
काष्ठा tstorm_queue_zone_data अणु
	काष्ठा regpair reserved[4];
पूर्ण;


/*
 * zone B per-VF data
 */
काष्ठा tstorm_vf_zone_data अणु
	काष्ठा regpair reserved;
पूर्ण;

/* Add or Subtract Value क्रम Set Timesync Ramrod */
क्रमागत ts_add_sub_value अणु
	TS_SUB_VALUE,
	TS_ADD_VALUE,
	MAX_TS_ADD_SUB_VALUE
पूर्ण;

/* Drअगरt-Adjust Commands क्रम Set Timesync Ramrod */
क्रमागत ts_drअगरt_adjust_cmd अणु
	TS_DRIFT_ADJUST_KEEP,
	TS_DRIFT_ADJUST_SET,
	TS_DRIFT_ADJUST_RESET,
	MAX_TS_DRIFT_ADJUST_CMD
पूर्ण;

/* Offset Commands क्रम Set Timesync Ramrod */
क्रमागत ts_offset_cmd अणु
	TS_OFFSET_KEEP,
	TS_OFFSET_INC,
	TS_OFFSET_DEC,
	MAX_TS_OFFSET_CMD
पूर्ण;

 /* zone A per-queue data */
काष्ठा ustorm_queue_zone_data अणु
	काष्ठा ustorm_eth_rx_producers eth_rx_producers;
	काष्ठा regpair reserved[3];
पूर्ण;


/*
 * zone B per-VF data
 */
काष्ठा ustorm_vf_zone_data अणु
	काष्ठा regpair reserved;
पूर्ण;


/*
 * data per VF-PF channel
 */
काष्ठा vf_pf_channel_data अणु
#अगर defined(__BIG_ENDIAN)
	u16 reserved0;
	u8 valid;
	u8 state;
#या_अगर defined(__LITTLE_ENDIAN)
	u8 state;
	u8 valid;
	u16 reserved0;
#पूर्ण_अगर
	u32 reserved1;
पूर्ण;


/*
 * State of VF-PF channel
 */
क्रमागत vf_pf_channel_state अणु
	VF_PF_CHANNEL_STATE_READY,
	VF_PF_CHANNEL_STATE_WAITING_FOR_ACK,
	MAX_VF_PF_CHANNEL_STATE
पूर्ण;


/*
 * vअगर_list_rule_kind
 */
क्रमागत vअगर_list_rule_kind अणु
	VIF_LIST_RULE_SET,
	VIF_LIST_RULE_GET,
	VIF_LIST_RULE_CLEAR_ALL,
	VIF_LIST_RULE_CLEAR_FUNC,
	MAX_VIF_LIST_RULE_KIND
पूर्ण;


/*
 * zone A per-queue data
 */
काष्ठा xstorm_queue_zone_data अणु
	काष्ठा regpair reserved[4];
पूर्ण;


/*
 * zone B per-VF data
 */
काष्ठा xstorm_vf_zone_data अणु
	काष्ठा regpair reserved;
पूर्ण;

#पूर्ण_अगर /* BNX2X_HSI_H */
