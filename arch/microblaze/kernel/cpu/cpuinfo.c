<शैली गुरु>
/*
 * Copyright (C) 2007-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2007-2009 PetaLogix
 * Copyright (C) 2007 John Williams <john.williams@petalogix.com>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/clk.h>
#समावेश <linux/init.h>
#समावेश <यंत्र/cpuinfo.h>
#समावेश <यंत्र/pvr.h>

स्थिर काष्ठा cpu_ver_key cpu_ver_lookup[] = अणु
	/* These key value are as per MBV field in PVR0 */
	अणु"5.00.a", 0x01पूर्ण,
	अणु"5.00.b", 0x02पूर्ण,
	अणु"5.00.c", 0x03पूर्ण,
	अणु"6.00.a", 0x04पूर्ण,
	अणु"6.00.b", 0x06पूर्ण,
	अणु"7.00.a", 0x05पूर्ण,
	अणु"7.00.b", 0x07पूर्ण,
	अणु"7.10.a", 0x08पूर्ण,
	अणु"7.10.b", 0x09पूर्ण,
	अणु"7.10.c", 0x0aपूर्ण,
	अणु"7.10.d", 0x0bपूर्ण,
	अणु"7.20.a", 0x0cपूर्ण,
	अणु"7.20.b", 0x0dपूर्ण,
	अणु"7.20.c", 0x0eपूर्ण,
	अणु"7.20.d", 0x0fपूर्ण,
	अणु"7.30.a", 0x10पूर्ण,
	अणु"7.30.b", 0x11पूर्ण,
	अणु"8.00.a", 0x12पूर्ण,
	अणु"8.00.b", 0x13पूर्ण,
	अणु"8.10.a", 0x14पूर्ण,
	अणु"8.20.a", 0x15पूर्ण,
	अणु"8.20.b", 0x16पूर्ण,
	अणु"8.30.a", 0x17पूर्ण,
	अणु"8.40.a", 0x18पूर्ण,
	अणु"8.40.b", 0x19पूर्ण,
	अणु"8.50.a", 0x1aपूर्ण,
	अणु"8.50.b", 0x1cपूर्ण,
	अणु"8.50.c", 0x1eपूर्ण,
	अणु"9.0", 0x1bपूर्ण,
	अणु"9.1", 0x1dपूर्ण,
	अणु"9.2", 0x1fपूर्ण,
	अणु"9.3", 0x20पूर्ण,
	अणु"9.4", 0x21पूर्ण,
	अणु"9.5", 0x22पूर्ण,
	अणु"9.6", 0x23पूर्ण,
	अणु"10.0", 0x24पूर्ण,
	अणु"11.0", 0x25पूर्ण,
	अणुशून्य, 0पूर्ण,
पूर्ण;

/*
 * FIXME Not sure अगर the actual key is defined by Xilinx in the PVR
 */
स्थिर काष्ठा family_string_key family_string_lookup[] = अणु
	अणु"virtex2", 0x4पूर्ण,
	अणु"virtex2pro", 0x5पूर्ण,
	अणु"spartan3", 0x6पूर्ण,
	अणु"virtex4", 0x7पूर्ण,
	अणु"virtex5", 0x8पूर्ण,
	अणु"spartan3e", 0x9पूर्ण,
	अणु"spartan3a", 0xaपूर्ण,
	अणु"spartan3an", 0xbपूर्ण,
	अणु"spartan3adsp", 0xcपूर्ण,
	अणु"spartan6", 0xdपूर्ण,
	अणु"virtex6", 0xeपूर्ण,
	अणु"virtex7", 0xfपूर्ण,
	/* FIXME There is no key code defined क्रम spartan2 */
	अणु"spartan2", 0xf0पूर्ण,
	अणु"kintex7", 0x10पूर्ण,
	अणु"artix7", 0x11पूर्ण,
	अणु"zynq7000", 0x12पूर्ण,
	अणु"UltraScale Virtex", 0x13पूर्ण,
	अणु"UltraScale Kintex", 0x14पूर्ण,
	अणु"UltraScale+ Zynq", 0x15पूर्ण,
	अणु"UltraScale+ Virtex", 0x16पूर्ण,
	अणु"UltraScale+ Kintex", 0x17पूर्ण,
	अणु"Spartan7", 0x18पूर्ण,
	अणुशून्य, 0पूर्ण,
पूर्ण;

काष्ठा cpuinfo cpuinfo;
अटल काष्ठा device_node *cpu;

व्योम __init setup_cpuinfo(व्योम)
अणु
	cpu = of_get_cpu_node(0, शून्य);
	अगर (!cpu)
		pr_err("You don't have cpu or are missing cpu reg property!!!\n");

	pr_info("%s: initialising\n", __func__);

	चयन (cpu_has_pvr()) अणु
	हाल 0:
		pr_warn("%s: No PVR support. Using static CPU info from FDT\n",
			__func__);
		set_cpuinfo_अटल(&cpuinfo, cpu);
		अवरोध;
/* FIXME I found weird behavior with MB 7.00.a/b 7.10.a
 * please करो not use FULL PVR with MMU */
	हाल 1:
		pr_info("%s: Using full CPU PVR support\n",
			__func__);
		set_cpuinfo_अटल(&cpuinfo, cpu);
		set_cpuinfo_pvr_full(&cpuinfo, cpu);
		अवरोध;
	शेष:
		pr_warn("%s: Unsupported PVR setting\n", __func__);
		set_cpuinfo_अटल(&cpuinfo, cpu);
	पूर्ण

	अगर (cpuinfo.mmu_privins)
		pr_warn("%s: Stream instructions enabled"
			" - USERSPACE CAN LOCK THIS KERNEL!\n", __func__);

	of_node_put(cpu);
पूर्ण

व्योम __init setup_cpuinfo_clk(व्योम)
अणु
	काष्ठा clk *clk;

	clk = of_clk_get(cpu, 0);
	अगर (IS_ERR(clk)) अणु
		pr_err("ERROR: CPU CCF input clock not found\n");
		/* take समयbase-frequency from DTS */
		cpuinfo.cpu_घड़ी_freq = fcpu(cpu, "timebase-frequency");
	पूर्ण अन्यथा अणु
		cpuinfo.cpu_घड़ी_freq = clk_get_rate(clk);
	पूर्ण

	अगर (!cpuinfo.cpu_घड़ी_freq) अणु
		pr_err("ERROR: CPU clock frequency not setup\n");
		BUG();
	पूर्ण
पूर्ण
