<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2012 - 2014 Cisco Systems
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#अगर_अघोषित __TIMER_INTERNAL_H__
#घोषणा __TIMER_INTERNAL_H__
#समावेश <linux/list.h>
#समावेश <यंत्र/bug.h>

#घोषणा TIMER_MULTIPLIER 256
#घोषणा TIMER_MIN_DELTA  500

क्रमागत समय_प्रकारravel_mode अणु
	TT_MODE_OFF,
	TT_MODE_BASIC,
	TT_MODE_INFCPU,
	TT_MODE_EXTERNAL,
पूर्ण;

#अगर_घोषित CONFIG_UML_TIME_TRAVEL_SUPPORT
काष्ठा समय_प्रकारravel_event अणु
	अचिन्हित दीर्घ दीर्घ समय;
	व्योम (*fn)(काष्ठा समय_प्रकारravel_event *d);
	काष्ठा list_head list;
	bool pending, onstack;
पूर्ण;

बाह्य क्रमागत समय_प्रकारravel_mode समय_प्रकारravel_mode;

व्योम समय_प्रकारravel_sleep(व्योम);

अटल अंतरभूत व्योम
समय_प्रकारravel_set_event_fn(काष्ठा समय_प्रकारravel_event *e,
			 व्योम (*fn)(काष्ठा समय_प्रकारravel_event *d))
अणु
	e->fn = fn;
पूर्ण

व्योम __समय_प्रकारravel_propagate_समय(व्योम);

अटल अंतरभूत व्योम समय_प्रकारravel_propagate_समय(व्योम)
अणु
	अगर (समय_प्रकारravel_mode == TT_MODE_EXTERNAL)
		__समय_प्रकारravel_propagate_समय();
पूर्ण

व्योम __समय_प्रकारravel_रुको_पढ़ोable(पूर्णांक fd);

अटल अंतरभूत व्योम समय_प्रकारravel_रुको_पढ़ोable(पूर्णांक fd)
अणु
	अगर (समय_प्रकारravel_mode == TT_MODE_EXTERNAL)
		__समय_प्रकारravel_रुको_पढ़ोable(fd);
पूर्ण

व्योम समय_प्रकारravel_add_irq_event(काष्ठा समय_प्रकारravel_event *e);
व्योम समय_प्रकारravel_add_event_rel(काष्ठा समय_प्रकारravel_event *e,
			       अचिन्हित दीर्घ दीर्घ delay_ns);
bool समय_प्रकारravel_del_event(काष्ठा समय_प्रकारravel_event *e);
#अन्यथा
काष्ठा समय_प्रकारravel_event अणु
पूर्ण;

#घोषणा समय_प्रकारravel_mode TT_MODE_OFF

अटल अंतरभूत व्योम समय_प्रकारravel_sleep(व्योम)
अणु
पूर्ण

/* this is a macro so the event/function need not exist */
#घोषणा समय_प्रकारravel_set_event_fn(e, fn) करो अणुपूर्ण जबतक (0)

अटल अंतरभूत व्योम समय_प्रकारravel_propagate_समय(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम समय_प्रकारravel_रुको_पढ़ोable(पूर्णांक fd)
अणु
पूर्ण

अटल अंतरभूत व्योम समय_प्रकारravel_add_irq_event(काष्ठा समय_प्रकारravel_event *e)
अणु
	WARN_ON(1);
पूर्ण

/*
 * not अंतरभूतs so the data काष्ठाure need not exist,
 * cause linker failures
 */
बाह्य व्योम समय_प्रकारravel_not_configured(व्योम);
#घोषणा समय_प्रकारravel_add_event_rel(...) समय_प्रकारravel_not_configured()
#घोषणा समय_प्रकारravel_del_event(...) समय_प्रकारravel_not_configured()
#पूर्ण_अगर /* CONFIG_UML_TIME_TRAVEL_SUPPORT */

/*
 * Without CONFIG_UML_TIME_TRAVEL_SUPPORT this is a linker error अगर used,
 * which is पूर्णांकentional since we really shouldn't link it in that हाल.
 */
व्योम समय_प्रकारravel_ndelay(अचिन्हित दीर्घ nsec);
#पूर्ण_अगर /* __TIMER_INTERNAL_H__ */
