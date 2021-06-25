<शैली गुरु>
/*
 * Copyright (c) 2019 Alexey Dobriyan <aकरोbriyan@gmail.com>
 *
 * Permission to use, copy, modअगरy, and distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
/*
 * Fork and exec tiny 1 page executable which precisely controls its VM.
 * Test /proc/$PID/maps
 * Test /proc/$PID/smaps
 * Test /proc/$PID/smaps_rollup
 * Test /proc/$PID/staपंचांग
 *
 * FIXME require CONFIG_TMPFS which can be disabled
 * FIXME test other values from "smaps"
 * FIXME support other archs
 */
#अघोषित न_संशोधन
#समावेश <निश्चित.स>
#समावेश <त्रुटिसं.स>
#समावेश <sched.h>
#समावेश <संकेत.स>
#समावेश <stdbool.h>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश <sys/mount.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/रुको.h>
#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश <sys/syscall.h>
#समावेश <sys/uपन.स>
#समावेश <linux/kdev_t.h>
#समावेश <sys/समय.स>
#समावेश <sys/resource.h>

अटल अंतरभूत दीर्घ sys_execveat(पूर्णांक dirfd, स्थिर अक्षर *pathname, अक्षर **argv, अक्षर **envp, पूर्णांक flags)
अणु
	वापस syscall(SYS_execveat, dirfd, pathname, argv, envp, flags);
पूर्ण

अटल व्योम make_निजी_पंचांगp(व्योम)
अणु
	अगर (unshare(CLONE_NEWNS) == -1) अणु
		अगर (त्रुटि_सं == ENOSYS || त्रुटि_सं == EPERM) अणु
			निकास(4);
		पूर्ण
		निकास(1);
	पूर्ण
	अगर (mount(शून्य, "/", शून्य, MS_PRIVATE|MS_REC, शून्य) == -1) अणु
		निकास(1);
	पूर्ण
	अगर (mount(शून्य, "/tmp", "tmpfs", 0, शून्य) == -1) अणु
		निकास(1);
	पूर्ण
पूर्ण

अटल pid_t pid = -1;
अटल व्योम ate(व्योम)
अणु
	अगर (pid > 0) अणु
		समाप्त(pid, संक_इति);
	पूर्ण
पूर्ण

काष्ठा elf64_hdr अणु
	uपूर्णांक8_t e_ident[16];
	uपूर्णांक16_t e_type;
	uपूर्णांक16_t e_machine;
	uपूर्णांक32_t e_version;
	uपूर्णांक64_t e_entry;
	uपूर्णांक64_t e_phoff;
	uपूर्णांक64_t e_shoff;
	uपूर्णांक32_t e_flags;
	uपूर्णांक16_t e_ehsize;
	uपूर्णांक16_t e_phentsize;
	uपूर्णांक16_t e_phnum;
	uपूर्णांक16_t e_shentsize;
	uपूर्णांक16_t e_shnum;
	uपूर्णांक16_t e_shstrndx;
पूर्ण;

काष्ठा elf64_phdr अणु
	uपूर्णांक32_t p_type;
	uपूर्णांक32_t p_flags;
	uपूर्णांक64_t p_offset;
	uपूर्णांक64_t p_vaddr;
	uपूर्णांक64_t p_paddr;
	uपूर्णांक64_t p_filesz;
	uपूर्णांक64_t p_memsz;
	uपूर्णांक64_t p_align;
पूर्ण;

#अगर_घोषित __x86_64__
#घोषणा PAGE_SIZE 4096
#घोषणा VADDR (1UL << 32)
#घोषणा MAPS_OFFSET 73

#घोषणा syscall	0x0f, 0x05
#घोषणा mov_rdi(x)	\
	0x48, 0xbf,	\
	(x)&0xff, ((x)>>8)&0xff, ((x)>>16)&0xff, ((x)>>24)&0xff,	\
	((x)>>32)&0xff, ((x)>>40)&0xff, ((x)>>48)&0xff, ((x)>>56)&0xff

#घोषणा mov_rsi(x)	\
	0x48, 0xbe,	\
	(x)&0xff, ((x)>>8)&0xff, ((x)>>16)&0xff, ((x)>>24)&0xff,	\
	((x)>>32)&0xff, ((x)>>40)&0xff, ((x)>>48)&0xff, ((x)>>56)&0xff

#घोषणा mov_eax(x)	\
	0xb8, (x)&0xff, ((x)>>8)&0xff, ((x)>>16)&0xff, ((x)>>24)&0xff

अटल स्थिर uपूर्णांक8_t payload[] = अणु
	/* Casually unmap stack, vDSO and everything अन्यथा. */
	/* munmap */
	mov_rdi(VADDR + 4096),
	mov_rsi((1ULL << 47) - 4096 - VADDR - 4096),
	mov_eax(11),
	syscall,

	/* Ping parent. */
	/* ग_लिखो(0, &c, 1); */
	0x31, 0xff,					/* xor edi, edi */
	0x48, 0x8d, 0x35, 0x00, 0x00, 0x00, 0x00,	/* lea rsi, [rip] */
	0xba, 0x01, 0x00, 0x00, 0x00,			/* mov edx, 1 */
	mov_eax(1),
	syscall,

	/* 1: छोड़ो(); */
	mov_eax(34),
	syscall,

	0xeb, 0xf7,	/* jmp 1b */
पूर्ण;

अटल पूर्णांक make_exe(स्थिर uपूर्णांक8_t *payload, माप_प्रकार len)
अणु
	काष्ठा elf64_hdr h;
	काष्ठा elf64_phdr ph;

	काष्ठा iovec iov[3] = अणु
		अणु&h, माप(काष्ठा elf64_hdr)पूर्ण,
		अणु&ph, माप(काष्ठा elf64_phdr)पूर्ण,
		अणु(व्योम *)payload, lenपूर्ण,
	पूर्ण;
	पूर्णांक fd, fd1;
	अक्षर buf[64];

	स_रखो(&h, 0, माप(h));
	h.e_ident[0] = 0x7f;
	h.e_ident[1] = 'E';
	h.e_ident[2] = 'L';
	h.e_ident[3] = 'F';
	h.e_ident[4] = 2;
	h.e_ident[5] = 1;
	h.e_ident[6] = 1;
	h.e_ident[7] = 0;
	h.e_type = 2;
	h.e_machine = 0x3e;
	h.e_version = 1;
	h.e_entry = VADDR + माप(काष्ठा elf64_hdr) + माप(काष्ठा elf64_phdr);
	h.e_phoff = माप(काष्ठा elf64_hdr);
	h.e_shoff = 0;
	h.e_flags = 0;
	h.e_ehsize = माप(काष्ठा elf64_hdr);
	h.e_phentsize = माप(काष्ठा elf64_phdr);
	h.e_phnum = 1;
	h.e_shentsize = 0;
	h.e_shnum = 0;
	h.e_shstrndx = 0;

	स_रखो(&ph, 0, माप(ph));
	ph.p_type = 1;
	ph.p_flags = (1<<2)|1;
	ph.p_offset = 0;
	ph.p_vaddr = VADDR;
	ph.p_paddr = 0;
	ph.p_filesz = माप(काष्ठा elf64_hdr) + माप(काष्ठा elf64_phdr) + len;
	ph.p_memsz = माप(काष्ठा elf64_hdr) + माप(काष्ठा elf64_phdr) + len;
	ph.p_align = 4096;

	fd = खोलोat(AT_FDCWD, "/tmp", O_WRONLY|O_EXCL|O_TMPखाता, 0700);
	अगर (fd == -1) अणु
		निकास(1);
	पूर्ण

	अगर (ग_लिखोv(fd, iov, 3) != माप(काष्ठा elf64_hdr) + माप(काष्ठा elf64_phdr) + len) अणु
		निकास(1);
	पूर्ण

	/* Aव्योम ETXTBSY on exec. */
	snम_लिखो(buf, माप(buf), "/proc/self/fd/%u", fd);
	fd1 = खोलो(buf, O_RDONLY|O_CLOEXEC);
	बंद(fd);

	वापस fd1;
पूर्ण
#पूर्ण_अगर

अटल bool g_vsyscall = false;

अटल स्थिर अक्षर str_vsyscall[] =
"ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]\n";

#अगर_घोषित __x86_64__
अटल व्योम sigaction_संक_अंश(पूर्णांक _, siginfo_t *__, व्योम *___)
अणु
	_निकास(1);
पूर्ण

/*
 * vsyscall page can't be unmapped, probe it with memory load.
 */
अटल व्योम vsyscall(व्योम)
अणु
	pid_t pid;
	पूर्णांक wstatus;

	pid = विभाजन();
	अगर (pid < 0) अणु
		ख_लिखो(मानक_त्रुटि, "fork, errno %d\n", त्रुटि_सं);
		निकास(1);
	पूर्ण
	अगर (pid == 0) अणु
		काष्ठा rlimit rlim = अणु0, 0पूर्ण;
		(व्योम)setrlimit(RLIMIT_CORE, &rlim);

		/* Hide "segfault at ffffffffff600000" messages. */
		काष्ठा sigaction act;
		स_रखो(&act, 0, माप(काष्ठा sigaction));
		act.sa_flags = SA_SIGINFO;
		act.sa_sigaction = sigaction_संक_अंश;
		(व्योम)sigaction(संक_अंश, &act, शून्य);

		*(अस्थिर पूर्णांक *)0xffffffffff600000UL;
		निकास(0);
	पूर्ण
	रुकोpid(pid, &wstatus, 0);
	अगर (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 0) अणु
		g_vsyscall = true;
	पूर्ण
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	पूर्णांक pipefd[2];
	पूर्णांक exec_fd;

	vsyscall();

	निकास_पर(ate);

	make_निजी_पंचांगp();

	/* Reserve fd 0 क्रम 1-byte pipe ping from child. */
	बंद(0);
	अगर (खोलो("/", O_RDONLY|O_सूचीECTORY|O_PATH) != 0) अणु
		वापस 1;
	पूर्ण

	exec_fd = make_exe(payload, माप(payload));

	अगर (pipe(pipefd) == -1) अणु
		वापस 1;
	पूर्ण
	अगर (dup2(pipefd[1], 0) != 0) अणु
		वापस 1;
	पूर्ण

	pid = विभाजन();
	अगर (pid == -1) अणु
		वापस 1;
	पूर्ण
	अगर (pid == 0) अणु
		sys_execveat(exec_fd, "", शून्य, शून्य, AT_EMPTY_PATH);
		वापस 1;
	पूर्ण

	अक्षर _;
	अगर (पढ़ो(pipefd[0], &_, 1) != 1) अणु
		वापस 1;
	पूर्ण

	काष्ठा stat st;
	अगर (ख_स्थिति(exec_fd, &st) == -1) अणु
		वापस 1;
	पूर्ण

	/* Generate "head -n1 /proc/$PID/maps" */
	अक्षर buf0[256];
	स_रखो(buf0, ' ', माप(buf0));
	पूर्णांक len = snम_लिखो(buf0, माप(buf0),
			"%08lx-%08lx r-xp 00000000 %02lx:%02lx %llu",
			VADDR, VADDR + PAGE_SIZE,
			MAJOR(st.st_dev), MINOR(st.st_dev),
			(अचिन्हित दीर्घ दीर्घ)st.st_ino);
	buf0[len] = ' ';
	snम_लिखो(buf0 + MAPS_OFFSET, माप(buf0) - MAPS_OFFSET,
		 "/tmp/#%llu (deleted)\n", (अचिन्हित दीर्घ दीर्घ)st.st_ino);

	/* Test /proc/$PID/maps */
	अणु
		स्थिर माप_प्रकार len = म_माप(buf0) + (g_vsyscall ? म_माप(str_vsyscall) : 0);
		अक्षर buf[256];
		sमाप_प्रकार rv;
		पूर्णांक fd;

		snम_लिखो(buf, माप(buf), "/proc/%u/maps", pid);
		fd = खोलो(buf, O_RDONLY);
		अगर (fd == -1) अणु
			वापस 1;
		पूर्ण
		rv = पढ़ो(fd, buf, माप(buf));
		निश्चित(rv == len);
		निश्चित(स_भेद(buf, buf0, म_माप(buf0)) == 0);
		अगर (g_vsyscall) अणु
			निश्चित(स_भेद(buf + म_माप(buf0), str_vsyscall, म_माप(str_vsyscall)) == 0);
		पूर्ण
	पूर्ण

	/* Test /proc/$PID/smaps */
	अणु
		अक्षर buf[4096];
		sमाप_प्रकार rv;
		पूर्णांक fd;

		snम_लिखो(buf, माप(buf), "/proc/%u/smaps", pid);
		fd = खोलो(buf, O_RDONLY);
		अगर (fd == -1) अणु
			वापस 1;
		पूर्ण
		rv = पढ़ो(fd, buf, माप(buf));
		निश्चित(0 <= rv && rv <= माप(buf));

		निश्चित(rv >= म_माप(buf0));
		निश्चित(स_भेद(buf, buf0, म_माप(buf0)) == 0);

#घोषणा RSS1 "Rss:                   4 kB\n"
#घोषणा RSS2 "Rss:                   0 kB\n"
#घोषणा PSS1 "Pss:                   4 kB\n"
#घोषणा PSS2 "Pss:                   0 kB\n"
		निश्चित(memmem(buf, rv, RSS1, म_माप(RSS1)) ||
		       memmem(buf, rv, RSS2, म_माप(RSS2)));
		निश्चित(memmem(buf, rv, PSS1, म_माप(PSS1)) ||
		       memmem(buf, rv, PSS2, म_माप(PSS2)));

		अटल स्थिर अक्षर *S[] = अणु
			"Size:                  4 kB\n",
			"KernelPageSize:        4 kB\n",
			"MMUPageSize:           4 kB\n",
			"Anonymous:             0 kB\n",
			"AnonHugePages:         0 kB\n",
			"Shared_Hugetlb:        0 kB\n",
			"Private_Hugetlb:       0 kB\n",
			"Locked:                0 kB\n",
		पूर्ण;
		पूर्णांक i;

		क्रम (i = 0; i < माप(S)/माप(S[0]); i++) अणु
			निश्चित(memmem(buf, rv, S[i], म_माप(S[i])));
		पूर्ण

		अगर (g_vsyscall) अणु
			निश्चित(memmem(buf, rv, str_vsyscall, म_माप(str_vsyscall)));
		पूर्ण
	पूर्ण

	/* Test /proc/$PID/smaps_rollup */
	अणु
		अक्षर bufr[256];
		स_रखो(bufr, ' ', माप(bufr));
		len = snम_लिखो(bufr, माप(bufr),
				"%08lx-%08lx ---p 00000000 00:00 0",
				VADDR, VADDR + PAGE_SIZE);
		bufr[len] = ' ';
		snम_लिखो(bufr + MAPS_OFFSET, माप(bufr) - MAPS_OFFSET,
			 "[rollup]\n");

		अक्षर buf[1024];
		sमाप_प्रकार rv;
		पूर्णांक fd;

		snम_लिखो(buf, माप(buf), "/proc/%u/smaps_rollup", pid);
		fd = खोलो(buf, O_RDONLY);
		अगर (fd == -1) अणु
			वापस 1;
		पूर्ण
		rv = पढ़ो(fd, buf, माप(buf));
		निश्चित(0 <= rv && rv <= माप(buf));

		निश्चित(rv >= म_माप(bufr));
		निश्चित(स_भेद(buf, bufr, म_माप(bufr)) == 0);

		निश्चित(memmem(buf, rv, RSS1, म_माप(RSS1)) ||
		       memmem(buf, rv, RSS2, म_माप(RSS2)));
		निश्चित(memmem(buf, rv, PSS1, म_माप(PSS1)) ||
		       memmem(buf, rv, PSS2, म_माप(PSS2)));

		अटल स्थिर अक्षर *S[] = अणु
			"Anonymous:             0 kB\n",
			"AnonHugePages:         0 kB\n",
			"Shared_Hugetlb:        0 kB\n",
			"Private_Hugetlb:       0 kB\n",
			"Locked:                0 kB\n",
		पूर्ण;
		पूर्णांक i;

		क्रम (i = 0; i < माप(S)/माप(S[0]); i++) अणु
			निश्चित(memmem(buf, rv, S[i], म_माप(S[i])));
		पूर्ण
	पूर्ण

	/* Test /proc/$PID/staपंचांग */
	अणु
		अक्षर buf[64];
		sमाप_प्रकार rv;
		पूर्णांक fd;

		snम_लिखो(buf, माप(buf), "/proc/%u/statm", pid);
		fd = खोलो(buf, O_RDONLY);
		अगर (fd == -1) अणु
			वापस 1;
		पूर्ण
		rv = पढ़ो(fd, buf, माप(buf));
		निश्चित(rv == 7 * 2);

		निश्चित(buf[0] == '1');	/* ->total_vm */
		निश्चित(buf[1] == ' ');
		निश्चित(buf[2] == '0' || buf[2] == '1');	/* rss */
		निश्चित(buf[3] == ' ');
		निश्चित(buf[4] == '0' || buf[2] == '1');	/* file rss */
		निश्चित(buf[5] == ' ');
		निश्चित(buf[6] == '1');	/* ELF executable segments */
		निश्चित(buf[7] == ' ');
		निश्चित(buf[8] == '0');
		निश्चित(buf[9] == ' ');
		निश्चित(buf[10] == '0');	/* ->data_vm + ->stack_vm */
		निश्चित(buf[11] == ' ');
		निश्चित(buf[12] == '0');
		निश्चित(buf[13] == '\n');
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
पूर्णांक मुख्य(व्योम)
अणु
	वापस 4;
पूर्ण
#पूर्ण_अगर
