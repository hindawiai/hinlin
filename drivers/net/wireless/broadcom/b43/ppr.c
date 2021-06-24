<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Broadcom B43 wireless driver
 * PPR (Power Per Rate) management
 *
 * Copyright (c) 2014 Rafaध Miधecki <zajec5@gmail.com>
 */

#समावेश "ppr.h"
#समावेश "b43.h"

#घोषणा ppr_क्रम_each_entry(ppr, i, entry)				\
	क्रम (i = 0, entry = &(ppr)->__all_rates[i];			\
	     i < B43_PPR_RATES_NUM;					\
	     i++, entry++)

व्योम b43_ppr_clear(काष्ठा b43_wldev *dev, काष्ठा b43_ppr *ppr)
अणु
	स_रखो(ppr, 0, माप(*ppr));

	/* Compile-समय PPR check */
	BUILD_BUG_ON(माप(काष्ठा b43_ppr) != B43_PPR_RATES_NUM * माप(u8));
पूर्ण

व्योम b43_ppr_add(काष्ठा b43_wldev *dev, काष्ठा b43_ppr *ppr, पूर्णांक dअगरf)
अणु
	पूर्णांक i;
	u8 *rate;

	ppr_क्रम_each_entry(ppr, i, rate) अणु
		*rate = clamp_val(*rate + dअगरf, 0, 127);
	पूर्ण
पूर्ण

व्योम b43_ppr_apply_max(काष्ठा b43_wldev *dev, काष्ठा b43_ppr *ppr, u8 max)
अणु
	पूर्णांक i;
	u8 *rate;

	ppr_क्रम_each_entry(ppr, i, rate) अणु
		*rate = min(*rate, max);
	पूर्ण
पूर्ण

व्योम b43_ppr_apply_min(काष्ठा b43_wldev *dev, काष्ठा b43_ppr *ppr, u8 min)
अणु
	पूर्णांक i;
	u8 *rate;

	ppr_क्रम_each_entry(ppr, i, rate) अणु
		*rate = max(*rate, min);
	पूर्ण
पूर्ण

u8 b43_ppr_get_max(काष्ठा b43_wldev *dev, काष्ठा b43_ppr *ppr)
अणु
	u8 res = 0;
	पूर्णांक i;
	u8 *rate;

	ppr_क्रम_each_entry(ppr, i, rate) अणु
		res = max(*rate, res);
	पूर्ण

	वापस res;
पूर्ण

bool b43_ppr_load_max_from_sprom(काष्ठा b43_wldev *dev, काष्ठा b43_ppr *ppr,
				 क्रमागत b43_band band)
अणु
	काष्ठा b43_ppr_rates *rates = &ppr->rates;
	काष्ठा ssb_sprom *sprom = dev->dev->bus_sprom;
	काष्ठा b43_phy *phy = &dev->phy;
	u8 maxpwr, off;
	u32 sprom_ofdm_po;
	u16 *sprom_mcs_po;
	u8 extra_cdd_po, extra_stbc_po;
	पूर्णांक i;

	चयन (band) अणु
	हाल B43_BAND_2G:
		maxpwr = min(sprom->core_pwr_info[0].maxpwr_2g,
			     sprom->core_pwr_info[1].maxpwr_2g);
		sprom_ofdm_po = sprom->ofdm2gpo;
		sprom_mcs_po = sprom->mcs2gpo;
		extra_cdd_po = (sprom->cddpo >> 0) & 0xf;
		extra_stbc_po = (sprom->stbcpo >> 0) & 0xf;
		अवरोध;
	हाल B43_BAND_5G_LO:
		maxpwr = min(sprom->core_pwr_info[0].maxpwr_5gl,
			     sprom->core_pwr_info[1].maxpwr_5gl);
		sprom_ofdm_po = sprom->ofdm5glpo;
		sprom_mcs_po = sprom->mcs5glpo;
		extra_cdd_po = (sprom->cddpo >> 8) & 0xf;
		extra_stbc_po = (sprom->stbcpo >> 8) & 0xf;
		अवरोध;
	हाल B43_BAND_5G_MI:
		maxpwr = min(sprom->core_pwr_info[0].maxpwr_5g,
			     sprom->core_pwr_info[1].maxpwr_5g);
		sprom_ofdm_po = sprom->ofdm5gpo;
		sprom_mcs_po = sprom->mcs5gpo;
		extra_cdd_po = (sprom->cddpo >> 4) & 0xf;
		extra_stbc_po = (sprom->stbcpo >> 4) & 0xf;
		अवरोध;
	हाल B43_BAND_5G_HI:
		maxpwr = min(sprom->core_pwr_info[0].maxpwr_5gh,
			     sprom->core_pwr_info[1].maxpwr_5gh);
		sprom_ofdm_po = sprom->ofdm5ghpo;
		sprom_mcs_po = sprom->mcs5ghpo;
		extra_cdd_po = (sprom->cddpo >> 12) & 0xf;
		extra_stbc_po = (sprom->stbcpo >> 12) & 0xf;
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस false;
	पूर्ण

	अगर (band == B43_BAND_2G) अणु
		क्रम (i = 0; i < 4; i++) अणु
			off = ((sprom->cck2gpo >> (i * 4)) & 0xf) * 2;
			rates->cck[i] = maxpwr - off;
		पूर्ण
	पूर्ण

	/* OFDM */
	क्रम (i = 0; i < 8; i++) अणु
		off = ((sprom_ofdm_po >> (i * 4)) & 0xf) * 2;
		rates->ofdm[i] = maxpwr - off;
	पूर्ण

	/* MCS 20 SISO */
	rates->mcs_20[0] = rates->ofdm[0];
	rates->mcs_20[1] = rates->ofdm[2];
	rates->mcs_20[2] = rates->ofdm[3];
	rates->mcs_20[3] = rates->ofdm[4];
	rates->mcs_20[4] = rates->ofdm[5];
	rates->mcs_20[5] = rates->ofdm[6];
	rates->mcs_20[6] = rates->ofdm[7];
	rates->mcs_20[7] = rates->ofdm[7];

	/* MCS 20 CDD */
	क्रम (i = 0; i < 4; i++) अणु
		off = ((sprom_mcs_po[0] >> (i * 4)) & 0xf) * 2;
		rates->mcs_20_cdd[i] = maxpwr - off;
		अगर (phy->type == B43_PHYTYPE_N && phy->rev >= 3)
			rates->mcs_20_cdd[i] -= extra_cdd_po;
	पूर्ण
	क्रम (i = 0; i < 4; i++) अणु
		off = ((sprom_mcs_po[1] >> (i * 4)) & 0xf) * 2;
		rates->mcs_20_cdd[4 + i] = maxpwr - off;
		अगर (phy->type == B43_PHYTYPE_N && phy->rev >= 3)
			rates->mcs_20_cdd[4 + i] -= extra_cdd_po;
	पूर्ण

	/* OFDM 20 CDD */
	rates->ofdm_20_cdd[0] = rates->mcs_20_cdd[0];
	rates->ofdm_20_cdd[1] = rates->mcs_20_cdd[0];
	rates->ofdm_20_cdd[2] = rates->mcs_20_cdd[1];
	rates->ofdm_20_cdd[3] = rates->mcs_20_cdd[2];
	rates->ofdm_20_cdd[4] = rates->mcs_20_cdd[3];
	rates->ofdm_20_cdd[5] = rates->mcs_20_cdd[4];
	rates->ofdm_20_cdd[6] = rates->mcs_20_cdd[5];
	rates->ofdm_20_cdd[7] = rates->mcs_20_cdd[6];

	/* MCS 20 STBC */
	क्रम (i = 0; i < 4; i++) अणु
		off = ((sprom_mcs_po[0] >> (i * 4)) & 0xf) * 2;
		rates->mcs_20_stbc[i] = maxpwr - off;
		अगर (phy->type == B43_PHYTYPE_N && phy->rev >= 3)
			rates->mcs_20_stbc[i] -= extra_stbc_po;
	पूर्ण
	क्रम (i = 0; i < 4; i++) अणु
		off = ((sprom_mcs_po[1] >> (i * 4)) & 0xf) * 2;
		rates->mcs_20_stbc[4 + i] = maxpwr - off;
		अगर (phy->type == B43_PHYTYPE_N && phy->rev >= 3)
			rates->mcs_20_stbc[4 + i] -= extra_stbc_po;
	पूर्ण

	/* MCS 20 SDM */
	क्रम (i = 0; i < 4; i++) अणु
		off = ((sprom_mcs_po[2] >> (i * 4)) & 0xf) * 2;
		rates->mcs_20_sdm[i] = maxpwr - off;
	पूर्ण
	क्रम (i = 0; i < 4; i++) अणु
		off = ((sprom_mcs_po[3] >> (i * 4)) & 0xf) * 2;
		rates->mcs_20_sdm[4 + i] = maxpwr - off;
	पूर्ण

	वापस true;
पूर्ण
