<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * PowerPC BookIII S hardware अवरोधpoपूर्णांक definitions
 *
 * Copyright 2010, IBM Corporation.
 * Author: K.Prasad <prasad@linux.vnet.ibm.com>
 */

#अगर_अघोषित _PPC_BOOK3S_64_HW_BREAKPOINT_H
#घोषणा _PPC_BOOK3S_64_HW_BREAKPOINT_H

#समावेश <यंत्र/cpu_has_feature.h>
#समावेश <यंत्र/inst.h>

#अगर_घोषित	__KERNEL__
काष्ठा arch_hw_अवरोधpoपूर्णांक अणु
	अचिन्हित दीर्घ	address;
	u16		type;
	u16		len; /* length of the target data symbol */
	u16		hw_len; /* length programmed in hw */
	u8		flags;
पूर्ण;

/* Note: Don't change the first 6 bits below as they are in the same order
 * as the dabr and dabrx.
 */
#घोषणा HW_BRK_TYPE_READ		0x01
#घोषणा HW_BRK_TYPE_WRITE		0x02
#घोषणा HW_BRK_TYPE_TRANSLATE		0x04
#घोषणा HW_BRK_TYPE_USER		0x08
#घोषणा HW_BRK_TYPE_KERNEL		0x10
#घोषणा HW_BRK_TYPE_HYP			0x20
#घोषणा HW_BRK_TYPE_EXTRANEOUS_IRQ	0x80

/* bits that overlap with the bottom 3 bits of the dabr */
#घोषणा HW_BRK_TYPE_RDWR	(HW_BRK_TYPE_READ | HW_BRK_TYPE_WRITE)
#घोषणा HW_BRK_TYPE_DABR	(HW_BRK_TYPE_RDWR | HW_BRK_TYPE_TRANSLATE)
#घोषणा HW_BRK_TYPE_PRIV_ALL	(HW_BRK_TYPE_USER | HW_BRK_TYPE_KERNEL | \
				 HW_BRK_TYPE_HYP)

#घोषणा HW_BRK_FLAG_DISABLED	0x1

/* Minimum granularity */
#अगर_घोषित CONFIG_PPC_8xx
#घोषणा HW_BREAKPOINT_SIZE  0x4
#अन्यथा
#घोषणा HW_BREAKPOINT_SIZE  0x8
#पूर्ण_अगर
#घोषणा HW_BREAKPOINT_SIZE_QUADWORD	0x10

#घोषणा DABR_MAX_LEN	8
#घोषणा DAWR_MAX_LEN	512

अटल अंतरभूत पूर्णांक nr_wp_slots(व्योम)
अणु
	वापस cpu_has_feature(CPU_FTR_DAWR1) ? 2 : 1;
पूर्ण

bool wp_check_स्थिरraपूर्णांकs(काष्ठा pt_regs *regs, काष्ठा ppc_inst instr,
			  अचिन्हित दीर्घ ea, पूर्णांक type, पूर्णांक size,
			  काष्ठा arch_hw_अवरोधpoपूर्णांक *info);

व्योम wp_get_instr_detail(काष्ठा pt_regs *regs, काष्ठा ppc_inst *instr,
			 पूर्णांक *type, पूर्णांक *size, अचिन्हित दीर्घ *ea);

#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT
#समावेश <linux/kdebug.h>
#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/debug.h>

काष्ठा perf_event_attr;
काष्ठा perf_event;
काष्ठा pmu;
काष्ठा perf_sample_data;
काष्ठा task_काष्ठा;

बाह्य पूर्णांक hw_अवरोधpoपूर्णांक_slots(पूर्णांक type);
बाह्य पूर्णांक arch_bp_generic_fields(पूर्णांक type, पूर्णांक *gen_bp_type);
बाह्य पूर्णांक arch_check_bp_in_kernelspace(काष्ठा arch_hw_अवरोधpoपूर्णांक *hw);
बाह्य पूर्णांक hw_अवरोधpoपूर्णांक_arch_parse(काष्ठा perf_event *bp,
				    स्थिर काष्ठा perf_event_attr *attr,
				    काष्ठा arch_hw_अवरोधpoपूर्णांक *hw);
बाह्य पूर्णांक hw_अवरोधpoपूर्णांक_exceptions_notअगरy(काष्ठा notअगरier_block *unused,
						अचिन्हित दीर्घ val, व्योम *data);
पूर्णांक arch_install_hw_अवरोधpoपूर्णांक(काष्ठा perf_event *bp);
व्योम arch_uninstall_hw_अवरोधpoपूर्णांक(काष्ठा perf_event *bp);
व्योम hw_अवरोधpoपूर्णांक_pmu_पढ़ो(काष्ठा perf_event *bp);
बाह्य व्योम flush_ptrace_hw_अवरोधpoपूर्णांक(काष्ठा task_काष्ठा *tsk);

बाह्य काष्ठा pmu perf_ops_bp;
बाह्य व्योम ptrace_triggered(काष्ठा perf_event *bp,
			काष्ठा perf_sample_data *data, काष्ठा pt_regs *regs);
अटल अंतरभूत व्योम hw_अवरोधpoपूर्णांक_disable(व्योम)
अणु
	पूर्णांक i;
	काष्ठा arch_hw_अवरोधpoपूर्णांक null_brk = अणु0पूर्ण;

	अगर (!ppc_अवरोधpoपूर्णांक_available())
		वापस;

	क्रम (i = 0; i < nr_wp_slots(); i++)
		__set_अवरोधpoपूर्णांक(i, &null_brk);
पूर्ण
बाह्य व्योम thपढ़ो_change_pc(काष्ठा task_काष्ठा *tsk, काष्ठा pt_regs *regs);
पूर्णांक hw_अवरोधpoपूर्णांक_handler(काष्ठा die_args *args);

#अन्यथा	/* CONFIG_HAVE_HW_BREAKPOINT */
अटल अंतरभूत व्योम hw_अवरोधpoपूर्णांक_disable(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम thपढ़ो_change_pc(काष्ठा task_काष्ठा *tsk,
					काष्ठा pt_regs *regs) अणु पूर्ण

#पूर्ण_अगर	/* CONFIG_HAVE_HW_BREAKPOINT */


#अगर_घोषित CONFIG_PPC_DAWR
बाह्य bool dawr_क्रमce_enable;
अटल अंतरभूत bool dawr_enabled(व्योम)
अणु
	वापस dawr_क्रमce_enable;
पूर्ण
पूर्णांक set_dawr(पूर्णांक nr, काष्ठा arch_hw_अवरोधpoपूर्णांक *brk);
#अन्यथा
अटल अंतरभूत bool dawr_enabled(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत पूर्णांक set_dawr(पूर्णांक nr, काष्ठा arch_hw_अवरोधpoपूर्णांक *brk) अणु वापस -1; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर	/* __KERNEL__ */
#पूर्ण_अगर	/* _PPC_BOOK3S_64_HW_BREAKPOINT_H */
