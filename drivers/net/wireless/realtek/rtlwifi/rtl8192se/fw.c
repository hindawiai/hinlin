<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "../pci.h"
#समावेश "../base.h"
#समावेश "reg.h"
#समावेश "def.h"
#समावेश "fw.h"

अटल व्योम _rtl92s_fw_set_rqpn(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_ग_लिखो_dword(rtlpriv, RQPN, 0xffffffff);
	rtl_ग_लिखो_dword(rtlpriv, RQPN + 4, 0xffffffff);
	rtl_ग_लिखो_byte(rtlpriv, RQPN + 8, 0xff);
	rtl_ग_लिखो_byte(rtlpriv, RQPN + 0xB, 0x80);
पूर्ण

अटल bool _rtl92s_firmware_enable_cpu(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 icheckसमय = 200;
	u16 पंचांगpu2b;
	u8 पंचांगpu1b, cpustatus = 0;

	_rtl92s_fw_set_rqpn(hw);

	/* Enable CPU. */
	पंचांगpu1b = rtl_पढ़ो_byte(rtlpriv, SYS_CLKR);
	/* AFE source */
	rtl_ग_लिखो_byte(rtlpriv, SYS_CLKR, (पंचांगpu1b | SYS_CPU_CLKSEL));

	पंचांगpu2b = rtl_पढ़ो_word(rtlpriv, REG_SYS_FUNC_EN);
	rtl_ग_लिखो_word(rtlpriv, REG_SYS_FUNC_EN, (पंचांगpu2b | FEN_CPUEN));

	/* Polling IMEM Ready after CPU has refilled. */
	करो अणु
		cpustatus = rtl_पढ़ो_byte(rtlpriv, TCR);
		अगर (cpustatus & IMEM_RDY) अणु
			rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
				"IMEM Ready after CPU has refilled\n");
			अवरोध;
		पूर्ण

		udelay(100);
	पूर्ण जबतक (icheckसमय--);

	अगर (!(cpustatus & IMEM_RDY))
		वापस false;

	वापस true;
पूर्ण

अटल क्रमागत fw_status _rtl92s_firmware_get_nextstatus(
		क्रमागत fw_status fw_currentstatus)
अणु
	क्रमागत fw_status	next_fwstatus = 0;

	चयन (fw_currentstatus) अणु
	हाल FW_STATUS_INIT:
		next_fwstatus = FW_STATUS_LOAD_IMEM;
		अवरोध;
	हाल FW_STATUS_LOAD_IMEM:
		next_fwstatus = FW_STATUS_LOAD_EMEM;
		अवरोध;
	हाल FW_STATUS_LOAD_EMEM:
		next_fwstatus = FW_STATUS_LOAD_DMEM;
		अवरोध;
	हाल FW_STATUS_LOAD_DMEM:
		next_fwstatus = FW_STATUS_READY;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस next_fwstatus;
पूर्ण

अटल u8 _rtl92s_firmware_header_map_rftype(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);

	चयन (rtlphy->rf_type) अणु
	हाल RF_1T1R:
		वापस 0x11;
	हाल RF_1T2R:
		वापस 0x12;
	हाल RF_2T2R:
		वापस 0x22;
	शेष:
		pr_err("Unknown RF type(%x)\n", rtlphy->rf_type);
		अवरोध;
	पूर्ण
	वापस 0x22;
पूर्ण

अटल व्योम _rtl92s_firmwareheader_priveupdate(काष्ठा ieee80211_hw *hw,
		काष्ठा fw_priv *pfw_priv)
अणु
	/* Update RF types क्रम RATR settings. */
	pfw_priv->rf_config = _rtl92s_firmware_header_map_rftype(hw);
पूर्ण



अटल bool _rtl92s_cmd_send_packet(काष्ठा ieee80211_hw *hw,
		काष्ठा sk_buff *skb, u8 last)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl8192_tx_ring *ring;
	काष्ठा rtl_tx_desc *pdesc;
	अचिन्हित दीर्घ flags;
	u8 idx = 0;

	ring = &rtlpci->tx_ring[TXCMD_QUEUE];

	spin_lock_irqsave(&rtlpriv->locks.irq_th_lock, flags);

	idx = (ring->idx + skb_queue_len(&ring->queue)) % ring->entries;
	pdesc = &ring->desc[idx];
	rtlpriv->cfg->ops->fill_tx_cmddesc(hw, (u8 *)pdesc, 1, 1, skb);
	__skb_queue_tail(&ring->queue, skb);

	spin_unlock_irqrestore(&rtlpriv->locks.irq_th_lock, flags);

	वापस true;
पूर्ण

अटल bool _rtl92s_firmware_करोwnloadcode(काष्ठा ieee80211_hw *hw,
		u8 *code_भव_address, u32 buffer_len)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा sk_buff *skb;
	काष्ठा rtl_tcb_desc *tcb_desc;
	u16 frag_threshold = MAX_FIRMWARE_CODE_SIZE;
	u16 frag_length, frag_offset = 0;
	u16 extra_descoffset = 0;
	u8 last_inipkt = 0;

	_rtl92s_fw_set_rqpn(hw);

	अगर (buffer_len >= MAX_FIRMWARE_CODE_SIZE) अणु
		pr_err("Size over FIRMWARE_CODE_SIZE!\n");
		वापस false;
	पूर्ण

	extra_descoffset = 0;

	करो अणु
		अगर ((buffer_len - frag_offset) > frag_threshold) अणु
			frag_length = frag_threshold + extra_descoffset;
		पूर्ण अन्यथा अणु
			frag_length = (u16)(buffer_len - frag_offset +
					    extra_descoffset);
			last_inipkt = 1;
		पूर्ण

		/* Allocate skb buffer to contain firmware */
		/* info and tx descriptor info. */
		skb = dev_alloc_skb(frag_length);
		अगर (!skb)
			वापस false;
		skb_reserve(skb, extra_descoffset);
		skb_put_data(skb, code_भव_address + frag_offset,
			     (u32)(frag_length - extra_descoffset));

		tcb_desc = (काष्ठा rtl_tcb_desc *)(skb->cb);
		tcb_desc->queue_index = TXCMD_QUEUE;
		tcb_desc->cmd_or_init = DESC_PACKET_TYPE_INIT;
		tcb_desc->last_inipkt = last_inipkt;

		_rtl92s_cmd_send_packet(hw, skb, last_inipkt);

		frag_offset += (frag_length - extra_descoffset);

	पूर्ण जबतक (frag_offset < buffer_len);

	rtl_ग_लिखो_byte(rtlpriv, TP_POLL, TPPOLL_CQ);

	वापस true ;
पूर्ण

अटल bool _rtl92s_firmware_checkपढ़ोy(काष्ठा ieee80211_hw *hw,
		u8 loadfw_status)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rt_firmware *firmware = (काष्ठा rt_firmware *)rtlhal->pfirmware;
	u32 पंचांगpu4b;
	u8 cpustatus = 0;
	लघु pollingcnt = 1000;
	bool rtstatus = true;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"LoadStaus(%d)\n", loadfw_status);

	firmware->fwstatus = (क्रमागत fw_status)loadfw_status;

	चयन (loadfw_status) अणु
	हाल FW_STATUS_LOAD_IMEM:
		/* Polling IMEM code करोne. */
		करो अणु
			cpustatus = rtl_पढ़ो_byte(rtlpriv, TCR);
			अगर (cpustatus & IMEM_CODE_DONE)
				अवरोध;
			udelay(5);
		पूर्ण जबतक (pollingcnt--);

		अगर (!(cpustatus & IMEM_CHK_RPT) || (pollingcnt <= 0)) अणु
			pr_err("FW_STATUS_LOAD_IMEM FAIL CPU, Status=%x\n",
			       cpustatus);
			जाओ status_check_fail;
		पूर्ण
		अवरोध;

	हाल FW_STATUS_LOAD_EMEM:
		/* Check Put Code OK and Turn On CPU */
		/* Polling EMEM code करोne. */
		करो अणु
			cpustatus = rtl_पढ़ो_byte(rtlpriv, TCR);
			अगर (cpustatus & EMEM_CODE_DONE)
				अवरोध;
			udelay(5);
		पूर्ण जबतक (pollingcnt--);

		अगर (!(cpustatus & EMEM_CHK_RPT) || (pollingcnt <= 0)) अणु
			pr_err("FW_STATUS_LOAD_EMEM FAIL CPU, Status=%x\n",
			       cpustatus);
			जाओ status_check_fail;
		पूर्ण

		/* Turn On CPU */
		rtstatus = _rtl92s_firmware_enable_cpu(hw);
		अगर (!rtstatus) अणु
			pr_err("Enable CPU fail!\n");
			जाओ status_check_fail;
		पूर्ण
		अवरोध;

	हाल FW_STATUS_LOAD_DMEM:
		/* Polling DMEM code करोne */
		करो अणु
			cpustatus = rtl_पढ़ो_byte(rtlpriv, TCR);
			अगर (cpustatus & DMEM_CODE_DONE)
				अवरोध;
			udelay(5);
		पूर्ण जबतक (pollingcnt--);

		अगर (!(cpustatus & DMEM_CODE_DONE) || (pollingcnt <= 0)) अणु
			pr_err("Polling DMEM code done fail ! cpustatus(%#x)\n",
			       cpustatus);
			जाओ status_check_fail;
		पूर्ण

		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"DMEM code download success, cpustatus(%#x)\n",
			cpustatus);

		/* Prevent Delay too much and being scheduled out */
		/* Polling Load Firmware पढ़ोy */
		pollingcnt = 2000;
		करो अणु
			cpustatus = rtl_पढ़ो_byte(rtlpriv, TCR);
			अगर (cpustatus & FWRDY)
				अवरोध;
			udelay(40);
		पूर्ण जबतक (pollingcnt--);

		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Polling Load Firmware ready, cpustatus(%x)\n",
			cpustatus);

		अगर (((cpustatus & LOAD_FW_READY) != LOAD_FW_READY) ||
		    (pollingcnt <= 0)) अणु
			pr_err("Polling Load Firmware ready fail ! cpustatus(%x)\n",
			       cpustatus);
			जाओ status_check_fail;
		पूर्ण

		/* If right here, we can set TCR/RCR to desired value  */
		/* and config MAC lookback mode to normal mode */
		पंचांगpu4b = rtl_पढ़ो_dword(rtlpriv, TCR);
		rtl_ग_लिखो_dword(rtlpriv, TCR, (पंचांगpu4b & (~TCR_ICV)));

		पंचांगpu4b = rtl_पढ़ो_dword(rtlpriv, RCR);
		rtl_ग_लिखो_dword(rtlpriv, RCR, (पंचांगpu4b | RCR_APPFCS |
				RCR_APP_ICV | RCR_APP_MIC));

		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Current RCR settings(%#x)\n", पंचांगpu4b);

		/* Set to normal mode. */
		rtl_ग_लिखो_byte(rtlpriv, LBKMD_SEL, LBK_NORMAL);
		अवरोध;

	शेष:
		pr_err("Unknown status check!\n");
		rtstatus = false;
		अवरोध;
	पूर्ण

status_check_fail:
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"loadfw_status(%d), rtstatus(%x)\n",
		loadfw_status, rtstatus);
	वापस rtstatus;
पूर्ण

पूर्णांक rtl92s_करोwnload_fw(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rt_firmware *firmware = शून्य;
	काष्ठा fw_hdr *pfwheader;
	काष्ठा fw_priv *pfw_priv = शून्य;
	u8 *puc_mappedfile = शून्य;
	u32 ul_filelength = 0;
	u8 fwhdr_size = RT_8192S_FIRMWARE_HDR_SIZE;
	u8 fwstatus = FW_STATUS_INIT;
	bool rtstatus = true;

	अगर (rtlpriv->max_fw_size == 0 || !rtlhal->pfirmware)
		वापस 1;

	firmware = (काष्ठा rt_firmware *)rtlhal->pfirmware;
	firmware->fwstatus = FW_STATUS_INIT;

	puc_mappedfile = firmware->sz_fw_पंचांगpbuffer;

	/* 1. Retrieve FW header. */
	firmware->pfwheader = (काष्ठा fw_hdr *) puc_mappedfile;
	pfwheader = firmware->pfwheader;
	firmware->firmwareversion =  byte(pfwheader->version, 0);
	firmware->pfwheader->fwpriv.hci_sel = 1;/* pcie */

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"signature:%x, version:%x, size:%x, imemsize:%x, sram size:%x\n",
		pfwheader->signature,
		pfwheader->version, pfwheader->dmem_size,
		pfwheader->img_imem_size, pfwheader->img_sram_size);

	/* 2. Retrieve IMEM image. */
	अगर ((pfwheader->img_imem_size == 0) || (pfwheader->img_imem_size >
	    माप(firmware->fw_imem))) अणु
		pr_err("memory for data image is less than IMEM required\n");
		जाओ fail;
	पूर्ण अन्यथा अणु
		puc_mappedfile += fwhdr_size;

		स_नकल(firmware->fw_imem, puc_mappedfile,
		       pfwheader->img_imem_size);
		firmware->fw_imem_len = pfwheader->img_imem_size;
	पूर्ण

	/* 3. Retriecve EMEM image. */
	अगर (pfwheader->img_sram_size > माप(firmware->fw_emem)) अणु
		pr_err("memory for data image is less than EMEM required\n");
		जाओ fail;
	पूर्ण अन्यथा अणु
		puc_mappedfile += firmware->fw_imem_len;

		स_नकल(firmware->fw_emem, puc_mappedfile,
		       pfwheader->img_sram_size);
		firmware->fw_emem_len = pfwheader->img_sram_size;
	पूर्ण

	/* 4. करोwnload fw now */
	fwstatus = _rtl92s_firmware_get_nextstatus(firmware->fwstatus);
	जबतक (fwstatus != FW_STATUS_READY) अणु
		/* Image buffer redirection. */
		चयन (fwstatus) अणु
		हाल FW_STATUS_LOAD_IMEM:
			puc_mappedfile = firmware->fw_imem;
			ul_filelength = firmware->fw_imem_len;
			अवरोध;
		हाल FW_STATUS_LOAD_EMEM:
			puc_mappedfile = firmware->fw_emem;
			ul_filelength = firmware->fw_emem_len;
			अवरोध;
		हाल FW_STATUS_LOAD_DMEM:
			/* Partial update the content of header निजी. */
			pfwheader = firmware->pfwheader;
			pfw_priv = &pfwheader->fwpriv;
			_rtl92s_firmwareheader_priveupdate(hw, pfw_priv);
			puc_mappedfile = (u8 *)(firmware->pfwheader) +
					RT_8192S_FIRMWARE_HDR_EXCLUDE_PRI_SIZE;
			ul_filelength = fwhdr_size -
					RT_8192S_FIRMWARE_HDR_EXCLUDE_PRI_SIZE;
			अवरोध;
		शेष:
			pr_err("Unexpected Download step!!\n");
			जाओ fail;
		पूर्ण

		/* <2> Download image file */
		rtstatus = _rtl92s_firmware_करोwnloadcode(hw, puc_mappedfile,
				ul_filelength);

		अगर (!rtstatus) अणु
			pr_err("fail!\n");
			जाओ fail;
		पूर्ण

		/* <3> Check whether load FW process is पढ़ोy */
		rtstatus = _rtl92s_firmware_checkपढ़ोy(hw, fwstatus);
		अगर (!rtstatus) अणु
			pr_err("rtl8192se: firmware fail!\n");
			जाओ fail;
		पूर्ण

		fwstatus = _rtl92s_firmware_get_nextstatus(firmware->fwstatus);
	पूर्ण

	वापस rtstatus;
fail:
	वापस 0;
पूर्ण

अटल u32 _rtl92s_fill_h2c_cmd(काष्ठा sk_buff *skb, u32 h2cbufferlen,
				u32 cmd_num, u32 *pelement_id, u32 *pcmd_len,
				u8 **pcmb_buffer, u8 *cmd_start_seq)
अणु
	u32 totallen = 0, len = 0, tx_desclen = 0;
	u32 pre_जारीoffset = 0;
	u8 *ph2c_buffer;
	u8 i = 0;

	करो अणु
		/* 8 - Byte alignment */
		len = H2C_TX_CMD_HDR_LEN + N_BYTE_ALIGMENT(pcmd_len[i], 8);

		/* Buffer length is not enough */
		अगर (h2cbufferlen < totallen + len + tx_desclen)
			अवरोध;

		/* Clear content */
		ph2c_buffer = skb_put(skb, (u32)len);
		स_रखो((ph2c_buffer + totallen + tx_desclen), 0, len);

		/* CMD len */
		le32p_replace_bits((__le32 *)(ph2c_buffer + totallen +
					      tx_desclen), pcmd_len[i],
				   GENMASK(15, 0));

		/* CMD ID */
		le32p_replace_bits((__le32 *)(ph2c_buffer + totallen +
					      tx_desclen), pelement_id[i],
				   GENMASK(23, 16));

		/* CMD Sequence */
		*cmd_start_seq = *cmd_start_seq % 0x80;
		le32p_replace_bits((__le32 *)(ph2c_buffer + totallen +
					      tx_desclen), *cmd_start_seq,
				   GENMASK(30, 24));
		++*cmd_start_seq;

		/* Copy memory */
		स_नकल((ph2c_buffer + totallen + tx_desclen +
			H2C_TX_CMD_HDR_LEN), pcmb_buffer[i], pcmd_len[i]);

		/* CMD जारी */
		/* set the जारी in prevoius cmd. */
		अगर (i < cmd_num - 1)
			le32p_replace_bits((__le32 *)(ph2c_buffer +
						      pre_जारीoffset),
					   1, BIT(31));

		pre_जारीoffset = totallen;

		totallen += len;
	पूर्ण जबतक (++i < cmd_num);

	वापस totallen;
पूर्ण

अटल u32 _rtl92s_get_h2c_cmdlen(u32 h2cbufferlen, u32 cmd_num, u32 *pcmd_len)
अणु
	u32 totallen = 0, len = 0, tx_desclen = 0;
	u8 i = 0;

	करो अणु
		/* 8 - Byte alignment */
		len = H2C_TX_CMD_HDR_LEN + N_BYTE_ALIGMENT(pcmd_len[i], 8);

		/* Buffer length is not enough */
		अगर (h2cbufferlen < totallen + len + tx_desclen)
			अवरोध;

		totallen += len;
	पूर्ण जबतक (++i < cmd_num);

	वापस totallen + tx_desclen;
पूर्ण

अटल bool _rtl92s_firmware_set_h2c_cmd(काष्ठा ieee80211_hw *hw, u8 h2c_cmd,
					 u8 *pcmd_buffer)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_tcb_desc *cb_desc;
	काष्ठा sk_buff *skb;
	u32	element_id = 0;
	u32	cmd_len = 0;
	u32	len;

	चयन (h2c_cmd) अणु
	हाल FW_H2C_SETPWRMODE:
		element_id = H2C_SETPWRMODE_CMD ;
		cmd_len = माप(काष्ठा h2c_set_pwrmode_parm);
		अवरोध;
	हाल FW_H2C_JOINBSSRPT:
		element_id = H2C_JOINBSSRPT_CMD;
		cmd_len = माप(काष्ठा h2c_joinbss_rpt_parm);
		अवरोध;
	हाल FW_H2C_WOWLAN_UPDATE_GTK:
		element_id = H2C_WOWLAN_UPDATE_GTK_CMD;
		cmd_len = माप(काष्ठा h2c_wpa_two_way_parm);
		अवरोध;
	हाल FW_H2C_WOWLAN_UPDATE_IV:
		element_id = H2C_WOWLAN_UPDATE_IV_CMD;
		cmd_len = माप(अचिन्हित दीर्घ दीर्घ);
		अवरोध;
	हाल FW_H2C_WOWLAN_OFFLOAD:
		element_id = H2C_WOWLAN_FW_OFFLOAD;
		cmd_len = माप(u8);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	len = _rtl92s_get_h2c_cmdlen(MAX_TRANSMIT_BUFFER_SIZE, 1, &cmd_len);
	skb = dev_alloc_skb(len);
	अगर (!skb)
		वापस false;
	cb_desc = (काष्ठा rtl_tcb_desc *)(skb->cb);
	cb_desc->queue_index = TXCMD_QUEUE;
	cb_desc->cmd_or_init = DESC_PACKET_TYPE_NORMAL;
	cb_desc->last_inipkt = false;

	_rtl92s_fill_h2c_cmd(skb, MAX_TRANSMIT_BUFFER_SIZE, 1, &element_id,
			&cmd_len, &pcmd_buffer,	&rtlhal->h2c_txcmd_seq);
	_rtl92s_cmd_send_packet(hw, skb, false);
	rtlpriv->cfg->ops->tx_polling(hw, TXCMD_QUEUE);

	वापस true;
पूर्ण

व्योम rtl92s_set_fw_pwrmode_cmd(काष्ठा ieee80211_hw *hw, u8 mode)
अणु
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा h2c_set_pwrmode_parm	pwrmode;
	u16 max_wakeup_period = 0;

	pwrmode.mode = mode;
	pwrmode.flag_low_traffic_en = 0;
	pwrmode.flag_lpnav_en = 0;
	pwrmode.flag_rf_low_snr_en = 0;
	pwrmode.flag_dps_en = 0;
	pwrmode.bcn_rx_en = 0;
	pwrmode.bcn_to = 0;
	le16p_replace_bits((__le16 *)(((u8 *)(&pwrmode) + 8)),
			   mac->vअगर->bss_conf.beacon_पूर्णांक, GENMASK(15, 0));
	pwrmode.app_itv = 0;
	pwrmode.awake_bcn_itvl = ppsc->reg_max_lps_awakeपूर्णांकvl;
	pwrmode.smart_ps = 1;
	pwrmode.bcn_pass_period = 10;

	/* Set beacon pass count */
	अगर (pwrmode.mode == FW_PS_MIN_MODE)
		max_wakeup_period = mac->vअगर->bss_conf.beacon_पूर्णांक;
	अन्यथा अगर (pwrmode.mode == FW_PS_MAX_MODE)
		max_wakeup_period = mac->vअगर->bss_conf.beacon_पूर्णांक *
			mac->vअगर->bss_conf.dtim_period;

	अगर (max_wakeup_period >= 500)
		pwrmode.bcn_pass_cnt = 1;
	अन्यथा अगर ((max_wakeup_period >= 300) && (max_wakeup_period < 500))
		pwrmode.bcn_pass_cnt = 2;
	अन्यथा अगर ((max_wakeup_period >= 200) && (max_wakeup_period < 300))
		pwrmode.bcn_pass_cnt = 3;
	अन्यथा अगर ((max_wakeup_period >= 20) && (max_wakeup_period < 200))
		pwrmode.bcn_pass_cnt = 5;
	अन्यथा
		pwrmode.bcn_pass_cnt = 1;

	_rtl92s_firmware_set_h2c_cmd(hw, FW_H2C_SETPWRMODE, (u8 *)&pwrmode);

पूर्ण

व्योम rtl92s_set_fw_joinbss_report_cmd(काष्ठा ieee80211_hw *hw,
		u8 mstatus, u8 ps_qosinfo)
अणु
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा h2c_joinbss_rpt_parm joinbss_rpt;

	joinbss_rpt.opmode = mstatus;
	joinbss_rpt.ps_qos_info = ps_qosinfo;
	joinbss_rpt.bssid[0] = mac->bssid[0];
	joinbss_rpt.bssid[1] = mac->bssid[1];
	joinbss_rpt.bssid[2] = mac->bssid[2];
	joinbss_rpt.bssid[3] = mac->bssid[3];
	joinbss_rpt.bssid[4] = mac->bssid[4];
	joinbss_rpt.bssid[5] = mac->bssid[5];
	le16p_replace_bits((__le16 *)(((u8 *)(&joinbss_rpt) + 8)),
			   mac->vअगर->bss_conf.beacon_पूर्णांक, GENMASK(15, 0));
	le16p_replace_bits((__le16 *)(((u8 *)(&joinbss_rpt) + 10)),
			   mac->assoc_id, GENMASK(15, 0));

	_rtl92s_firmware_set_h2c_cmd(hw, FW_H2C_JOINBSSRPT, (u8 *)&joinbss_rpt);
पूर्ण

