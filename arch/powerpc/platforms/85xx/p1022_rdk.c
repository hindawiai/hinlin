<शैली गुरु>
/*
 * P1022 RDK board specअगरic routines
 *
 * Copyright 2012 Freescale Semiconductor, Inc.
 *
 * Author: Timur Tabi <timur@मुक्तscale.com>
 *
 * Based on p1022_ds.c
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2.  This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#समावेश <linux/fsl/guts.h>
#समावेश <linux/pci.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <यंत्र/भाग64.h>
#समावेश <यंत्र/mpic.h>
#समावेश <यंत्र/swiotlb.h>

#समावेश <sysdev/fsl_soc.h>
#समावेश <sysdev/fsl_pci.h>
#समावेश <यंत्र/udbg.h>
#समावेश "smp.h"

#समावेश "mpc85xx.h"

#अगर defined(CONFIG_FB_FSL_DIU) || defined(CONFIG_FB_FSL_DIU_MODULE)

/* DIU Pixel Clock bits of the CLKDVDR Global Utilities रेजिस्टर */
#घोषणा CLKDVDR_PXCKEN		0x80000000
#घोषणा CLKDVDR_PXCKINV		0x10000000
#घोषणा CLKDVDR_PXCKDLY		0x06000000
#घोषणा CLKDVDR_PXCLK_MASK	0x00FF0000

/**
 * p1022rdk_set_pixel_घड़ी: program the DIU's घड़ी
 *
 * @pixघड़ी: the wavelength, in picoseconds, of the घड़ी
 */
व्योम p1022rdk_set_pixel_घड़ी(अचिन्हित पूर्णांक pixघड़ी)
अणु
	काष्ठा device_node *guts_np = शून्य;
	काष्ठा ccsr_guts __iomem *guts;
	अचिन्हित दीर्घ freq;
	u64 temp;
	u32 pxclk;

	/* Map the global utilities रेजिस्टरs. */
	guts_np = of_find_compatible_node(शून्य, शून्य, "fsl,p1022-guts");
	अगर (!guts_np) अणु
		pr_err("p1022rdk: missing global utilities device node\n");
		वापस;
	पूर्ण

	guts = of_iomap(guts_np, 0);
	of_node_put(guts_np);
	अगर (!guts) अणु
		pr_err("p1022rdk: could not map global utilities device\n");
		वापस;
	पूर्ण

	/* Convert pixघड़ी from a wavelength to a frequency */
	temp = 1000000000000ULL;
	करो_भाग(temp, pixघड़ी);
	freq = temp;

	/*
	 * 'pxclk' is the ratio of the platक्रमm घड़ी to the pixel घड़ी.
	 * This number is programmed पूर्णांकo the CLKDVDR रेजिस्टर, and the valid
	 * range of values is 2-255.
	 */
	pxclk = DIV_ROUND_CLOSEST(fsl_get_sys_freq(), freq);
	pxclk = clamp_t(u32, pxclk, 2, 255);

	/* Disable the pixel घड़ी, and set it to non-inverted and no delay */
	clrbits32(&guts->clkdvdr,
		  CLKDVDR_PXCKEN | CLKDVDR_PXCKDLY | CLKDVDR_PXCLK_MASK);

	/* Enable the घड़ी and set the pxclk */
	setbits32(&guts->clkdvdr, CLKDVDR_PXCKEN | (pxclk << 16));

	iounmap(guts);
पूर्ण

/**
 * p1022rdk_valid_monitor_port: set the monitor port क्रम sysfs
 */
क्रमागत fsl_diu_monitor_port
p1022rdk_valid_monitor_port(क्रमागत fsl_diu_monitor_port port)
अणु
	वापस FSL_DIU_PORT_DVI;
पूर्ण

#पूर्ण_अगर

व्योम __init p1022_rdk_pic_init(व्योम)
अणु
	काष्ठा mpic *mpic = mpic_alloc(शून्य, 0, MPIC_BIG_ENDIAN |
		MPIC_SINGLE_DEST_CPU,
		0, 256, " OpenPIC  ");
	BUG_ON(mpic == शून्य);
	mpic_init(mpic);
पूर्ण

/*
 * Setup the architecture
 */
अटल व्योम __init p1022_rdk_setup_arch(व्योम)
अणु
	अगर (ppc_md.progress)
		ppc_md.progress("p1022_rdk_setup_arch()", 0);

#अगर defined(CONFIG_FB_FSL_DIU) || defined(CONFIG_FB_FSL_DIU_MODULE)
	diu_ops.set_pixel_घड़ी		= p1022rdk_set_pixel_घड़ी;
	diu_ops.valid_monitor_port	= p1022rdk_valid_monitor_port;
#पूर्ण_अगर

	mpc85xx_smp_init();

	fsl_pci_assign_primary();

	swiotlb_detect_4g();

	pr_info("Freescale / iVeia P1022 RDK reference board\n");
पूर्ण

machine_arch_initcall(p1022_rdk, mpc85xx_common_publish_devices);

/*
 * Called very early, device-tree isn't unflattened
 */
अटल पूर्णांक __init p1022_rdk_probe(व्योम)
अणु
	वापस of_machine_is_compatible("fsl,p1022rdk");
पूर्ण

define_machine(p1022_rdk) अणु
	.name			= "P1022 RDK",
	.probe			= p1022_rdk_probe,
	.setup_arch		= p1022_rdk_setup_arch,
	.init_IRQ		= p1022_rdk_pic_init,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsl_pcibios_fixup_phb,
#पूर्ण_अगर
	.get_irq		= mpic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;
