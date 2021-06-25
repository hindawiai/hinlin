<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-2-Clause)
/*
 * Copyright (C) ST-Ericsson 2010-2012
 * Contact: Alexey Orishko <alexey.orishko@stericsson.com>
 * Original author: Hans Petter Selasky <hans.petter.selasky@stericsson.com>
 *
 * USB Host Driver क्रम Network Control Model (NCM)
 * http://www.usb.org/developers/devclass_करोcs/NCM10.zip
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

#अगर_अघोषित __LINUX_USB_CDC_NCM_H
#घोषणा __LINUX_USB_CDC_NCM_H

#घोषणा CDC_NCM_COMM_ALTSETTING_NCM		0
#घोषणा CDC_NCM_COMM_ALTSETTING_MBIM		1

#घोषणा CDC_NCM_DATA_ALTSETTING_NCM		1
#घोषणा CDC_NCM_DATA_ALTSETTING_MBIM		2

/* CDC NCM subclass 3.3.1 */
#घोषणा USB_CDC_NCM_NDP16_LENGTH_MIN		0x10

/* CDC NCM subclass 3.3.2 */
#घोषणा USB_CDC_NCM_NDP32_LENGTH_MIN		0x20

/* Maximum NTB length */
#घोषणा	CDC_NCM_NTB_MAX_SIZE_TX			32768	/* bytes */
#घोषणा	CDC_NCM_NTB_MAX_SIZE_RX			32768	/* bytes */

/* Initial NTB length */
#घोषणा	CDC_NCM_NTB_DEF_SIZE_TX			16384	/* bytes */
#घोषणा	CDC_NCM_NTB_DEF_SIZE_RX			16384	/* bytes */

/* Minimum value क्रम MaxDatagramSize, ch. 6.2.9 */
#घोषणा	CDC_NCM_MIN_DATAGRAM_SIZE		1514	/* bytes */

/* Minimum value क्रम MaxDatagramSize, ch. 8.1.3 */
#घोषणा CDC_MBIM_MIN_DATAGRAM_SIZE		2048	/* bytes */

#घोषणा	CDC_NCM_MIN_TX_PKT			512	/* bytes */

/* Default value क्रम MaxDatagramSize */
#घोषणा	CDC_NCM_MAX_DATAGRAM_SIZE		8192	/* bytes */

/*
 * Maximum amount of datagrams in NCM Datagram Poपूर्णांकer Table, not counting
 * the last शून्य entry.
 */
#घोषणा	CDC_NCM_DPT_DATAGRAMS_MAX		40

/* Restart the समयr, अगर amount of datagrams is less than given value */
#घोषणा	CDC_NCM_RESTART_TIMER_DATAGRAM_CNT	3
#घोषणा	CDC_NCM_TIMER_PENDING_CNT		2
#घोषणा CDC_NCM_TIMER_INTERVAL_USEC		400UL
#घोषणा CDC_NCM_TIMER_INTERVAL_MIN		5UL
#घोषणा CDC_NCM_TIMER_INTERVAL_MAX		(U32_MAX / NSEC_PER_USEC)

/* Driver flags */
#घोषणा CDC_NCM_FLAG_NDP_TO_END			0x02	/* NDP is placed at end of frame */
#घोषणा CDC_MBIM_FLAG_AVOID_ALTSETTING_TOGGLE	0x04	/* Aव्योम altsetting toggle during init */
#घोषणा CDC_NCM_FLAG_PREFER_NTB32 0x08	/* prefer NDP32 over NDP16 */

#घोषणा cdc_ncm_comm_पूर्णांकf_is_mbim(x)  ((x)->desc.bInterfaceSubClass == USB_CDC_SUBCLASS_MBIM && \
				       (x)->desc.bInterfaceProtocol == USB_CDC_PROTO_NONE)
#घोषणा cdc_ncm_data_पूर्णांकf_is_mbim(x)  ((x)->desc.bInterfaceProtocol == USB_CDC_MBIM_PROTO_NTB)

काष्ठा cdc_ncm_ctx अणु
	काष्ठा usb_cdc_ncm_ntb_parameters ncm_parm;
	काष्ठा hrसमयr tx_समयr;
	काष्ठा tasklet_काष्ठा bh;

	काष्ठा usbnet *dev;

	स्थिर काष्ठा usb_cdc_ncm_desc *func_desc;
	स्थिर काष्ठा usb_cdc_mbim_desc *mbim_desc;
	स्थिर काष्ठा usb_cdc_mbim_extended_desc *mbim_extended_desc;
	स्थिर काष्ठा usb_cdc_ether_desc *ether_desc;

	काष्ठा usb_पूर्णांकerface *control;
	काष्ठा usb_पूर्णांकerface *data;

	काष्ठा sk_buff *tx_curr_skb;
	काष्ठा sk_buff *tx_rem_skb;
	__le32 tx_rem_sign;

	spinlock_t mtx;
	atomic_t stop;
	पूर्णांक drvflags;

	u32 समयr_पूर्णांकerval;
	u32 max_ndp_size;
	u8 is_ndp16;
	जोड़ अणु
		काष्ठा usb_cdc_ncm_ndp16 *delayed_ndp16;
		काष्ठा usb_cdc_ncm_ndp32 *delayed_ndp32;
	पूर्ण;

	u32 tx_समयr_pending;
	u32 tx_curr_frame_num;
	u32 rx_max;
	u32 tx_max;
	u32 tx_curr_size;
	u32 tx_low_mem_max_cnt;
	u32 tx_low_mem_val;
	u32 max_datagram_size;
	u16 tx_max_datagrams;
	u16 tx_reमुख्यder;
	u16 tx_modulus;
	u16 tx_ndp_modulus;
	u16 tx_seq;
	u16 rx_seq;
	u16 min_tx_pkt;

	/* statistics */
	u32 tx_curr_frame_payload;
	u32 tx_reason_ntb_full;
	u32 tx_reason_ndp_full;
	u32 tx_reason_समयout;
	u32 tx_reason_max_datagram;
	u64 tx_overhead;
	u64 tx_ntbs;
	u64 rx_overhead;
	u64 rx_ntbs;
पूर्ण;

u8 cdc_ncm_select_altsetting(काष्ठा usb_पूर्णांकerface *पूर्णांकf);
पूर्णांक cdc_ncm_change_mtu(काष्ठा net_device *net, पूर्णांक new_mtu);
पूर्णांक cdc_ncm_bind_common(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf, u8 data_altsetting, पूर्णांक drvflags);
व्योम cdc_ncm_unbind(काष्ठा usbnet *dev, काष्ठा usb_पूर्णांकerface *पूर्णांकf);
काष्ठा sk_buff *cdc_ncm_fill_tx_frame(काष्ठा usbnet *dev, काष्ठा sk_buff *skb, __le32 sign);
पूर्णांक cdc_ncm_rx_verअगरy_nth16(काष्ठा cdc_ncm_ctx *ctx, काष्ठा sk_buff *skb_in);
पूर्णांक cdc_ncm_rx_verअगरy_ndp16(काष्ठा sk_buff *skb_in, पूर्णांक ndpoffset);
पूर्णांक cdc_ncm_rx_verअगरy_nth32(काष्ठा cdc_ncm_ctx *ctx, काष्ठा sk_buff *skb_in);
पूर्णांक cdc_ncm_rx_verअगरy_ndp32(काष्ठा sk_buff *skb_in, पूर्णांक ndpoffset);
काष्ठा sk_buff *
cdc_ncm_tx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb, gfp_t flags);
पूर्णांक cdc_ncm_rx_fixup(काष्ठा usbnet *dev, काष्ठा sk_buff *skb_in);

#पूर्ण_अगर /* __LINUX_USB_CDC_NCM_H */
