<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
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
#घोषणा _RTL871X_MP_C_

#समावेश "osdep_service.h"
#समावेश "drv_types.h"
#समावेश "rtl871x_mp_phy_regdef.h"
#समावेश "rtl8712_cmd.h"

अटल व्योम _init_mp_priv_(काष्ठा mp_priv *pmp_priv)
अणु
	pmp_priv->mode = _LOOPBOOK_MODE_;
	pmp_priv->curr_ch = 1;
	pmp_priv->curr_modem = MIXED_PHY;
	pmp_priv->curr_rateidx = 0;
	pmp_priv->curr_txघातeridx = 0x14;
	pmp_priv->antenna_tx = ANTENNA_A;
	pmp_priv->antenna_rx = ANTENNA_AB;
	pmp_priv->check_mp_pkt = 0;
	pmp_priv->tx_pktcount = 0;
	pmp_priv->rx_pktcount = 0;
	pmp_priv->rx_crcerrpktcount = 0;
पूर्ण

अटल पूर्णांक init_mp_priv(काष्ठा mp_priv *pmp_priv)
अणु
	पूर्णांक i;
	काष्ठा mp_xmit_frame *pmp_xmitframe;

	_init_mp_priv_(pmp_priv);
	_init_queue(&pmp_priv->मुक्त_mp_xmitqueue);
	pmp_priv->pallocated_mp_xmitframe_buf = शून्य;
	pmp_priv->pallocated_mp_xmitframe_buf = kदो_स्मृति(NR_MP_XMITFRAME *
				माप(काष्ठा mp_xmit_frame) + 4,
				GFP_ATOMIC);
	अगर (!pmp_priv->pallocated_mp_xmitframe_buf)
		वापस -ENOMEM;

	pmp_priv->pmp_xmtframe_buf = pmp_priv->pallocated_mp_xmitframe_buf +
			 4 -
			 ((addr_t)(pmp_priv->pallocated_mp_xmitframe_buf) & 3);
	pmp_xmitframe = (काष्ठा mp_xmit_frame *)pmp_priv->pmp_xmtframe_buf;
	क्रम (i = 0; i < NR_MP_XMITFRAME; i++) अणु
		INIT_LIST_HEAD(&(pmp_xmitframe->list));
		list_add_tail(&(pmp_xmitframe->list),
				 &(pmp_priv->मुक्त_mp_xmitqueue.queue));
		pmp_xmitframe->pkt = शून्य;
		pmp_xmitframe->frame_tag = MP_FRAMETAG;
		pmp_xmitframe->padapter = pmp_priv->papdater;
		pmp_xmitframe++;
	पूर्ण
	pmp_priv->मुक्त_mp_xmitframe_cnt = NR_MP_XMITFRAME;
	वापस 0;
पूर्ण

अटल पूर्णांक मुक्त_mp_priv(काष्ठा mp_priv *pmp_priv)
अणु
	kमुक्त(pmp_priv->pallocated_mp_xmitframe_buf);
	वापस 0;
पूर्ण

व्योम mp871xinit(काष्ठा _adapter *padapter)
अणु
	काष्ठा mp_priv *pmppriv = &padapter->mppriv;

	pmppriv->papdater = padapter;
	init_mp_priv(pmppriv);
पूर्ण

व्योम mp871xdeinit(काष्ठा _adapter *padapter)
अणु
	काष्ठा mp_priv *pmppriv = &padapter->mppriv;

	मुक्त_mp_priv(pmppriv);
पूर्ण

/*
 * Special क्रम bb and rf reg पढ़ो/ग_लिखो
 */
अटल u32 fw_iocmd_पढ़ो(काष्ठा _adapter *pAdapter, काष्ठा IOCMD_STRUCT iocmd)
अणु
	u32 cmd32 = 0, val32 = 0;
	u8 iocmd_class	= iocmd.cmdclass;
	u16 iocmd_value	= iocmd.value;
	u8 iocmd_idx	= iocmd.index;

	cmd32 = (iocmd_class << 24) | (iocmd_value << 8) | iocmd_idx;
	अगर (r8712_fw_cmd(pAdapter, cmd32))
		r8712_fw_cmd_data(pAdapter, &val32, 1);
	अन्यथा
		val32 = 0;
	वापस val32;
पूर्ण

अटल u8 fw_iocmd_ग_लिखो(काष्ठा _adapter *pAdapter,
			 काष्ठा IOCMD_STRUCT iocmd, u32 value)
अणु
	u32 cmd32 = 0;
	u8 iocmd_class	= iocmd.cmdclass;
	u32 iocmd_value	= iocmd.value;
	u8 iocmd_idx	= iocmd.index;

	r8712_fw_cmd_data(pAdapter, &value, 0);
	msleep(100);
	cmd32 = (iocmd_class << 24) | (iocmd_value << 8) | iocmd_idx;
	वापस r8712_fw_cmd(pAdapter, cmd32);
पूर्ण

/* offset : 0X800~0XFFF */
u32 r8712_bb_reg_पढ़ो(काष्ठा _adapter *pAdapter, u16 offset)
अणु
	u8 shअगरt = offset & 0x0003;	/* 4 byte access */
	u16 bb_addr = offset & 0x0FFC;	/* 4 byte access */
	u32 bb_val = 0;
	काष्ठा IOCMD_STRUCT iocmd;

	iocmd.cmdclass	= IOCMD_CLASS_BB_RF;
	iocmd.value	= bb_addr;
	iocmd.index	= IOCMD_BB_READ_IDX;
	bb_val = fw_iocmd_पढ़ो(pAdapter, iocmd);
	अगर (shअगरt != 0) अणु
		u32 bb_val2 = 0;

		bb_val >>= (shअगरt * 8);
		iocmd.value += 4;
		bb_val2 = fw_iocmd_पढ़ो(pAdapter, iocmd);
		bb_val2 <<= ((4 - shअगरt) * 8);
		bb_val |= bb_val2;
	पूर्ण
	वापस bb_val;
पूर्ण

/* offset : 0X800~0XFFF */
u8 r8712_bb_reg_ग_लिखो(काष्ठा _adapter *pAdapter, u16 offset, u32 value)
अणु
	u8 shअगरt = offset & 0x0003;	/* 4 byte access */
	u16 bb_addr = offset & 0x0FFC;	/* 4 byte access */
	काष्ठा IOCMD_STRUCT iocmd;

	iocmd.cmdclass	= IOCMD_CLASS_BB_RF;
	iocmd.value	= bb_addr;
	iocmd.index	= IOCMD_BB_WRITE_IDX;
	अगर (shअगरt != 0) अणु
		u32 oldValue = 0;
		u32 newValue = value;

		oldValue = r8712_bb_reg_पढ़ो(pAdapter, iocmd.value);
		oldValue &= (0xFFFFFFFF >> ((4 - shअगरt) * 8));
		value = oldValue | (newValue << (shअगरt * 8));
		अगर (!fw_iocmd_ग_लिखो(pAdapter, iocmd, value))
			वापस false;
		iocmd.value += 4;
		oldValue = r8712_bb_reg_पढ़ो(pAdapter, iocmd.value);
		oldValue &= (0xFFFFFFFF << (shअगरt * 8));
		value = oldValue | (newValue >> ((4 - shअगरt) * 8));
	पूर्ण
	वापस fw_iocmd_ग_लिखो(pAdapter, iocmd, value);
पूर्ण

/* offset : 0x00 ~ 0xFF */
u32 r8712_rf_reg_पढ़ो(काष्ठा _adapter *pAdapter, u8 path, u8 offset)
अणु
	u16 rf_addr = (path << 8) | offset;
	काष्ठा IOCMD_STRUCT iocmd;

	iocmd.cmdclass	= IOCMD_CLASS_BB_RF;
	iocmd.value	= rf_addr;
	iocmd.index	= IOCMD_RF_READ_IDX;
	वापस fw_iocmd_पढ़ो(pAdapter, iocmd);
पूर्ण

u8 r8712_rf_reg_ग_लिखो(काष्ठा _adapter *pAdapter, u8 path, u8 offset, u32 value)
अणु
	u16 rf_addr = (path << 8) | offset;
	काष्ठा IOCMD_STRUCT iocmd;

	iocmd.cmdclass	= IOCMD_CLASS_BB_RF;
	iocmd.value	= rf_addr;
	iocmd.index	= IOCMD_RF_WRIT_IDX;
	वापस fw_iocmd_ग_लिखो(pAdapter, iocmd, value);
पूर्ण

अटल u32 bitshअगरt(u32 biपंचांगask)
अणु
	u32 i;

	क्रम (i = 0; i <= 31; i++)
		अगर (((biपंचांगask >> i) &  0x1) == 1)
			अवरोध;
	वापस i;
पूर्ण

अटल u32 get_bb_reg(काष्ठा _adapter *pAdapter, u16 offset, u32 biपंचांगask)
अणु
	u32 org_value, bit_shअगरt;

	org_value = r8712_bb_reg_पढ़ो(pAdapter, offset);
	bit_shअगरt = bitshअगरt(biपंचांगask);
	वापस (org_value & biपंचांगask) >> bit_shअगरt;
पूर्ण

अटल u8 set_bb_reg(काष्ठा _adapter *pAdapter,
		     u16 offset,
		     u32 biपंचांगask,
		     u32 value)
अणु
	u32 org_value, bit_shअगरt, new_value;

	अगर (biपंचांगask != bMaskDWord) अणु
		org_value = r8712_bb_reg_पढ़ो(pAdapter, offset);
		bit_shअगरt = bitshअगरt(biपंचांगask);
		new_value = (org_value & (~biपंचांगask)) | (value << bit_shअगरt);
	पूर्ण अन्यथा अणु
		new_value = value;
	पूर्ण
	वापस r8712_bb_reg_ग_लिखो(pAdapter, offset, new_value);
पूर्ण

अटल u32 get_rf_reg(काष्ठा _adapter *pAdapter, u8 path, u8 offset,
		      u32 biपंचांगask)
अणु
	u32 org_value, bit_shअगरt;

	org_value = r8712_rf_reg_पढ़ो(pAdapter, path, offset);
	bit_shअगरt = bitshअगरt(biपंचांगask);
	वापस (org_value & biपंचांगask) >> bit_shअगरt;
पूर्ण

अटल u8 set_rf_reg(काष्ठा _adapter *pAdapter, u8 path, u8 offset, u32 biपंचांगask,
	      u32 value)
अणु
	u32 org_value, bit_shअगरt, new_value;

	अगर (biपंचांगask != bMaskDWord) अणु
		org_value = r8712_rf_reg_पढ़ो(pAdapter, path, offset);
		bit_shअगरt = bitshअगरt(biपंचांगask);
		new_value = (org_value & (~biपंचांगask)) | (value << bit_shअगरt);
	पूर्ण अन्यथा अणु
		new_value = value;
	पूर्ण
	वापस r8712_rf_reg_ग_लिखो(pAdapter, path, offset, new_value);
पूर्ण

/*
 * SetChannel
 * Description
 *	Use H2C command to change channel,
 *	not only modअगरy rf रेजिस्टर, but also other setting need to be करोne.
 */
व्योम r8712_SetChannel(काष्ठा _adapter *pAdapter)
अणु
	काष्ठा cmd_priv *pcmdpriv = &pAdapter->cmdpriv;
	काष्ठा cmd_obj *pcmd = शून्य;
	काष्ठा SetChannel_parm *pparm = शून्य;
	u16 code = GEN_CMD_CODE(_SetChannel);

	pcmd = kदो_स्मृति(माप(*pcmd), GFP_ATOMIC);
	अगर (!pcmd)
		वापस;
	pparm = kदो_स्मृति(माप(*pparm), GFP_ATOMIC);
	अगर (!pparm) अणु
		kमुक्त(pcmd);
		वापस;
	पूर्ण
	pparm->curr_ch = pAdapter->mppriv.curr_ch;
	init_h2fwcmd_w_parm_no_rsp(pcmd, pparm, code);
	r8712_enqueue_cmd(pcmdpriv, pcmd);
पूर्ण

अटल व्योम SetCCKTxPower(काष्ठा _adapter *pAdapter, u8 TxPower)
अणु
	u16 TxAGC = 0;

	TxAGC = TxPower;
	set_bb_reg(pAdapter, rTxAGC_CCK_Mcs32, bTxAGCRateCCK, TxAGC);
पूर्ण

अटल व्योम SetOFDMTxPower(काष्ठा _adapter *pAdapter, u8 TxPower)
अणु
	u32 TxAGC = 0;

	TxAGC |= ((TxPower << 24) | (TxPower << 16) | (TxPower << 8) |
		  TxPower);
	set_bb_reg(pAdapter, rTxAGC_Rate18_06, bTxAGCRate18_06, TxAGC);
	set_bb_reg(pAdapter, rTxAGC_Rate54_24, bTxAGCRate54_24, TxAGC);
	set_bb_reg(pAdapter, rTxAGC_Mcs03_Mcs00, bTxAGCRateMCS3_MCS0, TxAGC);
	set_bb_reg(pAdapter, rTxAGC_Mcs07_Mcs04, bTxAGCRateMCS7_MCS4, TxAGC);
	set_bb_reg(pAdapter, rTxAGC_Mcs11_Mcs08, bTxAGCRateMCS11_MCS8, TxAGC);
	set_bb_reg(pAdapter, rTxAGC_Mcs15_Mcs12, bTxAGCRateMCS15_MCS12, TxAGC);
पूर्ण

व्योम r8712_SetTxPower(काष्ठा _adapter *pAdapter)
अणु
	u8 TxPower = pAdapter->mppriv.curr_txघातeridx;

	SetCCKTxPower(pAdapter, TxPower);
	SetOFDMTxPower(pAdapter, TxPower);
पूर्ण

व्योम r8712_SetTxAGCOffset(काष्ठा _adapter *pAdapter, u32 ulTxAGCOffset)
अणु
	u32 TxAGCOffset_B, TxAGCOffset_C, TxAGCOffset_D, पंचांगpAGC;

	TxAGCOffset_B = ulTxAGCOffset & 0x000000ff;
	TxAGCOffset_C = (ulTxAGCOffset & 0x0000ff00) >> 8;
	TxAGCOffset_D = (ulTxAGCOffset & 0x00ff0000) >> 16;
	पंचांगpAGC = TxAGCOffset_D << 8 | TxAGCOffset_C << 4 | TxAGCOffset_B;
	set_bb_reg(pAdapter, rFPGA0_TxGainStage,
			(bXBTxAGC | bXCTxAGC | bXDTxAGC), पंचांगpAGC);
पूर्ण

व्योम r8712_SetDataRate(काष्ठा _adapter *pAdapter)
अणु
	u8 path = RF_PATH_A;
	u8 offset = RF_SYN_G2;
	u32 value;

	value = (pAdapter->mppriv.curr_rateidx < 4) ? 0x4440 : 0xF200;
	r8712_rf_reg_ग_लिखो(pAdapter, path, offset, value);
पूर्ण

व्योम r8712_SwitchBandwidth(काष्ठा _adapter *pAdapter)
अणु
	/* 3 1.Set MAC रेजिस्टर : BWOPMODE  bit2:1 20MhzBW */
	u8 regBwOpMode = 0;
	u8 Bandwidth = pAdapter->mppriv.curr_bandwidth;

	regBwOpMode = r8712_पढ़ो8(pAdapter, 0x10250203);
	अगर (Bandwidth == HT_CHANNEL_WIDTH_20)
		regBwOpMode |= BIT(2);
	अन्यथा
		regBwOpMode &= ~(BIT(2));
	r8712_ग_लिखो8(pAdapter, 0x10250203, regBwOpMode);
	/* 3 2.Set PHY related रेजिस्टर */
	चयन (Bandwidth) अणु
	/* 20 MHz channel*/
	हाल HT_CHANNEL_WIDTH_20:
		set_bb_reg(pAdapter, rFPGA0_RFMOD, bRFMOD, 0x0);
		set_bb_reg(pAdapter, rFPGA1_RFMOD, bRFMOD, 0x0);
		/* Use PHY_REG.txt शेष value. Do not need to change.
		 * Correct the tx घातer क्रम CCK rate in 40M.
		 * It is set in Tx descriptor क्रम 8192x series
		 */
		set_bb_reg(pAdapter, rFPGA0_AnalogParameter2, bMaskDWord, 0x58);
		अवरोध;
	/* 40 MHz channel*/
	हाल HT_CHANNEL_WIDTH_40:
		set_bb_reg(pAdapter, rFPGA0_RFMOD, bRFMOD, 0x1);
		set_bb_reg(pAdapter, rFPGA1_RFMOD, bRFMOD, 0x1);
		/* Use PHY_REG.txt शेष value. Do not need to change.
		 * Correct the tx घातer क्रम CCK rate in 40M.
		 * Set Control channel to upper or lower. These settings are
		 * required only क्रम 40MHz
		 */
		set_bb_reg(pAdapter, rCCK0_System, bCCKSideBand,
			   (HAL_PRIME_CHNL_OFFSET_DONT_CARE >> 1));
		set_bb_reg(pAdapter, rOFDM1_LSTF, 0xC00,
			   HAL_PRIME_CHNL_OFFSET_DONT_CARE);
		set_bb_reg(pAdapter, rFPGA0_AnalogParameter2, bMaskDWord, 0x18);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* 3 3.Set RF related रेजिस्टर */
	चयन (Bandwidth) अणु
	हाल HT_CHANNEL_WIDTH_20:
		set_rf_reg(pAdapter, RF_PATH_A, RF_CHNLBW,
			   BIT(10) | BIT(11), 0x01);
		अवरोध;
	हाल HT_CHANNEL_WIDTH_40:
		set_rf_reg(pAdapter, RF_PATH_A, RF_CHNLBW,
			   BIT(10) | BIT(11), 0x00);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*------------------------------Define काष्ठाure----------------------------*/
काष्ठा R_ANTENNA_SELECT_OFDM अणु
	u32	r_tx_antenna:4;
	u32	r_ant_l:4;
	u32	r_ant_non_ht:4;
	u32	r_ant_ht1:4;
	u32	r_ant_ht2:4;
	u32	r_ant_ht_s1:4;
	u32	r_ant_non_ht_s1:4;
	u32	OFDM_TXSC:2;
	u32	Reserved:2;
पूर्ण;

काष्ठा R_ANTENNA_SELECT_CCK अणु
	u8	r_cckrx_enable_2:2;
	u8	r_cckrx_enable:2;
	u8	r_ccktx_enable:4;
पूर्ण;

व्योम r8712_SwitchAntenna(काष्ठा _adapter *pAdapter)
अणु
	u32	ofdm_tx_en_val = 0, ofdm_tx_ant_sel_val = 0;
	u8	ofdm_rx_ant_sel_val = 0;
	u8	cck_ant_select_val = 0;
	u32	cck_ant_sel_val = 0;
	काष्ठा R_ANTENNA_SELECT_CCK *p_cck_txrx;

	p_cck_txrx = (काष्ठा R_ANTENNA_SELECT_CCK *)&cck_ant_select_val;

	चयन (pAdapter->mppriv.antenna_tx) अणु
	हाल ANTENNA_A:
		/* From SD3 Willis suggestion !!! Set RF A=TX and B as standby*/
		set_bb_reg(pAdapter, rFPGA0_XA_HSSIParameter2, 0xe, 2);
		set_bb_reg(pAdapter, rFPGA0_XB_HSSIParameter2, 0xe, 1);
		ofdm_tx_en_val = 0x3;
		ofdm_tx_ant_sel_val = 0x11111111;/* Power save */
		p_cck_txrx->r_ccktx_enable = 0x8;
		अवरोध;
	हाल ANTENNA_B:
		set_bb_reg(pAdapter, rFPGA0_XA_HSSIParameter2, 0xe, 1);
		set_bb_reg(pAdapter, rFPGA0_XB_HSSIParameter2, 0xe, 2);
		ofdm_tx_en_val = 0x3;
		ofdm_tx_ant_sel_val = 0x22222222;/* Power save */
		p_cck_txrx->r_ccktx_enable = 0x4;
		अवरोध;
	हाल ANTENNA_AB:	/* For 8192S */
		set_bb_reg(pAdapter, rFPGA0_XA_HSSIParameter2, 0xe, 2);
		set_bb_reg(pAdapter, rFPGA0_XB_HSSIParameter2, 0xe, 2);
		ofdm_tx_en_val = 0x3;
		ofdm_tx_ant_sel_val = 0x3321333; /* Disable Power save */
		p_cck_txrx->r_ccktx_enable = 0xC;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	/*OFDM Tx*/
	set_bb_reg(pAdapter, rFPGA1_TxInfo, 0xffffffff, ofdm_tx_ant_sel_val);
	/*OFDM Tx*/
	set_bb_reg(pAdapter, rFPGA0_TxInfo, 0x0000000f, ofdm_tx_en_val);
	चयन (pAdapter->mppriv.antenna_rx) अणु
	हाल ANTENNA_A:
		ofdm_rx_ant_sel_val = 0x1;	/* A */
		p_cck_txrx->r_cckrx_enable = 0x0; /* शेष: A */
		p_cck_txrx->r_cckrx_enable_2 = 0x0; /* option: A */
		अवरोध;
	हाल ANTENNA_B:
		ofdm_rx_ant_sel_val = 0x2;	/* B */
		p_cck_txrx->r_cckrx_enable = 0x1; /* शेष: B */
		p_cck_txrx->r_cckrx_enable_2 = 0x1; /* option: B */
		अवरोध;
	हाल ANTENNA_AB:
		ofdm_rx_ant_sel_val = 0x3; /* AB */
		p_cck_txrx->r_cckrx_enable = 0x0; /* शेष:A */
		p_cck_txrx->r_cckrx_enable_2 = 0x1; /* option:B */
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	/*OFDM Rx*/
	set_bb_reg(pAdapter, rOFDM0_TRxPathEnable, 0x0000000f,
		   ofdm_rx_ant_sel_val);
	/*OFDM Rx*/
	set_bb_reg(pAdapter, rOFDM1_TRxPathEnable, 0x0000000f,
		   ofdm_rx_ant_sel_val);

	cck_ant_sel_val = cck_ant_select_val;
	/*CCK TxRx*/
	set_bb_reg(pAdapter, rCCK0_AFESetting, bMaskByte3, cck_ant_sel_val);
पूर्ण

अटल व्योम TriggerRFThermalMeter(काष्ठा _adapter *pAdapter)
अणु
	/* 0x24: RF Reg[6:5] */
	set_rf_reg(pAdapter, RF_PATH_A, RF_T_METER, bRFRegOffsetMask, 0x60);
पूर्ण

अटल u32 ReadRFThermalMeter(काष्ठा _adapter *pAdapter)
अणु
	/* 0x24: RF Reg[4:0] */
	वापस get_rf_reg(pAdapter, RF_PATH_A, RF_T_METER, 0x1F);
पूर्ण

व्योम r8712_GetThermalMeter(काष्ठा _adapter *pAdapter, u32 *value)
अणु
	TriggerRFThermalMeter(pAdapter);
	msleep(1000);
	*value = ReadRFThermalMeter(pAdapter);
पूर्ण

व्योम r8712_SetSingleCarrierTx(काष्ठा _adapter *pAdapter, u8 bStart)
अणु
	अगर (bStart) अणु /* Start Single Carrier. */
		/* 1. अगर OFDM block on? */
		अगर (!get_bb_reg(pAdapter, rFPGA0_RFMOD, bOFDMEn))
			/*set OFDM block on*/
			set_bb_reg(pAdapter, rFPGA0_RFMOD, bOFDMEn, bEnable);
		/* 2. set CCK test mode off, set to CCK normal mode */
		set_bb_reg(pAdapter, rCCK0_System, bCCKBBMode, bDisable);
		/* 3. turn on scramble setting */
		set_bb_reg(pAdapter, rCCK0_System, bCCKScramble, bEnable);
		/* 4. Turn On Single Carrier Tx and off the other test modes. */
		set_bb_reg(pAdapter, rOFDM1_LSTF, bOFDMContinueTx, bDisable);
		set_bb_reg(pAdapter, rOFDM1_LSTF, bOFDMSingleCarrier, bEnable);
		set_bb_reg(pAdapter, rOFDM1_LSTF, bOFDMSingleTone, bDisable);
	पूर्ण अन्यथा अणु /* Stop Single Carrier.*/
		/* Turn off all test modes.*/
		set_bb_reg(pAdapter, rOFDM1_LSTF, bOFDMContinueTx, bDisable);
		set_bb_reg(pAdapter, rOFDM1_LSTF, bOFDMSingleCarrier,
			   bDisable);
		set_bb_reg(pAdapter, rOFDM1_LSTF, bOFDMSingleTone, bDisable);
		msleep(20);
		/*BB Reset*/
		set_bb_reg(pAdapter, rPMAC_Reset, bBBResetB, 0x0);
		set_bb_reg(pAdapter, rPMAC_Reset, bBBResetB, 0x1);
	पूर्ण
पूर्ण

व्योम r8712_SetSingleToneTx(काष्ठा _adapter *pAdapter, u8 bStart)
अणु
	u8 rfPath;

	चयन (pAdapter->mppriv.antenna_tx) अणु
	हाल ANTENNA_B:
		rfPath = RF_PATH_B;
		अवरोध;
	हाल ANTENNA_A:
	शेष:
		rfPath = RF_PATH_A;
		अवरोध;
	पूर्ण
	अगर (bStart) अणु /* Start Single Tone.*/
		set_bb_reg(pAdapter, rFPGA0_RFMOD, bCCKEn, bDisable);
		set_bb_reg(pAdapter, rFPGA0_RFMOD, bOFDMEn, bDisable);
		set_rf_reg(pAdapter, rfPath, RF_TX_G2, bRFRegOffsetMask,
			   0xd4000);
		msleep(100);
		/* PAD all on.*/
		set_rf_reg(pAdapter, rfPath, RF_AC, bRFRegOffsetMask, 0x2001f);
		msleep(100);
	पूर्ण अन्यथा अणु /* Stop Single Tone.*/
		set_bb_reg(pAdapter, rFPGA0_RFMOD, bCCKEn, bEnable);
		set_bb_reg(pAdapter, rFPGA0_RFMOD, bOFDMEn, bEnable);
		set_rf_reg(pAdapter, rfPath, RF_TX_G2, bRFRegOffsetMask,
			   0x54000);
		msleep(100);
		/* PAD all on.*/
		set_rf_reg(pAdapter, rfPath, RF_AC, bRFRegOffsetMask, 0x30000);
		msleep(100);
	पूर्ण
पूर्ण

व्योम r8712_SetCarrierSuppressionTx(काष्ठा _adapter *pAdapter, u8 bStart)
अणु
	अगर (bStart) अणु /* Start Carrier Suppression.*/
		अगर (pAdapter->mppriv.curr_rateidx <= MPT_RATE_11M) अणु
			/* 1. अगर CCK block on? */
			अगर (!get_bb_reg(pAdapter, rFPGA0_RFMOD, bCCKEn)) अणु
				/*set CCK block on*/
				set_bb_reg(pAdapter, rFPGA0_RFMOD, bCCKEn,
					   bEnable);
			पूर्ण
			/* Turn Off All Test Mode */
			set_bb_reg(pAdapter, rOFDM1_LSTF, bOFDMContinueTx,
				   bDisable);
			set_bb_reg(pAdapter, rOFDM1_LSTF, bOFDMSingleCarrier,
				   bDisable);
			set_bb_reg(pAdapter, rOFDM1_LSTF, bOFDMSingleTone,
				   bDisable);
			/*transmit mode*/
			set_bb_reg(pAdapter, rCCK0_System, bCCKBBMode, 0x2);
			/*turn off scramble setting*/
			set_bb_reg(pAdapter, rCCK0_System, bCCKScramble,
				   bDisable);
			/*Set CCK Tx Test Rate*/
			/*Set FTxRate to 1Mbps*/
			set_bb_reg(pAdapter, rCCK0_System, bCCKTxRate, 0x0);
		पूर्ण
	पूर्ण अन्यथा अणु /* Stop Carrier Suppression. */
		अगर (pAdapter->mppriv.curr_rateidx <= MPT_RATE_11M) अणु
			/*normal mode*/
			set_bb_reg(pAdapter, rCCK0_System, bCCKBBMode, 0x0);
			/*turn on scramble setting*/
			set_bb_reg(pAdapter, rCCK0_System, bCCKScramble,
				   bEnable);
			/*BB Reset*/
			set_bb_reg(pAdapter, rPMAC_Reset, bBBResetB, 0x0);
			set_bb_reg(pAdapter, rPMAC_Reset, bBBResetB, 0x1);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम SetCCKContinuousTx(काष्ठा _adapter *pAdapter, u8 bStart)
अणु
	u32 cckrate;

	अगर (bStart) अणु
		/* 1. अगर CCK block on? */
		अगर (!get_bb_reg(pAdapter, rFPGA0_RFMOD, bCCKEn)) अणु
			/*set CCK block on*/
			set_bb_reg(pAdapter, rFPGA0_RFMOD, bCCKEn, bEnable);
		पूर्ण
		/* Turn Off All Test Mode */
		set_bb_reg(pAdapter, rOFDM1_LSTF, bOFDMContinueTx, bDisable);
		set_bb_reg(pAdapter, rOFDM1_LSTF, bOFDMSingleCarrier, bDisable);
		set_bb_reg(pAdapter, rOFDM1_LSTF, bOFDMSingleTone, bDisable);
		/*Set CCK Tx Test Rate*/
		cckrate  = pAdapter->mppriv.curr_rateidx;
		set_bb_reg(pAdapter, rCCK0_System, bCCKTxRate, cckrate);
		/*transmit mode*/
		set_bb_reg(pAdapter, rCCK0_System, bCCKBBMode, 0x2);
		/*turn on scramble setting*/
		set_bb_reg(pAdapter, rCCK0_System, bCCKScramble, bEnable);
	पूर्ण अन्यथा अणु
		/*normal mode*/
		set_bb_reg(pAdapter, rCCK0_System, bCCKBBMode, 0x0);
		/*turn on scramble setting*/
		set_bb_reg(pAdapter, rCCK0_System, bCCKScramble, bEnable);
		/*BB Reset*/
		set_bb_reg(pAdapter, rPMAC_Reset, bBBResetB, 0x0);
		set_bb_reg(pAdapter, rPMAC_Reset, bBBResetB, 0x1);
	पूर्ण
पूर्ण /* mpt_StartCckContTx */

अटल व्योम SetOFDMContinuousTx(काष्ठा _adapter *pAdapter, u8 bStart)
अणु
	अगर (bStart) अणु
		/* 1. अगर OFDM block on? */
		अगर (!get_bb_reg(pAdapter, rFPGA0_RFMOD, bOFDMEn)) अणु
			/*set OFDM block on*/
			set_bb_reg(pAdapter, rFPGA0_RFMOD, bOFDMEn, bEnable);
		पूर्ण
		/* 2. set CCK test mode off, set to CCK normal mode*/
		set_bb_reg(pAdapter, rCCK0_System, bCCKBBMode, bDisable);
		/* 3. turn on scramble setting */
		set_bb_reg(pAdapter, rCCK0_System, bCCKScramble, bEnable);
		/* 4. Turn On Continue Tx and turn off the other test modes.*/
		set_bb_reg(pAdapter, rOFDM1_LSTF, bOFDMContinueTx, bEnable);
		set_bb_reg(pAdapter, rOFDM1_LSTF, bOFDMSingleCarrier, bDisable);
		set_bb_reg(pAdapter, rOFDM1_LSTF, bOFDMSingleTone, bDisable);
	पूर्ण अन्यथा अणु
		set_bb_reg(pAdapter, rOFDM1_LSTF, bOFDMContinueTx, bDisable);
		set_bb_reg(pAdapter, rOFDM1_LSTF, bOFDMSingleCarrier,
			   bDisable);
		set_bb_reg(pAdapter, rOFDM1_LSTF, bOFDMSingleTone, bDisable);
		msleep(20);
		/*BB Reset*/
		set_bb_reg(pAdapter, rPMAC_Reset, bBBResetB, 0x0);
		set_bb_reg(pAdapter, rPMAC_Reset, bBBResetB, 0x1);
	पूर्ण
पूर्ण /* mpt_StartOfdmContTx */

व्योम r8712_SetContinuousTx(काष्ठा _adapter *pAdapter, u8 bStart)
अणु
	/* ADC turn off [bit24-21] adc port0 ~ port1 */
	अगर (bStart) अणु
		r8712_bb_reg_ग_लिखो(pAdapter, rRx_Wait_CCCA,
				   r8712_bb_reg_पढ़ो(pAdapter,
				   rRx_Wait_CCCA) & 0xFE1FFFFF);
		msleep(100);
	पूर्ण
	अगर (pAdapter->mppriv.curr_rateidx <= MPT_RATE_11M)
		SetCCKContinuousTx(pAdapter, bStart);
	अन्यथा अगर ((pAdapter->mppriv.curr_rateidx >= MPT_RATE_6M) &&
		 (pAdapter->mppriv.curr_rateidx <= MPT_RATE_MCS15))
		SetOFDMContinuousTx(pAdapter, bStart);
	/* ADC turn on [bit24-21] adc port0 ~ port1 */
	अगर (!bStart)
		r8712_bb_reg_ग_लिखो(pAdapter, rRx_Wait_CCCA,
				   r8712_bb_reg_पढ़ो(pAdapter,
				   rRx_Wait_CCCA) | 0x01E00000);
पूर्ण

व्योम r8712_ResetPhyRxPktCount(काष्ठा _adapter *pAdapter)
अणु
	u32 i, phyrx_set = 0;

	क्रम (i = OFDM_PPDU_BIT; i <= HT_MPDU_FAIL_BIT; i++) अणु
		phyrx_set = 0;
		phyrx_set |= (i << 28);		/*select*/
		phyrx_set |= 0x08000000;	/* set counter to zero*/
		r8712_ग_लिखो32(pAdapter, RXERR_RPT, phyrx_set);
	पूर्ण
पूर्ण

अटल u32 GetPhyRxPktCounts(काष्ठा _adapter *pAdapter, u32 selbit)
अणु
	/*selection*/
	u32 phyrx_set = 0;
	u32 SelectBit;

	SelectBit = selbit << 28;
	phyrx_set |= (SelectBit & 0xF0000000);
	r8712_ग_लिखो32(pAdapter, RXERR_RPT, phyrx_set);
	/*Read packet count*/
	वापस r8712_पढ़ो32(pAdapter, RXERR_RPT) & RPTMaxCount;
पूर्ण

u32 r8712_GetPhyRxPktReceived(काष्ठा _adapter *pAdapter)
अणु
	u32 OFDM_cnt = GetPhyRxPktCounts(pAdapter, OFDM_MPDU_OK_BIT);
	u32 CCK_cnt  = GetPhyRxPktCounts(pAdapter, CCK_MPDU_OK_BIT);
	u32 HT_cnt   = GetPhyRxPktCounts(pAdapter, HT_MPDU_OK_BIT);

	वापस OFDM_cnt + CCK_cnt + HT_cnt;
पूर्ण

u32 r8712_GetPhyRxPktCRC32Error(काष्ठा _adapter *pAdapter)
अणु
	u32 OFDM_cnt = GetPhyRxPktCounts(pAdapter, OFDM_MPDU_FAIL_BIT);
	u32 CCK_cnt  = GetPhyRxPktCounts(pAdapter, CCK_MPDU_FAIL_BIT);
	u32 HT_cnt   = GetPhyRxPktCounts(pAdapter, HT_MPDU_FAIL_BIT);

	वापस OFDM_cnt + CCK_cnt + HT_cnt;
पूर्ण
