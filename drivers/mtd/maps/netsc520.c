<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* netsc520.c -- MTD map driver क्रम AMD NetSc520 Demonstration Board
 *
 * Copyright (C) 2001 Mark Langsकरोrf (mark.langsकरोrf@amd.com)
 *	based on sc520cdp.c by Sysgo Real-Time Solutions GmbH
 *
 * The NetSc520 is a demonstration board क्रम the Elan Sc520 processor available
 * from AMD.  It has a single back of 16 megs of 32-bit Flash ROM and another
 * 16 megs of SDRAM.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/partitions.h>


/*
** The single, 16 megabyte flash bank is भागided पूर्णांकo four भव
** partitions.  The first partition is 768 KiB and is पूर्णांकended to
** store the kernel image loaded by the bootstrap loader.  The second
** partition is 256 KiB and holds the BIOS image.  The third
** partition is 14.5 MiB and is पूर्णांकended क्रम the flash file प्रणाली
** image.  The last partition is 512 KiB and contains another copy
** of the BIOS image and the reset vector.
**
** Only the third partition should be mounted.  The first partition
** should not be mounted, but it can erased and written to using the
** MTD अक्षरacter routines.  The second and fourth partitions should
** not be touched - it is possible to corrupt the BIOS image by
** mounting these partitions, and potentially the board will not be
** recoverable afterwards.
*/

/* partition_info gives details on the logical partitions that the split the
 * single flash device पूर्णांकo. If the size अगर zero we use up to the end of the
 * device. */
अटल स्थिर काष्ठा mtd_partition partition_info[] = अणु
    अणु
	    .name = "NetSc520 boot kernel",
	    .offset = 0,
	    .size = 0xc0000
    पूर्ण,
    अणु
	    .name = "NetSc520 Low BIOS",
	    .offset = 0xc0000,
	    .size = 0x40000
    पूर्ण,
    अणु
	    .name = "NetSc520 file system",
	    .offset = 0x100000,
	    .size = 0xe80000
    पूर्ण,
    अणु
	    .name = "NetSc520 High BIOS",
	    .offset = 0xf80000,
	    .size = 0x80000
    पूर्ण,
पूर्ण;
#घोषणा NUM_PARTITIONS ARRAY_SIZE(partition_info)

#घोषणा WINDOW_SIZE	0x00100000
#घोषणा WINDOW_ADDR	0x00200000

अटल काष्ठा map_info netsc520_map = अणु
	.name = "netsc520 Flash Bank",
	.size = WINDOW_SIZE,
	.bankwidth = 4,
	.phys = WINDOW_ADDR,
पूर्ण;

#घोषणा NUM_FLASH_BANKS	ARRAY_SIZE(netsc520_map)

अटल काष्ठा mtd_info *mymtd;

अटल पूर्णांक __init init_netsc520(व्योम)
अणु
	prपूर्णांकk(KERN_NOTICE "NetSc520 flash device: 0x%Lx at 0x%Lx\n",
			(अचिन्हित दीर्घ दीर्घ)netsc520_map.size,
			(अचिन्हित दीर्घ दीर्घ)netsc520_map.phys);
	netsc520_map.virt = ioremap(netsc520_map.phys, netsc520_map.size);

	अगर (!netsc520_map.virt) अणु
		prपूर्णांकk("Failed to ioremap\n");
		वापस -EIO;
	पूर्ण

	simple_map_init(&netsc520_map);

	mymtd = करो_map_probe("cfi_probe", &netsc520_map);
	अगर(!mymtd)
		mymtd = करो_map_probe("map_ram", &netsc520_map);
	अगर(!mymtd)
		mymtd = करो_map_probe("map_rom", &netsc520_map);

	अगर (!mymtd) अणु
		iounmap(netsc520_map.virt);
		वापस -ENXIO;
	पूर्ण

	mymtd->owner = THIS_MODULE;
	mtd_device_रेजिस्टर(mymtd, partition_info, NUM_PARTITIONS);
	वापस 0;
पूर्ण

अटल व्योम __निकास cleanup_netsc520(व्योम)
अणु
	अगर (mymtd) अणु
		mtd_device_unरेजिस्टर(mymtd);
		map_destroy(mymtd);
	पूर्ण
	अगर (netsc520_map.virt) अणु
		iounmap(netsc520_map.virt);
		netsc520_map.virt = शून्य;
	पूर्ण
पूर्ण

module_init(init_netsc520);
module_निकास(cleanup_netsc520);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mark Langsdorf <mark.langsdorf@amd.com>");
MODULE_DESCRIPTION("MTD map driver for AMD NetSc520 Demonstration Board");
