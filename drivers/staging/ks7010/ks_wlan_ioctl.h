<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *   Driver क्रम KeyStream 11b/g wireless LAN
 *
 *   Copyright (c) 2005-2008 KeyStream Corp.
 *   Copyright (C) 2009 Renesas Technology Corp.
 */

#अगर_अघोषित _KS_WLAN_IOCTL_H
#घोषणा _KS_WLAN_IOCTL_H

#समावेश <linux/wireless.h>
/* The low order bit identअगरy a SET (0) or a GET (1) ioctl.  */

/*					(SIOCIWFIRSTPRIV + 0) */
/* क्रमmer KS_WLAN_GET_DRIVER_VERSION	(SIOCIWFIRSTPRIV + 1) */
/*					(SIOCIWFIRSTPRIV + 2) */
#घोषणा KS_WLAN_GET_FIRM_VERSION	(SIOCIWFIRSTPRIV + 3)
#घोषणा KS_WLAN_SET_WPS_ENABLE		(SIOCIWFIRSTPRIV + 4)
#घोषणा KS_WLAN_GET_WPS_ENABLE		(SIOCIWFIRSTPRIV + 5)
#घोषणा KS_WLAN_SET_WPS_PROBE_REQ	(SIOCIWFIRSTPRIV + 6)
#घोषणा KS_WLAN_GET_EEPROM_CKSUM	(SIOCIWFIRSTPRIV + 7)
#घोषणा KS_WLAN_SET_PREAMBLE		(SIOCIWFIRSTPRIV + 8)
#घोषणा KS_WLAN_GET_PREAMBLE		(SIOCIWFIRSTPRIV + 9)
#घोषणा KS_WLAN_SET_POWER_SAVE		(SIOCIWFIRSTPRIV + 10)
#घोषणा KS_WLAN_GET_POWER_SAVE		(SIOCIWFIRSTPRIV + 11)
#घोषणा KS_WLAN_SET_SCAN_TYPE		(SIOCIWFIRSTPRIV + 12)
#घोषणा KS_WLAN_GET_SCAN_TYPE		(SIOCIWFIRSTPRIV + 13)
#घोषणा KS_WLAN_SET_RX_GAIN		(SIOCIWFIRSTPRIV + 14)
#घोषणा KS_WLAN_GET_RX_GAIN		(SIOCIWFIRSTPRIV + 15)
#घोषणा KS_WLAN_HOSTT			(SIOCIWFIRSTPRIV + 16)	/* unused */
//#घोषणा KS_WLAN_SET_REGION            (SIOCIWFIRSTPRIV + 17)
#घोषणा KS_WLAN_SET_BEACON_LOST		(SIOCIWFIRSTPRIV + 18)
#घोषणा KS_WLAN_GET_BEACON_LOST		(SIOCIWFIRSTPRIV + 19)

#घोषणा KS_WLAN_SET_TX_GAIN		(SIOCIWFIRSTPRIV + 20)
#घोषणा KS_WLAN_GET_TX_GAIN		(SIOCIWFIRSTPRIV + 21)

/* क्रम KS7010 */
#घोषणा KS_WLAN_SET_PHY_TYPE		(SIOCIWFIRSTPRIV + 22)
#घोषणा KS_WLAN_GET_PHY_TYPE		(SIOCIWFIRSTPRIV + 23)
#घोषणा KS_WLAN_SET_CTS_MODE		(SIOCIWFIRSTPRIV + 24)
#घोषणा KS_WLAN_GET_CTS_MODE		(SIOCIWFIRSTPRIV + 25)
/*					(SIOCIWFIRSTPRIV + 26) */
/*					(SIOCIWFIRSTPRIV + 27) */
#घोषणा KS_WLAN_SET_SLEEP_MODE		(SIOCIWFIRSTPRIV + 28)	/* sleep mode */
#घोषणा KS_WLAN_GET_SLEEP_MODE		(SIOCIWFIRSTPRIV + 29)	/* sleep mode */
/*					(SIOCIWFIRSTPRIV + 30) */
/*					(SIOCIWFIRSTPRIV + 31) */

#अगर_घोषित __KERNEL__

#समावेश "ks_wlan.h"
#समावेश <linux/netdevice.h>

पूर्णांक ks_wlan_setup_parameter(काष्ठा ks_wlan_निजी *priv,
			    अचिन्हित पूर्णांक commit_flag);

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* _KS_WLAN_IOCTL_H */
