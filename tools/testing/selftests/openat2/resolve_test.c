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
 * Conकाष्ठा a test directory with the following काष्ठाure:
 *
 * root/
 * |-- procexe -> /proc/self/exe
 * |-- procroot -> /proc/self/root
 * |-- root/
 * |-- mnt/ [mountpoपूर्णांक]
 * |   |-- self -> ../mnt/
 * |   `-- असलself -> /mnt/
 * |-- etc/
 * |   `-- passwd
 * |-- creatlink -> /newfile3
 * |-- reletc -> etc/
 * |-- relsym -> etc/passwd
 * |-- असलetc -> /etc/
 * |-- असलsym -> /etc/passwd
 * |-- असलcheeky -> /cheeky
 * `-- cheeky/
 *     |-- असलself -> /
 *     |-- self -> ../../root/
 *     |-- garbageself -> /../../root/
 *     |-- passwd -> ../cheeky/../cheeky/../etc/../etc/passwd
 *     |-- असलpasswd -> /../cheeky/../cheeky/../etc/../etc/passwd
 *     |-- करोtकरोtlink -> ../../../../../../../../../../../../../../etc/passwd
 *     `-- garbagelink -> /../../../../../../../../../../../../../../etc/passwd
 */
पूर्णांक setup_testdir(व्योम)
अणु
	पूर्णांक dfd, पंचांगpfd;
	अक्षर स_नाम[] = "/tmp/ksft-openat2-testdir.XXXXXX";

	/* Unshare and make /पंचांगp a new directory. */
	E_unshare(CLONE_NEWNS);
	E_mount("", "/tmp", "", MS_PRIVATE, "");

	/* Make the top-level directory. */
	अगर (!mkdtemp(स_नाम))
		ksft_निकास_fail_msg("setup_testdir: failed to create tmpdir\n");
	dfd = खोलो(स_नाम, O_PATH | O_सूचीECTORY);
	अगर (dfd < 0)
		ksft_निकास_fail_msg("setup_testdir: failed to open tmpdir\n");

	/* A sub-directory which is actually used क्रम tests. */
	E_सूची_गढ़ोat(dfd, "root", 0755);
	पंचांगpfd = खोलोat(dfd, "root", O_PATH | O_सूचीECTORY);
	अगर (पंचांगpfd < 0)
		ksft_निकास_fail_msg("setup_testdir: failed to open tmpdir\n");
	बंद(dfd);
	dfd = पंचांगpfd;

	E_symlinkat("/proc/self/exe", dfd, "procexe");
	E_symlinkat("/proc/self/root", dfd, "procroot");
	E_सूची_गढ़ोat(dfd, "root", 0755);

	/* There is no mountat(2), so use स_बदलो. */
	E_सूची_गढ़ोat(dfd, "mnt", 0755);
	E_fस_बदलो(dfd);
	E_mount("tmpfs", "./mnt", "tmpfs", MS_NOSUID | MS_NODEV, "");
	E_symlinkat("../mnt/", dfd, "mnt/self");
	E_symlinkat("/mnt/", dfd, "mnt/absself");

	E_सूची_गढ़ोat(dfd, "etc", 0755);
	E_touchat(dfd, "etc/passwd");

	E_symlinkat("/newfile3", dfd, "creatlink");
	E_symlinkat("etc/", dfd, "reletc");
	E_symlinkat("etc/passwd", dfd, "relsym");
	E_symlinkat("/etc/", dfd, "absetc");
	E_symlinkat("/etc/passwd", dfd, "abssym");
	E_symlinkat("/cheeky", dfd, "abscheeky");

	E_सूची_गढ़ोat(dfd, "cheeky", 0755);

	E_symlinkat("/", dfd, "cheeky/absself");
	E_symlinkat("../../root/", dfd, "cheeky/self");
	E_symlinkat("/../../root/", dfd, "cheeky/garbageself");

	E_symlinkat("../cheeky/../etc/../etc/passwd", dfd, "cheeky/passwd");
	E_symlinkat("/../cheeky/../etc/../etc/passwd", dfd, "cheeky/abspasswd");

	E_symlinkat("../../../../../../../../../../../../../../etc/passwd",
		    dfd, "cheeky/dotdotlink");
	E_symlinkat("/../../../../../../../../../../../../../../etc/passwd",
		    dfd, "cheeky/garbagelink");

	वापस dfd;
पूर्ण

काष्ठा basic_test अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *dir;
	स्थिर अक्षर *path;
	काष्ठा खोलो_how how;
	bool pass;
	जोड़ अणु
		पूर्णांक err;
		स्थिर अक्षर *path;
	पूर्ण out;
पूर्ण;

#घोषणा NUM_OPENAT2_OPATH_TESTS 88

व्योम test_खोलोat2_opath_tests(व्योम)
अणु
	पूर्णांक rootfd, hardcoded_fd;
	अक्षर *procselfexe, *hardcoded_fdpath;

	E_aप्र_लिखो(&procselfexe, "/proc/%d/exe", getpid());
	rootfd = setup_testdir();

	hardcoded_fd = खोलो("/dev/null", O_RDONLY);
	E_निश्चित(hardcoded_fd >= 0, "open fd to hardcode");
	E_aप्र_लिखो(&hardcoded_fdpath, "self/fd/%d", hardcoded_fd);

	काष्ठा basic_test tests[] = अणु
		/** RESOLVE_BENEATH **/
		/* Attempts to cross dirfd should be blocked. */
		अणु .name = "[beneath] jump to /",
		  .path = "/",			.how.resolve = RESOLVE_BENEATH,
		  .out.err = -EXDEV,		.pass = false पूर्ण,
		अणु .name = "[beneath] absolute link to $root",
		  .path = "cheeky/absself",	.how.resolve = RESOLVE_BENEATH,
		  .out.err = -EXDEV,		.pass = false पूर्ण,
		अणु .name = "[beneath] chained absolute links to $root",
		  .path = "abscheeky/absself",	.how.resolve = RESOLVE_BENEATH,
		  .out.err = -EXDEV,		.pass = false पूर्ण,
		अणु .name = "[beneath] jump outside $root",
		  .path = "..",			.how.resolve = RESOLVE_BENEATH,
		  .out.err = -EXDEV,		.pass = false पूर्ण,
		अणु .name = "[beneath] temporary jump outside $root",
		  .path = "../root/",		.how.resolve = RESOLVE_BENEATH,
		  .out.err = -EXDEV,		.pass = false पूर्ण,
		अणु .name = "[beneath] symlink temporary jump outside $root",
		  .path = "cheeky/self",	.how.resolve = RESOLVE_BENEATH,
		  .out.err = -EXDEV,		.pass = false पूर्ण,
		अणु .name = "[beneath] chained symlink temporary jump outside $root",
		  .path = "abscheeky/self",	.how.resolve = RESOLVE_BENEATH,
		  .out.err = -EXDEV,		.pass = false पूर्ण,
		अणु .name = "[beneath] garbage links to $root",
		  .path = "cheeky/garbageself",	.how.resolve = RESOLVE_BENEATH,
		  .out.err = -EXDEV,		.pass = false पूर्ण,
		अणु .name = "[beneath] chained garbage links to $root",
		  .path = "abscheeky/garbageself", .how.resolve = RESOLVE_BENEATH,
		  .out.err = -EXDEV,		.pass = false पूर्ण,
		/* Only relative paths that stay inside dirfd should work. */
		अणु .name = "[beneath] ordinary path to 'root'",
		  .path = "root",		.how.resolve = RESOLVE_BENEATH,
		  .out.path = "root",		.pass = true पूर्ण,
		अणु .name = "[beneath] ordinary path to 'etc'",
		  .path = "etc",		.how.resolve = RESOLVE_BENEATH,
		  .out.path = "etc",		.pass = true पूर्ण,
		अणु .name = "[beneath] ordinary path to 'etc/passwd'",
		  .path = "etc/passwd",		.how.resolve = RESOLVE_BENEATH,
		  .out.path = "etc/passwd",	.pass = true पूर्ण,
		अणु .name = "[beneath] relative symlink inside $root",
		  .path = "relsym",		.how.resolve = RESOLVE_BENEATH,
		  .out.path = "etc/passwd",	.pass = true पूर्ण,
		अणु .name = "[beneath] chained-'..' relative symlink inside $root",
		  .path = "cheeky/passwd",	.how.resolve = RESOLVE_BENEATH,
		  .out.path = "etc/passwd",	.pass = true पूर्ण,
		अणु .name = "[beneath] absolute symlink component outside $root",
		  .path = "abscheeky/passwd",	.how.resolve = RESOLVE_BENEATH,
		  .out.err = -EXDEV,		.pass = false पूर्ण,
		अणु .name = "[beneath] absolute symlink target outside $root",
		  .path = "abssym",		.how.resolve = RESOLVE_BENEATH,
		  .out.err = -EXDEV,		.pass = false पूर्ण,
		अणु .name = "[beneath] absolute path outside $root",
		  .path = "/etc/passwd",	.how.resolve = RESOLVE_BENEATH,
		  .out.err = -EXDEV,		.pass = false पूर्ण,
		अणु .name = "[beneath] cheeky absolute path outside $root",
		  .path = "cheeky/abspasswd",	.how.resolve = RESOLVE_BENEATH,
		  .out.err = -EXDEV,		.pass = false पूर्ण,
		अणु .name = "[beneath] chained cheeky absolute path outside $root",
		  .path = "abscheeky/abspasswd", .how.resolve = RESOLVE_BENEATH,
		  .out.err = -EXDEV,		.pass = false पूर्ण,
		/* Tricky paths should fail. */
		अणु .name = "[beneath] tricky '..'-chained symlink outside $root",
		  .path = "cheeky/dotdotlink",	.how.resolve = RESOLVE_BENEATH,
		  .out.err = -EXDEV,		.pass = false पूर्ण,
		अणु .name = "[beneath] tricky absolute + '..'-chained symlink outside $root",
		  .path = "abscheeky/dotdotlink", .how.resolve = RESOLVE_BENEATH,
		  .out.err = -EXDEV,		.pass = false पूर्ण,
		अणु .name = "[beneath] tricky garbage link outside $root",
		  .path = "cheeky/garbagelink",	.how.resolve = RESOLVE_BENEATH,
		  .out.err = -EXDEV,		.pass = false पूर्ण,
		अणु .name = "[beneath] tricky absolute + garbage link outside $root",
		  .path = "abscheeky/garbagelink", .how.resolve = RESOLVE_BENEATH,
		  .out.err = -EXDEV,		.pass = false पूर्ण,

		/** RESOLVE_IN_ROOT **/
		/* All attempts to cross the dirfd will be scoped-to-root. */
		अणु .name = "[in_root] jump to /",
		  .path = "/",			.how.resolve = RESOLVE_IN_ROOT,
		  .out.path = शून्य,		.pass = true पूर्ण,
		अणु .name = "[in_root] absolute symlink to /root",
		  .path = "cheeky/absself",	.how.resolve = RESOLVE_IN_ROOT,
		  .out.path = शून्य,		.pass = true पूर्ण,
		अणु .name = "[in_root] chained absolute symlinks to /root",
		  .path = "abscheeky/absself",	.how.resolve = RESOLVE_IN_ROOT,
		  .out.path = शून्य,		.pass = true पूर्ण,
		अणु .name = "[in_root] '..' at root",
		  .path = "..",			.how.resolve = RESOLVE_IN_ROOT,
		  .out.path = शून्य,		.pass = true पूर्ण,
		अणु .name = "[in_root] '../root' at root",
		  .path = "../root/",		.how.resolve = RESOLVE_IN_ROOT,
		  .out.path = "root",		.pass = true पूर्ण,
		अणु .name = "[in_root] relative symlink containing '..' above root",
		  .path = "cheeky/self",	.how.resolve = RESOLVE_IN_ROOT,
		  .out.path = "root",		.pass = true पूर्ण,
		अणु .name = "[in_root] garbage link to /root",
		  .path = "cheeky/garbageself",	.how.resolve = RESOLVE_IN_ROOT,
		  .out.path = "root",		.pass = true पूर्ण,
		अणु .name = "[in_root] chained garbage links to /root",
		  .path = "abscheeky/garbageself", .how.resolve = RESOLVE_IN_ROOT,
		  .out.path = "root",		.pass = true पूर्ण,
		अणु .name = "[in_root] relative path to 'root'",
		  .path = "root",		.how.resolve = RESOLVE_IN_ROOT,
		  .out.path = "root",		.pass = true पूर्ण,
		अणु .name = "[in_root] relative path to 'etc'",
		  .path = "etc",		.how.resolve = RESOLVE_IN_ROOT,
		  .out.path = "etc",		.pass = true पूर्ण,
		अणु .name = "[in_root] relative path to 'etc/passwd'",
		  .path = "etc/passwd",		.how.resolve = RESOLVE_IN_ROOT,
		  .out.path = "etc/passwd",	.pass = true पूर्ण,
		अणु .name = "[in_root] relative symlink to 'etc/passwd'",
		  .path = "relsym",		.how.resolve = RESOLVE_IN_ROOT,
		  .out.path = "etc/passwd",	.pass = true पूर्ण,
		अणु .name = "[in_root] chained-'..' relative symlink to 'etc/passwd'",
		  .path = "cheeky/passwd",	.how.resolve = RESOLVE_IN_ROOT,
		  .out.path = "etc/passwd",	.pass = true पूर्ण,
		अणु .name = "[in_root] chained-'..' absolute + relative symlink to 'etc/passwd'",
		  .path = "abscheeky/passwd",	.how.resolve = RESOLVE_IN_ROOT,
		  .out.path = "etc/passwd",	.pass = true पूर्ण,
		अणु .name = "[in_root] absolute symlink to 'etc/passwd'",
		  .path = "abssym",		.how.resolve = RESOLVE_IN_ROOT,
		  .out.path = "etc/passwd",	.pass = true पूर्ण,
		अणु .name = "[in_root] absolute path 'etc/passwd'",
		  .path = "/etc/passwd",	.how.resolve = RESOLVE_IN_ROOT,
		  .out.path = "etc/passwd",	.pass = true पूर्ण,
		अणु .name = "[in_root] cheeky absolute path 'etc/passwd'",
		  .path = "cheeky/abspasswd",	.how.resolve = RESOLVE_IN_ROOT,
		  .out.path = "etc/passwd",	.pass = true पूर्ण,
		अणु .name = "[in_root] chained cheeky absolute path 'etc/passwd'",
		  .path = "abscheeky/abspasswd", .how.resolve = RESOLVE_IN_ROOT,
		  .out.path = "etc/passwd",	.pass = true पूर्ण,
		अणु .name = "[in_root] tricky '..'-chained symlink outside $root",
		  .path = "cheeky/dotdotlink",	.how.resolve = RESOLVE_IN_ROOT,
		  .out.path = "etc/passwd",	.pass = true पूर्ण,
		अणु .name = "[in_root] tricky absolute + '..'-chained symlink outside $root",
		  .path = "abscheeky/dotdotlink", .how.resolve = RESOLVE_IN_ROOT,
		  .out.path = "etc/passwd",	.pass = true पूर्ण,
		अणु .name = "[in_root] tricky absolute path + absolute + '..'-chained symlink outside $root",
		  .path = "/../../../../abscheeky/dotdotlink", .how.resolve = RESOLVE_IN_ROOT,
		  .out.path = "etc/passwd",	.pass = true पूर्ण,
		अणु .name = "[in_root] tricky garbage link outside $root",
		  .path = "cheeky/garbagelink",	.how.resolve = RESOLVE_IN_ROOT,
		  .out.path = "etc/passwd",	.pass = true पूर्ण,
		अणु .name = "[in_root] tricky absolute + garbage link outside $root",
		  .path = "abscheeky/garbagelink", .how.resolve = RESOLVE_IN_ROOT,
		  .out.path = "etc/passwd",	.pass = true पूर्ण,
		अणु .name = "[in_root] tricky absolute path + absolute + garbage link outside $root",
		  .path = "/../../../../abscheeky/garbagelink", .how.resolve = RESOLVE_IN_ROOT,
		  .out.path = "etc/passwd",	.pass = true पूर्ण,
		/* O_CREAT should handle trailing symlinks correctly. */
		अणु .name = "[in_root] O_CREAT of relative path inside $root",
		  .path = "newfile1",		.how.flags = O_CREAT,
						.how.mode = 0700,
						.how.resolve = RESOLVE_IN_ROOT,
		  .out.path = "newfile1",	.pass = true पूर्ण,
		अणु .name = "[in_root] O_CREAT of absolute path",
		  .path = "/newfile2",		.how.flags = O_CREAT,
						.how.mode = 0700,
						.how.resolve = RESOLVE_IN_ROOT,
		  .out.path = "newfile2",	.pass = true पूर्ण,
		अणु .name = "[in_root] O_CREAT of tricky symlink outside root",
		  .path = "/creatlink",		.how.flags = O_CREAT,
						.how.mode = 0700,
						.how.resolve = RESOLVE_IN_ROOT,
		  .out.path = "newfile3",	.pass = true पूर्ण,

		/** RESOLVE_NO_XDEV **/
		/* Crossing *करोwn* पूर्णांकo a mountpoपूर्णांक is disallowed. */
		अणु .name = "[no_xdev] cross into $mnt",
		  .path = "mnt",		.how.resolve = RESOLVE_NO_XDEV,
		  .out.err = -EXDEV,		.pass = false पूर्ण,
		अणु .name = "[no_xdev] cross into $mnt/",
		  .path = "mnt/",		.how.resolve = RESOLVE_NO_XDEV,
		  .out.err = -EXDEV,		.pass = false पूर्ण,
		अणु .name = "[no_xdev] cross into $mnt/.",
		  .path = "mnt/.",		.how.resolve = RESOLVE_NO_XDEV,
		  .out.err = -EXDEV,		.pass = false पूर्ण,
		/* Crossing *up* out of a mountpoपूर्णांक is disallowed. */
		अणु .name = "[no_xdev] goto mountpoint root",
		  .dir = "mnt", .path = ".",	.how.resolve = RESOLVE_NO_XDEV,
		  .out.path = "mnt",		.pass = true पूर्ण,
		अणु .name = "[no_xdev] cross up through '..'",
		  .dir = "mnt", .path = "..",	.how.resolve = RESOLVE_NO_XDEV,
		  .out.err = -EXDEV,		.pass = false पूर्ण,
		अणु .name = "[no_xdev] temporary cross up through '..'",
		  .dir = "mnt", .path = "../mnt", .how.resolve = RESOLVE_NO_XDEV,
		  .out.err = -EXDEV,		.pass = false पूर्ण,
		अणु .name = "[no_xdev] temporary relative symlink cross up",
		  .dir = "mnt", .path = "self",	.how.resolve = RESOLVE_NO_XDEV,
		  .out.err = -EXDEV,		.pass = false पूर्ण,
		अणु .name = "[no_xdev] temporary absolute symlink cross up",
		  .dir = "mnt", .path = "absself", .how.resolve = RESOLVE_NO_XDEV,
		  .out.err = -EXDEV,		.pass = false पूर्ण,
		/* Jumping to "/" is ok, but later components cannot cross. */
		अणु .name = "[no_xdev] jump to / directly",
		  .dir = "mnt", .path = "/",	.how.resolve = RESOLVE_NO_XDEV,
		  .out.path = "/",		.pass = true पूर्ण,
		अणु .name = "[no_xdev] jump to / (from /) directly",
		  .dir = "/", .path = "/",	.how.resolve = RESOLVE_NO_XDEV,
		  .out.path = "/",		.pass = true पूर्ण,
		अणु .name = "[no_xdev] jump to / then proc",
		  .path = "/proc/1",		.how.resolve = RESOLVE_NO_XDEV,
		  .out.err = -EXDEV,		.pass = false पूर्ण,
		अणु .name = "[no_xdev] jump to / then tmp",
		  .path = "/tmp",		.how.resolve = RESOLVE_NO_XDEV,
		  .out.err = -EXDEV,		.pass = false पूर्ण,
		/* Magic-links are blocked since they can चयन vfsmounts. */
		अणु .name = "[no_xdev] cross through magic-link to self/root",
		  .dir = "/proc", .path = "self/root", 	.how.resolve = RESOLVE_NO_XDEV,
		  .out.err = -EXDEV,			.pass = false पूर्ण,
		अणु .name = "[no_xdev] cross through magic-link to self/cwd",
		  .dir = "/proc", .path = "self/cwd",	.how.resolve = RESOLVE_NO_XDEV,
		  .out.err = -EXDEV,			.pass = false पूर्ण,
		/* Except magic-link jumps inside the same vfsmount. */
		अणु .name = "[no_xdev] jump through magic-link to same procfs",
		  .dir = "/proc", .path = hardcoded_fdpath, .how.resolve = RESOLVE_NO_XDEV,
		  .out.path = "/proc",			    .pass = true, पूर्ण,

		/** RESOLVE_NO_MAGICLINKS **/
		/* Regular symlinks should work. */
		अणु .name = "[no_magiclinks] ordinary relative symlink",
		  .path = "relsym",		.how.resolve = RESOLVE_NO_MAGICLINKS,
		  .out.path = "etc/passwd",	.pass = true पूर्ण,
		/* Magic-links should not work. */
		अणु .name = "[no_magiclinks] symlink to magic-link",
		  .path = "procexe",		.how.resolve = RESOLVE_NO_MAGICLINKS,
		  .out.err = -ELOOP,		.pass = false पूर्ण,
		अणु .name = "[no_magiclinks] normal path to magic-link",
		  .path = "/proc/self/exe",	.how.resolve = RESOLVE_NO_MAGICLINKS,
		  .out.err = -ELOOP,		.pass = false पूर्ण,
		अणु .name = "[no_magiclinks] normal path to magic-link with O_NOFOLLOW",
		  .path = "/proc/self/exe",	.how.flags = O_NOFOLLOW,
						.how.resolve = RESOLVE_NO_MAGICLINKS,
		  .out.path = procselfexe,	.pass = true पूर्ण,
		अणु .name = "[no_magiclinks] symlink to magic-link path component",
		  .path = "procroot/etc",	.how.resolve = RESOLVE_NO_MAGICLINKS,
		  .out.err = -ELOOP,		.pass = false पूर्ण,
		अणु .name = "[no_magiclinks] magic-link path component",
		  .path = "/proc/self/root/etc", .how.resolve = RESOLVE_NO_MAGICLINKS,
		  .out.err = -ELOOP,		.pass = false पूर्ण,
		अणु .name = "[no_magiclinks] magic-link path component with O_NOFOLLOW",
		  .path = "/proc/self/root/etc", .how.flags = O_NOFOLLOW,
						 .how.resolve = RESOLVE_NO_MAGICLINKS,
		  .out.err = -ELOOP,		.pass = false पूर्ण,

		/** RESOLVE_NO_SYMLINKS **/
		/* Normal paths should work. */
		अणु .name = "[no_symlinks] ordinary path to '.'",
		  .path = ".",			.how.resolve = RESOLVE_NO_SYMLINKS,
		  .out.path = शून्य,		.pass = true पूर्ण,
		अणु .name = "[no_symlinks] ordinary path to 'root'",
		  .path = "root",		.how.resolve = RESOLVE_NO_SYMLINKS,
		  .out.path = "root",		.pass = true पूर्ण,
		अणु .name = "[no_symlinks] ordinary path to 'etc'",
		  .path = "etc",		.how.resolve = RESOLVE_NO_SYMLINKS,
		  .out.path = "etc",		.pass = true पूर्ण,
		अणु .name = "[no_symlinks] ordinary path to 'etc/passwd'",
		  .path = "etc/passwd",		.how.resolve = RESOLVE_NO_SYMLINKS,
		  .out.path = "etc/passwd",	.pass = true पूर्ण,
		/* Regular symlinks are blocked. */
		अणु .name = "[no_symlinks] relative symlink target",
		  .path = "relsym",		.how.resolve = RESOLVE_NO_SYMLINKS,
		  .out.err = -ELOOP,		.pass = false पूर्ण,
		अणु .name = "[no_symlinks] relative symlink component",
		  .path = "reletc/passwd",	.how.resolve = RESOLVE_NO_SYMLINKS,
		  .out.err = -ELOOP,		.pass = false पूर्ण,
		अणु .name = "[no_symlinks] absolute symlink target",
		  .path = "abssym",		.how.resolve = RESOLVE_NO_SYMLINKS,
		  .out.err = -ELOOP,		.pass = false पूर्ण,
		अणु .name = "[no_symlinks] absolute symlink component",
		  .path = "absetc/passwd",	.how.resolve = RESOLVE_NO_SYMLINKS,
		  .out.err = -ELOOP,		.pass = false पूर्ण,
		अणु .name = "[no_symlinks] cheeky garbage link",
		  .path = "cheeky/garbagelink",	.how.resolve = RESOLVE_NO_SYMLINKS,
		  .out.err = -ELOOP,		.pass = false पूर्ण,
		अणु .name = "[no_symlinks] cheeky absolute + garbage link",
		  .path = "abscheeky/garbagelink", .how.resolve = RESOLVE_NO_SYMLINKS,
		  .out.err = -ELOOP,		.pass = false पूर्ण,
		अणु .name = "[no_symlinks] cheeky absolute + absolute symlink",
		  .path = "abscheeky/absself",	.how.resolve = RESOLVE_NO_SYMLINKS,
		  .out.err = -ELOOP,		.pass = false पूर्ण,
		/* Trailing symlinks with NO_FOLLOW. */
		अणु .name = "[no_symlinks] relative symlink with O_NOFOLLOW",
		  .path = "relsym",		.how.flags = O_NOFOLLOW,
						.how.resolve = RESOLVE_NO_SYMLINKS,
		  .out.path = "relsym",		.pass = true पूर्ण,
		अणु .name = "[no_symlinks] absolute symlink with O_NOFOLLOW",
		  .path = "abssym",		.how.flags = O_NOFOLLOW,
						.how.resolve = RESOLVE_NO_SYMLINKS,
		  .out.path = "abssym",		.pass = true पूर्ण,
		अणु .name = "[no_symlinks] trailing symlink with O_NOFOLLOW",
		  .path = "cheeky/garbagelink",	.how.flags = O_NOFOLLOW,
						.how.resolve = RESOLVE_NO_SYMLINKS,
		  .out.path = "cheeky/garbagelink", .pass = true पूर्ण,
		अणु .name = "[no_symlinks] multiple symlink components with O_NOFOLLOW",
		  .path = "abscheeky/absself",	.how.flags = O_NOFOLLOW,
						.how.resolve = RESOLVE_NO_SYMLINKS,
		  .out.err = -ELOOP,		.pass = false पूर्ण,
		अणु .name = "[no_symlinks] multiple symlink (and garbage link) components with O_NOFOLLOW",
		  .path = "abscheeky/garbagelink", .how.flags = O_NOFOLLOW,
						   .how.resolve = RESOLVE_NO_SYMLINKS,
		  .out.err = -ELOOP,		.pass = false पूर्ण,
	पूर्ण;

	BUILD_BUG_ON(ARRAY_LEN(tests) != NUM_OPENAT2_OPATH_TESTS);

	क्रम (पूर्णांक i = 0; i < ARRAY_LEN(tests); i++) अणु
		पूर्णांक dfd, fd;
		अक्षर *fdpath = शून्य;
		bool failed;
		व्योम (*resultfn)(स्थिर अक्षर *msg, ...) = ksft_test_result_pass;
		काष्ठा basic_test *test = &tests[i];

		अगर (!खोलोat2_supported) अणु
			ksft_prपूर्णांक_msg("openat2(2) unsupported\n");
			resultfn = ksft_test_result_skip;
			जाओ skip;
		पूर्ण

		/* Auto-set O_PATH. */
		अगर (!(test->how.flags & O_CREAT))
			test->how.flags |= O_PATH;

		अगर (test->dir)
			dfd = खोलोat(rootfd, test->dir, O_PATH | O_सूचीECTORY);
		अन्यथा
			dfd = dup(rootfd);
		E_निश्चित(dfd, "failed to openat root '%s': %m", test->dir);

		E_dup2(dfd, hardcoded_fd);

		fd = sys_खोलोat2(dfd, test->path, &test->how);
		अगर (test->pass)
			failed = (fd < 0 || !fdequal(fd, rootfd, test->out.path));
		अन्यथा
			failed = (fd != test->out.err);
		अगर (fd >= 0) अणु
			fdpath = fdपढ़ोlink(fd);
			बंद(fd);
		पूर्ण
		बंद(dfd);

		अगर (failed) अणु
			resultfn = ksft_test_result_fail;

			ksft_prपूर्णांक_msg("openat2 unexpectedly returned ");
			अगर (fdpath)
				ksft_prपूर्णांक_msg("%d['%s']\n", fd, fdpath);
			अन्यथा
				ksft_prपूर्णांक_msg("%d (%s)\n", fd, म_त्रुटि(-fd));
		पूर्ण

skip:
		अगर (test->pass)
			resultfn("%s gives path '%s'\n", test->name,
				 test->out.path ?: ".");
		अन्यथा
			resultfn("%s fails with %d (%s)\n", test->name,
				 test->out.err, म_त्रुटि(-test->out.err));

		ख_साफ(मानक_निकास);
		मुक्त(fdpath);
	पूर्ण

	मुक्त(procselfexe);
	बंद(rootfd);

	मुक्त(hardcoded_fdpath);
	बंद(hardcoded_fd);
पूर्ण

#घोषणा NUM_TESTS NUM_OPENAT2_OPATH_TESTS

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	ksft_prपूर्णांक_header();
	ksft_set_plan(NUM_TESTS);

	/* NOTE: We should be checking क्रम CAP_SYS_ADMIN here... */
	अगर (geteuid() != 0)
		ksft_निकास_skip("all tests require euid == 0\n");

	test_खोलोat2_opath_tests();

	अगर (ksft_get_fail_cnt() + ksft_get_error_cnt() > 0)
		ksft_निकास_fail();
	अन्यथा
		ksft_निकास_pass();
पूर्ण
