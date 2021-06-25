<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 * Copyright(c) 2008 - 2010 Realtek Corporation. All rights reserved.
 *
 * Contact Inक्रमmation:
 * wlanfae <wlanfae@realtek.com>
 ******************************************************************************/
#अगर_अघोषित __INC_DOT11D_H
#घोषणा __INC_DOT11D_H

#समावेश "rtllib.h"

काष्ठा chnl_txघात_triple अणु
	u8 first_channel;
	u8  num_channels;
	u8  max_tx_घातer;
पूर्ण;

क्रमागत करोt11d_state अणु
	DOT11D_STATE_NONE = 0,
	DOT11D_STATE_LEARNED,
	DOT11D_STATE_DONE,
पूर्ण;

/**
 * काष्ठा rt_करोt11d_info * @country_len: value greater than 0 अगर
 *		  @country_buffer contains valid country inक्रमmation element.
 * @channel_map: holds channel values
 *		0 - invalid,
 *		1 - valid (active scan),
 *		2 - valid (passive scan)
 * @country_src_addr - Source AP of the country IE
 */

काष्ठा rt_करोt11d_info अणु
	bool enabled;

	u16 country_len;
	u8  country_buffer[MAX_IE_LEN];
	u8  country_src_addr[6];
	u8  country_watchकरोg;

	u8  channel_map[MAX_CHANNEL_NUMBER + 1];
	u8  max_tx_घातer_list[MAX_CHANNEL_NUMBER + 1];

	क्रमागत करोt11d_state state;
पूर्ण;

अटल अंतरभूत व्योम copy_mac_addr(अचिन्हित अक्षर *des, अचिन्हित अक्षर *src)
अणु
	स_नकल(des, src, 6);
पूर्ण

#घोषणा GET_DOT11D_INFO(__ieee_dev)			\
	 ((काष्ठा rt_करोt11d_info *)((__ieee_dev)->करोt11d_info))

#घोषणा IS_DOT11D_ENABLE(__ieee_dev)			\
	 (GET_DOT11D_INFO(__ieee_dev)->enabled)
#घोषणा IS_COUNTRY_IE_VALID(__ieee_dev)			\
	(GET_DOT11D_INFO(__ieee_dev)->country_len > 0)

#घोषणा IS_EQUAL_CIE_SRC(__ieee_dev, __address)		\
	 ether_addr_equal_unaligned( \
		GET_DOT11D_INFO(__ieee_dev)->country_src_addr, __address)
#घोषणा UPDATE_CIE_SRC(__ieee_dev, __address)		\
	copy_mac_addr(GET_DOT11D_INFO(__ieee_dev)->country_src_addr, __address)

#घोषणा GET_CIE_WATCHDOG(__ieee_dev)				\
	 (GET_DOT11D_INFO(__ieee_dev)->country_watchकरोg)
अटल अंतरभूत व्योम RESET_CIE_WATCHDOG(काष्ठा rtllib_device *__ieee_dev)
अणु
	GET_CIE_WATCHDOG(__ieee_dev) = 0;
पूर्ण

#घोषणा UPDATE_CIE_WATCHDOG(__ieee_dev) (++GET_CIE_WATCHDOG(__ieee_dev))

व्योम करोt11d_init(काष्ठा rtllib_device *dev);
व्योम करोt11d_channel_map(u8 channel_plan, काष्ठा rtllib_device *ieee);
व्योम करोt11d_reset(काष्ठा rtllib_device *dev);
व्योम करोt11d_update_country(काष्ठा rtllib_device *dev, u8 *address,
			   u16 country_len, u8 *country);
व्योम करोt11d_scan_complete(काष्ठा rtllib_device *dev);

#पूर्ण_अगर
