<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Common code to handle असलent "placeholder" devices
 * Copyright 2001 Resilience Corporation <ebrower@resilience.com>
 *
 * This map driver is used to allocate "placeholder" MTD
 * devices on प्रणालीs that have socketed/removable media.
 * Use of this driver as a fallback preserves the expected
 * registration of MTD device nodes regardless of probe outcome.
 * A usage example is as follows:
 *
 *		my_dev[i] = करो_map_probe("cfi", &my_map[i]);
 *		अगर(शून्य == my_dev[i]) अणु
 *			my_dev[i] = करो_map_probe("map_absent", &my_map[i]);
 *		पूर्ण
 *
 * Any device 'probed' with this driver will वापस -ENODEV
 * upon खोलो.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>

अटल पूर्णांक map_असलent_पढ़ो (काष्ठा mtd_info *, loff_t, माप_प्रकार, माप_प्रकार *, u_अक्षर *);
अटल पूर्णांक map_असलent_ग_लिखो (काष्ठा mtd_info *, loff_t, माप_प्रकार, माप_प्रकार *, स्थिर u_अक्षर *);
अटल पूर्णांक map_असलent_erase (काष्ठा mtd_info *, काष्ठा erase_info *);
अटल व्योम map_असलent_sync (काष्ठा mtd_info *);
अटल काष्ठा mtd_info *map_असलent_probe(काष्ठा map_info *map);
अटल व्योम map_असलent_destroy (काष्ठा mtd_info *);


अटल काष्ठा mtd_chip_driver map_असलent_chipdrv = अणु
	.probe		= map_असलent_probe,
	.destroy	= map_असलent_destroy,
	.name		= "map_absent",
	.module		= THIS_MODULE
पूर्ण;

अटल काष्ठा mtd_info *map_असलent_probe(काष्ठा map_info *map)
अणु
	काष्ठा mtd_info *mtd;

	mtd = kzalloc(माप(*mtd), GFP_KERNEL);
	अगर (!mtd) अणु
		वापस शून्य;
	पूर्ण

	map->fldrv 	= &map_असलent_chipdrv;
	mtd->priv 	= map;
	mtd->name 	= map->name;
	mtd->type 	= MTD_ABSENT;
	mtd->size 	= map->size;
	mtd->_erase 	= map_असलent_erase;
	mtd->_पढ़ो 	= map_असलent_पढ़ो;
	mtd->_ग_लिखो 	= map_असलent_ग_लिखो;
	mtd->_sync 	= map_असलent_sync;
	mtd->flags 	= 0;
	mtd->erasesize  = PAGE_SIZE;
	mtd->ग_लिखोsize  = 1;

	__module_get(THIS_MODULE);
	वापस mtd;
पूर्ण


अटल पूर्णांक map_असलent_पढ़ो(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len, माप_प्रकार *retlen, u_अक्षर *buf)
अणु
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक map_असलent_ग_लिखो(काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len, माप_प्रकार *retlen, स्थिर u_अक्षर *buf)
अणु
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक map_असलent_erase(काष्ठा mtd_info *mtd, काष्ठा erase_info *instr)
अणु
	वापस -ENODEV;
पूर्ण

अटल व्योम map_असलent_sync(काष्ठा mtd_info *mtd)
अणु
	/* nop */
पूर्ण

अटल व्योम map_असलent_destroy(काष्ठा mtd_info *mtd)
अणु
	/* nop */
पूर्ण

अटल पूर्णांक __init map_असलent_init(व्योम)
अणु
	रेजिस्टर_mtd_chip_driver(&map_असलent_chipdrv);
	वापस 0;
पूर्ण

अटल व्योम __निकास map_असलent_निकास(व्योम)
अणु
	unरेजिस्टर_mtd_chip_driver(&map_असलent_chipdrv);
पूर्ण

module_init(map_असलent_init);
module_निकास(map_असलent_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Resilience Corporation - Eric Brower <ebrower@resilience.com>");
MODULE_DESCRIPTION("Placeholder MTD chip driver for 'absent' chips");
