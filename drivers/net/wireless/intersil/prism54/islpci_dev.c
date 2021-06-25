<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2002 Intersil Americas Inc.
 *  Copyright (C) 2003 Herbert Valerio Riedel <hvr@gnu.org>
 *  Copyright (C) 2003 Luis R. Rodriguez <mcgrof@ruslug.rutgers.edu>
 */

#समावेश <linux/hardirq.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/pci.h>
#समावेश <linux/sched.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/अगर_arp.h>

#समावेश <यंत्र/पन.स>

#समावेश "prismcompat.h"
#समावेश "isl_38xx.h"
#समावेश "isl_ioctl.h"
#समावेश "islpci_dev.h"
#समावेश "islpci_mgt.h"
#समावेश "islpci_eth.h"
#समावेश "oid_mgt.h"

#घोषणा ISL3877_IMAGE_खाता	"isl3877"
#घोषणा ISL3886_IMAGE_खाता	"isl3886"
#घोषणा ISL3890_IMAGE_खाता	"isl3890"
MODULE_FIRMWARE(ISL3877_IMAGE_खाता);
MODULE_FIRMWARE(ISL3886_IMAGE_खाता);
MODULE_FIRMWARE(ISL3890_IMAGE_खाता);

अटल पूर्णांक prism54_bring_करोwn(islpci_निजी *);
अटल पूर्णांक islpci_alloc_memory(islpci_निजी *);

/* Temporary dummy MAC address to use until firmware is loaded.
 * The idea there is that some tools (such as nameअगर) may query
 * the MAC address beक्रमe the netdev is 'open'. By using a valid
 * OUI prefix, they can process the netdev properly.
 * Of course, this is not the final/real MAC address. It करोesn't
 * matter, as you are suppose to be able to change it anyसमय via
 * ndev->set_mac_address. Jean II */
अटल स्थिर अचिन्हित अक्षर	dummy_mac[6] = अणु 0x00, 0x30, 0xB4, 0x00, 0x00, 0x00 पूर्ण;

अटल पूर्णांक
isl_upload_firmware(islpci_निजी *priv)
अणु
	u32 reg, rc;
	व्योम __iomem *device_base = priv->device_base;

	/* clear the RAMBoot and the Reset bit */
	reg = पढ़ोl(device_base + ISL38XX_CTRL_STAT_REG);
	reg &= ~ISL38XX_CTRL_STAT_RESET;
	reg &= ~ISL38XX_CTRL_STAT_RAMBOOT;
	ग_लिखोl(reg, device_base + ISL38XX_CTRL_STAT_REG);
	wmb();
	udelay(ISL38XX_WRITEIO_DELAY);

	/* set the Reset bit without पढ़ोing the रेजिस्टर ! */
	reg |= ISL38XX_CTRL_STAT_RESET;
	ग_लिखोl(reg, device_base + ISL38XX_CTRL_STAT_REG);
	wmb();
	udelay(ISL38XX_WRITEIO_DELAY);

	/* clear the Reset bit */
	reg &= ~ISL38XX_CTRL_STAT_RESET;
	ग_लिखोl(reg, device_base + ISL38XX_CTRL_STAT_REG);
	wmb();

	/* रुको a जबतक क्रम the device to reboot */
	mdelay(50);

	अणु
		स्थिर काष्ठा firmware *fw_entry = शून्य;
		दीर्घ fw_len;
		स्थिर u32 *fw_ptr;

		rc = request_firmware(&fw_entry, priv->firmware, PRISM_FW_PDEV);
		अगर (rc) अणु
			prपूर्णांकk(KERN_ERR
			       "%s: request_firmware() failed for '%s'\n",
			       "prism54", priv->firmware);
			वापस rc;
		पूर्ण
		/* prepare the Direct Memory Base रेजिस्टर */
		reg = ISL38XX_DEV_FIRMWARE_ADDRES;

		fw_ptr = (u32 *) fw_entry->data;
		fw_len = fw_entry->size;

		अगर (fw_len % 4) अणु
			prपूर्णांकk(KERN_ERR
			       "%s: firmware '%s' size is not multiple of 32bit, aborting!\n",
			       "prism54", priv->firmware);
			release_firmware(fw_entry);
			वापस -EILSEQ; /* Illegal byte sequence  */;
		पूर्ण

		जबतक (fw_len > 0) अणु
			दीर्घ _fw_len =
			    (fw_len >
			     ISL38XX_MEMORY_WINDOW_SIZE) ?
			    ISL38XX_MEMORY_WINDOW_SIZE : fw_len;
			u32 __iomem *dev_fw_ptr = device_base + ISL38XX_सूचीECT_MEM_WIN;

			/* set the card's base address क्रम writing the data */
			isl38xx_w32_flush(device_base, reg,
					  ISL38XX_सूची_MEM_BASE_REG);
			wmb();	/* be paranoid */

			/* increment the ग_लिखो address क्रम next iteration */
			reg += _fw_len;
			fw_len -= _fw_len;

			/* ग_लिखो the data to the Direct Memory Winकरोw 32bit-wise */
			/* स_नकल_toio() करोesn't guarantee 32bit ग_लिखोs :-| */
			जबतक (_fw_len > 0) अणु
				/* use non-swapping ग_लिखोl() */
				__raw_ग_लिखोl(*fw_ptr, dev_fw_ptr);
				fw_ptr++, dev_fw_ptr++;
				_fw_len -= 4;
			पूर्ण

			/* flush PCI posting */
			(व्योम) पढ़ोl(device_base + ISL38XX_PCI_POSTING_FLUSH);
			wmb();	/* be paranoid again */

			BUG_ON(_fw_len != 0);
		पूर्ण

		BUG_ON(fw_len != 0);

		/* Firmware version is at offset 40 (also क्रम "newmac") */
		prपूर्णांकk(KERN_DEBUG "%s: firmware version: %.8s\n",
		       priv->ndev->name, fw_entry->data + 40);

		release_firmware(fw_entry);
	पूर्ण

	/* now reset the device
	 * clear the Reset & ClkRun bit, set the RAMBoot bit */
	reg = पढ़ोl(device_base + ISL38XX_CTRL_STAT_REG);
	reg &= ~ISL38XX_CTRL_STAT_CLKRUN;
	reg &= ~ISL38XX_CTRL_STAT_RESET;
	reg |= ISL38XX_CTRL_STAT_RAMBOOT;
	isl38xx_w32_flush(device_base, reg, ISL38XX_CTRL_STAT_REG);
	wmb();
	udelay(ISL38XX_WRITEIO_DELAY);

	/* set the reset bit latches the host override and RAMBoot bits
	 * पूर्णांकo the device क्रम operation when the reset bit is reset */
	reg |= ISL38XX_CTRL_STAT_RESET;
	ग_लिखोl(reg, device_base + ISL38XX_CTRL_STAT_REG);
	/* करोn't करो flush PCI posting here! */
	wmb();
	udelay(ISL38XX_WRITEIO_DELAY);

	/* clear the reset bit should start the whole circus */
	reg &= ~ISL38XX_CTRL_STAT_RESET;
	ग_लिखोl(reg, device_base + ISL38XX_CTRL_STAT_REG);
	/* करोn't करो flush PCI posting here! */
	wmb();
	udelay(ISL38XX_WRITEIO_DELAY);

	वापस 0;
पूर्ण

/******************************************************************************
    Device Interrupt Handler
******************************************************************************/

irqवापस_t
islpci_पूर्णांकerrupt(पूर्णांक irq, व्योम *config)
अणु
	u32 reg;
	islpci_निजी *priv = config;
	काष्ठा net_device *ndev = priv->ndev;
	व्योम __iomem *device = priv->device_base;
	पूर्णांक घातerstate = ISL38XX_PSM_POWERSAVE_STATE;

	/* lock the पूर्णांकerrupt handler */
	spin_lock(&priv->slock);

	/* received an पूर्णांकerrupt request on a shared IRQ line
	 * first check whether the device is in sleep mode */
	reg = पढ़ोl(device + ISL38XX_CTRL_STAT_REG);
	अगर (reg & ISL38XX_CTRL_STAT_SLEEPMODE)
		/* device is in sleep mode, IRQ was generated by someone अन्यथा */
	अणु
#अगर VERBOSE > SHOW_ERROR_MESSAGES
		DEBUG(SHOW_TRACING, "Assuming someone else called the IRQ\n");
#पूर्ण_अगर
		spin_unlock(&priv->slock);
		वापस IRQ_NONE;
	पूर्ण


	/* check whether there is any source of पूर्णांकerrupt on the device */
	reg = पढ़ोl(device + ISL38XX_INT_IDENT_REG);

	/* also check the contents of the Interrupt Enable Register, because this
	 * will filter out पूर्णांकerrupt sources from other devices on the same irq ! */
	reg &= पढ़ोl(device + ISL38XX_INT_EN_REG);
	reg &= ISL38XX_INT_SOURCES;

	अगर (reg != 0) अणु
		अगर (islpci_get_state(priv) != PRV_STATE_SLEEP)
			घातerstate = ISL38XX_PSM_ACTIVE_STATE;

		/* reset the request bits in the Identअगरication रेजिस्टर */
		isl38xx_w32_flush(device, reg, ISL38XX_INT_ACK_REG);

#अगर VERBOSE > SHOW_ERROR_MESSAGES
		DEBUG(SHOW_FUNCTION_CALLS,
		      "IRQ: Identification register 0x%p 0x%x\n", device, reg);
#पूर्ण_अगर

		/* check क्रम each bit in the रेजिस्टर separately */
		अगर (reg & ISL38XX_INT_IDENT_UPDATE) अणु
#अगर VERBOSE > SHOW_ERROR_MESSAGES
			/* Queue has been updated */
			DEBUG(SHOW_TRACING, "IRQ: Update flag\n");

			DEBUG(SHOW_QUEUE_INDEXES,
			      "CB drv Qs: [%i][%i][%i][%i][%i][%i]\n",
			      le32_to_cpu(priv->control_block->
					  driver_curr_frag[0]),
			      le32_to_cpu(priv->control_block->
					  driver_curr_frag[1]),
			      le32_to_cpu(priv->control_block->
					  driver_curr_frag[2]),
			      le32_to_cpu(priv->control_block->
					  driver_curr_frag[3]),
			      le32_to_cpu(priv->control_block->
					  driver_curr_frag[4]),
			      le32_to_cpu(priv->control_block->
					  driver_curr_frag[5])
			    );

			DEBUG(SHOW_QUEUE_INDEXES,
			      "CB dev Qs: [%i][%i][%i][%i][%i][%i]\n",
			      le32_to_cpu(priv->control_block->
					  device_curr_frag[0]),
			      le32_to_cpu(priv->control_block->
					  device_curr_frag[1]),
			      le32_to_cpu(priv->control_block->
					  device_curr_frag[2]),
			      le32_to_cpu(priv->control_block->
					  device_curr_frag[3]),
			      le32_to_cpu(priv->control_block->
					  device_curr_frag[4]),
			      le32_to_cpu(priv->control_block->
					  device_curr_frag[5])
			    );
#पूर्ण_अगर

			/* cleanup the data low transmit queue */
			islpci_eth_cleanup_transmit(priv, priv->control_block);

			/* device is in active state, update the
			 * घातerstate flag अगर necessary */
			घातerstate = ISL38XX_PSM_ACTIVE_STATE;

			/* check all three queues in priority order
			 * call the PIMFOR receive function until the
			 * queue is empty */
			अगर (isl38xx_in_queue(priv->control_block,
						ISL38XX_CB_RX_MGMTQ) != 0) अणु
#अगर VERBOSE > SHOW_ERROR_MESSAGES
				DEBUG(SHOW_TRACING,
				      "Received frame in Management Queue\n");
#पूर्ण_अगर
				islpci_mgt_receive(ndev);

				islpci_mgt_cleanup_transmit(ndev);

				/* Refill slots in receive queue */
				islpci_mgmt_rx_fill(ndev);

				/* no need to trigger the device, next
                                   islpci_mgt_transaction करोes it */
			पूर्ण

			जबतक (isl38xx_in_queue(priv->control_block,
						ISL38XX_CB_RX_DATA_LQ) != 0) अणु
#अगर VERBOSE > SHOW_ERROR_MESSAGES
				DEBUG(SHOW_TRACING,
				      "Received frame in Data Low Queue\n");
#पूर्ण_अगर
				islpci_eth_receive(priv);
			पूर्ण

			/* check whether the data transmit queues were full */
			अगर (priv->data_low_tx_full) अणु
				/* check whether the transmit is not full anymore */
				अगर (ISL38XX_CB_TX_QSIZE -
				    isl38xx_in_queue(priv->control_block,
						     ISL38XX_CB_TX_DATA_LQ) >=
				    ISL38XX_MIN_QTHRESHOLD) अणु
					/* nope, the driver is पढ़ोy क्रम more network frames */
					netअगर_wake_queue(priv->ndev);

					/* reset the full flag */
					priv->data_low_tx_full = 0;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (reg & ISL38XX_INT_IDENT_INIT) अणु
			/* Device has been initialized */
#अगर VERBOSE > SHOW_ERROR_MESSAGES
			DEBUG(SHOW_TRACING,
			      "IRQ: Init flag, device initialized\n");
#पूर्ण_अगर
			wake_up(&priv->reset_करोne);
		पूर्ण

		अगर (reg & ISL38XX_INT_IDENT_SLEEP) अणु
			/* Device पूर्णांकends to move to घातersave state */
#अगर VERBOSE > SHOW_ERROR_MESSAGES
			DEBUG(SHOW_TRACING, "IRQ: Sleep flag\n");
#पूर्ण_अगर
			isl38xx_handle_sleep_request(priv->control_block,
						     &घातerstate,
						     priv->device_base);
		पूर्ण

		अगर (reg & ISL38XX_INT_IDENT_WAKEUP) अणु
			/* Device has been woken up to active state */
#अगर VERBOSE > SHOW_ERROR_MESSAGES
			DEBUG(SHOW_TRACING, "IRQ: Wakeup flag\n");
#पूर्ण_अगर

			isl38xx_handle_wakeup(priv->control_block,
					      &घातerstate, priv->device_base);
		पूर्ण
	पूर्ण अन्यथा अणु
#अगर VERBOSE > SHOW_ERROR_MESSAGES
		DEBUG(SHOW_TRACING, "Assuming someone else called the IRQ\n");
#पूर्ण_अगर
		spin_unlock(&priv->slock);
		वापस IRQ_NONE;
	पूर्ण

	/* sleep -> पढ़ोy */
	अगर (islpci_get_state(priv) == PRV_STATE_SLEEP
	    && घातerstate == ISL38XX_PSM_ACTIVE_STATE)
		islpci_set_state(priv, PRV_STATE_READY);

	/* !sleep -> sleep */
	अगर (islpci_get_state(priv) != PRV_STATE_SLEEP
	    && घातerstate == ISL38XX_PSM_POWERSAVE_STATE)
		islpci_set_state(priv, PRV_STATE_SLEEP);

	/* unlock the पूर्णांकerrupt handler */
	spin_unlock(&priv->slock);

	वापस IRQ_HANDLED;
पूर्ण

/******************************************************************************
    Network Interface Control & Statistical functions
******************************************************************************/
अटल पूर्णांक
islpci_खोलो(काष्ठा net_device *ndev)
अणु
	u32 rc;
	islpci_निजी *priv = netdev_priv(ndev);

	/* reset data काष्ठाures, upload firmware and reset device */
	rc = islpci_reset(priv,1);
	अगर (rc) अणु
		prism54_bring_करोwn(priv);
		वापस rc; /* Returns inक्रमmative message */
	पूर्ण

	netअगर_start_queue(ndev);

	/* Turn off carrier अगर in STA or Ad-hoc mode. It will be turned on
	 * once the firmware receives a trap of being associated
	 * (GEN_OID_LINKSTATE). In other modes (AP or WDS or monitor) we
	 * should just leave the carrier on as its expected the firmware
	 * won't send us a trigger. */
	अगर (priv->iw_mode == IW_MODE_INFRA || priv->iw_mode == IW_MODE_ADHOC)
		netअगर_carrier_off(ndev);
	अन्यथा
		netअगर_carrier_on(ndev);

	वापस 0;
पूर्ण

अटल पूर्णांक
islpci_बंद(काष्ठा net_device *ndev)
अणु
	islpci_निजी *priv = netdev_priv(ndev);

	prपूर्णांकk(KERN_DEBUG "%s: islpci_close ()\n", ndev->name);

	netअगर_stop_queue(ndev);

	वापस prism54_bring_करोwn(priv);
पूर्ण

अटल पूर्णांक
prism54_bring_करोwn(islpci_निजी *priv)
अणु
	व्योम __iomem *device_base = priv->device_base;
	u32 reg;
	/* we are going to shutकरोwn the device */
	islpci_set_state(priv, PRV_STATE_PREBOOT);

	/* disable all device पूर्णांकerrupts in हाल they weren't */
	isl38xx_disable_पूर्णांकerrupts(priv->device_base);

	/* For safety reasons, we may want to ensure that no DMA transfer is
	 * currently in progress by emptying the TX and RX queues. */

	/* रुको until पूर्णांकerrupts have finished executing on other CPUs */
	synchronize_irq(priv->pdev->irq);

	reg = पढ़ोl(device_base + ISL38XX_CTRL_STAT_REG);
	reg &= ~(ISL38XX_CTRL_STAT_RESET | ISL38XX_CTRL_STAT_RAMBOOT);
	ग_लिखोl(reg, device_base + ISL38XX_CTRL_STAT_REG);
	wmb();
	udelay(ISL38XX_WRITEIO_DELAY);

	reg |= ISL38XX_CTRL_STAT_RESET;
	ग_लिखोl(reg, device_base + ISL38XX_CTRL_STAT_REG);
	wmb();
	udelay(ISL38XX_WRITEIO_DELAY);

	/* clear the Reset bit */
	reg &= ~ISL38XX_CTRL_STAT_RESET;
	ग_लिखोl(reg, device_base + ISL38XX_CTRL_STAT_REG);
	wmb();

	/* रुको a जबतक क्रम the device to reset */
	schedule_समयout_unपूर्णांकerruptible(msecs_to_jअगरfies(50));

	वापस 0;
पूर्ण

अटल पूर्णांक
islpci_upload_fw(islpci_निजी *priv)
अणु
	islpci_state_t old_state;
	u32 rc;

	old_state = islpci_set_state(priv, PRV_STATE_BOOT);

	prपूर्णांकk(KERN_DEBUG "%s: uploading firmware...\n", priv->ndev->name);

	rc = isl_upload_firmware(priv);
	अगर (rc) अणु
		/* error uploading the firmware */
		prपूर्णांकk(KERN_ERR "%s: could not upload firmware ('%s')\n",
		       priv->ndev->name, priv->firmware);

		islpci_set_state(priv, old_state);
		वापस rc;
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "%s: firmware upload complete\n",
	       priv->ndev->name);

	islpci_set_state(priv, PRV_STATE_POSTBOOT);

	वापस 0;
पूर्ण

अटल पूर्णांक
islpci_reset_अगर(islpci_निजी *priv)
अणु
	दीर्घ reमुख्यing;
	पूर्णांक result = -ETIME;
	पूर्णांक count;

	DEFINE_WAIT(रुको);
	prepare_to_रुको(&priv->reset_करोne, &रुको, TASK_UNINTERRUPTIBLE);

	/* now the last step is to reset the पूर्णांकerface */
	isl38xx_पूर्णांकerface_reset(priv->device_base, priv->device_host_address);
	islpci_set_state(priv, PRV_STATE_PREINIT);

        क्रम(count = 0; count < 2 && result; count++) अणु
		/* The software reset acknowledge needs about 220 msec here.
		 * Be conservative and रुको क्रम up to one second. */

		reमुख्यing = schedule_समयout_unपूर्णांकerruptible(HZ);

		अगर(reमुख्यing > 0) अणु
			result = 0;
			अवरोध;
		पूर्ण

		/* If we're here it's because our IRQ hasn't yet gone through.
		 * Retry a bit more...
		 */
		prपूर्णांकk(KERN_ERR "%s: no 'reset complete' IRQ seen - retrying\n",
			priv->ndev->name);
	पूर्ण

	finish_रुको(&priv->reset_करोne, &रुको);

	अगर (result) अणु
		prपूर्णांकk(KERN_ERR "%s: interface reset failure\n", priv->ndev->name);
		वापस result;
	पूर्ण

	islpci_set_state(priv, PRV_STATE_INIT);

	/* Now that the device is 100% up, let's allow
	 * क्रम the other पूर्णांकerrupts --
	 * NOTE: this is not *yet* true since we've only allowed the
	 * INIT पूर्णांकerrupt on the IRQ line. We can perhaps poll
	 * the IRQ line until we know क्रम sure the reset went through */
	isl38xx_enable_common_पूर्णांकerrupts(priv->device_base);

	करोwn_ग_लिखो(&priv->mib_sem);
	result = mgt_commit(priv);
	अगर (result) अणु
		prपूर्णांकk(KERN_ERR "%s: interface reset failure\n", priv->ndev->name);
		up_ग_लिखो(&priv->mib_sem);
		वापस result;
	पूर्ण
	up_ग_लिखो(&priv->mib_sem);

	islpci_set_state(priv, PRV_STATE_READY);

	prपूर्णांकk(KERN_DEBUG "%s: interface reset complete\n", priv->ndev->name);
	वापस 0;
पूर्ण

पूर्णांक
islpci_reset(islpci_निजी *priv, पूर्णांक reload_firmware)
अणु
	isl38xx_control_block *cb =    /* अस्थिर not needed */
		(isl38xx_control_block *) priv->control_block;
	अचिन्हित counter;
	पूर्णांक rc;

	अगर (reload_firmware)
		islpci_set_state(priv, PRV_STATE_PREBOOT);
	अन्यथा
		islpci_set_state(priv, PRV_STATE_POSTBOOT);

	prपूर्णांकk(KERN_DEBUG "%s: resetting device...\n", priv->ndev->name);

	/* disable all device पूर्णांकerrupts in हाल they weren't */
	isl38xx_disable_पूर्णांकerrupts(priv->device_base);

	/* flush all management queues */
	priv->index_mgmt_tx = 0;
	priv->index_mgmt_rx = 0;

	/* clear the indexes in the frame poपूर्णांकer */
	क्रम (counter = 0; counter < ISL38XX_CB_QCOUNT; counter++) अणु
		cb->driver_curr_frag[counter] = cpu_to_le32(0);
		cb->device_curr_frag[counter] = cpu_to_le32(0);
	पूर्ण

	/* reset the mgmt receive queue */
	क्रम (counter = 0; counter < ISL38XX_CB_MGMT_QSIZE; counter++) अणु
		isl38xx_fragment *frag = &cb->rx_data_mgmt[counter];
		frag->size = cpu_to_le16(MGMT_FRAME_SIZE);
		frag->flags = 0;
		frag->address = cpu_to_le32(priv->mgmt_rx[counter].pci_addr);
	पूर्ण

	क्रम (counter = 0; counter < ISL38XX_CB_RX_QSIZE; counter++) अणु
		cb->rx_data_low[counter].address =
		    cpu_to_le32((u32) priv->pci_map_rx_address[counter]);
	पूर्ण

	/* since the receive queues are filled with empty fragments, now we can
	 * set the corresponding indexes in the Control Block */
	priv->control_block->driver_curr_frag[ISL38XX_CB_RX_DATA_LQ] =
	    cpu_to_le32(ISL38XX_CB_RX_QSIZE);
	priv->control_block->driver_curr_frag[ISL38XX_CB_RX_MGMTQ] =
	    cpu_to_le32(ISL38XX_CB_MGMT_QSIZE);

	/* reset the reमुख्यing real index रेजिस्टरs and full flags */
	priv->मुक्त_data_rx = 0;
	priv->मुक्त_data_tx = 0;
	priv->data_low_tx_full = 0;

	अगर (reload_firmware) अणु /* Should we load the firmware ? */
	/* now that the data काष्ठाures are cleaned up, upload
	 * firmware and reset पूर्णांकerface */
		rc = islpci_upload_fw(priv);
		अगर (rc) अणु
			prपूर्णांकk(KERN_ERR "%s: islpci_reset: failure\n",
				priv->ndev->name);
			वापस rc;
		पूर्ण
	पूर्ण

	/* finally reset पूर्णांकerface */
	rc = islpci_reset_अगर(priv);
	अगर (rc)
		prपूर्णांकk(KERN_ERR "prism54: Your card/socket may be faulty, or IRQ line too busy :(\n");
	वापस rc;
पूर्ण

/******************************************************************************
    Network device configuration functions
******************************************************************************/
अटल पूर्णांक
islpci_alloc_memory(islpci_निजी *priv)
अणु
	पूर्णांक counter;

#अगर VERBOSE > SHOW_ERROR_MESSAGES
	prपूर्णांकk(KERN_DEBUG "islpci_alloc_memory\n");
#पूर्ण_अगर

	/* remap the PCI device base address to accessible */
	अगर (!(priv->device_base =
	      ioremap(pci_resource_start(priv->pdev, 0),
		      ISL38XX_PCI_MEM_SIZE))) अणु
		/* error in remapping the PCI device memory address range */
		prपूर्णांकk(KERN_ERR "PCI memory remapping failed\n");
		वापस -1;
	पूर्ण

	/* memory layout क्रम consistent DMA region:
	 *
	 * Area 1: Control Block क्रम the device पूर्णांकerface
	 * Area 2: Power Save Mode Buffer क्रम temporary frame storage. Be aware that
	 *         the number of supported stations in the AP determines the minimal
	 *         size of the buffer !
	 */

	/* perक्रमm the allocation */
	priv->driver_mem_address = dma_alloc_coherent(&priv->pdev->dev,
						      HOST_MEM_BLOCK,
						      &priv->device_host_address,
						      GFP_KERNEL);

	अगर (!priv->driver_mem_address) अणु
		/* error allocating the block of PCI memory */
		prपूर्णांकk(KERN_ERR "%s: could not allocate DMA memory, aborting!",
		       "prism54");
		वापस -1;
	पूर्ण

	/* assign the Control Block to the first address of the allocated area */
	priv->control_block =
	    (isl38xx_control_block *) priv->driver_mem_address;

	/* set the Power Save Buffer poपूर्णांकer directly behind the CB */
	priv->device_psm_buffer =
		priv->device_host_address + CONTROL_BLOCK_SIZE;

	/* make sure all buffer poपूर्णांकers are initialized */
	क्रम (counter = 0; counter < ISL38XX_CB_QCOUNT; counter++) अणु
		priv->control_block->driver_curr_frag[counter] = cpu_to_le32(0);
		priv->control_block->device_curr_frag[counter] = cpu_to_le32(0);
	पूर्ण

	priv->index_mgmt_rx = 0;
	स_रखो(priv->mgmt_rx, 0, माप(priv->mgmt_rx));
	स_रखो(priv->mgmt_tx, 0, माप(priv->mgmt_tx));

	/* allocate rx queue क्रम management frames */
	अगर (islpci_mgmt_rx_fill(priv->ndev) < 0)
		जाओ out_मुक्त;

	/* now get the data rx skb's */
	स_रखो(priv->data_low_rx, 0, माप (priv->data_low_rx));
	स_रखो(priv->pci_map_rx_address, 0, माप (priv->pci_map_rx_address));

	क्रम (counter = 0; counter < ISL38XX_CB_RX_QSIZE; counter++) अणु
		काष्ठा sk_buff *skb;

		/* allocate an sk_buff क्रम received data frames storage
		 * each frame on receive size consists of 1 fragment
		 * include any required allignment operations */
		अगर (!(skb = dev_alloc_skb(MAX_FRAGMENT_SIZE_RX + 2))) अणु
			/* error allocating an sk_buff काष्ठाure elements */
			prपूर्णांकk(KERN_ERR "Error allocating skb.\n");
			skb = शून्य;
			जाओ out_मुक्त;
		पूर्ण
		skb_reserve(skb, (4 - (दीर्घ) skb->data) & 0x03);
		/* add the new allocated sk_buff to the buffer array */
		priv->data_low_rx[counter] = skb;

		/* map the allocated skb data area to pci */
		priv->pci_map_rx_address[counter] =
		    dma_map_single(&priv->pdev->dev, (व्योम *)skb->data,
				   MAX_FRAGMENT_SIZE_RX + 2, DMA_FROM_DEVICE);
		अगर (dma_mapping_error(&priv->pdev->dev, priv->pci_map_rx_address[counter])) अणु
			priv->pci_map_rx_address[counter] = 0;
			/* error mapping the buffer to device
			   accessible memory address */
			prपूर्णांकk(KERN_ERR "failed to map skb DMA'able\n");
			जाओ out_मुक्त;
		पूर्ण
	पूर्ण

	prism54_acl_init(&priv->acl);
	prism54_wpa_bss_ie_init(priv);
	अगर (mgt_init(priv))
		जाओ out_मुक्त;

	वापस 0;
 out_मुक्त:
	islpci_मुक्त_memory(priv);
	वापस -1;
पूर्ण

पूर्णांक
islpci_मुक्त_memory(islpci_निजी *priv)
अणु
	पूर्णांक counter;

	अगर (priv->device_base)
		iounmap(priv->device_base);
	priv->device_base = शून्य;

	/* मुक्त consistent DMA area... */
	अगर (priv->driver_mem_address)
		dma_मुक्त_coherent(&priv->pdev->dev, HOST_MEM_BLOCK,
				  priv->driver_mem_address,
				  priv->device_host_address);

	/* clear some dangling poपूर्णांकers */
	priv->driver_mem_address = शून्य;
	priv->device_host_address = 0;
	priv->device_psm_buffer = 0;
	priv->control_block = शून्य;

        /* clean up mgmt rx buffers */
        क्रम (counter = 0; counter < ISL38XX_CB_MGMT_QSIZE; counter++) अणु
		काष्ठा islpci_membuf *buf = &priv->mgmt_rx[counter];
		अगर (buf->pci_addr)
			dma_unmap_single(&priv->pdev->dev, buf->pci_addr,
					 buf->size, DMA_FROM_DEVICE);
		buf->pci_addr = 0;
		kमुक्त(buf->mem);
		buf->size = 0;
		buf->mem = शून्य;
        पूर्ण

	/* clean up data rx buffers */
	क्रम (counter = 0; counter < ISL38XX_CB_RX_QSIZE; counter++) अणु
		अगर (priv->pci_map_rx_address[counter])
			dma_unmap_single(&priv->pdev->dev,
					 priv->pci_map_rx_address[counter],
					 MAX_FRAGMENT_SIZE_RX + 2,
					 DMA_FROM_DEVICE);
		priv->pci_map_rx_address[counter] = 0;

		अगर (priv->data_low_rx[counter])
			dev_kमुक्त_skb(priv->data_low_rx[counter]);
		priv->data_low_rx[counter] = शून्य;
	पूर्ण

	/* Free the access control list and the WPA list */
	prism54_acl_clean(&priv->acl);
	prism54_wpa_bss_ie_clean(priv);
	mgt_clean(priv);

	वापस 0;
पूर्ण

#अगर 0
अटल व्योम
islpci_set_multicast_list(काष्ठा net_device *dev)
अणु
	/* put device पूर्णांकo promisc mode and let network layer handle it */
पूर्ण
#पूर्ण_अगर

अटल व्योम islpci_ethtool_get_drvinfo(काष्ठा net_device *dev,
                                       काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, DRV_NAME, माप(info->driver));
	strlcpy(info->version, DRV_VERSION, माप(info->version));
पूर्ण

अटल स्थिर काष्ठा ethtool_ops islpci_ethtool_ops = अणु
	.get_drvinfo = islpci_ethtool_get_drvinfo,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops islpci_netdev_ops = अणु
	.nकरो_खोलो 		= islpci_खोलो,
	.nकरो_stop		= islpci_बंद,
	.nकरो_start_xmit		= islpci_eth_transmit,
	.nकरो_tx_समयout		= islpci_eth_tx_समयout,
	.nकरो_set_mac_address 	= prism54_set_mac_address,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल काष्ठा device_type wlan_type = अणु
	.name	= "wlan",
पूर्ण;

काष्ठा net_device *
islpci_setup(काष्ठा pci_dev *pdev)
अणु
	islpci_निजी *priv;
	काष्ठा net_device *ndev = alloc_etherdev(माप (islpci_निजी));

	अगर (!ndev)
		वापस ndev;

	pci_set_drvdata(pdev, ndev);
	SET_NETDEV_DEV(ndev, &pdev->dev);
	SET_NETDEV_DEVTYPE(ndev, &wlan_type);

	/* setup the काष्ठाure members */
	ndev->base_addr = pci_resource_start(pdev, 0);
	ndev->irq = pdev->irq;

	/* initialize the function poपूर्णांकers */
	ndev->netdev_ops = &islpci_netdev_ops;
	ndev->wireless_handlers = &prism54_handler_def;
	ndev->ethtool_ops = &islpci_ethtool_ops;

	/* ndev->set_multicast_list = &islpci_set_multicast_list; */
	ndev->addr_len = ETH_ALEN;
	/* Get a non-zero dummy MAC address क्रम nameअगर. Jean II */
	स_नकल(ndev->dev_addr, dummy_mac, ETH_ALEN);

	ndev->watchकरोg_समयo = ISLPCI_TX_TIMEOUT;

	/* allocate a निजी device काष्ठाure to the network device  */
	priv = netdev_priv(ndev);
	priv->ndev = ndev;
	priv->pdev = pdev;
	priv->monitor_type = ARPHRD_IEEE80211;
	priv->ndev->type = (priv->iw_mode == IW_MODE_MONITOR) ?
		priv->monitor_type : ARPHRD_ETHER;

	/* Add poपूर्णांकers to enable iwspy support. */
	priv->wireless_data.spy_data = &priv->spy_data;
	ndev->wireless_data = &priv->wireless_data;

	/* save the start and end address of the PCI memory area */
	ndev->mem_start = (अचिन्हित दीर्घ) priv->device_base;
	ndev->mem_end = ndev->mem_start + ISL38XX_PCI_MEM_SIZE;

#अगर VERBOSE > SHOW_ERROR_MESSAGES
	DEBUG(SHOW_TRACING, "PCI Memory remapped to 0x%p\n", priv->device_base);
#पूर्ण_अगर

	init_रुकोqueue_head(&priv->reset_करोne);

	/* init the queue पढ़ो locks, process रुको counter */
	mutex_init(&priv->mgmt_lock);
	priv->mgmt_received = शून्य;
	init_रुकोqueue_head(&priv->mgmt_wqueue);
	mutex_init(&priv->stats_lock);
	spin_lock_init(&priv->slock);

	/* init state machine with off#1 state */
	priv->state = PRV_STATE_OFF;
	priv->state_off = 1;

	/* initialize workqueue's */
	INIT_WORK(&priv->stats_work, prism54_update_stats);
	priv->stats_बारtamp = 0;

	INIT_WORK(&priv->reset_task, islpci_करो_reset_and_wake);
	priv->reset_task_pending = 0;

	/* allocate various memory areas */
	अगर (islpci_alloc_memory(priv))
		जाओ करो_मुक्त_netdev;

	/* select the firmware file depending on the device id */
	चयन (pdev->device) अणु
	हाल 0x3877:
		म_नकल(priv->firmware, ISL3877_IMAGE_खाता);
		अवरोध;

	हाल 0x3886:
		म_नकल(priv->firmware, ISL3886_IMAGE_खाता);
		अवरोध;

	शेष:
		म_नकल(priv->firmware, ISL3890_IMAGE_खाता);
		अवरोध;
	पूर्ण

	अगर (रेजिस्टर_netdev(ndev)) अणु
		DEBUG(SHOW_ERROR_MESSAGES,
		      "ERROR: register_netdev() failed\n");
		जाओ करो_islpci_मुक्त_memory;
	पूर्ण

	वापस ndev;

      करो_islpci_मुक्त_memory:
	islpci_मुक्त_memory(priv);
      करो_मुक्त_netdev:
	मुक्त_netdev(ndev);
	priv = शून्य;
	वापस शून्य;
पूर्ण

islpci_state_t
islpci_set_state(islpci_निजी *priv, islpci_state_t new_state)
अणु
	islpci_state_t old_state;

	/* lock */
	old_state = priv->state;

	/* this means either a race condition or some serious error in
	 * the driver code */
	चयन (new_state) अणु
	हाल PRV_STATE_OFF:
		priv->state_off++;
		fallthrough;
	शेष:
		priv->state = new_state;
		अवरोध;

	हाल PRV_STATE_PREBOOT:
		/* there are actually many off-states, क्रमागतerated by
		 * state_off */
		अगर (old_state == PRV_STATE_OFF)
			priv->state_off--;

		/* only अगर hw_unavailable is zero now it means we either
		 * were in off#1 state, or came here from
		 * somewhere अन्यथा */
		अगर (!priv->state_off)
			priv->state = new_state;
		अवरोध;
	पूर्ण
#अगर 0
	prपूर्णांकk(KERN_DEBUG "%s: state transition %d -> %d (off#%d)\n",
	       priv->ndev->name, old_state, new_state, priv->state_off);
#पूर्ण_अगर

	/* invariants */
	BUG_ON(priv->state_off < 0);
	BUG_ON(priv->state_off && (priv->state != PRV_STATE_OFF));
	BUG_ON(!priv->state_off && (priv->state == PRV_STATE_OFF));

	/* unlock */
	वापस old_state;
पूर्ण
