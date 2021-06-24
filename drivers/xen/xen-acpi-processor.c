<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2012 by Oracle Inc
 * Author: Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>
 *
 * This code borrows ideas from
 * https://lore.kernel.org/lkml/1322673664-14642-6-git-send-email-konrad.wilk@oracle.com
 * so many thanks go to Kevin Tian <kevin.tian@पूर्णांकel.com>
 * and Yu Ke <ke.yu@पूर्णांकel.com>.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/cpumask.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/acpi.h>
#समावेश <acpi/processor.h>
#समावेश <xen/xen.h>
#समावेश <xen/पूर्णांकerface/platक्रमm.h>
#समावेश <यंत्र/xen/hypercall.h>

अटल पूर्णांक no_hypercall;
MODULE_PARM_DESC(off, "Inhibit the hypercall.");
module_param_named(off, no_hypercall, पूर्णांक, 0400);

/*
 * Note: Do not convert the acpi_id* below to cpumask_var_t or use cpumask_bit
 * - as those shrink to nr_cpu_bits (which is dependent on possible_cpu), which
 * can be less than what we want to put in. Instead use the 'nr_acpi_bits'
 * which is dynamically computed based on the MADT or x2APIC table.
 */
अटल अचिन्हित पूर्णांक nr_acpi_bits;
/* Mutex to protect the acpi_ids_करोne - क्रम CPU hotplug use. */
अटल DEFINE_MUTEX(acpi_ids_mutex);
/* Which ACPI ID we have processed from 'struct acpi_processor'. */
अटल अचिन्हित दीर्घ *acpi_ids_करोne;
/* Which ACPI ID exist in the SSDT/DSDT processor definitions. */
अटल अचिन्हित दीर्घ *acpi_id_present;
/* And अगर there is an _CST definition (or a PBLK) क्रम the ACPI IDs */
अटल अचिन्हित दीर्घ *acpi_id_cst_present;
/* Which ACPI P-State dependencies क्रम a क्रमागतerated processor */
अटल काष्ठा acpi_psd_package *acpi_psd;

अटल पूर्णांक push_cxx_to_hypervisor(काष्ठा acpi_processor *_pr)
अणु
	काष्ठा xen_platक्रमm_op op = अणु
		.cmd			= XENPF_set_processor_pminfo,
		.पूर्णांकerface_version	= XENPF_INTERFACE_VERSION,
		.u.set_pminfo.id	= _pr->acpi_id,
		.u.set_pminfo.type	= XEN_PM_CX,
	पूर्ण;
	काष्ठा xen_processor_cx *dst_cx, *dst_cx_states = शून्य;
	काष्ठा acpi_processor_cx *cx;
	अचिन्हित पूर्णांक i, ok;
	पूर्णांक ret = 0;

	dst_cx_states = kसुस्मृति(_pr->घातer.count,
				माप(काष्ठा xen_processor_cx), GFP_KERNEL);
	अगर (!dst_cx_states)
		वापस -ENOMEM;

	क्रम (ok = 0, i = 1; i <= _pr->घातer.count; i++) अणु
		cx = &_pr->घातer.states[i];
		अगर (!cx->valid)
			जारी;

		dst_cx = &(dst_cx_states[ok++]);

		dst_cx->reg.space_id = ACPI_ADR_SPACE_SYSTEM_IO;
		अगर (cx->entry_method == ACPI_CSTATE_SYSTEMIO) अणु
			dst_cx->reg.bit_width = 8;
			dst_cx->reg.bit_offset = 0;
			dst_cx->reg.access_size = 1;
		पूर्ण अन्यथा अणु
			dst_cx->reg.space_id = ACPI_ADR_SPACE_FIXED_HARDWARE;
			अगर (cx->entry_method == ACPI_CSTATE_FFH) अणु
				/* NATIVE_CSTATE_BEYOND_HALT */
				dst_cx->reg.bit_offset = 2;
				dst_cx->reg.bit_width = 1; /* VENDOR_INTEL */
			पूर्ण
			dst_cx->reg.access_size = 0;
		पूर्ण
		dst_cx->reg.address = cx->address;

		dst_cx->type = cx->type;
		dst_cx->latency = cx->latency;

		dst_cx->dpcnt = 0;
		set_xen_guest_handle(dst_cx->dp, शून्य);
	पूर्ण
	अगर (!ok) अणु
		pr_debug("No _Cx for ACPI CPU %u\n", _pr->acpi_id);
		kमुक्त(dst_cx_states);
		वापस -EINVAL;
	पूर्ण
	op.u.set_pminfo.घातer.count = ok;
	op.u.set_pminfo.घातer.flags.bm_control = _pr->flags.bm_control;
	op.u.set_pminfo.घातer.flags.bm_check = _pr->flags.bm_check;
	op.u.set_pminfo.घातer.flags.has_cst = _pr->flags.has_cst;
	op.u.set_pminfo.घातer.flags.घातer_setup_करोne =
		_pr->flags.घातer_setup_करोne;

	set_xen_guest_handle(op.u.set_pminfo.घातer.states, dst_cx_states);

	अगर (!no_hypercall)
		ret = HYPERVISOR_platक्रमm_op(&op);

	अगर (!ret) अणु
		pr_debug("ACPI CPU%u - C-states uploaded.\n", _pr->acpi_id);
		क्रम (i = 1; i <= _pr->घातer.count; i++) अणु
			cx = &_pr->घातer.states[i];
			अगर (!cx->valid)
				जारी;
			pr_debug("     C%d: %s %d uS\n",
				 cx->type, cx->desc, (u32)cx->latency);
		पूर्ण
	पूर्ण अन्यथा अगर ((ret != -EINVAL) && (ret != -ENOSYS))
		/* EINVAL means the ACPI ID is incorrect - meaning the ACPI
		 * table is referencing a non-existing CPU - which can happen
		 * with broken ACPI tables. */
		pr_err("(CX): Hypervisor error (%d) for ACPI CPU%u\n",
		       ret, _pr->acpi_id);

	kमुक्त(dst_cx_states);

	वापस ret;
पूर्ण
अटल काष्ठा xen_processor_px *
xen_copy_pss_data(काष्ठा acpi_processor *_pr,
		  काष्ठा xen_processor_perक्रमmance *dst_perf)
अणु
	काष्ठा xen_processor_px *dst_states = शून्य;
	अचिन्हित पूर्णांक i;

	BUILD_BUG_ON(माप(काष्ठा xen_processor_px) !=
		     माप(काष्ठा acpi_processor_px));

	dst_states = kसुस्मृति(_pr->perक्रमmance->state_count,
			     माप(काष्ठा xen_processor_px), GFP_KERNEL);
	अगर (!dst_states)
		वापस ERR_PTR(-ENOMEM);

	dst_perf->state_count = _pr->perक्रमmance->state_count;
	क्रम (i = 0; i < _pr->perक्रमmance->state_count; i++) अणु
		/* Fortunatly क्रम us, they are both the same size */
		स_नकल(&(dst_states[i]), &(_pr->perक्रमmance->states[i]),
		       माप(काष्ठा acpi_processor_px));
	पूर्ण
	वापस dst_states;
पूर्ण
अटल पूर्णांक xen_copy_psd_data(काष्ठा acpi_processor *_pr,
			     काष्ठा xen_processor_perक्रमmance *dst)
अणु
	काष्ठा acpi_psd_package *pकरोमुख्य;

	BUILD_BUG_ON(माप(काष्ठा xen_psd_package) !=
		     माप(काष्ठा acpi_psd_package));

	/* This inक्रमmation is क्रमागतerated only अगर acpi_processor_preरेजिस्टर_perक्रमmance
	 * has been called.
	 */
	dst->shared_type = _pr->perक्रमmance->shared_type;

	pकरोमुख्य = &(_pr->perक्रमmance->करोमुख्य_info);

	/* 'acpi_processor_preregister_performance' करोes not parse अगर the
	 * num_processors <= 1, but Xen still requires it. Do it manually here.
	 */
	अगर (pकरोमुख्य->num_processors <= 1) अणु
		अगर (pकरोमुख्य->coord_type == DOMAIN_COORD_TYPE_SW_ALL)
			dst->shared_type = CPUFREQ_SHARED_TYPE_ALL;
		अन्यथा अगर (pकरोमुख्य->coord_type == DOMAIN_COORD_TYPE_HW_ALL)
			dst->shared_type = CPUFREQ_SHARED_TYPE_HW;
		अन्यथा अगर (pकरोमुख्य->coord_type == DOMAIN_COORD_TYPE_SW_ANY)
			dst->shared_type = CPUFREQ_SHARED_TYPE_ANY;

	पूर्ण
	स_नकल(&(dst->करोमुख्य_info), pकरोमुख्य, माप(काष्ठा acpi_psd_package));
	वापस 0;
पूर्ण
अटल पूर्णांक xen_copy_pct_data(काष्ठा acpi_pct_रेजिस्टर *pct,
			     काष्ठा xen_pct_रेजिस्टर *dst_pct)
अणु
	/* It would be nice अगर you could just करो 'memcpy(pct, dst_pct') but
	 * sadly the Xen काष्ठाure did not have the proper padding so the
	 * descriptor field takes two (dst_pct) bytes instead of one (pct).
	 */
	dst_pct->descriptor = pct->descriptor;
	dst_pct->length = pct->length;
	dst_pct->space_id = pct->space_id;
	dst_pct->bit_width = pct->bit_width;
	dst_pct->bit_offset = pct->bit_offset;
	dst_pct->reserved = pct->reserved;
	dst_pct->address = pct->address;
	वापस 0;
पूर्ण
अटल पूर्णांक push_pxx_to_hypervisor(काष्ठा acpi_processor *_pr)
अणु
	पूर्णांक ret = 0;
	काष्ठा xen_platक्रमm_op op = अणु
		.cmd			= XENPF_set_processor_pminfo,
		.पूर्णांकerface_version	= XENPF_INTERFACE_VERSION,
		.u.set_pminfo.id	= _pr->acpi_id,
		.u.set_pminfo.type	= XEN_PM_PX,
	पूर्ण;
	काष्ठा xen_processor_perक्रमmance *dst_perf;
	काष्ठा xen_processor_px *dst_states = शून्य;

	dst_perf = &op.u.set_pminfo.perf;

	dst_perf->platक्रमm_limit = _pr->perक्रमmance_platक्रमm_limit;
	dst_perf->flags |= XEN_PX_PPC;
	xen_copy_pct_data(&(_pr->perक्रमmance->control_रेजिस्टर),
			  &dst_perf->control_रेजिस्टर);
	xen_copy_pct_data(&(_pr->perक्रमmance->status_रेजिस्टर),
			  &dst_perf->status_रेजिस्टर);
	dst_perf->flags |= XEN_PX_PCT;
	dst_states = xen_copy_pss_data(_pr, dst_perf);
	अगर (!IS_ERR_OR_शून्य(dst_states)) अणु
		set_xen_guest_handle(dst_perf->states, dst_states);
		dst_perf->flags |= XEN_PX_PSS;
	पूर्ण
	अगर (!xen_copy_psd_data(_pr, dst_perf))
		dst_perf->flags |= XEN_PX_PSD;

	अगर (dst_perf->flags != (XEN_PX_PSD | XEN_PX_PSS | XEN_PX_PCT | XEN_PX_PPC)) अणु
		pr_warn("ACPI CPU%u missing some P-state data (%x), skipping\n",
			_pr->acpi_id, dst_perf->flags);
		ret = -ENODEV;
		जाओ err_मुक्त;
	पूर्ण

	अगर (!no_hypercall)
		ret = HYPERVISOR_platक्रमm_op(&op);

	अगर (!ret) अणु
		काष्ठा acpi_processor_perक्रमmance *perf;
		अचिन्हित पूर्णांक i;

		perf = _pr->perक्रमmance;
		pr_debug("ACPI CPU%u - P-states uploaded.\n", _pr->acpi_id);
		क्रम (i = 0; i < perf->state_count; i++) अणु
			pr_debug("     %cP%d: %d MHz, %d mW, %d uS\n",
			(i == perf->state ? '*' : ' '), i,
			(u32) perf->states[i].core_frequency,
			(u32) perf->states[i].घातer,
			(u32) perf->states[i].transition_latency);
		पूर्ण
	पूर्ण अन्यथा अगर ((ret != -EINVAL) && (ret != -ENOSYS))
		/* EINVAL means the ACPI ID is incorrect - meaning the ACPI
		 * table is referencing a non-existing CPU - which can happen
		 * with broken ACPI tables. */
		pr_warn("(_PXX): Hypervisor error (%d) for ACPI CPU%u\n",
			ret, _pr->acpi_id);
err_मुक्त:
	अगर (!IS_ERR_OR_शून्य(dst_states))
		kमुक्त(dst_states);

	वापस ret;
पूर्ण
अटल पूर्णांक upload_pm_data(काष्ठा acpi_processor *_pr)
अणु
	पूर्णांक err = 0;

	mutex_lock(&acpi_ids_mutex);
	अगर (__test_and_set_bit(_pr->acpi_id, acpi_ids_करोne)) अणु
		mutex_unlock(&acpi_ids_mutex);
		वापस -EBUSY;
	पूर्ण
	अगर (_pr->flags.घातer)
		err = push_cxx_to_hypervisor(_pr);

	अगर (_pr->perक्रमmance && _pr->perक्रमmance->states)
		err |= push_pxx_to_hypervisor(_pr);

	mutex_unlock(&acpi_ids_mutex);
	वापस err;
पूर्ण
अटल अचिन्हित पूर्णांक __init get_max_acpi_id(व्योम)
अणु
	काष्ठा xenpf_pcpuinfo *info;
	काष्ठा xen_platक्रमm_op op = अणु
		.cmd = XENPF_get_cpuinfo,
		.पूर्णांकerface_version = XENPF_INTERFACE_VERSION,
	पूर्ण;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक i, last_cpu, max_acpi_id = 0;

	info = &op.u.pcpu_info;
	info->xen_cpuid = 0;

	ret = HYPERVISOR_platक्रमm_op(&op);
	अगर (ret)
		वापस NR_CPUS;

	/* The max_present is the same irregardless of the xen_cpuid */
	last_cpu = op.u.pcpu_info.max_present;
	क्रम (i = 0; i <= last_cpu; i++) अणु
		info->xen_cpuid = i;
		ret = HYPERVISOR_platक्रमm_op(&op);
		अगर (ret)
			जारी;
		max_acpi_id = max(info->acpi_id, max_acpi_id);
	पूर्ण
	max_acpi_id *= 2; /* Slack क्रम CPU hotplug support. */
	pr_debug("Max ACPI ID: %u\n", max_acpi_id);
	वापस max_acpi_id;
पूर्ण
/*
 * The पढ़ो_acpi_id and check_acpi_ids are there to support the Xen
 * oddity of भव CPUs != physical CPUs in the initial करोमुख्य.
 * The user can supply 'xen_max_vcpus=X' on the Xen hypervisor line
 * which will band the amount of CPUs the initial करोमुख्य can see.
 * In general that is OK, except it plays havoc with any of the
 * क्रम_each_[present|online]_cpu macros which are banded to the भव
 * CPU amount.
 */
अटल acpi_status
पढ़ो_acpi_id(acpi_handle handle, u32 lvl, व्योम *context, व्योम **rv)
अणु
	u32 acpi_id;
	acpi_status status;
	acpi_object_type acpi_type;
	अचिन्हित दीर्घ दीर्घ पंचांगp;
	जोड़ acpi_object object = अणु 0 पूर्ण;
	काष्ठा acpi_buffer buffer = अणु माप(जोड़ acpi_object), &object पूर्ण;
	acpi_io_address pblk = 0;

	status = acpi_get_type(handle, &acpi_type);
	अगर (ACPI_FAILURE(status))
		वापस AE_OK;

	चयन (acpi_type) अणु
	हाल ACPI_TYPE_PROCESSOR:
		status = acpi_evaluate_object(handle, शून्य, शून्य, &buffer);
		अगर (ACPI_FAILURE(status))
			वापस AE_OK;
		acpi_id = object.processor.proc_id;
		pblk = object.processor.pblk_address;
		अवरोध;
	हाल ACPI_TYPE_DEVICE:
		status = acpi_evaluate_पूर्णांकeger(handle, "_UID", शून्य, &पंचांगp);
		अगर (ACPI_FAILURE(status))
			वापस AE_OK;
		acpi_id = पंचांगp;
		अवरोध;
	शेष:
		वापस AE_OK;
	पूर्ण
	अगर (invalid_phys_cpuid(acpi_get_phys_id(handle,
						acpi_type == ACPI_TYPE_DEVICE,
						acpi_id))) अणु
		pr_debug("CPU with ACPI ID %u is unavailable\n", acpi_id);
		वापस AE_OK;
	पूर्ण
	/* There are more ACPI Processor objects than in x2APIC or MADT.
	 * This can happen with incorrect ACPI SSDT declerations. */
	अगर (acpi_id >= nr_acpi_bits) अणु
		pr_debug("max acpi id %u, trying to set %u\n",
			 nr_acpi_bits - 1, acpi_id);
		वापस AE_OK;
	पूर्ण
	/* OK, There is a ACPI Processor object */
	__set_bit(acpi_id, acpi_id_present);

	pr_debug("ACPI CPU%u w/ PBLK:0x%lx\n", acpi_id, (अचिन्हित दीर्घ)pblk);

	/* It has P-state dependencies */
	अगर (!acpi_processor_get_psd(handle, &acpi_psd[acpi_id])) अणु
		pr_debug("ACPI CPU%u w/ PST:coord_type = %llu domain = %llu\n",
			 acpi_id, acpi_psd[acpi_id].coord_type,
			 acpi_psd[acpi_id].करोमुख्य);
	पूर्ण

	status = acpi_evaluate_object(handle, "_CST", शून्य, &buffer);
	अगर (ACPI_FAILURE(status)) अणु
		अगर (!pblk)
			वापस AE_OK;
	पूर्ण
	/* .. and it has a C-state */
	__set_bit(acpi_id, acpi_id_cst_present);

	वापस AE_OK;
पूर्ण
अटल पूर्णांक check_acpi_ids(काष्ठा acpi_processor *pr_backup)
अणु

	अगर (!pr_backup)
		वापस -ENODEV;

	अगर (acpi_id_present && acpi_id_cst_present)
		/* OK, करोne this once .. skip to uploading */
		जाओ upload;

	/* All online CPUs have been processed at this stage. Now verअगरy
	 * whether in fact "online CPUs" == physical CPUs.
	 */
	acpi_id_present = biपंचांगap_zalloc(nr_acpi_bits, GFP_KERNEL);
	अगर (!acpi_id_present)
		वापस -ENOMEM;

	acpi_id_cst_present = biपंचांगap_zalloc(nr_acpi_bits, GFP_KERNEL);
	अगर (!acpi_id_cst_present) अणु
		biपंचांगap_मुक्त(acpi_id_present);
		वापस -ENOMEM;
	पूर्ण

	acpi_psd = kसुस्मृति(nr_acpi_bits, माप(काष्ठा acpi_psd_package),
			   GFP_KERNEL);
	अगर (!acpi_psd) अणु
		biपंचांगap_मुक्त(acpi_id_present);
		biपंचांगap_मुक्त(acpi_id_cst_present);
		वापस -ENOMEM;
	पूर्ण

	acpi_walk_namespace(ACPI_TYPE_PROCESSOR, ACPI_ROOT_OBJECT,
			    ACPI_UINT32_MAX,
			    पढ़ो_acpi_id, शून्य, शून्य, शून्य);
	acpi_get_devices(ACPI_PROCESSOR_DEVICE_HID, पढ़ो_acpi_id, शून्य, शून्य);

upload:
	अगर (!biपंचांगap_equal(acpi_id_present, acpi_ids_करोne, nr_acpi_bits)) अणु
		अचिन्हित पूर्णांक i;
		क्रम_each_set_bit(i, acpi_id_present, nr_acpi_bits) अणु
			pr_backup->acpi_id = i;
			/* Mask out C-states अगर there are no _CST or PBLK */
			pr_backup->flags.घातer = test_bit(i, acpi_id_cst_present);
			/* num_entries is non-zero अगर we evaluated _PSD */
			अगर (acpi_psd[i].num_entries) अणु
				स_नकल(&pr_backup->perक्रमmance->करोमुख्य_info,
				       &acpi_psd[i],
				       माप(काष्ठा acpi_psd_package));
			पूर्ण
			(व्योम)upload_pm_data(pr_backup);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* acpi_perf_data is a poपूर्णांकer to percpu data. */
अटल काष्ठा acpi_processor_perक्रमmance __percpu *acpi_perf_data;

अटल व्योम मुक्त_acpi_perf_data(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	/* Freeing a शून्य poपूर्णांकer is OK, and alloc_percpu zeroes. */
	क्रम_each_possible_cpu(i)
		मुक्त_cpumask_var(per_cpu_ptr(acpi_perf_data, i)
				 ->shared_cpu_map);
	मुक्त_percpu(acpi_perf_data);
पूर्ण

अटल पूर्णांक xen_upload_processor_pm_data(व्योम)
अणु
	काष्ठा acpi_processor *pr_backup = शून्य;
	अचिन्हित पूर्णांक i;
	पूर्णांक rc = 0;

	pr_info("Uploading Xen processor PM info\n");

	क्रम_each_possible_cpu(i) अणु
		काष्ठा acpi_processor *_pr;
		_pr = per_cpu(processors, i /* APIC ID */);
		अगर (!_pr)
			जारी;

		अगर (!pr_backup) अणु
			pr_backup = kzalloc(माप(काष्ठा acpi_processor), GFP_KERNEL);
			अगर (pr_backup)
				स_नकल(pr_backup, _pr, माप(काष्ठा acpi_processor));
		पूर्ण
		(व्योम)upload_pm_data(_pr);
	पूर्ण

	rc = check_acpi_ids(pr_backup);
	kमुक्त(pr_backup);

	वापस rc;
पूर्ण

अटल व्योम xen_acpi_processor_resume_worker(काष्ठा work_काष्ठा *dummy)
अणु
	पूर्णांक rc;

	biपंचांगap_zero(acpi_ids_करोne, nr_acpi_bits);

	rc = xen_upload_processor_pm_data();
	अगर (rc != 0)
		pr_info("ACPI data upload failed, error = %d\n", rc);
पूर्ण

अटल व्योम xen_acpi_processor_resume(व्योम)
अणु
	अटल DECLARE_WORK(wq, xen_acpi_processor_resume_worker);

	/*
	 * xen_upload_processor_pm_data() calls non-atomic code.
	 * However, the context क्रम xen_acpi_processor_resume is syscore
	 * with only the boot CPU online and in an atomic context.
	 *
	 * So defer the upload क्रम some poपूर्णांक safer.
	 */
	schedule_work(&wq);
पूर्ण

अटल काष्ठा syscore_ops xap_syscore_ops = अणु
	.resume	= xen_acpi_processor_resume,
पूर्ण;

अटल पूर्णांक __init xen_acpi_processor_init(व्योम)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक rc;

	अगर (!xen_initial_करोमुख्य())
		वापस -ENODEV;

	nr_acpi_bits = get_max_acpi_id() + 1;
	acpi_ids_करोne = biपंचांगap_zalloc(nr_acpi_bits, GFP_KERNEL);
	अगर (!acpi_ids_करोne)
		वापस -ENOMEM;

	acpi_perf_data = alloc_percpu(काष्ठा acpi_processor_perक्रमmance);
	अगर (!acpi_perf_data) अणु
		pr_debug("Memory allocation error for acpi_perf_data\n");
		biपंचांगap_मुक्त(acpi_ids_करोne);
		वापस -ENOMEM;
	पूर्ण
	क्रम_each_possible_cpu(i) अणु
		अगर (!zalloc_cpumask_var_node(
			&per_cpu_ptr(acpi_perf_data, i)->shared_cpu_map,
			GFP_KERNEL, cpu_to_node(i))) अणु
			rc = -ENOMEM;
			जाओ err_out;
		पूर्ण
	पूर्ण

	/* Do initialization in ACPI core. It is OK to fail here. */
	(व्योम)acpi_processor_preरेजिस्टर_perक्रमmance(acpi_perf_data);

	क्रम_each_possible_cpu(i) अणु
		काष्ठा acpi_processor *pr;
		काष्ठा acpi_processor_perक्रमmance *perf;

		pr = per_cpu(processors, i);
		perf = per_cpu_ptr(acpi_perf_data, i);
		अगर (!pr)
			जारी;

		pr->perक्रमmance = perf;
		rc = acpi_processor_get_perक्रमmance_info(pr);
		अगर (rc)
			जाओ err_out;
	पूर्ण

	rc = xen_upload_processor_pm_data();
	अगर (rc)
		जाओ err_unरेजिस्टर;

	रेजिस्टर_syscore_ops(&xap_syscore_ops);

	वापस 0;
err_unरेजिस्टर:
	क्रम_each_possible_cpu(i)
		acpi_processor_unरेजिस्टर_perक्रमmance(i);

err_out:
	/* Freeing a शून्य poपूर्णांकer is OK: alloc_percpu zeroes. */
	मुक्त_acpi_perf_data();
	biपंचांगap_मुक्त(acpi_ids_करोne);
	वापस rc;
पूर्ण
अटल व्योम __निकास xen_acpi_processor_निकास(व्योम)
अणु
	पूर्णांक i;

	unरेजिस्टर_syscore_ops(&xap_syscore_ops);
	biपंचांगap_मुक्त(acpi_ids_करोne);
	biपंचांगap_मुक्त(acpi_id_present);
	biपंचांगap_मुक्त(acpi_id_cst_present);
	kमुक्त(acpi_psd);
	क्रम_each_possible_cpu(i)
		acpi_processor_unरेजिस्टर_perक्रमmance(i);

	मुक्त_acpi_perf_data();
पूर्ण

MODULE_AUTHOR("Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>");
MODULE_DESCRIPTION("Xen ACPI Processor P-states (and Cx) driver which uploads PM data to Xen hypervisor");
MODULE_LICENSE("GPL");

/* We want to be loaded beक्रमe the CPU freq scaling drivers are loaded.
 * They are loaded in late_initcall. */
device_initcall(xen_acpi_processor_init);
module_निकास(xen_acpi_processor_निकास);
