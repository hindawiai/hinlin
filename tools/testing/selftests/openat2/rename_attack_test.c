<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Author: Aleksa Sarai <cyphar@cyphar.com>
 * Copyright (C) 2018-2019 SUSE LLC.
 */

#घोषणा _GNU_SOURCE
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <sched.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>
#समावेश <sys/mount.h>
#समावेश <sys/mman.h>
#समावेश <sys/prctl.h>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <stdbool.h>
#समावेश <माला.स>
#समावेश <syscall.h>
#समावेश <सीमा.स>
#समावेश <unistd.h>

#समावेश "../kselftest.h"
#समावेश "helpers.h"

/* Conकाष्ठा a test directory with the following काष्ठाure:
 *
 * root/
 * |-- a/
 * |   `-- c/
 * `-- b/
 */
पूर्णांक setup_testdir(व्योम)
अणु
	पूर्णांक dfd;
	अक्षर स_नाम[] = "/tmp/ksft-openat2-rename-attack.XXXXXX";

	/* Make the top-level directory. */
	अगर (!mkdtemp(स_नाम))
		ksft_निकास_fail_msg("setup_testdir: failed to create tmpdir\n");
	dfd = खोलो(स_नाम, O_PATH | O_सूचीECTORY);
	अगर (dfd < 0)
		ksft_निकास_fail_msg("setup_testdir: failed to open tmpdir\n");

	E_सूची_गढ़ोat(dfd, "a", 0755);
	E_सूची_गढ़ोat(dfd, "b", 0755);
	E_सूची_गढ़ोat(dfd, "a/c", 0755);

	वापस dfd;
पूर्ण

/* Swap @dirfd/@a and @dirfd/@b स्थिरantly. Parent must समाप्त this process. */
pid_t spawn_attack(पूर्णांक dirfd, अक्षर *a, अक्षर *b)
अणु
	pid_t child = विभाजन();
	अगर (child != 0)
		वापस child;

	/* If the parent (the test process) dies, समाप्त ourselves too. */
	E_prctl(PR_SET_PDEATHSIG, SIGKILL);

	/* Swap @a and @b. */
	क्रम (;;)
		नामat2(dirfd, a, dirfd, b, RENAME_EXCHANGE);
	निकास(1);
पूर्ण

#घोषणा NUM_RENAME_TESTS 2
#घोषणा ROUNDS 400000

स्थिर अक्षर *flagname(पूर्णांक resolve)
अणु
	चयन (resolve) अणु
	हाल RESOLVE_IN_ROOT:
		वापस "RESOLVE_IN_ROOT";
	हाल RESOLVE_BENEATH:
		वापस "RESOLVE_BENEATH";
	पूर्ण
	वापस "(unknown)";
पूर्ण

व्योम test_नाम_attack(पूर्णांक resolve)
अणु
	पूर्णांक dfd, afd;
	pid_t child;
	व्योम (*resultfn)(स्थिर अक्षर *msg, ...) = ksft_test_result_pass;
	पूर्णांक escapes = 0, other_errs = 0, exdevs = 0, eagains = 0, successes = 0;

	काष्ठा खोलो_how how = अणु
		.flags = O_PATH,
		.resolve = resolve,
	पूर्ण;

	अगर (!खोलोat2_supported) अणु
		how.resolve = 0;
		ksft_prपूर्णांक_msg("openat2(2) unsupported -- using openat(2) instead\n");
	पूर्ण

	dfd = setup_testdir();
	afd = खोलोat(dfd, "a", O_PATH);
	अगर (afd < 0)
		ksft_निकास_fail_msg("test_rename_attack: failed to open 'a'\n");

	child = spawn_attack(dfd, "a/c", "b");

	क्रम (पूर्णांक i = 0; i < ROUNDS; i++) अणु
		पूर्णांक fd;
		अक्षर *victim_path = "c/../../c/../../c/../../c/../../c/../../c/../../c/../../c/../../c/../../c/../../c/../../c/../../c/../../c/../../c/../../c/../../c/../../c/../../c/../..";

		अगर (खोलोat2_supported)
			fd = sys_खोलोat2(afd, victim_path, &how);
		अन्यथा
			fd = sys_खोलोat(afd, victim_path, &how);

		अगर (fd < 0) अणु
			अगर (fd == -EAGAIN)
				eagains++;
			अन्यथा अगर (fd == -EXDEV)
				exdevs++;
			अन्यथा अगर (fd == -ENOENT)
				escapes++; /* escaped outside and got ENOENT... */
			अन्यथा
				other_errs++; /* unexpected error */
		पूर्ण अन्यथा अणु
			अगर (fdequal(fd, afd, शून्य))
				successes++;
			अन्यथा
				escapes++; /* we got an unexpected fd */
		पूर्ण
		बंद(fd);
	पूर्ण

	अगर (escapes > 0)
		resultfn = ksft_test_result_fail;
	ksft_prपूर्णांक_msg("non-escapes: EAGAIN=%d EXDEV=%d E<other>=%d success=%d\n",
		       eagains, exdevs, other_errs, successes);
	resultfn("rename attack with %s (%d runs, got %d escapes)\n",
		 flagname(resolve), ROUNDS, escapes);

	/* Should be समाप्तed anyway, but might as well make sure. */
	E_समाप्त(child, SIGKILL);
पूर्ण

#घोषणा NUM_TESTS NUM_RENAME_TESTS

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	ksft_prपूर्णांक_header();
	ksft_set_plan(NUM_TESTS);

	test_नाम_attack(RESOLVE_BENEATH);
	test_नाम_attack(RESOLVE_IN_ROOT);

	अगर (ksft_get_fail_cnt() + ksft_get_error_cnt() > 0)
		ksft_निकास_fail();
	अन्यथा
		ksft_निकास_pass();
पूर्ण
