<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2008 Maxime Bizon <mbizon@मुक्तbox.fr>
 * Copyright (C) 2014 Kevin Cernekee <cernekee@gmail.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/bitops.h>
#समावेश <linux/memblock.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_clk.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/libfdt.h>
#समावेश <linux/smp.h>
#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/bmips.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/cpu-type.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/smp-ops.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/traps.h>

#घोषणा RELO_NORMAL_VEC		BIT(18)

#घोषणा REG_BCM6328_OTP		((व्योम __iomem *)CKSEG1ADDR(0x1000062c))
#घोषणा BCM6328_TP1_DISABLED	BIT(9)

अटल स्थिर अचिन्हित दीर्घ kbase = VMLINUX_LOAD_ADDRESS & 0xfff00000;

काष्ठा bmips_quirk अणु
	स्थिर अक्षर		*compatible;
	व्योम			(*quirk_fn)(व्योम);
पूर्ण;

अटल व्योम kbase_setup(व्योम)
अणु
	__raw_ग_लिखोl(kbase | RELO_NORMAL_VEC,
		     BMIPS_GET_CBR() + BMIPS_RELO_VECTOR_CONTROL_1);
	ebase = kbase;
पूर्ण

अटल व्योम bcm3384_viper_quirks(व्योम)
अणु
	/*
	 * Some experimental CM boxes are set up to let CM own the Viper TP0
	 * and let Linux own TP1.  This requires moving the kernel
	 * load address to a non-conflicting region (e.g. via
	 * CONFIG_PHYSICAL_START) and supplying an alternate DTB.
	 * If we detect this condition, we need to move the MIPS exception
	 * vectors up to an area that we own.
	 *
	 * This is distinct from the OTHER special हाल mentioned in
	 * smp-bmips.c (boot on TP1, but enable SMP, then TP0 becomes our
	 * logical CPU#1).  For the Viper TP1 हाल, SMP is off limits.
	 *
	 * Also note that many BMIPS435x CPUs करो not have a
	 * BMIPS_RELO_VECTOR_CONTROL_1 रेजिस्टर, so it isn't safe to just
	 * ग_लिखो VMLINUX_LOAD_ADDRESS पूर्णांकo that रेजिस्टर on every SoC.
	 */
	board_ebase_setup = &kbase_setup;
	bmips_smp_enabled = 0;
पूर्ण

अटल व्योम bcm63xx_fixup_cpu1(व्योम)
अणु
	/*
	 * The bootloader has set up the CPU1 reset vector at
	 * 0xa000_0200.
	 * This conflicts with the special पूर्णांकerrupt vector (IV).
	 * The bootloader has also set up CPU1 to respond to the wrong
	 * IPI पूर्णांकerrupt.
	 * Here we will start up CPU1 in the background and ask it to
	 * reconfigure itself then go back to sleep.
	 */
	स_नकल((व्योम *)0xa0000200, &bmips_smp_movevec, 0x20);
	__sync();
	set_c0_cause(C_SW0);
	cpumask_set_cpu(1, &bmips_booted_mask);
पूर्ण

अटल व्योम bcm6328_quirks(व्योम)
अणु
	/* Check CPU1 status in OTP (it is usually disabled) */
	अगर (__raw_पढ़ोl(REG_BCM6328_OTP) & BCM6328_TP1_DISABLED)
		bmips_smp_enabled = 0;
	अन्यथा
		bcm63xx_fixup_cpu1();
पूर्ण

अटल व्योम bcm6358_quirks(व्योम)
अणु
	/*
	 * BCM3368/BCM6358 need special handling क्रम their shared TLB, so
	 * disable SMP क्रम now
	 */
	bmips_smp_enabled = 0;
पूर्ण

अटल व्योम bcm6368_quirks(व्योम)
अणु
	bcm63xx_fixup_cpu1();
पूर्ण

अटल स्थिर काष्ठा bmips_quirk bmips_quirk_list[] = अणु
	अणु "brcm,bcm3368",		&bcm6358_quirks			पूर्ण,
	अणु "brcm,bcm3384-viper",		&bcm3384_viper_quirks		पूर्ण,
	अणु "brcm,bcm33843-viper",	&bcm3384_viper_quirks		पूर्ण,
	अणु "brcm,bcm6328",		&bcm6328_quirks			पूर्ण,
	अणु "brcm,bcm6358",		&bcm6358_quirks			पूर्ण,
	अणु "brcm,bcm6362",		&bcm6368_quirks			पूर्ण,
	अणु "brcm,bcm6368",		&bcm6368_quirks			पूर्ण,
	अणु "brcm,bcm63168",		&bcm6368_quirks			पूर्ण,
	अणु "brcm,bcm63268",		&bcm6368_quirks			पूर्ण,
	अणु पूर्ण,
पूर्ण;

व्योम __init prom_init(व्योम)
अणु
	bmips_cpu_setup();
	रेजिस्टर_bmips_smp_ops();
पूर्ण

स्थिर अक्षर *get_प्रणाली_type(व्योम)
अणु
	वापस "Generic BMIPS kernel";
पूर्ण

व्योम __init plat_समय_init(व्योम)
अणु
	काष्ठा device_node *np;
	u32 freq;

	np = of_find_node_by_name(शून्य, "cpus");
	अगर (!np)
		panic("missing 'cpus' DT node");
	अगर (of_property_पढ़ो_u32(np, "mips-hpt-frequency", &freq) < 0)
		panic("missing 'mips-hpt-frequency' property");
	of_node_put(np);

	mips_hpt_frequency = freq;
पूर्ण

व्योम __init plat_mem_setup(व्योम)
अणु
	व्योम *dtb;
	स्थिर काष्ठा bmips_quirk *q;

	set_io_port_base(0);
	ioport_resource.start = 0;
	ioport_resource.end = ~0;

	/* पूर्णांकended to somewhat resemble ARM; see Documentation/arm/booting.rst */
	अगर (fw_arg0 == 0 && fw_arg1 == 0xffffffff)
		dtb = phys_to_virt(fw_arg2);
	अन्यथा
		dtb = get_fdt();

	अगर (!dtb)
		panic("no dtb found");

	__dt_setup_arch(dtb);

	क्रम (q = bmips_quirk_list; q->quirk_fn; q++) अणु
		अगर (of_flat_dt_is_compatible(of_get_flat_dt_root(),
					     q->compatible)) अणु
			q->quirk_fn();
		पूर्ण
	पूर्ण
पूर्ण

व्योम __init device_tree_init(व्योम)
अणु
	काष्ठा device_node *np;

	unflatten_and_copy_device_tree();

	/* Disable SMP boot unless both CPUs are listed in DT and !disabled */
	np = of_find_node_by_name(शून्य, "cpus");
	अगर (np && of_get_available_child_count(np) <= 1)
		bmips_smp_enabled = 0;
	of_node_put(np);
पूर्ण

अटल पूर्णांक __init plat_dev_init(व्योम)
अणु
	of_clk_init(शून्य);
	वापस 0;
पूर्ण

arch_initcall(plat_dev_init);
