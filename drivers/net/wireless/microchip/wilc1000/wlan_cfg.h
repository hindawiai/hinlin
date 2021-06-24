<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2012 - 2018 Microchip Technology Inc., and its subsidiaries.
 * All rights reserved.
 */

#अगर_अघोषित WILC_WLAN_CFG_H
#घोषणा WILC_WLAN_CFG_H

काष्ठा wilc_cfg_byte अणु
	u16 id;
	u8 val;
पूर्ण;

काष्ठा wilc_cfg_hword अणु
	u16 id;
	u16 val;
पूर्ण;

काष्ठा wilc_cfg_word अणु
	u16 id;
	u32 val;
पूर्ण;

काष्ठा wilc_cfg_str अणु
	u16 id;
	u8 *str;
पूर्ण;

काष्ठा wilc_cfg_str_vals अणु
	u8 mac_address[7];
	u8 firmware_version[129];
	u8 assoc_rsp[256];
पूर्ण;

काष्ठा wilc_cfg अणु
	काष्ठा wilc_cfg_byte *b;
	काष्ठा wilc_cfg_hword *hw;
	काष्ठा wilc_cfg_word *w;
	काष्ठा wilc_cfg_str *s;
	काष्ठा wilc_cfg_str_vals *str_vals;
पूर्ण;

काष्ठा wilc;
पूर्णांक wilc_wlan_cfg_set_wid(u8 *frame, u32 offset, u16 id, u8 *buf, पूर्णांक size);
पूर्णांक wilc_wlan_cfg_get_wid(u8 *frame, u32 offset, u16 id);
पूर्णांक wilc_wlan_cfg_get_val(काष्ठा wilc *wl, u16 wid, u8 *buffer,
			  u32 buffer_size);
व्योम wilc_wlan_cfg_indicate_rx(काष्ठा wilc *wilc, u8 *frame, पूर्णांक size,
			       काष्ठा wilc_cfg_rsp *rsp);
पूर्णांक wilc_wlan_cfg_init(काष्ठा wilc *wl);
व्योम wilc_wlan_cfg_deinit(काष्ठा wilc *wl);

#पूर्ण_अगर
