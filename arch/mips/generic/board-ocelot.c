<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/*
 * Microsemi MIPS SoC support
 *
 * Copyright (c) 2017 Microsemi Corporation
 */
#समावेश <यंत्र/machine.h>
#समावेश <यंत्र/prom.h>

#घोषणा DEVCPU_GCB_CHIP_REGS_CHIP_ID	0x71070000
#घोषणा CHIP_ID_PART_ID			GENMASK(27, 12)

#घोषणा OCELOT_PART_ID			(0x7514 << 12)

#घोषणा UART_UART			0x70100000

अटल __init bool ocelot_detect(व्योम)
अणु
	u32 rev;
	पूर्णांक idx;

	/* Look क्रम the TLB entry set up by redboot beक्रमe trying to use it */
	ग_लिखो_c0_entryhi(DEVCPU_GCB_CHIP_REGS_CHIP_ID);
	mtc0_tlbw_hazard();
	tlb_probe();
	tlb_probe_hazard();
	idx = पढ़ो_c0_index();
	अगर (idx < 0)
		वापस 0;

	/* A TLB entry exists, lets assume its usable and check the CHIP ID */
	rev = __raw_पढ़ोl((व्योम __iomem *)DEVCPU_GCB_CHIP_REGS_CHIP_ID);

	अगर ((rev & CHIP_ID_PART_ID) != OCELOT_PART_ID)
		वापस 0;

	/* Copy command line from bootloader early क्रम Initrd detection */
	अगर (fw_arg0 < 10 && (fw_arg1 & 0xFFF00000) == 0x80000000) अणु
		अचिन्हित पूर्णांक prom_argc = fw_arg0;
		स्थिर अक्षर **prom_argv = (स्थिर अक्षर **)fw_arg1;

		अगर (prom_argc > 1 && म_माप(prom_argv[1]) > 0)
			/* ignore all built-in args अगर any f/w args given */
			म_नकल(arcs_cmdline, prom_argv[1]);
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम __init ocelot_earlyprपूर्णांकk_init(व्योम)
अणु
	व्योम __iomem *uart_base;

	uart_base = ioremap(UART_UART, 0x20);
	setup_8250_early_prपूर्णांकk_port((अचिन्हित दीर्घ)uart_base, 2, 50000);
पूर्ण

अटल व्योम __init ocelot_late_init(व्योम)
अणु
	ocelot_earlyprपूर्णांकk_init();
पूर्ण

अटल __init स्थिर व्योम *ocelot_fixup_fdt(स्थिर व्योम *fdt,
					   स्थिर व्योम *match_data)
अणु
	/* This has to be करोne so late because ioremap needs to work */
	late_समय_init = ocelot_late_init;

	वापस fdt;
पूर्ण

बाह्य अक्षर __dtb_ocelot_pcb123_begin[];

MIPS_MACHINE(ocelot) = अणु
	.fdt = __dtb_ocelot_pcb123_begin,
	.fixup_fdt = ocelot_fixup_fdt,
	.detect = ocelot_detect,
पूर्ण;
