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

#समावेश <linux/delay.h>
#समावेश <linux/thपढ़ोs.h>

#समावेश <यंत्र/यंत्र.h>
#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/माला.स>

#समावेश <यंत्र/netlogic/haldefs.h>
#समावेश <यंत्र/netlogic/common.h>
#समावेश <यंत्र/netlogic/mips-extns.h>

#समावेश <यंत्र/netlogic/xlr/iomap.h>
#समावेश <यंत्र/netlogic/xlr/pic.h>

पूर्णांक xlr_wakeup_secondary_cpus(व्योम)
अणु
	काष्ठा nlm_soc_info *nodep;
	अचिन्हित पूर्णांक i, j, boot_cpu;
	अस्थिर u32 *cpu_पढ़ोy = nlm_get_boot_data(BOOT_CPU_READY);

	/*
	 *  In हाल of RMI boot, hit with NMI to get the cores
	 *  from bootloader to linux code.
	 */
	nodep = nlm_get_node(0);
	boot_cpu = hard_smp_processor_id();
	nlm_set_nmi_handler(nlm_rmiboot_preboot);
	क्रम (i = 0; i < NR_CPUS; i++) अणु
		अगर (i == boot_cpu || !cpumask_test_cpu(i, &nlm_cpumask))
			जारी;
		nlm_pic_send_ipi(nodep->picbase, i, 1, 1); /* send NMI */
	पूर्ण

	/* Fill up the coremask early */
	nodep->coremask = 1;
	क्रम (i = 1; i < nlm_cores_per_node(); i++) अणु
		क्रम (j = 1000000; j > 0; j--) अणु
			अगर (cpu_पढ़ोy[i * NLM_THREADS_PER_CORE])
				अवरोध;
			udelay(10);
		पूर्ण
		अगर (j != 0)
			nodep->coremask |= (1u << i);
		अन्यथा
			pr_err("Failed to wakeup core %d\n", i);
	पूर्ण

	वापस 0;
पूर्ण
