<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sni_82596.c -- driver क्रम पूर्णांकel 82596 ethernet controller, as
 *  		  used in older SNI RM machines
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>
#समावेश <linux/bitops.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>

#घोषणा SNI_82596_DRIVER_VERSION "SNI RM 82596 driver - Revision: 0.01"

अटल स्थिर अक्षर sni_82596_string[] = "snirm_82596";

#घोषणा SYSBUS      0x00004400

/* big endian CPU, 82596 little endian */
#घोषणा SWAP32(x)   cpu_to_le32((u32)(x))
#घोषणा SWAP16(x)   cpu_to_le16((u16)(x))

#घोषणा OPT_MPU_16BIT    0x01

#समावेश "lib82596.c"

MODULE_AUTHOR("Thomas Bogendoerfer");
MODULE_DESCRIPTION("i82596 driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:snirm_82596");
module_param(i596_debug, पूर्णांक, 0);
MODULE_PARM_DESC(i596_debug, "82596 debug mask");

अटल अंतरभूत व्योम ca(काष्ठा net_device *dev)
अणु
	काष्ठा i596_निजी *lp = netdev_priv(dev);

	ग_लिखोl(0, lp->ca);
पूर्ण


अटल व्योम mpu_port(काष्ठा net_device *dev, पूर्णांक c, dma_addr_t x)
अणु
	काष्ठा i596_निजी *lp = netdev_priv(dev);

	u32 v = (u32) (c) | (u32) (x);

	अगर (lp->options & OPT_MPU_16BIT) अणु
		ग_लिखोw(v & 0xffff, lp->mpu_port);
		wmb();  /* order ग_लिखोs to MPU port */
		udelay(1);
		ग_लिखोw(v >> 16, lp->mpu_port);
	पूर्ण अन्यथा अणु
		ग_लिखोl(v, lp->mpu_port);
		wmb();  /* order ग_लिखोs to MPU port */
		udelay(1);
		ग_लिखोl(v, lp->mpu_port);
	पूर्ण
पूर्ण


अटल पूर्णांक sni_82596_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा	net_device *netdevice;
	काष्ठा i596_निजी *lp;
	काष्ठा  resource *res, *ca, *idprom, *options;
	पूर्णांक	retval = -ENOMEM;
	व्योम __iomem *mpu_addr;
	व्योम __iomem *ca_addr;
	u8 __iomem *eth_addr;

	res = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	ca = platक्रमm_get_resource(dev, IORESOURCE_MEM, 1);
	options = platक्रमm_get_resource(dev, 0, 0);
	idprom = platक्रमm_get_resource(dev, IORESOURCE_MEM, 2);
	अगर (!res || !ca || !options || !idprom)
		वापस -ENODEV;
	mpu_addr = ioremap(res->start, 4);
	अगर (!mpu_addr)
		वापस -ENOMEM;
	ca_addr = ioremap(ca->start, 4);
	अगर (!ca_addr)
		जाओ probe_failed_मुक्त_mpu;

	prपूर्णांकk(KERN_INFO "Found i82596 at 0x%x\n", res->start);

	netdevice = alloc_etherdev(माप(काष्ठा i596_निजी));
	अगर (!netdevice)
		जाओ probe_failed_मुक्त_ca;

	SET_NETDEV_DEV(netdevice, &dev->dev);
	platक्रमm_set_drvdata (dev, netdevice);

	netdevice->base_addr = res->start;
	netdevice->irq = platक्रमm_get_irq(dev, 0);

	eth_addr = ioremap(idprom->start, 0x10);
	अगर (!eth_addr)
		जाओ probe_failed;

	/* someone seems to like messed up stuff */
	netdevice->dev_addr[0] = पढ़ोb(eth_addr + 0x0b);
	netdevice->dev_addr[1] = पढ़ोb(eth_addr + 0x0a);
	netdevice->dev_addr[2] = पढ़ोb(eth_addr + 0x09);
	netdevice->dev_addr[3] = पढ़ोb(eth_addr + 0x08);
	netdevice->dev_addr[4] = पढ़ोb(eth_addr + 0x07);
	netdevice->dev_addr[5] = पढ़ोb(eth_addr + 0x06);
	iounmap(eth_addr);

	अगर (!netdevice->irq) अणु
		prपूर्णांकk(KERN_ERR "%s: IRQ not found for i82596 at 0x%lx\n",
			__खाता__, netdevice->base_addr);
		जाओ probe_failed;
	पूर्ण

	lp = netdev_priv(netdevice);
	lp->options = options->flags & IORESOURCE_BITS;
	lp->ca = ca_addr;
	lp->mpu_port = mpu_addr;

	lp->dma = dma_alloc_coherent(&dev->dev, माप(काष्ठा i596_dma),
				     &lp->dma_addr, GFP_KERNEL);
	अगर (!lp->dma)
		जाओ probe_failed;

	retval = i82596_probe(netdevice);
	अगर (retval)
		जाओ probe_failed_मुक्त_dma;
	वापस 0;

probe_failed_मुक्त_dma:
	dma_मुक्त_coherent(&dev->dev, माप(काष्ठा i596_dma), lp->dma,
			  lp->dma_addr);
probe_failed:
	मुक्त_netdev(netdevice);
probe_failed_मुक्त_ca:
	iounmap(ca_addr);
probe_failed_मुक्त_mpu:
	iounmap(mpu_addr);
	वापस retval;
पूर्ण

अटल पूर्णांक sni_82596_driver_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(pdev);
	काष्ठा i596_निजी *lp = netdev_priv(dev);

	unरेजिस्टर_netdev(dev);
	dma_मुक्त_coherent(&pdev->dev, माप(काष्ठा i596_निजी), lp->dma,
			  lp->dma_addr);
	iounmap(lp->ca);
	iounmap(lp->mpu_port);
	मुक्त_netdev (dev);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sni_82596_driver = अणु
	.probe	= sni_82596_probe,
	.हटाओ	= sni_82596_driver_हटाओ,
	.driver	= अणु
		.name	= sni_82596_string,
	पूर्ण,
पूर्ण;

अटल पूर्णांक sni_82596_init(व्योम)
अणु
	prपूर्णांकk(KERN_INFO SNI_82596_DRIVER_VERSION "\n");
	वापस platक्रमm_driver_रेजिस्टर(&sni_82596_driver);
पूर्ण


अटल व्योम __निकास sni_82596_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&sni_82596_driver);
पूर्ण

module_init(sni_82596_init);
module_निकास(sni_82596_निकास);
