<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Machine check exception handling.
 *
 * Copyright 2013 IBM Corporation
 * Author: Mahesh Salgaonkar <mahesh@linux.vnet.ibm.com>
 */

#अघोषित DEBUG
#घोषणा pr_fmt(fmt) "mce: " fmt

#समावेश <linux/hardirq.h>
#समावेश <linux/types.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/percpu.h>
#समावेश <linux/export.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/extable.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/पूर्णांकerrupt.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/mce.h>
#समावेश <यंत्र/nmi.h>
#समावेश <यंत्र/यंत्र-prototypes.h>

#समावेश "setup.h"

अटल व्योम machine_check_process_queued_event(काष्ठा irq_work *work);
अटल व्योम machine_check_ue_irq_work(काष्ठा irq_work *work);
अटल व्योम machine_check_ue_event(काष्ठा machine_check_event *evt);
अटल व्योम machine_process_ue_event(काष्ठा work_काष्ठा *work);

अटल काष्ठा irq_work mce_event_process_work = अणु
        .func = machine_check_process_queued_event,
पूर्ण;

अटल काष्ठा irq_work mce_ue_event_irq_work = अणु
	.func = machine_check_ue_irq_work,
पूर्ण;

अटल DECLARE_WORK(mce_ue_event_work, machine_process_ue_event);

अटल BLOCKING_NOTIFIER_HEAD(mce_notअगरier_list);

पूर्णांक mce_रेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_रेजिस्टर(&mce_notअगरier_list, nb);
पूर्ण
EXPORT_SYMBOL_GPL(mce_रेजिस्टर_notअगरier);

पूर्णांक mce_unरेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_unरेजिस्टर(&mce_notअगरier_list, nb);
पूर्ण
EXPORT_SYMBOL_GPL(mce_unरेजिस्टर_notअगरier);

अटल व्योम mce_set_error_info(काष्ठा machine_check_event *mce,
			       काष्ठा mce_error_info *mce_err)
अणु
	mce->error_type = mce_err->error_type;
	चयन (mce_err->error_type) अणु
	हाल MCE_ERROR_TYPE_UE:
		mce->u.ue_error.ue_error_type = mce_err->u.ue_error_type;
		अवरोध;
	हाल MCE_ERROR_TYPE_SLB:
		mce->u.slb_error.slb_error_type = mce_err->u.slb_error_type;
		अवरोध;
	हाल MCE_ERROR_TYPE_ERAT:
		mce->u.erat_error.erat_error_type = mce_err->u.erat_error_type;
		अवरोध;
	हाल MCE_ERROR_TYPE_TLB:
		mce->u.tlb_error.tlb_error_type = mce_err->u.tlb_error_type;
		अवरोध;
	हाल MCE_ERROR_TYPE_USER:
		mce->u.user_error.user_error_type = mce_err->u.user_error_type;
		अवरोध;
	हाल MCE_ERROR_TYPE_RA:
		mce->u.ra_error.ra_error_type = mce_err->u.ra_error_type;
		अवरोध;
	हाल MCE_ERROR_TYPE_LINK:
		mce->u.link_error.link_error_type = mce_err->u.link_error_type;
		अवरोध;
	हाल MCE_ERROR_TYPE_UNKNOWN:
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Decode and save high level MCE inक्रमmation पूर्णांकo per cpu buffer which
 * is an array of machine_check_event काष्ठाure.
 */
व्योम save_mce_event(काष्ठा pt_regs *regs, दीर्घ handled,
		    काष्ठा mce_error_info *mce_err,
		    uपूर्णांक64_t nip, uपूर्णांक64_t addr, uपूर्णांक64_t phys_addr)
अणु
	पूर्णांक index = local_paca->mce_info->mce_nest_count++;
	काष्ठा machine_check_event *mce;

	mce = &local_paca->mce_info->mce_event[index];
	/*
	 * Return अगर we करोn't have enough space to log mce event.
	 * mce_nest_count may go beyond MAX_MC_EVT but that's ok,
	 * the check below will stop buffer overrun.
	 */
	अगर (index >= MAX_MC_EVT)
		वापस;

	/* Populate generic machine check info */
	mce->version = MCE_V1;
	mce->srr0 = nip;
	mce->srr1 = regs->msr;
	mce->gpr3 = regs->gpr[3];
	mce->in_use = 1;
	mce->cpu = get_paca()->paca_index;

	/* Mark it recovered अगर we have handled it and MSR(RI=1). */
	अगर (handled && (regs->msr & MSR_RI))
		mce->disposition = MCE_DISPOSITION_RECOVERED;
	अन्यथा
		mce->disposition = MCE_DISPOSITION_NOT_RECOVERED;

	mce->initiator = mce_err->initiator;
	mce->severity = mce_err->severity;
	mce->sync_error = mce_err->sync_error;
	mce->error_class = mce_err->error_class;

	/*
	 * Populate the mce error_type and type-specअगरic error_type.
	 */
	mce_set_error_info(mce, mce_err);
	अगर (mce->error_type == MCE_ERROR_TYPE_UE)
		mce->u.ue_error.ignore_event = mce_err->ignore_event;

	अगर (!addr)
		वापस;

	अगर (mce->error_type == MCE_ERROR_TYPE_TLB) अणु
		mce->u.tlb_error.effective_address_provided = true;
		mce->u.tlb_error.effective_address = addr;
	पूर्ण अन्यथा अगर (mce->error_type == MCE_ERROR_TYPE_SLB) अणु
		mce->u.slb_error.effective_address_provided = true;
		mce->u.slb_error.effective_address = addr;
	पूर्ण अन्यथा अगर (mce->error_type == MCE_ERROR_TYPE_ERAT) अणु
		mce->u.erat_error.effective_address_provided = true;
		mce->u.erat_error.effective_address = addr;
	पूर्ण अन्यथा अगर (mce->error_type == MCE_ERROR_TYPE_USER) अणु
		mce->u.user_error.effective_address_provided = true;
		mce->u.user_error.effective_address = addr;
	पूर्ण अन्यथा अगर (mce->error_type == MCE_ERROR_TYPE_RA) अणु
		mce->u.ra_error.effective_address_provided = true;
		mce->u.ra_error.effective_address = addr;
	पूर्ण अन्यथा अगर (mce->error_type == MCE_ERROR_TYPE_LINK) अणु
		mce->u.link_error.effective_address_provided = true;
		mce->u.link_error.effective_address = addr;
	पूर्ण अन्यथा अगर (mce->error_type == MCE_ERROR_TYPE_UE) अणु
		mce->u.ue_error.effective_address_provided = true;
		mce->u.ue_error.effective_address = addr;
		अगर (phys_addr != अच_दीर्घ_उच्च) अणु
			mce->u.ue_error.physical_address_provided = true;
			mce->u.ue_error.physical_address = phys_addr;
			machine_check_ue_event(mce);
		पूर्ण
	पूर्ण
	वापस;
पूर्ण

/*
 * get_mce_event:
 *	mce	Poपूर्णांकer to machine_check_event काष्ठाure to be filled.
 *	release Flag to indicate whether to मुक्त the event slot or not.
 *		0 <= करो not release the mce event. Caller will invoke
 *		     release_mce_event() once event has been consumed.
 *		1 <= release the slot.
 *
 *	वापस	1 = success
 *		0 = failure
 *
 * get_mce_event() will be called by platक्रमm specअगरic machine check
 * handle routine and in KVM.
 * When we call get_mce_event(), we are still in पूर्णांकerrupt context and
 * preemption will not be scheduled until ret_from_expect() routine
 * is called.
 */
पूर्णांक get_mce_event(काष्ठा machine_check_event *mce, bool release)
अणु
	पूर्णांक index = local_paca->mce_info->mce_nest_count - 1;
	काष्ठा machine_check_event *mc_evt;
	पूर्णांक ret = 0;

	/* Sanity check */
	अगर (index < 0)
		वापस ret;

	/* Check अगर we have MCE info to process. */
	अगर (index < MAX_MC_EVT) अणु
		mc_evt = &local_paca->mce_info->mce_event[index];
		/* Copy the event काष्ठाure and release the original */
		अगर (mce)
			*mce = *mc_evt;
		अगर (release)
			mc_evt->in_use = 0;
		ret = 1;
	पूर्ण
	/* Decrement the count to मुक्त the slot. */
	अगर (release)
		local_paca->mce_info->mce_nest_count--;

	वापस ret;
पूर्ण

व्योम release_mce_event(व्योम)
अणु
	get_mce_event(शून्य, true);
पूर्ण

अटल व्योम machine_check_ue_irq_work(काष्ठा irq_work *work)
अणु
	schedule_work(&mce_ue_event_work);
पूर्ण

/*
 * Queue up the MCE event which then can be handled later.
 */
अटल व्योम machine_check_ue_event(काष्ठा machine_check_event *evt)
अणु
	पूर्णांक index;

	index = local_paca->mce_info->mce_ue_count++;
	/* If queue is full, just वापस क्रम now. */
	अगर (index >= MAX_MC_EVT) अणु
		local_paca->mce_info->mce_ue_count--;
		वापस;
	पूर्ण
	स_नकल(&local_paca->mce_info->mce_ue_event_queue[index],
	       evt, माप(*evt));

	/* Queue work to process this event later. */
	irq_work_queue(&mce_ue_event_irq_work);
पूर्ण

/*
 * Queue up the MCE event which then can be handled later.
 */
व्योम machine_check_queue_event(व्योम)
अणु
	पूर्णांक index;
	काष्ठा machine_check_event evt;

	अगर (!get_mce_event(&evt, MCE_EVENT_RELEASE))
		वापस;

	index = local_paca->mce_info->mce_queue_count++;
	/* If queue is full, just वापस क्रम now. */
	अगर (index >= MAX_MC_EVT) अणु
		local_paca->mce_info->mce_queue_count--;
		वापस;
	पूर्ण
	स_नकल(&local_paca->mce_info->mce_event_queue[index],
	       &evt, माप(evt));

	/* Queue irq work to process this event later. */
	irq_work_queue(&mce_event_process_work);
पूर्ण

व्योम mce_common_process_ue(काष्ठा pt_regs *regs,
			   काष्ठा mce_error_info *mce_err)
अणु
	स्थिर काष्ठा exception_table_entry *entry;

	entry = search_kernel_exception_table(regs->nip);
	अगर (entry) अणु
		mce_err->ignore_event = true;
		regs->nip = extable_fixup(entry);
	पूर्ण
पूर्ण

/*
 * process pending MCE event from the mce event queue. This function will be
 * called during syscall निकास.
 */
अटल व्योम machine_process_ue_event(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक index;
	काष्ठा machine_check_event *evt;

	जबतक (local_paca->mce_info->mce_ue_count > 0) अणु
		index = local_paca->mce_info->mce_ue_count - 1;
		evt = &local_paca->mce_info->mce_ue_event_queue[index];
		blocking_notअगरier_call_chain(&mce_notअगरier_list, 0, evt);
#अगर_घोषित CONFIG_MEMORY_FAILURE
		/*
		 * This should probably queued अन्यथाwhere, but
		 * oh! well
		 *
		 * Don't report this machine check because the caller has a
		 * asked us to ignore the event, it has a fixup handler which
		 * will करो the appropriate error handling and reporting.
		 */
		अगर (evt->error_type == MCE_ERROR_TYPE_UE) अणु
			अगर (evt->u.ue_error.ignore_event) अणु
				local_paca->mce_info->mce_ue_count--;
				जारी;
			पूर्ण

			अगर (evt->u.ue_error.physical_address_provided) अणु
				अचिन्हित दीर्घ pfn;

				pfn = evt->u.ue_error.physical_address >>
					PAGE_SHIFT;
				memory_failure(pfn, 0);
			पूर्ण अन्यथा
				pr_warn("Failed to identify bad address from "
					"where the uncorrectable error (UE) "
					"was generated\n");
		पूर्ण
#पूर्ण_अगर
		local_paca->mce_info->mce_ue_count--;
	पूर्ण
पूर्ण
/*
 * process pending MCE event from the mce event queue. This function will be
 * called during syscall निकास.
 */
अटल व्योम machine_check_process_queued_event(काष्ठा irq_work *work)
अणु
	पूर्णांक index;
	काष्ठा machine_check_event *evt;

	add_taपूर्णांक(TAINT_MACHINE_CHECK, LOCKDEP_NOW_UNRELIABLE);

	/*
	 * For now just prपूर्णांक it to console.
	 * TODO: log this error event to FSP or nvram.
	 */
	जबतक (local_paca->mce_info->mce_queue_count > 0) अणु
		index = local_paca->mce_info->mce_queue_count - 1;
		evt = &local_paca->mce_info->mce_event_queue[index];

		अगर (evt->error_type == MCE_ERROR_TYPE_UE &&
		    evt->u.ue_error.ignore_event) अणु
			local_paca->mce_info->mce_queue_count--;
			जारी;
		पूर्ण
		machine_check_prपूर्णांक_event_info(evt, false, false);
		local_paca->mce_info->mce_queue_count--;
	पूर्ण
पूर्ण

व्योम machine_check_prपूर्णांक_event_info(काष्ठा machine_check_event *evt,
				    bool user_mode, bool in_guest)
अणु
	स्थिर अक्षर *level, *sevstr, *subtype, *err_type, *initiator;
	uपूर्णांक64_t ea = 0, pa = 0;
	पूर्णांक n = 0;
	अक्षर dar_str[50];
	अक्षर pa_str[50];
	अटल स्थिर अक्षर *mc_ue_types[] = अणु
		"Indeterminate",
		"Instruction fetch",
		"Page table walk ifetch",
		"Load/Store",
		"Page table walk Load/Store",
	पूर्ण;
	अटल स्थिर अक्षर *mc_slb_types[] = अणु
		"Indeterminate",
		"Parity",
		"Multihit",
	पूर्ण;
	अटल स्थिर अक्षर *mc_erat_types[] = अणु
		"Indeterminate",
		"Parity",
		"Multihit",
	पूर्ण;
	अटल स्थिर अक्षर *mc_tlb_types[] = अणु
		"Indeterminate",
		"Parity",
		"Multihit",
	पूर्ण;
	अटल स्थिर अक्षर *mc_user_types[] = अणु
		"Indeterminate",
		"tlbie(l) invalid",
		"scv invalid",
	पूर्ण;
	अटल स्थिर अक्षर *mc_ra_types[] = अणु
		"Indeterminate",
		"Instruction fetch (bad)",
		"Instruction fetch (foreign)",
		"Page table walk ifetch (bad)",
		"Page table walk ifetch (foreign)",
		"Load (bad)",
		"Store (bad)",
		"Page table walk Load/Store (bad)",
		"Page table walk Load/Store (foreign)",
		"Load/Store (foreign)",
	पूर्ण;
	अटल स्थिर अक्षर *mc_link_types[] = अणु
		"Indeterminate",
		"Instruction fetch (timeout)",
		"Page table walk ifetch (timeout)",
		"Load (timeout)",
		"Store (timeout)",
		"Page table walk Load/Store (timeout)",
	पूर्ण;
	अटल स्थिर अक्षर *mc_error_class[] = अणु
		"Unknown",
		"Hardware error",
		"Probable Hardware error (some chance of software cause)",
		"Software error",
		"Probable Software error (some chance of hardware cause)",
	पूर्ण;

	/* Prपूर्णांक things out */
	अगर (evt->version != MCE_V1) अणु
		pr_err("Machine Check Exception, Unknown event version %d !\n",
		       evt->version);
		वापस;
	पूर्ण
	चयन (evt->severity) अणु
	हाल MCE_SEV_NO_ERROR:
		level = KERN_INFO;
		sevstr = "Harmless";
		अवरोध;
	हाल MCE_SEV_WARNING:
		level = KERN_WARNING;
		sevstr = "Warning";
		अवरोध;
	हाल MCE_SEV_SEVERE:
		level = KERN_ERR;
		sevstr = "Severe";
		अवरोध;
	हाल MCE_SEV_FATAL:
	शेष:
		level = KERN_ERR;
		sevstr = "Fatal";
		अवरोध;
	पूर्ण

	चयन(evt->initiator) अणु
	हाल MCE_INITIATOR_CPU:
		initiator = "CPU";
		अवरोध;
	हाल MCE_INITIATOR_PCI:
		initiator = "PCI";
		अवरोध;
	हाल MCE_INITIATOR_ISA:
		initiator = "ISA";
		अवरोध;
	हाल MCE_INITIATOR_MEMORY:
		initiator = "Memory";
		अवरोध;
	हाल MCE_INITIATOR_POWERMGM:
		initiator = "Power Management";
		अवरोध;
	हाल MCE_INITIATOR_UNKNOWN:
	शेष:
		initiator = "Unknown";
		अवरोध;
	पूर्ण

	चयन (evt->error_type) अणु
	हाल MCE_ERROR_TYPE_UE:
		err_type = "UE";
		subtype = evt->u.ue_error.ue_error_type <
			ARRAY_SIZE(mc_ue_types) ?
			mc_ue_types[evt->u.ue_error.ue_error_type]
			: "Unknown";
		अगर (evt->u.ue_error.effective_address_provided)
			ea = evt->u.ue_error.effective_address;
		अगर (evt->u.ue_error.physical_address_provided)
			pa = evt->u.ue_error.physical_address;
		अवरोध;
	हाल MCE_ERROR_TYPE_SLB:
		err_type = "SLB";
		subtype = evt->u.slb_error.slb_error_type <
			ARRAY_SIZE(mc_slb_types) ?
			mc_slb_types[evt->u.slb_error.slb_error_type]
			: "Unknown";
		अगर (evt->u.slb_error.effective_address_provided)
			ea = evt->u.slb_error.effective_address;
		अवरोध;
	हाल MCE_ERROR_TYPE_ERAT:
		err_type = "ERAT";
		subtype = evt->u.erat_error.erat_error_type <
			ARRAY_SIZE(mc_erat_types) ?
			mc_erat_types[evt->u.erat_error.erat_error_type]
			: "Unknown";
		अगर (evt->u.erat_error.effective_address_provided)
			ea = evt->u.erat_error.effective_address;
		अवरोध;
	हाल MCE_ERROR_TYPE_TLB:
		err_type = "TLB";
		subtype = evt->u.tlb_error.tlb_error_type <
			ARRAY_SIZE(mc_tlb_types) ?
			mc_tlb_types[evt->u.tlb_error.tlb_error_type]
			: "Unknown";
		अगर (evt->u.tlb_error.effective_address_provided)
			ea = evt->u.tlb_error.effective_address;
		अवरोध;
	हाल MCE_ERROR_TYPE_USER:
		err_type = "User";
		subtype = evt->u.user_error.user_error_type <
			ARRAY_SIZE(mc_user_types) ?
			mc_user_types[evt->u.user_error.user_error_type]
			: "Unknown";
		अगर (evt->u.user_error.effective_address_provided)
			ea = evt->u.user_error.effective_address;
		अवरोध;
	हाल MCE_ERROR_TYPE_RA:
		err_type = "Real address";
		subtype = evt->u.ra_error.ra_error_type <
			ARRAY_SIZE(mc_ra_types) ?
			mc_ra_types[evt->u.ra_error.ra_error_type]
			: "Unknown";
		अगर (evt->u.ra_error.effective_address_provided)
			ea = evt->u.ra_error.effective_address;
		अवरोध;
	हाल MCE_ERROR_TYPE_LINK:
		err_type = "Link";
		subtype = evt->u.link_error.link_error_type <
			ARRAY_SIZE(mc_link_types) ?
			mc_link_types[evt->u.link_error.link_error_type]
			: "Unknown";
		अगर (evt->u.link_error.effective_address_provided)
			ea = evt->u.link_error.effective_address;
		अवरोध;
	हाल MCE_ERROR_TYPE_DCACHE:
		err_type = "D-Cache";
		subtype = "Unknown";
		अवरोध;
	हाल MCE_ERROR_TYPE_ICACHE:
		err_type = "I-Cache";
		subtype = "Unknown";
		अवरोध;
	शेष:
	हाल MCE_ERROR_TYPE_UNKNOWN:
		err_type = "Unknown";
		subtype = "";
		अवरोध;
	पूर्ण

	dar_str[0] = pa_str[0] = '\0';
	अगर (ea && evt->srr0 != ea) अणु
		/* Load/Store address */
		n = प्र_लिखो(dar_str, "DAR: %016llx ", ea);
		अगर (pa)
			प्र_लिखो(dar_str + n, "paddr: %016llx ", pa);
	पूर्ण अन्यथा अगर (pa) अणु
		प्र_लिखो(pa_str, " paddr: %016llx", pa);
	पूर्ण

	prपूर्णांकk("%sMCE: CPU%d: machine check (%s) %s %s %s %s[%s]\n",
		level, evt->cpu, sevstr, in_guest ? "Guest" : "",
		err_type, subtype, dar_str,
		evt->disposition == MCE_DISPOSITION_RECOVERED ?
		"Recovered" : "Not recovered");

	अगर (in_guest || user_mode) अणु
		prपूर्णांकk("%sMCE: CPU%d: PID: %d Comm: %s %sNIP: [%016llx]%s\n",
			level, evt->cpu, current->pid, current->comm,
			in_guest ? "Guest " : "", evt->srr0, pa_str);
	पूर्ण अन्यथा अणु
		prपूर्णांकk("%sMCE: CPU%d: NIP: [%016llx] %pS%s\n",
			level, evt->cpu, evt->srr0, (व्योम *)evt->srr0, pa_str);
	पूर्ण

	prपूर्णांकk("%sMCE: CPU%d: Initiator %s\n", level, evt->cpu, initiator);

	subtype = evt->error_class < ARRAY_SIZE(mc_error_class) ?
		mc_error_class[evt->error_class] : "Unknown";
	prपूर्णांकk("%sMCE: CPU%d: %s\n", level, evt->cpu, subtype);

#अगर_घोषित CONFIG_PPC_BOOK3S_64
	/* Display faulty slb contents क्रम SLB errors. */
	अगर (evt->error_type == MCE_ERROR_TYPE_SLB && !in_guest)
		slb_dump_contents(local_paca->mce_faulty_slbs);
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL_GPL(machine_check_prपूर्णांक_event_info);

/*
 * This function is called in real mode. Strictly no prपूर्णांकk's please.
 *
 * regs->nip and regs->msr contains srr0 and ssr1.
 */
DEFINE_INTERRUPT_HANDLER_NMI(machine_check_early)
अणु
	दीर्घ handled = 0;

	hv_nmi_check_nonrecoverable(regs);

	/*
	 * See अगर platक्रमm is capable of handling machine check.
	 */
	अगर (ppc_md.machine_check_early)
		handled = ppc_md.machine_check_early(regs);

	वापस handled;
पूर्ण

/* Possible meanings क्रम HMER_DEBUG_TRIG bit being set on POWER9 */
अटल क्रमागत अणु
	DTRIG_UNKNOWN,
	DTRIG_VECTOR_CI,	/* need to emulate vector CI load instr */
	DTRIG_SUSPEND_ESCAPE,	/* need to escape from TM suspend mode */
पूर्ण hmer_debug_trig_function;

अटल पूर्णांक init_debug_trig_function(व्योम)
अणु
	पूर्णांक pvr;
	काष्ठा device_node *cpun;
	काष्ठा property *prop = शून्य;
	स्थिर अक्षर *str;

	/* First look in the device tree */
	preempt_disable();
	cpun = of_get_cpu_node(smp_processor_id(), शून्य);
	अगर (cpun) अणु
		of_property_क्रम_each_string(cpun, "ibm,hmi-special-triggers",
					    prop, str) अणु
			अगर (म_भेद(str, "bit17-vector-ci-load") == 0)
				hmer_debug_trig_function = DTRIG_VECTOR_CI;
			अन्यथा अगर (म_भेद(str, "bit17-tm-suspend-escape") == 0)
				hmer_debug_trig_function = DTRIG_SUSPEND_ESCAPE;
		पूर्ण
		of_node_put(cpun);
	पूर्ण
	preempt_enable();

	/* If we found the property, करोn't look at PVR */
	अगर (prop)
		जाओ out;

	pvr = mfspr(SPRN_PVR);
	/* Check क्रम POWER9 Nimbus (scale-out) */
	अगर ((PVR_VER(pvr) == PVR_POWER9) && (pvr & 0xe000) == 0) अणु
		/* DD2.2 and later */
		अगर ((pvr & 0xfff) >= 0x202)
			hmer_debug_trig_function = DTRIG_SUSPEND_ESCAPE;
		/* DD2.0 and DD2.1 - used क्रम vector CI load emulation */
		अन्यथा अगर ((pvr & 0xfff) >= 0x200)
			hmer_debug_trig_function = DTRIG_VECTOR_CI;
	पूर्ण

 out:
	चयन (hmer_debug_trig_function) अणु
	हाल DTRIG_VECTOR_CI:
		pr_debug("HMI debug trigger used for vector CI load\n");
		अवरोध;
	हाल DTRIG_SUSPEND_ESCAPE:
		pr_debug("HMI debug trigger used for TM suspend escape\n");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण
__initcall(init_debug_trig_function);

/*
 * Handle HMIs that occur as a result of a debug trigger.
 * Return values:
 * -1 means this is not a HMI cause that we know about
 *  0 means no further handling is required
 *  1 means further handling is required
 */
दीर्घ hmi_handle_debugtrig(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ hmer = mfspr(SPRN_HMER);
	दीर्घ ret = 0;

	/* HMER_DEBUG_TRIG bit is used क्रम various workarounds on P9 */
	अगर (!((hmer & HMER_DEBUG_TRIG)
	      && hmer_debug_trig_function != DTRIG_UNKNOWN))
		वापस -1;
		
	hmer &= ~HMER_DEBUG_TRIG;
	/* HMER is a ग_लिखो-AND रेजिस्टर */
	mtspr(SPRN_HMER, ~HMER_DEBUG_TRIG);

	चयन (hmer_debug_trig_function) अणु
	हाल DTRIG_VECTOR_CI:
		/*
		 * Now to aव्योम problems with soft-disable we
		 * only करो the emulation अगर we are coming from
		 * host user space
		 */
		अगर (regs && user_mode(regs))
			ret = local_paca->hmi_p9_special_emu = 1;

		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	/*
	 * See अगर any other HMI causes reमुख्य to be handled
	 */
	अगर (hmer & mfspr(SPRN_HMEER))
		वापस -1;

	वापस ret;
पूर्ण

/*
 * Return values:
 */
DEFINE_INTERRUPT_HANDLER_NMI(hmi_exception_realmode)
अणु	
	पूर्णांक ret;

	local_paca->hmi_irqs++;

	ret = hmi_handle_debugtrig(regs);
	अगर (ret >= 0)
		वापस ret;

	रुको_क्रम_subcore_guest_निकास();

	अगर (ppc_md.hmi_exception_early)
		ppc_md.hmi_exception_early(regs);

	रुको_क्रम_tb_resync();

	वापस 1;
पूर्ण

व्योम __init mce_init(व्योम)
अणु
	काष्ठा mce_info *mce_info;
	u64 limit;
	पूर्णांक i;

	limit = min(ppc64_bolted_size(), ppc64_rma_size);
	क्रम_each_possible_cpu(i) अणु
		mce_info = memblock_alloc_try_nid(माप(*mce_info),
						  __alignof__(*mce_info),
						  MEMBLOCK_LOW_LIMIT,
						  limit, cpu_to_node(i));
		अगर (!mce_info)
			जाओ err;
		paca_ptrs[i]->mce_info = mce_info;
	पूर्ण
	वापस;
err:
	panic("Failed to allocate memory for MCE event data\n");
पूर्ण
