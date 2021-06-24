<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <पूर्णांकtypes.h>
#समावेश <unistd.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <पूर्णांकernal/lib.h> // page_size
#समावेश "machine.h"
#समावेश "api/fs/fs.h"
#समावेश "debug.h"
#समावेश "symbol.h"

पूर्णांक arch__fix_module_text_start(u64 *start, u64 *size, स्थिर अक्षर *name)
अणु
	u64 m_start = *start;
	अक्षर path[PATH_MAX];

	snम_लिखो(path, PATH_MAX, "module/%.*s/sections/.text",
				(पूर्णांक)म_माप(name) - 2, name + 1);
	अगर (sysfs__पढ़ो_ull(path, (अचिन्हित दीर्घ दीर्घ *)start) < 0) अणु
		pr_debug2("Using module %s start:%#lx\n", path, m_start);
		*start = m_start;
	पूर्ण अन्यथा अणु
		/* Successful पढ़ो of the modules segment text start address.
		 * Calculate dअगरference between module start address
		 * in memory and module text segment start address.
		 * For example module load address is 0x3ff8011b000
		 * (from /proc/modules) and module text segment start
		 * address is 0x3ff8011b870 (from file above).
		 *
		 * Adjust the module size and subtract the GOT table
		 * size located at the beginning of the module.
		 */
		*size -= (*start - m_start);
	पूर्ण

	वापस 0;
पूर्ण

/* On s390 kernel text segment start is located at very low memory addresses,
 * क्रम example 0x10000. Modules are located at very high memory addresses,
 * क्रम example 0x3ff xxxx xxxx. The gap between end of kernel text segment
 * and beginning of first module's text segment is very big.
 * Thereक्रमe करो not fill this gap and करो not assign it to the kernel dso map.
 */
व्योम arch__symbols__fixup_end(काष्ठा symbol *p, काष्ठा symbol *c)
अणु
	अगर (म_अक्षर(p->name, '[') == NULL && strchr(c->name, '['))
		/* Last kernel symbol mapped to end of page */
		p->end = roundup(p->end, page_size);
	अन्यथा
		p->end = c->start;
	pr_debug4("%s sym:%s end:%#" PRIx64 "\n", __func__, p->name, p->end);
पूर्ण
