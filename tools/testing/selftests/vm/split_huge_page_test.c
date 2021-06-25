<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * A test of splitting PMD THPs and PTE-mapped THPs from a specअगरied भव
 * address range in a process via <debugfs>/split_huge_pages पूर्णांकerface.
 */

#घोषणा _GNU_SOURCE
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <मानकतर्क.स>
#समावेश <unistd.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <माला.स>
#समावेश <fcntl.h>
#समावेश <sys/mman.h>
#समावेश <sys/mount.h>
#समावेश <दो_स्मृति.h>
#समावेश <stdbool.h>

uपूर्णांक64_t pagesize;
अचिन्हित पूर्णांक pageshअगरt;
uपूर्णांक64_t pmd_pagesize;

#घोषणा PMD_SIZE_PATH "/sys/kernel/mm/transparent_hugepage/hpage_pmd_size"
#घोषणा SPLIT_DEBUGFS "/sys/kernel/debug/split_huge_pages"
#घोषणा SMAP_PATH "/proc/self/smaps"
#घोषणा INPUT_MAX 80

#घोषणा PID_FMT "%d,0x%lx,0x%lx"
#घोषणा PATH_FMT "%s,0x%lx,0x%lx"

#घोषणा PFN_MASK     ((1UL<<55)-1)
#घोषणा KPF_THP      (1UL<<22)

पूर्णांक is_backed_by_thp(अक्षर *vaddr, पूर्णांक pagemap_file, पूर्णांक kpageflags_file)
अणु
	uपूर्णांक64_t paddr;
	uपूर्णांक64_t page_flags;

	अगर (pagemap_file) अणु
		pपढ़ो(pagemap_file, &paddr, माप(paddr),
			((दीर्घ)vaddr >> pageshअगरt) * माप(paddr));

		अगर (kpageflags_file) अणु
			pपढ़ो(kpageflags_file, &page_flags, माप(page_flags),
				(paddr & PFN_MASK) * माप(page_flags));

			वापस !!(page_flags & KPF_THP);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण


अटल uपूर्णांक64_t पढ़ो_pmd_pagesize(व्योम)
अणु
	पूर्णांक fd;
	अक्षर buf[20];
	sमाप_प्रकार num_पढ़ो;

	fd = खोलो(PMD_SIZE_PATH, O_RDONLY);
	अगर (fd == -1) अणु
		लिखो_त्रुटि("Open hpage_pmd_size failed");
		निकास(निकास_त्रुटि);
	पूर्ण
	num_पढ़ो = पढ़ो(fd, buf, 19);
	अगर (num_पढ़ो < 1) अणु
		बंद(fd);
		लिखो_त्रुटि("Read hpage_pmd_size failed");
		निकास(निकास_त्रुटि);
	पूर्ण
	buf[num_पढ़ो] = '\0';
	बंद(fd);

	वापस म_से_अदीर्घ(buf, शून्य, 10);
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

अटल व्योम ग_लिखो_debugfs(स्थिर अक्षर *fmt, ...)
अणु
	अक्षर input[INPUT_MAX];
	पूर्णांक ret;
	बहु_सूची argp;

	बहु_शुरू(argp, fmt);
	ret = vsnम_लिखो(input, INPUT_MAX, fmt, argp);
	बहु_पूर्ण(argp);

	अगर (ret >= INPUT_MAX) अणु
		म_लिखो("%s: Debugfs input is too long\n", __func__);
		निकास(निकास_त्रुटि);
	पूर्ण

	अगर (!ग_लिखो_file(SPLIT_DEBUGFS, input, ret + 1)) अणु
		लिखो_त्रुटि(SPLIT_DEBUGFS);
		निकास(निकास_त्रुटि);
	पूर्ण
पूर्ण

#घोषणा MAX_LINE_LENGTH 500

अटल bool check_क्रम_pattern(खाता *fp, स्थिर अक्षर *pattern, अक्षर *buf)
अणु
	जबतक (ख_माला_लो(buf, MAX_LINE_LENGTH, fp) != शून्य) अणु
		अगर (!म_भेदन(buf, pattern, म_माप(pattern)))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल uपूर्णांक64_t check_huge(व्योम *addr)
अणु
	uपूर्णांक64_t thp = 0;
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


	fp = ख_खोलो(SMAP_PATH, "r");
	अगर (!fp) अणु
		म_लिखो("%s: Failed to open file %s\n", __func__, SMAP_PATH);
		निकास(निकास_त्रुटि);
	पूर्ण
	अगर (!check_क्रम_pattern(fp, addr_pattern, buffer))
		जाओ err_out;

	/*
	 * Fetch the AnonHugePages: in the same block and check the number of
	 * hugepages.
	 */
	अगर (!check_क्रम_pattern(fp, "AnonHugePages:", buffer))
		जाओ err_out;

	अगर (माला_पूछो(buffer, "AnonHugePages:%10ld kB", &thp) != 1) अणु
		म_लिखो("Reading smap error\n");
		निकास(निकास_त्रुटि);
	पूर्ण

err_out:
	ख_बंद(fp);
	वापस thp;
पूर्ण

व्योम split_pmd_thp(व्योम)
अणु
	अक्षर *one_page;
	माप_प्रकार len = 4 * pmd_pagesize;
	uपूर्णांक64_t thp_size;
	माप_प्रकार i;

	one_page = memalign(pmd_pagesize, len);

	अगर (!one_page) अणु
		म_लिखो("Fail to allocate memory\n");
		निकास(निकास_त्रुटि);
	पूर्ण

	madvise(one_page, len, MADV_HUGEPAGE);

	क्रम (i = 0; i < len; i++)
		one_page[i] = (अक्षर)i;

	thp_size = check_huge(one_page);
	अगर (!thp_size) अणु
		म_लिखो("No THP is allocated\n");
		निकास(निकास_त्रुटि);
	पूर्ण

	/* split all THPs */
	ग_लिखो_debugfs(PID_FMT, getpid(), (uपूर्णांक64_t)one_page,
		(uपूर्णांक64_t)one_page + len);

	क्रम (i = 0; i < len; i++)
		अगर (one_page[i] != (अक्षर)i) अणु
			म_लिखो("%ld byte corrupted\n", i);
			निकास(निकास_त्रुटि);
		पूर्ण


	thp_size = check_huge(one_page);
	अगर (thp_size) अणु
		म_लिखो("Still %ld kB AnonHugePages not split\n", thp_size);
		निकास(निकास_त्रुटि);
	पूर्ण

	म_लिखो("Split huge pages successful\n");
	मुक्त(one_page);
पूर्ण

व्योम split_pte_mapped_thp(व्योम)
अणु
	अक्षर *one_page, *pte_mapped, *pte_mapped2;
	माप_प्रकार len = 4 * pmd_pagesize;
	uपूर्णांक64_t thp_size;
	माप_प्रकार i;
	स्थिर अक्षर *pagemap_ढाँचा = "/proc/%d/pagemap";
	स्थिर अक्षर *kpageflags_proc = "/proc/kpageflags";
	अक्षर pagemap_proc[255];
	पूर्णांक pagemap_fd;
	पूर्णांक kpageflags_fd;

	अगर (snम_लिखो(pagemap_proc, 255, pagemap_ढाँचा, getpid()) < 0) अणु
		लिखो_त्रुटि("get pagemap proc error");
		निकास(निकास_त्रुटि);
	पूर्ण
	pagemap_fd = खोलो(pagemap_proc, O_RDONLY);

	अगर (pagemap_fd == -1) अणु
		लिखो_त्रुटि("read pagemap:");
		निकास(निकास_त्रुटि);
	पूर्ण

	kpageflags_fd = खोलो(kpageflags_proc, O_RDONLY);

	अगर (kpageflags_fd == -1) अणु
		लिखो_त्रुटि("read kpageflags:");
		निकास(निकास_त्रुटि);
	पूर्ण

	one_page = mmap((व्योम *)(1UL << 30), len, PROT_READ | PROT_WRITE,
			MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

	madvise(one_page, len, MADV_HUGEPAGE);

	क्रम (i = 0; i < len; i++)
		one_page[i] = (अक्षर)i;

	thp_size = check_huge(one_page);
	अगर (!thp_size) अणु
		म_लिखो("No THP is allocated\n");
		निकास(निकास_त्रुटि);
	पूर्ण

	/* remap the first pagesize of first THP */
	pte_mapped = mremap(one_page, pagesize, pagesize, MREMAP_MAYMOVE);

	/* remap the Nth pagesize of Nth THP */
	क्रम (i = 1; i < 4; i++) अणु
		pte_mapped2 = mremap(one_page + pmd_pagesize * i + pagesize * i,
				     pagesize, pagesize,
				     MREMAP_MAYMOVE|MREMAP_FIXED,
				     pte_mapped + pagesize * i);
		अगर (pte_mapped2 == (अक्षर *)-1) अणु
			लिखो_त्रुटि("mremap failed");
			निकास(निकास_त्रुटि);
		पूर्ण
	पूर्ण

	/* smap करोes not show THPs after mremap, use kpageflags instead */
	thp_size = 0;
	क्रम (i = 0; i < pagesize * 4; i++)
		अगर (i % pagesize == 0 &&
		    is_backed_by_thp(&pte_mapped[i], pagemap_fd, kpageflags_fd))
			thp_size++;

	अगर (thp_size != 4) अणु
		म_लिखो("Some THPs are missing during mremap\n");
		निकास(निकास_त्रुटि);
	पूर्ण

	/* split all remapped THPs */
	ग_लिखो_debugfs(PID_FMT, getpid(), (uपूर्णांक64_t)pte_mapped,
		      (uपूर्णांक64_t)pte_mapped + pagesize * 4);

	/* smap करोes not show THPs after mremap, use kpageflags instead */
	thp_size = 0;
	क्रम (i = 0; i < pagesize * 4; i++) अणु
		अगर (pte_mapped[i] != (अक्षर)i) अणु
			म_लिखो("%ld byte corrupted\n", i);
			निकास(निकास_त्रुटि);
		पूर्ण
		अगर (i % pagesize == 0 &&
		    is_backed_by_thp(&pte_mapped[i], pagemap_fd, kpageflags_fd))
			thp_size++;
	पूर्ण

	अगर (thp_size) अणु
		म_लिखो("Still %ld THPs not split\n", thp_size);
		निकास(निकास_त्रुटि);
	पूर्ण

	म_लिखो("Split PTE-mapped huge pages successful\n");
	munmap(one_page, len);
	बंद(pagemap_fd);
	बंद(kpageflags_fd);
पूर्ण

व्योम split_file_backed_thp(व्योम)
अणु
	पूर्णांक status;
	पूर्णांक fd;
	sमाप_प्रकार num_written;
	अक्षर पंचांगpfs_ढाँचा[] = "/tmp/thp_split_XXXXXX";
	स्थिर अक्षर *पंचांगpfs_loc = mkdtemp(पंचांगpfs_ढाँचा);
	अक्षर testfile[INPUT_MAX];
	uपूर्णांक64_t pgoff_start = 0, pgoff_end = 1024;

	म_लिखो("Please enable pr_debug in split_huge_pages_in_file() if you need more info.\n");

	status = mount("tmpfs", पंचांगpfs_loc, "tmpfs", 0, "huge=always,size=4m");

	अगर (status) अणु
		म_लिखो("Unable to create a tmpfs for testing\n");
		निकास(निकास_त्रुटि);
	पूर्ण

	status = snम_लिखो(testfile, INPUT_MAX, "%s/thp_file", पंचांगpfs_loc);
	अगर (status >= INPUT_MAX) अणु
		म_लिखो("Fail to create file-backed THP split testing file\n");
		जाओ cleanup;
	पूर्ण

	fd = खोलो(testfile, O_CREAT|O_WRONLY);
	अगर (fd == -1) अणु
		लिखो_त्रुटि("Cannot open testing file\n");
		जाओ cleanup;
	पूर्ण

	/* ग_लिखो something to the file, so a file-backed THP can be allocated */
	num_written = ग_लिखो(fd, पंचांगpfs_loc, माप(पंचांगpfs_loc));
	बंद(fd);

	अगर (num_written < 1) अणु
		म_लिखो("Fail to write data to testing file\n");
		जाओ cleanup;
	पूर्ण

	/* split the file-backed THP */
	ग_लिखो_debugfs(PATH_FMT, testfile, pgoff_start, pgoff_end);

	status = unlink(testfile);
	अगर (status)
		लिखो_त्रुटि("Cannot remove testing file\n");

cleanup:
	status = umount(पंचांगpfs_loc);
	अगर (status) अणु
		म_लिखो("Unable to umount %s\n", पंचांगpfs_loc);
		निकास(निकास_त्रुटि);
	पूर्ण
	status = सूची_हटाओ(पंचांगpfs_loc);
	अगर (status) अणु
		लिखो_त्रुटि("cannot remove tmp dir");
		निकास(निकास_त्रुटि);
	पूर्ण

	म_लिखो("file-backed THP split test done, please check dmesg for more information\n");
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	अगर (geteuid() != 0) अणु
		म_लिखो("Please run the benchmark as root\n");
		निकास(निकास_त्रुटि);
	पूर्ण

	pagesize = getpagesize();
	pageshअगरt = ffs(pagesize) - 1;
	pmd_pagesize = पढ़ो_pmd_pagesize();

	split_pmd_thp();
	split_pte_mapped_thp();
	split_file_backed_thp();

	वापस 0;
पूर्ण
