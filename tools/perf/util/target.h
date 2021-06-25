<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PERF_TARGET_H
#घोषणा _PERF_TARGET_H

#समावेश <stdbool.h>
#समावेश <sys/types.h>

काष्ठा target अणु
	स्थिर अक्षर   *pid;
	स्थिर अक्षर   *tid;
	स्थिर अक्षर   *cpu_list;
	स्थिर अक्षर   *uid_str;
	स्थिर अक्षर   *bpf_str;
	uid_t	     uid;
	bool	     प्रणाली_wide;
	bool	     uses_mmap;
	bool	     शेष_per_cpu;
	bool	     per_thपढ़ो;
	bool	     use_bpf;
	स्थिर अक्षर   *attr_map;
पूर्ण;

क्रमागत target_त्रुटि_सं अणु
	TARGET_ERRNO__SUCCESS		= 0,

	/*
	 * Choose an arbitrary negative big number not to clash with standard
	 * त्रुटि_सं since SUS requires the त्रुटि_सं has distinct positive values.
	 * See 'Issue 6' in the link below.
	 *
	 * http://pubs.खोलोgroup.org/onlinepubs/9699919799/basedefs/त्रुटिसं.स.hपंचांगl
	 */
	__TARGET_ERRNO__START		= -10000,

	/* क्रम target__validate() */
	TARGET_ERRNO__PID_OVERRIDE_CPU	= __TARGET_ERRNO__START,
	TARGET_ERRNO__PID_OVERRIDE_UID,
	TARGET_ERRNO__UID_OVERRIDE_CPU,
	TARGET_ERRNO__PID_OVERRIDE_SYSTEM,
	TARGET_ERRNO__UID_OVERRIDE_SYSTEM,
	TARGET_ERRNO__SYSTEM_OVERRIDE_THREAD,
	TARGET_ERRNO__BPF_OVERRIDE_CPU,
	TARGET_ERRNO__BPF_OVERRIDE_PID,
	TARGET_ERRNO__BPF_OVERRIDE_UID,
	TARGET_ERRNO__BPF_OVERRIDE_THREAD,

	/* क्रम target__parse_uid() */
	TARGET_ERRNO__INVALID_UID,
	TARGET_ERRNO__USER_NOT_FOUND,

	__TARGET_ERRNO__END,
पूर्ण;

क्रमागत target_त्रुटि_सं target__validate(काष्ठा target *target);
क्रमागत target_त्रुटि_सं target__parse_uid(काष्ठा target *target);

पूर्णांक target__म_त्रुटि(काष्ठा target *target, पूर्णांक errnum, अक्षर *buf, माप_प्रकार buflen);

अटल अंतरभूत bool target__has_task(काष्ठा target *target)
अणु
	वापस target->tid || target->pid || target->uid_str;
पूर्ण

अटल अंतरभूत bool target__has_cpu(काष्ठा target *target)
अणु
	वापस target->प्रणाली_wide || target->cpu_list;
पूर्ण

अटल अंतरभूत bool target__none(काष्ठा target *target)
अणु
	वापस !target__has_task(target) && !target__has_cpu(target);
पूर्ण

अटल अंतरभूत bool target__has_per_thपढ़ो(काष्ठा target *target)
अणु
	वापस target->प्रणाली_wide && target->per_thपढ़ो;
पूर्ण

अटल अंतरभूत bool target__uses_dummy_map(काष्ठा target *target)
अणु
	bool use_dummy = false;

	अगर (target->शेष_per_cpu)
		use_dummy = target->per_thपढ़ो ? true : false;
	अन्यथा अगर (target__has_task(target) ||
	         (!target__has_cpu(target) && !target->uses_mmap))
		use_dummy = true;
	अन्यथा अगर (target__has_per_thपढ़ो(target))
		use_dummy = true;

	वापस use_dummy;
पूर्ण

#पूर्ण_अगर /* _PERF_TARGET_H */
