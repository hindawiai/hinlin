<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ASIX AX8817X based USB 2.0 Ethernet Devices
 * Copyright (C) 2003-2006 David Hollis <dhollis@davehollis.com>
 * Copyright (C) 2005 Phil Chang <pchang23@sbcglobal.net>
 * Copyright (C) 2006 James Paपूर्णांकer <jamie.paपूर्णांकer@iname.com>
 * Copyright (c) 2002-2003 TiVo Inc.
 */

#समावेश "asix.h"

पूर्णांक asix_पढ़ो_cmd(काष्ठा usbnet *dev, u8 cmd, u16 value, u16 index,
		  u16 size, व्योम *data, पूर्णांक in_pm)
अणु
	पूर्णांक ret;
	पूर्णांक (*fn)(काष्ठा usbnet *, u8, u8, u16, u16, व्योम *, u16);

	BUG_ON(!dev);

	अगर (!in_pm)
		fn = usbnet_पढ़ो_cmd;
	अन्यथा
		fn = usbnet_पढ़ो_cmd_nopm;

	ret = fn(dev, cmd, USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
		 value, index, data, size);

	अगर (unlikely(ret < 0))
		netdev_warn(dev->net, "Failed to read reg index 0x%04x: %d\n",
			    index, ret);

	वापस ret;
पूर्ण

पूर्णांक asix_ग_लिखो_cmd(काष्ठा usbnet *dev, u8 cmd, u16 value, u16 index,
		   u16 size, व्योम *data, पूर्णांक in_pm)
अणु
	पूर्णांक ret;
	पूर्णांक (*fn)(काष्ठा usbnet *, u8, u8, u16, u16, स्थिर व्योम *, u16);

	BUG_ON(!dev);

	अगर (!in_pm)
		fn = usbnet_ग_लिखो_cmd;
	अन्यथा
		fn = usbnet_ग_लिखो_cmd_nopm;

	ret = fn(dev, cmd, USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
		 value, index, data, size);

	अगर (unlikely(ret < 0))
		netdev_warn(dev->net, "Failed to write reg index 0x%04x: %d\n",
			    index, ret);

	वापस ret;
पूर्ण

व्योम asix_ग_लिखो_cmd_async(काष्ठा usbnet *dev, u8 cmd, u16 value, u16 index,
			  u16 size, व्योम *data)
अणु
	usbnet_ग_लिखो_cmd_async(dev, cmd,
			       USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			       value, index, data, size);
पूर्ण

अटल व्योम reset_asix_rx_fixup_info(काष्ठा asix_rx_fixup_info *rx)
अणु
	/* Reset the variables that have a lअगरeसमय outside of
	 * asix_rx_fixup_पूर्णांकernal() so that future processing starts from a
	 * known set of initial conditions.
	 */

	अगर (rx->ax_skb) अणु
		/* Discard any incomplete Ethernet frame in the netdev buffer */
		kमुक्त_skb(rx->ax_skb);
		rx->ax_skb = शून्य;
	पूर्ण

	/* Assume the Data header 32-bit word is at the start of the current
	 * or next URB socket buffer so reset all the state variables.
	 */
	rx->reमुख्यing = 0;
	rx->split_head = false;
	rx->header = 0;
पूर्ण

पूर्णांक asix_rx_fixup_पूर्णांकernal(काष्ठा usbnet *dev, काष्ठा sk_buff *skb,
			   काष्ठा asix_rx_fixup_info *rx)
अणु
	पूर्णांक offset = 0;
	u16 size;

	/* When an Ethernet frame spans multiple URB socket buffers,
	 * करो a sanity test क्रम the Data header synchronisation.
	 * Attempt to detect the situation of the previous socket buffer having
	 * been truncated or a socket buffer was missing. These situations
	 * cause a discontinuity in the data stream and thereक्रमe need to aव्योम
	 * appending bad data to the end of the current netdev socket buffer.
	 * Also aव्योम unnecessarily discarding a good current netdev socket
	 * buffer.
	 */
	अगर (rx->reमुख्यing && (rx->reमुख्यing + माप(u32) <= skb->len)) अणु
		offset = ((rx->reमुख्यing + 1) & 0xfffe);
		rx->header = get_unaligned_le32(skb->data + offset);
		offset = 0;

		size = (u16)(rx->header & 0x7ff);
		अगर (size != ((~rx->header >> 16) & 0x7ff)) अणु
			netdev_err(dev->net, "asix_rx_fixup() Data Header synchronisation was lost, remaining %d\n",
				   rx->reमुख्यing);
			reset_asix_rx_fixup_info(rx);
		पूर्ण
	पूर्ण

	जबतक (offset + माप(u16) <= skb->len) अणु
		u16 copy_length;

		अगर (!rx->reमुख्यing) अणु
			अगर (skb->len - offset == माप(u16)) अणु
				rx->header = get_unaligned_le16(
						skb->data + offset);
				rx->split_head = true;
				offset += माप(u16);
				अवरोध;
			पूर्ण

			अगर (rx->split_head == true) अणु
				rx->header |= (get_unaligned_le16(
						skb->data + offset) << 16);
				rx->split_head = false;
				offset += माप(u16);
			पूर्ण अन्यथा अणु
				rx->header = get_unaligned_le32(skb->data +
								offset);
				offset += माप(u32);
			पूर्ण

			/* take frame length from Data header 32-bit word */
			size = (u16)(rx->header & 0x7ff);
			अगर (size != ((~rx->header >> 16) & 0x7ff)) अणु
				netdev_err(dev->net, "asix_rx_fixup() Bad Header Length 0x%x, offset %d\n",
					   rx->header, offset);
				reset_asix_rx_fixup_info(rx);
				वापस 0;
			पूर्ण
			अगर (size > dev->net->mtu + ETH_HLEN + VLAN_HLEN) अणु
				netdev_dbg(dev->net, "asix_rx_fixup() Bad RX Length %d\n",
					   size);
				reset_asix_rx_fixup_info(rx);
				वापस 0;
			पूर्ण

			/* Someबार may fail to get a netdev socket buffer but
			 * जारी to process the URB socket buffer so that
			 * synchronisation of the Ethernet frame Data header
			 * word is मुख्यtained.
			 */
			rx->ax_skb = netdev_alloc_skb_ip_align(dev->net, size);

			rx->reमुख्यing = size;
		पूर्ण

		अगर (rx->reमुख्यing > skb->len - offset) अणु
			copy_length = skb->len - offset;
			rx->reमुख्यing -= copy_length;
		पूर्ण अन्यथा अणु
			copy_length = rx->reमुख्यing;
			rx->reमुख्यing = 0;
		पूर्ण

		अगर (rx->ax_skb) अणु
			skb_put_data(rx->ax_skb, skb->data + offset,
				     copy_length);
			अगर (!rx->reमुख्यing) अणु
				usbnet_skb_वापस(dev, rx->ax_skb);
				rx->ax_skb = शून्य;
			पूर्ण
		पूर्ण

		offset += (copy_length + 1) & 0xfffe;
	पूर्ण

	अगर (skb->len != offset) अणु
		netdev_err(dev->net, "asix_rx_fixup() Bad SKB Length %d, %d\n",
			   skb->len, offset);
		reset_asix_rx_fixup_info(rx);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

पूर्णांक asix_rx_fixup_common(काष्ठा usbnet *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा asix_common_निजी *dp = dev->driver_priv;
	काष्ठा asix_rx_fixup_info *rx = &dp->rx_fixup_info;

	वापस asix_rx_fixup_पूर्णांकernal(dev, skb, rx);
पूर्ण

व्योम asix_rx_fixup_common_मुक्त(काष्ठा asix_common_निजी *dp)
अणु
	काष्ठा asix_rx_fixup_info *rx;

	अगर (!dp)
		वापस;

	rx = &dp->rx_fixup_info;

	अगर (rx->ax_skb) अणु
		kमुक्त_skb(rx->ax_skb);
		rx->ax_skb = शून्य;
	पूर्ण
पूर्ण

काष्ठा sk_buff *asix_tx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb,
			      gfp_t flags)
अणु
	पूर्णांक padlen;
	पूर्णांक headroom = skb_headroom(skb);
	पूर्णांक tailroom = skb_tailroom(skb);
	u32 packet_len;
	u32 padbytes = 0xffff0000;
	व्योम *ptr;

	padlen = ((skb->len + 4) & (dev->maxpacket - 1)) ? 0 : 4;

	/* We need to push 4 bytes in front of frame (packet_len)
	 * and maybe add 4 bytes after the end (अगर padlen is 4)
	 *
	 * Aव्योम skb_copy_expand() expensive call, using following rules :
	 * - We are allowed to push 4 bytes in headroom अगर skb_header_cloned()
	 *   is false (and अगर we have 4 bytes of headroom)
	 * - We are allowed to put 4 bytes at tail अगर skb_cloned()
	 *   is false (and अगर we have 4 bytes of tailroom)
	 *
	 * TCP packets क्रम example are cloned, but __skb_header_release()
	 * was called in tcp stack, allowing us to use headroom क्रम our needs.
	 */
	अगर (!skb_header_cloned(skb) &&
	    !(padlen && skb_cloned(skb)) &&
	    headroom + tailroom >= 4 + padlen) अणु
		/* following should not happen, but better be safe */
		अगर (headroom < 4 ||
		    tailroom < padlen) अणु
			skb->data = स_हटाओ(skb->head + 4, skb->data, skb->len);
			skb_set_tail_poपूर्णांकer(skb, skb->len);
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा sk_buff *skb2;

		skb2 = skb_copy_expand(skb, 4, padlen, flags);
		dev_kमुक्त_skb_any(skb);
		skb = skb2;
		अगर (!skb)
			वापस शून्य;
	पूर्ण

	packet_len = ((skb->len ^ 0x0000ffff) << 16) + skb->len;
	ptr = skb_push(skb, 4);
	put_unaligned_le32(packet_len, ptr);

	अगर (padlen) अणु
		put_unaligned_le32(padbytes, skb_tail_poपूर्णांकer(skb));
		skb_put(skb, माप(padbytes));
	पूर्ण

	usbnet_set_skb_tx_stats(skb, 1, 0);
	वापस skb;
पूर्ण

पूर्णांक asix_set_sw_mii(काष्ठा usbnet *dev, पूर्णांक in_pm)
अणु
	पूर्णांक ret;
	ret = asix_ग_लिखो_cmd(dev, AX_CMD_SET_SW_MII, 0x0000, 0, 0, शून्य, in_pm);

	अगर (ret < 0)
		netdev_err(dev->net, "Failed to enable software MII access\n");
	वापस ret;
पूर्ण

पूर्णांक asix_set_hw_mii(काष्ठा usbnet *dev, पूर्णांक in_pm)
अणु
	पूर्णांक ret;
	ret = asix_ग_लिखो_cmd(dev, AX_CMD_SET_HW_MII, 0x0000, 0, 0, शून्य, in_pm);
	अगर (ret < 0)
		netdev_err(dev->net, "Failed to enable hardware MII access\n");
	वापस ret;
पूर्ण

पूर्णांक asix_पढ़ो_phy_addr(काष्ठा usbnet *dev, पूर्णांक पूर्णांकernal)
अणु
	पूर्णांक offset = (पूर्णांकernal ? 1 : 0);
	u8 buf[2];
	पूर्णांक ret = asix_पढ़ो_cmd(dev, AX_CMD_READ_PHY_ID, 0, 0, 2, buf, 0);

	netdev_dbg(dev->net, "asix_get_phy_addr()\n");

	अगर (ret < 2) अणु
		netdev_err(dev->net, "Error reading PHYID register: %02x\n", ret);
		जाओ out;
	पूर्ण
	netdev_dbg(dev->net, "asix_get_phy_addr() returning 0x%04x\n",
		   *((__le16 *)buf));
	ret = buf[offset];

out:
	वापस ret;
पूर्ण

पूर्णांक asix_get_phy_addr(काष्ठा usbnet *dev)
अणु
	/* वापस the address of the पूर्णांकernal phy */
	वापस asix_पढ़ो_phy_addr(dev, 1);
पूर्ण


पूर्णांक asix_sw_reset(काष्ठा usbnet *dev, u8 flags, पूर्णांक in_pm)
अणु
	पूर्णांक ret;

	ret = asix_ग_लिखो_cmd(dev, AX_CMD_SW_RESET, flags, 0, 0, शून्य, in_pm);
	अगर (ret < 0)
		netdev_err(dev->net, "Failed to send software reset: %02x\n", ret);

	वापस ret;
पूर्ण

u16 asix_पढ़ो_rx_ctl(काष्ठा usbnet *dev, पूर्णांक in_pm)
अणु
	__le16 v;
	पूर्णांक ret = asix_पढ़ो_cmd(dev, AX_CMD_READ_RX_CTL, 0, 0, 2, &v, in_pm);

	अगर (ret < 0) अणु
		netdev_err(dev->net, "Error reading RX_CTL register: %02x\n", ret);
		जाओ out;
	पूर्ण
	ret = le16_to_cpu(v);
out:
	वापस ret;
पूर्ण

पूर्णांक asix_ग_लिखो_rx_ctl(काष्ठा usbnet *dev, u16 mode, पूर्णांक in_pm)
अणु
	पूर्णांक ret;

	netdev_dbg(dev->net, "asix_write_rx_ctl() - mode = 0x%04x\n", mode);
	ret = asix_ग_लिखो_cmd(dev, AX_CMD_WRITE_RX_CTL, mode, 0, 0, शून्य, in_pm);
	अगर (ret < 0)
		netdev_err(dev->net, "Failed to write RX_CTL mode to 0x%04x: %02x\n",
			   mode, ret);

	वापस ret;
पूर्ण

u16 asix_पढ़ो_medium_status(काष्ठा usbnet *dev, पूर्णांक in_pm)
अणु
	__le16 v;
	पूर्णांक ret = asix_पढ़ो_cmd(dev, AX_CMD_READ_MEDIUM_STATUS,
				0, 0, 2, &v, in_pm);

	अगर (ret < 0) अणु
		netdev_err(dev->net, "Error reading Medium Status register: %02x\n",
			   ret);
		वापस ret;	/* TODO: callers not checking क्रम error ret */
	पूर्ण

	वापस le16_to_cpu(v);

पूर्ण

पूर्णांक asix_ग_लिखो_medium_mode(काष्ठा usbnet *dev, u16 mode, पूर्णांक in_pm)
अणु
	पूर्णांक ret;

	netdev_dbg(dev->net, "asix_write_medium_mode() - mode = 0x%04x\n", mode);
	ret = asix_ग_लिखो_cmd(dev, AX_CMD_WRITE_MEDIUM_MODE,
			     mode, 0, 0, शून्य, in_pm);
	अगर (ret < 0)
		netdev_err(dev->net, "Failed to write Medium Mode mode to 0x%04x: %02x\n",
			   mode, ret);

	वापस ret;
पूर्ण

पूर्णांक asix_ग_लिखो_gpio(काष्ठा usbnet *dev, u16 value, पूर्णांक sleep, पूर्णांक in_pm)
अणु
	पूर्णांक ret;

	netdev_dbg(dev->net, "asix_write_gpio() - value = 0x%04x\n", value);
	ret = asix_ग_लिखो_cmd(dev, AX_CMD_WRITE_GPIOS, value, 0, 0, शून्य, in_pm);
	अगर (ret < 0)
		netdev_err(dev->net, "Failed to write GPIO value 0x%04x: %02x\n",
			   value, ret);

	अगर (sleep)
		msleep(sleep);

	वापस ret;
पूर्ण

/*
 * AX88772 & AX88178 have a 16-bit RX_CTL value
 */
व्योम asix_set_multicast(काष्ठा net_device *net)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	काष्ठा asix_data *data = (काष्ठा asix_data *)&dev->data;
	u16 rx_ctl = AX_DEFAULT_RX_CTL;

	अगर (net->flags & IFF_PROMISC) अणु
		rx_ctl |= AX_RX_CTL_PRO;
	पूर्ण अन्यथा अगर (net->flags & IFF_ALLMULTI ||
		   netdev_mc_count(net) > AX_MAX_MCAST) अणु
		rx_ctl |= AX_RX_CTL_AMALL;
	पूर्ण अन्यथा अगर (netdev_mc_empty(net)) अणु
		/* just broadcast and directed */
	पूर्ण अन्यथा अणु
		/* We use the 20 byte dev->data
		 * क्रम our 8 byte filter buffer
		 * to aव्योम allocating memory that
		 * is tricky to मुक्त later */
		काष्ठा netdev_hw_addr *ha;
		u32 crc_bits;

		स_रखो(data->multi_filter, 0, AX_MCAST_FILTER_SIZE);

		/* Build the multicast hash filter. */
		netdev_क्रम_each_mc_addr(ha, net) अणु
			crc_bits = ether_crc(ETH_ALEN, ha->addr) >> 26;
			data->multi_filter[crc_bits >> 3] |=
			    1 << (crc_bits & 7);
		पूर्ण

		asix_ग_लिखो_cmd_async(dev, AX_CMD_WRITE_MULTI_FILTER, 0, 0,
				   AX_MCAST_FILTER_SIZE, data->multi_filter);

		rx_ctl |= AX_RX_CTL_AM;
	पूर्ण

	asix_ग_लिखो_cmd_async(dev, AX_CMD_WRITE_RX_CTL, rx_ctl, 0, 0, शून्य);
पूर्ण

पूर्णांक asix_mdio_पढ़ो(काष्ठा net_device *netdev, पूर्णांक phy_id, पूर्णांक loc)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);
	__le16 res;
	u8 smsr;
	पूर्णांक i = 0;
	पूर्णांक ret;

	mutex_lock(&dev->phy_mutex);
	करो अणु
		ret = asix_set_sw_mii(dev, 0);
		अगर (ret == -ENODEV || ret == -ETIMEDOUT)
			अवरोध;
		usleep_range(1000, 1100);
		ret = asix_पढ़ो_cmd(dev, AX_CMD_STATMNGSTS_REG,
				    0, 0, 1, &smsr, 0);
	पूर्ण जबतक (!(smsr & AX_HOST_EN) && (i++ < 30) && (ret != -ENODEV));
	अगर (ret == -ENODEV || ret == -ETIMEDOUT) अणु
		mutex_unlock(&dev->phy_mutex);
		वापस ret;
	पूर्ण

	asix_पढ़ो_cmd(dev, AX_CMD_READ_MII_REG, phy_id,
				(__u16)loc, 2, &res, 0);
	asix_set_hw_mii(dev, 0);
	mutex_unlock(&dev->phy_mutex);

	netdev_dbg(dev->net, "asix_mdio_read() phy_id=0x%02x, loc=0x%02x, returns=0x%04x\n",
			phy_id, loc, le16_to_cpu(res));

	वापस le16_to_cpu(res);
पूर्ण

व्योम asix_mdio_ग_लिखो(काष्ठा net_device *netdev, पूर्णांक phy_id, पूर्णांक loc, पूर्णांक val)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);
	__le16 res = cpu_to_le16(val);
	u8 smsr;
	पूर्णांक i = 0;
	पूर्णांक ret;

	netdev_dbg(dev->net, "asix_mdio_write() phy_id=0x%02x, loc=0x%02x, val=0x%04x\n",
			phy_id, loc, val);

	mutex_lock(&dev->phy_mutex);
	करो अणु
		ret = asix_set_sw_mii(dev, 0);
		अगर (ret == -ENODEV)
			अवरोध;
		usleep_range(1000, 1100);
		ret = asix_पढ़ो_cmd(dev, AX_CMD_STATMNGSTS_REG,
				    0, 0, 1, &smsr, 0);
	पूर्ण जबतक (!(smsr & AX_HOST_EN) && (i++ < 30) && (ret != -ENODEV));
	अगर (ret == -ENODEV) अणु
		mutex_unlock(&dev->phy_mutex);
		वापस;
	पूर्ण

	asix_ग_लिखो_cmd(dev, AX_CMD_WRITE_MII_REG, phy_id,
		       (__u16)loc, 2, &res, 0);
	asix_set_hw_mii(dev, 0);
	mutex_unlock(&dev->phy_mutex);
पूर्ण

पूर्णांक asix_mdio_पढ़ो_nopm(काष्ठा net_device *netdev, पूर्णांक phy_id, पूर्णांक loc)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);
	__le16 res;
	u8 smsr;
	पूर्णांक i = 0;
	पूर्णांक ret;

	mutex_lock(&dev->phy_mutex);
	करो अणु
		ret = asix_set_sw_mii(dev, 1);
		अगर (ret == -ENODEV || ret == -ETIMEDOUT)
			अवरोध;
		usleep_range(1000, 1100);
		ret = asix_पढ़ो_cmd(dev, AX_CMD_STATMNGSTS_REG,
				    0, 0, 1, &smsr, 1);
	पूर्ण जबतक (!(smsr & AX_HOST_EN) && (i++ < 30) && (ret != -ENODEV));
	अगर (ret == -ENODEV || ret == -ETIMEDOUT) अणु
		mutex_unlock(&dev->phy_mutex);
		वापस ret;
	पूर्ण

	asix_पढ़ो_cmd(dev, AX_CMD_READ_MII_REG, phy_id,
		      (__u16)loc, 2, &res, 1);
	asix_set_hw_mii(dev, 1);
	mutex_unlock(&dev->phy_mutex);

	netdev_dbg(dev->net, "asix_mdio_read_nopm() phy_id=0x%02x, loc=0x%02x, returns=0x%04x\n",
			phy_id, loc, le16_to_cpu(res));

	वापस le16_to_cpu(res);
पूर्ण

व्योम
asix_mdio_ग_लिखो_nopm(काष्ठा net_device *netdev, पूर्णांक phy_id, पूर्णांक loc, पूर्णांक val)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);
	__le16 res = cpu_to_le16(val);
	u8 smsr;
	पूर्णांक i = 0;
	पूर्णांक ret;

	netdev_dbg(dev->net, "asix_mdio_write() phy_id=0x%02x, loc=0x%02x, val=0x%04x\n",
			phy_id, loc, val);

	mutex_lock(&dev->phy_mutex);
	करो अणु
		ret = asix_set_sw_mii(dev, 1);
		अगर (ret == -ENODEV)
			अवरोध;
		usleep_range(1000, 1100);
		ret = asix_पढ़ो_cmd(dev, AX_CMD_STATMNGSTS_REG,
				    0, 0, 1, &smsr, 1);
	पूर्ण जबतक (!(smsr & AX_HOST_EN) && (i++ < 30) && (ret != -ENODEV));
	अगर (ret == -ENODEV) अणु
		mutex_unlock(&dev->phy_mutex);
		वापस;
	पूर्ण

	asix_ग_लिखो_cmd(dev, AX_CMD_WRITE_MII_REG, phy_id,
		       (__u16)loc, 2, &res, 1);
	asix_set_hw_mii(dev, 1);
	mutex_unlock(&dev->phy_mutex);
पूर्ण

व्योम asix_get_wol(काष्ठा net_device *net, काष्ठा ethtool_wolinfo *wolinfo)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	u8 opt;

	अगर (asix_पढ़ो_cmd(dev, AX_CMD_READ_MONITOR_MODE,
			  0, 0, 1, &opt, 0) < 0) अणु
		wolinfo->supported = 0;
		wolinfo->wolopts = 0;
		वापस;
	पूर्ण
	wolinfo->supported = WAKE_PHY | WAKE_MAGIC;
	wolinfo->wolopts = 0;
	अगर (opt & AX_MONITOR_LINK)
		wolinfo->wolopts |= WAKE_PHY;
	अगर (opt & AX_MONITOR_MAGIC)
		wolinfo->wolopts |= WAKE_MAGIC;
पूर्ण

पूर्णांक asix_set_wol(काष्ठा net_device *net, काष्ठा ethtool_wolinfo *wolinfo)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	u8 opt = 0;

	अगर (wolinfo->wolopts & ~(WAKE_PHY | WAKE_MAGIC))
		वापस -EINVAL;

	अगर (wolinfo->wolopts & WAKE_PHY)
		opt |= AX_MONITOR_LINK;
	अगर (wolinfo->wolopts & WAKE_MAGIC)
		opt |= AX_MONITOR_MAGIC;

	अगर (asix_ग_लिखो_cmd(dev, AX_CMD_WRITE_MONITOR_MODE,
			      opt, 0, 0, शून्य, 0) < 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक asix_get_eeprom_len(काष्ठा net_device *net)
अणु
	वापस AX_EEPROM_LEN;
पूर्ण

पूर्णांक asix_get_eeprom(काष्ठा net_device *net, काष्ठा ethtool_eeprom *eeprom,
		    u8 *data)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	u16 *eeprom_buff;
	पूर्णांक first_word, last_word;
	पूर्णांक i;

	अगर (eeprom->len == 0)
		वापस -EINVAL;

	eeprom->magic = AX_EEPROM_MAGIC;

	first_word = eeprom->offset >> 1;
	last_word = (eeprom->offset + eeprom->len - 1) >> 1;

	eeprom_buff = kदो_स्मृति_array(last_word - first_word + 1, माप(u16),
				    GFP_KERNEL);
	अगर (!eeprom_buff)
		वापस -ENOMEM;

	/* ax8817x वापसs 2 bytes from eeprom on पढ़ो */
	क्रम (i = first_word; i <= last_word; i++) अणु
		अगर (asix_पढ़ो_cmd(dev, AX_CMD_READ_EEPROM, i, 0, 2,
				  &eeprom_buff[i - first_word], 0) < 0) अणु
			kमुक्त(eeprom_buff);
			वापस -EIO;
		पूर्ण
	पूर्ण

	स_नकल(data, (u8 *)eeprom_buff + (eeprom->offset & 1), eeprom->len);
	kमुक्त(eeprom_buff);
	वापस 0;
पूर्ण

पूर्णांक asix_set_eeprom(काष्ठा net_device *net, काष्ठा ethtool_eeprom *eeprom,
		    u8 *data)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	u16 *eeprom_buff;
	पूर्णांक first_word, last_word;
	पूर्णांक i;
	पूर्णांक ret;

	netdev_dbg(net, "write EEPROM len %d, offset %d, magic 0x%x\n",
		   eeprom->len, eeprom->offset, eeprom->magic);

	अगर (eeprom->len == 0)
		वापस -EINVAL;

	अगर (eeprom->magic != AX_EEPROM_MAGIC)
		वापस -EINVAL;

	first_word = eeprom->offset >> 1;
	last_word = (eeprom->offset + eeprom->len - 1) >> 1;

	eeprom_buff = kदो_स्मृति_array(last_word - first_word + 1, माप(u16),
				    GFP_KERNEL);
	अगर (!eeprom_buff)
		वापस -ENOMEM;

	/* align data to 16 bit boundaries, पढ़ो the missing data from
	   the EEPROM */
	अगर (eeprom->offset & 1) अणु
		ret = asix_पढ़ो_cmd(dev, AX_CMD_READ_EEPROM, first_word, 0, 2,
				    &eeprom_buff[0], 0);
		अगर (ret < 0) अणु
			netdev_err(net, "Failed to read EEPROM at offset 0x%02x.\n", first_word);
			जाओ मुक्त;
		पूर्ण
	पूर्ण

	अगर ((eeprom->offset + eeprom->len) & 1) अणु
		ret = asix_पढ़ो_cmd(dev, AX_CMD_READ_EEPROM, last_word, 0, 2,
				    &eeprom_buff[last_word - first_word], 0);
		अगर (ret < 0) अणु
			netdev_err(net, "Failed to read EEPROM at offset 0x%02x.\n", last_word);
			जाओ मुक्त;
		पूर्ण
	पूर्ण

	स_नकल((u8 *)eeprom_buff + (eeprom->offset & 1), data, eeprom->len);

	/* ग_लिखो data to EEPROM */
	ret = asix_ग_लिखो_cmd(dev, AX_CMD_WRITE_ENABLE, 0x0000, 0, 0, शून्य, 0);
	अगर (ret < 0) अणु
		netdev_err(net, "Failed to enable EEPROM write\n");
		जाओ मुक्त;
	पूर्ण
	msleep(20);

	क्रम (i = first_word; i <= last_word; i++) अणु
		netdev_dbg(net, "write to EEPROM at offset 0x%02x, data 0x%04x\n",
			   i, eeprom_buff[i - first_word]);
		ret = asix_ग_लिखो_cmd(dev, AX_CMD_WRITE_EEPROM, i,
				     eeprom_buff[i - first_word], 0, शून्य, 0);
		अगर (ret < 0) अणु
			netdev_err(net, "Failed to write EEPROM at offset 0x%02x.\n",
				   i);
			जाओ मुक्त;
		पूर्ण
		msleep(20);
	पूर्ण

	ret = asix_ग_लिखो_cmd(dev, AX_CMD_WRITE_DISABLE, 0x0000, 0, 0, शून्य, 0);
	अगर (ret < 0) अणु
		netdev_err(net, "Failed to disable EEPROM write\n");
		जाओ मुक्त;
	पूर्ण

	ret = 0;
मुक्त:
	kमुक्त(eeprom_buff);
	वापस ret;
पूर्ण

व्योम asix_get_drvinfo(काष्ठा net_device *net, काष्ठा ethtool_drvinfo *info)
अणु
	/* Inherit standard device info */
	usbnet_get_drvinfo(net, info);
	strlcpy(info->driver, DRIVER_NAME, माप(info->driver));
	strlcpy(info->version, DRIVER_VERSION, माप(info->version));
पूर्ण

पूर्णांक asix_set_mac_address(काष्ठा net_device *net, व्योम *p)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	काष्ठा asix_data *data = (काष्ठा asix_data *)&dev->data;
	काष्ठा sockaddr *addr = p;

	अगर (netअगर_running(net))
		वापस -EBUSY;
	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(net->dev_addr, addr->sa_data, ETH_ALEN);

	/* We use the 20 byte dev->data
	 * क्रम our 6 byte mac buffer
	 * to aव्योम allocating memory that
	 * is tricky to मुक्त later */
	स_नकल(data->mac_addr, addr->sa_data, ETH_ALEN);
	asix_ग_लिखो_cmd_async(dev, AX_CMD_WRITE_NODE_ID, 0, 0, ETH_ALEN,
							data->mac_addr);

	वापस 0;
पूर्ण
