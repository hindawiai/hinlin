<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * processor_perflib.c - ACPI Processor P-States Library ($Revision: 71 $)
 *
 *  Copyright (C) 2001, 2002 Andy Grover <andrew.grover@पूर्णांकel.com>
 *  Copyright (C) 2001, 2002 Paul Diefenbaugh <paul.s.diefenbaugh@पूर्णांकel.com>
 *  Copyright (C) 2004       Dominik Broकरोwski <linux@broकरो.de>
 *  Copyright (C) 2004  Anil S Keshavamurthy <anil.s.keshavamurthy@पूर्णांकel.com>
 *  			- Added processor hotplug support
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>
#समावेश <acpi/processor.h>
#अगर_घोषित CONFIG_X86
#समावेश <यंत्र/cpufeature.h>
#पूर्ण_अगर

#घोषणा PREFIX "ACPI: "

#घोषणा ACPI_PROCESSOR_खाता_PERFORMANCE	"performance"

अटल DEFINE_MUTEX(perक्रमmance_mutex);

/*
 * _PPC support is implemented as a CPUfreq policy notअगरier:
 * This means each समय a CPUfreq driver रेजिस्टरed also with
 * the ACPI core is asked to change the speed policy, the maximum
 * value is adjusted so that it is within the platक्रमm limit.
 *
 * Also, when a new platक्रमm limit value is detected, the CPUfreq
 * policy is adjusted accordingly.
 */

/* ignore_ppc:
 * -1 -> cpufreq low level drivers not initialized -> _PSS, etc. not called yet
 *       ignore _PPC
 *  0 -> cpufreq low level drivers initialized -> consider _PPC values
 *  1 -> ignore _PPC totally -> क्रमced by user through boot param
 */
अटल पूर्णांक ignore_ppc = -1;
module_param(ignore_ppc, पूर्णांक, 0644);
MODULE_PARM_DESC(ignore_ppc, "If the frequency of your machine gets wrongly" \
		 "limited by BIOS, this should help");

अटल bool acpi_processor_ppc_in_use;

अटल पूर्णांक acpi_processor_get_platक्रमm_limit(काष्ठा acpi_processor *pr)
अणु
	acpi_status status = 0;
	अचिन्हित दीर्घ दीर्घ ppc = 0;
	पूर्णांक ret;

	अगर (!pr)
		वापस -EINVAL;

	/*
	 * _PPC indicates the maximum state currently supported by the platक्रमm
	 * (e.g. 0 = states 0..n; 1 = states 1..n; etc.
	 */
	status = acpi_evaluate_पूर्णांकeger(pr->handle, "_PPC", शून्य, &ppc);
	अगर (status != AE_NOT_FOUND) अणु
		acpi_processor_ppc_in_use = true;

		अगर (ACPI_FAILURE(status)) अणु
			acpi_evaluation_failure_warn(pr->handle, "_PPC", status);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	pr_debug("CPU %d: _PPC is %d - frequency %s limited\n", pr->id,
		       (पूर्णांक)ppc, ppc ? "" : "not");

	pr->perक्रमmance_platक्रमm_limit = (पूर्णांक)ppc;

	अगर (ppc >= pr->perक्रमmance->state_count ||
	    unlikely(!freq_qos_request_active(&pr->perflib_req)))
		वापस 0;

	ret = freq_qos_update_request(&pr->perflib_req,
			pr->perक्रमmance->states[ppc].core_frequency * 1000);
	अगर (ret < 0) अणु
		pr_warn("Failed to update perflib freq constraint: CPU%d (%d)\n",
			pr->id, ret);
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा ACPI_PROCESSOR_NOTIFY_PERFORMANCE	0x80
/*
 * acpi_processor_ppc_ost: Notअगरy firmware the _PPC evaluation status
 * @handle: ACPI processor handle
 * @status: the status code of _PPC evaluation
 *	0: success. OSPM is now using the perक्रमmance state specअगरied.
 *	1: failure. OSPM has not changed the number of P-states in use
 */
अटल व्योम acpi_processor_ppc_ost(acpi_handle handle, पूर्णांक status)
अणु
	अगर (acpi_has_method(handle, "_OST"))
		acpi_evaluate_ost(handle, ACPI_PROCESSOR_NOTIFY_PERFORMANCE,
				  status, शून्य);
पूर्ण

व्योम acpi_processor_ppc_has_changed(काष्ठा acpi_processor *pr, पूर्णांक event_flag)
अणु
	पूर्णांक ret;

	अगर (ignore_ppc || !pr->perक्रमmance) अणु
		/*
		 * Only when it is notअगरication event, the _OST object
		 * will be evaluated. Otherwise it is skipped.
		 */
		अगर (event_flag)
			acpi_processor_ppc_ost(pr->handle, 1);
		वापस;
	पूर्ण

	ret = acpi_processor_get_platक्रमm_limit(pr);
	/*
	 * Only when it is notअगरication event, the _OST object
	 * will be evaluated. Otherwise it is skipped.
	 */
	अगर (event_flag) अणु
		अगर (ret < 0)
			acpi_processor_ppc_ost(pr->handle, 1);
		अन्यथा
			acpi_processor_ppc_ost(pr->handle, 0);
	पूर्ण
	अगर (ret >= 0)
		cpufreq_update_limits(pr->id);
पूर्ण

पूर्णांक acpi_processor_get_bios_limit(पूर्णांक cpu, अचिन्हित पूर्णांक *limit)
अणु
	काष्ठा acpi_processor *pr;

	pr = per_cpu(processors, cpu);
	अगर (!pr || !pr->perक्रमmance || !pr->perक्रमmance->state_count)
		वापस -ENODEV;
	*limit = pr->perक्रमmance->states[pr->perक्रमmance_platक्रमm_limit].
		core_frequency * 1000;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(acpi_processor_get_bios_limit);

व्योम acpi_processor_ignore_ppc_init(व्योम)
अणु
	अगर (ignore_ppc < 0)
		ignore_ppc = 0;
पूर्ण

व्योम acpi_processor_ppc_init(काष्ठा cpufreq_policy *policy)
अणु
	अचिन्हित पूर्णांक cpu;

	क्रम_each_cpu(cpu, policy->related_cpus) अणु
		काष्ठा acpi_processor *pr = per_cpu(processors, cpu);
		पूर्णांक ret;

		अगर (!pr)
			जारी;

		ret = freq_qos_add_request(&policy->स्थिरraपूर्णांकs,
					   &pr->perflib_req,
					   FREQ_QOS_MAX, पूर्णांक_उच्च);
		अगर (ret < 0)
			pr_err("Failed to add freq constraint for CPU%d (%d)\n",
			       cpu, ret);
	पूर्ण
पूर्ण

व्योम acpi_processor_ppc_निकास(काष्ठा cpufreq_policy *policy)
अणु
	अचिन्हित पूर्णांक cpu;

	क्रम_each_cpu(cpu, policy->related_cpus) अणु
		काष्ठा acpi_processor *pr = per_cpu(processors, cpu);

		अगर (pr)
			freq_qos_हटाओ_request(&pr->perflib_req);
	पूर्ण
पूर्ण

अटल पूर्णांक acpi_processor_get_perक्रमmance_control(काष्ठा acpi_processor *pr)
अणु
	पूर्णांक result = 0;
	acpi_status status = 0;
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *pct = शून्य;
	जोड़ acpi_object obj = अणु 0 पूर्ण;


	status = acpi_evaluate_object(pr->handle, "_PCT", शून्य, &buffer);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_evaluation_failure_warn(pr->handle, "_PCT", status);
		वापस -ENODEV;
	पूर्ण

	pct = (जोड़ acpi_object *)buffer.poपूर्णांकer;
	अगर (!pct || (pct->type != ACPI_TYPE_PACKAGE)
	    || (pct->package.count != 2)) अणु
		prपूर्णांकk(KERN_ERR PREFIX "Invalid _PCT data\n");
		result = -EFAULT;
		जाओ end;
	पूर्ण

	/*
	 * control_रेजिस्टर
	 */

	obj = pct->package.elements[0];

	अगर ((obj.type != ACPI_TYPE_BUFFER)
	    || (obj.buffer.length < माप(काष्ठा acpi_pct_रेजिस्टर))
	    || (obj.buffer.poपूर्णांकer == शून्य)) अणु
		prपूर्णांकk(KERN_ERR PREFIX "Invalid _PCT data (control_register)\n");
		result = -EFAULT;
		जाओ end;
	पूर्ण
	स_नकल(&pr->perक्रमmance->control_रेजिस्टर, obj.buffer.poपूर्णांकer,
	       माप(काष्ठा acpi_pct_रेजिस्टर));

	/*
	 * status_रेजिस्टर
	 */

	obj = pct->package.elements[1];

	अगर ((obj.type != ACPI_TYPE_BUFFER)
	    || (obj.buffer.length < माप(काष्ठा acpi_pct_रेजिस्टर))
	    || (obj.buffer.poपूर्णांकer == शून्य)) अणु
		prपूर्णांकk(KERN_ERR PREFIX "Invalid _PCT data (status_register)\n");
		result = -EFAULT;
		जाओ end;
	पूर्ण

	स_नकल(&pr->perक्रमmance->status_रेजिस्टर, obj.buffer.poपूर्णांकer,
	       माप(काष्ठा acpi_pct_रेजिस्टर));

      end:
	kमुक्त(buffer.poपूर्णांकer);

	वापस result;
पूर्ण

#अगर_घोषित CONFIG_X86
/*
 * Some AMDs have 50MHz frequency multiples, but only provide 100MHz rounding
 * in their ACPI data. Calculate the real values and fix up the _PSS data.
 */
अटल व्योम amd_fixup_frequency(काष्ठा acpi_processor_px *px, पूर्णांक i)
अणु
	u32 hi, lo, fid, did;
	पूर्णांक index = px->control & 0x00000007;

	अगर (boot_cpu_data.x86_venकरोr != X86_VENDOR_AMD)
		वापस;

	अगर ((boot_cpu_data.x86 == 0x10 && boot_cpu_data.x86_model < 10)
	    || boot_cpu_data.x86 == 0x11) अणु
		rdmsr(MSR_AMD_PSTATE_DEF_BASE + index, lo, hi);
		/*
		 * MSR C001_0064+:
		 * Bit 63: PstateEn. Read-ग_लिखो. If set, the P-state is valid.
		 */
		अगर (!(hi & BIT(31)))
			वापस;

		fid = lo & 0x3f;
		did = (lo >> 6) & 7;
		अगर (boot_cpu_data.x86 == 0x10)
			px->core_frequency = (100 * (fid + 0x10)) >> did;
		अन्यथा
			px->core_frequency = (100 * (fid + 8)) >> did;
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम amd_fixup_frequency(काष्ठा acpi_processor_px *px, पूर्णांक i) अणुपूर्ण;
#पूर्ण_अगर

अटल पूर्णांक acpi_processor_get_perक्रमmance_states(काष्ठा acpi_processor *pr)
अणु
	पूर्णांक result = 0;
	acpi_status status = AE_OK;
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	काष्ठा acpi_buffer क्रमmat = अणु माप("NNNNNN"), "NNNNNN" पूर्ण;
	काष्ठा acpi_buffer state = अणु 0, शून्य पूर्ण;
	जोड़ acpi_object *pss = शून्य;
	पूर्णांक i;
	पूर्णांक last_invalid = -1;


	status = acpi_evaluate_object(pr->handle, "_PSS", शून्य, &buffer);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_evaluation_failure_warn(pr->handle, "_PSS", status);
		वापस -ENODEV;
	पूर्ण

	pss = buffer.poपूर्णांकer;
	अगर (!pss || (pss->type != ACPI_TYPE_PACKAGE)) अणु
		prपूर्णांकk(KERN_ERR PREFIX "Invalid _PSS data\n");
		result = -EFAULT;
		जाओ end;
	पूर्ण

	acpi_handle_debug(pr->handle, "Found %d performance states\n",
			  pss->package.count);

	pr->perक्रमmance->state_count = pss->package.count;
	pr->perक्रमmance->states =
	    kदो_स्मृति_array(pss->package.count,
			  माप(काष्ठा acpi_processor_px),
			  GFP_KERNEL);
	अगर (!pr->perक्रमmance->states) अणु
		result = -ENOMEM;
		जाओ end;
	पूर्ण

	क्रम (i = 0; i < pr->perक्रमmance->state_count; i++) अणु

		काष्ठा acpi_processor_px *px = &(pr->perक्रमmance->states[i]);

		state.length = माप(काष्ठा acpi_processor_px);
		state.poपूर्णांकer = px;

		acpi_handle_debug(pr->handle, "Extracting state %d\n", i);

		status = acpi_extract_package(&(pss->package.elements[i]),
					      &क्रमmat, &state);
		अगर (ACPI_FAILURE(status)) अणु
			acpi_handle_warn(pr->handle, "Invalid _PSS data: %s\n",
					 acpi_क्रमmat_exception(status));
			result = -EFAULT;
			kमुक्त(pr->perक्रमmance->states);
			जाओ end;
		पूर्ण

		amd_fixup_frequency(px, i);

		acpi_handle_debug(pr->handle,
				  "State [%d]: core_frequency[%d] power[%d] transition_latency[%d] bus_master_latency[%d] control[0x%x] status[0x%x]\n",
				  i,
				  (u32) px->core_frequency,
				  (u32) px->घातer,
				  (u32) px->transition_latency,
				  (u32) px->bus_master_latency,
				  (u32) px->control, (u32) px->status);

		/*
		 * Check that ACPI's u64 MHz will be valid as u32 KHz in cpufreq
		 */
		अगर (!px->core_frequency ||
		    ((u32)(px->core_frequency * 1000) !=
		     (px->core_frequency * 1000))) अणु
			prपूर्णांकk(KERN_ERR FW_BUG PREFIX
			       "Invalid BIOS _PSS frequency found for processor %d: 0x%llx MHz\n",
			       pr->id, px->core_frequency);
			अगर (last_invalid == -1)
				last_invalid = i;
		पूर्ण अन्यथा अणु
			अगर (last_invalid != -1) अणु
				/*
				 * Copy this valid entry over last_invalid entry
				 */
				स_नकल(&(pr->perक्रमmance->states[last_invalid]),
				       px, माप(काष्ठा acpi_processor_px));
				++last_invalid;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (last_invalid == 0) अणु
		prपूर्णांकk(KERN_ERR FW_BUG PREFIX
		       "No valid BIOS _PSS frequency found for processor %d\n", pr->id);
		result = -EFAULT;
		kमुक्त(pr->perक्रमmance->states);
		pr->perक्रमmance->states = शून्य;
	पूर्ण

	अगर (last_invalid > 0)
		pr->perक्रमmance->state_count = last_invalid;

      end:
	kमुक्त(buffer.poपूर्णांकer);

	वापस result;
पूर्ण

पूर्णांक acpi_processor_get_perक्रमmance_info(काष्ठा acpi_processor *pr)
अणु
	पूर्णांक result = 0;

	अगर (!pr || !pr->perक्रमmance || !pr->handle)
		वापस -EINVAL;

	अगर (!acpi_has_method(pr->handle, "_PCT")) अणु
		acpi_handle_debug(pr->handle,
				  "ACPI-based processor performance control unavailable\n");
		वापस -ENODEV;
	पूर्ण

	result = acpi_processor_get_perक्रमmance_control(pr);
	अगर (result)
		जाओ update_bios;

	result = acpi_processor_get_perक्रमmance_states(pr);
	अगर (result)
		जाओ update_bios;

	/* We need to call _PPC once when cpufreq starts */
	अगर (ignore_ppc != 1)
		result = acpi_processor_get_platक्रमm_limit(pr);

	वापस result;

	/*
	 * Having _PPC but missing frequencies (_PSS, _PCT) is a very good hपूर्णांक that
	 * the BIOS is older than the CPU and करोes not know its frequencies
	 */
 update_bios:
#अगर_घोषित CONFIG_X86
	अगर (acpi_has_method(pr->handle, "_PPC")) अणु
		अगर(boot_cpu_has(X86_FEATURE_EST))
			prपूर्णांकk(KERN_WARNING FW_BUG "BIOS needs update for CPU "
			       "frequency support\n");
	पूर्ण
#पूर्ण_अगर
	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_processor_get_perक्रमmance_info);

पूर्णांक acpi_processor_pstate_control(व्योम)
अणु
	acpi_status status;

	अगर (!acpi_gbl_FADT.smi_command || !acpi_gbl_FADT.pstate_control)
		वापस 0;

	pr_debug("Writing pstate_control [0x%x] to smi_command [0x%x]\n",
		 acpi_gbl_FADT.pstate_control, acpi_gbl_FADT.smi_command);

	status = acpi_os_ग_लिखो_port(acpi_gbl_FADT.smi_command,
				    (u32)acpi_gbl_FADT.pstate_control, 8);
	अगर (ACPI_SUCCESS(status))
		वापस 1;

	pr_warn("Failed to write pstate_control [0x%x] to smi_command [0x%x]: %s\n",
		acpi_gbl_FADT.pstate_control, acpi_gbl_FADT.smi_command,
		acpi_क्रमmat_exception(status));
	वापस -EIO;
पूर्ण

पूर्णांक acpi_processor_notअगरy_smm(काष्ठा module *calling_module)
अणु
	अटल पूर्णांक is_करोne;
	पूर्णांक result;

	अगर (!acpi_processor_cpufreq_init)
		वापस -EBUSY;

	अगर (!try_module_get(calling_module))
		वापस -EINVAL;

	/* is_करोne is set to negative अगर an error occurred,
	 * and to postitive अगर _no_ error occurred, but SMM
	 * was alपढ़ोy notअगरied. This aव्योमs द्विगुन notअगरication
	 * which might lead to unexpected results...
	 */
	अगर (is_करोne > 0) अणु
		module_put(calling_module);
		वापस 0;
	पूर्ण अन्यथा अगर (is_करोne < 0) अणु
		module_put(calling_module);
		वापस is_करोne;
	पूर्ण

	is_करोne = -EIO;

	result = acpi_processor_pstate_control();
	अगर (!result) अणु
		pr_debug("No SMI port or pstate_control\n");
		module_put(calling_module);
		वापस 0;
	पूर्ण
	अगर (result < 0) अणु
		module_put(calling_module);
		वापस result;
	पूर्ण

	/* Success. If there's no _PPC, we need to fear nothing, so
	 * we can allow the cpufreq driver to be rmmod'ed. */
	is_करोne = 1;

	अगर (!acpi_processor_ppc_in_use)
		module_put(calling_module);

	वापस 0;
पूर्ण

EXPORT_SYMBOL(acpi_processor_notअगरy_smm);

पूर्णांक acpi_processor_get_psd(acpi_handle handle, काष्ठा acpi_psd_package *pकरोमुख्य)
अणु
	पूर्णांक result = 0;
	acpi_status status = AE_OK;
	काष्ठा acpi_buffer buffer = अणुACPI_ALLOCATE_BUFFER, शून्यपूर्ण;
	काष्ठा acpi_buffer क्रमmat = अणुमाप("NNNNN"), "NNNNN"पूर्ण;
	काष्ठा acpi_buffer state = अणु0, शून्यपूर्ण;
	जोड़ acpi_object  *psd = शून्य;

	status = acpi_evaluate_object(handle, "_PSD", शून्य, &buffer);
	अगर (ACPI_FAILURE(status)) अणु
		वापस -ENODEV;
	पूर्ण

	psd = buffer.poपूर्णांकer;
	अगर (!psd || (psd->type != ACPI_TYPE_PACKAGE)) अणु
		prपूर्णांकk(KERN_ERR PREFIX "Invalid _PSD data\n");
		result = -EFAULT;
		जाओ end;
	पूर्ण

	अगर (psd->package.count != 1) अणु
		prपूर्णांकk(KERN_ERR PREFIX "Invalid _PSD data\n");
		result = -EFAULT;
		जाओ end;
	पूर्ण

	state.length = माप(काष्ठा acpi_psd_package);
	state.poपूर्णांकer = pकरोमुख्य;

	status = acpi_extract_package(&(psd->package.elements[0]),
		&क्रमmat, &state);
	अगर (ACPI_FAILURE(status)) अणु
		prपूर्णांकk(KERN_ERR PREFIX "Invalid _PSD data\n");
		result = -EFAULT;
		जाओ end;
	पूर्ण

	अगर (pकरोमुख्य->num_entries != ACPI_PSD_REV0_ENTRIES) अणु
		prपूर्णांकk(KERN_ERR PREFIX "Unknown _PSD:num_entries\n");
		result = -EFAULT;
		जाओ end;
	पूर्ण

	अगर (pकरोमुख्य->revision != ACPI_PSD_REV0_REVISION) अणु
		prपूर्णांकk(KERN_ERR PREFIX "Unknown _PSD:revision\n");
		result = -EFAULT;
		जाओ end;
	पूर्ण

	अगर (pकरोमुख्य->coord_type != DOMAIN_COORD_TYPE_SW_ALL &&
	    pकरोमुख्य->coord_type != DOMAIN_COORD_TYPE_SW_ANY &&
	    pकरोमुख्य->coord_type != DOMAIN_COORD_TYPE_HW_ALL) अणु
		prपूर्णांकk(KERN_ERR PREFIX "Invalid _PSD:coord_type\n");
		result = -EFAULT;
		जाओ end;
	पूर्ण
end:
	kमुक्त(buffer.poपूर्णांकer);
	वापस result;
पूर्ण
EXPORT_SYMBOL(acpi_processor_get_psd);

पूर्णांक acpi_processor_preरेजिस्टर_perक्रमmance(
		काष्ठा acpi_processor_perक्रमmance __percpu *perक्रमmance)
अणु
	पूर्णांक count_target;
	पूर्णांक retval = 0;
	अचिन्हित पूर्णांक i, j;
	cpumask_var_t covered_cpus;
	काष्ठा acpi_processor *pr;
	काष्ठा acpi_psd_package *pकरोमुख्य;
	काष्ठा acpi_processor *match_pr;
	काष्ठा acpi_psd_package *match_pकरोमुख्य;

	अगर (!zalloc_cpumask_var(&covered_cpus, GFP_KERNEL))
		वापस -ENOMEM;

	mutex_lock(&perक्रमmance_mutex);

	/*
	 * Check अगर another driver has alपढ़ोy रेजिस्टरed, and पात beक्रमe
	 * changing pr->perक्रमmance अगर it has. Check input data as well.
	 */
	क्रम_each_possible_cpu(i) अणु
		pr = per_cpu(processors, i);
		अगर (!pr) अणु
			/* Look only at processors in ACPI namespace */
			जारी;
		पूर्ण

		अगर (pr->perक्रमmance) अणु
			retval = -EBUSY;
			जाओ err_out;
		पूर्ण

		अगर (!perक्रमmance || !per_cpu_ptr(perक्रमmance, i)) अणु
			retval = -EINVAL;
			जाओ err_out;
		पूर्ण
	पूर्ण

	/* Call _PSD क्रम all CPUs */
	क्रम_each_possible_cpu(i) अणु
		pr = per_cpu(processors, i);
		अगर (!pr)
			जारी;

		pr->perक्रमmance = per_cpu_ptr(perक्रमmance, i);
		pकरोमुख्य = &(pr->perक्रमmance->करोमुख्य_info);
		अगर (acpi_processor_get_psd(pr->handle, pकरोमुख्य)) अणु
			retval = -EINVAL;
			जारी;
		पूर्ण
	पूर्ण
	अगर (retval)
		जाओ err_ret;

	/*
	 * Now that we have _PSD data from all CPUs, lets setup P-state
	 * करोमुख्य info.
	 */
	क्रम_each_possible_cpu(i) अणु
		pr = per_cpu(processors, i);
		अगर (!pr)
			जारी;

		अगर (cpumask_test_cpu(i, covered_cpus))
			जारी;

		pकरोमुख्य = &(pr->perक्रमmance->करोमुख्य_info);
		cpumask_set_cpu(i, pr->perक्रमmance->shared_cpu_map);
		cpumask_set_cpu(i, covered_cpus);
		अगर (pकरोमुख्य->num_processors <= 1)
			जारी;

		/* Validate the Doमुख्य info */
		count_target = pकरोमुख्य->num_processors;
		अगर (pकरोमुख्य->coord_type == DOMAIN_COORD_TYPE_SW_ALL)
			pr->perक्रमmance->shared_type = CPUFREQ_SHARED_TYPE_ALL;
		अन्यथा अगर (pकरोमुख्य->coord_type == DOMAIN_COORD_TYPE_HW_ALL)
			pr->perक्रमmance->shared_type = CPUFREQ_SHARED_TYPE_HW;
		अन्यथा अगर (pकरोमुख्य->coord_type == DOMAIN_COORD_TYPE_SW_ANY)
			pr->perक्रमmance->shared_type = CPUFREQ_SHARED_TYPE_ANY;

		क्रम_each_possible_cpu(j) अणु
			अगर (i == j)
				जारी;

			match_pr = per_cpu(processors, j);
			अगर (!match_pr)
				जारी;

			match_pकरोमुख्य = &(match_pr->perक्रमmance->करोमुख्य_info);
			अगर (match_pकरोमुख्य->करोमुख्य != pकरोमुख्य->करोमुख्य)
				जारी;

			/* Here i and j are in the same करोमुख्य */

			अगर (match_pकरोमुख्य->num_processors != count_target) अणु
				retval = -EINVAL;
				जाओ err_ret;
			पूर्ण

			अगर (pकरोमुख्य->coord_type != match_pकरोमुख्य->coord_type) अणु
				retval = -EINVAL;
				जाओ err_ret;
			पूर्ण

			cpumask_set_cpu(j, covered_cpus);
			cpumask_set_cpu(j, pr->perक्रमmance->shared_cpu_map);
		पूर्ण

		क्रम_each_possible_cpu(j) अणु
			अगर (i == j)
				जारी;

			match_pr = per_cpu(processors, j);
			अगर (!match_pr)
				जारी;

			match_pकरोमुख्य = &(match_pr->perक्रमmance->करोमुख्य_info);
			अगर (match_pकरोमुख्य->करोमुख्य != pकरोमुख्य->करोमुख्य)
				जारी;

			match_pr->perक्रमmance->shared_type =
					pr->perक्रमmance->shared_type;
			cpumask_copy(match_pr->perक्रमmance->shared_cpu_map,
				     pr->perक्रमmance->shared_cpu_map);
		पूर्ण
	पूर्ण

err_ret:
	क्रम_each_possible_cpu(i) अणु
		pr = per_cpu(processors, i);
		अगर (!pr || !pr->perक्रमmance)
			जारी;

		/* Assume no coordination on any error parsing करोमुख्य info */
		अगर (retval) अणु
			cpumask_clear(pr->perक्रमmance->shared_cpu_map);
			cpumask_set_cpu(i, pr->perक्रमmance->shared_cpu_map);
			pr->perक्रमmance->shared_type = CPUFREQ_SHARED_TYPE_NONE;
		पूर्ण
		pr->perक्रमmance = शून्य; /* Will be set क्रम real in रेजिस्टर */
	पूर्ण

err_out:
	mutex_unlock(&perक्रमmance_mutex);
	मुक्त_cpumask_var(covered_cpus);
	वापस retval;
पूर्ण
EXPORT_SYMBOL(acpi_processor_preरेजिस्टर_perक्रमmance);

पूर्णांक
acpi_processor_रेजिस्टर_perक्रमmance(काष्ठा acpi_processor_perक्रमmance
				    *perक्रमmance, अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा acpi_processor *pr;

	अगर (!acpi_processor_cpufreq_init)
		वापस -EINVAL;

	mutex_lock(&perक्रमmance_mutex);

	pr = per_cpu(processors, cpu);
	अगर (!pr) अणु
		mutex_unlock(&perक्रमmance_mutex);
		वापस -ENODEV;
	पूर्ण

	अगर (pr->perक्रमmance) अणु
		mutex_unlock(&perक्रमmance_mutex);
		वापस -EBUSY;
	पूर्ण

	WARN_ON(!perक्रमmance);

	pr->perक्रमmance = perक्रमmance;

	अगर (acpi_processor_get_perक्रमmance_info(pr)) अणु
		pr->perक्रमmance = शून्य;
		mutex_unlock(&perक्रमmance_mutex);
		वापस -EIO;
	पूर्ण

	mutex_unlock(&perक्रमmance_mutex);
	वापस 0;
पूर्ण

EXPORT_SYMBOL(acpi_processor_रेजिस्टर_perक्रमmance);

व्योम acpi_processor_unरेजिस्टर_perक्रमmance(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा acpi_processor *pr;

	mutex_lock(&perक्रमmance_mutex);

	pr = per_cpu(processors, cpu);
	अगर (!pr) अणु
		mutex_unlock(&perक्रमmance_mutex);
		वापस;
	पूर्ण

	अगर (pr->perक्रमmance)
		kमुक्त(pr->perक्रमmance->states);
	pr->perक्रमmance = शून्य;

	mutex_unlock(&perक्रमmance_mutex);

	वापस;
पूर्ण

EXPORT_SYMBOL(acpi_processor_unरेजिस्टर_perक्रमmance);
