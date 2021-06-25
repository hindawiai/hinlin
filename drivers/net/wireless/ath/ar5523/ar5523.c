<शैली गुरु>
/*
 * Copyright (c) 2006 Damien Bergamini <damien.bergamini@मुक्त.fr>
 * Copyright (c) 2006 Sam Leffler, Errno Consulting
 * Copyright (c) 2007 Christoph Hellwig <hch@lst.de>
 * Copyright (c) 2008-2009 Weongyo Jeong <weongyo@मुक्तbsd.org>
 * Copyright (c) 2012 Pontus Fuchs <pontus.fuchs@gmail.com>
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * This driver is based on the uath driver written by Damien Bergamini क्रम
 * OpenBSD, who did black-box analysis of the Winकरोws binary driver to find
 * out how the hardware works.  It contains a lot magic numbers because of
 * that and only has minimal functionality.
 */
#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/completion.h>
#समावेश <linux/firmware.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/usb.h>
#समावेश <net/mac80211.h>

#समावेश "ar5523.h"
#समावेश "ar5523_hw.h"

/*
 * Various supported device venकरोrs/products.
 * UB51: AR5005UG 802.11b/g, UB52: AR5005UX 802.11a/b/g
 */

अटल पूर्णांक ar5523_submit_rx_cmd(काष्ठा ar5523 *ar);
अटल व्योम ar5523_data_tx_pkt_put(काष्ठा ar5523 *ar);

अटल व्योम ar5523_पढ़ो_reply(काष्ठा ar5523 *ar, काष्ठा ar5523_cmd_hdr *hdr,
			      काष्ठा ar5523_tx_cmd *cmd)
अणु
	पूर्णांक dlen, olen;
	__be32 *rp;

	dlen = be32_to_cpu(hdr->len) - माप(*hdr);

	अगर (dlen < 0) अणु
		WARN_ON(1);
		जाओ out;
	पूर्ण

	ar5523_dbg(ar, "Code = %d len = %d\n", be32_to_cpu(hdr->code) & 0xff,
		   dlen);

	rp = (__be32 *)(hdr + 1);
	अगर (dlen >= माप(u32)) अणु
		olen = be32_to_cpu(rp[0]);
		dlen -= माप(u32);
		अगर (olen == 0) अणु
			/* convention is 0 =>'s one word */
			olen = माप(u32);
		पूर्ण
	पूर्ण अन्यथा
		olen = 0;

	अगर (cmd->odata) अणु
		अगर (cmd->olen < olen) अणु
			ar5523_err(ar, "olen too small %d < %d\n",
				   cmd->olen, olen);
			cmd->olen = 0;
			cmd->res = -EOVERFLOW;
		पूर्ण अन्यथा अणु
			cmd->olen = olen;
			स_नकल(cmd->odata, &rp[1], olen);
			cmd->res = 0;
		पूर्ण
	पूर्ण

out:
	complete(&cmd->करोne);
पूर्ण

अटल व्योम ar5523_cmd_rx_cb(काष्ठा urb *urb)
अणु
	काष्ठा ar5523 *ar = urb->context;
	काष्ठा ar5523_tx_cmd *cmd = &ar->tx_cmd;
	काष्ठा ar5523_cmd_hdr *hdr = ar->rx_cmd_buf;
	पूर्णांक dlen;
	u32 code, hdrlen;

	अगर (urb->status) अणु
		अगर (urb->status != -ESHUTDOWN)
			ar5523_err(ar, "RX USB error %d.\n", urb->status);
		जाओ skip;
	पूर्ण

	अगर (urb->actual_length < माप(काष्ठा ar5523_cmd_hdr)) अणु
		ar5523_err(ar, "RX USB to short.\n");
		जाओ skip;
	पूर्ण

	ar5523_dbg(ar, "%s code %02x priv %d\n", __func__,
		   be32_to_cpu(hdr->code) & 0xff, hdr->priv);

	code = be32_to_cpu(hdr->code);
	hdrlen = be32_to_cpu(hdr->len);

	चयन (code & 0xff) अणु
	शेष:
		/* reply to a पढ़ो command */
		अगर (hdr->priv != AR5523_CMD_ID) अणु
			ar5523_err(ar, "Unexpected command id: %02x\n",
				   code & 0xff);
			जाओ skip;
		पूर्ण
		ar5523_पढ़ो_reply(ar, hdr, cmd);
		अवरोध;

	हाल WDCMSG_DEVICE_AVAIL:
		ar5523_dbg(ar, "WDCMSG_DEVICE_AVAIL\n");
		cmd->res = 0;
		cmd->olen = 0;
		complete(&cmd->करोne);
		अवरोध;

	हाल WDCMSG_SEND_COMPLETE:
		ar5523_dbg(ar, "WDCMSG_SEND_COMPLETE: %d pending\n",
			atomic_पढ़ो(&ar->tx_nr_pending));
		अगर (!test_bit(AR5523_HW_UP, &ar->flags))
			ar5523_dbg(ar, "Unexpected WDCMSG_SEND_COMPLETE\n");
		अन्यथा अणु
			mod_समयr(&ar->tx_wd_समयr,
				  jअगरfies + AR5523_TX_WD_TIMEOUT);
			ar5523_data_tx_pkt_put(ar);

		पूर्ण
		अवरोध;

	हाल WDCMSG_TARGET_START:
		/* This command वापसs a bogus id so it needs special
		   handling */
		dlen = hdrlen - माप(*hdr);
		अगर (dlen != (पूर्णांक)माप(u32)) अणु
			ar5523_err(ar, "Invalid reply to WDCMSG_TARGET_START");
			वापस;
		पूर्ण
		स_नकल(cmd->odata, hdr + 1, माप(u32));
		cmd->olen = माप(u32);
		cmd->res = 0;
		complete(&cmd->करोne);
		अवरोध;

	हाल WDCMSG_STATS_UPDATE:
		ar5523_dbg(ar, "WDCMSG_STATS_UPDATE\n");
		अवरोध;
	पूर्ण

skip:
	ar5523_submit_rx_cmd(ar);
पूर्ण

अटल पूर्णांक ar5523_alloc_rx_cmd(काष्ठा ar5523 *ar)
अणु
	ar->rx_cmd_urb = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!ar->rx_cmd_urb)
		वापस -ENOMEM;

	ar->rx_cmd_buf = usb_alloc_coherent(ar->dev, AR5523_MAX_RXCMDSZ,
					    GFP_KERNEL,
					    &ar->rx_cmd_urb->transfer_dma);
	अगर (!ar->rx_cmd_buf) अणु
		usb_मुक्त_urb(ar->rx_cmd_urb);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ar5523_cancel_rx_cmd(काष्ठा ar5523 *ar)
अणु
	usb_समाप्त_urb(ar->rx_cmd_urb);
पूर्ण

अटल व्योम ar5523_मुक्त_rx_cmd(काष्ठा ar5523 *ar)
अणु
	usb_मुक्त_coherent(ar->dev, AR5523_MAX_RXCMDSZ,
			  ar->rx_cmd_buf, ar->rx_cmd_urb->transfer_dma);
	usb_मुक्त_urb(ar->rx_cmd_urb);
पूर्ण

अटल पूर्णांक ar5523_submit_rx_cmd(काष्ठा ar5523 *ar)
अणु
	पूर्णांक error;

	usb_fill_bulk_urb(ar->rx_cmd_urb, ar->dev,
			  ar5523_cmd_rx_pipe(ar->dev), ar->rx_cmd_buf,
			  AR5523_MAX_RXCMDSZ, ar5523_cmd_rx_cb, ar);
	ar->rx_cmd_urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	error = usb_submit_urb(ar->rx_cmd_urb, GFP_ATOMIC);
	अगर (error) अणु
		अगर (error != -ENODEV)
			ar5523_err(ar, "error %d when submitting rx urb\n",
				   error);
		वापस error;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Command submitted cb
 */
अटल व्योम ar5523_cmd_tx_cb(काष्ठा urb *urb)
अणु
	काष्ठा ar5523_tx_cmd *cmd = urb->context;
	काष्ठा ar5523 *ar = cmd->ar;

	अगर (urb->status) अणु
		ar5523_err(ar, "Failed to TX command. Status = %d\n",
			   urb->status);
		cmd->res = urb->status;
		complete(&cmd->करोne);
		वापस;
	पूर्ण

	अगर (!(cmd->flags & AR5523_CMD_FLAG_READ)) अणु
		cmd->res = 0;
		complete(&cmd->करोne);
	पूर्ण
पूर्ण

अटल पूर्णांक ar5523_cmd(काष्ठा ar5523 *ar, u32 code, स्थिर व्योम *idata,
		      पूर्णांक ilen, व्योम *odata, पूर्णांक olen, पूर्णांक flags)
अणु
	काष्ठा ar5523_cmd_hdr *hdr;
	काष्ठा ar5523_tx_cmd *cmd = &ar->tx_cmd;
	पूर्णांक xferlen, error;

	/* always bulk-out a multiple of 4 bytes */
	xferlen = (माप(काष्ठा ar5523_cmd_hdr) + ilen + 3) & ~3;

	hdr = (काष्ठा ar5523_cmd_hdr *)cmd->buf_tx;
	स_रखो(hdr, 0, माप(काष्ठा ar5523_cmd_hdr));
	hdr->len  = cpu_to_be32(xferlen);
	hdr->code = cpu_to_be32(code);
	hdr->priv = AR5523_CMD_ID;

	अगर (flags & AR5523_CMD_FLAG_MAGIC)
		hdr->magic = cpu_to_be32(1 << 24);
	अगर (ilen)
		स_नकल(hdr + 1, idata, ilen);

	cmd->odata = odata;
	cmd->olen = olen;
	cmd->flags = flags;

	ar5523_dbg(ar, "do cmd %02x\n", code);

	usb_fill_bulk_urb(cmd->urb_tx, ar->dev, ar5523_cmd_tx_pipe(ar->dev),
			  cmd->buf_tx, xferlen, ar5523_cmd_tx_cb, cmd);
	cmd->urb_tx->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	error = usb_submit_urb(cmd->urb_tx, GFP_KERNEL);
	अगर (error) अणु
		ar5523_err(ar, "could not send command 0x%x, error=%d\n",
			   code, error);
		वापस error;
	पूर्ण

	अगर (!रुको_क्रम_completion_समयout(&cmd->करोne, 2 * HZ)) अणु
		cmd->odata = शून्य;
		ar5523_err(ar, "timeout waiting for command %02x reply\n",
			   code);
		cmd->res = -ETIMEDOUT;
	पूर्ण
	वापस cmd->res;
पूर्ण

अटल पूर्णांक ar5523_cmd_ग_लिखो(काष्ठा ar5523 *ar, u32 code, स्थिर व्योम *data,
			    पूर्णांक len, पूर्णांक flags)
अणु
	flags &= ~AR5523_CMD_FLAG_READ;
	वापस ar5523_cmd(ar, code, data, len, शून्य, 0, flags);
पूर्ण

अटल पूर्णांक ar5523_cmd_पढ़ो(काष्ठा ar5523 *ar, u32 code, स्थिर व्योम *idata,
			   पूर्णांक ilen, व्योम *odata, पूर्णांक olen, पूर्णांक flags)
अणु
	flags |= AR5523_CMD_FLAG_READ;
	वापस ar5523_cmd(ar, code, idata, ilen, odata, olen, flags);
पूर्ण

अटल पूर्णांक ar5523_config(काष्ठा ar5523 *ar, u32 reg, u32 val)
अणु
	काष्ठा ar5523_ग_लिखो_mac ग_लिखो;
	पूर्णांक error;

	ग_लिखो.reg = cpu_to_be32(reg);
	ग_लिखो.len = cpu_to_be32(0);	/* 0 = single ग_लिखो */
	*(__be32 *)ग_लिखो.data = cpu_to_be32(val);

	error = ar5523_cmd_ग_लिखो(ar, WDCMSG_TARGET_SET_CONFIG, &ग_लिखो,
				 3 * माप(u32), 0);
	अगर (error != 0)
		ar5523_err(ar, "could not write register 0x%02x\n", reg);
	वापस error;
पूर्ण

अटल पूर्णांक ar5523_config_multi(काष्ठा ar5523 *ar, u32 reg, स्थिर व्योम *data,
			       पूर्णांक len)
अणु
	काष्ठा ar5523_ग_लिखो_mac ग_लिखो;
	पूर्णांक error;

	ग_लिखो.reg = cpu_to_be32(reg);
	ग_लिखो.len = cpu_to_be32(len);
	स_नकल(ग_लिखो.data, data, len);

	/* properly handle the हाल where len is zero (reset) */
	error = ar5523_cmd_ग_लिखो(ar, WDCMSG_TARGET_SET_CONFIG, &ग_लिखो,
	    (len == 0) ? माप(u32) : 2 * माप(u32) + len, 0);
	अगर (error != 0)
		ar5523_err(ar, "could not write %d bytes to register 0x%02x\n",
			   len, reg);
	वापस error;
पूर्ण

अटल पूर्णांक ar5523_get_status(काष्ठा ar5523 *ar, u32 which, व्योम *odata,
			     पूर्णांक olen)
अणु
	पूर्णांक error;
	__be32 which_be;

	which_be = cpu_to_be32(which);
	error = ar5523_cmd_पढ़ो(ar, WDCMSG_TARGET_GET_STATUS,
	    &which_be, माप(which_be), odata, olen, AR5523_CMD_FLAG_MAGIC);
	अगर (error != 0)
		ar5523_err(ar, "could not read EEPROM offset 0x%02x\n", which);
	वापस error;
पूर्ण

अटल पूर्णांक ar5523_get_capability(काष्ठा ar5523 *ar, u32 cap, u32 *val)
अणु
	पूर्णांक error;
	__be32 cap_be, val_be;

	cap_be = cpu_to_be32(cap);
	error = ar5523_cmd_पढ़ो(ar, WDCMSG_TARGET_GET_CAPABILITY, &cap_be,
				माप(cap_be), &val_be, माप(__be32),
				AR5523_CMD_FLAG_MAGIC);
	अगर (error != 0) अणु
		ar5523_err(ar, "could not read capability %u\n", cap);
		वापस error;
	पूर्ण
	*val = be32_to_cpu(val_be);
	वापस error;
पूर्ण

अटल पूर्णांक ar5523_get_devcap(काष्ठा ar5523 *ar)
अणु
#घोषणा	GETCAP(x) करो अणु				\
	error = ar5523_get_capability(ar, x, &cap);		\
	अगर (error != 0)					\
		वापस error;				\
	ar5523_info(ar, "Cap: "			\
	    "%s=0x%08x\n", #x, cap);	\
पूर्ण जबतक (0)
	पूर्णांक error;
	u32 cap;

	/* collect device capabilities */
	GETCAP(CAP_TARGET_VERSION);
	GETCAP(CAP_TARGET_REVISION);
	GETCAP(CAP_MAC_VERSION);
	GETCAP(CAP_MAC_REVISION);
	GETCAP(CAP_PHY_REVISION);
	GETCAP(CAP_ANALOG_5GHz_REVISION);
	GETCAP(CAP_ANALOG_2GHz_REVISION);

	GETCAP(CAP_REG_DOMAIN);
	GETCAP(CAP_REG_CAP_BITS);
	GETCAP(CAP_WIRELESS_MODES);
	GETCAP(CAP_CHAN_SPREAD_SUPPORT);
	GETCAP(CAP_COMPRESS_SUPPORT);
	GETCAP(CAP_BURST_SUPPORT);
	GETCAP(CAP_FAST_FRAMES_SUPPORT);
	GETCAP(CAP_CHAP_TUNING_SUPPORT);
	GETCAP(CAP_TURBOG_SUPPORT);
	GETCAP(CAP_TURBO_PRIME_SUPPORT);
	GETCAP(CAP_DEVICE_TYPE);
	GETCAP(CAP_WME_SUPPORT);
	GETCAP(CAP_TOTAL_QUEUES);
	GETCAP(CAP_CONNECTION_ID_MAX);

	GETCAP(CAP_LOW_5GHZ_CHAN);
	GETCAP(CAP_HIGH_5GHZ_CHAN);
	GETCAP(CAP_LOW_2GHZ_CHAN);
	GETCAP(CAP_HIGH_2GHZ_CHAN);
	GETCAP(CAP_TWICE_ANTENNAGAIN_5G);
	GETCAP(CAP_TWICE_ANTENNAGAIN_2G);

	GETCAP(CAP_CIPHER_AES_CCM);
	GETCAP(CAP_CIPHER_TKIP);
	GETCAP(CAP_MIC_TKIP);
	वापस 0;
पूर्ण

अटल पूर्णांक ar5523_set_ledsteady(काष्ठा ar5523 *ar, पूर्णांक lednum, पूर्णांक ledmode)
अणु
	काष्ठा ar5523_cmd_ledsteady led;

	led.lednum = cpu_to_be32(lednum);
	led.ledmode = cpu_to_be32(ledmode);

	ar5523_dbg(ar, "set %s led %s (steady)\n",
		   (lednum == UATH_LED_LINK) ? "link" : "activity",
		   ledmode ? "on" : "off");
	वापस ar5523_cmd_ग_लिखो(ar, WDCMSG_SET_LED_STEADY, &led, माप(led),
				 0);
पूर्ण

अटल पूर्णांक ar5523_set_rxfilter(काष्ठा ar5523 *ar, u32 bits, u32 op)
अणु
	काष्ठा ar5523_cmd_rx_filter rxfilter;

	rxfilter.bits = cpu_to_be32(bits);
	rxfilter.op = cpu_to_be32(op);

	ar5523_dbg(ar, "setting Rx filter=0x%x flags=0x%x\n", bits, op);
	वापस ar5523_cmd_ग_लिखो(ar, WDCMSG_RX_FILTER, &rxfilter,
				 माप(rxfilter), 0);
पूर्ण

अटल पूर्णांक ar5523_reset_tx_queues(काष्ठा ar5523 *ar)
अणु
	__be32 qid = cpu_to_be32(0);

	ar5523_dbg(ar, "resetting Tx queue\n");
	वापस ar5523_cmd_ग_लिखो(ar, WDCMSG_RELEASE_TX_QUEUE,
				 &qid, माप(qid), 0);
पूर्ण

अटल पूर्णांक ar5523_set_chan(काष्ठा ar5523 *ar)
अणु
	काष्ठा ieee80211_conf *conf = &ar->hw->conf;

	काष्ठा ar5523_cmd_reset reset;

	स_रखो(&reset, 0, माप(reset));
	reset.flags |= cpu_to_be32(UATH_CHAN_2GHZ);
	reset.flags |= cpu_to_be32(UATH_CHAN_OFDM);
	reset.freq = cpu_to_be32(conf->chandef.chan->center_freq);
	reset.maxrdघातer = cpu_to_be32(50);	/* XXX */
	reset.channelchange = cpu_to_be32(1);
	reset.keeprccontent = cpu_to_be32(0);

	ar5523_dbg(ar, "set chan flags 0x%x freq %d\n",
		   be32_to_cpu(reset.flags),
		   conf->chandef.chan->center_freq);
	वापस ar5523_cmd_ग_लिखो(ar, WDCMSG_RESET, &reset, माप(reset), 0);
पूर्ण

अटल पूर्णांक ar5523_queue_init(काष्ठा ar5523 *ar)
अणु
	काष्ठा ar5523_cmd_txq_setup qinfo;

	ar5523_dbg(ar, "setting up Tx queue\n");
	qinfo.qid	     = cpu_to_be32(0);
	qinfo.len	     = cpu_to_be32(माप(qinfo.attr));
	qinfo.attr.priority  = cpu_to_be32(0);	/* XXX */
	qinfo.attr.aअगरs	     = cpu_to_be32(3);
	qinfo.attr.logcwmin  = cpu_to_be32(4);
	qinfo.attr.logcwmax  = cpu_to_be32(10);
	qinfo.attr.burstसमय = cpu_to_be32(0);
	qinfo.attr.mode	     = cpu_to_be32(0);
	qinfo.attr.qflags    = cpu_to_be32(1);	/* XXX? */
	वापस ar5523_cmd_ग_लिखो(ar, WDCMSG_SETUP_TX_QUEUE, &qinfo,
				 माप(qinfo), 0);
पूर्ण

अटल पूर्णांक ar5523_चयन_chan(काष्ठा ar5523 *ar)
अणु
	पूर्णांक error;

	error = ar5523_set_chan(ar);
	अगर (error) अणु
		ar5523_err(ar, "could not set chan, error %d\n", error);
		जाओ out_err;
	पूर्ण

	/* reset Tx rings */
	error = ar5523_reset_tx_queues(ar);
	अगर (error) अणु
		ar5523_err(ar, "could not reset Tx queues, error %d\n",
			   error);
		जाओ out_err;
	पूर्ण
	/* set Tx rings WME properties */
	error = ar5523_queue_init(ar);
	अगर (error)
		ar5523_err(ar, "could not init wme, error %d\n", error);

out_err:
	वापस error;
पूर्ण

अटल व्योम ar5523_rx_data_put(काष्ठा ar5523 *ar,
				काष्ठा ar5523_rx_data *data)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&ar->rx_data_list_lock, flags);
	list_move(&data->list, &ar->rx_data_मुक्त);
	spin_unlock_irqrestore(&ar->rx_data_list_lock, flags);
पूर्ण

अटल व्योम ar5523_data_rx_cb(काष्ठा urb *urb)
अणु
	काष्ठा ar5523_rx_data *data = urb->context;
	काष्ठा ar5523 *ar = data->ar;
	काष्ठा ar5523_rx_desc *desc;
	काष्ठा ar5523_chunk *chunk;
	काष्ठा ieee80211_hw *hw = ar->hw;
	काष्ठा ieee80211_rx_status *rx_status;
	u32 rxlen;
	पूर्णांक usblen = urb->actual_length;
	पूर्णांक hdrlen, pad;

	ar5523_dbg(ar, "%s\n", __func__);
	/* sync/async unlink faults aren't errors */
	अगर (urb->status) अणु
		अगर (urb->status != -ESHUTDOWN)
			ar5523_err(ar, "%s: USB err: %d\n", __func__,
				   urb->status);
		जाओ skip;
	पूर्ण

	अगर (usblen < AR5523_MIN_RXBUFSZ) अणु
		ar5523_err(ar, "RX: wrong xfer size (usblen=%d)\n", usblen);
		जाओ skip;
	पूर्ण

	chunk = (काष्ठा ar5523_chunk *) data->skb->data;

	अगर (((chunk->flags & UATH_CFLAGS_FINAL) == 0) ||
		chunk->seqnum != 0) अणु
		ar5523_dbg(ar, "RX: No final flag. s: %d f: %02x l: %d\n",
			   chunk->seqnum, chunk->flags,
			   be16_to_cpu(chunk->length));
		जाओ skip;
	पूर्ण

	/* Rx descriptor is located at the end, 32-bit aligned */
	desc = (काष्ठा ar5523_rx_desc *)
		(data->skb->data + usblen - माप(काष्ठा ar5523_rx_desc));

	rxlen = be32_to_cpu(desc->len);
	अगर (rxlen > ar->rxbufsz) अणु
		ar5523_dbg(ar, "RX: Bad descriptor (len=%d)\n",
			   be32_to_cpu(desc->len));
		जाओ skip;
	पूर्ण

	अगर (!rxlen) अणु
		ar5523_dbg(ar, "RX: rxlen is 0\n");
		जाओ skip;
	पूर्ण

	अगर (be32_to_cpu(desc->status) != 0) अणु
		ar5523_dbg(ar, "Bad RX status (0x%x len = %d). Skip\n",
			   be32_to_cpu(desc->status), be32_to_cpu(desc->len));
		जाओ skip;
	पूर्ण

	skb_reserve(data->skb, माप(*chunk));
	skb_put(data->skb, rxlen - माप(काष्ठा ar5523_rx_desc));

	hdrlen = ieee80211_get_hdrlen_from_skb(data->skb);
	अगर (!IS_ALIGNED(hdrlen, 4)) अणु
		ar5523_dbg(ar, "eek, alignment workaround activated\n");
		pad = ALIGN(hdrlen, 4) - hdrlen;
		स_हटाओ(data->skb->data + pad, data->skb->data, hdrlen);
		skb_pull(data->skb, pad);
		skb_put(data->skb, pad);
	पूर्ण

	rx_status = IEEE80211_SKB_RXCB(data->skb);
	स_रखो(rx_status, 0, माप(*rx_status));
	rx_status->freq = be32_to_cpu(desc->channel);
	rx_status->band = hw->conf.chandef.chan->band;
	rx_status->संकेत = -95 + be32_to_cpu(desc->rssi);

	ieee80211_rx_irqsafe(hw, data->skb);
	data->skb = शून्य;

skip:
	अगर (data->skb) अणु
		dev_kमुक्त_skb_irq(data->skb);
		data->skb = शून्य;
	पूर्ण

	ar5523_rx_data_put(ar, data);
	अगर (atomic_inc_वापस(&ar->rx_data_मुक्त_cnt) >=
	    AR5523_RX_DATA_REFILL_COUNT &&
	    test_bit(AR5523_HW_UP, &ar->flags))
		queue_work(ar->wq, &ar->rx_refill_work);
पूर्ण

अटल व्योम ar5523_rx_refill_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ar5523 *ar = container_of(work, काष्ठा ar5523, rx_refill_work);
	काष्ठा ar5523_rx_data *data;
	अचिन्हित दीर्घ flags;
	पूर्णांक error;

	ar5523_dbg(ar, "%s\n", __func__);
	करो अणु
		spin_lock_irqsave(&ar->rx_data_list_lock, flags);

		अगर (!list_empty(&ar->rx_data_मुक्त))
			data = (काष्ठा ar5523_rx_data *) ar->rx_data_मुक्त.next;
		अन्यथा
			data = शून्य;
		spin_unlock_irqrestore(&ar->rx_data_list_lock, flags);

		अगर (!data)
			जाओ करोne;

		data->skb = alloc_skb(ar->rxbufsz, GFP_KERNEL);
		अगर (!data->skb) अणु
			ar5523_err(ar, "could not allocate rx skbuff\n");
			वापस;
		पूर्ण

		usb_fill_bulk_urb(data->urb, ar->dev,
				  ar5523_data_rx_pipe(ar->dev), data->skb->data,
				  ar->rxbufsz, ar5523_data_rx_cb, data);

		spin_lock_irqsave(&ar->rx_data_list_lock, flags);
		list_move(&data->list, &ar->rx_data_used);
		spin_unlock_irqrestore(&ar->rx_data_list_lock, flags);
		atomic_dec(&ar->rx_data_मुक्त_cnt);

		error = usb_submit_urb(data->urb, GFP_KERNEL);
		अगर (error) अणु
			kमुक्त_skb(data->skb);
			अगर (error != -ENODEV)
				ar5523_err(ar, "Err sending rx data urb %d\n",
					   error);
			ar5523_rx_data_put(ar, data);
			atomic_inc(&ar->rx_data_मुक्त_cnt);
			वापस;
		पूर्ण

	पूर्ण जबतक (true);
करोne:
	वापस;
पूर्ण

अटल व्योम ar5523_cancel_rx_bufs(काष्ठा ar5523 *ar)
अणु
	काष्ठा ar5523_rx_data *data;
	अचिन्हित दीर्घ flags;

	करो अणु
		spin_lock_irqsave(&ar->rx_data_list_lock, flags);
		अगर (!list_empty(&ar->rx_data_used))
			data = (काष्ठा ar5523_rx_data *) ar->rx_data_used.next;
		अन्यथा
			data = शून्य;
		spin_unlock_irqrestore(&ar->rx_data_list_lock, flags);

		अगर (!data)
			अवरोध;

		usb_समाप्त_urb(data->urb);
		list_move(&data->list, &ar->rx_data_मुक्त);
		atomic_inc(&ar->rx_data_मुक्त_cnt);
	पूर्ण जबतक (data);
पूर्ण

अटल व्योम ar5523_मुक्त_rx_bufs(काष्ठा ar5523 *ar)
अणु
	काष्ठा ar5523_rx_data *data;

	ar5523_cancel_rx_bufs(ar);
	जबतक (!list_empty(&ar->rx_data_मुक्त)) अणु
		data = (काष्ठा ar5523_rx_data *) ar->rx_data_मुक्त.next;
		list_del(&data->list);
		usb_मुक्त_urb(data->urb);
	पूर्ण
पूर्ण

अटल पूर्णांक ar5523_alloc_rx_bufs(काष्ठा ar5523 *ar)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < AR5523_RX_DATA_COUNT; i++) अणु
		काष्ठा ar5523_rx_data *data = &ar->rx_data[i];

		data->ar = ar;
		data->urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!data->urb)
			जाओ err;
		list_add_tail(&data->list, &ar->rx_data_मुक्त);
		atomic_inc(&ar->rx_data_मुक्त_cnt);
	पूर्ण
	वापस 0;

err:
	ar5523_मुक्त_rx_bufs(ar);
	वापस -ENOMEM;
पूर्ण

अटल व्योम ar5523_data_tx_pkt_put(काष्ठा ar5523 *ar)
अणु
	atomic_dec(&ar->tx_nr_total);
	अगर (!atomic_dec_वापस(&ar->tx_nr_pending)) अणु
		del_समयr(&ar->tx_wd_समयr);
		wake_up(&ar->tx_flush_रुकोq);
	पूर्ण

	अगर (atomic_पढ़ो(&ar->tx_nr_total) < AR5523_TX_DATA_RESTART_COUNT) अणु
		ar5523_dbg(ar, "restart tx queue\n");
		ieee80211_wake_queues(ar->hw);
	पूर्ण
पूर्ण

अटल व्योम ar5523_data_tx_cb(काष्ठा urb *urb)
अणु
	काष्ठा sk_buff *skb = urb->context;
	काष्ठा ieee80211_tx_info *txi = IEEE80211_SKB_CB(skb);
	काष्ठा ar5523_tx_data *data = (काष्ठा ar5523_tx_data *)
				       txi->driver_data;
	काष्ठा ar5523 *ar = data->ar;
	अचिन्हित दीर्घ flags;

	ar5523_dbg(ar, "data tx urb completed: %d\n", urb->status);

	spin_lock_irqsave(&ar->tx_data_list_lock, flags);
	list_del(&data->list);
	spin_unlock_irqrestore(&ar->tx_data_list_lock, flags);

	अगर (urb->status) अणु
		ar5523_dbg(ar, "%s: urb status: %d\n", __func__, urb->status);
		ar5523_data_tx_pkt_put(ar);
		ieee80211_मुक्त_txskb(ar->hw, skb);
	पूर्ण अन्यथा अणु
		skb_pull(skb, माप(काष्ठा ar5523_tx_desc) + माप(__be32));
		ieee80211_tx_status_irqsafe(ar->hw, skb);
	पूर्ण
	usb_मुक्त_urb(urb);
पूर्ण

अटल व्योम ar5523_tx(काष्ठा ieee80211_hw *hw,
		       काष्ठा ieee80211_tx_control *control,
		       काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *txi = IEEE80211_SKB_CB(skb);
	काष्ठा ar5523_tx_data *data = (काष्ठा ar5523_tx_data *)
					txi->driver_data;
	काष्ठा ar5523 *ar = hw->priv;
	अचिन्हित दीर्घ flags;

	ar5523_dbg(ar, "tx called\n");
	अगर (atomic_inc_वापस(&ar->tx_nr_total) >= AR5523_TX_DATA_COUNT) अणु
		ar5523_dbg(ar, "tx queue full\n");
		ar5523_dbg(ar, "stop queues (tot %d pend %d)\n",
			   atomic_पढ़ो(&ar->tx_nr_total),
			   atomic_पढ़ो(&ar->tx_nr_pending));
		ieee80211_stop_queues(hw);
	पूर्ण

	spin_lock_irqsave(&ar->tx_data_list_lock, flags);
	list_add_tail(&data->list, &ar->tx_queue_pending);
	spin_unlock_irqrestore(&ar->tx_data_list_lock, flags);

	ieee80211_queue_work(ar->hw, &ar->tx_work);
पूर्ण

अटल व्योम ar5523_tx_work_locked(काष्ठा ar5523 *ar)
अणु
	काष्ठा ar5523_tx_data *data;
	काष्ठा ar5523_tx_desc *desc;
	काष्ठा ar5523_chunk *chunk;
	काष्ठा ieee80211_tx_info *txi;
	काष्ठा urb *urb;
	काष्ठा sk_buff *skb;
	पूर्णांक error = 0, paylen;
	u32 txqid;
	अचिन्हित दीर्घ flags;

	BUILD_BUG_ON(माप(काष्ठा ar5523_tx_data) >
		     IEEE80211_TX_INFO_DRIVER_DATA_SIZE);

	ar5523_dbg(ar, "%s\n", __func__);
	करो अणु
		spin_lock_irqsave(&ar->tx_data_list_lock, flags);
		अगर (!list_empty(&ar->tx_queue_pending)) अणु
			data = (काष्ठा ar5523_tx_data *)
				ar->tx_queue_pending.next;
			list_del(&data->list);
		पूर्ण अन्यथा
			data = शून्य;
		spin_unlock_irqrestore(&ar->tx_data_list_lock, flags);

		अगर (!data)
			अवरोध;

		txi = container_of((व्योम *)data, काष्ठा ieee80211_tx_info,
				   driver_data);
		txqid = 0;

		skb = container_of((व्योम *)txi, काष्ठा sk_buff, cb);
		paylen = skb->len;

		urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!urb) अणु
			ieee80211_मुक्त_txskb(ar->hw, skb);
			जारी;
		पूर्ण

		data->ar = ar;
		data->urb = urb;

		desc = skb_push(skb, माप(*desc));
		chunk = skb_push(skb, माप(*chunk));

		chunk->seqnum = 0;
		chunk->flags = UATH_CFLAGS_FINAL;
		chunk->length = cpu_to_be16(skb->len);

		desc->msglen = cpu_to_be32(skb->len);
		desc->msgid  = AR5523_DATA_ID;
		desc->buflen = cpu_to_be32(paylen);
		desc->type   = cpu_to_be32(WDCMSG_SEND);
		desc->flags  = cpu_to_be32(UATH_TX_NOTIFY);

		अगर (test_bit(AR5523_CONNECTED, &ar->flags))
			desc->connid = cpu_to_be32(AR5523_ID_BSS);
		अन्यथा
			desc->connid = cpu_to_be32(AR5523_ID_BROADCAST);

		अगर (txi->flags & IEEE80211_TX_CTL_USE_MINRATE)
			txqid |= UATH_TXQID_MINRATE;

		desc->txqid = cpu_to_be32(txqid);

		urb->transfer_flags = URB_ZERO_PACKET;
		usb_fill_bulk_urb(urb, ar->dev, ar5523_data_tx_pipe(ar->dev),
				  skb->data, skb->len, ar5523_data_tx_cb, skb);

		spin_lock_irqsave(&ar->tx_data_list_lock, flags);
		list_add_tail(&data->list, &ar->tx_queue_submitted);
		spin_unlock_irqrestore(&ar->tx_data_list_lock, flags);
		mod_समयr(&ar->tx_wd_समयr, jअगरfies + AR5523_TX_WD_TIMEOUT);
		atomic_inc(&ar->tx_nr_pending);

		ar5523_dbg(ar, "TX Frame (%d pending)\n",
			   atomic_पढ़ो(&ar->tx_nr_pending));
		error = usb_submit_urb(urb, GFP_KERNEL);
		अगर (error) अणु
			ar5523_err(ar, "error %d when submitting tx urb\n",
				   error);
			spin_lock_irqsave(&ar->tx_data_list_lock, flags);
			list_del(&data->list);
			spin_unlock_irqrestore(&ar->tx_data_list_lock, flags);
			atomic_dec(&ar->tx_nr_pending);
			ar5523_data_tx_pkt_put(ar);
			usb_मुक्त_urb(urb);
			ieee80211_मुक्त_txskb(ar->hw, skb);
		पूर्ण
	पूर्ण जबतक (true);
पूर्ण

अटल व्योम ar5523_tx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ar5523 *ar = container_of(work, काष्ठा ar5523, tx_work);

	ar5523_dbg(ar, "%s\n", __func__);
	mutex_lock(&ar->mutex);
	ar5523_tx_work_locked(ar);
	mutex_unlock(&ar->mutex);
पूर्ण

अटल व्योम ar5523_tx_wd_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा ar5523 *ar = from_समयr(ar, t, tx_wd_समयr);

	ar5523_dbg(ar, "TX watchdog timer triggered\n");
	ieee80211_queue_work(ar->hw, &ar->tx_wd_work);
पूर्ण

अटल व्योम ar5523_tx_wd_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ar5523 *ar = container_of(work, काष्ठा ar5523, tx_wd_work);

	/* Occasionally the TX queues stop responding. The only way to
	 * recover seems to be to reset the करोngle.
	 */

	mutex_lock(&ar->mutex);
	ar5523_err(ar, "TX queue stuck (tot %d pend %d)\n",
		   atomic_पढ़ो(&ar->tx_nr_total),
		   atomic_पढ़ो(&ar->tx_nr_pending));

	ar5523_err(ar, "Will restart dongle.\n");
	ar5523_cmd_ग_लिखो(ar, WDCMSG_TARGET_RESET, शून्य, 0, 0);
	mutex_unlock(&ar->mutex);
पूर्ण

अटल व्योम ar5523_flush_tx(काष्ठा ar5523 *ar)
अणु
	ar5523_tx_work_locked(ar);

	/* Don't waste समय trying to flush अगर USB is disconnected */
	अगर (test_bit(AR5523_USB_DISCONNECTED, &ar->flags))
		वापस;
	अगर (!रुको_event_समयout(ar->tx_flush_रुकोq,
	    !atomic_पढ़ो(&ar->tx_nr_pending), AR5523_FLUSH_TIMEOUT))
		ar5523_err(ar, "flush timeout (tot %d pend %d)\n",
			   atomic_पढ़ो(&ar->tx_nr_total),
			   atomic_पढ़ो(&ar->tx_nr_pending));
पूर्ण

अटल व्योम ar5523_मुक्त_tx_cmd(काष्ठा ar5523 *ar)
अणु
	काष्ठा ar5523_tx_cmd *cmd = &ar->tx_cmd;

	usb_मुक्त_coherent(ar->dev, AR5523_MAX_RXCMDSZ, cmd->buf_tx,
			  cmd->urb_tx->transfer_dma);
	usb_मुक्त_urb(cmd->urb_tx);
पूर्ण

अटल पूर्णांक ar5523_alloc_tx_cmd(काष्ठा ar5523 *ar)
अणु
	काष्ठा ar5523_tx_cmd *cmd = &ar->tx_cmd;

	cmd->ar = ar;
	init_completion(&cmd->करोne);

	cmd->urb_tx = usb_alloc_urb(0, GFP_KERNEL);
	अगर (!cmd->urb_tx)
		वापस -ENOMEM;
	cmd->buf_tx = usb_alloc_coherent(ar->dev, AR5523_MAX_TXCMDSZ,
					 GFP_KERNEL,
					 &cmd->urb_tx->transfer_dma);
	अगर (!cmd->buf_tx) अणु
		usb_मुक्त_urb(cmd->urb_tx);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * This function is called periodically (every second) when associated to
 * query device statistics.
 */
अटल व्योम ar5523_stat_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ar5523 *ar = container_of(work, काष्ठा ar5523, stat_work.work);
	पूर्णांक error;

	ar5523_dbg(ar, "%s\n", __func__);
	mutex_lock(&ar->mutex);

	/*
	 * Send request क्रम statistics asynchronously once a second. This
	 * seems to be important. Throughput is a lot better अगर this is करोne.
	 */
	error = ar5523_cmd_ग_लिखो(ar, WDCMSG_TARGET_GET_STATS, शून्य, 0, 0);
	अगर (error)
		ar5523_err(ar, "could not query stats, error %d\n", error);
	mutex_unlock(&ar->mutex);
	ieee80211_queue_delayed_work(ar->hw, &ar->stat_work, HZ);
पूर्ण

/*
 * Interface routines to the mac80211 stack.
 */
अटल पूर्णांक ar5523_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ar5523 *ar = hw->priv;
	पूर्णांक error;
	__be32 val;

	ar5523_dbg(ar, "start called\n");

	mutex_lock(&ar->mutex);
	val = cpu_to_be32(0);
	ar5523_cmd_ग_लिखो(ar, WDCMSG_BIND, &val, माप(val), 0);

	/* set MAC address */
	ar5523_config_multi(ar, CFG_MAC_ADDR, &ar->hw->wiphy->perm_addr,
			    ETH_ALEN);

	/* XXX honor net80211 state */
	ar5523_config(ar, CFG_RATE_CONTROL_ENABLE, 0x00000001);
	ar5523_config(ar, CFG_DIVERSITY_CTL, 0x00000001);
	ar5523_config(ar, CFG_ABOLT, 0x0000003f);
	ar5523_config(ar, CFG_WME_ENABLED, 0x00000000);

	ar5523_config(ar, CFG_SERVICE_TYPE, 1);
	ar5523_config(ar, CFG_TP_SCALE, 0x00000000);
	ar5523_config(ar, CFG_TPC_HALF_DBM5, 0x0000003c);
	ar5523_config(ar, CFG_TPC_HALF_DBM2, 0x0000003c);
	ar5523_config(ar, CFG_OVERRD_TX_POWER, 0x00000000);
	ar5523_config(ar, CFG_GMODE_PROTECTION, 0x00000000);
	ar5523_config(ar, CFG_GMODE_PROTECT_RATE_INDEX, 0x00000003);
	ar5523_config(ar, CFG_PROTECTION_TYPE, 0x00000000);
	ar5523_config(ar, CFG_MODE_CTS, 0x00000002);

	error = ar5523_cmd_पढ़ो(ar, WDCMSG_TARGET_START, शून्य, 0,
	    &val, माप(val), AR5523_CMD_FLAG_MAGIC);
	अगर (error) अणु
		ar5523_dbg(ar, "could not start target, error %d\n", error);
		जाओ err;
	पूर्ण
	ar5523_dbg(ar, "WDCMSG_TARGET_START returns handle: 0x%x\n",
		   be32_to_cpu(val));

	ar5523_चयन_chan(ar);

	val = cpu_to_be32(TARGET_DEVICE_AWAKE);
	ar5523_cmd_ग_लिखो(ar, WDCMSG_SET_PWR_MODE, &val, माप(val), 0);
	/* XXX? check */
	ar5523_cmd_ग_लिखो(ar, WDCMSG_RESET_KEY_CACHE, शून्य, 0, 0);

	set_bit(AR5523_HW_UP, &ar->flags);
	queue_work(ar->wq, &ar->rx_refill_work);

	/* enable Rx */
	ar5523_set_rxfilter(ar, 0, UATH_FILTER_OP_INIT);
	ar5523_set_rxfilter(ar,
			    UATH_FILTER_RX_UCAST | UATH_FILTER_RX_MCAST |
			    UATH_FILTER_RX_BCAST | UATH_FILTER_RX_BEACON,
			    UATH_FILTER_OP_SET);

	ar5523_set_ledsteady(ar, UATH_LED_ACTIVITY, UATH_LED_ON);
	ar5523_dbg(ar, "start OK\n");

err:
	mutex_unlock(&ar->mutex);
	वापस error;
पूर्ण

अटल व्योम ar5523_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ar5523 *ar = hw->priv;

	ar5523_dbg(ar, "stop called\n");

	cancel_delayed_work_sync(&ar->stat_work);
	mutex_lock(&ar->mutex);
	clear_bit(AR5523_HW_UP, &ar->flags);

	ar5523_set_ledsteady(ar, UATH_LED_LINK, UATH_LED_OFF);
	ar5523_set_ledsteady(ar, UATH_LED_ACTIVITY, UATH_LED_OFF);

	ar5523_cmd_ग_लिखो(ar, WDCMSG_TARGET_STOP, शून्य, 0, 0);

	del_समयr_sync(&ar->tx_wd_समयr);
	cancel_work_sync(&ar->tx_wd_work);
	cancel_work_sync(&ar->rx_refill_work);
	ar5523_cancel_rx_bufs(ar);
	mutex_unlock(&ar->mutex);
पूर्ण

अटल पूर्णांक ar5523_set_rts_threshold(काष्ठा ieee80211_hw *hw, u32 value)
अणु
	काष्ठा ar5523 *ar = hw->priv;
	पूर्णांक ret;

	ar5523_dbg(ar, "set_rts_threshold called\n");
	mutex_lock(&ar->mutex);

	ret = ar5523_config(ar, CFG_USER_RTS_THRESHOLD, value);

	mutex_unlock(&ar->mutex);
	वापस ret;
पूर्ण

अटल व्योम ar5523_flush(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			 u32 queues, bool drop)
अणु
	काष्ठा ar5523 *ar = hw->priv;

	ar5523_dbg(ar, "flush called\n");
	ar5523_flush_tx(ar);
पूर्ण

अटल पूर्णांक ar5523_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ar5523 *ar = hw->priv;

	ar5523_dbg(ar, "add interface called\n");

	अगर (ar->vअगर) अणु
		ar5523_dbg(ar, "invalid add_interface\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_STATION:
		ar->vअगर = vअगर;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ar5523_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ar5523 *ar = hw->priv;

	ar5523_dbg(ar, "remove interface called\n");
	ar->vअगर = शून्य;
पूर्ण

अटल पूर्णांक ar5523_hwconfig(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	काष्ठा ar5523 *ar = hw->priv;

	ar5523_dbg(ar, "config called\n");
	mutex_lock(&ar->mutex);
	अगर (changed & IEEE80211_CONF_CHANGE_CHANNEL) अणु
		ar5523_dbg(ar, "Do channel switch\n");
		ar5523_flush_tx(ar);
		ar5523_चयन_chan(ar);
	पूर्ण
	mutex_unlock(&ar->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक ar5523_get_wlan_mode(काष्ठा ar5523 *ar,
				काष्ठा ieee80211_bss_conf *bss_conf)
अणु
	काष्ठा ieee80211_supported_band *band;
	पूर्णांक bit;
	काष्ठा ieee80211_sta *sta;
	u32 sta_rate_set;

	band = ar->hw->wiphy->bands[ar->hw->conf.chandef.chan->band];
	sta = ieee80211_find_sta(ar->vअगर, bss_conf->bssid);
	अगर (!sta) अणु
		ar5523_info(ar, "STA not found!\n");
		वापस WLAN_MODE_11b;
	पूर्ण
	sta_rate_set = sta->supp_rates[ar->hw->conf.chandef.chan->band];

	क्रम (bit = 0; bit < band->n_bitrates; bit++) अणु
		अगर (sta_rate_set & 1) अणु
			पूर्णांक rate = band->bitrates[bit].bitrate;
			चयन (rate) अणु
			हाल 60:
			हाल 90:
			हाल 120:
			हाल 180:
			हाल 240:
			हाल 360:
			हाल 480:
			हाल 540:
				वापस WLAN_MODE_11g;
			पूर्ण
		पूर्ण
		sta_rate_set >>= 1;
	पूर्ण
	वापस WLAN_MODE_11b;
पूर्ण

अटल व्योम ar5523_create_rateset(काष्ठा ar5523 *ar,
				  काष्ठा ieee80211_bss_conf *bss_conf,
				  काष्ठा ar5523_cmd_rateset *rs,
				  bool basic)
अणु
	काष्ठा ieee80211_supported_band *band;
	काष्ठा ieee80211_sta *sta;
	पूर्णांक bit, i = 0;
	u32 sta_rate_set, basic_rate_set;

	sta = ieee80211_find_sta(ar->vअगर, bss_conf->bssid);
	basic_rate_set = bss_conf->basic_rates;
	अगर (!sta) अणु
		ar5523_info(ar, "STA not found. Cannot set rates\n");
		sta_rate_set = bss_conf->basic_rates;
	पूर्ण अन्यथा
		sta_rate_set = sta->supp_rates[ar->hw->conf.chandef.chan->band];

	ar5523_dbg(ar, "sta rate_set = %08x\n", sta_rate_set);

	band = ar->hw->wiphy->bands[ar->hw->conf.chandef.chan->band];
	क्रम (bit = 0; bit < band->n_bitrates; bit++) अणु
		BUG_ON(i >= AR5523_MAX_NRATES);
		ar5523_dbg(ar, "Considering rate %d : %d\n",
			   band->bitrates[bit].hw_value, sta_rate_set & 1);
		अगर (sta_rate_set & 1) अणु
			rs->set[i] = band->bitrates[bit].hw_value;
			अगर (basic_rate_set & 1 && basic)
				rs->set[i] |= 0x80;
			i++;
		पूर्ण
		sta_rate_set >>= 1;
		basic_rate_set >>= 1;
	पूर्ण

	rs->length = i;
पूर्ण

अटल पूर्णांक ar5523_set_basic_rates(काष्ठा ar5523 *ar,
				  काष्ठा ieee80211_bss_conf *bss)
अणु
	काष्ठा ar5523_cmd_rates rates;

	स_रखो(&rates, 0, माप(rates));
	rates.connid = cpu_to_be32(2);		/* XXX */
	rates.size   = cpu_to_be32(माप(काष्ठा ar5523_cmd_rateset));
	ar5523_create_rateset(ar, bss, &rates.rateset, true);

	वापस ar5523_cmd_ग_लिखो(ar, WDCMSG_SET_BASIC_RATE, &rates,
				माप(rates), 0);
पूर्ण

अटल पूर्णांक ar5523_create_connection(काष्ठा ar5523 *ar,
				    काष्ठा ieee80211_vअगर *vअगर,
				    काष्ठा ieee80211_bss_conf *bss)
अणु
	काष्ठा ar5523_cmd_create_connection create;
	पूर्णांक wlan_mode;

	स_रखो(&create, 0, माप(create));
	create.connid = cpu_to_be32(2);
	create.bssid = cpu_to_be32(0);
	/* XXX packed or not?  */
	create.size = cpu_to_be32(माप(काष्ठा ar5523_cmd_rateset));

	ar5523_create_rateset(ar, bss, &create.connattr.rateset, false);

	wlan_mode = ar5523_get_wlan_mode(ar, bss);
	create.connattr.wlanmode = cpu_to_be32(wlan_mode);

	वापस ar5523_cmd_ग_लिखो(ar, WDCMSG_CREATE_CONNECTION, &create,
				माप(create), 0);
पूर्ण

अटल पूर्णांक ar5523_ग_लिखो_associd(काष्ठा ar5523 *ar,
				काष्ठा ieee80211_bss_conf *bss)
अणु
	काष्ठा ar5523_cmd_set_associd associd;

	स_रखो(&associd, 0, माप(associd));
	associd.शेषrateix = cpu_to_be32(0);	/* XXX */
	associd.associd = cpu_to_be32(bss->aid);
	associd.timoffset = cpu_to_be32(0x3b);	/* XXX */
	स_नकल(associd.bssid, bss->bssid, ETH_ALEN);
	वापस ar5523_cmd_ग_लिखो(ar, WDCMSG_WRITE_ASSOCID, &associd,
				माप(associd), 0);
पूर्ण

अटल व्योम ar5523_bss_info_changed(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर,
				    काष्ठा ieee80211_bss_conf *bss,
				    u32 changed)
अणु
	काष्ठा ar5523 *ar = hw->priv;
	पूर्णांक error;

	ar5523_dbg(ar, "bss_info_changed called\n");
	mutex_lock(&ar->mutex);

	अगर (!(changed & BSS_CHANGED_ASSOC))
		जाओ out_unlock;

	अगर (bss->assoc) अणु
		error = ar5523_create_connection(ar, vअगर, bss);
		अगर (error) अणु
			ar5523_err(ar, "could not create connection\n");
			जाओ out_unlock;
		पूर्ण

		error = ar5523_set_basic_rates(ar, bss);
		अगर (error) अणु
			ar5523_err(ar, "could not set negotiated rate set\n");
			जाओ out_unlock;
		पूर्ण

		error = ar5523_ग_लिखो_associd(ar, bss);
		अगर (error) अणु
			ar5523_err(ar, "could not set association\n");
			जाओ out_unlock;
		पूर्ण

		/* turn link LED on */
		ar5523_set_ledsteady(ar, UATH_LED_LINK, UATH_LED_ON);
		set_bit(AR5523_CONNECTED, &ar->flags);
		ieee80211_queue_delayed_work(hw, &ar->stat_work, HZ);

	पूर्ण अन्यथा अणु
		cancel_delayed_work(&ar->stat_work);
		clear_bit(AR5523_CONNECTED, &ar->flags);
		ar5523_set_ledsteady(ar, UATH_LED_LINK, UATH_LED_OFF);
	पूर्ण

out_unlock:
	mutex_unlock(&ar->mutex);

पूर्ण

#घोषणा AR5523_SUPPORTED_FILTERS (FIF_ALLMULTI | \
				  FIF_FCSFAIL | \
				  FIF_OTHER_BSS)

अटल व्योम ar5523_configure_filter(काष्ठा ieee80211_hw *hw,
				    अचिन्हित पूर्णांक changed_flags,
				    अचिन्हित पूर्णांक *total_flags,
				    u64 multicast)
अणु
	काष्ठा ar5523 *ar = hw->priv;
	u32 filter = 0;

	ar5523_dbg(ar, "configure_filter called\n");
	mutex_lock(&ar->mutex);
	ar5523_flush_tx(ar);

	*total_flags &= AR5523_SUPPORTED_FILTERS;

	/* The filters seems strange. UATH_FILTER_RX_BCAST and
	 * UATH_FILTER_RX_MCAST करोes not result in those frames being RXed.
	 * The only way I have found to get [mb]cast frames seems to be
	 * to set UATH_FILTER_RX_PROM. */
	filter |= UATH_FILTER_RX_UCAST | UATH_FILTER_RX_MCAST |
		  UATH_FILTER_RX_BCAST | UATH_FILTER_RX_BEACON |
		  UATH_FILTER_RX_PROM;

	ar5523_set_rxfilter(ar, 0, UATH_FILTER_OP_INIT);
	ar5523_set_rxfilter(ar, filter, UATH_FILTER_OP_SET);

	mutex_unlock(&ar->mutex);
पूर्ण

अटल स्थिर काष्ठा ieee80211_ops ar5523_ops = अणु
	.start			= ar5523_start,
	.stop			= ar5523_stop,
	.tx			= ar5523_tx,
	.set_rts_threshold	= ar5523_set_rts_threshold,
	.add_पूर्णांकerface		= ar5523_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface	= ar5523_हटाओ_पूर्णांकerface,
	.config			= ar5523_hwconfig,
	.bss_info_changed	= ar5523_bss_info_changed,
	.configure_filter	= ar5523_configure_filter,
	.flush			= ar5523_flush,
पूर्ण;

अटल पूर्णांक ar5523_host_available(काष्ठा ar5523 *ar)
अणु
	काष्ठा ar5523_cmd_host_available setup;

	/* inक्रमm target the host is available */
	setup.sw_ver_major = cpu_to_be32(ATH_SW_VER_MAJOR);
	setup.sw_ver_minor = cpu_to_be32(ATH_SW_VER_MINOR);
	setup.sw_ver_patch = cpu_to_be32(ATH_SW_VER_PATCH);
	setup.sw_ver_build = cpu_to_be32(ATH_SW_VER_BUILD);
	वापस ar5523_cmd_पढ़ो(ar, WDCMSG_HOST_AVAILABLE,
			       &setup, माप(setup), शून्य, 0, 0);
पूर्ण

अटल पूर्णांक ar5523_get_devstatus(काष्ठा ar5523 *ar)
अणु
	u8 macaddr[ETH_ALEN];
	पूर्णांक error;

	/* retrieve MAC address */
	error = ar5523_get_status(ar, ST_MAC_ADDR, macaddr, ETH_ALEN);
	अगर (error) अणु
		ar5523_err(ar, "could not read MAC address\n");
		वापस error;
	पूर्ण

	SET_IEEE80211_PERM_ADDR(ar->hw, macaddr);

	error = ar5523_get_status(ar, ST_SERIAL_NUMBER,
	    &ar->serial[0], माप(ar->serial));
	अगर (error) अणु
		ar5523_err(ar, "could not read device serial number\n");
		वापस error;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा AR5523_SANE_RXBUFSZ 2000

अटल पूर्णांक ar5523_get_max_rxsz(काष्ठा ar5523 *ar)
अणु
	पूर्णांक error;
	__be32 rxsize;

	/* Get max rx size */
	error = ar5523_get_status(ar, ST_WDC_TRANSPORT_CHUNK_SIZE, &rxsize,
				  माप(rxsize));
	अगर (error != 0) अणु
		ar5523_err(ar, "could not read max RX size\n");
		वापस error;
	पूर्ण

	ar->rxbufsz = be32_to_cpu(rxsize);

	अगर (!ar->rxbufsz || ar->rxbufsz > AR5523_SANE_RXBUFSZ) अणु
		ar5523_err(ar, "Bad rxbufsz from device. Using %d instead\n",
			   AR5523_SANE_RXBUFSZ);
		ar->rxbufsz = AR5523_SANE_RXBUFSZ;
	पूर्ण

	ar5523_dbg(ar, "Max RX buf size: %d\n", ar->rxbufsz);
	वापस 0;
पूर्ण

/*
 * This is copied from rtl818x, but we should probably move this
 * to common code as in OpenBSD.
 */
अटल स्थिर काष्ठा ieee80211_rate ar5523_rates[] = अणु
	अणु .bitrate = 10, .hw_value = 2, पूर्ण,
	अणु .bitrate = 20, .hw_value = 4 पूर्ण,
	अणु .bitrate = 55, .hw_value = 11, पूर्ण,
	अणु .bitrate = 110, .hw_value = 22, पूर्ण,
	अणु .bitrate = 60, .hw_value = 12, पूर्ण,
	अणु .bitrate = 90, .hw_value = 18, पूर्ण,
	अणु .bitrate = 120, .hw_value = 24, पूर्ण,
	अणु .bitrate = 180, .hw_value = 36, पूर्ण,
	अणु .bitrate = 240, .hw_value = 48, पूर्ण,
	अणु .bitrate = 360, .hw_value = 72, पूर्ण,
	अणु .bitrate = 480, .hw_value = 96, पूर्ण,
	अणु .bitrate = 540, .hw_value = 108, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_channel ar5523_channels[] = अणु
	अणु .center_freq = 2412 पूर्ण,
	अणु .center_freq = 2417 पूर्ण,
	अणु .center_freq = 2422 पूर्ण,
	अणु .center_freq = 2427 पूर्ण,
	अणु .center_freq = 2432 पूर्ण,
	अणु .center_freq = 2437 पूर्ण,
	अणु .center_freq = 2442 पूर्ण,
	अणु .center_freq = 2447 पूर्ण,
	अणु .center_freq = 2452 पूर्ण,
	अणु .center_freq = 2457 पूर्ण,
	अणु .center_freq = 2462 पूर्ण,
	अणु .center_freq = 2467 पूर्ण,
	अणु .center_freq = 2472 पूर्ण,
	अणु .center_freq = 2484 पूर्ण,
पूर्ण;

अटल पूर्णांक ar5523_init_modes(काष्ठा ar5523 *ar)
अणु
	BUILD_BUG_ON(माप(ar->channels) != माप(ar5523_channels));
	BUILD_BUG_ON(माप(ar->rates) != माप(ar5523_rates));

	स_नकल(ar->channels, ar5523_channels, माप(ar5523_channels));
	स_नकल(ar->rates, ar5523_rates, माप(ar5523_rates));

	ar->band.band = NL80211_BAND_2GHZ;
	ar->band.channels = ar->channels;
	ar->band.n_channels = ARRAY_SIZE(ar5523_channels);
	ar->band.bitrates = ar->rates;
	ar->band.n_bitrates = ARRAY_SIZE(ar5523_rates);
	ar->hw->wiphy->bands[NL80211_BAND_2GHZ] = &ar->band;
	वापस 0;
पूर्ण

/*
 * Load the MIPS R4000 microcode पूर्णांकo the device.  Once the image is loaded,
 * the device will detach itself from the bus and reattach later with a new
 * product Id (a la ezusb).
 */
अटल पूर्णांक ar5523_load_firmware(काष्ठा usb_device *dev)
अणु
	काष्ठा ar5523_fwblock *txblock, *rxblock;
	स्थिर काष्ठा firmware *fw;
	व्योम *fwbuf;
	पूर्णांक len, offset;
	पूर्णांक foolen; /* XXX(hch): handle लघु transfers */
	पूर्णांक error = -ENXIO;

	अगर (request_firmware(&fw, AR5523_FIRMWARE_खाता, &dev->dev)) अणु
		dev_err(&dev->dev, "no firmware found: %s\n",
			AR5523_FIRMWARE_खाता);
		वापस -ENOENT;
	पूर्ण

	txblock = kदो_स्मृति(माप(*txblock), GFP_KERNEL);
	अगर (!txblock)
		जाओ out;

	rxblock = kदो_स्मृति(माप(*rxblock), GFP_KERNEL);
	अगर (!rxblock)
		जाओ out_मुक्त_txblock;

	fwbuf = kदो_स्मृति(AR5523_MAX_FWBLOCK_SIZE, GFP_KERNEL);
	अगर (!fwbuf)
		जाओ out_मुक्त_rxblock;

	स_रखो(txblock, 0, माप(काष्ठा ar5523_fwblock));
	txblock->flags = cpu_to_be32(AR5523_WRITE_BLOCK);
	txblock->total = cpu_to_be32(fw->size);

	offset = 0;
	len = fw->size;
	जबतक (len > 0) अणु
		पूर्णांक mlen = min(len, AR5523_MAX_FWBLOCK_SIZE);

		txblock->reमुख्य = cpu_to_be32(len - mlen);
		txblock->len = cpu_to_be32(mlen);

		/* send firmware block meta-data */
		error = usb_bulk_msg(dev, ar5523_cmd_tx_pipe(dev),
				     txblock, माप(*txblock), &foolen,
				     AR5523_CMD_TIMEOUT);
		अगर (error) अणु
			dev_err(&dev->dev,
				"could not send firmware block info\n");
			जाओ out_मुक्त_fwbuf;
		पूर्ण

		/* send firmware block data */
		स_नकल(fwbuf, fw->data + offset, mlen);
		error = usb_bulk_msg(dev, ar5523_data_tx_pipe(dev),
				     fwbuf, mlen, &foolen,
				     AR5523_DATA_TIMEOUT);
		अगर (error) अणु
			dev_err(&dev->dev,
				"could not send firmware block data\n");
			जाओ out_मुक्त_fwbuf;
		पूर्ण

		/* रुको क्रम ack from firmware */
		error = usb_bulk_msg(dev, ar5523_cmd_rx_pipe(dev),
				     rxblock, माप(*rxblock), &foolen,
				     AR5523_CMD_TIMEOUT);
		अगर (error) अणु
			dev_err(&dev->dev,
				"could not read firmware answer\n");
			जाओ out_मुक्त_fwbuf;
		पूर्ण

		len -= mlen;
		offset += mlen;
	पूर्ण

	/*
	 * Set the error to -ENXIO to make sure we जारी probing क्रम
	 * a driver.
	 */
	error = -ENXIO;

 out_मुक्त_fwbuf:
	kमुक्त(fwbuf);
 out_मुक्त_rxblock:
	kमुक्त(rxblock);
 out_मुक्त_txblock:
	kमुक्त(txblock);
 out:
	release_firmware(fw);
	वापस error;
पूर्ण

अटल पूर्णांक ar5523_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा ieee80211_hw *hw;
	काष्ठा ar5523 *ar;
	पूर्णांक error = -ENOMEM;

	/*
	 * Load firmware अगर the device requires it.  This will वापस
	 * -ENXIO on success and we'll get called back afer the usb
	 * id changes to indicate that the firmware is present.
	 */
	अगर (id->driver_info & AR5523_FLAG_PRE_FIRMWARE)
		वापस ar5523_load_firmware(dev);


	hw = ieee80211_alloc_hw(माप(*ar), &ar5523_ops);
	अगर (!hw)
		जाओ out;
	SET_IEEE80211_DEV(hw, &पूर्णांकf->dev);

	ar = hw->priv;
	ar->hw = hw;
	ar->dev = dev;
	mutex_init(&ar->mutex);

	INIT_DELAYED_WORK(&ar->stat_work, ar5523_stat_work);
	समयr_setup(&ar->tx_wd_समयr, ar5523_tx_wd_समयr, 0);
	INIT_WORK(&ar->tx_wd_work, ar5523_tx_wd_work);
	INIT_WORK(&ar->tx_work, ar5523_tx_work);
	INIT_LIST_HEAD(&ar->tx_queue_pending);
	INIT_LIST_HEAD(&ar->tx_queue_submitted);
	spin_lock_init(&ar->tx_data_list_lock);
	atomic_set(&ar->tx_nr_total, 0);
	atomic_set(&ar->tx_nr_pending, 0);
	init_रुकोqueue_head(&ar->tx_flush_रुकोq);

	atomic_set(&ar->rx_data_मुक्त_cnt, 0);
	INIT_WORK(&ar->rx_refill_work, ar5523_rx_refill_work);
	INIT_LIST_HEAD(&ar->rx_data_मुक्त);
	INIT_LIST_HEAD(&ar->rx_data_used);
	spin_lock_init(&ar->rx_data_list_lock);

	ar->wq = create_singlethपढ़ो_workqueue("ar5523");
	अगर (!ar->wq) अणु
		ar5523_err(ar, "Could not create wq\n");
		जाओ out_मुक्त_ar;
	पूर्ण

	error = ar5523_alloc_rx_bufs(ar);
	अगर (error) अणु
		ar5523_err(ar, "Could not allocate rx buffers\n");
		जाओ out_मुक्त_wq;
	पूर्ण

	error = ar5523_alloc_rx_cmd(ar);
	अगर (error) अणु
		ar5523_err(ar, "Could not allocate rx command buffers\n");
		जाओ out_मुक्त_rx_bufs;
	पूर्ण

	error = ar5523_alloc_tx_cmd(ar);
	अगर (error) अणु
		ar5523_err(ar, "Could not allocate tx command buffers\n");
		जाओ out_मुक्त_rx_cmd;
	पूर्ण

	error = ar5523_submit_rx_cmd(ar);
	अगर (error) अणु
		ar5523_err(ar, "Failed to submit rx cmd\n");
		जाओ out_मुक्त_tx_cmd;
	पूर्ण

	/*
	 * We're now पढ़ोy to send/receive firmware commands.
	 */
	error = ar5523_host_available(ar);
	अगर (error) अणु
		ar5523_err(ar, "could not initialize adapter\n");
		जाओ out_cancel_rx_cmd;
	पूर्ण

	error = ar5523_get_max_rxsz(ar);
	अगर (error) अणु
		ar5523_err(ar, "could not get caps from adapter\n");
		जाओ out_cancel_rx_cmd;
	पूर्ण

	error = ar5523_get_devcap(ar);
	अगर (error) अणु
		ar5523_err(ar, "could not get caps from adapter\n");
		जाओ out_cancel_rx_cmd;
	पूर्ण

	error = ar5523_get_devstatus(ar);
	अगर (error != 0) अणु
		ar5523_err(ar, "could not get device status\n");
		जाओ out_cancel_rx_cmd;
	पूर्ण

	ar5523_info(ar, "MAC/BBP AR5523, RF AR%c112\n",
			(id->driver_info & AR5523_FLAG_ABG) ? '5' : '2');

	ar->vअगर = शून्य;
	ieee80211_hw_set(hw, HAS_RATE_CONTROL);
	ieee80211_hw_set(hw, RX_INCLUDES_FCS);
	ieee80211_hw_set(hw, SIGNAL_DBM);
	hw->extra_tx_headroom = माप(काष्ठा ar5523_tx_desc) +
				माप(काष्ठा ar5523_chunk);
	hw->wiphy->पूर्णांकerface_modes = BIT(NL80211_IFTYPE_STATION);
	hw->queues = 1;

	error = ar5523_init_modes(ar);
	अगर (error)
		जाओ out_cancel_rx_cmd;

	wiphy_ext_feature_set(hw->wiphy, NL80211_EXT_FEATURE_CQM_RSSI_LIST);

	usb_set_पूर्णांकfdata(पूर्णांकf, hw);

	error = ieee80211_रेजिस्टर_hw(hw);
	अगर (error) अणु
		ar5523_err(ar, "could not register device\n");
		जाओ out_cancel_rx_cmd;
	पूर्ण

	ar5523_info(ar, "Found and initialized AR5523 device\n");
	वापस 0;

out_cancel_rx_cmd:
	ar5523_cancel_rx_cmd(ar);
out_मुक्त_tx_cmd:
	ar5523_मुक्त_tx_cmd(ar);
out_मुक्त_rx_cmd:
	ar5523_मुक्त_rx_cmd(ar);
out_मुक्त_rx_bufs:
	ar5523_मुक्त_rx_bufs(ar);
out_मुक्त_wq:
	destroy_workqueue(ar->wq);
out_मुक्त_ar:
	ieee80211_मुक्त_hw(hw);
out:
	वापस error;
पूर्ण

अटल व्योम ar5523_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा ieee80211_hw *hw = usb_get_पूर्णांकfdata(पूर्णांकf);
	काष्ठा ar5523 *ar = hw->priv;

	ar5523_dbg(ar, "detaching\n");
	set_bit(AR5523_USB_DISCONNECTED, &ar->flags);

	ieee80211_unरेजिस्टर_hw(hw);

	ar5523_cancel_rx_cmd(ar);
	ar5523_मुक्त_tx_cmd(ar);
	ar5523_मुक्त_rx_cmd(ar);
	ar5523_मुक्त_rx_bufs(ar);

	destroy_workqueue(ar->wq);

	ieee80211_मुक्त_hw(hw);
	usb_set_पूर्णांकfdata(पूर्णांकf, शून्य);
पूर्ण

#घोषणा AR5523_DEVICE_UG(venकरोr, device) \
	अणु USB_DEVICE((venकरोr), (device)) पूर्ण, \
	अणु USB_DEVICE((venकरोr), (device) + 1), \
		.driver_info = AR5523_FLAG_PRE_FIRMWARE पूर्ण
#घोषणा AR5523_DEVICE_UX(venकरोr, device) \
	अणु USB_DEVICE((venकरोr), (device)), \
		.driver_info = AR5523_FLAG_ABG पूर्ण, \
	अणु USB_DEVICE((venकरोr), (device) + 1), \
		.driver_info = AR5523_FLAG_ABG|AR5523_FLAG_PRE_FIRMWARE पूर्ण

अटल स्थिर काष्ठा usb_device_id ar5523_id_table[] = अणु
	AR5523_DEVICE_UG(0x168c, 0x0001),	/* Atheros / AR5523 */
	AR5523_DEVICE_UG(0x0cf3, 0x0001),	/* Atheros2 / AR5523_1 */
	AR5523_DEVICE_UG(0x0cf3, 0x0003),	/* Atheros2 / AR5523_2 */
	AR5523_DEVICE_UX(0x0cf3, 0x0005),	/* Atheros2 / AR5523_3 */
	AR5523_DEVICE_UG(0x0d8e, 0x7801),	/* Conceptronic / AR5523_1 */
	AR5523_DEVICE_UX(0x0d8e, 0x7811),	/* Conceptronic / AR5523_2 */
	AR5523_DEVICE_UX(0x2001, 0x3a00),	/* Dlink / DWLAG132 */
	AR5523_DEVICE_UG(0x2001, 0x3a02),	/* Dlink / DWLG132 */
	AR5523_DEVICE_UX(0x2001, 0x3a04),	/* Dlink / DWLAG122 */
	AR5523_DEVICE_UG(0x07d1, 0x3a07),	/* D-Link / WUA-2340 rev A1 */
	AR5523_DEVICE_UG(0x1690, 0x0712),	/* Gigaset / AR5523 */
	AR5523_DEVICE_UG(0x1690, 0x0710),	/* Gigaset / SMCWUSBTG */
	AR5523_DEVICE_UG(0x129b, 0x160b),	/* Gigaset / USB stick 108
						   (CyberTAN Technology) */
	AR5523_DEVICE_UG(0x16ab, 0x7801),	/* Globalsun / AR5523_1 */
	AR5523_DEVICE_UX(0x16ab, 0x7811),	/* Globalsun / AR5523_2 */
	AR5523_DEVICE_UG(0x0d8e, 0x7802),	/* Globalsun / AR5523_3 */
	AR5523_DEVICE_UX(0x0846, 0x4300),	/* Netgear / WG111U */
	AR5523_DEVICE_UG(0x0846, 0x4250),	/* Netgear / WG111T */
	AR5523_DEVICE_UG(0x0846, 0x5f00),	/* Netgear / WPN111 */
	AR5523_DEVICE_UG(0x083a, 0x4506),	/* SMC / EZ Connect
						   SMCWUSBT-G2 */
	AR5523_DEVICE_UG(0x157e, 0x3006),	/* Umedia / AR5523_1 */
	AR5523_DEVICE_UX(0x157e, 0x3205),	/* Umedia / AR5523_2 */
	AR5523_DEVICE_UG(0x157e, 0x3006),	/* Umedia / TEW444UBEU */
	AR5523_DEVICE_UG(0x1435, 0x0826),	/* Wistronneweb / AR5523_1 */
	AR5523_DEVICE_UX(0x1435, 0x0828),	/* Wistronneweb / AR5523_2 */
	AR5523_DEVICE_UG(0x0cde, 0x0012),	/* Zcom / AR5523 */
	AR5523_DEVICE_UG(0x1385, 0x4250),	/* Netgear3 / WG111T (2) */
	AR5523_DEVICE_UG(0x1385, 0x5f00),	/* Netgear / WPN111 */
	AR5523_DEVICE_UG(0x1385, 0x5f02),	/* Netgear / WPN111 */
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(usb, ar5523_id_table);

अटल काष्ठा usb_driver ar5523_driver = अणु
	.name		= "ar5523",
	.id_table	= ar5523_id_table,
	.probe		= ar5523_probe,
	.disconnect	= ar5523_disconnect,
पूर्ण;

module_usb_driver(ar5523_driver);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_FIRMWARE(AR5523_FIRMWARE_खाता);
