<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Test selecting other page sizes क्रम mmap/shmget.

   Beक्रमe running this huge pages क्रम each huge page size must have been
   reserved.
   For large pages beyond MAX_ORDER (like 1GB on x86) boot options must be used.
   Also shmmax must be increased.
   And you need to run as root to work around some weird permissions in shm.
   And nothing using huge pages should run in parallel.
   When the program पातs you may need to clean up the shm segments with
   ipcrm -m by hand, like this
   suकरो ipcs | awk '$1 == "0x00000000" {print $2}' | xargs -n1 suकरो ipcrm -m
   (warning this will हटाओ all अगर someone अन्यथा uses them) */

#घोषणा _GNU_SOURCE 1
#समावेश <sys/mman.h>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <sys/ipc.h>
#समावेश <sys/shm.h>
#समावेश <sys/स्थिति.स>
#समावेश <glob.h>
#समावेश <निश्चित.स>
#समावेश <unistd.h>
#समावेश <मानकतर्क.स>
#समावेश <माला.स>

#घोषणा err(x) लिखो_त्रुटि(x), निकास(1)

#घोषणा MAP_HUGE_2MB    (21 << MAP_HUGE_SHIFT)
#घोषणा MAP_HUGE_1GB    (30 << MAP_HUGE_SHIFT)
#घोषणा MAP_HUGE_SHIFT  26
#घोषणा MAP_HUGE_MASK   0x3f
#अगर !defined(MAP_HUGETLB)
#घोषणा MAP_HUGETLB	0x40000
#पूर्ण_अगर

#घोषणा SHM_HUGETLB     04000   /* segment will use huge TLB pages */
#घोषणा SHM_HUGE_SHIFT  26
#घोषणा SHM_HUGE_MASK   0x3f
#घोषणा SHM_HUGE_2MB    (21 << SHM_HUGE_SHIFT)
#घोषणा SHM_HUGE_1GB    (30 << SHM_HUGE_SHIFT)

#घोषणा NUM_PAGESIZES   5

#घोषणा NUM_PAGES 4

#घोषणा Dम_लिखो(fmt...) // म_लिखो(fmt)

अचिन्हित दीर्घ page_sizes[NUM_PAGESIZES];
पूर्णांक num_page_sizes;

पूर्णांक ilog2(अचिन्हित दीर्घ v)
अणु
	पूर्णांक l = 0;
	जबतक ((1UL << l) < v)
		l++;
	वापस l;
पूर्ण

व्योम find_pagesizes(व्योम)
अणु
	glob_t g;
	पूर्णांक i;
	glob("/sys/kernel/mm/hugepages/hugepages-*kB", 0, शून्य, &g);
	निश्चित(g.gl_pathc <= NUM_PAGESIZES);
	क्रम (i = 0; i < g.gl_pathc; i++) अणु
		माला_पूछो(g.gl_pathv[i], "/sys/kernel/mm/hugepages/hugepages-%lukB",
				&page_sizes[i]);
		page_sizes[i] <<= 10;
		म_लिखो("Found %luMB\n", page_sizes[i] >> 20);
	पूर्ण
	num_page_sizes = g.gl_pathc;
	globमुक्त(&g);
पूर्ण

अचिन्हित दीर्घ शेष_huge_page_size(व्योम)
अणु
	अचिन्हित दीर्घ hps = 0;
	अक्षर *line = शून्य;
	माप_प्रकार linelen = 0;
	खाता *f = ख_खोलो("/proc/meminfo", "r");
	अगर (!f)
		वापस 0;
	जबतक (getline(&line, &linelen, f) > 0) अणु
		अगर (माला_पूछो(line, "Hugepagesize:       %lu kB", &hps) == 1) अणु
			hps <<= 10;
			अवरोध;
		पूर्ण
	पूर्ण
	मुक्त(line);
	वापस hps;
पूर्ण

व्योम show(अचिन्हित दीर्घ ps)
अणु
	अक्षर buf[100];
	अगर (ps == getpagesize())
		वापस;
	म_लिखो("%luMB: ", ps >> 20);
	ख_साफ(मानक_निकास);
	snम_लिखो(buf, माप buf,
		"cat /sys/kernel/mm/hugepages/hugepages-%lukB/free_hugepages",
		ps >> 10);
	प्रणाली(buf);
पूर्ण

अचिन्हित दीर्घ पढ़ो_sysfs(पूर्णांक warn, अक्षर *fmt, ...)
अणु
	अक्षर *line = शून्य;
	माप_प्रकार linelen = 0;
	अक्षर buf[100];
	खाता *f;
	बहु_सूची ap;
	अचिन्हित दीर्घ val = 0;

	बहु_शुरू(ap, fmt);
	vsnम_लिखो(buf, माप buf, fmt, ap);
	बहु_पूर्ण(ap);

	f = ख_खोलो(buf, "r");
	अगर (!f) अणु
		अगर (warn)
			म_लिखो("missing %s\n", buf);
		वापस 0;
	पूर्ण
	अगर (getline(&line, &linelen, f) > 0) अणु
		माला_पूछो(line, "%lu", &val);
	पूर्ण
	ख_बंद(f);
	मुक्त(line);
	वापस val;
पूर्ण

अचिन्हित दीर्घ पढ़ो_मुक्त(अचिन्हित दीर्घ ps)
अणु
	वापस पढ़ो_sysfs(ps != getpagesize(),
			"/sys/kernel/mm/hugepages/hugepages-%lukB/free_hugepages",
			ps >> 10);
पूर्ण

व्योम test_mmap(अचिन्हित दीर्घ size, अचिन्हित flags)
अणु
	अक्षर *map;
	अचिन्हित दीर्घ beक्रमe, after;
	पूर्णांक err;

	beक्रमe = पढ़ो_मुक्त(size);
	map = mmap(शून्य, size*NUM_PAGES, PROT_READ|PROT_WRITE,
			MAP_PRIVATE|MAP_ANONYMOUS|MAP_HUGETLB|flags, -1, 0);

	अगर (map == (अक्षर *)-1) err("mmap");
	स_रखो(map, 0xff, size*NUM_PAGES);
	after = पढ़ो_मुक्त(size);
	Dम_लिखो("before %lu after %lu diff %ld size %lu\n",
		beक्रमe, after, beक्रमe - after, size);
	निश्चित(size == getpagesize() || (beक्रमe - after) == NUM_PAGES);
	show(size);
	err = munmap(map, size);
	निश्चित(!err);
पूर्ण

व्योम test_shmget(अचिन्हित दीर्घ size, अचिन्हित flags)
अणु
	पूर्णांक id;
	अचिन्हित दीर्घ beक्रमe, after;
	पूर्णांक err;

	beक्रमe = पढ़ो_मुक्त(size);
	id = shmget(IPC_PRIVATE, size * NUM_PAGES, IPC_CREAT|0600|flags);
	अगर (id < 0) err("shmget");

	काष्ठा shm_info i;
	अगर (shmctl(id, SHM_INFO, (व्योम *)&i) < 0) err("shmctl");
	Dम_लिखो("alloc %lu res %lu\n", i.shm_tot, i.shm_rss);


	Dम_लिखो("id %d\n", id);
	अक्षर *map = shmat(id, शून्य, 0600);
	अगर (map == (अक्षर*)-1) err("shmat");

	shmctl(id, IPC_RMID, शून्य);

	स_रखो(map, 0xff, size*NUM_PAGES);
	after = पढ़ो_मुक्त(size);

	Dम_लिखो("before %lu after %lu diff %ld size %lu\n",
		beक्रमe, after, beक्रमe - after, size);
	निश्चित(size == getpagesize() || (beक्रमe - after) == NUM_PAGES);
	show(size);
	err = shmdt(map);
	निश्चित(!err);
पूर्ण

व्योम sanity_checks(व्योम)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ largest = getpagesize();

	क्रम (i = 0; i < num_page_sizes; i++) अणु
		अगर (page_sizes[i] > largest)
			largest = page_sizes[i];

		अगर (पढ़ो_मुक्त(page_sizes[i]) < NUM_PAGES) अणु
			म_लिखो("Not enough huge pages for page size %lu MB, need %u\n",
				page_sizes[i] >> 20,
				NUM_PAGES);
			निकास(0);
		पूर्ण
	पूर्ण

	अगर (पढ़ो_sysfs(0, "/proc/sys/kernel/shmmax") < NUM_PAGES * largest) अणु
		म_लिखो("Please do echo %lu > /proc/sys/kernel/shmmax", largest * NUM_PAGES);
		निकास(0);
	पूर्ण

#अगर defined(__x86_64__)
	अगर (largest != 1U<<30) अणु
		म_लिखो("No GB pages available on x86-64\n"
		       "Please boot with hugepagesz=1G hugepages=%d\n", NUM_PAGES);
		निकास(0);
	पूर्ण
#पूर्ण_अगर
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	पूर्णांक i;
	अचिन्हित शेष_hps = शेष_huge_page_size();

	find_pagesizes();

	sanity_checks();

	क्रम (i = 0; i < num_page_sizes; i++) अणु
		अचिन्हित दीर्घ ps = page_sizes[i];
		पूर्णांक arg = ilog2(ps) << MAP_HUGE_SHIFT;
		म_लिखो("Testing %luMB mmap with shift %x\n", ps >> 20, arg);
		test_mmap(ps, MAP_HUGETLB | arg);
	पूर्ण
	म_लिखो("Testing default huge mmap\n");
	test_mmap(शेष_hps, SHM_HUGETLB);

	माला_दो("Testing non-huge shmget");
	test_shmget(getpagesize(), 0);

	क्रम (i = 0; i < num_page_sizes; i++) अणु
		अचिन्हित दीर्घ ps = page_sizes[i];
		पूर्णांक arg = ilog2(ps) << SHM_HUGE_SHIFT;
		म_लिखो("Testing %luMB shmget with shift %x\n", ps >> 20, arg);
		test_shmget(ps, SHM_HUGETLB | arg);
	पूर्ण
	माला_दो("default huge shmget");
	test_shmget(शेष_hps, SHM_HUGETLB);

	वापस 0;
पूर्ण
