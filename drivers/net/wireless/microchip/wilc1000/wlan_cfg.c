<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2012 - 2018 Microchip Technology Inc., and its subsidiaries.
 * All rights reserved.
 */

#समावेश <linux/bitfield.h>
#समावेश "wlan_if.h"
#समावेश "wlan.h"
#समावेश "wlan_cfg.h"
#समावेश "netdev.h"

क्रमागत cfg_cmd_type अणु
	CFG_BYTE_CMD	= 0,
	CFG_HWORD_CMD	= 1,
	CFG_WORD_CMD	= 2,
	CFG_STR_CMD	= 3,
	CFG_BIN_CMD	= 4
पूर्ण;

अटल स्थिर काष्ठा wilc_cfg_byte g_cfg_byte[] = अणु
	अणुWID_STATUS, 0पूर्ण,
	अणुWID_RSSI, 0पूर्ण,
	अणुWID_LINKSPEED, 0पूर्ण,
	अणुWID_NIL, 0पूर्ण
पूर्ण;

अटल स्थिर काष्ठा wilc_cfg_hword g_cfg_hword[] = अणु
	अणुWID_NIL, 0पूर्ण
पूर्ण;

अटल स्थिर काष्ठा wilc_cfg_word g_cfg_word[] = अणु
	अणुWID_FAILED_COUNT, 0पूर्ण,
	अणुWID_RECEIVED_FRAGMENT_COUNT, 0पूर्ण,
	अणुWID_SUCCESS_FRAME_COUNT, 0पूर्ण,
	अणुWID_GET_INACTIVE_TIME, 0पूर्ण,
	अणुWID_NIL, 0पूर्ण

पूर्ण;

अटल स्थिर काष्ठा wilc_cfg_str g_cfg_str[] = अणु
	अणुWID_FIRMWARE_VERSION, शून्यपूर्ण,
	अणुWID_MAC_ADDR, शून्यपूर्ण,
	अणुWID_ASSOC_RES_INFO, शून्यपूर्ण,
	अणुWID_NIL, शून्यपूर्ण
पूर्ण;

#घोषणा WILC_RESP_MSG_TYPE_CONFIG_REPLY		'R'
#घोषणा WILC_RESP_MSG_TYPE_STATUS_INFO		'I'
#घोषणा WILC_RESP_MSG_TYPE_NETWORK_INFO		'N'
#घोषणा WILC_RESP_MSG_TYPE_SCAN_COMPLETE	'S'

/********************************************
 *
 *      Configuration Functions
 *
 ********************************************/

अटल पूर्णांक wilc_wlan_cfg_set_byte(u8 *frame, u32 offset, u16 id, u8 val8)
अणु
	अगर ((offset + 4) >= WILC_MAX_CFG_FRAME_SIZE)
		वापस 0;

	put_unaligned_le16(id, &frame[offset]);
	put_unaligned_le16(1, &frame[offset + 2]);
	frame[offset + 4] = val8;
	वापस 5;
पूर्ण

अटल पूर्णांक wilc_wlan_cfg_set_hword(u8 *frame, u32 offset, u16 id, u16 val16)
अणु
	अगर ((offset + 5) >= WILC_MAX_CFG_FRAME_SIZE)
		वापस 0;

	put_unaligned_le16(id, &frame[offset]);
	put_unaligned_le16(2, &frame[offset + 2]);
	put_unaligned_le16(val16, &frame[offset + 4]);

	वापस 6;
पूर्ण

अटल पूर्णांक wilc_wlan_cfg_set_word(u8 *frame, u32 offset, u16 id, u32 val32)
अणु
	अगर ((offset + 7) >= WILC_MAX_CFG_FRAME_SIZE)
		वापस 0;

	put_unaligned_le16(id, &frame[offset]);
	put_unaligned_le16(4, &frame[offset + 2]);
	put_unaligned_le32(val32, &frame[offset + 4]);

	वापस 8;
पूर्ण

अटल पूर्णांक wilc_wlan_cfg_set_str(u8 *frame, u32 offset, u16 id, u8 *str,
				 u32 size)
अणु
	अगर ((offset + size + 4) >= WILC_MAX_CFG_FRAME_SIZE)
		वापस 0;

	put_unaligned_le16(id, &frame[offset]);
	put_unaligned_le16(size, &frame[offset + 2]);
	अगर (str && size != 0)
		स_नकल(&frame[offset + 4], str, size);

	वापस (size + 4);
पूर्ण

अटल पूर्णांक wilc_wlan_cfg_set_bin(u8 *frame, u32 offset, u16 id, u8 *b, u32 size)
अणु
	u32 i;
	u8 checksum = 0;

	अगर ((offset + size + 5) >= WILC_MAX_CFG_FRAME_SIZE)
		वापस 0;

	put_unaligned_le16(id, &frame[offset]);
	put_unaligned_le16(size, &frame[offset + 2]);

	अगर ((b) && size != 0) अणु
		स_नकल(&frame[offset + 4], b, size);
		क्रम (i = 0; i < size; i++)
			checksum += frame[offset + i + 4];
	पूर्ण

	frame[offset + size + 4] = checksum;

	वापस (size + 5);
पूर्ण

/********************************************
 *
 *      Configuration Response Functions
 *
 ********************************************/

अटल व्योम wilc_wlan_parse_response_frame(काष्ठा wilc *wl, u8 *info, पूर्णांक size)
अणु
	u16 wid;
	u32 len = 0, i = 0;
	काष्ठा wilc_cfg *cfg = &wl->cfg;

	जबतक (size > 0) अणु
		i = 0;
		wid = get_unaligned_le16(info);

		चयन (FIELD_GET(WILC_WID_TYPE, wid)) अणु
		हाल WID_CHAR:
			जबतक (cfg->b[i].id != WID_NIL && cfg->b[i].id != wid)
				i++;

			अगर (cfg->b[i].id == wid)
				cfg->b[i].val = info[4];

			len = 3;
			अवरोध;

		हाल WID_SHORT:
			जबतक (cfg->hw[i].id != WID_NIL && cfg->hw[i].id != wid)
				i++;

			अगर (cfg->hw[i].id == wid)
				cfg->hw[i].val = get_unaligned_le16(&info[4]);

			len = 4;
			अवरोध;

		हाल WID_INT:
			जबतक (cfg->w[i].id != WID_NIL && cfg->w[i].id != wid)
				i++;

			अगर (cfg->w[i].id == wid)
				cfg->w[i].val = get_unaligned_le32(&info[4]);

			len = 6;
			अवरोध;

		हाल WID_STR:
			जबतक (cfg->s[i].id != WID_NIL && cfg->s[i].id != wid)
				i++;

			अगर (cfg->s[i].id == wid)
				स_नकल(cfg->s[i].str, &info[2], info[2] + 2);

			len = 2 + info[2];
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
		size -= (2 + len);
		info += (2 + len);
	पूर्ण
पूर्ण

अटल व्योम wilc_wlan_parse_info_frame(काष्ठा wilc *wl, u8 *info)
अणु
	u32 wid, len;

	wid = get_unaligned_le16(info);

	len = info[2];

	अगर (len == 1 && wid == WID_STATUS) अणु
		पूर्णांक i = 0;

		जबतक (wl->cfg.b[i].id != WID_NIL &&
		       wl->cfg.b[i].id != wid)
			i++;

		अगर (wl->cfg.b[i].id == wid)
			wl->cfg.b[i].val = info[3];
	पूर्ण
पूर्ण

/********************************************
 *
 *      Configuration Exported Functions
 *
 ********************************************/

पूर्णांक wilc_wlan_cfg_set_wid(u8 *frame, u32 offset, u16 id, u8 *buf, पूर्णांक size)
अणु
	u8 type = FIELD_GET(WILC_WID_TYPE, id);
	पूर्णांक ret = 0;

	चयन (type) अणु
	हाल CFG_BYTE_CMD:
		अगर (size >= 1)
			ret = wilc_wlan_cfg_set_byte(frame, offset, id, *buf);
		अवरोध;

	हाल CFG_HWORD_CMD:
		अगर (size >= 2)
			ret = wilc_wlan_cfg_set_hword(frame, offset, id,
						      *((u16 *)buf));
		अवरोध;

	हाल CFG_WORD_CMD:
		अगर (size >= 4)
			ret = wilc_wlan_cfg_set_word(frame, offset, id,
						     *((u32 *)buf));
		अवरोध;

	हाल CFG_STR_CMD:
		ret = wilc_wlan_cfg_set_str(frame, offset, id, buf, size);
		अवरोध;

	हाल CFG_BIN_CMD:
		ret = wilc_wlan_cfg_set_bin(frame, offset, id, buf, size);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक wilc_wlan_cfg_get_wid(u8 *frame, u32 offset, u16 id)
अणु
	अगर ((offset + 2) >= WILC_MAX_CFG_FRAME_SIZE)
		वापस 0;

	put_unaligned_le16(id, &frame[offset]);

	वापस 2;
पूर्ण

पूर्णांक wilc_wlan_cfg_get_val(काष्ठा wilc *wl, u16 wid, u8 *buffer,
			  u32 buffer_size)
अणु
	u8 type = FIELD_GET(WILC_WID_TYPE, wid);
	पूर्णांक i, ret = 0;
	काष्ठा wilc_cfg *cfg = &wl->cfg;

	i = 0;
	अगर (type == CFG_BYTE_CMD) अणु
		जबतक (cfg->b[i].id != WID_NIL && cfg->b[i].id != wid)
			i++;

		अगर (cfg->b[i].id == wid) अणु
			स_नकल(buffer, &cfg->b[i].val, 1);
			ret = 1;
		पूर्ण
	पूर्ण अन्यथा अगर (type == CFG_HWORD_CMD) अणु
		जबतक (cfg->hw[i].id != WID_NIL && cfg->hw[i].id != wid)
			i++;

		अगर (cfg->hw[i].id == wid) अणु
			स_नकल(buffer, &cfg->hw[i].val, 2);
			ret = 2;
		पूर्ण
	पूर्ण अन्यथा अगर (type == CFG_WORD_CMD) अणु
		जबतक (cfg->w[i].id != WID_NIL && cfg->w[i].id != wid)
			i++;

		अगर (cfg->w[i].id == wid) अणु
			स_नकल(buffer, &cfg->w[i].val, 4);
			ret = 4;
		पूर्ण
	पूर्ण अन्यथा अगर (type == CFG_STR_CMD) अणु
		जबतक (cfg->s[i].id != WID_NIL && cfg->s[i].id != wid)
			i++;

		अगर (cfg->s[i].id == wid) अणु
			u16 size = get_unaligned_le16(cfg->s[i].str);

			अगर (buffer_size >= size) अणु
				स_नकल(buffer, &cfg->s[i].str[2], size);
				ret = size;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

व्योम wilc_wlan_cfg_indicate_rx(काष्ठा wilc *wilc, u8 *frame, पूर्णांक size,
			       काष्ठा wilc_cfg_rsp *rsp)
अणु
	u8 msg_type;
	u8 msg_id;

	msg_type = frame[0];
	msg_id = frame[1];      /* seq no */
	frame += 4;
	size -= 4;
	rsp->type = 0;

	चयन (msg_type) अणु
	हाल WILC_RESP_MSG_TYPE_CONFIG_REPLY:
		wilc_wlan_parse_response_frame(wilc, frame, size);
		rsp->type = WILC_CFG_RSP;
		rsp->seq_no = msg_id;
		अवरोध;

	हाल WILC_RESP_MSG_TYPE_STATUS_INFO:
		wilc_wlan_parse_info_frame(wilc, frame);
		rsp->type = WILC_CFG_RSP_STATUS;
		rsp->seq_no = msg_id;
		/* call host पूर्णांकerface info parse as well */
		wilc_gnrl_async_info_received(wilc, frame - 4, size + 4);
		अवरोध;

	हाल WILC_RESP_MSG_TYPE_NETWORK_INFO:
		wilc_network_info_received(wilc, frame - 4, size + 4);
		अवरोध;

	हाल WILC_RESP_MSG_TYPE_SCAN_COMPLETE:
		wilc_scan_complete_received(wilc, frame - 4, size + 4);
		अवरोध;

	शेष:
		rsp->seq_no = msg_id;
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक wilc_wlan_cfg_init(काष्ठा wilc *wl)
अणु
	काष्ठा wilc_cfg_str_vals *str_vals;
	पूर्णांक i = 0;

	wl->cfg.b = kmemdup(g_cfg_byte, माप(g_cfg_byte), GFP_KERNEL);
	अगर (!wl->cfg.b)
		वापस -ENOMEM;

	wl->cfg.hw = kmemdup(g_cfg_hword, माप(g_cfg_hword), GFP_KERNEL);
	अगर (!wl->cfg.hw)
		जाओ out_b;

	wl->cfg.w = kmemdup(g_cfg_word, माप(g_cfg_word), GFP_KERNEL);
	अगर (!wl->cfg.w)
		जाओ out_hw;

	wl->cfg.s = kmemdup(g_cfg_str, माप(g_cfg_str), GFP_KERNEL);
	अगर (!wl->cfg.s)
		जाओ out_w;

	str_vals = kzalloc(माप(*str_vals), GFP_KERNEL);
	अगर (!str_vals)
		जाओ out_s;

	wl->cfg.str_vals = str_vals;
	/* store the string cfg parameters */
	wl->cfg.s[i].id = WID_FIRMWARE_VERSION;
	wl->cfg.s[i].str = str_vals->firmware_version;
	i++;
	wl->cfg.s[i].id = WID_MAC_ADDR;
	wl->cfg.s[i].str = str_vals->mac_address;
	i++;
	wl->cfg.s[i].id = WID_ASSOC_RES_INFO;
	wl->cfg.s[i].str = str_vals->assoc_rsp;
	i++;
	wl->cfg.s[i].id = WID_NIL;
	wl->cfg.s[i].str = शून्य;
	वापस 0;

out_s:
	kमुक्त(wl->cfg.s);
out_w:
	kमुक्त(wl->cfg.w);
out_hw:
	kमुक्त(wl->cfg.hw);
out_b:
	kमुक्त(wl->cfg.b);
	वापस -ENOMEM;
पूर्ण

व्योम wilc_wlan_cfg_deinit(काष्ठा wilc *wl)
अणु
	kमुक्त(wl->cfg.b);
	kमुक्त(wl->cfg.hw);
	kमुक्त(wl->cfg.w);
	kमुक्त(wl->cfg.s);
	kमुक्त(wl->cfg.str_vals);
पूर्ण
