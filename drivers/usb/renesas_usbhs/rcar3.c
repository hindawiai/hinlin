<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas USB driver R-Car Gen. 3 initialization and घातer control
 *
 * Copyright (C) 2016-2019 Renesas Electronics Corporation
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश "common.h"
#समावेश "rcar3.h"

#घोषणा LPSTS		0x102
#घोषणा UGCTRL		0x180	/* 32-bit रेजिस्टर */
#घोषणा UGCTRL2		0x184	/* 32-bit रेजिस्टर */
#घोषणा UGSTS		0x188	/* 32-bit रेजिस्टर */

/* Low Power Status रेजिस्टर (LPSTS) */
#घोषणा LPSTS_SUSPM	0x4000

/* R-Car D3 only: USB General control रेजिस्टर (UGCTRL) */
#घोषणा UGCTRL_PLLRESET		0x00000001
#घोषणा UGCTRL_CONNECT		0x00000004

/*
 * USB General control रेजिस्टर 2 (UGCTRL2)
 * Remarks: bit[31:11] and bit[9:6] should be 0
 */
#घोषणा UGCTRL2_RESERVED_3	0x00000001	/* bit[3:0] should be B'0001 */
#घोषणा UGCTRL2_USB0SEL_HSUSB	0x00000020
#घोषणा UGCTRL2_USB0SEL_OTG	0x00000030
#घोषणा UGCTRL2_VBUSSEL		0x00000400

/* R-Car D3 only: USB General status रेजिस्टर (UGSTS) */
#घोषणा UGSTS_LOCK		0x00000100

अटल व्योम usbhs_ग_लिखो32(काष्ठा usbhs_priv *priv, u32 reg, u32 data)
अणु
	ioग_लिखो32(data, priv->base + reg);
पूर्ण

अटल u32 usbhs_पढ़ो32(काष्ठा usbhs_priv *priv, u32 reg)
अणु
	वापस ioपढ़ो32(priv->base + reg);
पूर्ण

अटल व्योम usbhs_rcar3_set_ugctrl2(काष्ठा usbhs_priv *priv, u32 val)
अणु
	usbhs_ग_लिखो32(priv, UGCTRL2, val | UGCTRL2_RESERVED_3);
पूर्ण

अटल पूर्णांक usbhs_rcar3_घातer_ctrl(काष्ठा platक्रमm_device *pdev,
				व्योम __iomem *base, पूर्णांक enable)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pdev_to_priv(pdev);

	usbhs_rcar3_set_ugctrl2(priv, UGCTRL2_USB0SEL_OTG | UGCTRL2_VBUSSEL);

	अगर (enable) अणु
		usbhs_bset(priv, LPSTS, LPSTS_SUSPM, LPSTS_SUSPM);
		/* The controller on R-Car Gen3 needs to रुको up to 45 usec */
		usleep_range(45, 90);
	पूर्ण अन्यथा अणु
		usbhs_bset(priv, LPSTS, LPSTS_SUSPM, 0);
	पूर्ण

	वापस 0;
पूर्ण

/* R-Car D3 needs to release UGCTRL.PLLRESET */
अटल पूर्णांक usbhs_rcar3_घातer_and_pll_ctrl(काष्ठा platक्रमm_device *pdev,
					  व्योम __iomem *base, पूर्णांक enable)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pdev_to_priv(pdev);
	u32 val;
	पूर्णांक समयout = 1000;

	अगर (enable) अणु
		usbhs_ग_लिखो32(priv, UGCTRL, 0);	/* release PLLRESET */
		usbhs_rcar3_set_ugctrl2(priv,
					UGCTRL2_USB0SEL_OTG | UGCTRL2_VBUSSEL);

		usbhs_bset(priv, LPSTS, LPSTS_SUSPM, LPSTS_SUSPM);
		करो अणु
			val = usbhs_पढ़ो32(priv, UGSTS);
			udelay(1);
		पूर्ण जबतक (!(val & UGSTS_LOCK) && समयout--);
		usbhs_ग_लिखो32(priv, UGCTRL, UGCTRL_CONNECT);
	पूर्ण अन्यथा अणु
		usbhs_ग_लिखो32(priv, UGCTRL, 0);
		usbhs_bset(priv, LPSTS, LPSTS_SUSPM, 0);
		usbhs_ग_लिखो32(priv, UGCTRL, UGCTRL_PLLRESET);
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा renesas_usbhs_platक्रमm_info usbhs_rcar_gen3_plat_info = अणु
	.platक्रमm_callback = अणु
		.घातer_ctrl = usbhs_rcar3_घातer_ctrl,
		.get_id = usbhs_get_id_as_gadget,
	पूर्ण,
	.driver_param = अणु
		.has_usb_dmac = 1,
		.multi_clks = 1,
		.has_new_pipe_configs = 1,
	पूर्ण,
पूर्ण;

स्थिर काष्ठा renesas_usbhs_platक्रमm_info usbhs_rcar_gen3_with_pll_plat_info = अणु
	.platक्रमm_callback = अणु
		.घातer_ctrl = usbhs_rcar3_घातer_and_pll_ctrl,
		.get_id = usbhs_get_id_as_gadget,
	पूर्ण,
	.driver_param = अणु
		.has_usb_dmac = 1,
		.multi_clks = 1,
		.has_new_pipe_configs = 1,
	पूर्ण,
पूर्ण;
