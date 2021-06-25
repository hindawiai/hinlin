<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Carsten Langgaard, carstenl@mips.com
 * Copyright (C) 2000 MIPS Technologies, Inc.  All rights reserved.
 * Copyright (C) 2008 Dmitri Vorobiev
 */
#समावेश <linux/cpu.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/ioport.h>
#समावेश <linux/irq.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/pci.h>
#समावेश <linux/screen_info.h>
#समावेश <linux/समय.स>
#समावेश <linux/dma-map-ops.h> /* क्रम dma_शेष_coherent */

#समावेश <यंत्र/fw/fw.h>
#समावेश <यंत्र/mips-cps.h>
#समावेश <यंत्र/mips-boards/generic.h>
#समावेश <यंत्र/mips-boards/malta.h>
#समावेश <यंत्र/mips-boards/maltaपूर्णांक.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/traps.h>
#अगर_घोषित CONFIG_VT
#समावेश <linux/console.h>
#पूर्ण_अगर

#घोषणा ROCIT_CONFIG_GEN0		0x1f403000
#घोषणा  ROCIT_CONFIG_GEN0_PCI_IOCU	BIT(7)

अटल काष्ठा resource standard_io_resources[] = अणु
	अणु
		.name = "dma1",
		.start = 0x00,
		.end = 0x1f,
		.flags = IORESOURCE_IO | IORESOURCE_BUSY
	पूर्ण,
	अणु
		.name = "timer",
		.start = 0x40,
		.end = 0x5f,
		.flags = IORESOURCE_IO | IORESOURCE_BUSY
	पूर्ण,
	अणु
		.name = "keyboard",
		.start = 0x60,
		.end = 0x6f,
		.flags = IORESOURCE_IO | IORESOURCE_BUSY
	पूर्ण,
	अणु
		.name = "dma page reg",
		.start = 0x80,
		.end = 0x8f,
		.flags = IORESOURCE_IO | IORESOURCE_BUSY
	पूर्ण,
	अणु
		.name = "dma2",
		.start = 0xc0,
		.end = 0xdf,
		.flags = IORESOURCE_IO | IORESOURCE_BUSY
	पूर्ण,
पूर्ण;

स्थिर अक्षर *get_प्रणाली_type(व्योम)
अणु
	वापस "MIPS Malta";
पूर्ण

#अगर_घोषित CONFIG_BLK_DEV_FD
अटल व्योम __init fd_activate(व्योम)
अणु
	/*
	 * Activate Floppy Controller in the SMSC FDC37M817 Super I/O
	 * Controller.
	 * Done by YAMON 2.00 onwards
	 */
	/* Entering config state. */
	SMSC_WRITE(SMSC_CONFIG_ENTER, SMSC_CONFIG_REG);

	/* Activate floppy controller. */
	SMSC_WRITE(SMSC_CONFIG_DEVNUM, SMSC_CONFIG_REG);
	SMSC_WRITE(SMSC_CONFIG_DEVNUM_FLOPPY, SMSC_DATA_REG);
	SMSC_WRITE(SMSC_CONFIG_ACTIVATE, SMSC_CONFIG_REG);
	SMSC_WRITE(SMSC_CONFIG_ACTIVATE_ENABLE, SMSC_DATA_REG);

	/* Exit config state. */
	SMSC_WRITE(SMSC_CONFIG_EXIT, SMSC_CONFIG_REG);
पूर्ण
#पूर्ण_अगर

अटल व्योम __init plat_setup_iocoherency(व्योम)
अणु
	u32 cfg;

	अगर (mips_revision_sconid == MIPS_REVISION_SCON_BONITO) अणु
		अगर (BONITO_PCICACHECTRL & BONITO_PCICACHECTRL_CPUCOH_PRES) अणु
			BONITO_PCICACHECTRL |= BONITO_PCICACHECTRL_CPUCOH_EN;
			pr_info("Enabled Bonito CPU coherency\n");
			dma_शेष_coherent = true;
		पूर्ण
		अगर (म_माला(fw_अ_लोmdline(), "iobcuncached")) अणु
			BONITO_PCICACHECTRL &= ~BONITO_PCICACHECTRL_IOBCCOH_EN;
			BONITO_PCIMEMBASECFG = BONITO_PCIMEMBASECFG &
				~(BONITO_PCIMEMBASECFG_MEMBASE0_CACHED |
				  BONITO_PCIMEMBASECFG_MEMBASE1_CACHED);
			pr_info("Disabled Bonito IOBC coherency\n");
		पूर्ण अन्यथा अणु
			BONITO_PCICACHECTRL |= BONITO_PCICACHECTRL_IOBCCOH_EN;
			BONITO_PCIMEMBASECFG |=
				(BONITO_PCIMEMBASECFG_MEMBASE0_CACHED |
				 BONITO_PCIMEMBASECFG_MEMBASE1_CACHED);
			pr_info("Enabled Bonito IOBC coherency\n");
		पूर्ण
	पूर्ण अन्यथा अगर (mips_cps_numiocu(0) != 0) अणु
		/* Nothing special needs to be करोne to enable coherency */
		pr_info("CMP IOCU detected\n");
		cfg = __raw_पढ़ोl((u32 *)CKSEG1ADDR(ROCIT_CONFIG_GEN0));
		अगर (cfg & ROCIT_CONFIG_GEN0_PCI_IOCU)
			dma_शेष_coherent = true;
		अन्यथा
			pr_crit("IOCU OPERATION DISABLED BY SWITCH - DEFAULTING TO SW IO COHERENCY\n");
	पूर्ण

	अगर (dma_शेष_coherent)
		pr_info("Hardware DMA cache coherency enabled\n");
	अन्यथा
		pr_info("Software DMA cache coherency enabled\n");
पूर्ण

अटल व्योम __init pci_घड़ी_check(व्योम)
अणु
	अचिन्हित पूर्णांक __iomem *jmpr_p =
		(अचिन्हित पूर्णांक *) ioremap(MALTA_JMPRS_REG, माप(अचिन्हित पूर्णांक));
	पूर्णांक jmpr = (__raw_पढ़ोl(jmpr_p) >> 2) & 0x07;
	अटल स्थिर पूर्णांक pciघड़ीs[] __initस्थिर = अणु
		33, 20, 25, 30, 12, 16, 37, 10
	पूर्ण;
	पूर्णांक pciघड़ी = pciघड़ीs[jmpr];
	अक्षर *optptr, *argptr = fw_अ_लोmdline();

	/*
	 * If user passed a pci_घड़ी= option, करोn't tack on another one
	 */
	optptr = म_माला(argptr, "pci_clock=");
	अगर (optptr && (optptr == argptr || optptr[-1] == ' '))
		वापस;

	अगर (pciघड़ी != 33) अणु
		pr_warn("WARNING: PCI clock is %dMHz, setting pci_clock\n",
			pciघड़ी);
		argptr += म_माप(argptr);
		प्र_लिखो(argptr, " pci_clock=%d", pciघड़ी);
		अगर (pciघड़ी < 20 || pciघड़ी > 66)
			pr_warn("WARNING: IDE timing calculations will be "
			        "incorrect\n");
	पूर्ण
पूर्ण

#अगर defined(CONFIG_VT) && defined(CONFIG_VGA_CONSOLE)
अटल व्योम __init screen_info_setup(व्योम)
अणु
	screen_info = (काष्ठा screen_info) अणु
		.orig_x = 0,
		.orig_y = 25,
		.ext_mem_k = 0,
		.orig_video_page = 0,
		.orig_video_mode = 0,
		.orig_video_cols = 80,
		.unused2 = 0,
		.orig_video_ega_bx = 0,
		.unused3 = 0,
		.orig_video_lines = 25,
		.orig_video_isVGA = VIDEO_TYPE_VGAC,
		.orig_video_poपूर्णांकs = 16
	पूर्ण;
पूर्ण
#पूर्ण_अगर

अटल व्योम __init bonito_quirks_setup(व्योम)
अणु
	अक्षर *argptr;

	argptr = fw_अ_लोmdline();
	अगर (म_माला(argptr, "debug")) अणु
		BONITO_BONGENCFG |= BONITO_BONGENCFG_DEBUGMODE;
		pr_info("Enabled Bonito debug mode\n");
	पूर्ण अन्यथा
		BONITO_BONGENCFG &= ~BONITO_BONGENCFG_DEBUGMODE;
पूर्ण

व्योम __init *plat_get_fdt(व्योम)
अणु
	वापस (व्योम *)__dtb_start;
पूर्ण

व्योम __init plat_mem_setup(व्योम)
अणु
	अचिन्हित पूर्णांक i;
	व्योम *fdt = plat_get_fdt();

	fdt = malta_dt_shim(fdt);
	__dt_setup_arch(fdt);

	अगर (IS_ENABLED(CONFIG_EVA))
		/* EVA has alपढ़ोy been configured in mach-malta/kernel-init.h */
		pr_info("Enhanced Virtual Addressing (EVA) activated\n");

	mips_pcibios_init();

	/* Request I/O space क्रम devices used on the Malta board. */
	क्रम (i = 0; i < ARRAY_SIZE(standard_io_resources); i++)
		request_resource(&ioport_resource, standard_io_resources+i);

	/*
	 * Enable DMA channel 4 (cascade channel) in the PIIX4 south bridge.
	 */
	enable_dma(4);

	अगर (mips_revision_sconid == MIPS_REVISION_SCON_BONITO)
		bonito_quirks_setup();

	plat_setup_iocoherency();

	pci_घड़ी_check();

#अगर_घोषित CONFIG_BLK_DEV_FD
	fd_activate();
#पूर्ण_अगर

#अगर defined(CONFIG_VT) && defined(CONFIG_VGA_CONSOLE)
	screen_info_setup();
#पूर्ण_अगर
पूर्ण
