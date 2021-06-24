<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * rrunner.c: Linux driver क्रम the Essential RoadRunner HIPPI board.
 *
 * Copyright (C) 1998-2002 by Jes Sorensen, <jes@wilकरोpensource.com>.
 *
 * Thanks to Essential Communication क्रम providing us with hardware
 * and very comprehensive करोcumentation without which I would not have
 * been able to ग_लिखो this driver. A special thank you to John Gibbon
 * क्रम sorting out the legal issues, with the NDA, allowing the code to
 * be released under the GPL.
 *
 * Thanks to Jayaram Bhat from ODS/Essential क्रम fixing some of the
 * stupid bugs in my code.
 *
 * Softnet support and various other patches from Val Henson of
 * ODS/Essential.
 *
 * PCI DMA mapping code partly based on work by Francois Romieu.
 */


#घोषणा DEBUG 1
#घोषणा RX_DMA_SKBUFF 1
#घोषणा PKT_COPY_THRESHOLD 512

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/hippidevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/delay.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <net/sock.h>

#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <linux/uaccess.h>

#घोषणा rr_अगर_busy(dev)     netअगर_queue_stopped(dev)
#घोषणा rr_अगर_running(dev)  netअगर_running(dev)

#समावेश "rrunner.h"

#घोषणा RUN_AT(x) (jअगरfies + (x))


MODULE_AUTHOR("Jes Sorensen <jes@wildopensource.com>");
MODULE_DESCRIPTION("Essential RoadRunner HIPPI driver");
MODULE_LICENSE("GPL");

अटल स्थिर अक्षर version[] =
"rrunner.c: v0.50 11/11/2002  Jes Sorensen (jes@wildopensource.com)\n";


अटल स्थिर काष्ठा net_device_ops rr_netdev_ops = अणु
	.nकरो_खोलो 		= rr_खोलो,
	.nकरो_stop		= rr_बंद,
	.nकरो_करो_ioctl		= rr_ioctl,
	.nकरो_start_xmit		= rr_start_xmit,
	.nकरो_set_mac_address	= hippi_mac_addr,
पूर्ण;

/*
 * Implementation notes:
 *
 * The DMA engine only allows क्रम DMA within physical 64KB chunks of
 * memory. The current approach of the driver (and stack) is to use
 * linear blocks of memory क्रम the skbuffs. However, as the data block
 * is always the first part of the skb and skbs are 2^n aligned so we
 * are guarantted to get the whole block within one 64KB align 64KB
 * chunk.
 *
 * On the दीर्घ term, relying on being able to allocate 64KB linear
 * chunks of memory is not feasible and the skb handling code and the
 * stack will need to know about I/O vectors or something similar.
 */

अटल पूर्णांक rr_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *dev;
	अटल पूर्णांक version_disp;
	u8 pci_latency;
	काष्ठा rr_निजी *rrpriv;
	व्योम *पंचांगpptr;
	dma_addr_t ring_dma;
	पूर्णांक ret = -ENOMEM;

	dev = alloc_hippi_dev(माप(काष्ठा rr_निजी));
	अगर (!dev)
		जाओ out3;

	ret = pci_enable_device(pdev);
	अगर (ret) अणु
		ret = -ENODEV;
		जाओ out2;
	पूर्ण

	rrpriv = netdev_priv(dev);

	SET_NETDEV_DEV(dev, &pdev->dev);

	ret = pci_request_regions(pdev, "rrunner");
	अगर (ret < 0)
		जाओ out;

	pci_set_drvdata(pdev, dev);

	rrpriv->pci_dev = pdev;

	spin_lock_init(&rrpriv->lock);

	dev->netdev_ops = &rr_netdev_ops;

	/* display version info अगर adapter is found */
	अगर (!version_disp) अणु
		/* set display flag to TRUE so that */
		/* we only display this string ONCE */
		version_disp = 1;
		prपूर्णांकk(version);
	पूर्ण

	pci_पढ़ो_config_byte(pdev, PCI_LATENCY_TIMER, &pci_latency);
	अगर (pci_latency <= 0x58)अणु
		pci_latency = 0x58;
		pci_ग_लिखो_config_byte(pdev, PCI_LATENCY_TIMER, pci_latency);
	पूर्ण

	pci_set_master(pdev);

	prपूर्णांकk(KERN_INFO "%s: Essential RoadRunner serial HIPPI "
	       "at 0x%llx, irq %i, PCI latency %i\n", dev->name,
	       (अचिन्हित दीर्घ दीर्घ)pci_resource_start(pdev, 0),
	       pdev->irq, pci_latency);

	/*
	 * Remap the MMIO regs पूर्णांकo kernel space.
	 */
	rrpriv->regs = pci_iomap(pdev, 0, 0x1000);
	अगर (!rrpriv->regs) अणु
		prपूर्णांकk(KERN_ERR "%s:  Unable to map I/O register, "
			"RoadRunner will be disabled.\n", dev->name);
		ret = -EIO;
		जाओ out;
	पूर्ण

	पंचांगpptr = dma_alloc_coherent(&pdev->dev, TX_TOTAL_SIZE, &ring_dma,
				    GFP_KERNEL);
	rrpriv->tx_ring = पंचांगpptr;
	rrpriv->tx_ring_dma = ring_dma;

	अगर (!पंचांगpptr) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	पंचांगpptr = dma_alloc_coherent(&pdev->dev, RX_TOTAL_SIZE, &ring_dma,
				    GFP_KERNEL);
	rrpriv->rx_ring = पंचांगpptr;
	rrpriv->rx_ring_dma = ring_dma;

	अगर (!पंचांगpptr) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	पंचांगpptr = dma_alloc_coherent(&pdev->dev, EVT_RING_SIZE, &ring_dma,
				    GFP_KERNEL);
	rrpriv->evt_ring = पंचांगpptr;
	rrpriv->evt_ring_dma = ring_dma;

	अगर (!पंचांगpptr) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/*
	 * Don't access any रेजिस्टर beक्रमe this poपूर्णांक!
	 */
#अगर_घोषित __BIG_ENDIAN
	ग_लिखोl(पढ़ोl(&rrpriv->regs->HostCtrl) | NO_SWAP,
		&rrpriv->regs->HostCtrl);
#पूर्ण_अगर
	/*
	 * Need to add a हाल क्रम little-endian 64-bit hosts here.
	 */

	rr_init(dev);

	ret = रेजिस्टर_netdev(dev);
	अगर (ret)
		जाओ out;
	वापस 0;

 out:
	अगर (rrpriv->evt_ring)
		dma_मुक्त_coherent(&pdev->dev, EVT_RING_SIZE, rrpriv->evt_ring,
				  rrpriv->evt_ring_dma);
	अगर (rrpriv->rx_ring)
		dma_मुक्त_coherent(&pdev->dev, RX_TOTAL_SIZE, rrpriv->rx_ring,
				  rrpriv->rx_ring_dma);
	अगर (rrpriv->tx_ring)
		dma_मुक्त_coherent(&pdev->dev, TX_TOTAL_SIZE, rrpriv->tx_ring,
				  rrpriv->tx_ring_dma);
	अगर (rrpriv->regs)
		pci_iounmap(pdev, rrpriv->regs);
	अगर (pdev)
		pci_release_regions(pdev);
 out2:
	मुक्त_netdev(dev);
 out3:
	वापस ret;
पूर्ण

अटल व्योम rr_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev);
	काष्ठा rr_निजी *rr = netdev_priv(dev);

	अगर (!(पढ़ोl(&rr->regs->HostCtrl) & NIC_HALTED)) अणु
		prपूर्णांकk(KERN_ERR "%s: trying to unload running NIC\n",
		       dev->name);
		ग_लिखोl(HALT_NIC, &rr->regs->HostCtrl);
	पूर्ण

	unरेजिस्टर_netdev(dev);
	dma_मुक्त_coherent(&pdev->dev, EVT_RING_SIZE, rr->evt_ring,
			  rr->evt_ring_dma);
	dma_मुक्त_coherent(&pdev->dev, RX_TOTAL_SIZE, rr->rx_ring,
			  rr->rx_ring_dma);
	dma_मुक्त_coherent(&pdev->dev, TX_TOTAL_SIZE, rr->tx_ring,
			  rr->tx_ring_dma);
	pci_iounmap(pdev, rr->regs);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	मुक्त_netdev(dev);
पूर्ण


/*
 * Commands are considered to be slow, thus there is no reason to
 * अंतरभूत this.
 */
अटल व्योम rr_issue_cmd(काष्ठा rr_निजी *rrpriv, काष्ठा cmd *cmd)
अणु
	काष्ठा rr_regs __iomem *regs;
	u32 idx;

	regs = rrpriv->regs;
	/*
	 * This is temporary - it will go away in the final version.
	 * We probably also want to make this function अंतरभूत.
	 */
	अगर (पढ़ोl(&regs->HostCtrl) & NIC_HALTED)अणु
		prपूर्णांकk("issuing command for halted NIC, code 0x%x, "
		       "HostCtrl %08x\n", cmd->code, पढ़ोl(&regs->HostCtrl));
		अगर (पढ़ोl(&regs->Mode) & FATAL_ERR)
			prपूर्णांकk("error codes Fail1 %02x, Fail2 %02x\n",
			       पढ़ोl(&regs->Fail1), पढ़ोl(&regs->Fail2));
	पूर्ण

	idx = rrpriv->info->cmd_ctrl.pi;

	ग_लिखोl(*(u32*)(cmd), &regs->CmdRing[idx]);
	wmb();

	idx = (idx - 1) % CMD_RING_ENTRIES;
	rrpriv->info->cmd_ctrl.pi = idx;
	wmb();

	अगर (पढ़ोl(&regs->Mode) & FATAL_ERR)
		prपूर्णांकk("error code %02x\n", पढ़ोl(&regs->Fail1));
पूर्ण


/*
 * Reset the board in a sensible manner. The NIC is alपढ़ोy halted
 * when we get here and a spin-lock is held.
 */
अटल पूर्णांक rr_reset(काष्ठा net_device *dev)
अणु
	काष्ठा rr_निजी *rrpriv;
	काष्ठा rr_regs __iomem *regs;
	u32 start_pc;
	पूर्णांक i;

	rrpriv = netdev_priv(dev);
	regs = rrpriv->regs;

	rr_load_firmware(dev);

	ग_लिखोl(0x01000000, &regs->TX_state);
	ग_लिखोl(0xff800000, &regs->RX_state);
	ग_लिखोl(0, &regs->AssistState);
	ग_लिखोl(CLEAR_INTA, &regs->LocalCtrl);
	ग_लिखोl(0x01, &regs->BrkPt);
	ग_लिखोl(0, &regs->Timer);
	ग_लिखोl(0, &regs->TimerRef);
	ग_लिखोl(RESET_DMA, &regs->DmaReadState);
	ग_लिखोl(RESET_DMA, &regs->DmaWriteState);
	ग_लिखोl(0, &regs->DmaWriteHostHi);
	ग_लिखोl(0, &regs->DmaWriteHostLo);
	ग_लिखोl(0, &regs->DmaReadHostHi);
	ग_लिखोl(0, &regs->DmaReadHostLo);
	ग_लिखोl(0, &regs->DmaReadLen);
	ग_लिखोl(0, &regs->DmaWriteLen);
	ग_लिखोl(0, &regs->DmaWriteLcl);
	ग_लिखोl(0, &regs->DmaWriteIPchecksum);
	ग_लिखोl(0, &regs->DmaReadLcl);
	ग_लिखोl(0, &regs->DmaReadIPchecksum);
	ग_लिखोl(0, &regs->PciState);
#अगर (BITS_PER_LONG == 64) && defined __LITTLE_ENDIAN
	ग_लिखोl(SWAP_DATA | PTR64BIT | PTR_WD_SWAP, &regs->Mode);
#या_अगर (BITS_PER_LONG == 64)
	ग_लिखोl(SWAP_DATA | PTR64BIT | PTR_WD_NOSWAP, &regs->Mode);
#अन्यथा
	ग_लिखोl(SWAP_DATA | PTR32BIT | PTR_WD_NOSWAP, &regs->Mode);
#पूर्ण_अगर

#अगर 0
	/*
	 * Don't worry, this is just black magic.
	 */
	ग_लिखोl(0xdf000, &regs->RxBase);
	ग_लिखोl(0xdf000, &regs->RxPrd);
	ग_लिखोl(0xdf000, &regs->RxCon);
	ग_लिखोl(0xce000, &regs->TxBase);
	ग_लिखोl(0xce000, &regs->TxPrd);
	ग_लिखोl(0xce000, &regs->TxCon);
	ग_लिखोl(0, &regs->RxIndPro);
	ग_लिखोl(0, &regs->RxIndCon);
	ग_लिखोl(0, &regs->RxIndRef);
	ग_लिखोl(0, &regs->TxIndPro);
	ग_लिखोl(0, &regs->TxIndCon);
	ग_लिखोl(0, &regs->TxIndRef);
	ग_लिखोl(0xcc000, &regs->pad10[0]);
	ग_लिखोl(0, &regs->DrCmndPro);
	ग_लिखोl(0, &regs->DrCmndCon);
	ग_लिखोl(0, &regs->DwCmndPro);
	ग_लिखोl(0, &regs->DwCmndCon);
	ग_लिखोl(0, &regs->DwCmndRef);
	ग_लिखोl(0, &regs->DrDataPro);
	ग_लिखोl(0, &regs->DrDataCon);
	ग_लिखोl(0, &regs->DrDataRef);
	ग_लिखोl(0, &regs->DwDataPro);
	ग_लिखोl(0, &regs->DwDataCon);
	ग_लिखोl(0, &regs->DwDataRef);
#पूर्ण_अगर

	ग_लिखोl(0xffffffff, &regs->MbEvent);
	ग_लिखोl(0, &regs->Event);

	ग_लिखोl(0, &regs->TxPi);
	ग_लिखोl(0, &regs->IpRxPi);

	ग_लिखोl(0, &regs->EvtCon);
	ग_लिखोl(0, &regs->EvtPrd);

	rrpriv->info->evt_ctrl.pi = 0;

	क्रम (i = 0; i < CMD_RING_ENTRIES; i++)
		ग_लिखोl(0, &regs->CmdRing[i]);

/*
 * Why 32 ? is this not cache line size dependent?
 */
	ग_लिखोl(RBURST_64|WBURST_64, &regs->PciState);
	wmb();

	start_pc = rr_पढ़ो_eeprom_word(rrpriv,
			दुरत्व(काष्ठा eeprom, rncd_info.FwStart));

#अगर (DEBUG > 1)
	prपूर्णांकk("%s: Executing firmware at address 0x%06x\n",
	       dev->name, start_pc);
#पूर्ण_अगर

	ग_लिखोl(start_pc + 0x800, &regs->Pc);
	wmb();
	udelay(5);

	ग_लिखोl(start_pc, &regs->Pc);
	wmb();

	वापस 0;
पूर्ण


/*
 * Read a string from the EEPROM.
 */
अटल अचिन्हित पूर्णांक rr_पढ़ो_eeprom(काष्ठा rr_निजी *rrpriv,
				अचिन्हित दीर्घ offset,
				अचिन्हित अक्षर *buf,
				अचिन्हित दीर्घ length)
अणु
	काष्ठा rr_regs __iomem *regs = rrpriv->regs;
	u32 misc, io, host, i;

	io = पढ़ोl(&regs->ExtIo);
	ग_लिखोl(0, &regs->ExtIo);
	misc = पढ़ोl(&regs->LocalCtrl);
	ग_लिखोl(0, &regs->LocalCtrl);
	host = पढ़ोl(&regs->HostCtrl);
	ग_लिखोl(host | HALT_NIC, &regs->HostCtrl);
	mb();

	क्रम (i = 0; i < length; i++)अणु
		ग_लिखोl((EEPROM_BASE + ((offset+i) << 3)), &regs->WinBase);
		mb();
		buf[i] = (पढ़ोl(&regs->WinData) >> 24) & 0xff;
		mb();
	पूर्ण

	ग_लिखोl(host, &regs->HostCtrl);
	ग_लिखोl(misc, &regs->LocalCtrl);
	ग_लिखोl(io, &regs->ExtIo);
	mb();
	वापस i;
पूर्ण


/*
 * Shortcut to पढ़ो one word (4 bytes) out of the EEPROM and convert
 * it to our CPU byte-order.
 */
अटल u32 rr_पढ़ो_eeprom_word(काष्ठा rr_निजी *rrpriv,
			    माप_प्रकार offset)
अणु
	__be32 word;

	अगर ((rr_पढ़ो_eeprom(rrpriv, offset,
			    (अचिन्हित अक्षर *)&word, 4) == 4))
		वापस be32_to_cpu(word);
	वापस 0;
पूर्ण


/*
 * Write a string to the EEPROM.
 *
 * This is only called when the firmware is not running.
 */
अटल अचिन्हित पूर्णांक ग_लिखो_eeprom(काष्ठा rr_निजी *rrpriv,
				 अचिन्हित दीर्घ offset,
				 अचिन्हित अक्षर *buf,
				 अचिन्हित दीर्घ length)
अणु
	काष्ठा rr_regs __iomem *regs = rrpriv->regs;
	u32 misc, io, data, i, j, पढ़ोy, error = 0;

	io = पढ़ोl(&regs->ExtIo);
	ग_लिखोl(0, &regs->ExtIo);
	misc = पढ़ोl(&regs->LocalCtrl);
	ग_लिखोl(ENABLE_EEPROM_WRITE, &regs->LocalCtrl);
	mb();

	क्रम (i = 0; i < length; i++)अणु
		ग_लिखोl((EEPROM_BASE + ((offset+i) << 3)), &regs->WinBase);
		mb();
		data = buf[i] << 24;
		/*
		 * Only try to ग_लिखो the data अगर it is not the same
		 * value alपढ़ोy.
		 */
		अगर ((पढ़ोl(&regs->WinData) & 0xff000000) != data)अणु
			ग_लिखोl(data, &regs->WinData);
			पढ़ोy = 0;
			j = 0;
			mb();
			जबतक(!पढ़ोy)अणु
				udelay(20);
				अगर ((पढ़ोl(&regs->WinData) & 0xff000000) ==
				    data)
					पढ़ोy = 1;
				mb();
				अगर (j++ > 5000)अणु
					prपूर्णांकk("data mismatch: %08x, "
					       "WinData %08x\n", data,
					       पढ़ोl(&regs->WinData));
					पढ़ोy = 1;
					error = 1;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	ग_लिखोl(misc, &regs->LocalCtrl);
	ग_लिखोl(io, &regs->ExtIo);
	mb();

	वापस error;
पूर्ण


अटल पूर्णांक rr_init(काष्ठा net_device *dev)
अणु
	काष्ठा rr_निजी *rrpriv;
	काष्ठा rr_regs __iomem *regs;
	u32 sram_size, rev;

	rrpriv = netdev_priv(dev);
	regs = rrpriv->regs;

	rev = पढ़ोl(&regs->FwRev);
	rrpriv->fw_rev = rev;
	अगर (rev > 0x00020024)
		prपूर्णांकk("  Firmware revision: %i.%i.%i\n", (rev >> 16),
		       ((rev >> 8) & 0xff), (rev & 0xff));
	अन्यथा अगर (rev >= 0x00020000) अणु
		prपूर्णांकk("  Firmware revision: %i.%i.%i (2.0.37 or "
		       "later is recommended)\n", (rev >> 16),
		       ((rev >> 8) & 0xff), (rev & 0xff));
	पूर्णअन्यथाअणु
		prपूर्णांकk("  Firmware revision too old: %i.%i.%i, please "
		       "upgrade to 2.0.37 or later.\n",
		       (rev >> 16), ((rev >> 8) & 0xff), (rev & 0xff));
	पूर्ण

#अगर (DEBUG > 2)
	prपूर्णांकk("  Maximum receive rings %i\n", पढ़ोl(&regs->MaxRxRng));
#पूर्ण_अगर

	/*
	 * Read the hardware address from the eeprom.  The HW address
	 * is not really necessary क्रम HIPPI but awfully convenient.
	 * The poपूर्णांकer arithmetic to put it in dev_addr is ugly, but
	 * Donald Becker करोes it this way क्रम the GigE version of this
	 * card and it's लघुer and more portable than any
	 * other method I've seen.  -VAL
	 */

	*(__be16 *)(dev->dev_addr) =
	  htons(rr_पढ़ो_eeprom_word(rrpriv, दुरत्व(काष्ठा eeprom, manf.BoardULA)));
	*(__be32 *)(dev->dev_addr+2) =
	  htonl(rr_पढ़ो_eeprom_word(rrpriv, दुरत्व(काष्ठा eeprom, manf.BoardULA[4])));

	prपूर्णांकk("  MAC: %pM\n", dev->dev_addr);

	sram_size = rr_पढ़ो_eeprom_word(rrpriv, 8);
	prपूर्णांकk("  SRAM size 0x%06x\n", sram_size);

	वापस 0;
पूर्ण


अटल पूर्णांक rr_init1(काष्ठा net_device *dev)
अणु
	काष्ठा rr_निजी *rrpriv;
	काष्ठा rr_regs __iomem *regs;
	अचिन्हित दीर्घ myjअगर, flags;
	काष्ठा cmd cmd;
	u32 hostctrl;
	पूर्णांक ecode = 0;
	लघु i;

	rrpriv = netdev_priv(dev);
	regs = rrpriv->regs;

	spin_lock_irqsave(&rrpriv->lock, flags);

	hostctrl = पढ़ोl(&regs->HostCtrl);
	ग_लिखोl(hostctrl | HALT_NIC | RR_CLEAR_INT, &regs->HostCtrl);
	wmb();

	अगर (hostctrl & PARITY_ERR)अणु
		prपूर्णांकk("%s: Parity error halting NIC - this is serious!\n",
		       dev->name);
		spin_unlock_irqrestore(&rrpriv->lock, flags);
		ecode = -EFAULT;
		जाओ error;
	पूर्ण

	set_rxaddr(regs, rrpriv->rx_ctrl_dma);
	set_infoaddr(regs, rrpriv->info_dma);

	rrpriv->info->evt_ctrl.entry_size = माप(काष्ठा event);
	rrpriv->info->evt_ctrl.entries = EVT_RING_ENTRIES;
	rrpriv->info->evt_ctrl.mode = 0;
	rrpriv->info->evt_ctrl.pi = 0;
	set_rraddr(&rrpriv->info->evt_ctrl.rngptr, rrpriv->evt_ring_dma);

	rrpriv->info->cmd_ctrl.entry_size = माप(काष्ठा cmd);
	rrpriv->info->cmd_ctrl.entries = CMD_RING_ENTRIES;
	rrpriv->info->cmd_ctrl.mode = 0;
	rrpriv->info->cmd_ctrl.pi = 15;

	क्रम (i = 0; i < CMD_RING_ENTRIES; i++) अणु
		ग_लिखोl(0, &regs->CmdRing[i]);
	पूर्ण

	क्रम (i = 0; i < TX_RING_ENTRIES; i++) अणु
		rrpriv->tx_ring[i].size = 0;
		set_rraddr(&rrpriv->tx_ring[i].addr, 0);
		rrpriv->tx_skbuff[i] = शून्य;
	पूर्ण
	rrpriv->info->tx_ctrl.entry_size = माप(काष्ठा tx_desc);
	rrpriv->info->tx_ctrl.entries = TX_RING_ENTRIES;
	rrpriv->info->tx_ctrl.mode = 0;
	rrpriv->info->tx_ctrl.pi = 0;
	set_rraddr(&rrpriv->info->tx_ctrl.rngptr, rrpriv->tx_ring_dma);

	/*
	 * Set dirty_tx beक्रमe we start receiving पूर्णांकerrupts, otherwise
	 * the पूर्णांकerrupt handler might think it is supposed to process
	 * tx पूर्णांकs beक्रमe we are up and running, which may cause a null
	 * poपूर्णांकer access in the पूर्णांक handler.
	 */
	rrpriv->tx_full = 0;
	rrpriv->cur_rx = 0;
	rrpriv->dirty_rx = rrpriv->dirty_tx = 0;

	rr_reset(dev);

	/* Tuning values */
	ग_लिखोl(0x5000, &regs->ConRetry);
	ग_लिखोl(0x100, &regs->ConRetryTmr);
	ग_लिखोl(0x500000, &regs->ConTmout);
 	ग_लिखोl(0x60, &regs->IntrTmr);
	ग_लिखोl(0x500000, &regs->TxDataMvTimeout);
	ग_लिखोl(0x200000, &regs->RxDataMvTimeout);
 	ग_लिखोl(0x80, &regs->WriteDmaThresh);
 	ग_लिखोl(0x80, &regs->ReadDmaThresh);

	rrpriv->fw_running = 0;
	wmb();

	hostctrl &= ~(HALT_NIC | INVALID_INST_B | PARITY_ERR);
	ग_लिखोl(hostctrl, &regs->HostCtrl);
	wmb();

	spin_unlock_irqrestore(&rrpriv->lock, flags);

	क्रम (i = 0; i < RX_RING_ENTRIES; i++) अणु
		काष्ठा sk_buff *skb;
		dma_addr_t addr;

		rrpriv->rx_ring[i].mode = 0;
		skb = alloc_skb(dev->mtu + HIPPI_HLEN, GFP_ATOMIC);
		अगर (!skb) अणु
			prपूर्णांकk(KERN_WARNING "%s: Unable to allocate memory "
			       "for receive ring - halting NIC\n", dev->name);
			ecode = -ENOMEM;
			जाओ error;
		पूर्ण
		rrpriv->rx_skbuff[i] = skb;
		addr = dma_map_single(&rrpriv->pci_dev->dev, skb->data,
				      dev->mtu + HIPPI_HLEN, DMA_FROM_DEVICE);
		/*
		 * Sanity test to see अगर we conflict with the DMA
		 * limitations of the Roadrunner.
		 */
		अगर ((((अचिन्हित दीर्घ)skb->data) & 0xfff) > ~65320)
			prपूर्णांकk("skb alloc error\n");

		set_rraddr(&rrpriv->rx_ring[i].addr, addr);
		rrpriv->rx_ring[i].size = dev->mtu + HIPPI_HLEN;
	पूर्ण

	rrpriv->rx_ctrl[4].entry_size = माप(काष्ठा rx_desc);
	rrpriv->rx_ctrl[4].entries = RX_RING_ENTRIES;
	rrpriv->rx_ctrl[4].mode = 8;
	rrpriv->rx_ctrl[4].pi = 0;
	wmb();
	set_rraddr(&rrpriv->rx_ctrl[4].rngptr, rrpriv->rx_ring_dma);

	udelay(1000);

	/*
	 * Now start the FirmWare.
	 */
	cmd.code = C_START_FW;
	cmd.ring = 0;
	cmd.index = 0;

	rr_issue_cmd(rrpriv, &cmd);

	/*
	 * Give the FirmWare समय to chew on the `get running' command.
	 */
	myjअगर = jअगरfies + 5 * HZ;
	जबतक (समय_beक्रमe(jअगरfies, myjअगर) && !rrpriv->fw_running)
		cpu_relax();

	netअगर_start_queue(dev);

	वापस ecode;

 error:
	/*
	 * We might have gotten here because we are out of memory,
	 * make sure we release everything we allocated beक्रमe failing
	 */
	क्रम (i = 0; i < RX_RING_ENTRIES; i++) अणु
		काष्ठा sk_buff *skb = rrpriv->rx_skbuff[i];

		अगर (skb) अणु
			dma_unmap_single(&rrpriv->pci_dev->dev,
					 rrpriv->rx_ring[i].addr.addrlo,
					 dev->mtu + HIPPI_HLEN,
					 DMA_FROM_DEVICE);
			rrpriv->rx_ring[i].size = 0;
			set_rraddr(&rrpriv->rx_ring[i].addr, 0);
			dev_kमुक्त_skb(skb);
			rrpriv->rx_skbuff[i] = शून्य;
		पूर्ण
	पूर्ण
	वापस ecode;
पूर्ण


/*
 * All events are considered to be slow (RX/TX पूर्णांकs करो not generate
 * events) and are handled here, outside the मुख्य पूर्णांकerrupt handler,
 * to reduce the size of the handler.
 */
अटल u32 rr_handle_event(काष्ठा net_device *dev, u32 prodidx, u32 eidx)
अणु
	काष्ठा rr_निजी *rrpriv;
	काष्ठा rr_regs __iomem *regs;
	u32 पंचांगp;

	rrpriv = netdev_priv(dev);
	regs = rrpriv->regs;

	जबतक (prodidx != eidx)अणु
		चयन (rrpriv->evt_ring[eidx].code)अणु
		हाल E_NIC_UP:
			पंचांगp = पढ़ोl(&regs->FwRev);
			prपूर्णांकk(KERN_INFO "%s: Firmware revision %i.%i.%i "
			       "up and running\n", dev->name,
			       (पंचांगp >> 16), ((पंचांगp >> 8) & 0xff), (पंचांगp & 0xff));
			rrpriv->fw_running = 1;
			ग_लिखोl(RX_RING_ENTRIES - 1, &regs->IpRxPi);
			wmb();
			अवरोध;
		हाल E_LINK_ON:
			prपूर्णांकk(KERN_INFO "%s: Optical link ON\n", dev->name);
			अवरोध;
		हाल E_LINK_OFF:
			prपूर्णांकk(KERN_INFO "%s: Optical link OFF\n", dev->name);
			अवरोध;
		हाल E_RX_IDLE:
			prपूर्णांकk(KERN_WARNING "%s: RX data not moving\n",
			       dev->name);
			जाओ drop;
		हाल E_WATCHDOG:
			prपूर्णांकk(KERN_INFO "%s: The watchdog is here to see "
			       "us\n", dev->name);
			अवरोध;
		हाल E_INTERN_ERR:
			prपूर्णांकk(KERN_ERR "%s: HIPPI Internal NIC error\n",
			       dev->name);
			ग_लिखोl(पढ़ोl(&regs->HostCtrl)|HALT_NIC|RR_CLEAR_INT,
			       &regs->HostCtrl);
			wmb();
			अवरोध;
		हाल E_HOST_ERR:
			prपूर्णांकk(KERN_ERR "%s: Host software error\n",
			       dev->name);
			ग_लिखोl(पढ़ोl(&regs->HostCtrl)|HALT_NIC|RR_CLEAR_INT,
			       &regs->HostCtrl);
			wmb();
			अवरोध;
		/*
		 * TX events.
		 */
		हाल E_CON_REJ:
			prपूर्णांकk(KERN_WARNING "%s: Connection rejected\n",
			       dev->name);
			dev->stats.tx_पातed_errors++;
			अवरोध;
		हाल E_CON_TMOUT:
			prपूर्णांकk(KERN_WARNING "%s: Connection timeout\n",
			       dev->name);
			अवरोध;
		हाल E_DISC_ERR:
			prपूर्णांकk(KERN_WARNING "%s: HIPPI disconnect error\n",
			       dev->name);
			dev->stats.tx_पातed_errors++;
			अवरोध;
		हाल E_INT_PRTY:
			prपूर्णांकk(KERN_ERR "%s: HIPPI Internal Parity error\n",
			       dev->name);
			ग_लिखोl(पढ़ोl(&regs->HostCtrl)|HALT_NIC|RR_CLEAR_INT,
			       &regs->HostCtrl);
			wmb();
			अवरोध;
		हाल E_TX_IDLE:
			prपूर्णांकk(KERN_WARNING "%s: Transmitter idle\n",
			       dev->name);
			अवरोध;
		हाल E_TX_LINK_DROP:
			prपूर्णांकk(KERN_WARNING "%s: Link lost during transmit\n",
			       dev->name);
			dev->stats.tx_पातed_errors++;
			ग_लिखोl(पढ़ोl(&regs->HostCtrl)|HALT_NIC|RR_CLEAR_INT,
			       &regs->HostCtrl);
			wmb();
			अवरोध;
		हाल E_TX_INV_RNG:
			prपूर्णांकk(KERN_ERR "%s: Invalid send ring block\n",
			       dev->name);
			ग_लिखोl(पढ़ोl(&regs->HostCtrl)|HALT_NIC|RR_CLEAR_INT,
			       &regs->HostCtrl);
			wmb();
			अवरोध;
		हाल E_TX_INV_BUF:
			prपूर्णांकk(KERN_ERR "%s: Invalid send buffer address\n",
			       dev->name);
			ग_लिखोl(पढ़ोl(&regs->HostCtrl)|HALT_NIC|RR_CLEAR_INT,
			       &regs->HostCtrl);
			wmb();
			अवरोध;
		हाल E_TX_INV_DSC:
			prपूर्णांकk(KERN_ERR "%s: Invalid descriptor address\n",
			       dev->name);
			ग_लिखोl(पढ़ोl(&regs->HostCtrl)|HALT_NIC|RR_CLEAR_INT,
			       &regs->HostCtrl);
			wmb();
			अवरोध;
		/*
		 * RX events.
		 */
		हाल E_RX_RNG_OUT:
			prपूर्णांकk(KERN_INFO "%s: Receive ring full\n", dev->name);
			अवरोध;

		हाल E_RX_PAR_ERR:
			prपूर्णांकk(KERN_WARNING "%s: Receive parity error\n",
			       dev->name);
			जाओ drop;
		हाल E_RX_LLRC_ERR:
			prपूर्णांकk(KERN_WARNING "%s: Receive LLRC error\n",
			       dev->name);
			जाओ drop;
		हाल E_PKT_LN_ERR:
			prपूर्णांकk(KERN_WARNING "%s: Receive packet length "
			       "error\n", dev->name);
			जाओ drop;
		हाल E_DTA_CKSM_ERR:
			prपूर्णांकk(KERN_WARNING "%s: Data checksum error\n",
			       dev->name);
			जाओ drop;
		हाल E_SHT_BST:
			prपूर्णांकk(KERN_WARNING "%s: Unexpected short burst "
			       "error\n", dev->name);
			जाओ drop;
		हाल E_STATE_ERR:
			prपूर्णांकk(KERN_WARNING "%s: Recv. state transition"
			       " error\n", dev->name);
			जाओ drop;
		हाल E_UNEXP_DATA:
			prपूर्णांकk(KERN_WARNING "%s: Unexpected data error\n",
			       dev->name);
			जाओ drop;
		हाल E_LST_LNK_ERR:
			prपूर्णांकk(KERN_WARNING "%s: Link lost error\n",
			       dev->name);
			जाओ drop;
		हाल E_FRM_ERR:
			prपूर्णांकk(KERN_WARNING "%s: Framing Error\n",
			       dev->name);
			जाओ drop;
		हाल E_FLG_SYN_ERR:
			prपूर्णांकk(KERN_WARNING "%s: Flag sync. lost during "
			       "packet\n", dev->name);
			जाओ drop;
		हाल E_RX_INV_BUF:
			prपूर्णांकk(KERN_ERR "%s: Invalid receive buffer "
			       "address\n", dev->name);
			ग_लिखोl(पढ़ोl(&regs->HostCtrl)|HALT_NIC|RR_CLEAR_INT,
			       &regs->HostCtrl);
			wmb();
			अवरोध;
		हाल E_RX_INV_DSC:
			prपूर्णांकk(KERN_ERR "%s: Invalid receive descriptor "
			       "address\n", dev->name);
			ग_लिखोl(पढ़ोl(&regs->HostCtrl)|HALT_NIC|RR_CLEAR_INT,
			       &regs->HostCtrl);
			wmb();
			अवरोध;
		हाल E_RNG_BLK:
			prपूर्णांकk(KERN_ERR "%s: Invalid ring block\n",
			       dev->name);
			ग_लिखोl(पढ़ोl(&regs->HostCtrl)|HALT_NIC|RR_CLEAR_INT,
			       &regs->HostCtrl);
			wmb();
			अवरोध;
		drop:
			/* Label packet to be dropped.
			 * Actual dropping occurs in rx
			 * handling.
			 *
			 * The index of packet we get to drop is
			 * the index of the packet following
			 * the bad packet. -kbf
			 */
			अणु
				u16 index = rrpriv->evt_ring[eidx].index;
				index = (index + (RX_RING_ENTRIES - 1)) %
					RX_RING_ENTRIES;
				rrpriv->rx_ring[index].mode |=
					(PACKET_BAD | PACKET_END);
			पूर्ण
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_WARNING "%s: Unhandled event 0x%02x\n",
			       dev->name, rrpriv->evt_ring[eidx].code);
		पूर्ण
		eidx = (eidx + 1) % EVT_RING_ENTRIES;
	पूर्ण

	rrpriv->info->evt_ctrl.pi = eidx;
	wmb();
	वापस eidx;
पूर्ण


अटल व्योम rx_पूर्णांक(काष्ठा net_device *dev, u32 rxlimit, u32 index)
अणु
	काष्ठा rr_निजी *rrpriv = netdev_priv(dev);
	काष्ठा rr_regs __iomem *regs = rrpriv->regs;

	करो अणु
		काष्ठा rx_desc *desc;
		u32 pkt_len;

		desc = &(rrpriv->rx_ring[index]);
		pkt_len = desc->size;
#अगर (DEBUG > 2)
		prपूर्णांकk("index %i, rxlimit %i\n", index, rxlimit);
		prपूर्णांकk("len %x, mode %x\n", pkt_len, desc->mode);
#पूर्ण_अगर
		अगर ( (rrpriv->rx_ring[index].mode & PACKET_BAD) == PACKET_BAD)अणु
			dev->stats.rx_dropped++;
			जाओ defer;
		पूर्ण

		अगर (pkt_len > 0)अणु
			काष्ठा sk_buff *skb, *rx_skb;

			rx_skb = rrpriv->rx_skbuff[index];

			अगर (pkt_len < PKT_COPY_THRESHOLD) अणु
				skb = alloc_skb(pkt_len, GFP_ATOMIC);
				अगर (skb == शून्य)अणु
					prपूर्णांकk(KERN_WARNING "%s: Unable to allocate skb (%i bytes), deferring packet\n", dev->name, pkt_len);
					dev->stats.rx_dropped++;
					जाओ defer;
				पूर्ण अन्यथा अणु
					dma_sync_single_क्रम_cpu(&rrpriv->pci_dev->dev,
								desc->addr.addrlo,
								pkt_len,
								DMA_FROM_DEVICE);

					skb_put_data(skb, rx_skb->data,
						     pkt_len);

					dma_sync_single_क्रम_device(&rrpriv->pci_dev->dev,
								   desc->addr.addrlo,
								   pkt_len,
								   DMA_FROM_DEVICE);
				पूर्ण
			पूर्णअन्यथाअणु
				काष्ठा sk_buff *newskb;

				newskb = alloc_skb(dev->mtu + HIPPI_HLEN,
					GFP_ATOMIC);
				अगर (newskb)अणु
					dma_addr_t addr;

					dma_unmap_single(&rrpriv->pci_dev->dev,
							 desc->addr.addrlo,
							 dev->mtu + HIPPI_HLEN,
							 DMA_FROM_DEVICE);
					skb = rx_skb;
					skb_put(skb, pkt_len);
					rrpriv->rx_skbuff[index] = newskb;
					addr = dma_map_single(&rrpriv->pci_dev->dev,
							      newskb->data,
							      dev->mtu + HIPPI_HLEN,
							      DMA_FROM_DEVICE);
					set_rraddr(&desc->addr, addr);
				पूर्ण अन्यथा अणु
					prपूर्णांकk("%s: Out of memory, deferring "
					       "packet\n", dev->name);
					dev->stats.rx_dropped++;
					जाओ defer;
				पूर्ण
			पूर्ण
			skb->protocol = hippi_type_trans(skb, dev);

			netअगर_rx(skb);		/* send it up */

			dev->stats.rx_packets++;
			dev->stats.rx_bytes += pkt_len;
		पूर्ण
	defer:
		desc->mode = 0;
		desc->size = dev->mtu + HIPPI_HLEN;

		अगर ((index & 7) == 7)
			ग_लिखोl(index, &regs->IpRxPi);

		index = (index + 1) % RX_RING_ENTRIES;
	पूर्ण जबतक(index != rxlimit);

	rrpriv->cur_rx = index;
	wmb();
पूर्ण


अटल irqवापस_t rr_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा rr_निजी *rrpriv;
	काष्ठा rr_regs __iomem *regs;
	काष्ठा net_device *dev = (काष्ठा net_device *)dev_id;
	u32 prodidx, rxindex, eidx, txcsmr, rxlimit, txcon;

	rrpriv = netdev_priv(dev);
	regs = rrpriv->regs;

	अगर (!(पढ़ोl(&regs->HostCtrl) & RR_INT))
		वापस IRQ_NONE;

	spin_lock(&rrpriv->lock);

	prodidx = पढ़ोl(&regs->EvtPrd);
	txcsmr = (prodidx >> 8) & 0xff;
	rxlimit = (prodidx >> 16) & 0xff;
	prodidx &= 0xff;

#अगर (DEBUG > 2)
	prपूर्णांकk("%s: interrupt, prodidx = %i, eidx = %i\n", dev->name,
	       prodidx, rrpriv->info->evt_ctrl.pi);
#पूर्ण_अगर
	/*
	 * Order here is important.  We must handle events
	 * beक्रमe करोing anything अन्यथा in order to catch
	 * such things as LLRC errors, etc -kbf
	 */

	eidx = rrpriv->info->evt_ctrl.pi;
	अगर (prodidx != eidx)
		eidx = rr_handle_event(dev, prodidx, eidx);

	rxindex = rrpriv->cur_rx;
	अगर (rxindex != rxlimit)
		rx_पूर्णांक(dev, rxlimit, rxindex);

	txcon = rrpriv->dirty_tx;
	अगर (txcsmr != txcon) अणु
		करो अणु
			/* Due to occational firmware TX producer/consumer out
			 * of sync. error need to check entry in ring -kbf
			 */
			अगर(rrpriv->tx_skbuff[txcon])अणु
				काष्ठा tx_desc *desc;
				काष्ठा sk_buff *skb;

				desc = &(rrpriv->tx_ring[txcon]);
				skb = rrpriv->tx_skbuff[txcon];

				dev->stats.tx_packets++;
				dev->stats.tx_bytes += skb->len;

				dma_unmap_single(&rrpriv->pci_dev->dev,
						 desc->addr.addrlo, skb->len,
						 DMA_TO_DEVICE);
				dev_kमुक्त_skb_irq(skb);

				rrpriv->tx_skbuff[txcon] = शून्य;
				desc->size = 0;
				set_rraddr(&rrpriv->tx_ring[txcon].addr, 0);
				desc->mode = 0;
			पूर्ण
			txcon = (txcon + 1) % TX_RING_ENTRIES;
		पूर्ण जबतक (txcsmr != txcon);
		wmb();

		rrpriv->dirty_tx = txcon;
		अगर (rrpriv->tx_full && rr_अगर_busy(dev) &&
		    (((rrpriv->info->tx_ctrl.pi + 1) % TX_RING_ENTRIES)
		     != rrpriv->dirty_tx))अणु
			rrpriv->tx_full = 0;
			netअगर_wake_queue(dev);
		पूर्ण
	पूर्ण

	eidx |= ((txcsmr << 8) | (rxlimit << 16));
	ग_लिखोl(eidx, &regs->EvtCon);
	wmb();

	spin_unlock(&rrpriv->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल अंतरभूत व्योम rr_raz_tx(काष्ठा rr_निजी *rrpriv,
			     काष्ठा net_device *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < TX_RING_ENTRIES; i++) अणु
		काष्ठा sk_buff *skb = rrpriv->tx_skbuff[i];

		अगर (skb) अणु
			काष्ठा tx_desc *desc = &(rrpriv->tx_ring[i]);

			dma_unmap_single(&rrpriv->pci_dev->dev,
					 desc->addr.addrlo, skb->len,
					 DMA_TO_DEVICE);
			desc->size = 0;
			set_rraddr(&desc->addr, 0);
			dev_kमुक्त_skb(skb);
			rrpriv->tx_skbuff[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण


अटल अंतरभूत व्योम rr_raz_rx(काष्ठा rr_निजी *rrpriv,
			     काष्ठा net_device *dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < RX_RING_ENTRIES; i++) अणु
		काष्ठा sk_buff *skb = rrpriv->rx_skbuff[i];

		अगर (skb) अणु
			काष्ठा rx_desc *desc = &(rrpriv->rx_ring[i]);

			dma_unmap_single(&rrpriv->pci_dev->dev,
					 desc->addr.addrlo,
					 dev->mtu + HIPPI_HLEN,
					 DMA_FROM_DEVICE);
			desc->size = 0;
			set_rraddr(&desc->addr, 0);
			dev_kमुक्त_skb(skb);
			rrpriv->rx_skbuff[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rr_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा rr_निजी *rrpriv = from_समयr(rrpriv, t, समयr);
	काष्ठा net_device *dev = pci_get_drvdata(rrpriv->pci_dev);
	काष्ठा rr_regs __iomem *regs = rrpriv->regs;
	अचिन्हित दीर्घ flags;

	अगर (पढ़ोl(&regs->HostCtrl) & NIC_HALTED)अणु
		prपूर्णांकk("%s: Restarting nic\n", dev->name);
		स_रखो(rrpriv->rx_ctrl, 0, 256 * माप(काष्ठा ring_ctrl));
		स_रखो(rrpriv->info, 0, माप(काष्ठा rr_info));
		wmb();

		rr_raz_tx(rrpriv, dev);
		rr_raz_rx(rrpriv, dev);

		अगर (rr_init1(dev)) अणु
			spin_lock_irqsave(&rrpriv->lock, flags);
			ग_लिखोl(पढ़ोl(&regs->HostCtrl)|HALT_NIC|RR_CLEAR_INT,
			       &regs->HostCtrl);
			spin_unlock_irqrestore(&rrpriv->lock, flags);
		पूर्ण
	पूर्ण
	rrpriv->समयr.expires = RUN_AT(5*HZ);
	add_समयr(&rrpriv->समयr);
पूर्ण


अटल पूर्णांक rr_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा rr_निजी *rrpriv = netdev_priv(dev);
	काष्ठा pci_dev *pdev = rrpriv->pci_dev;
	काष्ठा rr_regs __iomem *regs;
	पूर्णांक ecode = 0;
	अचिन्हित दीर्घ flags;
	dma_addr_t dma_addr;

	regs = rrpriv->regs;

	अगर (rrpriv->fw_rev < 0x00020000) अणु
		prपूर्णांकk(KERN_WARNING "%s: trying to configure device with "
		       "obsolete firmware\n", dev->name);
		ecode = -EBUSY;
		जाओ error;
	पूर्ण

	rrpriv->rx_ctrl = dma_alloc_coherent(&pdev->dev,
					     256 * माप(काष्ठा ring_ctrl),
					     &dma_addr, GFP_KERNEL);
	अगर (!rrpriv->rx_ctrl) अणु
		ecode = -ENOMEM;
		जाओ error;
	पूर्ण
	rrpriv->rx_ctrl_dma = dma_addr;

	rrpriv->info = dma_alloc_coherent(&pdev->dev, माप(काष्ठा rr_info),
					  &dma_addr, GFP_KERNEL);
	अगर (!rrpriv->info) अणु
		ecode = -ENOMEM;
		जाओ error;
	पूर्ण
	rrpriv->info_dma = dma_addr;
	wmb();

	spin_lock_irqsave(&rrpriv->lock, flags);
	ग_लिखोl(पढ़ोl(&regs->HostCtrl)|HALT_NIC|RR_CLEAR_INT, &regs->HostCtrl);
	पढ़ोl(&regs->HostCtrl);
	spin_unlock_irqrestore(&rrpriv->lock, flags);

	अगर (request_irq(pdev->irq, rr_पूर्णांकerrupt, IRQF_SHARED, dev->name, dev)) अणु
		prपूर्णांकk(KERN_WARNING "%s: Requested IRQ %d is busy\n",
		       dev->name, pdev->irq);
		ecode = -EAGAIN;
		जाओ error;
	पूर्ण

	अगर ((ecode = rr_init1(dev)))
		जाओ error;

	/* Set the समयr to चयन to check क्रम link beat and perhaps चयन
	   to an alternate media type. */
	समयr_setup(&rrpriv->समयr, rr_समयr, 0);
	rrpriv->समयr.expires = RUN_AT(5*HZ);           /* 5 sec. watchकरोg */
	add_समयr(&rrpriv->समयr);

	netअगर_start_queue(dev);

	वापस ecode;

 error:
	spin_lock_irqsave(&rrpriv->lock, flags);
	ग_लिखोl(पढ़ोl(&regs->HostCtrl)|HALT_NIC|RR_CLEAR_INT, &regs->HostCtrl);
	spin_unlock_irqrestore(&rrpriv->lock, flags);

	अगर (rrpriv->info) अणु
		dma_मुक्त_coherent(&pdev->dev, माप(काष्ठा rr_info),
				  rrpriv->info, rrpriv->info_dma);
		rrpriv->info = शून्य;
	पूर्ण
	अगर (rrpriv->rx_ctrl) अणु
		dma_मुक्त_coherent(&pdev->dev, 256 * माप(काष्ठा ring_ctrl),
				  rrpriv->rx_ctrl, rrpriv->rx_ctrl_dma);
		rrpriv->rx_ctrl = शून्य;
	पूर्ण

	netअगर_stop_queue(dev);

	वापस ecode;
पूर्ण


अटल व्योम rr_dump(काष्ठा net_device *dev)
अणु
	काष्ठा rr_निजी *rrpriv;
	काष्ठा rr_regs __iomem *regs;
	u32 index, cons;
	लघु i;
	पूर्णांक len;

	rrpriv = netdev_priv(dev);
	regs = rrpriv->regs;

	prपूर्णांकk("%s: dumping NIC TX rings\n", dev->name);

	prपूर्णांकk("RxPrd %08x, TxPrd %02x, EvtPrd %08x, TxPi %02x, TxCtrlPi %02x\n",
	       पढ़ोl(&regs->RxPrd), पढ़ोl(&regs->TxPrd),
	       पढ़ोl(&regs->EvtPrd), पढ़ोl(&regs->TxPi),
	       rrpriv->info->tx_ctrl.pi);

	prपूर्णांकk("Error code 0x%x\n", पढ़ोl(&regs->Fail1));

	index = (((पढ़ोl(&regs->EvtPrd) >> 8) & 0xff) - 1) % TX_RING_ENTRIES;
	cons = rrpriv->dirty_tx;
	prपूर्णांकk("TX ring index %i, TX consumer %i\n",
	       index, cons);

	अगर (rrpriv->tx_skbuff[index])अणु
		len = min_t(पूर्णांक, 0x80, rrpriv->tx_skbuff[index]->len);
		prपूर्णांकk("skbuff for index %i is valid - dumping data (0x%x bytes - DMA len 0x%x)\n", index, len, rrpriv->tx_ring[index].size);
		क्रम (i = 0; i < len; i++)अणु
			अगर (!(i & 7))
				prपूर्णांकk("\n");
			prपूर्णांकk("%02x ", (अचिन्हित अक्षर) rrpriv->tx_skbuff[index]->data[i]);
		पूर्ण
		prपूर्णांकk("\n");
	पूर्ण

	अगर (rrpriv->tx_skbuff[cons])अणु
		len = min_t(पूर्णांक, 0x80, rrpriv->tx_skbuff[cons]->len);
		prपूर्णांकk("skbuff for cons %i is valid - dumping data (0x%x bytes - skbuff len 0x%x)\n", cons, len, rrpriv->tx_skbuff[cons]->len);
		prपूर्णांकk("mode 0x%x, size 0x%x,\n phys %08Lx, skbuff-addr %p, truesize 0x%x\n",
		       rrpriv->tx_ring[cons].mode,
		       rrpriv->tx_ring[cons].size,
		       (अचिन्हित दीर्घ दीर्घ) rrpriv->tx_ring[cons].addr.addrlo,
		       rrpriv->tx_skbuff[cons]->data,
		       (अचिन्हित पूर्णांक)rrpriv->tx_skbuff[cons]->truesize);
		क्रम (i = 0; i < len; i++)अणु
			अगर (!(i & 7))
				prपूर्णांकk("\n");
			prपूर्णांकk("%02x ", (अचिन्हित अक्षर)rrpriv->tx_ring[cons].size);
		पूर्ण
		prपूर्णांकk("\n");
	पूर्ण

	prपूर्णांकk("dumping TX ring info:\n");
	क्रम (i = 0; i < TX_RING_ENTRIES; i++)
		prपूर्णांकk("mode 0x%x, size 0x%x, phys-addr %08Lx\n",
		       rrpriv->tx_ring[i].mode,
		       rrpriv->tx_ring[i].size,
		       (अचिन्हित दीर्घ दीर्घ) rrpriv->tx_ring[i].addr.addrlo);

पूर्ण


अटल पूर्णांक rr_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा rr_निजी *rrpriv = netdev_priv(dev);
	काष्ठा rr_regs __iomem *regs = rrpriv->regs;
	काष्ठा pci_dev *pdev = rrpriv->pci_dev;
	अचिन्हित दीर्घ flags;
	u32 पंचांगp;
	लघु i;

	netअगर_stop_queue(dev);


	/*
	 * Lock to make sure we are not cleaning up जबतक another CPU
	 * is handling पूर्णांकerrupts.
	 */
	spin_lock_irqsave(&rrpriv->lock, flags);

	पंचांगp = पढ़ोl(&regs->HostCtrl);
	अगर (पंचांगp & NIC_HALTED)अणु
		prपूर्णांकk("%s: NIC already halted\n", dev->name);
		rr_dump(dev);
	पूर्णअन्यथाअणु
		पंचांगp |= HALT_NIC | RR_CLEAR_INT;
		ग_लिखोl(पंचांगp, &regs->HostCtrl);
		पढ़ोl(&regs->HostCtrl);
	पूर्ण

	rrpriv->fw_running = 0;

	del_समयr_sync(&rrpriv->समयr);

	ग_लिखोl(0, &regs->TxPi);
	ग_लिखोl(0, &regs->IpRxPi);

	ग_लिखोl(0, &regs->EvtCon);
	ग_लिखोl(0, &regs->EvtPrd);

	क्रम (i = 0; i < CMD_RING_ENTRIES; i++)
		ग_लिखोl(0, &regs->CmdRing[i]);

	rrpriv->info->tx_ctrl.entries = 0;
	rrpriv->info->cmd_ctrl.pi = 0;
	rrpriv->info->evt_ctrl.pi = 0;
	rrpriv->rx_ctrl[4].entries = 0;

	rr_raz_tx(rrpriv, dev);
	rr_raz_rx(rrpriv, dev);

	dma_मुक्त_coherent(&pdev->dev, 256 * माप(काष्ठा ring_ctrl),
			  rrpriv->rx_ctrl, rrpriv->rx_ctrl_dma);
	rrpriv->rx_ctrl = शून्य;

	dma_मुक्त_coherent(&pdev->dev, माप(काष्ठा rr_info), rrpriv->info,
			  rrpriv->info_dma);
	rrpriv->info = शून्य;

	spin_unlock_irqrestore(&rrpriv->lock, flags);
	मुक्त_irq(pdev->irq, dev);

	वापस 0;
पूर्ण


अटल netdev_tx_t rr_start_xmit(काष्ठा sk_buff *skb,
				 काष्ठा net_device *dev)
अणु
	काष्ठा rr_निजी *rrpriv = netdev_priv(dev);
	काष्ठा rr_regs __iomem *regs = rrpriv->regs;
	काष्ठा hippi_cb *hcb = (काष्ठा hippi_cb *) skb->cb;
	काष्ठा ring_ctrl *txctrl;
	अचिन्हित दीर्घ flags;
	u32 index, len = skb->len;
	u32 *अगरield;
	काष्ठा sk_buff *new_skb;

	अगर (पढ़ोl(&regs->Mode) & FATAL_ERR)
		prपूर्णांकk("error codes Fail1 %02x, Fail2 %02x\n",
		       पढ़ोl(&regs->Fail1), पढ़ोl(&regs->Fail2));

	/*
	 * We probably need to deal with tbusy here to prevent overruns.
	 */

	अगर (skb_headroom(skb) < 8)अणु
		prपूर्णांकk("incoming skb too small - reallocating\n");
		अगर (!(new_skb = dev_alloc_skb(len + 8))) अणु
			dev_kमुक्त_skb(skb);
			netअगर_wake_queue(dev);
			वापस NETDEV_TX_OK;
		पूर्ण
		skb_reserve(new_skb, 8);
		skb_put(new_skb, len);
		skb_copy_from_linear_data(skb, new_skb->data, len);
		dev_kमुक्त_skb(skb);
		skb = new_skb;
	पूर्ण

	अगरield = skb_push(skb, 8);

	अगरield[0] = 0;
	अगरield[1] = hcb->अगरield;

	/*
	 * We करोn't need the lock beक्रमe we are actually going to start
	 * fiddling with the control blocks.
	 */
	spin_lock_irqsave(&rrpriv->lock, flags);

	txctrl = &rrpriv->info->tx_ctrl;

	index = txctrl->pi;

	rrpriv->tx_skbuff[index] = skb;
	set_rraddr(&rrpriv->tx_ring[index].addr,
		   dma_map_single(&rrpriv->pci_dev->dev, skb->data, len + 8, DMA_TO_DEVICE));
	rrpriv->tx_ring[index].size = len + 8; /* include IFIELD */
	rrpriv->tx_ring[index].mode = PACKET_START | PACKET_END;
	txctrl->pi = (index + 1) % TX_RING_ENTRIES;
	wmb();
	ग_लिखोl(txctrl->pi, &regs->TxPi);

	अगर (txctrl->pi == rrpriv->dirty_tx)अणु
		rrpriv->tx_full = 1;
		netअगर_stop_queue(dev);
	पूर्ण

	spin_unlock_irqrestore(&rrpriv->lock, flags);

	वापस NETDEV_TX_OK;
पूर्ण


/*
 * Read the firmware out of the EEPROM and put it पूर्णांकo the SRAM
 * (or from user space - later)
 *
 * This operation requires the NIC to be halted and is perक्रमmed with
 * पूर्णांकerrupts disabled and with the spinlock hold.
 */
अटल पूर्णांक rr_load_firmware(काष्ठा net_device *dev)
अणु
	काष्ठा rr_निजी *rrpriv;
	काष्ठा rr_regs __iomem *regs;
	माप_प्रकार eptr, segptr;
	पूर्णांक i, j;
	u32 localctrl, sptr, len, पंचांगp;
	u32 p2len, p2size, nr_seg, revision, io, sram_size;

	rrpriv = netdev_priv(dev);
	regs = rrpriv->regs;

	अगर (dev->flags & IFF_UP)
		वापस -EBUSY;

	अगर (!(पढ़ोl(&regs->HostCtrl) & NIC_HALTED))अणु
		prपूर्णांकk("%s: Trying to load firmware to a running NIC.\n",
		       dev->name);
		वापस -EBUSY;
	पूर्ण

	localctrl = पढ़ोl(&regs->LocalCtrl);
	ग_लिखोl(0, &regs->LocalCtrl);

	ग_लिखोl(0, &regs->EvtPrd);
	ग_लिखोl(0, &regs->RxPrd);
	ग_लिखोl(0, &regs->TxPrd);

	/*
	 * First wipe the entire SRAM, otherwise we might run पूर्णांकo all
	 * kinds of trouble ... sigh, this took almost all afternoon
	 * to track करोwn ;-(
	 */
	io = पढ़ोl(&regs->ExtIo);
	ग_लिखोl(0, &regs->ExtIo);
	sram_size = rr_पढ़ो_eeprom_word(rrpriv, 8);

	क्रम (i = 200; i < sram_size / 4; i++)अणु
		ग_लिखोl(i * 4, &regs->WinBase);
		mb();
		ग_लिखोl(0, &regs->WinData);
		mb();
	पूर्ण
	ग_लिखोl(io, &regs->ExtIo);
	mb();

	eptr = rr_पढ़ो_eeprom_word(rrpriv,
		       दुरत्व(काष्ठा eeprom, rncd_info.AddrRunCodeSegs));
	eptr = ((eptr & 0x1fffff) >> 3);

	p2len = rr_पढ़ो_eeprom_word(rrpriv, 0x83*4);
	p2len = (p2len << 2);
	p2size = rr_पढ़ो_eeprom_word(rrpriv, 0x84*4);
	p2size = ((p2size & 0x1fffff) >> 3);

	अगर ((eptr < p2size) || (eptr > (p2size + p2len)))अणु
		prपूर्णांकk("%s: eptr is invalid\n", dev->name);
		जाओ out;
	पूर्ण

	revision = rr_पढ़ो_eeprom_word(rrpriv,
			दुरत्व(काष्ठा eeprom, manf.HeaderFmt));

	अगर (revision != 1)अणु
		prपूर्णांकk("%s: invalid firmware format (%i)\n",
		       dev->name, revision);
		जाओ out;
	पूर्ण

	nr_seg = rr_पढ़ो_eeprom_word(rrpriv, eptr);
	eptr +=4;
#अगर (DEBUG > 1)
	prपूर्णांकk("%s: nr_seg %i\n", dev->name, nr_seg);
#पूर्ण_अगर

	क्रम (i = 0; i < nr_seg; i++)अणु
		sptr = rr_पढ़ो_eeprom_word(rrpriv, eptr);
		eptr += 4;
		len = rr_पढ़ो_eeprom_word(rrpriv, eptr);
		eptr += 4;
		segptr = rr_पढ़ो_eeprom_word(rrpriv, eptr);
		segptr = ((segptr & 0x1fffff) >> 3);
		eptr += 4;
#अगर (DEBUG > 1)
		prपूर्णांकk("%s: segment %i, sram address %06x, length %04x, segptr %06x\n",
		       dev->name, i, sptr, len, segptr);
#पूर्ण_अगर
		क्रम (j = 0; j < len; j++)अणु
			पंचांगp = rr_पढ़ो_eeprom_word(rrpriv, segptr);
			ग_लिखोl(sptr, &regs->WinBase);
			mb();
			ग_लिखोl(पंचांगp, &regs->WinData);
			mb();
			segptr += 4;
			sptr += 4;
		पूर्ण
	पूर्ण

out:
	ग_लिखोl(localctrl, &regs->LocalCtrl);
	mb();
	वापस 0;
पूर्ण


अटल पूर्णांक rr_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा rr_निजी *rrpriv;
	अचिन्हित अक्षर *image, *oldimage;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;
	पूर्णांक error = -EOPNOTSUPP;

	rrpriv = netdev_priv(dev);

	चयन(cmd)अणु
	हाल SIOCRRGFW:
		अगर (!capable(CAP_SYS_RAWIO))अणु
			वापस -EPERM;
		पूर्ण

		image = kदो_स्मृति_array(EEPROM_WORDS, माप(u32), GFP_KERNEL);
		अगर (!image)
			वापस -ENOMEM;

		अगर (rrpriv->fw_running)अणु
			prपूर्णांकk("%s: Firmware already running\n", dev->name);
			error = -EPERM;
			जाओ gf_out;
		पूर्ण

		spin_lock_irqsave(&rrpriv->lock, flags);
		i = rr_पढ़ो_eeprom(rrpriv, 0, image, EEPROM_BYTES);
		spin_unlock_irqrestore(&rrpriv->lock, flags);
		अगर (i != EEPROM_BYTES)अणु
			prपूर्णांकk(KERN_ERR "%s: Error reading EEPROM\n",
			       dev->name);
			error = -EFAULT;
			जाओ gf_out;
		पूर्ण
		error = copy_to_user(rq->अगरr_data, image, EEPROM_BYTES);
		अगर (error)
			error = -EFAULT;
	gf_out:
		kमुक्त(image);
		वापस error;

	हाल SIOCRRPFW:
		अगर (!capable(CAP_SYS_RAWIO))अणु
			वापस -EPERM;
		पूर्ण

		image = memdup_user(rq->अगरr_data, EEPROM_BYTES);
		अगर (IS_ERR(image))
			वापस PTR_ERR(image);

		oldimage = kदो_स्मृति(EEPROM_BYTES, GFP_KERNEL);
		अगर (!oldimage) अणु
			kमुक्त(image);
			वापस -ENOMEM;
		पूर्ण

		अगर (rrpriv->fw_running)अणु
			prपूर्णांकk("%s: Firmware already running\n", dev->name);
			error = -EPERM;
			जाओ wf_out;
		पूर्ण

		prपूर्णांकk("%s: Updating EEPROM firmware\n", dev->name);

		spin_lock_irqsave(&rrpriv->lock, flags);
		error = ग_लिखो_eeprom(rrpriv, 0, image, EEPROM_BYTES);
		अगर (error)
			prपूर्णांकk(KERN_ERR "%s: Error writing EEPROM\n",
			       dev->name);

		i = rr_पढ़ो_eeprom(rrpriv, 0, oldimage, EEPROM_BYTES);
		spin_unlock_irqrestore(&rrpriv->lock, flags);

		अगर (i != EEPROM_BYTES)
			prपूर्णांकk(KERN_ERR "%s: Error reading back EEPROM "
			       "image\n", dev->name);

		error = स_भेद(image, oldimage, EEPROM_BYTES);
		अगर (error)अणु
			prपूर्णांकk(KERN_ERR "%s: Error verifying EEPROM image\n",
			       dev->name);
			error = -EFAULT;
		पूर्ण
	wf_out:
		kमुक्त(oldimage);
		kमुक्त(image);
		वापस error;

	हाल SIOCRRID:
		वापस put_user(0x52523032, (पूर्णांक __user *)rq->अगरr_data);
	शेष:
		वापस error;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा pci_device_id rr_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_ESSENTIAL, PCI_DEVICE_ID_ESSENTIAL_ROADRUNNER,
		PCI_ANY_ID, PCI_ANY_ID, पूर्ण,
	अणु 0,पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, rr_pci_tbl);

अटल काष्ठा pci_driver rr_driver = अणु
	.name		= "rrunner",
	.id_table	= rr_pci_tbl,
	.probe		= rr_init_one,
	.हटाओ		= rr_हटाओ_one,
पूर्ण;

module_pci_driver(rr_driver);
