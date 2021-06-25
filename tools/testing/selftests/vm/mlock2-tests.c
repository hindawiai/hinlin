<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE
#समावेश <sys/mman.h>
#समावेश <मानक_निवेशt.h>
#समावेश <unistd.h>
#समावेश <माला.स>
#समावेश <sys/समय.स>
#समावेश <sys/resource.h>
#समावेश <stdbool.h>
#समावेश "mlock2.h"

#समावेश "../kselftest.h"

काष्ठा vm_boundaries अणु
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ end;
पूर्ण;

अटल पूर्णांक get_vm_area(अचिन्हित दीर्घ addr, काष्ठा vm_boundaries *area)
अणु
	खाता *file;
	पूर्णांक ret = 1;
	अक्षर line[1024] = अणु0पूर्ण;
	अक्षर *end_addr;
	अक्षर *stop;
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ end;

	अगर (!area)
		वापस ret;

	file = ख_खोलो("/proc/self/maps", "r");
	अगर (!file) अणु
		लिखो_त्रुटि("fopen");
		वापस ret;
	पूर्ण

	स_रखो(area, 0, माप(काष्ठा vm_boundaries));

	जबतक(ख_माला_लो(line, 1024, file)) अणु
		end_addr = म_अक्षर(line, '-');
		अगर (!end_addr) अणु
			म_लिखो("cannot parse /proc/self/maps\n");
			जाओ out;
		पूर्ण
		*end_addr = '\0';
		end_addr++;
		stop = म_अक्षर(end_addr, ' ');
		अगर (!stop) अणु
			म_लिखो("cannot parse /proc/self/maps\n");
			जाओ out;
		पूर्ण
		stop = '\0';

		माला_पूछो(line, "%lx", &start);
		माला_पूछो(end_addr, "%lx", &end);

		अगर (start <= addr && end > addr) अणु
			area->start = start;
			area->end = end;
			ret = 0;
			जाओ out;
		पूर्ण
	पूर्ण
out:
	ख_बंद(file);
	वापस ret;
पूर्ण

#घोषणा VMFLAGS "VmFlags:"

अटल bool is_vmflag_set(अचिन्हित दीर्घ addr, स्थिर अक्षर *vmflag)
अणु
	अक्षर *line = शून्य;
	अक्षर *flags;
	माप_प्रकार size = 0;
	bool ret = false;
	खाता *smaps;

	smaps = seek_to_smaps_entry(addr);
	अगर (!smaps) अणु
		म_लिखो("Unable to parse /proc/self/smaps\n");
		जाओ out;
	पूर्ण

	जबतक (getline(&line, &size, smaps) > 0) अणु
		अगर (!म_माला(line, VMFLAGS)) अणु
			मुक्त(line);
			line = शून्य;
			size = 0;
			जारी;
		पूर्ण

		flags = line + म_माप(VMFLAGS);
		ret = (म_माला(flags, vmflag) != शून्य);
		जाओ out;
	पूर्ण

out:
	मुक्त(line);
	ख_बंद(smaps);
	वापस ret;
पूर्ण

#घोषणा SIZE "Size:"
#घोषणा RSS  "Rss:"
#घोषणा LOCKED "lo"

अटल अचिन्हित दीर्घ get_value_क्रम_name(अचिन्हित दीर्घ addr, स्थिर अक्षर *name)
अणु
	अक्षर *line = शून्य;
	माप_प्रकार size = 0;
	अक्षर *value_ptr;
	खाता *smaps = शून्य;
	अचिन्हित दीर्घ value = -1UL;

	smaps = seek_to_smaps_entry(addr);
	अगर (!smaps) अणु
		म_लिखो("Unable to parse /proc/self/smaps\n");
		जाओ out;
	पूर्ण

	जबतक (getline(&line, &size, smaps) > 0) अणु
		अगर (!म_माला(line, name)) अणु
			मुक्त(line);
			line = शून्य;
			size = 0;
			जारी;
		पूर्ण

		value_ptr = line + म_माप(name);
		अगर (माला_पूछो(value_ptr, "%lu kB", &value) < 1) अणु
			म_लिखो("Unable to parse smaps entry for Size\n");
			जाओ out;
		पूर्ण
		अवरोध;
	पूर्ण

out:
	अगर (smaps)
		ख_बंद(smaps);
	मुक्त(line);
	वापस value;
पूर्ण

अटल bool is_vma_lock_on_fault(अचिन्हित दीर्घ addr)
अणु
	bool locked;
	अचिन्हित दीर्घ vma_size, vma_rss;

	locked = is_vmflag_set(addr, LOCKED);
	अगर (!locked)
		वापस false;

	vma_size = get_value_क्रम_name(addr, SIZE);
	vma_rss = get_value_क्रम_name(addr, RSS);

	/* only one page is faulted in */
	वापस (vma_rss < vma_size);
पूर्ण

#घोषणा PRESENT_BIT     0x8000000000000000ULL
#घोषणा PFN_MASK        0x007FFFFFFFFFFFFFULL
#घोषणा UNEVICTABLE_BIT (1UL << 18)

अटल पूर्णांक lock_check(अचिन्हित दीर्घ addr)
अणु
	bool locked;
	अचिन्हित दीर्घ vma_size, vma_rss;

	locked = is_vmflag_set(addr, LOCKED);
	अगर (!locked)
		वापस false;

	vma_size = get_value_क्रम_name(addr, SIZE);
	vma_rss = get_value_क्रम_name(addr, RSS);

	वापस (vma_rss == vma_size);
पूर्ण

अटल पूर्णांक unlock_lock_check(अक्षर *map)
अणु
	अगर (is_vmflag_set((अचिन्हित दीर्घ)map, LOCKED)) अणु
		म_लिखो("VMA flag %s is present on page 1 after unlock\n", LOCKED);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक test_mlock_lock()
अणु
	अक्षर *map;
	पूर्णांक ret = 1;
	अचिन्हित दीर्घ page_size = getpagesize();

	map = mmap(शून्य, 2 * page_size, PROT_READ | PROT_WRITE,
		   MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	अगर (map == MAP_FAILED) अणु
		लिखो_त्रुटि("test_mlock_locked mmap");
		जाओ out;
	पूर्ण

	अगर (mlock2_(map, 2 * page_size, 0)) अणु
		अगर (त्रुटि_सं == ENOSYS) अणु
			म_लिखो("Cannot call new mlock family, skipping test\n");
			_निकास(KSFT_SKIP);
		पूर्ण
		लिखो_त्रुटि("mlock2(0)");
		जाओ unmap;
	पूर्ण

	अगर (!lock_check((अचिन्हित दीर्घ)map))
		जाओ unmap;

	/* Now unlock and recheck attributes */
	अगर (munlock(map, 2 * page_size)) अणु
		लिखो_त्रुटि("munlock()");
		जाओ unmap;
	पूर्ण

	ret = unlock_lock_check(map);

unmap:
	munmap(map, 2 * page_size);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक onfault_check(अक्षर *map)
अणु
	*map = 'a';
	अगर (!is_vma_lock_on_fault((अचिन्हित दीर्घ)map)) अणु
		म_लिखो("VMA is not marked for lock on fault\n");
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक unlock_onfault_check(अक्षर *map)
अणु
	अचिन्हित दीर्घ page_size = getpagesize();

	अगर (is_vma_lock_on_fault((अचिन्हित दीर्घ)map) ||
	    is_vma_lock_on_fault((अचिन्हित दीर्घ)map + page_size)) अणु
		म_लिखो("VMA is still lock on fault after unlock\n");
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक test_mlock_onfault()
अणु
	अक्षर *map;
	पूर्णांक ret = 1;
	अचिन्हित दीर्घ page_size = getpagesize();

	map = mmap(शून्य, 2 * page_size, PROT_READ | PROT_WRITE,
		   MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	अगर (map == MAP_FAILED) अणु
		लिखो_त्रुटि("test_mlock_locked mmap");
		जाओ out;
	पूर्ण

	अगर (mlock2_(map, 2 * page_size, MLOCK_ONFAULT)) अणु
		अगर (त्रुटि_सं == ENOSYS) अणु
			म_लिखो("Cannot call new mlock family, skipping test\n");
			_निकास(KSFT_SKIP);
		पूर्ण
		लिखो_त्रुटि("mlock2(MLOCK_ONFAULT)");
		जाओ unmap;
	पूर्ण

	अगर (onfault_check(map))
		जाओ unmap;

	/* Now unlock and recheck attributes */
	अगर (munlock(map, 2 * page_size)) अणु
		अगर (त्रुटि_सं == ENOSYS) अणु
			म_लिखो("Cannot call new mlock family, skipping test\n");
			_निकास(KSFT_SKIP);
		पूर्ण
		लिखो_त्रुटि("munlock()");
		जाओ unmap;
	पूर्ण

	ret = unlock_onfault_check(map);
unmap:
	munmap(map, 2 * page_size);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक test_lock_onfault_of_present()
अणु
	अक्षर *map;
	पूर्णांक ret = 1;
	अचिन्हित दीर्घ page_size = getpagesize();

	map = mmap(शून्य, 2 * page_size, PROT_READ | PROT_WRITE,
		   MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	अगर (map == MAP_FAILED) अणु
		लिखो_त्रुटि("test_mlock_locked mmap");
		जाओ out;
	पूर्ण

	*map = 'a';

	अगर (mlock2_(map, 2 * page_size, MLOCK_ONFAULT)) अणु
		अगर (त्रुटि_सं == ENOSYS) अणु
			म_लिखो("Cannot call new mlock family, skipping test\n");
			_निकास(KSFT_SKIP);
		पूर्ण
		लिखो_त्रुटि("mlock2(MLOCK_ONFAULT)");
		जाओ unmap;
	पूर्ण

	अगर (!is_vma_lock_on_fault((अचिन्हित दीर्घ)map) ||
	    !is_vma_lock_on_fault((अचिन्हित दीर्घ)map + page_size)) अणु
		म_लिखो("VMA with present pages is not marked lock on fault\n");
		जाओ unmap;
	पूर्ण
	ret = 0;
unmap:
	munmap(map, 2 * page_size);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक test_munlockall()
अणु
	अक्षर *map;
	पूर्णांक ret = 1;
	अचिन्हित दीर्घ page_size = getpagesize();

	map = mmap(शून्य, 2 * page_size, PROT_READ | PROT_WRITE,
		   MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

	अगर (map == MAP_FAILED) अणु
		लिखो_त्रुटि("test_munlockall mmap");
		जाओ out;
	पूर्ण

	अगर (mlockall(MCL_CURRENT)) अणु
		लिखो_त्रुटि("mlockall(MCL_CURRENT)");
		जाओ out;
	पूर्ण

	अगर (!lock_check((अचिन्हित दीर्घ)map))
		जाओ unmap;

	अगर (munlockall()) अणु
		लिखो_त्रुटि("munlockall()");
		जाओ unmap;
	पूर्ण

	अगर (unlock_lock_check(map))
		जाओ unmap;

	munmap(map, 2 * page_size);

	map = mmap(शून्य, 2 * page_size, PROT_READ | PROT_WRITE,
		   MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

	अगर (map == MAP_FAILED) अणु
		लिखो_त्रुटि("test_munlockall second mmap");
		जाओ out;
	पूर्ण

	अगर (mlockall(MCL_CURRENT | MCL_ONFAULT)) अणु
		लिखो_त्रुटि("mlockall(MCL_CURRENT | MCL_ONFAULT)");
		जाओ unmap;
	पूर्ण

	अगर (onfault_check(map))
		जाओ unmap;

	अगर (munlockall()) अणु
		लिखो_त्रुटि("munlockall()");
		जाओ unmap;
	पूर्ण

	अगर (unlock_onfault_check(map))
		जाओ unmap;

	अगर (mlockall(MCL_CURRENT | MCL_FUTURE)) अणु
		लिखो_त्रुटि("mlockall(MCL_CURRENT | MCL_FUTURE)");
		जाओ out;
	पूर्ण

	अगर (!lock_check((अचिन्हित दीर्घ)map))
		जाओ unmap;

	अगर (munlockall()) अणु
		लिखो_त्रुटि("munlockall()");
		जाओ unmap;
	पूर्ण

	ret = unlock_lock_check(map);

unmap:
	munmap(map, 2 * page_size);
out:
	munlockall();
	वापस ret;
पूर्ण

अटल पूर्णांक test_vma_management(bool call_mlock)
अणु
	पूर्णांक ret = 1;
	व्योम *map;
	अचिन्हित दीर्घ page_size = getpagesize();
	काष्ठा vm_boundaries page1;
	काष्ठा vm_boundaries page2;
	काष्ठा vm_boundaries page3;

	map = mmap(शून्य, 3 * page_size, PROT_READ | PROT_WRITE,
		   MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	अगर (map == MAP_FAILED) अणु
		लिखो_त्रुटि("mmap()");
		वापस ret;
	पूर्ण

	अगर (call_mlock && mlock2_(map, 3 * page_size, MLOCK_ONFAULT)) अणु
		अगर (त्रुटि_सं == ENOSYS) अणु
			म_लिखो("Cannot call new mlock family, skipping test\n");
			_निकास(KSFT_SKIP);
		पूर्ण
		लिखो_त्रुटि("mlock(ONFAULT)\n");
		जाओ out;
	पूर्ण

	अगर (get_vm_area((अचिन्हित दीर्घ)map, &page1) ||
	    get_vm_area((अचिन्हित दीर्घ)map + page_size, &page2) ||
	    get_vm_area((अचिन्हित दीर्घ)map + page_size * 2, &page3)) अणु
		म_लिखो("couldn't find mapping in /proc/self/maps\n");
		जाओ out;
	पूर्ण

	/*
	 * Beक्रमe we unlock a portion, we need to that all three pages are in
	 * the same VMA.  If they are not we पात this test (Note that this is
	 * not a failure)
	 */
	अगर (page1.start != page2.start || page2.start != page3.start) अणु
		म_लिखो("VMAs are not merged to start, aborting test\n");
		ret = 0;
		जाओ out;
	पूर्ण

	अगर (munlock(map + page_size, page_size)) अणु
		लिखो_त्रुटि("munlock()");
		जाओ out;
	पूर्ण

	अगर (get_vm_area((अचिन्हित दीर्घ)map, &page1) ||
	    get_vm_area((अचिन्हित दीर्घ)map + page_size, &page2) ||
	    get_vm_area((अचिन्हित दीर्घ)map + page_size * 2, &page3)) अणु
		म_लिखो("couldn't find mapping in /proc/self/maps\n");
		जाओ out;
	पूर्ण

	/* All three VMAs should be dअगरferent */
	अगर (page1.start == page2.start || page2.start == page3.start) अणु
		म_लिखो("failed to split VMA for munlock\n");
		जाओ out;
	पूर्ण

	/* Now unlock the first and third page and check the VMAs again */
	अगर (munlock(map, page_size * 3)) अणु
		लिखो_त्रुटि("munlock()");
		जाओ out;
	पूर्ण

	अगर (get_vm_area((अचिन्हित दीर्घ)map, &page1) ||
	    get_vm_area((अचिन्हित दीर्घ)map + page_size, &page2) ||
	    get_vm_area((अचिन्हित दीर्घ)map + page_size * 2, &page3)) अणु
		म_लिखो("couldn't find mapping in /proc/self/maps\n");
		जाओ out;
	पूर्ण

	/* Now all three VMAs should be the same */
	अगर (page1.start != page2.start || page2.start != page3.start) अणु
		म_लिखो("failed to merge VMAs after munlock\n");
		जाओ out;
	पूर्ण

	ret = 0;
out:
	munmap(map, 3 * page_size);
	वापस ret;
पूर्ण

अटल पूर्णांक test_mlockall(पूर्णांक (test_function)(bool call_mlock))
अणु
	पूर्णांक ret = 1;

	अगर (mlockall(MCL_CURRENT | MCL_ONFAULT | MCL_FUTURE)) अणु
		लिखो_त्रुटि("mlockall");
		वापस ret;
	पूर्ण

	ret = test_function(false);
	munlockall();
	वापस ret;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक ret = 0;
	ret += test_mlock_lock();
	ret += test_mlock_onfault();
	ret += test_munlockall();
	ret += test_lock_onfault_of_present();
	ret += test_vma_management(true);
	ret += test_mlockall(test_vma_management);
	वापस ret;
पूर्ण
