<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel dynamic_speed_select -- Enumerate and control features
 * Copyright (c) 2019 Intel Corporation.
 */

#समावेश "isst.h"

अटल व्योम prपूर्णांकcpulist(पूर्णांक str_len, अक्षर *str, पूर्णांक mask_size,
			 cpu_set_t *cpu_mask)
अणु
	पूर्णांक i, first, curr_index, index;

	अगर (!CPU_COUNT_S(mask_size, cpu_mask)) अणु
		snम_लिखो(str, str_len, "none");
		वापस;
	पूर्ण

	curr_index = 0;
	first = 1;
	क्रम (i = 0; i < get_topo_max_cpus(); ++i) अणु
		अगर (!CPU_ISSET_S(i, mask_size, cpu_mask))
			जारी;
		अगर (!first) अणु
			index = snम_लिखो(&str[curr_index],
					 str_len - curr_index, ",");
			curr_index += index;
			अगर (curr_index >= str_len)
				अवरोध;
		पूर्ण
		index = snम_लिखो(&str[curr_index], str_len - curr_index, "%d",
				 i);
		curr_index += index;
		अगर (curr_index >= str_len)
			अवरोध;
		first = 0;
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांकcpumask(पूर्णांक str_len, अक्षर *str, पूर्णांक mask_size,
			 cpu_set_t *cpu_mask)
अणु
	पूर्णांक i, max_cpus = get_topo_max_cpus();
	अचिन्हित पूर्णांक *mask;
	पूर्णांक size, index, curr_index;

	size = max_cpus / (माप(अचिन्हित पूर्णांक) * 8);
	अगर (max_cpus % (माप(अचिन्हित पूर्णांक) * 8))
		size++;

	mask = सुस्मृति(size, माप(अचिन्हित पूर्णांक));
	अगर (!mask)
		वापस;

	क्रम (i = 0; i < max_cpus; ++i) अणु
		पूर्णांक mask_index, bit_index;

		अगर (!CPU_ISSET_S(i, mask_size, cpu_mask))
			जारी;

		mask_index = i / (माप(अचिन्हित पूर्णांक) * 8);
		bit_index = i % (माप(अचिन्हित पूर्णांक) * 8);
		mask[mask_index] |= BIT(bit_index);
	पूर्ण

	curr_index = 0;
	क्रम (i = size - 1; i >= 0; --i) अणु
		index = snम_लिखो(&str[curr_index], str_len - curr_index, "%08x",
				 mask[i]);
		curr_index += index;
		अगर (curr_index >= str_len)
			अवरोध;
		अगर (i) अणु
			म_जोड़न(&str[curr_index], ",", str_len - curr_index);
			curr_index++;
		पूर्ण
		अगर (curr_index >= str_len)
			अवरोध;
	पूर्ण

	मुक्त(mask);
पूर्ण

अटल व्योम क्रमmat_and_prपूर्णांक_txt(खाता *outf, पूर्णांक level, अक्षर *header,
				 अक्षर *value)
अणु
	अक्षर *spaces = "  ";
	अटल अक्षर delimiters[256];
	पूर्णांक i, j = 0;

	अगर (!level)
		वापस;

	अगर (level == 1) अणु
		म_नकल(delimiters, " ");
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < level - 1; ++i)
			j += snम_लिखो(&delimiters[j], माप(delimiters) - j,
				      "%s", spaces);
	पूर्ण

	अगर (header && value) अणु
		ख_लिखो(outf, "%s", delimiters);
		ख_लिखो(outf, "%s:%s\n", header, value);
	पूर्ण अन्यथा अगर (header) अणु
		ख_लिखो(outf, "%s", delimiters);
		ख_लिखो(outf, "%s\n", header);
	पूर्ण
पूर्ण

अटल पूर्णांक last_level;
अटल व्योम क्रमmat_and_prपूर्णांक(खाता *outf, पूर्णांक level, अक्षर *header, अक्षर *value)
अणु
	अक्षर *spaces = "  ";
	अटल अक्षर delimiters[256];
	पूर्णांक i;

	अगर (!out_क्रमmat_is_json()) अणु
		क्रमmat_and_prपूर्णांक_txt(outf, level, header, value);
		वापस;
	पूर्ण

	अगर (level == 0) अणु
		अगर (header)
			ख_लिखो(outf, "{");
		अन्यथा
			ख_लिखो(outf, "\n}\n");

	पूर्ण अन्यथा अणु
		पूर्णांक j = 0;

		क्रम (i = 0; i < level; ++i)
			j += snम_लिखो(&delimiters[j], माप(delimiters) - j,
				      "%s", spaces);

		अगर (last_level == level)
			ख_लिखो(outf, ",\n");

		अगर (value) अणु
			अगर (last_level != level)
				ख_लिखो(outf, "\n");

			ख_लिखो(outf, "%s\"%s\": ", delimiters, header);
			ख_लिखो(outf, "\"%s\"", value);
		पूर्ण अन्यथा अणु
			क्रम (i = last_level - 1; i >= level; --i) अणु
				पूर्णांक k = 0;

				क्रम (j = i; j > 0; --j)
					k += snम_लिखो(&delimiters[k],
						      माप(delimiters) - k,
						      "%s", spaces);
				अगर (i == level && header)
					ख_लिखो(outf, "\n%s},", delimiters);
				अन्यथा
					ख_लिखो(outf, "\n%s}", delimiters);
			पूर्ण
			अगर (असल(last_level - level) < 3)
				ख_लिखो(outf, "\n");
			अगर (header)
				ख_लिखो(outf, "%s\"%s\": {", delimiters,
					header);
		पूर्ण
	पूर्ण

	last_level = level;
पूर्ण

अटल पूर्णांक prपूर्णांक_package_info(पूर्णांक cpu, खाता *outf)
अणु
	अक्षर header[256];

	अगर (out_क्रमmat_is_json()) अणु
		snम_लिखो(header, माप(header), "package-%d:die-%d:cpu-%d",
			 get_physical_package_id(cpu), get_physical_die_id(cpu),
			 cpu);
		क्रमmat_and_prपूर्णांक(outf, 1, header, शून्य);
		वापस 1;
	पूर्ण
	snम_लिखो(header, माप(header), "package-%d",
		 get_physical_package_id(cpu));
	क्रमmat_and_prपूर्णांक(outf, 1, header, शून्य);
	snम_लिखो(header, माप(header), "die-%d", get_physical_die_id(cpu));
	क्रमmat_and_prपूर्णांक(outf, 2, header, शून्य);
	snम_लिखो(header, माप(header), "cpu-%d", cpu);
	क्रमmat_and_prपूर्णांक(outf, 3, header, शून्य);

	वापस 3;
पूर्ण

अटल व्योम _isst_pbf_display_inक्रमmation(पूर्णांक cpu, खाता *outf, पूर्णांक level,
					  काष्ठा isst_pbf_info *pbf_info,
					  पूर्णांक disp_level)
अणु
	अक्षर header[256];
	अक्षर value[512];

	snम_लिखो(header, माप(header), "speed-select-base-freq-properties");
	क्रमmat_and_prपूर्णांक(outf, disp_level, header, शून्य);

	snम_लिखो(header, माप(header), "high-priority-base-frequency(MHz)");
	snम_लिखो(value, माप(value), "%d",
		 pbf_info->p1_high * DISP_FREQ_MULTIPLIER);
	क्रमmat_and_prपूर्णांक(outf, disp_level + 1, header, value);

	snम_लिखो(header, माप(header), "high-priority-cpu-mask");
	prपूर्णांकcpumask(माप(value), value, pbf_info->core_cpumask_size,
		     pbf_info->core_cpumask);
	क्रमmat_and_prपूर्णांक(outf, disp_level + 1, header, value);

	snम_लिखो(header, माप(header), "high-priority-cpu-list");
	prपूर्णांकcpulist(माप(value), value,
		     pbf_info->core_cpumask_size,
		     pbf_info->core_cpumask);
	क्रमmat_and_prपूर्णांक(outf, disp_level + 1, header, value);

	snम_लिखो(header, माप(header), "low-priority-base-frequency(MHz)");
	snम_लिखो(value, माप(value), "%d",
		 pbf_info->p1_low * DISP_FREQ_MULTIPLIER);
	क्रमmat_and_prपूर्णांक(outf, disp_level + 1, header, value);

	अगर (is_clx_n_platक्रमm())
		वापस;

	snम_लिखो(header, माप(header), "tjunction-temperature(C)");
	snम_लिखो(value, माप(value), "%d", pbf_info->t_prochot);
	क्रमmat_and_prपूर्णांक(outf, disp_level + 1, header, value);

	snम_लिखो(header, माप(header), "thermal-design-power(W)");
	snम_लिखो(value, माप(value), "%d", pbf_info->tdp);
	क्रमmat_and_prपूर्णांक(outf, disp_level + 1, header, value);
पूर्ण

अटल व्योम _isst_fact_display_inक्रमmation(पूर्णांक cpu, खाता *outf, पूर्णांक level,
					   पूर्णांक fact_bucket, पूर्णांक fact_avx,
					   काष्ठा isst_fact_info *fact_info,
					   पूर्णांक base_level)
अणु
	काष्ठा isst_fact_bucket_info *bucket_info = fact_info->bucket_info;
	अक्षर header[256];
	अक्षर value[256];
	पूर्णांक prपूर्णांक = 0, j;

	क्रम (j = 0; j < ISST_FACT_MAX_BUCKETS; ++j) अणु
		अगर (fact_bucket != 0xff && fact_bucket != j)
			जारी;

		अगर (!bucket_info[j].high_priority_cores_count)
			अवरोध;

		prपूर्णांक = 1;
	पूर्ण
	अगर (!prपूर्णांक) अणु
		ख_लिखो(मानक_त्रुटि, "Invalid bucket\n");
		वापस;
	पूर्ण

	snम_लिखो(header, माप(header), "speed-select-turbo-freq-properties");
	क्रमmat_and_prपूर्णांक(outf, base_level, header, शून्य);
	क्रम (j = 0; j < ISST_FACT_MAX_BUCKETS; ++j) अणु
		अगर (fact_bucket != 0xff && fact_bucket != j)
			जारी;

		अगर (!bucket_info[j].high_priority_cores_count)
			अवरोध;

		snम_लिखो(header, माप(header), "bucket-%d", j);
		क्रमmat_and_prपूर्णांक(outf, base_level + 1, header, शून्य);

		snम_लिखो(header, माप(header), "high-priority-cores-count");
		snम_लिखो(value, माप(value), "%d",
			 bucket_info[j].high_priority_cores_count);
		क्रमmat_and_prपूर्णांक(outf, base_level + 2, header, value);

		अगर (fact_avx & 0x01) अणु
			snम_लिखो(header, माप(header),
				 "high-priority-max-frequency(MHz)");
			snम_लिखो(value, माप(value), "%d",
				 bucket_info[j].sse_trl * DISP_FREQ_MULTIPLIER);
			क्रमmat_and_prपूर्णांक(outf, base_level + 2, header, value);
		पूर्ण

		अगर (fact_avx & 0x02) अणु
			snम_लिखो(header, माप(header),
				 "high-priority-max-avx2-frequency(MHz)");
			snम_लिखो(value, माप(value), "%d",
				 bucket_info[j].avx_trl * DISP_FREQ_MULTIPLIER);
			क्रमmat_and_prपूर्णांक(outf, base_level + 2, header, value);
		पूर्ण

		अगर (fact_avx & 0x04) अणु
			snम_लिखो(header, माप(header),
				 "high-priority-max-avx512-frequency(MHz)");
			snम_लिखो(value, माप(value), "%d",
				 bucket_info[j].avx512_trl *
					 DISP_FREQ_MULTIPLIER);
			क्रमmat_and_prपूर्णांक(outf, base_level + 2, header, value);
		पूर्ण
	पूर्ण
	snम_लिखो(header, माप(header),
		 "speed-select-turbo-freq-clip-frequencies");
	क्रमmat_and_prपूर्णांक(outf, base_level + 1, header, शून्य);
	snम_लिखो(header, माप(header), "low-priority-max-frequency(MHz)");
	snम_लिखो(value, माप(value), "%d",
		 fact_info->lp_clipping_ratio_license_sse *
			 DISP_FREQ_MULTIPLIER);
	क्रमmat_and_prपूर्णांक(outf, base_level + 2, header, value);
	snम_लिखो(header, माप(header),
		 "low-priority-max-avx2-frequency(MHz)");
	snम_लिखो(value, माप(value), "%d",
		 fact_info->lp_clipping_ratio_license_avx2 *
			 DISP_FREQ_MULTIPLIER);
	क्रमmat_and_prपूर्णांक(outf, base_level + 2, header, value);
	snम_लिखो(header, माप(header),
		 "low-priority-max-avx512-frequency(MHz)");
	snम_लिखो(value, माप(value), "%d",
		 fact_info->lp_clipping_ratio_license_avx512 *
			 DISP_FREQ_MULTIPLIER);
	क्रमmat_and_prपूर्णांक(outf, base_level + 2, header, value);
पूर्ण

व्योम isst_ctdp_display_core_info(पूर्णांक cpu, खाता *outf, अक्षर *prefix,
				 अचिन्हित पूर्णांक val, अक्षर *str0, अक्षर *str1)
अणु
	अक्षर header[256];
	अक्षर value[256];
	पूर्णांक level = 1;

	अगर (out_क्रमmat_is_json()) अणु
		snम_लिखो(header, माप(header), "package-%d:die-%d:cpu-%d",
			 get_physical_package_id(cpu), get_physical_die_id(cpu),
			 cpu);
		क्रमmat_and_prपूर्णांक(outf, level++, header, शून्य);
	पूर्ण अन्यथा अणु
		snम_लिखो(header, माप(header), "package-%d",
			 get_physical_package_id(cpu));
		क्रमmat_and_prपूर्णांक(outf, level++, header, शून्य);
		snम_लिखो(header, माप(header), "die-%d",
			 get_physical_die_id(cpu));
		क्रमmat_and_prपूर्णांक(outf, level++, header, शून्य);
		snम_लिखो(header, माप(header), "cpu-%d", cpu);
		क्रमmat_and_prपूर्णांक(outf, level++, header, शून्य);
	पूर्ण

	अगर (str0 && !val)
		snम_लिखो(value, माप(value), "%s", str0);
	अन्यथा अगर (str1 && val)
		snम_लिखो(value, माप(value), "%s", str1);
	अन्यथा
		snम_लिखो(value, माप(value), "%u", val);
	क्रमmat_and_prपूर्णांक(outf, level, prefix, value);

	क्रमmat_and_prपूर्णांक(outf, 1, शून्य, शून्य);
पूर्ण

व्योम isst_ctdp_display_inक्रमmation(पूर्णांक cpu, खाता *outf, पूर्णांक tdp_level,
				   काष्ठा isst_pkg_ctdp *pkg_dev)
अणु
	अक्षर header[256];
	अक्षर value[512];
	अटल पूर्णांक level;
	पूर्णांक i;

	अगर (pkg_dev->processed)
		level = prपूर्णांक_package_info(cpu, outf);

	क्रम (i = 0; i <= pkg_dev->levels; ++i) अणु
		काष्ठा isst_pkg_ctdp_level_info *ctdp_level;
		पूर्णांक j;

		ctdp_level = &pkg_dev->ctdp_level[i];
		अगर (!ctdp_level->processed)
			जारी;

		snम_लिखो(header, माप(header), "perf-profile-level-%d",
			 ctdp_level->level);
		क्रमmat_and_prपूर्णांक(outf, level + 1, header, शून्य);

		snम_लिखो(header, माप(header), "cpu-count");
		j = get_cpu_count(get_physical_die_id(cpu),
				  get_physical_die_id(cpu));
		snम_लिखो(value, माप(value), "%d", j);
		क्रमmat_and_prपूर्णांक(outf, level + 2, header, value);

		j = CPU_COUNT_S(ctdp_level->core_cpumask_size,
				ctdp_level->core_cpumask);
		अगर (j) अणु
			snम_लिखो(header, माप(header), "enable-cpu-count");
			snम_लिखो(value, माप(value), "%d", j);
			क्रमmat_and_prपूर्णांक(outf, level + 2, header, value);
		पूर्ण

		अगर (ctdp_level->core_cpumask_size) अणु
			snम_लिखो(header, माप(header), "enable-cpu-mask");
			prपूर्णांकcpumask(माप(value), value,
				     ctdp_level->core_cpumask_size,
				     ctdp_level->core_cpumask);
			क्रमmat_and_prपूर्णांक(outf, level + 2, header, value);

			snम_लिखो(header, माप(header), "enable-cpu-list");
			prपूर्णांकcpulist(माप(value), value,
				     ctdp_level->core_cpumask_size,
				     ctdp_level->core_cpumask);
			क्रमmat_and_prपूर्णांक(outf, level + 2, header, value);
		पूर्ण

		snम_लिखो(header, माप(header), "thermal-design-power-ratio");
		snम_लिखो(value, माप(value), "%d", ctdp_level->tdp_ratio);
		क्रमmat_and_prपूर्णांक(outf, level + 2, header, value);

		snम_लिखो(header, माप(header), "base-frequency(MHz)");
		अगर (!ctdp_level->sse_p1)
			ctdp_level->sse_p1 = ctdp_level->tdp_ratio;
		snम_लिखो(value, माप(value), "%d",
			  ctdp_level->sse_p1 * DISP_FREQ_MULTIPLIER);
		क्रमmat_and_prपूर्णांक(outf, level + 2, header, value);

		अगर (ctdp_level->avx2_p1) अणु
			snम_लिखो(header, माप(header), "base-frequency-avx2(MHz)");
			snम_लिखो(value, माप(value), "%d",
				 ctdp_level->avx2_p1 * DISP_FREQ_MULTIPLIER);
			क्रमmat_and_prपूर्णांक(outf, level + 2, header, value);
		पूर्ण

		अगर (ctdp_level->avx512_p1) अणु
			snम_लिखो(header, माप(header), "base-frequency-avx512(MHz)");
			snम_लिखो(value, माप(value), "%d",
				 ctdp_level->avx512_p1 * DISP_FREQ_MULTIPLIER);
			क्रमmat_and_prपूर्णांक(outf, level + 2, header, value);
		पूर्ण

		अगर (ctdp_level->uncore_p1) अणु
			snम_लिखो(header, माप(header), "uncore-frequency-min(MHz)");
			snम_लिखो(value, माप(value), "%d",
				 ctdp_level->uncore_p1 * DISP_FREQ_MULTIPLIER);
			क्रमmat_and_prपूर्णांक(outf, level + 2, header, value);
		पूर्ण

		अगर (ctdp_level->uncore_p0) अणु
			snम_लिखो(header, माप(header), "uncore-frequency-max(MHz)");
			snम_लिखो(value, माप(value), "%d",
				 ctdp_level->uncore_p0 * DISP_FREQ_MULTIPLIER);
			क्रमmat_and_prपूर्णांक(outf, level + 2, header, value);
		पूर्ण

		अगर (ctdp_level->mem_freq) अणु
			snम_लिखो(header, माप(header), "mem-frequency(MHz)");
			snम_लिखो(value, माप(value), "%d",
				 ctdp_level->mem_freq * DISP_FREQ_MULTIPLIER);
			क्रमmat_and_prपूर्णांक(outf, level + 2, header, value);
		पूर्ण

		snम_लिखो(header, माप(header),
			 "speed-select-turbo-freq");
		अगर (ctdp_level->fact_support) अणु
			अगर (ctdp_level->fact_enabled)
				snम_लिखो(value, माप(value), "enabled");
			अन्यथा
				snम_लिखो(value, माप(value), "disabled");
		पूर्ण अन्यथा
			snम_लिखो(value, माप(value), "unsupported");
		क्रमmat_and_prपूर्णांक(outf, level + 2, header, value);

		snम_लिखो(header, माप(header),
			 "speed-select-base-freq");
		अगर (ctdp_level->pbf_support) अणु
			अगर (ctdp_level->pbf_enabled)
				snम_लिखो(value, माप(value), "enabled");
			अन्यथा
				snम_लिखो(value, माप(value), "disabled");
		पूर्ण अन्यथा
			snम_लिखो(value, माप(value), "unsupported");
		क्रमmat_and_prपूर्णांक(outf, level + 2, header, value);

		snम_लिखो(header, माप(header),
			 "speed-select-core-power");
		अगर (ctdp_level->sst_cp_support) अणु
			अगर (ctdp_level->sst_cp_enabled)
				snम_लिखो(value, माप(value), "enabled");
			अन्यथा
				snम_लिखो(value, माप(value), "disabled");
		पूर्ण अन्यथा
			snम_लिखो(value, माप(value), "unsupported");
		क्रमmat_and_prपूर्णांक(outf, level + 2, header, value);

		अगर (is_clx_n_platक्रमm()) अणु
			अगर (ctdp_level->pbf_support)
				_isst_pbf_display_inक्रमmation(cpu, outf,
							      tdp_level,
							  &ctdp_level->pbf_info,
							      level + 2);
			जारी;
		पूर्ण

		अगर (ctdp_level->pkg_tdp) अणु
			snम_लिखो(header, माप(header), "thermal-design-power(W)");
			snम_लिखो(value, माप(value), "%d", ctdp_level->pkg_tdp);
			क्रमmat_and_prपूर्णांक(outf, level + 2, header, value);
		पूर्ण

		अगर (ctdp_level->t_proc_hot) अणु
			snम_लिखो(header, माप(header), "tjunction-max(C)");
			snम_लिखो(value, माप(value), "%d", ctdp_level->t_proc_hot);
			क्रमmat_and_prपूर्णांक(outf, level + 2, header, value);
		पूर्ण

		snम_लिखो(header, माप(header), "turbo-ratio-limits-sse");
		क्रमmat_and_prपूर्णांक(outf, level + 2, header, शून्य);
		क्रम (j = 0; j < 8; ++j) अणु
			snम_लिखो(header, माप(header), "bucket-%d", j);
			क्रमmat_and_prपूर्णांक(outf, level + 3, header, शून्य);

			snम_लिखो(header, माप(header), "core-count");
			snम_लिखो(value, माप(value), "%llu", (ctdp_level->buckets_info >> (j * 8)) & 0xff);
			क्रमmat_and_prपूर्णांक(outf, level + 4, header, value);

			snम_लिखो(header, माप(header),
				"max-turbo-frequency(MHz)");
			snम_लिखो(value, माप(value), "%d",
				 ctdp_level->trl_sse_active_cores[j] *
				  DISP_FREQ_MULTIPLIER);
			क्रमmat_and_prपूर्णांक(outf, level + 4, header, value);
		पूर्ण

		अगर (ctdp_level->trl_avx_active_cores[0]) अणु
			snम_लिखो(header, माप(header), "turbo-ratio-limits-avx2");
			क्रमmat_and_prपूर्णांक(outf, level + 2, header, शून्य);
			क्रम (j = 0; j < 8; ++j) अणु
				snम_लिखो(header, माप(header), "bucket-%d", j);
				क्रमmat_and_prपूर्णांक(outf, level + 3, header, शून्य);

				snम_लिखो(header, माप(header), "core-count");
				snम_लिखो(value, माप(value), "%llu", (ctdp_level->buckets_info >> (j * 8)) & 0xff);
				क्रमmat_and_prपूर्णांक(outf, level + 4, header, value);

				snम_लिखो(header, माप(header), "max-turbo-frequency(MHz)");
				snम_लिखो(value, माप(value), "%d", ctdp_level->trl_avx_active_cores[j] * DISP_FREQ_MULTIPLIER);
				क्रमmat_and_prपूर्णांक(outf, level + 4, header, value);
			पूर्ण
		पूर्ण

		अगर (ctdp_level->trl_avx_512_active_cores[0]) अणु
			snम_लिखो(header, माप(header), "turbo-ratio-limits-avx512");
			क्रमmat_and_prपूर्णांक(outf, level + 2, header, शून्य);
			क्रम (j = 0; j < 8; ++j) अणु
				snम_लिखो(header, माप(header), "bucket-%d", j);
				क्रमmat_and_prपूर्णांक(outf, level + 3, header, शून्य);

				snम_लिखो(header, माप(header), "core-count");
				snम_लिखो(value, माप(value), "%llu", (ctdp_level->buckets_info >> (j * 8)) & 0xff);
				क्रमmat_and_prपूर्णांक(outf, level + 4, header, value);

				snम_लिखो(header, माप(header), "max-turbo-frequency(MHz)");
				snम_लिखो(value, माप(value), "%d", ctdp_level->trl_avx_512_active_cores[j] * DISP_FREQ_MULTIPLIER);
				क्रमmat_and_prपूर्णांक(outf, level + 4, header, value);
			पूर्ण
		पूर्ण

		अगर (ctdp_level->pbf_support)
			_isst_pbf_display_inक्रमmation(cpu, outf, i,
						      &ctdp_level->pbf_info,
						      level + 2);
		अगर (ctdp_level->fact_support)
			_isst_fact_display_inक्रमmation(cpu, outf, i, 0xff, 0xff,
						       &ctdp_level->fact_info,
						       level + 2);
	पूर्ण

	क्रमmat_and_prपूर्णांक(outf, 1, शून्य, शून्य);
पूर्ण

अटल पूर्णांक start;
व्योम isst_ctdp_display_inक्रमmation_start(खाता *outf)
अणु
	last_level = 0;
	क्रमmat_and_prपूर्णांक(outf, 0, "start", शून्य);
	start = 1;
पूर्ण

व्योम isst_ctdp_display_inक्रमmation_end(खाता *outf)
अणु
	क्रमmat_and_prपूर्णांक(outf, 0, शून्य, शून्य);
	start = 0;
पूर्ण

व्योम isst_pbf_display_inक्रमmation(पूर्णांक cpu, खाता *outf, पूर्णांक level,
				  काष्ठा isst_pbf_info *pbf_info)
अणु
	पूर्णांक _level;

	_level = prपूर्णांक_package_info(cpu, outf);
	_isst_pbf_display_inक्रमmation(cpu, outf, level, pbf_info, _level + 1);
	क्रमmat_and_prपूर्णांक(outf, 1, शून्य, शून्य);
पूर्ण

व्योम isst_fact_display_inक्रमmation(पूर्णांक cpu, खाता *outf, पूर्णांक level,
				   पूर्णांक fact_bucket, पूर्णांक fact_avx,
				   काष्ठा isst_fact_info *fact_info)
अणु
	पूर्णांक _level;

	_level = prपूर्णांक_package_info(cpu, outf);
	_isst_fact_display_inक्रमmation(cpu, outf, level, fact_bucket, fact_avx,
				       fact_info, _level + 1);
	क्रमmat_and_prपूर्णांक(outf, 1, शून्य, शून्य);
पूर्ण

व्योम isst_clos_display_inक्रमmation(पूर्णांक cpu, खाता *outf, पूर्णांक clos,
				   काष्ठा isst_clos_config *clos_config)
अणु
	अक्षर header[256];
	अक्षर value[256];
	पूर्णांक level;

	level = prपूर्णांक_package_info(cpu, outf);

	snम_लिखो(header, माप(header), "core-power");
	क्रमmat_and_prपूर्णांक(outf, level + 1, header, शून्य);

	snम_लिखो(header, माप(header), "clos");
	snम_लिखो(value, माप(value), "%d", clos);
	क्रमmat_and_prपूर्णांक(outf, level + 2, header, value);

	snम_लिखो(header, माप(header), "epp");
	snम_लिखो(value, माप(value), "%d", clos_config->epp);
	क्रमmat_and_prपूर्णांक(outf, level + 2, header, value);

	snम_लिखो(header, माप(header), "clos-proportional-priority");
	snम_लिखो(value, माप(value), "%d", clos_config->clos_prop_prio);
	क्रमmat_and_prपूर्णांक(outf, level + 2, header, value);

	snम_लिखो(header, माप(header), "clos-min");
	snम_लिखो(value, माप(value), "%d MHz", clos_config->clos_min * DISP_FREQ_MULTIPLIER);
	क्रमmat_and_prपूर्णांक(outf, level + 2, header, value);

	snम_लिखो(header, माप(header), "clos-max");
	अगर (clos_config->clos_max == 0xff)
		snम_लिखो(value, माप(value), "Max Turbo frequency");
	अन्यथा
		snम_लिखो(value, माप(value), "%d MHz", clos_config->clos_max * DISP_FREQ_MULTIPLIER);
	क्रमmat_and_prपूर्णांक(outf, level + 2, header, value);

	snम_लिखो(header, माप(header), "clos-desired");
	snम_लिखो(value, माप(value), "%d MHz", clos_config->clos_desired * DISP_FREQ_MULTIPLIER);
	क्रमmat_and_prपूर्णांक(outf, level + 2, header, value);

	क्रमmat_and_prपूर्णांक(outf, level, शून्य, शून्य);
पूर्ण

व्योम isst_clos_display_clos_inक्रमmation(पूर्णांक cpu, खाता *outf,
					पूर्णांक clos_enable, पूर्णांक type,
					पूर्णांक state, पूर्णांक cap)
अणु
	अक्षर header[256];
	अक्षर value[256];
	पूर्णांक level;

	level = prपूर्णांक_package_info(cpu, outf);

	snम_लिखो(header, माप(header), "core-power");
	क्रमmat_and_prपूर्णांक(outf, level + 1, header, शून्य);

	snम_लिखो(header, माप(header), "support-status");
	अगर (cap)
		snम_लिखो(value, माप(value), "supported");
	अन्यथा
		snम_लिखो(value, माप(value), "unsupported");
	क्रमmat_and_prपूर्णांक(outf, level + 2, header, value);

	snम_लिखो(header, माप(header), "enable-status");
	अगर (state)
		snम_लिखो(value, माप(value), "enabled");
	अन्यथा
		snम_लिखो(value, माप(value), "disabled");
	क्रमmat_and_prपूर्णांक(outf, level + 2, header, value);

	snम_लिखो(header, माप(header), "clos-enable-status");
	अगर (clos_enable)
		snम_लिखो(value, माप(value), "enabled");
	अन्यथा
		snम_लिखो(value, माप(value), "disabled");
	क्रमmat_and_prपूर्णांक(outf, level + 2, header, value);

	snम_लिखो(header, माप(header), "priority-type");
	अगर (type)
		snम_लिखो(value, माप(value), "ordered");
	अन्यथा
		snम_लिखो(value, माप(value), "proportional");
	क्रमmat_and_prपूर्णांक(outf, level + 2, header, value);

	क्रमmat_and_prपूर्णांक(outf, level, शून्य, शून्य);
पूर्ण

व्योम isst_clos_display_assoc_inक्रमmation(पूर्णांक cpu, खाता *outf, पूर्णांक clos)
अणु
	अक्षर header[256];
	अक्षर value[256];
	पूर्णांक level;

	level = prपूर्णांक_package_info(cpu, outf);

	snम_लिखो(header, माप(header), "get-assoc");
	क्रमmat_and_prपूर्णांक(outf, level + 1, header, शून्य);

	snम_लिखो(header, माप(header), "clos");
	snम_लिखो(value, माप(value), "%d", clos);
	क्रमmat_and_prपूर्णांक(outf, level + 2, header, value);

	क्रमmat_and_prपूर्णांक(outf, level, शून्य, शून्य);
पूर्ण

व्योम isst_display_result(पूर्णांक cpu, खाता *outf, अक्षर *feature, अक्षर *cmd,
			 पूर्णांक result)
अणु
	अक्षर header[256];
	अक्षर value[256];
	पूर्णांक level = 3;

	अगर (cpu >= 0)
		level = prपूर्णांक_package_info(cpu, outf);

	snम_लिखो(header, माप(header), "%s", feature);
	क्रमmat_and_prपूर्णांक(outf, level + 1, header, शून्य);
	snम_लिखो(header, माप(header), "%s", cmd);
	अगर (!result)
		snम_लिखो(value, माप(value), "success");
	अन्यथा
		snम_लिखो(value, माप(value), "failed(error %d)", result);
	क्रमmat_and_prपूर्णांक(outf, level + 2, header, value);

	क्रमmat_and_prपूर्णांक(outf, level, शून्य, शून्य);
पूर्ण

व्योम isst_display_error_info_message(पूर्णांक error, अक्षर *msg, पूर्णांक arg_valid, पूर्णांक arg)
अणु
	खाता *outf = get_output_file();
	अटल पूर्णांक error_index;
	अक्षर header[256];
	अक्षर value[256];

	अगर (!out_क्रमmat_is_json()) अणु
		अगर (arg_valid)
			snम_लिखो(value, माप(value), "%s %d", msg, arg);
		अन्यथा
			snम_लिखो(value, माप(value), "%s", msg);

		अगर (error)
			ख_लिखो(outf, "Error: %s\n", value);
		अन्यथा
			ख_लिखो(outf, "Information: %s\n", value);
		वापस;
	पूर्ण

	अगर (!start)
		क्रमmat_and_prपूर्णांक(outf, 0, "start", शून्य);

	अगर (error)
		snम_लिखो(header, माप(header), "Error%d", error_index++);
	अन्यथा
		snम_लिखो(header, माप(header), "Information:%d", error_index++);
	क्रमmat_and_prपूर्णांक(outf, 1, header, शून्य);

	snम_लिखो(header, माप(header), "message");
	अगर (arg_valid)
		snम_लिखो(value, माप(value), "%s %d", msg, arg);
	अन्यथा
		snम_लिखो(value, माप(value), "%s", msg);

	क्रमmat_and_prपूर्णांक(outf, 2, header, value);
	क्रमmat_and_prपूर्णांक(outf, 1, शून्य, शून्य);
	अगर (!start)
		क्रमmat_and_prपूर्णांक(outf, 0, शून्य, शून्य);
पूर्ण

व्योम isst_trl_display_inक्रमmation(पूर्णांक cpu, खाता *outf, अचिन्हित दीर्घ दीर्घ trl)
अणु
	अक्षर header[256];
	अक्षर value[256];
	पूर्णांक level;

	level = prपूर्णांक_package_info(cpu, outf);

	snम_लिखो(header, माप(header), "get-trl");
	क्रमmat_and_prपूर्णांक(outf, level + 1, header, शून्य);

	snम_लिखो(header, माप(header), "trl");
	snम_लिखो(value, माप(value), "0x%llx", trl);
	क्रमmat_and_prपूर्णांक(outf, level + 2, header, value);

	क्रमmat_and_prपूर्णांक(outf, level, शून्य, शून्य);
पूर्ण
