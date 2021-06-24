<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <पूर्णांकtypes.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <पूर्णांकernal/lib.h> // page_size
#समावेश "debug.h"
#समावेश "symbol.h"

/* On घातerpc kernel text segment start at memory addresses, 0xc000000000000000
 * whereas the modules are located at very high memory addresses,
 * क्रम example 0xc00800000xxxxxxx. The gap between end of kernel text segment
 * and beginning of first module's text segment is very high.
 * Thereक्रमe करो not fill this gap and करो not assign it to the kernel dso map.
 */

व्योम arch__symbols__fixup_end(काष्ठा symbol *p, काष्ठा symbol *c)
अणु
	अगर (म_अक्षर(p->name, '[') == NULL && strchr(c->name, '['))
		/* Limit the range of last kernel symbol */
		p->end += page_size;
	अन्यथा
		p->end = c->start;
	pr_debug4("%s sym:%s end:%#" PRIx64 "\n", __func__, p->name, p->end);
पूर्ण
