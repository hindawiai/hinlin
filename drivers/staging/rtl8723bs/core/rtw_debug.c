<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTW_DEBUG_C_

#समावेश <drv_types.h>
#समावेश <rtw_debug.h>
#समावेश <hal_btcoex.h>

u32 GlobalDebugLevel = _drv_err_;

#समावेश <rtw_version.h>

व्योम sd_f0_reg_dump(व्योम *sel, काष्ठा adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0x0; i <= 0xff; i++) अणु
		अगर (i%16 == 0)
			netdev_dbg(adapter->pnetdev, "0x%02x ", i);

		DBG_871X_SEL(sel, "%02x ", rtw_sd_f0_पढ़ो8(adapter, i));

		अगर (i%16 == 15)
			DBG_871X_SEL(sel, "\n");
		अन्यथा अगर (i%8 == 7)
			DBG_871X_SEL(sel, "\t");
	पूर्ण
पूर्ण

व्योम mac_reg_dump(व्योम *sel, काष्ठा adapter *adapter)
अणु
	पूर्णांक i, j = 1;

	netdev_dbg(adapter->pnetdev, "======= MAC REG =======\n");

	क्रम (i = 0x0; i < 0x800; i += 4) अणु
		अगर (j%4 == 1)
			netdev_dbg(adapter->pnetdev, "0x%03x", i);
		DBG_871X_SEL(sel, " 0x%08x ", rtw_पढ़ो32(adapter, i));
		अगर ((j++)%4 == 0)
			DBG_871X_SEL(sel, "\n");
	पूर्ण
पूर्ण

व्योम bb_reg_dump(व्योम *sel, काष्ठा adapter *adapter)
अणु
	पूर्णांक i, j = 1;

	netdev_dbg(adapter->pnetdev, "======= BB REG =======\n");
	क्रम (i = 0x800; i < 0x1000 ; i += 4) अणु
		अगर (j%4 == 1)
			netdev_dbg(adapter->pnetdev, "0x%03x", i);
		DBG_871X_SEL(sel, " 0x%08x ", rtw_पढ़ो32(adapter, i));
		अगर ((j++)%4 == 0)
			DBG_871X_SEL(sel, "\n");
	पूर्ण
पूर्ण

व्योम rf_reg_dump(व्योम *sel, काष्ठा adapter *adapter)
अणु
	पूर्णांक i, j = 1, path;
	u32 value;
	u8 rf_type = 0;
	u8 path_nums = 0;

	rtw_hal_get_hwreg(adapter, HW_VAR_RF_TYPE, (u8 *)(&rf_type));
	अगर ((RF_1T2R == rf_type) || (RF_1T1R == rf_type))
		path_nums = 1;
	अन्यथा
		path_nums = 2;

	netdev_dbg(adapter->pnetdev, "======= RF REG =======\n");

	क्रम (path = 0; path < path_nums; path++) अणु
		netdev_dbg(adapter->pnetdev, "RF_Path(%x)\n", path);
		क्रम (i = 0; i < 0x100; i++) अणु
			value = rtw_hal_पढ़ो_rfreg(adapter, path, i, 0xffffffff);
			अगर (j%4 == 1)
				netdev_dbg(adapter->pnetdev, "0x%02x ", i);
			DBG_871X_SEL(sel, " 0x%08x ", value);
			अगर ((j++)%4 == 0)
				DBG_871X_SEL(sel, "\n");
		पूर्ण
	पूर्ण
पूर्ण
