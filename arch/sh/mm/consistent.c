<शैली गुरु>
/*
 * Copyright (C) 2004 - 2007  Paul Mundt
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>

अटल पूर्णांक __init memchunk_setup(अक्षर *str)
अणु
	वापस 1; /* accept anything that begins with "memchunk." */
पूर्ण
__setup("memchunk.", memchunk_setup);

अटल व्योम __init memchunk_cmdline_override(अक्षर *name, अचिन्हित दीर्घ *sizep)
अणु
	अक्षर *p = boot_command_line;
	पूर्णांक k = म_माप(name);

	जबतक ((p = म_माला(p, "memchunk."))) अणु
		p += 9; /* म_माप("memchunk.") */
		अगर (!म_भेदन(name, p, k) && p[k] == '=') अणु
			p += k + 1;
			*sizep = memparse(p, शून्य);
			pr_info("%s: forcing memory chunk size to 0x%08lx\n",
				name, *sizep);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक __init platक्रमm_resource_setup_memory(काष्ठा platक्रमm_device *pdev,
					  अक्षर *name, अचिन्हित दीर्घ memsize)
अणु
	काष्ठा resource *r;
	dma_addr_t dma_handle;
	व्योम *buf;

	r = pdev->resource + pdev->num_resources - 1;
	अगर (r->flags) अणु
		pr_warn("%s: unable to find empty space for resource\n", name);
		वापस -EINVAL;
	पूर्ण

	memchunk_cmdline_override(name, &memsize);
	अगर (!memsize)
		वापस 0;

	buf = dma_alloc_coherent(&pdev->dev, memsize, &dma_handle, GFP_KERNEL);
	अगर (!buf) अणु
		pr_warn("%s: unable to allocate memory\n", name);
		वापस -ENOMEM;
	पूर्ण

	r->flags = IORESOURCE_MEM;
	r->start = dma_handle;
	r->end = r->start + memsize - 1;
	r->name = name;
	वापस 0;
पूर्ण
