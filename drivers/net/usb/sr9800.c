<शैली गुरु>
/* CoreChip-sz SR9800 one chip USB 2.0 Ethernet Devices
 *
 * Author : Liu Junliang <liujunliang_ljl@163.com>
 *
 * Based on asix_common.c, asix_devices.c
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2.  This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.*
 */

#समावेश <linux/module.h>
#समावेश <linux/kmod.h>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mii.h>
#समावेश <linux/usb.h>
#समावेश <linux/crc32.h>
#समावेश <linux/usb/usbnet.h>
#समावेश <linux/slab.h>
#समावेश <linux/अगर_vlan.h>

#समावेश "sr9800.h"

अटल पूर्णांक sr_पढ़ो_cmd(काष्ठा usbnet *dev, u8 cmd, u16 value, u16 index,
			    u16 size, व्योम *data)
अणु
	पूर्णांक err;

	err = usbnet_पढ़ो_cmd(dev, cmd, SR_REQ_RD_REG, value, index,
			      data, size);
	अगर ((err != size) && (err >= 0))
		err = -EINVAL;

	वापस err;
पूर्ण

अटल पूर्णांक sr_ग_लिखो_cmd(काष्ठा usbnet *dev, u8 cmd, u16 value, u16 index,
			     u16 size, व्योम *data)
अणु
	पूर्णांक err;

	err = usbnet_ग_लिखो_cmd(dev, cmd, SR_REQ_WR_REG, value, index,
			      data, size);
	अगर ((err != size) && (err >= 0))
		err = -EINVAL;

	वापस err;
पूर्ण

अटल व्योम
sr_ग_लिखो_cmd_async(काष्ठा usbnet *dev, u8 cmd, u16 value, u16 index,
		   u16 size, व्योम *data)
अणु
	usbnet_ग_लिखो_cmd_async(dev, cmd, SR_REQ_WR_REG, value, index, data,
			       size);
पूर्ण

अटल पूर्णांक sr_rx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb)
अणु
	पूर्णांक offset = 0;

	/* This check is no दीर्घer करोne by usbnet */
	अगर (skb->len < dev->net->hard_header_len)
		वापस 0;

	जबतक (offset + माप(u32) < skb->len) अणु
		काष्ठा sk_buff *sr_skb;
		u16 size;
		u32 header = get_unaligned_le32(skb->data + offset);

		offset += माप(u32);
		/* get the packet length */
		size = (u16) (header & 0x7ff);
		अगर (size != ((~header >> 16) & 0x07ff)) अणु
			netdev_err(dev->net, "%s : Bad Header Length\n",
				   __func__);
			वापस 0;
		पूर्ण

		अगर ((size > dev->net->mtu + ETH_HLEN + VLAN_HLEN) ||
		    (size + offset > skb->len)) अणु
			netdev_err(dev->net, "%s : Bad RX Length %d\n",
				   __func__, size);
			वापस 0;
		पूर्ण
		sr_skb = netdev_alloc_skb_ip_align(dev->net, size);
		अगर (!sr_skb)
			वापस 0;

		skb_put(sr_skb, size);
		स_नकल(sr_skb->data, skb->data + offset, size);
		usbnet_skb_वापस(dev, sr_skb);

		offset += (size + 1) & 0xfffe;
	पूर्ण

	अगर (skb->len != offset) अणु
		netdev_err(dev->net, "%s : Bad SKB Length %d\n", __func__,
			   skb->len);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल काष्ठा sk_buff *sr_tx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb,
					gfp_t flags)
अणु
	पूर्णांक headroom = skb_headroom(skb);
	पूर्णांक tailroom = skb_tailroom(skb);
	u32 padbytes = 0xffff0000;
	u32 packet_len;
	पूर्णांक padlen;
	व्योम *ptr;

	padlen = ((skb->len + 4) % (dev->maxpacket - 1)) ? 0 : 4;

	अगर ((!skb_cloned(skb)) && ((headroom + tailroom) >= (4 + padlen))) अणु
		अगर ((headroom < 4) || (tailroom < padlen)) अणु
			skb->data = स_हटाओ(skb->head + 4, skb->data,
					    skb->len);
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

	ptr = skb_push(skb, 4);
	packet_len = (((skb->len - 4) ^ 0x0000ffff) << 16) + (skb->len - 4);
	put_unaligned_le32(packet_len, ptr);

	अगर (padlen) अणु
		put_unaligned_le32(padbytes, skb_tail_poपूर्णांकer(skb));
		skb_put(skb, माप(padbytes));
	पूर्ण

	usbnet_set_skb_tx_stats(skb, 1, 0);
	वापस skb;
पूर्ण

अटल व्योम sr_status(काष्ठा usbnet *dev, काष्ठा urb *urb)
अणु
	काष्ठा sr9800_पूर्णांक_data *event;
	पूर्णांक link;

	अगर (urb->actual_length < 8)
		वापस;

	event = urb->transfer_buffer;
	link = event->link & 0x01;
	अगर (netअगर_carrier_ok(dev->net) != link) अणु
		usbnet_link_change(dev, link, 1);
		netdev_dbg(dev->net, "Link Status is: %d\n", link);
	पूर्ण

	वापस;
पूर्ण

अटल अंतरभूत पूर्णांक sr_set_sw_mii(काष्ठा usbnet *dev)
अणु
	पूर्णांक ret;

	ret = sr_ग_लिखो_cmd(dev, SR_CMD_SET_SW_MII, 0x0000, 0, 0, शून्य);
	अगर (ret < 0)
		netdev_err(dev->net, "Failed to enable software MII access\n");
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक sr_set_hw_mii(काष्ठा usbnet *dev)
अणु
	पूर्णांक ret;

	ret = sr_ग_लिखो_cmd(dev, SR_CMD_SET_HW_MII, 0x0000, 0, 0, शून्य);
	अगर (ret < 0)
		netdev_err(dev->net, "Failed to enable hardware MII access\n");
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक sr_get_phy_addr(काष्ठा usbnet *dev)
अणु
	u8 buf[2];
	पूर्णांक ret;

	ret = sr_पढ़ो_cmd(dev, SR_CMD_READ_PHY_ID, 0, 0, 2, buf);
	अगर (ret < 0) अणु
		netdev_err(dev->net, "%s : Error reading PHYID register:%02x\n",
			   __func__, ret);
		जाओ out;
	पूर्ण
	netdev_dbg(dev->net, "%s : returning 0x%04x\n", __func__,
		   *((__le16 *)buf));

	ret = buf[1];

out:
	वापस ret;
पूर्ण

अटल पूर्णांक sr_sw_reset(काष्ठा usbnet *dev, u8 flags)
अणु
	पूर्णांक ret;

	ret = sr_ग_लिखो_cmd(dev, SR_CMD_SW_RESET, flags, 0, 0, शून्य);
	अगर (ret < 0)
		netdev_err(dev->net, "Failed to send software reset:%02x\n",
			   ret);

	वापस ret;
पूर्ण

अटल u16 sr_पढ़ो_rx_ctl(काष्ठा usbnet *dev)
अणु
	__le16 v;
	पूर्णांक ret;

	ret = sr_पढ़ो_cmd(dev, SR_CMD_READ_RX_CTL, 0, 0, 2, &v);
	अगर (ret < 0) अणु
		netdev_err(dev->net, "Error reading RX_CTL register:%02x\n",
			   ret);
		जाओ out;
	पूर्ण

	ret = le16_to_cpu(v);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक sr_ग_लिखो_rx_ctl(काष्ठा usbnet *dev, u16 mode)
अणु
	पूर्णांक ret;

	netdev_dbg(dev->net, "%s : mode = 0x%04x\n", __func__, mode);
	ret = sr_ग_लिखो_cmd(dev, SR_CMD_WRITE_RX_CTL, mode, 0, 0, शून्य);
	अगर (ret < 0)
		netdev_err(dev->net,
			   "Failed to write RX_CTL mode to 0x%04x:%02x\n",
			   mode, ret);

	वापस ret;
पूर्ण

अटल u16 sr_पढ़ो_medium_status(काष्ठा usbnet *dev)
अणु
	__le16 v;
	पूर्णांक ret;

	ret = sr_पढ़ो_cmd(dev, SR_CMD_READ_MEDIUM_STATUS, 0, 0, 2, &v);
	अगर (ret < 0) अणु
		netdev_err(dev->net,
			   "Error reading Medium Status register:%02x\n", ret);
		वापस ret;	/* TODO: callers not checking क्रम error ret */
	पूर्ण

	वापस le16_to_cpu(v);
पूर्ण

अटल पूर्णांक sr_ग_लिखो_medium_mode(काष्ठा usbnet *dev, u16 mode)
अणु
	पूर्णांक ret;

	netdev_dbg(dev->net, "%s : mode = 0x%04x\n", __func__, mode);
	ret = sr_ग_लिखो_cmd(dev, SR_CMD_WRITE_MEDIUM_MODE, mode, 0, 0, शून्य);
	अगर (ret < 0)
		netdev_err(dev->net,
			   "Failed to write Medium Mode mode to 0x%04x:%02x\n",
			   mode, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक sr_ग_लिखो_gpio(काष्ठा usbnet *dev, u16 value, पूर्णांक sleep)
अणु
	पूर्णांक ret;

	netdev_dbg(dev->net, "%s : value = 0x%04x\n", __func__, value);
	ret = sr_ग_लिखो_cmd(dev, SR_CMD_WRITE_GPIOS, value, 0, 0, शून्य);
	अगर (ret < 0)
		netdev_err(dev->net, "Failed to write GPIO value 0x%04x:%02x\n",
			   value, ret);
	अगर (sleep)
		msleep(sleep);

	वापस ret;
पूर्ण

/* SR9800 have a 16-bit RX_CTL value */
अटल व्योम sr_set_multicast(काष्ठा net_device *net)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	काष्ठा sr_data *data = (काष्ठा sr_data *)&dev->data;
	u16 rx_ctl = SR_DEFAULT_RX_CTL;

	अगर (net->flags & IFF_PROMISC) अणु
		rx_ctl |= SR_RX_CTL_PRO;
	पूर्ण अन्यथा अगर (net->flags & IFF_ALLMULTI ||
		   netdev_mc_count(net) > SR_MAX_MCAST) अणु
		rx_ctl |= SR_RX_CTL_AMALL;
	पूर्ण अन्यथा अगर (netdev_mc_empty(net)) अणु
		/* just broadcast and directed */
	पूर्ण अन्यथा अणु
		/* We use the 20 byte dev->data
		 * क्रम our 8 byte filter buffer
		 * to aव्योम allocating memory that
		 * is tricky to मुक्त later
		 */
		काष्ठा netdev_hw_addr *ha;
		u32 crc_bits;

		स_रखो(data->multi_filter, 0, SR_MCAST_FILTER_SIZE);

		/* Build the multicast hash filter. */
		netdev_क्रम_each_mc_addr(ha, net) अणु
			crc_bits = ether_crc(ETH_ALEN, ha->addr) >> 26;
			data->multi_filter[crc_bits >> 3] |=
			    1 << (crc_bits & 7);
		पूर्ण

		sr_ग_लिखो_cmd_async(dev, SR_CMD_WRITE_MULTI_FILTER, 0, 0,
				   SR_MCAST_FILTER_SIZE, data->multi_filter);

		rx_ctl |= SR_RX_CTL_AM;
	पूर्ण

	sr_ग_लिखो_cmd_async(dev, SR_CMD_WRITE_RX_CTL, rx_ctl, 0, 0, शून्य);
पूर्ण

अटल पूर्णांक sr_mdio_पढ़ो(काष्ठा net_device *net, पूर्णांक phy_id, पूर्णांक loc)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	__le16 res = 0;

	mutex_lock(&dev->phy_mutex);
	sr_set_sw_mii(dev);
	sr_पढ़ो_cmd(dev, SR_CMD_READ_MII_REG, phy_id, (__u16)loc, 2, &res);
	sr_set_hw_mii(dev);
	mutex_unlock(&dev->phy_mutex);

	netdev_dbg(dev->net,
		   "%s : phy_id=0x%02x, loc=0x%02x, returns=0x%04x\n", __func__,
		   phy_id, loc, le16_to_cpu(res));

	वापस le16_to_cpu(res);
पूर्ण

अटल व्योम
sr_mdio_ग_लिखो(काष्ठा net_device *net, पूर्णांक phy_id, पूर्णांक loc, पूर्णांक val)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	__le16 res = cpu_to_le16(val);

	netdev_dbg(dev->net,
		   "%s : phy_id=0x%02x, loc=0x%02x, val=0x%04x\n", __func__,
		   phy_id, loc, val);
	mutex_lock(&dev->phy_mutex);
	sr_set_sw_mii(dev);
	sr_ग_लिखो_cmd(dev, SR_CMD_WRITE_MII_REG, phy_id, (__u16)loc, 2, &res);
	sr_set_hw_mii(dev);
	mutex_unlock(&dev->phy_mutex);
पूर्ण

/* Get the PHY Identअगरier from the PHYSID1 & PHYSID2 MII रेजिस्टरs */
अटल u32 sr_get_phyid(काष्ठा usbnet *dev)
अणु
	पूर्णांक phy_reg;
	u32 phy_id;
	पूर्णांक i;

	/* Poll क्रम the rare हाल the FW or phy isn't पढ़ोy yet.  */
	क्रम (i = 0; i < 100; i++) अणु
		phy_reg = sr_mdio_पढ़ो(dev->net, dev->mii.phy_id, MII_PHYSID1);
		अगर (phy_reg != 0 && phy_reg != 0xFFFF)
			अवरोध;
		mdelay(1);
	पूर्ण

	अगर (phy_reg <= 0 || phy_reg == 0xFFFF)
		वापस 0;

	phy_id = (phy_reg & 0xffff) << 16;

	phy_reg = sr_mdio_पढ़ो(dev->net, dev->mii.phy_id, MII_PHYSID2);
	अगर (phy_reg < 0)
		वापस 0;

	phy_id |= (phy_reg & 0xffff);

	वापस phy_id;
पूर्ण

अटल व्योम
sr_get_wol(काष्ठा net_device *net, काष्ठा ethtool_wolinfo *wolinfo)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	u8 opt;

	अगर (sr_पढ़ो_cmd(dev, SR_CMD_READ_MONITOR_MODE, 0, 0, 1, &opt) < 0) अणु
		wolinfo->supported = 0;
		wolinfo->wolopts = 0;
		वापस;
	पूर्ण
	wolinfo->supported = WAKE_PHY | WAKE_MAGIC;
	wolinfo->wolopts = 0;
	अगर (opt & SR_MONITOR_LINK)
		wolinfo->wolopts |= WAKE_PHY;
	अगर (opt & SR_MONITOR_MAGIC)
		wolinfo->wolopts |= WAKE_MAGIC;
पूर्ण

अटल पूर्णांक
sr_set_wol(काष्ठा net_device *net, काष्ठा ethtool_wolinfo *wolinfo)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	u8 opt = 0;

	अगर (wolinfo->wolopts & ~(WAKE_PHY | WAKE_MAGIC))
		वापस -EINVAL;

	अगर (wolinfo->wolopts & WAKE_PHY)
		opt |= SR_MONITOR_LINK;
	अगर (wolinfo->wolopts & WAKE_MAGIC)
		opt |= SR_MONITOR_MAGIC;

	अगर (sr_ग_लिखो_cmd(dev, SR_CMD_WRITE_MONITOR_MODE,
			 opt, 0, 0, शून्य) < 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक sr_get_eeprom_len(काष्ठा net_device *net)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	काष्ठा sr_data *data = (काष्ठा sr_data *)&dev->data;

	वापस data->eeprom_len;
पूर्ण

अटल पूर्णांक sr_get_eeprom(काष्ठा net_device *net,
			      काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	__le16 *ebuf = (__le16 *)data;
	पूर्णांक ret;
	पूर्णांक i;

	/* Crude hack to ensure that we करोn't overग_लिखो memory
	 * अगर an odd length is supplied
	 */
	अगर (eeprom->len % 2)
		वापस -EINVAL;

	eeprom->magic = SR_EEPROM_MAGIC;

	/* sr9800 वापसs 2 bytes from eeprom on पढ़ो */
	क्रम (i = 0; i < eeprom->len / 2; i++) अणु
		ret = sr_पढ़ो_cmd(dev, SR_CMD_READ_EEPROM, eeprom->offset + i,
				  0, 2, &ebuf[i]);
		अगर (ret < 0)
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम sr_get_drvinfo(काष्ठा net_device *net,
				 काष्ठा ethtool_drvinfo *info)
अणु
	/* Inherit standard device info */
	usbnet_get_drvinfo(net, info);
	म_नकलन(info->driver, DRIVER_NAME, माप(info->driver));
	म_नकलन(info->version, DRIVER_VERSION, माप(info->version));
पूर्ण

अटल u32 sr_get_link(काष्ठा net_device *net)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);

	वापस mii_link_ok(&dev->mii);
पूर्ण

अटल पूर्णांक sr_ioctl(काष्ठा net_device *net, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);

	वापस generic_mii_ioctl(&dev->mii, अगर_mii(rq), cmd, शून्य);
पूर्ण

अटल पूर्णांक sr_set_mac_address(काष्ठा net_device *net, व्योम *p)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);
	काष्ठा sr_data *data = (काष्ठा sr_data *)&dev->data;
	काष्ठा sockaddr *addr = p;

	अगर (netअगर_running(net))
		वापस -EBUSY;
	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(net->dev_addr, addr->sa_data, ETH_ALEN);

	/* We use the 20 byte dev->data
	 * क्रम our 6 byte mac buffer
	 * to aव्योम allocating memory that
	 * is tricky to मुक्त later
	 */
	स_नकल(data->mac_addr, addr->sa_data, ETH_ALEN);
	sr_ग_लिखो_cmd_async(dev, SR_CMD_WRITE_NODE_ID, 0, 0, ETH_ALEN,
			   data->mac_addr);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops sr9800_ethtool_ops = अणु
	.get_drvinfo	= sr_get_drvinfo,
	.get_link	= sr_get_link,
	.get_msglevel	= usbnet_get_msglevel,
	.set_msglevel	= usbnet_set_msglevel,
	.get_wol	= sr_get_wol,
	.set_wol	= sr_set_wol,
	.get_eeprom_len	= sr_get_eeprom_len,
	.get_eeprom	= sr_get_eeprom,
	.nway_reset	= usbnet_nway_reset,
	.get_link_ksettings	= usbnet_get_link_ksettings_mii,
	.set_link_ksettings	= usbnet_set_link_ksettings_mii,
पूर्ण;

अटल पूर्णांक sr9800_link_reset(काष्ठा usbnet *dev)
अणु
	काष्ठा ethtool_cmd ecmd = अणु .cmd = ETHTOOL_GSET पूर्ण;
	u16 mode;

	mii_check_media(&dev->mii, 1, 1);
	mii_ethtool_gset(&dev->mii, &ecmd);
	mode = SR9800_MEDIUM_DEFAULT;

	अगर (ethtool_cmd_speed(&ecmd) != SPEED_100)
		mode &= ~SR_MEDIUM_PS;

	अगर (ecmd.duplex != DUPLEX_FULL)
		mode &= ~SR_MEDIUM_FD;

	netdev_dbg(dev->net, "%s : speed: %u duplex: %d mode: 0x%04x\n",
		   __func__, ethtool_cmd_speed(&ecmd), ecmd.duplex, mode);

	sr_ग_लिखो_medium_mode(dev, mode);

	वापस 0;
पूर्ण


अटल पूर्णांक sr9800_set_शेष_mode(काष्ठा usbnet *dev)
अणु
	u16 rx_ctl;
	पूर्णांक ret;

	sr_mdio_ग_लिखो(dev->net, dev->mii.phy_id, MII_BMCR, BMCR_RESET);
	sr_mdio_ग_लिखो(dev->net, dev->mii.phy_id, MII_ADVERTISE,
		      ADVERTISE_ALL | ADVERTISE_CSMA);
	mii_nway_restart(&dev->mii);

	ret = sr_ग_लिखो_medium_mode(dev, SR9800_MEDIUM_DEFAULT);
	अगर (ret < 0)
		जाओ out;

	ret = sr_ग_लिखो_cmd(dev, SR_CMD_WRITE_IPG012,
				SR9800_IPG0_DEFAULT | SR9800_IPG1_DEFAULT,
				SR9800_IPG2_DEFAULT, 0, शून्य);
	अगर (ret < 0) अणु
		netdev_dbg(dev->net, "Write IPG,IPG1,IPG2 failed: %d\n", ret);
		जाओ out;
	पूर्ण

	/* Set RX_CTL to शेष values with 2k buffer, and enable cactus */
	ret = sr_ग_लिखो_rx_ctl(dev, SR_DEFAULT_RX_CTL);
	अगर (ret < 0)
		जाओ out;

	rx_ctl = sr_पढ़ो_rx_ctl(dev);
	netdev_dbg(dev->net, "RX_CTL is 0x%04x after all initializations\n",
		   rx_ctl);

	rx_ctl = sr_पढ़ो_medium_status(dev);
	netdev_dbg(dev->net, "Medium Status:0x%04x after all initializations\n",
		   rx_ctl);

	वापस 0;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक sr9800_reset(काष्ठा usbnet *dev)
अणु
	काष्ठा sr_data *data = (काष्ठा sr_data *)&dev->data;
	पूर्णांक ret, embd_phy;
	u16 rx_ctl;

	ret = sr_ग_लिखो_gpio(dev,
			SR_GPIO_RSE | SR_GPIO_GPO_2 | SR_GPIO_GPO2EN, 5);
	अगर (ret < 0)
		जाओ out;

	embd_phy = ((sr_get_phy_addr(dev) & 0x1f) == 0x10 ? 1 : 0);

	ret = sr_ग_लिखो_cmd(dev, SR_CMD_SW_PHY_SELECT, embd_phy, 0, 0, शून्य);
	अगर (ret < 0) अणु
		netdev_dbg(dev->net, "Select PHY #1 failed: %d\n", ret);
		जाओ out;
	पूर्ण

	ret = sr_sw_reset(dev, SR_SWRESET_IPPD | SR_SWRESET_PRL);
	अगर (ret < 0)
		जाओ out;

	msleep(150);

	ret = sr_sw_reset(dev, SR_SWRESET_CLEAR);
	अगर (ret < 0)
		जाओ out;

	msleep(150);

	अगर (embd_phy) अणु
		ret = sr_sw_reset(dev, SR_SWRESET_IPRL);
		अगर (ret < 0)
			जाओ out;
	पूर्ण अन्यथा अणु
		ret = sr_sw_reset(dev, SR_SWRESET_PRTE);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	msleep(150);
	rx_ctl = sr_पढ़ो_rx_ctl(dev);
	netdev_dbg(dev->net, "RX_CTL is 0x%04x after software reset\n", rx_ctl);
	ret = sr_ग_लिखो_rx_ctl(dev, 0x0000);
	अगर (ret < 0)
		जाओ out;

	rx_ctl = sr_पढ़ो_rx_ctl(dev);
	netdev_dbg(dev->net, "RX_CTL is 0x%04x setting to 0x0000\n", rx_ctl);

	ret = sr_sw_reset(dev, SR_SWRESET_PRL);
	अगर (ret < 0)
		जाओ out;

	msleep(150);

	ret = sr_sw_reset(dev, SR_SWRESET_IPRL | SR_SWRESET_PRL);
	अगर (ret < 0)
		जाओ out;

	msleep(150);

	ret = sr9800_set_शेष_mode(dev);
	अगर (ret < 0)
		जाओ out;

	/* Reग_लिखो MAC address */
	स_नकल(data->mac_addr, dev->net->dev_addr, ETH_ALEN);
	ret = sr_ग_लिखो_cmd(dev, SR_CMD_WRITE_NODE_ID, 0, 0, ETH_ALEN,
							data->mac_addr);
	अगर (ret < 0)
		जाओ out;

	वापस 0;

out:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा net_device_ops sr9800_netdev_ops = अणु
	.nकरो_खोलो		= usbnet_खोलो,
	.nकरो_stop		= usbnet_stop,
	.nकरो_start_xmit		= usbnet_start_xmit,
	.nकरो_tx_समयout		= usbnet_tx_समयout,
	.nकरो_change_mtu		= usbnet_change_mtu,
	.nकरो_get_stats64	= dev_get_tstats64,
	.nकरो_set_mac_address	= sr_set_mac_address,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_करो_ioctl		= sr_ioctl,
	.nकरो_set_rx_mode        = sr_set_multicast,
पूर्ण;

अटल पूर्णांक sr9800_phy_घातerup(काष्ठा usbnet *dev)
अणु
	पूर्णांक ret;

	/* set the embedded Ethernet PHY in घातer-करोwn state */
	ret = sr_sw_reset(dev, SR_SWRESET_IPPD | SR_SWRESET_IPRL);
	अगर (ret < 0) अणु
		netdev_err(dev->net, "Failed to power down PHY : %d\n", ret);
		वापस ret;
	पूर्ण
	msleep(20);

	/* set the embedded Ethernet PHY in घातer-up state */
	ret = sr_sw_reset(dev, SR_SWRESET_IPRL);
	अगर (ret < 0) अणु
		netdev_err(dev->net, "Failed to reset PHY: %d\n", ret);
		वापस ret;
	पूर्ण
	msleep(600);

	/* set the embedded Ethernet PHY in reset state */
	ret = sr_sw_reset(dev, SR_SWRESET_CLEAR);
	अगर (ret < 0) अणु
		netdev_err(dev->net, "Failed to power up PHY: %d\n", ret);
		वापस ret;
	पूर्ण
	msleep(20);

	/* set the embedded Ethernet PHY in घातer-up state */
	ret = sr_sw_reset(dev, SR_SWRESET_IPRL);
	अगर (ret < 0) अणु
		netdev_err(dev->net, "Failed to reset PHY: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sr9800_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा sr_data *data = (काष्ठा sr_data *)&dev->data;
	u16 led01_mux, led23_mux;
	पूर्णांक ret, embd_phy;
	u32 phyid;
	u16 rx_ctl;

	data->eeprom_len = SR9800_EEPROM_LEN;

	usbnet_get_endpoपूर्णांकs(dev, पूर्णांकf);

	/* LED Setting Rule :
	 * AABB:CCDD
	 * AA : MFA0(LED0)
	 * BB : MFA1(LED1)
	 * CC : MFA2(LED2), Reserved क्रम SR9800
	 * DD : MFA3(LED3), Reserved क्रम SR9800
	 */
	led01_mux = (SR_LED_MUX_LINK_ACTIVE << 8) | SR_LED_MUX_LINK;
	led23_mux = (SR_LED_MUX_LINK_ACTIVE << 8) | SR_LED_MUX_TX_ACTIVE;
	ret = sr_ग_लिखो_cmd(dev, SR_CMD_LED_MUX, led01_mux, led23_mux, 0, शून्य);
	अगर (ret < 0) अणु
			netdev_err(dev->net, "set LINK LED failed : %d\n", ret);
			जाओ out;
	पूर्ण

	/* Get the MAC address */
	ret = sr_पढ़ो_cmd(dev, SR_CMD_READ_NODE_ID, 0, 0, ETH_ALEN,
			  dev->net->dev_addr);
	अगर (ret < 0) अणु
		netdev_dbg(dev->net, "Failed to read MAC address: %d\n", ret);
		वापस ret;
	पूर्ण
	netdev_dbg(dev->net, "mac addr : %pM\n", dev->net->dev_addr);

	/* Initialize MII काष्ठाure */
	dev->mii.dev = dev->net;
	dev->mii.mdio_पढ़ो = sr_mdio_पढ़ो;
	dev->mii.mdio_ग_लिखो = sr_mdio_ग_लिखो;
	dev->mii.phy_id_mask = 0x1f;
	dev->mii.reg_num_mask = 0x1f;
	dev->mii.phy_id = sr_get_phy_addr(dev);

	dev->net->netdev_ops = &sr9800_netdev_ops;
	dev->net->ethtool_ops = &sr9800_ethtool_ops;

	embd_phy = ((dev->mii.phy_id & 0x1f) == 0x10 ? 1 : 0);
	/* Reset the PHY to normal operation mode */
	ret = sr_ग_लिखो_cmd(dev, SR_CMD_SW_PHY_SELECT, embd_phy, 0, 0, शून्य);
	अगर (ret < 0) अणु
		netdev_dbg(dev->net, "Select PHY #1 failed: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Init PHY routine */
	ret = sr9800_phy_घातerup(dev);
	अगर (ret < 0)
		जाओ out;

	rx_ctl = sr_पढ़ो_rx_ctl(dev);
	netdev_dbg(dev->net, "RX_CTL is 0x%04x after software reset\n", rx_ctl);
	ret = sr_ग_लिखो_rx_ctl(dev, 0x0000);
	अगर (ret < 0)
		जाओ out;

	rx_ctl = sr_पढ़ो_rx_ctl(dev);
	netdev_dbg(dev->net, "RX_CTL is 0x%04x setting to 0x0000\n", rx_ctl);

	/* Read PHYID रेजिस्टर *AFTER* the PHY was reset properly */
	phyid = sr_get_phyid(dev);
	netdev_dbg(dev->net, "PHYID=0x%08x\n", phyid);

	/* medium mode setting */
	ret = sr9800_set_शेष_mode(dev);
	अगर (ret < 0)
		जाओ out;

	अगर (dev->udev->speed == USB_SPEED_HIGH) अणु
		ret = sr_ग_लिखो_cmd(dev, SR_CMD_BULKIN_SIZE,
			SR9800_BULKIN_SIZE[SR9800_MAX_BULKIN_4K].byte_cnt,
			SR9800_BULKIN_SIZE[SR9800_MAX_BULKIN_4K].threshold,
			0, शून्य);
		अगर (ret < 0) अणु
			netdev_err(dev->net, "Reset RX_CTL failed: %d\n", ret);
			जाओ out;
		पूर्ण
		dev->rx_urb_size =
			SR9800_BULKIN_SIZE[SR9800_MAX_BULKIN_4K].size;
	पूर्ण अन्यथा अणु
		ret = sr_ग_लिखो_cmd(dev, SR_CMD_BULKIN_SIZE,
			SR9800_BULKIN_SIZE[SR9800_MAX_BULKIN_2K].byte_cnt,
			SR9800_BULKIN_SIZE[SR9800_MAX_BULKIN_2K].threshold,
			0, शून्य);
		अगर (ret < 0) अणु
			netdev_err(dev->net, "Reset RX_CTL failed: %d\n", ret);
			जाओ out;
		पूर्ण
		dev->rx_urb_size =
			SR9800_BULKIN_SIZE[SR9800_MAX_BULKIN_2K].size;
	पूर्ण
	netdev_dbg(dev->net, "%s : setting rx_urb_size with : %zu\n", __func__,
		   dev->rx_urb_size);
	वापस 0;

out:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा driver_info sr9800_driver_info = अणु
	.description	= "CoreChip SR9800 USB 2.0 Ethernet",
	.bind		= sr9800_bind,
	.status		= sr_status,
	.link_reset	= sr9800_link_reset,
	.reset		= sr9800_reset,
	.flags		= DRIVER_FLAG,
	.rx_fixup	= sr_rx_fixup,
	.tx_fixup	= sr_tx_fixup,
पूर्ण;

अटल स्थिर काष्ठा usb_device_id	products[] = अणु
	अणु
		USB_DEVICE(0x0fe6, 0x9800),	/* SR9800 Device  */
		.driver_info = (अचिन्हित दीर्घ) &sr9800_driver_info,
	पूर्ण,
	अणुपूर्ण,		/* END */
पूर्ण;

MODULE_DEVICE_TABLE(usb, products);

अटल काष्ठा usb_driver sr_driver = अणु
	.name		= DRIVER_NAME,
	.id_table	= products,
	.probe		= usbnet_probe,
	.suspend	= usbnet_suspend,
	.resume		= usbnet_resume,
	.disconnect	= usbnet_disconnect,
	.supports_स्वतःsuspend = 1,
पूर्ण;

module_usb_driver(sr_driver);

MODULE_AUTHOR("Liu Junliang <liujunliang_ljl@163.com");
MODULE_VERSION(DRIVER_VERSION);
MODULE_DESCRIPTION("SR9800 USB 2.0 USB2NET Dev : http://www.corechip-sz.com");
MODULE_LICENSE("GPL");
