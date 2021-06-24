<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/smp.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/sn/types.h>
#समावेश <यंत्र/sn/addrs.h>
#समावेश <यंत्र/sn/nmi.h>
#समावेश <यंत्र/sn/arch.h>
#समावेश <यंत्र/sn/agent.h>

#अगर 0
#घोषणा NODE_NUM_CPUS(n)	CNODE_NUM_CPUS(n)
#अन्यथा
#घोषणा NODE_NUM_CPUS(n)	CPUS_PER_NODE
#पूर्ण_अगर

#घोषणा SEND_NMI(_nasid, _slice)	\
	REMOTE_HUB_S((_nasid),  (PI_NMI_A + ((_slice) * PI_NMI_OFFSET)), 1)

प्रकार अचिन्हित दीर्घ machreg_t;

अटल arch_spinlock_t nmi_lock = __ARCH_SPIN_LOCK_UNLOCKED;

/*
 * Let's see what अन्यथा we need to करो here. Set up sp, gp?
 */
व्योम nmi_dump(व्योम)
अणु
	व्योम cont_nmi_dump(व्योम);

	cont_nmi_dump();
पूर्ण

व्योम install_cpu_nmi_handler(पूर्णांक slice)
अणु
	nmi_t *nmi_addr;

	nmi_addr = (nmi_t *)NMI_ADDR(get_nasid(), slice);
	अगर (nmi_addr->call_addr)
		वापस;
	nmi_addr->magic = NMI_MAGIC;
	nmi_addr->call_addr = (व्योम *)nmi_dump;
	nmi_addr->call_addr_c =
		(व्योम *)(~((अचिन्हित दीर्घ)(nmi_addr->call_addr)));
	nmi_addr->call_parm = 0;
पूर्ण

/*
 * Copy the cpu रेजिस्टरs which have been saved in the IP27prom क्रमmat
 * पूर्णांकo the eframe क्रमmat क्रम the node under consideration.
 */

व्योम nmi_cpu_eframe_save(nasid_t nasid, पूर्णांक slice)
अणु
	काष्ठा reg_काष्ठा *nr;
	पूर्णांक		i;

	/* Get the poपूर्णांकer to the current cpu's रेजिस्टर set. */
	nr = (काष्ठा reg_काष्ठा *)
		(TO_UNCAC(TO_NODE(nasid, IP27_NMI_KREGS_OFFSET)) +
		slice * IP27_NMI_KREGS_CPU_SIZE);

	pr_emerg("NMI nasid %d: slice %d\n", nasid, slice);

	/*
	 * Saved मुख्य processor रेजिस्टरs
	 */
	क्रम (i = 0; i < 32; ) अणु
		अगर ((i % 4) == 0)
			pr_emerg("$%2d   :", i);
		pr_cont(" %016lx", nr->gpr[i]);

		i++;
		अगर ((i % 4) == 0)
			pr_cont("\n");
	पूर्ण

	pr_emerg("Hi    : (value lost)\n");
	pr_emerg("Lo    : (value lost)\n");

	/*
	 * Saved cp0 रेजिस्टरs
	 */
	pr_emerg("epc   : %016lx %pS\n", nr->epc, (व्योम *)nr->epc);
	pr_emerg("%s\n", prपूर्णांक_taपूर्णांकed());
	pr_emerg("ErrEPC: %016lx %pS\n", nr->error_epc, (व्योम *)nr->error_epc);
	pr_emerg("ra    : %016lx %pS\n", nr->gpr[31], (व्योम *)nr->gpr[31]);
	pr_emerg("Status: %08lx	      ", nr->sr);

	अगर (nr->sr & ST0_KX)
		pr_cont("KX ");
	अगर (nr->sr & ST0_SX)
		pr_cont("SX ");
	अगर (nr->sr & ST0_UX)
		pr_cont("UX ");

	चयन (nr->sr & ST0_KSU) अणु
	हाल KSU_USER:
		pr_cont("USER ");
		अवरोध;
	हाल KSU_SUPERVISOR:
		pr_cont("SUPERVISOR ");
		अवरोध;
	हाल KSU_KERNEL:
		pr_cont("KERNEL ");
		अवरोध;
	शेष:
		pr_cont("BAD_MODE ");
		अवरोध;
	पूर्ण

	अगर (nr->sr & ST0_ERL)
		pr_cont("ERL ");
	अगर (nr->sr & ST0_EXL)
		pr_cont("EXL ");
	अगर (nr->sr & ST0_IE)
		pr_cont("IE ");
	pr_cont("\n");

	pr_emerg("Cause : %08lx\n", nr->cause);
	pr_emerg("PrId  : %08x\n", पढ़ो_c0_prid());
	pr_emerg("BadVA : %016lx\n", nr->badva);
	pr_emerg("CErr  : %016lx\n", nr->cache_err);
	pr_emerg("NMI_SR: %016lx\n", nr->nmi_sr);

	pr_emerg("\n");
पूर्ण

व्योम nmi_dump_hub_irq(nasid_t nasid, पूर्णांक slice)
अणु
	u64 mask0, mask1, pend0, pend1;

	अगर (slice == 0) अणु				/* Slice A */
		mask0 = REMOTE_HUB_L(nasid, PI_INT_MASK0_A);
		mask1 = REMOTE_HUB_L(nasid, PI_INT_MASK1_A);
	पूर्ण अन्यथा अणु					/* Slice B */
		mask0 = REMOTE_HUB_L(nasid, PI_INT_MASK0_B);
		mask1 = REMOTE_HUB_L(nasid, PI_INT_MASK1_B);
	पूर्ण

	pend0 = REMOTE_HUB_L(nasid, PI_INT_PEND0);
	pend1 = REMOTE_HUB_L(nasid, PI_INT_PEND1);

	pr_emerg("PI_INT_MASK0: %16llx PI_INT_MASK1: %16llx\n", mask0, mask1);
	pr_emerg("PI_INT_PEND0: %16llx PI_INT_PEND1: %16llx\n", pend0, pend1);
	pr_emerg("\n\n");
पूर्ण

/*
 * Copy the cpu रेजिस्टरs which have been saved in the IP27prom क्रमmat
 * पूर्णांकo the eframe क्रमmat क्रम the node under consideration.
 */
व्योम nmi_node_eframe_save(nasid_t nasid)
अणु
	पूर्णांक slice;

	अगर (nasid == INVALID_NASID)
		वापस;

	/* Save the रेजिस्टरs पूर्णांकo eframe क्रम each cpu */
	क्रम (slice = 0; slice < NODE_NUM_CPUS(slice); slice++) अणु
		nmi_cpu_eframe_save(nasid, slice);
		nmi_dump_hub_irq(nasid, slice);
	पूर्ण
पूर्ण

/*
 * Save the nmi cpu रेजिस्टरs क्रम all cpus in the प्रणाली.
 */
व्योम
nmi_eframes_save(व्योम)
अणु
	nasid_t nasid;

	क्रम_each_online_node(nasid)
		nmi_node_eframe_save(nasid);
पूर्ण

व्योम
cont_nmi_dump(व्योम)
अणु
#अगर_अघोषित REAL_NMI_SIGNAL
	अटल atomic_t nmied_cpus = ATOMIC_INIT(0);

	atomic_inc(&nmied_cpus);
#पूर्ण_अगर
	/*
	 * Only allow 1 cpu to proceed
	 */
	arch_spin_lock(&nmi_lock);

#अगर_घोषित REAL_NMI_SIGNAL
	/*
	 * Wait up to 15 seconds क्रम the other cpus to respond to the NMI.
	 * If a cpu has not responded after 10 sec, send it 1 additional NMI.
	 * This is क्रम 2 reasons:
	 *	- someबार a MMSC fail to NMI all cpus.
	 *	- on 512p SN0 प्रणाली, the MMSC will only send NMIs to
	 *	  half the cpus. Unक्रमtunately, we करोn't know which cpus may be
	 *	  NMIed - it depends on how the site chooses to configure.
	 *
	 * Note: it has been measure that it takes the MMSC up to 2.3 secs to
	 * send NMIs to all cpus on a 256p प्रणाली.
	 */
	क्रम (i=0; i < 1500; i++) अणु
		क्रम_each_online_node(node)
			अगर (NODEPDA(node)->dump_count == 0)
				अवरोध;
		अगर (node == MAX_NUMNODES)
			अवरोध;
		अगर (i == 1000) अणु
			क्रम_each_online_node(node)
				अगर (NODEPDA(node)->dump_count == 0) अणु
					cpu = cpumask_first(cpumask_of_node(node));
					क्रम (n=0; n < CNODE_NUM_CPUS(node); cpu++, n++) अणु
						CPUMASK_SETB(nmied_cpus, cpu);
						/*
						 * cputonasid, cputoslice
						 * needs kernel cpuid
						 */
						SEND_NMI((cputonasid(cpu)), (cputoslice(cpu)));
					पूर्ण
				पूर्ण

		पूर्ण
		udelay(10000);
	पूर्ण
#अन्यथा
	जबतक (atomic_पढ़ो(&nmied_cpus) != num_online_cpus());
#पूर्ण_अगर

	/*
	 * Save the nmi cpu रेजिस्टरs क्रम all cpu in the eframe क्रमmat.
	 */
	nmi_eframes_save();
	LOCAL_HUB_S(NI_PORT_RESET, NPR_PORTRESET | NPR_LOCALRESET);
पूर्ण
