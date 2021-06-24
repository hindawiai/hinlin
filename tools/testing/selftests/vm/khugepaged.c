<शैली गुरु>
#घोषणा _GNU_SOURCE
#समावेश <fcntl.h>
#समावेश <सीमा.स>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <stdbool.h>
#समावेश <माला.स>
#समावेश <unistd.h>

#समावेश <sys/mman.h>
#समावेश <sys/रुको.h>

#अगर_अघोषित MADV_PAGEOUT
#घोषणा MADV_PAGEOUT 21
#पूर्ण_अगर

#घोषणा BASE_ADDR ((व्योम *)(1UL << 30))
अटल अचिन्हित दीर्घ hpage_pmd_size;
अटल अचिन्हित दीर्घ page_size;
अटल पूर्णांक hpage_pmd_nr;

#घोषणा THP_SYSFS "/sys/kernel/mm/transparent_hugepage/"
#घोषणा PID_SMAPS "/proc/self/smaps"

क्रमागत thp_enabled अणु
	THP_ALWAYS,
	THP_MADVISE,
	THP_NEVER,
पूर्ण;

अटल स्थिर अक्षर *thp_enabled_strings[] = अणु
	"always",
	"madvise",
	"never",
	शून्य
पूर्ण;

क्रमागत thp_defrag अणु
	THP_DEFRAG_ALWAYS,
	THP_DEFRAG_DEFER,
	THP_DEFRAG_DEFER_MADVISE,
	THP_DEFRAG_MADVISE,
	THP_DEFRAG_NEVER,
पूर्ण;

अटल स्थिर अक्षर *thp_defrag_strings[] = अणु
	"always",
	"defer",
	"defer+madvise",
	"madvise",
	"never",
	शून्य
पूर्ण;

क्रमागत shmem_enabled अणु
	SHMEM_ALWAYS,
	SHMEM_WITHIN_SIZE,
	SHMEM_ADVISE,
	SHMEM_NEVER,
	SHMEM_DENY,
	SHMEM_FORCE,
पूर्ण;

अटल स्थिर अक्षर *shmem_enabled_strings[] = अणु
	"always",
	"within_size",
	"advise",
	"never",
	"deny",
	"force",
	शून्य
पूर्ण;

काष्ठा khugepaged_settings अणु
	bool defrag;
	अचिन्हित पूर्णांक alloc_sleep_millisecs;
	अचिन्हित पूर्णांक scan_sleep_millisecs;
	अचिन्हित पूर्णांक max_ptes_none;
	अचिन्हित पूर्णांक max_ptes_swap;
	अचिन्हित पूर्णांक max_ptes_shared;
	अचिन्हित दीर्घ pages_to_scan;
पूर्ण;

काष्ठा settings अणु
	क्रमागत thp_enabled thp_enabled;
	क्रमागत thp_defrag thp_defrag;
	क्रमागत shmem_enabled shmem_enabled;
	bool debug_cow;
	bool use_zero_page;
	काष्ठा khugepaged_settings khugepaged;
पूर्ण;

अटल काष्ठा settings शेष_settings = अणु
	.thp_enabled = THP_MADVISE,
	.thp_defrag = THP_DEFRAG_ALWAYS,
	.shmem_enabled = SHMEM_NEVER,
	.debug_cow = 0,
	.use_zero_page = 0,
	.khugepaged = अणु
		.defrag = 1,
		.alloc_sleep_millisecs = 10,
		.scan_sleep_millisecs = 10,
	पूर्ण,
पूर्ण;

अटल काष्ठा settings saved_settings;
अटल bool skip_settings_restore;

अटल पूर्णांक निकास_status;

अटल व्योम success(स्थिर अक्षर *msg)
अणु
	म_लिखो(" \e[32m%s\e[0m\n", msg);
पूर्ण

अटल व्योम fail(स्थिर अक्षर *msg)
अणु
	म_लिखो(" \e[31m%s\e[0m\n", msg);
	निकास_status++;
पूर्ण

अटल पूर्णांक पढ़ो_file(स्थिर अक्षर *path, अक्षर *buf, माप_प्रकार buflen)
अणु
	पूर्णांक fd;
	sमाप_प्रकार numपढ़ो;

	fd = खोलो(path, O_RDONLY);
	अगर (fd == -1)
		वापस 0;

	numपढ़ो = पढ़ो(fd, buf, buflen - 1);
	अगर (numपढ़ो < 1) अणु
		बंद(fd);
		वापस 0;
	पूर्ण

	buf[numपढ़ो] = '\0';
	बंद(fd);

	वापस (अचिन्हित पूर्णांक) numपढ़ो;
पूर्ण

अटल पूर्णांक ग_लिखो_file(स्थिर अक्षर *path, स्थिर अक्षर *buf, माप_प्रकार buflen)
अणु
	पूर्णांक fd;
	sमाप_प्रकार numwritten;

	fd = खोलो(path, O_WRONLY);
	अगर (fd == -1)
		वापस 0;

	numwritten = ग_लिखो(fd, buf, buflen - 1);
	बंद(fd);
	अगर (numwritten < 1)
		वापस 0;

	वापस (अचिन्हित पूर्णांक) numwritten;
पूर्ण

अटल पूर्णांक पढ़ो_string(स्थिर अक्षर *name, स्थिर अक्षर *strings[])
अणु
	अक्षर path[PATH_MAX];
	अक्षर buf[256];
	अक्षर *c;
	पूर्णांक ret;

	ret = snम_लिखो(path, PATH_MAX, THP_SYSFS "%s", name);
	अगर (ret >= PATH_MAX) अणु
		म_लिखो("%s: Pathname is too long\n", __func__);
		निकास(निकास_त्रुटि);
	पूर्ण

	अगर (!पढ़ो_file(path, buf, माप(buf))) अणु
		लिखो_त्रुटि(path);
		निकास(निकास_त्रुटि);
	पूर्ण

	c = म_अक्षर(buf, '[');
	अगर (!c) अणु
		म_लिखो("%s: Parse failure\n", __func__);
		निकास(निकास_त्रुटि);
	पूर्ण

	c++;
	स_हटाओ(buf, c, माप(buf) - (c - buf));

	c = म_अक्षर(buf, ']');
	अगर (!c) अणु
		म_लिखो("%s: Parse failure\n", __func__);
		निकास(निकास_त्रुटि);
	पूर्ण
	*c = '\0';

	ret = 0;
	जबतक (strings[ret]) अणु
		अगर (!म_भेद(strings[ret], buf))
			वापस ret;
		ret++;
	पूर्ण

	म_लिखो("Failed to parse %s\n", name);
	निकास(निकास_त्रुटि);
पूर्ण

अटल व्योम ग_लिखो_string(स्थिर अक्षर *name, स्थिर अक्षर *val)
अणु
	अक्षर path[PATH_MAX];
	पूर्णांक ret;

	ret = snम_लिखो(path, PATH_MAX, THP_SYSFS "%s", name);
	अगर (ret >= PATH_MAX) अणु
		म_लिखो("%s: Pathname is too long\n", __func__);
		निकास(निकास_त्रुटि);
	पूर्ण

	अगर (!ग_लिखो_file(path, val, म_माप(val) + 1)) अणु
		लिखो_त्रुटि(path);
		निकास(निकास_त्रुटि);
	पूर्ण
पूर्ण

अटल स्थिर अचिन्हित दीर्घ पढ़ो_num(स्थिर अक्षर *name)
अणु
	अक्षर path[PATH_MAX];
	अक्षर buf[21];
	पूर्णांक ret;

	ret = snम_लिखो(path, PATH_MAX, THP_SYSFS "%s", name);
	अगर (ret >= PATH_MAX) अणु
		म_लिखो("%s: Pathname is too long\n", __func__);
		निकास(निकास_त्रुटि);
	पूर्ण

	ret = पढ़ो_file(path, buf, माप(buf));
	अगर (ret < 0) अणु
		लिखो_त्रुटि("read_file(read_num)");
		निकास(निकास_त्रुटि);
	पूर्ण

	वापस म_से_अदीर्घ(buf, शून्य, 10);
पूर्ण

अटल व्योम ग_लिखो_num(स्थिर अक्षर *name, अचिन्हित दीर्घ num)
अणु
	अक्षर path[PATH_MAX];
	अक्षर buf[21];
	पूर्णांक ret;

	ret = snम_लिखो(path, PATH_MAX, THP_SYSFS "%s", name);
	अगर (ret >= PATH_MAX) अणु
		म_लिखो("%s: Pathname is too long\n", __func__);
		निकास(निकास_त्रुटि);
	पूर्ण

	प्र_लिखो(buf, "%ld", num);
	अगर (!ग_लिखो_file(path, buf, म_माप(buf) + 1)) अणु
		लिखो_त्रुटि(path);
		निकास(निकास_त्रुटि);
	पूर्ण
पूर्ण

अटल व्योम ग_लिखो_settings(काष्ठा settings *settings)
अणु
	काष्ठा khugepaged_settings *khugepaged = &settings->khugepaged;

	ग_लिखो_string("enabled", thp_enabled_strings[settings->thp_enabled]);
	ग_लिखो_string("defrag", thp_defrag_strings[settings->thp_defrag]);
	ग_लिखो_string("shmem_enabled",
			shmem_enabled_strings[settings->shmem_enabled]);
	ग_लिखो_num("debug_cow", settings->debug_cow);
	ग_लिखो_num("use_zero_page", settings->use_zero_page);

	ग_लिखो_num("khugepaged/defrag", khugepaged->defrag);
	ग_लिखो_num("khugepaged/alloc_sleep_millisecs",
			khugepaged->alloc_sleep_millisecs);
	ग_लिखो_num("khugepaged/scan_sleep_millisecs",
			khugepaged->scan_sleep_millisecs);
	ग_लिखो_num("khugepaged/max_ptes_none", khugepaged->max_ptes_none);
	ग_लिखो_num("khugepaged/max_ptes_swap", khugepaged->max_ptes_swap);
	ग_लिखो_num("khugepaged/max_ptes_shared", khugepaged->max_ptes_shared);
	ग_लिखो_num("khugepaged/pages_to_scan", khugepaged->pages_to_scan);
पूर्ण

अटल व्योम restore_settings(पूर्णांक sig)
अणु
	अगर (skip_settings_restore)
		जाओ out;

	म_लिखो("Restore THP and khugepaged settings...");
	ग_लिखो_settings(&saved_settings);
	success("OK");
	अगर (sig)
		निकास(निकास_त्रुटि);
out:
	निकास(निकास_status);
पूर्ण

अटल व्योम save_settings(व्योम)
अणु
	म_लिखो("Save THP and khugepaged settings...");
	saved_settings = (काष्ठा settings) अणु
		.thp_enabled = पढ़ो_string("enabled", thp_enabled_strings),
		.thp_defrag = पढ़ो_string("defrag", thp_defrag_strings),
		.shmem_enabled =
			पढ़ो_string("shmem_enabled", shmem_enabled_strings),
		.debug_cow = पढ़ो_num("debug_cow"),
		.use_zero_page = पढ़ो_num("use_zero_page"),
	पूर्ण;
	saved_settings.khugepaged = (काष्ठा khugepaged_settings) अणु
		.defrag = पढ़ो_num("khugepaged/defrag"),
		.alloc_sleep_millisecs =
			पढ़ो_num("khugepaged/alloc_sleep_millisecs"),
		.scan_sleep_millisecs =
			पढ़ो_num("khugepaged/scan_sleep_millisecs"),
		.max_ptes_none = पढ़ो_num("khugepaged/max_ptes_none"),
		.max_ptes_swap = पढ़ो_num("khugepaged/max_ptes_swap"),
		.max_ptes_shared = पढ़ो_num("khugepaged/max_ptes_shared"),
		.pages_to_scan = पढ़ो_num("khugepaged/pages_to_scan"),
	पूर्ण;
	success("OK");

	संकेत(संक_इति, restore_settings);
	संकेत(संक_विघ्न, restore_settings);
	संकेत(SIGHUP, restore_settings);
	संकेत(SIGQUIT, restore_settings);
पूर्ण

अटल व्योम adjust_settings(व्योम)
अणु

	म_लिखो("Adjust settings...");
	ग_लिखो_settings(&शेष_settings);
	success("OK");
पूर्ण

#घोषणा MAX_LINE_LENGTH 500

अटल bool check_क्रम_pattern(खाता *fp, अक्षर *pattern, अक्षर *buf)
अणु
	जबतक (ख_माला_लो(buf, MAX_LINE_LENGTH, fp) != शून्य) अणु
		अगर (!म_भेदन(buf, pattern, म_माप(pattern)))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool check_huge(व्योम *addr)
अणु
	bool thp = false;
	पूर्णांक ret;
	खाता *fp;
	अक्षर buffer[MAX_LINE_LENGTH];
	अक्षर addr_pattern[MAX_LINE_LENGTH];

	ret = snम_लिखो(addr_pattern, MAX_LINE_LENGTH, "%08lx-",
		       (अचिन्हित दीर्घ) addr);
	अगर (ret >= MAX_LINE_LENGTH) अणु
		म_लिखो("%s: Pattern is too long\n", __func__);
		निकास(निकास_त्रुटि);
	पूर्ण


	fp = ख_खोलो(PID_SMAPS, "r");
	अगर (!fp) अणु
		म_लिखो("%s: Failed to open file %s\n", __func__, PID_SMAPS);
		निकास(निकास_त्रुटि);
	पूर्ण
	अगर (!check_क्रम_pattern(fp, addr_pattern, buffer))
		जाओ err_out;

	ret = snम_लिखो(addr_pattern, MAX_LINE_LENGTH, "AnonHugePages:%10ld kB",
		       hpage_pmd_size >> 10);
	अगर (ret >= MAX_LINE_LENGTH) अणु
		म_लिखो("%s: Pattern is too long\n", __func__);
		निकास(निकास_त्रुटि);
	पूर्ण
	/*
	 * Fetch the AnonHugePages: in the same block and check whether it got
	 * the expected number of hugeepages next.
	 */
	अगर (!check_क्रम_pattern(fp, "AnonHugePages:", buffer))
		जाओ err_out;

	अगर (म_भेदन(buffer, addr_pattern, म_माप(addr_pattern)))
		जाओ err_out;

	thp = true;
err_out:
	ख_बंद(fp);
	वापस thp;
पूर्ण


अटल bool check_swap(व्योम *addr, अचिन्हित दीर्घ size)
अणु
	bool swap = false;
	पूर्णांक ret;
	खाता *fp;
	अक्षर buffer[MAX_LINE_LENGTH];
	अक्षर addr_pattern[MAX_LINE_LENGTH];

	ret = snम_लिखो(addr_pattern, MAX_LINE_LENGTH, "%08lx-",
		       (अचिन्हित दीर्घ) addr);
	अगर (ret >= MAX_LINE_LENGTH) अणु
		म_लिखो("%s: Pattern is too long\n", __func__);
		निकास(निकास_त्रुटि);
	पूर्ण


	fp = ख_खोलो(PID_SMAPS, "r");
	अगर (!fp) अणु
		म_लिखो("%s: Failed to open file %s\n", __func__, PID_SMAPS);
		निकास(निकास_त्रुटि);
	पूर्ण
	अगर (!check_क्रम_pattern(fp, addr_pattern, buffer))
		जाओ err_out;

	ret = snम_लिखो(addr_pattern, MAX_LINE_LENGTH, "Swap:%19ld kB",
		       size >> 10);
	अगर (ret >= MAX_LINE_LENGTH) अणु
		म_लिखो("%s: Pattern is too long\n", __func__);
		निकास(निकास_त्रुटि);
	पूर्ण
	/*
	 * Fetch the Swap: in the same block and check whether it got
	 * the expected number of hugeepages next.
	 */
	अगर (!check_क्रम_pattern(fp, "Swap:", buffer))
		जाओ err_out;

	अगर (म_भेदन(buffer, addr_pattern, म_माप(addr_pattern)))
		जाओ err_out;

	swap = true;
err_out:
	ख_बंद(fp);
	वापस swap;
पूर्ण

अटल व्योम *alloc_mapping(व्योम)
अणु
	व्योम *p;

	p = mmap(BASE_ADDR, hpage_pmd_size, PROT_READ | PROT_WRITE,
			MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	अगर (p != BASE_ADDR) अणु
		म_लिखो("Failed to allocate VMA at %p\n", BASE_ADDR);
		निकास(निकास_त्रुटि);
	पूर्ण

	वापस p;
पूर्ण

अटल व्योम fill_memory(पूर्णांक *p, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	पूर्णांक i;

	क्रम (i = start / page_size; i < end / page_size; i++)
		p[i * page_size / माप(*p)] = i + 0xdead0000;
पूर्ण

अटल व्योम validate_memory(पूर्णांक *p, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	पूर्णांक i;

	क्रम (i = start / page_size; i < end / page_size; i++) अणु
		अगर (p[i * page_size / माप(*p)] != i + 0xdead0000) अणु
			म_लिखो("Page %d is corrupted: %#x\n",
					i, p[i * page_size / माप(*p)]);
			निकास(निकास_त्रुटि);
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा TICK 500000
अटल bool रुको_क्रम_scan(स्थिर अक्षर *msg, अक्षर *p)
अणु
	पूर्णांक full_scans;
	पूर्णांक समयout = 6; /* 3 seconds */

	/* Sanity check */
	अगर (check_huge(p)) अणु
		म_लिखो("Unexpected huge page\n");
		निकास(निकास_त्रुटि);
	पूर्ण

	madvise(p, hpage_pmd_size, MADV_HUGEPAGE);

	/* Wait until the second full_scan completed */
	full_scans = पढ़ो_num("khugepaged/full_scans") + 2;

	म_लिखो("%s...", msg);
	जबतक (समयout--) अणु
		अगर (check_huge(p))
			अवरोध;
		अगर (पढ़ो_num("khugepaged/full_scans") >= full_scans)
			अवरोध;
		म_लिखो(".");
		usleep(TICK);
	पूर्ण

	madvise(p, hpage_pmd_size, MADV_NOHUGEPAGE);

	वापस समयout == -1;
पूर्ण

अटल व्योम alloc_at_fault(व्योम)
अणु
	काष्ठा settings settings = शेष_settings;
	अक्षर *p;

	settings.thp_enabled = THP_ALWAYS;
	ग_लिखो_settings(&settings);

	p = alloc_mapping();
	*p = 1;
	म_लिखो("Allocate huge page on fault...");
	अगर (check_huge(p))
		success("OK");
	अन्यथा
		fail("Fail");

	ग_लिखो_settings(&शेष_settings);

	madvise(p, page_size, MADV_DONTNEED);
	म_लिखो("Split huge PMD on MADV_DONTNEED...");
	अगर (!check_huge(p))
		success("OK");
	अन्यथा
		fail("Fail");
	munmap(p, hpage_pmd_size);
पूर्ण

अटल व्योम collapse_full(व्योम)
अणु
	व्योम *p;

	p = alloc_mapping();
	fill_memory(p, 0, hpage_pmd_size);
	अगर (रुको_क्रम_scan("Collapse fully populated PTE table", p))
		fail("Timeout");
	अन्यथा अगर (check_huge(p))
		success("OK");
	अन्यथा
		fail("Fail");
	validate_memory(p, 0, hpage_pmd_size);
	munmap(p, hpage_pmd_size);
पूर्ण

अटल व्योम collapse_empty(व्योम)
अणु
	व्योम *p;

	p = alloc_mapping();
	अगर (रुको_क्रम_scan("Do not collapse empty PTE table", p))
		fail("Timeout");
	अन्यथा अगर (check_huge(p))
		fail("Fail");
	अन्यथा
		success("OK");
	munmap(p, hpage_pmd_size);
पूर्ण

अटल व्योम collapse_single_pte_entry(व्योम)
अणु
	व्योम *p;

	p = alloc_mapping();
	fill_memory(p, 0, page_size);
	अगर (रुको_क्रम_scan("Collapse PTE table with single PTE entry present", p))
		fail("Timeout");
	अन्यथा अगर (check_huge(p))
		success("OK");
	अन्यथा
		fail("Fail");
	validate_memory(p, 0, page_size);
	munmap(p, hpage_pmd_size);
पूर्ण

अटल व्योम collapse_max_ptes_none(व्योम)
अणु
	पूर्णांक max_ptes_none = hpage_pmd_nr / 2;
	काष्ठा settings settings = शेष_settings;
	व्योम *p;

	settings.khugepaged.max_ptes_none = max_ptes_none;
	ग_लिखो_settings(&settings);

	p = alloc_mapping();

	fill_memory(p, 0, (hpage_pmd_nr - max_ptes_none - 1) * page_size);
	अगर (रुको_क्रम_scan("Do not collapse with max_ptes_none exceeded", p))
		fail("Timeout");
	अन्यथा अगर (check_huge(p))
		fail("Fail");
	अन्यथा
		success("OK");
	validate_memory(p, 0, (hpage_pmd_nr - max_ptes_none - 1) * page_size);

	fill_memory(p, 0, (hpage_pmd_nr - max_ptes_none) * page_size);
	अगर (रुको_क्रम_scan("Collapse with max_ptes_none PTEs empty", p))
		fail("Timeout");
	अन्यथा अगर (check_huge(p))
		success("OK");
	अन्यथा
		fail("Fail");
	validate_memory(p, 0, (hpage_pmd_nr - max_ptes_none) * page_size);

	munmap(p, hpage_pmd_size);
	ग_लिखो_settings(&शेष_settings);
पूर्ण

अटल व्योम collapse_swapin_single_pte(व्योम)
अणु
	व्योम *p;
	p = alloc_mapping();
	fill_memory(p, 0, hpage_pmd_size);

	म_लिखो("Swapout one page...");
	अगर (madvise(p, page_size, MADV_PAGEOUT)) अणु
		लिखो_त्रुटि("madvise(MADV_PAGEOUT)");
		निकास(निकास_त्रुटि);
	पूर्ण
	अगर (check_swap(p, page_size)) अणु
		success("OK");
	पूर्ण अन्यथा अणु
		fail("Fail");
		जाओ out;
	पूर्ण

	अगर (रुको_क्रम_scan("Collapse with swapping in single PTE entry", p))
		fail("Timeout");
	अन्यथा अगर (check_huge(p))
		success("OK");
	अन्यथा
		fail("Fail");
	validate_memory(p, 0, hpage_pmd_size);
out:
	munmap(p, hpage_pmd_size);
पूर्ण

अटल व्योम collapse_max_ptes_swap(व्योम)
अणु
	पूर्णांक max_ptes_swap = पढ़ो_num("khugepaged/max_ptes_swap");
	व्योम *p;

	p = alloc_mapping();

	fill_memory(p, 0, hpage_pmd_size);
	म_लिखो("Swapout %d of %d pages...", max_ptes_swap + 1, hpage_pmd_nr);
	अगर (madvise(p, (max_ptes_swap + 1) * page_size, MADV_PAGEOUT)) अणु
		लिखो_त्रुटि("madvise(MADV_PAGEOUT)");
		निकास(निकास_त्रुटि);
	पूर्ण
	अगर (check_swap(p, (max_ptes_swap + 1) * page_size)) अणु
		success("OK");
	पूर्ण अन्यथा अणु
		fail("Fail");
		जाओ out;
	पूर्ण

	अगर (रुको_क्रम_scan("Do not collapse with max_ptes_swap exceeded", p))
		fail("Timeout");
	अन्यथा अगर (check_huge(p))
		fail("Fail");
	अन्यथा
		success("OK");
	validate_memory(p, 0, hpage_pmd_size);

	fill_memory(p, 0, hpage_pmd_size);
	म_लिखो("Swapout %d of %d pages...", max_ptes_swap, hpage_pmd_nr);
	अगर (madvise(p, max_ptes_swap * page_size, MADV_PAGEOUT)) अणु
		लिखो_त्रुटि("madvise(MADV_PAGEOUT)");
		निकास(निकास_त्रुटि);
	पूर्ण
	अगर (check_swap(p, max_ptes_swap * page_size)) अणु
		success("OK");
	पूर्ण अन्यथा अणु
		fail("Fail");
		जाओ out;
	पूर्ण

	अगर (रुको_क्रम_scan("Collapse with max_ptes_swap pages swapped out", p))
		fail("Timeout");
	अन्यथा अगर (check_huge(p))
		success("OK");
	अन्यथा
		fail("Fail");
	validate_memory(p, 0, hpage_pmd_size);
out:
	munmap(p, hpage_pmd_size);
पूर्ण

अटल व्योम collapse_single_pte_entry_compound(व्योम)
अणु
	व्योम *p;

	p = alloc_mapping();

	म_लिखो("Allocate huge page...");
	madvise(p, hpage_pmd_size, MADV_HUGEPAGE);
	fill_memory(p, 0, hpage_pmd_size);
	अगर (check_huge(p))
		success("OK");
	अन्यथा
		fail("Fail");
	madvise(p, hpage_pmd_size, MADV_NOHUGEPAGE);

	म_लिखो("Split huge page leaving single PTE mapping compound page...");
	madvise(p + page_size, hpage_pmd_size - page_size, MADV_DONTNEED);
	अगर (!check_huge(p))
		success("OK");
	अन्यथा
		fail("Fail");

	अगर (रुको_क्रम_scan("Collapse PTE table with single PTE mapping compound page", p))
		fail("Timeout");
	अन्यथा अगर (check_huge(p))
		success("OK");
	अन्यथा
		fail("Fail");
	validate_memory(p, 0, page_size);
	munmap(p, hpage_pmd_size);
पूर्ण

अटल व्योम collapse_full_of_compound(व्योम)
अणु
	व्योम *p;

	p = alloc_mapping();

	म_लिखो("Allocate huge page...");
	madvise(p, hpage_pmd_size, MADV_HUGEPAGE);
	fill_memory(p, 0, hpage_pmd_size);
	अगर (check_huge(p))
		success("OK");
	अन्यथा
		fail("Fail");

	म_लिखो("Split huge page leaving single PTE page table full of compound pages...");
	madvise(p, page_size, MADV_NOHUGEPAGE);
	madvise(p, hpage_pmd_size, MADV_NOHUGEPAGE);
	अगर (!check_huge(p))
		success("OK");
	अन्यथा
		fail("Fail");

	अगर (रुको_क्रम_scan("Collapse PTE table full of compound pages", p))
		fail("Timeout");
	अन्यथा अगर (check_huge(p))
		success("OK");
	अन्यथा
		fail("Fail");
	validate_memory(p, 0, hpage_pmd_size);
	munmap(p, hpage_pmd_size);
पूर्ण

अटल व्योम collapse_compound_extreme(व्योम)
अणु
	व्योम *p;
	पूर्णांक i;

	p = alloc_mapping();
	क्रम (i = 0; i < hpage_pmd_nr; i++) अणु
		म_लिखो("\rConstruct PTE page table full of different PTE-mapped compound pages %3d/%d...",
				i + 1, hpage_pmd_nr);

		madvise(BASE_ADDR, hpage_pmd_size, MADV_HUGEPAGE);
		fill_memory(BASE_ADDR, 0, hpage_pmd_size);
		अगर (!check_huge(BASE_ADDR)) अणु
			म_लिखो("Failed to allocate huge page\n");
			निकास(निकास_त्रुटि);
		पूर्ण
		madvise(BASE_ADDR, hpage_pmd_size, MADV_NOHUGEPAGE);

		p = mremap(BASE_ADDR - i * page_size,
				i * page_size + hpage_pmd_size,
				(i + 1) * page_size,
				MREMAP_MAYMOVE | MREMAP_FIXED,
				BASE_ADDR + 2 * hpage_pmd_size);
		अगर (p == MAP_FAILED) अणु
			लिखो_त्रुटि("mremap+unmap");
			निकास(निकास_त्रुटि);
		पूर्ण

		p = mremap(BASE_ADDR + 2 * hpage_pmd_size,
				(i + 1) * page_size,
				(i + 1) * page_size + hpage_pmd_size,
				MREMAP_MAYMOVE | MREMAP_FIXED,
				BASE_ADDR - (i + 1) * page_size);
		अगर (p == MAP_FAILED) अणु
			लिखो_त्रुटि("mremap+alloc");
			निकास(निकास_त्रुटि);
		पूर्ण
	पूर्ण

	munmap(BASE_ADDR, hpage_pmd_size);
	fill_memory(p, 0, hpage_pmd_size);
	अगर (!check_huge(p))
		success("OK");
	अन्यथा
		fail("Fail");

	अगर (रुको_क्रम_scan("Collapse PTE table full of different compound pages", p))
		fail("Timeout");
	अन्यथा अगर (check_huge(p))
		success("OK");
	अन्यथा
		fail("Fail");

	validate_memory(p, 0, hpage_pmd_size);
	munmap(p, hpage_pmd_size);
पूर्ण

अटल व्योम collapse_विभाजन(व्योम)
अणु
	पूर्णांक wstatus;
	व्योम *p;

	p = alloc_mapping();

	म_लिखो("Allocate small page...");
	fill_memory(p, 0, page_size);
	अगर (!check_huge(p))
		success("OK");
	अन्यथा
		fail("Fail");

	म_लिखो("Share small page over fork()...");
	अगर (!विभाजन()) अणु
		/* Do not touch settings on child निकास */
		skip_settings_restore = true;
		निकास_status = 0;

		अगर (!check_huge(p))
			success("OK");
		अन्यथा
			fail("Fail");

		fill_memory(p, page_size, 2 * page_size);

		अगर (रुको_क्रम_scan("Collapse PTE table with single page shared with parent process", p))
			fail("Timeout");
		अन्यथा अगर (check_huge(p))
			success("OK");
		अन्यथा
			fail("Fail");

		validate_memory(p, 0, page_size);
		munmap(p, hpage_pmd_size);
		निकास(निकास_status);
	पूर्ण

	रुको(&wstatus);
	निकास_status += WEXITSTATUS(wstatus);

	म_लिखो("Check if parent still has small page...");
	अगर (!check_huge(p))
		success("OK");
	अन्यथा
		fail("Fail");
	validate_memory(p, 0, page_size);
	munmap(p, hpage_pmd_size);
पूर्ण

अटल व्योम collapse_विभाजन_compound(व्योम)
अणु
	पूर्णांक wstatus;
	व्योम *p;

	p = alloc_mapping();

	म_लिखो("Allocate huge page...");
	madvise(p, hpage_pmd_size, MADV_HUGEPAGE);
	fill_memory(p, 0, hpage_pmd_size);
	अगर (check_huge(p))
		success("OK");
	अन्यथा
		fail("Fail");

	म_लिखो("Share huge page over fork()...");
	अगर (!विभाजन()) अणु
		/* Do not touch settings on child निकास */
		skip_settings_restore = true;
		निकास_status = 0;

		अगर (check_huge(p))
			success("OK");
		अन्यथा
			fail("Fail");

		म_लिखो("Split huge page PMD in child process...");
		madvise(p, page_size, MADV_NOHUGEPAGE);
		madvise(p, hpage_pmd_size, MADV_NOHUGEPAGE);
		अगर (!check_huge(p))
			success("OK");
		अन्यथा
			fail("Fail");
		fill_memory(p, 0, page_size);

		ग_लिखो_num("khugepaged/max_ptes_shared", hpage_pmd_nr - 1);
		अगर (रुको_क्रम_scan("Collapse PTE table full of compound pages in child", p))
			fail("Timeout");
		अन्यथा अगर (check_huge(p))
			success("OK");
		अन्यथा
			fail("Fail");
		ग_लिखो_num("khugepaged/max_ptes_shared",
				शेष_settings.khugepaged.max_ptes_shared);

		validate_memory(p, 0, hpage_pmd_size);
		munmap(p, hpage_pmd_size);
		निकास(निकास_status);
	पूर्ण

	रुको(&wstatus);
	निकास_status += WEXITSTATUS(wstatus);

	म_लिखो("Check if parent still has huge page...");
	अगर (check_huge(p))
		success("OK");
	अन्यथा
		fail("Fail");
	validate_memory(p, 0, hpage_pmd_size);
	munmap(p, hpage_pmd_size);
पूर्ण

अटल व्योम collapse_max_ptes_shared()
अणु
	पूर्णांक max_ptes_shared = पढ़ो_num("khugepaged/max_ptes_shared");
	पूर्णांक wstatus;
	व्योम *p;

	p = alloc_mapping();

	म_लिखो("Allocate huge page...");
	madvise(p, hpage_pmd_size, MADV_HUGEPAGE);
	fill_memory(p, 0, hpage_pmd_size);
	अगर (check_huge(p))
		success("OK");
	अन्यथा
		fail("Fail");

	म_लिखो("Share huge page over fork()...");
	अगर (!विभाजन()) अणु
		/* Do not touch settings on child निकास */
		skip_settings_restore = true;
		निकास_status = 0;

		अगर (check_huge(p))
			success("OK");
		अन्यथा
			fail("Fail");

		म_लिखो("Trigger CoW on page %d of %d...",
				hpage_pmd_nr - max_ptes_shared - 1, hpage_pmd_nr);
		fill_memory(p, 0, (hpage_pmd_nr - max_ptes_shared - 1) * page_size);
		अगर (!check_huge(p))
			success("OK");
		अन्यथा
			fail("Fail");

		अगर (रुको_क्रम_scan("Do not collapse with max_ptes_shared exceeded", p))
			fail("Timeout");
		अन्यथा अगर (!check_huge(p))
			success("OK");
		अन्यथा
			fail("Fail");

		म_लिखो("Trigger CoW on page %d of %d...",
				hpage_pmd_nr - max_ptes_shared, hpage_pmd_nr);
		fill_memory(p, 0, (hpage_pmd_nr - max_ptes_shared) * page_size);
		अगर (!check_huge(p))
			success("OK");
		अन्यथा
			fail("Fail");


		अगर (रुको_क्रम_scan("Collapse with max_ptes_shared PTEs shared", p))
			fail("Timeout");
		अन्यथा अगर (check_huge(p))
			success("OK");
		अन्यथा
			fail("Fail");

		validate_memory(p, 0, hpage_pmd_size);
		munmap(p, hpage_pmd_size);
		निकास(निकास_status);
	पूर्ण

	रुको(&wstatus);
	निकास_status += WEXITSTATUS(wstatus);

	म_लिखो("Check if parent still has huge page...");
	अगर (check_huge(p))
		success("OK");
	अन्यथा
		fail("Fail");
	validate_memory(p, 0, hpage_pmd_size);
	munmap(p, hpage_pmd_size);
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	रखो_बफ(मानक_निकास, शून्य);

	page_size = getpagesize();
	hpage_pmd_size = पढ़ो_num("hpage_pmd_size");
	hpage_pmd_nr = hpage_pmd_size / page_size;

	शेष_settings.khugepaged.max_ptes_none = hpage_pmd_nr - 1;
	शेष_settings.khugepaged.max_ptes_swap = hpage_pmd_nr / 8;
	शेष_settings.khugepaged.max_ptes_shared = hpage_pmd_nr / 2;
	शेष_settings.khugepaged.pages_to_scan = hpage_pmd_nr * 8;

	save_settings();
	adjust_settings();

	alloc_at_fault();
	collapse_full();
	collapse_empty();
	collapse_single_pte_entry();
	collapse_max_ptes_none();
	collapse_swapin_single_pte();
	collapse_max_ptes_swap();
	collapse_single_pte_entry_compound();
	collapse_full_of_compound();
	collapse_compound_extreme();
	collapse_विभाजन();
	collapse_विभाजन_compound();
	collapse_max_ptes_shared();

	restore_settings(0);
पूर्ण
