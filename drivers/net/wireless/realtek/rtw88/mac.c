<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#समावेश "main.h"
#समावेश "mac.h"
#समावेश "reg.h"
#समावेश "fw.h"
#समावेश "debug.h"

व्योम rtw_set_channel_mac(काष्ठा rtw_dev *rtwdev, u8 channel, u8 bw,
			 u8 primary_ch_idx)
अणु
	u8 txsc40 = 0, txsc20 = 0;
	u32 value32;
	u8 value8;

	txsc20 = primary_ch_idx;
	अगर (bw == RTW_CHANNEL_WIDTH_80) अणु
		अगर (txsc20 == RTW_SC_20_UPPER || txsc20 == RTW_SC_20_UPMOST)
			txsc40 = RTW_SC_40_UPPER;
		अन्यथा
			txsc40 = RTW_SC_40_LOWER;
	पूर्ण
	rtw_ग_लिखो8(rtwdev, REG_DATA_SC,
		   BIT_TXSC_20M(txsc20) | BIT_TXSC_40M(txsc40));

	value32 = rtw_पढ़ो32(rtwdev, REG_WMAC_TRXPTCL_CTL);
	value32 &= ~BIT_RFMOD;
	चयन (bw) अणु
	हाल RTW_CHANNEL_WIDTH_80:
		value32 |= BIT_RFMOD_80M;
		अवरोध;
	हाल RTW_CHANNEL_WIDTH_40:
		value32 |= BIT_RFMOD_40M;
		अवरोध;
	हाल RTW_CHANNEL_WIDTH_20:
	शेष:
		अवरोध;
	पूर्ण
	rtw_ग_लिखो32(rtwdev, REG_WMAC_TRXPTCL_CTL, value32);

	अगर (rtw_chip_wcpu_11n(rtwdev))
		वापस;

	value32 = rtw_पढ़ो32(rtwdev, REG_AFE_CTRL1) & ~(BIT_MAC_CLK_SEL);
	value32 |= (MAC_CLK_HW_DEF_80M << BIT_SHIFT_MAC_CLK_SEL);
	rtw_ग_लिखो32(rtwdev, REG_AFE_CTRL1, value32);

	rtw_ग_लिखो8(rtwdev, REG_USTIME_TSF, MAC_CLK_SPEED);
	rtw_ग_लिखो8(rtwdev, REG_USTIME_EDCA, MAC_CLK_SPEED);

	value8 = rtw_पढ़ो8(rtwdev, REG_CCK_CHECK);
	value8 = value8 & ~BIT_CHECK_CCK_EN;
	अगर (IS_CH_5G_BAND(channel))
		value8 |= BIT_CHECK_CCK_EN;
	rtw_ग_लिखो8(rtwdev, REG_CCK_CHECK, value8);
पूर्ण
EXPORT_SYMBOL(rtw_set_channel_mac);

अटल पूर्णांक rtw_mac_pre_प्रणाली_cfg(काष्ठा rtw_dev *rtwdev)
अणु
	u32 value32;
	u8 value8;

	rtw_ग_लिखो8(rtwdev, REG_RSV_CTRL, 0);

	अगर (rtw_chip_wcpu_11n(rtwdev)) अणु
		अगर (rtw_पढ़ो32(rtwdev, REG_SYS_CFG1) & BIT_LDO)
			rtw_ग_लिखो8(rtwdev, REG_LDO_SWR_CTRL, LDO_SEL);
		अन्यथा
			rtw_ग_लिखो8(rtwdev, REG_LDO_SWR_CTRL, SPS_SEL);
		वापस 0;
	पूर्ण

	चयन (rtw_hci_type(rtwdev)) अणु
	हाल RTW_HCI_TYPE_PCIE:
		rtw_ग_लिखो32_set(rtwdev, REG_HCI_OPT_CTRL, BIT_BT_DIG_CLK_EN);
		अवरोध;
	हाल RTW_HCI_TYPE_USB:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* config PIN Mux */
	value32 = rtw_पढ़ो32(rtwdev, REG_PAD_CTRL1);
	value32 |= BIT_PAPE_WLBT_SEL | BIT_LNAON_WLBT_SEL;
	rtw_ग_लिखो32(rtwdev, REG_PAD_CTRL1, value32);

	value32 = rtw_पढ़ो32(rtwdev, REG_LED_CFG);
	value32 &= ~(BIT_PAPE_SEL_EN | BIT_LNAON_SEL_EN);
	rtw_ग_लिखो32(rtwdev, REG_LED_CFG, value32);

	value32 = rtw_पढ़ो32(rtwdev, REG_GPIO_MUXCFG);
	value32 |= BIT_WLRFE_4_5_EN;
	rtw_ग_लिखो32(rtwdev, REG_GPIO_MUXCFG, value32);

	/* disable BB/RF */
	value8 = rtw_पढ़ो8(rtwdev, REG_SYS_FUNC_EN);
	value8 &= ~(BIT_FEN_BB_RSTB | BIT_FEN_BB_GLB_RST);
	rtw_ग_लिखो8(rtwdev, REG_SYS_FUNC_EN, value8);

	value8 = rtw_पढ़ो8(rtwdev, REG_RF_CTRL);
	value8 &= ~(BIT_RF_SDM_RSTB | BIT_RF_RSTB | BIT_RF_EN);
	rtw_ग_लिखो8(rtwdev, REG_RF_CTRL, value8);

	value32 = rtw_पढ़ो32(rtwdev, REG_WLRF1);
	value32 &= ~BIT_WLRF1_BBRF_EN;
	rtw_ग_लिखो32(rtwdev, REG_WLRF1, value32);

	वापस 0;
पूर्ण

अटल bool करो_pwr_poll_cmd(काष्ठा rtw_dev *rtwdev, u32 addr, u32 mask, u32 target)
अणु
	u32 val;

	target &= mask;

	वापस पढ़ो_poll_समयout_atomic(rtw_पढ़ो8, val, (val & mask) == target,
					50, 50 * RTW_PWR_POLLING_CNT, false,
					rtwdev, addr) == 0;
पूर्ण

अटल पूर्णांक rtw_pwr_cmd_polling(काष्ठा rtw_dev *rtwdev,
			       स्थिर काष्ठा rtw_pwr_seq_cmd *cmd)
अणु
	u8 value;
	u32 offset;

	अगर (cmd->base == RTW_PWR_ADDR_SDIO)
		offset = cmd->offset | SDIO_LOCAL_OFFSET;
	अन्यथा
		offset = cmd->offset;

	अगर (करो_pwr_poll_cmd(rtwdev, offset, cmd->mask, cmd->value))
		वापस 0;

	अगर (rtw_hci_type(rtwdev) != RTW_HCI_TYPE_PCIE)
		जाओ err;

	/* अगर PCIE, toggle BIT_PFM_WOWL and try again */
	value = rtw_पढ़ो8(rtwdev, REG_SYS_PW_CTRL);
	अगर (rtwdev->chip->id == RTW_CHIP_TYPE_8723D)
		rtw_ग_लिखो8(rtwdev, REG_SYS_PW_CTRL, value & ~BIT_PFM_WOWL);
	rtw_ग_लिखो8(rtwdev, REG_SYS_PW_CTRL, value | BIT_PFM_WOWL);
	rtw_ग_लिखो8(rtwdev, REG_SYS_PW_CTRL, value & ~BIT_PFM_WOWL);
	अगर (rtwdev->chip->id == RTW_CHIP_TYPE_8723D)
		rtw_ग_लिखो8(rtwdev, REG_SYS_PW_CTRL, value | BIT_PFM_WOWL);

	अगर (करो_pwr_poll_cmd(rtwdev, offset, cmd->mask, cmd->value))
		वापस 0;

err:
	rtw_err(rtwdev, "failed to poll offset=0x%x mask=0x%x value=0x%x\n",
		offset, cmd->mask, cmd->value);
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक rtw_sub_pwr_seq_parser(काष्ठा rtw_dev *rtwdev, u8 पूर्णांकf_mask,
				  u8 cut_mask,
				  स्थिर काष्ठा rtw_pwr_seq_cmd *cmd)
अणु
	स्थिर काष्ठा rtw_pwr_seq_cmd *cur_cmd;
	u32 offset;
	u8 value;

	क्रम (cur_cmd = cmd; cur_cmd->cmd != RTW_PWR_CMD_END; cur_cmd++) अणु
		अगर (!(cur_cmd->पूर्णांकf_mask & पूर्णांकf_mask) ||
		    !(cur_cmd->cut_mask & cut_mask))
			जारी;

		चयन (cur_cmd->cmd) अणु
		हाल RTW_PWR_CMD_WRITE:
			offset = cur_cmd->offset;

			अगर (cur_cmd->base == RTW_PWR_ADDR_SDIO)
				offset |= SDIO_LOCAL_OFFSET;

			value = rtw_पढ़ो8(rtwdev, offset);
			value &= ~cur_cmd->mask;
			value |= (cur_cmd->value & cur_cmd->mask);
			rtw_ग_लिखो8(rtwdev, offset, value);
			अवरोध;
		हाल RTW_PWR_CMD_POLLING:
			अगर (rtw_pwr_cmd_polling(rtwdev, cur_cmd))
				वापस -EBUSY;
			अवरोध;
		हाल RTW_PWR_CMD_DELAY:
			अगर (cur_cmd->value == RTW_PWR_DELAY_US)
				udelay(cur_cmd->offset);
			अन्यथा
				mdelay(cur_cmd->offset);
			अवरोध;
		हाल RTW_PWR_CMD_READ:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_pwr_seq_parser(काष्ठा rtw_dev *rtwdev,
			      स्थिर काष्ठा rtw_pwr_seq_cmd **cmd_seq)
अणु
	u8 cut_mask;
	u8 पूर्णांकf_mask;
	u8 cut;
	u32 idx = 0;
	स्थिर काष्ठा rtw_pwr_seq_cmd *cmd;
	पूर्णांक ret;

	cut = rtwdev->hal.cut_version;
	cut_mask = cut_version_to_mask(cut);
	चयन (rtw_hci_type(rtwdev)) अणु
	हाल RTW_HCI_TYPE_PCIE:
		पूर्णांकf_mask = BIT(2);
		अवरोध;
	हाल RTW_HCI_TYPE_USB:
		पूर्णांकf_mask = BIT(1);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	करो अणु
		cmd = cmd_seq[idx];
		अगर (!cmd)
			अवरोध;

		ret = rtw_sub_pwr_seq_parser(rtwdev, पूर्णांकf_mask, cut_mask, cmd);
		अगर (ret)
			वापस -EBUSY;

		idx++;
	पूर्ण जबतक (1);

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_mac_घातer_चयन(काष्ठा rtw_dev *rtwdev, bool pwr_on)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	स्थिर काष्ठा rtw_pwr_seq_cmd **pwr_seq;
	u8 rpwm;
	bool cur_pwr;

	अगर (rtw_chip_wcpu_11ac(rtwdev)) अणु
		rpwm = rtw_पढ़ो8(rtwdev, rtwdev->hci.rpwm_addr);

		/* Check FW still exist or not */
		अगर (rtw_पढ़ो16(rtwdev, REG_MCUFW_CTRL) == 0xC078) अणु
			rpwm = (rpwm ^ BIT_RPWM_TOGGLE) & BIT_RPWM_TOGGLE;
			rtw_ग_लिखो8(rtwdev, rtwdev->hci.rpwm_addr, rpwm);
		पूर्ण
	पूर्ण

	अगर (rtw_पढ़ो8(rtwdev, REG_CR) == 0xea)
		cur_pwr = false;
	अन्यथा अगर (rtw_hci_type(rtwdev) == RTW_HCI_TYPE_USB &&
		 (rtw_पढ़ो8(rtwdev, REG_SYS_STATUS1 + 1) & BIT(0)))
		cur_pwr = false;
	अन्यथा
		cur_pwr = true;

	अगर (pwr_on == cur_pwr)
		वापस -EALREADY;

	pwr_seq = pwr_on ? chip->pwr_on_seq : chip->pwr_off_seq;
	अगर (rtw_pwr_seq_parser(rtwdev, pwr_seq))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक __rtw_mac_init_प्रणाली_cfg(काष्ठा rtw_dev *rtwdev)
अणु
	u8 sys_func_en = rtwdev->chip->sys_func_en;
	u8 value8;
	u32 value, पंचांगp;

	value = rtw_पढ़ो32(rtwdev, REG_CPU_DMEM_CON);
	value |= BIT_WL_PLATFORM_RST | BIT_DDMA_EN;
	rtw_ग_लिखो32(rtwdev, REG_CPU_DMEM_CON, value);

	rtw_ग_लिखो8_set(rtwdev, REG_SYS_FUNC_EN + 1, sys_func_en);
	value8 = (rtw_पढ़ो8(rtwdev, REG_CR_EXT + 3) & 0xF0) | 0x0C;
	rtw_ग_लिखो8(rtwdev, REG_CR_EXT + 3, value8);

	/* disable boot-from-flash क्रम driver's DL FW */
	पंचांगp = rtw_पढ़ो32(rtwdev, REG_MCUFW_CTRL);
	अगर (पंचांगp & BIT_BOOT_FSPI_EN) अणु
		rtw_ग_लिखो32(rtwdev, REG_MCUFW_CTRL, पंचांगp & (~BIT_BOOT_FSPI_EN));
		value = rtw_पढ़ो32(rtwdev, REG_GPIO_MUXCFG) & (~BIT_FSPI_EN);
		rtw_ग_लिखो32(rtwdev, REG_GPIO_MUXCFG, value);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __rtw_mac_init_प्रणाली_cfg_legacy(काष्ठा rtw_dev *rtwdev)
अणु
	rtw_ग_लिखो8(rtwdev, REG_CR, 0xff);
	mdelay(2);
	rtw_ग_लिखो8(rtwdev, REG_HWSEQ_CTRL, 0x7f);
	mdelay(2);

	rtw_ग_लिखो8_set(rtwdev, REG_SYS_CLKR, BIT_WAKEPAD_EN);
	rtw_ग_लिखो16_clr(rtwdev, REG_GPIO_MUXCFG, BIT_EN_SIC);

	rtw_ग_लिखो16(rtwdev, REG_CR, 0x2ff);

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_mac_init_प्रणाली_cfg(काष्ठा rtw_dev *rtwdev)
अणु
	अगर (rtw_chip_wcpu_11n(rtwdev))
		वापस __rtw_mac_init_प्रणाली_cfg_legacy(rtwdev);

	वापस __rtw_mac_init_प्रणाली_cfg(rtwdev);
पूर्ण

पूर्णांक rtw_mac_घातer_on(काष्ठा rtw_dev *rtwdev)
अणु
	पूर्णांक ret = 0;

	ret = rtw_mac_pre_प्रणाली_cfg(rtwdev);
	अगर (ret)
		जाओ err;

	ret = rtw_mac_घातer_चयन(rtwdev, true);
	अगर (ret == -EALREADY) अणु
		rtw_mac_घातer_चयन(rtwdev, false);
		ret = rtw_mac_घातer_चयन(rtwdev, true);
		अगर (ret)
			जाओ err;
	पूर्ण अन्यथा अगर (ret) अणु
		जाओ err;
	पूर्ण

	ret = rtw_mac_init_प्रणाली_cfg(rtwdev);
	अगर (ret)
		जाओ err;

	वापस 0;

err:
	rtw_err(rtwdev, "mac power on failed");
	वापस ret;
पूर्ण

व्योम rtw_mac_घातer_off(काष्ठा rtw_dev *rtwdev)
अणु
	rtw_mac_घातer_चयन(rtwdev, false);
पूर्ण

अटल bool check_firmware_size(स्थिर u8 *data, u32 size)
अणु
	स्थिर काष्ठा rtw_fw_hdr *fw_hdr = (स्थिर काष्ठा rtw_fw_hdr *)data;
	u32 dmem_size;
	u32 imem_size;
	u32 emem_size;
	u32 real_size;

	dmem_size = le32_to_cpu(fw_hdr->dmem_size);
	imem_size = le32_to_cpu(fw_hdr->imem_size);
	emem_size = (fw_hdr->mem_usage & BIT(4)) ?
		    le32_to_cpu(fw_hdr->emem_size) : 0;

	dmem_size += FW_HDR_CHKSUM_SIZE;
	imem_size += FW_HDR_CHKSUM_SIZE;
	emem_size += emem_size ? FW_HDR_CHKSUM_SIZE : 0;
	real_size = FW_HDR_SIZE + dmem_size + imem_size + emem_size;
	अगर (real_size != size)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम wlan_cpu_enable(काष्ठा rtw_dev *rtwdev, bool enable)
अणु
	अगर (enable) अणु
		/* cpu io पूर्णांकerface enable */
		rtw_ग_लिखो8_set(rtwdev, REG_RSV_CTRL + 1, BIT_WLMCU_IOIF);

		/* cpu enable */
		rtw_ग_लिखो8_set(rtwdev, REG_SYS_FUNC_EN + 1, BIT_FEN_CPUEN);
	पूर्ण अन्यथा अणु
		/* cpu io पूर्णांकerface disable */
		rtw_ग_लिखो8_clr(rtwdev, REG_SYS_FUNC_EN + 1, BIT_FEN_CPUEN);

		/* cpu disable */
		rtw_ग_लिखो8_clr(rtwdev, REG_RSV_CTRL + 1, BIT_WLMCU_IOIF);
	पूर्ण
पूर्ण

#घोषणा DLFW_RESTORE_REG_NUM 6

अटल व्योम करोwnload_firmware_reg_backup(काष्ठा rtw_dev *rtwdev,
					 काष्ठा rtw_backup_info *bckp)
अणु
	u8 पंचांगp;
	u8 bckp_idx = 0;

	/* set HIQ to hi priority */
	bckp[bckp_idx].len = 1;
	bckp[bckp_idx].reg = REG_TXDMA_PQ_MAP + 1;
	bckp[bckp_idx].val = rtw_पढ़ो8(rtwdev, REG_TXDMA_PQ_MAP + 1);
	bckp_idx++;
	पंचांगp = RTW_DMA_MAPPING_HIGH << 6;
	rtw_ग_लिखो8(rtwdev, REG_TXDMA_PQ_MAP + 1, पंचांगp);

	/* DLFW only use HIQ, map HIQ to hi priority */
	bckp[bckp_idx].len = 1;
	bckp[bckp_idx].reg = REG_CR;
	bckp[bckp_idx].val = rtw_पढ़ो8(rtwdev, REG_CR);
	bckp_idx++;
	bckp[bckp_idx].len = 4;
	bckp[bckp_idx].reg = REG_H2CQ_CSR;
	bckp[bckp_idx].val = BIT_H2CQ_FULL;
	bckp_idx++;
	पंचांगp = BIT_HCI_TXDMA_EN | BIT_TXDMA_EN;
	rtw_ग_लिखो8(rtwdev, REG_CR, पंचांगp);
	rtw_ग_लिखो32(rtwdev, REG_H2CQ_CSR, BIT_H2CQ_FULL);

	/* Config hi priority queue and खुला priority queue page number */
	bckp[bckp_idx].len = 2;
	bckp[bckp_idx].reg = REG_FIFOPAGE_INFO_1;
	bckp[bckp_idx].val = rtw_पढ़ो16(rtwdev, REG_FIFOPAGE_INFO_1);
	bckp_idx++;
	bckp[bckp_idx].len = 4;
	bckp[bckp_idx].reg = REG_RQPN_CTRL_2;
	bckp[bckp_idx].val = rtw_पढ़ो32(rtwdev, REG_RQPN_CTRL_2) | BIT_LD_RQPN;
	bckp_idx++;
	rtw_ग_लिखो16(rtwdev, REG_FIFOPAGE_INFO_1, 0x200);
	rtw_ग_लिखो32(rtwdev, REG_RQPN_CTRL_2, bckp[bckp_idx - 1].val);

	/* Disable beacon related functions */
	पंचांगp = rtw_पढ़ो8(rtwdev, REG_BCN_CTRL);
	bckp[bckp_idx].len = 1;
	bckp[bckp_idx].reg = REG_BCN_CTRL;
	bckp[bckp_idx].val = पंचांगp;
	bckp_idx++;
	पंचांगp = (u8)((पंचांगp & (~BIT_EN_BCN_FUNCTION)) | BIT_DIS_TSF_UDT);
	rtw_ग_लिखो8(rtwdev, REG_BCN_CTRL, पंचांगp);

	WARN(bckp_idx != DLFW_RESTORE_REG_NUM, "wrong backup number\n");
पूर्ण

अटल व्योम करोwnload_firmware_reset_platक्रमm(काष्ठा rtw_dev *rtwdev)
अणु
	rtw_ग_लिखो8_clr(rtwdev, REG_CPU_DMEM_CON + 2, BIT_WL_PLATFORM_RST >> 16);
	rtw_ग_लिखो8_clr(rtwdev, REG_SYS_CLK_CTRL + 1, BIT_CPU_CLK_EN >> 8);
	rtw_ग_लिखो8_set(rtwdev, REG_CPU_DMEM_CON + 2, BIT_WL_PLATFORM_RST >> 16);
	rtw_ग_लिखो8_set(rtwdev, REG_SYS_CLK_CTRL + 1, BIT_CPU_CLK_EN >> 8);
पूर्ण

अटल व्योम करोwnload_firmware_reg_restore(काष्ठा rtw_dev *rtwdev,
					  काष्ठा rtw_backup_info *bckp,
					  u8 bckp_num)
अणु
	rtw_restore_reg(rtwdev, bckp, bckp_num);
पूर्ण

#घोषणा TX_DESC_SIZE 48

अटल पूर्णांक send_firmware_pkt_rsvd_page(काष्ठा rtw_dev *rtwdev, u16 pg_addr,
				       स्थिर u8 *data, u32 size)
अणु
	u8 *buf;
	पूर्णांक ret;

	buf = kmemdup(data, size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = rtw_fw_ग_लिखो_data_rsvd_page(rtwdev, pg_addr, buf, size);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक
send_firmware_pkt(काष्ठा rtw_dev *rtwdev, u16 pg_addr, स्थिर u8 *data, u32 size)
अणु
	पूर्णांक ret;

	अगर (rtw_hci_type(rtwdev) == RTW_HCI_TYPE_USB &&
	    !((size + TX_DESC_SIZE) & (512 - 1)))
		size += 1;

	ret = send_firmware_pkt_rsvd_page(rtwdev, pg_addr, data, size);
	अगर (ret)
		rtw_err(rtwdev, "failed to download rsvd page\n");

	वापस ret;
पूर्ण

अटल पूर्णांक
iddma_enable(काष्ठा rtw_dev *rtwdev, u32 src, u32 dst, u32 ctrl)
अणु
	rtw_ग_लिखो32(rtwdev, REG_DDMA_CH0SA, src);
	rtw_ग_लिखो32(rtwdev, REG_DDMA_CH0DA, dst);
	rtw_ग_लिखो32(rtwdev, REG_DDMA_CH0CTRL, ctrl);

	अगर (!check_hw_पढ़ोy(rtwdev, REG_DDMA_CH0CTRL, BIT_DDMACH0_OWN, 0))
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल पूर्णांक iddma_करोwnload_firmware(काष्ठा rtw_dev *rtwdev, u32 src, u32 dst,
				   u32 len, u8 first)
अणु
	u32 ch0_ctrl = BIT_DDMACH0_CHKSUM_EN | BIT_DDMACH0_OWN;

	अगर (!check_hw_पढ़ोy(rtwdev, REG_DDMA_CH0CTRL, BIT_DDMACH0_OWN, 0))
		वापस -EBUSY;

	ch0_ctrl |= len & BIT_MASK_DDMACH0_DLEN;
	अगर (!first)
		ch0_ctrl |= BIT_DDMACH0_CHKSUM_CONT;

	अगर (iddma_enable(rtwdev, src, dst, ch0_ctrl))
		वापस -EBUSY;

	वापस 0;
पूर्ण

पूर्णांक rtw_ddma_to_fw_fअगरo(काष्ठा rtw_dev *rtwdev, u32 ocp_src, u32 size)
अणु
	u32 ch0_ctrl = BIT_DDMACH0_OWN | BIT_DDMACH0_DDMA_MODE;

	अगर (!check_hw_पढ़ोy(rtwdev, REG_DDMA_CH0CTRL, BIT_DDMACH0_OWN, 0)) अणु
		rtw_dbg(rtwdev, RTW_DBG_FW, "busy to start ddma\n");
		वापस -EBUSY;
	पूर्ण

	ch0_ctrl |= size & BIT_MASK_DDMACH0_DLEN;

	अगर (iddma_enable(rtwdev, ocp_src, OCPBASE_RXBUF_FW_88XX, ch0_ctrl)) अणु
		rtw_dbg(rtwdev, RTW_DBG_FW, "busy to complete ddma\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool
check_fw_checksum(काष्ठा rtw_dev *rtwdev, u32 addr)
अणु
	u8 fw_ctrl;

	fw_ctrl = rtw_पढ़ो8(rtwdev, REG_MCUFW_CTRL);

	अगर (rtw_पढ़ो32(rtwdev, REG_DDMA_CH0CTRL) & BIT_DDMACH0_CHKSUM_STS) अणु
		अगर (addr < OCPBASE_DMEM_88XX) अणु
			fw_ctrl |= BIT_IMEM_DW_OK;
			fw_ctrl &= ~BIT_IMEM_CHKSUM_OK;
			rtw_ग_लिखो8(rtwdev, REG_MCUFW_CTRL, fw_ctrl);
		पूर्ण अन्यथा अणु
			fw_ctrl |= BIT_DMEM_DW_OK;
			fw_ctrl &= ~BIT_DMEM_CHKSUM_OK;
			rtw_ग_लिखो8(rtwdev, REG_MCUFW_CTRL, fw_ctrl);
		पूर्ण

		rtw_err(rtwdev, "invalid fw checksum\n");

		वापस false;
	पूर्ण

	अगर (addr < OCPBASE_DMEM_88XX) अणु
		fw_ctrl |= (BIT_IMEM_DW_OK | BIT_IMEM_CHKSUM_OK);
		rtw_ग_लिखो8(rtwdev, REG_MCUFW_CTRL, fw_ctrl);
	पूर्ण अन्यथा अणु
		fw_ctrl |= (BIT_DMEM_DW_OK | BIT_DMEM_CHKSUM_OK);
		rtw_ग_लिखो8(rtwdev, REG_MCUFW_CTRL, fw_ctrl);
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक
करोwnload_firmware_to_mem(काष्ठा rtw_dev *rtwdev, स्थिर u8 *data,
			 u32 src, u32 dst, u32 size)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	u32 desc_size = chip->tx_pkt_desc_sz;
	u8 first_part;
	u32 mem_offset;
	u32 residue_size;
	u32 pkt_size;
	u32 max_size = 0x1000;
	u32 val;
	पूर्णांक ret;

	mem_offset = 0;
	first_part = 1;
	residue_size = size;

	val = rtw_पढ़ो32(rtwdev, REG_DDMA_CH0CTRL);
	val |= BIT_DDMACH0_RESET_CHKSUM_STS;
	rtw_ग_लिखो32(rtwdev, REG_DDMA_CH0CTRL, val);

	जबतक (residue_size) अणु
		अगर (residue_size >= max_size)
			pkt_size = max_size;
		अन्यथा
			pkt_size = residue_size;

		ret = send_firmware_pkt(rtwdev, (u16)(src >> 7),
					data + mem_offset, pkt_size);
		अगर (ret)
			वापस ret;

		ret = iddma_करोwnload_firmware(rtwdev, OCPBASE_TXBUF_88XX +
					      src + desc_size,
					      dst + mem_offset, pkt_size,
					      first_part);
		अगर (ret)
			वापस ret;

		first_part = 0;
		mem_offset += pkt_size;
		residue_size -= pkt_size;
	पूर्ण

	अगर (!check_fw_checksum(rtwdev, dst))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक
start_करोwnload_firmware(काष्ठा rtw_dev *rtwdev, स्थिर u8 *data, u32 size)
अणु
	स्थिर काष्ठा rtw_fw_hdr *fw_hdr = (स्थिर काष्ठा rtw_fw_hdr *)data;
	स्थिर u8 *cur_fw;
	u16 val;
	u32 imem_size;
	u32 dmem_size;
	u32 emem_size;
	u32 addr;
	पूर्णांक ret;

	dmem_size = le32_to_cpu(fw_hdr->dmem_size);
	imem_size = le32_to_cpu(fw_hdr->imem_size);
	emem_size = (fw_hdr->mem_usage & BIT(4)) ?
		    le32_to_cpu(fw_hdr->emem_size) : 0;
	dmem_size += FW_HDR_CHKSUM_SIZE;
	imem_size += FW_HDR_CHKSUM_SIZE;
	emem_size += emem_size ? FW_HDR_CHKSUM_SIZE : 0;

	val = (u16)(rtw_पढ़ो16(rtwdev, REG_MCUFW_CTRL) & 0x3800);
	val |= BIT_MCUFWDL_EN;
	rtw_ग_लिखो16(rtwdev, REG_MCUFW_CTRL, val);

	cur_fw = data + FW_HDR_SIZE;
	addr = le32_to_cpu(fw_hdr->dmem_addr);
	addr &= ~BIT(31);
	ret = करोwnload_firmware_to_mem(rtwdev, cur_fw, 0, addr, dmem_size);
	अगर (ret)
		वापस ret;

	cur_fw = data + FW_HDR_SIZE + dmem_size;
	addr = le32_to_cpu(fw_hdr->imem_addr);
	addr &= ~BIT(31);
	ret = करोwnload_firmware_to_mem(rtwdev, cur_fw, 0, addr, imem_size);
	अगर (ret)
		वापस ret;

	अगर (emem_size) अणु
		cur_fw = data + FW_HDR_SIZE + dmem_size + imem_size;
		addr = le32_to_cpu(fw_hdr->emem_addr);
		addr &= ~BIT(31);
		ret = करोwnload_firmware_to_mem(rtwdev, cur_fw, 0, addr,
					       emem_size);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक करोwnload_firmware_validate(काष्ठा rtw_dev *rtwdev)
अणु
	u32 fw_key;

	अगर (!check_hw_पढ़ोy(rtwdev, REG_MCUFW_CTRL, FW_READY_MASK, FW_READY)) अणु
		fw_key = rtw_पढ़ो32(rtwdev, REG_FW_DBG7) & FW_KEY_MASK;
		अगर (fw_key == ILLEGAL_KEY_GROUP)
			rtw_err(rtwdev, "invalid fw key\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम करोwnload_firmware_end_flow(काष्ठा rtw_dev *rtwdev)
अणु
	u16 fw_ctrl;

	rtw_ग_लिखो32(rtwdev, REG_TXDMA_STATUS, BTI_PAGE_OVF);

	/* Check IMEM & DMEM checksum is OK or not */
	fw_ctrl = rtw_पढ़ो16(rtwdev, REG_MCUFW_CTRL);
	अगर ((fw_ctrl & BIT_CHECK_SUM_OK) != BIT_CHECK_SUM_OK)
		वापस;

	fw_ctrl = (fw_ctrl | BIT_FW_DW_RDY) & ~BIT_MCUFWDL_EN;
	rtw_ग_लिखो16(rtwdev, REG_MCUFW_CTRL, fw_ctrl);
पूर्ण

अटल पूर्णांक __rtw_करोwnload_firmware(काष्ठा rtw_dev *rtwdev,
				   काष्ठा rtw_fw_state *fw)
अणु
	काष्ठा rtw_backup_info bckp[DLFW_RESTORE_REG_NUM];
	स्थिर u8 *data = fw->firmware->data;
	u32 size = fw->firmware->size;
	u32 ltecoex_bckp;
	पूर्णांक ret;

	अगर (!check_firmware_size(data, size))
		वापस -EINVAL;

	अगर (!ltecoex_पढ़ो_reg(rtwdev, 0x38, &ltecoex_bckp))
		वापस -EBUSY;

	wlan_cpu_enable(rtwdev, false);

	करोwnload_firmware_reg_backup(rtwdev, bckp);
	करोwnload_firmware_reset_platक्रमm(rtwdev);

	ret = start_करोwnload_firmware(rtwdev, data, size);
	अगर (ret)
		जाओ dlfw_fail;

	करोwnload_firmware_reg_restore(rtwdev, bckp, DLFW_RESTORE_REG_NUM);

	करोwnload_firmware_end_flow(rtwdev);

	wlan_cpu_enable(rtwdev, true);

	अगर (!ltecoex_reg_ग_लिखो(rtwdev, 0x38, ltecoex_bckp))
		वापस -EBUSY;

	ret = करोwnload_firmware_validate(rtwdev);
	अगर (ret)
		जाओ dlfw_fail;

	/* reset desc and index */
	rtw_hci_setup(rtwdev);

	rtwdev->h2c.last_box_num = 0;
	rtwdev->h2c.seq = 0;

	set_bit(RTW_FLAG_FW_RUNNING, rtwdev->flags);

	वापस 0;

dlfw_fail:
	/* Disable FWDL_EN */
	rtw_ग_लिखो8_clr(rtwdev, REG_MCUFW_CTRL, BIT_MCUFWDL_EN);
	rtw_ग_लिखो8_set(rtwdev, REG_SYS_FUNC_EN + 1, BIT_FEN_CPUEN);

	वापस ret;
पूर्ण

अटल व्योम en_करोwnload_firmware_legacy(काष्ठा rtw_dev *rtwdev, bool en)
अणु
	पूर्णांक try;

	अगर (en) अणु
		wlan_cpu_enable(rtwdev, false);
		wlan_cpu_enable(rtwdev, true);

		rtw_ग_लिखो8_set(rtwdev, REG_MCUFW_CTRL, BIT_MCUFWDL_EN);

		क्रम (try = 0; try < 10; try++) अणु
			अगर (rtw_पढ़ो8(rtwdev, REG_MCUFW_CTRL) & BIT_MCUFWDL_EN)
				जाओ fwdl_पढ़ोy;
			rtw_ग_लिखो8_set(rtwdev, REG_MCUFW_CTRL, BIT_MCUFWDL_EN);
			msleep(20);
		पूर्ण
		rtw_err(rtwdev, "failed to check fw download ready\n");
fwdl_पढ़ोy:
		rtw_ग_लिखो32_clr(rtwdev, REG_MCUFW_CTRL, BIT_ROM_DLEN);
	पूर्ण अन्यथा अणु
		rtw_ग_लिखो8_clr(rtwdev, REG_MCUFW_CTRL, BIT_MCUFWDL_EN);
	पूर्ण
पूर्ण

अटल व्योम
ग_लिखो_firmware_page(काष्ठा rtw_dev *rtwdev, u32 page, स्थिर u8 *data, u32 size)
अणु
	u32 val32;
	u32 block_nr;
	u32 reमुख्य_size;
	u32 ग_लिखो_addr = FW_START_ADDR_LEGACY;
	स्थिर __le32 *ptr = (स्थिर __le32 *)data;
	u32 block;
	__le32 reमुख्य_data = 0;

	block_nr = size >> DLFW_BLK_SIZE_SHIFT_LEGACY;
	reमुख्य_size = size & (DLFW_BLK_SIZE_LEGACY - 1);

	val32 = rtw_पढ़ो32(rtwdev, REG_MCUFW_CTRL);
	val32 &= ~BIT_ROM_PGE;
	val32 |= (page << BIT_SHIFT_ROM_PGE) & BIT_ROM_PGE;
	rtw_ग_लिखो32(rtwdev, REG_MCUFW_CTRL, val32);

	क्रम (block = 0; block < block_nr; block++) अणु
		rtw_ग_लिखो32(rtwdev, ग_लिखो_addr, le32_to_cpu(*ptr));

		ग_लिखो_addr += DLFW_BLK_SIZE_LEGACY;
		ptr++;
	पूर्ण

	अगर (reमुख्य_size) अणु
		स_नकल(&reमुख्य_data, ptr, reमुख्य_size);
		rtw_ग_लिखो32(rtwdev, ग_लिखो_addr, le32_to_cpu(reमुख्य_data));
	पूर्ण
पूर्ण

अटल पूर्णांक
करोwnload_firmware_legacy(काष्ठा rtw_dev *rtwdev, स्थिर u8 *data, u32 size)
अणु
	u32 page;
	u32 total_page;
	u32 last_page_size;

	data += माप(काष्ठा rtw_fw_hdr_legacy);
	size -= माप(काष्ठा rtw_fw_hdr_legacy);

	total_page = size >> DLFW_PAGE_SIZE_SHIFT_LEGACY;
	last_page_size = size & (DLFW_PAGE_SIZE_LEGACY - 1);

	rtw_ग_लिखो8_set(rtwdev, REG_MCUFW_CTRL, BIT_FWDL_CHK_RPT);

	क्रम (page = 0; page < total_page; page++) अणु
		ग_लिखो_firmware_page(rtwdev, page, data, DLFW_PAGE_SIZE_LEGACY);
		data += DLFW_PAGE_SIZE_LEGACY;
	पूर्ण
	अगर (last_page_size)
		ग_लिखो_firmware_page(rtwdev, page, data, last_page_size);

	अगर (!check_hw_पढ़ोy(rtwdev, REG_MCUFW_CTRL, BIT_FWDL_CHK_RPT, 1)) अणु
		rtw_err(rtwdev, "failed to check download firmware report\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक करोwnload_firmware_validate_legacy(काष्ठा rtw_dev *rtwdev)
अणु
	u32 val32;
	पूर्णांक try;

	val32 = rtw_पढ़ो32(rtwdev, REG_MCUFW_CTRL);
	val32 |= BIT_MCUFWDL_RDY;
	val32 &= ~BIT_WINTINI_RDY;
	rtw_ग_लिखो32(rtwdev, REG_MCUFW_CTRL, val32);

	wlan_cpu_enable(rtwdev, false);
	wlan_cpu_enable(rtwdev, true);

	क्रम (try = 0; try < 10; try++) अणु
		val32 = rtw_पढ़ो32(rtwdev, REG_MCUFW_CTRL);
		अगर ((val32 & FW_READY_LEGACY) == FW_READY_LEGACY)
			वापस 0;
		msleep(20);
	पूर्ण

	rtw_err(rtwdev, "failed to validate firmware\n");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक __rtw_करोwnload_firmware_legacy(काष्ठा rtw_dev *rtwdev,
					  काष्ठा rtw_fw_state *fw)
अणु
	पूर्णांक ret = 0;

	en_करोwnload_firmware_legacy(rtwdev, true);
	ret = करोwnload_firmware_legacy(rtwdev, fw->firmware->data, fw->firmware->size);
	en_करोwnload_firmware_legacy(rtwdev, false);
	अगर (ret)
		जाओ out;

	ret = करोwnload_firmware_validate_legacy(rtwdev);
	अगर (ret)
		जाओ out;

	/* reset desc and index */
	rtw_hci_setup(rtwdev);

	rtwdev->h2c.last_box_num = 0;
	rtwdev->h2c.seq = 0;

	set_bit(RTW_FLAG_FW_RUNNING, rtwdev->flags);

out:
	वापस ret;
पूर्ण

पूर्णांक rtw_करोwnload_firmware(काष्ठा rtw_dev *rtwdev, काष्ठा rtw_fw_state *fw)
अणु
	अगर (rtw_chip_wcpu_11n(rtwdev))
		वापस __rtw_करोwnload_firmware_legacy(rtwdev, fw);

	वापस __rtw_करोwnload_firmware(rtwdev, fw);
पूर्ण

अटल u32 get_priority_queues(काष्ठा rtw_dev *rtwdev, u32 queues)
अणु
	स्थिर काष्ठा rtw_rqpn *rqpn = rtwdev->fअगरo.rqpn;
	u32 prio_queues = 0;

	अगर (queues & BIT(IEEE80211_AC_VO))
		prio_queues |= BIT(rqpn->dma_map_vo);
	अगर (queues & BIT(IEEE80211_AC_VI))
		prio_queues |= BIT(rqpn->dma_map_vi);
	अगर (queues & BIT(IEEE80211_AC_BE))
		prio_queues |= BIT(rqpn->dma_map_be);
	अगर (queues & BIT(IEEE80211_AC_BK))
		prio_queues |= BIT(rqpn->dma_map_bk);

	वापस prio_queues;
पूर्ण

अटल व्योम __rtw_mac_flush_prio_queue(काष्ठा rtw_dev *rtwdev,
				       u32 prio_queue, bool drop)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	स्थिर काष्ठा rtw_prioq_addr *addr;
	bool wsize;
	u16 avail_page, rsvd_page;
	पूर्णांक i;

	अगर (prio_queue >= RTW_DMA_MAPPING_MAX)
		वापस;

	addr = &chip->prioq_addrs->prio[prio_queue];
	wsize = chip->prioq_addrs->wsize;

	/* check अगर all of the reserved pages are available क्रम 100 msecs */
	क्रम (i = 0; i < 5; i++) अणु
		rsvd_page = wsize ? rtw_पढ़ो16(rtwdev, addr->rsvd) :
				     rtw_पढ़ो8(rtwdev, addr->rsvd);
		avail_page = wsize ? rtw_पढ़ो16(rtwdev, addr->avail) :
				      rtw_पढ़ो8(rtwdev, addr->avail);
		अगर (rsvd_page == avail_page)
			वापस;

		msleep(20);
	पूर्ण

	/* priority queue is still not empty, throw a warning,
	 *
	 * Note that अगर we want to flush the tx queue when having a lot of
	 * traffic (ex, 100Mbps up), some of the packets could be dropped.
	 * And it requires like ~2secs to flush the full priority queue.
	 */
	अगर (!drop)
		rtw_warn(rtwdev, "timed out to flush queue %d\n", prio_queue);
पूर्ण

अटल व्योम rtw_mac_flush_prio_queues(काष्ठा rtw_dev *rtwdev,
				      u32 prio_queues, bool drop)
अणु
	u32 q;

	क्रम (q = 0; q < RTW_DMA_MAPPING_MAX; q++)
		अगर (prio_queues & BIT(q))
			__rtw_mac_flush_prio_queue(rtwdev, q, drop);
पूर्ण

व्योम rtw_mac_flush_queues(काष्ठा rtw_dev *rtwdev, u32 queues, bool drop)
अणु
	u32 prio_queues = 0;

	/* If all of the hardware queues are requested to flush,
	 * or the priority queues are not mapped yet,
	 * flush all of the priority queues
	 */
	अगर (queues == BIT(rtwdev->hw->queues) - 1 || !rtwdev->fअगरo.rqpn)
		prio_queues = BIT(RTW_DMA_MAPPING_MAX) - 1;
	अन्यथा
		prio_queues = get_priority_queues(rtwdev, queues);

	rtw_mac_flush_prio_queues(rtwdev, prio_queues, drop);
पूर्ण

अटल पूर्णांक txdma_queue_mapping(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	स्थिर काष्ठा rtw_rqpn *rqpn = शून्य;
	u16 txdma_pq_map = 0;

	चयन (rtw_hci_type(rtwdev)) अणु
	हाल RTW_HCI_TYPE_PCIE:
		rqpn = &chip->rqpn_table[1];
		अवरोध;
	हाल RTW_HCI_TYPE_USB:
		अगर (rtwdev->hci.bulkout_num == 2)
			rqpn = &chip->rqpn_table[2];
		अन्यथा अगर (rtwdev->hci.bulkout_num == 3)
			rqpn = &chip->rqpn_table[3];
		अन्यथा अगर (rtwdev->hci.bulkout_num == 4)
			rqpn = &chip->rqpn_table[4];
		अन्यथा
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	rtwdev->fअगरo.rqpn = rqpn;
	txdma_pq_map |= BIT_TXDMA_HIQ_MAP(rqpn->dma_map_hi);
	txdma_pq_map |= BIT_TXDMA_MGQ_MAP(rqpn->dma_map_mg);
	txdma_pq_map |= BIT_TXDMA_BKQ_MAP(rqpn->dma_map_bk);
	txdma_pq_map |= BIT_TXDMA_BEQ_MAP(rqpn->dma_map_be);
	txdma_pq_map |= BIT_TXDMA_VIQ_MAP(rqpn->dma_map_vi);
	txdma_pq_map |= BIT_TXDMA_VOQ_MAP(rqpn->dma_map_vo);
	rtw_ग_लिखो16(rtwdev, REG_TXDMA_PQ_MAP, txdma_pq_map);

	rtw_ग_लिखो8(rtwdev, REG_CR, 0);
	rtw_ग_लिखो8(rtwdev, REG_CR, MAC_TRX_ENABLE);
	अगर (rtw_chip_wcpu_11ac(rtwdev))
		rtw_ग_लिखो32(rtwdev, REG_H2CQ_CSR, BIT_H2CQ_FULL);

	वापस 0;
पूर्ण

अटल पूर्णांक set_trx_fअगरo_info(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_fअगरo_conf *fअगरo = &rtwdev->fअगरo;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	u16 cur_pg_addr;
	u8 csi_buf_pg_num = chip->csi_buf_pg_num;

	/* config rsvd page num */
	fअगरo->rsvd_drv_pg_num = 8;
	fअगरo->txff_pg_num = chip->txff_size >> 7;
	अगर (rtw_chip_wcpu_11n(rtwdev))
		fअगरo->rsvd_pg_num = fअगरo->rsvd_drv_pg_num;
	अन्यथा
		fअगरo->rsvd_pg_num = fअगरo->rsvd_drv_pg_num +
				   RSVD_PG_H2C_EXTRAINFO_NUM +
				   RSVD_PG_H2C_STATICINFO_NUM +
				   RSVD_PG_H2CQ_NUM +
				   RSVD_PG_CPU_INSTRUCTION_NUM +
				   RSVD_PG_FW_TXBUF_NUM +
				   csi_buf_pg_num;

	अगर (fअगरo->rsvd_pg_num > fअगरo->txff_pg_num)
		वापस -ENOMEM;

	fअगरo->acq_pg_num = fअगरo->txff_pg_num - fअगरo->rsvd_pg_num;
	fअगरo->rsvd_boundary = fअगरo->txff_pg_num - fअगरo->rsvd_pg_num;

	cur_pg_addr = fअगरo->txff_pg_num;
	अगर (rtw_chip_wcpu_11ac(rtwdev)) अणु
		cur_pg_addr -= csi_buf_pg_num;
		fअगरo->rsvd_csibuf_addr = cur_pg_addr;
		cur_pg_addr -= RSVD_PG_FW_TXBUF_NUM;
		fअगरo->rsvd_fw_txbuf_addr = cur_pg_addr;
		cur_pg_addr -= RSVD_PG_CPU_INSTRUCTION_NUM;
		fअगरo->rsvd_cpu_instr_addr = cur_pg_addr;
		cur_pg_addr -= RSVD_PG_H2CQ_NUM;
		fअगरo->rsvd_h2cq_addr = cur_pg_addr;
		cur_pg_addr -= RSVD_PG_H2C_STATICINFO_NUM;
		fअगरo->rsvd_h2c_sta_info_addr = cur_pg_addr;
		cur_pg_addr -= RSVD_PG_H2C_EXTRAINFO_NUM;
		fअगरo->rsvd_h2c_info_addr = cur_pg_addr;
	पूर्ण
	cur_pg_addr -= fअगरo->rsvd_drv_pg_num;
	fअगरo->rsvd_drv_addr = cur_pg_addr;

	अगर (fअगरo->rsvd_boundary != fअगरo->rsvd_drv_addr) अणु
		rtw_err(rtwdev, "wrong rsvd driver address\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __priority_queue_cfg(काष्ठा rtw_dev *rtwdev,
				स्थिर काष्ठा rtw_page_table *pg_tbl,
				u16 pubq_num)
अणु
	काष्ठा rtw_fअगरo_conf *fअगरo = &rtwdev->fअगरo;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;

	rtw_ग_लिखो16(rtwdev, REG_FIFOPAGE_INFO_1, pg_tbl->hq_num);
	rtw_ग_लिखो16(rtwdev, REG_FIFOPAGE_INFO_2, pg_tbl->lq_num);
	rtw_ग_लिखो16(rtwdev, REG_FIFOPAGE_INFO_3, pg_tbl->nq_num);
	rtw_ग_लिखो16(rtwdev, REG_FIFOPAGE_INFO_4, pg_tbl->exq_num);
	rtw_ग_लिखो16(rtwdev, REG_FIFOPAGE_INFO_5, pubq_num);
	rtw_ग_लिखो32_set(rtwdev, REG_RQPN_CTRL_2, BIT_LD_RQPN);

	rtw_ग_लिखो16(rtwdev, REG_FIFOPAGE_CTRL_2, fअगरo->rsvd_boundary);
	rtw_ग_लिखो8_set(rtwdev, REG_FWHW_TXQ_CTRL + 2, BIT_EN_WR_FREE_TAIL >> 16);

	rtw_ग_लिखो16(rtwdev, REG_BCNQ_BDNY_V1, fअगरo->rsvd_boundary);
	rtw_ग_लिखो16(rtwdev, REG_FIFOPAGE_CTRL_2 + 2, fअगरo->rsvd_boundary);
	rtw_ग_लिखो16(rtwdev, REG_BCNQ1_BDNY_V1, fअगरo->rsvd_boundary);
	rtw_ग_लिखो32(rtwdev, REG_RXFF_BNDY, chip->rxff_size - C2H_PKT_BUF - 1);
	rtw_ग_लिखो8_set(rtwdev, REG_AUTO_LLT_V1, BIT_AUTO_INIT_LLT_V1);

	अगर (!check_hw_पढ़ोy(rtwdev, REG_AUTO_LLT_V1, BIT_AUTO_INIT_LLT_V1, 0))
		वापस -EBUSY;

	rtw_ग_लिखो8(rtwdev, REG_CR + 3, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक __priority_queue_cfg_legacy(काष्ठा rtw_dev *rtwdev,
				       स्थिर काष्ठा rtw_page_table *pg_tbl,
				       u16 pubq_num)
अणु
	काष्ठा rtw_fअगरo_conf *fअगरo = &rtwdev->fअगरo;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	u32 val32;

	val32 = BIT_RQPN_NE(pg_tbl->nq_num, pg_tbl->exq_num);
	rtw_ग_लिखो32(rtwdev, REG_RQPN_NPQ, val32);
	val32 = BIT_RQPN_HLP(pg_tbl->hq_num, pg_tbl->lq_num, pubq_num);
	rtw_ग_लिखो32(rtwdev, REG_RQPN, val32);

	rtw_ग_लिखो8(rtwdev, REG_TRXFF_BNDY, fअगरo->rsvd_boundary);
	rtw_ग_लिखो16(rtwdev, REG_TRXFF_BNDY + 2, chip->rxff_size - REPORT_BUF - 1);
	rtw_ग_लिखो8(rtwdev, REG_DWBCN0_CTRL + 1, fअगरo->rsvd_boundary);
	rtw_ग_लिखो8(rtwdev, REG_BCNQ_BDNY, fअगरo->rsvd_boundary);
	rtw_ग_लिखो8(rtwdev, REG_MGQ_BDNY, fअगरo->rsvd_boundary);
	rtw_ग_लिखो8(rtwdev, REG_WMAC_LBK_BF_HD, fअगरo->rsvd_boundary);

	rtw_ग_लिखो32_set(rtwdev, REG_AUTO_LLT, BIT_AUTO_INIT_LLT);

	अगर (!check_hw_पढ़ोy(rtwdev, REG_AUTO_LLT, BIT_AUTO_INIT_LLT, 0))
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल पूर्णांक priority_queue_cfg(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_fअगरo_conf *fअगरo = &rtwdev->fअगरo;
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	स्थिर काष्ठा rtw_page_table *pg_tbl = शून्य;
	u16 pubq_num;
	पूर्णांक ret;

	ret = set_trx_fअगरo_info(rtwdev);
	अगर (ret)
		वापस ret;

	चयन (rtw_hci_type(rtwdev)) अणु
	हाल RTW_HCI_TYPE_PCIE:
		pg_tbl = &chip->page_table[1];
		अवरोध;
	हाल RTW_HCI_TYPE_USB:
		अगर (rtwdev->hci.bulkout_num == 2)
			pg_tbl = &chip->page_table[2];
		अन्यथा अगर (rtwdev->hci.bulkout_num == 3)
			pg_tbl = &chip->page_table[3];
		अन्यथा अगर (rtwdev->hci.bulkout_num == 4)
			pg_tbl = &chip->page_table[4];
		अन्यथा
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	pubq_num = fअगरo->acq_pg_num - pg_tbl->hq_num - pg_tbl->lq_num -
		   pg_tbl->nq_num - pg_tbl->exq_num - pg_tbl->gapq_num;
	अगर (rtw_chip_wcpu_11n(rtwdev))
		वापस __priority_queue_cfg_legacy(rtwdev, pg_tbl, pubq_num);
	अन्यथा
		वापस __priority_queue_cfg(rtwdev, pg_tbl, pubq_num);
पूर्ण

अटल पूर्णांक init_h2c(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_fअगरo_conf *fअगरo = &rtwdev->fअगरo;
	u8 value8;
	u32 value32;
	u32 h2cq_addr;
	u32 h2cq_size;
	u32 h2cq_मुक्त;
	u32 wp, rp;

	अगर (rtw_chip_wcpu_11n(rtwdev))
		वापस 0;

	h2cq_addr = fअगरo->rsvd_h2cq_addr << TX_PAGE_SIZE_SHIFT;
	h2cq_size = RSVD_PG_H2CQ_NUM << TX_PAGE_SIZE_SHIFT;

	value32 = rtw_पढ़ो32(rtwdev, REG_H2C_HEAD);
	value32 = (value32 & 0xFFFC0000) | h2cq_addr;
	rtw_ग_लिखो32(rtwdev, REG_H2C_HEAD, value32);

	value32 = rtw_पढ़ो32(rtwdev, REG_H2C_READ_ADDR);
	value32 = (value32 & 0xFFFC0000) | h2cq_addr;
	rtw_ग_लिखो32(rtwdev, REG_H2C_READ_ADDR, value32);

	value32 = rtw_पढ़ो32(rtwdev, REG_H2C_TAIL);
	value32 &= 0xFFFC0000;
	value32 |= (h2cq_addr + h2cq_size);
	rtw_ग_लिखो32(rtwdev, REG_H2C_TAIL, value32);

	value8 = rtw_पढ़ो8(rtwdev, REG_H2C_INFO);
	value8 = (u8)((value8 & 0xFC) | 0x01);
	rtw_ग_लिखो8(rtwdev, REG_H2C_INFO, value8);

	value8 = rtw_पढ़ो8(rtwdev, REG_H2C_INFO);
	value8 = (u8)((value8 & 0xFB) | 0x04);
	rtw_ग_लिखो8(rtwdev, REG_H2C_INFO, value8);

	value8 = rtw_पढ़ो8(rtwdev, REG_TXDMA_OFFSET_CHK + 1);
	value8 = (u8)((value8 & 0x7f) | 0x80);
	rtw_ग_लिखो8(rtwdev, REG_TXDMA_OFFSET_CHK + 1, value8);

	wp = rtw_पढ़ो32(rtwdev, REG_H2C_PKT_WRITEADDR) & 0x3FFFF;
	rp = rtw_पढ़ो32(rtwdev, REG_H2C_PKT_READADDR) & 0x3FFFF;
	h2cq_मुक्त = wp >= rp ? h2cq_size - (wp - rp) : rp - wp;

	अगर (h2cq_size != h2cq_मुक्त) अणु
		rtw_err(rtwdev, "H2C queue mismatch\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_init_trx_cfg(काष्ठा rtw_dev *rtwdev)
अणु
	पूर्णांक ret;

	ret = txdma_queue_mapping(rtwdev);
	अगर (ret)
		वापस ret;

	ret = priority_queue_cfg(rtwdev);
	अगर (ret)
		वापस ret;

	ret = init_h2c(rtwdev);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक rtw_drv_info_cfg(काष्ठा rtw_dev *rtwdev)
अणु
	u8 value8;

	rtw_ग_लिखो8(rtwdev, REG_RX_DRVINFO_SZ, PHY_STATUS_SIZE);
	अगर (rtw_chip_wcpu_11ac(rtwdev)) अणु
		value8 = rtw_पढ़ो8(rtwdev, REG_TRXFF_BNDY + 1);
		value8 &= 0xF0;
		/* For rxdesc len = 0 issue */
		value8 |= 0xF;
		rtw_ग_लिखो8(rtwdev, REG_TRXFF_BNDY + 1, value8);
	पूर्ण
	rtw_ग_लिखो32_set(rtwdev, REG_RCR, BIT_APP_PHYSTS);
	rtw_ग_लिखो32_clr(rtwdev, REG_WMAC_OPTION_FUNCTION + 4, BIT(8) | BIT(9));

	वापस 0;
पूर्ण

पूर्णांक rtw_mac_init(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	पूर्णांक ret;

	ret = rtw_init_trx_cfg(rtwdev);
	अगर (ret)
		वापस ret;

	ret = chip->ops->mac_init(rtwdev);
	अगर (ret)
		वापस ret;

	ret = rtw_drv_info_cfg(rtwdev);
	अगर (ret)
		वापस ret;

	rtw_hci_पूर्णांकerface_cfg(rtwdev);

	वापस 0;
पूर्ण
