<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Helper functions क्रम handling target thपढ़ोs/cpus
 *
 * Copyright (C) 2012, LG Electronics, Namhyung Kim <namhyung.kim@lge.com>
 */

#समावेश "target.h"

#समावेश <pwd.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>

क्रमागत target_त्रुटि_सं target__validate(काष्ठा target *target)
अणु
	क्रमागत target_त्रुटि_सं ret = TARGET_ERRNO__SUCCESS;

	अगर (target->pid)
		target->tid = target->pid;

	/* CPU and PID are mutually exclusive */
	अगर (target->tid && target->cpu_list) अणु
		target->cpu_list = शून्य;
		अगर (ret == TARGET_ERRNO__SUCCESS)
			ret = TARGET_ERRNO__PID_OVERRIDE_CPU;
	पूर्ण

	/* UID and PID are mutually exclusive */
	अगर (target->tid && target->uid_str) अणु
		target->uid_str = शून्य;
		अगर (ret == TARGET_ERRNO__SUCCESS)
			ret = TARGET_ERRNO__PID_OVERRIDE_UID;
	पूर्ण

	/* UID and CPU are mutually exclusive */
	अगर (target->uid_str && target->cpu_list) अणु
		target->cpu_list = शून्य;
		अगर (ret == TARGET_ERRNO__SUCCESS)
			ret = TARGET_ERRNO__UID_OVERRIDE_CPU;
	पूर्ण

	/* PID and SYSTEM are mutually exclusive */
	अगर (target->tid && target->प्रणाली_wide) अणु
		target->प्रणाली_wide = false;
		अगर (ret == TARGET_ERRNO__SUCCESS)
			ret = TARGET_ERRNO__PID_OVERRIDE_SYSTEM;
	पूर्ण

	/* UID and SYSTEM are mutually exclusive */
	अगर (target->uid_str && target->प्रणाली_wide) अणु
		target->प्रणाली_wide = false;
		अगर (ret == TARGET_ERRNO__SUCCESS)
			ret = TARGET_ERRNO__UID_OVERRIDE_SYSTEM;
	पूर्ण

	/* BPF and CPU are mutually exclusive */
	अगर (target->bpf_str && target->cpu_list) अणु
		target->cpu_list = शून्य;
		अगर (ret == TARGET_ERRNO__SUCCESS)
			ret = TARGET_ERRNO__BPF_OVERRIDE_CPU;
	पूर्ण

	/* BPF and PID/TID are mutually exclusive */
	अगर (target->bpf_str && target->tid) अणु
		target->tid = शून्य;
		अगर (ret == TARGET_ERRNO__SUCCESS)
			ret = TARGET_ERRNO__BPF_OVERRIDE_PID;
	पूर्ण

	/* BPF and UID are mutually exclusive */
	अगर (target->bpf_str && target->uid_str) अणु
		target->uid_str = शून्य;
		अगर (ret == TARGET_ERRNO__SUCCESS)
			ret = TARGET_ERRNO__BPF_OVERRIDE_UID;
	पूर्ण

	/* BPF and THREADS are mutually exclusive */
	अगर (target->bpf_str && target->per_thपढ़ो) अणु
		target->per_thपढ़ो = false;
		अगर (ret == TARGET_ERRNO__SUCCESS)
			ret = TARGET_ERRNO__BPF_OVERRIDE_THREAD;
	पूर्ण

	/* THREAD and SYSTEM/CPU are mutually exclusive */
	अगर (target->per_thपढ़ो && (target->प्रणाली_wide || target->cpu_list)) अणु
		target->per_thपढ़ो = false;
		अगर (ret == TARGET_ERRNO__SUCCESS)
			ret = TARGET_ERRNO__SYSTEM_OVERRIDE_THREAD;
	पूर्ण

	वापस ret;
पूर्ण

क्रमागत target_त्रुटि_सं target__parse_uid(काष्ठा target *target)
अणु
	काष्ठा passwd pwd, *result;
	अक्षर buf[1024];
	स्थिर अक्षर *str = target->uid_str;

	target->uid = अच_पूर्णांक_उच्च;
	अगर (str == शून्य)
		वापस TARGET_ERRNO__SUCCESS;

	/* Try user name first */
	getpwnam_r(str, &pwd, buf, माप(buf), &result);

	अगर (result == शून्य) अणु
		/*
		 * The user name not found. Maybe it's a UID number.
		 */
		अक्षर *endptr;
		पूर्णांक uid = म_से_दीर्घ(str, &endptr, 10);

		अगर (*endptr != '\0')
			वापस TARGET_ERRNO__INVALID_UID;

		getpwuid_r(uid, &pwd, buf, माप(buf), &result);

		अगर (result == शून्य)
			वापस TARGET_ERRNO__USER_NOT_FOUND;
	पूर्ण

	target->uid = result->pw_uid;
	वापस TARGET_ERRNO__SUCCESS;
पूर्ण

/*
 * This must have a same ordering as the क्रमागत target_त्रुटि_सं.
 */
अटल स्थिर अक्षर *target__error_str[] = अणु
	"PID/TID switch overriding CPU",
	"PID/TID switch overriding UID",
	"UID switch overriding CPU",
	"PID/TID switch overriding SYSTEM",
	"UID switch overriding SYSTEM",
	"SYSTEM/CPU switch overriding PER-THREAD",
	"BPF switch overriding CPU",
	"BPF switch overriding PID/TID",
	"BPF switch overriding UID",
	"BPF switch overriding THREAD",
	"Invalid User: %s",
	"Problems obtaining information for user %s",
पूर्ण;

पूर्णांक target__म_त्रुटि(काष्ठा target *target, पूर्णांक errnum,
			  अक्षर *buf, माप_प्रकार buflen)
अणु
	पूर्णांक idx;
	स्थिर अक्षर *msg;

	BUG_ON(buflen == 0);

	अगर (errnum >= 0) अणु
		str_error_r(errnum, buf, buflen);
		वापस 0;
	पूर्ण

	अगर (errnum <  __TARGET_ERRNO__START || errnum >= __TARGET_ERRNO__END)
		वापस -1;

	idx = errnum - __TARGET_ERRNO__START;
	msg = target__error_str[idx];

	चयन (errnum) अणु
	हाल TARGET_ERRNO__PID_OVERRIDE_CPU ...
	     TARGET_ERRNO__BPF_OVERRIDE_THREAD:
		snम_लिखो(buf, buflen, "%s", msg);
		अवरोध;

	हाल TARGET_ERRNO__INVALID_UID:
	हाल TARGET_ERRNO__USER_NOT_FOUND:
		snम_लिखो(buf, buflen, msg, target->uid_str);
		अवरोध;

	शेष:
		/* cannot reach here */
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
