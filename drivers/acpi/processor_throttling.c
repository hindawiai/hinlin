<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * processor_throttling.c - Throttling submodule of the ACPI processor driver
 *
 *  Copyright (C) 2001, 2002 Andy Grover <andrew.grover@पूर्णांकel.com>
 *  Copyright (C) 2001, 2002 Paul Diefenbaugh <paul.s.diefenbaugh@पूर्णांकel.com>
 *  Copyright (C) 2004       Dominik Broकरोwski <linux@broकरो.de>
 *  Copyright (C) 2004  Anil S Keshavamurthy <anil.s.keshavamurthy@पूर्णांकel.com>
 *  			- Added processor hotplug support
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/acpi.h>
#समावेश <acpi/processor.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>

#घोषणा PREFIX "ACPI: "

/* ignore_tpc:
 *  0 -> acpi processor driver करोesn't ignore _TPC values
 *  1 -> acpi processor driver ignores _TPC values
 */
अटल पूर्णांक ignore_tpc;
module_param(ignore_tpc, पूर्णांक, 0644);
MODULE_PARM_DESC(ignore_tpc, "Disable broken BIOS _TPC throttling support");

काष्ठा throttling_tstate अणु
	अचिन्हित पूर्णांक cpu;		/* cpu nr */
	पूर्णांक target_state;		/* target T-state */
पूर्ण;

काष्ठा acpi_processor_throttling_arg अणु
	काष्ठा acpi_processor *pr;
	पूर्णांक target_state;
	bool क्रमce;
पूर्ण;

#घोषणा THROTTLING_PRECHANGE       (1)
#घोषणा THROTTLING_POSTCHANGE      (2)

अटल पूर्णांक acpi_processor_get_throttling(काष्ठा acpi_processor *pr);
अटल पूर्णांक __acpi_processor_set_throttling(काष्ठा acpi_processor *pr,
					   पूर्णांक state, bool क्रमce, bool direct);

अटल पूर्णांक acpi_processor_update_tsd_coord(व्योम)
अणु
	पूर्णांक count, count_target;
	पूर्णांक retval = 0;
	अचिन्हित पूर्णांक i, j;
	cpumask_var_t covered_cpus;
	काष्ठा acpi_processor *pr, *match_pr;
	काष्ठा acpi_tsd_package *pकरोमुख्य, *match_pकरोमुख्य;
	काष्ठा acpi_processor_throttling *pthrottling, *match_pthrottling;

	अगर (!zalloc_cpumask_var(&covered_cpus, GFP_KERNEL))
		वापस -ENOMEM;

	/*
	 * Now that we have _TSD data from all CPUs, lets setup T-state
	 * coordination between all CPUs.
	 */
	क्रम_each_possible_cpu(i) अणु
		pr = per_cpu(processors, i);
		अगर (!pr)
			जारी;

		/* Basic validity check क्रम करोमुख्य info */
		pthrottling = &(pr->throttling);

		/*
		 * If tsd package क्रम one cpu is invalid, the coordination
		 * among all CPUs is thought as invalid.
		 * Maybe it is ugly.
		 */
		अगर (!pthrottling->tsd_valid_flag) अणु
			retval = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (retval)
		जाओ err_ret;

	क्रम_each_possible_cpu(i) अणु
		pr = per_cpu(processors, i);
		अगर (!pr)
			जारी;

		अगर (cpumask_test_cpu(i, covered_cpus))
			जारी;
		pthrottling = &pr->throttling;

		pकरोमुख्य = &(pthrottling->करोमुख्य_info);
		cpumask_set_cpu(i, pthrottling->shared_cpu_map);
		cpumask_set_cpu(i, covered_cpus);
		/*
		 * If the number of processor in the TSD करोमुख्य is 1, it is
		 * unnecessary to parse the coordination क्रम this CPU.
		 */
		अगर (pकरोमुख्य->num_processors <= 1)
			जारी;

		/* Validate the Doमुख्य info */
		count_target = pकरोमुख्य->num_processors;
		count = 1;

		क्रम_each_possible_cpu(j) अणु
			अगर (i == j)
				जारी;

			match_pr = per_cpu(processors, j);
			अगर (!match_pr)
				जारी;

			match_pthrottling = &(match_pr->throttling);
			match_pकरोमुख्य = &(match_pthrottling->करोमुख्य_info);
			अगर (match_pकरोमुख्य->करोमुख्य != pकरोमुख्य->करोमुख्य)
				जारी;

			/* Here i and j are in the same करोमुख्य.
			 * If two TSD packages have the same करोमुख्य, they
			 * should have the same num_porcessors and
			 * coordination type. Otherwise it will be regarded
			 * as illegal.
			 */
			अगर (match_pकरोमुख्य->num_processors != count_target) अणु
				retval = -EINVAL;
				जाओ err_ret;
			पूर्ण

			अगर (pकरोमुख्य->coord_type != match_pकरोमुख्य->coord_type) अणु
				retval = -EINVAL;
				जाओ err_ret;
			पूर्ण

			cpumask_set_cpu(j, covered_cpus);
			cpumask_set_cpu(j, pthrottling->shared_cpu_map);
			count++;
		पूर्ण
		क्रम_each_possible_cpu(j) अणु
			अगर (i == j)
				जारी;

			match_pr = per_cpu(processors, j);
			अगर (!match_pr)
				जारी;

			match_pthrottling = &(match_pr->throttling);
			match_pकरोमुख्य = &(match_pthrottling->करोमुख्य_info);
			अगर (match_pकरोमुख्य->करोमुख्य != pकरोमुख्य->करोमुख्य)
				जारी;

			/*
			 * If some CPUS have the same करोमुख्य, they
			 * will have the same shared_cpu_map.
			 */
			cpumask_copy(match_pthrottling->shared_cpu_map,
				     pthrottling->shared_cpu_map);
		पूर्ण
	पूर्ण

err_ret:
	मुक्त_cpumask_var(covered_cpus);

	क्रम_each_possible_cpu(i) अणु
		pr = per_cpu(processors, i);
		अगर (!pr)
			जारी;

		/*
		 * Assume no coordination on any error parsing करोमुख्य info.
		 * The coordination type will be क्रमced as SW_ALL.
		 */
		अगर (retval) अणु
			pthrottling = &(pr->throttling);
			cpumask_clear(pthrottling->shared_cpu_map);
			cpumask_set_cpu(i, pthrottling->shared_cpu_map);
			pthrottling->shared_type = DOMAIN_COORD_TYPE_SW_ALL;
		पूर्ण
	पूर्ण

	वापस retval;
पूर्ण

/*
 * Update the T-state coordination after the _TSD
 * data क्रम all cpus is obtained.
 */
व्योम acpi_processor_throttling_init(व्योम)
अणु
	अगर (acpi_processor_update_tsd_coord())
		pr_debug("Assume no T-state coordination\n");

	वापस;
पूर्ण

अटल पूर्णांक acpi_processor_throttling_notअगरier(अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा throttling_tstate *p_tstate = data;
	काष्ठा acpi_processor *pr;
	अचिन्हित पूर्णांक cpu ;
	पूर्णांक target_state;
	काष्ठा acpi_processor_limit *p_limit;
	काष्ठा acpi_processor_throttling *p_throttling;

	cpu = p_tstate->cpu;
	pr = per_cpu(processors, cpu);
	अगर (!pr) अणु
		pr_debug("Invalid pr pointer\n");
		वापस 0;
	पूर्ण
	अगर (!pr->flags.throttling) अणु
		acpi_handle_debug(pr->handle,
				  "Throttling control unsupported on CPU %d\n",
				  cpu);
		वापस 0;
	पूर्ण
	target_state = p_tstate->target_state;
	p_throttling = &(pr->throttling);
	चयन (event) अणु
	हाल THROTTLING_PRECHANGE:
		/*
		 * Prechange event is used to choose one proper t-state,
		 * which meets the limits of thermal, user and _TPC.
		 */
		p_limit = &pr->limit;
		अगर (p_limit->thermal.tx > target_state)
			target_state = p_limit->thermal.tx;
		अगर (p_limit->user.tx > target_state)
			target_state = p_limit->user.tx;
		अगर (pr->throttling_platक्रमm_limit > target_state)
			target_state = pr->throttling_platक्रमm_limit;
		अगर (target_state >= p_throttling->state_count) अणु
			prपूर्णांकk(KERN_WARNING
				"Exceed the limit of T-state \n");
			target_state = p_throttling->state_count - 1;
		पूर्ण
		p_tstate->target_state = target_state;
		acpi_handle_debug(pr->handle,
				  "PreChange Event: target T-state of CPU %d is T%d\n",
				  cpu, target_state);
		अवरोध;
	हाल THROTTLING_POSTCHANGE:
		/*
		 * Postchange event is only used to update the
		 * T-state flag of acpi_processor_throttling.
		 */
		p_throttling->state = target_state;
		acpi_handle_debug(pr->handle,
				  "PostChange Event: CPU %d is switched to T%d\n",
				  cpu, target_state);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING
			"Unsupported Throttling notifier event\n");
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * _TPC - Throttling Present Capabilities
 */
अटल पूर्णांक acpi_processor_get_platक्रमm_limit(काष्ठा acpi_processor *pr)
अणु
	acpi_status status = 0;
	अचिन्हित दीर्घ दीर्घ tpc = 0;

	अगर (!pr)
		वापस -EINVAL;

	अगर (ignore_tpc)
		जाओ end;

	status = acpi_evaluate_पूर्णांकeger(pr->handle, "_TPC", शून्य, &tpc);
	अगर (ACPI_FAILURE(status)) अणु
		अगर (status != AE_NOT_FOUND)
			acpi_evaluation_failure_warn(pr->handle, "_TPC", status);

		वापस -ENODEV;
	पूर्ण

end:
	pr->throttling_platक्रमm_limit = (पूर्णांक)tpc;
	वापस 0;
पूर्ण

पूर्णांक acpi_processor_tstate_has_changed(काष्ठा acpi_processor *pr)
अणु
	पूर्णांक result = 0;
	पूर्णांक throttling_limit;
	पूर्णांक current_state;
	काष्ठा acpi_processor_limit *limit;
	पूर्णांक target_state;

	अगर (ignore_tpc)
		वापस 0;

	result = acpi_processor_get_platक्रमm_limit(pr);
	अगर (result) अणु
		/* Throttling Limit is unsupported */
		वापस result;
	पूर्ण

	throttling_limit = pr->throttling_platक्रमm_limit;
	अगर (throttling_limit >= pr->throttling.state_count) अणु
		/* Uncorrect Throttling Limit */
		वापस -EINVAL;
	पूर्ण

	current_state = pr->throttling.state;
	अगर (current_state > throttling_limit) अणु
		/*
		 * The current state can meet the requirement of
		 * _TPC limit. But it is reasonable that OSPM changes
		 * t-states from high to low क्रम better perक्रमmance.
		 * Of course the limit condition of thermal
		 * and user should be considered.
		 */
		limit = &pr->limit;
		target_state = throttling_limit;
		अगर (limit->thermal.tx > target_state)
			target_state = limit->thermal.tx;
		अगर (limit->user.tx > target_state)
			target_state = limit->user.tx;
	पूर्ण अन्यथा अगर (current_state == throttling_limit) अणु
		/*
		 * Unnecessary to change the throttling state
		 */
		वापस 0;
	पूर्ण अन्यथा अणु
		/*
		 * If the current state is lower than the limit of _TPC, it
		 * will be क्रमced to चयन to the throttling state defined
		 * by throttling_platक्रम_limit.
		 * Because the previous state meets with the limit condition
		 * of thermal and user, it is unnecessary to check it again.
		 */
		target_state = throttling_limit;
	पूर्ण
	वापस acpi_processor_set_throttling(pr, target_state, false);
पूर्ण

/*
 * This function is used to reevaluate whether the T-state is valid
 * after one CPU is onlined/offlined.
 * It is noted that it won't reevaluate the following properties क्रम
 * the T-state.
 *	1. Control method.
 *	2. the number of supported T-state
 *	3. TSD करोमुख्य
 */
व्योम acpi_processor_reevaluate_tstate(काष्ठा acpi_processor *pr,
					bool is_dead)
अणु
	पूर्णांक result = 0;

	अगर (is_dead) अणु
		/* When one CPU is offline, the T-state throttling
		 * will be invalidated.
		 */
		pr->flags.throttling = 0;
		वापस;
	पूर्ण
	/* the following is to recheck whether the T-state is valid क्रम
	 * the online CPU
	 */
	अगर (!pr->throttling.state_count) अणु
		/* If the number of T-state is invalid, it is
		 * invalidated.
		 */
		pr->flags.throttling = 0;
		वापस;
	पूर्ण
	pr->flags.throttling = 1;

	/* Disable throttling (अगर enabled).  We'll let subsequent
	 * policy (e.g.thermal) decide to lower perक्रमmance अगर it
	 * so chooses, but क्रम now we'll crank up the speed.
	 */

	result = acpi_processor_get_throttling(pr);
	अगर (result)
		जाओ end;

	अगर (pr->throttling.state) अणु
		result = acpi_processor_set_throttling(pr, 0, false);
		अगर (result)
			जाओ end;
	पूर्ण

end:
	अगर (result)
		pr->flags.throttling = 0;
पूर्ण
/*
 * _PTC - Processor Throttling Control (and status) रेजिस्टर location
 */
अटल पूर्णांक acpi_processor_get_throttling_control(काष्ठा acpi_processor *pr)
अणु
	पूर्णांक result = 0;
	acpi_status status = 0;
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *ptc = शून्य;
	जोड़ acpi_object obj = अणु 0 पूर्ण;
	काष्ठा acpi_processor_throttling *throttling;

	status = acpi_evaluate_object(pr->handle, "_PTC", शून्य, &buffer);
	अगर (ACPI_FAILURE(status)) अणु
		अगर (status != AE_NOT_FOUND)
			acpi_evaluation_failure_warn(pr->handle, "_PTC", status);

		वापस -ENODEV;
	पूर्ण

	ptc = (जोड़ acpi_object *)buffer.poपूर्णांकer;
	अगर (!ptc || (ptc->type != ACPI_TYPE_PACKAGE)
	    || (ptc->package.count != 2)) अणु
		prपूर्णांकk(KERN_ERR PREFIX "Invalid _PTC data\n");
		result = -EFAULT;
		जाओ end;
	पूर्ण

	/*
	 * control_रेजिस्टर
	 */

	obj = ptc->package.elements[0];

	अगर ((obj.type != ACPI_TYPE_BUFFER)
	    || (obj.buffer.length < माप(काष्ठा acpi_ptc_रेजिस्टर))
	    || (obj.buffer.poपूर्णांकer == शून्य)) अणु
		prपूर्णांकk(KERN_ERR PREFIX
		       "Invalid _PTC data (control_register)\n");
		result = -EFAULT;
		जाओ end;
	पूर्ण
	स_नकल(&pr->throttling.control_रेजिस्टर, obj.buffer.poपूर्णांकer,
	       माप(काष्ठा acpi_ptc_रेजिस्टर));

	/*
	 * status_रेजिस्टर
	 */

	obj = ptc->package.elements[1];

	अगर ((obj.type != ACPI_TYPE_BUFFER)
	    || (obj.buffer.length < माप(काष्ठा acpi_ptc_रेजिस्टर))
	    || (obj.buffer.poपूर्णांकer == शून्य)) अणु
		prपूर्णांकk(KERN_ERR PREFIX "Invalid _PTC data (status_register)\n");
		result = -EFAULT;
		जाओ end;
	पूर्ण

	स_नकल(&pr->throttling.status_रेजिस्टर, obj.buffer.poपूर्णांकer,
	       माप(काष्ठा acpi_ptc_रेजिस्टर));

	throttling = &pr->throttling;

	अगर ((throttling->control_रेजिस्टर.bit_width +
		throttling->control_रेजिस्टर.bit_offset) > 32) अणु
		prपूर्णांकk(KERN_ERR PREFIX "Invalid _PTC control register\n");
		result = -EFAULT;
		जाओ end;
	पूर्ण

	अगर ((throttling->status_रेजिस्टर.bit_width +
		throttling->status_रेजिस्टर.bit_offset) > 32) अणु
		prपूर्णांकk(KERN_ERR PREFIX "Invalid _PTC status register\n");
		result = -EFAULT;
		जाओ end;
	पूर्ण

      end:
	kमुक्त(buffer.poपूर्णांकer);

	वापस result;
पूर्ण

/*
 * _TSS - Throttling Supported States
 */
अटल पूर्णांक acpi_processor_get_throttling_states(काष्ठा acpi_processor *pr)
अणु
	पूर्णांक result = 0;
	acpi_status status = AE_OK;
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	काष्ठा acpi_buffer क्रमmat = अणु माप("NNNNN"), "NNNNN" पूर्ण;
	काष्ठा acpi_buffer state = अणु 0, शून्य पूर्ण;
	जोड़ acpi_object *tss = शून्य;
	पूर्णांक i;

	status = acpi_evaluate_object(pr->handle, "_TSS", शून्य, &buffer);
	अगर (ACPI_FAILURE(status)) अणु
		अगर (status != AE_NOT_FOUND)
			acpi_evaluation_failure_warn(pr->handle, "_TSS", status);

		वापस -ENODEV;
	पूर्ण

	tss = buffer.poपूर्णांकer;
	अगर (!tss || (tss->type != ACPI_TYPE_PACKAGE)) अणु
		prपूर्णांकk(KERN_ERR PREFIX "Invalid _TSS data\n");
		result = -EFAULT;
		जाओ end;
	पूर्ण

	acpi_handle_debug(pr->handle, "Found %d throttling states\n",
			  tss->package.count);

	pr->throttling.state_count = tss->package.count;
	pr->throttling.states_tss =
	    kदो_स्मृति_array(tss->package.count,
			  माप(काष्ठा acpi_processor_tx_tss),
			  GFP_KERNEL);
	अगर (!pr->throttling.states_tss) अणु
		result = -ENOMEM;
		जाओ end;
	पूर्ण

	क्रम (i = 0; i < pr->throttling.state_count; i++) अणु

		काष्ठा acpi_processor_tx_tss *tx =
		    (काष्ठा acpi_processor_tx_tss *)&(pr->throttling.
						      states_tss[i]);

		state.length = माप(काष्ठा acpi_processor_tx_tss);
		state.poपूर्णांकer = tx;

		acpi_handle_debug(pr->handle, "Extracting state %d\n", i);

		status = acpi_extract_package(&(tss->package.elements[i]),
					      &क्रमmat, &state);
		अगर (ACPI_FAILURE(status)) अणु
			acpi_handle_warn(pr->handle, "Invalid _TSS data: %s\n",
					 acpi_क्रमmat_exception(status));
			result = -EFAULT;
			kमुक्त(pr->throttling.states_tss);
			जाओ end;
		पूर्ण

		अगर (!tx->freqpercentage) अणु
			prपूर्णांकk(KERN_ERR PREFIX
			       "Invalid _TSS data: freq is zero\n");
			result = -EFAULT;
			kमुक्त(pr->throttling.states_tss);
			जाओ end;
		पूर्ण
	पूर्ण

      end:
	kमुक्त(buffer.poपूर्णांकer);

	वापस result;
पूर्ण

/*
 * _TSD - T-State Dependencies
 */
अटल पूर्णांक acpi_processor_get_tsd(काष्ठा acpi_processor *pr)
अणु
	पूर्णांक result = 0;
	acpi_status status = AE_OK;
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	काष्ठा acpi_buffer क्रमmat = अणु माप("NNNNN"), "NNNNN" पूर्ण;
	काष्ठा acpi_buffer state = अणु 0, शून्य पूर्ण;
	जोड़ acpi_object *tsd = शून्य;
	काष्ठा acpi_tsd_package *pकरोमुख्य;
	काष्ठा acpi_processor_throttling *pthrottling;

	pthrottling = &pr->throttling;
	pthrottling->tsd_valid_flag = 0;

	status = acpi_evaluate_object(pr->handle, "_TSD", शून्य, &buffer);
	अगर (ACPI_FAILURE(status)) अणु
		अगर (status != AE_NOT_FOUND)
			acpi_evaluation_failure_warn(pr->handle, "_TSD", status);

		वापस -ENODEV;
	पूर्ण

	tsd = buffer.poपूर्णांकer;
	अगर (!tsd || (tsd->type != ACPI_TYPE_PACKAGE)) अणु
		prपूर्णांकk(KERN_ERR PREFIX "Invalid _TSD data\n");
		result = -EFAULT;
		जाओ end;
	पूर्ण

	अगर (tsd->package.count != 1) अणु
		prपूर्णांकk(KERN_ERR PREFIX "Invalid _TSD data\n");
		result = -EFAULT;
		जाओ end;
	पूर्ण

	pकरोमुख्य = &(pr->throttling.करोमुख्य_info);

	state.length = माप(काष्ठा acpi_tsd_package);
	state.poपूर्णांकer = pकरोमुख्य;

	status = acpi_extract_package(&(tsd->package.elements[0]),
				      &क्रमmat, &state);
	अगर (ACPI_FAILURE(status)) अणु
		prपूर्णांकk(KERN_ERR PREFIX "Invalid _TSD data\n");
		result = -EFAULT;
		जाओ end;
	पूर्ण

	अगर (pकरोमुख्य->num_entries != ACPI_TSD_REV0_ENTRIES) अणु
		prपूर्णांकk(KERN_ERR PREFIX "Unknown _TSD:num_entries\n");
		result = -EFAULT;
		जाओ end;
	पूर्ण

	अगर (pकरोमुख्य->revision != ACPI_TSD_REV0_REVISION) अणु
		prपूर्णांकk(KERN_ERR PREFIX "Unknown _TSD:revision\n");
		result = -EFAULT;
		जाओ end;
	पूर्ण

	pthrottling = &pr->throttling;
	pthrottling->tsd_valid_flag = 1;
	pthrottling->shared_type = pकरोमुख्य->coord_type;
	cpumask_set_cpu(pr->id, pthrottling->shared_cpu_map);
	/*
	 * If the coordination type is not defined in ACPI spec,
	 * the tsd_valid_flag will be clear and coordination type
	 * will be क्रमecd as DOMAIN_COORD_TYPE_SW_ALL.
	 */
	अगर (pकरोमुख्य->coord_type != DOMAIN_COORD_TYPE_SW_ALL &&
		pकरोमुख्य->coord_type != DOMAIN_COORD_TYPE_SW_ANY &&
		pकरोमुख्य->coord_type != DOMAIN_COORD_TYPE_HW_ALL) अणु
		pthrottling->tsd_valid_flag = 0;
		pthrottling->shared_type = DOMAIN_COORD_TYPE_SW_ALL;
	पूर्ण

      end:
	kमुक्त(buffer.poपूर्णांकer);
	वापस result;
पूर्ण

/* --------------------------------------------------------------------------
                              Throttling Control
   -------------------------------------------------------------------------- */
अटल पूर्णांक acpi_processor_get_throttling_fadt(काष्ठा acpi_processor *pr)
अणु
	पूर्णांक state = 0;
	u32 value = 0;
	u32 duty_mask = 0;
	u32 duty_value = 0;

	अगर (!pr)
		वापस -EINVAL;

	अगर (!pr->flags.throttling)
		वापस -ENODEV;

	/*
	 * We करोn't care about error वापसs - we just try to mark
	 * these reserved so that nobody अन्यथा is confused पूर्णांकo thinking
	 * that this region might be unused..
	 *
	 * (In particular, allocating the IO range क्रम Cardbus)
	 */
	request_region(pr->throttling.address, 6, "ACPI CPU throttle");

	pr->throttling.state = 0;

	duty_mask = pr->throttling.state_count - 1;

	duty_mask <<= pr->throttling.duty_offset;

	local_irq_disable();

	value = inl(pr->throttling.address);

	/*
	 * Compute the current throttling state when throttling is enabled
	 * (bit 4 is on).
	 */
	अगर (value & 0x10) अणु
		duty_value = value & duty_mask;
		duty_value >>= pr->throttling.duty_offset;

		अगर (duty_value)
			state = pr->throttling.state_count - duty_value;
	पूर्ण

	pr->throttling.state = state;

	local_irq_enable();

	acpi_handle_debug(pr->handle,
			  "Throttling state is T%d (%d%% throttling applied)\n",
			  state, pr->throttling.states[state].perक्रमmance);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_X86
अटल पूर्णांक acpi_throttling_rdmsr(u64 *value)
अणु
	u64 msr_high, msr_low;
	u64 msr = 0;
	पूर्णांक ret = -1;

	अगर ((this_cpu_पढ़ो(cpu_info.x86_venकरोr) != X86_VENDOR_INTEL) ||
		!this_cpu_has(X86_FEATURE_ACPI)) अणु
		prपूर्णांकk(KERN_ERR PREFIX
			"HARDWARE addr space,NOT supported yet\n");
	पूर्ण अन्यथा अणु
		msr_low = 0;
		msr_high = 0;
		rdmsr_safe(MSR_IA32_THERM_CONTROL,
			(u32 *)&msr_low , (u32 *) &msr_high);
		msr = (msr_high << 32) | msr_low;
		*value = (u64) msr;
		ret = 0;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक acpi_throttling_wrmsr(u64 value)
अणु
	पूर्णांक ret = -1;
	u64 msr;

	अगर ((this_cpu_पढ़ो(cpu_info.x86_venकरोr) != X86_VENDOR_INTEL) ||
		!this_cpu_has(X86_FEATURE_ACPI)) अणु
		prपूर्णांकk(KERN_ERR PREFIX
			"HARDWARE addr space,NOT supported yet\n");
	पूर्ण अन्यथा अणु
		msr = value;
		wrmsr_safe(MSR_IA32_THERM_CONTROL,
			msr & 0xffffffff, msr >> 32);
		ret = 0;
	पूर्ण
	वापस ret;
पूर्ण
#अन्यथा
अटल पूर्णांक acpi_throttling_rdmsr(u64 *value)
अणु
	prपूर्णांकk(KERN_ERR PREFIX
		"HARDWARE addr space,NOT supported yet\n");
	वापस -1;
पूर्ण

अटल पूर्णांक acpi_throttling_wrmsr(u64 value)
अणु
	prपूर्णांकk(KERN_ERR PREFIX
		"HARDWARE addr space,NOT supported yet\n");
	वापस -1;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक acpi_पढ़ो_throttling_status(काष्ठा acpi_processor *pr,
					u64 *value)
अणु
	u32 bit_width, bit_offset;
	u32 ptc_value;
	u64 ptc_mask;
	काष्ठा acpi_processor_throttling *throttling;
	पूर्णांक ret = -1;

	throttling = &pr->throttling;
	चयन (throttling->status_रेजिस्टर.space_id) अणु
	हाल ACPI_ADR_SPACE_SYSTEM_IO:
		bit_width = throttling->status_रेजिस्टर.bit_width;
		bit_offset = throttling->status_रेजिस्टर.bit_offset;

		acpi_os_पढ़ो_port((acpi_io_address) throttling->status_रेजिस्टर.
				  address, &ptc_value,
				  (u32) (bit_width + bit_offset));
		ptc_mask = (1 << bit_width) - 1;
		*value = (u64) ((ptc_value >> bit_offset) & ptc_mask);
		ret = 0;
		अवरोध;
	हाल ACPI_ADR_SPACE_FIXED_HARDWARE:
		ret = acpi_throttling_rdmsr(value);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR PREFIX "Unknown addr space %d\n",
		       (u32) (throttling->status_रेजिस्टर.space_id));
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक acpi_ग_लिखो_throttling_state(काष्ठा acpi_processor *pr,
				u64 value)
अणु
	u32 bit_width, bit_offset;
	u64 ptc_value;
	u64 ptc_mask;
	काष्ठा acpi_processor_throttling *throttling;
	पूर्णांक ret = -1;

	throttling = &pr->throttling;
	चयन (throttling->control_रेजिस्टर.space_id) अणु
	हाल ACPI_ADR_SPACE_SYSTEM_IO:
		bit_width = throttling->control_रेजिस्टर.bit_width;
		bit_offset = throttling->control_रेजिस्टर.bit_offset;
		ptc_mask = (1 << bit_width) - 1;
		ptc_value = value & ptc_mask;

		acpi_os_ग_लिखो_port((acpi_io_address) throttling->
					control_रेजिस्टर.address,
					(u32) (ptc_value << bit_offset),
					(u32) (bit_width + bit_offset));
		ret = 0;
		अवरोध;
	हाल ACPI_ADR_SPACE_FIXED_HARDWARE:
		ret = acpi_throttling_wrmsr(value);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR PREFIX "Unknown addr space %d\n",
		       (u32) (throttling->control_रेजिस्टर.space_id));
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक acpi_get_throttling_state(काष्ठा acpi_processor *pr,
				u64 value)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pr->throttling.state_count; i++) अणु
		काष्ठा acpi_processor_tx_tss *tx =
		    (काष्ठा acpi_processor_tx_tss *)&(pr->throttling.
						      states_tss[i]);
		अगर (tx->control == value)
			वापस i;
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक acpi_get_throttling_value(काष्ठा acpi_processor *pr,
			पूर्णांक state, u64 *value)
अणु
	पूर्णांक ret = -1;

	अगर (state >= 0 && state <= pr->throttling.state_count) अणु
		काष्ठा acpi_processor_tx_tss *tx =
		    (काष्ठा acpi_processor_tx_tss *)&(pr->throttling.
						      states_tss[state]);
		*value = tx->control;
		ret = 0;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक acpi_processor_get_throttling_ptc(काष्ठा acpi_processor *pr)
अणु
	पूर्णांक state = 0;
	पूर्णांक ret;
	u64 value;

	अगर (!pr)
		वापस -EINVAL;

	अगर (!pr->flags.throttling)
		वापस -ENODEV;

	pr->throttling.state = 0;

	value = 0;
	ret = acpi_पढ़ो_throttling_status(pr, &value);
	अगर (ret >= 0) अणु
		state = acpi_get_throttling_state(pr, value);
		अगर (state == -1) अणु
			acpi_handle_debug(pr->handle,
					  "Invalid throttling state, reset\n");
			state = 0;
			ret = __acpi_processor_set_throttling(pr, state, true,
							      true);
			अगर (ret)
				वापस ret;
		पूर्ण
		pr->throttling.state = state;
	पूर्ण

	वापस 0;
पूर्ण

अटल दीर्घ __acpi_processor_get_throttling(व्योम *data)
अणु
	काष्ठा acpi_processor *pr = data;

	वापस pr->throttling.acpi_processor_get_throttling(pr);
पूर्ण

अटल पूर्णांक acpi_processor_get_throttling(काष्ठा acpi_processor *pr)
अणु
	अगर (!pr)
		वापस -EINVAL;

	अगर (!pr->flags.throttling)
		वापस -ENODEV;

	/*
	 * This is either called from the CPU hotplug callback of
	 * processor_driver or via the ACPI probe function. In the latter
	 * हाल the CPU is not guaranteed to be online. Both call sites are
	 * रक्षित against CPU hotplug.
	 */
	अगर (!cpu_online(pr->id))
		वापस -ENODEV;

	वापस call_on_cpu(pr->id, __acpi_processor_get_throttling, pr, false);
पूर्ण

अटल पूर्णांक acpi_processor_get_fadt_info(काष्ठा acpi_processor *pr)
अणु
	पूर्णांक i, step;

	अगर (!pr->throttling.address) अणु
		acpi_handle_debug(pr->handle, "No throttling register\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (!pr->throttling.duty_width) अणु
		acpi_handle_debug(pr->handle, "No throttling states\n");
		वापस -EINVAL;
	पूर्ण
	/* TBD: Support duty_cycle values that span bit 4. */
	अन्यथा अगर ((pr->throttling.duty_offset + pr->throttling.duty_width) > 4) अणु
		prपूर्णांकk(KERN_WARNING PREFIX "duty_cycle spans bit 4\n");
		वापस -EINVAL;
	पूर्ण

	pr->throttling.state_count = 1 << acpi_gbl_FADT.duty_width;

	/*
	 * Compute state values. Note that throttling displays a linear घातer
	 * perक्रमmance relationship (at 50% perक्रमmance the CPU will consume
	 * 50% घातer).  Values are in 1/10th of a percent to preserve accuracy.
	 */

	step = (1000 / pr->throttling.state_count);

	क्रम (i = 0; i < pr->throttling.state_count; i++) अणु
		pr->throttling.states[i].perक्रमmance = 1000 - step * i;
		pr->throttling.states[i].घातer = 1000 - step * i;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_processor_set_throttling_fadt(काष्ठा acpi_processor *pr,
					      पूर्णांक state, bool क्रमce)
अणु
	u32 value = 0;
	u32 duty_mask = 0;
	u32 duty_value = 0;

	अगर (!pr)
		वापस -EINVAL;

	अगर ((state < 0) || (state > (pr->throttling.state_count - 1)))
		वापस -EINVAL;

	अगर (!pr->flags.throttling)
		वापस -ENODEV;

	अगर (!क्रमce && (state == pr->throttling.state))
		वापस 0;

	अगर (state < pr->throttling_platक्रमm_limit)
		वापस -EPERM;
	/*
	 * Calculate the duty_value and duty_mask.
	 */
	अगर (state) अणु
		duty_value = pr->throttling.state_count - state;

		duty_value <<= pr->throttling.duty_offset;

		/* Used to clear all duty_value bits */
		duty_mask = pr->throttling.state_count - 1;

		duty_mask <<= acpi_gbl_FADT.duty_offset;
		duty_mask = ~duty_mask;
	पूर्ण

	local_irq_disable();

	/*
	 * Disable throttling by writing a 0 to bit 4.  Note that we must
	 * turn it off beक्रमe you can change the duty_value.
	 */
	value = inl(pr->throttling.address);
	अगर (value & 0x10) अणु
		value &= 0xFFFFFFEF;
		outl(value, pr->throttling.address);
	पूर्ण

	/*
	 * Write the new duty_value and then enable throttling.  Note
	 * that a state value of 0 leaves throttling disabled.
	 */
	अगर (state) अणु
		value &= duty_mask;
		value |= duty_value;
		outl(value, pr->throttling.address);

		value |= 0x00000010;
		outl(value, pr->throttling.address);
	पूर्ण

	pr->throttling.state = state;

	local_irq_enable();

	acpi_handle_debug(pr->handle,
			  "Throttling state set to T%d (%d%%)\n", state,
			  (pr->throttling.states[state].perक्रमmance ? pr->
			   throttling.states[state].perक्रमmance / 10 : 0));

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_processor_set_throttling_ptc(काष्ठा acpi_processor *pr,
					     पूर्णांक state, bool क्रमce)
अणु
	पूर्णांक ret;
	u64 value;

	अगर (!pr)
		वापस -EINVAL;

	अगर ((state < 0) || (state > (pr->throttling.state_count - 1)))
		वापस -EINVAL;

	अगर (!pr->flags.throttling)
		वापस -ENODEV;

	अगर (!क्रमce && (state == pr->throttling.state))
		वापस 0;

	अगर (state < pr->throttling_platक्रमm_limit)
		वापस -EPERM;

	value = 0;
	ret = acpi_get_throttling_value(pr, state, &value);
	अगर (ret >= 0) अणु
		acpi_ग_लिखो_throttling_state(pr, value);
		pr->throttling.state = state;
	पूर्ण

	वापस 0;
पूर्ण

अटल दीर्घ acpi_processor_throttling_fn(व्योम *data)
अणु
	काष्ठा acpi_processor_throttling_arg *arg = data;
	काष्ठा acpi_processor *pr = arg->pr;

	वापस pr->throttling.acpi_processor_set_throttling(pr,
			arg->target_state, arg->क्रमce);
पूर्ण

अटल पूर्णांक __acpi_processor_set_throttling(काष्ठा acpi_processor *pr,
					   पूर्णांक state, bool क्रमce, bool direct)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक i;
	काष्ठा acpi_processor *match_pr;
	काष्ठा acpi_processor_throttling *p_throttling;
	काष्ठा acpi_processor_throttling_arg arg;
	काष्ठा throttling_tstate t_state;

	अगर (!pr)
		वापस -EINVAL;

	अगर (!pr->flags.throttling)
		वापस -ENODEV;

	अगर ((state < 0) || (state > (pr->throttling.state_count - 1)))
		वापस -EINVAL;

	अगर (cpu_is_offline(pr->id)) अणु
		/*
		 * the cpu poपूर्णांकed by pr->id is offline. Unnecessary to change
		 * the throttling state any more.
		 */
		वापस -ENODEV;
	पूर्ण

	t_state.target_state = state;
	p_throttling = &(pr->throttling);

	/*
	 * The throttling notअगरier will be called क्रम every
	 * affected cpu in order to get one proper T-state.
	 * The notअगरier event is THROTTLING_PRECHANGE.
	 */
	क्रम_each_cpu_and(i, cpu_online_mask, p_throttling->shared_cpu_map) अणु
		t_state.cpu = i;
		acpi_processor_throttling_notअगरier(THROTTLING_PRECHANGE,
							&t_state);
	पूर्ण
	/*
	 * The function of acpi_processor_set_throttling will be called
	 * to चयन T-state. If the coordination type is SW_ALL or HW_ALL,
	 * it is necessary to call it क्रम every affected cpu. Otherwise
	 * it can be called only क्रम the cpu poपूर्णांकed by pr.
	 */
	अगर (p_throttling->shared_type == DOMAIN_COORD_TYPE_SW_ANY) अणु
		arg.pr = pr;
		arg.target_state = state;
		arg.क्रमce = क्रमce;
		ret = call_on_cpu(pr->id, acpi_processor_throttling_fn, &arg,
				  direct);
	पूर्ण अन्यथा अणु
		/*
		 * When the T-state coordination is SW_ALL or HW_ALL,
		 * it is necessary to set T-state क्रम every affected
		 * cpus.
		 */
		क्रम_each_cpu_and(i, cpu_online_mask,
		    p_throttling->shared_cpu_map) अणु
			match_pr = per_cpu(processors, i);
			/*
			 * If the poपूर्णांकer is invalid, we will report the
			 * error message and जारी.
			 */
			अगर (!match_pr) अणु
				acpi_handle_debug(pr->handle,
					"Invalid Pointer for CPU %d\n", i);
				जारी;
			पूर्ण
			/*
			 * If the throttling control is unsupported on CPU i,
			 * we will report the error message and जारी.
			 */
			अगर (!match_pr->flags.throttling) अणु
				acpi_handle_debug(pr->handle,
					"Throttling Control unsupported on CPU %d\n", i);
				जारी;
			पूर्ण

			arg.pr = match_pr;
			arg.target_state = state;
			arg.क्रमce = क्रमce;
			ret = call_on_cpu(pr->id, acpi_processor_throttling_fn,
					  &arg, direct);
		पूर्ण
	पूर्ण
	/*
	 * After the set_throttling is called, the
	 * throttling notअगरier is called क्रम every
	 * affected cpu to update the T-states.
	 * The notअगरier event is THROTTLING_POSTCHANGE
	 */
	क्रम_each_cpu_and(i, cpu_online_mask, p_throttling->shared_cpu_map) अणु
		t_state.cpu = i;
		acpi_processor_throttling_notअगरier(THROTTLING_POSTCHANGE,
							&t_state);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक acpi_processor_set_throttling(काष्ठा acpi_processor *pr, पूर्णांक state,
				  bool क्रमce)
अणु
	वापस __acpi_processor_set_throttling(pr, state, क्रमce, false);
पूर्ण

पूर्णांक acpi_processor_get_throttling_info(काष्ठा acpi_processor *pr)
अणु
	पूर्णांक result = 0;
	काष्ठा acpi_processor_throttling *pthrottling;

	acpi_handle_debug(pr->handle,
			  "pblk_address[0x%08x] duty_offset[%d] duty_width[%d]\n",
			  pr->throttling.address,
			  pr->throttling.duty_offset,
			  pr->throttling.duty_width);

	/*
	 * Evaluate _PTC, _TSS and _TPC
	 * They must all be present or none of them can be used.
	 */
	अगर (acpi_processor_get_throttling_control(pr) ||
		acpi_processor_get_throttling_states(pr) ||
		acpi_processor_get_platक्रमm_limit(pr))
	अणु
		pr->throttling.acpi_processor_get_throttling =
		    &acpi_processor_get_throttling_fadt;
		pr->throttling.acpi_processor_set_throttling =
		    &acpi_processor_set_throttling_fadt;
		अगर (acpi_processor_get_fadt_info(pr))
			वापस 0;
	पूर्ण अन्यथा अणु
		pr->throttling.acpi_processor_get_throttling =
		    &acpi_processor_get_throttling_ptc;
		pr->throttling.acpi_processor_set_throttling =
		    &acpi_processor_set_throttling_ptc;
	पूर्ण

	/*
	 * If TSD package क्रम one CPU can't be parsed successfully, it means
	 * that this CPU will have no coordination with other CPUs.
	 */
	अगर (acpi_processor_get_tsd(pr)) अणु
		pthrottling = &pr->throttling;
		pthrottling->tsd_valid_flag = 0;
		cpumask_set_cpu(pr->id, pthrottling->shared_cpu_map);
		pthrottling->shared_type = DOMAIN_COORD_TYPE_SW_ALL;
	पूर्ण

	/*
	 * PIIX4 Errata: We करोn't support throttling on the original PIIX4.
	 * This shouldn't be an issue as few (अगर any) mobile प्रणालीs ever
	 * used this part.
	 */
	अगर (errata.piix4.throttle) अणु
		acpi_handle_debug(pr->handle,
				  "Throttling not supported on PIIX4 A- or B-step\n");
		वापस 0;
	पूर्ण

	acpi_handle_debug(pr->handle, "Found %d throttling states\n",
			  pr->throttling.state_count);

	pr->flags.throttling = 1;

	/*
	 * Disable throttling (अगर enabled).  We'll let subsequent policy (e.g.
	 * thermal) decide to lower perक्रमmance अगर it so chooses, but क्रम now
	 * we'll crank up the speed.
	 */

	result = acpi_processor_get_throttling(pr);
	अगर (result)
		जाओ end;

	अगर (pr->throttling.state) अणु
		acpi_handle_debug(pr->handle,
				  "Disabling throttling (was T%d)\n",
				  pr->throttling.state);
		result = acpi_processor_set_throttling(pr, 0, false);
		अगर (result)
			जाओ end;
	पूर्ण

      end:
	अगर (result)
		pr->flags.throttling = 0;

	वापस result;
पूर्ण

