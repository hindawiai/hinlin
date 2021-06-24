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
#समावेश <linux/thपढ़ोs.h>

#समावेश <यंत्र/यंत्र.h>
#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/माला.स>

#समावेश <यंत्र/netlogic/haldefs.h>
#समावेश <यंत्र/netlogic/common.h>
#समावेश <यंत्र/netlogic/mips-extns.h>

#समावेश <यंत्र/netlogic/xlp-hal/iomap.h>
#समावेश <यंत्र/netlogic/xlp-hal/xlp.h>
#समावेश <यंत्र/netlogic/xlp-hal/pic.h>
#समावेश <यंत्र/netlogic/xlp-hal/sys.h>

अटल पूर्णांक xlp_wakeup_core(uपूर्णांक64_t sysbase, पूर्णांक node, पूर्णांक core)
अणु
	uपूर्णांक32_t coremask, value;
	पूर्णांक count, resetreg;

	coremask = (1 << core);

	/* Enable CPU घड़ी in हाल of 8xx/3xx */
	अगर (!cpu_is_xlpii()) अणु
		value = nlm_पढ़ो_sys_reg(sysbase, SYS_CORE_DFS_DIS_CTRL);
		value &= ~coremask;
		nlm_ग_लिखो_sys_reg(sysbase, SYS_CORE_DFS_DIS_CTRL, value);
	पूर्ण

	/* On 9XX, mark coherent first */
	अगर (cpu_is_xlp9xx()) अणु
		value = nlm_पढ़ो_sys_reg(sysbase, SYS_9XX_CPU_NONCOHERENT_MODE);
		value &= ~coremask;
		nlm_ग_लिखो_sys_reg(sysbase, SYS_9XX_CPU_NONCOHERENT_MODE, value);
	पूर्ण

	/* Remove CPU Reset */
	resetreg = cpu_is_xlp9xx() ? SYS_9XX_CPU_RESET : SYS_CPU_RESET;
	value = nlm_पढ़ो_sys_reg(sysbase, resetreg);
	value &= ~coremask;
	nlm_ग_लिखो_sys_reg(sysbase, resetreg, value);

	/* We are करोne on 9XX */
	अगर (cpu_is_xlp9xx())
		वापस 1;

	/* Poll क्रम CPU to mark itself coherent on other type of XLP */
	count = 100000;
	करो अणु
		value = nlm_पढ़ो_sys_reg(sysbase, SYS_CPU_NONCOHERENT_MODE);
	पूर्ण जबतक ((value & coremask) != 0 && --count > 0);

	वापस count != 0;
पूर्ण

अटल पूर्णांक रुको_क्रम_cpus(पूर्णांक cpu, पूर्णांक bootcpu)
अणु
	अस्थिर uपूर्णांक32_t *cpu_पढ़ोy = nlm_get_boot_data(BOOT_CPU_READY);
	पूर्णांक i, count, notपढ़ोy;

	count = 0x800000;
	करो अणु
		notपढ़ोy = nlm_thपढ़ोs_per_core;
		क्रम (i = 0; i < nlm_thपढ़ोs_per_core; i++)
			अगर (cpu_पढ़ोy[cpu + i] || (cpu + i) == bootcpu)
				--notपढ़ोy;
	पूर्ण जबतक (notपढ़ोy != 0 && --count > 0);

	वापस count != 0;
पूर्ण

अटल व्योम xlp_enable_secondary_cores(स्थिर cpumask_t *wakeup_mask)
अणु
	काष्ठा nlm_soc_info *nodep;
	uपूर्णांक64_t syspcibase, fusebase;
	uपूर्णांक32_t syscoremask, mask, fusemask;
	पूर्णांक core, n, cpu, ncores;

	क्रम (n = 0; n < NLM_NR_NODES; n++) अणु
		अगर (n != 0) अणु
			/* check अगर node exists and is online */
			अगर (cpu_is_xlp9xx()) अणु
				पूर्णांक b = xlp9xx_get_socbus(n);
				pr_info("Node %d SoC PCI bus %d.\n", n, b);
				अगर (b == 0)
					अवरोध;
			पूर्ण अन्यथा अणु
				syspcibase = nlm_get_sys_pcibase(n);
				अगर (nlm_पढ़ो_reg(syspcibase, 0) == 0xffffffff)
					अवरोध;
			पूर्ण
			nlm_node_init(n);
		पूर्ण

		/* पढ़ो cores in reset from SYS */
		nodep = nlm_get_node(n);

		अगर (cpu_is_xlp9xx()) अणु
			fusebase = nlm_get_fuse_regbase(n);
			fusemask = nlm_पढ़ो_reg(fusebase, FUSE_9XX_DEVCFG6);
			चयन (पढ़ो_c0_prid() & PRID_IMP_MASK) अणु
			हाल PRID_IMP_NETLOGIC_XLP5XX:
				mask = 0xff;
				अवरोध;
			हाल PRID_IMP_NETLOGIC_XLP9XX:
			शेष:
				mask = 0xfffff;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			fusemask = nlm_पढ़ो_sys_reg(nodep->sysbase,
						SYS_EFUSE_DEVICE_CFG_STATUS0);
			चयन (पढ़ो_c0_prid() & PRID_IMP_MASK) अणु
			हाल PRID_IMP_NETLOGIC_XLP3XX:
				mask = 0xf;
				अवरोध;
			हाल PRID_IMP_NETLOGIC_XLP2XX:
				mask = 0x3;
				अवरोध;
			हाल PRID_IMP_NETLOGIC_XLP8XX:
			शेष:
				mask = 0xff;
				अवरोध;
			पूर्ण
		पूर्ण

		/*
		 * Fused out cores are set in the fusemask, and the reमुख्यing
		 * cores are rक्रमागतbered to range 0 .. nactive-1
		 */
		syscoremask = (1 << hweight32(~fusemask & mask)) - 1;

		pr_info("Node %d - SYS/FUSE coremask %x\n", n, syscoremask);
		ncores = nlm_cores_per_node();
		क्रम (core = 0; core < ncores; core++) अणु
			/* we will be on node 0 core 0 */
			अगर (n == 0 && core == 0)
				जारी;

			/* see अगर the core exists */
			अगर ((syscoremask & (1 << core)) == 0)
				जारी;

			/* see अगर at least the first hw thपढ़ो is enabled */
			cpu = (n * ncores + core) * NLM_THREADS_PER_CORE;
			अगर (!cpumask_test_cpu(cpu, wakeup_mask))
				जारी;

			/* wake up the core */
			अगर (!xlp_wakeup_core(nodep->sysbase, n, core))
				जारी;

			/* core is up */
			nodep->coremask |= 1u << core;

			/* spin until the hw thपढ़ोs sets their पढ़ोy */
			अगर (!रुको_क्रम_cpus(cpu, 0))
				pr_err("Node %d : timeout core %d\n", n, core);
		पूर्ण
	पूर्ण
पूर्ण

व्योम xlp_wakeup_secondary_cpus(व्योम)
अणु
	/*
	 * In हाल of u-boot, the secondaries are in reset
	 * first wakeup core 0 thपढ़ोs
	 */
	xlp_boot_core0_siblings();
	अगर (!रुको_क्रम_cpus(0, 0))
		pr_err("Node 0 : timeout core 0\n");

	/* now get other cores out of reset */
	xlp_enable_secondary_cores(&nlm_cpumask);
पूर्ण
