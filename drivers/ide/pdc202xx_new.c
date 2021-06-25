<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Promise TX2/TX4/TX2000/133 IDE driver
 *
 *  Split from:
 *  linux/drivers/ide/pdc202xx.c	Version 0.35	Mar. 30, 2002
 *  Copyright (C) 1998-2002		Andre Hedrick <andre@linux-ide.org>
 *  Copyright (C) 2005-2007		MontaVista Software, Inc.
 *  Portions Copyright (C) 1999 Promise Technology, Inc.
 *  Author: Frank Tiernan (frankt@promise.com)
 *  Released under terms of General Public License
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/ide.h>
#समावेश <linux/kसमय.स>

#समावेश <यंत्र/पन.स>

#अगर_घोषित CONFIG_PPC_PMAC
#समावेश <यंत्र/prom.h>
#पूर्ण_अगर

#घोषणा DRV_NAME "pdc202xx_new"

#अघोषित DEBUG

#अगर_घोषित DEBUG
#घोषणा DBG(fmt, args...) prपूर्णांकk("%s: " fmt, __func__, ## args)
#अन्यथा
#घोषणा DBG(fmt, args...)
#पूर्ण_अगर

अटल u8 max_dma_rate(काष्ठा pci_dev *pdev)
अणु
	u8 mode;

	चयन(pdev->device) अणु
		हाल PCI_DEVICE_ID_PROMISE_20277:
		हाल PCI_DEVICE_ID_PROMISE_20276:
		हाल PCI_DEVICE_ID_PROMISE_20275:
		हाल PCI_DEVICE_ID_PROMISE_20271:
		हाल PCI_DEVICE_ID_PROMISE_20269:
			mode = 4;
			अवरोध;
		हाल PCI_DEVICE_ID_PROMISE_20270:
		हाल PCI_DEVICE_ID_PROMISE_20268:
			mode = 3;
			अवरोध;
		शेष:
			वापस 0;
	पूर्ण

	वापस mode;
पूर्ण

/**
 * get_indexed_reg - Get indexed रेजिस्टर
 * @hwअगर: क्रम the port address
 * @index: index of the indexed रेजिस्टर
 */
अटल u8 get_indexed_reg(ide_hwअगर_t *hwअगर, u8 index)
अणु
	u8 value;

	outb(index, hwअगर->dma_base + 1);
	value = inb(hwअगर->dma_base + 3);

	DBG("index[%02X] value[%02X]\n", index, value);
	वापस value;
पूर्ण

/**
 * set_indexed_reg - Set indexed रेजिस्टर
 * @hwअगर: क्रम the port address
 * @index: index of the indexed रेजिस्टर
 */
अटल व्योम set_indexed_reg(ide_hwअगर_t *hwअगर, u8 index, u8 value)
अणु
	outb(index, hwअगर->dma_base + 1);
	outb(value, hwअगर->dma_base + 3);
	DBG("index[%02X] value[%02X]\n", index, value);
पूर्ण

/*
 * ATA Timing Tables based on 133 MHz PLL output घड़ी.
 *
 * If the PLL outमाला_दो 100 MHz घड़ी, the ASIC hardware will set
 * the timing रेजिस्टरs स्वतःmatically when "set features" command is
 * issued to the device. However, अगर the PLL output घड़ी is 133 MHz,
 * the following tables must be used.
 */
अटल काष्ठा pio_timing अणु
	u8 reg0c, reg0d, reg13;
पूर्ण pio_timings [] = अणु
	अणु 0xfb, 0x2b, 0xac पूर्ण,	/* PIO mode 0, IORDY off, Prefetch off */
	अणु 0x46, 0x29, 0xa4 पूर्ण,	/* PIO mode 1, IORDY off, Prefetch off */
	अणु 0x23, 0x26, 0x64 पूर्ण,	/* PIO mode 2, IORDY off, Prefetch off */
	अणु 0x27, 0x0d, 0x35 पूर्ण,	/* PIO mode 3, IORDY on,  Prefetch off */
	अणु 0x23, 0x09, 0x25 पूर्ण,	/* PIO mode 4, IORDY on,  Prefetch off */
पूर्ण;

अटल काष्ठा mwdma_timing अणु
	u8 reg0e, reg0f;
पूर्ण mwdma_timings [] = अणु
	अणु 0xdf, 0x5f पूर्ण, 	/* MWDMA mode 0 */
	अणु 0x6b, 0x27 पूर्ण, 	/* MWDMA mode 1 */
	अणु 0x69, 0x25 पूर्ण, 	/* MWDMA mode 2 */
पूर्ण;

अटल काष्ठा udma_timing अणु
	u8 reg10, reg11, reg12;
पूर्ण udma_timings [] = अणु
	अणु 0x4a, 0x0f, 0xd5 पूर्ण,	/* UDMA mode 0 */
	अणु 0x3a, 0x0a, 0xd0 पूर्ण,	/* UDMA mode 1 */
	अणु 0x2a, 0x07, 0xcd पूर्ण,	/* UDMA mode 2 */
	अणु 0x1a, 0x05, 0xcd पूर्ण,	/* UDMA mode 3 */
	अणु 0x1a, 0x03, 0xcd पूर्ण,	/* UDMA mode 4 */
	अणु 0x1a, 0x02, 0xcb पूर्ण,	/* UDMA mode 5 */
	अणु 0x1a, 0x01, 0xcb पूर्ण,	/* UDMA mode 6 */
पूर्ण;

अटल व्योम pdcnew_set_dma_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	काष्ठा pci_dev *dev	= to_pci_dev(hwअगर->dev);
	u8 adj			= (drive->dn & 1) ? 0x08 : 0x00;
	स्थिर u8 speed		= drive->dma_mode;

	/*
	 * IDE core issues SETFEATURES_XFER to the drive first (thanks to
	 * IDE_HFLAG_POST_SET_MODE in ->host_flags).  PDC202xx hardware will
	 * स्वतःmatically set the timing रेजिस्टरs based on 100 MHz PLL output.
	 *
	 * As we set up the PLL to output 133 MHz क्रम UltraDMA/133 capable
	 * chips, we must override the शेष रेजिस्टर settings...
	 */
	अगर (max_dma_rate(dev) == 4) अणु
		u8 mode = speed & 0x07;

		अगर (speed >= XFER_UDMA_0) अणु
			set_indexed_reg(hwअगर, 0x10 + adj,
					udma_timings[mode].reg10);
			set_indexed_reg(hwअगर, 0x11 + adj,
					udma_timings[mode].reg11);
			set_indexed_reg(hwअगर, 0x12 + adj,
					udma_timings[mode].reg12);
		पूर्ण अन्यथा अणु
			set_indexed_reg(hwअगर, 0x0e + adj,
					mwdma_timings[mode].reg0e);
			set_indexed_reg(hwअगर, 0x0f + adj,
					mwdma_timings[mode].reg0f);
		पूर्ण
	पूर्ण अन्यथा अगर (speed == XFER_UDMA_2) अणु
		/* Set tHOLD bit to 0 अगर using UDMA mode 2 */
		u8 पंचांगp = get_indexed_reg(hwअगर, 0x10 + adj);

		set_indexed_reg(hwअगर, 0x10 + adj, पंचांगp & 0x7f);
 	पूर्ण
पूर्ण

अटल व्योम pdcnew_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);
	u8 adj = (drive->dn & 1) ? 0x08 : 0x00;
	स्थिर u8 pio = drive->pio_mode - XFER_PIO_0;

	अगर (max_dma_rate(dev) == 4) अणु
		set_indexed_reg(hwअगर, 0x0c + adj, pio_timings[pio].reg0c);
		set_indexed_reg(hwअगर, 0x0d + adj, pio_timings[pio].reg0d);
		set_indexed_reg(hwअगर, 0x13 + adj, pio_timings[pio].reg13);
	पूर्ण
पूर्ण

अटल u8 pdcnew_cable_detect(ide_hwअगर_t *hwअगर)
अणु
	अगर (get_indexed_reg(hwअगर, 0x0b) & 0x04)
		वापस ATA_CBL_PATA40;
	अन्यथा
		वापस ATA_CBL_PATA80;
पूर्ण

अटल व्योम pdcnew_reset(ide_drive_t *drive)
अणु
	/*
	 * Deleted this because it is redundant from the caller.
	 */
	prपूर्णांकk(KERN_WARNING "pdc202xx_new: %s channel reset.\n",
		drive->hwअगर->channel ? "Secondary" : "Primary");
पूर्ण

/**
 * पढ़ो_counter - Read the byte count रेजिस्टरs
 * @dma_base: क्रम the port address
 */
अटल दीर्घ पढ़ो_counter(u32 dma_base)
अणु
	u32  pri_dma_base = dma_base, sec_dma_base = dma_base + 0x08;
	u8   cnt0, cnt1, cnt2, cnt3;
	दीर्घ count = 0, last;
	पूर्णांक  retry = 3;

	करो अणु
		last = count;

		/* Read the current count */
		outb(0x20, pri_dma_base + 0x01);
		cnt0 = inb(pri_dma_base + 0x03);
		outb(0x21, pri_dma_base + 0x01);
		cnt1 = inb(pri_dma_base + 0x03);
		outb(0x20, sec_dma_base + 0x01);
		cnt2 = inb(sec_dma_base + 0x03);
		outb(0x21, sec_dma_base + 0x01);
		cnt3 = inb(sec_dma_base + 0x03);

		count = (cnt3 << 23) | (cnt2 << 15) | (cnt1 << 8) | cnt0;

		/*
		 * The 30-bit decrementing counter is पढ़ो in 4 pieces.
		 * Incorrect value may be पढ़ो when the most signअगरicant bytes
		 * are changing...
		 */
	पूर्ण जबतक (retry-- && (((last ^ count) & 0x3fff8000) || last < count));

	DBG("cnt0[%02X] cnt1[%02X] cnt2[%02X] cnt3[%02X]\n",
		  cnt0, cnt1, cnt2, cnt3);

	वापस count;
पूर्ण

/**
 * detect_pll_input_घड़ी - Detect the PLL input घड़ी in Hz.
 * @dma_base: क्रम the port address
 * E.g. 16949000 on 33 MHz PCI bus, i.e. half of the PCI घड़ी.
 */
अटल दीर्घ detect_pll_input_घड़ी(अचिन्हित दीर्घ dma_base)
अणु
	kसमय_प्रकार start_समय, end_समय;
	दीर्घ start_count, end_count;
	दीर्घ pll_input, usec_elapsed;
	u8 scr1;

	start_count = पढ़ो_counter(dma_base);
	start_समय = kसमय_get();

	/* Start the test mode */
	outb(0x01, dma_base + 0x01);
	scr1 = inb(dma_base + 0x03);
	DBG("scr1[%02X]\n", scr1);
	outb(scr1 | 0x40, dma_base + 0x03);

	/* Let the counter run क्रम 10 ms. */
	mdelay(10);

	end_count = पढ़ो_counter(dma_base);
	end_समय = kसमय_get();

	/* Stop the test mode */
	outb(0x01, dma_base + 0x01);
	scr1 = inb(dma_base + 0x03);
	DBG("scr1[%02X]\n", scr1);
	outb(scr1 & ~0x40, dma_base + 0x03);

	/*
	 * Calculate the input घड़ी in Hz
	 * (the घड़ी counter is 30 bit wide and counts करोwn)
	 */
	usec_elapsed = kसमय_us_delta(end_समय, start_समय);
	pll_input = ((start_count - end_count) & 0x3fffffff) / 10 *
		(10000000 / usec_elapsed);

	DBG("start[%ld] end[%ld]\n", start_count, end_count);

	वापस pll_input;
पूर्ण

#अगर_घोषित CONFIG_PPC_PMAC
अटल व्योम apple_kiwi_init(काष्ठा pci_dev *pdev)
अणु
	काष्ठा device_node *np = pci_device_to_OF_node(pdev);
	u8 conf;

	अगर (np == शून्य || !of_device_is_compatible(np, "kiwi-root"))
		वापस;

	अगर (pdev->revision >= 0x03) अणु
		/* Setup chip magic config stuff (from darwin) */
		pci_पढ़ो_config_byte (pdev, 0x40, &conf);
		pci_ग_लिखो_config_byte(pdev, 0x40, (conf | 0x01));
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_PMAC */

अटल पूर्णांक init_chipset_pdcnew(काष्ठा pci_dev *dev)
अणु
	स्थिर अक्षर *name = DRV_NAME;
	अचिन्हित दीर्घ dma_base = pci_resource_start(dev, 4);
	अचिन्हित दीर्घ sec_dma_base = dma_base + 0x08;
	दीर्घ pll_input, pll_output, ratio;
	पूर्णांक f, r;
	u8 pll_ctl0, pll_ctl1;

	अगर (dma_base == 0)
		वापस -EFAULT;

#अगर_घोषित CONFIG_PPC_PMAC
	apple_kiwi_init(dev);
#पूर्ण_अगर

	/* Calculate the required PLL output frequency */
	चयन(max_dma_rate(dev)) अणु
		हाल 4: /* it's 133 MHz क्रम Ultra133 chips */
			pll_output = 133333333;
			अवरोध;
		हाल 3: /* and  100 MHz क्रम Ultra100 chips */
		शेष:
			pll_output = 100000000;
			अवरोध;
	पूर्ण

	/*
	 * Detect PLL input घड़ी.
	 * On some प्रणालीs, where PCI bus is running at non-standard घड़ी rate
	 * (e.g. 25 or 40 MHz), we have to adjust the cycle समय.
	 * PDC20268 and newer chips employ PLL circuit to help correct timing
	 * रेजिस्टरs setting.
	 */
	pll_input = detect_pll_input_घड़ी(dma_base);
	prपूर्णांकk(KERN_INFO "%s %s: PLL input clock is %ld kHz\n",
		name, pci_name(dev), pll_input / 1000);

	/* Sanity check */
	अगर (unlikely(pll_input < 5000000L || pll_input > 70000000L)) अणु
		prपूर्णांकk(KERN_ERR "%s %s: Bad PLL input clock %ld Hz, giving up!"
			"\n", name, pci_name(dev), pll_input);
		जाओ out;
	पूर्ण

#अगर_घोषित DEBUG
	DBG("pll_output is %ld Hz\n", pll_output);

	/* Show the current घड़ी value of PLL control रेजिस्टर
	 * (maybe alपढ़ोy configured by the BIOS)
	 */
	outb(0x02, sec_dma_base + 0x01);
	pll_ctl0 = inb(sec_dma_base + 0x03);
	outb(0x03, sec_dma_base + 0x01);
	pll_ctl1 = inb(sec_dma_base + 0x03);

	DBG("pll_ctl[%02X][%02X]\n", pll_ctl0, pll_ctl1);
#पूर्ण_अगर

	/*
	 * Calculate the ratio of F, R and NO
	 * POUT = (F + 2) / (( R + 2) * NO)
	 */
	ratio = pll_output / (pll_input / 1000);
	अगर (ratio < 8600L) अणु /* 8.6x */
		/* Using NO = 0x01, R = 0x0d */
		r = 0x0d;
	पूर्ण अन्यथा अगर (ratio < 12900L) अणु /* 12.9x */
		/* Using NO = 0x01, R = 0x08 */
		r = 0x08;
	पूर्ण अन्यथा अगर (ratio < 16100L) अणु /* 16.1x */
		/* Using NO = 0x01, R = 0x06 */
		r = 0x06;
	पूर्ण अन्यथा अगर (ratio < 64000L) अणु /* 64x */
		r = 0x00;
	पूर्ण अन्यथा अणु
		/* Invalid ratio */
		prपूर्णांकk(KERN_ERR "%s %s: Bad ratio %ld, giving up!\n",
			name, pci_name(dev), ratio);
		जाओ out;
	पूर्ण

	f = (ratio * (r + 2)) / 1000 - 2;

	DBG("F[%d] R[%d] ratio*1000[%ld]\n", f, r, ratio);

	अगर (unlikely(f < 0 || f > 127)) अणु
		/* Invalid F */
		prपूर्णांकk(KERN_ERR "%s %s: F[%d] invalid!\n",
			name, pci_name(dev), f);
		जाओ out;
	पूर्ण

	pll_ctl0 = (u8) f;
	pll_ctl1 = (u8) r;

	DBG("Writing pll_ctl[%02X][%02X]\n", pll_ctl0, pll_ctl1);

	outb(0x02,     sec_dma_base + 0x01);
	outb(pll_ctl0, sec_dma_base + 0x03);
	outb(0x03,     sec_dma_base + 0x01);
	outb(pll_ctl1, sec_dma_base + 0x03);

	/* Wait the PLL circuit to be stable */
	mdelay(30);

#अगर_घोषित DEBUG
	/*
	 *  Show the current घड़ी value of PLL control रेजिस्टर
	 */
	outb(0x02, sec_dma_base + 0x01);
	pll_ctl0 = inb(sec_dma_base + 0x03);
	outb(0x03, sec_dma_base + 0x01);
	pll_ctl1 = inb(sec_dma_base + 0x03);

	DBG("pll_ctl[%02X][%02X]\n", pll_ctl0, pll_ctl1);
#पूर्ण_अगर

 out:
	वापस 0;
पूर्ण

अटल काष्ठा pci_dev *pdc20270_get_dev2(काष्ठा pci_dev *dev)
अणु
	काष्ठा pci_dev *dev2;

	dev2 = pci_get_slot(dev->bus, PCI_DEVFN(PCI_SLOT(dev->devfn) + 1,
						PCI_FUNC(dev->devfn)));

	अगर (dev2 &&
	    dev2->venकरोr == dev->venकरोr &&
	    dev2->device == dev->device) अणु

		अगर (dev2->irq != dev->irq) अणु
			dev2->irq = dev->irq;
			prपूर्णांकk(KERN_INFO DRV_NAME " %s: PCI config space "
				"interrupt fixed\n", pci_name(dev));
		पूर्ण

		वापस dev2;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा ide_port_ops pdcnew_port_ops = अणु
	.set_pio_mode		= pdcnew_set_pio_mode,
	.set_dma_mode		= pdcnew_set_dma_mode,
	.resetproc		= pdcnew_reset,
	.cable_detect		= pdcnew_cable_detect,
पूर्ण;

#घोषणा DECLARE_PDCNEW_DEV(udma) \
	अणु \
		.name		= DRV_NAME, \
		.init_chipset	= init_chipset_pdcnew, \
		.port_ops	= &pdcnew_port_ops, \
		.host_flags	= IDE_HFLAG_POST_SET_MODE | \
				  IDE_HFLAG_ERROR_STOPS_FIFO | \
				  IDE_HFLAG_OFF_BOARD, \
		.pio_mask	= ATA_PIO4, \
		.mwdma_mask	= ATA_MWDMA2, \
		.udma_mask	= udma, \
	पूर्ण

अटल स्थिर काष्ठा ide_port_info pdcnew_chipsets[] = अणु
	/* 0: PDC202अणु68,70पूर्ण */		DECLARE_PDCNEW_DEV(ATA_UDMA5),
	/* 1: PDC202अणु69,71,75,76,77पूर्ण */	DECLARE_PDCNEW_DEV(ATA_UDMA6),
पूर्ण;

/**
 *	pdc202new_init_one	-	called when a pdc202xx is found
 *	@dev: the pdc202new device
 *	@id: the matching pci id
 *
 *	Called when the PCI registration layer (or the IDE initialization)
 *	finds a device matching our IDE device tables.
 */
 
अटल पूर्णांक pdc202new_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	स्थिर काष्ठा ide_port_info *d = &pdcnew_chipsets[id->driver_data];
	काष्ठा pci_dev *bridge = dev->bus->self;

	अगर (dev->device == PCI_DEVICE_ID_PROMISE_20270 && bridge &&
	    bridge->venकरोr == PCI_VENDOR_ID_DEC &&
	    bridge->device == PCI_DEVICE_ID_DEC_21150) अणु
		काष्ठा pci_dev *dev2;

		अगर (PCI_SLOT(dev->devfn) & 2)
			वापस -ENODEV;

		dev2 = pdc20270_get_dev2(dev);

		अगर (dev2) अणु
			पूर्णांक ret = ide_pci_init_two(dev, dev2, d, शून्य);
			अगर (ret < 0)
				pci_dev_put(dev2);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (dev->device == PCI_DEVICE_ID_PROMISE_20276 && bridge &&
	    bridge->venकरोr == PCI_VENDOR_ID_INTEL &&
	    (bridge->device == PCI_DEVICE_ID_INTEL_I960 ||
	     bridge->device == PCI_DEVICE_ID_INTEL_I960RM)) अणु
		prपूर्णांकk(KERN_INFO DRV_NAME " %s: attached to I2O RAID controller,"
			" skipping\n", pci_name(dev));
		वापस -ENODEV;
	पूर्ण

	वापस ide_pci_init_one(dev, d, शून्य);
पूर्ण

अटल व्योम pdc202new_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा ide_host *host = pci_get_drvdata(dev);
	काष्ठा pci_dev *dev2 = host->dev[1] ? to_pci_dev(host->dev[1]) : शून्य;

	ide_pci_हटाओ(dev);
	pci_dev_put(dev2);
पूर्ण

अटल स्थिर काष्ठा pci_device_id pdc202new_pci_tbl[] = अणु
	अणु PCI_VDEVICE(PROMISE, PCI_DEVICE_ID_PROMISE_20268), 0 पूर्ण,
	अणु PCI_VDEVICE(PROMISE, PCI_DEVICE_ID_PROMISE_20269), 1 पूर्ण,
	अणु PCI_VDEVICE(PROMISE, PCI_DEVICE_ID_PROMISE_20270), 0 पूर्ण,
	अणु PCI_VDEVICE(PROMISE, PCI_DEVICE_ID_PROMISE_20271), 1 पूर्ण,
	अणु PCI_VDEVICE(PROMISE, PCI_DEVICE_ID_PROMISE_20275), 1 पूर्ण,
	अणु PCI_VDEVICE(PROMISE, PCI_DEVICE_ID_PROMISE_20276), 1 पूर्ण,
	अणु PCI_VDEVICE(PROMISE, PCI_DEVICE_ID_PROMISE_20277), 1 पूर्ण,
	अणु 0, पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(pci, pdc202new_pci_tbl);

अटल काष्ठा pci_driver pdc202new_pci_driver = अणु
	.name		= "Promise_IDE",
	.id_table	= pdc202new_pci_tbl,
	.probe		= pdc202new_init_one,
	.हटाओ		= pdc202new_हटाओ,
	.suspend	= ide_pci_suspend,
	.resume		= ide_pci_resume,
पूर्ण;

अटल पूर्णांक __init pdc202new_ide_init(व्योम)
अणु
	वापस ide_pci_रेजिस्टर_driver(&pdc202new_pci_driver);
पूर्ण

अटल व्योम __निकास pdc202new_ide_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&pdc202new_pci_driver);
पूर्ण

module_init(pdc202new_ide_init);
module_निकास(pdc202new_ide_निकास);

MODULE_AUTHOR("Andre Hedrick, Frank Tiernan");
MODULE_DESCRIPTION("PCI driver module for Promise PDC20268 and higher");
MODULE_LICENSE("GPL");
