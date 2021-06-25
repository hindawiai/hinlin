<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE
#घोषणा __EXPORTED_HEADERS__

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <linux/fcntl.h>
#समावेश <linux/memfd.h>
#समावेश <unistd.h>
#समावेश <sys/syscall.h>

#समावेश "common.h"

पूर्णांक hugetlbfs_test = 0;

/*
 * Copied from mlock2-tests.c
 */
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
	ख_बंद(f);
	वापस hps;
पूर्ण

पूर्णांक sys_memfd_create(स्थिर अक्षर *name, अचिन्हित पूर्णांक flags)
अणु
	अगर (hugetlbfs_test)
		flags |= MFD_HUGETLB;

	वापस syscall(__NR_memfd_create, name, flags);
पूर्ण
