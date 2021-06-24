<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * phy-brcm-usb-init.c - Broadcom USB Phy chip specअगरic init functions
 *
 * Copyright (C) 2014-2017 Broadcom
 */

/*
 * This module contains USB PHY initialization क्रम घातer up and S3 resume
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>

#समावेश <linux/soc/brcmstb/brcmstb.h>
#समावेश "phy-brcm-usb-init.h"

#घोषणा PHY_PORTS 2
#घोषणा PHY_PORT_SELECT_0 0
#घोषणा PHY_PORT_SELECT_1 0x1000

/* Register definitions क्रम the USB CTRL block */
#घोषणा USB_CTRL_SETUP			0x00
#घोषणा   USB_CTRL_SETUP_IOC_MASK			0x00000010
#घोषणा   USB_CTRL_SETUP_IPP_MASK			0x00000020
#घोषणा   USB_CTRL_SETUP_BABO_MASK			0x00000001
#घोषणा   USB_CTRL_SETUP_FNHW_MASK			0x00000002
#घोषणा   USB_CTRL_SETUP_FNBO_MASK			0x00000004
#घोषणा   USB_CTRL_SETUP_WABO_MASK			0x00000008
#घोषणा   USB_CTRL_SETUP_SCB_CLIENT_SWAP_MASK		0x00002000 /* option */
#घोषणा   USB_CTRL_SETUP_SCB1_EN_MASK			0x00004000 /* option */
#घोषणा   USB_CTRL_SETUP_SCB2_EN_MASK			0x00008000 /* option */
#घोषणा   USB_CTRL_SETUP_SS_EHCI64BIT_EN_MASK		0X00020000 /* option */
#घोषणा   USB_CTRL_SETUP_SS_EHCI64BIT_EN_VAR_MASK	0x00010000 /* option */
#घोषणा   USB_CTRL_SETUP_STRAP_IPP_SEL_MASK		0x02000000 /* option */
#घोषणा   USB_CTRL_SETUP_CC_DRD_MODE_ENABLE_MASK	0x04000000 /* option */
#घोषणा   USB_CTRL_SETUP_STRAP_CC_DRD_MODE_ENABLE_SEL_MASK 0x08000000 /* opt */
#घोषणा   USB_CTRL_SETUP_OC3_DISABLE_MASK		0xc0000000 /* option */
#घोषणा USB_CTRL_PLL_CTL		0x04
#घोषणा   USB_CTRL_PLL_CTL_PLL_SUSPEND_EN_MASK		0x08000000
#घोषणा   USB_CTRL_PLL_CTL_PLL_RESETB_MASK		0x40000000
#घोषणा   USB_CTRL_PLL_CTL_PLL_IDDQ_PWRDN_MASK		0x80000000 /* option */
#घोषणा USB_CTRL_EBRIDGE		0x0c
#घोषणा   USB_CTRL_EBRIDGE_ESTOP_SCB_REQ_MASK		0x00020000 /* option */
#घोषणा   USB_CTRL_EBRIDGE_EBR_SCB_SIZE_MASK		0x00000f80 /* option */
#घोषणा USB_CTRL_OBRIDGE		0x10
#घोषणा   USB_CTRL_OBRIDGE_LS_KEEP_ALIVE_MASK		0x08000000
#घोषणा USB_CTRL_MDIO			0x14
#घोषणा USB_CTRL_MDIO2			0x18
#घोषणा USB_CTRL_UTMI_CTL_1		0x2c
#घोषणा   USB_CTRL_UTMI_CTL_1_POWER_UP_FSM_EN_MASK	0x00000800
#घोषणा   USB_CTRL_UTMI_CTL_1_POWER_UP_FSM_EN_P1_MASK	0x08000000
#घोषणा USB_CTRL_USB_PM			0x34
#घोषणा   USB_CTRL_USB_PM_BDC_SOFT_RESETB_MASK		0x00800000 /* option */
#घोषणा   USB_CTRL_USB_PM_XHC_SOFT_RESETB_MASK		0x00400000 /* option */
#घोषणा   USB_CTRL_USB_PM_XHC_SOFT_RESETB_VAR_MASK	0x40000000 /* option */
#घोषणा   USB_CTRL_USB_PM_USB_PWRDN_MASK		0x80000000 /* option */
#घोषणा   USB_CTRL_USB_PM_SOFT_RESET_MASK		0x40000000 /* option */
#घोषणा   USB_CTRL_USB_PM_USB20_HC_RESETB_MASK		0x30000000 /* option */
#घोषणा   USB_CTRL_USB_PM_USB20_HC_RESETB_VAR_MASK	0x00300000 /* option */
#घोषणा   USB_CTRL_USB_PM_RMTWKUP_EN_MASK		0x00000001
#घोषणा USB_CTRL_USB_PM_STATUS		0x38
#घोषणा USB_CTRL_USB30_CTL1		0x60
#घोषणा   USB_CTRL_USB30_CTL1_PHY3_PLL_SEQ_START_MASK	0x00000010
#घोषणा   USB_CTRL_USB30_CTL1_PHY3_RESETB_MASK		0x00010000
#घोषणा   USB_CTRL_USB30_CTL1_XHC_SOFT_RESETB_MASK	0x00020000 /* option */
#घोषणा   USB_CTRL_USB30_CTL1_USB3_IOC_MASK		0x10000000 /* option */
#घोषणा   USB_CTRL_USB30_CTL1_USB3_IPP_MASK		0x20000000 /* option */
#घोषणा USB_CTRL_USB30_PCTL		0x70
#घोषणा   USB_CTRL_USB30_PCTL_PHY3_SOFT_RESETB_MASK	0x00000002
#घोषणा   USB_CTRL_USB30_PCTL_PHY3_IDDQ_OVERRIDE_MASK	0x00008000
#घोषणा   USB_CTRL_USB30_PCTL_PHY3_SOFT_RESETB_P1_MASK	0x00020000
#घोषणा USB_CTRL_USB_DEVICE_CTL1	0x90
#घोषणा   USB_CTRL_USB_DEVICE_CTL1_PORT_MODE_MASK	0x00000003 /* option */

/* Register definitions क्रम the XHCI EC block */
#घोषणा USB_XHCI_EC_IRAADR 0x658
#घोषणा USB_XHCI_EC_IRADAT 0x65c

क्रमागत brcm_family_type अणु
	BRCM_FAMILY_3390A0,
	BRCM_FAMILY_7250B0,
	BRCM_FAMILY_7271A0,
	BRCM_FAMILY_7364A0,
	BRCM_FAMILY_7366C0,
	BRCM_FAMILY_74371A0,
	BRCM_FAMILY_7439B0,
	BRCM_FAMILY_7445D0,
	BRCM_FAMILY_7260A0,
	BRCM_FAMILY_7278A0,
	BRCM_FAMILY_COUNT,
पूर्ण;

#घोषणा USB_BRCM_FAMILY(chip) \
	[BRCM_FAMILY_##chip] = __stringअगरy(chip)

अटल स्थिर अक्षर *family_names[BRCM_FAMILY_COUNT] = अणु
	USB_BRCM_FAMILY(3390A0),
	USB_BRCM_FAMILY(7250B0),
	USB_BRCM_FAMILY(7271A0),
	USB_BRCM_FAMILY(7364A0),
	USB_BRCM_FAMILY(7366C0),
	USB_BRCM_FAMILY(74371A0),
	USB_BRCM_FAMILY(7439B0),
	USB_BRCM_FAMILY(7445D0),
	USB_BRCM_FAMILY(7260A0),
	USB_BRCM_FAMILY(7278A0),
पूर्ण;

क्रमागत अणु
	USB_CTRL_SETUP_SCB1_EN_SELECTOR,
	USB_CTRL_SETUP_SCB2_EN_SELECTOR,
	USB_CTRL_SETUP_SS_EHCI64BIT_EN_SELECTOR,
	USB_CTRL_SETUP_STRAP_IPP_SEL_SELECTOR,
	USB_CTRL_SETUP_OC3_DISABLE_SELECTOR,
	USB_CTRL_PLL_CTL_PLL_IDDQ_PWRDN_SELECTOR,
	USB_CTRL_USB_PM_BDC_SOFT_RESETB_SELECTOR,
	USB_CTRL_USB_PM_XHC_SOFT_RESETB_SELECTOR,
	USB_CTRL_USB_PM_USB_PWRDN_SELECTOR,
	USB_CTRL_USB30_CTL1_XHC_SOFT_RESETB_SELECTOR,
	USB_CTRL_USB30_CTL1_USB3_IOC_SELECTOR,
	USB_CTRL_USB30_CTL1_USB3_IPP_SELECTOR,
	USB_CTRL_USB_DEVICE_CTL1_PORT_MODE_SELECTOR,
	USB_CTRL_USB_PM_SOFT_RESET_SELECTOR,
	USB_CTRL_SETUP_CC_DRD_MODE_ENABLE_SELECTOR,
	USB_CTRL_SETUP_STRAP_CC_DRD_MODE_ENABLE_SEL_SELECTOR,
	USB_CTRL_USB_PM_USB20_HC_RESETB_SELECTOR,
	USB_CTRL_SETUP_ENDIAN_SELECTOR,
	USB_CTRL_SELECTOR_COUNT,
पूर्ण;

#घोषणा USB_CTRL_MASK_FAMILY(params, reg, field)			\
	(params->usb_reg_bits_map[USB_CTRL_##reg##_##field##_SELECTOR])

#घोषणा USB_CTRL_SET_FAMILY(params, reg, field)	\
	usb_ctrl_set_family(params, USB_CTRL_##reg,	\
			USB_CTRL_##reg##_##field##_SELECTOR)
#घोषणा USB_CTRL_UNSET_FAMILY(params, reg, field)	\
	usb_ctrl_unset_family(params, USB_CTRL_##reg,	\
		USB_CTRL_##reg##_##field##_SELECTOR)

#घोषणा MDIO_USB2	0
#घोषणा MDIO_USB3	BIT(31)

#घोषणा USB_CTRL_SETUP_ENDIAN_BITS (	\
		USB_CTRL_MASK(SETUP, BABO) |	\
		USB_CTRL_MASK(SETUP, FNHW) |	\
		USB_CTRL_MASK(SETUP, FNBO) |	\
		USB_CTRL_MASK(SETUP, WABO))

#अगर_घोषित __LITTLE_ENDIAN
#घोषणा ENDIAN_SETTINGS (			\
		USB_CTRL_MASK(SETUP, BABO) |	\
		USB_CTRL_MASK(SETUP, FNHW))
#अन्यथा
#घोषणा ENDIAN_SETTINGS (			\
		USB_CTRL_MASK(SETUP, FNHW) |	\
		USB_CTRL_MASK(SETUP, FNBO) |	\
		USB_CTRL_MASK(SETUP, WABO))
#पूर्ण_अगर

काष्ठा id_to_type अणु
	u32 id;
	पूर्णांक type;
पूर्ण;

अटल स्थिर काष्ठा id_to_type id_to_type_table[] = अणु
	अणु 0x33900000, BRCM_FAMILY_3390A0 पूर्ण,
	अणु 0x72500010, BRCM_FAMILY_7250B0 पूर्ण,
	अणु 0x72600000, BRCM_FAMILY_7260A0 पूर्ण,
	अणु 0x72550000, BRCM_FAMILY_7260A0 पूर्ण,
	अणु 0x72680000, BRCM_FAMILY_7271A0 पूर्ण,
	अणु 0x72710000, BRCM_FAMILY_7271A0 पूर्ण,
	अणु 0x73640000, BRCM_FAMILY_7364A0 पूर्ण,
	अणु 0x73660020, BRCM_FAMILY_7366C0 पूर्ण,
	अणु 0x07437100, BRCM_FAMILY_74371A0 पूर्ण,
	अणु 0x74390010, BRCM_FAMILY_7439B0 पूर्ण,
	अणु 0x74450030, BRCM_FAMILY_7445D0 पूर्ण,
	अणु 0x72780000, BRCM_FAMILY_7278A0 पूर्ण,
	अणु 0, BRCM_FAMILY_7271A0 पूर्ण, /* शेष */
पूर्ण;

अटल स्थिर u32
usb_reg_bits_map_table[BRCM_FAMILY_COUNT][USB_CTRL_SELECTOR_COUNT] = अणु
	/* 3390B0 */
	[BRCM_FAMILY_3390A0] = अणु
		USB_CTRL_SETUP_SCB1_EN_MASK,
		USB_CTRL_SETUP_SCB2_EN_MASK,
		USB_CTRL_SETUP_SS_EHCI64BIT_EN_MASK,
		USB_CTRL_SETUP_STRAP_IPP_SEL_MASK,
		USB_CTRL_SETUP_OC3_DISABLE_MASK,
		0, /* USB_CTRL_PLL_CTL_PLL_IDDQ_PWRDN_MASK */
		0, /* USB_CTRL_USB_PM_BDC_SOFT_RESETB_MASK */
		USB_CTRL_USB_PM_XHC_SOFT_RESETB_MASK,
		USB_CTRL_USB_PM_USB_PWRDN_MASK,
		0, /* USB_CTRL_USB30_CTL1_XHC_SOFT_RESETB_MASK */
		0, /* USB_CTRL_USB30_CTL1_USB3_IOC_MASK */
		0, /* USB_CTRL_USB30_CTL1_USB3_IPP_MASK */
		USB_CTRL_USB_DEVICE_CTL1_PORT_MODE_MASK,
		0, /* USB_CTRL_USB_PM_SOFT_RESET_MASK */
		0, /* USB_CTRL_SETUP_CC_DRD_MODE_ENABLE_MASK */
		0, /* USB_CTRL_SETUP_STRAP_CC_DRD_MODE_ENABLE_SEL_MASK */
		USB_CTRL_USB_PM_USB20_HC_RESETB_VAR_MASK,
		ENDIAN_SETTINGS, /* USB_CTRL_SETUP ENDIAN bits */
	पूर्ण,
	/* 7250b0 */
	[BRCM_FAMILY_7250B0] = अणु
		USB_CTRL_SETUP_SCB1_EN_MASK,
		USB_CTRL_SETUP_SCB2_EN_MASK,
		USB_CTRL_SETUP_SS_EHCI64BIT_EN_MASK,
		0, /* USB_CTRL_SETUP_STRAP_IPP_SEL_MASK */
		USB_CTRL_SETUP_OC3_DISABLE_MASK,
		USB_CTRL_PLL_CTL_PLL_IDDQ_PWRDN_MASK,
		0, /* USB_CTRL_USB_PM_BDC_SOFT_RESETB_MASK */
		USB_CTRL_USB_PM_XHC_SOFT_RESETB_VAR_MASK,
		0, /* USB_CTRL_USB_PM_USB_PWRDN_MASK */
		0, /* USB_CTRL_USB30_CTL1_XHC_SOFT_RESETB_MASK */
		0, /* USB_CTRL_USB30_CTL1_USB3_IOC_MASK */
		0, /* USB_CTRL_USB30_CTL1_USB3_IPP_MASK */
		0, /* USB_CTRL_USB_DEVICE_CTL1_PORT_MODE_MASK */
		0, /* USB_CTRL_USB_PM_SOFT_RESET_MASK */
		0, /* USB_CTRL_SETUP_CC_DRD_MODE_ENABLE_MASK */
		0, /* USB_CTRL_SETUP_STRAP_CC_DRD_MODE_ENABLE_SEL_MASK */
		USB_CTRL_USB_PM_USB20_HC_RESETB_MASK,
		ENDIAN_SETTINGS, /* USB_CTRL_SETUP ENDIAN bits */
	पूर्ण,
	/* 7271a0 */
	[BRCM_FAMILY_7271A0] = अणु
		0, /* USB_CTRL_SETUP_SCB1_EN_MASK */
		0, /* USB_CTRL_SETUP_SCB2_EN_MASK */
		USB_CTRL_SETUP_SS_EHCI64BIT_EN_MASK,
		USB_CTRL_SETUP_STRAP_IPP_SEL_MASK,
		USB_CTRL_SETUP_OC3_DISABLE_MASK,
		0, /* USB_CTRL_PLL_CTL_PLL_IDDQ_PWRDN_MASK */
		USB_CTRL_USB_PM_BDC_SOFT_RESETB_MASK,
		USB_CTRL_USB_PM_XHC_SOFT_RESETB_MASK,
		USB_CTRL_USB_PM_USB_PWRDN_MASK,
		0, /* USB_CTRL_USB30_CTL1_XHC_SOFT_RESETB_MASK */
		0, /* USB_CTRL_USB30_CTL1_USB3_IOC_MASK */
		0, /* USB_CTRL_USB30_CTL1_USB3_IPP_MASK */
		USB_CTRL_USB_DEVICE_CTL1_PORT_MODE_MASK,
		USB_CTRL_USB_PM_SOFT_RESET_MASK,
		USB_CTRL_SETUP_CC_DRD_MODE_ENABLE_MASK,
		USB_CTRL_SETUP_STRAP_CC_DRD_MODE_ENABLE_SEL_MASK,
		USB_CTRL_USB_PM_USB20_HC_RESETB_VAR_MASK,
		ENDIAN_SETTINGS, /* USB_CTRL_SETUP ENDIAN bits */
	पूर्ण,
	/* 7364a0 */
	[BRCM_FAMILY_7364A0] = अणु
		USB_CTRL_SETUP_SCB1_EN_MASK,
		USB_CTRL_SETUP_SCB2_EN_MASK,
		USB_CTRL_SETUP_SS_EHCI64BIT_EN_MASK,
		0, /* USB_CTRL_SETUP_STRAP_IPP_SEL_MASK */
		USB_CTRL_SETUP_OC3_DISABLE_MASK,
		USB_CTRL_PLL_CTL_PLL_IDDQ_PWRDN_MASK,
		0, /* USB_CTRL_USB_PM_BDC_SOFT_RESETB_MASK */
		USB_CTRL_USB_PM_XHC_SOFT_RESETB_VAR_MASK,
		0, /* USB_CTRL_USB_PM_USB_PWRDN_MASK */
		0, /* USB_CTRL_USB30_CTL1_XHC_SOFT_RESETB_MASK */
		0, /* USB_CTRL_USB30_CTL1_USB3_IOC_MASK */
		0, /* USB_CTRL_USB30_CTL1_USB3_IPP_MASK */
		0, /* USB_CTRL_USB_DEVICE_CTL1_PORT_MODE_MASK */
		0, /* USB_CTRL_USB_PM_SOFT_RESET_MASK */
		0, /* USB_CTRL_SETUP_CC_DRD_MODE_ENABLE_MASK */
		0, /* USB_CTRL_SETUP_STRAP_CC_DRD_MODE_ENABLE_SEL_MASK */
		USB_CTRL_USB_PM_USB20_HC_RESETB_MASK,
		ENDIAN_SETTINGS, /* USB_CTRL_SETUP ENDIAN bits */
	पूर्ण,
	/* 7366c0 */
	[BRCM_FAMILY_7366C0] = अणु
		USB_CTRL_SETUP_SCB1_EN_MASK,
		USB_CTRL_SETUP_SCB2_EN_MASK,
		USB_CTRL_SETUP_SS_EHCI64BIT_EN_MASK,
		0, /* USB_CTRL_SETUP_STRAP_IPP_SEL_MASK */
		USB_CTRL_SETUP_OC3_DISABLE_MASK,
		0, /* USB_CTRL_PLL_CTL_PLL_IDDQ_PWRDN_MASK */
		0, /* USB_CTRL_USB_PM_BDC_SOFT_RESETB_MASK */
		USB_CTRL_USB_PM_XHC_SOFT_RESETB_VAR_MASK,
		USB_CTRL_USB_PM_USB_PWRDN_MASK,
		0, /* USB_CTRL_USB30_CTL1_XHC_SOFT_RESETB_MASK */
		0, /* USB_CTRL_USB30_CTL1_USB3_IOC_MASK */
		0, /* USB_CTRL_USB30_CTL1_USB3_IPP_MASK */
		0, /* USB_CTRL_USB_DEVICE_CTL1_PORT_MODE_MASK */
		0, /* USB_CTRL_USB_PM_SOFT_RESET_MASK */
		0, /* USB_CTRL_SETUP_CC_DRD_MODE_ENABLE_MASK */
		0, /* USB_CTRL_SETUP_STRAP_CC_DRD_MODE_ENABLE_SEL_MASK */
		USB_CTRL_USB_PM_USB20_HC_RESETB_MASK,
		ENDIAN_SETTINGS, /* USB_CTRL_SETUP ENDIAN bits */
	पूर्ण,
	/* 74371A0 */
	[BRCM_FAMILY_74371A0] = अणु
		USB_CTRL_SETUP_SCB1_EN_MASK,
		USB_CTRL_SETUP_SCB2_EN_MASK,
		USB_CTRL_SETUP_SS_EHCI64BIT_EN_VAR_MASK,
		0, /* USB_CTRL_SETUP_STRAP_IPP_SEL_MASK */
		0, /* USB_CTRL_SETUP_OC3_DISABLE_MASK */
		USB_CTRL_PLL_CTL_PLL_IDDQ_PWRDN_MASK,
		0, /* USB_CTRL_USB_PM_BDC_SOFT_RESETB_MASK */
		0, /* USB_CTRL_USB_PM_XHC_SOFT_RESETB_MASK */
		0, /* USB_CTRL_USB_PM_USB_PWRDN_MASK */
		USB_CTRL_USB30_CTL1_XHC_SOFT_RESETB_MASK,
		USB_CTRL_USB30_CTL1_USB3_IOC_MASK,
		USB_CTRL_USB30_CTL1_USB3_IPP_MASK,
		0, /* USB_CTRL_USB_DEVICE_CTL1_PORT_MODE_MASK */
		0, /* USB_CTRL_USB_PM_SOFT_RESET_MASK */
		0, /* USB_CTRL_SETUP_CC_DRD_MODE_ENABLE_MASK */
		0, /* USB_CTRL_SETUP_STRAP_CC_DRD_MODE_ENABLE_SEL_MASK */
		0, /* USB_CTRL_USB_PM_USB20_HC_RESETB_MASK */
		ENDIAN_SETTINGS, /* USB_CTRL_SETUP ENDIAN bits */
	पूर्ण,
	/* 7439B0 */
	[BRCM_FAMILY_7439B0] = अणु
		USB_CTRL_SETUP_SCB1_EN_MASK,
		USB_CTRL_SETUP_SCB2_EN_MASK,
		USB_CTRL_SETUP_SS_EHCI64BIT_EN_MASK,
		USB_CTRL_SETUP_STRAP_IPP_SEL_MASK,
		USB_CTRL_SETUP_OC3_DISABLE_MASK,
		0, /* USB_CTRL_PLL_CTL_PLL_IDDQ_PWRDN_MASK */
		USB_CTRL_USB_PM_BDC_SOFT_RESETB_MASK,
		USB_CTRL_USB_PM_XHC_SOFT_RESETB_MASK,
		USB_CTRL_USB_PM_USB_PWRDN_MASK,
		0, /* USB_CTRL_USB30_CTL1_XHC_SOFT_RESETB_MASK */
		0, /* USB_CTRL_USB30_CTL1_USB3_IOC_MASK */
		0, /* USB_CTRL_USB30_CTL1_USB3_IPP_MASK */
		USB_CTRL_USB_DEVICE_CTL1_PORT_MODE_MASK,
		0, /* USB_CTRL_USB_PM_SOFT_RESET_MASK */
		0, /* USB_CTRL_SETUP_CC_DRD_MODE_ENABLE_MASK */
		0, /* USB_CTRL_SETUP_STRAP_CC_DRD_MODE_ENABLE_SEL_MASK */
		USB_CTRL_USB_PM_USB20_HC_RESETB_VAR_MASK,
		ENDIAN_SETTINGS, /* USB_CTRL_SETUP ENDIAN bits */
	पूर्ण,
	/* 7445d0 */
	[BRCM_FAMILY_7445D0] = अणु
		USB_CTRL_SETUP_SCB1_EN_MASK,
		USB_CTRL_SETUP_SCB2_EN_MASK,
		USB_CTRL_SETUP_SS_EHCI64BIT_EN_VAR_MASK,
		0, /* USB_CTRL_SETUP_STRAP_IPP_SEL_MASK */
		USB_CTRL_SETUP_OC3_DISABLE_MASK,
		USB_CTRL_PLL_CTL_PLL_IDDQ_PWRDN_MASK,
		0, /* USB_CTRL_USB_PM_BDC_SOFT_RESETB_MASK */
		0, /* USB_CTRL_USB_PM_XHC_SOFT_RESETB_MASK */
		0, /* USB_CTRL_USB_PM_USB_PWRDN_MASK */
		USB_CTRL_USB30_CTL1_XHC_SOFT_RESETB_MASK,
		0, /* USB_CTRL_USB30_CTL1_USB3_IOC_MASK */
		0, /* USB_CTRL_USB30_CTL1_USB3_IPP_MASK */
		0, /* USB_CTRL_USB_DEVICE_CTL1_PORT_MODE_MASK */
		0, /* USB_CTRL_USB_PM_SOFT_RESET_MASK */
		0, /* USB_CTRL_SETUP_CC_DRD_MODE_ENABLE_MASK */
		0, /* USB_CTRL_SETUP_STRAP_CC_DRD_MODE_ENABLE_SEL_MASK */
		USB_CTRL_USB_PM_USB20_HC_RESETB_VAR_MASK,
		ENDIAN_SETTINGS, /* USB_CTRL_SETUP ENDIAN bits */
	पूर्ण,
	/* 7260a0 */
	[BRCM_FAMILY_7260A0] = अणु
		0, /* USB_CTRL_SETUP_SCB1_EN_MASK */
		0, /* USB_CTRL_SETUP_SCB2_EN_MASK */
		USB_CTRL_SETUP_SS_EHCI64BIT_EN_MASK,
		USB_CTRL_SETUP_STRAP_IPP_SEL_MASK,
		USB_CTRL_SETUP_OC3_DISABLE_MASK,
		0, /* USB_CTRL_PLL_CTL_PLL_IDDQ_PWRDN_MASK */
		USB_CTRL_USB_PM_BDC_SOFT_RESETB_MASK,
		USB_CTRL_USB_PM_XHC_SOFT_RESETB_MASK,
		USB_CTRL_USB_PM_USB_PWRDN_MASK,
		0, /* USB_CTRL_USB30_CTL1_XHC_SOFT_RESETB_MASK */
		0, /* USB_CTRL_USB30_CTL1_USB3_IOC_MASK */
		0, /* USB_CTRL_USB30_CTL1_USB3_IPP_MASK */
		USB_CTRL_USB_DEVICE_CTL1_PORT_MODE_MASK,
		USB_CTRL_USB_PM_SOFT_RESET_MASK,
		USB_CTRL_SETUP_CC_DRD_MODE_ENABLE_MASK,
		USB_CTRL_SETUP_STRAP_CC_DRD_MODE_ENABLE_SEL_MASK,
		USB_CTRL_USB_PM_USB20_HC_RESETB_VAR_MASK,
		ENDIAN_SETTINGS, /* USB_CTRL_SETUP ENDIAN bits */
	पूर्ण,
	/* 7278a0 */
	[BRCM_FAMILY_7278A0] = अणु
		0, /* USB_CTRL_SETUP_SCB1_EN_MASK */
		0, /* USB_CTRL_SETUP_SCB2_EN_MASK */
		0, /*USB_CTRL_SETUP_SS_EHCI64BIT_EN_MASK */
		USB_CTRL_SETUP_STRAP_IPP_SEL_MASK,
		USB_CTRL_SETUP_OC3_DISABLE_MASK,
		0, /* USB_CTRL_PLL_CTL_PLL_IDDQ_PWRDN_MASK */
		USB_CTRL_USB_PM_BDC_SOFT_RESETB_MASK,
		USB_CTRL_USB_PM_XHC_SOFT_RESETB_MASK,
		USB_CTRL_USB_PM_USB_PWRDN_MASK,
		0, /* USB_CTRL_USB30_CTL1_XHC_SOFT_RESETB_MASK */
		0, /* USB_CTRL_USB30_CTL1_USB3_IOC_MASK */
		0, /* USB_CTRL_USB30_CTL1_USB3_IPP_MASK */
		USB_CTRL_USB_DEVICE_CTL1_PORT_MODE_MASK,
		USB_CTRL_USB_PM_SOFT_RESET_MASK,
		0, /* USB_CTRL_SETUP_CC_DRD_MODE_ENABLE_MASK */
		0, /* USB_CTRL_SETUP_STRAP_CC_DRD_MODE_ENABLE_SEL_MASK */
		0, /* USB_CTRL_USB_PM_USB20_HC_RESETB_MASK */
		0, /* USB_CTRL_SETUP ENDIAN bits */
	पूर्ण,
पूर्ण;

अटल अंतरभूत
व्योम usb_ctrl_unset_family(काष्ठा brcm_usb_init_params *params,
			   u32 reg_offset, u32 field)
अणु
	u32 mask;

	mask = params->usb_reg_bits_map[field];
	brcm_usb_ctrl_unset(params->regs[BRCM_REGS_CTRL] + reg_offset, mask);
पूर्ण;

अटल अंतरभूत
व्योम usb_ctrl_set_family(काष्ठा brcm_usb_init_params *params,
			 u32 reg_offset, u32 field)
अणु
	u32 mask;

	mask = params->usb_reg_bits_map[field];
	brcm_usb_ctrl_set(params->regs[BRCM_REGS_CTRL] + reg_offset, mask);
पूर्ण;

अटल u32 brcmusb_usb_mdio_पढ़ो(व्योम __iomem *ctrl_base, u32 reg, पूर्णांक mode)
अणु
	u32 data;

	data = (reg << 16) | mode;
	brcm_usb_ग_लिखोl(data, USB_CTRL_REG(ctrl_base, MDIO));
	data |= (1 << 24);
	brcm_usb_ग_लिखोl(data, USB_CTRL_REG(ctrl_base, MDIO));
	data &= ~(1 << 24);
	/* रुको क्रम the 60MHz parallel to serial shअगरter */
	usleep_range(10, 20);
	brcm_usb_ग_लिखोl(data, USB_CTRL_REG(ctrl_base, MDIO));
	/* रुको क्रम the 60MHz parallel to serial shअगरter */
	usleep_range(10, 20);

	वापस brcm_usb_पढ़ोl(USB_CTRL_REG(ctrl_base, MDIO2)) & 0xffff;
पूर्ण

अटल व्योम brcmusb_usb_mdio_ग_लिखो(व्योम __iomem *ctrl_base, u32 reg,
				   u32 val, पूर्णांक mode)
अणु
	u32 data;

	data = (reg << 16) | val | mode;
	brcm_usb_ग_लिखोl(data, USB_CTRL_REG(ctrl_base, MDIO));
	data |= (1 << 25);
	brcm_usb_ग_लिखोl(data, USB_CTRL_REG(ctrl_base, MDIO));
	data &= ~(1 << 25);

	/* रुको क्रम the 60MHz parallel to serial shअगरter */
	usleep_range(10, 20);
	brcm_usb_ग_लिखोl(data, USB_CTRL_REG(ctrl_base, MDIO));
	/* रुको क्रम the 60MHz parallel to serial shअगरter */
	usleep_range(10, 20);
पूर्ण

अटल व्योम brcmusb_usb_phy_lकरो_fix(व्योम __iomem *ctrl_base)
अणु
	/* first disable FSM but also leave it that way */
	/* to allow normal suspend/resume */
	USB_CTRL_UNSET(ctrl_base, UTMI_CTL_1, POWER_UP_FSM_EN);
	USB_CTRL_UNSET(ctrl_base, UTMI_CTL_1, POWER_UP_FSM_EN_P1);

	/* reset USB 2.0 PLL */
	USB_CTRL_UNSET(ctrl_base, PLL_CTL, PLL_RESETB);
	/* PLL reset period */
	udelay(1);
	USB_CTRL_SET(ctrl_base, PLL_CTL, PLL_RESETB);
	/* Give PLL enough समय to lock */
	usleep_range(1000, 2000);
पूर्ण

अटल व्योम brcmusb_usb2_eye_fix(व्योम __iomem *ctrl_base)
अणु
	/* Increase USB 2.0 TX level to meet spec requirement */
	brcmusb_usb_mdio_ग_लिखो(ctrl_base, 0x1f, 0x80a0, MDIO_USB2);
	brcmusb_usb_mdio_ग_लिखो(ctrl_base, 0x0a, 0xc6a0, MDIO_USB2);
पूर्ण

अटल व्योम brcmusb_usb3_pll_fix(व्योम __iomem *ctrl_base)
अणु
	/* Set correct winकरोw क्रम PLL lock detect */
	brcmusb_usb_mdio_ग_लिखो(ctrl_base, 0x1f, 0x8000, MDIO_USB3);
	brcmusb_usb_mdio_ग_लिखो(ctrl_base, 0x07, 0x1503, MDIO_USB3);
पूर्ण

अटल व्योम brcmusb_usb3_enable_pipe_reset(व्योम __iomem *ctrl_base)
अणु
	u32 val;

	/* Re-enable USB 3.0 pipe reset */
	brcmusb_usb_mdio_ग_लिखो(ctrl_base, 0x1f, 0x8000, MDIO_USB3);
	val = brcmusb_usb_mdio_पढ़ो(ctrl_base, 0x0f, MDIO_USB3) | 0x200;
	brcmusb_usb_mdio_ग_लिखो(ctrl_base, 0x0f, val, MDIO_USB3);
पूर्ण

अटल व्योम brcmusb_usb3_enable_sigdet(व्योम __iomem *ctrl_base)
अणु
	u32 val, ofs;
	पूर्णांक ii;

	ofs = 0;
	क्रम (ii = 0; ii < PHY_PORTS; ++ii) अणु
		/* Set correct शेष क्रम sigdet */
		brcmusb_usb_mdio_ग_लिखो(ctrl_base, 0x1f, (0x8080 + ofs),
				       MDIO_USB3);
		val = brcmusb_usb_mdio_पढ़ो(ctrl_base, 0x05, MDIO_USB3);
		val = (val & ~0x800f) | 0x800d;
		brcmusb_usb_mdio_ग_लिखो(ctrl_base, 0x05, val, MDIO_USB3);
		ofs = PHY_PORT_SELECT_1;
	पूर्ण
पूर्ण

अटल व्योम brcmusb_usb3_enable_skip_align(व्योम __iomem *ctrl_base)
अणु
	u32 val, ofs;
	पूर्णांक ii;

	ofs = 0;
	क्रम (ii = 0; ii < PHY_PORTS; ++ii) अणु
		/* Set correct शेष क्रम SKIP align */
		brcmusb_usb_mdio_ग_लिखो(ctrl_base, 0x1f, (0x8060 + ofs),
				       MDIO_USB3);
		val = brcmusb_usb_mdio_पढ़ो(ctrl_base, 0x01, MDIO_USB3) | 0x200;
		brcmusb_usb_mdio_ग_लिखो(ctrl_base, 0x01, val, MDIO_USB3);
		ofs = PHY_PORT_SELECT_1;
	पूर्ण
पूर्ण

अटल व्योम brcmusb_usb3_unमुक्तze_aeq(व्योम __iomem *ctrl_base)
अणु
	u32 val, ofs;
	पूर्णांक ii;

	ofs = 0;
	क्रम (ii = 0; ii < PHY_PORTS; ++ii) अणु
		/* Let EQ मुक्तze after TSEQ */
		brcmusb_usb_mdio_ग_लिखो(ctrl_base, 0x1f, (0x80e0 + ofs),
				       MDIO_USB3);
		val = brcmusb_usb_mdio_पढ़ो(ctrl_base, 0x01, MDIO_USB3);
		val &= ~0x0008;
		brcmusb_usb_mdio_ग_लिखो(ctrl_base, 0x01, val, MDIO_USB3);
		ofs = PHY_PORT_SELECT_1;
	पूर्ण
पूर्ण

अटल व्योम brcmusb_usb3_pll_54mhz(काष्ठा brcm_usb_init_params *params)
अणु
	u32 ofs;
	पूर्णांक ii;
	व्योम __iomem *ctrl_base = params->regs[BRCM_REGS_CTRL];

	/*
	 * On newer B53 based SoC's, the reference घड़ी क्रम the
	 * 3.0 PLL has been changed from 50MHz to 54MHz so the
	 * PLL needs to be reprogrammed.
	 * See SWLINUX-4006.
	 *
	 * On the 7364C0, the reference घड़ी क्रम the
	 * 3.0 PLL has been changed from 50MHz to 54MHz to
	 * work around a MOCA issue.
	 * See SWLINUX-4169.
	 */
	चयन (params->selected_family) अणु
	हाल BRCM_FAMILY_3390A0:
	हाल BRCM_FAMILY_7250B0:
	हाल BRCM_FAMILY_7366C0:
	हाल BRCM_FAMILY_74371A0:
	हाल BRCM_FAMILY_7439B0:
	हाल BRCM_FAMILY_7445D0:
	हाल BRCM_FAMILY_7260A0:
		वापस;
	हाल BRCM_FAMILY_7364A0:
		अगर (BRCM_REV(params->family_id) < 0x20)
			वापस;
		अवरोध;
	पूर्ण

	/* set USB 3.0 PLL to accept 54Mhz reference घड़ी */
	USB_CTRL_UNSET(ctrl_base, USB30_CTL1, PHY3_PLL_SEQ_START);

	brcmusb_usb_mdio_ग_लिखो(ctrl_base, 0x1f, 0x8000, MDIO_USB3);
	brcmusb_usb_mdio_ग_लिखो(ctrl_base, 0x10, 0x5784, MDIO_USB3);
	brcmusb_usb_mdio_ग_लिखो(ctrl_base, 0x11, 0x01d0, MDIO_USB3);
	brcmusb_usb_mdio_ग_लिखो(ctrl_base, 0x12, 0x1DE8, MDIO_USB3);
	brcmusb_usb_mdio_ग_लिखो(ctrl_base, 0x13, 0xAA80, MDIO_USB3);
	brcmusb_usb_mdio_ग_लिखो(ctrl_base, 0x14, 0x8826, MDIO_USB3);
	brcmusb_usb_mdio_ग_लिखो(ctrl_base, 0x15, 0x0044, MDIO_USB3);
	brcmusb_usb_mdio_ग_लिखो(ctrl_base, 0x16, 0x8000, MDIO_USB3);
	brcmusb_usb_mdio_ग_लिखो(ctrl_base, 0x17, 0x0851, MDIO_USB3);
	brcmusb_usb_mdio_ग_लिखो(ctrl_base, 0x18, 0x0000, MDIO_USB3);

	/* both ports */
	ofs = 0;
	क्रम (ii = 0; ii < PHY_PORTS; ++ii) अणु
		brcmusb_usb_mdio_ग_लिखो(ctrl_base, 0x1f, (0x8040 + ofs),
				       MDIO_USB3);
		brcmusb_usb_mdio_ग_लिखो(ctrl_base, 0x03, 0x0090, MDIO_USB3);
		brcmusb_usb_mdio_ग_लिखो(ctrl_base, 0x04, 0x0134, MDIO_USB3);
		brcmusb_usb_mdio_ग_लिखो(ctrl_base, 0x1f, (0x8020 + ofs),
				       MDIO_USB3);
		brcmusb_usb_mdio_ग_लिखो(ctrl_base, 0x01, 0x00e2, MDIO_USB3);
		ofs = PHY_PORT_SELECT_1;
	पूर्ण

	/* restart PLL sequence */
	USB_CTRL_SET(ctrl_base, USB30_CTL1, PHY3_PLL_SEQ_START);
	/* Give PLL enough समय to lock */
	usleep_range(1000, 2000);
पूर्ण

अटल व्योम brcmusb_usb3_ssc_enable(व्योम __iomem *ctrl_base)
अणु
	u32 val;

	/* Enable USB 3.0 TX spपढ़ो spectrum */
	brcmusb_usb_mdio_ग_लिखो(ctrl_base, 0x1f, 0x8040, MDIO_USB3);
	val = brcmusb_usb_mdio_पढ़ो(ctrl_base, 0x01, MDIO_USB3) | 0xf;
	brcmusb_usb_mdio_ग_लिखो(ctrl_base, 0x01, val, MDIO_USB3);

	/* Currently, USB 3.0 SSC is enabled via port 0 MDIO रेजिस्टरs,
	 * which should have been adequate. However, due to a bug in the
	 * USB 3.0 PHY, it must be enabled via both ports (HWUSB3DVT-26).
	 */
	brcmusb_usb_mdio_ग_लिखो(ctrl_base, 0x1f, 0x9040, MDIO_USB3);
	val = brcmusb_usb_mdio_पढ़ो(ctrl_base, 0x01, MDIO_USB3) | 0xf;
	brcmusb_usb_mdio_ग_लिखो(ctrl_base, 0x01, val, MDIO_USB3);
पूर्ण

अटल व्योम brcmusb_usb3_phy_workarounds(काष्ठा brcm_usb_init_params *params)
अणु
	व्योम __iomem *ctrl_base = params->regs[BRCM_REGS_CTRL];

	brcmusb_usb3_pll_fix(ctrl_base);
	brcmusb_usb3_pll_54mhz(params);
	brcmusb_usb3_ssc_enable(ctrl_base);
	brcmusb_usb3_enable_pipe_reset(ctrl_base);
	brcmusb_usb3_enable_sigdet(ctrl_base);
	brcmusb_usb3_enable_skip_align(ctrl_base);
	brcmusb_usb3_unमुक्तze_aeq(ctrl_base);
पूर्ण

अटल व्योम brcmusb_memc_fix(काष्ठा brcm_usb_init_params *params)
अणु
	u32 prid;

	अगर (params->selected_family != BRCM_FAMILY_7445D0)
		वापस;
	/*
	 * This is a workaround क्रम HW7445-1869 where a DMA ग_लिखो ends up
	 * करोing a पढ़ो pre-fetch after the end of the DMA buffer. This
	 * causes a problem when the DMA buffer is at the end of physical
	 * memory, causing the pre-fetch पढ़ो to access non-existent memory,
	 * and the chip bonकरोut has MEMC2 disabled. When the pre-fetch पढ़ो
	 * tries to use the disabled MEMC2, it hangs the bus. The workaround
	 * is to disable MEMC2 access in the usb controller which aव्योमs
	 * the hang.
	 */

	prid = params->product_id & 0xfffff000;
	चयन (prid) अणु
	हाल 0x72520000:
	हाल 0x74480000:
	हाल 0x74490000:
	हाल 0x07252000:
	हाल 0x07448000:
	हाल 0x07449000:
		USB_CTRL_UNSET_FAMILY(params, SETUP, SCB2_EN);
	पूर्ण
पूर्ण

अटल व्योम brcmusb_usb3_otp_fix(काष्ठा brcm_usb_init_params *params)
अणु
	व्योम __iomem *xhci_ec_base = params->regs[BRCM_REGS_XHCI_EC];
	u32 val;

	अगर (params->family_id != 0x74371000 || !xhci_ec_base)
		वापस;
	brcm_usb_ग_लिखोl(0xa20c, USB_XHCI_EC_REG(xhci_ec_base, IRAADR));
	val = brcm_usb_पढ़ोl(USB_XHCI_EC_REG(xhci_ec_base, IRADAT));

	/* set cfg_pick_ss_lock */
	val |= (1 << 27);
	brcm_usb_ग_लिखोl(val, USB_XHCI_EC_REG(xhci_ec_base, IRADAT));

	/* Reset USB 3.0 PHY क्रम workaround to take effect */
	USB_CTRL_UNSET(params->regs[BRCM_REGS_CTRL], USB30_CTL1, PHY3_RESETB);
	USB_CTRL_SET(params->regs[BRCM_REGS_CTRL], USB30_CTL1, PHY3_RESETB);
पूर्ण

अटल व्योम brcmusb_xhci_soft_reset(काष्ठा brcm_usb_init_params *params,
				    पूर्णांक on_off)
अणु
	/* Assert reset */
	अगर (on_off) अणु
		अगर (USB_CTRL_MASK_FAMILY(params, USB_PM, XHC_SOFT_RESETB))
			USB_CTRL_UNSET_FAMILY(params, USB_PM, XHC_SOFT_RESETB);
		अन्यथा
			USB_CTRL_UNSET_FAMILY(params,
					      USB30_CTL1, XHC_SOFT_RESETB);
	पूर्ण अन्यथा अणु /* De-निश्चित reset */
		अगर (USB_CTRL_MASK_FAMILY(params, USB_PM, XHC_SOFT_RESETB))
			USB_CTRL_SET_FAMILY(params, USB_PM, XHC_SOFT_RESETB);
		अन्यथा
			USB_CTRL_SET_FAMILY(params, USB30_CTL1,
					    XHC_SOFT_RESETB);
	पूर्ण
पूर्ण

/*
 * Return the best map table family. The order is:
 *   - exact match of chip and major rev
 *   - exact match of chip and बंदst older major rev
 *   - शेष chip/rev.
 * NOTE: The minor rev is always ignored.
 */
अटल क्रमागत brcm_family_type get_family_type(
	काष्ठा brcm_usb_init_params *params)
अणु
	पूर्णांक last_type = -1;
	u32 last_family = 0;
	u32 family_no_major;
	अचिन्हित पूर्णांक x;
	u32 family;

	family = params->family_id & 0xfffffff0;
	family_no_major = params->family_id & 0xffffff00;
	क्रम (x = 0; id_to_type_table[x].id; x++) अणु
		अगर (family == id_to_type_table[x].id)
			वापस id_to_type_table[x].type;
		अगर (family_no_major == (id_to_type_table[x].id & 0xffffff00))
			अगर (family > id_to_type_table[x].id &&
			    last_family < id_to_type_table[x].id) अणु
				last_family = id_to_type_table[x].id;
				last_type = id_to_type_table[x].type;
			पूर्ण
	पूर्ण

	/* If no match, वापस the शेष family */
	अगर (last_type == -1)
		वापस id_to_type_table[x].type;
	वापस last_type;
पूर्ण

अटल व्योम usb_init_ipp(काष्ठा brcm_usb_init_params *params)
अणु
	व्योम __iomem *ctrl = params->regs[BRCM_REGS_CTRL];
	u32 reg;
	u32 orig_reg;

	/* Starting with the 7445d0, there are no दीर्घer separate 3.0
	 * versions of IOC and IPP.
	 */
	अगर (USB_CTRL_MASK_FAMILY(params, USB30_CTL1, USB3_IOC)) अणु
		अगर (params->ioc)
			USB_CTRL_SET_FAMILY(params, USB30_CTL1, USB3_IOC);
		अगर (params->ipp == 1)
			USB_CTRL_SET_FAMILY(params, USB30_CTL1, USB3_IPP);
	पूर्ण

	reg = brcm_usb_पढ़ोl(USB_CTRL_REG(ctrl, SETUP));
	orig_reg = reg;
	अगर (USB_CTRL_MASK_FAMILY(params, SETUP, STRAP_CC_DRD_MODE_ENABLE_SEL))
		/* Never use the strap, it's going away. */
		reg &= ~(USB_CTRL_MASK_FAMILY(params,
					      SETUP,
					      STRAP_CC_DRD_MODE_ENABLE_SEL));
	अगर (USB_CTRL_MASK_FAMILY(params, SETUP, STRAP_IPP_SEL))
		/* override ipp strap pin (अगर it निकासs) */
		अगर (params->ipp != 2)
			reg &= ~(USB_CTRL_MASK_FAMILY(params, SETUP,
						      STRAP_IPP_SEL));

	/* Override the शेष OC and PP polarity */
	reg &= ~(USB_CTRL_MASK(SETUP, IPP) | USB_CTRL_MASK(SETUP, IOC));
	अगर (params->ioc)
		reg |= USB_CTRL_MASK(SETUP, IOC);
	अगर (params->ipp == 1)
		reg |= USB_CTRL_MASK(SETUP, IPP);
	brcm_usb_ग_लिखोl(reg, USB_CTRL_REG(ctrl, SETUP));

	/*
	 * If we're changing IPP, make sure घातer is off दीर्घ enough
	 * to turn off any connected devices.
	 */
	अगर ((reg ^ orig_reg) & USB_CTRL_MASK(SETUP, IPP))
		msleep(50);
पूर्ण

अटल व्योम usb_wake_enable(काष्ठा brcm_usb_init_params *params,
			  bool enable)
अणु
	व्योम __iomem *ctrl = params->regs[BRCM_REGS_CTRL];

	अगर (enable)
		USB_CTRL_SET(ctrl, USB_PM, RMTWKUP_EN);
	अन्यथा
		USB_CTRL_UNSET(ctrl, USB_PM, RMTWKUP_EN);
पूर्ण

अटल व्योम usb_init_common(काष्ठा brcm_usb_init_params *params)
अणु
	u32 reg;
	व्योम __iomem *ctrl = params->regs[BRCM_REGS_CTRL];

	/* Clear any pending wake conditions */
	usb_wake_enable(params, false);
	reg = brcm_usb_पढ़ोl(USB_CTRL_REG(ctrl, USB_PM_STATUS));
	brcm_usb_ग_लिखोl(reg, USB_CTRL_REG(ctrl, USB_PM_STATUS));

	/* Take USB out of घातer करोwn */
	अगर (USB_CTRL_MASK_FAMILY(params, PLL_CTL, PLL_IDDQ_PWRDN)) अणु
		USB_CTRL_UNSET_FAMILY(params, PLL_CTL, PLL_IDDQ_PWRDN);
		/* 1 millisecond - क्रम USB घड़ीs to settle करोwn */
		usleep_range(1000, 2000);
	पूर्ण

	अगर (USB_CTRL_MASK_FAMILY(params, USB_PM, USB_PWRDN)) अणु
		USB_CTRL_UNSET_FAMILY(params, USB_PM, USB_PWRDN);
		/* 1 millisecond - क्रम USB घड़ीs to settle करोwn */
		usleep_range(1000, 2000);
	पूर्ण

	अगर (params->selected_family != BRCM_FAMILY_74371A0 &&
	    (BRCM_ID(params->family_id) != 0x7364))
		/*
		 * HW7439-637: 7439a0 and its derivatives करो not have large
		 * enough descriptor storage क्रम this.
		 */
		USB_CTRL_SET_FAMILY(params, SETUP, SS_EHCI64BIT_EN);

	/* Block स्वतः PLL suspend by USB2 PHY (Sasi) */
	USB_CTRL_SET(ctrl, PLL_CTL, PLL_SUSPEND_EN);

	reg = brcm_usb_पढ़ोl(USB_CTRL_REG(ctrl, SETUP));
	अगर (params->selected_family == BRCM_FAMILY_7364A0)
		/* Suppress overcurrent indication from USB30 ports क्रम A0 */
		reg |= USB_CTRL_MASK_FAMILY(params, SETUP, OC3_DISABLE);

	brcmusb_usb_phy_lकरो_fix(ctrl);
	brcmusb_usb2_eye_fix(ctrl);

	/*
	 * Make sure the the second and third memory controller
	 * पूर्णांकerfaces are enabled अगर they exist.
	 */
	अगर (USB_CTRL_MASK_FAMILY(params, SETUP, SCB1_EN))
		reg |= USB_CTRL_MASK_FAMILY(params, SETUP, SCB1_EN);
	अगर (USB_CTRL_MASK_FAMILY(params, SETUP, SCB2_EN))
		reg |= USB_CTRL_MASK_FAMILY(params, SETUP, SCB2_EN);
	brcm_usb_ग_लिखोl(reg, USB_CTRL_REG(ctrl, SETUP));

	brcmusb_memc_fix(params);

	अगर (USB_CTRL_MASK_FAMILY(params, USB_DEVICE_CTL1, PORT_MODE)) अणु
		reg = brcm_usb_पढ़ोl(USB_CTRL_REG(ctrl, USB_DEVICE_CTL1));
		reg &= ~USB_CTRL_MASK_FAMILY(params, USB_DEVICE_CTL1,
					PORT_MODE);
		reg |= params->mode;
		brcm_usb_ग_लिखोl(reg, USB_CTRL_REG(ctrl, USB_DEVICE_CTL1));
	पूर्ण
	अगर (USB_CTRL_MASK_FAMILY(params, USB_PM, BDC_SOFT_RESETB)) अणु
		चयन (params->mode) अणु
		हाल USB_CTLR_MODE_HOST:
			USB_CTRL_UNSET_FAMILY(params, USB_PM, BDC_SOFT_RESETB);
			अवरोध;
		शेष:
			USB_CTRL_UNSET_FAMILY(params, USB_PM, BDC_SOFT_RESETB);
			USB_CTRL_SET_FAMILY(params, USB_PM, BDC_SOFT_RESETB);
		अवरोध;
		पूर्ण
	पूर्ण
	अगर (USB_CTRL_MASK_FAMILY(params, SETUP, CC_DRD_MODE_ENABLE)) अणु
		अगर (params->mode == USB_CTLR_MODE_TYPEC_PD)
			USB_CTRL_SET_FAMILY(params, SETUP, CC_DRD_MODE_ENABLE);
		अन्यथा
			USB_CTRL_UNSET_FAMILY(params, SETUP,
					      CC_DRD_MODE_ENABLE);
	पूर्ण
पूर्ण

अटल व्योम usb_init_eohci(काष्ठा brcm_usb_init_params *params)
अणु
	u32 reg;
	व्योम __iomem *ctrl = params->regs[BRCM_REGS_CTRL];

	अगर (USB_CTRL_MASK_FAMILY(params, USB_PM, USB20_HC_RESETB))
		USB_CTRL_SET_FAMILY(params, USB_PM, USB20_HC_RESETB);

	अगर (params->selected_family == BRCM_FAMILY_7366C0)
		/*
		 * Don't enable this so the memory controller doesn't पढ़ो
		 * पूर्णांकo memory holes. NOTE: This bit is low true on 7366C0.
		 */
		USB_CTRL_SET(ctrl, EBRIDGE, ESTOP_SCB_REQ);

	/* Setup the endian bits */
	reg = brcm_usb_पढ़ोl(USB_CTRL_REG(ctrl, SETUP));
	reg &= ~USB_CTRL_SETUP_ENDIAN_BITS;
	reg |= USB_CTRL_MASK_FAMILY(params, SETUP, ENDIAN);
	brcm_usb_ग_लिखोl(reg, USB_CTRL_REG(ctrl, SETUP));

	अगर (params->selected_family == BRCM_FAMILY_7271A0)
		/* Enable LS keep alive fix क्रम certain keyboards */
		USB_CTRL_SET(ctrl, OBRIDGE, LS_KEEP_ALIVE);

	अगर (params->family_id == 0x72550000) अणु
		/*
		 * Make the burst size 512 bytes to fix a hardware bug
		 * on the 7255a0. See HW7255-24.
		 */
		reg = brcm_usb_पढ़ोl(USB_CTRL_REG(ctrl, EBRIDGE));
		reg &= ~USB_CTRL_MASK(EBRIDGE, EBR_SCB_SIZE);
		reg |= 0x800;
		brcm_usb_ग_लिखोl(reg, USB_CTRL_REG(ctrl, EBRIDGE));
	पूर्ण
पूर्ण

अटल व्योम usb_init_xhci(काष्ठा brcm_usb_init_params *params)
अणु
	व्योम __iomem *ctrl = params->regs[BRCM_REGS_CTRL];

	USB_CTRL_UNSET(ctrl, USB30_PCTL, PHY3_IDDQ_OVERRIDE);
	/* 1 millisecond - क्रम USB घड़ीs to settle करोwn */
	usleep_range(1000, 2000);

	अगर (BRCM_ID(params->family_id) == 0x7366) अणु
		/*
		 * The PHY3_SOFT_RESETB bits शेष to the wrong state.
		 */
		USB_CTRL_SET(ctrl, USB30_PCTL, PHY3_SOFT_RESETB);
		USB_CTRL_SET(ctrl, USB30_PCTL, PHY3_SOFT_RESETB_P1);
	पूर्ण

	/*
	 * Kick start USB3 PHY
	 * Make sure it's low to insure a rising edge.
	 */
	USB_CTRL_UNSET(ctrl, USB30_CTL1, PHY3_PLL_SEQ_START);
	USB_CTRL_SET(ctrl, USB30_CTL1, PHY3_PLL_SEQ_START);

	brcmusb_usb3_phy_workarounds(params);
	brcmusb_xhci_soft_reset(params, 0);
	brcmusb_usb3_otp_fix(params);
पूर्ण

अटल व्योम usb_uninit_common(काष्ठा brcm_usb_init_params *params)
अणु
	अगर (USB_CTRL_MASK_FAMILY(params, USB_PM, USB_PWRDN))
		USB_CTRL_SET_FAMILY(params, USB_PM, USB_PWRDN);

	अगर (USB_CTRL_MASK_FAMILY(params, PLL_CTL, PLL_IDDQ_PWRDN))
		USB_CTRL_SET_FAMILY(params, PLL_CTL, PLL_IDDQ_PWRDN);
	अगर (params->wake_enabled)
		usb_wake_enable(params, true);
पूर्ण

अटल व्योम usb_uninit_eohci(काष्ठा brcm_usb_init_params *params)
अणु
पूर्ण

अटल व्योम usb_uninit_xhci(काष्ठा brcm_usb_init_params *params)
अणु
	brcmusb_xhci_soft_reset(params, 1);
	USB_CTRL_SET(params->regs[BRCM_REGS_CTRL], USB30_PCTL,
		     PHY3_IDDQ_OVERRIDE);
पूर्ण

अटल पूर्णांक usb_get_dual_select(काष्ठा brcm_usb_init_params *params)
अणु
	व्योम __iomem *ctrl = params->regs[BRCM_REGS_CTRL];
	u32 reg = 0;

	pr_debug("%s\n", __func__);
	अगर (USB_CTRL_MASK_FAMILY(params, USB_DEVICE_CTL1, PORT_MODE)) अणु
		reg = brcm_usb_पढ़ोl(USB_CTRL_REG(ctrl, USB_DEVICE_CTL1));
		reg &= USB_CTRL_MASK_FAMILY(params, USB_DEVICE_CTL1,
					PORT_MODE);
	पूर्ण
	वापस reg;
पूर्ण

अटल व्योम usb_set_dual_select(काष्ठा brcm_usb_init_params *params, पूर्णांक mode)
अणु
	व्योम __iomem *ctrl = params->regs[BRCM_REGS_CTRL];
	u32 reg;

	pr_debug("%s\n", __func__);

	अगर (USB_CTRL_MASK_FAMILY(params, USB_DEVICE_CTL1, PORT_MODE)) अणु
		reg = brcm_usb_पढ़ोl(USB_CTRL_REG(ctrl, USB_DEVICE_CTL1));
		reg &= ~USB_CTRL_MASK_FAMILY(params, USB_DEVICE_CTL1,
					PORT_MODE);
		reg |= mode;
		brcm_usb_ग_लिखोl(reg, USB_CTRL_REG(ctrl, USB_DEVICE_CTL1));
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा brcm_usb_init_ops bcm7445_ops = अणु
	.init_ipp = usb_init_ipp,
	.init_common = usb_init_common,
	.init_eohci = usb_init_eohci,
	.init_xhci = usb_init_xhci,
	.uninit_common = usb_uninit_common,
	.uninit_eohci = usb_uninit_eohci,
	.uninit_xhci = usb_uninit_xhci,
	.get_dual_select = usb_get_dual_select,
	.set_dual_select = usb_set_dual_select,
पूर्ण;

व्योम brcm_usb_dvr_init_7445(काष्ठा brcm_usb_init_params *params)
अणु
	पूर्णांक fam;

	pr_debug("%s\n", __func__);

	fam = get_family_type(params);
	params->selected_family = fam;
	params->usb_reg_bits_map =
		&usb_reg_bits_map_table[fam][0];
	params->family_name = family_names[fam];
	params->ops = &bcm7445_ops;
पूर्ण
