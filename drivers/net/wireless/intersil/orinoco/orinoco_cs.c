<शैली गुरु>
/* orinoco_cs.c (क्रमmerly known as dldwd_cs.c)
 *
 * A driver क्रम "Hermes" chipset based PCMCIA wireless adaptors, such
 * as the Lucent WavelanIEEE/Orinoco cards and their OEM (Cabletron/
 * EnteraSys RoamAbout 802.11, ELSA Airlancer, Melco Buffalo and others).
 * It should also be usable on various Prism II based cards such as the
 * Linksys, D-Link and Farallon Skyline. It should also work on Symbol
 * cards such as the 3Com AirConnect and Ericsson WLAN.
 *
 * Copyright notice & release notes in file मुख्य.c
 */

#घोषणा DRIVER_NAME "orinoco_cs"
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

MODULE_AUTHOR("David Gibson <hermes@gibson.dropbear.id.au>");
MODULE_DESCRIPTION("Driver for PCMCIA Lucent Orinoco,"
		   " Prism II based and similar wireless cards");
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

	/* Used to handle hard reset */
	/* yuck, we need this hack to work around the insanity of the
	 * PCMCIA layer */
	अचिन्हित दीर्घ hard_reset_in_progress;
पूर्ण;


/********************************************************************/
/* Function prototypes						    */
/********************************************************************/

अटल पूर्णांक orinoco_cs_config(काष्ठा pcmcia_device *link);
अटल व्योम orinoco_cs_release(काष्ठा pcmcia_device *link);
अटल व्योम orinoco_cs_detach(काष्ठा pcmcia_device *p_dev);

/********************************************************************/
/* Device methods						    */
/********************************************************************/

अटल पूर्णांक
orinoco_cs_hard_reset(काष्ठा orinoco_निजी *priv)
अणु
	काष्ठा orinoco_pccard *card = priv->card;
	काष्ठा pcmcia_device *link = card->p_dev;
	पूर्णांक err;

	/* We need atomic ops here, because we're not holding the lock */
	set_bit(0, &card->hard_reset_in_progress);

	err = pcmcia_reset_card(link->socket);
	अगर (err)
		वापस err;

	msleep(100);
	clear_bit(0, &card->hard_reset_in_progress);

	वापस 0;
पूर्ण

/********************************************************************/
/* PCMCIA stuff							    */
/********************************************************************/

अटल पूर्णांक
orinoco_cs_probe(काष्ठा pcmcia_device *link)
अणु
	काष्ठा orinoco_निजी *priv;
	काष्ठा orinoco_pccard *card;

	priv = alloc_orinocodev(माप(*card), &link->dev,
				orinoco_cs_hard_reset, शून्य);
	अगर (!priv)
		वापस -ENOMEM;
	card = priv->card;

	/* Link both काष्ठाures together */
	card->p_dev = link;
	link->priv = priv;

	वापस orinoco_cs_config(link);
पूर्ण				/* orinoco_cs_attach */

अटल व्योम orinoco_cs_detach(काष्ठा pcmcia_device *link)
अणु
	काष्ठा orinoco_निजी *priv = link->priv;

	orinoco_अगर_del(priv);

	orinoco_cs_release(link);

	wiphy_unरेजिस्टर(priv_to_wiphy(priv));
	मुक्त_orinocodev(priv);
पूर्ण				/* orinoco_cs_detach */

अटल पूर्णांक orinoco_cs_config_check(काष्ठा pcmcia_device *p_dev, व्योम *priv_data)
अणु
	अगर (p_dev->config_index == 0)
		वापस -EINVAL;

	वापस pcmcia_request_io(p_dev);
पूर्ण;

अटल पूर्णांक
orinoco_cs_config(काष्ठा pcmcia_device *link)
अणु
	काष्ठा orinoco_निजी *priv = link->priv;
	काष्ठा hermes *hw = &priv->hw;
	पूर्णांक ret;
	व्योम __iomem *mem;

	link->config_flags |= CONF_AUTO_SET_VPP | CONF_AUTO_CHECK_VCC |
		CONF_AUTO_SET_IO | CONF_ENABLE_IRQ;
	अगर (ignore_cis_vcc)
		link->config_flags &= ~CONF_AUTO_CHECK_VCC;
	ret = pcmcia_loop_config(link, orinoco_cs_config_check, शून्य);
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

	ret = pcmcia_request_irq(link, orinoco_पूर्णांकerrupt);
	अगर (ret)
		जाओ failed;

	ret = pcmcia_enable_device(link);
	अगर (ret)
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
	orinoco_cs_release(link);
	वापस -ENODEV;
पूर्ण				/* orinoco_cs_config */

अटल व्योम
orinoco_cs_release(काष्ठा pcmcia_device *link)
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
पूर्ण				/* orinoco_cs_release */

अटल पूर्णांक orinoco_cs_suspend(काष्ठा pcmcia_device *link)
अणु
	काष्ठा orinoco_निजी *priv = link->priv;
	काष्ठा orinoco_pccard *card = priv->card;

	/* This is probably racy, but I can't think of
	   a better way, लघु of rewriting the PCMCIA
	   layer to not suck :-( */
	अगर (!test_bit(0, &card->hard_reset_in_progress))
		orinoco_करोwn(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक orinoco_cs_resume(काष्ठा pcmcia_device *link)
अणु
	काष्ठा orinoco_निजी *priv = link->priv;
	काष्ठा orinoco_pccard *card = priv->card;
	पूर्णांक err = 0;

	अगर (!test_bit(0, &card->hard_reset_in_progress))
		err = orinoco_up(priv);

	वापस err;
पूर्ण


/********************************************************************/
/* Module initialization					    */
/********************************************************************/

अटल स्थिर काष्ठा pcmcia_device_id orinoco_cs_ids[] = अणु
	PCMCIA_DEVICE_MANF_CARD(0x0101, 0x0777), /* 3Com AirConnect PCI 777A */
	PCMCIA_DEVICE_MANF_CARD(0x016b, 0x0001), /* Ericsson WLAN Card C11 */
	PCMCIA_DEVICE_MANF_CARD(0x01eb, 0x080a), /* Nortel Networks eMobility 802.11 Wireless Adapter */
	PCMCIA_DEVICE_MANF_CARD(0x0261, 0x0002), /* AirWay 802.11 Adapter (PCMCIA) */
	PCMCIA_DEVICE_MANF_CARD(0x0268, 0x0001), /* ARtem Onair */
	PCMCIA_DEVICE_MANF_CARD(0x0268, 0x0003), /* ARtem Onair Comcard 11 */
	PCMCIA_DEVICE_MANF_CARD(0x026f, 0x0305), /* Buffalo WLI-PCM-S11 */
	PCMCIA_DEVICE_MANF_CARD(0x02aa, 0x0002), /* ASUS SpaceLink WL-100 */
	PCMCIA_DEVICE_MANF_CARD(0x02ac, 0x0002), /* SpeedStream SS1021 Wireless Adapter */
	PCMCIA_DEVICE_MANF_CARD(0x02ac, 0x3021), /* SpeedStream Wireless Adapter */
	PCMCIA_DEVICE_MANF_CARD(0x14ea, 0xb001), /* PLANEX RoadLannerWave GW-NS11H */
	PCMCIA_DEVICE_PROD_ID12("3Com", "3CRWE737A AirConnect Wireless LAN PC Card", 0x41240e5b, 0x56010af3),
	PCMCIA_DEVICE_PROD_ID12("Allied Telesyn", "AT-WCL452 Wireless PCMCIA Radio", 0x5cd01705, 0x4271660f),
	PCMCIA_DEVICE_PROD_ID12("ASUS", "802_11B_CF_CARD_25", 0x78fc06ee, 0x45a50c1e),
	PCMCIA_DEVICE_PROD_ID12("ASUS", "802_11b_PC_CARD_25", 0x78fc06ee, 0xdb9aa842),
	PCMCIA_DEVICE_PROD_ID12("Avaya Communication", "Avaya Wireless PC Card", 0xd8a43b78, 0x0d341169),
	PCMCIA_DEVICE_PROD_ID12("BENQ", "AWL100 PCMCIA ADAPTER", 0x35dadc74, 0x01f7fedb),
	PCMCIA_DEVICE_PROD_ID12("Cabletron", "RoamAbout 802.11 DS", 0x32d445f5, 0xedeffd90),
	PCMCIA_DEVICE_PROD_ID12("D-Link Corporation", "D-Link DWL-650H 11Mbps WLAN Adapter", 0xef544d24, 0xcd8ea916),
	PCMCIA_DEVICE_PROD_ID12("ELSA", "AirLancer MC-11", 0x4507a33a, 0xef54f0e3),
	PCMCIA_DEVICE_PROD_ID12("HyperLink", "Wireless PC Card 11Mbps", 0x56cc3f1a, 0x0bcf220c),
	PCMCIA_DEVICE_PROD_ID12("Intel", "PRO/Wireless 2011 LAN PC Card", 0x816cc815, 0x07f58077),
	PCMCIA_DEVICE_PROD_ID12("LeArtery", "SYNCBYAIR 11Mbps Wireless LAN PC Card", 0x7e3b326a, 0x49893e92),
	PCMCIA_DEVICE_PROD_ID12("Lucent Technologies", "WaveLAN/IEEE", 0x23eb9949, 0xc562e72a),
	PCMCIA_DEVICE_PROD_ID12("MELCO", "WLI-PCM-L11", 0x481e0094, 0x7360e410),
	PCMCIA_DEVICE_PROD_ID12("MELCO", "WLI-PCM-L11G", 0x481e0094, 0xf57ca4b3),
	PCMCIA_DEVICE_PROD_ID12("NCR", "WaveLAN/IEEE", 0x24358cd4, 0xc562e72a),
	PCMCIA_DEVICE_PROD_ID12("Nortel Networks", "emobility 802.11 Wireless LAN PC Card", 0x2d617ea0, 0x88cd5767),
	PCMCIA_DEVICE_PROD_ID12("OTC", "Wireless AirEZY 2411-PCC WLAN Card", 0x4ac44287, 0x235a6bed),
	PCMCIA_DEVICE_PROD_ID12("PROXIM", "LAN PC CARD HARMONY 80211B", 0xc6536a5e, 0x090c3cd9),
	PCMCIA_DEVICE_PROD_ID12("PROXIM", "LAN PCI CARD HARMONY 80211B", 0xc6536a5e, 0x9f494e26),
	PCMCIA_DEVICE_PROD_ID12("SAMSUNG", "11Mbps WLAN Card", 0x43d74cb4, 0x579bd91b),
	PCMCIA_DEVICE_PROD_ID12("Symbol Technologies", "LA4111 Spectrum24 Wireless LAN PC Card", 0x3f02b4d6, 0x3663cb0e),
	PCMCIA_DEVICE_MANF_CARD_PROD_ID3(0x0156, 0x0002, "Version 01.01", 0xd27deb1a), /* Lucent Orinoco */
#अगर_घोषित CONFIG_HERMES_PRISM
	/* Only entries that certainly identअगरy Prism chipset */
	PCMCIA_DEVICE_MANF_CARD(0x000b, 0x7100), /* SonicWALL Long Range Wireless Card */
	PCMCIA_DEVICE_MANF_CARD(0x000b, 0x7300), /* Sohoware NCP110, Philips 802.11b */
	PCMCIA_DEVICE_MANF_CARD(0x0089, 0x0002), /* AnyPoपूर्णांक(TM) Wireless II PC Card */
	PCMCIA_DEVICE_MANF_CARD(0x0126, 0x8000), /* PROXIM RangeLAN-DS/LAN PC CARD */
	PCMCIA_DEVICE_MANF_CARD(0x0138, 0x0002), /* Compaq WL100 11 Mbps Wireless Adapter */
	PCMCIA_DEVICE_MANF_CARD(0x01ff, 0x0008), /* Intermec MobileLAN 11Mbps 802.11b WLAN Card */
	PCMCIA_DEVICE_MANF_CARD(0x0250, 0x0002), /* Samsung SWL2000-N 11Mb/s WLAN Card */
	PCMCIA_DEVICE_MANF_CARD(0x0274, 0x1612), /* Linksys WPC11 Version 2.5 */
	PCMCIA_DEVICE_MANF_CARD(0x0274, 0x1613), /* Linksys WPC11 Version 3 */
	PCMCIA_DEVICE_MANF_CARD(0x028a, 0x0002), /* Compaq HNW-100 11 Mbps Wireless Adapter */
	PCMCIA_DEVICE_MANF_CARD(0x028a, 0x0673), /* Linksys WCF12 Wireless CompactFlash Card */
	PCMCIA_DEVICE_MANF_CARD(0x50c2, 0x7300), /* Airvast WN-100 */
	PCMCIA_DEVICE_MANF_CARD(0x9005, 0x0021), /* Adaptec Ultra Wireless ANW-8030 */
	PCMCIA_DEVICE_MANF_CARD(0xc001, 0x0008), /* CONTEC FLEXSCAN/FX-DDS110-PCC */
	PCMCIA_DEVICE_MANF_CARD(0xc250, 0x0002), /* Conceptronic CON11Cpro, EMTAC A2424i */
	PCMCIA_DEVICE_MANF_CARD(0xd601, 0x0002), /* Safeway 802.11b, ZCOMAX AirRunner/XI-300 */
	PCMCIA_DEVICE_MANF_CARD(0xd601, 0x0005), /* D-Link DCF660, Sandisk Connect SDWCFB-000 */
	PCMCIA_DEVICE_PROD_ID123("Instant Wireless ", " Network PC CARD", "Version 01.02", 0x11d901af, 0x6e9bd926, 0x4b74baa0),
	PCMCIA_DEVICE_PROD_ID12("ACTIONTEC", "PRISM Wireless LAN PC Card", 0x393089da, 0xa71e69d5),
	PCMCIA_DEVICE_PROD_ID12("Addtron", "AWP-100 Wireless PCMCIA", 0xe6ec52ce, 0x08649af2),
	PCMCIA_DEVICE_PROD_ID12("BUFFALO", "WLI-CF-S11G", 0x2decece3, 0x82067c18),
	PCMCIA_DEVICE_PROD_ID12("BUFFALO", "WLI-PCM-L11G", 0x2decece3, 0xf57ca4b3),
	PCMCIA_DEVICE_PROD_ID12("Compaq", "WL200_11Mbps_Wireless_PCI_Card", 0x54f7c49c, 0x15a75e5b),
	PCMCIA_DEVICE_PROD_ID12("corega K.K.", "Wireless LAN PCC-11", 0x5261440f, 0xa6405584),
	PCMCIA_DEVICE_PROD_ID12("corega K.K.", "Wireless LAN PCCA-11", 0x5261440f, 0xdf6115f9),
	PCMCIA_DEVICE_PROD_ID12("corega_K.K.", "Wireless_LAN_PCCB-11", 0x29e33311, 0xee7a27ae),
	PCMCIA_DEVICE_PROD_ID12("Digital Data Communications", "WPC-0100", 0xfdd73470, 0xe0b6f146),
	PCMCIA_DEVICE_PROD_ID12("D", "Link DRC-650 11Mbps WLAN Card", 0x71b18589, 0xf144e3ac),
	PCMCIA_DEVICE_PROD_ID12("D", "Link DWL-650 11Mbps WLAN Card", 0x71b18589, 0xb6f1b0ab),
	PCMCIA_DEVICE_PROD_ID12(" ", "IEEE 802.11 Wireless LAN/PC Card", 0x3b6e20c8, 0xefccafe9),
	PCMCIA_DEVICE_PROD_ID12("INTERSIL", "HFA384x/IEEE", 0x74c5e40d, 0xdb472a18),
	PCMCIA_DEVICE_PROD_ID12("INTERSIL", "I-GATE 11M PC Card / PC Card plus", 0x74c5e40d, 0x8304ff77),
	PCMCIA_DEVICE_PROD_ID12("Intersil", "PRISM 2_5 PCMCIA ADAPTER", 0x4b801a17, 0x6345a0bf),
	PCMCIA_DEVICE_PROD_ID12("Linksys", "Wireless CompactFlash Card", 0x0733cc81, 0x0c52f395),
	PCMCIA_DEVICE_PROD_ID12("Microsoft", "Wireless Notebook Adapter MN-520", 0x5961bf85, 0x6eec8c01),
	PCMCIA_DEVICE_PROD_ID12("NETGEAR MA401RA Wireless PC", "Card", 0x0306467f, 0x9762e8f1),
	PCMCIA_DEVICE_PROD_ID12("NETGEAR MA401 Wireless PC", "Card", 0xa37434e9, 0x9762e8f1),
	PCMCIA_DEVICE_PROD_ID12("OEM", "PRISM2 IEEE 802.11 PC-Card", 0xfea54c90, 0x48f2bdd6),
	PCMCIA_DEVICE_PROD_ID12("PLANEX", "GeoWave/GW-CF110", 0x209f40ab, 0xd9715264),
	PCMCIA_DEVICE_PROD_ID12("PLANEX", "GeoWave/GW-NS110", 0x209f40ab, 0x46263178),
	PCMCIA_DEVICE_PROD_ID12("SMC", "SMC2532W-B EliteConnect Wireless Adapter", 0xc4f8b18b, 0x196bd757),
	PCMCIA_DEVICE_PROD_ID12("SMC", "SMC2632W", 0xc4f8b18b, 0x474a1f2a),
	PCMCIA_DEVICE_PROD_ID12("ZoomAir 11Mbps High", "Rate wireless Networking", 0x273fe3db, 0x32a1eaee),
	PCMCIA_DEVICE_PROD_ID3("HFA3863", 0x355cb092),
	PCMCIA_DEVICE_PROD_ID3("ISL37100P", 0x630d52b2),
	PCMCIA_DEVICE_PROD_ID3("ISL37101P-10", 0xdd97a26b),
	PCMCIA_DEVICE_PROD_ID3("ISL37300P", 0xc9049a39),

	/* This may be Agere or Intersil Firmware */
	PCMCIA_DEVICE_MANF_CARD(0x0156, 0x0002),
#पूर्ण_अगर
	PCMCIA_DEVICE_शून्य,
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, orinoco_cs_ids);

अटल काष्ठा pcmcia_driver orinoco_driver = अणु
	.owner		= THIS_MODULE,
	.name		= DRIVER_NAME,
	.probe		= orinoco_cs_probe,
	.हटाओ		= orinoco_cs_detach,
	.id_table       = orinoco_cs_ids,
	.suspend	= orinoco_cs_suspend,
	.resume		= orinoco_cs_resume,
पूर्ण;
module_pcmcia_driver(orinoco_driver);
