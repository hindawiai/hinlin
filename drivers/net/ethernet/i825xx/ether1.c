<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/acorn/net/ether1.c
 *
 *  Copyright (C) 1996-2000 Russell King
 *
 *  Acorn ether1 driver (82586 chip) क्रम Acorn machines
 *
 * We basically keep two queues in the cards memory - one क्रम transmit
 * and one क्रम receive.  Each has a head and a tail.  The head is where
 * we/the chip adds packets to be transmitted/received, and the tail
 * is where the transmitter has got to/where the receiver will stop.
 * Both of these queues are circular, and since the chip is running
 * all the समय, we have to be careful when we modअगरy the poपूर्णांकers etc
 * so that the buffer memory contents is valid all the समय.
 *
 * Change log:
 * 1.00	RMK			Released
 * 1.01	RMK	19/03/1996	Transfers the last odd byte onto/off of the card now.
 * 1.02	RMK	25/05/1997	Added code to restart RU अगर it goes not पढ़ोy
 * 1.03	RMK	14/09/1997	Cleaned up the handling of a reset during the TX पूर्णांकerrupt.
 *				Should prevent lockup.
 * 1.04 RMK	17/09/1997	Added more info when initialisation of chip goes wrong.
 *				TDR now only reports failure when chip reports non-zero
 *				TDR समय-distance.
 * 1.05	RMK	31/12/1997	Removed calls to dev_tपूर्णांक क्रम 2.1
 * 1.06	RMK	10/02/2000	Updated क्रम 2.3.43
 * 1.07	RMK	13/05/2000	Updated क्रम 2.3.99-pre8
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
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/ecard.h>

#घोषणा __ETHER1_C
#समावेश "ether1.h"

अटल अचिन्हित पूर्णांक net_debug = NET_DEBUG;

#घोषणा BUFFER_SIZE	0x10000
#घोषणा TX_AREA_START	0x00100
#घोषणा TX_AREA_END	0x05000
#घोषणा RX_AREA_START	0x05000
#घोषणा RX_AREA_END	0x0fc00

अटल पूर्णांक ether1_खोलो(काष्ठा net_device *dev);
अटल netdev_tx_t ether1_sendpacket(काष्ठा sk_buff *skb,
				     काष्ठा net_device *dev);
अटल irqवापस_t ether1_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल पूर्णांक ether1_बंद(काष्ठा net_device *dev);
अटल व्योम ether1_seपंचांगulticastlist(काष्ठा net_device *dev);
अटल व्योम ether1_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);

/* ------------------------------------------------------------------------- */

अटल अक्षर version[] = "ether1 ethernet driver (c) 2000 Russell King v1.07\n";

#घोषणा BUS_16 16
#घोषणा BUS_8  8

/* ------------------------------------------------------------------------- */

#घोषणा DISABLEIRQS 1
#घोषणा NORMALIRQS  0

#घोषणा ether1_पढ़ोw(dev, addr, type, offset, svflgs) ether1_inw_p (dev, addr + (पूर्णांक)(&((type *)0)->offset), svflgs)
#घोषणा ether1_ग_लिखोw(dev, val, addr, type, offset, svflgs) ether1_outw_p (dev, val, addr + (पूर्णांक)(&((type *)0)->offset), svflgs)

अटल अंतरभूत अचिन्हित लघु
ether1_inw_p (काष्ठा net_device *dev, पूर्णांक addr, पूर्णांक svflgs)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु ret;

	अगर (svflgs)
		local_irq_save (flags);

	ग_लिखोb(addr >> 12, REG_PAGE);
	ret = पढ़ोw(ETHER1_RAM + ((addr & 4095) << 1));
	अगर (svflgs)
		local_irq_restore (flags);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम
ether1_outw_p (काष्ठा net_device *dev, अचिन्हित लघु val, पूर्णांक addr, पूर्णांक svflgs)
अणु
	अचिन्हित दीर्घ flags;

	अगर (svflgs)
		local_irq_save (flags);

	ग_लिखोb(addr >> 12, REG_PAGE);
	ग_लिखोw(val, ETHER1_RAM + ((addr & 4095) << 1));
	अगर (svflgs)
		local_irq_restore (flags);
पूर्ण

/*
 * Some अंतरभूत assembler to allow fast transfers on to/off of the card.
 * Since this driver depends on some features presented by the ARM
 * specअगरic architecture, and that you can't configure this driver
 * without specअगरying ARM mode, this is not a problem.
 *
 * This routine is essentially an optimised स_नकल from the card's
 * onboard RAM to kernel memory.
 */
अटल व्योम
ether1_ग_लिखोbuffer (काष्ठा net_device *dev, व्योम *data, अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक length)
अणु
	अचिन्हित पूर्णांक page, thislen, offset;
	व्योम __iomem *addr;

	offset = start & 4095;
	page = start >> 12;
	addr = ETHER1_RAM + (offset << 1);

	अगर (offset + length > 4096)
		thislen = 4096 - offset;
	अन्यथा
		thislen = length;

	करो अणु
		पूर्णांक used;

		ग_लिखोb(page, REG_PAGE);
		length -= thislen;

		__यंत्र__ __अस्थिर__(
	"subs	%3, %3, #2\न\
	bmi	2f\न\
1:	ldr	%0, [%1], #2\न\
	mov	%0, %0, lsl #16\न\
	orr	%0, %0, %0, lsr #16\न\
	str	%0, [%2], #4\न\
	subs	%3, %3, #2\न\
	bmi	2f\न\
	ldr	%0, [%1], #2\न\
	mov	%0, %0, lsl #16\न\
	orr	%0, %0, %0, lsr #16\न\
	str	%0, [%2], #4\न\
	subs	%3, %3, #2\न\
	bmi	2f\न\
	ldr	%0, [%1], #2\न\
	mov	%0, %0, lsl #16\न\
	orr	%0, %0, %0, lsr #16\न\
	str	%0, [%2], #4\न\
	subs	%3, %3, #2\न\
	bmi	2f\न\
	ldr	%0, [%1], #2\न\
	mov	%0, %0, lsl #16\न\
	orr	%0, %0, %0, lsr #16\न\
	str	%0, [%2], #4\न\
	subs	%3, %3, #2\न\
	bpl	1b\न\
2:	adds	%3, %3, #1\न\
	ldreqb	%0, [%1]\न\
	streqb	%0, [%2]"
		: "=&r" (used), "=&r" (data)
		: "r"  (addr), "r" (thislen), "1" (data));

		addr = ETHER1_RAM;

		thislen = length;
		अगर (thislen > 4096)
			thislen = 4096;
		page++;
	पूर्ण जबतक (thislen);
पूर्ण

अटल व्योम
ether1_पढ़ोbuffer (काष्ठा net_device *dev, व्योम *data, अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक length)
अणु
	अचिन्हित पूर्णांक page, thislen, offset;
	व्योम __iomem *addr;

	offset = start & 4095;
	page = start >> 12;
	addr = ETHER1_RAM + (offset << 1);

	अगर (offset + length > 4096)
		thislen = 4096 - offset;
	अन्यथा
		thislen = length;

	करो अणु
		पूर्णांक used;

		ग_लिखोb(page, REG_PAGE);
		length -= thislen;

		__यंत्र__ __अस्थिर__(
	"subs	%3, %3, #2\न\
	bmi	2f\न\
1:	ldr	%0, [%2], #4\न\
	strb	%0, [%1], #1\न\
	mov	%0, %0, lsr #8\न\
	strb	%0, [%1], #1\न\
	subs	%3, %3, #2\न\
	bmi	2f\न\
	ldr	%0, [%2], #4\न\
	strb	%0, [%1], #1\न\
	mov	%0, %0, lsr #8\न\
	strb	%0, [%1], #1\न\
	subs	%3, %3, #2\न\
	bmi	2f\न\
	ldr	%0, [%2], #4\न\
	strb	%0, [%1], #1\न\
	mov	%0, %0, lsr #8\न\
	strb	%0, [%1], #1\न\
	subs	%3, %3, #2\न\
	bmi	2f\न\
	ldr	%0, [%2], #4\न\
	strb	%0, [%1], #1\न\
	mov	%0, %0, lsr #8\न\
	strb	%0, [%1], #1\न\
	subs	%3, %3, #2\न\
	bpl	1b\न\
2:	adds	%3, %3, #1\न\
	ldreqb	%0, [%2]\न\
	streqb	%0, [%1]"
		: "=&r" (used), "=&r" (data)
		: "r"  (addr), "r" (thislen), "1" (data));

		addr = ETHER1_RAM;

		thislen = length;
		अगर (thislen > 4096)
			thislen = 4096;
		page++;
	पूर्ण जबतक (thislen);
पूर्ण

अटल पूर्णांक
ether1_ramtest(काष्ठा net_device *dev, अचिन्हित अक्षर byte)
अणु
	अचिन्हित अक्षर *buffer = kदो_स्मृति (BUFFER_SIZE, GFP_KERNEL);
	पूर्णांक i, ret = BUFFER_SIZE;
	पूर्णांक max_errors = 15;
	पूर्णांक bad = -1;
	पूर्णांक bad_start = 0;

	अगर (!buffer)
		वापस 1;

	स_रखो (buffer, byte, BUFFER_SIZE);
	ether1_ग_लिखोbuffer (dev, buffer, 0, BUFFER_SIZE);
	स_रखो (buffer, byte ^ 0xff, BUFFER_SIZE);
	ether1_पढ़ोbuffer (dev, buffer, 0, BUFFER_SIZE);

	क्रम (i = 0; i < BUFFER_SIZE; i++) अणु
		अगर (buffer[i] != byte) अणु
			अगर (max_errors >= 0 && bad != buffer[i]) अणु
				अगर (bad != -1)
					prपूर्णांकk ("\n");
				prपूर्णांकk (KERN_CRIT "%s: RAM failed with (%02X instead of %02X) at 0x%04X",
					dev->name, buffer[i], byte, i);
				ret = -ENODEV;
				max_errors --;
				bad = buffer[i];
				bad_start = i;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (bad != -1) अणु
			    	अगर (bad_start == i - 1)
					prपूर्णांकk ("\n");
				अन्यथा
					prपूर्णांकk (" - 0x%04X\n", i - 1);
				bad = -1;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (bad != -1)
		prपूर्णांकk (" - 0x%04X\n", BUFFER_SIZE);
	kमुक्त (buffer);

	वापस ret;
पूर्ण

अटल पूर्णांक
ether1_reset (काष्ठा net_device *dev)
अणु
	ग_लिखोb(CTRL_RST|CTRL_ACK, REG_CONTROL);
	वापस BUS_16;
पूर्ण

अटल पूर्णांक
ether1_init_2(काष्ठा net_device *dev)
अणु
	पूर्णांक i;
	dev->mem_start = 0;

	i = ether1_ramtest (dev, 0x5a);

	अगर (i > 0)
		i = ether1_ramtest (dev, 0x1e);

	अगर (i <= 0)
	    	वापस -ENODEV;

	dev->mem_end = i;
	वापस 0;
पूर्ण

/*
 * These are the काष्ठाures that are loaded पूर्णांकo the ether RAM card to
 * initialise the 82586
 */

/* at 0x0100 */
#घोषणा NOP_ADDR	(TX_AREA_START)
#घोषणा NOP_SIZE	(0x06)
अटल nop_t  init_nop  = अणु
	0,
	CMD_NOP,
	NOP_ADDR
पूर्ण;

/* at 0x003a */
#घोषणा TDR_ADDR	(0x003a)
#घोषणा TDR_SIZE	(0x08)
अटल tdr_t  init_tdr	= अणु
	0,
	CMD_TDR | CMD_INTR,
	NOP_ADDR,
	0
पूर्ण;

/* at 0x002e */
#घोषणा MC_ADDR		(0x002e)
#घोषणा MC_SIZE		(0x0c)
अटल mc_t   init_mc   = अणु
	0,
	CMD_SETMULTICAST,
	TDR_ADDR,
	0,
	अणु अणु 0, पूर्ण पूर्ण
पूर्ण;

/* at 0x0022 */
#घोषणा SA_ADDR		(0x0022)
#घोषणा SA_SIZE		(0x0c)
अटल sa_t   init_sa   = अणु
	0,
	CMD_SETADDRESS,
	MC_ADDR,
	अणु 0, पूर्ण
पूर्ण;

/* at 0x0010 */
#घोषणा CFG_ADDR	(0x0010)
#घोषणा CFG_SIZE	(0x12)
अटल cfg_t  init_cfg  = अणु
	0,
	CMD_CONFIG,
	SA_ADDR,
	8,
	8,
	CFG8_SRDY,
	CFG9_PREAMB8 | CFG9_ADDRLENBUF | CFG9_ADDRLEN(6),
	0,
	0x60,
	0,
	CFG13_RETRY(15) | CFG13_SLOTH(2),
	0,
पूर्ण;

/* at 0x0000 */
#घोषणा SCB_ADDR	(0x0000)
#घोषणा SCB_SIZE	(0x10)
अटल scb_t  init_scb  = अणु
	0,
	SCB_CMDACKRNR | SCB_CMDACKCNA | SCB_CMDACKFR | SCB_CMDACKCX,
	CFG_ADDR,
	RX_AREA_START,
	0,
	0,
	0,
	0
पूर्ण;

/* at 0xffee */
#घोषणा ISCP_ADDR	(0xffee)
#घोषणा ISCP_SIZE	(0x08)
अटल iscp_t init_iscp = अणु
	1,
	SCB_ADDR,
	0x0000,
	0x0000
पूर्ण;

/* at 0xfff6 */
#घोषणा SCP_ADDR	(0xfff6)
#घोषणा SCP_SIZE	(0x0a)
अटल scp_t  init_scp  = अणु
	SCP_SY_16BBUS,
	अणु 0, 0 पूर्ण,
	ISCP_ADDR,
	0
पूर्ण;

#घोषणा RFD_SIZE	(0x16)
अटल rfd_t  init_rfd	= अणु
	0,
	0,
	0,
	0,
	अणु 0, पूर्ण,
	अणु 0, पूर्ण,
	0
पूर्ण;

#घोषणा RBD_SIZE	(0x0a)
अटल rbd_t  init_rbd	= अणु
	0,
	0,
	0,
	0,
	ETH_FRAME_LEN + 8
पूर्ण;

#घोषणा TX_SIZE		(0x08)
#घोषणा TBD_SIZE	(0x08)

अटल पूर्णांक
ether1_init_क्रम_खोलो (काष्ठा net_device *dev)
अणु
	पूर्णांक i, status, addr, next, next2;
	पूर्णांक failures = 0;
	अचिन्हित दीर्घ समयout;

	ग_लिखोb(CTRL_RST|CTRL_ACK, REG_CONTROL);

	क्रम (i = 0; i < 6; i++)
		init_sa.sa_addr[i] = dev->dev_addr[i];

	/* load data काष्ठाures पूर्णांकo ether1 RAM */
	ether1_ग_लिखोbuffer (dev, &init_scp,  SCP_ADDR,  SCP_SIZE);
	ether1_ग_लिखोbuffer (dev, &init_iscp, ISCP_ADDR, ISCP_SIZE);
	ether1_ग_लिखोbuffer (dev, &init_scb,  SCB_ADDR,  SCB_SIZE);
	ether1_ग_लिखोbuffer (dev, &init_cfg,  CFG_ADDR,  CFG_SIZE);
	ether1_ग_लिखोbuffer (dev, &init_sa,   SA_ADDR,   SA_SIZE);
	ether1_ग_लिखोbuffer (dev, &init_mc,   MC_ADDR,   MC_SIZE);
	ether1_ग_लिखोbuffer (dev, &init_tdr,  TDR_ADDR,  TDR_SIZE);
	ether1_ग_लिखोbuffer (dev, &init_nop,  NOP_ADDR,  NOP_SIZE);

	अगर (ether1_पढ़ोw(dev, CFG_ADDR, cfg_t, cfg_command, NORMALIRQS) != CMD_CONFIG) अणु
		prपूर्णांकk (KERN_ERR "%s: detected either RAM fault or compiler bug\n",
			dev->name);
		वापस 1;
	पूर्ण

	/*
	 * setup circularly linked list of अणु rfd, rbd, buffer पूर्ण, with
	 * all rfds circularly linked, rbds circularly linked.
	 * First rfd is linked to scp, first rbd is linked to first
	 * rfd.  Last rbd has a suspend command.
	 */
	addr = RX_AREA_START;
	करो अणु
		next = addr + RFD_SIZE + RBD_SIZE + ETH_FRAME_LEN + 10;
		next2 = next + RFD_SIZE + RBD_SIZE + ETH_FRAME_LEN + 10;

		अगर (next2 >= RX_AREA_END) अणु
			next = RX_AREA_START;
			init_rfd.rfd_command = RFD_CMDEL | RFD_CMDSUSPEND;
			priv(dev)->rx_tail = addr;
		पूर्ण अन्यथा
			init_rfd.rfd_command = 0;
		अगर (addr == RX_AREA_START)
			init_rfd.rfd_rbकरोffset = addr + RFD_SIZE;
		अन्यथा
			init_rfd.rfd_rbकरोffset = 0;
		init_rfd.rfd_link = next;
		init_rbd.rbd_link = next + RFD_SIZE;
		init_rbd.rbd_bufl = addr + RFD_SIZE + RBD_SIZE;

		ether1_ग_लिखोbuffer (dev, &init_rfd, addr, RFD_SIZE);
		ether1_ग_लिखोbuffer (dev, &init_rbd, addr + RFD_SIZE, RBD_SIZE);
		addr = next;
	पूर्ण जबतक (next2 < RX_AREA_END);

	priv(dev)->tx_link = NOP_ADDR;
	priv(dev)->tx_head = NOP_ADDR + NOP_SIZE;
	priv(dev)->tx_tail = TDR_ADDR;
	priv(dev)->rx_head = RX_AREA_START;

	/* release reset & give 586 a prod */
	priv(dev)->resetting = 1;
	priv(dev)->initialising = 1;
	ग_लिखोb(CTRL_RST, REG_CONTROL);
	ग_लिखोb(0, REG_CONTROL);
	ग_लिखोb(CTRL_CA, REG_CONTROL);

	/* 586 should now unset iscp.busy */
	समयout = jअगरfies + HZ/2;
	जबतक (ether1_पढ़ोw(dev, ISCP_ADDR, iscp_t, iscp_busy, DISABLEIRQS) == 1) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			prपूर्णांकk (KERN_WARNING "%s: can't initialise 82586: iscp is busy\n", dev->name);
			वापस 1;
		पूर्ण
	पूर्ण

	/* check status of commands that we issued */
	समयout += HZ/10;
	जबतक (((status = ether1_पढ़ोw(dev, CFG_ADDR, cfg_t, cfg_status, DISABLEIRQS))
			& STAT_COMPLETE) == 0) अणु
		अगर (समय_after(jअगरfies, समयout))
			अवरोध;
	पूर्ण

	अगर ((status & (STAT_COMPLETE | STAT_OK)) != (STAT_COMPLETE | STAT_OK)) अणु
		prपूर्णांकk (KERN_WARNING "%s: can't initialise 82586: config status %04X\n", dev->name, status);
		prपूर्णांकk (KERN_DEBUG "%s: SCB=[STS=%04X CMD=%04X CBL=%04X RFA=%04X]\n", dev->name,
			ether1_पढ़ोw(dev, SCB_ADDR, scb_t, scb_status, NORMALIRQS),
			ether1_पढ़ोw(dev, SCB_ADDR, scb_t, scb_command, NORMALIRQS),
			ether1_पढ़ोw(dev, SCB_ADDR, scb_t, scb_cbl_offset, NORMALIRQS),
			ether1_पढ़ोw(dev, SCB_ADDR, scb_t, scb_rfa_offset, NORMALIRQS));
		failures += 1;
	पूर्ण

	समयout += HZ/10;
	जबतक (((status = ether1_पढ़ोw(dev, SA_ADDR, sa_t, sa_status, DISABLEIRQS))
			& STAT_COMPLETE) == 0) अणु
		अगर (समय_after(jअगरfies, समयout))
			अवरोध;
	पूर्ण

	अगर ((status & (STAT_COMPLETE | STAT_OK)) != (STAT_COMPLETE | STAT_OK)) अणु
		prपूर्णांकk (KERN_WARNING "%s: can't initialise 82586: set address status %04X\n", dev->name, status);
		prपूर्णांकk (KERN_DEBUG "%s: SCB=[STS=%04X CMD=%04X CBL=%04X RFA=%04X]\n", dev->name,
			ether1_पढ़ोw(dev, SCB_ADDR, scb_t, scb_status, NORMALIRQS),
			ether1_पढ़ोw(dev, SCB_ADDR, scb_t, scb_command, NORMALIRQS),
			ether1_पढ़ोw(dev, SCB_ADDR, scb_t, scb_cbl_offset, NORMALIRQS),
			ether1_पढ़ोw(dev, SCB_ADDR, scb_t, scb_rfa_offset, NORMALIRQS));
		failures += 1;
	पूर्ण

	समयout += HZ/10;
	जबतक (((status = ether1_पढ़ोw(dev, MC_ADDR, mc_t, mc_status, DISABLEIRQS))
			& STAT_COMPLETE) == 0) अणु
		अगर (समय_after(jअगरfies, समयout))
			अवरोध;
	पूर्ण

	अगर ((status & (STAT_COMPLETE | STAT_OK)) != (STAT_COMPLETE | STAT_OK)) अणु
		prपूर्णांकk (KERN_WARNING "%s: can't initialise 82586: set multicast status %04X\n", dev->name, status);
		prपूर्णांकk (KERN_DEBUG "%s: SCB=[STS=%04X CMD=%04X CBL=%04X RFA=%04X]\n", dev->name,
			ether1_पढ़ोw(dev, SCB_ADDR, scb_t, scb_status, NORMALIRQS),
			ether1_पढ़ोw(dev, SCB_ADDR, scb_t, scb_command, NORMALIRQS),
			ether1_पढ़ोw(dev, SCB_ADDR, scb_t, scb_cbl_offset, NORMALIRQS),
			ether1_पढ़ोw(dev, SCB_ADDR, scb_t, scb_rfa_offset, NORMALIRQS));
		failures += 1;
	पूर्ण

	समयout += HZ;
	जबतक (((status = ether1_पढ़ोw(dev, TDR_ADDR, tdr_t, tdr_status, DISABLEIRQS))
			& STAT_COMPLETE) == 0) अणु
		अगर (समय_after(jअगरfies, समयout))
			अवरोध;
	पूर्ण

	अगर ((status & (STAT_COMPLETE | STAT_OK)) != (STAT_COMPLETE | STAT_OK)) अणु
		prपूर्णांकk (KERN_WARNING "%s: can't tdr (ignored)\n", dev->name);
		prपूर्णांकk (KERN_DEBUG "%s: SCB=[STS=%04X CMD=%04X CBL=%04X RFA=%04X]\n", dev->name,
			ether1_पढ़ोw(dev, SCB_ADDR, scb_t, scb_status, NORMALIRQS),
			ether1_पढ़ोw(dev, SCB_ADDR, scb_t, scb_command, NORMALIRQS),
			ether1_पढ़ोw(dev, SCB_ADDR, scb_t, scb_cbl_offset, NORMALIRQS),
			ether1_पढ़ोw(dev, SCB_ADDR, scb_t, scb_rfa_offset, NORMALIRQS));
	पूर्ण अन्यथा अणु
		status = ether1_पढ़ोw(dev, TDR_ADDR, tdr_t, tdr_result, DISABLEIRQS);
		अगर (status & TDR_XCVRPROB)
			prपूर्णांकk (KERN_WARNING "%s: i/f failed tdr: transceiver problem\n", dev->name);
		अन्यथा अगर ((status & (TDR_SHORT|TDR_OPEN)) && (status & TDR_TIME)) अणु
#अगर_घोषित FANCY
			prपूर्णांकk (KERN_WARNING "%s: i/f failed tdr: cable %s %d.%d us away\n", dev->name,
				status & TDR_SHORT ? "short" : "open", (status & TDR_TIME) / 10,
				(status & TDR_TIME) % 10);
#अन्यथा
			prपूर्णांकk (KERN_WARNING "%s: i/f failed tdr: cable %s %d clks away\n", dev->name,
				status & TDR_SHORT ? "short" : "open", (status & TDR_TIME));
#पूर्ण_अगर
		पूर्ण
	पूर्ण

	अगर (failures)
		ether1_reset (dev);
	वापस failures ? 1 : 0;
पूर्ण

/* ------------------------------------------------------------------------- */

अटल पूर्णांक
ether1_txalloc (काष्ठा net_device *dev, पूर्णांक size)
अणु
	पूर्णांक start, tail;

	size = (size + 1) & ~1;
	tail = priv(dev)->tx_tail;

	अगर (priv(dev)->tx_head + size > TX_AREA_END) अणु
		अगर (tail > priv(dev)->tx_head)
			वापस -1;
		start = TX_AREA_START;
		अगर (start + size > tail)
			वापस -1;
		priv(dev)->tx_head = start + size;
	पूर्ण अन्यथा अणु
		अगर (priv(dev)->tx_head < tail && (priv(dev)->tx_head + size) > tail)
			वापस -1;
		start = priv(dev)->tx_head;
		priv(dev)->tx_head += size;
	पूर्ण

	वापस start;
पूर्ण

अटल पूर्णांक
ether1_खोलो (काष्ठा net_device *dev)
अणु
	अगर (request_irq(dev->irq, ether1_पूर्णांकerrupt, 0, "ether1", dev))
		वापस -EAGAIN;

	अगर (ether1_init_क्रम_खोलो (dev)) अणु
		मुक्त_irq (dev->irq, dev);
		वापस -EAGAIN;
	पूर्ण

	netअगर_start_queue(dev);

	वापस 0;
पूर्ण

अटल व्योम
ether1_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	prपूर्णांकk(KERN_WARNING "%s: transmit timeout, network cable problem?\n",
		dev->name);
	prपूर्णांकk(KERN_WARNING "%s: resetting device\n", dev->name);

	ether1_reset (dev);

	अगर (ether1_init_क्रम_खोलो (dev))
		prपूर्णांकk (KERN_ERR "%s: unable to restart interface\n", dev->name);

	dev->stats.tx_errors++;
	netअगर_wake_queue(dev);
पूर्ण

अटल netdev_tx_t
ether1_sendpacket (काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	पूर्णांक पंचांगp, tst, nopaddr, txaddr, tbdaddr, dataddr;
	अचिन्हित दीर्घ flags;
	tx_t tx;
	tbd_t tbd;
	nop_t nop;

	अगर (priv(dev)->restart) अणु
		prपूर्णांकk(KERN_WARNING "%s: resetting device\n", dev->name);

		ether1_reset(dev);

		अगर (ether1_init_क्रम_खोलो(dev))
			prपूर्णांकk(KERN_ERR "%s: unable to restart interface\n", dev->name);
		अन्यथा
			priv(dev)->restart = 0;
	पूर्ण

	अगर (skb->len < ETH_ZLEN) अणु
		अगर (skb_padto(skb, ETH_ZLEN))
			जाओ out;
	पूर्ण

	/*
	 * insert packet followed by a nop
	 */
	txaddr = ether1_txalloc (dev, TX_SIZE);
	tbdaddr = ether1_txalloc (dev, TBD_SIZE);
	dataddr = ether1_txalloc (dev, skb->len);
	nopaddr = ether1_txalloc (dev, NOP_SIZE);

	tx.tx_status = 0;
	tx.tx_command = CMD_TX | CMD_INTR;
	tx.tx_link = nopaddr;
	tx.tx_tbकरोffset = tbdaddr;
	tbd.tbd_opts = TBD_EOL | skb->len;
	tbd.tbd_link = I82586_शून्य;
	tbd.tbd_bufl = dataddr;
	tbd.tbd_bufh = 0;
	nop.nop_status = 0;
	nop.nop_command = CMD_NOP;
	nop.nop_link = nopaddr;

	local_irq_save(flags);
	ether1_ग_लिखोbuffer (dev, &tx, txaddr, TX_SIZE);
	ether1_ग_लिखोbuffer (dev, &tbd, tbdaddr, TBD_SIZE);
	ether1_ग_लिखोbuffer (dev, skb->data, dataddr, skb->len);
	ether1_ग_लिखोbuffer (dev, &nop, nopaddr, NOP_SIZE);
	पंचांगp = priv(dev)->tx_link;
	priv(dev)->tx_link = nopaddr;

	/* now reset the previous nop poपूर्णांकer */
	ether1_ग_लिखोw(dev, txaddr, पंचांगp, nop_t, nop_link, NORMALIRQS);

	local_irq_restore(flags);

	/* handle transmit */

	/* check to see अगर we have room क्रम a full sized ether frame */
	पंचांगp = priv(dev)->tx_head;
	tst = ether1_txalloc (dev, TX_SIZE + TBD_SIZE + NOP_SIZE + ETH_FRAME_LEN);
	priv(dev)->tx_head = पंचांगp;
	dev_kमुक्त_skb (skb);

	अगर (tst == -1)
		netअगर_stop_queue(dev);

 out:
	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम
ether1_xmit_करोne (काष्ठा net_device *dev)
अणु
	nop_t nop;
	पूर्णांक caddr, tst;

	caddr = priv(dev)->tx_tail;

again:
	ether1_पढ़ोbuffer (dev, &nop, caddr, NOP_SIZE);

	चयन (nop.nop_command & CMD_MASK) अणु
	हाल CMD_TDR:
		/* special हाल */
		अगर (ether1_पढ़ोw(dev, SCB_ADDR, scb_t, scb_cbl_offset, NORMALIRQS)
				!= (अचिन्हित लघु)I82586_शून्य) अणु
			ether1_ग_लिखोw(dev, SCB_CMDCUCSTART | SCB_CMDRXSTART, SCB_ADDR, scb_t,
				    scb_command, NORMALIRQS);
			ग_लिखोb(CTRL_CA, REG_CONTROL);
		पूर्ण
		priv(dev)->tx_tail = NOP_ADDR;
		वापस;

	हाल CMD_NOP:
		अगर (nop.nop_link == caddr) अणु
			अगर (priv(dev)->initialising == 0)
				prपूर्णांकk (KERN_WARNING "%s: strange command complete with no tx command!\n", dev->name);
			अन्यथा
			        priv(dev)->initialising = 0;
			वापस;
		पूर्ण
		अगर (caddr == nop.nop_link)
			वापस;
		caddr = nop.nop_link;
		जाओ again;

	हाल CMD_TX:
		अगर (nop.nop_status & STAT_COMPLETE)
			अवरोध;
		prपूर्णांकk (KERN_ERR "%s: strange command complete without completed command\n", dev->name);
		priv(dev)->restart = 1;
		वापस;

	शेष:
		prपूर्णांकk (KERN_WARNING "%s: strange command %d complete! (offset %04X)", dev->name,
			nop.nop_command & CMD_MASK, caddr);
		priv(dev)->restart = 1;
		वापस;
	पूर्ण

	जबतक (nop.nop_status & STAT_COMPLETE) अणु
		अगर (nop.nop_status & STAT_OK) अणु
			dev->stats.tx_packets++;
			dev->stats.collisions += (nop.nop_status & STAT_COLLISIONS);
		पूर्ण अन्यथा अणु
			dev->stats.tx_errors++;

			अगर (nop.nop_status & STAT_COLLAFTERTX)
				dev->stats.collisions++;
			अगर (nop.nop_status & STAT_NOCARRIER)
				dev->stats.tx_carrier_errors++;
			अगर (nop.nop_status & STAT_TXLOSTCTS)
				prपूर्णांकk (KERN_WARNING "%s: cts lost\n", dev->name);
			अगर (nop.nop_status & STAT_TXSLOWDMA)
				dev->stats.tx_fअगरo_errors++;
			अगर (nop.nop_status & STAT_COLLEXCESSIVE)
				dev->stats.collisions += 16;
		पूर्ण

		अगर (nop.nop_link == caddr) अणु
			prपूर्णांकk (KERN_ERR "%s: tx buffer chaining error: tx command points to itself\n", dev->name);
			अवरोध;
		पूर्ण

		caddr = nop.nop_link;
		ether1_पढ़ोbuffer (dev, &nop, caddr, NOP_SIZE);
		अगर ((nop.nop_command & CMD_MASK) != CMD_NOP) अणु
			prपूर्णांकk (KERN_ERR "%s: tx buffer chaining error: no nop after tx command\n", dev->name);
			अवरोध;
		पूर्ण

		अगर (caddr == nop.nop_link)
			अवरोध;

		caddr = nop.nop_link;
		ether1_पढ़ोbuffer (dev, &nop, caddr, NOP_SIZE);
		अगर ((nop.nop_command & CMD_MASK) != CMD_TX) अणु
			prपूर्णांकk (KERN_ERR "%s: tx buffer chaining error: no tx command after nop\n", dev->name);
			अवरोध;
		पूर्ण
	पूर्ण
	priv(dev)->tx_tail = caddr;

	caddr = priv(dev)->tx_head;
	tst = ether1_txalloc (dev, TX_SIZE + TBD_SIZE + NOP_SIZE + ETH_FRAME_LEN);
	priv(dev)->tx_head = caddr;
	अगर (tst != -1)
		netअगर_wake_queue(dev);
पूर्ण

अटल व्योम
ether1_recv_करोne (काष्ठा net_device *dev)
अणु
	पूर्णांक status;
	पूर्णांक nexttail, rbdaddr;
	rbd_t rbd;

	करो अणु
		status = ether1_पढ़ोw(dev, priv(dev)->rx_head, rfd_t, rfd_status, NORMALIRQS);
		अगर ((status & RFD_COMPLETE) == 0)
			अवरोध;

		rbdaddr = ether1_पढ़ोw(dev, priv(dev)->rx_head, rfd_t, rfd_rbकरोffset, NORMALIRQS);
		ether1_पढ़ोbuffer (dev, &rbd, rbdaddr, RBD_SIZE);

		अगर ((rbd.rbd_status & (RBD_खातापूर्ण | RBD_ACNTVALID)) == (RBD_खातापूर्ण | RBD_ACNTVALID)) अणु
			पूर्णांक length = rbd.rbd_status & RBD_ACNT;
			काष्ठा sk_buff *skb;

			length = (length + 1) & ~1;
			skb = netdev_alloc_skb(dev, length + 2);

			अगर (skb) अणु
				skb_reserve (skb, 2);

				ether1_पढ़ोbuffer (dev, skb_put (skb, length), rbd.rbd_bufl, length);

				skb->protocol = eth_type_trans (skb, dev);
				netअगर_rx (skb);
				dev->stats.rx_packets++;
			पूर्ण अन्यथा
				dev->stats.rx_dropped++;
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_WARNING "%s: %s\n", dev->name,
				(rbd.rbd_status & RBD_खातापूर्ण) ? "oversized packet" : "acnt not valid");
			dev->stats.rx_dropped++;
		पूर्ण

		nexttail = ether1_पढ़ोw(dev, priv(dev)->rx_tail, rfd_t, rfd_link, NORMALIRQS);
		/* nexttail should be rx_head */
		अगर (nexttail != priv(dev)->rx_head)
			prपूर्णांकk(KERN_ERR "%s: receiver buffer chaining error (%04X != %04X)\n",
				dev->name, nexttail, priv(dev)->rx_head);
		ether1_ग_लिखोw(dev, RFD_CMDEL | RFD_CMDSUSPEND, nexttail, rfd_t, rfd_command, NORMALIRQS);
		ether1_ग_लिखोw(dev, 0, priv(dev)->rx_tail, rfd_t, rfd_command, NORMALIRQS);
		ether1_ग_लिखोw(dev, 0, priv(dev)->rx_tail, rfd_t, rfd_status, NORMALIRQS);
		ether1_ग_लिखोw(dev, 0, priv(dev)->rx_tail, rfd_t, rfd_rbकरोffset, NORMALIRQS);
	
		priv(dev)->rx_tail = nexttail;
		priv(dev)->rx_head = ether1_पढ़ोw(dev, priv(dev)->rx_head, rfd_t, rfd_link, NORMALIRQS);
	पूर्ण जबतक (1);
पूर्ण

अटल irqवापस_t
ether1_पूर्णांकerrupt (पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *)dev_id;
	पूर्णांक status;

	status = ether1_पढ़ोw(dev, SCB_ADDR, scb_t, scb_status, NORMALIRQS);

	अगर (status) अणु
		ether1_ग_लिखोw(dev, status & (SCB_STRNR | SCB_STCNA | SCB_STFR | SCB_STCX),
			    SCB_ADDR, scb_t, scb_command, NORMALIRQS);
		ग_लिखोb(CTRL_CA | CTRL_ACK, REG_CONTROL);
		अगर (status & SCB_STCX) अणु
			ether1_xmit_करोne (dev);
		पूर्ण
		अगर (status & SCB_STCNA) अणु
			अगर (priv(dev)->resetting == 0)
				prपूर्णांकk (KERN_WARNING "%s: CU went not ready ???\n", dev->name);
			अन्यथा
				priv(dev)->resetting += 1;
			अगर (ether1_पढ़ोw(dev, SCB_ADDR, scb_t, scb_cbl_offset, NORMALIRQS)
					!= (अचिन्हित लघु)I82586_शून्य) अणु
				ether1_ग_लिखोw(dev, SCB_CMDCUCSTART, SCB_ADDR, scb_t, scb_command, NORMALIRQS);
				ग_लिखोb(CTRL_CA, REG_CONTROL);
			पूर्ण
			अगर (priv(dev)->resetting == 2)
				priv(dev)->resetting = 0;
		पूर्ण
		अगर (status & SCB_STFR) अणु
			ether1_recv_करोne (dev);
		पूर्ण
		अगर (status & SCB_STRNR) अणु
			अगर (ether1_पढ़ोw(dev, SCB_ADDR, scb_t, scb_status, NORMALIRQS) & SCB_STRXSUSP) अणु
				prपूर्णांकk (KERN_WARNING "%s: RU went not ready: RU suspended\n", dev->name);
				ether1_ग_लिखोw(dev, SCB_CMDRXRESUME, SCB_ADDR, scb_t, scb_command, NORMALIRQS);
				ग_लिखोb(CTRL_CA, REG_CONTROL);
				dev->stats.rx_dropped++;	/* we suspended due to lack of buffer space */
			पूर्ण अन्यथा
				prपूर्णांकk(KERN_WARNING "%s: RU went not ready: %04X\n", dev->name,
					ether1_पढ़ोw(dev, SCB_ADDR, scb_t, scb_status, NORMALIRQS));
			prपूर्णांकk (KERN_WARNING "RU ptr = %04X\n", ether1_पढ़ोw(dev, SCB_ADDR, scb_t, scb_rfa_offset,
						NORMALIRQS));
		पूर्ण
	पूर्ण अन्यथा
		ग_लिखोb(CTRL_ACK, REG_CONTROL);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक
ether1_बंद (काष्ठा net_device *dev)
अणु
	ether1_reset (dev);

	मुक्त_irq(dev->irq, dev);

	वापस 0;
पूर्ण

/*
 * Set or clear the multicast filter क्रम this adaptor.
 * num_addrs == -1	Promiscuous mode, receive all packets.
 * num_addrs == 0	Normal mode, clear multicast list.
 * num_addrs > 0	Multicast mode, receive normal and MC packets, and करो
 *			best-efक्रमt filtering.
 */
अटल व्योम
ether1_seपंचांगulticastlist (काष्ठा net_device *dev)
अणु
पूर्ण

/* ------------------------------------------------------------------------- */

अटल व्योम ether1_banner(व्योम)
अणु
	अटल अचिन्हित पूर्णांक version_prपूर्णांकed = 0;

	अगर (net_debug && version_prपूर्णांकed++ == 0)
		prपूर्णांकk(KERN_INFO "%s", version);
पूर्ण

अटल स्थिर काष्ठा net_device_ops ether1_netdev_ops = अणु
	.nकरो_खोलो		= ether1_खोलो,
	.nकरो_stop		= ether1_बंद,
	.nकरो_start_xmit		= ether1_sendpacket,
	.nकरो_set_rx_mode	= ether1_seपंचांगulticastlist,
	.nकरो_tx_समयout		= ether1_समयout,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
पूर्ण;

अटल पूर्णांक
ether1_probe(काष्ठा expansion_card *ec, स्थिर काष्ठा ecard_id *id)
अणु
	काष्ठा net_device *dev;
	पूर्णांक i, ret = 0;

	ether1_banner();

	ret = ecard_request_resources(ec);
	अगर (ret)
		जाओ out;

	dev = alloc_etherdev(माप(काष्ठा ether1_priv));
	अगर (!dev) अणु
		ret = -ENOMEM;
		जाओ release;
	पूर्ण

	SET_NETDEV_DEV(dev, &ec->dev);

	dev->irq = ec->irq;
	priv(dev)->base = ecardm_iomap(ec, ECARD_RES_IOCFAST, 0, 0);
	अगर (!priv(dev)->base) अणु
		ret = -ENOMEM;
		जाओ मुक्त;
	पूर्ण

	अगर ((priv(dev)->bus_type = ether1_reset(dev)) == 0) अणु
		ret = -ENODEV;
		जाओ मुक्त;
	पूर्ण

	क्रम (i = 0; i < 6; i++)
		dev->dev_addr[i] = पढ़ोb(IDPROM_ADDRESS + (i << 2));

	अगर (ether1_init_2(dev)) अणु
		ret = -ENODEV;
		जाओ मुक्त;
	पूर्ण

	dev->netdev_ops		= &ether1_netdev_ops;
	dev->watchकरोg_समयo	= 5 * HZ / 100;

	ret = रेजिस्टर_netdev(dev);
	अगर (ret)
		जाओ मुक्त;

	prपूर्णांकk(KERN_INFO "%s: ether1 in slot %d, %pM\n",
		dev->name, ec->slot_no, dev->dev_addr);
    
	ecard_set_drvdata(ec, dev);
	वापस 0;

 मुक्त:
	मुक्त_netdev(dev);
 release:
	ecard_release_resources(ec);
 out:
	वापस ret;
पूर्ण

अटल व्योम ether1_हटाओ(काष्ठा expansion_card *ec)
अणु
	काष्ठा net_device *dev = ecard_get_drvdata(ec);

	ecard_set_drvdata(ec, शून्य);	

	unरेजिस्टर_netdev(dev);
	मुक्त_netdev(dev);
	ecard_release_resources(ec);
पूर्ण

अटल स्थिर काष्ठा ecard_id ether1_ids[] = अणु
	अणु MANU_ACORN, PROD_ACORN_ETHER1 पूर्ण,
	अणु 0xffff, 0xffff पूर्ण
पूर्ण;

अटल काष्ठा ecard_driver ether1_driver = अणु
	.probe		= ether1_probe,
	.हटाओ		= ether1_हटाओ,
	.id_table	= ether1_ids,
	.drv = अणु
		.name	= "ether1",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ether1_init(व्योम)
अणु
	वापस ecard_रेजिस्टर_driver(&ether1_driver);
पूर्ण

अटल व्योम __निकास ether1_निकास(व्योम)
अणु
	ecard_हटाओ_driver(&ether1_driver);
पूर्ण

module_init(ether1_init);
module_निकास(ether1_निकास);

MODULE_LICENSE("GPL");
