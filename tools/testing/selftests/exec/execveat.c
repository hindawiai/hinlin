<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014 Google, Inc.
 *
 * Selftests क्रम execveat(2).
 */

#अगर_अघोषित _GNU_SOURCE
#घोषणा _GNU_SOURCE  /* to get O_PATH, AT_EMPTY_PATH */
#पूर्ण_अगर
#समावेश <sys/sendfile.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/syscall.h>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <सीमा.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>

#समावेश "../kselftest.h"

अटल अक्षर दीर्घpath[2 * PATH_MAX] = "";
अटल अक्षर *envp[] = अणु "IN_TEST=yes", शून्य, शून्य पूर्ण;
अटल अक्षर *argv[] = अणु "execveat", "99", शून्य पूर्ण;

अटल पूर्णांक execveat_(पूर्णांक fd, स्थिर अक्षर *path, अक्षर **argv, अक्षर **envp,
		     पूर्णांक flags)
अणु
#अगर_घोषित __NR_execveat
	वापस syscall(__NR_execveat, fd, path, argv, envp, flags);
#अन्यथा
	त्रुटि_सं = ENOSYS;
	वापस -1;
#पूर्ण_अगर
पूर्ण

#घोषणा check_execveat_fail(fd, path, flags, त्रुटि_सं)	\
	_check_execveat_fail(fd, path, flags, त्रुटि_सं, #त्रुटि_सं)
अटल पूर्णांक _check_execveat_fail(पूर्णांक fd, स्थिर अक्षर *path, पूर्णांक flags,
				पूर्णांक expected_त्रुटि_सं, स्थिर अक्षर *त्रुटि_सं_str)
अणु
	पूर्णांक rc;

	त्रुटि_सं = 0;
	म_लिखो("Check failure of execveat(%d, '%s', %d) with %s... ",
		fd, path?:"(null)", flags, त्रुटि_सं_str);
	rc = execveat_(fd, path, argv, envp, flags);

	अगर (rc > 0) अणु
		म_लिखो("[FAIL] (unexpected success from execveat(2))\n");
		वापस 1;
	पूर्ण
	अगर (त्रुटि_सं != expected_त्रुटि_सं) अणु
		म_लिखो("[FAIL] (expected errno %d (%s) not %d (%s)\n",
			expected_त्रुटि_सं, म_त्रुटि(expected_त्रुटि_सं),
			त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
		वापस 1;
	पूर्ण
	म_लिखो("[OK]\n");
	वापस 0;
पूर्ण

अटल पूर्णांक check_execveat_invoked_rc(पूर्णांक fd, स्थिर अक्षर *path, पूर्णांक flags,
				     पूर्णांक expected_rc, पूर्णांक expected_rc2)
अणु
	पूर्णांक status;
	पूर्णांक rc;
	pid_t child;
	पूर्णांक pathlen = path ? म_माप(path) : 0;

	अगर (pathlen > 40)
		म_लिखो("Check success of execveat(%d, '%.20s...%s', %d)... ",
			fd, path, (path + pathlen - 20), flags);
	अन्यथा
		म_लिखो("Check success of execveat(%d, '%s', %d)... ",
			fd, path?:"(null)", flags);
	child = विभाजन();
	अगर (child < 0) अणु
		म_लिखो("[FAIL] (fork() failed)\n");
		वापस 1;
	पूर्ण
	अगर (child == 0) अणु
		/* Child: करो execveat(). */
		rc = execveat_(fd, path, argv, envp, flags);
		म_लिखो("[FAIL]: execveat() failed, rc=%d errno=%d (%s)\n",
			rc, त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
		निकास(1);  /* should not reach here */
	पूर्ण
	/* Parent: रुको क्रम & check child's निकास status. */
	rc = रुकोpid(child, &status, 0);
	अगर (rc != child) अणु
		म_लिखो("[FAIL] (waitpid(%d,...) returned %d)\n", child, rc);
		वापस 1;
	पूर्ण
	अगर (!WIFEXITED(status)) अणु
		म_लिखो("[FAIL] (child %d did not exit cleanly, status=%08x)\n",
			child, status);
		वापस 1;
	पूर्ण
	अगर ((WEXITSTATUS(status) != expected_rc) &&
	    (WEXITSTATUS(status) != expected_rc2)) अणु
		म_लिखो("[FAIL] (child %d exited with %d not %d nor %d)\n",
			child, WEXITSTATUS(status), expected_rc, expected_rc2);
		वापस 1;
	पूर्ण
	म_लिखो("[OK]\n");
	वापस 0;
पूर्ण

अटल पूर्णांक check_execveat(पूर्णांक fd, स्थिर अक्षर *path, पूर्णांक flags)
अणु
	वापस check_execveat_invoked_rc(fd, path, flags, 99, 99);
पूर्ण

अटल अक्षर *concat(स्थिर अक्षर *left, स्थिर अक्षर *right)
अणु
	अक्षर *result = दो_स्मृति(म_माप(left) + म_माप(right) + 1);

	म_नकल(result, left);
	म_जोड़ो(result, right);
	वापस result;
पूर्ण

अटल पूर्णांक खोलो_or_die(स्थिर अक्षर *filename, पूर्णांक flags)
अणु
	पूर्णांक fd = खोलो(filename, flags);

	अगर (fd < 0) अणु
		म_लिखो("Failed to open '%s'; "
			"check prerequisites are available\n", filename);
		निकास(1);
	पूर्ण
	वापस fd;
पूर्ण

अटल व्योम exe_cp(स्थिर अक्षर *src, स्थिर अक्षर *dest)
अणु
	पूर्णांक in_fd = खोलो_or_die(src, O_RDONLY);
	पूर्णांक out_fd = खोलो(dest, O_RDWR|O_CREAT|O_TRUNC, 0755);
	काष्ठा stat info;

	ख_स्थिति(in_fd, &info);
	sendfile(out_fd, in_fd, शून्य, info.st_size);
	बंद(in_fd);
	बंद(out_fd);
पूर्ण

#घोषणा XX_सूची_LEN 200
अटल पूर्णांक check_execveat_pathmax(पूर्णांक root_dfd, स्थिर अक्षर *src, पूर्णांक is_script)
अणु
	पूर्णांक fail = 0;
	पूर्णांक ii, count, len;
	अक्षर दीर्घname[XX_सूची_LEN + 1];
	पूर्णांक fd;

	अगर (*दीर्घpath == '\0') अणु
		/* Create a filename बंद to PATH_MAX in length */
		अक्षर *cwd = अ_लोwd(शून्य, 0);

		अगर (!cwd) अणु
			म_लिखो("Failed to getcwd(), errno=%d (%s)\n",
			       त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
			वापस 2;
		पूर्ण
		म_नकल(दीर्घpath, cwd);
		म_जोड़ो(दीर्घpath, "/");
		स_रखो(दीर्घname, 'x', XX_सूची_LEN - 1);
		दीर्घname[XX_सूची_LEN - 1] = '/';
		दीर्घname[XX_सूची_LEN] = '\0';
		count = (PATH_MAX - 3 - म_माप(cwd)) / XX_सूची_LEN;
		क्रम (ii = 0; ii < count; ii++) अणु
			म_जोड़ो(दीर्घpath, दीर्घname);
			सूची_गढ़ो(दीर्घpath, 0755);
		पूर्ण
		len = (PATH_MAX - 3 - म_माप(cwd)) - (count * XX_सूची_LEN);
		अगर (len <= 0)
			len = 1;
		स_रखो(दीर्घname, 'y', len);
		दीर्घname[len] = '\0';
		म_जोड़ो(दीर्घpath, दीर्घname);
		मुक्त(cwd);
	पूर्ण
	exe_cp(src, दीर्घpath);

	/*
	 * Execute as a pre-खोलोed file descriptor, which works whether this is
	 * a script or not (because the पूर्णांकerpreter sees a filename like
	 * "/dev/fd/20").
	 */
	fd = खोलो(दीर्घpath, O_RDONLY);
	अगर (fd > 0) अणु
		म_लिखो("Invoke copy of '%s' via filename of length %zu:\n",
			src, म_माप(दीर्घpath));
		fail += check_execveat(fd, "", AT_EMPTY_PATH);
	पूर्ण अन्यथा अणु
		म_लिखो("Failed to open length %zu filename, errno=%d (%s)\n",
			म_माप(दीर्घpath), त्रुटि_सं, म_त्रुटि(त्रुटि_सं));
		fail++;
	पूर्ण

	/*
	 * Execute as a दीर्घ pathname relative to "/".  If this is a script,
	 * the पूर्णांकerpreter will launch but fail to खोलो the script because its
	 * name ("/dev/fd/5/xxx....") is bigger than PATH_MAX.
	 *
	 * The failure code is usually 127 (POSIX: "If a command is not found,
	 * the निकास status shall be 127."), but some प्रणालीs give 126 (POSIX:
	 * "If the command name is found, but it is not an executable utility,
	 * the निकास status shall be 126."), so allow either.
	 */
	अगर (is_script)
		fail += check_execveat_invoked_rc(root_dfd, दीर्घpath + 1, 0,
						  127, 126);
	अन्यथा
		fail += check_execveat(root_dfd, दीर्घpath + 1, 0);

	वापस fail;
पूर्ण

अटल पूर्णांक run_tests(व्योम)
अणु
	पूर्णांक fail = 0;
	अक्षर *fullname = realpath("execveat", शून्य);
	अक्षर *fullname_script = realpath("script", शून्य);
	अक्षर *fullname_symlink = concat(fullname, ".symlink");
	पूर्णांक subdir_dfd = खोलो_or_die("subdir", O_सूचीECTORY|O_RDONLY);
	पूर्णांक subdir_dfd_ephemeral = खोलो_or_die("subdir.ephemeral",
					       O_सूचीECTORY|O_RDONLY);
	पूर्णांक करोt_dfd = खोलो_or_die(".", O_सूचीECTORY|O_RDONLY);
	पूर्णांक root_dfd = खोलो_or_die("/", O_सूचीECTORY|O_RDONLY);
	पूर्णांक करोt_dfd_path = खोलो_or_die(".", O_सूचीECTORY|O_RDONLY|O_PATH);
	पूर्णांक करोt_dfd_cloexec = खोलो_or_die(".", O_सूचीECTORY|O_RDONLY|O_CLOEXEC);
	पूर्णांक fd = खोलो_or_die("execveat", O_RDONLY);
	पूर्णांक fd_path = खोलो_or_die("execveat", O_RDONLY|O_PATH);
	पूर्णांक fd_symlink = खोलो_or_die("execveat.symlink", O_RDONLY);
	पूर्णांक fd_denatured = खोलो_or_die("execveat.denatured", O_RDONLY);
	पूर्णांक fd_denatured_path = खोलो_or_die("execveat.denatured",
					    O_RDONLY|O_PATH);
	पूर्णांक fd_script = खोलो_or_die("script", O_RDONLY);
	पूर्णांक fd_ephemeral = खोलो_or_die("execveat.ephemeral", O_RDONLY);
	पूर्णांक fd_ephemeral_path = खोलो_or_die("execveat.path.ephemeral",
					    O_RDONLY|O_PATH);
	पूर्णांक fd_script_ephemeral = खोलो_or_die("script.ephemeral", O_RDONLY);
	पूर्णांक fd_cloexec = खोलो_or_die("execveat", O_RDONLY|O_CLOEXEC);
	पूर्णांक fd_script_cloexec = खोलो_or_die("script", O_RDONLY|O_CLOEXEC);

	/* Check अगर we have execveat at all, and bail early अगर not */
	त्रुटि_सं = 0;
	execveat_(-1, शून्य, शून्य, शून्य, 0);
	अगर (त्रुटि_सं == ENOSYS) अणु
		ksft_निकास_skip(
			"ENOSYS calling execveat - no kernel support?\n");
	पूर्ण

	/* Change file position to confirm it करोesn't affect anything */
	lseek(fd, 10, शुरू_से);

	/* Normal executable file: */
	/*   dfd + path */
	fail += check_execveat(subdir_dfd, "../execveat", 0);
	fail += check_execveat(करोt_dfd, "execveat", 0);
	fail += check_execveat(करोt_dfd_path, "execveat", 0);
	/*   असलolute path */
	fail += check_execveat(AT_FDCWD, fullname, 0);
	/*   असलolute path with nonsense dfd */
	fail += check_execveat(99, fullname, 0);
	/*   fd + no path */
	fail += check_execveat(fd, "", AT_EMPTY_PATH);
	/*   O_CLOEXEC fd + no path */
	fail += check_execveat(fd_cloexec, "", AT_EMPTY_PATH);
	/*   O_PATH fd */
	fail += check_execveat(fd_path, "", AT_EMPTY_PATH);

	/* Mess with executable file that's alपढ़ोy खोलो: */
	/*   fd + no path to a file that's been नामd */
	नाम("execveat.ephemeral", "execveat.moved");
	fail += check_execveat(fd_ephemeral, "", AT_EMPTY_PATH);
	/*   fd + no path to a file that's been deleted */
	unlink("execveat.moved"); /* हटाओ the file now fd खोलो */
	fail += check_execveat(fd_ephemeral, "", AT_EMPTY_PATH);

	/* Mess with executable file that's alपढ़ोy खोलो with O_PATH */
	/*   fd + no path to a file that's been deleted */
	unlink("execveat.path.ephemeral");
	fail += check_execveat(fd_ephemeral_path, "", AT_EMPTY_PATH);

	/* Invalid argument failures */
	fail += check_execveat_fail(fd, "", 0, ENOENT);
	fail += check_execveat_fail(fd, शून्य, AT_EMPTY_PATH, EFAULT);

	/* Symlink to executable file: */
	/*   dfd + path */
	fail += check_execveat(करोt_dfd, "execveat.symlink", 0);
	fail += check_execveat(करोt_dfd_path, "execveat.symlink", 0);
	/*   असलolute path */
	fail += check_execveat(AT_FDCWD, fullname_symlink, 0);
	/*   fd + no path, even with AT_SYMLINK_NOFOLLOW (alपढ़ोy followed) */
	fail += check_execveat(fd_symlink, "", AT_EMPTY_PATH);
	fail += check_execveat(fd_symlink, "",
			       AT_EMPTY_PATH|AT_SYMLINK_NOFOLLOW);

	/* Symlink fails when AT_SYMLINK_NOFOLLOW set: */
	/*   dfd + path */
	fail += check_execveat_fail(करोt_dfd, "execveat.symlink",
				    AT_SYMLINK_NOFOLLOW, ELOOP);
	fail += check_execveat_fail(करोt_dfd_path, "execveat.symlink",
				    AT_SYMLINK_NOFOLLOW, ELOOP);
	/*   असलolute path */
	fail += check_execveat_fail(AT_FDCWD, fullname_symlink,
				    AT_SYMLINK_NOFOLLOW, ELOOP);

	/*  Non-regular file failure */
	fail += check_execveat_fail(करोt_dfd, "pipe", 0, EACCES);
	unlink("pipe");

	/* Shell script wrapping executable file: */
	/*   dfd + path */
	fail += check_execveat(subdir_dfd, "../script", 0);
	fail += check_execveat(करोt_dfd, "script", 0);
	fail += check_execveat(करोt_dfd_path, "script", 0);
	/*   असलolute path */
	fail += check_execveat(AT_FDCWD, fullname_script, 0);
	/*   fd + no path */
	fail += check_execveat(fd_script, "", AT_EMPTY_PATH);
	fail += check_execveat(fd_script, "",
			       AT_EMPTY_PATH|AT_SYMLINK_NOFOLLOW);
	/*   O_CLOEXEC fd fails क्रम a script (as script file inaccessible) */
	fail += check_execveat_fail(fd_script_cloexec, "", AT_EMPTY_PATH,
				    ENOENT);
	fail += check_execveat_fail(करोt_dfd_cloexec, "script", 0, ENOENT);

	/* Mess with script file that's alपढ़ोy खोलो: */
	/*   fd + no path to a file that's been नामd */
	नाम("script.ephemeral", "script.moved");
	fail += check_execveat(fd_script_ephemeral, "", AT_EMPTY_PATH);
	/*   fd + no path to a file that's been deleted */
	unlink("script.moved"); /* हटाओ the file जबतक fd खोलो */
	fail += check_execveat(fd_script_ephemeral, "", AT_EMPTY_PATH);

	/* Rename a subdirectory in the path: */
	नाम("subdir.ephemeral", "subdir.moved");
	fail += check_execveat(subdir_dfd_ephemeral, "../script", 0);
	fail += check_execveat(subdir_dfd_ephemeral, "script", 0);
	/* Remove the subdir and its contents */
	unlink("subdir.moved/script");
	unlink("subdir.moved");
	/* Shell loads via deleted subdir OK because name starts with .. */
	fail += check_execveat(subdir_dfd_ephemeral, "../script", 0);
	fail += check_execveat_fail(subdir_dfd_ephemeral, "script", 0, ENOENT);

	/* Flag values other than AT_SYMLINK_NOFOLLOW => EINVAL */
	fail += check_execveat_fail(करोt_dfd, "execveat", 0xFFFF, EINVAL);
	/* Invalid path => ENOENT */
	fail += check_execveat_fail(करोt_dfd, "no-such-file", 0, ENOENT);
	fail += check_execveat_fail(करोt_dfd_path, "no-such-file", 0, ENOENT);
	fail += check_execveat_fail(AT_FDCWD, "no-such-file", 0, ENOENT);
	/* Attempt to execute directory => EACCES */
	fail += check_execveat_fail(करोt_dfd, "", AT_EMPTY_PATH, EACCES);
	/* Attempt to execute non-executable => EACCES */
	fail += check_execveat_fail(करोt_dfd, "Makefile", 0, EACCES);
	fail += check_execveat_fail(fd_denatured, "", AT_EMPTY_PATH, EACCES);
	fail += check_execveat_fail(fd_denatured_path, "", AT_EMPTY_PATH,
				    EACCES);
	/* Attempt to execute nonsense FD => EBADF */
	fail += check_execveat_fail(99, "", AT_EMPTY_PATH, EBADF);
	fail += check_execveat_fail(99, "execveat", 0, EBADF);
	/* Attempt to execute relative to non-directory => ENOTसूची */
	fail += check_execveat_fail(fd, "execveat", 0, ENOTसूची);

	fail += check_execveat_pathmax(root_dfd, "execveat", 0);
	fail += check_execveat_pathmax(root_dfd, "script", 1);
	वापस fail;
पूर्ण

अटल व्योम prerequisites(व्योम)
अणु
	पूर्णांक fd;
	स्थिर अक्षर *script = "#!/bin/sh\nexit $*\n";

	/* Create ephemeral copies of files */
	exe_cp("execveat", "execveat.ephemeral");
	exe_cp("execveat", "execveat.path.ephemeral");
	exe_cp("script", "script.ephemeral");
	सूची_गढ़ो("subdir.ephemeral", 0755);

	fd = खोलो("subdir.ephemeral/script", O_RDWR|O_CREAT|O_TRUNC, 0755);
	ग_लिखो(fd, script, म_माप(script));
	बंद(fd);

	mkfअगरo("pipe", 0755);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक ii;
	पूर्णांक rc;
	स्थिर अक्षर *verbose = दो_पर्या("VERBOSE");

	अगर (argc >= 2) अणु
		/* If we are invoked with an argument, करोn't run tests. */
		स्थिर अक्षर *in_test = दो_पर्या("IN_TEST");

		अगर (verbose) अणु
			म_लिखो("  invoked with:");
			क्रम (ii = 0; ii < argc; ii++)
				म_लिखो(" [%d]='%s'", ii, argv[ii]);
			म_लिखो("\n");
		पूर्ण

		/* Check expected environment transferred. */
		अगर (!in_test || म_भेद(in_test, "yes") != 0) अणु
			म_लिखो("[FAIL] (no IN_TEST=yes in env)\n");
			वापस 1;
		पूर्ण

		/* Use the final argument as an निकास code. */
		rc = म_से_प(argv[argc - 1]);
		ख_साफ(मानक_निकास);
	पूर्ण अन्यथा अणु
		prerequisites();
		अगर (verbose)
			envp[1] = "VERBOSE=1";
		rc = run_tests();
		अगर (rc > 0)
			म_लिखो("%d tests failed\n", rc);
	पूर्ण
	वापस rc;
पूर्ण
