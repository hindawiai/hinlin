<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-mmp/common.c
 *
 *  Code common to PXA168 processor lines
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/page.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/प्रणाली_misc.h>
#समावेश "addr-map.h"
#समावेश <linux/soc/mmp/cputype.h>

#समावेश "common.h"

#घोषणा MMP_CHIPID	CIU_REG(0x00)

अचिन्हित पूर्णांक mmp_chip_id;
EXPORT_SYMBOL(mmp_chip_id);

अटल काष्ठा map_desc standard_io_desc[] __initdata = अणु
	अणु
		.pfn		= __phys_to_pfn(APB_PHYS_BASE),
		.भव	= (अचिन्हित दीर्घ)APB_VIRT_BASE,
		.length		= APB_PHYS_SIZE,
		.type		= MT_DEVICE,
	पूर्ण, अणु
		.pfn		= __phys_to_pfn(AXI_PHYS_BASE),
		.भव	= (अचिन्हित दीर्घ)AXI_VIRT_BASE,
		.length		= AXI_PHYS_SIZE,
		.type		= MT_DEVICE,
	पूर्ण,
पूर्ण;

अटल काष्ठा map_desc mmp2_io_desc[] __initdata = अणु
	अणु
		.pfn		= __phys_to_pfn(PGU_PHYS_BASE),
		.भव	= (अचिन्हित दीर्घ)PGU_VIRT_BASE,
		.length		= PGU_PHYS_SIZE,
		.type		= MT_DEVICE,
	पूर्ण,
पूर्ण;

व्योम __init mmp_map_io(व्योम)
अणु
	iotable_init(standard_io_desc, ARRAY_SIZE(standard_io_desc));

	/* this is early, initialize mmp_chip_id here */
	mmp_chip_id = __raw_पढ़ोl(MMP_CHIPID);
पूर्ण

व्योम __init mmp2_map_io(व्योम)
अणु
	mmp_map_io();
	iotable_init(mmp2_io_desc, ARRAY_SIZE(mmp2_io_desc));
पूर्ण

व्योम mmp_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	soft_restart(0);
पूर्ण
