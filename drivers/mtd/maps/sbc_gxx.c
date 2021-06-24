<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* sbc_gxx.c -- MTD map driver क्रम Arcom Control Systems SBC-MediaGX,
                SBC-GXm and SBC-GX1 series boards.

   Copyright (C) 2001 Arcom Control System Ltd


The SBC-MediaGX / SBC-GXx has up to 16 MiB of
Intel StrataFlash (28F320/28F640) in x8 mode.

This driver uses the CFI probe and Intel Extended Command Set drivers.

The flash is accessed as follows:

   16 KiB memory winकरोw at 0xdc000-0xdffff

   Two IO address locations क्रम paging

   0x258
       bit 0-7: address bit 14-21
   0x259
       bit 0-1: address bit 22-23
       bit 7:   0 - reset/घातered करोwn
                1 - device enabled

The single flash device is भागided पूर्णांकo 3 partition which appear as
separate MTD devices.

25/04/2001 AJL (Arcom)  Modअगरied signon strings and partition sizes
                        (to support bzImages up to 638KiB-ish)
*/

// Includes

#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <यंत्र/पन.स>

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/partitions.h>

// Defines

// - Hardware specअगरic

#घोषणा WINDOW_START 0xdc000

/* Number of bits in offset. */
#घोषणा WINDOW_SHIFT 14
#घोषणा WINDOW_LENGTH (1 << WINDOW_SHIFT)

/* The bits क्रम the offset पूर्णांकo the winकरोw. */
#घोषणा WINDOW_MASK (WINDOW_LENGTH-1)
#घोषणा PAGE_IO 0x258
#घोषणा PAGE_IO_SIZE 2

/* bit 7 of 0x259 must be 1 to enable device. */
#घोषणा DEVICE_ENABLE 0x8000

// - Flash / Partition sizing

#घोषणा MAX_SIZE_KiB             16384
#घोषणा BOOT_PARTITION_SIZE_KiB  768
#घोषणा DATA_PARTITION_SIZE_KiB  1280
#घोषणा APP_PARTITION_SIZE_KiB   6144

// Globals

अटल अस्थिर पूर्णांक page_in_winकरोw = -1; // Current page in winकरोw.
अटल व्योम __iomem *iomapadr;
अटल DEFINE_SPINLOCK(sbc_gxx_spin);

/* partition_info gives details on the logical partitions that the split the
 * single flash device पूर्णांकo. If the size अगर zero we use up to the end of the
 * device. */
अटल स्थिर काष्ठा mtd_partition partition_info[] = अणु
    अणु .name = "SBC-GXx flash boot partition",
      .offset = 0,
      .size =   BOOT_PARTITION_SIZE_KiB*1024 पूर्ण,
    अणु .name = "SBC-GXx flash data partition",
      .offset = BOOT_PARTITION_SIZE_KiB*1024,
      .size = (DATA_PARTITION_SIZE_KiB)*1024 पूर्ण,
    अणु .name = "SBC-GXx flash application partition",
      .offset = (BOOT_PARTITION_SIZE_KiB+DATA_PARTITION_SIZE_KiB)*1024 पूर्ण
पूर्ण;

#घोषणा NUM_PARTITIONS 3

अटल अंतरभूत व्योम sbc_gxx_page(काष्ठा map_info *map, अचिन्हित दीर्घ ofs)
अणु
	अचिन्हित दीर्घ page = ofs >> WINDOW_SHIFT;

	अगर( page!=page_in_winकरोw ) अणु
		outw( page | DEVICE_ENABLE, PAGE_IO );
		page_in_winकरोw = page;
	पूर्ण
पूर्ण


अटल map_word sbc_gxx_पढ़ो8(काष्ठा map_info *map, अचिन्हित दीर्घ ofs)
अणु
	map_word ret;
	spin_lock(&sbc_gxx_spin);
	sbc_gxx_page(map, ofs);
	ret.x[0] = पढ़ोb(iomapadr + (ofs & WINDOW_MASK));
	spin_unlock(&sbc_gxx_spin);
	वापस ret;
पूर्ण

अटल व्योम sbc_gxx_copy_from(काष्ठा map_info *map, व्योम *to, अचिन्हित दीर्घ from, sमाप_प्रकार len)
अणु
	जबतक(len) अणु
		अचिन्हित दीर्घ thislen = len;
		अगर (len > (WINDOW_LENGTH - (from & WINDOW_MASK)))
			thislen = WINDOW_LENGTH-(from & WINDOW_MASK);

		spin_lock(&sbc_gxx_spin);
		sbc_gxx_page(map, from);
		स_नकल_fromio(to, iomapadr + (from & WINDOW_MASK), thislen);
		spin_unlock(&sbc_gxx_spin);
		to += thislen;
		from += thislen;
		len -= thislen;
	पूर्ण
पूर्ण

अटल व्योम sbc_gxx_ग_लिखो8(काष्ठा map_info *map, map_word d, अचिन्हित दीर्घ adr)
अणु
	spin_lock(&sbc_gxx_spin);
	sbc_gxx_page(map, adr);
	ग_लिखोb(d.x[0], iomapadr + (adr & WINDOW_MASK));
	spin_unlock(&sbc_gxx_spin);
पूर्ण

अटल व्योम sbc_gxx_copy_to(काष्ठा map_info *map, अचिन्हित दीर्घ to, स्थिर व्योम *from, sमाप_प्रकार len)
अणु
	जबतक(len) अणु
		अचिन्हित दीर्घ thislen = len;
		अगर (len > (WINDOW_LENGTH - (to & WINDOW_MASK)))
			thislen = WINDOW_LENGTH-(to & WINDOW_MASK);

		spin_lock(&sbc_gxx_spin);
		sbc_gxx_page(map, to);
		स_नकल_toio(iomapadr + (to & WINDOW_MASK), from, thislen);
		spin_unlock(&sbc_gxx_spin);
		to += thislen;
		from += thislen;
		len -= thislen;
	पूर्ण
पूर्ण

अटल काष्ठा map_info sbc_gxx_map = अणु
	.name = "SBC-GXx flash",
	.phys = NO_XIP,
	.size = MAX_SIZE_KiB*1024, /* this must be set to a maximum possible amount
			 of flash so the cfi probe routines find all
			 the chips */
	.bankwidth = 1,
	.पढ़ो = sbc_gxx_पढ़ो8,
	.copy_from = sbc_gxx_copy_from,
	.ग_लिखो = sbc_gxx_ग_लिखो8,
	.copy_to = sbc_gxx_copy_to
पूर्ण;

/* MTD device क्रम all of the flash. */
अटल काष्ठा mtd_info *all_mtd;

अटल व्योम cleanup_sbc_gxx(व्योम)
अणु
	अगर( all_mtd ) अणु
		mtd_device_unरेजिस्टर(all_mtd);
		map_destroy( all_mtd );
	पूर्ण

	iounmap(iomapadr);
	release_region(PAGE_IO,PAGE_IO_SIZE);
पूर्ण

अटल पूर्णांक __init init_sbc_gxx(व्योम)
अणु
  	iomapadr = ioremap(WINDOW_START, WINDOW_LENGTH);
	अगर (!iomapadr) अणु
		prपूर्णांकk( KERN_ERR"%s: failed to ioremap memory region\n",
			sbc_gxx_map.name );
		वापस -EIO;
	पूर्ण

	अगर (!request_region( PAGE_IO, PAGE_IO_SIZE, "SBC-GXx flash")) अणु
		prपूर्णांकk( KERN_ERR"%s: IO ports 0x%x-0x%x in use\n",
			sbc_gxx_map.name,
			PAGE_IO, PAGE_IO+PAGE_IO_SIZE-1 );
		iounmap(iomapadr);
		वापस -EAGAIN;
	पूर्ण


	prपूर्णांकk( KERN_INFO"%s: IO:0x%x-0x%x MEM:0x%x-0x%x\n",
		sbc_gxx_map.name,
		PAGE_IO, PAGE_IO+PAGE_IO_SIZE-1,
		WINDOW_START, WINDOW_START+WINDOW_LENGTH-1 );

	/* Probe क्रम chip. */
	all_mtd = करो_map_probe( "cfi_probe", &sbc_gxx_map );
	अगर( !all_mtd ) अणु
		cleanup_sbc_gxx();
		वापस -ENXIO;
	पूर्ण

	all_mtd->owner = THIS_MODULE;

	/* Create MTD devices क्रम each partition. */
	mtd_device_रेजिस्टर(all_mtd, partition_info, NUM_PARTITIONS);

	वापस 0;
पूर्ण

module_init(init_sbc_gxx);
module_निकास(cleanup_sbc_gxx);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Arcom Control Systems Ltd.");
MODULE_DESCRIPTION("MTD map driver for SBC-GXm and SBC-GX1 series boards");
