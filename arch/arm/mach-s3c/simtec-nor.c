<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2008 Simtec Electronics
//	http://armlinux.simtec.co.uk/
//	Ben Dooks <ben@simtec.co.uk>
//
// Simtec NOR mapping

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/mtd/partitions.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश "map.h"

#समावेश "bast.h"
#समावेश "simtec.h"

अटल व्योम simtec_nor_vpp(काष्ठा platक्रमm_device *pdev, पूर्णांक vpp)
अणु
	अचिन्हित पूर्णांक val;

	val = __raw_पढ़ोb(BAST_VA_CTRL3);

	prपूर्णांकk(KERN_DEBUG "%s(%d)\n", __func__, vpp);

	अगर (vpp)
		val |= BAST_CPLD_CTRL3_ROMWEN;
	अन्यथा
		val &= ~BAST_CPLD_CTRL3_ROMWEN;

	__raw_ग_लिखोb(val, BAST_VA_CTRL3);
पूर्ण

अटल काष्ठा physmap_flash_data simtec_nor_pdata = अणु
	.width		= 2,
	.set_vpp	= simtec_nor_vpp,
	.nr_parts	= 0,
पूर्ण;

अटल काष्ठा resource simtec_nor_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C2410_CS1 + 0x4000000, SZ_8M),
पूर्ण;

अटल काष्ठा platक्रमm_device simtec_device_nor = अणु
	.name		= "physmap-flash",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(simtec_nor_resource),
	.resource	= simtec_nor_resource,
	.dev		= अणु
		.platक्रमm_data = &simtec_nor_pdata,
	पूर्ण,
पूर्ण;

व्योम __init nor_simtec_init(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_device_रेजिस्टर(&simtec_device_nor);
	अगर (ret < 0)
		prपूर्णांकk(KERN_ERR "failed to register physmap-flash device\n");
	अन्यथा
		simtec_nor_vpp(शून्य, 1);
पूर्ण
