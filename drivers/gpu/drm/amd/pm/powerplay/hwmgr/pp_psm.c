<शैली गुरु>
/*
 * Copyright 2017 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश "pp_psm.h"

पूर्णांक psm_init_घातer_state_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक table_entries;
	काष्ठा pp_घातer_state *state;
	पूर्णांक size;

	अगर (hwmgr->hwmgr_func->get_num_of_pp_table_entries == शून्य)
		वापस 0;

	अगर (hwmgr->hwmgr_func->get_घातer_state_size == शून्य)
		वापस 0;

	hwmgr->num_ps = table_entries = hwmgr->hwmgr_func->get_num_of_pp_table_entries(hwmgr);

	hwmgr->ps_size = size = hwmgr->hwmgr_func->get_घातer_state_size(hwmgr) +
					  माप(काष्ठा pp_घातer_state);

	अगर (table_entries == 0 || size == 0) अणु
		pr_warn("Please check whether power state management is supported on this asic\n");
		वापस 0;
	पूर्ण

	hwmgr->ps = kसुस्मृति(table_entries, size, GFP_KERNEL);
	अगर (hwmgr->ps == शून्य)
		वापस -ENOMEM;

	hwmgr->request_ps = kzalloc(size, GFP_KERNEL);
	अगर (hwmgr->request_ps == शून्य) अणु
		kमुक्त(hwmgr->ps);
		hwmgr->ps = शून्य;
		वापस -ENOMEM;
	पूर्ण

	hwmgr->current_ps = kzalloc(size, GFP_KERNEL);
	अगर (hwmgr->current_ps == शून्य) अणु
		kमुक्त(hwmgr->request_ps);
		kमुक्त(hwmgr->ps);
		hwmgr->request_ps = शून्य;
		hwmgr->ps = शून्य;
		वापस -ENOMEM;
	पूर्ण

	state = hwmgr->ps;

	क्रम (i = 0; i < table_entries; i++) अणु
		result = hwmgr->hwmgr_func->get_pp_table_entry(hwmgr, i, state);
		अगर (result) अणु
			kमुक्त(hwmgr->request_ps);
			kमुक्त(hwmgr->ps);
			hwmgr->request_ps = शून्य;
			hwmgr->ps = शून्य;
			वापस -EINVAL;
		पूर्ण

		अगर (state->classअगरication.flags & PP_StateClassअगरicationFlag_Boot) अणु
			hwmgr->boot_ps = state;
			स_नकल(hwmgr->current_ps, state, size);
			स_नकल(hwmgr->request_ps, state, size);
		पूर्ण

		state->id = i + 1; /* asचिन्हित unique num क्रम every घातer state id */

		अगर (state->classअगरication.flags & PP_StateClassअगरicationFlag_Uvd)
			hwmgr->uvd_ps = state;
		state = (काष्ठा pp_घातer_state *)((अचिन्हित दीर्घ)state + size);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक psm_fini_घातer_state_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (hwmgr == शून्य)
		वापस -EINVAL;

	अगर (!hwmgr->ps)
		वापस 0;

	kमुक्त(hwmgr->current_ps);
	kमुक्त(hwmgr->request_ps);
	kमुक्त(hwmgr->ps);
	hwmgr->request_ps = शून्य;
	hwmgr->ps = शून्य;
	hwmgr->current_ps = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक psm_get_ui_state(काष्ठा pp_hwmgr *hwmgr,
				क्रमागत PP_StateUILabel ui_label,
				अचिन्हित दीर्घ *state_id)
अणु
	काष्ठा pp_घातer_state *state;
	पूर्णांक table_entries;
	पूर्णांक i;

	table_entries = hwmgr->num_ps;
	state = hwmgr->ps;

	क्रम (i = 0; i < table_entries; i++) अणु
		अगर (state->classअगरication.ui_label & ui_label) अणु
			*state_id = state->id;
			वापस 0;
		पूर्ण
		state = (काष्ठा pp_घातer_state *)((अचिन्हित दीर्घ)state + hwmgr->ps_size);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक psm_get_state_by_classअगरication(काष्ठा pp_hwmgr *hwmgr,
					क्रमागत PP_StateClassअगरicationFlag flag,
					अचिन्हित दीर्घ *state_id)
अणु
	काष्ठा pp_घातer_state *state;
	पूर्णांक table_entries;
	पूर्णांक i;

	table_entries = hwmgr->num_ps;
	state = hwmgr->ps;

	क्रम (i = 0; i < table_entries; i++) अणु
		अगर (state->classअगरication.flags & flag) अणु
			*state_id = state->id;
			वापस 0;
		पूर्ण
		state = (काष्ठा pp_घातer_state *)((अचिन्हित दीर्घ)state + hwmgr->ps_size);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक psm_set_states(काष्ठा pp_hwmgr *hwmgr, अचिन्हित दीर्घ state_id)
अणु
	काष्ठा pp_घातer_state *state;
	पूर्णांक table_entries;
	पूर्णांक i;

	table_entries = hwmgr->num_ps;

	state = hwmgr->ps;

	क्रम (i = 0; i < table_entries; i++) अणु
		अगर (state->id == state_id) अणु
			स_नकल(hwmgr->request_ps, state, hwmgr->ps_size);
			वापस 0;
		पूर्ण
		state = (काष्ठा pp_घातer_state *)((अचिन्हित दीर्घ)state + hwmgr->ps_size);
	पूर्ण
	वापस -EINVAL;
पूर्ण

पूर्णांक psm_set_boot_states(काष्ठा pp_hwmgr *hwmgr)
अणु
	अचिन्हित दीर्घ state_id;
	पूर्णांक ret = -EINVAL;

	अगर (!hwmgr->ps)
		वापस 0;

	अगर (!psm_get_state_by_classअगरication(hwmgr, PP_StateClassअगरicationFlag_Boot,
					&state_id))
		ret = psm_set_states(hwmgr, state_id);

	वापस ret;
पूर्ण

पूर्णांक psm_set_perक्रमmance_states(काष्ठा pp_hwmgr *hwmgr)
अणु
	अचिन्हित दीर्घ state_id;
	पूर्णांक ret = -EINVAL;

	अगर (!hwmgr->ps)
		वापस 0;

	अगर (!psm_get_ui_state(hwmgr, PP_StateUILabel_Perक्रमmance,
					&state_id))
		ret = psm_set_states(hwmgr, state_id);

	वापस ret;
पूर्ण

पूर्णांक psm_set_user_perक्रमmance_state(काष्ठा pp_hwmgr *hwmgr,
					क्रमागत PP_StateUILabel label_id,
					काष्ठा pp_घातer_state **state)
अणु
	पूर्णांक table_entries;
	पूर्णांक i;

	अगर (!hwmgr->ps)
		वापस 0;

	table_entries = hwmgr->num_ps;
	*state = hwmgr->ps;

restart_search:
	क्रम (i = 0; i < table_entries; i++) अणु
		अगर ((*state)->classअगरication.ui_label & label_id)
			वापस 0;
		*state = (काष्ठा pp_घातer_state *)((uपूर्णांकptr_t)*state + hwmgr->ps_size);
	पूर्ण

	चयन (label_id) अणु
	हाल PP_StateUILabel_Battery:
	हाल PP_StateUILabel_Balanced:
		label_id = PP_StateUILabel_Perक्रमmance;
		जाओ restart_search;
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल व्योम घातer_state_management(काष्ठा pp_hwmgr *hwmgr,
						काष्ठा pp_घातer_state *new_ps)
अणु
	काष्ठा pp_घातer_state *pcurrent;
	काष्ठा pp_घातer_state *requested;
	bool equal;

	अगर (new_ps != शून्य)
		requested = new_ps;
	अन्यथा
		requested = hwmgr->request_ps;

	pcurrent = hwmgr->current_ps;

	phm_apply_state_adjust_rules(hwmgr, requested, pcurrent);
	अगर (pcurrent == शून्य || (0 != phm_check_states_equal(hwmgr,
			&pcurrent->hardware, &requested->hardware, &equal)))
		equal = false;

	अगर (!equal || phm_check_smc_update_required_क्रम_display_configuration(hwmgr)) अणु
		phm_set_घातer_state(hwmgr, &pcurrent->hardware, &requested->hardware);
		स_नकल(hwmgr->current_ps, hwmgr->request_ps, hwmgr->ps_size);
	पूर्ण
पूर्ण

पूर्णांक psm_adjust_घातer_state_dynamic(काष्ठा pp_hwmgr *hwmgr, bool skip_display_settings,
						काष्ठा pp_घातer_state *new_ps)
अणु
	uपूर्णांक32_t index;
	दीर्घ workload;

	अगर (hwmgr->not_vf) अणु
		अगर (!skip_display_settings)
			phm_display_configuration_changed(hwmgr);

		अगर (hwmgr->ps)
			घातer_state_management(hwmgr, new_ps);
		अन्यथा
			/*
			 * क्रम vega12/vega20 which करोes not support घातer state manager
			 * DAL घड़ी limits should also be honoured
			 */
			phm_apply_घड़ी_adjust_rules(hwmgr);

		अगर (!skip_display_settings)
			phm_notअगरy_smc_display_config_after_ps_adjusपंचांगent(hwmgr);
	पूर्ण

	अगर (!phm_क्रमce_dpm_levels(hwmgr, hwmgr->request_dpm_level))
		hwmgr->dpm_level = hwmgr->request_dpm_level;

	अगर (hwmgr->dpm_level != AMD_DPM_FORCED_LEVEL_MANUAL) अणु
		index = fls(hwmgr->workload_mask);
		index = index > 0 && index <= Workload_Policy_Max ? index - 1 : 0;
		workload = hwmgr->workload_setting[index];

		अगर (hwmgr->घातer_profile_mode != workload && hwmgr->hwmgr_func->set_घातer_profile_mode)
			hwmgr->hwmgr_func->set_घातer_profile_mode(hwmgr, &workload, 0);
	पूर्ण

	वापस 0;
पूर्ण

