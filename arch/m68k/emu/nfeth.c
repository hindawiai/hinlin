<शैली गुरु>
/*
 * atari_nfeth.c - ARAnyM ethernet card driver क्रम GNU/Linux
 *
 * Copyright (c) 2005 Milan Jurik, Petr Stehlik of ARAnyM dev team
 *
 * Based on ARAnyM driver क्रम FreeMiNT written by Standa Opichal
 *
 * This software may be used and distributed according to the terms of
 * the GNU General Public License (GPL), incorporated herein by reference.
 */

#घोषणा DRV_VERSION	"0.3"
#घोषणा DRV_RELDATE	"10/12/2005"

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/natfeat.h>
#समावेश <यंत्र/virtconvert.h>

क्रमागत अणु
	GET_VERSION = 0,/* no parameters, वापस NFAPI_VERSION in d0 */
	XIF_INTLEVEL,	/* no parameters, वापस Interrupt Level in d0 */
	XIF_IRQ,	/* acknowledge पूर्णांकerrupt from host */
	XIF_START,	/* (ethX), called on 'ifup', start receiver thपढ़ो */
	XIF_STOP,	/* (ethX), called on 'ifdown', stop the thपढ़ो */
	XIF_READLENGTH,	/* (ethX), वापस size of network data block to पढ़ो */
	XIF_READBLOCK,	/* (ethX, buffer, size), पढ़ो block of network data */
	XIF_WRITEBLOCK,	/* (ethX, buffer, size), ग_लिखो block of network data */
	XIF_GET_MAC,	/* (ethX, buffer, size), वापस MAC HW addr in buffer */
	XIF_GET_IPHOST,	/* (ethX, buffer, size), वापस IP address of host */
	XIF_GET_IPATARI,/* (ethX, buffer, size), वापस IP address of atari */
	XIF_GET_NETMASK	/* (ethX, buffer, size), वापस IP neपंचांगask */
पूर्ण;

#घोषणा MAX_UNIT	8

/* These identअगरy the driver base version and may not be हटाओd. */
अटल स्थिर अक्षर version[] =
	KERN_INFO KBUILD_MODNAME ".c:v" DRV_VERSION " " DRV_RELDATE
	" S.Opichal, M.Jurik, P.Stehlik\n"
	KERN_INFO " http://aranym.org/\n";

MODULE_AUTHOR("Milan Jurik");
MODULE_DESCRIPTION("Atari NFeth driver");
MODULE_LICENSE("GPL");


अटल दीर्घ nfEtherID;
अटल पूर्णांक nfEtherIRQ;

काष्ठा nfeth_निजी अणु
	पूर्णांक ethX;
पूर्ण;

अटल काष्ठा net_device *nfeth_dev[MAX_UNIT];

अटल पूर्णांक nfeth_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा nfeth_निजी *priv = netdev_priv(dev);
	पूर्णांक res;

	res = nf_call(nfEtherID + XIF_START, priv->ethX);
	netdev_dbg(dev, "%s: %d\n", __func__, res);

	/* Ready क्रम data */
	netअगर_start_queue(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक nfeth_stop(काष्ठा net_device *dev)
अणु
	काष्ठा nfeth_निजी *priv = netdev_priv(dev);

	/* No more data */
	netअगर_stop_queue(dev);

	nf_call(nfEtherID + XIF_STOP, priv->ethX);

	वापस 0;
पूर्ण

/*
 * Read a packet out of the adapter and pass it to the upper layers
 */
अटल अंतरभूत व्योम recv_packet(काष्ठा net_device *dev)
अणु
	काष्ठा nfeth_निजी *priv = netdev_priv(dev);
	अचिन्हित लघु pktlen;
	काष्ठा sk_buff *skb;

	/* पढ़ो packet length (excluding 32 bit crc) */
	pktlen = nf_call(nfEtherID + XIF_READLENGTH, priv->ethX);

	netdev_dbg(dev, "%s: %u\n", __func__, pktlen);

	अगर (!pktlen) अणु
		netdev_dbg(dev, "%s: pktlen == 0\n", __func__);
		dev->stats.rx_errors++;
		वापस;
	पूर्ण

	skb = dev_alloc_skb(pktlen + 2);
	अगर (!skb) अणु
		netdev_dbg(dev, "%s: out of mem (buf_alloc failed)\n",
			   __func__);
		dev->stats.rx_dropped++;
		वापस;
	पूर्ण

	skb->dev = dev;
	skb_reserve(skb, 2);		/* 16 Byte align  */
	skb_put(skb, pktlen);		/* make room */
	nf_call(nfEtherID + XIF_READBLOCK, priv->ethX, virt_to_phys(skb->data),
		pktlen);

	skb->protocol = eth_type_trans(skb, dev);
	netअगर_rx(skb);
	dev->stats.rx_packets++;
	dev->stats.rx_bytes += pktlen;

	/* and enqueue packet */
	वापस;
पूर्ण

अटल irqवापस_t nfeth_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक i, m, mask;

	mask = nf_call(nfEtherID + XIF_IRQ, 0);
	क्रम (i = 0, m = 1; i < MAX_UNIT; m <<= 1, i++) अणु
		अगर (mask & m && nfeth_dev[i]) अणु
			recv_packet(nfeth_dev[i]);
			nf_call(nfEtherID + XIF_IRQ, m);
		पूर्ण
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक nfeth_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक len;
	अक्षर *data, लघुpkt[ETH_ZLEN];
	काष्ठा nfeth_निजी *priv = netdev_priv(dev);

	data = skb->data;
	len = skb->len;
	अगर (len < ETH_ZLEN) अणु
		स_रखो(लघुpkt, 0, ETH_ZLEN);
		स_नकल(लघुpkt, data, len);
		data = लघुpkt;
		len = ETH_ZLEN;
	पूर्ण

	netdev_dbg(dev, "%s: send %u bytes\n", __func__, len);
	nf_call(nfEtherID + XIF_WRITEBLOCK, priv->ethX, virt_to_phys(data),
		len);

	dev->stats.tx_packets++;
	dev->stats.tx_bytes += len;

	dev_kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल व्योम nfeth_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	dev->stats.tx_errors++;
	netअगर_wake_queue(dev);
पूर्ण

अटल स्थिर काष्ठा net_device_ops nfeth_netdev_ops = अणु
	.nकरो_खोलो		= nfeth_खोलो,
	.nकरो_stop		= nfeth_stop,
	.nकरो_start_xmit		= nfeth_xmit,
	.nकरो_tx_समयout		= nfeth_tx_समयout,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
पूर्ण;

अटल काष्ठा net_device * __init nfeth_probe(पूर्णांक unit)
अणु
	काष्ठा net_device *dev;
	काष्ठा nfeth_निजी *priv;
	अक्षर mac[ETH_ALEN], host_ip[32], local_ip[32];
	पूर्णांक err;

	अगर (!nf_call(nfEtherID + XIF_GET_MAC, unit, virt_to_phys(mac),
		     ETH_ALEN))
		वापस शून्य;

	dev = alloc_etherdev(माप(काष्ठा nfeth_निजी));
	अगर (!dev)
		वापस शून्य;

	dev->irq = nfEtherIRQ;
	dev->netdev_ops = &nfeth_netdev_ops;

	स_नकल(dev->dev_addr, mac, ETH_ALEN);

	priv = netdev_priv(dev);
	priv->ethX = unit;

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		मुक्त_netdev(dev);
		वापस शून्य;
	पूर्ण

	nf_call(nfEtherID + XIF_GET_IPHOST, unit,
		virt_to_phys(host_ip), माप(host_ip));
	nf_call(nfEtherID + XIF_GET_IPATARI, unit,
		virt_to_phys(local_ip), माप(local_ip));

	netdev_info(dev, KBUILD_MODNAME " addr:%s (%s) HWaddr:%pM\n", host_ip,
		    local_ip, mac);

	वापस dev;
पूर्ण

अटल पूर्णांक __init nfeth_init(व्योम)
अणु
	दीर्घ ver;
	पूर्णांक error, i;

	nfEtherID = nf_get_id("ETHERNET");
	अगर (!nfEtherID)
		वापस -ENODEV;

	ver = nf_call(nfEtherID + GET_VERSION);
	pr_info("API %lu\n", ver);

	nfEtherIRQ = nf_call(nfEtherID + XIF_INTLEVEL);
	error = request_irq(nfEtherIRQ, nfeth_पूर्णांकerrupt, IRQF_SHARED,
			    "eth emu", nfeth_पूर्णांकerrupt);
	अगर (error) अणु
		pr_err("request for irq %d failed %d", nfEtherIRQ, error);
		वापस error;
	पूर्ण

	क्रम (i = 0; i < MAX_UNIT; i++)
		nfeth_dev[i] = nfeth_probe(i);

	वापस 0;
पूर्ण

अटल व्योम __निकास nfeth_cleanup(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_UNIT; i++) अणु
		अगर (nfeth_dev[i]) अणु
			unरेजिस्टर_netdev(nfeth_dev[0]);
			मुक्त_netdev(nfeth_dev[0]);
		पूर्ण
	पूर्ण
	मुक्त_irq(nfEtherIRQ, nfeth_पूर्णांकerrupt);
पूर्ण

module_init(nfeth_init);
module_निकास(nfeth_cleanup);
