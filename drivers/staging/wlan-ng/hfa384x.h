<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR MPL-1.1) */
/* hfa384x.h
 *
 * Defines the स्थिरants and data काष्ठाures क्रम the hfa384x
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
 *    implied. See the License क्रम the specअगरic language governing
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
 *   [Implementation and usage notes]
 *
 *   [References]
 *	CW10 Programmer's Manual v1.5
 *	IEEE 802.11 D10.0
 *
 * --------------------------------------------------------------------
 */

#अगर_अघोषित _HFA384x_H
#घोषणा _HFA384x_H

#घोषणा HFA384x_FIRMWARE_VERSION(a, b, c) (((a) << 16) + ((b) << 8) + (c))

#समावेश <linux/अगर_ether.h>
#समावेश <linux/usb.h>

/*--- Mins & Maxs -----------------------------------*/
#घोषणा	HFA384x_PORTID_MAX		((u16)7)
#घोषणा	HFA384x_NUMPORTS_MAX		((u16)(HFA384x_PORTID_MAX + 1))
#घोषणा	HFA384x_PDR_LEN_MAX		((u16)512) /* in bytes, from EK */
#घोषणा	HFA384x_PDA_RECS_MAX		((u16)200) /* a guess */
#घोषणा	HFA384x_PDA_LEN_MAX		((u16)1024) /* in bytes, from EK*/
#घोषणा	HFA384x_SCANRESULT_MAX		((u16)31)
#घोषणा	HFA384x_HSCANRESULT_MAX		((u16)31)
#घोषणा	HFA384x_CHINFORESULT_MAX	((u16)16)
#घोषणा	HFA384x_RID_GUESSING_MAXLEN	2048	/* I'm not really sure */
#घोषणा	HFA384x_RIDDATA_MAXLEN		HFA384x_RID_GUESSING_MAXLEN
#घोषणा	HFA384x_USB_RWMEM_MAXLEN	2048

/*--- Support Constants -----------------------------*/
#घोषणा		HFA384x_PORTTYPE_IBSS			((u16)0)
#घोषणा		HFA384x_PORTTYPE_BSS			((u16)1)
#घोषणा		HFA384x_PORTTYPE_PSUEDOIBSS		((u16)3)
#घोषणा		HFA384x_WEPFLAGS_PRIVINVOKED		((u16)BIT(0))
#घोषणा		HFA384x_WEPFLAGS_EXCLUDE		((u16)BIT(1))
#घोषणा		HFA384x_WEPFLAGS_DISABLE_TXCRYPT	((u16)BIT(4))
#घोषणा		HFA384x_WEPFLAGS_DISABLE_RXCRYPT	((u16)BIT(7))
#घोषणा		HFA384x_ROAMMODE_HOSTSCAN_HOSTROAM	((u16)3)
#घोषणा		HFA384x_PORTSTATUS_DISABLED		((u16)1)
#घोषणा		HFA384x_RATEBIT_1			((u16)1)
#घोषणा		HFA384x_RATEBIT_2			((u16)2)
#घोषणा		HFA384x_RATEBIT_5करोt5			((u16)4)
#घोषणा		HFA384x_RATEBIT_11			((u16)8)

/*--- MAC Internal memory स्थिरants and macros ------*/
/* masks and macros used to manipulate MAC पूर्णांकernal memory addresses. */
/* MAC पूर्णांकernal memory addresses are 23 bit quantities.  The MAC uses
 * a paged address space where the upper 16 bits are the page number
 * and the lower 7 bits are the offset.  There are various Host API
 * elements that require two 16-bit quantities to specअगरy a MAC
 * पूर्णांकernal memory address.  Unक्रमtunately, some of the API's use a
 * page/offset क्रमmat where the offset value is JUST the lower seven
 * bits and the page is  the reमुख्यing 16 bits.  Some of the API's
 * assume that the 23 bit address has been split at the 16th bit.  We
 * refer to these two क्रमmats as AUX क्रमmat and CMD क्रमmat.  The
 * macros below help handle some of this.
 */

/* Mask bits क्रम discarding unwanted pieces in a flat address */
#घोषणा		HFA384x_ADDR_FLAT_AUX_PAGE_MASK	(0x007fff80)
#घोषणा		HFA384x_ADDR_FLAT_AUX_OFF_MASK	(0x0000007f)
#घोषणा		HFA384x_ADDR_FLAT_CMD_PAGE_MASK	(0xffff0000)
#घोषणा		HFA384x_ADDR_FLAT_CMD_OFF_MASK	(0x0000ffff)

/* Mask bits क्रम discarding unwanted pieces in AUX क्रमmat
 * 16-bit address parts
 */
#घोषणा		HFA384x_ADDR_AUX_PAGE_MASK	(0xffff)
#घोषणा		HFA384x_ADDR_AUX_OFF_MASK	(0x007f)

/* Make a 32-bit flat address from AUX क्रमmat 16-bit page and offset */
#घोषणा		HFA384x_ADDR_AUX_MKFLAT(p, o)	\
		((((u32)(((u16)(p)) & HFA384x_ADDR_AUX_PAGE_MASK)) << 7) | \
		((u32)(((u16)(o)) & HFA384x_ADDR_AUX_OFF_MASK)))

/* Make CMD क्रमmat offset and page from a 32-bit flat address */
#घोषणा		HFA384x_ADDR_CMD_MKPAGE(f) \
		((u16)((((u32)(f)) & HFA384x_ADDR_FLAT_CMD_PAGE_MASK) >> 16))
#घोषणा		HFA384x_ADDR_CMD_MKOFF(f) \
		((u16)(((u32)(f)) & HFA384x_ADDR_FLAT_CMD_OFF_MASK))

/*--- Controller Memory addresses -------------------*/
#घोषणा		HFA3842_PDA_BASE	(0x007f0000UL)
#घोषणा		HFA3841_PDA_BASE	(0x003f0000UL)
#घोषणा		HFA3841_PDA_BOGUS_BASE	(0x00390000UL)

/*--- Driver Download states  -----------------------*/
#घोषणा		HFA384x_DLSTATE_DISABLED		0
#घोषणा		HFA384x_DLSTATE_RAMENABLED		1
#घोषणा		HFA384x_DLSTATE_FLASHENABLED		2

/*--- Register Field Masks --------------------------*/
#घोषणा		HFA384x_CMD_AINFO		((u16)GENMASK(14, 8))
#घोषणा		HFA384x_CMD_MACPORT		((u16)GENMASK(10, 8))
#घोषणा		HFA384x_CMD_PROGMODE		((u16)GENMASK(9, 8))
#घोषणा		HFA384x_CMD_CMDCODE		((u16)GENMASK(5, 0))
#घोषणा		HFA384x_STATUS_RESULT		((u16)GENMASK(14, 8))

/*--- Command Code Constants --------------------------*/
/*--- Controller Commands --------------------------*/
#घोषणा		HFA384x_CMDCODE_INIT		((u16)0x00)
#घोषणा		HFA384x_CMDCODE_ENABLE		((u16)0x01)
#घोषणा		HFA384x_CMDCODE_DISABLE		((u16)0x02)

/*--- Regulate Commands --------------------------*/
#घोषणा		HFA384x_CMDCODE_INQ		((u16)0x11)

/*--- Configure Commands --------------------------*/
#घोषणा		HFA384x_CMDCODE_DOWNLD		((u16)0x22)

/*--- Debugging Commands -----------------------------*/
#घोषणा		HFA384x_CMDCODE_MONITOR		((u16)(0x38))
#घोषणा		HFA384x_MONITOR_ENABLE		((u16)(0x0b))
#घोषणा		HFA384x_MONITOR_DISABLE		((u16)(0x0f))

/*--- Result Codes --------------------------*/
#घोषणा		HFA384x_CMD_ERR			((u16)(0x7F))

/*--- Programming Modes --------------------------
 *	MODE 0: Disable programming
 *	MODE 1: Enable अस्थिर memory programming
 *	MODE 2: Enable non-अस्थिर memory programming
 *	MODE 3: Program non-अस्थिर memory section
 *-------------------------------------------------
 */
#घोषणा		HFA384x_PROGMODE_DISABLE	((u16)0x00)
#घोषणा		HFA384x_PROGMODE_RAM		((u16)0x01)
#घोषणा		HFA384x_PROGMODE_NV		((u16)0x02)
#घोषणा		HFA384x_PROGMODE_NVWRITE	((u16)0x03)

/*--- Record ID Constants --------------------------*/
/*--------------------------------------------------------------------
 * Configuration RIDs: Network Parameters, Static Configuration Entities
 *--------------------------------------------------------------------
 */
#घोषणा		HFA384x_RID_CNFPORTTYPE		((u16)0xFC00)
#घोषणा		HFA384x_RID_CNFOWNMACADDR	((u16)0xFC01)
#घोषणा		HFA384x_RID_CNFDESIREDSSID	((u16)0xFC02)
#घोषणा		HFA384x_RID_CNFOWNCHANNEL	((u16)0xFC03)
#घोषणा		HFA384x_RID_CNFOWNSSID		((u16)0xFC04)
#घोषणा		HFA384x_RID_CNFMAXDATALEN	((u16)0xFC07)

/*--------------------------------------------------------------------
 * Configuration RID lengths: Network Params, Static Config Entities
 * This is the length of JUST the DATA part of the RID (करोes not
 * include the len or code fields)
 *--------------------------------------------------------------------
 */
#घोषणा		HFA384x_RID_CNFOWNMACADDR_LEN	((u16)6)
#घोषणा		HFA384x_RID_CNFDESIREDSSID_LEN	((u16)34)
#घोषणा		HFA384x_RID_CNFOWNSSID_LEN	((u16)34)

/*--------------------------------------------------------------------
 * Configuration RIDs: Network Parameters, Dynamic Configuration Entities
 *--------------------------------------------------------------------
 */
#घोषणा		HFA384x_RID_CREATEIBSS		((u16)0xFC81)
#घोषणा		HFA384x_RID_FRAGTHRESH		((u16)0xFC82)
#घोषणा		HFA384x_RID_RTSTHRESH		((u16)0xFC83)
#घोषणा		HFA384x_RID_TXRATECNTL		((u16)0xFC84)
#घोषणा		HFA384x_RID_PROMISCMODE		((u16)0xFC85)

/*----------------------------------------------------------------------
 * Inक्रमmation RIDs: NIC Inक्रमmation
 *----------------------------------------------------------------------
 */
#घोषणा		HFA384x_RID_MAXLOADTIME		((u16)0xFD00)
#घोषणा		HFA384x_RID_DOWNLOADBUFFER	((u16)0xFD01)
#घोषणा		HFA384x_RID_PRIIDENTITY		((u16)0xFD02)
#घोषणा		HFA384x_RID_PRISUPRANGE		((u16)0xFD03)
#घोषणा		HFA384x_RID_PRI_CFIACTRANGES	((u16)0xFD04)
#घोषणा		HFA384x_RID_NICSERIALNUMBER	((u16)0xFD0A)
#घोषणा		HFA384x_RID_NICIDENTITY		((u16)0xFD0B)
#घोषणा		HFA384x_RID_MFISUPRANGE		((u16)0xFD0C)
#घोषणा		HFA384x_RID_CFISUPRANGE		((u16)0xFD0D)
#घोषणा		HFA384x_RID_STAIDENTITY		((u16)0xFD20)
#घोषणा		HFA384x_RID_STASUPRANGE		((u16)0xFD21)
#घोषणा		HFA384x_RID_STA_MFIACTRANGES	((u16)0xFD22)
#घोषणा		HFA384x_RID_STA_CFIACTRANGES	((u16)0xFD23)

/*----------------------------------------------------------------------
 * Inक्रमmation RID Lengths: NIC Inक्रमmation
 * This is the length of JUST the DATA part of the RID (करोes not
 * include the len or code fields)
 *---------------------------------------------------------------------
 */
#घोषणा		HFA384x_RID_NICSERIALNUMBER_LEN		((u16)12)

/*--------------------------------------------------------------------
 * Inक्रमmation RIDs:  MAC Inक्रमmation
 *--------------------------------------------------------------------
 */
#घोषणा		HFA384x_RID_PORTSTATUS		((u16)0xFD40)
#घोषणा		HFA384x_RID_CURRENTSSID		((u16)0xFD41)
#घोषणा		HFA384x_RID_CURRENTBSSID	((u16)0xFD42)
#घोषणा		HFA384x_RID_CURRENTTXRATE	((u16)0xFD44)
#घोषणा		HFA384x_RID_SHORTRETRYLIMIT	((u16)0xFD48)
#घोषणा		HFA384x_RID_LONGRETRYLIMIT	((u16)0xFD49)
#घोषणा		HFA384x_RID_MAXTXLIFETIME	((u16)0xFD4A)
#घोषणा		HFA384x_RID_PRIVACYOPTIMP	((u16)0xFD4F)
#घोषणा		HFA384x_RID_DBMCOMMSQUALITY	((u16)0xFD51)

/*--------------------------------------------------------------------
 * Inक्रमmation RID Lengths:  MAC Inक्रमmation
 * This is the length of JUST the DATA part of the RID (करोes not
 * include the len or code fields)
 *--------------------------------------------------------------------
 */
#घोषणा		HFA384x_RID_DBMCOMMSQUALITY_LEN	 \
	((u16)माप(काष्ठा hfa384x_dbmcommsquality))
#घोषणा		HFA384x_RID_JOINREQUEST_LEN \
	((u16)माप(काष्ठा hfa384x_join_request_data))

/*--------------------------------------------------------------------
 * Inक्रमmation RIDs:  Modem Inक्रमmation
 *--------------------------------------------------------------------
 */
#घोषणा		HFA384x_RID_CURRENTCHANNEL	((u16)0xFDC1)

/*--------------------------------------------------------------------
 * API ENHANCEMENTS (NOT ALREADY IMPLEMENTED)
 *--------------------------------------------------------------------
 */
#घोषणा		HFA384x_RID_CNFWEPDEFAULTKEYID	((u16)0xFC23)
#घोषणा		HFA384x_RID_CNFWEPDEFAULTKEY0	((u16)0xFC24)
#घोषणा		HFA384x_RID_CNFWEPDEFAULTKEY1	((u16)0xFC25)
#घोषणा		HFA384x_RID_CNFWEPDEFAULTKEY2	((u16)0xFC26)
#घोषणा		HFA384x_RID_CNFWEPDEFAULTKEY3	((u16)0xFC27)
#घोषणा		HFA384x_RID_CNFWEPFLAGS		((u16)0xFC28)
#घोषणा		HFA384x_RID_CNFAUTHENTICATION	((u16)0xFC2A)
#घोषणा		HFA384x_RID_CNFROAMINGMODE	((u16)0xFC2D)
#घोषणा		HFA384x_RID_CNFAPBCNINT		((u16)0xFC33)
#घोषणा		HFA384x_RID_CNFDBMADJUST	((u16)0xFC46)
#घोषणा		HFA384x_RID_CNFWPADATA		((u16)0xFC48)
#घोषणा		HFA384x_RID_CNFBASICRATES	((u16)0xFCB3)
#घोषणा		HFA384x_RID_CNFSUPPRATES	((u16)0xFCB4)
#घोषणा		HFA384x_RID_CNFPASSIVESCANCTRL	((u16)0xFCBA)
#घोषणा		HFA384x_RID_TXPOWERMAX		((u16)0xFCBE)
#घोषणा		HFA384x_RID_JOINREQUEST		((u16)0xFCE2)
#घोषणा		HFA384x_RID_AUTHENTICATESTA	((u16)0xFCE3)
#घोषणा		HFA384x_RID_HOSTSCAN		((u16)0xFCE5)

#घोषणा		HFA384x_RID_CNFWEPDEFAULTKEY_LEN	((u16)6)
#घोषणा		HFA384x_RID_CNFWEP128DEFAULTKEY_LEN	((u16)14)

/*--------------------------------------------------------------------
 * PD Record codes
 *--------------------------------------------------------------------
 */
#घोषणा HFA384x_PDR_PCB_PARTNUM		((u16)0x0001)
#घोषणा HFA384x_PDR_PDAVER		((u16)0x0002)
#घोषणा HFA384x_PDR_NIC_SERIAL		((u16)0x0003)
#घोषणा HFA384x_PDR_MKK_MEASUREMENTS	((u16)0x0004)
#घोषणा HFA384x_PDR_NIC_RAMSIZE		((u16)0x0005)
#घोषणा HFA384x_PDR_MFISUPRANGE		((u16)0x0006)
#घोषणा HFA384x_PDR_CFISUPRANGE		((u16)0x0007)
#घोषणा HFA384x_PDR_NICID		((u16)0x0008)
#घोषणा HFA384x_PDR_MAC_ADDRESS		((u16)0x0101)
#घोषणा HFA384x_PDR_REGDOMAIN		((u16)0x0103)
#घोषणा HFA384x_PDR_ALLOWED_CHANNEL	((u16)0x0104)
#घोषणा HFA384x_PDR_DEFAULT_CHANNEL	((u16)0x0105)
#घोषणा HFA384x_PDR_TEMPTYPE		((u16)0x0107)
#घोषणा HFA384x_PDR_IFR_SETTING		((u16)0x0200)
#घोषणा HFA384x_PDR_RFR_SETTING		((u16)0x0201)
#घोषणा HFA384x_PDR_HFA3861_BASELINE	((u16)0x0202)
#घोषणा HFA384x_PDR_HFA3861_SHADOW	((u16)0x0203)
#घोषणा HFA384x_PDR_HFA3861_IFRF	((u16)0x0204)
#घोषणा HFA384x_PDR_HFA3861_CHCALSP	((u16)0x0300)
#घोषणा HFA384x_PDR_HFA3861_CHCALI	((u16)0x0301)
#घोषणा HFA384x_PDR_MAX_TX_POWER	((u16)0x0302)
#घोषणा HFA384x_PDR_MASTER_CHAN_LIST	((u16)0x0303)
#घोषणा HFA384x_PDR_3842_NIC_CONFIG	((u16)0x0400)
#घोषणा HFA384x_PDR_USB_ID		((u16)0x0401)
#घोषणा HFA384x_PDR_PCI_ID		((u16)0x0402)
#घोषणा HFA384x_PDR_PCI_IFCONF		((u16)0x0403)
#घोषणा HFA384x_PDR_PCI_PMCONF		((u16)0x0404)
#घोषणा HFA384x_PDR_RFENRGY		((u16)0x0406)
#घोषणा HFA384x_PDR_USB_POWER_TYPE      ((u16)0x0407)
#घोषणा HFA384x_PDR_USB_MAX_POWER	((u16)0x0409)
#घोषणा HFA384x_PDR_USB_MANUFACTURER	((u16)0x0410)
#घोषणा HFA384x_PDR_USB_PRODUCT		((u16)0x0411)
#घोषणा HFA384x_PDR_ANT_DIVERSITY	((u16)0x0412)
#घोषणा HFA384x_PDR_HFO_DELAY		((u16)0x0413)
#घोषणा HFA384x_PDR_SCALE_THRESH	((u16)0x0414)

#घोषणा HFA384x_PDR_HFA3861_MANF_TESTSP	((u16)0x0900)
#घोषणा HFA384x_PDR_HFA3861_MANF_TESTI	((u16)0x0901)
#घोषणा HFA384x_PDR_END_OF_PDA		((u16)0x0000)

/*--- Register Test/Get/Set Field macros ------------------------*/

#घोषणा		HFA384x_CMD_AINFO_SET(value)	((u16)((u16)(value) << 8))
#घोषणा		HFA384x_CMD_MACPORT_SET(value)	\
			((u16)HFA384x_CMD_AINFO_SET(value))
#घोषणा		HFA384x_CMD_PROGMODE_SET(value)	\
			((u16)HFA384x_CMD_AINFO_SET((u16)value))
#घोषणा		HFA384x_CMD_CMDCODE_SET(value)		((u16)(value))

#घोषणा		HFA384x_STATUS_RESULT_SET(value)	(((u16)(value)) << 8)

/* Host Maपूर्णांकained State Info */
#घोषणा HFA384x_STATE_PREINIT	0
#घोषणा HFA384x_STATE_INIT	1
#घोषणा HFA384x_STATE_RUNNING	2

/*-------------------------------------------------------------*/
/* Commonly used basic types */
काष्ठा hfa384x_bytestr अणु
	__le16 len;
	u8 data[];
पूर्ण __packed;

काष्ठा hfa384x_bytestr32 अणु
	__le16 len;
	u8 data[32];
पूर्ण __packed;

/*--------------------------------------------------------------------
 * Configuration Record Structures:
 *	Network Parameters, Static Configuration Entities
 *--------------------------------------------------------------------
 */

/*-- Hardware/Firmware Component Inक्रमmation ----------*/
काष्ठा hfa384x_compident अणु
	u16 id;
	u16 variant;
	u16 major;
	u16 minor;
पूर्ण __packed;

काष्ठा hfa384x_caplevel अणु
	u16 role;
	u16 id;
	u16 variant;
	u16 bottom;
	u16 top;
पूर्ण __packed;

/*-- Configuration Record: cnfAuthentication --*/
#घोषणा HFA384x_CNFAUTHENTICATION_OPENSYSTEM	0x0001
#घोषणा HFA384x_CNFAUTHENTICATION_SHAREDKEY	0x0002
#घोषणा HFA384x_CNFAUTHENTICATION_LEAP		0x0004

/*--------------------------------------------------------------------
 * Configuration Record Structures:
 *	Network Parameters, Dynamic Configuration Entities
 *--------------------------------------------------------------------
 */

#घोषणा HFA384x_CREATEIBSS_JOINCREATEIBSS          0

/*-- Configuration Record: HostScanRequest (data portion only) --*/
काष्ठा hfa384x_host_scan_request_data अणु
	__le16 channel_list;
	__le16 tx_rate;
	काष्ठा hfa384x_bytestr32 ssid;
पूर्ण __packed;

/*-- Configuration Record: JoinRequest (data portion only) --*/
काष्ठा hfa384x_join_request_data अणु
	u8 bssid[WLAN_BSSID_LEN];
	u16 channel;
पूर्ण __packed;

/*-- Configuration Record: authenticateStation (data portion only) --*/
काष्ठा hfa384x_authenticate_station_data अणु
	u8 address[ETH_ALEN];
	__le16 status;
	__le16 algorithm;
पूर्ण __packed;

/*-- Configuration Record: WPAData       (data portion only) --*/
काष्ठा hfa384x_wpa_data अणु
	__le16 datalen;
	u8 data[];		/* max 80 */
पूर्ण __packed;

/*--------------------------------------------------------------------
 * Inक्रमmation Record Structures: NIC Inक्रमmation
 *--------------------------------------------------------------------
 */

/*-- Inक्रमmation Record: DownLoadBuffer --*/
/* NOTE: The page and offset are in AUX क्रमmat */
काष्ठा hfa384x_करोwnloadbuffer अणु
	u16 page;
	u16 offset;
	u16 len;
पूर्ण __packed;

/*--------------------------------------------------------------------
 * Inक्रमmation Record Structures: NIC Inक्रमmation
 *--------------------------------------------------------------------
 */

#घोषणा HFA384x_PSTATUS_CONN_IBSS	((u16)3)

/*-- Inक्रमmation Record: commsquality --*/
काष्ठा hfa384x_commsquality अणु
	__le16 cq_curr_bss;
	__le16 asl_curr_bss;
	__le16 anl_curr_fc;
पूर्ण __packed;

/*-- Inक्रमmation Record: dmbcommsquality --*/
काष्ठा hfa384x_dbmcommsquality अणु
	u16 cq_dbm_curr_bss;
	u16 asl_dbm_curr_bss;
	u16 anl_dbm_curr_fc;
पूर्ण __packed;

/*--------------------------------------------------------------------
 * FRAME STRUCTURES: Communication Frames
 *--------------------------------------------------------------------
 * Communication Frames: Transmit Frames
 *--------------------------------------------------------------------
 */
/*-- Communication Frame: Transmit Frame Structure --*/
काष्ठा hfa384x_tx_frame अणु
	u16 status;
	u16 reserved1;
	u16 reserved2;
	u32 sw_support;
	u8 tx_retrycount;
	u8 tx_rate;
	u16 tx_control;

	/*-- 802.11 Header Inक्रमmation --*/

	u16 frame_control;
	u16 duration_id;
	u8 address1[6];
	u8 address2[6];
	u8 address3[6];
	u16 sequence_control;
	u8 address4[6];
	__le16 data_len;		/* little endian क्रमmat */

	/*-- 802.3 Header Inक्रमmation --*/

	u8 dest_addr[6];
	u8 src_addr[6];
	u16 data_length;	/* big endian क्रमmat */
पूर्ण __packed;
/*--------------------------------------------------------------------
 * Communication Frames: Field Masks क्रम Transmit Frames
 *--------------------------------------------------------------------
 */
/*-- Status Field --*/
#घोषणा		HFA384x_TXSTATUS_ACKERR			((u16)BIT(5))
#घोषणा		HFA384x_TXSTATUS_FORMERR		((u16)BIT(3))
#घोषणा		HFA384x_TXSTATUS_DISCON			((u16)BIT(2))
#घोषणा		HFA384x_TXSTATUS_AGEDERR		((u16)BIT(1))
#घोषणा		HFA384x_TXSTATUS_RETRYERR		((u16)BIT(0))
/*-- Transmit Control Field --*/
#घोषणा		HFA384x_TX_MACPORT			((u16)GENMASK(10, 8))
#घोषणा		HFA384x_TX_STRUCTYPE			((u16)GENMASK(4, 3))
#घोषणा		HFA384x_TX_TXEX				((u16)BIT(2))
#घोषणा		HFA384x_TX_TXOK				((u16)BIT(1))
/*--------------------------------------------------------------------
 * Communication Frames: Test/Get/Set Field Values क्रम Transmit Frames
 *--------------------------------------------------------------------
 */
/*-- Status Field --*/
#घोषणा HFA384x_TXSTATUS_ISERROR(v)	\
	(((u16)(v)) & \
	(HFA384x_TXSTATUS_ACKERR | HFA384x_TXSTATUS_FORMERR | \
	HFA384x_TXSTATUS_DISCON | HFA384x_TXSTATUS_AGEDERR | \
	HFA384x_TXSTATUS_RETRYERR))

#घोषणा	HFA384x_TX_SET(v, m, s)		((((u16)(v)) << ((u16)(s))) & ((u16)(m)))

#घोषणा	HFA384x_TX_MACPORT_SET(v)	HFA384x_TX_SET(v, HFA384x_TX_MACPORT, 8)
#घोषणा	HFA384x_TX_STRUCTYPE_SET(v)	HFA384x_TX_SET(v, \
						HFA384x_TX_STRUCTYPE, 3)
#घोषणा	HFA384x_TX_TXEX_SET(v)		HFA384x_TX_SET(v, HFA384x_TX_TXEX, 2)
#घोषणा	HFA384x_TX_TXOK_SET(v)		HFA384x_TX_SET(v, HFA384x_TX_TXOK, 1)
/*--------------------------------------------------------------------
 * Communication Frames: Receive Frames
 *--------------------------------------------------------------------
 */
/*-- Communication Frame: Receive Frame Structure --*/
काष्ठा hfa384x_rx_frame अणु
	/*-- MAC rx descriptor (hfa384x byte order) --*/
	u16 status;
	u32 समय;
	u8 silence;
	u8 संकेत;
	u8 rate;
	u8 rx_flow;
	u16 reserved1;
	u16 reserved2;

	/*-- 802.11 Header Inक्रमmation (802.11 byte order) --*/
	__le16 frame_control;
	u16 duration_id;
	u8 address1[6];
	u8 address2[6];
	u8 address3[6];
	u16 sequence_control;
	u8 address4[6];
	__le16 data_len;		/* hfa384x (little endian) क्रमmat */

	/*-- 802.3 Header Inक्रमmation --*/
	u8 dest_addr[6];
	u8 src_addr[6];
	u16 data_length;	/* IEEE? (big endian) क्रमmat */
पूर्ण __packed;
/*--------------------------------------------------------------------
 * Communication Frames: Field Masks क्रम Receive Frames
 *--------------------------------------------------------------------
 */

/*-- Status Fields --*/
#घोषणा		HFA384x_RXSTATUS_MACPORT		((u16)GENMASK(10, 8))
#घोषणा		HFA384x_RXSTATUS_FCSERR			((u16)BIT(0))
/*--------------------------------------------------------------------
 * Communication Frames: Test/Get/Set Field Values क्रम Receive Frames
 *--------------------------------------------------------------------
 */
#घोषणा		HFA384x_RXSTATUS_MACPORT_GET(value)	((u16)((((u16)(value)) \
					    & HFA384x_RXSTATUS_MACPORT) >> 8))
#घोषणा		HFA384x_RXSTATUS_ISFCSERR(value)	((u16)(((u16)(value)) \
						  & HFA384x_RXSTATUS_FCSERR))
/*--------------------------------------------------------------------
 * FRAME STRUCTURES: Inक्रमmation Types and Inक्रमmation Frame Structures
 *--------------------------------------------------------------------
 * Inक्रमmation Types
 *--------------------------------------------------------------------
 */
#घोषणा		HFA384x_IT_HANDOVERADDR			((u16)0xF000UL)
#घोषणा		HFA384x_IT_COMMTALLIES			((u16)0xF100UL)
#घोषणा		HFA384x_IT_SCANRESULTS			((u16)0xF101UL)
#घोषणा		HFA384x_IT_CHINFORESULTS		((u16)0xF102UL)
#घोषणा		HFA384x_IT_HOSTSCANRESULTS		((u16)0xF103UL)
#घोषणा		HFA384x_IT_LINKSTATUS			((u16)0xF200UL)
#घोषणा		HFA384x_IT_ASSOCSTATUS			((u16)0xF201UL)
#घोषणा		HFA384x_IT_AUTHREQ			((u16)0xF202UL)
#घोषणा		HFA384x_IT_PSUSERCNT			((u16)0xF203UL)
#घोषणा		HFA384x_IT_KEYIDCHANGED			((u16)0xF204UL)
#घोषणा		HFA384x_IT_ASSOCREQ			((u16)0xF205UL)
#घोषणा		HFA384x_IT_MICFAILURE			((u16)0xF206UL)

/*--------------------------------------------------------------------
 * Inक्रमmation Frames Structures
 *--------------------------------------------------------------------
 * Inक्रमmation Frames: Notअगरication Frame Structures
 *--------------------------------------------------------------------
 */

/*--  Inquiry Frame, Diagnose: Communication Tallies --*/
काष्ठा hfa384x_comm_tallies_16 अणु
	__le16 txunicastframes;
	__le16 txmulticastframes;
	__le16 txfragments;
	__le16 txunicastoctets;
	__le16 txmulticastoctets;
	__le16 txdeferredtrans;
	__le16 txsingleretryframes;
	__le16 txmultipleretryframes;
	__le16 txretrylimitexceeded;
	__le16 txdiscards;
	__le16 rxunicastframes;
	__le16 rxmulticastframes;
	__le16 rxfragments;
	__le16 rxunicastoctets;
	__le16 rxmulticastoctets;
	__le16 rxfcserrors;
	__le16 rxdiscardsnobuffer;
	__le16 txdiscardswrongsa;
	__le16 rxdiscardswepundecr;
	__le16 rxmsginmsgfrag;
	__le16 rxmsginbadmsgfrag;
पूर्ण __packed;

काष्ठा hfa384x_comm_tallies_32 अणु
	__le32 txunicastframes;
	__le32 txmulticastframes;
	__le32 txfragments;
	__le32 txunicastoctets;
	__le32 txmulticastoctets;
	__le32 txdeferredtrans;
	__le32 txsingleretryframes;
	__le32 txmultipleretryframes;
	__le32 txretrylimitexceeded;
	__le32 txdiscards;
	__le32 rxunicastframes;
	__le32 rxmulticastframes;
	__le32 rxfragments;
	__le32 rxunicastoctets;
	__le32 rxmulticastoctets;
	__le32 rxfcserrors;
	__le32 rxdiscardsnobuffer;
	__le32 txdiscardswrongsa;
	__le32 rxdiscardswepundecr;
	__le32 rxmsginmsgfrag;
	__le32 rxmsginbadmsgfrag;
पूर्ण __packed;

/*--  Inquiry Frame, Diagnose: Scan Results & Subfields--*/
काष्ठा hfa384x_scan_result_sub अणु
	u16 chid;
	u16 anl;
	u16 sl;
	u8 bssid[WLAN_BSSID_LEN];
	u16 bcnपूर्णांक;
	u16 capinfo;
	काष्ठा hfa384x_bytestr32 ssid;
	u8 supprates[10];	/* 802.11 info element */
	u16 proberesp_rate;
पूर्ण __packed;

काष्ठा hfa384x_scan_result अणु
	u16 rsvd;
	u16 scanreason;
	काष्ठा hfa384x_scan_result_sub result[HFA384x_SCANRESULT_MAX];
पूर्ण __packed;

/*--  Inquiry Frame, Diagnose: ChInfo Results & Subfields--*/
काष्ठा hfa384x_ch_info_result_sub अणु
	u16 chid;
	u16 anl;
	u16 pnl;
	u16 active;
पूर्ण __packed;

#घोषणा HFA384x_CHINFORESULT_BSSACTIVE	BIT(0)
#घोषणा HFA384x_CHINFORESULT_PCFACTIVE	BIT(1)

काष्ठा hfa384x_ch_info_result अणु
	u16 scanchannels;
	काष्ठा hfa384x_ch_info_result_sub result[HFA384x_CHINFORESULT_MAX];
पूर्ण __packed;

/*--  Inquiry Frame, Diagnose: Host Scan Results & Subfields--*/
काष्ठा hfa384x_hscan_result_sub अणु
	__le16 chid;
	__le16 anl;
	__le16 sl;
	u8 bssid[WLAN_BSSID_LEN];
	__le16 bcnपूर्णांक;
	__le16 capinfo;
	काष्ठा hfa384x_bytestr32 ssid;
	u8 supprates[10];	/* 802.11 info element */
	u16 proberesp_rate;
	__le16 atim;
पूर्ण __packed;

काष्ठा hfa384x_hscan_result अणु
	u16 nresult;
	u16 rsvd;
	काष्ठा hfa384x_hscan_result_sub result[HFA384x_HSCANRESULT_MAX];
पूर्ण __packed;

/*--  Unsolicited Frame, MAC Mgmt: LinkStatus --*/

#घोषणा HFA384x_LINK_NOTCONNECTED	((u16)0)
#घोषणा HFA384x_LINK_CONNECTED		((u16)1)
#घोषणा HFA384x_LINK_DISCONNECTED	((u16)2)
#घोषणा HFA384x_LINK_AP_CHANGE		((u16)3)
#घोषणा HFA384x_LINK_AP_OUTOFRANGE	((u16)4)
#घोषणा HFA384x_LINK_AP_INRANGE		((u16)5)
#घोषणा HFA384x_LINK_ASSOCFAIL		((u16)6)

काष्ठा hfa384x_link_status अणु
	__le16 linkstatus;
पूर्ण __packed;

/*--  Unsolicited Frame, MAC Mgmt: AssociationStatus (--*/

#घोषणा HFA384x_ASSOCSTATUS_STAASSOC	((u16)1)
#घोषणा HFA384x_ASSOCSTATUS_REASSOC	((u16)2)
#घोषणा HFA384x_ASSOCSTATUS_AUTHFAIL	((u16)5)

काष्ठा hfa384x_assoc_status अणु
	u16 assocstatus;
	u8 sta_addr[ETH_ALEN];
	/* old_ap_addr is only valid अगर assocstatus == 2 */
	u8 old_ap_addr[ETH_ALEN];
	u16 reason;
	u16 reserved;
पूर्ण __packed;

/*--  Unsolicited Frame, MAC Mgmt: AuthRequest (AP Only) --*/

काष्ठा hfa384x_auth_request अणु
	u8 sta_addr[ETH_ALEN];
	__le16 algorithm;
पूर्ण __packed;

/*--  Unsolicited Frame, MAC Mgmt: PSUserCount (AP Only) --*/

काष्ठा hfa384x_ps_user_count अणु
	__le16 usercnt;
पूर्ण __packed;

काष्ठा hfa384x_key_id_changed अणु
	u8 sta_addr[ETH_ALEN];
	u16 keyid;
पूर्ण __packed;

/*--  Collection of all Inf frames ---------------*/
जोड़ hfa384x_infodata अणु
	काष्ठा hfa384x_comm_tallies_16 commtallies16;
	काष्ठा hfa384x_comm_tallies_32 commtallies32;
	काष्ठा hfa384x_scan_result scanresult;
	काष्ठा hfa384x_ch_info_result chinक्रमesult;
	काष्ठा hfa384x_hscan_result hscanresult;
	काष्ठा hfa384x_link_status linkstatus;
	काष्ठा hfa384x_assoc_status assocstatus;
	काष्ठा hfa384x_auth_request authreq;
	काष्ठा hfa384x_ps_user_count psusercnt;
	काष्ठा hfa384x_key_id_changed keyidchanged;
पूर्ण __packed;

काष्ठा hfa384x_inf_frame अणु
	u16 framelen;
	u16 infotype;
	जोड़ hfa384x_infodata info;
पूर्ण __packed;

/*--------------------------------------------------------------------
 * USB Packet काष्ठाures and स्थिरants.
 *--------------------------------------------------------------------
 */

/* Should be sent to the bulkout endpoपूर्णांक */
#घोषणा HFA384x_USB_TXFRM	0
#घोषणा HFA384x_USB_CMDREQ	1
#घोषणा HFA384x_USB_WRIDREQ	2
#घोषणा HFA384x_USB_RRIDREQ	3
#घोषणा HFA384x_USB_WMEMREQ	4
#घोषणा HFA384x_USB_RMEMREQ	5

/* Received from the bulkin endpoपूर्णांक */
#घोषणा HFA384x_USB_ISTXFRM(a)	(((a) & 0x9000) == 0x1000)
#घोषणा HFA384x_USB_ISRXFRM(a)	(!((a) & 0x9000))
#घोषणा HFA384x_USB_INFOFRM	0x8000
#घोषणा HFA384x_USB_CMDRESP	0x8001
#घोषणा HFA384x_USB_WRIDRESP	0x8002
#घोषणा HFA384x_USB_RRIDRESP	0x8003
#घोषणा HFA384x_USB_WMEMRESP	0x8004
#घोषणा HFA384x_USB_RMEMRESP	0x8005
#घोषणा HFA384x_USB_BUFAVAIL	0x8006
#घोषणा HFA384x_USB_ERROR	0x8007

/*------------------------------------*/
/* Request (bulk OUT) packet contents */

काष्ठा hfa384x_usb_txfrm अणु
	काष्ठा hfa384x_tx_frame desc;
	u8 data[WLAN_DATA_MAXLEN];
पूर्ण __packed;

काष्ठा hfa384x_usb_cmdreq अणु
	__le16 type;
	__le16 cmd;
	__le16 parm0;
	__le16 parm1;
	__le16 parm2;
	u8 pad[54];
पूर्ण __packed;

काष्ठा hfa384x_usb_wridreq अणु
	__le16 type;
	__le16 frmlen;
	__le16 rid;
	u8 data[HFA384x_RIDDATA_MAXLEN];
पूर्ण __packed;

काष्ठा hfa384x_usb_rridreq अणु
	__le16 type;
	__le16 frmlen;
	__le16 rid;
	u8 pad[58];
पूर्ण __packed;

काष्ठा hfa384x_usb_wmemreq अणु
	__le16 type;
	__le16 frmlen;
	__le16 offset;
	__le16 page;
	u8 data[HFA384x_USB_RWMEM_MAXLEN];
पूर्ण __packed;

काष्ठा hfa384x_usb_rmemreq अणु
	__le16 type;
	__le16 frmlen;
	__le16 offset;
	__le16 page;
	u8 pad[56];
पूर्ण __packed;

/*------------------------------------*/
/* Response (bulk IN) packet contents */

काष्ठा hfa384x_usb_rxfrm अणु
	काष्ठा hfa384x_rx_frame desc;
	u8 data[WLAN_DATA_MAXLEN];
पूर्ण __packed;

काष्ठा hfa384x_usb_infofrm अणु
	u16 type;
	काष्ठा hfa384x_inf_frame info;
पूर्ण __packed;

काष्ठा hfa384x_usb_statusresp अणु
	u16 type;
	__le16 status;
	__le16 resp0;
	__le16 resp1;
	__le16 resp2;
पूर्ण __packed;

काष्ठा hfa384x_usb_rridresp अणु
	u16 type;
	__le16 frmlen;
	__le16 rid;
	u8 data[HFA384x_RIDDATA_MAXLEN];
पूर्ण __packed;

काष्ठा hfa384x_usb_rmemresp अणु
	u16 type;
	u16 frmlen;
	u8 data[HFA384x_USB_RWMEM_MAXLEN];
पूर्ण __packed;

काष्ठा hfa384x_usb_bufavail अणु
	u16 type;
	u16 frmlen;
पूर्ण __packed;

काष्ठा hfa384x_usb_error अणु
	u16 type;
	u16 errortype;
पूर्ण __packed;

/*----------------------------------------------------------*/
/* Unions क्रम packaging all the known packet types together */

जोड़ hfa384x_usbout अणु
	__le16 type;
	काष्ठा hfa384x_usb_txfrm txfrm;
	काष्ठा hfa384x_usb_cmdreq cmdreq;
	काष्ठा hfa384x_usb_wridreq wridreq;
	काष्ठा hfa384x_usb_rridreq rridreq;
	काष्ठा hfa384x_usb_wmemreq wmemreq;
	काष्ठा hfa384x_usb_rmemreq rmemreq;
पूर्ण __packed;

जोड़ hfa384x_usbin अणु
	__le16 type;
	काष्ठा hfa384x_usb_rxfrm rxfrm;
	काष्ठा hfa384x_usb_txfrm txfrm;
	काष्ठा hfa384x_usb_infofrm infofrm;
	काष्ठा hfa384x_usb_statusresp cmdresp;
	काष्ठा hfa384x_usb_statusresp wridresp;
	काष्ठा hfa384x_usb_rridresp rridresp;
	काष्ठा hfa384x_usb_statusresp wmemresp;
	काष्ठा hfa384x_usb_rmemresp rmemresp;
	काष्ठा hfa384x_usb_bufavail bufavail;
	काष्ठा hfa384x_usb_error usberror;
	u8 boguspad[3000];
पूर्ण __packed;

/*--------------------------------------------------------------------
 * PD record काष्ठाures.
 *--------------------------------------------------------------------
 */

काष्ठा hfa384x_pdr_pcb_partnum अणु
	u8 num[8];
पूर्ण __packed;

काष्ठा hfa384x_pdr_pcb_tracक्रमागत अणु
	u8 num[8];
पूर्ण __packed;

काष्ठा hfa384x_pdr_nic_serial अणु
	u8 num[12];
पूर्ण __packed;

काष्ठा hfa384x_pdr_mkk_measurements अणु
	द्विगुन carrier_freq;
	द्विगुन occupied_band;
	द्विगुन घातer_density;
	द्विगुन tx_spur_f1;
	द्विगुन tx_spur_f2;
	द्विगुन tx_spur_f3;
	द्विगुन tx_spur_f4;
	द्विगुन tx_spur_l1;
	द्विगुन tx_spur_l2;
	द्विगुन tx_spur_l3;
	द्विगुन tx_spur_l4;
	द्विगुन rx_spur_f1;
	द्विगुन rx_spur_f2;
	द्विगुन rx_spur_l1;
	द्विगुन rx_spur_l2;
पूर्ण __packed;

काष्ठा hfa384x_pdr_nic_ramsize अणु
	u8 size[12];		/* units of KB */
पूर्ण __packed;

काष्ठा hfa384x_pdr_mfisuprange अणु
	u16 id;
	u16 variant;
	u16 bottom;
	u16 top;
पूर्ण __packed;

काष्ठा hfa384x_pdr_cfisuprange अणु
	u16 id;
	u16 variant;
	u16 bottom;
	u16 top;
पूर्ण __packed;

काष्ठा hfa384x_pdr_nicid अणु
	u16 id;
	u16 variant;
	u16 major;
	u16 minor;
पूर्ण __packed;

काष्ठा hfa384x_pdr_refdac_measurements अणु
	u16 value[0];
पूर्ण __packed;

काष्ठा hfa384x_pdr_vgdac_measurements अणु
	u16 value[0];
पूर्ण __packed;

काष्ठा hfa384x_pdr_level_comp_measurements अणु
	u16 value[0];
पूर्ण __packed;

काष्ठा hfa384x_pdr_mac_address अणु
	u8 addr[6];
पूर्ण __packed;

काष्ठा hfa384x_pdr_mkk_callname अणु
	u8 callname[8];
पूर्ण __packed;

काष्ठा hfa384x_pdr_regकरोमुख्य अणु
	u16 numकरोमुख्यs;
	u16 करोमुख्य[5];
पूर्ण __packed;

काष्ठा hfa384x_pdr_allowed_channel अणु
	u16 ch_biपंचांगap;
पूर्ण __packed;

काष्ठा hfa384x_pdr_शेष_channel अणु
	u16 channel;
पूर्ण __packed;

काष्ठा hfa384x_pdr_privacy_option अणु
	u16 available;
पूर्ण __packed;

काष्ठा hfa384x_pdr_temptype अणु
	u16 type;
पूर्ण __packed;

काष्ठा hfa384x_pdr_refdac_setup अणु
	u16 ch_value[14];
पूर्ण __packed;

काष्ठा hfa384x_pdr_vgdac_setup अणु
	u16 ch_value[14];
पूर्ण __packed;

काष्ठा hfa384x_pdr_level_comp_setup अणु
	u16 ch_value[14];
पूर्ण __packed;

काष्ठा hfa384x_pdr_trimdac_setup अणु
	u16 trimidac;
	u16 trimqdac;
पूर्ण __packed;

काष्ठा hfa384x_pdr_अगरr_setting अणु
	u16 value[3];
पूर्ण __packed;

काष्ठा hfa384x_pdr_rfr_setting अणु
	u16 value[3];
पूर्ण __packed;

काष्ठा hfa384x_pdr_hfa3861_baseline अणु
	u16 value[50];
पूर्ण __packed;

काष्ठा hfa384x_pdr_hfa3861_shaकरोw अणु
	u32 value[32];
पूर्ण __packed;

काष्ठा hfa384x_pdr_hfa3861_अगरrf अणु
	u32 value[20];
पूर्ण __packed;

काष्ठा hfa384x_pdr_hfa3861_chcalsp अणु
	u16 value[14];
पूर्ण __packed;

काष्ठा hfa384x_pdr_hfa3861_chcali अणु
	u16 value[17];
पूर्ण __packed;

काष्ठा hfa384x_pdr_hfa3861_nic_config अणु
	u16 config_biपंचांगap;
पूर्ण __packed;

काष्ठा hfa384x_pdr_hfo_delay अणु
	u8 hfo_delay;
पूर्ण __packed;

काष्ठा hfa384x_pdr_hfa3861_manf_testsp अणु
	u16 value[30];
पूर्ण __packed;

काष्ठा hfa384x_pdr_hfa3861_manf_testi अणु
	u16 value[30];
पूर्ण __packed;

काष्ठा hfa384x_pdr_end_of_pda अणु
	u16 crc;
पूर्ण __packed;

काष्ठा hfa384x_pdrec अणु
	__le16 len;		/* in words */
	__le16 code;
	जोड़ pdr अणु
		काष्ठा hfa384x_pdr_pcb_partnum pcb_partnum;
		काष्ठा hfa384x_pdr_pcb_tracक्रमागत pcb_tracक्रमागत;
		काष्ठा hfa384x_pdr_nic_serial nic_serial;
		काष्ठा hfa384x_pdr_mkk_measurements mkk_measurements;
		काष्ठा hfa384x_pdr_nic_ramsize nic_ramsize;
		काष्ठा hfa384x_pdr_mfisuprange mfisuprange;
		काष्ठा hfa384x_pdr_cfisuprange cfisuprange;
		काष्ठा hfa384x_pdr_nicid nicid;
		काष्ठा hfa384x_pdr_refdac_measurements refdac_measurements;
		काष्ठा hfa384x_pdr_vgdac_measurements vgdac_measurements;
		काष्ठा hfa384x_pdr_level_comp_measurements level_compc_measurements;
		काष्ठा hfa384x_pdr_mac_address mac_address;
		काष्ठा hfa384x_pdr_mkk_callname mkk_callname;
		काष्ठा hfa384x_pdr_regकरोमुख्य regकरोमुख्य;
		काष्ठा hfa384x_pdr_allowed_channel allowed_channel;
		काष्ठा hfa384x_pdr_शेष_channel शेष_channel;
		काष्ठा hfa384x_pdr_privacy_option privacy_option;
		काष्ठा hfa384x_pdr_temptype temptype;
		काष्ठा hfa384x_pdr_refdac_setup refdac_setup;
		काष्ठा hfa384x_pdr_vgdac_setup vgdac_setup;
		काष्ठा hfa384x_pdr_level_comp_setup level_comp_setup;
		काष्ठा hfa384x_pdr_trimdac_setup trimdac_setup;
		काष्ठा hfa384x_pdr_अगरr_setting अगरr_setting;
		काष्ठा hfa384x_pdr_rfr_setting rfr_setting;
		काष्ठा hfa384x_pdr_hfa3861_baseline hfa3861_baseline;
		काष्ठा hfa384x_pdr_hfa3861_shaकरोw hfa3861_shaकरोw;
		काष्ठा hfa384x_pdr_hfa3861_अगरrf hfa3861_अगरrf;
		काष्ठा hfa384x_pdr_hfa3861_chcalsp hfa3861_chcalsp;
		काष्ठा hfa384x_pdr_hfa3861_chcali hfa3861_chcali;
		काष्ठा hfa384x_pdr_hfa3861_nic_config nic_config;
		काष्ठा hfa384x_pdr_hfo_delay hfo_delay;
		काष्ठा hfa384x_pdr_hfa3861_manf_testsp hfa3861_manf_testsp;
		काष्ठा hfa384x_pdr_hfa3861_manf_testi hfa3861_manf_testi;
		काष्ठा hfa384x_pdr_end_of_pda end_of_pda;

	पूर्ण data;
पूर्ण __packed;

#अगर_घोषित __KERNEL__
/*--------------------------------------------------------------------
 * ---  MAC state काष्ठाure, argument to all functions --
 * ---  Also, a collection of support types --
 *--------------------------------------------------------------------
 */
काष्ठा hfa384x_cmdresult अणु
	u16 status;
	u16 resp0;
	u16 resp1;
	u16 resp2;
पूर्ण;

/* USB Control Exchange (CTLX):
 *  A queue of the काष्ठाure below is मुख्यtained क्रम all of the
 *  Request/Response type USB packets supported by Prism2.
 */
/* The following hfa384x_* काष्ठाures are arguments to
 * the usercb() क्रम the dअगरferent CTLX types.
 */
काष्ठा hfa384x_rridresult अणु
	u16 rid;
	स्थिर व्योम *riddata;
	अचिन्हित पूर्णांक riddata_len;
पूर्ण;

क्रमागत ctlx_state अणु
	CTLX_START = 0,		/* Start state, not queued */

	CTLX_COMPLETE,		/* CTLX successfully completed */
	CTLX_REQ_FAILED,	/* OUT URB completed w/ error */

	CTLX_PENDING,		/* Queued, data valid */
	CTLX_REQ_SUBMITTED,	/* OUT URB submitted */
	CTLX_REQ_COMPLETE,	/* OUT URB complete */
	CTLX_RESP_COMPLETE	/* IN URB received */
पूर्ण;

काष्ठा hfa384x_usbctlx;
काष्ठा hfa384x;

प्रकार व्योम (*ctlx_cmdcb_t) (काष्ठा hfa384x *, स्थिर काष्ठा hfa384x_usbctlx *);

प्रकार व्योम (*ctlx_usercb_t) (काष्ठा hfa384x *hw,
			       व्योम *ctlxresult, व्योम *usercb_data);

काष्ठा hfa384x_usbctlx अणु
	काष्ठा list_head list;

	माप_प्रकार outbufsize;
	जोड़ hfa384x_usbout outbuf;	/* pkt buf क्रम OUT */
	जोड़ hfa384x_usbin inbuf;	/* pkt buf क्रम IN(a copy) */

	क्रमागत ctlx_state state;	/* Tracks running state */

	काष्ठा completion करोne;
	पूर्णांक reapable;		/* Food क्रम the reaper task */

	ctlx_cmdcb_t cmdcb;	/* Async command callback */
	ctlx_usercb_t usercb;	/* Async user callback, */
	व्योम *usercb_data;	/*  at CTLX completion  */
पूर्ण;

काष्ठा hfa384x_usbctlxq अणु
	spinlock_t lock;
	काष्ठा list_head pending;
	काष्ठा list_head active;
	काष्ठा list_head completing;
	काष्ठा list_head reapable;
पूर्ण;

काष्ठा hfa384x_metacmd अणु
	u16 cmd;

	u16 parm0;
	u16 parm1;
	u16 parm2;

	काष्ठा hfa384x_cmdresult result;
पूर्ण;

#घोषणा	MAX_GRP_ADDR		32
#घोषणा WLAN_COMMENT_MAX	80  /* Max. length of user comment string. */

#घोषणा WLAN_AUTH_MAX           60  /* Max. # of authenticated stations. */
#घोषणा WLAN_ACCESS_MAX		60  /* Max. # of stations in an access list. */
#घोषणा WLAN_ACCESS_NONE	0   /* No stations may be authenticated. */
#घोषणा WLAN_ACCESS_ALL		1   /* All stations may be authenticated. */
#घोषणा WLAN_ACCESS_ALLOW	2   /* Authenticate only "allowed" stations. */
#घोषणा WLAN_ACCESS_DENY	3   /* Do not authenticate "denied" stations. */

/* XXX These are going away ASAP */
काष्ठा prism2sta_authlist अणु
	अचिन्हित पूर्णांक cnt;
	u8 addr[WLAN_AUTH_MAX][ETH_ALEN];
	u8 assoc[WLAN_AUTH_MAX];
पूर्ण;

काष्ठा prism2sta_accesslist अणु
	अचिन्हित पूर्णांक modअगरy;
	अचिन्हित पूर्णांक cnt;
	u8 addr[WLAN_ACCESS_MAX][ETH_ALEN];
	अचिन्हित पूर्णांक cnt1;
	u8 addr1[WLAN_ACCESS_MAX][ETH_ALEN];
पूर्ण;

काष्ठा hfa384x अणु
	/* USB support data */
	काष्ठा usb_device *usb;
	काष्ठा urb rx_urb;
	काष्ठा sk_buff *rx_urb_skb;
	काष्ठा urb tx_urb;
	काष्ठा urb ctlx_urb;
	जोड़ hfa384x_usbout txbuff;
	काष्ठा hfa384x_usbctlxq ctlxq;
	काष्ठा समयr_list reqसमयr;
	काष्ठा समयr_list respसमयr;

	काष्ठा समयr_list throttle;

	काष्ठा tasklet_काष्ठा reaper_bh;
	काष्ठा tasklet_काष्ठा completion_bh;

	काष्ठा work_काष्ठा usb_work;

	अचिन्हित दीर्घ usb_flags;
#घोषणा THROTTLE_RX	0
#घोषणा THROTTLE_TX	1
#घोषणा WORK_RX_HALT	2
#घोषणा WORK_TX_HALT	3
#घोषणा WORK_RX_RESUME	4
#घोषणा WORK_TX_RESUME	5

	अचिन्हित लघु req_समयr_करोne:1;
	अचिन्हित लघु resp_समयr_करोne:1;

	पूर्णांक endp_in;
	पूर्णांक endp_out;

	पूर्णांक snअगरf_fcs;
	पूर्णांक snअगरf_channel;
	पूर्णांक snअगरf_truncate;
	पूर्णांक snअगरfhdr;

	रुको_queue_head_t cmdq;	/* रुको queue itself */

	/* Controller state */
	u32 state;
	u32 isap;
	u8 port_enabled[HFA384x_NUMPORTS_MAX];

	/* Download support */
	अचिन्हित पूर्णांक dlstate;
	काष्ठा hfa384x_करोwnloadbuffer bufinfo;
	u16 dlसमयout;

	पूर्णांक म_पूछोlag;		/* to संकेत scan complete */
	पूर्णांक join_ap;		/* are we joined to a specअगरic ap */
	पूर्णांक join_retries;	/* number of join retries till we fail */
	काष्ठा hfa384x_join_request_data joinreq;/* join request saved data */

	काष्ठा wlandevice *wlandev;
	/* Timer to allow क्रम the deferred processing of linkstatus messages */
	काष्ठा work_काष्ठा link_bh;

	काष्ठा work_काष्ठा commsqual_bh;
	काष्ठा hfa384x_commsquality qual;
	काष्ठा समयr_list commsqual_समयr;

	u16 link_status;
	u16 link_status_new;
	काष्ठा sk_buff_head authq;

	u32 txrate;

	/* And here we have stuff that used to be in priv */

	/* State variables */
	अचिन्हित पूर्णांक presnअगरf_port_type;
	u16 presnअगरf_wepflags;
	u32 करोt11_desired_bss_type;

	पूर्णांक dbmadjust;

	/* Group Addresses - right now, there are up to a total
	 * of MAX_GRP_ADDR group addresses
	 */
	u8 करोt11_grp_addr[MAX_GRP_ADDR][ETH_ALEN];
	अचिन्हित पूर्णांक करोt11_grpcnt;

	/* Component Identities */
	काष्ठा hfa384x_compident ident_nic;
	काष्ठा hfa384x_compident ident_pri_fw;
	काष्ठा hfa384x_compident ident_sta_fw;
	काष्ठा hfa384x_compident ident_ap_fw;
	u16 mm_mods;

	/* Supplier compatibility ranges */
	काष्ठा hfa384x_caplevel cap_sup_mfi;
	काष्ठा hfa384x_caplevel cap_sup_cfi;
	काष्ठा hfa384x_caplevel cap_sup_pri;
	काष्ठा hfa384x_caplevel cap_sup_sta;
	काष्ठा hfa384x_caplevel cap_sup_ap;

	/* Actor compatibility ranges */
	काष्ठा hfa384x_caplevel cap_act_pri_cfi; /*
						  * pri f/w to controller
						  * पूर्णांकerface
						  */

	काष्ठा hfa384x_caplevel cap_act_sta_cfi; /*
						  * sta f/w to controller
						  * पूर्णांकerface
						  */

	काष्ठा hfa384x_caplevel cap_act_sta_mfi; /*
						  * sta f/w to modem पूर्णांकerface
						  */

	काष्ठा hfa384x_caplevel cap_act_ap_cfi;	/*
						 * ap f/w to controller
						 * पूर्णांकerface
						 */

	काष्ठा hfa384x_caplevel cap_act_ap_mfi;	/* ap f/w to modem पूर्णांकerface */

	u32 psusercount;	/* Power save user count. */
	काष्ठा hfa384x_comm_tallies_32 tallies;	/* Communication tallies. */
	u8 comment[WLAN_COMMENT_MAX + 1];	/* User comment */

	/* Channel Info request results (AP only) */
	काष्ठा अणु
		atomic_t करोne;
		u8 count;
		काष्ठा hfa384x_ch_info_result results;
	पूर्ण channel_info;

	काष्ठा hfa384x_inf_frame *scanresults;

	काष्ठा prism2sta_authlist authlist;	/*
						 * Authenticated station list.
						 */
	अचिन्हित पूर्णांक accessmode;		/* Access mode. */
	काष्ठा prism2sta_accesslist allow;	/* Allowed station list. */
	काष्ठा prism2sta_accesslist deny;	/* Denied station list. */

पूर्ण;

व्योम hfa384x_create(काष्ठा hfa384x *hw, काष्ठा usb_device *usb);
व्योम hfa384x_destroy(काष्ठा hfa384x *hw);

पूर्णांक hfa384x_corereset(काष्ठा hfa384x *hw, पूर्णांक holdसमय, पूर्णांक settleसमय,
		      पूर्णांक genesis);
पूर्णांक hfa384x_drvr_disable(काष्ठा hfa384x *hw, u16 macport);
पूर्णांक hfa384x_drvr_enable(काष्ठा hfa384x *hw, u16 macport);
पूर्णांक hfa384x_drvr_flashdl_enable(काष्ठा hfa384x *hw);
पूर्णांक hfa384x_drvr_flashdl_disable(काष्ठा hfa384x *hw);
पूर्णांक hfa384x_drvr_flashdl_ग_लिखो(काष्ठा hfa384x *hw, u32 daddr, व्योम *buf,
			       u32 len);
पूर्णांक hfa384x_drvr_अ_लोonfig(काष्ठा hfa384x *hw, u16 rid, व्योम *buf, u16 len);
पूर्णांक hfa384x_drvr_ramdl_enable(काष्ठा hfa384x *hw, u32 exeaddr);
पूर्णांक hfa384x_drvr_ramdl_disable(काष्ठा hfa384x *hw);
पूर्णांक hfa384x_drvr_ramdl_ग_लिखो(काष्ठा hfa384x *hw, u32 daddr, व्योम *buf, u32 len);
पूर्णांक hfa384x_drvr_पढ़ोpda(काष्ठा hfa384x *hw, व्योम *buf, अचिन्हित पूर्णांक len);
पूर्णांक hfa384x_drvr_setconfig(काष्ठा hfa384x *hw, u16 rid, व्योम *buf, u16 len);

अटल अंतरभूत पूर्णांक
hfa384x_drvr_अ_लोonfig16(काष्ठा hfa384x *hw, u16 rid, व्योम *val)
अणु
	पूर्णांक result = 0;

	result = hfa384x_drvr_अ_लोonfig(hw, rid, val, माप(u16));
	अगर (result == 0)
		le16_to_cpus(val);
	वापस result;
पूर्ण

अटल अंतरभूत पूर्णांक hfa384x_drvr_setconfig16(काष्ठा hfa384x *hw, u16 rid, u16 val)
अणु
	__le16 value = cpu_to_le16(val);

	वापस hfa384x_drvr_setconfig(hw, rid, &value, माप(value));
पूर्ण

पूर्णांक
hfa384x_drvr_setconfig_async(काष्ठा hfa384x *hw,
			     u16 rid,
			     व्योम *buf,
			     u16 len, ctlx_usercb_t usercb, व्योम *usercb_data);

अटल अंतरभूत पूर्णांक
hfa384x_drvr_setconfig16_async(काष्ठा hfa384x *hw, u16 rid, u16 val)
अणु
	__le16 value = cpu_to_le16(val);

	वापस hfa384x_drvr_setconfig_async(hw, rid, &value, माप(value),
					    शून्य, शून्य);
पूर्ण

पूर्णांक hfa384x_drvr_start(काष्ठा hfa384x *hw);
पूर्णांक hfa384x_drvr_stop(काष्ठा hfa384x *hw);
पूर्णांक
hfa384x_drvr_txframe(काष्ठा hfa384x *hw, काष्ठा sk_buff *skb,
		     जोड़ p80211_hdr *p80211_hdr,
		     काष्ठा p80211_metawep *p80211_wep);
व्योम hfa384x_tx_समयout(काष्ठा wlandevice *wlandev);

पूर्णांक hfa384x_cmd_initialize(काष्ठा hfa384x *hw);
पूर्णांक hfa384x_cmd_enable(काष्ठा hfa384x *hw, u16 macport);
पूर्णांक hfa384x_cmd_disable(काष्ठा hfa384x *hw, u16 macport);
पूर्णांक hfa384x_cmd_allocate(काष्ठा hfa384x *hw, u16 len);
पूर्णांक hfa384x_cmd_monitor(काष्ठा hfa384x *hw, u16 enable);
पूर्णांक
hfa384x_cmd_करोwnload(काष्ठा hfa384x *hw,
		     u16 mode, u16 lowaddr, u16 highaddr, u16 codelen);

#पूर्ण_अगर /*__KERNEL__ */

#पूर्ण_अगर /*_HFA384x_H */
