<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* mvme147.c  : the  Linux/mvme147/lance ethernet driver
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
#समावेश <linux/gfp.h>
#समावेश <linux/pgtable.h>
/* Used क्रम the temporal inet entries and routing */
#समावेश <linux/socket.h>
#समावेश <linux/route.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/mvme147hw.h>

/* We have 32K of RAM क्रम the init block and buffers. This places
 * an upper limit on the number of buffers we can use. NetBSD uses 8 Rx
 * buffers and 2 Tx buffers, it takes (8 + 2) * 1544 bytes.
 */
#घोषणा LANCE_LOG_TX_BUFFERS 1
#घोषणा LANCE_LOG_RX_BUFFERS 3

#समावेश "7990.h"                                 /* use generic LANCE code */

/* Our निजी data काष्ठाure */
काष्ठा m147lance_निजी अणु
	काष्ठा lance_निजी lance;
	अचिन्हित दीर्घ ram;
पूर्ण;

/* function prototypes... This is easy because all the grot is in the
 * generic LANCE support. All we have to support is probing क्रम boards,
 * plus board-specअगरic init, खोलो and बंद actions.
 * Oh, and we need to tell the generic code how to पढ़ो and ग_लिखो LANCE रेजिस्टरs...
 */
अटल पूर्णांक m147lance_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक m147lance_बंद(काष्ठा net_device *dev);
अटल व्योम m147lance_ग_लिखोrap(काष्ठा lance_निजी *lp, अचिन्हित लघु value);
अटल व्योम m147lance_ग_लिखोrdp(काष्ठा lance_निजी *lp, अचिन्हित लघु value);
अटल अचिन्हित लघु m147lance_पढ़ोrdp(काष्ठा lance_निजी *lp);

प्रकार व्योम (*ग_लिखोrap_t)(व्योम *, अचिन्हित लघु);
प्रकार व्योम (*ग_लिखोrdp_t)(व्योम *, अचिन्हित लघु);
प्रकार अचिन्हित लघु (*पढ़ोrdp_t)(व्योम *);

अटल स्थिर काष्ठा net_device_ops lance_netdev_ops = अणु
	.nकरो_खोलो		= m147lance_खोलो,
	.nकरो_stop		= m147lance_बंद,
	.nकरो_start_xmit		= lance_start_xmit,
	.nकरो_set_rx_mode	= lance_set_multicast,
	.nकरो_tx_समयout		= lance_tx_समयout,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
पूर्ण;

/* Initialise the one and only on-board 7990 */
काष्ठा net_device * __init mvme147lance_probe(पूर्णांक unit)
अणु
	काष्ठा net_device *dev;
	अटल पूर्णांक called;
	अटल स्थिर अक्षर name[] = "MVME147 LANCE";
	काष्ठा m147lance_निजी *lp;
	u_दीर्घ *addr;
	u_दीर्घ address;
	पूर्णांक err;

	अगर (!MACH_IS_MVME147 || called)
		वापस ERR_PTR(-ENODEV);
	called++;

	dev = alloc_etherdev(माप(काष्ठा m147lance_निजी));
	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);

	अगर (unit >= 0)
		प्र_लिखो(dev->name, "eth%d", unit);

	/* Fill the dev fields */
	dev->base_addr = (अचिन्हित दीर्घ)MVME147_LANCE_BASE;
	dev->netdev_ops = &lance_netdev_ops;
	dev->dma = 0;

	addr = (u_दीर्घ *)ETHERNET_ADDRESS;
	address = *addr;
	dev->dev_addr[0] = 0x08;
	dev->dev_addr[1] = 0x00;
	dev->dev_addr[2] = 0x3e;
	address = address >> 8;
	dev->dev_addr[5] = address&0xff;
	address = address >> 8;
	dev->dev_addr[4] = address&0xff;
	address = address >> 8;
	dev->dev_addr[3] = address&0xff;

	prपूर्णांकk("%s: MVME147 at 0x%08lx, irq %d, Hardware Address %pM\n",
	       dev->name, dev->base_addr, MVME147_LANCE_IRQ,
	       dev->dev_addr);

	lp = netdev_priv(dev);
	lp->ram = __get_dma_pages(GFP_ATOMIC, 3);	/* 32K */
	अगर (!lp->ram) अणु
		prपूर्णांकk("%s: No memory for LANCE buffers\n", dev->name);
		मुक्त_netdev(dev);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	lp->lance.name = name;
	lp->lance.base = dev->base_addr;
	lp->lance.init_block = (काष्ठा lance_init_block *)(lp->ram); /* CPU addr */
	lp->lance.lance_init_block = (काष्ठा lance_init_block *)(lp->ram);                 /* LANCE addr of same RAM */
	lp->lance.busmaster_regval = LE_C3_BSWP;        /* we're bigendian */
	lp->lance.irq = MVME147_LANCE_IRQ;
	lp->lance.ग_लिखोrap = (ग_लिखोrap_t)m147lance_ग_लिखोrap;
	lp->lance.ग_लिखोrdp = (ग_लिखोrdp_t)m147lance_ग_लिखोrdp;
	lp->lance.पढ़ोrdp = (पढ़ोrdp_t)m147lance_पढ़ोrdp;
	lp->lance.lance_log_rx_bufs = LANCE_LOG_RX_BUFFERS;
	lp->lance.lance_log_tx_bufs = LANCE_LOG_TX_BUFFERS;
	lp->lance.rx_ring_mod_mask = RX_RING_MOD_MASK;
	lp->lance.tx_ring_mod_mask = TX_RING_MOD_MASK;

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		मुक्त_pages(lp->ram, 3);
		मुक्त_netdev(dev);
		वापस ERR_PTR(err);
	पूर्ण

	वापस dev;
पूर्ण

अटल व्योम m147lance_ग_लिखोrap(काष्ठा lance_निजी *lp, अचिन्हित लघु value)
अणु
	out_be16(lp->base + LANCE_RAP, value);
पूर्ण

अटल व्योम m147lance_ग_लिखोrdp(काष्ठा lance_निजी *lp, अचिन्हित लघु value)
अणु
	out_be16(lp->base + LANCE_RDP, value);
पूर्ण

अटल अचिन्हित लघु m147lance_पढ़ोrdp(काष्ठा lance_निजी *lp)
अणु
	वापस in_be16(lp->base + LANCE_RDP);
पूर्ण

अटल पूर्णांक m147lance_खोलो(काष्ठा net_device *dev)
अणु
	पूर्णांक status;

	status = lance_खोलो(dev);                 /* call generic lance खोलो code */
	अगर (status)
		वापस status;
	/* enable पूर्णांकerrupts at board level. */
	m147_pcc->lan_cntrl = 0;       /* clear the पूर्णांकerrupts (अगर any) */
	m147_pcc->lan_cntrl = 0x08 | 0x04;     /* Enable irq 4 */

	वापस 0;
पूर्ण

अटल पूर्णांक m147lance_बंद(काष्ठा net_device *dev)
अणु
	/* disable पूर्णांकerrupts at boardlevel */
	m147_pcc->lan_cntrl = 0x0; /* disable पूर्णांकerrupts */
	lance_बंद(dev);
	वापस 0;
पूर्ण

#अगर_घोषित MODULE
MODULE_LICENSE("GPL");

अटल काष्ठा net_device *dev_mvme147_lance;
पूर्णांक __init init_module(व्योम)
अणु
	dev_mvme147_lance = mvme147lance_probe(-1);
	वापस PTR_ERR_OR_ZERO(dev_mvme147_lance);
पूर्ण

व्योम __निकास cleanup_module(व्योम)
अणु
	काष्ठा m147lance_निजी *lp = netdev_priv(dev_mvme147_lance);
	unरेजिस्टर_netdev(dev_mvme147_lance);
	मुक्त_pages(lp->ram, 3);
	मुक्त_netdev(dev_mvme147_lance);
पूर्ण

#पूर्ण_अगर /* MODULE */
