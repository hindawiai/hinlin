<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* hplance.c  : the  Linux/hp300/lance ethernet driver
 *
 * Copyright (C) 05/1998 Peter Maydell <pmaydell@chiark.greenend.org.uk>
 * Based on the Sun Lance driver and the NetBSD HP Lance driver
 * Uses the generic 7990.c LANCE code.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/माला.स>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pgtable.h>
/* Used क्रम the temporal inet entries and routing */
#समावेश <linux/socket.h>
#समावेश <linux/route.h>
#समावेश <linux/dपन.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>

#समावेश <यंत्र/पन.स>

#समावेश "hplance.h"

/* We have 16392 bytes of RAM क्रम the init block and buffers. This places
 * an upper limit on the number of buffers we can use. NetBSD uses 8 Rx
 * buffers and 2 Tx buffers, it takes (8 + 2) * 1544 bytes.
 */
#घोषणा LANCE_LOG_TX_BUFFERS 1
#घोषणा LANCE_LOG_RX_BUFFERS 3

#समावेश "7990.h"                                 /* use generic LANCE code */

/* Our निजी data काष्ठाure */
काष्ठा hplance_निजी अणु
	काष्ठा lance_निजी lance;
पूर्ण;

/* function prototypes... This is easy because all the grot is in the
 * generic LANCE support. All we have to support is probing क्रम boards,
 * plus board-specअगरic init, खोलो and बंद actions.
 * Oh, and we need to tell the generic code how to पढ़ो and ग_लिखो LANCE रेजिस्टरs...
 */
अटल पूर्णांक hplance_init_one(काष्ठा dio_dev *d, स्थिर काष्ठा dio_device_id *ent);
अटल व्योम hplance_init(काष्ठा net_device *dev, काष्ठा dio_dev *d);
अटल व्योम hplance_हटाओ_one(काष्ठा dio_dev *d);
अटल व्योम hplance_ग_लिखोrap(व्योम *priv, अचिन्हित लघु value);
अटल व्योम hplance_ग_लिखोrdp(व्योम *priv, अचिन्हित लघु value);
अटल अचिन्हित लघु hplance_पढ़ोrdp(व्योम *priv);
अटल पूर्णांक hplance_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक hplance_बंद(काष्ठा net_device *dev);

अटल काष्ठा dio_device_id hplance_dio_tbl[] = अणु
	अणु DIO_ID_LAN पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

अटल काष्ठा dio_driver hplance_driver = अणु
	.name      = "hplance",
	.id_table  = hplance_dio_tbl,
	.probe     = hplance_init_one,
	.हटाओ    = hplance_हटाओ_one,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops hplance_netdev_ops = अणु
	.nकरो_खोलो		= hplance_खोलो,
	.nकरो_stop		= hplance_बंद,
	.nकरो_start_xmit		= lance_start_xmit,
	.nकरो_set_rx_mode	= lance_set_multicast,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= lance_poll,
#पूर्ण_अगर
पूर्ण;

/* Find all the HP Lance boards and initialise them... */
अटल पूर्णांक hplance_init_one(काष्ठा dio_dev *d, स्थिर काष्ठा dio_device_id *ent)
अणु
	काष्ठा net_device *dev;
	पूर्णांक err = -ENOMEM;

	dev = alloc_etherdev(माप(काष्ठा hplance_निजी));
	अगर (!dev)
		जाओ out;

	err = -EBUSY;
	अगर (!request_mem_region(dio_resource_start(d),
				dio_resource_len(d), d->name))
		जाओ out_मुक्त_netdev;

	hplance_init(dev, d);
	err = रेजिस्टर_netdev(dev);
	अगर (err)
		जाओ out_release_mem_region;

	dio_set_drvdata(d, dev);

	prपूर्णांकk(KERN_INFO "%s: %s; select code %d, addr %pM, irq %d\n",
	       dev->name, d->name, d->scode, dev->dev_addr, d->ipl);

	वापस 0;

 out_release_mem_region:
	release_mem_region(dio_resource_start(d), dio_resource_len(d));
 out_मुक्त_netdev:
	मुक्त_netdev(dev);
 out:
	वापस err;
पूर्ण

अटल व्योम hplance_हटाओ_one(काष्ठा dio_dev *d)
अणु
	काष्ठा net_device *dev = dio_get_drvdata(d);

	unरेजिस्टर_netdev(dev);
	release_mem_region(dio_resource_start(d), dio_resource_len(d));
	मुक्त_netdev(dev);
पूर्ण

/* Initialise a single lance board at the given DIO device */
अटल व्योम hplance_init(काष्ठा net_device *dev, काष्ठा dio_dev *d)
अणु
	अचिन्हित दीर्घ va = (d->resource.start + DIO_VIRADDRBASE);
	काष्ठा hplance_निजी *lp;
	पूर्णांक i;

	/* reset the board */
	out_8(va + DIO_IDOFF, 0xff);
	udelay(100);                              /* ariba! ariba! udelay! udelay! */

	/* Fill the dev fields */
	dev->base_addr = va;
	dev->netdev_ops = &hplance_netdev_ops;
	dev->dma = 0;

	क्रम (i = 0; i < 6; i++) अणु
		/* The NVRAM holds our ethernet address, one nibble per byte,
		 * at bytes NVRAMOFF+1,3,5,7,9...
		 */
		dev->dev_addr[i] = ((in_8(va + HPLANCE_NVRAMOFF + i*4 + 1) & 0xF) << 4)
			| (in_8(va + HPLANCE_NVRAMOFF + i*4 + 3) & 0xF);
	पूर्ण

	lp = netdev_priv(dev);
	lp->lance.name = d->name;
	lp->lance.base = va;
	lp->lance.init_block = (काष्ठा lance_init_block *)(va + HPLANCE_MEMOFF); /* CPU addr */
	lp->lance.lance_init_block = शून्य;              /* LANCE addr of same RAM */
	lp->lance.busmaster_regval = LE_C3_BSWP;        /* we're bigendian */
	lp->lance.irq = d->ipl;
	lp->lance.ग_लिखोrap = hplance_ग_लिखोrap;
	lp->lance.ग_लिखोrdp = hplance_ग_लिखोrdp;
	lp->lance.पढ़ोrdp = hplance_पढ़ोrdp;
	lp->lance.lance_log_rx_bufs = LANCE_LOG_RX_BUFFERS;
	lp->lance.lance_log_tx_bufs = LANCE_LOG_TX_BUFFERS;
	lp->lance.rx_ring_mod_mask = RX_RING_MOD_MASK;
	lp->lance.tx_ring_mod_mask = TX_RING_MOD_MASK;
पूर्ण

/* This is disgusting. We have to check the DIO status रेजिस्टर क्रम ack every
 * समय we पढ़ो or ग_लिखो the LANCE रेजिस्टरs.
 */
अटल व्योम hplance_ग_लिखोrap(व्योम *priv, अचिन्हित लघु value)
अणु
	काष्ठा lance_निजी *lp = (काष्ठा lance_निजी *)priv;

	करो अणु
		out_be16(lp->base + HPLANCE_REGOFF + LANCE_RAP, value);
	पूर्ण जबतक ((in_8(lp->base + HPLANCE_STATUS) & LE_ACK) == 0);
पूर्ण

अटल व्योम hplance_ग_लिखोrdp(व्योम *priv, अचिन्हित लघु value)
अणु
	काष्ठा lance_निजी *lp = (काष्ठा lance_निजी *)priv;

	करो अणु
		out_be16(lp->base + HPLANCE_REGOFF + LANCE_RDP, value);
	पूर्ण जबतक ((in_8(lp->base + HPLANCE_STATUS) & LE_ACK) == 0);
पूर्ण

अटल अचिन्हित लघु hplance_पढ़ोrdp(व्योम *priv)
अणु
	काष्ठा lance_निजी *lp = (काष्ठा lance_निजी *)priv;
	__u16 value;

	करो अणु
		value = in_be16(lp->base + HPLANCE_REGOFF + LANCE_RDP);
	पूर्ण जबतक ((in_8(lp->base + HPLANCE_STATUS) & LE_ACK) == 0);
	वापस value;
पूर्ण

अटल पूर्णांक hplance_खोलो(काष्ठा net_device *dev)
अणु
	पूर्णांक status;
	काष्ठा lance_निजी *lp = netdev_priv(dev);

	status = lance_खोलो(dev);                 /* call generic lance खोलो code */
	अगर (status)
		वापस status;
	/* enable पूर्णांकerrupts at board level. */
	out_8(lp->base + HPLANCE_STATUS, LE_IE);

	वापस 0;
पूर्ण

अटल पूर्णांक hplance_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा lance_निजी *lp = netdev_priv(dev);

	out_8(lp->base + HPLANCE_STATUS, 0);	/* disable पूर्णांकerrupts at boardlevel */
	lance_बंद(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक __init hplance_init_module(व्योम)
अणु
	वापस dio_रेजिस्टर_driver(&hplance_driver);
पूर्ण

अटल व्योम __निकास hplance_cleanup_module(व्योम)
अणु
	dio_unरेजिस्टर_driver(&hplance_driver);
पूर्ण

module_init(hplance_init_module);
module_निकास(hplance_cleanup_module);

MODULE_LICENSE("GPL");
