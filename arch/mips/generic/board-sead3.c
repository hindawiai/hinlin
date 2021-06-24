<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Imagination Technologies
 * Author: Paul Burton <paul.burton@mips.com>
 */

#घोषणा pr_fmt(fmt) "sead3: " fmt

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/libfdt.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/sizes.h>

#समावेश <यंत्र/fw/fw.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/machine.h>
#समावेश <यंत्र/yamon-dt.h>

#घोषणा SEAD_CONFIG			CKSEG1ADDR(0x1b100110)
#घोषणा SEAD_CONFIG_GIC_PRESENT		BIT(1)

#घोषणा MIPS_REVISION			CKSEG1ADDR(0x1fc00010)
#घोषणा MIPS_REVISION_MACHINE		(0xf << 4)
#घोषणा MIPS_REVISION_MACHINE_SEAD3	(0x4 << 4)

/*
 * Maximum 384MB RAM at physical address 0, preceding any I/O.
 */
अटल काष्ठा yamon_mem_region mem_regions[] __initdata = अणु
	/* start	size */
	अणु 0,		SZ_256M + SZ_128M पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल __init bool sead3_detect(व्योम)
अणु
	uपूर्णांक32_t rev;

	rev = __raw_पढ़ोl((व्योम *)MIPS_REVISION);
	वापस (rev & MIPS_REVISION_MACHINE) == MIPS_REVISION_MACHINE_SEAD3;
पूर्ण

अटल __init पूर्णांक append_memory(व्योम *fdt)
अणु
	वापस yamon_dt_append_memory(fdt, mem_regions);
पूर्ण

अटल __init पूर्णांक हटाओ_gic(व्योम *fdt)
अणु
	स्थिर अचिन्हित पूर्णांक cpu_ehci_पूर्णांक = 2;
	स्थिर अचिन्हित पूर्णांक cpu_uart_पूर्णांक = 4;
	स्थिर अचिन्हित पूर्णांक cpu_eth_पूर्णांक = 6;
	पूर्णांक gic_off, cpu_off, uart_off, eth_off, ehci_off, err;
	uपूर्णांक32_t cfg, cpu_phandle;

	/* leave the GIC node पूर्णांकact अगर a GIC is present */
	cfg = __raw_पढ़ोl((uपूर्णांक32_t *)SEAD_CONFIG);
	अगर (cfg & SEAD_CONFIG_GIC_PRESENT)
		वापस 0;

	gic_off = fdt_node_offset_by_compatible(fdt, -1, "mti,gic");
	अगर (gic_off < 0) अणु
		pr_err("unable to find DT GIC node: %d\n", gic_off);
		वापस gic_off;
	पूर्ण

	err = fdt_nop_node(fdt, gic_off);
	अगर (err) अणु
		pr_err("unable to nop GIC node\n");
		वापस err;
	पूर्ण

	cpu_off = fdt_node_offset_by_compatible(fdt, -1,
			"mti,cpu-interrupt-controller");
	अगर (cpu_off < 0) अणु
		pr_err("unable to find CPU intc node: %d\n", cpu_off);
		वापस cpu_off;
	पूर्ण

	cpu_phandle = fdt_get_phandle(fdt, cpu_off);
	अगर (!cpu_phandle) अणु
		pr_err("unable to get CPU intc phandle\n");
		वापस -EINVAL;
	पूर्ण

	uart_off = fdt_node_offset_by_compatible(fdt, -1, "ns16550a");
	जबतक (uart_off >= 0) अणु
		err = fdt_setprop_u32(fdt, uart_off, "interrupt-parent",
				      cpu_phandle);
		अगर (err) अणु
			pr_warn("unable to set UART interrupt-parent: %d\n",
				err);
			वापस err;
		पूर्ण

		err = fdt_setprop_u32(fdt, uart_off, "interrupts",
				      cpu_uart_पूर्णांक);
		अगर (err) अणु
			pr_err("unable to set UART interrupts property: %d\n",
			       err);
			वापस err;
		पूर्ण

		uart_off = fdt_node_offset_by_compatible(fdt, uart_off,
							 "ns16550a");
	पूर्ण
	अगर (uart_off != -FDT_ERR_NOTFOUND) अणु
		pr_err("error searching for UART DT node: %d\n", uart_off);
		वापस uart_off;
	पूर्ण

	eth_off = fdt_node_offset_by_compatible(fdt, -1, "smsc,lan9115");
	अगर (eth_off < 0) अणु
		pr_err("unable to find ethernet DT node: %d\n", eth_off);
		वापस eth_off;
	पूर्ण

	err = fdt_setprop_u32(fdt, eth_off, "interrupt-parent", cpu_phandle);
	अगर (err) अणु
		pr_err("unable to set ethernet interrupt-parent: %d\n", err);
		वापस err;
	पूर्ण

	err = fdt_setprop_u32(fdt, eth_off, "interrupts", cpu_eth_पूर्णांक);
	अगर (err) अणु
		pr_err("unable to set ethernet interrupts property: %d\n", err);
		वापस err;
	पूर्ण

	ehci_off = fdt_node_offset_by_compatible(fdt, -1, "generic-ehci");
	अगर (ehci_off < 0) अणु
		pr_err("unable to find EHCI DT node: %d\n", ehci_off);
		वापस ehci_off;
	पूर्ण

	err = fdt_setprop_u32(fdt, ehci_off, "interrupt-parent", cpu_phandle);
	अगर (err) अणु
		pr_err("unable to set EHCI interrupt-parent: %d\n", err);
		वापस err;
	पूर्ण

	err = fdt_setprop_u32(fdt, ehci_off, "interrupts", cpu_ehci_पूर्णांक);
	अगर (err) अणु
		pr_err("unable to set EHCI interrupts property: %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mips_fdt_fixup sead3_fdt_fixups[] __initस्थिर = अणु
	अणु yamon_dt_append_cmdline, "append command line" पूर्ण,
	अणु append_memory, "append memory" पूर्ण,
	अणु हटाओ_gic, "remove GIC when not present" पूर्ण,
	अणु yamon_dt_serial_config, "append serial configuration" पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल __init स्थिर व्योम *sead3_fixup_fdt(स्थिर व्योम *fdt,
					  स्थिर व्योम *match_data)
अणु
	अटल अचिन्हित अक्षर fdt_buf[16 << 10] __initdata;
	पूर्णांक err;

	अगर (fdt_check_header(fdt))
		panic("Corrupt DT");

	/* अगर this isn't SEAD3, something went wrong */
	BUG_ON(fdt_node_check_compatible(fdt, 0, "mti,sead-3"));

	fw_init_cmdline();

	err = apply_mips_fdt_fixups(fdt_buf, माप(fdt_buf),
				    fdt, sead3_fdt_fixups);
	अगर (err)
		panic("Unable to fixup FDT: %d", err);

	वापस fdt_buf;
पूर्ण

अटल __init अचिन्हित पूर्णांक sead3_measure_hpt_freq(व्योम)
अणु
	व्योम __iomem *status_reg = (व्योम __iomem *)0xbf000410;
	अचिन्हित पूर्णांक freq, orig, tick = 0;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	orig = पढ़ोl(status_reg) & 0x2;		      /* get original sample */
	/* रुको क्रम transition */
	जबतक ((पढ़ोl(status_reg) & 0x2) == orig)
		;
	orig = orig ^ 0x2;			      /* flip the bit */

	ग_लिखो_c0_count(0);

	/* रुको 1 second (the sampling घड़ी transitions every 10ms) */
	जबतक (tick < 100) अणु
		/* रुको क्रम transition */
		जबतक ((पढ़ोl(status_reg) & 0x2) == orig)
			;
		orig = orig ^ 0x2;			      /* flip the bit */
		tick++;
	पूर्ण

	freq = पढ़ो_c0_count();

	local_irq_restore(flags);

	वापस freq;
पूर्ण

बाह्य अक्षर __dtb_sead3_begin[];

MIPS_MACHINE(sead3) = अणु
	.fdt = __dtb_sead3_begin,
	.detect = sead3_detect,
	.fixup_fdt = sead3_fixup_fdt,
	.measure_hpt_freq = sead3_measure_hpt_freq,
पूर्ण;
