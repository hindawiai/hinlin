<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * File Name:
 *   skfddi.c
 *
 * Copyright Inक्रमmation:
 *   Copyright SysKonnect 1998,1999.
 *
 * The inक्रमmation in this file is provided "AS IS" without warranty.
 *
 * Abstract:
 *   A Linux device driver supporting the SysKonnect FDDI PCI controller
 *   familie.
 *
 * Maपूर्णांकainers:
 *   CG    Christoph Goos (cgoos@syskonnect.de)
 *
 * Contributors:
 *   DM    David S. Miller
 *
 * Address all question to:
 *   linux@syskonnect.de
 *
 * The technical manual क्रम the adapters is available from SysKonnect's
 * web pages: www.syskonnect.com
 * Goto "Support" and search Knowledge Base क्रम "manual".
 *
 * Driver Architecture:
 *   The driver architecture is based on the DEC FDDI driver by
 *   Lawrence V. Stefani and several ethernet drivers.
 *   I also used an existing Winकरोws NT miniport driver.
 *   All hardware dependent functions are handled by the SysKonnect
 *   Hardware Module.
 *   The only headerfiles that are directly related to this source
 *   are skfddi.c, h/types.h, h/osdef1st.h, h/targetos.h.
 *   The others beदीर्घ to the SysKonnect FDDI Hardware Module and
 *   should better not be changed.
 *
 * Modअगरication History:
 *              Date            Name    Description
 *              02-Mar-98       CG	Created.
 *
 *		10-Mar-99	CG	Support क्रम 2.2.x added.
 *		25-Mar-99	CG	Corrected IRQ routing क्रम SMP (APIC)
 *		26-Oct-99	CG	Fixed compilation error on 2.2.13
 *		12-Nov-99	CG	Source code release
 *		22-Nov-99	CG	Included in kernel source.
 *		07-May-00	DM	64 bit fixes, new dma पूर्णांकerface
 *		31-Jul-03	DB	Audit copy_*_user in skfp_ioctl
 *					  Daniele Bellucci <bellucda@tiscali.it>
 *		03-Dec-03	SH	Convert to PCI device model
 *
 * Compilation options (-Dxxx):
 *              DRIVERDEBUG     prपूर्णांक lots of messages to log file
 *              DUMPPACKETS     prपूर्णांक received/transmitted packets to logfile
 * 
 * Tested cpu architectures:
 *	- i386
 *	- sparc64
 */

/* Version inक्रमmation string - should be updated prior to */
/* each new release!!! */
#घोषणा VERSION		"2.07"

अटल स्थिर अक्षर * स्थिर boot_msg = 
	"SysKonnect FDDI PCI Adapter driver v" VERSION " for\n"
	"  SK-55xx/SK-58xx adapters (SK-NET FDDI-FP/UP/LP)";

/* Include files */

#समावेश <linux/capability.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/fddidevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/bitops.h>
#समावेश <linux/gfp.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>

#समावेश	"h/types.h"
#अघोषित ADDR			// unकरो Linux definition
#समावेश	"h/skfbi.h"
#समावेश	"h/fddi.h"
#समावेश	"h/smc.h"
#समावेश	"h/smtstate.h"


// Define module-wide (अटल) routines
अटल पूर्णांक skfp_driver_init(काष्ठा net_device *dev);
अटल पूर्णांक skfp_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक skfp_बंद(काष्ठा net_device *dev);
अटल irqवापस_t skfp_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
अटल काष्ठा net_device_stats *skfp_ctl_get_stats(काष्ठा net_device *dev);
अटल व्योम skfp_ctl_set_multicast_list(काष्ठा net_device *dev);
अटल व्योम skfp_ctl_set_multicast_list_wo_lock(काष्ठा net_device *dev);
अटल पूर्णांक skfp_ctl_set_mac_address(काष्ठा net_device *dev, व्योम *addr);
अटल पूर्णांक skfp_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd);
अटल netdev_tx_t skfp_send_pkt(काष्ठा sk_buff *skb,
				       काष्ठा net_device *dev);
अटल व्योम send_queued_packets(काष्ठा s_smc *smc);
अटल व्योम CheckSourceAddress(अचिन्हित अक्षर *frame, अचिन्हित अक्षर *hw_addr);
अटल व्योम ResetAdapter(काष्ठा s_smc *smc);


// Functions needed by the hardware module
व्योम *mac_drv_get_space(काष्ठा s_smc *smc, u_पूर्णांक size);
व्योम *mac_drv_get_desc_mem(काष्ठा s_smc *smc, u_पूर्णांक size);
अचिन्हित दीर्घ mac_drv_virt2phys(काष्ठा s_smc *smc, व्योम *virt);
अचिन्हित दीर्घ dma_master(काष्ठा s_smc *smc, व्योम *virt, पूर्णांक len, पूर्णांक flag);
व्योम dma_complete(काष्ठा s_smc *smc, अस्थिर जोड़ s_fp_descr *descr,
		  पूर्णांक flag);
व्योम mac_drv_tx_complete(काष्ठा s_smc *smc, अस्थिर काष्ठा s_smt_fp_txd *txd);
व्योम llc_restart_tx(काष्ठा s_smc *smc);
व्योम mac_drv_rx_complete(काष्ठा s_smc *smc, अस्थिर काष्ठा s_smt_fp_rxd *rxd,
			 पूर्णांक frag_count, पूर्णांक len);
व्योम mac_drv_requeue_rxd(काष्ठा s_smc *smc, अस्थिर काष्ठा s_smt_fp_rxd *rxd,
			 पूर्णांक frag_count);
व्योम mac_drv_fill_rxd(काष्ठा s_smc *smc);
व्योम mac_drv_clear_rxd(काष्ठा s_smc *smc, अस्थिर काष्ठा s_smt_fp_rxd *rxd,
		       पूर्णांक frag_count);
पूर्णांक mac_drv_rx_init(काष्ठा s_smc *smc, पूर्णांक len, पूर्णांक fc, अक्षर *look_ahead,
		    पूर्णांक la_len);
व्योम dump_data(अचिन्हित अक्षर *Data, पूर्णांक length);

// External functions from the hardware module
बाह्य u_पूर्णांक mac_drv_check_space(व्योम);
बाह्य पूर्णांक mac_drv_init(काष्ठा s_smc *smc);
बाह्य व्योम hwm_tx_frag(काष्ठा s_smc *smc, अक्षर far * virt, u_दीर्घ phys,
			पूर्णांक len, पूर्णांक frame_status);
बाह्य पूर्णांक hwm_tx_init(काष्ठा s_smc *smc, u_अक्षर fc, पूर्णांक frag_count,
		       पूर्णांक frame_len, पूर्णांक frame_status);
बाह्य व्योम fddi_isr(काष्ठा s_smc *smc);
बाह्य व्योम hwm_rx_frag(काष्ठा s_smc *smc, अक्षर far * virt, u_दीर्घ phys,
			पूर्णांक len, पूर्णांक frame_status);
बाह्य व्योम mac_drv_rx_mode(काष्ठा s_smc *smc, पूर्णांक mode);
बाह्य व्योम mac_drv_clear_rx_queue(काष्ठा s_smc *smc);
बाह्य व्योम enable_tx_irq(काष्ठा s_smc *smc, u_लघु queue);

अटल स्थिर काष्ठा pci_device_id skfddi_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_SK, PCI_DEVICE_ID_SK_FP, PCI_ANY_ID, PCI_ANY_ID, पूर्ण,
	अणु पूर्ण			/* Terminating entry */
पूर्ण;
MODULE_DEVICE_TABLE(pci, skfddi_pci_tbl);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mirko Lindner <mlindner@syskonnect.de>");

// Define module-wide (अटल) variables

अटल पूर्णांक num_boards;	/* total number of adapters configured */

अटल स्थिर काष्ठा net_device_ops skfp_netdev_ops = अणु
	.nकरो_खोलो		= skfp_खोलो,
	.nकरो_stop		= skfp_बंद,
	.nकरो_start_xmit		= skfp_send_pkt,
	.nकरो_get_stats		= skfp_ctl_get_stats,
	.nकरो_set_rx_mode	= skfp_ctl_set_multicast_list,
	.nकरो_set_mac_address	= skfp_ctl_set_mac_address,
	.nकरो_करो_ioctl		= skfp_ioctl,
पूर्ण;

/*
 * =================
 * = skfp_init_one =
 * =================
 *   
 * Overview:
 *   Probes क्रम supported FDDI PCI controllers
 *  
 * Returns:
 *   Condition code
 *       
 * Arguments:
 *   pdev - poपूर्णांकer to PCI device inक्रमmation
 *
 * Functional Description:
 *   This is now called by PCI driver registration process
 *   क्रम each board found.
 *   
 * Return Codes:
 *   0           - This device (fddi0, fddi1, etc) configured successfully
 *   -ENODEV - No devices present, or no SysKonnect FDDI PCI device
 *                         present क्रम this device name
 *
 *
 * Side Effects:
 *   Device काष्ठाures क्रम FDDI adapters (fddi0, fddi1, etc) are
 *   initialized and the board resources are पढ़ो and stored in
 *   the device काष्ठाure.
 */
अटल पूर्णांक skfp_init_one(काष्ठा pci_dev *pdev,
				स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *dev;
	काष्ठा s_smc *smc;	/* board poपूर्णांकer */
	व्योम __iomem *mem;
	पूर्णांक err;

	pr_debug("entering skfp_init_one\n");

	अगर (num_boards == 0) 
		prपूर्णांकk("%s\n", boot_msg);

	err = pci_enable_device(pdev);
	अगर (err)
		वापस err;

	err = pci_request_regions(pdev, "skfddi");
	अगर (err)
		जाओ err_out1;

	pci_set_master(pdev);

#अगर_घोषित MEM_MAPPED_IO
	अगर (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM)) अणु
		prपूर्णांकk(KERN_ERR "skfp: region is not an MMIO resource\n");
		err = -EIO;
		जाओ err_out2;
	पूर्ण

	mem = ioremap(pci_resource_start(pdev, 0), 0x4000);
#अन्यथा
	अगर (!(pci_resource_flags(pdev, 1) & IO_RESOURCE_IO)) अणु
		prपूर्णांकk(KERN_ERR "skfp: region is not PIO resource\n");
		err = -EIO;
		जाओ err_out2;
	पूर्ण

	mem = ioport_map(pci_resource_start(pdev, 1), FP_IO_LEN);
#पूर्ण_अगर
	अगर (!mem) अणु
		prपूर्णांकk(KERN_ERR "skfp:  Unable to map register, "
				"FDDI adapter will be disabled.\n");
		err = -EIO;
		जाओ err_out2;
	पूर्ण

	dev = alloc_fddidev(माप(काष्ठा s_smc));
	अगर (!dev) अणु
		prपूर्णांकk(KERN_ERR "skfp: Unable to allocate fddi device, "
				"FDDI adapter will be disabled.\n");
		err = -ENOMEM;
		जाओ err_out3;
	पूर्ण

	dev->irq = pdev->irq;
	dev->netdev_ops = &skfp_netdev_ops;

	SET_NETDEV_DEV(dev, &pdev->dev);

	/* Initialize board काष्ठाure with bus-specअगरic info */
	smc = netdev_priv(dev);
	smc->os.dev = dev;
	smc->os.bus_type = SK_BUS_TYPE_PCI;
	smc->os.pdev = *pdev;
	smc->os.QueueSkb = MAX_TX_QUEUE_LEN;
	smc->os.MaxFrameSize = MAX_FRAME_SIZE;
	smc->os.dev = dev;
	smc->hw.slot = -1;
	smc->hw.iop = mem;
	smc->os.ResetRequested = FALSE;
	skb_queue_head_init(&smc->os.SendSkbQueue);

	dev->base_addr = (अचिन्हित दीर्घ)mem;

	err = skfp_driver_init(dev);
	अगर (err)
		जाओ err_out4;

	err = रेजिस्टर_netdev(dev);
	अगर (err)
		जाओ err_out5;

	++num_boards;
	pci_set_drvdata(pdev, dev);

	अगर ((pdev->subप्रणाली_device & 0xff00) == 0x5500 ||
	    (pdev->subप्रणाली_device & 0xff00) == 0x5800) 
		prपूर्णांकk("%s: SysKonnect FDDI PCI adapter"
		       " found (SK-%04X)\n", dev->name,	
		       pdev->subप्रणाली_device);
	अन्यथा
		prपूर्णांकk("%s: FDDI PCI adapter found\n", dev->name);

	वापस 0;
err_out5:
	अगर (smc->os.SharedMemAddr) 
		dma_मुक्त_coherent(&pdev->dev, smc->os.SharedMemSize,
				  smc->os.SharedMemAddr,
				  smc->os.SharedMemDMA);
	dma_मुक्त_coherent(&pdev->dev, MAX_FRAME_SIZE,
			  smc->os.LocalRxBuffer, smc->os.LocalRxBufferDMA);
err_out4:
	मुक्त_netdev(dev);
err_out3:
#अगर_घोषित MEM_MAPPED_IO
	iounmap(mem);
#अन्यथा
	ioport_unmap(mem);
#पूर्ण_अगर
err_out2:
	pci_release_regions(pdev);
err_out1:
	pci_disable_device(pdev);
	वापस err;
पूर्ण

/*
 * Called क्रम each adapter board from pci_unरेजिस्टर_driver
 */
अटल व्योम skfp_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *p = pci_get_drvdata(pdev);
	काष्ठा s_smc *lp = netdev_priv(p);

	unरेजिस्टर_netdev(p);

	अगर (lp->os.SharedMemAddr) अणु
		dma_मुक्त_coherent(&pdev->dev,
				  lp->os.SharedMemSize,
				  lp->os.SharedMemAddr,
				  lp->os.SharedMemDMA);
		lp->os.SharedMemAddr = शून्य;
	पूर्ण
	अगर (lp->os.LocalRxBuffer) अणु
		dma_मुक्त_coherent(&pdev->dev,
				  MAX_FRAME_SIZE,
				  lp->os.LocalRxBuffer,
				  lp->os.LocalRxBufferDMA);
		lp->os.LocalRxBuffer = शून्य;
	पूर्ण
#अगर_घोषित MEM_MAPPED_IO
	iounmap(lp->hw.iop);
#अन्यथा
	ioport_unmap(lp->hw.iop);
#पूर्ण_अगर
	pci_release_regions(pdev);
	मुक्त_netdev(p);

	pci_disable_device(pdev);
पूर्ण

/*
 * ====================
 * = skfp_driver_init =
 * ====================
 *   
 * Overview:
 *   Initializes reमुख्यing adapter board काष्ठाure inक्रमmation
 *   and makes sure adapter is in a safe state prior to skfp_खोलो().
 *  
 * Returns:
 *   Condition code
 *       
 * Arguments:
 *   dev - poपूर्णांकer to device inक्रमmation
 *
 * Functional Description:
 *   This function allocates additional resources such as the host memory
 *   blocks needed by the adapter.
 *   The adapter is also reset. The OS must call skfp_खोलो() to खोलो 
 *   the adapter and bring it on-line.
 *
 * Return Codes:
 *    0 - initialization succeeded
 *   -1 - initialization failed
 */
अटल  पूर्णांक skfp_driver_init(काष्ठा net_device *dev)
अणु
	काष्ठा s_smc *smc = netdev_priv(dev);
	skfddi_priv *bp = &smc->os;
	पूर्णांक err = -EIO;

	pr_debug("entering skfp_driver_init\n");

	// set the io address in निजी काष्ठाures
	bp->base_addr = dev->base_addr;

	// Get the पूर्णांकerrupt level from the PCI Configuration Table
	smc->hw.irq = dev->irq;

	spin_lock_init(&bp->DriverLock);
	
	// Allocate invalid frame
	bp->LocalRxBuffer = dma_alloc_coherent(&bp->pdev.dev, MAX_FRAME_SIZE,
					       &bp->LocalRxBufferDMA,
					       GFP_ATOMIC);
	अगर (!bp->LocalRxBuffer) अणु
		prपूर्णांकk("could not allocate mem for ");
		prपूर्णांकk("LocalRxBuffer: %d byte\n", MAX_FRAME_SIZE);
		जाओ fail;
	पूर्ण

	// Determine the required size of the 'shared' memory area.
	bp->SharedMemSize = mac_drv_check_space();
	pr_debug("Memory for HWM: %ld\n", bp->SharedMemSize);
	अगर (bp->SharedMemSize > 0) अणु
		bp->SharedMemSize += 16;	// क्रम descriptor alignment

		bp->SharedMemAddr = dma_alloc_coherent(&bp->pdev.dev,
						       bp->SharedMemSize,
						       &bp->SharedMemDMA,
						       GFP_ATOMIC);
		अगर (!bp->SharedMemAddr) अणु
			prपूर्णांकk("could not allocate mem for ");
			prपूर्णांकk("hardware module: %ld byte\n",
			       bp->SharedMemSize);
			जाओ fail;
		पूर्ण

	पूर्ण अन्यथा अणु
		bp->SharedMemAddr = शून्य;
	पूर्ण

	bp->SharedMemHeap = 0;

	card_stop(smc);		// Reset adapter.

	pr_debug("mac_drv_init()..\n");
	अगर (mac_drv_init(smc) != 0) अणु
		pr_debug("mac_drv_init() failed\n");
		जाओ fail;
	पूर्ण
	पढ़ो_address(smc, शून्य);
	pr_debug("HW-Addr: %pMF\n", smc->hw.fddi_canon_addr.a);
	स_नकल(dev->dev_addr, smc->hw.fddi_canon_addr.a, ETH_ALEN);

	smt_reset_शेषs(smc, 0);

	वापस 0;

fail:
	अगर (bp->SharedMemAddr) अणु
		dma_मुक्त_coherent(&bp->pdev.dev,
				  bp->SharedMemSize,
				  bp->SharedMemAddr,
				  bp->SharedMemDMA);
		bp->SharedMemAddr = शून्य;
	पूर्ण
	अगर (bp->LocalRxBuffer) अणु
		dma_मुक्त_coherent(&bp->pdev.dev, MAX_FRAME_SIZE,
				  bp->LocalRxBuffer, bp->LocalRxBufferDMA);
		bp->LocalRxBuffer = शून्य;
	पूर्ण
	वापस err;
पूर्ण				// skfp_driver_init


/*
 * =============
 * = skfp_खोलो =
 * =============
 *   
 * Overview:
 *   Opens the adapter
 *  
 * Returns:
 *   Condition code
 *       
 * Arguments:
 *   dev - poपूर्णांकer to device inक्रमmation
 *
 * Functional Description:
 *   This function brings the adapter to an operational state.
 *
 * Return Codes:
 *   0           - Adapter was successfully खोलोed
 *   -EAGAIN - Could not रेजिस्टर IRQ
 */
अटल पूर्णांक skfp_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा s_smc *smc = netdev_priv(dev);
	पूर्णांक err;

	pr_debug("entering skfp_open\n");
	/* Register IRQ - support shared पूर्णांकerrupts by passing device ptr */
	err = request_irq(dev->irq, skfp_पूर्णांकerrupt, IRQF_SHARED,
			  dev->name, dev);
	अगर (err)
		वापस err;

	/*
	 * Set current address to factory MAC address
	 *
	 * Note: We've alपढ़ोy करोne this step in skfp_driver_init.
	 *       However, it's possible that a user has set a node
	 *               address override, then बंदd and reखोलोed the
	 *               adapter.  Unless we reset the device address field
	 *               now, we'll जारी to use the existing modअगरied
	 *               address.
	 */
	पढ़ो_address(smc, शून्य);
	स_नकल(dev->dev_addr, smc->hw.fddi_canon_addr.a, ETH_ALEN);

	init_smt(smc, शून्य);
	smt_online(smc, 1);
	STI_FBI();

	/* Clear local multicast address tables */
	mac_clear_multicast(smc);

	/* Disable promiscuous filter settings */
	mac_drv_rx_mode(smc, RX_DISABLE_PROMISC);

	netअगर_start_queue(dev);
	वापस 0;
पूर्ण				// skfp_खोलो


/*
 * ==============
 * = skfp_बंद =
 * ==============
 *   
 * Overview:
 *   Closes the device/module.
 *  
 * Returns:
 *   Condition code
 *       
 * Arguments:
 *   dev - poपूर्णांकer to device inक्रमmation
 *
 * Functional Description:
 *   This routine बंदs the adapter and brings it to a safe state.
 *   The पूर्णांकerrupt service routine is deरेजिस्टरed with the OS.
 *   The adapter can be खोलोed again with another call to skfp_खोलो().
 *
 * Return Codes:
 *   Always वापस 0.
 *
 * Assumptions:
 *   No further requests क्रम this adapter are made after this routine is
 *   called.  skfp_खोलो() can be called to reset and reinitialize the
 *   adapter.
 */
अटल पूर्णांक skfp_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा s_smc *smc = netdev_priv(dev);
	skfddi_priv *bp = &smc->os;

	CLI_FBI();
	smt_reset_शेषs(smc, 1);
	card_stop(smc);
	mac_drv_clear_tx_queue(smc);
	mac_drv_clear_rx_queue(smc);

	netअगर_stop_queue(dev);
	/* Deरेजिस्टर (मुक्त) IRQ */
	मुक्त_irq(dev->irq, dev);

	skb_queue_purge(&bp->SendSkbQueue);
	bp->QueueSkb = MAX_TX_QUEUE_LEN;

	वापस 0;
पूर्ण				// skfp_बंद


/*
 * ==================
 * = skfp_पूर्णांकerrupt =
 * ==================
 *   
 * Overview:
 *   Interrupt processing routine
 *  
 * Returns:
 *   None
 *       
 * Arguments:
 *   irq        - पूर्णांकerrupt vector
 *   dev_id     - poपूर्णांकer to device inक्रमmation
 *
 * Functional Description:
 *   This routine calls the पूर्णांकerrupt processing routine क्रम this adapter.  It
 *   disables and reenables adapter पूर्णांकerrupts, as appropriate.  We can support
 *   shared पूर्णांकerrupts since the incoming dev_id poपूर्णांकer provides our device
 *   काष्ठाure context. All the real work is करोne in the hardware module.
 *
 * Return Codes:
 *   None
 *
 * Assumptions:
 *   The पूर्णांकerrupt acknowledgement at the hardware level (eg. ACKing the PIC
 *   on Intel-based प्रणालीs) is करोne by the operating प्रणाली outside this
 *   routine.
 *
 *       System पूर्णांकerrupts are enabled through this call.
 *
 * Side Effects:
 *   Interrupts are disabled, then reenabled at the adapter.
 */

अटल irqवापस_t skfp_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा s_smc *smc;	/* निजी board काष्ठाure poपूर्णांकer */
	skfddi_priv *bp;

	smc = netdev_priv(dev);
	bp = &smc->os;

	// IRQs enabled or disabled ?
	अगर (inpd(ADDR(B0_IMSK)) == 0) अणु
		// IRQs are disabled: must be shared पूर्णांकerrupt
		वापस IRQ_NONE;
	पूर्ण
	// Note: At this poपूर्णांक, IRQs are enabled.
	अगर ((inpd(ISR_A) & smc->hw.is_imask) == 0) अणु	// IRQ?
		// Adapter did not issue an IRQ: must be shared पूर्णांकerrupt
		वापस IRQ_NONE;
	पूर्ण
	CLI_FBI();		// Disable IRQs from our adapter.
	spin_lock(&bp->DriverLock);

	// Call पूर्णांकerrupt handler in hardware module (HWM).
	fddi_isr(smc);

	अगर (smc->os.ResetRequested) अणु
		ResetAdapter(smc);
		smc->os.ResetRequested = FALSE;
	पूर्ण
	spin_unlock(&bp->DriverLock);
	STI_FBI();		// Enable IRQs from our adapter.

	वापस IRQ_HANDLED;
पूर्ण				// skfp_पूर्णांकerrupt


/*
 * ======================
 * = skfp_ctl_get_stats =
 * ======================
 *   
 * Overview:
 *   Get statistics क्रम FDDI adapter
 *  
 * Returns:
 *   Poपूर्णांकer to FDDI statistics काष्ठाure
 *       
 * Arguments:
 *   dev - poपूर्णांकer to device inक्रमmation
 *
 * Functional Description:
 *   Gets current MIB objects from adapter, then
 *   वापसs FDDI statistics काष्ठाure as defined
 *   in अगर_fddi.h.
 *
 *   Note: Since the FDDI statistics काष्ठाure is
 *   still new and the device काष्ठाure करोesn't
 *   have an FDDI-specअगरic get statistics handler,
 *   we'll वापस the FDDI statistics काष्ठाure as
 *   a poपूर्णांकer to an Ethernet statistics काष्ठाure.
 *   That way, at least the first part of the statistics
 *   काष्ठाure can be decoded properly.
 *   We'll have to pay attention to this routine as the
 *   device काष्ठाure becomes more mature and LAN media
 *   independent.
 *
 */
अटल काष्ठा net_device_stats *skfp_ctl_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा s_smc *bp = netdev_priv(dev);

	/* Fill the bp->stats काष्ठाure with driver-मुख्यtained counters */

	bp->os.MacStat.port_bs_flag[0] = 0x1234;
	bp->os.MacStat.port_bs_flag[1] = 0x5678;
// goos: need to fill out fddi statistic
#अगर 0
	/* Get FDDI SMT MIB objects */

/* Fill the bp->stats काष्ठाure with the SMT MIB object values */

	स_नकल(bp->stats.smt_station_id, &bp->cmd_rsp_virt->smt_mib_get.smt_station_id, माप(bp->cmd_rsp_virt->smt_mib_get.smt_station_id));
	bp->stats.smt_op_version_id = bp->cmd_rsp_virt->smt_mib_get.smt_op_version_id;
	bp->stats.smt_hi_version_id = bp->cmd_rsp_virt->smt_mib_get.smt_hi_version_id;
	bp->stats.smt_lo_version_id = bp->cmd_rsp_virt->smt_mib_get.smt_lo_version_id;
	स_नकल(bp->stats.smt_user_data, &bp->cmd_rsp_virt->smt_mib_get.smt_user_data, माप(bp->cmd_rsp_virt->smt_mib_get.smt_user_data));
	bp->stats.smt_mib_version_id = bp->cmd_rsp_virt->smt_mib_get.smt_mib_version_id;
	bp->stats.smt_mac_cts = bp->cmd_rsp_virt->smt_mib_get.smt_mac_ct;
	bp->stats.smt_non_master_cts = bp->cmd_rsp_virt->smt_mib_get.smt_non_master_ct;
	bp->stats.smt_master_cts = bp->cmd_rsp_virt->smt_mib_get.smt_master_ct;
	bp->stats.smt_available_paths = bp->cmd_rsp_virt->smt_mib_get.smt_available_paths;
	bp->stats.smt_config_capabilities = bp->cmd_rsp_virt->smt_mib_get.smt_config_capabilities;
	bp->stats.smt_config_policy = bp->cmd_rsp_virt->smt_mib_get.smt_config_policy;
	bp->stats.smt_connection_policy = bp->cmd_rsp_virt->smt_mib_get.smt_connection_policy;
	bp->stats.smt_t_notअगरy = bp->cmd_rsp_virt->smt_mib_get.smt_t_notअगरy;
	bp->stats.smt_stat_rpt_policy = bp->cmd_rsp_virt->smt_mib_get.smt_stat_rpt_policy;
	bp->stats.smt_trace_max_expiration = bp->cmd_rsp_virt->smt_mib_get.smt_trace_max_expiration;
	bp->stats.smt_bypass_present = bp->cmd_rsp_virt->smt_mib_get.smt_bypass_present;
	bp->stats.smt_ecm_state = bp->cmd_rsp_virt->smt_mib_get.smt_ecm_state;
	bp->stats.smt_cf_state = bp->cmd_rsp_virt->smt_mib_get.smt_cf_state;
	bp->stats.smt_remote_disconnect_flag = bp->cmd_rsp_virt->smt_mib_get.smt_remote_disconnect_flag;
	bp->stats.smt_station_status = bp->cmd_rsp_virt->smt_mib_get.smt_station_status;
	bp->stats.smt_peer_wrap_flag = bp->cmd_rsp_virt->smt_mib_get.smt_peer_wrap_flag;
	bp->stats.smt_समय_stamp = bp->cmd_rsp_virt->smt_mib_get.smt_msg_समय_stamp.ls;
	bp->stats.smt_transition_समय_stamp = bp->cmd_rsp_virt->smt_mib_get.smt_transition_समय_stamp.ls;
	bp->stats.mac_frame_status_functions = bp->cmd_rsp_virt->smt_mib_get.mac_frame_status_functions;
	bp->stats.mac_t_max_capability = bp->cmd_rsp_virt->smt_mib_get.mac_t_max_capability;
	bp->stats.mac_tvx_capability = bp->cmd_rsp_virt->smt_mib_get.mac_tvx_capability;
	bp->stats.mac_available_paths = bp->cmd_rsp_virt->smt_mib_get.mac_available_paths;
	bp->stats.mac_current_path = bp->cmd_rsp_virt->smt_mib_get.mac_current_path;
	स_नकल(bp->stats.mac_upstream_nbr, &bp->cmd_rsp_virt->smt_mib_get.mac_upstream_nbr, FDDI_K_ALEN);
	स_नकल(bp->stats.mac_करोwnstream_nbr, &bp->cmd_rsp_virt->smt_mib_get.mac_करोwnstream_nbr, FDDI_K_ALEN);
	स_नकल(bp->stats.mac_old_upstream_nbr, &bp->cmd_rsp_virt->smt_mib_get.mac_old_upstream_nbr, FDDI_K_ALEN);
	स_नकल(bp->stats.mac_old_करोwnstream_nbr, &bp->cmd_rsp_virt->smt_mib_get.mac_old_करोwnstream_nbr, FDDI_K_ALEN);
	bp->stats.mac_dup_address_test = bp->cmd_rsp_virt->smt_mib_get.mac_dup_address_test;
	bp->stats.mac_requested_paths = bp->cmd_rsp_virt->smt_mib_get.mac_requested_paths;
	bp->stats.mac_करोwnstream_port_type = bp->cmd_rsp_virt->smt_mib_get.mac_करोwnstream_port_type;
	स_नकल(bp->stats.mac_smt_address, &bp->cmd_rsp_virt->smt_mib_get.mac_smt_address, FDDI_K_ALEN);
	bp->stats.mac_t_req = bp->cmd_rsp_virt->smt_mib_get.mac_t_req;
	bp->stats.mac_t_neg = bp->cmd_rsp_virt->smt_mib_get.mac_t_neg;
	bp->stats.mac_t_max = bp->cmd_rsp_virt->smt_mib_get.mac_t_max;
	bp->stats.mac_tvx_value = bp->cmd_rsp_virt->smt_mib_get.mac_tvx_value;
	bp->stats.mac_frame_error_threshold = bp->cmd_rsp_virt->smt_mib_get.mac_frame_error_threshold;
	bp->stats.mac_frame_error_ratio = bp->cmd_rsp_virt->smt_mib_get.mac_frame_error_ratio;
	bp->stats.mac_rmt_state = bp->cmd_rsp_virt->smt_mib_get.mac_rmt_state;
	bp->stats.mac_da_flag = bp->cmd_rsp_virt->smt_mib_get.mac_da_flag;
	bp->stats.mac_una_da_flag = bp->cmd_rsp_virt->smt_mib_get.mac_unda_flag;
	bp->stats.mac_frame_error_flag = bp->cmd_rsp_virt->smt_mib_get.mac_frame_error_flag;
	bp->stats.mac_ma_unitdata_available = bp->cmd_rsp_virt->smt_mib_get.mac_ma_unitdata_available;
	bp->stats.mac_hardware_present = bp->cmd_rsp_virt->smt_mib_get.mac_hardware_present;
	bp->stats.mac_ma_unitdata_enable = bp->cmd_rsp_virt->smt_mib_get.mac_ma_unitdata_enable;
	bp->stats.path_tvx_lower_bound = bp->cmd_rsp_virt->smt_mib_get.path_tvx_lower_bound;
	bp->stats.path_t_max_lower_bound = bp->cmd_rsp_virt->smt_mib_get.path_t_max_lower_bound;
	bp->stats.path_max_t_req = bp->cmd_rsp_virt->smt_mib_get.path_max_t_req;
	स_नकल(bp->stats.path_configuration, &bp->cmd_rsp_virt->smt_mib_get.path_configuration, माप(bp->cmd_rsp_virt->smt_mib_get.path_configuration));
	bp->stats.port_my_type[0] = bp->cmd_rsp_virt->smt_mib_get.port_my_type[0];
	bp->stats.port_my_type[1] = bp->cmd_rsp_virt->smt_mib_get.port_my_type[1];
	bp->stats.port_neighbor_type[0] = bp->cmd_rsp_virt->smt_mib_get.port_neighbor_type[0];
	bp->stats.port_neighbor_type[1] = bp->cmd_rsp_virt->smt_mib_get.port_neighbor_type[1];
	bp->stats.port_connection_policies[0] = bp->cmd_rsp_virt->smt_mib_get.port_connection_policies[0];
	bp->stats.port_connection_policies[1] = bp->cmd_rsp_virt->smt_mib_get.port_connection_policies[1];
	bp->stats.port_mac_indicated[0] = bp->cmd_rsp_virt->smt_mib_get.port_mac_indicated[0];
	bp->stats.port_mac_indicated[1] = bp->cmd_rsp_virt->smt_mib_get.port_mac_indicated[1];
	bp->stats.port_current_path[0] = bp->cmd_rsp_virt->smt_mib_get.port_current_path[0];
	bp->stats.port_current_path[1] = bp->cmd_rsp_virt->smt_mib_get.port_current_path[1];
	स_नकल(&bp->stats.port_requested_paths[0 * 3], &bp->cmd_rsp_virt->smt_mib_get.port_requested_paths[0], 3);
	स_नकल(&bp->stats.port_requested_paths[1 * 3], &bp->cmd_rsp_virt->smt_mib_get.port_requested_paths[1], 3);
	bp->stats.port_mac_placement[0] = bp->cmd_rsp_virt->smt_mib_get.port_mac_placement[0];
	bp->stats.port_mac_placement[1] = bp->cmd_rsp_virt->smt_mib_get.port_mac_placement[1];
	bp->stats.port_available_paths[0] = bp->cmd_rsp_virt->smt_mib_get.port_available_paths[0];
	bp->stats.port_available_paths[1] = bp->cmd_rsp_virt->smt_mib_get.port_available_paths[1];
	bp->stats.port_pmd_class[0] = bp->cmd_rsp_virt->smt_mib_get.port_pmd_class[0];
	bp->stats.port_pmd_class[1] = bp->cmd_rsp_virt->smt_mib_get.port_pmd_class[1];
	bp->stats.port_connection_capabilities[0] = bp->cmd_rsp_virt->smt_mib_get.port_connection_capabilities[0];
	bp->stats.port_connection_capabilities[1] = bp->cmd_rsp_virt->smt_mib_get.port_connection_capabilities[1];
	bp->stats.port_bs_flag[0] = bp->cmd_rsp_virt->smt_mib_get.port_bs_flag[0];
	bp->stats.port_bs_flag[1] = bp->cmd_rsp_virt->smt_mib_get.port_bs_flag[1];
	bp->stats.port_ler_estimate[0] = bp->cmd_rsp_virt->smt_mib_get.port_ler_estimate[0];
	bp->stats.port_ler_estimate[1] = bp->cmd_rsp_virt->smt_mib_get.port_ler_estimate[1];
	bp->stats.port_ler_cutoff[0] = bp->cmd_rsp_virt->smt_mib_get.port_ler_cutoff[0];
	bp->stats.port_ler_cutoff[1] = bp->cmd_rsp_virt->smt_mib_get.port_ler_cutoff[1];
	bp->stats.port_ler_alarm[0] = bp->cmd_rsp_virt->smt_mib_get.port_ler_alarm[0];
	bp->stats.port_ler_alarm[1] = bp->cmd_rsp_virt->smt_mib_get.port_ler_alarm[1];
	bp->stats.port_connect_state[0] = bp->cmd_rsp_virt->smt_mib_get.port_connect_state[0];
	bp->stats.port_connect_state[1] = bp->cmd_rsp_virt->smt_mib_get.port_connect_state[1];
	bp->stats.port_pcm_state[0] = bp->cmd_rsp_virt->smt_mib_get.port_pcm_state[0];
	bp->stats.port_pcm_state[1] = bp->cmd_rsp_virt->smt_mib_get.port_pcm_state[1];
	bp->stats.port_pc_withhold[0] = bp->cmd_rsp_virt->smt_mib_get.port_pc_withhold[0];
	bp->stats.port_pc_withhold[1] = bp->cmd_rsp_virt->smt_mib_get.port_pc_withhold[1];
	bp->stats.port_ler_flag[0] = bp->cmd_rsp_virt->smt_mib_get.port_ler_flag[0];
	bp->stats.port_ler_flag[1] = bp->cmd_rsp_virt->smt_mib_get.port_ler_flag[1];
	bp->stats.port_hardware_present[0] = bp->cmd_rsp_virt->smt_mib_get.port_hardware_present[0];
	bp->stats.port_hardware_present[1] = bp->cmd_rsp_virt->smt_mib_get.port_hardware_present[1];


	/* Fill the bp->stats काष्ठाure with the FDDI counter values */

	bp->stats.mac_frame_cts = bp->cmd_rsp_virt->cntrs_get.cntrs.frame_cnt.ls;
	bp->stats.mac_copied_cts = bp->cmd_rsp_virt->cntrs_get.cntrs.copied_cnt.ls;
	bp->stats.mac_transmit_cts = bp->cmd_rsp_virt->cntrs_get.cntrs.transmit_cnt.ls;
	bp->stats.mac_error_cts = bp->cmd_rsp_virt->cntrs_get.cntrs.error_cnt.ls;
	bp->stats.mac_lost_cts = bp->cmd_rsp_virt->cntrs_get.cntrs.lost_cnt.ls;
	bp->stats.port_lct_fail_cts[0] = bp->cmd_rsp_virt->cntrs_get.cntrs.lct_rejects[0].ls;
	bp->stats.port_lct_fail_cts[1] = bp->cmd_rsp_virt->cntrs_get.cntrs.lct_rejects[1].ls;
	bp->stats.port_lem_reject_cts[0] = bp->cmd_rsp_virt->cntrs_get.cntrs.lem_rejects[0].ls;
	bp->stats.port_lem_reject_cts[1] = bp->cmd_rsp_virt->cntrs_get.cntrs.lem_rejects[1].ls;
	bp->stats.port_lem_cts[0] = bp->cmd_rsp_virt->cntrs_get.cntrs.link_errors[0].ls;
	bp->stats.port_lem_cts[1] = bp->cmd_rsp_virt->cntrs_get.cntrs.link_errors[1].ls;

#पूर्ण_अगर
	वापस (काष्ठा net_device_stats *)&bp->os.MacStat;
पूर्ण				// ctl_get_stat


/*
 * ==============================
 * = skfp_ctl_set_multicast_list =
 * ==============================
 *   
 * Overview:
 *   Enable/Disable LLC frame promiscuous mode reception
 *   on the adapter and/or update multicast address table.
 *  
 * Returns:
 *   None
 *       
 * Arguments:
 *   dev - poपूर्णांकer to device inक्रमmation
 *
 * Functional Description:
 *   This function acquires the driver lock and only calls
 *   skfp_ctl_set_multicast_list_wo_lock then.
 *   This routine follows a fairly simple algorithm क्रम setting the
 *   adapter filters and CAM:
 *
 *      अगर IFF_PROMISC flag is set
 *              enable promiscuous mode
 *      अन्यथा
 *              disable promiscuous mode
 *              अगर number of multicast addresses <= max. multicast number
 *                      add mc addresses to adapter table
 *              अन्यथा
 *                      enable promiscuous mode
 *              update adapter filters
 *
 * Assumptions:
 *   Multicast addresses are presented in canonical (LSB) क्रमmat.
 *
 * Side Effects:
 *   On-board adapter filters are updated.
 */
अटल व्योम skfp_ctl_set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा s_smc *smc = netdev_priv(dev);
	skfddi_priv *bp = &smc->os;
	अचिन्हित दीर्घ Flags;

	spin_lock_irqsave(&bp->DriverLock, Flags);
	skfp_ctl_set_multicast_list_wo_lock(dev);
	spin_unlock_irqrestore(&bp->DriverLock, Flags);
पूर्ण				// skfp_ctl_set_multicast_list



अटल व्योम skfp_ctl_set_multicast_list_wo_lock(काष्ठा net_device *dev)
अणु
	काष्ठा s_smc *smc = netdev_priv(dev);
	काष्ठा netdev_hw_addr *ha;

	/* Enable promiscuous mode, अगर necessary */
	अगर (dev->flags & IFF_PROMISC) अणु
		mac_drv_rx_mode(smc, RX_ENABLE_PROMISC);
		pr_debug("PROMISCUOUS MODE ENABLED\n");
	पूर्ण
	/* Else, update multicast address table */
	अन्यथा अणु
		mac_drv_rx_mode(smc, RX_DISABLE_PROMISC);
		pr_debug("PROMISCUOUS MODE DISABLED\n");

		// Reset all MC addresses
		mac_clear_multicast(smc);
		mac_drv_rx_mode(smc, RX_DISABLE_ALLMULTI);

		अगर (dev->flags & IFF_ALLMULTI) अणु
			mac_drv_rx_mode(smc, RX_ENABLE_ALLMULTI);
			pr_debug("ENABLE ALL MC ADDRESSES\n");
		पूर्ण अन्यथा अगर (!netdev_mc_empty(dev)) अणु
			अगर (netdev_mc_count(dev) <= FPMAX_MULTICAST) अणु
				/* use exact filtering */

				// poपूर्णांक to first multicast addr
				netdev_क्रम_each_mc_addr(ha, dev) अणु
					mac_add_multicast(smc,
						(काष्ठा fddi_addr *)ha->addr,
						1);

					pr_debug("ENABLE MC ADDRESS: %pMF\n",
						 ha->addr);
				पूर्ण

			पूर्ण अन्यथा अणु	// more MC addresses than HW supports

				mac_drv_rx_mode(smc, RX_ENABLE_ALLMULTI);
				pr_debug("ENABLE ALL MC ADDRESSES\n");
			पूर्ण
		पूर्ण अन्यथा अणु	// no MC addresses

			pr_debug("DISABLE ALL MC ADDRESSES\n");
		पूर्ण

		/* Update adapter filters */
		mac_update_multicast(smc);
	पूर्ण
पूर्ण				// skfp_ctl_set_multicast_list_wo_lock


/*
 * ===========================
 * = skfp_ctl_set_mac_address =
 * ===========================
 *   
 * Overview:
 *   set new mac address on adapter and update dev_addr field in device table.
 *  
 * Returns:
 *   None
 *       
 * Arguments:
 *   dev  - poपूर्णांकer to device inक्रमmation
 *   addr - poपूर्णांकer to sockaddr काष्ठाure containing unicast address to set
 *
 * Assumptions:
 *   The address poपूर्णांकed to by addr->sa_data is a valid unicast
 *   address and is presented in canonical (LSB) क्रमmat.
 */
अटल पूर्णांक skfp_ctl_set_mac_address(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा s_smc *smc = netdev_priv(dev);
	काष्ठा sockaddr *p_sockaddr = (काष्ठा sockaddr *) addr;
	skfddi_priv *bp = &smc->os;
	अचिन्हित दीर्घ Flags;


	स_नकल(dev->dev_addr, p_sockaddr->sa_data, FDDI_K_ALEN);
	spin_lock_irqsave(&bp->DriverLock, Flags);
	ResetAdapter(smc);
	spin_unlock_irqrestore(&bp->DriverLock, Flags);

	वापस 0;		/* always वापस zero */
पूर्ण				// skfp_ctl_set_mac_address


/*
 * ==============
 * = skfp_ioctl =
 * ==============
 *   
 * Overview:
 *
 * Perक्रमm IOCTL call functions here. Some are privileged operations and the
 * effective uid is checked in those हालs.
 *  
 * Returns:
 *   status value
 *   0 - success
 *   other - failure
 *       
 * Arguments:
 *   dev  - poपूर्णांकer to device inक्रमmation
 *   rq - poपूर्णांकer to ioctl request काष्ठाure
 *   cmd - ?
 *
 */


अटल पूर्णांक skfp_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा s_smc *smc = netdev_priv(dev);
	skfddi_priv *lp = &smc->os;
	काष्ठा s_skfp_ioctl ioc;
	पूर्णांक status = 0;

	अगर (copy_from_user(&ioc, rq->अगरr_data, माप(काष्ठा s_skfp_ioctl)))
		वापस -EFAULT;

	चयन (ioc.cmd) अणु
	हाल SKFP_GET_STATS:	/* Get the driver statistics */
		ioc.len = माप(lp->MacStat);
		status = copy_to_user(ioc.data, skfp_ctl_get_stats(dev), ioc.len)
				? -EFAULT : 0;
		अवरोध;
	हाल SKFP_CLR_STATS:	/* Zero out the driver statistics */
		अगर (!capable(CAP_NET_ADMIN)) अणु
			status = -EPERM;
		पूर्ण अन्यथा अणु
			स_रखो(&lp->MacStat, 0, माप(lp->MacStat));
		पूर्ण
		अवरोध;
	शेष:
		prपूर्णांकk("ioctl for %s: unknown cmd: %04x\n", dev->name, ioc.cmd);
		status = -EOPNOTSUPP;

	पूर्ण			// चयन

	वापस status;
पूर्ण				// skfp_ioctl


/*
 * =====================
 * = skfp_send_pkt     =
 * =====================
 *   
 * Overview:
 *   Queues a packet क्रम transmission and try to transmit it.
 *  
 * Returns:
 *   Condition code
 *       
 * Arguments:
 *   skb - poपूर्णांकer to sk_buff to queue क्रम transmission
 *   dev - poपूर्णांकer to device inक्रमmation
 *
 * Functional Description:
 *   Here we assume that an incoming skb transmit request
 *   is contained in a single physically contiguous buffer
 *   in which the भव address of the start of packet
 *   (skb->data) can be converted to a physical address
 *   by using pci_map_single().
 *
 *   We have an पूर्णांकernal queue क्रम packets we can not send 
 *   immediately. Packets in this queue can be given to the 
 *   adapter अगर transmit buffers are मुक्तd.
 *
 *   We can't free the skb until after it's been DMA'd
 *   out by the adapter, so we'll keep it in the driver and
 *   वापस it in mac_drv_tx_complete.
 *
 * Return Codes:
 *   0 - driver has queued and/or sent packet
 *       1 - caller should requeue the sk_buff क्रम later transmission
 *
 * Assumptions:
 *   The entire packet is stored in one physically
 *   contiguous buffer which is not cached and whose
 *   32-bit physical address can be determined.
 *
 *   It's vital that this routine is NOT reentered क्रम the
 *   same board and that the OS is not in another section of
 *   code (eg. skfp_पूर्णांकerrupt) क्रम the same board on a
 *   dअगरferent thपढ़ो.
 *
 * Side Effects:
 *   None
 */
अटल netdev_tx_t skfp_send_pkt(काष्ठा sk_buff *skb,
				       काष्ठा net_device *dev)
अणु
	काष्ठा s_smc *smc = netdev_priv(dev);
	skfddi_priv *bp = &smc->os;

	pr_debug("skfp_send_pkt\n");

	/*
	 * Verअगरy that incoming transmit request is OK
	 *
	 * Note: The packet size check is consistent with other
	 *               Linux device drivers, although the correct packet
	 *               size should be verअगरied beक्रमe calling the
	 *               transmit routine.
	 */

	अगर (!(skb->len >= FDDI_K_LLC_ZLEN && skb->len <= FDDI_K_LLC_LEN)) अणु
		bp->MacStat.gen.tx_errors++;	/* bump error counter */
		// dequeue packets from xmt queue and send them
		netअगर_start_queue(dev);
		dev_kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;	/* वापस "success" */
	पूर्ण
	अगर (bp->QueueSkb == 0) अणु	// वापस with tbusy set: queue full

		netअगर_stop_queue(dev);
		वापस NETDEV_TX_BUSY;
	पूर्ण
	bp->QueueSkb--;
	skb_queue_tail(&bp->SendSkbQueue, skb);
	send_queued_packets(netdev_priv(dev));
	अगर (bp->QueueSkb == 0) अणु
		netअगर_stop_queue(dev);
	पूर्ण
	वापस NETDEV_TX_OK;

पूर्ण				// skfp_send_pkt


/*
 * =======================
 * = send_queued_packets =
 * =======================
 *   
 * Overview:
 *   Send packets from the driver queue as दीर्घ as there are some and
 *   transmit resources are available.
 *  
 * Returns:
 *   None
 *       
 * Arguments:
 *   smc - poपूर्णांकer to smc (adapter) काष्ठाure
 *
 * Functional Description:
 *   Take a packet from queue अगर there is any. If not, then we are करोne.
 *   Check अगर there are resources to send the packet. If not, requeue it
 *   and निकास. 
 *   Set packet descriptor flags and give packet to adapter.
 *   Check अगर any send resources can be मुक्तd (we करो not use the
 *   transmit complete पूर्णांकerrupt).
 */
अटल व्योम send_queued_packets(काष्ठा s_smc *smc)
अणु
	skfddi_priv *bp = &smc->os;
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर fc;
	पूर्णांक queue;
	काष्ठा s_smt_fp_txd *txd;	// Current TxD.
	dma_addr_t dma_address;
	अचिन्हित दीर्घ Flags;

	पूर्णांक frame_status;	// HWM tx frame status.

	pr_debug("send queued packets\n");
	क्रम (;;) अणु
		// send first buffer from queue
		skb = skb_dequeue(&bp->SendSkbQueue);

		अगर (!skb) अणु
			pr_debug("queue empty\n");
			वापस;
		पूर्ण		// queue empty !

		spin_lock_irqsave(&bp->DriverLock, Flags);
		fc = skb->data[0];
		queue = (fc & FC_SYNC_BIT) ? QUEUE_S : QUEUE_A0;
#अगर_घोषित ESS
		// Check अगर the frame may/must be sent as a synchronous frame.

		अगर ((fc & ~(FC_SYNC_BIT | FC_LLC_PRIOR)) == FC_ASYNC_LLC) अणु
			// It's an LLC frame.
			अगर (!smc->ess.sync_bw_available)
				fc &= ~FC_SYNC_BIT; // No bandwidth available.

			अन्यथा अणु	// Bandwidth is available.

				अगर (smc->mib.fddiESSSynchTxMode) अणु
					// Send as sync. frame.
					fc |= FC_SYNC_BIT;
				पूर्ण
			पूर्ण
		पूर्ण
#पूर्ण_अगर				// ESS
		frame_status = hwm_tx_init(smc, fc, 1, skb->len, queue);

		अगर ((frame_status & (LOC_TX | LAN_TX)) == 0) अणु
			// Unable to send the frame.

			अगर ((frame_status & RING_DOWN) != 0) अणु
				// Ring is करोwn.
				pr_debug("Tx attempt while ring down.\n");
			पूर्ण अन्यथा अगर ((frame_status & OUT_OF_TXD) != 0) अणु
				pr_debug("%s: out of TXDs.\n", bp->dev->name);
			पूर्ण अन्यथा अणु
				pr_debug("%s: out of transmit resources",
					bp->dev->name);
			पूर्ण

			// Note: We will retry the operation as soon as
			// transmit resources become available.
			skb_queue_head(&bp->SendSkbQueue, skb);
			spin_unlock_irqrestore(&bp->DriverLock, Flags);
			वापस;	// Packet has been queued.

		पूर्ण		// अगर (unable to send frame)

		bp->QueueSkb++;	// one packet less in local queue

		// source address in packet ?
		CheckSourceAddress(skb->data, smc->hw.fddi_canon_addr.a);

		txd = (काष्ठा s_smt_fp_txd *) HWM_GET_CURR_TXD(smc, queue);

		dma_address = pci_map_single(&bp->pdev, skb->data,
					     skb->len, PCI_DMA_TODEVICE);
		अगर (frame_status & LAN_TX) अणु
			txd->txd_os.skb = skb;			// save skb
			txd->txd_os.dma_addr = dma_address;	// save dma mapping
		पूर्ण
		hwm_tx_frag(smc, skb->data, dma_address, skb->len,
                      frame_status | FIRST_FRAG | LAST_FRAG | EN_IRQ_खातापूर्ण);

		अगर (!(frame_status & LAN_TX)) अणु		// local only frame
			pci_unmap_single(&bp->pdev, dma_address,
					 skb->len, PCI_DMA_TODEVICE);
			dev_kमुक्त_skb_irq(skb);
		पूर्ण
		spin_unlock_irqrestore(&bp->DriverLock, Flags);
	पूर्ण			// क्रम

	वापस;			// never reached

पूर्ण				// send_queued_packets


/************************
 * 
 * CheckSourceAddress
 *
 * Verअगरy अगर the source address is set. Insert it अगर necessary.
 *
 ************************/
अटल व्योम CheckSourceAddress(अचिन्हित अक्षर *frame, अचिन्हित अक्षर *hw_addr)
अणु
	अचिन्हित अक्षर SRBit;

	अगर ((((अचिन्हित दीर्घ) frame[1 + 6]) & ~0x01) != 0) // source routing bit

		वापस;
	अगर ((अचिन्हित लघु) frame[1 + 10] != 0)
		वापस;
	SRBit = frame[1 + 6] & 0x01;
	स_नकल(&frame[1 + 6], hw_addr, ETH_ALEN);
	frame[8] |= SRBit;
पूर्ण				// CheckSourceAddress


/************************
 *
 *	ResetAdapter
 *
 *	Reset the adapter and bring it back to operational mode.
 * Args
 *	smc - A poपूर्णांकer to the SMT context काष्ठा.
 * Out
 *	Nothing.
 *
 ************************/
अटल व्योम ResetAdapter(काष्ठा s_smc *smc)
अणु

	pr_debug("[fddi: ResetAdapter]\n");

	// Stop the adapter.

	card_stop(smc);		// Stop all activity.

	// Clear the transmit and receive descriptor queues.
	mac_drv_clear_tx_queue(smc);
	mac_drv_clear_rx_queue(smc);

	// Restart the adapter.

	smt_reset_शेषs(smc, 1);	// Initialize the SMT module.

	init_smt(smc, (smc->os.dev)->dev_addr);	// Initialize the hardware.

	smt_online(smc, 1);	// Insert पूर्णांकo the ring again.
	STI_FBI();

	// Restore original receive mode (multicasts, promiscuous, etc.).
	skfp_ctl_set_multicast_list_wo_lock(smc->os.dev);
पूर्ण				// ResetAdapter


//--------------- functions called by hardware module ----------------

/************************
 *
 *	llc_restart_tx
 *
 *	The hardware driver calls this routine when the transmit complete
 *	पूर्णांकerrupt bits (end of frame) क्रम the synchronous or asynchronous
 *	queue is set.
 *
 * NOTE The hardware driver calls this function also अगर no packets are queued.
 *	The routine must be able to handle this हाल.
 * Args
 *	smc - A poपूर्णांकer to the SMT context काष्ठा.
 * Out
 *	Nothing.
 *
 ************************/
व्योम llc_restart_tx(काष्ठा s_smc *smc)
अणु
	skfddi_priv *bp = &smc->os;

	pr_debug("[llc_restart_tx]\n");

	// Try to send queued packets
	spin_unlock(&bp->DriverLock);
	send_queued_packets(smc);
	spin_lock(&bp->DriverLock);
	netअगर_start_queue(bp->dev);// प्रणाली may send again अगर it was blocked

पूर्ण				// llc_restart_tx


/************************
 *
 *	mac_drv_get_space
 *
 *	The hardware module calls this function to allocate the memory
 *	क्रम the SMT MBufs अगर the define MB_OUTSIDE_SMC is specअगरied.
 * Args
 *	smc - A poपूर्णांकer to the SMT context काष्ठा.
 *
 *	size - Size of memory in bytes to allocate.
 * Out
 *	!= 0	A poपूर्णांकer to the भव address of the allocated memory.
 *	== 0	Allocation error.
 *
 ************************/
व्योम *mac_drv_get_space(काष्ठा s_smc *smc, अचिन्हित पूर्णांक size)
अणु
	व्योम *virt;

	pr_debug("mac_drv_get_space (%d bytes), ", size);
	virt = (व्योम *) (smc->os.SharedMemAddr + smc->os.SharedMemHeap);

	अगर ((smc->os.SharedMemHeap + size) > smc->os.SharedMemSize) अणु
		prपूर्णांकk("Unexpected SMT memory size requested: %d\n", size);
		वापस शून्य;
	पूर्ण
	smc->os.SharedMemHeap += size;	// Move heap poपूर्णांकer.

	pr_debug("mac_drv_get_space end\n");
	pr_debug("virt addr: %lx\n", (uदीर्घ) virt);
	pr_debug("bus  addr: %lx\n", (uदीर्घ)
	       (smc->os.SharedMemDMA +
		((अक्षर *) virt - (अक्षर *)smc->os.SharedMemAddr)));
	वापस virt;
पूर्ण				// mac_drv_get_space


/************************
 *
 *	mac_drv_get_desc_mem
 *
 *	This function is called by the hardware dependent module.
 *	It allocates the memory क्रम the RxD and TxD descriptors.
 *
 *	This memory must be non-cached, non-movable and non-swappable.
 *	This memory should start at a physical page boundary.
 * Args
 *	smc - A poपूर्णांकer to the SMT context काष्ठा.
 *
 *	size - Size of memory in bytes to allocate.
 * Out
 *	!= 0	A poपूर्णांकer to the भव address of the allocated memory.
 *	== 0	Allocation error.
 *
 ************************/
व्योम *mac_drv_get_desc_mem(काष्ठा s_smc *smc, अचिन्हित पूर्णांक size)
अणु

	अक्षर *virt;

	pr_debug("mac_drv_get_desc_mem\n");

	// Descriptor memory must be aligned on 16-byte boundary.

	virt = mac_drv_get_space(smc, size);

	size = (u_पूर्णांक) (16 - (((अचिन्हित दीर्घ) virt) & 15UL));
	size = size % 16;

	pr_debug("Allocate %u bytes alignment gap ", size);
	pr_debug("for descriptor memory.\n");

	अगर (!mac_drv_get_space(smc, size)) अणु
		prपूर्णांकk("fddi: Unable to align descriptor memory.\n");
		वापस शून्य;
	पूर्ण
	वापस virt + size;
पूर्ण				// mac_drv_get_desc_mem


/************************
 *
 *	mac_drv_virt2phys
 *
 *	Get the physical address of a given भव address.
 * Args
 *	smc - A poपूर्णांकer to the SMT context काष्ठा.
 *
 *	virt - A (भव) poपूर्णांकer पूर्णांकo our 'shared' memory area.
 * Out
 *	Physical address of the given भव address.
 *
 ************************/
अचिन्हित दीर्घ mac_drv_virt2phys(काष्ठा s_smc *smc, व्योम *virt)
अणु
	वापस smc->os.SharedMemDMA +
		((अक्षर *) virt - (अक्षर *)smc->os.SharedMemAddr);
पूर्ण				// mac_drv_virt2phys


/************************
 *
 *	dma_master
 *
 *	The HWM calls this function, when the driver leads through a DMA
 *	transfer. If the OS-specअगरic module must prepare the प्रणाली hardware
 *	क्रम the DMA transfer, it should करो it in this function.
 *
 *	The hardware module calls this dma_master अगर it wants to send an SMT
 *	frame.  This means that the virt address passed in here is part of
 *      the 'shared' memory area.
 * Args
 *	smc - A poपूर्णांकer to the SMT context काष्ठा.
 *
 *	virt - The भव address of the data.
 *
 *	len - The length in bytes of the data.
 *
 *	flag - Indicates the transmit direction and the buffer type:
 *		DMA_RD	(0x01)	प्रणाली RAM ==> adapter buffer memory
 *		DMA_WR	(0x02)	adapter buffer memory ==> प्रणाली RAM
 *		SMT_BUF (0x80)	SMT buffer
 *
 *	>> NOTE: SMT_BUF and DMA_RD are always set क्रम PCI. <<
 * Out
 *	Returns the pyhsical address क्रम the DMA transfer.
 *
 ************************/
u_दीर्घ dma_master(काष्ठा s_smc * smc, व्योम *virt, पूर्णांक len, पूर्णांक flag)
अणु
	वापस smc->os.SharedMemDMA +
		((अक्षर *) virt - (अक्षर *)smc->os.SharedMemAddr);
पूर्ण				// dma_master


/************************
 *
 *	dma_complete
 *
 *	The hardware module calls this routine when it has completed a DMA
 *	transfer. If the operating प्रणाली dependent module has set up the DMA
 *	channel via dma_master() (e.g. Winकरोws NT or AIX) it should clean up
 *	the DMA channel.
 * Args
 *	smc - A poपूर्णांकer to the SMT context काष्ठा.
 *
 *	descr - A poपूर्णांकer to a TxD or RxD, respectively.
 *
 *	flag - Indicates the DMA transfer direction / SMT buffer:
 *		DMA_RD	(0x01)	प्रणाली RAM ==> adapter buffer memory
 *		DMA_WR	(0x02)	adapter buffer memory ==> प्रणाली RAM
 *		SMT_BUF (0x80)	SMT buffer (managed by HWM)
 * Out
 *	Nothing.
 *
 ************************/
व्योम dma_complete(काष्ठा s_smc *smc, अस्थिर जोड़ s_fp_descr *descr, पूर्णांक flag)
अणु
	/* For TX buffers, there are two हालs.  If it is an SMT transmit
	 * buffer, there is nothing to करो since we use consistent memory
	 * क्रम the 'shared' memory area.  The other हाल is क्रम normal
	 * transmit packets given to us by the networking stack, and in
	 * that हाल we cleanup the PCI DMA mapping in mac_drv_tx_complete
	 * below.
	 *
	 * For RX buffers, we have to unmap dynamic PCI DMA mappings here
	 * because the hardware module is about to potentially look at
	 * the contents of the buffer.  If we did not call the PCI DMA
	 * unmap first, the hardware module could पढ़ो inconsistent data.
	 */
	अगर (flag & DMA_WR) अणु
		skfddi_priv *bp = &smc->os;
		अस्थिर काष्ठा s_smt_fp_rxd *r = &descr->r;

		/* If SKB is शून्य, we used the local buffer. */
		अगर (r->rxd_os.skb && r->rxd_os.dma_addr) अणु
			पूर्णांक MaxFrameSize = bp->MaxFrameSize;

			pci_unmap_single(&bp->pdev, r->rxd_os.dma_addr,
					 MaxFrameSize, PCI_DMA_FROMDEVICE);
			r->rxd_os.dma_addr = 0;
		पूर्ण
	पूर्ण
पूर्ण				// dma_complete


/************************
 *
 *	mac_drv_tx_complete
 *
 *	Transmit of a packet is complete. Release the tx staging buffer.
 *
 * Args
 *	smc - A poपूर्णांकer to the SMT context काष्ठा.
 *
 *	txd - A poपूर्णांकer to the last TxD which is used by the frame.
 * Out
 *	Returns nothing.
 *
 ************************/
व्योम mac_drv_tx_complete(काष्ठा s_smc *smc, अस्थिर काष्ठा s_smt_fp_txd *txd)
अणु
	काष्ठा sk_buff *skb;

	pr_debug("entering mac_drv_tx_complete\n");
	// Check अगर this TxD poपूर्णांकs to a skb

	अगर (!(skb = txd->txd_os.skb)) अणु
		pr_debug("TXD with no skb assigned.\n");
		वापस;
	पूर्ण
	txd->txd_os.skb = शून्य;

	// release the DMA mapping
	pci_unmap_single(&smc->os.pdev, txd->txd_os.dma_addr,
			 skb->len, PCI_DMA_TODEVICE);
	txd->txd_os.dma_addr = 0;

	smc->os.MacStat.gen.tx_packets++;	// Count transmitted packets.
	smc->os.MacStat.gen.tx_bytes+=skb->len;	// Count bytes

	// मुक्त the skb
	dev_kमुक्त_skb_irq(skb);

	pr_debug("leaving mac_drv_tx_complete\n");
पूर्ण				// mac_drv_tx_complete


/************************
 *
 * dump packets to logfile
 *
 ************************/
#अगर_घोषित DUMPPACKETS
व्योम dump_data(अचिन्हित अक्षर *Data, पूर्णांक length)
अणु
	prपूर्णांकk(KERN_INFO "---Packet start---\n");
	prपूर्णांक_hex_dump(KERN_INFO, "", DUMP_PREFIX_NONE, 16, 1, Data, min_t(माप_प्रकार, length, 64), false);
	prपूर्णांकk(KERN_INFO "------------------\n");
पूर्ण				// dump_data
#अन्यथा
#घोषणा dump_data(data,len)
#पूर्ण_अगर				// DUMPPACKETS

/************************
 *
 *	mac_drv_rx_complete
 *
 *	The hardware module calls this function अगर an LLC frame is received
 *	in a receive buffer. Also the SMT, NSA, and directed beacon frames
 *	from the network will be passed to the LLC layer by this function
 *	अगर passing is enabled.
 *
 *	mac_drv_rx_complete क्रमwards the frame to the LLC layer अगर it should
 *	be received. It also fills the RxD ring with new receive buffers अगर
 *	some can be queued.
 * Args
 *	smc - A poपूर्णांकer to the SMT context काष्ठा.
 *
 *	rxd - A poपूर्णांकer to the first RxD which is used by the receive frame.
 *
 *	frag_count - Count of RxDs used by the received frame.
 *
 *	len - Frame length.
 * Out
 *	Nothing.
 *
 ************************/
व्योम mac_drv_rx_complete(काष्ठा s_smc *smc, अस्थिर काष्ठा s_smt_fp_rxd *rxd,
			 पूर्णांक frag_count, पूर्णांक len)
अणु
	skfddi_priv *bp = &smc->os;
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर *virt, *cp;
	अचिन्हित लघु ri;
	u_पूर्णांक RअगरLength;

	pr_debug("entering mac_drv_rx_complete (len=%d)\n", len);
	अगर (frag_count != 1) अणु	// This is not allowed to happen.

		prपूर्णांकk("fddi: Multi-fragment receive!\n");
		जाओ RequeueRxd;	// Re-use the given RXD(s).

	पूर्ण
	skb = rxd->rxd_os.skb;
	अगर (!skb) अणु
		pr_debug("No skb in rxd\n");
		smc->os.MacStat.gen.rx_errors++;
		जाओ RequeueRxd;
	पूर्ण
	virt = skb->data;

	// The DMA mapping was released in dma_complete above.

	dump_data(skb->data, len);

	/*
	 * FDDI Frame क्रमmat:
	 * +-------+-------+-------+------------+--------+------------+
	 * | FC[1] | DA[6] | SA[6] | RIF[0..18] | LLC[3] | Data[0..n] |
	 * +-------+-------+-------+------------+--------+------------+
	 *
	 * FC = Frame Control
	 * DA = Destination Address
	 * SA = Source Address
	 * RIF = Routing Inक्रमmation Field
	 * LLC = Logical Link Control
	 */

	// Remove Routing Inक्रमmation Field (RIF), अगर present.

	अगर ((virt[1 + 6] & FDDI_RII) == 0)
		RअगरLength = 0;
	अन्यथा अणु
		पूर्णांक n;
// goos: RIF removal has still to be tested
		pr_debug("RIF found\n");
		// Get RIF length from Routing Control (RC) field.
		cp = virt + FDDI_MAC_HDR_LEN;	// Poपूर्णांक behind MAC header.

		ri = ntohs(*((__be16 *) cp));
		RअगरLength = ri & FDDI_RCF_LEN_MASK;
		अगर (len < (पूर्णांक) (FDDI_MAC_HDR_LEN + RअगरLength)) अणु
			prपूर्णांकk("fddi: Invalid RIF.\n");
			जाओ RequeueRxd;	// Discard the frame.

		पूर्ण
		virt[1 + 6] &= ~FDDI_RII;	// Clear RII bit.
		// regions overlap

		virt = cp + RअगरLength;
		क्रम (n = FDDI_MAC_HDR_LEN; n; n--)
			*--virt = *--cp;
		// adjust sbd->data poपूर्णांकer
		skb_pull(skb, RअगरLength);
		len -= RअगरLength;
		RअगरLength = 0;
	पूर्ण

	// Count statistics.
	smc->os.MacStat.gen.rx_packets++;	// Count indicated receive
						// packets.
	smc->os.MacStat.gen.rx_bytes+=len;	// Count bytes.

	// virt poपूर्णांकs to header again
	अगर (virt[1] & 0x01) अणु	// Check group (multicast) bit.

		smc->os.MacStat.gen.multicast++;
	पूर्ण

	// deliver frame to प्रणाली
	rxd->rxd_os.skb = शून्य;
	skb_trim(skb, len);
	skb->protocol = fddi_type_trans(skb, bp->dev);

	netअगर_rx(skb);

	HWM_RX_CHECK(smc, RX_LOW_WATERMARK);
	वापस;

      RequeueRxd:
	pr_debug("Rx: re-queue RXD.\n");
	mac_drv_requeue_rxd(smc, rxd, frag_count);
	smc->os.MacStat.gen.rx_errors++;	// Count receive packets
						// not indicated.

पूर्ण				// mac_drv_rx_complete


/************************
 *
 *	mac_drv_requeue_rxd
 *
 *	The hardware module calls this function to request the OS-specअगरic
 *	module to queue the receive buffer(s) represented by the poपूर्णांकer
 *	to the RxD and the frag_count पूर्णांकo the receive queue again. This
 *	buffer was filled with an invalid frame or an SMT frame.
 * Args
 *	smc - A poपूर्णांकer to the SMT context काष्ठा.
 *
 *	rxd - A poपूर्णांकer to the first RxD which is used by the receive frame.
 *
 *	frag_count - Count of RxDs used by the received frame.
 * Out
 *	Nothing.
 *
 ************************/
व्योम mac_drv_requeue_rxd(काष्ठा s_smc *smc, अस्थिर काष्ठा s_smt_fp_rxd *rxd,
			 पूर्णांक frag_count)
अणु
	अस्थिर काष्ठा s_smt_fp_rxd *next_rxd;
	अस्थिर काष्ठा s_smt_fp_rxd *src_rxd;
	काष्ठा sk_buff *skb;
	पूर्णांक MaxFrameSize;
	अचिन्हित अक्षर *v_addr;
	dma_addr_t b_addr;

	अगर (frag_count != 1)	// This is not allowed to happen.

		prपूर्णांकk("fddi: Multi-fragment requeue!\n");

	MaxFrameSize = smc->os.MaxFrameSize;
	src_rxd = rxd;
	क्रम (; frag_count > 0; frag_count--) अणु
		next_rxd = src_rxd->rxd_next;
		rxd = HWM_GET_CURR_RXD(smc);

		skb = src_rxd->rxd_os.skb;
		अगर (skb == शून्य) अणु	// this should not happen

			pr_debug("Requeue with no skb in rxd!\n");
			skb = alloc_skb(MaxFrameSize + 3, GFP_ATOMIC);
			अगर (skb) अणु
				// we got a skb
				rxd->rxd_os.skb = skb;
				skb_reserve(skb, 3);
				skb_put(skb, MaxFrameSize);
				v_addr = skb->data;
				b_addr = pci_map_single(&smc->os.pdev,
							v_addr,
							MaxFrameSize,
							PCI_DMA_FROMDEVICE);
				rxd->rxd_os.dma_addr = b_addr;
			पूर्ण अन्यथा अणु
				// no skb available, use local buffer
				pr_debug("Queueing invalid buffer!\n");
				rxd->rxd_os.skb = शून्य;
				v_addr = smc->os.LocalRxBuffer;
				b_addr = smc->os.LocalRxBufferDMA;
			पूर्ण
		पूर्ण अन्यथा अणु
			// we use skb from old rxd
			rxd->rxd_os.skb = skb;
			v_addr = skb->data;
			b_addr = pci_map_single(&smc->os.pdev,
						v_addr,
						MaxFrameSize,
						PCI_DMA_FROMDEVICE);
			rxd->rxd_os.dma_addr = b_addr;
		पूर्ण
		hwm_rx_frag(smc, v_addr, b_addr, MaxFrameSize,
			    FIRST_FRAG | LAST_FRAG);

		src_rxd = next_rxd;
	पूर्ण
पूर्ण				// mac_drv_requeue_rxd


/************************
 *
 *	mac_drv_fill_rxd
 *
 *	The hardware module calls this function at initialization समय
 *	to fill the RxD ring with receive buffers. It is also called by
 *	mac_drv_rx_complete अगर rx_मुक्त is large enough to queue some new
 *	receive buffers पूर्णांकo the RxD ring. mac_drv_fill_rxd queues new
 *	receive buffers as दीर्घ as enough RxDs and receive buffers are
 *	available.
 * Args
 *	smc - A poपूर्णांकer to the SMT context काष्ठा.
 * Out
 *	Nothing.
 *
 ************************/
व्योम mac_drv_fill_rxd(काष्ठा s_smc *smc)
अणु
	पूर्णांक MaxFrameSize;
	अचिन्हित अक्षर *v_addr;
	अचिन्हित दीर्घ b_addr;
	काष्ठा sk_buff *skb;
	अस्थिर काष्ठा s_smt_fp_rxd *rxd;

	pr_debug("entering mac_drv_fill_rxd\n");

	// Walk through the list of मुक्त receive buffers, passing receive
	// buffers to the HWM as दीर्घ as RXDs are available.

	MaxFrameSize = smc->os.MaxFrameSize;
	// Check अगर there is any RXD left.
	जबतक (HWM_GET_RX_FREE(smc) > 0) अणु
		pr_debug(".\n");

		rxd = HWM_GET_CURR_RXD(smc);
		skb = alloc_skb(MaxFrameSize + 3, GFP_ATOMIC);
		अगर (skb) अणु
			// we got a skb
			skb_reserve(skb, 3);
			skb_put(skb, MaxFrameSize);
			v_addr = skb->data;
			b_addr = pci_map_single(&smc->os.pdev,
						v_addr,
						MaxFrameSize,
						PCI_DMA_FROMDEVICE);
			rxd->rxd_os.dma_addr = b_addr;
		पूर्ण अन्यथा अणु
			// no skb available, use local buffer
			// System has run out of buffer memory, but we want to
			// keep the receiver running in hope of better बार.
			// Multiple descriptors may poपूर्णांक to this local buffer,
			// so data in it must be considered invalid.
			pr_debug("Queueing invalid buffer!\n");
			v_addr = smc->os.LocalRxBuffer;
			b_addr = smc->os.LocalRxBufferDMA;
		पूर्ण

		rxd->rxd_os.skb = skb;

		// Pass receive buffer to HWM.
		hwm_rx_frag(smc, v_addr, b_addr, MaxFrameSize,
			    FIRST_FRAG | LAST_FRAG);
	पूर्ण
	pr_debug("leaving mac_drv_fill_rxd\n");
पूर्ण				// mac_drv_fill_rxd


/************************
 *
 *	mac_drv_clear_rxd
 *
 *	The hardware module calls this function to release unused
 *	receive buffers.
 * Args
 *	smc - A poपूर्णांकer to the SMT context काष्ठा.
 *
 *	rxd - A poपूर्णांकer to the first RxD which is used by the receive buffer.
 *
 *	frag_count - Count of RxDs used by the receive buffer.
 * Out
 *	Nothing.
 *
 ************************/
व्योम mac_drv_clear_rxd(काष्ठा s_smc *smc, अस्थिर काष्ठा s_smt_fp_rxd *rxd,
		       पूर्णांक frag_count)
अणु

	काष्ठा sk_buff *skb;

	pr_debug("entering mac_drv_clear_rxd\n");

	अगर (frag_count != 1)	// This is not allowed to happen.

		prपूर्णांकk("fddi: Multi-fragment clear!\n");

	क्रम (; frag_count > 0; frag_count--) अणु
		skb = rxd->rxd_os.skb;
		अगर (skb != शून्य) अणु
			skfddi_priv *bp = &smc->os;
			पूर्णांक MaxFrameSize = bp->MaxFrameSize;

			pci_unmap_single(&bp->pdev, rxd->rxd_os.dma_addr,
					 MaxFrameSize, PCI_DMA_FROMDEVICE);

			dev_kमुक्त_skb(skb);
			rxd->rxd_os.skb = शून्य;
		पूर्ण
		rxd = rxd->rxd_next;	// Next RXD.

	पूर्ण
पूर्ण				// mac_drv_clear_rxd


/************************
 *
 *	mac_drv_rx_init
 *
 *	The hardware module calls this routine when an SMT or NSA frame of the
 *	local SMT should be delivered to the LLC layer.
 *
 *	It is necessary to have this function, because there is no other way to
 *	copy the contents of SMT MBufs पूर्णांकo receive buffers.
 *
 *	mac_drv_rx_init allocates the required target memory क्रम this frame,
 *	and receives the frame fragment by fragment by calling mac_drv_rx_frag.
 * Args
 *	smc - A poपूर्णांकer to the SMT context काष्ठा.
 *
 *	len - The length (in bytes) of the received frame (FC, DA, SA, Data).
 *
 *	fc - The Frame Control field of the received frame.
 *
 *	look_ahead - A poपूर्णांकer to the lookahead data buffer (may be शून्य).
 *
 *	la_len - The length of the lookahead data stored in the lookahead
 *	buffer (may be zero).
 * Out
 *	Always वापसs zero (0).
 *
 ************************/
पूर्णांक mac_drv_rx_init(काष्ठा s_smc *smc, पूर्णांक len, पूर्णांक fc,
		    अक्षर *look_ahead, पूर्णांक la_len)
अणु
	काष्ठा sk_buff *skb;

	pr_debug("entering mac_drv_rx_init(len=%d)\n", len);

	// "Received" a SMT or NSA frame of the local SMT.

	अगर (len != la_len || len < FDDI_MAC_HDR_LEN || !look_ahead) अणु
		pr_debug("fddi: Discard invalid local SMT frame\n");
		pr_debug("  len=%d, la_len=%d, (ULONG) look_ahead=%08lXh.\n",
		       len, la_len, (अचिन्हित दीर्घ) look_ahead);
		वापस 0;
	पूर्ण
	skb = alloc_skb(len + 3, GFP_ATOMIC);
	अगर (!skb) अणु
		pr_debug("fddi: Local SMT: skb memory exhausted.\n");
		वापस 0;
	पूर्ण
	skb_reserve(skb, 3);
	skb_put(skb, len);
	skb_copy_to_linear_data(skb, look_ahead, len);

	// deliver frame to प्रणाली
	skb->protocol = fddi_type_trans(skb, smc->os.dev);
	netअगर_rx(skb);

	वापस 0;
पूर्ण				// mac_drv_rx_init


/************************
 *
 *	smt_समयr_poll
 *
 *	This routine is called periodically by the SMT module to clean up the
 *	driver.
 *
 *	Return any queued frames back to the upper protocol layers अगर the ring
 *	is करोwn.
 * Args
 *	smc - A poपूर्णांकer to the SMT context काष्ठा.
 * Out
 *	Nothing.
 *
 ************************/
व्योम smt_समयr_poll(काष्ठा s_smc *smc)
अणु
पूर्ण				// smt_समयr_poll


/************************
 *
 *	ring_status_indication
 *
 *	This function indicates a change of the ring state.
 * Args
 *	smc - A poपूर्णांकer to the SMT context काष्ठा.
 *
 *	status - The current ring status.
 * Out
 *	Nothing.
 *
 ************************/
व्योम ring_status_indication(काष्ठा s_smc *smc, u_दीर्घ status)
अणु
	pr_debug("ring_status_indication( ");
	अगर (status & RS_RES15)
		pr_debug("RS_RES15 ");
	अगर (status & RS_HARDERROR)
		pr_debug("RS_HARDERROR ");
	अगर (status & RS_SOFTERROR)
		pr_debug("RS_SOFTERROR ");
	अगर (status & RS_BEACON)
		pr_debug("RS_BEACON ");
	अगर (status & RS_PATHTEST)
		pr_debug("RS_PATHTEST ");
	अगर (status & RS_SELFTEST)
		pr_debug("RS_SELFTEST ");
	अगर (status & RS_RES9)
		pr_debug("RS_RES9 ");
	अगर (status & RS_DISCONNECT)
		pr_debug("RS_DISCONNECT ");
	अगर (status & RS_RES7)
		pr_debug("RS_RES7 ");
	अगर (status & RS_DUPADDR)
		pr_debug("RS_DUPADDR ");
	अगर (status & RS_NORINGOP)
		pr_debug("RS_NORINGOP ");
	अगर (status & RS_VERSION)
		pr_debug("RS_VERSION ");
	अगर (status & RS_STUCKBYPASSS)
		pr_debug("RS_STUCKBYPASSS ");
	अगर (status & RS_EVENT)
		pr_debug("RS_EVENT ");
	अगर (status & RS_RINGOPCHANGE)
		pr_debug("RS_RINGOPCHANGE ");
	अगर (status & RS_RES0)
		pr_debug("RS_RES0 ");
	pr_debug("]\n");
पूर्ण				// ring_status_indication


/************************
 *
 *	smt_get_समय
 *
 *	Gets the current समय from the प्रणाली.
 * Args
 *	None.
 * Out
 *	The current समय in TICKS_PER_SECOND.
 *
 *	TICKS_PER_SECOND has the unit 'count of timer ticks per second'. It is
 *	defined in "targetos.h". The definition of TICKS_PER_SECOND must comply
 *	to the समय वापसed by smt_get_समय().
 *
 ************************/
अचिन्हित दीर्घ smt_get_समय(व्योम)
अणु
	वापस jअगरfies;
पूर्ण				// smt_get_समय


/************************
 *
 *	smt_stat_counter
 *
 *	Status counter update (ring_op, fअगरo full).
 * Args
 *	smc - A poपूर्णांकer to the SMT context काष्ठा.
 *
 *	stat -	= 0: A ring operational change occurred.
 *		= 1: The FORMAC FIFO buffer is full / FIFO overflow.
 * Out
 *	Nothing.
 *
 ************************/
व्योम smt_stat_counter(काष्ठा s_smc *smc, पूर्णांक stat)
अणु
//      BOOLEAN RingIsUp ;

	pr_debug("smt_stat_counter\n");
	चयन (stat) अणु
	हाल 0:
		pr_debug("Ring operational change.\n");
		अवरोध;
	हाल 1:
		pr_debug("Receive fifo overflow.\n");
		smc->os.MacStat.gen.rx_errors++;
		अवरोध;
	शेष:
		pr_debug("Unknown status (%d).\n", stat);
		अवरोध;
	पूर्ण
पूर्ण				// smt_stat_counter


/************************
 *
 *	cfm_state_change
 *
 *	Sets CFM state in custom statistics.
 * Args
 *	smc - A poपूर्णांकer to the SMT context काष्ठा.
 *
 *	c_state - Possible values are:
 *
 *		EC0_OUT, EC1_IN, EC2_TRACE, EC3_LEAVE, EC4_PATH_TEST,
 *		EC5_INSERT, EC6_CHECK, EC7_DEINSERT
 * Out
 *	Nothing.
 *
 ************************/
व्योम cfm_state_change(काष्ठा s_smc *smc, पूर्णांक c_state)
अणु
#अगर_घोषित DRIVERDEBUG
	अक्षर *s;

	चयन (c_state) अणु
	हाल SC0_ISOLATED:
		s = "SC0_ISOLATED";
		अवरोध;
	हाल SC1_WRAP_A:
		s = "SC1_WRAP_A";
		अवरोध;
	हाल SC2_WRAP_B:
		s = "SC2_WRAP_B";
		अवरोध;
	हाल SC4_THRU_A:
		s = "SC4_THRU_A";
		अवरोध;
	हाल SC5_THRU_B:
		s = "SC5_THRU_B";
		अवरोध;
	हाल SC7_WRAP_S:
		s = "SC7_WRAP_S";
		अवरोध;
	हाल SC9_C_WRAP_A:
		s = "SC9_C_WRAP_A";
		अवरोध;
	हाल SC10_C_WRAP_B:
		s = "SC10_C_WRAP_B";
		अवरोध;
	हाल SC11_C_WRAP_S:
		s = "SC11_C_WRAP_S";
		अवरोध;
	शेष:
		pr_debug("cfm_state_change: unknown %d\n", c_state);
		वापस;
	पूर्ण
	pr_debug("cfm_state_change: %s\n", s);
#पूर्ण_अगर				// DRIVERDEBUG
पूर्ण				// cfm_state_change


/************************
 *
 *	ecm_state_change
 *
 *	Sets ECM state in custom statistics.
 * Args
 *	smc - A poपूर्णांकer to the SMT context काष्ठा.
 *
 *	e_state - Possible values are:
 *
 *		SC0_ISOLATED, SC1_WRAP_A (5), SC2_WRAP_B (6), SC4_THRU_A (12),
 *		SC5_THRU_B (7), SC7_WRAP_S (8)
 * Out
 *	Nothing.
 *
 ************************/
व्योम ecm_state_change(काष्ठा s_smc *smc, पूर्णांक e_state)
अणु
#अगर_घोषित DRIVERDEBUG
	अक्षर *s;

	चयन (e_state) अणु
	हाल EC0_OUT:
		s = "EC0_OUT";
		अवरोध;
	हाल EC1_IN:
		s = "EC1_IN";
		अवरोध;
	हाल EC2_TRACE:
		s = "EC2_TRACE";
		अवरोध;
	हाल EC3_LEAVE:
		s = "EC3_LEAVE";
		अवरोध;
	हाल EC4_PATH_TEST:
		s = "EC4_PATH_TEST";
		अवरोध;
	हाल EC5_INSERT:
		s = "EC5_INSERT";
		अवरोध;
	हाल EC6_CHECK:
		s = "EC6_CHECK";
		अवरोध;
	हाल EC7_DEINSERT:
		s = "EC7_DEINSERT";
		अवरोध;
	शेष:
		s = "unknown";
		अवरोध;
	पूर्ण
	pr_debug("ecm_state_change: %s\n", s);
#पूर्ण_अगर				//DRIVERDEBUG
पूर्ण				// ecm_state_change


/************************
 *
 *	rmt_state_change
 *
 *	Sets RMT state in custom statistics.
 * Args
 *	smc - A poपूर्णांकer to the SMT context काष्ठा.
 *
 *	r_state - Possible values are:
 *
 *		RM0_ISOLATED, RM1_NON_OP, RM2_RING_OP, RM3_DETECT,
 *		RM4_NON_OP_DUP, RM5_RING_OP_DUP, RM6_सूचीECTED, RM7_TRACE
 * Out
 *	Nothing.
 *
 ************************/
व्योम rmt_state_change(काष्ठा s_smc *smc, पूर्णांक r_state)
अणु
#अगर_घोषित DRIVERDEBUG
	अक्षर *s;

	चयन (r_state) अणु
	हाल RM0_ISOLATED:
		s = "RM0_ISOLATED";
		अवरोध;
	हाल RM1_NON_OP:
		s = "RM1_NON_OP - not operational";
		अवरोध;
	हाल RM2_RING_OP:
		s = "RM2_RING_OP - ring operational";
		अवरोध;
	हाल RM3_DETECT:
		s = "RM3_DETECT - detect dupl addresses";
		अवरोध;
	हाल RM4_NON_OP_DUP:
		s = "RM4_NON_OP_DUP - dupl. addr detected";
		अवरोध;
	हाल RM5_RING_OP_DUP:
		s = "RM5_RING_OP_DUP - ring oper. with dupl. addr";
		अवरोध;
	हाल RM6_सूचीECTED:
		s = "RM6_DIRECTED - sending directed beacons";
		अवरोध;
	हाल RM7_TRACE:
		s = "RM7_TRACE - trace initiated";
		अवरोध;
	शेष:
		s = "unknown";
		अवरोध;
	पूर्ण
	pr_debug("[rmt_state_change: %s]\n", s);
#पूर्ण_अगर				// DRIVERDEBUG
पूर्ण				// rmt_state_change


/************************
 *
 *	drv_reset_indication
 *
 *	This function is called by the SMT when it has detected a severe
 *	hardware problem. The driver should perक्रमm a reset on the adapter
 *	as soon as possible, but not from within this function.
 * Args
 *	smc - A poपूर्णांकer to the SMT context काष्ठा.
 * Out
 *	Nothing.
 *
 ************************/
व्योम drv_reset_indication(काष्ठा s_smc *smc)
अणु
	pr_debug("entering drv_reset_indication\n");

	smc->os.ResetRequested = TRUE;	// Set flag.

पूर्ण				// drv_reset_indication

अटल काष्ठा pci_driver skfddi_pci_driver = अणु
	.name		= "skfddi",
	.id_table	= skfddi_pci_tbl,
	.probe		= skfp_init_one,
	.हटाओ		= skfp_हटाओ_one,
पूर्ण;

module_pci_driver(skfddi_pci_driver);
