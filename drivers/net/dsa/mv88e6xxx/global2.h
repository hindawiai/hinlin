<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Marvell 88E6xxx Switch Global 2 Registers support
 *
 * Copyright (c) 2008 Marvell Semiconductor
 *
 * Copyright (c) 2016-2017 Savoir-faire Linux Inc.
 *	Vivien Didelot <vivien.didelot@savoirfairelinux.com>
 */

#अगर_अघोषित _MV88E6XXX_GLOBAL2_H
#घोषणा _MV88E6XXX_GLOBAL2_H

#समावेश "chip.h"

/* Offset 0x00: Interrupt Source Register */
#घोषणा MV88E6XXX_G2_INT_SRC			0x00
#घोषणा MV88E6XXX_G2_INT_SRC_WDOG		0x8000
#घोषणा MV88E6XXX_G2_INT_SRC_JAM_LIMIT		0x4000
#घोषणा MV88E6XXX_G2_INT_SRC_DUPLEX_MISMATCH	0x2000
#घोषणा MV88E6XXX_G2_INT_SRC_WAKE_EVENT		0x1000
#घोषणा MV88E6352_G2_INT_SRC_SERDES		0x0800
#घोषणा MV88E6352_G2_INT_SRC_PHY		0x001f
#घोषणा MV88E6390_G2_INT_SRC_PHY		0x07fe

#घोषणा MV88E6XXX_G2_INT_SOURCE_WATCHDOG	15

/* Offset 0x01: Interrupt Mask Register */
#घोषणा MV88E6XXX_G2_INT_MASK			0x01
#घोषणा MV88E6XXX_G2_INT_MASK_WDOG		0x8000
#घोषणा MV88E6XXX_G2_INT_MASK_JAM_LIMIT		0x4000
#घोषणा MV88E6XXX_G2_INT_MASK_DUPLEX_MISMATCH	0x2000
#घोषणा MV88E6XXX_G2_INT_MASK_WAKE_EVENT	0x1000
#घोषणा MV88E6352_G2_INT_MASK_SERDES		0x0800
#घोषणा MV88E6352_G2_INT_MASK_PHY		0x001f
#घोषणा MV88E6390_G2_INT_MASK_PHY		0x07fe

/* Offset 0x02: MGMT Enable Register 2x */
#घोषणा MV88E6XXX_G2_MGMT_EN_2X		0x02

/* Offset 0x02: MAC LINK change IRQ Register क्रम MV88E6393X */
#घोषणा MV88E6393X_G2_MACLINK_INT_SRC		0x02

/* Offset 0x03: MGMT Enable Register 0x */
#घोषणा MV88E6XXX_G2_MGMT_EN_0X		0x03

/* Offset 0x03: MAC LINK change IRQ Mask Register क्रम MV88E6393X */
#घोषणा MV88E6393X_G2_MACLINK_INT_MASK		0x03

/* Offset 0x04: Flow Control Delay Register */
#घोषणा MV88E6XXX_G2_FLOW_CTL	0x04

/* Offset 0x05: Switch Management Register */
#घोषणा MV88E6XXX_G2_SWITCH_MGMT			0x05
#घोषणा MV88E6XXX_G2_SWITCH_MGMT_USE_DOUBLE_TAG_DATA	0x8000
#घोषणा MV88E6XXX_G2_SWITCH_MGMT_PREVENT_LOOPS		0x4000
#घोषणा MV88E6XXX_G2_SWITCH_MGMT_FLOW_CTL_MSG		0x2000
#घोषणा MV88E6XXX_G2_SWITCH_MGMT_FORCE_FLOW_CTL_PRI	0x0080
#घोषणा MV88E6XXX_G2_SWITCH_MGMT_RSVD2CPU		0x0008

#घोषणा MV88E6393X_G2_EGRESS_MONITOR_DEST		0x05

/* Offset 0x06: Device Mapping Table Register */
#घोषणा MV88E6XXX_G2_DEVICE_MAPPING		0x06
#घोषणा MV88E6XXX_G2_DEVICE_MAPPING_UPDATE	0x8000
#घोषणा MV88E6XXX_G2_DEVICE_MAPPING_DEV_MASK	0x1f00
#घोषणा MV88E6352_G2_DEVICE_MAPPING_PORT_MASK	0x000f
#घोषणा MV88E6390_G2_DEVICE_MAPPING_PORT_MASK	0x001f

/* Offset 0x07: Trunk Mask Table Register */
#घोषणा MV88E6XXX_G2_TRUNK_MASK			0x07
#घोषणा MV88E6XXX_G2_TRUNK_MASK_UPDATE		0x8000
#घोषणा MV88E6XXX_G2_TRUNK_MASK_NUM_MASK	0x7000
#घोषणा MV88E6XXX_G2_TRUNK_MASK_HASH		0x0800

/* Offset 0x08: Trunk Mapping Table Register */
#घोषणा MV88E6XXX_G2_TRUNK_MAPPING		0x08
#घोषणा MV88E6XXX_G2_TRUNK_MAPPING_UPDATE	0x8000
#घोषणा MV88E6XXX_G2_TRUNK_MAPPING_ID_MASK	0x7800

/* Offset 0x09: Ingress Rate Command Register */
#घोषणा MV88E6XXX_G2_IRL_CMD			0x09
#घोषणा MV88E6XXX_G2_IRL_CMD_BUSY		0x8000
#घोषणा MV88E6352_G2_IRL_CMD_OP_MASK		0x7000
#घोषणा MV88E6352_G2_IRL_CMD_OP_NOOP		0x0000
#घोषणा MV88E6352_G2_IRL_CMD_OP_INIT_ALL	0x1000
#घोषणा MV88E6352_G2_IRL_CMD_OP_INIT_RES	0x2000
#घोषणा MV88E6352_G2_IRL_CMD_OP_WRITE_REG	0x3000
#घोषणा MV88E6352_G2_IRL_CMD_OP_READ_REG	0x4000
#घोषणा MV88E6390_G2_IRL_CMD_OP_MASK		0x6000
#घोषणा MV88E6390_G2_IRL_CMD_OP_READ_REG	0x0000
#घोषणा MV88E6390_G2_IRL_CMD_OP_INIT_ALL	0x2000
#घोषणा MV88E6390_G2_IRL_CMD_OP_INIT_RES	0x4000
#घोषणा MV88E6390_G2_IRL_CMD_OP_WRITE_REG	0x6000
#घोषणा MV88E6352_G2_IRL_CMD_PORT_MASK		0x0f00
#घोषणा MV88E6390_G2_IRL_CMD_PORT_MASK		0x1f00
#घोषणा MV88E6XXX_G2_IRL_CMD_RES_MASK		0x00e0
#घोषणा MV88E6XXX_G2_IRL_CMD_REG_MASK		0x000f

/* Offset 0x0A: Ingress Rate Data Register */
#घोषणा MV88E6XXX_G2_IRL_DATA		0x0a
#घोषणा MV88E6XXX_G2_IRL_DATA_MASK	0xffff

/* Offset 0x0B: Cross-chip Port VLAN Register */
#घोषणा MV88E6XXX_G2_PVT_ADDR			0x0b
#घोषणा MV88E6XXX_G2_PVT_ADDR_BUSY		0x8000
#घोषणा MV88E6XXX_G2_PVT_ADDR_OP_MASK		0x7000
#घोषणा MV88E6XXX_G2_PVT_ADDR_OP_INIT_ONES	0x1000
#घोषणा MV88E6XXX_G2_PVT_ADDR_OP_WRITE_PVLAN	0x3000
#घोषणा MV88E6XXX_G2_PVT_ADDR_OP_READ		0x4000
#घोषणा MV88E6XXX_G2_PVT_ADDR_PTR_MASK		0x01ff
#घोषणा MV88E6XXX_G2_PVT_ADDR_DEV_TRUNK		0x1f

/* Offset 0x0C: Cross-chip Port VLAN Data Register */
#घोषणा MV88E6XXX_G2_PVT_DATA		0x0c
#घोषणा MV88E6XXX_G2_PVT_DATA_MASK	0x7f

/* Offset 0x0D: Switch MAC/WoL/WoF Register */
#घोषणा MV88E6XXX_G2_SWITCH_MAC			0x0d
#घोषणा MV88E6XXX_G2_SWITCH_MAC_UPDATE		0x8000
#घोषणा MV88E6XXX_G2_SWITCH_MAC_PTR_MASK	0x1f00
#घोषणा MV88E6XXX_G2_SWITCH_MAC_DATA_MASK	0x00ff

/* Offset 0x0E: ATU Stats Register */
#घोषणा MV88E6XXX_G2_ATU_STATS				0x0e
#घोषणा MV88E6XXX_G2_ATU_STATS_BIN_0			(0x0 << 14)
#घोषणा MV88E6XXX_G2_ATU_STATS_BIN_1			(0x1 << 14)
#घोषणा MV88E6XXX_G2_ATU_STATS_BIN_2			(0x2 << 14)
#घोषणा MV88E6XXX_G2_ATU_STATS_BIN_3			(0x3 << 14)
#घोषणा MV88E6XXX_G2_ATU_STATS_MODE_ALL			(0x0 << 12)
#घोषणा MV88E6XXX_G2_ATU_STATS_MODE_ALL_DYNAMIC		(0x1 << 12)
#घोषणा MV88E6XXX_G2_ATU_STATS_MODE_FID_ALL		(0x2 << 12)
#घोषणा MV88E6XXX_G2_ATU_STATS_MODE_FID_ALL_DYNAMIC	(0x3 << 12)
#घोषणा MV88E6XXX_G2_ATU_STATS_MASK			0x0fff

/* Offset 0x0F: Priority Override Table */
#घोषणा MV88E6XXX_G2_PRIO_OVERRIDE		0x0f
#घोषणा MV88E6XXX_G2_PRIO_OVERRIDE_UPDATE	0x8000
#घोषणा MV88E6XXX_G2_PRIO_OVERRIDE_FPRISET	0x1000
#घोषणा MV88E6XXX_G2_PRIO_OVERRIDE_PTR_MASK	0x0f00
#घोषणा MV88E6352_G2_PRIO_OVERRIDE_QPRIAVBEN	0x0080
#घोषणा MV88E6352_G2_PRIO_OVERRIDE_DATAAVB_MASK	0x0030
#घोषणा MV88E6XXX_G2_PRIO_OVERRIDE_QFPRIEN	0x0008
#घोषणा MV88E6XXX_G2_PRIO_OVERRIDE_DATA_MASK	0x0007

/* Offset 0x14: EEPROM Command */
#घोषणा MV88E6XXX_G2_EEPROM_CMD			0x14
#घोषणा MV88E6XXX_G2_EEPROM_CMD_BUSY		0x8000
#घोषणा MV88E6XXX_G2_EEPROM_CMD_OP_MASK		0x7000
#घोषणा MV88E6XXX_G2_EEPROM_CMD_OP_WRITE	0x3000
#घोषणा MV88E6XXX_G2_EEPROM_CMD_OP_READ		0x4000
#घोषणा MV88E6XXX_G2_EEPROM_CMD_OP_LOAD		0x6000
#घोषणा MV88E6XXX_G2_EEPROM_CMD_RUNNING		0x0800
#घोषणा MV88E6XXX_G2_EEPROM_CMD_WRITE_EN	0x0400
#घोषणा MV88E6352_G2_EEPROM_CMD_ADDR_MASK	0x00ff
#घोषणा MV88E6390_G2_EEPROM_CMD_DATA_MASK	0x00ff

/* Offset 0x15: EEPROM Data */
#घोषणा MV88E6352_G2_EEPROM_DATA	0x15
#घोषणा MV88E6352_G2_EEPROM_DATA_MASK	0xffff

/* Offset 0x15: EEPROM Addr */
#घोषणा MV88E6390_G2_EEPROM_ADDR	0x15
#घोषणा MV88E6390_G2_EEPROM_ADDR_MASK	0xffff

/* Offset 0x16: AVB Command Register */
#घोषणा MV88E6352_G2_AVB_CMD			0x16
#घोषणा MV88E6352_G2_AVB_CMD_BUSY		0x8000
#घोषणा MV88E6352_G2_AVB_CMD_OP_READ		0x4000
#घोषणा MV88E6352_G2_AVB_CMD_OP_READ_INCR	0x6000
#घोषणा MV88E6352_G2_AVB_CMD_OP_WRITE		0x3000
#घोषणा MV88E6390_G2_AVB_CMD_OP_READ		0x0000
#घोषणा MV88E6390_G2_AVB_CMD_OP_READ_INCR	0x4000
#घोषणा MV88E6390_G2_AVB_CMD_OP_WRITE		0x6000
#घोषणा MV88E6352_G2_AVB_CMD_PORT_MASK		0x0f00
#घोषणा MV88E6352_G2_AVB_CMD_PORT_TAIGLOBAL	0xe
#घोषणा MV88E6165_G2_AVB_CMD_PORT_PTPGLOBAL	0xf
#घोषणा MV88E6352_G2_AVB_CMD_PORT_PTPGLOBAL	0xf
#घोषणा MV88E6390_G2_AVB_CMD_PORT_MASK		0x1f00
#घोषणा MV88E6390_G2_AVB_CMD_PORT_TAIGLOBAL	0x1e
#घोषणा MV88E6390_G2_AVB_CMD_PORT_PTPGLOBAL	0x1f
#घोषणा MV88E6352_G2_AVB_CMD_BLOCK_PTP		0
#घोषणा MV88E6352_G2_AVB_CMD_BLOCK_AVB		1
#घोषणा MV88E6352_G2_AVB_CMD_BLOCK_QAV		2
#घोषणा MV88E6352_G2_AVB_CMD_BLOCK_QVB		3
#घोषणा MV88E6352_G2_AVB_CMD_BLOCK_MASK		0x00e0
#घोषणा MV88E6352_G2_AVB_CMD_ADDR_MASK		0x001f

/* Offset 0x17: AVB Data Register */
#घोषणा MV88E6352_G2_AVB_DATA		0x17

/* Offset 0x18: SMI PHY Command Register */
#घोषणा MV88E6XXX_G2_SMI_PHY_CMD			0x18
#घोषणा MV88E6XXX_G2_SMI_PHY_CMD_BUSY			0x8000
#घोषणा MV88E6390_G2_SMI_PHY_CMD_FUNC_MASK		0x6000
#घोषणा MV88E6390_G2_SMI_PHY_CMD_FUNC_INTERNAL		0x0000
#घोषणा MV88E6390_G2_SMI_PHY_CMD_FUNC_EXTERNAL		0x2000
#घोषणा MV88E6390_G2_SMI_PHY_CMD_FUNC_SETUP		0x4000
#घोषणा MV88E6XXX_G2_SMI_PHY_CMD_MODE_MASK		0x1000
#घोषणा MV88E6XXX_G2_SMI_PHY_CMD_MODE_45		0x0000
#घोषणा MV88E6XXX_G2_SMI_PHY_CMD_MODE_22		0x1000
#घोषणा MV88E6XXX_G2_SMI_PHY_CMD_OP_MASK		0x0c00
#घोषणा MV88E6XXX_G2_SMI_PHY_CMD_OP_22_WRITE_DATA	0x0400
#घोषणा MV88E6XXX_G2_SMI_PHY_CMD_OP_22_READ_DATA	0x0800
#घोषणा MV88E6XXX_G2_SMI_PHY_CMD_OP_45_WRITE_ADDR	0x0000
#घोषणा MV88E6XXX_G2_SMI_PHY_CMD_OP_45_WRITE_DATA	0x0400
#घोषणा MV88E6XXX_G2_SMI_PHY_CMD_OP_45_READ_DATA_INC	0x0800
#घोषणा MV88E6XXX_G2_SMI_PHY_CMD_OP_45_READ_DATA	0x0c00
#घोषणा MV88E6XXX_G2_SMI_PHY_CMD_DEV_ADDR_MASK		0x03e0
#घोषणा MV88E6XXX_G2_SMI_PHY_CMD_REG_ADDR_MASK		0x001f
#घोषणा MV88E6XXX_G2_SMI_PHY_CMD_SETUP_PTR_MASK		0x03ff

/* Offset 0x19: SMI PHY Data Register */
#घोषणा MV88E6XXX_G2_SMI_PHY_DATA	0x19

/* Offset 0x1A: Scratch and Misc. Register */
#घोषणा MV88E6XXX_G2_SCRATCH_MISC_MISC		0x1a
#घोषणा MV88E6XXX_G2_SCRATCH_MISC_UPDATE	0x8000
#घोषणा MV88E6XXX_G2_SCRATCH_MISC_PTR_MASK	0x7f00
#घोषणा MV88E6XXX_G2_SCRATCH_MISC_DATA_MASK	0x00ff

/* Offset 0x1B: Watch Dog Control Register */
#घोषणा MV88E6250_G2_WDOG_CTL			0x1b
#घोषणा MV88E6250_G2_WDOG_CTL_QC_HISTORY	0x0100
#घोषणा MV88E6250_G2_WDOG_CTL_QC_EVENT		0x0080
#घोषणा MV88E6250_G2_WDOG_CTL_QC_ENABLE		0x0040
#घोषणा MV88E6250_G2_WDOG_CTL_EGRESS_HISTORY	0x0020
#घोषणा MV88E6250_G2_WDOG_CTL_EGRESS_EVENT	0x0010
#घोषणा MV88E6250_G2_WDOG_CTL_EGRESS_ENABLE	0x0008
#घोषणा MV88E6250_G2_WDOG_CTL_FORCE_IRQ		0x0004
#घोषणा MV88E6250_G2_WDOG_CTL_HISTORY		0x0002
#घोषणा MV88E6250_G2_WDOG_CTL_SWRESET		0x0001

/* Offset 0x1B: Watch Dog Control Register */
#घोषणा MV88E6352_G2_WDOG_CTL			0x1b
#घोषणा MV88E6352_G2_WDOG_CTL_EGRESS_EVENT	0x0080
#घोषणा MV88E6352_G2_WDOG_CTL_RMU_TIMEOUT	0x0040
#घोषणा MV88E6352_G2_WDOG_CTL_QC_ENABLE		0x0020
#घोषणा MV88E6352_G2_WDOG_CTL_EGRESS_HISTORY	0x0010
#घोषणा MV88E6352_G2_WDOG_CTL_EGRESS_ENABLE	0x0008
#घोषणा MV88E6352_G2_WDOG_CTL_FORCE_IRQ		0x0004
#घोषणा MV88E6352_G2_WDOG_CTL_HISTORY		0x0002
#घोषणा MV88E6352_G2_WDOG_CTL_SWRESET		0x0001

/* Offset 0x1B: Watch Dog Control Register */
#घोषणा MV88E6390_G2_WDOG_CTL				0x1b
#घोषणा MV88E6390_G2_WDOG_CTL_UPDATE			0x8000
#घोषणा MV88E6390_G2_WDOG_CTL_PTR_MASK			0x7f00
#घोषणा MV88E6390_G2_WDOG_CTL_PTR_INT_SOURCE		0x0000
#घोषणा MV88E6390_G2_WDOG_CTL_PTR_INT_STS		0x1000
#घोषणा MV88E6390_G2_WDOG_CTL_PTR_INT_ENABLE		0x1100
#घोषणा MV88E6390_G2_WDOG_CTL_PTR_EVENT			0x1200
#घोषणा MV88E6390_G2_WDOG_CTL_PTR_HISTORY		0x1300
#घोषणा MV88E6390_G2_WDOG_CTL_DATA_MASK			0x00ff
#घोषणा MV88E6390_G2_WDOG_CTL_CUT_THROUGH		0x0008
#घोषणा MV88E6390_G2_WDOG_CTL_QUEUE_CONTROLLER		0x0004
#घोषणा MV88E6390_G2_WDOG_CTL_EGRESS			0x0002
#घोषणा MV88E6390_G2_WDOG_CTL_FORCE_IRQ			0x0001

/* Offset 0x1C: QoS Weights Register */
#घोषणा MV88E6XXX_G2_QOS_WEIGHTS		0x1c
#घोषणा MV88E6XXX_G2_QOS_WEIGHTS_UPDATE		0x8000
#घोषणा MV88E6352_G2_QOS_WEIGHTS_PTR_MASK	0x3f00
#घोषणा MV88E6390_G2_QOS_WEIGHTS_PTR_MASK	0x7f00
#घोषणा MV88E6XXX_G2_QOS_WEIGHTS_DATA_MASK	0x00ff

/* Offset 0x1D: Misc Register */
#घोषणा MV88E6XXX_G2_MISC		0x1d
#घोषणा MV88E6XXX_G2_MISC_5_BIT_PORT	0x4000
#घोषणा MV88E6352_G2_NOEGR_POLICY	0x2000
#घोषणा MV88E6390_G2_LAG_ID_4		0x2000

/* Scratch/Misc रेजिस्टरs accessed through MV88E6XXX_G2_SCRATCH_MISC */
/* Offset 0x02: Misc Configuration */
#घोषणा MV88E6352_G2_SCRATCH_MISC_CFG		0x02
#घोषणा MV88E6352_G2_SCRATCH_MISC_CFG_NORMALSMI	0x80
/* Offset 0x60-0x61: GPIO Configuration */
#घोषणा MV88E6352_G2_SCRATCH_GPIO_CFG0		0x60
#घोषणा MV88E6352_G2_SCRATCH_GPIO_CFG1		0x61
/* Offset 0x62-0x63: GPIO Direction */
#घोषणा MV88E6352_G2_SCRATCH_GPIO_सूची0		0x62
#घोषणा MV88E6352_G2_SCRATCH_GPIO_सूची1		0x63
#घोषणा MV88E6352_G2_SCRATCH_GPIO_सूची_OUT	0
#घोषणा MV88E6352_G2_SCRATCH_GPIO_सूची_IN	1
/* Offset 0x64-0x65: GPIO Data */
#घोषणा MV88E6352_G2_SCRATCH_GPIO_DATA0		0x64
#घोषणा MV88E6352_G2_SCRATCH_GPIO_DATA1		0x65
/* Offset 0x68-0x6F: GPIO Pin Control */
#घोषणा MV88E6352_G2_SCRATCH_GPIO_PCTL0		0x68
#घोषणा MV88E6352_G2_SCRATCH_GPIO_PCTL1		0x69
#घोषणा MV88E6352_G2_SCRATCH_GPIO_PCTL2		0x6A
#घोषणा MV88E6352_G2_SCRATCH_GPIO_PCTL3		0x6B
#घोषणा MV88E6352_G2_SCRATCH_GPIO_PCTL4		0x6C
#घोषणा MV88E6352_G2_SCRATCH_GPIO_PCTL5		0x6D
#घोषणा MV88E6352_G2_SCRATCH_GPIO_PCTL6		0x6E
#घोषणा MV88E6352_G2_SCRATCH_GPIO_PCTL7		0x6F
#घोषणा MV88E6352_G2_SCRATCH_CONFIG_DATA0	0x70
#घोषणा MV88E6352_G2_SCRATCH_CONFIG_DATA1	0x71
#घोषणा MV88E6352_G2_SCRATCH_CONFIG_DATA1_NO_CPU	BIT(2)
#घोषणा MV88E6352_G2_SCRATCH_CONFIG_DATA2	0x72
#घोषणा MV88E6352_G2_SCRATCH_CONFIG_DATA2_P0_MODE_MASK	0x3

#घोषणा MV88E6352_G2_SCRATCH_GPIO_PCTL_GPIO	0
#घोषणा MV88E6352_G2_SCRATCH_GPIO_PCTL_TRIG	1
#घोषणा MV88E6352_G2_SCRATCH_GPIO_PCTL_EVREQ	2

पूर्णांक mv88e6xxx_g2_पढ़ो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक reg, u16 *val);
पूर्णांक mv88e6xxx_g2_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक reg, u16 val);
पूर्णांक mv88e6xxx_g2_रुको_bit(काष्ठा mv88e6xxx_chip *chip, पूर्णांक reg,
			  पूर्णांक bit, पूर्णांक val);

पूर्णांक mv88e6352_g2_irl_init_all(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);
पूर्णांक mv88e6390_g2_irl_init_all(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);

पूर्णांक mv88e6xxx_g2_smi_phy_पढ़ो(काष्ठा mv88e6xxx_chip *chip,
			      काष्ठा mii_bus *bus,
			      पूर्णांक addr, पूर्णांक reg, u16 *val);
पूर्णांक mv88e6xxx_g2_smi_phy_ग_लिखो(काष्ठा mv88e6xxx_chip *chip,
			       काष्ठा mii_bus *bus,
			       पूर्णांक addr, पूर्णांक reg, u16 val);
पूर्णांक mv88e6xxx_g2_set_चयन_mac(काष्ठा mv88e6xxx_chip *chip, u8 *addr);

पूर्णांक mv88e6xxx_g2_get_eeprom8(काष्ठा mv88e6xxx_chip *chip,
			     काष्ठा ethtool_eeprom *eeprom, u8 *data);
पूर्णांक mv88e6xxx_g2_set_eeprom8(काष्ठा mv88e6xxx_chip *chip,
			     काष्ठा ethtool_eeprom *eeprom, u8 *data);

पूर्णांक mv88e6xxx_g2_get_eeprom16(काष्ठा mv88e6xxx_chip *chip,
			      काष्ठा ethtool_eeprom *eeprom, u8 *data);
पूर्णांक mv88e6xxx_g2_set_eeprom16(काष्ठा mv88e6xxx_chip *chip,
			      काष्ठा ethtool_eeprom *eeprom, u8 *data);

पूर्णांक mv88e6xxx_g2_pvt_पढ़ो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक src_dev,
			  पूर्णांक src_port, u16 *data);
पूर्णांक mv88e6xxx_g2_pvt_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक src_dev,
			   पूर्णांक src_port, u16 data);
पूर्णांक mv88e6xxx_g2_misc_4_bit_port(काष्ठा mv88e6xxx_chip *chip);

पूर्णांक mv88e6xxx_g2_irq_setup(काष्ठा mv88e6xxx_chip *chip);
व्योम mv88e6xxx_g2_irq_मुक्त(काष्ठा mv88e6xxx_chip *chip);

पूर्णांक mv88e6xxx_g2_irq_mdio_setup(काष्ठा mv88e6xxx_chip *chip,
				काष्ठा mii_bus *bus);
व्योम mv88e6xxx_g2_irq_mdio_मुक्त(काष्ठा mv88e6xxx_chip *chip,
				काष्ठा mii_bus *bus);

पूर्णांक mv88e6185_g2_mgmt_rsvd2cpu(काष्ठा mv88e6xxx_chip *chip);
पूर्णांक mv88e6352_g2_mgmt_rsvd2cpu(काष्ठा mv88e6xxx_chip *chip);

पूर्णांक mv88e6xxx_g2_pot_clear(काष्ठा mv88e6xxx_chip *chip);

पूर्णांक mv88e6xxx_g2_trunk_mask_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक num,
				  bool hash, u16 mask);
पूर्णांक mv88e6xxx_g2_trunk_mapping_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक id,
				     u16 map);
पूर्णांक mv88e6xxx_g2_trunk_clear(काष्ठा mv88e6xxx_chip *chip);

पूर्णांक mv88e6xxx_g2_device_mapping_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक target,
				      पूर्णांक port);

बाह्य स्थिर काष्ठा mv88e6xxx_irq_ops mv88e6097_watchकरोg_ops;
बाह्य स्थिर काष्ठा mv88e6xxx_irq_ops mv88e6250_watchकरोg_ops;
बाह्य स्थिर काष्ठा mv88e6xxx_irq_ops mv88e6390_watchकरोg_ops;

बाह्य स्थिर काष्ठा mv88e6xxx_avb_ops mv88e6165_avb_ops;
बाह्य स्थिर काष्ठा mv88e6xxx_avb_ops mv88e6352_avb_ops;
बाह्य स्थिर काष्ठा mv88e6xxx_avb_ops mv88e6390_avb_ops;

बाह्य स्थिर काष्ठा mv88e6xxx_gpio_ops mv88e6352_gpio_ops;

पूर्णांक mv88e6xxx_g2_scratch_gpio_set_smi(काष्ठा mv88e6xxx_chip *chip,
				      bool बाह्यal);
पूर्णांक mv88e6xxx_g2_atu_stats_set(काष्ठा mv88e6xxx_chip *chip, u16 kind, u16 bin);
पूर्णांक mv88e6xxx_g2_atu_stats_get(काष्ठा mv88e6xxx_chip *chip, u16 *stats);

#पूर्ण_अगर /* _MV88E6XXX_GLOBAL2_H */
