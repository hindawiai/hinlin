<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_CONTEXT_TRACKING_STATE_H
#घोषणा _LINUX_CONTEXT_TRACKING_STATE_H

#समावेश <linux/percpu.h>
#समावेश <linux/अटल_key.h>

काष्ठा context_tracking अणु
	/*
	 * When active is false, probes are unset in order
	 * to minimize overhead: TIF flags are cleared
	 * and calls to user_enter/निकास are ignored. This
	 * may be further optimized using अटल keys.
	 */
	bool active;
	पूर्णांक recursion;
	क्रमागत ctx_state अणु
		CONTEXT_DISABLED = -1,	/* वापसed by ct_state() अगर unknown */
		CONTEXT_KERNEL = 0,
		CONTEXT_USER,
		CONTEXT_GUEST,
	पूर्ण state;
पूर्ण;

#अगर_घोषित CONFIG_CONTEXT_TRACKING
बाह्य काष्ठा अटल_key_false context_tracking_key;
DECLARE_PER_CPU(काष्ठा context_tracking, context_tracking);

अटल __always_अंतरभूत bool context_tracking_enabled(व्योम)
अणु
	वापस अटल_branch_unlikely(&context_tracking_key);
पूर्ण

अटल __always_अंतरभूत bool context_tracking_enabled_cpu(पूर्णांक cpu)
अणु
	वापस context_tracking_enabled() && per_cpu(context_tracking.active, cpu);
पूर्ण

अटल अंतरभूत bool context_tracking_enabled_this_cpu(व्योम)
अणु
	वापस context_tracking_enabled() && __this_cpu_पढ़ो(context_tracking.active);
पूर्ण

अटल __always_अंतरभूत bool context_tracking_in_user(व्योम)
अणु
	वापस __this_cpu_पढ़ो(context_tracking.state) == CONTEXT_USER;
पूर्ण
#अन्यथा
अटल अंतरभूत bool context_tracking_in_user(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत bool context_tracking_enabled(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत bool context_tracking_enabled_cpu(पूर्णांक cpu) अणु वापस false; पूर्ण
अटल अंतरभूत bool context_tracking_enabled_this_cpu(व्योम) अणु वापस false; पूर्ण
#पूर्ण_अगर /* CONFIG_CONTEXT_TRACKING */

#पूर्ण_अगर
