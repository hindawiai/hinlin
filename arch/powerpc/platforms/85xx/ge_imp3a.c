<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * GE IMP3A Board Setup
 *
 * Author Martyn Welch <martyn.welch@ge.com>
 *
 * Copyright 2010 GE Intelligent Platक्रमms Embedded Systems, Inc.
 *
 * Based on: mpc85xx_ds.c (MPC85xx DS Board Setup)
 * Copyright 2007 Freescale Semiconductor Inc.
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/delay.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <mm/mmu_decl.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/mpic.h>
#समावेश <यंत्र/swiotlb.h>
#समावेश <यंत्र/nvram.h>

#समावेश <sysdev/fsl_soc.h>
#समावेश <sysdev/fsl_pci.h>
#समावेश "smp.h"

#समावेश "mpc85xx.h"
#समावेश <sysdev/ge/ge_pic.h>

व्योम __iomem *imp3a_regs;

व्योम __init ge_imp3a_pic_init(व्योम)
अणु
	काष्ठा mpic *mpic;
	काष्ठा device_node *np;
	काष्ठा device_node *cascade_node = शून्य;

	अगर (of_machine_is_compatible("fsl,MPC8572DS-CAMP")) अणु
		mpic = mpic_alloc(शून्य, 0,
			MPIC_NO_RESET |
			MPIC_BIG_ENDIAN |
			MPIC_SINGLE_DEST_CPU,
			0, 256, " OpenPIC  ");
	पूर्ण अन्यथा अणु
		mpic = mpic_alloc(शून्य, 0,
			  MPIC_BIG_ENDIAN |
			  MPIC_SINGLE_DEST_CPU,
			0, 256, " OpenPIC  ");
	पूर्ण

	BUG_ON(mpic == शून्य);
	mpic_init(mpic);
	/*
	 * There is a simple पूर्णांकerrupt handler in the मुख्य FPGA, this needs
	 * to be cascaded पूर्णांकo the MPIC
	 */
	क्रम_each_node_by_type(np, "interrupt-controller")
		अगर (of_device_is_compatible(np, "gef,fpga-pic-1.00")) अणु
			cascade_node = np;
			अवरोध;
		पूर्ण

	अगर (cascade_node == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "IMP3A: No FPGA PIC\n");
		वापस;
	पूर्ण

	gef_pic_init(cascade_node);
	of_node_put(cascade_node);
पूर्ण

अटल व्योम ge_imp3a_pci_assign_primary(व्योम)
अणु
#अगर_घोषित CONFIG_PCI
	काष्ठा device_node *np;
	काष्ठा resource rsrc;

	क्रम_each_node_by_type(np, "pci") अणु
		अगर (of_device_is_compatible(np, "fsl,mpc8540-pci") ||
		    of_device_is_compatible(np, "fsl,mpc8548-pcie") ||
		    of_device_is_compatible(np, "fsl,p2020-pcie")) अणु
			of_address_to_resource(np, 0, &rsrc);
			अगर ((rsrc.start & 0xfffff) == 0x9000)
				fsl_pci_primary = np;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * Setup the architecture
 */
अटल व्योम __init ge_imp3a_setup_arch(व्योम)
अणु
	काष्ठा device_node *regs;

	अगर (ppc_md.progress)
		ppc_md.progress("ge_imp3a_setup_arch()", 0);

	mpc85xx_smp_init();

	ge_imp3a_pci_assign_primary();

	swiotlb_detect_4g();

	/* Remap basic board रेजिस्टरs */
	regs = of_find_compatible_node(शून्य, शून्य, "ge,imp3a-fpga-regs");
	अगर (regs) अणु
		imp3a_regs = of_iomap(regs, 0);
		अगर (imp3a_regs == शून्य)
			prपूर्णांकk(KERN_WARNING "Unable to map board registers\n");
		of_node_put(regs);
	पूर्ण

#अगर defined(CONFIG_MMIO_NVRAM)
	mmio_nvram_init();
#पूर्ण_अगर

	prपूर्णांकk(KERN_INFO "GE Intelligent Platforms IMP3A 3U cPCI SBC\n");
पूर्ण

/* Return the PCB revision */
अटल अचिन्हित पूर्णांक ge_imp3a_get_pcb_rev(व्योम)
अणु
	अचिन्हित पूर्णांक reg;

	reg = ioपढ़ो16(imp3a_regs);
	वापस (reg >> 8) & 0xff;
पूर्ण

/* Return the board (software) revision */
अटल अचिन्हित पूर्णांक ge_imp3a_get_board_rev(व्योम)
अणु
	अचिन्हित पूर्णांक reg;

	reg = ioपढ़ो16(imp3a_regs + 0x2);
	वापस reg & 0xff;
पूर्ण

/* Return the FPGA revision */
अटल अचिन्हित पूर्णांक ge_imp3a_get_fpga_rev(व्योम)
अणु
	अचिन्हित पूर्णांक reg;

	reg = ioपढ़ो16(imp3a_regs + 0x2);
	वापस (reg >> 8) & 0xff;
पूर्ण

/* Return compactPCI Geographical Address */
अटल अचिन्हित पूर्णांक ge_imp3a_get_cpci_geo_addr(व्योम)
अणु
	अचिन्हित पूर्णांक reg;

	reg = ioपढ़ो16(imp3a_regs + 0x6);
	वापस (reg & 0x0f00) >> 8;
पूर्ण

/* Return compactPCI System Controller Status */
अटल अचिन्हित पूर्णांक ge_imp3a_get_cpci_is_syscon(व्योम)
अणु
	अचिन्हित पूर्णांक reg;

	reg = ioपढ़ो16(imp3a_regs + 0x6);
	वापस reg & (1 << 12);
पूर्ण

अटल व्योम ge_imp3a_show_cpuinfo(काष्ठा seq_file *m)
अणु
	seq_म_लिखो(m, "Vendor\t\t: GE Intelligent Platforms\n");

	seq_म_लिखो(m, "Revision\t: %u%c\n", ge_imp3a_get_pcb_rev(),
		('A' + ge_imp3a_get_board_rev() - 1));

	seq_म_लिखो(m, "FPGA Revision\t: %u\n", ge_imp3a_get_fpga_rev());

	seq_म_लिखो(m, "cPCI geo. addr\t: %u\n", ge_imp3a_get_cpci_geo_addr());

	seq_म_लिखो(m, "cPCI syscon\t: %s\n",
		ge_imp3a_get_cpci_is_syscon() ? "yes" : "no");
पूर्ण

/*
 * Called very early, device-tree isn't unflattened
 */
अटल पूर्णांक __init ge_imp3a_probe(व्योम)
अणु
	वापस of_machine_is_compatible("ge,IMP3A");
पूर्ण

machine_arch_initcall(ge_imp3a, mpc85xx_common_publish_devices);

define_machine(ge_imp3a) अणु
	.name			= "GE_IMP3A",
	.probe			= ge_imp3a_probe,
	.setup_arch		= ge_imp3a_setup_arch,
	.init_IRQ		= ge_imp3a_pic_init,
	.show_cpuinfo		= ge_imp3a_show_cpuinfo,
#अगर_घोषित CONFIG_PCI
	.pcibios_fixup_bus	= fsl_pcibios_fixup_bus,
	.pcibios_fixup_phb      = fsl_pcibios_fixup_phb,
#पूर्ण_अगर
	.get_irq		= mpic_get_irq,
	.calibrate_decr		= generic_calibrate_decr,
	.progress		= udbg_progress,
पूर्ण;
