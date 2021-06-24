<शैली गुरु>
/* New Hydra driver using generic 8390 core */
/* Based on old hydra driver by Topi Kanerva (topi@susanna.oulu.fi) */

/* This file is subject to the terms and conditions of the GNU General      */
/* Public License.  See the file COPYING in the मुख्य directory of the       */
/* Linux distribution क्रम more details.                                     */

/* Peter De Schrijver (p2@mind.be) */
/* Oldenburg 2000 */

/* The Amiganet is a Zorro-II board made by Hydra Systems. It contains a    */
/* NS8390 NIC (network पूर्णांकerface controller) clone, 16 or 64K on-board RAM  */
/* and 10BASE-2 (thin coax) and AUI connectors.                             */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/init.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/amigaपूर्णांकs.h>
#समावेश <यंत्र/amigahw.h>
#समावेश <linux/zorro.h>

#घोषणा EI_SHIFT(x)	(ei_local->reg_offset[x])
#घोषणा ei_inb(port)   in_8(port)
#घोषणा ei_outb(val,port)  out_8(port,val)
#घोषणा ei_inb_p(port)   in_8(port)
#घोषणा ei_outb_p(val,port)  out_8(port,val)

अटल स्थिर अक्षर version[] =
    "8390.c:v1.10cvs 9/23/94 Donald Becker (becker@cesdis.gsfc.nasa.gov)\n";

#समावेश "lib8390.c"

#घोषणा NE_EN0_DCFG     (0x0e*2)

#घोषणा NESM_START_PG   0x0    /* First page of TX buffer */
#घोषणा NESM_STOP_PG    0x40    /* Last page +1 of RX ring */

#घोषणा HYDRA_NIC_BASE 0xffe1
#घोषणा HYDRA_ADDRPROM 0xffc0
#घोषणा HYDRA_VERSION "v3.0alpha"

#घोषणा WORDSWAP(a)     ((((a)>>8)&0xff) | ((a)<<8))


अटल पूर्णांक hydra_init_one(काष्ठा zorro_dev *z,
				    स्थिर काष्ठा zorro_device_id *ent);
अटल पूर्णांक hydra_init(काष्ठा zorro_dev *z);
अटल पूर्णांक hydra_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक hydra_बंद(काष्ठा net_device *dev);
अटल व्योम hydra_reset_8390(काष्ठा net_device *dev);
अटल व्योम hydra_get_8390_hdr(काष्ठा net_device *dev,
			       काष्ठा e8390_pkt_hdr *hdr, पूर्णांक ring_page);
अटल व्योम hydra_block_input(काष्ठा net_device *dev, पूर्णांक count,
			      काष्ठा sk_buff *skb, पूर्णांक ring_offset);
अटल व्योम hydra_block_output(काष्ठा net_device *dev, पूर्णांक count,
			       स्थिर अचिन्हित अक्षर *buf, पूर्णांक start_page);
अटल व्योम hydra_हटाओ_one(काष्ठा zorro_dev *z);

अटल काष्ठा zorro_device_id hydra_zorro_tbl[] = अणु
    अणु ZORRO_PROD_HYDRA_SYSTEMS_AMIGANET पूर्ण,
    अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(zorro, hydra_zorro_tbl);

अटल काष्ठा zorro_driver hydra_driver = अणु
    .name	= "hydra",
    .id_table	= hydra_zorro_tbl,
    .probe	= hydra_init_one,
    .हटाओ	= hydra_हटाओ_one,
पूर्ण;

अटल पूर्णांक hydra_init_one(काष्ठा zorro_dev *z,
			  स्थिर काष्ठा zorro_device_id *ent)
अणु
    पूर्णांक err;

    अगर (!request_mem_region(z->resource.start, 0x10000, "Hydra"))
	वापस -EBUSY;
    अगर ((err = hydra_init(z))) अणु
	release_mem_region(z->resource.start, 0x10000);
	वापस -EBUSY;
    पूर्ण
    वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops hydra_netdev_ops = अणु
	.nकरो_खोलो		= hydra_खोलो,
	.nकरो_stop		= hydra_बंद,

	.nकरो_start_xmit		= __ei_start_xmit,
	.nकरो_tx_समयout		= __ei_tx_समयout,
	.nकरो_get_stats		= __ei_get_stats,
	.nकरो_set_rx_mode	= __ei_set_multicast_list,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= __ei_poll,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक hydra_init(काष्ठा zorro_dev *z)
अणु
    काष्ठा net_device *dev;
    अचिन्हित दीर्घ board = (अचिन्हित दीर्घ)ZTWO_VADDR(z->resource.start);
    अचिन्हित दीर्घ ioaddr = board+HYDRA_NIC_BASE;
    स्थिर अक्षर name[] = "NE2000";
    पूर्णांक start_page, stop_page;
    पूर्णांक j;
    पूर्णांक err;

    अटल u32 hydra_offsets[16] = अणु
	0x00, 0x02, 0x04, 0x06, 0x08, 0x0a, 0x0c, 0x0e,
	0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e,
    पूर्ण;

    dev = ____alloc_ei_netdev(0);
    अगर (!dev)
	वापस -ENOMEM;

    क्रम (j = 0; j < ETH_ALEN; j++)
	dev->dev_addr[j] = *((u8 *)(board + HYDRA_ADDRPROM + 2*j));

    /* We must set the 8390 क्रम word mode. */
    z_ग_लिखोb(0x4b, ioaddr + NE_EN0_DCFG);
    start_page = NESM_START_PG;
    stop_page = NESM_STOP_PG;

    dev->base_addr = ioaddr;
    dev->irq = IRQ_AMIGA_PORTS;

    /* Install the Interrupt handler */
    अगर (request_irq(IRQ_AMIGA_PORTS, __ei_पूर्णांकerrupt, IRQF_SHARED, "Hydra Ethernet",
		    dev)) अणु
	मुक्त_netdev(dev);
	वापस -EAGAIN;
    पूर्ण

    ei_status.name = name;
    ei_status.tx_start_page = start_page;
    ei_status.stop_page = stop_page;
    ei_status.word16 = 1;
    ei_status.bigendian = 1;

    ei_status.rx_start_page = start_page + TX_PAGES;

    ei_status.reset_8390 = hydra_reset_8390;
    ei_status.block_input = hydra_block_input;
    ei_status.block_output = hydra_block_output;
    ei_status.get_8390_hdr = hydra_get_8390_hdr;
    ei_status.reg_offset = hydra_offsets;

    dev->netdev_ops = &hydra_netdev_ops;
    __NS8390_init(dev, 0);

    err = रेजिस्टर_netdev(dev);
    अगर (err) अणु
	मुक्त_irq(IRQ_AMIGA_PORTS, dev);
	मुक्त_netdev(dev);
	वापस err;
    पूर्ण

    zorro_set_drvdata(z, dev);

    pr_info("%s: Hydra at %pR, address %pM (hydra.c " HYDRA_VERSION ")\n",
	    dev->name, &z->resource, dev->dev_addr);

    वापस 0;
पूर्ण

अटल पूर्णांक hydra_खोलो(काष्ठा net_device *dev)
अणु
    __ei_खोलो(dev);
    वापस 0;
पूर्ण

अटल पूर्णांक hydra_बंद(काष्ठा net_device *dev)
अणु
    काष्ठा ei_device *ei_local = netdev_priv(dev);

    netअगर_dbg(ei_local, अगरकरोwn, dev, "Shutting down ethercard.\n");
    __ei_बंद(dev);
    वापस 0;
पूर्ण

अटल व्योम hydra_reset_8390(काष्ठा net_device *dev)
अणु
    netdev_info(dev, "Hydra hw reset not there\n");
पूर्ण

अटल व्योम hydra_get_8390_hdr(काष्ठा net_device *dev,
			       काष्ठा e8390_pkt_hdr *hdr, पूर्णांक ring_page)
अणु
    पूर्णांक nic_base = dev->base_addr;
    लघु *ptrs;
    अचिन्हित दीर्घ hdr_start= (nic_base-HYDRA_NIC_BASE) +
			     ((ring_page - NESM_START_PG)<<8);
    ptrs = (लघु *)hdr;

    *(ptrs++) = z_पढ़ोw(hdr_start);
    *((लघु *)hdr) = WORDSWAP(*((लघु *)hdr));
    hdr_start += 2;
    *(ptrs++) = z_पढ़ोw(hdr_start);
    *((लघु *)hdr+1) = WORDSWAP(*((लघु *)hdr+1));
पूर्ण

अटल व्योम hydra_block_input(काष्ठा net_device *dev, पूर्णांक count,
			      काष्ठा sk_buff *skb, पूर्णांक ring_offset)
अणु
    अचिन्हित दीर्घ nic_base = dev->base_addr;
    अचिन्हित दीर्घ mem_base = nic_base - HYDRA_NIC_BASE;
    अचिन्हित दीर्घ xfer_start = mem_base + ring_offset - (NESM_START_PG<<8);

    अगर (count&1)
	count++;

    अगर (xfer_start+count >  mem_base + (NESM_STOP_PG<<8)) अणु
	पूर्णांक semi_count = (mem_base + (NESM_STOP_PG<<8)) - xfer_start;

	z_स_नकल_fromio(skb->data,xfer_start,semi_count);
	count -= semi_count;
	z_स_नकल_fromio(skb->data+semi_count, mem_base, count);
    पूर्ण अन्यथा
	z_स_नकल_fromio(skb->data, xfer_start,count);

पूर्ण

अटल व्योम hydra_block_output(काष्ठा net_device *dev, पूर्णांक count,
			       स्थिर अचिन्हित अक्षर *buf, पूर्णांक start_page)
अणु
    अचिन्हित दीर्घ nic_base = dev->base_addr;
    अचिन्हित दीर्घ mem_base = nic_base - HYDRA_NIC_BASE;

    अगर (count&1)
	count++;

    z_स_नकल_toio(mem_base+((start_page - NESM_START_PG)<<8), buf, count);
पूर्ण

अटल व्योम hydra_हटाओ_one(काष्ठा zorro_dev *z)
अणु
    काष्ठा net_device *dev = zorro_get_drvdata(z);

    unरेजिस्टर_netdev(dev);
    मुक्त_irq(IRQ_AMIGA_PORTS, dev);
    release_mem_region(ZTWO_PADDR(dev->base_addr)-HYDRA_NIC_BASE, 0x10000);
    मुक्त_netdev(dev);
पूर्ण

अटल पूर्णांक __init hydra_init_module(व्योम)
अणु
    वापस zorro_रेजिस्टर_driver(&hydra_driver);
पूर्ण

अटल व्योम __निकास hydra_cleanup_module(व्योम)
अणु
    zorro_unरेजिस्टर_driver(&hydra_driver);
पूर्ण

module_init(hydra_init_module);
module_निकास(hydra_cleanup_module);

MODULE_LICENSE("GPL");
