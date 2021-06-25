<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * RTL8XXXU mac80211 USB driver - 8723a specअगरic subdriver
 *
 * Copyright (c) 2014 - 2017 Jes Sorensen <Jes.Sorensen@gmail.com>
 *
 * Portions, notably calibration code:
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 * This driver was written as a replacement क्रम the venकरोr provided
 * rtl8723au driver. As the Realtek 8xxx chips are very similar in
 * their programming पूर्णांकerface, I have started adding support क्रम
 * additional 8xxx chips like the 8192cu, 8188cus, etc.
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/list.h>
#समावेश <linux/usb.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/wireless.h>
#समावेश <linux/firmware.h>
#समावेश <linux/moduleparam.h>
#समावेश <net/mac80211.h>
#समावेश "rtl8xxxu.h"
#समावेश "rtl8xxxu_regs.h"

अटल काष्ठा rtl8xxxu_घातer_base rtl8723a_घातer_base = अणु
	.reg_0e00 = 0x0a0c0c0c,
	.reg_0e04 = 0x02040608,
	.reg_0e08 = 0x00000000,
	.reg_086c = 0x00000000,

	.reg_0e10 = 0x0a0c0d0e,
	.reg_0e14 = 0x02040608,
	.reg_0e18 = 0x0a0c0d0e,
	.reg_0e1c = 0x02040608,

	.reg_0830 = 0x0a0c0c0c,
	.reg_0834 = 0x02040608,
	.reg_0838 = 0x00000000,
	.reg_086c_2 = 0x00000000,

	.reg_083c = 0x0a0c0d0e,
	.reg_0848 = 0x02040608,
	.reg_084c = 0x0a0c0d0e,
	.reg_0868 = 0x02040608,
पूर्ण;

अटल काष्ठा rtl8xxxu_rfregval rtl8723au_radioa_1t_init_table[] = अणु
	अणु0x00, 0x00030159पूर्ण, अणु0x01, 0x00031284पूर्ण,
	अणु0x02, 0x00098000पूर्ण, अणु0x03, 0x00039c63पूर्ण,
	अणु0x04, 0x000210e7पूर्ण, अणु0x09, 0x0002044fपूर्ण,
	अणु0x0a, 0x0001a3f1पूर्ण, अणु0x0b, 0x00014787पूर्ण,
	अणु0x0c, 0x000896feपूर्ण, अणु0x0d, 0x0000e02cपूर्ण,
	अणु0x0e, 0x00039ce7पूर्ण, अणु0x0f, 0x00000451पूर्ण,
	अणु0x19, 0x00000000पूर्ण, अणु0x1a, 0x00030355पूर्ण,
	अणु0x1b, 0x00060a00पूर्ण, अणु0x1c, 0x000fc378पूर्ण,
	अणु0x1d, 0x000a1250पूर्ण, अणु0x1e, 0x0000024fपूर्ण,
	अणु0x1f, 0x00000000पूर्ण, अणु0x20, 0x0000b614पूर्ण,
	अणु0x21, 0x0006c000पूर्ण, अणु0x22, 0x00000000पूर्ण,
	अणु0x23, 0x00001558पूर्ण, अणु0x24, 0x00000060पूर्ण,
	अणु0x25, 0x00000483पूर्ण, अणु0x26, 0x0004f000पूर्ण,
	अणु0x27, 0x000ec7d9पूर्ण, अणु0x28, 0x00057730पूर्ण,
	अणु0x29, 0x00004783पूर्ण, अणु0x2a, 0x00000001पूर्ण,
	अणु0x2b, 0x00021334पूर्ण, अणु0x2a, 0x00000000पूर्ण,
	अणु0x2b, 0x00000054पूर्ण, अणु0x2a, 0x00000001पूर्ण,
	अणु0x2b, 0x00000808पूर्ण, अणु0x2b, 0x00053333पूर्ण,
	अणु0x2c, 0x0000000cपूर्ण, अणु0x2a, 0x00000002पूर्ण,
	अणु0x2b, 0x00000808पूर्ण, अणु0x2b, 0x0005b333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x00000003पूर्ण,
	अणु0x2b, 0x00000808पूर्ण, अणु0x2b, 0x00063333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x00000004पूर्ण,
	अणु0x2b, 0x00000808पूर्ण, अणु0x2b, 0x0006b333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x00000005पूर्ण,
	अणु0x2b, 0x00000808पूर्ण, अणु0x2b, 0x00073333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x00000006पूर्ण,
	अणु0x2b, 0x00000709पूर्ण, अणु0x2b, 0x0005b333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x00000007पूर्ण,
	अणु0x2b, 0x00000709पूर्ण, अणु0x2b, 0x00063333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x00000008पूर्ण,
	अणु0x2b, 0x0000060aपूर्ण, अणु0x2b, 0x0004b333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x00000009पूर्ण,
	अणु0x2b, 0x0000060aपूर्ण, अणु0x2b, 0x00053333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x0000000aपूर्ण,
	अणु0x2b, 0x0000060aपूर्ण, अणु0x2b, 0x0005b333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x0000000bपूर्ण,
	अणु0x2b, 0x0000060aपूर्ण, अणु0x2b, 0x00063333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x0000000cपूर्ण,
	अणु0x2b, 0x0000060aपूर्ण, अणु0x2b, 0x0006b333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x0000000dपूर्ण,
	अणु0x2b, 0x0000060aपूर्ण, अणु0x2b, 0x00073333पूर्ण,
	अणु0x2c, 0x0000000dपूर्ण, अणु0x2a, 0x0000000eपूर्ण,
	अणु0x2b, 0x0000050bपूर्ण, अणु0x2b, 0x00066666पूर्ण,
	अणु0x2c, 0x0000001aपूर्ण, अणु0x2a, 0x000e0000पूर्ण,
	अणु0x10, 0x0004000fपूर्ण, अणु0x11, 0x000e31fcपूर्ण,
	अणु0x10, 0x0006000fपूर्ण, अणु0x11, 0x000ff9f8पूर्ण,
	अणु0x10, 0x0002000fपूर्ण, अणु0x11, 0x000203f9पूर्ण,
	अणु0x10, 0x0003000fपूर्ण, अणु0x11, 0x000ff500पूर्ण,
	अणु0x10, 0x00000000पूर्ण, अणु0x11, 0x00000000पूर्ण,
	अणु0x10, 0x0008000fपूर्ण, अणु0x11, 0x0003f100पूर्ण,
	अणु0x10, 0x0009000fपूर्ण, अणु0x11, 0x00023100पूर्ण,
	अणु0x12, 0x00032000पूर्ण, अणु0x12, 0x00071000पूर्ण,
	अणु0x12, 0x000b0000पूर्ण, अणु0x12, 0x000fc000पूर्ण,
	अणु0x13, 0x000287b3पूर्ण, अणु0x13, 0x000244b7पूर्ण,
	अणु0x13, 0x000204abपूर्ण, अणु0x13, 0x0001c49fपूर्ण,
	अणु0x13, 0x00018493पूर्ण, अणु0x13, 0x0001429bपूर्ण,
	अणु0x13, 0x00010299पूर्ण, अणु0x13, 0x0000c29cपूर्ण,
	अणु0x13, 0x000081a0पूर्ण, अणु0x13, 0x000040acपूर्ण,
	अणु0x13, 0x00000020पूर्ण, अणु0x14, 0x0001944cपूर्ण,
	अणु0x14, 0x00059444पूर्ण, अणु0x14, 0x0009944cपूर्ण,
	अणु0x14, 0x000d9444पूर्ण, अणु0x15, 0x0000f474पूर्ण,
	अणु0x15, 0x0004f477पूर्ण, अणु0x15, 0x0008f455पूर्ण,
	अणु0x15, 0x000cf455पूर्ण, अणु0x16, 0x00000339पूर्ण,
	अणु0x16, 0x00040339पूर्ण, अणु0x16, 0x00080339पूर्ण,
	अणु0x16, 0x000c0366पूर्ण, अणु0x00, 0x00010159पूर्ण,
	अणु0x18, 0x0000f401पूर्ण, अणु0xfe, 0x00000000पूर्ण,
	अणु0xfe, 0x00000000पूर्ण, अणु0x1f, 0x00000003पूर्ण,
	अणु0xfe, 0x00000000पूर्ण, अणु0xfe, 0x00000000पूर्ण,
	अणु0x1e, 0x00000247पूर्ण, अणु0x1f, 0x00000000पूर्ण,
	अणु0x00, 0x00030159पूर्ण,
	अणु0xff, 0xffffffffपूर्ण
पूर्ण;

अटल पूर्णांक rtl8723au_parse_efuse(काष्ठा rtl8xxxu_priv *priv)
अणु
	काष्ठा rtl8723au_efuse *efuse = &priv->efuse_wअगरi.efuse8723;

	अगर (efuse->rtl_id != cpu_to_le16(0x8129))
		वापस -EINVAL;

	ether_addr_copy(priv->mac_addr, efuse->mac_addr);

	स_नकल(priv->cck_tx_घातer_index_A,
	       efuse->cck_tx_घातer_index_A,
	       माप(efuse->cck_tx_घातer_index_A));
	स_नकल(priv->cck_tx_घातer_index_B,
	       efuse->cck_tx_घातer_index_B,
	       माप(efuse->cck_tx_घातer_index_B));

	स_नकल(priv->ht40_1s_tx_घातer_index_A,
	       efuse->ht40_1s_tx_घातer_index_A,
	       माप(efuse->ht40_1s_tx_घातer_index_A));
	स_नकल(priv->ht40_1s_tx_घातer_index_B,
	       efuse->ht40_1s_tx_घातer_index_B,
	       माप(efuse->ht40_1s_tx_घातer_index_B));

	स_नकल(priv->ht20_tx_घातer_index_dअगरf,
	       efuse->ht20_tx_घातer_index_dअगरf,
	       माप(efuse->ht20_tx_घातer_index_dअगरf));
	स_नकल(priv->ofdm_tx_घातer_index_dअगरf,
	       efuse->ofdm_tx_घातer_index_dअगरf,
	       माप(efuse->ofdm_tx_घातer_index_dअगरf));

	स_नकल(priv->ht40_max_घातer_offset,
	       efuse->ht40_max_घातer_offset,
	       माप(efuse->ht40_max_घातer_offset));
	स_नकल(priv->ht20_max_घातer_offset,
	       efuse->ht20_max_घातer_offset,
	       माप(efuse->ht20_max_घातer_offset));

	अगर (priv->efuse_wअगरi.efuse8723.version >= 0x01) अणु
		priv->has_xtalk = 1;
		priv->xtalk = priv->efuse_wअगरi.efuse8723.xtal_k & 0x3f;
	पूर्ण

	priv->घातer_base = &rtl8723a_घातer_base;

	dev_info(&priv->udev->dev, "Vendor: %.7s\n",
		 efuse->venकरोr_name);
	dev_info(&priv->udev->dev, "Product: %.41s\n",
		 efuse->device_name);
	वापस 0;
पूर्ण

अटल पूर्णांक rtl8723au_load_firmware(काष्ठा rtl8xxxu_priv *priv)
अणु
	अक्षर *fw_name;
	पूर्णांक ret;

	चयन (priv->chip_cut) अणु
	हाल 0:
		fw_name = "rtlwifi/rtl8723aufw_A.bin";
		अवरोध;
	हाल 1:
		अगर (priv->enable_bluetooth)
			fw_name = "rtlwifi/rtl8723aufw_B.bin";
		अन्यथा
			fw_name = "rtlwifi/rtl8723aufw_B_NoBT.bin";

		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = rtl8xxxu_load_firmware(priv, fw_name);
	वापस ret;
पूर्ण

अटल पूर्णांक rtl8723au_init_phy_rf(काष्ठा rtl8xxxu_priv *priv)
अणु
	पूर्णांक ret;

	ret = rtl8xxxu_init_phy_rf(priv, rtl8723au_radioa_1t_init_table, RF_A);

	/* Reduce 80M spur */
	rtl8xxxu_ग_लिखो32(priv, REG_AFE_XTAL_CTRL, 0x0381808d);
	rtl8xxxu_ग_लिखो32(priv, REG_AFE_PLL_CTRL, 0xf0ffff83);
	rtl8xxxu_ग_लिखो32(priv, REG_AFE_PLL_CTRL, 0xf0ffff82);
	rtl8xxxu_ग_लिखो32(priv, REG_AFE_PLL_CTRL, 0xf0ffff83);

	वापस ret;
पूर्ण

अटल पूर्णांक rtl8723a_emu_to_active(काष्ठा rtl8xxxu_priv *priv)
अणु
	u8 val8;
	u32 val32;
	पूर्णांक count, ret = 0;

	/* 0x20[0] = 1 enable LDOA12 MACRO block क्रम all पूर्णांकerface*/
	val8 = rtl8xxxu_पढ़ो8(priv, REG_LDOA15_CTRL);
	val8 |= LDOA15_ENABLE;
	rtl8xxxu_ग_लिखो8(priv, REG_LDOA15_CTRL, val8);

	/* 0x67[0] = 0 to disable BT_GPS_SEL pins*/
	val8 = rtl8xxxu_पढ़ो8(priv, 0x0067);
	val8 &= ~BIT(4);
	rtl8xxxu_ग_लिखो8(priv, 0x0067, val8);

	mdelay(1);

	/* 0x00[5] = 0 release analog Ips to digital, 1:isolation */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_SYS_ISO_CTRL);
	val8 &= ~SYS_ISO_ANALOG_IPS;
	rtl8xxxu_ग_लिखो8(priv, REG_SYS_ISO_CTRL, val8);

	/* disable SW LPS 0x04[10]= 0 */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_APS_FSMCO + 1);
	val8 &= ~BIT(2);
	rtl8xxxu_ग_लिखो8(priv, REG_APS_FSMCO + 1, val8);

	/* रुको till 0x04[17] = 1 घातer पढ़ोy*/
	क्रम (count = RTL8XXXU_MAX_REG_POLL; count; count--) अणु
		val32 = rtl8xxxu_पढ़ो32(priv, REG_APS_FSMCO);
		अगर (val32 & BIT(17))
			अवरोध;

		udelay(10);
	पूर्ण

	अगर (!count) अणु
		ret = -EBUSY;
		जाओ निकास;
	पूर्ण

	/* We should be able to optimize the following three entries पूर्णांकo one */

	/* release WLON reset 0x04[16]= 1*/
	val8 = rtl8xxxu_पढ़ो8(priv, REG_APS_FSMCO + 2);
	val8 |= BIT(0);
	rtl8xxxu_ग_लिखो8(priv, REG_APS_FSMCO + 2, val8);

	/* disable HWPDN 0x04[15]= 0*/
	val8 = rtl8xxxu_पढ़ो8(priv, REG_APS_FSMCO + 1);
	val8 &= ~BIT(7);
	rtl8xxxu_ग_लिखो8(priv, REG_APS_FSMCO + 1, val8);

	/* disable WL suspend*/
	val8 = rtl8xxxu_पढ़ो8(priv, REG_APS_FSMCO + 1);
	val8 &= ~(BIT(3) | BIT(4));
	rtl8xxxu_ग_लिखो8(priv, REG_APS_FSMCO + 1, val8);

	/* set, then poll until 0 */
	val32 = rtl8xxxu_पढ़ो32(priv, REG_APS_FSMCO);
	val32 |= APS_FSMCO_MAC_ENABLE;
	rtl8xxxu_ग_लिखो32(priv, REG_APS_FSMCO, val32);

	क्रम (count = RTL8XXXU_MAX_REG_POLL; count; count--) अणु
		val32 = rtl8xxxu_पढ़ो32(priv, REG_APS_FSMCO);
		अगर ((val32 & APS_FSMCO_MAC_ENABLE) == 0) अणु
			ret = 0;
			अवरोध;
		पूर्ण
		udelay(10);
	पूर्ण

	अगर (!count) अणु
		ret = -EBUSY;
		जाओ निकास;
	पूर्ण

	/* 0x4C[23] = 0x4E[7] = 1, चयन DPDT_SEL_P output from WL BB */
	/*
	 * Note: Venकरोr driver actually clears this bit, despite the
	 * करोcumentation claims it's being set!
	 */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_LEDCFG2);
	val8 |= LEDCFG2_DPDT_SELECT;
	val8 &= ~LEDCFG2_DPDT_SELECT;
	rtl8xxxu_ग_लिखो8(priv, REG_LEDCFG2, val8);

निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक rtl8723au_घातer_on(काष्ठा rtl8xxxu_priv *priv)
अणु
	u8 val8;
	u16 val16;
	u32 val32;
	पूर्णांक ret;

	/*
	 * RSV_CTRL 0x001C[7:0] = 0x00, unlock ISO/CLK/Power control रेजिस्टर
	 */
	rtl8xxxu_ग_लिखो8(priv, REG_RSV_CTRL, 0x0);

	rtl8xxxu_disabled_to_emu(priv);

	ret = rtl8723a_emu_to_active(priv);
	अगर (ret)
		जाओ निकास;

	/*
	 * 0x0004[19] = 1, reset 8051
	 */
	val8 = rtl8xxxu_पढ़ो8(priv, REG_APS_FSMCO + 2);
	val8 |= BIT(3);
	rtl8xxxu_ग_लिखो8(priv, REG_APS_FSMCO + 2, val8);

	/*
	 * Enable MAC DMA/WMAC/SCHEDULE/SEC block
	 * Set CR bit10 to enable 32k calibration.
	 */
	val16 = rtl8xxxu_पढ़ो16(priv, REG_CR);
	val16 |= (CR_HCI_TXDMA_ENABLE | CR_HCI_RXDMA_ENABLE |
		  CR_TXDMA_ENABLE | CR_RXDMA_ENABLE |
		  CR_PROTOCOL_ENABLE | CR_SCHEDULE_ENABLE |
		  CR_MAC_TX_ENABLE | CR_MAC_RX_ENABLE |
		  CR_SECURITY_ENABLE | CR_CALTIMER_ENABLE);
	rtl8xxxu_ग_लिखो16(priv, REG_CR, val16);

	/* For EFuse PG */
	val32 = rtl8xxxu_पढ़ो32(priv, REG_EFUSE_CTRL);
	val32 &= ~(BIT(28) | BIT(29) | BIT(30));
	val32 |= (0x06 << 28);
	rtl8xxxu_ग_लिखो32(priv, REG_EFUSE_CTRL, val32);
निकास:
	वापस ret;
पूर्ण

काष्ठा rtl8xxxu_fileops rtl8723au_fops = अणु
	.parse_efuse = rtl8723au_parse_efuse,
	.load_firmware = rtl8723au_load_firmware,
	.घातer_on = rtl8723au_घातer_on,
	.घातer_off = rtl8xxxu_घातer_off,
	.reset_8051 = rtl8xxxu_reset_8051,
	.llt_init = rtl8xxxu_init_llt_table,
	.init_phy_bb = rtl8xxxu_gen1_init_phy_bb,
	.init_phy_rf = rtl8723au_init_phy_rf,
	.phy_iq_calibrate = rtl8xxxu_gen1_phy_iq_calibrate,
	.config_channel = rtl8xxxu_gen1_config_channel,
	.parse_rx_desc = rtl8xxxu_parse_rxdesc16,
	.init_aggregation = rtl8xxxu_gen1_init_aggregation,
	.enable_rf = rtl8xxxu_gen1_enable_rf,
	.disable_rf = rtl8xxxu_gen1_disable_rf,
	.usb_quirks = rtl8xxxu_gen1_usb_quirks,
	.set_tx_घातer = rtl8xxxu_gen1_set_tx_घातer,
	.update_rate_mask = rtl8xxxu_update_rate_mask,
	.report_connect = rtl8xxxu_gen1_report_connect,
	.fill_txdesc = rtl8xxxu_fill_txdesc_v1,
	.ग_लिखोN_block_size = 1024,
	.rx_agg_buf_size = 16000,
	.tx_desc_size = माप(काष्ठा rtl8xxxu_txdesc32),
	.rx_desc_size = माप(काष्ठा rtl8xxxu_rxdesc16),
	.adda_1t_init = 0x0b1b25a0,
	.adda_1t_path_on = 0x0bdb25a0,
	.adda_2t_path_on_a = 0x04db25a4,
	.adda_2t_path_on_b = 0x0b1b25a4,
	.trxff_boundary = 0x27ff,
	.pbp_rx = PBP_PAGE_SIZE_128,
	.pbp_tx = PBP_PAGE_SIZE_128,
	.mactable = rtl8xxxu_gen1_mac_init_table,
	.total_page_num = TX_TOTAL_PAGE_NUM,
	.page_num_hi = TX_PAGE_NUM_HI_PQ,
	.page_num_lo = TX_PAGE_NUM_LO_PQ,
	.page_num_norm = TX_PAGE_NUM_NORM_PQ,
पूर्ण;
