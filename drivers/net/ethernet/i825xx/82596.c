<शैली गुरु>
/* 82596.c: A generic 82596 ethernet driver क्रम linux. */
/*
   Based on Apricot.c
   Written 1994 by Mark Evans.
   This driver is क्रम the Apricot 82596 bus-master पूर्णांकerface

   Modularised 12/94 Mark Evans


   Modअगरied to support the 82596 ethernet chips on 680x0 VME boards.
   by Riअक्षरd Hirst <riअक्षरd@sleepie.demon.co.uk>
   Renamed to be 82596.c

   980825:  Changed to receive directly in to sk_buffs which are
   allocated at खोलो() समय.  Eliminates copy on incoming frames
   (small ones are still copied).  Shared data now held in a
   non-cached page, so we can run on 68060 in copyback mode.

   TBD:
   * look at deferring rx frames rather than discarding (as per tulip)
   * handle tx ring full as per tulip
   * perक्रमmance test to tune rx_copyअवरोध

   Most of my modअगरications relate to the braindead big-endian
   implementation by Intel.  When the i596 is operating in
   'big-endian' mode, it thinks a 32 bit value of 0x12345678
   should be stored as 0x56781234.  This is a real pain, when
   you have linked lists which are shared by the 680x0 and the
   i596.

   Driver skeleton
   Written 1993 by Donald Becker.
   Copyright 1993 United States Government as represented by the Director,
   National Security Agency. This software may only be used and distributed
   according to the terms of the GNU General Public License as modअगरied by SRC,
   incorporated herein by reference.

   The author may be reached as becker@scyld.com, or C/O
   Scyld Computing Corporation, 410 Severn Ave., Suite 210, Annapolis MD 21403

 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/init.h>
#समावेश <linux/bitops.h>
#समावेश <linux/gfp.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/cacheflush.h>

अटल अक्षर version[] __initdata =
	"82596.c $Revision: 1.5 $\n";

#घोषणा DRV_NAME	"82596"

/* DEBUG flags
 */

#घोषणा DEB_INIT	0x0001
#घोषणा DEB_PROBE	0x0002
#घोषणा DEB_SERIOUS	0x0004
#घोषणा DEB_ERRORS	0x0008
#घोषणा DEB_MULTI	0x0010
#घोषणा DEB_TDR		0x0020
#घोषणा DEB_OPEN	0x0040
#घोषणा DEB_RESET	0x0080
#घोषणा DEB_ADDCMD	0x0100
#घोषणा DEB_STATUS	0x0200
#घोषणा DEB_STARTTX	0x0400
#घोषणा DEB_RXADDR	0x0800
#घोषणा DEB_TXADDR	0x1000
#घोषणा DEB_RXFRAME	0x2000
#घोषणा DEB_INTS	0x4000
#घोषणा DEB_STRUCT	0x8000
#घोषणा DEB_ANY		0xffff


#घोषणा DEB(x,y)	अगर (i596_debug & (x)) y


#अगर IS_ENABLED(CONFIG_MVME16x_NET)
#घोषणा ENABLE_MVME16x_NET
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_BVME6000_NET)
#घोषणा ENABLE_BVME6000_NET
#पूर्ण_अगर

#अगर_घोषित ENABLE_MVME16x_NET
#समावेश <यंत्र/mvme16xhw.h>
#पूर्ण_अगर
#अगर_घोषित ENABLE_BVME6000_NET
#समावेश <यंत्र/bvme6000hw.h>
#पूर्ण_अगर

/*
 * Define various macros क्रम Channel Attention, word swapping etc., dependent
 * on architecture.  MVME and BVME are 680x0 based, otherwise it is Intel.
 */

#अगर_घोषित __mc68000__
#घोषणा WSWAPrfd(x)  ((काष्ठा i596_rfd *) (((u32)(x)<<16) | ((((u32)(x)))>>16)))
#घोषणा WSWAPrbd(x)  ((काष्ठा i596_rbd *) (((u32)(x)<<16) | ((((u32)(x)))>>16)))
#घोषणा WSWAPiscp(x) ((काष्ठा i596_iscp *)(((u32)(x)<<16) | ((((u32)(x)))>>16)))
#घोषणा WSWAPscb(x)  ((काष्ठा i596_scb *) (((u32)(x)<<16) | ((((u32)(x)))>>16)))
#घोषणा WSWAPcmd(x)  ((काष्ठा i596_cmd *) (((u32)(x)<<16) | ((((u32)(x)))>>16)))
#घोषणा WSWAPtbd(x)  ((काष्ठा i596_tbd *) (((u32)(x)<<16) | ((((u32)(x)))>>16)))
#घोषणा WSWAPअक्षर(x) ((अक्षर *)            (((u32)(x)<<16) | ((((u32)(x)))>>16)))
#घोषणा ISCP_BUSY	0x00010000
#अन्यथा
#त्रुटि 82596.c: unknown architecture
#पूर्ण_अगर

/*
 * These were the पूर्णांकel versions, left here क्रम reference. There
 * are currently no x86 users of this legacy i82596 chip.
 */
#अगर 0
#घोषणा WSWAPrfd(x)     ((काष्ठा i596_rfd *)((दीर्घ)x))
#घोषणा WSWAPrbd(x)     ((काष्ठा i596_rbd *)((दीर्घ)x))
#घोषणा WSWAPiscp(x)    ((काष्ठा i596_iscp *)((दीर्घ)x))
#घोषणा WSWAPscb(x)     ((काष्ठा i596_scb *)((दीर्घ)x))
#घोषणा WSWAPcmd(x)     ((काष्ठा i596_cmd *)((दीर्घ)x))
#घोषणा WSWAPtbd(x)     ((काष्ठा i596_tbd *)((दीर्घ)x))
#घोषणा WSWAPअक्षर(x)    ((अक्षर *)((दीर्घ)x))
#घोषणा ISCP_BUSY	0x0001
#पूर्ण_अगर

/*
 * The MPU_PORT command allows direct access to the 82596. With PORT access
 * the following commands are available (p5-18). The 32-bit port command
 * must be word-swapped with the most signअगरicant word written first.
 * This only applies to VME boards.
 */
#घोषणा PORT_RESET		0x00	/* reset 82596 */
#घोषणा PORT_SELFTEST		0x01	/* selftest */
#घोषणा PORT_ALTSCP		0x02	/* alternate SCB address */
#घोषणा PORT_ALTDUMP		0x03	/* Alternate DUMP address */

अटल पूर्णांक i596_debug = (DEB_SERIOUS|DEB_PROBE);

MODULE_AUTHOR("Richard Hirst");
MODULE_DESCRIPTION("i82596 driver");
MODULE_LICENSE("GPL");

module_param(i596_debug, पूर्णांक, 0);
MODULE_PARM_DESC(i596_debug, "i82596 debug mask");


/* Copy frames लघुer than rx_copyअवरोध, otherwise pass on up in
 * a full sized sk_buff.  Value of 100 stolen from tulip.c (!alpha).
 */
अटल पूर्णांक rx_copyअवरोध = 100;

#घोषणा PKT_BUF_SZ	1536
#घोषणा MAX_MC_CNT	64

#घोषणा I596_TOTAL_SIZE 17

#घोषणा I596_शून्य ((व्योम *)0xffffffff)

#घोषणा CMD_EOL		0x8000	/* The last command of the list, stop. */
#घोषणा CMD_SUSP	0x4000	/* Suspend after करोing cmd. */
#घोषणा CMD_INTR	0x2000	/* Interrupt after करोing cmd. */

#घोषणा CMD_FLEX	0x0008	/* Enable flexible memory model */

क्रमागत commands अणु
	CmdNOp = 0, CmdSASetup = 1, CmdConfigure = 2, CmdMulticastList = 3,
	CmdTx = 4, CmdTDR = 5, CmdDump = 6, CmdDiagnose = 7
पूर्ण;

#घोषणा STAT_C		0x8000	/* Set to 0 after execution */
#घोषणा STAT_B		0x4000	/* Command being executed */
#घोषणा STAT_OK		0x2000	/* Command executed ok */
#घोषणा STAT_A		0x1000	/* Command पातed */

#घोषणा	 CUC_START	0x0100
#घोषणा	 CUC_RESUME	0x0200
#घोषणा	 CUC_SUSPEND    0x0300
#घोषणा	 CUC_ABORT	0x0400
#घोषणा	 RX_START	0x0010
#घोषणा	 RX_RESUME	0x0020
#घोषणा	 RX_SUSPEND	0x0030
#घोषणा	 RX_ABORT	0x0040

#घोषणा TX_TIMEOUT	(HZ/20)


काष्ठा i596_reg अणु
	अचिन्हित लघु porthi;
	अचिन्हित लघु portlo;
	अचिन्हित दीर्घ ca;
पूर्ण;

#घोषणा खातापूर्ण		0x8000
#घोषणा SIZE_MASK	0x3fff

काष्ठा i596_tbd अणु
	अचिन्हित लघु size;
	अचिन्हित लघु pad;
	काष्ठा i596_tbd *next;
	अक्षर *data;
पूर्ण;

/* The command काष्ठाure has two 'next' poपूर्णांकers; v_next is the address of
 * the next command as seen by the CPU, b_next is the address of the next
 * command as seen by the 82596.  The b_next poपूर्णांकer, as used by the 82596
 * always references the status field of the next command, rather than the
 * v_next field, because the 82596 is unaware of v_next.  It may seem more
 * logical to put v_next at the end of the काष्ठाure, but we cannot करो that
 * because the 82596 expects other fields to be there, depending on command
 * type.
 */

काष्ठा i596_cmd अणु
	काष्ठा i596_cmd *v_next;	/* Address from CPUs viewpoपूर्णांक */
	अचिन्हित लघु status;
	अचिन्हित लघु command;
	काष्ठा i596_cmd *b_next;	/* Address from i596 viewpoपूर्णांक */
पूर्ण;

काष्ठा tx_cmd अणु
	काष्ठा i596_cmd cmd;
	काष्ठा i596_tbd *tbd;
	अचिन्हित लघु size;
	अचिन्हित लघु pad;
	काष्ठा sk_buff *skb;	/* So we can मुक्त it after tx */
पूर्ण;

काष्ठा tdr_cmd अणु
	काष्ठा i596_cmd cmd;
	अचिन्हित लघु status;
	अचिन्हित लघु pad;
पूर्ण;

काष्ठा mc_cmd अणु
	काष्ठा i596_cmd cmd;
	लघु mc_cnt;
	अक्षर mc_addrs[MAX_MC_CNT*6];
पूर्ण;

काष्ठा sa_cmd अणु
	काष्ठा i596_cmd cmd;
	अक्षर eth_addr[8];
पूर्ण;

काष्ठा cf_cmd अणु
	काष्ठा i596_cmd cmd;
	अक्षर i596_config[16];
पूर्ण;

काष्ठा i596_rfd अणु
	अचिन्हित लघु stat;
	अचिन्हित लघु cmd;
	काष्ठा i596_rfd *b_next;	/* Address from i596 viewpoपूर्णांक */
	काष्ठा i596_rbd *rbd;
	अचिन्हित लघु count;
	अचिन्हित लघु size;
	काष्ठा i596_rfd *v_next;	/* Address from CPUs viewpoपूर्णांक */
	काष्ठा i596_rfd *v_prev;
पूर्ण;

काष्ठा i596_rbd अणु
    अचिन्हित लघु count;
    अचिन्हित लघु zero1;
    काष्ठा i596_rbd *b_next;
    अचिन्हित अक्षर *b_data;		/* Address from i596 viewpoपूर्णांक */
    अचिन्हित लघु size;
    अचिन्हित लघु zero2;
    काष्ठा sk_buff *skb;
    काष्ठा i596_rbd *v_next;
    काष्ठा i596_rbd *b_addr;		/* This rbd addr from i596 view */
    अचिन्हित अक्षर *v_data;		/* Address from CPUs viewpoपूर्णांक */
पूर्ण;

#घोषणा TX_RING_SIZE 64
#घोषणा RX_RING_SIZE 16

काष्ठा i596_scb अणु
	अचिन्हित लघु status;
	अचिन्हित लघु command;
	काष्ठा i596_cmd *cmd;
	काष्ठा i596_rfd *rfd;
	अचिन्हित दीर्घ crc_err;
	अचिन्हित दीर्घ align_err;
	अचिन्हित दीर्घ resource_err;
	अचिन्हित दीर्घ over_err;
	अचिन्हित दीर्घ rcvdt_err;
	अचिन्हित दीर्घ लघु_err;
	अचिन्हित लघु t_on;
	अचिन्हित लघु t_off;
पूर्ण;

काष्ठा i596_iscp अणु
	अचिन्हित दीर्घ stat;
	काष्ठा i596_scb *scb;
पूर्ण;

काष्ठा i596_scp अणु
	अचिन्हित दीर्घ sysbus;
	अचिन्हित दीर्घ pad;
	काष्ठा i596_iscp *iscp;
पूर्ण;

काष्ठा i596_निजी अणु
	अस्थिर काष्ठा i596_scp scp;
	अस्थिर काष्ठा i596_iscp iscp;
	अस्थिर काष्ठा i596_scb scb;
	काष्ठा sa_cmd sa_cmd;
	काष्ठा cf_cmd cf_cmd;
	काष्ठा tdr_cmd tdr_cmd;
	काष्ठा mc_cmd mc_cmd;
	अचिन्हित दीर्घ stat;
	पूर्णांक last_restart __attribute__((aligned(4)));
	काष्ठा i596_rfd *rfd_head;
	काष्ठा i596_rbd *rbd_head;
	काष्ठा i596_cmd *cmd_tail;
	काष्ठा i596_cmd *cmd_head;
	पूर्णांक cmd_backlog;
	अचिन्हित दीर्घ last_cmd;
	काष्ठा i596_rfd rfds[RX_RING_SIZE];
	काष्ठा i596_rbd rbds[RX_RING_SIZE];
	काष्ठा tx_cmd tx_cmds[TX_RING_SIZE];
	काष्ठा i596_tbd tbds[TX_RING_SIZE];
	पूर्णांक next_tx_cmd;
	spinlock_t lock;
पूर्ण;

अटल अक्षर init_setup[] =
अणु
	0x8E,			/* length, prefetch on */
	0xC8,			/* fअगरo to 8, monitor off */
#अगर_घोषित CONFIG_VME
	0xc0,			/* करोn't save bad frames */
#अन्यथा
	0x80,			/* करोn't save bad frames */
#पूर्ण_अगर
	0x2E,			/* No source address insertion, 8 byte preamble */
	0x00,			/* priority and backoff शेषs */
	0x60,			/* पूर्णांकerframe spacing */
	0x00,			/* slot समय LSB */
	0xf2,			/* slot समय and retries */
	0x00,			/* promiscuous mode */
	0x00,			/* collision detect */
	0x40,			/* minimum frame length */
	0xff,
	0x00,
	0x7f /*  *multi IA */ पूर्ण;

अटल पूर्णांक i596_खोलो(काष्ठा net_device *dev);
अटल netdev_tx_t i596_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
अटल irqवापस_t i596_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल पूर्णांक i596_बंद(काष्ठा net_device *dev);
अटल व्योम i596_add_cmd(काष्ठा net_device *dev, काष्ठा i596_cmd *cmd);
अटल व्योम i596_tx_समयout (काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल व्योम prपूर्णांक_eth(अचिन्हित अक्षर *buf, अक्षर *str);
अटल व्योम set_multicast_list(काष्ठा net_device *dev);

अटल पूर्णांक rx_ring_size = RX_RING_SIZE;
अटल पूर्णांक ticks_limit = 25;
अटल पूर्णांक max_cmd_backlog = TX_RING_SIZE-1;


अटल अंतरभूत व्योम CA(काष्ठा net_device *dev)
अणु
#अगर_घोषित ENABLE_MVME16x_NET
	अगर (MACH_IS_MVME16x) अणु
		((काष्ठा i596_reg *) dev->base_addr)->ca = 1;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित ENABLE_BVME6000_NET
	अगर (MACH_IS_BVME6000) अणु
		अस्थिर u32 i;

		i = *(अस्थिर u32 *) (dev->base_addr);
	पूर्ण
#पूर्ण_अगर
पूर्ण


अटल अंतरभूत व्योम MPU_PORT(काष्ठा net_device *dev, पूर्णांक c, अस्थिर व्योम *x)
अणु
#अगर_घोषित ENABLE_MVME16x_NET
	अगर (MACH_IS_MVME16x) अणु
		काष्ठा i596_reg *p = (काष्ठा i596_reg *) (dev->base_addr);
		p->porthi = ((c) | (u32) (x)) & 0xffff;
		p->portlo = ((c) | (u32) (x)) >> 16;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित ENABLE_BVME6000_NET
	अगर (MACH_IS_BVME6000) अणु
		u32 v = (u32) (c) | (u32) (x);
		v = ((u32) (v) << 16) | ((u32) (v) >> 16);
		*(अस्थिर u32 *) dev->base_addr = v;
		udelay(1);
		*(अस्थिर u32 *) dev->base_addr = v;
	पूर्ण
#पूर्ण_अगर
पूर्ण


अटल अंतरभूत पूर्णांक रुको_istat(काष्ठा net_device *dev, काष्ठा i596_निजी *lp, पूर्णांक delcnt, अक्षर *str)
अणु
	जबतक (--delcnt && lp->iscp.stat)
		udelay(10);
	अगर (!delcnt) अणु
		prपूर्णांकk(KERN_ERR "%s: %s, status %4.4x, cmd %4.4x.\n",
		     dev->name, str, lp->scb.status, lp->scb.command);
		वापस -1;
	पूर्ण
	अन्यथा
		वापस 0;
पूर्ण


अटल अंतरभूत पूर्णांक रुको_cmd(काष्ठा net_device *dev, काष्ठा i596_निजी *lp, पूर्णांक delcnt, अक्षर *str)
अणु
	जबतक (--delcnt && lp->scb.command)
		udelay(10);
	अगर (!delcnt) अणु
		prपूर्णांकk(KERN_ERR "%s: %s, status %4.4x, cmd %4.4x.\n",
		     dev->name, str, lp->scb.status, lp->scb.command);
		वापस -1;
	पूर्ण
	अन्यथा
		वापस 0;
पूर्ण


अटल अंतरभूत पूर्णांक रुको_cfg(काष्ठा net_device *dev, काष्ठा i596_cmd *cmd, पूर्णांक delcnt, अक्षर *str)
अणु
	अस्थिर काष्ठा i596_cmd *c = cmd;

	जबतक (--delcnt && c->command)
		udelay(10);
	अगर (!delcnt) अणु
		prपूर्णांकk(KERN_ERR "%s: %s.\n", dev->name, str);
		वापस -1;
	पूर्ण
	अन्यथा
		वापस 0;
पूर्ण


अटल व्योम i596_display_data(काष्ठा net_device *dev)
अणु
	काष्ठा i596_निजी *lp = dev->ml_priv;
	काष्ठा i596_cmd *cmd;
	काष्ठा i596_rfd *rfd;
	काष्ठा i596_rbd *rbd;

	prपूर्णांकk(KERN_ERR "lp and scp at %p, .sysbus = %08lx, .iscp = %p\n",
	       &lp->scp, lp->scp.sysbus, lp->scp.iscp);
	prपूर्णांकk(KERN_ERR "iscp at %p, iscp.stat = %08lx, .scb = %p\n",
	       &lp->iscp, lp->iscp.stat, lp->iscp.scb);
	prपूर्णांकk(KERN_ERR "scb at %p, scb.status = %04x, .command = %04x,"
		" .cmd = %p, .rfd = %p\n",
	       &lp->scb, lp->scb.status, lp->scb.command,
		lp->scb.cmd, lp->scb.rfd);
	prपूर्णांकk(KERN_ERR "   errors: crc %lx, align %lx, resource %lx,"
               " over %lx, rcvdt %lx, short %lx\n",
		lp->scb.crc_err, lp->scb.align_err, lp->scb.resource_err,
		lp->scb.over_err, lp->scb.rcvdt_err, lp->scb.लघु_err);
	cmd = lp->cmd_head;
	जबतक (cmd != I596_शून्य) अणु
		prपूर्णांकk(KERN_ERR "cmd at %p, .status = %04x, .command = %04x, .b_next = %p\n",
		  cmd, cmd->status, cmd->command, cmd->b_next);
		cmd = cmd->v_next;
	पूर्ण
	rfd = lp->rfd_head;
	prपूर्णांकk(KERN_ERR "rfd_head = %p\n", rfd);
	करो अणु
		prपूर्णांकk(KERN_ERR "   %p .stat %04x, .cmd %04x, b_next %p, rbd %p,"
                        " count %04x\n",
			rfd, rfd->stat, rfd->cmd, rfd->b_next, rfd->rbd,
			rfd->count);
		rfd = rfd->v_next;
	पूर्ण जबतक (rfd != lp->rfd_head);
	rbd = lp->rbd_head;
	prपूर्णांकk(KERN_ERR "rbd_head = %p\n", rbd);
	करो अणु
		prपूर्णांकk(KERN_ERR "   %p .count %04x, b_next %p, b_data %p, size %04x\n",
			rbd, rbd->count, rbd->b_next, rbd->b_data, rbd->size);
		rbd = rbd->v_next;
	पूर्ण जबतक (rbd != lp->rbd_head);
पूर्ण


#अगर defined(ENABLE_MVME16x_NET) || defined(ENABLE_BVME6000_NET)
अटल irqवापस_t i596_error(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
#अगर_घोषित ENABLE_MVME16x_NET
	अगर (MACH_IS_MVME16x) अणु
		अस्थिर अचिन्हित अक्षर *pcc2 = (अचिन्हित अक्षर *) 0xfff42000;

		pcc2[0x28] = 1;
		pcc2[0x2b] = 0x1d;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित ENABLE_BVME6000_NET
	अगर (MACH_IS_BVME6000) अणु
		अस्थिर अचिन्हित अक्षर *ethirq = (अचिन्हित अक्षर *) BVME_ETHIRQ_REG;

		*ethirq = 1;
		*ethirq = 3;
	पूर्ण
#पूर्ण_अगर
	prपूर्णांकk(KERN_ERR "%s: Error interrupt\n", dev->name);
	i596_display_data(dev);
	वापस IRQ_HANDLED;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम हटाओ_rx_bufs(काष्ठा net_device *dev)
अणु
	काष्ठा i596_निजी *lp = dev->ml_priv;
	काष्ठा i596_rbd *rbd;
	पूर्णांक i;

	क्रम (i = 0, rbd = lp->rbds; i < rx_ring_size; i++, rbd++) अणु
		अगर (rbd->skb == शून्य)
			अवरोध;
		dev_kमुक्त_skb(rbd->skb);
		rbd->skb = शून्य;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक init_rx_bufs(काष्ठा net_device *dev)
अणु
	काष्ठा i596_निजी *lp = dev->ml_priv;
	पूर्णांक i;
	काष्ठा i596_rfd *rfd;
	काष्ठा i596_rbd *rbd;

	/* First build the Receive Buffer Descriptor List */

	क्रम (i = 0, rbd = lp->rbds; i < rx_ring_size; i++, rbd++) अणु
		काष्ठा sk_buff *skb = netdev_alloc_skb(dev, PKT_BUF_SZ);

		अगर (skb == शून्य) अणु
			हटाओ_rx_bufs(dev);
			वापस -ENOMEM;
		पूर्ण

		rbd->v_next = rbd+1;
		rbd->b_next = WSWAPrbd(virt_to_bus(rbd+1));
		rbd->b_addr = WSWAPrbd(virt_to_bus(rbd));
		rbd->skb = skb;
		rbd->v_data = skb->data;
		rbd->b_data = WSWAPअक्षर(virt_to_bus(skb->data));
		rbd->size = PKT_BUF_SZ;
#अगर_घोषित __mc68000__
		cache_clear(virt_to_phys(skb->data), PKT_BUF_SZ);
#पूर्ण_अगर
	पूर्ण
	lp->rbd_head = lp->rbds;
	rbd = lp->rbds + rx_ring_size - 1;
	rbd->v_next = lp->rbds;
	rbd->b_next = WSWAPrbd(virt_to_bus(lp->rbds));

	/* Now build the Receive Frame Descriptor List */

	क्रम (i = 0, rfd = lp->rfds; i < rx_ring_size; i++, rfd++) अणु
		rfd->rbd = I596_शून्य;
		rfd->v_next = rfd+1;
		rfd->v_prev = rfd-1;
		rfd->b_next = WSWAPrfd(virt_to_bus(rfd+1));
		rfd->cmd = CMD_FLEX;
	पूर्ण
	lp->rfd_head = lp->rfds;
	lp->scb.rfd = WSWAPrfd(virt_to_bus(lp->rfds));
	rfd = lp->rfds;
	rfd->rbd = lp->rbd_head;
	rfd->v_prev = lp->rfds + rx_ring_size - 1;
	rfd = lp->rfds + rx_ring_size - 1;
	rfd->v_next = lp->rfds;
	rfd->b_next = WSWAPrfd(virt_to_bus(lp->rfds));
	rfd->cmd = CMD_EOL|CMD_FLEX;

	वापस 0;
पूर्ण


अटल व्योम rebuild_rx_bufs(काष्ठा net_device *dev)
अणु
	काष्ठा i596_निजी *lp = dev->ml_priv;
	पूर्णांक i;

	/* Ensure rx frame/buffer descriptors are tidy */

	क्रम (i = 0; i < rx_ring_size; i++) अणु
		lp->rfds[i].rbd = I596_शून्य;
		lp->rfds[i].cmd = CMD_FLEX;
	पूर्ण
	lp->rfds[rx_ring_size-1].cmd = CMD_EOL|CMD_FLEX;
	lp->rfd_head = lp->rfds;
	lp->scb.rfd = WSWAPrfd(virt_to_bus(lp->rfds));
	lp->rbd_head = lp->rbds;
	lp->rfds[0].rbd = WSWAPrbd(virt_to_bus(lp->rbds));
पूर्ण


अटल पूर्णांक init_i596_mem(काष्ठा net_device *dev)
अणु
	काष्ठा i596_निजी *lp = dev->ml_priv;
	अचिन्हित दीर्घ flags;

	MPU_PORT(dev, PORT_RESET, शून्य);

	udelay(100);		/* Wait 100us - seems to help */

#अगर defined(ENABLE_MVME16x_NET) || defined(ENABLE_BVME6000_NET)
#अगर_घोषित ENABLE_MVME16x_NET
	अगर (MACH_IS_MVME16x) अणु
		अस्थिर अचिन्हित अक्षर *pcc2 = (अचिन्हित अक्षर *) 0xfff42000;

		/* Disable all पूर्णांकs क्रम now */
		pcc2[0x28] = 1;
		pcc2[0x2a] = 0x48;
		/* Following disables snooping.  Snooping is not required
		 * as we make appropriate use of non-cached pages क्रम
		 * shared data, and cache_push/cache_clear.
		 */
		pcc2[0x2b] = 0x08;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित ENABLE_BVME6000_NET
	अगर (MACH_IS_BVME6000) अणु
		अस्थिर अचिन्हित अक्षर *ethirq = (अचिन्हित अक्षर *) BVME_ETHIRQ_REG;

		*ethirq = 1;
	पूर्ण
#पूर्ण_अगर

	/* change the scp address */

	MPU_PORT(dev, PORT_ALTSCP, (व्योम *)virt_to_bus((व्योम *)&lp->scp));

#पूर्ण_अगर

	lp->last_cmd = jअगरfies;

#अगर_घोषित ENABLE_MVME16x_NET
	अगर (MACH_IS_MVME16x)
		lp->scp.sysbus = 0x00000054;
#पूर्ण_अगर
#अगर_घोषित ENABLE_BVME6000_NET
	अगर (MACH_IS_BVME6000)
		lp->scp.sysbus = 0x0000004c;
#पूर्ण_अगर

	lp->scp.iscp = WSWAPiscp(virt_to_bus((व्योम *)&lp->iscp));
	lp->iscp.scb = WSWAPscb(virt_to_bus((व्योम *)&lp->scb));
	lp->iscp.stat = ISCP_BUSY;
	lp->cmd_backlog = 0;

	lp->cmd_head = lp->scb.cmd = I596_शून्य;

#अगर_घोषित ENABLE_BVME6000_NET
	अगर (MACH_IS_BVME6000) अणु
		lp->scb.t_on  = 7 * 25;
		lp->scb.t_off = 1 * 25;
	पूर्ण
#पूर्ण_अगर

	DEB(DEB_INIT,prपूर्णांकk(KERN_DEBUG "%s: starting i82596.\n", dev->name));

	CA(dev);

	अगर (रुको_istat(dev,lp,1000,"initialization timed out"))
		जाओ failed;
	DEB(DEB_INIT,prपूर्णांकk(KERN_DEBUG "%s: i82596 initialization successful\n", dev->name));

	/* Ensure rx frame/buffer descriptors are tidy */
	rebuild_rx_bufs(dev);
	lp->scb.command = 0;

#अगर_घोषित ENABLE_MVME16x_NET
	अगर (MACH_IS_MVME16x) अणु
		अस्थिर अचिन्हित अक्षर *pcc2 = (अचिन्हित अक्षर *) 0xfff42000;

		/* Enable पूर्णांकs, etc. now */
		pcc2[0x2a] = 0x55;	/* Edge sensitive */
		pcc2[0x2b] = 0x15;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित ENABLE_BVME6000_NET
	अगर (MACH_IS_BVME6000) अणु
		अस्थिर अचिन्हित अक्षर *ethirq = (अचिन्हित अक्षर *) BVME_ETHIRQ_REG;

		*ethirq = 3;
	पूर्ण
#पूर्ण_अगर


	DEB(DEB_INIT,prपूर्णांकk(KERN_DEBUG "%s: queuing CmdConfigure\n", dev->name));
	स_नकल(lp->cf_cmd.i596_config, init_setup, 14);
	lp->cf_cmd.cmd.command = CmdConfigure;
	i596_add_cmd(dev, &lp->cf_cmd.cmd);

	DEB(DEB_INIT,prपूर्णांकk(KERN_DEBUG "%s: queuing CmdSASetup\n", dev->name));
	स_नकल(lp->sa_cmd.eth_addr, dev->dev_addr, ETH_ALEN);
	lp->sa_cmd.cmd.command = CmdSASetup;
	i596_add_cmd(dev, &lp->sa_cmd.cmd);

	DEB(DEB_INIT,prपूर्णांकk(KERN_DEBUG "%s: queuing CmdTDR\n", dev->name));
	lp->tdr_cmd.cmd.command = CmdTDR;
	i596_add_cmd(dev, &lp->tdr_cmd.cmd);

	spin_lock_irqsave (&lp->lock, flags);

	अगर (रुको_cmd(dev,lp,1000,"timed out waiting to issue RX_START")) अणु
		spin_unlock_irqrestore (&lp->lock, flags);
		जाओ failed;
	पूर्ण
	DEB(DEB_INIT,prपूर्णांकk(KERN_DEBUG "%s: Issuing RX_START\n", dev->name));
	lp->scb.command = RX_START;
	CA(dev);

	spin_unlock_irqrestore (&lp->lock, flags);

	अगर (रुको_cmd(dev,lp,1000,"RX_START not processed"))
		जाओ failed;
	DEB(DEB_INIT,prपूर्णांकk(KERN_DEBUG "%s: Receive unit started OK\n", dev->name));
	वापस 0;

failed:
	prपूर्णांकk(KERN_CRIT "%s: Failed to initialise 82596\n", dev->name);
	MPU_PORT(dev, PORT_RESET, शून्य);
	वापस -1;
पूर्ण

अटल अंतरभूत पूर्णांक i596_rx(काष्ठा net_device *dev)
अणु
	काष्ठा i596_निजी *lp = dev->ml_priv;
	काष्ठा i596_rfd *rfd;
	काष्ठा i596_rbd *rbd;
	पूर्णांक frames = 0;

	DEB(DEB_RXFRAME,prपूर्णांकk(KERN_DEBUG "i596_rx(), rfd_head %p, rbd_head %p\n",
			lp->rfd_head, lp->rbd_head));

	rfd = lp->rfd_head;		/* Ref next frame to check */

	जबतक ((rfd->stat) & STAT_C) अणु	/* Loop जबतक complete frames */
		अगर (rfd->rbd == I596_शून्य)
			rbd = I596_शून्य;
		अन्यथा अगर (rfd->rbd == lp->rbd_head->b_addr)
			rbd = lp->rbd_head;
		अन्यथा अणु
			prपूर्णांकk(KERN_CRIT "%s: rbd chain broken!\n", dev->name);
			/* XXX Now what? */
			rbd = I596_शून्य;
		पूर्ण
		DEB(DEB_RXFRAME, prपूर्णांकk(KERN_DEBUG "  rfd %p, rfd.rbd %p, rfd.stat %04x\n",
			rfd, rfd->rbd, rfd->stat));

		अगर (rbd != I596_शून्य && ((rfd->stat) & STAT_OK)) अणु
			/* a good frame */
			पूर्णांक pkt_len = rbd->count & 0x3fff;
			काष्ठा sk_buff *skb = rbd->skb;
			पूर्णांक rx_in_place = 0;

			DEB(DEB_RXADDR,prपूर्णांक_eth(rbd->v_data, "received"));
			frames++;

			/* Check अगर the packet is दीर्घ enough to just accept
			 * without copying to a properly sized skbuff.
			 */

			अगर (pkt_len > rx_copyअवरोध) अणु
				काष्ठा sk_buff *newskb;

				/* Get fresh skbuff to replace filled one. */
				newskb = netdev_alloc_skb(dev, PKT_BUF_SZ);
				अगर (newskb == शून्य) अणु
					skb = शून्य;	/* drop pkt */
					जाओ memory_squeeze;
				पूर्ण
				/* Pass up the skb alपढ़ोy on the Rx ring. */
				skb_put(skb, pkt_len);
				rx_in_place = 1;
				rbd->skb = newskb;
				rbd->v_data = newskb->data;
				rbd->b_data = WSWAPअक्षर(virt_to_bus(newskb->data));
#अगर_घोषित __mc68000__
				cache_clear(virt_to_phys(newskb->data), PKT_BUF_SZ);
#पूर्ण_अगर
			पूर्ण अन्यथा अणु
				skb = netdev_alloc_skb(dev, pkt_len + 2);
			पूर्ण
memory_squeeze:
			अगर (skb == शून्य) अणु
				/* XXX tulip.c can defer packets here!! */
				dev->stats.rx_dropped++;
			पूर्ण अन्यथा अणु
				अगर (!rx_in_place) अणु
					/* 16 byte align the data fields */
					skb_reserve(skb, 2);
					skb_put_data(skb, rbd->v_data,
						     pkt_len);
				पूर्ण
				skb->protocol=eth_type_trans(skb,dev);
				skb->len = pkt_len;
#अगर_घोषित __mc68000__
				cache_clear(virt_to_phys(rbd->skb->data),
						pkt_len);
#पूर्ण_अगर
				netअगर_rx(skb);
				dev->stats.rx_packets++;
				dev->stats.rx_bytes+=pkt_len;
			पूर्ण
		पूर्ण
		अन्यथा अणु
			DEB(DEB_ERRORS, prपूर्णांकk(KERN_DEBUG "%s: Error, rfd.stat = 0x%04x\n",
					dev->name, rfd->stat));
			dev->stats.rx_errors++;
			अगर ((rfd->stat) & 0x0001)
				dev->stats.collisions++;
			अगर ((rfd->stat) & 0x0080)
				dev->stats.rx_length_errors++;
			अगर ((rfd->stat) & 0x0100)
				dev->stats.rx_over_errors++;
			अगर ((rfd->stat) & 0x0200)
				dev->stats.rx_fअगरo_errors++;
			अगर ((rfd->stat) & 0x0400)
				dev->stats.rx_frame_errors++;
			अगर ((rfd->stat) & 0x0800)
				dev->stats.rx_crc_errors++;
			अगर ((rfd->stat) & 0x1000)
				dev->stats.rx_length_errors++;
		पूर्ण

		/* Clear the buffer descriptor count and खातापूर्ण + F flags */

		अगर (rbd != I596_शून्य && (rbd->count & 0x4000)) अणु
			rbd->count = 0;
			lp->rbd_head = rbd->v_next;
		पूर्ण

		/* Tidy the frame descriptor, marking it as end of list */

		rfd->rbd = I596_शून्य;
		rfd->stat = 0;
		rfd->cmd = CMD_EOL|CMD_FLEX;
		rfd->count = 0;

		/* Remove end-of-list from old end descriptor */

		rfd->v_prev->cmd = CMD_FLEX;

		/* Update record of next frame descriptor to process */

		lp->scb.rfd = rfd->b_next;
		lp->rfd_head = rfd->v_next;
		rfd = lp->rfd_head;
	पूर्ण

	DEB(DEB_RXFRAME,prपूर्णांकk(KERN_DEBUG "frames %d\n", frames));

	वापस 0;
पूर्ण


अटल व्योम i596_cleanup_cmd(काष्ठा net_device *dev, काष्ठा i596_निजी *lp)
अणु
	काष्ठा i596_cmd *ptr;

	जबतक (lp->cmd_head != I596_शून्य) अणु
		ptr = lp->cmd_head;
		lp->cmd_head = ptr->v_next;
		lp->cmd_backlog--;

		चयन ((ptr->command) & 0x7) अणु
		हाल CmdTx:
			अणु
				काष्ठा tx_cmd *tx_cmd = (काष्ठा tx_cmd *) ptr;
				काष्ठा sk_buff *skb = tx_cmd->skb;

				dev_kमुक्त_skb(skb);

				dev->stats.tx_errors++;
				dev->stats.tx_पातed_errors++;

				ptr->v_next = ptr->b_next = I596_शून्य;
				tx_cmd->cmd.command = 0;  /* Mark as मुक्त */
				अवरोध;
			पूर्ण
		शेष:
			ptr->v_next = ptr->b_next = I596_शून्य;
		पूर्ण
	पूर्ण

	रुको_cmd(dev,lp,100,"i596_cleanup_cmd timed out");
	lp->scb.cmd = I596_शून्य;
पूर्ण

अटल व्योम i596_reset(काष्ठा net_device *dev, काष्ठा i596_निजी *lp,
			पूर्णांक ioaddr)
अणु
	अचिन्हित दीर्घ flags;

	DEB(DEB_RESET,prपूर्णांकk(KERN_DEBUG "i596_reset\n"));

	spin_lock_irqsave (&lp->lock, flags);

	रुको_cmd(dev,lp,100,"i596_reset timed out");

	netअगर_stop_queue(dev);

	lp->scb.command = CUC_ABORT | RX_ABORT;
	CA(dev);

	/* रुको क्रम shutकरोwn */
	रुको_cmd(dev,lp,1000,"i596_reset 2 timed out");
	spin_unlock_irqrestore (&lp->lock, flags);

	i596_cleanup_cmd(dev,lp);
	i596_rx(dev);

	netअगर_start_queue(dev);
	init_i596_mem(dev);
पूर्ण

अटल व्योम i596_add_cmd(काष्ठा net_device *dev, काष्ठा i596_cmd *cmd)
अणु
	काष्ठा i596_निजी *lp = dev->ml_priv;
	पूर्णांक ioaddr = dev->base_addr;
	अचिन्हित दीर्घ flags;

	DEB(DEB_ADDCMD,prपूर्णांकk(KERN_DEBUG "i596_add_cmd\n"));

	cmd->status = 0;
	cmd->command |= (CMD_EOL | CMD_INTR);
	cmd->v_next = cmd->b_next = I596_शून्य;

	spin_lock_irqsave (&lp->lock, flags);

	अगर (lp->cmd_head != I596_शून्य) अणु
		lp->cmd_tail->v_next = cmd;
		lp->cmd_tail->b_next = WSWAPcmd(virt_to_bus(&cmd->status));
	पूर्ण अन्यथा अणु
		lp->cmd_head = cmd;
		रुको_cmd(dev,lp,100,"i596_add_cmd timed out");
		lp->scb.cmd = WSWAPcmd(virt_to_bus(&cmd->status));
		lp->scb.command = CUC_START;
		CA(dev);
	पूर्ण
	lp->cmd_tail = cmd;
	lp->cmd_backlog++;

	spin_unlock_irqrestore (&lp->lock, flags);

	अगर (lp->cmd_backlog > max_cmd_backlog) अणु
		अचिन्हित दीर्घ tickssofar = jअगरfies - lp->last_cmd;

		अगर (tickssofar < ticks_limit)
			वापस;

		prपूर्णांकk(KERN_NOTICE "%s: command unit timed out, status resetting.\n", dev->name);

		i596_reset(dev, lp, ioaddr);
	पूर्ण
पूर्ण

अटल पूर्णांक i596_खोलो(काष्ठा net_device *dev)
अणु
	पूर्णांक res = 0;

	DEB(DEB_OPEN,prपूर्णांकk(KERN_DEBUG "%s: i596_open() irq %d.\n", dev->name, dev->irq));

	अगर (request_irq(dev->irq, i596_पूर्णांकerrupt, 0, "i82596", dev)) अणु
		prपूर्णांकk(KERN_ERR "%s: IRQ %d not free\n", dev->name, dev->irq);
		वापस -EAGAIN;
	पूर्ण
#अगर_घोषित ENABLE_MVME16x_NET
	अगर (MACH_IS_MVME16x) अणु
		अगर (request_irq(0x56, i596_error, 0, "i82596_error", dev)) अणु
			res = -EAGAIN;
			जाओ err_irq_dev;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	res = init_rx_bufs(dev);
	अगर (res)
		जाओ err_irq_56;

	netअगर_start_queue(dev);

	अगर (init_i596_mem(dev)) अणु
		res = -EAGAIN;
		जाओ err_queue;
	पूर्ण

	वापस 0;

err_queue:
	netअगर_stop_queue(dev);
	हटाओ_rx_bufs(dev);
err_irq_56:
#अगर_घोषित ENABLE_MVME16x_NET
	मुक्त_irq(0x56, dev);
err_irq_dev:
#पूर्ण_अगर
	मुक्त_irq(dev->irq, dev);

	वापस res;
पूर्ण

अटल व्योम i596_tx_समयout (काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा i596_निजी *lp = dev->ml_priv;
	पूर्णांक ioaddr = dev->base_addr;

	/* Transmitter समयout, serious problems. */
	DEB(DEB_ERRORS,prपूर्णांकk(KERN_ERR "%s: transmit timed out, status resetting.\n",
			dev->name));

	dev->stats.tx_errors++;

	/* Try to restart the adaptor */
	अगर (lp->last_restart == dev->stats.tx_packets) अणु
		DEB(DEB_ERRORS,prपूर्णांकk(KERN_ERR "Resetting board.\n"));
		/* Shutकरोwn and restart */
		i596_reset (dev, lp, ioaddr);
	पूर्ण अन्यथा अणु
		/* Issue a channel attention संकेत */
		DEB(DEB_ERRORS,prपूर्णांकk(KERN_ERR "Kicking board.\n"));
		lp->scb.command = CUC_START | RX_START;
		CA (dev);
		lp->last_restart = dev->stats.tx_packets;
	पूर्ण

	netअगर_trans_update(dev); /* prevent tx समयout */
	netअगर_wake_queue (dev);
पूर्ण

अटल netdev_tx_t i596_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा i596_निजी *lp = dev->ml_priv;
	काष्ठा tx_cmd *tx_cmd;
	काष्ठा i596_tbd *tbd;
	लघु length = skb->len;

	DEB(DEB_STARTTX,prपूर्णांकk(KERN_DEBUG "%s: i596_start_xmit(%x,%p) called\n",
				dev->name, skb->len, skb->data));

	अगर (skb->len < ETH_ZLEN) अणु
		अगर (skb_padto(skb, ETH_ZLEN))
			वापस NETDEV_TX_OK;
		length = ETH_ZLEN;
	पूर्ण
	netअगर_stop_queue(dev);

	tx_cmd = lp->tx_cmds + lp->next_tx_cmd;
	tbd = lp->tbds + lp->next_tx_cmd;

	अगर (tx_cmd->cmd.command) अणु
		prपूर्णांकk(KERN_NOTICE "%s: xmit ring full, dropping packet.\n",
				dev->name);
		dev->stats.tx_dropped++;

		dev_kमुक्त_skb(skb);
	पूर्ण अन्यथा अणु
		अगर (++lp->next_tx_cmd == TX_RING_SIZE)
			lp->next_tx_cmd = 0;
		tx_cmd->tbd = WSWAPtbd(virt_to_bus(tbd));
		tbd->next = I596_शून्य;

		tx_cmd->cmd.command = CMD_FLEX | CmdTx;
		tx_cmd->skb = skb;

		tx_cmd->pad = 0;
		tx_cmd->size = 0;
		tbd->pad = 0;
		tbd->size = खातापूर्ण | length;

		tbd->data = WSWAPअक्षर(virt_to_bus(skb->data));

#अगर_घोषित __mc68000__
		cache_push(virt_to_phys(skb->data), length);
#पूर्ण_अगर
		DEB(DEB_TXADDR,prपूर्णांक_eth(skb->data, "tx-queued"));
		i596_add_cmd(dev, &tx_cmd->cmd);

		dev->stats.tx_packets++;
		dev->stats.tx_bytes += length;
	पूर्ण

	netअगर_start_queue(dev);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम prपूर्णांक_eth(अचिन्हित अक्षर *add, अक्षर *str)
अणु
	prपूर्णांकk(KERN_DEBUG "i596 0x%p, %pM --> %pM %02X%02X, %s\n",
	       add, add + 6, add, add[12], add[13], str);
पूर्ण

अटल पूर्णांक io = 0x300;
अटल पूर्णांक irq = 10;

अटल स्थिर काष्ठा net_device_ops i596_netdev_ops = अणु
	.nकरो_खोलो 		= i596_खोलो,
	.nकरो_stop		= i596_बंद,
	.nकरो_start_xmit		= i596_start_xmit,
	.nकरो_set_rx_mode	= set_multicast_list,
	.nकरो_tx_समयout		= i596_tx_समयout,
	.nकरो_set_mac_address 	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

काष्ठा net_device * __init i82596_probe(पूर्णांक unit)
अणु
	काष्ठा net_device *dev;
	पूर्णांक i;
	काष्ठा i596_निजी *lp;
	अक्षर eth_addr[8];
	अटल पूर्णांक probed;
	पूर्णांक err;

	अगर (probed)
		वापस ERR_PTR(-ENODEV);
	probed++;

	dev = alloc_etherdev(0);
	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);

	अगर (unit >= 0) अणु
		प्र_लिखो(dev->name, "eth%d", unit);
		netdev_boot_setup_check(dev);
	पूर्ण अन्यथा अणु
		dev->base_addr = io;
		dev->irq = irq;
	पूर्ण

#अगर_घोषित ENABLE_MVME16x_NET
	अगर (MACH_IS_MVME16x) अणु
		अगर (mvme16x_config & MVME16x_CONFIG_NO_ETHERNET) अणु
			prपूर्णांकk(KERN_NOTICE "Ethernet probe disabled - chip not present\n");
			err = -ENODEV;
			जाओ out;
		पूर्ण
		स_नकल(eth_addr, (व्योम *) 0xfffc1f2c, ETH_ALEN);	/* YUCK! Get addr from NOVRAM */
		dev->base_addr = MVME_I596_BASE;
		dev->irq = (अचिन्हित) MVME16x_IRQ_I596;
		जाओ found;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित ENABLE_BVME6000_NET
	अगर (MACH_IS_BVME6000) अणु
		अस्थिर अचिन्हित अक्षर *rtc = (अचिन्हित अक्षर *) BVME_RTC_BASE;
		अचिन्हित अक्षर msr = rtc[3];
		पूर्णांक i;

		rtc[3] |= 0x80;
		क्रम (i = 0; i < 6; i++)
			eth_addr[i] = rtc[i * 4 + 7];	/* Stored in RTC RAM at offset 1 */
		rtc[3] = msr;
		dev->base_addr = BVME_I596_BASE;
		dev->irq = (अचिन्हित) BVME_IRQ_I596;
		जाओ found;
	पूर्ण
#पूर्ण_अगर
	err = -ENODEV;
	जाओ out;

found:
	dev->mem_start = (पूर्णांक)__get_मुक्त_pages(GFP_ATOMIC, 0);
	अगर (!dev->mem_start) अणु
		err = -ENOMEM;
		जाओ out1;
	पूर्ण

	DEB(DEB_PROBE,prपूर्णांकk(KERN_INFO "%s: 82596 at %#3lx,", dev->name, dev->base_addr));

	क्रम (i = 0; i < 6; i++)
		DEB(DEB_PROBE,prपूर्णांकk(" %2.2X", dev->dev_addr[i] = eth_addr[i]));

	DEB(DEB_PROBE,prपूर्णांकk(" IRQ %d.\n", dev->irq));

	DEB(DEB_PROBE,prपूर्णांकk(KERN_INFO "%s", version));

	/* The 82596-specअगरic entries in the device काष्ठाure. */
	dev->netdev_ops = &i596_netdev_ops;
	dev->watchकरोg_समयo = TX_TIMEOUT;

	dev->ml_priv = (व्योम *)(dev->mem_start);

	lp = dev->ml_priv;
	DEB(DEB_INIT,prपूर्णांकk(KERN_DEBUG "%s: lp at 0x%08lx (%zd bytes), "
			"lp->scb at 0x%08lx\n",
			dev->name, (अचिन्हित दीर्घ)lp,
			माप(काष्ठा i596_निजी), (अचिन्हित दीर्घ)&lp->scb));
	स_रखो((व्योम *) lp, 0, माप(काष्ठा i596_निजी));

#अगर_घोषित __mc68000__
	cache_push(virt_to_phys((व्योम *)(dev->mem_start)), 4096);
	cache_clear(virt_to_phys((व्योम *)(dev->mem_start)), 4096);
	kernel_set_cachemode((व्योम *)(dev->mem_start), 4096, IOMAP_NOCACHE_SER);
#पूर्ण_अगर
	lp->scb.command = 0;
	lp->scb.cmd = I596_शून्य;
	lp->scb.rfd = I596_शून्य;
	spin_lock_init(&lp->lock);

	err = रेजिस्टर_netdev(dev);
	अगर (err)
		जाओ out2;
	वापस dev;
out2:
#अगर_घोषित __mc68000__
	/* XXX This assumes शेष cache mode to be IOMAP_FULL_CACHING,
	 * XXX which may be invalid (CONFIG_060_WRITETHROUGH)
	 */
	kernel_set_cachemode((व्योम *)(dev->mem_start), 4096,
			IOMAP_FULL_CACHING);
#पूर्ण_अगर
	मुक्त_page ((u32)(dev->mem_start));
out1:
out:
	मुक्त_netdev(dev);
	वापस ERR_PTR(err);
पूर्ण

अटल irqवापस_t i596_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा i596_निजी *lp;
	लघु ioaddr;
	अचिन्हित लघु status, ack_cmd = 0;
	पूर्णांक handled = 0;

#अगर_घोषित ENABLE_BVME6000_NET
	अगर (MACH_IS_BVME6000) अणु
		अगर (*(अक्षर *) BVME_LOCAL_IRQ_STAT & BVME_ETHERR) अणु
			i596_error(irq, dev_id);
			वापस IRQ_HANDLED;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	अगर (dev == शून्य) अणु
		prपूर्णांकk(KERN_ERR "i596_interrupt(): irq %d for unknown device.\n", irq);
		वापस IRQ_NONE;
	पूर्ण

	ioaddr = dev->base_addr;
	lp = dev->ml_priv;

	spin_lock (&lp->lock);

	रुको_cmd(dev,lp,100,"i596 interrupt, timeout");
	status = lp->scb.status;

	DEB(DEB_INTS,prपूर्णांकk(KERN_DEBUG "%s: i596 interrupt, IRQ %d, status %4.4x.\n",
			dev->name, irq, status));

	ack_cmd = status & 0xf000;

	अगर ((status & 0x8000) || (status & 0x2000)) अणु
		काष्ठा i596_cmd *ptr;

		handled = 1;
		अगर ((status & 0x8000))
			DEB(DEB_INTS,prपूर्णांकk(KERN_DEBUG "%s: i596 interrupt completed command.\n", dev->name));
		अगर ((status & 0x2000))
			DEB(DEB_INTS,prपूर्णांकk(KERN_DEBUG "%s: i596 interrupt command unit inactive %x.\n", dev->name, status & 0x0700));

		जबतक ((lp->cmd_head != I596_शून्य) && (lp->cmd_head->status & STAT_C)) अणु
			ptr = lp->cmd_head;

			DEB(DEB_STATUS,prपूर्णांकk(KERN_DEBUG "cmd_head->status = %04x, ->command = %04x\n",
				       lp->cmd_head->status, lp->cmd_head->command));
			lp->cmd_head = ptr->v_next;
			lp->cmd_backlog--;

			चयन ((ptr->command) & 0x7) अणु
			हाल CmdTx:
			    अणु
				काष्ठा tx_cmd *tx_cmd = (काष्ठा tx_cmd *) ptr;
				काष्ठा sk_buff *skb = tx_cmd->skb;

				अगर ((ptr->status) & STAT_OK) अणु
					DEB(DEB_TXADDR,prपूर्णांक_eth(skb->data, "tx-done"));
				पूर्ण अन्यथा अणु
					dev->stats.tx_errors++;
					अगर ((ptr->status) & 0x0020)
						dev->stats.collisions++;
					अगर (!((ptr->status) & 0x0040))
						dev->stats.tx_heartbeat_errors++;
					अगर ((ptr->status) & 0x0400)
						dev->stats.tx_carrier_errors++;
					अगर ((ptr->status) & 0x0800)
						dev->stats.collisions++;
					अगर ((ptr->status) & 0x1000)
						dev->stats.tx_पातed_errors++;
				पूर्ण

				dev_consume_skb_irq(skb);

				tx_cmd->cmd.command = 0; /* Mark मुक्त */
				अवरोध;
			    पूर्ण
			हाल CmdTDR:
			    अणु
				अचिन्हित लघु status = ((काष्ठा tdr_cmd *)ptr)->status;

				अगर (status & 0x8000) अणु
					DEB(DEB_TDR,prपूर्णांकk(KERN_INFO "%s: link ok.\n", dev->name));
				पूर्ण अन्यथा अणु
					अगर (status & 0x4000)
						prपूर्णांकk(KERN_ERR "%s: Transceiver problem.\n", dev->name);
					अगर (status & 0x2000)
						prपूर्णांकk(KERN_ERR "%s: Termination problem.\n", dev->name);
					अगर (status & 0x1000)
						prपूर्णांकk(KERN_ERR "%s: Short circuit.\n", dev->name);

					DEB(DEB_TDR,prपूर्णांकk(KERN_INFO "%s: Time %d.\n", dev->name, status & 0x07ff));
				पूर्ण
				अवरोध;
			    पूर्ण
			हाल CmdConfigure:
			हाल CmdMulticastList:
				/* Zap command so set_multicast_list() knows it is मुक्त */
				ptr->command = 0;
				अवरोध;
			पूर्ण
			ptr->v_next = ptr->b_next = I596_शून्य;
			lp->last_cmd = jअगरfies;
		पूर्ण

		ptr = lp->cmd_head;
		जबतक ((ptr != I596_शून्य) && (ptr != lp->cmd_tail)) अणु
			ptr->command &= 0x1fff;
			ptr = ptr->v_next;
		पूर्ण

		अगर ((lp->cmd_head != I596_शून्य))
			ack_cmd |= CUC_START;
		lp->scb.cmd = WSWAPcmd(virt_to_bus(&lp->cmd_head->status));
	पूर्ण
	अगर ((status & 0x1000) || (status & 0x4000)) अणु
		अगर ((status & 0x4000))
			DEB(DEB_INTS,prपूर्णांकk(KERN_DEBUG "%s: i596 interrupt received a frame.\n", dev->name));
		i596_rx(dev);
		/* Only RX_START अगर stopped - RGH 07-07-96 */
		अगर (status & 0x1000) अणु
			अगर (netअगर_running(dev)) अणु
				DEB(DEB_ERRORS,prपूर्णांकk(KERN_ERR "%s: i596 interrupt receive unit inactive, status 0x%x\n", dev->name, status));
				ack_cmd |= RX_START;
				dev->stats.rx_errors++;
				dev->stats.rx_fअगरo_errors++;
				rebuild_rx_bufs(dev);
			पूर्ण
		पूर्ण
	पूर्ण
	रुको_cmd(dev,lp,100,"i596 interrupt, timeout");
	lp->scb.command = ack_cmd;

#अगर_घोषित ENABLE_MVME16x_NET
	अगर (MACH_IS_MVME16x) अणु
		/* Ack the पूर्णांकerrupt */

		अस्थिर अचिन्हित अक्षर *pcc2 = (अचिन्हित अक्षर *) 0xfff42000;

		pcc2[0x2a] |= 0x08;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित ENABLE_BVME6000_NET
	अगर (MACH_IS_BVME6000) अणु
		अस्थिर अचिन्हित अक्षर *ethirq = (अचिन्हित अक्षर *) BVME_ETHIRQ_REG;

		*ethirq = 1;
		*ethirq = 3;
	पूर्ण
#पूर्ण_अगर
	CA(dev);

	DEB(DEB_INTS,prपूर्णांकk(KERN_DEBUG "%s: exiting interrupt.\n", dev->name));

	spin_unlock (&lp->lock);
	वापस IRQ_RETVAL(handled);
पूर्ण

अटल पूर्णांक i596_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा i596_निजी *lp = dev->ml_priv;
	अचिन्हित दीर्घ flags;

	netअगर_stop_queue(dev);

	DEB(DEB_INIT,prपूर्णांकk(KERN_DEBUG "%s: Shutting down ethercard, status was %4.4x.\n",
		       dev->name, lp->scb.status));

	spin_lock_irqsave(&lp->lock, flags);

	रुको_cmd(dev,lp,100,"close1 timed out");
	lp->scb.command = CUC_ABORT | RX_ABORT;
	CA(dev);

	रुको_cmd(dev,lp,100,"close2 timed out");

	spin_unlock_irqrestore(&lp->lock, flags);
	DEB(DEB_STRUCT,i596_display_data(dev));
	i596_cleanup_cmd(dev,lp);

#अगर_घोषित ENABLE_MVME16x_NET
	अगर (MACH_IS_MVME16x) अणु
		अस्थिर अचिन्हित अक्षर *pcc2 = (अचिन्हित अक्षर *) 0xfff42000;

		/* Disable all पूर्णांकs */
		pcc2[0x28] = 1;
		pcc2[0x2a] = 0x40;
		pcc2[0x2b] = 0x40;	/* Set snooping bits now! */
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित ENABLE_BVME6000_NET
	अगर (MACH_IS_BVME6000) अणु
		अस्थिर अचिन्हित अक्षर *ethirq = (अचिन्हित अक्षर *) BVME_ETHIRQ_REG;

		*ethirq = 1;
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित ENABLE_MVME16x_NET
	मुक्त_irq(0x56, dev);
#पूर्ण_अगर
	मुक्त_irq(dev->irq, dev);
	हटाओ_rx_bufs(dev);

	वापस 0;
पूर्ण

/*
 *    Set or clear the multicast filter क्रम this adaptor.
 */

अटल व्योम set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा i596_निजी *lp = dev->ml_priv;
	पूर्णांक config = 0, cnt;

	DEB(DEB_MULTI,prपूर्णांकk(KERN_DEBUG "%s: set multicast list, %d entries, promisc %s, allmulti %s\n",
		dev->name, netdev_mc_count(dev),
		dev->flags & IFF_PROMISC  ? "ON" : "OFF",
		dev->flags & IFF_ALLMULTI ? "ON" : "OFF"));

	अगर (रुको_cfg(dev, &lp->cf_cmd.cmd, 1000, "config change request timed out"))
		वापस;

	अगर ((dev->flags & IFF_PROMISC) && !(lp->cf_cmd.i596_config[8] & 0x01)) अणु
		lp->cf_cmd.i596_config[8] |= 0x01;
		config = 1;
	पूर्ण
	अगर (!(dev->flags & IFF_PROMISC) && (lp->cf_cmd.i596_config[8] & 0x01)) अणु
		lp->cf_cmd.i596_config[8] &= ~0x01;
		config = 1;
	पूर्ण
	अगर ((dev->flags & IFF_ALLMULTI) && (lp->cf_cmd.i596_config[11] & 0x20)) अणु
		lp->cf_cmd.i596_config[11] &= ~0x20;
		config = 1;
	पूर्ण
	अगर (!(dev->flags & IFF_ALLMULTI) && !(lp->cf_cmd.i596_config[11] & 0x20)) अणु
		lp->cf_cmd.i596_config[11] |= 0x20;
		config = 1;
	पूर्ण
	अगर (config) अणु
		lp->cf_cmd.cmd.command = CmdConfigure;
		i596_add_cmd(dev, &lp->cf_cmd.cmd);
	पूर्ण

	cnt = netdev_mc_count(dev);
	अगर (cnt > MAX_MC_CNT)
	अणु
		cnt = MAX_MC_CNT;
		prपूर्णांकk(KERN_ERR "%s: Only %d multicast addresses supported",
			dev->name, cnt);
	पूर्ण

	अगर (!netdev_mc_empty(dev)) अणु
		काष्ठा netdev_hw_addr *ha;
		अचिन्हित अक्षर *cp;
		काष्ठा mc_cmd *cmd;

		अगर (रुको_cfg(dev, &lp->mc_cmd.cmd, 1000, "multicast list change request timed out"))
			वापस;
		cmd = &lp->mc_cmd;
		cmd->cmd.command = CmdMulticastList;
		cmd->mc_cnt = cnt * ETH_ALEN;
		cp = cmd->mc_addrs;
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			अगर (!cnt--)
				अवरोध;
			स_नकल(cp, ha->addr, ETH_ALEN);
			अगर (i596_debug > 1)
				DEB(DEB_MULTI,prपूर्णांकk(KERN_INFO "%s: Adding address %pM\n",
						dev->name, cp));
			cp += ETH_ALEN;
		पूर्ण
		i596_add_cmd(dev, &cmd->cmd);
	पूर्ण
पूर्ण

#अगर_घोषित MODULE
अटल काष्ठा net_device *dev_82596;

अटल पूर्णांक debug = -1;
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "i82596 debug mask");

पूर्णांक __init init_module(व्योम)
अणु
	अगर (debug >= 0)
		i596_debug = debug;
	dev_82596 = i82596_probe(-1);
	वापस PTR_ERR_OR_ZERO(dev_82596);
पूर्ण

व्योम __निकास cleanup_module(व्योम)
अणु
	unरेजिस्टर_netdev(dev_82596);
#अगर_घोषित __mc68000__
	/* XXX This assumes शेष cache mode to be IOMAP_FULL_CACHING,
	 * XXX which may be invalid (CONFIG_060_WRITETHROUGH)
	 */

	kernel_set_cachemode((व्योम *)(dev_82596->mem_start), 4096,
			IOMAP_FULL_CACHING);
#पूर्ण_अगर
	मुक्त_page ((u32)(dev_82596->mem_start));
	मुक्त_netdev(dev_82596);
पूर्ण

#पूर्ण_अगर				/* MODULE */
