<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <पूर्णांकtypes.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश "debug.h"
#समावेश "symbol.h"

/* On arm64, kernel text segment starts at high memory address,
 * क्रम example 0xffff 0000 8xxx xxxx. Modules start at a low memory
 * address, like 0xffff 0000 00ax xxxx. When only small amount of
 * memory is used by modules, gap between end of module's text segment
 * and start of kernel text segment may reach 2G.
 * Thereक्रमe करो not fill this gap and करो not assign it to the kernel dso map.
 */

#घोषणा SYMBOL_LIMIT (1 << 12) /* 4K */

व्योम arch__symbols__fixup_end(काष्ठा symbol *p, काष्ठा symbol *c)
अणु
	अगर ((म_अक्षर(p->name, '[') && strchr(c->name, '[') == शून्य) ||
			(म_अक्षर(p->name, '[') == NULL && strchr(c->name, '[')))
		/* Limit range of last symbol in module and kernel */
		p->end += SYMBOL_LIMIT;
	अन्यथा
		p->end = c->start;
	pr_debug4("%s sym:%s end:%#" PRIx64 "\n", __func__, p->name, p->end);
पूर्ण
