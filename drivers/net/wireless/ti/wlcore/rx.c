<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl1271
 *
 * Copyright (C) 2009 Nokia Corporation
 *
 * Contact: Luciano Coelho <luciano.coelho@nokia.com>
 */

#समावेश <linux/gfp.h>
#समावेश <linux/sched.h>

#समावेश "wlcore.h"
#समावेश "debug.h"
#समावेश "acx.h"
#समावेश "rx.h"
#समावेश "tx.h"
#समावेश "io.h"
#समावेश "hw_ops.h"

/*
 * TODO: this is here just क्रम now, it must be हटाओd when the data
 * operations are in place.
 */
#समावेश "../wl12xx/reg.h"

अटल u32 wlcore_rx_get_buf_size(काष्ठा wl1271 *wl,
				  u32 rx_pkt_desc)
अणु
	अगर (wl->quirks & WLCORE_QUIRK_RX_BLOCKSIZE_ALIGN)
		वापस (rx_pkt_desc & ALIGNED_RX_BUF_SIZE_MASK) >>
		       ALIGNED_RX_BUF_SIZE_SHIFT;

	वापस (rx_pkt_desc & RX_BUF_SIZE_MASK) >> RX_BUF_SIZE_SHIFT_DIV;
पूर्ण

अटल u32 wlcore_rx_get_align_buf_size(काष्ठा wl1271 *wl, u32 pkt_len)
अणु
	अगर (wl->quirks & WLCORE_QUIRK_RX_BLOCKSIZE_ALIGN)
		वापस ALIGN(pkt_len, WL12XX_BUS_BLOCK_SIZE);

	वापस pkt_len;
पूर्ण

अटल व्योम wl1271_rx_status(काष्ठा wl1271 *wl,
			     काष्ठा wl1271_rx_descriptor *desc,
			     काष्ठा ieee80211_rx_status *status,
			     u8 beacon, u8 probe_rsp)
अणु
	स_रखो(status, 0, माप(काष्ठा ieee80211_rx_status));

	अगर ((desc->flags & WL1271_RX_DESC_BAND_MASK) == WL1271_RX_DESC_BAND_BG)
		status->band = NL80211_BAND_2GHZ;
	अन्यथा
		status->band = NL80211_BAND_5GHZ;

	status->rate_idx = wlcore_rate_to_idx(wl, desc->rate, status->band);

	/* 11n support */
	अगर (desc->rate <= wl->hw_min_ht_rate)
		status->encoding = RX_ENC_HT;

	/*
	* Read the संकेत level and antenna भागersity indication.
	* The msb in the संकेत level is always set as it is a
	* negative number.
	* The antenna indication is the msb of the rssi.
	*/
	status->संकेत = ((desc->rssi & RSSI_LEVEL_BITMASK) | BIT(7));
	status->antenna = ((desc->rssi & ANT_DIVERSITY_BITMASK) >> 7);

	/*
	 * FIXME: In wl1251, the SNR should be भागided by two.  In wl1271 we
	 * need to भागide by two क्रम now, but TI has been discussing about
	 * changing it.  This needs to be rechecked.
	 */
	wl->noise = desc->rssi - (desc->snr >> 1);

	status->freq = ieee80211_channel_to_frequency(desc->channel,
						      status->band);

	अगर (desc->flags & WL1271_RX_DESC_ENCRYPT_MASK) अणु
		u8 desc_err_code = desc->status & WL1271_RX_DESC_STATUS_MASK;

		status->flag |= RX_FLAG_IV_STRIPPED | RX_FLAG_MMIC_STRIPPED |
				RX_FLAG_DECRYPTED;

		अगर (unlikely(desc_err_code & WL1271_RX_DESC_MIC_FAIL)) अणु
			status->flag |= RX_FLAG_MMIC_ERROR;
			wl1271_warning("Michael MIC error. Desc: 0x%x",
				       desc_err_code);
		पूर्ण
	पूर्ण

	अगर (beacon || probe_rsp)
		status->bootसमय_ns = kसमय_get_bootसमय_ns();

	अगर (beacon)
		wlcore_set_pending_regकरोमुख्य_ch(wl, (u16)desc->channel,
						status->band);
पूर्ण

अटल पूर्णांक wl1271_rx_handle_data(काष्ठा wl1271 *wl, u8 *data, u32 length,
				 क्रमागत wl_rx_buf_align rx_align, u8 *hlid)
अणु
	काष्ठा wl1271_rx_descriptor *desc;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_hdr *hdr;
	u8 beacon = 0;
	u8 is_data = 0;
	u8 reserved = 0, offset_to_data = 0;
	u16 seq_num;
	u32 pkt_data_len;

	/*
	 * In PLT mode we seem to get frames and mac80211 warns about them,
	 * workaround this by not retrieving them at all.
	 */
	अगर (unlikely(wl->plt))
		वापस -EINVAL;

	pkt_data_len = wlcore_hw_get_rx_packet_len(wl, data, length);
	अगर (!pkt_data_len) अणु
		wl1271_error("Invalid packet arrived from HW. length %d",
			     length);
		वापस -EINVAL;
	पूर्ण

	अगर (rx_align == WLCORE_RX_BUF_UNALIGNED)
		reserved = RX_BUF_ALIGN;
	अन्यथा अगर (rx_align == WLCORE_RX_BUF_PADDED)
		offset_to_data = RX_BUF_ALIGN;

	/* the data पढ़ो starts with the descriptor */
	desc = (काष्ठा wl1271_rx_descriptor *) data;

	अगर (desc->packet_class == WL12XX_RX_CLASS_LOGGER) अणु
		माप_प्रकार len = length - माप(*desc);
		wl12xx_copy_fwlog(wl, data + माप(*desc), len);
		वापस 0;
	पूर्ण

	/* discard corrupted packets */
	अगर (desc->status & WL1271_RX_DESC_DECRYPT_FAIL) अणु
		hdr = (व्योम *)(data + माप(*desc) + offset_to_data);
		wl1271_warning("corrupted packet in RX: status: 0x%x len: %d",
			       desc->status & WL1271_RX_DESC_STATUS_MASK,
			       pkt_data_len);
		wl1271_dump((DEBUG_RX|DEBUG_CMD), "PKT: ", data + माप(*desc),
			    min(pkt_data_len,
				ieee80211_hdrlen(hdr->frame_control)));
		वापस -EINVAL;
	पूर्ण

	/* skb length not including rx descriptor */
	skb = __dev_alloc_skb(pkt_data_len + reserved, GFP_KERNEL);
	अगर (!skb) अणु
		wl1271_error("Couldn't allocate RX frame");
		वापस -ENOMEM;
	पूर्ण

	/* reserve the unaligned payload(अगर any) */
	skb_reserve(skb, reserved);

	/*
	 * Copy packets from aggregation buffer to the skbs without rx
	 * descriptor and with packet payload aligned care. In हाल of unaligned
	 * packets copy the packets in offset of 2 bytes guarantee IP header
	 * payload aligned to 4 bytes.
	 */
	skb_put_data(skb, data + माप(*desc), pkt_data_len);
	अगर (rx_align == WLCORE_RX_BUF_PADDED)
		skb_pull(skb, RX_BUF_ALIGN);

	*hlid = desc->hlid;

	hdr = (काष्ठा ieee80211_hdr *)skb->data;
	अगर (ieee80211_is_beacon(hdr->frame_control))
		beacon = 1;
	अगर (ieee80211_is_data_present(hdr->frame_control))
		is_data = 1;

	wl1271_rx_status(wl, desc, IEEE80211_SKB_RXCB(skb), beacon,
			 ieee80211_is_probe_resp(hdr->frame_control));
	wlcore_hw_set_rx_csum(wl, desc, skb);

	seq_num = (le16_to_cpu(hdr->seq_ctrl) & IEEE80211_SCTL_SEQ) >> 4;
	wl1271_debug(DEBUG_RX, "rx skb 0x%p: %d B %s seq %d hlid %d", skb,
		     skb->len - desc->pad_len,
		     beacon ? "beacon" : "",
		     seq_num, *hlid);

	skb_queue_tail(&wl->deferred_rx_queue, skb);
	queue_work(wl->मुक्तzable_wq, &wl->netstack_work);

	वापस is_data;
पूर्ण

पूर्णांक wlcore_rx(काष्ठा wl1271 *wl, काष्ठा wl_fw_status *status)
अणु
	अचिन्हित दीर्घ active_hlids[BITS_TO_LONGS(WLCORE_MAX_LINKS)] = अणु0पूर्ण;
	u32 buf_size;
	u32 fw_rx_counter = status->fw_rx_counter % wl->num_rx_desc;
	u32 drv_rx_counter = wl->rx_counter % wl->num_rx_desc;
	u32 rx_counter;
	u32 pkt_len, align_pkt_len;
	u32 pkt_offset, des;
	u8 hlid;
	क्रमागत wl_rx_buf_align rx_align;
	पूर्णांक ret = 0;

	/* update rates per link */
	hlid = status->counters.hlid;

	अगर (hlid < WLCORE_MAX_LINKS)
		wl->links[hlid].fw_rate_mbps =
				status->counters.tx_last_rate_mbps;

	जबतक (drv_rx_counter != fw_rx_counter) अणु
		buf_size = 0;
		rx_counter = drv_rx_counter;
		जबतक (rx_counter != fw_rx_counter) अणु
			des = le32_to_cpu(status->rx_pkt_descs[rx_counter]);
			pkt_len = wlcore_rx_get_buf_size(wl, des);
			align_pkt_len = wlcore_rx_get_align_buf_size(wl,
								     pkt_len);
			अगर (buf_size + align_pkt_len > wl->aggr_buf_size)
				अवरोध;
			buf_size += align_pkt_len;
			rx_counter++;
			rx_counter %= wl->num_rx_desc;
		पूर्ण

		अगर (buf_size == 0) अणु
			wl1271_warning("received empty data");
			अवरोध;
		पूर्ण

		/* Read all available packets at once */
		des = le32_to_cpu(status->rx_pkt_descs[drv_rx_counter]);
		ret = wlcore_hw_prepare_पढ़ो(wl, des, buf_size);
		अगर (ret < 0)
			जाओ out;

		ret = wlcore_पढ़ो_data(wl, REG_SLV_MEM_DATA, wl->aggr_buf,
				       buf_size, true);
		अगर (ret < 0)
			जाओ out;

		/* Split data पूर्णांकo separate packets */
		pkt_offset = 0;
		जबतक (pkt_offset < buf_size) अणु
			des = le32_to_cpu(status->rx_pkt_descs[drv_rx_counter]);
			pkt_len = wlcore_rx_get_buf_size(wl, des);
			rx_align = wlcore_hw_get_rx_buf_align(wl, des);

			/*
			 * the handle data call can only fail in memory-outage
			 * conditions, in that हाल the received frame will just
			 * be dropped.
			 */
			अगर (wl1271_rx_handle_data(wl,
						  wl->aggr_buf + pkt_offset,
						  pkt_len, rx_align,
						  &hlid) == 1) अणु
				अगर (hlid < wl->num_links)
					__set_bit(hlid, active_hlids);
				अन्यथा
					WARN(1,
					     "hlid (%d) exceeded MAX_LINKS\n",
					     hlid);
			पूर्ण

			wl->rx_counter++;
			drv_rx_counter++;
			drv_rx_counter %= wl->num_rx_desc;
			pkt_offset += wlcore_rx_get_align_buf_size(wl, pkt_len);
		पूर्ण
	पूर्ण

	/*
	 * Write the driver's packet counter to the FW. This is only required
	 * क्रम older hardware revisions
	 */
	अगर (wl->quirks & WLCORE_QUIRK_END_OF_TRANSACTION) अणु
		ret = wlcore_ग_लिखो32(wl, WL12XX_REG_RX_DRIVER_COUNTER,
				     wl->rx_counter);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	wl12xx_rearm_rx_streaming(wl, active_hlids);

out:
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM
पूर्णांक wl1271_rx_filter_enable(काष्ठा wl1271 *wl,
			    पूर्णांक index, bool enable,
			    काष्ठा wl12xx_rx_filter *filter)
अणु
	पूर्णांक ret;

	अगर (!!test_bit(index, wl->rx_filter_enabled) == enable) अणु
		wl1271_warning("Request to enable an already "
			     "enabled rx filter %d", index);
		वापस 0;
	पूर्ण

	ret = wl1271_acx_set_rx_filter(wl, index, enable, filter);

	अगर (ret) अणु
		wl1271_error("Failed to %s rx data filter %d (err=%d)",
			     enable ? "enable" : "disable", index, ret);
		वापस ret;
	पूर्ण

	अगर (enable)
		__set_bit(index, wl->rx_filter_enabled);
	अन्यथा
		__clear_bit(index, wl->rx_filter_enabled);

	वापस 0;
पूर्ण

पूर्णांक wl1271_rx_filter_clear_all(काष्ठा wl1271 *wl)
अणु
	पूर्णांक i, ret = 0;

	क्रम (i = 0; i < WL1271_MAX_RX_FILTERS; i++) अणु
		अगर (!test_bit(i, wl->rx_filter_enabled))
			जारी;
		ret = wl1271_rx_filter_enable(wl, i, 0, शून्य);
		अगर (ret)
			जाओ out;
	पूर्ण

out:
	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */
