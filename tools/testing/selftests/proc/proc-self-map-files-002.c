<शैली गुरु>
/*
 * Copyright तऊ 2018 Alexey Dobriyan <aकरोbriyan@gmail.com>
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
/* Test पढ़ोlink /proc/self/map_files/... with minimum address. */
#समावेश <त्रुटिसं.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <sys/mman.h>
#समावेश <मानककोष.स>

अटल व्योम pass(स्थिर अक्षर *fmt, अचिन्हित दीर्घ a, अचिन्हित दीर्घ b)
अणु
	अक्षर name[64];
	अक्षर buf[64];

	snम_लिखो(name, माप(name), fmt, a, b);
	अगर (पढ़ोlink(name, buf, माप(buf)) == -1)
		निकास(1);
पूर्ण

अटल व्योम fail(स्थिर अक्षर *fmt, अचिन्हित दीर्घ a, अचिन्हित दीर्घ b)
अणु
	अक्षर name[64];
	अक्षर buf[64];

	snम_लिखो(name, माप(name), fmt, a, b);
	अगर (पढ़ोlink(name, buf, माप(buf)) == -1 && त्रुटि_सं == ENOENT)
		वापस;
	निकास(1);
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	स्थिर पूर्णांक PAGE_SIZE = sysconf(_SC_PAGESIZE);
	/*
	 * va_max must be enough bigger than vm.mmap_min_addr, which is
	 * 64KB/32KB by शेष. (depends on CONFIG_LSM_MMAP_MIN_ADDR)
	 */
	स्थिर अचिन्हित दीर्घ va_max = 1UL << 20;
	अचिन्हित दीर्घ va;
	व्योम *p;
	पूर्णांक fd;
	अचिन्हित दीर्घ a, b;

	fd = खोलो("/dev/zero", O_RDONLY);
	अगर (fd == -1)
		वापस 1;

	क्रम (va = 0; va < va_max; va += PAGE_SIZE) अणु
		p = mmap((व्योम *)va, PAGE_SIZE, PROT_NONE, MAP_PRIVATE|MAP_खाता|MAP_FIXED, fd, 0);
		अगर (p == (व्योम *)va)
			अवरोध;
	पूर्ण
	अगर (va == va_max) अणु
		ख_लिखो(मानक_त्रुटि, "error: mmap doesn't like you\n");
		वापस 1;
	पूर्ण

	a = (अचिन्हित दीर्घ)p;
	b = (अचिन्हित दीर्घ)p + PAGE_SIZE;

	pass("/proc/self/map_files/%lx-%lx", a, b);
	fail("/proc/self/map_files/ %lx-%lx", a, b);
	fail("/proc/self/map_files/%lx -%lx", a, b);
	fail("/proc/self/map_files/%lx- %lx", a, b);
	fail("/proc/self/map_files/%lx-%lx ", a, b);
	fail("/proc/self/map_files/0%lx-%lx", a, b);
	fail("/proc/self/map_files/%lx-0%lx", a, b);
	अगर (माप(दीर्घ) == 4) अणु
		fail("/proc/self/map_files/100000000%lx-%lx", a, b);
		fail("/proc/self/map_files/%lx-100000000%lx", a, b);
	पूर्ण अन्यथा अगर (माप(दीर्घ) == 8) अणु
		fail("/proc/self/map_files/10000000000000000%lx-%lx", a, b);
		fail("/proc/self/map_files/%lx-10000000000000000%lx", a, b);
	पूर्ण अन्यथा
		वापस 1;

	वापस 0;
पूर्ण
