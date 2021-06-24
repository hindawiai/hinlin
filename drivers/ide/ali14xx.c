<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 1996  Linus Torvalds & author (see below)
 */

/*
 * ALI M14xx chipset EIDE controller
 *
 * Works क्रम ALI M1439/1443/1445/1487/1489 chipsets.
 *
 * Adapted from code developed by derekn@vw.ece.cmu.edu.  -ml
 * Derek's notes follow:
 *
 * I think the code should be pretty understandable,
 * but I'll be happy to (try to) answer questions.
 *
 * The critical part is in the setupDrive function.  The initRegisters
 * function करोesn't seem to be necessary, but the DOS driver करोes it, so
 * I threw it in.
 *
 * I've only tested this on my प्रणाली, which only has one disk.  I posted
 * it to comp.sys.linux.hardware, so maybe some other people will try it
 * out.
 *
 * Derek Noonburg  (derekn@ece.cmu.edu)
 * 95-sep-26
 *
 * Update 96-jul-13:
 *
 * I've since upgraded to two disks and a CD-ROM, with no trouble, and
 * I've also heard from several others who have used it successfully.
 * This driver appears to work with both the 1443/1445 and the 1487/1489
 * chipsets.  I've added support क्रम PIO mode 4 क्रम the 1487.  This
 * seems to work just fine on the 1443 also, although I'm not sure it's
 * advertised as supporting mode 4.  (I've been running a WDC AC21200 in
 * mode 4 क्रम a जबतक now with no trouble.)  -Derek
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

#घोषणा DRV_NAME "ali14xx"

/* port addresses क्रम स्वतः-detection */
#घोषणा ALI_NUM_PORTS 4
अटल स्थिर पूर्णांक ports[ALI_NUM_PORTS] __initस्थिर =
	अणु 0x074, 0x0f4, 0x034, 0x0e4 पूर्ण;

/* रेजिस्टर initialization data */
प्रकार काष्ठा अणु u8 reg, data; पूर्ण RegInitializer;

अटल स्थिर RegInitializer initData[] __initस्थिर = अणु
	अणु0x01, 0x0fपूर्ण, अणु0x02, 0x00पूर्ण, अणु0x03, 0x00पूर्ण, अणु0x04, 0x00पूर्ण,
	अणु0x05, 0x00पूर्ण, अणु0x06, 0x00पूर्ण, अणु0x07, 0x2bपूर्ण, अणु0x0a, 0x0fपूर्ण,
	अणु0x25, 0x00पूर्ण, अणु0x26, 0x00पूर्ण, अणु0x27, 0x00पूर्ण, अणु0x28, 0x00पूर्ण,
	अणु0x29, 0x00पूर्ण, अणु0x2a, 0x00पूर्ण, अणु0x2f, 0x00पूर्ण, अणु0x2b, 0x00पूर्ण,
	अणु0x2c, 0x00पूर्ण, अणु0x2d, 0x00पूर्ण, अणु0x2e, 0x00पूर्ण, अणु0x30, 0x00पूर्ण,
	अणु0x31, 0x00पूर्ण, अणु0x32, 0x00पूर्ण, अणु0x33, 0x00पूर्ण, अणु0x34, 0xffपूर्ण,
	अणु0x35, 0x03पूर्ण, अणु0x00, 0x00पूर्ण
पूर्ण;

/* timing parameter रेजिस्टरs क्रम each drive */
अटल काष्ठा अणु u8 reg1, reg2, reg3, reg4; पूर्ण regTab[4] = अणु
	अणु0x03, 0x26, 0x04, 0x27पूर्ण,     /* drive 0 */
	अणु0x05, 0x28, 0x06, 0x29पूर्ण,     /* drive 1 */
	अणु0x2b, 0x30, 0x2c, 0x31पूर्ण,     /* drive 2 */
	अणु0x2d, 0x32, 0x2e, 0x33पूर्ण,     /* drive 3 */
पूर्ण;

अटल पूर्णांक basePort;	/* base port address */
अटल पूर्णांक regPort;	/* port क्रम रेजिस्टर number */
अटल पूर्णांक dataPort;	/* port क्रम रेजिस्टर data */
अटल u8 regOn;	/* output to base port to access रेजिस्टरs */
अटल u8 regOff;	/* output to base port to बंद रेजिस्टरs */

/*------------------------------------------------------------------------*/

/*
 * Read a controller रेजिस्टर.
 */
अटल अंतरभूत u8 inReg(u8 reg)
अणु
	outb_p(reg, regPort);
	वापस inb(dataPort);
पूर्ण

/*
 * Write a controller रेजिस्टर.
 */
अटल व्योम outReg(u8 data, u8 reg)
अणु
	outb_p(reg, regPort);
	outb_p(data, dataPort);
पूर्ण

अटल DEFINE_SPINLOCK(ali14xx_lock);

/*
 * Set PIO mode क्रम the specअगरied drive.
 * This function computes timing parameters
 * and sets controller रेजिस्टरs accordingly.
 */
अटल व्योम ali14xx_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	पूर्णांक driveNum;
	पूर्णांक समय1, समय2;
	u8 param1, param2, param3, param4;
	अचिन्हित दीर्घ flags;
	पूर्णांक bus_speed = ide_vlb_clk ? ide_vlb_clk : 50;
	स्थिर u8 pio = drive->pio_mode - XFER_PIO_0;
	काष्ठा ide_timing *t = ide_timing_find_mode(XFER_PIO_0 + pio);

	/* calculate timing, according to PIO mode */
	समय1 = ide_pio_cycle_समय(drive, pio);
	समय2 = t->active;
	param3 = param1 = (समय2 * bus_speed + 999) / 1000;
	param4 = param2 = (समय1 * bus_speed + 999) / 1000 - param1;
	अगर (pio < 3) अणु
		param3 += 8;
		param4 += 8;
	पूर्ण
	prपूर्णांकk(KERN_DEBUG "%s: PIO mode%d, t1=%dns, t2=%dns, cycles = %d+%d, %d+%d\n",
		drive->name, pio, समय1, समय2, param1, param2, param3, param4);

	/* stuff timing parameters पूर्णांकo controller रेजिस्टरs */
	driveNum = (drive->hwअगर->index << 1) + (drive->dn & 1);
	spin_lock_irqsave(&ali14xx_lock, flags);
	outb_p(regOn, basePort);
	outReg(param1, regTab[driveNum].reg1);
	outReg(param2, regTab[driveNum].reg2);
	outReg(param3, regTab[driveNum].reg3);
	outReg(param4, regTab[driveNum].reg4);
	outb_p(regOff, basePort);
	spin_unlock_irqrestore(&ali14xx_lock, flags);
पूर्ण

/*
 * Auto-detect the IDE controller port.
 */
अटल पूर्णांक __init findPort(व्योम)
अणु
	पूर्णांक i;
	u8 t;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	क्रम (i = 0; i < ALI_NUM_PORTS; ++i) अणु
		basePort = ports[i];
		regOff = inb(basePort);
		क्रम (regOn = 0x30; regOn <= 0x33; ++regOn) अणु
			outb_p(regOn, basePort);
			अगर (inb(basePort) == regOn) अणु
				regPort = basePort + 4;
				dataPort = basePort + 8;
				t = inReg(0) & 0xf0;
				outb_p(regOff, basePort);
				local_irq_restore(flags);
				अगर (t != 0x50)
					वापस 0;
				वापस 1;  /* success */
			पूर्ण
		पूर्ण
		outb_p(regOff, basePort);
	पूर्ण
	local_irq_restore(flags);
	वापस 0;
पूर्ण

/*
 * Initialize controller रेजिस्टरs with शेष values.
 */
अटल पूर्णांक __init initRegisters(व्योम)
अणु
	स्थिर RegInitializer *p;
	u8 t;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	outb_p(regOn, basePort);
	क्रम (p = initData; p->reg != 0; ++p)
		outReg(p->data, p->reg);
	outb_p(0x01, regPort);
	t = inb(regPort) & 0x01;
	outb_p(regOff, basePort);
	local_irq_restore(flags);
	वापस t;
पूर्ण

अटल स्थिर काष्ठा ide_port_ops ali14xx_port_ops = अणु
	.set_pio_mode		= ali14xx_set_pio_mode,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info ali14xx_port_info = अणु
	.name			= DRV_NAME,
	.chipset		= ide_ali14xx,
	.port_ops		= &ali14xx_port_ops,
	.host_flags		= IDE_HFLAG_NO_DMA,
	.pio_mask		= ATA_PIO4,
पूर्ण;

अटल पूर्णांक __init ali14xx_probe(व्योम)
अणु
	prपूर्णांकk(KERN_DEBUG "ali14xx: base=0x%03x, regOn=0x%02x.\n",
			  basePort, regOn);

	/* initialize controller रेजिस्टरs */
	अगर (!initRegisters()) अणु
		prपूर्णांकk(KERN_ERR "ali14xx: Chip initialization failed.\n");
		वापस 1;
	पूर्ण

	वापस ide_legacy_device_add(&ali14xx_port_info, 0);
पूर्ण

अटल bool probe_ali14xx;

module_param_named(probe, probe_ali14xx, bool, 0);
MODULE_PARM_DESC(probe, "probe for ALI M14xx chipsets");

अटल पूर्णांक __init ali14xx_init(व्योम)
अणु
	अगर (probe_ali14xx == 0)
		जाओ out;

	/* स्वतः-detect IDE controller port */
	अगर (findPort()) अणु
		अगर (ali14xx_probe())
			वापस -ENODEV;
		वापस 0;
	पूर्ण
	prपूर्णांकk(KERN_ERR "ali14xx: not found.\n");
out:
	वापस -ENODEV;
पूर्ण

module_init(ali14xx_init);

MODULE_AUTHOR("see local file");
MODULE_DESCRIPTION("support of ALI 14XX IDE chipsets");
MODULE_LICENSE("GPL");
