<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * xHCI host controller driver क्रम R-Car SoCs
 *
 * Copyright (C) 2014 Renesas Electronics Corporation
 */

#समावेश <linux/firmware.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/usb/phy.h>
#समावेश <linux/sys_soc.h>

#समावेश "xhci.h"
#समावेश "xhci-plat.h"
#समावेश "xhci-rcar.h"

/*
* - The V3 firmware is क्रम almost all R-Car Gen3 (except r8a7795 ES1.x)
* - The V2 firmware is क्रम r8a7795 ES1.x.
* - The V2 firmware is possible to use on R-Car Gen2. However, the V2 causes
*   perक्रमmance degradation. So, this driver जारीs to use the V1 अगर R-Car
*   Gen2.
* - The V1 firmware is impossible to use on R-Car Gen3.
*/
MODULE_FIRMWARE(XHCI_RCAR_FIRMWARE_NAME_V1);
MODULE_FIRMWARE(XHCI_RCAR_FIRMWARE_NAME_V2);
MODULE_FIRMWARE(XHCI_RCAR_FIRMWARE_NAME_V3);

/*** Register Offset ***/
#घोषणा RCAR_USB3_AXH_STA	0x104	/* AXI Host Control Status */
#घोषणा RCAR_USB3_INT_ENA	0x224	/* Interrupt Enable */
#घोषणा RCAR_USB3_DL_CTRL	0x250	/* FW Download Control & Status */
#घोषणा RCAR_USB3_FW_DATA0	0x258	/* FW Data0 */

#घोषणा RCAR_USB3_LCLK		0xa44	/* LCLK Select */
#घोषणा RCAR_USB3_CONF1		0xa48	/* USB3.0 Configuration1 */
#घोषणा RCAR_USB3_CONF2		0xa5c	/* USB3.0 Configuration2 */
#घोषणा RCAR_USB3_CONF3		0xaa8	/* USB3.0 Configuration3 */
#घोषणा RCAR_USB3_RX_POL	0xab0	/* USB3.0 RX Polarity */
#घोषणा RCAR_USB3_TX_POL	0xab8	/* USB3.0 TX Polarity */

/*** Register Settings ***/
/* AXI Host Control Status */
#घोषणा RCAR_USB3_AXH_STA_B3_PLL_ACTIVE		0x00010000
#घोषणा RCAR_USB3_AXH_STA_B2_PLL_ACTIVE		0x00000001
#घोषणा RCAR_USB3_AXH_STA_PLL_ACTIVE_MASK (RCAR_USB3_AXH_STA_B3_PLL_ACTIVE | \
					   RCAR_USB3_AXH_STA_B2_PLL_ACTIVE)

/* Interrupt Enable */
#घोषणा RCAR_USB3_INT_XHC_ENA	0x00000001
#घोषणा RCAR_USB3_INT_PME_ENA	0x00000002
#घोषणा RCAR_USB3_INT_HSE_ENA	0x00000004
#घोषणा RCAR_USB3_INT_ENA_VAL	(RCAR_USB3_INT_XHC_ENA | \
				RCAR_USB3_INT_PME_ENA | RCAR_USB3_INT_HSE_ENA)

/* FW Download Control & Status */
#घोषणा RCAR_USB3_DL_CTRL_ENABLE	0x00000001
#घोषणा RCAR_USB3_DL_CTRL_FW_SUCCESS	0x00000010
#घोषणा RCAR_USB3_DL_CTRL_FW_SET_DATA0	0x00000100

/* LCLK Select */
#घोषणा RCAR_USB3_LCLK_ENA_VAL	0x01030001

/* USB3.0 Configuration */
#घोषणा RCAR_USB3_CONF1_VAL	0x00030204
#घोषणा RCAR_USB3_CONF2_VAL	0x00030300
#घोषणा RCAR_USB3_CONF3_VAL	0x13802007

/* USB3.0 Polarity */
#घोषणा RCAR_USB3_RX_POL_VAL	BIT(21)
#घोषणा RCAR_USB3_TX_POL_VAL	BIT(4)

/* For soc_device_attribute */
#घोषणा RCAR_XHCI_FIRMWARE_V2   BIT(0) /* FIRMWARE V2 */
#घोषणा RCAR_XHCI_FIRMWARE_V3   BIT(1) /* FIRMWARE V3 */

अटल स्थिर काष्ठा soc_device_attribute rcar_quirks_match[]  = अणु
	अणु
		.soc_id = "r8a7795", .revision = "ES1.*",
		.data = (व्योम *)RCAR_XHCI_FIRMWARE_V2,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल व्योम xhci_rcar_start_gen2(काष्ठा usb_hcd *hcd)
अणु
	/* LCLK Select */
	ग_लिखोl(RCAR_USB3_LCLK_ENA_VAL, hcd->regs + RCAR_USB3_LCLK);
	/* USB3.0 Configuration */
	ग_लिखोl(RCAR_USB3_CONF1_VAL, hcd->regs + RCAR_USB3_CONF1);
	ग_लिखोl(RCAR_USB3_CONF2_VAL, hcd->regs + RCAR_USB3_CONF2);
	ग_लिखोl(RCAR_USB3_CONF3_VAL, hcd->regs + RCAR_USB3_CONF3);
	/* USB3.0 Polarity */
	ग_लिखोl(RCAR_USB3_RX_POL_VAL, hcd->regs + RCAR_USB3_RX_POL);
	ग_लिखोl(RCAR_USB3_TX_POL_VAL, hcd->regs + RCAR_USB3_TX_POL);
पूर्ण

अटल पूर्णांक xhci_rcar_is_gen2(काष्ठा device *dev)
अणु
	काष्ठा device_node *node = dev->of_node;

	वापस of_device_is_compatible(node, "renesas,xhci-r8a7790") ||
		of_device_is_compatible(node, "renesas,xhci-r8a7791") ||
		of_device_is_compatible(node, "renesas,xhci-r8a7793") ||
		of_device_is_compatible(node, "renesas,rcar-gen2-xhci");
पूर्ण

व्योम xhci_rcar_start(काष्ठा usb_hcd *hcd)
अणु
	u32 temp;

	अगर (hcd->regs != शून्य) अणु
		/* Interrupt Enable */
		temp = पढ़ोl(hcd->regs + RCAR_USB3_INT_ENA);
		temp |= RCAR_USB3_INT_ENA_VAL;
		ग_लिखोl(temp, hcd->regs + RCAR_USB3_INT_ENA);
		अगर (xhci_rcar_is_gen2(hcd->self.controller))
			xhci_rcar_start_gen2(hcd);
	पूर्ण
पूर्ण

अटल पूर्णांक xhci_rcar_करोwnload_firmware(काष्ठा usb_hcd *hcd)
अणु
	काष्ठा device *dev = hcd->self.controller;
	व्योम __iomem *regs = hcd->regs;
	काष्ठा xhci_plat_priv *priv = hcd_to_xhci_priv(hcd);
	स्थिर काष्ठा firmware *fw;
	पूर्णांक retval, index, j;
	u32 data, val, temp;
	u32 quirks = 0;
	स्थिर काष्ठा soc_device_attribute *attr;
	स्थिर अक्षर *firmware_name;

	attr = soc_device_match(rcar_quirks_match);
	अगर (attr)
		quirks = (uपूर्णांकptr_t)attr->data;

	अगर (quirks & RCAR_XHCI_FIRMWARE_V2)
		firmware_name = XHCI_RCAR_FIRMWARE_NAME_V2;
	अन्यथा अगर (quirks & RCAR_XHCI_FIRMWARE_V3)
		firmware_name = XHCI_RCAR_FIRMWARE_NAME_V3;
	अन्यथा
		firmware_name = priv->firmware_name;

	/* request R-Car USB3.0 firmware */
	retval = request_firmware(&fw, firmware_name, dev);
	अगर (retval)
		वापस retval;

	/* करोwnload R-Car USB3.0 firmware */
	temp = पढ़ोl(regs + RCAR_USB3_DL_CTRL);
	temp |= RCAR_USB3_DL_CTRL_ENABLE;
	ग_लिखोl(temp, regs + RCAR_USB3_DL_CTRL);

	क्रम (index = 0; index < fw->size; index += 4) अणु
		/* to aव्योम पढ़ोing beyond the end of the buffer */
		क्रम (data = 0, j = 3; j >= 0; j--) अणु
			अगर ((j + index) < fw->size)
				data |= fw->data[index + j] << (8 * j);
		पूर्ण
		ग_लिखोl(data, regs + RCAR_USB3_FW_DATA0);
		temp = पढ़ोl(regs + RCAR_USB3_DL_CTRL);
		temp |= RCAR_USB3_DL_CTRL_FW_SET_DATA0;
		ग_लिखोl(temp, regs + RCAR_USB3_DL_CTRL);

		retval = पढ़ोl_poll_समयout_atomic(regs + RCAR_USB3_DL_CTRL,
				val, !(val & RCAR_USB3_DL_CTRL_FW_SET_DATA0),
				1, 10000);
		अगर (retval < 0)
			अवरोध;
	पूर्ण

	temp = पढ़ोl(regs + RCAR_USB3_DL_CTRL);
	temp &= ~RCAR_USB3_DL_CTRL_ENABLE;
	ग_लिखोl(temp, regs + RCAR_USB3_DL_CTRL);

	retval = पढ़ोl_poll_समयout_atomic((regs + RCAR_USB3_DL_CTRL),
			val, val & RCAR_USB3_DL_CTRL_FW_SUCCESS, 1, 10000);

	release_firmware(fw);

	वापस retval;
पूर्ण

अटल bool xhci_rcar_रुको_क्रम_pll_active(काष्ठा usb_hcd *hcd)
अणु
	पूर्णांक retval;
	u32 val, mask = RCAR_USB3_AXH_STA_PLL_ACTIVE_MASK;

	retval = पढ़ोl_poll_समयout_atomic(hcd->regs + RCAR_USB3_AXH_STA,
			val, (val & mask) == mask, 1, 1000);
	वापस !retval;
पूर्ण

/* This function needs to initialize a "phy" of usb beक्रमe */
पूर्णांक xhci_rcar_init_quirk(काष्ठा usb_hcd *hcd)
अणु
	/* If hcd->regs is शून्य, we करोn't just call the following function */
	अगर (!hcd->regs)
		वापस 0;

	अगर (!xhci_rcar_रुको_क्रम_pll_active(hcd))
		वापस -ETIMEDOUT;

	वापस xhci_rcar_करोwnload_firmware(hcd);
पूर्ण

पूर्णांक xhci_rcar_resume_quirk(काष्ठा usb_hcd *hcd)
अणु
	पूर्णांक ret;

	ret = xhci_rcar_करोwnload_firmware(hcd);
	अगर (!ret)
		xhci_rcar_start(hcd);

	वापस ret;
पूर्ण
