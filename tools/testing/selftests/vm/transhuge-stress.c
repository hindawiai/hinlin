<शैली गुरु>
/*
 * Stress test क्रम transparent huge pages, memory compaction and migration.
 *
 * Authors: Konstantin Khlebnikov <koct9i@gmail.com>
 *
 * This is मुक्त and unencumbered software released पूर्णांकo the खुला करोमुख्य.
 */

#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <मानक_निवेशt.h>
#समावेश <err.h>
#समावेश <समय.स>
#समावेश <unistd.h>
#समावेश <fcntl.h>
#समावेश <माला.स>
#समावेश <sys/mman.h>

#घोषणा PAGE_SHIFT 12
#घोषणा HPAGE_SHIFT 21

#घोषणा PAGE_SIZE (1 << PAGE_SHIFT)
#घोषणा HPAGE_SIZE (1 << HPAGE_SHIFT)

#घोषणा PAGEMAP_PRESENT(ent)	(((ent) & (1ull << 63)) != 0)
#घोषणा PAGEMAP_PFN(ent)	((ent) & ((1ull << 55) - 1))

पूर्णांक pagemap_fd;

पूर्णांक64_t allocate_transhuge(व्योम *ptr)
अणु
	uपूर्णांक64_t ent[2];

	/* drop pmd */
	अगर (mmap(ptr, HPAGE_SIZE, PROT_READ | PROT_WRITE,
				MAP_FIXED | MAP_ANONYMOUS |
				MAP_NORESERVE | MAP_PRIVATE, -1, 0) != ptr)
		errx(2, "mmap transhuge");

	अगर (madvise(ptr, HPAGE_SIZE, MADV_HUGEPAGE))
		err(2, "MADV_HUGEPAGE");

	/* allocate transparent huge page */
	*(अस्थिर व्योम **)ptr = ptr;

	अगर (pपढ़ो(pagemap_fd, ent, माप(ent),
			(uपूर्णांकptr_t)ptr >> (PAGE_SHIFT - 3)) != माप(ent))
		err(2, "read pagemap");

	अगर (PAGEMAP_PRESENT(ent[0]) && PAGEMAP_PRESENT(ent[1]) &&
	    PAGEMAP_PFN(ent[0]) + 1 == PAGEMAP_PFN(ent[1]) &&
	    !(PAGEMAP_PFN(ent[0]) & ((1 << (HPAGE_SHIFT - PAGE_SHIFT)) - 1)))
		वापस PAGEMAP_PFN(ent[0]);

	वापस -1;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	माप_प्रकार ram, len;
	व्योम *ptr, *p;
	काष्ठा बारpec a, b;
	द्विगुन s;
	uपूर्णांक8_t *map;
	माप_प्रकार map_len;

	ram = sysconf(_SC_PHYS_PAGES);
	अगर (ram > SIZE_MAX / sysconf(_SC_PAGESIZE) / 4)
		ram = SIZE_MAX / 4;
	अन्यथा
		ram *= sysconf(_SC_PAGESIZE);

	अगर (argc == 1)
		len = ram;
	अन्यथा अगर (!म_भेद(argv[1], "-h"))
		errx(1, "usage: %s [size in MiB]", argv[0]);
	अन्यथा
		len = म_से_दl(argv[1]) << 20;

	warnx("allocate %zd transhuge pages, using %zd MiB virtual memory"
	      " and %zd MiB of ram", len >> HPAGE_SHIFT, len >> 20,
	      len >> (20 + HPAGE_SHIFT - PAGE_SHIFT - 1));

	pagemap_fd = खोलो("/proc/self/pagemap", O_RDONLY);
	अगर (pagemap_fd < 0)
		err(2, "open pagemap");

	len -= len % HPAGE_SIZE;
	ptr = mmap(शून्य, len + HPAGE_SIZE, PROT_READ | PROT_WRITE,
			MAP_ANONYMOUS | MAP_NORESERVE | MAP_PRIVATE, -1, 0);
	अगर (ptr == MAP_FAILED)
		err(2, "initial mmap");
	ptr += HPAGE_SIZE - (uपूर्णांकptr_t)ptr % HPAGE_SIZE;

	अगर (madvise(ptr, len, MADV_HUGEPAGE))
		err(2, "MADV_HUGEPAGE");

	map_len = ram >> (HPAGE_SHIFT - 1);
	map = दो_स्मृति(map_len);
	अगर (!map)
		errx(2, "map malloc");

	जबतक (1) अणु
		पूर्णांक nr_succeed = 0, nr_failed = 0, nr_pages = 0;

		स_रखो(map, 0, map_len);

		घड़ी_समय_लो(CLOCK_MONOTONIC, &a);
		क्रम (p = ptr; p < ptr + len; p += HPAGE_SIZE) अणु
			पूर्णांक64_t pfn;

			pfn = allocate_transhuge(p);

			अगर (pfn < 0) अणु
				nr_failed++;
			पूर्ण अन्यथा अणु
				माप_प्रकार idx = pfn >> (HPAGE_SHIFT - PAGE_SHIFT);

				nr_succeed++;
				अगर (idx >= map_len) अणु
					map = पुनः_स्मृति(map, idx + 1);
					अगर (!map)
						errx(2, "map realloc");
					स_रखो(map + map_len, 0, idx + 1 - map_len);
					map_len = idx + 1;
				पूर्ण
				अगर (!map[idx])
					nr_pages++;
				map[idx] = 1;
			पूर्ण

			/* split transhuge page, keep last page */
			अगर (madvise(p, HPAGE_SIZE - PAGE_SIZE, MADV_DONTNEED))
				err(2, "MADV_DONTNEED");
		पूर्ण
		घड़ी_समय_लो(CLOCK_MONOTONIC, &b);
		s = b.tv_sec - a.tv_sec + (b.tv_nsec - a.tv_nsec) / 1000000000.;

		warnx("%.3f s/loop, %.3f ms/page, %10.3f MiB/s\t"
		      "%4d succeed, %4d failed, %4d different pages",
		      s, s * 1000 / (len >> HPAGE_SHIFT), len / s / (1 << 20),
		      nr_succeed, nr_failed, nr_pages);
	पूर्ण
पूर्ण
