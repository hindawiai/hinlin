<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
#समावेश <sched.h>

/*
 * Not defined anywhere अन्यथा, probably, just to make sure we
 * catch future flags
 */
#घोषणा SCHED_POLICY_MASK 0xff

#अगर_अघोषित SCHED_DEADLINE
#घोषणा SCHED_DEADLINE 6
#पूर्ण_अगर
#अगर_अघोषित SCHED_RESET_ON_FORK
#घोषणा SCHED_RESET_ON_FORK 0x40000000
#पूर्ण_अगर

अटल माप_प्रकार syscall_arg__scnम_लिखो_sched_policy(अक्षर *bf, माप_प्रकार size,
						  काष्ठा syscall_arg *arg)
अणु
	bool show_prefix = arg->show_string_prefix;
	स्थिर अक्षर *prefix = "SCHED_";
	स्थिर अक्षर *policies[] = अणु
		"NORMAL", "FIFO", "RR", "BATCH", "ISO", "IDLE", "DEADLINE",
	पूर्ण;
	माप_प्रकार prपूर्णांकed;
	पूर्णांक policy = arg->val,
	    flags = policy & ~SCHED_POLICY_MASK;

	policy &= SCHED_POLICY_MASK;
	अगर (policy <= SCHED_DEADLINE)
		prपूर्णांकed = scnम_लिखो(bf, size, "%s%s", show_prefix ? prefix : "", policies[policy]);
	अन्यथा
		prपूर्णांकed = scnम_लिखो(bf, size, "%#x", policy);

#घोषणा	P_POLICY_FLAG(n) \
	अगर (flags & SCHED_##n) अणु \
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "|%s%s", show_prefix ? prefix : "",  #n); \
		flags &= ~SCHED_##n; \
	पूर्ण

	P_POLICY_FLAG(RESET_ON_FORK);
#अघोषित P_POLICY_FLAG

	अगर (flags)
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "|%#x", flags);

	वापस prपूर्णांकed;
पूर्ण

#घोषणा SCA_SCHED_POLICY syscall_arg__scnम_लिखो_sched_policy
