<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Handle mapping of the NOR flash on implementa A7 boards
 *
 * Copyright 2002 SYSGO Real-Time Solutions GmbH
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/partitions.h>

#घोषणा WINDOW_ADDR0 0x00000000      /* physical properties of flash */
#घोषणा WINDOW_SIZE0 0x00800000
#घोषणा WINDOW_ADDR1 0x10000000      /* physical properties of flash */
#घोषणा WINDOW_SIZE1 0x00800000
#घोषणा NUM_FLASHBANKS 2
#घोषणा BUSWIDTH     4

#घोषणा MSG_PREFIX "impA7:"   /* prefix क्रम our prपूर्णांकk()'s */
#घोषणा MTDID      "impa7-%d"  /* क्रम mtdparts= partitioning */

अटल काष्ठा mtd_info *impa7_mtd[NUM_FLASHBANKS];

अटल स्थिर अक्षर * स्थिर rom_probe_types[] = अणु "jedec_probe", शून्य पूर्ण;

अटल काष्ठा map_info impa7_map[NUM_FLASHBANKS] = अणु
	अणु
		.name = "impA7 NOR Flash Bank #0",
		.size = WINDOW_SIZE0,
		.bankwidth = BUSWIDTH,
	पूर्ण,
	अणु
		.name = "impA7 NOR Flash Bank #1",
		.size = WINDOW_SIZE1,
		.bankwidth = BUSWIDTH,
	पूर्ण,
पूर्ण;

/*
 * MTD partitioning stuff
 */
अटल स्थिर काष्ठा mtd_partition partitions[] =
अणु
	अणु
		.name = "FileSystem",
		.size = 0x800000,
		.offset = 0x00000000
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init init_impa7(व्योम)
अणु
	स्थिर अक्षर * स्थिर *type;
	पूर्णांक i;
	अटल काष्ठा अणु u_दीर्घ addr; u_दीर्घ size; पूर्ण pt[NUM_FLASHBANKS] = अणु
	  अणु WINDOW_ADDR0, WINDOW_SIZE0 पूर्ण,
	  अणु WINDOW_ADDR1, WINDOW_SIZE1 पूर्ण,
        पूर्ण;
	पूर्णांक devicesfound = 0;

	क्रम(i=0; i<NUM_FLASHBANKS; i++)
	अणु
		prपूर्णांकk(KERN_NOTICE MSG_PREFIX "probing 0x%08lx at 0x%08lx\n",
		       pt[i].size, pt[i].addr);

		impa7_map[i].phys = pt[i].addr;
		impa7_map[i].virt = ioremap(pt[i].addr, pt[i].size);
		अगर (!impa7_map[i].virt) अणु
			prपूर्णांकk(MSG_PREFIX "failed to ioremap\n");
			वापस -EIO;
		पूर्ण
		simple_map_init(&impa7_map[i]);

		impa7_mtd[i] = शून्य;
		type = rom_probe_types;
		क्रम(; !impa7_mtd[i] && *type; type++) अणु
			impa7_mtd[i] = करो_map_probe(*type, &impa7_map[i]);
		पूर्ण

		अगर (impa7_mtd[i]) अणु
			impa7_mtd[i]->owner = THIS_MODULE;
			devicesfound++;
			mtd_device_रेजिस्टर(impa7_mtd[i], partitions,
					    ARRAY_SIZE(partitions));
		पूर्ण अन्यथा अणु
			iounmap((व्योम __iomem *)impa7_map[i].virt);
		पूर्ण
	पूर्ण
	वापस devicesfound == 0 ? -ENXIO : 0;
पूर्ण

अटल व्योम __निकास cleanup_impa7(व्योम)
अणु
	पूर्णांक i;
	क्रम (i=0; i<NUM_FLASHBANKS; i++) अणु
		अगर (impa7_mtd[i]) अणु
			mtd_device_unरेजिस्टर(impa7_mtd[i]);
			map_destroy(impa7_mtd[i]);
			iounmap((व्योम __iomem *)impa7_map[i].virt);
			impa7_map[i].virt = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

module_init(init_impa7);
module_निकास(cleanup_impa7);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pavel Bartusek <pba@sysgo.de>");
MODULE_DESCRIPTION("MTD map driver for implementa impA7");
