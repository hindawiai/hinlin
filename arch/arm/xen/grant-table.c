<शैली गुरु>
/******************************************************************************
 * grant_table.c
 * ARM specअगरic part
 *
 * Granting क्रमeign access to our memory reservation.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation; or, when distributed
 * separately from the Linux kernel or incorporated पूर्णांकo other
 * software packages, subject to the following license:
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this source file (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modअगरy,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#समावेश <xen/पूर्णांकerface/xen.h>
#समावेश <xen/page.h>
#समावेश <xen/grant_table.h>

पूर्णांक arch_gnttab_map_shared(xen_pfn_t *frames, अचिन्हित दीर्घ nr_gframes,
			   अचिन्हित दीर्घ max_nr_gframes,
			   व्योम **__shared)
अणु
	वापस -ENOSYS;
पूर्ण

व्योम arch_gnttab_unmap(व्योम *shared, अचिन्हित दीर्घ nr_gframes)
अणु
	वापस;
पूर्ण

पूर्णांक arch_gnttab_map_status(uपूर्णांक64_t *frames, अचिन्हित दीर्घ nr_gframes,
			   अचिन्हित दीर्घ max_nr_gframes,
			   grant_status_t **__shared)
अणु
	वापस -ENOSYS;
पूर्ण

पूर्णांक arch_gnttab_init(अचिन्हित दीर्घ nr_shared, अचिन्हित दीर्घ nr_status)
अणु
	वापस 0;
पूर्ण
