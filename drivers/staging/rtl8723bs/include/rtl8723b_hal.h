<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __RTL8723B_HAL_H__
#घोषणा __RTL8723B_HAL_H__

#समावेश "hal_data.h"

#समावेश "rtl8723b_spec.h"
#समावेश "rtl8723b_rf.h"
#समावेश "rtl8723b_dm.h"
#समावेश "rtl8723b_recv.h"
#समावेश "rtl8723b_xmit.h"
#समावेश "rtl8723b_cmd.h"
#समावेश "rtw_mp.h"
#समावेश "hal_pwr_seq.h"
#समावेश "hal_phy_reg_8723b.h"
#समावेश "hal_phy_cfg.h"

/*  */
/* RTL8723B From header */
/*  */

#घोषणा FW_8723B_SIZE          0x8000
#घोषणा FW_8723B_START_ADDRESS 0x1000
#घोषणा FW_8723B_END_ADDRESS   0x1FFF /* 0x5FFF */

#घोषणा IS_FW_HEADER_EXIST_8723B(fw_hdr) \
	((le16_to_cpu(fw_hdr->signature) & 0xFFF0) == 0x5300)

काष्ठा rt_firmware अणु
	u32 fw_length;
	u8 *fw_buffer_sz;
पूर्ण;

/* This काष्ठाure must be carefully byte-ordered. */
काष्ठा rt_firmware_hdr अणु
	/*  8-byte alinment required */

	/*  LONG WORD 0 ---- */
	__le16 signature;  /* 92C0: test chip; 92C, 88C0: test chip;
			    * 88C1: MP A-cut; 92C1: MP A-cut
			    */
	u8 category;	   /* AP/NIC and USB/PCI */
	u8 function;	   /* Reserved क्रम dअगरferent FW function indications,
			    * क्रम further use when driver needs to करोwnload
			    * dअगरferent FW in dअगरferent conditions.
			    */
	__le16 version;    /* FW Version */
	__le16 subversion; /* FW Subversion, शेष 0x00 */

	/*  LONG WORD 1 ---- */
	u8 month;  /* Release समय Month field */
	u8 date;   /* Release समय Date field */
	u8 hour;   /* Release समय Hour field */
	u8 minute; /* Release समय Minute field */

	__le16 ram_code_size; /* The size of RAM code */
	__le16 rsvd2;

	/*  LONG WORD 2 ---- */
	__le32 svn_idx;	/* The SVN entry index */
	__le32 rsvd3;

	/*  LONG WORD 3 ---- */
	__le32 rsvd4;
	__le32 rsvd5;
पूर्ण;

#घोषणा DRIVER_EARLY_INT_TIME_8723B  0x05
#घोषणा BCN_DMA_ATIME_INT_TIME_8723B 0x02

/* क्रम 8723B */
/* TX 32K, RX 16K, Page size 128B क्रम TX, 8B क्रम RX */
#घोषणा PAGE_SIZE_TX_8723B 128
#घोषणा PAGE_SIZE_RX_8723B 8

#घोषणा RX_DMA_SIZE_8723B          0x4000 /* 16K */
#घोषणा RX_DMA_RESERVED_SIZE_8723B 0x80   /* 128B, reserved क्रम tx report */
#घोषणा RX_DMA_BOUNDARY_8723B \
	(RX_DMA_SIZE_8723B - RX_DMA_RESERVED_SIZE_8723B - 1)

/* Note: We will भागide number of pages equally क्रम each queue other than the
 * खुला queue!
 */

/* For General Reserved Page Number(Beacon Queue is reserved page) */
/* Beacon:2, PS-Poll:1, Null Data:1, Qos Null Data:1, BT Qos Null Data:1 */
#घोषणा BCNQ_PAGE_NUM_8723B  0x08
#घोषणा BCNQ1_PAGE_NUM_8723B 0x00

#घोषणा MAX_RX_DMA_BUFFER_SIZE_8723B 0x2800 /* RX 10K */

/* For WoWLan, more reserved page */
/* ARP Rsp:1, RWC:1, GTK Info:1, GTK RSP:2, GTK EXT MEM:2, PNO: 6 */
#घोषणा WOWLAN_PAGE_NUM_8723B 0x00

#घोषणा TX_TOTAL_PAGE_NUMBER_8723B     \
	(0xFF - BCNQ_PAGE_NUM_8723B  - \
		BCNQ1_PAGE_NUM_8723B - \
		WOWLAN_PAGE_NUM_8723B)
#घोषणा TX_PAGE_BOUNDARY_8723B (TX_TOTAL_PAGE_NUMBER_8723B + 1)

#घोषणा WMM_NORMAL_TX_TOTAL_PAGE_NUMBER_8723B TX_TOTAL_PAGE_NUMBER_8723B
#घोषणा WMM_NORMAL_TX_PAGE_BOUNDARY_8723B \
	(WMM_NORMAL_TX_TOTAL_PAGE_NUMBER_8723B + 1)

/* For Normal Chip Setting */
/* (HPQ + LPQ + NPQ + PUBQ) shall be TX_TOTAL_PAGE_NUMBER_8723B */
#घोषणा NORMAL_PAGE_NUM_HPQ_8723B 0x0C
#घोषणा NORMAL_PAGE_NUM_LPQ_8723B 0x02
#घोषणा NORMAL_PAGE_NUM_NPQ_8723B 0x02

/*  Note: For Normal Chip Setting, modअगरy later */
#घोषणा WMM_NORMAL_PAGE_NUM_HPQ_8723B 0x30
#घोषणा WMM_NORMAL_PAGE_NUM_LPQ_8723B 0x20
#घोषणा WMM_NORMAL_PAGE_NUM_NPQ_8723B 0x20

#समावेश "HalVerDef.h"
#समावेश "hal_com.h"

#घोषणा EFUSE_OOB_PROTECT_BYTES 15

#घोषणा HAL_EFUSE_MEMORY

#घोषणा HWSET_MAX_SIZE_8723B         512
#घोषणा EFUSE_REAL_CONTENT_LEN_8723B 512
#घोषणा EFUSE_MAP_LEN_8723B          512
#घोषणा EFUSE_MAX_SECTION_8723B      64

#घोषणा EFUSE_IC_ID_OFFSET 506 /* For some inferiority IC purpose.
				* Added by Roger, 2009.09.02.
				*/
#घोषणा AVAILABLE_EFUSE_ADDR(addr) (addr < EFUSE_REAL_CONTENT_LEN_8723B)

#घोषणा EFUSE_ACCESS_ON  0x69 /* For RTL8723 only. */
#घोषणा EFUSE_ACCESS_OFF 0x00 /* For RTL8723 only. */

/*  */
/* EFUSE क्रम BT definition */
/*  */
#घोषणा EFUSE_BT_REAL_BANK_CONTENT_LEN 512
#घोषणा EFUSE_BT_REAL_CONTENT_LEN      1536 /* 512*3 */
#घोषणा EFUSE_BT_MAP_LEN               1024 /* 1k bytes */
#घोषणा EFUSE_BT_MAX_SECTION           128  /* 1024/8 */

#घोषणा EFUSE_PROTECT_BYTES_BANK 16

/* Description: Determine the types of C2H events that are the same in driver
 * and FW; First स्थिरructed by tynli. 2009.10.09.
 */
क्रमागत अणु
	C2H_DBG = 0,
	C2H_TSF = 1,
	C2H_AP_RPT_RSP = 2,
	C2H_CCX_TX_RPT = 3, /* The FW notअगरy the report
			     * of the specअगरic tx packet.
			     */
	C2H_BT_RSSI = 4,
	C2H_BT_OP_MODE = 5,
	C2H_EXT_RA_RPT = 6,
	C2H_8723B_BT_INFO = 9,
	C2H_HW_INFO_EXCH = 10,
	C2H_8723B_BT_MP_INFO = 11,
	MAX_C2HEVENT
पूर्ण;

काष्ठा c2h_evt_hdr_t अणु
	u8 CmdID;
	u8 CmdLen;
	u8 CmdSeq;
पूर्ण __attribute__((__packed__));

क्रमागत अणु /* tag_Package_Definition */
	PACKAGE_DEFAULT,
	PACKAGE_QFN68,
	PACKAGE_TFBGA90,
	PACKAGE_TFBGA80,
	PACKAGE_TFBGA79
पूर्ण;

#घोषणा INCLUDE_MULTI_FUNC_BT(_Adapter)  \
	(GET_HAL_DATA(_Adapter)->MultiFunc & RT_MULTI_FUNC_BT)
#घोषणा INCLUDE_MULTI_FUNC_GPS(_Adapter) \
	(GET_HAL_DATA(_Adapter)->MultiFunc & RT_MULTI_FUNC_GPS)

/*  rtl8723a_hal_init.c */
s32 rtl8723b_FirmwareDownload(काष्ठा adapter *padapter, bool  bUsedWoWLANFw);
व्योम rtl8723b_FirmwareSelfReset(काष्ठा adapter *padapter);
व्योम rtl8723b_InitializeFirmwareVars(काष्ठा adapter *padapter);

व्योम rtl8723b_InitAntenna_Selection(काष्ठा adapter *padapter);
व्योम rtl8723b_init_शेष_value(काष्ठा adapter *padapter);

s32 rtl8723b_InitLLTTable(काष्ठा adapter *padapter);

/*  EFuse */
u8 GetEEPROMSize8723B(काष्ठा adapter *padapter);
व्योम Hal_InitPGData(काष्ठा adapter *padapter, u8 *PROMContent);
व्योम Hal_EfuseParseIDCode(काष्ठा adapter *padapter, u8 *hwinfo);
व्योम Hal_EfuseParseTxPowerInfo_8723B(काष्ठा adapter *padapter, u8 *PROMContent,
				     bool AutoLoadFail);
व्योम Hal_EfuseParseBTCoexistInfo_8723B(काष्ठा adapter *padapter, u8 *hwinfo,
				       bool AutoLoadFail);
व्योम Hal_EfuseParseEEPROMVer_8723B(काष्ठा adapter *padapter, u8 *hwinfo,
				   bool AutoLoadFail);
व्योम Hal_EfuseParseChnlPlan_8723B(काष्ठा adapter *padapter, u8 *hwinfo,
				  bool AutoLoadFail);
व्योम Hal_EfuseParseCustomerID_8723B(काष्ठा adapter *padapter, u8 *hwinfo,
				    bool AutoLoadFail);
व्योम Hal_EfuseParseAntennaDiversity_8723B(काष्ठा adapter *padapter, u8 *hwinfo,
					  bool AutoLoadFail);
व्योम Hal_EfuseParseXtal_8723B(काष्ठा adapter *padapter, u8 *hwinfo,
			      bool AutoLoadFail);
व्योम Hal_EfuseParseThermalMeter_8723B(काष्ठा adapter *padapter, u8 *hwinfo,
				      u8 AutoLoadFail);
व्योम Hal_EfuseParsePackageType_8723B(काष्ठा adapter *padapter, u8 *hwinfo,
				     bool AutoLoadFail);
व्योम Hal_EfuseParseVoltage_8723B(काष्ठा adapter *padapter, u8 *hwinfo,
				 bool AutoLoadFail);

व्योम C2HPacketHandler_8723B(काष्ठा adapter *padapter, u8 *pbuffer, u16 length);

व्योम rtl8723b_set_hal_ops(काष्ठा hal_ops *pHalFunc);
व्योम SetHwReg8723B(काष्ठा adapter *padapter, u8 variable, u8 *val);
व्योम GetHwReg8723B(काष्ठा adapter *padapter, u8 variable, u8 *val);
u8 SetHalDefVar8723B(काष्ठा adapter *padapter, क्रमागत hal_def_variable variable,
		     व्योम *pval);
u8 GetHalDefVar8723B(काष्ठा adapter *padapter, क्रमागत hal_def_variable variable,
		     व्योम *pval);

/*  रेजिस्टर */
व्योम rtl8723b_InitBeaconParameters(काष्ठा adapter *padapter);
व्योम _InitBurstPktLen_8723BS(काष्ठा adapter *adapter);
व्योम _8051Reset8723(काष्ठा adapter *padapter);

व्योम rtl8723b_start_thपढ़ो(काष्ठा adapter *padapter);
व्योम rtl8723b_stop_thपढ़ो(काष्ठा adapter *padapter);

पूर्णांक FirmwareDownloadBT(काष्ठा adapter *adapter, काष्ठा rt_firmware *firmware);

व्योम CCX_FwC2HTxRpt_8723b(काष्ठा adapter *padapter, u8 *pdata, u8 len);
s32 c2h_id_filter_ccx_8723b(u8 *buf);
s32 c2h_handler_8723b(काष्ठा adapter *padapter, u8 *pC2hEvent);
u8 MRateToHwRate8723B(u8 rate);
u8 HwRateToMRate8723B(u8 rate);

व्योम Hal_ReadRFGainOffset(काष्ठा adapter *padapter, u8 *hwinfo,
			  bool AutoLoadFail);

#पूर्ण_अगर
