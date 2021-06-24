<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "wifi.h"
#समावेश "efuse.h"
#समावेश "pci.h"
#समावेश <linux/export.h>

अटल स्थिर u8 PGPKT_DATA_SIZE = 8;
अटल स्थिर पूर्णांक EFUSE_MAX_SIZE = 512;

#घोषणा START_ADDRESS		0x1000
#घोषणा REG_MCUFWDL		0x0080

अटल स्थिर काष्ठा rtl_efuse_ops efuse_ops = अणु
	.efuse_onebyte_पढ़ो = efuse_one_byte_पढ़ो,
	.efuse_logical_map_पढ़ो = efuse_shaकरोw_पढ़ो,
पूर्ण;

अटल व्योम efuse_shaकरोw_पढ़ो_1byte(काष्ठा ieee80211_hw *hw, u16 offset,
				    u8 *value);
अटल व्योम efuse_shaकरोw_पढ़ो_2byte(काष्ठा ieee80211_hw *hw, u16 offset,
				    u16 *value);
अटल व्योम efuse_shaकरोw_पढ़ो_4byte(काष्ठा ieee80211_hw *hw, u16 offset,
				    u32 *value);
अटल व्योम efuse_shaकरोw_ग_लिखो_1byte(काष्ठा ieee80211_hw *hw, u16 offset,
				     u8 value);
अटल व्योम efuse_shaकरोw_ग_लिखो_2byte(काष्ठा ieee80211_hw *hw, u16 offset,
				     u16 value);
अटल व्योम efuse_shaकरोw_ग_लिखो_4byte(काष्ठा ieee80211_hw *hw, u16 offset,
				     u32 value);
अटल पूर्णांक efuse_one_byte_ग_लिखो(काष्ठा ieee80211_hw *hw, u16 addr,
				u8 data);
अटल व्योम efuse_पढ़ो_all_map(काष्ठा ieee80211_hw *hw, u8 *efuse);
अटल पूर्णांक efuse_pg_packet_पढ़ो(काष्ठा ieee80211_hw *hw, u8 offset,
				u8 *data);
अटल पूर्णांक efuse_pg_packet_ग_लिखो(काष्ठा ieee80211_hw *hw, u8 offset,
				 u8 word_en, u8 *data);
अटल व्योम efuse_word_enable_data_पढ़ो(u8 word_en, u8 *sourdata,
					u8 *targetdata);
अटल u8 enable_efuse_data_ग_लिखो(काष्ठा ieee80211_hw *hw,
				  u16 efuse_addr, u8 word_en, u8 *data);
अटल u16 efuse_get_current_size(काष्ठा ieee80211_hw *hw);
अटल u8 efuse_calculate_word_cnts(u8 word_en);

व्योम efuse_initialize(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 bytetemp;
	u8 temp;

	bytetemp = rtl_पढ़ो_byte(rtlpriv, rtlpriv->cfg->maps[SYS_FUNC_EN] + 1);
	temp = bytetemp | 0x20;
	rtl_ग_लिखो_byte(rtlpriv, rtlpriv->cfg->maps[SYS_FUNC_EN] + 1, temp);

	bytetemp = rtl_पढ़ो_byte(rtlpriv, rtlpriv->cfg->maps[SYS_ISO_CTRL] + 1);
	temp = bytetemp & 0xFE;
	rtl_ग_लिखो_byte(rtlpriv, rtlpriv->cfg->maps[SYS_ISO_CTRL] + 1, temp);

	bytetemp = rtl_पढ़ो_byte(rtlpriv, rtlpriv->cfg->maps[EFUSE_TEST] + 3);
	temp = bytetemp | 0x80;
	rtl_ग_लिखो_byte(rtlpriv, rtlpriv->cfg->maps[EFUSE_TEST] + 3, temp);

	rtl_ग_लिखो_byte(rtlpriv, 0x2F8, 0x3);

	rtl_ग_लिखो_byte(rtlpriv, rtlpriv->cfg->maps[EFUSE_CTRL] + 3, 0x72);

पूर्ण

u8 efuse_पढ़ो_1byte(काष्ठा ieee80211_hw *hw, u16 address)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 data;
	u8 bytetemp;
	u8 temp;
	u32 k = 0;
	स्थिर u32 efuse_len =
		rtlpriv->cfg->maps[EFUSE_REAL_CONTENT_SIZE];

	अगर (address < efuse_len) अणु
		temp = address & 0xFF;
		rtl_ग_लिखो_byte(rtlpriv, rtlpriv->cfg->maps[EFUSE_CTRL] + 1,
			       temp);
		bytetemp = rtl_पढ़ो_byte(rtlpriv,
					 rtlpriv->cfg->maps[EFUSE_CTRL] + 2);
		temp = ((address >> 8) & 0x03) | (bytetemp & 0xFC);
		rtl_ग_लिखो_byte(rtlpriv, rtlpriv->cfg->maps[EFUSE_CTRL] + 2,
			       temp);

		bytetemp = rtl_पढ़ो_byte(rtlpriv,
					 rtlpriv->cfg->maps[EFUSE_CTRL] + 3);
		temp = bytetemp & 0x7F;
		rtl_ग_लिखो_byte(rtlpriv, rtlpriv->cfg->maps[EFUSE_CTRL] + 3,
			       temp);

		bytetemp = rtl_पढ़ो_byte(rtlpriv,
					 rtlpriv->cfg->maps[EFUSE_CTRL] + 3);
		जबतक (!(bytetemp & 0x80)) अणु
			bytetemp = rtl_पढ़ो_byte(rtlpriv,
						 rtlpriv->cfg->
						 maps[EFUSE_CTRL] + 3);
			k++;
			अगर (k == 1000)
				अवरोध;
		पूर्ण
		data = rtl_पढ़ो_byte(rtlpriv, rtlpriv->cfg->maps[EFUSE_CTRL]);
		वापस data;
	पूर्ण अन्यथा
		वापस 0xFF;

पूर्ण
EXPORT_SYMBOL(efuse_पढ़ो_1byte);

व्योम efuse_ग_लिखो_1byte(काष्ठा ieee80211_hw *hw, u16 address, u8 value)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 bytetemp;
	u8 temp;
	u32 k = 0;
	स्थिर u32 efuse_len =
		rtlpriv->cfg->maps[EFUSE_REAL_CONTENT_SIZE];

	rtl_dbg(rtlpriv, COMP_EFUSE, DBG_LOUD, "Addr=%x Data =%x\n",
		address, value);

	अगर (address < efuse_len) अणु
		rtl_ग_लिखो_byte(rtlpriv, rtlpriv->cfg->maps[EFUSE_CTRL], value);

		temp = address & 0xFF;
		rtl_ग_लिखो_byte(rtlpriv, rtlpriv->cfg->maps[EFUSE_CTRL] + 1,
			       temp);
		bytetemp = rtl_पढ़ो_byte(rtlpriv,
					 rtlpriv->cfg->maps[EFUSE_CTRL] + 2);

		temp = ((address >> 8) & 0x03) | (bytetemp & 0xFC);
		rtl_ग_लिखो_byte(rtlpriv,
			       rtlpriv->cfg->maps[EFUSE_CTRL] + 2, temp);

		bytetemp = rtl_पढ़ो_byte(rtlpriv,
					 rtlpriv->cfg->maps[EFUSE_CTRL] + 3);
		temp = bytetemp | 0x80;
		rtl_ग_लिखो_byte(rtlpriv,
			       rtlpriv->cfg->maps[EFUSE_CTRL] + 3, temp);

		bytetemp = rtl_पढ़ो_byte(rtlpriv,
					 rtlpriv->cfg->maps[EFUSE_CTRL] + 3);

		जबतक (bytetemp & 0x80) अणु
			bytetemp = rtl_पढ़ो_byte(rtlpriv,
						 rtlpriv->cfg->
						 maps[EFUSE_CTRL] + 3);
			k++;
			अगर (k == 100) अणु
				k = 0;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

पूर्ण

व्योम पढ़ो_efuse_byte(काष्ठा ieee80211_hw *hw, u16 _offset, u8 *pbuf)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 value32;
	u8 पढ़ोbyte;
	u16 retry;

	rtl_ग_लिखो_byte(rtlpriv, rtlpriv->cfg->maps[EFUSE_CTRL] + 1,
		       (_offset & 0xff));
	पढ़ोbyte = rtl_पढ़ो_byte(rtlpriv, rtlpriv->cfg->maps[EFUSE_CTRL] + 2);
	rtl_ग_लिखो_byte(rtlpriv, rtlpriv->cfg->maps[EFUSE_CTRL] + 2,
		       ((_offset >> 8) & 0x03) | (पढ़ोbyte & 0xfc));

	पढ़ोbyte = rtl_पढ़ो_byte(rtlpriv, rtlpriv->cfg->maps[EFUSE_CTRL] + 3);
	rtl_ग_लिखो_byte(rtlpriv, rtlpriv->cfg->maps[EFUSE_CTRL] + 3,
		       (पढ़ोbyte & 0x7f));

	retry = 0;
	value32 = rtl_पढ़ो_dword(rtlpriv, rtlpriv->cfg->maps[EFUSE_CTRL]);
	जबतक (!(((value32 >> 24) & 0xff) & 0x80) && (retry < 10000)) अणु
		value32 = rtl_पढ़ो_dword(rtlpriv,
					 rtlpriv->cfg->maps[EFUSE_CTRL]);
		retry++;
	पूर्ण

	udelay(50);
	value32 = rtl_पढ़ो_dword(rtlpriv, rtlpriv->cfg->maps[EFUSE_CTRL]);

	*pbuf = (u8) (value32 & 0xff);
पूर्ण
EXPORT_SYMBOL_GPL(पढ़ो_efuse_byte);

व्योम पढ़ो_efuse(काष्ठा ieee80211_hw *hw, u16 _offset, u16 _size_byte, u8 *pbuf)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u8 *efuse_tbl;
	u8 rtemp8[1];
	u16 efuse_addr = 0;
	u8 offset, wren;
	u8 u1temp = 0;
	u16 i;
	u16 j;
	स्थिर u16 efuse_max_section =
		rtlpriv->cfg->maps[EFUSE_MAX_SECTION_MAP];
	स्थिर u32 efuse_len =
		rtlpriv->cfg->maps[EFUSE_REAL_CONTENT_SIZE];
	u16 **efuse_word;
	u16 efuse_utilized = 0;
	u8 efuse_usage;

	अगर ((_offset + _size_byte) > rtlpriv->cfg->maps[EFUSE_HWSET_MAX_SIZE]) अणु
		rtl_dbg(rtlpriv, COMP_EFUSE, DBG_LOUD,
			"%s: Invalid offset(%#x) with read bytes(%#x)!!\n",
			__func__, _offset, _size_byte);
		वापस;
	पूर्ण

	/* allocate memory क्रम efuse_tbl and efuse_word */
	efuse_tbl = kzalloc(rtlpriv->cfg->maps[EFUSE_HWSET_MAX_SIZE],
			    GFP_ATOMIC);
	अगर (!efuse_tbl)
		वापस;
	efuse_word = kसुस्मृति(EFUSE_MAX_WORD_UNIT, माप(u16 *), GFP_ATOMIC);
	अगर (!efuse_word)
		जाओ out;
	क्रम (i = 0; i < EFUSE_MAX_WORD_UNIT; i++) अणु
		efuse_word[i] = kसुस्मृति(efuse_max_section, माप(u16),
					GFP_ATOMIC);
		अगर (!efuse_word[i])
			जाओ करोne;
	पूर्ण

	क्रम (i = 0; i < efuse_max_section; i++)
		क्रम (j = 0; j < EFUSE_MAX_WORD_UNIT; j++)
			efuse_word[j][i] = 0xFFFF;

	पढ़ो_efuse_byte(hw, efuse_addr, rtemp8);
	अगर (*rtemp8 != 0xFF) अणु
		efuse_utilized++;
		RTPRINT(rtlpriv, FEEPROM, EFUSE_READ_ALL,
			"Addr=%d\n", efuse_addr);
		efuse_addr++;
	पूर्ण

	जबतक ((*rtemp8 != 0xFF) && (efuse_addr < efuse_len)) अणु
		/*  Check PG header क्रम section num.  */
		अगर ((*rtemp8 & 0x1F) == 0x0F) अणु/* extended header */
			u1temp = ((*rtemp8 & 0xE0) >> 5);
			पढ़ो_efuse_byte(hw, efuse_addr, rtemp8);

			अगर ((*rtemp8 & 0x0F) == 0x0F) अणु
				efuse_addr++;
				पढ़ो_efuse_byte(hw, efuse_addr, rtemp8);

				अगर (*rtemp8 != 0xFF &&
				    (efuse_addr < efuse_len)) अणु
					efuse_addr++;
				पूर्ण
				जारी;
			पूर्ण अन्यथा अणु
				offset = ((*rtemp8 & 0xF0) >> 1) | u1temp;
				wren = (*rtemp8 & 0x0F);
				efuse_addr++;
			पूर्ण
		पूर्ण अन्यथा अणु
			offset = ((*rtemp8 >> 4) & 0x0f);
			wren = (*rtemp8 & 0x0f);
		पूर्ण

		अगर (offset < efuse_max_section) अणु
			RTPRINT(rtlpriv, FEEPROM, EFUSE_READ_ALL,
				"offset-%d Worden=%x\n", offset, wren);

			क्रम (i = 0; i < EFUSE_MAX_WORD_UNIT; i++) अणु
				अगर (!(wren & 0x01)) अणु
					RTPRINT(rtlpriv, FEEPROM,
						EFUSE_READ_ALL,
						"Addr=%d\n", efuse_addr);

					पढ़ो_efuse_byte(hw, efuse_addr, rtemp8);
					efuse_addr++;
					efuse_utilized++;
					efuse_word[i][offset] =
							 (*rtemp8 & 0xff);

					अगर (efuse_addr >= efuse_len)
						अवरोध;

					RTPRINT(rtlpriv, FEEPROM,
						EFUSE_READ_ALL,
						"Addr=%d\n", efuse_addr);

					पढ़ो_efuse_byte(hw, efuse_addr, rtemp8);
					efuse_addr++;
					efuse_utilized++;
					efuse_word[i][offset] |=
					    (((u16)*rtemp8 << 8) & 0xff00);

					अगर (efuse_addr >= efuse_len)
						अवरोध;
				पूर्ण

				wren >>= 1;
			पूर्ण
		पूर्ण

		RTPRINT(rtlpriv, FEEPROM, EFUSE_READ_ALL,
			"Addr=%d\n", efuse_addr);
		पढ़ो_efuse_byte(hw, efuse_addr, rtemp8);
		अगर (*rtemp8 != 0xFF && (efuse_addr < efuse_len)) अणु
			efuse_utilized++;
			efuse_addr++;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < efuse_max_section; i++) अणु
		क्रम (j = 0; j < EFUSE_MAX_WORD_UNIT; j++) अणु
			efuse_tbl[(i * 8) + (j * 2)] =
			    (efuse_word[j][i] & 0xff);
			efuse_tbl[(i * 8) + ((j * 2) + 1)] =
			    ((efuse_word[j][i] >> 8) & 0xff);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < _size_byte; i++)
		pbuf[i] = efuse_tbl[_offset + i];

	rtlefuse->efuse_usedbytes = efuse_utilized;
	efuse_usage = (u8) ((efuse_utilized * 100) / efuse_len);
	rtlefuse->efuse_usedpercentage = efuse_usage;
	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_EFUSE_BYTES,
				      (u8 *)&efuse_utilized);
	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_EFUSE_USAGE,
				      &efuse_usage);
करोne:
	क्रम (i = 0; i < EFUSE_MAX_WORD_UNIT; i++)
		kमुक्त(efuse_word[i]);
	kमुक्त(efuse_word);
out:
	kमुक्त(efuse_tbl);
पूर्ण

bool efuse_shaकरोw_update_chk(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u8 section_idx, i, base;
	u16 words_need = 0, hdr_num = 0, totalbytes, efuse_used;
	bool wordchanged, result = true;

	क्रम (section_idx = 0; section_idx < 16; section_idx++) अणु
		base = section_idx * 8;
		wordchanged = false;

		क्रम (i = 0; i < 8; i = i + 2) अणु
			अगर (rtlefuse->efuse_map[EFUSE_INIT_MAP][base + i] !=
			    rtlefuse->efuse_map[EFUSE_MODIFY_MAP][base + i] ||
			    rtlefuse->efuse_map[EFUSE_INIT_MAP][base + i + 1] !=
			    rtlefuse->efuse_map[EFUSE_MODIFY_MAP][base + i +
								   1]) अणु
				words_need++;
				wordchanged = true;
			पूर्ण
		पूर्ण

		अगर (wordchanged)
			hdr_num++;
	पूर्ण

	totalbytes = hdr_num + words_need * 2;
	efuse_used = rtlefuse->efuse_usedbytes;

	अगर ((totalbytes + efuse_used) >=
	    (EFUSE_MAX_SIZE - rtlpriv->cfg->maps[EFUSE_OOB_PROTECT_BYTES_LEN]))
		result = false;

	rtl_dbg(rtlpriv, COMP_EFUSE, DBG_LOUD,
		"%s: totalbytes(%#x), hdr_num(%#x), words_need(%#x), efuse_used(%d)\n",
		__func__, totalbytes, hdr_num, words_need, efuse_used);

	वापस result;
पूर्ण

व्योम efuse_shaकरोw_पढ़ो(काष्ठा ieee80211_hw *hw, u8 type,
		       u16 offset, u32 *value)
अणु
	अगर (type == 1)
		efuse_shaकरोw_पढ़ो_1byte(hw, offset, (u8 *)value);
	अन्यथा अगर (type == 2)
		efuse_shaकरोw_पढ़ो_2byte(hw, offset, (u16 *)value);
	अन्यथा अगर (type == 4)
		efuse_shaकरोw_पढ़ो_4byte(hw, offset, value);

पूर्ण
EXPORT_SYMBOL(efuse_shaकरोw_पढ़ो);

व्योम efuse_shaकरोw_ग_लिखो(काष्ठा ieee80211_hw *hw, u8 type, u16 offset,
				u32 value)
अणु
	अगर (type == 1)
		efuse_shaकरोw_ग_लिखो_1byte(hw, offset, (u8) value);
	अन्यथा अगर (type == 2)
		efuse_shaकरोw_ग_लिखो_2byte(hw, offset, (u16) value);
	अन्यथा अगर (type == 4)
		efuse_shaकरोw_ग_लिखो_4byte(hw, offset, value);

पूर्ण

bool efuse_shaकरोw_update(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u16 i, offset, base;
	u8 word_en = 0x0F;
	u8 first_pg = false;

	rtl_dbg(rtlpriv, COMP_EFUSE, DBG_LOUD, "\n");

	अगर (!efuse_shaकरोw_update_chk(hw)) अणु
		efuse_पढ़ो_all_map(hw, &rtlefuse->efuse_map[EFUSE_INIT_MAP][0]);
		स_नकल(&rtlefuse->efuse_map[EFUSE_MODIFY_MAP][0],
		       &rtlefuse->efuse_map[EFUSE_INIT_MAP][0],
		       rtlpriv->cfg->maps[EFUSE_HWSET_MAX_SIZE]);

		rtl_dbg(rtlpriv, COMP_EFUSE, DBG_LOUD,
			"efuse out of capacity!!\n");
		वापस false;
	पूर्ण
	efuse_घातer_चयन(hw, true, true);

	क्रम (offset = 0; offset < 16; offset++) अणु

		word_en = 0x0F;
		base = offset * 8;

		क्रम (i = 0; i < 8; i++) अणु
			अगर (first_pg) अणु
				word_en &= ~(BIT(i / 2));

				rtlefuse->efuse_map[EFUSE_INIT_MAP][base + i] =
				    rtlefuse->efuse_map[EFUSE_MODIFY_MAP][base + i];
			पूर्ण अन्यथा अणु

				अगर (rtlefuse->efuse_map[EFUSE_INIT_MAP][base + i] !=
				    rtlefuse->efuse_map[EFUSE_MODIFY_MAP][base + i]) अणु
					word_en &= ~(BIT(i / 2));

					rtlefuse->efuse_map[EFUSE_INIT_MAP][base + i] =
					    rtlefuse->efuse_map[EFUSE_MODIFY_MAP][base + i];
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (word_en != 0x0F) अणु
			u8 पंचांगpdata[8];

			स_नकल(पंचांगpdata,
			       &rtlefuse->efuse_map[EFUSE_MODIFY_MAP][base],
			       8);
			RT_PRINT_DATA(rtlpriv, COMP_INIT, DBG_LOUD,
				      "U-efuse\n", पंचांगpdata, 8);

			अगर (!efuse_pg_packet_ग_लिखो(hw, (u8) offset, word_en,
						   पंचांगpdata)) अणु
				rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
					"PG section(%#x) fail!!\n", offset);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	efuse_घातer_चयन(hw, true, false);
	efuse_पढ़ो_all_map(hw, &rtlefuse->efuse_map[EFUSE_INIT_MAP][0]);

	स_नकल(&rtlefuse->efuse_map[EFUSE_MODIFY_MAP][0],
	       &rtlefuse->efuse_map[EFUSE_INIT_MAP][0],
	       rtlpriv->cfg->maps[EFUSE_HWSET_MAX_SIZE]);

	rtl_dbg(rtlpriv, COMP_EFUSE, DBG_LOUD, "\n");
	वापस true;
पूर्ण

व्योम rtl_efuse_shaकरोw_map_update(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));

	अगर (rtlefuse->स्वतःload_failflag)
		स_रखो((&rtlefuse->efuse_map[EFUSE_INIT_MAP][0]),
		       0xFF, rtlpriv->cfg->maps[EFUSE_HWSET_MAX_SIZE]);
	अन्यथा
		efuse_पढ़ो_all_map(hw, &rtlefuse->efuse_map[EFUSE_INIT_MAP][0]);

	स_नकल(&rtlefuse->efuse_map[EFUSE_MODIFY_MAP][0],
			&rtlefuse->efuse_map[EFUSE_INIT_MAP][0],
			rtlpriv->cfg->maps[EFUSE_HWSET_MAX_SIZE]);

पूर्ण
EXPORT_SYMBOL(rtl_efuse_shaकरोw_map_update);

व्योम efuse_क्रमce_ग_लिखो_venकरोr_id(काष्ठा ieee80211_hw *hw)
अणु
	u8 पंचांगpdata[8] = अणु 0xFF, 0xFF, 0xEC, 0x10, 0xFF, 0xFF, 0xFF, 0xFF पूर्ण;

	efuse_घातer_चयन(hw, true, true);

	efuse_pg_packet_ग_लिखो(hw, 1, 0xD, पंचांगpdata);

	efuse_घातer_चयन(hw, true, false);

पूर्ण

व्योम efuse_re_pg_section(काष्ठा ieee80211_hw *hw, u8 section_idx)
अणु
पूर्ण

अटल व्योम efuse_shaकरोw_पढ़ो_1byte(काष्ठा ieee80211_hw *hw,
				    u16 offset, u8 *value)
अणु
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	*value = rtlefuse->efuse_map[EFUSE_MODIFY_MAP][offset];
पूर्ण

अटल व्योम efuse_shaकरोw_पढ़ो_2byte(काष्ठा ieee80211_hw *hw,
				    u16 offset, u16 *value)
अणु
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));

	*value = rtlefuse->efuse_map[EFUSE_MODIFY_MAP][offset];
	*value |= rtlefuse->efuse_map[EFUSE_MODIFY_MAP][offset + 1] << 8;

पूर्ण

अटल व्योम efuse_shaकरोw_पढ़ो_4byte(काष्ठा ieee80211_hw *hw,
				    u16 offset, u32 *value)
अणु
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));

	*value = rtlefuse->efuse_map[EFUSE_MODIFY_MAP][offset];
	*value |= rtlefuse->efuse_map[EFUSE_MODIFY_MAP][offset + 1] << 8;
	*value |= rtlefuse->efuse_map[EFUSE_MODIFY_MAP][offset + 2] << 16;
	*value |= rtlefuse->efuse_map[EFUSE_MODIFY_MAP][offset + 3] << 24;
पूर्ण

अटल व्योम efuse_shaकरोw_ग_लिखो_1byte(काष्ठा ieee80211_hw *hw,
				     u16 offset, u8 value)
अणु
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));

	rtlefuse->efuse_map[EFUSE_MODIFY_MAP][offset] = value;
पूर्ण

अटल व्योम efuse_shaकरोw_ग_लिखो_2byte(काष्ठा ieee80211_hw *hw,
				     u16 offset, u16 value)
अणु
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));

	rtlefuse->efuse_map[EFUSE_MODIFY_MAP][offset] = value & 0x00FF;
	rtlefuse->efuse_map[EFUSE_MODIFY_MAP][offset + 1] = value >> 8;

पूर्ण

अटल व्योम efuse_shaकरोw_ग_लिखो_4byte(काष्ठा ieee80211_hw *hw,
				     u16 offset, u32 value)
अणु
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));

	rtlefuse->efuse_map[EFUSE_MODIFY_MAP][offset] =
	    (u8) (value & 0x000000FF);
	rtlefuse->efuse_map[EFUSE_MODIFY_MAP][offset + 1] =
	    (u8) ((value >> 8) & 0x0000FF);
	rtlefuse->efuse_map[EFUSE_MODIFY_MAP][offset + 2] =
	    (u8) ((value >> 16) & 0x00FF);
	rtlefuse->efuse_map[EFUSE_MODIFY_MAP][offset + 3] =
	    (u8) ((value >> 24) & 0xFF);

पूर्ण

पूर्णांक efuse_one_byte_पढ़ो(काष्ठा ieee80211_hw *hw, u16 addr, u8 *data)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 पंचांगpidx = 0;
	पूर्णांक result;

	rtl_ग_लिखो_byte(rtlpriv, rtlpriv->cfg->maps[EFUSE_CTRL] + 1,
		       (u8) (addr & 0xff));
	rtl_ग_लिखो_byte(rtlpriv, rtlpriv->cfg->maps[EFUSE_CTRL] + 2,
		       ((u8) ((addr >> 8) & 0x03)) |
		       (rtl_पढ़ो_byte(rtlpriv,
				      rtlpriv->cfg->maps[EFUSE_CTRL] + 2) &
			0xFC));

	rtl_ग_लिखो_byte(rtlpriv, rtlpriv->cfg->maps[EFUSE_CTRL] + 3, 0x72);

	जबतक (!(0x80 & rtl_पढ़ो_byte(rtlpriv,
				      rtlpriv->cfg->maps[EFUSE_CTRL] + 3))
	       && (पंचांगpidx < 100)) अणु
		पंचांगpidx++;
	पूर्ण

	अगर (पंचांगpidx < 100) अणु
		*data = rtl_पढ़ो_byte(rtlpriv, rtlpriv->cfg->maps[EFUSE_CTRL]);
		result = true;
	पूर्ण अन्यथा अणु
		*data = 0xff;
		result = false;
	पूर्ण
	वापस result;
पूर्ण
EXPORT_SYMBOL(efuse_one_byte_पढ़ो);

अटल पूर्णांक efuse_one_byte_ग_लिखो(काष्ठा ieee80211_hw *hw, u16 addr, u8 data)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 पंचांगpidx = 0;

	rtl_dbg(rtlpriv, COMP_EFUSE, DBG_LOUD,
		"Addr = %x Data=%x\n", addr, data);

	rtl_ग_लिखो_byte(rtlpriv,
		       rtlpriv->cfg->maps[EFUSE_CTRL] + 1, (u8) (addr & 0xff));
	rtl_ग_लिखो_byte(rtlpriv, rtlpriv->cfg->maps[EFUSE_CTRL] + 2,
		       (rtl_पढ़ो_byte(rtlpriv,
			 rtlpriv->cfg->maps[EFUSE_CTRL] +
			 2) & 0xFC) | (u8) ((addr >> 8) & 0x03));

	rtl_ग_लिखो_byte(rtlpriv, rtlpriv->cfg->maps[EFUSE_CTRL], data);
	rtl_ग_लिखो_byte(rtlpriv, rtlpriv->cfg->maps[EFUSE_CTRL] + 3, 0xF2);

	जबतक ((0x80 & rtl_पढ़ो_byte(rtlpriv,
				     rtlpriv->cfg->maps[EFUSE_CTRL] + 3))
	       && (पंचांगpidx < 100)) अणु
		पंचांगpidx++;
	पूर्ण

	अगर (पंचांगpidx < 100)
		वापस true;
	वापस false;
पूर्ण

अटल व्योम efuse_पढ़ो_all_map(काष्ठा ieee80211_hw *hw, u8 *efuse)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	efuse_घातer_चयन(hw, false, true);
	पढ़ो_efuse(hw, 0, rtlpriv->cfg->maps[EFUSE_HWSET_MAX_SIZE], efuse);
	efuse_घातer_चयन(hw, false, false);
पूर्ण

अटल व्योम efuse_पढ़ो_data_हाल1(काष्ठा ieee80211_hw *hw, u16 *efuse_addr,
				u8 efuse_data, u8 offset, u8 *पंचांगpdata,
				u8 *पढ़ोstate)
अणु
	bool dataempty = true;
	u8 hoffset;
	u8 पंचांगpidx;
	u8 hworden;
	u8 word_cnts;

	hoffset = (efuse_data >> 4) & 0x0F;
	hworden = efuse_data & 0x0F;
	word_cnts = efuse_calculate_word_cnts(hworden);

	अगर (hoffset == offset) अणु
		क्रम (पंचांगpidx = 0; पंचांगpidx < word_cnts * 2; पंचांगpidx++) अणु
			अगर (efuse_one_byte_पढ़ो(hw, *efuse_addr + 1 + पंचांगpidx,
						&efuse_data)) अणु
				पंचांगpdata[पंचांगpidx] = efuse_data;
				अगर (efuse_data != 0xff)
					dataempty = false;
			पूर्ण
		पूर्ण

		अगर (!dataempty) अणु
			*पढ़ोstate = PG_STATE_DATA;
		पूर्ण अन्यथा अणु
			*efuse_addr = *efuse_addr + (word_cnts * 2) + 1;
			*पढ़ोstate = PG_STATE_HEADER;
		पूर्ण

	पूर्ण अन्यथा अणु
		*efuse_addr = *efuse_addr + (word_cnts * 2) + 1;
		*पढ़ोstate = PG_STATE_HEADER;
	पूर्ण
पूर्ण

अटल पूर्णांक efuse_pg_packet_पढ़ो(काष्ठा ieee80211_hw *hw, u8 offset, u8 *data)
अणु
	u8 पढ़ोstate = PG_STATE_HEADER;

	bool continual = true;

	u8 efuse_data, word_cnts = 0;
	u16 efuse_addr = 0;
	u8 पंचांगpdata[8];

	अगर (data == शून्य)
		वापस false;
	अगर (offset > 15)
		वापस false;

	स_रखो(data, 0xff, PGPKT_DATA_SIZE * माप(u8));
	स_रखो(पंचांगpdata, 0xff, PGPKT_DATA_SIZE * माप(u8));

	जबतक (continual && (efuse_addr < EFUSE_MAX_SIZE)) अणु
		अगर (पढ़ोstate & PG_STATE_HEADER) अणु
			अगर (efuse_one_byte_पढ़ो(hw, efuse_addr, &efuse_data)
			    && (efuse_data != 0xFF))
				efuse_पढ़ो_data_हाल1(hw, &efuse_addr,
						      efuse_data, offset,
						      पंचांगpdata, &पढ़ोstate);
			अन्यथा
				continual = false;
		पूर्ण अन्यथा अगर (पढ़ोstate & PG_STATE_DATA) अणु
			efuse_word_enable_data_पढ़ो(0, पंचांगpdata, data);
			efuse_addr = efuse_addr + (word_cnts * 2) + 1;
			पढ़ोstate = PG_STATE_HEADER;
		पूर्ण

	पूर्ण

	अगर ((data[0] == 0xff) && (data[1] == 0xff) &&
	    (data[2] == 0xff) && (data[3] == 0xff) &&
	    (data[4] == 0xff) && (data[5] == 0xff) &&
	    (data[6] == 0xff) && (data[7] == 0xff))
		वापस false;
	अन्यथा
		वापस true;

पूर्ण

अटल व्योम efuse_ग_लिखो_data_हाल1(काष्ठा ieee80211_hw *hw, u16 *efuse_addr,
				   u8 efuse_data, u8 offset,
				   पूर्णांक *continual, u8 *ग_लिखो_state,
				   काष्ठा pgpkt_काष्ठा *target_pkt,
				   पूर्णांक *repeat_बार, पूर्णांक *result, u8 word_en)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा pgpkt_काष्ठा पंचांगp_pkt;
	पूर्णांक dataempty = true;
	u8 originaldata[8 * माप(u8)];
	u8 badworden = 0x0F;
	u8 match_word_en, पंचांगp_word_en;
	u8 पंचांगpindex;
	u8 पंचांगp_header = efuse_data;
	u8 पंचांगp_word_cnts;

	पंचांगp_pkt.offset = (पंचांगp_header >> 4) & 0x0F;
	पंचांगp_pkt.word_en = पंचांगp_header & 0x0F;
	पंचांगp_word_cnts = efuse_calculate_word_cnts(पंचांगp_pkt.word_en);

	अगर (पंचांगp_pkt.offset != target_pkt->offset) अणु
		*efuse_addr = *efuse_addr + (पंचांगp_word_cnts * 2) + 1;
		*ग_लिखो_state = PG_STATE_HEADER;
	पूर्ण अन्यथा अणु
		क्रम (पंचांगpindex = 0; पंचांगpindex < (पंचांगp_word_cnts * 2); पंचांगpindex++) अणु
			अगर (efuse_one_byte_पढ़ो(hw,
						(*efuse_addr + 1 + पंचांगpindex),
						&efuse_data) &&
			    (efuse_data != 0xFF))
				dataempty = false;
		पूर्ण

		अगर (!dataempty) अणु
			*efuse_addr = *efuse_addr + (पंचांगp_word_cnts * 2) + 1;
			*ग_लिखो_state = PG_STATE_HEADER;
		पूर्ण अन्यथा अणु
			match_word_en = 0x0F;
			अगर (!((target_pkt->word_en & BIT(0)) |
			    (पंचांगp_pkt.word_en & BIT(0))))
				match_word_en &= (~BIT(0));

			अगर (!((target_pkt->word_en & BIT(1)) |
			    (पंचांगp_pkt.word_en & BIT(1))))
				match_word_en &= (~BIT(1));

			अगर (!((target_pkt->word_en & BIT(2)) |
			    (पंचांगp_pkt.word_en & BIT(2))))
				match_word_en &= (~BIT(2));

			अगर (!((target_pkt->word_en & BIT(3)) |
			    (पंचांगp_pkt.word_en & BIT(3))))
				match_word_en &= (~BIT(3));

			अगर ((match_word_en & 0x0F) != 0x0F) अणु
				badworden =
				  enable_efuse_data_ग_लिखो(hw,
							  *efuse_addr + 1,
							  पंचांगp_pkt.word_en,
							  target_pkt->data);

				अगर (0x0F != (badworden & 0x0F))	अणु
					u8 reorg_offset = offset;
					u8 reorg_worden = badworden;

					efuse_pg_packet_ग_लिखो(hw, reorg_offset,
							      reorg_worden,
							      originaldata);
				पूर्ण

				पंचांगp_word_en = 0x0F;
				अगर ((target_pkt->word_en & BIT(0)) ^
				    (match_word_en & BIT(0)))
					पंचांगp_word_en &= (~BIT(0));

				अगर ((target_pkt->word_en & BIT(1)) ^
				    (match_word_en & BIT(1)))
					पंचांगp_word_en &= (~BIT(1));

				अगर ((target_pkt->word_en & BIT(2)) ^
				    (match_word_en & BIT(2)))
					पंचांगp_word_en &= (~BIT(2));

				अगर ((target_pkt->word_en & BIT(3)) ^
				    (match_word_en & BIT(3)))
					पंचांगp_word_en &= (~BIT(3));

				अगर ((पंचांगp_word_en & 0x0F) != 0x0F) अणु
					*efuse_addr = efuse_get_current_size(hw);
					target_pkt->offset = offset;
					target_pkt->word_en = पंचांगp_word_en;
				पूर्ण अन्यथा अणु
					*continual = false;
				पूर्ण
				*ग_लिखो_state = PG_STATE_HEADER;
				*repeat_बार += 1;
				अगर (*repeat_बार > EFUSE_REPEAT_THRESHOLD_) अणु
					*continual = false;
					*result = false;
				पूर्ण
			पूर्ण अन्यथा अणु
				*efuse_addr += (2 * पंचांगp_word_cnts) + 1;
				target_pkt->offset = offset;
				target_pkt->word_en = word_en;
				*ग_लिखो_state = PG_STATE_HEADER;
			पूर्ण
		पूर्ण
	पूर्ण
	RTPRINT(rtlpriv, FEEPROM, EFUSE_PG, "efuse PG_STATE_HEADER-1\n");
पूर्ण

अटल व्योम efuse_ग_लिखो_data_हाल2(काष्ठा ieee80211_hw *hw, u16 *efuse_addr,
				   पूर्णांक *continual, u8 *ग_लिखो_state,
				   काष्ठा pgpkt_काष्ठा target_pkt,
				   पूर्णांक *repeat_बार, पूर्णांक *result)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा pgpkt_काष्ठा पंचांगp_pkt;
	u8 pg_header;
	u8 पंचांगp_header;
	u8 originaldata[8 * माप(u8)];
	u8 पंचांगp_word_cnts;
	u8 badworden = 0x0F;

	pg_header = ((target_pkt.offset << 4) & 0xf0) | target_pkt.word_en;
	efuse_one_byte_ग_लिखो(hw, *efuse_addr, pg_header);
	efuse_one_byte_पढ़ो(hw, *efuse_addr, &पंचांगp_header);

	अगर (पंचांगp_header == pg_header) अणु
		*ग_लिखो_state = PG_STATE_DATA;
	पूर्ण अन्यथा अगर (पंचांगp_header == 0xFF) अणु
		*ग_लिखो_state = PG_STATE_HEADER;
		*repeat_बार += 1;
		अगर (*repeat_बार > EFUSE_REPEAT_THRESHOLD_) अणु
			*continual = false;
			*result = false;
		पूर्ण
	पूर्ण अन्यथा अणु
		पंचांगp_pkt.offset = (पंचांगp_header >> 4) & 0x0F;
		पंचांगp_pkt.word_en = पंचांगp_header & 0x0F;

		पंचांगp_word_cnts = efuse_calculate_word_cnts(पंचांगp_pkt.word_en);

		स_रखो(originaldata, 0xff,  8 * माप(u8));

		अगर (efuse_pg_packet_पढ़ो(hw, पंचांगp_pkt.offset, originaldata)) अणु
			badworden = enable_efuse_data_ग_लिखो(hw,
							    *efuse_addr + 1,
							    पंचांगp_pkt.word_en,
							    originaldata);

			अगर (0x0F != (badworden & 0x0F)) अणु
				u8 reorg_offset = पंचांगp_pkt.offset;
				u8 reorg_worden = badworden;

				efuse_pg_packet_ग_लिखो(hw, reorg_offset,
						      reorg_worden,
						      originaldata);
				*efuse_addr = efuse_get_current_size(hw);
			पूर्ण अन्यथा अणु
				*efuse_addr = *efuse_addr +
					      (पंचांगp_word_cnts * 2) + 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			*efuse_addr = *efuse_addr + (पंचांगp_word_cnts * 2) + 1;
		पूर्ण

		*ग_लिखो_state = PG_STATE_HEADER;
		*repeat_बार += 1;
		अगर (*repeat_बार > EFUSE_REPEAT_THRESHOLD_) अणु
			*continual = false;
			*result = false;
		पूर्ण

		RTPRINT(rtlpriv, FEEPROM, EFUSE_PG,
			"efuse PG_STATE_HEADER-2\n");
	पूर्ण
पूर्ण

अटल पूर्णांक efuse_pg_packet_ग_लिखो(काष्ठा ieee80211_hw *hw,
				 u8 offset, u8 word_en, u8 *data)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा pgpkt_काष्ठा target_pkt;
	u8 ग_लिखो_state = PG_STATE_HEADER;
	पूर्णांक continual = true, result = true;
	u16 efuse_addr = 0;
	u8 efuse_data;
	u8 target_word_cnts = 0;
	u8 badworden = 0x0F;
	अटल पूर्णांक repeat_बार;

	अगर (efuse_get_current_size(hw) >= (EFUSE_MAX_SIZE -
		rtlpriv->cfg->maps[EFUSE_OOB_PROTECT_BYTES_LEN])) अणु
		RTPRINT(rtlpriv, FEEPROM, EFUSE_PG,
			"efuse_pg_packet_write error\n");
		वापस false;
	पूर्ण

	target_pkt.offset = offset;
	target_pkt.word_en = word_en;

	स_रखो(target_pkt.data, 0xFF,  8 * माप(u8));

	efuse_word_enable_data_पढ़ो(word_en, data, target_pkt.data);
	target_word_cnts = efuse_calculate_word_cnts(target_pkt.word_en);

	RTPRINT(rtlpriv, FEEPROM, EFUSE_PG, "efuse Power ON\n");

	जबतक (continual && (efuse_addr < (EFUSE_MAX_SIZE -
		rtlpriv->cfg->maps[EFUSE_OOB_PROTECT_BYTES_LEN]))) अणु
		अगर (ग_लिखो_state == PG_STATE_HEADER) अणु
			badworden = 0x0F;
			RTPRINT(rtlpriv, FEEPROM, EFUSE_PG,
				"efuse PG_STATE_HEADER\n");

			अगर (efuse_one_byte_पढ़ो(hw, efuse_addr, &efuse_data) &&
			    (efuse_data != 0xFF))
				efuse_ग_लिखो_data_हाल1(hw, &efuse_addr,
						       efuse_data, offset,
						       &continual,
						       &ग_लिखो_state,
						       &target_pkt,
						       &repeat_बार, &result,
						       word_en);
			अन्यथा
				efuse_ग_लिखो_data_हाल2(hw, &efuse_addr,
						       &continual,
						       &ग_लिखो_state,
						       target_pkt,
						       &repeat_बार,
						       &result);

		पूर्ण अन्यथा अगर (ग_लिखो_state == PG_STATE_DATA) अणु
			RTPRINT(rtlpriv, FEEPROM, EFUSE_PG,
				"efuse PG_STATE_DATA\n");
			badworden =
			    enable_efuse_data_ग_लिखो(hw, efuse_addr + 1,
						    target_pkt.word_en,
						    target_pkt.data);

			अगर ((badworden & 0x0F) == 0x0F) अणु
				continual = false;
			पूर्ण अन्यथा अणु
				efuse_addr =
				    efuse_addr + (2 * target_word_cnts) + 1;

				target_pkt.offset = offset;
				target_pkt.word_en = badworden;
				target_word_cnts =
				    efuse_calculate_word_cnts(target_pkt.
							      word_en);
				ग_लिखो_state = PG_STATE_HEADER;
				repeat_बार++;
				अगर (repeat_बार > EFUSE_REPEAT_THRESHOLD_) अणु
					continual = false;
					result = false;
				पूर्ण
				RTPRINT(rtlpriv, FEEPROM, EFUSE_PG,
					"efuse PG_STATE_HEADER-3\n");
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (efuse_addr >= (EFUSE_MAX_SIZE -
		rtlpriv->cfg->maps[EFUSE_OOB_PROTECT_BYTES_LEN])) अणु
		rtl_dbg(rtlpriv, COMP_EFUSE, DBG_LOUD,
			"efuse_addr(%#x) Out of size!!\n", efuse_addr);
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम efuse_word_enable_data_पढ़ो(u8 word_en, u8 *sourdata,
					u8 *targetdata)
अणु
	अगर (!(word_en & BIT(0))) अणु
		targetdata[0] = sourdata[0];
		targetdata[1] = sourdata[1];
	पूर्ण

	अगर (!(word_en & BIT(1))) अणु
		targetdata[2] = sourdata[2];
		targetdata[3] = sourdata[3];
	पूर्ण

	अगर (!(word_en & BIT(2))) अणु
		targetdata[4] = sourdata[4];
		targetdata[5] = sourdata[5];
	पूर्ण

	अगर (!(word_en & BIT(3))) अणु
		targetdata[6] = sourdata[6];
		targetdata[7] = sourdata[7];
	पूर्ण
पूर्ण

अटल u8 enable_efuse_data_ग_लिखो(काष्ठा ieee80211_hw *hw,
				  u16 efuse_addr, u8 word_en, u8 *data)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u16 पंचांगpaddr;
	u16 start_addr = efuse_addr;
	u8 badworden = 0x0F;
	u8 पंचांगpdata[8];

	स_रखो(पंचांगpdata, 0xff, PGPKT_DATA_SIZE);
	rtl_dbg(rtlpriv, COMP_EFUSE, DBG_LOUD,
		"word_en = %x efuse_addr=%x\n", word_en, efuse_addr);

	अगर (!(word_en & BIT(0))) अणु
		पंचांगpaddr = start_addr;
		efuse_one_byte_ग_लिखो(hw, start_addr++, data[0]);
		efuse_one_byte_ग_लिखो(hw, start_addr++, data[1]);

		efuse_one_byte_पढ़ो(hw, पंचांगpaddr, &पंचांगpdata[0]);
		efuse_one_byte_पढ़ो(hw, पंचांगpaddr + 1, &पंचांगpdata[1]);
		अगर ((data[0] != पंचांगpdata[0]) || (data[1] != पंचांगpdata[1]))
			badworden &= (~BIT(0));
	पूर्ण

	अगर (!(word_en & BIT(1))) अणु
		पंचांगpaddr = start_addr;
		efuse_one_byte_ग_लिखो(hw, start_addr++, data[2]);
		efuse_one_byte_ग_लिखो(hw, start_addr++, data[3]);

		efuse_one_byte_पढ़ो(hw, पंचांगpaddr, &पंचांगpdata[2]);
		efuse_one_byte_पढ़ो(hw, पंचांगpaddr + 1, &पंचांगpdata[3]);
		अगर ((data[2] != पंचांगpdata[2]) || (data[3] != पंचांगpdata[3]))
			badworden &= (~BIT(1));
	पूर्ण

	अगर (!(word_en & BIT(2))) अणु
		पंचांगpaddr = start_addr;
		efuse_one_byte_ग_लिखो(hw, start_addr++, data[4]);
		efuse_one_byte_ग_लिखो(hw, start_addr++, data[5]);

		efuse_one_byte_पढ़ो(hw, पंचांगpaddr, &पंचांगpdata[4]);
		efuse_one_byte_पढ़ो(hw, पंचांगpaddr + 1, &पंचांगpdata[5]);
		अगर ((data[4] != पंचांगpdata[4]) || (data[5] != पंचांगpdata[5]))
			badworden &= (~BIT(2));
	पूर्ण

	अगर (!(word_en & BIT(3))) अणु
		पंचांगpaddr = start_addr;
		efuse_one_byte_ग_लिखो(hw, start_addr++, data[6]);
		efuse_one_byte_ग_लिखो(hw, start_addr++, data[7]);

		efuse_one_byte_पढ़ो(hw, पंचांगpaddr, &पंचांगpdata[6]);
		efuse_one_byte_पढ़ो(hw, पंचांगpaddr + 1, &पंचांगpdata[7]);
		अगर ((data[6] != पंचांगpdata[6]) || (data[7] != पंचांगpdata[7]))
			badworden &= (~BIT(3));
	पूर्ण

	वापस badworden;
पूर्ण

व्योम efuse_घातer_चयन(काष्ठा ieee80211_hw *hw, u8 ग_लिखो, u8 pwrstate)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 tempval;
	u16 पंचांगpv16;

	अगर (pwrstate && (rtlhal->hw_type != HARDWARE_TYPE_RTL8192SE)) अणु
		अगर (rtlhal->hw_type != HARDWARE_TYPE_RTL8192CE &&
		    rtlhal->hw_type != HARDWARE_TYPE_RTL8192DE) अणु
			rtl_ग_लिखो_byte(rtlpriv,
				       rtlpriv->cfg->maps[EFUSE_ACCESS], 0x69);
		पूर्ण अन्यथा अणु
			पंचांगpv16 =
			  rtl_पढ़ो_word(rtlpriv,
					rtlpriv->cfg->maps[SYS_ISO_CTRL]);
			अगर (!(पंचांगpv16 & rtlpriv->cfg->maps[EFUSE_PWC_EV12V])) अणु
				पंचांगpv16 |= rtlpriv->cfg->maps[EFUSE_PWC_EV12V];
				rtl_ग_लिखो_word(rtlpriv,
					       rtlpriv->cfg->maps[SYS_ISO_CTRL],
					       पंचांगpv16);
			पूर्ण
		पूर्ण
		पंचांगpv16 = rtl_पढ़ो_word(rtlpriv,
				       rtlpriv->cfg->maps[SYS_FUNC_EN]);
		अगर (!(पंचांगpv16 & rtlpriv->cfg->maps[EFUSE_FEN_ELDR])) अणु
			पंचांगpv16 |= rtlpriv->cfg->maps[EFUSE_FEN_ELDR];
			rtl_ग_लिखो_word(rtlpriv,
				       rtlpriv->cfg->maps[SYS_FUNC_EN], पंचांगpv16);
		पूर्ण

		पंचांगpv16 = rtl_पढ़ो_word(rtlpriv, rtlpriv->cfg->maps[SYS_CLK]);
		अगर ((!(पंचांगpv16 & rtlpriv->cfg->maps[EFUSE_LOADER_CLK_EN])) ||
		    (!(पंचांगpv16 & rtlpriv->cfg->maps[EFUSE_ANA8M]))) अणु
			पंचांगpv16 |= (rtlpriv->cfg->maps[EFUSE_LOADER_CLK_EN] |
				   rtlpriv->cfg->maps[EFUSE_ANA8M]);
			rtl_ग_लिखो_word(rtlpriv,
				       rtlpriv->cfg->maps[SYS_CLK], पंचांगpv16);
		पूर्ण
	पूर्ण

	अगर (pwrstate) अणु
		अगर (ग_लिखो) अणु
			tempval = rtl_पढ़ो_byte(rtlpriv,
						rtlpriv->cfg->maps[EFUSE_TEST] +
						3);

			अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE) अणु
				tempval &= ~(BIT(3) | BIT(4) | BIT(5) | BIT(6));
				tempval |= (VOLTAGE_V25 << 3);
			पूर्ण अन्यथा अगर (rtlhal->hw_type != HARDWARE_TYPE_RTL8192SE) अणु
				tempval &= 0x0F;
				tempval |= (VOLTAGE_V25 << 4);
			पूर्ण

			rtl_ग_लिखो_byte(rtlpriv,
				       rtlpriv->cfg->maps[EFUSE_TEST] + 3,
				       (tempval | 0x80));
		पूर्ण

		अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8192SE) अणु
			rtl_ग_लिखो_byte(rtlpriv, rtlpriv->cfg->maps[EFUSE_CLK],
				       0x03);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (rtlhal->hw_type != HARDWARE_TYPE_RTL8192CE &&
		    rtlhal->hw_type != HARDWARE_TYPE_RTL8192DE)
			rtl_ग_लिखो_byte(rtlpriv,
				       rtlpriv->cfg->maps[EFUSE_ACCESS], 0);

		अगर (ग_लिखो) अणु
			tempval = rtl_पढ़ो_byte(rtlpriv,
						rtlpriv->cfg->maps[EFUSE_TEST] +
						3);
			rtl_ग_लिखो_byte(rtlpriv,
				       rtlpriv->cfg->maps[EFUSE_TEST] + 3,
				       (tempval & 0x7F));
		पूर्ण

		अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8192SE) अणु
			rtl_ग_लिखो_byte(rtlpriv, rtlpriv->cfg->maps[EFUSE_CLK],
				       0x02);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(efuse_घातer_चयन);

अटल u16 efuse_get_current_size(काष्ठा ieee80211_hw *hw)
अणु
	पूर्णांक continual = true;
	u16 efuse_addr = 0;
	u8 hworden;
	u8 efuse_data, word_cnts;

	जबतक (continual && efuse_one_byte_पढ़ो(hw, efuse_addr, &efuse_data) &&
	       (efuse_addr < EFUSE_MAX_SIZE)) अणु
		अगर (efuse_data != 0xFF) अणु
			hworden = efuse_data & 0x0F;
			word_cnts = efuse_calculate_word_cnts(hworden);
			efuse_addr = efuse_addr + (word_cnts * 2) + 1;
		पूर्ण अन्यथा अणु
			continual = false;
		पूर्ण
	पूर्ण

	वापस efuse_addr;
पूर्ण

अटल u8 efuse_calculate_word_cnts(u8 word_en)
अणु
	u8 word_cnts = 0;

	अगर (!(word_en & BIT(0)))
		word_cnts++;
	अगर (!(word_en & BIT(1)))
		word_cnts++;
	अगर (!(word_en & BIT(2)))
		word_cnts++;
	अगर (!(word_en & BIT(3)))
		word_cnts++;
	वापस word_cnts;
पूर्ण

पूर्णांक rtl_get_hwinfo(काष्ठा ieee80211_hw *hw, काष्ठा rtl_priv *rtlpriv,
		   पूर्णांक max_size, u8 *hwinfo, पूर्णांक *params)
अणु
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_pci_priv *rtlpcipriv = rtl_pcipriv(hw);
	काष्ठा device *dev = &rtlpcipriv->dev.pdev->dev;
	u16 eeprom_id;
	u16 i, usvalue;

	चयन (rtlefuse->epromtype) अणु
	हाल EEPROM_BOOT_EFUSE:
		rtl_efuse_shaकरोw_map_update(hw);
		अवरोध;

	हाल EEPROM_93C46:
		pr_err("RTL8XXX did not boot from eeprom, check it !!\n");
		वापस 1;

	शेष:
		dev_warn(dev, "no efuse data\n");
		वापस 1;
	पूर्ण

	स_नकल(hwinfo, &rtlefuse->efuse_map[EFUSE_INIT_MAP][0], max_size);

	RT_PRINT_DATA(rtlpriv, COMP_INIT, DBG_DMESG, "MAP",
		      hwinfo, max_size);

	eeprom_id = *((u16 *)&hwinfo[0]);
	अगर (eeprom_id != params[0]) अणु
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
			"EEPROM ID(%#x) is invalid!!\n", eeprom_id);
		rtlefuse->स्वतःload_failflag = true;
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "Autoload OK\n");
		rtlefuse->स्वतःload_failflag = false;
	पूर्ण

	अगर (rtlefuse->स्वतःload_failflag)
		वापस 1;

	rtlefuse->eeprom_vid = *(u16 *)&hwinfo[params[1]];
	rtlefuse->eeprom_did = *(u16 *)&hwinfo[params[2]];
	rtlefuse->eeprom_svid = *(u16 *)&hwinfo[params[3]];
	rtlefuse->eeprom_smid = *(u16 *)&hwinfo[params[4]];
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"EEPROMId = 0x%4x\n", eeprom_id);
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"EEPROM VID = 0x%4x\n", rtlefuse->eeprom_vid);
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"EEPROM DID = 0x%4x\n", rtlefuse->eeprom_did);
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"EEPROM SVID = 0x%4x\n", rtlefuse->eeprom_svid);
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"EEPROM SMID = 0x%4x\n", rtlefuse->eeprom_smid);

	क्रम (i = 0; i < 6; i += 2) अणु
		usvalue = *(u16 *)&hwinfo[params[5] + i];
		*((u16 *)(&rtlefuse->dev_addr[i])) = usvalue;
	पूर्ण
	rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG, "%pM\n", rtlefuse->dev_addr);

	rtlefuse->eeprom_channelplan = *&hwinfo[params[6]];
	rtlefuse->eeprom_version = *(u16 *)&hwinfo[params[7]];
	rtlefuse->txpwr_fromeprom = true;
	rtlefuse->eeprom_oemid = *&hwinfo[params[8]];

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"EEPROM Customer ID: 0x%2x\n", rtlefuse->eeprom_oemid);

	/* set channel plan to world wide 13 */
	rtlefuse->channel_plan = params[9];

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rtl_get_hwinfo);

व्योम rtl_fw_block_ग_लिखो(काष्ठा ieee80211_hw *hw, स्थिर u8 *buffer, u32 size)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 *pu4byteptr = (u8 *)buffer;
	u32 i;

	क्रम (i = 0; i < size; i++)
		rtl_ग_लिखो_byte(rtlpriv, (START_ADDRESS + i), *(pu4byteptr + i));
पूर्ण
EXPORT_SYMBOL_GPL(rtl_fw_block_ग_लिखो);

व्योम rtl_fw_page_ग_लिखो(काष्ठा ieee80211_hw *hw, u32 page, स्थिर u8 *buffer,
		       u32 size)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 value8;
	u8 u8page = (u8)(page & 0x07);

	value8 = (rtl_पढ़ो_byte(rtlpriv, REG_MCUFWDL + 2) & 0xF8) | u8page;

	rtl_ग_लिखो_byte(rtlpriv, (REG_MCUFWDL + 2), value8);
	rtl_fw_block_ग_लिखो(hw, buffer, size);
पूर्ण
EXPORT_SYMBOL_GPL(rtl_fw_page_ग_लिखो);

व्योम rtl_fill_dummy(u8 *pfwbuf, u32 *pfwlen)
अणु
	u32 fwlen = *pfwlen;
	u8 reमुख्य = (u8)(fwlen % 4);

	reमुख्य = (reमुख्य == 0) ? 0 : (4 - reमुख्य);

	जबतक (reमुख्य > 0) अणु
		pfwbuf[fwlen] = 0;
		fwlen++;
		reमुख्य--;
	पूर्ण

	*pfwlen = fwlen;
पूर्ण
EXPORT_SYMBOL_GPL(rtl_fill_dummy);

व्योम rtl_efuse_ops_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->efuse.efuse_ops = &efuse_ops;
पूर्ण
EXPORT_SYMBOL_GPL(rtl_efuse_ops_init);
