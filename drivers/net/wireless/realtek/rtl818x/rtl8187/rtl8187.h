<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Definitions क्रम RTL8187 hardware
 *
 * Copyright 2007 Michael Wu <flamingice@sourmilk.net>
 * Copyright 2007 Andrea Merello <andrea.merello@gmail.com>
 *
 * Based on the r8187 driver, which is:
 * Copyright 2005 Andrea Merello <andrea.merello@gmail.com>, et al.
 */

#अगर_अघोषित RTL8187_H
#घोषणा RTL8187_H

#समावेश <linux/cache.h>

#समावेश "rtl818x.h"
#समावेश "leds.h"

#घोषणा RTL8187_EEPROM_TXPWR_BASE	0x05
#घोषणा RTL8187_EEPROM_MAC_ADDR		0x07
#घोषणा RTL8187_EEPROM_TXPWR_CHAN_1	0x16	/* 3 channels */
#घोषणा RTL8187_EEPROM_TXPWR_CHAN_6	0x1B	/* 2 channels */
#घोषणा RTL8187_EEPROM_TXPWR_CHAN_4	0x3D	/* 2 channels */
#घोषणा RTL8187_EEPROM_SELECT_GPIO	0x3B

#घोषणा RTL8187_REQT_READ	0xC0
#घोषणा RTL8187_REQT_WRITE	0x40
#घोषणा RTL8187_REQ_GET_REG	0x05
#घोषणा RTL8187_REQ_SET_REG	0x05

#घोषणा RTL8187_MAX_RX		0x9C4

#घोषणा RFKILL_MASK_8187_89_97	0x2
#घोषणा RFKILL_MASK_8198	0x4

#घोषणा RETRY_COUNT		7

काष्ठा rtl8187_rx_info अणु
	काष्ठा urb *urb;
	काष्ठा ieee80211_hw *dev;
पूर्ण;

काष्ठा rtl8187_rx_hdr अणु
	__le32 flags;
	u8 noise;
	u8 संकेत;
	u8 agc;
	u8 reserved;
	__le64 mac_समय;
पूर्ण __packed;

काष्ठा rtl8187b_rx_hdr अणु
	__le32 flags;
	__le64 mac_समय;
	u8 sq;
	u8 rssi;
	u8 agc;
	u8 flags2;
	__le16 snr_दीर्घ2end;
	s8 pwdb_g12;
	u8 fot;
पूर्ण __packed;

/* अणुrtl8187,rtl8187bपूर्ण_tx_info is in skb */

काष्ठा rtl8187_tx_hdr अणु
	__le32 flags;
	__le16 rts_duration;
	__le16 len;
	__le32 retry;
पूर्ण __packed;

काष्ठा rtl8187b_tx_hdr अणु
	__le32 flags;
	__le16 rts_duration;
	__le16 len;
	__le32 unused_1;
	__le16 unused_2;
	__le16 tx_duration;
	__le32 unused_3;
	__le32 retry;
	__le32 unused_4[2];
पूर्ण __packed;

क्रमागत अणु
	DEVICE_RTL8187,
	DEVICE_RTL8187B
पूर्ण;

काष्ठा rtl8187_vअगर अणु
	काष्ठा ieee80211_hw *dev;

	/* beaconing */
	काष्ठा delayed_work beacon_work;
	bool enable_beacon;
पूर्ण;

काष्ठा rtl8187_priv अणु
	/* common between rtl818x drivers */
	काष्ठा rtl818x_csr *map;
	स्थिर काष्ठा rtl818x_rf_ops *rf;
	काष्ठा ieee80211_vअगर *vअगर;

	/* The mutex protects the TX loopback state.
	 * Any attempt to set channels concurrently locks the device.
	 */
	काष्ठा mutex conf_mutex;

	/* rtl8187 specअगरic */
	काष्ठा ieee80211_channel channels[14];
	काष्ठा ieee80211_rate rates[12];
	काष्ठा ieee80211_supported_band band;
	काष्ठा usb_device *udev;
	u32 rx_conf;
	काष्ठा usb_anchor anchored;
	काष्ठा delayed_work work;
	काष्ठा ieee80211_hw *dev;
#अगर_घोषित CONFIG_RTL8187_LEDS
	काष्ठा rtl8187_led led_radio;
	काष्ठा rtl8187_led led_tx;
	काष्ठा rtl8187_led led_rx;
	काष्ठा delayed_work led_on;
	काष्ठा delayed_work led_off;
#पूर्ण_अगर
	u16 txpwr_base;
	u8 asic_rev;
	u8 is_rtl8187b;
	क्रमागत अणु
		RTL8187BvB,
		RTL8187BvD,
		RTL8187BvE
	पूर्ण hw_rev;
	काष्ठा sk_buff_head rx_queue;
	u8 संकेत;
	u8 noise;
	u8 slot_समय;
	u8 aअगरsn[4];
	u8 rfसमाप्त_mask;
	काष्ठा अणु
		जोड़ अणु
			__le64 buf;
			u8 dummy1[L1_CACHE_BYTES];
		पूर्ण ____cacheline_aligned;
		काष्ठा sk_buff_head queue;
	पूर्ण b_tx_status; /* This queue is used by both -b and non-b devices */
	काष्ठा mutex io_mutex;
	जोड़ अणु
		u8 bits8;
		__le16 bits16;
		__le32 bits32;
		u8 dummy2[L1_CACHE_BYTES];
	पूर्ण *io_dmabuf ____cacheline_aligned;
	bool rfसमाप्त_off;
	u16 seqno;
पूर्ण;

व्योम rtl8187_ग_लिखो_phy(काष्ठा ieee80211_hw *dev, u8 addr, u32 data);

u8 rtl818x_ioपढ़ो8_idx(काष्ठा rtl8187_priv *priv,
				u8 *addr, u8 idx);

अटल अंतरभूत u8 rtl818x_ioपढ़ो8(काष्ठा rtl8187_priv *priv, u8 *addr)
अणु
	वापस rtl818x_ioपढ़ो8_idx(priv, addr, 0);
पूर्ण

u16 rtl818x_ioपढ़ो16_idx(काष्ठा rtl8187_priv *priv,
				__le16 *addr, u8 idx);

अटल अंतरभूत u16 rtl818x_ioपढ़ो16(काष्ठा rtl8187_priv *priv, __le16 *addr)
अणु
	वापस rtl818x_ioपढ़ो16_idx(priv, addr, 0);
पूर्ण

u32 rtl818x_ioपढ़ो32_idx(काष्ठा rtl8187_priv *priv,
				__le32 *addr, u8 idx);

अटल अंतरभूत u32 rtl818x_ioपढ़ो32(काष्ठा rtl8187_priv *priv, __le32 *addr)
अणु
	वापस rtl818x_ioपढ़ो32_idx(priv, addr, 0);
पूर्ण

व्योम rtl818x_ioग_लिखो8_idx(काष्ठा rtl8187_priv *priv,
				u8 *addr, u8 val, u8 idx);

अटल अंतरभूत व्योम rtl818x_ioग_लिखो8(काष्ठा rtl8187_priv *priv, u8 *addr, u8 val)
अणु
	rtl818x_ioग_लिखो8_idx(priv, addr, val, 0);
पूर्ण

व्योम rtl818x_ioग_लिखो16_idx(काष्ठा rtl8187_priv *priv,
				__le16 *addr, u16 val, u8 idx);

अटल अंतरभूत व्योम rtl818x_ioग_लिखो16(काष्ठा rtl8187_priv *priv, __le16 *addr,
				     u16 val)
अणु
	rtl818x_ioग_लिखो16_idx(priv, addr, val, 0);
पूर्ण

व्योम rtl818x_ioग_लिखो32_idx(काष्ठा rtl8187_priv *priv,
				__le32 *addr, u32 val, u8 idx);

अटल अंतरभूत व्योम rtl818x_ioग_लिखो32(काष्ठा rtl8187_priv *priv, __le32 *addr,
				     u32 val)
अणु
	rtl818x_ioग_लिखो32_idx(priv, addr, val, 0);
पूर्ण

#पूर्ण_अगर /* RTL8187_H */
