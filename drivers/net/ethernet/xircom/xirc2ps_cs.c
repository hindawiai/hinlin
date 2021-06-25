<शैली गुरु>
/* [xirc2ps_cs.c wk 03.11.99] (1.40 1999/11/18 00:06:03)
 * Xircom CreditCard Ethernet Adapter IIps driver
 * Xircom Realport 10/100 (RE-100) driver 
 *
 * This driver supports various Xircom CreditCard Ethernet adapters
 * including the CE2, CE IIps, RE-10, CEM28, CEM33, CE33, CEM56,
 * CE3-100, CE3B, RE-100, REM10BT, and REM56G-100.
 *
 * 2000-09-24 <psheer@icon.co.za> The Xircom CE3B-100 may not
 * स्वतःdetect the media properly. In this हाल use the
 * अगर_port=1 (क्रम 10BaseT) or अगर_port=4 (क्रम 100BaseT) options
 * to क्रमce the media type.
 * 
 * Written originally by Werner Koch based on David Hinds' skeleton of the
 * PCMCIA driver.
 *
 * Copyright (c) 1997,1998 Werner Koch (dd9jn)
 *
 * This driver is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * It is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, see <http://www.gnu.org/licenses/>.
 *
 *
 * ALTERNATIVELY, this driver may be distributed under the terms of
 * the following license, in which हाल the provisions of this license
 * are required INSTEAD OF the GNU General Public License.  (This clause
 * is necessary due to a potential bad पूर्णांकeraction between the GPL and
 * the restrictions contained in a BSD-style copyright.)
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, and the entire permission notice in its entirety,
 *    including the disclaimer of warranties.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to enकरोrse or promote
 *    products derived from this software without specअगरic prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY सूचीECT,
 * INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/in.h>
#समावेश <linux/delay.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/ioport.h>
#समावेश <linux/bitops.h>
#समावेश <linux/mii.h>

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/cisreg.h>
#समावेश <pcmcia/ciscode.h>

#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>

#अगर_अघोषित MANFID_COMPAQ
  #घोषणा MANFID_COMPAQ 	   0x0138
  #घोषणा MANFID_COMPAQ2	   0x0183  /* is this correct? */
#पूर्ण_अगर

#समावेश <pcmcia/ds.h>

/* Time in jअगरfies beक्रमe concluding Tx hung */
#घोषणा TX_TIMEOUT	((400*HZ)/1000)

/****************
 * Some स्थिरants used to access the hardware
 */

/* Register offsets and value स्थिरans */
#घोषणा XIRCREG_CR  0	/* Command रेजिस्टर (wr) */
क्रमागत xirc_cr अणु
    TransmitPacket = 0x01,
    SoftReset = 0x02,
    EnableIntr = 0x04,
    ForceIntr  = 0x08,
    ClearTxFIFO = 0x10,
    ClearRxOvrun = 0x20,
    RestartTx	 = 0x40
पूर्ण;
#घोषणा XIRCREG_ESR 0	/* Ethernet status रेजिस्टर (rd) */
क्रमागत xirc_esr अणु
    FullPktRcvd = 0x01, /* full packet in receive buffer */
    PktRejected = 0x04, /* a packet has been rejected */
    TxPktPend = 0x08,	/* TX Packet Pending */
    IncorPolarity = 0x10,
    MediaSelect = 0x20	/* set अगर TP, clear अगर AUI */
पूर्ण;
#घोषणा XIRCREG_PR  1	/* Page Register select */
#घोषणा XIRCREG_EDP 4	/* Ethernet Data Port Register */
#घोषणा XIRCREG_ISR 6	/* Ethernet Interrupt Status Register */
क्रमागत xirc_isr अणु
    TxBufOvr = 0x01,	/* TX Buffer Overflow */
    PktTxed  = 0x02,	/* Packet Transmitted */
    MACIntr  = 0x04,	/* MAC Interrupt occurred */
    TxResGrant = 0x08,	/* Tx Reservation Granted */
    RxFullPkt = 0x20,	/* Rx Full Packet */
    RxPktRej  = 0x40,	/* Rx Packet Rejected */
    ForcedIntr= 0x80	/* Forced Interrupt */
पूर्ण;
#घोषणा XIRCREG1_IMR0 12 /* Ethernet Interrupt Mask Register (on page 1)*/
#घोषणा XIRCREG1_IMR1 13
#घोषणा XIRCREG0_TSO  8  /* Transmit Space Open Register (on page 0)*/
#घोषणा XIRCREG0_TRS  10 /* Transmit reservation Size Register (page 0)*/
#घोषणा XIRCREG0_DO   12 /* Data Offset Register (page 0) (wr) */
#घोषणा XIRCREG0_RSR  12 /* Receive Status Register (page 0) (rd) */
क्रमागत xirc_rsr अणु
    PhyPkt = 0x01,	/* set:physical packet, clear: multicast packet */
    BrdcstPkt = 0x02,	/* set अगर it is a broadcast packet */
    PktTooLong = 0x04,	/* set अगर packet length > 1518 */
    AlignErr = 0x10,	/* incorrect CRC and last octet not complete */
    CRCErr = 0x20,	/* incorrect CRC and last octet is complete */
    PktRxOk = 0x80	/* received ok */
पूर्ण;
#घोषणा XIRCREG0_PTR 13 /* packets transmitted रेजिस्टर (rd) */
#घोषणा XIRCREG0_RBC 14 /* receive byte count regsister (rd) */
#घोषणा XIRCREG1_ECR 14 /* ethernet configurationn रेजिस्टर */
क्रमागत xirc_ecr अणु
    FullDuplex = 0x04,	/* enable full duplex mode */
    LongTPMode = 0x08,	/* adjust क्रम दीर्घer lengths of TP cable */
    DisablePolCor = 0x10,/* disable स्वतः polarity correction */
    DisableLinkPulse = 0x20, /* disable link pulse generation */
    DisableAutoTx = 0x40, /* disable स्वतः-transmit */
पूर्ण;
#घोषणा XIRCREG2_RBS 8	/* receive buffer start रेजिस्टर */
#घोषणा XIRCREG2_LED 10 /* LED Configuration रेजिस्टर */
/* values क्रम the leds:    Bits 2-0 क्रम led 1
 *  0 disabled		   Bits 5-3 क्रम led 2
 *  1 collision
 *  2 noncollision
 *  3 link_detected
 *  4 incor_polarity
 *  5 jabber
 *  6 स्वतः_निश्चितion
 *  7 rx_tx_activity
 */
#घोषणा XIRCREG2_MSR 12 /* Mohawk specअगरic रेजिस्टर */

#घोषणा XIRCREG4_GPR0 8 /* General Purpose Register 0 */
#घोषणा XIRCREG4_GPR1 9 /* General Purpose Register 1 */
#घोषणा XIRCREG2_GPR2 13 /* General Purpose Register 2 (page2!)*/
#घोषणा XIRCREG4_BOV 10 /* Bonding Version Register */
#घोषणा XIRCREG4_LMA 12 /* Local Memory Address Register */
#घोषणा XIRCREG4_LMD 14 /* Local Memory Data Port */
/* MAC रेजिस्टर can only by accessed with 8 bit operations */
#घोषणा XIRCREG40_CMD0 8    /* Command Register (wr) */
क्रमागत xirc_cmd अणु 	    /* Commands */
    Transmit = 0x01,
    EnableRecv = 0x04,
    DisableRecv = 0x08,
    Abort = 0x10,
    Online = 0x20,
    IntrAck = 0x40,
    Offline = 0x80
पूर्ण;
#घोषणा XIRCREG5_RHSA0	10  /* Rx Host Start Address */
#घोषणा XIRCREG40_RXST0 9   /* Receive Status Register */
#घोषणा XIRCREG40_TXST0 11  /* Transmit Status Register 0 */
#घोषणा XIRCREG40_TXST1 12  /* Transmit Status Register 10 */
#घोषणा XIRCREG40_RMASK0 13  /* Receive Mask Register */
#घोषणा XIRCREG40_TMASK0 14  /* Transmit Mask Register 0 */
#घोषणा XIRCREG40_TMASK1 15  /* Transmit Mask Register 0 */
#घोषणा XIRCREG42_SWC0	8   /* Software Configuration 0 */
#घोषणा XIRCREG42_SWC1	9   /* Software Configuration 1 */
#घोषणा XIRCREG42_BOC	10  /* Back-Off Configuration */
#घोषणा XIRCREG44_TDR0	8   /* Time Doमुख्य Reflectometry 0 */
#घोषणा XIRCREG44_TDR1	9   /* Time Doमुख्य Reflectometry 1 */
#घोषणा XIRCREG44_RXBC_LO 10 /* Rx Byte Count 0 (rd) */
#घोषणा XIRCREG44_RXBC_HI 11 /* Rx Byte Count 1 (rd) */
#घोषणा XIRCREG45_REV	 15 /* Revision Register (rd) */
#घोषणा XIRCREG50_IA	8   /* Inभागidual Address (8-13) */

अटल स्थिर अक्षर *अगर_names[] = अणु "Auto", "10BaseT", "10Base2", "AUI", "100BaseT" पूर्ण;

/* card types */
#घोषणा XIR_UNKNOWN  0	/* unknown: not supported */
#घोषणा XIR_CE	     1	/* (prodid 1) dअगरferent hardware: not supported */
#घोषणा XIR_CE2      2	/* (prodid 2) */
#घोषणा XIR_CE3      3	/* (prodid 3) */
#घोषणा XIR_CEM      4	/* (prodid 1) dअगरferent hardware: not supported */
#घोषणा XIR_CEM2     5	/* (prodid 2) */
#घोषणा XIR_CEM3     6	/* (prodid 3) */
#घोषणा XIR_CEM33    7	/* (prodid 4) */
#घोषणा XIR_CEM56M   8	/* (prodid 5) */
#घोषणा XIR_CEM56    9	/* (prodid 6) */
#घोषणा XIR_CM28    10	/* (prodid 3) modem only: not supported here */
#घोषणा XIR_CM33    11	/* (prodid 4) modem only: not supported here */
#घोषणा XIR_CM56    12	/* (prodid 5) modem only: not supported here */
#घोषणा XIR_CG	    13	/* (prodid 1) GSM modem only: not supported */
#घोषणा XIR_CBE     14	/* (prodid 1) cardbus ethernet: not supported */
/*====================================================================*/

/* Module parameters */

MODULE_DESCRIPTION("Xircom PCMCIA ethernet driver");
MODULE_LICENSE("Dual MPL/GPL");

#घोषणा INT_MODULE_PARM(n, v) अटल पूर्णांक n = v; module_param(n, पूर्णांक, 0)

INT_MODULE_PARM(अगर_port,	0);
INT_MODULE_PARM(full_duplex,	0);
INT_MODULE_PARM(करो_sound, 	1);
INT_MODULE_PARM(lockup_hack,	0);  /* anti lockup hack */

/*====================================================================*/

/* We करो not process more than these number of bytes during one
 * पूर्णांकerrupt. (Of course we receive complete packets, so this is not
 * an exact value).
 * Something between 2000..22000; first value gives best पूर्णांकerrupt latency,
 * the second enables the usage of the complete on-chip buffer. We use the
 * high value as the initial value.
 */
अटल अचिन्हित maxrx_bytes = 22000;

/* MII management prototypes */
अटल व्योम mii_idle(अचिन्हित पूर्णांक ioaddr);
अटल व्योम mii_putbit(अचिन्हित पूर्णांक ioaddr, अचिन्हित data);
अटल पूर्णांक  mii_getbit(अचिन्हित पूर्णांक ioaddr);
अटल व्योम mii_wbits(अचिन्हित पूर्णांक ioaddr, अचिन्हित data, पूर्णांक len);
अटल अचिन्हित mii_rd(अचिन्हित पूर्णांक ioaddr, u_अक्षर phyaddr, u_अक्षर phyreg);
अटल व्योम mii_wr(अचिन्हित पूर्णांक ioaddr, u_अक्षर phyaddr, u_अक्षर phyreg,
		   अचिन्हित data, पूर्णांक len);

अटल पूर्णांक has_ce2_string(काष्ठा pcmcia_device * link);
अटल पूर्णांक xirc2ps_config(काष्ठा pcmcia_device * link);
अटल व्योम xirc2ps_release(काष्ठा pcmcia_device * link);
अटल व्योम xirc2ps_detach(काष्ठा pcmcia_device *p_dev);

अटल irqवापस_t xirc2ps_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);

काष्ठा local_info अणु
	काष्ठा net_device	*dev;
	काष्ठा pcmcia_device	*p_dev;

    पूर्णांक card_type;
    पूर्णांक probe_port;
    पूर्णांक silicon; /* silicon revision. 0=old CE2, 1=Scipper, 4=Mohawk */
    पूर्णांक mohawk;  /* a CE3 type card */
    पूर्णांक dingo;	 /* a CEM56 type card */
    पूर्णांक new_mii; /* has full 10baseT/100baseT MII */
    पूर्णांक modem;	 /* is a multi function card (i.e with a modem) */
    व्योम __iomem *dingo_ccr; /* only used क्रम CEM56 cards */
    अचिन्हित last_ptr_value; /* last packets transmitted value */
    स्थिर अक्षर *manf_str;
    काष्ठा work_काष्ठा tx_समयout_task;
पूर्ण;

/****************
 * Some more prototypes
 */
अटल netdev_tx_t करो_start_xmit(काष्ठा sk_buff *skb,
				       काष्ठा net_device *dev);
अटल व्योम xirc_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल व्योम xirc2ps_tx_समयout_task(काष्ठा work_काष्ठा *work);
अटल व्योम set_addresses(काष्ठा net_device *dev);
अटल व्योम set_multicast_list(काष्ठा net_device *dev);
अटल पूर्णांक set_card_type(काष्ठा pcmcia_device *link);
अटल पूर्णांक करो_config(काष्ठा net_device *dev, काष्ठा अगरmap *map);
अटल पूर्णांक करो_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक करो_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);
अटल स्थिर काष्ठा ethtool_ops netdev_ethtool_ops;
अटल व्योम hardreset(काष्ठा net_device *dev);
अटल व्योम करो_reset(काष्ठा net_device *dev, पूर्णांक full);
अटल पूर्णांक init_mii(काष्ठा net_device *dev);
अटल व्योम करो_घातerकरोwn(काष्ठा net_device *dev);
अटल पूर्णांक करो_stop(काष्ठा net_device *dev);

/*=============== Helper functions =========================*/
#घोषणा SelectPage(pgnr)   outb((pgnr), ioaddr + XIRCREG_PR)
#घोषणा GetByte(reg)	   ((अचिन्हित)inb(ioaddr + (reg)))
#घोषणा GetWord(reg)	   ((अचिन्हित)inw(ioaddr + (reg)))
#घोषणा PutByte(reg,value) outb((value), ioaddr+(reg))
#घोषणा PutWord(reg,value) outw((value), ioaddr+(reg))

/*====== Functions used क्रम debugging =================================*/
#अगर 0 /* पढ़ोing regs may change प्रणाली status */
अटल व्योम
Prपूर्णांकRegisters(काष्ठा net_device *dev)
अणु
    अचिन्हित पूर्णांक ioaddr = dev->base_addr;

    अगर (pc_debug > 1) अणु
	पूर्णांक i, page;

	prपूर्णांकk(KERN_DEBUG pr_fmt("Register  common: "));
	क्रम (i = 0; i < 8; i++)
	    pr_cont(" %2.2x", GetByte(i));
	pr_cont("\n");
	क्रम (page = 0; page <= 8; page++) अणु
	    prपूर्णांकk(KERN_DEBUG pr_fmt("Register page %2x: "), page);
	    SelectPage(page);
	    क्रम (i = 8; i < 16; i++)
		pr_cont(" %2.2x", GetByte(i));
	    pr_cont("\n");
	पूर्ण
	क्रम (page=0x40 ; page <= 0x5f; page++) अणु
		अगर (page == 0x43 || (page >= 0x46 && page <= 0x4f) ||
		    (page >= 0x51 && page <=0x5e))
			जारी;
	    prपूर्णांकk(KERN_DEBUG pr_fmt("Register page %2x: "), page);
	    SelectPage(page);
	    क्रम (i = 8; i < 16; i++)
		pr_cont(" %2.2x", GetByte(i));
	    pr_cont("\n");
	पूर्ण
    पूर्ण
पूर्ण
#पूर्ण_अगर /* 0 */

/*============== MII Management functions ===============*/

/****************
 * Turn around क्रम पढ़ो
 */
अटल व्योम
mii_idle(अचिन्हित पूर्णांक ioaddr)
अणु
    PutByte(XIRCREG2_GPR2, 0x04|0); /* drive MDCK low */
    udelay(1);
    PutByte(XIRCREG2_GPR2, 0x04|1); /* and drive MDCK high */
    udelay(1);
पूर्ण

/****************
 * Write a bit to MDI/O
 */
अटल व्योम
mii_putbit(अचिन्हित पूर्णांक ioaddr, अचिन्हित data)
अणु
  #अगर 1
    अगर (data) अणु
	PutByte(XIRCREG2_GPR2, 0x0c|2|0); /* set MDIO */
	udelay(1);
	PutByte(XIRCREG2_GPR2, 0x0c|2|1); /* and drive MDCK high */
	udelay(1);
    पूर्ण अन्यथा अणु
	PutByte(XIRCREG2_GPR2, 0x0c|0|0); /* clear MDIO */
	udelay(1);
	PutByte(XIRCREG2_GPR2, 0x0c|0|1); /* and drive MDCK high */
	udelay(1);
    पूर्ण
  #अन्यथा
    अगर (data) अणु
	PutWord(XIRCREG2_GPR2-1, 0x0e0e);
	udelay(1);
	PutWord(XIRCREG2_GPR2-1, 0x0f0f);
	udelay(1);
    पूर्ण अन्यथा अणु
	PutWord(XIRCREG2_GPR2-1, 0x0c0c);
	udelay(1);
	PutWord(XIRCREG2_GPR2-1, 0x0d0d);
	udelay(1);
    पूर्ण
  #पूर्ण_अगर
पूर्ण

/****************
 * Get a bit from MDI/O
 */
अटल पूर्णांक
mii_getbit(अचिन्हित पूर्णांक ioaddr)
अणु
    अचिन्हित d;

    PutByte(XIRCREG2_GPR2, 4|0); /* drive MDCK low */
    udelay(1);
    d = GetByte(XIRCREG2_GPR2); /* पढ़ो MDIO */
    PutByte(XIRCREG2_GPR2, 4|1); /* drive MDCK high again */
    udelay(1);
    वापस d & 0x20; /* पढ़ो MDIO */
पूर्ण

अटल व्योम
mii_wbits(अचिन्हित पूर्णांक ioaddr, अचिन्हित data, पूर्णांक len)
अणु
    अचिन्हित m = 1 << (len-1);
    क्रम (; m; m >>= 1)
	mii_putbit(ioaddr, data & m);
पूर्ण

अटल अचिन्हित
mii_rd(अचिन्हित पूर्णांक ioaddr,	u_अक्षर phyaddr, u_अक्षर phyreg)
अणु
    पूर्णांक i;
    अचिन्हित data=0, m;

    SelectPage(2);
    क्रम (i=0; i < 32; i++)		/* 32 bit preamble */
	mii_putbit(ioaddr, 1);
    mii_wbits(ioaddr, 0x06, 4); 	/* Start and opcode क्रम पढ़ो */
    mii_wbits(ioaddr, phyaddr, 5);	/* PHY address to be accessed */
    mii_wbits(ioaddr, phyreg, 5);	/* PHY रेजिस्टर to पढ़ो */
    mii_idle(ioaddr);			/* turn around */
    mii_getbit(ioaddr);

    क्रम (m = 1<<15; m; m >>= 1)
	अगर (mii_getbit(ioaddr))
	    data |= m;
    mii_idle(ioaddr);
    वापस data;
पूर्ण

अटल व्योम
mii_wr(अचिन्हित पूर्णांक ioaddr, u_अक्षर phyaddr, u_अक्षर phyreg, अचिन्हित data,
       पूर्णांक len)
अणु
    पूर्णांक i;

    SelectPage(2);
    क्रम (i=0; i < 32; i++)		/* 32 bit preamble */
	mii_putbit(ioaddr, 1);
    mii_wbits(ioaddr, 0x05, 4); 	/* Start and opcode क्रम ग_लिखो */
    mii_wbits(ioaddr, phyaddr, 5);	/* PHY address to be accessed */
    mii_wbits(ioaddr, phyreg, 5);	/* PHY Register to ग_लिखो */
    mii_putbit(ioaddr, 1);		/* turn around */
    mii_putbit(ioaddr, 0);
    mii_wbits(ioaddr, data, len);	/* And ग_लिखो the data */
    mii_idle(ioaddr);
पूर्ण

/*============= Main bulk of functions	=========================*/

अटल स्थिर काष्ठा net_device_ops netdev_ops = अणु
	.nकरो_खोलो		= करो_खोलो,
	.nकरो_stop		= करो_stop,
	.nकरो_start_xmit		= करो_start_xmit,
	.nकरो_tx_समयout 	= xirc_tx_समयout,
	.nकरो_set_config		= करो_config,
	.nकरो_करो_ioctl		= करो_ioctl,
	.nकरो_set_rx_mode	= set_multicast_list,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक
xirc2ps_probe(काष्ठा pcmcia_device *link)
अणु
    काष्ठा net_device *dev;
    काष्ठा local_info *local;

    dev_dbg(&link->dev, "attach()\n");

    /* Allocate the device काष्ठाure */
    dev = alloc_etherdev(माप(काष्ठा local_info));
    अगर (!dev)
	    वापस -ENOMEM;
    local = netdev_priv(dev);
    local->dev = dev;
    local->p_dev = link;
    link->priv = dev;

    /* General socket configuration */
    link->config_index = 1;

    /* Fill in card specअगरic entries */
    dev->netdev_ops = &netdev_ops;
    dev->ethtool_ops = &netdev_ethtool_ops;
    dev->watchकरोg_समयo = TX_TIMEOUT;
    INIT_WORK(&local->tx_समयout_task, xirc2ps_tx_समयout_task);

    वापस xirc2ps_config(link);
पूर्ण /* xirc2ps_attach */

अटल व्योम
xirc2ps_detach(काष्ठा pcmcia_device *link)
अणु
    काष्ठा net_device *dev = link->priv;

    dev_dbg(&link->dev, "detach\n");

    unरेजिस्टर_netdev(dev);

    xirc2ps_release(link);

    मुक्त_netdev(dev);
पूर्ण /* xirc2ps_detach */

/****************
 * Detect the type of the card. s is the buffer with the data of tuple 0x20
 * Returns: 0 := not supported
 *		       mediaid=11 and prodid=47
 * Media-Id bits:
 *  Ethernet	    0x01
 *  Tokenring	    0x02
 *  Arcnet	    0x04
 *  Wireless	    0x08
 *  Modem	    0x10
 *  GSM only	    0x20
 * Prod-Id bits:
 *  Pocket	    0x10
 *  External	    0x20
 *  Creditcard	    0x40
 *  Cardbus	    0x80
 *
 */
अटल पूर्णांक
set_card_type(काष्ठा pcmcia_device *link)
अणु
    काष्ठा net_device *dev = link->priv;
    काष्ठा local_info *local = netdev_priv(dev);
    u8 *buf;
    अचिन्हित पूर्णांक cisrev, mediaid, prodid;
    माप_प्रकार len;

    len = pcmcia_get_tuple(link, CISTPL_MANFID, &buf);
    अगर (len < 5) अणु
	    dev_err(&link->dev, "invalid CIS -- sorry\n");
	    वापस 0;
    पूर्ण

    cisrev = buf[2];
    mediaid = buf[3];
    prodid = buf[4];

    dev_dbg(&link->dev, "cisrev=%02x mediaid=%02x prodid=%02x\n",
	  cisrev, mediaid, prodid);

    local->mohawk = 0;
    local->dingo = 0;
    local->modem = 0;
    local->card_type = XIR_UNKNOWN;
    अगर (!(prodid & 0x40)) अणु
	pr_notice("Oops: Not a creditcard\n");
	वापस 0;
    पूर्ण
    अगर (!(mediaid & 0x01)) अणु
	pr_notice("Not an Ethernet card\n");
	वापस 0;
    पूर्ण
    अगर (mediaid & 0x10) अणु
	local->modem = 1;
	चयन(prodid & 15) अणु
	  हाल 1: local->card_type = XIR_CEM   ; अवरोध;
	  हाल 2: local->card_type = XIR_CEM2  ; अवरोध;
	  हाल 3: local->card_type = XIR_CEM3  ; अवरोध;
	  हाल 4: local->card_type = XIR_CEM33 ; अवरोध;
	  हाल 5: local->card_type = XIR_CEM56M;
		  local->mohawk = 1;
		  अवरोध;
	  हाल 6:
	  हाल 7: /* 7 is the RealPort 10/56 */
		  local->card_type = XIR_CEM56 ;
		  local->mohawk = 1;
		  local->dingo = 1;
		  अवरोध;
	पूर्ण
    पूर्ण अन्यथा अणु
	चयन(prodid & 15) अणु
	  हाल 1: local->card_type = has_ce2_string(link)? XIR_CE2 : XIR_CE ;
		  अवरोध;
	  हाल 2: local->card_type = XIR_CE2; अवरोध;
	  हाल 3: local->card_type = XIR_CE3;
		  local->mohawk = 1;
		  अवरोध;
	पूर्ण
    पूर्ण
    अगर (local->card_type == XIR_CE || local->card_type == XIR_CEM) अणु
	pr_notice("Sorry, this is an old CE card\n");
	वापस 0;
    पूर्ण
    अगर (local->card_type == XIR_UNKNOWN)
	pr_notice("unknown card (mediaid=%02x prodid=%02x)\n", mediaid, prodid);

    वापस 1;
पूर्ण

/****************
 * There are some CE2 cards out which claim to be a CE card.
 * This function looks क्रम a "CE2" in the 3rd version field.
 * Returns: true अगर this is a CE2
 */
अटल पूर्णांक
has_ce2_string(काष्ठा pcmcia_device * p_dev)
अणु
	अगर (p_dev->prod_id[2] && म_माला(p_dev->prod_id[2], "CE2"))
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक
xirc2ps_config_modem(काष्ठा pcmcia_device *p_dev, व्योम *priv_data)
अणु
	अचिन्हित पूर्णांक ioaddr;

	अगर ((p_dev->resource[0]->start & 0xf) == 8)
		वापस -ENODEV;

	p_dev->resource[0]->end = 16;
	p_dev->resource[1]->end = 8;
	p_dev->resource[0]->flags &= ~IO_DATA_PATH_WIDTH;
	p_dev->resource[0]->flags |= IO_DATA_PATH_WIDTH_16;
	p_dev->resource[1]->flags &= ~IO_DATA_PATH_WIDTH;
	p_dev->resource[1]->flags |= IO_DATA_PATH_WIDTH_8;
	p_dev->io_lines = 10;

	p_dev->resource[1]->start = p_dev->resource[0]->start;
	क्रम (ioaddr = 0x300; ioaddr < 0x400; ioaddr += 0x10) अणु
		p_dev->resource[0]->start = ioaddr;
		अगर (!pcmcia_request_io(p_dev))
			वापस 0;
	पूर्ण
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक
xirc2ps_config_check(काष्ठा pcmcia_device *p_dev, व्योम *priv_data)
अणु
	पूर्णांक *pass = priv_data;
	resource_माप_प्रकार पंचांगp = p_dev->resource[1]->start;

	पंचांगp += (*pass ? (p_dev->config_index & 0x20 ? -24 : 8)
		: (p_dev->config_index & 0x20 ?   8 : -24));

	अगर ((p_dev->resource[0]->start & 0xf) == 8)
		वापस -ENODEV;

	p_dev->resource[0]->end = 18;
	p_dev->resource[1]->end = 8;
	p_dev->resource[0]->flags &= ~IO_DATA_PATH_WIDTH;
	p_dev->resource[0]->flags |= IO_DATA_PATH_WIDTH_16;
	p_dev->resource[1]->flags &= ~IO_DATA_PATH_WIDTH;
	p_dev->resource[1]->flags |= IO_DATA_PATH_WIDTH_8;
	p_dev->io_lines = 10;

	p_dev->resource[1]->start = p_dev->resource[0]->start;
	p_dev->resource[0]->start = पंचांगp;
	वापस pcmcia_request_io(p_dev);
पूर्ण


अटल पूर्णांक pcmcia_get_mac_ce(काष्ठा pcmcia_device *p_dev,
			     tuple_t *tuple,
			     व्योम *priv)
अणु
	काष्ठा net_device *dev = priv;
	पूर्णांक i;

	अगर (tuple->TupleDataLen != 13)
		वापस -EINVAL;
	अगर ((tuple->TupleData[0] != 2) || (tuple->TupleData[1] != 1) ||
		(tuple->TupleData[2] != 6))
		वापस -EINVAL;
	/* another try	(James Lehmer's CE2 version 4.1)*/
	क्रम (i = 2; i < 6; i++)
		dev->dev_addr[i] = tuple->TupleData[i+2];
	वापस 0;
पूर्ण;


अटल पूर्णांक
xirc2ps_config(काष्ठा pcmcia_device * link)
अणु
    काष्ठा net_device *dev = link->priv;
    काष्ठा local_info *local = netdev_priv(dev);
    अचिन्हित पूर्णांक ioaddr;
    पूर्णांक err;
    u8 *buf;
    माप_प्रकार len;

    local->dingo_ccr = शून्य;

    dev_dbg(&link->dev, "config\n");

    /* Is this a valid	card */
    अगर (link->has_manf_id == 0) अणु
	pr_notice("manfid not found in CIS\n");
	जाओ failure;
    पूर्ण

    चयन (link->manf_id) अणु
      हाल MANFID_XIRCOM:
	local->manf_str = "Xircom";
	अवरोध;
      हाल MANFID_ACCTON:
	local->manf_str = "Accton";
	अवरोध;
      हाल MANFID_COMPAQ:
      हाल MANFID_COMPAQ2:
	local->manf_str = "Compaq";
	अवरोध;
      हाल MANFID_INTEL:
	local->manf_str = "Intel";
	अवरोध;
      हाल MANFID_TOSHIBA:
	local->manf_str = "Toshiba";
	अवरोध;
      शेष:
	pr_notice("Unknown Card Manufacturer ID: 0x%04x\n",
		  (अचिन्हित)link->manf_id);
	जाओ failure;
    पूर्ण
    dev_dbg(&link->dev, "found %s card\n", local->manf_str);

    अगर (!set_card_type(link)) अणु
	pr_notice("this card is not supported\n");
	जाओ failure;
    पूर्ण

    /* get the ethernet address from the CIS */
    err = pcmcia_get_mac_from_cis(link, dev);

    /* not found: try to get the node-id from tuple 0x89 */
    अगर (err) अणु
	    len = pcmcia_get_tuple(link, 0x89, &buf);
	    /* data layout looks like tuple 0x22 */
	    अगर (buf && len == 8) अणु
		    अगर (*buf == CISTPL_FUNCE_LAN_NODE_ID) अणु
			    पूर्णांक i;
			    क्रम (i = 2; i < 6; i++)
				    dev->dev_addr[i] = buf[i+2];
		    पूर्ण अन्यथा
			    err = -1;
	    पूर्ण
	    kमुक्त(buf);
    पूर्ण

    अगर (err)
	err = pcmcia_loop_tuple(link, CISTPL_FUNCE, pcmcia_get_mac_ce, dev);

    अगर (err) अणु
	pr_notice("node-id not found in CIS\n");
	जाओ failure;
    पूर्ण

    अगर (local->modem) अणु
	पूर्णांक pass;
	link->config_flags |= CONF_AUTO_SET_IO;

	अगर (local->dingo) अणु
	    /* Take the Modem IO port from the CIS and scan क्रम a मुक्त
	     * Ethernet port */
	    अगर (!pcmcia_loop_config(link, xirc2ps_config_modem, शून्य))
		    जाओ port_found;
	पूर्ण अन्यथा अणु
	    /* We करो 2 passes here: The first one uses the regular mapping and
	     * the second tries again, thereby considering that the 32 ports are
	     * mirrored every 32 bytes. Actually we use a mirrored port क्रम
	     * the Mako अगर (on the first pass) the COR bit 5 is set.
	     */
	    क्रम (pass=0; pass < 2; pass++)
		    अगर (!pcmcia_loop_config(link, xirc2ps_config_check,
						    &pass))
			    जाओ port_found;
	    /* अगर special option:
	     * try to configure as Ethernet only.
	     * .... */
	पूर्ण
	pr_notice("no ports available\n");
    पूर्ण अन्यथा अणु
	link->io_lines = 10;
	link->resource[0]->end = 16;
	link->resource[0]->flags |= IO_DATA_PATH_WIDTH_16;
	क्रम (ioaddr = 0x300; ioaddr < 0x400; ioaddr += 0x10) अणु
	    link->resource[0]->start = ioaddr;
	    अगर (!(err = pcmcia_request_io(link)))
		जाओ port_found;
	पूर्ण
	link->resource[0]->start = 0; /* let CS decide */
	अगर ((err = pcmcia_request_io(link)))
	    जाओ config_error;
    पूर्ण
  port_found:

    /****************
     * Now allocate an पूर्णांकerrupt line.	Note that this करोes not
     * actually assign a handler to the पूर्णांकerrupt.
     */
    अगर ((err=pcmcia_request_irq(link, xirc2ps_पूर्णांकerrupt)))
	जाओ config_error;

    link->config_flags |= CONF_ENABLE_IRQ;
    अगर (करो_sound)
	    link->config_flags |= CONF_ENABLE_SPKR;

    अगर ((err = pcmcia_enable_device(link)))
	जाओ config_error;

    अगर (local->dingo) अणु
	/* Reset the modem's BAR to the correct value
	 * This is necessary because in the RequestConfiguration call,
	 * the base address of the ethernet port (BasePort1) is written
	 * to the BAR रेजिस्टरs of the modem.
	 */
	err = pcmcia_ग_लिखो_config_byte(link, CISREG_IOBASE_0, (u8)
				link->resource[1]->start & 0xff);
	अगर (err)
	    जाओ config_error;

	err = pcmcia_ग_लिखो_config_byte(link, CISREG_IOBASE_1,
				(link->resource[1]->start >> 8) & 0xff);
	अगर (err)
	    जाओ config_error;

	/* There is no config entry क्रम the Ethernet part which
	 * is at 0x0800. So we allocate a winकरोw पूर्णांकo the attribute
	 * memory and ग_लिखो direct to the CIS रेजिस्टरs
	 */
	link->resource[2]->flags = WIN_DATA_WIDTH_8 | WIN_MEMORY_TYPE_AM |
					WIN_ENABLE;
	link->resource[2]->start = link->resource[2]->end = 0;
	अगर ((err = pcmcia_request_winकरोw(link, link->resource[2], 0)))
	    जाओ config_error;

	local->dingo_ccr = ioremap(link->resource[2]->start, 0x1000) + 0x0800;
	अगर ((err = pcmcia_map_mem_page(link, link->resource[2], 0)))
	    जाओ config_error;

	/* Setup the CCRs; there are no infos in the CIS about the Ethernet
	 * part.
	 */
	ग_लिखोb(0x47, local->dingo_ccr + CISREG_COR);
	ioaddr = link->resource[0]->start;
	ग_लिखोb(ioaddr & 0xff	  , local->dingo_ccr + CISREG_IOBASE_0);
	ग_लिखोb((ioaddr >> 8)&0xff , local->dingo_ccr + CISREG_IOBASE_1);

      #अगर 0
	अणु
	    u_अक्षर पंचांगp;
	    pr_info("ECOR:");
	    क्रम (i=0; i < 7; i++) अणु
		पंचांगp = पढ़ोb(local->dingo_ccr + i*2);
		pr_cont(" %02x", पंचांगp);
	    पूर्ण
	    pr_cont("\n");
	    pr_info("DCOR:");
	    क्रम (i=0; i < 4; i++) अणु
		पंचांगp = पढ़ोb(local->dingo_ccr + 0x20 + i*2);
		pr_cont(" %02x", पंचांगp);
	    पूर्ण
	    pr_cont("\n");
	    pr_info("SCOR:");
	    क्रम (i=0; i < 10; i++) अणु
		पंचांगp = पढ़ोb(local->dingo_ccr + 0x40 + i*2);
		pr_cont(" %02x", पंचांगp);
	    पूर्ण
	    pr_cont("\n");
	पूर्ण
      #पूर्ण_अगर

	ग_लिखोb(0x01, local->dingo_ccr + 0x20);
	ग_लिखोb(0x0c, local->dingo_ccr + 0x22);
	ग_लिखोb(0x00, local->dingo_ccr + 0x24);
	ग_लिखोb(0x00, local->dingo_ccr + 0x26);
	ग_लिखोb(0x00, local->dingo_ccr + 0x28);
    पूर्ण

    /* The अगर_port symbol can be set when the module is loaded */
    local->probe_port=0;
    अगर (!अगर_port) अणु
	local->probe_port = dev->अगर_port = 1;
    पूर्ण अन्यथा अगर ((अगर_port >= 1 && अगर_port <= 2) ||
	       (local->mohawk && अगर_port==4))
	dev->अगर_port = अगर_port;
    अन्यथा
	pr_notice("invalid if_port requested\n");

    /* we can now रेजिस्टर the device with the net subप्रणाली */
    dev->irq = link->irq;
    dev->base_addr = link->resource[0]->start;

    अगर (local->dingo)
	करो_reset(dev, 1); /* a kludge to make the cem56 work */

    SET_NETDEV_DEV(dev, &link->dev);

    अगर ((err=रेजिस्टर_netdev(dev))) अणु
	pr_notice("register_netdev() failed\n");
	जाओ config_error;
    पूर्ण

    /* give some infos about the hardware */
    netdev_info(dev, "%s: port %#3lx, irq %d, hwaddr %pM\n",
		local->manf_str, (u_दीर्घ)dev->base_addr, (पूर्णांक)dev->irq,
		dev->dev_addr);

    वापस 0;

  config_error:
    xirc2ps_release(link);
    वापस -ENODEV;

  failure:
    वापस -ENODEV;
पूर्ण /* xirc2ps_config */

अटल व्योम
xirc2ps_release(काष्ठा pcmcia_device *link)
अणु
	dev_dbg(&link->dev, "release\n");

	अगर (link->resource[2]->end) अणु
		काष्ठा net_device *dev = link->priv;
		काष्ठा local_info *local = netdev_priv(dev);
		अगर (local->dingo)
			iounmap(local->dingo_ccr - 0x0800);
	पूर्ण
	pcmcia_disable_device(link);
पूर्ण /* xirc2ps_release */

/*====================================================================*/


अटल पूर्णांक xirc2ps_suspend(काष्ठा pcmcia_device *link)
अणु
	काष्ठा net_device *dev = link->priv;

	अगर (link->खोलो) अणु
		netअगर_device_detach(dev);
		करो_घातerकरोwn(dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xirc2ps_resume(काष्ठा pcmcia_device *link)
अणु
	काष्ठा net_device *dev = link->priv;

	अगर (link->खोलो) अणु
		करो_reset(dev,1);
		netअगर_device_attach(dev);
	पूर्ण

	वापस 0;
पूर्ण


/*====================================================================*/

/****************
 * This is the Interrupt service route.
 */
अटल irqवापस_t
xirc2ps_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
    काष्ठा net_device *dev = (काष्ठा net_device *)dev_id;
    काष्ठा local_info *lp = netdev_priv(dev);
    अचिन्हित पूर्णांक ioaddr;
    u_अक्षर saved_page;
    अचिन्हित bytes_rcvd;
    अचिन्हित पूर्णांक_status, eth_status, rx_status, tx_status;
    अचिन्हित rsr, pktlen;
    uदीर्घ start_ticks = jअगरfies; /* fixme: jअगरfies rollover every 497 days
				  * is this something to worry about?
				  * -- on a laptop?
				  */

    अगर (!netअगर_device_present(dev))
	वापस IRQ_HANDLED;

    ioaddr = dev->base_addr;
    अगर (lp->mohawk) अणु /* must disable the पूर्णांकerrupt */
	PutByte(XIRCREG_CR, 0);
    पूर्ण

    pr_debug("%s: interrupt %d at %#x.\n", dev->name, irq, ioaddr);

    saved_page = GetByte(XIRCREG_PR);
    /* Read the ISR to see whats the cause क्रम the पूर्णांकerrupt.
     * This also clears the पूर्णांकerrupt flags on CE2 cards
     */
    पूर्णांक_status = GetByte(XIRCREG_ISR);
    bytes_rcvd = 0;
  loop_entry:
    अगर (पूर्णांक_status == 0xff) अणु /* card may be ejected */
	pr_debug("%s: interrupt %d for dead card\n", dev->name, irq);
	जाओ leave;
    पूर्ण
    eth_status = GetByte(XIRCREG_ESR);

    SelectPage(0x40);
    rx_status  = GetByte(XIRCREG40_RXST0);
    PutByte(XIRCREG40_RXST0, (~rx_status & 0xff));
    tx_status = GetByte(XIRCREG40_TXST0);
    tx_status |= GetByte(XIRCREG40_TXST1) << 8;
    PutByte(XIRCREG40_TXST0, 0);
    PutByte(XIRCREG40_TXST1, 0);

    pr_debug("%s: ISR=%#2.2x ESR=%#2.2x RSR=%#2.2x TSR=%#4.4x\n",
	  dev->name, पूर्णांक_status, eth_status, rx_status, tx_status);

    /***** receive section ******/
    SelectPage(0);
    जबतक (eth_status & FullPktRcvd) अणु
	rsr = GetByte(XIRCREG0_RSR);
	अगर (bytes_rcvd > maxrx_bytes && (rsr & PktRxOk)) अणु
	    /* too many bytes received during this पूर्णांक, drop the rest of the
	     * packets */
	    dev->stats.rx_dropped++;
	    pr_debug("%s: RX drop, too much done\n", dev->name);
	पूर्ण अन्यथा अगर (rsr & PktRxOk) अणु
	    काष्ठा sk_buff *skb;

	    pktlen = GetWord(XIRCREG0_RBC);
	    bytes_rcvd += pktlen;

	    pr_debug("rsr=%#02x packet_length=%u\n", rsr, pktlen);

	    /* 1 extra so we can use insw */
	    skb = netdev_alloc_skb(dev, pktlen + 3);
	    अगर (!skb) अणु
		dev->stats.rx_dropped++;
	    पूर्ण अन्यथा अणु /* okay get the packet */
		skb_reserve(skb, 2);
		अगर (lp->silicon == 0 ) अणु /* work around a hardware bug */
		    अचिन्हित rhsa; /* receive start address */

		    SelectPage(5);
		    rhsa = GetWord(XIRCREG5_RHSA0);
		    SelectPage(0);
		    rhsa += 3; /* skip control infos */
		    अगर (rhsa >= 0x8000)
			rhsa = 0;
		    अगर (rhsa + pktlen > 0x8000) अणु
			अचिन्हित i;
			u_अक्षर *buf = skb_put(skb, pktlen);
			क्रम (i=0; i < pktlen ; i++, rhsa++) अणु
			    buf[i] = GetByte(XIRCREG_EDP);
			    अगर (rhsa == 0x8000) अणु
				rhsa = 0;
				i--;
			    पूर्ण
			पूर्ण
		    पूर्ण अन्यथा अणु
			insw(ioaddr+XIRCREG_EDP,
				skb_put(skb, pktlen), (pktlen+1)>>1);
		    पूर्ण
		पूर्ण
	      #अगर 0
		अन्यथा अगर (lp->mohawk) अणु
		    /* To use this 32 bit access we should use
		     * a manual optimized loop
		     * Also the words are swapped, we can get more
		     * perक्रमmance by using 32 bit access and swapping
		     * the words in a रेजिस्टर. Will need this क्रम cardbus
		     *
		     * Note: करोn't क्रमget to change the ALLOC_SKB to .. +3
		     */
		    अचिन्हित i;
		    u_दीर्घ *p = skb_put(skb, pktlen);
		    रेजिस्टर u_दीर्घ a;
		    अचिन्हित पूर्णांक edpreg = ioaddr+XIRCREG_EDP-2;
		    क्रम (i=0; i < len ; i += 4, p++) अणु
			a = inl(edpreg);
			__यंत्र__("rorl $16,%0\n\t"
				:"=q" (a)
				: "0" (a));
			*p = a;
		    पूर्ण
		पूर्ण
	      #पूर्ण_अगर
		अन्यथा अणु
		    insw(ioaddr+XIRCREG_EDP, skb_put(skb, pktlen),
			    (pktlen+1)>>1);
		पूर्ण
		skb->protocol = eth_type_trans(skb, dev);
		netअगर_rx(skb);
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += pktlen;
		अगर (!(rsr & PhyPkt))
		    dev->stats.multicast++;
	    पूर्ण
	पूर्ण अन्यथा अणु /* bad packet */
	    pr_debug("rsr=%#02x\n", rsr);
	पूर्ण
	अगर (rsr & PktTooLong) अणु
	    dev->stats.rx_frame_errors++;
	    pr_debug("%s: Packet too long\n", dev->name);
	पूर्ण
	अगर (rsr & CRCErr) अणु
	    dev->stats.rx_crc_errors++;
	    pr_debug("%s: CRC error\n", dev->name);
	पूर्ण
	अगर (rsr & AlignErr) अणु
	    dev->stats.rx_fअगरo_errors++; /* okay ? */
	    pr_debug("%s: Alignment error\n", dev->name);
	पूर्ण

	/* clear the received/dropped/error packet */
	PutWord(XIRCREG0_DO, 0x8000); /* issue cmd: skip_rx_packet */

	/* get the new ethernet status */
	eth_status = GetByte(XIRCREG_ESR);
    पूर्ण
    अगर (rx_status & 0x10) अणु /* Receive overrun */
	dev->stats.rx_over_errors++;
	PutByte(XIRCREG_CR, ClearRxOvrun);
	pr_debug("receive overrun cleared\n");
    पूर्ण

    /***** transmit section ******/
    अगर (पूर्णांक_status & PktTxed) अणु
	अचिन्हित n, nn;

	n = lp->last_ptr_value;
	nn = GetByte(XIRCREG0_PTR);
	lp->last_ptr_value = nn;
	अगर (nn < n) /* rollover */
	    dev->stats.tx_packets += 256 - n;
	अन्यथा अगर (n == nn) अणु /* happens someबार - करोn't know why */
	    pr_debug("PTR not changed?\n");
	पूर्ण अन्यथा
	    dev->stats.tx_packets += lp->last_ptr_value - n;
	netअगर_wake_queue(dev);
    पूर्ण
    अगर (tx_status & 0x0002) अणु	/* Excessive collisions */
	pr_debug("tx restarted due to excessive collisions\n");
	PutByte(XIRCREG_CR, RestartTx);  /* restart transmitter process */
    पूर्ण
    अगर (tx_status & 0x0040)
	dev->stats.tx_पातed_errors++;

    /* recalculate our work chunk so that we limit the duration of this
     * ISR to about 1/10 of a second.
     * Calculate only अगर we received a reasonable amount of bytes.
     */
    अगर (bytes_rcvd > 1000) अणु
	u_दीर्घ duration = jअगरfies - start_ticks;

	अगर (duration >= HZ/10) अणु /* अगर more than about 1/10 second */
	    maxrx_bytes = (bytes_rcvd * (HZ/10)) / duration;
	    अगर (maxrx_bytes < 2000)
		maxrx_bytes = 2000;
	    अन्यथा अगर (maxrx_bytes > 22000)
		maxrx_bytes = 22000;
	    pr_debug("set maxrx=%u (rcvd=%u ticks=%lu)\n",
		  maxrx_bytes, bytes_rcvd, duration);
	पूर्ण अन्यथा अगर (!duration && maxrx_bytes < 22000) अणु
	    /* now much faster */
	    maxrx_bytes += 2000;
	    अगर (maxrx_bytes > 22000)
		maxrx_bytes = 22000;
	    pr_debug("set maxrx=%u\n", maxrx_bytes);
	पूर्ण
    पूर्ण

  leave:
    अगर (lockup_hack) अणु
	अगर (पूर्णांक_status != 0xff && (पूर्णांक_status = GetByte(XIRCREG_ISR)) != 0)
	    जाओ loop_entry;
    पूर्ण
    SelectPage(saved_page);
    PutByte(XIRCREG_CR, EnableIntr);  /* re-enable पूर्णांकerrupts */
    /* Instead of dropping packets during a receive, we could
     * क्रमce an पूर्णांकerrupt with this command:
     *	  PutByte(XIRCREG_CR, EnableIntr|ForceIntr);
     */
    वापस IRQ_HANDLED;
पूर्ण /* xirc2ps_पूर्णांकerrupt */

/*====================================================================*/

अटल व्योम
xirc2ps_tx_समयout_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा local_info *local =
		container_of(work, काष्ठा local_info, tx_समयout_task);
	काष्ठा net_device *dev = local->dev;
    /* reset the card */
    करो_reset(dev,1);
    netअगर_trans_update(dev); /* prevent tx समयout */
    netअगर_wake_queue(dev);
पूर्ण

अटल व्योम
xirc_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
    काष्ठा local_info *lp = netdev_priv(dev);
    dev->stats.tx_errors++;
    netdev_notice(dev, "transmit timed out\n");
    schedule_work(&lp->tx_समयout_task);
पूर्ण

अटल netdev_tx_t
करो_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
    काष्ठा local_info *lp = netdev_priv(dev);
    अचिन्हित पूर्णांक ioaddr = dev->base_addr;
    पूर्णांक okay;
    अचिन्हित मुक्तspace;
    अचिन्हित pktlen = skb->len;

    pr_debug("do_start_xmit(skb=%p, dev=%p) len=%u\n",
	  skb, dev, pktlen);


    /* adjust the packet length to min. required
     * and hope that the buffer is large enough
     * to provide some अक्रमom data.
     * fixme: For Mohawk we can change this by sending
     * a larger packetlen than we actually have; the chip will
     * pad this in his buffer with अक्रमom bytes
     */
    अगर (pktlen < ETH_ZLEN)
    अणु
        अगर (skb_padto(skb, ETH_ZLEN))
        	वापस NETDEV_TX_OK;
	pktlen = ETH_ZLEN;
    पूर्ण

    netअगर_stop_queue(dev);
    SelectPage(0);
    PutWord(XIRCREG0_TRS, (u_लघु)pktlen+2);
    मुक्तspace = GetWord(XIRCREG0_TSO);
    okay = मुक्तspace & 0x8000;
    मुक्तspace &= 0x7fff;
    /* TRS करोesn't work - (indeed it is eliminated with sil-rev 1) */
    okay = pktlen +2 < मुक्तspace;
    pr_debug("%s: avail. tx space=%u%s\n",
	  dev->name, मुक्तspace, okay ? " (okay)":" (not enough)");
    अगर (!okay) अणु /* not enough space */
	वापस NETDEV_TX_BUSY;  /* upper layer may decide to requeue this packet */
    पूर्ण
    /* send the packet */
    PutWord(XIRCREG_EDP, (u_लघु)pktlen);
    outsw(ioaddr+XIRCREG_EDP, skb->data, pktlen>>1);
    अगर (pktlen & 1)
	PutByte(XIRCREG_EDP, skb->data[pktlen-1]);

    अगर (lp->mohawk)
	PutByte(XIRCREG_CR, TransmitPacket|EnableIntr);

    dev_kमुक्त_skb (skb);
    dev->stats.tx_bytes += pktlen;
    netअगर_start_queue(dev);
    वापस NETDEV_TX_OK;
पूर्ण

काष्ठा set_address_info अणु
	पूर्णांक reg_nr;
	पूर्णांक page_nr;
	पूर्णांक mohawk;
	अचिन्हित पूर्णांक ioaddr;
पूर्ण;

अटल व्योम set_address(काष्ठा set_address_info *sa_info, अक्षर *addr)
अणु
	अचिन्हित पूर्णांक ioaddr = sa_info->ioaddr;
	पूर्णांक i;

	क्रम (i = 0; i < 6; i++) अणु
		अगर (sa_info->reg_nr > 15) अणु
			sa_info->reg_nr = 8;
			sa_info->page_nr++;
			SelectPage(sa_info->page_nr);
		पूर्ण
		अगर (sa_info->mohawk)
			PutByte(sa_info->reg_nr++, addr[5 - i]);
		अन्यथा
			PutByte(sa_info->reg_nr++, addr[i]);
	पूर्ण
पूर्ण

/****************
 * Set all addresses: This first one is the inभागidual address,
 * the next 9 addresses are taken from the multicast list and
 * the rest is filled with the inभागidual address.
 */
अटल व्योम set_addresses(काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक ioaddr = dev->base_addr;
	काष्ठा local_info *lp = netdev_priv(dev);
	काष्ठा netdev_hw_addr *ha;
	काष्ठा set_address_info sa_info;
	पूर्णांक i;

	/*
	 * Setup the info काष्ठाure so that by first set_address call it will करो
	 * SelectPage with the right page number. Hence these ones here.
	 */
	sa_info.reg_nr = 15 + 1;
	sa_info.page_nr = 0x50 - 1;
	sa_info.mohawk = lp->mohawk;
	sa_info.ioaddr = ioaddr;

	set_address(&sa_info, dev->dev_addr);
	i = 0;
	netdev_क्रम_each_mc_addr(ha, dev) अणु
		अगर (i++ == 9)
			अवरोध;
		set_address(&sa_info, ha->addr);
	पूर्ण
	जबतक (i++ < 9)
		set_address(&sa_info, dev->dev_addr);
	SelectPage(0);
पूर्ण

/****************
 * Set or clear the multicast filter क्रम this adaptor.
 * We can filter up to 9 addresses, अगर more are requested we set
 * multicast promiscuous mode.
 */

अटल व्योम
set_multicast_list(काष्ठा net_device *dev)
अणु
    अचिन्हित पूर्णांक ioaddr = dev->base_addr;
    अचिन्हित value;

    SelectPage(0x42);
    value = GetByte(XIRCREG42_SWC1) & 0xC0;

    अगर (dev->flags & IFF_PROMISC) अणु /* snoop */
	PutByte(XIRCREG42_SWC1, value | 0x06); /* set MPE and PME */
    पूर्ण अन्यथा अगर (netdev_mc_count(dev) > 9 || (dev->flags & IFF_ALLMULTI)) अणु
	PutByte(XIRCREG42_SWC1, value | 0x02); /* set MPE */
    पूर्ण अन्यथा अगर (!netdev_mc_empty(dev)) अणु
	/* the chip can filter 9 addresses perfectly */
	PutByte(XIRCREG42_SWC1, value | 0x01);
	SelectPage(0x40);
	PutByte(XIRCREG40_CMD0, Offline);
	set_addresses(dev);
	SelectPage(0x40);
	PutByte(XIRCREG40_CMD0, EnableRecv | Online);
    पूर्ण अन्यथा अणु /* standard usage */
	PutByte(XIRCREG42_SWC1, value | 0x00);
    पूर्ण
    SelectPage(0);
पूर्ण

अटल पूर्णांक
करो_config(काष्ठा net_device *dev, काष्ठा अगरmap *map)
अणु
    काष्ठा local_info *local = netdev_priv(dev);

    pr_debug("do_config(%p)\n", dev);
    अगर (map->port != 255 && map->port != dev->अगर_port) अणु
	अगर (map->port > 4)
	    वापस -EINVAL;
	अगर (!map->port) अणु
	    local->probe_port = 1;
	    dev->अगर_port = 1;
	पूर्ण अन्यथा अणु
	    local->probe_port = 0;
	    dev->अगर_port = map->port;
	पूर्ण
	netdev_info(dev, "switching to %s port\n", अगर_names[dev->अगर_port]);
	करो_reset(dev,1);  /* not the fine way :-) */
    पूर्ण
    वापस 0;
पूर्ण

/****************
 * Open the driver
 */
अटल पूर्णांक
करो_खोलो(काष्ठा net_device *dev)
अणु
    काष्ठा local_info *lp = netdev_priv(dev);
    काष्ठा pcmcia_device *link = lp->p_dev;

    dev_dbg(&link->dev, "do_open(%p)\n", dev);

    /* Check that the PCMCIA card is still here. */
    /* Physical device present signature. */
    अगर (!pcmcia_dev_present(link))
	वापस -ENODEV;

    /* okay */
    link->खोलो++;

    netअगर_start_queue(dev);
    करो_reset(dev,1);

    वापस 0;
पूर्ण

अटल व्योम netdev_get_drvinfo(काष्ठा net_device *dev,
			       काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, "xirc2ps_cs", माप(info->driver));
	snम_लिखो(info->bus_info, माप(info->bus_info), "PCMCIA 0x%lx",
		 dev->base_addr);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops netdev_ethtool_ops = अणु
	.get_drvinfo		= netdev_get_drvinfo,
पूर्ण;

अटल पूर्णांक
करो_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
    काष्ठा local_info *local = netdev_priv(dev);
    अचिन्हित पूर्णांक ioaddr = dev->base_addr;
    काष्ठा mii_ioctl_data *data = अगर_mii(rq);

    pr_debug("%s: ioctl(%-.6s, %#04x) %04x %04x %04x %04x\n",
	  dev->name, rq->अगरr_अगरrn.अगरrn_name, cmd,
	  data->phy_id, data->reg_num, data->val_in, data->val_out);

    अगर (!local->mohawk)
	वापस -EOPNOTSUPP;

    चयन(cmd) अणु
      हाल SIOCGMIIPHY:		/* Get the address of the PHY in use. */
	data->phy_id = 0;	/* we have only this address */
	fallthrough;
      हाल SIOCGMIIREG:		/* Read the specअगरied MII रेजिस्टर. */
	data->val_out = mii_rd(ioaddr, data->phy_id & 0x1f,
			       data->reg_num & 0x1f);
	अवरोध;
      हाल SIOCSMIIREG:		/* Write the specअगरied MII रेजिस्टर */
	mii_wr(ioaddr, data->phy_id & 0x1f, data->reg_num & 0x1f, data->val_in,
	       16);
	अवरोध;
      शेष:
	वापस -EOPNOTSUPP;
    पूर्ण
    वापस 0;
पूर्ण

अटल व्योम
hardreset(काष्ठा net_device *dev)
अणु
    काष्ठा local_info *local = netdev_priv(dev);
    अचिन्हित पूर्णांक ioaddr = dev->base_addr;

    SelectPage(4);
    udelay(1);
    PutByte(XIRCREG4_GPR1, 0);	     /* clear bit 0: घातer करोwn */
    msleep(40);				     /* रुको 40 msec */
    अगर (local->mohawk)
	PutByte(XIRCREG4_GPR1, 1);	 /* set bit 0: घातer up */
    अन्यथा
	PutByte(XIRCREG4_GPR1, 1 | 4);	 /* set bit 0: घातer up, bit 2: AIC */
    msleep(20);			     /* रुको 20 msec */
पूर्ण

अटल व्योम
करो_reset(काष्ठा net_device *dev, पूर्णांक full)
अणु
    काष्ठा local_info *local = netdev_priv(dev);
    अचिन्हित पूर्णांक ioaddr = dev->base_addr;
    अचिन्हित value;

    pr_debug("%s: do_reset(%p,%d)\n", dev->name, dev, full);

    hardreset(dev);
    PutByte(XIRCREG_CR, SoftReset); /* set */
    msleep(20);			     /* रुको 20 msec */
    PutByte(XIRCREG_CR, 0);	     /* clear */
    msleep(40);			     /* रुको 40 msec */
    अगर (local->mohawk) अणु
	SelectPage(4);
	/* set pin GP1 and GP2 to output  (0x0c)
	 * set GP1 to low to घातer up the ML6692 (0x00)
	 * set GP2 to high to घातer up the 10Mhz chip  (0x02)
	 */
	PutByte(XIRCREG4_GPR0, 0x0e);
    पूर्ण

    /* give the circuits some समय to घातer up */
    msleep(500);			/* about 500ms */

    local->last_ptr_value = 0;
    local->silicon = local->mohawk ? (GetByte(XIRCREG4_BOV) & 0x70) >> 4
				   : (GetByte(XIRCREG4_BOV) & 0x30) >> 4;

    अगर (local->probe_port) अणु
	अगर (!local->mohawk) अणु
	    SelectPage(4);
	    PutByte(XIRCREG4_GPR0, 4);
	    local->probe_port = 0;
	पूर्ण
    पूर्ण अन्यथा अगर (dev->अगर_port == 2) अणु /* enable 10Base2 */
	SelectPage(0x42);
	PutByte(XIRCREG42_SWC1, 0xC0);
    पूर्ण अन्यथा अणु /* enable 10BaseT */
	SelectPage(0x42);
	PutByte(XIRCREG42_SWC1, 0x80);
    पूर्ण
    msleep(40);			     /* रुको 40 msec to let it complete */

  #अगर 0
    अणु
	SelectPage(0);
	value = GetByte(XIRCREG_ESR);	 /* पढ़ो the ESR */
	pr_debug("%s: ESR is: %#02x\n", dev->name, value);
    पूर्ण
  #पूर्ण_अगर

    /* setup the ECR */
    SelectPage(1);
    PutByte(XIRCREG1_IMR0, 0xff); /* allow all पूर्णांकs */
    PutByte(XIRCREG1_IMR1, 1	); /* and Set TxUnderrunDetect */
    value = GetByte(XIRCREG1_ECR);
  #अगर 0
    अगर (local->mohawk)
	value |= DisableLinkPulse;
    PutByte(XIRCREG1_ECR, value);
  #पूर्ण_अगर
    pr_debug("%s: ECR is: %#02x\n", dev->name, value);

    SelectPage(0x42);
    PutByte(XIRCREG42_SWC0, 0x20); /* disable source insertion */

    अगर (local->silicon != 1) अणु
	/* set the local memory भागiding line.
	 * The comments in the sample code say that this is only
	 * settable with the scipper version 2 which is revision 0.
	 * Always क्रम CE3 cards
	 */
	SelectPage(2);
	PutWord(XIRCREG2_RBS, 0x2000);
    पूर्ण

    अगर (full)
	set_addresses(dev);

    /* Hardware workaround:
     * The receive byte poपूर्णांकer after reset is off by 1 so we need
     * to move the offset poपूर्णांकer back to 0.
     */
    SelectPage(0);
    PutWord(XIRCREG0_DO, 0x2000); /* change offset command, off=0 */

    /* setup MAC IMRs and clear status रेजिस्टरs */
    SelectPage(0x40);		     /* Bit 7 ... bit 0 */
    PutByte(XIRCREG40_RMASK0, 0xff); /* ROK, RAB, rsv, RO, CRC, AE, PTL, MP */
    PutByte(XIRCREG40_TMASK0, 0xff); /* TOK, TAB, SQE, LL, TU, JAB, EXC, CRS */
    PutByte(XIRCREG40_TMASK1, 0xb0); /* rsv, rsv, PTD, EXT, rsv,rsv,rsv, rsv*/
    PutByte(XIRCREG40_RXST0,  0x00); /* ROK, RAB, REN, RO, CRC, AE, PTL, MP */
    PutByte(XIRCREG40_TXST0,  0x00); /* TOK, TAB, SQE, LL, TU, JAB, EXC, CRS */
    PutByte(XIRCREG40_TXST1,  0x00); /* TEN, rsv, PTD, EXT, retry_counter:4  */

    अगर (full && local->mohawk && init_mii(dev)) अणु
	अगर (dev->अगर_port == 4 || local->dingo || local->new_mii) अणु
	    netdev_info(dev, "MII selected\n");
	    SelectPage(2);
	    PutByte(XIRCREG2_MSR, GetByte(XIRCREG2_MSR) | 0x08);
	    msleep(20);
	पूर्ण अन्यथा अणु
	    netdev_info(dev, "MII detected; using 10mbs\n");
	    SelectPage(0x42);
	    अगर (dev->अगर_port == 2) /* enable 10Base2 */
		PutByte(XIRCREG42_SWC1, 0xC0);
	    अन्यथा  /* enable 10BaseT */
		PutByte(XIRCREG42_SWC1, 0x80);
	    msleep(40);			/* रुको 40 msec to let it complete */
	पूर्ण
	अगर (full_duplex)
	    PutByte(XIRCREG1_ECR, GetByte(XIRCREG1_ECR | FullDuplex));
    पूर्ण अन्यथा अणु  /* No MII */
	SelectPage(0);
	value = GetByte(XIRCREG_ESR);	 /* पढ़ो the ESR */
	dev->अगर_port = (value & MediaSelect) ? 1 : 2;
    पूर्ण

    /* configure the LEDs */
    SelectPage(2);
    अगर (dev->अगर_port == 1 || dev->अगर_port == 4) /* TP: Link and Activity */
	PutByte(XIRCREG2_LED, 0x3b);
    अन्यथा			      /* Coax: Not-Collision and Activity */
	PutByte(XIRCREG2_LED, 0x3a);

    अगर (local->dingo)
	PutByte(0x0b, 0x04); /* 100 Mbit LED */

    /* enable receiver and put the mac online */
    अगर (full) अणु
	set_multicast_list(dev);
	SelectPage(0x40);
	PutByte(XIRCREG40_CMD0, EnableRecv | Online);
    पूर्ण

    /* setup Ethernet IMR and enable पूर्णांकerrupts */
    SelectPage(1);
    PutByte(XIRCREG1_IMR0, 0xff);
    udelay(1);
    SelectPage(0);
    PutByte(XIRCREG_CR, EnableIntr);
    अगर (local->modem && !local->dingo) अणु /* करो some magic */
	अगर (!(GetByte(0x10) & 0x01))
	    PutByte(0x10, 0x11); /* unmask master-पूर्णांक bit */
    पूर्ण

    अगर (full)
	netdev_info(dev, "media %s, silicon revision %d\n",
		    अगर_names[dev->अगर_port], local->silicon);
    /* We should चयन back to page 0 to aव्योम a bug in revision 0
     * where regs with offset below 8 can't be पढ़ो after an access
     * to the MAC रेजिस्टरs */
    SelectPage(0);
पूर्ण

/****************
 * Initialize the Media-Independent-Interface
 * Returns: True अगर we have a good MII
 */
अटल पूर्णांक
init_mii(काष्ठा net_device *dev)
अणु
    काष्ठा local_info *local = netdev_priv(dev);
    अचिन्हित पूर्णांक ioaddr = dev->base_addr;
    अचिन्हित control, status, linkpartner;
    पूर्णांक i;

    अगर (अगर_port == 4 || अगर_port == 1) अणु /* क्रमce 100BaseT or 10BaseT */
	dev->अगर_port = अगर_port;
	local->probe_port = 0;
	वापस 1;
    पूर्ण

    status = mii_rd(ioaddr,  0, 1);
    अगर ((status & 0xff00) != 0x7800)
	वापस 0; /* No MII */

    local->new_mii = (mii_rd(ioaddr, 0, 2) != 0xffff);
    
    अगर (local->probe_port)
	control = 0x1000; /* स्वतः neg */
    अन्यथा अगर (dev->अगर_port == 4)
	control = 0x2000; /* no स्वतः neg, 100mbs mode */
    अन्यथा
	control = 0x0000; /* no स्वतः neg, 10mbs mode */
    mii_wr(ioaddr,  0, 0, control, 16);
    udelay(100);
    control = mii_rd(ioaddr, 0, 0);

    अगर (control & 0x0400) अणु
	netdev_notice(dev, "can't take PHY out of isolation mode\n");
	local->probe_port = 0;
	वापस 0;
    पूर्ण

    अगर (local->probe_port) अणु
	/* according to the DP83840A specs the स्वतः negotiation process
	 * may take up to 3.5 sec, so we use this also क्रम our ML6692
	 * Fixme: Better to use a समयr here!
	 */
	क्रम (i=0; i < 35; i++) अणु
	    msleep(100);	 /* रुको 100 msec */
	    status = mii_rd(ioaddr,  0, 1);
	    अगर ((status & 0x0020) && (status & 0x0004))
		अवरोध;
	पूर्ण

	अगर (!(status & 0x0020)) अणु
	    netdev_info(dev, "autonegotiation failed; using 10mbs\n");
	    अगर (!local->new_mii) अणु
		control = 0x0000;
		mii_wr(ioaddr,  0, 0, control, 16);
		udelay(100);
		SelectPage(0);
		dev->अगर_port = (GetByte(XIRCREG_ESR) & MediaSelect) ? 1 : 2;
	    पूर्ण
	पूर्ण अन्यथा अणु
	    linkpartner = mii_rd(ioaddr, 0, 5);
	    netdev_info(dev, "MII link partner: %04x\n", linkpartner);
	    अगर (linkpartner & 0x0080) अणु
		dev->अगर_port = 4;
	    पूर्ण अन्यथा
		dev->अगर_port = 1;
	पूर्ण
    पूर्ण

    वापस 1;
पूर्ण

अटल व्योम
करो_घातerकरोwn(काष्ठा net_device *dev)
अणु

    अचिन्हित पूर्णांक ioaddr = dev->base_addr;

    pr_debug("do_powerdown(%p)\n", dev);

    SelectPage(4);
    PutByte(XIRCREG4_GPR1, 0);	     /* clear bit 0: घातer करोwn */
    SelectPage(0);
पूर्ण

अटल पूर्णांक
करो_stop(काष्ठा net_device *dev)
अणु
    अचिन्हित पूर्णांक ioaddr = dev->base_addr;
    काष्ठा local_info *lp = netdev_priv(dev);
    काष्ठा pcmcia_device *link = lp->p_dev;

    dev_dbg(&link->dev, "do_stop(%p)\n", dev);

    अगर (!link)
	वापस -ENODEV;

    netअगर_stop_queue(dev);

    SelectPage(0);
    PutByte(XIRCREG_CR, 0);  /* disable पूर्णांकerrupts */
    SelectPage(0x01);
    PutByte(XIRCREG1_IMR0, 0x00); /* क्रमbid all पूर्णांकs */
    SelectPage(4);
    PutByte(XIRCREG4_GPR1, 0);	/* clear bit 0: घातer करोwn */
    SelectPage(0);

    link->खोलो--;
    वापस 0;
पूर्ण

अटल स्थिर काष्ठा pcmcia_device_id xirc2ps_ids[] = अणु
	PCMCIA_PFC_DEVICE_MANF_CARD(0, 0x0089, 0x110a),
	PCMCIA_PFC_DEVICE_MANF_CARD(0, 0x0138, 0x110a),
	PCMCIA_PFC_DEVICE_PROD_ID13(0, "Xircom", "CEM28", 0x2e3ee845, 0x0ea978ea),
	PCMCIA_PFC_DEVICE_PROD_ID13(0, "Xircom", "CEM33", 0x2e3ee845, 0x80609023),
	PCMCIA_PFC_DEVICE_PROD_ID13(0, "Xircom", "CEM56", 0x2e3ee845, 0xa650c32a),
	PCMCIA_PFC_DEVICE_PROD_ID13(0, "Xircom", "REM10", 0x2e3ee845, 0x76df1d29),
	PCMCIA_PFC_DEVICE_PROD_ID13(0, "Xircom", "XEM5600", 0x2e3ee845, 0xf1403719),
	PCMCIA_PFC_DEVICE_PROD_ID12(0, "Xircom", "CreditCard Ethernet+Modem II", 0x2e3ee845, 0xeca401bf),
	PCMCIA_DEVICE_MANF_CARD(0x01bf, 0x010a),
	PCMCIA_DEVICE_PROD_ID13("Toshiba Information Systems", "TPCENET", 0x1b3b94fe, 0xf381c1a2),
	PCMCIA_DEVICE_PROD_ID13("Xircom", "CE3-10/100", 0x2e3ee845, 0x0ec0ac37),
	PCMCIA_DEVICE_PROD_ID13("Xircom", "PS-CE2-10", 0x2e3ee845, 0x947d9073),
	PCMCIA_DEVICE_PROD_ID13("Xircom", "R2E-100BTX", 0x2e3ee845, 0x2464a6e3),
	PCMCIA_DEVICE_PROD_ID13("Xircom", "RE-10", 0x2e3ee845, 0x3e08d609),
	PCMCIA_DEVICE_PROD_ID13("Xircom", "XE2000", 0x2e3ee845, 0xf7188e46),
	PCMCIA_DEVICE_PROD_ID12("Compaq", "Ethernet LAN Card", 0x54f7c49c, 0x9fd2f0a2),
	PCMCIA_DEVICE_PROD_ID12("Compaq", "Netelligent 10/100 PC Card", 0x54f7c49c, 0xefe96769),
	PCMCIA_DEVICE_PROD_ID12("Intel", "EtherExpress(TM) PRO/100 PC Card Mobile Adapter16", 0x816cc815, 0x174397db),
	PCMCIA_DEVICE_PROD_ID12("Toshiba", "10/100 Ethernet PC Card", 0x44a09d9c, 0xb44deecf),
	/* also matches CFE-10 cards! */
	/* PCMCIA_DEVICE_MANF_CARD(0x0105, 0x010a), */
	PCMCIA_DEVICE_शून्य,
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, xirc2ps_ids);


अटल काष्ठा pcmcia_driver xirc2ps_cs_driver = अणु
	.owner		= THIS_MODULE,
	.name		= "xirc2ps_cs",
	.probe		= xirc2ps_probe,
	.हटाओ		= xirc2ps_detach,
	.id_table       = xirc2ps_ids,
	.suspend	= xirc2ps_suspend,
	.resume		= xirc2ps_resume,
पूर्ण;
module_pcmcia_driver(xirc2ps_cs_driver);

#अगर_अघोषित MODULE
अटल पूर्णांक __init setup_xirc2ps_cs(अक्षर *str)
अणु
	/* अगर_port, full_duplex, करो_sound, lockup_hack
	 */
	पूर्णांक पूर्णांकs[10] = अणु -1 पूर्ण;

	str = get_options(str, ARRAY_SIZE(पूर्णांकs), पूर्णांकs);

#घोषणा MAYBE_SET(X,Y) अगर (पूर्णांकs[0] >= Y && पूर्णांकs[Y] != -1) अणु X = पूर्णांकs[Y]; पूर्ण
	MAYBE_SET(अगर_port, 3);
	MAYBE_SET(full_duplex, 4);
	MAYBE_SET(करो_sound, 5);
	MAYBE_SET(lockup_hack, 6);
#अघोषित  MAYBE_SET

	वापस 1;
पूर्ण

__setup("xirc2ps_cs=", setup_xirc2ps_cs);
#पूर्ण_अगर
