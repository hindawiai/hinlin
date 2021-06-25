<शैली गुरु>
/*
 * Copyright (c) 2008-2011 Atheros Communications Inc.
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

#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/ath9k_platक्रमm.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_net.h>
#समावेश <linux/relay.h>
#समावेश <linux/dmi.h>
#समावेश <net/ieee80211_radiotap.h>

#समावेश "ath9k.h"

काष्ठा ath9k_eeprom_ctx अणु
	काष्ठा completion complete;
	काष्ठा ath_hw *ah;
पूर्ण;

अटल अक्षर *dev_info = "ath9k";

MODULE_AUTHOR("Atheros Communications");
MODULE_DESCRIPTION("Support for Atheros 802.11n wireless LAN cards.");
MODULE_LICENSE("Dual BSD/GPL");

अटल अचिन्हित पूर्णांक ath9k_debug = ATH_DBG_DEFAULT;
module_param_named(debug, ath9k_debug, uपूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debugging mask");

पूर्णांक ath9k_modparam_nohwcrypt;
module_param_named(nohwcrypt, ath9k_modparam_nohwcrypt, पूर्णांक, 0444);
MODULE_PARM_DESC(nohwcrypt, "Disable hardware encryption");

पूर्णांक ath9k_led_blink;
module_param_named(blink, ath9k_led_blink, पूर्णांक, 0444);
MODULE_PARM_DESC(blink, "Enable LED blink on activity");

अटल पूर्णांक ath9k_led_active_high = -1;
module_param_named(led_active_high, ath9k_led_active_high, पूर्णांक, 0444);
MODULE_PARM_DESC(led_active_high, "Invert LED polarity");

अटल पूर्णांक ath9k_btcoex_enable;
module_param_named(btcoex_enable, ath9k_btcoex_enable, पूर्णांक, 0444);
MODULE_PARM_DESC(btcoex_enable, "Enable wifi-BT coexistence");

अटल पूर्णांक ath9k_bt_ant_भागersity;
module_param_named(bt_ant_भागersity, ath9k_bt_ant_भागersity, पूर्णांक, 0444);
MODULE_PARM_DESC(bt_ant_भागersity, "Enable WLAN/BT RX antenna diversity");

अटल पूर्णांक ath9k_ps_enable;
module_param_named(ps_enable, ath9k_ps_enable, पूर्णांक, 0444);
MODULE_PARM_DESC(ps_enable, "Enable WLAN PowerSave");

#अगर_घोषित CONFIG_ATH9K_CHANNEL_CONTEXT

पूर्णांक ath9k_use_chanctx;
module_param_named(use_chanctx, ath9k_use_chanctx, पूर्णांक, 0444);
MODULE_PARM_DESC(use_chanctx, "Enable channel context for concurrency");

#पूर्ण_अगर /* CONFIG_ATH9K_CHANNEL_CONTEXT */

पूर्णांक ath9k_use_msi;
module_param_named(use_msi, ath9k_use_msi, पूर्णांक, 0444);
MODULE_PARM_DESC(use_msi, "Use MSI instead of INTx if possible");

bool is_ath9k_unloaded;

#अगर_घोषित CONFIG_MAC80211_LEDS
अटल स्थिर काष्ठा ieee80211_tpt_blink ath9k_tpt_blink[] = अणु
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

अटल पूर्णांक __init set_use_msi(स्थिर काष्ठा dmi_प्रणाली_id *dmi)
अणु
	ath9k_use_msi = 1;
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id ath9k_quirks[] __initस्थिर = अणु
	अणु
		.callback = set_use_msi,
		.ident = "Dell Inspiron 24-3460",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 24-3460"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = set_use_msi,
		.ident = "Dell Vostro 3262",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Vostro 3262"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = set_use_msi,
		.ident = "Dell Inspiron 3472",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 3472"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = set_use_msi,
		.ident = "Dell Vostro 15-3572",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Vostro 15-3572"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = set_use_msi,
		.ident = "Dell Inspiron 14-3473",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Inspiron 14-3473"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम ath9k_deinit_softc(काष्ठा ath_softc *sc);

अटल व्योम ath9k_op_ps_wakeup(काष्ठा ath_common *common)
अणु
	ath9k_ps_wakeup((काष्ठा ath_softc *) common->priv);
पूर्ण

अटल व्योम ath9k_op_ps_restore(काष्ठा ath_common *common)
अणु
	ath9k_ps_restore((काष्ठा ath_softc *) common->priv);
पूर्ण

अटल स्थिर काष्ठा ath_ps_ops ath9k_ps_ops = अणु
	.wakeup = ath9k_op_ps_wakeup,
	.restore = ath9k_op_ps_restore,
पूर्ण;

/*
 * Read and ग_लिखो, they both share the same lock. We करो this to serialize
 * पढ़ोs and ग_लिखोs on Atheros 802.11n PCI devices only. This is required
 * as the FIFO on these devices can only accept sanely 2 requests.
 */

अटल व्योम ath9k_ioग_लिखो32(व्योम *hw_priv, u32 val, u32 reg_offset)
अणु
	काष्ठा ath_hw *ah = hw_priv;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath_softc *sc = (काष्ठा ath_softc *) common->priv;

	अगर (NR_CPUS > 1 && ah->config.serialize_regmode == SER_REG_MODE_ON) अणु
		अचिन्हित दीर्घ flags;
		spin_lock_irqsave(&sc->sc_serial_rw, flags);
		ioग_लिखो32(val, sc->mem + reg_offset);
		spin_unlock_irqrestore(&sc->sc_serial_rw, flags);
	पूर्ण अन्यथा
		ioग_लिखो32(val, sc->mem + reg_offset);
पूर्ण

अटल अचिन्हित पूर्णांक ath9k_ioपढ़ो32(व्योम *hw_priv, u32 reg_offset)
अणु
	काष्ठा ath_hw *ah = hw_priv;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath_softc *sc = (काष्ठा ath_softc *) common->priv;
	u32 val;

	अगर (NR_CPUS > 1 && ah->config.serialize_regmode == SER_REG_MODE_ON) अणु
		अचिन्हित दीर्घ flags;
		spin_lock_irqsave(&sc->sc_serial_rw, flags);
		val = ioपढ़ो32(sc->mem + reg_offset);
		spin_unlock_irqrestore(&sc->sc_serial_rw, flags);
	पूर्ण अन्यथा
		val = ioपढ़ो32(sc->mem + reg_offset);
	वापस val;
पूर्ण

अटल व्योम ath9k_multi_ioपढ़ो32(व्योम *hw_priv, u32 *addr,
                                u32 *val, u16 count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		val[i] = ath9k_ioपढ़ो32(hw_priv, addr[i]);
पूर्ण


अटल अचिन्हित पूर्णांक __ath9k_reg_rmw(काष्ठा ath_softc *sc, u32 reg_offset,
				    u32 set, u32 clr)
अणु
	u32 val;

	val = ioपढ़ो32(sc->mem + reg_offset);
	val &= ~clr;
	val |= set;
	ioग_लिखो32(val, sc->mem + reg_offset);

	वापस val;
पूर्ण

अटल अचिन्हित पूर्णांक ath9k_reg_rmw(व्योम *hw_priv, u32 reg_offset, u32 set, u32 clr)
अणु
	काष्ठा ath_hw *ah = hw_priv;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath_softc *sc = (काष्ठा ath_softc *) common->priv;
	अचिन्हित दीर्घ flags;
	u32 val;

	अगर (NR_CPUS > 1 && ah->config.serialize_regmode == SER_REG_MODE_ON) अणु
		spin_lock_irqsave(&sc->sc_serial_rw, flags);
		val = __ath9k_reg_rmw(sc, reg_offset, set, clr);
		spin_unlock_irqrestore(&sc->sc_serial_rw, flags);
	पूर्ण अन्यथा
		val = __ath9k_reg_rmw(sc, reg_offset, set, clr);

	वापस val;
पूर्ण

/**************************/
/*     Initialization     */
/**************************/

अटल व्योम ath9k_reg_notअगरier(काष्ठा wiphy *wiphy,
			       काष्ठा regulatory_request *request)
अणु
	काष्ठा ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_regulatory *reg = ath9k_hw_regulatory(ah);

	ath_reg_notअगरier_apply(wiphy, request, reg);

	/* synchronize DFS detector अगर regulatory करोमुख्य changed */
	अगर (sc->dfs_detector != शून्य)
		sc->dfs_detector->set_dfs_करोमुख्य(sc->dfs_detector,
						 request->dfs_region);

	/* Set tx घातer */
	अगर (!ah->curchan)
		वापस;

	sc->cur_chan->txघातer = 2 * ah->curchan->chan->max_घातer;
	ath9k_ps_wakeup(sc);
	ath9k_hw_set_txघातerlimit(ah, sc->cur_chan->txघातer, false);
	ath9k_cmn_update_txघात(ah, sc->cur_chan->cur_txघातer,
			       sc->cur_chan->txघातer,
			       &sc->cur_chan->cur_txघातer);
	ath9k_ps_restore(sc);
पूर्ण

/*
 *  This function will allocate both the DMA descriptor काष्ठाure, and the
 *  buffers it contains.  These are used to contain the descriptors used
 *  by the प्रणाली.
*/
पूर्णांक ath_descdma_setup(काष्ठा ath_softc *sc, काष्ठा ath_descdma *dd,
		      काष्ठा list_head *head, स्थिर अक्षर *name,
		      पूर्णांक nbuf, पूर्णांक ndesc, bool is_tx)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	u8 *ds;
	पूर्णांक i, bsize, desc_len;

	ath_dbg(common, CONFIG, "%s DMA: %u buffers %u desc/buf\n",
		name, nbuf, ndesc);

	INIT_LIST_HEAD(head);

	अगर (is_tx)
		desc_len = sc->sc_ah->caps.tx_desc_len;
	अन्यथा
		desc_len = माप(काष्ठा ath_desc);

	/* ath_desc must be a multiple of DWORDs */
	अगर ((desc_len % 4) != 0) अणु
		ath_err(common, "ath_desc not DWORD aligned\n");
		BUG_ON((desc_len % 4) != 0);
		वापस -ENOMEM;
	पूर्ण

	dd->dd_desc_len = desc_len * nbuf * ndesc;

	/*
	 * Need additional DMA memory because we can't use
	 * descriptors that cross the 4K page boundary. Assume
	 * one skipped descriptor per 4K page.
	 */
	अगर (!(sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_4KB_SPLITTRANS)) अणु
		u32 ndesc_skipped =
			ATH_DESC_4KB_BOUND_NUM_SKIPPED(dd->dd_desc_len);
		u32 dma_len;

		जबतक (ndesc_skipped) अणु
			dma_len = ndesc_skipped * desc_len;
			dd->dd_desc_len += dma_len;

			ndesc_skipped = ATH_DESC_4KB_BOUND_NUM_SKIPPED(dma_len);
		पूर्ण
	पूर्ण

	/* allocate descriptors */
	dd->dd_desc = dmam_alloc_coherent(sc->dev, dd->dd_desc_len,
					  &dd->dd_desc_paddr, GFP_KERNEL);
	अगर (!dd->dd_desc)
		वापस -ENOMEM;

	ds = dd->dd_desc;
	ath_dbg(common, CONFIG, "%s DMA map: %p (%u) -> %llx (%u)\n",
		name, ds, (u32) dd->dd_desc_len,
		ito64(dd->dd_desc_paddr), /*XXX*/(u32) dd->dd_desc_len);

	/* allocate buffers */
	अगर (is_tx) अणु
		काष्ठा ath_buf *bf;

		bsize = माप(काष्ठा ath_buf) * nbuf;
		bf = devm_kzalloc(sc->dev, bsize, GFP_KERNEL);
		अगर (!bf)
			वापस -ENOMEM;

		क्रम (i = 0; i < nbuf; i++, bf++, ds += (desc_len * ndesc)) अणु
			bf->bf_desc = ds;
			bf->bf_daddr = DS2PHYS(dd, ds);

			अगर (!(sc->sc_ah->caps.hw_caps &
				  ATH9K_HW_CAP_4KB_SPLITTRANS)) अणु
				/*
				 * Skip descriptor addresses which can cause 4KB
				 * boundary crossing (addr + length) with a 32 dword
				 * descriptor fetch.
				 */
				जबतक (ATH_DESC_4KB_BOUND_CHECK(bf->bf_daddr)) अणु
					BUG_ON((caddr_t) bf->bf_desc >=
						   ((caddr_t) dd->dd_desc +
						dd->dd_desc_len));

					ds += (desc_len * ndesc);
					bf->bf_desc = ds;
					bf->bf_daddr = DS2PHYS(dd, ds);
				पूर्ण
			पूर्ण
			list_add_tail(&bf->list, head);
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा ath_rxbuf *bf;

		bsize = माप(काष्ठा ath_rxbuf) * nbuf;
		bf = devm_kzalloc(sc->dev, bsize, GFP_KERNEL);
		अगर (!bf)
			वापस -ENOMEM;

		क्रम (i = 0; i < nbuf; i++, bf++, ds += (desc_len * ndesc)) अणु
			bf->bf_desc = ds;
			bf->bf_daddr = DS2PHYS(dd, ds);

			अगर (!(sc->sc_ah->caps.hw_caps &
				  ATH9K_HW_CAP_4KB_SPLITTRANS)) अणु
				/*
				 * Skip descriptor addresses which can cause 4KB
				 * boundary crossing (addr + length) with a 32 dword
				 * descriptor fetch.
				 */
				जबतक (ATH_DESC_4KB_BOUND_CHECK(bf->bf_daddr)) अणु
					BUG_ON((caddr_t) bf->bf_desc >=
						   ((caddr_t) dd->dd_desc +
						dd->dd_desc_len));

					ds += (desc_len * ndesc);
					bf->bf_desc = ds;
					bf->bf_daddr = DS2PHYS(dd, ds);
				पूर्ण
			पूर्ण
			list_add_tail(&bf->list, head);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ath9k_init_queues(काष्ठा ath_softc *sc)
अणु
	पूर्णांक i = 0;

	sc->beacon.beaconq = ath9k_hw_beaconq_setup(sc->sc_ah);
	sc->beacon.cabq = ath_txq_setup(sc, ATH9K_TX_QUEUE_CAB, 0);
	ath_cabq_update(sc);

	sc->tx.uapsdq = ath_txq_setup(sc, ATH9K_TX_QUEUE_UAPSD, 0);

	क्रम (i = 0; i < IEEE80211_NUM_ACS; i++) अणु
		sc->tx.txq_map[i] = ath_txq_setup(sc, ATH9K_TX_QUEUE_DATA, i);
		sc->tx.txq_map[i]->mac80211_qnum = i;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ath9k_init_misc(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	पूर्णांक i = 0;

	समयr_setup(&common->ani.समयr, ath_ani_calibrate, 0);

	common->last_rssi = ATH_RSSI_DUMMY_MARKER;
	eth_broadcast_addr(common->bssidmask);
	sc->beacon.slotसमय = 9;

	क्रम (i = 0; i < ARRAY_SIZE(sc->beacon.bslot); i++)
		sc->beacon.bslot[i] = शून्य;

	अगर (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_ANT_DIV_COMB)
		sc->ant_comb.count = ATH_ANT_DIV_COMB_INIT_COUNT;

	sc->spec_priv.ah = sc->sc_ah;
	sc->spec_priv.spec_config.enabled = 0;
	sc->spec_priv.spec_config.लघु_repeat = true;
	sc->spec_priv.spec_config.count = 8;
	sc->spec_priv.spec_config.endless = false;
	sc->spec_priv.spec_config.period = 0xFF;
	sc->spec_priv.spec_config.fft_period = 0xF;
पूर्ण

अटल व्योम ath9k_init_pcoem_platक्रमm(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath9k_hw_capabilities *pCap = &ah->caps;
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	अगर (!IS_ENABLED(CONFIG_ATH9K_PCOEM))
		वापस;

	अगर (common->bus_ops->ath_bus_type != ATH_PCI)
		वापस;

	अगर (sc->driver_data & (ATH9K_PCI_CUS198 |
			       ATH9K_PCI_CUS230)) अणु
		ah->config.xlna_gpio = 9;
		ah->config.xatten_margin_cfg = true;
		ah->config.alt_mingainidx = true;
		ah->config.ant_ctrl_comm2g_चयन_enable = 0x000BBB88;
		sc->ant_comb.low_rssi_thresh = 20;
		sc->ant_comb.fast_भाग_bias = 3;

		ath_info(common, "Set parameters for %s\n",
			 (sc->driver_data & ATH9K_PCI_CUS198) ?
			 "CUS198" : "CUS230");
	पूर्ण

	अगर (sc->driver_data & ATH9K_PCI_CUS217)
		ath_info(common, "CUS217 card detected\n");

	अगर (sc->driver_data & ATH9K_PCI_CUS252)
		ath_info(common, "CUS252 card detected\n");

	अगर (sc->driver_data & ATH9K_PCI_AR9565_1ANT)
		ath_info(common, "WB335 1-ANT card detected\n");

	अगर (sc->driver_data & ATH9K_PCI_AR9565_2ANT)
		ath_info(common, "WB335 2-ANT card detected\n");

	अगर (sc->driver_data & ATH9K_PCI_KILLER)
		ath_info(common, "Killer Wireless card detected\n");

	/*
	 * Some WB335 cards करो not support antenna भागersity. Since
	 * we use a hardcoded value क्रम AR9565 instead of using the
	 * EEPROM/OTP data, हटाओ the combining feature from
	 * the HW capabilities biपंचांगap.
	 */
	अगर (sc->driver_data & (ATH9K_PCI_AR9565_1ANT | ATH9K_PCI_AR9565_2ANT)) अणु
		अगर (!(sc->driver_data & ATH9K_PCI_BT_ANT_DIV))
			pCap->hw_caps &= ~ATH9K_HW_CAP_ANT_DIV_COMB;
	पूर्ण

	अगर (sc->driver_data & ATH9K_PCI_BT_ANT_DIV) अणु
		pCap->hw_caps |= ATH9K_HW_CAP_BT_ANT_DIV;
		ath_info(common, "Set BT/WLAN RX diversity capability\n");
	पूर्ण

	अगर (sc->driver_data & ATH9K_PCI_D3_L1_WAR) अणु
		ah->config.pcie_waen = 0x0040473b;
		ath_info(common, "Enable WAR for ASPM D3/L1\n");
	पूर्ण

	/*
	 * The शेष value of pll_pwrsave is 1.
	 * For certain AR9485 cards, it is set to 0.
	 * For AR9462, AR9565 it's set to 7.
	 */
	ah->config.pll_pwrsave = 1;

	अगर (sc->driver_data & ATH9K_PCI_NO_PLL_PWRSAVE) अणु
		ah->config.pll_pwrsave = 0;
		ath_info(common, "Disable PLL PowerSave\n");
	पूर्ण

	अगर (sc->driver_data & ATH9K_PCI_LED_ACT_HI)
		ah->config.led_active_high = true;
पूर्ण

अटल व्योम ath9k_eeprom_request_cb(स्थिर काष्ठा firmware *eeprom_blob,
				    व्योम *ctx)
अणु
	काष्ठा ath9k_eeprom_ctx *ec = ctx;

	अगर (eeprom_blob)
		ec->ah->eeprom_blob = eeprom_blob;

	complete(&ec->complete);
पूर्ण

अटल पूर्णांक ath9k_eeprom_request(काष्ठा ath_softc *sc, स्थिर अक्षर *name)
अणु
	काष्ठा ath9k_eeprom_ctx ec;
	काष्ठा ath_hw *ah = sc->sc_ah;
	पूर्णांक err;

	/* try to load the EEPROM content asynchronously */
	init_completion(&ec.complete);
	ec.ah = sc->sc_ah;

	err = request_firmware_noरुको(THIS_MODULE, 1, name, sc->dev, GFP_KERNEL,
				      &ec, ath9k_eeprom_request_cb);
	अगर (err < 0) अणु
		ath_err(ath9k_hw_common(ah),
			"EEPROM request failed\n");
		वापस err;
	पूर्ण

	रुको_क्रम_completion(&ec.complete);

	अगर (!ah->eeprom_blob) अणु
		ath_err(ath9k_hw_common(ah),
			"Unable to load EEPROM file %s\n", name);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ath9k_eeprom_release(काष्ठा ath_softc *sc)
अणु
	release_firmware(sc->sc_ah->eeprom_blob);
पूर्ण

अटल पूर्णांक ath9k_init_platक्रमm(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath9k_platक्रमm_data *pdata = sc->dev->platक्रमm_data;
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	पूर्णांक ret;

	अगर (!pdata)
		वापस 0;

	अगर (!pdata->use_eeprom) अणु
		ah->ah_flags &= ~AH_USE_EEPROM;
		ah->gpio_mask = pdata->gpio_mask;
		ah->gpio_val = pdata->gpio_val;
		ah->led_pin = pdata->led_pin;
		ah->is_clk_25mhz = pdata->is_clk_25mhz;
		ah->get_mac_revision = pdata->get_mac_revision;
		ah->बाह्यal_reset = pdata->बाह्यal_reset;
		ah->disable_2ghz = pdata->disable_2ghz;
		ah->disable_5ghz = pdata->disable_5ghz;

		अगर (!pdata->endian_check)
			ah->ah_flags |= AH_NO_EEP_SWAP;
	पूर्ण

	अगर (pdata->eeprom_name) अणु
		ret = ath9k_eeprom_request(sc, pdata->eeprom_name);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (pdata->led_active_high)
		ah->config.led_active_high = true;

	अगर (pdata->tx_gain_buffalo)
		ah->config.tx_gain_buffalo = true;

	अगर (pdata->macaddr)
		ether_addr_copy(common->macaddr, pdata->macaddr);

	वापस 0;
पूर्ण

अटल पूर्णांक ath9k_of_init(काष्ठा ath_softc *sc)
अणु
	काष्ठा device_node *np = sc->dev->of_node;
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	क्रमागत ath_bus_type bus_type = common->bus_ops->ath_bus_type;
	अक्षर eeprom_name[100];
	पूर्णांक ret;

	अगर (!of_device_is_available(np))
		वापस 0;

	ath_dbg(common, CONFIG, "parsing configuration from OF node\n");

	अगर (of_property_पढ़ो_bool(np, "qca,no-eeprom")) अणु
		/* ath9k-eeprom-<bus>-<id>.bin */
		scnम_लिखो(eeprom_name, माप(eeprom_name),
			  "ath9k-eeprom-%s-%s.bin",
			  ath_bus_type_to_string(bus_type), dev_name(ah->dev));

		ret = ath9k_eeprom_request(sc, eeprom_name);
		अगर (ret)
			वापस ret;

		ah->ah_flags &= ~AH_USE_EEPROM;
		ah->ah_flags |= AH_NO_EEP_SWAP;
	पूर्ण

	of_get_mac_address(np, common->macaddr);

	वापस 0;
पूर्ण

अटल पूर्णांक ath9k_init_softc(u16 devid, काष्ठा ath_softc *sc,
			    स्थिर काष्ठा ath_bus_ops *bus_ops)
अणु
	काष्ठा ath_hw *ah = शून्य;
	काष्ठा ath9k_hw_capabilities *pCap;
	काष्ठा ath_common *common;
	पूर्णांक ret = 0, i;
	पूर्णांक csz = 0;

	ah = devm_kzalloc(sc->dev, माप(काष्ठा ath_hw), GFP_KERNEL);
	अगर (!ah)
		वापस -ENOMEM;

	ah->dev = sc->dev;
	ah->hw = sc->hw;
	ah->hw_version.devid = devid;
	ah->ah_flags |= AH_USE_EEPROM;
	ah->led_pin = -1;
	ah->reg_ops.पढ़ो = ath9k_ioपढ़ो32;
	ah->reg_ops.multi_पढ़ो = ath9k_multi_ioपढ़ो32;
	ah->reg_ops.ग_लिखो = ath9k_ioग_लिखो32;
	ah->reg_ops.rmw = ath9k_reg_rmw;
	pCap = &ah->caps;

	common = ath9k_hw_common(ah);

	/* Will be cleared in ath9k_start() */
	set_bit(ATH_OP_INVALID, &common->op_flags);

	sc->sc_ah = ah;
	sc->dfs_detector = dfs_pattern_detector_init(common, NL80211_DFS_UNSET);
	sc->tx99_घातer = MAX_RATE_POWER + 1;
	init_रुकोqueue_head(&sc->tx_रुको);
	sc->cur_chan = &sc->chanctx[0];
	अगर (!ath9k_is_chanctx_enabled())
		sc->cur_chan->hw_queue_base = 0;

	common->ops = &ah->reg_ops;
	common->bus_ops = bus_ops;
	common->ps_ops = &ath9k_ps_ops;
	common->ah = ah;
	common->hw = sc->hw;
	common->priv = sc;
	common->debug_mask = ath9k_debug;
	common->btcoex_enabled = ath9k_btcoex_enable == 1;
	common->disable_ani = false;

	/*
	 * Platक्रमm quirks.
	 */
	ath9k_init_pcoem_platक्रमm(sc);

	ret = ath9k_init_platक्रमm(sc);
	अगर (ret)
		वापस ret;

	ret = ath9k_of_init(sc);
	अगर (ret)
		वापस ret;

	अगर (ath9k_led_active_high != -1)
		ah->config.led_active_high = ath9k_led_active_high == 1;

	/*
	 * Enable WLAN/BT RX Antenna भागersity only when:
	 *
	 * - BTCOEX is disabled.
	 * - the user manually requests the feature.
	 * - the HW cap is set using the platक्रमm data.
	 */
	अगर (!common->btcoex_enabled && ath9k_bt_ant_भागersity &&
	    (pCap->hw_caps & ATH9K_HW_CAP_BT_ANT_DIV))
		common->bt_ant_भागersity = 1;

	spin_lock_init(&common->cc_lock);
	spin_lock_init(&sc->पूर्णांकr_lock);
	spin_lock_init(&sc->sc_serial_rw);
	spin_lock_init(&sc->sc_pm_lock);
	spin_lock_init(&sc->chan_lock);
	mutex_init(&sc->mutex);
	tasklet_setup(&sc->पूर्णांकr_tq, ath9k_tasklet);
	tasklet_setup(&sc->bcon_tasklet, ath9k_beacon_tasklet);

	समयr_setup(&sc->sleep_समयr, ath_ps_full_sleep, 0);
	INIT_WORK(&sc->hw_reset_work, ath_reset_work);
	INIT_WORK(&sc->paprd_work, ath_paprd_calibrate);
	INIT_DELAYED_WORK(&sc->hw_pll_work, ath_hw_pll_work);
	INIT_DELAYED_WORK(&sc->hw_check_work, ath_hw_check_work);

	ath9k_init_channel_context(sc);

	/*
	 * Cache line size is used to size and align various
	 * काष्ठाures used to communicate with the hardware.
	 */
	ath_पढ़ो_cachesize(common, &csz);
	common->cachelsz = csz << 2; /* convert to bytes */

	/* Initializes the hardware क्रम all supported chipsets */
	ret = ath9k_hw_init(ah);
	अगर (ret)
		जाओ err_hw;

	ret = ath9k_init_queues(sc);
	अगर (ret)
		जाओ err_queues;

	ret =  ath9k_init_btcoex(sc);
	अगर (ret)
		जाओ err_btcoex;

	ret = ath9k_cmn_init_channels_rates(common);
	अगर (ret)
		जाओ err_btcoex;

	ret = ath9k_init_p2p(sc);
	अगर (ret)
		जाओ err_btcoex;

	ath9k_cmn_init_crypto(sc->sc_ah);
	ath9k_init_misc(sc);
	ath_chanctx_init(sc);
	ath9k_offchannel_init(sc);

	अगर (common->bus_ops->aspm_init)
		common->bus_ops->aspm_init(common);

	वापस 0;

err_btcoex:
	क्रम (i = 0; i < ATH9K_NUM_TX_QUEUES; i++)
		अगर (ATH_TXQ_SETUP(sc, i))
			ath_tx_cleanupq(sc, &sc->tx.txq[i]);
err_queues:
	ath9k_hw_deinit(ah);
err_hw:
	ath9k_eeprom_release(sc);
	dev_kमुक्त_skb_any(sc->tx99_skb);
	वापस ret;
पूर्ण

अटल व्योम ath9k_init_band_txघातer(काष्ठा ath_softc *sc, पूर्णांक band)
अणु
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_channel *chan;
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा cfg80211_chan_def chandef;
	पूर्णांक i;

	sband = &common->sbands[band];
	क्रम (i = 0; i < sband->n_channels; i++) अणु
		chan = &sband->channels[i];
		ah->curchan = &ah->channels[chan->hw_value];
		cfg80211_chandef_create(&chandef, chan, NL80211_CHAN_HT20);
		ath9k_cmn_get_channel(sc->hw, ah, &chandef);
		ath9k_hw_set_txघातerlimit(ah, MAX_COMBINED_POWER, true);
	पूर्ण
पूर्ण

अटल व्योम ath9k_init_txघातer_limits(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath9k_channel *curchan = ah->curchan;

	अगर (ah->caps.hw_caps & ATH9K_HW_CAP_2GHZ)
		ath9k_init_band_txघातer(sc, NL80211_BAND_2GHZ);
	अगर (ah->caps.hw_caps & ATH9K_HW_CAP_5GHZ)
		ath9k_init_band_txघातer(sc, NL80211_BAND_5GHZ);

	ah->curchan = curchan;
पूर्ण

अटल स्थिर काष्ठा ieee80211_अगरace_limit अगर_limits[] = अणु
	अणु .max = 2048,	.types = BIT(NL80211_IFTYPE_STATION) पूर्ण,
	अणु .max = 8,	.types =
#अगर_घोषित CONFIG_MAC80211_MESH
				 BIT(NL80211_IFTYPE_MESH_POINT) |
#पूर्ण_अगर
				 BIT(NL80211_IFTYPE_AP) पूर्ण,
	अणु .max = 1,	.types = BIT(NL80211_IFTYPE_P2P_CLIENT) |
				 BIT(NL80211_IFTYPE_P2P_GO) पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_ATH9K_CHANNEL_CONTEXT

अटल स्थिर काष्ठा ieee80211_अगरace_limit अगर_limits_multi[] = अणु
	अणु .max = 2,	.types = BIT(NL80211_IFTYPE_STATION) |
				 BIT(NL80211_IFTYPE_AP) |
				 BIT(NL80211_IFTYPE_P2P_CLIENT) |
				 BIT(NL80211_IFTYPE_P2P_GO) पूर्ण,
	अणु .max = 1,	.types = BIT(NL80211_IFTYPE_ADHOC) पूर्ण,
	अणु .max = 1,	.types = BIT(NL80211_IFTYPE_P2P_DEVICE) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_अगरace_combination अगर_comb_multi[] = अणु
	अणु
		.limits = अगर_limits_multi,
		.n_limits = ARRAY_SIZE(अगर_limits_multi),
		.max_पूर्णांकerfaces = 3,
		.num_dअगरferent_channels = 2,
		.beacon_पूर्णांक_infra_match = true,
	पूर्ण,
पूर्ण;

#पूर्ण_अगर /* CONFIG_ATH9K_CHANNEL_CONTEXT */

अटल स्थिर काष्ठा ieee80211_अगरace_combination अगर_comb[] = अणु
	अणु
		.limits = अगर_limits,
		.n_limits = ARRAY_SIZE(अगर_limits),
		.max_पूर्णांकerfaces = 2048,
		.num_dअगरferent_channels = 1,
		.beacon_पूर्णांक_infra_match = true,
#अगर_घोषित CONFIG_ATH9K_DFS_CERTIFIED
		.radar_detect_widths =	BIT(NL80211_CHAN_WIDTH_20_NOHT) |
					BIT(NL80211_CHAN_WIDTH_20) |
					BIT(NL80211_CHAN_WIDTH_40),
#पूर्ण_अगर
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_ATH9K_CHANNEL_CONTEXT
अटल व्योम ath9k_set_mcc_capab(काष्ठा ath_softc *sc, काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	अगर (!ath9k_is_chanctx_enabled())
		वापस;

	ieee80211_hw_set(hw, QUEUE_CONTROL);
	hw->queues = ATH9K_NUM_TX_QUEUES;
	hw->offchannel_tx_hw_queue = hw->queues - 1;
	hw->wiphy->अगरace_combinations = अगर_comb_multi;
	hw->wiphy->n_अगरace_combinations = ARRAY_SIZE(अगर_comb_multi);
	hw->wiphy->max_scan_ssids = 255;
	hw->wiphy->max_scan_ie_len = IEEE80211_MAX_DATA_LEN;
	hw->wiphy->max_reमुख्य_on_channel_duration = 10000;
	hw->chanctx_data_size = माप(व्योम *);
	hw->extra_beacon_tailroom =
		माप(काष्ठा ieee80211_p2p_noa_attr) + 9;

	ath_dbg(common, CHAN_CTX, "Use channel contexts\n");
पूर्ण
#पूर्ण_अगर /* CONFIG_ATH9K_CHANNEL_CONTEXT */

अटल व्योम ath9k_set_hw_capab(काष्ठा ath_softc *sc, काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	ieee80211_hw_set(hw, SUPPORTS_HT_CCK_RATES);
	ieee80211_hw_set(hw, SUPPORTS_RC_TABLE);
	ieee80211_hw_set(hw, REPORTS_TX_ACK_STATUS);
	ieee80211_hw_set(hw, SPECTRUM_MGMT);
	ieee80211_hw_set(hw, PS_शून्यFUNC_STACK);
	ieee80211_hw_set(hw, SIGNAL_DBM);
	ieee80211_hw_set(hw, RX_INCLUDES_FCS);
	ieee80211_hw_set(hw, HOST_BROADCAST_PS_BUFFERING);
	ieee80211_hw_set(hw, SUPPORT_FAST_XMIT);
	ieee80211_hw_set(hw, SUPPORTS_CLONED_SKBS);

	अगर (ath9k_ps_enable)
		ieee80211_hw_set(hw, SUPPORTS_PS);

	अगर (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_HT) अणु
		ieee80211_hw_set(hw, AMPDU_AGGREGATION);

		अगर (AR_SREV_9280_20_OR_LATER(ah))
			hw->radiotap_mcs_details |=
				IEEE80211_RADIOTAP_MCS_HAVE_STBC;
	पूर्ण

	अगर (AR_SREV_9160_10_OR_LATER(sc->sc_ah) || ath9k_modparam_nohwcrypt)
		ieee80211_hw_set(hw, MFP_CAPABLE);

	hw->wiphy->features |= NL80211_FEATURE_ACTIVE_MONITOR |
			       NL80211_FEATURE_AP_MODE_CHAN_WIDTH_CHANGE |
			       NL80211_FEATURE_P2P_GO_CTWIN;

	अगर (!IS_ENABLED(CONFIG_ATH9K_TX99)) अणु
		hw->wiphy->पूर्णांकerface_modes =
			BIT(NL80211_IFTYPE_P2P_GO) |
			BIT(NL80211_IFTYPE_P2P_CLIENT) |
			BIT(NL80211_IFTYPE_AP) |
			BIT(NL80211_IFTYPE_STATION) |
			BIT(NL80211_IFTYPE_ADHOC) |
			BIT(NL80211_IFTYPE_MESH_POINT) |
			BIT(NL80211_IFTYPE_OCB);

		अगर (ath9k_is_chanctx_enabled())
			hw->wiphy->पूर्णांकerface_modes |=
					BIT(NL80211_IFTYPE_P2P_DEVICE);

		hw->wiphy->अगरace_combinations = अगर_comb;
		hw->wiphy->n_अगरace_combinations = ARRAY_SIZE(अगर_comb);
	पूर्ण

	hw->wiphy->flags &= ~WIPHY_FLAG_PS_ON_BY_DEFAULT;

	hw->wiphy->flags |= WIPHY_FLAG_IBSS_RSN;
	hw->wiphy->flags |= WIPHY_FLAG_SUPPORTS_TDLS;
	hw->wiphy->flags |= WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL;
	hw->wiphy->flags |= WIPHY_FLAG_SUPPORTS_5_10_MHZ;
	hw->wiphy->flags |= WIPHY_FLAG_HAS_CHANNEL_SWITCH;
	hw->wiphy->flags |= WIPHY_FLAG_AP_UAPSD;

	hw->queues = 4;
	hw->max_rates = 4;
	hw->max_listen_पूर्णांकerval = 10;
	hw->max_rate_tries = 10;
	hw->sta_data_size = माप(काष्ठा ath_node);
	hw->vअगर_data_size = माप(काष्ठा ath_vअगर);
	hw->txq_data_size = माप(काष्ठा ath_atx_tid);
	hw->extra_tx_headroom = 4;

	hw->wiphy->available_antennas_rx = BIT(ah->caps.max_rxchains) - 1;
	hw->wiphy->available_antennas_tx = BIT(ah->caps.max_txchains) - 1;

	/* single chain devices with rx भागersity */
	अगर (ah->caps.hw_caps & ATH9K_HW_CAP_ANT_DIV_COMB)
		hw->wiphy->available_antennas_rx = BIT(0) | BIT(1);

	sc->ant_rx = hw->wiphy->available_antennas_rx;
	sc->ant_tx = hw->wiphy->available_antennas_tx;

	अगर (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_2GHZ)
		hw->wiphy->bands[NL80211_BAND_2GHZ] =
			&common->sbands[NL80211_BAND_2GHZ];
	अगर (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_5GHZ)
		hw->wiphy->bands[NL80211_BAND_5GHZ] =
			&common->sbands[NL80211_BAND_5GHZ];

#अगर_घोषित CONFIG_ATH9K_CHANNEL_CONTEXT
	ath9k_set_mcc_capab(sc, hw);
#पूर्ण_अगर
	ath9k_init_wow(hw);
	ath9k_cmn_reload_chainmask(ah);

	SET_IEEE80211_PERM_ADDR(hw, common->macaddr);

	wiphy_ext_feature_set(hw->wiphy, NL80211_EXT_FEATURE_CQM_RSSI_LIST);
	wiphy_ext_feature_set(hw->wiphy, NL80211_EXT_FEATURE_AIRTIME_FAIRNESS);
	wiphy_ext_feature_set(hw->wiphy,
			      NL80211_EXT_FEATURE_MULTICAST_REGISTRATIONS);
	wiphy_ext_feature_set(hw->wiphy, NL80211_EXT_FEATURE_CAN_REPLACE_PTK0);
पूर्ण

पूर्णांक ath9k_init_device(u16 devid, काष्ठा ath_softc *sc,
		    स्थिर काष्ठा ath_bus_ops *bus_ops)
अणु
	काष्ठा ieee80211_hw *hw = sc->hw;
	काष्ठा ath_common *common;
	काष्ठा ath_hw *ah;
	पूर्णांक error = 0;
	काष्ठा ath_regulatory *reg;

	/* Bring up device */
	error = ath9k_init_softc(devid, sc, bus_ops);
	अगर (error)
		वापस error;

	ah = sc->sc_ah;
	common = ath9k_hw_common(ah);
	ath9k_set_hw_capab(sc, hw);

	/* Initialize regulatory */
	error = ath_regd_init(&common->regulatory, sc->hw->wiphy,
			      ath9k_reg_notअगरier);
	अगर (error)
		जाओ deinit;

	reg = &common->regulatory;

	/* Setup TX DMA */
	error = ath_tx_init(sc, ATH_TXBUF);
	अगर (error != 0)
		जाओ deinit;

	/* Setup RX DMA */
	error = ath_rx_init(sc, ATH_RXBUF);
	अगर (error != 0)
		जाओ deinit;

	ath9k_init_txघातer_limits(sc);

#अगर_घोषित CONFIG_MAC80211_LEDS
	/* must be initialized beक्रमe ieee80211_रेजिस्टर_hw */
	sc->led_cdev.शेष_trigger = ieee80211_create_tpt_led_trigger(sc->hw,
		IEEE80211_TPT_LEDTRIG_FL_RADIO, ath9k_tpt_blink,
		ARRAY_SIZE(ath9k_tpt_blink));
#पूर्ण_अगर

	/* Register with mac80211 */
	error = ieee80211_रेजिस्टर_hw(hw);
	अगर (error)
		जाओ rx_cleanup;

	error = ath9k_init_debug(ah);
	अगर (error) अणु
		ath_err(common, "Unable to create debugfs files\n");
		जाओ unरेजिस्टर;
	पूर्ण

	/* Handle world regulatory */
	अगर (!ath_is_world_regd(reg)) अणु
		error = regulatory_hपूर्णांक(hw->wiphy, reg->alpha2);
		अगर (error)
			जाओ debug_cleanup;
	पूर्ण

	ath_init_leds(sc);
	ath_start_rfसमाप्त_poll(sc);

	वापस 0;

debug_cleanup:
	ath9k_deinit_debug(sc);
unरेजिस्टर:
	ieee80211_unरेजिस्टर_hw(hw);
rx_cleanup:
	ath_rx_cleanup(sc);
deinit:
	ath9k_deinit_softc(sc);
	वापस error;
पूर्ण

/*****************************/
/*     De-Initialization     */
/*****************************/

अटल व्योम ath9k_deinit_softc(काष्ठा ath_softc *sc)
अणु
	पूर्णांक i = 0;

	ath9k_deinit_p2p(sc);
	ath9k_deinit_btcoex(sc);

	क्रम (i = 0; i < ATH9K_NUM_TX_QUEUES; i++)
		अगर (ATH_TXQ_SETUP(sc, i))
			ath_tx_cleanupq(sc, &sc->tx.txq[i]);

	del_समयr_sync(&sc->sleep_समयr);
	ath9k_hw_deinit(sc->sc_ah);
	अगर (sc->dfs_detector != शून्य)
		sc->dfs_detector->निकास(sc->dfs_detector);

	ath9k_eeprom_release(sc);
पूर्ण

व्योम ath9k_deinit_device(काष्ठा ath_softc *sc)
अणु
	काष्ठा ieee80211_hw *hw = sc->hw;

	ath9k_ps_wakeup(sc);

	wiphy_rfसमाप्त_stop_polling(sc->hw->wiphy);
	ath_deinit_leds(sc);

	ath9k_ps_restore(sc);

	ath9k_deinit_debug(sc);
	ath9k_deinit_wow(hw);
	ieee80211_unरेजिस्टर_hw(hw);
	ath_rx_cleanup(sc);
	ath9k_deinit_softc(sc);
पूर्ण

/************************/
/*     Module Hooks     */
/************************/

अटल पूर्णांक __init ath9k_init(व्योम)
अणु
	पूर्णांक error;

	error = ath_pci_init();
	अगर (error < 0) अणु
		pr_err("No PCI devices found, driver not installed\n");
		error = -ENODEV;
		जाओ err_out;
	पूर्ण

	error = ath_ahb_init();
	अगर (error < 0) अणु
		error = -ENODEV;
		जाओ err_pci_निकास;
	पूर्ण

	dmi_check_प्रणाली(ath9k_quirks);

	वापस 0;

 err_pci_निकास:
	ath_pci_निकास();
 err_out:
	वापस error;
पूर्ण
module_init(ath9k_init);

अटल व्योम __निकास ath9k_निकास(व्योम)
अणु
	is_ath9k_unloaded = true;
	ath_ahb_निकास();
	ath_pci_निकास();
	pr_info("%s: Driver unloaded\n", dev_info);
पूर्ण
module_निकास(ath9k_निकास);
