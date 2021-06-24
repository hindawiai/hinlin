<शैली गुरु>
/*----------------------------------------------------------------*/
/*
   Qlogic linux driver - work in progress. No Warranty express or implied.
   Use at your own risk.  Support Tort Reक्रमm so you won't have to पढ़ो all
   these silly disclaimers.

   Copyright 1994, Tom Zerucha.   
   tz@execpc.com
   
   Additional Code, and much appreciated help by
   Michael A. Grअगरfith
   grअगर@cs.ucr.edu

   Thanks to Eric Youngdale and Dave Hinds क्रम loadable module and PCMCIA
   help respectively, and क्रम suffering through my foolishness during the
   debugging process.

   Reference Qlogic FAS408 Technical Manual, 53408-510-00A, May 10, 1994
   (you can reference it, but it is incomplete and inaccurate in places)

   Version 0.46 1/30/97 - kernel 1.2.0+

   Functions as standalone, loadable, and PCMCIA driver, the latter from
   Dave Hinds' PCMCIA package.
   
   Cleaned up 26/10/2002 by Alan Cox <alan@lxorguk.ukuu.org.uk> as part of the 2.5
   SCSI driver cleanup and audit. This driver still needs work on the
   following
   	-	Non terminating hardware रुकोs
   	-	Some layering violations with its pcmcia stub

   Redistributable under terms of the GNU General Public License

   For the aव्योमance of करोubt the "preferred form" of this code is one which
   is in an खोलो non patent encumbered क्रमmat. Where cryptographic key signing
   क्रमms part of the process of creating an executable the inक्रमmation
   including keys needed to generate an equivalently functional executable
   are deemed to be part of the source code.

*/

#समावेश <linux/module.h>
#समावेश <linux/blkdev.h>		/* to get disk capacity */
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/unistd.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/स्थिति.स>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/dma.h>

#समावेश "scsi.h"
#समावेश <scsi/scsi_host.h>
#समावेश "qlogicfas408.h"

/*----------------------------------------------------------------*/
अटल पूर्णांक qlcfg5 = (XTALFREQ << 5);	/* 15625/512 */
अटल पूर्णांक qlcfg6 = SYNCXFRPD;
अटल पूर्णांक qlcfg7 = SYNCOFFST;
अटल पूर्णांक qlcfg8 = (SLOWCABLE << 7) | (QL_ENABLE_PARITY << 4);
अटल पूर्णांक qlcfg9 = ((XTALFREQ + 4) / 5);
अटल पूर्णांक qlcfgc = (FASTCLK << 3) | (FASTSCSI << 4);

/*----------------------------------------------------------------*/

/*----------------------------------------------------------------*/
/* local functions */
/*----------------------------------------------------------------*/

/* error recovery - reset everything */

अटल व्योम ql_zap(काष्ठा qlogicfas408_priv *priv)
अणु
	पूर्णांक x;
	पूर्णांक qbase = priv->qbase;
	पूर्णांक पूर्णांक_type = priv->पूर्णांक_type;

	x = inb(qbase + 0xd);
	REG0;
	outb(3, qbase + 3);	/* reset SCSI */
	outb(2, qbase + 3);	/* reset chip */
	अगर (x & 0x80)
		REG1;
पूर्ण

/*
 *	Do a pseuकरो-dma tranfer
 */
 
अटल पूर्णांक ql_pdma(काष्ठा qlogicfas408_priv *priv, पूर्णांक phase, अक्षर *request, पूर्णांक reqlen)
अणु
	पूर्णांक j;
	पूर्णांक qbase = priv->qbase;
	j = 0;
	अगर (phase & 1) अणु	/* in */
#अगर QL_TURBO_PDMA
		rtrc(4)
		/* empty fअगरo in large chunks */
		अगर (reqlen >= 128 && (inb(qbase + 8) & 2)) अणु	/* full */
			insl(qbase + 4, request, 32);
			reqlen -= 128;
			request += 128;
		पूर्ण
		जबतक (reqlen >= 84 && !(j & 0xc0))	/* 2/3 */
			अगर ((j = inb(qbase + 8)) & 4) 
			अणु
				insl(qbase + 4, request, 21);
				reqlen -= 84;
				request += 84;
			पूर्ण
		अगर (reqlen >= 44 && (inb(qbase + 8) & 8)) अणु	/* 1/3 */
			insl(qbase + 4, request, 11);
			reqlen -= 44;
			request += 44;
		पूर्ण
#पूर्ण_अगर
		/* until both empty and पूर्णांक (or until reclen is 0) */
		rtrc(7)
		j = 0;
		जबतक (reqlen && !((j & 0x10) && (j & 0xc0))) 
		अणु
			/* जबतक bytes to receive and not empty */
			j &= 0xc0;
			जबतक (reqlen && !((j = inb(qbase + 8)) & 0x10)) 
			अणु
				*request++ = inb(qbase + 4);
				reqlen--;
			पूर्ण
			अगर (j & 0x10)
				j = inb(qbase + 8);

		पूर्ण
	पूर्ण अन्यथा अणु		/* out */
#अगर QL_TURBO_PDMA
		rtrc(4)
		अगर (reqlen >= 128 && inb(qbase + 8) & 0x10) अणु	/* empty */
			outsl(qbase + 4, request, 32);
			reqlen -= 128;
			request += 128;
		पूर्ण
		जबतक (reqlen >= 84 && !(j & 0xc0))	/* 1/3 */
			अगर (!((j = inb(qbase + 8)) & 8)) अणु
				outsl(qbase + 4, request, 21);
				reqlen -= 84;
				request += 84;
			पूर्ण
		अगर (reqlen >= 40 && !(inb(qbase + 8) & 4)) अणु	/* 2/3 */
			outsl(qbase + 4, request, 10);
			reqlen -= 40;
			request += 40;
		पूर्ण
#पूर्ण_अगर
		/* until full and पूर्णांक (or until reclen is 0) */
		rtrc(7)
		    j = 0;
		जबतक (reqlen && !((j & 2) && (j & 0xc0))) अणु
			/* जबतक bytes to send and not full */
			जबतक (reqlen && !((j = inb(qbase + 8)) & 2)) 
			अणु
				outb(*request++, qbase + 4);
				reqlen--;
			पूर्ण
			अगर (j & 2)
				j = inb(qbase + 8);
		पूर्ण
	पूर्ण
	/* maybe वापस reqlen */
	वापस inb(qbase + 8) & 0xc0;
पूर्ण

/*
 *	Wait क्रम पूर्णांकerrupt flag (polled - not real hardware पूर्णांकerrupt) 
 */

अटल पूर्णांक ql_wai(काष्ठा qlogicfas408_priv *priv)
अणु
	पूर्णांक k;
	पूर्णांक qbase = priv->qbase;
	अचिन्हित दीर्घ i;

	k = 0;
	i = jअगरfies + WATCHDOG;
	जबतक (समय_beक्रमe(jअगरfies, i) && !priv->qपात &&
					!((k = inb(qbase + 4)) & 0xe0)) अणु
		barrier();
		cpu_relax();
	पूर्ण
	अगर (समय_after_eq(jअगरfies, i))
		वापस (DID_TIME_OUT);
	अगर (priv->qपात)
		वापस (priv->qपात == 1 ? DID_ABORT : DID_RESET);
	अगर (k & 0x60)
		ql_zap(priv);
	अगर (k & 0x20)
		वापस (DID_PARITY);
	अगर (k & 0x40)
		वापस (DID_ERROR);
	वापस 0;
पूर्ण

/*
 *	Initiate scsi command - queueing handler 
 *	caller must hold host lock
 */

अटल व्योम ql_icmd(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा qlogicfas408_priv *priv = get_priv_by_cmd(cmd);
	पूर्णांक 	qbase = priv->qbase;
	पूर्णांक	पूर्णांक_type = priv->पूर्णांक_type;
	अचिन्हित पूर्णांक i;

	priv->qपात = 0;

	REG0;
	/* clearing of पूर्णांकerrupts and the fअगरo is needed */

	inb(qbase + 5);		/* clear पूर्णांकerrupts */
	अगर (inb(qbase + 5))	/* अगर still पूर्णांकerrupting */
		outb(2, qbase + 3);	/* reset chip */
	अन्यथा अगर (inb(qbase + 7) & 0x1f)
		outb(1, qbase + 3);	/* clear fअगरo */
	जबतक (inb(qbase + 5));	/* clear पूर्णांकs */
	REG1;
	outb(1, qbase + 8);	/* set क्रम PIO pseuकरो DMA */
	outb(0, qbase + 0xb);	/* disable पूर्णांकs */
	inb(qbase + 8);		/* clear पूर्णांक bits */
	REG0;
	outb(0x40, qbase + 0xb);	/* enable features */

	/* configurables */
	outb(qlcfgc, qbase + 0xc);
	/* config: no reset पूर्णांकerrupt, (initiator) bus id */
	outb(0x40 | qlcfg8 | priv->qinitid, qbase + 8);
	outb(qlcfg7, qbase + 7);
	outb(qlcfg6, qbase + 6);
	outb(qlcfg5, qbase + 5);	/* select समयr */
	outb(qlcfg9 & 7, qbase + 9);	/* prescaler */
/*	outb(0x99, qbase + 5);	*/
	outb(scmd_id(cmd), qbase + 4);

	क्रम (i = 0; i < cmd->cmd_len; i++)
		outb(cmd->cmnd[i], qbase + 2);

	priv->qlcmd = cmd;
	outb(0x41, qbase + 3);	/* select and send command */
पूर्ण

/*
 *	Process scsi command - usually after पूर्णांकerrupt 
 */

अटल अचिन्हित पूर्णांक ql_pcmd(काष्ठा scsi_cmnd *cmd)
अणु
	अचिन्हित पूर्णांक i, j;
	अचिन्हित दीर्घ k;
	अचिन्हित पूर्णांक result;	/* ultimate वापस result */
	अचिन्हित पूर्णांक status;	/* scsi वापसed status */
	अचिन्हित पूर्णांक message;	/* scsi वापसed message */
	अचिन्हित पूर्णांक phase;	/* recorded scsi phase */
	अचिन्हित पूर्णांक reqlen;	/* total length of transfer */
	अक्षर *buf;
	काष्ठा qlogicfas408_priv *priv = get_priv_by_cmd(cmd);
	पूर्णांक qbase = priv->qbase;
	पूर्णांक पूर्णांक_type = priv->पूर्णांक_type;

	rtrc(1)
	j = inb(qbase + 6);
	i = inb(qbase + 5);
	अगर (i == 0x20) अणु
		वापस (DID_NO_CONNECT << 16);
	पूर्ण
	i |= inb(qbase + 5);	/* the 0x10 bit can be set after the 0x08 */
	अगर (i != 0x18) अणु
		prपूर्णांकk(KERN_ERR "Ql:Bad Interrupt status:%02x\n", i);
		ql_zap(priv);
		वापस (DID_BAD_INTR << 16);
	पूर्ण
	j &= 7;			/* j = inb( qbase + 7 ) >> 5; */

	/* correct status is supposed to be step 4 */
	/* it someबार वापसs step 3 but with 0 bytes left to send */
	/* We can try stuffing the FIFO with the max each समय, but we will get a
	   sequence of 3 अगर any bytes are left (but we करो flush the FIFO anyway */

	अगर (j != 3 && j != 4) अणु
		prपूर्णांकk(KERN_ERR "Ql:Bad sequence for command %d, int %02X, cmdleft = %d\n",
		     j, i, inb(qbase + 7) & 0x1f);
		ql_zap(priv);
		वापस (DID_ERROR << 16);
	पूर्ण
	result = DID_OK;
	अगर (inb(qbase + 7) & 0x1f)	/* अगर some bytes in fअगरo */
		outb(1, qbase + 3);	/* clear fअगरo */
	/* note that request_bufflen is the total xfer size when sg is used */
	reqlen = scsi_bufflen(cmd);
	/* note that it won't work अगर transfers > 16M are requested */
	अगर (reqlen && !((phase = inb(qbase + 4)) & 6)) अणु	/* data phase */
		काष्ठा scatterlist *sg;
		rtrc(2)
		outb(reqlen, qbase);	/* low-mid xfer cnt */
		outb(reqlen >> 8, qbase + 1);	/* low-mid xfer cnt */
		outb(reqlen >> 16, qbase + 0xe);	/* high xfer cnt */
		outb(0x90, qbase + 3);	/* command करो xfer */
		/* PIO pseuकरो DMA to buffer or sglist */
		REG1;

		scsi_क्रम_each_sg(cmd, sg, scsi_sg_count(cmd), i) अणु
			अगर (priv->qपात) अणु
				REG0;
				वापस ((priv->qपात == 1 ?
					 DID_ABORT : DID_RESET) << 16);
			पूर्ण
			buf = sg_virt(sg);
			अगर (ql_pdma(priv, phase, buf, sg->length))
				अवरोध;
		पूर्ण
		REG0;
		rtrc(2)
		/*
		 *	Wait क्रम irq (split पूर्णांकo second state of irq handler
		 *	अगर this can take समय) 
		 */
		अगर ((k = ql_wai(priv)))
			वापस (k << 16);
		k = inb(qbase + 5);	/* should be 0x10, bus service */
	पूर्ण

	/*
	 *	Enter Status (and Message In) Phase 
	 */
	 
	k = jअगरfies + WATCHDOG;

	जबतक (समय_beक्रमe(jअगरfies, k) && !priv->qपात &&
						!(inb(qbase + 4) & 6))
		cpu_relax();	/* रुको क्रम status phase */

	अगर (समय_after_eq(jअगरfies, k)) अणु
		ql_zap(priv);
		वापस (DID_TIME_OUT << 16);
	पूर्ण

	/* FIXME: समयout ?? */
	जबतक (inb(qbase + 5))
		cpu_relax();	/* clear pending पूर्णांकs */

	अगर (priv->qपात)
		वापस ((priv->qपात == 1 ? DID_ABORT : DID_RESET) << 16);

	outb(0x11, qbase + 3);	/* get status and message */
	अगर ((k = ql_wai(priv)))
		वापस (k << 16);
	i = inb(qbase + 5);	/* get chip irq stat */
	j = inb(qbase + 7) & 0x1f;	/* and bytes rec'd */
	status = inb(qbase + 2);
	message = inb(qbase + 2);

	/*
	 *	Should get function complete पूर्णांक अगर Status and message, अन्यथा 
	 *	bus serv अगर only status 
	 */
	अगर (!((i == 8 && j == 2) || (i == 0x10 && j == 1))) अणु
		prपूर्णांकk(KERN_ERR "Ql:Error during status phase, int=%02X, %d bytes recd\n", i, j);
		result = DID_ERROR;
	पूर्ण
	outb(0x12, qbase + 3);	/* करोne, disconnect */
	rtrc(1)
	अगर ((k = ql_wai(priv)))
		वापस (k << 16);

	/*
	 *	Should get bus service पूर्णांकerrupt and disconnect पूर्णांकerrupt 
	 */
	 
	i = inb(qbase + 5);	/* should be bus service */
	जबतक (!priv->qपात && ((i & 0x20) != 0x20)) अणु
		barrier();
		cpu_relax();
		i |= inb(qbase + 5);
	पूर्ण
	rtrc(0)

	अगर (priv->qपात)
		वापस ((priv->qपात == 1 ? DID_ABORT : DID_RESET) << 16);
		
	वापस (result << 16) | (message << 8) | (status & STATUS_MASK);
पूर्ण

/*
 *	Interrupt handler 
 */

अटल व्योम ql_ihandl(व्योम *dev_id)
अणु
	काष्ठा scsi_cmnd *icmd;
	काष्ठा Scsi_Host *host = dev_id;
	काष्ठा qlogicfas408_priv *priv = get_priv_by_host(host);
	पूर्णांक qbase = priv->qbase;
	REG0;

	अगर (!(inb(qbase + 4) & 0x80))	/* false alarm? */
		वापस;

	अगर (priv->qlcmd == शून्य) अणु	/* no command to process? */
		पूर्णांक i;
		i = 16;
		जबतक (i-- && inb(qbase + 5));	/* maybe also ql_zap() */
		वापस;
	पूर्ण
	icmd = priv->qlcmd;
	icmd->result = ql_pcmd(icmd);
	priv->qlcmd = शून्य;
	/*
	 *	If result is CHECK CONDITION करोne calls qcommand to request 
	 *	sense 
	 */
	(icmd->scsi_करोne) (icmd);
पूर्ण

irqवापस_t qlogicfas408_ihandl(पूर्णांक irq, व्योम *dev_id)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा Scsi_Host *host = dev_id;

	spin_lock_irqsave(host->host_lock, flags);
	ql_ihandl(dev_id);
	spin_unlock_irqrestore(host->host_lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

/*
 *	Queued command
 */

अटल पूर्णांक qlogicfas408_queuecommand_lck(काष्ठा scsi_cmnd *cmd,
			      व्योम (*करोne) (काष्ठा scsi_cmnd *))
अणु
	काष्ठा qlogicfas408_priv *priv = get_priv_by_cmd(cmd);
	अगर (scmd_id(cmd) == priv->qinitid) अणु
		cmd->result = DID_BAD_TARGET << 16;
		करोne(cmd);
		वापस 0;
	पूर्ण

	cmd->scsi_करोne = करोne;
	/* रुको क्रम the last command's पूर्णांकerrupt to finish */
	जबतक (priv->qlcmd != शून्य) अणु
		barrier();
		cpu_relax();
	पूर्ण
	ql_icmd(cmd);
	वापस 0;
पूर्ण

DEF_SCSI_QCMD(qlogicfas408_queuecommand)

/* 
 *	Return bios parameters 
 */

पूर्णांक qlogicfas408_biosparam(काष्ठा scsi_device *disk, काष्ठा block_device *dev,
			   sector_t capacity, पूर्णांक ip[])
अणु
/* This should mimic the DOS Qlogic driver's behavior exactly */
	ip[0] = 0x40;
	ip[1] = 0x20;
	ip[2] = (अचिन्हित दीर्घ) capacity / (ip[0] * ip[1]);
	अगर (ip[2] > 1024) अणु
		ip[0] = 0xff;
		ip[1] = 0x3f;
		ip[2] = (अचिन्हित दीर्घ) capacity / (ip[0] * ip[1]);
#अगर 0
		अगर (ip[2] > 1023)
			ip[2] = 1023;
#पूर्ण_अगर
	पूर्ण
	वापस 0;
पूर्ण

/*
 *	Abort a command in progress
 */
 
पूर्णांक qlogicfas408_पात(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा qlogicfas408_priv *priv = get_priv_by_cmd(cmd);
	priv->qपात = 1;
	ql_zap(priv);
	वापस SUCCESS;
पूर्ण

/*
 *	Reset SCSI bus
 *	FIXME: This function is invoked with cmd = शून्य directly by
 *	the PCMCIA qlogic_stub code. This wants fixing
 */

पूर्णांक qlogicfas408_host_reset(काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा qlogicfas408_priv *priv = get_priv_by_cmd(cmd);
	अचिन्हित दीर्घ flags;

	priv->qपात = 2;

	spin_lock_irqsave(cmd->device->host->host_lock, flags);
	ql_zap(priv);
	spin_unlock_irqrestore(cmd->device->host->host_lock, flags);

	वापस SUCCESS;
पूर्ण

/*
 *	Return info string
 */

स्थिर अक्षर *qlogicfas408_info(काष्ठा Scsi_Host *host)
अणु
	काष्ठा qlogicfas408_priv *priv = get_priv_by_host(host);
	वापस priv->qinfo;
पूर्ण

/*
 *	Get type of chip
 */

पूर्णांक qlogicfas408_get_chip_type(पूर्णांक qbase, पूर्णांक पूर्णांक_type)
अणु
	REG1;
	वापस inb(qbase + 0xe) & 0xf8;
पूर्ण

/*
 *	Perक्रमm initialization tasks
 */

व्योम qlogicfas408_setup(पूर्णांक qbase, पूर्णांक id, पूर्णांक पूर्णांक_type)
अणु
	outb(1, qbase + 8);	/* set क्रम PIO pseuकरो DMA */
	REG0;
	outb(0x40 | qlcfg8 | id, qbase + 8);	/* (ini) bus id, disable scsi rst */
	outb(qlcfg5, qbase + 5);	/* select समयr */
	outb(qlcfg9, qbase + 9);	/* prescaler */

#अगर QL_RESET_AT_START
	outb(3, qbase + 3);

	REG1;
	/* FIXME: समयout */
	जबतक (inb(qbase + 0xf) & 4)
		cpu_relax();

	REG0;
#पूर्ण_अगर
पूर्ण

/*
 *	Checks अगर this is a QLogic FAS 408
 */

पूर्णांक qlogicfas408_detect(पूर्णांक qbase, पूर्णांक पूर्णांक_type)
अणु
        REG1;
	वापस (((inb(qbase + 0xe) ^ inb(qbase + 0xe)) == 7) &&
	       ((inb(qbase + 0xe) ^ inb(qbase + 0xe)) == 7));		
पूर्ण

/*
 *	Disable पूर्णांकerrupts
 */

व्योम qlogicfas408_disable_पूर्णांकs(काष्ठा qlogicfas408_priv *priv)
अणु
	पूर्णांक qbase = priv->qbase;
	पूर्णांक पूर्णांक_type = priv->पूर्णांक_type;

	REG1;
	outb(0, qbase + 0xb);	/* disable पूर्णांकs */
पूर्ण

/*
 *	Init and निकास functions
 */

अटल पूर्णांक __init qlogicfas408_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम __निकास qlogicfas408_निकास(व्योम)
अणु

पूर्ण

MODULE_AUTHOR("Tom Zerucha, Michael Griffith");
MODULE_DESCRIPTION("Driver for the Qlogic FAS SCSI controllers");
MODULE_LICENSE("GPL");
module_init(qlogicfas408_init);
module_निकास(qlogicfas408_निकास);

EXPORT_SYMBOL(qlogicfas408_info);
EXPORT_SYMBOL(qlogicfas408_queuecommand);
EXPORT_SYMBOL(qlogicfas408_पात);
EXPORT_SYMBOL(qlogicfas408_host_reset);
EXPORT_SYMBOL(qlogicfas408_biosparam);
EXPORT_SYMBOL(qlogicfas408_ihandl);
EXPORT_SYMBOL(qlogicfas408_get_chip_type);
EXPORT_SYMBOL(qlogicfas408_setup);
EXPORT_SYMBOL(qlogicfas408_detect);
EXPORT_SYMBOL(qlogicfas408_disable_पूर्णांकs);

