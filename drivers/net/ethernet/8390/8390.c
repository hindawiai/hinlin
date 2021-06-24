<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* 8390 core क्रम usual drivers */

अटल स्थिर अक्षर version[] =
    "8390.c:v1.10cvs 9/23/94 Donald Becker (becker@cesdis.gsfc.nasa.gov)\n";

#समावेश "lib8390.c"

पूर्णांक ei_खोलो(काष्ठा net_device *dev)
अणु
	वापस __ei_खोलो(dev);
पूर्ण
EXPORT_SYMBOL(ei_खोलो);

पूर्णांक ei_बंद(काष्ठा net_device *dev)
अणु
	वापस __ei_बंद(dev);
पूर्ण
EXPORT_SYMBOL(ei_बंद);

netdev_tx_t ei_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	वापस __ei_start_xmit(skb, dev);
पूर्ण
EXPORT_SYMBOL(ei_start_xmit);

काष्ठा net_device_stats *ei_get_stats(काष्ठा net_device *dev)
अणु
	वापस __ei_get_stats(dev);
पूर्ण
EXPORT_SYMBOL(ei_get_stats);

व्योम ei_set_multicast_list(काष्ठा net_device *dev)
अणु
	__ei_set_multicast_list(dev);
पूर्ण
EXPORT_SYMBOL(ei_set_multicast_list);

व्योम ei_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	__ei_tx_समयout(dev, txqueue);
पूर्ण
EXPORT_SYMBOL(ei_tx_समयout);

irqवापस_t ei_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	वापस __ei_पूर्णांकerrupt(irq, dev_id);
पूर्ण
EXPORT_SYMBOL(ei_पूर्णांकerrupt);

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
व्योम ei_poll(काष्ठा net_device *dev)
अणु
	__ei_poll(dev);
पूर्ण
EXPORT_SYMBOL(ei_poll);
#पूर्ण_अगर

स्थिर काष्ठा net_device_ops ei_netdev_ops = अणु
	.nकरो_खोलो		= ei_खोलो,
	.nकरो_stop		= ei_बंद,
	.nकरो_start_xmit		= ei_start_xmit,
	.nकरो_tx_समयout		= ei_tx_समयout,
	.nकरो_get_stats		= ei_get_stats,
	.nकरो_set_rx_mode	= ei_set_multicast_list,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address 	= eth_mac_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= ei_poll,
#पूर्ण_अगर
पूर्ण;
EXPORT_SYMBOL(ei_netdev_ops);

काष्ठा net_device *__alloc_ei_netdev(पूर्णांक size)
अणु
	काष्ठा net_device *dev = ____alloc_ei_netdev(size);
	अगर (dev)
		dev->netdev_ops = &ei_netdev_ops;
	वापस dev;
पूर्ण
EXPORT_SYMBOL(__alloc_ei_netdev);

व्योम NS8390_init(काष्ठा net_device *dev, पूर्णांक startp)
अणु
	__NS8390_init(dev, startp);
पूर्ण
EXPORT_SYMBOL(NS8390_init);

#अगर defined(MODULE)

अटल पूर्णांक __init ns8390_module_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम __निकास ns8390_module_निकास(व्योम)
अणु
पूर्ण

module_init(ns8390_module_init);
module_निकास(ns8390_module_निकास);
#पूर्ण_अगर /* MODULE */
MODULE_LICENSE("GPL");
