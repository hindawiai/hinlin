<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 1995-1996  Linus Torvalds & authors (see below)
 */

/*
 *  Original authors:	abramov@cecmow.enet.dec.com (Igor Abramov)
 *			mlord@pobox.com (Mark Lord)
 *
 *  See linux/MAINTAINERS क्रम address of current मुख्यtainer.
 *
 *  This file provides support क्रम the advanced features and bugs
 *  of IDE पूर्णांकerfaces using the CMD Technologies 0640 IDE पूर्णांकerface chip.
 *
 *  These chips are basically fucked by design, and getting this driver
 *  to work on every motherboard design that uses this screwed chip seems
 *  bloody well impossible.  However, we're still trying.
 *
 *  Version 0.97 worked क्रम everybody.
 *
 *  User feedback is essential.  Many thanks to the beta test team:
 *
 *  A.Hartgers@stud.tue.nl, JZDQC@CUNYVM.CUNY.edu, abramov@cecmow.enet.dec.com,
 *  bardj@utopia.ppp.sn.no, bart@gaga.tue.nl, bbol001@cs.auckland.ac.nz,
 *  chrisc@dbass.demon.co.uk, dalecki@namu26.Num.Math.Uni-Goettingen.de,
 *  derekn@vw.ece.cmu.edu, florian@btp2x3.phy.uni-bayreuth.de,
 *  flynn@dei.unipd.it, gadio@netvision.net.il, godzilla@futuris.net,
 *  j@pobox.com, jkemp1@mises.uni-paderborn.de, jtoppe@hiwaay.net,
 *  kerouac@ssnet.com, meskes@inक्रमmatik.rwth-aachen.de, hzoli@cs.elte.hu,
 *  peter@udgaard.isgtec.com, phil@tazenda.demon.co.uk, roadcapw@cfw.com,
 *  s0033las@sun10.vsz.bme.hu, schaffer@tam.cornell.edu, sjd@slip.net,
 *  steve@ei.org, ulrpeg@bigcomm.gun.de, ism@tardis.ed.ac.uk, mack@cray.com
 *  liug@mama.indstate.edu, and others.
 *
 *  Version 0.01	Initial version, hacked out of ide.c,
 *			and #समावेश'd rather than compiled separately.
 *			This will get cleaned up in a subsequent release.
 *
 *  Version 0.02	Fixes क्रम vlb initialization code, enable prefetch
 *			क्रम versions 'B' and 'C' of chip by शेष,
 *			some code cleanup.
 *
 *  Version 0.03	Added reset of secondary पूर्णांकerface,
 *			and black list क्रम devices which are not compatible
 *			with prefetch mode. Separate function क्रम setting
 *			prefetch is added, possibly it will be called some
 *			day from ioctl processing code.
 *
 *  Version 0.04	Now configs/compiles separate from ide.c
 *
 *  Version 0.05	Major reग_लिखो of पूर्णांकerface timing code.
 *			Added new function cmd640_set_mode to set PIO mode
 *			from ioctl call. New drives added to black list.
 *
 *  Version 0.06	More code cleanup. Prefetch is enabled only क्रम
 *			detected hard drives, not included in prefetch
 *			black list.
 *
 *  Version 0.07	Changed to more conservative drive tuning policy.
 *			Unknown drives, which report PIO < 4 are set to
 *			(reported_PIO - 1) अगर it is supported, or to PIO0.
 *			List of known drives extended by info provided by
 *			CMD at their ftp site.
 *
 *  Version 0.08	Added स्वतःtune/noस्वतःtune support.
 *
 *  Version 0.09	Try to be smarter about 2nd port enabling.
 *  Version 0.10	Be nice and करोn't reset 2nd port.
 *  Version 0.11	Try to handle more weird situations.
 *
 *  Version 0.12	Lots of bug fixes from Laszlo Peter
 *			irq unmasking disabled क्रम reliability.
 *			try to be even smarter about the second port.
 *			tidy up source code क्रमmatting.
 *  Version 0.13	permit irq unmasking again.
 *  Version 0.90	massive code cleanup, some bugs fixed.
 *			शेषs all drives to PIO mode0, prefetch off.
 *			स्वतःtune is OFF by शेष, with compile समय flag.
 *			prefetch can be turned OFF/ON using "hdparm -p8/-p9"
 *			 (requires hdparm-3.1 or newer)
 *  Version 0.91	first release to linux-kernel list.
 *  Version 0.92	move initial reg dump to separate callable function
 *			change "readahead" to "prefetch" to aव्योम confusion
 *  Version 0.95	respect original BIOS timings unless स्वतःtuning.
 *			tons of code cleanup and rearrangement.
 *			added CONFIG_BLK_DEV_CMD640_ENHANCED option
 *			prevent use of unmask when prefetch is on
 *  Version 0.96	prevent use of io_32bit when prefetch is off
 *  Version 0.97	fix VLB secondary पूर्णांकerface क्रम sjd@slip.net
 *			other minor tune-ups:  0.96 was very good.
 *  Version 0.98	ignore PCI version when disabled by BIOS
 *  Version 0.99	display setup/active/recovery घड़ीs with PIO mode
 *  Version 1.00	Mmm.. cannot depend on PCMD_ENA in all प्रणालीs
 *  Version 1.01	slow/fast devsel can be selected with "hdparm -p6/-p7"
 *			 ("fast" is necessary क्रम 32bit I/O in some प्रणालीs)
 *  Version 1.02	fix bug that resulted in slow "setup times"
 *			 (patch courtesy of Zoltan Hidvegi)
 */

#घोषणा CMD640_PREFETCH_MASKS 1

/*#घोषणा CMD640_DUMP_REGS */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/ide.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/पन.स>

#घोषणा DRV_NAME "cmd640"

अटल bool cmd640_vlb;

/*
 * CMD640 specअगरic रेजिस्टरs definition.
 */

#घोषणा VID		0x00
#घोषणा DID		0x02
#घोषणा PCMD		0x04
#घोषणा   PCMD_ENA	0x01
#घोषणा PSTTS		0x06
#घोषणा REVID		0x08
#घोषणा PROGIF		0x09
#घोषणा SUBCL		0x0a
#घोषणा BASCL		0x0b
#घोषणा BaseA0		0x10
#घोषणा BaseA1		0x14
#घोषणा BaseA2		0x18
#घोषणा BaseA3		0x1c
#घोषणा INTLINE		0x3c
#घोषणा INPINE		0x3d

#घोषणा	CFR		0x50
#घोषणा   CFR_DEVREV		0x03
#घोषणा   CFR_IDE01INTR		0x04
#घोषणा	  CFR_DEVID		0x18
#घोषणा	  CFR_AT_VESA_078h	0x20
#घोषणा	  CFR_DSA1		0x40
#घोषणा	  CFR_DSA0		0x80

#घोषणा CNTRL		0x51
#घोषणा	  CNTRL_DIS_RA0		0x40
#घोषणा   CNTRL_DIS_RA1		0x80
#घोषणा	  CNTRL_ENA_2ND		0x08

#घोषणा	CMDTIM		0x52
#घोषणा	ARTTIM0		0x53
#घोषणा	DRWTIM0		0x54
#घोषणा ARTTIM1 	0x55
#घोषणा DRWTIM1		0x56
#घोषणा ARTTIM23	0x57
#घोषणा   ARTTIM23_DIS_RA2	0x04
#घोषणा   ARTTIM23_DIS_RA3	0x08
#घोषणा   ARTTIM23_IDE23INTR	0x10
#घोषणा DRWTIM23	0x58
#घोषणा BRST		0x59

/*
 * Registers and masks क्रम easy access by drive index:
 */
अटल u8 prefetch_regs[4]  = अणुCNTRL, CNTRL, ARTTIM23, ARTTIM23पूर्ण;
अटल u8 prefetch_masks[4] = अणुCNTRL_DIS_RA0, CNTRL_DIS_RA1, ARTTIM23_DIS_RA2, ARTTIM23_DIS_RA3पूर्ण;

#अगर_घोषित CONFIG_BLK_DEV_CMD640_ENHANCED

अटल u8 arttim_regs[4] = अणुARTTIM0, ARTTIM1, ARTTIM23, ARTTIM23पूर्ण;
अटल u8 drwtim_regs[4] = अणुDRWTIM0, DRWTIM1, DRWTIM23, DRWTIM23पूर्ण;

/*
 * Current cmd640 timing values क्रम each drive.
 * The शेषs क्रम each are the slowest possible timings.
 */
अटल u8 setup_counts[4]    = अणु4, 4, 4, 4पूर्ण;     /* Address setup count (in घड़ीs) */
अटल u8 active_counts[4]   = अणु16, 16, 16, 16पूर्ण; /* Active count   (encoded) */
अटल u8 recovery_counts[4] = अणु16, 16, 16, 16पूर्ण; /* Recovery count (encoded) */

#पूर्ण_अगर /* CONFIG_BLK_DEV_CMD640_ENHANCED */

अटल DEFINE_SPINLOCK(cmd640_lock);

/*
 * Interface to access cmd640x रेजिस्टरs
 */
अटल अचिन्हित पूर्णांक cmd640_key;
अटल व्योम (*__put_cmd640_reg)(u16 reg, u8 val);
अटल u8 (*__get_cmd640_reg)(u16 reg);

/*
 * This is पढ़ो from the CFR reg, and is used in several places.
 */
अटल अचिन्हित पूर्णांक cmd640_chip_version;

/*
 * The CMD640x chip करोes not support DWORD config ग_लिखो cycles, but some
 * of the BIOSes use them to implement the config services.
 * Thereक्रमe, we must use direct IO instead.
 */

/* PCI method 1 access */

अटल व्योम put_cmd640_reg_pci1(u16 reg, u8 val)
अणु
	outl_p((reg & 0xfc) | cmd640_key, 0xcf8);
	outb_p(val, (reg & 3) | 0xcfc);
पूर्ण

अटल u8 get_cmd640_reg_pci1(u16 reg)
अणु
	outl_p((reg & 0xfc) | cmd640_key, 0xcf8);
	वापस inb_p((reg & 3) | 0xcfc);
पूर्ण

/* PCI method 2 access (from CMD datasheet) */

अटल व्योम put_cmd640_reg_pci2(u16 reg, u8 val)
अणु
	outb_p(0x10, 0xcf8);
	outb_p(val, cmd640_key + reg);
	outb_p(0, 0xcf8);
पूर्ण

अटल u8 get_cmd640_reg_pci2(u16 reg)
अणु
	u8 b;

	outb_p(0x10, 0xcf8);
	b = inb_p(cmd640_key + reg);
	outb_p(0, 0xcf8);
	वापस b;
पूर्ण

/* VLB access */

अटल व्योम put_cmd640_reg_vlb(u16 reg, u8 val)
अणु
	outb_p(reg, cmd640_key);
	outb_p(val, cmd640_key + 4);
पूर्ण

अटल u8 get_cmd640_reg_vlb(u16 reg)
अणु
	outb_p(reg, cmd640_key);
	वापस inb_p(cmd640_key + 4);
पूर्ण

अटल u8 get_cmd640_reg(u16 reg)
अणु
	अचिन्हित दीर्घ flags;
	u8 b;

	spin_lock_irqsave(&cmd640_lock, flags);
	b = __get_cmd640_reg(reg);
	spin_unlock_irqrestore(&cmd640_lock, flags);
	वापस b;
पूर्ण

अटल व्योम put_cmd640_reg(u16 reg, u8 val)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cmd640_lock, flags);
	__put_cmd640_reg(reg, val);
	spin_unlock_irqrestore(&cmd640_lock, flags);
पूर्ण

अटल पूर्णांक __init match_pci_cmd640_device(व्योम)
अणु
	स्थिर u8 ven_dev[4] = अणु0x95, 0x10, 0x40, 0x06पूर्ण;
	अचिन्हित पूर्णांक i;
	क्रम (i = 0; i < 4; i++) अणु
		अगर (get_cmd640_reg(i) != ven_dev[i])
			वापस 0;
	पूर्ण
#अगर_घोषित STUPIDLY_TRUST_BROKEN_PCMD_ENA_BIT
	अगर ((get_cmd640_reg(PCMD) & PCMD_ENA) == 0) अणु
		prपूर्णांकk("ide: cmd640 on PCI disabled by BIOS\n");
		वापस 0;
	पूर्ण
#पूर्ण_अगर /* STUPIDLY_TRUST_BROKEN_PCMD_ENA_BIT */
	वापस 1; /* success */
पूर्ण

/*
 * Probe क्रम CMD640x -- pci method 1
 */
अटल पूर्णांक __init probe_क्रम_cmd640_pci1(व्योम)
अणु
	__get_cmd640_reg = get_cmd640_reg_pci1;
	__put_cmd640_reg = put_cmd640_reg_pci1;
	क्रम (cmd640_key = 0x80000000;
	     cmd640_key <= 0x8000f800;
	     cmd640_key += 0x800) अणु
		अगर (match_pci_cmd640_device())
			वापस 1; /* success */
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Probe क्रम CMD640x -- pci method 2
 */
अटल पूर्णांक __init probe_क्रम_cmd640_pci2(व्योम)
अणु
	__get_cmd640_reg = get_cmd640_reg_pci2;
	__put_cmd640_reg = put_cmd640_reg_pci2;
	क्रम (cmd640_key = 0xc000; cmd640_key <= 0xcf00; cmd640_key += 0x100) अणु
		अगर (match_pci_cmd640_device())
			वापस 1; /* success */
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Probe क्रम CMD640x -- vlb
 */
अटल पूर्णांक __init probe_क्रम_cmd640_vlb(व्योम)
अणु
	u8 b;

	__get_cmd640_reg = get_cmd640_reg_vlb;
	__put_cmd640_reg = put_cmd640_reg_vlb;
	cmd640_key = 0x178;
	b = get_cmd640_reg(CFR);
	अगर (b == 0xff || b == 0x00 || (b & CFR_AT_VESA_078h)) अणु
		cmd640_key = 0x78;
		b = get_cmd640_reg(CFR);
		अगर (b == 0xff || b == 0x00 || !(b & CFR_AT_VESA_078h))
			वापस 0;
	पूर्ण
	वापस 1; /* success */
पूर्ण

/*
 *  Returns 1 अगर an IDE पूर्णांकerface/drive exists at 0x170,
 *  Returns 0 otherwise.
 */
अटल पूर्णांक __init secondary_port_responding(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cmd640_lock, flags);

	outb_p(0x0a, 0x176);	/* select drive0 */
	udelay(100);
	अगर ((inb_p(0x176) & 0x1f) != 0x0a) अणु
		outb_p(0x1a, 0x176); /* select drive1 */
		udelay(100);
		अगर ((inb_p(0x176) & 0x1f) != 0x1a) अणु
			spin_unlock_irqrestore(&cmd640_lock, flags);
			वापस 0; /* nothing responded */
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&cmd640_lock, flags);
	वापस 1; /* success */
पूर्ण

#अगर_घोषित CMD640_DUMP_REGS
/*
 * Dump out all cmd640 रेजिस्टरs.  May be called from ide.c
 */
अटल व्योम cmd640_dump_regs(व्योम)
अणु
	अचिन्हित पूर्णांक reg = cmd640_vlb ? 0x50 : 0x00;

	/* Dump current state of chip रेजिस्टरs */
	prपूर्णांकk("ide: cmd640 internal register dump:");
	क्रम (; reg <= 0x59; reg++) अणु
		अगर (!(reg & 0x0f))
			prपूर्णांकk("\n%04x:", reg);
		prपूर्णांकk(" %02x", get_cmd640_reg(reg));
	पूर्ण
	prपूर्णांकk("\n");
पूर्ण
#पूर्ण_अगर

अटल व्योम __set_prefetch_mode(ide_drive_t *drive, पूर्णांक mode)
अणु
	अगर (mode) अणु	/* want prefetch on? */
#अगर CMD640_PREFETCH_MASKS
		drive->dev_flags |= IDE_DFLAG_NO_UNMASK;
		drive->dev_flags &= ~IDE_DFLAG_UNMASK;
#पूर्ण_अगर
		drive->dev_flags &= ~IDE_DFLAG_NO_IO_32BIT;
	पूर्ण अन्यथा अणु
		drive->dev_flags &= ~IDE_DFLAG_NO_UNMASK;
		drive->dev_flags |= IDE_DFLAG_NO_IO_32BIT;
		drive->io_32bit = 0;
	पूर्ण
पूर्ण

#अगर_अघोषित CONFIG_BLK_DEV_CMD640_ENHANCED
/*
 * Check whether prefetch is on क्रम a drive,
 * and initialize the unmask flags क्रम safe operation.
 */
अटल व्योम __init check_prefetch(ide_drive_t *drive, अचिन्हित पूर्णांक index)
अणु
	u8 b = get_cmd640_reg(prefetch_regs[index]);

	__set_prefetch_mode(drive, (b & prefetch_masks[index]) ? 0 : 1);
पूर्ण
#अन्यथा

/*
 * Sets prefetch mode क्रम a drive.
 */
अटल व्योम set_prefetch_mode(ide_drive_t *drive, अचिन्हित पूर्णांक index, पूर्णांक mode)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक reg = prefetch_regs[index];
	u8 b;

	spin_lock_irqsave(&cmd640_lock, flags);
	b = __get_cmd640_reg(reg);
	__set_prefetch_mode(drive, mode);
	अगर (mode)
		b &= ~prefetch_masks[index];	/* enable prefetch */
	अन्यथा
		b |= prefetch_masks[index];	/* disable prefetch */
	__put_cmd640_reg(reg, b);
	spin_unlock_irqrestore(&cmd640_lock, flags);
पूर्ण

/*
 * Dump out current drive घड़ीs settings
 */
अटल व्योम display_घड़ीs(अचिन्हित पूर्णांक index)
अणु
	u8 active_count, recovery_count;

	active_count = active_counts[index];
	अगर (active_count == 1)
		++active_count;
	recovery_count = recovery_counts[index];
	अगर (active_count > 3 && recovery_count == 1)
		++recovery_count;
	अगर (cmd640_chip_version > 1)
		recovery_count += 1;  /* cmd640b uses (count + 1)*/
	prपूर्णांकk(", clocks=%d/%d/%d\n", setup_counts[index], active_count, recovery_count);
पूर्ण

/*
 * Pack active and recovery counts पूर्णांकo single byte representation
 * used by controller
 */
अटल अंतरभूत u8 pack_nibbles(u8 upper, u8 lower)
अणु
	वापस ((upper & 0x0f) << 4) | (lower & 0x0f);
पूर्ण

/*
 * This routine ग_लिखोs the prepared setup/active/recovery counts
 * क्रम a drive पूर्णांकo the cmd640 chipset रेजिस्टरs to active them.
 */
अटल व्योम program_drive_counts(ide_drive_t *drive, अचिन्हित पूर्णांक index)
अणु
	अचिन्हित दीर्घ flags;
	u8 setup_count    = setup_counts[index];
	u8 active_count   = active_counts[index];
	u8 recovery_count = recovery_counts[index];

	/*
	 * Set up address setup count and drive पढ़ो/ग_लिखो timing रेजिस्टरs.
	 * Primary पूर्णांकerface has inभागidual count/timing रेजिस्टरs क्रम
	 * each drive.  Secondary पूर्णांकerface has one common set of रेजिस्टरs,
	 * so we merge the timings, using the slowest value क्रम each timing.
	 */
	अगर (index > 1) अणु
		ide_drive_t *peer = ide_get_pair_dev(drive);
		अचिन्हित पूर्णांक mate = index ^ 1;

		अगर (peer) अणु
			अगर (setup_count < setup_counts[mate])
				setup_count = setup_counts[mate];
			अगर (active_count < active_counts[mate])
				active_count = active_counts[mate];
			अगर (recovery_count < recovery_counts[mate])
				recovery_count = recovery_counts[mate];
		पूर्ण
	पूर्ण

	/*
	 * Convert setup_count to पूर्णांकernal chipset representation
	 */
	चयन (setup_count) अणु
	हाल 4:	 setup_count = 0x00; अवरोध;
	हाल 3:	 setup_count = 0x80; अवरोध;
	हाल 1:
	हाल 2:	 setup_count = 0x40; अवरोध;
	शेष: setup_count = 0xc0; /* हाल 5 */
	पूर्ण

	/*
	 * Now that everything is पढ़ोy, program the new timings
	 */
	spin_lock_irqsave(&cmd640_lock, flags);
	/*
	 * Program the address_setup घड़ीs पूर्णांकo ARTTIM reg,
	 * and then the active/recovery counts पूर्णांकo the DRWTIM reg
	 * (this converts counts of 16 पूर्णांकo counts of zero -- okay).
	 */
	setup_count |= __get_cmd640_reg(arttim_regs[index]) & 0x3f;
	__put_cmd640_reg(arttim_regs[index], setup_count);
	__put_cmd640_reg(drwtim_regs[index], pack_nibbles(active_count, recovery_count));
	spin_unlock_irqrestore(&cmd640_lock, flags);
पूर्ण

/*
 * Set a specअगरic pio_mode क्रम a drive
 */
अटल व्योम cmd640_set_mode(ide_drive_t *drive, अचिन्हित पूर्णांक index,
			    u8 pio_mode, अचिन्हित पूर्णांक cycle_समय)
अणु
	काष्ठा ide_timing *t;
	पूर्णांक setup_समय, active_समय, recovery_समय, घड़ी_प्रकारime;
	u8 setup_count, active_count, recovery_count, recovery_count2, cycle_count;
	पूर्णांक bus_speed;

	अगर (cmd640_vlb)
		bus_speed = ide_vlb_clk ? ide_vlb_clk : 50;
	अन्यथा
		bus_speed = ide_pci_clk ? ide_pci_clk : 33;

	अगर (pio_mode > 5)
		pio_mode = 5;

	t = ide_timing_find_mode(XFER_PIO_0 + pio_mode);
	setup_समय  = t->setup;
	active_समय = t->active;

	recovery_समय = cycle_समय - (setup_समय + active_समय);
	घड़ी_प्रकारime = 1000 / bus_speed;
	cycle_count = DIV_ROUND_UP(cycle_समय, घड़ी_प्रकारime);

	setup_count = DIV_ROUND_UP(setup_समय, घड़ी_प्रकारime);

	active_count = DIV_ROUND_UP(active_समय, घड़ी_प्रकारime);
	अगर (active_count < 2)
		active_count = 2; /* minimum allowed by cmd640 */

	recovery_count = DIV_ROUND_UP(recovery_समय, घड़ी_प्रकारime);
	recovery_count2 = cycle_count - (setup_count + active_count);
	अगर (recovery_count2 > recovery_count)
		recovery_count = recovery_count2;
	अगर (recovery_count < 2)
		recovery_count = 2; /* minimum allowed by cmd640 */
	अगर (recovery_count > 17) अणु
		active_count += recovery_count - 17;
		recovery_count = 17;
	पूर्ण
	अगर (active_count > 16)
		active_count = 16; /* maximum allowed by cmd640 */
	अगर (cmd640_chip_version > 1)
		recovery_count -= 1;  /* cmd640b uses (count + 1)*/
	अगर (recovery_count > 16)
		recovery_count = 16; /* maximum allowed by cmd640 */

	setup_counts[index]    = setup_count;
	active_counts[index]   = active_count;
	recovery_counts[index] = recovery_count;

	/*
	 * In a perfect world, we might set the drive pio mode here
	 * (using WIN_SETFEATURE) beक्रमe continuing.
	 *
	 * But we करो not, because:
	 *	1) this is the wrong place to करो it (proper is करो_special() in ide.c)
	 * 	2) in practice this is rarely, अगर ever, necessary
	 */
	program_drive_counts(drive, index);
पूर्ण

अटल व्योम cmd640_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	अचिन्हित पूर्णांक index = 0, cycle_समय;
	स्थिर u8 pio = drive->pio_mode - XFER_PIO_0;
	u8 b;

	चयन (pio) अणु
	हाल 6: /* set fast-devsel off */
	हाल 7: /* set fast-devsel on */
		b = get_cmd640_reg(CNTRL) & ~0x27;
		अगर (pio & 1)
			b |= 0x27;
		put_cmd640_reg(CNTRL, b);
		prपूर्णांकk("%s: %sabled cmd640 fast host timing (devsel)\n",
			drive->name, (pio & 1) ? "en" : "dis");
		वापस;
	हाल 8: /* set prefetch off */
	हाल 9: /* set prefetch on */
		set_prefetch_mode(drive, index, pio & 1);
		prपूर्णांकk("%s: %sabled cmd640 prefetch\n",
			drive->name, (pio & 1) ? "en" : "dis");
		वापस;
	पूर्ण

	cycle_समय = ide_pio_cycle_समय(drive, pio);
	cmd640_set_mode(drive, index, pio, cycle_समय);

	prपूर्णांकk("%s: selected cmd640 PIO mode%d (%dns)",
		drive->name, pio, cycle_समय);

	display_घड़ीs(index);
पूर्ण
#पूर्ण_अगर /* CONFIG_BLK_DEV_CMD640_ENHANCED */

अटल व्योम __init cmd640_init_dev(ide_drive_t *drive)
अणु
	अचिन्हित पूर्णांक i = drive->hwअगर->channel * 2 + (drive->dn & 1);

#अगर_घोषित CONFIG_BLK_DEV_CMD640_ENHANCED
	/*
	 * Reset timing to the slowest speed and turn off prefetch.
	 * This way, the drive identअगरy code has a better chance.
	 */
	setup_counts[i]    =  4;	/* max possible */
	active_counts[i]   = 16;	/* max possible */
	recovery_counts[i] = 16;	/* max possible */
	program_drive_counts(drive, i);
	set_prefetch_mode(drive, i, 0);
	prपूर्णांकk(KERN_INFO DRV_NAME ": drive%d timings/prefetch cleared\n", i);
#अन्यथा
	/*
	 * Set the drive unmask flags to match the prefetch setting.
	 */
	check_prefetch(drive, i);
	prपूर्णांकk(KERN_INFO DRV_NAME ": drive%d timings/prefetch(%s) preserved\n",
		i, (drive->dev_flags & IDE_DFLAG_NO_IO_32BIT) ? "off" : "on");
#पूर्ण_अगर /* CONFIG_BLK_DEV_CMD640_ENHANCED */
पूर्ण

अटल पूर्णांक cmd640_test_irq(ide_hwअगर_t *hwअगर)
अणु
	पूर्णांक irq_reg		= hwअगर->channel ? ARTTIM23 : CFR;
	u8  irq_mask		= hwअगर->channel ? ARTTIM23_IDE23INTR :
						  CFR_IDE01INTR;
	u8  irq_stat		= get_cmd640_reg(irq_reg);

	वापस (irq_stat & irq_mask) ? 1 : 0;
पूर्ण

अटल स्थिर काष्ठा ide_port_ops cmd640_port_ops = अणु
	.init_dev		= cmd640_init_dev,
#अगर_घोषित CONFIG_BLK_DEV_CMD640_ENHANCED
	.set_pio_mode		= cmd640_set_pio_mode,
#पूर्ण_अगर
	.test_irq		= cmd640_test_irq,
पूर्ण;

अटल पूर्णांक pci_conf1(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	u32 पंचांगp;

	spin_lock_irqsave(&cmd640_lock, flags);
	outb(0x01, 0xCFB);
	पंचांगp = inl(0xCF8);
	outl(0x80000000, 0xCF8);
	अगर (inl(0xCF8) == 0x80000000) अणु
		outl(पंचांगp, 0xCF8);
		spin_unlock_irqrestore(&cmd640_lock, flags);
		वापस 1;
	पूर्ण
	outl(पंचांगp, 0xCF8);
	spin_unlock_irqrestore(&cmd640_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक pci_conf2(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cmd640_lock, flags);
	outb(0x00, 0xCFB);
	outb(0x00, 0xCF8);
	outb(0x00, 0xCFA);
	अगर (inb(0xCF8) == 0x00 && inb(0xCF8) == 0x00) अणु
		spin_unlock_irqrestore(&cmd640_lock, flags);
		वापस 1;
	पूर्ण
	spin_unlock_irqrestore(&cmd640_lock, flags);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ide_port_info cmd640_port_info __initस्थिर = अणु
	.chipset		= ide_cmd640,
	.host_flags		= IDE_HFLAG_SERIALIZE |
				  IDE_HFLAG_NO_DMA |
				  IDE_HFLAG_ABUSE_PREFETCH |
				  IDE_HFLAG_ABUSE_FAST_DEVSEL,
	.port_ops		= &cmd640_port_ops,
	.pio_mask		= ATA_PIO5,
पूर्ण;

अटल पूर्णांक __init cmd640x_init_one(अचिन्हित दीर्घ base, अचिन्हित दीर्घ ctl)
अणु
	अगर (!request_region(base, 8, DRV_NAME)) अणु
		prपूर्णांकk(KERN_ERR "%s: I/O resource 0x%lX-0x%lX not free.\n",
				DRV_NAME, base, base + 7);
		वापस -EBUSY;
	पूर्ण

	अगर (!request_region(ctl, 1, DRV_NAME)) अणु
		prपूर्णांकk(KERN_ERR "%s: I/O resource 0x%lX not free.\n",
				DRV_NAME, ctl);
		release_region(base, 8);
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Probe क्रम a cmd640 chipset, and initialize it अगर found.
 */
अटल पूर्णांक __init cmd640x_init(व्योम)
अणु
	पूर्णांक second_port_cmd640 = 0, rc;
	स्थिर अक्षर *bus_type, *port2;
	u8 b, cfr;
	काष्ठा ide_hw hw[2], *hws[2];

	अगर (cmd640_vlb && probe_क्रम_cmd640_vlb()) अणु
		bus_type = "VLB";
	पूर्ण अन्यथा अणु
		cmd640_vlb = 0;
		/* Find out what kind of PCI probing is supported otherwise
		   Justin Gibbs will sulk.. */
		अगर (pci_conf1() && probe_क्रम_cmd640_pci1())
			bus_type = "PCI (type1)";
		अन्यथा अगर (pci_conf2() && probe_क्रम_cmd640_pci2())
			bus_type = "PCI (type2)";
		अन्यथा
			वापस 0;
	पूर्ण
	/*
	 * Unकरोcumented magic (there is no 0x5b reg in specs)
	 */
	put_cmd640_reg(0x5b, 0xbd);
	अगर (get_cmd640_reg(0x5b) != 0xbd) अणु
		prपूर्णांकk(KERN_ERR "ide: cmd640 init failed: wrong value in reg 0x5b\n");
		वापस 0;
	पूर्ण
	put_cmd640_reg(0x5b, 0);

#अगर_घोषित CMD640_DUMP_REGS
	cmd640_dump_regs();
#पूर्ण_अगर

	/*
	 * Documented magic begins here
	 */
	cfr = get_cmd640_reg(CFR);
	cmd640_chip_version = cfr & CFR_DEVREV;
	अगर (cmd640_chip_version == 0) अणु
		prपूर्णांकk("ide: bad cmd640 revision: %d\n", cmd640_chip_version);
		वापस 0;
	पूर्ण

	rc = cmd640x_init_one(0x1f0, 0x3f6);
	अगर (rc)
		वापस rc;

	rc = cmd640x_init_one(0x170, 0x376);
	अगर (rc) अणु
		release_region(0x3f6, 1);
		release_region(0x1f0, 8);
		वापस rc;
	पूर्ण

	स_रखो(&hw, 0, माप(hw));

	ide_std_init_ports(&hw[0], 0x1f0, 0x3f6);
	hw[0].irq = 14;

	ide_std_init_ports(&hw[1], 0x170, 0x376);
	hw[1].irq = 15;

	prपूर्णांकk(KERN_INFO "cmd640: buggy cmd640%c interface on %s, config=0x%02x"
			 "\n", 'a' + cmd640_chip_version - 1, bus_type, cfr);

	/*
	 * Initialize data क्रम primary port
	 */
	hws[0] = &hw[0];

	/*
	 * Ensure compatibility by always using the slowest timings
	 * क्रम access to the drive's command रेजिस्टर block,
	 * and reset the prefetch burstsize to शेष (512 bytes).
	 *
	 * Maybe we need a way to NOT करो these on *some* प्रणालीs?
	 */
	put_cmd640_reg(CMDTIM, 0);
	put_cmd640_reg(BRST, 0x40);

	b = get_cmd640_reg(CNTRL);

	/*
	 * Try to enable the secondary पूर्णांकerface, अगर not alपढ़ोy enabled
	 */
	अगर (secondary_port_responding()) अणु
		अगर ((b & CNTRL_ENA_2ND)) अणु
			second_port_cmd640 = 1;
			port2 = "okay";
		पूर्ण अन्यथा अगर (cmd640_vlb) अणु
			second_port_cmd640 = 1;
			port2 = "alive";
		पूर्ण अन्यथा
			port2 = "not cmd640";
	पूर्ण अन्यथा अणु
		put_cmd640_reg(CNTRL, b ^ CNTRL_ENA_2ND); /* toggle the bit */
		अगर (secondary_port_responding()) अणु
			second_port_cmd640 = 1;
			port2 = "enabled";
		पूर्ण अन्यथा अणु
			put_cmd640_reg(CNTRL, b); /* restore original setting */
			port2 = "not responding";
		पूर्ण
	पूर्ण

	/*
	 * Initialize data क्रम secondary cmd640 port, अगर enabled
	 */
	अगर (second_port_cmd640)
		hws[1] = &hw[1];

	prपूर्णांकk(KERN_INFO "cmd640: %sserialized, secondary interface %s\n",
			 second_port_cmd640 ? "" : "not ", port2);

#अगर_घोषित CMD640_DUMP_REGS
	cmd640_dump_regs();
#पूर्ण_अगर

	वापस ide_host_add(&cmd640_port_info, hws, second_port_cmd640 ? 2 : 1,
			    शून्य);
पूर्ण

module_param_named(probe_vlb, cmd640_vlb, bool, 0);
MODULE_PARM_DESC(probe_vlb, "probe for VLB version of CMD640 chipset");

module_init(cmd640x_init);

MODULE_LICENSE("GPL");
