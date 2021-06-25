<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * T1042 platक्रमm DIU operation
 *
 * Copyright 2014 Freescale Semiconductor Inc.
 */

#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#समावेश <sysdev/fsl_soc.h>

/*DIU Pixel ClockCR offset in scfg*/
#घोषणा CCSR_SCFG_PIXCLKCR      0x28

/* DIU Pixel Clock bits of the PIXCLKCR */
#घोषणा PIXCLKCR_PXCKEN		0x80000000
#घोषणा PIXCLKCR_PXCKINV	0x40000000
#घोषणा PIXCLKCR_PXCKDLY	0x0000FF00
#घोषणा PIXCLKCR_PXCLK_MASK	0x00FF0000

/* Some CPLD रेजिस्टर definitions */
#घोषणा CPLD_DIUCSR		0x16
#घोषणा CPLD_DIUCSR_DVIEN	0x80
#घोषणा CPLD_DIUCSR_BACKLIGHT	0x0f

काष्ठा device_node *cpld_node;

/**
 * t1042rdb_set_monitor_port: चयन the output to a dअगरferent monitor port
 */
अटल व्योम t1042rdb_set_monitor_port(क्रमागत fsl_diu_monitor_port port)
अणु
	व्योम __iomem *cpld_base;

	cpld_base = of_iomap(cpld_node, 0);
	अगर (!cpld_base) अणु
		pr_err("%s: Could not map cpld registers\n", __func__);
		जाओ निकास;
	पूर्ण

	चयन (port) अणु
	हाल FSL_DIU_PORT_DVI:
		/* Enable the DVI(HDMI) port, disable the DFP and
		 * the backlight
		 */
		clrbits8(cpld_base + CPLD_DIUCSR, CPLD_DIUCSR_DVIEN);
		अवरोध;
	हाल FSL_DIU_PORT_LVDS:
		/*
		 * LVDS also needs backlight enabled, otherwise the display
		 * will be blank.
		 */
		/* Enable the DFP port, disable the DVI*/
		setbits8(cpld_base + CPLD_DIUCSR, 0x01 << 8);
		setbits8(cpld_base + CPLD_DIUCSR, 0x01 << 4);
		setbits8(cpld_base + CPLD_DIUCSR, CPLD_DIUCSR_BACKLIGHT);
		अवरोध;
	शेष:
		pr_err("%s: Unsupported monitor port %i\n", __func__, port);
	पूर्ण

	iounmap(cpld_base);
निकास:
	of_node_put(cpld_node);
पूर्ण

/**
 * t1042rdb_set_pixel_घड़ी: program the DIU's घड़ी
 * @pixघड़ी: pixel घड़ी in ps (pico seconds)
 */
अटल व्योम t1042rdb_set_pixel_घड़ी(अचिन्हित पूर्णांक pixघड़ी)
अणु
	काष्ठा device_node *scfg_np;
	व्योम __iomem *scfg;
	अचिन्हित दीर्घ freq;
	u64 temp;
	u32 pxclk;

	scfg_np = of_find_compatible_node(शून्य, शून्य, "fsl,t1040-scfg");
	अगर (!scfg_np) अणु
		pr_err("%s: Missing scfg node. Can not display video.\n",
		       __func__);
		वापस;
	पूर्ण

	scfg = of_iomap(scfg_np, 0);
	of_node_put(scfg_np);
	अगर (!scfg) अणु
		pr_err("%s: Could not map device. Can not display video.\n",
		       __func__);
		वापस;
	पूर्ण

	/* Convert pixघड़ी पूर्णांकo frequency */
	temp = 1000000000000ULL;
	करो_भाग(temp, pixघड़ी);
	freq = temp;

	/*
	 * 'pxclk' is the ratio of the platक्रमm घड़ी to the pixel घड़ी.
	 * This number is programmed पूर्णांकo the PIXCLKCR रेजिस्टर, and the valid
	 * range of values is 2-255.
	 */
	pxclk = DIV_ROUND_CLOSEST(fsl_get_sys_freq(), freq);
	pxclk = clamp_t(u32, pxclk, 2, 255);

	/* Disable the pixel घड़ी, and set it to non-inverted and no delay */
	clrbits32(scfg + CCSR_SCFG_PIXCLKCR,
		  PIXCLKCR_PXCKEN | PIXCLKCR_PXCKDLY | PIXCLKCR_PXCLK_MASK);

	/* Enable the घड़ी and set the pxclk */
	setbits32(scfg + CCSR_SCFG_PIXCLKCR, PIXCLKCR_PXCKEN | (pxclk << 16));

	iounmap(scfg);
पूर्ण

/**
 * t1042rdb_valid_monitor_port: set the monitor port क्रम sysfs
 */
अटल क्रमागत fsl_diu_monitor_port
t1042rdb_valid_monitor_port(क्रमागत fsl_diu_monitor_port port)
अणु
	चयन (port) अणु
	हाल FSL_DIU_PORT_DVI:
	हाल FSL_DIU_PORT_LVDS:
		वापस port;
	शेष:
		वापस FSL_DIU_PORT_DVI; /* Dual-link LVDS is not supported */
	पूर्ण
पूर्ण

अटल पूर्णांक __init t1042rdb_diu_init(व्योम)
अणु
	cpld_node = of_find_compatible_node(शून्य, शून्य, "fsl,t1042rdb-cpld");
	अगर (!cpld_node)
		वापस 0;

	diu_ops.set_monitor_port	= t1042rdb_set_monitor_port;
	diu_ops.set_pixel_घड़ी		= t1042rdb_set_pixel_घड़ी;
	diu_ops.valid_monitor_port	= t1042rdb_valid_monitor_port;

	वापस 0;
पूर्ण

early_initcall(t1042rdb_diu_init);

MODULE_LICENSE("GPL");
