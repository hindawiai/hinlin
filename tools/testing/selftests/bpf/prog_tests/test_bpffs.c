<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2020 Facebook */
#घोषणा _GNU_SOURCE
#समावेश <sched.h>
#समावेश <sys/mount.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>
#समावेश <test_progs.h>

#घोषणा Tसूची "/sys/kernel/debug"

अटल पूर्णांक पढ़ो_iter(अक्षर *file)
अणु
	/* 1024 should be enough to get contiguous 4 "iter" letters at some poपूर्णांक */
	अक्षर buf[1024];
	पूर्णांक fd, len;

	fd = खोलो(file, 0);
	अगर (fd < 0)
		वापस -1;
	जबतक ((len = पढ़ो(fd, buf, माप(buf))) > 0)
		अगर (म_माला(buf, "iter")) अणु
			बंद(fd);
			वापस 0;
		पूर्ण
	बंद(fd);
	वापस -1;
पूर्ण

अटल पूर्णांक fn(व्योम)
अणु
	पूर्णांक err, duration = 0;

	err = unshare(CLONE_NEWNS);
	अगर (CHECK(err, "unshare", "failed: %d\n", त्रुटि_सं))
		जाओ out;

	err = mount("", "/", "", MS_REC | MS_PRIVATE, शून्य);
	अगर (CHECK(err, "mount /", "failed: %d\n", त्रुटि_सं))
		जाओ out;

	err = umount(Tसूची);
	अगर (CHECK(err, "umount " Tसूची, "failed: %d\n", त्रुटि_सं))
		जाओ out;

	err = mount("none", Tसूची, "tmpfs", 0, शून्य);
	अगर (CHECK(err, "mount", "mount root failed: %d\n", त्रुटि_सं))
		जाओ out;

	err = सूची_गढ़ो(Tसूची "/fs1", 0777);
	अगर (CHECK(err, "mkdir "Tसूची"/fs1", "failed: %d\n", त्रुटि_सं))
		जाओ out;
	err = सूची_गढ़ो(Tसूची "/fs2", 0777);
	अगर (CHECK(err, "mkdir "Tसूची"/fs2", "failed: %d\n", त्रुटि_सं))
		जाओ out;

	err = mount("bpf", Tसूची "/fs1", "bpf", 0, शून्य);
	अगर (CHECK(err, "mount bpffs "Tसूची"/fs1", "failed: %d\n", त्रुटि_सं))
		जाओ out;
	err = mount("bpf", Tसूची "/fs2", "bpf", 0, शून्य);
	अगर (CHECK(err, "mount bpffs " Tसूची "/fs2", "failed: %d\n", त्रुटि_सं))
		जाओ out;

	err = पढ़ो_iter(Tसूची "/fs1/maps.debug");
	अगर (CHECK(err, "reading " Tसूची "/fs1/maps.debug", "failed\n"))
		जाओ out;
	err = पढ़ो_iter(Tसूची "/fs2/progs.debug");
	अगर (CHECK(err, "reading " Tसूची "/fs2/progs.debug", "failed\n"))
		जाओ out;
out:
	umount(Tसूची "/fs1");
	umount(Tसूची "/fs2");
	सूची_हटाओ(Tसूची "/fs1");
	सूची_हटाओ(Tसूची "/fs2");
	umount(Tसूची);
	निकास(err);
पूर्ण

व्योम test_test_bpffs(व्योम)
अणु
	पूर्णांक err, duration = 0, status = 0;
	pid_t pid;

	pid = विभाजन();
	अगर (CHECK(pid == -1, "clone", "clone failed %d", त्रुटि_सं))
		वापस;
	अगर (pid == 0)
		fn();
	err = रुकोpid(pid, &status, 0);
	अगर (CHECK(err == -1 && त्रुटि_सं != ECHILD, "waitpid", "failed %d", त्रुटि_सं))
		वापस;
	अगर (CHECK(WEXITSTATUS(status), "bpffs test ", "failed %d", WEXITSTATUS(status)))
		वापस;
पूर्ण
