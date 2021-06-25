<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_FTRACE_IRQ_H
#घोषणा _LINUX_FTRACE_IRQ_H

#अगर_घोषित CONFIG_HWLAT_TRACER
बाह्य bool trace_hwlat_callback_enabled;
बाह्य व्योम trace_hwlat_callback(bool enter);
#पूर्ण_अगर

अटल अंतरभूत व्योम ftrace_nmi_enter(व्योम)
अणु
#अगर_घोषित CONFIG_HWLAT_TRACER
	अगर (trace_hwlat_callback_enabled)
		trace_hwlat_callback(true);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम ftrace_nmi_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_HWLAT_TRACER
	अगर (trace_hwlat_callback_enabled)
		trace_hwlat_callback(false);
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* _LINUX_FTRACE_IRQ_H */
