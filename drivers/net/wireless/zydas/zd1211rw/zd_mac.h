<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* ZD1211 USB-WLAN driver क्रम Linux
 *
 * Copyright (C) 2005-2007 Ulrich Kunitz <kune@deine-taler.de>
 * Copyright (C) 2006-2007 Daniel Drake <dsd@gentoo.org>
 */

#अगर_अघोषित _ZD_MAC_H
#घोषणा _ZD_MAC_H

#समावेश <linux/kernel.h>
#समावेश <net/mac80211.h>

#समावेश "zd_chip.h"

काष्ठा zd_ctrlset अणु
	u8     modulation;
	__le16 tx_length;
	u8     control;
	/* stores only the dअगरference to tx_length on ZD1211B */
	__le16 packet_length;
	__le16 current_length;
	u8     service;
	__le16  next_frame_length;
पूर्ण __packed;

#घोषणा ZD_CS_RESERVED_SIZE	25

/* The field modulation of काष्ठा zd_ctrlset controls the bit rate, the use
 * of लघु or दीर्घ preambles in 802.11b (CCK mode) or the use of 802.11a or
 * 802.11g in OFDM mode.
 *
 * The term zd-rate is used क्रम the combination of the modulation type flag
 * and the "pure" rate value.
 */
#घोषणा ZD_PURE_RATE_MASK       0x0f
#घोषणा ZD_MODULATION_TYPE_MASK 0x10
#घोषणा ZD_RATE_MASK            (ZD_PURE_RATE_MASK|ZD_MODULATION_TYPE_MASK)
#घोषणा ZD_PURE_RATE(modulation) ((modulation) & ZD_PURE_RATE_MASK)
#घोषणा ZD_MODULATION_TYPE(modulation) ((modulation) & ZD_MODULATION_TYPE_MASK)
#घोषणा ZD_RATE(modulation) ((modulation) & ZD_RATE_MASK)

/* The two possible modulation types. Notअगरy that 802.11b करोesn't use the CCK
 * codeing क्रम the 1 and 2 MBit/s rate. We stay with the term here to reमुख्य
 * consistent with uses the term at other places.
 */
#घोषणा ZD_CCK                  0x00
#घोषणा ZD_OFDM                 0x10

/* The ZD1211 firmware uses proprietary encodings of the 802.11b (CCK) rates.
 * For OFDM the PLCP rate encodings are used. We combine these "pure" rates
 * with the modulation type flag and call the resulting values zd-rates.
 */
#घोषणा ZD_CCK_RATE_1M          (ZD_CCK|0x00)
#घोषणा ZD_CCK_RATE_2M          (ZD_CCK|0x01)
#घोषणा ZD_CCK_RATE_5_5M        (ZD_CCK|0x02)
#घोषणा ZD_CCK_RATE_11M         (ZD_CCK|0x03)
#घोषणा ZD_OFDM_RATE_6M         (ZD_OFDM|ZD_OFDM_PLCP_RATE_6M)
#घोषणा ZD_OFDM_RATE_9M         (ZD_OFDM|ZD_OFDM_PLCP_RATE_9M)
#घोषणा ZD_OFDM_RATE_12M        (ZD_OFDM|ZD_OFDM_PLCP_RATE_12M)
#घोषणा ZD_OFDM_RATE_18M        (ZD_OFDM|ZD_OFDM_PLCP_RATE_18M)
#घोषणा ZD_OFDM_RATE_24M        (ZD_OFDM|ZD_OFDM_PLCP_RATE_24M)
#घोषणा ZD_OFDM_RATE_36M        (ZD_OFDM|ZD_OFDM_PLCP_RATE_36M)
#घोषणा ZD_OFDM_RATE_48M        (ZD_OFDM|ZD_OFDM_PLCP_RATE_48M)
#घोषणा ZD_OFDM_RATE_54M        (ZD_OFDM|ZD_OFDM_PLCP_RATE_54M)

/* The bit 5 of the zd_ctrlset modulation field controls the preamble in CCK
 * mode or the 802.11a/802.11g selection in OFDM mode.
 */
#घोषणा ZD_CCK_PREA_LONG        0x00
#घोषणा ZD_CCK_PREA_SHORT       0x20
#घोषणा ZD_OFDM_MODE_11G        0x00
#घोषणा ZD_OFDM_MODE_11A        0x20

/* zd_ctrlset control field */
#घोषणा ZD_CS_NEED_RANDOM_BACKOFF	0x01
#घोषणा ZD_CS_NO_ACK			0x02

#घोषणा ZD_CS_FRAME_TYPE_MASK		0x0c
#घोषणा ZD_CS_DATA_FRAME		0x00
#घोषणा ZD_CS_PS_POLL_FRAME		0x04
#घोषणा ZD_CS_MANAGEMENT_FRAME		0x08
#घोषणा ZD_CS_NO_SEQUENCE_CTL_FRAME	0x0c

#घोषणा ZD_CS_WAKE_DESTINATION		0x10
#घोषणा ZD_CS_RTS			0x20
#घोषणा ZD_CS_ENCRYPT			0x40
#घोषणा ZD_CS_SELF_CTS			0x80

/* Incoming frames are prepended by a PLCP header */
#घोषणा ZD_PLCP_HEADER_SIZE		5

काष्ठा rx_length_info अणु
	__le16 length[3];
	__le16 tag;
पूर्ण __packed;

#घोषणा RX_LENGTH_INFO_TAG		0x697e

काष्ठा rx_status अणु
	u8 संकेत_quality_cck;
	/* rssi */
	u8 संकेत_strength;
	u8 संकेत_quality_ofdm;
	u8 decryption_type;
	u8 frame_status;
पूर्ण __packed;

/* rx_status field decryption_type */
#घोषणा ZD_RX_NO_WEP	0
#घोषणा ZD_RX_WEP64	1
#घोषणा ZD_RX_TKIP	2
#घोषणा ZD_RX_AES	4
#घोषणा ZD_RX_WEP128	5
#घोषणा ZD_RX_WEP256	6

/* rx_status field frame_status */
#घोषणा ZD_RX_FRAME_MODULATION_MASK	0x01
#घोषणा ZD_RX_CCK			0x00
#घोषणा ZD_RX_OFDM			0x01

#घोषणा ZD_RX_TIMEOUT_ERROR		0x02
#घोषणा ZD_RX_FIFO_OVERRUN_ERROR	0x04
#घोषणा ZD_RX_DECRYPTION_ERROR		0x08
#घोषणा ZD_RX_CRC32_ERROR		0x10
#घोषणा ZD_RX_NO_ADDR1_MATCH_ERROR	0x20
#घोषणा ZD_RX_CRC16_ERROR		0x40
#घोषणा ZD_RX_ERROR			0x80

काष्ठा tx_retry_rate अणु
	पूर्णांक count;	/* number of valid element in rate[] array */
	पूर्णांक rate[10];	/* retry rates, described by an index in zd_rates[] */
पूर्ण;

काष्ठा tx_status अणु
	u8 type;	/* must always be 0x01 : USB_INT_TYPE */
	u8 id;		/* must always be 0xa0 : USB_INT_ID_RETRY_FAILED */
	u8 rate;
	u8 pad;
	u8 mac[ETH_ALEN];
	u8 retry;
	u8 failure;
पूर्ण __packed;

क्रमागत mac_flags अणु
	MAC_FIXED_CHANNEL = 0x01,
पूर्ण;

काष्ठा housekeeping अणु
	काष्ठा delayed_work link_led_work;
पूर्ण;

काष्ठा beacon अणु
	काष्ठा delayed_work watchकरोg_work;
	काष्ठा sk_buff *cur_beacon;
	अचिन्हित दीर्घ last_update;
	u16 पूर्णांकerval;
	u8 period;
पूर्ण;

क्रमागत zd_device_flags अणु
	ZD_DEVICE_RUNNING,
पूर्ण;

#घोषणा ZD_MAC_STATS_BUFFER_SIZE 16

#घोषणा ZD_MAC_MAX_ACK_WAITERS 50

काष्ठा zd_mac अणु
	काष्ठा zd_chip chip;
	spinlock_t lock;
	spinlock_t पूर्णांकr_lock;
	काष्ठा ieee80211_hw *hw;
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा housekeeping housekeeping;
	काष्ठा beacon beacon;
	काष्ठा work_काष्ठा set_rts_cts_work;
	काष्ठा work_काष्ठा process_पूर्णांकr;
	काष्ठा zd_mc_hash multicast_hash;
	u8 पूर्णांकr_buffer[USB_MAX_EP_INT_BUFFER];
	u8 regकरोमुख्य;
	u8 शेष_regकरोमुख्य;
	u8 channel;
	पूर्णांक type;
	पूर्णांक associated;
	अचिन्हित दीर्घ flags;
	काष्ठा sk_buff_head ack_रुको_queue;
	काष्ठा ieee80211_channel channels[14];
	काष्ठा ieee80211_rate rates[12];
	काष्ठा ieee80211_supported_band band;

	/* Short preamble (used क्रम RTS/CTS) */
	अचिन्हित पूर्णांक लघु_preamble:1;

	/* whether to pass frames with CRC errors to stack */
	अचिन्हित पूर्णांक pass_failed_fcs:1;

	/* whether to pass control frames to stack */
	अचिन्हित पूर्णांक pass_ctrl:1;

	/* whether we have received a 802.11 ACK that is pending */
	अचिन्हित पूर्णांक ack_pending:1;

	/* संकेत strength of the last 802.11 ACK received */
	पूर्णांक ack_संकेत;
पूर्ण;

#घोषणा ZD_REGDOMAIN_FCC	0x10
#घोषणा ZD_REGDOMAIN_IC		0x20
#घोषणा ZD_REGDOMAIN_ETSI	0x30
#घोषणा ZD_REGDOMAIN_SPAIN	0x31
#घोषणा ZD_REGDOMAIN_FRANCE	0x32
#घोषणा ZD_REGDOMAIN_JAPAN_2	0x40
#घोषणा ZD_REGDOMAIN_JAPAN	0x41
#घोषणा ZD_REGDOMAIN_JAPAN_3	0x49

क्रमागत अणु
	MIN_CHANNEL24 = 1,
	MAX_CHANNEL24 = 14,
पूर्ण;

#घोषणा ZD_PLCP_SERVICE_LENGTH_EXTENSION 0x80

काष्ठा ofdm_plcp_header अणु
	u8 prefix[3];
	__le16 service;
पूर्ण __packed;

अटल अंतरभूत u8 zd_ofdm_plcp_header_rate(स्थिर काष्ठा ofdm_plcp_header *header)
अणु
	वापस header->prefix[0] & 0xf;
पूर्ण

/* The following defines give the encoding of the 4-bit rate field in the
 * OFDM (802.11a/802.11g) PLCP header. Notअगरy that these values are used to
 * define the zd-rate values क्रम OFDM.
 *
 * See the काष्ठा zd_ctrlset definition in zd_mac.h.
 */
#घोषणा ZD_OFDM_PLCP_RATE_6M	0xb
#घोषणा ZD_OFDM_PLCP_RATE_9M	0xf
#घोषणा ZD_OFDM_PLCP_RATE_12M	0xa
#घोषणा ZD_OFDM_PLCP_RATE_18M	0xe
#घोषणा ZD_OFDM_PLCP_RATE_24M	0x9
#घोषणा ZD_OFDM_PLCP_RATE_36M	0xd
#घोषणा ZD_OFDM_PLCP_RATE_48M	0x8
#घोषणा ZD_OFDM_PLCP_RATE_54M	0xc

काष्ठा cck_plcp_header अणु
	u8 संकेत;
	u8 service;
	__le16 length;
	__le16 crc16;
पूर्ण __packed;

अटल अंतरभूत u8 zd_cck_plcp_header_संकेत(स्थिर काष्ठा cck_plcp_header *header)
अणु
	वापस header->संकेत;
पूर्ण

/* These defines give the encodings of the संकेत field in the 802.11b PLCP
 * header. The संकेत field gives the bit rate of the following packet. Even
 * अगर technically wrong we use CCK here also क्रम the 1 MBit/s and 2 MBit/s
 * rate to stay consistent with Zydas and our use of the term.
 *
 * Notअगरy that these values are *not* used in the zd-rates.
 */
#घोषणा ZD_CCK_PLCP_SIGNAL_1M	0x0a
#घोषणा ZD_CCK_PLCP_SIGNAL_2M	0x14
#घोषणा ZD_CCK_PLCP_SIGNAL_5M5	0x37
#घोषणा ZD_CCK_PLCP_SIGNAL_11M	0x6e

अटल अंतरभूत काष्ठा zd_mac *zd_hw_mac(काष्ठा ieee80211_hw *hw)
अणु
	वापस hw->priv;
पूर्ण

अटल अंतरभूत काष्ठा zd_mac *zd_chip_to_mac(काष्ठा zd_chip *chip)
अणु
	वापस container_of(chip, काष्ठा zd_mac, chip);
पूर्ण

अटल अंतरभूत काष्ठा zd_mac *zd_usb_to_mac(काष्ठा zd_usb *usb)
अणु
	वापस zd_chip_to_mac(zd_usb_to_chip(usb));
पूर्ण

अटल अंतरभूत u8 *zd_mac_get_perm_addr(काष्ठा zd_mac *mac)
अणु
	वापस mac->hw->wiphy->perm_addr;
पूर्ण

#घोषणा zd_mac_dev(mac) (zd_chip_dev(&(mac)->chip))

काष्ठा ieee80211_hw *zd_mac_alloc_hw(काष्ठा usb_पूर्णांकerface *पूर्णांकf);
व्योम zd_mac_clear(काष्ठा zd_mac *mac);

पूर्णांक zd_mac_preinit_hw(काष्ठा ieee80211_hw *hw);
पूर्णांक zd_mac_init_hw(काष्ठा ieee80211_hw *hw);

पूर्णांक zd_mac_rx(काष्ठा ieee80211_hw *hw, स्थिर u8 *buffer, अचिन्हित पूर्णांक length);
व्योम zd_mac_tx_failed(काष्ठा urb *urb);
व्योम zd_mac_tx_to_dev(काष्ठा sk_buff *skb, पूर्णांक error);

पूर्णांक zd_op_start(काष्ठा ieee80211_hw *hw);
व्योम zd_op_stop(काष्ठा ieee80211_hw *hw);
पूर्णांक zd_restore_settings(काष्ठा zd_mac *mac);

#अगर_घोषित DEBUG
व्योम zd_dump_rx_status(स्थिर काष्ठा rx_status *status);
#अन्यथा
#घोषणा zd_dump_rx_status(status)
#पूर्ण_अगर /* DEBUG */

#पूर्ण_अगर /* _ZD_MAC_H */
