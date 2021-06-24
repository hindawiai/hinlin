<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_CONTEXT_TRACKING_H
#घोषणा _LINUX_CONTEXT_TRACKING_H

#समावेश <linux/sched.h>
#समावेश <linux/vसमय.स>
#समावेश <linux/context_tracking_state.h>
#समावेश <linux/instrumentation.h>

#समावेश <यंत्र/ptrace.h>


#अगर_घोषित CONFIG_CONTEXT_TRACKING
बाह्य व्योम context_tracking_cpu_set(पूर्णांक cpu);

/* Called with पूर्णांकerrupts disabled.  */
बाह्य व्योम __context_tracking_enter(क्रमागत ctx_state state);
बाह्य व्योम __context_tracking_निकास(क्रमागत ctx_state state);

बाह्य व्योम context_tracking_enter(क्रमागत ctx_state state);
बाह्य व्योम context_tracking_निकास(क्रमागत ctx_state state);
बाह्य व्योम context_tracking_user_enter(व्योम);
बाह्य व्योम context_tracking_user_निकास(व्योम);

अटल अंतरभूत व्योम user_enter(व्योम)
अणु
	अगर (context_tracking_enabled())
		context_tracking_enter(CONTEXT_USER);

पूर्ण
अटल अंतरभूत व्योम user_निकास(व्योम)
अणु
	अगर (context_tracking_enabled())
		context_tracking_निकास(CONTEXT_USER);
पूर्ण

/* Called with पूर्णांकerrupts disabled.  */
अटल __always_अंतरभूत व्योम user_enter_irqoff(व्योम)
अणु
	अगर (context_tracking_enabled())
		__context_tracking_enter(CONTEXT_USER);

पूर्ण
अटल __always_अंतरभूत व्योम user_निकास_irqoff(व्योम)
अणु
	अगर (context_tracking_enabled())
		__context_tracking_निकास(CONTEXT_USER);
पूर्ण

अटल अंतरभूत क्रमागत ctx_state exception_enter(व्योम)
अणु
	क्रमागत ctx_state prev_ctx;

	अगर (IS_ENABLED(CONFIG_HAVE_CONTEXT_TRACKING_OFFSTACK) ||
	    !context_tracking_enabled())
		वापस 0;

	prev_ctx = this_cpu_पढ़ो(context_tracking.state);
	अगर (prev_ctx != CONTEXT_KERNEL)
		context_tracking_निकास(prev_ctx);

	वापस prev_ctx;
पूर्ण

अटल अंतरभूत व्योम exception_निकास(क्रमागत ctx_state prev_ctx)
अणु
	अगर (!IS_ENABLED(CONFIG_HAVE_CONTEXT_TRACKING_OFFSTACK) &&
	    context_tracking_enabled()) अणु
		अगर (prev_ctx != CONTEXT_KERNEL)
			context_tracking_enter(prev_ctx);
	पूर्ण
पूर्ण

अटल __always_अंतरभूत bool context_tracking_guest_enter(व्योम)
अणु
	अगर (context_tracking_enabled())
		__context_tracking_enter(CONTEXT_GUEST);

	वापस context_tracking_enabled_this_cpu();
पूर्ण

अटल __always_अंतरभूत व्योम context_tracking_guest_निकास(व्योम)
अणु
	अगर (context_tracking_enabled())
		__context_tracking_निकास(CONTEXT_GUEST);
पूर्ण

/**
 * ct_state() - वापस the current context tracking state अगर known
 *
 * Returns the current cpu's context tracking state अगर context tracking
 * is enabled.  If context tracking is disabled, वापसs
 * CONTEXT_DISABLED.  This should be used primarily क्रम debugging.
 */
अटल __always_अंतरभूत क्रमागत ctx_state ct_state(व्योम)
अणु
	वापस context_tracking_enabled() ?
		this_cpu_पढ़ो(context_tracking.state) : CONTEXT_DISABLED;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम user_enter(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम user_निकास(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम user_enter_irqoff(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम user_निकास_irqoff(व्योम) अणु पूर्ण
अटल अंतरभूत क्रमागत ctx_state exception_enter(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम exception_निकास(क्रमागत ctx_state prev_ctx) अणु पूर्ण
अटल अंतरभूत क्रमागत ctx_state ct_state(व्योम) अणु वापस CONTEXT_DISABLED; पूर्ण
अटल अंतरभूत bool context_tracking_guest_enter(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम context_tracking_guest_निकास(व्योम) अणु पूर्ण

#पूर्ण_अगर /* !CONFIG_CONTEXT_TRACKING */

#घोषणा CT_WARN_ON(cond) WARN_ON(context_tracking_enabled() && (cond))

#अगर_घोषित CONFIG_CONTEXT_TRACKING_FORCE
बाह्य व्योम context_tracking_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम context_tracking_init(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_CONTEXT_TRACKING_FORCE */

#पूर्ण_अगर
