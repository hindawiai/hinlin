<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* 8390 core क्रम ISA devices needing bus delays */

अटल स्थिर अक्षर version[] =
    "8390p.c:v1.10cvs 9/23/94 Donald Becker (becker@cesdis.gsfc.nasa.gov)\n";

#घोषणा ei_inb(_p)	inb(_p)
#घोषणा ei_outb(_v, _p)	outb(_v, _p)
#घोषणा ei_inb_p(_p)	inb_p(_p)
#घोषणा ei_outb_p(_v, _p) outb_p(_v, _p)

#समावेश "lib8390.c"

पूर्णांक eip_खोलो(काष्ठा net_device *dev)
अणु
	वापस __ei_खोलो(dev);
पूर्ण
EXPORT_SYMBOL(eip_खोलो);

पूर्णांक eip_बंद(काष्ठा net_device *dev)
अणु
	वापस __ei_बंद(dev);
पूर्ण
EXPORT_SYMBOL(eip_बंद);

netdev_tx_t eip_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	वापस __ei_start_xmit(skb, dev);
पूर्ण
EXPORT_SYMBOL(eip_start_xmit);

काष्ठा net_device_stats *eip_get_stats(काष्ठा net_device *dev)
अणु
	वापस __ei_get_stats(dev);
पूर्ण
EXPORT_SYMBOL(eip_get_stats);

व्योम eip_set_multicast_list(काष्ठा net_device *dev)
अणु
	__ei_set_multicast_list(dev);
पूर्ण
EXPORT_SYMBOL(eip_set_multicast_list);

व्योम eip_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	__ei_tx_समयout(dev, txqueue);
पूर्ण
EXPORT_SYMBOL(eip_tx_समयout);

irqवापस_t eip_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	वापस __ei_पूर्णांकerrupt(irq, dev_id);
पूर्ण
EXPORT_SYMBOL(eip_पूर्णांकerrupt);

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
व्योम eip_poll(काष्ठा net_device *dev)
अणु
	__ei_poll(dev);
पूर्ण
EXPORT_SYMBOL(eip_poll);
#पूर्ण_अगर

स्थिर काष्ठा net_device_ops eip_netdev_ops = अणु
	.nकरो_खोलो		= eip_खोलो,
	.nकरो_stop		= eip_बंद,
	.nकरो_start_xmit		= eip_start_xmit,
	.nकरो_tx_समयout		= eip_tx_समयout,
	.nकरो_get_stats		= eip_get_stats,
	.nकरो_set_rx_mode	= eip_set_multicast_list,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address 	= eth_mac_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= eip_poll,
#पूर्ण_अगर
पूर्ण;
EXPORT_SYMBOL(eip_netdev_ops);

काष्ठा net_device *__alloc_eip_netdev(पूर्णांक size)
अणु
	काष्ठा net_device *dev = ____alloc_ei_netdev(size);
	अगर (dev)
		dev->netdev_ops = &eip_netdev_ops;
	वापस dev;
पूर्ण
EXPORT_SYMBOL(__alloc_eip_netdev);

व्योम NS8390p_init(काष्ठा net_device *dev, पूर्णांक startp)
अणु
	__NS8390_init(dev, startp);
पूर्ण
EXPORT_SYMBOL(NS8390p_init);

अटल पूर्णांक __init NS8390p_init_module(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम __निकास NS8390p_cleanup_module(व्योम)
अणु
पूर्ण

module_init(NS8390p_init_module);
module_निकास(NS8390p_cleanup_module);
MODULE_LICENSE("GPL");
