<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#अगर_अघोषित _IXGBE_PHY_H_
#घोषणा _IXGBE_PHY_H_

#समावेश "ixgbe_type.h"
#घोषणा IXGBE_I2C_EEPROM_DEV_ADDR    0xA0
#घोषणा IXGBE_I2C_EEPROM_DEV_ADDR2   0xA2

/* EEPROM byte offsets */
#घोषणा IXGBE_SFF_IDENTIFIER		0x0
#घोषणा IXGBE_SFF_IDENTIFIER_SFP	0x3
#घोषणा IXGBE_SFF_VENDOR_OUI_BYTE0	0x25
#घोषणा IXGBE_SFF_VENDOR_OUI_BYTE1	0x26
#घोषणा IXGBE_SFF_VENDOR_OUI_BYTE2	0x27
#घोषणा IXGBE_SFF_1GBE_COMP_CODES	0x6
#घोषणा IXGBE_SFF_10GBE_COMP_CODES	0x3
#घोषणा IXGBE_SFF_CABLE_TECHNOLOGY	0x8
#घोषणा IXGBE_SFF_CABLE_SPEC_COMP	0x3C
#घोषणा IXGBE_SFF_SFF_8472_SWAP		0x5C
#घोषणा IXGBE_SFF_SFF_8472_COMP		0x5E
#घोषणा IXGBE_SFF_SFF_8472_OSCB		0x6E
#घोषणा IXGBE_SFF_SFF_8472_ESCB		0x76
#घोषणा IXGBE_SFF_IDENTIFIER_QSFP_PLUS	0xD
#घोषणा IXGBE_SFF_QSFP_VENDOR_OUI_BYTE0	0xA5
#घोषणा IXGBE_SFF_QSFP_VENDOR_OUI_BYTE1	0xA6
#घोषणा IXGBE_SFF_QSFP_VENDOR_OUI_BYTE2	0xA7
#घोषणा IXGBE_SFF_QSFP_CONNECTOR	0x82
#घोषणा IXGBE_SFF_QSFP_10GBE_COMP	0x83
#घोषणा IXGBE_SFF_QSFP_1GBE_COMP	0x86
#घोषणा IXGBE_SFF_QSFP_CABLE_LENGTH	0x92
#घोषणा IXGBE_SFF_QSFP_DEVICE_TECH	0x93

/* Biपंचांगasks */
#घोषणा IXGBE_SFF_DA_PASSIVE_CABLE		0x4
#घोषणा IXGBE_SFF_DA_ACTIVE_CABLE		0x8
#घोषणा IXGBE_SFF_DA_SPEC_ACTIVE_LIMITING	0x4
#घोषणा IXGBE_SFF_1GBASESX_CAPABLE		0x1
#घोषणा IXGBE_SFF_1GBASELX_CAPABLE		0x2
#घोषणा IXGBE_SFF_1GBASET_CAPABLE		0x8
#घोषणा IXGBE_SFF_10GBASESR_CAPABLE		0x10
#घोषणा IXGBE_SFF_10GBASELR_CAPABLE		0x20
#घोषणा IXGBE_SFF_SOFT_RS_SELECT_MASK		0x8
#घोषणा IXGBE_SFF_SOFT_RS_SELECT_10G		0x8
#घोषणा IXGBE_SFF_SOFT_RS_SELECT_1G		0x0
#घोषणा IXGBE_SFF_ADDRESSING_MODE		0x4
#घोषणा IXGBE_SFF_DDM_IMPLEMENTED		0x40
#घोषणा IXGBE_SFF_QSFP_DA_ACTIVE_CABLE		0x1
#घोषणा IXGBE_SFF_QSFP_DA_PASSIVE_CABLE		0x8
#घोषणा IXGBE_SFF_QSFP_CONNECTOR_NOT_SEPARABLE	0x23
#घोषणा IXGBE_SFF_QSFP_TRANSMITER_850NM_VCSEL	0x0
#घोषणा IXGBE_I2C_EEPROM_READ_MASK		0x100
#घोषणा IXGBE_I2C_EEPROM_STATUS_MASK		0x3
#घोषणा IXGBE_I2C_EEPROM_STATUS_NO_OPERATION	0x0
#घोषणा IXGBE_I2C_EEPROM_STATUS_PASS		0x1
#घोषणा IXGBE_I2C_EEPROM_STATUS_FAIL		0x2
#घोषणा IXGBE_I2C_EEPROM_STATUS_IN_PROGRESS	0x3
#घोषणा IXGBE_CS4227				0xBE    /* CS4227 address */
#घोषणा IXGBE_CS4227_GLOBAL_ID_LSB		0
#घोषणा IXGBE_CS4227_GLOBAL_ID_MSB		1
#घोषणा IXGBE_CS4227_SCRATCH			2
#घोषणा IXGBE_CS4227_EFUSE_PDF_SKU		0x19F
#घोषणा IXGBE_CS4223_SKU_ID			0x0010  /* Quad port */
#घोषणा IXGBE_CS4227_SKU_ID			0x0014  /* Dual port */
#घोषणा IXGBE_CS4227_RESET_PENDING		0x1357
#घोषणा IXGBE_CS4227_RESET_COMPLETE		0x5AA5
#घोषणा IXGBE_CS4227_RETRIES			15
#घोषणा IXGBE_CS4227_EFUSE_STATUS		0x0181
#घोषणा IXGBE_CS4227_LINE_SPARE22_MSB		0x12AD	/* Reg to set speed */
#घोषणा IXGBE_CS4227_LINE_SPARE24_LSB		0x12B0	/* Reg to set EDC */
#घोषणा IXGBE_CS4227_HOST_SPARE22_MSB		0x1AAD	/* Reg to set speed */
#घोषणा IXGBE_CS4227_HOST_SPARE24_LSB		0x1AB0	/* Reg to program EDC */
#घोषणा IXGBE_CS4227_EEPROM_STATUS		0x5001
#घोषणा IXGBE_CS4227_EEPROM_LOAD_OK		0x0001
#घोषणा IXGBE_CS4227_SPEED_1G			0x8000
#घोषणा IXGBE_CS4227_SPEED_10G			0
#घोषणा IXGBE_CS4227_EDC_MODE_CX1		0x0002
#घोषणा IXGBE_CS4227_EDC_MODE_SR		0x0004
#घोषणा IXGBE_CS4227_EDC_MODE_DIAG		0x0008
#घोषणा IXGBE_CS4227_RESET_HOLD			500	/* microseconds */
#घोषणा IXGBE_CS4227_RESET_DELAY		500	/* milliseconds */
#घोषणा IXGBE_CS4227_CHECK_DELAY		30	/* milliseconds */
#घोषणा IXGBE_PE				0xE0	/* Port expander addr */
#घोषणा IXGBE_PE_OUTPUT				1	/* Output reg offset */
#घोषणा IXGBE_PE_CONFIG				3	/* Config reg offset */
#घोषणा IXGBE_PE_BIT1				BIT(1)

/* Flow control defines */
#घोषणा IXGBE_TAF_SYM_PAUSE                  0x400
#घोषणा IXGBE_TAF_ASM_PAUSE                  0x800

/* Bit-shअगरt macros */
#घोषणा IXGBE_SFF_VENDOR_OUI_BYTE0_SHIFT    24
#घोषणा IXGBE_SFF_VENDOR_OUI_BYTE1_SHIFT    16
#घोषणा IXGBE_SFF_VENDOR_OUI_BYTE2_SHIFT    8

/* Venकरोr OUIs: क्रमmat of OUI is 0x[byte0][byte1][byte2][00] */
#घोषणा IXGBE_SFF_VENDOR_OUI_TYCO     0x00407600
#घोषणा IXGBE_SFF_VENDOR_OUI_FTL      0x00906500
#घोषणा IXGBE_SFF_VENDOR_OUI_AVAGO    0x00176A00
#घोषणा IXGBE_SFF_VENDOR_OUI_INTEL    0x001B2100

/* I2C SDA and SCL timing parameters क्रम standard mode */
#घोषणा IXGBE_I2C_T_HD_STA  4
#घोषणा IXGBE_I2C_T_LOW     5
#घोषणा IXGBE_I2C_T_HIGH    4
#घोषणा IXGBE_I2C_T_SU_STA  5
#घोषणा IXGBE_I2C_T_HD_DATA 5
#घोषणा IXGBE_I2C_T_SU_DATA 1
#घोषणा IXGBE_I2C_T_RISE    1
#घोषणा IXGBE_I2C_T_FALL    1
#घोषणा IXGBE_I2C_T_SU_STO  4
#घोषणा IXGBE_I2C_T_BUF     5

#घोषणा IXGBE_SFP_DETECT_RETRIES	2

#घोषणा IXGBE_TN_LASI_STATUS_REG        0x9005
#घोषणा IXGBE_TN_LASI_STATUS_TEMP_ALARM 0x0008

/* SFP+ SFF-8472 Compliance code */
#घोषणा IXGBE_SFF_SFF_8472_UNSUP      0x00

s32 ixgbe_mii_bus_init(काष्ठा ixgbe_hw *hw);

s32 ixgbe_identअगरy_phy_generic(काष्ठा ixgbe_hw *hw);
s32 ixgbe_reset_phy_generic(काष्ठा ixgbe_hw *hw);
s32 ixgbe_पढ़ो_phy_reg_generic(काष्ठा ixgbe_hw *hw, u32 reg_addr,
			       u32 device_type, u16 *phy_data);
s32 ixgbe_ग_लिखो_phy_reg_generic(काष्ठा ixgbe_hw *hw, u32 reg_addr,
				u32 device_type, u16 phy_data);
s32 ixgbe_पढ़ो_phy_reg_mdi(काष्ठा ixgbe_hw *hw, u32 reg_addr,
			   u32 device_type, u16 *phy_data);
s32 ixgbe_ग_लिखो_phy_reg_mdi(काष्ठा ixgbe_hw *hw, u32 reg_addr,
			    u32 device_type, u16 phy_data);
s32 ixgbe_setup_phy_link_generic(काष्ठा ixgbe_hw *hw);
s32 ixgbe_setup_phy_link_speed_generic(काष्ठा ixgbe_hw *hw,
				       ixgbe_link_speed speed,
				       bool स्वतःneg_रुको_to_complete);
s32 ixgbe_get_copper_link_capabilities_generic(काष्ठा ixgbe_hw *hw,
					       ixgbe_link_speed *speed,
					       bool *स्वतःneg);
bool ixgbe_check_reset_blocked(काष्ठा ixgbe_hw *hw);

/* PHY specअगरic */
s32 ixgbe_check_phy_link_tnx(काष्ठा ixgbe_hw *hw,
			     ixgbe_link_speed *speed,
			     bool *link_up);
s32 ixgbe_setup_phy_link_tnx(काष्ठा ixgbe_hw *hw);

s32 ixgbe_reset_phy_nl(काष्ठा ixgbe_hw *hw);
s32 ixgbe_set_copper_phy_घातer(काष्ठा ixgbe_hw *hw, bool on);
s32 ixgbe_identअगरy_module_generic(काष्ठा ixgbe_hw *hw);
s32 ixgbe_identअगरy_sfp_module_generic(काष्ठा ixgbe_hw *hw);
s32 ixgbe_get_sfp_init_sequence_offsets(काष्ठा ixgbe_hw *hw,
					u16 *list_offset,
					u16 *data_offset);
s32 ixgbe_tn_check_overtemp(काष्ठा ixgbe_hw *hw);
s32 ixgbe_पढ़ो_i2c_byte_generic(काष्ठा ixgbe_hw *hw, u8 byte_offset,
				u8 dev_addr, u8 *data);
s32 ixgbe_पढ़ो_i2c_byte_generic_unlocked(काष्ठा ixgbe_hw *hw, u8 byte_offset,
					 u8 dev_addr, u8 *data);
s32 ixgbe_ग_लिखो_i2c_byte_generic(काष्ठा ixgbe_hw *hw, u8 byte_offset,
				 u8 dev_addr, u8 data);
s32 ixgbe_ग_लिखो_i2c_byte_generic_unlocked(काष्ठा ixgbe_hw *hw, u8 byte_offset,
					  u8 dev_addr, u8 data);
s32 ixgbe_पढ़ो_i2c_eeprom_generic(काष्ठा ixgbe_hw *hw, u8 byte_offset,
				  u8 *eeprom_data);
s32 ixgbe_पढ़ो_i2c_sff8472_generic(काष्ठा ixgbe_hw *hw, u8 byte_offset,
				   u8 *sff8472_data);
s32 ixgbe_ग_लिखो_i2c_eeprom_generic(काष्ठा ixgbe_hw *hw, u8 byte_offset,
				   u8 eeprom_data);
s32 ixgbe_पढ़ो_i2c_combined_generic_पूर्णांक(काष्ठा ixgbe_hw *, u8 addr, u16 reg,
					u16 *val, bool lock);
s32 ixgbe_ग_लिखो_i2c_combined_generic_पूर्णांक(काष्ठा ixgbe_hw *, u8 addr, u16 reg,
					 u16 val, bool lock);
#पूर्ण_अगर /* _IXGBE_PHY_H_ */
