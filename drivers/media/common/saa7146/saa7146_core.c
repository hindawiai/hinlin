<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    saa7146.o - driver क्रम generic saa7146-based hardware

    Copyright (C) 1998-2003 Michael Hunold <michael@mihu.de>

*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <media/drv-पूर्णांकf/saa7146.h>
#समावेश <linux/module.h>

अटल पूर्णांक saa7146_num;

अचिन्हित पूर्णांक saa7146_debug;

module_param(saa7146_debug, uपूर्णांक, 0644);
MODULE_PARM_DESC(saa7146_debug, "debug level (default: 0)");

#अगर 0
अटल व्योम dump_रेजिस्टरs(काष्ठा saa7146_dev* dev)
अणु
	पूर्णांक i = 0;

	pr_info(" @ %li jiffies:\n", jअगरfies);
	क्रम (i = 0; i <= 0x148; i += 4)
		pr_info("0x%03x: 0x%08x\n", i, saa7146_पढ़ो(dev, i));
पूर्ण
#पूर्ण_अगर

/****************************************************************************
 * gpio and debi helper functions
 ****************************************************************************/

व्योम saa7146_setgpio(काष्ठा saa7146_dev *dev, पूर्णांक port, u32 data)
अणु
	u32 value = 0;

	BUG_ON(port > 3);

	value = saa7146_पढ़ो(dev, GPIO_CTRL);
	value &= ~(0xff << (8*port));
	value |= (data << (8*port));
	saa7146_ग_लिखो(dev, GPIO_CTRL, value);
पूर्ण

/* This DEBI code is based on the saa7146 Stradis driver by Nathan Lareकरो */
अटल अंतरभूत पूर्णांक saa7146_रुको_क्रम_debi_करोne_sleep(काष्ठा saa7146_dev *dev,
				अचिन्हित दीर्घ us1, अचिन्हित दीर्घ us2)
अणु
	अचिन्हित दीर्घ समयout;
	पूर्णांक err;

	/* रुको क्रम रेजिस्टरs to be programmed */
	समयout = jअगरfies + usecs_to_jअगरfies(us1);
	जबतक (1) अणु
		err = समय_after(jअगरfies, समयout);
		अगर (saa7146_पढ़ो(dev, MC2) & 2)
			अवरोध;
		अगर (err) अणु
			pr_debug("%s: %s timed out while waiting for registers getting programmed\n",
			       dev->name, __func__);
			वापस -ETIMEDOUT;
		पूर्ण
		msleep(1);
	पूर्ण

	/* रुको क्रम transfer to complete */
	समयout = jअगरfies + usecs_to_jअगरfies(us2);
	जबतक (1) अणु
		err = समय_after(jअगरfies, समयout);
		अगर (!(saa7146_पढ़ो(dev, PSR) & SPCI_DEBI_S))
			अवरोध;
		saa7146_पढ़ो(dev, MC2);
		अगर (err) अणु
			DEB_S("%s: %s timed out while waiting for transfer completion\n",
			      dev->name, __func__);
			वापस -ETIMEDOUT;
		पूर्ण
		msleep(1);
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक saa7146_रुको_क्रम_debi_करोne_busyloop(काष्ठा saa7146_dev *dev,
				अचिन्हित दीर्घ us1, अचिन्हित दीर्घ us2)
अणु
	अचिन्हित दीर्घ loops;

	/* रुको क्रम रेजिस्टरs to be programmed */
	loops = us1;
	जबतक (1) अणु
		अगर (saa7146_पढ़ो(dev, MC2) & 2)
			अवरोध;
		अगर (!loops--) अणु
			pr_err("%s: %s timed out while waiting for registers getting programmed\n",
			       dev->name, __func__);
			वापस -ETIMEDOUT;
		पूर्ण
		udelay(1);
	पूर्ण

	/* रुको क्रम transfer to complete */
	loops = us2 / 5;
	जबतक (1) अणु
		अगर (!(saa7146_पढ़ो(dev, PSR) & SPCI_DEBI_S))
			अवरोध;
		saa7146_पढ़ो(dev, MC2);
		अगर (!loops--) अणु
			DEB_S("%s: %s timed out while waiting for transfer completion\n",
			      dev->name, __func__);
			वापस -ETIMEDOUT;
		पूर्ण
		udelay(5);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक saa7146_रुको_क्रम_debi_करोne(काष्ठा saa7146_dev *dev, पूर्णांक nobusyloop)
अणु
	अगर (nobusyloop)
		वापस saa7146_रुको_क्रम_debi_करोne_sleep(dev, 50000, 250000);
	अन्यथा
		वापस saa7146_रुको_क्रम_debi_करोne_busyloop(dev, 50000, 250000);
पूर्ण

/****************************************************************************
 * general helper functions
 ****************************************************************************/

/* this is videobuf_vदो_स्मृति_to_sg() from videobuf-dma-sg.c
   make sure virt has been allocated with vदो_स्मृति_32(), otherwise the BUG()
   may be triggered on highmem machines */
अटल काष्ठा scatterlist* vदो_स्मृति_to_sg(अचिन्हित अक्षर *virt, पूर्णांक nr_pages)
अणु
	काष्ठा scatterlist *sglist;
	काष्ठा page *pg;
	पूर्णांक i;

	sglist = kदो_स्मृति_array(nr_pages, माप(काष्ठा scatterlist), GFP_KERNEL);
	अगर (शून्य == sglist)
		वापस शून्य;
	sg_init_table(sglist, nr_pages);
	क्रम (i = 0; i < nr_pages; i++, virt += PAGE_SIZE) अणु
		pg = vदो_स्मृति_to_page(virt);
		अगर (शून्य == pg)
			जाओ err;
		BUG_ON(PageHighMem(pg));
		sg_set_page(&sglist[i], pg, PAGE_SIZE, 0);
	पूर्ण
	वापस sglist;

 err:
	kमुक्त(sglist);
	वापस शून्य;
पूर्ण

/********************************************************************************/
/* common page table functions */

व्योम *saa7146_vदो_स्मृति_build_pgtable(काष्ठा pci_dev *pci, दीर्घ length, काष्ठा saa7146_pgtable *pt)
अणु
	पूर्णांक pages = (length+PAGE_SIZE-1)/PAGE_SIZE;
	व्योम *mem = vदो_स्मृति_32(length);
	पूर्णांक slen = 0;

	अगर (शून्य == mem)
		जाओ err_null;

	अगर (!(pt->slist = vदो_स्मृति_to_sg(mem, pages)))
		जाओ err_मुक्त_mem;

	अगर (saa7146_pgtable_alloc(pci, pt))
		जाओ err_मुक्त_slist;

	pt->nents = pages;
	slen = dma_map_sg(&pci->dev, pt->slist, pt->nents, DMA_FROM_DEVICE);
	अगर (0 == slen)
		जाओ err_मुक्त_pgtable;

	अगर (0 != saa7146_pgtable_build_single(pci, pt, pt->slist, slen))
		जाओ err_unmap_sg;

	वापस mem;

err_unmap_sg:
	dma_unmap_sg(&pci->dev, pt->slist, pt->nents, DMA_FROM_DEVICE);
err_मुक्त_pgtable:
	saa7146_pgtable_मुक्त(pci, pt);
err_मुक्त_slist:
	kमुक्त(pt->slist);
	pt->slist = शून्य;
err_मुक्त_mem:
	vमुक्त(mem);
err_null:
	वापस शून्य;
पूर्ण

व्योम saa7146_vमुक्त_destroy_pgtable(काष्ठा pci_dev *pci, व्योम *mem, काष्ठा saa7146_pgtable *pt)
अणु
	dma_unmap_sg(&pci->dev, pt->slist, pt->nents, DMA_FROM_DEVICE);
	saa7146_pgtable_मुक्त(pci, pt);
	kमुक्त(pt->slist);
	pt->slist = शून्य;
	vमुक्त(mem);
पूर्ण

व्योम saa7146_pgtable_मुक्त(काष्ठा pci_dev *pci, काष्ठा saa7146_pgtable *pt)
अणु
	अगर (शून्य == pt->cpu)
		वापस;
	dma_मुक्त_coherent(&pci->dev, pt->size, pt->cpu, pt->dma);
	pt->cpu = शून्य;
पूर्ण

पूर्णांक saa7146_pgtable_alloc(काष्ठा pci_dev *pci, काष्ठा saa7146_pgtable *pt)
अणु
	__le32       *cpu;
	dma_addr_t   dma_addr = 0;

	cpu = dma_alloc_coherent(&pci->dev, PAGE_SIZE, &dma_addr, GFP_KERNEL);
	अगर (शून्य == cpu) अणु
		वापस -ENOMEM;
	पूर्ण
	pt->size = PAGE_SIZE;
	pt->cpu  = cpu;
	pt->dma  = dma_addr;

	वापस 0;
पूर्ण

पूर्णांक saa7146_pgtable_build_single(काष्ठा pci_dev *pci, काष्ठा saa7146_pgtable *pt,
	काष्ठा scatterlist *list, पूर्णांक sglen  )
अणु
	__le32 *ptr, fill;
	पूर्णांक nr_pages = 0;
	पूर्णांक i,p;

	BUG_ON(0 == sglen);
	BUG_ON(list->offset > PAGE_SIZE);

	/* अगर we have a user buffer, the first page may not be
	   aligned to a page boundary. */
	pt->offset = list->offset;

	ptr = pt->cpu;
	क्रम (i = 0; i < sglen; i++, list++) अणु
/*
		pr_debug("i:%d, adr:0x%08x, len:%d, offset:%d\n",
			 i, sg_dma_address(list), sg_dma_len(list),
			 list->offset);
*/
		क्रम (p = 0; p * 4096 < sg_dma_len(list); p++, ptr++) अणु
			*ptr = cpu_to_le32(sg_dma_address(list) + p * 4096);
			nr_pages++;
		पूर्ण
	पूर्ण


	/* safety; fill the page table up with the last valid page */
	fill = *(ptr-1);
	क्रम(i=nr_pages;i<1024;i++) अणु
		*ptr++ = fill;
	पूर्ण

/*
	ptr = pt->cpu;
	pr_debug("offset: %d\n", pt->offset);
	क्रम(i=0;i<5;i++) अणु
		pr_debug("ptr1 %d: 0x%08x\n", i, ptr[i]);
	पूर्ण
*/
	वापस 0;
पूर्ण

/********************************************************************************/
/* पूर्णांकerrupt handler */
अटल irqवापस_t पूर्णांकerrupt_hw(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा saa7146_dev *dev = dev_id;
	u32 isr;
	u32 ack_isr;

	/* पढ़ो out the पूर्णांकerrupt status रेजिस्टर */
	ack_isr = isr = saa7146_पढ़ो(dev, ISR);

	/* is this our पूर्णांकerrupt? */
	अगर ( 0 == isr ) अणु
		/* nope, some other device */
		वापस IRQ_NONE;
	पूर्ण

	अगर (dev->ext) अणु
		अगर (dev->ext->irq_mask & isr) अणु
			अगर (dev->ext->irq_func)
				dev->ext->irq_func(dev, &isr);
			isr &= ~dev->ext->irq_mask;
		पूर्ण
	पूर्ण
	अगर (0 != (isr & (MASK_27))) अणु
		DEB_INT("irq: RPS0 (0x%08x)\n", isr);
		अगर (dev->vv_data && dev->vv_callback)
			dev->vv_callback(dev,isr);
		isr &= ~MASK_27;
	पूर्ण
	अगर (0 != (isr & (MASK_28))) अणु
		अगर (dev->vv_data && dev->vv_callback)
			dev->vv_callback(dev,isr);
		isr &= ~MASK_28;
	पूर्ण
	अगर (0 != (isr & (MASK_16|MASK_17))) अणु
		SAA7146_IER_DISABLE(dev, MASK_16|MASK_17);
		/* only wake up अगर we expect something */
		अगर (0 != dev->i2c_op) अणु
			dev->i2c_op = 0;
			wake_up(&dev->i2c_wq);
		पूर्ण अन्यथा अणु
			u32 psr = saa7146_पढ़ो(dev, PSR);
			u32 ssr = saa7146_पढ़ो(dev, SSR);
			pr_warn("%s: unexpected i2c irq: isr %08x psr %08x ssr %08x\n",
				dev->name, isr, psr, ssr);
		पूर्ण
		isr &= ~(MASK_16|MASK_17);
	पूर्ण
	अगर( 0 != isr ) अणु
		ERR("warning: interrupt enabled, but not handled properly.(0x%08x)\n",
		    isr);
		ERR("disabling interrupt source(s)!\n");
		SAA7146_IER_DISABLE(dev,isr);
	पूर्ण
	saa7146_ग_लिखो(dev, ISR, ack_isr);
	वापस IRQ_HANDLED;
पूर्ण

/*********************************************************************************/
/* configuration-functions                                                       */

अटल पूर्णांक saa7146_init_one(काष्ठा pci_dev *pci, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा saa7146_pci_extension_data *pci_ext = (काष्ठा saa7146_pci_extension_data *)ent->driver_data;
	काष्ठा saa7146_extension *ext = pci_ext->ext;
	काष्ठा saa7146_dev *dev;
	पूर्णांक err = -ENOMEM;

	/* clear out mem क्रम sure */
	dev = kzalloc(माप(काष्ठा saa7146_dev), GFP_KERNEL);
	अगर (!dev) अणु
		ERR("out of memory\n");
		जाओ out;
	पूर्ण

	/* create a nice device name */
	प्र_लिखो(dev->name, "saa7146 (%d)", saa7146_num);

	DEB_EE("pci:%p\n", pci);

	err = pci_enable_device(pci);
	अगर (err < 0) अणु
		ERR("pci_enable_device() failed\n");
		जाओ err_मुक्त;
	पूर्ण

	/* enable bus-mastering */
	pci_set_master(pci);

	dev->pci = pci;

	/* get chip-revision; this is needed to enable bug-fixes */
	dev->revision = pci->revision;

	/* remap the memory from भव to physical address */

	err = pci_request_region(pci, 0, "saa7146");
	अगर (err < 0)
		जाओ err_disable;

	dev->mem = ioremap(pci_resource_start(pci, 0),
			   pci_resource_len(pci, 0));
	अगर (!dev->mem) अणु
		ERR("ioremap() failed\n");
		err = -ENODEV;
		जाओ err_release;
	पूर्ण

	/* we करोn't करो a master reset here anymore, it screws up
	   some boards that करोn't have an i2c-eeprom क्रम configuration
	   values */
/*
	saa7146_ग_लिखो(dev, MC1, MASK_31);
*/

	/* disable all irqs */
	saa7146_ग_लिखो(dev, IER, 0);

	/* shut करोwn all dma transfers and rps tasks */
	saa7146_ग_लिखो(dev, MC1, 0x30ff0000);

	/* clear out any rps-संकेतs pending */
	saa7146_ग_लिखो(dev, MC2, 0xf8000000);

	/* request an पूर्णांकerrupt क्रम the saa7146 */
	err = request_irq(pci->irq, पूर्णांकerrupt_hw, IRQF_SHARED,
			  dev->name, dev);
	अगर (err < 0) अणु
		ERR("request_irq() failed\n");
		जाओ err_unmap;
	पूर्ण

	err = -ENOMEM;

	/* get memory क्रम various stuff */
	dev->d_rps0.cpu_addr = dma_alloc_coherent(&pci->dev, SAA7146_RPS_MEM,
						  &dev->d_rps0.dma_handle,
						  GFP_KERNEL);
	अगर (!dev->d_rps0.cpu_addr)
		जाओ err_मुक्त_irq;

	dev->d_rps1.cpu_addr = dma_alloc_coherent(&pci->dev, SAA7146_RPS_MEM,
						  &dev->d_rps1.dma_handle,
						  GFP_KERNEL);
	अगर (!dev->d_rps1.cpu_addr)
		जाओ err_मुक्त_rps0;

	dev->d_i2c.cpu_addr = dma_alloc_coherent(&pci->dev, SAA7146_RPS_MEM,
						 &dev->d_i2c.dma_handle, GFP_KERNEL);
	अगर (!dev->d_i2c.cpu_addr)
		जाओ err_मुक्त_rps1;

	/* the rest + prपूर्णांक status message */

	pr_info("found saa7146 @ mem %p (revision %d, irq %d) (0x%04x,0x%04x)\n",
		dev->mem, dev->revision, pci->irq,
		pci->subप्रणाली_venकरोr, pci->subप्रणाली_device);
	dev->ext = ext;

	mutex_init(&dev->v4l2_lock);
	spin_lock_init(&dev->पूर्णांक_slock);
	spin_lock_init(&dev->slock);

	mutex_init(&dev->i2c_lock);

	dev->module = THIS_MODULE;
	init_रुकोqueue_head(&dev->i2c_wq);

	/* set some sane pci arbitrition values */
	saa7146_ग_लिखो(dev, PCI_BT_V1, 0x1c00101f);

	/* TODO: use the status code of the callback */

	err = -ENODEV;

	अगर (ext->probe && ext->probe(dev)) अणु
		DEB_D("ext->probe() failed for %p. skipping device.\n", dev);
		जाओ err_मुक्त_i2c;
	पूर्ण

	अगर (ext->attach(dev, pci_ext)) अणु
		DEB_D("ext->attach() failed for %p. skipping device.\n", dev);
		जाओ err_मुक्त_i2c;
	पूर्ण
	/* V4L extensions will set the pci drvdata to the v4l2_device in the
	   attach() above. So क्रम those cards that करो not use V4L we have to
	   set it explicitly. */
	pci_set_drvdata(pci, &dev->v4l2_dev);

	saa7146_num++;

	err = 0;
out:
	वापस err;

err_मुक्त_i2c:
	dma_मुक्त_coherent(&pci->dev, SAA7146_RPS_MEM, dev->d_i2c.cpu_addr,
			  dev->d_i2c.dma_handle);
err_मुक्त_rps1:
	dma_मुक्त_coherent(&pci->dev, SAA7146_RPS_MEM, dev->d_rps1.cpu_addr,
			  dev->d_rps1.dma_handle);
err_मुक्त_rps0:
	dma_मुक्त_coherent(&pci->dev, SAA7146_RPS_MEM, dev->d_rps0.cpu_addr,
			  dev->d_rps0.dma_handle);
err_मुक्त_irq:
	मुक्त_irq(pci->irq, (व्योम *)dev);
err_unmap:
	iounmap(dev->mem);
err_release:
	pci_release_region(pci, 0);
err_disable:
	pci_disable_device(pci);
err_मुक्त:
	kमुक्त(dev);
	जाओ out;
पूर्ण

अटल व्योम saa7146_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा v4l2_device *v4l2_dev = pci_get_drvdata(pdev);
	काष्ठा saa7146_dev *dev = to_saa7146_dev(v4l2_dev);
	काष्ठा अणु
		व्योम *addr;
		dma_addr_t dma;
	पूर्ण dev_map[] = अणु
		अणु dev->d_i2c.cpu_addr, dev->d_i2c.dma_handle पूर्ण,
		अणु dev->d_rps1.cpu_addr, dev->d_rps1.dma_handle पूर्ण,
		अणु dev->d_rps0.cpu_addr, dev->d_rps0.dma_handle पूर्ण,
		अणु शून्य, 0 पूर्ण
	पूर्ण, *p;

	DEB_EE("dev:%p\n", dev);

	dev->ext->detach(dev);

	/* shut करोwn all video dma transfers */
	saa7146_ग_लिखो(dev, MC1, 0x00ff0000);

	/* disable all irqs, release irq-routine */
	saa7146_ग_लिखो(dev, IER, 0);

	मुक्त_irq(pdev->irq, dev);

	क्रम (p = dev_map; p->addr; p++)
		dma_मुक्त_coherent(&pdev->dev, SAA7146_RPS_MEM, p->addr,
				  p->dma);

	iounmap(dev->mem);
	pci_release_region(pdev, 0);
	pci_disable_device(pdev);
	kमुक्त(dev);

	saa7146_num--;
पूर्ण

/*********************************************************************************/
/* extension handling functions                                                  */

पूर्णांक saa7146_रेजिस्टर_extension(काष्ठा saa7146_extension* ext)
अणु
	DEB_EE("ext:%p\n", ext);

	ext->driver.name = ext->name;
	ext->driver.id_table = ext->pci_tbl;
	ext->driver.probe = saa7146_init_one;
	ext->driver.हटाओ = saa7146_हटाओ_one;

	pr_info("register extension '%s'\n", ext->name);
	वापस pci_रेजिस्टर_driver(&ext->driver);
पूर्ण

पूर्णांक saa7146_unरेजिस्टर_extension(काष्ठा saa7146_extension* ext)
अणु
	DEB_EE("ext:%p\n", ext);
	pr_info("unregister extension '%s'\n", ext->name);
	pci_unरेजिस्टर_driver(&ext->driver);
	वापस 0;
पूर्ण

EXPORT_SYMBOL_GPL(saa7146_रेजिस्टर_extension);
EXPORT_SYMBOL_GPL(saa7146_unरेजिस्टर_extension);

/* misc functions used by extension modules */
EXPORT_SYMBOL_GPL(saa7146_pgtable_alloc);
EXPORT_SYMBOL_GPL(saa7146_pgtable_मुक्त);
EXPORT_SYMBOL_GPL(saa7146_pgtable_build_single);
EXPORT_SYMBOL_GPL(saa7146_vदो_स्मृति_build_pgtable);
EXPORT_SYMBOL_GPL(saa7146_vमुक्त_destroy_pgtable);
EXPORT_SYMBOL_GPL(saa7146_रुको_क्रम_debi_करोne);

EXPORT_SYMBOL_GPL(saa7146_setgpio);

EXPORT_SYMBOL_GPL(saa7146_i2c_adapter_prepare);

EXPORT_SYMBOL_GPL(saa7146_debug);

MODULE_AUTHOR("Michael Hunold <michael@mihu.de>");
MODULE_DESCRIPTION("driver for generic saa7146-based hardware");
MODULE_LICENSE("GPL");
