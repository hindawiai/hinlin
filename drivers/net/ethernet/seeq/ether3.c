<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/acorn/net/ether3.c
 *
 *  Copyright (C) 1995-2000 Russell King
 *
 * SEEQ nq8005 ethernet driver क्रम Acorn/ANT Ether3 card
 *  क्रम Acorn machines
 *
 * By Russell King, with some suggestions from borris@ant.co.uk
 *
 * Changelog:
 * 1.04	RMK	29/02/1996	Won't pass packets that are from our ethernet
 *				address up to the higher levels - they're
 *				silently ignored.  I/F can now be put पूर्णांकo
 *				multicast mode.  Receiver routine optimised.
 * 1.05	RMK	30/02/1996	Now claims पूर्णांकerrupt at खोलो when part of
 *				the kernel rather than when a module.
 * 1.06	RMK	02/03/1996	Various code cleanups
 * 1.07	RMK	13/10/1996	Optimised पूर्णांकerrupt routine and transmit
 *				routines.
 * 1.08	RMK	14/10/1996	Fixed problem with too many packets,
 *				prevented the kernel message about dropped
 *				packets appearing too many बार a second.
 *				Now करोes not disable all IRQs, only the IRQ
 *				used by this card.
 * 1.09	RMK	10/11/1996	Only enables TX irq when buffer space is low,
 *				but we still service the TX queue अगर we get a
 *				RX पूर्णांकerrupt.
 * 1.10	RMK	15/07/1997	Fixed स्वतःprobing of NQ8004.
 * 1.11	RMK	16/11/1997	Fixed स्वतःprobing of NQ8005A.
 * 1.12	RMK	31/12/1997	Removed reference to dev_tपूर्णांक क्रम Linux 2.1.
 *      RMK	27/06/1998	Changed यंत्र/delay.h to linux/delay.h.
 * 1.13	RMK	29/06/1998	Fixed problem with transmission of packets.
 *				Chip seems to have a bug in, whereby अगर the
 *				packet starts two bytes from the end of the
 *				buffer, it corrupts the receiver chain, and
 *				never updates the transmit status correctly.
 * 1.14	RMK	07/01/1998	Added initial code क्रम ETHERB addressing.
 * 1.15	RMK	30/04/1999	More fixes to the transmit routine क्रम buggy
 *				hardware.
 * 1.16	RMK	10/02/2000	Updated क्रम 2.3.43
 * 1.17	RMK	13/05/2000	Updated क्रम 2.3.99-pre8
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/in.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/ecard.h>
#समावेश <यंत्र/पन.स>

अटल अक्षर version[] = "ether3 ethernet driver (c) 1995-2000 R.M.King v1.17\n";

#समावेश "ether3.h"

अटल अचिन्हित पूर्णांक net_debug = NET_DEBUG;

अटल व्योम	ether3_seपंचांगulticastlist(काष्ठा net_device *dev);
अटल पूर्णांक	ether3_rx(काष्ठा net_device *dev, अचिन्हित पूर्णांक maxcnt);
अटल व्योम	ether3_tx(काष्ठा net_device *dev);
अटल पूर्णांक	ether3_खोलो (काष्ठा net_device *dev);
अटल netdev_tx_t	ether3_sendpacket(काष्ठा sk_buff *skb,
					  काष्ठा net_device *dev);
अटल irqवापस_t ether3_पूर्णांकerrupt (पूर्णांक irq, व्योम *dev_id);
अटल पूर्णांक	ether3_बंद (काष्ठा net_device *dev);
अटल व्योम	ether3_seपंचांगulticastlist (काष्ठा net_device *dev);
अटल व्योम	ether3_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);

#घोषणा BUS_16		2
#घोषणा BUS_8		1
#घोषणा BUS_UNKNOWN	0

/* --------------------------------------------------------------------------- */

प्रकार क्रमागत अणु
	buffer_ग_लिखो,
	buffer_पढ़ो
पूर्ण buffer_rw_t;

/*
 * ether3 पढ़ो/ग_लिखो.  Slow things करोwn a bit...
 * The SEEQ8005 करोesn't like us writing to its रेजिस्टरs
 * too quickly.
 */
अटल अंतरभूत व्योम ether3_outb(पूर्णांक v, व्योम __iomem *r)
अणु
	ग_लिखोb(v, r);
	udelay(1);
पूर्ण

अटल अंतरभूत व्योम ether3_outw(पूर्णांक v, व्योम __iomem *r)
अणु
	ग_लिखोw(v, r);
	udelay(1);
पूर्ण
#घोषणा ether3_inb(r)		(अणु अचिन्हित पूर्णांक __v = पढ़ोb((r)); udelay(1); __v; पूर्ण)
#घोषणा ether3_inw(r)		(अणु अचिन्हित पूर्णांक __v = पढ़ोw((r)); udelay(1); __v; पूर्ण)

अटल पूर्णांक
ether3_रखो_बफfer(काष्ठा net_device *dev, buffer_rw_t पढ़ो, पूर्णांक start)
अणु
	पूर्णांक समयout = 1000;

	ether3_outw(priv(dev)->regs.config1 | CFG1_LOCBUFMEM, REG_CONFIG1);
	ether3_outw(priv(dev)->regs.command | CMD_FIFOWRITE, REG_COMMAND);

	जबतक ((ether3_inw(REG_STATUS) & STAT_FIFOEMPTY) == 0) अणु
		अगर (!समयout--) अणु
			prपूर्णांकk("%s: setbuffer broken\n", dev->name);
			priv(dev)->broken = 1;
			वापस 1;
		पूर्ण
		udelay(1);
	पूर्ण

	अगर (पढ़ो == buffer_पढ़ो) अणु
		ether3_outw(start, REG_DMAADDR);
		ether3_outw(priv(dev)->regs.command | CMD_FIFOREAD, REG_COMMAND);
	पूर्ण अन्यथा अणु
		ether3_outw(priv(dev)->regs.command | CMD_FIFOWRITE, REG_COMMAND);
		ether3_outw(start, REG_DMAADDR);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * ग_लिखो data to the buffer memory
 */
#घोषणा ether3_ग_लिखोbuffer(dev,data,length)			\
	ग_लिखोsw(REG_BUFWIN, (data), (length) >> 1)

#घोषणा ether3_ग_लिखोword(dev,data)				\
	ग_लिखोw((data), REG_BUFWIN)

#घोषणा ether3_ग_लिखोदीर्घ(dev,data)	अणु			\
	व्योम __iomem *reg_bufwin = REG_BUFWIN;			\
	ग_लिखोw((data), reg_bufwin);				\
	ग_लिखोw((data) >> 16, reg_bufwin);			\
पूर्ण

/*
 * पढ़ो data from the buffer memory
 */
#घोषणा ether3_पढ़ोbuffer(dev,data,length)			\
	पढ़ोsw(REG_BUFWIN, (data), (length) >> 1)

#घोषणा ether3_पढ़ोword(dev)					\
	पढ़ोw(REG_BUFWIN)

#घोषणा ether3_पढ़ोदीर्घ(dev)	 				\
	पढ़ोw(REG_BUFWIN) | (पढ़ोw(REG_BUFWIN) << 16)

/*
 * Switch LED off...
 */
अटल व्योम ether3_leकरोff(काष्ठा समयr_list *t)
अणु
	काष्ठा dev_priv *निजी = from_समयr(निजी, t, समयr);
	काष्ठा net_device *dev = निजी->dev;

	ether3_outw(priv(dev)->regs.config2 |= CFG2_CTRLO, REG_CONFIG2);
पूर्ण

/*
 * चयन LED on...
 */
अटल अंतरभूत व्योम ether3_leकरोn(काष्ठा net_device *dev)
अणु
	del_समयr(&priv(dev)->समयr);
	priv(dev)->समयr.expires = jअगरfies + HZ / 50; /* leave on क्रम 1/50th second */
	add_समयr(&priv(dev)->समयr);
	अगर (priv(dev)->regs.config2 & CFG2_CTRLO)
		ether3_outw(priv(dev)->regs.config2 &= ~CFG2_CTRLO, REG_CONFIG2);
पूर्ण

/*
 * Read the ethernet address string from the on board rom.
 * This is an ascii string!!!
 */
अटल पूर्णांक
ether3_addr(अक्षर *addr, काष्ठा expansion_card *ec)
अणु
	काष्ठा in_chunk_dir cd;
	अक्षर *s;
	
	अगर (ecard_पढ़ोchunk(&cd, ec, 0xf5, 0) && (s = म_अक्षर(cd.d.string, '('))) अणु
		पूर्णांक i;
		क्रम (i = 0; i<6; i++) अणु
			addr[i] = simple_म_से_अदीर्घ(s + 1, &s, 0x10);
			अगर (*s != (i==5?')' : ':' ))
				अवरोध;
		पूर्ण
		अगर (i == 6)
			वापस 0;
	पूर्ण
	/* I wonder अगर we should even let the user जारी in this हाल
	 *   - no, it would be better to disable the device
	 */
	prपूर्णांकk(KERN_ERR "ether3: Couldn't read a valid MAC address from card.\n");
	वापस -ENODEV;
पूर्ण

/* --------------------------------------------------------------------------- */

अटल पूर्णांक
ether3_ramtest(काष्ठा net_device *dev, अचिन्हित अक्षर byte)
अणु
	अचिन्हित अक्षर *buffer = kदो_स्मृति(RX_END, GFP_KERNEL);
	पूर्णांक i,ret = 0;
	पूर्णांक max_errors = 4;
	पूर्णांक bad = -1;

	अगर (!buffer)
		वापस 1;

	स_रखो(buffer, byte, RX_END);
	ether3_रखो_बफfer(dev, buffer_ग_लिखो, 0);
	ether3_ग_लिखोbuffer(dev, buffer, TX_END);
	ether3_रखो_बफfer(dev, buffer_ग_लिखो, RX_START);
	ether3_ग_लिखोbuffer(dev, buffer + RX_START, RX_LEN);
	स_रखो(buffer, byte ^ 0xff, RX_END);
	ether3_रखो_बफfer(dev, buffer_पढ़ो, 0);
	ether3_पढ़ोbuffer(dev, buffer, TX_END);
	ether3_रखो_बफfer(dev, buffer_पढ़ो, RX_START);
	ether3_पढ़ोbuffer(dev, buffer + RX_START, RX_LEN);

	क्रम (i = 0; i < RX_END; i++) अणु
		अगर (buffer[i] != byte) अणु
			अगर (max_errors > 0 && bad != buffer[i]) अणु
				prपूर्णांकk("%s: RAM failed with (%02X instead of %02X) at 0x%04X",
				       dev->name, buffer[i], byte, i);
				ret = 2;
				max_errors--;
				bad = i;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (bad != -1) अणु
				अगर (bad != i - 1)
					prपूर्णांकk(" - 0x%04X\n", i - 1);
				prपूर्णांकk("\n");
				bad = -1;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (bad != -1)
		prपूर्णांकk(" - 0xffff\n");
	kमुक्त(buffer);

	वापस ret;
पूर्ण

/* ------------------------------------------------------------------------------- */

अटल पूर्णांक ether3_init_2(काष्ठा net_device *dev)
अणु
	पूर्णांक i;

	priv(dev)->regs.config1 = CFG1_RECVCOMPSTAT0|CFG1_DMABURST8;
	priv(dev)->regs.config2 = CFG2_CTRLO|CFG2_RECVCRC|CFG2_ERRENCRC;
	priv(dev)->regs.command = 0;

	/*
	 * Set up our hardware address
	 */
	ether3_outw(priv(dev)->regs.config1 | CFG1_BUFSELSTAT0, REG_CONFIG1);
	क्रम (i = 0; i < 6; i++)
		ether3_outb(dev->dev_addr[i], REG_BUFWIN);

	अगर (dev->flags & IFF_PROMISC)
		priv(dev)->regs.config1 |= CFG1_RECVPROMISC;
	अन्यथा अगर (dev->flags & IFF_MULTICAST)
		priv(dev)->regs.config1 |= CFG1_RECVSPECBRMULTI;
	अन्यथा
		priv(dev)->regs.config1 |= CFG1_RECVSPECBROAD;

	/*
	 * There is a problem with the NQ8005 in that it occasionally loses the
	 * last two bytes.  To get round this problem, we receive the CRC as
	 * well.  That way, अगर we करो lose the last two, then it करोesn't matter.
	 */
	ether3_outw(priv(dev)->regs.config1 | CFG1_TRANSEND, REG_CONFIG1);
	ether3_outw((TX_END>>8) - 1, REG_BUFWIN);
	ether3_outw(priv(dev)->rx_head, REG_RECVPTR);
	ether3_outw(0, REG_TRANSMITPTR);
	ether3_outw(priv(dev)->rx_head >> 8, REG_RECVEND);
	ether3_outw(priv(dev)->regs.config2, REG_CONFIG2);
	ether3_outw(priv(dev)->regs.config1 | CFG1_LOCBUFMEM, REG_CONFIG1);
	ether3_outw(priv(dev)->regs.command, REG_COMMAND);

	i = ether3_ramtest(dev, 0x5A);
	अगर(i)
		वापस i;
	i = ether3_ramtest(dev, 0x1E);
	अगर(i)
		वापस i;

	ether3_रखो_बफfer(dev, buffer_ग_लिखो, 0);
	ether3_ग_लिखोदीर्घ(dev, 0);
	वापस 0;
पूर्ण

अटल व्योम
ether3_init_क्रम_खोलो(काष्ठा net_device *dev)
अणु
	पूर्णांक i;

	/* Reset the chip */
	ether3_outw(CFG2_RESET, REG_CONFIG2);
	udelay(4);

	priv(dev)->regs.command = 0;
	ether3_outw(CMD_RXOFF|CMD_TXOFF, REG_COMMAND);
	जबतक (ether3_inw(REG_STATUS) & (STAT_RXON|STAT_TXON))
		barrier();

	ether3_outw(priv(dev)->regs.config1 | CFG1_BUFSELSTAT0, REG_CONFIG1);
	क्रम (i = 0; i < 6; i++)
		ether3_outb(dev->dev_addr[i], REG_BUFWIN);

	priv(dev)->tx_head	= 0;
	priv(dev)->tx_tail	= 0;
	priv(dev)->regs.config2 |= CFG2_CTRLO;
	priv(dev)->rx_head	= RX_START;

	ether3_outw(priv(dev)->regs.config1 | CFG1_TRANSEND, REG_CONFIG1);
	ether3_outw((TX_END>>8) - 1, REG_BUFWIN);
	ether3_outw(priv(dev)->rx_head, REG_RECVPTR);
	ether3_outw(priv(dev)->rx_head >> 8, REG_RECVEND);
	ether3_outw(0, REG_TRANSMITPTR);
	ether3_outw(priv(dev)->regs.config2, REG_CONFIG2);
	ether3_outw(priv(dev)->regs.config1 | CFG1_LOCBUFMEM, REG_CONFIG1);

	ether3_रखो_बफfer(dev, buffer_ग_लिखो, 0);
	ether3_ग_लिखोदीर्घ(dev, 0);

	priv(dev)->regs.command = CMD_ENINTRX | CMD_ENINTTX;
	ether3_outw(priv(dev)->regs.command | CMD_RXON, REG_COMMAND);
पूर्ण

अटल अंतरभूत पूर्णांक
ether3_probe_bus_8(काष्ठा net_device *dev, पूर्णांक val)
अणु
	पूर्णांक ग_लिखो_low, ग_लिखो_high, पढ़ो_low, पढ़ो_high;

	ग_लिखो_low = val & 255;
	ग_लिखो_high = val >> 8;

	prपूर्णांकk(KERN_DEBUG "ether3_probe: write8 [%02X:%02X]", ग_लिखो_high, ग_लिखो_low);

	ether3_outb(ग_लिखो_low, REG_RECVPTR);
	ether3_outb(ग_लिखो_high, REG_RECVPTR + 4);

	पढ़ो_low = ether3_inb(REG_RECVPTR);
	पढ़ो_high = ether3_inb(REG_RECVPTR + 4);

	prपूर्णांकk(", read8 [%02X:%02X]\n", पढ़ो_high, पढ़ो_low);

	वापस पढ़ो_low == ग_लिखो_low && पढ़ो_high == ग_लिखो_high;
पूर्ण

अटल अंतरभूत पूर्णांक
ether3_probe_bus_16(काष्ठा net_device *dev, पूर्णांक val)
अणु
	पूर्णांक पढ़ो_val;

	ether3_outw(val, REG_RECVPTR);
	पढ़ो_val = ether3_inw(REG_RECVPTR);

	prपूर्णांकk(KERN_DEBUG "ether3_probe: write16 [%04X], read16 [%04X]\n", val, पढ़ो_val);

	वापस पढ़ो_val == val;
पूर्ण

/*
 * Open/initialize the board.  This is called (in the current kernel)
 * someसमय after booting when the 'ifconfig' program is run.
 *
 * This routine should set everything up anew at each खोलो, even
 * रेजिस्टरs that "should" only need to be set once at boot, so that
 * there is non-reboot way to recover अगर something goes wrong.
 */
अटल पूर्णांक
ether3_खोलो(काष्ठा net_device *dev)
अणु
	अगर (request_irq(dev->irq, ether3_पूर्णांकerrupt, 0, "ether3", dev))
		वापस -EAGAIN;

	ether3_init_क्रम_खोलो(dev);

	netअगर_start_queue(dev);

	वापस 0;
पूर्ण

/*
 * The inverse routine to ether3_खोलो().
 */
अटल पूर्णांक
ether3_बंद(काष्ठा net_device *dev)
अणु
	netअगर_stop_queue(dev);

	disable_irq(dev->irq);

	ether3_outw(CMD_RXOFF|CMD_TXOFF, REG_COMMAND);
	priv(dev)->regs.command = 0;
	जबतक (ether3_inw(REG_STATUS) & (STAT_RXON|STAT_TXON))
		barrier();
	ether3_outb(0x80, REG_CONFIG2 + 4);
	ether3_outw(0, REG_COMMAND);

	मुक्त_irq(dev->irq, dev);

	वापस 0;
पूर्ण

/*
 * Set or clear promiscuous/multicast mode filter क्रम this adaptor.
 *
 * We करोn't attempt any packet filtering.  The card may have a SEEQ 8004
 * in which करोes not have the other ethernet address रेजिस्टरs present...
 */
अटल व्योम ether3_seपंचांगulticastlist(काष्ठा net_device *dev)
अणु
	priv(dev)->regs.config1 &= ~CFG1_RECVPROMISC;

	अगर (dev->flags & IFF_PROMISC) अणु
		/* promiscuous mode */
		priv(dev)->regs.config1 |= CFG1_RECVPROMISC;
	पूर्ण अन्यथा अगर (dev->flags & IFF_ALLMULTI || !netdev_mc_empty(dev)) अणु
		priv(dev)->regs.config1 |= CFG1_RECVSPECBRMULTI;
	पूर्ण अन्यथा
		priv(dev)->regs.config1 |= CFG1_RECVSPECBROAD;

	ether3_outw(priv(dev)->regs.config1 | CFG1_LOCBUFMEM, REG_CONFIG1);
पूर्ण

अटल व्योम ether3_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	अचिन्हित दीर्घ flags;

	del_समयr(&priv(dev)->समयr);

	local_irq_save(flags);
	prपूर्णांकk(KERN_ERR "%s: transmit timed out, network cable problem?\n", dev->name);
	prपूर्णांकk(KERN_ERR "%s: state: { status=%04X cfg1=%04X cfg2=%04X }\n", dev->name,
		ether3_inw(REG_STATUS), ether3_inw(REG_CONFIG1), ether3_inw(REG_CONFIG2));
	prपूर्णांकk(KERN_ERR "%s: { rpr=%04X rea=%04X tpr=%04X }\n", dev->name,
		ether3_inw(REG_RECVPTR), ether3_inw(REG_RECVEND), ether3_inw(REG_TRANSMITPTR));
	prपूर्णांकk(KERN_ERR "%s: tx head=%X tx tail=%X\n", dev->name,
		priv(dev)->tx_head, priv(dev)->tx_tail);
	ether3_रखो_बफfer(dev, buffer_पढ़ो, priv(dev)->tx_tail);
	prपूर्णांकk(KERN_ERR "%s: packet status = %08X\n", dev->name, ether3_पढ़ोदीर्घ(dev));
	local_irq_restore(flags);

	priv(dev)->regs.config2 |= CFG2_CTRLO;
	dev->stats.tx_errors += 1;
	ether3_outw(priv(dev)->regs.config2, REG_CONFIG2);
	priv(dev)->tx_head = priv(dev)->tx_tail = 0;

	netअगर_wake_queue(dev);
पूर्ण

/*
 * Transmit a packet
 */
अटल netdev_tx_t
ether3_sendpacket(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक length = ETH_ZLEN < skb->len ? skb->len : ETH_ZLEN;
	अचिन्हित पूर्णांक ptr, next_ptr;

	अगर (priv(dev)->broken) अणु
		dev_kमुक्त_skb(skb);
		dev->stats.tx_dropped++;
		netअगर_start_queue(dev);
		वापस NETDEV_TX_OK;
	पूर्ण

	length = (length + 1) & ~1;
	अगर (length != skb->len) अणु
		अगर (skb_padto(skb, length))
			जाओ out;
	पूर्ण

	next_ptr = (priv(dev)->tx_head + 1) & 15;

	local_irq_save(flags);

	अगर (priv(dev)->tx_tail == next_ptr) अणु
		local_irq_restore(flags);
		वापस NETDEV_TX_BUSY;	/* unable to queue */
	पूर्ण

	ptr		 = 0x600 * priv(dev)->tx_head;
	priv(dev)->tx_head = next_ptr;
	next_ptr	*= 0x600;

#घोषणा TXHDR_FLAGS (TXHDR_TRANSMIT|TXHDR_CHAINCONTINUE|TXHDR_DATAFOLLOWS|TXHDR_ENSUCCESS)

	ether3_रखो_बफfer(dev, buffer_ग_लिखो, next_ptr);
	ether3_ग_लिखोदीर्घ(dev, 0);
	ether3_रखो_बफfer(dev, buffer_ग_लिखो, ptr);
	ether3_ग_लिखोदीर्घ(dev, 0);
	ether3_ग_लिखोbuffer(dev, skb->data, length);
	ether3_ग_लिखोword(dev, htons(next_ptr));
	ether3_ग_लिखोword(dev, TXHDR_CHAINCONTINUE >> 16);
	ether3_रखो_बफfer(dev, buffer_ग_लिखो, ptr);
	ether3_ग_लिखोword(dev, htons((ptr + length + 4)));
	ether3_ग_लिखोword(dev, TXHDR_FLAGS >> 16);
	ether3_leकरोn(dev);

	अगर (!(ether3_inw(REG_STATUS) & STAT_TXON)) अणु
		ether3_outw(ptr, REG_TRANSMITPTR);
		ether3_outw(priv(dev)->regs.command | CMD_TXON, REG_COMMAND);
	पूर्ण

	next_ptr = (priv(dev)->tx_head + 1) & 15;
	local_irq_restore(flags);

	dev_kमुक्त_skb(skb);

	अगर (priv(dev)->tx_tail == next_ptr)
		netअगर_stop_queue(dev);

 out:
	वापस NETDEV_TX_OK;
पूर्ण

अटल irqवापस_t
ether3_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *)dev_id;
	अचिन्हित पूर्णांक status, handled = IRQ_NONE;

#अगर NET_DEBUG > 1
	अगर(net_debug & DEBUG_INT)
		prपूर्णांकk("eth3irq: %d ", irq);
#पूर्ण_अगर

	status = ether3_inw(REG_STATUS);

	अगर (status & STAT_INTRX) अणु
		ether3_outw(CMD_ACKINTRX | priv(dev)->regs.command, REG_COMMAND);
		ether3_rx(dev, 12);
		handled = IRQ_HANDLED;
	पूर्ण

	अगर (status & STAT_INTTX) अणु
		ether3_outw(CMD_ACKINTTX | priv(dev)->regs.command, REG_COMMAND);
		ether3_tx(dev);
		handled = IRQ_HANDLED;
	पूर्ण

#अगर NET_DEBUG > 1
	अगर(net_debug & DEBUG_INT)
		prपूर्णांकk("done\n");
#पूर्ण_अगर
	वापस handled;
पूर्ण

/*
 * If we have a good packet(s), get it/them out of the buffers.
 */
अटल पूर्णांक ether3_rx(काष्ठा net_device *dev, अचिन्हित पूर्णांक maxcnt)
अणु
	अचिन्हित पूर्णांक next_ptr = priv(dev)->rx_head, received = 0;

	ether3_leकरोn(dev);

	करो अणु
		अचिन्हित पूर्णांक this_ptr, status;
		अचिन्हित अक्षर addrs[16];

		/*
		 * पढ़ो the first 16 bytes from the buffer.
		 * This contains the status bytes etc and ethernet addresses,
		 * and we also check the source ethernet address to see अगर
		 * it originated from us.
		 */
		अणु
			अचिन्हित पूर्णांक temp_ptr;
			ether3_रखो_बफfer(dev, buffer_पढ़ो, next_ptr);
			temp_ptr = ether3_पढ़ोword(dev);
			status = ether3_पढ़ोword(dev);
			अगर ((status & (RXSTAT_DONE | RXHDR_CHAINCONTINUE | RXHDR_RECEIVE)) !=
				(RXSTAT_DONE | RXHDR_CHAINCONTINUE) || !temp_ptr)
				अवरोध;

			this_ptr = next_ptr + 4;
			next_ptr = ntohs(temp_ptr);
		पूर्ण
		ether3_रखो_बफfer(dev, buffer_पढ़ो, this_ptr);
		ether3_पढ़ोbuffer(dev, addrs+2, 12);

अगर (next_ptr < RX_START || next_ptr >= RX_END) अणु
 prपूर्णांकk("%s: bad next pointer @%04X: ", dev->name, priv(dev)->rx_head);
 prपूर्णांकk("%02X %02X %02X %02X ", next_ptr >> 8, next_ptr & 255, status & 255, status >> 8);
 prपूर्णांकk("%pM %pM\n", addrs + 2, addrs + 8);
 next_ptr = priv(dev)->rx_head;
 अवरोध;
पूर्ण
		/*
 		 * ignore our own packets...
	 	 */
		अगर (!(*(अचिन्हित दीर्घ *)&dev->dev_addr[0] ^ *(अचिन्हित दीर्घ *)&addrs[2+6]) &&
		    !(*(अचिन्हित लघु *)&dev->dev_addr[4] ^ *(अचिन्हित लघु *)&addrs[2+10])) अणु
			maxcnt ++; /* compensate क्रम loopedback packet */
			ether3_outw(next_ptr >> 8, REG_RECVEND);
		पूर्ण अन्यथा
		अगर (!(status & (RXSTAT_OVERSIZE|RXSTAT_CRCERROR|RXSTAT_DRIBBLEERROR|RXSTAT_SHORTPACKET))) अणु
			अचिन्हित पूर्णांक length = next_ptr - this_ptr;
			काष्ठा sk_buff *skb;

			अगर (next_ptr <= this_ptr)
				length += RX_END - RX_START;

			skb = netdev_alloc_skb(dev, length + 2);
			अगर (skb) अणु
				अचिन्हित अक्षर *buf;

				skb_reserve(skb, 2);
				buf = skb_put(skb, length);
				ether3_पढ़ोbuffer(dev, buf + 12, length - 12);
				ether3_outw(next_ptr >> 8, REG_RECVEND);
				*(अचिन्हित लघु *)(buf + 0)	= *(अचिन्हित लघु *)(addrs + 2);
				*(अचिन्हित दीर्घ *)(buf + 2)	= *(अचिन्हित दीर्घ *)(addrs + 4);
				*(अचिन्हित दीर्घ *)(buf + 6)	= *(अचिन्हित दीर्घ *)(addrs + 8);
				*(अचिन्हित लघु *)(buf + 10)	= *(अचिन्हित लघु *)(addrs + 12);
				skb->protocol = eth_type_trans(skb, dev);
				netअगर_rx(skb);
				received ++;
			पूर्ण अन्यथा अणु
				ether3_outw(next_ptr >> 8, REG_RECVEND);
				dev->stats.rx_dropped++;
				जाओ करोne;
			पूर्ण
		पूर्ण अन्यथा अणु
			काष्ठा net_device_stats *stats = &dev->stats;
			ether3_outw(next_ptr >> 8, REG_RECVEND);
			अगर (status & RXSTAT_OVERSIZE)	  stats->rx_over_errors ++;
			अगर (status & RXSTAT_CRCERROR)	  stats->rx_crc_errors ++;
			अगर (status & RXSTAT_DRIBBLEERROR) stats->rx_fअगरo_errors ++;
			अगर (status & RXSTAT_SHORTPACKET)  stats->rx_length_errors ++;
			stats->rx_errors++;
		पूर्ण
	पूर्ण
	जबतक (-- maxcnt);

करोne:
	dev->stats.rx_packets += received;
	priv(dev)->rx_head = next_ptr;
	/*
	 * If rx went off line, then that means that the buffer may be full.  We
	 * have dropped at least one packet.
	 */
	अगर (!(ether3_inw(REG_STATUS) & STAT_RXON)) अणु
		dev->stats.rx_dropped++;
    		ether3_outw(next_ptr, REG_RECVPTR);
		ether3_outw(priv(dev)->regs.command | CMD_RXON, REG_COMMAND);
	पूर्ण

	वापस maxcnt;
पूर्ण

/*
 * Update stats क्रम the transmitted packet(s)
 */
अटल व्योम ether3_tx(काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक tx_tail = priv(dev)->tx_tail;
	पूर्णांक max_work = 14;

	करो अणु
	    	अचिन्हित दीर्घ status;

    		/*
	    	 * Read the packet header
    		 */
	    	ether3_रखो_बफfer(dev, buffer_पढ़ो, tx_tail * 0x600);
    		status = ether3_पढ़ोदीर्घ(dev);

		/*
		 * Check to see अगर this packet has been transmitted
		 */
		अगर ((status & (TXSTAT_DONE | TXHDR_TRANSMIT)) !=
		    (TXSTAT_DONE | TXHDR_TRANSMIT))
			अवरोध;

		/*
		 * Update errors
		 */
		अगर (!(status & (TXSTAT_BABBLED | TXSTAT_16COLLISIONS)))
			dev->stats.tx_packets++;
		अन्यथा अणु
			dev->stats.tx_errors++;
			अगर (status & TXSTAT_16COLLISIONS)
				dev->stats.collisions += 16;
			अगर (status & TXSTAT_BABBLED)
				dev->stats.tx_fअगरo_errors++;
		पूर्ण

		tx_tail = (tx_tail + 1) & 15;
	पूर्ण जबतक (--max_work);

	अगर (priv(dev)->tx_tail != tx_tail) अणु
		priv(dev)->tx_tail = tx_tail;
		netअगर_wake_queue(dev);
	पूर्ण
पूर्ण

अटल व्योम ether3_banner(व्योम)
अणु
	अटल अचिन्हित version_prपूर्णांकed = 0;

	अगर (net_debug && version_prपूर्णांकed++ == 0)
		prपूर्णांकk(KERN_INFO "%s", version);
पूर्ण

अटल स्थिर काष्ठा net_device_ops ether3_netdev_ops = अणु
	.nकरो_खोलो		= ether3_खोलो,
	.nकरो_stop		= ether3_बंद,
	.nकरो_start_xmit		= ether3_sendpacket,
	.nकरो_set_rx_mode	= ether3_seपंचांगulticastlist,
	.nकरो_tx_समयout		= ether3_समयout,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
पूर्ण;

अटल पूर्णांक
ether3_probe(काष्ठा expansion_card *ec, स्थिर काष्ठा ecard_id *id)
अणु
	स्थिर काष्ठा ether3_data *data = id->data;
	काष्ठा net_device *dev;
	पूर्णांक bus_type, ret;

	ether3_banner();

	ret = ecard_request_resources(ec);
	अगर (ret)
		जाओ out;

	dev = alloc_etherdev(माप(काष्ठा dev_priv));
	अगर (!dev) अणु
		ret = -ENOMEM;
		जाओ release;
	पूर्ण

	SET_NETDEV_DEV(dev, &ec->dev);

	priv(dev)->base = ecardm_iomap(ec, ECARD_RES_MEMC, 0, 0);
	अगर (!priv(dev)->base) अणु
		ret = -ENOMEM;
		जाओ मुक्त;
	पूर्ण

	ec->irqaddr = priv(dev)->base + data->base_offset;
	ec->irqmask = 0xf0;

	priv(dev)->seeq = priv(dev)->base + data->base_offset;
	dev->irq = ec->irq;

	ether3_addr(dev->dev_addr, ec);

	priv(dev)->dev = dev;
	समयr_setup(&priv(dev)->समयr, ether3_leकरोff, 0);

	/* Reset card...
	 */
	ether3_outb(0x80, REG_CONFIG2 + 4);
	bus_type = BUS_UNKNOWN;
	udelay(4);

	/* Test using Receive Poपूर्णांकer (16-bit रेजिस्टर) to find out
	 * how the ether3 is connected to the bus...
	 */
	अगर (ether3_probe_bus_8(dev, 0x100) &&
	    ether3_probe_bus_8(dev, 0x201))
		bus_type = BUS_8;

	अगर (bus_type == BUS_UNKNOWN &&
	    ether3_probe_bus_16(dev, 0x101) &&
	    ether3_probe_bus_16(dev, 0x201))
		bus_type = BUS_16;

	चयन (bus_type) अणु
	हाल BUS_UNKNOWN:
		prपूर्णांकk(KERN_ERR "%s: unable to identify bus width\n", dev->name);
		ret = -ENODEV;
		जाओ मुक्त;

	हाल BUS_8:
		prपूर्णांकk(KERN_ERR "%s: %s found, but is an unsupported "
			"8-bit card\n", dev->name, data->name);
		ret = -ENODEV;
		जाओ मुक्त;

	शेष:
		अवरोध;
	पूर्ण

	अगर (ether3_init_2(dev)) अणु
		ret = -ENODEV;
		जाओ मुक्त;
	पूर्ण

	dev->netdev_ops		= &ether3_netdev_ops;
	dev->watchकरोg_समयo	= 5 * HZ / 100;

	ret = रेजिस्टर_netdev(dev);
	अगर (ret)
		जाओ मुक्त;

	prपूर्णांकk("%s: %s in slot %d, %pM\n",
	       dev->name, data->name, ec->slot_no, dev->dev_addr);

	ecard_set_drvdata(ec, dev);
	वापस 0;

 मुक्त:
	मुक्त_netdev(dev);
 release:
	ecard_release_resources(ec);
 out:
	वापस ret;
पूर्ण

अटल व्योम ether3_हटाओ(काष्ठा expansion_card *ec)
अणु
	काष्ठा net_device *dev = ecard_get_drvdata(ec);

	ecard_set_drvdata(ec, शून्य);

	unरेजिस्टर_netdev(dev);
	मुक्त_netdev(dev);
	ecard_release_resources(ec);
पूर्ण

अटल काष्ठा ether3_data ether3 = अणु
	.name		= "ether3",
	.base_offset	= 0,
पूर्ण;

अटल काष्ठा ether3_data etherb = अणु
	.name		= "etherb",
	.base_offset	= 0x800,
पूर्ण;

अटल स्थिर काष्ठा ecard_id ether3_ids[] = अणु
	अणु MANU_ANT2, PROD_ANT_ETHER3, &ether3 पूर्ण,
	अणु MANU_ANT,  PROD_ANT_ETHER3, &ether3 पूर्ण,
	अणु MANU_ANT,  PROD_ANT_ETHERB, &etherb पूर्ण,
	अणु 0xffff, 0xffff पूर्ण
पूर्ण;

अटल काष्ठा ecard_driver ether3_driver = अणु
	.probe		= ether3_probe,
	.हटाओ		= ether3_हटाओ,
	.id_table	= ether3_ids,
	.drv = अणु
		.name	= "ether3",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ether3_init(व्योम)
अणु
	वापस ecard_रेजिस्टर_driver(&ether3_driver);
पूर्ण

अटल व्योम __निकास ether3_निकास(व्योम)
अणु
	ecard_हटाओ_driver(&ether3_driver);
पूर्ण

module_init(ether3_init);
module_निकास(ether3_निकास);

MODULE_LICENSE("GPL");
