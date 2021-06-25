<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/export.h>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>
#समावेश <linux/sizes.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/page.h>
#अगर_घोषित CONFIG_MIPS
#समावेश <यंत्र/bootinfo.h>
#पूर्ण_अगर

काष्ठा foo अणु
	अचिन्हित पूर्णांक bar;
पूर्ण;

अटल काष्ठा foo *foo;

अटल पूर्णांक __init test_debug_भव_init(व्योम)
अणु
	phys_addr_t pa;
	व्योम *va;

	va = (व्योम *)VMALLOC_START;
	pa = virt_to_phys(va);

	pr_info("PA: %pa for VA: 0x%lx\n", &pa, (अचिन्हित दीर्घ)va);

	foo = kzalloc(माप(*foo), GFP_KERNEL);
	अगर (!foo)
		वापस -ENOMEM;

	pa = virt_to_phys(foo);
	va = foo;
	pr_info("PA: %pa for VA: 0x%lx\n", &pa, (अचिन्हित दीर्घ)va);

	वापस 0;
पूर्ण
module_init(test_debug_भव_init);

अटल व्योम __निकास test_debug_भव_निकास(व्योम)
अणु
	kमुक्त(foo);
पूर्ण
module_निकास(test_debug_भव_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Test module for CONFIG_DEBUG_VIRTUAL");
