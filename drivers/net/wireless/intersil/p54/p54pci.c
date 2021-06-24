<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

/*
 * Linux device driver क्रम PCI based Prism54
 *
 * Copyright (c) 2006, Michael Wu <flamingice@sourmilk.net>
 * Copyright (c) 2008, Christian Lamparter <chunkeey@web.de>
 *
 * Based on the islsm (sofपंचांगac prism54) driver, which is:
 * Copyright 2004-2006 Jean-Baptiste Note <jean-baptiste.note@m4x.org>, et al.
 */

#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/firmware.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/completion.h>
#समावेश <linux/module.h>
#समावेश <net/mac80211.h>

#समावेश "p54.h"
#समावेश "lmac.h"
#समावेश "p54pci.h"

MODULE_AUTHOR("Michael Wu <flamingice@sourmilk.net>");
MODULE_DESCRIPTION("Prism54 PCI wireless driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("prism54pci");
MODULE_FIRMWARE("isl3886pci");

अटल स्थिर काष्ठा pci_device_id p54p_table[] = अणु
	/* Intersil PRISM Duette/Prism GT Wireless LAN adapter */
	अणु PCI_DEVICE(0x1260, 0x3890) पूर्ण,
	/* 3COM 3CRWE154G72 Wireless LAN adapter */
	अणु PCI_DEVICE(0x10b7, 0x6001) पूर्ण,
	/* Intersil PRISM Indigo Wireless LAN adapter */
	अणु PCI_DEVICE(0x1260, 0x3877) पूर्ण,
	/* Intersil PRISM Javelin/Xbow Wireless LAN adapter */
	अणु PCI_DEVICE(0x1260, 0x3886) पूर्ण,
	/* Intersil PRISM Xbow Wireless LAN adapter (Symbol AP-300) */
	अणु PCI_DEVICE(0x1260, 0xffff) पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, p54p_table);

अटल पूर्णांक p54p_upload_firmware(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा p54p_priv *priv = dev->priv;
	__le32 reg;
	पूर्णांक err;
	__le32 *data;
	u32 reमुख्यs, left, device_addr;

	P54P_WRITE(पूर्णांक_enable, cpu_to_le32(0));
	P54P_READ(पूर्णांक_enable);
	udelay(10);

	reg = P54P_READ(ctrl_stat);
	reg &= cpu_to_le32(~ISL38XX_CTRL_STAT_RESET);
	reg &= cpu_to_le32(~ISL38XX_CTRL_STAT_RAMBOOT);
	P54P_WRITE(ctrl_stat, reg);
	P54P_READ(ctrl_stat);
	udelay(10);

	reg |= cpu_to_le32(ISL38XX_CTRL_STAT_RESET);
	P54P_WRITE(ctrl_stat, reg);
	wmb();
	udelay(10);

	reg &= cpu_to_le32(~ISL38XX_CTRL_STAT_RESET);
	P54P_WRITE(ctrl_stat, reg);
	wmb();

	/* रुको क्रम the firmware to reset properly */
	mdelay(10);

	err = p54_parse_firmware(dev, priv->firmware);
	अगर (err)
		वापस err;

	अगर (priv->common.fw_पूर्णांकerface != FW_LM86) अणु
		dev_err(&priv->pdev->dev, "wrong firmware, "
			"please get a LM86(PCI) firmware a try again.\n");
		वापस -EINVAL;
	पूर्ण

	data = (__le32 *) priv->firmware->data;
	reमुख्यs = priv->firmware->size;
	device_addr = ISL38XX_DEV_FIRMWARE_ADDR;
	जबतक (reमुख्यs) अणु
		u32 i = 0;
		left = min((u32)0x1000, reमुख्यs);
		P54P_WRITE(direct_mem_base, cpu_to_le32(device_addr));
		P54P_READ(पूर्णांक_enable);

		device_addr += 0x1000;
		जबतक (i < left) अणु
			P54P_WRITE(direct_mem_win[i], *data++);
			i += माप(u32);
		पूर्ण

		reमुख्यs -= left;
		P54P_READ(पूर्णांक_enable);
	पूर्ण

	reg = P54P_READ(ctrl_stat);
	reg &= cpu_to_le32(~ISL38XX_CTRL_STAT_CLKRUN);
	reg &= cpu_to_le32(~ISL38XX_CTRL_STAT_RESET);
	reg |= cpu_to_le32(ISL38XX_CTRL_STAT_RAMBOOT);
	P54P_WRITE(ctrl_stat, reg);
	P54P_READ(ctrl_stat);
	udelay(10);

	reg |= cpu_to_le32(ISL38XX_CTRL_STAT_RESET);
	P54P_WRITE(ctrl_stat, reg);
	wmb();
	udelay(10);

	reg &= cpu_to_le32(~ISL38XX_CTRL_STAT_RESET);
	P54P_WRITE(ctrl_stat, reg);
	wmb();
	udelay(10);

	/* रुको क्रम the firmware to boot properly */
	mdelay(100);

	वापस 0;
पूर्ण

अटल व्योम p54p_refill_rx_ring(काष्ठा ieee80211_hw *dev,
	पूर्णांक ring_index, काष्ठा p54p_desc *ring, u32 ring_limit,
	काष्ठा sk_buff **rx_buf, u32 index)
अणु
	काष्ठा p54p_priv *priv = dev->priv;
	काष्ठा p54p_ring_control *ring_control = priv->ring_control;
	u32 limit, idx, i;

	idx = le32_to_cpu(ring_control->host_idx[ring_index]);
	limit = idx;
	limit -= index;
	limit = ring_limit - limit;

	i = idx % ring_limit;
	जबतक (limit-- > 1) अणु
		काष्ठा p54p_desc *desc = &ring[i];

		अगर (!desc->host_addr) अणु
			काष्ठा sk_buff *skb;
			dma_addr_t mapping;
			skb = dev_alloc_skb(priv->common.rx_mtu + 32);
			अगर (!skb)
				अवरोध;

			mapping = dma_map_single(&priv->pdev->dev,
						 skb_tail_poपूर्णांकer(skb),
						 priv->common.rx_mtu + 32,
						 DMA_FROM_DEVICE);

			अगर (dma_mapping_error(&priv->pdev->dev, mapping)) अणु
				dev_kमुक्त_skb_any(skb);
				dev_err(&priv->pdev->dev,
					"RX DMA Mapping error\n");
				अवरोध;
			पूर्ण

			desc->host_addr = cpu_to_le32(mapping);
			desc->device_addr = 0;	// FIXME: necessary?
			desc->len = cpu_to_le16(priv->common.rx_mtu + 32);
			desc->flags = 0;
			rx_buf[i] = skb;
		पूर्ण

		i++;
		idx++;
		i %= ring_limit;
	पूर्ण

	wmb();
	ring_control->host_idx[ring_index] = cpu_to_le32(idx);
पूर्ण

अटल व्योम p54p_check_rx_ring(काष्ठा ieee80211_hw *dev, u32 *index,
	पूर्णांक ring_index, काष्ठा p54p_desc *ring, u32 ring_limit,
	काष्ठा sk_buff **rx_buf)
अणु
	काष्ठा p54p_priv *priv = dev->priv;
	काष्ठा p54p_ring_control *ring_control = priv->ring_control;
	काष्ठा p54p_desc *desc;
	u32 idx, i;

	i = (*index) % ring_limit;
	(*index) = idx = le32_to_cpu(ring_control->device_idx[ring_index]);
	idx %= ring_limit;
	जबतक (i != idx) अणु
		u16 len;
		काष्ठा sk_buff *skb;
		dma_addr_t dma_addr;
		desc = &ring[i];
		len = le16_to_cpu(desc->len);
		skb = rx_buf[i];

		अगर (!skb) अणु
			i++;
			i %= ring_limit;
			जारी;
		पूर्ण

		अगर (unlikely(len > priv->common.rx_mtu)) अणु
			अगर (net_ratelimit())
				dev_err(&priv->pdev->dev, "rx'd frame size "
					"exceeds length threshold.\n");

			len = priv->common.rx_mtu;
		पूर्ण
		dma_addr = le32_to_cpu(desc->host_addr);
		dma_sync_single_क्रम_cpu(&priv->pdev->dev, dma_addr,
					priv->common.rx_mtu + 32,
					DMA_FROM_DEVICE);
		skb_put(skb, len);

		अगर (p54_rx(dev, skb)) अणु
			dma_unmap_single(&priv->pdev->dev, dma_addr,
					 priv->common.rx_mtu + 32,
					 DMA_FROM_DEVICE);
			rx_buf[i] = शून्य;
			desc->host_addr = cpu_to_le32(0);
		पूर्ण अन्यथा अणु
			skb_trim(skb, 0);
			dma_sync_single_क्रम_device(&priv->pdev->dev, dma_addr,
						   priv->common.rx_mtu + 32,
						   DMA_FROM_DEVICE);
			desc->len = cpu_to_le16(priv->common.rx_mtu + 32);
		पूर्ण

		i++;
		i %= ring_limit;
	पूर्ण

	p54p_refill_rx_ring(dev, ring_index, ring, ring_limit, rx_buf, *index);
पूर्ण

अटल व्योम p54p_check_tx_ring(काष्ठा ieee80211_hw *dev, u32 *index,
	पूर्णांक ring_index, काष्ठा p54p_desc *ring, u32 ring_limit,
	काष्ठा sk_buff **tx_buf)
अणु
	काष्ठा p54p_priv *priv = dev->priv;
	काष्ठा p54p_ring_control *ring_control = priv->ring_control;
	काष्ठा p54p_desc *desc;
	काष्ठा sk_buff *skb;
	u32 idx, i;

	i = (*index) % ring_limit;
	(*index) = idx = le32_to_cpu(ring_control->device_idx[ring_index]);
	idx %= ring_limit;

	जबतक (i != idx) अणु
		desc = &ring[i];

		skb = tx_buf[i];
		tx_buf[i] = शून्य;

		dma_unmap_single(&priv->pdev->dev,
				 le32_to_cpu(desc->host_addr),
				 le16_to_cpu(desc->len), DMA_TO_DEVICE);

		desc->host_addr = 0;
		desc->device_addr = 0;
		desc->len = 0;
		desc->flags = 0;

		अगर (skb && FREE_AFTER_TX(skb))
			p54_मुक्त_skb(dev, skb);

		i++;
		i %= ring_limit;
	पूर्ण
पूर्ण

अटल व्योम p54p_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा p54p_priv *priv = from_tasklet(priv, t, tasklet);
	काष्ठा ieee80211_hw *dev = pci_get_drvdata(priv->pdev);
	काष्ठा p54p_ring_control *ring_control = priv->ring_control;

	p54p_check_tx_ring(dev, &priv->tx_idx_mgmt, 3, ring_control->tx_mgmt,
			   ARRAY_SIZE(ring_control->tx_mgmt),
			   priv->tx_buf_mgmt);

	p54p_check_tx_ring(dev, &priv->tx_idx_data, 1, ring_control->tx_data,
			   ARRAY_SIZE(ring_control->tx_data),
			   priv->tx_buf_data);

	p54p_check_rx_ring(dev, &priv->rx_idx_mgmt, 2, ring_control->rx_mgmt,
		ARRAY_SIZE(ring_control->rx_mgmt), priv->rx_buf_mgmt);

	p54p_check_rx_ring(dev, &priv->rx_idx_data, 0, ring_control->rx_data,
		ARRAY_SIZE(ring_control->rx_data), priv->rx_buf_data);

	wmb();
	P54P_WRITE(dev_पूर्णांक, cpu_to_le32(ISL38XX_DEV_INT_UPDATE));
पूर्ण

अटल irqवापस_t p54p_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ieee80211_hw *dev = dev_id;
	काष्ठा p54p_priv *priv = dev->priv;
	__le32 reg;

	reg = P54P_READ(पूर्णांक_ident);
	अगर (unlikely(reg == cpu_to_le32(0xFFFFFFFF))) अणु
		जाओ out;
	पूर्ण
	P54P_WRITE(पूर्णांक_ack, reg);

	reg &= P54P_READ(पूर्णांक_enable);

	अगर (reg & cpu_to_le32(ISL38XX_INT_IDENT_UPDATE))
		tasklet_schedule(&priv->tasklet);
	अन्यथा अगर (reg & cpu_to_le32(ISL38XX_INT_IDENT_INIT))
		complete(&priv->boot_comp);

out:
	वापस reg ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल व्योम p54p_tx(काष्ठा ieee80211_hw *dev, काष्ठा sk_buff *skb)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा p54p_priv *priv = dev->priv;
	काष्ठा p54p_ring_control *ring_control = priv->ring_control;
	काष्ठा p54p_desc *desc;
	dma_addr_t mapping;
	u32 idx, i;
	__le32 device_addr;

	spin_lock_irqsave(&priv->lock, flags);
	idx = le32_to_cpu(ring_control->host_idx[1]);
	i = idx % ARRAY_SIZE(ring_control->tx_data);
	device_addr = ((काष्ठा p54_hdr *)skb->data)->req_id;

	mapping = dma_map_single(&priv->pdev->dev, skb->data, skb->len,
				 DMA_TO_DEVICE);
	अगर (dma_mapping_error(&priv->pdev->dev, mapping)) अणु
		spin_unlock_irqrestore(&priv->lock, flags);
		p54_मुक्त_skb(dev, skb);
		dev_err(&priv->pdev->dev, "TX DMA mapping error\n");
		वापस ;
	पूर्ण
	priv->tx_buf_data[i] = skb;

	desc = &ring_control->tx_data[i];
	desc->host_addr = cpu_to_le32(mapping);
	desc->device_addr = device_addr;
	desc->len = cpu_to_le16(skb->len);
	desc->flags = 0;

	wmb();
	ring_control->host_idx[1] = cpu_to_le32(idx + 1);
	spin_unlock_irqrestore(&priv->lock, flags);

	P54P_WRITE(dev_पूर्णांक, cpu_to_le32(ISL38XX_DEV_INT_UPDATE));
	P54P_READ(dev_पूर्णांक);
पूर्ण

अटल व्योम p54p_stop(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा p54p_priv *priv = dev->priv;
	काष्ठा p54p_ring_control *ring_control = priv->ring_control;
	अचिन्हित पूर्णांक i;
	काष्ठा p54p_desc *desc;

	P54P_WRITE(पूर्णांक_enable, cpu_to_le32(0));
	P54P_READ(पूर्णांक_enable);
	udelay(10);

	मुक्त_irq(priv->pdev->irq, dev);

	tasklet_समाप्त(&priv->tasklet);

	P54P_WRITE(dev_पूर्णांक, cpu_to_le32(ISL38XX_DEV_INT_RESET));

	क्रम (i = 0; i < ARRAY_SIZE(priv->rx_buf_data); i++) अणु
		desc = &ring_control->rx_data[i];
		अगर (desc->host_addr)
			dma_unmap_single(&priv->pdev->dev,
					 le32_to_cpu(desc->host_addr),
					 priv->common.rx_mtu + 32,
					 DMA_FROM_DEVICE);
		kमुक्त_skb(priv->rx_buf_data[i]);
		priv->rx_buf_data[i] = शून्य;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(priv->rx_buf_mgmt); i++) अणु
		desc = &ring_control->rx_mgmt[i];
		अगर (desc->host_addr)
			dma_unmap_single(&priv->pdev->dev,
					 le32_to_cpu(desc->host_addr),
					 priv->common.rx_mtu + 32,
					 DMA_FROM_DEVICE);
		kमुक्त_skb(priv->rx_buf_mgmt[i]);
		priv->rx_buf_mgmt[i] = शून्य;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(priv->tx_buf_data); i++) अणु
		desc = &ring_control->tx_data[i];
		अगर (desc->host_addr)
			dma_unmap_single(&priv->pdev->dev,
					 le32_to_cpu(desc->host_addr),
					 le16_to_cpu(desc->len),
					 DMA_TO_DEVICE);

		p54_मुक्त_skb(dev, priv->tx_buf_data[i]);
		priv->tx_buf_data[i] = शून्य;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(priv->tx_buf_mgmt); i++) अणु
		desc = &ring_control->tx_mgmt[i];
		अगर (desc->host_addr)
			dma_unmap_single(&priv->pdev->dev,
					 le32_to_cpu(desc->host_addr),
					 le16_to_cpu(desc->len),
					 DMA_TO_DEVICE);

		p54_मुक्त_skb(dev, priv->tx_buf_mgmt[i]);
		priv->tx_buf_mgmt[i] = शून्य;
	पूर्ण

	स_रखो(ring_control, 0, माप(*ring_control));
पूर्ण

अटल पूर्णांक p54p_खोलो(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा p54p_priv *priv = dev->priv;
	पूर्णांक err;
	दीर्घ समयout;

	init_completion(&priv->boot_comp);
	err = request_irq(priv->pdev->irq, p54p_पूर्णांकerrupt,
			  IRQF_SHARED, "p54pci", dev);
	अगर (err) अणु
		dev_err(&priv->pdev->dev, "failed to register IRQ handler\n");
		वापस err;
	पूर्ण

	स_रखो(priv->ring_control, 0, माप(*priv->ring_control));
	err = p54p_upload_firmware(dev);
	अगर (err) अणु
		मुक्त_irq(priv->pdev->irq, dev);
		वापस err;
	पूर्ण
	priv->rx_idx_data = priv->tx_idx_data = 0;
	priv->rx_idx_mgmt = priv->tx_idx_mgmt = 0;

	p54p_refill_rx_ring(dev, 0, priv->ring_control->rx_data,
		ARRAY_SIZE(priv->ring_control->rx_data), priv->rx_buf_data, 0);

	p54p_refill_rx_ring(dev, 2, priv->ring_control->rx_mgmt,
		ARRAY_SIZE(priv->ring_control->rx_mgmt), priv->rx_buf_mgmt, 0);

	P54P_WRITE(ring_control_base, cpu_to_le32(priv->ring_control_dma));
	P54P_READ(ring_control_base);
	wmb();
	udelay(10);

	P54P_WRITE(पूर्णांक_enable, cpu_to_le32(ISL38XX_INT_IDENT_INIT));
	P54P_READ(पूर्णांक_enable);
	wmb();
	udelay(10);

	P54P_WRITE(dev_पूर्णांक, cpu_to_le32(ISL38XX_DEV_INT_RESET));
	P54P_READ(dev_पूर्णांक);

	समयout = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
			&priv->boot_comp, HZ);
	अगर (समयout <= 0) अणु
		wiphy_err(dev->wiphy, "Cannot boot firmware!\n");
		p54p_stop(dev);
		वापस समयout ? -ERESTARTSYS : -ETIMEDOUT;
	पूर्ण

	P54P_WRITE(पूर्णांक_enable, cpu_to_le32(ISL38XX_INT_IDENT_UPDATE));
	P54P_READ(पूर्णांक_enable);
	wmb();
	udelay(10);

	P54P_WRITE(dev_पूर्णांक, cpu_to_le32(ISL38XX_DEV_INT_UPDATE));
	P54P_READ(dev_पूर्णांक);
	wmb();
	udelay(10);

	वापस 0;
पूर्ण

अटल व्योम p54p_firmware_step2(स्थिर काष्ठा firmware *fw,
				व्योम *context)
अणु
	काष्ठा p54p_priv *priv = context;
	काष्ठा ieee80211_hw *dev = priv->common.hw;
	काष्ठा pci_dev *pdev = priv->pdev;
	पूर्णांक err;

	अगर (!fw) अणु
		dev_err(&pdev->dev, "Cannot find firmware (isl3886pci)\n");
		err = -ENOENT;
		जाओ out;
	पूर्ण

	priv->firmware = fw;

	err = p54p_खोलो(dev);
	अगर (err)
		जाओ out;
	err = p54_पढ़ो_eeprom(dev);
	p54p_stop(dev);
	अगर (err)
		जाओ out;

	err = p54_रेजिस्टर_common(dev, &pdev->dev);
	अगर (err)
		जाओ out;

out:

	complete(&priv->fw_loaded);

	अगर (err) अणु
		काष्ठा device *parent = pdev->dev.parent;

		अगर (parent)
			device_lock(parent);

		/*
		 * This will indirectly result in a call to p54p_हटाओ.
		 * Hence, we करोn't need to bother with मुक्तing any
		 * allocated ressources at all.
		 */
		device_release_driver(&pdev->dev);

		अगर (parent)
			device_unlock(parent);
	पूर्ण

	pci_dev_put(pdev);
पूर्ण

अटल पूर्णांक p54p_probe(काष्ठा pci_dev *pdev,
				स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा p54p_priv *priv;
	काष्ठा ieee80211_hw *dev;
	अचिन्हित दीर्घ mem_addr, mem_len;
	पूर्णांक err;

	pci_dev_get(pdev);
	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Cannot enable new PCI device\n");
		जाओ err_put;
	पूर्ण

	mem_addr = pci_resource_start(pdev, 0);
	mem_len = pci_resource_len(pdev, 0);
	अगर (mem_len < माप(काष्ठा p54p_csr)) अणु
		dev_err(&pdev->dev, "Too short PCI resources\n");
		err = -ENODEV;
		जाओ err_disable_dev;
	पूर्ण

	err = pci_request_regions(pdev, "p54pci");
	अगर (err) अणु
		dev_err(&pdev->dev, "Cannot obtain PCI resources\n");
		जाओ err_disable_dev;
	पूर्ण

	err = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
	अगर (!err)
		err = dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32));
	अगर (err) अणु
		dev_err(&pdev->dev, "No suitable DMA available\n");
		जाओ err_मुक्त_reg;
	पूर्ण

	pci_set_master(pdev);
	pci_try_set_mwi(pdev);

	pci_ग_लिखो_config_byte(pdev, 0x40, 0);
	pci_ग_लिखो_config_byte(pdev, 0x41, 0);

	dev = p54_init_common(माप(*priv));
	अगर (!dev) अणु
		dev_err(&pdev->dev, "ieee80211 alloc failed\n");
		err = -ENOMEM;
		जाओ err_मुक्त_reg;
	पूर्ण

	priv = dev->priv;
	priv->pdev = pdev;

	init_completion(&priv->fw_loaded);
	SET_IEEE80211_DEV(dev, &pdev->dev);
	pci_set_drvdata(pdev, dev);

	priv->map = ioremap(mem_addr, mem_len);
	अगर (!priv->map) अणु
		dev_err(&pdev->dev, "Cannot map device memory\n");
		err = -ENOMEM;
		जाओ err_मुक्त_dev;
	पूर्ण

	priv->ring_control = dma_alloc_coherent(&pdev->dev,
						माप(*priv->ring_control),
						&priv->ring_control_dma, GFP_KERNEL);
	अगर (!priv->ring_control) अणु
		dev_err(&pdev->dev, "Cannot allocate rings\n");
		err = -ENOMEM;
		जाओ err_iounmap;
	पूर्ण
	priv->common.खोलो = p54p_खोलो;
	priv->common.stop = p54p_stop;
	priv->common.tx = p54p_tx;

	spin_lock_init(&priv->lock);
	tasklet_setup(&priv->tasklet, p54p_tasklet);

	err = request_firmware_noरुको(THIS_MODULE, 1, "isl3886pci",
				      &priv->pdev->dev, GFP_KERNEL,
				      priv, p54p_firmware_step2);
	अगर (!err)
		वापस 0;

	dma_मुक्त_coherent(&pdev->dev, माप(*priv->ring_control),
			  priv->ring_control, priv->ring_control_dma);

 err_iounmap:
	iounmap(priv->map);

 err_मुक्त_dev:
	p54_मुक्त_common(dev);

 err_मुक्त_reg:
	pci_release_regions(pdev);
 err_disable_dev:
	pci_disable_device(pdev);
err_put:
	pci_dev_put(pdev);
	वापस err;
पूर्ण

अटल व्योम p54p_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ieee80211_hw *dev = pci_get_drvdata(pdev);
	काष्ठा p54p_priv *priv;

	अगर (!dev)
		वापस;

	priv = dev->priv;
	रुको_क्रम_completion(&priv->fw_loaded);
	p54_unरेजिस्टर_common(dev);
	release_firmware(priv->firmware);
	dma_मुक्त_coherent(&pdev->dev, माप(*priv->ring_control),
			  priv->ring_control, priv->ring_control_dma);
	iounmap(priv->map);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	p54_मुक्त_common(dev);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक p54p_suspend(काष्ठा device *device)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(device);

	pci_save_state(pdev);
	pci_set_घातer_state(pdev, PCI_D3hot);
	pci_disable_device(pdev);
	वापस 0;
पूर्ण

अटल पूर्णांक p54p_resume(काष्ठा device *device)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(device);
	पूर्णांक err;

	err = pci_reenable_device(pdev);
	अगर (err)
		वापस err;
	वापस pci_set_घातer_state(pdev, PCI_D0);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(p54pci_pm_ops, p54p_suspend, p54p_resume);

#घोषणा P54P_PM_OPS (&p54pci_pm_ops)
#अन्यथा
#घोषणा P54P_PM_OPS (शून्य)
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल काष्ठा pci_driver p54p_driver = अणु
	.name		= "p54pci",
	.id_table	= p54p_table,
	.probe		= p54p_probe,
	.हटाओ		= p54p_हटाओ,
	.driver.pm	= P54P_PM_OPS,
पूर्ण;

module_pci_driver(p54p_driver);
