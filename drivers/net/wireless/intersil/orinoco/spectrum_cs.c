<शैली गुरु>
/*
 * Driver क्रम 802.11b cards using RAM-loadable Symbol firmware, such as
 * Symbol Wireless Networker LA4137, CompactFlash cards by Socket
 * Communications and Intel PRO/Wireless 2011B.
 *
 * The driver implements Symbol firmware करोwnload.  The rest is handled
 * in hermes.c and मुख्य.c.
 *
 * Utilities क्रम करोwnloading the Symbol firmware are available at
 * http://sourceक्रमge.net/projects/orinoco/
 *
 * Copyright (C) 2002-2005 Pavel Roskin <proski@gnu.org>
 * Portions based on orinoco_cs.c:
 *	Copyright (C) David Gibson, Linuxcare Australia
 * Portions based on Spectrum24tDnld.c from original spectrum24 driver:
 *	Copyright (C) Symbol Technologies.
 *
 * See copyright notice in file मुख्य.c.
 */

#घोषणा DRIVER_NAME "spectrum_cs"
#घोषणा PFX DRIVER_NAME ": "

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/cisreg.h>
#समावेश <pcmcia/ds.h>

#समावेश "orinoco.h"

/********************************************************************/
/* Module stuff							    */
/********************************************************************/

MODULE_AUTHOR("Pavel Roskin <proski@gnu.org>");
MODULE_DESCRIPTION("Driver for Symbol Spectrum24 Trilogy cards with firmware downloader");
MODULE_LICENSE("Dual MPL/GPL");

/* Module parameters */

/* Some D-Link cards have buggy CIS. They करो work at 5v properly, but
 * करोn't have any CIS entry क्रम it. This workaround it... */
अटल पूर्णांक ignore_cis_vcc; /* = 0 */
module_param(ignore_cis_vcc, पूर्णांक, 0);
MODULE_PARM_DESC(ignore_cis_vcc, "Allow voltage mismatch between card and socket");

/********************************************************************/
/* Data काष्ठाures						    */
/********************************************************************/

/* PCMCIA specअगरic device inक्रमmation (goes in the card field of
 * काष्ठा orinoco_निजी */
काष्ठा orinoco_pccard अणु
	काष्ठा pcmcia_device	*p_dev;
पूर्ण;

/********************************************************************/
/* Function prototypes						    */
/********************************************************************/

अटल पूर्णांक spectrum_cs_config(काष्ठा pcmcia_device *link);
अटल व्योम spectrum_cs_release(काष्ठा pcmcia_device *link);

/* Constants क्रम the CISREG_CCSR रेजिस्टर */
#घोषणा HCR_RUN		0x07	/* run firmware after reset */
#घोषणा HCR_IDLE	0x0E	/* करोn't run firmware after reset */
#घोषणा HCR_MEM16	0x10	/* memory width bit, should be preserved */


/*
 * Reset the card using configuration रेजिस्टरs COR and CCSR.
 * If IDLE is 1, stop the firmware, so that it can be safely rewritten.
 */
अटल पूर्णांक
spectrum_reset(काष्ठा pcmcia_device *link, पूर्णांक idle)
अणु
	पूर्णांक ret;
	u8 save_cor;
	u8 ccsr;

	/* Doing it अगर hardware is gone is guaranteed crash */
	अगर (!pcmcia_dev_present(link))
		वापस -ENODEV;

	/* Save original COR value */
	ret = pcmcia_पढ़ो_config_byte(link, CISREG_COR, &save_cor);
	अगर (ret)
		जाओ failed;

	/* Soft-Reset card */
	ret = pcmcia_ग_लिखो_config_byte(link, CISREG_COR,
				(save_cor | COR_SOFT_RESET));
	अगर (ret)
		जाओ failed;
	udelay(1000);

	/* Read CCSR */
	ret = pcmcia_पढ़ो_config_byte(link, CISREG_CCSR, &ccsr);
	अगर (ret)
		जाओ failed;

	/*
	 * Start or stop the firmware.  Memory width bit should be
	 * preserved from the value we've just पढ़ो.
	 */
	ccsr = (idle ? HCR_IDLE : HCR_RUN) | (ccsr & HCR_MEM16);
	ret = pcmcia_ग_लिखो_config_byte(link, CISREG_CCSR, ccsr);
	अगर (ret)
		जाओ failed;
	udelay(1000);

	/* Restore original COR configuration index */
	ret = pcmcia_ग_लिखो_config_byte(link, CISREG_COR,
				(save_cor & ~COR_SOFT_RESET));
	अगर (ret)
		जाओ failed;
	udelay(1000);
	वापस 0;

failed:
	वापस -ENODEV;
पूर्ण

/********************************************************************/
/* Device methods						    */
/********************************************************************/

अटल पूर्णांक
spectrum_cs_hard_reset(काष्ठा orinoco_निजी *priv)
अणु
	काष्ठा orinoco_pccard *card = priv->card;
	काष्ठा pcmcia_device *link = card->p_dev;

	/* Soft reset using COR and HCR */
	spectrum_reset(link, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक
spectrum_cs_stop_firmware(काष्ठा orinoco_निजी *priv, पूर्णांक idle)
अणु
	काष्ठा orinoco_pccard *card = priv->card;
	काष्ठा pcmcia_device *link = card->p_dev;

	वापस spectrum_reset(link, idle);
पूर्ण

/********************************************************************/
/* PCMCIA stuff							    */
/********************************************************************/

अटल पूर्णांक
spectrum_cs_probe(काष्ठा pcmcia_device *link)
अणु
	काष्ठा orinoco_निजी *priv;
	काष्ठा orinoco_pccard *card;

	priv = alloc_orinocodev(माप(*card), &link->dev,
				spectrum_cs_hard_reset,
				spectrum_cs_stop_firmware);
	अगर (!priv)
		वापस -ENOMEM;
	card = priv->card;

	/* Link both काष्ठाures together */
	card->p_dev = link;
	link->priv = priv;

	वापस spectrum_cs_config(link);
पूर्ण				/* spectrum_cs_attach */

अटल व्योम spectrum_cs_detach(काष्ठा pcmcia_device *link)
अणु
	काष्ठा orinoco_निजी *priv = link->priv;

	orinoco_अगर_del(priv);

	spectrum_cs_release(link);

	मुक्त_orinocodev(priv);
पूर्ण				/* spectrum_cs_detach */

अटल पूर्णांक spectrum_cs_config_check(काष्ठा pcmcia_device *p_dev,
				    व्योम *priv_data)
अणु
	अगर (p_dev->config_index == 0)
		वापस -EINVAL;

	वापस pcmcia_request_io(p_dev);
पूर्ण;

अटल पूर्णांक
spectrum_cs_config(काष्ठा pcmcia_device *link)
अणु
	काष्ठा orinoco_निजी *priv = link->priv;
	काष्ठा hermes *hw = &priv->hw;
	पूर्णांक ret;
	व्योम __iomem *mem;

	link->config_flags |= CONF_AUTO_SET_VPP | CONF_AUTO_CHECK_VCC |
		CONF_AUTO_SET_IO | CONF_ENABLE_IRQ;
	अगर (ignore_cis_vcc)
		link->config_flags &= ~CONF_AUTO_CHECK_VCC;
	ret = pcmcia_loop_config(link, spectrum_cs_config_check, शून्य);
	अगर (ret) अणु
		अगर (!ignore_cis_vcc)
			prपूर्णांकk(KERN_ERR PFX "GetNextTuple(): No matching "
			       "CIS configuration.  Maybe you need the "
			       "ignore_cis_vcc=1 parameter.\n");
		जाओ failed;
	पूर्ण

	mem = ioport_map(link->resource[0]->start,
			resource_size(link->resource[0]));
	अगर (!mem)
		जाओ failed;

	/* We initialize the hermes काष्ठाure beक्रमe completing PCMCIA
	 * configuration just in हाल the पूर्णांकerrupt handler माला_लो
	 * called. */
	hermes_काष्ठा_init(hw, mem, HERMES_16BIT_REGSPACING);
	hw->eeprom_pda = true;

	ret = pcmcia_request_irq(link, orinoco_पूर्णांकerrupt);
	अगर (ret)
		जाओ failed;

	ret = pcmcia_enable_device(link);
	अगर (ret)
		जाओ failed;

	/* Reset card */
	अगर (spectrum_cs_hard_reset(priv) != 0)
		जाओ failed;

	/* Initialise the मुख्य driver */
	अगर (orinoco_init(priv) != 0) अणु
		prपूर्णांकk(KERN_ERR PFX "orinoco_init() failed\n");
		जाओ failed;
	पूर्ण

	/* Register an पूर्णांकerface with the stack */
	अगर (orinoco_अगर_add(priv, link->resource[0]->start,
			   link->irq, शून्य) != 0) अणु
		prपूर्णांकk(KERN_ERR PFX "orinoco_if_add() failed\n");
		जाओ failed;
	पूर्ण

	वापस 0;

 failed:
	spectrum_cs_release(link);
	वापस -ENODEV;
पूर्ण				/* spectrum_cs_config */

अटल व्योम
spectrum_cs_release(काष्ठा pcmcia_device *link)
अणु
	काष्ठा orinoco_निजी *priv = link->priv;
	अचिन्हित दीर्घ flags;

	/* We're committed to taking the device away now, so mark the
	 * hardware as unavailable */
	priv->hw.ops->lock_irqsave(&priv->lock, &flags);
	priv->hw_unavailable++;
	priv->hw.ops->unlock_irqrestore(&priv->lock, &flags);

	pcmcia_disable_device(link);
	अगर (priv->hw.iobase)
		ioport_unmap(priv->hw.iobase);
पूर्ण				/* spectrum_cs_release */


अटल पूर्णांक
spectrum_cs_suspend(काष्ठा pcmcia_device *link)
अणु
	काष्ठा orinoco_निजी *priv = link->priv;

	/* Mark the device as stopped, to block IO until later */
	orinoco_करोwn(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक
spectrum_cs_resume(काष्ठा pcmcia_device *link)
अणु
	काष्ठा orinoco_निजी *priv = link->priv;
	पूर्णांक err = orinoco_up(priv);

	वापस err;
पूर्ण


/********************************************************************/
/* Module initialization					    */
/********************************************************************/

अटल स्थिर काष्ठा pcmcia_device_id spectrum_cs_ids[] = अणु
	PCMCIA_DEVICE_MANF_CARD(0x026c, 0x0001), /* Symbol Spectrum24 LA4137 */
	PCMCIA_DEVICE_MANF_CARD(0x0104, 0x0001), /* Socket Communications CF */
	PCMCIA_DEVICE_PROD_ID12("Intel", "PRO/Wireless LAN PC Card", 0x816cc815, 0x6fbf459a), /* 2011B, not 2011 */
	PCMCIA_DEVICE_शून्य,
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, spectrum_cs_ids);

अटल काष्ठा pcmcia_driver orinoco_driver = अणु
	.owner		= THIS_MODULE,
	.name		= DRIVER_NAME,
	.probe		= spectrum_cs_probe,
	.हटाओ		= spectrum_cs_detach,
	.suspend	= spectrum_cs_suspend,
	.resume		= spectrum_cs_resume,
	.id_table       = spectrum_cs_ids,
पूर्ण;
module_pcmcia_driver(orinoco_driver);
