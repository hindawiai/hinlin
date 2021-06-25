<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 * Copyright(c) 2008 - 2010 Realtek Corporation. All rights reserved.
 *
 * Contact Inक्रमmation:
 * wlanfae <wlanfae@realtek.com>
 ******************************************************************************/
#समावेश "dot11d.h"

काष्ठा channel_list अणु
	u8      channel[32];
	u8      len;
पूर्ण;

अटल काष्ठा channel_list channel_array[] = अणु
	अणुअणु1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 36, 40, 44, 48, 52, 56, 60, 64,
	  149, 153, 157, 161, 165पूर्ण, 24पूर्ण,
	अणुअणु1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11पूर्ण, 11पूर्ण,
	अणुअणु1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 36, 40, 44, 48, 52, 56,
	  60, 64पूर्ण, 21पूर्ण,
	अणुअणु1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13पूर्ण, 13पूर्ण,
	अणुअणु1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13पूर्ण, 13पूर्ण,
	अणुअणु1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 36, 40, 44, 48, 52,
	  56, 60, 64पूर्ण, 22पूर्ण,
	अणुअणु1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 36, 40, 44, 48, 52,
	  56, 60, 64पूर्ण, 22पूर्ण,
	अणुअणु1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13पूर्ण, 13पूर्ण,
	अणुअणु1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 36, 40, 44, 48, 52,
	  56, 60, 64पूर्ण, 22पूर्ण,
	अणुअणु1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 36, 40, 44, 48, 52,
	 56, 60, 64पूर्ण, 22पूर्ण,
	अणुअणु1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14पूर्ण, 14पूर्ण,
	अणुअणु1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13पूर्ण, 13पूर्ण,
	अणुअणु1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 36, 40, 44, 48, 52,
	  56, 60, 64पूर्ण, 21पूर्ण
पूर्ण;

व्योम करोt11d_init(काष्ठा rtllib_device *ieee)
अणु
	काष्ठा rt_करोt11d_info *करोt11d_info = GET_DOT11D_INFO(ieee);

	करोt11d_info->enabled = false;

	करोt11d_info->state = DOT11D_STATE_NONE;
	करोt11d_info->country_len = 0;
	स_रखो(करोt11d_info->channel_map, 0, MAX_CHANNEL_NUMBER + 1);
	स_रखो(करोt11d_info->max_tx_घातer_list, 0xFF, MAX_CHANNEL_NUMBER + 1);
	RESET_CIE_WATCHDOG(ieee);
पूर्ण
EXPORT_SYMBOL(करोt11d_init);

व्योम करोt11d_channel_map(u8 channel_plan, काष्ठा rtllib_device *ieee)
अणु
	पूर्णांक i, max_chan = 14, min_chan = 1;

	ieee->global_करोमुख्य = false;

	अगर (channel_array[channel_plan].len != 0) अणु
		स_रखो(GET_DOT11D_INFO(ieee)->channel_map, 0,
		       माप(GET_DOT11D_INFO(ieee)->channel_map));
		क्रम (i = 0; i < channel_array[channel_plan].len; i++) अणु
			अगर (channel_array[channel_plan].channel[i] < min_chan ||
			    channel_array[channel_plan].channel[i] > max_chan)
				अवरोध;
			GET_DOT11D_INFO(ieee)->channel_map[channel_array
					[channel_plan].channel[i]] = 1;
		पूर्ण
	पूर्ण

	चयन (channel_plan) अणु
	हाल COUNTRY_CODE_GLOBAL_DOMAIN:
		ieee->global_करोमुख्य = true;
		क्रम (i = 12; i <= 14; i++)
			GET_DOT11D_INFO(ieee)->channel_map[i] = 2;
		ieee->bss_start_channel = 10;
		ieee->ibss_maxjoin_chal = 11;
		अवरोध;

	हाल COUNTRY_CODE_WORLD_WIDE_13:
		क्रम (i = 12; i <= 13; i++)
			GET_DOT11D_INFO(ieee)->channel_map[i] = 2;
		ieee->bss_start_channel = 10;
		ieee->ibss_maxjoin_chal = 11;
		अवरोध;

	शेष:
		ieee->bss_start_channel = 1;
		ieee->ibss_maxjoin_chal = 14;
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(करोt11d_channel_map);

व्योम करोt11d_reset(काष्ठा rtllib_device *ieee)
अणु
	काष्ठा rt_करोt11d_info *करोt11d_info = GET_DOT11D_INFO(ieee);
	u32 i;

	स_रखो(करोt11d_info->channel_map, 0, MAX_CHANNEL_NUMBER + 1);
	स_रखो(करोt11d_info->max_tx_घातer_list, 0xFF, MAX_CHANNEL_NUMBER + 1);
	क्रम (i = 1; i <= 11; i++)
		(करोt11d_info->channel_map)[i] = 1;
	क्रम (i = 12; i <= 14; i++)
		(करोt11d_info->channel_map)[i] = 2;
	करोt11d_info->state = DOT11D_STATE_NONE;
	करोt11d_info->country_len = 0;
	RESET_CIE_WATCHDOG(ieee);
पूर्ण

व्योम करोt11d_update_country(काष्ठा rtllib_device *dev, u8 *address,
			   u16 country_len, u8 *country)
अणु
	काष्ठा rt_करोt11d_info *करोt11d_info = GET_DOT11D_INFO(dev);
	u8 i, j, number_of_triples, max_channel_number;
	काष्ठा chnl_txघात_triple *triple;

	स_रखो(करोt11d_info->channel_map, 0, MAX_CHANNEL_NUMBER + 1);
	स_रखो(करोt11d_info->max_tx_घातer_list, 0xFF, MAX_CHANNEL_NUMBER + 1);
	max_channel_number = 0;
	number_of_triples = (country_len - 3) / 3;
	triple = (काष्ठा chnl_txघात_triple *)(country + 3);
	क्रम (i = 0; i < number_of_triples; i++) अणु
		अगर (max_channel_number >= triple->first_channel) अणु
			netdev_info(dev->dev,
				    "%s: Invalid country IE, skip it......1\n",
				    __func__);
			वापस;
		पूर्ण
		अगर (MAX_CHANNEL_NUMBER < (triple->first_channel +
		    triple->num_channels)) अणु
			netdev_info(dev->dev,
				    "%s: Invalid country IE, skip it......2\n",
				    __func__);
			वापस;
		पूर्ण

		क्रम (j = 0; j < triple->num_channels; j++) अणु
			करोt11d_info->channel_map[triple->first_channel + j] = 1;
			करोt11d_info->max_tx_घातer_list[triple->first_channel + j] =
						 triple->max_tx_घातer;
			max_channel_number = triple->first_channel + j;
		पूर्ण

		triple = (काष्ठा chnl_txघात_triple *)((u8 *)triple + 3);
	पूर्ण

	UPDATE_CIE_SRC(dev, address);

	करोt11d_info->country_len = country_len;
	स_नकल(करोt11d_info->country_buffer, country, country_len);
	करोt11d_info->state = DOT11D_STATE_LEARNED;
पूर्ण

व्योम करोt11d_scan_complete(काष्ठा rtllib_device *dev)
अणु
	काष्ठा rt_करोt11d_info *करोt11d_info = GET_DOT11D_INFO(dev);

	चयन (करोt11d_info->state) अणु
	हाल DOT11D_STATE_LEARNED:
		करोt11d_info->state = DOT11D_STATE_DONE;
		अवरोध;
	हाल DOT11D_STATE_DONE:
		करोt11d_reset(dev);
		अवरोध;
	हाल DOT11D_STATE_NONE:
		अवरोध;
	पूर्ण
पूर्ण
