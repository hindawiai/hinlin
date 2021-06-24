<शैली गुरु>
/*
 * Copyright 2003-2011 NetLogic Microप्रणालीs, Inc. (NetLogic). All rights
 * reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the NetLogic
 * license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY NETLOGIC ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL NETLOGIC OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/idle.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/bootinfo.h>

#समावेश <यंत्र/netlogic/haldefs.h>
#समावेश <यंत्र/netlogic/common.h>

#समावेश <यंत्र/netlogic/xlp-hal/iomap.h>
#समावेश <यंत्र/netlogic/xlp-hal/xlp.h>
#समावेश <यंत्र/netlogic/xlp-hal/sys.h>

uपूर्णांक64_t nlm_io_base;
काष्ठा nlm_soc_info nlm_nodes[NLM_NR_NODES];
cpumask_t nlm_cpumask = CPU_MASK_CPU0;
अचिन्हित पूर्णांक nlm_thपढ़ोs_per_core;

अटल व्योम nlm_linux_निकास(व्योम)
अणु
	uपूर्णांक64_t sysbase = nlm_get_node(0)->sysbase;

	अगर (cpu_is_xlp9xx())
		nlm_ग_लिखो_sys_reg(sysbase, SYS_9XX_CHIP_RESET, 1);
	अन्यथा
		nlm_ग_लिखो_sys_reg(sysbase, SYS_CHIP_RESET, 1);
	क्रम ( ; ; )
		cpu_रुको();
पूर्ण

अटल व्योम nlm_fixup_mem(व्योम)
अणु
	स्थिर पूर्णांक pref_backup = 512;
	काष्ठा memblock_region *mem;

	क्रम_each_mem_region(mem) अणु
		memblock_हटाओ(mem->base + mem->size - pref_backup,
			pref_backup);
	पूर्ण
पूर्ण

अटल व्योम __init xlp_init_mem_from_bars(व्योम)
अणु
	uपूर्णांक64_t map[16];
	पूर्णांक i, n;

	n = nlm_get_dram_map(-1, map, ARRAY_SIZE(map));	/* -1 : all nodes */
	क्रम (i = 0; i < n; i += 2) अणु
		/* exclude 0x1000_0000-0x2000_0000, u-boot device */
		अगर (map[i] <= 0x10000000 && map[i+1] > 0x10000000)
			map[i+1] = 0x10000000;
		अगर (map[i] > 0x10000000 && map[i] < 0x20000000)
			map[i] = 0x20000000;

		memblock_add(map[i], map[i+1] - map[i]);
	पूर्ण
पूर्ण

व्योम __init plat_mem_setup(व्योम)
अणु
#अगर_घोषित CONFIG_SMP
	nlm_wakeup_secondary_cpus();

	/* update TLB size after waking up thपढ़ोs */
	current_cpu_data.tlbsize = ((पढ़ो_c0_config6() >> 16) & 0xffff) + 1;

	रेजिस्टर_smp_ops(&nlm_smp_ops);
#पूर्ण_अगर
	_machine_restart = (व्योम (*)(अक्षर *))nlm_linux_निकास;
	_machine_halt	= nlm_linux_निकास;
	pm_घातer_off	= nlm_linux_निकास;

	/* memory and bootargs from DT */
	xlp_early_init_devtree();

	अगर (memblock_end_of_DRAM() == 0) अणु
		pr_info("Using DRAM BARs for memory map.\n");
		xlp_init_mem_from_bars();
	पूर्ण
	/* Calculate and setup wired entries क्रम mapped kernel */
	nlm_fixup_mem();
पूर्ण

स्थिर अक्षर *get_प्रणाली_type(व्योम)
अणु
	चयन (पढ़ो_c0_prid() & PRID_IMP_MASK) अणु
	हाल PRID_IMP_NETLOGIC_XLP9XX:
	हाल PRID_IMP_NETLOGIC_XLP5XX:
	हाल PRID_IMP_NETLOGIC_XLP2XX:
		वापस "Broadcom XLPII Series";
	शेष:
		वापस "Netlogic XLP Series";
	पूर्ण
पूर्ण

व्योम xlp_mmu_init(व्योम)
अणु
	u32 conf4;

	अगर (cpu_is_xlpii()) अणु
		/* XLPII series has extended pagesize in config 4 */
		conf4 = पढ़ो_c0_config4() & ~0x1f00u;
		ग_लिखो_c0_config4(conf4 | ((PAGE_SHIFT - 10) / 2 << 8));
	पूर्ण अन्यथा अणु
		/* enable extended TLB and Large Fixed TLB */
		ग_लिखो_c0_config6(पढ़ो_c0_config6() | 0x24);

		/* set page mask of extended Fixed TLB in config7 */
		ग_लिखो_c0_config7(PM_DEFAULT_MASK >>
			(13 + (ffz(PM_DEFAULT_MASK >> 13) / 2)));
	पूर्ण
पूर्ण

व्योम nlm_percpu_init(पूर्णांक hwcpuid)
अणु
पूर्ण

व्योम __init prom_init(व्योम)
अणु
	व्योम *reset_vec;

	nlm_io_base = CKSEG1ADDR(XLP_DEFAULT_IO_BASE);
	nlm_init_boot_cpu();
	xlp_mmu_init();
	nlm_node_init(0);
	xlp_dt_init((व्योम *)(दीर्घ)fw_arg0);

	/* Update reset entry poपूर्णांक with CPU init code */
	reset_vec = (व्योम *)CKSEG1ADDR(RESET_VEC_PHYS);
	स_रखो(reset_vec, 0, RESET_VEC_SIZE);
	स_नकल(reset_vec, (व्योम *)nlm_reset_entry,
			(nlm_reset_entry_end - nlm_reset_entry));

#अगर_घोषित CONFIG_SMP
	cpumask_setall(&nlm_cpumask);
#पूर्ण_अगर
पूर्ण
