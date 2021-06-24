<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR MPL-1.1) */
/* p80211netdev.h
 *
 * WLAN net device काष्ठाure and functions
 *
 * Copyright (C) 1999 AbsoluteValue Systems, Inc.  All Rights Reserved.
 * --------------------------------------------------------------------
 *
 * linux-wlan
 *
 *   The contents of this file are subject to the Mozilla Public
 *   License Version 1.1 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.mozilla.org/MPL/
 *
 *   Software distributed under the License is distributed on an "AS
 *   IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 *   implied. See the License क्रम the specअगरic language governing
 *   rights and limitations under the License.
 *
 *   Alternatively, the contents of this file may be used under the
 *   terms of the GNU Public License version 2 (the "GPL"), in which
 *   हाल the provisions of the GPL are applicable instead of the
 *   above.  If you wish to allow the use of your version of this file
 *   only under the terms of the GPL and not to allow others to use
 *   your version of this file under the MPL, indicate your decision
 *   by deleting the provisions above and replace them with the notice
 *   and other provisions required by the GPL.  If you करो not delete
 *   the provisions above, a recipient may use your version of this
 *   file under either the MPL or the GPL.
 *
 * --------------------------------------------------------------------
 *
 * Inquiries regarding the linux-wlan Open Source project can be
 * made directly to:
 *
 * AbsoluteValue Systems Inc.
 * info@linux-wlan.com
 * http://www.linux-wlan.com
 *
 * --------------------------------------------------------------------
 *
 * Portions of the development of this software were funded by
 * Intersil Corporation as part of PRISM(R) chipset product development.
 *
 * --------------------------------------------------------------------
 *
 * This file declares the काष्ठाure type that represents each wlan
 * पूर्णांकerface.
 *
 * --------------------------------------------------------------------
 */

#अगर_अघोषित _LINUX_P80211NETDEV_H
#घोषणा _LINUX_P80211NETDEV_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/wireless.h>
#समावेश <linux/netdevice.h>

#घोषणा WLAN_RELEASE	"0.3.0-staging"

#घोषणा WLAN_DEVICE_CLOSED	0
#घोषणा WLAN_DEVICE_OPEN	1

#घोषणा WLAN_MACMODE_NONE	0
#घोषणा WLAN_MACMODE_IBSS_STA	1
#घोषणा WLAN_MACMODE_ESS_STA	2
#घोषणा WLAN_MACMODE_ESS_AP	3

/* MSD States */
#घोषणा WLAN_MSD_HWPRESENT_PENDING	1
#घोषणा WLAN_MSD_HWFAIL			2
#घोषणा WLAN_MSD_HWPRESENT		3
#घोषणा WLAN_MSD_FWLOAD_PENDING		4
#घोषणा WLAN_MSD_FWLOAD			5
#घोषणा WLAN_MSD_RUNNING_PENDING	6
#घोषणा WLAN_MSD_RUNNING		7

#अगर_अघोषित ETH_P_ECONET
#घोषणा ETH_P_ECONET   0x0018	/* needed क्रम 2.2.x kernels */
#पूर्ण_अगर

#घोषणा ETH_P_80211_RAW        (ETH_P_ECONET + 1)

#अगर_अघोषित ARPHRD_IEEE80211
#घोषणा ARPHRD_IEEE80211 801	/* kernel 2.4.6 */
#पूर्ण_अगर

#अगर_अघोषित ARPHRD_IEEE80211_PRISM	/* kernel 2.4.18 */
#घोषणा ARPHRD_IEEE80211_PRISM 802
#पूर्ण_अगर

/*--- NSD Capabilities Flags ------------------------------*/
#घोषणा P80211_NSDCAP_HARDWAREWEP           0x01  /* hardware wep engine */
#घोषणा P80211_NSDCAP_SHORT_PREAMBLE        0x10  /* hardware supports */
#घोषणा P80211_NSDCAP_HWFRAGMENT            0x80  /* nsd handles frag/defrag */
#घोषणा P80211_NSDCAP_AUTOJOIN              0x100 /* nsd करोes स्वतःjoin */
#घोषणा P80211_NSDCAP_NOSCAN                0x200 /* nsd can scan */

/* Received frame statistics */
काष्ठा p80211_frmrx अणु
	u32 mgmt;
	u32 assocreq;
	u32 assocresp;
	u32 reassocreq;
	u32 reassocresp;
	u32 probereq;
	u32 proberesp;
	u32 beacon;
	u32 atim;
	u32 disassoc;
	u32 authen;
	u32 deauthen;
	u32 mgmt_unknown;
	u32 ctl;
	u32 pspoll;
	u32 rts;
	u32 cts;
	u32 ack;
	u32 cfend;
	u32 cfendcfack;
	u32 ctl_unknown;
	u32 data;
	u32 dataonly;
	u32 data_cfack;
	u32 data_cfpoll;
	u32 data__cfack_cfpoll;
	u32 null;
	u32 cfack;
	u32 cfpoll;
	u32 cfack_cfpoll;
	u32 data_unknown;
	u32 decrypt;
	u32 decrypt_err;
पूर्ण;

/* called by /proc/net/wireless */
काष्ठा iw_statistics *p80211wext_get_wireless_stats(काष्ठा net_device *dev);
/* wireless extensions' ioctls */
बाह्य काष्ठा iw_handler_def p80211wext_handler_def;

/* WEP stuff */
#घोषणा NUM_WEPKEYS 4
#घोषणा MAX_KEYLEN 32

#घोषणा HOSTWEP_DEFAULTKEY_MASK GENMASK(1, 0)
#घोषणा HOSTWEP_SHAREDKEY BIT(3)
#घोषणा HOSTWEP_DECRYPT  BIT(4)
#घोषणा HOSTWEP_ENCRYPT  BIT(5)
#घोषणा HOSTWEP_PRIVACYINVOKED BIT(6)
#घोषणा HOSTWEP_EXCLUDEUNENCRYPTED BIT(7)

बाह्य पूर्णांक wlan_watchकरोg;
बाह्य पूर्णांक wlan_wext_ग_लिखो;

/* WLAN device type */
काष्ठा wlandevice अणु
	व्योम *priv;		/* निजी data क्रम MSD */

	/* Subप्रणाली State */
	अक्षर name[WLAN_DEVNAMELEN_MAX];	/* Dev name, from रेजिस्टर_wlandev() */
	अक्षर *nsdname;

	u32 state;		/* Device I/F state (खोलो/बंदd) */
	u32 msdstate;		/* state of underlying driver */
	u32 hwहटाओd;		/* Has the hw been yanked out? */

	/* Hardware config */
	अचिन्हित पूर्णांक irq;
	अचिन्हित पूर्णांक iobase;
	अचिन्हित पूर्णांक membase;
	u32 nsdcaps;		/* NSD Capabilities flags */

	/* Config vars */
	अचिन्हित पूर्णांक ethconv;

	/* device methods (init by MSD, used by p80211 */
	पूर्णांक (*खोलो)(काष्ठा wlandevice *wlandev);
	पूर्णांक (*बंद)(काष्ठा wlandevice *wlandev);
	व्योम (*reset)(काष्ठा wlandevice *wlandev);
	पूर्णांक (*txframe)(काष्ठा wlandevice *wlandev, काष्ठा sk_buff *skb,
		       जोड़ p80211_hdr *p80211_hdr,
		       काष्ठा p80211_metawep *p80211_wep);
	पूर्णांक (*mlmerequest)(काष्ठा wlandevice *wlandev, काष्ठा p80211msg *msg);
	पूर्णांक (*set_multicast_list)(काष्ठा wlandevice *wlandev,
				  काष्ठा net_device *dev);
	व्योम (*tx_समयout)(काष्ठा wlandevice *wlandev);

	/* 802.11 State */
	u8 bssid[WLAN_BSSID_LEN];
	काष्ठा p80211pstr32 ssid;
	u32 macmode;
	पूर्णांक linkstatus;

	/* WEP State */
	u8 wep_keys[NUM_WEPKEYS][MAX_KEYLEN];
	u8 wep_keylens[NUM_WEPKEYS];
	पूर्णांक hostwep;

	/* Request/Confirm i/f state (used by p80211) */
	अचिन्हित दीर्घ request_pending;	/* flag, access atomically */

	/* netlink socket */
	/* queue क्रम indications रुकोing क्रम cmd completion */
	/* Linux netdevice and support */
	काष्ठा net_device *netdev;	/* ptr to linux netdevice */

	/* Rx bottom half */
	काष्ठा tasklet_काष्ठा rx_bh;

	काष्ठा sk_buff_head nsd_rxq;

	/* 802.11 device statistics */
	काष्ठा p80211_frmrx rx;

	काष्ठा iw_statistics wstats;

	/* jkriegl: iwspy fields */
	u8 spy_number;
	अक्षर spy_address[IW_MAX_SPY][ETH_ALEN];
	काष्ठा iw_quality spy_stat[IW_MAX_SPY];
पूर्ण;

/* WEP stuff */
पूर्णांक wep_change_key(काष्ठा wlandevice *wlandev, पूर्णांक keynum, u8 *key, पूर्णांक keylen);
पूर्णांक wep_decrypt(काष्ठा wlandevice *wlandev, u8 *buf, u32 len, पूर्णांक key_override,
		u8 *iv, u8 *icv);
पूर्णांक wep_encrypt(काष्ठा wlandevice *wlandev, u8 *buf, u8 *dst, u32 len,
		पूर्णांक keynum, u8 *iv, u8 *icv);

पूर्णांक wlan_setup(काष्ठा wlandevice *wlandev, काष्ठा device *physdev);
व्योम wlan_unsetup(काष्ठा wlandevice *wlandev);
पूर्णांक रेजिस्टर_wlandev(काष्ठा wlandevice *wlandev);
पूर्णांक unरेजिस्टर_wlandev(काष्ठा wlandevice *wlandev);
व्योम p80211netdev_rx(काष्ठा wlandevice *wlandev, काष्ठा sk_buff *skb);
व्योम p80211netdev_hwहटाओd(काष्ठा wlandevice *wlandev);
#पूर्ण_अगर
