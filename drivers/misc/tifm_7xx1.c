<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  tअगरm_7xx1.c - TI FlashMedia driver
 *
 *  Copyright (C) 2006 Alex Dubov <oakad@yahoo.com>
 */

#समावेश <linux/tअगरm.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>

#घोषणा DRIVER_NAME "tifm_7xx1"
#घोषणा DRIVER_VERSION "0.8"

#घोषणा TIFM_IRQ_ENABLE           0x80000000
#घोषणा TIFM_IRQ_SOCKMASK(x)      (x)
#घोषणा TIFM_IRQ_CARDMASK(x)      ((x) << 8)
#घोषणा TIFM_IRQ_FIFOMASK(x)      ((x) << 16)
#घोषणा TIFM_IRQ_SETALL           0xffffffff

अटल व्योम tअगरm_7xx1_dummy_eject(काष्ठा tअगरm_adapter *fm,
				  काष्ठा tअगरm_dev *sock)
अणु
पूर्ण

अटल व्योम tअगरm_7xx1_eject(काष्ठा tअगरm_adapter *fm, काष्ठा tअगरm_dev *sock)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fm->lock, flags);
	fm->socket_change_set |= 1 << sock->socket_id;
	tअगरm_queue_work(&fm->media_चयनer);
	spin_unlock_irqrestore(&fm->lock, flags);
पूर्ण

अटल irqवापस_t tअगरm_7xx1_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा tअगरm_adapter *fm = dev_id;
	काष्ठा tअगरm_dev *sock;
	अचिन्हित पूर्णांक irq_status, cnt;

	spin_lock(&fm->lock);
	irq_status = पढ़ोl(fm->addr + FM_INTERRUPT_STATUS);
	अगर (irq_status == 0 || irq_status == (~0)) अणु
		spin_unlock(&fm->lock);
		वापस IRQ_NONE;
	पूर्ण

	अगर (irq_status & TIFM_IRQ_ENABLE) अणु
		ग_लिखोl(TIFM_IRQ_ENABLE, fm->addr + FM_CLEAR_INTERRUPT_ENABLE);

		क्रम (cnt = 0; cnt < fm->num_sockets; cnt++) अणु
			sock = fm->sockets[cnt];
			अगर (sock) अणु
				अगर ((irq_status >> cnt) & TIFM_IRQ_FIFOMASK(1))
					sock->data_event(sock);
				अगर ((irq_status >> cnt) & TIFM_IRQ_CARDMASK(1))
					sock->card_event(sock);
			पूर्ण
		पूर्ण

		fm->socket_change_set |= irq_status
					 & ((1 << fm->num_sockets) - 1);
	पूर्ण
	ग_लिखोl(irq_status, fm->addr + FM_INTERRUPT_STATUS);

	अगर (fm->finish_me)
		complete_all(fm->finish_me);
	अन्यथा अगर (!fm->socket_change_set)
		ग_लिखोl(TIFM_IRQ_ENABLE, fm->addr + FM_SET_INTERRUPT_ENABLE);
	अन्यथा
		tअगरm_queue_work(&fm->media_चयनer);

	spin_unlock(&fm->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल अचिन्हित अक्षर tअगरm_7xx1_toggle_sock_घातer(अक्षर __iomem *sock_addr)
अणु
	अचिन्हित पूर्णांक s_state;
	पूर्णांक cnt;

	ग_लिखोl(0x0e00, sock_addr + SOCK_CONTROL);

	क्रम (cnt = 16; cnt <= 256; cnt <<= 1) अणु
		अगर (!(TIFM_SOCK_STATE_POWERED
		      & पढ़ोl(sock_addr + SOCK_PRESENT_STATE)))
			अवरोध;

		msleep(cnt);
	पूर्ण

	s_state = पढ़ोl(sock_addr + SOCK_PRESENT_STATE);
	अगर (!(TIFM_SOCK_STATE_OCCUPIED & s_state))
		वापस 0;

	ग_लिखोl(पढ़ोl(sock_addr + SOCK_CONTROL) | TIFM_CTRL_LED,
	       sock_addr + SOCK_CONTROL);

	/* xd needs some extra समय beक्रमe घातer on */
	अगर (((पढ़ोl(sock_addr + SOCK_PRESENT_STATE) >> 4) & 7)
	    == TIFM_TYPE_XD)
		msleep(40);

	ग_लिखोl((s_state & TIFM_CTRL_POWER_MASK) | 0x0c00,
	       sock_addr + SOCK_CONTROL);
	/* रुको क्रम घातer to stabilize */
	msleep(20);
	क्रम (cnt = 16; cnt <= 256; cnt <<= 1) अणु
		अगर ((TIFM_SOCK_STATE_POWERED
		     & पढ़ोl(sock_addr + SOCK_PRESENT_STATE)))
			अवरोध;

		msleep(cnt);
	पूर्ण

	ग_लिखोl(पढ़ोl(sock_addr + SOCK_CONTROL) & (~TIFM_CTRL_LED),
	       sock_addr + SOCK_CONTROL);

	वापस (पढ़ोl(sock_addr + SOCK_PRESENT_STATE) >> 4) & 7;
पूर्ण

अंतरभूत अटल व्योम tअगरm_7xx1_sock_घातer_off(अक्षर __iomem *sock_addr)
अणु
	ग_लिखोl((~TIFM_CTRL_POWER_MASK) & पढ़ोl(sock_addr + SOCK_CONTROL),
	       sock_addr + SOCK_CONTROL);
पूर्ण

अंतरभूत अटल अक्षर __iomem *
tअगरm_7xx1_sock_addr(अक्षर __iomem *base_addr, अचिन्हित पूर्णांक sock_num)
अणु
	वापस base_addr + ((sock_num + 1) << 10);
पूर्ण

अटल व्योम tअगरm_7xx1_चयन_media(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tअगरm_adapter *fm = container_of(work, काष्ठा tअगरm_adapter,
					       media_चयनer);
	काष्ठा tअगरm_dev *sock;
	अक्षर __iomem *sock_addr;
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर media_id;
	अचिन्हित पूर्णांक socket_change_set, cnt;

	spin_lock_irqsave(&fm->lock, flags);
	socket_change_set = fm->socket_change_set;
	fm->socket_change_set = 0;

	dev_dbg(fm->dev.parent, "checking media set %x\n",
		socket_change_set);

	अगर (!socket_change_set) अणु
		spin_unlock_irqrestore(&fm->lock, flags);
		वापस;
	पूर्ण

	क्रम (cnt = 0; cnt < fm->num_sockets; cnt++) अणु
		अगर (!(socket_change_set & (1 << cnt)))
			जारी;
		sock = fm->sockets[cnt];
		अगर (sock) अणु
			prपूर्णांकk(KERN_INFO
			       "%s : demand removing card from socket %u:%u\n",
			       dev_name(&fm->dev), fm->id, cnt);
			fm->sockets[cnt] = शून्य;
			sock_addr = sock->addr;
			spin_unlock_irqrestore(&fm->lock, flags);
			device_unरेजिस्टर(&sock->dev);
			spin_lock_irqsave(&fm->lock, flags);
			tअगरm_7xx1_sock_घातer_off(sock_addr);
			ग_लिखोl(0x0e00, sock_addr + SOCK_CONTROL);
		पूर्ण

		spin_unlock_irqrestore(&fm->lock, flags);

		media_id = tअगरm_7xx1_toggle_sock_घातer(
				tअगरm_7xx1_sock_addr(fm->addr, cnt));

		// tअगरm_alloc_device will check अगर media_id is valid
		sock = tअगरm_alloc_device(fm, cnt, media_id);
		अगर (sock) अणु
			sock->addr = tअगरm_7xx1_sock_addr(fm->addr, cnt);

			अगर (!device_रेजिस्टर(&sock->dev)) अणु
				spin_lock_irqsave(&fm->lock, flags);
				अगर (!fm->sockets[cnt]) अणु
					fm->sockets[cnt] = sock;
					sock = शून्य;
				पूर्ण
				spin_unlock_irqrestore(&fm->lock, flags);
			पूर्ण
			अगर (sock)
				tअगरm_मुक्त_device(&sock->dev);
		पूर्ण
		spin_lock_irqsave(&fm->lock, flags);
	पूर्ण

	ग_लिखोl(TIFM_IRQ_FIFOMASK(socket_change_set)
	       | TIFM_IRQ_CARDMASK(socket_change_set),
	       fm->addr + FM_CLEAR_INTERRUPT_ENABLE);

	ग_लिखोl(TIFM_IRQ_FIFOMASK(socket_change_set)
	       | TIFM_IRQ_CARDMASK(socket_change_set),
	       fm->addr + FM_SET_INTERRUPT_ENABLE);

	ग_लिखोl(TIFM_IRQ_ENABLE, fm->addr + FM_SET_INTERRUPT_ENABLE);
	spin_unlock_irqrestore(&fm->lock, flags);
पूर्ण

अटल पूर्णांक __maybe_unused tअगरm_7xx1_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(dev_d);
	काष्ठा tअगरm_adapter *fm = pci_get_drvdata(dev);
	पूर्णांक cnt;

	dev_dbg(&dev->dev, "suspending host\n");

	क्रम (cnt = 0; cnt < fm->num_sockets; cnt++) अणु
		अगर (fm->sockets[cnt])
			tअगरm_7xx1_sock_घातer_off(fm->sockets[cnt]->addr);
	पूर्ण

	device_wakeup_disable(dev_d);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tअगरm_7xx1_resume(काष्ठा device *dev_d)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(dev_d);
	काष्ठा tअगरm_adapter *fm = pci_get_drvdata(dev);
	पूर्णांक rc;
	अचिन्हित दीर्घ समयout;
	अचिन्हित पूर्णांक good_sockets = 0, bad_sockets = 0;
	अचिन्हित दीर्घ flags;
	/* Maximum number of entries is 4 */
	अचिन्हित अक्षर new_ids[4];
	DECLARE_COMPLETION_ONSTACK(finish_resume);

	अगर (WARN_ON(fm->num_sockets > ARRAY_SIZE(new_ids)))
		वापस -ENXIO;

	pci_set_master(dev);

	dev_dbg(&dev->dev, "resuming host\n");

	क्रम (rc = 0; rc < fm->num_sockets; rc++)
		new_ids[rc] = tअगरm_7xx1_toggle_sock_घातer(
					tअगरm_7xx1_sock_addr(fm->addr, rc));
	spin_lock_irqsave(&fm->lock, flags);
	क्रम (rc = 0; rc < fm->num_sockets; rc++) अणु
		अगर (fm->sockets[rc]) अणु
			अगर (fm->sockets[rc]->type == new_ids[rc])
				good_sockets |= 1 << rc;
			अन्यथा
				bad_sockets |= 1 << rc;
		पूर्ण
	पूर्ण

	ग_लिखोl(TIFM_IRQ_ENABLE | TIFM_IRQ_SOCKMASK((1 << fm->num_sockets) - 1),
	       fm->addr + FM_SET_INTERRUPT_ENABLE);
	dev_dbg(&dev->dev, "change sets on resume: good %x, bad %x\n",
		good_sockets, bad_sockets);

	fm->socket_change_set = 0;
	अगर (good_sockets) अणु
		fm->finish_me = &finish_resume;
		spin_unlock_irqrestore(&fm->lock, flags);
		समयout = रुको_क्रम_completion_समयout(&finish_resume, HZ);
		dev_dbg(&dev->dev, "wait returned %lu\n", समयout);
		ग_लिखोl(TIFM_IRQ_FIFOMASK(good_sockets)
		       | TIFM_IRQ_CARDMASK(good_sockets),
		       fm->addr + FM_CLEAR_INTERRUPT_ENABLE);
		ग_लिखोl(TIFM_IRQ_FIFOMASK(good_sockets)
		       | TIFM_IRQ_CARDMASK(good_sockets),
		       fm->addr + FM_SET_INTERRUPT_ENABLE);
		spin_lock_irqsave(&fm->lock, flags);
		fm->finish_me = शून्य;
		fm->socket_change_set ^= good_sockets & fm->socket_change_set;
	पूर्ण

	fm->socket_change_set |= bad_sockets;
	अगर (fm->socket_change_set)
		tअगरm_queue_work(&fm->media_चयनer);

	spin_unlock_irqrestore(&fm->lock, flags);
	ग_लिखोl(TIFM_IRQ_ENABLE,
	       fm->addr + FM_SET_INTERRUPT_ENABLE);

	वापस 0;
पूर्ण

अटल पूर्णांक tअगरm_7xx1_dummy_has_ms_pअगर(काष्ठा tअगरm_adapter *fm,
				      काष्ठा tअगरm_dev *sock)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक tअगरm_7xx1_has_ms_pअगर(काष्ठा tअगरm_adapter *fm, काष्ठा tअगरm_dev *sock)
अणु
	अगर (((fm->num_sockets == 4) && (sock->socket_id == 2))
	    || ((fm->num_sockets == 2) && (sock->socket_id == 0)))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक tअगरm_7xx1_probe(काष्ठा pci_dev *dev,
			   स्थिर काष्ठा pci_device_id *dev_id)
अणु
	काष्ठा tअगरm_adapter *fm;
	पूर्णांक pci_dev_busy = 0;
	पूर्णांक rc;

	rc = pci_set_dma_mask(dev, DMA_BIT_MASK(32));
	अगर (rc)
		वापस rc;

	rc = pci_enable_device(dev);
	अगर (rc)
		वापस rc;

	pci_set_master(dev);

	rc = pci_request_regions(dev, DRIVER_NAME);
	अगर (rc) अणु
		pci_dev_busy = 1;
		जाओ err_out;
	पूर्ण

	pci_पूर्णांकx(dev, 1);

	fm = tअगरm_alloc_adapter(dev->device == PCI_DEVICE_ID_TI_XX21_XX11_FM
				? 4 : 2, &dev->dev);
	अगर (!fm) अणु
		rc = -ENOMEM;
		जाओ err_out_पूर्णांक;
	पूर्ण

	INIT_WORK(&fm->media_चयनer, tअगरm_7xx1_चयन_media);
	fm->eject = tअगरm_7xx1_eject;
	fm->has_ms_pअगर = tअगरm_7xx1_has_ms_pअगर;
	pci_set_drvdata(dev, fm);

	fm->addr = pci_ioremap_bar(dev, 0);
	अगर (!fm->addr) अणु
		rc = -ENODEV;
		जाओ err_out_मुक्त;
	पूर्ण

	rc = request_irq(dev->irq, tअगरm_7xx1_isr, IRQF_SHARED, DRIVER_NAME, fm);
	अगर (rc)
		जाओ err_out_unmap;

	rc = tअगरm_add_adapter(fm);
	अगर (rc)
		जाओ err_out_irq;

	ग_लिखोl(TIFM_IRQ_ENABLE | TIFM_IRQ_SOCKMASK((1 << fm->num_sockets) - 1),
	       fm->addr + FM_CLEAR_INTERRUPT_ENABLE);
	ग_लिखोl(TIFM_IRQ_ENABLE | TIFM_IRQ_SOCKMASK((1 << fm->num_sockets) - 1),
	       fm->addr + FM_SET_INTERRUPT_ENABLE);
	वापस 0;

err_out_irq:
	मुक्त_irq(dev->irq, fm);
err_out_unmap:
	iounmap(fm->addr);
err_out_मुक्त:
	tअगरm_मुक्त_adapter(fm);
err_out_पूर्णांक:
	pci_पूर्णांकx(dev, 0);
	pci_release_regions(dev);
err_out:
	अगर (!pci_dev_busy)
		pci_disable_device(dev);
	वापस rc;
पूर्ण

अटल व्योम tअगरm_7xx1_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा tअगरm_adapter *fm = pci_get_drvdata(dev);
	पूर्णांक cnt;

	fm->eject = tअगरm_7xx1_dummy_eject;
	fm->has_ms_pअगर = tअगरm_7xx1_dummy_has_ms_pअगर;
	ग_लिखोl(TIFM_IRQ_SETALL, fm->addr + FM_CLEAR_INTERRUPT_ENABLE);
	मुक्त_irq(dev->irq, fm);

	tअगरm_हटाओ_adapter(fm);

	क्रम (cnt = 0; cnt < fm->num_sockets; cnt++)
		tअगरm_7xx1_sock_घातer_off(tअगरm_7xx1_sock_addr(fm->addr, cnt));

	iounmap(fm->addr);
	pci_पूर्णांकx(dev, 0);
	pci_release_regions(dev);

	pci_disable_device(dev);
	tअगरm_मुक्त_adapter(fm);
पूर्ण

अटल स्थिर काष्ठा pci_device_id tअगरm_7xx1_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_XX21_XX11_FM, PCI_ANY_ID,
	  PCI_ANY_ID, 0, 0, 0 पूर्ण, /* xx21 - the one I have */
        अणु PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_XX12_FM, PCI_ANY_ID,
	  PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_TI, PCI_DEVICE_ID_TI_XX20_FM, PCI_ANY_ID,
	  PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल SIMPLE_DEV_PM_OPS(tअगरm_7xx1_pm_ops, tअगरm_7xx1_suspend, tअगरm_7xx1_resume);

अटल काष्ठा pci_driver tअगरm_7xx1_driver = अणु
	.name = DRIVER_NAME,
	.id_table = tअगरm_7xx1_pci_tbl,
	.probe = tअगरm_7xx1_probe,
	.हटाओ = tअगरm_7xx1_हटाओ,
	.driver.pm = &tअगरm_7xx1_pm_ops,
पूर्ण;

module_pci_driver(tअगरm_7xx1_driver);
MODULE_AUTHOR("Alex Dubov");
MODULE_DESCRIPTION("TI FlashMedia host driver");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(pci, tअगरm_7xx1_pci_tbl);
MODULE_VERSION(DRIVER_VERSION);
