<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#घोषणा TIMER_RETRY 1

काष्ठा k_घड़ी अणु
	पूर्णांक	(*घड़ी_getres)(स्थिर घड़ीid_t which_घड़ी,
				काष्ठा बारpec64 *tp);
	पूर्णांक	(*घड़ी_set)(स्थिर घड़ीid_t which_घड़ी,
			     स्थिर काष्ठा बारpec64 *tp);
	/* Returns the घड़ी value in the current समय namespace. */
	पूर्णांक	(*घड़ी_get_बारpec)(स्थिर घड़ीid_t which_घड़ी,
				      काष्ठा बारpec64 *tp);
	/* Returns the घड़ी value in the root समय namespace. */
	kसमय_प्रकार	(*घड़ी_get_kसमय)(स्थिर घड़ीid_t which_घड़ी);
	पूर्णांक	(*घड़ी_adj)(स्थिर घड़ीid_t which_घड़ी, काष्ठा __kernel_समयx *tx);
	पूर्णांक	(*समयr_create)(काष्ठा k_iसमयr *समयr);
	पूर्णांक	(*nsleep)(स्थिर घड़ीid_t which_घड़ी, पूर्णांक flags,
			  स्थिर काष्ठा बारpec64 *);
	पूर्णांक	(*समयr_set)(काष्ठा k_iसमयr *timr, पूर्णांक flags,
			     काष्ठा iसमयrspec64 *new_setting,
			     काष्ठा iसमयrspec64 *old_setting);
	पूर्णांक	(*समयr_del)(काष्ठा k_iसमयr *timr);
	व्योम	(*समयr_get)(काष्ठा k_iसमयr *timr,
			     काष्ठा iसमयrspec64 *cur_setting);
	व्योम	(*समयr_rearm)(काष्ठा k_iसमयr *timr);
	s64	(*समयr_क्रमward)(काष्ठा k_iसमयr *timr, kसमय_प्रकार now);
	kसमय_प्रकार	(*समयr_reमुख्यing)(काष्ठा k_iसमयr *timr, kसमय_प्रकार now);
	पूर्णांक	(*समयr_try_to_cancel)(काष्ठा k_iसमयr *timr);
	व्योम	(*समयr_arm)(काष्ठा k_iसमयr *timr, kसमय_प्रकार expires,
			     bool असलolute, bool sigev_none);
	व्योम	(*समयr_रुको_running)(काष्ठा k_iसमयr *timr);
पूर्ण;

बाह्य स्थिर काष्ठा k_घड़ी घड़ी_posix_cpu;
बाह्य स्थिर काष्ठा k_घड़ी घड़ी_posix_dynamic;
बाह्य स्थिर काष्ठा k_घड़ी घड़ी_process;
बाह्य स्थिर काष्ठा k_घड़ी घड़ी_प्रकारhपढ़ो;
बाह्य स्थिर काष्ठा k_घड़ी alarm_घड़ी;

पूर्णांक posix_समयr_event(काष्ठा k_iसमयr *timr, पूर्णांक si_निजी);

व्योम common_समयr_get(काष्ठा k_iसमयr *timr, काष्ठा iसमयrspec64 *cur_setting);
पूर्णांक common_समयr_set(काष्ठा k_iसमयr *timr, पूर्णांक flags,
		     काष्ठा iसमयrspec64 *new_setting,
		     काष्ठा iसमयrspec64 *old_setting);
पूर्णांक common_समयr_del(काष्ठा k_iसमयr *समयr);
