<शैली गुरु>
/*
 * P1022DS board specअगरic routines
 *
 * Authors: Travis Wheatley <travis.wheatley@मुक्तscale.com>
 *          Dave Liu <daveliu@मुक्तscale.com>
 *          Timur Tabi <timur@मुक्तscale.com>
 *
 * Copyright 2010 Freescale Semiconductor, Inc.
 *
 * This file is taken from the Freescale P1022DS BSP, with modअगरications:
 * 2) No AMP support
 * 3) No PCI endpoपूर्णांक support
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
#समावेश <यंत्र/fsl_lbc.h>
#समावेश "smp.h"

#समावेश "mpc85xx.h"

#अगर defined(CONFIG_FB_FSL_DIU) || defined(CONFIG_FB_FSL_DIU_MODULE)

#घोषणा PMUXCR_ELBCDIU_MASK	0xc0000000
#घोषणा PMUXCR_ELBCDIU_NOR16	0x80000000
#घोषणा PMUXCR_ELBCDIU_DIU	0x40000000

/*
 * Board-specअगरic initialization of the DIU.  This code should probably be
 * executed when the DIU is खोलोed, rather than in arch code, but the DIU
 * driver करोes not have a mechanism क्रम this (yet).
 *
 * This is especially problematic on the P1022DS because the local bus (eLBC)
 * and the DIU video संकेतs share the same pins, which means that enabling the
 * DIU will disable access to NOR flash.
 */

/* DIU Pixel Clock bits of the CLKDVDR Global Utilities रेजिस्टर */
#घोषणा CLKDVDR_PXCKEN		0x80000000
#घोषणा CLKDVDR_PXCKINV		0x10000000
#घोषणा CLKDVDR_PXCKDLY		0x06000000
#घोषणा CLKDVDR_PXCLK_MASK	0x00FF0000

/* Some ngPIXIS रेजिस्टर definitions */
#घोषणा PX_CTL		3
#घोषणा PX_BRDCFG0	8
#घोषणा PX_BRDCFG1	9

#घोषणा PX_BRDCFG0_ELBC_SPI_MASK	0xc0
#घोषणा PX_BRDCFG0_ELBC_SPI_ELBC	0x00
#घोषणा PX_BRDCFG0_ELBC_SPI_शून्य	0xc0
#घोषणा PX_BRDCFG0_ELBC_DIU		0x02

#घोषणा PX_BRDCFG1_DVIEN	0x80
#घोषणा PX_BRDCFG1_DFPEN	0x40
#घोषणा PX_BRDCFG1_BACKLIGHT	0x20
#घोषणा PX_BRDCFG1_DDCEN	0x10

#घोषणा PX_CTL_ALTACC		0x80

/*
 * DIU Area Descriptor
 *
 * Note that we need to byte-swap the value beक्रमe it's written to the AD
 * रेजिस्टर.  So even though the रेजिस्टरs करोn't look like they're in the same
 * bit positions as they are on the MPC8610, the same value is written to the
 * AD रेजिस्टर on the MPC8610 and on the P1022.
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

काष्ठा fsl_law अणु
	u32	lawbar;
	u32	reserved1;
	u32	lawar;
	u32	reserved[5];
पूर्ण;

#घोषणा LAWBAR_MASK	0x00F00000
#घोषणा LAWBAR_SHIFT	12

#घोषणा LAWAR_EN	0x80000000
#घोषणा LAWAR_TGT_MASK	0x01F00000
#घोषणा LAW_TRGT_IF_LBC	(0x04 << 20)

#घोषणा LAWAR_MASK	(LAWAR_EN | LAWAR_TGT_MASK)
#घोषणा LAWAR_MATCH	(LAWAR_EN | LAW_TRGT_IF_LBC)

#घोषणा BR_BA		0xFFFF8000

/*
 * Map a BRx value to a physical address
 *
 * The localbus BRx रेजिस्टरs only store the lower 32 bits of the address.  To
 * obtain the upper four bits, we need to scan the LAW table.  The entry which
 * maps to the localbus will contain the upper four bits.
 */
अटल phys_addr_t lbc_br_to_phys(स्थिर व्योम *ecm, अचिन्हित पूर्णांक count, u32 br)
अणु
#अगर_अघोषित CONFIG_PHYS_64BIT
	/*
	 * If we only have 32-bit addressing, then the BRx address *is* the
	 * physical address.
	 */
	वापस br & BR_BA;
#अन्यथा
	स्थिर काष्ठा fsl_law *law = ecm + 0xc08;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		u64 lawbar = in_be32(&law[i].lawbar);
		u32 lawar = in_be32(&law[i].lawar);

		अगर ((lawar & LAWAR_MASK) == LAWAR_MATCH)
			/* Extract the upper four bits */
			वापस (br & BR_BA) | ((lawbar & LAWBAR_MASK) << 12);
	पूर्ण

	वापस 0;
#पूर्ण_अगर
पूर्ण

/**
 * p1022ds_set_monitor_port: चयन the output to a dअगरferent monitor port
 */
अटल व्योम p1022ds_set_monitor_port(क्रमागत fsl_diu_monitor_port port)
अणु
	काष्ठा device_node *guts_node;
	काष्ठा device_node *lbc_node = शून्य;
	काष्ठा device_node *law_node = शून्य;
	काष्ठा ccsr_guts __iomem *guts;
	काष्ठा fsl_lbc_regs *lbc = शून्य;
	व्योम *ecm = शून्य;
	u8 __iomem *lbc_lcs0_ba = शून्य;
	u8 __iomem *lbc_lcs1_ba = शून्य;
	phys_addr_t cs0_addr, cs1_addr;
	u32 br0, or0, br1, or1;
	स्थिर __be32 *iprop;
	अचिन्हित पूर्णांक num_laws;
	u8 b;

	/* Map the global utilities रेजिस्टरs. */
	guts_node = of_find_compatible_node(शून्य, शून्य, "fsl,p1022-guts");
	अगर (!guts_node) अणु
		pr_err("p1022ds: missing global utilities device node\n");
		वापस;
	पूर्ण

	guts = of_iomap(guts_node, 0);
	अगर (!guts) अणु
		pr_err("p1022ds: could not map global utilities device\n");
		जाओ निकास;
	पूर्ण

	lbc_node = of_find_compatible_node(शून्य, शून्य, "fsl,p1022-elbc");
	अगर (!lbc_node) अणु
		pr_err("p1022ds: missing localbus node\n");
		जाओ निकास;
	पूर्ण

	lbc = of_iomap(lbc_node, 0);
	अगर (!lbc) अणु
		pr_err("p1022ds: could not map localbus node\n");
		जाओ निकास;
	पूर्ण

	law_node = of_find_compatible_node(शून्य, शून्य, "fsl,ecm-law");
	अगर (!law_node) अणु
		pr_err("p1022ds: missing local access window node\n");
		जाओ निकास;
	पूर्ण

	ecm = of_iomap(law_node, 0);
	अगर (!ecm) अणु
		pr_err("p1022ds: could not map local access window node\n");
		जाओ निकास;
	पूर्ण

	iprop = of_get_property(law_node, "fsl,num-laws", शून्य);
	अगर (!iprop) अणु
		pr_err("p1022ds: LAW node is missing fsl,num-laws property\n");
		जाओ निकास;
	पूर्ण
	num_laws = be32_to_cpup(iprop);

	/*
	 * Indirect mode requires both BR0 and BR1 to be set to "GPCM",
	 * otherwise ग_लिखोs to these addresses won't actually appear on the
	 * local bus, and so the PIXIS won't see them.
	 *
	 * In FCM mode, ग_लिखोs go to the न_अंकD controller, which करोes not pass
	 * them to the localbus directly.  So we क्रमce BR0 and BR1 पूर्णांकo GPCM
	 * mode, since we करोn't care about what's behind the localbus any
	 * more.
	 */
	br0 = in_be32(&lbc->bank[0].br);
	br1 = in_be32(&lbc->bank[1].br);
	or0 = in_be32(&lbc->bank[0].or);
	or1 = in_be32(&lbc->bank[1].or);

	/* Make sure CS0 and CS1 are programmed */
	अगर (!(br0 & BR_V) || !(br1 & BR_V)) अणु
		pr_err("p1022ds: CS0 and/or CS1 is not programmed\n");
		जाओ निकास;
	पूर्ण

	/*
	 * Use the existing BRx/ORx values अगर it's alपढ़ोy GPCM. Otherwise,
	 * क्रमce the values to simple 32KB GPCM winकरोws with the most
	 * conservative timing.
	 */
	अगर ((br0 & BR_MSEL) != BR_MS_GPCM) अणु
		br0 = (br0 & BR_BA) | BR_V;
		or0 = 0xFFFF8000 | 0xFF7;
		out_be32(&lbc->bank[0].br, br0);
		out_be32(&lbc->bank[0].or, or0);
	पूर्ण
	अगर ((br1 & BR_MSEL) != BR_MS_GPCM) अणु
		br1 = (br1 & BR_BA) | BR_V;
		or1 = 0xFFFF8000 | 0xFF7;
		out_be32(&lbc->bank[1].br, br1);
		out_be32(&lbc->bank[1].or, or1);
	पूर्ण

	cs0_addr = lbc_br_to_phys(ecm, num_laws, br0);
	अगर (!cs0_addr) अणु
		pr_err("p1022ds: could not determine physical address for CS0"
		       " (BR0=%08x)\n", br0);
		जाओ निकास;
	पूर्ण
	cs1_addr = lbc_br_to_phys(ecm, num_laws, br1);
	अगर (!cs1_addr) अणु
		pr_err("p1022ds: could not determine physical address for CS1"
		       " (BR1=%08x)\n", br1);
		जाओ निकास;
	पूर्ण

	lbc_lcs0_ba = ioremap(cs0_addr, 1);
	अगर (!lbc_lcs0_ba) अणु
		pr_err("p1022ds: could not ioremap CS0 address %llx\n",
		       (अचिन्हित दीर्घ दीर्घ)cs0_addr);
		जाओ निकास;
	पूर्ण
	lbc_lcs1_ba = ioremap(cs1_addr, 1);
	अगर (!lbc_lcs1_ba) अणु
		pr_err("p1022ds: could not ioremap CS1 address %llx\n",
		       (अचिन्हित दीर्घ दीर्घ)cs1_addr);
		जाओ निकास;
	पूर्ण

	/* Make sure we're in indirect mode first. */
	अगर ((in_be32(&guts->pmuxcr) & PMUXCR_ELBCDIU_MASK) !=
	    PMUXCR_ELBCDIU_DIU) अणु
		काष्ठा device_node *pixis_node;
		व्योम __iomem *pixis;

		pixis_node =
			of_find_compatible_node(शून्य, शून्य, "fsl,p1022ds-fpga");
		अगर (!pixis_node) अणु
			pr_err("p1022ds: missing pixis node\n");
			जाओ निकास;
		पूर्ण

		pixis = of_iomap(pixis_node, 0);
		of_node_put(pixis_node);
		अगर (!pixis) अणु
			pr_err("p1022ds: could not map pixis registers\n");
			जाओ निकास;
		पूर्ण

		/* Enable indirect PIXIS mode.  */
		setbits8(pixis + PX_CTL, PX_CTL_ALTACC);
		iounmap(pixis);

		/* Switch the board mux to the DIU */
		out_8(lbc_lcs0_ba, PX_BRDCFG0);	/* BRDCFG0 */
		b = in_8(lbc_lcs1_ba);
		b |= PX_BRDCFG0_ELBC_DIU;
		out_8(lbc_lcs1_ba, b);

		/* Set the chip mux to DIU mode. */
		clrsetbits_be32(&guts->pmuxcr, PMUXCR_ELBCDIU_MASK,
				PMUXCR_ELBCDIU_DIU);
		in_be32(&guts->pmuxcr);
	पूर्ण


	चयन (port) अणु
	हाल FSL_DIU_PORT_DVI:
		/* Enable the DVI port, disable the DFP and the backlight */
		out_8(lbc_lcs0_ba, PX_BRDCFG1);
		b = in_8(lbc_lcs1_ba);
		b &= ~(PX_BRDCFG1_DFPEN | PX_BRDCFG1_BACKLIGHT);
		b |= PX_BRDCFG1_DVIEN;
		out_8(lbc_lcs1_ba, b);
		अवरोध;
	हाल FSL_DIU_PORT_LVDS:
		/*
		 * LVDS also needs backlight enabled, otherwise the display
		 * will be blank.
		 */
		/* Enable the DFP port, disable the DVI and the backlight */
		out_8(lbc_lcs0_ba, PX_BRDCFG1);
		b = in_8(lbc_lcs1_ba);
		b &= ~PX_BRDCFG1_DVIEN;
		b |= PX_BRDCFG1_DFPEN | PX_BRDCFG1_BACKLIGHT;
		out_8(lbc_lcs1_ba, b);
		अवरोध;
	शेष:
		pr_err("p1022ds: unsupported monitor port %i\n", port);
	पूर्ण

निकास:
	अगर (lbc_lcs1_ba)
		iounmap(lbc_lcs1_ba);
	अगर (lbc_lcs0_ba)
		iounmap(lbc_lcs0_ba);
	अगर (lbc)
		iounmap(lbc);
	अगर (ecm)
		iounmap(ecm);
	अगर (guts)
		iounmap(guts);

	of_node_put(law_node);
	of_node_put(lbc_node);
	of_node_put(guts_node);
पूर्ण

/**
 * p1022ds_set_pixel_घड़ी: program the DIU's घड़ी
 *
 * @pixघड़ी: the wavelength, in picoseconds, of the घड़ी
 */
व्योम p1022ds_set_pixel_घड़ी(अचिन्हित पूर्णांक pixघड़ी)
अणु
	काष्ठा device_node *guts_np = शून्य;
	काष्ठा ccsr_guts __iomem *guts;
	अचिन्हित दीर्घ freq;
	u64 temp;
	u32 pxclk;

	/* Map the global utilities रेजिस्टरs. */
	guts_np = of_find_compatible_node(शून्य, शून्य, "fsl,p1022-guts");
	अगर (!guts_np) अणु
		pr_err("p1022ds: missing global utilities device node\n");
		वापस;
	पूर्ण

	guts = of_iomap(guts_np, 0);
	of_node_put(guts_np);
	अगर (!guts) अणु
		pr_err("p1022ds: could not map global utilities device\n");
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
 * p1022ds_valid_monitor_port: set the monitor port क्रम sysfs
 */
क्रमागत fsl_diu_monitor_port
p1022ds_valid_monitor_port(क्रमागत fsl_diu_monitor_port port)
अणु
	चयन (port) अणु
	हाल FSL_DIU_PORT_DVI:
	हाल FSL_DIU_PORT_LVDS:
		वापस port;
	शेष:
		वापस FSL_DIU_PORT_DVI; /* Dual-link LVDS is not supported */
	पूर्ण
पूर्ण

#पूर्ण_अगर

व्योम __init p1022_ds_pic_init(व्योम)
अणु
	काष्ठा mpic *mpic = mpic_alloc(शून्य, 0, MPIC_BIG_ENDIAN |
		MPIC_SINGLE_DEST_CPU,
		0, 256, " OpenPIC  ");
	BUG_ON(mpic == शून्य);
	mpic_init(mpic);
पूर्ण

#अगर defined(CONFIG_FB_FSL_DIU) || defined(CONFIG_FB_FSL_DIU_MODULE)

/* TRUE अगर there is a "video=fslfb" command-line parameter. */
अटल bool fslfb;

/*
 * Search क्रम a "video=fslfb" command-line parameter, and set 'fslfb' to
 * true अगर we find it.
 *
 * We need to use early_param() instead of __setup() because the normal
 * __setup() माला_लो called to late.  However, early_param() माला_लो called very
 * early, beक्रमe the device tree is unflattened, so all we can करो now is set a
 * global variable.  Later on, p1022_ds_setup_arch() will use that variable
 * to determine अगर we need to update the device tree.
 */
अटल पूर्णांक __init early_video_setup(अक्षर *options)
अणु
	fslfb = (म_भेदन(options, "fslfb:", 6) == 0);

	वापस 0;
पूर्ण
early_param("video", early_video_setup);

#पूर्ण_अगर

/*
 * Setup the architecture
 */
अटल व्योम __init p1022_ds_setup_arch(व्योम)
अणु
	अगर (ppc_md.progress)
		ppc_md.progress("p1022_ds_setup_arch()", 0);

#अगर defined(CONFIG_FB_FSL_DIU) || defined(CONFIG_FB_FSL_DIU_MODULE)
	diu_ops.set_monitor_port	= p1022ds_set_monitor_port;
	diu_ops.set_pixel_घड़ी		= p1022ds_set_pixel_घड़ी;
	diu_ops.valid_monitor_port	= p1022ds_valid_monitor_port;

	/*
	 * Disable the NOR and न_अंकD flash nodes अगर there is video=fslfb...
	 * command-line parameter.  When the DIU is active, the localbus is
	 * unavailable, so we have to disable these nodes beक्रमe the MTD
	 * driver loads.
	 */
	अगर (fslfb) अणु
		काष्ठा device_node *np =
			of_find_compatible_node(शून्य, शून्य, "fsl,p1022-elbc");

		अगर (np) अणु
			काष्ठा device_node *np2;

			of_node_get(np);
			np2 = of_find_compatible_node(np, शून्य, "cfi-flash");
			अगर (np2) अणु
				अटल काष्ठा property nor_status = अणु
					.name = "status",
					.value = "disabled",
					.length = माप("disabled"),
				पूर्ण;

				/*
				 * of_update_property() is called beक्रमe
				 * kदो_स्मृति() is available, so the 'new' object
				 * should be allocated in the global area.
				 * The easiest way is to करो that is to
				 * allocate one अटल local variable क्रम each
				 * call to this function.
				 */
				pr_info("p1022ds: disabling %pOF node",
					np2);
				of_update_property(np2, &nor_status);
				of_node_put(np2);
			पूर्ण

			of_node_get(np);
			np2 = of_find_compatible_node(np, शून्य,
						      "fsl,elbc-fcm-nand");
			अगर (np2) अणु
				अटल काष्ठा property nand_status = अणु
					.name = "status",
					.value = "disabled",
					.length = माप("disabled"),
				पूर्ण;

				pr_info("p1022ds: disabling %pOF node",
					np2);
				of_update_property(np2, &nand_status);
				of_node_put(np2);
			पूर्ण

			of_node_put(np);
		पूर्ण

	पूर्ण

#पूर्ण_अगर

	mpc85xx_smp_init();

	fsl_pci_assign_primary();

	swiotlb_detect_4g();

	pr_info("Freescale P1022 DS reference board\n");
पूर्ण

machine_arch_initcall(p1022_ds, mpc85xx_common_publish_devices);

/*
 * Called very early, device-tree isn't unflattened
 */
अटल पूर्णांक __init p1022_ds_probe(व्योम)
अणु
	वापस of_machine_is_compatible("fsl,p1022ds");
पूर्ण

define_machine(p1022_ds) अणु
	.name			= "P1022 DS",
	.probe			= p1022_ds_probe,
	.setup_arch		= p1022_ds_setup_arch,
	.init_IRQ		= p1022_ds_pic_init,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
	.pcibios_fixup_phb	= fsl_pcibios_fixup_phb,
#पूर्ण_अगर
	.get_irq		= mpic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;
