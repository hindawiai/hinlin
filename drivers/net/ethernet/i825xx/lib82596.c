<शैली गुरु>
/* lasi_82596.c -- driver क्रम the पूर्णांकel 82596 ethernet controller, as
   munged पूर्णांकo HPPA boxen .

   This driver is based upon 82596.c, original credits are below...
   but there were too many hoops which HP wants jumped through to
   keep this code in there in a sane manner.

   3 primary sources of the mess --
   1) hppa needs *lots* of cacheline flushing to keep this kind of
   MMIO running.

   2) The 82596 needs to see all of its poपूर्णांकers as their physical
   address.  Thus virt_to_bus/bus_to_virt are *everywhere*.

   3) The implementation HP is using seems to be signअगरicantly pickier
   about when and how the command and RX units are started.  some
   command ordering was changed.

   Examination of the mach driver leads one to believe that there
   might be a saner way to pull this off...  anyone who feels like a
   full reग_लिखो can be my guest.

   Split 02/13/2000 Sam Creasey (sammy@oh.verio.com)

   02/01/2000  Initial modअगरications क्रम parisc by Helge Deller (deller@gmx.de)
   03/02/2000  changes क्रम better/correct(?) cache-flushing (deller)
*/

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
#समावेश <linux/types.h>
#समावेश <linux/bitops.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/gfp.h>

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


#घोषणा DEB(x, y)	अगर (i596_debug & (x)) अणु y; पूर्ण


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

/* Copy frames लघुer than rx_copyअवरोध, otherwise pass on up in
 * a full sized sk_buff.  Value of 100 stolen from tulip.c (!alpha).
 */
अटल पूर्णांक rx_copyअवरोध = 100;

#घोषणा PKT_BUF_SZ	1536
#घोषणा MAX_MC_CNT	64

#घोषणा ISCP_BUSY	0x0001

#घोषणा I596_शून्य ((u32)0xffffffff)

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
	u32            ca;
पूर्ण;

#घोषणा खातापूर्ण		0x8000
#घोषणा SIZE_MASK	0x3fff

काष्ठा i596_tbd अणु
	अचिन्हित लघु size;
	अचिन्हित लघु pad;
	u32            next;
	u32            data;
	u32 cache_pad[5];		/* Total 32 bytes... */
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
	u32            b_next;	/* Address from i596 viewpoपूर्णांक */
पूर्ण;

काष्ठा tx_cmd अणु
	काष्ठा i596_cmd cmd;
	u32            tbd;
	अचिन्हित लघु size;
	अचिन्हित लघु pad;
	काष्ठा sk_buff *skb;		/* So we can मुक्त it after tx */
	dma_addr_t dma_addr;
#अगर_घोषित __LP64__
	u32 cache_pad[6];		/* Total 64 bytes... */
#अन्यथा
	u32 cache_pad[1];		/* Total 32 bytes... */
#पूर्ण_अगर
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
	u32            b_next;	/* Address from i596 viewpoपूर्णांक */
	u32            rbd;
	अचिन्हित लघु count;
	अचिन्हित लघु size;
	काष्ठा i596_rfd *v_next;	/* Address from CPUs viewpoपूर्णांक */
	काष्ठा i596_rfd *v_prev;
#अगर_अघोषित __LP64__
	u32 cache_pad[2];		/* Total 32 bytes... */
#पूर्ण_अगर
पूर्ण;

काष्ठा i596_rbd अणु
	/* hardware data */
	अचिन्हित लघु count;
	अचिन्हित लघु zero1;
	u32            b_next;
	u32            b_data;		/* Address from i596 viewpoपूर्णांक */
	अचिन्हित लघु size;
	अचिन्हित लघु zero2;
	/* driver data */
	काष्ठा sk_buff *skb;
	काष्ठा i596_rbd *v_next;
	u32            b_addr;		/* This rbd addr from i596 view */
	अचिन्हित अक्षर *v_data;		/* Address from CPUs viewpoपूर्णांक */
					/* Total 32 bytes... */
#अगर_घोषित __LP64__
    u32 cache_pad[4];
#पूर्ण_अगर
पूर्ण;

/* These values as chosen so काष्ठा i596_dma fits in one page... */

#घोषणा TX_RING_SIZE 32
#घोषणा RX_RING_SIZE 16

काष्ठा i596_scb अणु
	अचिन्हित लघु status;
	अचिन्हित लघु command;
	u32           cmd;
	u32           rfd;
	u32           crc_err;
	u32           align_err;
	u32           resource_err;
	u32           over_err;
	u32           rcvdt_err;
	u32           लघु_err;
	अचिन्हित लघु t_on;
	अचिन्हित लघु t_off;
पूर्ण;

काष्ठा i596_iscp अणु
	u32 stat;
	u32 scb;
पूर्ण;

काष्ठा i596_scp अणु
	u32 sysbus;
	u32 pad;
	u32 iscp;
पूर्ण;

काष्ठा i596_dma अणु
	काष्ठा i596_scp scp		        __attribute__((aligned(32)));
	अस्थिर काष्ठा i596_iscp iscp		__attribute__((aligned(32)));
	अस्थिर काष्ठा i596_scb scb		__attribute__((aligned(32)));
	काष्ठा sa_cmd sa_cmd			__attribute__((aligned(32)));
	काष्ठा cf_cmd cf_cmd			__attribute__((aligned(32)));
	काष्ठा tdr_cmd tdr_cmd			__attribute__((aligned(32)));
	काष्ठा mc_cmd mc_cmd			__attribute__((aligned(32)));
	काष्ठा i596_rfd rfds[RX_RING_SIZE]	__attribute__((aligned(32)));
	काष्ठा i596_rbd rbds[RX_RING_SIZE]	__attribute__((aligned(32)));
	काष्ठा tx_cmd tx_cmds[TX_RING_SIZE]	__attribute__((aligned(32)));
	काष्ठा i596_tbd tbds[TX_RING_SIZE]	__attribute__((aligned(32)));
पूर्ण;

काष्ठा i596_निजी अणु
	काष्ठा i596_dma *dma;
	u32    stat;
	पूर्णांक last_restart;
	काष्ठा i596_rfd *rfd_head;
	काष्ठा i596_rbd *rbd_head;
	काष्ठा i596_cmd *cmd_tail;
	काष्ठा i596_cmd *cmd_head;
	पूर्णांक cmd_backlog;
	u32    last_cmd;
	पूर्णांक next_tx_cmd;
	पूर्णांक options;
	spinlock_t lock;       /* serialize access to chip */
	dma_addr_t dma_addr;
	व्योम __iomem *mpu_port;
	व्योम __iomem *ca;
पूर्ण;

अटल स्थिर अक्षर init_setup[] =
अणु
	0x8E,		/* length, prefetch on */
	0xC8,		/* fअगरo to 8, monitor off */
	0x80,		/* करोn't save bad frames */
	0x2E,		/* No source address insertion, 8 byte preamble */
	0x00,		/* priority and backoff शेषs */
	0x60,		/* पूर्णांकerframe spacing */
	0x00,		/* slot समय LSB */
	0xf2,		/* slot समय and retries */
	0x00,		/* promiscuous mode */
	0x00,		/* collision detect */
	0x40,		/* minimum frame length */
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
अटल अंतरभूत व्योम ca(काष्ठा net_device *dev);
अटल व्योम mpu_port(काष्ठा net_device *dev, पूर्णांक c, dma_addr_t x);

अटल पूर्णांक rx_ring_size = RX_RING_SIZE;
अटल पूर्णांक ticks_limit = 100;
अटल पूर्णांक max_cmd_backlog = TX_RING_SIZE-1;

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम i596_poll_controller(काष्ठा net_device *dev);
#पूर्ण_अगर

अटल अंतरभूत dma_addr_t virt_to_dma(काष्ठा i596_निजी *lp, अस्थिर व्योम *v)
अणु
	वापस lp->dma_addr + ((अचिन्हित दीर्घ)v - (अचिन्हित दीर्घ)lp->dma);
पूर्ण

#अगर_घोषित NONCOHERENT_DMA
अटल अंतरभूत व्योम dma_sync_dev(काष्ठा net_device *ndev, अस्थिर व्योम *addr,
		माप_प्रकार len)
अणु
	dma_sync_single_क्रम_device(ndev->dev.parent,
			virt_to_dma(netdev_priv(ndev), addr), len,
			DMA_BIसूचीECTIONAL);
पूर्ण

अटल अंतरभूत व्योम dma_sync_cpu(काष्ठा net_device *ndev, अस्थिर व्योम *addr,
		माप_प्रकार len)
अणु
	dma_sync_single_क्रम_cpu(ndev->dev.parent,
			virt_to_dma(netdev_priv(ndev), addr), len,
			DMA_BIसूचीECTIONAL);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम dma_sync_dev(काष्ठा net_device *ndev, अस्थिर व्योम *addr,
		माप_प्रकार len)
अणु
पूर्ण
अटल अंतरभूत व्योम dma_sync_cpu(काष्ठा net_device *ndev, अस्थिर व्योम *addr,
		माप_प्रकार len)
अणु
पूर्ण
#पूर्ण_अगर /* NONCOHERENT_DMA */

अटल अंतरभूत पूर्णांक रुको_istat(काष्ठा net_device *dev, काष्ठा i596_dma *dma, पूर्णांक delcnt, अक्षर *str)
अणु
	dma_sync_cpu(dev, &(dma->iscp), माप(काष्ठा i596_iscp));
	जबतक (--delcnt && dma->iscp.stat) अणु
		udelay(10);
		dma_sync_cpu(dev, &(dma->iscp), माप(काष्ठा i596_iscp));
	पूर्ण
	अगर (!delcnt) अणु
		prपूर्णांकk(KERN_ERR "%s: %s, iscp.stat %04x, didn't clear\n",
		     dev->name, str, SWAP16(dma->iscp.stat));
		वापस -1;
	पूर्ण अन्यथा
		वापस 0;
पूर्ण


अटल अंतरभूत पूर्णांक रुको_cmd(काष्ठा net_device *dev, काष्ठा i596_dma *dma, पूर्णांक delcnt, अक्षर *str)
अणु
	dma_sync_cpu(dev, &(dma->scb), माप(काष्ठा i596_scb));
	जबतक (--delcnt && dma->scb.command) अणु
		udelay(10);
		dma_sync_cpu(dev, &(dma->scb), माप(काष्ठा i596_scb));
	पूर्ण
	अगर (!delcnt) अणु
		prपूर्णांकk(KERN_ERR "%s: %s, status %4.4x, cmd %4.4x.\n",
		       dev->name, str,
		       SWAP16(dma->scb.status),
		       SWAP16(dma->scb.command));
		वापस -1;
	पूर्ण अन्यथा
		वापस 0;
पूर्ण


अटल व्योम i596_display_data(काष्ठा net_device *dev)
अणु
	काष्ठा i596_निजी *lp = netdev_priv(dev);
	काष्ठा i596_dma *dma = lp->dma;
	काष्ठा i596_cmd *cmd;
	काष्ठा i596_rfd *rfd;
	काष्ठा i596_rbd *rbd;

	prपूर्णांकk(KERN_DEBUG "lp and scp at %p, .sysbus = %08x, .iscp = %08x\n",
	       &dma->scp, dma->scp.sysbus, SWAP32(dma->scp.iscp));
	prपूर्णांकk(KERN_DEBUG "iscp at %p, iscp.stat = %08x, .scb = %08x\n",
	       &dma->iscp, SWAP32(dma->iscp.stat), SWAP32(dma->iscp.scb));
	prपूर्णांकk(KERN_DEBUG "scb at %p, scb.status = %04x, .command = %04x,"
		" .cmd = %08x, .rfd = %08x\n",
	       &dma->scb, SWAP16(dma->scb.status), SWAP16(dma->scb.command),
		SWAP16(dma->scb.cmd), SWAP32(dma->scb.rfd));
	prपूर्णांकk(KERN_DEBUG "   errors: crc %x, align %x, resource %x,"
	       " over %x, rcvdt %x, short %x\n",
	       SWAP32(dma->scb.crc_err), SWAP32(dma->scb.align_err),
	       SWAP32(dma->scb.resource_err), SWAP32(dma->scb.over_err),
	       SWAP32(dma->scb.rcvdt_err), SWAP32(dma->scb.लघु_err));
	cmd = lp->cmd_head;
	जबतक (cmd != शून्य) अणु
		prपूर्णांकk(KERN_DEBUG
		       "cmd at %p, .status = %04x, .command = %04x,"
		       " .b_next = %08x\n",
		       cmd, SWAP16(cmd->status), SWAP16(cmd->command),
		       SWAP32(cmd->b_next));
		cmd = cmd->v_next;
	पूर्ण
	rfd = lp->rfd_head;
	prपूर्णांकk(KERN_DEBUG "rfd_head = %p\n", rfd);
	करो अणु
		prपूर्णांकk(KERN_DEBUG
		       "   %p .stat %04x, .cmd %04x, b_next %08x, rbd %08x,"
		       " count %04x\n",
		       rfd, SWAP16(rfd->stat), SWAP16(rfd->cmd),
		       SWAP32(rfd->b_next), SWAP32(rfd->rbd),
		       SWAP16(rfd->count));
		rfd = rfd->v_next;
	पूर्ण जबतक (rfd != lp->rfd_head);
	rbd = lp->rbd_head;
	prपूर्णांकk(KERN_DEBUG "rbd_head = %p\n", rbd);
	करो अणु
		prपूर्णांकk(KERN_DEBUG
		       "   %p .count %04x, b_next %08x, b_data %08x,"
		       " size %04x\n",
			rbd, SWAP16(rbd->count), SWAP32(rbd->b_next),
		       SWAP32(rbd->b_data), SWAP16(rbd->size));
		rbd = rbd->v_next;
	पूर्ण जबतक (rbd != lp->rbd_head);
	dma_sync_cpu(dev, dma, माप(काष्ठा i596_dma));
पूर्ण

अटल अंतरभूत पूर्णांक init_rx_bufs(काष्ठा net_device *dev)
अणु
	काष्ठा i596_निजी *lp = netdev_priv(dev);
	काष्ठा i596_dma *dma = lp->dma;
	पूर्णांक i;
	काष्ठा i596_rfd *rfd;
	काष्ठा i596_rbd *rbd;

	/* First build the Receive Buffer Descriptor List */

	क्रम (i = 0, rbd = dma->rbds; i < rx_ring_size; i++, rbd++) अणु
		dma_addr_t dma_addr;
		काष्ठा sk_buff *skb;

		skb = netdev_alloc_skb_ip_align(dev, PKT_BUF_SZ);
		अगर (skb == शून्य)
			वापस -1;
		dma_addr = dma_map_single(dev->dev.parent, skb->data,
					  PKT_BUF_SZ, DMA_FROM_DEVICE);
		rbd->v_next = rbd+1;
		rbd->b_next = SWAP32(virt_to_dma(lp, rbd+1));
		rbd->b_addr = SWAP32(virt_to_dma(lp, rbd));
		rbd->skb = skb;
		rbd->v_data = skb->data;
		rbd->b_data = SWAP32(dma_addr);
		rbd->size = SWAP16(PKT_BUF_SZ);
	पूर्ण
	lp->rbd_head = dma->rbds;
	rbd = dma->rbds + rx_ring_size - 1;
	rbd->v_next = dma->rbds;
	rbd->b_next = SWAP32(virt_to_dma(lp, dma->rbds));

	/* Now build the Receive Frame Descriptor List */

	क्रम (i = 0, rfd = dma->rfds; i < rx_ring_size; i++, rfd++) अणु
		rfd->rbd = I596_शून्य;
		rfd->v_next = rfd+1;
		rfd->v_prev = rfd-1;
		rfd->b_next = SWAP32(virt_to_dma(lp, rfd+1));
		rfd->cmd = SWAP16(CMD_FLEX);
	पूर्ण
	lp->rfd_head = dma->rfds;
	dma->scb.rfd = SWAP32(virt_to_dma(lp, dma->rfds));
	rfd = dma->rfds;
	rfd->rbd = SWAP32(virt_to_dma(lp, lp->rbd_head));
	rfd->v_prev = dma->rfds + rx_ring_size - 1;
	rfd = dma->rfds + rx_ring_size - 1;
	rfd->v_next = dma->rfds;
	rfd->b_next = SWAP32(virt_to_dma(lp, dma->rfds));
	rfd->cmd = SWAP16(CMD_EOL|CMD_FLEX);

	dma_sync_dev(dev, dma, माप(काष्ठा i596_dma));
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम हटाओ_rx_bufs(काष्ठा net_device *dev)
अणु
	काष्ठा i596_निजी *lp = netdev_priv(dev);
	काष्ठा i596_rbd *rbd;
	पूर्णांक i;

	क्रम (i = 0, rbd = lp->dma->rbds; i < rx_ring_size; i++, rbd++) अणु
		अगर (rbd->skb == शून्य)
			अवरोध;
		dma_unmap_single(dev->dev.parent,
				 (dma_addr_t)SWAP32(rbd->b_data),
				 PKT_BUF_SZ, DMA_FROM_DEVICE);
		dev_kमुक्त_skb(rbd->skb);
	पूर्ण
पूर्ण


अटल व्योम rebuild_rx_bufs(काष्ठा net_device *dev)
अणु
	काष्ठा i596_निजी *lp = netdev_priv(dev);
	काष्ठा i596_dma *dma = lp->dma;
	पूर्णांक i;

	/* Ensure rx frame/buffer descriptors are tidy */

	क्रम (i = 0; i < rx_ring_size; i++) अणु
		dma->rfds[i].rbd = I596_शून्य;
		dma->rfds[i].cmd = SWAP16(CMD_FLEX);
	पूर्ण
	dma->rfds[rx_ring_size-1].cmd = SWAP16(CMD_EOL|CMD_FLEX);
	lp->rfd_head = dma->rfds;
	dma->scb.rfd = SWAP32(virt_to_dma(lp, dma->rfds));
	lp->rbd_head = dma->rbds;
	dma->rfds[0].rbd = SWAP32(virt_to_dma(lp, dma->rbds));

	dma_sync_dev(dev, dma, माप(काष्ठा i596_dma));
पूर्ण


अटल पूर्णांक init_i596_mem(काष्ठा net_device *dev)
अणु
	काष्ठा i596_निजी *lp = netdev_priv(dev);
	काष्ठा i596_dma *dma = lp->dma;
	अचिन्हित दीर्घ flags;

	mpu_port(dev, PORT_RESET, 0);
	udelay(100);			/* Wait 100us - seems to help */

	/* change the scp address */

	lp->last_cmd = jअगरfies;

	dma->scp.sysbus = SYSBUS;
	dma->scp.iscp = SWAP32(virt_to_dma(lp, &(dma->iscp)));
	dma->iscp.scb = SWAP32(virt_to_dma(lp, &(dma->scb)));
	dma->iscp.stat = SWAP32(ISCP_BUSY);
	lp->cmd_backlog = 0;

	lp->cmd_head = शून्य;
	dma->scb.cmd = I596_शून्य;

	DEB(DEB_INIT, prपूर्णांकk(KERN_DEBUG "%s: starting i82596.\n", dev->name));

	dma_sync_dev(dev, &(dma->scp), माप(काष्ठा i596_scp));
	dma_sync_dev(dev, &(dma->iscp), माप(काष्ठा i596_iscp));
	dma_sync_dev(dev, &(dma->scb), माप(काष्ठा i596_scb));

	mpu_port(dev, PORT_ALTSCP, virt_to_dma(lp, &dma->scp));
	ca(dev);
	अगर (रुको_istat(dev, dma, 1000, "initialization timed out"))
		जाओ failed;
	DEB(DEB_INIT, prपूर्णांकk(KERN_DEBUG
			     "%s: i82596 initialization successful\n",
			     dev->name));

	अगर (request_irq(dev->irq, i596_पूर्णांकerrupt, 0, "i82596", dev)) अणु
		prपूर्णांकk(KERN_ERR "%s: IRQ %d not free\n", dev->name, dev->irq);
		जाओ failed;
	पूर्ण

	/* Ensure rx frame/buffer descriptors are tidy */
	rebuild_rx_bufs(dev);

	dma->scb.command = 0;
	dma_sync_dev(dev, &(dma->scb), माप(काष्ठा i596_scb));

	DEB(DEB_INIT, prपूर्णांकk(KERN_DEBUG
			     "%s: queuing CmdConfigure\n", dev->name));
	स_नकल(dma->cf_cmd.i596_config, init_setup, 14);
	dma->cf_cmd.cmd.command = SWAP16(CmdConfigure);
	dma_sync_dev(dev, &(dma->cf_cmd), माप(काष्ठा cf_cmd));
	i596_add_cmd(dev, &dma->cf_cmd.cmd);

	DEB(DEB_INIT, prपूर्णांकk(KERN_DEBUG "%s: queuing CmdSASetup\n", dev->name));
	स_नकल(dma->sa_cmd.eth_addr, dev->dev_addr, ETH_ALEN);
	dma->sa_cmd.cmd.command = SWAP16(CmdSASetup);
	dma_sync_dev(dev, &(dma->sa_cmd), माप(काष्ठा sa_cmd));
	i596_add_cmd(dev, &dma->sa_cmd.cmd);

	DEB(DEB_INIT, prपूर्णांकk(KERN_DEBUG "%s: queuing CmdTDR\n", dev->name));
	dma->tdr_cmd.cmd.command = SWAP16(CmdTDR);
	dma_sync_dev(dev, &(dma->tdr_cmd), माप(काष्ठा tdr_cmd));
	i596_add_cmd(dev, &dma->tdr_cmd.cmd);

	spin_lock_irqsave (&lp->lock, flags);

	अगर (रुको_cmd(dev, dma, 1000, "timed out waiting to issue RX_START")) अणु
		spin_unlock_irqrestore (&lp->lock, flags);
		जाओ failed_मुक्त_irq;
	पूर्ण
	DEB(DEB_INIT, prपूर्णांकk(KERN_DEBUG "%s: Issuing RX_START\n", dev->name));
	dma->scb.command = SWAP16(RX_START);
	dma->scb.rfd = SWAP32(virt_to_dma(lp, dma->rfds));
	dma_sync_dev(dev, &(dma->scb), माप(काष्ठा i596_scb));

	ca(dev);

	spin_unlock_irqrestore (&lp->lock, flags);
	अगर (रुको_cmd(dev, dma, 1000, "RX_START not processed"))
		जाओ failed_मुक्त_irq;
	DEB(DEB_INIT, prपूर्णांकk(KERN_DEBUG
			     "%s: Receive unit started OK\n", dev->name));
	वापस 0;

failed_मुक्त_irq:
	मुक्त_irq(dev->irq, dev);
failed:
	prपूर्णांकk(KERN_ERR "%s: Failed to initialise 82596\n", dev->name);
	mpu_port(dev, PORT_RESET, 0);
	वापस -1;
पूर्ण


अटल अंतरभूत पूर्णांक i596_rx(काष्ठा net_device *dev)
अणु
	काष्ठा i596_निजी *lp = netdev_priv(dev);
	काष्ठा i596_rfd *rfd;
	काष्ठा i596_rbd *rbd;
	पूर्णांक frames = 0;

	DEB(DEB_RXFRAME, prपूर्णांकk(KERN_DEBUG
				"i596_rx(), rfd_head %p, rbd_head %p\n",
				lp->rfd_head, lp->rbd_head));


	rfd = lp->rfd_head;		/* Ref next frame to check */

	dma_sync_cpu(dev, rfd, माप(काष्ठा i596_rfd));
	जबतक (rfd->stat & SWAP16(STAT_C)) अणु	/* Loop जबतक complete frames */
		अगर (rfd->rbd == I596_शून्य)
			rbd = शून्य;
		अन्यथा अगर (rfd->rbd == lp->rbd_head->b_addr) अणु
			rbd = lp->rbd_head;
			dma_sync_cpu(dev, rbd, माप(काष्ठा i596_rbd));
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_ERR "%s: rbd chain broken!\n", dev->name);
			/* XXX Now what? */
			rbd = शून्य;
		पूर्ण
		DEB(DEB_RXFRAME, prपूर्णांकk(KERN_DEBUG
				      "  rfd %p, rfd.rbd %08x, rfd.stat %04x\n",
				      rfd, rfd->rbd, rfd->stat));

		अगर (rbd != शून्य && (rfd->stat & SWAP16(STAT_OK))) अणु
			/* a good frame */
			पूर्णांक pkt_len = SWAP16(rbd->count) & 0x3fff;
			काष्ठा sk_buff *skb = rbd->skb;
			पूर्णांक rx_in_place = 0;

			DEB(DEB_RXADDR, prपूर्णांक_eth(rbd->v_data, "received"));
			frames++;

			/* Check अगर the packet is दीर्घ enough to just accept
			 * without copying to a properly sized skbuff.
			 */

			अगर (pkt_len > rx_copyअवरोध) अणु
				काष्ठा sk_buff *newskb;
				dma_addr_t dma_addr;

				dma_unmap_single(dev->dev.parent,
						 (dma_addr_t)SWAP32(rbd->b_data),
						 PKT_BUF_SZ, DMA_FROM_DEVICE);
				/* Get fresh skbuff to replace filled one. */
				newskb = netdev_alloc_skb_ip_align(dev,
								   PKT_BUF_SZ);
				अगर (newskb == शून्य) अणु
					skb = शून्य;	/* drop pkt */
					जाओ memory_squeeze;
				पूर्ण

				/* Pass up the skb alपढ़ोy on the Rx ring. */
				skb_put(skb, pkt_len);
				rx_in_place = 1;
				rbd->skb = newskb;
				dma_addr = dma_map_single(dev->dev.parent,
							  newskb->data,
							  PKT_BUF_SZ,
							  DMA_FROM_DEVICE);
				rbd->v_data = newskb->data;
				rbd->b_data = SWAP32(dma_addr);
				dma_sync_dev(dev, rbd, माप(काष्ठा i596_rbd));
			पूर्ण अन्यथा अणु
				skb = netdev_alloc_skb_ip_align(dev, pkt_len);
			पूर्ण
memory_squeeze:
			अगर (skb == शून्य) अणु
				/* XXX tulip.c can defer packets here!! */
				dev->stats.rx_dropped++;
			पूर्ण अन्यथा अणु
				अगर (!rx_in_place) अणु
					/* 16 byte align the data fields */
					dma_sync_single_क्रम_cpu(dev->dev.parent,
								(dma_addr_t)SWAP32(rbd->b_data),
								PKT_BUF_SZ, DMA_FROM_DEVICE);
					skb_put_data(skb, rbd->v_data,
						     pkt_len);
					dma_sync_single_क्रम_device(dev->dev.parent,
								   (dma_addr_t)SWAP32(rbd->b_data),
								   PKT_BUF_SZ, DMA_FROM_DEVICE);
				पूर्ण
				skb->len = pkt_len;
				skb->protocol = eth_type_trans(skb, dev);
				netअगर_rx(skb);
				dev->stats.rx_packets++;
				dev->stats.rx_bytes += pkt_len;
			पूर्ण
		पूर्ण अन्यथा अणु
			DEB(DEB_ERRORS, prपूर्णांकk(KERN_DEBUG
					       "%s: Error, rfd.stat = 0x%04x\n",
					       dev->name, rfd->stat));
			dev->stats.rx_errors++;
			अगर (rfd->stat & SWAP16(0x0100))
				dev->stats.collisions++;
			अगर (rfd->stat & SWAP16(0x8000))
				dev->stats.rx_length_errors++;
			अगर (rfd->stat & SWAP16(0x0001))
				dev->stats.rx_over_errors++;
			अगर (rfd->stat & SWAP16(0x0002))
				dev->stats.rx_fअगरo_errors++;
			अगर (rfd->stat & SWAP16(0x0004))
				dev->stats.rx_frame_errors++;
			अगर (rfd->stat & SWAP16(0x0008))
				dev->stats.rx_crc_errors++;
			अगर (rfd->stat & SWAP16(0x0010))
				dev->stats.rx_length_errors++;
		पूर्ण

		/* Clear the buffer descriptor count and खातापूर्ण + F flags */

		अगर (rbd != शून्य && (rbd->count & SWAP16(0x4000))) अणु
			rbd->count = 0;
			lp->rbd_head = rbd->v_next;
			dma_sync_dev(dev, rbd, माप(काष्ठा i596_rbd));
		पूर्ण

		/* Tidy the frame descriptor, marking it as end of list */

		rfd->rbd = I596_शून्य;
		rfd->stat = 0;
		rfd->cmd = SWAP16(CMD_EOL|CMD_FLEX);
		rfd->count = 0;

		/* Update record of next frame descriptor to process */

		lp->dma->scb.rfd = rfd->b_next;
		lp->rfd_head = rfd->v_next;
		dma_sync_dev(dev, rfd, माप(काष्ठा i596_rfd));

		/* Remove end-of-list from old end descriptor */

		rfd->v_prev->cmd = SWAP16(CMD_FLEX);
		dma_sync_dev(dev, rfd->v_prev, माप(काष्ठा i596_rfd));
		rfd = lp->rfd_head;
		dma_sync_cpu(dev, rfd, माप(काष्ठा i596_rfd));
	पूर्ण

	DEB(DEB_RXFRAME, prपूर्णांकk(KERN_DEBUG "frames %d\n", frames));

	वापस 0;
पूर्ण


अटल अंतरभूत व्योम i596_cleanup_cmd(काष्ठा net_device *dev, काष्ठा i596_निजी *lp)
अणु
	काष्ठा i596_cmd *ptr;

	जबतक (lp->cmd_head != शून्य) अणु
		ptr = lp->cmd_head;
		lp->cmd_head = ptr->v_next;
		lp->cmd_backlog--;

		चयन (SWAP16(ptr->command) & 0x7) अणु
		हाल CmdTx:
			अणु
				काष्ठा tx_cmd *tx_cmd = (काष्ठा tx_cmd *) ptr;
				काष्ठा sk_buff *skb = tx_cmd->skb;
				dma_unmap_single(dev->dev.parent,
						 tx_cmd->dma_addr,
						 skb->len, DMA_TO_DEVICE);

				dev_kमुक्त_skb(skb);

				dev->stats.tx_errors++;
				dev->stats.tx_पातed_errors++;

				ptr->v_next = शून्य;
				ptr->b_next = I596_शून्य;
				tx_cmd->cmd.command = 0;  /* Mark as मुक्त */
				अवरोध;
			पूर्ण
		शेष:
			ptr->v_next = शून्य;
			ptr->b_next = I596_शून्य;
		पूर्ण
		dma_sync_dev(dev, ptr, माप(काष्ठा i596_cmd));
	पूर्ण

	रुको_cmd(dev, lp->dma, 100, "i596_cleanup_cmd timed out");
	lp->dma->scb.cmd = I596_शून्य;
	dma_sync_dev(dev, &(lp->dma->scb), माप(काष्ठा i596_scb));
पूर्ण


अटल अंतरभूत व्योम i596_reset(काष्ठा net_device *dev, काष्ठा i596_निजी *lp)
अणु
	अचिन्हित दीर्घ flags;

	DEB(DEB_RESET, prपूर्णांकk(KERN_DEBUG "i596_reset\n"));

	spin_lock_irqsave (&lp->lock, flags);

	रुको_cmd(dev, lp->dma, 100, "i596_reset timed out");

	netअगर_stop_queue(dev);

	/* FIXME: this command might cause an lpmc */
	lp->dma->scb.command = SWAP16(CUC_ABORT | RX_ABORT);
	dma_sync_dev(dev, &(lp->dma->scb), माप(काष्ठा i596_scb));
	ca(dev);

	/* रुको क्रम shutकरोwn */
	रुको_cmd(dev, lp->dma, 1000, "i596_reset 2 timed out");
	spin_unlock_irqrestore (&lp->lock, flags);

	i596_cleanup_cmd(dev, lp);
	i596_rx(dev);

	netअगर_start_queue(dev);
	init_i596_mem(dev);
पूर्ण


अटल व्योम i596_add_cmd(काष्ठा net_device *dev, काष्ठा i596_cmd *cmd)
अणु
	काष्ठा i596_निजी *lp = netdev_priv(dev);
	काष्ठा i596_dma *dma = lp->dma;
	अचिन्हित दीर्घ flags;

	DEB(DEB_ADDCMD, prपूर्णांकk(KERN_DEBUG "i596_add_cmd cmd_head %p\n",
			       lp->cmd_head));

	cmd->status = 0;
	cmd->command |= SWAP16(CMD_EOL | CMD_INTR);
	cmd->v_next = शून्य;
	cmd->b_next = I596_शून्य;
	dma_sync_dev(dev, cmd, माप(काष्ठा i596_cmd));

	spin_lock_irqsave (&lp->lock, flags);

	अगर (lp->cmd_head != शून्य) अणु
		lp->cmd_tail->v_next = cmd;
		lp->cmd_tail->b_next = SWAP32(virt_to_dma(lp, &cmd->status));
		dma_sync_dev(dev, lp->cmd_tail, माप(काष्ठा i596_cmd));
	पूर्ण अन्यथा अणु
		lp->cmd_head = cmd;
		रुको_cmd(dev, dma, 100, "i596_add_cmd timed out");
		dma->scb.cmd = SWAP32(virt_to_dma(lp, &cmd->status));
		dma->scb.command = SWAP16(CUC_START);
		dma_sync_dev(dev, &(dma->scb), माप(काष्ठा i596_scb));
		ca(dev);
	पूर्ण
	lp->cmd_tail = cmd;
	lp->cmd_backlog++;

	spin_unlock_irqrestore (&lp->lock, flags);

	अगर (lp->cmd_backlog > max_cmd_backlog) अणु
		अचिन्हित दीर्घ tickssofar = jअगरfies - lp->last_cmd;

		अगर (tickssofar < ticks_limit)
			वापस;

		prपूर्णांकk(KERN_ERR
		       "%s: command unit timed out, status resetting.\n",
		       dev->name);
#अगर 1
		i596_reset(dev, lp);
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल पूर्णांक i596_खोलो(काष्ठा net_device *dev)
अणु
	DEB(DEB_OPEN, prपूर्णांकk(KERN_DEBUG
			     "%s: i596_open() irq %d.\n", dev->name, dev->irq));

	अगर (init_rx_bufs(dev)) अणु
		prपूर्णांकk(KERN_ERR "%s: Failed to init rx bufs\n", dev->name);
		वापस -EAGAIN;
	पूर्ण
	अगर (init_i596_mem(dev)) अणु
		prपूर्णांकk(KERN_ERR "%s: Failed to init memory\n", dev->name);
		जाओ out_हटाओ_rx_bufs;
	पूर्ण
	netअगर_start_queue(dev);

	वापस 0;

out_हटाओ_rx_bufs:
	हटाओ_rx_bufs(dev);
	वापस -EAGAIN;
पूर्ण

अटल व्योम i596_tx_समयout (काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा i596_निजी *lp = netdev_priv(dev);

	/* Transmitter समयout, serious problems. */
	DEB(DEB_ERRORS, prपूर्णांकk(KERN_DEBUG
			       "%s: transmit timed out, status resetting.\n",
			       dev->name));

	dev->stats.tx_errors++;

	/* Try to restart the adaptor */
	अगर (lp->last_restart == dev->stats.tx_packets) अणु
		DEB(DEB_ERRORS, prपूर्णांकk(KERN_DEBUG "Resetting board.\n"));
		/* Shutकरोwn and restart */
		i596_reset (dev, lp);
	पूर्ण अन्यथा अणु
		/* Issue a channel attention संकेत */
		DEB(DEB_ERRORS, prपूर्णांकk(KERN_DEBUG "Kicking board.\n"));
		lp->dma->scb.command = SWAP16(CUC_START | RX_START);
		dma_sync_dev(dev, &(lp->dma->scb), माप(काष्ठा i596_scb));
		ca (dev);
		lp->last_restart = dev->stats.tx_packets;
	पूर्ण

	netअगर_trans_update(dev); /* prevent tx समयout */
	netअगर_wake_queue (dev);
पूर्ण


अटल netdev_tx_t i596_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा i596_निजी *lp = netdev_priv(dev);
	काष्ठा tx_cmd *tx_cmd;
	काष्ठा i596_tbd *tbd;
	लघु length = skb->len;

	DEB(DEB_STARTTX, prपूर्णांकk(KERN_DEBUG
				"%s: i596_start_xmit(%x,%p) called\n",
				dev->name, skb->len, skb->data));

	अगर (length < ETH_ZLEN) अणु
		अगर (skb_padto(skb, ETH_ZLEN))
			वापस NETDEV_TX_OK;
		length = ETH_ZLEN;
	पूर्ण

	netअगर_stop_queue(dev);

	tx_cmd = lp->dma->tx_cmds + lp->next_tx_cmd;
	tbd = lp->dma->tbds + lp->next_tx_cmd;

	अगर (tx_cmd->cmd.command) अणु
		DEB(DEB_ERRORS, prपूर्णांकk(KERN_DEBUG
				       "%s: xmit ring full, dropping packet.\n",
				       dev->name));
		dev->stats.tx_dropped++;

		dev_kमुक्त_skb_any(skb);
	पूर्ण अन्यथा अणु
		अगर (++lp->next_tx_cmd == TX_RING_SIZE)
			lp->next_tx_cmd = 0;
		tx_cmd->tbd = SWAP32(virt_to_dma(lp, tbd));
		tbd->next = I596_शून्य;

		tx_cmd->cmd.command = SWAP16(CMD_FLEX | CmdTx);
		tx_cmd->skb = skb;

		tx_cmd->pad = 0;
		tx_cmd->size = 0;
		tbd->pad = 0;
		tbd->size = SWAP16(खातापूर्ण | length);

		tx_cmd->dma_addr = dma_map_single(dev->dev.parent, skb->data,
						  skb->len, DMA_TO_DEVICE);
		tbd->data = SWAP32(tx_cmd->dma_addr);

		DEB(DEB_TXADDR, prपूर्णांक_eth(skb->data, "tx-queued"));
		dma_sync_dev(dev, tx_cmd, माप(काष्ठा tx_cmd));
		dma_sync_dev(dev, tbd, माप(काष्ठा i596_tbd));
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
अटल स्थिर काष्ठा net_device_ops i596_netdev_ops = अणु
	.nकरो_खोलो		= i596_खोलो,
	.nकरो_stop		= i596_बंद,
	.nकरो_start_xmit		= i596_start_xmit,
	.nकरो_set_rx_mode	= set_multicast_list,
	.nकरो_tx_समयout		= i596_tx_समयout,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= i596_poll_controller,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक i82596_probe(काष्ठा net_device *dev)
अणु
	काष्ठा i596_निजी *lp = netdev_priv(dev);
	पूर्णांक ret;

	/* This lot is ensure things have been cache line aligned. */
	BUILD_BUG_ON(माप(काष्ठा i596_rfd) != 32);
	BUILD_BUG_ON(माप(काष्ठा i596_rbd) &  31);
	BUILD_BUG_ON(माप(काष्ठा tx_cmd)   &  31);
	BUILD_BUG_ON(माप(काष्ठा i596_tbd) != 32);
#अगर_अघोषित __LP64__
	BUILD_BUG_ON(माप(काष्ठा i596_dma) > 4096);
#पूर्ण_अगर

	अगर (!dev->base_addr || !dev->irq)
		वापस -ENODEV;

	dev->netdev_ops = &i596_netdev_ops;
	dev->watchकरोg_समयo = TX_TIMEOUT;

	स_रखो(lp->dma, 0, माप(काष्ठा i596_dma));
	lp->dma->scb.command = 0;
	lp->dma->scb.cmd = I596_शून्य;
	lp->dma->scb.rfd = I596_शून्य;
	spin_lock_init(&lp->lock);

	dma_sync_dev(dev, lp->dma, माप(काष्ठा i596_dma));

	ret = रेजिस्टर_netdev(dev);
	अगर (ret)
		वापस ret;

	DEB(DEB_PROBE, prपूर्णांकk(KERN_INFO "%s: 82596 at %#3lx, %pM IRQ %d.\n",
			      dev->name, dev->base_addr, dev->dev_addr,
			      dev->irq));
	DEB(DEB_INIT, prपूर्णांकk(KERN_INFO
			     "%s: dma at 0x%p (%d bytes), lp->scb at 0x%p\n",
			     dev->name, lp->dma, (पूर्णांक)माप(काष्ठा i596_dma),
			     &lp->dma->scb));

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम i596_poll_controller(काष्ठा net_device *dev)
अणु
	disable_irq(dev->irq);
	i596_पूर्णांकerrupt(dev->irq, dev);
	enable_irq(dev->irq);
पूर्ण
#पूर्ण_अगर

अटल irqवापस_t i596_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा i596_निजी *lp;
	काष्ठा i596_dma *dma;
	अचिन्हित लघु status, ack_cmd = 0;

	lp = netdev_priv(dev);
	dma = lp->dma;

	spin_lock (&lp->lock);

	रुको_cmd(dev, dma, 100, "i596 interrupt, timeout");
	status = SWAP16(dma->scb.status);

	DEB(DEB_INTS, prपूर्णांकk(KERN_DEBUG
			     "%s: i596 interrupt, IRQ %d, status %4.4x.\n",
			dev->name, dev->irq, status));

	ack_cmd = status & 0xf000;

	अगर (!ack_cmd) अणु
		DEB(DEB_ERRORS, prपूर्णांकk(KERN_DEBUG
				       "%s: interrupt with no events\n",
				       dev->name));
		spin_unlock (&lp->lock);
		वापस IRQ_NONE;
	पूर्ण

	अगर ((status & 0x8000) || (status & 0x2000)) अणु
		काष्ठा i596_cmd *ptr;

		अगर ((status & 0x8000))
			DEB(DEB_INTS,
			    prपूर्णांकk(KERN_DEBUG
				   "%s: i596 interrupt completed command.\n",
				   dev->name));
		अगर ((status & 0x2000))
			DEB(DEB_INTS,
			    prपूर्णांकk(KERN_DEBUG
				   "%s: i596 interrupt command unit inactive %x.\n",
				   dev->name, status & 0x0700));

		जबतक (lp->cmd_head != शून्य) अणु
			dma_sync_cpu(dev, lp->cmd_head, माप(काष्ठा i596_cmd));
			अगर (!(lp->cmd_head->status & SWAP16(STAT_C)))
				अवरोध;

			ptr = lp->cmd_head;

			DEB(DEB_STATUS,
			    prपूर्णांकk(KERN_DEBUG
				   "cmd_head->status = %04x, ->command = %04x\n",
				   SWAP16(lp->cmd_head->status),
				   SWAP16(lp->cmd_head->command)));
			lp->cmd_head = ptr->v_next;
			lp->cmd_backlog--;

			चयन (SWAP16(ptr->command) & 0x7) अणु
			हाल CmdTx:
			    अणु
				काष्ठा tx_cmd *tx_cmd = (काष्ठा tx_cmd *) ptr;
				काष्ठा sk_buff *skb = tx_cmd->skb;

				अगर (ptr->status & SWAP16(STAT_OK)) अणु
					DEB(DEB_TXADDR,
					    prपूर्णांक_eth(skb->data, "tx-done"));
				पूर्ण अन्यथा अणु
					dev->stats.tx_errors++;
					अगर (ptr->status & SWAP16(0x0020))
						dev->stats.collisions++;
					अगर (!(ptr->status & SWAP16(0x0040)))
						dev->stats.tx_heartbeat_errors++;
					अगर (ptr->status & SWAP16(0x0400))
						dev->stats.tx_carrier_errors++;
					अगर (ptr->status & SWAP16(0x0800))
						dev->stats.collisions++;
					अगर (ptr->status & SWAP16(0x1000))
						dev->stats.tx_पातed_errors++;
				पूर्ण
				dma_unmap_single(dev->dev.parent,
						 tx_cmd->dma_addr,
						 skb->len, DMA_TO_DEVICE);
				dev_consume_skb_irq(skb);

				tx_cmd->cmd.command = 0; /* Mark मुक्त */
				अवरोध;
			    पूर्ण
			हाल CmdTDR:
			    अणु
				अचिन्हित लघु status = SWAP16(((काष्ठा tdr_cmd *)ptr)->status);

				अगर (status & 0x8000) अणु
					DEB(DEB_ANY,
					    prपूर्णांकk(KERN_DEBUG "%s: link ok.\n",
						   dev->name));
				पूर्ण अन्यथा अणु
					अगर (status & 0x4000)
						prपूर्णांकk(KERN_ERR
						       "%s: Transceiver problem.\n",
						       dev->name);
					अगर (status & 0x2000)
						prपूर्णांकk(KERN_ERR
						       "%s: Termination problem.\n",
						       dev->name);
					अगर (status & 0x1000)
						prपूर्णांकk(KERN_ERR
						       "%s: Short circuit.\n",
						       dev->name);

					DEB(DEB_TDR,
					    prपूर्णांकk(KERN_DEBUG "%s: Time %d.\n",
						   dev->name, status & 0x07ff));
				पूर्ण
				अवरोध;
			    पूर्ण
			हाल CmdConfigure:
				/*
				 * Zap command so set_multicast_list() know
				 * it is मुक्त
				 */
				ptr->command = 0;
				अवरोध;
			पूर्ण
			ptr->v_next = शून्य;
			ptr->b_next = I596_शून्य;
			dma_sync_dev(dev, ptr, माप(काष्ठा i596_cmd));
			lp->last_cmd = jअगरfies;
		पूर्ण

		/* This mess is arranging that only the last of any outstanding
		 * commands has the पूर्णांकerrupt bit set.  Should probably really
		 * only add to the cmd queue when the CU is stopped.
		 */
		ptr = lp->cmd_head;
		जबतक ((ptr != शून्य) && (ptr != lp->cmd_tail)) अणु
			काष्ठा i596_cmd *prev = ptr;

			ptr->command &= SWAP16(0x1fff);
			ptr = ptr->v_next;
			dma_sync_dev(dev, prev, माप(काष्ठा i596_cmd));
		पूर्ण

		अगर (lp->cmd_head != शून्य)
			ack_cmd |= CUC_START;
		dma->scb.cmd = SWAP32(virt_to_dma(lp, &lp->cmd_head->status));
		dma_sync_dev(dev, &dma->scb, माप(काष्ठा i596_scb));
	पूर्ण
	अगर ((status & 0x1000) || (status & 0x4000)) अणु
		अगर ((status & 0x4000))
			DEB(DEB_INTS,
			    prपूर्णांकk(KERN_DEBUG
				   "%s: i596 interrupt received a frame.\n",
				   dev->name));
		i596_rx(dev);
		/* Only RX_START अगर stopped - RGH 07-07-96 */
		अगर (status & 0x1000) अणु
			अगर (netअगर_running(dev)) अणु
				DEB(DEB_ERRORS,
				    prपूर्णांकk(KERN_DEBUG
					   "%s: i596 interrupt receive unit inactive, status 0x%x\n",
					   dev->name, status));
				ack_cmd |= RX_START;
				dev->stats.rx_errors++;
				dev->stats.rx_fअगरo_errors++;
				rebuild_rx_bufs(dev);
			पूर्ण
		पूर्ण
	पूर्ण
	रुको_cmd(dev, dma, 100, "i596 interrupt, timeout");
	dma->scb.command = SWAP16(ack_cmd);
	dma_sync_dev(dev, &dma->scb, माप(काष्ठा i596_scb));

	/* DANGER: I suspect that some kind of पूर्णांकerrupt
	 acknowledgement aside from acking the 82596 might be needed
	 here...  but it's running acceptably without */

	ca(dev);

	रुको_cmd(dev, dma, 100, "i596 interrupt, exit timeout");
	DEB(DEB_INTS, prपूर्णांकk(KERN_DEBUG "%s: exiting interrupt.\n", dev->name));

	spin_unlock (&lp->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक i596_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा i596_निजी *lp = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	netअगर_stop_queue(dev);

	DEB(DEB_INIT,
	    prपूर्णांकk(KERN_DEBUG
		   "%s: Shutting down ethercard, status was %4.4x.\n",
		   dev->name, SWAP16(lp->dma->scb.status)));

	spin_lock_irqsave(&lp->lock, flags);

	रुको_cmd(dev, lp->dma, 100, "close1 timed out");
	lp->dma->scb.command = SWAP16(CUC_ABORT | RX_ABORT);
	dma_sync_dev(dev, &lp->dma->scb, माप(काष्ठा i596_scb));

	ca(dev);

	रुको_cmd(dev, lp->dma, 100, "close2 timed out");
	spin_unlock_irqrestore(&lp->lock, flags);
	DEB(DEB_STRUCT, i596_display_data(dev));
	i596_cleanup_cmd(dev, lp);

	मुक्त_irq(dev->irq, dev);
	हटाओ_rx_bufs(dev);

	वापस 0;
पूर्ण

/*
 *    Set or clear the multicast filter क्रम this adaptor.
 */

अटल व्योम set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा i596_निजी *lp = netdev_priv(dev);
	काष्ठा i596_dma *dma = lp->dma;
	पूर्णांक config = 0, cnt;

	DEB(DEB_MULTI,
	    prपूर्णांकk(KERN_DEBUG
		   "%s: set multicast list, %d entries, promisc %s, allmulti %s\n",
		   dev->name, netdev_mc_count(dev),
		   dev->flags & IFF_PROMISC ? "ON" : "OFF",
		   dev->flags & IFF_ALLMULTI ? "ON" : "OFF"));

	अगर ((dev->flags & IFF_PROMISC) &&
	    !(dma->cf_cmd.i596_config[8] & 0x01)) अणु
		dma->cf_cmd.i596_config[8] |= 0x01;
		config = 1;
	पूर्ण
	अगर (!(dev->flags & IFF_PROMISC) &&
	    (dma->cf_cmd.i596_config[8] & 0x01)) अणु
		dma->cf_cmd.i596_config[8] &= ~0x01;
		config = 1;
	पूर्ण
	अगर ((dev->flags & IFF_ALLMULTI) &&
	    (dma->cf_cmd.i596_config[11] & 0x20)) अणु
		dma->cf_cmd.i596_config[11] &= ~0x20;
		config = 1;
	पूर्ण
	अगर (!(dev->flags & IFF_ALLMULTI) &&
	    !(dma->cf_cmd.i596_config[11] & 0x20)) अणु
		dma->cf_cmd.i596_config[11] |= 0x20;
		config = 1;
	पूर्ण
	अगर (config) अणु
		अगर (dma->cf_cmd.cmd.command)
			prपूर्णांकk(KERN_INFO
			       "%s: config change request already queued\n",
			       dev->name);
		अन्यथा अणु
			dma->cf_cmd.cmd.command = SWAP16(CmdConfigure);
			dma_sync_dev(dev, &dma->cf_cmd, माप(काष्ठा cf_cmd));
			i596_add_cmd(dev, &dma->cf_cmd.cmd);
		पूर्ण
	पूर्ण

	cnt = netdev_mc_count(dev);
	अगर (cnt > MAX_MC_CNT) अणु
		cnt = MAX_MC_CNT;
		prपूर्णांकk(KERN_NOTICE "%s: Only %d multicast addresses supported",
			dev->name, cnt);
	पूर्ण

	अगर (!netdev_mc_empty(dev)) अणु
		काष्ठा netdev_hw_addr *ha;
		अचिन्हित अक्षर *cp;
		काष्ठा mc_cmd *cmd;

		cmd = &dma->mc_cmd;
		cmd->cmd.command = SWAP16(CmdMulticastList);
		cmd->mc_cnt = SWAP16(netdev_mc_count(dev) * 6);
		cp = cmd->mc_addrs;
		netdev_क्रम_each_mc_addr(ha, dev) अणु
			अगर (!cnt--)
				अवरोध;
			स_नकल(cp, ha->addr, ETH_ALEN);
			अगर (i596_debug > 1)
				DEB(DEB_MULTI,
				    prपूर्णांकk(KERN_DEBUG
					   "%s: Adding address %pM\n",
					   dev->name, cp));
			cp += ETH_ALEN;
		पूर्ण
		dma_sync_dev(dev, &dma->mc_cmd, माप(काष्ठा mc_cmd));
		i596_add_cmd(dev, &cmd->cmd);
	पूर्ण
पूर्ण
