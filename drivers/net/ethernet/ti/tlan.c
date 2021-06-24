<शैली गुरु>
/*******************************************************************************
 *
 *  Linux ThunderLAN Driver
 *
 *  tlan.c
 *  by James Banks
 *
 *  (C) 1997-1998 Caldera, Inc.
 *  (C) 1998 James Banks
 *  (C) 1999-2001 Torben Mathiasen
 *  (C) 2002 Samuel Chessman
 *
 *  This software may be used and distributed according to the terms
 *  of the GNU General Public License, incorporated herein by reference.
 *
 ** Useful (अगर not required) पढ़ोing:
 *
 *		Texas Instruments, ThunderLAN Programmer's Guide,
 *			TI Literature Number SPWU013A
 *			available in PDF क्रमmat from www.ti.com
 *		Level One, LXT901 and LXT970 Data Sheets
 *			available in PDF क्रमmat from www.level1.com
 *		National Semiconductor, DP83840A Data Sheet
 *			available in PDF क्रमmat from www.national.com
 *		Microchip Technology, 24C01A/02A/04A Data Sheet
 *			available in PDF क्रमmat from www.microchip.com
 *
 ******************************************************************************/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/hardirq.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/eisa.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mii.h>

#समावेश "tlan.h"


/* For removing EISA devices */
अटल	काष्ठा net_device	*tlan_eisa_devices;

अटल	पूर्णांक		tlan_devices_installed;

/* Set speed, duplex and aui settings */
अटल  पूर्णांक aui[MAX_TLAN_BOARDS];
अटल  पूर्णांक duplex[MAX_TLAN_BOARDS];
अटल  पूर्णांक speed[MAX_TLAN_BOARDS];
अटल  पूर्णांक boards_found;
module_param_array(aui, पूर्णांक, शून्य, 0);
module_param_array(duplex, पूर्णांक, शून्य, 0);
module_param_array(speed, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(aui, "ThunderLAN use AUI port(s) (0-1)");
MODULE_PARM_DESC(duplex,
		 "ThunderLAN duplex setting(s) (0-default, 1-half, 2-full)");
MODULE_PARM_DESC(speed, "ThunderLAN port speed setting(s) (0,10,100)");

MODULE_AUTHOR("Maintainer: Samuel Chessman <chessman@tux.org>");
MODULE_DESCRIPTION("Driver for TI ThunderLAN based ethernet PCI adapters");
MODULE_LICENSE("GPL");

/* Turn on debugging.
 * See Documentation/networking/device_drivers/ethernet/ti/tlan.rst क्रम details
 */
अटल  पूर्णांक		debug;
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "ThunderLAN debug mask");

अटल	स्थिर अक्षर tlan_signature[] = "TLAN";
अटल  स्थिर अक्षर tlan_banner[] = "ThunderLAN driver v1.17\n";
अटल  पूर्णांक tlan_have_pci;
अटल  पूर्णांक tlan_have_eisa;

अटल स्थिर अक्षर * स्थिर media[] = अणु
	"10BaseT-HD", "10BaseT-FD", "100baseTx-HD",
	"100BaseTx-FD", "100BaseT4", शून्य
पूर्ण;

अटल काष्ठा board अणु
	स्थिर अक्षर	*device_label;
	u32		flags;
	u16		addr_ofs;
पूर्ण board_info[] = अणु
	अणु "Compaq Netelligent 10 T PCI UTP", TLAN_ADAPTER_ACTIVITY_LED, 0x83 पूर्ण,
	अणु "Compaq Netelligent 10/100 TX PCI UTP",
	  TLAN_ADAPTER_ACTIVITY_LED, 0x83 पूर्ण,
	अणु "Compaq Integrated NetFlex-3/P", TLAN_ADAPTER_NONE, 0x83 पूर्ण,
	अणु "Compaq NetFlex-3/P",
	  TLAN_ADAPTER_UNMANAGED_PHY | TLAN_ADAPTER_BIT_RATE_PHY, 0x83 पूर्ण,
	अणु "Compaq NetFlex-3/P", TLAN_ADAPTER_NONE, 0x83 पूर्ण,
	अणु "Compaq Netelligent Integrated 10/100 TX UTP",
	  TLAN_ADAPTER_ACTIVITY_LED, 0x83 पूर्ण,
	अणु "Compaq Netelligent Dual 10/100 TX PCI UTP",
	  TLAN_ADAPTER_NONE, 0x83 पूर्ण,
	अणु "Compaq Netelligent 10/100 TX Embedded UTP",
	  TLAN_ADAPTER_NONE, 0x83 पूर्ण,
	अणु "Olicom OC-2183/2185", TLAN_ADAPTER_USE_INTERN_10, 0x83 पूर्ण,
	अणु "Olicom OC-2325", TLAN_ADAPTER_ACTIVITY_LED |
	  TLAN_ADAPTER_UNMANAGED_PHY, 0xf8 पूर्ण,
	अणु "Olicom OC-2326", TLAN_ADAPTER_ACTIVITY_LED |
	  TLAN_ADAPTER_USE_INTERN_10, 0xf8 पूर्ण,
	अणु "Compaq Netelligent 10/100 TX UTP", TLAN_ADAPTER_ACTIVITY_LED, 0x83 पूर्ण,
	अणु "Compaq Netelligent 10 T/2 PCI UTP/coax", TLAN_ADAPTER_NONE, 0x83 पूर्ण,
	अणु "Compaq NetFlex-3/E",
	  TLAN_ADAPTER_ACTIVITY_LED |	/* EISA card */
	  TLAN_ADAPTER_UNMANAGED_PHY | TLAN_ADAPTER_BIT_RATE_PHY, 0x83 पूर्ण,
	अणु "Compaq NetFlex-3/E",
	  TLAN_ADAPTER_ACTIVITY_LED, 0x83 पूर्ण, /* EISA card */
पूर्ण;

अटल स्थिर काष्ठा pci_device_id tlan_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_COMPAQ, PCI_DEVICE_ID_COMPAQ_NETEL10,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 पूर्ण,
	अणु PCI_VENDOR_ID_COMPAQ, PCI_DEVICE_ID_COMPAQ_NETEL100,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 1 पूर्ण,
	अणु PCI_VENDOR_ID_COMPAQ, PCI_DEVICE_ID_COMPAQ_NETFLEX3I,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 2 पूर्ण,
	अणु PCI_VENDOR_ID_COMPAQ, PCI_DEVICE_ID_COMPAQ_THUNDER,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 3 पूर्ण,
	अणु PCI_VENDOR_ID_COMPAQ, PCI_DEVICE_ID_COMPAQ_NETFLEX3B,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 4 पूर्ण,
	अणु PCI_VENDOR_ID_COMPAQ, PCI_DEVICE_ID_COMPAQ_NETEL100PI,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 5 पूर्ण,
	अणु PCI_VENDOR_ID_COMPAQ, PCI_DEVICE_ID_COMPAQ_NETEL100D,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 6 पूर्ण,
	अणु PCI_VENDOR_ID_COMPAQ, PCI_DEVICE_ID_COMPAQ_NETEL100I,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 7 पूर्ण,
	अणु PCI_VENDOR_ID_OLICOM, PCI_DEVICE_ID_OLICOM_OC2183,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 8 पूर्ण,
	अणु PCI_VENDOR_ID_OLICOM, PCI_DEVICE_ID_OLICOM_OC2325,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 9 पूर्ण,
	अणु PCI_VENDOR_ID_OLICOM, PCI_DEVICE_ID_OLICOM_OC2326,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 10 पूर्ण,
	अणु PCI_VENDOR_ID_COMPAQ, PCI_DEVICE_ID_NETELLIGENT_10_100_WS_5100,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 11 पूर्ण,
	अणु PCI_VENDOR_ID_COMPAQ, PCI_DEVICE_ID_NETELLIGENT_10_T2,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 12 पूर्ण,
	अणु 0,पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, tlan_pci_tbl);

अटल व्योम	tlan_eisa_probe(व्योम);
अटल व्योम	tlan_eisa_cleanup(व्योम);
अटल पूर्णांक      tlan_init(काष्ठा net_device *);
अटल पूर्णांक	tlan_खोलो(काष्ठा net_device *dev);
अटल netdev_tx_t tlan_start_tx(काष्ठा sk_buff *, काष्ठा net_device *);
अटल irqवापस_t tlan_handle_पूर्णांकerrupt(पूर्णांक, व्योम *);
अटल पूर्णांक	tlan_बंद(काष्ठा net_device *);
अटल काष्ठा	net_device_stats *tlan_get_stats(काष्ठा net_device *);
अटल व्योम	tlan_set_multicast_list(काष्ठा net_device *);
अटल पूर्णांक	tlan_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);
अटल पूर्णांक      tlan_probe1(काष्ठा pci_dev *pdev, दीर्घ ioaddr,
			    पूर्णांक irq, पूर्णांक rev, स्थिर काष्ठा pci_device_id *ent);
अटल व्योम	tlan_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue);
अटल व्योम	tlan_tx_समयout_work(काष्ठा work_काष्ठा *work);
अटल पूर्णांक	tlan_init_one(काष्ठा pci_dev *pdev,
			      स्थिर काष्ठा pci_device_id *ent);

अटल u32	tlan_handle_tx_eof(काष्ठा net_device *, u16);
अटल u32	tlan_handle_stat_overflow(काष्ठा net_device *, u16);
अटल u32	tlan_handle_rx_eof(काष्ठा net_device *, u16);
अटल u32	tlan_handle_dummy(काष्ठा net_device *, u16);
अटल u32	tlan_handle_tx_eoc(काष्ठा net_device *, u16);
अटल u32	tlan_handle_status_check(काष्ठा net_device *, u16);
अटल u32	tlan_handle_rx_eoc(काष्ठा net_device *, u16);

अटल व्योम	tlan_समयr(काष्ठा समयr_list *t);
अटल व्योम	tlan_phy_monitor(काष्ठा समयr_list *t);

अटल व्योम	tlan_reset_lists(काष्ठा net_device *);
अटल व्योम	tlan_मुक्त_lists(काष्ठा net_device *);
अटल व्योम	tlan_prपूर्णांक_dio(u16);
अटल व्योम	tlan_prपूर्णांक_list(काष्ठा tlan_list *, अक्षर *, पूर्णांक);
अटल व्योम	tlan_पढ़ो_and_clear_stats(काष्ठा net_device *, पूर्णांक);
अटल व्योम	tlan_reset_adapter(काष्ठा net_device *);
अटल व्योम	tlan_finish_reset(काष्ठा net_device *);
अटल व्योम	tlan_set_mac(काष्ठा net_device *, पूर्णांक areg, अक्षर *mac);

अटल व्योम	__tlan_phy_prपूर्णांक(काष्ठा net_device *);
अटल व्योम	tlan_phy_prपूर्णांक(काष्ठा net_device *);
अटल व्योम	tlan_phy_detect(काष्ठा net_device *);
अटल व्योम	tlan_phy_घातer_करोwn(काष्ठा net_device *);
अटल व्योम	tlan_phy_घातer_up(काष्ठा net_device *);
अटल व्योम	tlan_phy_reset(काष्ठा net_device *);
अटल व्योम	tlan_phy_start_link(काष्ठा net_device *);
अटल व्योम	tlan_phy_finish_स्वतः_neg(काष्ठा net_device *);

/*
  अटल पूर्णांक	tlan_phy_nop(काष्ठा net_device *);
  अटल पूर्णांक	tlan_phy_पूर्णांकernal_check(काष्ठा net_device *);
  अटल पूर्णांक	tlan_phy_पूर्णांकernal_service(काष्ठा net_device *);
  अटल पूर्णांक	tlan_phy_dp83840a_check(काष्ठा net_device *);
*/

अटल bool	__tlan_mii_पढ़ो_reg(काष्ठा net_device *, u16, u16, u16 *);
अटल व्योम	tlan_mii_पढ़ो_reg(काष्ठा net_device *, u16, u16, u16 *);
अटल व्योम	tlan_mii_send_data(u16, u32, अचिन्हित);
अटल व्योम	tlan_mii_sync(u16);
अटल व्योम	__tlan_mii_ग_लिखो_reg(काष्ठा net_device *, u16, u16, u16);
अटल व्योम	tlan_mii_ग_लिखो_reg(काष्ठा net_device *, u16, u16, u16);

अटल व्योम	tlan_ee_send_start(u16);
अटल पूर्णांक	tlan_ee_send_byte(u16, u8, पूर्णांक);
अटल व्योम	tlan_ee_receive_byte(u16, u8 *, पूर्णांक);
अटल पूर्णांक	tlan_ee_पढ़ो_byte(काष्ठा net_device *, u8, u8 *);


अटल अंतरभूत व्योम
tlan_store_skb(काष्ठा tlan_list *tag, काष्ठा sk_buff *skb)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)skb;
	tag->buffer[9].address = addr;
	tag->buffer[8].address = upper_32_bits(addr);
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *
tlan_get_skb(स्थिर काष्ठा tlan_list *tag)
अणु
	अचिन्हित दीर्घ addr;

	addr = tag->buffer[9].address;
	addr |= ((अचिन्हित दीर्घ) tag->buffer[8].address << 16) << 16;
	वापस (काष्ठा sk_buff *) addr;
पूर्ण

अटल u32
(*tlan_पूर्णांक_vector[TLAN_INT_NUMBER_OF_INTS])(काष्ठा net_device *, u16) = अणु
	शून्य,
	tlan_handle_tx_eof,
	tlan_handle_stat_overflow,
	tlan_handle_rx_eof,
	tlan_handle_dummy,
	tlan_handle_tx_eoc,
	tlan_handle_status_check,
	tlan_handle_rx_eoc
पूर्ण;

अटल व्योम
tlan_set_समयr(काष्ठा net_device *dev, u32 ticks, u32 type)
अणु
	काष्ठा tlan_priv *priv = netdev_priv(dev);
	अचिन्हित दीर्घ flags = 0;

	spin_lock_irqsave(&priv->lock, flags);
	अगर (priv->समयr.function != शून्य &&
	    priv->समयr_type != TLAN_TIMER_ACTIVITY) अणु
		spin_unlock_irqrestore(&priv->lock, flags);
		वापस;
	पूर्ण
	priv->समयr.function = tlan_समयr;
	spin_unlock_irqrestore(&priv->lock, flags);

	priv->समयr_set_at = jअगरfies;
	priv->समयr_type = type;
	mod_समयr(&priv->समयr, jअगरfies + ticks);

पूर्ण


/*****************************************************************************
******************************************************************************

ThunderLAN driver primary functions

these functions are more or less common to all linux network drivers.

******************************************************************************
*****************************************************************************/





/***************************************************************
 *	tlan_हटाओ_one
 *
 *	Returns:
 *		Nothing
 *	Parms:
 *		None
 *
 *	Goes through the TLanDevices list and मुक्तs the device
 *	काष्ठाs and memory associated with each device (lists
 *	and buffers).  It also ureserves the IO port regions
 *	associated with this device.
 *
 **************************************************************/


अटल व्योम tlan_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा tlan_priv	*priv = netdev_priv(dev);

	unरेजिस्टर_netdev(dev);

	अगर (priv->dma_storage) अणु
		dma_मुक्त_coherent(&priv->pci_dev->dev, priv->dma_size,
				  priv->dma_storage, priv->dma_storage_dma);
	पूर्ण

#अगर_घोषित CONFIG_PCI
	pci_release_regions(pdev);
#पूर्ण_अगर

	मुक्त_netdev(dev);

	cancel_work_sync(&priv->tlan_tqueue);
पूर्ण

अटल व्योम tlan_start(काष्ठा net_device *dev)
अणु
	tlan_reset_lists(dev);
	/* NOTE: It might not be necessary to पढ़ो the stats beक्रमe a
	   reset अगर you करोn't care what the values are.
	*/
	tlan_पढ़ो_and_clear_stats(dev, TLAN_IGNORE);
	tlan_reset_adapter(dev);
	netअगर_wake_queue(dev);
पूर्ण

अटल व्योम tlan_stop(काष्ठा net_device *dev)
अणु
	काष्ठा tlan_priv *priv = netdev_priv(dev);

	del_समयr_sync(&priv->media_समयr);
	tlan_पढ़ो_and_clear_stats(dev, TLAN_RECORD);
	outl(TLAN_HC_AD_RST, dev->base_addr + TLAN_HOST_CMD);
	/* Reset and घातer करोwn phy */
	tlan_reset_adapter(dev);
	अगर (priv->समयr.function != शून्य) अणु
		del_समयr_sync(&priv->समयr);
		priv->समयr.function = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक __maybe_unused tlan_suspend(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);

	अगर (netअगर_running(dev))
		tlan_stop(dev);

	netअगर_device_detach(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused tlan_resume(काष्ठा device *dev_d)
अणु
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);
	netअगर_device_attach(dev);

	अगर (netअगर_running(dev))
		tlan_start(dev);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(tlan_pm_ops, tlan_suspend, tlan_resume);

अटल काष्ठा pci_driver tlan_driver = अणु
	.name		= "tlan",
	.id_table	= tlan_pci_tbl,
	.probe		= tlan_init_one,
	.हटाओ		= tlan_हटाओ_one,
	.driver.pm	= &tlan_pm_ops,
पूर्ण;

अटल पूर्णांक __init tlan_probe(व्योम)
अणु
	पूर्णांक rc = -ENODEV;

	pr_info("%s", tlan_banner);

	TLAN_DBG(TLAN_DEBUG_PROBE, "Starting PCI Probe....\n");

	/* Use new style PCI probing. Now the kernel will
	   करो most of this क्रम us */
	rc = pci_रेजिस्टर_driver(&tlan_driver);

	अगर (rc != 0) अणु
		pr_err("Could not register pci driver\n");
		जाओ err_out_pci_मुक्त;
	पूर्ण

	TLAN_DBG(TLAN_DEBUG_PROBE, "Starting EISA Probe....\n");
	tlan_eisa_probe();

	pr_info("%d device%s installed, PCI: %d  EISA: %d\n",
		tlan_devices_installed, tlan_devices_installed == 1 ? "" : "s",
		tlan_have_pci, tlan_have_eisa);

	अगर (tlan_devices_installed == 0) अणु
		rc = -ENODEV;
		जाओ  err_out_pci_unreg;
	पूर्ण
	वापस 0;

err_out_pci_unreg:
	pci_unरेजिस्टर_driver(&tlan_driver);
err_out_pci_मुक्त:
	वापस rc;
पूर्ण


अटल पूर्णांक tlan_init_one(काष्ठा pci_dev *pdev,
				   स्थिर काष्ठा pci_device_id *ent)
अणु
	वापस tlan_probe1(pdev, -1, -1, 0, ent);
पूर्ण


/*
***************************************************************
*	tlan_probe1
*
*	Returns:
*		0 on success, error code on error
*	Parms:
*		none
*
*	The name is lower हाल to fit in with all the rest of
*	the netcard_probe names.  This function looks क्रम
*	another TLan based adapter, setting it up with the
*	allocated device काष्ठा अगर one is found.
*	tlan_probe has been ported to the new net API and
*	now allocates its own device काष्ठाure. This function
*	is also used by modules.
*
**************************************************************/

अटल पूर्णांक tlan_probe1(काष्ठा pci_dev *pdev, दीर्घ ioaddr, पूर्णांक irq, पूर्णांक rev,
		       स्थिर काष्ठा pci_device_id *ent)
अणु

	काष्ठा net_device  *dev;
	काष्ठा tlan_priv  *priv;
	u16		   device_id;
	पूर्णांक		   reg, rc = -ENODEV;

#अगर_घोषित CONFIG_PCI
	अगर (pdev) अणु
		rc = pci_enable_device(pdev);
		अगर (rc)
			वापस rc;

		rc = pci_request_regions(pdev, tlan_signature);
		अगर (rc) अणु
			pr_err("Could not reserve IO regions\n");
			जाओ err_out;
		पूर्ण
	पूर्ण
#पूर्ण_अगर  /*  CONFIG_PCI  */

	dev = alloc_etherdev(माप(काष्ठा tlan_priv));
	अगर (dev == शून्य) अणु
		rc = -ENOMEM;
		जाओ err_out_regions;
	पूर्ण
	SET_NETDEV_DEV(dev, &pdev->dev);

	priv = netdev_priv(dev);

	priv->pci_dev = pdev;
	priv->dev = dev;

	/* Is this a PCI device? */
	अगर (pdev) अणु
		u32		   pci_io_base = 0;

		priv->adapter = &board_info[ent->driver_data];

		rc = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
		अगर (rc) अणु
			pr_err("No suitable PCI mapping available\n");
			जाओ err_out_मुक्त_dev;
		पूर्ण

		क्रम (reg = 0; reg <= 5; reg++) अणु
			अगर (pci_resource_flags(pdev, reg) & IORESOURCE_IO) अणु
				pci_io_base = pci_resource_start(pdev, reg);
				TLAN_DBG(TLAN_DEBUG_GNRL,
					 "IO mapping is available at %x.\n",
					 pci_io_base);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!pci_io_base) अणु
			pr_err("No IO mappings available\n");
			rc = -EIO;
			जाओ err_out_मुक्त_dev;
		पूर्ण

		dev->base_addr = pci_io_base;
		dev->irq = pdev->irq;
		priv->adapter_rev = pdev->revision;
		pci_set_master(pdev);
		pci_set_drvdata(pdev, dev);

	पूर्ण अन्यथा	अणु     /* EISA card */
		/* This is a hack. We need to know which board काष्ठाure
		 * is suited क्रम this adapter */
		device_id = inw(ioaddr + EISA_ID2);
		अगर (device_id == 0x20F1) अणु
			priv->adapter = &board_info[13]; /* NetFlex-3/E */
			priv->adapter_rev = 23;		/* TLAN 2.3 */
		पूर्ण अन्यथा अणु
			priv->adapter = &board_info[14];
			priv->adapter_rev = 10;		/* TLAN 1.0 */
		पूर्ण
		dev->base_addr = ioaddr;
		dev->irq = irq;
	पूर्ण

	/* Kernel parameters */
	अगर (dev->mem_start) अणु
		priv->aui    = dev->mem_start & 0x01;
		priv->duplex = ((dev->mem_start & 0x06) == 0x06) ? 0
			: (dev->mem_start & 0x06) >> 1;
		priv->speed  = ((dev->mem_start & 0x18) == 0x18) ? 0
			: (dev->mem_start & 0x18) >> 3;

		अगर (priv->speed == 0x1)
			priv->speed = TLAN_SPEED_10;
		अन्यथा अगर (priv->speed == 0x2)
			priv->speed = TLAN_SPEED_100;

		debug = priv->debug = dev->mem_end;
	पूर्ण अन्यथा अणु
		priv->aui    = aui[boards_found];
		priv->speed  = speed[boards_found];
		priv->duplex = duplex[boards_found];
		priv->debug = debug;
	पूर्ण

	/* This will be used when we get an adapter error from
	 * within our irq handler */
	INIT_WORK(&priv->tlan_tqueue, tlan_tx_समयout_work);

	spin_lock_init(&priv->lock);

	rc = tlan_init(dev);
	अगर (rc) अणु
		pr_err("Could not set up device\n");
		जाओ err_out_मुक्त_dev;
	पूर्ण

	rc = रेजिस्टर_netdev(dev);
	अगर (rc) अणु
		pr_err("Could not register device\n");
		जाओ err_out_uninit;
	पूर्ण


	tlan_devices_installed++;
	boards_found++;

	/* pdev is शून्य अगर this is an EISA device */
	अगर (pdev)
		tlan_have_pci++;
	अन्यथा अणु
		priv->next_device = tlan_eisa_devices;
		tlan_eisa_devices = dev;
		tlan_have_eisa++;
	पूर्ण

	netdev_info(dev, "irq=%2d, io=%04x, %s, Rev. %d\n",
		    (पूर्णांक)dev->irq,
		    (पूर्णांक)dev->base_addr,
		    priv->adapter->device_label,
		    priv->adapter_rev);
	वापस 0;

err_out_uninit:
	dma_मुक्त_coherent(&priv->pci_dev->dev, priv->dma_size,
			  priv->dma_storage, priv->dma_storage_dma);
err_out_मुक्त_dev:
	मुक्त_netdev(dev);
err_out_regions:
#अगर_घोषित CONFIG_PCI
	अगर (pdev)
		pci_release_regions(pdev);
err_out:
#पूर्ण_अगर
	अगर (pdev)
		pci_disable_device(pdev);
	वापस rc;
पूर्ण


अटल व्योम tlan_eisa_cleanup(व्योम)
अणु
	काष्ठा net_device *dev;
	काष्ठा tlan_priv *priv;

	जबतक (tlan_have_eisa) अणु
		dev = tlan_eisa_devices;
		priv = netdev_priv(dev);
		अगर (priv->dma_storage) अणु
			dma_मुक्त_coherent(&priv->pci_dev->dev, priv->dma_size,
					  priv->dma_storage,
					  priv->dma_storage_dma);
		पूर्ण
		release_region(dev->base_addr, 0x10);
		unरेजिस्टर_netdev(dev);
		tlan_eisa_devices = priv->next_device;
		मुक्त_netdev(dev);
		tlan_have_eisa--;
	पूर्ण
पूर्ण


अटल व्योम __निकास tlan_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&tlan_driver);

	अगर (tlan_have_eisa)
		tlan_eisa_cleanup();

पूर्ण


/* Module loading/unloading */
module_init(tlan_probe);
module_निकास(tlan_निकास);



/**************************************************************
 *	tlan_eisa_probe
 *
 *	Returns: 0 on success, 1 otherwise
 *
 *	Parms:	 None
 *
 *
 *	This functions probes क्रम EISA devices and calls
 *	TLan_probe1 when one is found.
 *
 *************************************************************/

अटल व्योम  __init tlan_eisa_probe(व्योम)
अणु
	दीर्घ	ioaddr;
	पूर्णांक	irq;
	u16	device_id;

	अगर (!EISA_bus) अणु
		TLAN_DBG(TLAN_DEBUG_PROBE, "No EISA bus present\n");
		वापस;
	पूर्ण

	/* Loop through all slots of the EISA bus */
	क्रम (ioaddr = 0x1000; ioaddr < 0x9000; ioaddr += 0x1000) अणु

		TLAN_DBG(TLAN_DEBUG_PROBE, "EISA_ID 0x%4x: 0x%4x\n",
			 (पूर्णांक) ioaddr + 0xc80, inw(ioaddr + EISA_ID));
		TLAN_DBG(TLAN_DEBUG_PROBE, "EISA_ID 0x%4x: 0x%4x\n",
			 (पूर्णांक) ioaddr + 0xc82, inw(ioaddr + EISA_ID2));


		TLAN_DBG(TLAN_DEBUG_PROBE,
			 "Probing for EISA adapter at IO: 0x%4x : ",
			 (पूर्णांक) ioaddr);
		अगर (request_region(ioaddr, 0x10, tlan_signature) == शून्य)
			जाओ out;

		अगर (inw(ioaddr + EISA_ID) != 0x110E) अणु
			release_region(ioaddr, 0x10);
			जाओ out;
		पूर्ण

		device_id = inw(ioaddr + EISA_ID2);
		अगर (device_id !=  0x20F1 && device_id != 0x40F1) अणु
			release_region(ioaddr, 0x10);
			जाओ out;
		पूर्ण

		/* check अगर adapter is enabled */
		अगर (inb(ioaddr + EISA_CR) != 0x1) अणु
			release_region(ioaddr, 0x10);
			जाओ out2;
		पूर्ण

		अगर (debug == 0x10)
			pr_info("Found one\n");


		/* Get irq from board */
		चयन (inb(ioaddr + 0xcc0)) अणु
		हाल(0x10):
			irq = 5;
			अवरोध;
		हाल(0x20):
			irq = 9;
			अवरोध;
		हाल(0x40):
			irq = 10;
			अवरोध;
		हाल(0x80):
			irq = 11;
			अवरोध;
		शेष:
			जाओ out;
		पूर्ण


		/* Setup the newly found eisa adapter */
		tlan_probe1(शून्य, ioaddr, irq, 12, शून्य);
		जारी;

out:
		अगर (debug == 0x10)
			pr_info("None found\n");
		जारी;

out2:
		अगर (debug == 0x10)
			pr_info("Card found but it is not enabled, skipping\n");
		जारी;

	पूर्ण

पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम tlan_poll(काष्ठा net_device *dev)
अणु
	disable_irq(dev->irq);
	tlan_handle_पूर्णांकerrupt(dev->irq, dev);
	enable_irq(dev->irq);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा net_device_ops tlan_netdev_ops = अणु
	.nकरो_खोलो		= tlan_खोलो,
	.nकरो_stop		= tlan_बंद,
	.nकरो_start_xmit		= tlan_start_tx,
	.nकरो_tx_समयout		= tlan_tx_समयout,
	.nकरो_get_stats		= tlan_get_stats,
	.nकरो_set_rx_mode	= tlan_set_multicast_list,
	.nकरो_करो_ioctl		= tlan_ioctl,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	 = tlan_poll,
#पूर्ण_अगर
पूर्ण;

अटल व्योम tlan_get_drvinfo(काष्ठा net_device *dev,
			     काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा tlan_priv *priv = netdev_priv(dev);

	strlcpy(info->driver, KBUILD_MODNAME, माप(info->driver));
	अगर (priv->pci_dev)
		strlcpy(info->bus_info, pci_name(priv->pci_dev),
			माप(info->bus_info));
	अन्यथा
		strlcpy(info->bus_info, "EISA",	माप(info->bus_info));
पूर्ण

अटल पूर्णांक tlan_get_eeprom_len(काष्ठा net_device *dev)
अणु
	वापस TLAN_EEPROM_SIZE;
पूर्ण

अटल पूर्णांक tlan_get_eeprom(काष्ठा net_device *dev,
			   काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < TLAN_EEPROM_SIZE; i++)
		अगर (tlan_ee_पढ़ो_byte(dev, i, &data[i]))
			वापस -EIO;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops tlan_ethtool_ops = अणु
	.get_drvinfo	= tlan_get_drvinfo,
	.get_link	= ethtool_op_get_link,
	.get_eeprom_len	= tlan_get_eeprom_len,
	.get_eeprom	= tlan_get_eeprom,
पूर्ण;

/***************************************************************
 *	tlan_init
 *
 *	Returns:
 *		0 on success, error code otherwise.
 *	Parms:
 *		dev	The काष्ठाure of the device to be
 *			init'ed.
 *
 *	This function completes the initialization of the
 *	device काष्ठाure and driver.  It reserves the IO
 *	addresses, allocates memory क्रम the lists and bounce
 *	buffers, retrieves the MAC address from the eeprom
 *	and assignes the device's methods.
 *
 **************************************************************/

अटल पूर्णांक tlan_init(काष्ठा net_device *dev)
अणु
	पूर्णांक		dma_size;
	पूर्णांक		err;
	पूर्णांक		i;
	काष्ठा tlan_priv	*priv;

	priv = netdev_priv(dev);

	dma_size = (TLAN_NUM_RX_LISTS + TLAN_NUM_TX_LISTS)
		* (माप(काष्ठा tlan_list));
	priv->dma_storage = dma_alloc_coherent(&priv->pci_dev->dev, dma_size,
					       &priv->dma_storage_dma, GFP_KERNEL);
	priv->dma_size = dma_size;

	अगर (priv->dma_storage == शून्य) अणु
		pr_err("Could not allocate lists and buffers for %s\n",
		       dev->name);
		वापस -ENOMEM;
	पूर्ण
	priv->rx_list = (काष्ठा tlan_list *)
		ALIGN((अचिन्हित दीर्घ)priv->dma_storage, 8);
	priv->rx_list_dma = ALIGN(priv->dma_storage_dma, 8);
	priv->tx_list = priv->rx_list + TLAN_NUM_RX_LISTS;
	priv->tx_list_dma =
		priv->rx_list_dma + माप(काष्ठा tlan_list)*TLAN_NUM_RX_LISTS;

	err = 0;
	क्रम (i = 0; i < ETH_ALEN; i++)
		err |= tlan_ee_पढ़ो_byte(dev,
					 (u8) priv->adapter->addr_ofs + i,
					 (u8 *) &dev->dev_addr[i]);
	अगर (err) अणु
		pr_err("%s: Error reading MAC from eeprom: %d\n",
		       dev->name, err);
	पूर्ण
	/* Olicom OC-2325/OC-2326 have the address byte-swapped */
	अगर (priv->adapter->addr_ofs == 0xf8) अणु
		क्रम (i = 0; i < ETH_ALEN; i += 2) अणु
			अक्षर पंचांगp = dev->dev_addr[i];
			dev->dev_addr[i] = dev->dev_addr[i + 1];
			dev->dev_addr[i + 1] = पंचांगp;
		पूर्ण
	पूर्ण

	netअगर_carrier_off(dev);

	/* Device methods */
	dev->netdev_ops = &tlan_netdev_ops;
	dev->ethtool_ops = &tlan_ethtool_ops;
	dev->watchकरोg_समयo = TX_TIMEOUT;

	वापस 0;

पूर्ण




/***************************************************************
 *	tlan_खोलो
 *
 *	Returns:
 *		0 on success, error code otherwise.
 *	Parms:
 *		dev	Structure of device to be खोलोed.
 *
 *	This routine माला_दो the driver and TLAN adapter in a
 *	state where it is पढ़ोy to send and receive packets.
 *	It allocates the IRQ, resets and brings the adapter
 *	out of reset, and allows पूर्णांकerrupts.  It also delays
 *	the startup क्रम स्वतःnegotiation or sends a Rx GO
 *	command to the adapter, as appropriate.
 *
 **************************************************************/

अटल पूर्णांक tlan_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा tlan_priv	*priv = netdev_priv(dev);
	पूर्णांक		err;

	priv->tlan_rev = tlan_dio_पढ़ो8(dev->base_addr, TLAN_DEF_REVISION);
	err = request_irq(dev->irq, tlan_handle_पूर्णांकerrupt, IRQF_SHARED,
			  dev->name, dev);

	अगर (err) अणु
		netdev_err(dev, "Cannot open because IRQ %d is already in use\n",
			   dev->irq);
		वापस err;
	पूर्ण

	समयr_setup(&priv->समयr, शून्य, 0);
	समयr_setup(&priv->media_समयr, tlan_phy_monitor, 0);

	tlan_start(dev);

	TLAN_DBG(TLAN_DEBUG_GNRL, "%s: Opened.  TLAN Chip Rev: %x\n",
		 dev->name, priv->tlan_rev);

	वापस 0;

पूर्ण



/**************************************************************
 *	tlan_ioctl
 *
 *	Returns:
 *		0 on success, error code otherwise
 *	Params:
 *		dev	काष्ठाure of device to receive ioctl.
 *
 *		rq	अगरreq काष्ठाure to hold userspace data.
 *
 *		cmd	ioctl command.
 *
 *
 *************************************************************/

अटल पूर्णांक tlan_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा tlan_priv *priv = netdev_priv(dev);
	काष्ठा mii_ioctl_data *data = अगर_mii(rq);
	u32 phy   = priv->phy[priv->phy_num];

	अगर (!priv->phy_online)
		वापस -EAGAIN;

	चयन (cmd) अणु
	हाल SIOCGMIIPHY:		/* get address of MII PHY in use. */
		data->phy_id = phy;
		fallthrough;


	हाल SIOCGMIIREG:		/* पढ़ो MII PHY रेजिस्टर. */
		tlan_mii_पढ़ो_reg(dev, data->phy_id & 0x1f,
				  data->reg_num & 0x1f, &data->val_out);
		वापस 0;


	हाल SIOCSMIIREG:		/* ग_लिखो MII PHY रेजिस्टर. */
		tlan_mii_ग_लिखो_reg(dev, data->phy_id & 0x1f,
				   data->reg_num & 0x1f, data->val_in);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण


/***************************************************************
 *	tlan_tx_समयout
 *
 *	Returns: nothing
 *
 *	Params:
 *		dev	काष्ठाure of device which समयd out
 *			during transmit.
 *
 **************************************************************/

अटल व्योम tlan_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु

	TLAN_DBG(TLAN_DEBUG_GNRL, "%s: Transmit timed out.\n", dev->name);

	/* Ok so we समयd out, lets see what we can करो about it...*/
	tlan_मुक्त_lists(dev);
	tlan_reset_lists(dev);
	tlan_पढ़ो_and_clear_stats(dev, TLAN_IGNORE);
	tlan_reset_adapter(dev);
	netअगर_trans_update(dev); /* prevent tx समयout */
	netअगर_wake_queue(dev);

पूर्ण


/***************************************************************
 *	tlan_tx_समयout_work
 *
 *	Returns: nothing
 *
 *	Params:
 *		work	work item of device which समयd out
 *
 **************************************************************/

अटल व्योम tlan_tx_समयout_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tlan_priv	*priv =
		container_of(work, काष्ठा tlan_priv, tlan_tqueue);

	tlan_tx_समयout(priv->dev, अच_पूर्णांक_उच्च);
पूर्ण



/***************************************************************
 *	tlan_start_tx
 *
 *	Returns:
 *		0 on success, non-zero on failure.
 *	Parms:
 *		skb	A poपूर्णांकer to the sk_buff containing the
 *			frame to be sent.
 *		dev	The device to send the data on.
 *
 *	This function adds a frame to the Tx list to be sent
 *	ASAP.  First it	verअगरies that the adapter is पढ़ोy and
 *	there is room in the queue.  Then it sets up the next
 *	available list, copies the frame to the	corresponding
 *	buffer.  If the adapter Tx channel is idle, it gives
 *	the adapter a Tx Go command on the list, otherwise it
 *	sets the क्रमward address of the previous list to poपूर्णांक
 *	to this one.  Then it मुक्तs the sk_buff.
 *
 **************************************************************/

अटल netdev_tx_t tlan_start_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा tlan_priv *priv = netdev_priv(dev);
	dma_addr_t	tail_list_phys;
	काष्ठा tlan_list	*tail_list;
	अचिन्हित दीर्घ	flags;
	अचिन्हित पूर्णांक    txlen;

	अगर (!priv->phy_online) अणु
		TLAN_DBG(TLAN_DEBUG_TX, "TRANSMIT:  %s PHY is not ready\n",
			 dev->name);
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	अगर (skb_padto(skb, TLAN_MIN_FRAME_SIZE))
		वापस NETDEV_TX_OK;
	txlen = max(skb->len, (अचिन्हित पूर्णांक)TLAN_MIN_FRAME_SIZE);

	tail_list = priv->tx_list + priv->tx_tail;
	tail_list_phys =
		priv->tx_list_dma + माप(काष्ठा tlan_list)*priv->tx_tail;

	अगर (tail_list->c_stat != TLAN_CSTAT_UNUSED) अणु
		TLAN_DBG(TLAN_DEBUG_TX,
			 "TRANSMIT:  %s is busy (Head=%d Tail=%d)\n",
			 dev->name, priv->tx_head, priv->tx_tail);
		netअगर_stop_queue(dev);
		priv->tx_busy_count++;
		वापस NETDEV_TX_BUSY;
	पूर्ण

	tail_list->क्रमward = 0;

	tail_list->buffer[0].address = dma_map_single(&priv->pci_dev->dev,
						      skb->data, txlen,
						      DMA_TO_DEVICE);
	tlan_store_skb(tail_list, skb);

	tail_list->frame_size = (u16) txlen;
	tail_list->buffer[0].count = TLAN_LAST_BUFFER | (u32) txlen;
	tail_list->buffer[1].count = 0;
	tail_list->buffer[1].address = 0;

	spin_lock_irqsave(&priv->lock, flags);
	tail_list->c_stat = TLAN_CSTAT_READY;
	अगर (!priv->tx_in_progress) अणु
		priv->tx_in_progress = 1;
		TLAN_DBG(TLAN_DEBUG_TX,
			 "TRANSMIT:  Starting TX on buffer %d\n",
			 priv->tx_tail);
		outl(tail_list_phys, dev->base_addr + TLAN_CH_PARM);
		outl(TLAN_HC_GO, dev->base_addr + TLAN_HOST_CMD);
	पूर्ण अन्यथा अणु
		TLAN_DBG(TLAN_DEBUG_TX,
			 "TRANSMIT:  Adding buffer %d to TX channel\n",
			 priv->tx_tail);
		अगर (priv->tx_tail == 0) अणु
			(priv->tx_list + (TLAN_NUM_TX_LISTS - 1))->क्रमward
				= tail_list_phys;
		पूर्ण अन्यथा अणु
			(priv->tx_list + (priv->tx_tail - 1))->क्रमward
				= tail_list_phys;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&priv->lock, flags);

	CIRC_INC(priv->tx_tail, TLAN_NUM_TX_LISTS);

	वापस NETDEV_TX_OK;

पूर्ण




/***************************************************************
 *	tlan_handle_पूर्णांकerrupt
 *
 *	Returns:
 *		Nothing
 *	Parms:
 *		irq	The line on which the पूर्णांकerrupt
 *			occurred.
 *		dev_id	A poपूर्णांकer to the device asचिन्हित to
 *			this irq line.
 *
 *	This function handles an पूर्णांकerrupt generated by its
 *	asचिन्हित TLAN adapter.  The function deactivates
 *	पूर्णांकerrupts on its adapter, records the type of
 *	पूर्णांकerrupt, executes the appropriate subhandler, and
 *	acknowdges the पूर्णांकerrupt to the adapter (thus
 *	re-enabling adapter पूर्णांकerrupts.
 *
 **************************************************************/

अटल irqवापस_t tlan_handle_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device	*dev = dev_id;
	काष्ठा tlan_priv *priv = netdev_priv(dev);
	u16		host_पूर्णांक;
	u16		type;

	spin_lock(&priv->lock);

	host_पूर्णांक = inw(dev->base_addr + TLAN_HOST_INT);
	type = (host_पूर्णांक & TLAN_HI_IT_MASK) >> 2;
	अगर (type) अणु
		u32	ack;
		u32	host_cmd;

		outw(host_पूर्णांक, dev->base_addr + TLAN_HOST_INT);
		ack = tlan_पूर्णांक_vector[type](dev, host_पूर्णांक);

		अगर (ack) अणु
			host_cmd = TLAN_HC_ACK | ack | (type << 18);
			outl(host_cmd, dev->base_addr + TLAN_HOST_CMD);
		पूर्ण
	पूर्ण

	spin_unlock(&priv->lock);

	वापस IRQ_RETVAL(type);
पूर्ण




/***************************************************************
 *	tlan_बंद
 *
 *	Returns:
 *		An error code.
 *	Parms:
 *		dev	The device काष्ठाure of the device to
 *			बंद.
 *
 *	This function shuts करोwn the adapter.  It records any
 *	stats, माला_दो the adapter पूर्णांकo reset state, deactivates
 *	its समय as needed, and	मुक्तs the irq it is using.
 *
 **************************************************************/

अटल पूर्णांक tlan_बंद(काष्ठा net_device *dev)
अणु
	tlan_stop(dev);

	मुक्त_irq(dev->irq, dev);
	tlan_मुक्त_lists(dev);
	TLAN_DBG(TLAN_DEBUG_GNRL, "Device %s closed.\n", dev->name);

	वापस 0;

पूर्ण




/***************************************************************
 *	tlan_get_stats
 *
 *	Returns:
 *		A poपूर्णांकer to the device's statistics काष्ठाure.
 *	Parms:
 *		dev	The device काष्ठाure to वापस the
 *			stats क्रम.
 *
 *	This function updates the devices statistics by पढ़ोing
 *	the TLAN chip's onboard रेजिस्टरs.  Then it वापसs the
 *	address of the statistics काष्ठाure.
 *
 **************************************************************/

अटल काष्ठा net_device_stats *tlan_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा tlan_priv	*priv = netdev_priv(dev);
	पूर्णांक i;

	/* Should only पढ़ो stats अगर खोलो ? */
	tlan_पढ़ो_and_clear_stats(dev, TLAN_RECORD);

	TLAN_DBG(TLAN_DEBUG_RX, "RECEIVE:  %s EOC count = %d\n", dev->name,
		 priv->rx_eoc_count);
	TLAN_DBG(TLAN_DEBUG_TX, "TRANSMIT:  %s Busy count = %d\n", dev->name,
		 priv->tx_busy_count);
	अगर (debug & TLAN_DEBUG_GNRL) अणु
		tlan_prपूर्णांक_dio(dev->base_addr);
		tlan_phy_prपूर्णांक(dev);
	पूर्ण
	अगर (debug & TLAN_DEBUG_LIST) अणु
		क्रम (i = 0; i < TLAN_NUM_RX_LISTS; i++)
			tlan_prपूर्णांक_list(priv->rx_list + i, "RX", i);
		क्रम (i = 0; i < TLAN_NUM_TX_LISTS; i++)
			tlan_prपूर्णांक_list(priv->tx_list + i, "TX", i);
	पूर्ण

	वापस &dev->stats;

पूर्ण




/***************************************************************
 *	tlan_set_multicast_list
 *
 *	Returns:
 *		Nothing
 *	Parms:
 *		dev	The device काष्ठाure to set the
 *			multicast list क्रम.
 *
 *	This function sets the TLAN adaptor to various receive
 *	modes.  If the IFF_PROMISC flag is set, promiscuous
 *	mode is acitviated.  Otherwise,	promiscuous mode is
 *	turned off.  If the IFF_ALLMULTI flag is set, then
 *	the hash table is set to receive all group addresses.
 *	Otherwise, the first three multicast addresses are
 *	stored in AREG_1-3, and the rest are selected via the
 *	hash table, as necessary.
 *
 **************************************************************/

अटल व्योम tlan_set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_hw_addr *ha;
	u32			hash1 = 0;
	u32			hash2 = 0;
	पूर्णांक			i;
	u32			offset;
	u8			पंचांगp;

	अगर (dev->flags & IFF_PROMISC) अणु
		पंचांगp = tlan_dio_पढ़ो8(dev->base_addr, TLAN_NET_CMD);
		tlan_dio_ग_लिखो8(dev->base_addr,
				TLAN_NET_CMD, पंचांगp | TLAN_NET_CMD_CAF);
	पूर्ण अन्यथा अणु
		पंचांगp = tlan_dio_पढ़ो8(dev->base_addr, TLAN_NET_CMD);
		tlan_dio_ग_लिखो8(dev->base_addr,
				TLAN_NET_CMD, पंचांगp & ~TLAN_NET_CMD_CAF);
		अगर (dev->flags & IFF_ALLMULTI) अणु
			क्रम (i = 0; i < 3; i++)
				tlan_set_mac(dev, i + 1, शून्य);
			tlan_dio_ग_लिखो32(dev->base_addr, TLAN_HASH_1,
					 0xffffffff);
			tlan_dio_ग_लिखो32(dev->base_addr, TLAN_HASH_2,
					 0xffffffff);
		पूर्ण अन्यथा अणु
			i = 0;
			netdev_क्रम_each_mc_addr(ha, dev) अणु
				अगर (i < 3) अणु
					tlan_set_mac(dev, i + 1,
						     (अक्षर *) &ha->addr);
				पूर्ण अन्यथा अणु
					offset =
						tlan_hash_func((u8 *)&ha->addr);
					अगर (offset < 32)
						hash1 |= (1 << offset);
					अन्यथा
						hash2 |= (1 << (offset - 32));
				पूर्ण
				i++;
			पूर्ण
			क्रम ( ; i < 3; i++)
				tlan_set_mac(dev, i + 1, शून्य);
			tlan_dio_ग_लिखो32(dev->base_addr, TLAN_HASH_1, hash1);
			tlan_dio_ग_लिखो32(dev->base_addr, TLAN_HASH_2, hash2);
		पूर्ण
	पूर्ण

पूर्ण



/*****************************************************************************
******************************************************************************

ThunderLAN driver पूर्णांकerrupt vectors and table

please see chap. 4, "Interrupt Handling" of the "ThunderLAN
Programmer's Guide" क्रम more inक्रमmations on handling पूर्णांकerrupts
generated by TLAN based adapters.

******************************************************************************
*****************************************************************************/




/***************************************************************
 *	tlan_handle_tx_eof
 *
 *	Returns:
 *		1
 *	Parms:
 *		dev		Device asचिन्हित the IRQ that was
 *				उठाओd.
 *		host_पूर्णांक	The contents of the HOST_INT
 *				port.
 *
 *	This function handles Tx खातापूर्ण पूर्णांकerrupts which are उठाओd
 *	by the adapter when it has completed sending the
 *	contents of a buffer.  If detemines which list/buffer
 *	was completed and resets it.  If the buffer was the last
 *	in the channel (EOC), then the function checks to see अगर
 *	another buffer is पढ़ोy to send, and अगर so, sends a Tx
 *	Go command.  Finally, the driver activates/जारीs the
 *	activity LED.
 *
 **************************************************************/

अटल u32 tlan_handle_tx_eof(काष्ठा net_device *dev, u16 host_पूर्णांक)
अणु
	काष्ठा tlan_priv	*priv = netdev_priv(dev);
	पूर्णांक		eoc = 0;
	काष्ठा tlan_list	*head_list;
	dma_addr_t	head_list_phys;
	u32		ack = 0;
	u16		पंचांगp_c_stat;

	TLAN_DBG(TLAN_DEBUG_TX,
		 "TRANSMIT:  Handling TX EOF (Head=%d Tail=%d)\n",
		 priv->tx_head, priv->tx_tail);
	head_list = priv->tx_list + priv->tx_head;

	जबतक (((पंचांगp_c_stat = head_list->c_stat) & TLAN_CSTAT_FRM_CMP)
	       && (ack < 255)) अणु
		काष्ठा sk_buff *skb = tlan_get_skb(head_list);

		ack++;
		dma_unmap_single(&priv->pci_dev->dev,
				 head_list->buffer[0].address,
				 max(skb->len, (अचिन्हित पूर्णांक)TLAN_MIN_FRAME_SIZE),
				 DMA_TO_DEVICE);
		dev_kमुक्त_skb_any(skb);
		head_list->buffer[8].address = 0;
		head_list->buffer[9].address = 0;

		अगर (पंचांगp_c_stat & TLAN_CSTAT_EOC)
			eoc = 1;

		dev->stats.tx_bytes += head_list->frame_size;

		head_list->c_stat = TLAN_CSTAT_UNUSED;
		netअगर_start_queue(dev);
		CIRC_INC(priv->tx_head, TLAN_NUM_TX_LISTS);
		head_list = priv->tx_list + priv->tx_head;
	पूर्ण

	अगर (!ack)
		netdev_info(dev,
			    "Received interrupt for uncompleted TX frame\n");

	अगर (eoc) अणु
		TLAN_DBG(TLAN_DEBUG_TX,
			 "TRANSMIT:  handling TX EOC (Head=%d Tail=%d)\n",
			 priv->tx_head, priv->tx_tail);
		head_list = priv->tx_list + priv->tx_head;
		head_list_phys = priv->tx_list_dma
			+ माप(काष्ठा tlan_list)*priv->tx_head;
		अगर ((head_list->c_stat & TLAN_CSTAT_READY)
		    == TLAN_CSTAT_READY) अणु
			outl(head_list_phys, dev->base_addr + TLAN_CH_PARM);
			ack |= TLAN_HC_GO;
		पूर्ण अन्यथा अणु
			priv->tx_in_progress = 0;
		पूर्ण
	पूर्ण

	अगर (priv->adapter->flags & TLAN_ADAPTER_ACTIVITY_LED) अणु
		tlan_dio_ग_लिखो8(dev->base_addr,
				TLAN_LED_REG, TLAN_LED_LINK | TLAN_LED_ACT);
		अगर (priv->समयr.function == शून्य) अणु
			priv->समयr.function = tlan_समयr;
			priv->समयr.expires = jअगरfies + TLAN_TIMER_ACT_DELAY;
			priv->समयr_set_at = jअगरfies;
			priv->समयr_type = TLAN_TIMER_ACTIVITY;
			add_समयr(&priv->समयr);
		पूर्ण अन्यथा अगर (priv->समयr_type == TLAN_TIMER_ACTIVITY) अणु
			priv->समयr_set_at = jअगरfies;
		पूर्ण
	पूर्ण

	वापस ack;

पूर्ण




/***************************************************************
 *	TLan_HandleStatOverflow
 *
 *	Returns:
 *		1
 *	Parms:
 *		dev		Device asचिन्हित the IRQ that was
 *				उठाओd.
 *		host_पूर्णांक	The contents of the HOST_INT
 *				port.
 *
 *	This function handles the Statistics Overflow पूर्णांकerrupt
 *	which means that one or more of the TLAN statistics
 *	रेजिस्टरs has reached 1/2 capacity and needs to be पढ़ो.
 *
 **************************************************************/

अटल u32 tlan_handle_stat_overflow(काष्ठा net_device *dev, u16 host_पूर्णांक)
अणु
	tlan_पढ़ो_and_clear_stats(dev, TLAN_RECORD);

	वापस 1;

पूर्ण




/***************************************************************
 *	TLan_HandleRxखातापूर्ण
 *
 *	Returns:
 *		1
 *	Parms:
 *		dev		Device asचिन्हित the IRQ that was
 *				उठाओd.
 *		host_पूर्णांक	The contents of the HOST_INT
 *				port.
 *
 *	This function handles the Rx खातापूर्ण पूर्णांकerrupt which
 *	indicates a frame has been received by the adapter from
 *	the net and the frame has been transferred to memory.
 *	The function determines the bounce buffer the frame has
 *	been loaded पूर्णांकo, creates a new sk_buff big enough to
 *	hold the frame, and sends it to protocol stack.  It
 *	then resets the used buffer and appends it to the end
 *	of the list.  If the frame was the last in the Rx
 *	channel (EOC), the function restarts the receive channel
 *	by sending an Rx Go command to the adapter.  Then it
 *	activates/जारीs the activity LED.
 *
 **************************************************************/

अटल u32 tlan_handle_rx_eof(काष्ठा net_device *dev, u16 host_पूर्णांक)
अणु
	काष्ठा tlan_priv	*priv = netdev_priv(dev);
	u32		ack = 0;
	पूर्णांक		eoc = 0;
	काष्ठा tlan_list	*head_list;
	काष्ठा sk_buff	*skb;
	काष्ठा tlan_list	*tail_list;
	u16		पंचांगp_c_stat;
	dma_addr_t	head_list_phys;

	TLAN_DBG(TLAN_DEBUG_RX, "RECEIVE:  handling RX EOF (Head=%d Tail=%d)\n",
		 priv->rx_head, priv->rx_tail);
	head_list = priv->rx_list + priv->rx_head;
	head_list_phys =
		priv->rx_list_dma + माप(काष्ठा tlan_list)*priv->rx_head;

	जबतक (((पंचांगp_c_stat = head_list->c_stat) & TLAN_CSTAT_FRM_CMP)
	       && (ack < 255)) अणु
		dma_addr_t frame_dma = head_list->buffer[0].address;
		u32 frame_size = head_list->frame_size;
		काष्ठा sk_buff *new_skb;

		ack++;
		अगर (पंचांगp_c_stat & TLAN_CSTAT_EOC)
			eoc = 1;

		new_skb = netdev_alloc_skb_ip_align(dev,
						    TLAN_MAX_FRAME_SIZE + 5);
		अगर (!new_skb)
			जाओ drop_and_reuse;

		skb = tlan_get_skb(head_list);
		dma_unmap_single(&priv->pci_dev->dev, frame_dma,
				 TLAN_MAX_FRAME_SIZE, DMA_FROM_DEVICE);
		skb_put(skb, frame_size);

		dev->stats.rx_bytes += frame_size;

		skb->protocol = eth_type_trans(skb, dev);
		netअगर_rx(skb);

		head_list->buffer[0].address =
			dma_map_single(&priv->pci_dev->dev, new_skb->data,
				       TLAN_MAX_FRAME_SIZE, DMA_FROM_DEVICE);

		tlan_store_skb(head_list, new_skb);
drop_and_reuse:
		head_list->क्रमward = 0;
		head_list->c_stat = 0;
		tail_list = priv->rx_list + priv->rx_tail;
		tail_list->क्रमward = head_list_phys;

		CIRC_INC(priv->rx_head, TLAN_NUM_RX_LISTS);
		CIRC_INC(priv->rx_tail, TLAN_NUM_RX_LISTS);
		head_list = priv->rx_list + priv->rx_head;
		head_list_phys = priv->rx_list_dma
			+ माप(काष्ठा tlan_list)*priv->rx_head;
	पूर्ण

	अगर (!ack)
		netdev_info(dev,
			    "Received interrupt for uncompleted RX frame\n");


	अगर (eoc) अणु
		TLAN_DBG(TLAN_DEBUG_RX,
			 "RECEIVE:  handling RX EOC (Head=%d Tail=%d)\n",
			 priv->rx_head, priv->rx_tail);
		head_list = priv->rx_list + priv->rx_head;
		head_list_phys = priv->rx_list_dma
			+ माप(काष्ठा tlan_list)*priv->rx_head;
		outl(head_list_phys, dev->base_addr + TLAN_CH_PARM);
		ack |= TLAN_HC_GO | TLAN_HC_RT;
		priv->rx_eoc_count++;
	पूर्ण

	अगर (priv->adapter->flags & TLAN_ADAPTER_ACTIVITY_LED) अणु
		tlan_dio_ग_लिखो8(dev->base_addr,
				TLAN_LED_REG, TLAN_LED_LINK | TLAN_LED_ACT);
		अगर (priv->समयr.function == शून्य)  अणु
			priv->समयr.function = tlan_समयr;
			priv->समयr.expires = jअगरfies + TLAN_TIMER_ACT_DELAY;
			priv->समयr_set_at = jअगरfies;
			priv->समयr_type = TLAN_TIMER_ACTIVITY;
			add_समयr(&priv->समयr);
		पूर्ण अन्यथा अगर (priv->समयr_type == TLAN_TIMER_ACTIVITY) अणु
			priv->समयr_set_at = jअगरfies;
		पूर्ण
	पूर्ण

	वापस ack;

पूर्ण




/***************************************************************
 *	tlan_handle_dummy
 *
 *	Returns:
 *		1
 *	Parms:
 *		dev		Device asचिन्हित the IRQ that was
 *				उठाओd.
 *		host_पूर्णांक	The contents of the HOST_INT
 *				port.
 *
 *	This function handles the Dummy पूर्णांकerrupt, which is
 *	उठाओd whenever a test पूर्णांकerrupt is generated by setting
 *	the Req_Int bit of HOST_CMD to 1.
 *
 **************************************************************/

अटल u32 tlan_handle_dummy(काष्ठा net_device *dev, u16 host_पूर्णांक)
अणु
	netdev_info(dev, "Test interrupt\n");
	वापस 1;

पूर्ण




/***************************************************************
 *	tlan_handle_tx_eoc
 *
 *	Returns:
 *		1
 *	Parms:
 *		dev		Device asचिन्हित the IRQ that was
 *				उठाओd.
 *		host_पूर्णांक	The contents of the HOST_INT
 *				port.
 *
 *	This driver is काष्ठाured to determine EOC occurrences by
 *	पढ़ोing the CSTAT member of the list काष्ठाure.  Tx EOC
 *	पूर्णांकerrupts are disabled via the DIO INTDIS रेजिस्टर.
 *	However, TLAN chips beक्रमe revision 3.0 didn't have this
 *	functionality, so process EOC events अगर this is the
 *	हाल.
 *
 **************************************************************/

अटल u32 tlan_handle_tx_eoc(काष्ठा net_device *dev, u16 host_पूर्णांक)
अणु
	काष्ठा tlan_priv	*priv = netdev_priv(dev);
	काष्ठा tlan_list		*head_list;
	dma_addr_t		head_list_phys;
	u32			ack = 1;

	अगर (priv->tlan_rev < 0x30) अणु
		TLAN_DBG(TLAN_DEBUG_TX,
			 "TRANSMIT:  handling TX EOC (Head=%d Tail=%d) -- IRQ\n",
			 priv->tx_head, priv->tx_tail);
		head_list = priv->tx_list + priv->tx_head;
		head_list_phys = priv->tx_list_dma
			+ माप(काष्ठा tlan_list)*priv->tx_head;
		अगर ((head_list->c_stat & TLAN_CSTAT_READY)
		    == TLAN_CSTAT_READY) अणु
			netअगर_stop_queue(dev);
			outl(head_list_phys, dev->base_addr + TLAN_CH_PARM);
			ack |= TLAN_HC_GO;
		पूर्ण अन्यथा अणु
			priv->tx_in_progress = 0;
		पूर्ण
	पूर्ण

	वापस ack;

पूर्ण




/***************************************************************
 *	tlan_handle_status_check
 *
 *	Returns:
 *		0 अगर Adapter check, 1 अगर Network Status check.
 *	Parms:
 *		dev		Device asचिन्हित the IRQ that was
 *				उठाओd.
 *		host_पूर्णांक	The contents of the HOST_INT
 *				port.
 *
 *	This function handles Adapter Check/Network Status
 *	पूर्णांकerrupts generated by the adapter.  It checks the
 *	vector in the HOST_INT रेजिस्टर to determine अगर it is
 *	an Adapter Check पूर्णांकerrupt.  If so, it resets the
 *	adapter.  Otherwise it clears the status रेजिस्टरs
 *	and services the PHY.
 *
 **************************************************************/

अटल u32 tlan_handle_status_check(काष्ठा net_device *dev, u16 host_पूर्णांक)
अणु
	काष्ठा tlan_priv	*priv = netdev_priv(dev);
	u32		ack;
	u32		error;
	u8		net_sts;
	u32		phy;
	u16		tlphy_ctl;
	u16		tlphy_sts;

	ack = 1;
	अगर (host_पूर्णांक & TLAN_HI_IV_MASK) अणु
		netअगर_stop_queue(dev);
		error = inl(dev->base_addr + TLAN_CH_PARM);
		netdev_info(dev, "Adaptor Error = 0x%x\n", error);
		tlan_पढ़ो_and_clear_stats(dev, TLAN_RECORD);
		outl(TLAN_HC_AD_RST, dev->base_addr + TLAN_HOST_CMD);

		schedule_work(&priv->tlan_tqueue);

		netअगर_wake_queue(dev);
		ack = 0;
	पूर्ण अन्यथा अणु
		TLAN_DBG(TLAN_DEBUG_GNRL, "%s: Status Check\n", dev->name);
		phy = priv->phy[priv->phy_num];

		net_sts = tlan_dio_पढ़ो8(dev->base_addr, TLAN_NET_STS);
		अगर (net_sts) अणु
			tlan_dio_ग_लिखो8(dev->base_addr, TLAN_NET_STS, net_sts);
			TLAN_DBG(TLAN_DEBUG_GNRL, "%s:    Net_Sts = %x\n",
				 dev->name, (अचिन्हित) net_sts);
		पूर्ण
		अगर ((net_sts & TLAN_NET_STS_MIRQ) &&  (priv->phy_num == 0)) अणु
			__tlan_mii_पढ़ो_reg(dev, phy, TLAN_TLPHY_STS, &tlphy_sts);
			__tlan_mii_पढ़ो_reg(dev, phy, TLAN_TLPHY_CTL, &tlphy_ctl);
			अगर (!(tlphy_sts & TLAN_TS_POLOK) &&
			    !(tlphy_ctl & TLAN_TC_SWAPOL)) अणु
				tlphy_ctl |= TLAN_TC_SWAPOL;
				__tlan_mii_ग_लिखो_reg(dev, phy, TLAN_TLPHY_CTL,
						     tlphy_ctl);
			पूर्ण अन्यथा अगर ((tlphy_sts & TLAN_TS_POLOK) &&
				   (tlphy_ctl & TLAN_TC_SWAPOL)) अणु
				tlphy_ctl &= ~TLAN_TC_SWAPOL;
				__tlan_mii_ग_लिखो_reg(dev, phy, TLAN_TLPHY_CTL,
						     tlphy_ctl);
			पूर्ण

			अगर (debug)
				__tlan_phy_prपूर्णांक(dev);
		पूर्ण
	पूर्ण

	वापस ack;

पूर्ण




/***************************************************************
 *	tlan_handle_rx_eoc
 *
 *	Returns:
 *		1
 *	Parms:
 *		dev		Device asचिन्हित the IRQ that was
 *				उठाओd.
 *		host_पूर्णांक	The contents of the HOST_INT
 *				port.
 *
 *	This driver is काष्ठाured to determine EOC occurrences by
 *	पढ़ोing the CSTAT member of the list काष्ठाure.  Rx EOC
 *	पूर्णांकerrupts are disabled via the DIO INTDIS रेजिस्टर.
 *	However, TLAN chips beक्रमe revision 3.0 didn't have this
 *	CSTAT member or a INTDIS रेजिस्टर, so अगर this chip is
 *	pre-3.0, process EOC पूर्णांकerrupts normally.
 *
 **************************************************************/

अटल u32 tlan_handle_rx_eoc(काष्ठा net_device *dev, u16 host_पूर्णांक)
अणु
	काष्ठा tlan_priv	*priv = netdev_priv(dev);
	dma_addr_t	head_list_phys;
	u32		ack = 1;

	अगर (priv->tlan_rev < 0x30) अणु
		TLAN_DBG(TLAN_DEBUG_RX,
			 "RECEIVE:  Handling RX EOC (head=%d tail=%d) -- IRQ\n",
			 priv->rx_head, priv->rx_tail);
		head_list_phys = priv->rx_list_dma
			+ माप(काष्ठा tlan_list)*priv->rx_head;
		outl(head_list_phys, dev->base_addr + TLAN_CH_PARM);
		ack |= TLAN_HC_GO | TLAN_HC_RT;
		priv->rx_eoc_count++;
	पूर्ण

	वापस ack;

पूर्ण




/*****************************************************************************
******************************************************************************

ThunderLAN driver समयr function

******************************************************************************
*****************************************************************************/


/***************************************************************
 *	tlan_समयr
 *
 *	Returns:
 *		Nothing
 *	Parms:
 *		data	A value given to add समयr when
 *			add_समयr was called.
 *
 *	This function handles समयd functionality क्रम the
 *	TLAN driver.  The two current समयr uses are क्रम
 *	delaying क्रम स्वतःnegotionation and driving the ACT LED.
 *	-	Autonegotiation requires being allowed about
 *		2 1/2 seconds beक्रमe attempting to transmit a
 *		packet.  It would be a very bad thing to hang
 *		the kernel this दीर्घ, so the driver करोesn't
 *		allow transmission 'til after this समय, क्रम
 *		certain PHYs.  It would be much nicer अगर all
 *		PHYs were पूर्णांकerrupt-capable like the पूर्णांकernal
 *		PHY.
 *	-	The ACT LED, which shows adapter activity, is
 *		driven by the driver, and so must be left on
 *		क्रम a लघु period to घातer up the LED so it
 *		can be seen.  This delay can be changed by
 *		changing the TLAN_TIMER_ACT_DELAY in tlan.h,
 *		अगर desired.  100 ms  produces a slightly
 *		sluggish response.
 *
 **************************************************************/

अटल व्योम tlan_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा tlan_priv	*priv = from_समयr(priv, t, समयr);
	काष्ठा net_device	*dev = priv->dev;
	u32		elapsed;
	अचिन्हित दीर्घ	flags = 0;

	priv->समयr.function = शून्य;

	चयन (priv->समयr_type) अणु
	हाल TLAN_TIMER_PHY_PDOWN:
		tlan_phy_घातer_करोwn(dev);
		अवरोध;
	हाल TLAN_TIMER_PHY_PUP:
		tlan_phy_घातer_up(dev);
		अवरोध;
	हाल TLAN_TIMER_PHY_RESET:
		tlan_phy_reset(dev);
		अवरोध;
	हाल TLAN_TIMER_PHY_START_LINK:
		tlan_phy_start_link(dev);
		अवरोध;
	हाल TLAN_TIMER_PHY_FINISH_AN:
		tlan_phy_finish_स्वतः_neg(dev);
		अवरोध;
	हाल TLAN_TIMER_FINISH_RESET:
		tlan_finish_reset(dev);
		अवरोध;
	हाल TLAN_TIMER_ACTIVITY:
		spin_lock_irqsave(&priv->lock, flags);
		अगर (priv->समयr.function == शून्य) अणु
			elapsed = jअगरfies - priv->समयr_set_at;
			अगर (elapsed >= TLAN_TIMER_ACT_DELAY) अणु
				tlan_dio_ग_लिखो8(dev->base_addr,
						TLAN_LED_REG, TLAN_LED_LINK);
			पूर्ण अन्यथा  अणु
				priv->समयr.expires = priv->समयr_set_at
					+ TLAN_TIMER_ACT_DELAY;
				spin_unlock_irqrestore(&priv->lock, flags);
				add_समयr(&priv->समयr);
				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&priv->lock, flags);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

पूर्ण


/*****************************************************************************
******************************************************************************

ThunderLAN driver adapter related routines

******************************************************************************
*****************************************************************************/


/***************************************************************
 *	tlan_reset_lists
 *
 *	Returns:
 *		Nothing
 *	Parms:
 *		dev	The device काष्ठाure with the list
 *			काष्ठाures to be reset.
 *
 *	This routine sets the variables associated with managing
 *	the TLAN lists to their initial values.
 *
 **************************************************************/

अटल व्योम tlan_reset_lists(काष्ठा net_device *dev)
अणु
	काष्ठा tlan_priv *priv = netdev_priv(dev);
	पूर्णांक		i;
	काष्ठा tlan_list	*list;
	dma_addr_t	list_phys;
	काष्ठा sk_buff	*skb;

	priv->tx_head = 0;
	priv->tx_tail = 0;
	क्रम (i = 0; i < TLAN_NUM_TX_LISTS; i++) अणु
		list = priv->tx_list + i;
		list->c_stat = TLAN_CSTAT_UNUSED;
		list->buffer[0].address = 0;
		list->buffer[2].count = 0;
		list->buffer[2].address = 0;
		list->buffer[8].address = 0;
		list->buffer[9].address = 0;
	पूर्ण

	priv->rx_head = 0;
	priv->rx_tail = TLAN_NUM_RX_LISTS - 1;
	क्रम (i = 0; i < TLAN_NUM_RX_LISTS; i++) अणु
		list = priv->rx_list + i;
		list_phys = priv->rx_list_dma + माप(काष्ठा tlan_list)*i;
		list->c_stat = TLAN_CSTAT_READY;
		list->frame_size = TLAN_MAX_FRAME_SIZE;
		list->buffer[0].count = TLAN_MAX_FRAME_SIZE | TLAN_LAST_BUFFER;
		skb = netdev_alloc_skb_ip_align(dev, TLAN_MAX_FRAME_SIZE + 5);
		अगर (!skb)
			अवरोध;

		list->buffer[0].address = dma_map_single(&priv->pci_dev->dev,
							 skb->data,
							 TLAN_MAX_FRAME_SIZE,
							 DMA_FROM_DEVICE);
		tlan_store_skb(list, skb);
		list->buffer[1].count = 0;
		list->buffer[1].address = 0;
		list->क्रमward = list_phys + माप(काष्ठा tlan_list);
	पूर्ण

	/* in हाल ran out of memory early, clear bits */
	जबतक (i < TLAN_NUM_RX_LISTS) अणु
		tlan_store_skb(priv->rx_list + i, शून्य);
		++i;
	पूर्ण
	list->क्रमward = 0;

पूर्ण


अटल व्योम tlan_मुक्त_lists(काष्ठा net_device *dev)
अणु
	काष्ठा tlan_priv *priv = netdev_priv(dev);
	पूर्णांक		i;
	काष्ठा tlan_list	*list;
	काष्ठा sk_buff	*skb;

	क्रम (i = 0; i < TLAN_NUM_TX_LISTS; i++) अणु
		list = priv->tx_list + i;
		skb = tlan_get_skb(list);
		अगर (skb) अणु
			dma_unmap_single(&priv->pci_dev->dev,
					 list->buffer[0].address,
					 max(skb->len, (अचिन्हित पूर्णांक)TLAN_MIN_FRAME_SIZE),
					 DMA_TO_DEVICE);
			dev_kमुक्त_skb_any(skb);
			list->buffer[8].address = 0;
			list->buffer[9].address = 0;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < TLAN_NUM_RX_LISTS; i++) अणु
		list = priv->rx_list + i;
		skb = tlan_get_skb(list);
		अगर (skb) अणु
			dma_unmap_single(&priv->pci_dev->dev,
					 list->buffer[0].address,
					 TLAN_MAX_FRAME_SIZE, DMA_FROM_DEVICE);
			dev_kमुक्त_skb_any(skb);
			list->buffer[8].address = 0;
			list->buffer[9].address = 0;
		पूर्ण
	पूर्ण
पूर्ण




/***************************************************************
 *	tlan_prपूर्णांक_dio
 *
 *	Returns:
 *		Nothing
 *	Parms:
 *		io_base		Base IO port of the device of
 *				which to prपूर्णांक DIO रेजिस्टरs.
 *
 *	This function prपूर्णांकs out all the पूर्णांकernal (DIO)
 *	रेजिस्टरs of a TLAN chip.
 *
 **************************************************************/

अटल व्योम tlan_prपूर्णांक_dio(u16 io_base)
अणु
	u32 data0, data1;
	पूर्णांक	i;

	pr_info("Contents of internal registers for io base 0x%04hx\n",
		io_base);
	pr_info("Off.  +0        +4\n");
	क्रम (i = 0; i < 0x4C; i += 8) अणु
		data0 = tlan_dio_पढ़ो32(io_base, i);
		data1 = tlan_dio_पढ़ो32(io_base, i + 0x4);
		pr_info("0x%02x  0x%08x 0x%08x\n", i, data0, data1);
	पूर्ण

पूर्ण




/***************************************************************
 *	TLan_Prपूर्णांकList
 *
 *	Returns:
 *		Nothing
 *	Parms:
 *		list	A poपूर्णांकer to the काष्ठा tlan_list काष्ठाure to
 *			be prपूर्णांकed.
 *		type	A string to designate type of list,
 *			"Rx" or "Tx".
 *		num	The index of the list.
 *
 *	This function prपूर्णांकs out the contents of the list
 *	poपूर्णांकed to by the list parameter.
 *
 **************************************************************/

अटल व्योम tlan_prपूर्णांक_list(काष्ठा tlan_list *list, अक्षर *type, पूर्णांक num)
अणु
	पूर्णांक i;

	pr_info("%s List %d at %p\n", type, num, list);
	pr_info("   Forward    = 0x%08x\n",  list->क्रमward);
	pr_info("   CSTAT      = 0x%04hx\n", list->c_stat);
	pr_info("   Frame Size = 0x%04hx\n", list->frame_size);
	/* क्रम (i = 0; i < 10; i++) अणु */
	क्रम (i = 0; i < 2; i++) अणु
		pr_info("   Buffer[%d].count, addr = 0x%08x, 0x%08x\n",
			i, list->buffer[i].count, list->buffer[i].address);
	पूर्ण

पूर्ण




/***************************************************************
 *	tlan_पढ़ो_and_clear_stats
 *
 *	Returns:
 *		Nothing
 *	Parms:
 *		dev	Poपूर्णांकer to device काष्ठाure of adapter
 *			to which to पढ़ो stats.
 *		record	Flag indicating whether to add
 *
 *	This functions पढ़ोs all the पूर्णांकernal status रेजिस्टरs
 *	of the TLAN chip, which clears them as a side effect.
 *	It then either adds the values to the device's status
 *	काष्ठा, or discards them, depending on whether record
 *	is TLAN_RECORD (!=0)  or TLAN_IGNORE (==0).
 *
 **************************************************************/

अटल व्योम tlan_पढ़ो_and_clear_stats(काष्ठा net_device *dev, पूर्णांक record)
अणु
	u32		tx_good, tx_under;
	u32		rx_good, rx_over;
	u32		def_tx, crc, code;
	u32		multi_col, single_col;
	u32		excess_col, late_col, loss;

	outw(TLAN_GOOD_TX_FRMS, dev->base_addr + TLAN_DIO_ADR);
	tx_good  = inb(dev->base_addr + TLAN_DIO_DATA);
	tx_good += inb(dev->base_addr + TLAN_DIO_DATA + 1) << 8;
	tx_good += inb(dev->base_addr + TLAN_DIO_DATA + 2) << 16;
	tx_under = inb(dev->base_addr + TLAN_DIO_DATA + 3);

	outw(TLAN_GOOD_RX_FRMS, dev->base_addr + TLAN_DIO_ADR);
	rx_good  = inb(dev->base_addr + TLAN_DIO_DATA);
	rx_good += inb(dev->base_addr + TLAN_DIO_DATA + 1) << 8;
	rx_good += inb(dev->base_addr + TLAN_DIO_DATA + 2) << 16;
	rx_over  = inb(dev->base_addr + TLAN_DIO_DATA + 3);

	outw(TLAN_DEFERRED_TX, dev->base_addr + TLAN_DIO_ADR);
	def_tx  = inb(dev->base_addr + TLAN_DIO_DATA);
	def_tx += inb(dev->base_addr + TLAN_DIO_DATA + 1) << 8;
	crc     = inb(dev->base_addr + TLAN_DIO_DATA + 2);
	code    = inb(dev->base_addr + TLAN_DIO_DATA + 3);

	outw(TLAN_MULTICOL_FRMS, dev->base_addr + TLAN_DIO_ADR);
	multi_col   = inb(dev->base_addr + TLAN_DIO_DATA);
	multi_col  += inb(dev->base_addr + TLAN_DIO_DATA + 1) << 8;
	single_col  = inb(dev->base_addr + TLAN_DIO_DATA + 2);
	single_col += inb(dev->base_addr + TLAN_DIO_DATA + 3) << 8;

	outw(TLAN_EXCESSCOL_FRMS, dev->base_addr + TLAN_DIO_ADR);
	excess_col = inb(dev->base_addr + TLAN_DIO_DATA);
	late_col   = inb(dev->base_addr + TLAN_DIO_DATA + 1);
	loss       = inb(dev->base_addr + TLAN_DIO_DATA + 2);

	अगर (record) अणु
		dev->stats.rx_packets += rx_good;
		dev->stats.rx_errors  += rx_over + crc + code;
		dev->stats.tx_packets += tx_good;
		dev->stats.tx_errors  += tx_under + loss;
		dev->stats.collisions += multi_col
			+ single_col + excess_col + late_col;

		dev->stats.rx_over_errors    += rx_over;
		dev->stats.rx_crc_errors     += crc;
		dev->stats.rx_frame_errors   += code;

		dev->stats.tx_पातed_errors += tx_under;
		dev->stats.tx_carrier_errors += loss;
	पूर्ण

पूर्ण




/***************************************************************
 *	TLan_Reset
 *
 *	Returns:
 *		0
 *	Parms:
 *		dev	Poपूर्णांकer to device काष्ठाure of adapter
 *			to be reset.
 *
 *	This function resets the adapter and it's physical
 *	device.  See Chap. 3, pp. 9-10 of the "ThunderLAN
 *	Programmer's Guide" क्रम details.  The routine tries to
 *	implement what is detailed there, though adjusपंचांगents
 *	have been made.
 *
 **************************************************************/

अटल व्योम
tlan_reset_adapter(काष्ठा net_device *dev)
अणु
	काष्ठा tlan_priv	*priv = netdev_priv(dev);
	पूर्णांक		i;
	u32		addr;
	u32		data;
	u8		data8;

	priv->tlan_full_duplex = false;
	priv->phy_online = 0;
	netअगर_carrier_off(dev);

/*  1.	Assert reset bit. */

	data = inl(dev->base_addr + TLAN_HOST_CMD);
	data |= TLAN_HC_AD_RST;
	outl(data, dev->base_addr + TLAN_HOST_CMD);

	udelay(1000);

/*  2.	Turn off पूर्णांकerrupts. (Probably isn't necessary) */

	data = inl(dev->base_addr + TLAN_HOST_CMD);
	data |= TLAN_HC_INT_OFF;
	outl(data, dev->base_addr + TLAN_HOST_CMD);

/*  3.	Clear AREGs and HASHs. */

	क्रम (i = TLAN_AREG_0; i <= TLAN_HASH_2; i += 4)
		tlan_dio_ग_लिखो32(dev->base_addr, (u16) i, 0);

/*  4.	Setup NetConfig रेजिस्टर. */

	data = TLAN_NET_CFG_1FRAG | TLAN_NET_CFG_1CHAN | TLAN_NET_CFG_PHY_EN;
	tlan_dio_ग_लिखो16(dev->base_addr, TLAN_NET_CONFIG, (u16) data);

/*  5.	Load Ld_Tmr and Ld_Thr in HOST_CMD. */

	outl(TLAN_HC_LD_TMR | 0x3f, dev->base_addr + TLAN_HOST_CMD);
	outl(TLAN_HC_LD_THR | 0x9, dev->base_addr + TLAN_HOST_CMD);

/*  6.	Unreset the MII by setting NMRST (in NetSio) to 1. */

	outw(TLAN_NET_SIO, dev->base_addr + TLAN_DIO_ADR);
	addr = dev->base_addr + TLAN_DIO_DATA + TLAN_NET_SIO;
	tlan_set_bit(TLAN_NET_SIO_NMRST, addr);

/*  7.	Setup the reमुख्यing रेजिस्टरs. */

	अगर (priv->tlan_rev >= 0x30) अणु
		data8 = TLAN_ID_TX_EOC | TLAN_ID_RX_EOC;
		tlan_dio_ग_लिखो8(dev->base_addr, TLAN_INT_DIS, data8);
	पूर्ण
	tlan_phy_detect(dev);
	data = TLAN_NET_CFG_1FRAG | TLAN_NET_CFG_1CHAN;

	अगर (priv->adapter->flags & TLAN_ADAPTER_BIT_RATE_PHY) अणु
		data |= TLAN_NET_CFG_BIT;
		अगर (priv->aui == 1) अणु
			tlan_dio_ग_लिखो8(dev->base_addr, TLAN_ACOMMIT, 0x0a);
		पूर्ण अन्यथा अगर (priv->duplex == TLAN_DUPLEX_FULL) अणु
			tlan_dio_ग_लिखो8(dev->base_addr, TLAN_ACOMMIT, 0x00);
			priv->tlan_full_duplex = true;
		पूर्ण अन्यथा अणु
			tlan_dio_ग_लिखो8(dev->base_addr, TLAN_ACOMMIT, 0x08);
		पूर्ण
	पूर्ण

	/* करोn't power down internal PHY if we're going to use it */
	अगर (priv->phy_num == 0 ||
	   (priv->adapter->flags & TLAN_ADAPTER_USE_INTERN_10))
		data |= TLAN_NET_CFG_PHY_EN;
	tlan_dio_ग_लिखो16(dev->base_addr, TLAN_NET_CONFIG, (u16) data);

	अगर (priv->adapter->flags & TLAN_ADAPTER_UNMANAGED_PHY)
		tlan_finish_reset(dev);
	अन्यथा
		tlan_phy_घातer_करोwn(dev);

पूर्ण




अटल व्योम
tlan_finish_reset(काष्ठा net_device *dev)
अणु
	काष्ठा tlan_priv	*priv = netdev_priv(dev);
	u8		data;
	u32		phy;
	u8		sio;
	u16		status;
	u16		partner;
	u16		tlphy_ctl;
	u16		tlphy_par;
	u16		tlphy_id1, tlphy_id2;
	पूर्णांक		i;

	phy = priv->phy[priv->phy_num];

	data = TLAN_NET_CMD_NRESET | TLAN_NET_CMD_NWRAP;
	अगर (priv->tlan_full_duplex)
		data |= TLAN_NET_CMD_DUPLEX;
	tlan_dio_ग_लिखो8(dev->base_addr, TLAN_NET_CMD, data);
	data = TLAN_NET_MASK_MASK4 | TLAN_NET_MASK_MASK5;
	अगर (priv->phy_num == 0)
		data |= TLAN_NET_MASK_MASK7;
	tlan_dio_ग_लिखो8(dev->base_addr, TLAN_NET_MASK, data);
	tlan_dio_ग_लिखो16(dev->base_addr, TLAN_MAX_RX, ((1536)+7)&~7);
	tlan_mii_पढ़ो_reg(dev, phy, MII_GEN_ID_HI, &tlphy_id1);
	tlan_mii_पढ़ो_reg(dev, phy, MII_GEN_ID_LO, &tlphy_id2);

	अगर ((priv->adapter->flags & TLAN_ADAPTER_UNMANAGED_PHY) ||
	    (priv->aui)) अणु
		status = MII_GS_LINK;
		netdev_info(dev, "Link forced\n");
	पूर्ण अन्यथा अणु
		tlan_mii_पढ़ो_reg(dev, phy, MII_GEN_STS, &status);
		udelay(1000);
		tlan_mii_पढ़ो_reg(dev, phy, MII_GEN_STS, &status);
		अगर (status & MII_GS_LINK) अणु
			/* We only support link info on Nat.Sem. PHY's */
			अगर ((tlphy_id1 == NAT_SEM_ID1) &&
			    (tlphy_id2 == NAT_SEM_ID2)) अणु
				tlan_mii_पढ़ो_reg(dev, phy, MII_AN_LPA,
					&partner);
				tlan_mii_पढ़ो_reg(dev, phy, TLAN_TLPHY_PAR,
					&tlphy_par);

				netdev_info(dev,
					"Link active, %s %uMbps %s-Duplex\n",
					!(tlphy_par & TLAN_PHY_AN_EN_STAT)
					? "forced" : "Autonegotiation enabled,",
					tlphy_par & TLAN_PHY_SPEED_100
					? 100 : 10,
					tlphy_par & TLAN_PHY_DUPLEX_FULL
					? "Full" : "Half");

				अगर (tlphy_par & TLAN_PHY_AN_EN_STAT) अणु
					netdev_info(dev, "Partner capability:");
					क्रम (i = 5; i < 10; i++)
						अगर (partner & (1 << i))
							pr_cont(" %s",
								media[i-5]);
					pr_cont("\n");
				पूर्ण
			पूर्ण अन्यथा
				netdev_info(dev, "Link active\n");
			/* Enabling link beat monitoring */
			priv->media_समयr.expires = jअगरfies + HZ;
			add_समयr(&priv->media_समयr);
		पूर्ण
	पूर्ण

	अगर (priv->phy_num == 0) अणु
		tlan_mii_पढ़ो_reg(dev, phy, TLAN_TLPHY_CTL, &tlphy_ctl);
		tlphy_ctl |= TLAN_TC_INTEN;
		tlan_mii_ग_लिखो_reg(dev, phy, TLAN_TLPHY_CTL, tlphy_ctl);
		sio = tlan_dio_पढ़ो8(dev->base_addr, TLAN_NET_SIO);
		sio |= TLAN_NET_SIO_MINTEN;
		tlan_dio_ग_लिखो8(dev->base_addr, TLAN_NET_SIO, sio);
	पूर्ण

	अगर (status & MII_GS_LINK) अणु
		tlan_set_mac(dev, 0, dev->dev_addr);
		priv->phy_online = 1;
		outb((TLAN_HC_INT_ON >> 8), dev->base_addr + TLAN_HOST_CMD + 1);
		अगर (debug >= 1 && debug != TLAN_DEBUG_PROBE)
			outb((TLAN_HC_REQ_INT >> 8),
			     dev->base_addr + TLAN_HOST_CMD + 1);
		outl(priv->rx_list_dma, dev->base_addr + TLAN_CH_PARM);
		outl(TLAN_HC_GO | TLAN_HC_RT, dev->base_addr + TLAN_HOST_CMD);
		tlan_dio_ग_लिखो8(dev->base_addr, TLAN_LED_REG, TLAN_LED_LINK);
		netअगर_carrier_on(dev);
	पूर्ण अन्यथा अणु
		netdev_info(dev, "Link inactive, will retry in 10 secs...\n");
		tlan_set_समयr(dev, (10*HZ), TLAN_TIMER_FINISH_RESET);
		वापस;
	पूर्ण
	tlan_set_multicast_list(dev);

पूर्ण




/***************************************************************
 *	tlan_set_mac
 *
 *	Returns:
 *		Nothing
 *	Parms:
 *		dev	Poपूर्णांकer to device काष्ठाure of adapter
 *			on which to change the AREG.
 *		areg	The AREG to set the address in (0 - 3).
 *		mac	A poपूर्णांकer to an array of अक्षरs.  Each
 *			element stores one byte of the address.
 *			IE, it isn't in ascii.
 *
 *	This function transfers a MAC address to one of the
 *	TLAN AREGs (address रेजिस्टरs).  The TLAN chip locks
 *	the रेजिस्टर on writing to offset 0 and unlocks the
 *	रेजिस्टर after writing to offset 5.  If शून्य is passed
 *	in mac, then the AREG is filled with 0's.
 *
 **************************************************************/

अटल व्योम tlan_set_mac(काष्ठा net_device *dev, पूर्णांक areg, अक्षर *mac)
अणु
	पूर्णांक i;

	areg *= 6;

	अगर (mac != शून्य) अणु
		क्रम (i = 0; i < 6; i++)
			tlan_dio_ग_लिखो8(dev->base_addr,
					TLAN_AREG_0 + areg + i, mac[i]);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < 6; i++)
			tlan_dio_ग_लिखो8(dev->base_addr,
					TLAN_AREG_0 + areg + i, 0);
	पूर्ण

पूर्ण




/*****************************************************************************
******************************************************************************

ThunderLAN driver PHY layer routines

******************************************************************************
*****************************************************************************/



/*********************************************************************
 *	__tlan_phy_prपूर्णांक
 *
 *	Returns:
 *		Nothing
 *	Parms:
 *		dev	A poपूर्णांकer to the device काष्ठाure of the
 *			TLAN device having the PHYs to be detailed.
 *
 *	This function prपूर्णांकs the रेजिस्टरs a PHY (aka transceiver).
 *
 ********************************************************************/

अटल व्योम __tlan_phy_prपूर्णांक(काष्ठा net_device *dev)
अणु
	काष्ठा tlan_priv *priv = netdev_priv(dev);
	u16 i, data0, data1, data2, data3, phy;

	lockdep_निश्चित_held(&priv->lock);

	phy = priv->phy[priv->phy_num];

	अगर (priv->adapter->flags & TLAN_ADAPTER_UNMANAGED_PHY) अणु
		netdev_info(dev, "Unmanaged PHY\n");
	पूर्ण अन्यथा अगर (phy <= TLAN_PHY_MAX_ADDR) अणु
		netdev_info(dev, "PHY 0x%02x\n", phy);
		pr_info("   Off.  +0     +1     +2     +3\n");
		क्रम (i = 0; i < 0x20; i += 4) अणु
			__tlan_mii_पढ़ो_reg(dev, phy, i, &data0);
			__tlan_mii_पढ़ो_reg(dev, phy, i + 1, &data1);
			__tlan_mii_पढ़ो_reg(dev, phy, i + 2, &data2);
			__tlan_mii_पढ़ो_reg(dev, phy, i + 3, &data3);
			pr_info("   0x%02x 0x%04hx 0x%04hx 0x%04hx 0x%04hx\n",
				i, data0, data1, data2, data3);
		पूर्ण
	पूर्ण अन्यथा अणु
		netdev_info(dev, "Invalid PHY\n");
	पूर्ण

पूर्ण

अटल व्योम tlan_phy_prपूर्णांक(काष्ठा net_device *dev)
अणु
	काष्ठा tlan_priv *priv = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);
	__tlan_phy_prपूर्णांक(dev);
	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण


/*********************************************************************
 *	tlan_phy_detect
 *
 *	Returns:
 *		Nothing
 *	Parms:
 *		dev	A poपूर्णांकer to the device काष्ठाure of the adapter
 *			क्रम which the PHY needs determined.
 *
 *	So far I've found that adapters which have बाह्यal PHYs
 *	may also use the पूर्णांकernal PHY क्रम part of the functionality.
 *	(eg, AUI/Thinnet).  This function finds out अगर this TLAN
 *	chip has an पूर्णांकernal PHY, and then finds the first बाह्यal
 *	PHY (starting from address 0) अगर it exists).
 *
 ********************************************************************/

अटल व्योम tlan_phy_detect(काष्ठा net_device *dev)
अणु
	काष्ठा tlan_priv *priv = netdev_priv(dev);
	u16		control;
	u16		hi;
	u16		lo;
	u32		phy;

	अगर (priv->adapter->flags & TLAN_ADAPTER_UNMANAGED_PHY) अणु
		priv->phy_num = 0xffff;
		वापस;
	पूर्ण

	tlan_mii_पढ़ो_reg(dev, TLAN_PHY_MAX_ADDR, MII_GEN_ID_HI, &hi);

	अगर (hi != 0xffff)
		priv->phy[0] = TLAN_PHY_MAX_ADDR;
	अन्यथा
		priv->phy[0] = TLAN_PHY_NONE;

	priv->phy[1] = TLAN_PHY_NONE;
	क्रम (phy = 0; phy <= TLAN_PHY_MAX_ADDR; phy++) अणु
		tlan_mii_पढ़ो_reg(dev, phy, MII_GEN_CTL, &control);
		tlan_mii_पढ़ो_reg(dev, phy, MII_GEN_ID_HI, &hi);
		tlan_mii_पढ़ो_reg(dev, phy, MII_GEN_ID_LO, &lo);
		अगर ((control != 0xffff) ||
		    (hi != 0xffff) || (lo != 0xffff)) अणु
			TLAN_DBG(TLAN_DEBUG_GNRL,
				 "PHY found at %02x %04x %04x %04x\n",
				 phy, control, hi, lo);
			अगर ((priv->phy[1] == TLAN_PHY_NONE) &&
			    (phy != TLAN_PHY_MAX_ADDR)) अणु
				priv->phy[1] = phy;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (priv->phy[1] != TLAN_PHY_NONE)
		priv->phy_num = 1;
	अन्यथा अगर (priv->phy[0] != TLAN_PHY_NONE)
		priv->phy_num = 0;
	अन्यथा
		netdev_info(dev, "Cannot initialize device, no PHY was found!\n");

पूर्ण




अटल व्योम tlan_phy_घातer_करोwn(काष्ठा net_device *dev)
अणु
	काष्ठा tlan_priv	*priv = netdev_priv(dev);
	u16		value;

	TLAN_DBG(TLAN_DEBUG_GNRL, "%s: Powering down PHY(s).\n", dev->name);
	value = MII_GC_PDOWN | MII_GC_LOOPBK | MII_GC_ISOLATE;
	tlan_mii_sync(dev->base_addr);
	tlan_mii_ग_लिखो_reg(dev, priv->phy[priv->phy_num], MII_GEN_CTL, value);
	अगर ((priv->phy_num == 0) && (priv->phy[1] != TLAN_PHY_NONE)) अणु
		/* अगर using पूर्णांकernal PHY, the बाह्यal PHY must be घातered on */
		अगर (priv->adapter->flags & TLAN_ADAPTER_USE_INTERN_10)
			value = MII_GC_ISOLATE; /* just isolate it from MII */
		tlan_mii_sync(dev->base_addr);
		tlan_mii_ग_लिखो_reg(dev, priv->phy[1], MII_GEN_CTL, value);
	पूर्ण

	/* Wait क्रम 50 ms and घातerup
	 * This is arbitrary.  It is पूर्णांकended to make sure the
	 * transceiver settles.
	 */
	tlan_set_समयr(dev, msecs_to_jअगरfies(50), TLAN_TIMER_PHY_PUP);

पूर्ण




अटल व्योम tlan_phy_घातer_up(काष्ठा net_device *dev)
अणु
	काष्ठा tlan_priv	*priv = netdev_priv(dev);
	u16		value;

	TLAN_DBG(TLAN_DEBUG_GNRL, "%s: Powering up PHY.\n", dev->name);
	tlan_mii_sync(dev->base_addr);
	value = MII_GC_LOOPBK;
	tlan_mii_ग_लिखो_reg(dev, priv->phy[priv->phy_num], MII_GEN_CTL, value);
	tlan_mii_sync(dev->base_addr);
	/* Wait क्रम 500 ms and reset the
	 * transceiver.  The TLAN करोcs say both 50 ms and
	 * 500 ms, so करो the दीर्घer, just in हाल.
	 */
	tlan_set_समयr(dev, msecs_to_jअगरfies(500), TLAN_TIMER_PHY_RESET);

पूर्ण




अटल व्योम tlan_phy_reset(काष्ठा net_device *dev)
अणु
	काष्ठा tlan_priv	*priv = netdev_priv(dev);
	u16		phy;
	u16		value;
	अचिन्हित दीर्घ समयout = jअगरfies + HZ;

	phy = priv->phy[priv->phy_num];

	TLAN_DBG(TLAN_DEBUG_GNRL, "%s: Resetting PHY.\n", dev->name);
	tlan_mii_sync(dev->base_addr);
	value = MII_GC_LOOPBK | MII_GC_RESET;
	tlan_mii_ग_लिखो_reg(dev, phy, MII_GEN_CTL, value);
	करो अणु
		tlan_mii_पढ़ो_reg(dev, phy, MII_GEN_CTL, &value);
		अगर (समय_after(jअगरfies, समयout)) अणु
			netdev_err(dev, "PHY reset timeout\n");
			वापस;
		पूर्ण
	पूर्ण जबतक (value & MII_GC_RESET);

	/* Wait क्रम 500 ms and initialize.
	 * I करोn't remember why I रुको this दीर्घ.
	 * I've changed this to 50ms, as it seems दीर्घ enough.
	 */
	tlan_set_समयr(dev, msecs_to_jअगरfies(50), TLAN_TIMER_PHY_START_LINK);

पूर्ण




अटल व्योम tlan_phy_start_link(काष्ठा net_device *dev)
अणु
	काष्ठा tlan_priv	*priv = netdev_priv(dev);
	u16		ability;
	u16		control;
	u16		data;
	u16		phy;
	u16		status;
	u16		tctl;

	phy = priv->phy[priv->phy_num];
	TLAN_DBG(TLAN_DEBUG_GNRL, "%s: Trying to activate link.\n", dev->name);
	tlan_mii_पढ़ो_reg(dev, phy, MII_GEN_STS, &status);
	tlan_mii_पढ़ो_reg(dev, phy, MII_GEN_STS, &ability);

	अगर ((status & MII_GS_AUTONEG) &&
	    (!priv->aui)) अणु
		ability = status >> 11;
		अगर (priv->speed  == TLAN_SPEED_10 &&
		    priv->duplex == TLAN_DUPLEX_HALF) अणु
			tlan_mii_ग_लिखो_reg(dev, phy, MII_GEN_CTL, 0x0000);
		पूर्ण अन्यथा अगर (priv->speed == TLAN_SPEED_10 &&
			   priv->duplex == TLAN_DUPLEX_FULL) अणु
			priv->tlan_full_duplex = true;
			tlan_mii_ग_लिखो_reg(dev, phy, MII_GEN_CTL, 0x0100);
		पूर्ण अन्यथा अगर (priv->speed == TLAN_SPEED_100 &&
			   priv->duplex == TLAN_DUPLEX_HALF) अणु
			tlan_mii_ग_लिखो_reg(dev, phy, MII_GEN_CTL, 0x2000);
		पूर्ण अन्यथा अगर (priv->speed == TLAN_SPEED_100 &&
			   priv->duplex == TLAN_DUPLEX_FULL) अणु
			priv->tlan_full_duplex = true;
			tlan_mii_ग_लिखो_reg(dev, phy, MII_GEN_CTL, 0x2100);
		पूर्ण अन्यथा अणु

			/* Set Auto-Neg advertisement */
			tlan_mii_ग_लिखो_reg(dev, phy, MII_AN_ADV,
					   (ability << 5) | 1);
			/* Enablee Auto-Neg */
			tlan_mii_ग_लिखो_reg(dev, phy, MII_GEN_CTL, 0x1000);
			/* Restart Auto-Neg */
			tlan_mii_ग_लिखो_reg(dev, phy, MII_GEN_CTL, 0x1200);
			/* Wait क्रम 4 sec क्रम स्वतःnegotiation
			 * to complete.  The max spec समय is less than this
			 * but the card need additional समय to start AN.
			 * .5 sec should be plenty extra.
			 */
			netdev_info(dev, "Starting autonegotiation\n");
			tlan_set_समयr(dev, (2*HZ), TLAN_TIMER_PHY_FINISH_AN);
			वापस;
		पूर्ण

	पूर्ण

	अगर ((priv->aui) && (priv->phy_num != 0)) अणु
		priv->phy_num = 0;
		data = TLAN_NET_CFG_1FRAG | TLAN_NET_CFG_1CHAN
			| TLAN_NET_CFG_PHY_EN;
		tlan_dio_ग_लिखो16(dev->base_addr, TLAN_NET_CONFIG, data);
		tlan_set_समयr(dev, msecs_to_jअगरfies(40), TLAN_TIMER_PHY_PDOWN);
		वापस;
	पूर्ण अन्यथा अगर (priv->phy_num == 0) अणु
		control = 0;
		tlan_mii_पढ़ो_reg(dev, phy, TLAN_TLPHY_CTL, &tctl);
		अगर (priv->aui) अणु
			tctl |= TLAN_TC_AUISEL;
		पूर्ण अन्यथा अणु
			tctl &= ~TLAN_TC_AUISEL;
			अगर (priv->duplex == TLAN_DUPLEX_FULL) अणु
				control |= MII_GC_DUPLEX;
				priv->tlan_full_duplex = true;
			पूर्ण
			अगर (priv->speed == TLAN_SPEED_100)
				control |= MII_GC_SPEEDSEL;
		पूर्ण
		tlan_mii_ग_लिखो_reg(dev, phy, MII_GEN_CTL, control);
		tlan_mii_ग_लिखो_reg(dev, phy, TLAN_TLPHY_CTL, tctl);
	पूर्ण

	/* Wait क्रम 2 sec to give the transceiver समय
	 * to establish link.
	 */
	tlan_set_समयr(dev, (4*HZ), TLAN_TIMER_FINISH_RESET);

पूर्ण




अटल व्योम tlan_phy_finish_स्वतः_neg(काष्ठा net_device *dev)
अणु
	काष्ठा tlan_priv	*priv = netdev_priv(dev);
	u16		an_adv;
	u16		an_lpa;
	u16		mode;
	u16		phy;
	u16		status;

	phy = priv->phy[priv->phy_num];

	tlan_mii_पढ़ो_reg(dev, phy, MII_GEN_STS, &status);
	udelay(1000);
	tlan_mii_पढ़ो_reg(dev, phy, MII_GEN_STS, &status);

	अगर (!(status & MII_GS_AUTOCMPLT)) अणु
		/* Wait क्रम 8 sec to give the process
		 * more समय.  Perhaps we should fail after a जबतक.
		 */
		tlan_set_समयr(dev, 2 * HZ, TLAN_TIMER_PHY_FINISH_AN);
		वापस;
	पूर्ण

	netdev_info(dev, "Autonegotiation complete\n");
	tlan_mii_पढ़ो_reg(dev, phy, MII_AN_ADV, &an_adv);
	tlan_mii_पढ़ो_reg(dev, phy, MII_AN_LPA, &an_lpa);
	mode = an_adv & an_lpa & 0x03E0;
	अगर (mode & 0x0100)
		priv->tlan_full_duplex = true;
	अन्यथा अगर (!(mode & 0x0080) && (mode & 0x0040))
		priv->tlan_full_duplex = true;

	/* चयन to पूर्णांकernal PHY क्रम 10 Mbps */
	अगर ((!(mode & 0x0180)) &&
	    (priv->adapter->flags & TLAN_ADAPTER_USE_INTERN_10) &&
	    (priv->phy_num != 0)) अणु
		priv->phy_num = 0;
		tlan_set_समयr(dev, msecs_to_jअगरfies(400), TLAN_TIMER_PHY_PDOWN);
		वापस;
	पूर्ण

	अगर (priv->phy_num == 0) अणु
		अगर ((priv->duplex == TLAN_DUPLEX_FULL) ||
		    (an_adv & an_lpa & 0x0040)) अणु
			tlan_mii_ग_लिखो_reg(dev, phy, MII_GEN_CTL,
					   MII_GC_AUTOENB | MII_GC_DUPLEX);
			netdev_info(dev, "Starting internal PHY with FULL-DUPLEX\n");
		पूर्ण अन्यथा अणु
			tlan_mii_ग_लिखो_reg(dev, phy, MII_GEN_CTL,
					   MII_GC_AUTOENB);
			netdev_info(dev, "Starting internal PHY with HALF-DUPLEX\n");
		पूर्ण
	पूर्ण

	/* Wait क्रम 100 ms.  No reason in partiticular.
	 */
	tlan_set_समयr(dev, msecs_to_jअगरfies(100), TLAN_TIMER_FINISH_RESET);

पूर्ण


/*********************************************************************
 *
 *     tlan_phy_monitor
 *
 *     Returns:
 *	      None
 *
 *     Params:
 *	      data	     The device काष्ठाure of this device.
 *
 *
 *     This function monitors PHY condition by पढ़ोing the status
 *     रेजिस्टर via the MII bus, controls LINK LED and notअगरies the
 *     kernel about link state.
 *
 *******************************************************************/

अटल व्योम tlan_phy_monitor(काष्ठा समयr_list *t)
अणु
	काष्ठा tlan_priv *priv = from_समयr(priv, t, media_समयr);
	काष्ठा net_device *dev = priv->dev;
	u16     phy;
	u16     phy_status;

	phy = priv->phy[priv->phy_num];

	/* Get PHY status रेजिस्टर */
	tlan_mii_पढ़ो_reg(dev, phy, MII_GEN_STS, &phy_status);

	/* Check अगर link has been lost */
	अगर (!(phy_status & MII_GS_LINK)) अणु
		अगर (netअगर_carrier_ok(dev)) अणु
			prपूर्णांकk(KERN_DEBUG "TLAN: %s has lost link\n",
			       dev->name);
			tlan_dio_ग_लिखो8(dev->base_addr, TLAN_LED_REG, 0);
			netअगर_carrier_off(dev);
			अगर (priv->adapter->flags & TLAN_ADAPTER_USE_INTERN_10) अणु
				/* घातer करोwn पूर्णांकernal PHY */
				u16 data = MII_GC_PDOWN | MII_GC_LOOPBK |
					   MII_GC_ISOLATE;

				tlan_mii_sync(dev->base_addr);
				tlan_mii_ग_लिखो_reg(dev, priv->phy[0],
						   MII_GEN_CTL, data);
				/* set to बाह्यal PHY */
				priv->phy_num = 1;
				/* restart स्वतःnegotiation */
				tlan_set_समयr(dev, msecs_to_jअगरfies(400),
					       TLAN_TIMER_PHY_PDOWN);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Link restablished? */
	अगर ((phy_status & MII_GS_LINK) && !netअगर_carrier_ok(dev)) अणु
		tlan_dio_ग_लिखो8(dev->base_addr, TLAN_LED_REG, TLAN_LED_LINK);
		prपूर्णांकk(KERN_DEBUG "TLAN: %s has reestablished link\n",
		       dev->name);
		netअगर_carrier_on(dev);
	पूर्ण
	priv->media_समयr.expires = jअगरfies + HZ;
	add_समयr(&priv->media_समयr);
पूर्ण


/*****************************************************************************
******************************************************************************

ThunderLAN driver MII routines

these routines are based on the inक्रमmation in chap. 2 of the
"ThunderLAN Programmer's Guide", pp. 15-24.

******************************************************************************
*****************************************************************************/


/***************************************************************
 *	__tlan_mii_पढ़ो_reg
 *
 *	Returns:
 *		false	अगर ack received ok
 *		true	अगर no ack received or other error
 *
 *	Parms:
 *		dev		The device काष्ठाure containing
 *				The io address and पूर्णांकerrupt count
 *				क्रम this device.
 *		phy		The address of the PHY to be queried.
 *		reg		The रेजिस्टर whose contents are to be
 *				retrieved.
 *		val		A poपूर्णांकer to a variable to store the
 *				retrieved value.
 *
 *	This function uses the TLAN's MII bus to retrieve the contents
 *	of a given रेजिस्टर on a PHY.  It sends the appropriate info
 *	and then पढ़ोs the 16-bit रेजिस्टर value from the MII bus via
 *	the TLAN SIO रेजिस्टर.
 *
 **************************************************************/

अटल bool
__tlan_mii_पढ़ो_reg(काष्ठा net_device *dev, u16 phy, u16 reg, u16 *val)
अणु
	u8	nack;
	u16	sio, पंचांगp;
	u32	i;
	bool	err;
	पूर्णांक	mपूर्णांकen;
	काष्ठा tlan_priv *priv = netdev_priv(dev);

	lockdep_निश्चित_held(&priv->lock);

	err = false;
	outw(TLAN_NET_SIO, dev->base_addr + TLAN_DIO_ADR);
	sio = dev->base_addr + TLAN_DIO_DATA + TLAN_NET_SIO;

	tlan_mii_sync(dev->base_addr);

	mपूर्णांकen = tlan_get_bit(TLAN_NET_SIO_MINTEN, sio);
	अगर (mपूर्णांकen)
		tlan_clear_bit(TLAN_NET_SIO_MINTEN, sio);

	tlan_mii_send_data(dev->base_addr, 0x1, 2);	/* start (01b) */
	tlan_mii_send_data(dev->base_addr, 0x2, 2);	/* पढ़ो  (10b) */
	tlan_mii_send_data(dev->base_addr, phy, 5);	/* device #      */
	tlan_mii_send_data(dev->base_addr, reg, 5);	/* रेजिस्टर #    */


	tlan_clear_bit(TLAN_NET_SIO_MTXEN, sio);	/* change direction */

	tlan_clear_bit(TLAN_NET_SIO_MCLK, sio);		/* घड़ी idle bit */
	tlan_set_bit(TLAN_NET_SIO_MCLK, sio);
	tlan_clear_bit(TLAN_NET_SIO_MCLK, sio);		/* रुको 300ns */

	nack = tlan_get_bit(TLAN_NET_SIO_MDATA, sio);	/* check क्रम ACK */
	tlan_set_bit(TLAN_NET_SIO_MCLK, sio);		/* finish ACK */
	अगर (nack) अणु					/* no ACK, so fake it */
		क्रम (i = 0; i < 16; i++) अणु
			tlan_clear_bit(TLAN_NET_SIO_MCLK, sio);
			tlan_set_bit(TLAN_NET_SIO_MCLK, sio);
		पूर्ण
		पंचांगp = 0xffff;
		err = true;
	पूर्ण अन्यथा अणु					/* ACK, so पढ़ो data */
		क्रम (पंचांगp = 0, i = 0x8000; i; i >>= 1) अणु
			tlan_clear_bit(TLAN_NET_SIO_MCLK, sio);
			अगर (tlan_get_bit(TLAN_NET_SIO_MDATA, sio))
				पंचांगp |= i;
			tlan_set_bit(TLAN_NET_SIO_MCLK, sio);
		पूर्ण
	पूर्ण


	tlan_clear_bit(TLAN_NET_SIO_MCLK, sio);		/* idle cycle */
	tlan_set_bit(TLAN_NET_SIO_MCLK, sio);

	अगर (mपूर्णांकen)
		tlan_set_bit(TLAN_NET_SIO_MINTEN, sio);

	*val = पंचांगp;

	वापस err;
पूर्ण

अटल व्योम tlan_mii_पढ़ो_reg(काष्ठा net_device *dev, u16 phy, u16 reg,
			      u16 *val)
अणु
	काष्ठा tlan_priv *priv = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);
	__tlan_mii_पढ़ो_reg(dev, phy, reg, val);
	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

/***************************************************************
 *	tlan_mii_send_data
 *
 *	Returns:
 *		Nothing
 *	Parms:
 *		base_port	The base IO port of the adapter	in
 *				question.
 *		dev		The address of the PHY to be queried.
 *		data		The value to be placed on the MII bus.
 *		num_bits	The number of bits in data that are to
 *				be placed on the MII bus.
 *
 *	This function sends on sequence of bits on the MII
 *	configuration bus.
 *
 **************************************************************/

अटल व्योम tlan_mii_send_data(u16 base_port, u32 data, अचिन्हित num_bits)
अणु
	u16 sio;
	u32 i;

	अगर (num_bits == 0)
		वापस;

	outw(TLAN_NET_SIO, base_port + TLAN_DIO_ADR);
	sio = base_port + TLAN_DIO_DATA + TLAN_NET_SIO;
	tlan_set_bit(TLAN_NET_SIO_MTXEN, sio);

	क्रम (i = (0x1 << (num_bits - 1)); i; i >>= 1) अणु
		tlan_clear_bit(TLAN_NET_SIO_MCLK, sio);
		(व्योम) tlan_get_bit(TLAN_NET_SIO_MCLK, sio);
		अगर (data & i)
			tlan_set_bit(TLAN_NET_SIO_MDATA, sio);
		अन्यथा
			tlan_clear_bit(TLAN_NET_SIO_MDATA, sio);
		tlan_set_bit(TLAN_NET_SIO_MCLK, sio);
		(व्योम) tlan_get_bit(TLAN_NET_SIO_MCLK, sio);
	पूर्ण

पूर्ण




/***************************************************************
 *	TLan_MiiSync
 *
 *	Returns:
 *		Nothing
 *	Parms:
 *		base_port	The base IO port of the adapter in
 *				question.
 *
 *	This functions syncs all PHYs in terms of the MII configuration
 *	bus.
 *
 **************************************************************/

अटल व्योम tlan_mii_sync(u16 base_port)
अणु
	पूर्णांक i;
	u16 sio;

	outw(TLAN_NET_SIO, base_port + TLAN_DIO_ADR);
	sio = base_port + TLAN_DIO_DATA + TLAN_NET_SIO;

	tlan_clear_bit(TLAN_NET_SIO_MTXEN, sio);
	क्रम (i = 0; i < 32; i++) अणु
		tlan_clear_bit(TLAN_NET_SIO_MCLK, sio);
		tlan_set_bit(TLAN_NET_SIO_MCLK, sio);
	पूर्ण

पूर्ण




/***************************************************************
 *	__tlan_mii_ग_लिखो_reg
 *
 *	Returns:
 *		Nothing
 *	Parms:
 *		dev		The device काष्ठाure क्रम the device
 *				to ग_लिखो to.
 *		phy		The address of the PHY to be written to.
 *		reg		The रेजिस्टर whose contents are to be
 *				written.
 *		val		The value to be written to the रेजिस्टर.
 *
 *	This function uses the TLAN's MII bus to ग_लिखो the contents of a
 *	given रेजिस्टर on a PHY.  It sends the appropriate info and then
 *	ग_लिखोs the 16-bit रेजिस्टर value from the MII configuration bus
 *	via the TLAN SIO रेजिस्टर.
 *
 **************************************************************/

अटल व्योम
__tlan_mii_ग_लिखो_reg(काष्ठा net_device *dev, u16 phy, u16 reg, u16 val)
अणु
	u16	sio;
	पूर्णांक	mपूर्णांकen;
	काष्ठा tlan_priv *priv = netdev_priv(dev);

	lockdep_निश्चित_held(&priv->lock);

	outw(TLAN_NET_SIO, dev->base_addr + TLAN_DIO_ADR);
	sio = dev->base_addr + TLAN_DIO_DATA + TLAN_NET_SIO;

	tlan_mii_sync(dev->base_addr);

	mपूर्णांकen = tlan_get_bit(TLAN_NET_SIO_MINTEN, sio);
	अगर (mपूर्णांकen)
		tlan_clear_bit(TLAN_NET_SIO_MINTEN, sio);

	tlan_mii_send_data(dev->base_addr, 0x1, 2);	/* start (01b) */
	tlan_mii_send_data(dev->base_addr, 0x1, 2);	/* ग_लिखो (01b) */
	tlan_mii_send_data(dev->base_addr, phy, 5);	/* device #      */
	tlan_mii_send_data(dev->base_addr, reg, 5);	/* रेजिस्टर #    */

	tlan_mii_send_data(dev->base_addr, 0x2, 2);	/* send ACK */
	tlan_mii_send_data(dev->base_addr, val, 16);	/* send data */

	tlan_clear_bit(TLAN_NET_SIO_MCLK, sio);	/* idle cycle */
	tlan_set_bit(TLAN_NET_SIO_MCLK, sio);

	अगर (mपूर्णांकen)
		tlan_set_bit(TLAN_NET_SIO_MINTEN, sio);

पूर्ण

अटल व्योम
tlan_mii_ग_लिखो_reg(काष्ठा net_device *dev, u16 phy, u16 reg, u16 val)
अणु
	काष्ठा tlan_priv *priv = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);
	__tlan_mii_ग_लिखो_reg(dev, phy, reg, val);
	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण


/*****************************************************************************
******************************************************************************

ThunderLAN driver eeprom routines

the Compaq netelligent 10 and 10/100 cards use a microchip 24C02A
EEPROM.  these functions are based on inक्रमmation in microchip's
data sheet.  I करोn't know how well this functions will work with
other Eeproms.

******************************************************************************
*****************************************************************************/


/***************************************************************
 *	tlan_ee_send_start
 *
 *	Returns:
 *		Nothing
 *	Parms:
 *		io_base		The IO port base address क्रम the
 *				TLAN device with the EEPROM to
 *				use.
 *
 *	This function sends a start cycle to an EEPROM attached
 *	to a TLAN chip.
 *
 **************************************************************/

अटल व्योम tlan_ee_send_start(u16 io_base)
अणु
	u16	sio;

	outw(TLAN_NET_SIO, io_base + TLAN_DIO_ADR);
	sio = io_base + TLAN_DIO_DATA + TLAN_NET_SIO;

	tlan_set_bit(TLAN_NET_SIO_ECLOK, sio);
	tlan_set_bit(TLAN_NET_SIO_EDATA, sio);
	tlan_set_bit(TLAN_NET_SIO_ETXEN, sio);
	tlan_clear_bit(TLAN_NET_SIO_EDATA, sio);
	tlan_clear_bit(TLAN_NET_SIO_ECLOK, sio);

पूर्ण




/***************************************************************
 *	tlan_ee_send_byte
 *
 *	Returns:
 *		If the correct ack was received, 0, otherwise 1
 *	Parms:	io_base		The IO port base address क्रम the
 *				TLAN device with the EEPROM to
 *				use.
 *		data		The 8 bits of inक्रमmation to
 *				send to the EEPROM.
 *		stop		If TLAN_EEPROM_STOP is passed, a
 *				stop cycle is sent after the
 *				byte is sent after the ack is
 *				पढ़ो.
 *
 *	This function sends a byte on the serial EEPROM line,
 *	driving the घड़ी to send each bit. The function then
 *	reverses transmission direction and पढ़ोs an acknowledge
 *	bit.
 *
 **************************************************************/

अटल पूर्णांक tlan_ee_send_byte(u16 io_base, u8 data, पूर्णांक stop)
अणु
	पूर्णांक	err;
	u8	place;
	u16	sio;

	outw(TLAN_NET_SIO, io_base + TLAN_DIO_ADR);
	sio = io_base + TLAN_DIO_DATA + TLAN_NET_SIO;

	/* Assume घड़ी is low, tx is enabled; */
	क्रम (place = 0x80; place != 0; place >>= 1) अणु
		अगर (place & data)
			tlan_set_bit(TLAN_NET_SIO_EDATA, sio);
		अन्यथा
			tlan_clear_bit(TLAN_NET_SIO_EDATA, sio);
		tlan_set_bit(TLAN_NET_SIO_ECLOK, sio);
		tlan_clear_bit(TLAN_NET_SIO_ECLOK, sio);
	पूर्ण
	tlan_clear_bit(TLAN_NET_SIO_ETXEN, sio);
	tlan_set_bit(TLAN_NET_SIO_ECLOK, sio);
	err = tlan_get_bit(TLAN_NET_SIO_EDATA, sio);
	tlan_clear_bit(TLAN_NET_SIO_ECLOK, sio);
	tlan_set_bit(TLAN_NET_SIO_ETXEN, sio);

	अगर ((!err) && stop) अणु
		/* STOP, उठाओ data जबतक घड़ी is high */
		tlan_clear_bit(TLAN_NET_SIO_EDATA, sio);
		tlan_set_bit(TLAN_NET_SIO_ECLOK, sio);
		tlan_set_bit(TLAN_NET_SIO_EDATA, sio);
	पूर्ण

	वापस err;

पूर्ण




/***************************************************************
 *	tlan_ee_receive_byte
 *
 *	Returns:
 *		Nothing
 *	Parms:
 *		io_base		The IO port base address क्रम the
 *				TLAN device with the EEPROM to
 *				use.
 *		data		An address to a अक्षर to hold the
 *				data sent from the EEPROM.
 *		stop		If TLAN_EEPROM_STOP is passed, a
 *				stop cycle is sent after the
 *				byte is received, and no ack is
 *				sent.
 *
 *	This function receives 8 bits of data from the EEPROM
 *	over the serial link.  It then sends and ack bit, or no
 *	ack and a stop bit.  This function is used to retrieve
 *	data after the address of a byte in the EEPROM has been
 *	sent.
 *
 **************************************************************/

अटल व्योम tlan_ee_receive_byte(u16 io_base, u8 *data, पूर्णांक stop)
अणु
	u8  place;
	u16 sio;

	outw(TLAN_NET_SIO, io_base + TLAN_DIO_ADR);
	sio = io_base + TLAN_DIO_DATA + TLAN_NET_SIO;
	*data = 0;

	/* Assume घड़ी is low, tx is enabled; */
	tlan_clear_bit(TLAN_NET_SIO_ETXEN, sio);
	क्रम (place = 0x80; place; place >>= 1) अणु
		tlan_set_bit(TLAN_NET_SIO_ECLOK, sio);
		अगर (tlan_get_bit(TLAN_NET_SIO_EDATA, sio))
			*data |= place;
		tlan_clear_bit(TLAN_NET_SIO_ECLOK, sio);
	पूर्ण

	tlan_set_bit(TLAN_NET_SIO_ETXEN, sio);
	अगर (!stop) अणु
		tlan_clear_bit(TLAN_NET_SIO_EDATA, sio); /* ack = 0 */
		tlan_set_bit(TLAN_NET_SIO_ECLOK, sio);
		tlan_clear_bit(TLAN_NET_SIO_ECLOK, sio);
	पूर्ण अन्यथा अणु
		tlan_set_bit(TLAN_NET_SIO_EDATA, sio);	/* no ack = 1 (?) */
		tlan_set_bit(TLAN_NET_SIO_ECLOK, sio);
		tlan_clear_bit(TLAN_NET_SIO_ECLOK, sio);
		/* STOP, उठाओ data जबतक घड़ी is high */
		tlan_clear_bit(TLAN_NET_SIO_EDATA, sio);
		tlan_set_bit(TLAN_NET_SIO_ECLOK, sio);
		tlan_set_bit(TLAN_NET_SIO_EDATA, sio);
	पूर्ण

पूर्ण




/***************************************************************
 *	tlan_ee_पढ़ो_byte
 *
 *	Returns:
 *		No error = 0, अन्यथा, the stage at which the error
 *		occurred.
 *	Parms:
 *		io_base		The IO port base address क्रम the
 *				TLAN device with the EEPROM to
 *				use.
 *		ee_addr		The address of the byte in the
 *				EEPROM whose contents are to be
 *				retrieved.
 *		data		An address to a अक्षर to hold the
 *				data obtained from the EEPROM.
 *
 *	This function पढ़ोs a byte of inक्रमmation from an byte
 *	cell in the EEPROM.
 *
 **************************************************************/

अटल पूर्णांक tlan_ee_पढ़ो_byte(काष्ठा net_device *dev, u8 ee_addr, u8 *data)
अणु
	पूर्णांक err;
	काष्ठा tlan_priv *priv = netdev_priv(dev);
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&priv->lock, flags);

	tlan_ee_send_start(dev->base_addr);
	err = tlan_ee_send_byte(dev->base_addr, 0xa0, TLAN_EEPROM_ACK);
	अगर (err) अणु
		ret = 1;
		जाओ fail;
	पूर्ण
	err = tlan_ee_send_byte(dev->base_addr, ee_addr, TLAN_EEPROM_ACK);
	अगर (err) अणु
		ret = 2;
		जाओ fail;
	पूर्ण
	tlan_ee_send_start(dev->base_addr);
	err = tlan_ee_send_byte(dev->base_addr, 0xa1, TLAN_EEPROM_ACK);
	अगर (err) अणु
		ret = 3;
		जाओ fail;
	पूर्ण
	tlan_ee_receive_byte(dev->base_addr, data, TLAN_EEPROM_STOP);
fail:
	spin_unlock_irqrestore(&priv->lock, flags);

	वापस ret;

पूर्ण



