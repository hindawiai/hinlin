<शैली गुरु>
/*
 * Xtensa hardware अवरोधpoपूर्णांकs/watchpoपूर्णांकs handling functions
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2016 Cadence Design Systems Inc.
 */

#अगर_अघोषित __ASM_XTENSA_HW_BREAKPOINT_H
#घोषणा __ASM_XTENSA_HW_BREAKPOINT_H

#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT

#समावेश <linux/kdebug.h>
#समावेश <linux/types.h>
#समावेश <uapi/linux/hw_अवरोधpoपूर्णांक.h>

/* Breakpoपूर्णांक */
#घोषणा XTENSA_BREAKPOINT_EXECUTE	0

/* Watchpoपूर्णांकs */
#घोषणा XTENSA_BREAKPOINT_LOAD		1
#घोषणा XTENSA_BREAKPOINT_STORE		2

काष्ठा arch_hw_अवरोधpoपूर्णांक अणु
	अचिन्हित दीर्घ address;
	u16 len;
	u16 type;
पूर्ण;

काष्ठा perf_event_attr;
काष्ठा perf_event;
काष्ठा pt_regs;
काष्ठा task_काष्ठा;

पूर्णांक hw_अवरोधpoपूर्णांक_slots(पूर्णांक type);
पूर्णांक arch_check_bp_in_kernelspace(काष्ठा arch_hw_अवरोधpoपूर्णांक *hw);
पूर्णांक hw_अवरोधpoपूर्णांक_arch_parse(काष्ठा perf_event *bp,
			     स्थिर काष्ठा perf_event_attr *attr,
			     काष्ठा arch_hw_अवरोधpoपूर्णांक *hw);
पूर्णांक hw_अवरोधpoपूर्णांक_exceptions_notअगरy(काष्ठा notअगरier_block *unused,
				    अचिन्हित दीर्घ val, व्योम *data);

पूर्णांक arch_install_hw_अवरोधpoपूर्णांक(काष्ठा perf_event *bp);
व्योम arch_uninstall_hw_अवरोधpoपूर्णांक(काष्ठा perf_event *bp);
व्योम hw_अवरोधpoपूर्णांक_pmu_पढ़ो(काष्ठा perf_event *bp);
पूर्णांक check_hw_अवरोधpoपूर्णांक(काष्ठा pt_regs *regs);
व्योम clear_ptrace_hw_अवरोधpoपूर्णांक(काष्ठा task_काष्ठा *tsk);

#अन्यथा

काष्ठा task_काष्ठा;

अटल अंतरभूत व्योम clear_ptrace_hw_अवरोधpoपूर्णांक(काष्ठा task_काष्ठा *tsk)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_HAVE_HW_BREAKPOINT */
#पूर्ण_अगर /* __ASM_XTENSA_HW_BREAKPOINT_H */
