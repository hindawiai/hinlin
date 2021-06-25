<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#घोषणा PRISM2_PCI

/* Host AP driver's support क्रम Intersil Prism2.5 PCI cards is based on
 * driver patches from Reyk Floeter <reyk@vantronix.net> and
 * Andy Warner <andyw@pobox.com> */

#समावेश <linux/module.h>
#समावेश <linux/अगर.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/wireless.h>
#समावेश <net/iw_handler.h>

#समावेश <linux/ioport.h>
#समावेश <linux/pci.h>
#समावेश <यंत्र/पन.स>

#समावेश "hostap_wlan.h"


अटल अक्षर *dev_info = "hostap_pci";


MODULE_AUTHOR("Jouni Malinen");
MODULE_DESCRIPTION("Support for Intersil Prism2.5-based 802.11 wireless LAN "
		   "PCI cards.");
MODULE_LICENSE("GPL");


/* काष्ठा local_info::hw_priv */
काष्ठा hostap_pci_priv अणु
	व्योम __iomem *mem_start;
पूर्ण;


/* FIX: करो we need mb/wmb/rmb with memory operations? */


अटल स्थिर काष्ठा pci_device_id prism2_pci_id_table[] = अणु
	/* Intersil Prism3 ISL3872 11Mb/s WLAN Controller */
	अणु 0x1260, 0x3872, PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	/* Intersil Prism2.5 ISL3874 11Mb/s WLAN Controller */
	अणु 0x1260, 0x3873, PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	/* Samsung MagicLAN SWL-2210P */
	अणु 0x167d, 0xa000, PCI_ANY_ID, PCI_ANY_ID पूर्ण,
	अणु 0 पूर्ण
पूर्ण;


#अगर_घोषित PRISM2_IO_DEBUG

अटल अंतरभूत व्योम hfa384x_outb_debug(काष्ठा net_device *dev, पूर्णांक a, u8 v)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	काष्ठा hostap_pci_priv *hw_priv;
	local_info_t *local;
	अचिन्हित दीर्घ flags;

	अगरace = netdev_priv(dev);
	local = अगरace->local;
	hw_priv = local->hw_priv;

	spin_lock_irqsave(&local->lock, flags);
	prism2_io_debug_add(dev, PRISM2_IO_DEBUG_CMD_OUTB, a, v);
	ग_लिखोb(v, hw_priv->mem_start + a);
	spin_unlock_irqrestore(&local->lock, flags);
पूर्ण

अटल अंतरभूत u8 hfa384x_inb_debug(काष्ठा net_device *dev, पूर्णांक a)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	काष्ठा hostap_pci_priv *hw_priv;
	local_info_t *local;
	अचिन्हित दीर्घ flags;
	u8 v;

	अगरace = netdev_priv(dev);
	local = अगरace->local;
	hw_priv = local->hw_priv;

	spin_lock_irqsave(&local->lock, flags);
	v = पढ़ोb(hw_priv->mem_start + a);
	prism2_io_debug_add(dev, PRISM2_IO_DEBUG_CMD_INB, a, v);
	spin_unlock_irqrestore(&local->lock, flags);
	वापस v;
पूर्ण

अटल अंतरभूत व्योम hfa384x_outw_debug(काष्ठा net_device *dev, पूर्णांक a, u16 v)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	काष्ठा hostap_pci_priv *hw_priv;
	local_info_t *local;
	अचिन्हित दीर्घ flags;

	अगरace = netdev_priv(dev);
	local = अगरace->local;
	hw_priv = local->hw_priv;

	spin_lock_irqsave(&local->lock, flags);
	prism2_io_debug_add(dev, PRISM2_IO_DEBUG_CMD_OUTW, a, v);
	ग_लिखोw(v, hw_priv->mem_start + a);
	spin_unlock_irqrestore(&local->lock, flags);
पूर्ण

अटल अंतरभूत u16 hfa384x_inw_debug(काष्ठा net_device *dev, पूर्णांक a)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	काष्ठा hostap_pci_priv *hw_priv;
	local_info_t *local;
	अचिन्हित दीर्घ flags;
	u16 v;

	अगरace = netdev_priv(dev);
	local = अगरace->local;
	hw_priv = local->hw_priv;

	spin_lock_irqsave(&local->lock, flags);
	v = पढ़ोw(hw_priv->mem_start + a);
	prism2_io_debug_add(dev, PRISM2_IO_DEBUG_CMD_INW, a, v);
	spin_unlock_irqrestore(&local->lock, flags);
	वापस v;
पूर्ण

#घोषणा HFA384X_OUTB(v,a) hfa384x_outb_debug(dev, (a), (v))
#घोषणा HFA384X_INB(a) hfa384x_inb_debug(dev, (a))
#घोषणा HFA384X_OUTW(v,a) hfa384x_outw_debug(dev, (a), (v))
#घोषणा HFA384X_INW(a) hfa384x_inw_debug(dev, (a))
#घोषणा HFA384X_OUTW_DATA(v,a) hfa384x_outw_debug(dev, (a), le16_to_cpu((v)))
#घोषणा HFA384X_INW_DATA(a) cpu_to_le16(hfa384x_inw_debug(dev, (a)))

#अन्यथा /* PRISM2_IO_DEBUG */

अटल अंतरभूत व्योम hfa384x_outb(काष्ठा net_device *dev, पूर्णांक a, u8 v)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	काष्ठा hostap_pci_priv *hw_priv;
	अगरace = netdev_priv(dev);
	hw_priv = अगरace->local->hw_priv;
	ग_लिखोb(v, hw_priv->mem_start + a);
पूर्ण

अटल अंतरभूत u8 hfa384x_inb(काष्ठा net_device *dev, पूर्णांक a)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	काष्ठा hostap_pci_priv *hw_priv;
	अगरace = netdev_priv(dev);
	hw_priv = अगरace->local->hw_priv;
	वापस पढ़ोb(hw_priv->mem_start + a);
पूर्ण

अटल अंतरभूत व्योम hfa384x_outw(काष्ठा net_device *dev, पूर्णांक a, u16 v)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	काष्ठा hostap_pci_priv *hw_priv;
	अगरace = netdev_priv(dev);
	hw_priv = अगरace->local->hw_priv;
	ग_लिखोw(v, hw_priv->mem_start + a);
पूर्ण

अटल अंतरभूत u16 hfa384x_inw(काष्ठा net_device *dev, पूर्णांक a)
अणु
	काष्ठा hostap_पूर्णांकerface *अगरace;
	काष्ठा hostap_pci_priv *hw_priv;
	अगरace = netdev_priv(dev);
	hw_priv = अगरace->local->hw_priv;
	वापस पढ़ोw(hw_priv->mem_start + a);
पूर्ण

#घोषणा HFA384X_OUTB(v,a) hfa384x_outb(dev, (a), (v))
#घोषणा HFA384X_INB(a) hfa384x_inb(dev, (a))
#घोषणा HFA384X_OUTW(v,a) hfa384x_outw(dev, (a), (v))
#घोषणा HFA384X_INW(a) hfa384x_inw(dev, (a))
#घोषणा HFA384X_OUTW_DATA(v,a) hfa384x_outw(dev, (a), le16_to_cpu((v)))
#घोषणा HFA384X_INW_DATA(a) cpu_to_le16(hfa384x_inw(dev, (a)))

#पूर्ण_अगर /* PRISM2_IO_DEBUG */


अटल पूर्णांक hfa384x_from_bap(काष्ठा net_device *dev, u16 bap, व्योम *buf,
			    पूर्णांक len)
अणु
	u16 d_off;
	__le16 *pos;

	d_off = (bap == 1) ? HFA384X_DATA1_OFF : HFA384X_DATA0_OFF;
	pos = (__le16 *) buf;

	क्रम ( ; len > 1; len -= 2)
		*pos++ = HFA384X_INW_DATA(d_off);

	अगर (len & 1)
		*((अक्षर *) pos) = HFA384X_INB(d_off);

	वापस 0;
पूर्ण


अटल पूर्णांक hfa384x_to_bap(काष्ठा net_device *dev, u16 bap, व्योम *buf, पूर्णांक len)
अणु
	u16 d_off;
	__le16 *pos;

	d_off = (bap == 1) ? HFA384X_DATA1_OFF : HFA384X_DATA0_OFF;
	pos = (__le16 *) buf;

	क्रम ( ; len > 1; len -= 2)
		HFA384X_OUTW_DATA(*pos++, d_off);

	अगर (len & 1)
		HFA384X_OUTB(*((अक्षर *) pos), d_off);

	वापस 0;
पूर्ण


/* FIX: This might change at some poपूर्णांक.. */
#समावेश "hostap_hw.c"

अटल व्योम prism2_pci_cor_sreset(local_info_t *local)
अणु
	काष्ठा net_device *dev = local->dev;
	u16 reg;

	reg = HFA384X_INB(HFA384X_PCICOR_OFF);
	prपूर्णांकk(KERN_DEBUG "%s: Original COR value: 0x%0x\n", dev->name, reg);

	/* linux-wlan-ng uses extremely दीर्घ hold and settle बार क्रम
	 * COR sreset. A comment in the driver code mentions that the दीर्घ
	 * delays appear to be necessary. However, at least IBM 22P6901 seems
	 * to work fine with लघुer delays.
	 *
	 * Longer delays can be configured by uncommenting following line: */
/* #घोषणा PRISM2_PCI_USE_LONG_DELAYS */

#अगर_घोषित PRISM2_PCI_USE_LONG_DELAYS
	पूर्णांक i;

	HFA384X_OUTW(reg | 0x0080, HFA384X_PCICOR_OFF);
	mdelay(250);

	HFA384X_OUTW(reg & ~0x0080, HFA384X_PCICOR_OFF);
	mdelay(500);

	/* Wait क्रम f/w to complete initialization (CMD:BUSY == 0) */
	i = 2000000 / 10;
	जबतक ((HFA384X_INW(HFA384X_CMD_OFF) & HFA384X_CMD_BUSY) && --i)
		udelay(10);

#अन्यथा /* PRISM2_PCI_USE_LONG_DELAYS */

	HFA384X_OUTW(reg | 0x0080, HFA384X_PCICOR_OFF);
	mdelay(2);
	HFA384X_OUTW(reg & ~0x0080, HFA384X_PCICOR_OFF);
	mdelay(2);

#पूर्ण_अगर /* PRISM2_PCI_USE_LONG_DELAYS */

	अगर (HFA384X_INW(HFA384X_CMD_OFF) & HFA384X_CMD_BUSY) अणु
		prपूर्णांकk(KERN_DEBUG "%s: COR sreset timeout\n", dev->name);
	पूर्ण
पूर्ण


अटल व्योम prism2_pci_genesis_reset(local_info_t *local, पूर्णांक hcr)
अणु
	काष्ठा net_device *dev = local->dev;

	HFA384X_OUTW(0x00C5, HFA384X_PCICOR_OFF);
	mdelay(10);
	HFA384X_OUTW(hcr, HFA384X_PCIHCR_OFF);
	mdelay(10);
	HFA384X_OUTW(0x0045, HFA384X_PCICOR_OFF);
	mdelay(10);
पूर्ण


अटल काष्ठा prism2_helper_functions prism2_pci_funcs =
अणु
	.card_present	= शून्य,
	.cor_sreset	= prism2_pci_cor_sreset,
	.genesis_reset	= prism2_pci_genesis_reset,
	.hw_type	= HOSTAP_HW_PCI,
पूर्ण;


अटल पूर्णांक prism2_pci_probe(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *id)
अणु
	अचिन्हित दीर्घ phymem;
	व्योम __iomem *mem = शून्य;
	local_info_t *local = शून्य;
	काष्ठा net_device *dev = शून्य;
	अटल पूर्णांक cards_found /* = 0 */;
	पूर्णांक irq_रेजिस्टरed = 0;
	काष्ठा hostap_पूर्णांकerface *अगरace;
	काष्ठा hostap_pci_priv *hw_priv;

	hw_priv = kzalloc(माप(*hw_priv), GFP_KERNEL);
	अगर (hw_priv == शून्य)
		वापस -ENOMEM;

	अगर (pci_enable_device(pdev))
		जाओ err_out_मुक्त;

	phymem = pci_resource_start(pdev, 0);

	अगर (!request_mem_region(phymem, pci_resource_len(pdev, 0), "Prism2")) अणु
		prपूर्णांकk(KERN_ERR "prism2: Cannot reserve PCI memory region\n");
		जाओ err_out_disable;
	पूर्ण

	mem = pci_ioremap_bar(pdev, 0);
	अगर (mem == शून्य) अणु
		prपूर्णांकk(KERN_ERR "prism2: Cannot remap PCI memory region\n") ;
		जाओ fail;
	पूर्ण

	dev = prism2_init_local_data(&prism2_pci_funcs, cards_found,
				     &pdev->dev);
	अगर (dev == शून्य)
		जाओ fail;
	अगरace = netdev_priv(dev);
	local = अगरace->local;
	local->hw_priv = hw_priv;
	cards_found++;

        dev->irq = pdev->irq;
        hw_priv->mem_start = mem;
	dev->base_addr = (अचिन्हित दीर्घ) mem;

	prism2_pci_cor_sreset(local);

	pci_set_drvdata(pdev, dev);

	अगर (request_irq(dev->irq, prism2_पूर्णांकerrupt, IRQF_SHARED, dev->name,
			dev)) अणु
		prपूर्णांकk(KERN_WARNING "%s: request_irq failed\n", dev->name);
		जाओ fail;
	पूर्ण अन्यथा
		irq_रेजिस्टरed = 1;

	अगर (!local->pri_only && prism2_hw_config(dev, 1)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: hardware initialization failed\n",
		       dev_info);
		जाओ fail;
	पूर्ण

	prपूर्णांकk(KERN_INFO "%s: Intersil Prism2.5 PCI: "
	       "mem=0x%lx, irq=%d\n", dev->name, phymem, dev->irq);

	वापस hostap_hw_पढ़ोy(dev);

 fail:
	अगर (irq_रेजिस्टरed && dev)
		मुक्त_irq(dev->irq, dev);

	अगर (mem)
		iounmap(mem);

	release_mem_region(phymem, pci_resource_len(pdev, 0));

 err_out_disable:
	pci_disable_device(pdev);
	prism2_मुक्त_local_data(dev);

 err_out_मुक्त:
	kमुक्त(hw_priv);

	वापस -ENODEV;
पूर्ण


अटल व्योम prism2_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev;
	काष्ठा hostap_पूर्णांकerface *अगरace;
	व्योम __iomem *mem_start;
	काष्ठा hostap_pci_priv *hw_priv;

	dev = pci_get_drvdata(pdev);
	अगरace = netdev_priv(dev);
	hw_priv = अगरace->local->hw_priv;

	/* Reset the hardware, and ensure पूर्णांकerrupts are disabled. */
	prism2_pci_cor_sreset(अगरace->local);
	hfa384x_disable_पूर्णांकerrupts(dev);

	अगर (dev->irq)
		मुक्त_irq(dev->irq, dev);

	mem_start = hw_priv->mem_start;
	prism2_मुक्त_local_data(dev);
	kमुक्त(hw_priv);

	iounmap(mem_start);

	release_mem_region(pci_resource_start(pdev, 0),
			   pci_resource_len(pdev, 0));
	pci_disable_device(pdev);
पूर्ण

अटल पूर्णांक __maybe_unused prism2_pci_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);

	अगर (netअगर_running(dev)) अणु
		netअगर_stop_queue(dev);
		netअगर_device_detach(dev);
	पूर्ण
	prism2_suspend(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused prism2_pci_resume(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);

	prism2_hw_config(dev, 0);
	अगर (netअगर_running(dev)) अणु
		netअगर_device_attach(dev);
		netअगर_start_queue(dev);
	पूर्ण

	वापस 0;
पूर्ण

MODULE_DEVICE_TABLE(pci, prism2_pci_id_table);

अटल SIMPLE_DEV_PM_OPS(prism2_pci_pm_ops,
			 prism2_pci_suspend,
			 prism2_pci_resume);

अटल काष्ठा pci_driver prism2_pci_driver = अणु
	.name		= "hostap_pci",
	.id_table	= prism2_pci_id_table,
	.probe		= prism2_pci_probe,
	.हटाओ		= prism2_pci_हटाओ,
	.driver.pm	= &prism2_pci_pm_ops,
पूर्ण;

module_pci_driver(prism2_pci_driver);
