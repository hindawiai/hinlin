<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <net/ieee80211_radiotap.h>

काष्ठा tx_radiotap_hdr अणु
	काष्ठा ieee80211_radiotap_header hdr;
	u8 rate;
	u8 txघातer;
	u8 rts_retries;
	u8 data_retries;
पूर्ण __packed;

#घोषणा TX_RADIOTAP_PRESENT (				\
	(1 << IEEE80211_RADIOTAP_RATE) |		\
	(1 << IEEE80211_RADIOTAP_DBM_TX_POWER) |	\
	(1 << IEEE80211_RADIOTAP_RTS_RETRIES) |		\
	(1 << IEEE80211_RADIOTAP_DATA_RETRIES)  |	\
	0)

#घोषणा IEEE80211_FC_VERSION_MASK    0x0003
#घोषणा IEEE80211_FC_TYPE_MASK       0x000c
#घोषणा IEEE80211_FC_TYPE_MGT        0x0000
#घोषणा IEEE80211_FC_TYPE_CTL        0x0004
#घोषणा IEEE80211_FC_TYPE_DATA       0x0008
#घोषणा IEEE80211_FC_SUBTYPE_MASK    0x00f0
#घोषणा IEEE80211_FC_TOFROMDS_MASK   0x0300
#घोषणा IEEE80211_FC_TODS_MASK       0x0100
#घोषणा IEEE80211_FC_FROMDS_MASK     0x0200
#घोषणा IEEE80211_FC_NODS            0x0000
#घोषणा IEEE80211_FC_TODS            0x0100
#घोषणा IEEE80211_FC_FROMDS          0x0200
#घोषणा IEEE80211_FC_DSTODS          0x0300

काष्ठा rx_radiotap_hdr अणु
	काष्ठा ieee80211_radiotap_header hdr;
	u8 flags;
	u8 rate;
	u8 antसंकेत;
पूर्ण __packed;

#घोषणा RX_RADIOTAP_PRESENT (			\
	(1 << IEEE80211_RADIOTAP_FLAGS) |	\
	(1 << IEEE80211_RADIOTAP_RATE) |	\
	(1 << IEEE80211_RADIOTAP_DB_ANTSIGNAL) |\
	0)

