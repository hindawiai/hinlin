<शैली गुरु>
/* stnic.c : A SH7750 specअगरic part of driver क्रम NS DP83902A ST-NIC.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1999 kaz Kojima
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>

#समावेश <यंत्र/पन.स>
#समावेश <mach-se/mach/se.h>
#समावेश <यंत्र/machvec.h>
#अगर_घोषित CONFIG_SH_STANDARD_BIOS
#समावेश <यंत्र/sh_मूलप्रण.स>
#पूर्ण_अगर

#समावेश "8390.h"

#घोषणा DRV_NAME "stnic"

#घोषणा byte	अचिन्हित अक्षर
#घोषणा half	अचिन्हित लघु
#घोषणा word	अचिन्हित पूर्णांक
#घोषणा vbyte	अस्थिर अचिन्हित अक्षर
#घोषणा vhalf	अस्थिर अचिन्हित लघु
#घोषणा vword	अस्थिर अचिन्हित पूर्णांक

#घोषणा STNIC_RUN	0x01	/* 1 == Run, 0 == reset. */

#घोषणा START_PG	0	/* First page of TX buffer */
#घोषणा STOP_PG		128	/* Last page +1 of RX ring */

/* Alias */
#घोषणा STNIC_CR	E8390_CMD
#घोषणा PG0_RSAR0	EN0_RSARLO
#घोषणा PG0_RSAR1	EN0_RSARHI
#घोषणा PG0_RBCR0	EN0_RCNTLO
#घोषणा PG0_RBCR1	EN0_RCNTHI

#घोषणा CR_RRD		E8390_RREAD
#घोषणा CR_RWR		E8390_RWRITE
#घोषणा CR_PG0		E8390_PAGE0
#घोषणा CR_STA		E8390_START
#घोषणा CR_RDMA		E8390_NODMA

/* FIXME! YOU MUST SET YOUR OWN ETHER ADDRESS.  */
अटल byte stnic_eadr[6] =
अणु0x00, 0xc0, 0x6e, 0x00, 0x00, 0x07पूर्ण;

अटल काष्ठा net_device *stnic_dev;

अटल व्योम stnic_reset (काष्ठा net_device *dev);
अटल व्योम stnic_get_hdr (काष्ठा net_device *dev, काष्ठा e8390_pkt_hdr *hdr,
			   पूर्णांक ring_page);
अटल व्योम stnic_block_input (काष्ठा net_device *dev, पूर्णांक count,
			       काष्ठा sk_buff *skb , पूर्णांक ring_offset);
अटल व्योम stnic_block_output (काष्ठा net_device *dev, पूर्णांक count,
				स्थिर अचिन्हित अक्षर *buf, पूर्णांक start_page);

अटल व्योम stnic_init (काष्ठा net_device *dev);

अटल u32 stnic_msg_enable;

module_param_named(msg_enable, stnic_msg_enable, uपूर्णांक, 0444);
MODULE_PARM_DESC(msg_enable, "Debug message level (see linux/netdevice.h for bitmap)");

/* SH7750 specअगरic पढ़ो/ग_लिखो io. */
अटल अंतरभूत व्योम
STNIC_DELAY (व्योम)
अणु
  vword trash;
  trash = *(vword *) 0xa0000000;
  trash = *(vword *) 0xa0000000;
  trash = *(vword *) 0xa0000000;
पूर्ण

अटल अंतरभूत byte
STNIC_READ (पूर्णांक reg)
अणु
  byte val;

  val = (*(vhalf *) (PA_83902 + ((reg) << 1)) >> 8) & 0xff;
  STNIC_DELAY ();
  वापस val;
पूर्ण

अटल अंतरभूत व्योम
STNIC_WRITE (पूर्णांक reg, byte val)
अणु
  *(vhalf *) (PA_83902 + ((reg) << 1)) = ((half) (val) << 8);
  STNIC_DELAY ();
पूर्ण

अटल पूर्णांक __init stnic_probe(व्योम)
अणु
  काष्ठा net_device *dev;
  पूर्णांक i, err;
  काष्ठा ei_device *ei_local;

  /* If we are not running on a SolutionEngine, give up now */
  अगर (! MACH_SE)
    वापस -ENODEV;

  /* New style probing API */
  dev = alloc_ei_netdev();
  अगर (!dev)
  	वापस -ENOMEM;

#अगर_घोषित CONFIG_SH_STANDARD_BIOS
  sh_bios_get_node_addr (stnic_eadr);
#पूर्ण_अगर
  क्रम (i = 0; i < ETH_ALEN; i++)
    dev->dev_addr[i] = stnic_eadr[i];

  /* Set the base address to poपूर्णांक to the NIC, not the "real" base! */
  dev->base_addr = 0x1000;
  dev->irq = IRQ_STNIC;
  dev->netdev_ops = &ei_netdev_ops;

  /* Snarf the पूर्णांकerrupt now.  There's no poपूर्णांक in रुकोing since we cannot
     share and the board will usually be enabled. */
  err = request_irq (dev->irq, ei_पूर्णांकerrupt, 0, DRV_NAME, dev);
  अगर (err)  अणु
	netdev_emerg(dev, " unable to get IRQ %d.\n", dev->irq);
	मुक्त_netdev(dev);
	वापस err;
  पूर्ण

  ei_status.name = dev->name;
  ei_status.word16 = 1;
#अगर_घोषित __LITTLE_ENDIAN__
  ei_status.bigendian = 0;
#अन्यथा
  ei_status.bigendian = 1;
#पूर्ण_अगर
  ei_status.tx_start_page = START_PG;
  ei_status.rx_start_page = START_PG + TX_PAGES;
  ei_status.stop_page = STOP_PG;

  ei_status.reset_8390 = &stnic_reset;
  ei_status.get_8390_hdr = &stnic_get_hdr;
  ei_status.block_input = &stnic_block_input;
  ei_status.block_output = &stnic_block_output;

  stnic_init (dev);
  ei_local = netdev_priv(dev);
  ei_local->msg_enable = stnic_msg_enable;

  err = रेजिस्टर_netdev(dev);
  अगर (err) अणु
    मुक्त_irq(dev->irq, dev);
    मुक्त_netdev(dev);
    वापस err;
  पूर्ण
  stnic_dev = dev;

  netdev_info(dev, "NS ST-NIC 83902A\n");

  वापस 0;
पूर्ण

अटल व्योम
stnic_reset (काष्ठा net_device *dev)
अणु
  काष्ठा ei_device *ei_local = netdev_priv(dev);

  *(vhalf *) PA_83902_RST = 0;
  udelay (5);
  netअगर_warn(ei_local, hw, dev, "8390 reset done (%ld).\n", jअगरfies);
  *(vhalf *) PA_83902_RST = ~0;
  udelay (5);
पूर्ण

अटल व्योम
stnic_get_hdr (काष्ठा net_device *dev, काष्ठा e8390_pkt_hdr *hdr,
	       पूर्णांक ring_page)
अणु
  काष्ठा ei_device *ei_local = netdev_priv(dev);

  half buf[2];

  STNIC_WRITE (PG0_RSAR0, 0);
  STNIC_WRITE (PG0_RSAR1, ring_page);
  STNIC_WRITE (PG0_RBCR0, 4);
  STNIC_WRITE (PG0_RBCR1, 0);
  STNIC_WRITE (STNIC_CR, CR_RRD | CR_PG0 | CR_STA);

  buf[0] = *(vhalf *) PA_83902_IF;
  STNIC_DELAY ();
  buf[1] = *(vhalf *) PA_83902_IF;
  STNIC_DELAY ();
  hdr->next = buf[0] >> 8;
  hdr->status = buf[0] & 0xff;
#अगर_घोषित __LITTLE_ENDIAN__
  hdr->count = buf[1];
#अन्यथा
  hdr->count = ((buf[1] >> 8) & 0xff) | (buf[1] << 8);
#पूर्ण_अगर

  netअगर_dbg(ei_local, probe, dev, "ring %x status %02x next %02x count %04x.\n",
	    ring_page, hdr->status, hdr->next, hdr->count);

  STNIC_WRITE (STNIC_CR, CR_RDMA | CR_PG0 | CR_STA);
पूर्ण

/* Block input and output, similar to the Crynwr packet driver. If you are
   porting to a new ethercard look at the packet driver source क्रम hपूर्णांकs.
   The HP LAN करोesn't use shared memory -- we put the packet
   out through the "remote DMA" dataport. */

अटल व्योम
stnic_block_input (काष्ठा net_device *dev, पूर्णांक length, काष्ठा sk_buff *skb,
		   पूर्णांक offset)
अणु
  अक्षर *buf = skb->data;
  half val;

  STNIC_WRITE (PG0_RSAR0, offset & 0xff);
  STNIC_WRITE (PG0_RSAR1, offset >> 8);
  STNIC_WRITE (PG0_RBCR0, length & 0xff);
  STNIC_WRITE (PG0_RBCR1, length >> 8);
  STNIC_WRITE (STNIC_CR, CR_RRD | CR_PG0 | CR_STA);

  अगर (length & 1)
    length++;

  जबतक (length > 0)
    अणु
      val = *(vhalf *) PA_83902_IF;
#अगर_घोषित __LITTLE_ENDIAN__
      *buf++ = val & 0xff;
      *buf++ = val >> 8;
#अन्यथा
      *buf++ = val >> 8;
      *buf++ = val & 0xff;
#पूर्ण_अगर
      STNIC_DELAY ();
      length -= माप (half);
    पूर्ण

  STNIC_WRITE (STNIC_CR, CR_RDMA | CR_PG0 | CR_STA);
पूर्ण

अटल व्योम
stnic_block_output (काष्ठा net_device *dev, पूर्णांक length,
		    स्थिर अचिन्हित अक्षर *buf, पूर्णांक output_page)
अणु
  STNIC_WRITE (PG0_RBCR0, 1);	/* Write non-zero value */
  STNIC_WRITE (STNIC_CR, CR_RRD | CR_PG0 | CR_STA);
  STNIC_DELAY ();

  STNIC_WRITE (PG0_RBCR0, length & 0xff);
  STNIC_WRITE (PG0_RBCR1, length >> 8);
  STNIC_WRITE (PG0_RSAR0, 0);
  STNIC_WRITE (PG0_RSAR1, output_page);
  STNIC_WRITE (STNIC_CR, CR_RWR | CR_PG0 | CR_STA);

  अगर (length & 1)
    length++;

  जबतक (length > 0)
    अणु
#अगर_घोषित __LITTLE_ENDIAN__
      *(vhalf *) PA_83902_IF = ((half) buf[1] << 8) | buf[0];
#अन्यथा
      *(vhalf *) PA_83902_IF = ((half) buf[0] << 8) | buf[1];
#पूर्ण_अगर
      STNIC_DELAY ();
      buf += माप (half);
      length -= माप (half);
    पूर्ण

  STNIC_WRITE (STNIC_CR, CR_RDMA | CR_PG0 | CR_STA);
पूर्ण

/* This function resets the STNIC अगर something screws up.  */
अटल व्योम
stnic_init (काष्ठा net_device *dev)
अणु
  stnic_reset (dev);
  NS8390_init (dev, 0);
पूर्ण

अटल व्योम __निकास stnic_cleanup(व्योम)
अणु
	unरेजिस्टर_netdev(stnic_dev);
	मुक्त_irq(stnic_dev->irq, stnic_dev);
	मुक्त_netdev(stnic_dev);
पूर्ण

module_init(stnic_probe);
module_निकास(stnic_cleanup);
MODULE_LICENSE("GPL");
