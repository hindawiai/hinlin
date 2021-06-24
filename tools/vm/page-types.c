<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * page-types: Tool क्रम querying page flags
 *
 * Copyright (C) 2009 Intel corporation
 *
 * Authors: Wu Fengguang <fengguang.wu@पूर्णांकel.com>
 */

#घोषणा _खाता_OFFSET_BITS 64
#घोषणा _GNU_SOURCE
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <मानक_निवेशt.h>
#समावेश <मानकतर्क.स>
#समावेश <माला.स>
#समावेश <getopt.h>
#समावेश <सीमा.स>
#समावेश <निश्चित.स>
#समावेश <ftw.h>
#समावेश <समय.स>
#समावेश <समलाँघ.स>
#समावेश <संकेत.स>
#समावेश <sys/types.h>
#समावेश <sys/त्रुटिसं.स>
#समावेश <sys/fcntl.h>
#समावेश <sys/mount.h>
#समावेश <sys/statfs.h>
#समावेश <sys/mman.h>
#समावेश "../../include/uapi/linux/magic.h"
#समावेश "../../include/uapi/linux/kernel-page-flags.h"
#समावेश <api/fs/fs.h>

#अगर_अघोषित MAX_PATH
# define MAX_PATH 256
#पूर्ण_अगर

#अगर_अघोषित STR
# define _STR(x) #x
# define STR(x) _STR(x)
#पूर्ण_अगर

/*
 * pagemap kernel ABI bits
 */

#घोषणा PM_ENTRY_BYTES		8
#घोषणा PM_PFRAME_BITS		55
#घोषणा PM_PFRAME_MASK		((1LL << PM_PFRAME_BITS) - 1)
#घोषणा PM_PFRAME(x)		((x) & PM_PFRAME_MASK)
#घोषणा MAX_SWAPखाताS_SHIFT	5
#घोषणा PM_SWAP_OFFSET(x)	(((x) & PM_PFRAME_MASK) >> MAX_SWAPखाताS_SHIFT)
#घोषणा PM_SOFT_सूचीTY		(1ULL << 55)
#घोषणा PM_MMAP_EXCLUSIVE	(1ULL << 56)
#घोषणा PM_खाता			(1ULL << 61)
#घोषणा PM_SWAP			(1ULL << 62)
#घोषणा PM_PRESENT		(1ULL << 63)

/*
 * kernel page flags
 */

#घोषणा KPF_BYTES		8
#घोषणा PROC_KPAGEFLAGS		"/proc/kpageflags"
#घोषणा PROC_KPAGECOUNT		"/proc/kpagecount"
#घोषणा PROC_KPAGECGROUP	"/proc/kpagecgroup"

#घोषणा SYS_KERNEL_MM_PAGE_IDLE "/sys/kernel/mm/page_idle/bitmap"

/* [32-] kernel hacking assistances */
#घोषणा KPF_RESERVED		32
#घोषणा KPF_MLOCKED		33
#घोषणा KPF_MAPPEDTODISK	34
#घोषणा KPF_PRIVATE		35
#घोषणा KPF_PRIVATE_2		36
#घोषणा KPF_OWNER_PRIVATE	37
#घोषणा KPF_ARCH		38
#घोषणा KPF_UNCACHED		39
#घोषणा KPF_SOFTसूचीTY		40
#घोषणा KPF_ARCH_2		41

/* [48-] take some arbitrary मुक्त slots क्रम expanding overloaded flags
 * not part of kernel API
 */
#घोषणा KPF_READAHEAD		48
#घोषणा KPF_SLOB_FREE		49
#घोषणा KPF_SLUB_FROZEN		50
#घोषणा KPF_SLUB_DEBUG		51
#घोषणा KPF_खाता		61
#घोषणा KPF_SWAP		62
#घोषणा KPF_MMAP_EXCLUSIVE	63

#घोषणा KPF_ALL_BITS		((uपूर्णांक64_t)~0ULL)
#घोषणा KPF_HACKERS_BITS	(0xffffULL << 32)
#घोषणा KPF_OVERLOADED_BITS	(0xffffULL << 48)
#घोषणा BIT(name)		(1ULL << KPF_##name)
#घोषणा BITS_COMPOUND		(BIT(COMPOUND_HEAD) | BIT(COMPOUND_TAIL))

अटल स्थिर अक्षर * स्थिर page_flag_names[] = अणु
	[KPF_LOCKED]		= "L:locked",
	[KPF_ERROR]		= "E:error",
	[KPF_REFERENCED]	= "R:referenced",
	[KPF_UPTODATE]		= "U:uptodate",
	[KPF_सूचीTY]		= "D:dirty",
	[KPF_LRU]		= "l:lru",
	[KPF_ACTIVE]		= "A:active",
	[KPF_SLAB]		= "S:slab",
	[KPF_WRITEBACK]		= "W:writeback",
	[KPF_RECLAIM]		= "I:reclaim",
	[KPF_BUDDY]		= "B:buddy",

	[KPF_MMAP]		= "M:mmap",
	[KPF_ANON]		= "a:anonymous",
	[KPF_SWAPCACHE]		= "s:swapcache",
	[KPF_SWAPBACKED]	= "b:swapbacked",
	[KPF_COMPOUND_HEAD]	= "H:compound_head",
	[KPF_COMPOUND_TAIL]	= "T:compound_tail",
	[KPF_HUGE]		= "G:huge",
	[KPF_UNEVICTABLE]	= "u:unevictable",
	[KPF_HWPOISON]		= "X:hwpoison",
	[KPF_NOPAGE]		= "n:nopage",
	[KPF_KSM]		= "x:ksm",
	[KPF_THP]		= "t:thp",
	[KPF_OFFLINE]		= "o:offline",
	[KPF_PGTABLE]		= "g:pgtable",
	[KPF_ZERO_PAGE]		= "z:zero_page",
	[KPF_IDLE]              = "i:idle_page",

	[KPF_RESERVED]		= "r:reserved",
	[KPF_MLOCKED]		= "m:mlocked",
	[KPF_MAPPEDTODISK]	= "d:mappedtodisk",
	[KPF_PRIVATE]		= "P:private",
	[KPF_PRIVATE_2]		= "p:private_2",
	[KPF_OWNER_PRIVATE]	= "O:owner_private",
	[KPF_ARCH]		= "h:arch",
	[KPF_UNCACHED]		= "c:uncached",
	[KPF_SOFTसूचीTY]		= "f:softdirty",
	[KPF_ARCH_2]		= "H:arch_2",

	[KPF_READAHEAD]		= "I:readahead",
	[KPF_SLOB_FREE]		= "P:slob_free",
	[KPF_SLUB_FROZEN]	= "A:slub_frozen",
	[KPF_SLUB_DEBUG]	= "E:slub_debug",

	[KPF_खाता]		= "F:file",
	[KPF_SWAP]		= "w:swap",
	[KPF_MMAP_EXCLUSIVE]	= "1:mmap_exclusive",
पूर्ण;


/*
 * data काष्ठाures
 */

अटल पूर्णांक		opt_raw;	/* क्रम kernel developers */
अटल पूर्णांक		opt_list;	/* list pages (in ranges) */
अटल पूर्णांक		opt_mark_idle;	/* set accessed bit */
अटल पूर्णांक		opt_no_summary;	/* करोn't show summary */
अटल pid_t		opt_pid;	/* process to walk */
स्थिर अक्षर		*opt_file;	/* file or directory path */
अटल uपूर्णांक64_t		opt_cgroup;	/* cgroup inode */
अटल पूर्णांक		opt_list_cgroup;/* list page cgroup */
अटल पूर्णांक		opt_list_mapcnt;/* list page map count */
अटल स्थिर अक्षर	*opt_kpageflags;/* kpageflags file to parse */

#घोषणा MAX_ADDR_RANGES	1024
अटल पूर्णांक		nr_addr_ranges;
अटल अचिन्हित दीर्घ	opt_offset[MAX_ADDR_RANGES];
अटल अचिन्हित दीर्घ	opt_size[MAX_ADDR_RANGES];

#घोषणा MAX_VMAS	10240
अटल पूर्णांक		nr_vmas;
अटल अचिन्हित दीर्घ	pg_start[MAX_VMAS];
अटल अचिन्हित दीर्घ	pg_end[MAX_VMAS];

#घोषणा MAX_BIT_FILTERS	64
अटल पूर्णांक		nr_bit_filters;
अटल uपूर्णांक64_t		opt_mask[MAX_BIT_FILTERS];
अटल uपूर्णांक64_t		opt_bits[MAX_BIT_FILTERS];

अटल पूर्णांक		page_size;

अटल पूर्णांक		pagemap_fd;
अटल पूर्णांक		kpageflags_fd;
अटल पूर्णांक		kpagecount_fd = -1;
अटल पूर्णांक		kpagecgroup_fd = -1;
अटल पूर्णांक		page_idle_fd = -1;

अटल पूर्णांक		opt_hwpoison;
अटल पूर्णांक		opt_unpoison;

अटल स्थिर अक्षर	*hwpoison_debug_fs;
अटल पूर्णांक		hwpoison_inject_fd;
अटल पूर्णांक		hwpoison_क्रमget_fd;

#घोषणा HASH_SHIFT	13
#घोषणा HASH_SIZE	(1 << HASH_SHIFT)
#घोषणा HASH_MASK	(HASH_SIZE - 1)
#घोषणा HASH_KEY(flags)	(flags & HASH_MASK)

अटल अचिन्हित दीर्घ	total_pages;
अटल अचिन्हित दीर्घ	nr_pages[HASH_SIZE];
अटल uपूर्णांक64_t		page_flags[HASH_SIZE];


/*
 * helper functions
 */

#घोषणा ARRAY_SIZE(x) (माप(x) / माप((x)[0]))

#घोषणा min_t(type, x, y) (अणु			\
	type __min1 = (x);			\
	type __min2 = (y);			\
	__min1 < __min2 ? __min1 : __min2; पूर्ण)

#घोषणा max_t(type, x, y) (अणु			\
	type __max1 = (x);			\
	type __max2 = (y);			\
	__max1 > __max2 ? __max1 : __max2; पूर्ण)

अटल अचिन्हित दीर्घ pages2mb(अचिन्हित दीर्घ pages)
अणु
	वापस (pages * page_size) >> 20;
पूर्ण

अटल व्योम fatal(स्थिर अक्षर *x, ...)
अणु
	बहु_सूची ap;

	बहु_शुरू(ap, x);
	भख_लिखो(मानक_त्रुटि, x, ap);
	बहु_पूर्ण(ap);
	निकास(निकास_त्रुटि);
पूर्ण

अटल पूर्णांक checked_खोलो(स्थिर अक्षर *pathname, पूर्णांक flags)
अणु
	पूर्णांक fd = खोलो(pathname, flags);

	अगर (fd < 0) अणु
		लिखो_त्रुटि(pathname);
		निकास(निकास_त्रुटि);
	पूर्ण

	वापस fd;
पूर्ण

/*
 * pagemap/kpageflags routines
 */

अटल अचिन्हित दीर्घ करो_u64_पढ़ो(पूर्णांक fd, स्थिर अक्षर *name,
				 uपूर्णांक64_t *buf,
				 अचिन्हित दीर्घ index,
				 अचिन्हित दीर्घ count)
अणु
	दीर्घ bytes;

	अगर (index > अच_दीर्घ_उच्च / 8)
		fatal("index overflow: %lu\n", index);

	bytes = pपढ़ो(fd, buf, count * 8, (off_t)index * 8);
	अगर (bytes < 0) अणु
		लिखो_त्रुटि(name);
		निकास(निकास_त्रुटि);
	पूर्ण
	अगर (bytes % 8)
		fatal("partial read: %lu bytes\n", bytes);

	वापस bytes / 8;
पूर्ण

अटल अचिन्हित दीर्घ kpageflags_पढ़ो(uपूर्णांक64_t *buf,
				     अचिन्हित दीर्घ index,
				     अचिन्हित दीर्घ pages)
अणु
	वापस करो_u64_पढ़ो(kpageflags_fd, opt_kpageflags, buf, index, pages);
पूर्ण

अटल अचिन्हित दीर्घ kpagecgroup_पढ़ो(uपूर्णांक64_t *buf,
				      अचिन्हित दीर्घ index,
				      अचिन्हित दीर्घ pages)
अणु
	अगर (kpagecgroup_fd < 0)
		वापस pages;

	वापस करो_u64_पढ़ो(kpagecgroup_fd, opt_kpageflags, buf, index, pages);
पूर्ण

अटल अचिन्हित दीर्घ kpagecount_पढ़ो(uपूर्णांक64_t *buf,
				     अचिन्हित दीर्घ index,
				     अचिन्हित दीर्घ pages)
अणु
	वापस kpagecount_fd < 0 ? pages :
		करो_u64_पढ़ो(kpagecount_fd, PROC_KPAGECOUNT,
			    buf, index, pages);
पूर्ण

अटल अचिन्हित दीर्घ pagemap_पढ़ो(uपूर्णांक64_t *buf,
				  अचिन्हित दीर्घ index,
				  अचिन्हित दीर्घ pages)
अणु
	वापस करो_u64_पढ़ो(pagemap_fd, "/proc/pid/pagemap", buf, index, pages);
पूर्ण

अटल अचिन्हित दीर्घ pagemap_pfn(uपूर्णांक64_t val)
अणु
	अचिन्हित दीर्घ pfn;

	अगर (val & PM_PRESENT)
		pfn = PM_PFRAME(val);
	अन्यथा
		pfn = 0;

	वापस pfn;
पूर्ण

अटल अचिन्हित दीर्घ pagemap_swap_offset(uपूर्णांक64_t val)
अणु
	वापस val & PM_SWAP ? PM_SWAP_OFFSET(val) : 0;
पूर्ण

/*
 * page flag names
 */

अटल अक्षर *page_flag_name(uपूर्णांक64_t flags)
अणु
	अटल अक्षर buf[65];
	पूर्णांक present;
	माप_प्रकार i, j;

	क्रम (i = 0, j = 0; i < ARRAY_SIZE(page_flag_names); i++) अणु
		present = (flags >> i) & 1;
		अगर (!page_flag_names[i]) अणु
			अगर (present)
				fatal("unknown flag bit %d\n", i);
			जारी;
		पूर्ण
		buf[j++] = present ? page_flag_names[i][0] : '_';
	पूर्ण

	वापस buf;
पूर्ण

अटल अक्षर *page_flag_दीर्घname(uपूर्णांक64_t flags)
अणु
	अटल अक्षर buf[1024];
	माप_प्रकार i, n;

	क्रम (i = 0, n = 0; i < ARRAY_SIZE(page_flag_names); i++) अणु
		अगर (!page_flag_names[i])
			जारी;
		अगर ((flags >> i) & 1)
			n += snम_लिखो(buf + n, माप(buf) - n, "%s,",
					page_flag_names[i] + 2);
	पूर्ण
	अगर (n)
		n--;
	buf[n] = '\0';

	वापस buf;
पूर्ण


/*
 * page list and summary
 */

अटल व्योम show_page_range(अचिन्हित दीर्घ voffset, अचिन्हित दीर्घ offset,
			    अचिन्हित दीर्घ size, uपूर्णांक64_t flags,
			    uपूर्णांक64_t cgroup, uपूर्णांक64_t mapcnt)
अणु
	अटल uपूर्णांक64_t      flags0;
	अटल uपूर्णांक64_t	     cgroup0;
	अटल uपूर्णांक64_t      mapcnt0;
	अटल अचिन्हित दीर्घ voff;
	अटल अचिन्हित दीर्घ index;
	अटल अचिन्हित दीर्घ count;

	अगर (flags == flags0 && cgroup == cgroup0 && mapcnt == mapcnt0 &&
	    offset == index + count && size && voffset == voff + count) अणु
		count += size;
		वापस;
	पूर्ण

	अगर (count) अणु
		अगर (opt_pid)
			म_लिखो("%lx\t", voff);
		अगर (opt_file)
			म_लिखो("%lu\t", voff);
		अगर (opt_list_cgroup)
			म_लिखो("@%llu\t", (अचिन्हित दीर्घ दीर्घ)cgroup0);
		अगर (opt_list_mapcnt)
			म_लिखो("%lu\t", mapcnt0);
		म_लिखो("%lx\t%lx\t%s\n",
				index, count, page_flag_name(flags0));
	पूर्ण

	flags0 = flags;
	cgroup0 = cgroup;
	mapcnt0 = mapcnt;
	index  = offset;
	voff   = voffset;
	count  = size;
पूर्ण

अटल व्योम flush_page_range(व्योम)
अणु
	show_page_range(0, 0, 0, 0, 0, 0);
पूर्ण

अटल व्योम show_page(अचिन्हित दीर्घ voffset, अचिन्हित दीर्घ offset,
		      uपूर्णांक64_t flags, uपूर्णांक64_t cgroup, uपूर्णांक64_t mapcnt)
अणु
	अगर (opt_pid)
		म_लिखो("%lx\t", voffset);
	अगर (opt_file)
		म_लिखो("%lu\t", voffset);
	अगर (opt_list_cgroup)
		म_लिखो("@%llu\t", (अचिन्हित दीर्घ दीर्घ)cgroup);
	अगर (opt_list_mapcnt)
		म_लिखो("%lu\t", mapcnt);

	म_लिखो("%lx\t%s\n", offset, page_flag_name(flags));
पूर्ण

अटल व्योम show_summary(व्योम)
अणु
	माप_प्रकार i;

	म_लिखो("             flags\tpage-count       MB"
		"  symbolic-flags\t\t\tlong-symbolic-flags\n");

	क्रम (i = 0; i < ARRAY_SIZE(nr_pages); i++) अणु
		अगर (nr_pages[i])
			म_लिखो("0x%016llx\t%10lu %8lu  %s\t%s\n",
				(अचिन्हित दीर्घ दीर्घ)page_flags[i],
				nr_pages[i],
				pages2mb(nr_pages[i]),
				page_flag_name(page_flags[i]),
				page_flag_दीर्घname(page_flags[i]));
	पूर्ण

	म_लिखो("             total\t%10lu %8lu\n",
			total_pages, pages2mb(total_pages));
पूर्ण


/*
 * page flag filters
 */

अटल पूर्णांक bit_mask_ok(uपूर्णांक64_t flags)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_bit_filters; i++) अणु
		अगर (opt_bits[i] == KPF_ALL_BITS) अणु
			अगर ((flags & opt_mask[i]) == 0)
				वापस 0;
		पूर्ण अन्यथा अणु
			अगर ((flags & opt_mask[i]) != opt_bits[i])
				वापस 0;
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

अटल uपूर्णांक64_t expand_overloaded_flags(uपूर्णांक64_t flags, uपूर्णांक64_t pme)
अणु
	/* SLOB/SLUB overload several page flags */
	अगर (flags & BIT(SLAB)) अणु
		अगर (flags & BIT(PRIVATE))
			flags ^= BIT(PRIVATE) | BIT(SLOB_FREE);
		अगर (flags & BIT(ACTIVE))
			flags ^= BIT(ACTIVE) | BIT(SLUB_FROZEN);
		अगर (flags & BIT(ERROR))
			flags ^= BIT(ERROR) | BIT(SLUB_DEBUG);
	पूर्ण

	/* PG_reclaim is overloaded as PG_पढ़ोahead in the पढ़ो path */
	अगर ((flags & (BIT(RECLAIM) | BIT(WRITEBACK))) == BIT(RECLAIM))
		flags ^= BIT(RECLAIM) | BIT(READAHEAD);

	अगर (pme & PM_SOFT_सूचीTY)
		flags |= BIT(SOFTसूचीTY);
	अगर (pme & PM_खाता)
		flags |= BIT(खाता);
	अगर (pme & PM_SWAP)
		flags |= BIT(SWAP);
	अगर (pme & PM_MMAP_EXCLUSIVE)
		flags |= BIT(MMAP_EXCLUSIVE);

	वापस flags;
पूर्ण

अटल uपूर्णांक64_t well_known_flags(uपूर्णांक64_t flags)
अणु
	/* hide flags पूर्णांकended only क्रम kernel hacker */
	flags &= ~KPF_HACKERS_BITS;

	/* hide non-hugeTLB compound pages */
	अगर ((flags & BITS_COMPOUND) && !(flags & BIT(HUGE)))
		flags &= ~BITS_COMPOUND;

	वापस flags;
पूर्ण

अटल uपूर्णांक64_t kpageflags_flags(uपूर्णांक64_t flags, uपूर्णांक64_t pme)
अणु
	अगर (opt_raw)
		flags = expand_overloaded_flags(flags, pme);
	अन्यथा
		flags = well_known_flags(flags);

	वापस flags;
पूर्ण

/*
 * page actions
 */

अटल व्योम prepare_hwpoison_fd(व्योम)
अणु
	अक्षर buf[MAX_PATH + 1];

	hwpoison_debug_fs = debugfs__mount();
	अगर (!hwpoison_debug_fs) अणु
		लिखो_त्रुटि("mount debugfs");
		निकास(निकास_त्रुटि);
	पूर्ण

	अगर (opt_hwpoison && !hwpoison_inject_fd) अणु
		snम_लिखो(buf, MAX_PATH, "%s/hwpoison/corrupt-pfn",
			hwpoison_debug_fs);
		hwpoison_inject_fd = checked_खोलो(buf, O_WRONLY);
	पूर्ण

	अगर (opt_unpoison && !hwpoison_क्रमget_fd) अणु
		snम_लिखो(buf, MAX_PATH, "%s/hwpoison/unpoison-pfn",
			hwpoison_debug_fs);
		hwpoison_क्रमget_fd = checked_खोलो(buf, O_WRONLY);
	पूर्ण
पूर्ण

अटल पूर्णांक hwpoison_page(अचिन्हित दीर्घ offset)
अणु
	अक्षर buf[100];
	पूर्णांक len;

	len = प्र_लिखो(buf, "0x%lx\n", offset);
	len = ग_लिखो(hwpoison_inject_fd, buf, len);
	अगर (len < 0) अणु
		लिखो_त्रुटि("hwpoison inject");
		वापस len;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक unpoison_page(अचिन्हित दीर्घ offset)
अणु
	अक्षर buf[100];
	पूर्णांक len;

	len = प्र_लिखो(buf, "0x%lx\n", offset);
	len = ग_लिखो(hwpoison_क्रमget_fd, buf, len);
	अगर (len < 0) अणु
		लिखो_त्रुटि("hwpoison forget");
		वापस len;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mark_page_idle(अचिन्हित दीर्घ offset)
अणु
	अटल अचिन्हित दीर्घ off;
	अटल uपूर्णांक64_t buf;
	पूर्णांक len;

	अगर ((offset / 64 == off / 64) || buf == 0) अणु
		buf |= 1UL << (offset % 64);
		off = offset;
		वापस 0;
	पूर्ण

	len = pग_लिखो(page_idle_fd, &buf, 8, 8 * (off / 64));
	अगर (len < 0) अणु
		लिखो_त्रुटि("mark page idle");
		वापस len;
	पूर्ण

	buf = 1UL << (offset % 64);
	off = offset;

	वापस 0;
पूर्ण

/*
 * page frame walker
 */

अटल माप_प्रकार hash_slot(uपूर्णांक64_t flags)
अणु
	माप_प्रकार k = HASH_KEY(flags);
	माप_प्रकार i;

	/* Explicitly reserve slot 0 क्रम flags 0: the following logic
	 * cannot distinguish an unoccupied slot from slot (flags==0).
	 */
	अगर (flags == 0)
		वापस 0;

	/* search through the reमुख्यing (HASH_SIZE-1) slots */
	क्रम (i = 1; i < ARRAY_SIZE(page_flags); i++, k++) अणु
		अगर (!k || k >= ARRAY_SIZE(page_flags))
			k = 1;
		अगर (page_flags[k] == 0) अणु
			page_flags[k] = flags;
			वापस k;
		पूर्ण
		अगर (page_flags[k] == flags)
			वापस k;
	पूर्ण

	fatal("hash table full: bump up HASH_SHIFT?\n");
	निकास(निकास_त्रुटि);
पूर्ण

अटल व्योम add_page(अचिन्हित दीर्घ voffset, अचिन्हित दीर्घ offset,
		     uपूर्णांक64_t flags, uपूर्णांक64_t cgroup, uपूर्णांक64_t mapcnt,
		     uपूर्णांक64_t pme)
अणु
	flags = kpageflags_flags(flags, pme);

	अगर (!bit_mask_ok(flags))
		वापस;

	अगर (opt_cgroup && cgroup != (uपूर्णांक64_t)opt_cgroup)
		वापस;

	अगर (opt_hwpoison)
		hwpoison_page(offset);
	अगर (opt_unpoison)
		unpoison_page(offset);

	अगर (opt_mark_idle)
		mark_page_idle(offset);

	अगर (opt_list == 1)
		show_page_range(voffset, offset, 1, flags, cgroup, mapcnt);
	अन्यथा अगर (opt_list == 2)
		show_page(voffset, offset, flags, cgroup, mapcnt);

	nr_pages[hash_slot(flags)]++;
	total_pages++;
पूर्ण

#घोषणा KPAGEFLAGS_BATCH	(64 << 10)	/* 64k pages */
अटल व्योम walk_pfn(अचिन्हित दीर्घ voffset,
		     अचिन्हित दीर्घ index,
		     अचिन्हित दीर्घ count,
		     uपूर्णांक64_t pme)
अणु
	uपूर्णांक64_t buf[KPAGEFLAGS_BATCH];
	uपूर्णांक64_t cgi[KPAGEFLAGS_BATCH];
	uपूर्णांक64_t cnt[KPAGEFLAGS_BATCH];
	अचिन्हित दीर्घ batch;
	अचिन्हित दीर्घ pages;
	अचिन्हित दीर्घ i;

	/*
	 * kpagecgroup_पढ़ो() पढ़ोs only अगर kpagecgroup were खोलोed, but
	 * /proc/kpagecgroup might even not exist, so it's better to fill
	 * them with zeros here.
	 */
	अगर (count == 1)
		cgi[0] = 0;
	अन्यथा
		स_रखो(cgi, 0, माप cgi);

	जबतक (count) अणु
		batch = min_t(अचिन्हित दीर्घ, count, KPAGEFLAGS_BATCH);
		pages = kpageflags_पढ़ो(buf, index, batch);
		अगर (pages == 0)
			अवरोध;

		अगर (kpagecgroup_पढ़ो(cgi, index, pages) != pages)
			fatal("kpagecgroup returned fewer pages than expected");

		अगर (kpagecount_पढ़ो(cnt, index, pages) != pages)
			fatal("kpagecount returned fewer pages than expected");

		क्रम (i = 0; i < pages; i++)
			add_page(voffset + i, index + i,
				 buf[i], cgi[i], cnt[i], pme);

		index += pages;
		count -= pages;
	पूर्ण
पूर्ण

अटल व्योम walk_swap(अचिन्हित दीर्घ voffset, uपूर्णांक64_t pme)
अणु
	uपूर्णांक64_t flags = kpageflags_flags(0, pme);

	अगर (!bit_mask_ok(flags))
		वापस;

	अगर (opt_cgroup)
		वापस;

	अगर (opt_list == 1)
		show_page_range(voffset, pagemap_swap_offset(pme),
				1, flags, 0, 0);
	अन्यथा अगर (opt_list == 2)
		show_page(voffset, pagemap_swap_offset(pme), flags, 0, 0);

	nr_pages[hash_slot(flags)]++;
	total_pages++;
पूर्ण

#घोषणा PAGEMAP_BATCH	(64 << 10)
अटल व्योम walk_vma(अचिन्हित दीर्घ index, अचिन्हित दीर्घ count)
अणु
	uपूर्णांक64_t buf[PAGEMAP_BATCH];
	अचिन्हित दीर्घ batch;
	अचिन्हित दीर्घ pages;
	अचिन्हित दीर्घ pfn;
	अचिन्हित दीर्घ i;

	जबतक (count) अणु
		batch = min_t(अचिन्हित दीर्घ, count, PAGEMAP_BATCH);
		pages = pagemap_पढ़ो(buf, index, batch);
		अगर (pages == 0)
			अवरोध;

		क्रम (i = 0; i < pages; i++) अणु
			pfn = pagemap_pfn(buf[i]);
			अगर (pfn)
				walk_pfn(index + i, pfn, 1, buf[i]);
			अगर (buf[i] & PM_SWAP)
				walk_swap(index + i, buf[i]);
		पूर्ण

		index += pages;
		count -= pages;
	पूर्ण
पूर्ण

अटल व्योम walk_task(अचिन्हित दीर्घ index, अचिन्हित दीर्घ count)
अणु
	स्थिर अचिन्हित दीर्घ end = index + count;
	अचिन्हित दीर्घ start;
	पूर्णांक i = 0;

	जबतक (index < end) अणु

		जबतक (pg_end[i] <= index)
			अगर (++i >= nr_vmas)
				वापस;
		अगर (pg_start[i] >= end)
			वापस;

		start = max_t(अचिन्हित दीर्घ, pg_start[i], index);
		index = min_t(अचिन्हित दीर्घ, pg_end[i], end);

		निश्चित(start < index);
		walk_vma(start, index - start);
	पूर्ण
पूर्ण

अटल व्योम add_addr_range(अचिन्हित दीर्घ offset, अचिन्हित दीर्घ size)
अणु
	अगर (nr_addr_ranges >= MAX_ADDR_RANGES)
		fatal("too many addr ranges\n");

	opt_offset[nr_addr_ranges] = offset;
	opt_size[nr_addr_ranges] = min_t(अचिन्हित दीर्घ, size, अच_दीर्घ_उच्च-offset);
	nr_addr_ranges++;
पूर्ण

अटल व्योम walk_addr_ranges(व्योम)
अणु
	पूर्णांक i;

	kpageflags_fd = checked_खोलो(opt_kpageflags, O_RDONLY);

	अगर (!nr_addr_ranges)
		add_addr_range(0, अच_दीर्घ_उच्च);

	क्रम (i = 0; i < nr_addr_ranges; i++)
		अगर (!opt_pid)
			walk_pfn(opt_offset[i], opt_offset[i], opt_size[i], 0);
		अन्यथा
			walk_task(opt_offset[i], opt_size[i]);

	अगर (opt_mark_idle)
		mark_page_idle(0);

	बंद(kpageflags_fd);
पूर्ण


/*
 * user पूर्णांकerface
 */

अटल स्थिर अक्षर *page_flag_type(uपूर्णांक64_t flag)
अणु
	अगर (flag & KPF_HACKERS_BITS)
		वापस "(r)";
	अगर (flag & KPF_OVERLOADED_BITS)
		वापस "(o)";
	वापस "   ";
पूर्ण

अटल व्योम usage(व्योम)
अणु
	माप_प्रकार i, j;

	म_लिखो(
"page-types [options]\n"
"            -r|--raw                   Raw mode, for kernel developers\n"
"            -d|--describe flags        Describe flags\n"
"            -a|--addr    addr-spec     Walk a range of pages\n"
"            -b|--bits    bits-spec     Walk pages with specified bits\n"
"            -c|--cgroup  path|@inode   Walk pages within memory cgroup\n"
"            -p|--pid     pid           Walk process address space\n"
"            -f|--file    filename      Walk file address space\n"
"            -i|--mark-idle             Mark pages idle\n"
"            -l|--list                  Show page details in ranges\n"
"            -L|--list-each             Show page details one by one\n"
"            -C|--list-cgroup           Show cgroup inode for pages\n"
"            -M|--list-mapcnt           Show page map count\n"
"            -N|--no-summary            Don't show summary info\n"
"            -X|--hwpoison              hwpoison pages\n"
"            -x|--unpoison              unpoison pages\n"
"            -F|--kpageflags filename   kpageflags file to parse\n"
"            -h|--help                  Show this usage message\n"
"flags:\n"
"            0x10                       bitfield format, e.g.\n"
"            anon                       bit-name, e.g.\n"
"            0x10,anon                  comma-separated list, e.g.\n"
"addr-spec:\n"
"            N                          one page at offset N (unit: pages)\n"
"            N+M                        pages range from N to N+M-1\n"
"            N,M                        pages range from N to M-1\n"
"            N,                         pages range from N to end\n"
"            ,M                         pages range from 0 to M-1\n"
"bits-spec:\n"
"            bit1,bit2                  (flags & (bit1|bit2)) != 0\n"
"            bit1,bit2=bit1             (flags & (bit1|bit2)) == bit1\n"
"            bit1,~bit2                 (flags & (bit1|bit2)) == bit1\n"
"            =bit1,bit2                 flags == (bit1|bit2)\n"
"bit-names:\n"
	);

	क्रम (i = 0, j = 0; i < ARRAY_SIZE(page_flag_names); i++) अणु
		अगर (!page_flag_names[i])
			जारी;
		म_लिखो("%16s%s", page_flag_names[i] + 2,
				 page_flag_type(1ULL << i));
		अगर (++j > 3) अणु
			j = 0;
			अक्षर_दो('\n');
		पूर्ण
	पूर्ण
	म_लिखो("\n                                   "
		"(r) raw mode bits  (o) overloaded bits\n");
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ parse_number(स्थिर अक्षर *str)
अणु
	अचिन्हित दीर्घ दीर्घ n;

	n = म_से_दीर्घl(str, शून्य, 0);

	अगर (n == 0 && str[0] != '0')
		fatal("invalid name or number: %s\n", str);

	वापस n;
पूर्ण

अटल व्योम parse_pid(स्थिर अक्षर *str)
अणु
	खाता *file;
	अक्षर buf[5000];

	opt_pid = parse_number(str);

	प्र_लिखो(buf, "/proc/%d/pagemap", opt_pid);
	pagemap_fd = checked_खोलो(buf, O_RDONLY);

	प्र_लिखो(buf, "/proc/%d/maps", opt_pid);
	file = ख_खोलो(buf, "r");
	अगर (!file) अणु
		लिखो_त्रुटि(buf);
		निकास(निकास_त्रुटि);
	पूर्ण

	जबतक (ख_माला_लो(buf, माप(buf), file) != शून्य) अणु
		अचिन्हित दीर्घ vm_start;
		अचिन्हित दीर्घ vm_end;
		अचिन्हित दीर्घ दीर्घ pgoff;
		पूर्णांक major, minor;
		अक्षर r, w, x, s;
		अचिन्हित दीर्घ ino;
		पूर्णांक n;

		n = माला_पूछो(buf, "%lx-%lx %c%c%c%c %llx %x:%x %lu",
			   &vm_start,
			   &vm_end,
			   &r, &w, &x, &s,
			   &pgoff,
			   &major, &minor,
			   &ino);
		अगर (n < 10) अणु
			ख_लिखो(मानक_त्रुटि, "unexpected line: %s\n", buf);
			जारी;
		पूर्ण
		pg_start[nr_vmas] = vm_start / page_size;
		pg_end[nr_vmas] = vm_end / page_size;
		अगर (++nr_vmas >= MAX_VMAS) अणु
			ख_लिखो(मानक_त्रुटि, "too many VMAs\n");
			अवरोध;
		पूर्ण
	पूर्ण
	ख_बंद(file);
पूर्ण

अटल व्योम show_file(स्थिर अक्षर *name, स्थिर काष्ठा stat *st)
अणु
	अचिन्हित दीर्घ दीर्घ size = st->st_size;
	अक्षर aसमय[64], mसमय[64];
	दीर्घ now = समय(शून्य);

	म_लिखो("%s\tInode: %u\tSize: %llu (%llu pages)\n",
			name, (अचिन्हित)st->st_ino,
			size, (size + page_size - 1) / page_size);

	स_माला(aसमय, माप(aसमय), "%c", स_स्थानीय(&st->st_aसमय));
	स_माला(mसमय, माप(mसमय), "%c", स_स्थानीय(&st->st_mसमय));

	म_लिखो("Modify: %s (%ld seconds ago)\nAccess: %s (%ld seconds ago)\n",
			mसमय, now - st->st_mसमय,
			aसमय, now - st->st_aसमय);
पूर्ण

अटल sigलाँघ_बफ sigbus_jmp;

अटल व्योम * अस्थिर sigbus_addr;

अटल व्योम sigbus_handler(पूर्णांक sig, siginfo_t *info, व्योम *ucontex)
अणु
	(व्योम)sig;
	(व्योम)ucontex;
	sigbus_addr = info ? info->si_addr : शून्य;
	sigदीर्घ_लाँघ(sigbus_jmp, 1);
पूर्ण

अटल काष्ठा sigaction sigbus_action = अणु
	.sa_sigaction = sigbus_handler,
	.sa_flags = SA_SIGINFO,
पूर्ण;

अटल व्योम walk_file(स्थिर अक्षर *name, स्थिर काष्ठा stat *st)
अणु
	uपूर्णांक8_t vec[PAGEMAP_BATCH];
	uपूर्णांक64_t buf[PAGEMAP_BATCH], flags;
	uपूर्णांक64_t cgroup = 0;
	uपूर्णांक64_t mapcnt = 0;
	अचिन्हित दीर्घ nr_pages, pfn, i;
	off_t off, end = st->st_size;
	पूर्णांक fd;
	sमाप_प्रकार len;
	व्योम *ptr;
	पूर्णांक first = 1;

	fd = checked_खोलो(name, O_RDONLY|O_NOATIME|O_NOFOLLOW);

	क्रम (off = 0; off < end; off += len) अणु
		nr_pages = (end - off + page_size - 1) / page_size;
		अगर (nr_pages > PAGEMAP_BATCH)
			nr_pages = PAGEMAP_BATCH;
		len = nr_pages * page_size;

		ptr = mmap(शून्य, len, PROT_READ, MAP_SHARED, fd, off);
		अगर (ptr == MAP_FAILED)
			fatal("mmap failed: %s", name);

		/* determine cached pages */
		अगर (mincore(ptr, len, vec))
			fatal("mincore failed: %s", name);

		/* turn off पढ़ोahead */
		अगर (madvise(ptr, len, MADV_RANDOM))
			fatal("madvice failed: %s", name);

		अगर (sigबनाओ_लाँघ(sigbus_jmp, 1)) अणु
			end = off + sigbus_addr ? sigbus_addr - ptr : 0;
			ख_लिखो(मानक_त्रुटि, "got sigbus at offset %lld: %s\n",
					(दीर्घ दीर्घ)end, name);
			जाओ got_sigbus;
		पूर्ण

		/* populate ptes */
		क्रम (i = 0; i < nr_pages ; i++) अणु
			अगर (vec[i] & 1)
				(व्योम)*(अस्थिर पूर्णांक *)(ptr + i * page_size);
		पूर्ण
got_sigbus:

		/* turn off harvesting reference bits */
		अगर (madvise(ptr, len, MADV_SEQUENTIAL))
			fatal("madvice failed: %s", name);

		अगर (pagemap_पढ़ो(buf, (अचिन्हित दीर्घ)ptr / page_size,
					nr_pages) != nr_pages)
			fatal("cannot read pagemap");

		munmap(ptr, len);

		क्रम (i = 0; i < nr_pages; i++) अणु
			pfn = pagemap_pfn(buf[i]);
			अगर (!pfn)
				जारी;
			अगर (!kpageflags_पढ़ो(&flags, pfn, 1))
				जारी;
			अगर (!kpagecgroup_पढ़ो(&cgroup, pfn, 1))
				fatal("kpagecgroup_read failed");
			अगर (!kpagecount_पढ़ो(&mapcnt, pfn, 1))
				fatal("kpagecount_read failed");
			अगर (first && opt_list) अणु
				first = 0;
				flush_page_range();
				show_file(name, st);
			पूर्ण
			add_page(off / page_size + i, pfn,
				 flags, cgroup, mapcnt, buf[i]);
		पूर्ण
	पूर्ण

	बंद(fd);
पूर्ण

पूर्णांक walk_tree(स्थिर अक्षर *name, स्थिर काष्ठा stat *st, पूर्णांक type, काष्ठा FTW *f)
अणु
	(व्योम)f;
	चयन (type) अणु
	हाल FTW_F:
		अगर (S_ISREG(st->st_mode))
			walk_file(name, st);
		अवरोध;
	हाल FTW_DNR:
		ख_लिखो(मानक_त्रुटि, "cannot read dir: %s\n", name);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम walk_page_cache(व्योम)
अणु
	काष्ठा stat st;

	kpageflags_fd = checked_खोलो(opt_kpageflags, O_RDONLY);
	pagemap_fd = checked_खोलो("/proc/self/pagemap", O_RDONLY);
	sigaction(SIGBUS, &sigbus_action, शून्य);

	अगर (stat(opt_file, &st))
		fatal("stat failed: %s\n", opt_file);

	अगर (S_ISREG(st.st_mode)) अणु
		walk_file(opt_file, &st);
	पूर्ण अन्यथा अगर (S_ISसूची(st.st_mode)) अणु
		/* करो not follow symlinks and mountpoपूर्णांकs */
		अगर (nftw(opt_file, walk_tree, 64, FTW_MOUNT | FTW_PHYS) < 0)
			fatal("nftw failed: %s\n", opt_file);
	पूर्ण अन्यथा
		fatal("unhandled file type: %s\n", opt_file);

	बंद(kpageflags_fd);
	बंद(pagemap_fd);
	संकेत(SIGBUS, संक_पूर्व);
पूर्ण

अटल व्योम parse_file(स्थिर अक्षर *name)
अणु
	opt_file = name;
पूर्ण

अटल व्योम parse_cgroup(स्थिर अक्षर *path)
अणु
	अगर (path[0] == '@') अणु
		opt_cgroup = parse_number(path + 1);
		वापस;
	पूर्ण

	काष्ठा stat st;

	अगर (stat(path, &st))
		fatal("stat failed: %s: %m\n", path);

	अगर (!S_ISसूची(st.st_mode))
		fatal("cgroup supposed to be a directory: %s\n", path);

	opt_cgroup = st.st_ino;
पूर्ण

अटल व्योम parse_addr_range(स्थिर अक्षर *optarg)
अणु
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ size;
	अक्षर *p;

	p = म_अक्षर(optarg, ',');
	अगर (!p)
		p = म_अक्षर(optarg, '+');

	अगर (p == optarg) अणु
		offset = 0;
		size   = parse_number(p + 1);
	पूर्ण अन्यथा अगर (p) अणु
		offset = parse_number(optarg);
		अगर (p[1] == '\0')
			size = अच_दीर्घ_उच्च;
		अन्यथा अणु
			size = parse_number(p + 1);
			अगर (*p == ',') अणु
				अगर (size < offset)
					fatal("invalid range: %lu,%lu\n",
							offset, size);
				size -= offset;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		offset = parse_number(optarg);
		size   = 1;
	पूर्ण

	add_addr_range(offset, size);
पूर्ण

अटल व्योम add_bits_filter(uपूर्णांक64_t mask, uपूर्णांक64_t bits)
अणु
	अगर (nr_bit_filters >= MAX_BIT_FILTERS)
		fatal("too much bit filters\n");

	opt_mask[nr_bit_filters] = mask;
	opt_bits[nr_bit_filters] = bits;
	nr_bit_filters++;
पूर्ण

अटल uपूर्णांक64_t parse_flag_name(स्थिर अक्षर *str, पूर्णांक len)
अणु
	माप_प्रकार i;

	अगर (!*str || !len)
		वापस 0;

	अगर (len <= 8 && !म_भेदन(str, "compound", len))
		वापस BITS_COMPOUND;

	क्रम (i = 0; i < ARRAY_SIZE(page_flag_names); i++) अणु
		अगर (!page_flag_names[i])
			जारी;
		अगर (!म_भेदन(str, page_flag_names[i] + 2, len))
			वापस 1ULL << i;
	पूर्ण

	वापस parse_number(str);
पूर्ण

अटल uपूर्णांक64_t parse_flag_names(स्थिर अक्षर *str, पूर्णांक all)
अणु
	स्थिर अक्षर *p    = str;
	uपूर्णांक64_t   flags = 0;

	जबतक (1) अणु
		अगर (*p == ',' || *p == '=' || *p == '\0') अणु
			अगर ((*str != '~') || (*str == '~' && all && *++str))
				flags |= parse_flag_name(str, p - str);
			अगर (*p != ',')
				अवरोध;
			str = p + 1;
		पूर्ण
		p++;
	पूर्ण

	वापस flags;
पूर्ण

अटल व्योम parse_bits_mask(स्थिर अक्षर *optarg)
अणु
	uपूर्णांक64_t mask;
	uपूर्णांक64_t bits;
	स्थिर अक्षर *p;

	p = म_अक्षर(optarg, '=');
	अगर (p == optarg) अणु
		mask = KPF_ALL_BITS;
		bits = parse_flag_names(p + 1, 0);
	पूर्ण अन्यथा अगर (p) अणु
		mask = parse_flag_names(optarg, 0);
		bits = parse_flag_names(p + 1, 0);
	पूर्ण अन्यथा अगर (म_अक्षर(optarg, '~')) अणु
		mask = parse_flag_names(optarg, 1);
		bits = parse_flag_names(optarg, 0);
	पूर्ण अन्यथा अणु
		mask = parse_flag_names(optarg, 0);
		bits = KPF_ALL_BITS;
	पूर्ण

	add_bits_filter(mask, bits);
पूर्ण

अटल व्योम parse_kpageflags(स्थिर अक्षर *name)
अणु
	opt_kpageflags = name;
पूर्ण

अटल व्योम describe_flags(स्थिर अक्षर *optarg)
अणु
	uपूर्णांक64_t flags = parse_flag_names(optarg, 0);

	म_लिखो("0x%016llx\t%s\t%s\n",
		(अचिन्हित दीर्घ दीर्घ)flags,
		page_flag_name(flags),
		page_flag_दीर्घname(flags));
पूर्ण

अटल स्थिर काष्ठा option opts[] = अणु
	अणु "raw"       , 0, शून्य, 'r' पूर्ण,
	अणु "pid"       , 1, शून्य, 'p' पूर्ण,
	अणु "file"      , 1, शून्य, 'f' पूर्ण,
	अणु "addr"      , 1, शून्य, 'a' पूर्ण,
	अणु "bits"      , 1, शून्य, 'b' पूर्ण,
	अणु "cgroup"    , 1, शून्य, 'c' पूर्ण,
	अणु "describe"  , 1, शून्य, 'd' पूर्ण,
	अणु "mark-idle" , 0, शून्य, 'i' पूर्ण,
	अणु "list"      , 0, शून्य, 'l' पूर्ण,
	अणु "list-each" , 0, शून्य, 'L' पूर्ण,
	अणु "list-cgroup", 0, शून्य, 'C' पूर्ण,
	अणु "list-mapcnt", 0, शून्य, 'M' पूर्ण,
	अणु "no-summary", 0, शून्य, 'N' पूर्ण,
	अणु "hwpoison"  , 0, शून्य, 'X' पूर्ण,
	अणु "unpoison"  , 0, शून्य, 'x' पूर्ण,
	अणु "kpageflags", 0, शून्य, 'F' पूर्ण,
	अणु "help"      , 0, शून्य, 'h' पूर्ण,
	अणु शून्य        , 0, शून्य, 0 पूर्ण
पूर्ण;

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक c;

	page_size = getpagesize();

	जबतक ((c = getopt_दीर्घ(argc, argv,
				"rp:f:a:b:d:c:CilLMNXxF:h",
				opts, शून्य)) != -1) अणु
		चयन (c) अणु
		हाल 'r':
			opt_raw = 1;
			अवरोध;
		हाल 'p':
			parse_pid(optarg);
			अवरोध;
		हाल 'f':
			parse_file(optarg);
			अवरोध;
		हाल 'a':
			parse_addr_range(optarg);
			अवरोध;
		हाल 'b':
			parse_bits_mask(optarg);
			अवरोध;
		हाल 'c':
			parse_cgroup(optarg);
			अवरोध;
		हाल 'C':
			opt_list_cgroup = 1;
			अवरोध;
		हाल 'd':
			describe_flags(optarg);
			निकास(0);
		हाल 'i':
			opt_mark_idle = 1;
			अवरोध;
		हाल 'l':
			opt_list = 1;
			अवरोध;
		हाल 'L':
			opt_list = 2;
			अवरोध;
		हाल 'M':
			opt_list_mapcnt = 1;
			अवरोध;
		हाल 'N':
			opt_no_summary = 1;
			अवरोध;
		हाल 'X':
			opt_hwpoison = 1;
			prepare_hwpoison_fd();
			अवरोध;
		हाल 'x':
			opt_unpoison = 1;
			prepare_hwpoison_fd();
			अवरोध;
		हाल 'F':
			parse_kpageflags(optarg);
			अवरोध;
		हाल 'h':
			usage();
			निकास(0);
		शेष:
			usage();
			निकास(1);
		पूर्ण
	पूर्ण

	अगर (!opt_kpageflags)
		opt_kpageflags = PROC_KPAGEFLAGS;

	अगर (opt_cgroup || opt_list_cgroup)
		kpagecgroup_fd = checked_खोलो(PROC_KPAGECGROUP, O_RDONLY);

	अगर (opt_list && opt_list_mapcnt)
		kpagecount_fd = checked_खोलो(PROC_KPAGECOUNT, O_RDONLY);

	अगर (opt_mark_idle && opt_file)
		page_idle_fd = checked_खोलो(SYS_KERNEL_MM_PAGE_IDLE, O_RDWR);

	अगर (opt_list && opt_pid)
		म_लिखो("voffset\t");
	अगर (opt_list && opt_file)
		म_लिखो("foffset\t");
	अगर (opt_list && opt_list_cgroup)
		म_लिखो("cgroup\t");
	अगर (opt_list && opt_list_mapcnt)
		म_लिखो("map-cnt\t");

	अगर (opt_list == 1)
		म_लिखो("offset\tlen\tflags\n");
	अगर (opt_list == 2)
		म_लिखो("offset\tflags\n");

	अगर (opt_file)
		walk_page_cache();
	अन्यथा
		walk_addr_ranges();

	अगर (opt_list == 1)
		flush_page_range();

	अगर (opt_no_summary)
		वापस 0;

	अगर (opt_list)
		म_लिखो("\n\n");

	show_summary();

	अगर (opt_list_mapcnt)
		बंद(kpagecount_fd);

	अगर (page_idle_fd >= 0)
		बंद(page_idle_fd);

	वापस 0;
पूर्ण
