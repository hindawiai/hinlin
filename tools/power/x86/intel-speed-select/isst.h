<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Intel Speed Select -- Enumerate and control features
 * Copyright (c) 2019 Intel Corporation.
 */

#अगर_अघोषित _ISST_H_
#घोषणा _ISST_H_

#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <sys/types.h>
#समावेश <sched.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/resource.h>
#समावेश <getopt.h>
#समावेश <err.h>
#समावेश <fcntl.h>
#समावेश <संकेत.स>
#समावेश <sys/समय.स>
#समावेश <सीमा.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <cpuid.h>
#समावेश <dirent.h>
#समावेश <त्रुटिसं.स>

#समावेश <मानकतर्क.स>
#समावेश <sys/ioctl.h>

#घोषणा BIT(x) (1 << (x))
#घोषणा BIT_ULL(nr) (1ULL << (nr))
#घोषणा GENMASK(h, l) (((~0UL) << (l)) & (~0UL >> (माप(दीर्घ) * 8 - 1 - (h))))
#घोषणा GENMASK_ULL(h, l)                                                      \
	(((~0ULL) << (l)) & (~0ULL >> (माप(दीर्घ दीर्घ) * 8 - 1 - (h))))

#घोषणा CONFIG_TDP				0x7f
#घोषणा CONFIG_TDP_GET_LEVELS_INFO		0x00
#घोषणा CONFIG_TDP_GET_TDP_CONTROL		0x01
#घोषणा CONFIG_TDP_SET_TDP_CONTROL		0x02
#घोषणा CONFIG_TDP_GET_TDP_INFO			0x03
#घोषणा CONFIG_TDP_GET_PWR_INFO			0x04
#घोषणा CONFIG_TDP_GET_TJMAX_INFO		0x05
#घोषणा CONFIG_TDP_GET_CORE_MASK		0x06
#घोषणा CONFIG_TDP_GET_TURBO_LIMIT_RATIOS	0x07
#घोषणा CONFIG_TDP_SET_LEVEL			0x08
#घोषणा CONFIG_TDP_GET_UNCORE_P0_P1_INFO	0X09
#घोषणा CONFIG_TDP_GET_P1_INFO			0x0a
#घोषणा CONFIG_TDP_GET_MEM_FREQ			0x0b

#घोषणा CONFIG_TDP_GET_FACT_HP_TURBO_LIMIT_NUMCORES	0x10
#घोषणा CONFIG_TDP_GET_FACT_HP_TURBO_LIMIT_RATIOS	0x11
#घोषणा CONFIG_TDP_GET_FACT_LP_CLIPPING_RATIO		0x12

#घोषणा CONFIG_TDP_PBF_GET_CORE_MASK_INFO	0x20
#घोषणा CONFIG_TDP_PBF_GET_P1HI_P1LO_INFO	0x21
#घोषणा CONFIG_TDP_PBF_GET_TJ_MAX_INFO		0x22
#घोषणा CONFIG_TDP_PBF_GET_TDP_INFO		0X23

#घोषणा CONFIG_CLOS				0xd0
#घोषणा CLOS_PQR_ASSOC				0x00
#घोषणा CLOS_PM_CLOS				0x01
#घोषणा CLOS_PM_QOS_CONFIG			0x02
#घोषणा CLOS_STATUS				0x03

#घोषणा MBOX_CMD_WRITE_BIT			0x08

#घोषणा PM_QOS_INFO_OFFSET			0x00
#घोषणा PM_QOS_CONFIG_OFFSET			0x04
#घोषणा PM_CLOS_OFFSET				0x08
#घोषणा PQR_ASSOC_OFFSET			0x20

#घोषणा READ_PM_CONFIG				0x94
#घोषणा WRITE_PM_CONFIG				0x95
#घोषणा PM_FEATURE				0x03

#घोषणा DISP_FREQ_MULTIPLIER 100

काष्ठा isst_clos_config अणु
	पूर्णांक pkg_id;
	पूर्णांक die_id;
	अचिन्हित अक्षर epp;
	अचिन्हित अक्षर clos_prop_prio;
	अचिन्हित अक्षर clos_min;
	अचिन्हित अक्षर clos_max;
	अचिन्हित अक्षर clos_desired;
पूर्ण;

काष्ठा isst_fact_bucket_info अणु
	पूर्णांक high_priority_cores_count;
	पूर्णांक sse_trl;
	पूर्णांक avx_trl;
	पूर्णांक avx512_trl;
पूर्ण;

काष्ठा isst_pbf_info अणु
	पूर्णांक pbf_acticated;
	पूर्णांक pbf_available;
	माप_प्रकार core_cpumask_size;
	cpu_set_t *core_cpumask;
	पूर्णांक p1_high;
	पूर्णांक p1_low;
	पूर्णांक t_control;
	पूर्णांक t_prochot;
	पूर्णांक tdp;
पूर्ण;

#घोषणा ISST_TRL_MAX_ACTIVE_CORES	8
#घोषणा ISST_FACT_MAX_BUCKETS		8
काष्ठा isst_fact_info अणु
	पूर्णांक lp_clipping_ratio_license_sse;
	पूर्णांक lp_clipping_ratio_license_avx2;
	पूर्णांक lp_clipping_ratio_license_avx512;
	काष्ठा isst_fact_bucket_info bucket_info[ISST_FACT_MAX_BUCKETS];
पूर्ण;

काष्ठा isst_pkg_ctdp_level_info अणु
	पूर्णांक processed;
	पूर्णांक control_cpu;
	पूर्णांक pkg_id;
	पूर्णांक die_id;
	पूर्णांक level;
	पूर्णांक fact_support;
	पूर्णांक pbf_support;
	पूर्णांक fact_enabled;
	पूर्णांक pbf_enabled;
	पूर्णांक sst_cp_support;
	पूर्णांक sst_cp_enabled;
	पूर्णांक tdp_ratio;
	पूर्णांक active;
	पूर्णांक tdp_control;
	पूर्णांक pkg_tdp;
	पूर्णांक pkg_min_घातer;
	पूर्णांक pkg_max_घातer;
	पूर्णांक fact;
	पूर्णांक t_proc_hot;
	पूर्णांक uncore_p0;
	पूर्णांक uncore_p1;
	पूर्णांक sse_p1;
	पूर्णांक avx2_p1;
	पूर्णांक avx512_p1;
	पूर्णांक mem_freq;
	माप_प्रकार core_cpumask_size;
	cpu_set_t *core_cpumask;
	पूर्णांक cpu_count;
	अचिन्हित दीर्घ दीर्घ buckets_info;
	पूर्णांक trl_sse_active_cores[ISST_TRL_MAX_ACTIVE_CORES];
	पूर्णांक trl_avx_active_cores[ISST_TRL_MAX_ACTIVE_CORES];
	पूर्णांक trl_avx_512_active_cores[ISST_TRL_MAX_ACTIVE_CORES];
	पूर्णांक kobj_bucket_index;
	पूर्णांक active_bucket;
	पूर्णांक fact_max_index;
	पूर्णांक fact_max_config;
	पूर्णांक pbf_found;
	पूर्णांक pbf_active;
	काष्ठा isst_pbf_info pbf_info;
	काष्ठा isst_fact_info fact_info;
पूर्ण;

#घोषणा ISST_MAX_TDP_LEVELS	(4 + 1) /* +1 क्रम base config */
काष्ठा isst_pkg_ctdp अणु
	पूर्णांक locked;
	पूर्णांक version;
	पूर्णांक processed;
	पूर्णांक levels;
	पूर्णांक current_level;
	पूर्णांक enabled;
	काष्ठा isst_pkg_ctdp_level_info ctdp_level[ISST_MAX_TDP_LEVELS];
पूर्ण;

बाह्य पूर्णांक get_topo_max_cpus(व्योम);
बाह्य पूर्णांक get_cpu_count(पूर्णांक pkg_id, पूर्णांक die_id);
बाह्य पूर्णांक get_max_punit_core_id(पूर्णांक pkg_id, पूर्णांक die_id);

/* Common पूर्णांकerfaces */
खाता *get_output_file(व्योम);
बाह्य व्योम debug_म_लिखो(स्थिर अक्षर *क्रमmat, ...);
बाह्य पूर्णांक out_क्रमmat_is_json(व्योम);
बाह्य पूर्णांक get_physical_package_id(पूर्णांक cpu);
बाह्य पूर्णांक get_physical_die_id(पूर्णांक cpu);
बाह्य माप_प्रकार alloc_cpu_set(cpu_set_t **cpu_set);
बाह्य व्योम मुक्त_cpu_set(cpu_set_t *cpu_set);
बाह्य पूर्णांक find_logical_cpu(पूर्णांक pkg_id, पूर्णांक die_id, पूर्णांक phy_cpu);
बाह्य पूर्णांक find_phy_cpu_num(पूर्णांक logical_cpu);
बाह्य पूर्णांक find_phy_core_num(पूर्णांक logical_cpu);
बाह्य व्योम set_cpu_mask_from_punit_coremask(पूर्णांक cpu,
					     अचिन्हित दीर्घ दीर्घ core_mask,
					     माप_प्रकार core_cpumask_size,
					     cpu_set_t *core_cpumask,
					     पूर्णांक *cpu_cnt);

बाह्य पूर्णांक isst_send_mbox_command(अचिन्हित पूर्णांक cpu, अचिन्हित अक्षर command,
				  अचिन्हित अक्षर sub_command,
				  अचिन्हित पूर्णांक ग_लिखो,
				  अचिन्हित पूर्णांक req_data, अचिन्हित पूर्णांक *resp);

बाह्य पूर्णांक isst_send_msr_command(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक command,
				 पूर्णांक ग_लिखो, अचिन्हित दीर्घ दीर्घ *req_resp);

बाह्य पूर्णांक isst_get_ctdp_levels(पूर्णांक cpu, काष्ठा isst_pkg_ctdp *pkg_dev);
बाह्य पूर्णांक isst_get_ctdp_control(पूर्णांक cpu, पूर्णांक config_index,
				 काष्ठा isst_pkg_ctdp_level_info *ctdp_level);
बाह्य पूर्णांक isst_get_coremask_info(पूर्णांक cpu, पूर्णांक config_index,
			   काष्ठा isst_pkg_ctdp_level_info *ctdp_level);
बाह्य पूर्णांक isst_get_process_ctdp(पूर्णांक cpu, पूर्णांक tdp_level,
				 काष्ठा isst_pkg_ctdp *pkg_dev);
बाह्य व्योम isst_get_process_ctdp_complete(पूर्णांक cpu,
					   काष्ठा isst_pkg_ctdp *pkg_dev);
बाह्य व्योम isst_ctdp_display_inक्रमmation(पूर्णांक cpu, खाता *outf, पूर्णांक tdp_level,
					  काष्ठा isst_pkg_ctdp *pkg_dev);
बाह्य व्योम isst_ctdp_display_core_info(पूर्णांक cpu, खाता *outf, अक्षर *prefix,
					अचिन्हित पूर्णांक val, अक्षर *str0, अक्षर *str1);
बाह्य व्योम isst_ctdp_display_inक्रमmation_start(खाता *outf);
बाह्य व्योम isst_ctdp_display_inक्रमmation_end(खाता *outf);
बाह्य व्योम isst_pbf_display_inक्रमmation(पूर्णांक cpu, खाता *outf, पूर्णांक level,
					 काष्ठा isst_pbf_info *info);
बाह्य पूर्णांक isst_set_tdp_level(पूर्णांक cpu, पूर्णांक tdp_level);
बाह्य पूर्णांक isst_set_tdp_level_msr(पूर्णांक cpu, पूर्णांक tdp_level);
बाह्य पूर्णांक isst_set_pbf_fact_status(पूर्णांक cpu, पूर्णांक pbf, पूर्णांक enable);
बाह्य पूर्णांक isst_get_pbf_info(पूर्णांक cpu, पूर्णांक level,
			     काष्ठा isst_pbf_info *pbf_info);
बाह्य व्योम isst_get_pbf_info_complete(काष्ठा isst_pbf_info *pbf_info);
बाह्य पूर्णांक isst_get_fact_info(पूर्णांक cpu, पूर्णांक level, पूर्णांक fact_bucket,
			      काष्ठा isst_fact_info *fact_info);
बाह्य पूर्णांक isst_get_fact_bucket_info(पूर्णांक cpu, पूर्णांक level,
				     काष्ठा isst_fact_bucket_info *bucket_info);
बाह्य व्योम isst_fact_display_inक्रमmation(पूर्णांक cpu, खाता *outf, पूर्णांक level,
					  पूर्णांक fact_bucket, पूर्णांक fact_avx,
					  काष्ठा isst_fact_info *fact_info);
बाह्य पूर्णांक isst_set_trl(पूर्णांक cpu, अचिन्हित दीर्घ दीर्घ trl);
बाह्य पूर्णांक isst_get_trl(पूर्णांक cpu, अचिन्हित दीर्घ दीर्घ *trl);
बाह्य पूर्णांक isst_set_trl_from_current_tdp(पूर्णांक cpu, अचिन्हित दीर्घ दीर्घ trl);
बाह्य पूर्णांक isst_get_config_tdp_lock_status(पूर्णांक cpu);

बाह्य पूर्णांक isst_pm_qos_config(पूर्णांक cpu, पूर्णांक enable_clos, पूर्णांक priority_type);
बाह्य पूर्णांक isst_pm_get_clos(पूर्णांक cpu, पूर्णांक clos,
			    काष्ठा isst_clos_config *clos_config);
बाह्य पूर्णांक isst_set_clos(पूर्णांक cpu, पूर्णांक clos,
			 काष्ठा isst_clos_config *clos_config);
बाह्य पूर्णांक isst_clos_associate(पूर्णांक cpu, पूर्णांक clos);
बाह्य पूर्णांक isst_clos_get_assoc_status(पूर्णांक cpu, पूर्णांक *clos_id);
बाह्य व्योम isst_clos_display_inक्रमmation(पूर्णांक cpu, खाता *outf, पूर्णांक clos,
					  काष्ठा isst_clos_config *clos_config);
बाह्य व्योम isst_clos_display_assoc_inक्रमmation(पूर्णांक cpu, खाता *outf, पूर्णांक clos);
बाह्य पूर्णांक isst_पढ़ो_reg(अचिन्हित लघु reg, अचिन्हित पूर्णांक *val);
बाह्य पूर्णांक isst_ग_लिखो_reg(पूर्णांक reg, अचिन्हित पूर्णांक val);

बाह्य व्योम isst_display_result(पूर्णांक cpu, खाता *outf, अक्षर *feature, अक्षर *cmd,
				पूर्णांक result);

बाह्य पूर्णांक isst_clos_get_clos_inक्रमmation(पूर्णांक cpu, पूर्णांक *enable, पूर्णांक *type);
बाह्य व्योम isst_clos_display_clos_inक्रमmation(पूर्णांक cpu, खाता *outf,
					       पूर्णांक clos_enable, पूर्णांक type,
					       पूर्णांक state, पूर्णांक cap);
बाह्य पूर्णांक is_clx_n_platक्रमm(व्योम);
बाह्य पूर्णांक get_cpufreq_base_freq(पूर्णांक cpu);
बाह्य पूर्णांक isst_पढ़ो_pm_config(पूर्णांक cpu, पूर्णांक *cp_state, पूर्णांक *cp_cap);
बाह्य व्योम isst_display_error_info_message(पूर्णांक error, अक्षर *msg, पूर्णांक arg_valid, पूर्णांक arg);
बाह्य पूर्णांक is_skx_based_platक्रमm(व्योम);
बाह्य व्योम isst_trl_display_inक्रमmation(पूर्णांक cpu, खाता *outf, अचिन्हित दीर्घ दीर्घ trl);
#पूर्ण_अगर
