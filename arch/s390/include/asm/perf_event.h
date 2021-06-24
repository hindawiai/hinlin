<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Perक्रमmance event support - s390 specअगरic definitions.
 *
 * Copyright IBM Corp. 2009, 2017
 * Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>
 *	      Hendrik Brueckner <brueckner@linux.vnet.ibm.com>
 */

#अगर_अघोषित _ASM_S390_PERF_EVENT_H
#घोषणा _ASM_S390_PERF_EVENT_H

#समावेश <linux/perf_event.h>
#समावेश <linux/device.h>
#समावेश <यंत्र/stacktrace.h>

/* Per-CPU flags क्रम PMU states */
#घोषणा PMU_F_RESERVED			0x1000
#घोषणा PMU_F_ENABLED			0x2000
#घोषणा PMU_F_IN_USE			0x4000
#घोषणा PMU_F_ERR_IBE			0x0100
#घोषणा PMU_F_ERR_LSDA			0x0200
#घोषणा PMU_F_ERR_MASK			(PMU_F_ERR_IBE|PMU_F_ERR_LSDA)

/* Perf definitions क्रम PMU event attributes in sysfs */
बाह्य __init स्थिर काष्ठा attribute_group **cpumf_cf_event_group(व्योम);
बाह्य sमाप_प्रकार cpumf_events_sysfs_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *page);
#घोषणा EVENT_VAR(_cat, _name)		event_attr_##_cat##_##_name
#घोषणा EVENT_PTR(_cat, _name)		(&EVENT_VAR(_cat, _name).attr.attr)

#घोषणा CPUMF_EVENT_ATTR(cat, name, id)			\
	PMU_EVENT_ATTR(name, EVENT_VAR(cat, name), id, cpumf_events_sysfs_show)
#घोषणा CPUMF_EVENT_PTR(cat, name)	EVENT_PTR(cat, name)


/* Perf callbacks */
काष्ठा pt_regs;
बाह्य अचिन्हित दीर्घ perf_inकाष्ठाion_poपूर्णांकer(काष्ठा pt_regs *regs);
बाह्य अचिन्हित दीर्घ perf_misc_flags(काष्ठा pt_regs *regs);
#घोषणा perf_misc_flags(regs) perf_misc_flags(regs)
#घोषणा perf_arch_bpf_user_pt_regs(regs) &regs->user_regs

/* Perf pt_regs extension क्रम sample-data-entry indicators */
काष्ठा perf_sf_sde_regs अणु
	अचिन्हित अक्षर in_guest:1;	  /* guest sample */
	अचिन्हित दीर्घ reserved:63;	  /* reserved */
पूर्ण;

/* Perf PMU definitions क्रम the counter facility */
#घोषणा PERF_CPUM_CF_MAX_CTR		0xffffUL  /* Max ctr क्रम ECCTR */

/* Perf PMU definitions क्रम the sampling facility */
#घोषणा PERF_CPUM_SF_MAX_CTR		2
#घोषणा PERF_EVENT_CPUM_SF		0xB0000UL /* Event: Basic-sampling */
#घोषणा PERF_EVENT_CPUM_SF_DIAG		0xBD000UL /* Event: Combined-sampling */
#घोषणा PERF_EVENT_CPUM_CF_DIAG		0xBC000UL /* Event: Counter sets */
#घोषणा PERF_CPUM_SF_BASIC_MODE		0x0001	  /* Basic-sampling flag */
#घोषणा PERF_CPUM_SF_DIAG_MODE		0x0002	  /* Diagnostic-sampling flag */
#घोषणा PERF_CPUM_SF_MODE_MASK		(PERF_CPUM_SF_BASIC_MODE| \
					 PERF_CPUM_SF_DIAG_MODE)
#घोषणा PERF_CPUM_SF_FULL_BLOCKS	0x0004	  /* Process full SDBs only */
#घोषणा PERF_CPUM_SF_FREQ_MODE		0x0008	  /* Sampling with frequency */

#घोषणा REG_NONE		0
#घोषणा REG_OVERFLOW		1
#घोषणा OVERFLOW_REG(hwc)	((hwc)->extra_reg.config)
#घोषणा SFB_ALLOC_REG(hwc)	((hwc)->extra_reg.alloc)
#घोषणा TEAR_REG(hwc)		((hwc)->last_tag)
#घोषणा SAMPL_RATE(hwc)		((hwc)->event_base)
#घोषणा SAMPL_FLAGS(hwc)	((hwc)->config_base)
#घोषणा SAMPL_DIAG_MODE(hwc)	(SAMPL_FLAGS(hwc) & PERF_CPUM_SF_DIAG_MODE)
#घोषणा SDB_FULL_BLOCKS(hwc)	(SAMPL_FLAGS(hwc) & PERF_CPUM_SF_FULL_BLOCKS)
#घोषणा SAMPLE_FREQ_MODE(hwc)	(SAMPL_FLAGS(hwc) & PERF_CPUM_SF_FREQ_MODE)

#घोषणा perf_arch_fetch_caller_regs(regs, __ip) करो अणु			\
	(regs)->psw.addr = (__ip);					\
	(regs)->gprs[15] = (अचिन्हित दीर्घ)__builtin_frame_address(0) -	\
		दुरत्व(काष्ठा stack_frame, back_chain);		\
पूर्ण जबतक (0)

#पूर्ण_अगर /* _ASM_S390_PERF_EVENT_H */
