<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE
#समावेश <test_progs.h>
#समावेश <sys/स्थिति.स>
#समावेश <linux/sched.h>
#समावेश <sys/syscall.h>

#घोषणा MAX_PATH_LEN		128
#घोषणा MAX_खाताS		7

#समावेश "test_d_path.skel.h"

अटल पूर्णांक duration;

अटल काष्ठा अणु
	__u32 cnt;
	अक्षर paths[MAX_खाताS][MAX_PATH_LEN];
पूर्ण src;

अटल पूर्णांक set_pathname(पूर्णांक fd, pid_t pid)
अणु
	अक्षर buf[MAX_PATH_LEN];

	snम_लिखो(buf, MAX_PATH_LEN, "/proc/%d/fd/%d", pid, fd);
	वापस पढ़ोlink(buf, src.paths[src.cnt++], MAX_PATH_LEN);
पूर्ण

अटल पूर्णांक trigger_ख_स्थिति_events(pid_t pid)
अणु
	पूर्णांक sockfd = -1, procfd = -1, devfd = -1;
	पूर्णांक localfd = -1, indicatorfd = -1;
	पूर्णांक pipefd[2] = अणु -1, -1 पूर्ण;
	काष्ठा stat fileStat;
	पूर्णांक ret = -1;

	/* unmountable pseuकरो-fileप्रणालीs */
	अगर (CHECK(pipe(pipefd) < 0, "trigger", "pipe failed\n"))
		वापस ret;
	/* unmountable pseuकरो-fileप्रणालीs */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	अगर (CHECK(sockfd < 0, "trigger", "socket failed\n"))
		जाओ out_बंद;
	/* mountable pseuकरो-fileप्रणालीs */
	procfd = खोलो("/proc/self/comm", O_RDONLY);
	अगर (CHECK(procfd < 0, "trigger", "open /proc/self/comm failed\n"))
		जाओ out_बंद;
	devfd = खोलो("/dev/urandom", O_RDONLY);
	अगर (CHECK(devfd < 0, "trigger", "open /dev/urandom failed\n"))
		जाओ out_बंद;
	localfd = खोलो("/tmp/d_path_loadgen.txt", O_CREAT | O_RDONLY, 0644);
	अगर (CHECK(localfd < 0, "trigger", "open /tmp/d_path_loadgen.txt failed\n"))
		जाओ out_बंद;
	/* bpf_d_path will वापस path with (deleted) */
	हटाओ("/tmp/d_path_loadgen.txt");
	indicatorfd = खोलो("/tmp/", O_PATH);
	अगर (CHECK(indicatorfd < 0, "trigger", "open /tmp/ failed\n"))
		जाओ out_बंद;

	ret = set_pathname(pipefd[0], pid);
	अगर (CHECK(ret < 0, "trigger", "set_pathname failed for pipe[0]\n"))
		जाओ out_बंद;
	ret = set_pathname(pipefd[1], pid);
	अगर (CHECK(ret < 0, "trigger", "set_pathname failed for pipe[1]\n"))
		जाओ out_बंद;
	ret = set_pathname(sockfd, pid);
	अगर (CHECK(ret < 0, "trigger", "set_pathname failed for socket\n"))
		जाओ out_बंद;
	ret = set_pathname(procfd, pid);
	अगर (CHECK(ret < 0, "trigger", "set_pathname failed for proc\n"))
		जाओ out_बंद;
	ret = set_pathname(devfd, pid);
	अगर (CHECK(ret < 0, "trigger", "set_pathname failed for dev\n"))
		जाओ out_बंद;
	ret = set_pathname(localfd, pid);
	अगर (CHECK(ret < 0, "trigger", "set_pathname failed for file\n"))
		जाओ out_बंद;
	ret = set_pathname(indicatorfd, pid);
	अगर (CHECK(ret < 0, "trigger", "set_pathname failed for dir\n"))
		जाओ out_बंद;

	/* triggers vfs_getattr */
	ख_स्थिति(pipefd[0], &fileStat);
	ख_स्थिति(pipefd[1], &fileStat);
	ख_स्थिति(sockfd, &fileStat);
	ख_स्थिति(procfd, &fileStat);
	ख_स्थिति(devfd, &fileStat);
	ख_स्थिति(localfd, &fileStat);
	ख_स्थिति(indicatorfd, &fileStat);

out_बंद:
	/* triggers filp_बंद */
	बंद(pipefd[0]);
	बंद(pipefd[1]);
	बंद(sockfd);
	बंद(procfd);
	बंद(devfd);
	बंद(localfd);
	बंद(indicatorfd);
	वापस ret;
पूर्ण

व्योम test_d_path(व्योम)
अणु
	काष्ठा test_d_path__bss *bss;
	काष्ठा test_d_path *skel;
	पूर्णांक err;

	skel = test_d_path__खोलो_and_load();
	अगर (CHECK(!skel, "setup", "d_path skeleton failed\n"))
		जाओ cleanup;

	err = test_d_path__attach(skel);
	अगर (CHECK(err, "setup", "attach failed: %d\n", err))
		जाओ cleanup;

	bss = skel->bss;
	bss->my_pid = getpid();

	err = trigger_ख_स्थिति_events(bss->my_pid);
	अगर (err < 0)
		जाओ cleanup;

	अगर (CHECK(!bss->called_stat,
		  "stat",
		  "trampoline for security_inode_getattr was not called\n"))
		जाओ cleanup;

	अगर (CHECK(!bss->called_बंद,
		  "close",
		  "trampoline for filp_close was not called\n"))
		जाओ cleanup;

	क्रम (पूर्णांक i = 0; i < MAX_खाताS; i++) अणु
		CHECK(म_भेदन(src.paths[i], bss->paths_stat[i], MAX_PATH_LEN),
		      "check",
		      "failed to get stat path[%d]: %s vs %s\n",
		      i, src.paths[i], bss->paths_stat[i]);
		CHECK(म_भेदन(src.paths[i], bss->paths_बंद[i], MAX_PATH_LEN),
		      "check",
		      "failed to get close path[%d]: %s vs %s\n",
		      i, src.paths[i], bss->paths_बंद[i]);
		/* The d_path helper वापसs size plus NUL अक्षर, hence + 1 */
		CHECK(bss->rets_stat[i] != म_माप(bss->paths_stat[i]) + 1,
		      "check",
		      "failed to match stat return [%d]: %d vs %zd [%s]\n",
		      i, bss->rets_stat[i], म_माप(bss->paths_stat[i]) + 1,
		      bss->paths_stat[i]);
		CHECK(bss->rets_बंद[i] != म_माप(bss->paths_stat[i]) + 1,
		      "check",
		      "failed to match stat return [%d]: %d vs %zd [%s]\n",
		      i, bss->rets_बंद[i], म_माप(bss->paths_बंद[i]) + 1,
		      bss->paths_stat[i]);
	पूर्ण

cleanup:
	test_d_path__destroy(skel);
पूर्ण
