<शैली गुरु>
/*======================================================================

    A driver क्रम the Qlogic SCSI card

    qlogic_cs.c 1.79 2000/06/12 21:27:26

    The contents of this file are subject to the Mozilla Public
    License Version 1.1 (the "License"); you may not use this file
    except in compliance with the License. You may obtain a copy of
    the License at http://www.mozilla.org/MPL/

    Software distributed under the License is distributed on an "AS
    IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
    implied. See the License क्रम the specअगरic language governing
    rights and limitations under the License.

    The initial developer of the original code is David A. Hinds
    <dahinds@users.sourceक्रमge.net>.  Portions created by David A. Hinds
    are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.

    Alternatively, the contents of this file may be used under the
    terms of the GNU General Public License version 2 (the "GPL"), in which
    हाल the provisions of the GPL are applicable instead of the
    above.  If you wish to allow the use of your version of this file
    only under the terms of the GPL and not to allow others to use
    your version of this file under the MPL, indicate your decision
    by deleting the provisions above and replace them with the notice
    and other provisions required by the GPL.  If you करो not delete
    the provisions above, a recipient may use your version of this
    file under either the MPL or the GPL.
    
======================================================================*/

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/ioport.h>
#समावेश <यंत्र/पन.स>
#समावेश <scsi/scsi.h>
#समावेश <linux/major.h>
#समावेश <linux/blkdev.h>
#समावेश <scsi/scsi_ioctl.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "scsi.h"
#समावेश <scsi/scsi_host.h>
#समावेश "../qlogicfas408.h"

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ds.h>
#समावेश <pcmcia/ciscode.h>

/* Set the following to 2 to use normal पूर्णांकerrupt (active high/totempole-
 * tristate), otherwise use 0 (REQUIRED FOR PCMCIA) क्रम active low, खोलो
 * drain
 */
#घोषणा INT_TYPE	0

अटल अक्षर qlogic_name[] = "qlogic_cs";

अटल काष्ठा scsi_host_ढाँचा qlogicfas_driver_ढाँचा = अणु
	.module			= THIS_MODULE,
	.name			= qlogic_name,
	.proc_name		= qlogic_name,
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

/*====================================================================*/

प्रकार काष्ठा scsi_info_t अणु
	काष्ठा pcmcia_device	*p_dev;
	काष्ठा Scsi_Host *host;
	अचिन्हित लघु manf_id;
पूर्ण scsi_info_t;

अटल व्योम qlogic_release(काष्ठा pcmcia_device *link);
अटल व्योम qlogic_detach(काष्ठा pcmcia_device *p_dev);
अटल पूर्णांक qlogic_config(काष्ठा pcmcia_device * link);

अटल काष्ठा Scsi_Host *qlogic_detect(काष्ठा scsi_host_ढाँचा *host,
				काष्ठा pcmcia_device *link, पूर्णांक qbase, पूर्णांक qlirq)
अणु
	पूर्णांक qltyp;		/* type of chip */
	पूर्णांक qinitid;
	काष्ठा Scsi_Host *shost;	/* रेजिस्टरed host काष्ठाure */
	काष्ठा qlogicfas408_priv *priv;

	qltyp = qlogicfas408_get_chip_type(qbase, INT_TYPE);
	qinitid = host->this_id;
	अगर (qinitid < 0)
		qinitid = 7;	/* अगर no ID, use 7 */

	qlogicfas408_setup(qbase, qinitid, INT_TYPE);

	host->name = qlogic_name;
	shost = scsi_host_alloc(host, माप(काष्ठा qlogicfas408_priv));
	अगर (!shost)
		जाओ err;
	shost->io_port = qbase;
	shost->n_io_port = 16;
	shost->dma_channel = -1;
	अगर (qlirq != -1)
		shost->irq = qlirq;

	priv = get_priv_by_host(shost);
	priv->qlirq = qlirq;
	priv->qbase = qbase;
	priv->qinitid = qinitid;
	priv->shost = shost;
	priv->पूर्णांक_type = INT_TYPE;					

	अगर (request_irq(qlirq, qlogicfas408_ihandl, 0, qlogic_name, shost))
		जाओ मुक्त_scsi_host;

	प्र_लिखो(priv->qinfo,
		"Qlogicfas Driver version 0.46, chip %02X at %03X, IRQ %d, TPdma:%d",
		qltyp, qbase, qlirq, QL_TURBO_PDMA);

	अगर (scsi_add_host(shost, शून्य))
		जाओ मुक्त_पूर्णांकerrupt;

	scsi_scan_host(shost);

	वापस shost;

मुक्त_पूर्णांकerrupt:
	मुक्त_irq(qlirq, shost);

मुक्त_scsi_host:
	scsi_host_put(shost);
	
err:
	वापस शून्य;
पूर्ण
अटल पूर्णांक qlogic_probe(काष्ठा pcmcia_device *link)
अणु
	scsi_info_t *info;

	dev_dbg(&link->dev, "qlogic_attach()\n");

	/* Create new SCSI device */
	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;
	info->p_dev = link;
	link->priv = info;
	link->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_IO;
	link->config_regs = PRESENT_OPTION;

	वापस qlogic_config(link);
पूर्ण				/* qlogic_attach */

/*====================================================================*/

अटल व्योम qlogic_detach(काष्ठा pcmcia_device *link)
अणु
	dev_dbg(&link->dev, "qlogic_detach\n");

	qlogic_release(link);
	kमुक्त(link->priv);

पूर्ण				/* qlogic_detach */

/*====================================================================*/

अटल पूर्णांक qlogic_config_check(काष्ठा pcmcia_device *p_dev, व्योम *priv_data)
अणु
	p_dev->io_lines = 10;
	p_dev->resource[0]->flags &= ~IO_DATA_PATH_WIDTH;
	p_dev->resource[0]->flags |= IO_DATA_PATH_WIDTH_AUTO;

	अगर (p_dev->resource[0]->start == 0)
		वापस -ENODEV;

	वापस pcmcia_request_io(p_dev);
पूर्ण

अटल पूर्णांक qlogic_config(काष्ठा pcmcia_device * link)
अणु
	scsi_info_t *info = link->priv;
	पूर्णांक ret;
	काष्ठा Scsi_Host *host;

	dev_dbg(&link->dev, "qlogic_config\n");

	ret = pcmcia_loop_config(link, qlogic_config_check, शून्य);
	अगर (ret)
		जाओ failed;

	अगर (!link->irq)
		जाओ failed;

	ret = pcmcia_enable_device(link);
	अगर (ret)
		जाओ failed;

	अगर ((info->manf_id == MANFID_MACNICA) || (info->manf_id == MANFID_PIONEER) || (info->manf_id == 0x0098)) अणु
		/* set ATAcmd */
		outb(0xb4, link->resource[0]->start + 0xd);
		outb(0x24, link->resource[0]->start + 0x9);
		outb(0x04, link->resource[0]->start + 0xd);
	पूर्ण

	/* The KXL-810AN has a bigger IO port winकरोw */
	अगर (resource_size(link->resource[0]) == 32)
		host = qlogic_detect(&qlogicfas_driver_ढाँचा, link,
			link->resource[0]->start + 16, link->irq);
	अन्यथा
		host = qlogic_detect(&qlogicfas_driver_ढाँचा, link,
			link->resource[0]->start, link->irq);
	
	अगर (!host) अणु
		prपूर्णांकk(KERN_INFO "%s: no SCSI devices found\n", qlogic_name);
		जाओ failed;
	पूर्ण

	info->host = host;

	वापस 0;

failed:
	pcmcia_disable_device(link);
	वापस -ENODEV;
पूर्ण				/* qlogic_config */

/*====================================================================*/

अटल व्योम qlogic_release(काष्ठा pcmcia_device *link)
अणु
	scsi_info_t *info = link->priv;

	dev_dbg(&link->dev, "qlogic_release\n");

	scsi_हटाओ_host(info->host);

	मुक्त_irq(link->irq, info->host);
	pcmcia_disable_device(link);

	scsi_host_put(info->host);
पूर्ण

/*====================================================================*/

अटल पूर्णांक qlogic_resume(काष्ठा pcmcia_device *link)
अणु
	scsi_info_t *info = link->priv;
	पूर्णांक ret;

	ret = pcmcia_enable_device(link);
	अगर (ret)
		वापस ret;

	अगर ((info->manf_id == MANFID_MACNICA) ||
	    (info->manf_id == MANFID_PIONEER) ||
	    (info->manf_id == 0x0098)) अणु
		outb(0x80, link->resource[0]->start + 0xd);
		outb(0x24, link->resource[0]->start + 0x9);
		outb(0x04, link->resource[0]->start + 0xd);
	पूर्ण
	/* Ugggglllyyyy!!! */
	qlogicfas408_host_reset(शून्य);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pcmcia_device_id qlogic_ids[] = अणु
	PCMCIA_DEVICE_PROD_ID12("EIger Labs", "PCMCIA-to-SCSI Adapter", 0x88395fa7, 0x33b7a5e6),
	PCMCIA_DEVICE_PROD_ID12("EPSON", "SCSI-2 PC Card SC200", 0xd361772f, 0x299d1751),
	PCMCIA_DEVICE_PROD_ID12("MACNICA", "MIRACLE SCSI-II mPS110", 0x20841b68, 0xab3c3b6d),
	PCMCIA_DEVICE_PROD_ID12("MIDORI ELECTRONICS ", "CN-SC43", 0x6534382a, 0xd67eee79),
	PCMCIA_DEVICE_PROD_ID12("NEC", "PC-9801N-J03R", 0x18df0ba0, 0x24662e8a),
	PCMCIA_DEVICE_PROD_ID12("KME ", "KXLC003", 0x82375a27, 0xf68e5bf7),
	PCMCIA_DEVICE_PROD_ID12("KME ", "KXLC004", 0x82375a27, 0x68eace54),
	PCMCIA_DEVICE_PROD_ID12("KME", "KXLC101", 0x3faee676, 0x194250ec),
	PCMCIA_DEVICE_PROD_ID12("QLOGIC CORPORATION", "pc05", 0xd77b2930, 0xa85b2735),
	PCMCIA_DEVICE_PROD_ID12("QLOGIC CORPORATION", "pc05 rev 1.10", 0xd77b2930, 0x70f8b5f8),
	PCMCIA_DEVICE_PROD_ID123("KME", "KXLC002", "00", 0x3faee676, 0x81896b61, 0xf99f065f),
	PCMCIA_DEVICE_PROD_ID12("RATOC System Inc.", "SCSI2 CARD 37", 0x85c10e17, 0x1a2640c1),
	PCMCIA_DEVICE_PROD_ID12("TOSHIBA", "SCSC200A PC CARD SCSI", 0xb4585a1a, 0xa6f06ebe),
	PCMCIA_DEVICE_PROD_ID12("TOSHIBA", "SCSC200B PC CARD SCSI-10", 0xb4585a1a, 0x0a88dea0),
	/* these conflict with other cards! */
	/* PCMCIA_DEVICE_PROD_ID123("MACNICA", "MIRACLE SCSI", "mPS100", 0x20841b68, 0xf8dedaeb, 0x89f7fafb), */
	/* PCMCIA_DEVICE_PROD_ID123("MACNICA", "MIRACLE SCSI", "mPS100", 0x20841b68, 0xf8dedaeb, 0x89f7fafb), */
	PCMCIA_DEVICE_शून्य,
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, qlogic_ids);

अटल काष्ठा pcmcia_driver qlogic_cs_driver = अणु
	.owner		= THIS_MODULE,
	.name		= "qlogic_cs",
	.probe		= qlogic_probe,
	.हटाओ		= qlogic_detach,
	.id_table       = qlogic_ids,
	.resume		= qlogic_resume,
पूर्ण;

MODULE_AUTHOR("Tom Zerucha, Michael Griffith");
MODULE_DESCRIPTION("Driver for the PCMCIA Qlogic FAS SCSI controllers");
MODULE_LICENSE("GPL");
module_pcmcia_driver(qlogic_cs_driver);
