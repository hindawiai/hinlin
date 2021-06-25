<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <सीमा.स>
#समावेश <linux/types.h>
#समावेश <sched.h>
#समावेश <संकेत.स>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <syscall.h>
#समावेश <sys/mount.h>
#समावेश <sys/prctl.h>
#समावेश <sys/रुको.h>
#समावेश <unistd.h>

#समावेश "pidfd.h"
#समावेश "../kselftest.h"

अटल पूर्णांक safe_पूर्णांक(स्थिर अक्षर *numstr, पूर्णांक *converted)
अणु
	अक्षर *err = शून्य;
	दीर्घ sli;

	त्रुटि_सं = 0;
	sli = म_से_दीर्घ(numstr, &err, 0);
	अगर (त्रुटि_सं == दुस्फल && (sli == दीर्घ_उच्च || sli == दीर्घ_न्यून))
		वापस -दुस्फल;

	अगर (त्रुटि_सं != 0 && sli == 0)
		वापस -EINVAL;

	अगर (err == numstr || *err != '\0')
		वापस -EINVAL;

	अगर (sli > पूर्णांक_उच्च || sli < पूर्णांक_न्यून)
		वापस -दुस्फल;

	*converted = (पूर्णांक)sli;
	वापस 0;
पूर्ण

अटल पूर्णांक अक्षर_left_gc(स्थिर अक्षर *buffer, माप_प्रकार len)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < len; i++) अणु
		अगर (buffer[i] == ' ' ||
		    buffer[i] == '\t')
			जारी;

		वापस i;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक अक्षर_right_gc(स्थिर अक्षर *buffer, माप_प्रकार len)
अणु
	पूर्णांक i;

	क्रम (i = len - 1; i >= 0; i--) अणु
		अगर (buffer[i] == ' '  ||
		    buffer[i] == '\t' ||
		    buffer[i] == '\n' ||
		    buffer[i] == '\0')
			जारी;

		वापस i + 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल अक्षर *trim_whitespace_in_place(अक्षर *buffer)
अणु
	buffer += अक्षर_left_gc(buffer, म_माप(buffer));
	buffer[अक्षर_right_gc(buffer, म_माप(buffer))] = '\0';
	वापस buffer;
पूर्ण

अटल pid_t get_pid_from_fdinfo_file(पूर्णांक pidfd, स्थिर अक्षर *key, माप_प्रकार keylen)
अणु
	पूर्णांक ret;
	अक्षर path[512];
	खाता *f;
	माप_प्रकार n = 0;
	pid_t result = -1;
	अक्षर *line = शून्य;

	snम_लिखो(path, माप(path), "/proc/self/fdinfo/%d", pidfd);

	f = ख_खोलो(path, "re");
	अगर (!f)
		वापस -1;

	जबतक (getline(&line, &n, f) != -1) अणु
		अक्षर *numstr;

		अगर (म_भेदन(line, key, keylen))
			जारी;

		numstr = trim_whitespace_in_place(line + 4);
		ret = safe_पूर्णांक(numstr, &result);
		अगर (ret < 0)
			जाओ out;

		अवरोध;
	पूर्ण

out:
	मुक्त(line);
	ख_बंद(f);
	वापस result;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक pidfd = -1, ret = 1;
	pid_t pid;

	ksft_set_plan(3);

	pidfd = sys_pidfd_खोलो(-1, 0);
	अगर (pidfd >= 0) अणु
		ksft_prपूर्णांक_msg(
			"%s - succeeded to open pidfd for invalid pid -1\n",
			म_त्रुटि(त्रुटि_सं));
		जाओ on_error;
	पूर्ण
	ksft_test_result_pass("do not allow invalid pid test: passed\n");

	pidfd = sys_pidfd_खोलो(getpid(), 1);
	अगर (pidfd >= 0) अणु
		ksft_prपूर्णांक_msg(
			"%s - succeeded to open pidfd with invalid flag value specified\n",
			म_त्रुटि(त्रुटि_सं));
		जाओ on_error;
	पूर्ण
	ksft_test_result_pass("do not allow invalid flag test: passed\n");

	pidfd = sys_pidfd_खोलो(getpid(), 0);
	अगर (pidfd < 0) अणु
		ksft_prपूर्णांक_msg("%s - failed to open pidfd\n", म_त्रुटि(त्रुटि_सं));
		जाओ on_error;
	पूर्ण
	ksft_test_result_pass("open a new pidfd test: passed\n");

	pid = get_pid_from_fdinfo_file(pidfd, "Pid:", माप("Pid:") - 1);
	ksft_prपूर्णांक_msg("pidfd %d refers to process with pid %d\n", pidfd, pid);

	ret = 0;

on_error:
	अगर (pidfd >= 0)
		बंद(pidfd);

	वापस !ret ? ksft_निकास_pass() : ksft_निकास_fail();
पूर्ण
