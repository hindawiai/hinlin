<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2001 Dave Engebretsen IBM Corporation
 */

#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/of.h>
#समावेश <linux/fs.h>
#समावेश <linux/reboot.h>
#समावेश <linux/irq_work.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/mce.h>

#समावेश "pseries.h"

अटल अचिन्हित अक्षर ras_log_buf[RTAS_ERROR_LOG_MAX];
अटल DEFINE_SPINLOCK(ras_log_buf_lock);

अटल पूर्णांक ras_check_exception_token;

अटल व्योम mce_process_errlog_event(काष्ठा irq_work *work);
अटल काष्ठा irq_work mce_errlog_process_work = अणु
	.func = mce_process_errlog_event,
पूर्ण;

#घोषणा EPOW_SENSOR_TOKEN	9
#घोषणा EPOW_SENSOR_INDEX	0

/* EPOW events counter variable */
अटल पूर्णांक num_eघात_events;

अटल irqवापस_t ras_hotplug_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल irqवापस_t ras_eघात_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल irqवापस_t ras_error_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);

/* RTAS pseries MCE errorlog section. */
काष्ठा pseries_mc_errorlog अणु
	__be32	fru_id;
	__be32	proc_id;
	u8	error_type;
	/*
	 * sub_err_type (1 byte). Bit fields depends on error_type
	 *
	 *   MSB0
	 *   |
	 *   V
	 *   01234567
	 *   XXXXXXXX
	 *
	 * For error_type == MC_ERROR_TYPE_UE
	 *   XXXXXXXX
	 *   X		1: Permanent or Transient UE.
	 *    X		1: Effective address provided.
	 *     X	1: Logical address provided.
	 *      XX	2: Reserved.
	 *        XXX	3: Type of UE error.
	 *
	 * For error_type != MC_ERROR_TYPE_UE
	 *   XXXXXXXX
	 *   X		1: Effective address provided.
	 *    XXXXX	5: Reserved.
	 *         XX	2: Type of SLB/ERAT/TLB error.
	 */
	u8	sub_err_type;
	u8	reserved_1[6];
	__be64	effective_address;
	__be64	logical_address;
पूर्ण __packed;

/* RTAS pseries MCE error types */
#घोषणा MC_ERROR_TYPE_UE		0x00
#घोषणा MC_ERROR_TYPE_SLB		0x01
#घोषणा MC_ERROR_TYPE_ERAT		0x02
#घोषणा MC_ERROR_TYPE_UNKNOWN		0x03
#घोषणा MC_ERROR_TYPE_TLB		0x04
#घोषणा MC_ERROR_TYPE_D_CACHE		0x05
#घोषणा MC_ERROR_TYPE_I_CACHE		0x07

/* RTAS pseries MCE error sub types */
#घोषणा MC_ERROR_UE_INDETERMINATE		0
#घोषणा MC_ERROR_UE_IFETCH			1
#घोषणा MC_ERROR_UE_PAGE_TABLE_WALK_IFETCH	2
#घोषणा MC_ERROR_UE_LOAD_STORE			3
#घोषणा MC_ERROR_UE_PAGE_TABLE_WALK_LOAD_STORE	4

#घोषणा UE_EFFECTIVE_ADDR_PROVIDED		0x40
#घोषणा UE_LOGICAL_ADDR_PROVIDED		0x20

#घोषणा MC_ERROR_SLB_PARITY		0
#घोषणा MC_ERROR_SLB_MULTIHIT		1
#घोषणा MC_ERROR_SLB_INDETERMINATE	2

#घोषणा MC_ERROR_ERAT_PARITY		1
#घोषणा MC_ERROR_ERAT_MULTIHIT		2
#घोषणा MC_ERROR_ERAT_INDETERMINATE	3

#घोषणा MC_ERROR_TLB_PARITY		1
#घोषणा MC_ERROR_TLB_MULTIHIT		2
#घोषणा MC_ERROR_TLB_INDETERMINATE	3

अटल अंतरभूत u8 rtas_mc_error_sub_type(स्थिर काष्ठा pseries_mc_errorlog *mlog)
अणु
	चयन (mlog->error_type) अणु
	हाल	MC_ERROR_TYPE_UE:
		वापस (mlog->sub_err_type & 0x07);
	हाल	MC_ERROR_TYPE_SLB:
	हाल	MC_ERROR_TYPE_ERAT:
	हाल	MC_ERROR_TYPE_TLB:
		वापस (mlog->sub_err_type & 0x03);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/*
 * Enable the hotplug पूर्णांकerrupt late because processing them may touch other
 * devices or प्रणालीs (e.g. hugepages) that have not been initialized at the
 * subsys stage.
 */
अटल पूर्णांक __init init_ras_hotplug_IRQ(व्योम)
अणु
	काष्ठा device_node *np;

	/* Hotplug Events */
	np = of_find_node_by_path("/event-sources/hot-plug-events");
	अगर (np != शून्य) अणु
		अगर (dlpar_workqueue_init() == 0)
			request_event_sources_irqs(np, ras_hotplug_पूर्णांकerrupt,
						   "RAS_HOTPLUG");
		of_node_put(np);
	पूर्ण

	वापस 0;
पूर्ण
machine_late_initcall(pseries, init_ras_hotplug_IRQ);

/*
 * Initialize handlers क्रम the set of पूर्णांकerrupts caused by hardware errors
 * and घातer प्रणाली events.
 */
अटल पूर्णांक __init init_ras_IRQ(व्योम)
अणु
	काष्ठा device_node *np;

	ras_check_exception_token = rtas_token("check-exception");

	/* Internal Errors */
	np = of_find_node_by_path("/event-sources/internal-errors");
	अगर (np != शून्य) अणु
		request_event_sources_irqs(np, ras_error_पूर्णांकerrupt,
					   "RAS_ERROR");
		of_node_put(np);
	पूर्ण

	/* EPOW Events */
	np = of_find_node_by_path("/event-sources/epow-events");
	अगर (np != शून्य) अणु
		request_event_sources_irqs(np, ras_eघात_पूर्णांकerrupt, "RAS_EPOW");
		of_node_put(np);
	पूर्ण

	वापस 0;
पूर्ण
machine_subsys_initcall(pseries, init_ras_IRQ);

#घोषणा EPOW_SHUTDOWN_NORMAL				1
#घोषणा EPOW_SHUTDOWN_ON_UPS				2
#घोषणा EPOW_SHUTDOWN_LOSS_OF_CRITICAL_FUNCTIONS	3
#घोषणा EPOW_SHUTDOWN_AMBIENT_TEMPERATURE_TOO_HIGH	4

अटल व्योम handle_प्रणाली_shutकरोwn(अक्षर event_modअगरier)
अणु
	चयन (event_modअगरier) अणु
	हाल EPOW_SHUTDOWN_NORMAL:
		pr_emerg("Power off requested\n");
		orderly_घातeroff(true);
		अवरोध;

	हाल EPOW_SHUTDOWN_ON_UPS:
		pr_emerg("Loss of system power detected. System is running on"
			 " UPS/battery. Check RTAS error log for details\n");
		अवरोध;

	हाल EPOW_SHUTDOWN_LOSS_OF_CRITICAL_FUNCTIONS:
		pr_emerg("Loss of system critical functions detected. Check"
			 " RTAS error log for details\n");
		orderly_घातeroff(true);
		अवरोध;

	हाल EPOW_SHUTDOWN_AMBIENT_TEMPERATURE_TOO_HIGH:
		pr_emerg("High ambient temperature detected. Check RTAS"
			 " error log for details\n");
		orderly_घातeroff(true);
		अवरोध;

	शेष:
		pr_err("Unknown power/cooling shutdown event (modifier = %d)\n",
			event_modअगरier);
	पूर्ण
पूर्ण

काष्ठा eघात_errorlog अणु
	अचिन्हित अक्षर sensor_value;
	अचिन्हित अक्षर event_modअगरier;
	अचिन्हित अक्षर extended_modअगरier;
	अचिन्हित अक्षर reserved;
	अचिन्हित अक्षर platक्रमm_reason;
पूर्ण;

#घोषणा EPOW_RESET			0
#घोषणा EPOW_WARN_COOLING		1
#घोषणा EPOW_WARN_POWER			2
#घोषणा EPOW_SYSTEM_SHUTDOWN		3
#घोषणा EPOW_SYSTEM_HALT		4
#घोषणा EPOW_MAIN_ENCLOSURE		5
#घोषणा EPOW_POWER_OFF			7

अटल व्योम rtas_parse_eघात_errlog(काष्ठा rtas_error_log *log)
अणु
	काष्ठा pseries_errorlog *pseries_log;
	काष्ठा eघात_errorlog *eघात_log;
	अक्षर action_code;
	अक्षर modअगरier;

	pseries_log = get_pseries_errorlog(log, PSERIES_ELOG_SECT_ID_EPOW);
	अगर (pseries_log == शून्य)
		वापस;

	eघात_log = (काष्ठा eघात_errorlog *)pseries_log->data;
	action_code = eघात_log->sensor_value & 0xF;	/* bottom 4 bits */
	modअगरier = eघात_log->event_modअगरier & 0xF;	/* bottom 4 bits */

	चयन (action_code) अणु
	हाल EPOW_RESET:
		अगर (num_eघात_events) अणु
			pr_info("Non critical power/cooling issue cleared\n");
			num_eघात_events--;
		पूर्ण
		अवरोध;

	हाल EPOW_WARN_COOLING:
		pr_info("Non-critical cooling issue detected. Check RTAS error"
			" log for details\n");
		अवरोध;

	हाल EPOW_WARN_POWER:
		pr_info("Non-critical power issue detected. Check RTAS error"
			" log for details\n");
		अवरोध;

	हाल EPOW_SYSTEM_SHUTDOWN:
		handle_प्रणाली_shutकरोwn(modअगरier);
		अवरोध;

	हाल EPOW_SYSTEM_HALT:
		pr_emerg("Critical power/cooling issue detected. Check RTAS"
			 " error log for details. Powering off.\n");
		orderly_घातeroff(true);
		अवरोध;

	हाल EPOW_MAIN_ENCLOSURE:
	हाल EPOW_POWER_OFF:
		pr_emerg("System about to lose power. Check RTAS error log "
			 " for details. Powering off immediately.\n");
		emergency_sync();
		kernel_घातer_off();
		अवरोध;

	शेष:
		pr_err("Unknown power/cooling event (action code  = %d)\n",
			action_code);
	पूर्ण

	/* Increment eघात events counter variable */
	अगर (action_code != EPOW_RESET)
		num_eघात_events++;
पूर्ण

अटल irqवापस_t ras_hotplug_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pseries_errorlog *pseries_log;
	काष्ठा pseries_hp_errorlog *hp_elog;

	spin_lock(&ras_log_buf_lock);

	rtas_call(ras_check_exception_token, 6, 1, शून्य,
		  RTAS_VECTOR_EXTERNAL_INTERRUPT, virq_to_hw(irq),
		  RTAS_HOTPLUG_EVENTS, 0, __pa(&ras_log_buf),
		  rtas_get_error_log_max());

	pseries_log = get_pseries_errorlog((काष्ठा rtas_error_log *)ras_log_buf,
					   PSERIES_ELOG_SECT_ID_HOTPLUG);
	hp_elog = (काष्ठा pseries_hp_errorlog *)pseries_log->data;

	/*
	 * Since PCI hotplug is not currently supported on pseries, put PCI
	 * hotplug events on the ras_log_buf to be handled by rtas_errd.
	 */
	अगर (hp_elog->resource == PSERIES_HP_ELOG_RESOURCE_MEM ||
	    hp_elog->resource == PSERIES_HP_ELOG_RESOURCE_CPU ||
	    hp_elog->resource == PSERIES_HP_ELOG_RESOURCE_PMEM)
		queue_hotplug_event(hp_elog);
	अन्यथा
		log_error(ras_log_buf, ERR_TYPE_RTAS_LOG, 0);

	spin_unlock(&ras_log_buf_lock);
	वापस IRQ_HANDLED;
पूर्ण

/* Handle environmental and घातer warning (EPOW) पूर्णांकerrupts. */
अटल irqवापस_t ras_eघात_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक state;
	पूर्णांक critical;

	rtas_get_sensor_fast(EPOW_SENSOR_TOKEN, EPOW_SENSOR_INDEX, &state);

	अगर (state > 3)
		critical = 1;		/* Time Critical */
	अन्यथा
		critical = 0;

	spin_lock(&ras_log_buf_lock);

	rtas_call(ras_check_exception_token, 6, 1, शून्य, RTAS_VECTOR_EXTERNAL_INTERRUPT,
		  virq_to_hw(irq), RTAS_EPOW_WARNING, critical, __pa(&ras_log_buf),
		  rtas_get_error_log_max());

	log_error(ras_log_buf, ERR_TYPE_RTAS_LOG, 0);

	rtas_parse_eघात_errlog((काष्ठा rtas_error_log *)ras_log_buf);

	spin_unlock(&ras_log_buf_lock);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * Handle hardware error पूर्णांकerrupts.
 *
 * RTAS check-exception is called to collect data on the exception.  If
 * the error is deemed recoverable, we log a warning and वापस.
 * For nonrecoverable errors, an error is logged and we stop all processing
 * as quickly as possible in order to prevent propagation of the failure.
 */
अटल irqवापस_t ras_error_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा rtas_error_log *rtas_elog;
	पूर्णांक status;
	पूर्णांक fatal;

	spin_lock(&ras_log_buf_lock);

	status = rtas_call(ras_check_exception_token, 6, 1, शून्य,
			   RTAS_VECTOR_EXTERNAL_INTERRUPT,
			   virq_to_hw(irq),
			   RTAS_INTERNAL_ERROR, 1 /* Time Critical */,
			   __pa(&ras_log_buf),
				rtas_get_error_log_max());

	rtas_elog = (काष्ठा rtas_error_log *)ras_log_buf;

	अगर (status == 0 &&
	    rtas_error_severity(rtas_elog) >= RTAS_SEVERITY_ERROR_SYNC)
		fatal = 1;
	अन्यथा
		fatal = 0;

	/* क्रमmat and prपूर्णांक the extended inक्रमmation */
	log_error(ras_log_buf, ERR_TYPE_RTAS_LOG, fatal);

	अगर (fatal) अणु
		pr_emerg("Fatal hardware error detected. Check RTAS error"
			 " log for details. Powering off immediately\n");
		emergency_sync();
		kernel_घातer_off();
	पूर्ण अन्यथा अणु
		pr_err("Recoverable hardware error detected\n");
	पूर्ण

	spin_unlock(&ras_log_buf_lock);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * Some versions of FWNMI place the buffer inside the 4kB page starting at
 * 0x7000. Other versions place it inside the rtas buffer. We check both.
 * Minimum size of the buffer is 16 bytes.
 */
#घोषणा VALID_FWNMI_BUFFER(A) \
	((((A) >= 0x7000) && ((A) <= 0x8000 - 16)) || \
	(((A) >= rtas.base) && ((A) <= (rtas.base + rtas.size - 16))))

अटल अंतरभूत काष्ठा rtas_error_log *fwnmi_get_errlog(व्योम)
अणु
	वापस (काष्ठा rtas_error_log *)local_paca->mce_data_buf;
पूर्ण

अटल __be64 *fwnmi_get_savep(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ savep_ra;

	/* Mask top two bits */
	savep_ra = regs->gpr[3] & ~(0x3UL << 62);
	अगर (!VALID_FWNMI_BUFFER(savep_ra)) अणु
		prपूर्णांकk(KERN_ERR "FWNMI: corrupt r3 0x%016lx\n", regs->gpr[3]);
		वापस शून्य;
	पूर्ण

	वापस __va(savep_ra);
पूर्ण

/*
 * Get the error inक्रमmation क्रम errors coming through the
 * FWNMI vectors.  The pt_regs' r3 will be updated to reflect
 * the actual r3 अगर possible, and a ptr to the error log entry
 * will be वापसed अगर found.
 *
 * Use one buffer mce_data_buf per cpu to store RTAS error.
 *
 * The mce_data_buf करोes not have any locks or protection around it,
 * अगर a second machine check comes in, or a प्रणाली reset is करोne
 * beक्रमe we have logged the error, then we will get corruption in the
 * error log.  This is preferable over holding off on calling
 * ibm,nmi-पूर्णांकerlock which would result in us checkstopping अगर a
 * second machine check did come in.
 */
अटल काष्ठा rtas_error_log *fwnmi_get_errinfo(काष्ठा pt_regs *regs)
अणु
	काष्ठा rtas_error_log *h;
	__be64 *savep;

	savep = fwnmi_get_savep(regs);
	अगर (!savep)
		वापस शून्य;

	regs->gpr[3] = be64_to_cpu(savep[0]); /* restore original r3 */

	h = (काष्ठा rtas_error_log *)&savep[1];
	/* Use the per cpu buffer from paca to store rtas error log */
	स_रखो(local_paca->mce_data_buf, 0, RTAS_ERROR_LOG_MAX);
	अगर (!rtas_error_extended(h)) अणु
		स_नकल(local_paca->mce_data_buf, h, माप(__u64));
	पूर्ण अन्यथा अणु
		पूर्णांक len, error_log_length;

		error_log_length = 8 + rtas_error_extended_log_length(h);
		len = min_t(पूर्णांक, error_log_length, RTAS_ERROR_LOG_MAX);
		स_नकल(local_paca->mce_data_buf, h, len);
	पूर्ण

	वापस (काष्ठा rtas_error_log *)local_paca->mce_data_buf;
पूर्ण

/* Call this when करोne with the data वापसed by FWNMI_get_errinfo.
 * It will release the saved data area क्रम other CPUs in the
 * partition to receive FWNMI errors.
 */
अटल व्योम fwnmi_release_errinfo(व्योम)
अणु
	काष्ठा rtas_args rtas_args;
	पूर्णांक ret;

	/*
	 * On pseries, the machine check stack is limited to under 4GB, so
	 * args can be on-stack.
	 */
	rtas_call_unlocked(&rtas_args, ibm_nmi_पूर्णांकerlock_token, 0, 1, शून्य);
	ret = be32_to_cpu(rtas_args.rets[0]);
	अगर (ret != 0)
		prपूर्णांकk(KERN_ERR "FWNMI: nmi-interlock failed: %d\n", ret);
पूर्ण

पूर्णांक pSeries_प्रणाली_reset_exception(काष्ठा pt_regs *regs)
अणु
#अगर_घोषित __LITTLE_ENDIAN__
	/*
	 * Some firmware byteswaps SRR रेजिस्टरs and gives incorrect SRR1. Try
	 * to detect the bad SRR1 pattern here. Flip the NIP back to correct
	 * endian क्रम reporting purposes. Unक्रमtunately the MSR can't be fixed,
	 * so clear it. It will be missing MSR_RI so we won't try to recover.
	 */
	अगर ((be64_to_cpu(regs->msr) &
			(MSR_LE|MSR_RI|MSR_DR|MSR_IR|MSR_ME|MSR_PR|
			 MSR_ILE|MSR_HV|MSR_SF)) == (MSR_DR|MSR_SF)) अणु
		regs->nip = be64_to_cpu((__be64)regs->nip);
		regs->msr = 0;
	पूर्ण
#पूर्ण_अगर

	अगर (fwnmi_active) अणु
		__be64 *savep;

		/*
		 * Firmware (PowerVM and KVM) saves r3 to a save area like
		 * machine check, which is not exactly what PAPR (2.9)
		 * suggests but there is no way to detect otherwise, so this
		 * is the पूर्णांकerface now.
		 *
		 * System resets करो not save any error log or require an
		 * "ibm,nmi-interlock" rtas call to release.
		 */

		savep = fwnmi_get_savep(regs);
		अगर (savep)
			regs->gpr[3] = be64_to_cpu(savep[0]); /* restore original r3 */
	पूर्ण

	अगर (smp_handle_nmi_ipi(regs))
		वापस 1;

	वापस 0; /* need to perक्रमm reset */
पूर्ण

अटल पूर्णांक mce_handle_err_realmode(पूर्णांक disposition, u8 error_type)
अणु
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	अगर (disposition == RTAS_DISP_NOT_RECOVERED) अणु
		चयन (error_type) अणु
		हाल	MC_ERROR_TYPE_ERAT:
			flush_erat();
			disposition = RTAS_DISP_FULLY_RECOVERED;
			अवरोध;
		हाल	MC_ERROR_TYPE_SLB:
			/*
			 * Store the old slb content in paca beक्रमe flushing.
			 * Prपूर्णांक this when we go to भव mode.
			 * There are chances that we may hit MCE again अगर there
			 * is a parity error on the SLB entry we trying to पढ़ो
			 * क्रम saving. Hence limit the slb saving to single
			 * level of recursion.
			 */
			अगर (local_paca->in_mce == 1)
				slb_save_contents(local_paca->mce_faulty_slbs);
			flush_and_reload_slb();
			disposition = RTAS_DISP_FULLY_RECOVERED;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (disposition == RTAS_DISP_LIMITED_RECOVERY) अणु
		/* Platक्रमm corrected itself but could be degraded */
		pr_err("MCE: limited recovery, system may be degraded\n");
		disposition = RTAS_DISP_FULLY_RECOVERED;
	पूर्ण
#पूर्ण_अगर
	वापस disposition;
पूर्ण

अटल पूर्णांक mce_handle_err_virपंचांगode(काष्ठा pt_regs *regs,
				   काष्ठा rtas_error_log *errp,
				   काष्ठा pseries_mc_errorlog *mce_log,
				   पूर्णांक disposition)
अणु
	काष्ठा mce_error_info mce_err = अणु 0 पूर्ण;
	पूर्णांक initiator = rtas_error_initiator(errp);
	पूर्णांक severity = rtas_error_severity(errp);
	अचिन्हित दीर्घ eaddr = 0, paddr = 0;
	u8 error_type, err_sub_type;

	अगर (!mce_log)
		जाओ out;

	error_type = mce_log->error_type;
	err_sub_type = rtas_mc_error_sub_type(mce_log);

	अगर (initiator == RTAS_INITIATOR_UNKNOWN)
		mce_err.initiator = MCE_INITIATOR_UNKNOWN;
	अन्यथा अगर (initiator == RTAS_INITIATOR_CPU)
		mce_err.initiator = MCE_INITIATOR_CPU;
	अन्यथा अगर (initiator == RTAS_INITIATOR_PCI)
		mce_err.initiator = MCE_INITIATOR_PCI;
	अन्यथा अगर (initiator == RTAS_INITIATOR_ISA)
		mce_err.initiator = MCE_INITIATOR_ISA;
	अन्यथा अगर (initiator == RTAS_INITIATOR_MEMORY)
		mce_err.initiator = MCE_INITIATOR_MEMORY;
	अन्यथा अगर (initiator == RTAS_INITIATOR_POWERMGM)
		mce_err.initiator = MCE_INITIATOR_POWERMGM;
	अन्यथा
		mce_err.initiator = MCE_INITIATOR_UNKNOWN;

	अगर (severity == RTAS_SEVERITY_NO_ERROR)
		mce_err.severity = MCE_SEV_NO_ERROR;
	अन्यथा अगर (severity == RTAS_SEVERITY_EVENT)
		mce_err.severity = MCE_SEV_WARNING;
	अन्यथा अगर (severity == RTAS_SEVERITY_WARNING)
		mce_err.severity = MCE_SEV_WARNING;
	अन्यथा अगर (severity == RTAS_SEVERITY_ERROR_SYNC)
		mce_err.severity = MCE_SEV_SEVERE;
	अन्यथा अगर (severity == RTAS_SEVERITY_ERROR)
		mce_err.severity = MCE_SEV_SEVERE;
	अन्यथा अगर (severity == RTAS_SEVERITY_FATAL)
		mce_err.severity = MCE_SEV_FATAL;
	अन्यथा
		mce_err.severity = MCE_SEV_FATAL;

	अगर (severity <= RTAS_SEVERITY_ERROR_SYNC)
		mce_err.sync_error = true;
	अन्यथा
		mce_err.sync_error = false;

	mce_err.error_type = MCE_ERROR_TYPE_UNKNOWN;
	mce_err.error_class = MCE_ECLASS_UNKNOWN;

	चयन (error_type) अणु
	हाल MC_ERROR_TYPE_UE:
		mce_err.error_type = MCE_ERROR_TYPE_UE;
		mce_common_process_ue(regs, &mce_err);
		अगर (mce_err.ignore_event)
			disposition = RTAS_DISP_FULLY_RECOVERED;
		चयन (err_sub_type) अणु
		हाल MC_ERROR_UE_IFETCH:
			mce_err.u.ue_error_type = MCE_UE_ERROR_IFETCH;
			अवरोध;
		हाल MC_ERROR_UE_PAGE_TABLE_WALK_IFETCH:
			mce_err.u.ue_error_type = MCE_UE_ERROR_PAGE_TABLE_WALK_IFETCH;
			अवरोध;
		हाल MC_ERROR_UE_LOAD_STORE:
			mce_err.u.ue_error_type = MCE_UE_ERROR_LOAD_STORE;
			अवरोध;
		हाल MC_ERROR_UE_PAGE_TABLE_WALK_LOAD_STORE:
			mce_err.u.ue_error_type = MCE_UE_ERROR_PAGE_TABLE_WALK_LOAD_STORE;
			अवरोध;
		हाल MC_ERROR_UE_INDETERMINATE:
		शेष:
			mce_err.u.ue_error_type = MCE_UE_ERROR_INDETERMINATE;
			अवरोध;
		पूर्ण
		अगर (mce_log->sub_err_type & UE_EFFECTIVE_ADDR_PROVIDED)
			eaddr = be64_to_cpu(mce_log->effective_address);

		अगर (mce_log->sub_err_type & UE_LOGICAL_ADDR_PROVIDED) अणु
			paddr = be64_to_cpu(mce_log->logical_address);
		पूर्ण अन्यथा अगर (mce_log->sub_err_type & UE_EFFECTIVE_ADDR_PROVIDED) अणु
			अचिन्हित दीर्घ pfn;

			pfn = addr_to_pfn(regs, eaddr);
			अगर (pfn != अच_दीर्घ_उच्च)
				paddr = pfn << PAGE_SHIFT;
		पूर्ण

		अवरोध;
	हाल MC_ERROR_TYPE_SLB:
		mce_err.error_type = MCE_ERROR_TYPE_SLB;
		चयन (err_sub_type) अणु
		हाल MC_ERROR_SLB_PARITY:
			mce_err.u.slb_error_type = MCE_SLB_ERROR_PARITY;
			अवरोध;
		हाल MC_ERROR_SLB_MULTIHIT:
			mce_err.u.slb_error_type = MCE_SLB_ERROR_MULTIHIT;
			अवरोध;
		हाल MC_ERROR_SLB_INDETERMINATE:
		शेष:
			mce_err.u.slb_error_type = MCE_SLB_ERROR_INDETERMINATE;
			अवरोध;
		पूर्ण
		अगर (mce_log->sub_err_type & 0x80)
			eaddr = be64_to_cpu(mce_log->effective_address);
		अवरोध;
	हाल MC_ERROR_TYPE_ERAT:
		mce_err.error_type = MCE_ERROR_TYPE_ERAT;
		चयन (err_sub_type) अणु
		हाल MC_ERROR_ERAT_PARITY:
			mce_err.u.erat_error_type = MCE_ERAT_ERROR_PARITY;
			अवरोध;
		हाल MC_ERROR_ERAT_MULTIHIT:
			mce_err.u.erat_error_type = MCE_ERAT_ERROR_MULTIHIT;
			अवरोध;
		हाल MC_ERROR_ERAT_INDETERMINATE:
		शेष:
			mce_err.u.erat_error_type = MCE_ERAT_ERROR_INDETERMINATE;
			अवरोध;
		पूर्ण
		अगर (mce_log->sub_err_type & 0x80)
			eaddr = be64_to_cpu(mce_log->effective_address);
		अवरोध;
	हाल MC_ERROR_TYPE_TLB:
		mce_err.error_type = MCE_ERROR_TYPE_TLB;
		चयन (err_sub_type) अणु
		हाल MC_ERROR_TLB_PARITY:
			mce_err.u.tlb_error_type = MCE_TLB_ERROR_PARITY;
			अवरोध;
		हाल MC_ERROR_TLB_MULTIHIT:
			mce_err.u.tlb_error_type = MCE_TLB_ERROR_MULTIHIT;
			अवरोध;
		हाल MC_ERROR_TLB_INDETERMINATE:
		शेष:
			mce_err.u.tlb_error_type = MCE_TLB_ERROR_INDETERMINATE;
			अवरोध;
		पूर्ण
		अगर (mce_log->sub_err_type & 0x80)
			eaddr = be64_to_cpu(mce_log->effective_address);
		अवरोध;
	हाल MC_ERROR_TYPE_D_CACHE:
		mce_err.error_type = MCE_ERROR_TYPE_DCACHE;
		अवरोध;
	हाल MC_ERROR_TYPE_I_CACHE:
		mce_err.error_type = MCE_ERROR_TYPE_ICACHE;
		अवरोध;
	हाल MC_ERROR_TYPE_UNKNOWN:
	शेष:
		mce_err.error_type = MCE_ERROR_TYPE_UNKNOWN;
		अवरोध;
	पूर्ण
out:
	save_mce_event(regs, disposition == RTAS_DISP_FULLY_RECOVERED,
		       &mce_err, regs->nip, eaddr, paddr);
	वापस disposition;
पूर्ण

अटल पूर्णांक mce_handle_error(काष्ठा pt_regs *regs, काष्ठा rtas_error_log *errp)
अणु
	काष्ठा pseries_errorlog *pseries_log;
	काष्ठा pseries_mc_errorlog *mce_log = शून्य;
	पूर्णांक disposition = rtas_error_disposition(errp);
	अचिन्हित दीर्घ msr;
	u8 error_type;

	अगर (!rtas_error_extended(errp))
		जाओ out;

	pseries_log = get_pseries_errorlog(errp, PSERIES_ELOG_SECT_ID_MCE);
	अगर (!pseries_log)
		जाओ out;

	mce_log = (काष्ठा pseries_mc_errorlog *)pseries_log->data;
	error_type = mce_log->error_type;

	disposition = mce_handle_err_realmode(disposition, error_type);

	/*
	 * Enable translation as we will be accessing per-cpu variables
	 * in save_mce_event() which may fall outside RMO region, also
	 * leave it enabled because subsequently we will be queuing work
	 * to workqueues where again per-cpu variables accessed, besides
	 * fwnmi_release_errinfo() crashes when called in realmode on
	 * pseries.
	 * Note: All the realmode handling like flushing SLB entries क्रम
	 *       SLB multihit is करोne by now.
	 */
out:
	msr = mfmsr();
	mपंचांगsr(msr | MSR_IR | MSR_DR);

	disposition = mce_handle_err_virपंचांगode(regs, errp, mce_log,
					      disposition);

	/*
	 * Queue irq work to log this rtas event later.
	 * irq_work_queue uses per-cpu variables, so करो this in virt
	 * mode as well.
	 */
	irq_work_queue(&mce_errlog_process_work);

	mपंचांगsr(msr);

	वापस disposition;
पूर्ण

/*
 * Process MCE rtas errlog event.
 */
अटल व्योम mce_process_errlog_event(काष्ठा irq_work *work)
अणु
	काष्ठा rtas_error_log *err;

	err = fwnmi_get_errlog();
	log_error((अक्षर *)err, ERR_TYPE_RTAS_LOG, 0);
पूर्ण

/*
 * See अगर we can recover from a machine check exception.
 * This is only called on घातer4 (or above) and only via
 * the Firmware Non-Maskable Interrupts (fwnmi) handler
 * which provides the error analysis क्रम us.
 *
 * Return 1 अगर corrected (or delivered a संकेत).
 * Return 0 अगर there is nothing we can करो.
 */
अटल पूर्णांक recover_mce(काष्ठा pt_regs *regs, काष्ठा machine_check_event *evt)
अणु
	पूर्णांक recovered = 0;

	अगर (!(regs->msr & MSR_RI)) अणु
		/* If MSR_RI isn't set, we cannot recover */
		pr_err("Machine check interrupt unrecoverable: MSR(RI=0)\n");
		recovered = 0;
	पूर्ण अन्यथा अगर (evt->disposition == MCE_DISPOSITION_RECOVERED) अणु
		/* Platक्रमm corrected itself */
		recovered = 1;
	पूर्ण अन्यथा अगर (evt->severity == MCE_SEV_FATAL) अणु
		/* Fatal machine check */
		pr_err("Machine check interrupt is fatal\n");
		recovered = 0;
	पूर्ण

	अगर (!recovered && evt->sync_error) अणु
		/*
		 * Try to समाप्त processes अगर we get a synchronous machine check
		 * (e.g., one caused by execution of this inकाष्ठाion). This
		 * will devolve पूर्णांकo a panic अगर we try to समाप्त init or are in
		 * an पूर्णांकerrupt etc.
		 *
		 * TODO: Queue up this address क्रम hwpoisioning later.
		 * TODO: This is not quite right क्रम d-side machine
		 *       checks ->nip is not necessarily the important
		 *       address.
		 */
		अगर ((user_mode(regs))) अणु
			_exception(SIGBUS, regs, BUS_MCEERR_AR, regs->nip);
			recovered = 1;
		पूर्ण अन्यथा अगर (die_will_crash()) अणु
			/*
			 * die() would समाप्त the kernel, so better to go via
			 * the platक्रमm reboot code that will log the
			 * machine check.
			 */
			recovered = 0;
		पूर्ण अन्यथा अणु
			die_mce("Machine check", regs, SIGBUS);
			recovered = 1;
		पूर्ण
	पूर्ण

	वापस recovered;
पूर्ण

/*
 * Handle a machine check.
 *
 * Note that on Power 4 and beyond Firmware Non-Maskable Interrupts (fwnmi)
 * should be present.  If so the handler which called us tells us अगर the
 * error was recovered (never true अगर RI=0).
 *
 * On hardware prior to Power 4 these exceptions were asynchronous which
 * means we can't tell exactly where it occurred and so we can't recover.
 */
पूर्णांक pSeries_machine_check_exception(काष्ठा pt_regs *regs)
अणु
	काष्ठा machine_check_event evt;

	अगर (!get_mce_event(&evt, MCE_EVENT_RELEASE))
		वापस 0;

	/* Prपूर्णांक things out */
	अगर (evt.version != MCE_V1) अणु
		pr_err("Machine Check Exception, Unknown event version %d !\n",
		       evt.version);
		वापस 0;
	पूर्ण
	machine_check_prपूर्णांक_event_info(&evt, user_mode(regs), false);

	अगर (recover_mce(regs, &evt))
		वापस 1;

	वापस 0;
पूर्ण

दीर्घ pseries_machine_check_realmode(काष्ठा pt_regs *regs)
अणु
	काष्ठा rtas_error_log *errp;
	पूर्णांक disposition;

	अगर (fwnmi_active) अणु
		errp = fwnmi_get_errinfo(regs);
		/*
		 * Call to fwnmi_release_errinfo() in real mode causes kernel
		 * to panic. Hence we will call it as soon as we go पूर्णांकo
		 * भव mode.
		 */
		disposition = mce_handle_error(regs, errp);

		fwnmi_release_errinfo();

		अगर (disposition == RTAS_DISP_FULLY_RECOVERED)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण
