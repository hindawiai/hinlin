<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/
#अगर_अघोषित __RTL8712_HAL_H__
#घोषणा __RTL8712_HAL_H__

क्रमागत _HW_VERSION अणु
	RTL8712_FPGA,
	RTL8712_1stCUT,	/*A Cut (RTL8712_ASIC)*/
	RTL8712_2ndCUT,	/*B Cut*/
	RTL8712_3rdCUT,	/*C Cut*/
पूर्ण;

क्रमागत _LOOPBACK_TYPE अणु
	RTL8712_AIR_TRX = 0,
	RTL8712_MAC_LBK,
	RTL8712_BB_LBK,
	RTL8712_MAC_FW_LBK = 4,
	RTL8712_BB_FW_LBK = 8,
पूर्ण;

क्रमागत RTL871X_HCI_TYPE अणु
	RTL8712_SDIO,
	RTL8712_USB,
पूर्ण;

क्रमागत RTL8712_RF_CONFIG अणु
	RTL8712_RF_1T1R,
	RTL8712_RF_1T2R,
	RTL8712_RF_2T2R
पूर्ण;

क्रमागत _RTL8712_HCI_TYPE_ अणु
	RTL8712_HCI_TYPE_PCIE = 0x01,
	RTL8712_HCI_TYPE_AP_PCIE = 0x81,
	RTL8712_HCI_TYPE_USB = 0x02,
	RTL8712_HCI_TYPE_92USB = 0x02,
	RTL8712_HCI_TYPE_AP_USB = 0x82,
	RTL8712_HCI_TYPE_72USB = 0x12,
	RTL8712_HCI_TYPE_SDIO = 0x04,
	RTL8712_HCI_TYPE_72SDIO = 0x14
पूर्ण;

काष्ठा fw_priv अणु   /*8-bytes alignment required*/
	/*--- दीर्घ word 0 ----*/
	अचिन्हित अक्षर signature_0;  /*0x12: CE product, 0x92: IT product*/
	अचिन्हित अक्षर signature_1;  /*0x87: CE product, 0x81: IT product*/
	अचिन्हित अक्षर hci_sel; /*0x81: PCI-AP, 01:PCIe, 02: 92S-U, 0x82: USB-AP,
				* 0x12: 72S-U, 03:SDIO
				*/
	अचिन्हित अक्षर chip_version; /*the same value as रेजिस्टर value*/
	अचिन्हित अक्षर customer_ID_0; /*customer  ID low byte*/
	अचिन्हित अक्षर customer_ID_1; /*customer  ID high byte*/
	अचिन्हित अक्षर rf_config;  /*0x11:  1T1R, 0x12: 1T2R, 0x92: 1T2R turbo,
				   * 0x22: 2T2R
				   */
	अचिन्हित अक्षर usb_ep_num;  /* 4: 4EP, 6: 6EP, 11: 11EP*/
	/*--- दीर्घ word 1 ----*/
	अचिन्हित अक्षर regulatory_class_0; /*regulatory class bit map 0*/
	अचिन्हित अक्षर regulatory_class_1; /*regulatory class bit map 1*/
	अचिन्हित अक्षर regulatory_class_2; /*regulatory class bit map 2*/
	अचिन्हित अक्षर regulatory_class_3; /*regulatory class bit map 3*/
	अचिन्हित अक्षर rfपूर्णांकfs;    /* 0:SWSI, 1:HWSI, 2:HWPI*/
	अचिन्हित अक्षर def_nettype;
	अचिन्हित अक्षर turbo_mode;
	अचिन्हित अक्षर low_घातer_mode;/* 0: normal mode, 1: low घातer mode*/
	/*--- दीर्घ word 2 ----*/
	अचिन्हित अक्षर lbk_mode; /*0x00: normal, 0x03: MACLBK, 0x01: PHYLBK*/
	अचिन्हित अक्षर mp_mode; /* 1: क्रम MP use, 0: क्रम normal driver */
	अचिन्हित अक्षर vcs_type; /* 0:off 1:on 2:स्वतः */
	अचिन्हित अक्षर vcs_mode; /* 1:RTS/CTS 2:CTS to self */
	अचिन्हित अक्षर rsvd022;
	अचिन्हित अक्षर rsvd023;
	अचिन्हित अक्षर rsvd024;
	अचिन्हित अक्षर rsvd025;
	/*--- दीर्घ word 3 ----*/
	अचिन्हित अक्षर qos_en;    /*1: QoS enable*/
	अचिन्हित अक्षर bw_40MHz_en;   /*1: 40MHz BW enable*/
	अचिन्हित अक्षर AMSDU2AMPDU_en;   /*1: 4181 convert AMSDU to AMPDU,
					 * 0: disable
					 */
	अचिन्हित अक्षर AMPDU_en;   /*1: 11n AMPDU enable*/
	अचिन्हित अक्षर rate_control_offload; /*1: FW offloads,0: driver handles*/
	अचिन्हित अक्षर aggregation_offload;  /*1: FW offloads,0: driver handles*/
	अचिन्हित अक्षर rsvd030;
	अचिन्हित अक्षर rsvd031;
	/*--- दीर्घ word 4 ----*/
	अचिन्हित अक्षर beacon_offload;   /* 1. FW offloads, 0: driver handles*/
	अचिन्हित अक्षर MLME_offload;   /* 2. FW offloads, 0: driver handles*/
	अचिन्हित अक्षर hwpc_offload;   /* 3. FW offloads, 0: driver handles*/
	अचिन्हित अक्षर tcp_checksum_offload; /*4. FW offloads,0: driver handles*/
	अचिन्हित अक्षर tcp_offload;    /* 5. FW offloads, 0: driver handles*/
	अचिन्हित अक्षर ps_control_offload; /* 6. FW offloads, 0: driver handles*/
	अचिन्हित अक्षर WWLAN_offload;   /* 7. FW offloads, 0: driver handles*/
	अचिन्हित अक्षर rsvd040;
	/*--- दीर्घ word 5 ----*/
	अचिन्हित अक्षर tcp_tx_frame_len_L;  /*tcp tx packet length low byte*/
	अचिन्हित अक्षर tcp_tx_frame_len_H;  /*tcp tx packet length high byte*/
	अचिन्हित अक्षर tcp_rx_frame_len_L;  /*tcp rx packet length low byte*/
	अचिन्हित अक्षर tcp_rx_frame_len_H;  /*tcp rx packet length high byte*/
	अचिन्हित अक्षर rsvd050;
	अचिन्हित अक्षर rsvd051;
	अचिन्हित अक्षर rsvd052;
	अचिन्हित अक्षर rsvd053;
पूर्ण;

काष्ठा fw_hdr अणु/*8-byte alignment required*/
	अचिन्हित लघु	signature;
	अचिन्हित लघु	version;	/* 0x8000 ~ 0x8FFF क्रम FPGA version,
					 * 0x0000 ~ 0x7FFF क्रम ASIC version,
					 */
	अचिन्हित पूर्णांक		dmem_size;    /*define the size of boot loader*/
	अचिन्हित पूर्णांक		img_IMEM_size; /*define the size of FW in IMEM*/
	अचिन्हित पूर्णांक		img_SRAM_size; /*define the size of FW in SRAM*/
	अचिन्हित पूर्णांक		fw_priv_sz; /*define the size of DMEM variable*/
	अचिन्हित लघु	efuse_addr;
	अचिन्हित लघु	h2ccnd_resp_addr;
	अचिन्हित पूर्णांक		SVNRevision;
	अचिन्हित पूर्णांक		release_समय; /*Mon:Day:Hr:Min*/
	काष्ठा fw_priv	fwpriv;
पूर्ण;

काष्ठा hal_priv अणु
	/*Endpoपूर्णांक handles*/
	काष्ठा  net_device *pipehdls_r8712[10];
	u8 (*hal_bus_init)(काष्ठा _adapter *adapter);
पूर्ण;

uपूर्णांक	 rtl8712_hal_init(काष्ठा _adapter *padapter);
पूर्णांक rtl871x_load_fw(काष्ठा _adapter *padapter);

#पूर्ण_अगर
