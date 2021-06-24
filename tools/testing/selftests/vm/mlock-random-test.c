<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * It tests the mlock/mlock2() when they are invoked
 * on अक्रमomly memory region.
 */
#समावेश <unistd.h>
#समावेश <sys/resource.h>
#समावेश <sys/capability.h>
#समावेश <sys/mman.h>
#समावेश <fcntl.h>
#समावेश <माला.स>
#समावेश <sys/ipc.h>
#समावेश <sys/shm.h>
#समावेश <समय.स>
#समावेश "mlock2.h"

#घोषणा CHUNK_UNIT (128 * 1024)
#घोषणा MLOCK_RLIMIT_SIZE (CHUNK_UNIT * 2)
#घोषणा MLOCK_WITHIN_LIMIT_SIZE CHUNK_UNIT
#घोषणा MLOCK_OUTOF_LIMIT_SIZE (CHUNK_UNIT * 3)

#घोषणा TEST_LOOP 100
#घोषणा PAGE_ALIGN(size, ps) (((size) + ((ps) - 1)) & ~((ps) - 1))

पूर्णांक set_cap_limits(rlim_t max)
अणु
	काष्ठा rlimit new;
	cap_t cap = cap_init();

	new.rlim_cur = max;
	new.rlim_max = max;
	अगर (setrlimit(RLIMIT_MEMLOCK, &new)) अणु
		लिखो_त्रुटि("setrlimit() returns error\n");
		वापस -1;
	पूर्ण

	/* drop capabilities including CAP_IPC_LOCK */
	अगर (cap_set_proc(cap)) अणु
		लिखो_त्रुटि("cap_set_proc() returns error\n");
		वापस -2;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक get_proc_locked_vm_size(व्योम)
अणु
	खाता *f;
	पूर्णांक ret = -1;
	अक्षर line[1024] = अणु0पूर्ण;
	अचिन्हित दीर्घ lock_size = 0;

	f = ख_खोलो("/proc/self/status", "r");
	अगर (!f) अणु
		लिखो_त्रुटि("fopen");
		वापस -1;
	पूर्ण

	जबतक (ख_माला_लो(line, 1024, f)) अणु
		अगर (म_माला(line, "VmLck")) अणु
			ret = माला_पूछो(line, "VmLck:\t%8lu kB", &lock_size);
			अगर (ret <= 0) अणु
				म_लिखो("sscanf() on VmLck error: %s: %d\n",
						line, ret);
				ख_बंद(f);
				वापस -1;
			पूर्ण
			ख_बंद(f);
			वापस (पूर्णांक)(lock_size << 10);
		पूर्ण
	पूर्ण

	लिखो_त्रुटि("cann't parse VmLck in /proc/self/status\n");
	ख_बंद(f);
	वापस -1;
पूर्ण

/*
 * Get the MMUPageSize of the memory region including input
 * address from proc file.
 *
 * वापस value: on error हाल, 0 will be वापसed.
 * Otherwise the page size(in bytes) is वापसed.
 */
पूर्णांक get_proc_page_size(अचिन्हित दीर्घ addr)
अणु
	खाता *smaps;
	अक्षर *line;
	अचिन्हित दीर्घ mmupage_size = 0;
	माप_प्रकार size;

	smaps = seek_to_smaps_entry(addr);
	अगर (!smaps) अणु
		म_लिखो("Unable to parse /proc/self/smaps\n");
		वापस 0;
	पूर्ण

	जबतक (getline(&line, &size, smaps) > 0) अणु
		अगर (!म_माला(line, "MMUPageSize")) अणु
			मुक्त(line);
			line = शून्य;
			size = 0;
			जारी;
		पूर्ण

		/* found the MMUPageSize of this section */
		अगर (माला_पूछो(line, "MMUPageSize:    %8lu kB",
					&mmupage_size) < 1) अणु
			म_लिखो("Unable to parse smaps entry for Size:%s\n",
					line);
			अवरोध;
		पूर्ण

	पूर्ण
	मुक्त(line);
	अगर (smaps)
		ख_बंद(smaps);
	वापस mmupage_size << 10;
पूर्ण

/*
 * Test mlock/mlock2() on provided memory chunk.
 * It expects the mlock/mlock2() to be successful (within rlimit)
 *
 * With allocated memory chunk [p, p + alloc_size), this
 * test will choose start/len अक्रमomly to perक्रमm mlock/mlock2
 * [start, start +  len] memory range. The range is within range
 * of the allocated chunk.
 *
 * The memory region size alloc_size is within the rlimit.
 * So we always expect a success of mlock/mlock2.
 *
 * VmLck is assumed to be 0 beक्रमe this test.
 *
 *    वापस value: 0 - success
 *    अन्यथा: failure
 */
पूर्णांक test_mlock_within_limit(अक्षर *p, पूर्णांक alloc_size)
अणु
	पूर्णांक i;
	पूर्णांक ret = 0;
	पूर्णांक locked_vm_size = 0;
	काष्ठा rlimit cur;
	पूर्णांक page_size = 0;

	getrlimit(RLIMIT_MEMLOCK, &cur);
	अगर (cur.rlim_cur < alloc_size) अणु
		म_लिखो("alloc_size[%d] < %u rlimit,lead to mlock failure\n",
				alloc_size, (अचिन्हित पूर्णांक)cur.rlim_cur);
		वापस -1;
	पूर्ण

	बेक्रम(समय(शून्य));
	क्रम (i = 0; i < TEST_LOOP; i++) अणु
		/*
		 * - choose mlock/mlock2 अक्रमomly
		 * - choose lock_size अक्रमomly but lock_size < alloc_size
		 * - choose start_offset अक्रमomly but p+start_offset+lock_size
		 *   < p+alloc_size
		 */
		पूर्णांक is_mlock = !!(अक्रम() % 2);
		पूर्णांक lock_size = अक्रम() % alloc_size;
		पूर्णांक start_offset = अक्रम() % (alloc_size - lock_size);

		अगर (is_mlock)
			ret = mlock(p + start_offset, lock_size);
		अन्यथा
			ret = mlock2_(p + start_offset, lock_size,
				       MLOCK_ONFAULT);

		अगर (ret) अणु
			म_लिखो("%s() failure at |%p(%d)| mlock:|%p(%d)|\n",
					is_mlock ? "mlock" : "mlock2",
					p, alloc_size,
					p + start_offset, lock_size);
			वापस ret;
		पूर्ण
	पूर्ण

	/*
	 * Check VmLck left by the tests.
	 */
	locked_vm_size = get_proc_locked_vm_size();
	page_size = get_proc_page_size((अचिन्हित दीर्घ)p);
	अगर (page_size == 0) अणु
		म_लिखो("cannot get proc MMUPageSize\n");
		वापस -1;
	पूर्ण

	अगर (locked_vm_size > PAGE_ALIGN(alloc_size, page_size) + page_size) अणु
		म_लिखो("test_mlock_within_limit() left VmLck:%d on %d chunk\n",
				locked_vm_size, alloc_size);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण


/*
 * We expect the mlock/mlock2() to be fail (outof limitation)
 *
 * With allocated memory chunk [p, p + alloc_size), this
 * test will अक्रमomly choose start/len and perक्रमm mlock/mlock2
 * on [start, start+len] range.
 *
 * The memory region size alloc_size is above the rlimit.
 * And the len to be locked is higher than rlimit.
 * So we always expect a failure of mlock/mlock2.
 * No locked page number should be increased as a side effect.
 *
 *    वापस value: 0 - success
 *    अन्यथा: failure
 */
पूर्णांक test_mlock_outof_limit(अक्षर *p, पूर्णांक alloc_size)
अणु
	पूर्णांक i;
	पूर्णांक ret = 0;
	पूर्णांक locked_vm_size = 0, old_locked_vm_size = 0;
	काष्ठा rlimit cur;

	getrlimit(RLIMIT_MEMLOCK, &cur);
	अगर (cur.rlim_cur >= alloc_size) अणु
		म_लिखो("alloc_size[%d] >%u rlimit, violates test condition\n",
				alloc_size, (अचिन्हित पूर्णांक)cur.rlim_cur);
		वापस -1;
	पूर्ण

	old_locked_vm_size = get_proc_locked_vm_size();
	बेक्रम(समय(शून्य));
	क्रम (i = 0; i < TEST_LOOP; i++) अणु
		पूर्णांक is_mlock = !!(अक्रम() % 2);
		पूर्णांक lock_size = (अक्रम() % (alloc_size - cur.rlim_cur))
			+ cur.rlim_cur;
		पूर्णांक start_offset = अक्रम() % (alloc_size - lock_size);

		अगर (is_mlock)
			ret = mlock(p + start_offset, lock_size);
		अन्यथा
			ret = mlock2_(p + start_offset, lock_size,
					MLOCK_ONFAULT);
		अगर (ret == 0) अणु
			म_लिखो("%s() succeeds? on %p(%d) mlock%p(%d)\n",
					is_mlock ? "mlock" : "mlock2",
					p, alloc_size,
					p + start_offset, lock_size);
			वापस -1;
		पूर्ण
	पूर्ण

	locked_vm_size = get_proc_locked_vm_size();
	अगर (locked_vm_size != old_locked_vm_size) अणु
		म_लिखो("tests leads to new mlocked page: old[%d], new[%d]\n",
				old_locked_vm_size,
				locked_vm_size);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अक्षर *p = शून्य;
	पूर्णांक ret = 0;

	अगर (set_cap_limits(MLOCK_RLIMIT_SIZE))
		वापस -1;

	p = दो_स्मृति(MLOCK_WITHIN_LIMIT_SIZE);
	अगर (p == शून्य) अणु
		लिखो_त्रुटि("malloc() failure\n");
		वापस -1;
	पूर्ण
	ret = test_mlock_within_limit(p, MLOCK_WITHIN_LIMIT_SIZE);
	अगर (ret)
		वापस ret;
	munlock(p, MLOCK_WITHIN_LIMIT_SIZE);
	मुक्त(p);


	p = दो_स्मृति(MLOCK_OUTOF_LIMIT_SIZE);
	अगर (p == शून्य) अणु
		लिखो_त्रुटि("malloc() failure\n");
		वापस -1;
	पूर्ण
	ret = test_mlock_outof_limit(p, MLOCK_OUTOF_LIMIT_SIZE);
	अगर (ret)
		वापस ret;
	munlock(p, MLOCK_OUTOF_LIMIT_SIZE);
	मुक्त(p);

	वापस 0;
पूर्ण
