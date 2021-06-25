<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#समावेश <linux/module.h>
#समावेश "main.h"
#समावेश "coex.h"
#समावेश "fw.h"
#समावेश "tx.h"
#समावेश "rx.h"
#समावेश "phy.h"
#समावेश "rtw8822c.h"
#समावेश "rtw8822c_table.h"
#समावेश "mac.h"
#समावेश "reg.h"
#समावेश "debug.h"
#समावेश "util.h"
#समावेश "bf.h"
#समावेश "efuse.h"
#समावेश "coex.h"

#घोषणा IQK_DONE_8822C 0xaa

अटल व्योम rtw8822c_config_trx_mode(काष्ठा rtw_dev *rtwdev, u8 tx_path,
				     u8 rx_path, bool is_tx2_path);

अटल व्योम rtw8822ce_efuse_parsing(काष्ठा rtw_efuse *efuse,
				    काष्ठा rtw8822c_efuse *map)
अणु
	ether_addr_copy(efuse->addr, map->e.mac_addr);
पूर्ण

अटल पूर्णांक rtw8822c_पढ़ो_efuse(काष्ठा rtw_dev *rtwdev, u8 *log_map)
अणु
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	काष्ठा rtw8822c_efuse *map;
	पूर्णांक i;

	map = (काष्ठा rtw8822c_efuse *)log_map;

	efuse->rfe_option = map->rfe_option;
	efuse->rf_board_option = map->rf_board_option;
	efuse->crystal_cap = map->xtal_k & XCAP_MASK;
	efuse->channel_plan = map->channel_plan;
	efuse->country_code[0] = map->country_code[0];
	efuse->country_code[1] = map->country_code[1];
	efuse->bt_setting = map->rf_bt_setting;
	efuse->regd = map->rf_board_option & 0x7;
	efuse->thermal_meter[RF_PATH_A] = map->path_a_thermal;
	efuse->thermal_meter[RF_PATH_B] = map->path_b_thermal;
	efuse->thermal_meter_k =
			(map->path_a_thermal + map->path_b_thermal) >> 1;
	efuse->घातer_track_type = (map->tx_pwr_calibrate_rate >> 4) & 0xf;

	क्रम (i = 0; i < 4; i++)
		efuse->txpwr_idx_table[i] = map->txpwr_idx_table[i];

	चयन (rtw_hci_type(rtwdev)) अणु
	हाल RTW_HCI_TYPE_PCIE:
		rtw8822ce_efuse_parsing(efuse, map);
		अवरोध;
	शेष:
		/* unsupported now */
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rtw8822c_header_file_init(काष्ठा rtw_dev *rtwdev, bool pre)
अणु
	rtw_ग_लिखो32_set(rtwdev, REG_3WIRE, BIT_3WIRE_TX_EN | BIT_3WIRE_RX_EN);
	rtw_ग_लिखो32_set(rtwdev, REG_3WIRE, BIT_3WIRE_PI_ON);
	rtw_ग_लिखो32_set(rtwdev, REG_3WIRE2, BIT_3WIRE_TX_EN | BIT_3WIRE_RX_EN);
	rtw_ग_लिखो32_set(rtwdev, REG_3WIRE2, BIT_3WIRE_PI_ON);

	अगर (pre)
		rtw_ग_लिखो32_clr(rtwdev, REG_ENCCK, BIT_CCK_OFDM_BLK_EN);
	अन्यथा
		rtw_ग_लिखो32_set(rtwdev, REG_ENCCK, BIT_CCK_OFDM_BLK_EN);
पूर्ण

अटल व्योम rtw8822c_dac_backup_reg(काष्ठा rtw_dev *rtwdev,
				    काष्ठा rtw_backup_info *backup,
				    काष्ठा rtw_backup_info *backup_rf)
अणु
	u32 path, i;
	u32 val;
	u32 reg;
	u32 rf_addr[DACK_RF_8822C] = अणु0x8fपूर्ण;
	u32 addrs[DACK_REG_8822C] = अणु0x180c, 0x1810, 0x410c, 0x4110,
				     0x1c3c, 0x1c24, 0x1d70, 0x9b4,
				     0x1a00, 0x1a14, 0x1d58, 0x1c38,
				     0x1e24, 0x1e28, 0x1860, 0x4160पूर्ण;

	क्रम (i = 0; i < DACK_REG_8822C; i++) अणु
		backup[i].len = 4;
		backup[i].reg = addrs[i];
		backup[i].val = rtw_पढ़ो32(rtwdev, addrs[i]);
	पूर्ण

	क्रम (path = 0; path < DACK_PATH_8822C; path++) अणु
		क्रम (i = 0; i < DACK_RF_8822C; i++) अणु
			reg = rf_addr[i];
			val = rtw_पढ़ो_rf(rtwdev, path, reg, RFREG_MASK);
			backup_rf[path * i + i].reg = reg;
			backup_rf[path * i + i].val = val;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rtw8822c_dac_restore_reg(काष्ठा rtw_dev *rtwdev,
				     काष्ठा rtw_backup_info *backup,
				     काष्ठा rtw_backup_info *backup_rf)
अणु
	u32 path, i;
	u32 val;
	u32 reg;

	rtw_restore_reg(rtwdev, backup, DACK_REG_8822C);

	क्रम (path = 0; path < DACK_PATH_8822C; path++) अणु
		क्रम (i = 0; i < DACK_RF_8822C; i++) अणु
			val = backup_rf[path * i + i].val;
			reg = backup_rf[path * i + i].reg;
			rtw_ग_लिखो_rf(rtwdev, path, reg, RFREG_MASK, val);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rtw8822c_rf_minmax_cmp(काष्ठा rtw_dev *rtwdev, u32 value,
				   u32 *min, u32 *max)
अणु
	अगर (value >= 0x200) अणु
		अगर (*min >= 0x200) अणु
			अगर (*min > value)
				*min = value;
		पूर्ण अन्यथा अणु
			*min = value;
		पूर्ण
		अगर (*max >= 0x200) अणु
			अगर (*max < value)
				*max = value;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (*min < 0x200) अणु
			अगर (*min > value)
				*min = value;
		पूर्ण

		अगर (*max  >= 0x200) अणु
			*max = value;
		पूर्ण अन्यथा अणु
			अगर (*max < value)
				*max = value;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __rtw8822c_dac_iq_sort(काष्ठा rtw_dev *rtwdev, u32 *v1, u32 *v2)
अणु
	अगर (*v1 >= 0x200 && *v2 >= 0x200) अणु
		अगर (*v1 > *v2)
			swap(*v1, *v2);
	पूर्ण अन्यथा अगर (*v1 < 0x200 && *v2 < 0x200) अणु
		अगर (*v1 > *v2)
			swap(*v1, *v2);
	पूर्ण अन्यथा अगर (*v1 < 0x200 && *v2 >= 0x200) अणु
		swap(*v1, *v2);
	पूर्ण
पूर्ण

अटल व्योम rtw8822c_dac_iq_sort(काष्ठा rtw_dev *rtwdev, u32 *iv, u32 *qv)
अणु
	u32 i, j;

	क्रम (i = 0; i < DACK_SN_8822C - 1; i++) अणु
		क्रम (j = 0; j < (DACK_SN_8822C - 1 - i) ; j++) अणु
			__rtw8822c_dac_iq_sort(rtwdev, &iv[j], &iv[j + 1]);
			__rtw8822c_dac_iq_sort(rtwdev, &qv[j], &qv[j + 1]);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rtw8822c_dac_iq_offset(काष्ठा rtw_dev *rtwdev, u32 *vec, u32 *val)
अणु
	u32 p, m, t, i;

	m = 0;
	p = 0;
	क्रम (i = 10; i < DACK_SN_8822C - 10; i++) अणु
		अगर (vec[i] > 0x200)
			m = (0x400 - vec[i]) + m;
		अन्यथा
			p = vec[i] + p;
	पूर्ण

	अगर (p > m) अणु
		t = p - m;
		t = t / (DACK_SN_8822C - 20);
	पूर्ण अन्यथा अणु
		t = m - p;
		t = t / (DACK_SN_8822C - 20);
		अगर (t != 0x0)
			t = 0x400 - t;
	पूर्ण

	*val = t;
पूर्ण

अटल u32 rtw8822c_get_path_ग_लिखो_addr(u8 path)
अणु
	u32 base_addr;

	चयन (path) अणु
	हाल RF_PATH_A:
		base_addr = 0x1800;
		अवरोध;
	हाल RF_PATH_B:
		base_addr = 0x4100;
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस -1;
	पूर्ण

	वापस base_addr;
पूर्ण

अटल u32 rtw8822c_get_path_पढ़ो_addr(u8 path)
अणु
	u32 base_addr;

	चयन (path) अणु
	हाल RF_PATH_A:
		base_addr = 0x2800;
		अवरोध;
	हाल RF_PATH_B:
		base_addr = 0x4500;
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस -1;
	पूर्ण

	वापस base_addr;
पूर्ण

अटल bool rtw8822c_dac_iq_check(काष्ठा rtw_dev *rtwdev, u32 value)
अणु
	bool ret = true;

	अगर ((value >= 0x200 && (0x400 - value) > 0x64) ||
	    (value < 0x200 && value > 0x64)) अणु
		ret = false;
		rtw_dbg(rtwdev, RTW_DBG_RFK, "[DACK] Error overflow\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम rtw8822c_dac_cal_iq_sample(काष्ठा rtw_dev *rtwdev, u32 *iv, u32 *qv)
अणु
	u32 temp;
	पूर्णांक i = 0, cnt = 0;

	जबतक (i < DACK_SN_8822C && cnt < 10000) अणु
		cnt++;
		temp = rtw_पढ़ो32_mask(rtwdev, 0x2dbc, 0x3fffff);
		iv[i] = (temp & 0x3ff000) >> 12;
		qv[i] = temp & 0x3ff;

		अगर (rtw8822c_dac_iq_check(rtwdev, iv[i]) &&
		    rtw8822c_dac_iq_check(rtwdev, qv[i]))
			i++;
	पूर्ण
पूर्ण

अटल व्योम rtw8822c_dac_cal_iq_search(काष्ठा rtw_dev *rtwdev,
				       u32 *iv, u32 *qv,
				       u32 *i_value, u32 *q_value)
अणु
	u32 i_max = 0, q_max = 0, i_min = 0, q_min = 0;
	u32 i_delta, q_delta;
	u32 temp;
	पूर्णांक i, cnt = 0;

	करो अणु
		i_min = iv[0];
		i_max = iv[0];
		q_min = qv[0];
		q_max = qv[0];
		क्रम (i = 0; i < DACK_SN_8822C; i++) अणु
			rtw8822c_rf_minmax_cmp(rtwdev, iv[i], &i_min, &i_max);
			rtw8822c_rf_minmax_cmp(rtwdev, qv[i], &q_min, &q_max);
		पूर्ण

		अगर (i_max < 0x200 && i_min < 0x200)
			i_delta = i_max - i_min;
		अन्यथा अगर (i_max >= 0x200 && i_min >= 0x200)
			i_delta = i_max - i_min;
		अन्यथा
			i_delta = i_max + (0x400 - i_min);

		अगर (q_max < 0x200 && q_min < 0x200)
			q_delta = q_max - q_min;
		अन्यथा अगर (q_max >= 0x200 && q_min >= 0x200)
			q_delta = q_max - q_min;
		अन्यथा
			q_delta = q_max + (0x400 - q_min);

		rtw_dbg(rtwdev, RTW_DBG_RFK,
			"[DACK] i: min=0x%08x, max=0x%08x, delta=0x%08x\n",
			i_min, i_max, i_delta);
		rtw_dbg(rtwdev, RTW_DBG_RFK,
			"[DACK] q: min=0x%08x, max=0x%08x, delta=0x%08x\n",
			q_min, q_max, q_delta);

		rtw8822c_dac_iq_sort(rtwdev, iv, qv);

		अगर (i_delta > 5 || q_delta > 5) अणु
			temp = rtw_पढ़ो32_mask(rtwdev, 0x2dbc, 0x3fffff);
			iv[0] = (temp & 0x3ff000) >> 12;
			qv[0] = temp & 0x3ff;
			temp = rtw_पढ़ो32_mask(rtwdev, 0x2dbc, 0x3fffff);
			iv[DACK_SN_8822C - 1] = (temp & 0x3ff000) >> 12;
			qv[DACK_SN_8822C - 1] = temp & 0x3ff;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण जबतक (cnt++ < 100);

	rtw8822c_dac_iq_offset(rtwdev, iv, i_value);
	rtw8822c_dac_iq_offset(rtwdev, qv, q_value);
पूर्ण

अटल व्योम rtw8822c_dac_cal_rf_mode(काष्ठा rtw_dev *rtwdev,
				     u32 *i_value, u32 *q_value)
अणु
	u32 iv[DACK_SN_8822C], qv[DACK_SN_8822C];
	u32 rf_a, rf_b;

	rf_a = rtw_पढ़ो_rf(rtwdev, RF_PATH_A, 0x0, RFREG_MASK);
	rf_b = rtw_पढ़ो_rf(rtwdev, RF_PATH_B, 0x0, RFREG_MASK);

	rtw_dbg(rtwdev, RTW_DBG_RFK, "[DACK] RF path-A=0x%05x\n", rf_a);
	rtw_dbg(rtwdev, RTW_DBG_RFK, "[DACK] RF path-B=0x%05x\n", rf_b);

	rtw8822c_dac_cal_iq_sample(rtwdev, iv, qv);
	rtw8822c_dac_cal_iq_search(rtwdev, iv, qv, i_value, q_value);
पूर्ण

अटल व्योम rtw8822c_dac_bb_setting(काष्ठा rtw_dev *rtwdev)
अणु
	rtw_ग_लिखो32_mask(rtwdev, 0x1d58, 0xff8, 0x1ff);
	rtw_ग_लिखो32_mask(rtwdev, 0x1a00, 0x3, 0x2);
	rtw_ग_लिखो32_mask(rtwdev, 0x1a14, 0x300, 0x3);
	rtw_ग_लिखो32(rtwdev, 0x1d70, 0x7e7e7e7e);
	rtw_ग_लिखो32_mask(rtwdev, 0x180c, 0x3, 0x0);
	rtw_ग_लिखो32_mask(rtwdev, 0x410c, 0x3, 0x0);
	rtw_ग_लिखो32(rtwdev, 0x1b00, 0x00000008);
	rtw_ग_लिखो8(rtwdev, 0x1bcc, 0x3f);
	rtw_ग_लिखो32(rtwdev, 0x1b00, 0x0000000a);
	rtw_ग_लिखो8(rtwdev, 0x1bcc, 0x3f);
	rtw_ग_लिखो32_mask(rtwdev, 0x1e24, BIT(31), 0x0);
	rtw_ग_लिखो32_mask(rtwdev, 0x1e28, 0xf, 0x3);
पूर्ण

अटल व्योम rtw8822c_dac_cal_adc(काष्ठा rtw_dev *rtwdev,
				 u8 path, u32 *adc_ic, u32 *adc_qc)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u32 ic = 0, qc = 0, temp = 0;
	u32 base_addr;
	u32 path_sel;
	पूर्णांक i;

	rtw_dbg(rtwdev, RTW_DBG_RFK, "[DACK] ADCK path(%d)\n", path);

	base_addr = rtw8822c_get_path_ग_लिखो_addr(path);
	चयन (path) अणु
	हाल RF_PATH_A:
		path_sel = 0xa0000;
		अवरोध;
	हाल RF_PATH_B:
		path_sel = 0x80000;
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस;
	पूर्ण

	/* ADCK step1 */
	rtw_ग_लिखो32_mask(rtwdev, base_addr + 0x30, BIT(30), 0x0);
	अगर (path == RF_PATH_B)
		rtw_ग_लिखो32(rtwdev, base_addr + 0x30, 0x30db8041);
	rtw_ग_लिखो32(rtwdev, base_addr + 0x60, 0xf0040ff0);
	rtw_ग_लिखो32(rtwdev, base_addr + 0x0c, 0xdff00220);
	rtw_ग_लिखो32(rtwdev, base_addr + 0x10, 0x02dd08c4);
	rtw_ग_लिखो32(rtwdev, base_addr + 0x0c, 0x10000260);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, 0x0, RFREG_MASK, 0x10000);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_B, 0x0, RFREG_MASK, 0x10000);
	क्रम (i = 0; i < 10; i++) अणु
		rtw_dbg(rtwdev, RTW_DBG_RFK, "[DACK] ADCK count=%d\n", i);
		rtw_ग_लिखो32(rtwdev, 0x1c3c, path_sel + 0x8003);
		rtw_ग_लिखो32(rtwdev, 0x1c24, 0x00010002);
		rtw8822c_dac_cal_rf_mode(rtwdev, &ic, &qc);
		rtw_dbg(rtwdev, RTW_DBG_RFK,
			"[DACK] before: i=0x%x, q=0x%x\n", ic, qc);

		/* compensation value */
		अगर (ic != 0x0) अणु
			ic = 0x400 - ic;
			*adc_ic = ic;
		पूर्ण
		अगर (qc != 0x0) अणु
			qc = 0x400 - qc;
			*adc_qc = qc;
		पूर्ण
		temp = (ic & 0x3ff) | ((qc & 0x3ff) << 10);
		rtw_ग_लिखो32(rtwdev, base_addr + 0x68, temp);
		dm_info->dack_adck[path] = temp;
		rtw_dbg(rtwdev, RTW_DBG_RFK, "[DACK] ADCK 0x%08x=0x08%x\n",
			base_addr + 0x68, temp);
		/* check ADC DC offset */
		rtw_ग_लिखो32(rtwdev, 0x1c3c, path_sel + 0x8103);
		rtw8822c_dac_cal_rf_mode(rtwdev, &ic, &qc);
		rtw_dbg(rtwdev, RTW_DBG_RFK,
			"[DACK] after:  i=0x%08x, q=0x%08x\n", ic, qc);
		अगर (ic >= 0x200)
			ic = 0x400 - ic;
		अगर (qc >= 0x200)
			qc = 0x400 - qc;
		अगर (ic < 5 && qc < 5)
			अवरोध;
	पूर्ण

	/* ADCK step2 */
	rtw_ग_लिखो32(rtwdev, 0x1c3c, 0x00000003);
	rtw_ग_लिखो32(rtwdev, base_addr + 0x0c, 0x10000260);
	rtw_ग_लिखो32(rtwdev, base_addr + 0x10, 0x02d508c4);

	/* release pull low चयन on IQ path */
	rtw_ग_लिखो_rf(rtwdev, path, 0x8f, BIT(13), 0x1);
पूर्ण

अटल व्योम rtw8822c_dac_cal_step1(काष्ठा rtw_dev *rtwdev, u8 path)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u32 base_addr;
	u32 पढ़ो_addr;

	base_addr = rtw8822c_get_path_ग_लिखो_addr(path);
	पढ़ो_addr = rtw8822c_get_path_पढ़ो_addr(path);

	rtw_ग_लिखो32(rtwdev, base_addr + 0x68, dm_info->dack_adck[path]);
	rtw_ग_लिखो32(rtwdev, base_addr + 0x0c, 0xdff00220);
	अगर (path == RF_PATH_A) अणु
		rtw_ग_लिखो32(rtwdev, base_addr + 0x60, 0xf0040ff0);
		rtw_ग_लिखो32(rtwdev, 0x1c38, 0xffffffff);
	पूर्ण
	rtw_ग_लिखो32(rtwdev, base_addr + 0x10, 0x02d508c5);
	rtw_ग_लिखो32(rtwdev, 0x9b4, 0xdb66db00);
	rtw_ग_लिखो32(rtwdev, base_addr + 0xb0, 0x0a11fb88);
	rtw_ग_लिखो32(rtwdev, base_addr + 0xbc, 0x0008ff81);
	rtw_ग_लिखो32(rtwdev, base_addr + 0xc0, 0x0003d208);
	rtw_ग_लिखो32(rtwdev, base_addr + 0xcc, 0x0a11fb88);
	rtw_ग_लिखो32(rtwdev, base_addr + 0xd8, 0x0008ff81);
	rtw_ग_लिखो32(rtwdev, base_addr + 0xdc, 0x0003d208);
	rtw_ग_लिखो32(rtwdev, base_addr + 0xb8, 0x60000000);
	mdelay(2);
	rtw_ग_लिखो32(rtwdev, base_addr + 0xbc, 0x000aff8d);
	mdelay(2);
	rtw_ग_लिखो32(rtwdev, base_addr + 0xb0, 0x0a11fb89);
	rtw_ग_लिखो32(rtwdev, base_addr + 0xcc, 0x0a11fb89);
	mdelay(1);
	rtw_ग_लिखो32(rtwdev, base_addr + 0xb8, 0x62000000);
	rtw_ग_लिखो32(rtwdev, base_addr + 0xd4, 0x62000000);
	mdelay(20);
	अगर (!check_hw_पढ़ोy(rtwdev, पढ़ो_addr + 0x08, 0x7fff80, 0xffff) ||
	    !check_hw_पढ़ोy(rtwdev, पढ़ो_addr + 0x34, 0x7fff80, 0xffff))
		rtw_err(rtwdev, "failed to wait for dack ready\n");
	rtw_ग_लिखो32(rtwdev, base_addr + 0xb8, 0x02000000);
	mdelay(1);
	rtw_ग_लिखो32(rtwdev, base_addr + 0xbc, 0x0008ff87);
	rtw_ग_लिखो32(rtwdev, 0x9b4, 0xdb6db600);
	rtw_ग_लिखो32(rtwdev, base_addr + 0x10, 0x02d508c5);
	rtw_ग_लिखो32(rtwdev, base_addr + 0xbc, 0x0008ff87);
	rtw_ग_लिखो32(rtwdev, base_addr + 0x60, 0xf0000000);
पूर्ण

अटल व्योम rtw8822c_dac_cal_step2(काष्ठा rtw_dev *rtwdev,
				   u8 path, u32 *ic_out, u32 *qc_out)
अणु
	u32 base_addr;
	u32 ic, qc, ic_in, qc_in;

	base_addr = rtw8822c_get_path_ग_लिखो_addr(path);
	rtw_ग_लिखो32_mask(rtwdev, base_addr + 0xbc, 0xf0000000, 0x0);
	rtw_ग_लिखो32_mask(rtwdev, base_addr + 0xc0, 0xf, 0x8);
	rtw_ग_लिखो32_mask(rtwdev, base_addr + 0xd8, 0xf0000000, 0x0);
	rtw_ग_लिखो32_mask(rtwdev, base_addr + 0xdc, 0xf, 0x8);

	rtw_ग_लिखो32(rtwdev, 0x1b00, 0x00000008);
	rtw_ग_लिखो8(rtwdev, 0x1bcc, 0x03f);
	rtw_ग_लिखो32(rtwdev, base_addr + 0x0c, 0xdff00220);
	rtw_ग_लिखो32(rtwdev, base_addr + 0x10, 0x02d508c5);
	rtw_ग_लिखो32(rtwdev, 0x1c3c, 0x00088103);

	rtw8822c_dac_cal_rf_mode(rtwdev, &ic_in, &qc_in);
	ic = ic_in;
	qc = qc_in;

	/* compensation value */
	अगर (ic != 0x0)
		ic = 0x400 - ic;
	अगर (qc != 0x0)
		qc = 0x400 - qc;
	अगर (ic < 0x300) अणु
		ic = ic * 2 * 6 / 5;
		ic = ic + 0x80;
	पूर्ण अन्यथा अणु
		ic = (0x400 - ic) * 2 * 6 / 5;
		ic = 0x7f - ic;
	पूर्ण
	अगर (qc < 0x300) अणु
		qc = qc * 2 * 6 / 5;
		qc = qc + 0x80;
	पूर्ण अन्यथा अणु
		qc = (0x400 - qc) * 2 * 6 / 5;
		qc = 0x7f - qc;
	पूर्ण

	*ic_out = ic;
	*qc_out = qc;

	rtw_dbg(rtwdev, RTW_DBG_RFK, "[DACK] before i=0x%x, q=0x%x\n", ic_in, qc_in);
	rtw_dbg(rtwdev, RTW_DBG_RFK, "[DACK] after  i=0x%x, q=0x%x\n", ic, qc);
पूर्ण

अटल व्योम rtw8822c_dac_cal_step3(काष्ठा rtw_dev *rtwdev, u8 path,
				   u32 adc_ic, u32 adc_qc,
				   u32 *ic_in, u32 *qc_in,
				   u32 *i_out, u32 *q_out)
अणु
	u32 base_addr;
	u32 पढ़ो_addr;
	u32 ic, qc;
	u32 temp;

	base_addr = rtw8822c_get_path_ग_लिखो_addr(path);
	पढ़ो_addr = rtw8822c_get_path_पढ़ो_addr(path);
	ic = *ic_in;
	qc = *qc_in;

	rtw_ग_लिखो32(rtwdev, base_addr + 0x0c, 0xdff00220);
	rtw_ग_लिखो32(rtwdev, base_addr + 0x10, 0x02d508c5);
	rtw_ग_लिखो32(rtwdev, 0x9b4, 0xdb66db00);
	rtw_ग_लिखो32(rtwdev, base_addr + 0xb0, 0x0a11fb88);
	rtw_ग_लिखो32(rtwdev, base_addr + 0xbc, 0xc008ff81);
	rtw_ग_लिखो32(rtwdev, base_addr + 0xc0, 0x0003d208);
	rtw_ग_लिखो32_mask(rtwdev, base_addr + 0xbc, 0xf0000000, ic & 0xf);
	rtw_ग_लिखो32_mask(rtwdev, base_addr + 0xc0, 0xf, (ic & 0xf0) >> 4);
	rtw_ग_लिखो32(rtwdev, base_addr + 0xcc, 0x0a11fb88);
	rtw_ग_लिखो32(rtwdev, base_addr + 0xd8, 0xe008ff81);
	rtw_ग_लिखो32(rtwdev, base_addr + 0xdc, 0x0003d208);
	rtw_ग_लिखो32_mask(rtwdev, base_addr + 0xd8, 0xf0000000, qc & 0xf);
	rtw_ग_लिखो32_mask(rtwdev, base_addr + 0xdc, 0xf, (qc & 0xf0) >> 4);
	rtw_ग_लिखो32(rtwdev, base_addr + 0xb8, 0x60000000);
	mdelay(2);
	rtw_ग_लिखो32_mask(rtwdev, base_addr + 0xbc, 0xe, 0x6);
	mdelay(2);
	rtw_ग_लिखो32(rtwdev, base_addr + 0xb0, 0x0a11fb89);
	rtw_ग_लिखो32(rtwdev, base_addr + 0xcc, 0x0a11fb89);
	mdelay(1);
	rtw_ग_लिखो32(rtwdev, base_addr + 0xb8, 0x62000000);
	rtw_ग_लिखो32(rtwdev, base_addr + 0xd4, 0x62000000);
	mdelay(20);
	अगर (!check_hw_पढ़ोy(rtwdev, पढ़ो_addr + 0x24, 0x07f80000, ic) ||
	    !check_hw_पढ़ोy(rtwdev, पढ़ो_addr + 0x50, 0x07f80000, qc))
		rtw_err(rtwdev, "failed to write IQ vector to hardware\n");
	rtw_ग_लिखो32(rtwdev, base_addr + 0xb8, 0x02000000);
	mdelay(1);
	rtw_ग_लिखो32_mask(rtwdev, base_addr + 0xbc, 0xe, 0x3);
	rtw_ग_लिखो32(rtwdev, 0x9b4, 0xdb6db600);

	/* check DAC DC offset */
	temp = ((adc_ic + 0x10) & 0x3ff) | (((adc_qc + 0x10) & 0x3ff) << 10);
	rtw_ग_लिखो32(rtwdev, base_addr + 0x68, temp);
	rtw_ग_लिखो32(rtwdev, base_addr + 0x10, 0x02d508c5);
	rtw_ग_लिखो32(rtwdev, base_addr + 0x60, 0xf0000000);
	rtw8822c_dac_cal_rf_mode(rtwdev, &ic, &qc);
	अगर (ic >= 0x10)
		ic = ic - 0x10;
	अन्यथा
		ic = 0x400 - (0x10 - ic);

	अगर (qc >= 0x10)
		qc = qc - 0x10;
	अन्यथा
		qc = 0x400 - (0x10 - qc);

	*i_out = ic;
	*q_out = qc;

	अगर (ic >= 0x200)
		ic = 0x400 - ic;
	अगर (qc >= 0x200)
		qc = 0x400 - qc;

	*ic_in = ic;
	*qc_in = qc;

	rtw_dbg(rtwdev, RTW_DBG_RFK,
		"[DACK] after  DACK i=0x%x, q=0x%x\n", *i_out, *q_out);
पूर्ण

अटल व्योम rtw8822c_dac_cal_step4(काष्ठा rtw_dev *rtwdev, u8 path)
अणु
	u32 base_addr = rtw8822c_get_path_ग_लिखो_addr(path);

	rtw_ग_लिखो32(rtwdev, base_addr + 0x68, 0x0);
	rtw_ग_लिखो32(rtwdev, base_addr + 0x10, 0x02d508c4);
	rtw_ग_लिखो32_mask(rtwdev, base_addr + 0xbc, 0x1, 0x0);
	rtw_ग_लिखो32_mask(rtwdev, base_addr + 0x30, BIT(30), 0x1);
पूर्ण

अटल व्योम rtw8822c_dac_cal_backup_vec(काष्ठा rtw_dev *rtwdev,
					u8 path, u8 vec, u32 w_addr, u32 r_addr)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u16 val;
	u32 i;

	अगर (WARN_ON(vec >= 2))
		वापस;

	क्रम (i = 0; i < DACK_MSBK_BACKUP_NUM; i++) अणु
		rtw_ग_लिखो32_mask(rtwdev, w_addr, 0xf0000000, i);
		val = (u16)rtw_पढ़ो32_mask(rtwdev, r_addr, 0x7fc0000);
		dm_info->dack_msbk[path][vec][i] = val;
	पूर्ण
पूर्ण

अटल व्योम rtw8822c_dac_cal_backup_path(काष्ठा rtw_dev *rtwdev, u8 path)
अणु
	u32 w_off = 0x1c;
	u32 r_off = 0x2c;
	u32 w_addr, r_addr;

	अगर (WARN_ON(path >= 2))
		वापस;

	/* backup I vector */
	w_addr = rtw8822c_get_path_ग_लिखो_addr(path) + 0xb0;
	r_addr = rtw8822c_get_path_पढ़ो_addr(path) + 0x10;
	rtw8822c_dac_cal_backup_vec(rtwdev, path, 0, w_addr, r_addr);

	/* backup Q vector */
	w_addr = rtw8822c_get_path_ग_लिखो_addr(path) + 0xb0 + w_off;
	r_addr = rtw8822c_get_path_पढ़ो_addr(path) + 0x10 + r_off;
	rtw8822c_dac_cal_backup_vec(rtwdev, path, 1, w_addr, r_addr);
पूर्ण

अटल व्योम rtw8822c_dac_cal_backup_dck(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u8 val;

	val = (u8)rtw_पढ़ो32_mask(rtwdev, REG_DCKA_I_0, 0xf0000000);
	dm_info->dack_dck[RF_PATH_A][0][0] = val;
	val = (u8)rtw_पढ़ो32_mask(rtwdev, REG_DCKA_I_1, 0xf);
	dm_info->dack_dck[RF_PATH_A][0][1] = val;
	val = (u8)rtw_पढ़ो32_mask(rtwdev, REG_DCKA_Q_0, 0xf0000000);
	dm_info->dack_dck[RF_PATH_A][1][0] = val;
	val = (u8)rtw_पढ़ो32_mask(rtwdev, REG_DCKA_Q_1, 0xf);
	dm_info->dack_dck[RF_PATH_A][1][1] = val;

	val = (u8)rtw_पढ़ो32_mask(rtwdev, REG_DCKB_I_0, 0xf0000000);
	dm_info->dack_dck[RF_PATH_B][0][0] = val;
	val = (u8)rtw_पढ़ो32_mask(rtwdev, REG_DCKB_I_1, 0xf);
	dm_info->dack_dck[RF_PATH_B][1][0] = val;
	val = (u8)rtw_पढ़ो32_mask(rtwdev, REG_DCKB_Q_0, 0xf0000000);
	dm_info->dack_dck[RF_PATH_B][0][1] = val;
	val = (u8)rtw_पढ़ो32_mask(rtwdev, REG_DCKB_Q_1, 0xf);
	dm_info->dack_dck[RF_PATH_B][1][1] = val;
पूर्ण

अटल व्योम rtw8822c_dac_cal_backup(काष्ठा rtw_dev *rtwdev)
अणु
	u32 temp[3];

	temp[0] = rtw_पढ़ो32(rtwdev, 0x1860);
	temp[1] = rtw_पढ़ो32(rtwdev, 0x4160);
	temp[2] = rtw_पढ़ो32(rtwdev, 0x9b4);

	/* set घड़ी */
	rtw_ग_लिखो32(rtwdev, 0x9b4, 0xdb66db00);

	/* backup path-A I/Q */
	rtw_ग_लिखो32_clr(rtwdev, 0x1830, BIT(30));
	rtw_ग_लिखो32_mask(rtwdev, 0x1860, 0xfc000000, 0x3c);
	rtw8822c_dac_cal_backup_path(rtwdev, RF_PATH_A);

	/* backup path-B I/Q */
	rtw_ग_लिखो32_clr(rtwdev, 0x4130, BIT(30));
	rtw_ग_लिखो32_mask(rtwdev, 0x4160, 0xfc000000, 0x3c);
	rtw8822c_dac_cal_backup_path(rtwdev, RF_PATH_B);

	rtw8822c_dac_cal_backup_dck(rtwdev);
	rtw_ग_लिखो32_set(rtwdev, 0x1830, BIT(30));
	rtw_ग_लिखो32_set(rtwdev, 0x4130, BIT(30));

	rtw_ग_लिखो32(rtwdev, 0x1860, temp[0]);
	rtw_ग_लिखो32(rtwdev, 0x4160, temp[1]);
	rtw_ग_लिखो32(rtwdev, 0x9b4, temp[2]);
पूर्ण

अटल व्योम rtw8822c_dac_cal_restore_dck(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u8 val;

	rtw_ग_लिखो32_set(rtwdev, REG_DCKA_I_0, BIT(19));
	val = dm_info->dack_dck[RF_PATH_A][0][0];
	rtw_ग_लिखो32_mask(rtwdev, REG_DCKA_I_0, 0xf0000000, val);
	val = dm_info->dack_dck[RF_PATH_A][0][1];
	rtw_ग_लिखो32_mask(rtwdev, REG_DCKA_I_1, 0xf, val);

	rtw_ग_लिखो32_set(rtwdev, REG_DCKA_Q_0, BIT(19));
	val = dm_info->dack_dck[RF_PATH_A][1][0];
	rtw_ग_लिखो32_mask(rtwdev, REG_DCKA_Q_0, 0xf0000000, val);
	val = dm_info->dack_dck[RF_PATH_A][1][1];
	rtw_ग_लिखो32_mask(rtwdev, REG_DCKA_Q_1, 0xf, val);

	rtw_ग_लिखो32_set(rtwdev, REG_DCKB_I_0, BIT(19));
	val = dm_info->dack_dck[RF_PATH_B][0][0];
	rtw_ग_लिखो32_mask(rtwdev, REG_DCKB_I_0, 0xf0000000, val);
	val = dm_info->dack_dck[RF_PATH_B][0][1];
	rtw_ग_लिखो32_mask(rtwdev, REG_DCKB_I_1, 0xf, val);

	rtw_ग_लिखो32_set(rtwdev, REG_DCKB_Q_0, BIT(19));
	val = dm_info->dack_dck[RF_PATH_B][1][0];
	rtw_ग_लिखो32_mask(rtwdev, REG_DCKB_Q_0, 0xf0000000, val);
	val = dm_info->dack_dck[RF_PATH_B][1][1];
	rtw_ग_लिखो32_mask(rtwdev, REG_DCKB_Q_1, 0xf, val);
पूर्ण

अटल व्योम rtw8822c_dac_cal_restore_prepare(काष्ठा rtw_dev *rtwdev)
अणु
	rtw_ग_लिखो32(rtwdev, 0x9b4, 0xdb66db00);

	rtw_ग_लिखो32_mask(rtwdev, 0x18b0, BIT(27), 0x0);
	rtw_ग_लिखो32_mask(rtwdev, 0x18cc, BIT(27), 0x0);
	rtw_ग_लिखो32_mask(rtwdev, 0x41b0, BIT(27), 0x0);
	rtw_ग_लिखो32_mask(rtwdev, 0x41cc, BIT(27), 0x0);

	rtw_ग_लिखो32_mask(rtwdev, 0x1830, BIT(30), 0x0);
	rtw_ग_लिखो32_mask(rtwdev, 0x1860, 0xfc000000, 0x3c);
	rtw_ग_लिखो32_mask(rtwdev, 0x18b4, BIT(0), 0x1);
	rtw_ग_लिखो32_mask(rtwdev, 0x18d0, BIT(0), 0x1);

	rtw_ग_लिखो32_mask(rtwdev, 0x4130, BIT(30), 0x0);
	rtw_ग_लिखो32_mask(rtwdev, 0x4160, 0xfc000000, 0x3c);
	rtw_ग_लिखो32_mask(rtwdev, 0x41b4, BIT(0), 0x1);
	rtw_ग_लिखो32_mask(rtwdev, 0x41d0, BIT(0), 0x1);

	rtw_ग_लिखो32_mask(rtwdev, 0x18b0, 0xf00, 0x0);
	rtw_ग_लिखो32_mask(rtwdev, 0x18c0, BIT(14), 0x0);
	rtw_ग_लिखो32_mask(rtwdev, 0x18cc, 0xf00, 0x0);
	rtw_ग_लिखो32_mask(rtwdev, 0x18dc, BIT(14), 0x0);

	rtw_ग_लिखो32_mask(rtwdev, 0x18b0, BIT(0), 0x0);
	rtw_ग_लिखो32_mask(rtwdev, 0x18cc, BIT(0), 0x0);
	rtw_ग_लिखो32_mask(rtwdev, 0x18b0, BIT(0), 0x1);
	rtw_ग_लिखो32_mask(rtwdev, 0x18cc, BIT(0), 0x1);

	rtw8822c_dac_cal_restore_dck(rtwdev);

	rtw_ग_लिखो32_mask(rtwdev, 0x18c0, 0x38000, 0x7);
	rtw_ग_लिखो32_mask(rtwdev, 0x18dc, 0x38000, 0x7);
	rtw_ग_लिखो32_mask(rtwdev, 0x41c0, 0x38000, 0x7);
	rtw_ग_लिखो32_mask(rtwdev, 0x41dc, 0x38000, 0x7);

	rtw_ग_लिखो32_mask(rtwdev, 0x18b8, BIT(26) | BIT(25), 0x1);
	rtw_ग_लिखो32_mask(rtwdev, 0x18d4, BIT(26) | BIT(25), 0x1);

	rtw_ग_लिखो32_mask(rtwdev, 0x41b0, 0xf00, 0x0);
	rtw_ग_लिखो32_mask(rtwdev, 0x41c0, BIT(14), 0x0);
	rtw_ग_लिखो32_mask(rtwdev, 0x41cc, 0xf00, 0x0);
	rtw_ग_लिखो32_mask(rtwdev, 0x41dc, BIT(14), 0x0);

	rtw_ग_लिखो32_mask(rtwdev, 0x41b0, BIT(0), 0x0);
	rtw_ग_लिखो32_mask(rtwdev, 0x41cc, BIT(0), 0x0);
	rtw_ग_लिखो32_mask(rtwdev, 0x41b0, BIT(0), 0x1);
	rtw_ग_लिखो32_mask(rtwdev, 0x41cc, BIT(0), 0x1);

	rtw_ग_लिखो32_mask(rtwdev, 0x41b8, BIT(26) | BIT(25), 0x1);
	rtw_ग_लिखो32_mask(rtwdev, 0x41d4, BIT(26) | BIT(25), 0x1);
पूर्ण

अटल bool rtw8822c_dac_cal_restore_रुको(काष्ठा rtw_dev *rtwdev,
					  u32 target_addr, u32 toggle_addr)
अणु
	u32 cnt = 0;

	करो अणु
		rtw_ग_लिखो32_mask(rtwdev, toggle_addr, BIT(26) | BIT(25), 0x0);
		rtw_ग_लिखो32_mask(rtwdev, toggle_addr, BIT(26) | BIT(25), 0x2);

		अगर (rtw_पढ़ो32_mask(rtwdev, target_addr, 0xf) == 0x6)
			वापस true;

	पूर्ण जबतक (cnt++ < 100);

	वापस false;
पूर्ण

अटल bool rtw8822c_dac_cal_restore_path(काष्ठा rtw_dev *rtwdev, u8 path)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u32 w_off = 0x1c;
	u32 r_off = 0x2c;
	u32 w_i, r_i, w_q, r_q;
	u32 value;
	u32 i;

	w_i = rtw8822c_get_path_ग_लिखो_addr(path) + 0xb0;
	r_i = rtw8822c_get_path_पढ़ो_addr(path) + 0x08;
	w_q = rtw8822c_get_path_ग_लिखो_addr(path) + 0xb0 + w_off;
	r_q = rtw8822c_get_path_पढ़ो_addr(path) + 0x08 + r_off;

	अगर (!rtw8822c_dac_cal_restore_रुको(rtwdev, r_i, w_i + 0x8))
		वापस false;

	क्रम (i = 0; i < DACK_MSBK_BACKUP_NUM; i++) अणु
		rtw_ग_लिखो32_mask(rtwdev, w_i + 0x4, BIT(2), 0x0);
		value = dm_info->dack_msbk[path][0][i];
		rtw_ग_लिखो32_mask(rtwdev, w_i + 0x4, 0xff8, value);
		rtw_ग_लिखो32_mask(rtwdev, w_i, 0xf0000000, i);
		rtw_ग_लिखो32_mask(rtwdev, w_i + 0x4, BIT(2), 0x1);
	पूर्ण

	rtw_ग_लिखो32_mask(rtwdev, w_i + 0x4, BIT(2), 0x0);

	अगर (!rtw8822c_dac_cal_restore_रुको(rtwdev, r_q, w_q + 0x8))
		वापस false;

	क्रम (i = 0; i < DACK_MSBK_BACKUP_NUM; i++) अणु
		rtw_ग_लिखो32_mask(rtwdev, w_q + 0x4, BIT(2), 0x0);
		value = dm_info->dack_msbk[path][1][i];
		rtw_ग_लिखो32_mask(rtwdev, w_q + 0x4, 0xff8, value);
		rtw_ग_लिखो32_mask(rtwdev, w_q, 0xf0000000, i);
		rtw_ग_लिखो32_mask(rtwdev, w_q + 0x4, BIT(2), 0x1);
	पूर्ण
	rtw_ग_लिखो32_mask(rtwdev, w_q + 0x4, BIT(2), 0x0);

	rtw_ग_लिखो32_mask(rtwdev, w_i + 0x8, BIT(26) | BIT(25), 0x0);
	rtw_ग_लिखो32_mask(rtwdev, w_q + 0x8, BIT(26) | BIT(25), 0x0);
	rtw_ग_लिखो32_mask(rtwdev, w_i + 0x4, BIT(0), 0x0);
	rtw_ग_लिखो32_mask(rtwdev, w_q + 0x4, BIT(0), 0x0);

	वापस true;
पूर्ण

अटल bool __rtw8822c_dac_cal_restore(काष्ठा rtw_dev *rtwdev)
अणु
	अगर (!rtw8822c_dac_cal_restore_path(rtwdev, RF_PATH_A))
		वापस false;

	अगर (!rtw8822c_dac_cal_restore_path(rtwdev, RF_PATH_B))
		वापस false;

	वापस true;
पूर्ण

अटल bool rtw8822c_dac_cal_restore(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u32 temp[3];

	/* sample the first element क्रम both path's IQ vector */
	अगर (dm_info->dack_msbk[RF_PATH_A][0][0] == 0 &&
	    dm_info->dack_msbk[RF_PATH_A][1][0] == 0 &&
	    dm_info->dack_msbk[RF_PATH_B][0][0] == 0 &&
	    dm_info->dack_msbk[RF_PATH_B][1][0] == 0)
		वापस false;

	temp[0] = rtw_पढ़ो32(rtwdev, 0x1860);
	temp[1] = rtw_पढ़ो32(rtwdev, 0x4160);
	temp[2] = rtw_पढ़ो32(rtwdev, 0x9b4);

	rtw8822c_dac_cal_restore_prepare(rtwdev);
	अगर (!check_hw_पढ़ोy(rtwdev, 0x2808, 0x7fff80, 0xffff) ||
	    !check_hw_पढ़ोy(rtwdev, 0x2834, 0x7fff80, 0xffff) ||
	    !check_hw_पढ़ोy(rtwdev, 0x4508, 0x7fff80, 0xffff) ||
	    !check_hw_पढ़ोy(rtwdev, 0x4534, 0x7fff80, 0xffff))
		वापस false;

	अगर (!__rtw8822c_dac_cal_restore(rtwdev)) अणु
		rtw_err(rtwdev, "failed to restore dack vectors\n");
		वापस false;
	पूर्ण

	rtw_ग_लिखो32_mask(rtwdev, 0x1830, BIT(30), 0x1);
	rtw_ग_लिखो32_mask(rtwdev, 0x4130, BIT(30), 0x1);
	rtw_ग_लिखो32(rtwdev, 0x1860, temp[0]);
	rtw_ग_लिखो32(rtwdev, 0x4160, temp[1]);
	rtw_ग_लिखो32_mask(rtwdev, 0x18b0, BIT(27), 0x1);
	rtw_ग_लिखो32_mask(rtwdev, 0x18cc, BIT(27), 0x1);
	rtw_ग_लिखो32_mask(rtwdev, 0x41b0, BIT(27), 0x1);
	rtw_ग_लिखो32_mask(rtwdev, 0x41cc, BIT(27), 0x1);
	rtw_ग_लिखो32(rtwdev, 0x9b4, temp[2]);

	वापस true;
पूर्ण

अटल व्योम rtw8822c_rf_dac_cal(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_backup_info backup_rf[DACK_RF_8822C * DACK_PATH_8822C];
	काष्ठा rtw_backup_info backup[DACK_REG_8822C];
	u32 ic = 0, qc = 0, i;
	u32 i_a = 0x0, q_a = 0x0, i_b = 0x0, q_b = 0x0;
	u32 ic_a = 0x0, qc_a = 0x0, ic_b = 0x0, qc_b = 0x0;
	u32 adc_ic_a = 0x0, adc_qc_a = 0x0, adc_ic_b = 0x0, adc_qc_b = 0x0;

	अगर (rtw8822c_dac_cal_restore(rtwdev))
		वापस;

	/* not able to restore, करो it */

	rtw8822c_dac_backup_reg(rtwdev, backup, backup_rf);

	rtw8822c_dac_bb_setting(rtwdev);

	/* path-A */
	rtw8822c_dac_cal_adc(rtwdev, RF_PATH_A, &adc_ic_a, &adc_qc_a);
	क्रम (i = 0; i < 10; i++) अणु
		rtw8822c_dac_cal_step1(rtwdev, RF_PATH_A);
		rtw8822c_dac_cal_step2(rtwdev, RF_PATH_A, &ic, &qc);
		ic_a = ic;
		qc_a = qc;

		rtw8822c_dac_cal_step3(rtwdev, RF_PATH_A, adc_ic_a, adc_qc_a,
				       &ic, &qc, &i_a, &q_a);

		अगर (ic < 5 && qc < 5)
			अवरोध;
	पूर्ण
	rtw8822c_dac_cal_step4(rtwdev, RF_PATH_A);

	/* path-B */
	rtw8822c_dac_cal_adc(rtwdev, RF_PATH_B, &adc_ic_b, &adc_qc_b);
	क्रम (i = 0; i < 10; i++) अणु
		rtw8822c_dac_cal_step1(rtwdev, RF_PATH_B);
		rtw8822c_dac_cal_step2(rtwdev, RF_PATH_B, &ic, &qc);
		ic_b = ic;
		qc_b = qc;

		rtw8822c_dac_cal_step3(rtwdev, RF_PATH_B, adc_ic_b, adc_qc_b,
				       &ic, &qc, &i_b, &q_b);

		अगर (ic < 5 && qc < 5)
			अवरोध;
	पूर्ण
	rtw8822c_dac_cal_step4(rtwdev, RF_PATH_B);

	rtw_ग_लिखो32(rtwdev, 0x1b00, 0x00000008);
	rtw_ग_लिखो32_mask(rtwdev, 0x4130, BIT(30), 0x1);
	rtw_ग_लिखो8(rtwdev, 0x1bcc, 0x0);
	rtw_ग_लिखो32(rtwdev, 0x1b00, 0x0000000a);
	rtw_ग_लिखो8(rtwdev, 0x1bcc, 0x0);

	rtw8822c_dac_restore_reg(rtwdev, backup, backup_rf);

	/* backup results to restore, saving a lot of समय */
	rtw8822c_dac_cal_backup(rtwdev);

	rtw_dbg(rtwdev, RTW_DBG_RFK, "[DACK] path A: ic=0x%x, qc=0x%x\n", ic_a, qc_a);
	rtw_dbg(rtwdev, RTW_DBG_RFK, "[DACK] path B: ic=0x%x, qc=0x%x\n", ic_b, qc_b);
	rtw_dbg(rtwdev, RTW_DBG_RFK, "[DACK] path A: i=0x%x, q=0x%x\n", i_a, q_a);
	rtw_dbg(rtwdev, RTW_DBG_RFK, "[DACK] path B: i=0x%x, q=0x%x\n", i_b, q_b);
पूर्ण

अटल व्योम rtw8822c_rf_x2_check(काष्ठा rtw_dev *rtwdev)
अणु
	u8 x2k_busy;

	mdelay(1);
	x2k_busy = rtw_पढ़ो_rf(rtwdev, RF_PATH_A, 0xb8, BIT(15));
	अगर (x2k_busy == 1) अणु
		rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, 0xb8, RFREG_MASK, 0xC4440);
		rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, 0xba, RFREG_MASK, 0x6840D);
		rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, 0xb8, RFREG_MASK, 0x80440);
		mdelay(1);
	पूर्ण
पूर्ण

अटल व्योम rtw8822c_set_घातer_trim(काष्ठा rtw_dev *rtwdev, s8 bb_gain[2][8])
अणु
#घोषणा RF_SET_POWER_TRIM(_path, _seq, _idx)					\
		करो अणु								\
			rtw_ग_लिखो_rf(rtwdev, _path, 0x33, RFREG_MASK, _seq);	\
			rtw_ग_लिखो_rf(rtwdev, _path, 0x3f, RFREG_MASK,		\
				     bb_gain[_path][_idx]);			\
		पूर्ण जबतक (0)
	u8 path;

	क्रम (path = 0; path < rtwdev->hal.rf_path_num; path++) अणु
		rtw_ग_लिखो_rf(rtwdev, path, 0xee, BIT(19), 1);
		RF_SET_POWER_TRIM(path, 0x0, 0);
		RF_SET_POWER_TRIM(path, 0x1, 1);
		RF_SET_POWER_TRIM(path, 0x2, 2);
		RF_SET_POWER_TRIM(path, 0x3, 2);
		RF_SET_POWER_TRIM(path, 0x4, 3);
		RF_SET_POWER_TRIM(path, 0x5, 4);
		RF_SET_POWER_TRIM(path, 0x6, 5);
		RF_SET_POWER_TRIM(path, 0x7, 6);
		RF_SET_POWER_TRIM(path, 0x8, 7);
		RF_SET_POWER_TRIM(path, 0x9, 3);
		RF_SET_POWER_TRIM(path, 0xa, 4);
		RF_SET_POWER_TRIM(path, 0xb, 5);
		RF_SET_POWER_TRIM(path, 0xc, 6);
		RF_SET_POWER_TRIM(path, 0xd, 7);
		RF_SET_POWER_TRIM(path, 0xe, 7);
		rtw_ग_लिखो_rf(rtwdev, path, 0xee, BIT(19), 0);
	पूर्ण
#अघोषित RF_SET_POWER_TRIM
पूर्ण

अटल व्योम rtw8822c_घातer_trim(काष्ठा rtw_dev *rtwdev)
अणु
	u8 pg_pwr = 0xff, i, path, idx;
	s8 bb_gain[2][8] = अणुपूर्ण;
	u16 rf_efuse_2g[3] = अणुPPG_2GL_TXAB, PPG_2GM_TXAB, PPG_2GH_TXABपूर्ण;
	u16 rf_efuse_5g[2][5] = अणुअणुPPG_5GL1_TXA, PPG_5GL2_TXA, PPG_5GM1_TXA,
				  PPG_5GM2_TXA, PPG_5GH1_TXAपूर्ण,
				 अणुPPG_5GL1_TXB, PPG_5GL2_TXB, PPG_5GM1_TXB,
				  PPG_5GM2_TXB, PPG_5GH1_TXBपूर्ण पूर्ण;
	bool set = false;

	क्रम (i = 0; i < ARRAY_SIZE(rf_efuse_2g); i++) अणु
		rtw_पढ़ो8_physical_efuse(rtwdev, rf_efuse_2g[i], &pg_pwr);
		अगर (pg_pwr == EFUSE_READ_FAIL)
			जारी;
		set = true;
		bb_gain[RF_PATH_A][i] = FIELD_GET(PPG_2G_A_MASK, pg_pwr);
		bb_gain[RF_PATH_B][i] = FIELD_GET(PPG_2G_B_MASK, pg_pwr);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(rf_efuse_5g[0]); i++) अणु
		क्रम (path = 0; path < rtwdev->hal.rf_path_num; path++) अणु
			rtw_पढ़ो8_physical_efuse(rtwdev, rf_efuse_5g[path][i],
						 &pg_pwr);
			अगर (pg_pwr == EFUSE_READ_FAIL)
				जारी;
			set = true;
			idx = i + ARRAY_SIZE(rf_efuse_2g);
			bb_gain[path][idx] = FIELD_GET(PPG_5G_MASK, pg_pwr);
		पूर्ण
	पूर्ण
	अगर (set)
		rtw8822c_set_घातer_trim(rtwdev, bb_gain);

	rtw_ग_लिखो32_mask(rtwdev, REG_DIS_DPD, DIS_DPD_MASK, DIS_DPD_RATEALL);
पूर्ण

अटल व्योम rtw8822c_thermal_trim(काष्ठा rtw_dev *rtwdev)
अणु
	u16 rf_efuse[2] = अणुPPG_THERMAL_A, PPG_THERMAL_Bपूर्ण;
	u8 pg_therm = 0xff, thermal[2] = अणु0पूर्ण, path;

	क्रम (path = 0; path < rtwdev->hal.rf_path_num; path++) अणु
		rtw_पढ़ो8_physical_efuse(rtwdev, rf_efuse[path], &pg_therm);
		अगर (pg_therm == EFUSE_READ_FAIL)
			वापस;
		/* Efuse value of BIT(0) shall be move to BIT(3), and the value
		 * of BIT(1) to BIT(3) should be right shअगरted 1 bit.
		 */
		thermal[path] = FIELD_GET(GENMASK(3, 1), pg_therm);
		thermal[path] |= FIELD_PREP(BIT(3), pg_therm & BIT(0));
		rtw_ग_लिखो_rf(rtwdev, path, 0x43, RF_THEMAL_MASK, thermal[path]);
	पूर्ण
पूर्ण

अटल व्योम rtw8822c_pa_bias(काष्ठा rtw_dev *rtwdev)
अणु
	u16 rf_efuse_2g[2] = अणुPPG_PABIAS_2GA, PPG_PABIAS_2GBपूर्ण;
	u16 rf_efuse_5g[2] = अणुPPG_PABIAS_5GA, PPG_PABIAS_5GBपूर्ण;
	u8 pg_pa_bias = 0xff, path;

	क्रम (path = 0; path < rtwdev->hal.rf_path_num; path++) अणु
		rtw_पढ़ो8_physical_efuse(rtwdev, rf_efuse_2g[path],
					 &pg_pa_bias);
		अगर (pg_pa_bias == EFUSE_READ_FAIL)
			वापस;
		pg_pa_bias = FIELD_GET(PPG_PABIAS_MASK, pg_pa_bias);
		rtw_ग_लिखो_rf(rtwdev, path, RF_PA, RF_PABIAS_2G_MASK, pg_pa_bias);
	पूर्ण
	क्रम (path = 0; path < rtwdev->hal.rf_path_num; path++) अणु
		rtw_पढ़ो8_physical_efuse(rtwdev, rf_efuse_5g[path],
					 &pg_pa_bias);
		pg_pa_bias = FIELD_GET(PPG_PABIAS_MASK, pg_pa_bias);
		rtw_ग_लिखो_rf(rtwdev, path, RF_PA, RF_PABIAS_5G_MASK, pg_pa_bias);
	पूर्ण
पूर्ण

अटल व्योम rtw8822c_rfk_handshake(काष्ठा rtw_dev *rtwdev, bool is_beक्रमe_k)
अणु
	काष्ठा rtw_dm_info *dm = &rtwdev->dm_info;
	u8 u1b_पंचांगp;
	u8 u4b_पंचांगp;
	पूर्णांक ret;

	अगर (is_beक्रमe_k) अणु
		rtw_dbg(rtwdev, RTW_DBG_RFK,
			"[RFK] WiFi / BT RFK handshake start!!\n");

		अगर (!dm->is_bt_iqk_समयout) अणु
			ret = पढ़ो_poll_समयout(rtw_पढ़ो32_mask, u4b_पंचांगp,
						u4b_पंचांगp == 0, 20, 600000, false,
						rtwdev, REG_PMC_DBG_CTRL1,
						BITS_PMC_BT_IQK_STS);
			अगर (ret) अणु
				rtw_dbg(rtwdev, RTW_DBG_RFK,
					"[RFK] Wait BT IQK finish timeout!!\n");
				dm->is_bt_iqk_समयout = true;
			पूर्ण
		पूर्ण

		rtw_fw_inक्रमm_rfk_status(rtwdev, true);

		ret = पढ़ो_poll_समयout(rtw_पढ़ो8_mask, u1b_पंचांगp,
					u1b_पंचांगp == 1, 20, 100000, false,
					rtwdev, REG_ARFR4, BIT_WL_RFK);
		अगर (ret)
			rtw_dbg(rtwdev, RTW_DBG_RFK,
				"[RFK] Send WiFi RFK start H2C cmd FAIL!!\n");
	पूर्ण अन्यथा अणु
		rtw_fw_inक्रमm_rfk_status(rtwdev, false);
		ret = पढ़ो_poll_समयout(rtw_पढ़ो8_mask, u1b_पंचांगp,
					u1b_पंचांगp == 1, 20, 100000, false,
					rtwdev, REG_ARFR4,
					BIT_WL_RFK);
		अगर (ret)
			rtw_dbg(rtwdev, RTW_DBG_RFK,
				"[RFK] Send WiFi RFK finish H2C cmd FAIL!!\n");

		rtw_dbg(rtwdev, RTW_DBG_RFK,
			"[RFK] WiFi / BT RFK handshake finish!!\n");
	पूर्ण
पूर्ण

अटल व्योम rtw8822c_rfk_घातer_save(काष्ठा rtw_dev *rtwdev,
				    bool is_घातer_save)
अणु
	u8 path;

	क्रम (path = 0; path < rtwdev->hal.rf_path_num; path++) अणु
		rtw_ग_लिखो32_mask(rtwdev, REG_NCTL0, BIT_SEL_PATH, path);
		rtw_ग_लिखो32_mask(rtwdev, REG_DPD_CTL1_S0, BIT_PS_EN,
				 is_घातer_save ? 0 : 1);
	पूर्ण
पूर्ण

अटल व्योम rtw8822c_txgapk_backup_bb_reg(काष्ठा rtw_dev *rtwdev, स्थिर u32 reg[],
					  u32 reg_backup[], u32 reg_num)
अणु
	u32 i;

	क्रम (i = 0; i < reg_num; i++) अणु
		reg_backup[i] = rtw_पढ़ो32(rtwdev, reg[i]);

		rtw_dbg(rtwdev, RTW_DBG_RFK, "[TXGAPK] Backup BB 0x%x = 0x%x\n",
			reg[i], reg_backup[i]);
	पूर्ण
पूर्ण

अटल व्योम rtw8822c_txgapk_reload_bb_reg(काष्ठा rtw_dev *rtwdev,
					  स्थिर u32 reg[], u32 reg_backup[],
					  u32 reg_num)
अणु
	u32 i;

	क्रम (i = 0; i < reg_num; i++) अणु
		rtw_ग_लिखो32(rtwdev, reg[i], reg_backup[i]);
		rtw_dbg(rtwdev, RTW_DBG_RFK, "[TXGAPK] Reload BB 0x%x = 0x%x\n",
			reg[i], reg_backup[i]);
	पूर्ण
पूर्ण

अटल bool check_rf_status(काष्ठा rtw_dev *rtwdev, u8 status)
अणु
	u8 reg_rf0_a, reg_rf0_b;

	reg_rf0_a = (u8)rtw_पढ़ो_rf(rtwdev, RF_PATH_A,
				    RF_MODE_TRXAGC, BIT_RF_MODE);
	reg_rf0_b = (u8)rtw_पढ़ो_rf(rtwdev, RF_PATH_B,
				    RF_MODE_TRXAGC, BIT_RF_MODE);

	अगर (reg_rf0_a == status || reg_rf0_b == status)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम rtw8822c_txgapk_tx_छोड़ो(काष्ठा rtw_dev *rtwdev)
अणु
	bool status;
	पूर्णांक ret;

	rtw_ग_लिखो8(rtwdev, REG_TXPAUSE, BIT_AC_QUEUE);
	rtw_ग_लिखो32_mask(rtwdev, REG_TX_FIFO, BIT_STOP_TX, 0x2);

	ret = पढ़ो_poll_समयout_atomic(check_rf_status, status, status,
				       2, 5000, false, rtwdev, 2);
	अगर (ret)
		rtw_warn(rtwdev, "failed to pause TX\n");

	rtw_dbg(rtwdev, RTW_DBG_RFK, "[TXGAPK] Tx pause!!\n");
पूर्ण

अटल व्योम rtw8822c_txgapk_bb_dpk(काष्ठा rtw_dev *rtwdev, u8 path)
अणु
	rtw_dbg(rtwdev, RTW_DBG_RFK, "[TXGAPK] ======>%s\n", __func__);

	rtw_ग_लिखो32_mask(rtwdev, REG_ENFN, BIT_IQK_DPK_EN, 0x1);
	rtw_ग_लिखो32_mask(rtwdev, REG_CH_DELAY_EXTR2,
			 BIT_IQK_DPK_CLOCK_SRC, 0x1);
	rtw_ग_लिखो32_mask(rtwdev, REG_CH_DELAY_EXTR2,
			 BIT_IQK_DPK_RESET_SRC, 0x1);
	rtw_ग_लिखो32_mask(rtwdev, REG_CH_DELAY_EXTR2, BIT_EN_IOQ_IQK_DPK, 0x1);
	rtw_ग_लिखो32_mask(rtwdev, REG_CH_DELAY_EXTR2, BIT_TST_IQK2SET_SRC, 0x0);
	rtw_ग_लिखो32_mask(rtwdev, REG_CCA_OFF, BIT_CCA_ON_BY_PW, 0x1ff);

	अगर (path == RF_PATH_A) अणु
		rtw_ग_लिखो32_mask(rtwdev, REG_RFTXEN_GCK_A,
				 BIT_RFTXEN_GCK_FORCE_ON, 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_3WIRE, BIT_DIS_SHARERX_TXGAT, 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_DIS_SHARE_RX_A,
				 BIT_TX_SCALE_0DB, 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_3WIRE, BIT_3WIRE_EN, 0x0);
	पूर्ण अन्यथा अगर (path == RF_PATH_B) अणु
		rtw_ग_लिखो32_mask(rtwdev, REG_RFTXEN_GCK_B,
				 BIT_RFTXEN_GCK_FORCE_ON, 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_3WIRE2,
				 BIT_DIS_SHARERX_TXGAT, 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_DIS_SHARE_RX_B,
				 BIT_TX_SCALE_0DB, 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_3WIRE2, BIT_3WIRE_EN, 0x0);
	पूर्ण
	rtw_ग_लिखो32_mask(rtwdev, REG_CCKSB, BIT_BBMODE, 0x2);
पूर्ण

अटल व्योम rtw8822c_txgapk_afe_dpk(काष्ठा rtw_dev *rtwdev, u8 path)
अणु
	u32 reg;

	rtw_dbg(rtwdev, RTW_DBG_RFK, "[TXGAPK] ======>%s\n", __func__);

	अगर (path == RF_PATH_A) अणु
		reg = REG_ANAPAR_A;
	पूर्ण अन्यथा अगर (path == RF_PATH_B) अणु
		reg = REG_ANAPAR_B;
	पूर्ण अन्यथा अणु
		rtw_err(rtwdev, "[TXGAPK] unknown path %d!!\n", path);
		वापस;
	पूर्ण

	rtw_ग_लिखो32_mask(rtwdev, REG_IQK_CTRL, MASKDWORD, MASKDWORD);
	rtw_ग_लिखो32_mask(rtwdev, reg, MASKDWORD, 0x700f0001);
	rtw_ग_लिखो32_mask(rtwdev, reg, MASKDWORD, 0x700f0001);
	rtw_ग_लिखो32_mask(rtwdev, reg, MASKDWORD, 0x701f0001);
	rtw_ग_लिखो32_mask(rtwdev, reg, MASKDWORD, 0x702f0001);
	rtw_ग_लिखो32_mask(rtwdev, reg, MASKDWORD, 0x703f0001);
	rtw_ग_लिखो32_mask(rtwdev, reg, MASKDWORD, 0x704f0001);
	rtw_ग_लिखो32_mask(rtwdev, reg, MASKDWORD, 0x705f0001);
	rtw_ग_लिखो32_mask(rtwdev, reg, MASKDWORD, 0x706f0001);
	rtw_ग_लिखो32_mask(rtwdev, reg, MASKDWORD, 0x707f0001);
	rtw_ग_लिखो32_mask(rtwdev, reg, MASKDWORD, 0x708f0001);
	rtw_ग_लिखो32_mask(rtwdev, reg, MASKDWORD, 0x709f0001);
	rtw_ग_लिखो32_mask(rtwdev, reg, MASKDWORD, 0x70af0001);
	rtw_ग_लिखो32_mask(rtwdev, reg, MASKDWORD, 0x70bf0001);
	rtw_ग_लिखो32_mask(rtwdev, reg, MASKDWORD, 0x70cf0001);
	rtw_ग_लिखो32_mask(rtwdev, reg, MASKDWORD, 0x70df0001);
	rtw_ग_लिखो32_mask(rtwdev, reg, MASKDWORD, 0x70ef0001);
	rtw_ग_लिखो32_mask(rtwdev, reg, MASKDWORD, 0x70ff0001);
	rtw_ग_लिखो32_mask(rtwdev, reg, MASKDWORD, 0x70ff0001);
पूर्ण

अटल व्योम rtw8822c_txgapk_afe_dpk_restore(काष्ठा rtw_dev *rtwdev, u8 path)
अणु
	u32 reg;

	rtw_dbg(rtwdev, RTW_DBG_RFK, "[TXGAPK] ======>%s\n", __func__);

	अगर (path == RF_PATH_A) अणु
		reg = REG_ANAPAR_A;
	पूर्ण अन्यथा अगर (path == RF_PATH_B) अणु
		reg = REG_ANAPAR_B;
	पूर्ण अन्यथा अणु
		rtw_err(rtwdev, "[TXGAPK] unknown path %d!!\n", path);
		वापस;
	पूर्ण
	rtw_ग_लिखो32_mask(rtwdev, REG_IQK_CTRL, MASKDWORD, 0xffa1005e);
	rtw_ग_लिखो32_mask(rtwdev, reg, MASKDWORD, 0x700b8041);
	rtw_ग_लिखो32_mask(rtwdev, reg, MASKDWORD, 0x70144041);
	rtw_ग_लिखो32_mask(rtwdev, reg, MASKDWORD, 0x70244041);
	rtw_ग_लिखो32_mask(rtwdev, reg, MASKDWORD, 0x70344041);
	rtw_ग_लिखो32_mask(rtwdev, reg, MASKDWORD, 0x70444041);
	rtw_ग_लिखो32_mask(rtwdev, reg, MASKDWORD, 0x705b8041);
	rtw_ग_लिखो32_mask(rtwdev, reg, MASKDWORD, 0x70644041);
	rtw_ग_लिखो32_mask(rtwdev, reg, MASKDWORD, 0x707b8041);
	rtw_ग_लिखो32_mask(rtwdev, reg, MASKDWORD, 0x708b8041);
	rtw_ग_लिखो32_mask(rtwdev, reg, MASKDWORD, 0x709b8041);
	rtw_ग_लिखो32_mask(rtwdev, reg, MASKDWORD, 0x70ab8041);
	rtw_ग_लिखो32_mask(rtwdev, reg, MASKDWORD, 0x70bb8041);
	rtw_ग_लिखो32_mask(rtwdev, reg, MASKDWORD, 0x70cb8041);
	rtw_ग_लिखो32_mask(rtwdev, reg, MASKDWORD, 0x70db8041);
	rtw_ग_लिखो32_mask(rtwdev, reg, MASKDWORD, 0x70eb8041);
	rtw_ग_लिखो32_mask(rtwdev, reg, MASKDWORD, 0x70fb8041);
पूर्ण

अटल व्योम rtw8822c_txgapk_bb_dpk_restore(काष्ठा rtw_dev *rtwdev, u8 path)
अणु
	rtw_dbg(rtwdev, RTW_DBG_RFK, "[TXGAPK] ======>%s\n", __func__);

	rtw_ग_लिखो_rf(rtwdev, path, RF_DEBUG, BIT_DE_TX_GAIN, 0x0);
	rtw_ग_लिखो_rf(rtwdev, path, RF_DIS_BYPASS_TXBB, BIT_TIA_BYPASS, 0x0);
	rtw_ग_लिखो_rf(rtwdev, path, RF_DIS_BYPASS_TXBB, BIT_TXBB, 0x0);

	rtw_ग_लिखो32_mask(rtwdev, REG_NCTL0, BIT_SEL_PATH, 0x0);
	rtw_ग_लिखो32_mask(rtwdev, REG_IQK_CTL1, BIT_TX_CFIR, 0x0);
	rtw_ग_लिखो32_mask(rtwdev, REG_SINGLE_TONE_SW, BIT_IRQ_TEST_MODE, 0x0);
	rtw_ग_लिखो32_mask(rtwdev, REG_R_CONFIG, MASKBYTE0, 0x00);
	rtw_ग_लिखो32_mask(rtwdev, REG_NCTL0, BIT_SEL_PATH, 0x1);
	rtw_ग_लिखो32_mask(rtwdev, REG_IQK_CTL1, BIT_TX_CFIR, 0x0);
	rtw_ग_लिखो32_mask(rtwdev, REG_SINGLE_TONE_SW, BIT_IRQ_TEST_MODE, 0x0);
	rtw_ग_लिखो32_mask(rtwdev, REG_R_CONFIG, MASKBYTE0, 0x00);
	rtw_ग_लिखो32_mask(rtwdev, REG_NCTL0, BIT_SEL_PATH, 0x0);
	rtw_ग_लिखो32_mask(rtwdev, REG_CCA_OFF, BIT_CCA_ON_BY_PW, 0x0);

	अगर (path == RF_PATH_A) अणु
		rtw_ग_लिखो32_mask(rtwdev, REG_RFTXEN_GCK_A,
				 BIT_RFTXEN_GCK_FORCE_ON, 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_3WIRE, BIT_DIS_SHARERX_TXGAT, 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_DIS_SHARE_RX_A,
				 BIT_TX_SCALE_0DB, 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_3WIRE, BIT_3WIRE_EN, 0x3);
	पूर्ण अन्यथा अगर (path == RF_PATH_B) अणु
		rtw_ग_लिखो32_mask(rtwdev, REG_RFTXEN_GCK_B,
				 BIT_RFTXEN_GCK_FORCE_ON, 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_3WIRE2,
				 BIT_DIS_SHARERX_TXGAT, 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_DIS_SHARE_RX_B,
				 BIT_TX_SCALE_0DB, 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_3WIRE2, BIT_3WIRE_EN, 0x3);
	पूर्ण

	rtw_ग_लिखो32_mask(rtwdev, REG_CCKSB, BIT_BBMODE, 0x0);
	rtw_ग_लिखो32_mask(rtwdev, REG_IQK_CTL1, BIT_CFIR_EN, 0x5);
पूर्ण

अटल bool _rtw8822c_txgapk_gain_valid(काष्ठा rtw_dev *rtwdev, u32 gain)
अणु
	अगर ((FIELD_GET(BIT_GAIN_TX_PAD_H, gain) >= 0xc) &&
	    (FIELD_GET(BIT_GAIN_TX_PAD_L, gain) >= 0xe))
		वापस true;

	वापस false;
पूर्ण

अटल व्योम _rtw8822c_txgapk_ग_लिखो_gain_bb_table(काष्ठा rtw_dev *rtwdev,
						 u8 band, u8 path)
अणु
	काष्ठा rtw_gapk_info *txgapk = &rtwdev->dm_info.gapk;
	u32 v, पंचांगp_3f = 0;
	u8 gain, check_txgain;

	rtw_ग_लिखो32_mask(rtwdev, REG_NCTL0, BIT_SEL_PATH, path);

	चयन (band) अणु
	हाल RF_BAND_2G_OFDM:
		rtw_ग_लिखो32_mask(rtwdev, REG_TABLE_SEL, BIT_Q_GAIN_SEL, 0x0);
		अवरोध;
	हाल RF_BAND_5G_L:
		rtw_ग_लिखो32_mask(rtwdev, REG_TABLE_SEL, BIT_Q_GAIN_SEL, 0x2);
		अवरोध;
	हाल RF_BAND_5G_M:
		rtw_ग_लिखो32_mask(rtwdev, REG_TABLE_SEL, BIT_Q_GAIN_SEL, 0x3);
		अवरोध;
	हाल RF_BAND_5G_H:
		rtw_ग_लिखो32_mask(rtwdev, REG_TABLE_SEL, BIT_Q_GAIN_SEL, 0x4);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	rtw_ग_लिखो32_mask(rtwdev, REG_TX_GAIN_SET, MASKBYTE0, 0x88);

	check_txgain = 0;
	क्रम (gain = 0; gain < RF_GAIN_NUM; gain++) अणु
		v = txgapk->rf3f_bp[band][gain][path];
		अगर (_rtw8822c_txgapk_gain_valid(rtwdev, v)) अणु
			अगर (!check_txgain) अणु
				पंचांगp_3f = txgapk->rf3f_bp[band][gain][path];
				check_txgain = 1;
			पूर्ण
			rtw_dbg(rtwdev, RTW_DBG_RFK,
				"[TXGAPK] tx_gain=0x%03X >= 0xCEX\n",
				txgapk->rf3f_bp[band][gain][path]);
		पूर्ण अन्यथा अणु
			पंचांगp_3f = txgapk->rf3f_bp[band][gain][path];
		पूर्ण

		rtw_ग_लिखो32_mask(rtwdev, REG_TABLE_SEL, BIT_Q_GAIN, पंचांगp_3f);
		rtw_ग_लिखो32_mask(rtwdev, REG_TABLE_SEL, BIT_I_GAIN, gain);
		rtw_ग_लिखो32_mask(rtwdev, REG_TABLE_SEL, BIT_GAIN_RST, 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_TABLE_SEL, BIT_GAIN_RST, 0x0);

		rtw_dbg(rtwdev, RTW_DBG_RFK,
			"[TXGAPK] Band=%d 0x1b98[11:0]=0x%03X path=%d\n",
			band, पंचांगp_3f, path);
	पूर्ण
पूर्ण

अटल व्योम rtw8822c_txgapk_ग_लिखो_gain_bb_table(काष्ठा rtw_dev *rtwdev)
अणु
	u8 path, band;

	rtw_dbg(rtwdev, RTW_DBG_RFK, "[TXGAPK] ======>%s channel=%d\n",
		__func__, rtwdev->dm_info.gapk.channel);

	क्रम (band = 0; band < RF_BAND_MAX; band++) अणु
		क्रम (path = 0; path < rtwdev->hal.rf_path_num; path++) अणु
			_rtw8822c_txgapk_ग_लिखो_gain_bb_table(rtwdev,
							     band, path);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rtw8822c_txgapk_पढ़ो_offset(काष्ठा rtw_dev *rtwdev, u8 path)
अणु
	अटल स्थिर u32 cfg1_1b00[2] = अणु0x00000d18, 0x00000d2aपूर्ण;
	अटल स्थिर u32 cfg2_1b00[2] = अणु0x00000d19, 0x00000d2bपूर्ण;
	अटल स्थिर u32 set_pi[2] = अणुREG_RSV_CTRL, REG_WLRF1पूर्ण;
	अटल स्थिर u32 path_setting[2] = अणुREG_ORITXCODE, REG_ORITXCODE2पूर्ण;
	काष्ठा rtw_gapk_info *txgapk = &rtwdev->dm_info.gapk;
	u8 channel = txgapk->channel;
	u32 val;
	पूर्णांक i;

	अगर (path >= ARRAY_SIZE(cfg1_1b00) ||
	    path >= ARRAY_SIZE(cfg2_1b00) ||
	    path >= ARRAY_SIZE(set_pi) ||
	    path >= ARRAY_SIZE(path_setting)) अणु
		rtw_warn(rtwdev, "[TXGAPK] wrong path %d\n", path);
		वापस;
	पूर्ण

	rtw_ग_लिखो32_mask(rtwdev, REG_ANTMAP0, BIT_ANT_PATH, path + 1);
	rtw_ग_लिखो32_mask(rtwdev, REG_TXLGMAP, MASKDWORD, 0xe4e40000);
	rtw_ग_लिखो32_mask(rtwdev, REG_TXANTSEG, BIT_ANTSEG, 0x3);
	rtw_ग_लिखो32_mask(rtwdev, path_setting[path], MASK20BITS, 0x33312);
	rtw_ग_लिखो32_mask(rtwdev, path_setting[path], BIT_PATH_EN, 0x1);
	rtw_ग_लिखो32_mask(rtwdev, set_pi[path], BITS_RFC_सूचीECT, 0x0);
	rtw_ग_लिखो_rf(rtwdev, path, RF_LUTDBG, BIT_TXA_TANK, 0x1);
	rtw_ग_लिखो_rf(rtwdev, path, RF_IDAC, BIT_TX_MODE, 0x820);
	rtw_ग_लिखो32_mask(rtwdev, REG_NCTL0, BIT_SEL_PATH, path);
	rtw_ग_लिखो32_mask(rtwdev, REG_IQKSTAT, MASKBYTE0, 0x0);

	rtw_ग_लिखो32_mask(rtwdev, REG_TX_TONE_IDX, MASKBYTE0, 0x018);
	fsleep(1000);
	अगर (channel >= 1 && channel <= 14)
		rtw_ग_लिखो32_mask(rtwdev, REG_R_CONFIG, MASKBYTE0, BIT_2G_SWING);
	अन्यथा
		rtw_ग_लिखो32_mask(rtwdev, REG_R_CONFIG, MASKBYTE0, BIT_5G_SWING);
	fsleep(1000);

	rtw_ग_लिखो32_mask(rtwdev, REG_NCTL0, MASKDWORD, cfg1_1b00[path]);
	rtw_ग_लिखो32_mask(rtwdev, REG_NCTL0, MASKDWORD, cfg2_1b00[path]);

	पढ़ो_poll_समयout(rtw_पढ़ो32_mask, val,
			  val == 0x55, 1000, 100000, false,
			  rtwdev, REG_RPT_CIP, BIT_RPT_CIP_STATUS);

	rtw_ग_लिखो32_mask(rtwdev, set_pi[path], BITS_RFC_सूचीECT, 0x2);
	rtw_ग_लिखो32_mask(rtwdev, REG_NCTL0, BIT_SEL_PATH, path);
	rtw_ग_लिखो32_mask(rtwdev, REG_RXSRAM_CTL, BIT_RPT_EN, 0x1);
	rtw_ग_लिखो32_mask(rtwdev, REG_RXSRAM_CTL, BIT_RPT_SEL, 0x12);
	rtw_ग_लिखो32_mask(rtwdev, REG_TX_GAIN_SET, BIT_GAPK_RPT_IDX, 0x3);
	val = rtw_पढ़ो32(rtwdev, REG_STAT_RPT);

	txgapk->offset[0][path] = (s8)FIELD_GET(BIT_GAPK_RPT0, val);
	txgapk->offset[1][path] = (s8)FIELD_GET(BIT_GAPK_RPT1, val);
	txgapk->offset[2][path] = (s8)FIELD_GET(BIT_GAPK_RPT2, val);
	txgapk->offset[3][path] = (s8)FIELD_GET(BIT_GAPK_RPT3, val);
	txgapk->offset[4][path] = (s8)FIELD_GET(BIT_GAPK_RPT4, val);
	txgapk->offset[5][path] = (s8)FIELD_GET(BIT_GAPK_RPT5, val);
	txgapk->offset[6][path] = (s8)FIELD_GET(BIT_GAPK_RPT6, val);
	txgapk->offset[7][path] = (s8)FIELD_GET(BIT_GAPK_RPT7, val);

	rtw_ग_लिखो32_mask(rtwdev, REG_TX_GAIN_SET, BIT_GAPK_RPT_IDX, 0x4);
	val = rtw_पढ़ो32(rtwdev, REG_STAT_RPT);

	txgapk->offset[8][path] = (s8)FIELD_GET(BIT_GAPK_RPT0, val);
	txgapk->offset[9][path] = (s8)FIELD_GET(BIT_GAPK_RPT1, val);

	क्रम (i = 0; i < RF_HW_OFFSET_NUM; i++)
		अगर (txgapk->offset[i][path] & BIT(3))
			txgapk->offset[i][path] = txgapk->offset[i][path] |
						  0xf0;
	क्रम (i = 0; i < RF_HW_OFFSET_NUM; i++)
		rtw_dbg(rtwdev, RTW_DBG_RFK,
			"[TXGAPK] offset %d %d path=%d\n",
			txgapk->offset[i][path], i, path);
पूर्ण

अटल व्योम rtw8822c_txgapk_calculate_offset(काष्ठा rtw_dev *rtwdev, u8 path)
अणु
	अटल स्थिर u32 bb_reg[] = अणुREG_ANTMAP0, REG_TXLGMAP, REG_TXANTSEG,
				     REG_ORITXCODE, REG_ORITXCODE2पूर्ण;
	काष्ठा rtw_gapk_info *txgapk = &rtwdev->dm_info.gapk;
	u8 channel = txgapk->channel;
	u32 reg_backup[ARRAY_SIZE(bb_reg)] = अणु0पूर्ण;

	rtw_dbg(rtwdev, RTW_DBG_RFK, "[TXGAPK] ======>%s channel=%d\n",
		__func__, channel);

	rtw8822c_txgapk_backup_bb_reg(rtwdev, bb_reg,
				      reg_backup, ARRAY_SIZE(bb_reg));

	अगर (channel >= 1 && channel <= 14) अणु
		rtw_ग_लिखो32_mask(rtwdev,
				 REG_SINGLE_TONE_SW, BIT_IRQ_TEST_MODE, 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_NCTL0, BIT_SEL_PATH, path);
		rtw_ग_लिखो32_mask(rtwdev, REG_R_CONFIG, BIT_IQ_SWITCH, 0x3f);
		rtw_ग_लिखो32_mask(rtwdev, REG_IQK_CTL1, BIT_TX_CFIR, 0x0);
		rtw_ग_लिखो_rf(rtwdev, path, RF_DEBUG, BIT_DE_TX_GAIN, 0x1);
		rtw_ग_लिखो_rf(rtwdev, path, RF_MODE_TRXAGC, RFREG_MASK, 0x5000f);
		rtw_ग_लिखो_rf(rtwdev, path, RF_TX_GAIN_OFFSET, BIT_RF_GAIN, 0x0);
		rtw_ग_लिखो_rf(rtwdev, path, RF_RXG_GAIN, BIT_RXG_GAIN, 0x1);
		rtw_ग_लिखो_rf(rtwdev, path, RF_MODE_TRXAGC, BIT_RXAGC, 0x0f);
		rtw_ग_लिखो_rf(rtwdev, path, RF_DEBUG, BIT_DE_TRXBW, 0x1);
		rtw_ग_लिखो_rf(rtwdev, path, RF_BW_TRXBB, BIT_BW_TXBB, 0x1);
		rtw_ग_लिखो_rf(rtwdev, path, RF_BW_TRXBB, BIT_BW_RXBB, 0x0);
		rtw_ग_लिखो_rf(rtwdev, path, RF_EXT_TIA_BW, BIT_PW_EXT_TIA, 0x1);

		rtw_ग_लिखो32_mask(rtwdev, REG_IQKSTAT, MASKBYTE0, 0x00);
		rtw_ग_लिखो32_mask(rtwdev, REG_TABLE_SEL, BIT_Q_GAIN_SEL, 0x0);

		rtw8822c_txgapk_पढ़ो_offset(rtwdev, path);
		rtw_dbg(rtwdev, RTW_DBG_RFK, "=============================\n");

	पूर्ण अन्यथा अणु
		rtw_ग_लिखो32_mask(rtwdev,
				 REG_SINGLE_TONE_SW, BIT_IRQ_TEST_MODE, 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_NCTL0, BIT_SEL_PATH, path);
		rtw_ग_लिखो32_mask(rtwdev, REG_R_CONFIG, BIT_IQ_SWITCH, 0x3f);
		rtw_ग_लिखो32_mask(rtwdev, REG_IQK_CTL1, BIT_TX_CFIR, 0x0);
		rtw_ग_लिखो_rf(rtwdev, path, RF_DEBUG, BIT_DE_TX_GAIN, 0x1);
		rtw_ग_लिखो_rf(rtwdev, path, RF_MODE_TRXAGC, RFREG_MASK, 0x50011);
		rtw_ग_लिखो_rf(rtwdev, path, RF_TXA_LB_SW, BIT_TXA_LB_ATT, 0x3);
		rtw_ग_लिखो_rf(rtwdev, path, RF_TXA_LB_SW, BIT_LB_ATT, 0x3);
		rtw_ग_लिखो_rf(rtwdev, path, RF_TXA_LB_SW, BIT_LB_SW, 0x1);
		rtw_ग_लिखो_rf(rtwdev, path,
			     RF_RXA_MIX_GAIN, BIT_RXA_MIX_GAIN, 0x2);
		rtw_ग_लिखो_rf(rtwdev, path, RF_MODE_TRXAGC, BIT_RXAGC, 0x12);
		rtw_ग_लिखो_rf(rtwdev, path, RF_DEBUG, BIT_DE_TRXBW, 0x1);
		rtw_ग_लिखो_rf(rtwdev, path, RF_BW_TRXBB, BIT_BW_RXBB, 0x0);
		rtw_ग_लिखो_rf(rtwdev, path, RF_EXT_TIA_BW, BIT_PW_EXT_TIA, 0x1);
		rtw_ग_लिखो_rf(rtwdev, path, RF_MODE_TRXAGC, BIT_RF_MODE, 0x5);

		rtw_ग_लिखो32_mask(rtwdev, REG_IQKSTAT, MASKBYTE0, 0x0);

		अगर (channel >= 36 && channel <= 64)
			rtw_ग_लिखो32_mask(rtwdev,
					 REG_TABLE_SEL, BIT_Q_GAIN_SEL, 0x2);
		अन्यथा अगर (channel >= 100 && channel <= 144)
			rtw_ग_लिखो32_mask(rtwdev,
					 REG_TABLE_SEL, BIT_Q_GAIN_SEL, 0x3);
		अन्यथा अगर (channel >= 149 && channel <= 177)
			rtw_ग_लिखो32_mask(rtwdev,
					 REG_TABLE_SEL, BIT_Q_GAIN_SEL, 0x4);

		rtw8822c_txgapk_पढ़ो_offset(rtwdev, path);
		rtw_dbg(rtwdev, RTW_DBG_RFK, "=============================\n");
	पूर्ण
	rtw8822c_txgapk_reload_bb_reg(rtwdev, bb_reg,
				      reg_backup, ARRAY_SIZE(bb_reg));
पूर्ण

अटल व्योम rtw8822c_txgapk_rf_restore(काष्ठा rtw_dev *rtwdev, u8 path)
अणु
	rtw_dbg(rtwdev, RTW_DBG_RFK, "[TXGAPK] ======>%s\n", __func__);

	अगर (path >= rtwdev->hal.rf_path_num)
		वापस;

	rtw_ग_लिखो_rf(rtwdev, path, RF_MODE_TRXAGC, BIT_RF_MODE, 0x3);
	rtw_ग_लिखो_rf(rtwdev, path, RF_DEBUG, BIT_DE_TRXBW, 0x0);
	rtw_ग_लिखो_rf(rtwdev, path, RF_EXT_TIA_BW, BIT_PW_EXT_TIA, 0x0);
पूर्ण

अटल u32 rtw8822c_txgapk_cal_gain(काष्ठा rtw_dev *rtwdev, u32 gain, s8 offset)
अणु
	u32 gain_x2, new_gain;

	rtw_dbg(rtwdev, RTW_DBG_RFK, "[TXGAPK] ======>%s\n", __func__);

	अगर (_rtw8822c_txgapk_gain_valid(rtwdev, gain)) अणु
		new_gain = gain;
		rtw_dbg(rtwdev, RTW_DBG_RFK,
			"[TXGAPK] gain=0x%03X(>=0xCEX) offset=%d new_gain=0x%03X\n",
			gain, offset, new_gain);
		वापस new_gain;
	पूर्ण

	gain_x2 = (gain << 1) + offset;
	new_gain = (gain_x2 >> 1) | (gain_x2 & BIT(0) ? BIT_GAIN_EXT : 0);

	rtw_dbg(rtwdev, RTW_DBG_RFK,
		"[TXGAPK] gain=0x%X offset=%d new_gain=0x%X\n",
		gain, offset, new_gain);

	वापस new_gain;
पूर्ण

अटल व्योम rtw8822c_txgapk_ग_लिखो_tx_gain(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_gapk_info *txgapk = &rtwdev->dm_info.gapk;
	u32 i, j, पंचांगp = 0x20, पंचांगp_3f, v;
	s8 offset_पंचांगp[RF_GAIN_NUM] = अणु0पूर्ण;
	u8 path, band = RF_BAND_2G_OFDM, channel = txgapk->channel;

	rtw_dbg(rtwdev, RTW_DBG_RFK, "[TXGAPK] ======>%s\n", __func__);

	अगर (channel >= 1 && channel <= 14) अणु
		पंचांगp = 0x20;
		band = RF_BAND_2G_OFDM;
	पूर्ण अन्यथा अगर (channel >= 36 && channel <= 64) अणु
		पंचांगp = 0x200;
		band = RF_BAND_5G_L;
	पूर्ण अन्यथा अगर (channel >= 100 && channel <= 144) अणु
		पंचांगp = 0x280;
		band = RF_BAND_5G_M;
	पूर्ण अन्यथा अगर (channel >= 149 && channel <= 177) अणु
		पंचांगp = 0x300;
		band = RF_BAND_5G_H;
	पूर्ण अन्यथा अणु
		rtw_err(rtwdev, "[TXGAPK] unknown channel %d!!\n", channel);
		वापस;
	पूर्ण

	क्रम (path = 0; path < rtwdev->hal.rf_path_num; path++) अणु
		क्रम (i = 0; i < RF_GAIN_NUM; i++) अणु
			offset_पंचांगp[i] = 0;
			क्रम (j = i; j < RF_GAIN_NUM; j++) अणु
				v = txgapk->rf3f_bp[band][j][path];
				अगर (_rtw8822c_txgapk_gain_valid(rtwdev, v))
					जारी;

				offset_पंचांगp[i] += txgapk->offset[j][path];
				txgapk->fianl_offset[i][path] = offset_पंचांगp[i];
			पूर्ण

			v = txgapk->rf3f_bp[band][i][path];
			अगर (_rtw8822c_txgapk_gain_valid(rtwdev, v)) अणु
				rtw_dbg(rtwdev, RTW_DBG_RFK,
					"[TXGAPK] tx_gain=0x%03X >= 0xCEX\n",
					txgapk->rf3f_bp[band][i][path]);
			पूर्ण अन्यथा अणु
				txgapk->rf3f_fs[path][i] = offset_पंचांगp[i];
				rtw_dbg(rtwdev, RTW_DBG_RFK,
					"[TXGAPK] offset %d %d\n",
					offset_पंचांगp[i], i);
			पूर्ण
		पूर्ण

		rtw_ग_लिखो_rf(rtwdev, path, RF_LUTWE2, RFREG_MASK, 0x10000);
		क्रम (i = 0; i < RF_GAIN_NUM; i++) अणु
			rtw_ग_लिखो_rf(rtwdev, path,
				     RF_LUTWA, RFREG_MASK, पंचांगp + i);

			पंचांगp_3f = rtw8822c_txgapk_cal_gain(rtwdev,
							  txgapk->rf3f_bp[band][i][path],
							  offset_पंचांगp[i]);
			rtw_ग_लिखो_rf(rtwdev, path, RF_LUTWD0,
				     BIT_GAIN_EXT | BIT_DATA_L, पंचांगp_3f);

			rtw_dbg(rtwdev, RTW_DBG_RFK,
				"[TXGAPK] 0x33=0x%05X 0x3f=0x%04X\n",
				पंचांगp + i, पंचांगp_3f);
		पूर्ण
		rtw_ग_लिखो_rf(rtwdev, path, RF_LUTWE2, RFREG_MASK, 0x0);
	पूर्ण
पूर्ण

अटल व्योम rtw8822c_txgapk_save_all_tx_gain_table(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_gapk_info *txgapk = &rtwdev->dm_info.gapk;
	अटल स्थिर u32 three_wire[2] = अणुREG_3WIRE, REG_3WIRE2पूर्ण;
	अटल स्थिर u8 ch_num[RF_BAND_MAX] = अणु1, 1, 36, 100, 149पूर्ण;
	अटल स्थिर u8 band_num[RF_BAND_MAX] = अणु0x0, 0x0, 0x1, 0x3, 0x5पूर्ण;
	अटल स्थिर u8 cck[RF_BAND_MAX] = अणु0x1, 0x0, 0x0, 0x0, 0x0पूर्ण;
	u8 path, band, gain, rf0_idx;
	u32 rf18, v;

	अगर (rtwdev->dm_info.dm_flags & BIT(RTW_DM_CAP_TXGAPK))
		वापस;

	rtw_dbg(rtwdev, RTW_DBG_RFK, "[TXGAPK] ======>%s\n", __func__);

	अगर (txgapk->पढ़ो_txgain == 1) अणु
		rtw_dbg(rtwdev, RTW_DBG_RFK,
			"[TXGAPK] Already Read txgapk->read_txgain return!!!\n");
		rtw8822c_txgapk_ग_लिखो_gain_bb_table(rtwdev);
		वापस;
	पूर्ण

	क्रम (band = 0; band < RF_BAND_MAX; band++) अणु
		क्रम (path = 0; path < rtwdev->hal.rf_path_num; path++) अणु
			rf18 = rtw_पढ़ो_rf(rtwdev, path, RF_CFGCH, RFREG_MASK);

			rtw_ग_लिखो32_mask(rtwdev,
					 three_wire[path], BIT_3WIRE_EN, 0x0);
			rtw_ग_लिखो_rf(rtwdev, path,
				     RF_CFGCH, MASKBYTE0, ch_num[band]);
			rtw_ग_लिखो_rf(rtwdev, path,
				     RF_CFGCH, BIT_BAND, band_num[band]);
			rtw_ग_लिखो_rf(rtwdev, path,
				     RF_BW_TRXBB, BIT_DBG_CCK_CCA, cck[band]);
			rtw_ग_लिखो_rf(rtwdev, path,
				     RF_BW_TRXBB, BIT_TX_CCK_IND, cck[band]);
			gain = 0;
			क्रम (rf0_idx = 1; rf0_idx < 32; rf0_idx += 3) अणु
				rtw_ग_लिखो_rf(rtwdev, path, RF_MODE_TRXAGC,
					     MASKBYTE0, rf0_idx);
				v = rtw_पढ़ो_rf(rtwdev, path,
						RF_TX_RESULT, RFREG_MASK);
				txgapk->rf3f_bp[band][gain][path] = v & BIT_DATA_L;

				rtw_dbg(rtwdev, RTW_DBG_RFK,
					"[TXGAPK] 0x5f=0x%03X band=%d path=%d\n",
					txgapk->rf3f_bp[band][gain][path],
					band, path);
				gain++;
			पूर्ण
			rtw_ग_लिखो_rf(rtwdev, path, RF_CFGCH, RFREG_MASK, rf18);
			rtw_ग_लिखो32_mask(rtwdev,
					 three_wire[path], BIT_3WIRE_EN, 0x3);
		पूर्ण
	पूर्ण
	rtw8822c_txgapk_ग_लिखो_gain_bb_table(rtwdev);
	txgapk->पढ़ो_txgain = 1;
पूर्ण

अटल व्योम rtw8822c_txgapk(काष्ठा rtw_dev *rtwdev)
अणु
	अटल स्थिर u32 bb_reg[2] = अणुREG_TX_PTCL_CTRL, REG_TX_FIFOपूर्ण;
	काष्ठा rtw_gapk_info *txgapk = &rtwdev->dm_info.gapk;
	u32 bb_reg_backup[2];
	u8 path;

	rtw_dbg(rtwdev, RTW_DBG_RFK, "[TXGAPK] ======>%s\n", __func__);

	rtw8822c_txgapk_save_all_tx_gain_table(rtwdev);

	अगर (txgapk->पढ़ो_txgain == 0) अणु
		rtw_dbg(rtwdev, RTW_DBG_RFK,
			"[TXGAPK] txgapk->read_txgain == 0 return!!!\n");
		वापस;
	पूर्ण

	अगर (rtwdev->efuse.घातer_track_type >= 4 &&
	    rtwdev->efuse.घातer_track_type <= 7) अणु
		rtw_dbg(rtwdev, RTW_DBG_RFK,
			"[TXGAPK] Normal Mode in TSSI mode. return!!!\n");
		वापस;
	पूर्ण

	rtw8822c_txgapk_backup_bb_reg(rtwdev, bb_reg,
				      bb_reg_backup, ARRAY_SIZE(bb_reg));
	rtw8822c_txgapk_tx_छोड़ो(rtwdev);
	क्रम (path = 0; path < rtwdev->hal.rf_path_num; path++) अणु
		txgapk->channel = rtw_पढ़ो_rf(rtwdev, path,
					      RF_CFGCH, RFREG_MASK) & MASKBYTE0;
		rtw8822c_txgapk_bb_dpk(rtwdev, path);
		rtw8822c_txgapk_afe_dpk(rtwdev, path);
		rtw8822c_txgapk_calculate_offset(rtwdev, path);
		rtw8822c_txgapk_rf_restore(rtwdev, path);
		rtw8822c_txgapk_afe_dpk_restore(rtwdev, path);
		rtw8822c_txgapk_bb_dpk_restore(rtwdev, path);
	पूर्ण
	rtw8822c_txgapk_ग_लिखो_tx_gain(rtwdev);
	rtw8822c_txgapk_reload_bb_reg(rtwdev, bb_reg,
				      bb_reg_backup, ARRAY_SIZE(bb_reg));
पूर्ण

अटल व्योम rtw8822c_करो_gapk(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dm_info *dm = &rtwdev->dm_info;

	अगर (dm->dm_flags & BIT(RTW_DM_CAP_TXGAPK)) अणु
		rtw_dbg(rtwdev, RTW_DBG_RFK, "[TXGAPK] feature disable!!!\n");
		वापस;
	पूर्ण
	rtw8822c_rfk_handshake(rtwdev, true);
	rtw8822c_txgapk(rtwdev);
	rtw8822c_rfk_handshake(rtwdev, false);
पूर्ण

अटल व्योम rtw8822c_rf_init(काष्ठा rtw_dev *rtwdev)
अणु
	rtw8822c_rf_dac_cal(rtwdev);
	rtw8822c_rf_x2_check(rtwdev);
	rtw8822c_thermal_trim(rtwdev);
	rtw8822c_घातer_trim(rtwdev);
	rtw8822c_pa_bias(rtwdev);
पूर्ण

अटल व्योम rtw8822c_pwrtrack_init(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u8 path;

	क्रम (path = RF_PATH_A; path < RTW_RF_PATH_MAX; path++) अणु
		dm_info->delta_घातer_index[path] = 0;
		ewma_thermal_init(&dm_info->avg_thermal[path]);
		dm_info->thermal_avg[path] = 0xff;
	पूर्ण

	dm_info->pwr_trk_triggered = false;
	dm_info->thermal_meter_k = rtwdev->efuse.thermal_meter_k;
	dm_info->thermal_meter_lck = rtwdev->efuse.thermal_meter_k;
पूर्ण

अटल व्योम rtw8822c_phy_set_param(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	u8 crystal_cap;
	u8 cck_gi_u_bnd_msb = 0;
	u8 cck_gi_u_bnd_lsb = 0;
	u8 cck_gi_l_bnd_msb = 0;
	u8 cck_gi_l_bnd_lsb = 0;
	bool is_tx2_path;

	/* घातer on BB/RF करोमुख्य */
	rtw_ग_लिखो8_set(rtwdev, REG_SYS_FUNC_EN,
		       BIT_FEN_BB_GLB_RST | BIT_FEN_BB_RSTB);
	rtw_ग_लिखो8_set(rtwdev, REG_RF_CTRL,
		       BIT_RF_EN | BIT_RF_RSTB | BIT_RF_SDM_RSTB);
	rtw_ग_लिखो32_set(rtwdev, REG_WLRF1, BIT_WLRF1_BBRF_EN);

	/* disable low rate DPD */
	rtw_ग_लिखो32_mask(rtwdev, REG_DIS_DPD, DIS_DPD_MASK, DIS_DPD_RATEALL);

	/* pre init beक्रमe header files config */
	rtw8822c_header_file_init(rtwdev, true);

	rtw_phy_load_tables(rtwdev);

	crystal_cap = rtwdev->efuse.crystal_cap & 0x7f;
	rtw_ग_लिखो32_mask(rtwdev, REG_ANAPAR_XTAL_0, 0xfffc00,
			 crystal_cap | (crystal_cap << 7));

	/* post init after header files config */
	rtw8822c_header_file_init(rtwdev, false);

	is_tx2_path = false;
	rtw8822c_config_trx_mode(rtwdev, hal->antenna_tx, hal->antenna_rx,
				 is_tx2_path);
	rtw_phy_init(rtwdev);

	cck_gi_u_bnd_msb = (u8)rtw_पढ़ो32_mask(rtwdev, 0x1a98, 0xc000);
	cck_gi_u_bnd_lsb = (u8)rtw_पढ़ो32_mask(rtwdev, 0x1aa8, 0xf0000);
	cck_gi_l_bnd_msb = (u8)rtw_पढ़ो32_mask(rtwdev, 0x1a98, 0xc0);
	cck_gi_l_bnd_lsb = (u8)rtw_पढ़ो32_mask(rtwdev, 0x1a70, 0x0f000000);

	dm_info->cck_gi_u_bnd = ((cck_gi_u_bnd_msb << 4) | (cck_gi_u_bnd_lsb));
	dm_info->cck_gi_l_bnd = ((cck_gi_l_bnd_msb << 4) | (cck_gi_l_bnd_lsb));

	rtw8822c_rf_init(rtwdev);
	rtw8822c_pwrtrack_init(rtwdev);

	rtw_bf_phy_init(rtwdev);
पूर्ण

#घोषणा WLAN_TXQ_RPT_EN		0x1F
#घोषणा WLAN_SLOT_TIME		0x09
#घोषणा WLAN_PIFS_TIME		0x1C
#घोषणा WLAN_SIFS_CCK_CONT_TX	0x0A
#घोषणा WLAN_SIFS_OFDM_CONT_TX	0x0E
#घोषणा WLAN_SIFS_CCK_TRX	0x0A
#घोषणा WLAN_SIFS_OFDM_TRX	0x10
#घोषणा WLAN_NAV_MAX		0xC8
#घोषणा WLAN_RDG_NAV		0x05
#घोषणा WLAN_TXOP_NAV		0x1B
#घोषणा WLAN_CCK_RX_TSF		0x30
#घोषणा WLAN_OFDM_RX_TSF	0x30
#घोषणा WLAN_TBTT_PROHIBIT	0x04 /* unit : 32us */
#घोषणा WLAN_TBTT_HOLD_TIME	0x064 /* unit : 32us */
#घोषणा WLAN_DRV_EARLY_INT	0x04
#घोषणा WLAN_BCN_CTRL_CLT0	0x10
#घोषणा WLAN_BCN_DMA_TIME	0x02
#घोषणा WLAN_BCN_MAX_ERR	0xFF
#घोषणा WLAN_SIFS_CCK_DUR_TUNE	0x0A
#घोषणा WLAN_SIFS_OFDM_DUR_TUNE	0x10
#घोषणा WLAN_SIFS_CCK_CTX	0x0A
#घोषणा WLAN_SIFS_CCK_IRX	0x0A
#घोषणा WLAN_SIFS_OFDM_CTX	0x0E
#घोषणा WLAN_SIFS_OFDM_IRX	0x0E
#घोषणा WLAN_EIFS_DUR_TUNE	0x40
#घोषणा WLAN_EDCA_VO_PARAM	0x002FA226
#घोषणा WLAN_EDCA_VI_PARAM	0x005EA328
#घोषणा WLAN_EDCA_BE_PARAM	0x005EA42B
#घोषणा WLAN_EDCA_BK_PARAM	0x0000A44F

#घोषणा WLAN_RX_FILTER0		0xFFFFFFFF
#घोषणा WLAN_RX_FILTER2		0xFFFF
#घोषणा WLAN_RCR_CFG		0xE400220E
#घोषणा WLAN_RXPKT_MAX_SZ	12288
#घोषणा WLAN_RXPKT_MAX_SZ_512	(WLAN_RXPKT_MAX_SZ >> 9)

#घोषणा WLAN_AMPDU_MAX_TIME		0x70
#घोषणा WLAN_RTS_LEN_TH			0xFF
#घोषणा WLAN_RTS_TX_TIME_TH		0x08
#घोषणा WLAN_MAX_AGG_PKT_LIMIT		0x3f
#घोषणा WLAN_RTS_MAX_AGG_PKT_LIMIT	0x3f
#घोषणा WLAN_PRE_TXCNT_TIME_TH		0x1E0
#घोषणा FAST_EDCA_VO_TH		0x06
#घोषणा FAST_EDCA_VI_TH		0x06
#घोषणा FAST_EDCA_BE_TH		0x06
#घोषणा FAST_EDCA_BK_TH		0x06
#घोषणा WLAN_BAR_RETRY_LIMIT		0x01
#घोषणा WLAN_BAR_ACK_TYPE		0x05
#घोषणा WLAN_RA_TRY_RATE_AGG_LIMIT	0x08
#घोषणा WLAN_RESP_TXRATE		0x84
#घोषणा WLAN_ACK_TO			0x21
#घोषणा WLAN_ACK_TO_CCK			0x6A
#घोषणा WLAN_DATA_RATE_FB_CNT_1_4	0x01000000
#घोषणा WLAN_DATA_RATE_FB_CNT_5_8	0x08070504
#घोषणा WLAN_RTS_RATE_FB_CNT_5_8	0x08070504
#घोषणा WLAN_DATA_RATE_FB_RATE0		0xFE01F010
#घोषणा WLAN_DATA_RATE_FB_RATE0_H	0x40000000
#घोषणा WLAN_RTS_RATE_FB_RATE1		0x003FF010
#घोषणा WLAN_RTS_RATE_FB_RATE1_H	0x40000000
#घोषणा WLAN_RTS_RATE_FB_RATE4		0x0600F010
#घोषणा WLAN_RTS_RATE_FB_RATE4_H	0x400003E0
#घोषणा WLAN_RTS_RATE_FB_RATE5		0x0600F015
#घोषणा WLAN_RTS_RATE_FB_RATE5_H	0x000000E0
#घोषणा WLAN_MULTI_ADDR			0xFFFFFFFF

#घोषणा WLAN_TX_FUNC_CFG1		0x30
#घोषणा WLAN_TX_FUNC_CFG2		0x30
#घोषणा WLAN_MAC_OPT_NORM_FUNC1		0x98
#घोषणा WLAN_MAC_OPT_LB_FUNC1		0x80
#घोषणा WLAN_MAC_OPT_FUNC2		0x30810041
#घोषणा WLAN_MAC_INT_MIG_CFG		0x33330000

#घोषणा WLAN_SIFS_CFG	(WLAN_SIFS_CCK_CONT_TX | \
			(WLAN_SIFS_OFDM_CONT_TX << BIT_SHIFT_SIFS_OFDM_CTX) | \
			(WLAN_SIFS_CCK_TRX << BIT_SHIFT_SIFS_CCK_TRX) | \
			(WLAN_SIFS_OFDM_TRX << BIT_SHIFT_SIFS_OFDM_TRX))

#घोषणा WLAN_SIFS_DUR_TUNE	(WLAN_SIFS_CCK_DUR_TUNE | \
				(WLAN_SIFS_OFDM_DUR_TUNE << 8))

#घोषणा WLAN_TBTT_TIME	(WLAN_TBTT_PROHIBIT |\
			(WLAN_TBTT_HOLD_TIME << BIT_SHIFT_TBTT_HOLD_TIME_AP))

#घोषणा WLAN_NAV_CFG		(WLAN_RDG_NAV | (WLAN_TXOP_NAV << 16))
#घोषणा WLAN_RX_TSF_CFG		(WLAN_CCK_RX_TSF | (WLAN_OFDM_RX_TSF) << 8)

#घोषणा MAC_CLK_SPEED	80 /* 80M */
#घोषणा EFUSE_PCB_INFO_OFFSET	0xCA

अटल पूर्णांक rtw8822c_mac_init(काष्ठा rtw_dev *rtwdev)
अणु
	u8 value8;
	u16 value16;
	u32 value32;
	u16 pre_txcnt;

	/* txq control */
	value8 = rtw_पढ़ो8(rtwdev, REG_FWHW_TXQ_CTRL);
	value8 |= (BIT(7) & ~BIT(1) & ~BIT(2));
	rtw_ग_लिखो8(rtwdev, REG_FWHW_TXQ_CTRL, value8);
	rtw_ग_लिखो8(rtwdev, REG_FWHW_TXQ_CTRL + 1, WLAN_TXQ_RPT_EN);
	/* sअगरs control */
	rtw_ग_लिखो16(rtwdev, REG_SPEC_SIFS, WLAN_SIFS_DUR_TUNE);
	rtw_ग_लिखो32(rtwdev, REG_SIFS, WLAN_SIFS_CFG);
	rtw_ग_लिखो16(rtwdev, REG_RESP_SIFS_CCK,
		    WLAN_SIFS_CCK_CTX | WLAN_SIFS_CCK_IRX << 8);
	rtw_ग_लिखो16(rtwdev, REG_RESP_SIFS_OFDM,
		    WLAN_SIFS_OFDM_CTX | WLAN_SIFS_OFDM_IRX << 8);
	/* rate fallback control */
	rtw_ग_लिखो32(rtwdev, REG_DARFRC, WLAN_DATA_RATE_FB_CNT_1_4);
	rtw_ग_लिखो32(rtwdev, REG_DARFRCH, WLAN_DATA_RATE_FB_CNT_5_8);
	rtw_ग_लिखो32(rtwdev, REG_RARFRCH, WLAN_RTS_RATE_FB_CNT_5_8);
	rtw_ग_लिखो32(rtwdev, REG_ARFR0, WLAN_DATA_RATE_FB_RATE0);
	rtw_ग_लिखो32(rtwdev, REG_ARFRH0, WLAN_DATA_RATE_FB_RATE0_H);
	rtw_ग_लिखो32(rtwdev, REG_ARFR1_V1, WLAN_RTS_RATE_FB_RATE1);
	rtw_ग_लिखो32(rtwdev, REG_ARFRH1_V1, WLAN_RTS_RATE_FB_RATE1_H);
	rtw_ग_लिखो32(rtwdev, REG_ARFR4, WLAN_RTS_RATE_FB_RATE4);
	rtw_ग_लिखो32(rtwdev, REG_ARFRH4, WLAN_RTS_RATE_FB_RATE4_H);
	rtw_ग_लिखो32(rtwdev, REG_ARFR5, WLAN_RTS_RATE_FB_RATE5);
	rtw_ग_लिखो32(rtwdev, REG_ARFRH5, WLAN_RTS_RATE_FB_RATE5_H);
	/* protocol configuration */
	rtw_ग_लिखो8(rtwdev, REG_AMPDU_MAX_TIME_V1, WLAN_AMPDU_MAX_TIME);
	rtw_ग_लिखो8_set(rtwdev, REG_TX_HANG_CTRL, BIT_EN_खातापूर्ण_V1);
	pre_txcnt = WLAN_PRE_TXCNT_TIME_TH | BIT_EN_PRECNT;
	rtw_ग_लिखो8(rtwdev, REG_PRECNT_CTRL, (u8)(pre_txcnt & 0xFF));
	rtw_ग_लिखो8(rtwdev, REG_PRECNT_CTRL + 1, (u8)(pre_txcnt >> 8));
	value32 = WLAN_RTS_LEN_TH | (WLAN_RTS_TX_TIME_TH << 8) |
		  (WLAN_MAX_AGG_PKT_LIMIT << 16) |
		  (WLAN_RTS_MAX_AGG_PKT_LIMIT << 24);
	rtw_ग_लिखो32(rtwdev, REG_PROT_MODE_CTRL, value32);
	rtw_ग_लिखो16(rtwdev, REG_BAR_MODE_CTRL + 2,
		    WLAN_BAR_RETRY_LIMIT | WLAN_RA_TRY_RATE_AGG_LIMIT << 8);
	rtw_ग_लिखो8(rtwdev, REG_FAST_EDCA_VOVI_SETTING, FAST_EDCA_VO_TH);
	rtw_ग_लिखो8(rtwdev, REG_FAST_EDCA_VOVI_SETTING + 2, FAST_EDCA_VI_TH);
	rtw_ग_लिखो8(rtwdev, REG_FAST_EDCA_BEBK_SETTING, FAST_EDCA_BE_TH);
	rtw_ग_लिखो8(rtwdev, REG_FAST_EDCA_BEBK_SETTING + 2, FAST_EDCA_BK_TH);
	/* बंद BA parser */
	rtw_ग_लिखो8_clr(rtwdev, REG_LIFETIME_EN, BIT_BA_PARSER_EN);
	rtw_ग_लिखो32_clr(rtwdev, REG_RRSR, BITS_RRSR_RSC);

	/* EDCA configuration */
	rtw_ग_लिखो32(rtwdev, REG_EDCA_VO_PARAM, WLAN_EDCA_VO_PARAM);
	rtw_ग_लिखो32(rtwdev, REG_EDCA_VI_PARAM, WLAN_EDCA_VI_PARAM);
	rtw_ग_लिखो32(rtwdev, REG_EDCA_BE_PARAM, WLAN_EDCA_BE_PARAM);
	rtw_ग_लिखो32(rtwdev, REG_EDCA_BK_PARAM, WLAN_EDCA_BK_PARAM);
	rtw_ग_लिखो8(rtwdev, REG_PIFS, WLAN_PIFS_TIME);
	rtw_ग_लिखो8_clr(rtwdev, REG_TX_PTCL_CTRL + 1, BIT_SIFS_BK_EN >> 8);
	rtw_ग_लिखो8_set(rtwdev, REG_RD_CTRL + 1,
		       (BIT_DIS_TXOP_CFE | BIT_DIS_LSIG_CFE |
			BIT_DIS_STBC_CFE) >> 8);

	/* MAC घड़ी configuration */
	rtw_ग_लिखो32_clr(rtwdev, REG_AFE_CTRL1, BIT_MAC_CLK_SEL);
	rtw_ग_लिखो8(rtwdev, REG_USTIME_TSF, MAC_CLK_SPEED);
	rtw_ग_लिखो8(rtwdev, REG_USTIME_EDCA, MAC_CLK_SPEED);

	rtw_ग_लिखो8_set(rtwdev, REG_MISC_CTRL,
		       BIT_EN_FREE_CNT | BIT_DIS_SECOND_CCA);
	rtw_ग_लिखो8_clr(rtwdev, REG_TIMER0_SRC_SEL, BIT_TSFT_SEL_TIMER0);
	rtw_ग_लिखो16(rtwdev, REG_TXPAUSE, 0x0000);
	rtw_ग_लिखो8(rtwdev, REG_SLOT, WLAN_SLOT_TIME);
	rtw_ग_लिखो32(rtwdev, REG_RD_NAV_NXT, WLAN_NAV_CFG);
	rtw_ग_लिखो16(rtwdev, REG_RXTSF_OFFSET_CCK, WLAN_RX_TSF_CFG);
	/* Set beacon cotnrol - enable TSF and other related functions */
	rtw_ग_लिखो8_set(rtwdev, REG_BCN_CTRL, BIT_EN_BCN_FUNCTION);
	/* Set send beacon related रेजिस्टरs */
	rtw_ग_लिखो32(rtwdev, REG_TBTT_PROHIBIT, WLAN_TBTT_TIME);
	rtw_ग_लिखो8(rtwdev, REG_DRVERLYINT, WLAN_DRV_EARLY_INT);
	rtw_ग_लिखो8(rtwdev, REG_BCN_CTRL_CLINT0, WLAN_BCN_CTRL_CLT0);
	rtw_ग_लिखो8(rtwdev, REG_BCNDMATIM, WLAN_BCN_DMA_TIME);
	rtw_ग_लिखो8(rtwdev, REG_BCN_MAX_ERR, WLAN_BCN_MAX_ERR);

	/* WMAC configuration */
	rtw_ग_लिखो32(rtwdev, REG_MAR, WLAN_MULTI_ADDR);
	rtw_ग_लिखो32(rtwdev, REG_MAR + 4, WLAN_MULTI_ADDR);
	rtw_ग_लिखो8(rtwdev, REG_BBPSF_CTRL + 2, WLAN_RESP_TXRATE);
	rtw_ग_लिखो8(rtwdev, REG_ACKTO, WLAN_ACK_TO);
	rtw_ग_लिखो8(rtwdev, REG_ACKTO_CCK, WLAN_ACK_TO_CCK);
	rtw_ग_लिखो16(rtwdev, REG_EIFS, WLAN_EIFS_DUR_TUNE);
	rtw_ग_लिखो8(rtwdev, REG_NAV_CTRL + 2, WLAN_NAV_MAX);
	rtw_ग_लिखो8(rtwdev, REG_WMAC_TRXPTCL_CTL_H  + 2, WLAN_BAR_ACK_TYPE);
	rtw_ग_लिखो32(rtwdev, REG_RXFLTMAP0, WLAN_RX_FILTER0);
	rtw_ग_लिखो16(rtwdev, REG_RXFLTMAP2, WLAN_RX_FILTER2);
	rtw_ग_लिखो32(rtwdev, REG_RCR, WLAN_RCR_CFG);
	rtw_ग_लिखो8(rtwdev, REG_RX_PKT_LIMIT, WLAN_RXPKT_MAX_SZ_512);
	rtw_ग_लिखो8(rtwdev, REG_TCR + 2, WLAN_TX_FUNC_CFG2);
	rtw_ग_लिखो8(rtwdev, REG_TCR + 1, WLAN_TX_FUNC_CFG1);
	rtw_ग_लिखो32_set(rtwdev, REG_GENERAL_OPTION, BIT_DUMMY_FCS_READY_MASK_EN);
	rtw_ग_लिखो32(rtwdev, REG_WMAC_OPTION_FUNCTION + 8, WLAN_MAC_OPT_FUNC2);
	rtw_ग_लिखो8(rtwdev, REG_WMAC_OPTION_FUNCTION_1, WLAN_MAC_OPT_NORM_FUNC1);

	/* init low घातer */
	value16 = rtw_पढ़ो16(rtwdev, REG_RXPSF_CTRL + 2) & 0xF00F;
	value16 |= (BIT_RXGCK_VHT_FIFOTHR(1) | BIT_RXGCK_HT_FIFOTHR(1) |
		    BIT_RXGCK_OFDM_FIFOTHR(1) | BIT_RXGCK_CCK_FIFOTHR(1)) >> 16;
	rtw_ग_लिखो16(rtwdev, REG_RXPSF_CTRL + 2, value16);
	value16 = 0;
	value16 = BIT_SET_RXPSF_PKTLENTHR(value16, 1);
	value16 |= BIT_RXPSF_CTRLEN | BIT_RXPSF_VHTCHKEN | BIT_RXPSF_HTCHKEN
		| BIT_RXPSF_OFDMCHKEN | BIT_RXPSF_CCKCHKEN
		| BIT_RXPSF_OFDMRST;
	rtw_ग_लिखो16(rtwdev, REG_RXPSF_CTRL, value16);
	rtw_ग_लिखो32(rtwdev, REG_RXPSF_TYPE_CTRL, 0xFFFFFFFF);
	/* rx ignore configuration */
	value16 = rtw_पढ़ो16(rtwdev, REG_RXPSF_CTRL);
	value16 &= ~(BIT_RXPSF_MHCHKEN | BIT_RXPSF_CCKRST |
		     BIT_RXPSF_CONT_ERRCHKEN);
	value16 = BIT_SET_RXPSF_ERRTHR(value16, 0x07);
	rtw_ग_लिखो16(rtwdev, REG_RXPSF_CTRL, value16);

	/* Interrupt migration configuration */
	rtw_ग_लिखो32(rtwdev, REG_INT_MIG, WLAN_MAC_INT_MIG_CFG);

	वापस 0;
पूर्ण

अटल व्योम rtw8822c_dump_fw_crash(काष्ठा rtw_dev *rtwdev)
अणु
	rtw_dump_reg(rtwdev, 0x0, 0x2000, "rtw8822c reg_");
	rtw_dump_fw(rtwdev, OCPBASE_DMEM_88XX, 0x10000, "rtw8822c DMEM_");
	rtw_dump_fw(rtwdev, OCPBASE_IMEM_88XX, 0x10000, "rtw8822c IMEM_");
	rtw_dump_fw(rtwdev, OCPBASE_EMEM_88XX, 0x20000, "rtw8822c EMEM_");
	rtw_dump_fw(rtwdev, OCPBASE_ROM_88XX, 0x10000, "rtw8822c ROM_");
पूर्ण

अटल व्योम rtw8822c_rstb_3wire(काष्ठा rtw_dev *rtwdev, bool enable)
अणु
	अगर (enable) अणु
		rtw_ग_लिखो32_mask(rtwdev, REG_RSTB, BIT_RSTB_3WIRE, 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_ANAPAR_A, BIT_ANAPAR_UPDATE, 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_ANAPAR_B, BIT_ANAPAR_UPDATE, 0x1);
	पूर्ण अन्यथा अणु
		rtw_ग_लिखो32_mask(rtwdev, REG_RSTB, BIT_RSTB_3WIRE, 0x0);
	पूर्ण
पूर्ण

अटल व्योम rtw8822c_set_channel_rf(काष्ठा rtw_dev *rtwdev, u8 channel, u8 bw)
अणु
#घोषणा RF18_BAND_MASK		(BIT(16) | BIT(9) | BIT(8))
#घोषणा RF18_BAND_2G		(0)
#घोषणा RF18_BAND_5G		(BIT(16) | BIT(8))
#घोषणा RF18_CHANNEL_MASK	(MASKBYTE0)
#घोषणा RF18_RFSI_MASK		(BIT(18) | BIT(17))
#घोषणा RF18_RFSI_GE_CH80	(BIT(17))
#घोषणा RF18_RFSI_GT_CH140	(BIT(18))
#घोषणा RF18_BW_MASK		(BIT(13) | BIT(12))
#घोषणा RF18_BW_20M		(BIT(13) | BIT(12))
#घोषणा RF18_BW_40M		(BIT(13))
#घोषणा RF18_BW_80M		(BIT(12))

	u32 rf_reg18 = 0;
	u32 rf_rxbb = 0;

	rf_reg18 = rtw_पढ़ो_rf(rtwdev, RF_PATH_A, 0x18, RFREG_MASK);

	rf_reg18 &= ~(RF18_BAND_MASK | RF18_CHANNEL_MASK | RF18_RFSI_MASK |
		      RF18_BW_MASK);

	rf_reg18 |= (IS_CH_2G_BAND(channel) ? RF18_BAND_2G : RF18_BAND_5G);
	rf_reg18 |= (channel & RF18_CHANNEL_MASK);
	अगर (IS_CH_5G_BAND_4(channel))
		rf_reg18 |= RF18_RFSI_GT_CH140;
	अन्यथा अगर (IS_CH_5G_BAND_3(channel))
		rf_reg18 |= RF18_RFSI_GE_CH80;

	चयन (bw) अणु
	हाल RTW_CHANNEL_WIDTH_5:
	हाल RTW_CHANNEL_WIDTH_10:
	हाल RTW_CHANNEL_WIDTH_20:
	शेष:
		rf_reg18 |= RF18_BW_20M;
		rf_rxbb = 0x18;
		अवरोध;
	हाल RTW_CHANNEL_WIDTH_40:
		/* RF bandwidth */
		rf_reg18 |= RF18_BW_40M;
		rf_rxbb = 0x10;
		अवरोध;
	हाल RTW_CHANNEL_WIDTH_80:
		rf_reg18 |= RF18_BW_80M;
		rf_rxbb = 0x8;
		अवरोध;
	पूर्ण

	rtw8822c_rstb_3wire(rtwdev, false);

	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_LUTWE2, 0x04, 0x01);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_LUTWA, 0x1f, 0x12);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_LUTWD0, 0xfffff, rf_rxbb);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_LUTWE2, 0x04, 0x00);

	rtw_ग_लिखो_rf(rtwdev, RF_PATH_B, RF_LUTWE2, 0x04, 0x01);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_B, RF_LUTWA, 0x1f, 0x12);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_B, RF_LUTWD0, 0xfffff, rf_rxbb);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_B, RF_LUTWE2, 0x04, 0x00);

	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_CFGCH, RFREG_MASK, rf_reg18);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_B, RF_CFGCH, RFREG_MASK, rf_reg18);

	rtw8822c_rstb_3wire(rtwdev, true);
पूर्ण

अटल व्योम rtw8822c_toggle_igi(काष्ठा rtw_dev *rtwdev)
अणु
	u32 igi;

	igi = rtw_पढ़ो32_mask(rtwdev, REG_RXIGI, 0x7f);
	rtw_ग_लिखो32_mask(rtwdev, REG_RXIGI, 0x7f, igi - 2);
	rtw_ग_लिखो32_mask(rtwdev, REG_RXIGI, 0x7f00, igi - 2);
	rtw_ग_लिखो32_mask(rtwdev, REG_RXIGI, 0x7f, igi);
	rtw_ग_लिखो32_mask(rtwdev, REG_RXIGI, 0x7f00, igi);
पूर्ण

अटल व्योम rtw8822c_set_channel_bb(काष्ठा rtw_dev *rtwdev, u8 channel, u8 bw,
				    u8 primary_ch_idx)
अणु
	अगर (IS_CH_2G_BAND(channel)) अणु
		rtw_ग_लिखो32_clr(rtwdev, REG_BGCTRL, BITS_RX_IQ_WEIGHT);
		rtw_ग_लिखो32_set(rtwdev, REG_TXF4, BIT(20));
		rtw_ग_लिखो32_clr(rtwdev, REG_CCK_CHECK, BIT_CHECK_CCK_EN);
		rtw_ग_लिखो32_clr(rtwdev, REG_CCKTXONLY, BIT_BB_CCK_CHECK_EN);
		rtw_ग_लिखो32_mask(rtwdev, REG_CCAMSK, 0x3F000000, 0xF);

		चयन (bw) अणु
		हाल RTW_CHANNEL_WIDTH_20:
			rtw_ग_लिखो32_mask(rtwdev, REG_RXAGCCTL0, BITS_RXAGC_CCK,
					 0x5);
			rtw_ग_लिखो32_mask(rtwdev, REG_RXAGCCTL, BITS_RXAGC_CCK,
					 0x5);
			rtw_ग_लिखो32_mask(rtwdev, REG_RXAGCCTL0, BITS_RXAGC_OFDM,
					 0x6);
			rtw_ग_लिखो32_mask(rtwdev, REG_RXAGCCTL, BITS_RXAGC_OFDM,
					 0x6);
			अवरोध;
		हाल RTW_CHANNEL_WIDTH_40:
			rtw_ग_लिखो32_mask(rtwdev, REG_RXAGCCTL0, BITS_RXAGC_CCK,
					 0x4);
			rtw_ग_लिखो32_mask(rtwdev, REG_RXAGCCTL, BITS_RXAGC_CCK,
					 0x4);
			rtw_ग_लिखो32_mask(rtwdev, REG_RXAGCCTL0, BITS_RXAGC_OFDM,
					 0x0);
			rtw_ग_लिखो32_mask(rtwdev, REG_RXAGCCTL, BITS_RXAGC_OFDM,
					 0x0);
			अवरोध;
		पूर्ण
		अगर (channel == 13 || channel == 14)
			rtw_ग_लिखो32_mask(rtwdev, REG_SCOTRK, 0xfff, 0x969);
		अन्यथा अगर (channel == 11 || channel == 12)
			rtw_ग_लिखो32_mask(rtwdev, REG_SCOTRK, 0xfff, 0x96a);
		अन्यथा
			rtw_ग_लिखो32_mask(rtwdev, REG_SCOTRK, 0xfff, 0x9aa);
		अगर (channel == 14) अणु
			rtw_ग_लिखो32_mask(rtwdev, REG_TXF0, MASKHWORD, 0x3da0);
			rtw_ग_लिखो32_mask(rtwdev, REG_TXF1, MASKDWORD,
					 0x4962c931);
			rtw_ग_लिखो32_mask(rtwdev, REG_TXF2, MASKLWORD, 0x6aa3);
			rtw_ग_लिखो32_mask(rtwdev, REG_TXF3, MASKHWORD, 0xaa7b);
			rtw_ग_लिखो32_mask(rtwdev, REG_TXF4, MASKLWORD, 0xf3d7);
			rtw_ग_लिखो32_mask(rtwdev, REG_TXF5, MASKDWORD, 0x0);
			rtw_ग_लिखो32_mask(rtwdev, REG_TXF6, MASKDWORD,
					 0xff012455);
			rtw_ग_लिखो32_mask(rtwdev, REG_TXF7, MASKDWORD, 0xffff);
		पूर्ण अन्यथा अणु
			rtw_ग_लिखो32_mask(rtwdev, REG_TXF0, MASKHWORD, 0x5284);
			rtw_ग_लिखो32_mask(rtwdev, REG_TXF1, MASKDWORD,
					 0x3e18fec8);
			rtw_ग_लिखो32_mask(rtwdev, REG_TXF2, MASKLWORD, 0x0a88);
			rtw_ग_लिखो32_mask(rtwdev, REG_TXF3, MASKHWORD, 0xacc4);
			rtw_ग_लिखो32_mask(rtwdev, REG_TXF4, MASKLWORD, 0xc8b2);
			rtw_ग_लिखो32_mask(rtwdev, REG_TXF5, MASKDWORD,
					 0x00faf0de);
			rtw_ग_लिखो32_mask(rtwdev, REG_TXF6, MASKDWORD,
					 0x00122344);
			rtw_ग_लिखो32_mask(rtwdev, REG_TXF7, MASKDWORD,
					 0x0fffffff);
		पूर्ण
		अगर (channel == 13)
			rtw_ग_लिखो32_mask(rtwdev, REG_TXDFIR0, 0x70, 0x3);
		अन्यथा
			rtw_ग_लिखो32_mask(rtwdev, REG_TXDFIR0, 0x70, 0x1);
	पूर्ण अन्यथा अगर (IS_CH_5G_BAND(channel)) अणु
		rtw_ग_लिखो32_set(rtwdev, REG_CCKTXONLY, BIT_BB_CCK_CHECK_EN);
		rtw_ग_लिखो32_set(rtwdev, REG_CCK_CHECK, BIT_CHECK_CCK_EN);
		rtw_ग_लिखो32_set(rtwdev, REG_BGCTRL, BITS_RX_IQ_WEIGHT);
		rtw_ग_लिखो32_clr(rtwdev, REG_TXF4, BIT(20));
		rtw_ग_लिखो32_mask(rtwdev, REG_CCAMSK, 0x3F000000, 0x22);
		rtw_ग_लिखो32_mask(rtwdev, REG_TXDFIR0, 0x70, 0x3);
		अगर (IS_CH_5G_BAND_1(channel) || IS_CH_5G_BAND_2(channel)) अणु
			rtw_ग_लिखो32_mask(rtwdev, REG_RXAGCCTL0, BITS_RXAGC_OFDM,
					 0x1);
			rtw_ग_लिखो32_mask(rtwdev, REG_RXAGCCTL, BITS_RXAGC_OFDM,
					 0x1);
		पूर्ण अन्यथा अगर (IS_CH_5G_BAND_3(channel)) अणु
			rtw_ग_लिखो32_mask(rtwdev, REG_RXAGCCTL0, BITS_RXAGC_OFDM,
					 0x2);
			rtw_ग_लिखो32_mask(rtwdev, REG_RXAGCCTL, BITS_RXAGC_OFDM,
					 0x2);
		पूर्ण अन्यथा अगर (IS_CH_5G_BAND_4(channel)) अणु
			rtw_ग_लिखो32_mask(rtwdev, REG_RXAGCCTL0, BITS_RXAGC_OFDM,
					 0x3);
			rtw_ग_लिखो32_mask(rtwdev, REG_RXAGCCTL, BITS_RXAGC_OFDM,
					 0x3);
		पूर्ण

		अगर (channel >= 36 && channel <= 51)
			rtw_ग_लिखो32_mask(rtwdev, REG_SCOTRK, 0xfff, 0x494);
		अन्यथा अगर (channel >= 52 && channel <= 55)
			rtw_ग_लिखो32_mask(rtwdev, REG_SCOTRK, 0xfff, 0x493);
		अन्यथा अगर (channel >= 56 && channel <= 111)
			rtw_ग_लिखो32_mask(rtwdev, REG_SCOTRK, 0xfff, 0x453);
		अन्यथा अगर (channel >= 112 && channel <= 119)
			rtw_ग_लिखो32_mask(rtwdev, REG_SCOTRK, 0xfff, 0x452);
		अन्यथा अगर (channel >= 120 && channel <= 172)
			rtw_ग_लिखो32_mask(rtwdev, REG_SCOTRK, 0xfff, 0x412);
		अन्यथा अगर (channel >= 173 && channel <= 177)
			rtw_ग_लिखो32_mask(rtwdev, REG_SCOTRK, 0xfff, 0x411);
	पूर्ण

	चयन (bw) अणु
	हाल RTW_CHANNEL_WIDTH_20:
		rtw_ग_लिखो32_mask(rtwdev, REG_DFIRBW, 0x3FF0, 0x19B);
		rtw_ग_लिखो32_mask(rtwdev, REG_TXBWCTL, 0xf, 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_TXBWCTL, 0xffc0, 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_TXCLK, 0x700, 0x7);
		rtw_ग_लिखो32_mask(rtwdev, REG_TXCLK, 0x700000, 0x6);
		rtw_ग_लिखो32_mask(rtwdev, REG_CCK_SOURCE, BIT_NBI_EN, 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_SBD, BITS_SUBTUNE, 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_PT_CHSMO, BIT_PT_OPT, 0x0);
		अवरोध;
	हाल RTW_CHANNEL_WIDTH_40:
		rtw_ग_लिखो32_mask(rtwdev, REG_CCKSB, BIT(4),
				 (primary_ch_idx == RTW_SC_20_UPPER ? 1 : 0));
		rtw_ग_लिखो32_mask(rtwdev, REG_TXBWCTL, 0xf, 0x5);
		rtw_ग_लिखो32_mask(rtwdev, REG_TXBWCTL, 0xc0, 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_TXBWCTL, 0xff00,
				 (primary_ch_idx | (primary_ch_idx << 4)));
		rtw_ग_लिखो32_mask(rtwdev, REG_CCK_SOURCE, BIT_NBI_EN, 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_SBD, BITS_SUBTUNE, 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_PT_CHSMO, BIT_PT_OPT, 0x1);
		अवरोध;
	हाल RTW_CHANNEL_WIDTH_80:
		rtw_ग_लिखो32_mask(rtwdev, REG_TXBWCTL, 0xf, 0xa);
		rtw_ग_लिखो32_mask(rtwdev, REG_TXBWCTL, 0xc0, 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_TXBWCTL, 0xff00,
				 (primary_ch_idx | (primary_ch_idx << 4)));
		rtw_ग_लिखो32_mask(rtwdev, REG_SBD, BITS_SUBTUNE, 0x6);
		rtw_ग_लिखो32_mask(rtwdev, REG_PT_CHSMO, BIT_PT_OPT, 0x1);
		अवरोध;
	हाल RTW_CHANNEL_WIDTH_5:
		rtw_ग_लिखो32_mask(rtwdev, REG_DFIRBW, 0x3FF0, 0x2AB);
		rtw_ग_लिखो32_mask(rtwdev, REG_TXBWCTL, 0xf, 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_TXBWCTL, 0xffc0, 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_TXCLK, 0x700, 0x4);
		rtw_ग_लिखो32_mask(rtwdev, REG_TXCLK, 0x700000, 0x4);
		rtw_ग_लिखो32_mask(rtwdev, REG_CCK_SOURCE, BIT_NBI_EN, 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_SBD, BITS_SUBTUNE, 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_PT_CHSMO, BIT_PT_OPT, 0x0);
		अवरोध;
	हाल RTW_CHANNEL_WIDTH_10:
		rtw_ग_लिखो32_mask(rtwdev, REG_DFIRBW, 0x3FF0, 0x2AB);
		rtw_ग_लिखो32_mask(rtwdev, REG_TXBWCTL, 0xf, 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_TXBWCTL, 0xffc0, 0x2);
		rtw_ग_लिखो32_mask(rtwdev, REG_TXCLK, 0x700, 0x6);
		rtw_ग_लिखो32_mask(rtwdev, REG_TXCLK, 0x700000, 0x5);
		rtw_ग_लिखो32_mask(rtwdev, REG_CCK_SOURCE, BIT_NBI_EN, 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_SBD, BITS_SUBTUNE, 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_PT_CHSMO, BIT_PT_OPT, 0x0);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rtw8822c_set_channel(काष्ठा rtw_dev *rtwdev, u8 channel, u8 bw,
				 u8 primary_chan_idx)
अणु
	rtw8822c_set_channel_bb(rtwdev, channel, bw, primary_chan_idx);
	rtw_set_channel_mac(rtwdev, channel, bw, primary_chan_idx);
	rtw8822c_set_channel_rf(rtwdev, channel, bw);
	rtw8822c_toggle_igi(rtwdev);
पूर्ण

अटल व्योम rtw8822c_config_cck_rx_path(काष्ठा rtw_dev *rtwdev, u8 rx_path)
अणु
	अगर (rx_path == BB_PATH_A || rx_path == BB_PATH_B) अणु
		rtw_ग_लिखो32_mask(rtwdev, REG_CCANRX, 0x00060000, 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_CCANRX, 0x00600000, 0x0);
	पूर्ण अन्यथा अगर (rx_path == BB_PATH_AB) अणु
		rtw_ग_लिखो32_mask(rtwdev, REG_CCANRX, 0x00600000, 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_CCANRX, 0x00060000, 0x1);
	पूर्ण

	अगर (rx_path == BB_PATH_A)
		rtw_ग_लिखो32_mask(rtwdev, REG_RXCCKSEL, 0x0f000000, 0x0);
	अन्यथा अगर (rx_path == BB_PATH_B)
		rtw_ग_लिखो32_mask(rtwdev, REG_RXCCKSEL, 0x0f000000, 0x5);
	अन्यथा अगर (rx_path == BB_PATH_AB)
		rtw_ग_लिखो32_mask(rtwdev, REG_RXCCKSEL, 0x0f000000, 0x1);
पूर्ण

अटल व्योम rtw8822c_config_ofdm_rx_path(काष्ठा rtw_dev *rtwdev, u8 rx_path)
अणु
	अगर (rx_path == BB_PATH_A || rx_path == BB_PATH_B) अणु
		rtw_ग_लिखो32_mask(rtwdev, REG_RXFNCTL, 0x300, 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_RXFNCTL, 0x600000, 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_AGCSWSH, BIT(17), 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_ANTWTPD, BIT(20), 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_MRCM, BIT(24), 0x0);
	पूर्ण अन्यथा अगर (rx_path == BB_PATH_AB) अणु
		rtw_ग_लिखो32_mask(rtwdev, REG_RXFNCTL, 0x300, 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_RXFNCTL, 0x600000, 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_AGCSWSH, BIT(17), 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_ANTWTPD, BIT(20), 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_MRCM, BIT(24), 0x1);
	पूर्ण

	rtw_ग_लिखो32_mask(rtwdev, 0x824, 0x0f000000, rx_path);
	rtw_ग_लिखो32_mask(rtwdev, 0x824, 0x000f0000, rx_path);
पूर्ण

अटल व्योम rtw8822c_config_rx_path(काष्ठा rtw_dev *rtwdev, u8 rx_path)
अणु
	rtw8822c_config_cck_rx_path(rtwdev, rx_path);
	rtw8822c_config_ofdm_rx_path(rtwdev, rx_path);
पूर्ण

अटल व्योम rtw8822c_config_cck_tx_path(काष्ठा rtw_dev *rtwdev, u8 tx_path,
					bool is_tx2_path)
अणु
	अगर (tx_path == BB_PATH_A) अणु
		rtw_ग_लिखो32_mask(rtwdev, REG_RXCCKSEL, 0xf0000000, 0x8);
	पूर्ण अन्यथा अगर (tx_path == BB_PATH_B) अणु
		rtw_ग_लिखो32_mask(rtwdev, REG_RXCCKSEL, 0xf0000000, 0x4);
	पूर्ण अन्यथा अणु
		अगर (is_tx2_path)
			rtw_ग_लिखो32_mask(rtwdev, REG_RXCCKSEL, 0xf0000000, 0xc);
		अन्यथा
			rtw_ग_लिखो32_mask(rtwdev, REG_RXCCKSEL, 0xf0000000, 0x8);
	पूर्ण
पूर्ण

अटल व्योम rtw8822c_config_ofdm_tx_path(काष्ठा rtw_dev *rtwdev, u8 tx_path,
					 bool is_tx2_path)
अणु
	अगर (tx_path == BB_PATH_A) अणु
		rtw_ग_लिखो32_mask(rtwdev, REG_ANTMAP0, 0xff, 0x11);
		rtw_ग_लिखो32_mask(rtwdev, REG_TXLGMAP, 0xff, 0x0);
	पूर्ण अन्यथा अगर (tx_path == BB_PATH_B) अणु
		rtw_ग_लिखो32_mask(rtwdev, REG_ANTMAP0, 0xff, 0x12);
		rtw_ग_लिखो32_mask(rtwdev, REG_TXLGMAP, 0xff, 0x0);
	पूर्ण अन्यथा अणु
		अगर (is_tx2_path) अणु
			rtw_ग_लिखो32_mask(rtwdev, REG_ANTMAP0, 0xff, 0x33);
			rtw_ग_लिखो32_mask(rtwdev, REG_TXLGMAP, 0xffff, 0x0404);
		पूर्ण अन्यथा अणु
			rtw_ग_लिखो32_mask(rtwdev, REG_ANTMAP0, 0xff, 0x31);
			rtw_ग_लिखो32_mask(rtwdev, REG_TXLGMAP, 0xffff, 0x0400);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rtw8822c_config_tx_path(काष्ठा rtw_dev *rtwdev, u8 tx_path,
				    bool is_tx2_path)
अणु
	rtw8822c_config_cck_tx_path(rtwdev, tx_path, is_tx2_path);
	rtw8822c_config_ofdm_tx_path(rtwdev, tx_path, is_tx2_path);
पूर्ण

अटल व्योम rtw8822c_config_trx_mode(काष्ठा rtw_dev *rtwdev, u8 tx_path,
				     u8 rx_path, bool is_tx2_path)
अणु
	अगर ((tx_path | rx_path) & BB_PATH_A)
		rtw_ग_लिखो32_mask(rtwdev, REG_ORITXCODE, MASK20BITS, 0x33312);
	अन्यथा
		rtw_ग_लिखो32_mask(rtwdev, REG_ORITXCODE, MASK20BITS, 0x11111);
	अगर ((tx_path | rx_path) & BB_PATH_B)
		rtw_ग_लिखो32_mask(rtwdev, REG_ORITXCODE2, MASK20BITS, 0x33312);
	अन्यथा
		rtw_ग_लिखो32_mask(rtwdev, REG_ORITXCODE2, MASK20BITS, 0x11111);

	rtw8822c_config_rx_path(rtwdev, rx_path);
	rtw8822c_config_tx_path(rtwdev, tx_path, is_tx2_path);

	rtw8822c_toggle_igi(rtwdev);
पूर्ण

अटल व्योम query_phy_status_page0(काष्ठा rtw_dev *rtwdev, u8 *phy_status,
				   काष्ठा rtw_rx_pkt_stat *pkt_stat)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u8 l_bnd, u_bnd;
	u8 gain_a, gain_b;
	s8 rx_घातer[RTW_RF_PATH_MAX];
	s8 min_rx_घातer = -120;
	u8 rssi;
	पूर्णांक path;

	rx_घातer[RF_PATH_A] = GET_PHY_STAT_P0_PWDB_A(phy_status);
	rx_घातer[RF_PATH_B] = GET_PHY_STAT_P0_PWDB_B(phy_status);
	l_bnd = dm_info->cck_gi_l_bnd;
	u_bnd = dm_info->cck_gi_u_bnd;
	gain_a = GET_PHY_STAT_P0_GAIN_A(phy_status);
	gain_b = GET_PHY_STAT_P0_GAIN_B(phy_status);
	अगर (gain_a < l_bnd)
		rx_घातer[RF_PATH_A] += (l_bnd - gain_a) << 1;
	अन्यथा अगर (gain_a > u_bnd)
		rx_घातer[RF_PATH_A] -= (gain_a - u_bnd) << 1;
	अगर (gain_b < l_bnd)
		rx_घातer[RF_PATH_B] += (l_bnd - gain_b) << 1;
	अन्यथा अगर (gain_b > u_bnd)
		rx_घातer[RF_PATH_B] -= (gain_b - u_bnd) << 1;

	rx_घातer[RF_PATH_A] -= 110;
	rx_घातer[RF_PATH_B] -= 110;

	pkt_stat->rx_घातer[RF_PATH_A] = rx_घातer[RF_PATH_A];
	pkt_stat->rx_घातer[RF_PATH_B] = rx_घातer[RF_PATH_B];

	क्रम (path = 0; path <= rtwdev->hal.rf_path_num; path++) अणु
		rssi = rtw_phy_rf_घातer_2_rssi(&pkt_stat->rx_घातer[path], 1);
		dm_info->rssi[path] = rssi;
	पूर्ण

	pkt_stat->rssi = rtw_phy_rf_घातer_2_rssi(pkt_stat->rx_घातer, 1);
	pkt_stat->bw = RTW_CHANNEL_WIDTH_20;
	pkt_stat->संकेत_घातer = max(pkt_stat->rx_घातer[RF_PATH_A],
				     min_rx_घातer);
पूर्ण

अटल व्योम query_phy_status_page1(काष्ठा rtw_dev *rtwdev, u8 *phy_status,
				   काष्ठा rtw_rx_pkt_stat *pkt_stat)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u8 rxsc, bw;
	s8 min_rx_घातer = -120;
	s8 rx_evm;
	u8 evm_dbm = 0;
	u8 rssi;
	पूर्णांक path;

	अगर (pkt_stat->rate > DESC_RATE11M && pkt_stat->rate < DESC_RATEMCS0)
		rxsc = GET_PHY_STAT_P1_L_RXSC(phy_status);
	अन्यथा
		rxsc = GET_PHY_STAT_P1_HT_RXSC(phy_status);

	अगर (rxsc >= 9 && rxsc <= 12)
		bw = RTW_CHANNEL_WIDTH_40;
	अन्यथा अगर (rxsc >= 13)
		bw = RTW_CHANNEL_WIDTH_80;
	अन्यथा
		bw = RTW_CHANNEL_WIDTH_20;

	pkt_stat->rx_घातer[RF_PATH_A] = GET_PHY_STAT_P1_PWDB_A(phy_status) - 110;
	pkt_stat->rx_घातer[RF_PATH_B] = GET_PHY_STAT_P1_PWDB_B(phy_status) - 110;
	pkt_stat->rssi = rtw_phy_rf_घातer_2_rssi(pkt_stat->rx_घातer, 2);
	pkt_stat->bw = bw;
	pkt_stat->संकेत_घातer = max3(pkt_stat->rx_घातer[RF_PATH_A],
				      pkt_stat->rx_घातer[RF_PATH_B],
				      min_rx_घातer);

	dm_info->curr_rx_rate = pkt_stat->rate;

	pkt_stat->rx_evm[RF_PATH_A] = GET_PHY_STAT_P1_RXEVM_A(phy_status);
	pkt_stat->rx_evm[RF_PATH_B] = GET_PHY_STAT_P1_RXEVM_B(phy_status);

	pkt_stat->rx_snr[RF_PATH_A] = GET_PHY_STAT_P1_RXSNR_A(phy_status);
	pkt_stat->rx_snr[RF_PATH_B] = GET_PHY_STAT_P1_RXSNR_B(phy_status);

	pkt_stat->cfo_tail[RF_PATH_A] = GET_PHY_STAT_P1_CFO_TAIL_A(phy_status);
	pkt_stat->cfo_tail[RF_PATH_B] = GET_PHY_STAT_P1_CFO_TAIL_B(phy_status);

	क्रम (path = 0; path <= rtwdev->hal.rf_path_num; path++) अणु
		rssi = rtw_phy_rf_घातer_2_rssi(&pkt_stat->rx_घातer[path], 1);
		dm_info->rssi[path] = rssi;
		dm_info->rx_snr[path] = pkt_stat->rx_snr[path] >> 1;
		dm_info->cfo_tail[path] = (pkt_stat->cfo_tail[path] * 5) >> 1;

		rx_evm = pkt_stat->rx_evm[path];

		अगर (rx_evm < 0) अणु
			अगर (rx_evm == S8_MIN)
				evm_dbm = 0;
			अन्यथा
				evm_dbm = ((u8)-rx_evm >> 1);
		पूर्ण
		dm_info->rx_evm_dbm[path] = evm_dbm;
	पूर्ण
	rtw_phy_parsing_cfo(rtwdev, pkt_stat);
पूर्ण

अटल व्योम query_phy_status(काष्ठा rtw_dev *rtwdev, u8 *phy_status,
			     काष्ठा rtw_rx_pkt_stat *pkt_stat)
अणु
	u8 page;

	page = *phy_status & 0xf;

	चयन (page) अणु
	हाल 0:
		query_phy_status_page0(rtwdev, phy_status, pkt_stat);
		अवरोध;
	हाल 1:
		query_phy_status_page1(rtwdev, phy_status, pkt_stat);
		अवरोध;
	शेष:
		rtw_warn(rtwdev, "unused phy status page (%d)\n", page);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम rtw8822c_query_rx_desc(काष्ठा rtw_dev *rtwdev, u8 *rx_desc,
				   काष्ठा rtw_rx_pkt_stat *pkt_stat,
				   काष्ठा ieee80211_rx_status *rx_status)
अणु
	काष्ठा ieee80211_hdr *hdr;
	u32 desc_sz = rtwdev->chip->rx_pkt_desc_sz;
	u8 *phy_status = शून्य;

	स_रखो(pkt_stat, 0, माप(*pkt_stat));

	pkt_stat->phy_status = GET_RX_DESC_PHYST(rx_desc);
	pkt_stat->icv_err = GET_RX_DESC_ICV_ERR(rx_desc);
	pkt_stat->crc_err = GET_RX_DESC_CRC32(rx_desc);
	pkt_stat->decrypted = !GET_RX_DESC_SWDEC(rx_desc) &&
			      GET_RX_DESC_ENC_TYPE(rx_desc) != RX_DESC_ENC_NONE;
	pkt_stat->is_c2h = GET_RX_DESC_C2H(rx_desc);
	pkt_stat->pkt_len = GET_RX_DESC_PKT_LEN(rx_desc);
	pkt_stat->drv_info_sz = GET_RX_DESC_DRV_INFO_SIZE(rx_desc);
	pkt_stat->shअगरt = GET_RX_DESC_SHIFT(rx_desc);
	pkt_stat->rate = GET_RX_DESC_RX_RATE(rx_desc);
	pkt_stat->cam_id = GET_RX_DESC_MACID(rx_desc);
	pkt_stat->ppdu_cnt = GET_RX_DESC_PPDU_CNT(rx_desc);
	pkt_stat->tsf_low = GET_RX_DESC_TSFL(rx_desc);

	/* drv_info_sz is in unit of 8-bytes */
	pkt_stat->drv_info_sz *= 8;

	/* c2h cmd pkt's rx/phy status is not पूर्णांकerested */
	अगर (pkt_stat->is_c2h)
		वापस;

	hdr = (काष्ठा ieee80211_hdr *)(rx_desc + desc_sz + pkt_stat->shअगरt +
				       pkt_stat->drv_info_sz);
	pkt_stat->hdr = hdr;
	अगर (pkt_stat->phy_status) अणु
		phy_status = rx_desc + desc_sz + pkt_stat->shअगरt;
		query_phy_status(rtwdev, phy_status, pkt_stat);
	पूर्ण

	rtw_rx_fill_rx_status(rtwdev, pkt_stat, hdr, rx_status, phy_status);
पूर्ण

अटल व्योम
rtw8822c_set_ग_लिखो_tx_घातer_ref(काष्ठा rtw_dev *rtwdev, u8 *tx_pwr_ref_cck,
				u8 *tx_pwr_ref_ofdm)
अणु
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	u32 txref_cck[2] = अणु0x18a0, 0x41a0पूर्ण;
	u32 txref_ofdm[2] = अणु0x18e8, 0x41e8पूर्ण;
	u8 path;

	क्रम (path = 0; path < hal->rf_path_num; path++) अणु
		rtw_ग_लिखो32_mask(rtwdev, 0x1c90, BIT(15), 0);
		rtw_ग_लिखो32_mask(rtwdev, txref_cck[path], 0x7f0000,
				 tx_pwr_ref_cck[path]);
	पूर्ण
	क्रम (path = 0; path < hal->rf_path_num; path++) अणु
		rtw_ग_लिखो32_mask(rtwdev, 0x1c90, BIT(15), 0);
		rtw_ग_लिखो32_mask(rtwdev, txref_ofdm[path], 0x1fc00,
				 tx_pwr_ref_ofdm[path]);
	पूर्ण
पूर्ण

अटल व्योम rtw8822c_set_tx_घातer_dअगरf(काष्ठा rtw_dev *rtwdev, u8 rate,
				       s8 *dअगरf_idx)
अणु
	u32 offset_txagc = 0x3a00;
	u8 rate_idx = rate & 0xfc;
	u8 pwr_idx[4];
	u32 phy_pwr_idx;
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++)
		pwr_idx[i] = dअगरf_idx[i] & 0x7f;

	phy_pwr_idx = pwr_idx[0] |
		      (pwr_idx[1] << 8) |
		      (pwr_idx[2] << 16) |
		      (pwr_idx[3] << 24);

	rtw_ग_लिखो32_mask(rtwdev, 0x1c90, BIT(15), 0x0);
	rtw_ग_लिखो32_mask(rtwdev, offset_txagc + rate_idx, MASKDWORD,
			 phy_pwr_idx);
पूर्ण

अटल व्योम rtw8822c_set_tx_घातer_index(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_hal *hal = &rtwdev->hal;
	u8 rs, rate, j;
	u8 pwr_ref_cck[2] = अणुhal->tx_pwr_tbl[RF_PATH_A][DESC_RATE11M],
			     hal->tx_pwr_tbl[RF_PATH_B][DESC_RATE11M]पूर्ण;
	u8 pwr_ref_ofdm[2] = अणुhal->tx_pwr_tbl[RF_PATH_A][DESC_RATEMCS7],
			      hal->tx_pwr_tbl[RF_PATH_B][DESC_RATEMCS7]पूर्ण;
	s8 dअगरf_a, dअगरf_b;
	u8 pwr_a, pwr_b;
	s8 dअगरf_idx[4];

	rtw8822c_set_ग_लिखो_tx_घातer_ref(rtwdev, pwr_ref_cck, pwr_ref_ofdm);
	क्रम (rs = 0; rs < RTW_RATE_SECTION_MAX; rs++) अणु
		क्रम (j = 0; j < rtw_rate_size[rs]; j++) अणु
			rate = rtw_rate_section[rs][j];
			pwr_a = hal->tx_pwr_tbl[RF_PATH_A][rate];
			pwr_b = hal->tx_pwr_tbl[RF_PATH_B][rate];
			अगर (rs == 0) अणु
				dअगरf_a = (s8)pwr_a - (s8)pwr_ref_cck[0];
				dअगरf_b = (s8)pwr_b - (s8)pwr_ref_cck[1];
			पूर्ण अन्यथा अणु
				dअगरf_a = (s8)pwr_a - (s8)pwr_ref_ofdm[0];
				dअगरf_b = (s8)pwr_b - (s8)pwr_ref_ofdm[1];
			पूर्ण
			dअगरf_idx[rate % 4] = min(dअगरf_a, dअगरf_b);
			अगर (rate % 4 == 3)
				rtw8822c_set_tx_घातer_dअगरf(rtwdev, rate - 3,
							   dअगरf_idx);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक rtw8822c_set_antenna(काष्ठा rtw_dev *rtwdev,
				u32 antenna_tx,
				u32 antenna_rx)
अणु
	काष्ठा rtw_hal *hal = &rtwdev->hal;

	चयन (antenna_tx) अणु
	हाल BB_PATH_A:
	हाल BB_PATH_B:
	हाल BB_PATH_AB:
		अवरोध;
	शेष:
		rtw_info(rtwdev, "unsupported tx path 0x%x\n", antenna_tx);
		वापस -EINVAL;
	पूर्ण

	/* path B only is not available क्रम RX */
	चयन (antenna_rx) अणु
	हाल BB_PATH_A:
	हाल BB_PATH_AB:
		अवरोध;
	शेष:
		rtw_info(rtwdev, "unsupported rx path 0x%x\n", antenna_rx);
		वापस -EINVAL;
	पूर्ण

	hal->antenna_tx = antenna_tx;
	hal->antenna_rx = antenna_rx;

	rtw8822c_config_trx_mode(rtwdev, antenna_tx, antenna_rx, false);

	वापस 0;
पूर्ण

अटल व्योम rtw8822c_cfg_lकरो25(काष्ठा rtw_dev *rtwdev, bool enable)
अणु
	u8 lकरो_pwr;

	lकरो_pwr = rtw_पढ़ो8(rtwdev, REG_ANAPARLDO_POW_MAC);
	lकरो_pwr = enable ? lकरो_pwr | BIT_LDOE25_PON : lकरो_pwr & ~BIT_LDOE25_PON;
	rtw_ग_लिखो8(rtwdev, REG_ANAPARLDO_POW_MAC, lकरो_pwr);
पूर्ण

अटल व्योम rtw8822c_false_alarm_statistics(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u32 cck_enable;
	u32 cck_fa_cnt;
	u32 crc32_cnt;
	u32 cca32_cnt;
	u32 ofdm_fa_cnt;
	u32 ofdm_fa_cnt1, ofdm_fa_cnt2, ofdm_fa_cnt3, ofdm_fa_cnt4, ofdm_fa_cnt5;
	u16 parity_fail, rate_illegal, crc8_fail, mcs_fail, sb_search_fail,
	    fast_fsync, crc8_fail_vhta, mcs_fail_vht;

	cck_enable = rtw_पढ़ो32(rtwdev, REG_ENCCK) & BIT_CCK_BLK_EN;
	cck_fa_cnt = rtw_पढ़ो16(rtwdev, REG_CCK_FACNT);

	ofdm_fa_cnt1 = rtw_पढ़ो32(rtwdev, REG_OFDM_FACNT1);
	ofdm_fa_cnt2 = rtw_पढ़ो32(rtwdev, REG_OFDM_FACNT2);
	ofdm_fa_cnt3 = rtw_पढ़ो32(rtwdev, REG_OFDM_FACNT3);
	ofdm_fa_cnt4 = rtw_पढ़ो32(rtwdev, REG_OFDM_FACNT4);
	ofdm_fa_cnt5 = rtw_पढ़ो32(rtwdev, REG_OFDM_FACNT5);

	parity_fail	= FIELD_GET(GENMASK(31, 16), ofdm_fa_cnt1);
	rate_illegal	= FIELD_GET(GENMASK(15, 0), ofdm_fa_cnt2);
	crc8_fail	= FIELD_GET(GENMASK(31, 16), ofdm_fa_cnt2);
	crc8_fail_vhta	= FIELD_GET(GENMASK(15, 0), ofdm_fa_cnt3);
	mcs_fail	= FIELD_GET(GENMASK(15, 0), ofdm_fa_cnt4);
	mcs_fail_vht	= FIELD_GET(GENMASK(31, 16), ofdm_fa_cnt4);
	fast_fsync	= FIELD_GET(GENMASK(15, 0), ofdm_fa_cnt5);
	sb_search_fail	= FIELD_GET(GENMASK(31, 16), ofdm_fa_cnt5);

	ofdm_fa_cnt = parity_fail + rate_illegal + crc8_fail + crc8_fail_vhta +
		      mcs_fail + mcs_fail_vht + fast_fsync + sb_search_fail;

	dm_info->cck_fa_cnt = cck_fa_cnt;
	dm_info->ofdm_fa_cnt = ofdm_fa_cnt;
	dm_info->total_fa_cnt = ofdm_fa_cnt;
	dm_info->total_fa_cnt += cck_enable ? cck_fa_cnt : 0;

	crc32_cnt = rtw_पढ़ो32(rtwdev, 0x2c04);
	dm_info->cck_ok_cnt = crc32_cnt & 0xffff;
	dm_info->cck_err_cnt = (crc32_cnt & 0xffff0000) >> 16;
	crc32_cnt = rtw_पढ़ो32(rtwdev, 0x2c14);
	dm_info->ofdm_ok_cnt = crc32_cnt & 0xffff;
	dm_info->ofdm_err_cnt = (crc32_cnt & 0xffff0000) >> 16;
	crc32_cnt = rtw_पढ़ो32(rtwdev, 0x2c10);
	dm_info->ht_ok_cnt = crc32_cnt & 0xffff;
	dm_info->ht_err_cnt = (crc32_cnt & 0xffff0000) >> 16;
	crc32_cnt = rtw_पढ़ो32(rtwdev, 0x2c0c);
	dm_info->vht_ok_cnt = crc32_cnt & 0xffff;
	dm_info->vht_err_cnt = (crc32_cnt & 0xffff0000) >> 16;

	cca32_cnt = rtw_पढ़ो32(rtwdev, 0x2c08);
	dm_info->ofdm_cca_cnt = ((cca32_cnt & 0xffff0000) >> 16);
	dm_info->cck_cca_cnt = cca32_cnt & 0xffff;
	dm_info->total_cca_cnt = dm_info->ofdm_cca_cnt;
	अगर (cck_enable)
		dm_info->total_cca_cnt += dm_info->cck_cca_cnt;

	rtw_ग_लिखो32_mask(rtwdev, REG_CCANRX, BIT_CCK_FA_RST, 0);
	rtw_ग_लिखो32_mask(rtwdev, REG_CCANRX, BIT_CCK_FA_RST, 2);
	rtw_ग_लिखो32_mask(rtwdev, REG_CCANRX, BIT_OFDM_FA_RST, 0);
	rtw_ग_लिखो32_mask(rtwdev, REG_CCANRX, BIT_OFDM_FA_RST, 2);

	/* disable rx clk gating to reset counters */
	rtw_ग_लिखो32_clr(rtwdev, REG_RX_BREAK, BIT_COM_RX_GCK_EN);
	rtw_ग_लिखो32_set(rtwdev, REG_CNT_CTRL, BIT_ALL_CNT_RST);
	rtw_ग_लिखो32_clr(rtwdev, REG_CNT_CTRL, BIT_ALL_CNT_RST);
	rtw_ग_लिखो32_set(rtwdev, REG_RX_BREAK, BIT_COM_RX_GCK_EN);
पूर्ण

अटल व्योम rtw8822c_करो_lck(काष्ठा rtw_dev *rtwdev)
अणु
	u32 val;

	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_SYN_CTRL, RFREG_MASK, 0x80010);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_SYN_PFD, RFREG_MASK, 0x1F0FA);
	fsleep(1);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_AAC_CTRL, RFREG_MASK, 0x80000);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_SYN_AAC, RFREG_MASK, 0x80001);
	पढ़ो_poll_समयout(rtw_पढ़ो_rf, val, val != 0x1, 1000, 100000,
			  true, rtwdev, RF_PATH_A, RF_AAC_CTRL, 0x1000);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_SYN_PFD, RFREG_MASK, 0x1F0F8);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_B, RF_SYN_CTRL, RFREG_MASK, 0x80010);

	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_FAST_LCK, RFREG_MASK, 0x0f000);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_FAST_LCK, RFREG_MASK, 0x4f000);
	fsleep(1);
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_FAST_LCK, RFREG_MASK, 0x0f000);
पूर्ण

अटल व्योम rtw8822c_करो_iqk(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_iqk_para para = अणु0पूर्ण;
	u8 iqk_chk;
	पूर्णांक ret;

	para.clear = 1;
	rtw_fw_करो_iqk(rtwdev, &para);

	ret = पढ़ो_poll_समयout(rtw_पढ़ो8, iqk_chk, iqk_chk == IQK_DONE_8822C,
				20000, 300000, false, rtwdev, REG_RPT_CIP);
	अगर (ret)
		rtw_warn(rtwdev, "failed to poll iqk status bit\n");

	rtw_ग_लिखो8(rtwdev, REG_IQKSTAT, 0x0);
पूर्ण

/* क्रम coex */
अटल व्योम rtw8822c_coex_cfg_init(काष्ठा rtw_dev *rtwdev)
अणु
	/* enable TBTT nterrupt */
	rtw_ग_लिखो8_set(rtwdev, REG_BCN_CTRL, BIT_EN_BCN_FUNCTION);

	/* BT report packet sample rate */
	/* 0x790[5:0]=0x5 */
	rtw_ग_लिखो8_mask(rtwdev, REG_BT_TDMA_TIME, BIT_MASK_SAMPLE_RATE, 0x5);

	/* enable BT counter statistics */
	rtw_ग_लिखो8(rtwdev, REG_BT_STAT_CTRL, 0x1);

	/* enable PTA (3-wire function क्रमm BT side) */
	rtw_ग_लिखो32_set(rtwdev, REG_GPIO_MUXCFG, BIT_BT_PTA_EN);
	rtw_ग_लिखो32_set(rtwdev, REG_GPIO_MUXCFG, BIT_PO_BT_PTA_PINS);

	/* enable PTA (tx/rx संकेत क्रमm WiFi side) */
	rtw_ग_लिखो8_set(rtwdev, REG_QUEUE_CTRL, BIT_PTA_WL_TX_EN);
	/* wl tx संकेत to PTA not हाल EDCCA */
	rtw_ग_लिखो8_clr(rtwdev, REG_QUEUE_CTRL, BIT_PTA_EDCCA_EN);
	/* GNT_BT=1 जबतक select both */
	rtw_ग_लिखो16_set(rtwdev, REG_BT_COEX_V2, BIT_GNT_BT_POLARITY);
	/* BT_CCA = ~GNT_WL_BB, not or GNT_BT_BB, LTE_Rx */
	rtw_ग_लिखो8_clr(rtwdev, REG_DUMMY_PAGE4_V1, BIT_BTCCA_CTRL);

	/* to aव्योम RF parameter error */
	rtw_ग_लिखो_rf(rtwdev, RF_PATH_B, RF_MODOPT, 0xfffff, 0x40000);
पूर्ण

अटल व्योम rtw8822c_coex_cfg_gnt_fix(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_stat *coex_stat = &coex->stat;
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	u32 rf_0x1;

	अगर (coex_stat->gnt_workaround_state == coex_stat->wl_coex_mode)
		वापस;

	coex_stat->gnt_workaround_state = coex_stat->wl_coex_mode;

	अगर ((coex_stat->kt_ver == 0 && coex->under_5g) || coex->मुक्तrun)
		rf_0x1 = 0x40021;
	अन्यथा
		rf_0x1 = 0x40000;

	/* BT at S1 क्रम Shared-Ant */
	अगर (efuse->share_ant)
		rf_0x1 |= BIT(13);

	rtw_ग_लिखो_rf(rtwdev, RF_PATH_B, 0x1, 0xfffff, rf_0x1);

	/* WL-S0 2G RF TRX cannot be masked by GNT_BT
	 * enable "WLS0 BB chage RF mode if GNT_BT = 1" क्रम shared-antenna type
	 * disable:0x1860[3] = 1, enable:0x1860[3] = 0
	 *
	 * enable "DAC off if GNT_WL = 0" क्रम non-shared-antenna
	 * disable 0x1c30[22] = 0,
	 * enable: 0x1c30[22] = 1, 0x1c38[12] = 0, 0x1c38[28] = 1
	 *
	 * disable WL-S1 BB chage RF mode अगर GNT_BT
	 * since RF TRx mask can करो it
	 */
	rtw_ग_लिखो8_mask(rtwdev, REG_ANAPAR + 2, BIT_ANAPAR_BTPS >> 16, 1);
	rtw_ग_लिखो8_mask(rtwdev, REG_RSTB_SEL + 1, BIT_DAC_OFF_ENABLE, 0);
	rtw_ग_लिखो8_mask(rtwdev, REG_RSTB_SEL + 3, BIT_DAC_OFF_ENABLE, 1);
	rtw_ग_लिखो8_mask(rtwdev, REG_IGN_GNTBT4, BIT_PI_IGNORE_GNT_BT, 1);

	/* disable WL-S0 BB chage RF mode अगर wअगरi is at 5G,
	 * or antenna path is separated
	 */
	अगर (coex_stat->wl_coex_mode == COEX_WLINK_5G ||
	    coex->under_5g || !efuse->share_ant) अणु
		अगर (coex_stat->kt_ver >= 3) अणु
			rtw_ग_लिखो8_mask(rtwdev, REG_IGN_GNT_BT1,
					BIT_PI_IGNORE_GNT_BT, 0);
			rtw_ग_लिखो8_mask(rtwdev, REG_NOMASK_TXBT,
					BIT_NOMASK_TXBT_ENABLE, 1);
		पूर्ण अन्यथा अणु
			rtw_ग_लिखो8_mask(rtwdev, REG_IGN_GNT_BT1,
					BIT_PI_IGNORE_GNT_BT, 1);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* shared-antenna */
		rtw_ग_लिखो8_mask(rtwdev, REG_IGN_GNT_BT1,
				BIT_PI_IGNORE_GNT_BT, 0);
		अगर (coex_stat->kt_ver >= 3) अणु
			rtw_ग_लिखो8_mask(rtwdev, REG_NOMASK_TXBT,
					BIT_NOMASK_TXBT_ENABLE, 0);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rtw8822c_coex_cfg_gnt_debug(काष्ठा rtw_dev *rtwdev)
अणु
	rtw_ग_लिखो8_mask(rtwdev, REG_PAD_CTRL1 + 2, BIT_BTGP_SPI_EN >> 16, 0);
	rtw_ग_लिखो8_mask(rtwdev, REG_PAD_CTRL1 + 3, BIT_BTGP_JTAG_EN >> 24, 0);
	rtw_ग_लिखो8_mask(rtwdev, REG_GPIO_MUXCFG + 2, BIT_FSPI_EN >> 16, 0);
	rtw_ग_लिखो8_mask(rtwdev, REG_PAD_CTRL1 + 1, BIT_LED1DIS >> 8, 0);
	rtw_ग_लिखो8_mask(rtwdev, REG_SYS_SDIO_CTRL + 3, BIT_DBG_GNT_WL_BT >> 24, 0);
पूर्ण

अटल व्योम rtw8822c_coex_cfg_rfe_type(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_rfe *coex_rfe = &coex->rfe;
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;

	coex_rfe->rfe_module_type = rtwdev->efuse.rfe_option;
	coex_rfe->ant_चयन_polarity = 0;
	coex_rfe->ant_चयन_exist = false;
	coex_rfe->ant_चयन_with_bt = false;
	coex_rfe->ant_चयन_भागersity = false;

	अगर (efuse->share_ant)
		coex_rfe->wlg_at_btg = true;
	अन्यथा
		coex_rfe->wlg_at_btg = false;

	/* disable LTE coex in wअगरi side */
	rtw_coex_ग_लिखो_indirect_reg(rtwdev, LTE_COEX_CTRL, BIT_LTE_COEX_EN, 0x0);
	rtw_coex_ग_लिखो_indirect_reg(rtwdev, LTE_WL_TRX_CTRL, MASKLWORD, 0xffff);
	rtw_coex_ग_लिखो_indirect_reg(rtwdev, LTE_BT_TRX_CTRL, MASKLWORD, 0xffff);
पूर्ण

अटल व्योम rtw8822c_coex_cfg_wl_tx_घातer(काष्ठा rtw_dev *rtwdev, u8 wl_pwr)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_dm *coex_dm = &coex->dm;

	अगर (wl_pwr == coex_dm->cur_wl_pwr_lvl)
		वापस;

	coex_dm->cur_wl_pwr_lvl = wl_pwr;
पूर्ण

अटल व्योम rtw8822c_coex_cfg_wl_rx_gain(काष्ठा rtw_dev *rtwdev, bool low_gain)
अणु
	काष्ठा rtw_coex *coex = &rtwdev->coex;
	काष्ठा rtw_coex_dm *coex_dm = &coex->dm;

	अगर (low_gain == coex_dm->cur_wl_rx_low_gain_en)
		वापस;

	coex_dm->cur_wl_rx_low_gain_en = low_gain;

	अगर (coex_dm->cur_wl_rx_low_gain_en) अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], Hi-Li Table On!\n");

		/* set Rx filter corner RCK offset */
		rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_RCKD, RFREG_MASK, 0x22);
		rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_RCK, RFREG_MASK, 0x36);
		rtw_ग_लिखो_rf(rtwdev, RF_PATH_B, RF_RCKD, RFREG_MASK, 0x22);
		rtw_ग_लिखो_rf(rtwdev, RF_PATH_B, RF_RCK, RFREG_MASK, 0x36);

	पूर्ण अन्यथा अणु
		rtw_dbg(rtwdev, RTW_DBG_COEX, "[BTCoex], Hi-Li Table Off!\n");

		/* set Rx filter corner RCK offset */
		rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_RCKD, RFREG_MASK, 0x20);
		rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_RCK, RFREG_MASK, 0x0);
		rtw_ग_लिखो_rf(rtwdev, RF_PATH_B, RF_RCKD, RFREG_MASK, 0x20);
		rtw_ग_लिखो_rf(rtwdev, RF_PATH_B, RF_RCK, RFREG_MASK, 0x0);
	पूर्ण
पूर्ण

अटल व्योम rtw8822c_bf_enable_bfee_su(काष्ठा rtw_dev *rtwdev,
				       काष्ठा rtw_vअगर *vअगर,
				       काष्ठा rtw_bfee *bfee)
अणु
	u8 csi_rsc = 0;
	u32 पंचांगp6dc;

	rtw_bf_enable_bfee_su(rtwdev, vअगर, bfee);

	पंचांगp6dc = rtw_पढ़ो32(rtwdev, REG_BBPSF_CTRL) |
			    BIT_WMAC_USE_NDPARATE |
			    (csi_rsc << 13);
	अगर (vअगर->net_type == RTW_NET_AP_MODE)
		rtw_ग_लिखो32(rtwdev, REG_BBPSF_CTRL, पंचांगp6dc | BIT(12));
	अन्यथा
		rtw_ग_लिखो32(rtwdev, REG_BBPSF_CTRL, पंचांगp6dc & ~BIT(12));

	rtw_ग_लिखो32(rtwdev, REG_CSI_RRSR, 0x550);
पूर्ण

अटल व्योम rtw8822c_bf_config_bfee_su(काष्ठा rtw_dev *rtwdev,
				       काष्ठा rtw_vअगर *vअगर,
				       काष्ठा rtw_bfee *bfee, bool enable)
अणु
	अगर (enable)
		rtw8822c_bf_enable_bfee_su(rtwdev, vअगर, bfee);
	अन्यथा
		rtw_bf_हटाओ_bfee_su(rtwdev, bfee);
पूर्ण

अटल व्योम rtw8822c_bf_config_bfee_mu(काष्ठा rtw_dev *rtwdev,
				       काष्ठा rtw_vअगर *vअगर,
				       काष्ठा rtw_bfee *bfee, bool enable)
अणु
	अगर (enable)
		rtw_bf_enable_bfee_mu(rtwdev, vअगर, bfee);
	अन्यथा
		rtw_bf_हटाओ_bfee_mu(rtwdev, bfee);
पूर्ण

अटल व्योम rtw8822c_bf_config_bfee(काष्ठा rtw_dev *rtwdev, काष्ठा rtw_vअगर *vअगर,
				    काष्ठा rtw_bfee *bfee, bool enable)
अणु
	अगर (bfee->role == RTW_BFEE_SU)
		rtw8822c_bf_config_bfee_su(rtwdev, vअगर, bfee, enable);
	अन्यथा अगर (bfee->role == RTW_BFEE_MU)
		rtw8822c_bf_config_bfee_mu(rtwdev, vअगर, bfee, enable);
	अन्यथा
		rtw_warn(rtwdev, "wrong bfee role\n");
पूर्ण

काष्ठा dpk_cfg_pair अणु
	u32 addr;
	u32 biपंचांगask;
	u32 data;
पूर्ण;

व्योम rtw8822c_parse_tbl_dpk(काष्ठा rtw_dev *rtwdev,
			    स्थिर काष्ठा rtw_table *tbl)
अणु
	स्थिर काष्ठा dpk_cfg_pair *p = tbl->data;
	स्थिर काष्ठा dpk_cfg_pair *end = p + tbl->size / 3;

	BUILD_BUG_ON(माप(काष्ठा dpk_cfg_pair) != माप(u32) * 3);

	क्रम (; p < end; p++)
		rtw_ग_लिखो32_mask(rtwdev, p->addr, p->biपंचांगask, p->data);
पूर्ण

अटल व्योम rtw8822c_dpk_set_gnt_wl(काष्ठा rtw_dev *rtwdev, bool is_beक्रमe_k)
अणु
	काष्ठा rtw_dpk_info *dpk_info = &rtwdev->dm_info.dpk_info;

	अगर (is_beक्रमe_k) अणु
		dpk_info->gnt_control = rtw_पढ़ो32(rtwdev, 0x70);
		dpk_info->gnt_value = rtw_coex_पढ़ो_indirect_reg(rtwdev, 0x38);
		rtw_ग_लिखो32_mask(rtwdev, 0x70, BIT(26), 0x1);
		rtw_coex_ग_लिखो_indirect_reg(rtwdev, 0x38, MASKBYTE1, 0x77);
	पूर्ण अन्यथा अणु
		rtw_coex_ग_लिखो_indirect_reg(rtwdev, 0x38, MASKDWORD,
					    dpk_info->gnt_value);
		rtw_ग_लिखो32(rtwdev, 0x70, dpk_info->gnt_control);
	पूर्ण
पूर्ण

अटल व्योम
rtw8822c_dpk_restore_रेजिस्टरs(काष्ठा rtw_dev *rtwdev, u32 reg_num,
			       काष्ठा rtw_backup_info *bckp)
अणु
	rtw_restore_reg(rtwdev, bckp, reg_num);
	rtw_ग_लिखो32_mask(rtwdev, REG_NCTL0, BIT_SUBPAGE, 0xc);
	rtw_ग_लिखो32_mask(rtwdev, REG_RXSRAM_CTL, BIT_DPD_CLK, 0x4);
पूर्ण

अटल व्योम
rtw8822c_dpk_backup_रेजिस्टरs(काष्ठा rtw_dev *rtwdev, u32 *reg,
			      u32 reg_num, काष्ठा rtw_backup_info *bckp)
अणु
	u32 i;

	क्रम (i = 0; i < reg_num; i++) अणु
		bckp[i].len = 4;
		bckp[i].reg = reg[i];
		bckp[i].val = rtw_पढ़ो32(rtwdev, reg[i]);
	पूर्ण
पूर्ण

अटल व्योम rtw8822c_dpk_backup_rf_रेजिस्टरs(काष्ठा rtw_dev *rtwdev,
					     u32 *rf_reg,
					     u32 rf_reg_bak[][2])
अणु
	u32 i;

	क्रम (i = 0; i < DPK_RF_REG_NUM; i++) अणु
		rf_reg_bak[i][RF_PATH_A] = rtw_पढ़ो_rf(rtwdev, RF_PATH_A,
						       rf_reg[i], RFREG_MASK);
		rf_reg_bak[i][RF_PATH_B] = rtw_पढ़ो_rf(rtwdev, RF_PATH_B,
						       rf_reg[i], RFREG_MASK);
	पूर्ण
पूर्ण

अटल व्योम rtw8822c_dpk_reload_rf_रेजिस्टरs(काष्ठा rtw_dev *rtwdev,
					     u32 *rf_reg,
					     u32 rf_reg_bak[][2])
अणु
	u32 i;

	क्रम (i = 0; i < DPK_RF_REG_NUM; i++) अणु
		rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, rf_reg[i], RFREG_MASK,
			     rf_reg_bak[i][RF_PATH_A]);
		rtw_ग_लिखो_rf(rtwdev, RF_PATH_B, rf_reg[i], RFREG_MASK,
			     rf_reg_bak[i][RF_PATH_B]);
	पूर्ण
पूर्ण

अटल व्योम rtw8822c_dpk_inक्रमmation(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dpk_info *dpk_info = &rtwdev->dm_info.dpk_info;
	u32  reg;
	u8 band_shअगरt;

	reg = rtw_पढ़ो_rf(rtwdev, RF_PATH_A, 0x18, RFREG_MASK);

	band_shअगरt = FIELD_GET(BIT(16), reg);
	dpk_info->dpk_band = 1 << band_shअगरt;
	dpk_info->dpk_ch = FIELD_GET(0xff, reg);
	dpk_info->dpk_bw = FIELD_GET(0x3000, reg);
पूर्ण

अटल व्योम rtw8822c_dpk_rxbb_dc_cal(काष्ठा rtw_dev *rtwdev, u8 path)
अणु
	rtw_ग_लिखो_rf(rtwdev, path, 0x92, RFREG_MASK, 0x84800);
	udelay(5);
	rtw_ग_लिखो_rf(rtwdev, path, 0x92, RFREG_MASK, 0x84801);
	usleep_range(600, 610);
	rtw_ग_लिखो_rf(rtwdev, path, 0x92, RFREG_MASK, 0x84800);
पूर्ण

अटल u8 rtw8822c_dpk_dc_corr_check(काष्ठा rtw_dev *rtwdev, u8 path)
अणु
	u16 dc_i, dc_q;
	u8 corr_idx;

	rtw_ग_लिखो32(rtwdev, REG_RXSRAM_CTL, 0x000900f0);
	dc_i = (u16)rtw_पढ़ो32_mask(rtwdev, REG_STAT_RPT, GENMASK(27, 16));
	dc_q = (u16)rtw_पढ़ो32_mask(rtwdev, REG_STAT_RPT, GENMASK(11, 0));

	अगर (dc_i & BIT(11))
		dc_i = 0x1000 - dc_i;
	अगर (dc_q & BIT(11))
		dc_q = 0x1000 - dc_q;

	rtw_ग_लिखो32(rtwdev, REG_RXSRAM_CTL, 0x000000f0);
	corr_idx = (u8)rtw_पढ़ो32_mask(rtwdev, REG_STAT_RPT, GENMASK(7, 0));
	rtw_पढ़ो32_mask(rtwdev, REG_STAT_RPT, GENMASK(15, 8));

	अगर (dc_i > 200 || dc_q > 200 || corr_idx < 40 || corr_idx > 65)
		वापस 1;
	अन्यथा
		वापस 0;

पूर्ण

अटल व्योम rtw8822c_dpk_tx_छोड़ो(काष्ठा rtw_dev *rtwdev)
अणु
	u8 reg_a, reg_b;
	u16 count = 0;

	rtw_ग_लिखो8(rtwdev, 0x522, 0xff);
	rtw_ग_लिखो32_mask(rtwdev, 0x1e70, 0xf, 0x2);

	करो अणु
		reg_a = (u8)rtw_पढ़ो_rf(rtwdev, RF_PATH_A, 0x00, 0xf0000);
		reg_b = (u8)rtw_पढ़ो_rf(rtwdev, RF_PATH_B, 0x00, 0xf0000);
		udelay(2);
		count++;
	पूर्ण जबतक ((reg_a == 2 || reg_b == 2) && count < 2500);
पूर्ण

अटल व्योम rtw8822c_dpk_mac_bb_setting(काष्ठा rtw_dev *rtwdev)
अणु
	rtw8822c_dpk_tx_छोड़ो(rtwdev);
	rtw_load_table(rtwdev, &rtw8822c_dpk_mac_bb_tbl);
पूर्ण

अटल व्योम rtw8822c_dpk_afe_setting(काष्ठा rtw_dev *rtwdev, bool is_करो_dpk)
अणु
	अगर (is_करो_dpk)
		rtw_load_table(rtwdev, &rtw8822c_dpk_afe_is_dpk_tbl);
	अन्यथा
		rtw_load_table(rtwdev, &rtw8822c_dpk_afe_no_dpk_tbl);
पूर्ण

अटल व्योम rtw8822c_dpk_pre_setting(काष्ठा rtw_dev *rtwdev)
अणु
	u8 path;

	क्रम (path = 0; path < rtwdev->hal.rf_path_num; path++) अणु
		rtw_ग_लिखो_rf(rtwdev, path, RF_RXAGC_OFFSET, RFREG_MASK, 0x0);
		rtw_ग_लिखो32(rtwdev, REG_NCTL0, 0x8 | (path << 1));
		अगर (rtwdev->dm_info.dpk_info.dpk_band == RTW_BAND_2G)
			rtw_ग_लिखो32(rtwdev, REG_DPD_CTL1_S1, 0x1f100000);
		अन्यथा
			rtw_ग_लिखो32(rtwdev, REG_DPD_CTL1_S1, 0x1f0d0000);
		rtw_ग_लिखो32_mask(rtwdev, REG_DPD_LUT0, BIT_GLOSS_DB, 0x4);
		rtw_ग_लिखो32_mask(rtwdev, REG_IQK_CTL1, BIT_TX_CFIR, 0x3);
	पूर्ण
	rtw_ग_लिखो32_mask(rtwdev, REG_NCTL0, BIT_SUBPAGE, 0xc);
	rtw_ग_लिखो32(rtwdev, REG_DPD_CTL11, 0x3b23170b);
	rtw_ग_लिखो32(rtwdev, REG_DPD_CTL12, 0x775f5347);
पूर्ण

अटल u32 rtw8822c_dpk_rf_setting(काष्ठा rtw_dev *rtwdev, u8 path)
अणु
	u32 ori_txbb;

	rtw_ग_लिखो_rf(rtwdev, path, RF_MODE_TRXAGC, RFREG_MASK, 0x50017);
	ori_txbb = rtw_पढ़ो_rf(rtwdev, path, RF_TX_GAIN, RFREG_MASK);

	rtw_ग_लिखो_rf(rtwdev, path, RF_DEBUG, BIT_DE_TX_GAIN, 0x1);
	rtw_ग_लिखो_rf(rtwdev, path, RF_DEBUG, BIT_DE_PWR_TRIM, 0x1);
	rtw_ग_लिखो_rf(rtwdev, path, RF_TX_GAIN_OFFSET, BIT_BB_GAIN, 0x0);
	rtw_ग_लिखो_rf(rtwdev, path, RF_TX_GAIN, RFREG_MASK, ori_txbb);

	अगर (rtwdev->dm_info.dpk_info.dpk_band == RTW_BAND_2G) अणु
		rtw_ग_लिखो_rf(rtwdev, path, RF_TX_GAIN_OFFSET, BIT_RF_GAIN, 0x1);
		rtw_ग_लिखो_rf(rtwdev, path, RF_RXG_GAIN, BIT_RXG_GAIN, 0x0);
	पूर्ण अन्यथा अणु
		rtw_ग_लिखो_rf(rtwdev, path, RF_TXA_LB_SW, BIT_TXA_LB_ATT, 0x0);
		rtw_ग_लिखो_rf(rtwdev, path, RF_TXA_LB_SW, BIT_LB_ATT, 0x6);
		rtw_ग_लिखो_rf(rtwdev, path, RF_TXA_LB_SW, BIT_LB_SW, 0x1);
		rtw_ग_लिखो_rf(rtwdev, path, RF_RXA_MIX_GAIN, BIT_RXA_MIX_GAIN, 0);
	पूर्ण

	rtw_ग_लिखो_rf(rtwdev, path, RF_MODE_TRXAGC, BIT_RXAGC, 0xf);
	rtw_ग_लिखो_rf(rtwdev, path, RF_DEBUG, BIT_DE_TRXBW, 0x1);
	rtw_ग_लिखो_rf(rtwdev, path, RF_BW_TRXBB, BIT_BW_RXBB, 0x0);

	अगर (rtwdev->dm_info.dpk_info.dpk_bw == DPK_CHANNEL_WIDTH_80)
		rtw_ग_लिखो_rf(rtwdev, path, RF_BW_TRXBB, BIT_BW_TXBB, 0x2);
	अन्यथा
		rtw_ग_लिखो_rf(rtwdev, path, RF_BW_TRXBB, BIT_BW_TXBB, 0x1);

	rtw_ग_लिखो_rf(rtwdev, path, RF_EXT_TIA_BW, BIT(1), 0x1);

	usleep_range(100, 110);

	वापस ori_txbb & 0x1f;
पूर्ण

अटल u16 rtw8822c_dpk_get_cmd(काष्ठा rtw_dev *rtwdev, u8 action, u8 path)
अणु
	u16 cmd;
	u8 bw = rtwdev->dm_info.dpk_info.dpk_bw == DPK_CHANNEL_WIDTH_80 ? 2 : 0;

	चयन (action) अणु
	हाल RTW_DPK_GAIN_LOSS:
		cmd = 0x14 + path;
		अवरोध;
	हाल RTW_DPK_DO_DPK:
		cmd = 0x16 + path + bw;
		अवरोध;
	हाल RTW_DPK_DPK_ON:
		cmd = 0x1a + path;
		अवरोध;
	हाल RTW_DPK_DAGC:
		cmd = 0x1c + path + bw;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस (cmd << 8) | 0x48;
पूर्ण

अटल u8 rtw8822c_dpk_one_shot(काष्ठा rtw_dev *rtwdev, u8 path, u8 action)
अणु
	u16 dpk_cmd;
	u8 result = 0;

	rtw8822c_dpk_set_gnt_wl(rtwdev, true);

	अगर (action == RTW_DPK_CAL_PWR) अणु
		rtw_ग_लिखो32_mask(rtwdev, REG_DPD_CTL0, BIT(12), 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_DPD_CTL0, BIT(12), 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_RXSRAM_CTL, BIT_RPT_SEL, 0x0);
		msleep(10);
		अगर (!check_hw_पढ़ोy(rtwdev, REG_STAT_RPT, BIT(31), 0x1)) अणु
			result = 1;
			rtw_dbg(rtwdev, RTW_DBG_RFK, "[DPK] one-shot over 20ms\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		rtw_ग_लिखो32_mask(rtwdev, REG_NCTL0, BIT_SUBPAGE,
				 0x8 | (path << 1));
		rtw_ग_लिखो32_mask(rtwdev, REG_R_CONFIG, BIT_IQ_SWITCH, 0x9);

		dpk_cmd = rtw8822c_dpk_get_cmd(rtwdev, action, path);
		rtw_ग_लिखो32(rtwdev, REG_NCTL0, dpk_cmd);
		rtw_ग_लिखो32(rtwdev, REG_NCTL0, dpk_cmd + 1);
		msleep(10);
		अगर (!check_hw_पढ़ोy(rtwdev, 0x2d9c, 0xff, 0x55)) अणु
			result = 1;
			rtw_dbg(rtwdev, RTW_DBG_RFK, "[DPK] one-shot over 20ms\n");
		पूर्ण
		rtw_ग_लिखो32_mask(rtwdev, REG_NCTL0, BIT_SUBPAGE,
				 0x8 | (path << 1));
		rtw_ग_लिखो32_mask(rtwdev, REG_R_CONFIG, BIT_IQ_SWITCH, 0x0);
	पूर्ण

	rtw8822c_dpk_set_gnt_wl(rtwdev, false);

	rtw_ग_लिखो8(rtwdev, 0x1b10, 0x0);

	वापस result;
पूर्ण

अटल u16 rtw8822c_dpk_dgain_पढ़ो(काष्ठा rtw_dev *rtwdev, u8 path)
अणु
	u16 dgain;

	rtw_ग_लिखो32_mask(rtwdev, REG_NCTL0, BIT_SUBPAGE, 0xc);
	rtw_ग_लिखो32_mask(rtwdev, REG_RXSRAM_CTL, 0x00ff0000, 0x0);

	dgain = (u16)rtw_पढ़ो32_mask(rtwdev, REG_STAT_RPT, GENMASK(27, 16));

	वापस dgain;
पूर्ण

अटल u8 rtw8822c_dpk_thermal_पढ़ो(काष्ठा rtw_dev *rtwdev, u8 path)
अणु
	rtw_ग_लिखो_rf(rtwdev, path, RF_T_METER, BIT(19), 0x1);
	rtw_ग_लिखो_rf(rtwdev, path, RF_T_METER, BIT(19), 0x0);
	rtw_ग_लिखो_rf(rtwdev, path, RF_T_METER, BIT(19), 0x1);
	udelay(15);

	वापस (u8)rtw_पढ़ो_rf(rtwdev, path, RF_T_METER, 0x0007e);
पूर्ण

अटल u32 rtw8822c_dpk_pas_पढ़ो(काष्ठा rtw_dev *rtwdev, u8 path)
अणु
	u32 i_val, q_val;

	rtw_ग_लिखो32(rtwdev, REG_NCTL0, 0x8 | (path << 1));
	rtw_ग_लिखो32_mask(rtwdev, 0x1b48, BIT(14), 0x0);
	rtw_ग_लिखो32(rtwdev, REG_RXSRAM_CTL, 0x00060001);
	rtw_ग_लिखो32(rtwdev, 0x1b4c, 0x00000000);
	rtw_ग_लिखो32(rtwdev, 0x1b4c, 0x00080000);

	q_val = rtw_पढ़ो32_mask(rtwdev, REG_STAT_RPT, MASKHWORD);
	i_val = rtw_पढ़ो32_mask(rtwdev, REG_STAT_RPT, MASKLWORD);

	अगर (i_val & BIT(15))
		i_val = 0x10000 - i_val;
	अगर (q_val & BIT(15))
		q_val = 0x10000 - q_val;

	rtw_ग_लिखो32(rtwdev, 0x1b4c, 0x00000000);

	वापस i_val * i_val + q_val * q_val;
पूर्ण

अटल u32 rtw8822c_psd_log2base(u32 val)
अणु
	u32 पंचांगp, val_पूर्णांकegerd_b, tindex;
	u32 result, val_fractiond_b;
	u32 table_fraction[21] = अणु0, 432, 332, 274, 232, 200, 174,
				  151, 132, 115, 100, 86, 74, 62, 51,
				  42, 32, 23, 15, 7, 0पूर्ण;

	अगर (val == 0)
		वापस 0;

	val_पूर्णांकegerd_b = __fls(val) + 1;

	पंचांगp = (val * 100) / (1 << val_पूर्णांकegerd_b);
	tindex = पंचांगp / 5;

	अगर (tindex >= ARRAY_SIZE(table_fraction))
		tindex = ARRAY_SIZE(table_fraction) - 1;

	val_fractiond_b = table_fraction[tindex];

	result = val_पूर्णांकegerd_b * 100 - val_fractiond_b;

	वापस result;
पूर्ण

अटल u8 rtw8822c_dpk_gainloss_result(काष्ठा rtw_dev *rtwdev, u8 path)
अणु
	u8 result;

	rtw_ग_लिखो32_mask(rtwdev, REG_NCTL0, BIT_SUBPAGE, 0x8 | (path << 1));
	rtw_ग_लिखो32_mask(rtwdev, 0x1b48, BIT(14), 0x1);
	rtw_ग_लिखो32(rtwdev, REG_RXSRAM_CTL, 0x00060000);

	result = (u8)rtw_पढ़ो32_mask(rtwdev, REG_STAT_RPT, 0x000000f0);

	rtw_ग_लिखो32_mask(rtwdev, 0x1b48, BIT(14), 0x0);

	वापस result;
पूर्ण

अटल u8 rtw8822c_dpk_agc_gain_chk(काष्ठा rtw_dev *rtwdev, u8 path,
				    u8 limited_pga)
अणु
	u8 result = 0;
	u16 dgain;

	rtw8822c_dpk_one_shot(rtwdev, path, RTW_DPK_DAGC);
	dgain = rtw8822c_dpk_dgain_पढ़ो(rtwdev, path);

	अगर (dgain > 1535 && !limited_pga)
		वापस RTW_DPK_GAIN_LESS;
	अन्यथा अगर (dgain < 768 && !limited_pga)
		वापस RTW_DPK_GAIN_LARGE;
	अन्यथा
		वापस result;
पूर्ण

अटल u8 rtw8822c_dpk_agc_loss_chk(काष्ठा rtw_dev *rtwdev, u8 path)
अणु
	u32 loss, loss_db;

	loss = rtw8822c_dpk_pas_पढ़ो(rtwdev, path);
	अगर (loss < 0x4000000)
		वापस RTW_DPK_GL_LESS;
	loss_db = 3 * rtw8822c_psd_log2base(loss >> 13) - 3870;

	अगर (loss_db > 1000)
		वापस RTW_DPK_GL_LARGE;
	अन्यथा अगर (loss_db < 250)
		वापस RTW_DPK_GL_LESS;
	अन्यथा
		वापस RTW_DPK_AGC_OUT;
पूर्ण

काष्ठा rtw8822c_dpk_data अणु
	u8 txbb;
	u8 pga;
	u8 limited_pga;
	u8 agc_cnt;
	bool loss_only;
	bool gain_only;
	u8 path;
पूर्ण;

अटल u8 rtw8822c_gain_check_state(काष्ठा rtw_dev *rtwdev,
				    काष्ठा rtw8822c_dpk_data *data)
अणु
	u8 state;

	data->txbb = (u8)rtw_पढ़ो_rf(rtwdev, data->path, RF_TX_GAIN,
				     BIT_GAIN_TXBB);
	data->pga = (u8)rtw_पढ़ो_rf(rtwdev, data->path, RF_MODE_TRXAGC,
				    BIT_RXAGC);

	अगर (data->loss_only) अणु
		state = RTW_DPK_LOSS_CHECK;
		जाओ check_end;
	पूर्ण

	state = rtw8822c_dpk_agc_gain_chk(rtwdev, data->path,
					  data->limited_pga);
	अगर (state == RTW_DPK_GAIN_CHECK && data->gain_only)
		state = RTW_DPK_AGC_OUT;
	अन्यथा अगर (state == RTW_DPK_GAIN_CHECK)
		state = RTW_DPK_LOSS_CHECK;

check_end:
	data->agc_cnt++;
	अगर (data->agc_cnt >= 6)
		state = RTW_DPK_AGC_OUT;

	वापस state;
पूर्ण

अटल u8 rtw8822c_gain_large_state(काष्ठा rtw_dev *rtwdev,
				    काष्ठा rtw8822c_dpk_data *data)
अणु
	u8 pga = data->pga;

	अगर (pga > 0xe)
		rtw_ग_लिखो_rf(rtwdev, data->path, RF_MODE_TRXAGC, BIT_RXAGC, 0xc);
	अन्यथा अगर (pga > 0xb && pga < 0xf)
		rtw_ग_लिखो_rf(rtwdev, data->path, RF_MODE_TRXAGC, BIT_RXAGC, 0x0);
	अन्यथा अगर (pga < 0xc)
		data->limited_pga = 1;

	वापस RTW_DPK_GAIN_CHECK;
पूर्ण

अटल u8 rtw8822c_gain_less_state(काष्ठा rtw_dev *rtwdev,
				   काष्ठा rtw8822c_dpk_data *data)
अणु
	u8 pga = data->pga;

	अगर (pga < 0xc)
		rtw_ग_लिखो_rf(rtwdev, data->path, RF_MODE_TRXAGC, BIT_RXAGC, 0xc);
	अन्यथा अगर (pga > 0xb && pga < 0xf)
		rtw_ग_लिखो_rf(rtwdev, data->path, RF_MODE_TRXAGC, BIT_RXAGC, 0xf);
	अन्यथा अगर (pga > 0xe)
		data->limited_pga = 1;

	वापस RTW_DPK_GAIN_CHECK;
पूर्ण

अटल u8 rtw8822c_gl_state(काष्ठा rtw_dev *rtwdev,
			    काष्ठा rtw8822c_dpk_data *data, u8 is_large)
अणु
	u8 txbb_bound[] = अणु0x1f, 0पूर्ण;

	अगर (data->txbb == txbb_bound[is_large])
		वापस RTW_DPK_AGC_OUT;

	अगर (is_large == 1)
		data->txbb -= 2;
	अन्यथा
		data->txbb += 3;

	rtw_ग_लिखो_rf(rtwdev, data->path, RF_TX_GAIN, BIT_GAIN_TXBB, data->txbb);
	data->limited_pga = 0;

	वापस RTW_DPK_GAIN_CHECK;
पूर्ण

अटल u8 rtw8822c_gl_large_state(काष्ठा rtw_dev *rtwdev,
				  काष्ठा rtw8822c_dpk_data *data)
अणु
	वापस rtw8822c_gl_state(rtwdev, data, 1);
पूर्ण

अटल u8 rtw8822c_gl_less_state(काष्ठा rtw_dev *rtwdev,
				 काष्ठा rtw8822c_dpk_data *data)
अणु
	वापस rtw8822c_gl_state(rtwdev, data, 0);
पूर्ण

अटल u8 rtw8822c_loss_check_state(काष्ठा rtw_dev *rtwdev,
				    काष्ठा rtw8822c_dpk_data *data)
अणु
	u8 path = data->path;
	u8 state;

	rtw8822c_dpk_one_shot(rtwdev, path, RTW_DPK_GAIN_LOSS);
	state = rtw8822c_dpk_agc_loss_chk(rtwdev, path);

	वापस state;
पूर्ण

अटल u8 (*dpk_state[])(काष्ठा rtw_dev *rtwdev,
			  काष्ठा rtw8822c_dpk_data *data) = अणु
	rtw8822c_gain_check_state, rtw8822c_gain_large_state,
	rtw8822c_gain_less_state, rtw8822c_gl_large_state,
	rtw8822c_gl_less_state, rtw8822c_loss_check_state पूर्ण;

अटल u8 rtw8822c_dpk_pas_agc(काष्ठा rtw_dev *rtwdev, u8 path,
			       bool gain_only, bool loss_only)
अणु
	काष्ठा rtw8822c_dpk_data data = अणु0पूर्ण;
	u8 (*func)(काष्ठा rtw_dev *rtwdev, काष्ठा rtw8822c_dpk_data *data);
	u8 state = RTW_DPK_GAIN_CHECK;

	data.loss_only = loss_only;
	data.gain_only = gain_only;
	data.path = path;

	क्रम (;;) अणु
		func = dpk_state[state];
		state = func(rtwdev, &data);
		अगर (state == RTW_DPK_AGC_OUT)
			अवरोध;
	पूर्ण

	वापस data.txbb;
पूर्ण

अटल bool rtw8822c_dpk_coef_iq_check(काष्ठा rtw_dev *rtwdev,
				       u16 coef_i, u16 coef_q)
अणु
	अगर (coef_i == 0x1000 || coef_i == 0x0fff ||
	    coef_q == 0x1000 || coef_q == 0x0fff)
		वापस true;

	वापस false;
पूर्ण

अटल u32 rtw8822c_dpk_coef_transfer(काष्ठा rtw_dev *rtwdev)
अणु
	u32 reg = 0;
	u16 coef_i = 0, coef_q = 0;

	reg = rtw_पढ़ो32(rtwdev, REG_STAT_RPT);

	coef_i = (u16)rtw_पढ़ो32_mask(rtwdev, REG_STAT_RPT, MASKHWORD) & 0x1fff;
	coef_q = (u16)rtw_पढ़ो32_mask(rtwdev, REG_STAT_RPT, MASKLWORD) & 0x1fff;

	coef_q = ((0x2000 - coef_q) & 0x1fff) - 1;

	reg = (coef_i << 16) | coef_q;

	वापस reg;
पूर्ण

अटल स्थिर u32 rtw8822c_dpk_get_coef_tbl[] = अणु
	0x000400f0, 0x040400f0, 0x080400f0, 0x010400f0, 0x050400f0,
	0x090400f0, 0x020400f0, 0x060400f0, 0x0a0400f0, 0x030400f0,
	0x070400f0, 0x0b0400f0, 0x0c0400f0, 0x100400f0, 0x0d0400f0,
	0x110400f0, 0x0e0400f0, 0x120400f0, 0x0f0400f0, 0x130400f0,
पूर्ण;

अटल व्योम rtw8822c_dpk_coef_tbl_apply(काष्ठा rtw_dev *rtwdev, u8 path)
अणु
	काष्ठा rtw_dpk_info *dpk_info = &rtwdev->dm_info.dpk_info;
	पूर्णांक i;

	क्रम (i = 0; i < 20; i++) अणु
		rtw_ग_लिखो32(rtwdev, REG_RXSRAM_CTL,
			    rtw8822c_dpk_get_coef_tbl[i]);
		dpk_info->coef[path][i] = rtw8822c_dpk_coef_transfer(rtwdev);
	पूर्ण
पूर्ण

अटल व्योम rtw8822c_dpk_get_coef(काष्ठा rtw_dev *rtwdev, u8 path)
अणु
	rtw_ग_लिखो32(rtwdev, REG_NCTL0, 0x0000000c);

	अगर (path == RF_PATH_A) अणु
		rtw_ग_लिखो32_mask(rtwdev, REG_DPD_CTL0, BIT(24), 0x0);
		rtw_ग_लिखो32(rtwdev, REG_DPD_CTL0_S0, 0x30000080);
	पूर्ण अन्यथा अगर (path == RF_PATH_B) अणु
		rtw_ग_लिखो32_mask(rtwdev, REG_DPD_CTL0, BIT(24), 0x1);
		rtw_ग_लिखो32(rtwdev, REG_DPD_CTL0_S1, 0x30000080);
	पूर्ण

	rtw8822c_dpk_coef_tbl_apply(rtwdev, path);
पूर्ण

अटल u8 rtw8822c_dpk_coef_पढ़ो(काष्ठा rtw_dev *rtwdev, u8 path)
अणु
	काष्ठा rtw_dpk_info *dpk_info = &rtwdev->dm_info.dpk_info;
	u8 addr, result = 1;
	u16 coef_i, coef_q;

	क्रम (addr = 0; addr < 20; addr++) अणु
		coef_i = FIELD_GET(0x1fff0000, dpk_info->coef[path][addr]);
		coef_q = FIELD_GET(0x1fff, dpk_info->coef[path][addr]);

		अगर (rtw8822c_dpk_coef_iq_check(rtwdev, coef_i, coef_q)) अणु
			result = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस result;
पूर्ण

अटल व्योम rtw8822c_dpk_coef_ग_लिखो(काष्ठा rtw_dev *rtwdev, u8 path, u8 result)
अणु
	काष्ठा rtw_dpk_info *dpk_info = &rtwdev->dm_info.dpk_info;
	u16 reg[DPK_RF_PATH_NUM] = अणु0x1b0c, 0x1b64पूर्ण;
	u32 coef;
	u8 addr;

	rtw_ग_लिखो32(rtwdev, REG_NCTL0, 0x0000000c);
	rtw_ग_लिखो32(rtwdev, REG_RXSRAM_CTL, 0x000000f0);

	क्रम (addr = 0; addr < 20; addr++) अणु
		अगर (result == 0) अणु
			अगर (addr == 3)
				coef = 0x04001fff;
			अन्यथा
				coef = 0x00001fff;
		पूर्ण अन्यथा अणु
			coef = dpk_info->coef[path][addr];
		पूर्ण
		rtw_ग_लिखो32(rtwdev, reg[path] + addr * 4, coef);
	पूर्ण
पूर्ण

अटल व्योम rtw8822c_dpk_fill_result(काष्ठा rtw_dev *rtwdev, u32 dpk_txagc,
				     u8 path, u8 result)
अणु
	काष्ठा rtw_dpk_info *dpk_info = &rtwdev->dm_info.dpk_info;

	rtw_ग_लिखो32_mask(rtwdev, REG_NCTL0, BIT_SUBPAGE, 0x8 | (path << 1));

	अगर (result)
		rtw_ग_लिखो8(rtwdev, REG_DPD_AGC, (u8)(dpk_txagc - 6));
	अन्यथा
		rtw_ग_लिखो8(rtwdev, REG_DPD_AGC, 0x00);

	dpk_info->result[path] = result;
	dpk_info->dpk_txagc[path] = rtw_पढ़ो8(rtwdev, REG_DPD_AGC);

	rtw8822c_dpk_coef_ग_लिखो(rtwdev, path, result);
पूर्ण

अटल u32 rtw8822c_dpk_gainloss(काष्ठा rtw_dev *rtwdev, u8 path)
अणु
	काष्ठा rtw_dpk_info *dpk_info = &rtwdev->dm_info.dpk_info;
	u8 tx_agc, tx_bb, ori_txbb, ori_txagc, tx_agc_search, t1, t2;

	ori_txbb = rtw8822c_dpk_rf_setting(rtwdev, path);
	ori_txagc = (u8)rtw_पढ़ो_rf(rtwdev, path, RF_MODE_TRXAGC, BIT_TXAGC);

	rtw8822c_dpk_rxbb_dc_cal(rtwdev, path);
	rtw8822c_dpk_one_shot(rtwdev, path, RTW_DPK_DAGC);
	rtw8822c_dpk_dgain_पढ़ो(rtwdev, path);

	अगर (rtw8822c_dpk_dc_corr_check(rtwdev, path)) अणु
		rtw8822c_dpk_rxbb_dc_cal(rtwdev, path);
		rtw8822c_dpk_one_shot(rtwdev, path, RTW_DPK_DAGC);
		rtw8822c_dpk_dc_corr_check(rtwdev, path);
	पूर्ण

	t1 = rtw8822c_dpk_thermal_पढ़ो(rtwdev, path);
	tx_bb = rtw8822c_dpk_pas_agc(rtwdev, path, false, true);
	tx_agc_search = rtw8822c_dpk_gainloss_result(rtwdev, path);

	अगर (tx_bb < tx_agc_search)
		tx_bb = 0;
	अन्यथा
		tx_bb = tx_bb - tx_agc_search;

	rtw_ग_लिखो_rf(rtwdev, path, RF_TX_GAIN, BIT_GAIN_TXBB, tx_bb);

	tx_agc = ori_txagc - (ori_txbb - tx_bb);

	t2 = rtw8822c_dpk_thermal_पढ़ो(rtwdev, path);

	dpk_info->thermal_dpk_delta[path] = असल(t2 - t1);

	वापस tx_agc;
पूर्ण

अटल u8 rtw8822c_dpk_by_path(काष्ठा rtw_dev *rtwdev, u32 tx_agc, u8 path)
अणु
	u8 result;

	result = rtw8822c_dpk_one_shot(rtwdev, path, RTW_DPK_DO_DPK);

	rtw_ग_लिखो32_mask(rtwdev, REG_NCTL0, BIT_SUBPAGE, 0x8 | (path << 1));

	result = result | (u8)rtw_पढ़ो32_mask(rtwdev, REG_DPD_CTL1_S0, BIT(26));

	rtw_ग_लिखो_rf(rtwdev, path, RF_MODE_TRXAGC, RFREG_MASK, 0x33e14);

	rtw8822c_dpk_get_coef(rtwdev, path);

	वापस result;
पूर्ण

अटल व्योम rtw8822c_dpk_cal_gs(काष्ठा rtw_dev *rtwdev, u8 path)
अणु
	काष्ठा rtw_dpk_info *dpk_info = &rtwdev->dm_info.dpk_info;
	u32 पंचांगp_gs = 0;

	rtw_ग_लिखो32_mask(rtwdev, REG_NCTL0, BIT_SUBPAGE, 0x8 | (path << 1));
	rtw_ग_लिखो32_mask(rtwdev, REG_IQK_CTL1, BIT_BYPASS_DPD, 0x0);
	rtw_ग_लिखो32_mask(rtwdev, REG_IQK_CTL1, BIT_TX_CFIR, 0x0);
	rtw_ग_लिखो32_mask(rtwdev, REG_R_CONFIG, BIT_IQ_SWITCH, 0x9);
	rtw_ग_लिखो32_mask(rtwdev, REG_R_CONFIG, BIT_INNER_LB, 0x1);
	rtw_ग_लिखो32_mask(rtwdev, REG_NCTL0, BIT_SUBPAGE, 0xc);
	rtw_ग_लिखो32_mask(rtwdev, REG_RXSRAM_CTL, BIT_DPD_CLK, 0xf);

	अगर (path == RF_PATH_A) अणु
		rtw_ग_लिखो32_mask(rtwdev, REG_DPD_CTL0_S0, BIT_GS_PWSF,
				 0x1066680);
		rtw_ग_लिखो32_mask(rtwdev, REG_DPD_CTL1_S0, BIT_DPD_EN, 0x1);
	पूर्ण अन्यथा अणु
		rtw_ग_लिखो32_mask(rtwdev, REG_DPD_CTL0_S1, BIT_GS_PWSF,
				 0x1066680);
		rtw_ग_लिखो32_mask(rtwdev, REG_DPD_CTL1_S1, BIT_DPD_EN, 0x1);
	पूर्ण

	अगर (dpk_info->dpk_bw == DPK_CHANNEL_WIDTH_80) अणु
		rtw_ग_लिखो32(rtwdev, REG_DPD_CTL16, 0x80001310);
		rtw_ग_लिखो32(rtwdev, REG_DPD_CTL16, 0x00001310);
		rtw_ग_लिखो32(rtwdev, REG_DPD_CTL16, 0x810000db);
		rtw_ग_लिखो32(rtwdev, REG_DPD_CTL16, 0x010000db);
		rtw_ग_लिखो32(rtwdev, REG_DPD_CTL16, 0x0000b428);
		rtw_ग_लिखो32(rtwdev, REG_DPD_CTL15,
			    0x05020000 | (BIT(path) << 28));
	पूर्ण अन्यथा अणु
		rtw_ग_लिखो32(rtwdev, REG_DPD_CTL16, 0x8200190c);
		rtw_ग_लिखो32(rtwdev, REG_DPD_CTL16, 0x0200190c);
		rtw_ग_लिखो32(rtwdev, REG_DPD_CTL16, 0x8301ee14);
		rtw_ग_लिखो32(rtwdev, REG_DPD_CTL16, 0x0301ee14);
		rtw_ग_लिखो32(rtwdev, REG_DPD_CTL16, 0x0000b428);
		rtw_ग_लिखो32(rtwdev, REG_DPD_CTL15,
			    0x05020008 | (BIT(path) << 28));
	पूर्ण

	rtw_ग_लिखो32_mask(rtwdev, REG_DPD_CTL0, MASKBYTE3, 0x8 | path);

	rtw8822c_dpk_one_shot(rtwdev, path, RTW_DPK_CAL_PWR);

	rtw_ग_लिखो32_mask(rtwdev, REG_DPD_CTL15, MASKBYTE3, 0x0);
	rtw_ग_लिखो32_mask(rtwdev, REG_NCTL0, BIT_SUBPAGE, 0x8 | (path << 1));
	rtw_ग_लिखो32_mask(rtwdev, REG_R_CONFIG, BIT_IQ_SWITCH, 0x0);
	rtw_ग_लिखो32_mask(rtwdev, REG_R_CONFIG, BIT_INNER_LB, 0x0);
	rtw_ग_लिखो32_mask(rtwdev, REG_NCTL0, BIT_SUBPAGE, 0xc);

	अगर (path == RF_PATH_A)
		rtw_ग_लिखो32_mask(rtwdev, REG_DPD_CTL0_S0, BIT_GS_PWSF, 0x5b);
	अन्यथा
		rtw_ग_लिखो32_mask(rtwdev, REG_DPD_CTL0_S1, BIT_GS_PWSF, 0x5b);

	rtw_ग_लिखो32_mask(rtwdev, REG_RXSRAM_CTL, BIT_RPT_SEL, 0x0);

	पंचांगp_gs = (u16)rtw_पढ़ो32_mask(rtwdev, REG_STAT_RPT, BIT_RPT_DGAIN);
	पंचांगp_gs = (पंचांगp_gs * 910) >> 10;
	पंचांगp_gs = DIV_ROUND_CLOSEST(पंचांगp_gs, 10);

	अगर (path == RF_PATH_A)
		rtw_ग_लिखो32_mask(rtwdev, REG_DPD_CTL0_S0, BIT_GS_PWSF, पंचांगp_gs);
	अन्यथा
		rtw_ग_लिखो32_mask(rtwdev, REG_DPD_CTL0_S1, BIT_GS_PWSF, पंचांगp_gs);

	dpk_info->dpk_gs[path] = पंचांगp_gs;
पूर्ण

अटल व्योम rtw8822c_dpk_cal_coef1(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dpk_info *dpk_info = &rtwdev->dm_info.dpk_info;
	u32 offset[DPK_RF_PATH_NUM] = अणु0, 0x58पूर्ण;
	u32 i_scaling;
	u8 path;

	rtw_ग_लिखो32_mask(rtwdev, REG_NCTL0, BIT_SUBPAGE, 0x0000000c);
	rtw_ग_लिखो32(rtwdev, REG_RXSRAM_CTL, 0x000000f0);
	rtw_ग_लिखो32(rtwdev, REG_NCTL0, 0x00001148);
	rtw_ग_लिखो32(rtwdev, REG_NCTL0, 0x00001149);

	check_hw_पढ़ोy(rtwdev, 0x2d9c, MASKBYTE0, 0x55);

	rtw_ग_लिखो8(rtwdev, 0x1b10, 0x0);
	rtw_ग_लिखो32_mask(rtwdev, REG_NCTL0, BIT_SUBPAGE, 0x0000000c);

	क्रम (path = 0; path < rtwdev->hal.rf_path_num; path++) अणु
		i_scaling = 0x16c00 / dpk_info->dpk_gs[path];

		rtw_ग_लिखो32_mask(rtwdev, 0x1b18 + offset[path], MASKHWORD,
				 i_scaling);
		rtw_ग_लिखो32_mask(rtwdev, REG_DPD_CTL0_S0 + offset[path],
				 GENMASK(31, 28), 0x9);
		rtw_ग_लिखो32_mask(rtwdev, REG_DPD_CTL0_S0 + offset[path],
				 GENMASK(31, 28), 0x1);
		rtw_ग_लिखो32_mask(rtwdev, REG_DPD_CTL0_S0 + offset[path],
				 GENMASK(31, 28), 0x0);
		rtw_ग_लिखो32_mask(rtwdev, REG_DPD_CTL1_S0 + offset[path],
				 BIT(14), 0x0);
	पूर्ण
पूर्ण

अटल व्योम rtw8822c_dpk_on(काष्ठा rtw_dev *rtwdev, u8 path)
अणु
	काष्ठा rtw_dpk_info *dpk_info = &rtwdev->dm_info.dpk_info;

	rtw8822c_dpk_one_shot(rtwdev, path, RTW_DPK_DPK_ON);

	rtw_ग_लिखो32_mask(rtwdev, REG_NCTL0, BIT_SUBPAGE, 0x8 | (path << 1));
	rtw_ग_लिखो32_mask(rtwdev, REG_IQK_CTL1, BIT_TX_CFIR, 0x0);

	अगर (test_bit(path, dpk_info->dpk_path_ok))
		rtw8822c_dpk_cal_gs(rtwdev, path);
पूर्ण

अटल bool rtw8822c_dpk_check_pass(काष्ठा rtw_dev *rtwdev, bool is_fail,
				    u32 dpk_txagc, u8 path)
अणु
	bool result;

	अगर (!is_fail) अणु
		अगर (rtw8822c_dpk_coef_पढ़ो(rtwdev, path))
			result = true;
		अन्यथा
			result = false;
	पूर्ण अन्यथा अणु
		result = false;
	पूर्ण

	rtw8822c_dpk_fill_result(rtwdev, dpk_txagc, path, result);

	वापस result;
पूर्ण

अटल व्योम rtw8822c_dpk_result_reset(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dpk_info *dpk_info = &rtwdev->dm_info.dpk_info;
	u8 path;

	क्रम (path = 0; path < rtwdev->hal.rf_path_num; path++) अणु
		clear_bit(path, dpk_info->dpk_path_ok);
		rtw_ग_लिखो32_mask(rtwdev, REG_NCTL0, BIT_SUBPAGE,
				 0x8 | (path << 1));
		rtw_ग_लिखो32_mask(rtwdev, 0x1b58, 0x0000007f, 0x0);

		dpk_info->dpk_txagc[path] = 0;
		dpk_info->result[path] = 0;
		dpk_info->dpk_gs[path] = 0x5b;
		dpk_info->pre_pwsf[path] = 0;
		dpk_info->thermal_dpk[path] = rtw8822c_dpk_thermal_पढ़ो(rtwdev,
									path);
	पूर्ण
पूर्ण

अटल व्योम rtw8822c_dpk_calibrate(काष्ठा rtw_dev *rtwdev, u8 path)
अणु
	काष्ठा rtw_dpk_info *dpk_info = &rtwdev->dm_info.dpk_info;
	u32 dpk_txagc;
	u8 dpk_fail;

	rtw_dbg(rtwdev, RTW_DBG_RFK, "[DPK] s%d dpk start\n", path);

	dpk_txagc = rtw8822c_dpk_gainloss(rtwdev, path);

	dpk_fail = rtw8822c_dpk_by_path(rtwdev, dpk_txagc, path);

	अगर (!rtw8822c_dpk_check_pass(rtwdev, dpk_fail, dpk_txagc, path))
		rtw_err(rtwdev, "failed to do dpk calibration\n");

	rtw_dbg(rtwdev, RTW_DBG_RFK, "[DPK] s%d dpk finish\n", path);

	अगर (dpk_info->result[path])
		set_bit(path, dpk_info->dpk_path_ok);
पूर्ण

अटल व्योम rtw8822c_dpk_path_select(काष्ठा rtw_dev *rtwdev)
अणु
	rtw8822c_dpk_calibrate(rtwdev, RF_PATH_A);
	rtw8822c_dpk_calibrate(rtwdev, RF_PATH_B);
	rtw8822c_dpk_on(rtwdev, RF_PATH_A);
	rtw8822c_dpk_on(rtwdev, RF_PATH_B);
	rtw8822c_dpk_cal_coef1(rtwdev);
पूर्ण

अटल व्योम rtw8822c_dpk_enable_disable(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dpk_info *dpk_info = &rtwdev->dm_info.dpk_info;
	u32 mask = BIT(15) | BIT(14);

	rtw_ग_लिखो32_mask(rtwdev, REG_NCTL0, BIT_SUBPAGE, 0xc);

	rtw_ग_लिखो32_mask(rtwdev, REG_DPD_CTL1_S0, BIT_DPD_EN,
			 dpk_info->is_dpk_pwr_on);
	rtw_ग_लिखो32_mask(rtwdev, REG_DPD_CTL1_S1, BIT_DPD_EN,
			 dpk_info->is_dpk_pwr_on);

	अगर (test_bit(RF_PATH_A, dpk_info->dpk_path_ok)) अणु
		rtw_ग_लिखो32_mask(rtwdev, REG_DPD_CTL1_S0, mask, 0x0);
		rtw_ग_लिखो8(rtwdev, REG_DPD_CTL0_S0, dpk_info->dpk_gs[RF_PATH_A]);
	पूर्ण
	अगर (test_bit(RF_PATH_B, dpk_info->dpk_path_ok)) अणु
		rtw_ग_लिखो32_mask(rtwdev, REG_DPD_CTL1_S1, mask, 0x0);
		rtw_ग_लिखो8(rtwdev, REG_DPD_CTL0_S1, dpk_info->dpk_gs[RF_PATH_B]);
	पूर्ण
पूर्ण

अटल व्योम rtw8822c_dpk_reload_data(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dpk_info *dpk_info = &rtwdev->dm_info.dpk_info;
	u8 path;

	अगर (!test_bit(RF_PATH_A, dpk_info->dpk_path_ok) &&
	    !test_bit(RF_PATH_B, dpk_info->dpk_path_ok) &&
	    dpk_info->dpk_ch == 0)
		वापस;

	क्रम (path = 0; path < rtwdev->hal.rf_path_num; path++) अणु
		rtw_ग_लिखो32_mask(rtwdev, REG_NCTL0, BIT_SUBPAGE,
				 0x8 | (path << 1));
		अगर (dpk_info->dpk_band == RTW_BAND_2G)
			rtw_ग_लिखो32(rtwdev, REG_DPD_CTL1_S1, 0x1f100000);
		अन्यथा
			rtw_ग_लिखो32(rtwdev, REG_DPD_CTL1_S1, 0x1f0d0000);

		rtw_ग_लिखो8(rtwdev, REG_DPD_AGC, dpk_info->dpk_txagc[path]);

		rtw8822c_dpk_coef_ग_लिखो(rtwdev, path,
					test_bit(path, dpk_info->dpk_path_ok));

		rtw8822c_dpk_one_shot(rtwdev, path, RTW_DPK_DPK_ON);

		rtw_ग_लिखो32_mask(rtwdev, REG_NCTL0, BIT_SUBPAGE, 0xc);

		अगर (path == RF_PATH_A)
			rtw_ग_लिखो32_mask(rtwdev, REG_DPD_CTL0_S0, BIT_GS_PWSF,
					 dpk_info->dpk_gs[path]);
		अन्यथा
			rtw_ग_लिखो32_mask(rtwdev, REG_DPD_CTL0_S1, BIT_GS_PWSF,
					 dpk_info->dpk_gs[path]);
	पूर्ण
	rtw8822c_dpk_cal_coef1(rtwdev);
पूर्ण

अटल bool rtw8822c_dpk_reload(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dpk_info *dpk_info = &rtwdev->dm_info.dpk_info;
	u8 channel;

	dpk_info->is_reload = false;

	channel = (u8)(rtw_पढ़ो_rf(rtwdev, RF_PATH_A, 0x18, RFREG_MASK) & 0xff);

	अगर (channel == dpk_info->dpk_ch) अणु
		rtw_dbg(rtwdev, RTW_DBG_RFK,
			"[DPK] DPK reload for CH%d!!\n", dpk_info->dpk_ch);
		rtw8822c_dpk_reload_data(rtwdev);
		dpk_info->is_reload = true;
	पूर्ण

	वापस dpk_info->is_reload;
पूर्ण

अटल व्योम rtw8822c_करो_dpk(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dpk_info *dpk_info = &rtwdev->dm_info.dpk_info;
	काष्ठा rtw_backup_info bckp[DPK_BB_REG_NUM];
	u32 rf_reg_backup[DPK_RF_REG_NUM][DPK_RF_PATH_NUM];
	u32 bb_reg[DPK_BB_REG_NUM] = अणु
		0x520, 0x820, 0x824, 0x1c3c, 0x1d58, 0x1864,
		0x4164, 0x180c, 0x410c, 0x186c, 0x416c,
		0x1a14, 0x1e70, 0x80c, 0x1d70, 0x1e7c, 0x18a4, 0x41a4पूर्ण;
	u32 rf_reg[DPK_RF_REG_NUM] = अणु
		0x0, 0x1a, 0x55, 0x63, 0x87, 0x8f, 0xdeपूर्ण;
	u8 path;

	अगर (!dpk_info->is_dpk_pwr_on) अणु
		rtw_dbg(rtwdev, RTW_DBG_RFK, "[DPK] Skip DPK due to DPD PWR off\n");
		वापस;
	पूर्ण अन्यथा अगर (rtw8822c_dpk_reload(rtwdev)) अणु
		वापस;
	पूर्ण

	क्रम (path = RF_PATH_A; path < DPK_RF_PATH_NUM; path++)
		ewma_thermal_init(&dpk_info->avg_thermal[path]);

	rtw8822c_dpk_inक्रमmation(rtwdev);

	rtw8822c_dpk_backup_रेजिस्टरs(rtwdev, bb_reg, DPK_BB_REG_NUM, bckp);
	rtw8822c_dpk_backup_rf_रेजिस्टरs(rtwdev, rf_reg, rf_reg_backup);

	rtw8822c_dpk_mac_bb_setting(rtwdev);
	rtw8822c_dpk_afe_setting(rtwdev, true);
	rtw8822c_dpk_pre_setting(rtwdev);
	rtw8822c_dpk_result_reset(rtwdev);
	rtw8822c_dpk_path_select(rtwdev);
	rtw8822c_dpk_afe_setting(rtwdev, false);
	rtw8822c_dpk_enable_disable(rtwdev);

	rtw8822c_dpk_reload_rf_रेजिस्टरs(rtwdev, rf_reg, rf_reg_backup);
	क्रम (path = 0; path < rtwdev->hal.rf_path_num; path++)
		rtw8822c_dpk_rxbb_dc_cal(rtwdev, path);
	rtw8822c_dpk_restore_रेजिस्टरs(rtwdev, DPK_BB_REG_NUM, bckp);
पूर्ण

अटल व्योम rtw8822c_phy_calibration(काष्ठा rtw_dev *rtwdev)
अणु
	rtw8822c_rfk_घातer_save(rtwdev, false);
	rtw8822c_करो_gapk(rtwdev);
	rtw8822c_करो_iqk(rtwdev);
	rtw8822c_करो_dpk(rtwdev);
	rtw8822c_rfk_घातer_save(rtwdev, true);
पूर्ण

अटल व्योम rtw8822c_dpk_track(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dpk_info *dpk_info = &rtwdev->dm_info.dpk_info;
	u8 path;
	u8 thermal_value[DPK_RF_PATH_NUM] = अणु0पूर्ण;
	s8 offset[DPK_RF_PATH_NUM], delta_dpk[DPK_RF_PATH_NUM];

	अगर (dpk_info->thermal_dpk[0] == 0 && dpk_info->thermal_dpk[1] == 0)
		वापस;

	क्रम (path = 0; path < DPK_RF_PATH_NUM; path++) अणु
		thermal_value[path] = rtw8822c_dpk_thermal_पढ़ो(rtwdev, path);
		ewma_thermal_add(&dpk_info->avg_thermal[path],
				 thermal_value[path]);
		thermal_value[path] =
			ewma_thermal_पढ़ो(&dpk_info->avg_thermal[path]);
		delta_dpk[path] = dpk_info->thermal_dpk[path] -
				  thermal_value[path];
		offset[path] = delta_dpk[path] -
			       dpk_info->thermal_dpk_delta[path];
		offset[path] &= 0x7f;

		अगर (offset[path] != dpk_info->pre_pwsf[path]) अणु
			rtw_ग_लिखो32_mask(rtwdev, REG_NCTL0, BIT_SUBPAGE,
					 0x8 | (path << 1));
			rtw_ग_लिखो32_mask(rtwdev, 0x1b58, GENMASK(6, 0),
					 offset[path]);
			dpk_info->pre_pwsf[path] = offset[path];
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा XCAP_EXTEND(val) (अणुtypeof(val) _v = (val); _v | _v << 7; पूर्ण)
अटल व्योम rtw8822c_set_crystal_cap_reg(काष्ठा rtw_dev *rtwdev, u8 crystal_cap)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	काष्ठा rtw_cfo_track *cfo = &dm_info->cfo_track;
	u32 val = 0;

	val = XCAP_EXTEND(crystal_cap);
	cfo->crystal_cap = crystal_cap;
	rtw_ग_लिखो32_mask(rtwdev, REG_ANAPAR_XTAL_0, BIT_XCAP_0, val);
पूर्ण

अटल व्योम rtw8822c_set_crystal_cap(काष्ठा rtw_dev *rtwdev, u8 crystal_cap)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	काष्ठा rtw_cfo_track *cfo = &dm_info->cfo_track;

	अगर (cfo->crystal_cap == crystal_cap)
		वापस;

	rtw8822c_set_crystal_cap_reg(rtwdev, crystal_cap);
पूर्ण

अटल व्योम rtw8822c_cfo_tracking_reset(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	काष्ठा rtw_cfo_track *cfo = &dm_info->cfo_track;

	cfo->is_adjust = true;

	अगर (cfo->crystal_cap > rtwdev->efuse.crystal_cap)
		rtw8822c_set_crystal_cap(rtwdev, cfo->crystal_cap - 1);
	अन्यथा अगर (cfo->crystal_cap < rtwdev->efuse.crystal_cap)
		rtw8822c_set_crystal_cap(rtwdev, cfo->crystal_cap + 1);
पूर्ण

अटल व्योम rtw8822c_cfo_init(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	काष्ठा rtw_cfo_track *cfo = &dm_info->cfo_track;

	cfo->crystal_cap = rtwdev->efuse.crystal_cap;
	cfo->is_adjust = true;
पूर्ण

#घोषणा REPORT_TO_KHZ(val) (अणुtypeof(val) _v = (val); (_v << 1) + (_v >> 1); पूर्ण)
अटल s32 rtw8822c_cfo_calc_avg(काष्ठा rtw_dev *rtwdev, u8 path_num)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	काष्ठा rtw_cfo_track *cfo = &dm_info->cfo_track;
	s32 cfo_avg, cfo_path_sum = 0, cfo_rpt_sum;
	u8 i;

	क्रम (i = 0; i < path_num; i++) अणु
		cfo_rpt_sum = REPORT_TO_KHZ(cfo->cfo_tail[i]);

		अगर (cfo->cfo_cnt[i])
			cfo_avg = cfo_rpt_sum / cfo->cfo_cnt[i];
		अन्यथा
			cfo_avg = 0;

		cfo_path_sum += cfo_avg;
	पूर्ण

	क्रम (i = 0; i < path_num; i++) अणु
		cfo->cfo_tail[i] = 0;
		cfo->cfo_cnt[i] = 0;
	पूर्ण

	वापस cfo_path_sum / path_num;
पूर्ण

अटल व्योम rtw8822c_cfo_need_adjust(काष्ठा rtw_dev *rtwdev, s32 cfo_avg)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	काष्ठा rtw_cfo_track *cfo = &dm_info->cfo_track;

	अगर (!cfo->is_adjust) अणु
		अगर (असल(cfo_avg) > CFO_TRK_ENABLE_TH)
			cfo->is_adjust = true;
	पूर्ण अन्यथा अणु
		अगर (असल(cfo_avg) <= CFO_TRK_STOP_TH)
			cfo->is_adjust = false;
	पूर्ण

	अगर (!rtw_coex_disabled(rtwdev)) अणु
		cfo->is_adjust = false;
		rtw8822c_set_crystal_cap(rtwdev, rtwdev->efuse.crystal_cap);
	पूर्ण
पूर्ण

अटल व्योम rtw8822c_cfo_track(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	काष्ठा rtw_cfo_track *cfo = &dm_info->cfo_track;
	u8 path_num = rtwdev->hal.rf_path_num;
	s8 crystal_cap = cfo->crystal_cap;
	s32 cfo_avg = 0;

	अगर (rtwdev->sta_cnt != 1) अणु
		rtw8822c_cfo_tracking_reset(rtwdev);
		वापस;
	पूर्ण

	अगर (cfo->packet_count == cfo->packet_count_pre)
		वापस;

	cfo->packet_count_pre = cfo->packet_count;
	cfo_avg = rtw8822c_cfo_calc_avg(rtwdev, path_num);
	rtw8822c_cfo_need_adjust(rtwdev, cfo_avg);

	अगर (cfo->is_adjust) अणु
		अगर (cfo_avg > CFO_TRK_ADJ_TH)
			crystal_cap++;
		अन्यथा अगर (cfo_avg < -CFO_TRK_ADJ_TH)
			crystal_cap--;

		crystal_cap = clamp_t(s8, crystal_cap, 0, XCAP_MASK);
		rtw8822c_set_crystal_cap(rtwdev, (u8)crystal_cap);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा rtw_phy_cck_pd_reg
rtw8822c_cck_pd_reg[RTW_CHANNEL_WIDTH_40 + 1][RTW_RF_PATH_MAX] = अणु
	अणु
		अणु0x1ac8, 0x00ff, 0x1ad0, 0x01fपूर्ण,
		अणु0x1ac8, 0xff00, 0x1ad0, 0x3e0पूर्ण
	पूर्ण,
	अणु
		अणु0x1acc, 0x00ff, 0x1ad0, 0x01F00000पूर्ण,
		अणु0x1acc, 0xff00, 0x1ad0, 0x3E000000पूर्ण
	पूर्ण,
पूर्ण;

#घोषणा RTW_CCK_PD_MAX 255
#घोषणा RTW_CCK_CS_MAX 31
#घोषणा RTW_CCK_CS_ERR1 27
#घोषणा RTW_CCK_CS_ERR2 29
अटल व्योम
rtw8822c_phy_cck_pd_set_reg(काष्ठा rtw_dev *rtwdev,
			    s8 pd_dअगरf, s8 cs_dअगरf, u8 bw, u8 nrx)
अणु
	u32 pd, cs;

	अगर (WARN_ON(bw > RTW_CHANNEL_WIDTH_40 || nrx >= RTW_RF_PATH_MAX))
		वापस;

	pd = rtw_पढ़ो32_mask(rtwdev,
			     rtw8822c_cck_pd_reg[bw][nrx].reg_pd,
			     rtw8822c_cck_pd_reg[bw][nrx].mask_pd);
	cs = rtw_पढ़ो32_mask(rtwdev,
			     rtw8822c_cck_pd_reg[bw][nrx].reg_cs,
			     rtw8822c_cck_pd_reg[bw][nrx].mask_cs);
	pd += pd_dअगरf;
	cs += cs_dअगरf;
	अगर (pd > RTW_CCK_PD_MAX)
		pd = RTW_CCK_PD_MAX;
	अगर (cs == RTW_CCK_CS_ERR1 || cs == RTW_CCK_CS_ERR2)
		cs++;
	अन्यथा अगर (cs > RTW_CCK_CS_MAX)
		cs = RTW_CCK_CS_MAX;
	rtw_ग_लिखो32_mask(rtwdev,
			 rtw8822c_cck_pd_reg[bw][nrx].reg_pd,
			 rtw8822c_cck_pd_reg[bw][nrx].mask_pd,
			 pd);
	rtw_ग_लिखो32_mask(rtwdev,
			 rtw8822c_cck_pd_reg[bw][nrx].reg_cs,
			 rtw8822c_cck_pd_reg[bw][nrx].mask_cs,
			 cs);

	rtw_dbg(rtwdev, RTW_DBG_PHY,
		"is_linked=%d, bw=%d, nrx=%d, cs_ratio=0x%x, pd_th=0x%x\n",
		rtw_is_assoc(rtwdev), bw, nrx, cs, pd);
पूर्ण

अटल व्योम rtw8822c_phy_cck_pd_set(काष्ठा rtw_dev *rtwdev, u8 new_lvl)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	s8 pd_lvl[CCK_PD_LV_MAX] = अणु0, 2, 4, 6, 8पूर्ण;
	s8 cs_lvl[CCK_PD_LV_MAX] = अणु0, 2, 2, 2, 4पूर्ण;
	u8 cur_lvl;
	u8 nrx, bw;

	nrx = (u8)rtw_पढ़ो32_mask(rtwdev, 0x1a2c, 0x60000);
	bw = (u8)rtw_पढ़ो32_mask(rtwdev, 0x9b0, 0xc);

	rtw_dbg(rtwdev, RTW_DBG_PHY, "lv: (%d) -> (%d) bw=%d nr=%d cck_fa_avg=%d\n",
		dm_info->cck_pd_lv[bw][nrx], new_lvl, bw, nrx,
		dm_info->cck_fa_avg);

	अगर (dm_info->cck_pd_lv[bw][nrx] == new_lvl)
		वापस;

	cur_lvl = dm_info->cck_pd_lv[bw][nrx];

	/* update cck pd info */
	dm_info->cck_fa_avg = CCK_FA_AVG_RESET;

	rtw8822c_phy_cck_pd_set_reg(rtwdev,
				    pd_lvl[new_lvl] - pd_lvl[cur_lvl],
				    cs_lvl[new_lvl] - cs_lvl[cur_lvl],
				    bw, nrx);
	dm_info->cck_pd_lv[bw][nrx] = new_lvl;
पूर्ण

#घोषणा PWR_TRACK_MASK 0x7f
अटल व्योम rtw8822c_pwrtrack_set(काष्ठा rtw_dev *rtwdev, u8 rf_path)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;

	चयन (rf_path) अणु
	हाल RF_PATH_A:
		rtw_ग_लिखो32_mask(rtwdev, 0x18a0, PWR_TRACK_MASK,
				 dm_info->delta_घातer_index[rf_path]);
		अवरोध;
	हाल RF_PATH_B:
		rtw_ग_लिखो32_mask(rtwdev, 0x41a0, PWR_TRACK_MASK,
				 dm_info->delta_घातer_index[rf_path]);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rtw8822c_pwr_track_path(काष्ठा rtw_dev *rtwdev,
				    काष्ठा rtw_swing_table *swing_table,
				    u8 path)
अणु
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;
	u8 thermal_value, delta;

	अगर (rtwdev->efuse.thermal_meter[path] == 0xff)
		वापस;

	thermal_value = rtw_पढ़ो_rf(rtwdev, path, RF_T_METER, 0x7e);

	rtw_phy_pwrtrack_avg(rtwdev, thermal_value, path);

	delta = rtw_phy_pwrtrack_get_delta(rtwdev, path);

	dm_info->delta_घातer_index[path] =
		rtw_phy_pwrtrack_get_pwridx(rtwdev, swing_table, path, path,
					    delta);

	rtw8822c_pwrtrack_set(rtwdev, path);
पूर्ण

अटल व्योम __rtw8822c_pwr_track(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_swing_table swing_table;
	u8 i;

	rtw_phy_config_swing_table(rtwdev, &swing_table);

	अगर (rtw_phy_pwrtrack_need_lck(rtwdev))
		rtw8822c_करो_lck(rtwdev);

	क्रम (i = 0; i < rtwdev->hal.rf_path_num; i++)
		rtw8822c_pwr_track_path(rtwdev, &swing_table, i);

पूर्ण

अटल व्योम rtw8822c_pwr_track(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	काष्ठा rtw_dm_info *dm_info = &rtwdev->dm_info;

	अगर (efuse->घातer_track_type != 0)
		वापस;

	अगर (!dm_info->pwr_trk_triggered) अणु
		rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_T_METER, BIT(19), 0x01);
		rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_T_METER, BIT(19), 0x00);
		rtw_ग_लिखो_rf(rtwdev, RF_PATH_A, RF_T_METER, BIT(19), 0x01);

		rtw_ग_लिखो_rf(rtwdev, RF_PATH_B, RF_T_METER, BIT(19), 0x01);
		rtw_ग_लिखो_rf(rtwdev, RF_PATH_B, RF_T_METER, BIT(19), 0x00);
		rtw_ग_लिखो_rf(rtwdev, RF_PATH_B, RF_T_METER, BIT(19), 0x01);

		dm_info->pwr_trk_triggered = true;
		वापस;
	पूर्ण

	__rtw8822c_pwr_track(rtwdev);
	dm_info->pwr_trk_triggered = false;
पूर्ण

अटल स्थिर काष्ठा rtw_pwr_seq_cmd trans_carddis_to_cardemu_8822c[] = अणु
	अणु0x0086,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_SDIO,
	 RTW_PWR_CMD_WRITE, BIT(0), 0पूर्ण,
	अणु0x0086,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_SDIO,
	 RTW_PWR_CMD_POLLING, BIT(1), BIT(1)पूर्ण,
	अणु0x002E,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(2), BIT(2)पूर्ण,
	अणु0x002D,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(0), 0पूर्ण,
	अणु0x007F,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(7), 0पूर्ण,
	अणु0x004A,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_USB_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(0), 0पूर्ण,
	अणु0x0005,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(3) | BIT(4) | BIT(7), 0पूर्ण,
	अणु0xFFFF,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 0,
	 RTW_PWR_CMD_END, 0, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_pwr_seq_cmd trans_cardemu_to_act_8822c[] = अणु
	अणु0x0000,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_USB_MSK | RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(5), 0पूर्ण,
	अणु0x0005,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, (BIT(4) | BIT(3) | BIT(2)), 0पूर्ण,
	अणु0x0075,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_PCI_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(0), BIT(0)पूर्ण,
	अणु0x0006,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_POLLING, BIT(1), BIT(1)पूर्ण,
	अणु0x0075,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_PCI_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(0), 0पूर्ण,
	अणु0xFF1A,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_USB_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, 0xFF, 0पूर्ण,
	अणु0x002E,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(3), 0पूर्ण,
	अणु0x0006,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(0), BIT(0)पूर्ण,
	अणु0x0005,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, (BIT(4) | BIT(3)), 0पूर्ण,
	अणु0x1018,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(2), BIT(2)पूर्ण,
	अणु0x0005,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(0), BIT(0)पूर्ण,
	अणु0x0005,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_POLLING, BIT(0), 0पूर्ण,
	अणु0x0074,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_PCI_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(5), BIT(5)पूर्ण,
	अणु0x0071,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_PCI_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(4), 0पूर्ण,
	अणु0x0062,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_PCI_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, (BIT(7) | BIT(6) | BIT(5)),
	 (BIT(7) | BIT(6) | BIT(5))पूर्ण,
	अणु0x0061,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_PCI_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, (BIT(7) | BIT(6) | BIT(5)), 0पूर्ण,
	अणु0x001F,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, (BIT(7) | BIT(6)), BIT(7)पूर्ण,
	अणु0x00EF,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, (BIT(7) | BIT(6)), BIT(7)पूर्ण,
	अणु0x1045,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(4), BIT(4)पूर्ण,
	अणु0x0010,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(2), BIT(2)पूर्ण,
	अणु0x1064,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(1), BIT(1)पूर्ण,
	अणु0xFFFF,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 0,
	 RTW_PWR_CMD_END, 0, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_pwr_seq_cmd trans_act_to_cardemu_8822c[] = अणु
	अणु0x0093,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(3), 0पूर्ण,
	अणु0x001F,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, 0xFF, 0पूर्ण,
	अणु0x00EF,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, 0xFF, 0पूर्ण,
	अणु0x1045,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(4), 0पूर्ण,
	अणु0xFF1A,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_USB_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, 0xFF, 0x30पूर्ण,
	अणु0x0049,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(1), 0पूर्ण,
	अणु0x0006,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(0), BIT(0)पूर्ण,
	अणु0x0002,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(1), 0पूर्ण,
	अणु0x0005,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(1), BIT(1)पूर्ण,
	अणु0x0005,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_POLLING, BIT(1), 0पूर्ण,
	अणु0x0000,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_USB_MSK | RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(5), BIT(5)पूर्ण,
	अणु0xFFFF,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 0,
	 RTW_PWR_CMD_END, 0, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_pwr_seq_cmd trans_cardemu_to_carddis_8822c[] = अणु
	अणु0x0005,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(7), BIT(7)पूर्ण,
	अणु0x0007,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_USB_MSK | RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, 0xFF, 0x00पूर्ण,
	अणु0x0067,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(5), 0पूर्ण,
	अणु0x004A,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_USB_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(0), 0पूर्ण,
	अणु0x0081,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(7) | BIT(6), 0पूर्ण,
	अणु0x0090,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(1), 0पूर्ण,
	अणु0x0092,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_PCI_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, 0xFF, 0x20पूर्ण,
	अणु0x0093,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_PCI_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, 0xFF, 0x04पूर्ण,
	अणु0x0005,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_USB_MSK | RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(3) | BIT(4), BIT(3)पूर्ण,
	अणु0x0005,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_PCI_MSK,
	 RTW_PWR_ADDR_MAC,
	 RTW_PWR_CMD_WRITE, BIT(2), BIT(2)पूर्ण,
	अणु0x0086,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_SDIO_MSK,
	 RTW_PWR_ADDR_SDIO,
	 RTW_PWR_CMD_WRITE, BIT(0), BIT(0)पूर्ण,
	अणु0xFFFF,
	 RTW_PWR_CUT_ALL_MSK,
	 RTW_PWR_INTF_ALL_MSK,
	 0,
	 RTW_PWR_CMD_END, 0, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_pwr_seq_cmd *card_enable_flow_8822c[] = अणु
	trans_carddis_to_cardemu_8822c,
	trans_cardemu_to_act_8822c,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा rtw_pwr_seq_cmd *card_disable_flow_8822c[] = अणु
	trans_act_to_cardemu_8822c,
	trans_cardemu_to_carddis_8822c,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा rtw_पूर्णांकf_phy_para usb2_param_8822c[] = अणु
	अणु0xFFFF, 0x00,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_ALL,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_पूर्णांकf_phy_para usb3_param_8822c[] = अणु
	अणु0xFFFF, 0x0000,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_ALL,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_पूर्णांकf_phy_para pcie_gen1_param_8822c[] = अणु
	अणु0xFFFF, 0x0000,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_ALL,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_पूर्णांकf_phy_para pcie_gen2_param_8822c[] = अणु
	अणु0xFFFF, 0x0000,
	 RTW_IP_SEL_PHY,
	 RTW_INTF_PHY_CUT_ALL,
	 RTW_INTF_PHY_PLATFORM_ALLपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_पूर्णांकf_phy_para_table phy_para_table_8822c = अणु
	.usb2_para	= usb2_param_8822c,
	.usb3_para	= usb3_param_8822c,
	.gen1_para	= pcie_gen1_param_8822c,
	.gen2_para	= pcie_gen2_param_8822c,
	.n_usb2_para	= ARRAY_SIZE(usb2_param_8822c),
	.n_usb3_para	= ARRAY_SIZE(usb2_param_8822c),
	.n_gen1_para	= ARRAY_SIZE(pcie_gen1_param_8822c),
	.n_gen2_para	= ARRAY_SIZE(pcie_gen2_param_8822c),
पूर्ण;

अटल स्थिर काष्ठा rtw_rfe_def rtw8822c_rfe_defs[] = अणु
	[0] = RTW_DEF_RFE(8822c, 0, 0),
	[1] = RTW_DEF_RFE(8822c, 0, 0),
	[2] = RTW_DEF_RFE(8822c, 0, 0),
	[5] = RTW_DEF_RFE(8822c, 0, 5),
	[6] = RTW_DEF_RFE(8822c, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा rtw_hw_reg rtw8822c_dig[] = अणु
	[0] = अणु .addr = 0x1d70, .mask = 0x7f पूर्ण,
	[1] = अणु .addr = 0x1d70, .mask = 0x7f00 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_ltecoex_addr rtw8822c_ltecoex_addr = अणु
	.ctrl = LTECOEX_ACCESS_CTRL,
	.wdata = LTECOEX_WRITE_DATA,
	.rdata = LTECOEX_READ_DATA,
पूर्ण;

अटल स्थिर काष्ठा rtw_page_table page_table_8822c[] = अणु
	अणु64, 64, 64, 64, 1पूर्ण,
	अणु64, 64, 64, 64, 1पूर्ण,
	अणु64, 64, 0, 0, 1पूर्ण,
	अणु64, 64, 64, 0, 1पूर्ण,
	अणु64, 64, 64, 64, 1पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rtw_rqpn rqpn_table_8822c[] = अणु
	अणुRTW_DMA_MAPPING_NORMAL, RTW_DMA_MAPPING_NORMAL,
	 RTW_DMA_MAPPING_LOW, RTW_DMA_MAPPING_LOW,
	 RTW_DMA_MAPPING_EXTRA, RTW_DMA_MAPPING_HIGHपूर्ण,
	अणुRTW_DMA_MAPPING_NORMAL, RTW_DMA_MAPPING_NORMAL,
	 RTW_DMA_MAPPING_LOW, RTW_DMA_MAPPING_LOW,
	 RTW_DMA_MAPPING_EXTRA, RTW_DMA_MAPPING_HIGHपूर्ण,
	अणुRTW_DMA_MAPPING_NORMAL, RTW_DMA_MAPPING_NORMAL,
	 RTW_DMA_MAPPING_NORMAL, RTW_DMA_MAPPING_HIGH,
	 RTW_DMA_MAPPING_HIGH, RTW_DMA_MAPPING_HIGHपूर्ण,
	अणुRTW_DMA_MAPPING_NORMAL, RTW_DMA_MAPPING_NORMAL,
	 RTW_DMA_MAPPING_LOW, RTW_DMA_MAPPING_LOW,
	 RTW_DMA_MAPPING_HIGH, RTW_DMA_MAPPING_HIGHपूर्ण,
	अणुRTW_DMA_MAPPING_NORMAL, RTW_DMA_MAPPING_NORMAL,
	 RTW_DMA_MAPPING_LOW, RTW_DMA_MAPPING_LOW,
	 RTW_DMA_MAPPING_EXTRA, RTW_DMA_MAPPING_HIGHपूर्ण,
पूर्ण;

अटल काष्ठा rtw_prioq_addrs prioq_addrs_8822c = अणु
	.prio[RTW_DMA_MAPPING_EXTRA] = अणु
		.rsvd = REG_FIFOPAGE_INFO_4, .avail = REG_FIFOPAGE_INFO_4 + 2,
	पूर्ण,
	.prio[RTW_DMA_MAPPING_LOW] = अणु
		.rsvd = REG_FIFOPAGE_INFO_2, .avail = REG_FIFOPAGE_INFO_2 + 2,
	पूर्ण,
	.prio[RTW_DMA_MAPPING_NORMAL] = अणु
		.rsvd = REG_FIFOPAGE_INFO_3, .avail = REG_FIFOPAGE_INFO_3 + 2,
	पूर्ण,
	.prio[RTW_DMA_MAPPING_HIGH] = अणु
		.rsvd = REG_FIFOPAGE_INFO_1, .avail = REG_FIFOPAGE_INFO_1 + 2,
	पूर्ण,
	.wsize = true,
पूर्ण;

अटल काष्ठा rtw_chip_ops rtw8822c_ops = अणु
	.phy_set_param		= rtw8822c_phy_set_param,
	.पढ़ो_efuse		= rtw8822c_पढ़ो_efuse,
	.query_rx_desc		= rtw8822c_query_rx_desc,
	.set_channel		= rtw8822c_set_channel,
	.mac_init		= rtw8822c_mac_init,
	.dump_fw_crash		= rtw8822c_dump_fw_crash,
	.पढ़ो_rf		= rtw_phy_पढ़ो_rf,
	.ग_लिखो_rf		= rtw_phy_ग_लिखो_rf_reg_mix,
	.set_tx_घातer_index	= rtw8822c_set_tx_घातer_index,
	.set_antenna		= rtw8822c_set_antenna,
	.cfg_lकरो25		= rtw8822c_cfg_lकरो25,
	.false_alarm_statistics	= rtw8822c_false_alarm_statistics,
	.dpk_track		= rtw8822c_dpk_track,
	.phy_calibration	= rtw8822c_phy_calibration,
	.cck_pd_set		= rtw8822c_phy_cck_pd_set,
	.pwr_track		= rtw8822c_pwr_track,
	.config_bfee		= rtw8822c_bf_config_bfee,
	.set_gid_table		= rtw_bf_set_gid_table,
	.cfg_csi_rate		= rtw_bf_cfg_csi_rate,
	.cfo_init		= rtw8822c_cfo_init,
	.cfo_track		= rtw8822c_cfo_track,

	.coex_set_init		= rtw8822c_coex_cfg_init,
	.coex_set_ant_चयन	= शून्य,
	.coex_set_gnt_fix	= rtw8822c_coex_cfg_gnt_fix,
	.coex_set_gnt_debug	= rtw8822c_coex_cfg_gnt_debug,
	.coex_set_rfe_type	= rtw8822c_coex_cfg_rfe_type,
	.coex_set_wl_tx_घातer	= rtw8822c_coex_cfg_wl_tx_घातer,
	.coex_set_wl_rx_gain	= rtw8822c_coex_cfg_wl_rx_gain,
पूर्ण;

/* Shared-Antenna Coex Table */
अटल स्थिर काष्ठा coex_table_para table_sant_8822c[] = अणु
	अणु0xffffffff, 0xffffffffपूर्ण, /* हाल-0 */
	अणु0x55555555, 0x55555555पूर्ण,
	अणु0x66555555, 0x66555555पूर्ण,
	अणु0xaaaaaaaa, 0xaaaaaaaaपूर्ण,
	अणु0x5a5a5a5a, 0x5a5a5a5aपूर्ण,
	अणु0xfafafafa, 0xfafafafaपूर्ण, /* हाल-5 */
	अणु0x6a5a5555, 0xaaaaaaaaपूर्ण,
	अणु0x6a5a56aa, 0x6a5a56aaपूर्ण,
	अणु0x6a5a5a5a, 0x6a5a5a5aपूर्ण,
	अणु0x66555555, 0x5a5a5a5aपूर्ण,
	अणु0x66555555, 0x6a5a5a5aपूर्ण, /* हाल-10 */
	अणु0x66555555, 0x6a5a5aaaपूर्ण,
	अणु0x66555555, 0x5a5a5aaaपूर्ण,
	अणु0x66555555, 0x6aaa5aaaपूर्ण,
	अणु0x66555555, 0xaaaa5aaaपूर्ण,
	अणु0x66555555, 0xaaaaaaaaपूर्ण, /* हाल-15 */
	अणु0xffff55ff, 0xfafafafaपूर्ण,
	अणु0xffff55ff, 0x6afa5afaपूर्ण,
	अणु0xaaffffaa, 0xfafafafaपूर्ण,
	अणु0xaa5555aa, 0x5a5a5a5aपूर्ण,
	अणु0xaa5555aa, 0x6a5a5a5aपूर्ण, /* हाल-20 */
	अणु0xaa5555aa, 0xaaaaaaaaपूर्ण,
	अणु0xffffffff, 0x5a5a5a5aपूर्ण,
	अणु0xffffffff, 0x5a5a5a5aपूर्ण,
	अणु0xffffffff, 0x55555555पूर्ण,
	अणु0xffffffff, 0x5a5a5aaaपूर्ण, /* हाल-25 */
	अणु0x55555555, 0x5a5a5a5aपूर्ण,
	अणु0x55555555, 0xaaaaaaaaपूर्ण,
	अणु0x55555555, 0x6a5a6a5aपूर्ण,
	अणु0x66556655, 0x66556655पूर्ण,
	अणु0x66556aaa, 0x6a5a6aaaपूर्ण, /*हाल-30*/
	अणु0xffffffff, 0x5aaa5aaaपूर्ण,
	अणु0x56555555, 0x5a5a5aaaपूर्ण,
पूर्ण;

/* Non-Shared-Antenna Coex Table */
अटल स्थिर काष्ठा coex_table_para table_nsant_8822c[] = अणु
	अणु0xffffffff, 0xffffffffपूर्ण, /* हाल-100 */
	अणु0x55555555, 0x55555555पूर्ण,
	अणु0x66555555, 0x66555555पूर्ण,
	अणु0xaaaaaaaa, 0xaaaaaaaaपूर्ण,
	अणु0x5a5a5a5a, 0x5a5a5a5aपूर्ण,
	अणु0xfafafafa, 0xfafafafaपूर्ण, /* हाल-105 */
	अणु0x5afa5afa, 0x5afa5afaपूर्ण,
	अणु0x55555555, 0xfafafafaपूर्ण,
	अणु0x66555555, 0xfafafafaपूर्ण,
	अणु0x66555555, 0x5a5a5a5aपूर्ण,
	अणु0x66555555, 0x6a5a5a5aपूर्ण, /* हाल-110 */
	अणु0x66555555, 0xaaaaaaaaपूर्ण,
	अणु0xffff55ff, 0xfafafafaपूर्ण,
	अणु0xffff55ff, 0x5afa5afaपूर्ण,
	अणु0xffff55ff, 0xaaaaaaaaपूर्ण,
	अणु0xffff55ff, 0xffff55ffपूर्ण, /* हाल-115 */
	अणु0xaaffffaa, 0x5afa5afaपूर्ण,
	अणु0xaaffffaa, 0xaaaaaaaaपूर्ण,
	अणु0xffffffff, 0xfafafafaपूर्ण,
	अणु0xffffffff, 0x5afa5afaपूर्ण,
	अणु0xffffffff, 0xaaaaaaaaपूर्ण, /* हाल-120 */
	अणु0x55ff55ff, 0x5afa5afaपूर्ण,
	अणु0x55ff55ff, 0xaaaaaaaaपूर्ण,
	अणु0x55ff55ff, 0x55ff55ffपूर्ण
पूर्ण;

/* Shared-Antenna TDMA */
अटल स्थिर काष्ठा coex_tdma_para tdma_sant_8822c[] = अणु
	अणु अणु0x00, 0x00, 0x00, 0x00, 0x00पूर्ण पूर्ण, /* हाल-0 */
	अणु अणु0x61, 0x45, 0x03, 0x11, 0x11पूर्ण पूर्ण, /* हाल-1 */
	अणु अणु0x61, 0x3a, 0x03, 0x11, 0x11पूर्ण पूर्ण,
	अणु अणु0x61, 0x30, 0x03, 0x11, 0x11पूर्ण पूर्ण,
	अणु अणु0x61, 0x20, 0x03, 0x11, 0x11पूर्ण पूर्ण,
	अणु अणु0x61, 0x10, 0x03, 0x11, 0x11पूर्ण पूर्ण, /* हाल-5 */
	अणु अणु0x61, 0x45, 0x03, 0x11, 0x10पूर्ण पूर्ण,
	अणु अणु0x61, 0x3a, 0x03, 0x11, 0x10पूर्ण पूर्ण,
	अणु अणु0x61, 0x30, 0x03, 0x11, 0x10पूर्ण पूर्ण,
	अणु अणु0x61, 0x20, 0x03, 0x11, 0x10पूर्ण पूर्ण,
	अणु अणु0x61, 0x10, 0x03, 0x11, 0x10पूर्ण पूर्ण, /* हाल-10 */
	अणु अणु0x61, 0x08, 0x03, 0x11, 0x14पूर्ण पूर्ण,
	अणु अणु0x61, 0x08, 0x03, 0x10, 0x14पूर्ण पूर्ण,
	अणु अणु0x51, 0x08, 0x03, 0x10, 0x54पूर्ण पूर्ण,
	अणु अणु0x51, 0x08, 0x03, 0x10, 0x55पूर्ण पूर्ण,
	अणु अणु0x51, 0x08, 0x07, 0x10, 0x54पूर्ण पूर्ण, /* हाल-15 */
	अणु अणु0x51, 0x45, 0x03, 0x10, 0x50पूर्ण पूर्ण,
	अणु अणु0x51, 0x3a, 0x03, 0x10, 0x50पूर्ण पूर्ण,
	अणु अणु0x51, 0x30, 0x03, 0x10, 0x50पूर्ण पूर्ण,
	अणु अणु0x51, 0x20, 0x03, 0x10, 0x50पूर्ण पूर्ण,
	अणु अणु0x51, 0x10, 0x03, 0x10, 0x50पूर्ण पूर्ण, /* हाल-20 */
	अणु अणु0x51, 0x4a, 0x03, 0x10, 0x50पूर्ण पूर्ण,
	अणु अणु0x51, 0x0c, 0x03, 0x10, 0x54पूर्ण पूर्ण,
	अणु अणु0x55, 0x08, 0x03, 0x10, 0x54पूर्ण पूर्ण,
	अणु अणु0x65, 0x10, 0x03, 0x11, 0x10पूर्ण पूर्ण,
	अणु अणु0x51, 0x10, 0x03, 0x10, 0x51पूर्ण पूर्ण, /* हाल-25 */
	अणु अणु0x51, 0x08, 0x03, 0x10, 0x50पूर्ण पूर्ण,
	अणु अणु0x61, 0x08, 0x03, 0x11, 0x11पूर्ण पूर्ण
पूर्ण;

/* Non-Shared-Antenna TDMA */
अटल स्थिर काष्ठा coex_tdma_para tdma_nsant_8822c[] = अणु
	अणु अणु0x00, 0x00, 0x00, 0x00, 0x00पूर्ण पूर्ण, /* हाल-100 */
	अणु अणु0x61, 0x45, 0x03, 0x11, 0x11पूर्ण पूर्ण,
	अणु अणु0x61, 0x3a, 0x03, 0x11, 0x11पूर्ण पूर्ण,
	अणु अणु0x61, 0x30, 0x03, 0x11, 0x11पूर्ण पूर्ण,
	अणु अणु0x61, 0x20, 0x03, 0x11, 0x11पूर्ण पूर्ण,
	अणु अणु0x61, 0x10, 0x03, 0x11, 0x11पूर्ण पूर्ण, /* हाल-105 */
	अणु अणु0x61, 0x45, 0x03, 0x11, 0x10पूर्ण पूर्ण,
	अणु अणु0x61, 0x3a, 0x03, 0x11, 0x10पूर्ण पूर्ण,
	अणु अणु0x61, 0x30, 0x03, 0x11, 0x10पूर्ण पूर्ण,
	अणु अणु0x61, 0x20, 0x03, 0x11, 0x10पूर्ण पूर्ण,
	अणु अणु0x61, 0x10, 0x03, 0x11, 0x10पूर्ण पूर्ण, /* हाल-110 */
	अणु अणु0x61, 0x08, 0x03, 0x11, 0x14पूर्ण पूर्ण,
	अणु अणु0x61, 0x08, 0x03, 0x10, 0x14पूर्ण पूर्ण,
	अणु अणु0x51, 0x08, 0x03, 0x10, 0x54पूर्ण पूर्ण,
	अणु अणु0x51, 0x08, 0x03, 0x10, 0x55पूर्ण पूर्ण,
	अणु अणु0x51, 0x08, 0x07, 0x10, 0x54पूर्ण पूर्ण, /* हाल-115 */
	अणु अणु0x51, 0x45, 0x03, 0x10, 0x50पूर्ण पूर्ण,
	अणु अणु0x51, 0x3a, 0x03, 0x10, 0x50पूर्ण पूर्ण,
	अणु अणु0x51, 0x30, 0x03, 0x10, 0x50पूर्ण पूर्ण,
	अणु अणु0x51, 0x20, 0x03, 0x10, 0x50पूर्ण पूर्ण,
	अणु अणु0x51, 0x10, 0x03, 0x10, 0x50पूर्ण पूर्ण, /* हाल-120 */
	अणु अणु0x51, 0x08, 0x03, 0x10, 0x50पूर्ण पूर्ण
पूर्ण;

/* rssi in percentage % (dbm = % - 100) */
अटल स्थिर u8 wl_rssi_step_8822c[] = अणु60, 50, 44, 30पूर्ण;
अटल स्थिर u8 bt_rssi_step_8822c[] = अणु8, 15, 20, 25पूर्ण;
अटल स्थिर काष्ठा coex_5g_afh_map afh_5g_8822c[] = अणु अणु0, 0, 0पूर्ण पूर्ण;

/* wl_tx_dec_घातer, bt_tx_dec_घातer, wl_rx_gain, bt_rx_lna_स्थिरrain */
अटल स्थिर काष्ठा coex_rf_para rf_para_tx_8822c[] = अणु
	अणु0, 0, false, 7पूर्ण,  /* क्रम normal */
	अणु0, 16, false, 7पूर्ण, /* क्रम WL-CPT */
	अणु8, 17, true, 4पूर्ण,
	अणु7, 18, true, 4पूर्ण,
	अणु6, 19, true, 4पूर्ण,
	अणु5, 20, true, 4पूर्ण
पूर्ण;

अटल स्थिर काष्ठा coex_rf_para rf_para_rx_8822c[] = अणु
	अणु0, 0, false, 7पूर्ण,  /* क्रम normal */
	अणु0, 16, false, 7पूर्ण, /* क्रम WL-CPT */
	अणु3, 24, true, 5पूर्ण,
	अणु2, 26, true, 5पूर्ण,
	अणु1, 27, true, 5पूर्ण,
	अणु0, 28, true, 5पूर्ण
पूर्ण;

अटल_निश्चित(ARRAY_SIZE(rf_para_tx_8822c) == ARRAY_SIZE(rf_para_rx_8822c));

अटल स्थिर u8
rtw8822c_pwrtrk_5gb_n[RTW_PWR_TRK_5G_NUM][RTW_PWR_TRK_TBL_SZ] = अणु
	अणु 0,  1,  2,  3,  5,  6,  7,  8,  9, 10,
	 11, 12, 13, 14, 15, 16, 18, 19, 20, 21,
	 22, 23, 24, 25, 26, 27, 28, 29, 30, 32 पूर्ण,
	अणु 0,  1,  2,  3,  5,  6,  7,  8,  9, 10,
	 11, 12, 13, 14, 15, 16, 18, 19, 20, 21,
	 22, 23, 24, 25, 26, 27, 28, 29, 30, 32 पूर्ण,
	अणु 0,  1,  2,  3,  5,  6,  7,  8,  9, 10,
	 11, 12, 13, 14, 15, 16, 18, 19, 20, 21,
	 22, 23, 24, 25, 26, 27, 28, 29, 30, 32 पूर्ण,
पूर्ण;

अटल स्थिर u8
rtw8822c_pwrtrk_5gb_p[RTW_PWR_TRK_5G_NUM][RTW_PWR_TRK_TBL_SZ] = अणु
	अणु 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
	 10, 10, 11, 12, 13, 14, 15, 16, 17, 18,
	 19, 20, 21, 22, 22, 23, 24, 25, 26, 27 पूर्ण,
	अणु 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
	 10, 10, 11, 12, 13, 14, 15, 16, 17, 18,
	 19, 20, 21, 22, 22, 23, 24, 25, 26, 27 पूर्ण,
	अणु 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
	 10, 10, 11, 12, 13, 14, 15, 16, 17, 18,
	 19, 20, 21, 22, 22, 23, 24, 25, 26, 27 पूर्ण,
पूर्ण;

अटल स्थिर u8
rtw8822c_pwrtrk_5ga_n[RTW_PWR_TRK_5G_NUM][RTW_PWR_TRK_TBL_SZ] = अणु
	अणु 0,  1,  2,  4,  5,  6,  7,  8,  9, 10,
	 11, 13, 14, 15, 16, 17, 18, 19, 20, 21,
	 23, 24, 25, 26, 27, 28, 29, 30, 31, 33 पूर्ण,
	अणु 0,  1,  2,  4,  5,  6,  7,  8,  9, 10,
	 11, 13, 14, 15, 16, 17, 18, 19, 20, 21,
	 23, 24, 25, 26, 27, 28, 29, 30, 31, 33 पूर्ण,
	अणु 0,  1,  2,  4,  5,  6,  7,  8,  9, 10,
	 11, 13, 14, 15, 16, 17, 18, 19, 20, 21,
	 23, 24, 25, 26, 27, 28, 29, 30, 31, 33 पूर्ण,
पूर्ण;

अटल स्थिर u8
rtw8822c_pwrtrk_5ga_p[RTW_PWR_TRK_5G_NUM][RTW_PWR_TRK_TBL_SZ] = अणु
	अणु 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
	 10, 11, 12, 13, 14, 15, 16, 17, 18, 20,
	 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 पूर्ण,
	अणु 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
	 10, 11, 12, 13, 14, 15, 16, 17, 18, 20,
	 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 पूर्ण,
	अणु 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
	 10, 11, 12, 13, 14, 15, 16, 17, 18, 20,
	 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 पूर्ण,
पूर्ण;

अटल स्थिर u8 rtw8822c_pwrtrk_2gb_n[RTW_PWR_TRK_TBL_SZ] = अणु
	 0,  1,  2,  3,  4,  4,  5,  6,  7,  8,
	 9,  9, 10, 11, 12, 13, 14, 15, 15, 16,
	17, 18, 19, 20, 20, 21, 22, 23, 24, 25
पूर्ण;

अटल स्थिर u8 rtw8822c_pwrtrk_2gb_p[RTW_PWR_TRK_TBL_SZ] = अणु
	 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
	10, 11, 12, 13, 14, 14, 15, 16, 17, 18,
	19, 20, 21, 22, 23, 24, 25, 26, 27, 28
पूर्ण;

अटल स्थिर u8 rtw8822c_pwrtrk_2ga_n[RTW_PWR_TRK_TBL_SZ] = अणु
	 0,  1,  2,  2,  3,  4,  4,  5,  6,  6,
	 7,  8,  8,  9,  9, 10, 11, 11, 12, 13,
	13, 14, 15, 15, 16, 17, 17, 18, 19, 19
पूर्ण;

अटल स्थिर u8 rtw8822c_pwrtrk_2ga_p[RTW_PWR_TRK_TBL_SZ] = अणु
	 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
	10, 11, 11, 12, 13, 14, 15, 16, 17, 18,
	19, 20, 21, 22, 23, 24, 25, 25, 26, 27
पूर्ण;

अटल स्थिर u8 rtw8822c_pwrtrk_2g_cck_b_n[RTW_PWR_TRK_TBL_SZ] = अणु
	 0,  1,  2,  3,  4,  5,  5,  6,  7,  8,
	 9, 10, 11, 11, 12, 13, 14, 15, 16, 17,
	17, 18, 19, 20, 21, 22, 23, 23, 24, 25
पूर्ण;

अटल स्थिर u8 rtw8822c_pwrtrk_2g_cck_b_p[RTW_PWR_TRK_TBL_SZ] = अणु
	 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
	10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
	20, 21, 22, 23, 24, 25, 26, 27, 28, 29
पूर्ण;

अटल स्थिर u8 rtw8822c_pwrtrk_2g_cck_a_n[RTW_PWR_TRK_TBL_SZ] = अणु
	 0,  1,  2,  3,  3,  4,  5,  6,  6,  7,
	 8,  9,  9, 10, 11, 12, 12, 13, 14, 15,
	15, 16, 17, 18, 18, 19, 20, 21, 21, 22
पूर्ण;

अटल स्थिर u8 rtw8822c_pwrtrk_2g_cck_a_p[RTW_PWR_TRK_TBL_SZ] = अणु
	 0,  1,  2,  3,  4,  5,  5,  6,  7,  8,
	 9, 10, 11, 11, 12, 13, 14, 15, 16, 17,
	18, 18, 19, 20, 21, 22, 23, 24, 24, 25
पूर्ण;

अटल स्थिर काष्ठा rtw_pwr_track_tbl rtw8822c_rtw_pwr_track_tbl = अणु
	.pwrtrk_5gb_n[RTW_PWR_TRK_5G_1] = rtw8822c_pwrtrk_5gb_n[RTW_PWR_TRK_5G_1],
	.pwrtrk_5gb_n[RTW_PWR_TRK_5G_2] = rtw8822c_pwrtrk_5gb_n[RTW_PWR_TRK_5G_2],
	.pwrtrk_5gb_n[RTW_PWR_TRK_5G_3] = rtw8822c_pwrtrk_5gb_n[RTW_PWR_TRK_5G_3],
	.pwrtrk_5gb_p[RTW_PWR_TRK_5G_1] = rtw8822c_pwrtrk_5gb_p[RTW_PWR_TRK_5G_1],
	.pwrtrk_5gb_p[RTW_PWR_TRK_5G_2] = rtw8822c_pwrtrk_5gb_p[RTW_PWR_TRK_5G_2],
	.pwrtrk_5gb_p[RTW_PWR_TRK_5G_3] = rtw8822c_pwrtrk_5gb_p[RTW_PWR_TRK_5G_3],
	.pwrtrk_5ga_n[RTW_PWR_TRK_5G_1] = rtw8822c_pwrtrk_5ga_n[RTW_PWR_TRK_5G_1],
	.pwrtrk_5ga_n[RTW_PWR_TRK_5G_2] = rtw8822c_pwrtrk_5ga_n[RTW_PWR_TRK_5G_2],
	.pwrtrk_5ga_n[RTW_PWR_TRK_5G_3] = rtw8822c_pwrtrk_5ga_n[RTW_PWR_TRK_5G_3],
	.pwrtrk_5ga_p[RTW_PWR_TRK_5G_1] = rtw8822c_pwrtrk_5ga_p[RTW_PWR_TRK_5G_1],
	.pwrtrk_5ga_p[RTW_PWR_TRK_5G_2] = rtw8822c_pwrtrk_5ga_p[RTW_PWR_TRK_5G_2],
	.pwrtrk_5ga_p[RTW_PWR_TRK_5G_3] = rtw8822c_pwrtrk_5ga_p[RTW_PWR_TRK_5G_3],
	.pwrtrk_2gb_n = rtw8822c_pwrtrk_2gb_n,
	.pwrtrk_2gb_p = rtw8822c_pwrtrk_2gb_p,
	.pwrtrk_2ga_n = rtw8822c_pwrtrk_2ga_n,
	.pwrtrk_2ga_p = rtw8822c_pwrtrk_2ga_p,
	.pwrtrk_2g_cckb_n = rtw8822c_pwrtrk_2g_cck_b_n,
	.pwrtrk_2g_cckb_p = rtw8822c_pwrtrk_2g_cck_b_p,
	.pwrtrk_2g_ccka_n = rtw8822c_pwrtrk_2g_cck_a_n,
	.pwrtrk_2g_ccka_p = rtw8822c_pwrtrk_2g_cck_a_p,
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल स्थिर काष्ठा wiphy_wowlan_support rtw_wowlan_stub_8822c = अणु
	.flags = WIPHY_WOWLAN_MAGIC_PKT | WIPHY_WOWLAN_GTK_REKEY_FAILURE |
		 WIPHY_WOWLAN_DISCONNECT | WIPHY_WOWLAN_SUPPORTS_GTK_REKEY |
		 WIPHY_WOWLAN_NET_DETECT,
	.n_patterns = RTW_MAX_PATTERN_NUM,
	.pattern_max_len = RTW_MAX_PATTERN_SIZE,
	.pattern_min_len = 1,
	.max_nd_match_sets = 4,
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा rtw_reg_करोमुख्य coex_info_hw_regs_8822c[] = अणु
	अणु0x1860, BIT(3), RTW_REG_DOMAIN_MAC8पूर्ण,
	अणु0x4160, BIT(3), RTW_REG_DOMAIN_MAC8पूर्ण,
	अणु0x1c32, BIT(6), RTW_REG_DOMAIN_MAC8पूर्ण,
	अणु0x1c38, BIT(28), RTW_REG_DOMAIN_MAC32पूर्ण,
	अणु0, 0, RTW_REG_DOMAIN_NLपूर्ण,
	अणु0x430, MASKDWORD, RTW_REG_DOMAIN_MAC32पूर्ण,
	अणु0x434, MASKDWORD, RTW_REG_DOMAIN_MAC32पूर्ण,
	अणु0x42a, MASKLWORD, RTW_REG_DOMAIN_MAC16पूर्ण,
	अणु0x426, MASKBYTE0, RTW_REG_DOMAIN_MAC8पूर्ण,
	अणु0x45e, BIT(3), RTW_REG_DOMAIN_MAC8पूर्ण,
	अणु0x454, MASKLWORD, RTW_REG_DOMAIN_MAC16पूर्ण,
	अणु0, 0, RTW_REG_DOMAIN_NLपूर्ण,
	अणु0x4c, BIT(24) | BIT(23), RTW_REG_DOMAIN_MAC32पूर्ण,
	अणु0x64, BIT(0), RTW_REG_DOMAIN_MAC8पूर्ण,
	अणु0x4c6, BIT(4), RTW_REG_DOMAIN_MAC8पूर्ण,
	अणु0x40, BIT(5), RTW_REG_DOMAIN_MAC8पूर्ण,
	अणु0x1, RFREG_MASK, RTW_REG_DOMAIN_RF_Bपूर्ण,
	अणु0, 0, RTW_REG_DOMAIN_NLपूर्ण,
	अणु0x550, MASKDWORD, RTW_REG_DOMAIN_MAC32पूर्ण,
	अणु0x522, MASKBYTE0, RTW_REG_DOMAIN_MAC8पूर्ण,
	अणु0x953, BIT(1), RTW_REG_DOMAIN_MAC8पूर्ण,
	अणु0xc50, MASKBYTE0, RTW_REG_DOMAIN_MAC8पूर्ण,
पूर्ण;

काष्ठा rtw_chip_info rtw8822c_hw_spec = अणु
	.ops = &rtw8822c_ops,
	.id = RTW_CHIP_TYPE_8822C,
	.fw_name = "rtw88/rtw8822c_fw.bin",
	.wlan_cpu = RTW_WCPU_11AC,
	.tx_pkt_desc_sz = 48,
	.tx_buf_desc_sz = 16,
	.rx_pkt_desc_sz = 24,
	.rx_buf_desc_sz = 8,
	.phy_efuse_size = 512,
	.log_efuse_size = 768,
	.ptct_efuse_size = 124,
	.txff_size = 262144,
	.rxff_size = 24576,
	.fw_rxff_size = 12288,
	.txgi_factor = 2,
	.is_pwr_by_rate_dec = false,
	.max_घातer_index = 0x7f,
	.csi_buf_pg_num = 50,
	.band = RTW_BAND_2G | RTW_BAND_5G,
	.page_size = 128,
	.dig_min = 0x20,
	.ht_supported = true,
	.vht_supported = true,
	.lps_deep_mode_supported = BIT(LPS_DEEP_MODE_LCLK) | BIT(LPS_DEEP_MODE_PG),
	.sys_func_en = 0xD8,
	.pwr_on_seq = card_enable_flow_8822c,
	.pwr_off_seq = card_disable_flow_8822c,
	.page_table = page_table_8822c,
	.rqpn_table = rqpn_table_8822c,
	.prioq_addrs = &prioq_addrs_8822c,
	.पूर्णांकf_table = &phy_para_table_8822c,
	.dig = rtw8822c_dig,
	.dig_cck = शून्य,
	.rf_base_addr = अणु0x3c00, 0x4c00पूर्ण,
	.rf_sipi_addr = अणु0x1808, 0x4108पूर्ण,
	.ltecoex_addr = &rtw8822c_ltecoex_addr,
	.mac_tbl = &rtw8822c_mac_tbl,
	.agc_tbl = &rtw8822c_agc_tbl,
	.bb_tbl = &rtw8822c_bb_tbl,
	.rfk_init_tbl = &rtw8822c_array_mp_cal_init_tbl,
	.rf_tbl = अणु&rtw8822c_rf_b_tbl, &rtw8822c_rf_a_tblपूर्ण,
	.rfe_defs = rtw8822c_rfe_defs,
	.rfe_defs_size = ARRAY_SIZE(rtw8822c_rfe_defs),
	.en_dis_dpd = true,
	.dpd_ratemask = DIS_DPD_RATEALL,
	.pwr_track_tbl = &rtw8822c_rtw_pwr_track_tbl,
	.iqk_threshold = 8,
	.lck_threshold = 8,
	.bfer_su_max_num = 2,
	.bfer_mu_max_num = 1,
	.rx_ldpc = true,

#अगर_घोषित CONFIG_PM
	.wow_fw_name = "rtw88/rtw8822c_wow_fw.bin",
	.wowlan_stub = &rtw_wowlan_stub_8822c,
	.max_sched_scan_ssids = 4,
#पूर्ण_अगर
	.coex_para_ver = 0x2103181c,
	.bt_desired_ver = 0x1c,
	.scbd_support = true,
	.new_scbd10_def = true,
	.ble_hid_profile_support = true,
	.pstdma_type = COEX_PSTDMA_FORCE_LPSOFF,
	.bt_rssi_type = COEX_BTRSSI_DBM,
	.ant_isolation = 15,
	.rssi_tolerance = 2,
	.wl_rssi_step = wl_rssi_step_8822c,
	.bt_rssi_step = bt_rssi_step_8822c,
	.table_sant_num = ARRAY_SIZE(table_sant_8822c),
	.table_sant = table_sant_8822c,
	.table_nsant_num = ARRAY_SIZE(table_nsant_8822c),
	.table_nsant = table_nsant_8822c,
	.tdma_sant_num = ARRAY_SIZE(tdma_sant_8822c),
	.tdma_sant = tdma_sant_8822c,
	.tdma_nsant_num = ARRAY_SIZE(tdma_nsant_8822c),
	.tdma_nsant = tdma_nsant_8822c,
	.wl_rf_para_num = ARRAY_SIZE(rf_para_tx_8822c),
	.wl_rf_para_tx = rf_para_tx_8822c,
	.wl_rf_para_rx = rf_para_rx_8822c,
	.bt_afh_span_bw20 = 0x24,
	.bt_afh_span_bw40 = 0x36,
	.afh_5g_num = ARRAY_SIZE(afh_5g_8822c),
	.afh_5g = afh_5g_8822c,

	.coex_info_hw_regs_num = ARRAY_SIZE(coex_info_hw_regs_8822c),
	.coex_info_hw_regs = coex_info_hw_regs_8822c,

	.fw_fअगरo_addr = अणु0x780, 0x700, 0x780, 0x660, 0x650, 0x680पूर्ण,
पूर्ण;
EXPORT_SYMBOL(rtw8822c_hw_spec);

MODULE_FIRMWARE("rtw88/rtw8822c_fw.bin");
MODULE_FIRMWARE("rtw88/rtw8822c_wow_fw.bin");

MODULE_AUTHOR("Realtek Corporation");
MODULE_DESCRIPTION("Realtek 802.11ac wireless 8822c driver");
MODULE_LICENSE("Dual BSD/GPL");
