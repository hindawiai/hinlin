<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* sc520cdp.c -- MTD map driver क्रम AMD SC520 Customer Development Platक्रमm
 *
 * Copyright (C) 2001 Sysgo Real-Time Solutions GmbH
 *
 * The SC520CDP is an evaluation board क्रम the Elan SC520 processor available
 * from AMD. It has two banks of 32-bit Flash ROM, each 8 Megabytes in size,
 * and up to 512 KiB of 8-bit DIL Flash ROM.
 * For details see https://www.amd.com/products/epd/desiging/evalboards/18.elansc520/520_cdp_brief/index.hपंचांगl
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/concat.h>

/*
** The Embedded Systems BIOS decodes the first FLASH starting at
** 0x8400000. This is a *terrible* place क्रम it because accessing
** the flash at this location causes the A22 address line to be high
** (that's what 0x8400000 binary's ought to be). But this is the highest
** order address line on the raw flash devices themselves!!
** This causes the top HALF of the flash to be accessed first. Beyond
** the physical limits of the flash, the flash chip aliases over (to
** 0x880000 which causes the bottom half to be accessed. This splits the
** flash पूर्णांकo two and inverts it! If you then try to access this from another
** program that करोes NOT करो this insanity, then you *will* access the
** first half of the flash, but not find what you expect there. That
** stuff is in the *second* half! Similarly, the address used by the
** BIOS क्रम the second FLASH bank is also quite a bad choice.
** If REPROGRAM_PAR is defined below (the शेष), then this driver will
** choose more useful addresses क्रम the FLASH banks by reprogramming the
** responsible PARxx रेजिस्टरs in the SC520's MMCR region. This will
** cause the settings to be incompatible with the BIOS's settings, which
** shouldn't be a problem since you are running Linux, (i.e. the BIOS is
** not much use anyway). However, अगर you need to be compatible with
** the BIOS क्रम some reason, just undefine REPROGRAM_PAR.
*/
#घोषणा REPROGRAM_PAR



#अगर_घोषित REPROGRAM_PAR

/* These are the addresses we want.. */
#घोषणा WINDOW_ADDR_0	0x08800000
#घोषणा WINDOW_ADDR_1	0x09000000
#घोषणा WINDOW_ADDR_2	0x09800000

/* .. and these are the addresses the BIOS gives us */
#घोषणा WINDOW_ADDR_0_BIOS	0x08400000
#घोषणा WINDOW_ADDR_1_BIOS	0x08c00000
#घोषणा WINDOW_ADDR_2_BIOS	0x09400000

#अन्यथा

#घोषणा WINDOW_ADDR_0	0x08400000
#घोषणा WINDOW_ADDR_1	0x08C00000
#घोषणा WINDOW_ADDR_2	0x09400000

#पूर्ण_अगर

#घोषणा WINDOW_SIZE_0	0x00800000
#घोषणा WINDOW_SIZE_1	0x00800000
#घोषणा WINDOW_SIZE_2	0x00080000


अटल काष्ठा map_info sc520cdp_map[] = अणु
	अणु
		.name = "SC520CDP Flash Bank #0",
		.size = WINDOW_SIZE_0,
		.bankwidth = 4,
		.phys = WINDOW_ADDR_0
	पूर्ण,
	अणु
		.name = "SC520CDP Flash Bank #1",
		.size = WINDOW_SIZE_1,
		.bankwidth = 4,
		.phys = WINDOW_ADDR_1
	पूर्ण,
	अणु
		.name = "SC520CDP DIL Flash",
		.size = WINDOW_SIZE_2,
		.bankwidth = 1,
		.phys = WINDOW_ADDR_2
	पूर्ण,
पूर्ण;

#घोषणा NUM_FLASH_BANKS	ARRAY_SIZE(sc520cdp_map)

अटल काष्ठा mtd_info *mymtd[NUM_FLASH_BANKS];
अटल काष्ठा mtd_info *merged_mtd;

#अगर_घोषित REPROGRAM_PAR

/*
** The SC520 MMCR (memory mapped control रेजिस्टर) region resides
** at 0xFFFEF000. The 16 Programmable Address Region (PAR) रेजिस्टरs
** are at offset 0x88 in the MMCR:
*/
#घोषणा SC520_MMCR_BASE		0xFFFEF000
#घोषणा SC520_MMCR_EXTENT	0x1000
#घोषणा SC520_PAR(x)		((0x88/माप(अचिन्हित दीर्घ)) + (x))
#घोषणा NUM_SC520_PAR		16	/* total number of PAR रेजिस्टरs */

/*
** The highest three bits in a PAR रेजिस्टर determine what target
** device is controlled by this PAR. Here, only ROMCS? and BOOTCS
** devices are of पूर्णांकerest.
*/
#घोषणा SC520_PAR_BOOTCS	(0x4<<29)
#घोषणा SC520_PAR_ROMCS0	(0x5<<29)
#घोषणा SC520_PAR_ROMCS1	(0x6<<29)
#घोषणा SC520_PAR_TRGDEV	(0x7<<29)

/*
** Bits 28 thru 26 determine some attributes क्रम the
** region controlled by the PAR. (We only use non-cacheable)
*/
#घोषणा SC520_PAR_WRPROT	(1<<26)	/* ग_लिखो रक्षित       */
#घोषणा SC520_PAR_NOCACHE	(1<<27)	/* non-cacheable         */
#घोषणा SC520_PAR_NOEXEC	(1<<28)	/* code execution denied */


/*
** Bit 25 determines the granularity: 4K or 64K
*/
#घोषणा SC520_PAR_PG_SIZ4	(0<<25)
#घोषणा SC520_PAR_PG_SIZ64	(1<<25)

/*
** Build a value to be written पूर्णांकo a PAR रेजिस्टर.
** We only need ROM entries, 64K page size:
*/
#घोषणा SC520_PAR_ENTRY(trgdev, address, size) \
	((trgdev) | SC520_PAR_NOCACHE | SC520_PAR_PG_SIZ64 | \
	(address) >> 16 | (((size) >> 16) - 1) << 14)

काष्ठा sc520_par_table
अणु
	अचिन्हित दीर्घ trgdev;
	अचिन्हित दीर्घ new_par;
	अचिन्हित दीर्घ शेष_address;
पूर्ण;

अटल स्थिर काष्ठा sc520_par_table par_table[NUM_FLASH_BANKS] =
अणु
	अणु	/* Flash Bank #0: selected by ROMCS0 */
		SC520_PAR_ROMCS0,
		SC520_PAR_ENTRY(SC520_PAR_ROMCS0, WINDOW_ADDR_0, WINDOW_SIZE_0),
		WINDOW_ADDR_0_BIOS
	पूर्ण,
	अणु	/* Flash Bank #1: selected by ROMCS1 */
		SC520_PAR_ROMCS1,
		SC520_PAR_ENTRY(SC520_PAR_ROMCS1, WINDOW_ADDR_1, WINDOW_SIZE_1),
		WINDOW_ADDR_1_BIOS
	पूर्ण,
	अणु	/* DIL (BIOS) Flash: selected by BOOTCS */
		SC520_PAR_BOOTCS,
		SC520_PAR_ENTRY(SC520_PAR_BOOTCS, WINDOW_ADDR_2, WINDOW_SIZE_2),
		WINDOW_ADDR_2_BIOS
	पूर्ण
पूर्ण;


अटल व्योम sc520cdp_setup_par(व्योम)
अणु
	अचिन्हित दीर्घ __iomem *mmcr;
	अचिन्हित दीर्घ mmcr_val;
	पूर्णांक i, j;

	/* map in SC520's MMCR area */
	mmcr = ioremap(SC520_MMCR_BASE, SC520_MMCR_EXTENT);
	अगर(!mmcr) अणु /* ioremap failed: skip the PAR reprogramming */
		/* क्रमce physical address fields to BIOS शेषs: */
		क्रम(i = 0; i < NUM_FLASH_BANKS; i++)
			sc520cdp_map[i].phys = par_table[i].शेष_address;
		वापस;
	पूर्ण

	/*
	** Find the PARxx रेजिस्टरs that are responsible क्रम activating
	** ROMCS0, ROMCS1 and BOOTCS. Reprogram each of these with a
	** new value from the table.
	*/
	क्रम(i = 0; i < NUM_FLASH_BANKS; i++) अणु		/* क्रम each par_table entry  */
		क्रम(j = 0; j < NUM_SC520_PAR; j++) अणु	/* क्रम each PAR रेजिस्टर     */
			mmcr_val = पढ़ोl(&mmcr[SC520_PAR(j)]);
			/* अगर target device field matches, reprogram the PAR */
			अगर((mmcr_val & SC520_PAR_TRGDEV) == par_table[i].trgdev)
			अणु
				ग_लिखोl(par_table[i].new_par, &mmcr[SC520_PAR(j)]);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर(j == NUM_SC520_PAR)
		अणु	/* no matching PAR found: try शेष BIOS address */
			prपूर्णांकk(KERN_NOTICE "Could not find PAR responsible for %s\n",
				sc520cdp_map[i].name);
			prपूर्णांकk(KERN_NOTICE "Trying default address 0x%lx\n",
				par_table[i].शेष_address);
			sc520cdp_map[i].phys = par_table[i].शेष_address;
		पूर्ण
	पूर्ण
	iounmap(mmcr);
पूर्ण
#पूर्ण_अगर


अटल पूर्णांक __init init_sc520cdp(व्योम)
अणु
	पूर्णांक i, j, devices_found = 0;

#अगर_घोषित REPROGRAM_PAR
	/* reprogram PAR रेजिस्टरs so flash appears at the desired addresses */
	sc520cdp_setup_par();
#पूर्ण_अगर

	क्रम (i = 0; i < NUM_FLASH_BANKS; i++) अणु
		prपूर्णांकk(KERN_NOTICE "SC520 CDP flash device: 0x%Lx at 0x%Lx\n",
			(अचिन्हित दीर्घ दीर्घ)sc520cdp_map[i].size,
			(अचिन्हित दीर्घ दीर्घ)sc520cdp_map[i].phys);

		sc520cdp_map[i].virt = ioremap(sc520cdp_map[i].phys, sc520cdp_map[i].size);

		अगर (!sc520cdp_map[i].virt) अणु
			prपूर्णांकk("Failed to ioremap\n");
			क्रम (j = 0; j < i; j++) अणु
				अगर (mymtd[j]) अणु
					map_destroy(mymtd[j]);
					iounmap(sc520cdp_map[j].virt);
				पूर्ण
			पूर्ण
			वापस -EIO;
		पूर्ण

		simple_map_init(&sc520cdp_map[i]);

		mymtd[i] = करो_map_probe("cfi_probe", &sc520cdp_map[i]);
		अगर(!mymtd[i])
			mymtd[i] = करो_map_probe("jedec_probe", &sc520cdp_map[i]);
		अगर(!mymtd[i])
			mymtd[i] = करो_map_probe("map_rom", &sc520cdp_map[i]);

		अगर (mymtd[i]) अणु
			mymtd[i]->owner = THIS_MODULE;
			++devices_found;
		पूर्ण
		अन्यथा अणु
			iounmap(sc520cdp_map[i].virt);
		पूर्ण
	पूर्ण
	अगर(devices_found >= 2) अणु
		/* Combine the two flash banks पूर्णांकo a single MTD device & रेजिस्टर it: */
		merged_mtd = mtd_concat_create(mymtd, 2, "SC520CDP Flash Banks #0 and #1");
		अगर(merged_mtd)
			mtd_device_रेजिस्टर(merged_mtd, शून्य, 0);
	पूर्ण
	अगर(devices_found == 3) /* रेजिस्टर the third (DIL-Flash) device */
		mtd_device_रेजिस्टर(mymtd[2], शून्य, 0);
	वापस(devices_found ? 0 : -ENXIO);
पूर्ण

अटल व्योम __निकास cleanup_sc520cdp(व्योम)
अणु
	पूर्णांक i;

	अगर (merged_mtd) अणु
		mtd_device_unरेजिस्टर(merged_mtd);
		mtd_concat_destroy(merged_mtd);
	पूर्ण
	अगर (mymtd[2])
		mtd_device_unरेजिस्टर(mymtd[2]);

	क्रम (i = 0; i < NUM_FLASH_BANKS; i++) अणु
		अगर (mymtd[i])
			map_destroy(mymtd[i]);
		अगर (sc520cdp_map[i].virt) अणु
			iounmap(sc520cdp_map[i].virt);
			sc520cdp_map[i].virt = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

module_init(init_sc520cdp);
module_निकास(cleanup_sc520cdp);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sysgo Real-Time Solutions GmbH");
MODULE_DESCRIPTION("MTD map driver for AMD SC520 Customer Development Platform");
