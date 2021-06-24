<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ts5500_flash.c -- MTD map driver क्रम Technology Systems TS-5500 board
 *
 * Copyright (C) 2004 Sean Young <sean@mess.org>
 *
 * Note:
 * - In order क्रम detection to work, jumper 3 must be set.
 * - Drive A and B use the resident flash disk (RFD) flash translation layer.
 * - If you have created your own jffs file प्रणाली and the bios overग_लिखोs
 *   it during boot, try disabling Drive A: and B: in the boot order.
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/types.h>


#घोषणा WINDOW_ADDR	0x09400000
#घोषणा WINDOW_SIZE	0x00200000

अटल काष्ठा map_info ts5500_map = अणु
	.name = "TS-5500 Flash",
	.size = WINDOW_SIZE,
	.bankwidth = 1,
	.phys = WINDOW_ADDR
पूर्ण;

अटल स्थिर काष्ठा mtd_partition ts5500_partitions[] = अणु
	अणु
		.name = "Drive A",
		.offset = 0,
		.size = 0x0e0000
	पूर्ण,
	अणु
		.name = "BIOS",
		.offset = 0x0e0000,
		.size = 0x020000,
	पूर्ण,
	अणु
		.name = "Drive B",
		.offset = 0x100000,
		.size = 0x100000
	पूर्ण
पूर्ण;

#घोषणा NUM_PARTITIONS ARRAY_SIZE(ts5500_partitions)

अटल काष्ठा mtd_info *mymtd;

अटल पूर्णांक __init init_ts5500_map(व्योम)
अणु
	पूर्णांक rc = 0;

	ts5500_map.virt = ioremap(ts5500_map.phys, ts5500_map.size);

	अगर (!ts5500_map.virt) अणु
		prपूर्णांकk(KERN_ERR "Failed to ioremap\n");
		rc = -EIO;
		जाओ err2;
	पूर्ण

	simple_map_init(&ts5500_map);

	mymtd = करो_map_probe("jedec_probe", &ts5500_map);
	अगर (!mymtd)
		mymtd = करो_map_probe("map_rom", &ts5500_map);

	अगर (!mymtd) अणु
		rc = -ENXIO;
		जाओ err1;
	पूर्ण

	mymtd->owner = THIS_MODULE;
	mtd_device_रेजिस्टर(mymtd, ts5500_partitions, NUM_PARTITIONS);

	वापस 0;

err1:
	iounmap(ts5500_map.virt);
err2:
	वापस rc;
पूर्ण

अटल व्योम __निकास cleanup_ts5500_map(व्योम)
अणु
	अगर (mymtd) अणु
		mtd_device_unरेजिस्टर(mymtd);
		map_destroy(mymtd);
	पूर्ण

	अगर (ts5500_map.virt) अणु
		iounmap(ts5500_map.virt);
		ts5500_map.virt = शून्य;
	पूर्ण
पूर्ण

module_init(init_ts5500_map);
module_निकास(cleanup_ts5500_map);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sean Young <sean@mess.org>");
MODULE_DESCRIPTION("MTD map driver for Technology Systems TS-5500 board");

