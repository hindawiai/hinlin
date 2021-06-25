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
#समावेश <linux/serial_8250.h>
#समावेश <linux/memblock.h>
#समावेश <linux/pm.h>

#समावेश <यंत्र/idle.h>
#समावेश <यंत्र/reboot.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/bootinfo.h>

#समावेश <यंत्र/netlogic/पूर्णांकerrupt.h>
#समावेश <यंत्र/netlogic/psb-bootinfo.h>
#समावेश <यंत्र/netlogic/haldefs.h>
#समावेश <यंत्र/netlogic/common.h>

#समावेश <यंत्र/netlogic/xlr/xlr.h>
#समावेश <यंत्र/netlogic/xlr/iomap.h>
#समावेश <यंत्र/netlogic/xlr/pic.h>
#समावेश <यंत्र/netlogic/xlr/gpपन.स>
#समावेश <यंत्र/netlogic/xlr/fmn.h>

uपूर्णांक64_t nlm_io_base = DEFAULT_NETLOGIC_IO_BASE;
काष्ठा psb_info nlm_prom_info;

/* शेष to uniprocessor */
अचिन्हित पूर्णांक  nlm_thपढ़ोs_per_core = 1;
काष्ठा nlm_soc_info nlm_nodes[NLM_NR_NODES];
cpumask_t nlm_cpumask = CPU_MASK_CPU0;

अटल व्योम nlm_linux_निकास(व्योम)
अणु
	uपूर्णांक64_t gpiobase;

	gpiobase = nlm_mmio_base(NETLOGIC_IO_GPIO_OFFSET);
	/* trigger a chip reset by writing 1 to GPIO_SWRESET_REG */
	nlm_ग_लिखो_reg(gpiobase, GPIO_SWRESET_REG, 1);
	क्रम ( ; ; )
		cpu_रुको();
पूर्ण

व्योम __init plat_mem_setup(व्योम)
अणु
	_machine_restart = (व्योम (*)(अक्षर *))nlm_linux_निकास;
	_machine_halt	= nlm_linux_निकास;
	pm_घातer_off	= nlm_linux_निकास;
पूर्ण

स्थिर अक्षर *get_प्रणाली_type(व्योम)
अणु
	वापस "Netlogic XLR/XLS Series";
पूर्ण

अचिन्हित पूर्णांक nlm_get_cpu_frequency(व्योम)
अणु
	वापस (अचिन्हित पूर्णांक)nlm_prom_info.cpu_frequency;
पूर्ण

व्योम nlm_percpu_init(पूर्णांक hwcpuid)
अणु
	अगर (hwcpuid % 4 == 0)
		xlr_percpu_fmn_init();
पूर्ण

अटल व्योम __init build_arcs_cmdline(पूर्णांक *argv)
अणु
	पूर्णांक i, reमुख्य, len;
	अक्षर *arg;

	reमुख्य = माप(arcs_cmdline) - 1;
	arcs_cmdline[0] = '\0';
	क्रम (i = 0; argv[i] != 0; i++) अणु
		arg = (अक्षर *)(दीर्घ)argv[i];
		len = म_माप(arg);
		अगर (len + 1 > reमुख्य)
			अवरोध;
		म_जोड़ो(arcs_cmdline, arg);
		म_जोड़ो(arcs_cmdline, " ");
		reमुख्य -=  len + 1;
	पूर्ण

	/* Add the शेष options here */
	अगर ((म_माला(arcs_cmdline, "console=")) == शून्य) अणु
		arg = "console=ttyS0,38400 ";
		len = म_माप(arg);
		अगर (len > reमुख्य)
			जाओ fail;
		म_जोड़ो(arcs_cmdline, arg);
		reमुख्य -= len;
	पूर्ण
#अगर_घोषित CONFIG_BLK_DEV_INITRD
	अगर ((म_माला(arcs_cmdline, "rdinit=")) == शून्य) अणु
		arg = "rdinit=/sbin/init ";
		len = म_माप(arg);
		अगर (len > reमुख्य)
			जाओ fail;
		म_जोड़ो(arcs_cmdline, arg);
		reमुख्य -= len;
	पूर्ण
#पूर्ण_अगर
	वापस;
fail:
	panic("Cannot add %s, command line too big!", arg);
पूर्ण

अटल व्योम prom_add_memory(व्योम)
अणु
	काष्ठा nlm_boot_mem_map *booपंचांग;
	u64 start, size;
	u64 pref_backup = 512;	/* aव्योम pref walking beyond end */
	पूर्णांक i;

	booपंचांग = (व्योम *)(दीर्घ)nlm_prom_info.psb_mem_map;
	क्रम (i = 0; i < booपंचांग->nr_map; i++) अणु
		अगर (booपंचांग->map[i].type != NLM_BOOT_MEM_RAM)
			जारी;
		start = booपंचांग->map[i].addr;
		size   = booपंचांग->map[i].size;

		/* Work around क्रम using bootloader mem */
		अगर (i == 0 && start == 0 && size == 0x0c000000)
			size = 0x0ff00000;

		memblock_add(start, size - pref_backup);
	पूर्ण
पूर्ण

अटल व्योम nlm_init_node(व्योम)
अणु
	काष्ठा nlm_soc_info *nodep;

	nodep = nlm_current_node();
	nodep->picbase = nlm_mmio_base(NETLOGIC_IO_PIC_OFFSET);
	nodep->ebase = पढ़ो_c0_ebase() & MIPS_EBASE_BASE;
	spin_lock_init(&nodep->piघड़ी);
पूर्ण

व्योम __init prom_init(व्योम)
अणु
	पूर्णांक *argv, *envp;		/* passed as 32 bit ptrs */
	काष्ठा psb_info *prom_infop;
	व्योम *reset_vec;
#अगर_घोषित CONFIG_SMP
	पूर्णांक i;
#पूर्ण_अगर

	/* truncate to 32 bit and sign extend all args */
	argv = (पूर्णांक *)(दीर्घ)(पूर्णांक)fw_arg1;
	envp = (पूर्णांक *)(दीर्घ)(पूर्णांक)fw_arg2;
	prom_infop = (काष्ठा psb_info *)(दीर्घ)(पूर्णांक)fw_arg3;

	nlm_prom_info = *prom_infop;
	nlm_init_node();

	/* Update reset entry poपूर्णांक with CPU init code */
	reset_vec = (व्योम *)CKSEG1ADDR(RESET_VEC_PHYS);
	स_रखो(reset_vec, 0, RESET_VEC_SIZE);
	स_नकल(reset_vec, (व्योम *)nlm_reset_entry,
			(nlm_reset_entry_end - nlm_reset_entry));

	build_arcs_cmdline(argv);
	prom_add_memory();

#अगर_घोषित CONFIG_SMP
	क्रम (i = 0; i < 32; i++)
		अगर (nlm_prom_info.online_cpu_map & (1 << i))
			cpumask_set_cpu(i, &nlm_cpumask);
	nlm_wakeup_secondary_cpus();
	रेजिस्टर_smp_ops(&nlm_smp_ops);
#पूर्ण_अगर
	xlr_board_info_setup();
	xlr_percpu_fmn_init();
पूर्ण
