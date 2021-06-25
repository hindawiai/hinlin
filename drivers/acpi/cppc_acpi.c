<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CPPC (Collaborative Processor Perक्रमmance Control) methods used by CPUfreq drivers.
 *
 * (C) Copyright 2014, 2015 Linaro Ltd.
 * Author: Ashwin Chaugule <ashwin.chaugule@linaro.org>
 *
 * CPPC describes a few methods क्रम controlling CPU perक्रमmance using
 * inक्रमmation from a per CPU table called CPC. This table is described in
 * the ACPI v5.0+ specअगरication. The table consists of a list of
 * रेजिस्टरs which may be memory mapped or hardware रेजिस्टरs and also may
 * include some अटल पूर्णांकeger values.
 *
 * CPU perक्रमmance is on an असलtract continuous scale as against a discretized
 * P-state scale which is tied to CPU frequency only. In brief, the basic
 * operation involves:
 *
 * - OS makes a CPU perक्रमmance request. (Can provide min and max bounds)
 *
 * - Platक्रमm (such as BMC) is मुक्त to optimize request within requested bounds
 *   depending on घातer/thermal budमाला_लो etc.
 *
 * - Platक्रमm conveys its decision back to OS
 *
 * The communication between OS and platक्रमm occurs through another medium
 * called (PCC) Platक्रमm Communication Channel. This is a generic mailbox like
 * mechanism which includes करोorbell semantics to indicate रेजिस्टर updates.
 * See drivers/mailbox/pcc.c क्रम details on PCC.
 *
 * Finer details about the PCC and CPPC spec are available in the ACPI v5.1 and
 * above specअगरications.
 */

#घोषणा pr_fmt(fmt)	"ACPI CPPC: " fmt

#समावेश <linux/delay.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/rwsem.h>
#समावेश <linux/रुको.h>
#समावेश <linux/topology.h>

#समावेश <acpi/cppc_acpi.h>

काष्ठा cppc_pcc_data अणु
	काष्ठा mbox_chan *pcc_channel;
	व्योम __iomem *pcc_comm_addr;
	bool pcc_channel_acquired;
	अचिन्हित पूर्णांक deadline_us;
	अचिन्हित पूर्णांक pcc_mpar, pcc_mrtt, pcc_nominal;

	bool pending_pcc_ग_लिखो_cmd;	/* Any pending/batched PCC ग_लिखो cmds? */
	bool platक्रमm_owns_pcc;		/* Ownership of PCC subspace */
	अचिन्हित पूर्णांक pcc_ग_लिखो_cnt;	/* Running count of PCC ग_लिखो commands */

	/*
	 * Lock to provide controlled access to the PCC channel.
	 *
	 * For perक्रमmance critical useहालs(currently cppc_set_perf)
	 *	We need to take पढ़ो_lock and check अगर channel beदीर्घs to OSPM
	 * beक्रमe पढ़ोing or writing to PCC subspace
	 *	We need to take ग_लिखो_lock beक्रमe transferring the channel
	 * ownership to the platक्रमm via a Doorbell
	 *	This allows us to batch a number of CPPC requests अगर they happen
	 * to originate in about the same समय
	 *
	 * For non-perक्रमmance critical useहालs(init)
	 *	Take ग_लिखो_lock क्रम all purposes which gives exclusive access
	 */
	काष्ठा rw_semaphore pcc_lock;

	/* Wait queue क्रम CPUs whose requests were batched */
	रुको_queue_head_t pcc_ग_लिखो_रुको_q;
	kसमय_प्रकार last_cmd_cmpl_समय;
	kसमय_प्रकार last_mpar_reset;
	पूर्णांक mpar_count;
	पूर्णांक refcount;
पूर्ण;

/* Array to represent the PCC channel per subspace ID */
अटल काष्ठा cppc_pcc_data *pcc_data[MAX_PCC_SUBSPACES];
/* The cpu_pcc_subspace_idx contains per CPU subspace ID */
अटल DEFINE_PER_CPU(पूर्णांक, cpu_pcc_subspace_idx);

/*
 * The cpc_desc काष्ठाure contains the ACPI रेजिस्टर details
 * as described in the per CPU _CPC tables. The details
 * include the type of रेजिस्टर (e.g. PCC, System IO, FFH etc.)
 * and destination addresses which lets us READ/WRITE CPU perक्रमmance
 * inक्रमmation using the appropriate I/O methods.
 */
अटल DEFINE_PER_CPU(काष्ठा cpc_desc *, cpc_desc_ptr);

/* pcc mapped address + header size + offset within PCC subspace */
#घोषणा GET_PCC_VADDR(offs, pcc_ss_id) (pcc_data[pcc_ss_id]->pcc_comm_addr + \
						0x8 + (offs))

/* Check अगर a CPC रेजिस्टर is in PCC */
#घोषणा CPC_IN_PCC(cpc) ((cpc)->type == ACPI_TYPE_BUFFER &&		\
				(cpc)->cpc_entry.reg.space_id ==	\
				ACPI_ADR_SPACE_PLATFORM_COMM)

/* Evaluates to True अगर reg is a शून्य रेजिस्टर descriptor */
#घोषणा IS_शून्य_REG(reg) ((reg)->space_id ==  ACPI_ADR_SPACE_SYSTEM_MEMORY && \
				(reg)->address == 0 &&			\
				(reg)->bit_width == 0 &&		\
				(reg)->bit_offset == 0 &&		\
				(reg)->access_width == 0)

/* Evaluates to True अगर an optional cpc field is supported */
#घोषणा CPC_SUPPORTED(cpc) ((cpc)->type == ACPI_TYPE_INTEGER ?		\
				!!(cpc)->cpc_entry.पूर्णांक_value :		\
				!IS_शून्य_REG(&(cpc)->cpc_entry.reg))
/*
 * Arbitrary Retries in हाल the remote processor is slow to respond
 * to PCC commands. Keeping it high enough to cover emulators where
 * the processors run painfully slow.
 */
#घोषणा NUM_RETRIES 500ULL

#घोषणा define_one_cppc_ro(_name)		\
अटल काष्ठा kobj_attribute _name =		\
__ATTR(_name, 0444, show_##_name, शून्य)

#घोषणा to_cpc_desc(a) container_of(a, काष्ठा cpc_desc, kobj)

#घोषणा show_cppc_data(access_fn, काष्ठा_name, member_name)		\
	अटल sमाप_प्रकार show_##member_name(काष्ठा kobject *kobj,		\
				काष्ठा kobj_attribute *attr, अक्षर *buf)	\
	अणु								\
		काष्ठा cpc_desc *cpc_ptr = to_cpc_desc(kobj);		\
		काष्ठा काष्ठा_name st_name = अणु0पूर्ण;			\
		पूर्णांक ret;						\
									\
		ret = access_fn(cpc_ptr->cpu_id, &st_name);		\
		अगर (ret)						\
			वापस ret;					\
									\
		वापस scnम_लिखो(buf, PAGE_SIZE, "%llu\n",		\
				(u64)st_name.member_name);		\
	पूर्ण								\
	define_one_cppc_ro(member_name)

show_cppc_data(cppc_get_perf_caps, cppc_perf_caps, highest_perf);
show_cppc_data(cppc_get_perf_caps, cppc_perf_caps, lowest_perf);
show_cppc_data(cppc_get_perf_caps, cppc_perf_caps, nominal_perf);
show_cppc_data(cppc_get_perf_caps, cppc_perf_caps, lowest_nonlinear_perf);
show_cppc_data(cppc_get_perf_caps, cppc_perf_caps, lowest_freq);
show_cppc_data(cppc_get_perf_caps, cppc_perf_caps, nominal_freq);

show_cppc_data(cppc_get_perf_ctrs, cppc_perf_fb_ctrs, reference_perf);
show_cppc_data(cppc_get_perf_ctrs, cppc_perf_fb_ctrs, wraparound_समय);

अटल sमाप_प्रकार show_feedback_ctrs(काष्ठा kobject *kobj,
		काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cpc_desc *cpc_ptr = to_cpc_desc(kobj);
	काष्ठा cppc_perf_fb_ctrs fb_ctrs = अणु0पूर्ण;
	पूर्णांक ret;

	ret = cppc_get_perf_ctrs(cpc_ptr->cpu_id, &fb_ctrs);
	अगर (ret)
		वापस ret;

	वापस scnम_लिखो(buf, PAGE_SIZE, "ref:%llu del:%llu\n",
			fb_ctrs.reference, fb_ctrs.delivered);
पूर्ण
define_one_cppc_ro(feedback_ctrs);

अटल काष्ठा attribute *cppc_attrs[] = अणु
	&feedback_ctrs.attr,
	&reference_perf.attr,
	&wraparound_समय.attr,
	&highest_perf.attr,
	&lowest_perf.attr,
	&lowest_nonlinear_perf.attr,
	&nominal_perf.attr,
	&nominal_freq.attr,
	&lowest_freq.attr,
	शून्य
पूर्ण;

अटल काष्ठा kobj_type cppc_ktype = अणु
	.sysfs_ops = &kobj_sysfs_ops,
	.शेष_attrs = cppc_attrs,
पूर्ण;

अटल पूर्णांक check_pcc_chan(पूर्णांक pcc_ss_id, bool chk_err_bit)
अणु
	पूर्णांक ret, status;
	काष्ठा cppc_pcc_data *pcc_ss_data = pcc_data[pcc_ss_id];
	काष्ठा acpi_pcct_shared_memory __iomem *generic_comm_base =
		pcc_ss_data->pcc_comm_addr;

	अगर (!pcc_ss_data->platक्रमm_owns_pcc)
		वापस 0;

	/*
	 * Poll PCC status रेजिस्टर every 3us(delay_us) क्रम maximum of
	 * deadline_us(समयout_us) until PCC command complete bit is set(cond)
	 */
	ret = पढ़ोw_relaxed_poll_समयout(&generic_comm_base->status, status,
					status & PCC_CMD_COMPLETE_MASK, 3,
					pcc_ss_data->deadline_us);

	अगर (likely(!ret)) अणु
		pcc_ss_data->platक्रमm_owns_pcc = false;
		अगर (chk_err_bit && (status & PCC_ERROR_MASK))
			ret = -EIO;
	पूर्ण

	अगर (unlikely(ret))
		pr_err("PCC check channel failed for ss: %d. ret=%d\n",
		       pcc_ss_id, ret);

	वापस ret;
पूर्ण

/*
 * This function transfers the ownership of the PCC to the platक्रमm
 * So it must be called जबतक holding ग_लिखो_lock(pcc_lock)
 */
अटल पूर्णांक send_pcc_cmd(पूर्णांक pcc_ss_id, u16 cmd)
अणु
	पूर्णांक ret = -EIO, i;
	काष्ठा cppc_pcc_data *pcc_ss_data = pcc_data[pcc_ss_id];
	काष्ठा acpi_pcct_shared_memory __iomem *generic_comm_base =
		pcc_ss_data->pcc_comm_addr;
	अचिन्हित पूर्णांक समय_delta;

	/*
	 * For CMD_WRITE we know क्रम a fact the caller should have checked
	 * the channel beक्रमe writing to PCC space
	 */
	अगर (cmd == CMD_READ) अणु
		/*
		 * If there are pending cpc_ग_लिखोs, then we stole the channel
		 * beक्रमe ग_लिखो completion, so first send a WRITE command to
		 * platक्रमm
		 */
		अगर (pcc_ss_data->pending_pcc_ग_लिखो_cmd)
			send_pcc_cmd(pcc_ss_id, CMD_WRITE);

		ret = check_pcc_chan(pcc_ss_id, false);
		अगर (ret)
			जाओ end;
	पूर्ण अन्यथा /* CMD_WRITE */
		pcc_ss_data->pending_pcc_ग_लिखो_cmd = FALSE;

	/*
	 * Handle the Minimum Request Turnaround Time(MRTT)
	 * "The minimum amount of समय that OSPM must रुको after the completion
	 * of a command beक्रमe issuing the next command, in microseconds"
	 */
	अगर (pcc_ss_data->pcc_mrtt) अणु
		समय_delta = kसमय_us_delta(kसमय_get(),
					    pcc_ss_data->last_cmd_cmpl_समय);
		अगर (pcc_ss_data->pcc_mrtt > समय_delta)
			udelay(pcc_ss_data->pcc_mrtt - समय_delta);
	पूर्ण

	/*
	 * Handle the non-zero Maximum Periodic Access Rate(MPAR)
	 * "The maximum number of periodic requests that the subspace channel can
	 * support, reported in commands per minute. 0 indicates no limitation."
	 *
	 * This parameter should be ideally zero or large enough so that it can
	 * handle maximum number of requests that all the cores in the प्रणाली can
	 * collectively generate. If it is not, we will follow the spec and just
	 * not send the request to the platक्रमm after hitting the MPAR limit in
	 * any 60s winकरोw
	 */
	अगर (pcc_ss_data->pcc_mpar) अणु
		अगर (pcc_ss_data->mpar_count == 0) अणु
			समय_delta = kसमय_ms_delta(kसमय_get(),
						    pcc_ss_data->last_mpar_reset);
			अगर ((समय_delta < 60 * MSEC_PER_SEC) && pcc_ss_data->last_mpar_reset) अणु
				pr_debug("PCC cmd for subspace %d not sent due to MPAR limit",
					 pcc_ss_id);
				ret = -EIO;
				जाओ end;
			पूर्ण
			pcc_ss_data->last_mpar_reset = kसमय_get();
			pcc_ss_data->mpar_count = pcc_ss_data->pcc_mpar;
		पूर्ण
		pcc_ss_data->mpar_count--;
	पूर्ण

	/* Write to the shared comm region. */
	ग_लिखोw_relaxed(cmd, &generic_comm_base->command);

	/* Flip CMD COMPLETE bit */
	ग_लिखोw_relaxed(0, &generic_comm_base->status);

	pcc_ss_data->platक्रमm_owns_pcc = true;

	/* Ring करोorbell */
	ret = mbox_send_message(pcc_ss_data->pcc_channel, &cmd);
	अगर (ret < 0) अणु
		pr_err("Err sending PCC mbox message. ss: %d cmd:%d, ret:%d\n",
		       pcc_ss_id, cmd, ret);
		जाओ end;
	पूर्ण

	/* रुको क्रम completion and check क्रम PCC errro bit */
	ret = check_pcc_chan(pcc_ss_id, true);

	अगर (pcc_ss_data->pcc_mrtt)
		pcc_ss_data->last_cmd_cmpl_समय = kसमय_get();

	अगर (pcc_ss_data->pcc_channel->mbox->txकरोne_irq)
		mbox_chan_txकरोne(pcc_ss_data->pcc_channel, ret);
	अन्यथा
		mbox_client_txकरोne(pcc_ss_data->pcc_channel, ret);

end:
	अगर (cmd == CMD_WRITE) अणु
		अगर (unlikely(ret)) अणु
			क्रम_each_possible_cpu(i) अणु
				काष्ठा cpc_desc *desc = per_cpu(cpc_desc_ptr, i);

				अगर (!desc)
					जारी;

				अगर (desc->ग_लिखो_cmd_id == pcc_ss_data->pcc_ग_लिखो_cnt)
					desc->ग_लिखो_cmd_status = ret;
			पूर्ण
		पूर्ण
		pcc_ss_data->pcc_ग_लिखो_cnt++;
		wake_up_all(&pcc_ss_data->pcc_ग_लिखो_रुको_q);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम cppc_chan_tx_करोne(काष्ठा mbox_client *cl, व्योम *msg, पूर्णांक ret)
अणु
	अगर (ret < 0)
		pr_debug("TX did not complete: CMD sent:%x, ret:%d\n",
				*(u16 *)msg, ret);
	अन्यथा
		pr_debug("TX completed. CMD sent:%x, ret:%d\n",
				*(u16 *)msg, ret);
पूर्ण

अटल काष्ठा mbox_client cppc_mbox_cl = अणु
	.tx_करोne = cppc_chan_tx_करोne,
	.knows_txकरोne = true,
पूर्ण;

अटल पूर्णांक acpi_get_psd(काष्ठा cpc_desc *cpc_ptr, acpi_handle handle)
अणु
	पूर्णांक result = -EFAULT;
	acpi_status status = AE_OK;
	काष्ठा acpi_buffer buffer = अणुACPI_ALLOCATE_BUFFER, शून्यपूर्ण;
	काष्ठा acpi_buffer क्रमmat = अणुमाप("NNNNN"), "NNNNN"पूर्ण;
	काष्ठा acpi_buffer state = अणु0, शून्यपूर्ण;
	जोड़ acpi_object  *psd = शून्य;
	काष्ठा acpi_psd_package *pकरोमुख्य;

	status = acpi_evaluate_object_typed(handle, "_PSD", शून्य,
					    &buffer, ACPI_TYPE_PACKAGE);
	अगर (status == AE_NOT_FOUND)	/* _PSD is optional */
		वापस 0;
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	psd = buffer.poपूर्णांकer;
	अगर (!psd || psd->package.count != 1) अणु
		pr_debug("Invalid _PSD data\n");
		जाओ end;
	पूर्ण

	pकरोमुख्य = &(cpc_ptr->करोमुख्य_info);

	state.length = माप(काष्ठा acpi_psd_package);
	state.poपूर्णांकer = pकरोमुख्य;

	status = acpi_extract_package(&(psd->package.elements[0]),
		&क्रमmat, &state);
	अगर (ACPI_FAILURE(status)) अणु
		pr_debug("Invalid _PSD data for CPU:%d\n", cpc_ptr->cpu_id);
		जाओ end;
	पूर्ण

	अगर (pकरोमुख्य->num_entries != ACPI_PSD_REV0_ENTRIES) अणु
		pr_debug("Unknown _PSD:num_entries for CPU:%d\n", cpc_ptr->cpu_id);
		जाओ end;
	पूर्ण

	अगर (pकरोमुख्य->revision != ACPI_PSD_REV0_REVISION) अणु
		pr_debug("Unknown _PSD:revision for CPU: %d\n", cpc_ptr->cpu_id);
		जाओ end;
	पूर्ण

	अगर (pकरोमुख्य->coord_type != DOMAIN_COORD_TYPE_SW_ALL &&
	    pकरोमुख्य->coord_type != DOMAIN_COORD_TYPE_SW_ANY &&
	    pकरोमुख्य->coord_type != DOMAIN_COORD_TYPE_HW_ALL) अणु
		pr_debug("Invalid _PSD:coord_type for CPU:%d\n", cpc_ptr->cpu_id);
		जाओ end;
	पूर्ण

	result = 0;
end:
	kमुक्त(buffer.poपूर्णांकer);
	वापस result;
पूर्ण

bool acpi_cpc_valid(व्योम)
अणु
	काष्ठा cpc_desc *cpc_ptr;
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		cpc_ptr = per_cpu(cpc_desc_ptr, cpu);
		अगर (!cpc_ptr)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_cpc_valid);

/**
 * acpi_get_psd_map - Map the CPUs in the freq करोमुख्य of a given cpu
 * @cpu: Find all CPUs that share a करोमुख्य with cpu.
 * @cpu_data: Poपूर्णांकer to CPU specअगरic CPPC data including PSD info.
 *
 *	Return: 0 क्रम success or negative value क्रम err.
 */
पूर्णांक acpi_get_psd_map(अचिन्हित पूर्णांक cpu, काष्ठा cppc_cpudata *cpu_data)
अणु
	काष्ठा cpc_desc *cpc_ptr, *match_cpc_ptr;
	काष्ठा acpi_psd_package *match_pकरोमुख्य;
	काष्ठा acpi_psd_package *pकरोमुख्य;
	पूर्णांक count_target, i;

	/*
	 * Now that we have _PSD data from all CPUs, let's setup P-state
	 * करोमुख्य info.
	 */
	cpc_ptr = per_cpu(cpc_desc_ptr, cpu);
	अगर (!cpc_ptr)
		वापस -EFAULT;

	pकरोमुख्य = &(cpc_ptr->करोमुख्य_info);
	cpumask_set_cpu(cpu, cpu_data->shared_cpu_map);
	अगर (pकरोमुख्य->num_processors <= 1)
		वापस 0;

	/* Validate the Doमुख्य info */
	count_target = pकरोमुख्य->num_processors;
	अगर (pकरोमुख्य->coord_type == DOMAIN_COORD_TYPE_SW_ALL)
		cpu_data->shared_type = CPUFREQ_SHARED_TYPE_ALL;
	अन्यथा अगर (pकरोमुख्य->coord_type == DOMAIN_COORD_TYPE_HW_ALL)
		cpu_data->shared_type = CPUFREQ_SHARED_TYPE_HW;
	अन्यथा अगर (pकरोमुख्य->coord_type == DOMAIN_COORD_TYPE_SW_ANY)
		cpu_data->shared_type = CPUFREQ_SHARED_TYPE_ANY;

	क्रम_each_possible_cpu(i) अणु
		अगर (i == cpu)
			जारी;

		match_cpc_ptr = per_cpu(cpc_desc_ptr, i);
		अगर (!match_cpc_ptr)
			जाओ err_fault;

		match_pकरोमुख्य = &(match_cpc_ptr->करोमुख्य_info);
		अगर (match_pकरोमुख्य->करोमुख्य != pकरोमुख्य->करोमुख्य)
			जारी;

		/* Here i and cpu are in the same करोमुख्य */
		अगर (match_pकरोमुख्य->num_processors != count_target)
			जाओ err_fault;

		अगर (pकरोमुख्य->coord_type != match_pकरोमुख्य->coord_type)
			जाओ err_fault;

		cpumask_set_cpu(i, cpu_data->shared_cpu_map);
	पूर्ण

	वापस 0;

err_fault:
	/* Assume no coordination on any error parsing करोमुख्य info */
	cpumask_clear(cpu_data->shared_cpu_map);
	cpumask_set_cpu(cpu, cpu_data->shared_cpu_map);
	cpu_data->shared_type = CPUFREQ_SHARED_TYPE_NONE;

	वापस -EFAULT;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_get_psd_map);

अटल पूर्णांक रेजिस्टर_pcc_channel(पूर्णांक pcc_ss_idx)
अणु
	काष्ठा acpi_pcct_hw_reduced *cppc_ss;
	u64 usecs_lat;

	अगर (pcc_ss_idx >= 0) अणु
		pcc_data[pcc_ss_idx]->pcc_channel =
			pcc_mbox_request_channel(&cppc_mbox_cl,	pcc_ss_idx);

		अगर (IS_ERR(pcc_data[pcc_ss_idx]->pcc_channel)) अणु
			pr_err("Failed to find PCC channel for subspace %d\n",
			       pcc_ss_idx);
			वापस -ENODEV;
		पूर्ण

		/*
		 * The PCC mailbox controller driver should
		 * have parsed the PCCT (global table of all
		 * PCC channels) and stored poपूर्णांकers to the
		 * subspace communication region in con_priv.
		 */
		cppc_ss = (pcc_data[pcc_ss_idx]->pcc_channel)->con_priv;

		अगर (!cppc_ss) अणु
			pr_err("No PCC subspace found for %d CPPC\n",
			       pcc_ss_idx);
			वापस -ENODEV;
		पूर्ण

		/*
		 * cppc_ss->latency is just a Nominal value. In reality
		 * the remote processor could be much slower to reply.
		 * So add an arbitrary amount of रुको on top of Nominal.
		 */
		usecs_lat = NUM_RETRIES * cppc_ss->latency;
		pcc_data[pcc_ss_idx]->deadline_us = usecs_lat;
		pcc_data[pcc_ss_idx]->pcc_mrtt = cppc_ss->min_turnaround_समय;
		pcc_data[pcc_ss_idx]->pcc_mpar = cppc_ss->max_access_rate;
		pcc_data[pcc_ss_idx]->pcc_nominal = cppc_ss->latency;

		pcc_data[pcc_ss_idx]->pcc_comm_addr =
			acpi_os_ioremap(cppc_ss->base_address, cppc_ss->length);
		अगर (!pcc_data[pcc_ss_idx]->pcc_comm_addr) अणु
			pr_err("Failed to ioremap PCC comm region mem for %d\n",
			       pcc_ss_idx);
			वापस -ENOMEM;
		पूर्ण

		/* Set flag so that we करोn't come here क्रम each CPU. */
		pcc_data[pcc_ss_idx]->pcc_channel_acquired = true;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * cpc_ffh_supported() - check अगर FFH पढ़ोing supported
 *
 * Check अगर the architecture has support क्रम functional fixed hardware
 * पढ़ो/ग_लिखो capability.
 *
 * Return: true क्रम supported, false क्रम not supported
 */
bool __weak cpc_ffh_supported(व्योम)
अणु
	वापस false;
पूर्ण

/**
 * pcc_data_alloc() - Allocate the pcc_data memory क्रम pcc subspace
 *
 * Check and allocate the cppc_pcc_data memory.
 * In some processor configurations it is possible that same subspace
 * is shared between multiple CPUs. This is seen especially in CPUs
 * with hardware multi-thपढ़ोing support.
 *
 * Return: 0 क्रम success, त्रुटि_सं क्रम failure
 */
अटल पूर्णांक pcc_data_alloc(पूर्णांक pcc_ss_id)
अणु
	अगर (pcc_ss_id < 0 || pcc_ss_id >= MAX_PCC_SUBSPACES)
		वापस -EINVAL;

	अगर (pcc_data[pcc_ss_id]) अणु
		pcc_data[pcc_ss_id]->refcount++;
	पूर्ण अन्यथा अणु
		pcc_data[pcc_ss_id] = kzalloc(माप(काष्ठा cppc_pcc_data),
					      GFP_KERNEL);
		अगर (!pcc_data[pcc_ss_id])
			वापस -ENOMEM;
		pcc_data[pcc_ss_id]->refcount++;
	पूर्ण

	वापस 0;
पूर्ण

/* Check अगर CPPC revision + num_ent combination is supported */
अटल bool is_cppc_supported(पूर्णांक revision, पूर्णांक num_ent)
अणु
	पूर्णांक expected_num_ent;

	चयन (revision) अणु
	हाल CPPC_V2_REV:
		expected_num_ent = CPPC_V2_NUM_ENT;
		अवरोध;
	हाल CPPC_V3_REV:
		expected_num_ent = CPPC_V3_NUM_ENT;
		अवरोध;
	शेष:
		pr_debug("Firmware exports unsupported CPPC revision: %d\n",
			revision);
		वापस false;
	पूर्ण

	अगर (expected_num_ent != num_ent) अणु
		pr_debug("Firmware exports %d entries. Expected: %d for CPPC rev:%d\n",
			num_ent, expected_num_ent, revision);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/*
 * An example CPC table looks like the following.
 *
 *	Name(_CPC, Package()
 *			अणु
 *			17,
 *			NumEntries
 *			1,
 *			// Revision
 *			ResourceTemplate()अणुRegister(PCC, 32, 0, 0x120, 2)पूर्ण,
 *			// Highest Perक्रमmance
 *			ResourceTemplate()अणुRegister(PCC, 32, 0, 0x124, 2)पूर्ण,
 *			// Nominal Perक्रमmance
 *			ResourceTemplate()अणुRegister(PCC, 32, 0, 0x128, 2)पूर्ण,
 *			// Lowest Nonlinear Perक्रमmance
 *			ResourceTemplate()अणुRegister(PCC, 32, 0, 0x12C, 2)पूर्ण,
 *			// Lowest Perक्रमmance
 *			ResourceTemplate()अणुRegister(PCC, 32, 0, 0x130, 2)पूर्ण,
 *			// Guaranteed Perक्रमmance Register
 *			ResourceTemplate()अणुRegister(PCC, 32, 0, 0x110, 2)पूर्ण,
 *			// Desired Perक्रमmance Register
 *			ResourceTemplate()अणुRegister(SystemMemory, 0, 0, 0, 0)पूर्ण,
 *			..
 *			..
 *			..
 *
 *		पूर्ण
 * Each Register() encodes how to access that specअगरic रेजिस्टर.
 * e.g. a sample PCC entry has the following encoding:
 *
 *	Register (
 *		PCC,
 *		AddressSpaceKeyword
 *		8,
 *		//RegisterBitWidth
 *		8,
 *		//RegisterBitOffset
 *		0x30,
 *		//RegisterAddress
 *		9
 *		//AccessSize (subspace ID)
 *		0
 *		)
 *	पूर्ण
 */

#अगर_अघोषित init_freq_invariance_cppc
अटल अंतरभूत व्योम init_freq_invariance_cppc(व्योम) अणु पूर्ण
#पूर्ण_अगर

/**
 * acpi_cppc_processor_probe - Search क्रम per CPU _CPC objects.
 * @pr: Ptr to acpi_processor containing this CPU's logical ID.
 *
 *	Return: 0 क्रम success or negative value क्रम err.
 */
पूर्णांक acpi_cppc_processor_probe(काष्ठा acpi_processor *pr)
अणु
	काष्ठा acpi_buffer output = अणुACPI_ALLOCATE_BUFFER, शून्यपूर्ण;
	जोड़ acpi_object *out_obj, *cpc_obj;
	काष्ठा cpc_desc *cpc_ptr;
	काष्ठा cpc_reg *gas_t;
	काष्ठा device *cpu_dev;
	acpi_handle handle = pr->handle;
	अचिन्हित पूर्णांक num_ent, i, cpc_rev;
	पूर्णांक pcc_subspace_id = -1;
	acpi_status status;
	पूर्णांक ret = -EFAULT;

	/* Parse the ACPI _CPC table क्रम this CPU. */
	status = acpi_evaluate_object_typed(handle, "_CPC", शून्य, &output,
			ACPI_TYPE_PACKAGE);
	अगर (ACPI_FAILURE(status)) अणु
		ret = -ENODEV;
		जाओ out_buf_मुक्त;
	पूर्ण

	out_obj = (जोड़ acpi_object *) output.poपूर्णांकer;

	cpc_ptr = kzalloc(माप(काष्ठा cpc_desc), GFP_KERNEL);
	अगर (!cpc_ptr) अणु
		ret = -ENOMEM;
		जाओ out_buf_मुक्त;
	पूर्ण

	/* First entry is NumEntries. */
	cpc_obj = &out_obj->package.elements[0];
	अगर (cpc_obj->type == ACPI_TYPE_INTEGER)	अणु
		num_ent = cpc_obj->पूर्णांकeger.value;
	पूर्ण अन्यथा अणु
		pr_debug("Unexpected entry type(%d) for NumEntries\n",
				cpc_obj->type);
		जाओ out_मुक्त;
	पूर्ण
	cpc_ptr->num_entries = num_ent;

	/* Second entry should be revision. */
	cpc_obj = &out_obj->package.elements[1];
	अगर (cpc_obj->type == ACPI_TYPE_INTEGER)	अणु
		cpc_rev = cpc_obj->पूर्णांकeger.value;
	पूर्ण अन्यथा अणु
		pr_debug("Unexpected entry type(%d) for Revision\n",
				cpc_obj->type);
		जाओ out_मुक्त;
	पूर्ण
	cpc_ptr->version = cpc_rev;

	अगर (!is_cppc_supported(cpc_rev, num_ent))
		जाओ out_मुक्त;

	/* Iterate through reमुख्यing entries in _CPC */
	क्रम (i = 2; i < num_ent; i++) अणु
		cpc_obj = &out_obj->package.elements[i];

		अगर (cpc_obj->type == ACPI_TYPE_INTEGER)	अणु
			cpc_ptr->cpc_regs[i-2].type = ACPI_TYPE_INTEGER;
			cpc_ptr->cpc_regs[i-2].cpc_entry.पूर्णांक_value = cpc_obj->पूर्णांकeger.value;
		पूर्ण अन्यथा अगर (cpc_obj->type == ACPI_TYPE_BUFFER) अणु
			gas_t = (काष्ठा cpc_reg *)
				cpc_obj->buffer.poपूर्णांकer;

			/*
			 * The PCC Subspace index is encoded inside
			 * the CPC table entries. The same PCC index
			 * will be used क्रम all the PCC entries,
			 * so extract it only once.
			 */
			अगर (gas_t->space_id == ACPI_ADR_SPACE_PLATFORM_COMM) अणु
				अगर (pcc_subspace_id < 0) अणु
					pcc_subspace_id = gas_t->access_width;
					अगर (pcc_data_alloc(pcc_subspace_id))
						जाओ out_मुक्त;
				पूर्ण अन्यथा अगर (pcc_subspace_id != gas_t->access_width) अणु
					pr_debug("Mismatched PCC ids.\n");
					जाओ out_मुक्त;
				पूर्ण
			पूर्ण अन्यथा अगर (gas_t->space_id == ACPI_ADR_SPACE_SYSTEM_MEMORY) अणु
				अगर (gas_t->address) अणु
					व्योम __iomem *addr;

					addr = ioremap(gas_t->address, gas_t->bit_width/8);
					अगर (!addr)
						जाओ out_मुक्त;
					cpc_ptr->cpc_regs[i-2].sys_mem_vaddr = addr;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (gas_t->space_id != ACPI_ADR_SPACE_FIXED_HARDWARE || !cpc_ffh_supported()) अणु
					/* Support only PCC ,SYS MEM and FFH type regs */
					pr_debug("Unsupported register type: %d\n", gas_t->space_id);
					जाओ out_मुक्त;
				पूर्ण
			पूर्ण

			cpc_ptr->cpc_regs[i-2].type = ACPI_TYPE_BUFFER;
			स_नकल(&cpc_ptr->cpc_regs[i-2].cpc_entry.reg, gas_t, माप(*gas_t));
		पूर्ण अन्यथा अणु
			pr_debug("Err in entry:%d in CPC table of CPU:%d\n", i, pr->id);
			जाओ out_मुक्त;
		पूर्ण
	पूर्ण
	per_cpu(cpu_pcc_subspace_idx, pr->id) = pcc_subspace_id;

	/*
	 * Initialize the reमुख्यing cpc_regs as unsupported.
	 * Example: In हाल FW exposes CPPC v2, the below loop will initialize
	 * LOWEST_FREQ and NOMINAL_FREQ regs as unsupported
	 */
	क्रम (i = num_ent - 2; i < MAX_CPC_REG_ENT; i++) अणु
		cpc_ptr->cpc_regs[i].type = ACPI_TYPE_INTEGER;
		cpc_ptr->cpc_regs[i].cpc_entry.पूर्णांक_value = 0;
	पूर्ण


	/* Store CPU Logical ID */
	cpc_ptr->cpu_id = pr->id;

	/* Parse PSD data क्रम this CPU */
	ret = acpi_get_psd(cpc_ptr, handle);
	अगर (ret)
		जाओ out_मुक्त;

	/* Register PCC channel once क्रम all PCC subspace ID. */
	अगर (pcc_subspace_id >= 0 && !pcc_data[pcc_subspace_id]->pcc_channel_acquired) अणु
		ret = रेजिस्टर_pcc_channel(pcc_subspace_id);
		अगर (ret)
			जाओ out_मुक्त;

		init_rwsem(&pcc_data[pcc_subspace_id]->pcc_lock);
		init_रुकोqueue_head(&pcc_data[pcc_subspace_id]->pcc_ग_लिखो_रुको_q);
	पूर्ण

	/* Everything looks okay */
	pr_debug("Parsed CPC struct for CPU: %d\n", pr->id);

	/* Add per logical CPU nodes क्रम पढ़ोing its feedback counters. */
	cpu_dev = get_cpu_device(pr->id);
	अगर (!cpu_dev) अणु
		ret = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	/* Plug PSD data पूर्णांकo this CPU's CPC descriptor. */
	per_cpu(cpc_desc_ptr, pr->id) = cpc_ptr;

	ret = kobject_init_and_add(&cpc_ptr->kobj, &cppc_ktype, &cpu_dev->kobj,
			"acpi_cppc");
	अगर (ret) अणु
		per_cpu(cpc_desc_ptr, pr->id) = शून्य;
		kobject_put(&cpc_ptr->kobj);
		जाओ out_मुक्त;
	पूर्ण

	init_freq_invariance_cppc();

	kमुक्त(output.poपूर्णांकer);
	वापस 0;

out_मुक्त:
	/* Free all the mapped sys mem areas क्रम this CPU */
	क्रम (i = 2; i < cpc_ptr->num_entries; i++) अणु
		व्योम __iomem *addr = cpc_ptr->cpc_regs[i-2].sys_mem_vaddr;

		अगर (addr)
			iounmap(addr);
	पूर्ण
	kमुक्त(cpc_ptr);

out_buf_मुक्त:
	kमुक्त(output.poपूर्णांकer);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_cppc_processor_probe);

/**
 * acpi_cppc_processor_निकास - Cleanup CPC काष्ठाs.
 * @pr: Ptr to acpi_processor containing this CPU's logical ID.
 *
 * Return: Void
 */
व्योम acpi_cppc_processor_निकास(काष्ठा acpi_processor *pr)
अणु
	काष्ठा cpc_desc *cpc_ptr;
	अचिन्हित पूर्णांक i;
	व्योम __iomem *addr;
	पूर्णांक pcc_ss_id = per_cpu(cpu_pcc_subspace_idx, pr->id);

	अगर (pcc_ss_id >= 0 && pcc_data[pcc_ss_id]) अणु
		अगर (pcc_data[pcc_ss_id]->pcc_channel_acquired) अणु
			pcc_data[pcc_ss_id]->refcount--;
			अगर (!pcc_data[pcc_ss_id]->refcount) अणु
				pcc_mbox_मुक्त_channel(pcc_data[pcc_ss_id]->pcc_channel);
				kमुक्त(pcc_data[pcc_ss_id]);
				pcc_data[pcc_ss_id] = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण

	cpc_ptr = per_cpu(cpc_desc_ptr, pr->id);
	अगर (!cpc_ptr)
		वापस;

	/* Free all the mapped sys mem areas क्रम this CPU */
	क्रम (i = 2; i < cpc_ptr->num_entries; i++) अणु
		addr = cpc_ptr->cpc_regs[i-2].sys_mem_vaddr;
		अगर (addr)
			iounmap(addr);
	पूर्ण

	kobject_put(&cpc_ptr->kobj);
	kमुक्त(cpc_ptr);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_cppc_processor_निकास);

/**
 * cpc_पढ़ो_ffh() - Read FFH रेजिस्टर
 * @cpunum:	CPU number to पढ़ो
 * @reg:	cppc रेजिस्टर inक्रमmation
 * @val:	place holder क्रम वापस value
 *
 * Read bit_width bits from a specअगरied address and bit_offset
 *
 * Return: 0 क्रम success and error code
 */
पूर्णांक __weak cpc_पढ़ो_ffh(पूर्णांक cpunum, काष्ठा cpc_reg *reg, u64 *val)
अणु
	वापस -ENOTSUPP;
पूर्ण

/**
 * cpc_ग_लिखो_ffh() - Write FFH रेजिस्टर
 * @cpunum:	CPU number to ग_लिखो
 * @reg:	cppc रेजिस्टर inक्रमmation
 * @val:	value to ग_लिखो
 *
 * Write value of bit_width bits to a specअगरied address and bit_offset
 *
 * Return: 0 क्रम success and error code
 */
पूर्णांक __weak cpc_ग_लिखो_ffh(पूर्णांक cpunum, काष्ठा cpc_reg *reg, u64 val)
अणु
	वापस -ENOTSUPP;
पूर्ण

/*
 * Since cpc_पढ़ो and cpc_ग_लिखो are called जबतक holding pcc_lock, it should be
 * as fast as possible. We have alपढ़ोy mapped the PCC subspace during init, so
 * we can directly ग_लिखो to it.
 */

अटल पूर्णांक cpc_पढ़ो(पूर्णांक cpu, काष्ठा cpc_रेजिस्टर_resource *reg_res, u64 *val)
अणु
	पूर्णांक ret_val = 0;
	व्योम __iomem *vaddr = शून्य;
	पूर्णांक pcc_ss_id = per_cpu(cpu_pcc_subspace_idx, cpu);
	काष्ठा cpc_reg *reg = &reg_res->cpc_entry.reg;

	अगर (reg_res->type == ACPI_TYPE_INTEGER) अणु
		*val = reg_res->cpc_entry.पूर्णांक_value;
		वापस ret_val;
	पूर्ण

	*val = 0;
	अगर (reg->space_id == ACPI_ADR_SPACE_PLATFORM_COMM && pcc_ss_id >= 0)
		vaddr = GET_PCC_VADDR(reg->address, pcc_ss_id);
	अन्यथा अगर (reg->space_id == ACPI_ADR_SPACE_SYSTEM_MEMORY)
		vaddr = reg_res->sys_mem_vaddr;
	अन्यथा अगर (reg->space_id == ACPI_ADR_SPACE_FIXED_HARDWARE)
		वापस cpc_पढ़ो_ffh(cpu, reg, val);
	अन्यथा
		वापस acpi_os_पढ़ो_memory((acpi_physical_address)reg->address,
				val, reg->bit_width);

	चयन (reg->bit_width) अणु
	हाल 8:
		*val = पढ़ोb_relaxed(vaddr);
		अवरोध;
	हाल 16:
		*val = पढ़ोw_relaxed(vaddr);
		अवरोध;
	हाल 32:
		*val = पढ़ोl_relaxed(vaddr);
		अवरोध;
	हाल 64:
		*val = पढ़ोq_relaxed(vaddr);
		अवरोध;
	शेष:
		pr_debug("Error: Cannot read %u bit width from PCC for ss: %d\n",
			 reg->bit_width, pcc_ss_id);
		ret_val = -EFAULT;
	पूर्ण

	वापस ret_val;
पूर्ण

अटल पूर्णांक cpc_ग_लिखो(पूर्णांक cpu, काष्ठा cpc_रेजिस्टर_resource *reg_res, u64 val)
अणु
	पूर्णांक ret_val = 0;
	व्योम __iomem *vaddr = शून्य;
	पूर्णांक pcc_ss_id = per_cpu(cpu_pcc_subspace_idx, cpu);
	काष्ठा cpc_reg *reg = &reg_res->cpc_entry.reg;

	अगर (reg->space_id == ACPI_ADR_SPACE_PLATFORM_COMM && pcc_ss_id >= 0)
		vaddr = GET_PCC_VADDR(reg->address, pcc_ss_id);
	अन्यथा अगर (reg->space_id == ACPI_ADR_SPACE_SYSTEM_MEMORY)
		vaddr = reg_res->sys_mem_vaddr;
	अन्यथा अगर (reg->space_id == ACPI_ADR_SPACE_FIXED_HARDWARE)
		वापस cpc_ग_लिखो_ffh(cpu, reg, val);
	अन्यथा
		वापस acpi_os_ग_लिखो_memory((acpi_physical_address)reg->address,
				val, reg->bit_width);

	चयन (reg->bit_width) अणु
	हाल 8:
		ग_लिखोb_relaxed(val, vaddr);
		अवरोध;
	हाल 16:
		ग_लिखोw_relaxed(val, vaddr);
		अवरोध;
	हाल 32:
		ग_लिखोl_relaxed(val, vaddr);
		अवरोध;
	हाल 64:
		ग_लिखोq_relaxed(val, vaddr);
		अवरोध;
	शेष:
		pr_debug("Error: Cannot write %u bit width to PCC for ss: %d\n",
			 reg->bit_width, pcc_ss_id);
		ret_val = -EFAULT;
		अवरोध;
	पूर्ण

	वापस ret_val;
पूर्ण

/**
 * cppc_get_desired_perf - Get the value of desired perक्रमmance रेजिस्टर.
 * @cpunum: CPU from which to get desired perक्रमmance.
 * @desired_perf: address of a variable to store the वापसed desired perक्रमmance
 *
 * Return: 0 क्रम success, -EIO otherwise.
 */
पूर्णांक cppc_get_desired_perf(पूर्णांक cpunum, u64 *desired_perf)
अणु
	काष्ठा cpc_desc *cpc_desc = per_cpu(cpc_desc_ptr, cpunum);
	पूर्णांक pcc_ss_id = per_cpu(cpu_pcc_subspace_idx, cpunum);
	काष्ठा cpc_रेजिस्टर_resource *desired_reg;
	काष्ठा cppc_pcc_data *pcc_ss_data = शून्य;

	desired_reg = &cpc_desc->cpc_regs[DESIRED_PERF];

	अगर (CPC_IN_PCC(desired_reg)) अणु
		पूर्णांक ret = 0;

		अगर (pcc_ss_id < 0)
			वापस -EIO;

		pcc_ss_data = pcc_data[pcc_ss_id];

		करोwn_ग_लिखो(&pcc_ss_data->pcc_lock);

		अगर (send_pcc_cmd(pcc_ss_id, CMD_READ) >= 0)
			cpc_पढ़ो(cpunum, desired_reg, desired_perf);
		अन्यथा
			ret = -EIO;

		up_ग_लिखो(&pcc_ss_data->pcc_lock);

		वापस ret;
	पूर्ण

	cpc_पढ़ो(cpunum, desired_reg, desired_perf);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cppc_get_desired_perf);

/**
 * cppc_get_perf_caps - Get a CPU's perक्रमmance capabilities.
 * @cpunum: CPU from which to get capabilities info.
 * @perf_caps: ptr to cppc_perf_caps. See cppc_acpi.h
 *
 * Return: 0 क्रम success with perf_caps populated अन्यथा -ERRNO.
 */
पूर्णांक cppc_get_perf_caps(पूर्णांक cpunum, काष्ठा cppc_perf_caps *perf_caps)
अणु
	काष्ठा cpc_desc *cpc_desc = per_cpu(cpc_desc_ptr, cpunum);
	काष्ठा cpc_रेजिस्टर_resource *highest_reg, *lowest_reg,
		*lowest_non_linear_reg, *nominal_reg, *guaranteed_reg,
		*low_freq_reg = शून्य, *nom_freq_reg = शून्य;
	u64 high, low, guaranteed, nom, min_nonlinear, low_f = 0, nom_f = 0;
	पूर्णांक pcc_ss_id = per_cpu(cpu_pcc_subspace_idx, cpunum);
	काष्ठा cppc_pcc_data *pcc_ss_data = शून्य;
	पूर्णांक ret = 0, regs_in_pcc = 0;

	अगर (!cpc_desc) अणु
		pr_debug("No CPC descriptor for CPU:%d\n", cpunum);
		वापस -ENODEV;
	पूर्ण

	highest_reg = &cpc_desc->cpc_regs[HIGHEST_PERF];
	lowest_reg = &cpc_desc->cpc_regs[LOWEST_PERF];
	lowest_non_linear_reg = &cpc_desc->cpc_regs[LOW_NON_LINEAR_PERF];
	nominal_reg = &cpc_desc->cpc_regs[NOMINAL_PERF];
	low_freq_reg = &cpc_desc->cpc_regs[LOWEST_FREQ];
	nom_freq_reg = &cpc_desc->cpc_regs[NOMINAL_FREQ];
	guaranteed_reg = &cpc_desc->cpc_regs[GUARANTEED_PERF];

	/* Are any of the regs PCC ?*/
	अगर (CPC_IN_PCC(highest_reg) || CPC_IN_PCC(lowest_reg) ||
		CPC_IN_PCC(lowest_non_linear_reg) || CPC_IN_PCC(nominal_reg) ||
		CPC_IN_PCC(low_freq_reg) || CPC_IN_PCC(nom_freq_reg)) अणु
		अगर (pcc_ss_id < 0) अणु
			pr_debug("Invalid pcc_ss_id\n");
			वापस -ENODEV;
		पूर्ण
		pcc_ss_data = pcc_data[pcc_ss_id];
		regs_in_pcc = 1;
		करोwn_ग_लिखो(&pcc_ss_data->pcc_lock);
		/* Ring करोorbell once to update PCC subspace */
		अगर (send_pcc_cmd(pcc_ss_id, CMD_READ) < 0) अणु
			ret = -EIO;
			जाओ out_err;
		पूर्ण
	पूर्ण

	cpc_पढ़ो(cpunum, highest_reg, &high);
	perf_caps->highest_perf = high;

	cpc_पढ़ो(cpunum, lowest_reg, &low);
	perf_caps->lowest_perf = low;

	cpc_पढ़ो(cpunum, nominal_reg, &nom);
	perf_caps->nominal_perf = nom;

	अगर (guaranteed_reg->type != ACPI_TYPE_BUFFER  ||
	    IS_शून्य_REG(&guaranteed_reg->cpc_entry.reg)) अणु
		perf_caps->guaranteed_perf = 0;
	पूर्ण अन्यथा अणु
		cpc_पढ़ो(cpunum, guaranteed_reg, &guaranteed);
		perf_caps->guaranteed_perf = guaranteed;
	पूर्ण

	cpc_पढ़ो(cpunum, lowest_non_linear_reg, &min_nonlinear);
	perf_caps->lowest_nonlinear_perf = min_nonlinear;

	अगर (!high || !low || !nom || !min_nonlinear)
		ret = -EFAULT;

	/* Read optional lowest and nominal frequencies अगर present */
	अगर (CPC_SUPPORTED(low_freq_reg))
		cpc_पढ़ो(cpunum, low_freq_reg, &low_f);

	अगर (CPC_SUPPORTED(nom_freq_reg))
		cpc_पढ़ो(cpunum, nom_freq_reg, &nom_f);

	perf_caps->lowest_freq = low_f;
	perf_caps->nominal_freq = nom_f;


out_err:
	अगर (regs_in_pcc)
		up_ग_लिखो(&pcc_ss_data->pcc_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(cppc_get_perf_caps);

/**
 * cppc_get_perf_ctrs - Read a CPU's perक्रमmance feedback counters.
 * @cpunum: CPU from which to पढ़ो counters.
 * @perf_fb_ctrs: ptr to cppc_perf_fb_ctrs. See cppc_acpi.h
 *
 * Return: 0 क्रम success with perf_fb_ctrs populated अन्यथा -ERRNO.
 */
पूर्णांक cppc_get_perf_ctrs(पूर्णांक cpunum, काष्ठा cppc_perf_fb_ctrs *perf_fb_ctrs)
अणु
	काष्ठा cpc_desc *cpc_desc = per_cpu(cpc_desc_ptr, cpunum);
	काष्ठा cpc_रेजिस्टर_resource *delivered_reg, *reference_reg,
		*ref_perf_reg, *ctr_wrap_reg;
	पूर्णांक pcc_ss_id = per_cpu(cpu_pcc_subspace_idx, cpunum);
	काष्ठा cppc_pcc_data *pcc_ss_data = शून्य;
	u64 delivered, reference, ref_perf, ctr_wrap_समय;
	पूर्णांक ret = 0, regs_in_pcc = 0;

	अगर (!cpc_desc) अणु
		pr_debug("No CPC descriptor for CPU:%d\n", cpunum);
		वापस -ENODEV;
	पूर्ण

	delivered_reg = &cpc_desc->cpc_regs[DELIVERED_CTR];
	reference_reg = &cpc_desc->cpc_regs[REFERENCE_CTR];
	ref_perf_reg = &cpc_desc->cpc_regs[REFERENCE_PERF];
	ctr_wrap_reg = &cpc_desc->cpc_regs[CTR_WRAP_TIME];

	/*
	 * If reference perf रेजिस्टर is not supported then we should
	 * use the nominal perf value
	 */
	अगर (!CPC_SUPPORTED(ref_perf_reg))
		ref_perf_reg = &cpc_desc->cpc_regs[NOMINAL_PERF];

	/* Are any of the regs PCC ?*/
	अगर (CPC_IN_PCC(delivered_reg) || CPC_IN_PCC(reference_reg) ||
		CPC_IN_PCC(ctr_wrap_reg) || CPC_IN_PCC(ref_perf_reg)) अणु
		अगर (pcc_ss_id < 0) अणु
			pr_debug("Invalid pcc_ss_id\n");
			वापस -ENODEV;
		पूर्ण
		pcc_ss_data = pcc_data[pcc_ss_id];
		करोwn_ग_लिखो(&pcc_ss_data->pcc_lock);
		regs_in_pcc = 1;
		/* Ring करोorbell once to update PCC subspace */
		अगर (send_pcc_cmd(pcc_ss_id, CMD_READ) < 0) अणु
			ret = -EIO;
			जाओ out_err;
		पूर्ण
	पूर्ण

	cpc_पढ़ो(cpunum, delivered_reg, &delivered);
	cpc_पढ़ो(cpunum, reference_reg, &reference);
	cpc_पढ़ो(cpunum, ref_perf_reg, &ref_perf);

	/*
	 * Per spec, अगर ctr_wrap_समय optional रेजिस्टर is unsupported, then the
	 * perक्रमmance counters are assumed to never wrap during the lअगरeसमय of
	 * platक्रमm
	 */
	ctr_wrap_समय = (u64)(~((u64)0));
	अगर (CPC_SUPPORTED(ctr_wrap_reg))
		cpc_पढ़ो(cpunum, ctr_wrap_reg, &ctr_wrap_समय);

	अगर (!delivered || !reference ||	!ref_perf) अणु
		ret = -EFAULT;
		जाओ out_err;
	पूर्ण

	perf_fb_ctrs->delivered = delivered;
	perf_fb_ctrs->reference = reference;
	perf_fb_ctrs->reference_perf = ref_perf;
	perf_fb_ctrs->wraparound_समय = ctr_wrap_समय;
out_err:
	अगर (regs_in_pcc)
		up_ग_लिखो(&pcc_ss_data->pcc_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(cppc_get_perf_ctrs);

/**
 * cppc_set_perf - Set a CPU's perक्रमmance controls.
 * @cpu: CPU क्रम which to set perक्रमmance controls.
 * @perf_ctrls: ptr to cppc_perf_ctrls. See cppc_acpi.h
 *
 * Return: 0 क्रम success, -ERRNO otherwise.
 */
पूर्णांक cppc_set_perf(पूर्णांक cpu, काष्ठा cppc_perf_ctrls *perf_ctrls)
अणु
	काष्ठा cpc_desc *cpc_desc = per_cpu(cpc_desc_ptr, cpu);
	काष्ठा cpc_रेजिस्टर_resource *desired_reg;
	पूर्णांक pcc_ss_id = per_cpu(cpu_pcc_subspace_idx, cpu);
	काष्ठा cppc_pcc_data *pcc_ss_data = शून्य;
	पूर्णांक ret = 0;

	अगर (!cpc_desc) अणु
		pr_debug("No CPC descriptor for CPU:%d\n", cpu);
		वापस -ENODEV;
	पूर्ण

	desired_reg = &cpc_desc->cpc_regs[DESIRED_PERF];

	/*
	 * This is Phase-I where we want to ग_लिखो to CPC रेजिस्टरs
	 * -> We want all CPUs to be able to execute this phase in parallel
	 *
	 * Since पढ़ो_lock can be acquired by multiple CPUs simultaneously we
	 * achieve that goal here
	 */
	अगर (CPC_IN_PCC(desired_reg)) अणु
		अगर (pcc_ss_id < 0) अणु
			pr_debug("Invalid pcc_ss_id\n");
			वापस -ENODEV;
		पूर्ण
		pcc_ss_data = pcc_data[pcc_ss_id];
		करोwn_पढ़ो(&pcc_ss_data->pcc_lock); /* BEGIN Phase-I */
		अगर (pcc_ss_data->platक्रमm_owns_pcc) अणु
			ret = check_pcc_chan(pcc_ss_id, false);
			अगर (ret) अणु
				up_पढ़ो(&pcc_ss_data->pcc_lock);
				वापस ret;
			पूर्ण
		पूर्ण
		/*
		 * Update the pending_ग_लिखो to make sure a PCC CMD_READ will not
		 * arrive and steal the channel during the चयन to ग_लिखो lock
		 */
		pcc_ss_data->pending_pcc_ग_लिखो_cmd = true;
		cpc_desc->ग_लिखो_cmd_id = pcc_ss_data->pcc_ग_लिखो_cnt;
		cpc_desc->ग_लिखो_cmd_status = 0;
	पूर्ण

	/*
	 * Skip writing MIN/MAX until Linux knows how to come up with
	 * useful values.
	 */
	cpc_ग_लिखो(cpu, desired_reg, perf_ctrls->desired_perf);

	अगर (CPC_IN_PCC(desired_reg))
		up_पढ़ो(&pcc_ss_data->pcc_lock);	/* END Phase-I */
	/*
	 * This is Phase-II where we transfer the ownership of PCC to Platक्रमm
	 *
	 * Short Summary: Basically अगर we think of a group of cppc_set_perf
	 * requests that happened in लघु overlapping पूर्णांकerval. The last CPU to
	 * come out of Phase-I will enter Phase-II and ring the करोorbell.
	 *
	 * We have the following requirements क्रम Phase-II:
	 *     1. We want to execute Phase-II only when there are no CPUs
	 * currently executing in Phase-I
	 *     2. Once we start Phase-II we want to aव्योम all other CPUs from
	 * entering Phase-I.
	 *     3. We want only one CPU among all those who went through Phase-I
	 * to run phase-II
	 *
	 * If ग_लिखो_trylock fails to get the lock and करोesn't transfer the
	 * PCC ownership to the platक्रमm, then one of the following will be TRUE
	 *     1. There is at-least one CPU in Phase-I which will later execute
	 * ग_लिखो_trylock, so the CPUs in Phase-I will be responsible क्रम
	 * executing the Phase-II.
	 *     2. Some other CPU has beaten this CPU to successfully execute the
	 * ग_लिखो_trylock and has alपढ़ोy acquired the ग_लिखो_lock. We know क्रम a
	 * fact it (other CPU acquiring the ग_लिखो_lock) couldn't have happened
	 * beक्रमe this CPU's Phase-I as we held the पढ़ो_lock.
	 *     3. Some other CPU executing pcc CMD_READ has stolen the
	 * करोwn_ग_लिखो, in which हाल, send_pcc_cmd will check क्रम pending
	 * CMD_WRITE commands by checking the pending_pcc_ग_लिखो_cmd.
	 * So this CPU can be certain that its request will be delivered
	 *    So in all हालs, this CPU knows that its request will be delivered
	 * by another CPU and can वापस
	 *
	 * After getting the करोwn_ग_लिखो we still need to check क्रम
	 * pending_pcc_ग_लिखो_cmd to take care of the following scenario
	 *    The thपढ़ो running this code could be scheduled out between
	 * Phase-I and Phase-II. Beक्रमe it is scheduled back on, another CPU
	 * could have delivered the request to Platक्रमm by triggering the
	 * करोorbell and transferred the ownership of PCC to platक्रमm. So this
	 * aव्योमs triggering an unnecessary करोorbell and more importantly beक्रमe
	 * triggering the करोorbell it makes sure that the PCC channel ownership
	 * is still with OSPM.
	 *   pending_pcc_ग_लिखो_cmd can also be cleared by a dअगरferent CPU, अगर
	 * there was a pcc CMD_READ रुकोing on करोwn_ग_लिखो and it steals the lock
	 * beक्रमe the pcc CMD_WRITE is completed. send_pcc_cmd checks क्रम this
	 * हाल during a CMD_READ and अगर there are pending ग_लिखोs it delivers
	 * the ग_लिखो command beक्रमe servicing the पढ़ो command
	 */
	अगर (CPC_IN_PCC(desired_reg)) अणु
		अगर (करोwn_ग_लिखो_trylock(&pcc_ss_data->pcc_lock)) अणु/* BEGIN Phase-II */
			/* Update only अगर there are pending ग_लिखो commands */
			अगर (pcc_ss_data->pending_pcc_ग_लिखो_cmd)
				send_pcc_cmd(pcc_ss_id, CMD_WRITE);
			up_ग_लिखो(&pcc_ss_data->pcc_lock);	/* END Phase-II */
		पूर्ण अन्यथा
			/* Wait until pcc_ग_लिखो_cnt is updated by send_pcc_cmd */
			रुको_event(pcc_ss_data->pcc_ग_लिखो_रुको_q,
				   cpc_desc->ग_लिखो_cmd_id != pcc_ss_data->pcc_ग_लिखो_cnt);

		/* send_pcc_cmd updates the status in हाल of failure */
		ret = cpc_desc->ग_लिखो_cmd_status;
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(cppc_set_perf);

/**
 * cppc_get_transition_latency - वापसs frequency transition latency in ns
 *
 * ACPI CPPC करोes not explicitly specअगरy how a platक्रमm can specअगरy the
 * transition latency क्रम perक्रमmance change requests. The बंदst we have
 * is the timing inक्रमmation from the PCCT tables which provides the info
 * on the number and frequency of PCC commands the platक्रमm can handle.
 */
अचिन्हित पूर्णांक cppc_get_transition_latency(पूर्णांक cpu_num)
अणु
	/*
	 * Expected transition latency is based on the PCCT timing values
	 * Below are definition from ACPI spec:
	 * pcc_nominal- Expected latency to process a command, in microseconds
	 * pcc_mpar   - The maximum number of periodic requests that the subspace
	 *              channel can support, reported in commands per minute. 0
	 *              indicates no limitation.
	 * pcc_mrtt   - The minimum amount of समय that OSPM must रुको after the
	 *              completion of a command beक्रमe issuing the next command,
	 *              in microseconds.
	 */
	अचिन्हित पूर्णांक latency_ns = 0;
	काष्ठा cpc_desc *cpc_desc;
	काष्ठा cpc_रेजिस्टर_resource *desired_reg;
	पूर्णांक pcc_ss_id = per_cpu(cpu_pcc_subspace_idx, cpu_num);
	काष्ठा cppc_pcc_data *pcc_ss_data;

	cpc_desc = per_cpu(cpc_desc_ptr, cpu_num);
	अगर (!cpc_desc)
		वापस CPUFREQ_ETERNAL;

	desired_reg = &cpc_desc->cpc_regs[DESIRED_PERF];
	अगर (!CPC_IN_PCC(desired_reg))
		वापस CPUFREQ_ETERNAL;

	अगर (pcc_ss_id < 0)
		वापस CPUFREQ_ETERNAL;

	pcc_ss_data = pcc_data[pcc_ss_id];
	अगर (pcc_ss_data->pcc_mpar)
		latency_ns = 60 * (1000 * 1000 * 1000 / pcc_ss_data->pcc_mpar);

	latency_ns = max(latency_ns, pcc_ss_data->pcc_nominal * 1000);
	latency_ns = max(latency_ns, pcc_ss_data->pcc_mrtt * 1000);

	वापस latency_ns;
पूर्ण
EXPORT_SYMBOL_GPL(cppc_get_transition_latency);
