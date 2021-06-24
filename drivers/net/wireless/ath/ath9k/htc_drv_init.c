<शैली गुरु>
/*
 * Copyright (c) 2010-2011 Atheros Communications Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "htc.h"

MODULE_AUTHOR("Atheros Communications");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Atheros driver 802.11n HTC based wireless devices");

अटल अचिन्हित पूर्णांक ath9k_debug = ATH_DBG_DEFAULT;
module_param_named(debug, ath9k_debug, uपूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debugging mask");

पूर्णांक htc_modparam_nohwcrypt;
module_param_named(nohwcrypt, htc_modparam_nohwcrypt, पूर्णांक, 0444);
MODULE_PARM_DESC(nohwcrypt, "Disable hardware encryption");

अटल पूर्णांक ath9k_htc_btcoex_enable;
module_param_named(btcoex_enable, ath9k_htc_btcoex_enable, पूर्णांक, 0444);
MODULE_PARM_DESC(btcoex_enable, "Enable wifi-BT coexistence");

अटल पूर्णांक ath9k_ps_enable;
module_param_named(ps_enable, ath9k_ps_enable, पूर्णांक, 0444);
MODULE_PARM_DESC(ps_enable, "Enable WLAN PowerSave");

पूर्णांक htc_use_dev_fw = 0;
module_param_named(use_dev_fw, htc_use_dev_fw, पूर्णांक, 0444);
MODULE_PARM_DESC(use_dev_fw, "Use development FW version");

#अगर_घोषित CONFIG_MAC80211_LEDS
पूर्णांक ath9k_htc_led_blink = 1;
module_param_named(blink, ath9k_htc_led_blink, पूर्णांक, 0444);
MODULE_PARM_DESC(blink, "Enable LED blink on activity");

अटल स्थिर काष्ठा ieee80211_tpt_blink ath9k_htc_tpt_blink[] = अणु
	अणु .throughput = 0 * 1024, .blink_समय = 334 पूर्ण,
	अणु .throughput = 1 * 1024, .blink_समय = 260 पूर्ण,
	अणु .throughput = 5 * 1024, .blink_समय = 220 पूर्ण,
	अणु .throughput = 10 * 1024, .blink_समय = 190 पूर्ण,
	अणु .throughput = 20 * 1024, .blink_समय = 170 पूर्ण,
	अणु .throughput = 50 * 1024, .blink_समय = 150 पूर्ण,
	अणु .throughput = 70 * 1024, .blink_समय = 130 पूर्ण,
	अणु .throughput = 100 * 1024, .blink_समय = 110 पूर्ण,
	अणु .throughput = 200 * 1024, .blink_समय = 80 पूर्ण,
	अणु .throughput = 300 * 1024, .blink_समय = 50 पूर्ण,
पूर्ण;
#पूर्ण_अगर

अटल व्योम ath9k_htc_op_ps_wakeup(काष्ठा ath_common *common)
अणु
	ath9k_htc_ps_wakeup((काष्ठा ath9k_htc_priv *) common->priv);
पूर्ण

अटल व्योम ath9k_htc_op_ps_restore(काष्ठा ath_common *common)
अणु
	ath9k_htc_ps_restore((काष्ठा ath9k_htc_priv *) common->priv);
पूर्ण

अटल स्थिर काष्ठा ath_ps_ops ath9k_htc_ps_ops = अणु
	.wakeup = ath9k_htc_op_ps_wakeup,
	.restore = ath9k_htc_op_ps_restore,
पूर्ण;

अटल पूर्णांक ath9k_htc_रुको_क्रम_target(काष्ठा ath9k_htc_priv *priv)
अणु
	अचिन्हित दीर्घ समय_left;

	अगर (atomic_पढ़ो(&priv->htc->tgt_पढ़ोy) > 0) अणु
		atomic_dec(&priv->htc->tgt_पढ़ोy);
		वापस 0;
	पूर्ण

	/* Firmware can take up to 50ms to get पढ़ोy, to be safe use 1 second */
	समय_left = रुको_क्रम_completion_समयout(&priv->htc->target_रुको, HZ);
	अगर (!समय_left) अणु
		dev_err(priv->dev, "ath9k_htc: Target is unresponsive\n");
		वापस -ETIMEDOUT;
	पूर्ण

	atomic_dec(&priv->htc->tgt_पढ़ोy);

	वापस 0;
पूर्ण

अटल व्योम ath9k_deinit_priv(काष्ठा ath9k_htc_priv *priv)
अणु
	ath9k_hw_deinit(priv->ah);
	kमुक्त(priv->ah);
	priv->ah = शून्य;
पूर्ण

अटल व्योम ath9k_deinit_device(काष्ठा ath9k_htc_priv *priv)
अणु
	काष्ठा ieee80211_hw *hw = priv->hw;

	wiphy_rfसमाप्त_stop_polling(hw->wiphy);
	ath9k_deinit_leds(priv);
	ath9k_htc_deinit_debug(priv);
	ieee80211_unरेजिस्टर_hw(hw);
	ath9k_rx_cleanup(priv);
	ath9k_tx_cleanup(priv);
	ath9k_deinit_priv(priv);
पूर्ण

अटल अंतरभूत पूर्णांक ath9k_htc_connect_svc(काष्ठा ath9k_htc_priv *priv,
					u16 service_id,
					व्योम (*tx) (व्योम *,
						    काष्ठा sk_buff *,
						    क्रमागत htc_endpoपूर्णांक_id,
						    bool txok),
					क्रमागत htc_endpoपूर्णांक_id *ep_id)
अणु
	काष्ठा htc_service_connreq req;

	स_रखो(&req, 0, माप(काष्ठा htc_service_connreq));

	req.service_id = service_id;
	req.ep_callbacks.priv = priv;
	req.ep_callbacks.rx = ath9k_htc_rxep;
	req.ep_callbacks.tx = tx;

	वापस htc_connect_service(priv->htc, &req, ep_id);
पूर्ण

अटल पूर्णांक ath9k_init_htc_services(काष्ठा ath9k_htc_priv *priv, u16 devid,
				   u32 drv_info)
अणु
	पूर्णांक ret;

	/* WMI CMD*/
	ret = ath9k_wmi_connect(priv->htc, priv->wmi, &priv->wmi_cmd_ep);
	अगर (ret)
		जाओ err;

	/* Beacon */
	ret = ath9k_htc_connect_svc(priv, WMI_BEACON_SVC, ath9k_htc_beaconep,
				    &priv->beacon_ep);
	अगर (ret)
		जाओ err;

	/* CAB */
	ret = ath9k_htc_connect_svc(priv, WMI_CAB_SVC, ath9k_htc_txep,
				    &priv->cab_ep);
	अगर (ret)
		जाओ err;


	/* UAPSD */
	ret = ath9k_htc_connect_svc(priv, WMI_UAPSD_SVC, ath9k_htc_txep,
				    &priv->uapsd_ep);
	अगर (ret)
		जाओ err;

	/* MGMT */
	ret = ath9k_htc_connect_svc(priv, WMI_MGMT_SVC, ath9k_htc_txep,
				    &priv->mgmt_ep);
	अगर (ret)
		जाओ err;

	/* DATA BE */
	ret = ath9k_htc_connect_svc(priv, WMI_DATA_BE_SVC, ath9k_htc_txep,
				    &priv->data_be_ep);
	अगर (ret)
		जाओ err;

	/* DATA BK */
	ret = ath9k_htc_connect_svc(priv, WMI_DATA_BK_SVC, ath9k_htc_txep,
				    &priv->data_bk_ep);
	अगर (ret)
		जाओ err;

	/* DATA VI */
	ret = ath9k_htc_connect_svc(priv, WMI_DATA_VI_SVC, ath9k_htc_txep,
				    &priv->data_vi_ep);
	अगर (ret)
		जाओ err;

	/* DATA VO */
	ret = ath9k_htc_connect_svc(priv, WMI_DATA_VO_SVC, ath9k_htc_txep,
				    &priv->data_vo_ep);
	अगर (ret)
		जाओ err;

	/*
	 * Setup required credits beक्रमe initializing HTC.
	 * This is a bit hacky, but, since queuing is करोne in
	 * the HIF layer, shouldn't matter much.
	 */

	अगर (IS_AR7010_DEVICE(drv_info))
		priv->htc->credits = 45;
	अन्यथा
		priv->htc->credits = 33;

	ret = htc_init(priv->htc);
	अगर (ret)
		जाओ err;

	dev_info(priv->dev, "ath9k_htc: HTC initialized with %d credits\n",
		 priv->htc->credits);

	वापस 0;

err:
	dev_err(priv->dev, "ath9k_htc: Unable to initialize HTC services\n");
	वापस ret;
पूर्ण

अटल व्योम ath9k_reg_notअगरier(काष्ठा wiphy *wiphy,
			       काष्ठा regulatory_request *request)
अणु
	काष्ठा ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	काष्ठा ath9k_htc_priv *priv = hw->priv;

	ath_reg_notअगरier_apply(wiphy, request,
			       ath9k_hw_regulatory(priv->ah));
पूर्ण

अटल अचिन्हित पूर्णांक ath9k_regपढ़ो(व्योम *hw_priv, u32 reg_offset)
अणु
	काष्ठा ath_hw *ah = hw_priv;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_htc_priv *priv = (काष्ठा ath9k_htc_priv *) common->priv;
	__be32 val, reg = cpu_to_be32(reg_offset);
	पूर्णांक r;

	r = ath9k_wmi_cmd(priv->wmi, WMI_REG_READ_CMDID,
			  (u8 *) &reg, माप(reg),
			  (u8 *) &val, माप(val),
			  100);
	अगर (unlikely(r)) अणु
		ath_dbg(common, WMI, "REGISTER READ FAILED: (0x%04x, %d)\n",
			reg_offset, r);
		वापस -1;
	पूर्ण

	वापस be32_to_cpu(val);
पूर्ण

अटल व्योम ath9k_multi_regपढ़ो(व्योम *hw_priv, u32 *addr,
				u32 *val, u16 count)
अणु
	काष्ठा ath_hw *ah = hw_priv;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_htc_priv *priv = (काष्ठा ath9k_htc_priv *) common->priv;
	__be32 पंचांगpaddr[8];
	__be32 पंचांगpval[8];
	पूर्णांक i, ret;

	क्रम (i = 0; i < count; i++) अणु
		पंचांगpaddr[i] = cpu_to_be32(addr[i]);
	पूर्ण

	ret = ath9k_wmi_cmd(priv->wmi, WMI_REG_READ_CMDID,
			   (u8 *)पंचांगpaddr , माप(u32) * count,
			   (u8 *)पंचांगpval, माप(u32) * count,
			   100);
	अगर (unlikely(ret)) अणु
		ath_dbg(common, WMI,
			"Multiple REGISTER READ FAILED (count: %d)\n", count);
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		val[i] = be32_to_cpu(पंचांगpval[i]);
	पूर्ण
पूर्ण

अटल व्योम ath9k_regग_लिखो_multi(काष्ठा ath_common *common)
अणु
	काष्ठा ath9k_htc_priv *priv = (काष्ठा ath9k_htc_priv *) common->priv;
	u32 rsp_status;
	पूर्णांक r;

	r = ath9k_wmi_cmd(priv->wmi, WMI_REG_WRITE_CMDID,
			  (u8 *) &priv->wmi->multi_ग_लिखो,
			  माप(काष्ठा रेजिस्टर_ग_लिखो) * priv->wmi->multi_ग_लिखो_idx,
			  (u8 *) &rsp_status, माप(rsp_status),
			  100);
	अगर (unlikely(r)) अणु
		ath_dbg(common, WMI,
			"REGISTER WRITE FAILED, multi len: %d\n",
			priv->wmi->multi_ग_लिखो_idx);
	पूर्ण
	priv->wmi->multi_ग_लिखो_idx = 0;
पूर्ण

अटल व्योम ath9k_regग_लिखो_single(व्योम *hw_priv, u32 val, u32 reg_offset)
अणु
	काष्ठा ath_hw *ah = hw_priv;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_htc_priv *priv = (काष्ठा ath9k_htc_priv *) common->priv;
	स्थिर __be32 buf[2] = अणु
		cpu_to_be32(reg_offset),
		cpu_to_be32(val),
	पूर्ण;
	पूर्णांक r;

	r = ath9k_wmi_cmd(priv->wmi, WMI_REG_WRITE_CMDID,
			  (u8 *) &buf, माप(buf),
			  (u8 *) &val, माप(val),
			  100);
	अगर (unlikely(r)) अणु
		ath_dbg(common, WMI, "REGISTER WRITE FAILED:(0x%04x, %d)\n",
			reg_offset, r);
	पूर्ण
पूर्ण

अटल व्योम ath9k_regग_लिखो_buffer(व्योम *hw_priv, u32 val, u32 reg_offset)
अणु
	काष्ठा ath_hw *ah = hw_priv;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_htc_priv *priv = (काष्ठा ath9k_htc_priv *) common->priv;

	mutex_lock(&priv->wmi->multi_ग_लिखो_mutex);

	/* Store the रेजिस्टर/value */
	priv->wmi->multi_ग_लिखो[priv->wmi->multi_ग_लिखो_idx].reg =
		cpu_to_be32(reg_offset);
	priv->wmi->multi_ग_लिखो[priv->wmi->multi_ग_लिखो_idx].val =
		cpu_to_be32(val);

	priv->wmi->multi_ग_लिखो_idx++;

	/* If the buffer is full, send it out. */
	अगर (priv->wmi->multi_ग_लिखो_idx == MAX_CMD_NUMBER)
		ath9k_regग_लिखो_multi(common);

	mutex_unlock(&priv->wmi->multi_ग_लिखो_mutex);
पूर्ण

अटल व्योम ath9k_regग_लिखो(व्योम *hw_priv, u32 val, u32 reg_offset)
अणु
	काष्ठा ath_hw *ah = hw_priv;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_htc_priv *priv = (काष्ठा ath9k_htc_priv *) common->priv;

	अगर (atomic_पढ़ो(&priv->wmi->mग_लिखो_cnt))
		ath9k_regग_लिखो_buffer(hw_priv, val, reg_offset);
	अन्यथा
		ath9k_regग_लिखो_single(hw_priv, val, reg_offset);
पूर्ण

अटल व्योम ath9k_enable_regग_लिखो_buffer(व्योम *hw_priv)
अणु
	काष्ठा ath_hw *ah = hw_priv;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_htc_priv *priv = (काष्ठा ath9k_htc_priv *) common->priv;

	atomic_inc(&priv->wmi->mग_लिखो_cnt);
पूर्ण

अटल व्योम ath9k_regग_लिखो_flush(व्योम *hw_priv)
अणु
	काष्ठा ath_hw *ah = hw_priv;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_htc_priv *priv = (काष्ठा ath9k_htc_priv *) common->priv;

	atomic_dec(&priv->wmi->mग_लिखो_cnt);

	mutex_lock(&priv->wmi->multi_ग_लिखो_mutex);

	अगर (priv->wmi->multi_ग_लिखो_idx)
		ath9k_regग_लिखो_multi(common);

	mutex_unlock(&priv->wmi->multi_ग_लिखो_mutex);
पूर्ण

अटल व्योम ath9k_reg_rmw_buffer(व्योम *hw_priv,
				 u32 reg_offset, u32 set, u32 clr)
अणु
	काष्ठा ath_hw *ah = hw_priv;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_htc_priv *priv = (काष्ठा ath9k_htc_priv *) common->priv;
	u32 rsp_status;
	पूर्णांक r;

	mutex_lock(&priv->wmi->multi_rmw_mutex);

	/* Store the रेजिस्टर/value */
	priv->wmi->multi_rmw[priv->wmi->multi_rmw_idx].reg =
		cpu_to_be32(reg_offset);
	priv->wmi->multi_rmw[priv->wmi->multi_rmw_idx].set =
		cpu_to_be32(set);
	priv->wmi->multi_rmw[priv->wmi->multi_rmw_idx].clr =
		cpu_to_be32(clr);

	priv->wmi->multi_rmw_idx++;

	/* If the buffer is full, send it out. */
	अगर (priv->wmi->multi_rmw_idx == MAX_RMW_CMD_NUMBER) अणु
		r = ath9k_wmi_cmd(priv->wmi, WMI_REG_RMW_CMDID,
			  (u8 *) &priv->wmi->multi_rmw,
			  माप(काष्ठा रेजिस्टर_ग_लिखो) * priv->wmi->multi_rmw_idx,
			  (u8 *) &rsp_status, माप(rsp_status),
			  100);
		अगर (unlikely(r)) अणु
			ath_dbg(common, WMI,
				"REGISTER RMW FAILED, multi len: %d\n",
				priv->wmi->multi_rmw_idx);
		पूर्ण
		priv->wmi->multi_rmw_idx = 0;
	पूर्ण

	mutex_unlock(&priv->wmi->multi_rmw_mutex);
पूर्ण

अटल व्योम ath9k_reg_rmw_flush(व्योम *hw_priv)
अणु
	काष्ठा ath_hw *ah = hw_priv;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_htc_priv *priv = (काष्ठा ath9k_htc_priv *) common->priv;
	u32 rsp_status;
	पूर्णांक r;

	अगर (test_bit(HTC_FWFLAG_NO_RMW, &priv->fw_flags))
		वापस;

	atomic_dec(&priv->wmi->m_rmw_cnt);

	mutex_lock(&priv->wmi->multi_rmw_mutex);

	अगर (priv->wmi->multi_rmw_idx) अणु
		r = ath9k_wmi_cmd(priv->wmi, WMI_REG_RMW_CMDID,
			  (u8 *) &priv->wmi->multi_rmw,
			  माप(काष्ठा रेजिस्टर_rmw) * priv->wmi->multi_rmw_idx,
			  (u8 *) &rsp_status, माप(rsp_status),
			  100);
		अगर (unlikely(r)) अणु
			ath_dbg(common, WMI,
				"REGISTER RMW FAILED, multi len: %d\n",
				priv->wmi->multi_rmw_idx);
		पूर्ण
		priv->wmi->multi_rmw_idx = 0;
	पूर्ण

	mutex_unlock(&priv->wmi->multi_rmw_mutex);
पूर्ण

अटल व्योम ath9k_enable_rmw_buffer(व्योम *hw_priv)
अणु
	काष्ठा ath_hw *ah = hw_priv;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_htc_priv *priv = (काष्ठा ath9k_htc_priv *) common->priv;

	अगर (test_bit(HTC_FWFLAG_NO_RMW, &priv->fw_flags))
		वापस;

	atomic_inc(&priv->wmi->m_rmw_cnt);
पूर्ण

अटल व्योम ath9k_reg_rmw_single(व्योम *hw_priv,
				 u32 reg_offset, u32 set, u32 clr)
अणु
	काष्ठा ath_hw *ah = hw_priv;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_htc_priv *priv = (काष्ठा ath9k_htc_priv *) common->priv;
	काष्ठा रेजिस्टर_rmw buf, buf_ret;
	पूर्णांक ret;

	buf.reg = cpu_to_be32(reg_offset);
	buf.set = cpu_to_be32(set);
	buf.clr = cpu_to_be32(clr);

	ret = ath9k_wmi_cmd(priv->wmi, WMI_REG_RMW_CMDID,
			  (u8 *) &buf, माप(buf),
			  (u8 *) &buf_ret, माप(buf_ret),
			  100);
	अगर (unlikely(ret)) अणु
		ath_dbg(common, WMI, "REGISTER RMW FAILED:(0x%04x, %d)\n",
			reg_offset, ret);
	पूर्ण
पूर्ण

अटल u32 ath9k_reg_rmw(व्योम *hw_priv, u32 reg_offset, u32 set, u32 clr)
अणु
	काष्ठा ath_hw *ah = hw_priv;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_htc_priv *priv = (काष्ठा ath9k_htc_priv *) common->priv;

	अगर (test_bit(HTC_FWFLAG_NO_RMW, &priv->fw_flags)) अणु
		u32 val;

		val = REG_READ(ah, reg_offset);
		val &= ~clr;
		val |= set;
		REG_WRITE(ah, reg_offset, val);

		वापस 0;
	पूर्ण

	अगर (atomic_पढ़ो(&priv->wmi->m_rmw_cnt))
		ath9k_reg_rmw_buffer(hw_priv, reg_offset, set, clr);
	अन्यथा
		ath9k_reg_rmw_single(hw_priv, reg_offset, set, clr);

	वापस 0;
पूर्ण

अटल व्योम ath_usb_पढ़ो_cachesize(काष्ठा ath_common *common, पूर्णांक *csz)
अणु
	*csz = L1_CACHE_BYTES >> 2;
पूर्ण

अटल bool ath_usb_eeprom_पढ़ो(काष्ठा ath_common *common, u32 off, u16 *data)
अणु
	काष्ठा ath_hw *ah = (काष्ठा ath_hw *) common->ah;

	(व्योम)REG_READ(ah, AR5416_EEPROM_OFFSET + (off << AR5416_EEPROM_S));

	अगर (!ath9k_hw_रुको(ah,
			   AR_EEPROM_STATUS_DATA,
			   AR_EEPROM_STATUS_DATA_BUSY |
			   AR_EEPROM_STATUS_DATA_PROT_ACCESS, 0,
			   AH_WAIT_TIMEOUT))
		वापस false;

	*data = MS(REG_READ(ah, AR_EEPROM_STATUS_DATA),
		   AR_EEPROM_STATUS_DATA_VAL);

	वापस true;
पूर्ण

अटल स्थिर काष्ठा ath_bus_ops ath9k_usb_bus_ops = अणु
	.ath_bus_type = ATH_USB,
	.पढ़ो_cachesize = ath_usb_पढ़ो_cachesize,
	.eeprom_पढ़ो = ath_usb_eeprom_पढ़ो,
पूर्ण;

अटल पूर्णांक ath9k_init_queues(काष्ठा ath9k_htc_priv *priv)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(priv->hwq_map); i++)
		priv->hwq_map[i] = -1;

	priv->beacon.beaconq = ath9k_hw_beaconq_setup(priv->ah);
	अगर (priv->beacon.beaconq == -1) अणु
		ath_err(common, "Unable to setup BEACON xmit queue\n");
		जाओ err;
	पूर्ण

	priv->cabq = ath9k_htc_cabq_setup(priv);
	अगर (priv->cabq == -1) अणु
		ath_err(common, "Unable to setup CAB xmit queue\n");
		जाओ err;
	पूर्ण

	अगर (!ath9k_htc_txq_setup(priv, IEEE80211_AC_BE)) अणु
		ath_err(common, "Unable to setup xmit queue for BE traffic\n");
		जाओ err;
	पूर्ण

	अगर (!ath9k_htc_txq_setup(priv, IEEE80211_AC_BK)) अणु
		ath_err(common, "Unable to setup xmit queue for BK traffic\n");
		जाओ err;
	पूर्ण
	अगर (!ath9k_htc_txq_setup(priv, IEEE80211_AC_VI)) अणु
		ath_err(common, "Unable to setup xmit queue for VI traffic\n");
		जाओ err;
	पूर्ण
	अगर (!ath9k_htc_txq_setup(priv, IEEE80211_AC_VO)) अणु
		ath_err(common, "Unable to setup xmit queue for VO traffic\n");
		जाओ err;
	पूर्ण

	वापस 0;

err:
	वापस -EINVAL;
पूर्ण

अटल व्योम ath9k_init_misc(काष्ठा ath9k_htc_priv *priv)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);

	eth_broadcast_addr(common->bssidmask);

	common->last_rssi = ATH_RSSI_DUMMY_MARKER;
	priv->ah->opmode = NL80211_IFTYPE_STATION;

	priv->spec_priv.ah = priv->ah;
	priv->spec_priv.spec_config.enabled = 0;
	priv->spec_priv.spec_config.लघु_repeat = true;
	priv->spec_priv.spec_config.count = 8;
	priv->spec_priv.spec_config.endless = false;
	priv->spec_priv.spec_config.period = 0x12;
	priv->spec_priv.spec_config.fft_period = 0x02;
पूर्ण

अटल पूर्णांक ath9k_init_priv(काष्ठा ath9k_htc_priv *priv,
			   u16 devid, अक्षर *product,
			   u32 drv_info)
अणु
	काष्ठा ath_hw *ah = शून्य;
	काष्ठा ath_common *common;
	पूर्णांक i, ret = 0, csz = 0;

	ah = kzalloc(माप(काष्ठा ath_hw), GFP_KERNEL);
	अगर (!ah)
		वापस -ENOMEM;

	ah->dev = priv->dev;
	ah->hw = priv->hw;
	ah->hw_version.devid = devid;
	ah->hw_version.usbdev = drv_info;
	ah->ah_flags |= AH_USE_EEPROM;
	ah->reg_ops.पढ़ो = ath9k_regपढ़ो;
	ah->reg_ops.multi_पढ़ो = ath9k_multi_regपढ़ो;
	ah->reg_ops.ग_लिखो = ath9k_regग_लिखो;
	ah->reg_ops.enable_ग_लिखो_buffer = ath9k_enable_regग_लिखो_buffer;
	ah->reg_ops.ग_लिखो_flush = ath9k_regग_लिखो_flush;
	ah->reg_ops.enable_rmw_buffer = ath9k_enable_rmw_buffer;
	ah->reg_ops.rmw_flush = ath9k_reg_rmw_flush;
	ah->reg_ops.rmw = ath9k_reg_rmw;
	priv->ah = ah;

	common = ath9k_hw_common(ah);
	common->ops = &ah->reg_ops;
	common->ps_ops = &ath9k_htc_ps_ops;
	common->bus_ops = &ath9k_usb_bus_ops;
	common->ah = ah;
	common->hw = priv->hw;
	common->priv = priv;
	common->debug_mask = ath9k_debug;
	common->btcoex_enabled = ath9k_htc_btcoex_enable == 1;
	set_bit(ATH_OP_INVALID, &common->op_flags);

	spin_lock_init(&priv->beacon_lock);
	spin_lock_init(&priv->tx.tx_lock);
	mutex_init(&priv->mutex);
	mutex_init(&priv->htc_pm_lock);
	tasklet_setup(&priv->rx_tasklet, ath9k_rx_tasklet);
	tasklet_setup(&priv->tx_failed_tasklet, ath9k_tx_failed_tasklet);
	INIT_DELAYED_WORK(&priv->ani_work, ath9k_htc_ani_work);
	INIT_WORK(&priv->ps_work, ath9k_ps_work);
	INIT_WORK(&priv->fatal_work, ath9k_fatal_work);
	समयr_setup(&priv->tx.cleanup_समयr, ath9k_htc_tx_cleanup_समयr, 0);

	/*
	 * Cache line size is used to size and align various
	 * काष्ठाures used to communicate with the hardware.
	 */
	ath_पढ़ो_cachesize(common, &csz);
	common->cachelsz = csz << 2; /* convert to bytes */

	ret = ath9k_hw_init(ah);
	अगर (ret) अणु
		ath_err(common,
			"Unable to initialize hardware; initialization status: %d\n",
			ret);
		जाओ err_hw;
	पूर्ण

	ret = ath9k_init_queues(priv);
	अगर (ret)
		जाओ err_queues;

	क्रम (i = 0; i < ATH9K_HTC_MAX_BCN_VIF; i++)
		priv->beacon.bslot[i] = शून्य;
	priv->beacon.slotसमय = 9;

	ath9k_cmn_init_channels_rates(common);
	ath9k_cmn_init_crypto(ah);
	ath9k_init_misc(priv);
	ath9k_htc_init_btcoex(priv, product);

	वापस 0;

err_queues:
	ath9k_hw_deinit(ah);
err_hw:

	kमुक्त(ah);
	priv->ah = शून्य;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा ieee80211_अगरace_limit अगर_limits[] = अणु
	अणु .max = 2,	.types = BIT(NL80211_IFTYPE_STATION) |
				 BIT(NL80211_IFTYPE_P2P_CLIENT) पूर्ण,
	अणु .max = 2,	.types = BIT(NL80211_IFTYPE_AP) |
#अगर_घोषित CONFIG_MAC80211_MESH
				 BIT(NL80211_IFTYPE_MESH_POINT) |
#पूर्ण_अगर
				 BIT(NL80211_IFTYPE_P2P_GO) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_अगरace_combination अगर_comb = अणु
	.limits = अगर_limits,
	.n_limits = ARRAY_SIZE(अगर_limits),
	.max_पूर्णांकerfaces = 2,
	.num_dअगरferent_channels = 1,
पूर्ण;

अटल व्योम ath9k_set_hw_capab(काष्ठा ath9k_htc_priv *priv,
			       काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ath_hw *ah = priv->ah;
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	काष्ठा base_eep_header *pBase;

	ieee80211_hw_set(hw, HOST_BROADCAST_PS_BUFFERING);
	ieee80211_hw_set(hw, MFP_CAPABLE);
	ieee80211_hw_set(hw, REPORTS_TX_ACK_STATUS);
	ieee80211_hw_set(hw, PS_शून्यFUNC_STACK);
	ieee80211_hw_set(hw, RX_INCLUDES_FCS);
	ieee80211_hw_set(hw, HAS_RATE_CONTROL);
	ieee80211_hw_set(hw, SPECTRUM_MGMT);
	ieee80211_hw_set(hw, SIGNAL_DBM);
	ieee80211_hw_set(hw, AMPDU_AGGREGATION);
	ieee80211_hw_set(hw, DOESNT_SUPPORT_QOS_NDP);

	अगर (ath9k_ps_enable)
		ieee80211_hw_set(hw, SUPPORTS_PS);

	hw->wiphy->पूर्णांकerface_modes =
		BIT(NL80211_IFTYPE_STATION) |
		BIT(NL80211_IFTYPE_ADHOC) |
		BIT(NL80211_IFTYPE_AP) |
		BIT(NL80211_IFTYPE_P2P_GO) |
		BIT(NL80211_IFTYPE_P2P_CLIENT) |
		BIT(NL80211_IFTYPE_MESH_POINT) |
		BIT(NL80211_IFTYPE_OCB);

	hw->wiphy->अगरace_combinations = &अगर_comb;
	hw->wiphy->n_अगरace_combinations = 1;

	hw->wiphy->flags &= ~WIPHY_FLAG_PS_ON_BY_DEFAULT;

	hw->wiphy->flags |= WIPHY_FLAG_IBSS_RSN |
			    WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL |
			    WIPHY_FLAG_HAS_CHANNEL_SWITCH;

	hw->wiphy->flags |= WIPHY_FLAG_SUPPORTS_TDLS;

	hw->queues = 4;
	hw->max_listen_पूर्णांकerval = 1;

	hw->vअगर_data_size = माप(काष्ठा ath9k_htc_vअगर);
	hw->sta_data_size = माप(काष्ठा ath9k_htc_sta);

	/* tx_frame_hdr is larger than tx_mgmt_hdr anyway */
	hw->extra_tx_headroom = माप(काष्ठा tx_frame_hdr) +
		माप(काष्ठा htc_frame_hdr) + 4;

	अगर (priv->ah->caps.hw_caps & ATH9K_HW_CAP_2GHZ)
		hw->wiphy->bands[NL80211_BAND_2GHZ] =
			&common->sbands[NL80211_BAND_2GHZ];
	अगर (priv->ah->caps.hw_caps & ATH9K_HW_CAP_5GHZ)
		hw->wiphy->bands[NL80211_BAND_5GHZ] =
			&common->sbands[NL80211_BAND_5GHZ];

	ath9k_cmn_reload_chainmask(ah);

	pBase = ath9k_htc_get_eeprom_base(priv);
	अगर (pBase) अणु
		hw->wiphy->available_antennas_rx = pBase->rxMask;
		hw->wiphy->available_antennas_tx = pBase->txMask;
	पूर्ण

	SET_IEEE80211_PERM_ADDR(hw, common->macaddr);

	wiphy_ext_feature_set(hw->wiphy, NL80211_EXT_FEATURE_CQM_RSSI_LIST);
	wiphy_ext_feature_set(hw->wiphy,
			      NL80211_EXT_FEATURE_MULTICAST_REGISTRATIONS);
पूर्ण

अटल पूर्णांक ath9k_init_firmware_version(काष्ठा ath9k_htc_priv *priv)
अणु
	काष्ठा ieee80211_hw *hw = priv->hw;
	काष्ठा wmi_fw_version cmd_rsp;
	पूर्णांक ret;

	स_रखो(&cmd_rsp, 0, माप(cmd_rsp));

	WMI_CMD(WMI_GET_FW_VERSION);
	अगर (ret)
		वापस -EINVAL;

	priv->fw_version_major = be16_to_cpu(cmd_rsp.major);
	priv->fw_version_minor = be16_to_cpu(cmd_rsp.minor);

	snम_लिखो(hw->wiphy->fw_version, माप(hw->wiphy->fw_version), "%d.%d",
		 priv->fw_version_major,
		 priv->fw_version_minor);

	dev_info(priv->dev, "ath9k_htc: FW Version: %d.%d\n",
		 priv->fw_version_major,
		 priv->fw_version_minor);

	/*
	 * Check अगर the available FW matches the driver's
	 * required version.
	 */
	अगर (priv->fw_version_major != MAJOR_VERSION_REQ ||
	    priv->fw_version_minor < MINOR_VERSION_REQ) अणु
		dev_err(priv->dev, "ath9k_htc: Please upgrade to FW version %d.%d\n",
			MAJOR_VERSION_REQ, MINOR_VERSION_REQ);
		वापस -EINVAL;
	पूर्ण

	अगर (priv->fw_version_major == 1 && priv->fw_version_minor < 4)
		set_bit(HTC_FWFLAG_NO_RMW, &priv->fw_flags);

	dev_info(priv->dev, "FW RMW support: %s\n",
		test_bit(HTC_FWFLAG_NO_RMW, &priv->fw_flags) ? "Off" : "On");

	वापस 0;
पूर्ण

अटल पूर्णांक ath9k_init_device(काष्ठा ath9k_htc_priv *priv,
			     u16 devid, अक्षर *product, u32 drv_info)
अणु
	काष्ठा ieee80211_hw *hw = priv->hw;
	काष्ठा ath_common *common;
	काष्ठा ath_hw *ah;
	पूर्णांक error = 0;
	काष्ठा ath_regulatory *reg;
	अक्षर hw_name[64];

	/* Bring up device */
	error = ath9k_init_priv(priv, devid, product, drv_info);
	अगर (error != 0)
		जाओ err_init;

	ah = priv->ah;
	common = ath9k_hw_common(ah);
	ath9k_set_hw_capab(priv, hw);

	error = ath9k_init_firmware_version(priv);
	अगर (error != 0)
		जाओ err_fw;

	/* Initialize regulatory */
	error = ath_regd_init(&common->regulatory, priv->hw->wiphy,
			      ath9k_reg_notअगरier);
	अगर (error)
		जाओ err_regd;

	reg = &common->regulatory;

	/* Setup TX */
	error = ath9k_tx_init(priv);
	अगर (error != 0)
		जाओ err_tx;

	/* Setup RX */
	error = ath9k_rx_init(priv);
	अगर (error != 0)
		जाओ err_rx;

	ath9k_hw_disable(priv->ah);
#अगर_घोषित CONFIG_MAC80211_LEDS
	/* must be initialized beक्रमe ieee80211_रेजिस्टर_hw */
	priv->led_cdev.शेष_trigger = ieee80211_create_tpt_led_trigger(priv->hw,
		IEEE80211_TPT_LEDTRIG_FL_RADIO, ath9k_htc_tpt_blink,
		ARRAY_SIZE(ath9k_htc_tpt_blink));
#पूर्ण_अगर

	/* Register with mac80211 */
	error = ieee80211_रेजिस्टर_hw(hw);
	अगर (error)
		जाओ err_रेजिस्टर;

	/* Handle world regulatory */
	अगर (!ath_is_world_regd(reg)) अणु
		error = regulatory_hपूर्णांक(hw->wiphy, reg->alpha2);
		अगर (error)
			जाओ err_world;
	पूर्ण

	error = ath9k_htc_init_debug(priv->ah);
	अगर (error) अणु
		ath_err(common, "Unable to create debugfs files\n");
		जाओ err_world;
	पूर्ण

	ath_dbg(common, CONFIG,
		"WMI:%d, BCN:%d, CAB:%d, UAPSD:%d, MGMT:%d, BE:%d, BK:%d, VI:%d, VO:%d\n",
		priv->wmi_cmd_ep,
		priv->beacon_ep,
		priv->cab_ep,
		priv->uapsd_ep,
		priv->mgmt_ep,
		priv->data_be_ep,
		priv->data_bk_ep,
		priv->data_vi_ep,
		priv->data_vo_ep);

	ath9k_hw_name(priv->ah, hw_name, माप(hw_name));
	wiphy_info(hw->wiphy, "%s\n", hw_name);

	ath9k_init_leds(priv);
	ath9k_start_rfसमाप्त_poll(priv);

	वापस 0;

err_world:
	ieee80211_unरेजिस्टर_hw(hw);
err_रेजिस्टर:
	ath9k_rx_cleanup(priv);
err_rx:
	ath9k_tx_cleanup(priv);
err_tx:
	/* Nothing */
err_regd:
	/* Nothing */
err_fw:
	ath9k_deinit_priv(priv);
err_init:
	वापस error;
पूर्ण

पूर्णांक ath9k_htc_probe_device(काष्ठा htc_target *htc_handle, काष्ठा device *dev,
			   u16 devid, अक्षर *product, u32 drv_info)
अणु
	काष्ठा hअगर_device_usb *hअगर_dev;
	काष्ठा ath9k_htc_priv *priv;
	काष्ठा ieee80211_hw *hw;
	पूर्णांक ret;

	hw = ieee80211_alloc_hw(माप(काष्ठा ath9k_htc_priv), &ath9k_htc_ops);
	अगर (!hw)
		वापस -ENOMEM;

	priv = hw->priv;
	priv->hw = hw;
	priv->htc = htc_handle;
	priv->dev = dev;
	htc_handle->drv_priv = priv;
	SET_IEEE80211_DEV(hw, priv->dev);

	ret = ath9k_htc_रुको_क्रम_target(priv);
	अगर (ret)
		जाओ err_मुक्त;

	priv->wmi = ath9k_init_wmi(priv);
	अगर (!priv->wmi) अणु
		ret = -EINVAL;
		जाओ err_मुक्त;
	पूर्ण

	ret = ath9k_init_htc_services(priv, devid, drv_info);
	अगर (ret)
		जाओ err_init;

	ret = ath9k_init_device(priv, devid, product, drv_info);
	अगर (ret)
		जाओ err_init;

	वापस 0;

err_init:
	ath9k_stop_wmi(priv);
	hअगर_dev = (काष्ठा hअगर_device_usb *)htc_handle->hअगर_dev;
	ath9k_hअगर_usb_dealloc_urbs(hअगर_dev);
	ath9k_destroy_wmi(priv);
err_मुक्त:
	ieee80211_मुक्त_hw(hw);
	वापस ret;
पूर्ण

व्योम ath9k_htc_disconnect_device(काष्ठा htc_target *htc_handle, bool hotunplug)
अणु
	अगर (htc_handle->drv_priv) अणु

		/* Check अगर the device has been yanked out. */
		अगर (hotunplug)
			htc_handle->drv_priv->ah->ah_flags |= AH_UNPLUGGED;

		ath9k_deinit_device(htc_handle->drv_priv);
		ath9k_stop_wmi(htc_handle->drv_priv);
		ieee80211_मुक्त_hw(htc_handle->drv_priv->hw);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM

व्योम ath9k_htc_suspend(काष्ठा htc_target *htc_handle)
अणु
	ath9k_htc_setघातer(htc_handle->drv_priv, ATH9K_PM_FULL_SLEEP);
पूर्ण

पूर्णांक ath9k_htc_resume(काष्ठा htc_target *htc_handle)
अणु
	काष्ठा ath9k_htc_priv *priv = htc_handle->drv_priv;
	पूर्णांक ret;

	ret = ath9k_htc_रुको_क्रम_target(priv);
	अगर (ret)
		वापस ret;

	ret = ath9k_init_htc_services(priv, priv->ah->hw_version.devid,
				      priv->ah->hw_version.usbdev);
	ath9k_configure_leds(priv);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init ath9k_htc_init(व्योम)
अणु
	अगर (ath9k_hअगर_usb_init() < 0) अणु
		pr_err("No USB devices found, driver not installed\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण
module_init(ath9k_htc_init);

अटल व्योम __निकास ath9k_htc_निकास(व्योम)
अणु
	ath9k_hअगर_usb_निकास();
	pr_info("Driver unloaded\n");
पूर्ण
module_निकास(ath9k_htc_निकास);
