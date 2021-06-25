<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#समावेश "main.h"
#समावेश "sec.h"
#समावेश "reg.h"

पूर्णांक rtw_sec_get_मुक्त_cam(काष्ठा rtw_sec_desc *sec)
अणु
	/* अगर शेष key search is enabled, the first 4 cam entries
	 * are used to direct map to group key with its key->key_idx, so
	 * driver should use cam entries after 4 to install pairwise key
	 */
	अगर (sec->शेष_key_search)
		वापस find_next_zero_bit(sec->cam_map, RTW_MAX_SEC_CAM_NUM,
					  RTW_SEC_DEFAULT_KEY_NUM);

	वापस find_first_zero_bit(sec->cam_map, RTW_MAX_SEC_CAM_NUM);
पूर्ण

व्योम rtw_sec_ग_लिखो_cam(काष्ठा rtw_dev *rtwdev,
		       काष्ठा rtw_sec_desc *sec,
		       काष्ठा ieee80211_sta *sta,
		       काष्ठा ieee80211_key_conf *key,
		       u8 hw_key_type, u8 hw_key_idx)
अणु
	काष्ठा rtw_cam_entry *cam = &sec->cam_table[hw_key_idx];
	u32 ग_लिखो_cmd;
	u32 command;
	u32 content;
	u32 addr;
	पूर्णांक i, j;

	set_bit(hw_key_idx, sec->cam_map);
	cam->valid = true;
	cam->group = !(key->flags & IEEE80211_KEY_FLAG_PAIRWISE);
	cam->hw_key_type = hw_key_type;
	cam->key = key;
	अगर (sta)
		ether_addr_copy(cam->addr, sta->addr);
	अन्यथा
		eth_broadcast_addr(cam->addr);

	ग_लिखो_cmd = RTW_SEC_CMD_WRITE_ENABLE | RTW_SEC_CMD_POLLING;
	addr = hw_key_idx << RTW_SEC_CAM_ENTRY_SHIFT;
	क्रम (i = 7; i >= 0; i--) अणु
		चयन (i) अणु
		हाल 0:
			content = ((key->keyidx & 0x3))		|
				  ((hw_key_type & 0x7)	<< 2)	|
				  (cam->group		<< 6)	|
				  (cam->valid		<< 15)	|
				  (cam->addr[0]		<< 16)	|
				  (cam->addr[1]		<< 24);
			अवरोध;
		हाल 1:
			content = (cam->addr[2])		|
				  (cam->addr[3]		<< 8)	|
				  (cam->addr[4]		<< 16)	|
				  (cam->addr[5]		<< 24);
			अवरोध;
		हाल 6:
		हाल 7:
			content = 0;
			अवरोध;
		शेष:
			j = (i - 2) << 2;
			content = (key->key[j])			|
				  (key->key[j + 1]	<< 8)	|
				  (key->key[j + 2]	<< 16)	|
				  (key->key[j + 3]	<< 24);
			अवरोध;
		पूर्ण

		command = ग_लिखो_cmd | (addr + i);
		rtw_ग_लिखो32(rtwdev, RTW_SEC_WRITE_REG, content);
		rtw_ग_लिखो32(rtwdev, RTW_SEC_CMD_REG, command);
	पूर्ण
पूर्ण

व्योम rtw_sec_clear_cam(काष्ठा rtw_dev *rtwdev,
		       काष्ठा rtw_sec_desc *sec,
		       u8 hw_key_idx)
अणु
	काष्ठा rtw_cam_entry *cam = &sec->cam_table[hw_key_idx];
	u32 ग_लिखो_cmd;
	u32 command;
	u32 addr;

	clear_bit(hw_key_idx, sec->cam_map);
	cam->valid = false;
	cam->key = शून्य;
	eth_zero_addr(cam->addr);

	ग_लिखो_cmd = RTW_SEC_CMD_WRITE_ENABLE | RTW_SEC_CMD_POLLING;
	addr = hw_key_idx << RTW_SEC_CAM_ENTRY_SHIFT;
	command = ग_लिखो_cmd | addr;
	rtw_ग_लिखो32(rtwdev, RTW_SEC_WRITE_REG, 0);
	rtw_ग_लिखो32(rtwdev, RTW_SEC_CMD_REG, command);
पूर्ण

u8 rtw_sec_cam_pg_backup(काष्ठा rtw_dev *rtwdev, u8 *used_cam)
अणु
	काष्ठा rtw_sec_desc *sec = &rtwdev->sec;
	u8 offset = 0;
	u8 count, n;

	अगर (!used_cam)
		वापस 0;

	क्रम (count = 0; count < MAX_PG_CAM_BACKUP_NUM; count++) अणु
		n = find_next_bit(sec->cam_map, RTW_MAX_SEC_CAM_NUM, offset);
		अगर (n == RTW_MAX_SEC_CAM_NUM)
			अवरोध;

		used_cam[count] = n;
		offset = n + 1;
	पूर्ण

	वापस count;
पूर्ण

व्योम rtw_sec_enable_sec_engine(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_sec_desc *sec = &rtwdev->sec;
	u16 ctrl_reg;
	u16 sec_config;

	/* शेष use शेष key search क्रम now */
	sec->शेष_key_search = true;

	ctrl_reg = rtw_पढ़ो16(rtwdev, REG_CR);
	ctrl_reg |= RTW_SEC_ENGINE_EN;
	rtw_ग_लिखो16(rtwdev, REG_CR, ctrl_reg);

	sec_config = rtw_पढ़ो16(rtwdev, RTW_SEC_CONFIG);

	sec_config |= RTW_SEC_TX_DEC_EN | RTW_SEC_RX_DEC_EN;
	अगर (sec->शेष_key_search)
		sec_config |= RTW_SEC_TX_UNI_USE_DK | RTW_SEC_RX_UNI_USE_DK |
			      RTW_SEC_TX_BC_USE_DK | RTW_SEC_RX_BC_USE_DK;

	rtw_ग_लिखो16(rtwdev, RTW_SEC_CONFIG, sec_config);
पूर्ण
