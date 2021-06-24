<शैली गुरु>
/*
 * Qlogic FAS408 ISA card driver
 *
 * Copyright 1994, Tom Zerucha.   
 * tz@execpc.com
 * 
 * Redistributable under terms of the GNU General Public License
 *
 * For the aव्योमance of करोubt the "preferred form" of this code is one which
 * is in an खोलो non patent encumbered क्रमmat. Where cryptographic key signing
 * क्रमms part of the process of creating an executable the inक्रमmation
 * including keys needed to generate an equivalently functional executable
 * are deemed to be part of the source code.
 *
 * Check qlogicfas408.c क्रम more credits and info.
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

/* Set the following to 2 to use normal पूर्णांकerrupt (active high/totempole-
 * tristate), otherwise use 0 (REQUIRED FOR PCMCIA) क्रम active low, खोलो
 * drain
 */
#घोषणा INT_TYPE	2

अटल अक्षर qlogicfas_name[] = "qlogicfas";

/*
 *	Look क्रम qlogic card and init अगर found 
 */
 
अटल काष्ठा Scsi_Host *__qlogicfas_detect(काष्ठा scsi_host_ढाँचा *host,
								पूर्णांक qbase,
								पूर्णांक qlirq)
अणु
	पूर्णांक qltyp;		/* type of chip */
	पूर्णांक qinitid;
	काष्ठा Scsi_Host *hreg;	/* रेजिस्टरed host काष्ठाure */
	काष्ठा qlogicfas408_priv *priv;

	/*	Qlogic Cards only exist at 0x230 or 0x330 (the chip itself
	 *	decodes the address - I check 230 first since MIDI cards are
	 *	typically at 0x330
	 *
	 *	Theoretically, two Qlogic cards can coexist in the same प्रणाली.
	 *	This should work by simply using this as a loadable module क्रम
	 *	the second card, but I haven't tested this.
	 */

	अगर (!qbase || qlirq == -1)
		जाओ err;

	अगर (!request_region(qbase, 0x10, qlogicfas_name)) अणु
		prपूर्णांकk(KERN_INFO "%s: address %#x is busy\n", qlogicfas_name,
							      qbase);
		जाओ err;
	पूर्ण

	अगर (!qlogicfas408_detect(qbase, INT_TYPE)) अणु
		prपूर्णांकk(KERN_WARNING "%s: probe failed for %#x\n",
								qlogicfas_name,
								qbase);
		जाओ err_release_mem;
	पूर्ण

	prपूर्णांकk(KERN_INFO "%s: Using preset base address of %03x,"
			 " IRQ %d\n", qlogicfas_name, qbase, qlirq);

	qltyp = qlogicfas408_get_chip_type(qbase, INT_TYPE);
	qinitid = host->this_id;
	अगर (qinitid < 0)
		qinitid = 7;	/* अगर no ID, use 7 */

	qlogicfas408_setup(qbase, qinitid, INT_TYPE);

	hreg = scsi_host_alloc(host, माप(काष्ठा qlogicfas408_priv));
	अगर (!hreg)
		जाओ err_release_mem;
	priv = get_priv_by_host(hreg);
	hreg->io_port = qbase;
	hreg->n_io_port = 16;
	hreg->dma_channel = -1;
	अगर (qlirq != -1)
		hreg->irq = qlirq;
	priv->qbase = qbase;
	priv->qlirq = qlirq;
	priv->qinitid = qinitid;
	priv->shost = hreg;
	priv->पूर्णांक_type = INT_TYPE;

	प्र_लिखो(priv->qinfo,
		"Qlogicfas Driver version 0.46, chip %02X at %03X, IRQ %d, TPdma:%d",
		qltyp, qbase, qlirq, QL_TURBO_PDMA);
	host->name = qlogicfas_name;

	अगर (request_irq(qlirq, qlogicfas408_ihandl, 0, qlogicfas_name, hreg))
		जाओ मुक्त_scsi_host;

	अगर (scsi_add_host(hreg, शून्य))
		जाओ मुक्त_पूर्णांकerrupt;

	scsi_scan_host(hreg);

	वापस hreg;

मुक्त_पूर्णांकerrupt:
	मुक्त_irq(qlirq, hreg);

मुक्त_scsi_host:
	scsi_host_put(hreg);

err_release_mem:
	release_region(qbase, 0x10);
err:
	वापस शून्य;
पूर्ण

#घोषणा MAX_QLOGICFAS	8
अटल काष्ठा qlogicfas408_priv *cards;
अटल पूर्णांक iobase[MAX_QLOGICFAS];
अटल पूर्णांक irq[MAX_QLOGICFAS] = अणु [0 ... MAX_QLOGICFAS-1] = -1 पूर्ण;
module_param_hw_array(iobase, पूर्णांक, ioport, शून्य, 0);
module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0);
MODULE_PARM_DESC(iobase, "I/O address");
MODULE_PARM_DESC(irq, "IRQ");

अटल पूर्णांक qlogicfas_detect(काष्ठा scsi_host_ढाँचा *sht)
अणु
	काष्ठा Scsi_Host *shost;
	काष्ठा qlogicfas408_priv *priv;
	पूर्णांक num;

	क्रम (num = 0; num < MAX_QLOGICFAS; num++) अणु
		shost = __qlogicfas_detect(sht, iobase[num], irq[num]);
		अगर (shost == शून्य) अणु
			/* no more devices */
			अवरोध;
		पूर्ण
		priv = get_priv_by_host(shost);
		priv->next = cards;
		cards = priv;
	पूर्ण

	वापस num;
पूर्ण

अटल पूर्णांक qlogicfas_release(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा qlogicfas408_priv *priv = get_priv_by_host(shost);

	scsi_हटाओ_host(shost);
	अगर (shost->irq) अणु
		qlogicfas408_disable_पूर्णांकs(priv);	
		मुक्त_irq(shost->irq, shost);
	पूर्ण
	अगर (shost->io_port && shost->n_io_port)
		release_region(shost->io_port, shost->n_io_port);
	scsi_host_put(shost);

	वापस 0;
पूर्ण

/*
 *	The driver ढाँचा is also needed क्रम PCMCIA
 */
अटल काष्ठा scsi_host_ढाँचा qlogicfas_driver_ढाँचा = अणु
	.module			= THIS_MODULE,
	.name			= qlogicfas_name,
	.proc_name		= qlogicfas_name,
	.info			= qlogicfas408_info,
	.queuecommand		= qlogicfas408_queuecommand,
	.eh_पात_handler	= qlogicfas408_पात,
	.eh_host_reset_handler	= qlogicfas408_host_reset,
	.bios_param		= qlogicfas408_biosparam,
	.can_queue		= 1,
	.this_id		= -1,
	.sg_tablesize		= SG_ALL,
	.dma_boundary		= PAGE_SIZE - 1,
पूर्ण;

अटल __init पूर्णांक qlogicfas_init(व्योम)
अणु
	अगर (!qlogicfas_detect(&qlogicfas_driver_ढाँचा)) अणु
		/* no cards found */
		prपूर्णांकk(KERN_INFO "%s: no cards were found, please specify "
				 "I/O address and IRQ using iobase= and irq= "
				 "options", qlogicfas_name);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल __निकास व्योम qlogicfas_निकास(व्योम)
अणु
	काष्ठा qlogicfas408_priv *priv;

	क्रम (priv = cards; priv != शून्य; priv = priv->next)
		qlogicfas_release(priv->shost);
पूर्ण

MODULE_AUTHOR("Tom Zerucha, Michael Griffith");
MODULE_DESCRIPTION("Driver for the Qlogic FAS408 based ISA card");
MODULE_LICENSE("GPL");
module_init(qlogicfas_init);
module_निकास(qlogicfas_निकास);

