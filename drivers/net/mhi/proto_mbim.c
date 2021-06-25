<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* MHI Network driver - Network over MHI bus
 *
 * Copyright (C) 2021 Linaro Ltd <loic.poulain@linaro.org>
 *
 * This driver copy some code from cdc_ncm, which is:
 * Copyright (C) ST-Ericsson 2010-2012
 * and cdc_mbim, which is:
 * Copyright (c) 2012  Smith Micro Software, Inc.
 * Copyright (c) 2012  Bjथचrn Mork <bjorn@mork.no>
 *
 */

#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/ip.h>
#समावेश <linux/mii.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/cdc.h>
#समावेश <linux/usb/usbnet.h>
#समावेश <linux/usb/cdc_ncm.h>

#समावेश "mhi.h"

#घोषणा MBIM_NDP16_SIGN_MASK 0x00ffffff

/* Usual WWAN MTU */
#घोषणा MHI_MBIM_DEFAULT_MTU 1500

/* 3500 allows to optimize skb allocation, the skbs will basically fit in
 * one 4K page. Large MBIM packets will simply be split over several MHI
 * transfers and chained by the MHI net layer (zerocopy).
 */
#घोषणा MHI_MBIM_DEFAULT_MRU 3500

काष्ठा mbim_context अणु
	u16 rx_seq;
	u16 tx_seq;
पूर्ण;

अटल व्योम __mbim_length_errors_inc(काष्ठा mhi_net_dev *dev)
अणु
	u64_stats_update_begin(&dev->stats.rx_syncp);
	u64_stats_inc(&dev->stats.rx_length_errors);
	u64_stats_update_end(&dev->stats.rx_syncp);
पूर्ण

अटल व्योम __mbim_errors_inc(काष्ठा mhi_net_dev *dev)
अणु
	u64_stats_update_begin(&dev->stats.rx_syncp);
	u64_stats_inc(&dev->stats.rx_errors);
	u64_stats_update_end(&dev->stats.rx_syncp);
पूर्ण

अटल पूर्णांक mbim_rx_verअगरy_nth16(काष्ठा sk_buff *skb)
अणु
	काष्ठा mhi_net_dev *dev = netdev_priv(skb->dev);
	काष्ठा mbim_context *ctx = dev->proto_data;
	काष्ठा usb_cdc_ncm_nth16 *nth16;
	पूर्णांक len;

	अगर (skb->len < माप(काष्ठा usb_cdc_ncm_nth16) +
			माप(काष्ठा usb_cdc_ncm_ndp16)) अणु
		netअगर_dbg(dev, rx_err, dev->ndev, "frame too short\n");
		__mbim_length_errors_inc(dev);
		वापस -EINVAL;
	पूर्ण

	nth16 = (काष्ठा usb_cdc_ncm_nth16 *)skb->data;

	अगर (nth16->dwSignature != cpu_to_le32(USB_CDC_NCM_NTH16_SIGN)) अणु
		netअगर_dbg(dev, rx_err, dev->ndev,
			  "invalid NTH16 signature <%#010x>\n",
			  le32_to_cpu(nth16->dwSignature));
		__mbim_errors_inc(dev);
		वापस -EINVAL;
	पूर्ण

	/* No limit on the block length, except the size of the data pkt */
	len = le16_to_cpu(nth16->wBlockLength);
	अगर (len > skb->len) अणु
		netअगर_dbg(dev, rx_err, dev->ndev,
			  "NTB does not fit into the skb %u/%u\n", len,
			  skb->len);
		__mbim_length_errors_inc(dev);
		वापस -EINVAL;
	पूर्ण

	अगर (ctx->rx_seq + 1 != le16_to_cpu(nth16->wSequence) &&
	    (ctx->rx_seq || le16_to_cpu(nth16->wSequence)) &&
	    !(ctx->rx_seq == 0xffff && !le16_to_cpu(nth16->wSequence))) अणु
		netअगर_dbg(dev, rx_err, dev->ndev,
			  "sequence number glitch prev=%d curr=%d\n",
			  ctx->rx_seq, le16_to_cpu(nth16->wSequence));
	पूर्ण
	ctx->rx_seq = le16_to_cpu(nth16->wSequence);

	वापस le16_to_cpu(nth16->wNdpIndex);
पूर्ण

अटल पूर्णांक mbim_rx_verअगरy_ndp16(काष्ठा sk_buff *skb, काष्ठा usb_cdc_ncm_ndp16 *ndp16)
अणु
	काष्ठा mhi_net_dev *dev = netdev_priv(skb->dev);
	पूर्णांक ret;

	अगर (le16_to_cpu(ndp16->wLength) < USB_CDC_NCM_NDP16_LENGTH_MIN) अणु
		netअगर_dbg(dev, rx_err, dev->ndev, "invalid DPT16 length <%u>\n",
			  le16_to_cpu(ndp16->wLength));
		वापस -EINVAL;
	पूर्ण

	ret = ((le16_to_cpu(ndp16->wLength) - माप(काष्ठा usb_cdc_ncm_ndp16))
			/ माप(काष्ठा usb_cdc_ncm_dpe16));
	ret--; /* Last entry is always a शून्य terminator */

	अगर (माप(काष्ठा usb_cdc_ncm_ndp16) +
	     ret * माप(काष्ठा usb_cdc_ncm_dpe16) > skb->len) अणु
		netअगर_dbg(dev, rx_err, dev->ndev,
			  "Invalid nframes = %d\n", ret);
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम mbim_rx(काष्ठा mhi_net_dev *mhi_netdev, काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *ndev = mhi_netdev->ndev;
	पूर्णांक ndpoffset;

	/* Check NTB header and retrieve first NDP offset */
	ndpoffset = mbim_rx_verअगरy_nth16(skb);
	अगर (ndpoffset < 0) अणु
		net_err_ratelimited("%s: Incorrect NTB header\n", ndev->name);
		जाओ error;
	पूर्ण

	/* Process each NDP */
	जबतक (1) अणु
		काष्ठा usb_cdc_ncm_ndp16 ndp16;
		काष्ठा usb_cdc_ncm_dpe16 dpe16;
		पूर्णांक nframes, n, dpeoffset;

		अगर (skb_copy_bits(skb, ndpoffset, &ndp16, माप(ndp16))) अणु
			net_err_ratelimited("%s: Incorrect NDP offset (%u)\n",
					    ndev->name, ndpoffset);
			__mbim_length_errors_inc(mhi_netdev);
			जाओ error;
		पूर्ण

		/* Check NDP header and retrieve number of datagrams */
		nframes = mbim_rx_verअगरy_ndp16(skb, &ndp16);
		अगर (nframes < 0) अणु
			net_err_ratelimited("%s: Incorrect NDP16\n", ndev->name);
			__mbim_length_errors_inc(mhi_netdev);
			जाओ error;
		पूर्ण

		 /* Only IP data type supported, no DSS in MHI context */
		अगर ((ndp16.dwSignature & cpu_to_le32(MBIM_NDP16_SIGN_MASK))
				!= cpu_to_le32(USB_CDC_MBIM_NDP16_IPS_SIGN)) अणु
			net_err_ratelimited("%s: Unsupported NDP type\n", ndev->name);
			__mbim_errors_inc(mhi_netdev);
			जाओ next_ndp;
		पूर्ण

		/* Only primary IP session 0 (0x00) supported क्रम now */
		अगर (ndp16.dwSignature & ~cpu_to_le32(MBIM_NDP16_SIGN_MASK)) अणु
			net_err_ratelimited("%s: bad packet session\n", ndev->name);
			__mbim_errors_inc(mhi_netdev);
			जाओ next_ndp;
		पूर्ण

		/* de-aggregate and deliver IP packets */
		dpeoffset = ndpoffset + माप(काष्ठा usb_cdc_ncm_ndp16);
		क्रम (n = 0; n < nframes; n++, dpeoffset += माप(dpe16)) अणु
			u16 dgram_offset, dgram_len;
			काष्ठा sk_buff *skbn;

			अगर (skb_copy_bits(skb, dpeoffset, &dpe16, माप(dpe16)))
				अवरोध;

			dgram_offset = le16_to_cpu(dpe16.wDatagramIndex);
			dgram_len = le16_to_cpu(dpe16.wDatagramLength);

			अगर (!dgram_offset || !dgram_len)
				अवरोध; /* null terminator */

			skbn = netdev_alloc_skb(ndev, dgram_len);
			अगर (!skbn)
				जारी;

			skb_put(skbn, dgram_len);
			skb_copy_bits(skb, dgram_offset, skbn->data, dgram_len);

			चयन (skbn->data[0] & 0xf0) अणु
			हाल 0x40:
				skbn->protocol = htons(ETH_P_IP);
				अवरोध;
			हाल 0x60:
				skbn->protocol = htons(ETH_P_IPV6);
				अवरोध;
			शेष:
				net_err_ratelimited("%s: unknown protocol\n",
						    ndev->name);
				__mbim_errors_inc(mhi_netdev);
				dev_kमुक्त_skb_any(skbn);
				जारी;
			पूर्ण

			netअगर_rx(skbn);
		पूर्ण
next_ndp:
		/* Other NDP to process? */
		ndpoffset = (पूर्णांक)le16_to_cpu(ndp16.wNextNdpIndex);
		अगर (!ndpoffset)
			अवरोध;
	पूर्ण

	/* मुक्त skb */
	dev_consume_skb_any(skb);
	वापस;
error:
	dev_kमुक्त_skb_any(skb);
पूर्ण

काष्ठा mbim_tx_hdr अणु
	काष्ठा usb_cdc_ncm_nth16 nth16;
	काष्ठा usb_cdc_ncm_ndp16 ndp16;
	काष्ठा usb_cdc_ncm_dpe16 dpe16[2];
पूर्ण __packed;

अटल काष्ठा sk_buff *mbim_tx_fixup(काष्ठा mhi_net_dev *mhi_netdev,
				     काष्ठा sk_buff *skb)
अणु
	काष्ठा mbim_context *ctx = mhi_netdev->proto_data;
	अचिन्हित पूर्णांक dgram_size = skb->len;
	काष्ठा usb_cdc_ncm_nth16 *nth16;
	काष्ठा usb_cdc_ncm_ndp16 *ndp16;
	काष्ठा mbim_tx_hdr *mbim_hdr;

	/* For now, this is a partial implementation of CDC MBIM, only one NDP
	 * is sent, containing the IP packet (no aggregation).
	 */

	/* Ensure we have enough headroom क्रम crafting MBIM header */
	अगर (skb_cow_head(skb, माप(काष्ठा mbim_tx_hdr))) अणु
		dev_kमुक्त_skb_any(skb);
		वापस शून्य;
	पूर्ण

	mbim_hdr = skb_push(skb, माप(काष्ठा mbim_tx_hdr));

	/* Fill NTB header */
	nth16 = &mbim_hdr->nth16;
	nth16->dwSignature = cpu_to_le32(USB_CDC_NCM_NTH16_SIGN);
	nth16->wHeaderLength = cpu_to_le16(माप(काष्ठा usb_cdc_ncm_nth16));
	nth16->wSequence = cpu_to_le16(ctx->tx_seq++);
	nth16->wBlockLength = cpu_to_le16(skb->len);
	nth16->wNdpIndex = cpu_to_le16(माप(काष्ठा usb_cdc_ncm_nth16));

	/* Fill the unique NDP */
	ndp16 = &mbim_hdr->ndp16;
	ndp16->dwSignature = cpu_to_le32(USB_CDC_MBIM_NDP16_IPS_SIGN);
	ndp16->wLength = cpu_to_le16(माप(काष्ठा usb_cdc_ncm_ndp16)
					+ माप(काष्ठा usb_cdc_ncm_dpe16) * 2);
	ndp16->wNextNdpIndex = 0;

	/* Datagram follows the mbim header */
	ndp16->dpe16[0].wDatagramIndex = cpu_to_le16(माप(काष्ठा mbim_tx_hdr));
	ndp16->dpe16[0].wDatagramLength = cpu_to_le16(dgram_size);

	/* null termination */
	ndp16->dpe16[1].wDatagramIndex = 0;
	ndp16->dpe16[1].wDatagramLength = 0;

	वापस skb;
पूर्ण

अटल पूर्णांक mbim_init(काष्ठा mhi_net_dev *mhi_netdev)
अणु
	काष्ठा net_device *ndev = mhi_netdev->ndev;

	mhi_netdev->proto_data = devm_kzalloc(&ndev->dev,
					      माप(काष्ठा mbim_context),
					      GFP_KERNEL);
	अगर (!mhi_netdev->proto_data)
		वापस -ENOMEM;

	ndev->needed_headroom = माप(काष्ठा mbim_tx_hdr);
	ndev->mtu = MHI_MBIM_DEFAULT_MTU;
	mhi_netdev->mru = MHI_MBIM_DEFAULT_MRU;

	वापस 0;
पूर्ण

स्थिर काष्ठा mhi_net_proto proto_mbim = अणु
	.init = mbim_init,
	.rx = mbim_rx,
	.tx_fixup = mbim_tx_fixup,
पूर्ण;
