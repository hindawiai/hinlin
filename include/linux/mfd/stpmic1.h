<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) STMicroelectronics 2018 - All Rights Reserved
 * Author: Philippe Peuriअक्षरd <philippe.peuriअक्षरd@st.com>,
 * Pascal Paillet <p.paillet@st.com> क्रम STMicroelectronics.
 */

#अगर_अघोषित __LINUX_MFD_STPMIC1_H
#घोषणा __LINUX_MFD_STPMIC1_H

#घोषणा TURN_ON_SR		0x1
#घोषणा TURN_OFF_SR		0x2
#घोषणा ICC_LDO_TURN_OFF_SR	0x3
#घोषणा ICC_BUCK_TURN_OFF_SR	0x4
#घोषणा RREQ_STATE_SR		0x5
#घोषणा VERSION_SR		0x6

#घोषणा SWOFF_PWRCTRL_CR	0x10
#घोषणा PADS_PULL_CR		0x11
#घोषणा BUCKS_PD_CR		0x12
#घोषणा LDO14_PD_CR		0x13
#घोषणा LDO56_VREF_PD_CR	0x14
#घोषणा VBUS_DET_VIN_CR		0x15
#घोषणा PKEY_TURNOFF_CR		0x16
#घोषणा BUCKS_MASK_RANK_CR	0x17
#घोषणा BUCKS_MASK_RESET_CR	0x18
#घोषणा LDOS_MASK_RANK_CR	0x19
#घोषणा LDOS_MASK_RESET_CR	0x1A
#घोषणा WCHDG_CR		0x1B
#घोषणा WCHDG_TIMER_CR		0x1C
#घोषणा BUCKS_ICCTO_CR		0x1D
#घोषणा LDOS_ICCTO_CR		0x1E

#घोषणा BUCK1_ACTIVE_CR		0x20
#घोषणा BUCK2_ACTIVE_CR		0x21
#घोषणा BUCK3_ACTIVE_CR		0x22
#घोषणा BUCK4_ACTIVE_CR		0x23
#घोषणा VREF_DDR_ACTIVE_CR	0x24
#घोषणा LDO1_ACTIVE_CR		0x25
#घोषणा LDO2_ACTIVE_CR		0x26
#घोषणा LDO3_ACTIVE_CR		0x27
#घोषणा LDO4_ACTIVE_CR		0x28
#घोषणा LDO5_ACTIVE_CR		0x29
#घोषणा LDO6_ACTIVE_CR		0x2A

#घोषणा BUCK1_STDBY_CR		0x30
#घोषणा BUCK2_STDBY_CR		0x31
#घोषणा BUCK3_STDBY_CR		0x32
#घोषणा BUCK4_STDBY_CR		0x33
#घोषणा VREF_DDR_STDBY_CR	0x34
#घोषणा LDO1_STDBY_CR		0x35
#घोषणा LDO2_STDBY_CR		0x36
#घोषणा LDO3_STDBY_CR		0x37
#घोषणा LDO4_STDBY_CR		0x38
#घोषणा LDO5_STDBY_CR		0x39
#घोषणा LDO6_STDBY_CR		0x3A

#घोषणा BST_SW_CR		0x40

#घोषणा INT_PENDING_R1		0x50
#घोषणा INT_PENDING_R2		0x51
#घोषणा INT_PENDING_R3		0x52
#घोषणा INT_PENDING_R4		0x53

#घोषणा INT_DBG_LATCH_R1	0x60
#घोषणा INT_DBG_LATCH_R2	0x61
#घोषणा INT_DBG_LATCH_R3	0x62
#घोषणा INT_DBG_LATCH_R4	0x63

#घोषणा INT_CLEAR_R1		0x70
#घोषणा INT_CLEAR_R2		0x71
#घोषणा INT_CLEAR_R3		0x72
#घोषणा INT_CLEAR_R4		0x73

#घोषणा INT_MASK_R1		0x80
#घोषणा INT_MASK_R2		0x81
#घोषणा INT_MASK_R3		0x82
#घोषणा INT_MASK_R4		0x83

#घोषणा INT_SET_MASK_R1		0x90
#घोषणा INT_SET_MASK_R2		0x91
#घोषणा INT_SET_MASK_R3		0x92
#घोषणा INT_SET_MASK_R4		0x93

#घोषणा INT_CLEAR_MASK_R1	0xA0
#घोषणा INT_CLEAR_MASK_R2	0xA1
#घोषणा INT_CLEAR_MASK_R3	0xA2
#घोषणा INT_CLEAR_MASK_R4	0xA3

#घोषणा INT_SRC_R1		0xB0
#घोषणा INT_SRC_R2		0xB1
#घोषणा INT_SRC_R3		0xB2
#घोषणा INT_SRC_R4		0xB3

#घोषणा PMIC_MAX_REGISTER_ADDRESS INT_SRC_R4

#घोषणा STPMIC1_PMIC_NUM_IRQ_REGS 4

#घोषणा TURN_OFF_SR_ICC_EVENT	0x08

#घोषणा LDO_VOLTAGE_MASK		GENMASK(6, 2)
#घोषणा BUCK_VOLTAGE_MASK		GENMASK(7, 2)
#घोषणा LDO_BUCK_VOLTAGE_SHIFT		2

#घोषणा LDO_ENABLE_MASK			BIT(0)
#घोषणा BUCK_ENABLE_MASK		BIT(0)

#घोषणा BUCK_HPLP_ENABLE_MASK		BIT(1)
#घोषणा BUCK_HPLP_SHIFT			1

#घोषणा STDBY_ENABLE_MASK  BIT(0)

#घोषणा BUCKS_PD_CR_REG_MASK	GENMASK(7, 0)
#घोषणा BUCK_MASK_RANK_REGISTER_MASK	GENMASK(3, 0)
#घोषणा BUCK_MASK_RESET_REGISTER_MASK	GENMASK(3, 0)
#घोषणा LDO1234_PULL_DOWN_REGISTER_MASK	GENMASK(7, 0)
#घोषणा LDO56_VREF_PD_CR_REG_MASK	GENMASK(5, 0)
#घोषणा LDO_MASK_RANK_REGISTER_MASK	GENMASK(5, 0)
#घोषणा LDO_MASK_RESET_REGISTER_MASK	GENMASK(5, 0)

#घोषणा BUCK1_PULL_DOWN_REG		BUCKS_PD_CR
#घोषणा BUCK1_PULL_DOWN_MASK		BIT(0)
#घोषणा BUCK2_PULL_DOWN_REG		BUCKS_PD_CR
#घोषणा BUCK2_PULL_DOWN_MASK		BIT(2)
#घोषणा BUCK3_PULL_DOWN_REG		BUCKS_PD_CR
#घोषणा BUCK3_PULL_DOWN_MASK		BIT(4)
#घोषणा BUCK4_PULL_DOWN_REG		BUCKS_PD_CR
#घोषणा BUCK4_PULL_DOWN_MASK		BIT(6)

#घोषणा LDO1_PULL_DOWN_REG		LDO14_PD_CR
#घोषणा LDO1_PULL_DOWN_MASK		BIT(0)
#घोषणा LDO2_PULL_DOWN_REG		LDO14_PD_CR
#घोषणा LDO2_PULL_DOWN_MASK		BIT(2)
#घोषणा LDO3_PULL_DOWN_REG		LDO14_PD_CR
#घोषणा LDO3_PULL_DOWN_MASK		BIT(4)
#घोषणा LDO4_PULL_DOWN_REG		LDO14_PD_CR
#घोषणा LDO4_PULL_DOWN_MASK		BIT(6)
#घोषणा LDO5_PULL_DOWN_REG		LDO56_VREF_PD_CR
#घोषणा LDO5_PULL_DOWN_MASK		BIT(0)
#घोषणा LDO6_PULL_DOWN_REG		LDO56_VREF_PD_CR
#घोषणा LDO6_PULL_DOWN_MASK		BIT(2)
#घोषणा VREF_DDR_PULL_DOWN_REG		LDO56_VREF_PD_CR
#घोषणा VREF_DDR_PULL_DOWN_MASK		BIT(4)

#घोषणा BUCKS_ICCTO_CR_REG_MASK	GENMASK(6, 0)
#घोषणा LDOS_ICCTO_CR_REG_MASK	GENMASK(5, 0)

#घोषणा LDO_BYPASS_MASK			BIT(7)

/* Main PMIC Control Register
 * SWOFF_PWRCTRL_CR
 * Address : 0x10
 */
#घोषणा ICC_EVENT_ENABLED		BIT(4)
#घोषणा PWRCTRL_POLARITY_HIGH		BIT(3)
#घोषणा PWRCTRL_PIN_VALID		BIT(2)
#घोषणा RESTART_REQUEST_ENABLED		BIT(1)
#घोषणा SOFTWARE_SWITCH_OFF_ENABLED	BIT(0)

/* Main PMIC PADS Control Register
 * PADS_PULL_CR
 * Address : 0x11
 */
#घोषणा WAKEUP_DETECTOR_DISABLED	BIT(4)
#घोषणा PWRCTRL_PD_ACTIVE		BIT(3)
#घोषणा PWRCTRL_PU_ACTIVE		BIT(2)
#घोषणा WAKEUP_PD_ACTIVE		BIT(1)
#घोषणा PONKEY_PU_INACTIVE		BIT(0)

/* Main PMIC VINLOW Control Register
 * VBUS_DET_VIN_CRC DMSC
 * Address : 0x15
 */
#घोषणा SWIN_DETECTOR_ENABLED		BIT(7)
#घोषणा SWOUT_DETECTOR_ENABLED		BIT(6)
#घोषणा VINLOW_ENABLED			BIT(0)
#घोषणा VINLOW_CTRL_REG_MASK		GENMASK(7, 0)

/* USB Control Register
 * Address : 0x40
 */
#घोषणा BOOST_OVP_DISABLED		BIT(7)
#घोषणा VBUS_OTG_DETECTION_DISABLED	BIT(6)
#घोषणा SW_OUT_DISCHARGE		BIT(5)
#घोषणा VBUS_OTG_DISCHARGE		BIT(4)
#घोषणा OCP_LIMIT_HIGH			BIT(3)
#घोषणा SWIN_SWOUT_ENABLED		BIT(2)
#घोषणा USBSW_OTG_SWITCH_ENABLED	BIT(1)
#घोषणा BOOST_ENABLED			BIT(0)

/* PKEY_TURNOFF_CR
 * Address : 0x16
 */
#घोषणा PONKEY_PWR_OFF			BIT(7)
#घोषणा PONKEY_CC_FLAG_CLEAR		BIT(6)
#घोषणा PONKEY_TURNOFF_TIMER_MASK	GENMASK(3, 0)
#घोषणा PONKEY_TURNOFF_MASK		GENMASK(7, 0)

/*
 * काष्ठा stpmic1 - stpmic1 master device क्रम sub-drivers
 * @dev: master device of the chip (can be used to access platक्रमm data)
 * @irq: मुख्य IRQ number
 * @regmap_irq_chip_data: irq chip data
 */
काष्ठा stpmic1 अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	पूर्णांक irq;
	काष्ठा regmap_irq_chip_data *irq_data;
पूर्ण;

#पूर्ण_अगर /*  __LINUX_MFD_STPMIC1_H */
