<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Marvell 88E6xxx Switch Global (1) Registers support
 *
 * Copyright (c) 2008 Marvell Semiconductor
 *
 * Copyright (c) 2016-2017 Savoir-faire Linux Inc.
 *	Vivien Didelot <vivien.didelot@savoirfairelinux.com>
 */

#अगर_अघोषित _MV88E6XXX_GLOBAL1_H
#घोषणा _MV88E6XXX_GLOBAL1_H

#समावेश "chip.h"

/* Offset 0x00: Switch Global Status Register */
#घोषणा MV88E6XXX_G1_STS				0x00
#घोषणा MV88E6352_G1_STS_PPU_STATE			0x8000
#घोषणा MV88E6185_G1_STS_PPU_STATE_MASK			0xc000
#घोषणा MV88E6185_G1_STS_PPU_STATE_DISABLED_RST		0x0000
#घोषणा MV88E6185_G1_STS_PPU_STATE_INITIALIZING		0x4000
#घोषणा MV88E6185_G1_STS_PPU_STATE_DISABLED		0x8000
#घोषणा MV88E6185_G1_STS_PPU_STATE_POLLING		0xc000
#घोषणा MV88E6XXX_G1_STS_INIT_READY			0x0800
#घोषणा MV88E6393X_G1_STS_IRQ_DEVICE_2			9
#घोषणा MV88E6XXX_G1_STS_IRQ_AVB			8
#घोषणा MV88E6XXX_G1_STS_IRQ_DEVICE			7
#घोषणा MV88E6XXX_G1_STS_IRQ_STATS			6
#घोषणा MV88E6XXX_G1_STS_IRQ_VTU_PROB			5
#घोषणा MV88E6XXX_G1_STS_IRQ_VTU_DONE			4
#घोषणा MV88E6XXX_G1_STS_IRQ_ATU_PROB			3
#घोषणा MV88E6XXX_G1_STS_IRQ_ATU_DONE			2
#घोषणा MV88E6XXX_G1_STS_IRQ_TCAM_DONE			1
#घोषणा MV88E6XXX_G1_STS_IRQ_EEPROM_DONE		0

/* Offset 0x01: Switch MAC Address Register Bytes 0 & 1
 * Offset 0x02: Switch MAC Address Register Bytes 2 & 3
 * Offset 0x03: Switch MAC Address Register Bytes 4 & 5
 */
#घोषणा MV88E6XXX_G1_MAC_01		0x01
#घोषणा MV88E6XXX_G1_MAC_23		0x02
#घोषणा MV88E6XXX_G1_MAC_45		0x03

/* Offset 0x01: ATU FID Register */
#घोषणा MV88E6352_G1_ATU_FID		0x01

/* Offset 0x02: VTU FID Register */
#घोषणा MV88E6352_G1_VTU_FID		0x02
#घोषणा MV88E6352_G1_VTU_FID_MASK	0x0fff

/* Offset 0x03: VTU SID Register */
#घोषणा MV88E6352_G1_VTU_SID		0x03
#घोषणा MV88E6352_G1_VTU_SID_MASK	0x3f

/* Offset 0x04: Switch Global Control Register */
#घोषणा MV88E6XXX_G1_CTL1			0x04
#घोषणा MV88E6XXX_G1_CTL1_SW_RESET		0x8000
#घोषणा MV88E6XXX_G1_CTL1_PPU_ENABLE		0x4000
#घोषणा MV88E6352_G1_CTL1_DISCARD_EXCESS	0x2000
#घोषणा MV88E6185_G1_CTL1_SCHED_PRIO		0x0800
#घोषणा MV88E6185_G1_CTL1_MAX_FRAME_1632	0x0400
#घोषणा MV88E6185_G1_CTL1_RELOAD_EEPROM		0x0200
#घोषणा MV88E6393X_G1_CTL1_DEVICE2_EN		0x0200
#घोषणा MV88E6XXX_G1_CTL1_DEVICE_EN		0x0080
#घोषणा MV88E6XXX_G1_CTL1_STATS_DONE_EN		0x0040
#घोषणा MV88E6XXX_G1_CTL1_VTU_PROBLEM_EN	0x0020
#घोषणा MV88E6XXX_G1_CTL1_VTU_DONE_EN		0x0010
#घोषणा MV88E6XXX_G1_CTL1_ATU_PROBLEM_EN	0x0008
#घोषणा MV88E6XXX_G1_CTL1_ATU_DONE_EN		0x0004
#घोषणा MV88E6XXX_G1_CTL1_TCAM_EN		0x0002
#घोषणा MV88E6XXX_G1_CTL1_EEPROM_DONE_EN	0x0001

/* Offset 0x05: VTU Operation Register */
#घोषणा MV88E6XXX_G1_VTU_OP			0x05
#घोषणा MV88E6XXX_G1_VTU_OP_BUSY		0x8000
#घोषणा MV88E6XXX_G1_VTU_OP_MASK		0x7000
#घोषणा MV88E6XXX_G1_VTU_OP_FLUSH_ALL		0x1000
#घोषणा MV88E6XXX_G1_VTU_OP_NOOP		0x2000
#घोषणा MV88E6XXX_G1_VTU_OP_VTU_LOAD_PURGE	0x3000
#घोषणा MV88E6XXX_G1_VTU_OP_VTU_GET_NEXT	0x4000
#घोषणा MV88E6XXX_G1_VTU_OP_STU_LOAD_PURGE	0x5000
#घोषणा MV88E6XXX_G1_VTU_OP_STU_GET_NEXT	0x6000
#घोषणा MV88E6XXX_G1_VTU_OP_GET_CLR_VIOLATION	0x7000
#घोषणा MV88E6XXX_G1_VTU_OP_MEMBER_VIOLATION	BIT(6)
#घोषणा MV88E6XXX_G1_VTU_OP_MISS_VIOLATION	BIT(5)
#घोषणा MV88E6XXX_G1_VTU_OP_SPID_MASK		0xf

/* Offset 0x06: VTU VID Register */
#घोषणा MV88E6XXX_G1_VTU_VID		0x06
#घोषणा MV88E6XXX_G1_VTU_VID_MASK	0x0fff
#घोषणा MV88E6390_G1_VTU_VID_PAGE	0x2000
#घोषणा MV88E6XXX_G1_VTU_VID_VALID	0x1000

/* Offset 0x07: VTU/STU Data Register 1
 * Offset 0x08: VTU/STU Data Register 2
 * Offset 0x09: VTU/STU Data Register 3
 */
#घोषणा MV88E6XXX_G1_VTU_DATA1				0x07
#घोषणा MV88E6XXX_G1_VTU_DATA2				0x08
#घोषणा MV88E6XXX_G1_VTU_DATA3				0x09
#घोषणा MV88E6XXX_G1_VTU_STU_DATA_MASK			0x0003
#घोषणा MV88E6XXX_G1_VTU_DATA_MEMBER_TAG_UNMODIFIED	0x0000
#घोषणा MV88E6XXX_G1_VTU_DATA_MEMBER_TAG_UNTAGGED	0x0001
#घोषणा MV88E6XXX_G1_VTU_DATA_MEMBER_TAG_TAGGED		0x0002
#घोषणा MV88E6XXX_G1_VTU_DATA_MEMBER_TAG_NON_MEMBER	0x0003
#घोषणा MV88E6XXX_G1_STU_DATA_PORT_STATE_DISABLED	0x0000
#घोषणा MV88E6XXX_G1_STU_DATA_PORT_STATE_BLOCKING	0x0001
#घोषणा MV88E6XXX_G1_STU_DATA_PORT_STATE_LEARNING	0x0002
#घोषणा MV88E6XXX_G1_STU_DATA_PORT_STATE_FORWARDING	0x0003

/* Offset 0x0A: ATU Control Register */
#घोषणा MV88E6XXX_G1_ATU_CTL		0x0a
#घोषणा MV88E6XXX_G1_ATU_CTL_LEARN2ALL	0x0008
#घोषणा MV88E6161_G1_ATU_CTL_HASH_MASK	0x0003

/* Offset 0x0B: ATU Operation Register */
#घोषणा MV88E6XXX_G1_ATU_OP				0x0b
#घोषणा MV88E6XXX_G1_ATU_OP_BUSY			0x8000
#घोषणा MV88E6XXX_G1_ATU_OP_MASK			0x7000
#घोषणा MV88E6XXX_G1_ATU_OP_NOOP			0x0000
#घोषणा MV88E6XXX_G1_ATU_OP_FLUSH_MOVE_ALL		0x1000
#घोषणा MV88E6XXX_G1_ATU_OP_FLUSH_MOVE_NON_STATIC	0x2000
#घोषणा MV88E6XXX_G1_ATU_OP_LOAD_DB			0x3000
#घोषणा MV88E6XXX_G1_ATU_OP_GET_NEXT_DB			0x4000
#घोषणा MV88E6XXX_G1_ATU_OP_FLUSH_MOVE_ALL_DB		0x5000
#घोषणा MV88E6XXX_G1_ATU_OP_FLUSH_MOVE_NON_STATIC_DB	0x6000
#घोषणा MV88E6XXX_G1_ATU_OP_GET_CLR_VIOLATION		0x7000
#घोषणा MV88E6XXX_G1_ATU_OP_AGE_OUT_VIOLATION		BIT(7)
#घोषणा MV88E6XXX_G1_ATU_OP_MEMBER_VIOLATION		BIT(6)
#घोषणा MV88E6XXX_G1_ATU_OP_MISS_VIOLATION		BIT(5)
#घोषणा MV88E6XXX_G1_ATU_OP_FULL_VIOLATION		BIT(4)

/* Offset 0x0C: ATU Data Register */
#घोषणा MV88E6XXX_G1_ATU_DATA					0x0c
#घोषणा MV88E6XXX_G1_ATU_DATA_TRUNK				0x8000
#घोषणा MV88E6XXX_G1_ATU_DATA_TRUNK_ID_MASK			0x00f0
#घोषणा MV88E6XXX_G1_ATU_DATA_PORT_VECTOR_MASK			0x3ff0
#घोषणा MV88E6XXX_G1_ATU_DATA_STATE_MASK			0x000f
#घोषणा MV88E6XXX_G1_ATU_DATA_STATE_UC_UNUSED			0x0000
#घोषणा MV88E6XXX_G1_ATU_DATA_STATE_UC_AGE_1_OLDEST		0x0001
#घोषणा MV88E6XXX_G1_ATU_DATA_STATE_UC_AGE_2			0x0002
#घोषणा MV88E6XXX_G1_ATU_DATA_STATE_UC_AGE_3			0x0003
#घोषणा MV88E6XXX_G1_ATU_DATA_STATE_UC_AGE_4			0x0004
#घोषणा MV88E6XXX_G1_ATU_DATA_STATE_UC_AGE_5			0x0005
#घोषणा MV88E6XXX_G1_ATU_DATA_STATE_UC_AGE_6			0x0006
#घोषणा MV88E6XXX_G1_ATU_DATA_STATE_UC_AGE_7_NEWEST		0x0007
#घोषणा MV88E6XXX_G1_ATU_DATA_STATE_UC_STATIC_POLICY		0x0008
#घोषणा MV88E6XXX_G1_ATU_DATA_STATE_UC_STATIC_POLICY_PO		0x0009
#घोषणा MV88E6XXX_G1_ATU_DATA_STATE_UC_STATIC_AVB_NRL		0x000a
#घोषणा MV88E6XXX_G1_ATU_DATA_STATE_UC_STATIC_AVB_NRL_PO	0x000b
#घोषणा MV88E6XXX_G1_ATU_DATA_STATE_UC_STATIC_DA_MGMT		0x000c
#घोषणा MV88E6XXX_G1_ATU_DATA_STATE_UC_STATIC_DA_MGMT_PO	0x000d
#घोषणा MV88E6XXX_G1_ATU_DATA_STATE_UC_STATIC			0x000e
#घोषणा MV88E6XXX_G1_ATU_DATA_STATE_UC_STATIC_PO		0x000f
#घोषणा MV88E6XXX_G1_ATU_DATA_STATE_MC_UNUSED			0x0000
#घोषणा MV88E6XXX_G1_ATU_DATA_STATE_MC_STATIC_POLICY		0x0004
#घोषणा MV88E6XXX_G1_ATU_DATA_STATE_MC_STATIC_AVB_NRL		0x0005
#घोषणा MV88E6XXX_G1_ATU_DATA_STATE_MC_STATIC_DA_MGMT		0x0006
#घोषणा MV88E6XXX_G1_ATU_DATA_STATE_MC_STATIC			0x0007
#घोषणा MV88E6XXX_G1_ATU_DATA_STATE_MC_STATIC_POLICY_PO		0x000c
#घोषणा MV88E6XXX_G1_ATU_DATA_STATE_MC_STATIC_AVB_NRL_PO	0x000d
#घोषणा MV88E6XXX_G1_ATU_DATA_STATE_MC_STATIC_DA_MGMT_PO	0x000e
#घोषणा MV88E6XXX_G1_ATU_DATA_STATE_MC_STATIC_PO		0x000f

/* Offset 0x0D: ATU MAC Address Register Bytes 0 & 1
 * Offset 0x0E: ATU MAC Address Register Bytes 2 & 3
 * Offset 0x0F: ATU MAC Address Register Bytes 4 & 5
 */
#घोषणा MV88E6XXX_G1_ATU_MAC01		0x0d
#घोषणा MV88E6XXX_G1_ATU_MAC23		0x0e
#घोषणा MV88E6XXX_G1_ATU_MAC45		0x0f

/* Offset 0x10: IP-PRI Mapping Register 0
 * Offset 0x11: IP-PRI Mapping Register 1
 * Offset 0x12: IP-PRI Mapping Register 2
 * Offset 0x13: IP-PRI Mapping Register 3
 * Offset 0x14: IP-PRI Mapping Register 4
 * Offset 0x15: IP-PRI Mapping Register 5
 * Offset 0x16: IP-PRI Mapping Register 6
 * Offset 0x17: IP-PRI Mapping Register 7
 */
#घोषणा MV88E6XXX_G1_IP_PRI_0	0x10
#घोषणा MV88E6XXX_G1_IP_PRI_1	0x11
#घोषणा MV88E6XXX_G1_IP_PRI_2	0x12
#घोषणा MV88E6XXX_G1_IP_PRI_3	0x13
#घोषणा MV88E6XXX_G1_IP_PRI_4	0x14
#घोषणा MV88E6XXX_G1_IP_PRI_5	0x15
#घोषणा MV88E6XXX_G1_IP_PRI_6	0x16
#घोषणा MV88E6XXX_G1_IP_PRI_7	0x17

/* Offset 0x18: IEEE-PRI Register */
#घोषणा MV88E6XXX_G1_IEEE_PRI	0x18

/* Offset 0x19: Core Tag Type */
#घोषणा MV88E6185_G1_CORE_TAG_TYPE	0x19

/* Offset 0x1A: Monitor Control */
#घोषणा MV88E6185_G1_MONITOR_CTL			0x1a
#घोषणा MV88E6185_G1_MONITOR_CTL_INGRESS_DEST_MASK	0xf000
#घोषणा MV88E6185_G1_MONITOR_CTL_EGRESS_DEST_MASK	0x0f00
#घोषणा MV88E6185_G1_MONITOR_CTL_ARP_DEST_MASK	        0x00f0
#घोषणा MV88E6352_G1_MONITOR_CTL_CPU_DEST_MASK	        0x00f0
#घोषणा MV88E6352_G1_MONITOR_CTL_MIRROR_DEST_MASK	0x000f

/* Offset 0x1A: Monitor & MGMT Control Register */
#घोषणा MV88E6390_G1_MONITOR_MGMT_CTL				0x1a
#घोषणा MV88E6390_G1_MONITOR_MGMT_CTL_UPDATE			0x8000
#घोषणा MV88E6390_G1_MONITOR_MGMT_CTL_PTR_MASK			0x3f00
#घोषणा MV88E6390_G1_MONITOR_MGMT_CTL_PTR_0180C200000XLO	0x0000
#घोषणा MV88E6390_G1_MONITOR_MGMT_CTL_PTR_0180C200000XHI	0x0100
#घोषणा MV88E6390_G1_MONITOR_MGMT_CTL_PTR_0180C200002XLO	0x0200
#घोषणा MV88E6390_G1_MONITOR_MGMT_CTL_PTR_0180C200002XHI	0x0300
#घोषणा MV88E6390_G1_MONITOR_MGMT_CTL_PTR_INGRESS_DEST		0x2000
#घोषणा MV88E6390_G1_MONITOR_MGMT_CTL_PTR_EGRESS_DEST		0x2100
#घोषणा MV88E6390_G1_MONITOR_MGMT_CTL_PTR_CPU_DEST		0x3000
#घोषणा MV88E6390_G1_MONITOR_MGMT_CTL_PTR_CPU_DEST_MGMTPRI	0x00e0
#घोषणा MV88E6390_G1_MONITOR_MGMT_CTL_DATA_MASK			0x00ff

/* Offset 0x1C: Global Control 2 */
#घोषणा MV88E6XXX_G1_CTL2			0x1c
#घोषणा MV88E6185_G1_CTL2_CASCADE_PORT_MASK	0xf000
#घोषणा MV88E6185_G1_CTL2_CASCADE_PORT_NONE	0xe000
#घोषणा MV88E6185_G1_CTL2_CASCADE_PORT_MULTI	0xf000
#घोषणा MV88E6352_G1_CTL2_HEADER_TYPE_MASK	0xc000
#घोषणा MV88E6352_G1_CTL2_HEADER_TYPE_ORIG	0x0000
#घोषणा MV88E6352_G1_CTL2_HEADER_TYPE_MGMT	0x4000
#घोषणा MV88E6390_G1_CTL2_HEADER_TYPE_LAG	0x8000
#घोषणा MV88E6352_G1_CTL2_RMU_MODE_MASK		0x3000
#घोषणा MV88E6352_G1_CTL2_RMU_MODE_DISABLED	0x0000
#घोषणा MV88E6352_G1_CTL2_RMU_MODE_PORT_4	0x1000
#घोषणा MV88E6352_G1_CTL2_RMU_MODE_PORT_5	0x2000
#घोषणा MV88E6352_G1_CTL2_RMU_MODE_PORT_6	0x3000
#घोषणा MV88E6085_G1_CTL2_DA_CHECK		0x4000
#घोषणा MV88E6085_G1_CTL2_P10RM			0x2000
#घोषणा MV88E6085_G1_CTL2_RM_ENABLE		0x1000
#घोषणा MV88E6352_G1_CTL2_DA_CHECK		0x0800
#घोषणा MV88E6390_G1_CTL2_RMU_MODE_MASK		0x0700
#घोषणा MV88E6390_G1_CTL2_RMU_MODE_PORT_0	0x0000
#घोषणा MV88E6390_G1_CTL2_RMU_MODE_PORT_1	0x0100
#घोषणा MV88E6390_G1_CTL2_RMU_MODE_PORT_9	0x0200
#घोषणा MV88E6390_G1_CTL2_RMU_MODE_PORT_10	0x0300
#घोषणा MV88E6390_G1_CTL2_RMU_MODE_ALL_DSA	0x0600
#घोषणा MV88E6390_G1_CTL2_RMU_MODE_DISABLED	0x0700
#घोषणा MV88E6390_G1_CTL2_HIST_MODE_MASK	0x00c0
#घोषणा MV88E6390_G1_CTL2_HIST_MODE_RX		0x0040
#घोषणा MV88E6390_G1_CTL2_HIST_MODE_TX		0x0080
#घोषणा MV88E6352_G1_CTL2_CTR_MODE_MASK		0x0060
#घोषणा MV88E6390_G1_CTL2_CTR_MODE		0x0020
#घोषणा MV88E6XXX_G1_CTL2_DEVICE_NUMBER_MASK	0x001f

/* Offset 0x1D: Stats Operation Register */
#घोषणा MV88E6XXX_G1_STATS_OP			0x1d
#घोषणा MV88E6XXX_G1_STATS_OP_BUSY		0x8000
#घोषणा MV88E6XXX_G1_STATS_OP_NOP		0x0000
#घोषणा MV88E6XXX_G1_STATS_OP_FLUSH_ALL		0x1000
#घोषणा MV88E6XXX_G1_STATS_OP_FLUSH_PORT	0x2000
#घोषणा MV88E6XXX_G1_STATS_OP_READ_CAPTURED	0x4000
#घोषणा MV88E6XXX_G1_STATS_OP_CAPTURE_PORT	0x5000
#घोषणा MV88E6XXX_G1_STATS_OP_HIST_RX		0x0400
#घोषणा MV88E6XXX_G1_STATS_OP_HIST_TX		0x0800
#घोषणा MV88E6XXX_G1_STATS_OP_HIST_RX_TX	0x0c00
#घोषणा MV88E6XXX_G1_STATS_OP_BANK_1_BIT_9	0x0200
#घोषणा MV88E6XXX_G1_STATS_OP_BANK_1_BIT_10	0x0400

/* Offset 0x1E: Stats Counter Register Bytes 3 & 2
 * Offset 0x1F: Stats Counter Register Bytes 1 & 0
 */
#घोषणा MV88E6XXX_G1_STATS_COUNTER_32	0x1e
#घोषणा MV88E6XXX_G1_STATS_COUNTER_01	0x1f

पूर्णांक mv88e6xxx_g1_पढ़ो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक reg, u16 *val);
पूर्णांक mv88e6xxx_g1_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक reg, u16 val);
पूर्णांक mv88e6xxx_g1_रुको_bit(काष्ठा mv88e6xxx_chip *chip, पूर्णांक reg, पूर्णांक
			  bit, पूर्णांक val);
पूर्णांक mv88e6xxx_g1_रुको_mask(काष्ठा mv88e6xxx_chip *chip, पूर्णांक reg,
			   u16 mask, u16 val);

पूर्णांक mv88e6xxx_g1_set_चयन_mac(काष्ठा mv88e6xxx_chip *chip, u8 *addr);

पूर्णांक mv88e6185_g1_reset(काष्ठा mv88e6xxx_chip *chip);
पूर्णांक mv88e6352_g1_reset(काष्ठा mv88e6xxx_chip *chip);
पूर्णांक mv88e6250_g1_reset(काष्ठा mv88e6xxx_chip *chip);
व्योम mv88e6xxx_g1_रुको_eeprom_करोne(काष्ठा mv88e6xxx_chip *chip);

पूर्णांक mv88e6185_g1_ppu_enable(काष्ठा mv88e6xxx_chip *chip);
पूर्णांक mv88e6185_g1_ppu_disable(काष्ठा mv88e6xxx_chip *chip);

पूर्णांक mv88e6185_g1_set_max_frame_size(काष्ठा mv88e6xxx_chip *chip, पूर्णांक mtu);

पूर्णांक mv88e6xxx_g1_stats_snapshot(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);
पूर्णांक mv88e6320_g1_stats_snapshot(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);
पूर्णांक mv88e6390_g1_stats_snapshot(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);
पूर्णांक mv88e6095_g1_stats_set_histogram(काष्ठा mv88e6xxx_chip *chip);
पूर्णांक mv88e6390_g1_stats_set_histogram(काष्ठा mv88e6xxx_chip *chip);
व्योम mv88e6xxx_g1_stats_पढ़ो(काष्ठा mv88e6xxx_chip *chip, पूर्णांक stat, u32 *val);
पूर्णांक mv88e6xxx_g1_stats_clear(काष्ठा mv88e6xxx_chip *chip);
पूर्णांक mv88e6095_g1_set_egress_port(काष्ठा mv88e6xxx_chip *chip,
				 क्रमागत mv88e6xxx_egress_direction direction,
				 पूर्णांक port);
पूर्णांक mv88e6390_g1_set_egress_port(काष्ठा mv88e6xxx_chip *chip,
				 क्रमागत mv88e6xxx_egress_direction direction,
				 पूर्णांक port);
पूर्णांक mv88e6095_g1_set_cpu_port(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);
पूर्णांक mv88e6390_g1_set_cpu_port(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);
पूर्णांक mv88e6390_g1_mgmt_rsvd2cpu(काष्ठा mv88e6xxx_chip *chip);

पूर्णांक mv88e6085_g1_ip_pri_map(काष्ठा mv88e6xxx_chip *chip);

पूर्णांक mv88e6085_g1_ieee_pri_map(काष्ठा mv88e6xxx_chip *chip);
पूर्णांक mv88e6250_g1_ieee_pri_map(काष्ठा mv88e6xxx_chip *chip);

पूर्णांक mv88e6185_g1_set_cascade_port(काष्ठा mv88e6xxx_chip *chip, पूर्णांक port);

पूर्णांक mv88e6085_g1_rmu_disable(काष्ठा mv88e6xxx_chip *chip);
पूर्णांक mv88e6352_g1_rmu_disable(काष्ठा mv88e6xxx_chip *chip);
पूर्णांक mv88e6390_g1_rmu_disable(काष्ठा mv88e6xxx_chip *chip);

पूर्णांक mv88e6xxx_g1_set_device_number(काष्ठा mv88e6xxx_chip *chip, पूर्णांक index);

पूर्णांक mv88e6xxx_g1_atu_set_learn2all(काष्ठा mv88e6xxx_chip *chip, bool learn2all);
पूर्णांक mv88e6xxx_g1_atu_set_age_समय(काष्ठा mv88e6xxx_chip *chip,
				  अचिन्हित पूर्णांक msecs);
पूर्णांक mv88e6xxx_g1_atu_getnext(काष्ठा mv88e6xxx_chip *chip, u16 fid,
			     काष्ठा mv88e6xxx_atu_entry *entry);
पूर्णांक mv88e6xxx_g1_atu_loadpurge(काष्ठा mv88e6xxx_chip *chip, u16 fid,
			       काष्ठा mv88e6xxx_atu_entry *entry);
पूर्णांक mv88e6xxx_g1_atu_flush(काष्ठा mv88e6xxx_chip *chip, u16 fid, bool all);
पूर्णांक mv88e6xxx_g1_atu_हटाओ(काष्ठा mv88e6xxx_chip *chip, u16 fid, पूर्णांक port,
			    bool all);
पूर्णांक mv88e6xxx_g1_atu_prob_irq_setup(काष्ठा mv88e6xxx_chip *chip);
व्योम mv88e6xxx_g1_atu_prob_irq_मुक्त(काष्ठा mv88e6xxx_chip *chip);
पूर्णांक mv88e6165_g1_atu_get_hash(काष्ठा mv88e6xxx_chip *chip, u8 *hash);
पूर्णांक mv88e6165_g1_atu_set_hash(काष्ठा mv88e6xxx_chip *chip, u8 hash);

पूर्णांक mv88e6xxx_g1_vtu_getnext(काष्ठा mv88e6xxx_chip *chip,
			     काष्ठा mv88e6xxx_vtu_entry *entry);
पूर्णांक mv88e6185_g1_vtu_getnext(काष्ठा mv88e6xxx_chip *chip,
			     काष्ठा mv88e6xxx_vtu_entry *entry);
पूर्णांक mv88e6185_g1_vtu_loadpurge(काष्ठा mv88e6xxx_chip *chip,
			       काष्ठा mv88e6xxx_vtu_entry *entry);
पूर्णांक mv88e6352_g1_vtu_getnext(काष्ठा mv88e6xxx_chip *chip,
			     काष्ठा mv88e6xxx_vtu_entry *entry);
पूर्णांक mv88e6352_g1_vtu_loadpurge(काष्ठा mv88e6xxx_chip *chip,
			       काष्ठा mv88e6xxx_vtu_entry *entry);
पूर्णांक mv88e6390_g1_vtu_getnext(काष्ठा mv88e6xxx_chip *chip,
			     काष्ठा mv88e6xxx_vtu_entry *entry);
पूर्णांक mv88e6390_g1_vtu_loadpurge(काष्ठा mv88e6xxx_chip *chip,
			       काष्ठा mv88e6xxx_vtu_entry *entry);
पूर्णांक mv88e6xxx_g1_vtu_flush(काष्ठा mv88e6xxx_chip *chip);
पूर्णांक mv88e6xxx_g1_vtu_prob_irq_setup(काष्ठा mv88e6xxx_chip *chip);
व्योम mv88e6xxx_g1_vtu_prob_irq_मुक्त(काष्ठा mv88e6xxx_chip *chip);
पूर्णांक mv88e6xxx_g1_atu_get_next(काष्ठा mv88e6xxx_chip *chip, u16 fid);

#पूर्ण_अगर /* _MV88E6XXX_GLOBAL1_H */
