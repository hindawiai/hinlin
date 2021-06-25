<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Ptrace test क्रम Memory Protection Key रेजिस्टरs
 *
 * Copyright (C) 2015 Anshuman Khandual, IBM Corporation.
 * Copyright (C) 2018 IBM Corporation.
 */
#समावेश <सीमा.स>
#समावेश <linux/kernel.h>
#समावेश <sys/mman.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/समय.स>
#समावेश <sys/resource.h>
#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश "ptrace.h"
#समावेश "child.h"

#अगर_अघोषित __NR_pkey_alloc
#घोषणा __NR_pkey_alloc		384
#पूर्ण_अगर

#अगर_अघोषित __NR_pkey_मुक्त
#घोषणा __NR_pkey_मुक्त		385
#पूर्ण_अगर

#अगर_अघोषित NT_PPC_PKEY
#घोषणा NT_PPC_PKEY		0x110
#पूर्ण_अगर

#अगर_अघोषित PKEY_DISABLE_EXECUTE
#घोषणा PKEY_DISABLE_EXECUTE	0x4
#पूर्ण_अगर

#घोषणा AMR_BITS_PER_PKEY 2
#घोषणा PKEY_REG_BITS (माप(u64) * 8)
#घोषणा pkeyshअगरt(pkey) (PKEY_REG_BITS - ((pkey + 1) * AMR_BITS_PER_PKEY))

#घोषणा CORE_खाता_LIMIT	(5 * 1024 * 1024)	/* 5 MB should be enough */

अटल स्थिर अक्षर core_pattern_file[] = "/proc/sys/kernel/core_pattern";

अटल स्थिर अक्षर user_ग_लिखो[] = "[User Write (Running)]";
अटल स्थिर अक्षर core_पढ़ो_running[] = "[Core Read (Running)]";

/* Inक्रमmation shared between the parent and the child. */
काष्ठा shared_info अणु
	काष्ठा child_sync child_sync;

	/* AMR value the parent expects to पढ़ो in the core file. */
	अचिन्हित दीर्घ amr;

	/* IAMR value the parent expects to पढ़ो in the core file. */
	अचिन्हित दीर्घ iamr;

	/* UAMOR value the parent expects to पढ़ो in the core file. */
	अचिन्हित दीर्घ uamor;

	/* When the child crashed. */
	समय_प्रकार core_समय;
पूर्ण;

अटल पूर्णांक sys_pkey_alloc(अचिन्हित दीर्घ flags, अचिन्हित दीर्घ init_access_rights)
अणु
	वापस syscall(__NR_pkey_alloc, flags, init_access_rights);
पूर्ण

अटल पूर्णांक sys_pkey_मुक्त(पूर्णांक pkey)
अणु
	वापस syscall(__NR_pkey_मुक्त, pkey);
पूर्ण

अटल पूर्णांक increase_core_file_limit(व्योम)
अणु
	काष्ठा rlimit rlim;
	पूर्णांक ret;

	ret = getrlimit(RLIMIT_CORE, &rlim);
	FAIL_IF(ret);

	अगर (rlim.rlim_cur != RLIM_अनन्त && rlim.rlim_cur < CORE_खाता_LIMIT) अणु
		rlim.rlim_cur = CORE_खाता_LIMIT;

		अगर (rlim.rlim_max != RLIM_अनन्त &&
		    rlim.rlim_max < CORE_खाता_LIMIT)
			rlim.rlim_max = CORE_खाता_LIMIT;

		ret = setrlimit(RLIMIT_CORE, &rlim);
		FAIL_IF(ret);
	पूर्ण

	ret = getrlimit(RLIMIT_FSIZE, &rlim);
	FAIL_IF(ret);

	अगर (rlim.rlim_cur != RLIM_अनन्त && rlim.rlim_cur < CORE_खाता_LIMIT) अणु
		rlim.rlim_cur = CORE_खाता_LIMIT;

		अगर (rlim.rlim_max != RLIM_अनन्त &&
		    rlim.rlim_max < CORE_खाता_LIMIT)
			rlim.rlim_max = CORE_खाता_LIMIT;

		ret = setrlimit(RLIMIT_FSIZE, &rlim);
		FAIL_IF(ret);
	पूर्ण

	वापस TEST_PASS;
पूर्ण

अटल पूर्णांक child(काष्ठा shared_info *info)
अणु
	bool disable_execute = true;
	पूर्णांक pkey1, pkey2, pkey3;
	पूर्णांक *ptr, ret;

	/* Wait until parent fills out the initial रेजिस्टर values. */
	ret = रुको_parent(&info->child_sync);
	अगर (ret)
		वापस ret;

	ret = increase_core_file_limit();
	FAIL_IF(ret);

	/* Get some pkeys so that we can change their bits in the AMR. */
	pkey1 = sys_pkey_alloc(0, PKEY_DISABLE_EXECUTE);
	अगर (pkey1 < 0) अणु
		pkey1 = sys_pkey_alloc(0, 0);
		FAIL_IF(pkey1 < 0);

		disable_execute = false;
	पूर्ण

	pkey2 = sys_pkey_alloc(0, 0);
	FAIL_IF(pkey2 < 0);

	pkey3 = sys_pkey_alloc(0, 0);
	FAIL_IF(pkey3 < 0);

	info->amr |= 3ul << pkeyshअगरt(pkey1) | 2ul << pkeyshअगरt(pkey2);

	अगर (disable_execute)
		info->iamr |= 1ul << pkeyshअगरt(pkey1);
	अन्यथा
		info->iamr &= ~(1ul << pkeyshअगरt(pkey1));

	info->iamr &= ~(1ul << pkeyshअगरt(pkey2) | 1ul << pkeyshअगरt(pkey3));

	info->uamor |= 3ul << pkeyshअगरt(pkey1) | 3ul << pkeyshअगरt(pkey2);

	म_लिखो("%-30s AMR: %016lx pkey1: %d pkey2: %d pkey3: %d\n",
	       user_ग_लिखो, info->amr, pkey1, pkey2, pkey3);

	set_amr(info->amr);

	/*
	 * We won't use pkey3. This tests whether the kernel restores the UAMOR
	 * permissions after a key is मुक्तd.
	 */
	sys_pkey_मुक्त(pkey3);

	info->core_समय = समय(शून्य);

	/* Crash. */
	ptr = 0;
	*ptr = 1;

	/* Shouldn't get here. */
	FAIL_IF(true);

	वापस TEST_FAIL;
पूर्ण

/* Return file size अगर filename exists and pass sanity check, or zero अगर not. */
अटल off_t try_core_file(स्थिर अक्षर *filename, काष्ठा shared_info *info,
			   pid_t pid)
अणु
	काष्ठा stat buf;
	पूर्णांक ret;

	ret = stat(filename, &buf);
	अगर (ret == -1)
		वापस TEST_FAIL;

	/* Make sure we're not using a stale core file. */
	वापस buf.st_mसमय >= info->core_समय ? buf.st_size : TEST_FAIL;
पूर्ण

अटल Elf64_Nhdr *next_note(Elf64_Nhdr *nhdr)
अणु
	वापस (व्योम *) nhdr + माप(*nhdr) +
		__ALIGN_KERNEL(nhdr->n_namesz, 4) +
		__ALIGN_KERNEL(nhdr->n_descsz, 4);
पूर्ण

अटल पूर्णांक check_core_file(काष्ठा shared_info *info, Elf64_Ehdr *ehdr,
			   off_t core_size)
अणु
	अचिन्हित दीर्घ *regs;
	Elf64_Phdr *phdr;
	Elf64_Nhdr *nhdr;
	माप_प्रकार phdr_size;
	व्योम *p = ehdr, *note;
	पूर्णांक ret;

	ret = स_भेद(ehdr->e_ident, ELFMAG, SELFMAG);
	FAIL_IF(ret);

	FAIL_IF(ehdr->e_type != ET_CORE);
	FAIL_IF(ehdr->e_machine != EM_PPC64);
	FAIL_IF(ehdr->e_phoff == 0 || ehdr->e_phnum == 0);

	/*
	 * e_phnum is at most 65535 so calculating the size of the
	 * program header cannot overflow.
	 */
	phdr_size = माप(*phdr) * ehdr->e_phnum;

	/* Sanity check the program header table location. */
	FAIL_IF(ehdr->e_phoff + phdr_size < ehdr->e_phoff);
	FAIL_IF(ehdr->e_phoff + phdr_size > core_size);

	/* Find the PT_NOTE segment. */
	क्रम (phdr = p + ehdr->e_phoff;
	     (व्योम *) phdr < p + ehdr->e_phoff + phdr_size;
	     phdr += ehdr->e_phentsize)
		अगर (phdr->p_type == PT_NOTE)
			अवरोध;

	FAIL_IF((व्योम *) phdr >= p + ehdr->e_phoff + phdr_size);

	/* Find the NT_PPC_PKEY note. */
	क्रम (nhdr = p + phdr->p_offset;
	     (व्योम *) nhdr < p + phdr->p_offset + phdr->p_filesz;
	     nhdr = next_note(nhdr))
		अगर (nhdr->n_type == NT_PPC_PKEY)
			अवरोध;

	FAIL_IF((व्योम *) nhdr >= p + phdr->p_offset + phdr->p_filesz);
	FAIL_IF(nhdr->n_descsz == 0);

	p = nhdr;
	note = p + माप(*nhdr) + __ALIGN_KERNEL(nhdr->n_namesz, 4);

	regs = (अचिन्हित दीर्घ *) note;

	म_लिखो("%-30s AMR: %016lx IAMR: %016lx UAMOR: %016lx\n",
	       core_पढ़ो_running, regs[0], regs[1], regs[2]);

	FAIL_IF(regs[0] != info->amr);
	FAIL_IF(regs[1] != info->iamr);
	FAIL_IF(regs[2] != info->uamor);

	वापस TEST_PASS;
पूर्ण

अटल पूर्णांक parent(काष्ठा shared_info *info, pid_t pid)
अणु
	अक्षर *filenames, *filename[3];
	पूर्णांक fd, i, ret, status;
	अचिन्हित दीर्घ regs[3];
	off_t core_size;
	व्योम *core;

	/*
	 * Get the initial values क्रम AMR, IAMR and UAMOR and communicate them
	 * to the child.
	 */
	ret = ptrace_पढ़ो_regs(pid, NT_PPC_PKEY, regs, 3);
	PARENT_SKIP_IF_UNSUPPORTED(ret, &info->child_sync);
	PARENT_FAIL_IF(ret, &info->child_sync);

	info->amr = regs[0];
	info->iamr = regs[1];
	info->uamor = regs[2];

	/* Wake up child so that it can set itself up. */
	ret = prod_child(&info->child_sync);
	PARENT_FAIL_IF(ret, &info->child_sync);

	ret = रुको(&status);
	अगर (ret != pid) अणु
		म_लिखो("Child's exit status not captured\n");
		वापस TEST_FAIL;
	पूर्ण अन्यथा अगर (!WIFSIGNALED(status) || !WCOREDUMP(status)) अणु
		म_लिखो("Child didn't dump core\n");
		वापस TEST_FAIL;
	पूर्ण

	/* Conकाष्ठा array of core file names to try. */

	filename[0] = filenames = दो_स्मृति(PATH_MAX);
	अगर (!filenames) अणु
		लिखो_त्रुटि("Error allocating memory");
		वापस TEST_FAIL;
	पूर्ण

	ret = snम_लिखो(filename[0], PATH_MAX, "core-pkey.%d", pid);
	अगर (ret < 0 || ret >= PATH_MAX) अणु
		ret = TEST_FAIL;
		जाओ out;
	पूर्ण

	filename[1] = filename[0] + ret + 1;
	ret = snम_लिखो(filename[1], PATH_MAX - ret - 1, "core.%d", pid);
	अगर (ret < 0 || ret >= PATH_MAX - ret - 1) अणु
		ret = TEST_FAIL;
		जाओ out;
	पूर्ण
	filename[2] = "core";

	क्रम (i = 0; i < 3; i++) अणु
		core_size = try_core_file(filename[i], info, pid);
		अगर (core_size != TEST_FAIL)
			अवरोध;
	पूर्ण

	अगर (i == 3) अणु
		म_लिखो("Couldn't find core file\n");
		ret = TEST_FAIL;
		जाओ out;
	पूर्ण

	fd = खोलो(filename[i], O_RDONLY);
	अगर (fd == -1) अणु
		लिखो_त्रुटि("Error opening core file");
		ret = TEST_FAIL;
		जाओ out;
	पूर्ण

	core = mmap(शून्य, core_size, PROT_READ, MAP_PRIVATE, fd, 0);
	अगर (core == (व्योम *) -1) अणु
		लिखो_त्रुटि("Error mmaping core file");
		ret = TEST_FAIL;
		जाओ out;
	पूर्ण

	ret = check_core_file(info, core, core_size);

	munmap(core, core_size);
	बंद(fd);
	unlink(filename[i]);

 out:
	मुक्त(filenames);

	वापस ret;
पूर्ण

अटल पूर्णांक ग_लिखो_core_pattern(स्थिर अक्षर *core_pattern)
अणु
	माप_प्रकार len = म_माप(core_pattern), ret;
	खाता *f;

	f = ख_खोलो(core_pattern_file, "w");
	SKIP_IF_MSG(!f, "Try with root privileges");

	ret = ख_डालो(core_pattern, 1, len, f);
	ख_बंद(f);
	अगर (ret != len) अणु
		लिखो_त्रुटि("Error writing to core_pattern file");
		वापस TEST_FAIL;
	पूर्ण

	वापस TEST_PASS;
पूर्ण

अटल पूर्णांक setup_core_pattern(अक्षर **core_pattern_, bool *changed_)
अणु
	खाता *f;
	अक्षर *core_pattern;
	पूर्णांक ret;

	core_pattern = दो_स्मृति(PATH_MAX);
	अगर (!core_pattern) अणु
		लिखो_त्रुटि("Error allocating memory");
		वापस TEST_FAIL;
	पूर्ण

	f = ख_खोलो(core_pattern_file, "r");
	अगर (!f) अणु
		लिखो_त्रुटि("Error opening core_pattern file");
		ret = TEST_FAIL;
		जाओ out;
	पूर्ण

	ret = ख_पढ़ो(core_pattern, 1, PATH_MAX, f);
	ख_बंद(f);
	अगर (!ret) अणु
		लिखो_त्रुटि("Error reading core_pattern file");
		ret = TEST_FAIL;
		जाओ out;
	पूर्ण

	/* Check whether we can predict the name of the core file. */
	अगर (!म_भेद(core_pattern, "core") || !म_भेद(core_pattern, "core.%p"))
		*changed_ = false;
	अन्यथा अणु
		ret = ग_लिखो_core_pattern("core-pkey.%p");
		अगर (ret)
			जाओ out;

		*changed_ = true;
	पूर्ण

	*core_pattern_ = core_pattern;
	ret = TEST_PASS;

 out:
	अगर (ret)
		मुक्त(core_pattern);

	वापस ret;
पूर्ण

अटल पूर्णांक core_pkey(व्योम)
अणु
	अक्षर *core_pattern;
	bool changed_core_pattern;
	काष्ठा shared_info *info;
	पूर्णांक shm_id;
	पूर्णांक ret;
	pid_t pid;

	ret = setup_core_pattern(&core_pattern, &changed_core_pattern);
	अगर (ret)
		वापस ret;

	shm_id = shmget(IPC_PRIVATE, माप(*info), 0777 | IPC_CREAT);
	info = shmat(shm_id, शून्य, 0);

	ret = init_child_sync(&info->child_sync);
	अगर (ret)
		वापस ret;

	pid = विभाजन();
	अगर (pid < 0) अणु
		लिखो_त्रुटि("fork() failed");
		ret = TEST_FAIL;
	पूर्ण अन्यथा अगर (pid == 0)
		ret = child(info);
	अन्यथा
		ret = parent(info, pid);

	shmdt(info);

	अगर (pid) अणु
		destroy_child_sync(&info->child_sync);
		shmctl(shm_id, IPC_RMID, शून्य);

		अगर (changed_core_pattern)
			ग_लिखो_core_pattern(core_pattern);
	पूर्ण

	मुक्त(core_pattern);

	वापस ret;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	वापस test_harness(core_pkey, "core_pkey");
पूर्ण
