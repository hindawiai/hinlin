<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Implement 802.11d. */

#समावेश "dot11d.h"

व्योम rtl8192u_करोt11d_init(काष्ठा ieee80211_device *ieee)
अणु
	काष्ठा rt_करोt11d_info *करोt11d_info = GET_DOT11D_INFO(ieee);

	करोt11d_info->करोt11d_enabled = false;

	करोt11d_info->state = DOT11D_STATE_NONE;
	करोt11d_info->country_ie_len = 0;
	स_रखो(करोt11d_info->channel_map, 0, MAX_CHANNEL_NUMBER + 1);
	स_रखो(करोt11d_info->max_tx_pwr_dbm_list, 0xFF, MAX_CHANNEL_NUMBER + 1);
	RESET_CIE_WATCHDOG(ieee);
पूर्ण
EXPORT_SYMBOL(rtl8192u_करोt11d_init);

/* Reset to the state as we are just entering a regulatory करोमुख्य. */
व्योम करोt11d_reset(काष्ठा ieee80211_device *ieee)
अणु
	u32 i;
	काष्ठा rt_करोt11d_info *करोt11d_info = GET_DOT11D_INFO(ieee);
	/* Clear old channel map */
	स_रखो(करोt11d_info->channel_map, 0, MAX_CHANNEL_NUMBER + 1);
	स_रखो(करोt11d_info->max_tx_pwr_dbm_list, 0xFF, MAX_CHANNEL_NUMBER + 1);
	/* Set new channel map */
	क्रम (i = 1; i <= 11; i++)
		(करोt11d_info->channel_map)[i] = 1;

	क्रम (i = 12; i <= 14; i++)
		(करोt11d_info->channel_map)[i] = 2;

	करोt11d_info->state = DOT11D_STATE_NONE;
	करोt11d_info->country_ie_len = 0;
	RESET_CIE_WATCHDOG(ieee);
पूर्ण
EXPORT_SYMBOL(करोt11d_reset);

/*
 * Update country IE from Beacon or Probe Resopnse and configure PHY क्रम
 * operation in the regulatory करोमुख्य.
 *
 * TODO: Configure Tx घातer.
 * Assumption:
 * 1. IS_DOT11D_ENABLE() is TRUE.
 * 2. Input IE is an valid one.
 */
व्योम करोt11d_update_country_ie(काष्ठा ieee80211_device *dev, u8 *pTaddr,
			    u16 CoutryIeLen, u8 *pCoutryIe)
अणु
	काष्ठा rt_करोt11d_info *करोt11d_info = GET_DOT11D_INFO(dev);
	u8 i, j, NumTriples, MaxChnlNum;
	काष्ठा chnl_txघातer_triple *pTriple;

	स_रखो(करोt11d_info->channel_map, 0, MAX_CHANNEL_NUMBER + 1);
	स_रखो(करोt11d_info->max_tx_pwr_dbm_list, 0xFF, MAX_CHANNEL_NUMBER + 1);
	MaxChnlNum = 0;
	NumTriples = (CoutryIeLen - 3) / 3; /* skip 3-byte country string. */
	pTriple = (काष्ठा chnl_txघातer_triple *)(pCoutryIe + 3);
	क्रम (i = 0; i < NumTriples; i++) अणु
		अगर (MaxChnlNum >= pTriple->first_channel) अणु
			/* It is not in a monotonically increasing order, so
			 * stop processing.
			 */
			netdev_err(dev->dev, "%s: Invalid country IE, skip it 1\n", __func__);
			वापस;
		पूर्ण
		अगर (MAX_CHANNEL_NUMBER < (pTriple->first_channel + pTriple->num_channels)) अणु
			/* It is not a valid set of channel id, so stop
			 * processing.
			 */
			netdev_err(dev->dev, "%s: Invalid country IE, skip it 2\n", __func__);
			वापस;
		पूर्ण

		क्रम (j = 0; j < pTriple->num_channels; j++) अणु
			करोt11d_info->channel_map[pTriple->first_channel + j] = 1;
			करोt11d_info->max_tx_pwr_dbm_list[pTriple->first_channel + j] = pTriple->max_tx_pwr_dbm;
			MaxChnlNum = pTriple->first_channel + j;
		पूर्ण

		pTriple = (काष्ठा chnl_txघातer_triple *)((u8 *)pTriple + 3);
	पूर्ण
	netdev_info(dev->dev, "Channel List:");
	क्रम (i = 1; i <= MAX_CHANNEL_NUMBER; i++)
		अगर (करोt11d_info->channel_map[i] > 0)
			netdev_info(dev->dev, " %d", i);
	netdev_info(dev->dev, "\n");

	UPDATE_CIE_SRC(dev, pTaddr);

	करोt11d_info->country_ie_len = CoutryIeLen;
	स_नकल(करोt11d_info->country_ie_buf, pCoutryIe, CoutryIeLen);
	करोt11d_info->state = DOT11D_STATE_LEARNED;
पूर्ण
EXPORT_SYMBOL(करोt11d_update_country_ie);

u8 करोt11d_get_max_tx_pwr_in_dbm(काष्ठा ieee80211_device *dev, u8 Channel)
अणु
	काष्ठा rt_करोt11d_info *करोt11d_info = GET_DOT11D_INFO(dev);
	u8 MaxTxPwrInDbm = 255;

	अगर (Channel > MAX_CHANNEL_NUMBER) अणु
		netdev_err(dev->dev, "%s: Invalid Channel\n", __func__);
		वापस MaxTxPwrInDbm;
	पूर्ण
	अगर (करोt11d_info->channel_map[Channel])
		MaxTxPwrInDbm = करोt11d_info->max_tx_pwr_dbm_list[Channel];

	वापस MaxTxPwrInDbm;
पूर्ण
EXPORT_SYMBOL(करोt11d_get_max_tx_pwr_in_dbm);

व्योम करोt11d_scan_complete(काष्ठा ieee80211_device *dev)
अणु
	काष्ठा rt_करोt11d_info *करोt11d_info = GET_DOT11D_INFO(dev);

	चयन (करोt11d_info->state) अणु
	हाल DOT11D_STATE_LEARNED:
		करोt11d_info->state = DOT11D_STATE_DONE;
		अवरोध;

	हाल DOT11D_STATE_DONE:
		अगर (GET_CIE_WATCHDOG(dev) == 0) अणु
			/* Reset country IE अगर previous one is gone. */
			करोt11d_reset(dev);
		पूर्ण
		अवरोध;
	हाल DOT11D_STATE_NONE:
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(करोt11d_scan_complete);

पूर्णांक is_legal_channel(काष्ठा ieee80211_device *dev, u8 channel)
अणु
	काष्ठा rt_करोt11d_info *करोt11d_info = GET_DOT11D_INFO(dev);

	अगर (channel > MAX_CHANNEL_NUMBER) अणु
		netdev_err(dev->dev, "%s: Invalid Channel\n", __func__);
		वापस 0;
	पूर्ण
	अगर (करोt11d_info->channel_map[channel] > 0)
		वापस 1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(is_legal_channel);

पूर्णांक to_legal_channel(काष्ठा ieee80211_device *dev, u8 channel)
अणु
	काष्ठा rt_करोt11d_info *करोt11d_info = GET_DOT11D_INFO(dev);
	u8 शेष_chn = 0;
	u32 i = 0;

	क्रम (i = 1; i <= MAX_CHANNEL_NUMBER; i++) अणु
		अगर (करोt11d_info->channel_map[i] > 0) अणु
			शेष_chn = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (channel > MAX_CHANNEL_NUMBER) अणु
		netdev_err(dev->dev, "%s: Invalid Channel\n", __func__);
		वापस शेष_chn;
	पूर्ण

	अगर (करोt11d_info->channel_map[channel] > 0)
		वापस channel;

	वापस शेष_chn;
पूर्ण
EXPORT_SYMBOL(to_legal_channel);
