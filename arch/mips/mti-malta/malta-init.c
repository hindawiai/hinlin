<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * PROM library initialisation code.
 *
 * Copyright (C) 1999,2000,2004,2005,2012  MIPS Technologies, Inc.
 * All rights reserved.
 * Authors: Carsten Langgaard <carstenl@mips.com>
 *         Maciej W. Rozycki <macro@mips.com>
 *          Steven J. Hill <sjhill@mips.com>
 */
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/pci_regs.h>
#समावेश <linux/serial_core.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/smp-ops.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/fw/fw.h>
#समावेश <यंत्र/mips-cps.h>
#समावेश <यंत्र/mips-boards/generic.h>
#समावेश <यंत्र/mips-boards/malta.h>

अटल पूर्णांक mips_revision_corid;
पूर्णांक mips_revision_sconid;

/* Bonito64 प्रणाली controller रेजिस्टर base. */
अचिन्हित दीर्घ _pcictrl_bonito;
अचिन्हित दीर्घ _pcictrl_bonito_pcicfg;

/* GT64120 प्रणाली controller रेजिस्टर base */
अचिन्हित दीर्घ _pcictrl_gt64120;

/* MIPS System controller रेजिस्टर base */
अचिन्हित दीर्घ _pcictrl_msc;

#अगर_घोषित CONFIG_SERIAL_8250_CONSOLE
अटल व्योम __init console_config(व्योम)
अणु
	अक्षर console_string[40];
	पूर्णांक baud = 0;
	अक्षर parity = '\0', bits = '\0', flow = '\0';
	अक्षर *s;

	s = fw_दो_पर्या("modetty0");
	अगर (s) अणु
		जबतक (*s >= '0' && *s <= '9')
			baud = baud*10 + *s++ - '0';
		अगर (*s == ',')
			s++;
		अगर (*s)
			parity = *s++;
		अगर (*s == ',')
			s++;
		अगर (*s)
			bits = *s++;
		अगर (*s == ',')
			s++;
		अगर (*s == 'h')
			flow = 'r';
	पूर्ण
	अगर (baud == 0)
		baud = 38400;
	अगर (parity != 'n' && parity != 'o' && parity != 'e')
		parity = 'n';
	अगर (bits != '7' && bits != '8')
		bits = '8';
	अगर (flow == '\0')
		flow = 'r';

	अगर ((म_माला(fw_अ_लोmdline(), "earlycon=")) == शून्य) अणु
		प्र_लिखो(console_string, "uart8250,io,0x3f8,%d%c%c", baud,
			parity, bits);
		setup_earlycon(console_string);
	पूर्ण

	अगर ((म_माला(fw_अ_लोmdline(), "console=")) == शून्य) अणु
		प्र_लिखो(console_string, " console=ttyS0,%d%c%c%c", baud,
			parity, bits, flow);
		म_जोड़ो(fw_अ_लोmdline(), console_string);
		pr_info("Config serial console:%s\n", console_string);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल व्योम __init mips_nmi_setup(व्योम)
अणु
	व्योम *base;

	base = cpu_has_veic ?
		(व्योम *)(CAC_BASE + 0xa80) :
		(व्योम *)(CAC_BASE + 0x380);
	स_नकल(base, except_vec_nmi, 0x80);
	flush_icache_range((अचिन्हित दीर्घ)base, (अचिन्हित दीर्घ)base + 0x80);
पूर्ण

अटल व्योम __init mips_ejtag_setup(व्योम)
अणु
	व्योम *base;
	बाह्य अक्षर except_vec_ejtag_debug[];

	base = cpu_has_veic ?
		(व्योम *)(CAC_BASE + 0xa00) :
		(व्योम *)(CAC_BASE + 0x300);
	स_नकल(base, except_vec_ejtag_debug, 0x80);
	flush_icache_range((अचिन्हित दीर्घ)base, (अचिन्हित दीर्घ)base + 0x80);
पूर्ण

phys_addr_t mips_cpc_शेष_phys_base(व्योम)
अणु
	वापस CPC_BASE_ADDR;
पूर्ण

व्योम __init prom_init(व्योम)
अणु
	/*
	 * early setup of _pcictrl_bonito so that we can determine
	 * the प्रणाली controller on a CORE_EMUL board
	 */
	_pcictrl_bonito = (अचिन्हित दीर्घ)ioremap(BONITO_REG_BASE, BONITO_REG_SIZE);

	mips_revision_corid = MIPS_REVISION_CORID;

	अगर (mips_revision_corid == MIPS_REVISION_CORID_CORE_EMUL) अणु
		अगर (BONITO_PCIDID == 0x0001df53 ||
		    BONITO_PCIDID == 0x0003df53)
			mips_revision_corid = MIPS_REVISION_CORID_CORE_EMUL_BON;
		अन्यथा
			mips_revision_corid = MIPS_REVISION_CORID_CORE_EMUL_MSC;
	पूर्ण

	mips_revision_sconid = MIPS_REVISION_SCONID;
	अगर (mips_revision_sconid == MIPS_REVISION_SCON_OTHER) अणु
		चयन (mips_revision_corid) अणु
		हाल MIPS_REVISION_CORID_QED_RM5261:
		हाल MIPS_REVISION_CORID_CORE_LV:
		हाल MIPS_REVISION_CORID_CORE_FPGA:
		हाल MIPS_REVISION_CORID_CORE_FPGAR2:
			mips_revision_sconid = MIPS_REVISION_SCON_GT64120;
			अवरोध;
		हाल MIPS_REVISION_CORID_CORE_EMUL_BON:
		हाल MIPS_REVISION_CORID_BONITO64:
		हाल MIPS_REVISION_CORID_CORE_20K:
			mips_revision_sconid = MIPS_REVISION_SCON_BONITO;
			अवरोध;
		हाल MIPS_REVISION_CORID_CORE_MSC:
		हाल MIPS_REVISION_CORID_CORE_FPGA2:
		हाल MIPS_REVISION_CORID_CORE_24K:
			/*
			 * SOCit/ROCit support is essentially identical
			 * but make an attempt to distinguish them
			 */
			mips_revision_sconid = MIPS_REVISION_SCON_SOCIT;
			अवरोध;
		हाल MIPS_REVISION_CORID_CORE_FPGA3:
		हाल MIPS_REVISION_CORID_CORE_FPGA4:
		हाल MIPS_REVISION_CORID_CORE_FPGA5:
		हाल MIPS_REVISION_CORID_CORE_EMUL_MSC:
		शेष:
			/* See above */
			mips_revision_sconid = MIPS_REVISION_SCON_ROCIT;
			अवरोध;
		पूर्ण
	पूर्ण

	चयन (mips_revision_sconid) अणु
		u32 start, map, mask, data;

	हाल MIPS_REVISION_SCON_GT64120:
		/*
		 * Setup the North bridge to करो Master byte-lane swapping
		 * when running in bigendian.
		 */
		_pcictrl_gt64120 = (अचिन्हित दीर्घ)ioremap(MIPS_GT_BASE, 0x2000);

#अगर_घोषित CONFIG_CPU_LITTLE_ENDIAN
		GT_WRITE(GT_PCI0_CMD_OFS, GT_PCI0_CMD_MBYTESWAP_BIT |
			 GT_PCI0_CMD_SBYTESWAP_BIT);
#अन्यथा
		GT_WRITE(GT_PCI0_CMD_OFS, 0);
#पूर्ण_अगर
		/* Fix up PCI I/O mapping अगर necessary (क्रम Atlas).  */
		start = GT_READ(GT_PCI0IOLD_OFS);
		map = GT_READ(GT_PCI0IOREMAP_OFS);
		अगर ((start & map) != 0) अणु
			map &= ~start;
			GT_WRITE(GT_PCI0IOREMAP_OFS, map);
		पूर्ण

		set_io_port_base(MALTA_GT_PORT_BASE);
		अवरोध;

	हाल MIPS_REVISION_SCON_BONITO:
		_pcictrl_bonito_pcicfg = (अचिन्हित दीर्घ)ioremap(BONITO_PCICFG_BASE, BONITO_PCICFG_SIZE);

		/*
		 * Disable Bonito IOBC.
		 */
		BONITO_PCIMEMBASECFG = BONITO_PCIMEMBASECFG &
			~(BONITO_PCIMEMBASECFG_MEMBASE0_CACHED |
			  BONITO_PCIMEMBASECFG_MEMBASE1_CACHED);

		/*
		 * Setup the North bridge to करो Master byte-lane swapping
		 * when running in bigendian.
		 */
#अगर_घोषित CONFIG_CPU_LITTLE_ENDIAN
		BONITO_BONGENCFG = BONITO_BONGENCFG &
			~(BONITO_BONGENCFG_MSTRBYTESWAP |
			  BONITO_BONGENCFG_BYTESWAP);
#अन्यथा
		BONITO_BONGENCFG = BONITO_BONGENCFG |
			BONITO_BONGENCFG_MSTRBYTESWAP |
			BONITO_BONGENCFG_BYTESWAP;
#पूर्ण_अगर

		set_io_port_base(MALTA_BONITO_PORT_BASE);
		अवरोध;

	हाल MIPS_REVISION_SCON_SOCIT:
	हाल MIPS_REVISION_SCON_ROCIT:
		_pcictrl_msc = (अचिन्हित दीर्घ)ioremap(MIPS_MSC01_PCI_REG_BASE, 0x2000);
mips_pci_controller:
		mb();
		MSC_READ(MSC01_PCI_CFG, data);
		MSC_WRITE(MSC01_PCI_CFG, data & ~MSC01_PCI_CFG_EN_BIT);
		wmb();

		/* Fix up lane swapping.  */
#अगर_घोषित CONFIG_CPU_LITTLE_ENDIAN
		MSC_WRITE(MSC01_PCI_SWAP, MSC01_PCI_SWAP_NOSWAP);
#अन्यथा
		MSC_WRITE(MSC01_PCI_SWAP,
			  MSC01_PCI_SWAP_BYTESWAP << MSC01_PCI_SWAP_IO_SHF |
			  MSC01_PCI_SWAP_BYTESWAP << MSC01_PCI_SWAP_MEM_SHF |
			  MSC01_PCI_SWAP_BYTESWAP << MSC01_PCI_SWAP_BAR0_SHF);
#पूर्ण_अगर

		/*
		 * Setup the Malta max (2GB) memory क्रम PCI DMA in host bridge
		 * in transparent addressing mode.
		 */
		mask = PHYS_OFFSET | PCI_BASE_ADDRESS_MEM_PREFETCH;
		MSC_WRITE(MSC01_PCI_BAR0, mask);
		MSC_WRITE(MSC01_PCI_HEAD4, mask);

		mask &= MSC01_PCI_BAR0_SIZE_MSK;
		MSC_WRITE(MSC01_PCI_P2SCMSKL, mask);
		MSC_WRITE(MSC01_PCI_P2SCMAPL, mask);

		/* Don't handle target retries indefinitely.  */
		अगर ((data & MSC01_PCI_CFG_MAXRTRY_MSK) ==
		    MSC01_PCI_CFG_MAXRTRY_MSK)
			data = (data & ~(MSC01_PCI_CFG_MAXRTRY_MSK <<
					 MSC01_PCI_CFG_MAXRTRY_SHF)) |
			       ((MSC01_PCI_CFG_MAXRTRY_MSK - 1) <<
				MSC01_PCI_CFG_MAXRTRY_SHF);

		wmb();
		MSC_WRITE(MSC01_PCI_CFG, data);
		mb();

		set_io_port_base(MALTA_MSC_PORT_BASE);
		अवरोध;

	हाल MIPS_REVISION_SCON_SOCITSC:
	हाल MIPS_REVISION_SCON_SOCITSCP:
		_pcictrl_msc = (अचिन्हित दीर्घ)ioremap(MIPS_SOCITSC_PCI_REG_BASE, 0x2000);
		जाओ mips_pci_controller;

	शेष:
		/* Unknown प्रणाली controller */
		जबतक (1);	/* We die here... */
	पूर्ण
	board_nmi_handler_setup = mips_nmi_setup;
	board_ejtag_handler_setup = mips_ejtag_setup;

	fw_init_cmdline();
	fw_meminit();
#अगर_घोषित CONFIG_SERIAL_8250_CONSOLE
	console_config();
#पूर्ण_अगर
	/* Early detection of CMP support */
	mips_cpc_probe();

	अगर (!रेजिस्टर_cps_smp_ops())
		वापस;
	अगर (!रेजिस्टर_cmp_smp_ops())
		वापस;
	अगर (!रेजिस्टर_vsmp_smp_ops())
		वापस;
	रेजिस्टर_up_smp_ops();
पूर्ण
