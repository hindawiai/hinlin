<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel Speed Select -- Enumerate and control features
 * Copyright (c) 2019 Intel Corporation.
 */

#समावेश "isst.h"

पूर्णांक isst_ग_लिखो_pm_config(पूर्णांक cpu, पूर्णांक cp_state)
अणु
	अचिन्हित पूर्णांक req, resp;
	पूर्णांक ret;

	अगर (cp_state)
		req = BIT(16);
	अन्यथा
		req = 0;

	ret = isst_send_mbox_command(cpu, WRITE_PM_CONFIG, PM_FEATURE, 0, req,
				     &resp);
	अगर (ret)
		वापस ret;

	debug_म_लिखो("cpu:%d WRITE_PM_CONFIG resp:%x\n", cpu, resp);

	वापस 0;
पूर्ण

पूर्णांक isst_पढ़ो_pm_config(पूर्णांक cpu, पूर्णांक *cp_state, पूर्णांक *cp_cap)
अणु
	अचिन्हित पूर्णांक resp;
	पूर्णांक ret;

	ret = isst_send_mbox_command(cpu, READ_PM_CONFIG, PM_FEATURE, 0, 0,
				     &resp);
	अगर (ret)
		वापस ret;

	debug_म_लिखो("cpu:%d READ_PM_CONFIG resp:%x\n", cpu, resp);

	*cp_state = resp & BIT(16);
	*cp_cap = resp & BIT(0) ? 1 : 0;

	वापस 0;
पूर्ण

पूर्णांक isst_get_ctdp_levels(पूर्णांक cpu, काष्ठा isst_pkg_ctdp *pkg_dev)
अणु
	अचिन्हित पूर्णांक resp;
	पूर्णांक ret;

	ret = isst_send_mbox_command(cpu, CONFIG_TDP,
				     CONFIG_TDP_GET_LEVELS_INFO, 0, 0, &resp);
	अगर (ret) अणु
		pkg_dev->levels = 0;
		pkg_dev->locked = 1;
		pkg_dev->current_level = 0;
		pkg_dev->version = 0;
		pkg_dev->enabled = 0;
		वापस 0;
	पूर्ण

	debug_म_लिखो("cpu:%d CONFIG_TDP_GET_LEVELS_INFO resp:%x\n", cpu, resp);

	pkg_dev->version = resp & 0xff;
	pkg_dev->levels = (resp >> 8) & 0xff;
	pkg_dev->current_level = (resp >> 16) & 0xff;
	pkg_dev->locked = !!(resp & BIT(24));
	pkg_dev->enabled = !!(resp & BIT(31));

	वापस 0;
पूर्ण

पूर्णांक isst_get_ctdp_control(पूर्णांक cpu, पूर्णांक config_index,
			  काष्ठा isst_pkg_ctdp_level_info *ctdp_level)
अणु
	पूर्णांक cp_state, cp_cap;
	अचिन्हित पूर्णांक resp;
	पूर्णांक ret;

	ret = isst_send_mbox_command(cpu, CONFIG_TDP,
				     CONFIG_TDP_GET_TDP_CONTROL, 0,
				     config_index, &resp);
	अगर (ret)
		वापस ret;

	ctdp_level->fact_support = resp & BIT(0);
	ctdp_level->pbf_support = !!(resp & BIT(1));
	ctdp_level->fact_enabled = !!(resp & BIT(16));
	ctdp_level->pbf_enabled = !!(resp & BIT(17));

	ret = isst_पढ़ो_pm_config(cpu, &cp_state, &cp_cap);
	अगर (ret) अणु
		debug_म_लिखो("cpu:%d pm_config is not supported \n", cpu);
	पूर्ण अन्यथा अणु
		debug_म_लिखो("cpu:%d pm_config SST-CP state:%d cap:%d \n", cpu, cp_state, cp_cap);
		ctdp_level->sst_cp_support = cp_cap;
		ctdp_level->sst_cp_enabled = cp_state;
	पूर्ण

	debug_म_लिखो(
		"cpu:%d CONFIG_TDP_GET_TDP_CONTROL resp:%x fact_support:%d pbf_support: %d fact_enabled:%d pbf_enabled:%d\n",
		cpu, resp, ctdp_level->fact_support, ctdp_level->pbf_support,
		ctdp_level->fact_enabled, ctdp_level->pbf_enabled);

	वापस 0;
पूर्ण

पूर्णांक isst_get_tdp_info(पूर्णांक cpu, पूर्णांक config_index,
		      काष्ठा isst_pkg_ctdp_level_info *ctdp_level)
अणु
	अचिन्हित पूर्णांक resp;
	पूर्णांक ret;

	ret = isst_send_mbox_command(cpu, CONFIG_TDP, CONFIG_TDP_GET_TDP_INFO,
				     0, config_index, &resp);
	अगर (ret) अणु
		isst_display_error_info_message(1, "Invalid level, Can't get TDP information at level", 1, config_index);
		वापस ret;
	पूर्ण

	ctdp_level->pkg_tdp = resp & GENMASK(14, 0);
	ctdp_level->tdp_ratio = (resp & GENMASK(23, 16)) >> 16;

	debug_म_लिखो(
		"cpu:%d ctdp:%d CONFIG_TDP_GET_TDP_INFO resp:%x tdp_ratio:%d pkg_tdp:%d\n",
		cpu, config_index, resp, ctdp_level->tdp_ratio,
		ctdp_level->pkg_tdp);
	वापस 0;
पूर्ण

पूर्णांक isst_get_pwr_info(पूर्णांक cpu, पूर्णांक config_index,
		      काष्ठा isst_pkg_ctdp_level_info *ctdp_level)
अणु
	अचिन्हित पूर्णांक resp;
	पूर्णांक ret;

	ret = isst_send_mbox_command(cpu, CONFIG_TDP, CONFIG_TDP_GET_PWR_INFO,
				     0, config_index, &resp);
	अगर (ret)
		वापस ret;

	ctdp_level->pkg_max_घातer = resp & GENMASK(14, 0);
	ctdp_level->pkg_min_घातer = (resp & GENMASK(30, 16)) >> 16;

	debug_म_लिखो(
		"cpu:%d ctdp:%d CONFIG_TDP_GET_PWR_INFO resp:%x pkg_max_power:%d pkg_min_power:%d\n",
		cpu, config_index, resp, ctdp_level->pkg_max_घातer,
		ctdp_level->pkg_min_घातer);

	वापस 0;
पूर्ण

व्योम isst_get_uncore_p0_p1_info(पूर्णांक cpu, पूर्णांक config_index,
				काष्ठा isst_pkg_ctdp_level_info *ctdp_level)
अणु
	अचिन्हित पूर्णांक resp;
	पूर्णांक ret;
	ret = isst_send_mbox_command(cpu, CONFIG_TDP,
				     CONFIG_TDP_GET_UNCORE_P0_P1_INFO, 0,
				     config_index, &resp);
	अगर (ret) अणु
		ctdp_level->uncore_p0 = 0;
		ctdp_level->uncore_p1 = 0;
		वापस;
	पूर्ण

	ctdp_level->uncore_p0 = resp & GENMASK(7, 0);
	ctdp_level->uncore_p1 = (resp & GENMASK(15, 8)) >> 8;
	debug_म_लिखो(
		"cpu:%d ctdp:%d CONFIG_TDP_GET_UNCORE_P0_P1_INFO resp:%x uncore p0:%d uncore p1:%d\n",
		cpu, config_index, resp, ctdp_level->uncore_p0,
		ctdp_level->uncore_p1);
पूर्ण

व्योम isst_get_p1_info(पूर्णांक cpu, पूर्णांक config_index,
		      काष्ठा isst_pkg_ctdp_level_info *ctdp_level)
अणु
	अचिन्हित पूर्णांक resp;
	पूर्णांक ret;
	ret = isst_send_mbox_command(cpu, CONFIG_TDP, CONFIG_TDP_GET_P1_INFO, 0,
				     config_index, &resp);
	अगर (ret) अणु
		ctdp_level->sse_p1 = 0;
		ctdp_level->avx2_p1 = 0;
		ctdp_level->avx512_p1 = 0;
		वापस;
	पूर्ण

	ctdp_level->sse_p1 = resp & GENMASK(7, 0);
	ctdp_level->avx2_p1 = (resp & GENMASK(15, 8)) >> 8;
	ctdp_level->avx512_p1 = (resp & GENMASK(23, 16)) >> 16;
	debug_म_लिखो(
		"cpu:%d ctdp:%d CONFIG_TDP_GET_P1_INFO resp:%x sse_p1:%d avx2_p1:%d avx512_p1:%d\n",
		cpu, config_index, resp, ctdp_level->sse_p1,
		ctdp_level->avx2_p1, ctdp_level->avx512_p1);
पूर्ण

व्योम isst_get_uncore_mem_freq(पूर्णांक cpu, पूर्णांक config_index,
			      काष्ठा isst_pkg_ctdp_level_info *ctdp_level)
अणु
	अचिन्हित पूर्णांक resp;
	पूर्णांक ret;
	ret = isst_send_mbox_command(cpu, CONFIG_TDP, CONFIG_TDP_GET_MEM_FREQ,
				     0, config_index, &resp);
	अगर (ret) अणु
		ctdp_level->mem_freq = 0;
		वापस;
	पूर्ण

	ctdp_level->mem_freq = resp & GENMASK(7, 0);
	debug_म_लिखो(
		"cpu:%d ctdp:%d CONFIG_TDP_GET_MEM_FREQ resp:%x uncore mem_freq:%d\n",
		cpu, config_index, resp, ctdp_level->mem_freq);
पूर्ण

पूर्णांक isst_get_tjmax_info(पूर्णांक cpu, पूर्णांक config_index,
			काष्ठा isst_pkg_ctdp_level_info *ctdp_level)
अणु
	अचिन्हित पूर्णांक resp;
	पूर्णांक ret;

	ret = isst_send_mbox_command(cpu, CONFIG_TDP, CONFIG_TDP_GET_TJMAX_INFO,
				     0, config_index, &resp);
	अगर (ret)
		वापस ret;

	ctdp_level->t_proc_hot = resp & GENMASK(7, 0);

	debug_म_लिखो(
		"cpu:%d ctdp:%d CONFIG_TDP_GET_TJMAX_INFO resp:%x t_proc_hot:%d\n",
		cpu, config_index, resp, ctdp_level->t_proc_hot);

	वापस 0;
पूर्ण

पूर्णांक isst_get_coremask_info(पूर्णांक cpu, पूर्णांक config_index,
			   काष्ठा isst_pkg_ctdp_level_info *ctdp_level)
अणु
	अचिन्हित पूर्णांक resp;
	पूर्णांक i, ret;

	ctdp_level->cpu_count = 0;
	क्रम (i = 0; i < 2; ++i) अणु
		अचिन्हित दीर्घ दीर्घ mask;
		पूर्णांक cpu_count = 0;

		ret = isst_send_mbox_command(cpu, CONFIG_TDP,
					     CONFIG_TDP_GET_CORE_MASK, 0,
					     (i << 8) | config_index, &resp);
		अगर (ret)
			वापस ret;

		debug_म_लिखो(
			"cpu:%d ctdp:%d mask:%d CONFIG_TDP_GET_CORE_MASK resp:%x\n",
			cpu, config_index, i, resp);

		mask = (अचिन्हित दीर्घ दीर्घ)resp << (32 * i);
		set_cpu_mask_from_punit_coremask(cpu, mask,
						 ctdp_level->core_cpumask_size,
						 ctdp_level->core_cpumask,
						 &cpu_count);
		ctdp_level->cpu_count += cpu_count;
		debug_म_लिखो("cpu:%d ctdp:%d mask:%d cpu count:%d\n", cpu,
			     config_index, i, ctdp_level->cpu_count);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक isst_get_get_trl_from_msr(पूर्णांक cpu, पूर्णांक *trl)
अणु
	अचिन्हित दीर्घ दीर्घ msr_trl;
	पूर्णांक ret;

	ret = isst_send_msr_command(cpu, 0x1AD, 0, &msr_trl);
	अगर (ret)
		वापस ret;

	trl[0] = msr_trl & GENMASK(7, 0);
	trl[1] = (msr_trl & GENMASK(15, 8)) >> 8;
	trl[2] = (msr_trl & GENMASK(23, 16)) >> 16;
	trl[3] = (msr_trl & GENMASK(31, 24)) >> 24;
	trl[4] = (msr_trl & GENMASK(39, 32)) >> 32;
	trl[5] = (msr_trl & GENMASK(47, 40)) >> 40;
	trl[6] = (msr_trl & GENMASK(55, 48)) >> 48;
	trl[7] = (msr_trl & GENMASK(63, 56)) >> 56;

	वापस 0;
पूर्ण

पूर्णांक isst_get_get_trl(पूर्णांक cpu, पूर्णांक level, पूर्णांक avx_level, पूर्णांक *trl)
अणु
	अचिन्हित पूर्णांक req, resp;
	पूर्णांक ret;

	req = level | (avx_level << 16);
	ret = isst_send_mbox_command(cpu, CONFIG_TDP,
				     CONFIG_TDP_GET_TURBO_LIMIT_RATIOS, 0, req,
				     &resp);
	अगर (ret)
		वापस ret;

	debug_म_लिखो(
		"cpu:%d CONFIG_TDP_GET_TURBO_LIMIT_RATIOS req:%x resp:%x\n",
		cpu, req, resp);

	trl[0] = resp & GENMASK(7, 0);
	trl[1] = (resp & GENMASK(15, 8)) >> 8;
	trl[2] = (resp & GENMASK(23, 16)) >> 16;
	trl[3] = (resp & GENMASK(31, 24)) >> 24;

	req = level | BIT(8) | (avx_level << 16);
	ret = isst_send_mbox_command(cpu, CONFIG_TDP,
				     CONFIG_TDP_GET_TURBO_LIMIT_RATIOS, 0, req,
				     &resp);
	अगर (ret)
		वापस ret;

	debug_म_लिखो("cpu:%d CONFIG_TDP_GET_TURBO_LIMIT req:%x resp:%x\n", cpu,
		     req, resp);

	trl[4] = resp & GENMASK(7, 0);
	trl[5] = (resp & GENMASK(15, 8)) >> 8;
	trl[6] = (resp & GENMASK(23, 16)) >> 16;
	trl[7] = (resp & GENMASK(31, 24)) >> 24;

	वापस 0;
पूर्ण

पूर्णांक isst_get_trl_bucket_info(पूर्णांक cpu, अचिन्हित दीर्घ दीर्घ *buckets_info)
अणु
	पूर्णांक ret;

	debug_म_लिखो("cpu:%d bucket info via MSR\n", cpu);

	*buckets_info = 0;

	ret = isst_send_msr_command(cpu, 0x1ae, 0, buckets_info);
	अगर (ret)
		वापस ret;

	debug_म_लिखो("cpu:%d bucket info via MSR successful 0x%llx\n", cpu,
		     *buckets_info);

	वापस 0;
पूर्ण

पूर्णांक isst_set_tdp_level_msr(पूर्णांक cpu, पूर्णांक tdp_level)
अणु
	अचिन्हित दीर्घ दीर्घ level = tdp_level;
	पूर्णांक ret;

	debug_म_लिखो("cpu: tdp_level via MSR %d\n", cpu, tdp_level);

	अगर (isst_get_config_tdp_lock_status(cpu)) अणु
		isst_display_error_info_message(1, "tdp_locked", 0, 0);
		वापस -1;
	पूर्ण

	अगर (tdp_level > 2)
		वापस -1; /* invalid value */

	ret = isst_send_msr_command(cpu, 0x64b, 1, &level);
	अगर (ret)
		वापस ret;

	debug_म_लिखो("cpu: tdp_level via MSR successful %d\n", cpu, tdp_level);

	वापस 0;
पूर्ण

पूर्णांक isst_set_tdp_level(पूर्णांक cpu, पूर्णांक tdp_level)
अणु
	अचिन्हित पूर्णांक resp;
	पूर्णांक ret;


	अगर (isst_get_config_tdp_lock_status(cpu)) अणु
		isst_display_error_info_message(1, "TDP is locked", 0, 0);
		वापस -1;

	पूर्ण

	ret = isst_send_mbox_command(cpu, CONFIG_TDP, CONFIG_TDP_SET_LEVEL, 0,
				     tdp_level, &resp);
	अगर (ret) अणु
		isst_display_error_info_message(1, "Set TDP level failed for level", 1, tdp_level);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक isst_get_pbf_info(पूर्णांक cpu, पूर्णांक level, काष्ठा isst_pbf_info *pbf_info)
अणु
	काष्ठा isst_pkg_ctdp_level_info ctdp_level;
	काष्ठा isst_pkg_ctdp pkg_dev;
	पूर्णांक i, ret, max_punit_core, max_mask_index;
	अचिन्हित पूर्णांक req, resp;

	ret = isst_get_ctdp_levels(cpu, &pkg_dev);
	अगर (ret) अणु
		isst_display_error_info_message(1, "Failed to get number of levels", 0, 0);
		वापस ret;
	पूर्ण

	अगर (level > pkg_dev.levels) अणु
		isst_display_error_info_message(1, "Invalid level", 1, level);
		वापस -1;
	पूर्ण

	ret = isst_get_ctdp_control(cpu, level, &ctdp_level);
	अगर (ret)
		वापस ret;

	अगर (!ctdp_level.pbf_support) अणु
		isst_display_error_info_message(1, "base-freq feature is not present at this level", 1, level);
		वापस -1;
	पूर्ण

	pbf_info->core_cpumask_size = alloc_cpu_set(&pbf_info->core_cpumask);

	max_punit_core = get_max_punit_core_id(get_physical_package_id(cpu), get_physical_die_id(cpu));
	max_mask_index = max_punit_core > 32 ? 2 : 1;

	क्रम (i = 0; i < max_mask_index; ++i) अणु
		अचिन्हित दीर्घ दीर्घ mask;
		पूर्णांक count;

		ret = isst_send_mbox_command(cpu, CONFIG_TDP,
					     CONFIG_TDP_PBF_GET_CORE_MASK_INFO,
					     0, (i << 8) | level, &resp);
		अगर (ret)
			अवरोध;

		debug_म_लिखो(
			"cpu:%d CONFIG_TDP_PBF_GET_CORE_MASK_INFO resp:%x\n",
			cpu, resp);

		mask = (अचिन्हित दीर्घ दीर्घ)resp << (32 * i);
		set_cpu_mask_from_punit_coremask(cpu, mask,
						 pbf_info->core_cpumask_size,
						 pbf_info->core_cpumask,
						 &count);
	पूर्ण

	req = level;
	ret = isst_send_mbox_command(cpu, CONFIG_TDP,
				     CONFIG_TDP_PBF_GET_P1HI_P1LO_INFO, 0, req,
				     &resp);
	अगर (ret)
		वापस ret;

	debug_म_लिखो("cpu:%d CONFIG_TDP_PBF_GET_P1HI_P1LO_INFO resp:%x\n", cpu,
		     resp);

	pbf_info->p1_low = resp & 0xff;
	pbf_info->p1_high = (resp & GENMASK(15, 8)) >> 8;

	req = level;
	ret = isst_send_mbox_command(
		cpu, CONFIG_TDP, CONFIG_TDP_PBF_GET_TDP_INFO, 0, req, &resp);
	अगर (ret)
		वापस ret;

	debug_म_लिखो("cpu:%d CONFIG_TDP_PBF_GET_TDP_INFO resp:%x\n", cpu, resp);

	pbf_info->tdp = resp & 0xffff;

	req = level;
	ret = isst_send_mbox_command(
		cpu, CONFIG_TDP, CONFIG_TDP_PBF_GET_TJ_MAX_INFO, 0, req, &resp);
	अगर (ret)
		वापस ret;

	debug_म_लिखो("cpu:%d CONFIG_TDP_PBF_GET_TJ_MAX_INFO resp:%x\n", cpu,
		     resp);
	pbf_info->t_control = (resp >> 8) & 0xff;
	pbf_info->t_prochot = resp & 0xff;

	वापस 0;
पूर्ण

व्योम isst_get_pbf_info_complete(काष्ठा isst_pbf_info *pbf_info)
अणु
	मुक्त_cpu_set(pbf_info->core_cpumask);
पूर्ण

पूर्णांक isst_set_pbf_fact_status(पूर्णांक cpu, पूर्णांक pbf, पूर्णांक enable)
अणु
	काष्ठा isst_pkg_ctdp pkg_dev;
	काष्ठा isst_pkg_ctdp_level_info ctdp_level;
	पूर्णांक current_level;
	अचिन्हित पूर्णांक req = 0, resp;
	पूर्णांक ret;

	ret = isst_get_ctdp_levels(cpu, &pkg_dev);
	अगर (ret)
		debug_म_लिखो("cpu:%d No support for dynamic ISST\n", cpu);

	current_level = pkg_dev.current_level;

	ret = isst_get_ctdp_control(cpu, current_level, &ctdp_level);
	अगर (ret)
		वापस ret;

	अगर (pbf) अणु
		अगर (ctdp_level.fact_enabled)
			req = BIT(16);

		अगर (enable)
			req |= BIT(17);
		अन्यथा
			req &= ~BIT(17);
	पूर्ण अन्यथा अणु

		अगर (enable && !ctdp_level.sst_cp_enabled)
			isst_display_error_info_message(0, "Make sure to execute before: core-power enable", 0, 0);

		अगर (ctdp_level.pbf_enabled)
			req = BIT(17);

		अगर (enable)
			req |= BIT(16);
		अन्यथा
			req &= ~BIT(16);
	पूर्ण

	ret = isst_send_mbox_command(cpu, CONFIG_TDP,
				     CONFIG_TDP_SET_TDP_CONTROL, 0, req, &resp);
	अगर (ret)
		वापस ret;

	debug_म_लिखो("cpu:%d CONFIG_TDP_SET_TDP_CONTROL pbf/fact:%d req:%x\n",
		     cpu, pbf, req);

	वापस 0;
पूर्ण

पूर्णांक isst_get_fact_bucket_info(पूर्णांक cpu, पूर्णांक level,
			      काष्ठा isst_fact_bucket_info *bucket_info)
अणु
	अचिन्हित पूर्णांक resp;
	पूर्णांक i, k, ret;

	क्रम (i = 0; i < 2; ++i) अणु
		पूर्णांक j;

		ret = isst_send_mbox_command(
			cpu, CONFIG_TDP,
			CONFIG_TDP_GET_FACT_HP_TURBO_LIMIT_NUMCORES, 0,
			(i << 8) | level, &resp);
		अगर (ret)
			वापस ret;

		debug_म_लिखो(
			"cpu:%d CONFIG_TDP_GET_FACT_HP_TURBO_LIMIT_NUMCORES index:%d level:%d resp:%x\n",
			cpu, i, level, resp);

		क्रम (j = 0; j < 4; ++j) अणु
			bucket_info[j + (i * 4)].high_priority_cores_count =
				(resp >> (j * 8)) & 0xff;
		पूर्ण
	पूर्ण

	क्रम (k = 0; k < 3; ++k) अणु
		क्रम (i = 0; i < 2; ++i) अणु
			पूर्णांक j;

			ret = isst_send_mbox_command(
				cpu, CONFIG_TDP,
				CONFIG_TDP_GET_FACT_HP_TURBO_LIMIT_RATIOS, 0,
				(k << 16) | (i << 8) | level, &resp);
			अगर (ret)
				वापस ret;

			debug_म_लिखो(
				"cpu:%d CONFIG_TDP_GET_FACT_HP_TURBO_LIMIT_RATIOS index:%d level:%d avx:%d resp:%x\n",
				cpu, i, level, k, resp);

			क्रम (j = 0; j < 4; ++j) अणु
				चयन (k) अणु
				हाल 0:
					bucket_info[j + (i * 4)].sse_trl =
						(resp >> (j * 8)) & 0xff;
					अवरोध;
				हाल 1:
					bucket_info[j + (i * 4)].avx_trl =
						(resp >> (j * 8)) & 0xff;
					अवरोध;
				हाल 2:
					bucket_info[j + (i * 4)].avx512_trl =
						(resp >> (j * 8)) & 0xff;
					अवरोध;
				शेष:
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक isst_get_fact_info(पूर्णांक cpu, पूर्णांक level, पूर्णांक fact_bucket, काष्ठा isst_fact_info *fact_info)
अणु
	काष्ठा isst_pkg_ctdp_level_info ctdp_level;
	काष्ठा isst_pkg_ctdp pkg_dev;
	अचिन्हित पूर्णांक resp;
	पूर्णांक j, ret, prपूर्णांक;

	ret = isst_get_ctdp_levels(cpu, &pkg_dev);
	अगर (ret) अणु
		isst_display_error_info_message(1, "Failed to get number of levels", 0, 0);
		वापस ret;
	पूर्ण

	अगर (level > pkg_dev.levels) अणु
		isst_display_error_info_message(1, "Invalid level", 1, level);
		वापस -1;
	पूर्ण

	ret = isst_get_ctdp_control(cpu, level, &ctdp_level);
	अगर (ret)
		वापस ret;

	अगर (!ctdp_level.fact_support) अणु
		isst_display_error_info_message(1, "turbo-freq feature is not present at this level", 1, level);
		वापस -1;
	पूर्ण

	ret = isst_send_mbox_command(cpu, CONFIG_TDP,
				     CONFIG_TDP_GET_FACT_LP_CLIPPING_RATIO, 0,
				     level, &resp);
	अगर (ret)
		वापस ret;

	debug_म_लिखो("cpu:%d CONFIG_TDP_GET_FACT_LP_CLIPPING_RATIO resp:%x\n",
		     cpu, resp);

	fact_info->lp_clipping_ratio_license_sse = resp & 0xff;
	fact_info->lp_clipping_ratio_license_avx2 = (resp >> 8) & 0xff;
	fact_info->lp_clipping_ratio_license_avx512 = (resp >> 16) & 0xff;

	ret = isst_get_fact_bucket_info(cpu, level, fact_info->bucket_info);
	अगर (ret)
		वापस ret;

	prपूर्णांक = 0;
	क्रम (j = 0; j < ISST_FACT_MAX_BUCKETS; ++j) अणु
		अगर (fact_bucket != 0xff && fact_bucket != j)
			जारी;

		अगर (!fact_info->bucket_info[j].high_priority_cores_count)
			अवरोध;

		prपूर्णांक = 1;
	पूर्ण
	अगर (!prपूर्णांक) अणु
		isst_display_error_info_message(1, "Invalid bucket", 0, 0);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक isst_get_trl(पूर्णांक cpu, अचिन्हित दीर्घ दीर्घ *trl)
अणु
	पूर्णांक ret;

	ret = isst_send_msr_command(cpu, 0x1AD, 0, trl);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक isst_set_trl(पूर्णांक cpu, अचिन्हित दीर्घ दीर्घ trl)
अणु
	पूर्णांक ret;

	अगर (!trl)
		trl = 0xFFFFFFFFFFFFFFFFULL;

	ret = isst_send_msr_command(cpu, 0x1AD, 1, &trl);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

पूर्णांक isst_set_trl_from_current_tdp(पूर्णांक cpu, अचिन्हित दीर्घ दीर्घ trl)
अणु
	अचिन्हित दीर्घ दीर्घ msr_trl;
	पूर्णांक ret;

	अगर (trl) अणु
		msr_trl = trl;
	पूर्ण अन्यथा अणु
		काष्ठा isst_pkg_ctdp pkg_dev;
		पूर्णांक trl[8];
		पूर्णांक i;

		ret = isst_get_ctdp_levels(cpu, &pkg_dev);
		अगर (ret)
			वापस ret;

		ret = isst_get_get_trl(cpu, pkg_dev.current_level, 0, trl);
		अगर (ret)
			वापस ret;

		msr_trl = 0;
		क्रम (i = 0; i < 8; ++i) अणु
			अचिन्हित दीर्घ दीर्घ _trl = trl[i];

			msr_trl |= (_trl << (i * 8));
		पूर्ण
	पूर्ण
	ret = isst_send_msr_command(cpu, 0x1AD, 1, &msr_trl);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

/* Return 1 अगर locked */
पूर्णांक isst_get_config_tdp_lock_status(पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ दीर्घ tdp_control = 0;
	पूर्णांक ret;

	ret = isst_send_msr_command(cpu, 0x64b, 0, &tdp_control);
	अगर (ret)
		वापस ret;

	ret = !!(tdp_control & BIT(31));

	वापस ret;
पूर्ण

व्योम isst_get_process_ctdp_complete(पूर्णांक cpu, काष्ठा isst_pkg_ctdp *pkg_dev)
अणु
	पूर्णांक i;

	अगर (!pkg_dev->processed)
		वापस;

	क्रम (i = 0; i < pkg_dev->levels; ++i) अणु
		काष्ठा isst_pkg_ctdp_level_info *ctdp_level;

		ctdp_level = &pkg_dev->ctdp_level[i];
		अगर (ctdp_level->pbf_support)
			मुक्त_cpu_set(ctdp_level->pbf_info.core_cpumask);
		मुक्त_cpu_set(ctdp_level->core_cpumask);
	पूर्ण
पूर्ण

पूर्णांक isst_get_process_ctdp(पूर्णांक cpu, पूर्णांक tdp_level, काष्ठा isst_pkg_ctdp *pkg_dev)
अणु
	पूर्णांक i, ret, valid = 0;

	अगर (pkg_dev->processed)
		वापस 0;

	ret = isst_get_ctdp_levels(cpu, pkg_dev);
	अगर (ret)
		वापस ret;

	debug_म_लिखो("cpu: %d ctdp enable:%d current level: %d levels:%d\n",
		     cpu, pkg_dev->enabled, pkg_dev->current_level,
		     pkg_dev->levels);

	अगर (tdp_level != 0xff && tdp_level > pkg_dev->levels) अणु
		isst_display_error_info_message(1, "Invalid level", 0, 0);
		वापस -1;
	पूर्ण

	अगर (!pkg_dev->enabled)
		isst_display_error_info_message(0, "perf-profile feature is not supported, just base-config level 0 is valid", 0, 0);

	क्रम (i = 0; i <= pkg_dev->levels; ++i) अणु
		काष्ठा isst_pkg_ctdp_level_info *ctdp_level;

		अगर (tdp_level != 0xff && i != tdp_level)
			जारी;

		debug_म_लिखो("cpu:%d Get Information for TDP level:%d\n", cpu,
			     i);
		ctdp_level = &pkg_dev->ctdp_level[i];

		ctdp_level->level = i;
		ctdp_level->control_cpu = cpu;
		ctdp_level->pkg_id = get_physical_package_id(cpu);
		ctdp_level->die_id = get_physical_die_id(cpu);

		ret = isst_get_ctdp_control(cpu, i, ctdp_level);
		अगर (ret)
			जारी;

		valid = 1;
		pkg_dev->processed = 1;
		ctdp_level->processed = 1;

		अगर (ctdp_level->pbf_support) अणु
			ret = isst_get_pbf_info(cpu, i, &ctdp_level->pbf_info);
			अगर (!ret)
				ctdp_level->pbf_found = 1;
		पूर्ण

		अगर (ctdp_level->fact_support) अणु
			ret = isst_get_fact_info(cpu, i, 0xff,
						 &ctdp_level->fact_info);
			अगर (ret)
				वापस ret;
		पूर्ण

		अगर (!pkg_dev->enabled && is_skx_based_platक्रमm()) अणु
			पूर्णांक freq;

			freq = get_cpufreq_base_freq(cpu);
			अगर (freq > 0) अणु
				ctdp_level->sse_p1 = freq / 100000;
				ctdp_level->tdp_ratio = ctdp_level->sse_p1;
			पूर्ण

			isst_get_get_trl_from_msr(cpu, ctdp_level->trl_sse_active_cores);
			isst_get_trl_bucket_info(cpu, &ctdp_level->buckets_info);
			जारी;
		पूर्ण

		ret = isst_get_tdp_info(cpu, i, ctdp_level);
		अगर (ret)
			वापस ret;

		ret = isst_get_pwr_info(cpu, i, ctdp_level);
		अगर (ret)
			वापस ret;

		ret = isst_get_tjmax_info(cpu, i, ctdp_level);
		अगर (ret)
			वापस ret;

		ctdp_level->core_cpumask_size =
			alloc_cpu_set(&ctdp_level->core_cpumask);
		ret = isst_get_coremask_info(cpu, i, ctdp_level);
		अगर (ret)
			वापस ret;

		ret = isst_get_trl_bucket_info(cpu, &ctdp_level->buckets_info);
		अगर (ret)
			वापस ret;

		ret = isst_get_get_trl(cpu, i, 0,
				       ctdp_level->trl_sse_active_cores);
		अगर (ret)
			वापस ret;

		ret = isst_get_get_trl(cpu, i, 1,
				       ctdp_level->trl_avx_active_cores);
		अगर (ret)
			वापस ret;

		ret = isst_get_get_trl(cpu, i, 2,
				       ctdp_level->trl_avx_512_active_cores);
		अगर (ret)
			वापस ret;

		isst_get_uncore_p0_p1_info(cpu, i, ctdp_level);
		isst_get_p1_info(cpu, i, ctdp_level);
		isst_get_uncore_mem_freq(cpu, i, ctdp_level);
	पूर्ण

	अगर (!valid)
		isst_display_error_info_message(0, "Invalid level, Can't get TDP control information at specified levels on cpu", 1, cpu);

	वापस 0;
पूर्ण

पूर्णांक isst_clos_get_clos_inक्रमmation(पूर्णांक cpu, पूर्णांक *enable, पूर्णांक *type)
अणु
	अचिन्हित पूर्णांक resp;
	पूर्णांक ret;

	ret = isst_send_mbox_command(cpu, CONFIG_CLOS, CLOS_PM_QOS_CONFIG, 0, 0,
				     &resp);
	अगर (ret)
		वापस ret;

	debug_म_लिखो("cpu:%d CLOS_PM_QOS_CONFIG resp:%x\n", cpu, resp);

	अगर (resp & BIT(1))
		*enable = 1;
	अन्यथा
		*enable = 0;

	अगर (resp & BIT(2))
		*type = 1;
	अन्यथा
		*type = 0;

	वापस 0;
पूर्ण

पूर्णांक isst_pm_qos_config(पूर्णांक cpu, पूर्णांक enable_clos, पूर्णांक priority_type)
अणु
	अचिन्हित पूर्णांक req, resp;
	पूर्णांक ret;

	अगर (!enable_clos) अणु
		काष्ठा isst_pkg_ctdp pkg_dev;
		काष्ठा isst_pkg_ctdp_level_info ctdp_level;

		ret = isst_get_ctdp_levels(cpu, &pkg_dev);
		अगर (ret) अणु
			debug_म_लिखो("isst_get_ctdp_levels\n");
			वापस ret;
		पूर्ण

		ret = isst_get_ctdp_control(cpu, pkg_dev.current_level,
					    &ctdp_level);
		अगर (ret)
			वापस ret;

		अगर (ctdp_level.fact_enabled) अणु
			isst_display_error_info_message(1, "Ignoring request, turbo-freq feature is still enabled", 0, 0);
			वापस -EINVAL;
		पूर्ण
		ret = isst_ग_लिखो_pm_config(cpu, 0);
		अगर (ret)
			isst_display_error_info_message(0, "WRITE_PM_CONFIG command failed, ignoring error", 0, 0);
	पूर्ण अन्यथा अणु
		ret = isst_ग_लिखो_pm_config(cpu, 1);
		अगर (ret)
			isst_display_error_info_message(0, "WRITE_PM_CONFIG command failed, ignoring error", 0, 0);
	पूर्ण

	ret = isst_send_mbox_command(cpu, CONFIG_CLOS, CLOS_PM_QOS_CONFIG, 0, 0,
				     &resp);
	अगर (ret) अणु
		isst_display_error_info_message(1, "CLOS_PM_QOS_CONFIG command failed", 0, 0);
		वापस ret;
	पूर्ण

	debug_म_लिखो("cpu:%d CLOS_PM_QOS_CONFIG resp:%x\n", cpu, resp);

	req = resp;

	अगर (enable_clos)
		req = req | BIT(1);
	अन्यथा
		req = req & ~BIT(1);

	अगर (priority_type > 1)
		isst_display_error_info_message(1, "Invalid priority type: Changing type to ordered", 0, 0);

	अगर (priority_type)
		req = req | BIT(2);
	अन्यथा
		req = req & ~BIT(2);

	ret = isst_send_mbox_command(cpu, CONFIG_CLOS, CLOS_PM_QOS_CONFIG,
				     BIT(MBOX_CMD_WRITE_BIT), req, &resp);
	अगर (ret)
		वापस ret;

	debug_म_लिखो("cpu:%d CLOS_PM_QOS_CONFIG priority type:%d req:%x\n", cpu,
		     priority_type, req);

	वापस 0;
पूर्ण

पूर्णांक isst_pm_get_clos(पूर्णांक cpu, पूर्णांक clos, काष्ठा isst_clos_config *clos_config)
अणु
	अचिन्हित पूर्णांक resp;
	पूर्णांक ret;

	ret = isst_send_mbox_command(cpu, CONFIG_CLOS, CLOS_PM_CLOS, clos, 0,
				     &resp);
	अगर (ret)
		वापस ret;

	clos_config->pkg_id = get_physical_package_id(cpu);
	clos_config->die_id = get_physical_die_id(cpu);

	clos_config->epp = resp & 0x0f;
	clos_config->clos_prop_prio = (resp >> 4) & 0x0f;
	clos_config->clos_min = (resp >> 8) & 0xff;
	clos_config->clos_max = (resp >> 16) & 0xff;
	clos_config->clos_desired = (resp >> 24) & 0xff;

	वापस 0;
पूर्ण

पूर्णांक isst_set_clos(पूर्णांक cpu, पूर्णांक clos, काष्ठा isst_clos_config *clos_config)
अणु
	अचिन्हित पूर्णांक req, resp;
	अचिन्हित पूर्णांक param;
	पूर्णांक ret;

	req = clos_config->epp & 0x0f;
	req |= (clos_config->clos_prop_prio & 0x0f) << 4;
	req |= (clos_config->clos_min & 0xff) << 8;
	req |= (clos_config->clos_max & 0xff) << 16;
	req |= (clos_config->clos_desired & 0xff) << 24;

	param = BIT(MBOX_CMD_WRITE_BIT) | clos;

	ret = isst_send_mbox_command(cpu, CONFIG_CLOS, CLOS_PM_CLOS, param, req,
				     &resp);
	अगर (ret)
		वापस ret;

	debug_म_लिखो("cpu:%d CLOS_PM_CLOS param:%x req:%x\n", cpu, param, req);

	वापस 0;
पूर्ण

पूर्णांक isst_clos_get_assoc_status(पूर्णांक cpu, पूर्णांक *clos_id)
अणु
	अचिन्हित पूर्णांक resp;
	अचिन्हित पूर्णांक param;
	पूर्णांक core_id, ret;

	core_id = find_phy_core_num(cpu);
	param = core_id;

	ret = isst_send_mbox_command(cpu, CONFIG_CLOS, CLOS_PQR_ASSOC, param, 0,
				     &resp);
	अगर (ret)
		वापस ret;

	debug_म_लिखो("cpu:%d CLOS_PQR_ASSOC param:%x resp:%x\n", cpu, param,
		     resp);
	*clos_id = (resp >> 16) & 0x03;

	वापस 0;
पूर्ण

पूर्णांक isst_clos_associate(पूर्णांक cpu, पूर्णांक clos_id)
अणु
	अचिन्हित पूर्णांक req, resp;
	अचिन्हित पूर्णांक param;
	पूर्णांक core_id, ret;

	req = (clos_id & 0x03) << 16;
	core_id = find_phy_core_num(cpu);
	param = BIT(MBOX_CMD_WRITE_BIT) | core_id;

	ret = isst_send_mbox_command(cpu, CONFIG_CLOS, CLOS_PQR_ASSOC, param,
				     req, &resp);
	अगर (ret)
		वापस ret;

	debug_म_लिखो("cpu:%d CLOS_PQR_ASSOC param:%x req:%x\n", cpu, param,
		     req);

	वापस 0;
पूर्ण
