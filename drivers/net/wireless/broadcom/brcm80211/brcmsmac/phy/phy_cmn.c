<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2010 Broadcom Corporation
 */
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/bitops.h>

#समावेश <brcm_hw_ids.h>
#समावेश <chipcommon.h>
#समावेश <aiutils.h>
#समावेश <d11.h>
#समावेश <phy_shim.h>
#समावेश "phy_hal.h"
#समावेश "phy_int.h"
#समावेश "phy_radio.h"
#समावेश "phy_lcn.h"
#समावेश "phyreg_n.h"

#घोषणा VALID_N_RADIO(radioid) ((radioid == BCM2055_ID) || \
				 (radioid == BCM2056_ID) || \
				 (radioid == BCM2057_ID))

#घोषणा VALID_LCN_RADIO(radioid)	(radioid == BCM2064_ID)

#घोषणा VALID_RADIO(pi, radioid)        ( \
		(ISNPHY(pi) ? VALID_N_RADIO(radioid) : false) || \
		(ISLCNPHY(pi) ? VALID_LCN_RADIO(radioid) : false))

/* basic mux operation - can be optimized on several architectures */
#घोषणा MUX(pred, true, false) ((pred) ? (true) : (false))

/* modulo inc/dec - assumes x E [0, bound - 1] */
#घोषणा MODINC(x, bound) MUX((x) == (bound) - 1, 0, (x) + 1)

/* modulo inc/dec, bound = 2^k */
#घोषणा MODDEC_POW2(x, bound) (((x) - 1) & ((bound) - 1))
#घोषणा MODINC_POW2(x, bound) (((x) + 1) & ((bound) - 1))

काष्ठा chan_info_basic अणु
	u16 chan;
	u16 freq;
पूर्ण;

अटल स्थिर काष्ठा chan_info_basic chan_info_all[] = अणु
	अणु1, 2412पूर्ण,
	अणु2, 2417पूर्ण,
	अणु3, 2422पूर्ण,
	अणु4, 2427पूर्ण,
	अणु5, 2432पूर्ण,
	अणु6, 2437पूर्ण,
	अणु7, 2442पूर्ण,
	अणु8, 2447पूर्ण,
	अणु9, 2452पूर्ण,
	अणु10, 2457पूर्ण,
	अणु11, 2462पूर्ण,
	अणु12, 2467पूर्ण,
	अणु13, 2472पूर्ण,
	अणु14, 2484पूर्ण,

	अणु34, 5170पूर्ण,
	अणु38, 5190पूर्ण,
	अणु42, 5210पूर्ण,
	अणु46, 5230पूर्ण,

	अणु36, 5180पूर्ण,
	अणु40, 5200पूर्ण,
	अणु44, 5220पूर्ण,
	अणु48, 5240पूर्ण,
	अणु52, 5260पूर्ण,
	अणु56, 5280पूर्ण,
	अणु60, 5300पूर्ण,
	अणु64, 5320पूर्ण,

	अणु100, 5500पूर्ण,
	अणु104, 5520पूर्ण,
	अणु108, 5540पूर्ण,
	अणु112, 5560पूर्ण,
	अणु116, 5580पूर्ण,
	अणु120, 5600पूर्ण,
	अणु124, 5620पूर्ण,
	अणु128, 5640पूर्ण,
	अणु132, 5660पूर्ण,
	अणु136, 5680पूर्ण,
	अणु140, 5700पूर्ण,

	अणु149, 5745पूर्ण,
	अणु153, 5765पूर्ण,
	अणु157, 5785पूर्ण,
	अणु161, 5805पूर्ण,
	अणु165, 5825पूर्ण,

	अणु184, 4920पूर्ण,
	अणु188, 4940पूर्ण,
	अणु192, 4960पूर्ण,
	अणु196, 4980पूर्ण,
	अणु200, 5000पूर्ण,
	अणु204, 5020पूर्ण,
	अणु208, 5040पूर्ण,
	अणु212, 5060पूर्ण,
	अणु216, 5080पूर्ण
पूर्ण;

अटल स्थिर u8 ofdm_rate_lookup[] = अणु

	BRCM_RATE_48M,
	BRCM_RATE_24M,
	BRCM_RATE_12M,
	BRCM_RATE_6M,
	BRCM_RATE_54M,
	BRCM_RATE_36M,
	BRCM_RATE_18M,
	BRCM_RATE_9M
पूर्ण;

#घोषणा PHY_WREG_LIMIT  24

व्योम wlc_phyreg_enter(काष्ठा brcms_phy_pub *pih)
अणु
	काष्ठा brcms_phy *pi = container_of(pih, काष्ठा brcms_phy, pubpi_ro);
	wlapi_bmac_ucode_wake_override_phyreg_set(pi->sh->physhim);
पूर्ण

व्योम wlc_phyreg_निकास(काष्ठा brcms_phy_pub *pih)
अणु
	काष्ठा brcms_phy *pi = container_of(pih, काष्ठा brcms_phy, pubpi_ro);
	wlapi_bmac_ucode_wake_override_phyreg_clear(pi->sh->physhim);
पूर्ण

व्योम wlc_radioreg_enter(काष्ठा brcms_phy_pub *pih)
अणु
	काष्ठा brcms_phy *pi = container_of(pih, काष्ठा brcms_phy, pubpi_ro);
	wlapi_bmac_mctrl(pi->sh->physhim, MCTL_LOCK_RADIO, MCTL_LOCK_RADIO);

	udelay(10);
पूर्ण

व्योम wlc_radioreg_निकास(काष्ठा brcms_phy_pub *pih)
अणु
	काष्ठा brcms_phy *pi = container_of(pih, काष्ठा brcms_phy, pubpi_ro);

	(व्योम)bcma_पढ़ो16(pi->d11core, D11REGOFFS(phyversion));
	pi->phy_wreg = 0;
	wlapi_bmac_mctrl(pi->sh->physhim, MCTL_LOCK_RADIO, 0);
पूर्ण

u16 पढ़ो_radio_reg(काष्ठा brcms_phy *pi, u16 addr)
अणु
	u16 data;

	अगर (addr == RADIO_IDCODE)
		वापस 0xffff;

	चयन (pi->pubpi.phy_type) अणु
	हाल PHY_TYPE_N:
		अगर (!CONF_HAS(PHYTYPE, PHY_TYPE_N))
			अवरोध;
		अगर (NREV_GE(pi->pubpi.phy_rev, 7))
			addr |= RADIO_2057_READ_OFF;
		अन्यथा
			addr |= RADIO_2055_READ_OFF;
		अवरोध;

	हाल PHY_TYPE_LCN:
		अगर (!CONF_HAS(PHYTYPE, PHY_TYPE_LCN))
			अवरोध;
		addr |= RADIO_2064_READ_OFF;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	अगर ((D11REV_GE(pi->sh->corerev, 24)) ||
	    (D11REV_IS(pi->sh->corerev, 22)
	     && (pi->pubpi.phy_type != PHY_TYPE_SSN))) अणु
		bcma_wflush16(pi->d11core, D11REGOFFS(radioregaddr), addr);
		data = bcma_पढ़ो16(pi->d11core, D11REGOFFS(radioregdata));
	पूर्ण अन्यथा अणु
		bcma_wflush16(pi->d11core, D11REGOFFS(phy4waddr), addr);
		data = bcma_पढ़ो16(pi->d11core, D11REGOFFS(phy4wdatalo));
	पूर्ण
	pi->phy_wreg = 0;

	वापस data;
पूर्ण

व्योम ग_लिखो_radio_reg(काष्ठा brcms_phy *pi, u16 addr, u16 val)
अणु
	अगर ((D11REV_GE(pi->sh->corerev, 24)) ||
	    (D11REV_IS(pi->sh->corerev, 22)
	     && (pi->pubpi.phy_type != PHY_TYPE_SSN))) अणु

		bcma_wflush16(pi->d11core, D11REGOFFS(radioregaddr), addr);
		bcma_ग_लिखो16(pi->d11core, D11REGOFFS(radioregdata), val);
	पूर्ण अन्यथा अणु
		bcma_wflush16(pi->d11core, D11REGOFFS(phy4waddr), addr);
		bcma_ग_लिखो16(pi->d11core, D11REGOFFS(phy4wdatalo), val);
	पूर्ण

	अगर ((pi->d11core->bus->hosttype == BCMA_HOSTTYPE_PCI) &&
	    (++pi->phy_wreg >= pi->phy_wreg_limit)) अणु
		(व्योम)bcma_पढ़ो32(pi->d11core, D11REGOFFS(maccontrol));
		pi->phy_wreg = 0;
	पूर्ण
पूर्ण

अटल u32 पढ़ो_radio_id(काष्ठा brcms_phy *pi)
अणु
	u32 id;

	अगर (D11REV_GE(pi->sh->corerev, 24)) अणु
		u32 b0, b1, b2;

		bcma_wflush16(pi->d11core, D11REGOFFS(radioregaddr), 0);
		b0 = (u32) bcma_पढ़ो16(pi->d11core, D11REGOFFS(radioregdata));
		bcma_wflush16(pi->d11core, D11REGOFFS(radioregaddr), 1);
		b1 = (u32) bcma_पढ़ो16(pi->d11core, D11REGOFFS(radioregdata));
		bcma_wflush16(pi->d11core, D11REGOFFS(radioregaddr), 2);
		b2 = (u32) bcma_पढ़ो16(pi->d11core, D11REGOFFS(radioregdata));

		id = ((b0 & 0xf) << 28) | (((b2 << 8) | b1) << 12) | ((b0 >> 4)
								      & 0xf);
	पूर्ण अन्यथा अणु
		bcma_wflush16(pi->d11core, D11REGOFFS(phy4waddr), RADIO_IDCODE);
		id = (u32) bcma_पढ़ो16(pi->d11core, D11REGOFFS(phy4wdatalo));
		id |= (u32) bcma_पढ़ो16(pi->d11core,
					D11REGOFFS(phy4wdatahi)) << 16;
	पूर्ण
	pi->phy_wreg = 0;
	वापस id;
पूर्ण

व्योम and_radio_reg(काष्ठा brcms_phy *pi, u16 addr, u16 val)
अणु
	u16 rval;

	rval = पढ़ो_radio_reg(pi, addr);
	ग_लिखो_radio_reg(pi, addr, (rval & val));
पूर्ण

व्योम or_radio_reg(काष्ठा brcms_phy *pi, u16 addr, u16 val)
अणु
	u16 rval;

	rval = पढ़ो_radio_reg(pi, addr);
	ग_लिखो_radio_reg(pi, addr, (rval | val));
पूर्ण

व्योम xor_radio_reg(काष्ठा brcms_phy *pi, u16 addr, u16 mask)
अणु
	u16 rval;

	rval = पढ़ो_radio_reg(pi, addr);
	ग_लिखो_radio_reg(pi, addr, (rval ^ mask));
पूर्ण

व्योम mod_radio_reg(काष्ठा brcms_phy *pi, u16 addr, u16 mask, u16 val)
अणु
	u16 rval;

	rval = पढ़ो_radio_reg(pi, addr);
	ग_लिखो_radio_reg(pi, addr, (rval & ~mask) | (val & mask));
पूर्ण

व्योम ग_लिखो_phy_channel_reg(काष्ठा brcms_phy *pi, uपूर्णांक val)
अणु
	bcma_ग_लिखो16(pi->d11core, D11REGOFFS(phychannel), val);
पूर्ण

u16 पढ़ो_phy_reg(काष्ठा brcms_phy *pi, u16 addr)
अणु
	bcma_wflush16(pi->d11core, D11REGOFFS(phyregaddr), addr);

	pi->phy_wreg = 0;
	वापस bcma_पढ़ो16(pi->d11core, D11REGOFFS(phyregdata));
पूर्ण

व्योम ग_लिखो_phy_reg(काष्ठा brcms_phy *pi, u16 addr, u16 val)
अणु
#अगर_घोषित CONFIG_BCM47XX
	bcma_wflush16(pi->d11core, D11REGOFFS(phyregaddr), addr);
	bcma_ग_लिखो16(pi->d11core, D11REGOFFS(phyregdata), val);
	अगर (addr == 0x72)
		(व्योम)bcma_पढ़ो16(pi->d11core, D11REGOFFS(phyregdata));
#अन्यथा
	bcma_ग_लिखो32(pi->d11core, D11REGOFFS(phyregaddr), addr | (val << 16));
	अगर ((pi->d11core->bus->hosttype == BCMA_HOSTTYPE_PCI) &&
	    (++pi->phy_wreg >= pi->phy_wreg_limit)) अणु
		pi->phy_wreg = 0;
		(व्योम)bcma_पढ़ो16(pi->d11core, D11REGOFFS(phyversion));
	पूर्ण
#पूर्ण_अगर
पूर्ण

व्योम and_phy_reg(काष्ठा brcms_phy *pi, u16 addr, u16 val)
अणु
	bcma_wflush16(pi->d11core, D11REGOFFS(phyregaddr), addr);
	bcma_mask16(pi->d11core, D11REGOFFS(phyregdata), val);
	pi->phy_wreg = 0;
पूर्ण

व्योम or_phy_reg(काष्ठा brcms_phy *pi, u16 addr, u16 val)
अणु
	bcma_wflush16(pi->d11core, D11REGOFFS(phyregaddr), addr);
	bcma_set16(pi->d11core, D11REGOFFS(phyregdata), val);
	pi->phy_wreg = 0;
पूर्ण

व्योम mod_phy_reg(काष्ठा brcms_phy *pi, u16 addr, u16 mask, u16 val)
अणु
	val &= mask;
	bcma_wflush16(pi->d11core, D11REGOFFS(phyregaddr), addr);
	bcma_maskset16(pi->d11core, D11REGOFFS(phyregdata), ~mask, val);
	pi->phy_wreg = 0;
पूर्ण

अटल व्योम wlc_set_phy_uninitted(काष्ठा brcms_phy *pi)
अणु
	पूर्णांक i, j;

	pi->initialized = false;

	pi->tx_vos = 0xffff;
	pi->nrssi_table_delta = 0x7fffffff;
	pi->rc_cal = 0xffff;
	pi->mपूर्णांकxbias = 0xffff;
	pi->txpwridx = -1;
	अगर (ISNPHY(pi)) अणु
		pi->phy_spuraव्योम = SPURAVOID_DISABLE;

		अगर (NREV_GE(pi->pubpi.phy_rev, 3)
		    && NREV_LT(pi->pubpi.phy_rev, 7))
			pi->phy_spuraव्योम = SPURAVOID_AUTO;

		pi->nphy_papd_skip = 0;
		pi->nphy_papd_epsilon_offset[0] = 0xf588;
		pi->nphy_papd_epsilon_offset[1] = 0xf588;
		pi->nphy_txpwr_idx[0] = 128;
		pi->nphy_txpwr_idx[1] = 128;
		pi->nphy_txpwrindex[0].index_पूर्णांकernal = 40;
		pi->nphy_txpwrindex[1].index_पूर्णांकernal = 40;
		pi->phy_pabias = 0;
	पूर्ण अन्यथा अणु
		pi->phy_spuraव्योम = SPURAVOID_AUTO;
	पूर्ण
	pi->radiopwr = 0xffff;
	क्रम (i = 0; i < STATIC_NUM_RF; i++) अणु
		क्रम (j = 0; j < STATIC_NUM_BB; j++)
			pi->stats_11b_txघातer[i][j] = -1;
	पूर्ण
पूर्ण

काष्ठा shared_phy *wlc_phy_shared_attach(काष्ठा shared_phy_params *shp)
अणु
	काष्ठा shared_phy *sh;

	sh = kzalloc(माप(काष्ठा shared_phy), GFP_ATOMIC);
	अगर (sh == शून्य)
		वापस शून्य;

	sh->physhim = shp->physhim;
	sh->unit = shp->unit;
	sh->corerev = shp->corerev;

	sh->vid = shp->vid;
	sh->did = shp->did;
	sh->chip = shp->chip;
	sh->chiprev = shp->chiprev;
	sh->chippkg = shp->chippkg;
	sh->sromrev = shp->sromrev;
	sh->boardtype = shp->boardtype;
	sh->boardrev = shp->boardrev;
	sh->boardflags = shp->boardflags;
	sh->boardflags2 = shp->boardflags2;

	sh->fast_समयr = PHY_SW_TIMER_FAST;
	sh->slow_समयr = PHY_SW_TIMER_SLOW;
	sh->glacial_समयr = PHY_SW_TIMER_GLACIAL;

	sh->rssi_mode = RSSI_ANT_MERGE_MAX;

	वापस sh;
पूर्ण

अटल व्योम wlc_phy_समयrcb_phycal(काष्ठा brcms_phy *pi)
अणु
	uपूर्णांक delay = 5;

	अगर (PHY_PERICAL_MPHASE_PENDING(pi)) अणु
		अगर (!pi->sh->up) अणु
			wlc_phy_cal_perical_mphase_reset(pi);
			वापस;
		पूर्ण

		अगर (SCAN_RM_IN_PROGRESS(pi) || PLT_INPROG_PHY(pi)) अणु

			delay = 1000;
			wlc_phy_cal_perical_mphase_restart(pi);
		पूर्ण अन्यथा
			wlc_phy_cal_perical_nphy_run(pi, PHY_PERICAL_AUTO);
		wlapi_add_समयr(pi->phycal_समयr, delay, 0);
		वापस;
	पूर्ण

पूर्ण

अटल u32 wlc_phy_get_radio_ver(काष्ठा brcms_phy *pi)
अणु
	u32 ver;

	ver = पढ़ो_radio_id(pi);

	वापस ver;
पूर्ण

काष्ठा brcms_phy_pub *
wlc_phy_attach(काष्ठा shared_phy *sh, काष्ठा bcma_device *d11core,
	       पूर्णांक bandtype, काष्ठा wiphy *wiphy)
अणु
	काष्ठा brcms_phy *pi;
	u32 sflags = 0;
	uपूर्णांक phyversion;
	u32 idcode;
	पूर्णांक i;

	अगर (D11REV_IS(sh->corerev, 4))
		sflags = SISF_2G_PHY | SISF_5G_PHY;
	अन्यथा
		sflags = bcma_aपढ़ो32(d11core, BCMA_IOST);

	अगर (bandtype == BRCM_BAND_5G) अणु
		अगर ((sflags & (SISF_5G_PHY | SISF_DB_PHY)) == 0)
			वापस शून्य;
	पूर्ण

	pi = sh->phy_head;
	अगर ((sflags & SISF_DB_PHY) && pi) अणु
		wlapi_bmac_corereset(pi->sh->physhim, pi->pubpi.coreflags);
		pi->refcnt++;
		वापस &pi->pubpi_ro;
	पूर्ण

	pi = kzalloc(माप(काष्ठा brcms_phy), GFP_ATOMIC);
	अगर (pi == शून्य)
		वापस शून्य;
	pi->wiphy = wiphy;
	pi->d11core = d11core;
	pi->sh = sh;
	pi->phy_init_por = true;
	pi->phy_wreg_limit = PHY_WREG_LIMIT;

	pi->txpwr_percent = 100;

	pi->करो_initcal = true;

	pi->phycal_tempdelta = 0;

	अगर (bandtype == BRCM_BAND_2G && (sflags & SISF_2G_PHY))
		pi->pubpi.coreflags = SICF_GMODE;

	wlapi_bmac_corereset(pi->sh->physhim, pi->pubpi.coreflags);
	phyversion = bcma_पढ़ो16(pi->d11core, D11REGOFFS(phyversion));

	pi->pubpi.phy_type = PHY_TYPE(phyversion);
	pi->pubpi.phy_rev = phyversion & PV_PV_MASK;

	अगर (pi->pubpi.phy_type == PHY_TYPE_LCNXN) अणु
		pi->pubpi.phy_type = PHY_TYPE_N;
		pi->pubpi.phy_rev += LCNXN_BASEREV;
	पूर्ण
	pi->pubpi.phy_corक्रमागत = PHY_CORE_NUM_2;
	pi->pubpi.ana_rev = (phyversion & PV_AV_MASK) >> PV_AV_SHIFT;

	अगर (pi->pubpi.phy_type != PHY_TYPE_N &&
	    pi->pubpi.phy_type != PHY_TYPE_LCN)
		जाओ err;

	अगर (bandtype == BRCM_BAND_5G) अणु
		अगर (!ISNPHY(pi))
			जाओ err;
	पूर्ण अन्यथा अगर (!ISNPHY(pi) && !ISLCNPHY(pi)) अणु
		जाओ err;
	पूर्ण

	wlc_phy_anacore((काष्ठा brcms_phy_pub *) pi, ON);

	idcode = wlc_phy_get_radio_ver(pi);
	pi->pubpi.radioid =
		(idcode & IDCODE_ID_MASK) >> IDCODE_ID_SHIFT;
	pi->pubpi.radiorev =
		(idcode & IDCODE_REV_MASK) >> IDCODE_REV_SHIFT;
	pi->pubpi.radiover =
		(idcode & IDCODE_VER_MASK) >> IDCODE_VER_SHIFT;
	अगर (!VALID_RADIO(pi, pi->pubpi.radioid))
		जाओ err;

	wlc_phy_चयन_radio((काष्ठा brcms_phy_pub *) pi, OFF);

	wlc_set_phy_uninitted(pi);

	pi->bw = WL_CHANSPEC_BW_20;
	pi->radio_chanspec = (bandtype == BRCM_BAND_2G) ?
			     ch20mhz_chspec(1) : ch20mhz_chspec(36);

	pi->rxiq_samps = PHY_NOISE_SAMPLE_LOG_NUM_NPHY;
	pi->rxiq_antsel = ANT_RX_DIV_DEF;

	pi->watchकरोg_override = true;

	pi->cal_type_override = PHY_PERICAL_AUTO;

	pi->nphy_saved_noisevars.bufcount = 0;

	अगर (ISNPHY(pi))
		pi->min_txघातer = PHY_TXPWR_MIN_NPHY;
	अन्यथा
		pi->min_txघातer = PHY_TXPWR_MIN;

	pi->sh->phyrxchain = 0x3;

	pi->rx2tx_biasentry = -1;

	pi->phy_txcore_disable_temp = PHY_CHAIN_TX_DISABLE_TEMP;
	pi->phy_txcore_enable_temp =
		PHY_CHAIN_TX_DISABLE_TEMP - PHY_HYSTERESIS_DELTATEMP;
	pi->phy_tempsense_offset = 0;
	pi->phy_txcore_heatedup = false;

	pi->nphy_lastcal_temp = -50;

	pi->phynoise_polling = true;
	अगर (ISNPHY(pi) || ISLCNPHY(pi))
		pi->phynoise_polling = false;

	क्रम (i = 0; i < TXP_NUM_RATES; i++) अणु
		pi->txpwr_limit[i] = BRCMS_TXPWR_MAX;
		pi->txpwr_env_limit[i] = BRCMS_TXPWR_MAX;
		pi->tx_user_target[i] = BRCMS_TXPWR_MAX;
	पूर्ण

	pi->radiopwr_override = RADIOPWR_OVERRIDE_DEF;

	pi->user_txpwr_at_rfport = false;

	अगर (ISNPHY(pi)) अणु

		pi->phycal_समयr = wlapi_init_समयr(pi->sh->physhim,
						    wlc_phy_समयrcb_phycal,
						    pi, "phycal");
		अगर (!pi->phycal_समयr)
			जाओ err;

		अगर (!wlc_phy_attach_nphy(pi))
			जाओ err;

	पूर्ण अन्यथा अगर (ISLCNPHY(pi)) अणु
		अगर (!wlc_phy_attach_lcnphy(pi))
			जाओ err;

	पूर्ण

	pi->refcnt++;
	pi->next = pi->sh->phy_head;
	sh->phy_head = pi;

	स_नकल(&pi->pubpi_ro, &pi->pubpi, माप(काष्ठा brcms_phy_pub));

	वापस &pi->pubpi_ro;

err:
	kमुक्त(pi);
	वापस शून्य;
पूर्ण

व्योम wlc_phy_detach(काष्ठा brcms_phy_pub *pih)
अणु
	काष्ठा brcms_phy *pi = container_of(pih, काष्ठा brcms_phy, pubpi_ro);

	अगर (pih) अणु
		अगर (--pi->refcnt)
			वापस;

		अगर (pi->phycal_समयr) अणु
			wlapi_मुक्त_समयr(pi->phycal_समयr);
			pi->phycal_समयr = शून्य;
		पूर्ण

		अगर (pi->sh->phy_head == pi)
			pi->sh->phy_head = pi->next;
		अन्यथा अगर (pi->sh->phy_head->next == pi)
			pi->sh->phy_head->next = शून्य;

		अगर (pi->pi_fptr.detach)
			(pi->pi_fptr.detach)(pi);

		kमुक्त(pi);
	पूर्ण
पूर्ण

bool
wlc_phy_get_phyversion(काष्ठा brcms_phy_pub *pih, u16 *phytype, u16 *phyrev,
		       u16 *radioid, u16 *radiover)
अणु
	काष्ठा brcms_phy *pi = container_of(pih, काष्ठा brcms_phy, pubpi_ro);
	*phytype = (u16) pi->pubpi.phy_type;
	*phyrev = (u16) pi->pubpi.phy_rev;
	*radioid = pi->pubpi.radioid;
	*radiover = pi->pubpi.radiorev;

	वापस true;
पूर्ण

bool wlc_phy_get_encore(काष्ठा brcms_phy_pub *pih)
अणु
	काष्ठा brcms_phy *pi = container_of(pih, काष्ठा brcms_phy, pubpi_ro);
	वापस pi->pubpi.abgphy_encore;
पूर्ण

u32 wlc_phy_get_coreflags(काष्ठा brcms_phy_pub *pih)
अणु
	काष्ठा brcms_phy *pi = container_of(pih, काष्ठा brcms_phy, pubpi_ro);
	वापस pi->pubpi.coreflags;
पूर्ण

व्योम wlc_phy_anacore(काष्ठा brcms_phy_pub *pih, bool on)
अणु
	काष्ठा brcms_phy *pi = container_of(pih, काष्ठा brcms_phy, pubpi_ro);

	अगर (ISNPHY(pi)) अणु
		अगर (on) अणु
			अगर (NREV_GE(pi->pubpi.phy_rev, 3)) अणु
				ग_लिखो_phy_reg(pi, 0xa6, 0x0d);
				ग_लिखो_phy_reg(pi, 0x8f, 0x0);
				ग_लिखो_phy_reg(pi, 0xa7, 0x0d);
				ग_लिखो_phy_reg(pi, 0xa5, 0x0);
			पूर्ण अन्यथा अणु
				ग_लिखो_phy_reg(pi, 0xa5, 0x0);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (NREV_GE(pi->pubpi.phy_rev, 3)) अणु
				ग_लिखो_phy_reg(pi, 0x8f, 0x07ff);
				ग_लिखो_phy_reg(pi, 0xa6, 0x0fd);
				ग_लिखो_phy_reg(pi, 0xa5, 0x07ff);
				ग_लिखो_phy_reg(pi, 0xa7, 0x0fd);
			पूर्ण अन्यथा अणु
				ग_लिखो_phy_reg(pi, 0xa5, 0x7fff);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (ISLCNPHY(pi)) अणु
		अगर (on) अणु
			and_phy_reg(pi, 0x43b,
				    ~((0x1 << 0) | (0x1 << 1) | (0x1 << 2)));
		पूर्ण अन्यथा अणु
			or_phy_reg(pi, 0x43c,
				   (0x1 << 0) | (0x1 << 1) | (0x1 << 2));
			or_phy_reg(pi, 0x43b,
				   (0x1 << 0) | (0x1 << 1) | (0x1 << 2));
		पूर्ण
	पूर्ण
पूर्ण

u32 wlc_phy_clk_bwbits(काष्ठा brcms_phy_pub *pih)
अणु
	काष्ठा brcms_phy *pi = container_of(pih, काष्ठा brcms_phy, pubpi_ro);

	u32 phy_bw_clkbits = 0;

	अगर (pi && (ISNPHY(pi) || ISLCNPHY(pi))) अणु
		चयन (pi->bw) अणु
		हाल WL_CHANSPEC_BW_10:
			phy_bw_clkbits = SICF_BW10;
			अवरोध;
		हाल WL_CHANSPEC_BW_20:
			phy_bw_clkbits = SICF_BW20;
			अवरोध;
		हाल WL_CHANSPEC_BW_40:
			phy_bw_clkbits = SICF_BW40;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस phy_bw_clkbits;
पूर्ण

व्योम wlc_phy_por_inक्रमm(काष्ठा brcms_phy_pub *ppi)
अणु
	काष्ठा brcms_phy *pi = container_of(ppi, काष्ठा brcms_phy, pubpi_ro);

	pi->phy_init_por = true;
पूर्ण

व्योम wlc_phy_edcrs_lock(काष्ठा brcms_phy_pub *pih, bool lock)
अणु
	काष्ठा brcms_phy *pi = container_of(pih, काष्ठा brcms_phy, pubpi_ro);

	pi->edcrs_threshold_lock = lock;

	ग_लिखो_phy_reg(pi, 0x22c, 0x46b);
	ग_लिखो_phy_reg(pi, 0x22d, 0x46b);
	ग_लिखो_phy_reg(pi, 0x22e, 0x3c0);
	ग_लिखो_phy_reg(pi, 0x22f, 0x3c0);
पूर्ण

व्योम wlc_phy_initcal_enable(काष्ठा brcms_phy_pub *pih, bool initcal)
अणु
	काष्ठा brcms_phy *pi = container_of(pih, काष्ठा brcms_phy, pubpi_ro);

	pi->करो_initcal = initcal;
पूर्ण

व्योम wlc_phy_hw_clk_state_upd(काष्ठा brcms_phy_pub *pih, bool newstate)
अणु
	काष्ठा brcms_phy *pi = container_of(pih, काष्ठा brcms_phy, pubpi_ro);

	अगर (!pi || !pi->sh)
		वापस;

	pi->sh->clk = newstate;
पूर्ण

व्योम wlc_phy_hw_state_upd(काष्ठा brcms_phy_pub *pih, bool newstate)
अणु
	काष्ठा brcms_phy *pi = container_of(pih, काष्ठा brcms_phy, pubpi_ro);

	अगर (!pi || !pi->sh)
		वापस;

	pi->sh->up = newstate;
पूर्ण

व्योम wlc_phy_init(काष्ठा brcms_phy_pub *pih, u16 chanspec)
अणु
	u32 mc;
	व्योम (*phy_init)(काष्ठा brcms_phy *) = शून्य;
	काष्ठा brcms_phy *pi = container_of(pih, काष्ठा brcms_phy, pubpi_ro);

	अगर (pi->init_in_progress)
		वापस;

	pi->init_in_progress = true;

	pi->radio_chanspec = chanspec;

	mc = bcma_पढ़ो32(pi->d11core, D11REGOFFS(maccontrol));
	अगर (WARN(mc & MCTL_EN_MAC, "HW error MAC running on init"))
		वापस;

	अगर (!(pi->measure_hold & PHY_HOLD_FOR_SCAN))
		pi->measure_hold |= PHY_HOLD_FOR_NOT_ASSOC;

	अगर (WARN(!(bcma_aपढ़ो32(pi->d11core, BCMA_IOST) & SISF_FCLKA),
		 "HW error SISF_FCLKA\n"))
		वापस;

	phy_init = pi->pi_fptr.init;

	अगर (phy_init == शून्य)
		वापस;

	wlc_phy_anacore(pih, ON);

	अगर (CHSPEC_BW(pi->radio_chanspec) != pi->bw)
		wlapi_bmac_bw_set(pi->sh->physhim,
				  CHSPEC_BW(pi->radio_chanspec));

	pi->nphy_gain_boost = true;

	wlc_phy_चयन_radio((काष्ठा brcms_phy_pub *) pi, ON);

	(*phy_init)(pi);

	pi->phy_init_por = false;

	अगर (D11REV_IS(pi->sh->corerev, 11) || D11REV_IS(pi->sh->corerev, 12))
		wlc_phy_करो_dummy_tx(pi, true, OFF);

	अगर (!(ISNPHY(pi)))
		wlc_phy_txघातer_update_shm(pi);

	wlc_phy_ant_rxभाग_set((काष्ठा brcms_phy_pub *) pi, pi->sh->rx_antभाग);

	pi->init_in_progress = false;
पूर्ण

व्योम wlc_phy_cal_init(काष्ठा brcms_phy_pub *pih)
अणु
	काष्ठा brcms_phy *pi = container_of(pih, काष्ठा brcms_phy, pubpi_ro);
	व्योम (*cal_init)(काष्ठा brcms_phy *) = शून्य;

	अगर (WARN((bcma_पढ़ो32(pi->d11core, D11REGOFFS(maccontrol)) &
		  MCTL_EN_MAC) != 0, "HW error: MAC enabled during phy cal\n"))
		वापस;

	अगर (!pi->initialized) अणु
		cal_init = pi->pi_fptr.calinit;
		अगर (cal_init)
			(*cal_init)(pi);

		pi->initialized = true;
	पूर्ण
पूर्ण

पूर्णांक wlc_phy_करोwn(काष्ठा brcms_phy_pub *pih)
अणु
	काष्ठा brcms_phy *pi = container_of(pih, काष्ठा brcms_phy, pubpi_ro);
	पूर्णांक callbacks = 0;

	अगर (pi->phycal_समयr
	    && !wlapi_del_समयr(pi->phycal_समयr))
		callbacks++;

	pi->nphy_iqcal_chanspec_2G = 0;
	pi->nphy_iqcal_chanspec_5G = 0;

	वापस callbacks;
पूर्ण

व्योम
wlc_phy_table_addr(काष्ठा brcms_phy *pi, uपूर्णांक tbl_id, uपूर्णांक tbl_offset,
		   u16 tblAddr, u16 tblDataHi, u16 tblDataLo)
अणु
	ग_लिखो_phy_reg(pi, tblAddr, (tbl_id << 10) | tbl_offset);

	pi->tbl_data_hi = tblDataHi;
	pi->tbl_data_lo = tblDataLo;

	अगर (pi->sh->chip == BCMA_CHIP_ID_BCM43224 &&
	    pi->sh->chiprev == 1) अणु
		pi->tbl_addr = tblAddr;
		pi->tbl_save_id = tbl_id;
		pi->tbl_save_offset = tbl_offset;
	पूर्ण
पूर्ण

व्योम wlc_phy_table_data_ग_लिखो(काष्ठा brcms_phy *pi, uपूर्णांक width, u32 val)
अणु
	अगर ((pi->sh->chip == BCMA_CHIP_ID_BCM43224) &&
	    (pi->sh->chiprev == 1) &&
	    (pi->tbl_save_id == NPHY_TBL_ID_ANTSWCTRLLUT)) अणु
		पढ़ो_phy_reg(pi, pi->tbl_data_lo);

		ग_लिखो_phy_reg(pi, pi->tbl_addr,
			      (pi->tbl_save_id << 10) | pi->tbl_save_offset);
		pi->tbl_save_offset++;
	पूर्ण

	अगर (width == 32) अणु
		ग_लिखो_phy_reg(pi, pi->tbl_data_hi, (u16) (val >> 16));
		ग_लिखो_phy_reg(pi, pi->tbl_data_lo, (u16) val);
	पूर्ण अन्यथा अणु
		ग_लिखो_phy_reg(pi, pi->tbl_data_lo, (u16) val);
	पूर्ण
पूर्ण

व्योम
wlc_phy_ग_लिखो_table(काष्ठा brcms_phy *pi, स्थिर काष्ठा phytbl_info *ptbl_info,
		    u16 tblAddr, u16 tblDataHi, u16 tblDataLo)
अणु
	uपूर्णांक idx;
	uपूर्णांक tbl_id = ptbl_info->tbl_id;
	uपूर्णांक tbl_offset = ptbl_info->tbl_offset;
	uपूर्णांक tbl_width = ptbl_info->tbl_width;
	स्थिर u8 *ptbl_8b = (स्थिर u8 *)ptbl_info->tbl_ptr;
	स्थिर u16 *ptbl_16b = (स्थिर u16 *)ptbl_info->tbl_ptr;
	स्थिर u32 *ptbl_32b = (स्थिर u32 *)ptbl_info->tbl_ptr;

	ग_लिखो_phy_reg(pi, tblAddr, (tbl_id << 10) | tbl_offset);

	क्रम (idx = 0; idx < ptbl_info->tbl_len; idx++) अणु

		अगर ((pi->sh->chip == BCMA_CHIP_ID_BCM43224) &&
		    (pi->sh->chiprev == 1) &&
		    (tbl_id == NPHY_TBL_ID_ANTSWCTRLLUT)) अणु
			पढ़ो_phy_reg(pi, tblDataLo);

			ग_लिखो_phy_reg(pi, tblAddr,
				      (tbl_id << 10) | (tbl_offset + idx));
		पूर्ण

		अगर (tbl_width == 32) अणु
			ग_लिखो_phy_reg(pi, tblDataHi,
				      (u16) (ptbl_32b[idx] >> 16));
			ग_लिखो_phy_reg(pi, tblDataLo, (u16) ptbl_32b[idx]);
		पूर्ण अन्यथा अगर (tbl_width == 16) अणु
			ग_लिखो_phy_reg(pi, tblDataLo, ptbl_16b[idx]);
		पूर्ण अन्यथा अणु
			ग_लिखो_phy_reg(pi, tblDataLo, ptbl_8b[idx]);
		पूर्ण
	पूर्ण
पूर्ण

व्योम
wlc_phy_पढ़ो_table(काष्ठा brcms_phy *pi, स्थिर काष्ठा phytbl_info *ptbl_info,
		   u16 tblAddr, u16 tblDataHi, u16 tblDataLo)
अणु
	uपूर्णांक idx;
	uपूर्णांक tbl_id = ptbl_info->tbl_id;
	uपूर्णांक tbl_offset = ptbl_info->tbl_offset;
	uपूर्णांक tbl_width = ptbl_info->tbl_width;
	u8 *ptbl_8b = (u8 *)ptbl_info->tbl_ptr;
	u16 *ptbl_16b = (u16 *)ptbl_info->tbl_ptr;
	u32 *ptbl_32b = (u32 *)ptbl_info->tbl_ptr;

	ग_लिखो_phy_reg(pi, tblAddr, (tbl_id << 10) | tbl_offset);

	क्रम (idx = 0; idx < ptbl_info->tbl_len; idx++) अणु

		अगर ((pi->sh->chip == BCMA_CHIP_ID_BCM43224) &&
		    (pi->sh->chiprev == 1)) अणु
			(व्योम)पढ़ो_phy_reg(pi, tblDataLo);

			ग_लिखो_phy_reg(pi, tblAddr,
				      (tbl_id << 10) | (tbl_offset + idx));
		पूर्ण

		अगर (tbl_width == 32) अणु
			ptbl_32b[idx] = पढ़ो_phy_reg(pi, tblDataLo);
			ptbl_32b[idx] |= (पढ़ो_phy_reg(pi, tblDataHi) << 16);
		पूर्ण अन्यथा अगर (tbl_width == 16) अणु
			ptbl_16b[idx] = पढ़ो_phy_reg(pi, tblDataLo);
		पूर्ण अन्यथा अणु
			ptbl_8b[idx] = (u8) पढ़ो_phy_reg(pi, tblDataLo);
		पूर्ण
	पूर्ण
पूर्ण

uपूर्णांक
wlc_phy_init_radio_regs_allbands(काष्ठा brcms_phy *pi,
				 काष्ठा radio_20xx_regs *radioregs)
अणु
	uपूर्णांक i = 0;

	करो अणु
		अगर (radioregs[i].करो_init)
			ग_लिखो_radio_reg(pi, radioregs[i].address,
					(u16) radioregs[i].init);

		i++;
	पूर्ण जबतक (radioregs[i].address != 0xffff);

	वापस i;
पूर्ण

uपूर्णांक
wlc_phy_init_radio_regs(काष्ठा brcms_phy *pi,
			स्थिर काष्ठा radio_regs *radioregs,
			u16 core_offset)
अणु
	uपूर्णांक i = 0;
	uपूर्णांक count = 0;

	करो अणु
		अगर (CHSPEC_IS5G(pi->radio_chanspec)) अणु
			अगर (radioregs[i].करो_init_a) अणु
				ग_लिखो_radio_reg(pi,
						radioregs[i].
						address | core_offset,
						(u16) radioregs[i].init_a);
				अगर (ISNPHY(pi) && (++count % 4 == 0))
					BRCMS_PHY_WAR_PR51571(pi);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (radioregs[i].करो_init_g) अणु
				ग_लिखो_radio_reg(pi,
						radioregs[i].
						address | core_offset,
						(u16) radioregs[i].init_g);
				अगर (ISNPHY(pi) && (++count % 4 == 0))
					BRCMS_PHY_WAR_PR51571(pi);
			पूर्ण
		पूर्ण

		i++;
	पूर्ण जबतक (radioregs[i].address != 0xffff);

	वापस i;
पूर्ण

व्योम wlc_phy_करो_dummy_tx(काष्ठा brcms_phy *pi, bool ofdm, bool pa_on)
अणु
#घोषणा DUMMY_PKT_LEN   20
	काष्ठा bcma_device *core = pi->d11core;
	पूर्णांक i, count;
	u8 ofdmpkt[DUMMY_PKT_LEN] = अणु
		0xcc, 0x01, 0x02, 0x00, 0x00, 0x00, 0xd4, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00
	पूर्ण;
	u8 cckpkt[DUMMY_PKT_LEN] = अणु
		0x6e, 0x84, 0x0b, 0x00, 0x00, 0x00, 0xd4, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00
	पूर्ण;
	u32 *dummypkt;

	dummypkt = (u32 *) (ofdm ? ofdmpkt : cckpkt);
	wlapi_bmac_ग_लिखो_ढाँचा_ram(pi->sh->physhim, 0, DUMMY_PKT_LEN,
				      dummypkt);

	bcma_ग_लिखो16(core, D11REGOFFS(xmtsel), 0);

	अगर (D11REV_GE(pi->sh->corerev, 11))
		bcma_ग_लिखो16(core, D11REGOFFS(wepctl), 0x100);
	अन्यथा
		bcma_ग_लिखो16(core, D11REGOFFS(wepctl), 0);

	bcma_ग_लिखो16(core, D11REGOFFS(txe_phyctl),
		     (ofdm ? 1 : 0) | PHY_TXC_ANT_0);
	अगर (ISNPHY(pi) || ISLCNPHY(pi))
		bcma_ग_लिखो16(core, D11REGOFFS(txe_phyctl1), 0x1A02);

	bcma_ग_लिखो16(core, D11REGOFFS(txe_wm_0), 0);
	bcma_ग_लिखो16(core, D11REGOFFS(txe_wm_1), 0);

	bcma_ग_लिखो16(core, D11REGOFFS(xmttplatetxptr), 0);
	bcma_ग_लिखो16(core, D11REGOFFS(xmttxcnt), DUMMY_PKT_LEN);

	bcma_ग_लिखो16(core, D11REGOFFS(xmtsel),
		     ((8 << 8) | (1 << 5) | (1 << 2) | 2));

	bcma_ग_लिखो16(core, D11REGOFFS(txe_ctl), 0);

	अगर (!pa_on) अणु
		अगर (ISNPHY(pi))
			wlc_phy_pa_override_nphy(pi, OFF);
	पूर्ण

	अगर (ISNPHY(pi) || ISLCNPHY(pi))
		bcma_ग_लिखो16(core, D11REGOFFS(txe_aux), 0xD0);
	अन्यथा
		bcma_ग_लिखो16(core, D11REGOFFS(txe_aux), ((1 << 5) | (1 << 4)));

	(व्योम)bcma_पढ़ो16(core, D11REGOFFS(txe_aux));

	i = 0;
	count = ofdm ? 30 : 250;
	जबतक ((i++ < count)
	       && (bcma_पढ़ो16(core, D11REGOFFS(txe_status)) & (1 << 7)))
		udelay(10);

	i = 0;

	जबतक ((i++ < 10) &&
	       ((bcma_पढ़ो16(core, D11REGOFFS(txe_status)) & (1 << 10)) == 0))
		udelay(10);

	i = 0;

	जबतक ((i++ < 10) &&
	       ((bcma_पढ़ो16(core, D11REGOFFS(अगरsstat)) & (1 << 8))))
		udelay(10);

	अगर (!pa_on) अणु
		अगर (ISNPHY(pi))
			wlc_phy_pa_override_nphy(pi, ON);
	पूर्ण
पूर्ण

व्योम wlc_phy_hold_upd(काष्ठा brcms_phy_pub *pih, u32 id, bool set)
अणु
	काष्ठा brcms_phy *pi = container_of(pih, काष्ठा brcms_phy, pubpi_ro);

	अगर (set)
		mboolset(pi->measure_hold, id);
	अन्यथा
		mboolclr(pi->measure_hold, id);

	वापस;
पूर्ण

व्योम wlc_phy_mute_upd(काष्ठा brcms_phy_pub *pih, bool mute, u32 flags)
अणु
	काष्ठा brcms_phy *pi = container_of(pih, काष्ठा brcms_phy, pubpi_ro);

	अगर (mute)
		mboolset(pi->measure_hold, PHY_HOLD_FOR_MUTE);
	अन्यथा
		mboolclr(pi->measure_hold, PHY_HOLD_FOR_MUTE);

	अगर (!mute && (flags & PHY_MUTE_FOR_PREISM))
		pi->nphy_perical_last = pi->sh->now - pi->sh->glacial_समयr;
	वापस;
पूर्ण

व्योम wlc_phy_clear_tssi(काष्ठा brcms_phy_pub *pih)
अणु
	काष्ठा brcms_phy *pi = container_of(pih, काष्ठा brcms_phy, pubpi_ro);

	अगर (ISNPHY(pi)) अणु
		वापस;
	पूर्ण अन्यथा अणु
		wlapi_bmac_ग_लिखो_shm(pi->sh->physhim, M_B_TSSI_0, शून्य_TSSI_W);
		wlapi_bmac_ग_लिखो_shm(pi->sh->physhim, M_B_TSSI_1, शून्य_TSSI_W);
		wlapi_bmac_ग_लिखो_shm(pi->sh->physhim, M_G_TSSI_0, शून्य_TSSI_W);
		wlapi_bmac_ग_लिखो_shm(pi->sh->physhim, M_G_TSSI_1, शून्य_TSSI_W);
	पूर्ण
पूर्ण

अटल bool wlc_phy_cal_txघातer_recalc_sw(काष्ठा brcms_phy *pi)
अणु
	वापस false;
पूर्ण

व्योम wlc_phy_चयन_radio(काष्ठा brcms_phy_pub *pih, bool on)
अणु
	काष्ठा brcms_phy *pi = container_of(pih, काष्ठा brcms_phy, pubpi_ro);
	(व्योम)bcma_पढ़ो32(pi->d11core, D11REGOFFS(maccontrol));

	अगर (ISNPHY(pi)) अणु
		wlc_phy_चयन_radio_nphy(pi, on);
	पूर्ण अन्यथा अगर (ISLCNPHY(pi)) अणु
		अगर (on) अणु
			and_phy_reg(pi, 0x44c,
				    ~((0x1 << 8) |
				      (0x1 << 9) |
				      (0x1 << 10) | (0x1 << 11) | (0x1 << 12)));
			and_phy_reg(pi, 0x4b0, ~((0x1 << 3) | (0x1 << 11)));
			and_phy_reg(pi, 0x4f9, ~(0x1 << 3));
		पूर्ण अन्यथा अणु
			and_phy_reg(pi, 0x44d,
				    ~((0x1 << 10) |
				      (0x1 << 11) |
				      (0x1 << 12) | (0x1 << 13) | (0x1 << 14)));
			or_phy_reg(pi, 0x44c,
				   (0x1 << 8) |
				   (0x1 << 9) |
				   (0x1 << 10) | (0x1 << 11) | (0x1 << 12));

			and_phy_reg(pi, 0x4b7, ~((0x7f << 8)));
			and_phy_reg(pi, 0x4b1, ~((0x1 << 13)));
			or_phy_reg(pi, 0x4b0, (0x1 << 3) | (0x1 << 11));
			and_phy_reg(pi, 0x4fa, ~((0x1 << 3)));
			or_phy_reg(pi, 0x4f9, (0x1 << 3));
		पूर्ण
	पूर्ण
पूर्ण

u16 wlc_phy_bw_state_get(काष्ठा brcms_phy_pub *ppi)
अणु
	काष्ठा brcms_phy *pi = container_of(ppi, काष्ठा brcms_phy, pubpi_ro);

	वापस pi->bw;
पूर्ण

व्योम wlc_phy_bw_state_set(काष्ठा brcms_phy_pub *ppi, u16 bw)
अणु
	काष्ठा brcms_phy *pi = container_of(ppi, काष्ठा brcms_phy, pubpi_ro);

	pi->bw = bw;
पूर्ण

व्योम wlc_phy_chanspec_radio_set(काष्ठा brcms_phy_pub *ppi, u16 newch)
अणु
	काष्ठा brcms_phy *pi = container_of(ppi, काष्ठा brcms_phy, pubpi_ro);
	pi->radio_chanspec = newch;

पूर्ण

u16 wlc_phy_chanspec_get(काष्ठा brcms_phy_pub *ppi)
अणु
	काष्ठा brcms_phy *pi = container_of(ppi, काष्ठा brcms_phy, pubpi_ro);

	वापस pi->radio_chanspec;
पूर्ण

व्योम wlc_phy_chanspec_set(काष्ठा brcms_phy_pub *ppi, u16 chanspec)
अणु
	काष्ठा brcms_phy *pi = container_of(ppi, काष्ठा brcms_phy, pubpi_ro);
	u16 m_cur_channel;
	व्योम (*chanspec_set)(काष्ठा brcms_phy *, u16) = शून्य;
	m_cur_channel = CHSPEC_CHANNEL(chanspec);
	अगर (CHSPEC_IS5G(chanspec))
		m_cur_channel |= D11_CURCHANNEL_5G;
	अगर (CHSPEC_IS40(chanspec))
		m_cur_channel |= D11_CURCHANNEL_40;
	wlapi_bmac_ग_लिखो_shm(pi->sh->physhim, M_CURCHANNEL, m_cur_channel);

	chanspec_set = pi->pi_fptr.chanset;
	अगर (chanspec_set)
		(*chanspec_set)(pi, chanspec);

पूर्ण

पूर्णांक wlc_phy_chanspec_freq2bandrange_lpssn(uपूर्णांक freq)
अणु
	पूर्णांक range = -1;

	अगर (freq < 2500)
		range = WL_CHAN_FREQ_RANGE_2G;
	अन्यथा अगर (freq <= 5320)
		range = WL_CHAN_FREQ_RANGE_5GL;
	अन्यथा अगर (freq <= 5700)
		range = WL_CHAN_FREQ_RANGE_5GM;
	अन्यथा
		range = WL_CHAN_FREQ_RANGE_5GH;

	वापस range;
पूर्ण

पूर्णांक wlc_phy_chanspec_bandrange_get(काष्ठा brcms_phy *pi, u16 chanspec)
अणु
	पूर्णांक range = -1;
	uपूर्णांक channel = CHSPEC_CHANNEL(chanspec);
	uपूर्णांक freq = wlc_phy_channel2freq(channel);

	अगर (ISNPHY(pi))
		range = wlc_phy_get_chan_freq_range_nphy(pi, channel);
	अन्यथा अगर (ISLCNPHY(pi))
		range = wlc_phy_chanspec_freq2bandrange_lpssn(freq);

	वापस range;
पूर्ण

व्योम wlc_phy_chanspec_ch14_widefilter_set(काष्ठा brcms_phy_pub *ppi,
					  bool wide_filter)
अणु
	काष्ठा brcms_phy *pi = container_of(ppi, काष्ठा brcms_phy, pubpi_ro);

	pi->channel_14_wide_filter = wide_filter;

पूर्ण

पूर्णांक wlc_phy_channel2freq(uपूर्णांक channel)
अणु
	uपूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(chan_info_all); i++)
		अगर (chan_info_all[i].chan == channel)
			वापस chan_info_all[i].freq;
	वापस 0;
पूर्ण

व्योम
wlc_phy_chanspec_band_validch(काष्ठा brcms_phy_pub *ppi, uपूर्णांक band,
			      काष्ठा brcms_chanvec *channels)
अणु
	काष्ठा brcms_phy *pi = container_of(ppi, काष्ठा brcms_phy, pubpi_ro);
	uपूर्णांक i;
	uपूर्णांक channel;

	स_रखो(channels, 0, माप(काष्ठा brcms_chanvec));

	क्रम (i = 0; i < ARRAY_SIZE(chan_info_all); i++) अणु
		channel = chan_info_all[i].chan;

		अगर ((pi->a_band_high_disable) && (channel >= FIRST_REF5_CHANNUM)
		    && (channel <= LAST_REF5_CHANNUM))
			जारी;

		अगर ((band == BRCM_BAND_2G && channel <= CH_MAX_2G_CHANNEL) ||
		    (band == BRCM_BAND_5G && channel > CH_MAX_2G_CHANNEL))
			setbit(channels->vec, channel);
	पूर्ण
पूर्ण

u16 wlc_phy_chanspec_band_firstch(काष्ठा brcms_phy_pub *ppi, uपूर्णांक band)
अणु
	काष्ठा brcms_phy *pi = container_of(ppi, काष्ठा brcms_phy, pubpi_ro);
	uपूर्णांक i;
	uपूर्णांक channel;
	u16 chspec;

	क्रम (i = 0; i < ARRAY_SIZE(chan_info_all); i++) अणु
		channel = chan_info_all[i].chan;

		अगर (ISNPHY(pi) && pi->bw == WL_CHANSPEC_BW_40) अणु
			uपूर्णांक j;

			क्रम (j = 0; j < ARRAY_SIZE(chan_info_all); j++) अणु
				अगर (chan_info_all[j].chan ==
				    channel + CH_10MHZ_APART)
					अवरोध;
			पूर्ण

			अगर (j == ARRAY_SIZE(chan_info_all))
				जारी;

			channel = upper_20_sb(channel);
			chspec =  channel | WL_CHANSPEC_BW_40 |
				  WL_CHANSPEC_CTL_SB_LOWER;
			अगर (band == BRCM_BAND_2G)
				chspec |= WL_CHANSPEC_BAND_2G;
			अन्यथा
				chspec |= WL_CHANSPEC_BAND_5G;
		पूर्ण अन्यथा
			chspec = ch20mhz_chspec(channel);

		अगर ((pi->a_band_high_disable) && (channel >= FIRST_REF5_CHANNUM)
		    && (channel <= LAST_REF5_CHANNUM))
			जारी;

		अगर ((band == BRCM_BAND_2G && channel <= CH_MAX_2G_CHANNEL) ||
		    (band == BRCM_BAND_5G && channel > CH_MAX_2G_CHANNEL))
			वापस chspec;
	पूर्ण

	वापस (u16) INVCHANSPEC;
पूर्ण

पूर्णांक wlc_phy_txघातer_get(काष्ठा brcms_phy_pub *ppi, uपूर्णांक *qdbm, bool *override)
अणु
	काष्ठा brcms_phy *pi = container_of(ppi, काष्ठा brcms_phy, pubpi_ro);

	*qdbm = pi->tx_user_target[0];
	अगर (override != शून्य)
		*override = pi->txpwroverride;
	वापस 0;
पूर्ण

व्योम wlc_phy_txघातer_target_set(काष्ठा brcms_phy_pub *ppi,
				काष्ठा txpwr_limits *txpwr)
अणु
	bool mac_enabled = false;
	काष्ठा brcms_phy *pi = container_of(ppi, काष्ठा brcms_phy, pubpi_ro);

	स_नकल(&pi->tx_user_target[TXP_FIRST_CCK],
	       &txpwr->cck[0], BRCMS_NUM_RATES_CCK);

	स_नकल(&pi->tx_user_target[TXP_FIRST_OFDM],
	       &txpwr->ofdm[0], BRCMS_NUM_RATES_OFDM);
	स_नकल(&pi->tx_user_target[TXP_FIRST_OFDM_20_CDD],
	       &txpwr->ofdm_cdd[0], BRCMS_NUM_RATES_OFDM);

	स_नकल(&pi->tx_user_target[TXP_FIRST_OFDM_40_SISO],
	       &txpwr->ofdm_40_siso[0], BRCMS_NUM_RATES_OFDM);
	स_नकल(&pi->tx_user_target[TXP_FIRST_OFDM_40_CDD],
	       &txpwr->ofdm_40_cdd[0], BRCMS_NUM_RATES_OFDM);

	स_नकल(&pi->tx_user_target[TXP_FIRST_MCS_20_SISO],
	       &txpwr->mcs_20_siso[0], BRCMS_NUM_RATES_MCS_1_STREAM);
	स_नकल(&pi->tx_user_target[TXP_FIRST_MCS_20_CDD],
	       &txpwr->mcs_20_cdd[0], BRCMS_NUM_RATES_MCS_1_STREAM);
	स_नकल(&pi->tx_user_target[TXP_FIRST_MCS_20_STBC],
	       &txpwr->mcs_20_stbc[0], BRCMS_NUM_RATES_MCS_1_STREAM);
	स_नकल(&pi->tx_user_target[TXP_FIRST_MCS_20_SDM],
	       &txpwr->mcs_20_mimo[0], BRCMS_NUM_RATES_MCS_2_STREAM);

	स_नकल(&pi->tx_user_target[TXP_FIRST_MCS_40_SISO],
	       &txpwr->mcs_40_siso[0], BRCMS_NUM_RATES_MCS_1_STREAM);
	स_नकल(&pi->tx_user_target[TXP_FIRST_MCS_40_CDD],
	       &txpwr->mcs_40_cdd[0], BRCMS_NUM_RATES_MCS_1_STREAM);
	स_नकल(&pi->tx_user_target[TXP_FIRST_MCS_40_STBC],
	       &txpwr->mcs_40_stbc[0], BRCMS_NUM_RATES_MCS_1_STREAM);
	स_नकल(&pi->tx_user_target[TXP_FIRST_MCS_40_SDM],
	       &txpwr->mcs_40_mimo[0], BRCMS_NUM_RATES_MCS_2_STREAM);

	अगर (bcma_पढ़ो32(pi->d11core, D11REGOFFS(maccontrol)) & MCTL_EN_MAC)
		mac_enabled = true;

	अगर (mac_enabled)
		wlapi_suspend_mac_and_रुको(pi->sh->physhim);

	wlc_phy_txघातer_recalc_target(pi);
	wlc_phy_cal_txघातer_recalc_sw(pi);

	अगर (mac_enabled)
		wlapi_enable_mac(pi->sh->physhim);
पूर्ण

पूर्णांक wlc_phy_txघातer_set(काष्ठा brcms_phy_pub *ppi, uपूर्णांक qdbm, bool override)
अणु
	काष्ठा brcms_phy *pi = container_of(ppi, काष्ठा brcms_phy, pubpi_ro);
	पूर्णांक i;

	अगर (qdbm > 127)
		वापस -EINVAL;

	क्रम (i = 0; i < TXP_NUM_RATES; i++)
		pi->tx_user_target[i] = (u8) qdbm;

	pi->txpwroverride = false;

	अगर (pi->sh->up) अणु
		अगर (!SCAN_INPROG_PHY(pi)) अणु
			bool suspend;

			suspend = (0 == (bcma_पढ़ो32(pi->d11core,
						     D11REGOFFS(maccontrol)) &
					 MCTL_EN_MAC));

			अगर (!suspend)
				wlapi_suspend_mac_and_रुको(pi->sh->physhim);

			wlc_phy_txघातer_recalc_target(pi);
			wlc_phy_cal_txघातer_recalc_sw(pi);

			अगर (!suspend)
				wlapi_enable_mac(pi->sh->physhim);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

व्योम
wlc_phy_txघातer_sromlimit(काष्ठा brcms_phy_pub *ppi, uपूर्णांक channel, u8 *min_pwr,
			  u8 *max_pwr, पूर्णांक txp_rate_idx)
अणु
	काष्ठा brcms_phy *pi = container_of(ppi, काष्ठा brcms_phy, pubpi_ro);
	uपूर्णांक i;

	*min_pwr = pi->min_txघातer * BRCMS_TXPWR_DB_FACTOR;

	अगर (ISNPHY(pi)) अणु
		अगर (txp_rate_idx < 0)
			txp_rate_idx = TXP_FIRST_CCK;
		wlc_phy_txघातer_sromlimit_get_nphy(pi, channel, max_pwr,
						   (u8) txp_rate_idx);

	पूर्ण अन्यथा अगर ((channel <= CH_MAX_2G_CHANNEL)) अणु
		अगर (txp_rate_idx < 0)
			txp_rate_idx = TXP_FIRST_CCK;
		*max_pwr = pi->tx_srom_max_rate_2g[txp_rate_idx];
	पूर्ण अन्यथा अणु

		*max_pwr = BRCMS_TXPWR_MAX;

		अगर (txp_rate_idx < 0)
			txp_rate_idx = TXP_FIRST_OFDM;

		क्रम (i = 0; i < ARRAY_SIZE(chan_info_all); i++) अणु
			अगर (channel == chan_info_all[i].chan)
				अवरोध;
		पूर्ण

		अगर (pi->hwtxpwr) अणु
			*max_pwr = pi->hwtxpwr[i];
		पूर्ण अन्यथा अणु

			अगर ((i >= FIRST_MID_5G_CHAN) && (i <= LAST_MID_5G_CHAN))
				*max_pwr =
				    pi->tx_srom_max_rate_5g_mid[txp_rate_idx];
			अगर ((i >= FIRST_HIGH_5G_CHAN)
			    && (i <= LAST_HIGH_5G_CHAN))
				*max_pwr =
				    pi->tx_srom_max_rate_5g_hi[txp_rate_idx];
			अगर ((i >= FIRST_LOW_5G_CHAN) && (i <= LAST_LOW_5G_CHAN))
				*max_pwr =
				    pi->tx_srom_max_rate_5g_low[txp_rate_idx];
		पूर्ण
	पूर्ण
पूर्ण

व्योम
wlc_phy_txघातer_sromlimit_max_get(काष्ठा brcms_phy_pub *ppi, uपूर्णांक chan,
				  u8 *max_txpwr, u8 *min_txpwr)
अणु
	काष्ठा brcms_phy *pi = container_of(ppi, काष्ठा brcms_phy, pubpi_ro);
	u8 tx_pwr_max = 0;
	u8 tx_pwr_min = 255;
	u8 max_num_rate;
	u8 maxtxpwr, mपूर्णांकxpwr, rate, pactrl;

	pactrl = 0;

	max_num_rate = ISNPHY(pi) ? TXP_NUM_RATES :
		       ISLCNPHY(pi) ? (TXP_LAST_SISO_MCS_20 +
				       1) : (TXP_LAST_OFDM + 1);

	क्रम (rate = 0; rate < max_num_rate; rate++) अणु

		wlc_phy_txघातer_sromlimit(ppi, chan, &mपूर्णांकxpwr, &maxtxpwr,
					  rate);

		maxtxpwr = (maxtxpwr > pactrl) ? (maxtxpwr - pactrl) : 0;

		maxtxpwr = (maxtxpwr > 6) ? (maxtxpwr - 6) : 0;

		tx_pwr_max = max(tx_pwr_max, maxtxpwr);
		tx_pwr_min = min(tx_pwr_min, maxtxpwr);
	पूर्ण
	*max_txpwr = tx_pwr_max;
	*min_txpwr = tx_pwr_min;
पूर्ण

व्योम
wlc_phy_txघातer_boardlimit_band(काष्ठा brcms_phy_pub *ppi, uपूर्णांक bandunit,
				s32 *max_pwr, s32 *min_pwr, u32 *step_pwr)
अणु
	वापस;
पूर्ण

u8 wlc_phy_txघातer_get_target_min(काष्ठा brcms_phy_pub *ppi)
अणु
	काष्ठा brcms_phy *pi = container_of(ppi, काष्ठा brcms_phy, pubpi_ro);

	वापस pi->tx_घातer_min;
पूर्ण

u8 wlc_phy_txघातer_get_target_max(काष्ठा brcms_phy_pub *ppi)
अणु
	काष्ठा brcms_phy *pi = container_of(ppi, काष्ठा brcms_phy, pubpi_ro);

	वापस pi->tx_घातer_max;
पूर्ण

अटल s8 wlc_phy_env_measure_vbat(काष्ठा brcms_phy *pi)
अणु
	अगर (ISLCNPHY(pi))
		वापस wlc_lcnphy_vbatsense(pi, 0);
	अन्यथा
		वापस 0;
पूर्ण

अटल s8 wlc_phy_env_measure_temperature(काष्ठा brcms_phy *pi)
अणु
	अगर (ISLCNPHY(pi))
		वापस wlc_lcnphy_tempsense_degree(pi, 0);
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम wlc_phy_upd_env_txpwr_rate_limits(काष्ठा brcms_phy *pi, u32 band)
अणु
	u8 i;

	क्रम (i = 0; i < TXP_NUM_RATES; i++)
		pi->txpwr_env_limit[i] = BRCMS_TXPWR_MAX;

	wlc_phy_env_measure_vbat(pi);
	wlc_phy_env_measure_temperature(pi);
पूर्ण

अटल s8
wlc_user_txpwr_antport_to_rfport(काष्ठा brcms_phy *pi, uपूर्णांक chan, u32 band,
				 u8 rate)
अणु
	वापस 0;
पूर्ण

व्योम wlc_phy_txघातer_recalc_target(काष्ठा brcms_phy *pi)
अणु
	u8 maxtxpwr, mपूर्णांकxpwr, rate, pactrl;
	uपूर्णांक target_chan;
	u8 tx_pwr_target[TXP_NUM_RATES];
	u8 tx_pwr_max = 0;
	u8 tx_pwr_min = 255;
	u8 tx_pwr_max_rate_ind = 0;
	u8 max_num_rate;
	u8 start_rate = 0;
	u16 chspec;
	u32 band = CHSPEC2BAND(pi->radio_chanspec);
	व्योम (*txpwr_recalc_fn)(काष्ठा brcms_phy *) = शून्य;

	chspec = pi->radio_chanspec;
	अगर (CHSPEC_CTL_SB(chspec) == WL_CHANSPEC_CTL_SB_NONE)
		target_chan = CHSPEC_CHANNEL(chspec);
	अन्यथा अगर (CHSPEC_CTL_SB(chspec) == WL_CHANSPEC_CTL_SB_UPPER)
		target_chan = upper_20_sb(CHSPEC_CHANNEL(chspec));
	अन्यथा
		target_chan = lower_20_sb(CHSPEC_CHANNEL(chspec));

	pactrl = 0;
	अगर (ISLCNPHY(pi)) अणु
		u32 offset_mcs, i;

		अगर (CHSPEC_IS40(pi->radio_chanspec)) अणु
			offset_mcs = pi->mcs40_po;
			क्रम (i = TXP_FIRST_SISO_MCS_20;
			     i <= TXP_LAST_SISO_MCS_20; i++) अणु
				pi->tx_srom_max_rate_2g[i - 8] =
					pi->tx_srom_max_2g -
					((offset_mcs & 0xf) * 2);
				offset_mcs >>= 4;
			पूर्ण
		पूर्ण अन्यथा अणु
			offset_mcs = pi->mcs20_po;
			क्रम (i = TXP_FIRST_SISO_MCS_20;
			     i <= TXP_LAST_SISO_MCS_20; i++) अणु
				pi->tx_srom_max_rate_2g[i - 8] =
					pi->tx_srom_max_2g -
					((offset_mcs & 0xf) * 2);
				offset_mcs >>= 4;
			पूर्ण
		पूर्ण
	पूर्ण

	max_num_rate = ((ISNPHY(pi)) ? (TXP_NUM_RATES) :
			((ISLCNPHY(pi)) ?
			 (TXP_LAST_SISO_MCS_20 + 1) : (TXP_LAST_OFDM + 1)));

	wlc_phy_upd_env_txpwr_rate_limits(pi, band);

	क्रम (rate = start_rate; rate < max_num_rate; rate++) अणु

		tx_pwr_target[rate] = pi->tx_user_target[rate];

		अगर (pi->user_txpwr_at_rfport)
			tx_pwr_target[rate] +=
				wlc_user_txpwr_antport_to_rfport(pi,
								 target_chan,
								 band,
								 rate);

		wlc_phy_txघातer_sromlimit((काष्ठा brcms_phy_pub *) pi,
					  target_chan,
					  &mपूर्णांकxpwr, &maxtxpwr, rate);

		maxtxpwr = min(maxtxpwr, pi->txpwr_limit[rate]);

		maxtxpwr = (maxtxpwr > pactrl) ? (maxtxpwr - pactrl) : 0;

		maxtxpwr = (maxtxpwr > 6) ? (maxtxpwr - 6) : 0;

		maxtxpwr = min(maxtxpwr, tx_pwr_target[rate]);

		अगर (pi->txpwr_percent <= 100)
			maxtxpwr = (maxtxpwr * pi->txpwr_percent) / 100;

		tx_pwr_target[rate] = max(maxtxpwr, mपूर्णांकxpwr);

		tx_pwr_target[rate] =
			min(tx_pwr_target[rate], pi->txpwr_env_limit[rate]);

		अगर (tx_pwr_target[rate] > tx_pwr_max)
			tx_pwr_max_rate_ind = rate;

		tx_pwr_max = max(tx_pwr_max, tx_pwr_target[rate]);
		tx_pwr_min = min(tx_pwr_min, tx_pwr_target[rate]);
	पूर्ण

	स_रखो(pi->tx_घातer_offset, 0, माप(pi->tx_घातer_offset));
	pi->tx_घातer_max = tx_pwr_max;
	pi->tx_घातer_min = tx_pwr_min;
	pi->tx_घातer_max_rate_ind = tx_pwr_max_rate_ind;
	क्रम (rate = 0; rate < max_num_rate; rate++) अणु

		pi->tx_घातer_target[rate] = tx_pwr_target[rate];

		अगर (!pi->hwpwrctrl || ISNPHY(pi))
			pi->tx_घातer_offset[rate] =
				pi->tx_घातer_max - pi->tx_घातer_target[rate];
		अन्यथा
			pi->tx_घातer_offset[rate] =
				pi->tx_घातer_target[rate] - pi->tx_घातer_min;
	पूर्ण

	txpwr_recalc_fn = pi->pi_fptr.txpwrrecalc;
	अगर (txpwr_recalc_fn)
		(*txpwr_recalc_fn)(pi);
पूर्ण

अटल व्योम
wlc_phy_txघातer_reg_limit_calc(काष्ठा brcms_phy *pi, काष्ठा txpwr_limits *txpwr,
			       u16 chanspec)
अणु
	u8 पंचांगp_txpwr_limit[2 * BRCMS_NUM_RATES_OFDM];
	u8 *txpwr_ptr1 = शून्य, *txpwr_ptr2 = शून्य;
	पूर्णांक rate_start_index = 0, rate1, rate2, k;

	क्रम (rate1 = WL_TX_POWER_CCK_FIRST, rate2 = 0;
	     rate2 < WL_TX_POWER_CCK_NUM; rate1++, rate2++)
		pi->txpwr_limit[rate1] = txpwr->cck[rate2];

	क्रम (rate1 = WL_TX_POWER_OFDM_FIRST, rate2 = 0;
	     rate2 < WL_TX_POWER_OFDM_NUM; rate1++, rate2++)
		pi->txpwr_limit[rate1] = txpwr->ofdm[rate2];

	अगर (ISNPHY(pi)) अणु

		क्रम (k = 0; k < 4; k++) अणु
			चयन (k) अणु
			हाल 0:

				txpwr_ptr1 = txpwr->mcs_20_siso;
				txpwr_ptr2 = txpwr->ofdm;
				rate_start_index = WL_TX_POWER_OFDM_FIRST;
				अवरोध;
			हाल 1:

				txpwr_ptr1 = txpwr->mcs_20_cdd;
				txpwr_ptr2 = txpwr->ofdm_cdd;
				rate_start_index = WL_TX_POWER_OFDM20_CDD_FIRST;
				अवरोध;
			हाल 2:

				txpwr_ptr1 = txpwr->mcs_40_siso;
				txpwr_ptr2 = txpwr->ofdm_40_siso;
				rate_start_index =
					WL_TX_POWER_OFDM40_SISO_FIRST;
				अवरोध;
			हाल 3:

				txpwr_ptr1 = txpwr->mcs_40_cdd;
				txpwr_ptr2 = txpwr->ofdm_40_cdd;
				rate_start_index = WL_TX_POWER_OFDM40_CDD_FIRST;
				अवरोध;
			पूर्ण

			क्रम (rate2 = 0; rate2 < BRCMS_NUM_RATES_OFDM;
			     rate2++) अणु
				पंचांगp_txpwr_limit[rate2] = 0;
				पंचांगp_txpwr_limit[BRCMS_NUM_RATES_OFDM + rate2] =
					txpwr_ptr1[rate2];
			पूर्ण
			wlc_phy_mcs_to_ofdm_घातers_nphy(
				पंचांगp_txpwr_limit, 0,
				BRCMS_NUM_RATES_OFDM -
				1, BRCMS_NUM_RATES_OFDM);
			क्रम (rate1 = rate_start_index, rate2 = 0;
			     rate2 < BRCMS_NUM_RATES_OFDM; rate1++, rate2++)
				pi->txpwr_limit[rate1] =
					min(txpwr_ptr2[rate2],
					    पंचांगp_txpwr_limit[rate2]);
		पूर्ण

		क्रम (k = 0; k < 4; k++) अणु
			चयन (k) अणु
			हाल 0:

				txpwr_ptr1 = txpwr->ofdm;
				txpwr_ptr2 = txpwr->mcs_20_siso;
				rate_start_index = WL_TX_POWER_MCS20_SISO_FIRST;
				अवरोध;
			हाल 1:

				txpwr_ptr1 = txpwr->ofdm_cdd;
				txpwr_ptr2 = txpwr->mcs_20_cdd;
				rate_start_index = WL_TX_POWER_MCS20_CDD_FIRST;
				अवरोध;
			हाल 2:

				txpwr_ptr1 = txpwr->ofdm_40_siso;
				txpwr_ptr2 = txpwr->mcs_40_siso;
				rate_start_index = WL_TX_POWER_MCS40_SISO_FIRST;
				अवरोध;
			हाल 3:

				txpwr_ptr1 = txpwr->ofdm_40_cdd;
				txpwr_ptr2 = txpwr->mcs_40_cdd;
				rate_start_index = WL_TX_POWER_MCS40_CDD_FIRST;
				अवरोध;
			पूर्ण
			क्रम (rate2 = 0; rate2 < BRCMS_NUM_RATES_OFDM;
			     rate2++) अणु
				पंचांगp_txpwr_limit[rate2] = 0;
				पंचांगp_txpwr_limit[BRCMS_NUM_RATES_OFDM + rate2] =
					txpwr_ptr1[rate2];
			पूर्ण
			wlc_phy_ofdm_to_mcs_घातers_nphy(
				पंचांगp_txpwr_limit, 0,
				BRCMS_NUM_RATES_OFDM -
				1, BRCMS_NUM_RATES_OFDM);
			क्रम (rate1 = rate_start_index, rate2 = 0;
			     rate2 < BRCMS_NUM_RATES_MCS_1_STREAM;
			     rate1++, rate2++)
				pi->txpwr_limit[rate1] =
					min(txpwr_ptr2[rate2],
					    पंचांगp_txpwr_limit[rate2]);
		पूर्ण

		क्रम (k = 0; k < 2; k++) अणु
			चयन (k) अणु
			हाल 0:

				rate_start_index = WL_TX_POWER_MCS20_STBC_FIRST;
				txpwr_ptr1 = txpwr->mcs_20_stbc;
				अवरोध;
			हाल 1:

				rate_start_index = WL_TX_POWER_MCS40_STBC_FIRST;
				txpwr_ptr1 = txpwr->mcs_40_stbc;
				अवरोध;
			पूर्ण
			क्रम (rate1 = rate_start_index, rate2 = 0;
			     rate2 < BRCMS_NUM_RATES_MCS_1_STREAM;
			     rate1++, rate2++)
				pi->txpwr_limit[rate1] = txpwr_ptr1[rate2];
		पूर्ण

		क्रम (k = 0; k < 2; k++) अणु
			चयन (k) अणु
			हाल 0:

				rate_start_index = WL_TX_POWER_MCS20_SDM_FIRST;
				txpwr_ptr1 = txpwr->mcs_20_mimo;
				अवरोध;
			हाल 1:

				rate_start_index = WL_TX_POWER_MCS40_SDM_FIRST;
				txpwr_ptr1 = txpwr->mcs_40_mimo;
				अवरोध;
			पूर्ण
			क्रम (rate1 = rate_start_index, rate2 = 0;
			     rate2 < BRCMS_NUM_RATES_MCS_2_STREAM;
			     rate1++, rate2++)
				pi->txpwr_limit[rate1] = txpwr_ptr1[rate2];
		पूर्ण

		pi->txpwr_limit[WL_TX_POWER_MCS_32] = txpwr->mcs32;

		pi->txpwr_limit[WL_TX_POWER_MCS40_CDD_FIRST] =
			min(pi->txpwr_limit[WL_TX_POWER_MCS40_CDD_FIRST],
			    pi->txpwr_limit[WL_TX_POWER_MCS_32]);
		pi->txpwr_limit[WL_TX_POWER_MCS_32] =
			pi->txpwr_limit[WL_TX_POWER_MCS40_CDD_FIRST];
	पूर्ण
पूर्ण

व्योम wlc_phy_txpwr_percent_set(काष्ठा brcms_phy_pub *ppi, u8 txpwr_percent)
अणु
	काष्ठा brcms_phy *pi = container_of(ppi, काष्ठा brcms_phy, pubpi_ro);

	pi->txpwr_percent = txpwr_percent;
पूर्ण

व्योम wlc_phy_machwcap_set(काष्ठा brcms_phy_pub *ppi, u32 machwcap)
अणु
	काष्ठा brcms_phy *pi = container_of(ppi, काष्ठा brcms_phy, pubpi_ro);

	pi->sh->machwcap = machwcap;
पूर्ण

व्योम wlc_phy_runbist_config(काष्ठा brcms_phy_pub *ppi, bool start_end)
अणु
	काष्ठा brcms_phy *pi = container_of(ppi, काष्ठा brcms_phy, pubpi_ro);
	u16 rxc;
	rxc = 0;

	अगर (start_end == ON) अणु
		अगर (!ISNPHY(pi))
			वापस;

		अगर (NREV_IS(pi->pubpi.phy_rev, 3)
		    || NREV_IS(pi->pubpi.phy_rev, 4)) अणु
			bcma_wflush16(pi->d11core, D11REGOFFS(phyregaddr),
				      0xa0);
			bcma_set16(pi->d11core, D11REGOFFS(phyregdata),
				   0x1 << 15);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (NREV_IS(pi->pubpi.phy_rev, 3)
		    || NREV_IS(pi->pubpi.phy_rev, 4)) अणु
			bcma_wflush16(pi->d11core, D11REGOFFS(phyregaddr),
				      0xa0);
			bcma_ग_लिखो16(pi->d11core, D11REGOFFS(phyregdata), rxc);
		पूर्ण

		wlc_phy_por_inक्रमm(ppi);
	पूर्ण
पूर्ण

व्योम
wlc_phy_txघातer_limit_set(काष्ठा brcms_phy_pub *ppi, काष्ठा txpwr_limits *txpwr,
			  u16 chanspec)
अणु
	काष्ठा brcms_phy *pi = container_of(ppi, काष्ठा brcms_phy, pubpi_ro);

	wlc_phy_txघातer_reg_limit_calc(pi, txpwr, chanspec);

	अगर (ISLCNPHY(pi)) अणु
		पूर्णांक i, j;
		क्रम (i = TXP_FIRST_OFDM_20_CDD, j = 0;
		     j < BRCMS_NUM_RATES_MCS_1_STREAM; i++, j++) अणु
			अगर (txpwr->mcs_20_siso[j])
				pi->txpwr_limit[i] = txpwr->mcs_20_siso[j];
			अन्यथा
				pi->txpwr_limit[i] = txpwr->ofdm[j];
		पूर्ण
	पूर्ण

	wlapi_suspend_mac_and_रुको(pi->sh->physhim);

	wlc_phy_txघातer_recalc_target(pi);
	wlc_phy_cal_txघातer_recalc_sw(pi);
	wlapi_enable_mac(pi->sh->physhim);
पूर्ण

व्योम wlc_phy_ofdm_rateset_war(काष्ठा brcms_phy_pub *pih, bool war)
अणु
	काष्ठा brcms_phy *pi = container_of(pih, काष्ठा brcms_phy, pubpi_ro);

	pi->ofdm_rateset_war = war;
पूर्ण

व्योम wlc_phy_bf_preempt_enable(काष्ठा brcms_phy_pub *pih, bool bf_preempt)
अणु
	काष्ठा brcms_phy *pi = container_of(pih, काष्ठा brcms_phy, pubpi_ro);

	pi->bf_preempt_4306 = bf_preempt;
पूर्ण

व्योम wlc_phy_txघातer_update_shm(काष्ठा brcms_phy *pi)
अणु
	पूर्णांक j;
	अगर (ISNPHY(pi))
		वापस;

	अगर (!pi->sh->clk)
		वापस;

	अगर (pi->hwpwrctrl) अणु
		u16 offset;

		wlapi_bmac_ग_लिखो_shm(pi->sh->physhim, M_TXPWR_MAX, 63);
		wlapi_bmac_ग_लिखो_shm(pi->sh->physhim, M_TXPWR_N,
				     1 << NUM_TSSI_FRAMES);

		wlapi_bmac_ग_लिखो_shm(pi->sh->physhim, M_TXPWR_TARGET,
				     pi->tx_घातer_min << NUM_TSSI_FRAMES);

		wlapi_bmac_ग_लिखो_shm(pi->sh->physhim, M_TXPWR_CUR,
				     pi->hwpwr_txcur);

		क्रम (j = TXP_FIRST_OFDM; j <= TXP_LAST_OFDM; j++) अणु
			अटल स्थिर u8 ucode_ofdm_rates[] = अणु
				0x0c, 0x12, 0x18, 0x24, 0x30, 0x48, 0x60, 0x6c
			पूर्ण;
			offset = wlapi_bmac_rate_shm_offset(
				pi->sh->physhim,
				ucode_ofdm_rates[j - TXP_FIRST_OFDM]);
			wlapi_bmac_ग_लिखो_shm(pi->sh->physhim, offset + 6,
					     pi->tx_घातer_offset[j]);
			wlapi_bmac_ग_लिखो_shm(pi->sh->physhim, offset + 14,
					     -(pi->tx_घातer_offset[j] / 2));
		पूर्ण

		wlapi_bmac_mhf(pi->sh->physhim, MHF2, MHF2_HWPWRCTL,
			       MHF2_HWPWRCTL, BRCM_BAND_ALL);
	पूर्ण अन्यथा अणु
		पूर्णांक i;

		क्रम (i = TXP_FIRST_OFDM; i <= TXP_LAST_OFDM; i++)
			pi->tx_घातer_offset[i] =
				(u8) roundup(pi->tx_घातer_offset[i], 8);
		wlapi_bmac_ग_लिखो_shm(pi->sh->physhim, M_OFDM_OFFSET,
				     (u16)
				     ((pi->tx_घातer_offset[TXP_FIRST_OFDM]
				       + 7) >> 3));
	पूर्ण
पूर्ण

bool wlc_phy_txघातer_hw_ctrl_get(काष्ठा brcms_phy_pub *ppi)
अणु
	काष्ठा brcms_phy *pi = container_of(ppi, काष्ठा brcms_phy, pubpi_ro);

	अगर (ISNPHY(pi))
		वापस pi->nphy_txpwrctrl;
	अन्यथा
		वापस pi->hwpwrctrl;
पूर्ण

व्योम wlc_phy_txघातer_hw_ctrl_set(काष्ठा brcms_phy_pub *ppi, bool hwpwrctrl)
अणु
	काष्ठा brcms_phy *pi = container_of(ppi, काष्ठा brcms_phy, pubpi_ro);
	bool suspend;

	अगर (!pi->hwpwrctrl_capable)
		वापस;

	pi->hwpwrctrl = hwpwrctrl;
	pi->nphy_txpwrctrl = hwpwrctrl;
	pi->txpwrctrl = hwpwrctrl;

	अगर (ISNPHY(pi)) अणु
		suspend = (0 == (bcma_पढ़ो32(pi->d11core,
					     D11REGOFFS(maccontrol)) &
				 MCTL_EN_MAC));
		अगर (!suspend)
			wlapi_suspend_mac_and_रुको(pi->sh->physhim);

		wlc_phy_txpwrctrl_enable_nphy(pi, pi->nphy_txpwrctrl);
		अगर (pi->nphy_txpwrctrl == PHY_TPC_HW_OFF)
			wlc_phy_txpwr_fixघातer_nphy(pi);
		अन्यथा
			mod_phy_reg(pi, 0x1e7, (0x7f << 0),
				    pi->saved_txpwr_idx);

		अगर (!suspend)
			wlapi_enable_mac(pi->sh->physhim);
	पूर्ण
पूर्ण

व्योम wlc_phy_txघातer_ipa_upd(काष्ठा brcms_phy *pi)
अणु

	अगर (NREV_GE(pi->pubpi.phy_rev, 3)) अणु
		pi->ipa2g_on = (pi->srom_fem2g.extpagain == 2);
		pi->ipa5g_on = (pi->srom_fem5g.extpagain == 2);
	पूर्ण अन्यथा अणु
		pi->ipa2g_on = false;
		pi->ipa5g_on = false;
	पूर्ण
पूर्ण

अटल u32 wlc_phy_txघातer_est_घातer_nphy(काष्ठा brcms_phy *pi)
अणु
	s16 tx0_status, tx1_status;
	u16 estPower1, estPower2;
	u8 pwr0, pwr1, adj_pwr0, adj_pwr1;
	u32 est_pwr;

	estPower1 = पढ़ो_phy_reg(pi, 0x118);
	estPower2 = पढ़ो_phy_reg(pi, 0x119);

	अगर ((estPower1 & (0x1 << 8)) == (0x1 << 8))
		pwr0 = (u8) (estPower1 & (0xff << 0)) >> 0;
	अन्यथा
		pwr0 = 0x80;

	अगर ((estPower2 & (0x1 << 8)) == (0x1 << 8))
		pwr1 = (u8) (estPower2 & (0xff << 0)) >> 0;
	अन्यथा
		pwr1 = 0x80;

	tx0_status = पढ़ो_phy_reg(pi, 0x1ed);
	tx1_status = पढ़ो_phy_reg(pi, 0x1ee);

	अगर ((tx0_status & (0x1 << 15)) == (0x1 << 15))
		adj_pwr0 = (u8) (tx0_status & (0xff << 0)) >> 0;
	अन्यथा
		adj_pwr0 = 0x80;
	अगर ((tx1_status & (0x1 << 15)) == (0x1 << 15))
		adj_pwr1 = (u8) (tx1_status & (0xff << 0)) >> 0;
	अन्यथा
		adj_pwr1 = 0x80;

	est_pwr = (u32) ((pwr0 << 24) | (pwr1 << 16) | (adj_pwr0 << 8) |
			 adj_pwr1);

	वापस est_pwr;
पूर्ण

व्योम
wlc_phy_txघातer_get_current(काष्ठा brcms_phy_pub *ppi, काष्ठा tx_घातer *घातer,
			    uपूर्णांक channel)
अणु
	काष्ठा brcms_phy *pi = container_of(ppi, काष्ठा brcms_phy, pubpi_ro);
	uपूर्णांक rate, num_rates;
	u8 min_pwr, max_pwr;

#अगर WL_TX_POWER_RATES != TXP_NUM_RATES
#त्रुटि "struct tx_power out of sync with this fn"
#पूर्ण_अगर

	अगर (ISNPHY(pi)) अणु
		घातer->rf_cores = 2;
		घातer->flags |= (WL_TX_POWER_F_MIMO);
		अगर (pi->nphy_txpwrctrl == PHY_TPC_HW_ON)
			घातer->flags |=
				(WL_TX_POWER_F_ENABLED | WL_TX_POWER_F_HW);
	पूर्ण अन्यथा अगर (ISLCNPHY(pi)) अणु
		घातer->rf_cores = 1;
		घातer->flags |= (WL_TX_POWER_F_SISO);
		अगर (pi->radiopwr_override == RADIOPWR_OVERRIDE_DEF)
			घातer->flags |= WL_TX_POWER_F_ENABLED;
		अगर (pi->hwpwrctrl)
			घातer->flags |= WL_TX_POWER_F_HW;
	पूर्ण

	num_rates = ((ISNPHY(pi)) ? (TXP_NUM_RATES) :
		     ((ISLCNPHY(pi)) ?
		      (TXP_LAST_OFDM_20_CDD + 1) : (TXP_LAST_OFDM + 1)));

	क्रम (rate = 0; rate < num_rates; rate++) अणु
		घातer->user_limit[rate] = pi->tx_user_target[rate];
		wlc_phy_txघातer_sromlimit(ppi, channel, &min_pwr, &max_pwr,
					  rate);
		घातer->board_limit[rate] = (u8) max_pwr;
		घातer->target[rate] = pi->tx_घातer_target[rate];
	पूर्ण

	अगर (ISNPHY(pi)) अणु
		u32 est_pout;

		wlapi_suspend_mac_and_रुको(pi->sh->physhim);
		wlc_phyreg_enter((काष्ठा brcms_phy_pub *) pi);
		est_pout = wlc_phy_txघातer_est_घातer_nphy(pi);
		wlc_phyreg_निकास((काष्ठा brcms_phy_pub *) pi);
		wlapi_enable_mac(pi->sh->physhim);

		घातer->est_Pout[0] = (est_pout >> 8) & 0xff;
		घातer->est_Pout[1] = est_pout & 0xff;

		घातer->est_Pout_act[0] = est_pout >> 24;
		घातer->est_Pout_act[1] = (est_pout >> 16) & 0xff;

		अगर (घातer->est_Pout[0] == 0x80)
			घातer->est_Pout[0] = 0;
		अगर (घातer->est_Pout[1] == 0x80)
			घातer->est_Pout[1] = 0;

		अगर (घातer->est_Pout_act[0] == 0x80)
			घातer->est_Pout_act[0] = 0;
		अगर (घातer->est_Pout_act[1] == 0x80)
			घातer->est_Pout_act[1] = 0;

		घातer->est_Pout_cck = 0;

		घातer->tx_घातer_max[0] = pi->tx_घातer_max;
		घातer->tx_घातer_max[1] = pi->tx_घातer_max;

		घातer->tx_घातer_max_rate_ind[0] = pi->tx_घातer_max_rate_ind;
		घातer->tx_घातer_max_rate_ind[1] = pi->tx_घातer_max_rate_ind;
	पूर्ण अन्यथा अगर (pi->hwpwrctrl && pi->sh->up) अणु

		wlc_phyreg_enter(ppi);
		अगर (ISLCNPHY(pi)) अणु

			घातer->tx_घातer_max[0] = pi->tx_घातer_max;
			घातer->tx_घातer_max[1] = pi->tx_घातer_max;

			घातer->tx_घातer_max_rate_ind[0] =
				pi->tx_घातer_max_rate_ind;
			घातer->tx_घातer_max_rate_ind[1] =
				pi->tx_घातer_max_rate_ind;

			अगर (wlc_phy_tpc_isenabled_lcnphy(pi))
				घातer->flags |=
					(WL_TX_POWER_F_HW |
					 WL_TX_POWER_F_ENABLED);
			अन्यथा
				घातer->flags &=
					~(WL_TX_POWER_F_HW |
					  WL_TX_POWER_F_ENABLED);

			wlc_lcnphy_get_tssi(pi, (s8 *) &घातer->est_Pout[0],
					    (s8 *) &घातer->est_Pout_cck);
		पूर्ण
		wlc_phyreg_निकास(ppi);
	पूर्ण
पूर्ण

व्योम wlc_phy_antsel_type_set(काष्ठा brcms_phy_pub *ppi, u8 antsel_type)
अणु
	काष्ठा brcms_phy *pi = container_of(ppi, काष्ठा brcms_phy, pubpi_ro);

	pi->antsel_type = antsel_type;
पूर्ण

bool wlc_phy_test_ison(काष्ठा brcms_phy_pub *ppi)
अणु
	काष्ठा brcms_phy *pi = container_of(ppi, काष्ठा brcms_phy, pubpi_ro);

	वापस pi->phytest_on;
पूर्ण

व्योम wlc_phy_ant_rxभाग_set(काष्ठा brcms_phy_pub *ppi, u8 val)
अणु
	काष्ठा brcms_phy *pi = container_of(ppi, काष्ठा brcms_phy, pubpi_ro);
	bool suspend;

	pi->sh->rx_antभाग = val;

	अगर (!(ISNPHY(pi) && D11REV_IS(pi->sh->corerev, 16))) अणु
		अगर (val > ANT_RX_DIV_FORCE_1)
			wlapi_bmac_mhf(pi->sh->physhim, MHF1, MHF1_ANTDIV,
				       MHF1_ANTDIV, BRCM_BAND_ALL);
		अन्यथा
			wlapi_bmac_mhf(pi->sh->physhim, MHF1, MHF1_ANTDIV, 0,
				       BRCM_BAND_ALL);
	पूर्ण

	अगर (ISNPHY(pi))
		वापस;

	अगर (!pi->sh->clk)
		वापस;

	suspend = (0 == (bcma_पढ़ो32(pi->d11core, D11REGOFFS(maccontrol)) &
			 MCTL_EN_MAC));
	अगर (!suspend)
		wlapi_suspend_mac_and_रुको(pi->sh->physhim);

	अगर (ISLCNPHY(pi)) अणु
		अगर (val > ANT_RX_DIV_FORCE_1) अणु
			mod_phy_reg(pi, 0x410, (0x1 << 1), 0x01 << 1);
			mod_phy_reg(pi, 0x410,
				    (0x1 << 0),
				    ((ANT_RX_DIV_START_1 == val) ? 1 : 0) << 0);
		पूर्ण अन्यथा अणु
			mod_phy_reg(pi, 0x410, (0x1 << 1), 0x00 << 1);
			mod_phy_reg(pi, 0x410, (0x1 << 0), (u16) val << 0);
		पूर्ण
	पूर्ण

	अगर (!suspend)
		wlapi_enable_mac(pi->sh->physhim);

	वापस;
पूर्ण

अटल bool
wlc_phy_noise_calc_phy(काष्ठा brcms_phy *pi, u32 *cmplx_pwr, s8 *pwr_ant)
अणु
	s8 cmplx_pwr_dbm[PHY_CORE_MAX];
	u8 i;

	स_रखो((u8 *) cmplx_pwr_dbm, 0, माप(cmplx_pwr_dbm));
	wlc_phy_compute_dB(cmplx_pwr, cmplx_pwr_dbm, pi->pubpi.phy_corक्रमागत);

	क्रम (i = 0; i < pi->pubpi.phy_corक्रमागत; i++) अणु
		अगर (NREV_GE(pi->pubpi.phy_rev, 3))
			cmplx_pwr_dbm[i] += (s8) PHY_NOISE_OFFSETFACT_4322;
		अन्यथा

			cmplx_pwr_dbm[i] += (s8) (16 - (15) * 3 - 70);
	पूर्ण

	क्रम (i = 0; i < pi->pubpi.phy_corक्रमागत; i++) अणु
		pi->nphy_noise_win[i][pi->nphy_noise_index] = cmplx_pwr_dbm[i];
		pwr_ant[i] = cmplx_pwr_dbm[i];
	पूर्ण
	pi->nphy_noise_index =
		MODINC_POW2(pi->nphy_noise_index, PHY_NOISE_WINDOW_SZ);
	वापस true;
पूर्ण

अटल व्योम wlc_phy_noise_cb(काष्ठा brcms_phy *pi, u8 channel, s8 noise_dbm)
अणु
	अगर (!pi->phynoise_state)
		वापस;

	अगर (pi->phynoise_state & PHY_NOISE_STATE_MON) अणु
		अगर (pi->phynoise_chan_watchकरोg == channel) अणु
			pi->sh->phy_noise_winकरोw[pi->sh->phy_noise_index] =
				noise_dbm;
			pi->sh->phy_noise_index =
				MODINC(pi->sh->phy_noise_index, MA_WINDOW_SZ);
		पूर्ण
		pi->phynoise_state &= ~PHY_NOISE_STATE_MON;
	पूर्ण

	अगर (pi->phynoise_state & PHY_NOISE_STATE_EXTERNAL)
		pi->phynoise_state &= ~PHY_NOISE_STATE_EXTERNAL;

पूर्ण

अटल s8 wlc_phy_noise_पढ़ो_shmem(काष्ठा brcms_phy *pi)
अणु
	u32 cmplx_pwr[PHY_CORE_MAX];
	s8 noise_dbm_ant[PHY_CORE_MAX];
	u16 lo, hi;
	u32 cmplx_pwr_tot = 0;
	s8 noise_dbm = PHY_NOISE_FIXED_VAL_NPHY;
	u8 idx, core;

	स_रखो((u8 *) cmplx_pwr, 0, माप(cmplx_pwr));
	स_रखो((u8 *) noise_dbm_ant, 0, माप(noise_dbm_ant));

	क्रम (idx = 0, core = 0; core < pi->pubpi.phy_corक्रमागत; idx += 2,
	     core++) अणु
		lo = wlapi_bmac_पढ़ो_shm(pi->sh->physhim, M_PWRIND_MAP(idx));
		hi = wlapi_bmac_पढ़ो_shm(pi->sh->physhim,
					 M_PWRIND_MAP(idx + 1));
		cmplx_pwr[core] = (hi << 16) + lo;
		cmplx_pwr_tot += cmplx_pwr[core];
		अगर (cmplx_pwr[core] == 0)
			noise_dbm_ant[core] = PHY_NOISE_FIXED_VAL_NPHY;
		अन्यथा
			cmplx_pwr[core] >>= PHY_NOISE_SAMPLE_LOG_NUM_UCODE;
	पूर्ण

	अगर (cmplx_pwr_tot != 0)
		wlc_phy_noise_calc_phy(pi, cmplx_pwr, noise_dbm_ant);

	क्रम (core = 0; core < pi->pubpi.phy_corक्रमागत; core++) अणु
		pi->nphy_noise_win[core][pi->nphy_noise_index] =
			noise_dbm_ant[core];

		अगर (noise_dbm_ant[core] > noise_dbm)
			noise_dbm = noise_dbm_ant[core];
	पूर्ण
	pi->nphy_noise_index =
		MODINC_POW2(pi->nphy_noise_index, PHY_NOISE_WINDOW_SZ);

	वापस noise_dbm;

पूर्ण

व्योम wlc_phy_noise_sample_पूर्णांकr(काष्ठा brcms_phy_pub *pih)
अणु
	काष्ठा brcms_phy *pi = container_of(pih, काष्ठा brcms_phy, pubpi_ro);
	u16 jssi_aux;
	u8 channel = 0;
	s8 noise_dbm = PHY_NOISE_FIXED_VAL_NPHY;

	अगर (ISLCNPHY(pi)) अणु
		u32 cmplx_pwr, cmplx_pwr0, cmplx_pwr1;
		u16 lo, hi;
		s32 pwr_offset_dB, gain_dB;
		u16 status_0, status_1;

		jssi_aux = wlapi_bmac_पढ़ो_shm(pi->sh->physhim, M_JSSI_AUX);
		channel = jssi_aux & D11_CURCHANNEL_MAX;

		lo = wlapi_bmac_पढ़ो_shm(pi->sh->physhim, M_PWRIND_MAP0);
		hi = wlapi_bmac_पढ़ो_shm(pi->sh->physhim, M_PWRIND_MAP1);
		cmplx_pwr0 = (hi << 16) + lo;

		lo = wlapi_bmac_पढ़ो_shm(pi->sh->physhim, M_PWRIND_MAP2);
		hi = wlapi_bmac_पढ़ो_shm(pi->sh->physhim, M_PWRIND_MAP3);
		cmplx_pwr1 = (hi << 16) + lo;
		cmplx_pwr = (cmplx_pwr0 + cmplx_pwr1) >> 6;

		status_0 = 0x44;
		status_1 = wlapi_bmac_पढ़ो_shm(pi->sh->physhim, M_JSSI_0);
		अगर ((cmplx_pwr > 0 && cmplx_pwr < 500)
		    && ((status_1 & 0xc000) == 0x4000)) अणु

			wlc_phy_compute_dB(&cmplx_pwr, &noise_dbm,
					   pi->pubpi.phy_corक्रमागत);
			pwr_offset_dB = (पढ़ो_phy_reg(pi, 0x434) & 0xFF);
			अगर (pwr_offset_dB > 127)
				pwr_offset_dB -= 256;

			noise_dbm += (s8) (pwr_offset_dB - 30);

			gain_dB = (status_0 & 0x1ff);
			noise_dbm -= (s8) (gain_dB);
		पूर्ण अन्यथा अणु
			noise_dbm = PHY_NOISE_FIXED_VAL_LCNPHY;
		पूर्ण
	पूर्ण अन्यथा अगर (ISNPHY(pi)) अणु

		jssi_aux = wlapi_bmac_पढ़ो_shm(pi->sh->physhim, M_JSSI_AUX);
		channel = jssi_aux & D11_CURCHANNEL_MAX;

		noise_dbm = wlc_phy_noise_पढ़ो_shmem(pi);
	पूर्ण

	wlc_phy_noise_cb(pi, channel, noise_dbm);

पूर्ण

अटल व्योम
wlc_phy_noise_sample_request(काष्ठा brcms_phy_pub *pih, u8 reason, u8 ch)
अणु
	काष्ठा brcms_phy *pi = container_of(pih, काष्ठा brcms_phy, pubpi_ro);
	s8 noise_dbm = PHY_NOISE_FIXED_VAL_NPHY;
	bool sampling_in_progress = (pi->phynoise_state != 0);
	bool रुको_क्रम_पूर्णांकr = true;

	चयन (reason) अणु
	हाल PHY_NOISE_SAMPLE_MON:
		pi->phynoise_chan_watchकरोg = ch;
		pi->phynoise_state |= PHY_NOISE_STATE_MON;
		अवरोध;

	हाल PHY_NOISE_SAMPLE_EXTERNAL:
		pi->phynoise_state |= PHY_NOISE_STATE_EXTERNAL;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	अगर (sampling_in_progress)
		वापस;

	pi->phynoise_now = pi->sh->now;

	अगर (pi->phy_fixed_noise) अणु
		अगर (ISNPHY(pi)) अणु
			pi->nphy_noise_win[WL_ANT_IDX_1][pi->nphy_noise_index] =
				PHY_NOISE_FIXED_VAL_NPHY;
			pi->nphy_noise_win[WL_ANT_IDX_2][pi->nphy_noise_index] =
				PHY_NOISE_FIXED_VAL_NPHY;
			pi->nphy_noise_index = MODINC_POW2(pi->nphy_noise_index,
							   PHY_NOISE_WINDOW_SZ);
			noise_dbm = PHY_NOISE_FIXED_VAL_NPHY;
		पूर्ण अन्यथा अणु
			noise_dbm = PHY_NOISE_FIXED_VAL;
		पूर्ण

		रुको_क्रम_पूर्णांकr = false;
		जाओ करोne;
	पूर्ण

	अगर (ISLCNPHY(pi)) अणु
		अगर (!pi->phynoise_polling
		    || (reason == PHY_NOISE_SAMPLE_EXTERNAL)) अणु
			wlapi_bmac_ग_लिखो_shm(pi->sh->physhim, M_JSSI_0, 0);
			wlapi_bmac_ग_लिखो_shm(pi->sh->physhim, M_PWRIND_MAP0, 0);
			wlapi_bmac_ग_लिखो_shm(pi->sh->physhim, M_PWRIND_MAP1, 0);
			wlapi_bmac_ग_लिखो_shm(pi->sh->physhim, M_PWRIND_MAP2, 0);
			wlapi_bmac_ग_लिखो_shm(pi->sh->physhim, M_PWRIND_MAP3, 0);

			bcma_set32(pi->d11core, D11REGOFFS(maccommand),
				   MCMD_BG_NOISE);
		पूर्ण अन्यथा अणु
			wlapi_suspend_mac_and_रुको(pi->sh->physhim);
			wlc_lcnphy_deaf_mode(pi, (bool) 0);
			noise_dbm = (s8) wlc_lcnphy_rx_संकेत_घातer(pi, 20);
			wlc_lcnphy_deaf_mode(pi, (bool) 1);
			wlapi_enable_mac(pi->sh->physhim);
			रुको_क्रम_पूर्णांकr = false;
		पूर्ण
	पूर्ण अन्यथा अगर (ISNPHY(pi)) अणु
		अगर (!pi->phynoise_polling
		    || (reason == PHY_NOISE_SAMPLE_EXTERNAL)) अणु

			wlapi_bmac_ग_लिखो_shm(pi->sh->physhim, M_PWRIND_MAP0, 0);
			wlapi_bmac_ग_लिखो_shm(pi->sh->physhim, M_PWRIND_MAP1, 0);
			wlapi_bmac_ग_लिखो_shm(pi->sh->physhim, M_PWRIND_MAP2, 0);
			wlapi_bmac_ग_लिखो_shm(pi->sh->physhim, M_PWRIND_MAP3, 0);

			bcma_set32(pi->d11core, D11REGOFFS(maccommand),
				   MCMD_BG_NOISE);
		पूर्ण अन्यथा अणु
			काष्ठा phy_iq_est est[PHY_CORE_MAX];
			u32 cmplx_pwr[PHY_CORE_MAX];
			s8 noise_dbm_ant[PHY_CORE_MAX];
			u16 log_num_samps, num_samps, classअगर_state = 0;
			u8 रुको_समय = 32;
			u8 रुको_crs = 0;
			u8 i;

			स_रखो((u8 *) est, 0, माप(est));
			स_रखो((u8 *) cmplx_pwr, 0, माप(cmplx_pwr));
			स_रखो((u8 *) noise_dbm_ant, 0, माप(noise_dbm_ant));

			log_num_samps = PHY_NOISE_SAMPLE_LOG_NUM_NPHY;
			num_samps = 1 << log_num_samps;

			wlapi_suspend_mac_and_रुको(pi->sh->physhim);
			classअगर_state = wlc_phy_classअगरier_nphy(pi, 0, 0);
			wlc_phy_classअगरier_nphy(pi, 3, 0);
			wlc_phy_rx_iq_est_nphy(pi, est, num_samps, रुको_समय,
					       रुको_crs);
			wlc_phy_classअगरier_nphy(pi, (0x7 << 0), classअगर_state);
			wlapi_enable_mac(pi->sh->physhim);

			क्रम (i = 0; i < pi->pubpi.phy_corक्रमागत; i++)
				cmplx_pwr[i] = (est[i].i_pwr + est[i].q_pwr) >>
					       log_num_samps;

			wlc_phy_noise_calc_phy(pi, cmplx_pwr, noise_dbm_ant);

			क्रम (i = 0; i < pi->pubpi.phy_corक्रमागत; i++) अणु
				pi->nphy_noise_win[i][pi->nphy_noise_index] =
					noise_dbm_ant[i];

				अगर (noise_dbm_ant[i] > noise_dbm)
					noise_dbm = noise_dbm_ant[i];
			पूर्ण
			pi->nphy_noise_index = MODINC_POW2(pi->nphy_noise_index,
							   PHY_NOISE_WINDOW_SZ);

			रुको_क्रम_पूर्णांकr = false;
		पूर्ण
	पूर्ण

करोne:

	अगर (!रुको_क्रम_पूर्णांकr)
		wlc_phy_noise_cb(pi, ch, noise_dbm);

पूर्ण

व्योम wlc_phy_noise_sample_request_बाह्यal(काष्ठा brcms_phy_pub *pih)
अणु
	u8 channel;

	channel = CHSPEC_CHANNEL(wlc_phy_chanspec_get(pih));

	wlc_phy_noise_sample_request(pih, PHY_NOISE_SAMPLE_EXTERNAL, channel);
पूर्ण

अटल स्थिर s8 lcnphy_gain_index_offset_क्रम_pkt_rssi[] = अणु
	8,
	8,
	8,
	8,
	8,
	8,
	8,
	9,
	10,
	8,
	8,
	7,
	7,
	1,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	1,
	1,
	0,
	0,
	0,
	0
पूर्ण;

व्योम wlc_phy_compute_dB(u32 *cmplx_pwr, s8 *p_cmplx_pwr_dB, u8 core)
अणु
	u8 msb, secondmsb, i;
	u32 पंचांगp;

	क्रम (i = 0; i < core; i++) अणु
		secondmsb = 0;
		पंचांगp = cmplx_pwr[i];
		msb = fls(पंचांगp);
		अगर (msb)
			secondmsb = (u8) ((पंचांगp >> (--msb - 1)) & 1);
		p_cmplx_pwr_dB[i] = (s8) (3 * msb + 2 * secondmsb);
	पूर्ण
पूर्ण

पूर्णांक wlc_phy_rssi_compute(काष्ठा brcms_phy_pub *pih,
			 काष्ठा d11rxhdr *rxh)
अणु
	पूर्णांक rssi = rxh->PhyRxStatus_1 & PRXS1_JSSI_MASK;
	uपूर्णांक radioid = pih->radioid;
	काष्ठा brcms_phy *pi = container_of(pih, काष्ठा brcms_phy, pubpi_ro);

	अगर ((pi->sh->corerev >= 11)
	    && !(rxh->RxStatus2 & RXS_PHYRXST_VALID)) अणु
		rssi = BRCMS_RSSI_INVALID;
		जाओ end;
	पूर्ण

	अगर (ISLCNPHY(pi)) अणु
		u8 gidx = (rxh->PhyRxStatus_2 & 0xFC00) >> 10;
		काष्ठा brcms_phy_lcnphy *pi_lcn = pi->u.pi_lcnphy;

		अगर (rssi > 127)
			rssi -= 256;

		rssi = rssi + lcnphy_gain_index_offset_क्रम_pkt_rssi[gidx];
		अगर ((rssi > -46) && (gidx > 18))
			rssi = rssi + 7;

		rssi = rssi + pi_lcn->lcnphy_pkteng_rssi_slope;

		rssi = rssi + 2;

	पूर्ण

	अगर (ISLCNPHY(pi)) अणु
		अगर (rssi > 127)
			rssi -= 256;
	पूर्ण अन्यथा अगर (radioid == BCM2055_ID || radioid == BCM2056_ID
		   || radioid == BCM2057_ID) अणु
		rssi = wlc_phy_rssi_compute_nphy(pi, rxh);
	पूर्ण

end:
	वापस rssi;
पूर्ण

व्योम wlc_phy_freqtrack_start(काष्ठा brcms_phy_pub *pih)
अणु
	वापस;
पूर्ण

व्योम wlc_phy_freqtrack_end(काष्ठा brcms_phy_pub *pih)
अणु
	वापस;
पूर्ण

व्योम wlc_phy_set_deaf(काष्ठा brcms_phy_pub *ppi, bool user_flag)
अणु
	काष्ठा brcms_phy *pi;
	pi = (काष्ठा brcms_phy *) ppi;

	अगर (ISLCNPHY(pi))
		wlc_lcnphy_deaf_mode(pi, true);
	अन्यथा अगर (ISNPHY(pi))
		wlc_nphy_deaf_mode(pi, true);
पूर्ण

व्योम wlc_phy_watchकरोg(काष्ठा brcms_phy_pub *pih)
अणु
	काष्ठा brcms_phy *pi = container_of(pih, काष्ठा brcms_phy, pubpi_ro);
	bool delay_phy_cal = false;
	pi->sh->now++;

	अगर (!pi->watchकरोg_override)
		वापस;

	अगर (!(SCAN_RM_IN_PROGRESS(pi) || PLT_INPROG_PHY(pi)))
		wlc_phy_noise_sample_request((काष्ठा brcms_phy_pub *) pi,
					     PHY_NOISE_SAMPLE_MON,
					     CHSPEC_CHANNEL(pi->
							    radio_chanspec));

	अगर (pi->phynoise_state && (pi->sh->now - pi->phynoise_now) > 5)
		pi->phynoise_state = 0;

	अगर ((!pi->phycal_txघातer) ||
	    ((pi->sh->now - pi->phycal_txघातer) >= pi->sh->fast_समयr)) अणु

		अगर (!SCAN_INPROG_PHY(pi) && wlc_phy_cal_txघातer_recalc_sw(pi))
			pi->phycal_txघातer = pi->sh->now;
	पूर्ण

	अगर ((SCAN_RM_IN_PROGRESS(pi) || PLT_INPROG_PHY(pi)
	     || ASSOC_INPROG_PHY(pi)))
		वापस;

	अगर (ISNPHY(pi) && !pi->disable_percal && !delay_phy_cal) अणु

		अगर ((pi->nphy_perical != PHY_PERICAL_DISABLE) &&
		    (pi->nphy_perical != PHY_PERICAL_MANUAL) &&
		    ((pi->sh->now - pi->nphy_perical_last) >=
		     pi->sh->glacial_समयr))
			wlc_phy_cal_perical((काष्ठा brcms_phy_pub *) pi,
					    PHY_PERICAL_WATCHDOG);

		wlc_phy_txpwr_papd_cal_nphy(pi);
	पूर्ण

	अगर (ISLCNPHY(pi)) अणु
		अगर (pi->phy_क्रमcecal ||
		    ((pi->sh->now - pi->phy_lastcal) >=
		     pi->sh->glacial_समयr)) अणु
			अगर (!(SCAN_RM_IN_PROGRESS(pi) || ASSOC_INPROG_PHY(pi)))
				wlc_lcnphy_calib_modes(
					pi,
					LCNPHY_PERICAL_TEMPBASED_TXPWRCTRL);
			अगर (!
			    (SCAN_RM_IN_PROGRESS(pi) || PLT_INPROG_PHY(pi)
			     || ASSOC_INPROG_PHY(pi)
			     || pi->carrier_suppr_disable
			     || pi->disable_percal))
				wlc_lcnphy_calib_modes(pi,
						       PHY_PERICAL_WATCHDOG);
		पूर्ण
	पूर्ण
पूर्ण

व्योम wlc_phy_BSSinit(काष्ठा brcms_phy_pub *pih, bool bonlyap, पूर्णांक rssi)
अणु
	काष्ठा brcms_phy *pi = container_of(pih, काष्ठा brcms_phy, pubpi_ro);
	uपूर्णांक i;
	uपूर्णांक k;

	क्रम (i = 0; i < MA_WINDOW_SZ; i++)
		pi->sh->phy_noise_winकरोw[i] = (s8) (rssi & 0xff);
	अगर (ISLCNPHY(pi)) अणु
		क्रम (i = 0; i < MA_WINDOW_SZ; i++)
			pi->sh->phy_noise_winकरोw[i] =
				PHY_NOISE_FIXED_VAL_LCNPHY;
	पूर्ण
	pi->sh->phy_noise_index = 0;

	क्रम (i = 0; i < PHY_NOISE_WINDOW_SZ; i++) अणु
		क्रम (k = WL_ANT_IDX_1; k < WL_ANT_RX_MAX; k++)
			pi->nphy_noise_win[k][i] = PHY_NOISE_FIXED_VAL_NPHY;
	पूर्ण
	pi->nphy_noise_index = 0;
पूर्ण

व्योम
wlc_phy_papd_decode_epsilon(u32 epsilon, s32 *eps_real, s32 *eps_imag)
अणु
	*eps_imag = (epsilon >> 13);
	अगर (*eps_imag > 0xfff)
		*eps_imag -= 0x2000;

	*eps_real = (epsilon & 0x1fff);
	अगर (*eps_real > 0xfff)
		*eps_real -= 0x2000;
पूर्ण

व्योम wlc_phy_cal_perical_mphase_reset(काष्ठा brcms_phy *pi)
अणु
	wlapi_del_समयr(pi->phycal_समयr);

	pi->cal_type_override = PHY_PERICAL_AUTO;
	pi->mphase_cal_phase_id = MPHASE_CAL_STATE_IDLE;
	pi->mphase_txcal_cmdidx = 0;
पूर्ण

अटल व्योम
wlc_phy_cal_perical_mphase_schedule(काष्ठा brcms_phy *pi, uपूर्णांक delay)
अणु

	अगर ((pi->nphy_perical != PHY_PERICAL_MPHASE) &&
	    (pi->nphy_perical != PHY_PERICAL_MANUAL))
		वापस;

	wlapi_del_समयr(pi->phycal_समयr);

	pi->mphase_cal_phase_id = MPHASE_CAL_STATE_INIT;
	wlapi_add_समयr(pi->phycal_समयr, delay, 0);
पूर्ण

व्योम wlc_phy_cal_perical(काष्ठा brcms_phy_pub *pih, u8 reason)
अणु
	s16 nphy_currtemp = 0;
	s16 delta_temp = 0;
	bool करो_periodic_cal = true;
	काष्ठा brcms_phy *pi = container_of(pih, काष्ठा brcms_phy, pubpi_ro);

	अगर (!ISNPHY(pi))
		वापस;

	अगर ((pi->nphy_perical == PHY_PERICAL_DISABLE) ||
	    (pi->nphy_perical == PHY_PERICAL_MANUAL))
		वापस;

	चयन (reason) अणु
	हाल PHY_PERICAL_DRIVERUP:
		अवरोध;

	हाल PHY_PERICAL_PHYINIT:
		अगर (pi->nphy_perical == PHY_PERICAL_MPHASE) अणु
			अगर (PHY_PERICAL_MPHASE_PENDING(pi))
				wlc_phy_cal_perical_mphase_reset(pi);

			wlc_phy_cal_perical_mphase_schedule(
				pi,
				PHY_PERICAL_INIT_DELAY);
		पूर्ण
		अवरोध;

	हाल PHY_PERICAL_JOIN_BSS:
	हाल PHY_PERICAL_START_IBSS:
	हाल PHY_PERICAL_UP_BSS:
		अगर ((pi->nphy_perical == PHY_PERICAL_MPHASE) &&
		    PHY_PERICAL_MPHASE_PENDING(pi))
			wlc_phy_cal_perical_mphase_reset(pi);

		pi->first_cal_after_assoc = true;

		pi->cal_type_override = PHY_PERICAL_FULL;

		अगर (pi->phycal_tempdelta)
			pi->nphy_lastcal_temp = wlc_phy_tempsense_nphy(pi);

		wlc_phy_cal_perical_nphy_run(pi, PHY_PERICAL_FULL);
		अवरोध;

	हाल PHY_PERICAL_WATCHDOG:
		अगर (pi->phycal_tempdelta) अणु
			nphy_currtemp = wlc_phy_tempsense_nphy(pi);
			delta_temp =
				(nphy_currtemp > pi->nphy_lastcal_temp) ?
				nphy_currtemp - pi->nphy_lastcal_temp :
				pi->nphy_lastcal_temp - nphy_currtemp;

			अगर ((delta_temp < (s16) pi->phycal_tempdelta) &&
			    (pi->nphy_txiqlocal_chanspec ==
			     pi->radio_chanspec))
				करो_periodic_cal = false;
			अन्यथा
				pi->nphy_lastcal_temp = nphy_currtemp;
		पूर्ण

		अगर (करो_periodic_cal) अणु
			अगर (pi->nphy_perical == PHY_PERICAL_MPHASE) अणु
				अगर (!PHY_PERICAL_MPHASE_PENDING(pi))
					wlc_phy_cal_perical_mphase_schedule(
						pi,
						PHY_PERICAL_WDOG_DELAY);
			पूर्ण अन्यथा अगर (pi->nphy_perical == PHY_PERICAL_SPHASE)
				wlc_phy_cal_perical_nphy_run(pi,
							     PHY_PERICAL_AUTO);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम wlc_phy_cal_perical_mphase_restart(काष्ठा brcms_phy *pi)
अणु
	pi->mphase_cal_phase_id = MPHASE_CAL_STATE_INIT;
	pi->mphase_txcal_cmdidx = 0;
पूर्ण

u8 wlc_phy_nbits(s32 value)
अणु
	s32 असल_val;
	u8 nbits = 0;

	असल_val = असल(value);
	जबतक ((असल_val >> nbits) > 0)
		nbits++;

	वापस nbits;
पूर्ण

व्योम wlc_phy_stf_chain_init(काष्ठा brcms_phy_pub *pih, u8 txchain, u8 rxchain)
अणु
	काष्ठा brcms_phy *pi = container_of(pih, काष्ठा brcms_phy, pubpi_ro);

	pi->sh->hw_phytxchain = txchain;
	pi->sh->hw_phyrxchain = rxchain;
	pi->sh->phytxchain = txchain;
	pi->sh->phyrxchain = rxchain;
	pi->pubpi.phy_corक्रमागत = (u8)hweight8(pi->sh->phyrxchain);
पूर्ण

व्योम wlc_phy_stf_chain_set(काष्ठा brcms_phy_pub *pih, u8 txchain, u8 rxchain)
अणु
	काष्ठा brcms_phy *pi = container_of(pih, काष्ठा brcms_phy, pubpi_ro);

	pi->sh->phytxchain = txchain;

	अगर (ISNPHY(pi))
		wlc_phy_rxcore_setstate_nphy(pih, rxchain);

	pi->pubpi.phy_corक्रमागत = (u8)hweight8(pi->sh->phyrxchain);
पूर्ण

व्योम wlc_phy_stf_chain_get(काष्ठा brcms_phy_pub *pih, u8 *txchain, u8 *rxchain)
अणु
	काष्ठा brcms_phy *pi = container_of(pih, काष्ठा brcms_phy, pubpi_ro);

	*txchain = pi->sh->phytxchain;
	*rxchain = pi->sh->phyrxchain;
पूर्ण

u8 wlc_phy_stf_chain_active_get(काष्ठा brcms_phy_pub *pih)
अणु
	s16 nphy_currtemp;
	u8 active_biपंचांगap;
	काष्ठा brcms_phy *pi = container_of(pih, काष्ठा brcms_phy, pubpi_ro);

	active_biपंचांगap = (pi->phy_txcore_heatedup) ? 0x31 : 0x33;

	अगर (!pi->watchकरोg_override)
		वापस active_biपंचांगap;

	अगर (NREV_GE(pi->pubpi.phy_rev, 6)) अणु
		wlapi_suspend_mac_and_रुको(pi->sh->physhim);
		nphy_currtemp = wlc_phy_tempsense_nphy(pi);
		wlapi_enable_mac(pi->sh->physhim);

		अगर (!pi->phy_txcore_heatedup) अणु
			अगर (nphy_currtemp >= pi->phy_txcore_disable_temp) अणु
				active_biपंचांगap &= 0xFD;
				pi->phy_txcore_heatedup = true;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (nphy_currtemp <= pi->phy_txcore_enable_temp) अणु
				active_biपंचांगap |= 0x2;
				pi->phy_txcore_heatedup = false;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस active_biपंचांगap;
पूर्ण

s8 wlc_phy_stf_ssmode_get(काष्ठा brcms_phy_pub *pih, u16 chanspec)
अणु
	काष्ठा brcms_phy *pi = container_of(pih, काष्ठा brcms_phy, pubpi_ro);
	u8 siso_mcs_id, cdd_mcs_id;

	siso_mcs_id =
		(CHSPEC_IS40(chanspec)) ? TXP_FIRST_MCS_40_SISO :
		TXP_FIRST_MCS_20_SISO;
	cdd_mcs_id =
		(CHSPEC_IS40(chanspec)) ? TXP_FIRST_MCS_40_CDD :
		TXP_FIRST_MCS_20_CDD;

	अगर (pi->tx_घातer_target[siso_mcs_id] >
	    (pi->tx_घातer_target[cdd_mcs_id] + 12))
		वापस PHY_TXC1_MODE_SISO;
	अन्यथा
		वापस PHY_TXC1_MODE_CDD;
पूर्ण

स्थिर u8 *wlc_phy_get_ofdm_rate_lookup(व्योम)
अणु
	वापस ofdm_rate_lookup;
पूर्ण

व्योम wlc_lcnphy_epa_चयन(काष्ठा brcms_phy *pi, bool mode)
अणु
	अगर ((pi->sh->chip == BCMA_CHIP_ID_BCM4313) &&
	    (pi->sh->boardflags & BFL_FEM)) अणु
		अगर (mode) अणु
			u16 txant = 0;
			txant = wlapi_bmac_get_txant(pi->sh->physhim);
			अगर (txant == 1) अणु
				mod_phy_reg(pi, 0x44d, (0x1 << 2), (1) << 2);

				mod_phy_reg(pi, 0x44c, (0x1 << 2), (1) << 2);

			पूर्ण

			bcma_chipco_gpio_control(&pi->d11core->bus->drv_cc,
						 0x0, 0x0);
			bcma_chipco_gpio_out(&pi->d11core->bus->drv_cc,
					     ~0x40, 0x40);
			bcma_chipco_gpio_outen(&pi->d11core->bus->drv_cc,
					       ~0x40, 0x40);
		पूर्ण अन्यथा अणु
			mod_phy_reg(pi, 0x44c, (0x1 << 2), (0) << 2);

			mod_phy_reg(pi, 0x44d, (0x1 << 2), (0) << 2);

			bcma_chipco_gpio_out(&pi->d11core->bus->drv_cc,
					     ~0x40, 0x00);
			bcma_chipco_gpio_outen(&pi->d11core->bus->drv_cc,
					       ~0x40, 0x00);
			bcma_chipco_gpio_control(&pi->d11core->bus->drv_cc,
						 0x0, 0x40);
		पूर्ण
	पूर्ण
पूर्ण

व्योम wlc_phy_ldpc_override_set(काष्ठा brcms_phy_pub *ppi, bool ldpc)
अणु
	वापस;
पूर्ण

व्योम
wlc_phy_get_pwrdet_offsets(काष्ठा brcms_phy *pi, s8 *cckoffset, s8 *ofdmoffset)
अणु
	*cckoffset = 0;
	*ofdmoffset = 0;
पूर्ण

s8 wlc_phy_upd_rssi_offset(काष्ठा brcms_phy *pi, s8 rssi, u16 chanspec)
अणु

	वापस rssi;
पूर्ण

bool wlc_phy_txघातer_ipa_ison(काष्ठा brcms_phy_pub *ppi)
अणु
	काष्ठा brcms_phy *pi = container_of(ppi, काष्ठा brcms_phy, pubpi_ro);

	अगर (ISNPHY(pi))
		वापस wlc_phy_n_txघातer_ipa_ison(pi);
	अन्यथा
		वापस false;
पूर्ण
