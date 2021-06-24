<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "cacheline.h"
#समावेश <unistd.h>

#अगर_घोषित _SC_LEVEL1_DCACHE_LINESIZE
#घोषणा cache_line_size(cacheline_sizep) *cacheline_sizep = sysconf(_SC_LEVEL1_DCACHE_LINESIZE)
#अन्यथा
#समावेश <api/fs/fs.h>
#समावेश "debug.h"
अटल व्योम cache_line_size(पूर्णांक *cacheline_sizep)
अणु
	अगर (sysfs__पढ़ो_पूर्णांक("devices/system/cpu/cpu0/cache/index0/coherency_line_size", cacheline_sizep))
		pr_debug("cannot determine cache line size");
पूर्ण
#पूर्ण_अगर

पूर्णांक cacheline_size(व्योम)
अणु
	अटल पूर्णांक size;

	अगर (!size)
		cache_line_size(&size);

	वापस size;
पूर्ण
