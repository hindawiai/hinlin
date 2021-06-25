<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Renesas USB driver RZ/A initialization and घातer control
 *
 * Copyright (C) 2018 Chris Bअक्रमt
 * Copyright (C) 2018-2019 Renesas Electronics Corporation
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_device.h>
#समावेश "common.h"
#समावेश "rza.h"

अटल पूर्णांक usbhs_rza1_hardware_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pdev_to_priv(pdev);
	काष्ठा device_node *usb_x1_clk, *extal_clk;
	u32 freq_usb = 0, freq_extal = 0;

	/* Input Clock Selection (NOTE: ch0 controls both ch0 and ch1) */
	usb_x1_clk = of_find_node_by_name(शून्य, "usb_x1");
	extal_clk = of_find_node_by_name(शून्य, "extal");
	of_property_पढ़ो_u32(usb_x1_clk, "clock-frequency", &freq_usb);
	of_property_पढ़ो_u32(extal_clk, "clock-frequency", &freq_extal);
	अगर (freq_usb == 0) अणु
		अगर (freq_extal == 12000000) अणु
			/* Select 12MHz XTAL */
			usbhs_bset(priv, SYSCFG, UCKSEL, UCKSEL);
		पूर्ण अन्यथा अणु
			dev_err(usbhs_priv_to_dev(priv), "A 48MHz USB clock or 12MHz main clock is required.\n");
			वापस -EIO;
		पूर्ण
	पूर्ण

	/* Enable USB PLL (NOTE: ch0 controls both ch0 and ch1) */
	usbhs_bset(priv, SYSCFG, UPLLE, UPLLE);
	usleep_range(1000, 2000);
	usbhs_bset(priv, SUSPMODE, SUSPM, SUSPM);

	वापस 0;
पूर्ण

स्थिर काष्ठा renesas_usbhs_platक्रमm_info usbhs_rza1_plat_info = अणु
	.platक्रमm_callback = अणु
		.hardware_init = usbhs_rza1_hardware_init,
		.get_id = usbhs_get_id_as_gadget,
	पूर्ण,
	.driver_param = अणु
		.has_new_pipe_configs = 1,
	पूर्ण,
पूर्ण;
