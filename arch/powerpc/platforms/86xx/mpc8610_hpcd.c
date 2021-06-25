<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MPC8610 HPCD board specअगरic routines
 *
 * Initial author: Xianghua Xiao <x.xiao@मुक्तscale.com>
 * Recode: Jason Jin <jason.jin@मुक्तscale.com>
 *         York Sun <yorksun@मुक्तscale.com>
 *
 * Reग_लिखो the पूर्णांकerrupt routing. हटाओ the 8259PIC support,
 * All the पूर्णांकegrated device in ULI use sideband पूर्णांकerrupt.
 *
 * Copyright 2008 Freescale Semiconductor Inc.
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/delay.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/of.h>
#समावेश <linux/fsl/guts.h>

#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/prom.h>
#समावेश <mm/mmu_decl.h>
#समावेश <यंत्र/udbg.h>

#समावेश <यंत्र/mpic.h>

#समावेश <linux/of_platक्रमm.h>
#समावेश <sysdev/fsl_pci.h>
#समावेश <sysdev/fsl_soc.h>

#समावेश "mpc86xx.h"

अटल काष्ठा device_node *pixis_node;
अटल अचिन्हित अक्षर *pixis_bdcfg0, *pixis_arch;

/* DIU Pixel Clock bits of the CLKDVDR Global Utilities रेजिस्टर */
#घोषणा CLKDVDR_PXCKEN		0x80000000
#घोषणा CLKDVDR_PXCKINV		0x10000000
#घोषणा CLKDVDR_PXCKDLY		0x06000000
#घोषणा CLKDVDR_PXCLK_MASK	0x001F0000

#अगर_घोषित CONFIG_SUSPEND
अटल irqवापस_t mpc8610_sw9_irq(पूर्णांक irq, व्योम *data)
अणु
	pr_debug("%s: PIXIS' event (sw9/wakeup) IRQ handled\n", __func__);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम __init mpc8610_suspend_init(व्योम)
अणु
	पूर्णांक irq;
	पूर्णांक ret;

	अगर (!pixis_node)
		वापस;

	irq = irq_of_parse_and_map(pixis_node, 0);
	अगर (!irq) अणु
		pr_err("%s: can't map pixis event IRQ.\n", __func__);
		वापस;
	पूर्ण

	ret = request_irq(irq, mpc8610_sw9_irq, 0, "sw9:wakeup", शून्य);
	अगर (ret) अणु
		pr_err("%s: can't request pixis event IRQ: %d\n",
		       __func__, ret);
		irq_dispose_mapping(irq);
	पूर्ण

	enable_irq_wake(irq);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम mpc8610_suspend_init(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_SUSPEND */

अटल स्थिर काष्ठा of_device_id mpc8610_ids[] __initस्थिर = अणु
	अणु .compatible = "fsl,mpc8610-immr", पूर्ण,
	अणु .compatible = "fsl,mpc8610-guts", पूर्ण,
	/* So that the DMA channel nodes can be probed inभागidually: */
	अणु .compatible = "fsl,eloplus-dma", पूर्ण,
	/* PCI controllers */
	अणु .compatible = "fsl,mpc8610-pci", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक __init mpc8610_declare_of_platक्रमm_devices(व्योम)
अणु
	/* Enable wakeup on PIXIS' event IRQ. */
	mpc8610_suspend_init();

	mpc86xx_common_publish_devices();

	/* Without this call, the SSI device driver won't get probed. */
	of_platक्रमm_bus_probe(शून्य, mpc8610_ids, शून्य);

	वापस 0;
पूर्ण
machine_arch_initcall(mpc86xx_hpcd, mpc8610_declare_of_platक्रमm_devices);

#अगर defined(CONFIG_FB_FSL_DIU) || defined(CONFIG_FB_FSL_DIU_MODULE)

/*
 * DIU Area Descriptor
 *
 * The MPC8610 reference manual shows the bits of the AD रेजिस्टर in
 * little-endian order, which causes the BLUE_C field to be split पूर्णांकo two
 * parts. To simplअगरy the definition of the MAKE_AD() macro, we define the
 * fields in big-endian order and byte-swap the result.
 *
 * So even though the रेजिस्टरs करोn't look like they're in the
 * same bit positions as they are on the P1022, the same value is written to
 * the AD रेजिस्टर on the MPC8610 and on the P1022.
 */
#घोषणा AD_BYTE_F		0x10000000
#घोषणा AD_ALPHA_C_MASK		0x0E000000
#घोषणा AD_ALPHA_C_SHIFT	25
#घोषणा AD_BLUE_C_MASK		0x01800000
#घोषणा AD_BLUE_C_SHIFT		23
#घोषणा AD_GREEN_C_MASK		0x00600000
#घोषणा AD_GREEN_C_SHIFT	21
#घोषणा AD_RED_C_MASK		0x00180000
#घोषणा AD_RED_C_SHIFT		19
#घोषणा AD_PALETTE		0x00040000
#घोषणा AD_PIXEL_S_MASK		0x00030000
#घोषणा AD_PIXEL_S_SHIFT	16
#घोषणा AD_COMP_3_MASK		0x0000F000
#घोषणा AD_COMP_3_SHIFT		12
#घोषणा AD_COMP_2_MASK		0x00000F00
#घोषणा AD_COMP_2_SHIFT		8
#घोषणा AD_COMP_1_MASK		0x000000F0
#घोषणा AD_COMP_1_SHIFT		4
#घोषणा AD_COMP_0_MASK		0x0000000F
#घोषणा AD_COMP_0_SHIFT		0

#घोषणा MAKE_AD(alpha, red, blue, green, size, c0, c1, c2, c3) \
	cpu_to_le32(AD_BYTE_F | (alpha << AD_ALPHA_C_SHIFT) | \
	(blue << AD_BLUE_C_SHIFT) | (green << AD_GREEN_C_SHIFT) | \
	(red << AD_RED_C_SHIFT) | (c3 << AD_COMP_3_SHIFT) | \
	(c2 << AD_COMP_2_SHIFT) | (c1 << AD_COMP_1_SHIFT) | \
	(c0 << AD_COMP_0_SHIFT) | (size << AD_PIXEL_S_SHIFT))

u32 mpc8610hpcd_get_pixel_क्रमmat(क्रमागत fsl_diu_monitor_port port,
				 अचिन्हित पूर्णांक bits_per_pixel)
अणु
	अटल स्थिर u32 pixelक्रमmat[][3] = अणु
		अणु
			MAKE_AD(3, 0, 2, 1, 3, 8, 8, 8, 8),
			MAKE_AD(4, 2, 0, 1, 2, 8, 8, 8, 0),
			MAKE_AD(4, 0, 2, 1, 1, 5, 6, 5, 0)
		पूर्ण,
		अणु
			MAKE_AD(3, 2, 0, 1, 3, 8, 8, 8, 8),
			MAKE_AD(4, 0, 2, 1, 2, 8, 8, 8, 0),
			MAKE_AD(4, 2, 0, 1, 1, 5, 6, 5, 0)
		पूर्ण,
	पूर्ण;
	अचिन्हित पूर्णांक arch_monitor;

	/* The DVI port is mis-wired on revision 1 of this board. */
	arch_monitor =
		((*pixis_arch == 0x01) && (port == FSL_DIU_PORT_DVI)) ? 0 : 1;

	चयन (bits_per_pixel) अणु
	हाल 32:
		वापस pixelक्रमmat[arch_monitor][0];
	हाल 24:
		वापस pixelक्रमmat[arch_monitor][1];
	हाल 16:
		वापस pixelक्रमmat[arch_monitor][2];
	शेष:
		pr_err("fsl-diu: unsupported pixel depth %u\n", bits_per_pixel);
		वापस 0;
	पूर्ण
पूर्ण

व्योम mpc8610hpcd_set_gamma_table(क्रमागत fsl_diu_monitor_port port,
				 अक्षर *gamma_table_base)
अणु
	पूर्णांक i;
	अगर (port == FSL_DIU_PORT_DLVDS) अणु
		क्रम (i = 0; i < 256*3; i++)
			gamma_table_base[i] = (gamma_table_base[i] << 2) |
					 ((gamma_table_base[i] >> 6) & 0x03);
	पूर्ण
पूर्ण

#घोषणा PX_BRDCFG0_DVISEL	(1 << 3)
#घोषणा PX_BRDCFG0_DLINK	(1 << 4)
#घोषणा PX_BRDCFG0_DIU_MASK	(PX_BRDCFG0_DVISEL | PX_BRDCFG0_DLINK)

व्योम mpc8610hpcd_set_monitor_port(क्रमागत fsl_diu_monitor_port port)
अणु
	चयन (port) अणु
	हाल FSL_DIU_PORT_DVI:
		clrsetbits_8(pixis_bdcfg0, PX_BRDCFG0_DIU_MASK,
			     PX_BRDCFG0_DVISEL | PX_BRDCFG0_DLINK);
		अवरोध;
	हाल FSL_DIU_PORT_LVDS:
		clrsetbits_8(pixis_bdcfg0, PX_BRDCFG0_DIU_MASK,
			     PX_BRDCFG0_DLINK);
		अवरोध;
	हाल FSL_DIU_PORT_DLVDS:
		clrbits8(pixis_bdcfg0, PX_BRDCFG0_DIU_MASK);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * mpc8610hpcd_set_pixel_घड़ी: program the DIU's घड़ी
 *
 * @pixघड़ी: the wavelength, in picoseconds, of the घड़ी
 */
व्योम mpc8610hpcd_set_pixel_घड़ी(अचिन्हित पूर्णांक pixघड़ी)
अणु
	काष्ठा device_node *guts_np = शून्य;
	काष्ठा ccsr_guts __iomem *guts;
	अचिन्हित दीर्घ freq;
	u64 temp;
	u32 pxclk;

	/* Map the global utilities रेजिस्टरs. */
	guts_np = of_find_compatible_node(शून्य, शून्य, "fsl,mpc8610-guts");
	अगर (!guts_np) अणु
		pr_err("mpc8610hpcd: missing global utilities device node\n");
		वापस;
	पूर्ण

	guts = of_iomap(guts_np, 0);
	of_node_put(guts_np);
	अगर (!guts) अणु
		pr_err("mpc8610hpcd: could not map global utilities device\n");
		वापस;
	पूर्ण

	/* Convert pixघड़ी from a wavelength to a frequency */
	temp = 1000000000000ULL;
	करो_भाग(temp, pixघड़ी);
	freq = temp;

	/*
	 * 'pxclk' is the ratio of the platक्रमm घड़ी to the pixel घड़ी.
	 * On the MPC8610, the value programmed पूर्णांकo CLKDVDR is the ratio
	 * minus one.  The valid range of values is 2-31.
	 */
	pxclk = DIV_ROUND_CLOSEST(fsl_get_sys_freq(), freq) - 1;
	pxclk = clamp_t(u32, pxclk, 2, 31);

	/* Disable the pixel घड़ी, and set it to non-inverted and no delay */
	clrbits32(&guts->clkdvdr,
		  CLKDVDR_PXCKEN | CLKDVDR_PXCKDLY | CLKDVDR_PXCLK_MASK);

	/* Enable the घड़ी and set the pxclk */
	setbits32(&guts->clkdvdr, CLKDVDR_PXCKEN | (pxclk << 16));

	iounmap(guts);
पूर्ण

क्रमागत fsl_diu_monitor_port
mpc8610hpcd_valid_monitor_port(क्रमागत fsl_diu_monitor_port port)
अणु
	वापस port;
पूर्ण

#पूर्ण_अगर

अटल व्योम __init mpc86xx_hpcd_setup_arch(व्योम)
अणु
	काष्ठा resource r;
	अचिन्हित अक्षर *pixis;

	अगर (ppc_md.progress)
		ppc_md.progress("mpc86xx_hpcd_setup_arch()", 0);

	fsl_pci_assign_primary();

#अगर defined(CONFIG_FB_FSL_DIU) || defined(CONFIG_FB_FSL_DIU_MODULE)
	diu_ops.get_pixel_क्रमmat	= mpc8610hpcd_get_pixel_क्रमmat;
	diu_ops.set_gamma_table		= mpc8610hpcd_set_gamma_table;
	diu_ops.set_monitor_port	= mpc8610hpcd_set_monitor_port;
	diu_ops.set_pixel_घड़ी		= mpc8610hpcd_set_pixel_घड़ी;
	diu_ops.valid_monitor_port	= mpc8610hpcd_valid_monitor_port;
#पूर्ण_अगर

	pixis_node = of_find_compatible_node(शून्य, शून्य, "fsl,fpga-pixis");
	अगर (pixis_node) अणु
		of_address_to_resource(pixis_node, 0, &r);
		of_node_put(pixis_node);
		pixis = ioremap(r.start, 32);
		अगर (!pixis) अणु
			prपूर्णांकk(KERN_ERR "Err: can't map FPGA cfg register!\n");
			वापस;
		पूर्ण
		pixis_bdcfg0 = pixis + 8;
		pixis_arch = pixis + 1;
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_ERR "Err: "
				"can't find device node 'fsl,fpga-pixis'\n");

	prपूर्णांकk("MPC86xx HPCD board from Freescale Semiconductor\n");
पूर्ण

/*
 * Called very early, device-tree isn't unflattened
 */
अटल पूर्णांक __init mpc86xx_hpcd_probe(व्योम)
अणु
	अगर (of_machine_is_compatible("fsl,MPC8610HPCD"))
		वापस 1;	/* Looks good */

	वापस 0;
पूर्ण

define_machine(mpc86xx_hpcd) अणु
	.name			= "MPC86xx HPCD",
	.probe			= mpc86xx_hpcd_probe,
	.setup_arch		= mpc86xx_hpcd_setup_arch,
	.init_IRQ		= mpc86xx_init_irq,
	.get_irq		= mpic_get_irq,
	.समय_init		= mpc86xx_समय_init,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
#पूर्ण_अगर
पूर्ण;
