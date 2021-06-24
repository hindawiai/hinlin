<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _R819XU_PHY_H
#घोषणा _R819XU_PHY_H

/* Channel चयन: The size of command tables क्रम चयन channel */
#घोषणा MAX_PRECMD_CNT 16
#घोषणा MAX_RFDEPENDCMD_CNT 16
#घोषणा MAX_POSTCMD_CNT 16

क्रमागत baseband_config_type अणु
	BASEBAND_CONFIG_PHY_REG = 0,			//Radio Path A
	BASEBAND_CONFIG_AGC_TAB = 1,			//Radio Path B
पूर्ण;

क्रमागत चयन_chan_cmd_id अणु
	CMD_ID_END,
	CMD_ID_SET_TX_PWR_LEVEL,
	CMD_ID_WRITE_PORT_ULONG,
	CMD_ID_WRITE_PORT_USHORT,
	CMD_ID_WRITE_PORT_UCHAR,
	CMD_ID_RF_WRITE_REG,
पूर्ण;

/* -----------------------Define काष्ठाure---------------------- */
/* 1. Switch channel related */
काष्ठा sw_chnl_cmd अणु
	क्रमागत चयन_chan_cmd_id	cmd_id;
	u32		        para_1;
	u32		        para_2;
	u32		        ms_delay;
पूर्ण __packed;

क्रमागत hw90_block_e अणु
	HW90_BLOCK_MAC = 0,
	HW90_BLOCK_PHY0 = 1,
	HW90_BLOCK_PHY1 = 2,
	HW90_BLOCK_RF = 3,
	HW90_BLOCK_MAXIMUM = 4, /* Never use this */
पूर्ण;

क्रमागत rf90_radio_path_e अणु
	RF90_PATH_A = 0,			/* Radio Path A */
	RF90_PATH_B = 1,			/* Radio Path B */
	RF90_PATH_C = 2,			/* Radio Path C */
	RF90_PATH_D = 3,			/* Radio Path D */
	RF90_PATH_MAX				/* Max RF number 92 support */
पूर्ण;

u8 rtl8192_phy_CheckIsLegalRFPath(काष्ठा net_device *dev, u32 e_rfpath);
व्योम rtl8192_setBBreg(काष्ठा net_device *dev, u32 reg_addr,
		      u32 biपंचांगask, u32 data);
u32 rtl8192_QueryBBReg(काष्ठा net_device *dev, u32 reg_addr, u32 biपंचांगask);
व्योम rtl8192_phy_SetRFReg(काष्ठा net_device *dev,
			  क्रमागत rf90_radio_path_e e_rfpath,
			  u32 reg_addr, u32 biपंचांगask, u32 data);
u32 rtl8192_phy_QueryRFReg(काष्ठा net_device *dev,
			   क्रमागत rf90_radio_path_e e_rfpath,
			   u32 reg_addr, u32 biपंचांगask);
व्योम rtl8192_phy_configmac(काष्ठा net_device *dev);
u8 rtl8192_phy_checkBBAndRF(काष्ठा net_device *dev,
			    क्रमागत hw90_block_e CheckBlock,
			    क्रमागत rf90_radio_path_e e_rfpath);
व्योम rtl8192_BBConfig(काष्ठा net_device *dev);
व्योम rtl8192_phy_getTxPower(काष्ठा net_device *dev);
व्योम rtl8192_phy_setTxPower(काष्ठा net_device *dev, u8 channel);
व्योम rtl8192_phy_RFConfig(काष्ठा net_device *dev);
व्योम rtl8192_phy_updateInitGain(काष्ठा net_device *dev);
u8 rtl8192_phy_ConfigRFWithHeaderFile(काष्ठा net_device *dev,
				      क्रमागत rf90_radio_path_e e_rfpath);

u8 rtl8192_phy_SwChnl(काष्ठा net_device *dev, u8 channel);
व्योम rtl8192_SetBWMode(काष्ठा net_device *dev,
		       क्रमागत ht_channel_width bandwidth,
		       क्रमागत ht_extension_chan_offset offset);
व्योम rtl8192_SwChnl_WorkItem(काष्ठा net_device *dev);
व्योम rtl8192_SetBWModeWorkItem(काष्ठा net_device *dev);
bool rtl8192_SetRFPowerState(काष्ठा net_device *dev,
			     RT_RF_POWER_STATE eRFPowerState);
व्योम InitialGain819xUsb(काष्ठा net_device *dev, u8 Operation);

व्योम InitialGainOperateWorkItemCallBack(काष्ठा work_काष्ठा *work);

#पूर्ण_अगर
