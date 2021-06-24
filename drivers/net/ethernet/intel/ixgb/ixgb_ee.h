<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 1999 - 2008 Intel Corporation. */

#अगर_अघोषित _IXGB_EE_H_
#घोषणा _IXGB_EE_H_

#घोषणा IXGB_EEPROM_SIZE    64	/* Size in words */

/* EEPROM Commands */
#घोषणा EEPROM_READ_OPCODE  0x6	/* EEPROM पढ़ो opcode */
#घोषणा EEPROM_WRITE_OPCODE 0x5	/* EEPROM ग_लिखो opcode */
#घोषणा EEPROM_ERASE_OPCODE 0x7	/* EEPROM erase opcode */
#घोषणा EEPROM_EWEN_OPCODE  0x13	/* EEPROM erase/ग_लिखो enable */
#घोषणा EEPROM_EWDS_OPCODE  0x10	/* EEPROM erase/ग_लिखो disable */

/* EEPROM MAP (Word Offsets) */
#घोषणा EEPROM_IA_1_2_REG        0x0000
#घोषणा EEPROM_IA_3_4_REG        0x0001
#घोषणा EEPROM_IA_5_6_REG        0x0002
#घोषणा EEPROM_COMPATIBILITY_REG 0x0003
#घोषणा EEPROM_PBA_1_2_REG       0x0008
#घोषणा EEPROM_PBA_3_4_REG       0x0009
#घोषणा EEPROM_INIT_CONTROL1_REG 0x000A
#घोषणा EEPROM_SUBSYS_ID_REG     0x000B
#घोषणा EEPROM_SUBVEND_ID_REG    0x000C
#घोषणा EEPROM_DEVICE_ID_REG     0x000D
#घोषणा EEPROM_VENDOR_ID_REG     0x000E
#घोषणा EEPROM_INIT_CONTROL2_REG 0x000F
#घोषणा EEPROM_SWDPINS_REG       0x0020
#घोषणा EEPROM_CIRCUIT_CTRL_REG  0x0021
#घोषणा EEPROM_D0_D3_POWER_REG   0x0022
#घोषणा EEPROM_FLASH_VERSION     0x0032
#घोषणा EEPROM_CHECKSUM_REG      0x003F

/* Mask bits क्रम fields in Word 0x0a of the EEPROM */

#घोषणा EEPROM_ICW1_SIGNATURE_MASK  0xC000
#घोषणा EEPROM_ICW1_SIGNATURE_VALID 0x4000
#घोषणा EEPROM_ICW1_SIGNATURE_CLEAR 0x0000

/* For checksumming, the sum of all words in the EEPROM should equal 0xBABA. */
#घोषणा EEPROM_SUM 0xBABA

/* EEPROM Map Sizes (Byte Counts) */
#घोषणा PBA_SIZE 4

/* EEPROM Map defines (WORD OFFSETS)*/

/* EEPROM काष्ठाure */
काष्ठा ixgb_ee_map_type अणु
	u8 mac_addr[ETH_ALEN];
	__le16 compatibility;
	__le16 reserved1[4];
	__le32 pba_number;
	__le16 init_ctrl_reg_1;
	__le16 subप्रणाली_id;
	__le16 subvenकरोr_id;
	__le16 device_id;
	__le16 venकरोr_id;
	__le16 init_ctrl_reg_2;
	__le16 oem_reserved[16];
	__le16 swdpins_reg;
	__le16 circuit_ctrl_reg;
	u8 d3_घातer;
	u8 d0_घातer;
	__le16 reserved2[28];
	__le16 checksum;
पूर्ण;

/* EEPROM Functions */
u16 ixgb_पढ़ो_eeprom(काष्ठा ixgb_hw *hw, u16 reg);

bool ixgb_validate_eeprom_checksum(काष्ठा ixgb_hw *hw);

व्योम ixgb_update_eeprom_checksum(काष्ठा ixgb_hw *hw);

व्योम ixgb_ग_लिखो_eeprom(काष्ठा ixgb_hw *hw, u16 reg, u16 data);

#पूर्ण_अगर				/* IXGB_EE_H */
