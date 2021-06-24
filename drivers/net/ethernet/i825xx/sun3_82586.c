<शैली गुरु>
/*
 * Sun3 i82586 Ethernet driver
 *
 * Cloned from ni52.c क्रम the Sun3 by Sam Creasey (sammy@sammy.net)
 *
 * Original copyright follows:
 * --------------------------
 *
 * net-3-driver क्रम the NI5210 card (i82586 Ethernet chip)
 *
 * This is an extension to the Linux operating प्रणाली, and is covered by the
 * same Gnu Public License that covers that work.
 *
 * Alphacode 0.82 (96/09/29) क्रम Linux 2.0.0 (or later)
 * Copyrights (c) 1994,1995,1996 by M.Hipp (hippm@inक्रमmatik.uni-tuebingen.de)
 * --------------------------
 *
 * Consult ni52.c क्रम further notes from the original driver.
 *
 * This incarnation currently supports the OBIO version of the i82586 chip
 * used in certain sun3 models.  It should be fairly करोable to expand this
 * to support VME अगर I should every acquire such a board.
 *
 */

अटल पूर्णांक debuglevel = 0; /* debug-prपूर्णांकk 0: off 1: a few 2: more */
अटल पूर्णांक स्वतःmatic_resume = 0; /* experimental .. better should be zero */
अटल पूर्णांक rfdadd = 0; /* rfdadd=1 may be better क्रम 8K MEM cards */
अटल पूर्णांक fअगरo=0x8;	/* करोn't change */

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/bitops.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/idprom.h>
#समावेश <यंत्र/machines.h>
#समावेश <यंत्र/sun3mmu.h>
#समावेश <यंत्र/dvma.h>
#समावेश <यंत्र/byteorder.h>

#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>

#समावेश "sun3_82586.h"

#घोषणा DRV_NAME "sun3_82586"

#घोषणा DEBUG       /* debug on */
#घोषणा SYSBUSVAL 0 /* 16 Bit */
#घोषणा SUN3_82586_TOTAL_SIZE	PAGE_SIZE

#घोषणा sun3_attn586()  अणु*(अस्थिर अचिन्हित अक्षर *)(dev->base_addr) |= IEOB_ATTEN; *(अस्थिर अचिन्हित अक्षर *)(dev->base_addr) &= ~IEOB_ATTEN;पूर्ण
#घोषणा sun3_reset586() अणु*(अस्थिर अचिन्हित अक्षर *)(dev->base_addr) = 0; udelay(100); *(अस्थिर अचिन्हित अक्षर *)(dev->base_addr) = IEOB_NORSET;पूर्ण
#घोषणा sun3_disपूर्णांक()   अणु*(अस्थिर अचिन्हित अक्षर *)(dev->base_addr) &= ~IEOB_IENAB;पूर्ण
#घोषणा sun3_enaपूर्णांक()   अणु*(अस्थिर अचिन्हित अक्षर *)(dev->base_addr) |= IEOB_IENAB;पूर्ण
#घोषणा sun3_active()   अणु*(अस्थिर अचिन्हित अक्षर *)(dev->base_addr) |= (IEOB_IENAB|IEOB_ONAIR|IEOB_NORSET);पूर्ण

#घोषणा make32(ptr16) (p->memtop + (swab16((अचिन्हित लघु) (ptr16))) )
#घोषणा make24(ptr32) (अक्षर *)swab32(( ((अचिन्हित दीर्घ) (ptr32)) - p->base))
#घोषणा make16(ptr32) (swab16((अचिन्हित लघु) ((अचिन्हित दीर्घ)(ptr32) - (अचिन्हित दीर्घ) p->memtop )))

/******************* how to calculate the buffers *****************************

  * IMPORTANT NOTE: अगर you configure only one NUM_XMIT_BUFFS, the driver works
  * --------------- in a dअगरferent (more stable?) mode. Only in this mode it's
  *                 possible to configure the driver with 'NO_NOPCOMMANDS'

माप(scp)=12; माप(scb)=16; माप(iscp)=8;
माप(scp)+माप(iscp)+माप(scb) = 36 = INIT
माप(rfd) = 24; माप(rbd) = 12;
माप(tbd) = 8; माप(transmit_cmd) = 16;
माप(nop_cmd) = 8;

  * अगर you करोn't know the driver, better करो not change these values: */

#घोषणा RECV_BUFF_SIZE 1536 /* slightly oversized */
#घोषणा XMIT_BUFF_SIZE 1536 /* slightly oversized */
#घोषणा NUM_XMIT_BUFFS 1    /* config क्रम 32K shmem */
#घोषणा NUM_RECV_BUFFS_8 4 /* config क्रम 32K shared mem */
#घोषणा NUM_RECV_BUFFS_16 9 /* config क्रम 32K shared mem */
#घोषणा NUM_RECV_BUFFS_32 16 /* config क्रम 32K shared mem */
#घोषणा NO_NOPCOMMANDS      /* only possible with NUM_XMIT_BUFFS=1 */

/**************************************************************************/

/* dअगरferent DELAYs */
#घोषणा DELAY(x) mdelay(32 * x);
#घोषणा DELAY_16(); अणु udelay(16); पूर्ण
#घोषणा DELAY_18(); अणु udelay(4); पूर्ण

/* रुको क्रम command with समयout: */
#घोषणा WAIT_4_SCB_CMD() \
अणु पूर्णांक i; \
  क्रम(i=0;i<16384;i++) अणु \
    अगर(!p->scb->cmd_cuc) अवरोध; \
    DELAY_18(); \
    अगर(i == 16383) अणु \
      prपूर्णांकk("%s: scb_cmd timed out: %04x,%04x .. disabling i82586!!\n",dev->name,p->scb->cmd_cuc,p->scb->cus); \
       अगर(!p->reseted) अणु p->reseted = 1; sun3_reset586(); पूर्ण पूर्ण पूर्ण पूर्ण

#घोषणा WAIT_4_SCB_CMD_RUC() अणु पूर्णांक i; \
  क्रम(i=0;i<16384;i++) अणु \
    अगर(!p->scb->cmd_ruc) अवरोध; \
    DELAY_18(); \
    अगर(i == 16383) अणु \
      prपूर्णांकk("%s: scb_cmd (ruc) timed out: %04x,%04x .. disabling i82586!!\n",dev->name,p->scb->cmd_ruc,p->scb->rus); \
       अगर(!p->reseted) अणु p->reseted = 1; sun3_reset586(); पूर्ण पूर्ण पूर्ण पूर्ण

#घोषणा WAIT_4_STAT_COMPL(addr) अणु पूर्णांक i; \
   क्रम(i=0;i<32767;i++) अणु \
     अगर(swab16((addr)->cmd_status) & STAT_COMPL) अवरोध; \
     DELAY_16(); DELAY_16(); पूर्ण पूर्ण

अटल पूर्णांक     sun3_82586_probe1(काष्ठा net_device *dev,पूर्णांक ioaddr);
अटल irqवापस_t sun3_82586_पूर्णांकerrupt(पूर्णांक irq,व्योम *dev_id);
अटल पूर्णांक     sun3_82586_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक     sun3_82586_बंद(काष्ठा net_device *dev);
अटल netdev_tx_t     sun3_82586_send_packet(काष्ठा sk_buff *,
					      काष्ठा net_device *);
अटल काष्ठा  net_device_stats *sun3_82586_get_stats(काष्ठा net_device *dev);
अटल व्योम    set_multicast_list(काष्ठा net_device *dev);
अटल व्योम    sun3_82586_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
#अगर 0
अटल व्योम    sun3_82586_dump(काष्ठा net_device *,व्योम *);
#पूर्ण_अगर

/* helper-functions */
अटल पूर्णांक     init586(काष्ठा net_device *dev);
अटल पूर्णांक     check586(काष्ठा net_device *dev,अक्षर *where,अचिन्हित size);
अटल व्योम    alloc586(काष्ठा net_device *dev);
अटल व्योम    startrecv586(काष्ठा net_device *dev);
अटल व्योम   *alloc_rfa(काष्ठा net_device *dev,व्योम *ptr);
अटल व्योम    sun3_82586_rcv_पूर्णांक(काष्ठा net_device *dev);
अटल व्योम    sun3_82586_xmt_पूर्णांक(काष्ठा net_device *dev);
अटल व्योम    sun3_82586_rnr_पूर्णांक(काष्ठा net_device *dev);

काष्ठा priv
अणु
	अचिन्हित दीर्घ base;
	अक्षर *memtop;
	दीर्घ पूर्णांक lock;
	पूर्णांक reseted;
	अस्थिर काष्ठा rfd_काष्ठा	*rfd_last,*rfd_top,*rfd_first;
	अस्थिर काष्ठा scp_काष्ठा	*scp;	/* अस्थिर is important */
	अस्थिर काष्ठा iscp_काष्ठा	*iscp;	/* अस्थिर is important */
	अस्थिर काष्ठा scb_काष्ठा	*scb;	/* अस्थिर is important */
	अस्थिर काष्ठा tbd_काष्ठा	*xmit_buffs[NUM_XMIT_BUFFS];
	अस्थिर काष्ठा transmit_cmd_काष्ठा *xmit_cmds[NUM_XMIT_BUFFS];
#अगर (NUM_XMIT_BUFFS == 1)
	अस्थिर काष्ठा nop_cmd_काष्ठा *nop_cmds[2];
#अन्यथा
	अस्थिर काष्ठा nop_cmd_काष्ठा *nop_cmds[NUM_XMIT_BUFFS];
#पूर्ण_अगर
	अस्थिर पूर्णांक		nop_poपूर्णांक,num_recv_buffs;
	अस्थिर अक्षर		*xmit_cbuffs[NUM_XMIT_BUFFS];
	अस्थिर पूर्णांक		xmit_count,xmit_last;
पूर्ण;

/**********************************************
 * बंद device
 */
अटल पूर्णांक sun3_82586_बंद(काष्ठा net_device *dev)
अणु
	मुक्त_irq(dev->irq, dev);

	sun3_reset586(); /* the hard way to stop the receiver */

	netअगर_stop_queue(dev);

	वापस 0;
पूर्ण

/**********************************************
 * खोलो device
 */
अटल पूर्णांक sun3_82586_खोलो(काष्ठा net_device *dev)
अणु
	पूर्णांक ret;

	sun3_disपूर्णांक();
	alloc586(dev);
	init586(dev);
	startrecv586(dev);
	sun3_enaपूर्णांक();

	ret = request_irq(dev->irq, sun3_82586_पूर्णांकerrupt,0,dev->name,dev);
	अगर (ret)
	अणु
		sun3_reset586();
		वापस ret;
	पूर्ण

	netअगर_start_queue(dev);

	वापस 0; /* most करोne by init */
पूर्ण

/**********************************************
 * Check to see अगर there's an 82586 out there.
 */
अटल पूर्णांक check586(काष्ठा net_device *dev,अक्षर *where,अचिन्हित size)
अणु
	काष्ठा priv pb;
	काष्ठा priv *p = &pb;
	अक्षर *iscp_addr;
	पूर्णांक i;

	p->base = (अचिन्हित दीर्घ) dvma_btov(0);
	p->memtop = (अक्षर *)dvma_btov((अचिन्हित दीर्घ)where);
	p->scp = (काष्ठा scp_काष्ठा *)(p->base + SCP_DEFAULT_ADDRESS);
	स_रखो((अक्षर *)p->scp,0, माप(काष्ठा scp_काष्ठा));
	क्रम(i=0;i<माप(काष्ठा scp_काष्ठा);i++) /* memory was ग_लिखोable? */
		अगर(((अक्षर *)p->scp)[i])
			वापस 0;
	p->scp->sysbus = SYSBUSVAL;				/* 1 = 8Bit-Bus, 0 = 16 Bit */
	अगर(p->scp->sysbus != SYSBUSVAL)
		वापस 0;

	iscp_addr = (अक्षर *)dvma_btov((अचिन्हित दीर्घ)where);

	p->iscp = (काष्ठा iscp_काष्ठा *) iscp_addr;
	स_रखो((अक्षर *)p->iscp,0, माप(काष्ठा iscp_काष्ठा));

	p->scp->iscp = make24(p->iscp);
	p->iscp->busy = 1;

	sun3_reset586();
	sun3_attn586();
	DELAY(1);	/* रुको a जबतक... */

	अगर(p->iscp->busy) /* i82586 clears 'busy' after successful init */
		वापस 0;

	वापस 1;
पूर्ण

/******************************************************************
 * set iscp at the right place, called by sun3_82586_probe1 and खोलो586.
 */
अटल व्योम alloc586(काष्ठा net_device *dev)
अणु
	काष्ठा priv *p = netdev_priv(dev);

	sun3_reset586();
	DELAY(1);

	p->scp	= (काष्ठा scp_काष्ठा *)	(p->base + SCP_DEFAULT_ADDRESS);
	p->iscp	= (काष्ठा iscp_काष्ठा *) dvma_btov(dev->mem_start);
	p->scb  = (काष्ठा scb_काष्ठा *)  ((अक्षर *)p->iscp + माप(काष्ठा iscp_काष्ठा));

	स_रखो((अक्षर *) p->iscp,0,माप(काष्ठा iscp_काष्ठा));
	स_रखो((अक्षर *) p->scp ,0,माप(काष्ठा scp_काष्ठा));

	p->scp->iscp = make24(p->iscp);
	p->scp->sysbus = SYSBUSVAL;
	p->iscp->scb_offset = make16(p->scb);
	p->iscp->scb_base = make24(dvma_btov(dev->mem_start));

	p->iscp->busy = 1;
	sun3_reset586();
	sun3_attn586();

	DELAY(1);

	अगर(p->iscp->busy)
		prपूर्णांकk("%s: Init-Problems (alloc).\n",dev->name);

	p->reseted = 0;

	स_रखो((अक्षर *)p->scb,0,माप(काष्ठा scb_काष्ठा));
पूर्ण

काष्ठा net_device * __init sun3_82586_probe(पूर्णांक unit)
अणु
	काष्ठा net_device *dev;
	अचिन्हित दीर्घ ioaddr;
	अटल पूर्णांक found = 0;
	पूर्णांक err = -ENOMEM;

	/* check that this machine has an onboard 82586 */
	चयन(idprom->id_machtype) अणु
	हाल SM_SUN3|SM_3_160:
	हाल SM_SUN3|SM_3_260:
		/* these machines have 82586 */
		अवरोध;

	शेष:
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	अगर (found)
		वापस ERR_PTR(-ENODEV);

	ioaddr = (अचिन्हित दीर्घ)ioremap(IE_OBIO, SUN3_82586_TOTAL_SIZE);
	अगर (!ioaddr)
		वापस ERR_PTR(-ENOMEM);
	found = 1;

	dev = alloc_etherdev(माप(काष्ठा priv));
	अगर (!dev)
		जाओ out;
	अगर (unit >= 0) अणु
		प्र_लिखो(dev->name, "eth%d", unit);
		netdev_boot_setup_check(dev);
	पूर्ण

	dev->irq = IE_IRQ;
	dev->base_addr = ioaddr;
	err = sun3_82586_probe1(dev, ioaddr);
	अगर (err)
		जाओ out1;
	err = रेजिस्टर_netdev(dev);
	अगर (err)
		जाओ out2;
	वापस dev;

out2:
	release_region(ioaddr, SUN3_82586_TOTAL_SIZE);
out1:
	मुक्त_netdev(dev);
out:
	iounmap((व्योम __iomem *)ioaddr);
	वापस ERR_PTR(err);
पूर्ण

अटल स्थिर काष्ठा net_device_ops sun3_82586_netdev_ops = अणु
	.nकरो_खोलो		= sun3_82586_खोलो,
	.nकरो_stop		= sun3_82586_बंद,
	.nकरो_start_xmit		= sun3_82586_send_packet,
	.nकरो_set_rx_mode	= set_multicast_list,
	.nकरो_tx_समयout		= sun3_82586_समयout,
	.nकरो_get_stats		= sun3_82586_get_stats,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
पूर्ण;

अटल पूर्णांक __init sun3_82586_probe1(काष्ठा net_device *dev,पूर्णांक ioaddr)
अणु
	पूर्णांक i, size, retval;

	अगर (!request_region(ioaddr, SUN3_82586_TOTAL_SIZE, DRV_NAME))
		वापस -EBUSY;

	/* copy in the ethernet address from the prom */
	क्रम(i = 0; i < 6 ; i++)
	     dev->dev_addr[i] = idprom->id_ethaddr[i];

	prपूर्णांकk("%s: SUN3 Intel 82586 found at %lx, ",dev->name,dev->base_addr);

	/*
	 * check (or search) IO-Memory, 32K
	 */
	size = 0x8000;

	dev->mem_start = (अचिन्हित दीर्घ)dvma_दो_स्मृति_align(0x8000, 0x1000);
	dev->mem_end = dev->mem_start + size;

	अगर(size != 0x2000 && size != 0x4000 && size != 0x8000) अणु
		prपूर्णांकk("\n%s: Illegal memory size %d. Allowed is 0x2000 or 0x4000 or 0x8000 bytes.\n",dev->name,size);
		retval = -ENODEV;
		जाओ out;
	पूर्ण
	अगर(!check586(dev,(अक्षर *) dev->mem_start,size)) अणु
		prपूर्णांकk("?memcheck, Can't find memory at 0x%lx with size %d!\n",dev->mem_start,size);
		retval = -ENODEV;
		जाओ out;
	पूर्ण

	((काष्ठा priv *)netdev_priv(dev))->memtop =
					(अक्षर *)dvma_btov(dev->mem_start);
	((काष्ठा priv *)netdev_priv(dev))->base = (अचिन्हित दीर्घ) dvma_btov(0);
	alloc586(dev);

	/* set number of receive-buffs according to memsize */
	अगर(size == 0x2000)
		((काष्ठा priv *)netdev_priv(dev))->num_recv_buffs =
							NUM_RECV_BUFFS_8;
	अन्यथा अगर(size == 0x4000)
		((काष्ठा priv *)netdev_priv(dev))->num_recv_buffs =
							NUM_RECV_BUFFS_16;
	अन्यथा
		((काष्ठा priv *)netdev_priv(dev))->num_recv_buffs =
							NUM_RECV_BUFFS_32;

	prपूर्णांकk("Memaddr: 0x%lx, Memsize: %d, IRQ %d\n",dev->mem_start,size, dev->irq);

	dev->netdev_ops		= &sun3_82586_netdev_ops;
	dev->watchकरोg_समयo	= HZ/20;

	dev->अगर_port 		= 0;
	वापस 0;
out:
	release_region(ioaddr, SUN3_82586_TOTAL_SIZE);
	वापस retval;
पूर्ण


अटल पूर्णांक init586(काष्ठा net_device *dev)
अणु
	व्योम *ptr;
	पूर्णांक i,result=0;
	काष्ठा priv *p = netdev_priv(dev);
	अस्थिर काष्ठा configure_cmd_काष्ठा	*cfg_cmd;
	अस्थिर काष्ठा iasetup_cmd_काष्ठा *ias_cmd;
	अस्थिर काष्ठा tdr_cmd_काष्ठा *tdr_cmd;
	अस्थिर काष्ठा mcsetup_cmd_काष्ठा *mc_cmd;
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक num_addrs=netdev_mc_count(dev);

	ptr = (व्योम *) ((अक्षर *)p->scb + माप(काष्ठा scb_काष्ठा));

	cfg_cmd = (काष्ठा configure_cmd_काष्ठा *)ptr; /* configure-command */
	cfg_cmd->cmd_status	= 0;
	cfg_cmd->cmd_cmd	= swab16(CMD_CONFIGURE | CMD_LAST);
	cfg_cmd->cmd_link	= 0xffff;

	cfg_cmd->byte_cnt	= 0x0a; /* number of cfg bytes */
	cfg_cmd->fअगरo		= fअगरo; /* fअगरo-limit (8=tx:32/rx:64) */
	cfg_cmd->sav_bf		= 0x40; /* hold or discard bad recv frames (bit 7) */
	cfg_cmd->adr_len	= 0x2e; /* addr_len |!src_insert |pre-len |loopback */
	cfg_cmd->priority	= 0x00;
	cfg_cmd->अगरs		= 0x60;
	cfg_cmd->समय_low	= 0x00;
	cfg_cmd->समय_high	= 0xf2;
	cfg_cmd->promisc	= 0;
	अगर(dev->flags & IFF_ALLMULTI) अणु
		पूर्णांक len = ((अक्षर *) p->iscp - (अक्षर *) ptr - 8) / 6;
		अगर(num_addrs > len)	अणु
			prपूर्णांकk("%s: switching to promisc. mode\n",dev->name);
			cfg_cmd->promisc = 1;
		पूर्ण
	पूर्ण
	अगर(dev->flags&IFF_PROMISC)
		cfg_cmd->promisc = 1;
	cfg_cmd->carr_coll	= 0x00;

	p->scb->cbl_offset	= make16(cfg_cmd);
	p->scb->cmd_ruc		= 0;

	p->scb->cmd_cuc		= CUC_START; /* cmd.-unit start */
	sun3_attn586();

	WAIT_4_STAT_COMPL(cfg_cmd);

	अगर((swab16(cfg_cmd->cmd_status) & (STAT_OK|STAT_COMPL)) != (STAT_COMPL|STAT_OK))
	अणु
		prपूर्णांकk("%s: configure command failed: %x\n",dev->name,swab16(cfg_cmd->cmd_status));
		वापस 1;
	पूर्ण

	/*
	 * inभागidual address setup
	 */

	ias_cmd = (काष्ठा iasetup_cmd_काष्ठा *)ptr;

	ias_cmd->cmd_status	= 0;
	ias_cmd->cmd_cmd	= swab16(CMD_IASETUP | CMD_LAST);
	ias_cmd->cmd_link	= 0xffff;

	स_नकल((अक्षर *)&ias_cmd->iaddr,(अक्षर *) dev->dev_addr,ETH_ALEN);

	p->scb->cbl_offset = make16(ias_cmd);

	p->scb->cmd_cuc = CUC_START; /* cmd.-unit start */
	sun3_attn586();

	WAIT_4_STAT_COMPL(ias_cmd);

	अगर((swab16(ias_cmd->cmd_status) & (STAT_OK|STAT_COMPL)) != (STAT_OK|STAT_COMPL)) अणु
		prपूर्णांकk("%s (82586): individual address setup command failed: %04x\n",dev->name,swab16(ias_cmd->cmd_status));
		वापस 1;
	पूर्ण

	/*
	 * TDR, wire check .. e.g. no resistor e.t.c
	 */

	tdr_cmd = (काष्ठा tdr_cmd_काष्ठा *)ptr;

	tdr_cmd->cmd_status	= 0;
	tdr_cmd->cmd_cmd	= swab16(CMD_TDR | CMD_LAST);
	tdr_cmd->cmd_link	= 0xffff;
	tdr_cmd->status		= 0;

	p->scb->cbl_offset = make16(tdr_cmd);
	p->scb->cmd_cuc = CUC_START; /* cmd.-unit start */
	sun3_attn586();

	WAIT_4_STAT_COMPL(tdr_cmd);

	अगर(!(swab16(tdr_cmd->cmd_status) & STAT_COMPL))
	अणु
		prपूर्णांकk("%s: Problems while running the TDR.\n",dev->name);
	पूर्ण
	अन्यथा
	अणु
		DELAY_16(); /* रुको क्रम result */
		result = swab16(tdr_cmd->status);

		p->scb->cmd_cuc = p->scb->cus & STAT_MASK;
		sun3_attn586(); /* ack the पूर्णांकerrupts */

		अगर(result & TDR_LNK_OK)
			;
		अन्यथा अगर(result & TDR_XCVR_PRB)
			prपूर्णांकk("%s: TDR: Transceiver problem. Check the cable(s)!\n",dev->name);
		अन्यथा अगर(result & TDR_ET_OPN)
			prपूर्णांकk("%s: TDR: No correct termination %d clocks away.\n",dev->name,result & TDR_TIMEMASK);
		अन्यथा अगर(result & TDR_ET_SRT)
		अणु
			अगर (result & TDR_TIMEMASK) /* समय == 0 -> strange :-) */
				prपूर्णांकk("%s: TDR: Detected a short circuit %d clocks away.\n",dev->name,result & TDR_TIMEMASK);
		पूर्ण
		अन्यथा
			prपूर्णांकk("%s: TDR: Unknown status %04x\n",dev->name,result);
	पूर्ण

	/*
	 * Multicast setup
	 */
	अगर(num_addrs && !(dev->flags & IFF_PROMISC) )
	अणु
		mc_cmd = (काष्ठा mcsetup_cmd_काष्ठा *) ptr;
		mc_cmd->cmd_status = 0;
		mc_cmd->cmd_cmd = swab16(CMD_MCSETUP | CMD_LAST);
		mc_cmd->cmd_link = 0xffff;
		mc_cmd->mc_cnt = swab16(num_addrs * 6);

		i = 0;
		netdev_क्रम_each_mc_addr(ha, dev)
			स_नकल((अक्षर *) mc_cmd->mc_list[i++],
			       ha->addr, ETH_ALEN);

		p->scb->cbl_offset = make16(mc_cmd);
		p->scb->cmd_cuc = CUC_START;
		sun3_attn586();

		WAIT_4_STAT_COMPL(mc_cmd);

		अगर( (swab16(mc_cmd->cmd_status) & (STAT_COMPL|STAT_OK)) != (STAT_COMPL|STAT_OK) )
			prपूर्णांकk("%s: Can't apply multicast-address-list.\n",dev->name);
	पूर्ण

	/*
	 * alloc nop/xmit-cmds
	 */
#अगर (NUM_XMIT_BUFFS == 1)
	क्रम(i=0;i<2;i++)
	अणु
		p->nop_cmds[i] 			= (काष्ठा nop_cmd_काष्ठा *)ptr;
		p->nop_cmds[i]->cmd_cmd		= swab16(CMD_NOP);
		p->nop_cmds[i]->cmd_status 	= 0;
		p->nop_cmds[i]->cmd_link	= make16((p->nop_cmds[i]));
		ptr = (अक्षर *) ptr + माप(काष्ठा nop_cmd_काष्ठा);
	पूर्ण
#अन्यथा
	क्रम(i=0;i<NUM_XMIT_BUFFS;i++)
	अणु
		p->nop_cmds[i]			= (काष्ठा nop_cmd_काष्ठा *)ptr;
		p->nop_cmds[i]->cmd_cmd		= swab16(CMD_NOP);
		p->nop_cmds[i]->cmd_status	= 0;
		p->nop_cmds[i]->cmd_link	= make16((p->nop_cmds[i]));
		ptr = (अक्षर *) ptr + माप(काष्ठा nop_cmd_काष्ठा);
	पूर्ण
#पूर्ण_अगर

	ptr = alloc_rfa(dev,ptr); /* init receive-frame-area */

	/*
	 * alloc xmit-buffs / init xmit_cmds
	 */
	क्रम(i=0;i<NUM_XMIT_BUFFS;i++)
	अणु
		p->xmit_cmds[i] = (काष्ठा transmit_cmd_काष्ठा *)ptr; /*transmit cmd/buff 0*/
		ptr = (अक्षर *) ptr + माप(काष्ठा transmit_cmd_काष्ठा);
		p->xmit_cbuffs[i] = (अक्षर *)ptr; /* अक्षर-buffs */
		ptr = (अक्षर *) ptr + XMIT_BUFF_SIZE;
		p->xmit_buffs[i] = (काष्ठा tbd_काष्ठा *)ptr; /* TBD */
		ptr = (अक्षर *) ptr + माप(काष्ठा tbd_काष्ठा);
		अगर(ptr > (व्योम *)dev->mem_end)
		अणु
			prपूर्णांकk("%s: not enough shared-mem for your configuration!\n",dev->name);
			वापस 1;
		पूर्ण
		स_रखो((अक्षर *)(p->xmit_cmds[i]) ,0, माप(काष्ठा transmit_cmd_काष्ठा));
		स_रखो((अक्षर *)(p->xmit_buffs[i]),0, माप(काष्ठा tbd_काष्ठा));
		p->xmit_cmds[i]->cmd_link = make16(p->nop_cmds[(i+1)%NUM_XMIT_BUFFS]);
		p->xmit_cmds[i]->cmd_status = swab16(STAT_COMPL);
		p->xmit_cmds[i]->cmd_cmd = swab16(CMD_XMIT | CMD_INT);
		p->xmit_cmds[i]->tbd_offset = make16((p->xmit_buffs[i]));
		p->xmit_buffs[i]->next = 0xffff;
		p->xmit_buffs[i]->buffer = make24((p->xmit_cbuffs[i]));
	पूर्ण

	p->xmit_count = 0;
	p->xmit_last	= 0;
#अगर_अघोषित NO_NOPCOMMANDS
	p->nop_poपूर्णांक	= 0;
#पूर्ण_अगर

	 /*
		* 'start transmitter'
		*/
#अगर_अघोषित NO_NOPCOMMANDS
	p->scb->cbl_offset = make16(p->nop_cmds[0]);
	p->scb->cmd_cuc = CUC_START;
	sun3_attn586();
	WAIT_4_SCB_CMD();
#अन्यथा
	p->xmit_cmds[0]->cmd_link = make16(p->xmit_cmds[0]);
	p->xmit_cmds[0]->cmd_cmd	= swab16(CMD_XMIT | CMD_SUSPEND | CMD_INT);
#पूर्ण_अगर

	/*
	 * ack. पूर्णांकerrupts
	 */
	p->scb->cmd_cuc = p->scb->cus & STAT_MASK;
	sun3_attn586();
	DELAY_16();

	sun3_enaपूर्णांक();
	sun3_active();

	वापस 0;
पूर्ण

/******************************************************
 * This is a helper routine क्रम sun3_82586_rnr_पूर्णांक() and init586().
 * It sets up the Receive Frame Area (RFA).
 */

अटल व्योम *alloc_rfa(काष्ठा net_device *dev,व्योम *ptr)
अणु
	अस्थिर काष्ठा rfd_काष्ठा *rfd = (काष्ठा rfd_काष्ठा *)ptr;
	अस्थिर काष्ठा rbd_काष्ठा *rbd;
	पूर्णांक i;
	काष्ठा priv *p = netdev_priv(dev);

	स_रखो((अक्षर *) rfd,0,माप(काष्ठा rfd_काष्ठा)*(p->num_recv_buffs+rfdadd));
	p->rfd_first = rfd;

	क्रम(i = 0; i < (p->num_recv_buffs+rfdadd); i++) अणु
		rfd[i].next = make16(rfd + (i+1) % (p->num_recv_buffs+rfdadd) );
		rfd[i].rbd_offset = 0xffff;
	पूर्ण
	rfd[p->num_recv_buffs-1+rfdadd].last = RFD_SUSP;	 /* RU suspend */

	ptr = (व्योम *) (rfd + (p->num_recv_buffs + rfdadd) );

	rbd = (काष्ठा rbd_काष्ठा *) ptr;
	ptr = (व्योम *) (rbd + p->num_recv_buffs);

	 /* clr descriptors */
	स_रखो((अक्षर *) rbd,0,माप(काष्ठा rbd_काष्ठा)*(p->num_recv_buffs));

	क्रम(i=0;i<p->num_recv_buffs;i++)
	अणु
		rbd[i].next = make16((rbd + (i+1) % p->num_recv_buffs));
		rbd[i].size = swab16(RECV_BUFF_SIZE);
		rbd[i].buffer = make24(ptr);
		ptr = (अक्षर *) ptr + RECV_BUFF_SIZE;
	पूर्ण

	p->rfd_top	= p->rfd_first;
	p->rfd_last = p->rfd_first + (p->num_recv_buffs - 1 + rfdadd);

	p->scb->rfa_offset		= make16(p->rfd_first);
	p->rfd_first->rbd_offset	= make16(rbd);

	वापस ptr;
पूर्ण


/**************************************************
 * Interrupt Handler ...
 */

अटल irqवापस_t sun3_82586_पूर्णांकerrupt(पूर्णांक irq,व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	अचिन्हित लघु stat;
	पूर्णांक cnt=0;
	काष्ठा priv *p;

	अगर (!dev) अणु
		prपूर्णांकk ("sun3_82586-interrupt: irq %d for unknown device.\n",irq);
		वापस IRQ_NONE;
	पूर्ण
	p = netdev_priv(dev);

	अगर(debuglevel > 1)
		prपूर्णांकk("I");

	WAIT_4_SCB_CMD(); /* रुको क्रम last command	*/

	जबतक((stat=p->scb->cus & STAT_MASK))
	अणु
		p->scb->cmd_cuc = stat;
		sun3_attn586();

		अगर(stat & STAT_FR)	 /* received a frame */
			sun3_82586_rcv_पूर्णांक(dev);

		अगर(stat & STAT_RNR) /* RU went 'not ready' */
		अणु
			prपूर्णांकk("(R)");
			अगर(p->scb->rus & RU_SUSPEND) /* special हाल: RU_SUSPEND */
			अणु
				WAIT_4_SCB_CMD();
				p->scb->cmd_ruc = RUC_RESUME;
				sun3_attn586();
				WAIT_4_SCB_CMD_RUC();
			पूर्ण
			अन्यथा
			अणु
				prपूर्णांकk("%s: Receiver-Unit went 'NOT READY': %04x/%02x.\n",dev->name,(पूर्णांक) stat,(पूर्णांक) p->scb->rus);
				sun3_82586_rnr_पूर्णांक(dev);
			पूर्ण
		पूर्ण

		अगर(stat & STAT_CX)		/* command with I-bit set complete */
			 sun3_82586_xmt_पूर्णांक(dev);

#अगर_अघोषित NO_NOPCOMMANDS
		अगर(stat & STAT_CNA)	/* CU went 'not ready' */
		अणु
			अगर(netअगर_running(dev))
				prपूर्णांकk("%s: oops! CU has left active state. stat: %04x/%02x.\n",dev->name,(पूर्णांक) stat,(पूर्णांक) p->scb->cus);
		पूर्ण
#पूर्ण_अगर

		अगर(debuglevel > 1)
			prपूर्णांकk("%d",cnt++);

		WAIT_4_SCB_CMD(); /* रुको क्रम ack. (sun3_82586_xmt_पूर्णांक can be faster than ack!!) */
		अगर(p->scb->cmd_cuc)	 /* समयd out? */
		अणु
			prपूर्णांकk("%s: Acknowledge timed out.\n",dev->name);
			sun3_disपूर्णांक();
			अवरोध;
		पूर्ण
	पूर्ण

	अगर(debuglevel > 1)
		prपूर्णांकk("i");
	वापस IRQ_HANDLED;
पूर्ण

/*******************************************************
 * receive-पूर्णांकerrupt
 */

अटल व्योम sun3_82586_rcv_पूर्णांक(काष्ठा net_device *dev)
अणु
	पूर्णांक status,cnt=0;
	अचिन्हित लघु totlen;
	काष्ठा sk_buff *skb;
	काष्ठा rbd_काष्ठा *rbd;
	काष्ठा priv *p = netdev_priv(dev);

	अगर(debuglevel > 0)
		prपूर्णांकk("R");

	क्रम(;(status = p->rfd_top->stat_high) & RFD_COMPL;)
	अणु
			rbd = (काष्ठा rbd_काष्ठा *) make32(p->rfd_top->rbd_offset);

			अगर(status & RFD_OK) /* frame received without error? */
			अणु
				अगर( (totlen = swab16(rbd->status)) & RBD_LAST) /* the first and the last buffer? */
				अणु
					totlen &= RBD_MASK; /* length of this frame */
					rbd->status = 0;
					skb = netdev_alloc_skb(dev, totlen + 2);
					अगर(skb != शून्य)
					अणु
						skb_reserve(skb,2);
						skb_put(skb,totlen);
						skb_copy_to_linear_data(skb,(अक्षर *) p->base+swab32((अचिन्हित दीर्घ) rbd->buffer),totlen);
						skb->protocol=eth_type_trans(skb,dev);
						netअगर_rx(skb);
						dev->stats.rx_packets++;
					पूर्ण
					अन्यथा
						dev->stats.rx_dropped++;
				पूर्ण
				अन्यथा
				अणु
					पूर्णांक rstat;
						 /* मुक्त all RBD's until RBD_LAST is set */
					totlen = 0;
					जबतक(!((rstat=swab16(rbd->status)) & RBD_LAST))
					अणु
						totlen += rstat & RBD_MASK;
						अगर(!rstat)
						अणु
							prपूर्णांकk("%s: Whoops .. no end mark in RBD list\n",dev->name);
							अवरोध;
						पूर्ण
						rbd->status = 0;
						rbd = (काष्ठा rbd_काष्ठा *) make32(rbd->next);
					पूर्ण
					totlen += rstat & RBD_MASK;
					rbd->status = 0;
					prपूर्णांकk("%s: received oversized frame! length: %d\n",dev->name,totlen);
					dev->stats.rx_dropped++;
			 पूर्ण
		पूर्ण
		अन्यथा /* frame !(ok), only with 'save-bad-frames' */
		अणु
			prपूर्णांकk("%s: oops! rfd-error-status: %04x\n",dev->name,status);
			dev->stats.rx_errors++;
		पूर्ण
		p->rfd_top->stat_high = 0;
		p->rfd_top->last = RFD_SUSP; /* maybe exchange by RFD_LAST */
		p->rfd_top->rbd_offset = 0xffff;
		p->rfd_last->last = 0;				/* delete RFD_SUSP	*/
		p->rfd_last = p->rfd_top;
		p->rfd_top = (काष्ठा rfd_काष्ठा *) make32(p->rfd_top->next); /* step to next RFD */
		p->scb->rfa_offset = make16(p->rfd_top);

		अगर(debuglevel > 0)
			prपूर्णांकk("%d",cnt++);
	पूर्ण

	अगर(स्वतःmatic_resume)
	अणु
		WAIT_4_SCB_CMD();
		p->scb->cmd_ruc = RUC_RESUME;
		sun3_attn586();
		WAIT_4_SCB_CMD_RUC();
	पूर्ण

#अगर_घोषित WAIT_4_BUSY
	अणु
		पूर्णांक i;
		क्रम(i=0;i<1024;i++)
		अणु
			अगर(p->rfd_top->status)
				अवरोध;
			DELAY_16();
			अगर(i == 1023)
				prपूर्णांकk("%s: RU hasn't fetched next RFD (not busy/complete)\n",dev->name);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

#अगर 0
	अगर(!at_least_one)
	अणु
		पूर्णांक i;
		अस्थिर काष्ठा rfd_काष्ठा *rfds=p->rfd_top;
		अस्थिर काष्ठा rbd_काष्ठा *rbds;
		prपूर्णांकk("%s: received a FC intr. without having a frame: %04x %d\n",dev->name,status,old_at_least);
		क्रम(i=0;i< (p->num_recv_buffs+4);i++)
		अणु
			rbds = (काष्ठा rbd_काष्ठा *) make32(rfds->rbd_offset);
			prपूर्णांकk("%04x:%04x ",rfds->status,rbds->status);
			rfds = (काष्ठा rfd_काष्ठा *) make32(rfds->next);
		पूर्ण
		prपूर्णांकk("\nerrs: %04x %04x stat: %04x\n",(पूर्णांक)p->scb->rsc_errs,(पूर्णांक)p->scb->ovrn_errs,(पूर्णांक)p->scb->status);
		prपूर्णांकk("\nerrs: %04x %04x rus: %02x, cus: %02x\n",(पूर्णांक)p->scb->rsc_errs,(पूर्णांक)p->scb->ovrn_errs,(पूर्णांक)p->scb->rus,(पूर्णांक)p->scb->cus);
	पूर्ण
	old_at_least = at_least_one;
#पूर्ण_अगर

	अगर(debuglevel > 0)
		prपूर्णांकk("r");
पूर्ण

/**********************************************************
 * handle 'Receiver went not ready'.
 */

अटल व्योम sun3_82586_rnr_पूर्णांक(काष्ठा net_device *dev)
अणु
	काष्ठा priv *p = netdev_priv(dev);

	dev->stats.rx_errors++;

	WAIT_4_SCB_CMD();		/* रुको क्रम the last cmd, WAIT_4_FULLSTAT?? */
	p->scb->cmd_ruc = RUC_ABORT; /* usually the RU is in the 'no resource'-state .. पात it now. */
	sun3_attn586();
	WAIT_4_SCB_CMD_RUC();		/* रुको क्रम accept cmd. */

	alloc_rfa(dev,(अक्षर *)p->rfd_first);
/* maybe add a check here, beक्रमe restarting the RU */
	startrecv586(dev); /* restart RU */

	prपूर्णांकk("%s: Receive-Unit restarted. Status: %04x\n",dev->name,p->scb->rus);

पूर्ण

/**********************************************************
 * handle xmit - पूर्णांकerrupt
 */

अटल व्योम sun3_82586_xmt_पूर्णांक(काष्ठा net_device *dev)
अणु
	पूर्णांक status;
	काष्ठा priv *p = netdev_priv(dev);

	अगर(debuglevel > 0)
		prपूर्णांकk("X");

	status = swab16(p->xmit_cmds[p->xmit_last]->cmd_status);
	अगर(!(status & STAT_COMPL))
		prपूर्णांकk("%s: strange .. xmit-int without a 'COMPLETE'\n",dev->name);

	अगर(status & STAT_OK)
	अणु
		dev->stats.tx_packets++;
		dev->stats.collisions += (status & TCMD_MAXCOLLMASK);
	पूर्ण
	अन्यथा
	अणु
		dev->stats.tx_errors++;
		अगर(status & TCMD_LATECOLL) अणु
			prपूर्णांकk("%s: late collision detected.\n",dev->name);
			dev->stats.collisions++;
		पूर्ण
		अन्यथा अगर(status & TCMD_NOCARRIER) अणु
			dev->stats.tx_carrier_errors++;
			prपूर्णांकk("%s: no carrier detected.\n",dev->name);
		पूर्ण
		अन्यथा अगर(status & TCMD_LOSTCTS)
			prपूर्णांकk("%s: loss of CTS detected.\n",dev->name);
		अन्यथा अगर(status & TCMD_UNDERRUN) अणु
			dev->stats.tx_fअगरo_errors++;
			prपूर्णांकk("%s: DMA underrun detected.\n",dev->name);
		पूर्ण
		अन्यथा अगर(status & TCMD_MAXCOLL) अणु
			prपूर्णांकk("%s: Max. collisions exceeded.\n",dev->name);
			dev->stats.collisions += 16;
		पूर्ण
	पूर्ण

#अगर (NUM_XMIT_BUFFS > 1)
	अगर( (++p->xmit_last) == NUM_XMIT_BUFFS)
		p->xmit_last = 0;
#पूर्ण_अगर
	netअगर_wake_queue(dev);
पूर्ण

/***********************************************************
 * (re)start the receiver
 */

अटल व्योम startrecv586(काष्ठा net_device *dev)
अणु
	काष्ठा priv *p = netdev_priv(dev);

	WAIT_4_SCB_CMD();
	WAIT_4_SCB_CMD_RUC();
	p->scb->rfa_offset = make16(p->rfd_first);
	p->scb->cmd_ruc = RUC_START;
	sun3_attn586();		/* start cmd. */
	WAIT_4_SCB_CMD_RUC();	/* रुको क्रम accept cmd. (no समयout!!) */
पूर्ण

अटल व्योम sun3_82586_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा priv *p = netdev_priv(dev);
#अगर_अघोषित NO_NOPCOMMANDS
	अगर(p->scb->cus & CU_ACTIVE) /* COMMAND-UNIT active? */
	अणु
		netअगर_wake_queue(dev);
#अगर_घोषित DEBUG
		prपूर्णांकk("%s: strange ... timeout with CU active?!?\n",dev->name);
		prपूर्णांकk("%s: X0: %04x N0: %04x N1: %04x %d\n",dev->name,(पूर्णांक)swab16(p->xmit_cmds[0]->cmd_status),(पूर्णांक)swab16(p->nop_cmds[0]->cmd_status),(पूर्णांक)swab16(p->nop_cmds[1]->cmd_status),(पूर्णांक)p->nop_poपूर्णांक);
#पूर्ण_अगर
		p->scb->cmd_cuc = CUC_ABORT;
		sun3_attn586();
		WAIT_4_SCB_CMD();
		p->scb->cbl_offset = make16(p->nop_cmds[p->nop_poपूर्णांक]);
		p->scb->cmd_cuc = CUC_START;
		sun3_attn586();
		WAIT_4_SCB_CMD();
		netअगर_trans_update(dev); /* prevent tx समयout */
		वापस 0;
	पूर्ण
#पूर्ण_अगर
	अणु
#अगर_घोषित DEBUG
		prपूर्णांकk("%s: xmitter timed out, try to restart! stat: %02x\n",dev->name,p->scb->cus);
		prपूर्णांकk("%s: command-stats: %04x %04x\n",dev->name,swab16(p->xmit_cmds[0]->cmd_status),swab16(p->xmit_cmds[1]->cmd_status));
		prपूर्णांकk("%s: check, whether you set the right interrupt number!\n",dev->name);
#पूर्ण_अगर
		sun3_82586_बंद(dev);
		sun3_82586_खोलो(dev);
	पूर्ण
	netअगर_trans_update(dev); /* prevent tx समयout */
पूर्ण

/******************************************************
 * send frame
 */

अटल netdev_tx_t
sun3_82586_send_packet(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	पूर्णांक len,i;
#अगर_अघोषित NO_NOPCOMMANDS
	पूर्णांक next_nop;
#पूर्ण_अगर
	काष्ठा priv *p = netdev_priv(dev);

	अगर(skb->len > XMIT_BUFF_SIZE)
	अणु
		prपूर्णांकk("%s: Sorry, max. framelength is %d bytes. The length of your frame is %d bytes.\n",dev->name,XMIT_BUFF_SIZE,skb->len);
		वापस NETDEV_TX_OK;
	पूर्ण

	netअगर_stop_queue(dev);

#अगर(NUM_XMIT_BUFFS > 1)
	अगर(test_and_set_bit(0,(व्योम *) &p->lock)) अणु
		prपूर्णांकk("%s: Queue was locked\n",dev->name);
		वापस NETDEV_TX_BUSY;
	पूर्ण
	अन्यथा
#पूर्ण_अगर
	अणु
		len = skb->len;
		अगर (len < ETH_ZLEN) अणु
			स_रखो((व्योम *)p->xmit_cbuffs[p->xmit_count], 0,
			       ETH_ZLEN);
			len = ETH_ZLEN;
		पूर्ण
		skb_copy_from_linear_data(skb, (व्योम *)p->xmit_cbuffs[p->xmit_count], skb->len);

#अगर (NUM_XMIT_BUFFS == 1)
#	अगरdef NO_NOPCOMMANDS

#अगर_घोषित DEBUG
		अगर(p->scb->cus & CU_ACTIVE)
		अणु
			prपूर्णांकk("%s: Hmmm .. CU is still running and we wanna send a new packet.\n",dev->name);
			prपूर्णांकk("%s: stat: %04x %04x\n",dev->name,p->scb->cus,swab16(p->xmit_cmds[0]->cmd_status));
		पूर्ण
#पूर्ण_अगर

		p->xmit_buffs[0]->size = swab16(TBD_LAST | len);
		क्रम(i=0;i<16;i++)
		अणु
			p->xmit_cmds[0]->cmd_status = 0;
			WAIT_4_SCB_CMD();
			अगर( (p->scb->cus & CU_STATUS) == CU_SUSPEND)
				p->scb->cmd_cuc = CUC_RESUME;
			अन्यथा
			अणु
				p->scb->cbl_offset = make16(p->xmit_cmds[0]);
				p->scb->cmd_cuc = CUC_START;
			पूर्ण

			sun3_attn586();
			अगर(!i)
				dev_kमुक्त_skb(skb);
			WAIT_4_SCB_CMD();
			अगर( (p->scb->cus & CU_ACTIVE)) /* test it, because CU someबार करोesn't start immediately */
				अवरोध;
			अगर(p->xmit_cmds[0]->cmd_status)
				अवरोध;
			अगर(i==15)
				prपूर्णांकk("%s: Can't start transmit-command.\n",dev->name);
		पूर्ण
#	अन्यथा
		next_nop = (p->nop_poपूर्णांक + 1) & 0x1;
		p->xmit_buffs[0]->size = swab16(TBD_LAST | len);

		p->xmit_cmds[0]->cmd_link	 = p->nop_cmds[next_nop]->cmd_link
			= make16((p->nop_cmds[next_nop]));
		p->xmit_cmds[0]->cmd_status = p->nop_cmds[next_nop]->cmd_status = 0;

		p->nop_cmds[p->nop_poपूर्णांक]->cmd_link = make16((p->xmit_cmds[0]));
		p->nop_poपूर्णांक = next_nop;
		dev_kमुक्त_skb(skb);
#	endअगर
#अन्यथा
		p->xmit_buffs[p->xmit_count]->size = swab16(TBD_LAST | len);
		अगर( (next_nop = p->xmit_count + 1) == NUM_XMIT_BUFFS )
			next_nop = 0;

		p->xmit_cmds[p->xmit_count]->cmd_status	= 0;
		/* linkpoपूर्णांकer of xmit-command alपढ़ोy poपूर्णांकs to next nop cmd */
		p->nop_cmds[next_nop]->cmd_link = make16((p->nop_cmds[next_nop]));
		p->nop_cmds[next_nop]->cmd_status = 0;

		p->nop_cmds[p->xmit_count]->cmd_link = make16((p->xmit_cmds[p->xmit_count]));
		p->xmit_count = next_nop;

		अणु
			अचिन्हित दीर्घ flags;
			local_irq_save(flags);
			अगर(p->xmit_count != p->xmit_last)
				netअगर_wake_queue(dev);
			p->lock = 0;
			local_irq_restore(flags);
		पूर्ण
		dev_kमुक्त_skb(skb);
#पूर्ण_अगर
	पूर्ण
	वापस NETDEV_TX_OK;
पूर्ण

/*******************************************
 * Someone wanna have the statistics
 */

अटल काष्ठा net_device_stats *sun3_82586_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा priv *p = netdev_priv(dev);
	अचिन्हित लघु crc,aln,rsc,ovrn;

	crc = swab16(p->scb->crc_errs); /* get error-statistic from the ni82586 */
	p->scb->crc_errs = 0;
	aln = swab16(p->scb->aln_errs);
	p->scb->aln_errs = 0;
	rsc = swab16(p->scb->rsc_errs);
	p->scb->rsc_errs = 0;
	ovrn = swab16(p->scb->ovrn_errs);
	p->scb->ovrn_errs = 0;

	dev->stats.rx_crc_errors += crc;
	dev->stats.rx_fअगरo_errors += ovrn;
	dev->stats.rx_frame_errors += aln;
	dev->stats.rx_dropped += rsc;

	वापस &dev->stats;
पूर्ण

/********************************************************
 * Set MC list ..
 */

अटल व्योम set_multicast_list(काष्ठा net_device *dev)
अणु
	netअगर_stop_queue(dev);
	sun3_disपूर्णांक();
	alloc586(dev);
	init586(dev);
	startrecv586(dev);
	sun3_enaपूर्णांक();
	netअगर_wake_queue(dev);
पूर्ण

#अगर 0
/*
 * DUMP .. we expect a not running CMD unit and enough space
 */
व्योम sun3_82586_dump(काष्ठा net_device *dev,व्योम *ptr)
अणु
	काष्ठा priv *p = netdev_priv(dev);
	काष्ठा dump_cmd_काष्ठा *dump_cmd = (काष्ठा dump_cmd_काष्ठा *) ptr;
	पूर्णांक i;

	p->scb->cmd_cuc = CUC_ABORT;
	sun3_attn586();
	WAIT_4_SCB_CMD();
	WAIT_4_SCB_CMD_RUC();

	dump_cmd->cmd_status = 0;
	dump_cmd->cmd_cmd = CMD_DUMP | CMD_LAST;
	dump_cmd->dump_offset = make16((dump_cmd + 1));
	dump_cmd->cmd_link = 0xffff;

	p->scb->cbl_offset = make16(dump_cmd);
	p->scb->cmd_cuc = CUC_START;
	sun3_attn586();
	WAIT_4_STAT_COMPL(dump_cmd);

	अगर( (dump_cmd->cmd_status & (STAT_COMPL|STAT_OK)) != (STAT_COMPL|STAT_OK) )
				prपूर्णांकk("%s: Can't get dump information.\n",dev->name);

	क्रम(i=0;i<170;i++) अणु
		prपूर्णांकk("%02x ",(पूर्णांक) ((अचिन्हित अक्षर *) (dump_cmd + 1))[i]);
		अगर(i % 24 == 23)
			prपूर्णांकk("\n");
	पूर्ण
	prपूर्णांकk("\n");
पूर्ण
#पूर्ण_अगर
