<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Freescale 83xx USB SOC setup code
 *
 * Copyright (C) 2007 Freescale Semiconductor, Inc.
 * Author: Li Yang
 */


#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/of.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <sysdev/fsl_soc.h>

#समावेश "mpc83xx.h"


#अगर_घोषित CONFIG_PPC_MPC834x
पूर्णांक mpc834x_usb_cfg(व्योम)
अणु
	अचिन्हित दीर्घ sccr, sicrl, sicrh;
	व्योम __iomem *immap;
	काष्ठा device_node *np = शून्य;
	पूर्णांक port0_is_dr = 0, port1_is_dr = 0;
	स्थिर व्योम *prop, *dr_mode;

	immap = ioremap(get_immrbase(), 0x1000);
	अगर (!immap)
		वापस -ENOMEM;

	/* Read रेजिस्टरs */
	/* Note: DR and MPH must use the same घड़ी setting in SCCR */
	sccr = in_be32(immap + MPC83XX_SCCR_OFFS) & ~MPC83XX_SCCR_USB_MASK;
	sicrl = in_be32(immap + MPC83XX_SICRL_OFFS) & ~MPC834X_SICRL_USB_MASK;
	sicrh = in_be32(immap + MPC83XX_SICRH_OFFS) & ~MPC834X_SICRH_USB_UTMI;

	np = of_find_compatible_node(शून्य, शून्य, "fsl-usb2-dr");
	अगर (np) अणु
		sccr |= MPC83XX_SCCR_USB_DRCM_11;  /* 1:3 */

		prop = of_get_property(np, "phy_type", शून्य);
		port1_is_dr = 1;
		अगर (prop && (!म_भेद(prop, "utmi") ||
					!म_भेद(prop, "utmi_wide"))) अणु
			sicrl |= MPC834X_SICRL_USB0 | MPC834X_SICRL_USB1;
			sicrh |= MPC834X_SICRH_USB_UTMI;
			port0_is_dr = 1;
		पूर्ण अन्यथा अगर (prop && !म_भेद(prop, "serial")) अणु
			dr_mode = of_get_property(np, "dr_mode", शून्य);
			अगर (dr_mode && !म_भेद(dr_mode, "otg")) अणु
				sicrl |= MPC834X_SICRL_USB0 | MPC834X_SICRL_USB1;
				port0_is_dr = 1;
			पूर्ण अन्यथा अणु
				sicrl |= MPC834X_SICRL_USB1;
			पूर्ण
		पूर्ण अन्यथा अगर (prop && !म_भेद(prop, "ulpi")) अणु
			sicrl |= MPC834X_SICRL_USB1;
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_WARNING "834x USB PHY type not supported\n");
		पूर्ण
		of_node_put(np);
	पूर्ण
	np = of_find_compatible_node(शून्य, शून्य, "fsl-usb2-mph");
	अगर (np) अणु
		sccr |= MPC83XX_SCCR_USB_MPHCM_11; /* 1:3 */

		prop = of_get_property(np, "port0", शून्य);
		अगर (prop) अणु
			अगर (port0_is_dr)
				prपूर्णांकk(KERN_WARNING
					"834x USB port0 can't be used by both DR and MPH!\n");
			sicrl &= ~MPC834X_SICRL_USB0;
		पूर्ण
		prop = of_get_property(np, "port1", शून्य);
		अगर (prop) अणु
			अगर (port1_is_dr)
				prपूर्णांकk(KERN_WARNING
					"834x USB port1 can't be used by both DR and MPH!\n");
			sicrl &= ~MPC834X_SICRL_USB1;
		पूर्ण
		of_node_put(np);
	पूर्ण

	/* Write back */
	out_be32(immap + MPC83XX_SCCR_OFFS, sccr);
	out_be32(immap + MPC83XX_SICRL_OFFS, sicrl);
	out_be32(immap + MPC83XX_SICRH_OFFS, sicrh);

	iounmap(immap);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_MPC834x */

#अगर_घोषित CONFIG_PPC_MPC831x
पूर्णांक mpc831x_usb_cfg(व्योम)
अणु
	u32 temp;
	व्योम __iomem *immap, *usb_regs;
	काष्ठा device_node *np = शून्य;
	काष्ठा device_node *immr_node = शून्य;
	स्थिर व्योम *prop;
	काष्ठा resource res;
	पूर्णांक ret = 0;
#अगर_घोषित CONFIG_USB_OTG
	स्थिर व्योम *dr_mode;
#पूर्ण_अगर

	np = of_find_compatible_node(शून्य, शून्य, "fsl-usb2-dr");
	अगर (!np)
		वापस -ENODEV;
	prop = of_get_property(np, "phy_type", शून्य);

	/* Map IMMR space क्रम pin and घड़ी settings */
	immap = ioremap(get_immrbase(), 0x1000);
	अगर (!immap) अणु
		of_node_put(np);
		वापस -ENOMEM;
	पूर्ण

	/* Configure घड़ी */
	immr_node = of_get_parent(np);
	अगर (immr_node && (of_device_is_compatible(immr_node, "fsl,mpc8315-immr") ||
			of_device_is_compatible(immr_node, "fsl,mpc8308-immr")))
		clrsetbits_be32(immap + MPC83XX_SCCR_OFFS,
		                MPC8315_SCCR_USB_MASK,
		                MPC8315_SCCR_USB_DRCM_01);
	अन्यथा
		clrsetbits_be32(immap + MPC83XX_SCCR_OFFS,
		                MPC83XX_SCCR_USB_MASK,
		                MPC83XX_SCCR_USB_DRCM_11);

	/* Configure pin mux क्रम ULPI.  There is no pin mux क्रम UTMI */
	अगर (prop && !म_भेद(prop, "ulpi")) अणु
		अगर (of_device_is_compatible(immr_node, "fsl,mpc8308-immr")) अणु
			clrsetbits_be32(immap + MPC83XX_SICRH_OFFS,
					MPC8308_SICRH_USB_MASK,
					MPC8308_SICRH_USB_ULPI);
		पूर्ण अन्यथा अगर (of_device_is_compatible(immr_node, "fsl,mpc8315-immr")) अणु
			clrsetbits_be32(immap + MPC83XX_SICRL_OFFS,
					MPC8315_SICRL_USB_MASK,
					MPC8315_SICRL_USB_ULPI);
			clrsetbits_be32(immap + MPC83XX_SICRH_OFFS,
					MPC8315_SICRH_USB_MASK,
					MPC8315_SICRH_USB_ULPI);
		पूर्ण अन्यथा अणु
			clrsetbits_be32(immap + MPC83XX_SICRL_OFFS,
					MPC831X_SICRL_USB_MASK,
					MPC831X_SICRL_USB_ULPI);
			clrsetbits_be32(immap + MPC83XX_SICRH_OFFS,
					MPC831X_SICRH_USB_MASK,
					MPC831X_SICRH_USB_ULPI);
		पूर्ण
	पूर्ण

	iounmap(immap);

	of_node_put(immr_node);

	/* Map USB SOC space */
	ret = of_address_to_resource(np, 0, &res);
	अगर (ret) अणु
		of_node_put(np);
		वापस ret;
	पूर्ण
	usb_regs = ioremap(res.start, resource_size(&res));

	/* Using on-chip PHY */
	अगर (prop && (!म_भेद(prop, "utmi_wide") ||
		     !म_भेद(prop, "utmi"))) अणु
		u32 refsel;

		अगर (of_device_is_compatible(immr_node, "fsl,mpc8308-immr"))
			जाओ out;

		अगर (of_device_is_compatible(immr_node, "fsl,mpc8315-immr"))
			refsel = CONTROL_REFSEL_24MHZ;
		अन्यथा
			refsel = CONTROL_REFSEL_48MHZ;
		/* Set UTMI_PHY_EN and REFSEL */
		out_be32(usb_regs + FSL_USB2_CONTROL_OFFS,
				CONTROL_UTMI_PHY_EN | refsel);
	/* Using बाह्यal UPLI PHY */
	पूर्ण अन्यथा अगर (prop && !म_भेद(prop, "ulpi")) अणु
		/* Set PHY_CLK_SEL to ULPI */
		temp = CONTROL_PHY_CLK_SEL_ULPI;
#अगर_घोषित CONFIG_USB_OTG
		/* Set OTG_PORT */
		अगर (!of_device_is_compatible(immr_node, "fsl,mpc8308-immr")) अणु
			dr_mode = of_get_property(np, "dr_mode", शून्य);
			अगर (dr_mode && !म_भेद(dr_mode, "otg"))
				temp |= CONTROL_OTG_PORT;
		पूर्ण
#पूर्ण_अगर /* CONFIG_USB_OTG */
		out_be32(usb_regs + FSL_USB2_CONTROL_OFFS, temp);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_WARNING "831x USB PHY type not supported\n");
		ret = -EINVAL;
	पूर्ण

out:
	iounmap(usb_regs);
	of_node_put(np);
	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_MPC831x */

#अगर_घोषित CONFIG_PPC_MPC837x
पूर्णांक mpc837x_usb_cfg(व्योम)
अणु
	व्योम __iomem *immap;
	काष्ठा device_node *np = शून्य;
	स्थिर व्योम *prop;
	पूर्णांक ret = 0;

	np = of_find_compatible_node(शून्य, शून्य, "fsl-usb2-dr");
	अगर (!np || !of_device_is_available(np)) अणु
		of_node_put(np);
		वापस -ENODEV;
	पूर्ण
	prop = of_get_property(np, "phy_type", शून्य);

	अगर (!prop || (म_भेद(prop, "ulpi") && म_भेद(prop, "serial"))) अणु
		prपूर्णांकk(KERN_WARNING "837x USB PHY type not supported\n");
		of_node_put(np);
		वापस -EINVAL;
	पूर्ण

	/* Map IMMR space क्रम pin and घड़ी settings */
	immap = ioremap(get_immrbase(), 0x1000);
	अगर (!immap) अणु
		of_node_put(np);
		वापस -ENOMEM;
	पूर्ण

	/* Configure घड़ी */
	clrsetbits_be32(immap + MPC83XX_SCCR_OFFS, MPC837X_SCCR_USB_DRCM_11,
			MPC837X_SCCR_USB_DRCM_11);

	/* Configure pin mux क्रम ULPI/serial */
	clrsetbits_be32(immap + MPC83XX_SICRL_OFFS, MPC837X_SICRL_USB_MASK,
			MPC837X_SICRL_USB_ULPI);

	iounmap(immap);
	of_node_put(np);
	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_MPC837x */
