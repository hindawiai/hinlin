<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 1995-2000  Linus Torvalds & author (see below)
 */

/*
 *  HT-6560B EIDE-controller support
 *  To activate controller support use kernel parameter "ide0=ht6560b".
 *  Use hdparm utility to enable PIO mode support.
 *
 *  Author:    Mikko Ala-Fossi            <maf@iki.fi>
 *             Jan Evert van Grootheest   <j.e.van.grootheest@caiway.nl>
 *
 */

#घोषणा DRV_NAME	"ht6560b"
#घोषणा HT6560B_VERSION "v0.08"

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

/* #घोषणा DEBUG */  /* हटाओ comments क्रम DEBUG messages */

/*
 * The special i/o-port that HT-6560B uses to configuration:
 *    bit0 (0x01): "1" selects secondary पूर्णांकerface
 *    bit2 (0x04): "1" enables FIFO function
 *    bit5 (0x20): "1" enables prefetched data पढ़ो function  (???)
 *
 * The special i/o-port that HT-6560A uses to configuration:
 *    bit0 (0x01): "1" selects secondary पूर्णांकerface
 *    bit1 (0x02): "1" enables prefetched data पढ़ो function
 *    bit2 (0x04): "0" enables multi-master प्रणाली	      (?)
 *    bit3 (0x08): "1" 3 cycle समय, "0" 2 cycle समय	      (?)
 */
#घोषणा HT_CONFIG_PORT	  0x3e6

अटल अंतरभूत u8 HT_CONFIG(ide_drive_t *drive)
अणु
	वापस ((अचिन्हित दीर्घ)ide_get_drivedata(drive) & 0xff00) >> 8;
पूर्ण

/*
 * FIFO + PREFETCH (both a/b-model)
 */
#घोषणा HT_CONFIG_DEFAULT 0x1c /* no prefetch */
/* #घोषणा HT_CONFIG_DEFAULT 0x3c */ /* with prefetch */
#घोषणा HT_SECONDARY_IF	  0x01
#घोषणा HT_PREFETCH_MODE  0x20

/*
 * ht6560b Timing values:
 *
 * I reviewed some assembler source listings of htide drivers and found
 * out how they setup those cycle समय पूर्णांकerfacing values, as they at Holtek
 * call them. IDESETUP.COM that is supplied with the drivers figures out
 * optimal values and fetches those values to drivers. I found out that
 * they use Select रेजिस्टर to fetch timings to the ide board right after
 * पूर्णांकerface चयनing. After that it was quite easy to add code to
 * ht6560b.c.
 *
 * IDESETUP.COM gave me values 0x24, 0x45, 0xaa, 0xff that worked fine
 * क्रम hda and hdc. But hdb needed higher values to work, so I guess
 * that someबार it is necessary to give higher value than IDESETUP
 * gives.   [see cmd640.c क्रम an extreme example of this. -ml]
 *
 * Perhaps I should explain something about these timing values:
 * The higher nibble of value is the Recovery Time  (rt) and the lower nibble
 * of the value is the Active Time  (at). Minimum value 2 is the fastest and
 * the maximum value 15 is the slowest. Default values should be 15 क्रम both.
 * So 0x24 means 2 क्रम rt and 4 क्रम at. Each of the drives should have
 * both values, and IDESETUP gives स्वतःmatically rt=15 st=15 क्रम CDROMs or
 * similar. If value is too small there will be all sorts of failures.
 *
 * Timing byte consists of
 *	High nibble:  Recovery Cycle Time  (rt)
 *	     The valid values range from 2 to 15. The शेष is 15.
 *
 *	Low nibble:   Active Cycle Time	   (at)
 *	     The valid values range from 2 to 15. The शेष is 15.
 *
 * You can obtain optimized timing values by running Holtek IDESETUP.COM
 * क्रम DOS. DOS drivers get their timing values from command line, where
 * the first value is the Recovery Time and the second value is the
 * Active Time क्रम each drive. Smaller value gives higher speed.
 * In हाल of failures you should probably fall back to a higher value.
 */
अटल अंतरभूत u8 HT_TIMING(ide_drive_t *drive)
अणु
	वापस (अचिन्हित दीर्घ)ide_get_drivedata(drive) & 0x00ff;
पूर्ण

#घोषणा HT_TIMING_DEFAULT 0xff

/*
 * This routine handles पूर्णांकerface चयनing क्रम the peculiar hardware design
 * on the F.G.I./Holtek HT-6560B VLB IDE पूर्णांकerface.
 * The HT-6560B can only enable one IDE port at a समय, and requires a
 * silly sequence (below) whenever we चयन between primary and secondary.
 */

/*
 * This routine is invoked from ide.c to prepare क्रम access to a given drive.
 */
अटल व्योम ht6560b_dev_select(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	अचिन्हित दीर्घ flags;
	अटल u8 current_select = 0;
	अटल u8 current_timing = 0;
	u8 select, timing;
	
	local_irq_save(flags);

	select = HT_CONFIG(drive);
	timing = HT_TIMING(drive);

	/*
	 * Need to enक्रमce prefetch someबार because otherwise
	 * it'll hang (hard).
	 */
	अगर (drive->media != ide_disk ||
	    (drive->dev_flags & IDE_DFLAG_PRESENT) == 0)
		select |= HT_PREFETCH_MODE;

	अगर (select != current_select || timing != current_timing) अणु
		current_select = select;
		current_timing = timing;
		(व्योम)inb(HT_CONFIG_PORT);
		(व्योम)inb(HT_CONFIG_PORT);
		(व्योम)inb(HT_CONFIG_PORT);
		(व्योम)inb(HT_CONFIG_PORT);
		outb(select, HT_CONFIG_PORT);
		/*
		 * Set timing क्रम this drive:
		 */
		outb(timing, hwअगर->io_ports.device_addr);
		(व्योम)inb(hwअगर->io_ports.status_addr);
#अगर_घोषित DEBUG
		prपूर्णांकk("ht6560b: %s: select=%#x timing=%#x\n",
			drive->name, select, timing);
#पूर्ण_अगर
	पूर्ण
	local_irq_restore(flags);

	outb(drive->select | ATA_DEVICE_OBS, hwअगर->io_ports.device_addr);
पूर्ण

/*
 * Autodetection and initialization of ht6560b
 */
अटल पूर्णांक __init try_to_init_ht6560b(व्योम)
अणु
	u8 orig_value;
	पूर्णांक i;
	
	/* Autodetect ht6560b */
	अगर ((orig_value = inb(HT_CONFIG_PORT)) == 0xff)
		वापस 0;
	
	क्रम (i=3;i>0;i--) अणु
		outb(0x00, HT_CONFIG_PORT);
		अगर (!( (~inb(HT_CONFIG_PORT)) & 0x3f )) अणु
			outb(orig_value, HT_CONFIG_PORT);
			वापस 0;
		पूर्ण
	पूर्ण
	outb(0x00, HT_CONFIG_PORT);
	अगर ((~inb(HT_CONFIG_PORT))& 0x3f) अणु
		outb(orig_value, HT_CONFIG_PORT);
		वापस 0;
	पूर्ण
	/*
	 * Ht6560b स्वतःdetected
	 */
	outb(HT_CONFIG_DEFAULT, HT_CONFIG_PORT);
	outb(HT_TIMING_DEFAULT, 0x1f6);	/* Select रेजिस्टर */
	(व्योम)inb(0x1f7);		/* Status रेजिस्टर */

	prपूर्णांकk("ht6560b " HT6560B_VERSION
	       ": chipset detected and initialized"
#अगर_घोषित DEBUG
	       " with debug enabled"
#पूर्ण_अगर
	       "\n"
		);
	वापस 1;
पूर्ण

अटल u8 ht_pio2timings(ide_drive_t *drive, स्थिर u8 pio)
अणु
	पूर्णांक active_समय, recovery_समय;
	पूर्णांक active_cycles, recovery_cycles;
	पूर्णांक bus_speed = ide_vlb_clk ? ide_vlb_clk : 50;

        अगर (pio) अणु
		अचिन्हित पूर्णांक cycle_समय;
		काष्ठा ide_timing *t = ide_timing_find_mode(XFER_PIO_0 + pio);

		cycle_समय = ide_pio_cycle_समय(drive, pio);

		/*
		 *  Just like opti621.c we try to calculate the
		 *  actual cycle समय क्रम recovery and activity
		 *  according प्रणाली bus speed.
		 */
		active_समय = t->active;
		recovery_समय = cycle_समय - active_समय - t->setup;
		/*
		 *  Cycle बार should be Vesa bus cycles
		 */
		active_cycles   = (active_समय   * bus_speed + 999) / 1000;
		recovery_cycles = (recovery_समय * bus_speed + 999) / 1000;
		/*
		 *  Upper and lower limits
		 */
		अगर (active_cycles   < 2)  active_cycles   = 2;
		अगर (recovery_cycles < 2)  recovery_cycles = 2;
		अगर (active_cycles   > 15) active_cycles   = 15;
		अगर (recovery_cycles > 15) recovery_cycles = 0;  /* 0==16 */
		
#अगर_घोषित DEBUG
		prपूर्णांकk("ht6560b: drive %s setting pio=%d recovery=%d (%dns) active=%d (%dns)\n", drive->name, pio, recovery_cycles, recovery_समय, active_cycles, active_समय);
#पूर्ण_अगर
		
		वापस (u8)((recovery_cycles << 4) | active_cycles);
	पूर्ण अन्यथा अणु
		
#अगर_घोषित DEBUG
		prपूर्णांकk("ht6560b: drive %s setting pio=0\n", drive->name);
#पूर्ण_अगर
		
		वापस HT_TIMING_DEFAULT;    /* शेष setting */
	पूर्ण
पूर्ण

अटल DEFINE_SPINLOCK(ht6560b_lock);

/*
 *  Enable/Disable so called prefetch mode
 */
अटल व्योम ht_set_prefetch(ide_drive_t *drive, u8 state)
अणु
	अचिन्हित दीर्घ flags, config;
	पूर्णांक t = HT_PREFETCH_MODE << 8;

	spin_lock_irqsave(&ht6560b_lock, flags);

	config = (अचिन्हित दीर्घ)ide_get_drivedata(drive);

	/*
	 *  Prefetch mode and unmask irq seems to conflict
	 */
	अगर (state) अणु
		config |= t;   /* enable prefetch mode */
		drive->dev_flags |= IDE_DFLAG_NO_UNMASK;
		drive->dev_flags &= ~IDE_DFLAG_UNMASK;
	पूर्ण अन्यथा अणु
		config &= ~t;  /* disable prefetch mode */
		drive->dev_flags &= ~IDE_DFLAG_NO_UNMASK;
	पूर्ण

	ide_set_drivedata(drive, (व्योम *)config);

	spin_unlock_irqrestore(&ht6560b_lock, flags);

#अगर_घोषित DEBUG
	prपूर्णांकk("ht6560b: drive %s prefetch mode %sabled\n", drive->name, (state ? "en" : "dis"));
#पूर्ण_अगर
पूर्ण

अटल व्योम ht6560b_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	अचिन्हित दीर्घ flags, config;
	स्थिर u8 pio = drive->pio_mode - XFER_PIO_0;
	u8 timing;
	
	चयन (pio) अणु
	हाल 8:         /* set prefetch off */
	हाल 9:         /* set prefetch on */
		ht_set_prefetch(drive, pio & 1);
		वापस;
	पूर्ण

	timing = ht_pio2timings(drive, pio);

	spin_lock_irqsave(&ht6560b_lock, flags);
	config = (अचिन्हित दीर्घ)ide_get_drivedata(drive);
	config &= 0xff00;
	config |= timing;
	ide_set_drivedata(drive, (व्योम *)config);
	spin_unlock_irqrestore(&ht6560b_lock, flags);

#अगर_घोषित DEBUG
	prपूर्णांकk("ht6560b: drive %s tuned to pio mode %#x timing=%#x\n", drive->name, pio, timing);
#पूर्ण_अगर
पूर्ण

अटल व्योम __init ht6560b_init_dev(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	/* Setting शेष configurations क्रम drives. */
	अचिन्हित दीर्घ t = (HT_CONFIG_DEFAULT << 8) | HT_TIMING_DEFAULT;

	अगर (hwअगर->channel)
		t |= (HT_SECONDARY_IF << 8);

	ide_set_drivedata(drive, (व्योम *)t);
पूर्ण

अटल bool probe_ht6560b;

module_param_named(probe, probe_ht6560b, bool, 0);
MODULE_PARM_DESC(probe, "probe for HT6560B chipset");

अटल स्थिर काष्ठा ide_tp_ops ht6560b_tp_ops = अणु
	.exec_command		= ide_exec_command,
	.पढ़ो_status		= ide_पढ़ो_status,
	.पढ़ो_altstatus		= ide_पढ़ो_altstatus,
	.ग_लिखो_devctl		= ide_ग_लिखो_devctl,

	.dev_select		= ht6560b_dev_select,
	.tf_load		= ide_tf_load,
	.tf_पढ़ो		= ide_tf_पढ़ो,

	.input_data		= ide_input_data,
	.output_data		= ide_output_data,
पूर्ण;

अटल स्थिर काष्ठा ide_port_ops ht6560b_port_ops = अणु
	.init_dev		= ht6560b_init_dev,
	.set_pio_mode		= ht6560b_set_pio_mode,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info ht6560b_port_info __initस्थिर = अणु
	.name			= DRV_NAME,
	.chipset		= ide_ht6560b,
	.tp_ops 		= &ht6560b_tp_ops,
	.port_ops		= &ht6560b_port_ops,
	.host_flags		= IDE_HFLAG_SERIALIZE | /* is this needed? */
				  IDE_HFLAG_NO_DMA |
				  IDE_HFLAG_ABUSE_PREFETCH,
	.pio_mask		= ATA_PIO4,
पूर्ण;

अटल पूर्णांक __init ht6560b_init(व्योम)
अणु
	अगर (probe_ht6560b == 0)
		वापस -ENODEV;

	अगर (!request_region(HT_CONFIG_PORT, 1, DRV_NAME)) अणु
		prपूर्णांकk(KERN_NOTICE "%s: HT_CONFIG_PORT not found\n",
			__func__);
		वापस -ENODEV;
	पूर्ण

	अगर (!try_to_init_ht6560b()) अणु
		prपूर्णांकk(KERN_NOTICE "%s: HBA not found\n", __func__);
		जाओ release_region;
	पूर्ण

	वापस ide_legacy_device_add(&ht6560b_port_info, 0);

release_region:
	release_region(HT_CONFIG_PORT, 1);
	वापस -ENODEV;
पूर्ण

module_init(ht6560b_init);

MODULE_AUTHOR("See Local File");
MODULE_DESCRIPTION("HT-6560B EIDE-controller support");
MODULE_LICENSE("GPL");
