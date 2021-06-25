<शैली गुरु>
/*======================================================================

    A driver क्रम Adaptec AHA152X-compatible PCMCIA SCSI cards.

    This driver supports the Adaptec AHA-1460, the New Media Bus
    Toaster, and the New Media Toast & Jam.
    
    aha152x_cs.c 1.54 2000/06/12 21:27:25

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
#समावेश <scsi/scsi.h>
#समावेश <linux/major.h>
#समावेश <linux/blkdev.h>
#समावेश <scsi/scsi_ioctl.h>

#समावेश "scsi.h"
#समावेश <scsi/scsi_host.h>
#समावेश "aha152x.h"

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ds.h>


/*====================================================================*/

/* Parameters that can be set with 'insmod' */

/* SCSI bus setup options */
अटल पूर्णांक host_id = 7;
अटल पूर्णांक reconnect = 1;
अटल पूर्णांक parity = 1;
अटल पूर्णांक synchronous = 1;
अटल पूर्णांक reset_delay = 100;
अटल पूर्णांक ext_trans = 0;

module_param(host_id, पूर्णांक, 0);
module_param(reconnect, पूर्णांक, 0);
module_param(parity, पूर्णांक, 0);
module_param(synchronous, पूर्णांक, 0);
module_param(reset_delay, पूर्णांक, 0);
module_param(ext_trans, पूर्णांक, 0);

MODULE_LICENSE("Dual MPL/GPL");

/*====================================================================*/

प्रकार काष्ठा scsi_info_t अणु
	काष्ठा pcmcia_device	*p_dev;
    काष्ठा Scsi_Host	*host;
पूर्ण scsi_info_t;

अटल व्योम aha152x_release_cs(काष्ठा pcmcia_device *link);
अटल व्योम aha152x_detach(काष्ठा pcmcia_device *p_dev);
अटल पूर्णांक aha152x_config_cs(काष्ठा pcmcia_device *link);

अटल पूर्णांक aha152x_probe(काष्ठा pcmcia_device *link)
अणु
    scsi_info_t *info;

    dev_dbg(&link->dev, "aha152x_attach()\n");

    /* Create new SCSI device */
    info = kzalloc(माप(*info), GFP_KERNEL);
    अगर (!info) वापस -ENOMEM;
    info->p_dev = link;
    link->priv = info;

    link->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_IO;
    link->config_regs = PRESENT_OPTION;

    वापस aha152x_config_cs(link);
पूर्ण /* aha152x_attach */

/*====================================================================*/

अटल व्योम aha152x_detach(काष्ठा pcmcia_device *link)
अणु
    dev_dbg(&link->dev, "aha152x_detach\n");

    aha152x_release_cs(link);

    /* Unlink device काष्ठाure, मुक्त bits */
    kमुक्त(link->priv);
पूर्ण /* aha152x_detach */

/*====================================================================*/

अटल पूर्णांक aha152x_config_check(काष्ठा pcmcia_device *p_dev, व्योम *priv_data)
अणु
	p_dev->io_lines = 10;

	/* For New Media T&J, look क्रम a SCSI winकरोw */
	अगर ((p_dev->resource[0]->end < 0x20) &&
		(p_dev->resource[1]->end >= 0x20))
		p_dev->resource[0]->start = p_dev->resource[1]->start;

	अगर (p_dev->resource[0]->start >= 0xffff)
		वापस -EINVAL;

	p_dev->resource[1]->start = p_dev->resource[1]->end = 0;
	p_dev->resource[0]->end = 0x20;
	p_dev->resource[0]->flags &= ~IO_DATA_PATH_WIDTH;
	p_dev->resource[0]->flags |= IO_DATA_PATH_WIDTH_AUTO;

	वापस pcmcia_request_io(p_dev);
पूर्ण

अटल पूर्णांक aha152x_config_cs(काष्ठा pcmcia_device *link)
अणु
    scsi_info_t *info = link->priv;
    काष्ठा aha152x_setup s;
    पूर्णांक ret;
    काष्ठा Scsi_Host *host;

    dev_dbg(&link->dev, "aha152x_config\n");

    ret = pcmcia_loop_config(link, aha152x_config_check, शून्य);
    अगर (ret)
	    जाओ failed;

    अगर (!link->irq)
	    जाओ failed;

    ret = pcmcia_enable_device(link);
    अगर (ret)
	    जाओ failed;
    
    /* Set configuration options क्रम the aha152x driver */
    स_रखो(&s, 0, माप(s));
    s.conf        = "PCMCIA setup";
    s.io_port     = link->resource[0]->start;
    s.irq         = link->irq;
    s.scsiid      = host_id;
    s.reconnect   = reconnect;
    s.parity      = parity;
    s.synchronous = synchronous;
    s.delay       = reset_delay;
    अगर (ext_trans)
        s.ext_trans = ext_trans;

    host = aha152x_probe_one(&s);
    अगर (host == शून्य) अणु
	prपूर्णांकk(KERN_INFO "aha152x_cs: no SCSI devices found\n");
	जाओ failed;
    पूर्ण

    info->host = host;

    वापस 0;

failed:
    aha152x_release_cs(link);
    वापस -ENODEV;
पूर्ण

अटल व्योम aha152x_release_cs(काष्ठा pcmcia_device *link)
अणु
	scsi_info_t *info = link->priv;

	aha152x_release(info->host);
	pcmcia_disable_device(link);
पूर्ण

अटल पूर्णांक aha152x_resume(काष्ठा pcmcia_device *link)
अणु
	scsi_info_t *info = link->priv;

	aha152x_host_reset_host(info->host);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pcmcia_device_id aha152x_ids[] = अणु
	PCMCIA_DEVICE_PROD_ID123("New Media", "SCSI", "Bus Toaster", 0xcdf7e4cc, 0x35f26476, 0xa8851d6e),
	PCMCIA_DEVICE_PROD_ID123("NOTEWORTHY", "SCSI", "Bus Toaster", 0xad89c6e8, 0x35f26476, 0xa8851d6e),
	PCMCIA_DEVICE_PROD_ID12("Adaptec, Inc.", "APA-1460 SCSI Host Adapter", 0x24ba9738, 0x3a3c3d20),
	PCMCIA_DEVICE_PROD_ID12("New Media Corporation", "Multimedia Sound/SCSI", 0x085a850b, 0x80a6535c),
	PCMCIA_DEVICE_PROD_ID12("NOTEWORTHY", "NWCOMB02 SCSI/AUDIO COMBO CARD", 0xad89c6e8, 0x5f9a615b),
	PCMCIA_DEVICE_शून्य,
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, aha152x_ids);

अटल काष्ठा pcmcia_driver aha152x_cs_driver = अणु
	.owner		= THIS_MODULE,
	.name		= "aha152x_cs",
	.probe		= aha152x_probe,
	.हटाओ		= aha152x_detach,
	.id_table       = aha152x_ids,
	.resume		= aha152x_resume,
पूर्ण;
module_pcmcia_driver(aha152x_cs_driver);
