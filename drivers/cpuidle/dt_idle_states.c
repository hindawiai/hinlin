<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * DT idle states parsing code.
 *
 * Copyright (C) 2014 ARM Ltd.
 * Author: Lorenzo Pieralisi <lorenzo.pieralisi@arm.com>
 */

#घोषणा pr_fmt(fmt) "DT idle-states: " fmt

#समावेश <linux/cpuidle.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#समावेश "dt_idle_states.h"

अटल पूर्णांक init_state_node(काष्ठा cpuidle_state *idle_state,
			   स्थिर काष्ठा of_device_id *match_id,
			   काष्ठा device_node *state_node)
अणु
	पूर्णांक err;
	स्थिर अक्षर *desc;

	/*
	 * CPUidle drivers are expected to initialize the स्थिर व्योम *data
	 * poपूर्णांकer of the passed in काष्ठा of_device_id array to the idle
	 * state enter function.
	 */
	idle_state->enter = match_id->data;
	/*
	 * Since this is not a "coupled" state, it's safe to assume पूर्णांकerrupts
	 * won't be enabled when it निकासs allowing the tick to be frozen
	 * safely. So enter() can be also enter_s2idle() callback.
	 */
	idle_state->enter_s2idle = match_id->data;

	err = of_property_पढ़ो_u32(state_node, "wakeup-latency-us",
				   &idle_state->निकास_latency);
	अगर (err) अणु
		u32 entry_latency, निकास_latency;

		err = of_property_पढ़ो_u32(state_node, "entry-latency-us",
					   &entry_latency);
		अगर (err) अणु
			pr_debug(" * %pOF missing entry-latency-us property\n",
				 state_node);
			वापस -EINVAL;
		पूर्ण

		err = of_property_पढ़ो_u32(state_node, "exit-latency-us",
					   &निकास_latency);
		अगर (err) अणु
			pr_debug(" * %pOF missing exit-latency-us property\n",
				 state_node);
			वापस -EINVAL;
		पूर्ण
		/*
		 * If wakeup-latency-us is missing, शेष to entry+निकास
		 * latencies as defined in idle states bindings
		 */
		idle_state->निकास_latency = entry_latency + निकास_latency;
	पूर्ण

	err = of_property_पढ़ो_u32(state_node, "min-residency-us",
				   &idle_state->target_residency);
	अगर (err) अणु
		pr_debug(" * %pOF missing min-residency-us property\n",
			     state_node);
		वापस -EINVAL;
	पूर्ण

	err = of_property_पढ़ो_string(state_node, "idle-state-name", &desc);
	अगर (err)
		desc = state_node->name;

	idle_state->flags = 0;
	अगर (of_property_पढ़ो_bool(state_node, "local-timer-stop"))
		idle_state->flags |= CPUIDLE_FLAG_TIMER_STOP;
	/*
	 * TODO:
	 *	replace with kstrdup and poपूर्णांकer assignment when name
	 *	and desc become string poपूर्णांकers
	 */
	म_नकलन(idle_state->name, state_node->name, CPUIDLE_NAME_LEN - 1);
	म_नकलन(idle_state->desc, desc, CPUIDLE_DESC_LEN - 1);
	वापस 0;
पूर्ण

/*
 * Check that the idle state is unअगरorm across all CPUs in the CPUidle driver
 * cpumask
 */
अटल bool idle_state_valid(काष्ठा device_node *state_node, अचिन्हित पूर्णांक idx,
			     स्थिर cpumask_t *cpumask)
अणु
	पूर्णांक cpu;
	काष्ठा device_node *cpu_node, *curr_state_node;
	bool valid = true;

	/*
	 * Compare idle state phandles क्रम index idx on all CPUs in the
	 * CPUidle driver cpumask. Start from next logical cpu following
	 * cpumask_first(cpumask) since that's the CPU state_node was
	 * retrieved from. If a mismatch is found bail out straight
	 * away since we certainly hit a firmware misconfiguration.
	 */
	क्रम (cpu = cpumask_next(cpumask_first(cpumask), cpumask);
	     cpu < nr_cpu_ids; cpu = cpumask_next(cpu, cpumask)) अणु
		cpu_node = of_cpu_device_node_get(cpu);
		curr_state_node = of_get_cpu_state_node(cpu_node, idx);
		अगर (state_node != curr_state_node)
			valid = false;

		of_node_put(curr_state_node);
		of_node_put(cpu_node);
		अगर (!valid)
			अवरोध;
	पूर्ण

	वापस valid;
पूर्ण

/**
 * dt_init_idle_driver() - Parse the DT idle states and initialize the
 *			   idle driver states array
 * @drv:	  Poपूर्णांकer to CPU idle driver to be initialized
 * @matches:	  Array of of_device_id match काष्ठाures to search in क्रम
 *		  compatible idle state nodes. The data poपूर्णांकer क्रम each valid
 *		  काष्ठा of_device_id entry in the matches array must poपूर्णांक to
 *		  a function with the following signature, that corresponds to
 *		  the CPUidle state enter function signature:
 *
 *		  पूर्णांक (*)(काष्ठा cpuidle_device *dev,
 *			  काष्ठा cpuidle_driver *drv,
 *			  पूर्णांक index);
 *
 * @start_idx:    First idle state index to be initialized
 *
 * If DT idle states are detected and are valid the state count and states
 * array entries in the cpuidle driver are initialized accordingly starting
 * from index start_idx.
 *
 * Return: number of valid DT idle states parsed, <0 on failure
 */
पूर्णांक dt_init_idle_driver(काष्ठा cpuidle_driver *drv,
			स्थिर काष्ठा of_device_id *matches,
			अचिन्हित पूर्णांक start_idx)
अणु
	काष्ठा cpuidle_state *idle_state;
	काष्ठा device_node *state_node, *cpu_node;
	स्थिर काष्ठा of_device_id *match_id;
	पूर्णांक i, err = 0;
	स्थिर cpumask_t *cpumask;
	अचिन्हित पूर्णांक state_idx = start_idx;

	अगर (state_idx >= CPUIDLE_STATE_MAX)
		वापस -EINVAL;
	/*
	 * We get the idle states क्रम the first logical cpu in the
	 * driver mask (or cpu_possible_mask अगर the driver cpumask is not set)
	 * and we check through idle_state_valid() अगर they are unअगरorm
	 * across CPUs, otherwise we hit a firmware misconfiguration.
	 */
	cpumask = drv->cpumask ? : cpu_possible_mask;
	cpu_node = of_cpu_device_node_get(cpumask_first(cpumask));

	क्रम (i = 0; ; i++) अणु
		state_node = of_get_cpu_state_node(cpu_node, i);
		अगर (!state_node)
			अवरोध;

		match_id = of_match_node(matches, state_node);
		अगर (!match_id) अणु
			err = -ENODEV;
			अवरोध;
		पूर्ण

		अगर (!of_device_is_available(state_node)) अणु
			of_node_put(state_node);
			जारी;
		पूर्ण

		अगर (!idle_state_valid(state_node, i, cpumask)) अणु
			pr_warn("%pOF idle state not valid, bailing out\n",
				state_node);
			err = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (state_idx == CPUIDLE_STATE_MAX) अणु
			pr_warn("State index reached static CPU idle driver states array size\n");
			अवरोध;
		पूर्ण

		idle_state = &drv->states[state_idx++];
		err = init_state_node(idle_state, match_id, state_node);
		अगर (err) अणु
			pr_err("Parsing idle state node %pOF failed with err %d\n",
			       state_node, err);
			err = -EINVAL;
			अवरोध;
		पूर्ण
		of_node_put(state_node);
	पूर्ण

	of_node_put(state_node);
	of_node_put(cpu_node);
	अगर (err)
		वापस err;
	/*
	 * Update the driver state count only अगर some valid DT idle states
	 * were detected
	 */
	अगर (i)
		drv->state_count = state_idx;

	/*
	 * Return the number of present and valid DT idle states, which can
	 * also be 0 on platक्रमms with missing DT idle states or legacy DT
	 * configuration predating the DT idle states bindings.
	 */
	वापस i;
पूर्ण
EXPORT_SYMBOL_GPL(dt_init_idle_driver);
