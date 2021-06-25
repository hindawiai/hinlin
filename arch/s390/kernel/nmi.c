<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *   Machine check handler
 *
 *    Copyright IBM Corp. 2000, 2009
 *    Author(s): Ingo Adlung <adlung@de.ibm.com>,
 *		 Martin Schwidefsky <schwidefsky@de.ibm.com>,
 *		 Cornelia Huck <cornelia.huck@de.ibm.com>,
 *		 Heiko Carstens <heiko.carstens@de.ibm.com>,
 */

#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/hardirq.h>
#समावेश <linux/log2.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/समय.स>
#समावेश <linux/module.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <linux/export.h>
#समावेश <यंत्र/lowcore.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/stp.h>
#समावेश <यंत्र/cpuसमय.स>
#समावेश <यंत्र/nmi.h>
#समावेश <यंत्र/crw.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/ctl_reg.h>
#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <linux/kvm_host.h>

काष्ठा mcck_काष्ठा अणु
	अचिन्हित पूर्णांक समाप्त_task : 1;
	अचिन्हित पूर्णांक channel_report : 1;
	अचिन्हित पूर्णांक warning : 1;
	अचिन्हित पूर्णांक stp_queue : 1;
	अचिन्हित दीर्घ mcck_code;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा mcck_काष्ठा, cpu_mcck);
अटल काष्ठा kmem_cache *mcesa_cache;
अटल अचिन्हित दीर्घ mcesa_origin_lc;

अटल अंतरभूत पूर्णांक nmi_needs_mcesa(व्योम)
अणु
	वापस MACHINE_HAS_VX || MACHINE_HAS_GS;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ nmi_get_mcesa_size(व्योम)
अणु
	अगर (MACHINE_HAS_GS)
		वापस MCESA_MAX_SIZE;
	वापस MCESA_MIN_SIZE;
पूर्ण

/*
 * The initial machine check extended save area क्रम the boot CPU.
 * It will be replaced by nmi_init() with an allocated काष्ठाure.
 * The काष्ठाure is required क्रम machine check happening early in
 * the boot process.
 */
अटल काष्ठा mcesa boot_mcesa __initdata __aligned(MCESA_MAX_SIZE);

व्योम __init nmi_alloc_boot_cpu(काष्ठा lowcore *lc)
अणु
	अगर (!nmi_needs_mcesa())
		वापस;
	lc->mcesad = (अचिन्हित दीर्घ) &boot_mcesa;
	अगर (MACHINE_HAS_GS)
		lc->mcesad |= ilog2(MCESA_MAX_SIZE);
पूर्ण

अटल पूर्णांक __init nmi_init(व्योम)
अणु
	अचिन्हित दीर्घ origin, cr0, size;

	अगर (!nmi_needs_mcesa())
		वापस 0;
	size = nmi_get_mcesa_size();
	अगर (size > MCESA_MIN_SIZE)
		mcesa_origin_lc = ilog2(size);
	/* create slab cache क्रम the machine-check-extended-save-areas */
	mcesa_cache = kmem_cache_create("nmi_save_areas", size, size, 0, शून्य);
	अगर (!mcesa_cache)
		panic("Couldn't create nmi save area cache");
	origin = (अचिन्हित दीर्घ) kmem_cache_alloc(mcesa_cache, GFP_KERNEL);
	अगर (!origin)
		panic("Couldn't allocate nmi save area");
	/* The poपूर्णांकer is stored with mcesa_bits ORed in */
	kmemleak_not_leak((व्योम *) origin);
	__ctl_store(cr0, 0, 0);
	__ctl_clear_bit(0, 28); /* disable lowcore protection */
	/* Replace boot_mcesa on the boot CPU */
	S390_lowcore.mcesad = origin | mcesa_origin_lc;
	__ctl_load(cr0, 0, 0);
	वापस 0;
पूर्ण
early_initcall(nmi_init);

पूर्णांक nmi_alloc_per_cpu(काष्ठा lowcore *lc)
अणु
	अचिन्हित दीर्घ origin;

	अगर (!nmi_needs_mcesa())
		वापस 0;
	origin = (अचिन्हित दीर्घ) kmem_cache_alloc(mcesa_cache, GFP_KERNEL);
	अगर (!origin)
		वापस -ENOMEM;
	/* The poपूर्णांकer is stored with mcesa_bits ORed in */
	kmemleak_not_leak((व्योम *) origin);
	lc->mcesad = origin | mcesa_origin_lc;
	वापस 0;
पूर्ण

व्योम nmi_मुक्त_per_cpu(काष्ठा lowcore *lc)
अणु
	अगर (!nmi_needs_mcesa())
		वापस;
	kmem_cache_मुक्त(mcesa_cache, (व्योम *)(lc->mcesad & MCESA_ORIGIN_MASK));
पूर्ण

अटल notrace व्योम s390_handle_damage(व्योम)
अणु
	smp_emergency_stop();
	disabled_रुको();
	जबतक (1);
पूर्ण
NOKPROBE_SYMBOL(s390_handle_damage);

/*
 * Main machine check handler function. Will be called with पूर्णांकerrupts disabled
 * and machine checks enabled.
 */
व्योम __s390_handle_mcck(व्योम)
अणु
	काष्ठा mcck_काष्ठा mcck;

	/*
	 * Disable machine checks and get the current state of accumulated
	 * machine checks. Afterwards delete the old state and enable machine
	 * checks again.
	 */
	local_mcck_disable();
	mcck = *this_cpu_ptr(&cpu_mcck);
	स_रखो(this_cpu_ptr(&cpu_mcck), 0, माप(mcck));
	local_mcck_enable();

	अगर (mcck.channel_report)
		crw_handle_channel_report();
	/*
	 * A warning may reमुख्य क्रम a proदीर्घed period on the bare iron.
	 * (actually until the machine is घातered off, or the problem is gone)
	 * So we just stop listening क्रम the WARNING MCH and aव्योम continuously
	 * being पूर्णांकerrupted.  One caveat is however, that we must करो this per
	 * processor and cannot use the smp version of ctl_clear_bit().
	 * On VM we only get one पूर्णांकerrupt per virtally presented machinecheck.
	 * Though one suffices, we may get one पूर्णांकerrupt per (भव) cpu.
	 */
	अगर (mcck.warning) अणु	/* WARNING pending ? */
		अटल पूर्णांक mchchk_wng_posted = 0;

		/* Use single cpu clear, as we cannot handle smp here. */
		__ctl_clear_bit(14, 24);	/* Disable WARNING MCH */
		अगर (xchg(&mchchk_wng_posted, 1) == 0)
			समाप्त_cad_pid(SIGPWR, 1);
	पूर्ण
	अगर (mcck.stp_queue)
		stp_queue_work();
	अगर (mcck.समाप्त_task) अणु
		local_irq_enable();
		prपूर्णांकk(KERN_EMERG "mcck: Terminating task because of machine "
		       "malfunction (code 0x%016lx).\n", mcck.mcck_code);
		prपूर्णांकk(KERN_EMERG "mcck: task: %s, pid: %d.\n",
		       current->comm, current->pid);
		करो_निकास(संक_अंश);
	पूर्ण
पूर्ण

व्योम noinstr s390_handle_mcck(व्योम)
अणु
	trace_hardirqs_off();
	__s390_handle_mcck();
	trace_hardirqs_on();
पूर्ण
/*
 * वापसs 0 अगर all required रेजिस्टरs are available
 * वापसs 1 otherwise
 */
अटल पूर्णांक notrace s390_check_रेजिस्टरs(जोड़ mci mci, पूर्णांक umode)
अणु
	जोड़ ctlreg2 cr2;
	पूर्णांक समाप्त_task;

	समाप्त_task = 0;

	अगर (!mci.gr) अणु
		/*
		 * General purpose रेजिस्टरs couldn't be restored and have
		 * unknown contents. Stop प्रणाली or terminate process.
		 */
		अगर (!umode)
			s390_handle_damage();
		समाप्त_task = 1;
	पूर्ण
	/* Check control रेजिस्टरs */
	अगर (!mci.cr) अणु
		/*
		 * Control रेजिस्टरs have unknown contents.
		 * Can't recover and thereक्रमe stopping machine.
		 */
		s390_handle_damage();
	पूर्ण
	अगर (!mci.fp) अणु
		/*
		 * Floating poपूर्णांक रेजिस्टरs can't be restored. If the
		 * kernel currently uses भग्नing poपूर्णांक रेजिस्टरs the
		 * प्रणाली is stopped. If the process has its भग्नing
		 * poपूर्णांकer रेजिस्टरs loaded it is terminated.
		 */
		अगर (S390_lowcore.fpu_flags & KERNEL_VXR_V0V7)
			s390_handle_damage();
		अगर (!test_cpu_flag(CIF_FPU))
			समाप्त_task = 1;
	पूर्ण
	अगर (!mci.fc) अणु
		/*
		 * Floating poपूर्णांक control रेजिस्टर can't be restored.
		 * If the kernel currently uses the भग्नing poपूर्णांकer
		 * रेजिस्टरs and needs the FPC रेजिस्टर the प्रणाली is
		 * stopped. If the process has its भग्नing poपूर्णांकer
		 * रेजिस्टरs loaded it is terminated.
		 */
		अगर (S390_lowcore.fpu_flags & KERNEL_FPC)
			s390_handle_damage();
		अगर (!test_cpu_flag(CIF_FPU))
			समाप्त_task = 1;
	पूर्ण

	अगर (MACHINE_HAS_VX) अणु
		अगर (!mci.vr) अणु
			/*
			 * Vector रेजिस्टरs can't be restored. If the kernel
			 * currently uses vector रेजिस्टरs the प्रणाली is
			 * stopped. If the process has its vector रेजिस्टरs
			 * loaded it is terminated.
			 */
			अगर (S390_lowcore.fpu_flags & KERNEL_VXR)
				s390_handle_damage();
			अगर (!test_cpu_flag(CIF_FPU))
				समाप्त_task = 1;
		पूर्ण
	पूर्ण
	/* Check अगर access रेजिस्टरs are valid */
	अगर (!mci.ar) अणु
		/*
		 * Access रेजिस्टरs have unknown contents.
		 * Terminating task.
		 */
		समाप्त_task = 1;
	पूर्ण
	/* Check guarded storage रेजिस्टरs */
	cr2.val = S390_lowcore.cregs_save_area[2];
	अगर (cr2.gse) अणु
		अगर (!mci.gs) अणु
			/*
			 * Guarded storage रेजिस्टर can't be restored and
			 * the current processes uses guarded storage.
			 * It has to be terminated.
			 */
			समाप्त_task = 1;
		पूर्ण
	पूर्ण
	/* Check अगर old PSW is valid */
	अगर (!mci.wp) अणु
		/*
		 * Can't tell अगर we come from user or kernel mode
		 * -> stopping machine.
		 */
		s390_handle_damage();
	पूर्ण
	/* Check क्रम invalid kernel inकाष्ठाion address */
	अगर (!mci.ia && !umode) अणु
		/*
		 * The inकाष्ठाion address got lost जबतक running
		 * in the kernel -> stopping machine.
		 */
		s390_handle_damage();
	पूर्ण

	अगर (!mci.ms || !mci.pm || !mci.ia)
		समाप्त_task = 1;

	वापस समाप्त_task;
पूर्ण
NOKPROBE_SYMBOL(s390_check_रेजिस्टरs);

/*
 * Backup the guest's machine check info to its description block
 */
अटल व्योम notrace s390_backup_mcck_info(काष्ठा pt_regs *regs)
अणु
	काष्ठा mcck_अस्थिर_info *mcck_backup;
	काष्ठा sie_page *sie_page;

	/* r14 contains the sie block, which was set in sie64a */
	काष्ठा kvm_s390_sie_block *sie_block =
			(काष्ठा kvm_s390_sie_block *) regs->gprs[14];

	अगर (sie_block == शून्य)
		/* Something's seriously wrong, stop प्रणाली. */
		s390_handle_damage();

	sie_page = container_of(sie_block, काष्ठा sie_page, sie_block);
	mcck_backup = &sie_page->mcck_info;
	mcck_backup->mcic = S390_lowcore.mcck_पूर्णांकerruption_code &
				~(MCCK_CODE_CP | MCCK_CODE_EXT_DAMAGE);
	mcck_backup->ext_damage_code = S390_lowcore.बाह्यal_damage_code;
	mcck_backup->failing_storage_address
			= S390_lowcore.failing_storage_address;
पूर्ण
NOKPROBE_SYMBOL(s390_backup_mcck_info);

#घोषणा MAX_IPD_COUNT	29
#घोषणा MAX_IPD_TIME	(5 * 60 * USEC_PER_SEC) /* 5 minutes */

#घोषणा ED_STP_ISLAND	6	/* External damage STP island check */
#घोषणा ED_STP_SYNC	7	/* External damage STP sync check */

#घोषणा MCCK_CODE_NO_GUEST	(MCCK_CODE_CP | MCCK_CODE_EXT_DAMAGE)

/*
 * machine check handler.
 */
पूर्णांक notrace s390_करो_machine_check(काष्ठा pt_regs *regs)
अणु
	अटल पूर्णांक ipd_count;
	अटल DEFINE_SPINLOCK(ipd_lock);
	अटल अचिन्हित दीर्घ दीर्घ last_ipd;
	काष्ठा mcck_काष्ठा *mcck;
	अचिन्हित दीर्घ दीर्घ पंचांगp;
	जोड़ mci mci;
	अचिन्हित दीर्घ mcck_dam_code;
	पूर्णांक mcck_pending = 0;

	nmi_enter();

	अगर (user_mode(regs))
		update_समयr_mcck();
	inc_irq_stat(NMI_NMI);
	mci.val = S390_lowcore.mcck_पूर्णांकerruption_code;
	mcck = this_cpu_ptr(&cpu_mcck);

	अगर (mci.sd) अणु
		/* System damage -> stopping machine */
		s390_handle_damage();
	पूर्ण

	/*
	 * Reinject the inकाष्ठाion processing damages' machine checks
	 * including Delayed Access Exception पूर्णांकo the guest
	 * instead of damaging the host अगर they happen in the guest.
	 */
	अगर (mci.pd && !test_cpu_flag(CIF_MCCK_GUEST)) अणु
		अगर (mci.b) अणु
			/* Processing backup -> verअगरy अगर we can survive this */
			u64 z_mcic, o_mcic, t_mcic;
			z_mcic = (1ULL<<63 | 1ULL<<59 | 1ULL<<29);
			o_mcic = (1ULL<<43 | 1ULL<<42 | 1ULL<<41 | 1ULL<<40 |
				  1ULL<<36 | 1ULL<<35 | 1ULL<<34 | 1ULL<<32 |
				  1ULL<<30 | 1ULL<<21 | 1ULL<<20 | 1ULL<<17 |
				  1ULL<<16);
			t_mcic = mci.val;

			अगर (((t_mcic & z_mcic) != 0) ||
			    ((t_mcic & o_mcic) != o_mcic)) अणु
				s390_handle_damage();
			पूर्ण

			/*
			 * Nullअगरying exigent condition, thereक्रमe we might
			 * retry this inकाष्ठाion.
			 */
			spin_lock(&ipd_lock);
			पंचांगp = get_tod_घड़ी();
			अगर (((पंचांगp - last_ipd) >> 12) < MAX_IPD_TIME)
				ipd_count++;
			अन्यथा
				ipd_count = 1;
			last_ipd = पंचांगp;
			अगर (ipd_count == MAX_IPD_COUNT)
				s390_handle_damage();
			spin_unlock(&ipd_lock);
		पूर्ण अन्यथा अणु
			/* Processing damage -> stopping machine */
			s390_handle_damage();
		पूर्ण
	पूर्ण
	अगर (s390_check_रेजिस्टरs(mci, user_mode(regs))) अणु
		/*
		 * Couldn't restore all रेजिस्टर contents क्रम the
		 * user space process -> mark task क्रम termination.
		 */
		mcck->समाप्त_task = 1;
		mcck->mcck_code = mci.val;
		mcck_pending = 1;
	पूर्ण

	/*
	 * Backup the machine check's info अगर it happens when the guest
	 * is running.
	 */
	अगर (test_cpu_flag(CIF_MCCK_GUEST))
		s390_backup_mcck_info(regs);

	अगर (mci.cd) अणु
		/* Timing facility damage */
		s390_handle_damage();
	पूर्ण
	अगर (mci.ed && mci.ec) अणु
		/* External damage */
		अगर (S390_lowcore.बाह्यal_damage_code & (1U << ED_STP_SYNC))
			mcck->stp_queue |= stp_sync_check();
		अगर (S390_lowcore.बाह्यal_damage_code & (1U << ED_STP_ISLAND))
			mcck->stp_queue |= stp_island_check();
		mcck_pending = 1;
	पूर्ण

	/*
	 * Reinject storage related machine checks पूर्णांकo the guest अगर they
	 * happen when the guest is running.
	 */
	अगर (!test_cpu_flag(CIF_MCCK_GUEST)) अणु
		अगर (mci.se)
			/* Storage error uncorrected */
			s390_handle_damage();
		अगर (mci.ke)
			/* Storage key-error uncorrected */
			s390_handle_damage();
		अगर (mci.ds && mci.fa)
			/* Storage degradation */
			s390_handle_damage();
	पूर्ण
	अगर (mci.cp) अणु
		/* Channel report word pending */
		mcck->channel_report = 1;
		mcck_pending = 1;
	पूर्ण
	अगर (mci.w) अणु
		/* Warning pending */
		mcck->warning = 1;
		mcck_pending = 1;
	पूर्ण

	/*
	 * If there are only Channel Report Pending and External Damage
	 * machine checks, they will not be reinjected पूर्णांकo the guest
	 * because they refer to host conditions only.
	 */
	mcck_dam_code = (mci.val & MCIC_SUBCLASS_MASK);
	अगर (test_cpu_flag(CIF_MCCK_GUEST) &&
	(mcck_dam_code & MCCK_CODE_NO_GUEST) != mcck_dam_code) अणु
		/* Set निकास reason code क्रम host's later handling */
		*((दीर्घ *)(regs->gprs[15] + __SF_SIE_REASON)) = -EINTR;
	पूर्ण
	clear_cpu_flag(CIF_MCCK_GUEST);

	अगर (user_mode(regs) && mcck_pending) अणु
		nmi_निकास();
		वापस 1;
	पूर्ण

	अगर (mcck_pending)
		schedule_mcck_handler();

	nmi_निकास();
	वापस 0;
पूर्ण
NOKPROBE_SYMBOL(s390_करो_machine_check);

अटल पूर्णांक __init machine_check_init(व्योम)
अणु
	ctl_set_bit(14, 25);	/* enable बाह्यal damage MCH */
	ctl_set_bit(14, 27);	/* enable प्रणाली recovery MCH */
	ctl_set_bit(14, 24);	/* enable warning MCH */
	वापस 0;
पूर्ण
early_initcall(machine_check_init);
