<शैली गुरु>
/*  $Id$
 *  1993/03/31
 *  linux/kernel/aha1740.c
 *
 *  Based loosely on aha1542.c which is
 *  Copyright (C) 1992  Tommy Thorn and
 *  Modअगरied by Eric Youngdale
 *
 *  This file is aha1740.c, written and
 *  Copyright (C) 1992,1993  Brad McLean
 *  brad@saturn.gaylord.com or brad@bradpc.gaylord.com.
 *  
 *  Modअगरications to makecode and queuecommand
 *  क्रम proper handling of multiple devices courteously
 *  provided by Michael Weller, March, 1993
 *
 *  Multiple adapter support, extended translation detection,
 *  update to current scsi subप्रणाली changes, proc fs support,
 *  working (!) module support based on patches from Andreas Arens,
 *  by Andreas Degert <ad@papyrus.hamburg.com>, 2/1997
 *
 * aha1740_makecode may still need even more work
 * अगर it करोesn't work क्रम your devices, take a look.
 *
 * Reworked क्रम new_eh and new locking by Alan Cox <alan@lxorguk.ukuu.org.uk>
 *
 * Converted to EISA and generic DMA APIs by Marc Zyngier
 * <maz@wild-wind.fr.eu.org>, 4/2003.
 *
 * Shared पूर्णांकerrupt support added by Rask Ingemann Lambertsen
 * <rask@sygehus.dk>, 10/2003
 *
 * For the aव्योमance of करोubt the "preferred form" of this code is one which
 * is in an खोलो non patent encumbered क्रमmat. Where cryptographic key signing
 * क्रमms part of the process of creating an executable the inक्रमmation
 * including keys needed to generate an equivalently functional executable
 * are deemed to be part of the source code.
 */

#समावेश <linux/blkdev.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/ioport.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/eisa.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/gfp.h>

#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/पन.स>

#समावेश "scsi.h"
#समावेश <scsi/scsi_host.h>
#समावेश "aha1740.h"

/* IF YOU ARE HAVING PROBLEMS WITH THIS DRIVER, AND WANT TO WATCH
   IT WORK, THEN:
#घोषणा DEBUG
*/
#अगर_घोषित DEBUG
#घोषणा DEB(x) x
#अन्यथा
#घोषणा DEB(x)
#पूर्ण_अगर

काष्ठा aha1740_hostdata अणु
	काष्ठा eisa_device *edev;
	अचिन्हित पूर्णांक translation;
	अचिन्हित पूर्णांक last_ecb_used;
	dma_addr_t ecb_dma_addr;
	काष्ठा ecb ecb[AHA1740_ECBS];
पूर्ण;

काष्ठा aha1740_sg अणु
	काष्ठा aha1740_chain sg_chain[AHA1740_SCATTER];
	dma_addr_t sg_dma_addr;
	dma_addr_t buf_dma_addr;
पूर्ण;

#घोषणा HOSTDATA(host) ((काष्ठा aha1740_hostdata *) &host->hostdata)

अटल अंतरभूत काष्ठा ecb *ecb_dma_to_cpu (काष्ठा Scsi_Host *host,
					  dma_addr_t dma)
अणु
	काष्ठा aha1740_hostdata *hdata = HOSTDATA (host);
	dma_addr_t offset;

	offset = dma - hdata->ecb_dma_addr;

	वापस (काष्ठा ecb *)(((अक्षर *) hdata->ecb) + (अचिन्हित पूर्णांक) offset);
पूर्ण

अटल अंतरभूत dma_addr_t ecb_cpu_to_dma (काष्ठा Scsi_Host *host, व्योम *cpu)
अणु
	काष्ठा aha1740_hostdata *hdata = HOSTDATA (host);
	dma_addr_t offset;
    
	offset = (अक्षर *) cpu - (अक्षर *) hdata->ecb;

	वापस hdata->ecb_dma_addr + offset;
पूर्ण

अटल पूर्णांक aha1740_show_info(काष्ठा seq_file *m, काष्ठा Scsi_Host *shpnt)
अणु
	काष्ठा aha1740_hostdata *host = HOSTDATA(shpnt);
	seq_म_लिखो(m, "aha174x at IO:%lx, IRQ %d, SLOT %d.\n"
		      "Extended translation %sabled.\n",
		      shpnt->io_port, shpnt->irq, host->edev->slot,
		      host->translation ? "en" : "dis");
	वापस 0;
पूर्ण

अटल पूर्णांक aha1740_makecode(unअक्षर *sense, unअक्षर *status)
अणु
	काष्ठा statusword
	अणु
		uलघु	करोn:1,	/* Command Done - No Error */
			du:1,	/* Data underrun */
		    :1,	qf:1,	/* Queue full */
		        sc:1,	/* Specअगरication Check */
		        करोr:1,	/* Data overrun */
		        ch:1,	/* Chaining Halted */
		        पूर्णांकr:1,	/* Interrupt issued */
		        asa:1,	/* Additional Status Available */
		        sns:1,	/* Sense inक्रमmation Stored */
		    :1,	ini:1,	/* Initialization Required */
			me:1,	/* Major error or exception */
		    :1,	eca:1,  /* Extended Contingent alliance */
		    :1;
	पूर्ण status_word;
	पूर्णांक retval = DID_OK;

	status_word = * (काष्ठा statusword *) status;
#अगर_घोषित DEBUG
	prपूर्णांकk("makecode from %x,%x,%x,%x %x,%x,%x,%x",
	       status[0], status[1], status[2], status[3],
	       sense[0], sense[1], sense[2], sense[3]);
#पूर्ण_अगर
	अगर (!status_word.करोn) अणु /* Anything abnormal was detected */
		अगर ( (status[1]&0x18) || status_word.sc ) अणु
			/*Additional info available*/
			/* Use the supplied info क्रम further diagnostics */
			चयन ( status[2] ) अणु
			हाल 0x12:
				अगर ( status_word.करोr )
					retval=DID_ERROR; /* It's an Overrun */
				/* If not overrun, assume underrun and
				 * ignore it! */
				अवरोध;
			हाल 0x00: /* No info, assume no error, should
				    * not occur */
				अवरोध;
			हाल 0x11:
			हाल 0x21:
				retval=DID_TIME_OUT;
				अवरोध;
			हाल 0x0a:
				retval=DID_BAD_TARGET;
				अवरोध;
			हाल 0x04:
			हाल 0x05:
				retval=DID_ABORT;
				/* Either by this driver or the
				 * AHA1740 itself */
				अवरोध;
			शेष:
				retval=DID_ERROR; /* No further
						   * diagnostics
						   * possible */
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Michael suggests, and Brad concurs: */
			अगर ( status_word.qf ) अणु
				retval = DID_TIME_OUT; /* क्रमces a reकरो */
				/* I think this specअगरic one should
				 * not happen -Brad */
				prपूर्णांकk("aha1740.c: WARNING: AHA1740 queue overflow!\n");
			पूर्ण अन्यथा
				अगर ( status[0]&0x60 ) अणु
					 /* Didn't find a better error */
					retval = DID_ERROR;
				पूर्ण
			/* In any other हाल वापस DID_OK so क्रम example
			   CONDITION_CHECKS make it through to the appropriate
			   device driver */
		पूर्ण
	पूर्ण
	/* Under all circumstances supply the target status -Michael */
	वापस status[3] | retval << 16;
पूर्ण

अटल पूर्णांक aha1740_test_port(अचिन्हित पूर्णांक base)
अणु
	अगर ( inb(PORTADR(base)) & PORTADDR_ENH )
		वापस 1;   /* Okay, we're all set */
	
	prपूर्णांकk("aha174x: Board detected, but not in enhanced mode, so disabled it.\n");
	वापस 0;
पूर्ण

/* A "high" level पूर्णांकerrupt handler */
अटल irqवापस_t aha1740_पूर्णांकr_handle(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा Scsi_Host *host = (काष्ठा Scsi_Host *) dev_id;
        व्योम (*my_करोne)(काष्ठा scsi_cmnd *);
	पूर्णांक errstatus, adapstat;
	पूर्णांक number_serviced;
	काष्ठा ecb *ecbptr;
	काष्ठा scsi_cmnd *SCपंचांगp;
	अचिन्हित पूर्णांक base;
	अचिन्हित दीर्घ flags;
	पूर्णांक handled = 0;
	काष्ठा aha1740_sg *sgptr;
	काष्ठा eisa_device *edev;
	
	अगर (!host)
		panic("aha1740.c: Irq from unknown host!\n");
	spin_lock_irqsave(host->host_lock, flags);
	base = host->io_port;
	number_serviced = 0;
	edev = HOSTDATA(host)->edev;

	जबतक(inb(G2STAT(base)) & G2STAT_INTPEND) अणु
		handled = 1;
		DEB(prपूर्णांकk("aha1740_intr top of loop.\n"));
		adapstat = inb(G2INTST(base));
		ecbptr = ecb_dma_to_cpu (host, inl(MBOXIN0(base)));
		outb(G2CNTRL_IRST,G2CNTRL(base)); /* पूर्णांकerrupt reset */
      
		चयन ( adapstat & G2INTST_MASK ) अणु
		हाल	G2INTST_CCBRETRY:
		हाल	G2INTST_CCBERROR:
		हाल	G2INTST_CCBGOOD:
			/* Host Ready -> Mailbox in complete */
			outb(G2CNTRL_HRDY,G2CNTRL(base));
			अगर (!ecbptr) अणु
				prपूर्णांकk("Aha1740 null ecbptr in interrupt (%x,%x,%x,%d)\n",
				       inb(G2STAT(base)),adapstat,
				       inb(G2INTST(base)), number_serviced++);
				जारी;
			पूर्ण
			SCपंचांगp = ecbptr->SCpnt;
			अगर (!SCपंचांगp) अणु
				prपूर्णांकk("Aha1740 null SCtmp in interrupt (%x,%x,%x,%d)\n",
				       inb(G2STAT(base)),adapstat,
				       inb(G2INTST(base)), number_serviced++);
				जारी;
			पूर्ण
			sgptr = (काष्ठा aha1740_sg *) SCपंचांगp->host_scribble;
			scsi_dma_unmap(SCपंचांगp);

			/* Free the sg block */
			dma_मुक्त_coherent (&edev->dev,
					   माप (काष्ठा aha1740_sg),
					   SCपंचांगp->host_scribble,
					   sgptr->sg_dma_addr);
	    
			/* Fetch the sense data, and tuck it away, in
			   the required slot.  The Adaptec
			   स्वतःmatically fetches it, and there is no
			   guarantee that we will still have it in the
			   cdb when we come back */
			अगर ( (adapstat & G2INTST_MASK) == G2INTST_CCBERROR ) अणु
				स_नकल(SCपंचांगp->sense_buffer, ecbptr->sense, 
				       SCSI_SENSE_BUFFERSIZE);
				errstatus = aha1740_makecode(ecbptr->sense,ecbptr->status);
			पूर्ण अन्यथा
				errstatus = 0;
			DEB(अगर (errstatus)
			    prपूर्णांकk("aha1740_intr_handle: returning %6x\n",
				   errstatus));
			SCपंचांगp->result = errstatus;
			my_करोne = ecbptr->करोne;
			स_रखो(ecbptr,0,माप(काष्ठा ecb)); 
			अगर ( my_करोne )
				my_करोne(SCपंचांगp);
			अवरोध;
			
		हाल	G2INTST_HARDFAIL:
			prपूर्णांकk(KERN_ALERT "aha1740 hardware failure!\n");
			panic("aha1740.c");	/* Goodbye */
			
		हाल	G2INTST_ASNEVENT:
			prपूर्णांकk("aha1740 asynchronous event: %02x %02x %02x %02x %02x\n",
			       adapstat,
			       inb(MBOXIN0(base)),
			       inb(MBOXIN1(base)),
			       inb(MBOXIN2(base)),
			       inb(MBOXIN3(base))); /* Say What? */
			/* Host Ready -> Mailbox in complete */
			outb(G2CNTRL_HRDY,G2CNTRL(base));
			अवरोध;
			
		हाल	G2INTST_CMDGOOD:
			/* set immediate command success flag here: */
			अवरोध;
			
		हाल	G2INTST_CMDERROR:
			/* Set immediate command failure flag here: */
			अवरोध;
		पूर्ण
		number_serviced++;
	पूर्ण

	spin_unlock_irqrestore(host->host_lock, flags);
	वापस IRQ_RETVAL(handled);
पूर्ण

अटल पूर्णांक aha1740_queuecommand_lck(काष्ठा scsi_cmnd * SCpnt,
				    व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
	unअक्षर direction;
	unअक्षर *cmd = (unअक्षर *) SCpnt->cmnd;
	unअक्षर target = scmd_id(SCpnt);
	काष्ठा aha1740_hostdata *host = HOSTDATA(SCpnt->device->host);
	अचिन्हित दीर्घ flags;
	dma_addr_t sg_dma;
	काष्ठा aha1740_sg *sgptr;
	पूर्णांक ecbno, nseg;
	DEB(पूर्णांक i);

	अगर(*cmd == REQUEST_SENSE) अणु
		SCpnt->result = 0;
		करोne(SCpnt); 
		वापस 0;
	पूर्ण

#अगर_घोषित DEBUG
	अगर (*cmd == READ_10 || *cmd == WRITE_10)
		i = xscsi2पूर्णांक(cmd+2);
	अन्यथा अगर (*cmd == READ_6 || *cmd == WRITE_6)
		i = scsi2पूर्णांक(cmd+2);
	अन्यथा
		i = -1;
	prपूर्णांकk("aha1740_queuecommand: dev %d cmd %02x pos %d len %d ",
	       target, *cmd, i, bufflen);
	prपूर्णांकk("scsi cmd:");
	क्रम (i = 0; i < SCpnt->cmd_len; i++) prपूर्णांकk("%02x ", cmd[i]);
	prपूर्णांकk("\n");
#पूर्ण_अगर

	/* locate an available ecb */
	spin_lock_irqsave(SCpnt->device->host->host_lock, flags);
	ecbno = host->last_ecb_used + 1; /* An optimization */
	अगर (ecbno >= AHA1740_ECBS)
		ecbno = 0;
	करो अणु
		अगर (!host->ecb[ecbno].cmdw)
			अवरोध;
		ecbno++;
		अगर (ecbno >= AHA1740_ECBS)
			ecbno = 0;
	पूर्ण जबतक (ecbno != host->last_ecb_used);

	अगर (host->ecb[ecbno].cmdw)
		panic("Unable to find empty ecb for aha1740.\n");

	host->ecb[ecbno].cmdw = AHA1740CMD_INIT; /* SCSI Initiator Command
						    द्विगुनs as reserved flag */

	host->last_ecb_used = ecbno;    
	spin_unlock_irqrestore(SCpnt->device->host->host_lock, flags);

#अगर_घोषित DEBUG
	prपूर्णांकk("Sending command (%d %x)...", ecbno, करोne);
#पूर्ण_अगर

	host->ecb[ecbno].cdblen = SCpnt->cmd_len; /* SCSI Command
						   * Descriptor Block
						   * Length */

	direction = 0;
	अगर (*cmd == READ_10 || *cmd == READ_6)
		direction = 1;
	अन्यथा अगर (*cmd == WRITE_10 || *cmd == WRITE_6)
		direction = 0;

	स_नकल(host->ecb[ecbno].cdb, cmd, SCpnt->cmd_len);

	SCpnt->host_scribble = dma_alloc_coherent (&host->edev->dev,
						   माप (काष्ठा aha1740_sg),
						   &sg_dma, GFP_ATOMIC);
	अगर(SCpnt->host_scribble == शून्य) अणु
		prपूर्णांकk(KERN_WARNING "aha1740: out of memory in queuecommand!\n");
		वापस 1;
	पूर्ण
	sgptr = (काष्ठा aha1740_sg *) SCpnt->host_scribble;
	sgptr->sg_dma_addr = sg_dma;

	nseg = scsi_dma_map(SCpnt);
	BUG_ON(nseg < 0);
	अगर (nseg) अणु
		काष्ठा scatterlist *sg;
		काष्ठा aha1740_chain * cptr;
		पूर्णांक i;
		DEB(अचिन्हित अक्षर * ptr);

		host->ecb[ecbno].sg = 1;  /* SCSI Initiator Command
					   * w/scatter-gather*/
		cptr = sgptr->sg_chain;
		scsi_क्रम_each_sg(SCpnt, sg, nseg, i) अणु
			cptr[i].datalen = sg_dma_len (sg);
			cptr[i].dataptr = sg_dma_address (sg);
		पूर्ण
		host->ecb[ecbno].datalen = nseg * माप(काष्ठा aha1740_chain);
		host->ecb[ecbno].dataptr = sg_dma;
#अगर_घोषित DEBUG
		prपूर्णांकk("cptr %x: ",cptr);
		ptr = (अचिन्हित अक्षर *) cptr;
		क्रम(i=0;i<24;i++) prपूर्णांकk("%02x ", ptr[i]);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		host->ecb[ecbno].datalen = 0;
		host->ecb[ecbno].dataptr = 0;
	पूर्ण
	host->ecb[ecbno].lun = SCpnt->device->lun;
	host->ecb[ecbno].ses = 1; /* Suppress underrun errors */
	host->ecb[ecbno].dir = direction;
	host->ecb[ecbno].ars = 1; /* Yes, get the sense on an error */
	host->ecb[ecbno].senselen = 12;
	host->ecb[ecbno].senseptr = ecb_cpu_to_dma (SCpnt->device->host,
						    host->ecb[ecbno].sense);
	host->ecb[ecbno].statusptr = ecb_cpu_to_dma (SCpnt->device->host,
						     host->ecb[ecbno].status);
	host->ecb[ecbno].करोne = करोne;
	host->ecb[ecbno].SCpnt = SCpnt;
#अगर_घोषित DEBUG
	अणु
		पूर्णांक i;
		prपूर्णांकk("aha1740_command: sending.. ");
		क्रम (i = 0; i < माप(host->ecb[ecbno]) - 10; i++)
			prपूर्णांकk("%02x ", ((unअक्षर *)&host->ecb[ecbno])[i]);
	पूर्ण
	prपूर्णांकk("\n");
#पूर्ण_अगर
	अगर (करोne) अणु
	/* The Adaptec Spec says the card is so fast that the loops
           will only be executed once in the code below. Even अगर this
           was true with the fastest processors when the spec was
           written, it करोesn't seem to be true with today's fast
           processors. We prपूर्णांक a warning अगर the code is executed more
           often than LOOPCNT_WARN. If this happens, it should be
           investigated. If the count reaches LOOPCNT_MAX, we assume
           something is broken; since there is no way to वापस an
           error (the वापस value is ignored by the mid-level scsi
           layer) we have to panic (and maybe that's the best thing we
           can करो then anyhow). */

#घोषणा LOOPCNT_WARN 10		/* excessive mbxout रुको -> syslog-msg */
#घोषणा LOOPCNT_MAX 1000000	/* mbxout deadlock -> panic() after ~ 2 sec. */
		पूर्णांक loopcnt;
		अचिन्हित पूर्णांक base = SCpnt->device->host->io_port;
		DEB(prपूर्णांकk("aha1740[%d] critical section\n",ecbno));

		spin_lock_irqsave(SCpnt->device->host->host_lock, flags);
		क्रम (loopcnt = 0; ; loopcnt++) अणु
			अगर (inb(G2STAT(base)) & G2STAT_MBXOUT) अवरोध;
			अगर (loopcnt == LOOPCNT_WARN) अणु
				prपूर्णांकk("aha1740[%d]_mbxout wait!\n",ecbno);
			पूर्ण
			अगर (loopcnt == LOOPCNT_MAX)
				panic("aha1740.c: mbxout busy!\n");
		पूर्ण
		outl (ecb_cpu_to_dma (SCpnt->device->host, host->ecb + ecbno),
		      MBOXOUT0(base));
		क्रम (loopcnt = 0; ; loopcnt++) अणु
			अगर (! (inb(G2STAT(base)) & G2STAT_BUSY)) अवरोध;
			अगर (loopcnt == LOOPCNT_WARN) अणु
				prपूर्णांकk("aha1740[%d]_attn wait!\n",ecbno);
			पूर्ण
			अगर (loopcnt == LOOPCNT_MAX)
				panic("aha1740.c: attn wait failed!\n");
		पूर्ण
		outb(ATTN_START | (target & 7), ATTN(base)); /* Start it up */
		spin_unlock_irqrestore(SCpnt->device->host->host_lock, flags);
		DEB(prपूर्णांकk("aha1740[%d] request queued.\n",ecbno));
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_ALERT "aha1740_queuecommand: done can't be NULL\n");
	वापस 0;
पूर्ण

अटल DEF_SCSI_QCMD(aha1740_queuecommand)

/* Query the board क्रम its irq_level and irq_type.  Nothing अन्यथा matters
   in enhanced mode on an EISA bus. */

अटल व्योम aha1740_अ_लोonfig(अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक *irq_level,
			      अचिन्हित पूर्णांक *irq_type,
			      अचिन्हित पूर्णांक *translation)
अणु
	अटल पूर्णांक पूर्णांकab[] = अणु 9, 10, 11, 12, 0, 14, 15, 0 पूर्ण;

	*irq_level = पूर्णांकab[inb(INTDEF(base)) & 0x7];
	*irq_type  = (inb(INTDEF(base)) & 0x8) >> 3;
	*translation = inb(RESV1(base)) & 0x1;
	outb(inb(INTDEF(base)) | 0x10, INTDEF(base));
पूर्ण

अटल पूर्णांक aha1740_biosparam(काष्ठा scsi_device *sdev,
			     काष्ठा block_device *dev,
			     sector_t capacity, पूर्णांक* ip)
अणु
	पूर्णांक size = capacity;
	पूर्णांक extended = HOSTDATA(sdev->host)->translation;

	DEB(prपूर्णांकk("aha1740_biosparam\n"));
	अगर (extended && (ip[2] > 1024))	अणु
		ip[0] = 255;
		ip[1] = 63;
		ip[2] = size / (255 * 63);
	पूर्ण अन्यथा अणु
		ip[0] = 64;
		ip[1] = 32;
		ip[2] = size >> 11;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक aha1740_eh_पात_handler (काष्ठा scsi_cmnd *dummy)
अणु
/*
 * From Alan Cox :
 * The AHA1740 has firmware handled पात/reset handling. The "head in
 * sand" kernel code is correct क्रम once 8)
 *
 * So we define a dummy handler just to keep the kernel SCSI code as
 * quiet as possible...
 */

	वापस SUCCESS;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा aha1740_ढाँचा = अणु
	.module           = THIS_MODULE,
	.proc_name        = "aha1740",
	.show_info        = aha1740_show_info,
	.name             = "Adaptec 174x (EISA)",
	.queuecommand     = aha1740_queuecommand,
	.bios_param       = aha1740_biosparam,
	.can_queue        = AHA1740_ECBS,
	.this_id          = 7,
	.sg_tablesize     = AHA1740_SCATTER,
	.eh_पात_handler = aha1740_eh_पात_handler,
पूर्ण;

अटल पूर्णांक aha1740_probe (काष्ठा device *dev)
अणु
	पूर्णांक slotbase, rc;
	अचिन्हित पूर्णांक irq_level, irq_type, translation;
	काष्ठा Scsi_Host *shpnt;
	काष्ठा aha1740_hostdata *host;
	काष्ठा eisa_device *edev = to_eisa_device (dev);

	DEB(prपूर्णांकk("aha1740_probe: \n"));
	
	slotbase = edev->base_addr + EISA_VENDOR_ID_OFFSET;
	अगर (!request_region(slotbase, SLOTSIZE, "aha1740")) /* See अगर in use */
		वापस -EBUSY;
	अगर (!aha1740_test_port(slotbase))
		जाओ err_release_region;
	aha1740_अ_लोonfig(slotbase,&irq_level,&irq_type,&translation);
	अगर ((inb(G2STAT(slotbase)) &
	     (G2STAT_MBXOUT|G2STAT_BUSY)) != G2STAT_MBXOUT) अणु
		/* If the card isn't पढ़ोy, hard reset it */
		outb(G2CNTRL_HRST, G2CNTRL(slotbase));
		outb(0, G2CNTRL(slotbase));
	पूर्ण
	prपूर्णांकk(KERN_INFO "Configuring slot %d at IO:%x, IRQ %u (%s)\n",
	       edev->slot, slotbase, irq_level, irq_type ? "edge" : "level");
	prपूर्णांकk(KERN_INFO "aha174x: Extended translation %sabled.\n",
	       translation ? "en" : "dis");
	shpnt = scsi_host_alloc(&aha1740_ढाँचा,
			      माप(काष्ठा aha1740_hostdata));
	अगर(shpnt == शून्य)
		जाओ err_release_region;

	shpnt->base = 0;
	shpnt->io_port = slotbase;
	shpnt->n_io_port = SLOTSIZE;
	shpnt->irq = irq_level;
	shpnt->dma_channel = 0xff;
	host = HOSTDATA(shpnt);
	host->edev = edev;
	host->translation = translation;
	host->ecb_dma_addr = dma_map_single (&edev->dev, host->ecb,
					     माप (host->ecb),
					     DMA_BIसूचीECTIONAL);
	अगर (!host->ecb_dma_addr) अणु
		prपूर्णांकk (KERN_ERR "aha1740_probe: Couldn't map ECB, giving up\n");
		जाओ err_host_put;
	पूर्ण
	
	DEB(prपूर्णांकk("aha1740_probe: enable interrupt channel %d\n",irq_level));
	अगर (request_irq(irq_level,aha1740_पूर्णांकr_handle,irq_type ? 0 : IRQF_SHARED,
			"aha1740",shpnt)) अणु
		prपूर्णांकk(KERN_ERR "aha1740_probe: Unable to allocate IRQ %d.\n",
		       irq_level);
		जाओ err_unmap;
	पूर्ण

	eisa_set_drvdata (edev, shpnt);

	rc = scsi_add_host (shpnt, dev);
	अगर (rc)
		जाओ err_irq;

	scsi_scan_host (shpnt);
	वापस 0;

 err_irq:
 	मुक्त_irq(irq_level, shpnt);
 err_unmap:
	dma_unmap_single (&edev->dev, host->ecb_dma_addr,
			  माप (host->ecb), DMA_BIसूचीECTIONAL);
 err_host_put:
	scsi_host_put (shpnt);
 err_release_region:
	release_region(slotbase, SLOTSIZE);

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक aha1740_हटाओ (काष्ठा device *dev)
अणु
	काष्ठा Scsi_Host *shpnt = dev_get_drvdata(dev);
	काष्ठा aha1740_hostdata *host = HOSTDATA (shpnt);

	scsi_हटाओ_host(shpnt);
	
	मुक्त_irq (shpnt->irq, shpnt);
	dma_unmap_single (dev, host->ecb_dma_addr,
			  माप (host->ecb), DMA_BIसूचीECTIONAL);
	release_region (shpnt->io_port, SLOTSIZE);

	scsi_host_put (shpnt);
	
	वापस 0;
पूर्ण

अटल काष्ठा eisa_device_id aha1740_ids[] = अणु
	अणु "ADP0000" पूर्ण,		/* 1740  */
	अणु "ADP0001" पूर्ण,		/* 1740A */
	अणु "ADP0002" पूर्ण,		/* 1742A */
	अणु "ADP0400" पूर्ण,		/* 1744  */
	अणु "" पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(eisa, aha1740_ids);

अटल काष्ठा eisa_driver aha1740_driver = अणु
	.id_table = aha1740_ids,
	.driver   = अणु
		.name    = "aha1740",
		.probe   = aha1740_probe,
		.हटाओ  = aha1740_हटाओ,
	पूर्ण,
पूर्ण;

अटल __init पूर्णांक aha1740_init (व्योम)
अणु
	वापस eisa_driver_रेजिस्टर (&aha1740_driver);
पूर्ण

अटल __निकास व्योम aha1740_निकास (व्योम)
अणु
	eisa_driver_unरेजिस्टर (&aha1740_driver);
पूर्ण

module_init (aha1740_init);
module_निकास (aha1740_निकास);

MODULE_LICENSE("GPL");
