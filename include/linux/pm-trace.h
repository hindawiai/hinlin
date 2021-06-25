<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित PM_TRACE_H
#घोषणा PM_TRACE_H

#समावेश <linux/types.h>
#अगर_घोषित CONFIG_PM_TRACE
#समावेश <यंत्र/pm-trace.h>

बाह्य पूर्णांक pm_trace_enabled;
बाह्य bool pm_trace_rtc_abused;

अटल अंतरभूत bool pm_trace_rtc_valid(व्योम)
अणु
	वापस !pm_trace_rtc_abused;
पूर्ण

अटल अंतरभूत पूर्णांक pm_trace_is_enabled(व्योम)
अणु
       वापस pm_trace_enabled;
पूर्ण

काष्ठा device;
बाह्य व्योम set_trace_device(काष्ठा device *);
बाह्य व्योम generate_pm_trace(स्थिर व्योम *tracedata, अचिन्हित पूर्णांक user);
बाह्य पूर्णांक show_trace_dev_match(अक्षर *buf, माप_प्रकार size);

#घोषणा TRACE_DEVICE(dev) करो अणु \
	अगर (pm_trace_enabled) \
		set_trace_device(dev); \
	पूर्ण जबतक(0)

#अन्यथा

अटल अंतरभूत bool pm_trace_rtc_valid(व्योम) अणु वापस true; पूर्ण
अटल अंतरभूत पूर्णांक pm_trace_is_enabled(व्योम) अणु वापस 0; पूर्ण

#घोषणा TRACE_DEVICE(dev) करो अणु पूर्ण जबतक (0)
#घोषणा TRACE_RESUME(dev) करो अणु पूर्ण जबतक (0)
#घोषणा TRACE_SUSPEND(dev) करो अणु पूर्ण जबतक (0)

#पूर्ण_अगर

#पूर्ण_अगर
