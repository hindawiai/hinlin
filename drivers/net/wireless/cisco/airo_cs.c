<शैली गुरु>
/*======================================================================

    Aironet driver क्रम 4500 and 4800 series cards

    This code is released under both the GPL version 2 and BSD licenses.
    Either license may be used.  The respective licenses are found at
    the end of this file.

    This code was developed by Benjamin Reed <breed@users.sourceक्रमge.net>
    including portions of which come from the Aironet PC4500
    Developer's Reference Manual and used with permission.  Copyright
    (C) 1999 Benjamin Reed.  All Rights Reserved.  Permission to use
    code in the Developer's manual was granted क्रम this driver by
    Aironet.

    In addition this module was derived from dummy_cs.
    The initial developer of dummy_cs is David A. Hinds
    <dahinds@users.sourceक्रमge.net>.  Portions created by David A. Hinds
    are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.

======================================================================*/

#अगर_घोषित __IN_PCMCIA_PACKAGE__
#समावेश <pcmcia/k_compat.h>
#पूर्ण_अगर
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/netdevice.h>

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/cisreg.h>
#समावेश <pcmcia/ds.h>

#समावेश <linux/पन.स>

#समावेश "airo.h"


/*====================================================================*/

MODULE_AUTHOR("Benjamin Reed");
MODULE_DESCRIPTION("Support for Cisco/Aironet 802.11 wireless ethernet "
		   "cards.  This is the module that links the PCMCIA card "
		   "with the airo module.");
MODULE_LICENSE("Dual BSD/GPL");

/*====================================================================*/

अटल पूर्णांक airo_config(काष्ठा pcmcia_device *link);
अटल व्योम airo_release(काष्ठा pcmcia_device *link);

अटल व्योम airo_detach(काष्ठा pcmcia_device *p_dev);

काष्ठा local_info अणु
	काष्ठा net_device *eth_dev;
पूर्ण;

अटल पूर्णांक airo_probe(काष्ठा pcmcia_device *p_dev)
अणु
	काष्ठा local_info *local;

	dev_dbg(&p_dev->dev, "airo_attach()\n");

	/* Allocate space क्रम निजी device-specअगरic data */
	local = kzalloc(माप(*local), GFP_KERNEL);
	अगर (!local)
		वापस -ENOMEM;

	p_dev->priv = local;

	वापस airo_config(p_dev);
पूर्ण /* airo_attach */

अटल व्योम airo_detach(काष्ठा pcmcia_device *link)
अणु
	dev_dbg(&link->dev, "airo_detach\n");

	airo_release(link);

	अगर (((काष्ठा local_info *)link->priv)->eth_dev) अणु
		stop_airo_card(((काष्ठा local_info *)link->priv)->eth_dev,
			       0);
	पूर्ण
	((काष्ठा local_info *)link->priv)->eth_dev = शून्य;

	kमुक्त(link->priv);
पूर्ण /* airo_detach */

अटल पूर्णांक airo_cs_config_check(काष्ठा pcmcia_device *p_dev, व्योम *priv_data)
अणु
	अगर (p_dev->config_index == 0)
		वापस -EINVAL;

	वापस pcmcia_request_io(p_dev);
पूर्ण


अटल पूर्णांक airo_config(काष्ठा pcmcia_device *link)
अणु
	पूर्णांक ret;

	dev_dbg(&link->dev, "airo_config\n");

	link->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_VPP |
		CONF_AUTO_AUDIO | CONF_AUTO_SET_IO;

	ret = pcmcia_loop_config(link, airo_cs_config_check, शून्य);
	अगर (ret)
		जाओ failed;

	अगर (!link->irq)
		जाओ failed;

	ret = pcmcia_enable_device(link);
	अगर (ret)
		जाओ failed;
	((काष्ठा local_info *)link->priv)->eth_dev =
		init_airo_card(link->irq,
			       link->resource[0]->start, 1, &link->dev);
	अगर (!((काष्ठा local_info *)link->priv)->eth_dev)
		जाओ failed;

	वापस 0;

 failed:
	airo_release(link);
	वापस -ENODEV;
पूर्ण /* airo_config */

अटल व्योम airo_release(काष्ठा pcmcia_device *link)
अणु
	dev_dbg(&link->dev, "airo_release\n");
	pcmcia_disable_device(link);
पूर्ण

अटल पूर्णांक airo_suspend(काष्ठा pcmcia_device *link)
अणु
	काष्ठा local_info *local = link->priv;

	netअगर_device_detach(local->eth_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक airo_resume(काष्ठा pcmcia_device *link)
अणु
	काष्ठा local_info *local = link->priv;

	अगर (link->खोलो) अणु
		reset_airo_card(local->eth_dev);
		netअगर_device_attach(local->eth_dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pcmcia_device_id airo_ids[] = अणु
	PCMCIA_DEVICE_MANF_CARD(0x015f, 0x000a),
	PCMCIA_DEVICE_MANF_CARD(0x015f, 0x0005),
	PCMCIA_DEVICE_MANF_CARD(0x015f, 0x0007),
	PCMCIA_DEVICE_MANF_CARD(0x0105, 0x0007),
	PCMCIA_DEVICE_शून्य,
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, airo_ids);

अटल काष्ठा pcmcia_driver airo_driver = अणु
	.owner		= THIS_MODULE,
	.name		= "airo_cs",
	.probe		= airo_probe,
	.हटाओ		= airo_detach,
	.id_table       = airo_ids,
	.suspend	= airo_suspend,
	.resume		= airo_resume,
पूर्ण;
module_pcmcia_driver(airo_driver);

/*
    This program is मुक्त software; you can redistribute it and/or
    modअगरy it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License क्रम more details.

    In addition:

    Redistribution and use in source and binary क्रमms, with or without
    modअगरication, are permitted provided that the following conditions
    are met:

    1. Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary क्रमm must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       करोcumentation and/or other materials provided with the distribution.
    3. The name of the author may not be used to enकरोrse or promote
       products derived from this software without specअगरic prior written
       permission.

    THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
    IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY सूचीECT,
    INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
    HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
    STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
    IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/
