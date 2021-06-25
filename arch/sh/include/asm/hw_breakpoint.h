<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_HW_BREAKPOINT_H
#घोषणा __ASM_SH_HW_BREAKPOINT_H

#समावेश <uapi/यंत्र/hw_अवरोधpoपूर्णांक.h>

#घोषणा __ARCH_HW_BREAKPOINT_H

#समावेश <linux/kdebug.h>
#समावेश <linux/types.h>

काष्ठा arch_hw_अवरोधpoपूर्णांक अणु
	अचिन्हित दीर्घ	address;
	u16		len;
	u16		type;
पूर्ण;

क्रमागत अणु
	SH_BREAKPOINT_READ	= (1 << 1),
	SH_BREAKPOINT_WRITE	= (1 << 2),
	SH_BREAKPOINT_RW	= SH_BREAKPOINT_READ | SH_BREAKPOINT_WRITE,

	SH_BREAKPOINT_LEN_1	= (1 << 12),
	SH_BREAKPOINT_LEN_2	= (1 << 13),
	SH_BREAKPOINT_LEN_4	= SH_BREAKPOINT_LEN_1 | SH_BREAKPOINT_LEN_2,
	SH_BREAKPOINT_LEN_8	= (1 << 14),
पूर्ण;

काष्ठा sh_ubc अणु
	स्थिर अक्षर	*name;
	अचिन्हित पूर्णांक	num_events;
	अचिन्हित पूर्णांक	trap_nr;
	व्योम		(*enable)(काष्ठा arch_hw_अवरोधpoपूर्णांक *, पूर्णांक);
	व्योम		(*disable)(काष्ठा arch_hw_अवरोधpoपूर्णांक *, पूर्णांक);
	व्योम		(*enable_all)(अचिन्हित दीर्घ);
	व्योम		(*disable_all)(व्योम);
	अचिन्हित दीर्घ	(*active_mask)(व्योम);
	अचिन्हित दीर्घ	(*triggered_mask)(व्योम);
	व्योम		(*clear_triggered_mask)(अचिन्हित दीर्घ);
	काष्ठा clk	*clk;	/* optional पूर्णांकerface घड़ी / MSTP bit */
पूर्ण;

काष्ठा perf_event_attr;
काष्ठा perf_event;
काष्ठा task_काष्ठा;
काष्ठा pmu;

/* Maximum number of UBC channels */
#घोषणा HBP_NUM		2

अटल अंतरभूत पूर्णांक hw_अवरोधpoपूर्णांक_slots(पूर्णांक type)
अणु
	वापस HBP_NUM;
पूर्ण

/* arch/sh/kernel/hw_अवरोधpoपूर्णांक.c */
बाह्य पूर्णांक arch_check_bp_in_kernelspace(काष्ठा arch_hw_अवरोधpoपूर्णांक *hw);
बाह्य पूर्णांक hw_अवरोधpoपूर्णांक_arch_parse(काष्ठा perf_event *bp,
				    स्थिर काष्ठा perf_event_attr *attr,
				    काष्ठा arch_hw_अवरोधpoपूर्णांक *hw);
बाह्य पूर्णांक hw_अवरोधpoपूर्णांक_exceptions_notअगरy(काष्ठा notअगरier_block *unused,
					   अचिन्हित दीर्घ val, व्योम *data);

पूर्णांक arch_install_hw_अवरोधpoपूर्णांक(काष्ठा perf_event *bp);
व्योम arch_uninstall_hw_अवरोधpoपूर्णांक(काष्ठा perf_event *bp);
व्योम hw_अवरोधpoपूर्णांक_pmu_पढ़ो(काष्ठा perf_event *bp);

बाह्य व्योम arch_fill_perf_अवरोधpoपूर्णांक(काष्ठा perf_event *bp);
बाह्य पूर्णांक रेजिस्टर_sh_ubc(काष्ठा sh_ubc *);

बाह्य काष्ठा pmu perf_ops_bp;

#पूर्ण_अगर /* __ASM_SH_HW_BREAKPOINT_H */
