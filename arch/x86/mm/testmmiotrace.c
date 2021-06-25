<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Written by Pekka Paalanen, 2008-2009 <pq@iki.fi>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/mmiotrace.h>
#समावेश <linux/security.h>

अटल अचिन्हित दीर्घ mmio_address;
module_param_hw(mmio_address, uदीर्घ, iomem, 0);
MODULE_PARM_DESC(mmio_address, " Start address of the mapping of 16 kB "
				"(or 8 MB if read_far is non-zero).");

अटल अचिन्हित दीर्घ पढ़ो_far = 0x400100;
module_param(पढ़ो_far, uदीर्घ, 0);
MODULE_PARM_DESC(पढ़ो_far, " Offset of a 32-bit read within 8 MB "
				"(default: 0x400100).");

अटल अचिन्हित v16(अचिन्हित i)
अणु
	वापस i * 12 + 7;
पूर्ण

अटल अचिन्हित v32(अचिन्हित i)
अणु
	वापस i * 212371 + 13;
पूर्ण

अटल व्योम करो_ग_लिखो_test(व्योम __iomem *p)
अणु
	अचिन्हित पूर्णांक i;
	pr_info("write test.\n");
	mmiotrace_prपूर्णांकk("Write test.\n");

	क्रम (i = 0; i < 256; i++)
		ioग_लिखो8(i, p + i);

	क्रम (i = 1024; i < (5 * 1024); i += 2)
		ioग_लिखो16(v16(i), p + i);

	क्रम (i = (5 * 1024); i < (16 * 1024); i += 4)
		ioग_लिखो32(v32(i), p + i);
पूर्ण

अटल व्योम करो_पढ़ो_test(व्योम __iomem *p)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित errs[3] = अणु 0 पूर्ण;
	pr_info("read test.\n");
	mmiotrace_prपूर्णांकk("Read test.\n");

	क्रम (i = 0; i < 256; i++)
		अगर (ioपढ़ो8(p + i) != i)
			++errs[0];

	क्रम (i = 1024; i < (5 * 1024); i += 2)
		अगर (ioपढ़ो16(p + i) != v16(i))
			++errs[1];

	क्रम (i = (5 * 1024); i < (16 * 1024); i += 4)
		अगर (ioपढ़ो32(p + i) != v32(i))
			++errs[2];

	mmiotrace_prपूर्णांकk("Read errors: 8-bit %d, 16-bit %d, 32-bit %d.\n",
						errs[0], errs[1], errs[2]);
पूर्ण

अटल व्योम करो_पढ़ो_far_test(व्योम __iomem *p)
अणु
	pr_info("read far test.\n");
	mmiotrace_prपूर्णांकk("Read far test.\n");

	ioपढ़ो32(p + पढ़ो_far);
पूर्ण

अटल व्योम करो_test(अचिन्हित दीर्घ size)
अणु
	व्योम __iomem *p = ioremap(mmio_address, size);
	अगर (!p) अणु
		pr_err("could not ioremap, aborting.\n");
		वापस;
	पूर्ण
	mmiotrace_prपूर्णांकk("ioremap returned %p.\n", p);
	करो_ग_लिखो_test(p);
	करो_पढ़ो_test(p);
	अगर (पढ़ो_far && पढ़ो_far < size - 4)
		करो_पढ़ो_far_test(p);
	iounmap(p);
पूर्ण

/*
 * Tests how mmiotrace behaves in face of multiple ioremap / iounmaps in
 * a लघु समय. We had a bug in deferred मुक्तing procedure which tried
 * to मुक्त this region multiple बार (ioremap can reuse the same address
 * क्रम many mappings).
 */
अटल व्योम करो_test_bulk_ioremapping(व्योम)
अणु
	व्योम __iomem *p;
	पूर्णांक i;

	क्रम (i = 0; i < 10; ++i) अणु
		p = ioremap(mmio_address, PAGE_SIZE);
		अगर (p)
			iounmap(p);
	पूर्ण

	/* Force मुक्तing. If it will crash we will know why. */
	synchronize_rcu();
पूर्ण

अटल पूर्णांक __init init(व्योम)
अणु
	अचिन्हित दीर्घ size = (पढ़ो_far) ? (8 << 20) : (16 << 10);
	पूर्णांक ret = security_locked_करोwn(LOCKDOWN_MMIOTRACE);

	अगर (ret)
		वापस ret;

	अगर (mmio_address == 0) अणु
		pr_err("you have to use the module argument mmio_address.\n");
		pr_err("DO NOT LOAD THIS MODULE UNLESS YOU REALLY KNOW WHAT YOU ARE DOING!\n");
		वापस -ENXIO;
	पूर्ण

	pr_warn("WARNING: mapping %lu kB @ 0x%08lx in PCI address space, "
		"and writing 16 kB of rubbish in there.\n",
		size >> 10, mmio_address);
	करो_test(size);
	करो_test_bulk_ioremapping();
	pr_info("All done.\n");
	वापस 0;
पूर्ण

अटल व्योम __निकास cleanup(व्योम)
अणु
	pr_debug("unloaded.\n");
पूर्ण

module_init(init);
module_निकास(cleanup);
MODULE_LICENSE("GPL");
