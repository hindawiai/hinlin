<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __INC_ODM_REGCONFIG_H_8723B
#घोषणा __INC_ODM_REGCONFIG_H_8723B

व्योम odm_ConfigRFReg_8723B(काष्ठा dm_odm_t *pDM_Odm,
			   u32 Addr,
			   u32 Data,
			   क्रमागत odm_rf_radio_path_e RF_PATH,
			   u32 RegAddr
);

व्योम odm_ConfigRF_RadioA_8723B(काष्ठा dm_odm_t *pDM_Odm, u32 Addr, u32 Data);

व्योम odm_ConfigMAC_8723B(काष्ठा dm_odm_t *pDM_Odm, u32 Addr, u8 Data);

व्योम odm_ConfigBB_AGC_8723B(काष्ठा dm_odm_t *pDM_Odm,
			    u32 Addr,
			    u32 Biपंचांगask,
			    u32 Data
);

व्योम odm_ConfigBB_PHY_REG_PG_8723B(काष्ठा dm_odm_t *pDM_Odm,
				   u32 Band,
				   u32 RfPath,
				   u32 TxNum,
				   u32 Addr,
				   u32 Biपंचांगask,
				   u32 Data
);

व्योम odm_ConfigBB_PHY_8723B(काष्ठा dm_odm_t *pDM_Odm,
			    u32 Addr,
			    u32 Biपंचांगask,
			    u32 Data
);

व्योम odm_ConfigBB_TXPWR_LMT_8723B(काष्ठा dm_odm_t *pDM_Odm,
				  u8 *Regulation,
				  u8 *Band,
				  u8 *Bandwidth,
				  u8 *RateSection,
				  u8 *RfPath,
				  u8 *Channel,
				  u8 *PowerLimit
);

#पूर्ण_अगर
