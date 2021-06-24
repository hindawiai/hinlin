<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *	Copyright (c) 2004, 2005 Jeroen Vreeken (pe1rxq@amsat.org)
 *
 *	Parts of this driver have been derived from a wlan-ng version
 *	modअगरied by ZyDAS.
 *	Copyright (C) 1999 AbsoluteValue Systems, Inc.  All Rights Reserved.
 */

#अगर_अघोषित _INCLUDE_ZD1201_H_
#घोषणा _INCLUDE_ZD1201_H_

#घोषणा ZD1201_NUMKEYS		4
#घोषणा ZD1201_MAXKEYLEN	13
#घोषणा ZD1201_MAXMULTI		16
#घोषणा ZD1201_FRAGMAX		2500
#घोषणा ZD1201_FRAGMIN		256
#घोषणा ZD1201_RTSMAX		2500

#घोषणा ZD1201_RXSIZE		3000

काष्ठा zd1201 अणु
	काष्ठा usb_device	*usb;
	पूर्णांक			हटाओd;
	काष्ठा net_device	*dev;
	काष्ठा iw_statistics	iwstats;

	पूर्णांक			endp_in;
	पूर्णांक			endp_out;
	पूर्णांक			endp_out2;
	काष्ठा urb		*rx_urb;
	काष्ठा urb		*tx_urb;

	अचिन्हित अक्षर 		rxdata[ZD1201_RXSIZE];
	पूर्णांक			rxlen;
	रुको_queue_head_t	rxdataq;
	पूर्णांक			rxdatas;
	काष्ठा hlist_head	fraglist;
	अचिन्हित अक्षर		txdata[ZD1201_RXSIZE];

	पूर्णांक			ap;
	अक्षर			essid[IW_ESSID_MAX_SIZE+1];
	पूर्णांक			essidlen;
	पूर्णांक			mac_enabled;
	पूर्णांक			was_enabled;
	पूर्णांक			monitor;
	पूर्णांक			encode_enabled;
	पूर्णांक			encode_restricted;
	अचिन्हित अक्षर		encode_keys[ZD1201_NUMKEYS][ZD1201_MAXKEYLEN];
	पूर्णांक			encode_keylen[ZD1201_NUMKEYS];
पूर्ण;

काष्ठा zd1201_frag अणु
	काष्ठा hlist_node	fnode;
	पूर्णांक			seq;
	काष्ठा sk_buff		*skb;
पूर्ण;

#घोषणा ZD1201SIWHOSTAUTH SIOCIWFIRSTPRIV
#घोषणा ZD1201GIWHOSTAUTH ZD1201SIWHOSTAUTH+1
#घोषणा ZD1201SIWAUTHSTA SIOCIWFIRSTPRIV+2
#घोषणा ZD1201SIWMAXASSOC SIOCIWFIRSTPRIV+4
#घोषणा ZD1201GIWMAXASSOC ZD1201SIWMAXASSOC+1

#घोषणा ZD1201_FW_TIMEOUT	(1000)

#घोषणा ZD1201_TX_TIMEOUT	(2000)

#घोषणा ZD1201_USB_CMDREQ	0
#घोषणा ZD1201_USB_RESREQ	1

#घोषणा	ZD1201_CMDCODE_INIT	0x00
#घोषणा ZD1201_CMDCODE_ENABLE	0x01
#घोषणा ZD1201_CMDCODE_DISABLE	0x02
#घोषणा ZD1201_CMDCODE_ALLOC	0x0a
#घोषणा ZD1201_CMDCODE_INQUIRE	0x11
#घोषणा ZD1201_CMDCODE_SETRXRID	0x17
#घोषणा ZD1201_CMDCODE_ACCESS	0x21

#घोषणा ZD1201_PACKET_EVENTSTAT	0x0
#घोषणा ZD1201_PACKET_RXDATA	0x1
#घोषणा ZD1201_PACKET_INQUIRE	0x2
#घोषणा ZD1201_PACKET_RESOURCE	0x3

#घोषणा ZD1201_ACCESSBIT	0x0100

#घोषणा ZD1201_RID_CNFPORTTYPE		0xfc00
#घोषणा ZD1201_RID_CNFOWNMACADDR	0xfc01
#घोषणा ZD1201_RID_CNFDESIREDSSID	0xfc02
#घोषणा ZD1201_RID_CNFOWNCHANNEL	0xfc03
#घोषणा ZD1201_RID_CNFOWNSSID		0xfc04
#घोषणा ZD1201_RID_CNFMAXDATALEN	0xfc07
#घोषणा ZD1201_RID_CNFPMENABLED		0xfc09
#घोषणा ZD1201_RID_CNFPMEPS		0xfc0a
#घोषणा ZD1201_RID_CNFMAXSLEEPDURATION	0xfc0c
#घोषणा ZD1201_RID_CNFDEFAULTKEYID	0xfc23
#घोषणा ZD1201_RID_CNFDEFAULTKEY0	0xfc24
#घोषणा ZD1201_RID_CNFDEFAULTKEY1	0xfc25
#घोषणा ZD1201_RID_CNFDEFAULTKEY2	0xfc26
#घोषणा ZD1201_RID_CNFDEFAULTKEY3	0xfc27
#घोषणा ZD1201_RID_CNFWEBFLAGS		0xfc28
#घोषणा ZD1201_RID_CNFAUTHENTICATION	0xfc2a
#घोषणा ZD1201_RID_CNFMAXASSOCSTATIONS	0xfc2b
#घोषणा ZD1201_RID_CNFHOSTAUTH		0xfc2e
#घोषणा ZD1201_RID_CNFGROUPADDRESS	0xfc80
#घोषणा ZD1201_RID_CNFFRAGTHRESHOLD	0xfc82
#घोषणा ZD1201_RID_CNFRTSTHRESHOLD	0xfc83
#घोषणा ZD1201_RID_TXRATECNTL		0xfc84
#घोषणा ZD1201_RID_PROMISCUOUSMODE	0xfc85
#घोषणा ZD1201_RID_CNFBASICRATES	0xfcb3
#घोषणा ZD1201_RID_AUTHENTICATESTA	0xfce3
#घोषणा ZD1201_RID_CURRENTBSSID		0xfd42
#घोषणा ZD1201_RID_COMMSQUALITY		0xfd43
#घोषणा ZD1201_RID_CURRENTTXRATE	0xfd44
#घोषणा ZD1201_RID_CNFMAXTXBUFFERNUMBER	0xfda0
#घोषणा ZD1201_RID_CURRENTCHANNEL	0xfdc1

#घोषणा ZD1201_INQ_SCANRESULTS		0xf101

#घोषणा ZD1201_INF_LINKSTATUS		0xf200
#घोषणा ZD1201_INF_ASSOCSTATUS		0xf201
#घोषणा ZD1201_INF_AUTHREQ		0xf202

#घोषणा ZD1201_ASSOCSTATUS_STAASSOC	0x1
#घोषणा ZD1201_ASSOCSTATUS_REASSOC	0x2
#घोषणा ZD1201_ASSOCSTATUS_DISASSOC	0x3
#घोषणा ZD1201_ASSOCSTATUS_ASSOCFAIL	0x4
#घोषणा ZD1201_ASSOCSTATUS_AUTHFAIL	0x5

#घोषणा ZD1201_PORTTYPE_IBSS		0
#घोषणा ZD1201_PORTTYPE_BSS		1
#घोषणा ZD1201_PORTTYPE_WDS		2
#घोषणा ZD1201_PORTTYPE_PSEUDOIBSS	3
#घोषणा ZD1201_PORTTYPE_AP		6

#घोषणा ZD1201_RATEB1	1
#घोषणा ZD1201_RATEB2	2
#घोषणा ZD1201_RATEB5	4	/* 5.5 really, but 5 is लघुer :) */
#घोषणा ZD1201_RATEB11	8

#घोषणा ZD1201_CNFAUTHENTICATION_OPENSYSTEM	0x0001
#घोषणा ZD1201_CNFAUTHENTICATION_SHAREDKEY	0x0002

#पूर्ण_अगर /* _INCLUDE_ZD1201_H_ */
