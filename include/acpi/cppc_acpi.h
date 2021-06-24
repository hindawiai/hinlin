<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * CPPC (Collaborative Processor Perक्रमmance Control) methods used
 * by CPUfreq drivers.
 *
 * (C) Copyright 2014, 2015 Linaro Ltd.
 * Author: Ashwin Chaugule <ashwin.chaugule@linaro.org>
 */

#अगर_अघोषित _CPPC_ACPI_H
#घोषणा _CPPC_ACPI_H

#समावेश <linux/acpi.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/types.h>

#समावेश <acpi/pcc.h>
#समावेश <acpi/processor.h>

/* Support CPPCv2 and CPPCv3  */
#घोषणा CPPC_V2_REV	2
#घोषणा CPPC_V3_REV	3
#घोषणा CPPC_V2_NUM_ENT	21
#घोषणा CPPC_V3_NUM_ENT	23

#घोषणा PCC_CMD_COMPLETE_MASK	(1 << 0)
#घोषणा PCC_ERROR_MASK		(1 << 2)

#घोषणा MAX_CPC_REG_ENT 21

/* CPPC specअगरic PCC commands. */
#घोषणा	CMD_READ 0
#घोषणा	CMD_WRITE 1

/* Each रेजिस्टर has the folowing क्रमmat. */
काष्ठा cpc_reg अणु
	u8 descriptor;
	u16 length;
	u8 space_id;
	u8 bit_width;
	u8 bit_offset;
	u8 access_width;
	u64 address;
पूर्ण __packed;

/*
 * Each entry in the CPC table is either
 * of type ACPI_TYPE_BUFFER or
 * ACPI_TYPE_INTEGER.
 */
काष्ठा cpc_रेजिस्टर_resource अणु
	acpi_object_type type;
	u64 __iomem *sys_mem_vaddr;
	जोड़ अणु
		काष्ठा cpc_reg reg;
		u64 पूर्णांक_value;
	पूर्ण cpc_entry;
पूर्ण;

/* Container to hold the CPC details क्रम each CPU */
काष्ठा cpc_desc अणु
	पूर्णांक num_entries;
	पूर्णांक version;
	पूर्णांक cpu_id;
	पूर्णांक ग_लिखो_cmd_status;
	पूर्णांक ग_लिखो_cmd_id;
	काष्ठा cpc_रेजिस्टर_resource cpc_regs[MAX_CPC_REG_ENT];
	काष्ठा acpi_psd_package करोमुख्य_info;
	काष्ठा kobject kobj;
पूर्ण;

/* These are indexes पूर्णांकo the per-cpu cpc_regs[]. Order is important. */
क्रमागत cppc_regs अणु
	HIGHEST_PERF,
	NOMINAL_PERF,
	LOW_NON_LINEAR_PERF,
	LOWEST_PERF,
	GUARANTEED_PERF,
	DESIRED_PERF,
	MIN_PERF,
	MAX_PERF,
	PERF_REDUC_TOLERANCE,
	TIME_WINDOW,
	CTR_WRAP_TIME,
	REFERENCE_CTR,
	DELIVERED_CTR,
	PERF_LIMITED,
	ENABLE,
	AUTO_SEL_ENABLE,
	AUTO_ACT_WINDOW,
	ENERGY_PERF,
	REFERENCE_PERF,
	LOWEST_FREQ,
	NOMINAL_FREQ,
पूर्ण;

/*
 * Categorization of रेजिस्टरs as described
 * in the ACPI v.5.1 spec.
 * XXX: Only filling up ones which are used by governors
 * today.
 */
काष्ठा cppc_perf_caps अणु
	u32 guaranteed_perf;
	u32 highest_perf;
	u32 nominal_perf;
	u32 lowest_perf;
	u32 lowest_nonlinear_perf;
	u32 lowest_freq;
	u32 nominal_freq;
पूर्ण;

काष्ठा cppc_perf_ctrls अणु
	u32 max_perf;
	u32 min_perf;
	u32 desired_perf;
पूर्ण;

काष्ठा cppc_perf_fb_ctrs अणु
	u64 reference;
	u64 delivered;
	u64 reference_perf;
	u64 wraparound_समय;
पूर्ण;

/* Per CPU container क्रम runसमय CPPC management. */
काष्ठा cppc_cpudata अणु
	काष्ठा list_head node;
	काष्ठा cppc_perf_caps perf_caps;
	काष्ठा cppc_perf_ctrls perf_ctrls;
	काष्ठा cppc_perf_fb_ctrs perf_fb_ctrs;
	अचिन्हित पूर्णांक shared_type;
	cpumask_var_t shared_cpu_map;
पूर्ण;

#अगर_घोषित CONFIG_ACPI_CPPC_LIB
बाह्य पूर्णांक cppc_get_desired_perf(पूर्णांक cpunum, u64 *desired_perf);
बाह्य पूर्णांक cppc_get_perf_ctrs(पूर्णांक cpu, काष्ठा cppc_perf_fb_ctrs *perf_fb_ctrs);
बाह्य पूर्णांक cppc_set_perf(पूर्णांक cpu, काष्ठा cppc_perf_ctrls *perf_ctrls);
बाह्य पूर्णांक cppc_get_perf_caps(पूर्णांक cpu, काष्ठा cppc_perf_caps *caps);
बाह्य bool acpi_cpc_valid(व्योम);
बाह्य पूर्णांक acpi_get_psd_map(अचिन्हित पूर्णांक cpu, काष्ठा cppc_cpudata *cpu_data);
बाह्य अचिन्हित पूर्णांक cppc_get_transition_latency(पूर्णांक cpu);
बाह्य bool cpc_ffh_supported(व्योम);
बाह्य पूर्णांक cpc_पढ़ो_ffh(पूर्णांक cpunum, काष्ठा cpc_reg *reg, u64 *val);
बाह्य पूर्णांक cpc_ग_लिखो_ffh(पूर्णांक cpunum, काष्ठा cpc_reg *reg, u64 val);
#अन्यथा /* !CONFIG_ACPI_CPPC_LIB */
अटल अंतरभूत पूर्णांक cppc_get_desired_perf(पूर्णांक cpunum, u64 *desired_perf)
अणु
	वापस -ENOTSUPP;
पूर्ण
अटल अंतरभूत पूर्णांक cppc_get_perf_ctrs(पूर्णांक cpu, काष्ठा cppc_perf_fb_ctrs *perf_fb_ctrs)
अणु
	वापस -ENOTSUPP;
पूर्ण
अटल अंतरभूत पूर्णांक cppc_set_perf(पूर्णांक cpu, काष्ठा cppc_perf_ctrls *perf_ctrls)
अणु
	वापस -ENOTSUPP;
पूर्ण
अटल अंतरभूत पूर्णांक cppc_get_perf_caps(पूर्णांक cpu, काष्ठा cppc_perf_caps *caps)
अणु
	वापस -ENOTSUPP;
पूर्ण
अटल अंतरभूत bool acpi_cpc_valid(व्योम)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत अचिन्हित पूर्णांक cppc_get_transition_latency(पूर्णांक cpu)
अणु
	वापस CPUFREQ_ETERNAL;
पूर्ण
अटल अंतरभूत bool cpc_ffh_supported(व्योम)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत पूर्णांक cpc_पढ़ो_ffh(पूर्णांक cpunum, काष्ठा cpc_reg *reg, u64 *val)
अणु
	वापस -ENOTSUPP;
पूर्ण
अटल अंतरभूत पूर्णांक cpc_ग_लिखो_ffh(पूर्णांक cpunum, काष्ठा cpc_reg *reg, u64 val)
अणु
	वापस -ENOTSUPP;
पूर्ण
#पूर्ण_अगर /* !CONFIG_ACPI_CPPC_LIB */

#पूर्ण_अगर /* _CPPC_ACPI_H*/
