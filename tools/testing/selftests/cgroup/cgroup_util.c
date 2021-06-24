<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#घोषणा _GNU_SOURCE

#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <linux/सीमा.स>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <unistd.h>

#समावेश "cgroup_util.h"
#समावेश "../clone3/clone3_selftests.h"

अटल sमाप_प्रकार पढ़ो_text(स्थिर अक्षर *path, अक्षर *buf, माप_प्रकार max_len)
अणु
	sमाप_प्रकार len;
	पूर्णांक fd;

	fd = खोलो(path, O_RDONLY);
	अगर (fd < 0)
		वापस fd;

	len = पढ़ो(fd, buf, max_len - 1);
	अगर (len < 0)
		जाओ out;

	buf[len] = 0;
out:
	बंद(fd);
	वापस len;
पूर्ण

अटल sमाप_प्रकार ग_लिखो_text(स्थिर अक्षर *path, अक्षर *buf, sमाप_प्रकार len)
अणु
	पूर्णांक fd;

	fd = खोलो(path, O_WRONLY | O_APPEND);
	अगर (fd < 0)
		वापस fd;

	len = ग_लिखो(fd, buf, len);
	अगर (len < 0) अणु
		बंद(fd);
		वापस len;
	पूर्ण

	बंद(fd);

	वापस len;
पूर्ण

अक्षर *cg_name(स्थिर अक्षर *root, स्थिर अक्षर *name)
अणु
	माप_प्रकार len = म_माप(root) + म_माप(name) + 2;
	अक्षर *ret = दो_स्मृति(len);

	snम_लिखो(ret, len, "%s/%s", root, name);

	वापस ret;
पूर्ण

अक्षर *cg_name_indexed(स्थिर अक्षर *root, स्थिर अक्षर *name, पूर्णांक index)
अणु
	माप_प्रकार len = म_माप(root) + म_माप(name) + 10;
	अक्षर *ret = दो_स्मृति(len);

	snम_लिखो(ret, len, "%s/%s_%d", root, name, index);

	वापस ret;
पूर्ण

अक्षर *cg_control(स्थिर अक्षर *cgroup, स्थिर अक्षर *control)
अणु
	माप_प्रकार len = म_माप(cgroup) + म_माप(control) + 2;
	अक्षर *ret = दो_स्मृति(len);

	snम_लिखो(ret, len, "%s/%s", cgroup, control);

	वापस ret;
पूर्ण

पूर्णांक cg_पढ़ो(स्थिर अक्षर *cgroup, स्थिर अक्षर *control, अक्षर *buf, माप_प्रकार len)
अणु
	अक्षर path[PATH_MAX];

	snम_लिखो(path, माप(path), "%s/%s", cgroup, control);

	अगर (पढ़ो_text(path, buf, len) >= 0)
		वापस 0;

	वापस -1;
पूर्ण

पूर्णांक cg_पढ़ो_म_भेद(स्थिर अक्षर *cgroup, स्थिर अक्षर *control,
		   स्थिर अक्षर *expected)
अणु
	माप_प्रकार size;
	अक्षर *buf;
	पूर्णांक ret;

	/* Handle the हाल of comparing against empty string */
	अगर (!expected)
		वापस -1;
	अन्यथा
		size = म_माप(expected) + 1;

	buf = दो_स्मृति(size);
	अगर (!buf)
		वापस -1;

	अगर (cg_पढ़ो(cgroup, control, buf, size)) अणु
		मुक्त(buf);
		वापस -1;
	पूर्ण

	ret = म_भेद(expected, buf);
	मुक्त(buf);
	वापस ret;
पूर्ण

पूर्णांक cg_पढ़ो_म_माला(स्थिर अक्षर *cgroup, स्थिर अक्षर *control, स्थिर अक्षर *needle)
अणु
	अक्षर buf[PAGE_SIZE];

	अगर (cg_पढ़ो(cgroup, control, buf, माप(buf)))
		वापस -1;

	वापस म_माला(buf, needle) ? 0 : -1;
पूर्ण

दीर्घ cg_पढ़ो_दीर्घ(स्थिर अक्षर *cgroup, स्थिर अक्षर *control)
अणु
	अक्षर buf[128];

	अगर (cg_पढ़ो(cgroup, control, buf, माप(buf)))
		वापस -1;

	वापस म_से_द(buf);
पूर्ण

दीर्घ cg_पढ़ो_key_दीर्घ(स्थिर अक्षर *cgroup, स्थिर अक्षर *control, स्थिर अक्षर *key)
अणु
	अक्षर buf[PAGE_SIZE];
	अक्षर *ptr;

	अगर (cg_पढ़ो(cgroup, control, buf, माप(buf)))
		वापस -1;

	ptr = म_माला(buf, key);
	अगर (!ptr)
		वापस -1;

	वापस म_से_द(ptr + म_माप(key));
पूर्ण

दीर्घ cg_पढ़ो_lc(स्थिर अक्षर *cgroup, स्थिर अक्षर *control)
अणु
	अक्षर buf[PAGE_SIZE];
	स्थिर अक्षर delim[] = "\n";
	अक्षर *line;
	दीर्घ cnt = 0;

	अगर (cg_पढ़ो(cgroup, control, buf, माप(buf)))
		वापस -1;

	क्रम (line = म_मोहर(buf, delim); line; line = म_मोहर(शून्य, delim))
		cnt++;

	वापस cnt;
पूर्ण

पूर्णांक cg_ग_लिखो(स्थिर अक्षर *cgroup, स्थिर अक्षर *control, अक्षर *buf)
अणु
	अक्षर path[PATH_MAX];
	sमाप_प्रकार len = म_माप(buf);

	snम_लिखो(path, माप(path), "%s/%s", cgroup, control);

	अगर (ग_लिखो_text(path, buf, len) == len)
		वापस 0;

	वापस -1;
पूर्ण

पूर्णांक cg_find_unअगरied_root(अक्षर *root, माप_प्रकार len)
अणु
	अक्षर buf[10 * PAGE_SIZE];
	अक्षर *fs, *mount, *type;
	स्थिर अक्षर delim[] = "\n\t ";

	अगर (पढ़ो_text("/proc/self/mounts", buf, माप(buf)) <= 0)
		वापस -1;

	/*
	 * Example:
	 * cgroup /sys/fs/cgroup cgroup2 rw,seclabel,noexec,relaसमय 0 0
	 */
	क्रम (fs = म_मोहर(buf, delim); fs; fs = म_मोहर(शून्य, delim)) अणु
		mount = म_मोहर(शून्य, delim);
		type = म_मोहर(शून्य, delim);
		म_मोहर(शून्य, delim);
		म_मोहर(शून्य, delim);
		म_मोहर(शून्य, delim);

		अगर (म_भेद(type, "cgroup2") == 0) अणु
			म_नकलन(root, mount, len);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -1;
पूर्ण

पूर्णांक cg_create(स्थिर अक्षर *cgroup)
अणु
	वापस सूची_गढ़ो(cgroup, 0644);
पूर्ण

पूर्णांक cg_रुको_क्रम_proc_count(स्थिर अक्षर *cgroup, पूर्णांक count)
अणु
	अक्षर buf[10 * PAGE_SIZE] = अणु0पूर्ण;
	पूर्णांक attempts;
	अक्षर *ptr;

	क्रम (attempts = 10; attempts >= 0; attempts--) अणु
		पूर्णांक nr = 0;

		अगर (cg_पढ़ो(cgroup, "cgroup.procs", buf, माप(buf)))
			अवरोध;

		क्रम (ptr = buf; *ptr; ptr++)
			अगर (*ptr == '\n')
				nr++;

		अगर (nr >= count)
			वापस 0;

		usleep(100000);
	पूर्ण

	वापस -1;
पूर्ण

पूर्णांक cg_समाप्तall(स्थिर अक्षर *cgroup)
अणु
	अक्षर buf[PAGE_SIZE];
	अक्षर *ptr = buf;

	अगर (cg_पढ़ो(cgroup, "cgroup.procs", buf, माप(buf)))
		वापस -1;

	जबतक (ptr < buf + माप(buf)) अणु
		पूर्णांक pid = म_से_दीर्घ(ptr, &ptr, 10);

		अगर (pid == 0)
			अवरोध;
		अगर (*ptr)
			ptr++;
		अन्यथा
			अवरोध;
		अगर (समाप्त(pid, SIGKILL))
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cg_destroy(स्थिर अक्षर *cgroup)
अणु
	पूर्णांक ret;

retry:
	ret = सूची_हटाओ(cgroup);
	अगर (ret && त्रुटि_सं == EBUSY) अणु
		cg_समाप्तall(cgroup);
		usleep(100);
		जाओ retry;
	पूर्ण

	अगर (ret && त्रुटि_सं == ENOENT)
		ret = 0;

	वापस ret;
पूर्ण

पूर्णांक cg_enter(स्थिर अक्षर *cgroup, पूर्णांक pid)
अणु
	अक्षर pidbuf[64];

	snम_लिखो(pidbuf, माप(pidbuf), "%d", pid);
	वापस cg_ग_लिखो(cgroup, "cgroup.procs", pidbuf);
पूर्ण

पूर्णांक cg_enter_current(स्थिर अक्षर *cgroup)
अणु
	वापस cg_ग_लिखो(cgroup, "cgroup.procs", "0");
पूर्ण

पूर्णांक cg_enter_current_thपढ़ो(स्थिर अक्षर *cgroup)
अणु
	वापस cg_ग_लिखो(cgroup, "cgroup.threads", "0");
पूर्ण

पूर्णांक cg_run(स्थिर अक्षर *cgroup,
	   पूर्णांक (*fn)(स्थिर अक्षर *cgroup, व्योम *arg),
	   व्योम *arg)
अणु
	पूर्णांक pid, retcode;

	pid = विभाजन();
	अगर (pid < 0) अणु
		वापस pid;
	पूर्ण अन्यथा अगर (pid == 0) अणु
		अक्षर buf[64];

		snम_लिखो(buf, माप(buf), "%d", getpid());
		अगर (cg_ग_लिखो(cgroup, "cgroup.procs", buf))
			निकास(निकास_त्रुटि);
		निकास(fn(cgroup, arg));
	पूर्ण अन्यथा अणु
		रुकोpid(pid, &retcode, 0);
		अगर (WIFEXITED(retcode))
			वापस WEXITSTATUS(retcode);
		अन्यथा
			वापस -1;
	पूर्ण
पूर्ण

pid_t clone_पूर्णांकo_cgroup(पूर्णांक cgroup_fd)
अणु
#अगर_घोषित CLONE_ARGS_SIZE_VER2
	pid_t pid;

	काष्ठा __clone_args args = अणु
		.flags = CLONE_INTO_CGROUP,
		.निकास_संकेत = SIGCHLD,
		.cgroup = cgroup_fd,
	पूर्ण;

	pid = sys_clone3(&args, माप(काष्ठा __clone_args));
	/*
	 * Verअगरy that this is a genuine test failure:
	 * ENOSYS -> clone3() not available
	 * E2BIG  -> CLONE_INTO_CGROUP not available
	 */
	अगर (pid < 0 && (त्रुटि_सं == ENOSYS || त्रुटि_सं == E2BIG))
		जाओ pretend_enosys;

	वापस pid;

pretend_enosys:
#पूर्ण_अगर
	त्रुटि_सं = ENOSYS;
	वापस -ENOSYS;
पूर्ण

पूर्णांक clone_reap(pid_t pid, पूर्णांक options)
अणु
	पूर्णांक ret;
	siginfo_t info = अणु
		.si_signo = 0,
	पूर्ण;

again:
	ret = रुकोid(P_PID, pid, &info, options | __WALL | __WNOTHREAD);
	अगर (ret < 0) अणु
		अगर (त्रुटि_सं == EINTR)
			जाओ again;
		वापस -1;
	पूर्ण

	अगर (options & WEXITED) अणु
		अगर (WIFEXITED(info.si_status))
			वापस WEXITSTATUS(info.si_status);
	पूर्ण

	अगर (options & WSTOPPED) अणु
		अगर (WIFSTOPPED(info.si_status))
			वापस WSTOPSIG(info.si_status);
	पूर्ण

	अगर (options & WCONTINUED) अणु
		अगर (WIFCONTINUED(info.si_status))
			वापस 0;
	पूर्ण

	वापस -1;
पूर्ण

पूर्णांक dirfd_खोलो_opath(स्थिर अक्षर *dir)
अणु
	वापस खोलो(dir, O_सूचीECTORY | O_CLOEXEC | O_NOFOLLOW | O_PATH);
पूर्ण

#घोषणा बंद_prot_त्रुटि_सं(fd)                                                   \
	अगर (fd >= 0) अणु                                                         \
		पूर्णांक _e_ = त्रुटि_सं;                                               \
		बंद(fd);                                                     \
		त्रुटि_सं = _e_;                                                   \
	पूर्ण

अटल पूर्णांक clone_पूर्णांकo_cgroup_run_noरुको(स्थिर अक्षर *cgroup,
					पूर्णांक (*fn)(स्थिर अक्षर *cgroup, व्योम *arg),
					व्योम *arg)
अणु
	पूर्णांक cgroup_fd;
	pid_t pid;

	cgroup_fd =  dirfd_खोलो_opath(cgroup);
	अगर (cgroup_fd < 0)
		वापस -1;

	pid = clone_पूर्णांकo_cgroup(cgroup_fd);
	बंद_prot_त्रुटि_सं(cgroup_fd);
	अगर (pid == 0)
		निकास(fn(cgroup, arg));

	वापस pid;
पूर्ण

पूर्णांक cg_run_noरुको(स्थिर अक्षर *cgroup,
		  पूर्णांक (*fn)(स्थिर अक्षर *cgroup, व्योम *arg),
		  व्योम *arg)
अणु
	पूर्णांक pid;

	pid = clone_पूर्णांकo_cgroup_run_noरुको(cgroup, fn, arg);
	अगर (pid > 0)
		वापस pid;

	/* Genuine test failure. */
	अगर (pid < 0 && त्रुटि_सं != ENOSYS)
		वापस -1;

	pid = विभाजन();
	अगर (pid == 0) अणु
		अक्षर buf[64];

		snम_लिखो(buf, माप(buf), "%d", getpid());
		अगर (cg_ग_लिखो(cgroup, "cgroup.procs", buf))
			निकास(निकास_त्रुटि);
		निकास(fn(cgroup, arg));
	पूर्ण

	वापस pid;
पूर्ण

पूर्णांक get_temp_fd(व्योम)
अणु
	वापस खोलो(".", O_TMPखाता | O_RDWR | O_EXCL);
पूर्ण

पूर्णांक alloc_pagecache(पूर्णांक fd, माप_प्रकार size)
अणु
	अक्षर buf[PAGE_SIZE];
	काष्ठा stat st;
	पूर्णांक i;

	अगर (ख_स्थिति(fd, &st))
		जाओ cleanup;

	size += st.st_size;

	अगर (ftruncate(fd, size))
		जाओ cleanup;

	क्रम (i = 0; i < size; i += माप(buf))
		पढ़ो(fd, buf, माप(buf));

	वापस 0;

cleanup:
	वापस -1;
पूर्ण

पूर्णांक alloc_anon(स्थिर अक्षर *cgroup, व्योम *arg)
अणु
	माप_प्रकार size = (अचिन्हित दीर्घ)arg;
	अक्षर *buf, *ptr;

	buf = दो_स्मृति(size);
	क्रम (ptr = buf; ptr < buf + size; ptr += PAGE_SIZE)
		*ptr = 0;

	मुक्त(buf);
	वापस 0;
पूर्ण

पूर्णांक is_swap_enabled(व्योम)
अणु
	अक्षर buf[PAGE_SIZE];
	स्थिर अक्षर delim[] = "\n";
	पूर्णांक cnt = 0;
	अक्षर *line;

	अगर (पढ़ो_text("/proc/swaps", buf, माप(buf)) <= 0)
		वापस -1;

	क्रम (line = म_मोहर(buf, delim); line; line = म_मोहर(शून्य, delim))
		cnt++;

	वापस cnt > 1;
पूर्ण

पूर्णांक set_oom_adj_score(पूर्णांक pid, पूर्णांक score)
अणु
	अक्षर path[PATH_MAX];
	पूर्णांक fd, len;

	प्र_लिखो(path, "/proc/%d/oom_score_adj", pid);

	fd = खोलो(path, O_WRONLY | O_APPEND);
	अगर (fd < 0)
		वापस fd;

	len = dम_लिखो(fd, "%d", score);
	अगर (len < 0) अणु
		बंद(fd);
		वापस len;
	पूर्ण

	बंद(fd);
	वापस 0;
पूर्ण

sमाप_प्रकार proc_पढ़ो_text(पूर्णांक pid, bool thपढ़ो, स्थिर अक्षर *item, अक्षर *buf, माप_प्रकार size)
अणु
	अक्षर path[PATH_MAX];

	अगर (!pid)
		snम_लिखो(path, माप(path), "/proc/%s/%s",
			 thपढ़ो ? "thread-self" : "self", item);
	अन्यथा
		snम_लिखो(path, माप(path), "/proc/%d/%s", pid, item);

	वापस पढ़ो_text(path, buf, size);
पूर्ण

पूर्णांक proc_पढ़ो_म_माला(पूर्णांक pid, bool thपढ़ो, स्थिर अक्षर *item, स्थिर अक्षर *needle)
अणु
	अक्षर buf[PAGE_SIZE];

	अगर (proc_पढ़ो_text(pid, thपढ़ो, item, buf, माप(buf)) < 0)
		वापस -1;

	वापस म_माला(buf, needle) ? 0 : -1;
पूर्ण

पूर्णांक clone_पूर्णांकo_cgroup_run_रुको(स्थिर अक्षर *cgroup)
अणु
	पूर्णांक cgroup_fd;
	pid_t pid;

	cgroup_fd =  dirfd_खोलो_opath(cgroup);
	अगर (cgroup_fd < 0)
		वापस -1;

	pid = clone_पूर्णांकo_cgroup(cgroup_fd);
	बंद_prot_त्रुटि_सं(cgroup_fd);
	अगर (pid < 0)
		वापस -1;

	अगर (pid == 0)
		निकास(निकास_सफल);

	/*
	 * We करोn't care whether this fails. We only care whether the initial
	 * clone succeeded.
	 */
	(व्योम)clone_reap(pid, WEXITED);
	वापस 0;
पूर्ण
