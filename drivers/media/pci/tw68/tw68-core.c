<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  tw68-core.c
 *  Core functions क्रम the Techwell 68xx driver
 *
 *  Much of this code is derived from the cx88 and sa7134 drivers, which
 *  were in turn derived from the bt87x driver.  The original work was by
 *  Gerd Knorr; more recently the code was enhanced by Mauro Carvalho Chehab,
 *  Hans Verkuil, Andy Walls and many others.  Their work is gratefully
 *  acknowledged.  Full credit goes to them - any problems within this code
 *  are mine.
 *
 *  Copyright (C) 2009  William M. Brack
 *
 *  Refactored and updated to the latest v4l core frameworks:
 *
 *  Copyright (C) 2014 Hans Verkuil <hverkuil@xs4all.nl>
 */

#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/kmod.h>
#समावेश <linux/sound.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/pm.h>

#समावेश <media/v4l2-dev.h>
#समावेश "tw68.h"
#समावेश "tw68-reg.h"

MODULE_DESCRIPTION("v4l2 driver module for tw6800 based video capture cards");
MODULE_AUTHOR("William M. Brack");
MODULE_AUTHOR("Hans Verkuil <hverkuil@xs4all.nl>");
MODULE_LICENSE("GPL");

अटल अचिन्हित पूर्णांक latency = UNSET;
module_param(latency, पूर्णांक, 0444);
MODULE_PARM_DESC(latency, "pci latency timer");

अटल अचिन्हित पूर्णांक video_nr[] = अणु[0 ... (TW68_MAXBOARDS - 1)] = UNSET पूर्ण;
module_param_array(video_nr, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(video_nr, "video device number");

अटल अचिन्हित पूर्णांक card[] = अणु[0 ... (TW68_MAXBOARDS - 1)] = UNSET पूर्ण;
module_param_array(card, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(card, "card type");

अटल atomic_t tw68_instance = ATOMIC_INIT(0);

/* ------------------------------------------------------------------ */

/*
 * Please add any new PCI IDs to: https://pci-ids.ucw.cz.  This keeps
 * the PCI ID database up to date.  Note that the entries must be
 * added under venकरोr 0x1797 (Techwell Inc.) as subप्रणाली IDs.
 */
अटल स्थिर काष्ठा pci_device_id tw68_pci_tbl[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_TECHWELL, PCI_DEVICE_ID_TECHWELL_6800)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_TECHWELL, PCI_DEVICE_ID_TECHWELL_6801)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_TECHWELL, PCI_DEVICE_ID_TECHWELL_6804)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_TECHWELL, PCI_DEVICE_ID_TECHWELL_6816_1)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_TECHWELL, PCI_DEVICE_ID_TECHWELL_6816_2)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_TECHWELL, PCI_DEVICE_ID_TECHWELL_6816_3)पूर्ण,
	अणुPCI_DEVICE(PCI_VENDOR_ID_TECHWELL, PCI_DEVICE_ID_TECHWELL_6816_4)पूर्ण,
	अणु0,पूर्ण
पूर्ण;

/* ------------------------------------------------------------------ */


/*
 * The device is given a "soft reset". According to the specअगरications,
 * after this "all register content remain unchanged", so we also ग_लिखो
 * to all specअगरied रेजिस्टरs manually as well (mostly to manufacturer's
 * specअगरied reset values)
 */
अटल पूर्णांक tw68_hw_init1(काष्ठा tw68_dev *dev)
अणु
	/* Assure all पूर्णांकerrupts are disabled */
	tw_ग_लिखोl(TW68_INTMASK, 0);		/* 020 */
	/* Clear any pending पूर्णांकerrupts */
	tw_ग_लिखोl(TW68_INTSTAT, 0xffffffff);	/* 01C */
	/* Stop risc processor, set शेष buffer level */
	tw_ग_लिखोl(TW68_DMAC, 0x1600);

	tw_ग_लिखोb(TW68_ACNTL, 0x80);	/* 218	soft reset */
	msleep(100);

	tw_ग_लिखोb(TW68_INFORM, 0x40);	/* 208	mux0, 27mhz xtal */
	tw_ग_लिखोb(TW68_OPFORM, 0x04);	/* 20C	analog line-lock */
	tw_ग_लिखोb(TW68_HSYNC, 0);	/* 210	color-समाप्तer high sens */
	tw_ग_लिखोb(TW68_ACNTL, 0x42);	/* 218	पूर्णांक vref #2, chroma adc off */

	tw_ग_लिखोb(TW68_CROP_HI, 0x02);	/* 21C	Hactive m.s. bits */
	tw_ग_लिखोb(TW68_VDELAY_LO, 0x12);/* 220	Mfg specअगरied reset value */
	tw_ग_लिखोb(TW68_VACTIVE_LO, 0xf0);
	tw_ग_लिखोb(TW68_HDELAY_LO, 0x0f);
	tw_ग_लिखोb(TW68_HACTIVE_LO, 0xd0);

	tw_ग_लिखोb(TW68_CNTRL1, 0xcd);	/* 230	Wide Chroma BPF B/W
					 *	Secam reduction, Adap comb क्रम
					 *	NTSC, Op Mode 1 */

	tw_ग_लिखोb(TW68_VSCALE_LO, 0);	/* 234 */
	tw_ग_लिखोb(TW68_SCALE_HI, 0x11);	/* 238 */
	tw_ग_लिखोb(TW68_HSCALE_LO, 0);	/* 23c */
	tw_ग_लिखोb(TW68_BRIGHT, 0);	/* 240 */
	tw_ग_लिखोb(TW68_CONTRAST, 0x5c);	/* 244 */
	tw_ग_लिखोb(TW68_SHARPNESS, 0x51);/* 248 */
	tw_ग_लिखोb(TW68_SAT_U, 0x80);	/* 24C */
	tw_ग_लिखोb(TW68_SAT_V, 0x80);	/* 250 */
	tw_ग_लिखोb(TW68_HUE, 0x00);	/* 254 */

	/* TODO - Check that none of these are set by control शेषs */
	tw_ग_लिखोb(TW68_SHARP2, 0x53);	/* 258	Mfg specअगरied reset val */
	tw_ग_लिखोb(TW68_VSHARP, 0x80);	/* 25C	Sharpness Coring val 8 */
	tw_ग_लिखोb(TW68_CORING, 0x44);	/* 260	CTI and Vert Peak coring */
	tw_ग_लिखोb(TW68_CNTRL2, 0x00);	/* 268	No घातer saving enabled */
	tw_ग_लिखोb(TW68_SDT, 0x07);	/* 270	Enable shaकरोw reg, स्वतः-det */
	tw_ग_लिखोb(TW68_SDTR, 0x7f);	/* 274	All stds recog, करोn't start */
	tw_ग_लिखोb(TW68_CLMPG, 0x50);	/* 280	Clamp end at 40 sys घड़ीs */
	tw_ग_लिखोb(TW68_IAGC, 0x22);	/* 284	Mfg specअगरied reset val */
	tw_ग_लिखोb(TW68_AGCGAIN, 0xf0);	/* 288	AGC gain when loop disabled */
	tw_ग_लिखोb(TW68_PEAKWT, 0xd8);	/* 28C	White peak threshold */
	tw_ग_लिखोb(TW68_CLMPL, 0x3c);	/* 290	Y channel clamp level */
/*	tw_ग_लिखोb(TW68_SYNCT, 0x38);*/	/* 294	Sync amplitude */
	tw_ग_लिखोb(TW68_SYNCT, 0x30);	/* 294	Sync amplitude */
	tw_ग_लिखोb(TW68_MISSCNT, 0x44);	/* 298	Horiz sync, VCR detect sens */
	tw_ग_लिखोb(TW68_PCLAMP, 0x28);	/* 29C	Clamp pos from PLL sync */
	/* Bit DETV of VCNTL1 helps sync multi cams/chip board */
	tw_ग_लिखोb(TW68_VCNTL1, 0x04);	/* 2A0 */
	tw_ग_लिखोb(TW68_VCNTL2, 0);	/* 2A4 */
	tw_ग_लिखोb(TW68_CKILL, 0x68);	/* 2A8	Mfg specअगरied reset val */
	tw_ग_लिखोb(TW68_COMB, 0x44);	/* 2AC	Mfg specअगरied reset val */
	tw_ग_लिखोb(TW68_LDLY, 0x30);	/* 2B0	Max positive luma delay */
	tw_ग_लिखोb(TW68_MISC1, 0x14);	/* 2B4	Mfg specअगरied reset val */
	tw_ग_लिखोb(TW68_LOOP, 0xa5);	/* 2B8	Mfg specअगरied reset val */
	tw_ग_लिखोb(TW68_MISC2, 0xe0);	/* 2BC	Enable colour समाप्तer */
	tw_ग_लिखोb(TW68_MVSN, 0);	/* 2C0 */
	tw_ग_लिखोb(TW68_CLMD, 0x05);	/* 2CC	slice level स्वतः, clamp med. */
	tw_ग_लिखोb(TW68_IDCNTL, 0);	/* 2D0	Writing zero to this रेजिस्टर
					 *	selects NTSC ID detection,
					 *	but करोesn't change the
					 *	sensitivity (which has a reset
					 *	value of 1E).  Since we are
					 *	not करोing स्वतः-detection, it
					 *	has no real effect */
	tw_ग_लिखोb(TW68_CLCNTL1, 0);	/* 2D4 */
	tw_ग_लिखोl(TW68_VBIC, 0x03);	/* 010 */
	tw_ग_लिखोl(TW68_CAP_CTL, 0x03);	/* 040	Enable both even & odd flds */
	tw_ग_लिखोl(TW68_DMAC, 0x2000);	/* patch set had 0x2080 */
	tw_ग_लिखोl(TW68_TESTREG, 0);	/* 02C */

	/*
	 * Some common boards, especially inexpensive single-chip models,
	 * use the GPIO bits 0-3 to control an on-board video-output mux.
	 * For these boards, we need to set up the GPIO रेजिस्टर पूर्णांकo
	 * "normal" mode, set bits 0-3 as output, and then set those bits
	 * zero.
	 *
	 * Eventually, it would be nice अगर we could identअगरy these boards
	 * uniquely, and only करो this initialisation अगर the board has been
	 * identअगरy.  For the moment, however, it shouldn't hurt anything
	 * to करो these steps.
	 */
	tw_ग_लिखोl(TW68_GPIOC, 0);	/* Set the GPIO to "normal", no पूर्णांकs */
	tw_ग_लिखोl(TW68_GPOE, 0x0f);	/* Set bits 0-3 to "output" */
	tw_ग_लिखोl(TW68_GPDATA, 0);	/* Set all bits to low state */

	/* Initialize the device control काष्ठाures */
	mutex_init(&dev->lock);
	spin_lock_init(&dev->slock);

	/* Initialize any subप्रणालीs */
	tw68_video_init1(dev);
	वापस 0;
पूर्ण

अटल irqवापस_t tw68_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा tw68_dev *dev = dev_id;
	u32 status, orig;
	पूर्णांक loop;

	status = orig = tw_पढ़ोl(TW68_INTSTAT) & dev->pci_irqmask;
	/* Check अगर anything to करो */
	अगर (0 == status)
		वापस IRQ_NONE;	/* Nope - वापस */
	क्रम (loop = 0; loop < 10; loop++) अणु
		अगर (status & dev->board_virqmask)	/* video पूर्णांकerrupt */
			tw68_irq_video_करोne(dev, status);
		status = tw_पढ़ोl(TW68_INTSTAT) & dev->pci_irqmask;
		अगर (0 == status)
			वापस IRQ_HANDLED;
	पूर्ण
	dev_dbg(&dev->pci->dev, "%s: **** INTERRUPT NOT HANDLED - clearing mask (orig 0x%08x, cur 0x%08x)",
			dev->name, orig, tw_पढ़ोl(TW68_INTSTAT));
	dev_dbg(&dev->pci->dev, "%s: pci_irqmask 0x%08x; board_virqmask 0x%08x ****\n",
			dev->name, dev->pci_irqmask, dev->board_virqmask);
	tw_clearl(TW68_INTMASK, dev->pci_irqmask);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक tw68_initdev(काष्ठा pci_dev *pci_dev,
				     स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा tw68_dev *dev;
	पूर्णांक vidnr = -1;
	पूर्णांक err;

	dev = devm_kzalloc(&pci_dev->dev, माप(*dev), GFP_KERNEL);
	अगर (शून्य == dev)
		वापस -ENOMEM;

	dev->instance = v4l2_device_set_name(&dev->v4l2_dev, "tw68",
						&tw68_instance);

	err = v4l2_device_रेजिस्टर(&pci_dev->dev, &dev->v4l2_dev);
	अगर (err)
		वापस err;

	/* pci init */
	dev->pci = pci_dev;
	अगर (pci_enable_device(pci_dev)) अणु
		err = -EIO;
		जाओ fail1;
	पूर्ण

	dev->name = dev->v4l2_dev.name;

	अगर (UNSET != latency) अणु
		pr_info("%s: setting pci latency timer to %d\n",
		       dev->name, latency);
		pci_ग_लिखो_config_byte(pci_dev, PCI_LATENCY_TIMER, latency);
	पूर्ण

	/* prपूर्णांक pci info */
	pci_पढ़ो_config_byte(pci_dev, PCI_CLASS_REVISION, &dev->pci_rev);
	pci_पढ़ो_config_byte(pci_dev, PCI_LATENCY_TIMER,  &dev->pci_lat);
	pr_info("%s: found at %s, rev: %d, irq: %d, latency: %d, mmio: 0x%llx\n",
		dev->name, pci_name(pci_dev), dev->pci_rev, pci_dev->irq,
		dev->pci_lat, (u64)pci_resource_start(pci_dev, 0));
	pci_set_master(pci_dev);
	err = dma_set_mask(&pci_dev->dev, DMA_BIT_MASK(32));
	अगर (err) अणु
		pr_info("%s: Oops: no 32bit PCI DMA ???\n", dev->name);
		जाओ fail1;
	पूर्ण

	चयन (pci_id->device) अणु
	हाल PCI_DEVICE_ID_TECHWELL_6800:	/* TW6800 */
		dev->vdecoder = TW6800;
		dev->board_virqmask = TW68_VID_INTS;
		अवरोध;
	हाल PCI_DEVICE_ID_TECHWELL_6801:	/* Video decoder क्रम TW6802 */
		dev->vdecoder = TW6801;
		dev->board_virqmask = TW68_VID_INTS | TW68_VID_INTSX;
		अवरोध;
	हाल PCI_DEVICE_ID_TECHWELL_6804:	/* Video decoder क्रम TW6804 */
		dev->vdecoder = TW6804;
		dev->board_virqmask = TW68_VID_INTS | TW68_VID_INTSX;
		अवरोध;
	शेष:
		dev->vdecoder = TWXXXX;	/* To be announced */
		dev->board_virqmask = TW68_VID_INTS | TW68_VID_INTSX;
		अवरोध;
	पूर्ण

	/* get mmio */
	अगर (!request_mem_region(pci_resource_start(pci_dev, 0),
				pci_resource_len(pci_dev, 0),
				dev->name)) अणु
		err = -EBUSY;
		pr_err("%s: can't get MMIO memory @ 0x%llx\n",
			dev->name,
			(अचिन्हित दीर्घ दीर्घ)pci_resource_start(pci_dev, 0));
		जाओ fail1;
	पूर्ण
	dev->lmmio = ioremap(pci_resource_start(pci_dev, 0),
			     pci_resource_len(pci_dev, 0));
	dev->bmmio = (__u8 __iomem *)dev->lmmio;
	अगर (शून्य == dev->lmmio) अणु
		err = -EIO;
		pr_err("%s: can't ioremap() MMIO memory\n",
		       dev->name);
		जाओ fail2;
	पूर्ण
	/* initialize hardware #1 */
	/* Then करो any initialisation wanted beक्रमe पूर्णांकerrupts are on */
	tw68_hw_init1(dev);

	/* get irq */
	err = devm_request_irq(&pci_dev->dev, pci_dev->irq, tw68_irq,
			  IRQF_SHARED, dev->name, dev);
	अगर (err < 0) अणु
		pr_err("%s: can't get IRQ %d\n",
		       dev->name, pci_dev->irq);
		जाओ fail3;
	पूर्ण

	/*
	 *  Now करो reमुख्यder of initialisation, first क्रम
	 *  things unique क्रम this card, then क्रम general board
	 */
	अगर (dev->instance < TW68_MAXBOARDS)
		vidnr = video_nr[dev->instance];
	/* initialise video function first */
	err = tw68_video_init2(dev, vidnr);
	अगर (err < 0) अणु
		pr_err("%s: can't register video device\n",
		       dev->name);
		जाओ fail4;
	पूर्ण
	tw_setl(TW68_INTMASK, dev->pci_irqmask);

	pr_info("%s: registered device %s\n",
	       dev->name, video_device_node_name(&dev->vdev));

	वापस 0;

fail4:
	video_unरेजिस्टर_device(&dev->vdev);
fail3:
	iounmap(dev->lmmio);
fail2:
	release_mem_region(pci_resource_start(pci_dev, 0),
			   pci_resource_len(pci_dev, 0));
fail1:
	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
	वापस err;
पूर्ण

अटल व्योम tw68_finidev(काष्ठा pci_dev *pci_dev)
अणु
	काष्ठा v4l2_device *v4l2_dev = pci_get_drvdata(pci_dev);
	काष्ठा tw68_dev *dev =
		container_of(v4l2_dev, काष्ठा tw68_dev, v4l2_dev);

	/* shutकरोwn subप्रणालीs */
	tw_clearl(TW68_DMAC, TW68_DMAP_EN | TW68_FIFO_EN);
	tw_ग_लिखोl(TW68_INTMASK, 0);

	/* unरेजिस्टर */
	video_unरेजिस्टर_device(&dev->vdev);
	v4l2_ctrl_handler_मुक्त(&dev->hdl);

	/* release resources */
	iounmap(dev->lmmio);
	release_mem_region(pci_resource_start(pci_dev, 0),
			   pci_resource_len(pci_dev, 0));

	v4l2_device_unरेजिस्टर(&dev->v4l2_dev);
पूर्ण

अटल पूर्णांक __maybe_unused tw68_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा pci_dev *pci_dev = to_pci_dev(dev_d);
	काष्ठा v4l2_device *v4l2_dev = pci_get_drvdata(pci_dev);
	काष्ठा tw68_dev *dev = container_of(v4l2_dev,
				काष्ठा tw68_dev, v4l2_dev);

	tw_clearl(TW68_DMAC, TW68_DMAP_EN | TW68_FIFO_EN);
	dev->pci_irqmask &= ~TW68_VID_INTS;
	tw_ग_लिखोl(TW68_INTMASK, 0);

	synchronize_irq(pci_dev->irq);

	vb2_discard_करोne(&dev->vidq);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tw68_resume(काष्ठा device *dev_d)
अणु
	काष्ठा v4l2_device *v4l2_dev = dev_get_drvdata(dev_d);
	काष्ठा tw68_dev *dev = container_of(v4l2_dev,
					    काष्ठा tw68_dev, v4l2_dev);
	काष्ठा tw68_buf *buf;
	अचिन्हित दीर्घ flags;

	/* Do things that are करोne in tw68_initdev ,
		except of initializing memory काष्ठाures.*/

	msleep(100);

	tw68_set_tvnorm_hw(dev);

	/*resume unfinished buffer(s)*/
	spin_lock_irqsave(&dev->slock, flags);
	buf = container_of(dev->active.next, काष्ठा tw68_buf, list);

	tw68_video_start_dma(dev, buf);

	spin_unlock_irqrestore(&dev->slock, flags);

	वापस 0;
पूर्ण

/* ----------------------------------------------------------- */

अटल SIMPLE_DEV_PM_OPS(tw68_pm_ops, tw68_suspend, tw68_resume);

अटल काष्ठा pci_driver tw68_pci_driver = अणु
	.name	   = "tw68",
	.id_table  = tw68_pci_tbl,
	.probe	   = tw68_initdev,
	.हटाओ	   = tw68_finidev,
	.driver.pm = &tw68_pm_ops,
पूर्ण;

module_pci_driver(tw68_pci_driver);
