<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Author: Aleksa Sarai <cyphar@cyphar.com>
 * Copyright (C) 2018-2019 SUSE LLC.
 */

#घोषणा _GNU_SOURCE
#समावेश <fcntl.h>
#समावेश <sched.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>
#समावेश <sys/mount.h>
#समावेश <मानककोष.स>
#समावेश <stdbool.h>
#समावेश <माला.स>

#समावेश "../kselftest.h"
#समावेश "helpers.h"

/*
 * O_LARGEखाता is set to 0 by glibc.
 * XXX: This is wrong on अणुmips, parisc, घातerpc, sparcपूर्ण.
 */
#अघोषित	O_LARGEखाता
#घोषणा	O_LARGEखाता 0x8000

काष्ठा खोलो_how_ext अणु
	काष्ठा खोलो_how inner;
	uपूर्णांक32_t extra1;
	अक्षर pad1[128];
	uपूर्णांक32_t extra2;
	अक्षर pad2[128];
	uपूर्णांक32_t extra3;
पूर्ण;

काष्ठा काष्ठा_test अणु
	स्थिर अक्षर *name;
	काष्ठा खोलो_how_ext arg;
	माप_प्रकार size;
	पूर्णांक err;
पूर्ण;

#घोषणा NUM_OPENAT2_STRUCT_TESTS 7
#घोषणा NUM_OPENAT2_STRUCT_VARIATIONS 13

व्योम test_खोलोat2_काष्ठा(व्योम)
अणु
	पूर्णांक misalignments[] = अणु 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 17, 87 पूर्ण;

	काष्ठा काष्ठा_test tests[] = अणु
		/* Normal काष्ठा. */
		अणु .name = "normal struct",
		  .arg.inner.flags = O_RDONLY,
		  .size = माप(काष्ठा खोलो_how) पूर्ण,
		/* Bigger काष्ठा, with zeroed out end. */
		अणु .name = "bigger struct (zeroed out)",
		  .arg.inner.flags = O_RDONLY,
		  .size = माप(काष्ठा खोलो_how_ext) पूर्ण,

		/* TODO: Once expanded, check zero-padding. */

		/* Smaller than version-0 काष्ठा. */
		अणु .name = "zero-sized 'struct'",
		  .arg.inner.flags = O_RDONLY, .size = 0, .err = -EINVAL पूर्ण,
		अणु .name = "smaller-than-v0 struct",
		  .arg.inner.flags = O_RDONLY,
		  .size = OPEN_HOW_SIZE_VER0 - 1, .err = -EINVAL पूर्ण,

		/* Bigger काष्ठा, with non-zero trailing bytes. */
		अणु .name = "bigger struct (non-zero data in first 'future field')",
		  .arg.inner.flags = O_RDONLY, .arg.extra1 = 0xdeadbeef,
		  .size = माप(काष्ठा खोलो_how_ext), .err = -E2BIG पूर्ण,
		अणु .name = "bigger struct (non-zero data in middle of 'future fields')",
		  .arg.inner.flags = O_RDONLY, .arg.extra2 = 0xfeedcafe,
		  .size = माप(काष्ठा खोलो_how_ext), .err = -E2BIG पूर्ण,
		अणु .name = "bigger struct (non-zero data at end of 'future fields')",
		  .arg.inner.flags = O_RDONLY, .arg.extra3 = 0xabad1dea,
		  .size = माप(काष्ठा खोलो_how_ext), .err = -E2BIG पूर्ण,
	पूर्ण;

	BUILD_BUG_ON(ARRAY_LEN(misalignments) != NUM_OPENAT2_STRUCT_VARIATIONS);
	BUILD_BUG_ON(ARRAY_LEN(tests) != NUM_OPENAT2_STRUCT_TESTS);

	क्रम (पूर्णांक i = 0; i < ARRAY_LEN(tests); i++) अणु
		काष्ठा काष्ठा_test *test = &tests[i];
		काष्ठा खोलो_how_ext how_ext = test->arg;

		क्रम (पूर्णांक j = 0; j < ARRAY_LEN(misalignments); j++) अणु
			पूर्णांक fd, misalign = misalignments[j];
			अक्षर *fdpath = शून्य;
			bool failed;
			व्योम (*resultfn)(स्थिर अक्षर *msg, ...) = ksft_test_result_pass;

			व्योम *copy = शून्य, *how_copy = &how_ext;

			अगर (!खोलोat2_supported) अणु
				ksft_prपूर्णांक_msg("openat2(2) unsupported\n");
				resultfn = ksft_test_result_skip;
				जाओ skip;
			पूर्ण

			अगर (misalign) अणु
				/*
				 * Explicitly misalign the काष्ठाure copying it with the given
				 * (mis)alignment offset. The other data is set to be non-zero to
				 * make sure that non-zero bytes outside the काष्ठा aren't checked
				 *
				 * This is effectively to check that is_zeroed_user() works.
				 */
				copy = दो_स्मृति(misalign + माप(how_ext));
				how_copy = copy + misalign;
				स_रखो(copy, 0xff, misalign);
				स_नकल(how_copy, &how_ext, माप(how_ext));
			पूर्ण

			fd = raw_खोलोat2(AT_FDCWD, ".", how_copy, test->size);
			अगर (test->err >= 0)
				failed = (fd < 0);
			अन्यथा
				failed = (fd != test->err);
			अगर (fd >= 0) अणु
				fdpath = fdपढ़ोlink(fd);
				बंद(fd);
			पूर्ण

			अगर (failed) अणु
				resultfn = ksft_test_result_fail;

				ksft_prपूर्णांक_msg("openat2 unexpectedly returned ");
				अगर (fdpath)
					ksft_prपूर्णांक_msg("%d['%s']\n", fd, fdpath);
				अन्यथा
					ksft_prपूर्णांक_msg("%d (%s)\n", fd, म_त्रुटि(-fd));
			पूर्ण

skip:
			अगर (test->err >= 0)
				resultfn("openat2 with %s argument [misalign=%d] succeeds\n",
					 test->name, misalign);
			अन्यथा
				resultfn("openat2 with %s argument [misalign=%d] fails with %d (%s)\n",
					 test->name, misalign, test->err,
					 म_त्रुटि(-test->err));

			मुक्त(copy);
			मुक्त(fdpath);
			ख_साफ(मानक_निकास);
		पूर्ण
	पूर्ण
पूर्ण

काष्ठा flag_test अणु
	स्थिर अक्षर *name;
	काष्ठा खोलो_how how;
	पूर्णांक err;
पूर्ण;

#घोषणा NUM_OPENAT2_FLAG_TESTS 24

व्योम test_खोलोat2_flags(व्योम)
अणु
	काष्ठा flag_test tests[] = अणु
		/* O_TMPखाता is incompatible with O_PATH and O_CREAT. */
		अणु .name = "incompatible flags (O_TMPFILE | O_PATH)",
		  .how.flags = O_TMPखाता | O_PATH | O_RDWR, .err = -EINVAL पूर्ण,
		अणु .name = "incompatible flags (O_TMPFILE | O_CREAT)",
		  .how.flags = O_TMPखाता | O_CREAT | O_RDWR, .err = -EINVAL पूर्ण,

		/* O_PATH only permits certain other flags to be set ... */
		अणु .name = "compatible flags (O_PATH | O_CLOEXEC)",
		  .how.flags = O_PATH | O_CLOEXEC पूर्ण,
		अणु .name = "compatible flags (O_PATH | O_DIRECTORY)",
		  .how.flags = O_PATH | O_सूचीECTORY पूर्ण,
		अणु .name = "compatible flags (O_PATH | O_NOFOLLOW)",
		  .how.flags = O_PATH | O_NOFOLLOW पूर्ण,
		/* ... and others are असलolutely not permitted. */
		अणु .name = "incompatible flags (O_PATH | O_RDWR)",
		  .how.flags = O_PATH | O_RDWR, .err = -EINVAL पूर्ण,
		अणु .name = "incompatible flags (O_PATH | O_CREAT)",
		  .how.flags = O_PATH | O_CREAT, .err = -EINVAL पूर्ण,
		अणु .name = "incompatible flags (O_PATH | O_EXCL)",
		  .how.flags = O_PATH | O_EXCL, .err = -EINVAL पूर्ण,
		अणु .name = "incompatible flags (O_PATH | O_NOCTTY)",
		  .how.flags = O_PATH | O_NOCTTY, .err = -EINVAL पूर्ण,
		अणु .name = "incompatible flags (O_PATH | O_DIRECT)",
		  .how.flags = O_PATH | O_सूचीECT, .err = -EINVAL पूर्ण,
		अणु .name = "incompatible flags (O_PATH | O_LARGEFILE)",
		  .how.flags = O_PATH | O_LARGEखाता, .err = -EINVAL पूर्ण,

		/* ->mode must only be set with O_अणुCREAT,TMPखातापूर्ण. */
		अणु .name = "non-zero how.mode and O_RDONLY",
		  .how.flags = O_RDONLY, .how.mode = 0600, .err = -EINVAL पूर्ण,
		अणु .name = "non-zero how.mode and O_PATH",
		  .how.flags = O_PATH,   .how.mode = 0600, .err = -EINVAL पूर्ण,
		अणु .name = "valid how.mode and O_CREAT",
		  .how.flags = O_CREAT,  .how.mode = 0600 पूर्ण,
		अणु .name = "valid how.mode and O_TMPFILE",
		  .how.flags = O_TMPखाता | O_RDWR, .how.mode = 0600 पूर्ण,
		/* ->mode must only contain 0777 bits. */
		अणु .name = "invalid how.mode and O_CREAT",
		  .how.flags = O_CREAT,
		  .how.mode = 0xFFFF, .err = -EINVAL पूर्ण,
		अणु .name = "invalid (very large) how.mode and O_CREAT",
		  .how.flags = O_CREAT,
		  .how.mode = 0xC000000000000000ULL, .err = -EINVAL पूर्ण,
		अणु .name = "invalid how.mode and O_TMPFILE",
		  .how.flags = O_TMPखाता | O_RDWR,
		  .how.mode = 0x1337, .err = -EINVAL पूर्ण,
		अणु .name = "invalid (very large) how.mode and O_TMPFILE",
		  .how.flags = O_TMPखाता | O_RDWR,
		  .how.mode = 0x0000A00000000000ULL, .err = -EINVAL पूर्ण,

		/* ->resolve flags must not conflict. */
		अणु .name = "incompatible resolve flags (BENEATH | IN_ROOT)",
		  .how.flags = O_RDONLY,
		  .how.resolve = RESOLVE_BENEATH | RESOLVE_IN_ROOT,
		  .err = -EINVAL पूर्ण,

		/* ->resolve must only contain RESOLVE_* flags. */
		अणु .name = "invalid how.resolve and O_RDONLY",
		  .how.flags = O_RDONLY,
		  .how.resolve = 0x1337, .err = -EINVAL पूर्ण,
		अणु .name = "invalid how.resolve and O_CREAT",
		  .how.flags = O_CREAT,
		  .how.resolve = 0x1337, .err = -EINVAL पूर्ण,
		अणु .name = "invalid how.resolve and O_TMPFILE",
		  .how.flags = O_TMPखाता | O_RDWR,
		  .how.resolve = 0x1337, .err = -EINVAL पूर्ण,
		अणु .name = "invalid how.resolve and O_PATH",
		  .how.flags = O_PATH,
		  .how.resolve = 0x1337, .err = -EINVAL पूर्ण,
	पूर्ण;

	BUILD_BUG_ON(ARRAY_LEN(tests) != NUM_OPENAT2_FLAG_TESTS);

	क्रम (पूर्णांक i = 0; i < ARRAY_LEN(tests); i++) अणु
		पूर्णांक fd, fdflags = -1;
		अक्षर *path, *fdpath = शून्य;
		bool failed = false;
		काष्ठा flag_test *test = &tests[i];
		व्योम (*resultfn)(स्थिर अक्षर *msg, ...) = ksft_test_result_pass;

		अगर (!खोलोat2_supported) अणु
			ksft_prपूर्णांक_msg("openat2(2) unsupported\n");
			resultfn = ksft_test_result_skip;
			जाओ skip;
		पूर्ण

		path = (test->how.flags & O_CREAT) ? "/tmp/ksft.openat2_tmpfile" : ".";
		unlink(path);

		fd = sys_खोलोat2(AT_FDCWD, path, &test->how);
		अगर (test->err >= 0)
			failed = (fd < 0);
		अन्यथा
			failed = (fd != test->err);
		अगर (fd >= 0) अणु
			पूर्णांक otherflags;

			fdpath = fdपढ़ोlink(fd);
			fdflags = fcntl(fd, F_GETFL);
			otherflags = fcntl(fd, F_GETFD);
			बंद(fd);

			E_निश्चित(fdflags >= 0, "fcntl F_GETFL of new fd");
			E_निश्चित(otherflags >= 0, "fcntl F_GETFD of new fd");

			/* O_CLOEXEC isn't shown in F_GETFL. */
			अगर (otherflags & FD_CLOEXEC)
				fdflags |= O_CLOEXEC;
			/* O_CREAT is hidden from F_GETFL. */
			अगर (test->how.flags & O_CREAT)
				fdflags |= O_CREAT;
			अगर (!(test->how.flags & O_LARGEखाता))
				fdflags &= ~O_LARGEखाता;
			failed |= (fdflags != test->how.flags);
		पूर्ण

		अगर (failed) अणु
			resultfn = ksft_test_result_fail;

			ksft_prपूर्णांक_msg("openat2 unexpectedly returned ");
			अगर (fdpath)
				ksft_prपूर्णांक_msg("%d['%s'] with %X (!= %X)\n",
					       fd, fdpath, fdflags,
					       test->how.flags);
			अन्यथा
				ksft_prपूर्णांक_msg("%d (%s)\n", fd, म_त्रुटि(-fd));
		पूर्ण

skip:
		अगर (test->err >= 0)
			resultfn("openat2 with %s succeeds\n", test->name);
		अन्यथा
			resultfn("openat2 with %s fails with %d (%s)\n",
				 test->name, test->err, म_त्रुटि(-test->err));

		मुक्त(fdpath);
		ख_साफ(मानक_निकास);
	पूर्ण
पूर्ण

#घोषणा NUM_TESTS (NUM_OPENAT2_STRUCT_VARIATIONS * NUM_OPENAT2_STRUCT_TESTS + \
		   NUM_OPENAT2_FLAG_TESTS)

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	ksft_prपूर्णांक_header();
	ksft_set_plan(NUM_TESTS);

	test_खोलोat2_काष्ठा();
	test_खोलोat2_flags();

	अगर (ksft_get_fail_cnt() + ksft_get_error_cnt() > 0)
		ksft_निकास_fail();
	अन्यथा
		ksft_निकास_pass();
पूर्ण
