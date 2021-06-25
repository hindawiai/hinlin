<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * bt878.c: part of the driver क्रम the Pinnacle PCTV Sat DVB PCI card
 *
 * Copyright (C) 2002 Peter Hettkamp <peter.hettkamp@htp-tel.de>
 *
 * large parts based on the bttv driver
 * Copyright (C) 1996,97,98 Ralph  Metzler (rjkm@metzlerbros.de)
 *                        & Marcus Metzler (mocm@metzlerbros.de)
 * (c) 1999,2000 Gerd Knorr <kraxel@goldbach.in-berlin.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/ioport.h>
#समावेश <यंत्र/page.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kmod.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/init.h>

#समावेश <media/dmxdev.h>
#समावेश <media/dvbdev.h>
#समावेश "bt878.h"
#समावेश "dst_priv.h"


/**************************************/
/* Miscellaneous utility  definitions */
/**************************************/

अटल अचिन्हित पूर्णांक bt878_verbose = 1;
अटल अचिन्हित पूर्णांक bt878_debug;

module_param_named(verbose, bt878_verbose, पूर्णांक, 0444);
MODULE_PARM_DESC(verbose,
		 "verbose startup messages, default is 1 (yes)");
module_param_named(debug, bt878_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off debugging, default is 0 (off).");

पूर्णांक bt878_num;
काष्ठा bt878 bt878[BT878_MAX];

EXPORT_SYMBOL(bt878_num);
EXPORT_SYMBOL(bt878);

#घोषणा btग_लिखो(dat,adr)    bmtग_लिखो((dat), (bt->bt878_mem+(adr)))
#घोषणा btपढ़ो(adr)         bmtपढ़ो(bt->bt878_mem+(adr))

#घोषणा btand(dat,adr)      btग_लिखो((dat) & btपढ़ो(adr), adr)
#घोषणा btor(dat,adr)       btग_लिखो((dat) | btपढ़ो(adr), adr)
#घोषणा btaor(dat,mask,adr) btग_लिखो((dat) | ((mask) & btपढ़ो(adr)), adr)

#अगर defined(dprपूर्णांकk)
#अघोषित dprपूर्णांकk
#पूर्ण_अगर
#घोषणा dprपूर्णांकk(fmt, arg...) \
	करो अणु \
		अगर (bt878_debug) \
			prपूर्णांकk(KERN_DEBUG fmt, ##arg); \
	पूर्ण जबतक (0)

अटल व्योम bt878_mem_मुक्त(काष्ठा bt878 *bt)
अणु
	अगर (bt->buf_cpu) अणु
		dma_मुक्त_coherent(&bt->dev->dev, bt->buf_size, bt->buf_cpu,
				  bt->buf_dma);
		bt->buf_cpu = शून्य;
	पूर्ण

	अगर (bt->risc_cpu) अणु
		dma_मुक्त_coherent(&bt->dev->dev, bt->risc_size, bt->risc_cpu,
				  bt->risc_dma);
		bt->risc_cpu = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक bt878_mem_alloc(काष्ठा bt878 *bt)
अणु
	अगर (!bt->buf_cpu) अणु
		bt->buf_size = 128 * 1024;

		bt->buf_cpu = dma_alloc_coherent(&bt->dev->dev, bt->buf_size,
						 &bt->buf_dma, GFP_KERNEL);
		अगर (!bt->buf_cpu)
			वापस -ENOMEM;
	पूर्ण

	अगर (!bt->risc_cpu) अणु
		bt->risc_size = PAGE_SIZE;
		bt->risc_cpu = dma_alloc_coherent(&bt->dev->dev, bt->risc_size,
						  &bt->risc_dma, GFP_KERNEL);
		अगर (!bt->risc_cpu) अणु
			bt878_mem_मुक्त(bt);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* RISC inकाष्ठाions */
#घोषणा RISC_WRITE		(0x01 << 28)
#घोषणा RISC_JUMP		(0x07 << 28)
#घोषणा RISC_SYNC		(0x08 << 28)

/* RISC bits */
#घोषणा RISC_WR_SOL		(1 << 27)
#घोषणा RISC_WR_EOL		(1 << 26)
#घोषणा RISC_IRQ		(1 << 24)
#घोषणा RISC_STATUS(status)	((((~status) & 0x0F) << 20) | ((status & 0x0F) << 16))
#घोषणा RISC_SYNC_RESYNC	(1 << 15)
#घोषणा RISC_SYNC_FM1		0x06
#घोषणा RISC_SYNC_VRO		0x0C

#घोषणा RISC_FLUSH()		bt->risc_pos = 0
#घोषणा RISC_INSTR(instr)	bt->risc_cpu[bt->risc_pos++] = cpu_to_le32(instr)

अटल पूर्णांक bt878_make_risc(काष्ठा bt878 *bt)
अणु
	bt->block_bytes = bt->buf_size >> 4;
	bt->block_count = 1 << 4;
	bt->line_bytes = bt->block_bytes;
	bt->line_count = bt->block_count;

	जबतक (bt->line_bytes > 4095) अणु
		bt->line_bytes >>= 1;
		bt->line_count <<= 1;
	पूर्ण

	अगर (bt->line_count > 255) अणु
		prपूर्णांकk(KERN_ERR "bt878: buffer size error!\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण


अटल व्योम bt878_risc_program(काष्ठा bt878 *bt, u32 op_sync_orin)
अणु
	u32 buf_pos = 0;
	u32 line;

	RISC_FLUSH();
	RISC_INSTR(RISC_SYNC | RISC_SYNC_FM1 | op_sync_orin);
	RISC_INSTR(0);

	dprपूर्णांकk("bt878: risc len lines %u, bytes per line %u\n",
			bt->line_count, bt->line_bytes);
	क्रम (line = 0; line < bt->line_count; line++) अणु
		// At the beginning of every block we issue an IRQ with previous (finished) block number set
		अगर (!(buf_pos % bt->block_bytes))
			RISC_INSTR(RISC_WRITE | RISC_WR_SOL | RISC_WR_EOL |
				   RISC_IRQ |
				   RISC_STATUS(((buf_pos /
						 bt->block_bytes) +
						(bt->block_count -
						 1)) %
					       bt->block_count) | bt->
				   line_bytes);
		अन्यथा
			RISC_INSTR(RISC_WRITE | RISC_WR_SOL | RISC_WR_EOL |
				   bt->line_bytes);
		RISC_INSTR(bt->buf_dma + buf_pos);
		buf_pos += bt->line_bytes;
	पूर्ण

	RISC_INSTR(RISC_SYNC | op_sync_orin | RISC_SYNC_VRO);
	RISC_INSTR(0);

	RISC_INSTR(RISC_JUMP);
	RISC_INSTR(bt->risc_dma);

	btग_लिखो((bt->line_count << 16) | bt->line_bytes, BT878_APACK_LEN);
पूर्ण

/*****************************/
/* Start/Stop grabbing funcs */
/*****************************/

व्योम bt878_start(काष्ठा bt878 *bt, u32 controlreg, u32 op_sync_orin,
		u32 irq_err_ignore)
अणु
	u32 पूर्णांक_mask;

	dprपूर्णांकk("bt878 debug: bt878_start (ctl=%8.8x)\n", controlreg);
	/* complete the writing of the risc dma program now we have
	 * the card specअगरics
	 */
	bt878_risc_program(bt, op_sync_orin);
	controlreg &= ~0x1f;
	controlreg |= 0x1b;

	btग_लिखो(bt->risc_dma, BT878_ARISC_START);

	/* original पूर्णांक mask had :
	 *    6    2    8    4    0
	 * 1111 1111 1000 0000 0000
	 * SCERR|OCERR|PABORT|RIPERR|FDSR|FTRGT|FBUS|RISCI
	 * Hacked क्रम DST to:
	 * SCERR | OCERR | FDSR | FTRGT | FBUS | RISCI
	 */
	पूर्णांक_mask = BT878_ASCERR | BT878_AOCERR | BT878_APABORT |
		BT878_ARIPERR | BT878_APPERR | BT878_AFDSR | BT878_AFTRGT |
		BT878_AFBUS | BT878_ARISCI;


	/* ignore pesky bits */
	पूर्णांक_mask &= ~irq_err_ignore;

	btग_लिखो(पूर्णांक_mask, BT878_AINT_MASK);
	btग_लिखो(controlreg, BT878_AGPIO_DMA_CTL);
पूर्ण

व्योम bt878_stop(काष्ठा bt878 *bt)
अणु
	u32 stat;
	पूर्णांक i = 0;

	dprपूर्णांकk("bt878 debug: bt878_stop\n");

	btग_लिखो(0, BT878_AINT_MASK);
	btand(~0x13, BT878_AGPIO_DMA_CTL);

	करो अणु
		stat = btपढ़ो(BT878_AINT_STAT);
		अगर (!(stat & BT878_ARISC_EN))
			अवरोध;
		i++;
	पूर्ण जबतक (i < 500);

	dprपूर्णांकk("bt878(%d) debug: bt878_stop, i=%d, stat=0x%8.8x\n",
		bt->nr, i, stat);
पूर्ण

EXPORT_SYMBOL(bt878_start);
EXPORT_SYMBOL(bt878_stop);

/*****************************/
/* Interrupt service routine */
/*****************************/

अटल irqवापस_t bt878_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	u32 stat, astat, mask;
	पूर्णांक count;
	काष्ठा bt878 *bt;

	bt = (काष्ठा bt878 *) dev_id;

	count = 0;
	जबतक (1) अणु
		stat = btपढ़ो(BT878_AINT_STAT);
		mask = btपढ़ो(BT878_AINT_MASK);
		अगर (!(astat = (stat & mask)))
			वापस IRQ_NONE;	/* this पूर्णांकerrupt is not क्रम me */
/*		dprपूर्णांकk("bt878(%d) debug: irq count %d, stat 0x%8.8x, mask 0x%8.8x\n",bt->nr,count,stat,mask); */
		btग_लिखो(astat, BT878_AINT_STAT);	/* try to clear पूर्णांकerrupt condition */


		अगर (astat & (BT878_ASCERR | BT878_AOCERR)) अणु
			अगर (bt878_verbose) अणु
				prपूर्णांकk(KERN_INFO
				       "bt878(%d): irq%s%s risc_pc=%08x\n",
				       bt->nr,
				       (astat & BT878_ASCERR) ? " SCERR" :
				       "",
				       (astat & BT878_AOCERR) ? " OCERR" :
				       "", btपढ़ो(BT878_ARISC_PC));
			पूर्ण
		पूर्ण
		अगर (astat & (BT878_APABORT | BT878_ARIPERR | BT878_APPERR)) अणु
			अगर (bt878_verbose) अणु
				prपूर्णांकk(KERN_INFO
				     "bt878(%d): irq%s%s%s risc_pc=%08x\n",
				     bt->nr,
				     (astat & BT878_APABORT) ? " PABORT" :
				     "",
				     (astat & BT878_ARIPERR) ? " RIPERR" :
				     "",
				     (astat & BT878_APPERR) ? " PPERR" :
				     "", btपढ़ो(BT878_ARISC_PC));
			पूर्ण
		पूर्ण
		अगर (astat & (BT878_AFDSR | BT878_AFTRGT | BT878_AFBUS)) अणु
			अगर (bt878_verbose) अणु
				prपूर्णांकk(KERN_INFO
				     "bt878(%d): irq%s%s%s risc_pc=%08x\n",
				     bt->nr,
				     (astat & BT878_AFDSR) ? " FDSR" : "",
				     (astat & BT878_AFTRGT) ? " FTRGT" :
				     "",
				     (astat & BT878_AFBUS) ? " FBUS" : "",
				     btपढ़ो(BT878_ARISC_PC));
			पूर्ण
		पूर्ण
		अगर (astat & BT878_ARISCI) अणु
			bt->finished_block = (stat & BT878_ARISCS) >> 28;
			tasklet_schedule(&bt->tasklet);
			अवरोध;
		पूर्ण
		count++;
		अगर (count > 20) अणु
			btग_लिखो(0, BT878_AINT_MASK);
			prपूर्णांकk(KERN_ERR
			       "bt878(%d): IRQ lockup, cleared int mask\n",
			       bt->nr);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक
bt878_device_control(काष्ठा bt878 *bt, अचिन्हित पूर्णांक cmd, जोड़ dst_gpio_packet *mp)
अणु
	पूर्णांक retval;

	retval = 0;
	अगर (mutex_lock_पूर्णांकerruptible(&bt->gpio_lock))
		वापस -ERESTARTSYS;
	/* special gpio संकेत */
	चयन (cmd) अणु
	    हाल DST_IG_ENABLE:
		// dprपूर्णांकk("dvb_bt8xx: dst enable mask 0x%02x enb 0x%02x \n", mp->dstg.enb.mask, mp->dstg.enb.enable);
		retval = bttv_gpio_enable(bt->bttv_nr,
				mp->enb.mask,
				mp->enb.enable);
		अवरोध;
	    हाल DST_IG_WRITE:
		// dprपूर्णांकk("dvb_bt8xx: dst write gpio mask 0x%02x out 0x%02x\n", mp->dstg.outp.mask, mp->dstg.outp.highvals);
		retval = bttv_ग_लिखो_gpio(bt->bttv_nr,
				mp->outp.mask,
				mp->outp.highvals);

		अवरोध;
	    हाल DST_IG_READ:
		/* पढ़ो */
		retval =  bttv_पढ़ो_gpio(bt->bttv_nr, &mp->rd.value);
		// dprपूर्णांकk("dvb_bt8xx: dst read gpio 0x%02x\n", (अचिन्हित)mp->dstg.rd.value);
		अवरोध;
	    हाल DST_IG_TS:
		/* Set packet size */
		bt->TS_Size = mp->psize;
		अवरोध;

	    शेष:
		retval = -EINVAL;
		अवरोध;
	पूर्ण
	mutex_unlock(&bt->gpio_lock);
	वापस retval;
पूर्ण

EXPORT_SYMBOL(bt878_device_control);

#घोषणा BROOKTREE_878_DEVICE(vend, dev, name) \
	अणु \
		.venकरोr = PCI_VENDOR_ID_BROOKTREE, \
		.device = PCI_DEVICE_ID_BROOKTREE_878, \
		.subvenकरोr = (vend), .subdevice = (dev), \
		.driver_data = (अचिन्हित दीर्घ) name \
	पूर्ण

अटल स्थिर काष्ठा pci_device_id bt878_pci_tbl[] = अणु
	BROOKTREE_878_DEVICE(0x0071, 0x0101, "Nebula Electronics DigiTV"),
	BROOKTREE_878_DEVICE(0x1461, 0x0761, "AverMedia AverTV DVB-T 761"),
	BROOKTREE_878_DEVICE(0x11bd, 0x001c, "Pinnacle PCTV Sat"),
	BROOKTREE_878_DEVICE(0x11bd, 0x0026, "Pinnacle PCTV SAT CI"),
	BROOKTREE_878_DEVICE(0x1822, 0x0001, "Twinhan VisionPlus DVB"),
	BROOKTREE_878_DEVICE(0x270f, 0xfc00,
				"ChainTech digitop DST-1000 DVB-S"),
	BROOKTREE_878_DEVICE(0x1461, 0x0771, "AVermedia AverTV DVB-T 771"),
	BROOKTREE_878_DEVICE(0x18ac, 0xdb10, "DViCO FusionHDTV DVB-T Lite"),
	BROOKTREE_878_DEVICE(0x18ac, 0xdb11, "Ultraview DVB-T Lite"),
	BROOKTREE_878_DEVICE(0x18ac, 0xd500, "DViCO FusionHDTV 5 Lite"),
	BROOKTREE_878_DEVICE(0x7063, 0x2000, "pcHDTV HD-2000 TV"),
	BROOKTREE_878_DEVICE(0x1822, 0x0026, "DNTV Live! Mini"),
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, bt878_pci_tbl);

अटल स्थिर अक्षर * card_name(स्थिर काष्ठा pci_device_id *id)
अणु
	वापस id->driver_data ? (स्थिर अक्षर *)id->driver_data : "Unknown";
पूर्ण

/***********************/
/* PCI device handling */
/***********************/

अटल पूर्णांक bt878_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *pci_id)
अणु
	पूर्णांक result = 0;
	अचिन्हित अक्षर lat;
	काष्ठा bt878 *bt;
	अचिन्हित पूर्णांक cardid;

	prपूर्णांकk(KERN_INFO "bt878: Bt878 AUDIO function found (%d).\n",
	       bt878_num);
	अगर (bt878_num >= BT878_MAX) अणु
		prपूर्णांकk(KERN_ERR "bt878: Too many devices inserted\n");
		वापस -ENOMEM;
	पूर्ण
	अगर (pci_enable_device(dev))
		वापस -EIO;

	cardid = dev->subप्रणाली_device << 16;
	cardid |= dev->subप्रणाली_venकरोr;

	prपूर्णांकk(KERN_INFO "%s: card id=[0x%x],[ %s ] has DVB functions.\n",
				__func__, cardid, card_name(pci_id));

	bt = &bt878[bt878_num];
	bt->dev = dev;
	bt->nr = bt878_num;
	bt->shutकरोwn = 0;

	bt->id = dev->device;
	bt->irq = dev->irq;
	bt->bt878_adr = pci_resource_start(dev, 0);
	अगर (!request_mem_region(pci_resource_start(dev, 0),
				pci_resource_len(dev, 0), "bt878")) अणु
		result = -EBUSY;
		जाओ fail0;
	पूर्ण

	bt->revision = dev->revision;
	pci_पढ़ो_config_byte(dev, PCI_LATENCY_TIMER, &lat);


	prपूर्णांकk(KERN_INFO "bt878(%d): Bt%x (rev %d) at %02x:%02x.%x, ",
	       bt878_num, bt->id, bt->revision, dev->bus->number,
	       PCI_SLOT(dev->devfn), PCI_FUNC(dev->devfn));
	prपूर्णांकk("irq: %d, latency: %d, memory: 0x%lx\n",
	       bt->irq, lat, bt->bt878_adr);

#अगर_घोषित __sparc__
	bt->bt878_mem = (अचिन्हित अक्षर *) bt->bt878_adr;
#अन्यथा
	bt->bt878_mem = ioremap(bt->bt878_adr, 0x1000);
#पूर्ण_अगर

	/* clear पूर्णांकerrupt mask */
	btग_लिखो(0, BT848_INT_MASK);

	result = request_irq(bt->irq, bt878_irq,
			     IRQF_SHARED, "bt878", (व्योम *) bt);
	अगर (result == -EINVAL) अणु
		prपूर्णांकk(KERN_ERR "bt878(%d): Bad irq number or handler\n",
		       bt878_num);
		जाओ fail1;
	पूर्ण
	अगर (result == -EBUSY) अणु
		prपूर्णांकk(KERN_ERR
		       "bt878(%d): IRQ %d busy, change your PnP config in BIOS\n",
		       bt878_num, bt->irq);
		जाओ fail1;
	पूर्ण
	अगर (result < 0)
		जाओ fail1;

	pci_set_master(dev);
	pci_set_drvdata(dev, bt);

	अगर ((result = bt878_mem_alloc(bt))) अणु
		prपूर्णांकk(KERN_ERR "bt878: failed to allocate memory!\n");
		जाओ fail2;
	पूर्ण

	bt878_make_risc(bt);
	btग_लिखो(0, BT878_AINT_MASK);
	bt878_num++;

	वापस 0;

      fail2:
	मुक्त_irq(bt->irq, bt);
      fail1:
	release_mem_region(pci_resource_start(bt->dev, 0),
			   pci_resource_len(bt->dev, 0));
      fail0:
	pci_disable_device(dev);
	वापस result;
पूर्ण

अटल व्योम bt878_हटाओ(काष्ठा pci_dev *pci_dev)
अणु
	u8 command;
	काष्ठा bt878 *bt = pci_get_drvdata(pci_dev);

	अगर (bt878_verbose)
		prपूर्णांकk(KERN_INFO "bt878(%d): unloading\n", bt->nr);

	/* turn off all capturing, DMA and IRQs */
	btand(~0x13, BT878_AGPIO_DMA_CTL);

	/* first disable पूर्णांकerrupts beक्रमe unmapping the memory! */
	btग_लिखो(0, BT878_AINT_MASK);
	btग_लिखो(~0U, BT878_AINT_STAT);

	/* disable PCI bus-mastering */
	pci_पढ़ो_config_byte(bt->dev, PCI_COMMAND, &command);
	/* Should this be &=~ ?? */
	command &= ~PCI_COMMAND_MASTER;
	pci_ग_लिखो_config_byte(bt->dev, PCI_COMMAND, command);

	मुक्त_irq(bt->irq, bt);
	prपूर्णांकk(KERN_DEBUG "bt878_mem: 0x%p.\n", bt->bt878_mem);
	अगर (bt->bt878_mem)
		iounmap(bt->bt878_mem);

	release_mem_region(pci_resource_start(bt->dev, 0),
			   pci_resource_len(bt->dev, 0));
	/* wake up any रुकोing processes
	   because shutकरोwn flag is set, no new processes (in this queue)
	   are expected
	 */
	bt->shutकरोwn = 1;
	bt878_mem_मुक्त(bt);

	pci_disable_device(pci_dev);
	वापस;
पूर्ण

अटल काष्ठा pci_driver bt878_pci_driver = अणु
      .name	= "bt878",
      .id_table = bt878_pci_tbl,
      .probe	= bt878_probe,
      .हटाओ	= bt878_हटाओ,
पूर्ण;

/*******************************/
/* Module management functions */
/*******************************/

अटल पूर्णांक __init bt878_init_module(व्योम)
अणु
	bt878_num = 0;

	prपूर्णांकk(KERN_INFO "bt878: AUDIO driver version %d.%d.%d loaded\n",
	       (BT878_VERSION_CODE >> 16) & 0xff,
	       (BT878_VERSION_CODE >> 8) & 0xff,
	       BT878_VERSION_CODE & 0xff);

	वापस pci_रेजिस्टर_driver(&bt878_pci_driver);
पूर्ण

अटल व्योम __निकास bt878_cleanup_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&bt878_pci_driver);
पूर्ण

module_init(bt878_init_module);
module_निकास(bt878_cleanup_module);

MODULE_LICENSE("GPL");
