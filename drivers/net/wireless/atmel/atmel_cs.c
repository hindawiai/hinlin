<शैली गुरु>
/*** -*- linux-c -*- **********************************************************

     Driver क्रम Aपंचांगel at76c502 at76c504 and at76c506 wireless cards.

        Copyright 2000-2001 ATMEL Corporation.
        Copyright 2003 Simon Kelley.

    This code was developed from version 2.1.1 of the Aपंचांगel drivers,
    released by Aपंचांगel corp. under the GPL in December 2002. It also
    includes code from the Linux aironet drivers (C) Benjamin Reed,
    and the Linux PCMCIA package, (C) David Hinds.

    For all queries about this code, please contact the current author,
    Simon Kelley <simon@thekelleys.org.uk> and not Aपंचांगel Corporation.

    This program is मुक्त software; you can redistribute it and/or modअगरy
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This software is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License क्रम more details.

    You should have received a copy of the GNU General Public License
    aदीर्घ with Aपंचांगel wireless lan drivers; अगर not, see
    <http://www.gnu.org/licenses/>.

******************************************************************************/

#अगर_घोषित __IN_PCMCIA_PACKAGE__
#समावेश <pcmcia/k_compat.h>
#पूर्ण_अगर
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/device.h>

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/cisreg.h>
#समावेश <pcmcia/ds.h>
#समावेश <pcmcia/ciscode.h>

#समावेश <यंत्र/पन.स>
#समावेश <linux/wireless.h>

#समावेश "atmel.h"


/*====================================================================*/

MODULE_AUTHOR("Simon Kelley");
MODULE_DESCRIPTION("Support for Atmel at76c50x 802.11 wireless ethernet cards.");
MODULE_LICENSE("GPL");

/*====================================================================*/

अटल पूर्णांक aपंचांगel_config(काष्ठा pcmcia_device *link);
अटल व्योम aपंचांगel_release(काष्ठा pcmcia_device *link);

अटल व्योम aपंचांगel_detach(काष्ठा pcmcia_device *p_dev);

काष्ठा local_info अणु
	काष्ठा net_device *eth_dev;
पूर्ण;

अटल पूर्णांक aपंचांगel_probe(काष्ठा pcmcia_device *p_dev)
अणु
	काष्ठा local_info *local;

	dev_dbg(&p_dev->dev, "atmel_attach()\n");

	/* Allocate space क्रम निजी device-specअगरic data */
	local = kzalloc(माप(*local), GFP_KERNEL);
	अगर (!local)
		वापस -ENOMEM;

	p_dev->priv = local;

	वापस aपंचांगel_config(p_dev);
पूर्ण /* aपंचांगel_attach */

अटल व्योम aपंचांगel_detach(काष्ठा pcmcia_device *link)
अणु
	dev_dbg(&link->dev, "atmel_detach\n");

	aपंचांगel_release(link);

	kमुक्त(link->priv);
पूर्ण

/* Call-back function to पूर्णांकerrogate PCMCIA-specअगरic inक्रमmation
   about the current existence of the card */
अटल पूर्णांक card_present(व्योम *arg)
अणु
	काष्ठा pcmcia_device *link = (काष्ठा pcmcia_device *)arg;

	अगर (pcmcia_dev_present(link))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_config_check(काष्ठा pcmcia_device *p_dev, व्योम *priv_data)
अणु
	अगर (p_dev->config_index == 0)
		वापस -EINVAL;

	वापस pcmcia_request_io(p_dev);
पूर्ण

अटल पूर्णांक aपंचांगel_config(काष्ठा pcmcia_device *link)
अणु
	पूर्णांक ret;
	स्थिर काष्ठा pcmcia_device_id *did;

	did = dev_get_drvdata(&link->dev);

	dev_dbg(&link->dev, "atmel_config\n");

	link->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_VPP |
		CONF_AUTO_AUDIO | CONF_AUTO_SET_IO;

	अगर (pcmcia_loop_config(link, aपंचांगel_config_check, शून्य))
		जाओ failed;

	अगर (!link->irq) अणु
		dev_err(&link->dev, "atmel: cannot assign IRQ: check that CONFIG_ISA is set in kernel config.");
		जाओ failed;
	पूर्ण

	ret = pcmcia_enable_device(link);
	अगर (ret)
		जाओ failed;

	((काष्ठा local_info *)link->priv)->eth_dev =
		init_aपंचांगel_card(link->irq,
				link->resource[0]->start,
				did ? did->driver_info : ATMEL_FW_TYPE_NONE,
				&link->dev,
				card_present,
				link);
	अगर (!((काष्ठा local_info *)link->priv)->eth_dev)
			जाओ failed;


	वापस 0;

 failed:
	aपंचांगel_release(link);
	वापस -ENODEV;
पूर्ण

अटल व्योम aपंचांगel_release(काष्ठा pcmcia_device *link)
अणु
	काष्ठा net_device *dev = ((काष्ठा local_info *)link->priv)->eth_dev;

	dev_dbg(&link->dev, "atmel_release\n");

	अगर (dev)
		stop_aपंचांगel_card(dev);
	((काष्ठा local_info *)link->priv)->eth_dev = शून्य;

	pcmcia_disable_device(link);
पूर्ण

अटल पूर्णांक aपंचांगel_suspend(काष्ठा pcmcia_device *link)
अणु
	काष्ठा local_info *local = link->priv;

	netअगर_device_detach(local->eth_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_resume(काष्ठा pcmcia_device *link)
अणु
	काष्ठा local_info *local = link->priv;

	aपंचांगel_खोलो(local->eth_dev);
	netअगर_device_attach(local->eth_dev);

	वापस 0;
पूर्ण

/*====================================================================*/
/* We use the driver_info field to store the correct firmware type क्रम a card. */

#घोषणा PCMCIA_DEVICE_MANF_CARD_INFO(manf, card, info) अणु \
	.match_flags = PCMCIA_DEV_ID_MATCH_MANF_ID| \
			PCMCIA_DEV_ID_MATCH_CARD_ID, \
	.manf_id = (manf), \
	.card_id = (card), \
        .driver_info = (kernel_uदीर्घ_t)(info), पूर्ण

#घोषणा PCMCIA_DEVICE_PROD_ID12_INFO(v1, v2, vh1, vh2, info) अणु \
	.match_flags = PCMCIA_DEV_ID_MATCH_PROD_ID1| \
			PCMCIA_DEV_ID_MATCH_PROD_ID2, \
	.prod_id = अणु (v1), (v2), शून्य, शून्य पूर्ण, \
	.prod_id_hash = अणु (vh1), (vh2), 0, 0 पूर्ण, \
        .driver_info = (kernel_uदीर्घ_t)(info), पूर्ण

अटल स्थिर काष्ठा pcmcia_device_id aपंचांगel_ids[] = अणु
	PCMCIA_DEVICE_MANF_CARD_INFO(0x0101, 0x0620, ATMEL_FW_TYPE_502_3COM),
	PCMCIA_DEVICE_MANF_CARD_INFO(0x0101, 0x0696, ATMEL_FW_TYPE_502_3COM),
	PCMCIA_DEVICE_MANF_CARD_INFO(0x01bf, 0x3302, ATMEL_FW_TYPE_502E),
	PCMCIA_DEVICE_MANF_CARD_INFO(0xd601, 0x0007, ATMEL_FW_TYPE_502),
	PCMCIA_DEVICE_PROD_ID12_INFO("11WAVE", "11WP611AL-E", 0x9eb2da1f, 0xc9a0d3f9, ATMEL_FW_TYPE_502E),
	PCMCIA_DEVICE_PROD_ID12_INFO("ATMEL", "AT76C502AR", 0xabda4164, 0x41b37e1f, ATMEL_FW_TYPE_502),
	PCMCIA_DEVICE_PROD_ID12_INFO("ATMEL", "AT76C502AR_D", 0xabda4164, 0x3675d704, ATMEL_FW_TYPE_502D),
	PCMCIA_DEVICE_PROD_ID12_INFO("ATMEL", "AT76C502AR_E", 0xabda4164, 0x4172e792, ATMEL_FW_TYPE_502E),
	PCMCIA_DEVICE_PROD_ID12_INFO("ATMEL", "AT76C504_R", 0xabda4164, 0x917f3d72, ATMEL_FW_TYPE_504_2958),
	PCMCIA_DEVICE_PROD_ID12_INFO("ATMEL", "AT76C504", 0xabda4164, 0x5040670a, ATMEL_FW_TYPE_504),
	PCMCIA_DEVICE_PROD_ID12_INFO("ATMEL", "AT76C504A", 0xabda4164, 0xe15ed87f, ATMEL_FW_TYPE_504A_2958),
	PCMCIA_DEVICE_PROD_ID12_INFO("BT", "Voyager 1020 Laptop Adapter", 0xae49b86a, 0x1e957cd5, ATMEL_FW_TYPE_502),
	PCMCIA_DEVICE_PROD_ID12_INFO("CNet", "CNWLC 11Mbps Wireless PC Card V-5", 0xbc477dde, 0x502fae6b, ATMEL_FW_TYPE_502E),
	PCMCIA_DEVICE_PROD_ID12_INFO("IEEE 802.11b", "Wireless LAN PC Card", 0x5b878724, 0x122f1df6, ATMEL_FW_TYPE_502),
	PCMCIA_DEVICE_PROD_ID12_INFO("IEEE 802.11b", "Wireless LAN Card S", 0x5b878724, 0x5fba533a, ATMEL_FW_TYPE_504_2958),
	PCMCIA_DEVICE_PROD_ID12_INFO("OEM", "11Mbps Wireless LAN PC Card V-3", 0xfea54c90, 0x1c5b0f68, ATMEL_FW_TYPE_502),
	PCMCIA_DEVICE_PROD_ID12_INFO("SMC", "2632W", 0xc4f8b18b, 0x30f38774, ATMEL_FW_TYPE_502D),
	PCMCIA_DEVICE_PROD_ID12_INFO("SMC", "2632W-V2", 0xc4f8b18b, 0x172d1377, ATMEL_FW_TYPE_502),
	PCMCIA_DEVICE_PROD_ID12_INFO("Wireless", "PC_CARD", 0xa407ecdd, 0x119f6314, ATMEL_FW_TYPE_502D),
	PCMCIA_DEVICE_PROD_ID12_INFO("WLAN", "802.11b PC CARD", 0x575c516c, 0xb1f6dbc4, ATMEL_FW_TYPE_502D),
	PCMCIA_DEVICE_PROD_ID12_INFO("LG", "LW2100N", 0xb474d43a, 0x6b1fec94, ATMEL_FW_TYPE_502E),
	PCMCIA_DEVICE_शून्य
पूर्ण;

MODULE_DEVICE_TABLE(pcmcia, aपंचांगel_ids);

अटल काष्ठा pcmcia_driver aपंचांगel_driver = अणु
	.owner		= THIS_MODULE,
	.name		= "atmel_cs",
	.probe          = aपंचांगel_probe,
	.हटाओ		= aपंचांगel_detach,
	.id_table	= aपंचांगel_ids,
	.suspend	= aपंचांगel_suspend,
	.resume		= aपंचांगel_resume,
पूर्ण;
module_pcmcia_driver(aपंचांगel_driver);

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
