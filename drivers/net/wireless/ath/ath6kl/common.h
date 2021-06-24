<शैली गुरु>
/*
 * Copyright (c) 2010-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2012 Qualcomm Atheros, Inc.
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

#अगर_अघोषित COMMON_H
#घोषणा COMMON_H

#समावेश <linux/netdevice.h>

#घोषणा ATH6KL_MAX_IE			256

__म_लिखो(2, 3) व्योम ath6kl_prपूर्णांकk(स्थिर अक्षर *level, स्थिर अक्षर *fmt, ...);

/*
 * Reflects the version of binary पूर्णांकerface exposed by ATH6KL target
 * firmware. Needs to be incremented by 1 क्रम any change in the firmware
 * that requires upgrade of the driver on the host side क्रम the change to
 * work correctly
 */
#घोषणा ATH6KL_ABI_VERSION        1

#घोषणा SIGNAL_QUALITY_METRICS_NUM_MAX    2

क्रमागत अणु
	SIGNAL_QUALITY_METRICS_SNR = 0,
	SIGNAL_QUALITY_METRICS_RSSI,
	SIGNAL_QUALITY_METRICS_ALL,
पूर्ण;

/*
 * Data Path
 */

#घोषणा WMI_MAX_TX_DATA_FRAME_LENGTH	      \
	(1500 + माप(काष्ठा wmi_data_hdr) + \
	 माप(काष्ठा ethhdr) +      \
	 माप(काष्ठा ath6kl_llc_snap_hdr))

/* An AMSDU frame */ /* The MAX AMSDU length of AR6003 is 3839 */
#घोषणा WMI_MAX_AMSDU_RX_DATA_FRAME_LENGTH    \
	(3840 + माप(काष्ठा wmi_data_hdr) + \
	 माप(काष्ठा ethhdr) +      \
	 माप(काष्ठा ath6kl_llc_snap_hdr))

#घोषणा EPPING_ALIGNMENT_PAD			       \
	(((माप(काष्ठा htc_frame_hdr) + 3) & (~0x3)) \
	 - माप(काष्ठा htc_frame_hdr))

काष्ठा ath6kl_llc_snap_hdr अणु
	u8 dsap;
	u8 ssap;
	u8 cntl;
	u8 org_code[3];
	__be16 eth_type;
पूर्ण __packed;

क्रमागत ath6kl_crypto_type अणु
	NONE_CRYPT          = 0x01,
	WEP_CRYPT           = 0x02,
	TKIP_CRYPT          = 0x04,
	AES_CRYPT           = 0x08,
	WAPI_CRYPT          = 0x10,
पूर्ण;

काष्ठा htc_endpoपूर्णांक_credit_dist;
काष्ठा ath6kl;
काष्ठा ath6kl_htcap;
क्रमागत htc_credit_dist_reason;
काष्ठा ath6kl_htc_credit_info;

काष्ठा sk_buff *ath6kl_buf_alloc(पूर्णांक size);
#पूर्ण_अगर /* COMMON_H */
