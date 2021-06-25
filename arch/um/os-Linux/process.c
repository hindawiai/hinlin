<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015 Thomas Meyer (thomas@m3y3r.de)
 * Copyright (C) 2002 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <संकेत.स>
#समावेश <fcntl.h>
#समावेश <sys/mman.h>
#समावेश <sys/ptrace.h>
#समावेश <sys/रुको.h>
#समावेश <यंत्र/unistd.h>
#समावेश <init.h>
#समावेश <दीर्घ_लाँघ.h>
#समावेश <os.h>

#घोषणा ARBITRARY_ADDR -1
#घोषणा FAILURE_PID    -1

#घोषणा STAT_PATH_LEN माप("/proc/#######/stat\0")
#घोषणा COMM_SCANF "%*[^)])"

अचिन्हित दीर्घ os_process_pc(पूर्णांक pid)
अणु
	अक्षर proc_stat[STAT_PATH_LEN], buf[256];
	अचिन्हित दीर्घ pc = ARBITRARY_ADDR;
	पूर्णांक fd, err;

	प्र_लिखो(proc_stat, "/proc/%d/stat", pid);
	fd = खोलो(proc_stat, O_RDONLY, 0);
	अगर (fd < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "os_process_pc - couldn't open '%s', "
		       "errno = %d\n", proc_stat, त्रुटि_सं);
		जाओ out;
	पूर्ण
	CATCH_EINTR(err = पढ़ो(fd, buf, माप(buf)));
	अगर (err < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "os_process_pc - couldn't read '%s', "
		       "err = %d\n", proc_stat, त्रुटि_सं);
		जाओ out_बंद;
	पूर्ण
	os_बंद_file(fd);
	pc = ARBITRARY_ADDR;
	अगर (माला_पूछो(buf, "%*d " COMM_SCANF " %*c %*d %*d %*d %*d %*d %*d %*d "
		   "%*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d "
		   "%*d %*d %*d %*d %*d %lu", &pc) != 1)
		prपूर्णांकk(UM_KERN_ERR "os_process_pc - couldn't find pc in '%s'\n",
		       buf);
 out_बंद:
	बंद(fd);
 out:
	वापस pc;
पूर्ण

पूर्णांक os_process_parent(पूर्णांक pid)
अणु
	अक्षर stat[STAT_PATH_LEN];
	अक्षर data[256];
	पूर्णांक parent = FAILURE_PID, n, fd;

	अगर (pid == -1)
		वापस parent;

	snम_लिखो(stat, माप(stat), "/proc/%d/stat", pid);
	fd = खोलो(stat, O_RDONLY, 0);
	अगर (fd < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "Couldn't open '%s', errno = %d\n", stat,
		       त्रुटि_सं);
		वापस parent;
	पूर्ण

	CATCH_EINTR(n = पढ़ो(fd, data, माप(data)));
	बंद(fd);

	अगर (n < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "Couldn't read '%s', errno = %d\n", stat,
		       त्रुटि_सं);
		वापस parent;
	पूर्ण

	parent = FAILURE_PID;
	n = माला_पूछो(data, "%*d " COMM_SCANF " %*c %d", &parent);
	अगर (n != 1)
		prपूर्णांकk(UM_KERN_ERR "Failed to scan '%s'\n", data);

	वापस parent;
पूर्ण

व्योम os_alarm_process(पूर्णांक pid)
अणु
	समाप्त(pid, SIGALRM);
पूर्ण

व्योम os_stop_process(पूर्णांक pid)
अणु
	समाप्त(pid, SIGSTOP);
पूर्ण

व्योम os_समाप्त_process(पूर्णांक pid, पूर्णांक reap_child)
अणु
	समाप्त(pid, SIGKILL);
	अगर (reap_child)
		CATCH_EINTR(रुकोpid(pid, शून्य, __WALL));
पूर्ण

/* Kill off a ptraced child by all means available.  समाप्त it normally first,
 * then PTRACE_KILL it, then PTRACE_CONT it in हाल it's in a run state from
 * which it can't निकास directly.
 */

व्योम os_समाप्त_ptraced_process(पूर्णांक pid, पूर्णांक reap_child)
अणु
	समाप्त(pid, SIGKILL);
	ptrace(PTRACE_KILL, pid);
	ptrace(PTRACE_CONT, pid);
	अगर (reap_child)
		CATCH_EINTR(रुकोpid(pid, शून्य, __WALL));
पूर्ण

/* Don't use the glibc version, which caches the result in TLS. It misses some
 * syscalls, and also अवरोधs with clone(), which करोes not unshare the TLS.
 */

पूर्णांक os_getpid(व्योम)
अणु
	वापस syscall(__NR_getpid);
पूर्ण

पूर्णांक os_getpgrp(व्योम)
अणु
	वापस getpgrp();
पूर्ण

पूर्णांक os_map_memory(व्योम *virt, पूर्णांक fd, अचिन्हित दीर्घ दीर्घ off, अचिन्हित दीर्घ len,
		  पूर्णांक r, पूर्णांक w, पूर्णांक x)
अणु
	व्योम *loc;
	पूर्णांक prot;

	prot = (r ? PROT_READ : 0) | (w ? PROT_WRITE : 0) |
		(x ? PROT_EXEC : 0);

	loc = mmap64((व्योम *) virt, len, prot, MAP_SHARED | MAP_FIXED,
		     fd, off);
	अगर (loc == MAP_FAILED)
		वापस -त्रुटि_सं;
	वापस 0;
पूर्ण

पूर्णांक os_protect_memory(व्योम *addr, अचिन्हित दीर्घ len, पूर्णांक r, पूर्णांक w, पूर्णांक x)
अणु
	पूर्णांक prot = ((r ? PROT_READ : 0) | (w ? PROT_WRITE : 0) |
		    (x ? PROT_EXEC : 0));

	अगर (mprotect(addr, len, prot) < 0)
		वापस -त्रुटि_सं;

	वापस 0;
पूर्ण

पूर्णांक os_unmap_memory(व्योम *addr, पूर्णांक len)
अणु
	पूर्णांक err;

	err = munmap(addr, len);
	अगर (err < 0)
		वापस -त्रुटि_सं;
	वापस 0;
पूर्ण

#अगर_अघोषित MADV_REMOVE
#घोषणा MADV_REMOVE KERNEL_MADV_REMOVE
#पूर्ण_अगर

पूर्णांक os_drop_memory(व्योम *addr, पूर्णांक length)
अणु
	पूर्णांक err;

	err = madvise(addr, length, MADV_REMOVE);
	अगर (err < 0)
		err = -त्रुटि_सं;
	वापस err;
पूर्ण

पूर्णांक __init can_drop_memory(व्योम)
अणु
	व्योम *addr;
	पूर्णांक fd, ok = 0;

	prपूर्णांकk(UM_KERN_INFO "Checking host MADV_REMOVE support...");
	fd = create_mem_file(UM_KERN_PAGE_SIZE);
	अगर (fd < 0) अणु
		prपूर्णांकk(UM_KERN_ERR "Creating test memory file failed, "
		       "err = %d\n", -fd);
		जाओ out;
	पूर्ण

	addr = mmap64(शून्य, UM_KERN_PAGE_SIZE, PROT_READ | PROT_WRITE,
		      MAP_SHARED, fd, 0);
	अगर (addr == MAP_FAILED) अणु
		prपूर्णांकk(UM_KERN_ERR "Mapping test memory file failed, "
		       "err = %d\n", -त्रुटि_सं);
		जाओ out_बंद;
	पूर्ण

	अगर (madvise(addr, UM_KERN_PAGE_SIZE, MADV_REMOVE) != 0) अणु
		prपूर्णांकk(UM_KERN_ERR "MADV_REMOVE failed, err = %d\n", -त्रुटि_सं);
		जाओ out_unmap;
	पूर्ण

	prपूर्णांकk(UM_KERN_CONT "OK\n");
	ok = 1;

out_unmap:
	munmap(addr, UM_KERN_PAGE_SIZE);
out_बंद:
	बंद(fd);
out:
	वापस ok;
पूर्ण

अटल पूर्णांक os_page_mincore(व्योम *addr)
अणु
	अक्षर vec[2];
	पूर्णांक ret;

	ret = mincore(addr, UM_KERN_PAGE_SIZE, vec);
	अगर (ret < 0) अणु
		अगर (त्रुटि_सं == ENOMEM || त्रुटि_सं == EINVAL)
			वापस 0;
		अन्यथा
			वापस -त्रुटि_सं;
	पूर्ण

	वापस vec[0] & 1;
पूर्ण

पूर्णांक os_mincore(व्योम *addr, अचिन्हित दीर्घ len)
अणु
	अक्षर *vec;
	पूर्णांक ret, i;

	अगर (len <= UM_KERN_PAGE_SIZE)
		वापस os_page_mincore(addr);

	vec = सुस्मृति(1, (len + UM_KERN_PAGE_SIZE - 1) / UM_KERN_PAGE_SIZE);
	अगर (!vec)
		वापस -ENOMEM;

	ret = mincore(addr, UM_KERN_PAGE_SIZE, vec);
	अगर (ret < 0) अणु
		अगर (त्रुटि_सं == ENOMEM || त्रुटि_सं == EINVAL)
			ret = 0;
		अन्यथा
			ret = -त्रुटि_सं;

		जाओ out;
	पूर्ण

	क्रम (i = 0; i < ((len + UM_KERN_PAGE_SIZE - 1) / UM_KERN_PAGE_SIZE); i++) अणु
		अगर (!(vec[i] & 1)) अणु
			ret = 0;
			जाओ out;
		पूर्ण
	पूर्ण

	ret = 1;
out:
	मुक्त(vec);
	वापस ret;
पूर्ण

व्योम init_new_thपढ़ो_संकेतs(व्योम)
अणु
	set_handler(संक_अंश);
	set_handler(SIGTRAP);
	set_handler(संक_भ_त्रुटि);
	set_handler(संक_अवैध);
	set_handler(SIGBUS);
	संकेत(SIGHUP, संक_छोड़ो);
	set_handler(SIGIO);
	संकेत(SIGWINCH, संक_छोड़ो);
पूर्ण
