<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
**  linux/amiga/chipram.c
**
**      Modअगरied 03-May-94 by Geert Uytterhoeven <geert@linux-m68k.org>
**          - 64-bit aligned allocations क्रम full AGA compatibility
**
**	Rewritten 15/9/2000 by Geert to use resource management
*/

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/module.h>

#समावेश <यंत्र/atomic.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/amigahw.h>

अचिन्हित दीर्घ amiga_chip_size;
EXPORT_SYMBOL(amiga_chip_size);

अटल काष्ठा resource chipram_res = अणु
	.name = "Chip RAM", .start = CHIP_PHYSADDR
पूर्ण;
अटल atomic_t chipavail;


व्योम __init amiga_chip_init(व्योम)
अणु
	अगर (!AMIGAHW_PRESENT(CHIP_RAM))
		वापस;

	chipram_res.end = CHIP_PHYSADDR + amiga_chip_size - 1;
	request_resource(&iomem_resource, &chipram_res);

	atomic_set(&chipavail, amiga_chip_size);
पूर्ण


व्योम *amiga_chip_alloc(अचिन्हित दीर्घ size, स्थिर अक्षर *name)
अणु
	काष्ठा resource *res;
	व्योम *p;

	res = kzalloc(माप(काष्ठा resource), GFP_KERNEL);
	अगर (!res)
		वापस शून्य;

	res->name = name;
	p = amiga_chip_alloc_res(size, res);
	अगर (!p) अणु
		kमुक्त(res);
		वापस शून्य;
	पूर्ण

	वापस p;
पूर्ण
EXPORT_SYMBOL(amiga_chip_alloc);


	/*
	 *  Warning:
	 *  amiga_chip_alloc_res is meant only क्रम drivers that need to
	 *  allocate Chip RAM beक्रमe kदो_स्मृति() is functional. As a consequence,
	 *  those drivers must not मुक्त that Chip RAM afterwards.
	 */

व्योम *amiga_chip_alloc_res(अचिन्हित दीर्घ size, काष्ठा resource *res)
अणु
	पूर्णांक error;

	/* round up */
	size = PAGE_ALIGN(size);

	pr_debug("amiga_chip_alloc_res: allocate %lu bytes\n", size);
	error = allocate_resource(&chipram_res, res, size, 0, अच_पूर्णांक_उच्च,
				  PAGE_SIZE, शून्य, शून्य);
	अगर (error < 0) अणु
		pr_err("amiga_chip_alloc_res: allocate_resource() failed %d!\n",
		       error);
		वापस शून्य;
	पूर्ण

	atomic_sub(size, &chipavail);
	pr_debug("amiga_chip_alloc_res: returning %pR\n", res);
	वापस ZTWO_VADDR(res->start);
पूर्ण

व्योम amiga_chip_मुक्त(व्योम *ptr)
अणु
	अचिन्हित दीर्घ start = ZTWO_PADDR(ptr);
	काष्ठा resource *res;
	अचिन्हित दीर्घ size;

	res = lookup_resource(&chipram_res, start);
	अगर (!res) अणु
		pr_err("amiga_chip_free: trying to free nonexistent region at "
		       "%p\n", ptr);
		वापस;
	पूर्ण

	size = resource_size(res);
	pr_debug("amiga_chip_free: free %lu bytes at %p\n", size, ptr);
	atomic_add(size, &chipavail);
	release_resource(res);
	kमुक्त(res);
पूर्ण
EXPORT_SYMBOL(amiga_chip_मुक्त);


अचिन्हित दीर्घ amiga_chip_avail(व्योम)
अणु
	अचिन्हित दीर्घ n = atomic_पढ़ो(&chipavail);

	pr_debug("amiga_chip_avail : %lu bytes\n", n);
	वापस n;
पूर्ण
EXPORT_SYMBOL(amiga_chip_avail);

