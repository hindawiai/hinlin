<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * VAS Fault handling.
 * Copyright 2019, IBM Corporation
 */

#घोषणा pr_fmt(fmt) "vas: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/mmu_context.h>
#समावेश <यंत्र/icswx.h>

#समावेश "vas.h"

/*
 * The maximum FIFO size क्रम fault winकरोw can be 8MB
 * (VAS_RX_FIFO_SIZE_MAX). Using 4MB FIFO since each VAS
 * instance will be having fault winकरोw.
 * 8MB FIFO can be used अगर expects more faults क्रम each VAS
 * instance.
 */
#घोषणा VAS_FAULT_WIN_FIFO_SIZE	(4 << 20)

अटल व्योम dump_crb(काष्ठा coprocessor_request_block *crb)
अणु
	काष्ठा data_descriptor_entry *dde;
	काष्ठा nx_fault_stamp *nx;

	dde = &crb->source;
	pr_devel("SrcDDE: addr 0x%llx, len %d, count %d, idx %d, flags %d\n",
		be64_to_cpu(dde->address), be32_to_cpu(dde->length),
		dde->count, dde->index, dde->flags);

	dde = &crb->target;
	pr_devel("TgtDDE: addr 0x%llx, len %d, count %d, idx %d, flags %d\n",
		be64_to_cpu(dde->address), be32_to_cpu(dde->length),
		dde->count, dde->index, dde->flags);

	nx = &crb->stamp.nx;
	pr_devel("NX Stamp: PSWID 0x%x, FSA 0x%llx, flags 0x%x, FS 0x%x\n",
		be32_to_cpu(nx->pswid),
		be64_to_cpu(crb->stamp.nx.fault_storage_addr),
		nx->flags, nx->fault_status);
पूर्ण

/*
 * Update the CSB to indicate a translation error.
 *
 * User space will be polling on CSB after the request is issued.
 * If NX can handle the request without any issues, it updates CSB.
 * Whereas अगर NX encounters page fault, the kernel will handle the
 * fault and update CSB with translation error.
 *
 * If we are unable to update the CSB means copy_to_user failed due to
 * invalid csb_addr, send a संकेत to the process.
 */
अटल व्योम update_csb(काष्ठा vas_winकरोw *winकरोw,
			काष्ठा coprocessor_request_block *crb)
अणु
	काष्ठा coprocessor_status_block csb;
	काष्ठा kernel_siginfo info;
	काष्ठा task_काष्ठा *tsk;
	व्योम __user *csb_addr;
	काष्ठा pid *pid;
	पूर्णांक rc;

	/*
	 * NX user space winकरोws can not be खोलोed क्रम task->mm=शून्य
	 * and faults will not be generated क्रम kernel requests.
	 */
	अगर (WARN_ON_ONCE(!winकरोw->mm || !winकरोw->user_win))
		वापस;

	csb_addr = (व्योम __user *)be64_to_cpu(crb->csb_addr);

	स_रखो(&csb, 0, माप(csb));
	csb.cc = CSB_CC_FAULT_ADDRESS;
	csb.ce = CSB_CE_TERMINATION;
	csb.cs = 0;
	csb.count = 0;

	/*
	 * NX operates and वापसs in BE क्रमmat as defined CRB काष्ठा.
	 * So saves fault_storage_addr in BE as NX pastes in FIFO and
	 * expects user space to convert to CPU क्रमmat.
	 */
	csb.address = crb->stamp.nx.fault_storage_addr;
	csb.flags = 0;

	pid = winकरोw->pid;
	tsk = get_pid_task(pid, PIDTYPE_PID);
	/*
	 * Process बंदs send winकरोw after all pending NX requests are
	 * completed. In multi-thपढ़ो applications, a child thपढ़ो can
	 * खोलो a winकरोw and can निकास without closing it. May be some
	 * requests are pending or this winकरोw can be used by other
	 * thपढ़ोs later. We should handle faults अगर NX encounters
	 * pages faults on these requests. Update CSB with translation
	 * error and fault address. If csb_addr passed by user space is
	 * invalid, send SEGV संकेत to pid saved in winकरोw. If the
	 * child thपढ़ो is not running, send the संकेत to tgid.
	 * Parent thपढ़ो (tgid) will बंद this winकरोw upon its निकास.
	 *
	 * pid and mm references are taken when winकरोw is खोलोed by
	 * process (pid). So tgid is used only when child thपढ़ो खोलोs
	 * a winकरोw and निकासs without closing it.
	 */
	अगर (!tsk) अणु
		pid = winकरोw->tgid;
		tsk = get_pid_task(pid, PIDTYPE_PID);
		/*
		 * Parent thपढ़ो (tgid) will be closing winकरोw when it
		 * निकासs. So should not get here.
		 */
		अगर (WARN_ON_ONCE(!tsk))
			वापस;
	पूर्ण

	/* Return अगर the task is निकासing. */
	अगर (tsk->flags & PF_EXITING) अणु
		put_task_काष्ठा(tsk);
		वापस;
	पूर्ण

	kthपढ़ो_use_mm(winकरोw->mm);
	rc = copy_to_user(csb_addr, &csb, माप(csb));
	/*
	 * User space polls on csb.flags (first byte). So add barrier
	 * then copy first byte with csb flags update.
	 */
	अगर (!rc) अणु
		csb.flags = CSB_V;
		/* Make sure update to csb.flags is visible now */
		smp_mb();
		rc = copy_to_user(csb_addr, &csb, माप(u8));
	पूर्ण
	kthपढ़ो_unuse_mm(winकरोw->mm);
	put_task_काष्ठा(tsk);

	/* Success */
	अगर (!rc)
		वापस;

	pr_debug("Invalid CSB address 0x%p signalling pid(%d)\n",
			csb_addr, pid_vnr(pid));

	clear_siginfo(&info);
	info.si_signo = संक_अंश;
	info.si_त्रुटि_सं = EFAULT;
	info.si_code = SEGV_MAPERR;
	info.si_addr = csb_addr;

	/*
	 * process will be polling on csb.flags after request is sent to
	 * NX. So generally CSB update should not fail except when an
	 * application passes invalid csb_addr. So an error message will
	 * be displayed and leave it to user space whether to ignore or
	 * handle this संकेत.
	 */
	rcu_पढ़ो_lock();
	rc = समाप्त_pid_info(संक_अंश, &info, pid);
	rcu_पढ़ो_unlock();

	pr_devel("%s(): pid %d kill_proc_info() rc %d\n", __func__,
			pid_vnr(pid), rc);
पूर्ण

अटल व्योम dump_fअगरo(काष्ठा vas_instance *vinst, व्योम *entry)
अणु
	अचिन्हित दीर्घ *end = vinst->fault_fअगरo + vinst->fault_fअगरo_size;
	अचिन्हित दीर्घ *fअगरo = entry;
	पूर्णांक i;

	pr_err("Fault fifo size %d, Max crbs %d\n", vinst->fault_fअगरo_size,
			vinst->fault_fअगरo_size / CRB_SIZE);

	/* Dump 10 CRB entries or until end of FIFO */
	pr_err("Fault FIFO Dump:\n");
	क्रम (i = 0; i < 10*(CRB_SIZE/8) && fअगरo < end; i += 4, fअगरo += 4) अणु
		pr_err("[%.3d, %p]: 0x%.16lx 0x%.16lx 0x%.16lx 0x%.16lx\n",
			i, fअगरo, *fअगरo, *(fअगरo+1), *(fअगरo+2), *(fअगरo+3));
	पूर्ण
पूर्ण

/*
 * Process valid CRBs in fault FIFO.
 * NX process user space requests, वापस credit and update the status
 * in CRB. If it encounters transalation error when accessing CRB or
 * request buffers, उठाओs पूर्णांकerrupt on the CPU to handle the fault.
 * It takes credit on fault winकरोw, updates nx_fault_stamp in CRB with
 * the following inक्रमmation and pastes CRB in fault FIFO.
 *
 * pswid - winकरोw ID of the winकरोw on which the request is sent.
 * fault_storage_addr - fault address
 *
 * It can उठाओ a single पूर्णांकerrupt क्रम multiple faults. Expects OS to
 * process all valid faults and वापस credit क्रम each fault on user
 * space and fault winकरोws. This fault FIFO control will be करोne with
 * credit mechanism. NX can continuously paste CRBs until credits are not
 * available on fault winकरोw. Otherwise, वापसs with RMA_reject.
 *
 * Total credits available on fault winकरोw: FIFO_SIZE(4MB)/CRBS_SIZE(128)
 *
 */
irqवापस_t vas_fault_thपढ़ो_fn(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा vas_instance *vinst = data;
	काष्ठा coprocessor_request_block *crb, *entry;
	काष्ठा coprocessor_request_block buf;
	काष्ठा vas_winकरोw *winकरोw;
	अचिन्हित दीर्घ flags;
	व्योम *fअगरo;

	crb = &buf;

	/*
	 * VAS can पूर्णांकerrupt with multiple page faults. So process all
	 * valid CRBs within fault FIFO until reaches invalid CRB.
	 * We use CCW[0] and pswid to validate validate CRBs:
	 *
	 * CCW[0]	Reserved bit. When NX pastes CRB, CCW[0]=0
	 *		OS sets this bit to 1 after पढ़ोing CRB.
	 * pswid	NX assigns winकरोw ID. Set pswid to -1 after
	 *		पढ़ोing CRB from fault FIFO.
	 *
	 * We निकास this function अगर no valid CRBs are available to process.
	 * So acquire fault_lock and reset fअगरo_in_progress to 0 beक्रमe
	 * निकास.
	 * In हाल kernel receives another पूर्णांकerrupt with dअगरferent page
	 * fault, पूर्णांकerrupt handler वापसs with IRQ_HANDLED अगर
	 * fअगरo_in_progress is set. Means these new faults will be
	 * handled by the current thपढ़ो. Otherwise set fअगरo_in_progress
	 * and वापस IRQ_WAKE_THREAD to wake up thपढ़ो.
	 */
	जबतक (true) अणु
		spin_lock_irqsave(&vinst->fault_lock, flags);
		/*
		 * Advance the fault fअगरo poपूर्णांकer to next CRB.
		 * Use CRB_SIZE rather than माप(*crb) since the latter is
		 * aligned to CRB_ALIGN (256) but the CRB written to by VAS is
		 * only CRB_SIZE in len.
		 */
		fअगरo = vinst->fault_fअगरo + (vinst->fault_crbs * CRB_SIZE);
		entry = fअगरo;

		अगर ((entry->stamp.nx.pswid == cpu_to_be32(FIFO_INVALID_ENTRY))
			|| (entry->ccw & cpu_to_be32(CCW0_INVALID))) अणु
			vinst->fअगरo_in_progress = 0;
			spin_unlock_irqrestore(&vinst->fault_lock, flags);
			वापस IRQ_HANDLED;
		पूर्ण

		spin_unlock_irqrestore(&vinst->fault_lock, flags);
		vinst->fault_crbs++;
		अगर (vinst->fault_crbs == (vinst->fault_fअगरo_size / CRB_SIZE))
			vinst->fault_crbs = 0;

		स_नकल(crb, fअगरo, CRB_SIZE);
		entry->stamp.nx.pswid = cpu_to_be32(FIFO_INVALID_ENTRY);
		entry->ccw |= cpu_to_be32(CCW0_INVALID);
		/*
		 * Return credit क्रम the fault winकरोw.
		 */
		vas_वापस_credit(vinst->fault_win, false);

		pr_devel("VAS[%d] fault_fifo %p, fifo %p, fault_crbs %d\n",
				vinst->vas_id, vinst->fault_fअगरo, fअगरo,
				vinst->fault_crbs);

		dump_crb(crb);
		winकरोw = vas_pswid_to_winकरोw(vinst,
				be32_to_cpu(crb->stamp.nx.pswid));

		अगर (IS_ERR(winकरोw)) अणु
			/*
			 * We got an पूर्णांकerrupt about a specअगरic send
			 * winकरोw but we can't find that window and we can't
			 * even clean it up (वापस credit on user space
			 * winकरोw).
			 * But we should not get here.
			 * TODO: Disable IRQ.
			 */
			dump_fअगरo(vinst, (व्योम *)entry);
			pr_err("VAS[%d] fault_fifo %p, fifo %p, pswid 0x%x, fault_crbs %d bad CRB?\n",
				vinst->vas_id, vinst->fault_fअगरo, fअगरo,
				be32_to_cpu(crb->stamp.nx.pswid),
				vinst->fault_crbs);

			WARN_ON_ONCE(1);
		पूर्ण अन्यथा अणु
			update_csb(winकरोw, crb);
			/*
			 * Return credit क्रम send winकरोw after processing
			 * fault CRB.
			 */
			vas_वापस_credit(winकरोw, true);
		पूर्ण
	पूर्ण
पूर्ण

irqवापस_t vas_fault_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा vas_instance *vinst = dev_id;
	irqवापस_t ret = IRQ_WAKE_THREAD;
	अचिन्हित दीर्घ flags;

	/*
	 * NX can generate an पूर्णांकerrupt क्रम multiple faults. So the
	 * fault handler thपढ़ो process all CRBs until finds invalid
	 * entry. In हाल अगर NX sees continuous faults, it is possible
	 * that the thपढ़ो function entered with the first पूर्णांकerrupt
	 * can execute and process all valid CRBs.
	 * So wake up thपढ़ो only अगर the fault thपढ़ो is not in progress.
	 */
	spin_lock_irqsave(&vinst->fault_lock, flags);

	अगर (vinst->fअगरo_in_progress)
		ret = IRQ_HANDLED;
	अन्यथा
		vinst->fअगरo_in_progress = 1;

	spin_unlock_irqrestore(&vinst->fault_lock, flags);

	वापस ret;
पूर्ण

/*
 * Fault winकरोw is खोलोed per VAS instance. NX pastes fault CRB in fault
 * FIFO upon page faults.
 */
पूर्णांक vas_setup_fault_winकरोw(काष्ठा vas_instance *vinst)
अणु
	काष्ठा vas_rx_win_attr attr;

	vinst->fault_fअगरo_size = VAS_FAULT_WIN_FIFO_SIZE;
	vinst->fault_fअगरo = kzalloc(vinst->fault_fअगरo_size, GFP_KERNEL);
	अगर (!vinst->fault_fअगरo) अणु
		pr_err("Unable to alloc %d bytes for fault_fifo\n",
				vinst->fault_fअगरo_size);
		वापस -ENOMEM;
	पूर्ण

	/*
	 * Invalidate all CRB entries. NX pastes valid entry क्रम each fault.
	 */
	स_रखो(vinst->fault_fअगरo, FIFO_INVALID_ENTRY, vinst->fault_fअगरo_size);
	vas_init_rx_win_attr(&attr, VAS_COP_TYPE_FAULT);

	attr.rx_fअगरo_size = vinst->fault_fअगरo_size;
	attr.rx_fअगरo = vinst->fault_fअगरo;

	/*
	 * Max creds is based on number of CRBs can fit in the FIFO.
	 * (fault_fअगरo_size/CRB_SIZE). If 8MB FIFO is used, max creds
	 * will be 0xffff since the receive creds field is 16bits wide.
	 */
	attr.wcreds_max = vinst->fault_fअगरo_size / CRB_SIZE;
	attr.lnotअगरy_lpid = 0;
	attr.lnotअगरy_pid = mfspr(SPRN_PID);
	attr.lnotअगरy_tid = mfspr(SPRN_PID);

	vinst->fault_win = vas_rx_win_खोलो(vinst->vas_id, VAS_COP_TYPE_FAULT,
					&attr);

	अगर (IS_ERR(vinst->fault_win)) अणु
		pr_err("VAS: Error %ld opening FaultWin\n",
			PTR_ERR(vinst->fault_win));
		kमुक्त(vinst->fault_fअगरo);
		वापस PTR_ERR(vinst->fault_win);
	पूर्ण

	pr_devel("VAS: Created FaultWin %d, LPID/PID/TID [%d/%d/%d]\n",
			vinst->fault_win->winid, attr.lnotअगरy_lpid,
			attr.lnotअगरy_pid, attr.lnotअगरy_tid);

	वापस 0;
पूर्ण
