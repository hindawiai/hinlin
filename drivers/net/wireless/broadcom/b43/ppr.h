<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_B43_PPR_H_
#घोषणा LINUX_B43_PPR_H_

#समावेश <linux/types.h>

#घोषणा B43_PPR_CCK_RATES_NUM		4
#घोषणा B43_PPR_OFDM_RATES_NUM		8
#घोषणा B43_PPR_MCS_RATES_NUM		8

#घोषणा B43_PPR_RATES_NUM	(B43_PPR_CCK_RATES_NUM +	\
				 B43_PPR_OFDM_RATES_NUM * 2 +	\
				 B43_PPR_MCS_RATES_NUM * 4)

काष्ठा b43_ppr_rates अणु
	u8 cck[B43_PPR_CCK_RATES_NUM];
	u8 ofdm[B43_PPR_OFDM_RATES_NUM];
	u8 ofdm_20_cdd[B43_PPR_OFDM_RATES_NUM];
	u8 mcs_20[B43_PPR_MCS_RATES_NUM]; /* SISO */
	u8 mcs_20_cdd[B43_PPR_MCS_RATES_NUM];
	u8 mcs_20_stbc[B43_PPR_MCS_RATES_NUM];
	u8 mcs_20_sdm[B43_PPR_MCS_RATES_NUM];
पूर्ण;

काष्ठा b43_ppr अणु
	/* All घातers are in qdbm (Q5.2) */
	जोड़ अणु
		u8 __all_rates[B43_PPR_RATES_NUM];
		काष्ठा b43_ppr_rates rates;
	पूर्ण;
पूर्ण;

काष्ठा b43_wldev;
क्रमागत b43_band;

व्योम b43_ppr_clear(काष्ठा b43_wldev *dev, काष्ठा b43_ppr *ppr);

व्योम b43_ppr_add(काष्ठा b43_wldev *dev, काष्ठा b43_ppr *ppr, पूर्णांक dअगरf);
व्योम b43_ppr_apply_max(काष्ठा b43_wldev *dev, काष्ठा b43_ppr *ppr, u8 max);
व्योम b43_ppr_apply_min(काष्ठा b43_wldev *dev, काष्ठा b43_ppr *ppr, u8 min);
u8 b43_ppr_get_max(काष्ठा b43_wldev *dev, काष्ठा b43_ppr *ppr);

bool b43_ppr_load_max_from_sprom(काष्ठा b43_wldev *dev, काष्ठा b43_ppr *ppr,
				 क्रमागत b43_band band);

#पूर्ण_अगर /* LINUX_B43_PPR_H_ */
