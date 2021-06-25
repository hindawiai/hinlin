<शैली गुरु>
/*
 * cdc_ncm.c
 *
 * Copyright (C) ST-Ericsson 2010-2012
 * Contact: Alexey Orishko <alexey.orishko@stericsson.com>
 * Original author: Hans Petter Selasky <hans.petter.selasky@stericsson.com>
 *
 * USB Host Driver क्रम Network Control Model (NCM)
 * http://www.usb.org/developers/करोcs/devclass_करोcs/NCM10_012011.zip
 *
 * The NCM encoding, decoding and initialization logic
 * derives from FreeBSD 8.x. अगर_cdce.c and अगर_cdcereg.h
 *
 * This software is available to you under a choice of one of two
 * licenses. You may choose this file to be licensed under the terms
 * of the GNU General Public License (GPL) Version 2 or the 2-clause
 * BSD license listed below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mii.h>
#समावेश <linux/crc32.h>
#समावेश <linux/usb.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/atomic.h>
#समावेश <linux/usb/usbnet.h>
#समावेश <linux/usb/cdc.h>
#समावेश <linux/usb/cdc_ncm.h>

#अगर IS_ENABLED(CONFIG_USB_NET_CDC_MBIM)
अटल bool prefer_mbim = true;
#अन्यथा
अटल bool prefer_mbim;
#पूर्ण_अगर
module_param(prefer_mbim, bool, 0644);
MODULE_PARM_DESC(prefer_mbim, "Prefer MBIM setting on dual NCM/MBIM functions");

अटल व्योम cdc_ncm_txpath_bh(काष्ठा tasklet_काष्ठा *t);
अटल व्योम cdc_ncm_tx_समयout_start(काष्ठा cdc_ncm_ctx *ctx);
अटल क्रमागत hrसमयr_restart cdc_ncm_tx_समयr_cb(काष्ठा hrसमयr *hr_समयr);
अटल काष्ठा usb_driver cdc_ncm_driver;

काष्ठा cdc_ncm_stats अणु
	अक्षर stat_string[ETH_GSTRING_LEN];
	पूर्णांक माप_stat;
	पूर्णांक stat_offset;
पूर्ण;

#घोषणा CDC_NCM_STAT(str, m) अणु \
		.stat_string = str, \
		.माप_stat = माप(((काष्ठा cdc_ncm_ctx *)0)->m), \
		.stat_offset = दुरत्व(काष्ठा cdc_ncm_ctx, m) पूर्ण
#घोषणा CDC_NCM_SIMPLE_STAT(m)	CDC_NCM_STAT(__stringअगरy(m), m)

अटल स्थिर काष्ठा cdc_ncm_stats cdc_ncm_gstrings_stats[] = अणु
	CDC_NCM_SIMPLE_STAT(tx_reason_ntb_full),
	CDC_NCM_SIMPLE_STAT(tx_reason_ndp_full),
	CDC_NCM_SIMPLE_STAT(tx_reason_समयout),
	CDC_NCM_SIMPLE_STAT(tx_reason_max_datagram),
	CDC_NCM_SIMPLE_STAT(tx_overhead),
	CDC_NCM_SIMPLE_STAT(tx_ntbs),
	CDC_NCM_SIMPLE_STAT(rx_overhead),
	CDC_NCM_SIMPLE_STAT(rx_ntbs),
पूर्ण;

#घोषणा CDC_NCM_LOW_MEM_MAX_CNT 10

अटल पूर्णांक cdc_ncm_get_sset_count(काष्ठा net_device __always_unused *netdev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस ARRAY_SIZE(cdc_ncm_gstrings_stats);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम cdc_ncm_get_ethtool_stats(काष्ठा net_device *netdev,
				    काष्ठा ethtool_stats __always_unused *stats,
				    u64 *data)
अणु
	काष्ठा usbnet *dev = netdev_priv(netdev);
	काष्ठा cdc_ncm_ctx *ctx = (काष्ठा cdc_ncm_ctx *)dev->data[0];
	पूर्णांक i;
	अक्षर *p = शून्य;

	क्रम (i = 0; i < ARRAY_SIZE(cdc_ncm_gstrings_stats); i++) अणु
		p = (अक्षर *)ctx + cdc_ncm_gstrings_stats[i].stat_offset;
		data[i] = (cdc_ncm_gstrings_stats[i].माप_stat == माप(u64)) ? *(u64 *)p : *(u32 *)p;
	पूर्ण
पूर्ण

अटल व्योम cdc_ncm_get_strings(काष्ठा net_device __always_unused *netdev, u32 stringset, u8 *data)
अणु
	u8 *p = data;
	पूर्णांक i;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < ARRAY_SIZE(cdc_ncm_gstrings_stats); i++) अणु
			स_नकल(p, cdc_ncm_gstrings_stats[i].stat_string, ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम cdc_ncm_update_rxtx_max(काष्ठा usbnet *dev, u32 new_rx, u32 new_tx);

अटल स्थिर काष्ठा ethtool_ops cdc_ncm_ethtool_ops = अणु
	.get_link		= usbnet_get_link,
	.nway_reset		= usbnet_nway_reset,
	.get_drvinfo		= usbnet_get_drvinfo,
	.get_msglevel		= usbnet_get_msglevel,
	.set_msglevel		= usbnet_set_msglevel,
	.get_ts_info		= ethtool_op_get_ts_info,
	.get_sset_count		= cdc_ncm_get_sset_count,
	.get_strings		= cdc_ncm_get_strings,
	.get_ethtool_stats	= cdc_ncm_get_ethtool_stats,
	.get_link_ksettings	= usbnet_get_link_ksettings_पूर्णांकernal,
	.set_link_ksettings	= शून्य,
पूर्ण;

अटल u32 cdc_ncm_check_rx_max(काष्ठा usbnet *dev, u32 new_rx)
अणु
	काष्ठा cdc_ncm_ctx *ctx = (काष्ठा cdc_ncm_ctx *)dev->data[0];
	u32 val, max, min;

	/* clamp new_rx to sane values */
	min = USB_CDC_NCM_NTB_MIN_IN_SIZE;
	max = min_t(u32, CDC_NCM_NTB_MAX_SIZE_RX, le32_to_cpu(ctx->ncm_parm.dwNtbInMaxSize));

	/* dwNtbInMaxSize spec violation? Use MIN size क्रम both limits */
	अगर (max < min) अणु
		dev_warn(&dev->पूर्णांकf->dev, "dwNtbInMaxSize=%u is too small. Using %u\n",
			 le32_to_cpu(ctx->ncm_parm.dwNtbInMaxSize), min);
		max = min;
	पूर्ण

	val = clamp_t(u32, new_rx, min, max);
	अगर (val != new_rx)
		dev_dbg(&dev->पूर्णांकf->dev, "rx_max must be in the [%u, %u] range\n", min, max);

	वापस val;
पूर्ण

अटल u32 cdc_ncm_check_tx_max(काष्ठा usbnet *dev, u32 new_tx)
अणु
	काष्ठा cdc_ncm_ctx *ctx = (काष्ठा cdc_ncm_ctx *)dev->data[0];
	u32 val, max, min;

	/* clamp new_tx to sane values */
	अगर (ctx->is_ndp16)
		min = ctx->max_datagram_size + ctx->max_ndp_size + माप(काष्ठा usb_cdc_ncm_nth16);
	अन्यथा
		min = ctx->max_datagram_size + ctx->max_ndp_size + माप(काष्ठा usb_cdc_ncm_nth32);

	max = min_t(u32, CDC_NCM_NTB_MAX_SIZE_TX, le32_to_cpu(ctx->ncm_parm.dwNtbOutMaxSize));

	/* some devices set dwNtbOutMaxSize too low क्रम the above शेष */
	min = min(min, max);

	val = clamp_t(u32, new_tx, min, max);
	अगर (val != new_tx)
		dev_dbg(&dev->पूर्णांकf->dev, "tx_max must be in the [%u, %u] range\n", min, max);

	वापस val;
पूर्ण

अटल sमाप_प्रकार cdc_ncm_show_min_tx_pkt(काष्ठा device *d, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usbnet *dev = netdev_priv(to_net_dev(d));
	काष्ठा cdc_ncm_ctx *ctx = (काष्ठा cdc_ncm_ctx *)dev->data[0];

	वापस प्र_लिखो(buf, "%u\n", ctx->min_tx_pkt);
पूर्ण

अटल sमाप_प्रकार cdc_ncm_show_rx_max(काष्ठा device *d, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usbnet *dev = netdev_priv(to_net_dev(d));
	काष्ठा cdc_ncm_ctx *ctx = (काष्ठा cdc_ncm_ctx *)dev->data[0];

	वापस प्र_लिखो(buf, "%u\n", ctx->rx_max);
पूर्ण

अटल sमाप_प्रकार cdc_ncm_show_tx_max(काष्ठा device *d, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usbnet *dev = netdev_priv(to_net_dev(d));
	काष्ठा cdc_ncm_ctx *ctx = (काष्ठा cdc_ncm_ctx *)dev->data[0];

	वापस प्र_लिखो(buf, "%u\n", ctx->tx_max);
पूर्ण

अटल sमाप_प्रकार cdc_ncm_show_tx_समयr_usecs(काष्ठा device *d, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usbnet *dev = netdev_priv(to_net_dev(d));
	काष्ठा cdc_ncm_ctx *ctx = (काष्ठा cdc_ncm_ctx *)dev->data[0];

	वापस प्र_लिखो(buf, "%u\n", ctx->समयr_पूर्णांकerval / (u32)NSEC_PER_USEC);
पूर्ण

अटल sमाप_प्रकार cdc_ncm_store_min_tx_pkt(काष्ठा device *d,  काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा usbnet *dev = netdev_priv(to_net_dev(d));
	काष्ठा cdc_ncm_ctx *ctx = (काष्ठा cdc_ncm_ctx *)dev->data[0];
	अचिन्हित दीर्घ val;

	/* no need to restrict values - anything from 0 to infinity is OK */
	अगर (kम_से_अदीर्घ(buf, 0, &val))
		वापस -EINVAL;

	ctx->min_tx_pkt = val;
	वापस len;
पूर्ण

अटल sमाप_प्रकार cdc_ncm_store_rx_max(काष्ठा device *d,  काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा usbnet *dev = netdev_priv(to_net_dev(d));
	काष्ठा cdc_ncm_ctx *ctx = (काष्ठा cdc_ncm_ctx *)dev->data[0];
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 0, &val) || cdc_ncm_check_rx_max(dev, val) != val)
		वापस -EINVAL;

	cdc_ncm_update_rxtx_max(dev, val, ctx->tx_max);
	वापस len;
पूर्ण

अटल sमाप_प्रकार cdc_ncm_store_tx_max(काष्ठा device *d,  काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा usbnet *dev = netdev_priv(to_net_dev(d));
	काष्ठा cdc_ncm_ctx *ctx = (काष्ठा cdc_ncm_ctx *)dev->data[0];
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 0, &val) || cdc_ncm_check_tx_max(dev, val) != val)
		वापस -EINVAL;

	cdc_ncm_update_rxtx_max(dev, ctx->rx_max, val);
	वापस len;
पूर्ण

अटल sमाप_प्रकार cdc_ncm_store_tx_समयr_usecs(काष्ठा device *d,  काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा usbnet *dev = netdev_priv(to_net_dev(d));
	काष्ठा cdc_ncm_ctx *ctx = (काष्ठा cdc_ncm_ctx *)dev->data[0];
	sमाप_प्रकार ret;
	अचिन्हित दीर्घ val;

	ret = kम_से_अदीर्घ(buf, 0, &val);
	अगर (ret)
		वापस ret;
	अगर (val && (val < CDC_NCM_TIMER_INTERVAL_MIN || val > CDC_NCM_TIMER_INTERVAL_MAX))
		वापस -EINVAL;

	spin_lock_bh(&ctx->mtx);
	ctx->समयr_पूर्णांकerval = val * NSEC_PER_USEC;
	अगर (!ctx->समयr_पूर्णांकerval)
		ctx->tx_समयr_pending = 0;
	spin_unlock_bh(&ctx->mtx);
	वापस len;
पूर्ण

अटल DEVICE_ATTR(min_tx_pkt, 0644, cdc_ncm_show_min_tx_pkt, cdc_ncm_store_min_tx_pkt);
अटल DEVICE_ATTR(rx_max, 0644, cdc_ncm_show_rx_max, cdc_ncm_store_rx_max);
अटल DEVICE_ATTR(tx_max, 0644, cdc_ncm_show_tx_max, cdc_ncm_store_tx_max);
अटल DEVICE_ATTR(tx_समयr_usecs, 0644, cdc_ncm_show_tx_समयr_usecs, cdc_ncm_store_tx_समयr_usecs);

अटल sमाप_प्रकार ndp_to_end_show(काष्ठा device *d, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usbnet *dev = netdev_priv(to_net_dev(d));
	काष्ठा cdc_ncm_ctx *ctx = (काष्ठा cdc_ncm_ctx *)dev->data[0];

	वापस प्र_लिखो(buf, "%c\n", ctx->drvflags & CDC_NCM_FLAG_NDP_TO_END ? 'Y' : 'N');
पूर्ण

अटल sमाप_प्रकार ndp_to_end_store(काष्ठा device *d,  काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा usbnet *dev = netdev_priv(to_net_dev(d));
	काष्ठा cdc_ncm_ctx *ctx = (काष्ठा cdc_ncm_ctx *)dev->data[0];
	bool enable;

	अगर (strtobool(buf, &enable))
		वापस -EINVAL;

	/* no change? */
	अगर (enable == (ctx->drvflags & CDC_NCM_FLAG_NDP_TO_END))
		वापस len;

	अगर (enable) अणु
		अगर (ctx->is_ndp16 && !ctx->delayed_ndp16) अणु
			ctx->delayed_ndp16 = kzalloc(ctx->max_ndp_size, GFP_KERNEL);
			अगर (!ctx->delayed_ndp16)
				वापस -ENOMEM;
		पूर्ण
		अगर (!ctx->is_ndp16 && !ctx->delayed_ndp32) अणु
			ctx->delayed_ndp32 = kzalloc(ctx->max_ndp_size, GFP_KERNEL);
			अगर (!ctx->delayed_ndp32)
				वापस -ENOMEM;
		पूर्ण
	पूर्ण

	/* flush pending data beक्रमe changing flag */
	netअगर_tx_lock_bh(dev->net);
	usbnet_start_xmit(शून्य, dev->net);
	spin_lock_bh(&ctx->mtx);
	अगर (enable)
		ctx->drvflags |= CDC_NCM_FLAG_NDP_TO_END;
	अन्यथा
		ctx->drvflags &= ~CDC_NCM_FLAG_NDP_TO_END;
	spin_unlock_bh(&ctx->mtx);
	netअगर_tx_unlock_bh(dev->net);

	वापस len;
पूर्ण
अटल DEVICE_ATTR_RW(ndp_to_end);

#घोषणा NCM_PARM_ATTR(name, क्रमmat, tocpu)				\
अटल sमाप_प्रकार cdc_ncm_show_##name(काष्ठा device *d, काष्ठा device_attribute *attr, अक्षर *buf) \
अणु \
	काष्ठा usbnet *dev = netdev_priv(to_net_dev(d)); \
	काष्ठा cdc_ncm_ctx *ctx = (काष्ठा cdc_ncm_ctx *)dev->data[0]; \
	वापस प्र_लिखो(buf, क्रमmat "\n", tocpu(ctx->ncm_parm.name));	\
पूर्ण \
अटल DEVICE_ATTR(name, 0444, cdc_ncm_show_##name, शून्य)

NCM_PARM_ATTR(bmNtbFormatsSupported, "0x%04x", le16_to_cpu);
NCM_PARM_ATTR(dwNtbInMaxSize, "%u", le32_to_cpu);
NCM_PARM_ATTR(wNdpInDivisor, "%u", le16_to_cpu);
NCM_PARM_ATTR(wNdpInPayloadReमुख्यder, "%u", le16_to_cpu);
NCM_PARM_ATTR(wNdpInAlignment, "%u", le16_to_cpu);
NCM_PARM_ATTR(dwNtbOutMaxSize, "%u", le32_to_cpu);
NCM_PARM_ATTR(wNdpOutDivisor, "%u", le16_to_cpu);
NCM_PARM_ATTR(wNdpOutPayloadReमुख्यder, "%u", le16_to_cpu);
NCM_PARM_ATTR(wNdpOutAlignment, "%u", le16_to_cpu);
NCM_PARM_ATTR(wNtbOutMaxDatagrams, "%u", le16_to_cpu);

अटल काष्ठा attribute *cdc_ncm_sysfs_attrs[] = अणु
	&dev_attr_min_tx_pkt.attr,
	&dev_attr_ndp_to_end.attr,
	&dev_attr_rx_max.attr,
	&dev_attr_tx_max.attr,
	&dev_attr_tx_समयr_usecs.attr,
	&dev_attr_bmNtbFormatsSupported.attr,
	&dev_attr_dwNtbInMaxSize.attr,
	&dev_attr_wNdpInDivisor.attr,
	&dev_attr_wNdpInPayloadReमुख्यder.attr,
	&dev_attr_wNdpInAlignment.attr,
	&dev_attr_dwNtbOutMaxSize.attr,
	&dev_attr_wNdpOutDivisor.attr,
	&dev_attr_wNdpOutPayloadReमुख्यder.attr,
	&dev_attr_wNdpOutAlignment.attr,
	&dev_attr_wNtbOutMaxDatagrams.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group cdc_ncm_sysfs_attr_group = अणु
	.name = "cdc_ncm",
	.attrs = cdc_ncm_sysfs_attrs,
पूर्ण;

/* handle rx_max and tx_max changes */
अटल व्योम cdc_ncm_update_rxtx_max(काष्ठा usbnet *dev, u32 new_rx, u32 new_tx)
अणु
	काष्ठा cdc_ncm_ctx *ctx = (काष्ठा cdc_ncm_ctx *)dev->data[0];
	u8 अगरace_no = ctx->control->cur_altsetting->desc.bInterfaceNumber;
	u32 val;

	val = cdc_ncm_check_rx_max(dev, new_rx);

	/* inक्रमm device about NTB input size changes */
	अगर (val != ctx->rx_max) अणु
		__le32 dwNtbInMaxSize = cpu_to_le32(val);

		dev_info(&dev->पूर्णांकf->dev, "setting rx_max = %u\n", val);

		/* tell device to use new size */
		अगर (usbnet_ग_लिखो_cmd(dev, USB_CDC_SET_NTB_INPUT_SIZE,
				     USB_TYPE_CLASS | USB_सूची_OUT
				     | USB_RECIP_INTERFACE,
				     0, अगरace_no, &dwNtbInMaxSize, 4) < 0)
			dev_dbg(&dev->पूर्णांकf->dev, "Setting NTB Input Size failed\n");
		अन्यथा
			ctx->rx_max = val;
	पूर्ण

	/* usbnet use these values क्रम sizing rx queues */
	अगर (dev->rx_urb_size != ctx->rx_max) अणु
		dev->rx_urb_size = ctx->rx_max;
		अगर (netअगर_running(dev->net))
			usbnet_unlink_rx_urbs(dev);
	पूर्ण

	val = cdc_ncm_check_tx_max(dev, new_tx);
	अगर (val != ctx->tx_max)
		dev_info(&dev->पूर्णांकf->dev, "setting tx_max = %u\n", val);

	/* Adding a pad byte here अगर necessary simplअगरies the handling
	 * in cdc_ncm_fill_tx_frame, making tx_max always represent
	 * the real skb max size.
	 *
	 * We cannot use dev->maxpacket here because this is called from
	 * .bind which is called beक्रमe usbnet sets up dev->maxpacket
	 */
	अगर (val != le32_to_cpu(ctx->ncm_parm.dwNtbOutMaxSize) &&
	    val % usb_maxpacket(dev->udev, dev->out, 1) == 0)
		val++;

	/* we might need to flush any pending tx buffers अगर running */
	अगर (netअगर_running(dev->net) && val > ctx->tx_max) अणु
		netअगर_tx_lock_bh(dev->net);
		usbnet_start_xmit(शून्य, dev->net);
		/* make sure tx_curr_skb is पुनः_स्मृतिated अगर it was empty */
		अगर (ctx->tx_curr_skb) अणु
			dev_kमुक्त_skb_any(ctx->tx_curr_skb);
			ctx->tx_curr_skb = शून्य;
		पूर्ण
		ctx->tx_max = val;
		netअगर_tx_unlock_bh(dev->net);
	पूर्ण अन्यथा अणु
		ctx->tx_max = val;
	पूर्ण

	dev->hard_mtu = ctx->tx_max;

	/* max qlen depend on hard_mtu and rx_urb_size */
	usbnet_update_max_qlen(dev);

	/* never pad more than 3 full USB packets per transfer */
	ctx->min_tx_pkt = clamp_t(u16, ctx->tx_max - 3 * usb_maxpacket(dev->udev, dev->out, 1),
				  CDC_NCM_MIN_TX_PKT, ctx->tx_max);
पूर्ण

/* helpers क्रम NCM and MBIM dअगरferences */
अटल u8 cdc_ncm_flags(काष्ठा usbnet *dev)
अणु
	काष्ठा cdc_ncm_ctx *ctx = (काष्ठा cdc_ncm_ctx *)dev->data[0];

	अगर (cdc_ncm_comm_पूर्णांकf_is_mbim(dev->पूर्णांकf->cur_altsetting) && ctx->mbim_desc)
		वापस ctx->mbim_desc->bmNetworkCapabilities;
	अगर (ctx->func_desc)
		वापस ctx->func_desc->bmNetworkCapabilities;
	वापस 0;
पूर्ण

अटल पूर्णांक cdc_ncm_eth_hlen(काष्ठा usbnet *dev)
अणु
	अगर (cdc_ncm_comm_पूर्णांकf_is_mbim(dev->पूर्णांकf->cur_altsetting))
		वापस 0;
	वापस ETH_HLEN;
पूर्ण

अटल u32 cdc_ncm_min_dgram_size(काष्ठा usbnet *dev)
अणु
	अगर (cdc_ncm_comm_पूर्णांकf_is_mbim(dev->पूर्णांकf->cur_altsetting))
		वापस CDC_MBIM_MIN_DATAGRAM_SIZE;
	वापस CDC_NCM_MIN_DATAGRAM_SIZE;
पूर्ण

अटल u32 cdc_ncm_max_dgram_size(काष्ठा usbnet *dev)
अणु
	काष्ठा cdc_ncm_ctx *ctx = (काष्ठा cdc_ncm_ctx *)dev->data[0];

	अगर (cdc_ncm_comm_पूर्णांकf_is_mbim(dev->पूर्णांकf->cur_altsetting) && ctx->mbim_desc)
		वापस le16_to_cpu(ctx->mbim_desc->wMaxSegmentSize);
	अगर (ctx->ether_desc)
		वापस le16_to_cpu(ctx->ether_desc->wMaxSegmentSize);
	वापस CDC_NCM_MAX_DATAGRAM_SIZE;
पूर्ण

/* initial one-समय device setup.  MUST be called with the data पूर्णांकerface
 * in altsetting 0
 */
अटल पूर्णांक cdc_ncm_init(काष्ठा usbnet *dev)
अणु
	काष्ठा cdc_ncm_ctx *ctx = (काष्ठा cdc_ncm_ctx *)dev->data[0];
	u8 अगरace_no = ctx->control->cur_altsetting->desc.bInterfaceNumber;
	पूर्णांक err;

	err = usbnet_पढ़ो_cmd(dev, USB_CDC_GET_NTB_PARAMETERS,
			      USB_TYPE_CLASS | USB_सूची_IN
			      |USB_RECIP_INTERFACE,
			      0, अगरace_no, &ctx->ncm_parm,
			      माप(ctx->ncm_parm));
	अगर (err < 0) अणु
		dev_err(&dev->पूर्णांकf->dev, "failed GET_NTB_PARAMETERS\n");
		वापस err; /* GET_NTB_PARAMETERS is required */
	पूर्ण

	/* set CRC Mode */
	अगर (cdc_ncm_flags(dev) & USB_CDC_NCM_NCAP_CRC_MODE) अणु
		dev_dbg(&dev->पूर्णांकf->dev, "Setting CRC mode off\n");
		err = usbnet_ग_लिखो_cmd(dev, USB_CDC_SET_CRC_MODE,
				       USB_TYPE_CLASS | USB_सूची_OUT
				       | USB_RECIP_INTERFACE,
				       USB_CDC_NCM_CRC_NOT_APPENDED,
				       अगरace_no, शून्य, 0);
		अगर (err < 0)
			dev_err(&dev->पूर्णांकf->dev, "SET_CRC_MODE failed\n");
	पूर्ण

	/* use ndp16 by शेष */
	ctx->is_ndp16 = 1;

	/* set NTB क्रमmat, अगर both क्रमmats are supported.
	 *
	 * "The host shall only send this command जबतक the NCM Data
	 *  Interface is in alternate setting 0."
	 */
	अगर (le16_to_cpu(ctx->ncm_parm.bmNtbFormatsSupported) &
						USB_CDC_NCM_NTB32_SUPPORTED) अणु
		अगर (ctx->drvflags & CDC_NCM_FLAG_PREFER_NTB32) अणु
			ctx->is_ndp16 = 0;
			dev_dbg(&dev->पूर्णांकf->dev, "Setting NTB format to 32-bit\n");
			err = usbnet_ग_लिखो_cmd(dev, USB_CDC_SET_NTB_FORMAT,
					       USB_TYPE_CLASS | USB_सूची_OUT
					       | USB_RECIP_INTERFACE,
					       USB_CDC_NCM_NTB32_FORMAT,
					       अगरace_no, शून्य, 0);
		पूर्ण अन्यथा अणु
			ctx->is_ndp16 = 1;
			dev_dbg(&dev->पूर्णांकf->dev, "Setting NTB format to 16-bit\n");
			err = usbnet_ग_लिखो_cmd(dev, USB_CDC_SET_NTB_FORMAT,
					       USB_TYPE_CLASS | USB_सूची_OUT
					       | USB_RECIP_INTERFACE,
					       USB_CDC_NCM_NTB16_FORMAT,
					       अगरace_no, शून्य, 0);
		पूर्ण
		अगर (err < 0) अणु
			ctx->is_ndp16 = 1;
			dev_err(&dev->पूर्णांकf->dev, "SET_NTB_FORMAT failed\n");
		पूर्ण
	पूर्ण

	/* set initial device values */
	ctx->rx_max = le32_to_cpu(ctx->ncm_parm.dwNtbInMaxSize);
	ctx->tx_max = le32_to_cpu(ctx->ncm_parm.dwNtbOutMaxSize);
	ctx->tx_reमुख्यder = le16_to_cpu(ctx->ncm_parm.wNdpOutPayloadReमुख्यder);
	ctx->tx_modulus = le16_to_cpu(ctx->ncm_parm.wNdpOutDivisor);
	ctx->tx_ndp_modulus = le16_to_cpu(ctx->ncm_parm.wNdpOutAlignment);
	/* devices prior to NCM Errata shall set this field to zero */
	ctx->tx_max_datagrams = le16_to_cpu(ctx->ncm_parm.wNtbOutMaxDatagrams);

	dev_dbg(&dev->पूर्णांकf->dev,
		"dwNtbInMaxSize=%u dwNtbOutMaxSize=%u wNdpOutPayloadRemainder=%u wNdpOutDivisor=%u wNdpOutAlignment=%u wNtbOutMaxDatagrams=%u flags=0x%x\n",
		ctx->rx_max, ctx->tx_max, ctx->tx_reमुख्यder, ctx->tx_modulus,
		ctx->tx_ndp_modulus, ctx->tx_max_datagrams, cdc_ncm_flags(dev));

	/* max count of tx datagrams */
	अगर ((ctx->tx_max_datagrams == 0) ||
			(ctx->tx_max_datagrams > CDC_NCM_DPT_DATAGRAMS_MAX))
		ctx->tx_max_datagrams = CDC_NCM_DPT_DATAGRAMS_MAX;

	/* set up maximum NDP size */
	अगर (ctx->is_ndp16)
		ctx->max_ndp_size = माप(काष्ठा usb_cdc_ncm_ndp16) + (ctx->tx_max_datagrams + 1) * माप(काष्ठा usb_cdc_ncm_dpe16);
	अन्यथा
		ctx->max_ndp_size = माप(काष्ठा usb_cdc_ncm_ndp32) + (ctx->tx_max_datagrams + 1) * माप(काष्ठा usb_cdc_ncm_dpe32);

	/* initial coalescing समयr पूर्णांकerval */
	ctx->समयr_पूर्णांकerval = CDC_NCM_TIMER_INTERVAL_USEC * NSEC_PER_USEC;

	वापस 0;
पूर्ण

/* set a new max datagram size */
अटल व्योम cdc_ncm_set_dgram_size(काष्ठा usbnet *dev, पूर्णांक new_size)
अणु
	काष्ठा cdc_ncm_ctx *ctx = (काष्ठा cdc_ncm_ctx *)dev->data[0];
	u8 अगरace_no = ctx->control->cur_altsetting->desc.bInterfaceNumber;
	__le16 max_datagram_size;
	u16 mbim_mtu;
	पूर्णांक err;

	/* set शेष based on descriptors */
	ctx->max_datagram_size = clamp_t(u32, new_size,
					 cdc_ncm_min_dgram_size(dev),
					 CDC_NCM_MAX_DATAGRAM_SIZE);

	/* inक्रमm the device about the selected Max Datagram Size? */
	अगर (!(cdc_ncm_flags(dev) & USB_CDC_NCM_NCAP_MAX_DATAGRAM_SIZE))
		जाओ out;

	/* पढ़ो current mtu value from device */
	err = usbnet_पढ़ो_cmd(dev, USB_CDC_GET_MAX_DATAGRAM_SIZE,
			      USB_TYPE_CLASS | USB_सूची_IN | USB_RECIP_INTERFACE,
			      0, अगरace_no, &max_datagram_size, माप(max_datagram_size));
	अगर (err != माप(max_datagram_size)) अणु
		dev_dbg(&dev->पूर्णांकf->dev, "GET_MAX_DATAGRAM_SIZE failed\n");
		जाओ out;
	पूर्ण

	अगर (le16_to_cpu(max_datagram_size) == ctx->max_datagram_size)
		जाओ out;

	max_datagram_size = cpu_to_le16(ctx->max_datagram_size);
	err = usbnet_ग_लिखो_cmd(dev, USB_CDC_SET_MAX_DATAGRAM_SIZE,
			       USB_TYPE_CLASS | USB_सूची_OUT | USB_RECIP_INTERFACE,
			       0, अगरace_no, &max_datagram_size, माप(max_datagram_size));
	अगर (err < 0)
		dev_dbg(&dev->पूर्णांकf->dev, "SET_MAX_DATAGRAM_SIZE failed\n");

out:
	/* set MTU to max supported by the device अगर necessary */
	dev->net->mtu = min_t(पूर्णांक, dev->net->mtu, ctx->max_datagram_size - cdc_ncm_eth_hlen(dev));

	/* करो not exceed operater preferred MTU */
	अगर (ctx->mbim_extended_desc) अणु
		mbim_mtu = le16_to_cpu(ctx->mbim_extended_desc->wMTU);
		अगर (mbim_mtu != 0 && mbim_mtu < dev->net->mtu)
			dev->net->mtu = mbim_mtu;
	पूर्ण
पूर्ण

अटल व्योम cdc_ncm_fix_modulus(काष्ठा usbnet *dev)
अणु
	काष्ठा cdc_ncm_ctx *ctx = (काष्ठा cdc_ncm_ctx *)dev->data[0];
	u32 val;

	/*
	 * verअगरy that the काष्ठाure alignment is:
	 * - घातer of two
	 * - not greater than the maximum transmit length
	 * - not less than four bytes
	 */
	val = ctx->tx_ndp_modulus;

	अगर ((val < USB_CDC_NCM_NDP_ALIGN_MIN_SIZE) ||
	    (val != ((-val) & val)) || (val >= ctx->tx_max)) अणु
		dev_dbg(&dev->पूर्णांकf->dev, "Using default alignment: 4 bytes\n");
		ctx->tx_ndp_modulus = USB_CDC_NCM_NDP_ALIGN_MIN_SIZE;
	पूर्ण

	/*
	 * verअगरy that the payload alignment is:
	 * - घातer of two
	 * - not greater than the maximum transmit length
	 * - not less than four bytes
	 */
	val = ctx->tx_modulus;

	अगर ((val < USB_CDC_NCM_NDP_ALIGN_MIN_SIZE) ||
	    (val != ((-val) & val)) || (val >= ctx->tx_max)) अणु
		dev_dbg(&dev->पूर्णांकf->dev, "Using default transmit modulus: 4 bytes\n");
		ctx->tx_modulus = USB_CDC_NCM_NDP_ALIGN_MIN_SIZE;
	पूर्ण

	/* verअगरy the payload reमुख्यder */
	अगर (ctx->tx_reमुख्यder >= ctx->tx_modulus) अणु
		dev_dbg(&dev->पूर्णांकf->dev, "Using default transmit remainder: 0 bytes\n");
		ctx->tx_reमुख्यder = 0;
	पूर्ण

	/* adjust TX-reमुख्यder according to NCM specअगरication. */
	ctx->tx_reमुख्यder = ((ctx->tx_reमुख्यder - cdc_ncm_eth_hlen(dev)) &
			     (ctx->tx_modulus - 1));
पूर्ण

अटल पूर्णांक cdc_ncm_setup(काष्ठा usbnet *dev)
अणु
	काष्ठा cdc_ncm_ctx *ctx = (काष्ठा cdc_ncm_ctx *)dev->data[0];
	u32 def_rx, def_tx;

	/* be conservative when selecting पूर्णांकial buffer size to
	 * increase the number of hosts this will work क्रम
	 */
	def_rx = min_t(u32, CDC_NCM_NTB_DEF_SIZE_RX,
		       le32_to_cpu(ctx->ncm_parm.dwNtbInMaxSize));
	def_tx = min_t(u32, CDC_NCM_NTB_DEF_SIZE_TX,
		       le32_to_cpu(ctx->ncm_parm.dwNtbOutMaxSize));

	/* clamp rx_max and tx_max and inक्रमm device */
	cdc_ncm_update_rxtx_max(dev, def_rx, def_tx);

	/* sanitize the modulus and reमुख्यder values */
	cdc_ncm_fix_modulus(dev);

	/* set max datagram size */
	cdc_ncm_set_dgram_size(dev, cdc_ncm_max_dgram_size(dev));
	वापस 0;
पूर्ण

अटल व्योम
cdc_ncm_find_endpoपूर्णांकs(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_host_endpoपूर्णांक *e, *in = शून्य, *out = शून्य;
	u8 ep;

	क्रम (ep = 0; ep < पूर्णांकf->cur_altsetting->desc.bNumEndpoपूर्णांकs; ep++) अणु
		e = पूर्णांकf->cur_altsetting->endpoपूर्णांक + ep;

		/* ignore endpoपूर्णांकs which cannot transfer data */
		अगर (!usb_endpoपूर्णांक_maxp(&e->desc))
			जारी;

		चयन (e->desc.bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) अणु
		हाल USB_ENDPOINT_XFER_INT:
			अगर (usb_endpoपूर्णांक_dir_in(&e->desc)) अणु
				अगर (!dev->status)
					dev->status = e;
			पूर्ण
			अवरोध;

		हाल USB_ENDPOINT_XFER_BULK:
			अगर (usb_endpoपूर्णांक_dir_in(&e->desc)) अणु
				अगर (!in)
					in = e;
			पूर्ण अन्यथा अणु
				अगर (!out)
					out = e;
			पूर्ण
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (in && !dev->in)
		dev->in = usb_rcvbulkpipe(dev->udev,
					  in->desc.bEndpoपूर्णांकAddress &
					  USB_ENDPOINT_NUMBER_MASK);
	अगर (out && !dev->out)
		dev->out = usb_sndbulkpipe(dev->udev,
					   out->desc.bEndpoपूर्णांकAddress &
					   USB_ENDPOINT_NUMBER_MASK);
पूर्ण

अटल व्योम cdc_ncm_मुक्त(काष्ठा cdc_ncm_ctx *ctx)
अणु
	अगर (ctx == शून्य)
		वापस;

	अगर (ctx->tx_rem_skb != शून्य) अणु
		dev_kमुक्त_skb_any(ctx->tx_rem_skb);
		ctx->tx_rem_skb = शून्य;
	पूर्ण

	अगर (ctx->tx_curr_skb != शून्य) अणु
		dev_kमुक्त_skb_any(ctx->tx_curr_skb);
		ctx->tx_curr_skb = शून्य;
	पूर्ण

	अगर (ctx->is_ndp16)
		kमुक्त(ctx->delayed_ndp16);
	अन्यथा
		kमुक्त(ctx->delayed_ndp32);

	kमुक्त(ctx);
पूर्ण

/* we need to override the usbnet change_mtu nकरो क्रम two reasons:
 *  - respect the negotiated maximum datagram size
 *  - aव्योम unwanted changes to rx and tx buffers
 */
पूर्णांक cdc_ncm_change_mtu(काष्ठा net_device *net, पूर्णांक new_mtu)
अणु
	काष्ठा usbnet *dev = netdev_priv(net);

	net->mtu = new_mtu;
	cdc_ncm_set_dgram_size(dev, new_mtu + cdc_ncm_eth_hlen(dev));

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cdc_ncm_change_mtu);

अटल स्थिर काष्ठा net_device_ops cdc_ncm_netdev_ops = अणु
	.nकरो_खोलो	     = usbnet_खोलो,
	.nकरो_stop	     = usbnet_stop,
	.nकरो_start_xmit	     = usbnet_start_xmit,
	.nकरो_tx_समयout	     = usbnet_tx_समयout,
	.nकरो_set_rx_mode     = usbnet_set_rx_mode,
	.nकरो_get_stats64     = dev_get_tstats64,
	.nकरो_change_mtu	     = cdc_ncm_change_mtu,
	.nकरो_set_mac_address = eth_mac_addr,
	.nकरो_validate_addr   = eth_validate_addr,
पूर्ण;

पूर्णांक cdc_ncm_bind_common(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf, u8 data_altsetting, पूर्णांक drvflags)
अणु
	काष्ठा cdc_ncm_ctx *ctx;
	काष्ठा usb_driver *driver;
	u8 *buf;
	पूर्णांक len;
	पूर्णांक temp;
	u8 अगरace_no;
	काष्ठा usb_cdc_parsed_header hdr;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->dev = dev;

	hrसमयr_init(&ctx->tx_समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	ctx->tx_समयr.function = &cdc_ncm_tx_समयr_cb;
	tasklet_setup(&ctx->bh, cdc_ncm_txpath_bh);
	atomic_set(&ctx->stop, 0);
	spin_lock_init(&ctx->mtx);

	/* store ctx poपूर्णांकer in device data field */
	dev->data[0] = (अचिन्हित दीर्घ)ctx;

	/* only the control पूर्णांकerface can be successfully probed */
	ctx->control = पूर्णांकf;

	/* get some poपूर्णांकers */
	driver = driver_of(पूर्णांकf);
	buf = पूर्णांकf->cur_altsetting->extra;
	len = पूर्णांकf->cur_altsetting->extralen;

	/* parse through descriptors associated with control पूर्णांकerface */
	cdc_parse_cdc_header(&hdr, पूर्णांकf, buf, len);

	अगर (hdr.usb_cdc_जोड़_desc)
		ctx->data = usb_अगरnum_to_अगर(dev->udev,
					    hdr.usb_cdc_जोड़_desc->bSlaveInterface0);
	ctx->ether_desc = hdr.usb_cdc_ether_desc;
	ctx->func_desc = hdr.usb_cdc_ncm_desc;
	ctx->mbim_desc = hdr.usb_cdc_mbim_desc;
	ctx->mbim_extended_desc = hdr.usb_cdc_mbim_extended_desc;

	/* some buggy devices have an IAD but no CDC Union */
	अगर (!hdr.usb_cdc_जोड़_desc && पूर्णांकf->पूर्णांकf_assoc && पूर्णांकf->पूर्णांकf_assoc->bInterfaceCount == 2) अणु
		ctx->data = usb_अगरnum_to_अगर(dev->udev, पूर्णांकf->cur_altsetting->desc.bInterfaceNumber + 1);
		dev_dbg(&पूर्णांकf->dev, "CDC Union missing - got slave from IAD\n");
	पूर्ण

	/* check अगर we got everything */
	अगर (!ctx->data) अणु
		dev_err(&पूर्णांकf->dev, "CDC Union missing and no IAD found\n");
		जाओ error;
	पूर्ण
	अगर (cdc_ncm_comm_पूर्णांकf_is_mbim(पूर्णांकf->cur_altsetting)) अणु
		अगर (!ctx->mbim_desc) अणु
			dev_err(&पूर्णांकf->dev, "MBIM functional descriptor missing\n");
			जाओ error;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!ctx->ether_desc || !ctx->func_desc) अणु
			dev_err(&पूर्णांकf->dev, "NCM or ECM functional descriptors missing\n");
			जाओ error;
		पूर्ण
	पूर्ण

	/* claim data पूर्णांकerface, अगर dअगरferent from control */
	अगर (ctx->data != ctx->control) अणु
		temp = usb_driver_claim_पूर्णांकerface(driver, ctx->data, dev);
		अगर (temp) अणु
			dev_err(&पूर्णांकf->dev, "failed to claim data intf\n");
			जाओ error;
		पूर्ण
	पूर्ण

	अगरace_no = ctx->data->cur_altsetting->desc.bInterfaceNumber;

	/* Device-specअगरic flags */
	ctx->drvflags = drvflags;

	/* Reset data पूर्णांकerface. Some devices will not reset properly
	 * unless they are configured first.  Toggle the altsetting to
	 * क्रमce a reset.
	 * Some other devices करो not work properly with this procedure
	 * that can be aव्योमed using quirk CDC_MBIM_FLAG_AVOID_ALTSETTING_TOGGLE
	 */
	अगर (!(ctx->drvflags & CDC_MBIM_FLAG_AVOID_ALTSETTING_TOGGLE))
		usb_set_पूर्णांकerface(dev->udev, अगरace_no, data_altsetting);

	temp = usb_set_पूर्णांकerface(dev->udev, अगरace_no, 0);
	अगर (temp) अणु
		dev_dbg(&पूर्णांकf->dev, "set interface failed\n");
		जाओ error2;
	पूर्ण

	/* initialize basic device settings */
	अगर (cdc_ncm_init(dev))
		जाओ error2;

	/* Some firmwares need a छोड़ो here or they will silently fail
	 * to set up the पूर्णांकerface properly.  This value was decided
	 * empirically on a Sierra Wireless MC7455 running 02.08.02.00
	 * firmware.
	 */
	usleep_range(10000, 20000);

	/* configure data पूर्णांकerface */
	temp = usb_set_पूर्णांकerface(dev->udev, अगरace_no, data_altsetting);
	अगर (temp) अणु
		dev_dbg(&पूर्णांकf->dev, "set interface failed\n");
		जाओ error2;
	पूर्ण

	cdc_ncm_find_endpoपूर्णांकs(dev, ctx->data);
	cdc_ncm_find_endpoपूर्णांकs(dev, ctx->control);
	अगर (!dev->in || !dev->out || !dev->status) अणु
		dev_dbg(&पूर्णांकf->dev, "failed to collect endpoints\n");
		जाओ error2;
	पूर्ण

	usb_set_पूर्णांकfdata(ctx->control, dev);

	अगर (ctx->ether_desc) अणु
		temp = usbnet_get_ethernet_addr(dev, ctx->ether_desc->iMACAddress);
		अगर (temp) अणु
			dev_err(&पूर्णांकf->dev, "failed to get mac address\n");
			जाओ error2;
		पूर्ण
		dev_info(&पूर्णांकf->dev, "MAC-Address: %pM\n", dev->net->dev_addr);
	पूर्ण

	/* finish setting up the device specअगरic data */
	cdc_ncm_setup(dev);

	/* Allocate the delayed NDP अगर needed. */
	अगर (ctx->drvflags & CDC_NCM_FLAG_NDP_TO_END) अणु
		अगर (ctx->is_ndp16) अणु
			ctx->delayed_ndp16 = kzalloc(ctx->max_ndp_size, GFP_KERNEL);
			अगर (!ctx->delayed_ndp16)
				जाओ error2;
		पूर्ण अन्यथा अणु
			ctx->delayed_ndp32 = kzalloc(ctx->max_ndp_size, GFP_KERNEL);
			अगर (!ctx->delayed_ndp32)
				जाओ error2;
		पूर्ण
		dev_info(&पूर्णांकf->dev, "NDP will be placed at end of frame for this device.");
	पूर्ण

	/* override ethtool_ops */
	dev->net->ethtool_ops = &cdc_ncm_ethtool_ops;

	/* add our sysfs attrs */
	dev->net->sysfs_groups[0] = &cdc_ncm_sysfs_attr_group;

	/* must handle MTU changes */
	dev->net->netdev_ops = &cdc_ncm_netdev_ops;
	dev->net->max_mtu = cdc_ncm_max_dgram_size(dev) - cdc_ncm_eth_hlen(dev);

	वापस 0;

error2:
	usb_set_पूर्णांकfdata(ctx->control, शून्य);
	usb_set_पूर्णांकfdata(ctx->data, शून्य);
	अगर (ctx->data != ctx->control)
		usb_driver_release_पूर्णांकerface(driver, ctx->data);
error:
	cdc_ncm_मुक्त((काष्ठा cdc_ncm_ctx *)dev->data[0]);
	dev->data[0] = 0;
	dev_info(&पूर्णांकf->dev, "bind() failure\n");
	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL_GPL(cdc_ncm_bind_common);

व्योम cdc_ncm_unbind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा cdc_ncm_ctx *ctx = (काष्ठा cdc_ncm_ctx *)dev->data[0];
	काष्ठा usb_driver *driver = driver_of(पूर्णांकf);

	अगर (ctx == शून्य)
		वापस;		/* no setup */

	atomic_set(&ctx->stop, 1);

	hrसमयr_cancel(&ctx->tx_समयr);

	tasklet_समाप्त(&ctx->bh);

	/* handle devices with combined control and data पूर्णांकerface */
	अगर (ctx->control == ctx->data)
		ctx->data = शून्य;

	/* disconnect master --> disconnect slave */
	अगर (पूर्णांकf == ctx->control && ctx->data) अणु
		usb_set_पूर्णांकfdata(ctx->data, शून्य);
		usb_driver_release_पूर्णांकerface(driver, ctx->data);
		ctx->data = शून्य;

	पूर्ण अन्यथा अगर (पूर्णांकf == ctx->data && ctx->control) अणु
		usb_set_पूर्णांकfdata(ctx->control, शून्य);
		usb_driver_release_पूर्णांकerface(driver, ctx->control);
		ctx->control = शून्य;
	पूर्ण

	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
	cdc_ncm_मुक्त(ctx);
पूर्ण
EXPORT_SYMBOL_GPL(cdc_ncm_unbind);

/* Return the number of the MBIM control पूर्णांकerface altsetting अगरf it
 * is preferred and available,
 */
u8 cdc_ncm_select_altsetting(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_host_पूर्णांकerface *alt;

	/* The MBIM spec defines a NCM compatible शेष altsetting,
	 * which we may have matched:
	 *
	 *  "Functions that implement both NCM 1.0 and MBIM (an
	 *   ै NCM/MBIM functionै ) according to this recommendation
	 *   shall provide two alternate settings क्रम the
	 *   Communication Interface.  Alternate setting 0, and the
	 *   associated class and endpoपूर्णांक descriptors, shall be
	 *   स्थिरructed according to the rules given क्रम the
	 *   Communication Interface in section 5 of [USBNCM10].
	 *   Alternate setting 1, and the associated class and
	 *   endpoपूर्णांक descriptors, shall be स्थिरructed according to
	 *   the rules given in section 6 (USB Device Model) of this
	 *   specअगरication."
	 */
	अगर (पूर्णांकf->num_altsetting < 2)
		वापस पूर्णांकf->cur_altsetting->desc.bAlternateSetting;

	अगर (prefer_mbim) अणु
		alt = usb_altnum_to_altsetting(पूर्णांकf, CDC_NCM_COMM_ALTSETTING_MBIM);
		अगर (alt && cdc_ncm_comm_पूर्णांकf_is_mbim(alt))
			वापस CDC_NCM_COMM_ALTSETTING_MBIM;
	पूर्ण
	वापस CDC_NCM_COMM_ALTSETTING_NCM;
पूर्ण
EXPORT_SYMBOL_GPL(cdc_ncm_select_altsetting);

अटल पूर्णांक cdc_ncm_bind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	/* MBIM backwards compatible function? */
	अगर (cdc_ncm_select_altsetting(पूर्णांकf) != CDC_NCM_COMM_ALTSETTING_NCM)
		वापस -ENODEV;

	/* The NCM data altsetting is fixed, so we hard-coded it.
	 * Additionally, generic NCM devices are assumed to accept arbitrarily
	 * placed NDP.
	 */
	वापस cdc_ncm_bind_common(dev, पूर्णांकf, CDC_NCM_DATA_ALTSETTING_NCM, 0);
पूर्ण

अटल व्योम cdc_ncm_align_tail(काष्ठा sk_buff *skb, माप_प्रकार modulus, माप_प्रकार reमुख्यder, माप_प्रकार max)
अणु
	माप_प्रकार align = ALIGN(skb->len, modulus) - skb->len + reमुख्यder;

	अगर (skb->len + align > max)
		align = max - skb->len;
	अगर (align && skb_tailroom(skb) >= align)
		skb_put_zero(skb, align);
पूर्ण

/* वापस a poपूर्णांकer to a valid काष्ठा usb_cdc_ncm_ndp16 of type sign, possibly
 * allocating a new one within skb
 */
अटल काष्ठा usb_cdc_ncm_ndp16 *cdc_ncm_ndp16(काष्ठा cdc_ncm_ctx *ctx, काष्ठा sk_buff *skb, __le32 sign, माप_प्रकार reserve)
अणु
	काष्ठा usb_cdc_ncm_ndp16 *ndp16 = शून्य;
	काष्ठा usb_cdc_ncm_nth16 *nth16 = (व्योम *)skb->data;
	माप_प्रकार ndpoffset = le16_to_cpu(nth16->wNdpIndex);

	/* If NDP should be moved to the end of the NCM package, we can't follow the
	* NTH16 header as we would normally करो. NDP isn't written to the SKB yet, and
	* the wNdpIndex field in the header is actually not consistent with reality. It will be later.
	*/
	अगर (ctx->drvflags & CDC_NCM_FLAG_NDP_TO_END) अणु
		अगर (ctx->delayed_ndp16->dwSignature == sign)
			वापस ctx->delayed_ndp16;

		/* We can only push a single NDP to the end. Return
		 * शून्य to send what we've alपढ़ोy got and queue this
		 * skb क्रम later.
		 */
		अन्यथा अगर (ctx->delayed_ndp16->dwSignature)
			वापस शून्य;
	पूर्ण

	/* follow the chain of NDPs, looking क्रम a match */
	जबतक (ndpoffset) अणु
		ndp16 = (काष्ठा usb_cdc_ncm_ndp16 *)(skb->data + ndpoffset);
		अगर  (ndp16->dwSignature == sign)
			वापस ndp16;
		ndpoffset = le16_to_cpu(ndp16->wNextNdpIndex);
	पूर्ण

	/* align new NDP */
	अगर (!(ctx->drvflags & CDC_NCM_FLAG_NDP_TO_END))
		cdc_ncm_align_tail(skb, ctx->tx_ndp_modulus, 0, ctx->tx_curr_size);

	/* verअगरy that there is room क्रम the NDP and the datagram (reserve) */
	अगर ((ctx->tx_curr_size - skb->len - reserve) < ctx->max_ndp_size)
		वापस शून्य;

	/* link to it */
	अगर (ndp16)
		ndp16->wNextNdpIndex = cpu_to_le16(skb->len);
	अन्यथा
		nth16->wNdpIndex = cpu_to_le16(skb->len);

	/* push a new empty NDP */
	अगर (!(ctx->drvflags & CDC_NCM_FLAG_NDP_TO_END))
		ndp16 = skb_put_zero(skb, ctx->max_ndp_size);
	अन्यथा
		ndp16 = ctx->delayed_ndp16;

	ndp16->dwSignature = sign;
	ndp16->wLength = cpu_to_le16(माप(काष्ठा usb_cdc_ncm_ndp16) + माप(काष्ठा usb_cdc_ncm_dpe16));
	वापस ndp16;
पूर्ण

अटल काष्ठा usb_cdc_ncm_ndp32 *cdc_ncm_ndp32(काष्ठा cdc_ncm_ctx *ctx, काष्ठा sk_buff *skb, __le32 sign, माप_प्रकार reserve)
अणु
	काष्ठा usb_cdc_ncm_ndp32 *ndp32 = शून्य;
	काष्ठा usb_cdc_ncm_nth32 *nth32 = (व्योम *)skb->data;
	माप_प्रकार ndpoffset = le32_to_cpu(nth32->dwNdpIndex);

	/* If NDP should be moved to the end of the NCM package, we can't follow the
	 * NTH32 header as we would normally करो. NDP isn't written to the SKB yet, and
	 * the wNdpIndex field in the header is actually not consistent with reality. It will be later.
	 */
	अगर (ctx->drvflags & CDC_NCM_FLAG_NDP_TO_END) अणु
		अगर (ctx->delayed_ndp32->dwSignature == sign)
			वापस ctx->delayed_ndp32;

		/* We can only push a single NDP to the end. Return
		 * शून्य to send what we've alपढ़ोy got and queue this
		 * skb क्रम later.
		 */
		अन्यथा अगर (ctx->delayed_ndp32->dwSignature)
			वापस शून्य;
	पूर्ण

	/* follow the chain of NDPs, looking क्रम a match */
	जबतक (ndpoffset) अणु
		ndp32 = (काष्ठा usb_cdc_ncm_ndp32 *)(skb->data + ndpoffset);
		अगर  (ndp32->dwSignature == sign)
			वापस ndp32;
		ndpoffset = le32_to_cpu(ndp32->dwNextNdpIndex);
	पूर्ण

	/* align new NDP */
	अगर (!(ctx->drvflags & CDC_NCM_FLAG_NDP_TO_END))
		cdc_ncm_align_tail(skb, ctx->tx_ndp_modulus, 0, ctx->tx_curr_size);

	/* verअगरy that there is room क्रम the NDP and the datagram (reserve) */
	अगर ((ctx->tx_curr_size - skb->len - reserve) < ctx->max_ndp_size)
		वापस शून्य;

	/* link to it */
	अगर (ndp32)
		ndp32->dwNextNdpIndex = cpu_to_le32(skb->len);
	अन्यथा
		nth32->dwNdpIndex = cpu_to_le32(skb->len);

	/* push a new empty NDP */
	अगर (!(ctx->drvflags & CDC_NCM_FLAG_NDP_TO_END))
		ndp32 = skb_put_zero(skb, ctx->max_ndp_size);
	अन्यथा
		ndp32 = ctx->delayed_ndp32;

	ndp32->dwSignature = sign;
	ndp32->wLength = cpu_to_le16(माप(काष्ठा usb_cdc_ncm_ndp32) + माप(काष्ठा usb_cdc_ncm_dpe32));
	वापस ndp32;
पूर्ण

काष्ठा sk_buff *
cdc_ncm_fill_tx_frame(काष्ठा usbnet *dev, काष्ठा sk_buff *skb, __le32 sign)
अणु
	काष्ठा cdc_ncm_ctx *ctx = (काष्ठा cdc_ncm_ctx *)dev->data[0];
	जोड़ अणु
		काष्ठा usb_cdc_ncm_nth16 *nth16;
		काष्ठा usb_cdc_ncm_nth32 *nth32;
	पूर्ण nth;
	जोड़ अणु
		काष्ठा usb_cdc_ncm_ndp16 *ndp16;
		काष्ठा usb_cdc_ncm_ndp32 *ndp32;
	पूर्ण ndp;
	काष्ठा sk_buff *skb_out;
	u16 n = 0, index, ndplen;
	u8 पढ़ोy2send = 0;
	u32 delayed_ndp_size;
	माप_प्रकार padding_count;

	/* When our NDP माला_लो written in cdc_ncm_ndp(), then skb_out->len माला_लो updated
	 * accordingly. Otherwise, we should check here.
	 */
	अगर (ctx->drvflags & CDC_NCM_FLAG_NDP_TO_END)
		delayed_ndp_size = ctx->max_ndp_size +
			max_t(u32,
			      ctx->tx_ndp_modulus,
			      ctx->tx_modulus + ctx->tx_reमुख्यder) - 1;
	अन्यथा
		delayed_ndp_size = 0;

	/* अगर there is a reमुख्यing skb, it माला_लो priority */
	अगर (skb != शून्य) अणु
		swap(skb, ctx->tx_rem_skb);
		swap(sign, ctx->tx_rem_sign);
	पूर्ण अन्यथा अणु
		पढ़ोy2send = 1;
	पूर्ण

	/* check अगर we are resuming an OUT skb */
	skb_out = ctx->tx_curr_skb;

	/* allocate a new OUT skb */
	अगर (!skb_out) अणु
		अगर (ctx->tx_low_mem_val == 0) अणु
			ctx->tx_curr_size = ctx->tx_max;
			skb_out = alloc_skb(ctx->tx_curr_size, GFP_ATOMIC);
			/* If the memory allocation fails we will रुको दीर्घer
			 * each समय beक्रमe attempting another full size
			 * allocation again to not overload the प्रणाली
			 * further.
			 */
			अगर (skb_out == शून्य) अणु
				ctx->tx_low_mem_max_cnt = min(ctx->tx_low_mem_max_cnt + 1,
							      (अचिन्हित)CDC_NCM_LOW_MEM_MAX_CNT);
				ctx->tx_low_mem_val = ctx->tx_low_mem_max_cnt;
			पूर्ण
		पूर्ण
		अगर (skb_out == शून्य) अणु
			/* See अगर a very small allocation is possible.
			 * We will send this packet immediately and hope
			 * that there is more memory available later.
			 */
			अगर (skb)
				ctx->tx_curr_size = max(skb->len,
					(u32)USB_CDC_NCM_NTB_MIN_OUT_SIZE);
			अन्यथा
				ctx->tx_curr_size = USB_CDC_NCM_NTB_MIN_OUT_SIZE;
			skb_out = alloc_skb(ctx->tx_curr_size, GFP_ATOMIC);

			/* No allocation possible so we will पात */
			अगर (skb_out == शून्य) अणु
				अगर (skb != शून्य) अणु
					dev_kमुक्त_skb_any(skb);
					dev->net->stats.tx_dropped++;
				पूर्ण
				जाओ निकास_no_skb;
			पूर्ण
			ctx->tx_low_mem_val--;
		पूर्ण
		अगर (ctx->is_ndp16) अणु
			/* fill out the initial 16-bit NTB header */
			nth.nth16 = skb_put_zero(skb_out, माप(काष्ठा usb_cdc_ncm_nth16));
			nth.nth16->dwSignature = cpu_to_le32(USB_CDC_NCM_NTH16_SIGN);
			nth.nth16->wHeaderLength = cpu_to_le16(माप(काष्ठा usb_cdc_ncm_nth16));
			nth.nth16->wSequence = cpu_to_le16(ctx->tx_seq++);
		पूर्ण अन्यथा अणु
			/* fill out the initial 32-bit NTB header */
			nth.nth32 = skb_put_zero(skb_out, माप(काष्ठा usb_cdc_ncm_nth32));
			nth.nth32->dwSignature = cpu_to_le32(USB_CDC_NCM_NTH32_SIGN);
			nth.nth32->wHeaderLength = cpu_to_le16(माप(काष्ठा usb_cdc_ncm_nth32));
			nth.nth32->wSequence = cpu_to_le16(ctx->tx_seq++);
		पूर्ण

		/* count total number of frames in this NTB */
		ctx->tx_curr_frame_num = 0;

		/* recent payload counter क्रम this skb_out */
		ctx->tx_curr_frame_payload = 0;
	पूर्ण

	क्रम (n = ctx->tx_curr_frame_num; n < ctx->tx_max_datagrams; n++) अणु
		/* send any reमुख्यing skb first */
		अगर (skb == शून्य) अणु
			skb = ctx->tx_rem_skb;
			sign = ctx->tx_rem_sign;
			ctx->tx_rem_skb = शून्य;

			/* check क्रम end of skb */
			अगर (skb == शून्य)
				अवरोध;
		पूर्ण

		/* get the appropriate NDP क्रम this skb */
		अगर (ctx->is_ndp16)
			ndp.ndp16 = cdc_ncm_ndp16(ctx, skb_out, sign, skb->len + ctx->tx_modulus + ctx->tx_reमुख्यder);
		अन्यथा
			ndp.ndp32 = cdc_ncm_ndp32(ctx, skb_out, sign, skb->len + ctx->tx_modulus + ctx->tx_reमुख्यder);

		/* align beginning of next frame */
		cdc_ncm_align_tail(skb_out,  ctx->tx_modulus, ctx->tx_reमुख्यder, ctx->tx_curr_size);

		/* check अगर we had enough room left क्रम both NDP and frame */
		अगर ((ctx->is_ndp16 && !ndp.ndp16) || (!ctx->is_ndp16 && !ndp.ndp32) ||
		    skb_out->len + skb->len + delayed_ndp_size > ctx->tx_curr_size) अणु
			अगर (n == 0) अणु
				/* won't fit, MTU problem? */
				dev_kमुक्त_skb_any(skb);
				skb = शून्य;
				dev->net->stats.tx_dropped++;
			पूर्ण अन्यथा अणु
				/* no room क्रम skb - store क्रम later */
				अगर (ctx->tx_rem_skb != शून्य) अणु
					dev_kमुक्त_skb_any(ctx->tx_rem_skb);
					dev->net->stats.tx_dropped++;
				पूर्ण
				ctx->tx_rem_skb = skb;
				ctx->tx_rem_sign = sign;
				skb = शून्य;
				पढ़ोy2send = 1;
				ctx->tx_reason_ntb_full++;	/* count reason क्रम transmitting */
			पूर्ण
			अवरोध;
		पूर्ण

		/* calculate frame number within this NDP */
		अगर (ctx->is_ndp16) अणु
			ndplen = le16_to_cpu(ndp.ndp16->wLength);
			index = (ndplen - माप(काष्ठा usb_cdc_ncm_ndp16)) / माप(काष्ठा usb_cdc_ncm_dpe16) - 1;

			/* OK, add this skb */
			ndp.ndp16->dpe16[index].wDatagramLength = cpu_to_le16(skb->len);
			ndp.ndp16->dpe16[index].wDatagramIndex = cpu_to_le16(skb_out->len);
			ndp.ndp16->wLength = cpu_to_le16(ndplen + माप(काष्ठा usb_cdc_ncm_dpe16));
		पूर्ण अन्यथा अणु
			ndplen = le16_to_cpu(ndp.ndp32->wLength);
			index = (ndplen - माप(काष्ठा usb_cdc_ncm_ndp32)) / माप(काष्ठा usb_cdc_ncm_dpe32) - 1;

			ndp.ndp32->dpe32[index].dwDatagramLength = cpu_to_le32(skb->len);
			ndp.ndp32->dpe32[index].dwDatagramIndex = cpu_to_le32(skb_out->len);
			ndp.ndp32->wLength = cpu_to_le16(ndplen + माप(काष्ठा usb_cdc_ncm_dpe32));
		पूर्ण
		skb_put_data(skb_out, skb->data, skb->len);
		ctx->tx_curr_frame_payload += skb->len;	/* count real tx payload data */
		dev_kमुक्त_skb_any(skb);
		skb = शून्य;

		/* send now अगर this NDP is full */
		अगर (index >= CDC_NCM_DPT_DATAGRAMS_MAX) अणु
			पढ़ोy2send = 1;
			ctx->tx_reason_ndp_full++;	/* count reason क्रम transmitting */
			अवरोध;
		पूर्ण
	पूर्ण

	/* मुक्त up any dangling skb */
	अगर (skb != शून्य) अणु
		dev_kमुक्त_skb_any(skb);
		skb = शून्य;
		dev->net->stats.tx_dropped++;
	पूर्ण

	ctx->tx_curr_frame_num = n;

	अगर (n == 0) अणु
		/* रुको क्रम more frames */
		/* push variables */
		ctx->tx_curr_skb = skb_out;
		जाओ निकास_no_skb;

	पूर्ण अन्यथा अगर ((n < ctx->tx_max_datagrams) && (पढ़ोy2send == 0) && (ctx->समयr_पूर्णांकerval > 0)) अणु
		/* रुको क्रम more frames */
		/* push variables */
		ctx->tx_curr_skb = skb_out;
		/* set the pending count */
		अगर (n < CDC_NCM_RESTART_TIMER_DATAGRAM_CNT)
			ctx->tx_समयr_pending = CDC_NCM_TIMER_PENDING_CNT;
		जाओ निकास_no_skb;

	पूर्ण अन्यथा अणु
		अगर (n == ctx->tx_max_datagrams)
			ctx->tx_reason_max_datagram++;	/* count reason क्रम transmitting */
		/* frame goes out */
		/* variables will be reset at next call */
	पूर्ण

	/* If requested, put NDP at end of frame. */
	अगर (ctx->drvflags & CDC_NCM_FLAG_NDP_TO_END) अणु
		अगर (ctx->is_ndp16) अणु
			nth.nth16 = (काष्ठा usb_cdc_ncm_nth16 *)skb_out->data;
			cdc_ncm_align_tail(skb_out, ctx->tx_ndp_modulus, 0, ctx->tx_curr_size - ctx->max_ndp_size);
			nth.nth16->wNdpIndex = cpu_to_le16(skb_out->len);
			skb_put_data(skb_out, ctx->delayed_ndp16, ctx->max_ndp_size);

			/* Zero out delayed NDP - signature checking will naturally fail. */
			ndp.ndp16 = स_रखो(ctx->delayed_ndp16, 0, ctx->max_ndp_size);
		पूर्ण अन्यथा अणु
			nth.nth32 = (काष्ठा usb_cdc_ncm_nth32 *)skb_out->data;
			cdc_ncm_align_tail(skb_out, ctx->tx_ndp_modulus, 0, ctx->tx_curr_size - ctx->max_ndp_size);
			nth.nth32->dwNdpIndex = cpu_to_le32(skb_out->len);
			skb_put_data(skb_out, ctx->delayed_ndp32, ctx->max_ndp_size);

			ndp.ndp32 = स_रखो(ctx->delayed_ndp32, 0, ctx->max_ndp_size);
		पूर्ण
	पूर्ण

	/* If collected data size is less or equal ctx->min_tx_pkt
	 * bytes, we send buffers as it is. If we get more data, it
	 * would be more efficient क्रम USB HS mobile device with DMA
	 * engine to receive a full size NTB, than canceling DMA
	 * transfer and receiving a लघु packet.
	 *
	 * This optimization support is poपूर्णांकless अगर we end up sending
	 * a ZLP after full sized NTBs.
	 */
	अगर (!(dev->driver_info->flags & FLAG_SEND_ZLP) &&
	    skb_out->len > ctx->min_tx_pkt) अणु
		padding_count = ctx->tx_curr_size - skb_out->len;
		अगर (!WARN_ON(padding_count > ctx->tx_curr_size))
			skb_put_zero(skb_out, padding_count);
	पूर्ण अन्यथा अगर (skb_out->len < ctx->tx_curr_size &&
		   (skb_out->len % dev->maxpacket) == 0) अणु
		skb_put_u8(skb_out, 0);	/* क्रमce लघु packet */
	पूर्ण

	/* set final frame length */
	अगर (ctx->is_ndp16) अणु
		nth.nth16 = (काष्ठा usb_cdc_ncm_nth16 *)skb_out->data;
		nth.nth16->wBlockLength = cpu_to_le16(skb_out->len);
	पूर्ण अन्यथा अणु
		nth.nth32 = (काष्ठा usb_cdc_ncm_nth32 *)skb_out->data;
		nth.nth32->dwBlockLength = cpu_to_le32(skb_out->len);
	पूर्ण

	/* वापस skb */
	ctx->tx_curr_skb = शून्य;

	/* keep निजी stats: framing overhead and number of NTBs */
	ctx->tx_overhead += skb_out->len - ctx->tx_curr_frame_payload;
	ctx->tx_ntbs++;

	/* usbnet will count all the framing overhead by शेष.
	 * Adjust the stats so that the tx_bytes counter show real
	 * payload data instead.
	 */
	usbnet_set_skb_tx_stats(skb_out, n,
				(दीर्घ)ctx->tx_curr_frame_payload - skb_out->len);

	वापस skb_out;

निकास_no_skb:
	/* Start समयr, अगर there is a reमुख्यing non-empty skb */
	अगर (ctx->tx_curr_skb != शून्य && n > 0)
		cdc_ncm_tx_समयout_start(ctx);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(cdc_ncm_fill_tx_frame);

अटल व्योम cdc_ncm_tx_समयout_start(काष्ठा cdc_ncm_ctx *ctx)
अणु
	/* start समयr, अगर not alपढ़ोy started */
	अगर (!(hrसमयr_active(&ctx->tx_समयr) || atomic_पढ़ो(&ctx->stop)))
		hrसमयr_start(&ctx->tx_समयr,
				ctx->समयr_पूर्णांकerval,
				HRTIMER_MODE_REL);
पूर्ण

अटल क्रमागत hrसमयr_restart cdc_ncm_tx_समयr_cb(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा cdc_ncm_ctx *ctx =
			container_of(समयr, काष्ठा cdc_ncm_ctx, tx_समयr);

	अगर (!atomic_पढ़ो(&ctx->stop))
		tasklet_schedule(&ctx->bh);
	वापस HRTIMER_NORESTART;
पूर्ण

अटल व्योम cdc_ncm_txpath_bh(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा cdc_ncm_ctx *ctx = from_tasklet(ctx, t, bh);
	काष्ठा usbnet *dev = ctx->dev;

	spin_lock_bh(&ctx->mtx);
	अगर (ctx->tx_समयr_pending != 0) अणु
		ctx->tx_समयr_pending--;
		cdc_ncm_tx_समयout_start(ctx);
		spin_unlock_bh(&ctx->mtx);
	पूर्ण अन्यथा अगर (dev->net != शून्य) अणु
		ctx->tx_reason_समयout++;	/* count reason क्रम transmitting */
		spin_unlock_bh(&ctx->mtx);
		netअगर_tx_lock_bh(dev->net);
		usbnet_start_xmit(शून्य, dev->net);
		netअगर_tx_unlock_bh(dev->net);
	पूर्ण अन्यथा अणु
		spin_unlock_bh(&ctx->mtx);
	पूर्ण
पूर्ण

काष्ठा sk_buff *
cdc_ncm_tx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb, gfp_t flags)
अणु
	काष्ठा sk_buff *skb_out;
	काष्ठा cdc_ncm_ctx *ctx = (काष्ठा cdc_ncm_ctx *)dev->data[0];

	/*
	 * The Ethernet API we are using करोes not support transmitting
	 * multiple Ethernet frames in a single call. This driver will
	 * accumulate multiple Ethernet frames and send out a larger
	 * USB frame when the USB buffer is full or when a single jअगरfies
	 * समयout happens.
	 */
	अगर (ctx == शून्य)
		जाओ error;

	spin_lock_bh(&ctx->mtx);

	अगर (ctx->is_ndp16)
		skb_out = cdc_ncm_fill_tx_frame(dev, skb, cpu_to_le32(USB_CDC_NCM_NDP16_NOCRC_SIGN));
	अन्यथा
		skb_out = cdc_ncm_fill_tx_frame(dev, skb, cpu_to_le32(USB_CDC_NCM_NDP32_NOCRC_SIGN));

	spin_unlock_bh(&ctx->mtx);
	वापस skb_out;

error:
	अगर (skb != शून्य)
		dev_kमुक्त_skb_any(skb);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(cdc_ncm_tx_fixup);

/* verअगरy NTB header and वापस offset of first NDP, or negative error */
पूर्णांक cdc_ncm_rx_verअगरy_nth16(काष्ठा cdc_ncm_ctx *ctx, काष्ठा sk_buff *skb_in)
अणु
	काष्ठा usbnet *dev = netdev_priv(skb_in->dev);
	काष्ठा usb_cdc_ncm_nth16 *nth16;
	पूर्णांक len;
	पूर्णांक ret = -EINVAL;

	अगर (ctx == शून्य)
		जाओ error;

	अगर (skb_in->len < (माप(काष्ठा usb_cdc_ncm_nth16) +
					माप(काष्ठा usb_cdc_ncm_ndp16))) अणु
		netअगर_dbg(dev, rx_err, dev->net, "frame too short\n");
		जाओ error;
	पूर्ण

	nth16 = (काष्ठा usb_cdc_ncm_nth16 *)skb_in->data;

	अगर (nth16->dwSignature != cpu_to_le32(USB_CDC_NCM_NTH16_SIGN)) अणु
		netअगर_dbg(dev, rx_err, dev->net,
			  "invalid NTH16 signature <%#010x>\n",
			  le32_to_cpu(nth16->dwSignature));
		जाओ error;
	पूर्ण

	len = le16_to_cpu(nth16->wBlockLength);
	अगर (len > ctx->rx_max) अणु
		netअगर_dbg(dev, rx_err, dev->net,
			  "unsupported NTB block length %u/%u\n", len,
			  ctx->rx_max);
		जाओ error;
	पूर्ण

	अगर ((ctx->rx_seq + 1) != le16_to_cpu(nth16->wSequence) &&
	    (ctx->rx_seq || le16_to_cpu(nth16->wSequence)) &&
	    !((ctx->rx_seq == 0xffff) && !le16_to_cpu(nth16->wSequence))) अणु
		netअगर_dbg(dev, rx_err, dev->net,
			  "sequence number glitch prev=%d curr=%d\n",
			  ctx->rx_seq, le16_to_cpu(nth16->wSequence));
	पूर्ण
	ctx->rx_seq = le16_to_cpu(nth16->wSequence);

	ret = le16_to_cpu(nth16->wNdpIndex);
error:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(cdc_ncm_rx_verअगरy_nth16);

पूर्णांक cdc_ncm_rx_verअगरy_nth32(काष्ठा cdc_ncm_ctx *ctx, काष्ठा sk_buff *skb_in)
अणु
	काष्ठा usbnet *dev = netdev_priv(skb_in->dev);
	काष्ठा usb_cdc_ncm_nth32 *nth32;
	पूर्णांक len;
	पूर्णांक ret = -EINVAL;

	अगर (ctx == शून्य)
		जाओ error;

	अगर (skb_in->len < (माप(काष्ठा usb_cdc_ncm_nth32) +
					माप(काष्ठा usb_cdc_ncm_ndp32))) अणु
		netअगर_dbg(dev, rx_err, dev->net, "frame too short\n");
		जाओ error;
	पूर्ण

	nth32 = (काष्ठा usb_cdc_ncm_nth32 *)skb_in->data;

	अगर (nth32->dwSignature != cpu_to_le32(USB_CDC_NCM_NTH32_SIGN)) अणु
		netअगर_dbg(dev, rx_err, dev->net,
			  "invalid NTH32 signature <%#010x>\n",
			  le32_to_cpu(nth32->dwSignature));
		जाओ error;
	पूर्ण

	len = le32_to_cpu(nth32->dwBlockLength);
	अगर (len > ctx->rx_max) अणु
		netअगर_dbg(dev, rx_err, dev->net,
			  "unsupported NTB block length %u/%u\n", len,
			  ctx->rx_max);
		जाओ error;
	पूर्ण

	अगर ((ctx->rx_seq + 1) != le16_to_cpu(nth32->wSequence) &&
	    (ctx->rx_seq || le16_to_cpu(nth32->wSequence)) &&
	    !((ctx->rx_seq == 0xffff) && !le16_to_cpu(nth32->wSequence))) अणु
		netअगर_dbg(dev, rx_err, dev->net,
			  "sequence number glitch prev=%d curr=%d\n",
			  ctx->rx_seq, le16_to_cpu(nth32->wSequence));
	पूर्ण
	ctx->rx_seq = le16_to_cpu(nth32->wSequence);

	ret = le32_to_cpu(nth32->dwNdpIndex);
error:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(cdc_ncm_rx_verअगरy_nth32);

/* verअगरy NDP header and वापस number of datagrams, or negative error */
पूर्णांक cdc_ncm_rx_verअगरy_ndp16(काष्ठा sk_buff *skb_in, पूर्णांक ndpoffset)
अणु
	काष्ठा usbnet *dev = netdev_priv(skb_in->dev);
	काष्ठा usb_cdc_ncm_ndp16 *ndp16;
	पूर्णांक ret = -EINVAL;

	अगर ((ndpoffset + माप(काष्ठा usb_cdc_ncm_ndp16)) > skb_in->len) अणु
		netअगर_dbg(dev, rx_err, dev->net, "invalid NDP offset  <%u>\n",
			  ndpoffset);
		जाओ error;
	पूर्ण
	ndp16 = (काष्ठा usb_cdc_ncm_ndp16 *)(skb_in->data + ndpoffset);

	अगर (le16_to_cpu(ndp16->wLength) < USB_CDC_NCM_NDP16_LENGTH_MIN) अणु
		netअगर_dbg(dev, rx_err, dev->net, "invalid DPT16 length <%u>\n",
			  le16_to_cpu(ndp16->wLength));
		जाओ error;
	पूर्ण

	ret = ((le16_to_cpu(ndp16->wLength) -
					माप(काष्ठा usb_cdc_ncm_ndp16)) /
					माप(काष्ठा usb_cdc_ncm_dpe16));
	ret--; /* we process NDP entries except क्रम the last one */

	अगर ((माप(काष्ठा usb_cdc_ncm_ndp16) +
	     ret * (माप(काष्ठा usb_cdc_ncm_dpe16))) > skb_in->len) अणु
		netअगर_dbg(dev, rx_err, dev->net, "Invalid nframes = %d\n", ret);
		ret = -EINVAL;
	पूर्ण

error:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(cdc_ncm_rx_verअगरy_ndp16);

/* verअगरy NDP header and वापस number of datagrams, or negative error */
पूर्णांक cdc_ncm_rx_verअगरy_ndp32(काष्ठा sk_buff *skb_in, पूर्णांक ndpoffset)
अणु
	काष्ठा usbnet *dev = netdev_priv(skb_in->dev);
	काष्ठा usb_cdc_ncm_ndp32 *ndp32;
	पूर्णांक ret = -EINVAL;

	अगर ((ndpoffset + माप(काष्ठा usb_cdc_ncm_ndp32)) > skb_in->len) अणु
		netअगर_dbg(dev, rx_err, dev->net, "invalid NDP offset  <%u>\n",
			  ndpoffset);
		जाओ error;
	पूर्ण
	ndp32 = (काष्ठा usb_cdc_ncm_ndp32 *)(skb_in->data + ndpoffset);

	अगर (le16_to_cpu(ndp32->wLength) < USB_CDC_NCM_NDP32_LENGTH_MIN) अणु
		netअगर_dbg(dev, rx_err, dev->net, "invalid DPT32 length <%u>\n",
			  le16_to_cpu(ndp32->wLength));
		जाओ error;
	पूर्ण

	ret = ((le16_to_cpu(ndp32->wLength) -
					माप(काष्ठा usb_cdc_ncm_ndp32)) /
					माप(काष्ठा usb_cdc_ncm_dpe32));
	ret--; /* we process NDP entries except क्रम the last one */

	अगर ((माप(काष्ठा usb_cdc_ncm_ndp32) +
	     ret * (माप(काष्ठा usb_cdc_ncm_dpe32))) > skb_in->len) अणु
		netअगर_dbg(dev, rx_err, dev->net, "Invalid nframes = %d\n", ret);
		ret = -EINVAL;
	पूर्ण

error:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(cdc_ncm_rx_verअगरy_ndp32);

पूर्णांक cdc_ncm_rx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb_in)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा cdc_ncm_ctx *ctx = (काष्ठा cdc_ncm_ctx *)dev->data[0];
	पूर्णांक len;
	पूर्णांक nframes;
	पूर्णांक x;
	पूर्णांक offset;
	जोड़ अणु
		काष्ठा usb_cdc_ncm_ndp16 *ndp16;
		काष्ठा usb_cdc_ncm_ndp32 *ndp32;
	पूर्ण ndp;
	जोड़ अणु
		काष्ठा usb_cdc_ncm_dpe16 *dpe16;
		काष्ठा usb_cdc_ncm_dpe32 *dpe32;
	पूर्ण dpe;

	पूर्णांक ndpoffset;
	पूर्णांक loopcount = 50; /* arbitrary max preventing infinite loop */
	u32 payload = 0;

	अगर (ctx->is_ndp16)
		ndpoffset = cdc_ncm_rx_verअगरy_nth16(ctx, skb_in);
	अन्यथा
		ndpoffset = cdc_ncm_rx_verअगरy_nth32(ctx, skb_in);

	अगर (ndpoffset < 0)
		जाओ error;

next_ndp:
	अगर (ctx->is_ndp16) अणु
		nframes = cdc_ncm_rx_verअगरy_ndp16(skb_in, ndpoffset);
		अगर (nframes < 0)
			जाओ error;

		ndp.ndp16 = (काष्ठा usb_cdc_ncm_ndp16 *)(skb_in->data + ndpoffset);

		अगर (ndp.ndp16->dwSignature != cpu_to_le32(USB_CDC_NCM_NDP16_NOCRC_SIGN)) अणु
			netअगर_dbg(dev, rx_err, dev->net,
				  "invalid DPT16 signature <%#010x>\n",
				  le32_to_cpu(ndp.ndp16->dwSignature));
			जाओ err_ndp;
		पूर्ण
		dpe.dpe16 = ndp.ndp16->dpe16;
	पूर्ण अन्यथा अणु
		nframes = cdc_ncm_rx_verअगरy_ndp32(skb_in, ndpoffset);
		अगर (nframes < 0)
			जाओ error;

		ndp.ndp32 = (काष्ठा usb_cdc_ncm_ndp32 *)(skb_in->data + ndpoffset);

		अगर (ndp.ndp32->dwSignature != cpu_to_le32(USB_CDC_NCM_NDP32_NOCRC_SIGN)) अणु
			netअगर_dbg(dev, rx_err, dev->net,
				  "invalid DPT32 signature <%#010x>\n",
				  le32_to_cpu(ndp.ndp32->dwSignature));
			जाओ err_ndp;
		पूर्ण
		dpe.dpe32 = ndp.ndp32->dpe32;
	पूर्ण

	क्रम (x = 0; x < nframes; x++) अणु
		अगर (ctx->is_ndp16) अणु
			offset = le16_to_cpu(dpe.dpe16->wDatagramIndex);
			len = le16_to_cpu(dpe.dpe16->wDatagramLength);
		पूर्ण अन्यथा अणु
			offset = le32_to_cpu(dpe.dpe32->dwDatagramIndex);
			len = le32_to_cpu(dpe.dpe32->dwDatagramLength);
		पूर्ण

		/*
		 * CDC NCM ch. 3.7
		 * All entries after first शून्य entry are to be ignored
		 */
		अगर ((offset == 0) || (len == 0)) अणु
			अगर (!x)
				जाओ err_ndp; /* empty NTB */
			अवरोध;
		पूर्ण

		/* sanity checking */
		अगर (((offset + len) > skb_in->len) ||
				(len > ctx->rx_max) || (len < ETH_HLEN)) अणु
			netअगर_dbg(dev, rx_err, dev->net,
				  "invalid frame detected (ignored) offset[%u]=%u, length=%u, skb=%p\n",
				  x, offset, len, skb_in);
			अगर (!x)
				जाओ err_ndp;
			अवरोध;

		पूर्ण अन्यथा अणु
			/* create a fresh copy to reduce truesize */
			skb = netdev_alloc_skb_ip_align(dev->net,  len);
			अगर (!skb)
				जाओ error;
			skb_put_data(skb, skb_in->data + offset, len);
			usbnet_skb_वापस(dev, skb);
			payload += len;	/* count payload bytes in this NTB */
		पूर्ण

		अगर (ctx->is_ndp16)
			dpe.dpe16++;
		अन्यथा
			dpe.dpe32++;
	पूर्ण
err_ndp:
	/* are there more NDPs to process? */
	अगर (ctx->is_ndp16)
		ndpoffset = le16_to_cpu(ndp.ndp16->wNextNdpIndex);
	अन्यथा
		ndpoffset = le32_to_cpu(ndp.ndp32->dwNextNdpIndex);

	अगर (ndpoffset && loopcount--)
		जाओ next_ndp;

	/* update stats */
	ctx->rx_overhead += skb_in->len - payload;
	ctx->rx_ntbs++;

	वापस 1;
error:
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cdc_ncm_rx_fixup);

अटल व्योम
cdc_ncm_speed_change(काष्ठा usbnet *dev,
		     काष्ठा usb_cdc_speed_change *data)
अणु
	/* RTL8156 shipped beक्रमe 2021 sends notअगरication about every 32ms. */
	dev->rx_speed = le32_to_cpu(data->DLBitRRate);
	dev->tx_speed = le32_to_cpu(data->ULBitRate);
पूर्ण

अटल व्योम cdc_ncm_status(काष्ठा usbnet *dev, काष्ठा urb *urb)
अणु
	काष्ठा usb_cdc_notअगरication *event;

	अगर (urb->actual_length < माप(*event))
		वापस;

	/* test क्रम split data in 8-byte chunks */
	अगर (test_and_clear_bit(EVENT_STS_SPLIT, &dev->flags)) अणु
		cdc_ncm_speed_change(dev,
		      (काष्ठा usb_cdc_speed_change *)urb->transfer_buffer);
		वापस;
	पूर्ण

	event = urb->transfer_buffer;

	चयन (event->bNotअगरicationType) अणु
	हाल USB_CDC_NOTIFY_NETWORK_CONNECTION:
		/*
		 * According to the CDC NCM specअगरication ch.7.1
		 * USB_CDC_NOTIFY_NETWORK_CONNECTION notअगरication shall be
		 * sent by device after USB_CDC_NOTIFY_SPEED_CHANGE.
		 */
		/* RTL8156 shipped beक्रमe 2021 sends notअगरication about
		 * every 32ms. Don't क्रमward notअगरication अगर state is same.
		 */
		अगर (netअगर_carrier_ok(dev->net) != !!event->wValue)
			usbnet_link_change(dev, !!event->wValue, 0);
		अवरोध;

	हाल USB_CDC_NOTIFY_SPEED_CHANGE:
		अगर (urb->actual_length < (माप(*event) +
					माप(काष्ठा usb_cdc_speed_change)))
			set_bit(EVENT_STS_SPLIT, &dev->flags);
		अन्यथा
			cdc_ncm_speed_change(dev,
					     (काष्ठा usb_cdc_speed_change *)&event[1]);
		अवरोध;

	शेष:
		dev_dbg(&dev->udev->dev,
			"NCM: unexpected notification 0x%02x!\n",
			event->bNotअगरicationType);
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा driver_info cdc_ncm_info = अणु
	.description = "CDC NCM",
	.flags = FLAG_POINTTOPOINT | FLAG_NO_SETINT | FLAG_MULTI_PACKET
			| FLAG_LINK_INTR | FLAG_ETHER,
	.bind = cdc_ncm_bind,
	.unbind = cdc_ncm_unbind,
	.manage_घातer = usbnet_manage_घातer,
	.status = cdc_ncm_status,
	.rx_fixup = cdc_ncm_rx_fixup,
	.tx_fixup = cdc_ncm_tx_fixup,
	.set_rx_mode = usbnet_cdc_update_filter,
पूर्ण;

/* Same as cdc_ncm_info, but with FLAG_WWAN */
अटल स्थिर काष्ठा driver_info wwan_info = अणु
	.description = "Mobile Broadband Network Device",
	.flags = FLAG_POINTTOPOINT | FLAG_NO_SETINT | FLAG_MULTI_PACKET
			| FLAG_LINK_INTR | FLAG_WWAN,
	.bind = cdc_ncm_bind,
	.unbind = cdc_ncm_unbind,
	.manage_घातer = usbnet_manage_घातer,
	.status = cdc_ncm_status,
	.rx_fixup = cdc_ncm_rx_fixup,
	.tx_fixup = cdc_ncm_tx_fixup,
	.set_rx_mode = usbnet_cdc_update_filter,
पूर्ण;

/* Same as wwan_info, but with FLAG_NOARP  */
अटल स्थिर काष्ठा driver_info wwan_noarp_info = अणु
	.description = "Mobile Broadband Network Device (NO ARP)",
	.flags = FLAG_POINTTOPOINT | FLAG_NO_SETINT | FLAG_MULTI_PACKET
			| FLAG_LINK_INTR | FLAG_WWAN | FLAG_NOARP,
	.bind = cdc_ncm_bind,
	.unbind = cdc_ncm_unbind,
	.manage_घातer = usbnet_manage_घातer,
	.status = cdc_ncm_status,
	.rx_fixup = cdc_ncm_rx_fixup,
	.tx_fixup = cdc_ncm_tx_fixup,
	.set_rx_mode = usbnet_cdc_update_filter,
पूर्ण;

अटल स्थिर काष्ठा usb_device_id cdc_devs[] = अणु
	/* Ericsson MBM devices like F5521gw */
	अणु .match_flags = USB_DEVICE_ID_MATCH_INT_INFO
		| USB_DEVICE_ID_MATCH_VENDOR,
	  .idVenकरोr = 0x0bdb,
	  .bInterfaceClass = USB_CLASS_COMM,
	  .bInterfaceSubClass = USB_CDC_SUBCLASS_NCM,
	  .bInterfaceProtocol = USB_CDC_PROTO_NONE,
	  .driver_info = (अचिन्हित दीर्घ) &wwan_info,
	पूर्ण,

	/* Telit LE910 V2 */
	अणु USB_DEVICE_AND_INTERFACE_INFO(0x1bc7, 0x0036,
		USB_CLASS_COMM,
		USB_CDC_SUBCLASS_NCM, USB_CDC_PROTO_NONE),
	  .driver_info = (अचिन्हित दीर्घ)&wwan_noarp_info,
	पूर्ण,

	/* DW5812 LTE Verizon Mobile Broadband Card
	 * Unlike DW5550 this device requires FLAG_NOARP
	 */
	अणु USB_DEVICE_AND_INTERFACE_INFO(0x413c, 0x81bb,
		USB_CLASS_COMM,
		USB_CDC_SUBCLASS_NCM, USB_CDC_PROTO_NONE),
	  .driver_info = (अचिन्हित दीर्घ)&wwan_noarp_info,
	पूर्ण,

	/* DW5813 LTE AT&T Mobile Broadband Card
	 * Unlike DW5550 this device requires FLAG_NOARP
	 */
	अणु USB_DEVICE_AND_INTERFACE_INFO(0x413c, 0x81bc,
		USB_CLASS_COMM,
		USB_CDC_SUBCLASS_NCM, USB_CDC_PROTO_NONE),
	  .driver_info = (अचिन्हित दीर्घ)&wwan_noarp_info,
	पूर्ण,

	/* Dell bअक्रमed MBM devices like DW5550 */
	अणु .match_flags = USB_DEVICE_ID_MATCH_INT_INFO
		| USB_DEVICE_ID_MATCH_VENDOR,
	  .idVenकरोr = 0x413c,
	  .bInterfaceClass = USB_CLASS_COMM,
	  .bInterfaceSubClass = USB_CDC_SUBCLASS_NCM,
	  .bInterfaceProtocol = USB_CDC_PROTO_NONE,
	  .driver_info = (अचिन्हित दीर्घ) &wwan_info,
	पूर्ण,

	/* Toshiba bअक्रमed MBM devices */
	अणु .match_flags = USB_DEVICE_ID_MATCH_INT_INFO
		| USB_DEVICE_ID_MATCH_VENDOR,
	  .idVenकरोr = 0x0930,
	  .bInterfaceClass = USB_CLASS_COMM,
	  .bInterfaceSubClass = USB_CDC_SUBCLASS_NCM,
	  .bInterfaceProtocol = USB_CDC_PROTO_NONE,
	  .driver_info = (अचिन्हित दीर्घ) &wwan_info,
	पूर्ण,

	/* tag Huawei devices as wwan */
	अणु USB_VENDOR_AND_INTERFACE_INFO(0x12d1,
					USB_CLASS_COMM,
					USB_CDC_SUBCLASS_NCM,
					USB_CDC_PROTO_NONE),
	  .driver_info = (अचिन्हित दीर्घ)&wwan_info,
	पूर्ण,

	/* Infineon(now Intel) HSPA Modem platक्रमm */
	अणु USB_DEVICE_AND_INTERFACE_INFO(0x1519, 0x0443,
		USB_CLASS_COMM,
		USB_CDC_SUBCLASS_NCM, USB_CDC_PROTO_NONE),
	  .driver_info = (अचिन्हित दीर्घ)&wwan_noarp_info,
	पूर्ण,

	/* u-blox TOBY-L4 */
	अणु USB_DEVICE_AND_INTERFACE_INFO(0x1546, 0x1010,
		USB_CLASS_COMM,
		USB_CDC_SUBCLASS_NCM, USB_CDC_PROTO_NONE),
	  .driver_info = (अचिन्हित दीर्घ)&wwan_info,
	पूर्ण,

	/* Generic CDC-NCM devices */
	अणु USB_INTERFACE_INFO(USB_CLASS_COMM,
		USB_CDC_SUBCLASS_NCM, USB_CDC_PROTO_NONE),
		.driver_info = (अचिन्हित दीर्घ)&cdc_ncm_info,
	पूर्ण,
	अणु
	पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, cdc_devs);

अटल काष्ठा usb_driver cdc_ncm_driver = अणु
	.name = "cdc_ncm",
	.id_table = cdc_devs,
	.probe = usbnet_probe,
	.disconnect = usbnet_disconnect,
	.suspend = usbnet_suspend,
	.resume = usbnet_resume,
	.reset_resume =	usbnet_resume,
	.supports_स्वतःsuspend = 1,
	.disable_hub_initiated_lpm = 1,
पूर्ण;

module_usb_driver(cdc_ncm_driver);

MODULE_AUTHOR("Hans Petter Selasky");
MODULE_DESCRIPTION("USB CDC NCM host driver");
MODULE_LICENSE("Dual BSD/GPL");
