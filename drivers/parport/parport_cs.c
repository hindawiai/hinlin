<शैली गुरु>
/*======================================================================

    A driver क्रम PCMCIA parallel port adapters

    (specअगरically, क्रम the Quatech SPP-100 EPP card: other cards will
    probably require driver tweaks)
    
    parport_cs.c 1.29 2002/10/11 06:57:41

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
    terms of the GNU General Public License version 2 (the "GPL"), in
    which हाल the provisions of the GPL are applicable instead of the
    above.  If you wish to allow the use of your version of this file
    only under the terms of the GPL and not to allow others to use
    your version of this file under the MPL, indicate your decision
    by deleting the provisions above and replace them with the notice
    and other provisions required by the GPL.  If you करो not delete
    the provisions above, a recipient may use your version of this
    file under either the MPL or the GPL.
    
======================================================================*/

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/ioport.h>
#समावेश <linux/major.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <linux/parport.h>
#समावेश <linux/parport_pc.h>

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ds.h>
#समावेश <pcmcia/cisreg.h>
#समावेश <pcmcia/ciscode.h>

/*====================================================================*/

/* Module parameters */

MODULE_AUTHOR("David Hinds <dahinds@users.sourceforge.net>");
MODULE_DESCRIPTION("PCMCIA parallel port card driver");
MODULE_LICENSE("Dual MPL/GPL");

#घोषणा INT_MODULE_PARM(n, v) अटल पूर्णांक n = v; module_param(n, पूर्णांक, 0)

INT_MODULE_PARM(epp_mode, 1);


/*====================================================================*/

#घोषणा FORCE_EPP_MODE	0x08

प्रकार काष्ठा parport_info_t अणु
	काष्ठा pcmcia_device	*p_dev;
    पूर्णांक			ndev;
    काष्ठा parport	*port;
पूर्ण parport_info_t;

अटल व्योम parport_detach(काष्ठा pcmcia_device *p_dev);
अटल पूर्णांक parport_config(काष्ठा pcmcia_device *link);
अटल व्योम parport_cs_release(काष्ठा pcmcia_device *);

अटल पूर्णांक parport_probe(काष्ठा pcmcia_device *link)
अणु
    parport_info_t *info;

    dev_dbg(&link->dev, "parport_attach()\n");

    /* Create new parport device */
    info = kzalloc(माप(*info), GFP_KERNEL);
    अगर (!info) वापस -ENOMEM;
    link->priv = info;
    info->p_dev = link;

    link->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_IO;

    वापस parport_config(link);
पूर्ण /* parport_attach */

अटल व्योम parport_detach(काष्ठा pcmcia_device *link)
अणु
    dev_dbg(&link->dev, "parport_detach\n");

    parport_cs_release(link);

    kमुक्त(link->priv);
पूर्ण /* parport_detach */

अटल पूर्णांक parport_config_check(काष्ठा pcmcia_device *p_dev, व्योम *priv_data)
अणु
	p_dev->resource[0]->flags &= ~IO_DATA_PATH_WIDTH;
	p_dev->resource[0]->flags |= IO_DATA_PATH_WIDTH_8;
	p_dev->resource[1]->flags &= ~IO_DATA_PATH_WIDTH;
	p_dev->resource[1]->flags |= IO_DATA_PATH_WIDTH_8;

	वापस pcmcia_request_io(p_dev);
पूर्ण

अटल पूर्णांक parport_config(काष्ठा pcmcia_device *link)
अणु
    parport_info_t *info = link->priv;
    काष्ठा parport *p;
    पूर्णांक ret;

    dev_dbg(&link->dev, "parport_config\n");

    अगर (epp_mode)
	    link->config_index |= FORCE_EPP_MODE;

    ret = pcmcia_loop_config(link, parport_config_check, शून्य);
    अगर (ret)
	    जाओ failed;

    अगर (!link->irq)
	    जाओ failed;
    ret = pcmcia_enable_device(link);
    अगर (ret)
	    जाओ failed;

    p = parport_pc_probe_port(link->resource[0]->start,
			      link->resource[1]->start,
			      link->irq, PARPORT_DMA_NONE,
			      &link->dev, IRQF_SHARED);
    अगर (p == शून्य) अणु
	    pr_notice("parport_cs: parport_pc_probe_port() at 0x%3x, irq %u failed\n",
		      (अचिन्हित पूर्णांक)link->resource[0]->start, link->irq);
	जाओ failed;
    पूर्ण

    p->modes |= PARPORT_MODE_PCSPP;
    अगर (epp_mode)
	p->modes |= PARPORT_MODE_TRISTATE | PARPORT_MODE_EPP;
    info->ndev = 1;
    info->port = p;

    वापस 0;

failed:
	parport_cs_release(link);
	kमुक्त(link->priv);
	वापस -ENODEV;
पूर्ण /* parport_config */

अटल व्योम parport_cs_release(काष्ठा pcmcia_device *link)
अणु
	parport_info_t *info = link->priv;

	dev_dbg(&link->dev, "parport_release\n");

	अगर (info->ndev) अणु
		काष्ठा parport *p = info->port;
		parport_pc_unरेजिस्टर_port(p);
	पूर्ण
	info->ndev = 0;

	pcmcia_disable_device(link);
पूर्ण /* parport_cs_release */


अटल स्थिर काष्ठा pcmcia_device_id parport_ids[] = अणु
	PCMCIA_DEVICE_FUNC_ID(3),
	PCMCIA_MFC_DEVICE_PROD_ID12(1,"Elan","Serial+Parallel Port: SP230",0x3beb8cf2,0xdb9e58bc),
	PCMCIA_DEVICE_MANF_CARD(0x0137, 0x0003),
	PCMCIA_DEVICE_शून्य
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, parport_ids);

अटल काष्ठा pcmcia_driver parport_cs_driver = अणु
	.owner		= THIS_MODULE,
	.name		= "parport_cs",
	.probe		= parport_probe,
	.हटाओ		= parport_detach,
	.id_table	= parport_ids,
पूर्ण;
module_pcmcia_driver(parport_cs_driver);
