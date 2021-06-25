<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#समावेश "odm_precomp.h"

#समावेश <phy.h>

अटल bool check_condition(काष्ठा adapter *adapt, स्थिर u32  condition)
अणु
	काष्ठा odm_dm_काष्ठा *odm = &adapt->HalData->odmpriv;
	u32 _board = odm->BoardType;
	u32 _platक्रमm = odm->SupportPlatक्रमm;
	u32 _पूर्णांकerface = odm->SupportInterface;
	u32 cond;

	अगर (condition == 0xCDCDCDCD)
		वापस true;

	cond = condition & 0x000000FF;
	अगर ((_board == cond) && cond != 0x00)
		वापस false;

	cond = condition & 0x0000FF00;
	cond >>= 8;
	अगर ((_पूर्णांकerface & cond) == 0 && cond != 0x07)
		वापस false;

	cond = condition & 0x00FF0000;
	cond >>= 16;
	अगर ((_platक्रमm & cond) == 0 && cond != 0x0F)
		वापस false;
	वापस true;
पूर्ण

/* RadioA_1T.TXT */

अटल u32 Array_RadioA_1T_8188E[] = अणु
		0x000, 0x00030000,
		0x008, 0x00084000,
		0x018, 0x00000407,
		0x019, 0x00000012,
		0x01E, 0x00080009,
		0x01F, 0x00000880,
		0x02F, 0x0001A060,
		0x03F, 0x00000000,
		0x042, 0x000060C0,
		0x057, 0x000D0000,
		0x058, 0x000BE180,
		0x067, 0x00001552,
		0x083, 0x00000000,
		0x0B0, 0x000FF8FC,
		0x0B1, 0x00054400,
		0x0B2, 0x000CCC19,
		0x0B4, 0x00043003,
		0x0B6, 0x0004953E,
		0x0B7, 0x0001C718,
		0x0B8, 0x000060FF,
		0x0B9, 0x00080001,
		0x0BA, 0x00040000,
		0x0BB, 0x00000400,
		0x0BF, 0x000C0000,
		0x0C2, 0x00002400,
		0x0C3, 0x00000009,
		0x0C4, 0x00040C91,
		0x0C5, 0x00099999,
		0x0C6, 0x000000A3,
		0x0C7, 0x00088820,
		0x0C8, 0x00076C06,
		0x0C9, 0x00000000,
		0x0CA, 0x00080000,
		0x0DF, 0x00000180,
		0x0EF, 0x000001A0,
		0x051, 0x0006B27D,
		0xFF0F041F, 0xABCD,
		0x052, 0x0007E4DD,
		0xCDCDCDCD, 0xCDCD,
		0x052, 0x0007E49D,
		0xFF0F041F, 0xDEAD,
		0x053, 0x00000073,
		0x056, 0x00051FF3,
		0x035, 0x00000086,
		0x035, 0x00000186,
		0x035, 0x00000286,
		0x036, 0x00001C25,
		0x036, 0x00009C25,
		0x036, 0x00011C25,
		0x036, 0x00019C25,
		0x0B6, 0x00048538,
		0x018, 0x00000C07,
		0x05A, 0x0004BD00,
		0x019, 0x000739D0,
		0x034, 0x0000ADF3,
		0x034, 0x00009DF0,
		0x034, 0x00008DED,
		0x034, 0x00007DEA,
		0x034, 0x00006DE7,
		0x034, 0x000054EE,
		0x034, 0x000044EB,
		0x034, 0x000034E8,
		0x034, 0x0000246B,
		0x034, 0x00001468,
		0x034, 0x0000006D,
		0x000, 0x00030159,
		0x084, 0x00068200,
		0x086, 0x000000CE,
		0x087, 0x00048A00,
		0x08E, 0x00065540,
		0x08F, 0x00088000,
		0x0EF, 0x000020A0,
		0x03B, 0x000F02B0,
		0x03B, 0x000EF7B0,
		0x03B, 0x000D4FB0,
		0x03B, 0x000CF060,
		0x03B, 0x000B0090,
		0x03B, 0x000A0080,
		0x03B, 0x00090080,
		0x03B, 0x0008F780,
		0x03B, 0x000722B0,
		0x03B, 0x0006F7B0,
		0x03B, 0x00054FB0,
		0x03B, 0x0004F060,
		0x03B, 0x00030090,
		0x03B, 0x00020080,
		0x03B, 0x00010080,
		0x03B, 0x0000F780,
		0x0EF, 0x000000A0,
		0x000, 0x00010159,
		0x018, 0x0000F407,
		0xFFE, 0x00000000,
		0xFFE, 0x00000000,
		0x01F, 0x00080003,
		0xFFE, 0x00000000,
		0xFFE, 0x00000000,
		0x01E, 0x00000001,
		0x01F, 0x00080000,
		0x000, 0x00033E60,
पूर्ण;

#घोषणा READ_NEXT_PAIR(v1, v2, i)	\
करो अणु								\
	i += 2; v1 = array[i];			\
	v2 = array[i + 1];				\
पूर्ण जबतक (0)

#घोषणा RFREG_OFFSET_MASK 0xfffff
#घोषणा B3WIREADDREAALENGTH 0x400
#घोषणा B3WIREDATALENGTH 0x800
#घोषणा BRFSI_RFENV 0x10

अटल व्योम rtl_rfreg_delay(काष्ठा adapter *adapt, क्रमागत rf_radio_path rfpath, u32 addr, u32 mask, u32 data)
अणु
	अगर (addr == 0xfe) अणु
		mdelay(50);
	पूर्ण अन्यथा अगर (addr == 0xfd) अणु
		mdelay(5);
	पूर्ण अन्यथा अगर (addr == 0xfc) अणु
		mdelay(1);
	पूर्ण अन्यथा अगर (addr == 0xfb) अणु
		udelay(50);
	पूर्ण अन्यथा अगर (addr == 0xfa) अणु
		udelay(5);
	पूर्ण अन्यथा अगर (addr == 0xf9) अणु
		udelay(1);
	पूर्ण अन्यथा अणु
		phy_set_rf_reg(adapt, rfpath, addr, mask, data);
		udelay(1);
	पूर्ण
पूर्ण

अटल व्योम rtl8188e_config_rf_reg(काष्ठा adapter *adapt, u32 addr, u32 data)
अणु
	u32 content = 0x1000; /*RF Content: radio_a_txt*/
	u32 maskक्रमphyset = content & 0xE000;

	rtl_rfreg_delay(adapt, RF_PATH_A, addr | maskक्रमphyset,
			RFREG_OFFSET_MASK,
			data);
पूर्ण

अटल bool rtl88e_phy_config_rf_with_headerfile(काष्ठा adapter *adapt)
अणु
	u32 i;
	u32 array_len = ARRAY_SIZE(Array_RadioA_1T_8188E);
	u32 *array = Array_RadioA_1T_8188E;

	क्रम (i = 0; i < array_len; i += 2) अणु
		u32 v1 = array[i];
		u32 v2 = array[i + 1];

		अगर (v1 < 0xCDCDCDCD) अणु
			rtl8188e_config_rf_reg(adapt, v1, v2);
			जारी;
		पूर्ण अन्यथा अणु
			अगर (!check_condition(adapt, array[i])) अणु
				READ_NEXT_PAIR(v1, v2, i);
				जबतक (v2 != 0xDEAD && v2 != 0xCDEF &&
				       v2 != 0xCDCD && i < array_len - 2)
					READ_NEXT_PAIR(v1, v2, i);
				i -= 2;
			पूर्ण अन्यथा अणु
				READ_NEXT_PAIR(v1, v2, i);
				जबतक (v2 != 0xDEAD && v2 != 0xCDEF &&
				       v2 != 0xCDCD && i < array_len - 2) अणु
					rtl8188e_config_rf_reg(adapt, v1, v2);
					READ_NEXT_PAIR(v1, v2, i);
				पूर्ण

				जबतक (v2 != 0xDEAD && i < array_len - 2)
					READ_NEXT_PAIR(v1, v2, i);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

bool rtl88eu_phy_rf_config(काष्ठा adapter *adapt)
अणु
	काष्ठा hal_data_8188e *hal_data = adapt->HalData;
	u32 u4val = 0;
	bool rtstatus;
	काष्ठा bb_reg_def *pphyreg;

	pphyreg = &hal_data->PHYRegDef[RF90_PATH_A];
	u4val = phy_query_bb_reg(adapt, pphyreg->rfपूर्णांकfs, BRFSI_RFENV);

	phy_set_bb_reg(adapt, pphyreg->rfपूर्णांकfe, BRFSI_RFENV << 16, 0x1);
	udelay(1);

	phy_set_bb_reg(adapt, pphyreg->rfपूर्णांकfo, BRFSI_RFENV, 0x1);
	udelay(1);

	phy_set_bb_reg(adapt, pphyreg->rfHSSIPara2, B3WIREADDREAALENGTH, 0x0);
	udelay(1);

	phy_set_bb_reg(adapt, pphyreg->rfHSSIPara2, B3WIREDATALENGTH, 0x0);
	udelay(1);

	rtstatus = rtl88e_phy_config_rf_with_headerfile(adapt);

	phy_set_bb_reg(adapt, pphyreg->rfपूर्णांकfs, BRFSI_RFENV, u4val);

	वापस rtstatus;
पूर्ण
