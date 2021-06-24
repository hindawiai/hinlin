<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 MediaTek Inc.
 * Authors:
 *	Stanley Chu <stanley.chu@mediatek.com>
 *	Peter Wang <peter.wang@mediatek.com>
 */

#समावेश <linux/arm-smccc.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>
#समावेश <linux/soc/mediatek/mtk_sip_svc.h>

#समावेश "ufshcd.h"
#समावेश "ufshcd-crypto.h"
#समावेश "ufshcd-pltfrm.h"
#समावेश "ufs_quirks.h"
#समावेश "unipro.h"
#समावेश "ufs-mediatek.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश "ufs-mediatek-trace.h"

#घोषणा ufs_mtk_smc(cmd, val, res) \
	arm_smccc_smc(MTK_SIP_UFS_CONTROL, \
		      cmd, val, 0, 0, 0, 0, 0, &(res))

#घोषणा ufs_mtk_va09_pwr_ctrl(res, on) \
	ufs_mtk_smc(UFS_MTK_SIP_VA09_PWR_CTRL, on, res)

#घोषणा ufs_mtk_crypto_ctrl(res, enable) \
	ufs_mtk_smc(UFS_MTK_SIP_CRYPTO_CTRL, enable, res)

#घोषणा ufs_mtk_ref_clk_notअगरy(on, res) \
	ufs_mtk_smc(UFS_MTK_SIP_REF_CLK_NOTIFICATION, on, res)

#घोषणा ufs_mtk_device_reset_ctrl(high, res) \
	ufs_mtk_smc(UFS_MTK_SIP_DEVICE_RESET, high, res)

अटल काष्ठा ufs_dev_fix ufs_mtk_dev_fixups[] = अणु
	UFS_FIX(UFS_VENDOR_MICRON, UFS_ANY_MODEL,
		UFS_DEVICE_QUIRK_DELAY_AFTER_LPM),
	UFS_FIX(UFS_VENDOR_SKHYNIX, "H9HQ21AFAMZDAR",
		UFS_DEVICE_QUIRK_SUPPORT_EXTENDED_FEATURES),
	END_FIX
पूर्ण;

अटल स्थिर काष्ठा of_device_id ufs_mtk_of_match[] = अणु
	अणु .compatible = "mediatek,mt8183-ufshci" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल bool ufs_mtk_is_boost_crypt_enabled(काष्ठा ufs_hba *hba)
अणु
	काष्ठा ufs_mtk_host *host = ufshcd_get_variant(hba);

	वापस !!(host->caps & UFS_MTK_CAP_BOOST_CRYPT_ENGINE);
पूर्ण

अटल bool ufs_mtk_is_va09_supported(काष्ठा ufs_hba *hba)
अणु
	काष्ठा ufs_mtk_host *host = ufshcd_get_variant(hba);

	वापस !!(host->caps & UFS_MTK_CAP_VA09_PWR_CTRL);
पूर्ण

अटल bool ufs_mtk_is_broken_vcc(काष्ठा ufs_hba *hba)
अणु
	काष्ठा ufs_mtk_host *host = ufshcd_get_variant(hba);

	वापस !!(host->caps & UFS_MTK_CAP_BROKEN_VCC);
पूर्ण

अटल व्योम ufs_mtk_cfg_unipro_cg(काष्ठा ufs_hba *hba, bool enable)
अणु
	u32 पंचांगp;

	अगर (enable) अणु
		ufshcd_dme_get(hba,
			       UIC_ARG_MIB(VS_SAVEPOWERCONTROL), &पंचांगp);
		पंचांगp = पंचांगp |
		      (1 << RX_SYMBOL_CLK_GATE_EN) |
		      (1 << SYS_CLK_GATE_EN) |
		      (1 << TX_CLK_GATE_EN);
		ufshcd_dme_set(hba,
			       UIC_ARG_MIB(VS_SAVEPOWERCONTROL), पंचांगp);

		ufshcd_dme_get(hba,
			       UIC_ARG_MIB(VS_DEBUGCLOCKENABLE), &पंचांगp);
		पंचांगp = पंचांगp & ~(1 << TX_SYMBOL_CLK_REQ_FORCE);
		ufshcd_dme_set(hba,
			       UIC_ARG_MIB(VS_DEBUGCLOCKENABLE), पंचांगp);
	पूर्ण अन्यथा अणु
		ufshcd_dme_get(hba,
			       UIC_ARG_MIB(VS_SAVEPOWERCONTROL), &पंचांगp);
		पंचांगp = पंचांगp & ~((1 << RX_SYMBOL_CLK_GATE_EN) |
			      (1 << SYS_CLK_GATE_EN) |
			      (1 << TX_CLK_GATE_EN));
		ufshcd_dme_set(hba,
			       UIC_ARG_MIB(VS_SAVEPOWERCONTROL), पंचांगp);

		ufshcd_dme_get(hba,
			       UIC_ARG_MIB(VS_DEBUGCLOCKENABLE), &पंचांगp);
		पंचांगp = पंचांगp | (1 << TX_SYMBOL_CLK_REQ_FORCE);
		ufshcd_dme_set(hba,
			       UIC_ARG_MIB(VS_DEBUGCLOCKENABLE), पंचांगp);
	पूर्ण
पूर्ण

अटल व्योम ufs_mtk_crypto_enable(काष्ठा ufs_hba *hba)
अणु
	काष्ठा arm_smccc_res res;

	ufs_mtk_crypto_ctrl(res, 1);
	अगर (res.a0) अणु
		dev_info(hba->dev, "%s: crypto enable failed, err: %lu\n",
			 __func__, res.a0);
		hba->caps &= ~UFSHCD_CAP_CRYPTO;
	पूर्ण
पूर्ण

अटल व्योम ufs_mtk_host_reset(काष्ठा ufs_hba *hba)
अणु
	काष्ठा ufs_mtk_host *host = ufshcd_get_variant(hba);

	reset_control_निश्चित(host->hci_reset);
	reset_control_निश्चित(host->crypto_reset);
	reset_control_निश्चित(host->unipro_reset);

	usleep_range(100, 110);

	reset_control_deनिश्चित(host->unipro_reset);
	reset_control_deनिश्चित(host->crypto_reset);
	reset_control_deनिश्चित(host->hci_reset);
पूर्ण

अटल व्योम ufs_mtk_init_reset_control(काष्ठा ufs_hba *hba,
				       काष्ठा reset_control **rc,
				       अक्षर *str)
अणु
	*rc = devm_reset_control_get(hba->dev, str);
	अगर (IS_ERR(*rc)) अणु
		dev_info(hba->dev, "Failed to get reset control %s: %ld\n",
			 str, PTR_ERR(*rc));
		*rc = शून्य;
	पूर्ण
पूर्ण

अटल व्योम ufs_mtk_init_reset(काष्ठा ufs_hba *hba)
अणु
	काष्ठा ufs_mtk_host *host = ufshcd_get_variant(hba);

	ufs_mtk_init_reset_control(hba, &host->hci_reset,
				   "hci_rst");
	ufs_mtk_init_reset_control(hba, &host->unipro_reset,
				   "unipro_rst");
	ufs_mtk_init_reset_control(hba, &host->crypto_reset,
				   "crypto_rst");
पूर्ण

अटल पूर्णांक ufs_mtk_hce_enable_notअगरy(काष्ठा ufs_hba *hba,
				     क्रमागत ufs_notअगरy_change_status status)
अणु
	काष्ठा ufs_mtk_host *host = ufshcd_get_variant(hba);
	अचिन्हित दीर्घ flags;

	अगर (status == PRE_CHANGE) अणु
		अगर (host->unipro_lpm) अणु
			hba->vps->hba_enable_delay_us = 0;
		पूर्ण अन्यथा अणु
			hba->vps->hba_enable_delay_us = 600;
			ufs_mtk_host_reset(hba);
		पूर्ण

		अगर (hba->caps & UFSHCD_CAP_CRYPTO)
			ufs_mtk_crypto_enable(hba);

		अगर (host->caps & UFS_MTK_CAP_DISABLE_AH8) अणु
			spin_lock_irqsave(hba->host->host_lock, flags);
			ufshcd_ग_लिखोl(hba, 0,
				      REG_AUTO_HIBERNATE_IDLE_TIMER);
			spin_unlock_irqrestore(hba->host->host_lock,
					       flags);

			hba->capabilities &= ~MASK_AUTO_HIBERN8_SUPPORT;
			hba->ahit = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ufs_mtk_bind_mphy(काष्ठा ufs_hba *hba)
अणु
	काष्ठा ufs_mtk_host *host = ufshcd_get_variant(hba);
	काष्ठा device *dev = hba->dev;
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक err = 0;

	host->mphy = devm_of_phy_get_by_index(dev, np, 0);

	अगर (host->mphy == ERR_PTR(-EPROBE_DEFER)) अणु
		/*
		 * UFS driver might be probed beक्रमe the phy driver करोes.
		 * In that हाल we would like to वापस EPROBE_DEFER code.
		 */
		err = -EPROBE_DEFER;
		dev_info(dev,
			 "%s: required phy hasn't probed yet. err = %d\n",
			__func__, err);
	पूर्ण अन्यथा अगर (IS_ERR(host->mphy)) अणु
		err = PTR_ERR(host->mphy);
		अगर (err != -ENODEV) अणु
			dev_info(dev, "%s: PHY get failed %d\n", __func__,
				 err);
		पूर्ण
	पूर्ण

	अगर (err)
		host->mphy = शून्य;
	/*
	 * Allow unbound mphy because not every platक्रमm needs specअगरic
	 * mphy control.
	 */
	अगर (err == -ENODEV)
		err = 0;

	वापस err;
पूर्ण

अटल पूर्णांक ufs_mtk_setup_ref_clk(काष्ठा ufs_hba *hba, bool on)
अणु
	काष्ठा ufs_mtk_host *host = ufshcd_get_variant(hba);
	काष्ठा arm_smccc_res res;
	kसमय_प्रकार समयout, समय_checked;
	u32 value;

	अगर (host->ref_clk_enabled == on)
		वापस 0;

	अगर (on) अणु
		ufs_mtk_ref_clk_notअगरy(on, res);
		ufshcd_delay_us(host->ref_clk_ungating_रुको_us, 10);
		ufshcd_ग_लिखोl(hba, REFCLK_REQUEST, REG_UFS_REFCLK_CTRL);
	पूर्ण अन्यथा अणु
		ufshcd_ग_लिखोl(hba, REFCLK_RELEASE, REG_UFS_REFCLK_CTRL);
	पूर्ण

	/* Wait क्रम ack */
	समयout = kसमय_add_us(kसमय_get(), REFCLK_REQ_TIMEOUT_US);
	करो अणु
		समय_checked = kसमय_get();
		value = ufshcd_पढ़ोl(hba, REG_UFS_REFCLK_CTRL);

		/* Wait until ack bit equals to req bit */
		अगर (((value & REFCLK_ACK) >> 1) == (value & REFCLK_REQUEST))
			जाओ out;

		usleep_range(100, 200);
	पूर्ण जबतक (kसमय_beक्रमe(समय_checked, समयout));

	dev_err(hba->dev, "missing ack of refclk req, reg: 0x%x\n", value);

	ufs_mtk_ref_clk_notअगरy(host->ref_clk_enabled, res);

	वापस -ETIMEDOUT;

out:
	host->ref_clk_enabled = on;
	अगर (!on) अणु
		ufshcd_delay_us(host->ref_clk_gating_रुको_us, 10);
		ufs_mtk_ref_clk_notअगरy(on, res);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ufs_mtk_setup_ref_clk_रुको_us(काष्ठा ufs_hba *hba,
					  u16 gating_us, u16 ungating_us)
अणु
	काष्ठा ufs_mtk_host *host = ufshcd_get_variant(hba);

	अगर (hba->dev_info.clk_gating_रुको_us) अणु
		host->ref_clk_gating_रुको_us =
			hba->dev_info.clk_gating_रुको_us;
	पूर्ण अन्यथा अणु
		host->ref_clk_gating_रुको_us = gating_us;
	पूर्ण

	host->ref_clk_ungating_रुको_us = ungating_us;
पूर्ण

अटल पूर्णांक ufs_mtk_रुको_link_state(काष्ठा ufs_hba *hba, u32 state,
				   अचिन्हित दीर्घ max_रुको_ms)
अणु
	kसमय_प्रकार समयout, समय_checked;
	u32 val;

	समयout = kसमय_add_ms(kसमय_get(), max_रुको_ms);
	करो अणु
		समय_checked = kसमय_get();
		ufshcd_ग_लिखोl(hba, 0x20, REG_UFS_DEBUG_SEL);
		val = ufshcd_पढ़ोl(hba, REG_UFS_PROBE);
		val = val >> 28;

		अगर (val == state)
			वापस 0;

		/* Sleep क्रम max. 200us */
		usleep_range(100, 200);
	पूर्ण जबतक (kसमय_beक्रमe(समय_checked, समयout));

	अगर (val == state)
		वापस 0;

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक ufs_mtk_mphy_घातer_on(काष्ठा ufs_hba *hba, bool on)
अणु
	काष्ठा ufs_mtk_host *host = ufshcd_get_variant(hba);
	काष्ठा phy *mphy = host->mphy;
	काष्ठा arm_smccc_res res;
	पूर्णांक ret = 0;

	अगर (!mphy || !(on ^ host->mphy_घातered_on))
		वापस 0;

	अगर (on) अणु
		अगर (ufs_mtk_is_va09_supported(hba)) अणु
			ret = regulator_enable(host->reg_va09);
			अगर (ret < 0)
				जाओ out;
			/* रुको 200 us to stablize VA09 */
			usleep_range(200, 210);
			ufs_mtk_va09_pwr_ctrl(res, 1);
		पूर्ण
		phy_घातer_on(mphy);
	पूर्ण अन्यथा अणु
		phy_घातer_off(mphy);
		अगर (ufs_mtk_is_va09_supported(hba)) अणु
			ufs_mtk_va09_pwr_ctrl(res, 0);
			ret = regulator_disable(host->reg_va09);
			अगर (ret < 0)
				जाओ out;
		पूर्ण
	पूर्ण
out:
	अगर (ret) अणु
		dev_info(hba->dev,
			 "failed to %s va09: %d\n",
			 on ? "enable" : "disable",
			 ret);
	पूर्ण अन्यथा अणु
		host->mphy_घातered_on = on;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ufs_mtk_get_host_clk(काष्ठा device *dev, स्थिर अक्षर *name,
				काष्ठा clk **clk_out)
अणु
	काष्ठा clk *clk;
	पूर्णांक err = 0;

	clk = devm_clk_get(dev, name);
	अगर (IS_ERR(clk))
		err = PTR_ERR(clk);
	अन्यथा
		*clk_out = clk;

	वापस err;
पूर्ण

अटल व्योम ufs_mtk_boost_crypt(काष्ठा ufs_hba *hba, bool boost)
अणु
	काष्ठा ufs_mtk_host *host = ufshcd_get_variant(hba);
	काष्ठा ufs_mtk_crypt_cfg *cfg;
	काष्ठा regulator *reg;
	पूर्णांक volt, ret;

	अगर (!ufs_mtk_is_boost_crypt_enabled(hba))
		वापस;

	cfg = host->crypt;
	volt = cfg->vcore_volt;
	reg = cfg->reg_vcore;

	ret = clk_prepare_enable(cfg->clk_crypt_mux);
	अगर (ret) अणु
		dev_info(hba->dev, "clk_prepare_enable(): %d\n",
			 ret);
		वापस;
	पूर्ण

	अगर (boost) अणु
		ret = regulator_set_voltage(reg, volt, पूर्णांक_उच्च);
		अगर (ret) अणु
			dev_info(hba->dev,
				 "failed to set vcore to %d\n", volt);
			जाओ out;
		पूर्ण

		ret = clk_set_parent(cfg->clk_crypt_mux,
				     cfg->clk_crypt_perf);
		अगर (ret) अणु
			dev_info(hba->dev,
				 "failed to set clk_crypt_perf\n");
			regulator_set_voltage(reg, 0, पूर्णांक_उच्च);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = clk_set_parent(cfg->clk_crypt_mux,
				     cfg->clk_crypt_lp);
		अगर (ret) अणु
			dev_info(hba->dev,
				 "failed to set clk_crypt_lp\n");
			जाओ out;
		पूर्ण

		ret = regulator_set_voltage(reg, 0, पूर्णांक_उच्च);
		अगर (ret) अणु
			dev_info(hba->dev,
				 "failed to set vcore to MIN\n");
		पूर्ण
	पूर्ण
out:
	clk_disable_unprepare(cfg->clk_crypt_mux);
पूर्ण

अटल पूर्णांक ufs_mtk_init_host_clk(काष्ठा ufs_hba *hba, स्थिर अक्षर *name,
				 काष्ठा clk **clk)
अणु
	पूर्णांक ret;

	ret = ufs_mtk_get_host_clk(hba->dev, name, clk);
	अगर (ret) अणु
		dev_info(hba->dev, "%s: failed to get %s: %d", __func__,
			 name, ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम ufs_mtk_init_boost_crypt(काष्ठा ufs_hba *hba)
अणु
	काष्ठा ufs_mtk_host *host = ufshcd_get_variant(hba);
	काष्ठा ufs_mtk_crypt_cfg *cfg;
	काष्ठा device *dev = hba->dev;
	काष्ठा regulator *reg;
	u32 volt;

	host->crypt = devm_kzalloc(dev, माप(*(host->crypt)),
				   GFP_KERNEL);
	अगर (!host->crypt)
		जाओ disable_caps;

	reg = devm_regulator_get_optional(dev, "dvfsrc-vcore");
	अगर (IS_ERR(reg)) अणु
		dev_info(dev, "failed to get dvfsrc-vcore: %ld",
			 PTR_ERR(reg));
		जाओ disable_caps;
	पूर्ण

	अगर (of_property_पढ़ो_u32(dev->of_node, "boost-crypt-vcore-min",
				 &volt)) अणु
		dev_info(dev, "failed to get boost-crypt-vcore-min");
		जाओ disable_caps;
	पूर्ण

	cfg = host->crypt;
	अगर (ufs_mtk_init_host_clk(hba, "crypt_mux",
				  &cfg->clk_crypt_mux))
		जाओ disable_caps;

	अगर (ufs_mtk_init_host_clk(hba, "crypt_lp",
				  &cfg->clk_crypt_lp))
		जाओ disable_caps;

	अगर (ufs_mtk_init_host_clk(hba, "crypt_perf",
				  &cfg->clk_crypt_perf))
		जाओ disable_caps;

	cfg->reg_vcore = reg;
	cfg->vcore_volt = volt;
	host->caps |= UFS_MTK_CAP_BOOST_CRYPT_ENGINE;

disable_caps:
	वापस;
पूर्ण

अटल व्योम ufs_mtk_init_va09_pwr_ctrl(काष्ठा ufs_hba *hba)
अणु
	काष्ठा ufs_mtk_host *host = ufshcd_get_variant(hba);

	host->reg_va09 = regulator_get(hba->dev, "va09");
	अगर (!host->reg_va09)
		dev_info(hba->dev, "failed to get va09");
	अन्यथा
		host->caps |= UFS_MTK_CAP_VA09_PWR_CTRL;
पूर्ण

अटल व्योम ufs_mtk_init_host_caps(काष्ठा ufs_hba *hba)
अणु
	काष्ठा ufs_mtk_host *host = ufshcd_get_variant(hba);
	काष्ठा device_node *np = hba->dev->of_node;

	अगर (of_property_पढ़ो_bool(np, "mediatek,ufs-boost-crypt"))
		ufs_mtk_init_boost_crypt(hba);

	अगर (of_property_पढ़ो_bool(np, "mediatek,ufs-support-va09"))
		ufs_mtk_init_va09_pwr_ctrl(hba);

	अगर (of_property_पढ़ो_bool(np, "mediatek,ufs-disable-ah8"))
		host->caps |= UFS_MTK_CAP_DISABLE_AH8;

	अगर (of_property_पढ़ो_bool(np, "mediatek,ufs-broken-vcc"))
		host->caps |= UFS_MTK_CAP_BROKEN_VCC;

	dev_info(hba->dev, "caps: 0x%x", host->caps);
पूर्ण

अटल व्योम ufs_mtk_scale_perf(काष्ठा ufs_hba *hba, bool up)
अणु
	काष्ठा ufs_mtk_host *host = ufshcd_get_variant(hba);

	ufs_mtk_boost_crypt(hba, up);
	ufs_mtk_setup_ref_clk(hba, up);

	अगर (up)
		phy_घातer_on(host->mphy);
	अन्यथा
		phy_घातer_off(host->mphy);
पूर्ण

/**
 * ufs_mtk_setup_घड़ीs - enables/disable घड़ीs
 * @hba: host controller instance
 * @on: If true, enable घड़ीs अन्यथा disable them.
 * @status: PRE_CHANGE or POST_CHANGE notअगरy
 *
 * Returns 0 on success, non-zero on failure.
 */
अटल पूर्णांक ufs_mtk_setup_घड़ीs(काष्ठा ufs_hba *hba, bool on,
				क्रमागत ufs_notअगरy_change_status status)
अणु
	काष्ठा ufs_mtk_host *host = ufshcd_get_variant(hba);
	bool clk_pwr_off = false;
	पूर्णांक ret = 0;

	/*
	 * In हाल ufs_mtk_init() is not yet करोne, simply ignore.
	 * This ufs_mtk_setup_घड़ीs() shall be called from
	 * ufs_mtk_init() after init is करोne.
	 */
	अगर (!host)
		वापस 0;

	अगर (!on && status == PRE_CHANGE) अणु
		अगर (ufshcd_is_link_off(hba)) अणु
			clk_pwr_off = true;
		पूर्ण अन्यथा अगर (ufshcd_is_link_hibern8(hba) ||
			 (!ufshcd_can_hibern8_during_gating(hba) &&
			 ufshcd_is_स्वतः_hibern8_enabled(hba))) अणु
			/*
			 * Gate ref-clk and घातeroff mphy अगर link state is in
			 * OFF or Hibern8 by either Auto-Hibern8 or
			 * ufshcd_link_state_transition().
			 */
			ret = ufs_mtk_रुको_link_state(hba,
						      VS_LINK_HIBERN8,
						      15);
			अगर (!ret)
				clk_pwr_off = true;
		पूर्ण

		अगर (clk_pwr_off)
			ufs_mtk_scale_perf(hba, false);
	पूर्ण अन्यथा अगर (on && status == POST_CHANGE) अणु
		ufs_mtk_scale_perf(hba, true);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम ufs_mtk_get_controller_version(काष्ठा ufs_hba *hba)
अणु
	काष्ठा ufs_mtk_host *host = ufshcd_get_variant(hba);
	पूर्णांक ret, ver = 0;

	अगर (host->hw_ver.major)
		वापस;

	/* Set शेष (minimum) version anyway */
	host->hw_ver.major = 2;

	ret = ufshcd_dme_get(hba, UIC_ARG_MIB(PA_LOCALVERINFO), &ver);
	अगर (!ret) अणु
		अगर (ver >= UFS_UNIPRO_VER_1_8) अणु
			host->hw_ver.major = 3;
			/*
			 * Fix HCI version क्रम some platक्रमms with
			 * incorrect version
			 */
			अगर (hba->ufs_version < ufshci_version(3, 0))
				hba->ufs_version = ufshci_version(3, 0);
		पूर्ण
	पूर्ण
पूर्ण

अटल u32 ufs_mtk_get_ufs_hci_version(काष्ठा ufs_hba *hba)
अणु
	वापस hba->ufs_version;
पूर्ण

/**
 * ufs_mtk_init - find other essential mmio bases
 * @hba: host controller instance
 *
 * Binds PHY with controller and घातers up PHY enabling घड़ीs
 * and regulators.
 *
 * Returns -EPROBE_DEFER अगर binding fails, वापसs negative error
 * on phy घातer up failure and वापसs zero on success.
 */
अटल पूर्णांक ufs_mtk_init(काष्ठा ufs_hba *hba)
अणु
	स्थिर काष्ठा of_device_id *id;
	काष्ठा device *dev = hba->dev;
	काष्ठा ufs_mtk_host *host;
	पूर्णांक err = 0;

	host = devm_kzalloc(dev, माप(*host), GFP_KERNEL);
	अगर (!host) अणु
		err = -ENOMEM;
		dev_info(dev, "%s: no memory for mtk ufs host\n", __func__);
		जाओ out;
	पूर्ण

	host->hba = hba;
	ufshcd_set_variant(hba, host);

	id = of_match_device(ufs_mtk_of_match, dev);
	अगर (!id) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	/* Initialize host capability */
	ufs_mtk_init_host_caps(hba);

	err = ufs_mtk_bind_mphy(hba);
	अगर (err)
		जाओ out_variant_clear;

	ufs_mtk_init_reset(hba);

	/* Enable runसमय स्वतःsuspend */
	hba->caps |= UFSHCD_CAP_RPM_AUTOSUSPEND;

	/* Enable घड़ी-gating */
	hba->caps |= UFSHCD_CAP_CLK_GATING;

	/* Enable अंतरभूत encryption */
	hba->caps |= UFSHCD_CAP_CRYPTO;

	/* Enable WriteBooster */
	hba->caps |= UFSHCD_CAP_WB_EN;
	hba->quirks |= UFSHCI_QUIRK_SKIP_MANUAL_WB_FLUSH_CTRL;
	hba->vps->wb_flush_threshold = UFS_WB_BUF_REMAIN_PERCENT(80);

	अगर (host->caps & UFS_MTK_CAP_DISABLE_AH8)
		hba->caps |= UFSHCD_CAP_HIBERN8_WITH_CLK_GATING;

	/*
	 * ufshcd_vops_init() is invoked after
	 * ufshcd_setup_घड़ी(true) in ufshcd_hba_init() thus
	 * phy घड़ी setup is skipped.
	 *
	 * Enable phy घड़ीs specअगरically here.
	 */
	ufs_mtk_mphy_घातer_on(hba, true);
	ufs_mtk_setup_घड़ीs(hba, true, POST_CHANGE);

	जाओ out;

out_variant_clear:
	ufshcd_set_variant(hba, शून्य);
out:
	वापस err;
पूर्ण

अटल पूर्णांक ufs_mtk_pre_pwr_change(काष्ठा ufs_hba *hba,
				  काष्ठा ufs_pa_layer_attr *dev_max_params,
				  काष्ठा ufs_pa_layer_attr *dev_req_params)
अणु
	काष्ठा ufs_mtk_host *host = ufshcd_get_variant(hba);
	काष्ठा ufs_dev_params host_cap;
	पूर्णांक ret;

	ufshcd_init_pwr_dev_param(&host_cap);
	host_cap.hs_rx_gear = UFS_HS_G4;
	host_cap.hs_tx_gear = UFS_HS_G4;

	ret = ufshcd_get_pwr_dev_param(&host_cap,
				       dev_max_params,
				       dev_req_params);
	अगर (ret) अणु
		pr_info("%s: failed to determine capabilities\n",
			__func__);
	पूर्ण

	अगर (host->hw_ver.major >= 3) अणु
		ret = ufshcd_dme_configure_adapt(hba,
					   dev_req_params->gear_tx,
					   PA_INITIAL_ADAPT);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ufs_mtk_pwr_change_notअगरy(काष्ठा ufs_hba *hba,
				     क्रमागत ufs_notअगरy_change_status stage,
				     काष्ठा ufs_pa_layer_attr *dev_max_params,
				     काष्ठा ufs_pa_layer_attr *dev_req_params)
अणु
	पूर्णांक ret = 0;

	चयन (stage) अणु
	हाल PRE_CHANGE:
		ret = ufs_mtk_pre_pwr_change(hba, dev_max_params,
					     dev_req_params);
		अवरोध;
	हाल POST_CHANGE:
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ufs_mtk_unipro_set_lpm(काष्ठा ufs_hba *hba, bool lpm)
अणु
	पूर्णांक ret;
	काष्ठा ufs_mtk_host *host = ufshcd_get_variant(hba);

	ret = ufshcd_dme_set(hba,
			     UIC_ARG_MIB_SEL(VS_UNIPROPOWERDOWNCONTROL, 0),
			     lpm ? 1 : 0);
	अगर (!ret || !lpm) अणु
		/*
		 * Forcibly set as non-LPM mode अगर UIC commands is failed
		 * to use शेष hba_enable_delay_us value क्रम re-enabling
		 * the host.
		 */
		host->unipro_lpm = lpm;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ufs_mtk_pre_link(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक ret;
	u32 पंचांगp;

	ufs_mtk_get_controller_version(hba);

	ret = ufs_mtk_unipro_set_lpm(hba, false);
	अगर (ret)
		वापस ret;

	/*
	 * Setting PA_Local_TX_LCC_Enable to 0 beक्रमe link startup
	 * to make sure that both host and device TX LCC are disabled
	 * once link startup is completed.
	 */
	ret = ufshcd_disable_host_tx_lcc(hba);
	अगर (ret)
		वापस ret;

	/* disable deep stall */
	ret = ufshcd_dme_get(hba, UIC_ARG_MIB(VS_SAVEPOWERCONTROL), &पंचांगp);
	अगर (ret)
		वापस ret;

	पंचांगp &= ~(1 << 6);

	ret = ufshcd_dme_set(hba, UIC_ARG_MIB(VS_SAVEPOWERCONTROL), पंचांगp);

	वापस ret;
पूर्ण

अटल व्योम ufs_mtk_setup_clk_gating(काष्ठा ufs_hba *hba)
अणु
	अचिन्हित दीर्घ flags;
	u32 ah_ms;

	अगर (ufshcd_is_clkgating_allowed(hba)) अणु
		अगर (ufshcd_is_स्वतः_hibern8_supported(hba) && hba->ahit)
			ah_ms = FIELD_GET(UFSHCI_AHIBERN8_TIMER_MASK,
					  hba->ahit);
		अन्यथा
			ah_ms = 10;
		spin_lock_irqsave(hba->host->host_lock, flags);
		hba->clk_gating.delay_ms = ah_ms + 5;
		spin_unlock_irqrestore(hba->host->host_lock, flags);
	पूर्ण
पूर्ण

अटल पूर्णांक ufs_mtk_post_link(काष्ठा ufs_hba *hba)
अणु
	/* enable unipro घड़ी gating feature */
	ufs_mtk_cfg_unipro_cg(hba, true);

	/* configure स्वतः-hibern8 समयr to 10ms */
	अगर (ufshcd_is_स्वतः_hibern8_supported(hba)) अणु
		ufshcd_स्वतः_hibern8_update(hba,
			FIELD_PREP(UFSHCI_AHIBERN8_TIMER_MASK, 10) |
			FIELD_PREP(UFSHCI_AHIBERN8_SCALE_MASK, 3));
	पूर्ण

	ufs_mtk_setup_clk_gating(hba);

	वापस 0;
पूर्ण

अटल पूर्णांक ufs_mtk_link_startup_notअगरy(काष्ठा ufs_hba *hba,
				       क्रमागत ufs_notअगरy_change_status stage)
अणु
	पूर्णांक ret = 0;

	चयन (stage) अणु
	हाल PRE_CHANGE:
		ret = ufs_mtk_pre_link(hba);
		अवरोध;
	हाल POST_CHANGE:
		ret = ufs_mtk_post_link(hba);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ufs_mtk_device_reset(काष्ठा ufs_hba *hba)
अणु
	काष्ठा arm_smccc_res res;

	ufs_mtk_device_reset_ctrl(0, res);

	/*
	 * The reset संकेत is active low. UFS devices shall detect
	 * more than or equal to 1us of positive or negative RST_n
	 * pulse width.
	 *
	 * To be on safe side, keep the reset low क्रम at least 10us.
	 */
	usleep_range(10, 15);

	ufs_mtk_device_reset_ctrl(1, res);

	/* Some devices may need समय to respond to rst_n */
	usleep_range(10000, 15000);

	dev_info(hba->dev, "device reset done\n");

	वापस 0;
पूर्ण

अटल पूर्णांक ufs_mtk_link_set_hpm(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक err;

	err = ufshcd_hba_enable(hba);
	अगर (err)
		वापस err;

	err = ufs_mtk_unipro_set_lpm(hba, false);
	अगर (err)
		वापस err;

	err = ufshcd_uic_hibern8_निकास(hba);
	अगर (!err)
		ufshcd_set_link_active(hba);
	अन्यथा
		वापस err;

	err = ufshcd_make_hba_operational(hba);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक ufs_mtk_link_set_lpm(काष्ठा ufs_hba *hba)
अणु
	पूर्णांक err;

	err = ufs_mtk_unipro_set_lpm(hba, true);
	अगर (err) अणु
		/* Resume UniPro state क्रम following error recovery */
		ufs_mtk_unipro_set_lpm(hba, false);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ufs_mtk_vreg_set_lpm(काष्ठा ufs_hba *hba, bool lpm)
अणु
	अगर (!hba->vreg_info.vccq2 || !hba->vreg_info.vcc)
		वापस;

	अगर (lpm && !hba->vreg_info.vcc->enabled)
		regulator_set_mode(hba->vreg_info.vccq2->reg,
				   REGULATOR_MODE_IDLE);
	अन्यथा अगर (!lpm)
		regulator_set_mode(hba->vreg_info.vccq2->reg,
				   REGULATOR_MODE_NORMAL);
पूर्ण

अटल पूर्णांक ufs_mtk_suspend(काष्ठा ufs_hba *hba, क्रमागत ufs_pm_op pm_op)
अणु
	पूर्णांक err;
	काष्ठा arm_smccc_res res;

	अगर (ufshcd_is_link_hibern8(hba)) अणु
		err = ufs_mtk_link_set_lpm(hba);
		अगर (err)
			जाओ fail;
	पूर्ण

	अगर (!ufshcd_is_link_active(hba)) अणु
		/*
		 * Make sure no error will be वापसed to prevent
		 * ufshcd_suspend() re-enabling regulators जबतक vreg is still
		 * in low-घातer mode.
		 */
		ufs_mtk_vreg_set_lpm(hba, true);
		err = ufs_mtk_mphy_घातer_on(hba, false);
		अगर (err)
			जाओ fail;
	पूर्ण

	अगर (ufshcd_is_link_off(hba))
		ufs_mtk_device_reset_ctrl(0, res);

	वापस 0;
fail:
	/*
	 * Set link as off state enक्रमcedly to trigger
	 * ufshcd_host_reset_and_restore() in ufshcd_suspend()
	 * क्रम completed host reset.
	 */
	ufshcd_set_link_off(hba);
	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक ufs_mtk_resume(काष्ठा ufs_hba *hba, क्रमागत ufs_pm_op pm_op)
अणु
	पूर्णांक err;

	err = ufs_mtk_mphy_घातer_on(hba, true);
	अगर (err)
		जाओ fail;

	ufs_mtk_vreg_set_lpm(hba, false);

	अगर (ufshcd_is_link_hibern8(hba)) अणु
		err = ufs_mtk_link_set_hpm(hba);
		अगर (err)
			जाओ fail;
	पूर्ण

	वापस 0;
fail:
	वापस ufshcd_link_recovery(hba);
पूर्ण

अटल व्योम ufs_mtk_dbg_रेजिस्टर_dump(काष्ठा ufs_hba *hba)
अणु
	ufshcd_dump_regs(hba, REG_UFS_REFCLK_CTRL, 0x4, "Ref-Clk Ctrl ");

	ufshcd_dump_regs(hba, REG_UFS_EXTREG, 0x4, "Ext Reg ");

	ufshcd_dump_regs(hba, REG_UFS_MPHYCTRL,
			 REG_UFS_REJECT_MON - REG_UFS_MPHYCTRL + 4,
			 "MPHY Ctrl ");

	/* Direct debugging inक्रमmation to REG_MTK_PROBE */
	ufshcd_ग_लिखोl(hba, 0x20, REG_UFS_DEBUG_SEL);
	ufshcd_dump_regs(hba, REG_UFS_PROBE, 0x4, "Debug Probe ");
पूर्ण

अटल पूर्णांक ufs_mtk_apply_dev_quirks(काष्ठा ufs_hba *hba)
अणु
	काष्ठा ufs_dev_info *dev_info = &hba->dev_info;
	u16 mid = dev_info->wmanufacturerid;

	अगर (mid == UFS_VENDOR_SAMSUNG)
		ufshcd_dme_set(hba, UIC_ARG_MIB(PA_TACTIVATE), 6);

	/*
	 * Decide रुकोing समय beक्रमe gating reference घड़ी and
	 * after ungating reference घड़ी according to venकरोrs'
	 * requirements.
	 */
	अगर (mid == UFS_VENDOR_SAMSUNG)
		ufs_mtk_setup_ref_clk_रुको_us(hba, 1, 1);
	अन्यथा अगर (mid == UFS_VENDOR_SKHYNIX)
		ufs_mtk_setup_ref_clk_रुको_us(hba, 30, 30);
	अन्यथा अगर (mid == UFS_VENDOR_TOSHIBA)
		ufs_mtk_setup_ref_clk_रुको_us(hba, 100, 32);

	वापस 0;
पूर्ण

अटल व्योम ufs_mtk_fixup_dev_quirks(काष्ठा ufs_hba *hba)
अणु
	ufshcd_fixup_dev_quirks(hba, ufs_mtk_dev_fixups);

	अगर (ufs_mtk_is_broken_vcc(hba) && hba->vreg_info.vcc &&
	    (hba->dev_quirks & UFS_DEVICE_QUIRK_DELAY_AFTER_LPM)) अणु
		hba->vreg_info.vcc->always_on = true;
		/*
		 * VCC will be kept always-on thus we करोn't
		 * need any delay during regulator operations
		 */
		hba->dev_quirks &= ~(UFS_DEVICE_QUIRK_DELAY_BEFORE_LPM |
			UFS_DEVICE_QUIRK_DELAY_AFTER_LPM);
	पूर्ण
पूर्ण

अटल व्योम ufs_mtk_event_notअगरy(काष्ठा ufs_hba *hba,
				 क्रमागत ufs_event_type evt, व्योम *data)
अणु
	अचिन्हित पूर्णांक val = *(u32 *)data;

	trace_ufs_mtk_event(evt, val);
पूर्ण

/*
 * काष्ठा ufs_hba_mtk_vops - UFS MTK specअगरic variant operations
 *
 * The variant operations configure the necessary controller and PHY
 * handshake during initialization.
 */
अटल स्थिर काष्ठा ufs_hba_variant_ops ufs_hba_mtk_vops = अणु
	.name                = "mediatek.ufshci",
	.init                = ufs_mtk_init,
	.get_ufs_hci_version = ufs_mtk_get_ufs_hci_version,
	.setup_घड़ीs        = ufs_mtk_setup_घड़ीs,
	.hce_enable_notअगरy   = ufs_mtk_hce_enable_notअगरy,
	.link_startup_notअगरy = ufs_mtk_link_startup_notअगरy,
	.pwr_change_notअगरy   = ufs_mtk_pwr_change_notअगरy,
	.apply_dev_quirks    = ufs_mtk_apply_dev_quirks,
	.fixup_dev_quirks    = ufs_mtk_fixup_dev_quirks,
	.suspend             = ufs_mtk_suspend,
	.resume              = ufs_mtk_resume,
	.dbg_रेजिस्टर_dump   = ufs_mtk_dbg_रेजिस्टर_dump,
	.device_reset        = ufs_mtk_device_reset,
	.event_notअगरy        = ufs_mtk_event_notअगरy,
पूर्ण;

/**
 * ufs_mtk_probe - probe routine of the driver
 * @pdev: poपूर्णांकer to Platक्रमm device handle
 *
 * Return zero क्रम success and non-zero क्रम failure
 */
अटल पूर्णांक ufs_mtk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err;
	काष्ठा device *dev = &pdev->dev;

	/* perक्रमm generic probe */
	err = ufshcd_pltfrm_init(pdev, &ufs_hba_mtk_vops);
	अगर (err)
		dev_info(dev, "probe failed %d\n", err);

	वापस err;
पूर्ण

/**
 * ufs_mtk_हटाओ - set driver_data of the device to शून्य
 * @pdev: poपूर्णांकer to platक्रमm device handle
 *
 * Always वापस 0
 */
अटल पूर्णांक ufs_mtk_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ufs_hba *hba =  platक्रमm_get_drvdata(pdev);

	pm_runसमय_get_sync(&(pdev)->dev);
	ufshcd_हटाओ(hba);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ufs_mtk_pm_ops = अणु
	.suspend         = ufshcd_pltfrm_suspend,
	.resume          = ufshcd_pltfrm_resume,
	.runसमय_suspend = ufshcd_pltfrm_runसमय_suspend,
	.runसमय_resume  = ufshcd_pltfrm_runसमय_resume,
	.runसमय_idle    = ufshcd_pltfrm_runसमय_idle,
पूर्ण;

अटल काष्ठा platक्रमm_driver ufs_mtk_pltक्रमm = अणु
	.probe      = ufs_mtk_probe,
	.हटाओ     = ufs_mtk_हटाओ,
	.shutकरोwn   = ufshcd_pltfrm_shutकरोwn,
	.driver = अणु
		.name   = "ufshcd-mtk",
		.pm     = &ufs_mtk_pm_ops,
		.of_match_table = ufs_mtk_of_match,
	पूर्ण,
पूर्ण;

MODULE_AUTHOR("Stanley Chu <stanley.chu@mediatek.com>");
MODULE_AUTHOR("Peter Wang <peter.wang@mediatek.com>");
MODULE_DESCRIPTION("MediaTek UFS Host Driver");
MODULE_LICENSE("GPL v2");

module_platक्रमm_driver(ufs_mtk_pltक्रमm);
