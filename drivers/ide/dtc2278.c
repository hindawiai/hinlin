<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 1996  Linus Torvalds & author (see below)
 */

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

#घोषणा DRV_NAME "dtc2278"

/*
 * Changing this #अघोषित to #घोषणा may solve start up problems in some प्रणालीs.
 */
#अघोषित ALWAYS_SET_DTC2278_PIO_MODE

/*
 * From: andy@cercle.cts.com (Dyan Wile)
 *
 * Below is a patch क्रम DTC-2278 - alike software-programmable controllers
 * The code enables the secondary IDE controller and the PIO4 (3?) timings on
 * the primary (EIDE). You may probably have to enable the 32-bit support to
 * get the full speed. You better get the disk पूर्णांकerrupts disabled ( hdparm -u0
 * /dev/hd.. ) क्रम the drives connected to the EIDE पूर्णांकerface. (I get my
 * fileप्रणाली  corrupted with -u1, but under heavy disk load only :-)
 *
 * This card is now क्रमced to use the "serialize" feature,
 * and irq-unmasking is disallowed.  If io_32bit is enabled,
 * it must be करोne क्रम BOTH drives on each पूर्णांकerface.
 *
 * This code was written क्रम the DTC2278E, but might work with any of these:
 *
 * DTC2278S has only a single IDE पूर्णांकerface.
 * DTC2278D has two IDE पूर्णांकerfaces and is otherwise identical to the S version.
 * DTC2278E also has serial ports and a prपूर्णांकer port
 * DTC2278EB: has onboard BIOS, and "works like a charm" -- Kent Bradक्रमd <kent@theory.caltech.edu>
 *
 * There may be a fourth controller type. The S and D versions use the
 * Winbond chip, and I think the E version करोes also.
 *
 */

अटल व्योम sub22 (अक्षर b, अक्षर c)
अणु
	पूर्णांक i;

	क्रम(i = 0; i < 3; ++i) अणु
		inb(0x3f6);
		outb_p(b,0xb0);
		inb(0x3f6);
		outb_p(c,0xb4);
		inb(0x3f6);
		अगर(inb(0xb4) == c) अणु
			outb_p(7,0xb0);
			inb(0x3f6);
			वापस;	/* success */
		पूर्ण
	पूर्ण
पूर्ण

अटल DEFINE_SPINLOCK(dtc2278_lock);

अटल व्योम dtc2278_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	अचिन्हित दीर्घ flags;

	अगर (drive->pio_mode >= XFER_PIO_3) अणु
		spin_lock_irqsave(&dtc2278_lock, flags);
		/*
		 * This enables PIO mode4 (3?) on the first पूर्णांकerface
		 */
		sub22(1,0xc3);
		sub22(0,0xa0);
		spin_unlock_irqrestore(&dtc2278_lock, flags);
	पूर्ण अन्यथा अणु
		/* we करोn't know how to set it back again.. */
		/* Actually we करो - there is a data sheet available क्रम the
		   Winbond but करोes anyone actually care */
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ide_port_ops dtc2278_port_ops = अणु
	.set_pio_mode		= dtc2278_set_pio_mode,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info dtc2278_port_info __initस्थिर = अणु
	.name			= DRV_NAME,
	.chipset		= ide_dtc2278,
	.port_ops		= &dtc2278_port_ops,
	.host_flags		= IDE_HFLAG_SERIALIZE |
				  IDE_HFLAG_NO_UNMASK_IRQS |
				  IDE_HFLAG_IO_32BIT |
				  /* disallow ->io_32bit changes */
				  IDE_HFLAG_NO_IO_32BIT |
				  IDE_HFLAG_NO_DMA |
				  IDE_HFLAG_DTC2278,
	.pio_mask		= ATA_PIO4,
पूर्ण;

अटल पूर्णांक __init dtc2278_probe(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	/*
	 * This enables the second पूर्णांकerface
	 */
	outb_p(4,0xb0);
	inb(0x3f6);
	outb_p(0x20,0xb4);
	inb(0x3f6);
#अगर_घोषित ALWAYS_SET_DTC2278_PIO_MODE
	/*
	 * This enables PIO mode4 (3?) on the first पूर्णांकerface
	 * and may solve start-up problems क्रम some people.
	 */
	sub22(1,0xc3);
	sub22(0,0xa0);
#पूर्ण_अगर
	local_irq_restore(flags);

	वापस ide_legacy_device_add(&dtc2278_port_info, 0);
पूर्ण

अटल bool probe_dtc2278;

module_param_named(probe, probe_dtc2278, bool, 0);
MODULE_PARM_DESC(probe, "probe for DTC2278xx chipsets");

अटल पूर्णांक __init dtc2278_init(व्योम)
अणु
	अगर (probe_dtc2278 == 0)
		वापस -ENODEV;

	अगर (dtc2278_probe()) अणु
		prपूर्णांकk(KERN_ERR "dtc2278: ide interfaces already in use!\n");
		वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण

module_init(dtc2278_init);

MODULE_AUTHOR("See Local File");
MODULE_DESCRIPTION("support of DTC-2278 VLB IDE chipsets");
MODULE_LICENSE("GPL");
