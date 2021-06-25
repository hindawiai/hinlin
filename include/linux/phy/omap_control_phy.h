<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * omap_control_phy.h - Header file क्रम the PHY part of control module.
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com
 * Author: Kishon Vijay Abraham I <kishon@ti.com>
 */

#अगर_अघोषित __OMAP_CONTROL_PHY_H__
#घोषणा __OMAP_CONTROL_PHY_H__

क्रमागत omap_control_phy_type अणु
	OMAP_CTRL_TYPE_OTGHS = 1,	/* Mailbox OTGHS_CONTROL */
	OMAP_CTRL_TYPE_USB2,	/* USB2_PHY, घातer करोwn in CONTROL_DEV_CONF */
	OMAP_CTRL_TYPE_PIPE3,	/* PIPE3 PHY, DPLL & seperate Rx/Tx घातer */
	OMAP_CTRL_TYPE_PCIE,	/* RX TX control of ACSPCIE */
	OMAP_CTRL_TYPE_DRA7USB2, /* USB2 PHY, घातer and घातer_aux e.g. DRA7 */
	OMAP_CTRL_TYPE_AM437USB2, /* USB2 PHY, घातer e.g. AM437x */
पूर्ण;

काष्ठा omap_control_phy अणु
	काष्ठा device *dev;

	u32 __iomem *otghs_control;
	u32 __iomem *घातer;
	u32 __iomem *घातer_aux;
	u32 __iomem *pcie_pcs;

	काष्ठा clk *sys_clk;

	क्रमागत omap_control_phy_type type;
पूर्ण;

क्रमागत omap_control_usb_mode अणु
	USB_MODE_UNDEFINED = 0,
	USB_MODE_HOST,
	USB_MODE_DEVICE,
	USB_MODE_DISCONNECT,
पूर्ण;

#घोषणा	OMAP_CTRL_DEV_PHY_PD		BIT(0)

#घोषणा	OMAP_CTRL_DEV_AVALID		BIT(0)
#घोषणा	OMAP_CTRL_DEV_BVALID		BIT(1)
#घोषणा	OMAP_CTRL_DEV_VBUSVALID		BIT(2)
#घोषणा	OMAP_CTRL_DEV_SESSEND		BIT(3)
#घोषणा	OMAP_CTRL_DEV_IDDIG		BIT(4)

#घोषणा	OMAP_CTRL_PIPE3_PHY_PWRCTL_CLK_CMD_MASK		0x003FC000
#घोषणा	OMAP_CTRL_PIPE3_PHY_PWRCTL_CLK_CMD_SHIFT	0xE

#घोषणा	OMAP_CTRL_PIPE3_PHY_PWRCTL_CLK_FREQ_MASK	0xFFC00000
#घोषणा	OMAP_CTRL_PIPE3_PHY_PWRCTL_CLK_FREQ_SHIFT	0x16

#घोषणा	OMAP_CTRL_PIPE3_PHY_TX_RX_POWERON	0x3
#घोषणा	OMAP_CTRL_PIPE3_PHY_TX_RX_POWEROFF	0x0

#घोषणा	OMAP_CTRL_PCIE_PCS_MASK			0xff
#घोषणा	OMAP_CTRL_PCIE_PCS_DELAY_COUNT_SHIFT	16

#घोषणा OMAP_CTRL_USB2_PHY_PD		BIT(28)

#घोषणा AM437X_CTRL_USB2_PHY_PD		BIT(0)
#घोषणा AM437X_CTRL_USB2_OTG_PD		BIT(1)
#घोषणा AM437X_CTRL_USB2_OTGVDET_EN	BIT(19)
#घोषणा AM437X_CTRL_USB2_OTGSESSEND_EN	BIT(20)

#अगर IS_ENABLED(CONFIG_OMAP_CONTROL_PHY)
व्योम omap_control_phy_घातer(काष्ठा device *dev, पूर्णांक on);
व्योम omap_control_usb_set_mode(काष्ठा device *dev,
			       क्रमागत omap_control_usb_mode mode);
व्योम omap_control_pcie_pcs(काष्ठा device *dev, u8 delay);
#अन्यथा

अटल अंतरभूत व्योम omap_control_phy_घातer(काष्ठा device *dev, पूर्णांक on)
अणु
पूर्ण

अटल अंतरभूत व्योम omap_control_usb_set_mode(काष्ठा device *dev,
	क्रमागत omap_control_usb_mode mode)
अणु
पूर्ण

अटल अंतरभूत व्योम omap_control_pcie_pcs(काष्ठा device *dev, u8 delay)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर	/* __OMAP_CONTROL_PHY_H__ */
