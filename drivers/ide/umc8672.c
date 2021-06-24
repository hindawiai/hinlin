<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 1995-1996  Linus Torvalds & author (see below)
 */

/*
 *  Principal Author/Maपूर्णांकainer:  PODIEN@hml2.atlas.de (Wolfram Podien)
 *
 *  This file provides support क्रम the advanced features
 *  of the UMC 8672 IDE पूर्णांकerface.
 *
 *  Version 0.01	Initial version, hacked out of ide.c,
 *			and #समावेश'd rather than compiled separately.
 *			This will get cleaned up in a subsequent release.
 *
 *  Version 0.02	now configs/compiles separate from ide.c  -ml
 *  Version 0.03	enhanced स्वतः-tune, fix display bug
 *  Version 0.05	replace sti() with restore_flags()  -ml
 *			add detection of possible race condition  -ml
 */

/*
 * VLB Controller Support from
 * Wolfram Podien
 * Rohoefe 3
 * D28832 Achim
 * Germany
 *
 * To enable UMC8672 support there must a lilo line like
 * append="ide0=umc8672"...
 * To set the speed according to the abilities of the hardware there must be a
 * line like
 * #घोषणा UMC_DRIVE0 11
 * in the beginning of the driver, which sets the speed of drive 0 to 11 (there
 * are some lines present). 0 - 11 are allowed speed values. These values are
 * the results from the DOS speed test program supplied from UMC. 11 is the
 * highest speed (about PIO mode 3)
 */
#घोषणा REALLY_SLOW_IO		/* some प्रणालीs can safely undef this */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/समयr.h>
#समावेश <linux/mm.h>
#समावेश <linux/ioport.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/ide.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/पन.स>

#घोषणा DRV_NAME "umc8672"

/*
 * Default speeds.  These can be changed with "auto-tune" and/or hdparm.
 */
#घोषणा UMC_DRIVE0      1              /* DOS measured drive speeds */
#घोषणा UMC_DRIVE1      1              /* 0 to 11 allowed */
#घोषणा UMC_DRIVE2      1              /* 11 = Fastest Speed */
#घोषणा UMC_DRIVE3      1              /* In हाल of crash reduce speed */

अटल u8 current_speeds[4] = अणुUMC_DRIVE0, UMC_DRIVE1, UMC_DRIVE2, UMC_DRIVE3पूर्ण;
अटल स्थिर u8 pio_to_umc [5] = अणु0, 3, 7, 10, 11पूर्ण;	/* rough guesses */

/*       0    1    2    3    4    5    6    7    8    9    10   11      */
अटल स्थिर u8 speedtab [3][12] = अणु
	अणु0x0f, 0x0b, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x1पूर्ण,
	अणु0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x1पूर्ण,
	अणु0xff, 0xcb, 0xc0, 0x58, 0x36, 0x33, 0x23, 0x22, 0x21, 0x11, 0x10, 0x0पूर्ण
पूर्ण;

अटल व्योम out_umc(अक्षर port, अक्षर wert)
अणु
	outb_p(port, 0x108);
	outb_p(wert, 0x109);
पूर्ण

अटल अंतरभूत u8 in_umc(अक्षर port)
अणु
	outb_p(port, 0x108);
	वापस inb_p(0x109);
पूर्ण

अटल व्योम umc_set_speeds(u8 speeds[])
अणु
	पूर्णांक i, पंचांगp;

	outb_p(0x5A, 0x108); /* enable umc */

	out_umc(0xd7, (speedtab[0][speeds[2]] | (speedtab[0][speeds[3]]<<4)));
	out_umc(0xd6, (speedtab[0][speeds[0]] | (speedtab[0][speeds[1]]<<4)));
	पंचांगp = 0;
	क्रम (i = 3; i >= 0; i--)
		पंचांगp = (पंचांगp << 2) | speedtab[1][speeds[i]];
	out_umc(0xdc, पंचांगp);
	क्रम (i = 0; i < 4; i++) अणु
		out_umc(0xd0 + i, speedtab[2][speeds[i]]);
		out_umc(0xd8 + i, speedtab[2][speeds[i]]);
	पूर्ण
	outb_p(0xa5, 0x108); /* disable umc */

	prपूर्णांकk("umc8672: drive speeds [0 to 11]: %d %d %d %d\n",
		speeds[0], speeds[1], speeds[2], speeds[3]);
पूर्ण

अटल व्योम umc_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	ide_hwअगर_t *mate = hwअगर->mate;
	अचिन्हित दीर्घ flags;
	स्थिर u8 pio = drive->pio_mode - XFER_PIO_0;

	prपूर्णांकk("%s: setting umc8672 to PIO mode%d (speed %d)\n",
		drive->name, pio, pio_to_umc[pio]);
	अगर (mate)
		spin_lock_irqsave(&mate->lock, flags);
	अगर (mate && mate->handler) अणु
		prपूर्णांकk(KERN_ERR "umc8672: other interface is busy: exiting tune_umc()\n");
	पूर्ण अन्यथा अणु
		current_speeds[drive->name[2] - 'a'] = pio_to_umc[pio];
		umc_set_speeds(current_speeds);
	पूर्ण
	अगर (mate)
		spin_unlock_irqrestore(&mate->lock, flags);
पूर्ण

अटल स्थिर काष्ठा ide_port_ops umc8672_port_ops = अणु
	.set_pio_mode		= umc_set_pio_mode,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info umc8672_port_info __initस्थिर = अणु
	.name			= DRV_NAME,
	.chipset		= ide_umc8672,
	.port_ops		= &umc8672_port_ops,
	.host_flags		= IDE_HFLAG_NO_DMA,
	.pio_mask		= ATA_PIO4,
पूर्ण;

अटल पूर्णांक __init umc8672_probe(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!request_region(0x108, 2, "umc8672")) अणु
		prपूर्णांकk(KERN_ERR "umc8672: ports 0x108-0x109 already in use.\n");
		वापस 1;
	पूर्ण
	local_irq_save(flags);
	outb_p(0x5A, 0x108); /* enable umc */
	अगर (in_umc (0xd5) != 0xa0) अणु
		local_irq_restore(flags);
		prपूर्णांकk(KERN_ERR "umc8672: not found\n");
		release_region(0x108, 2);
		वापस 1;
	पूर्ण
	outb_p(0xa5, 0x108); /* disable umc */

	umc_set_speeds(current_speeds);
	local_irq_restore(flags);

	वापस ide_legacy_device_add(&umc8672_port_info, 0);
पूर्ण

अटल bool probe_umc8672;

module_param_named(probe, probe_umc8672, bool, 0);
MODULE_PARM_DESC(probe, "probe for UMC8672 chipset");

अटल पूर्णांक __init umc8672_init(व्योम)
अणु
	अगर (probe_umc8672 == 0)
		जाओ out;

	अगर (umc8672_probe() == 0)
		वापस 0;
out:
	वापस -ENODEV;
पूर्ण

module_init(umc8672_init);

MODULE_AUTHOR("Wolfram Podien");
MODULE_DESCRIPTION("Support for UMC 8672 IDE chipset");
MODULE_LICENSE("GPL");
