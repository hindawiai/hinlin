<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * LP8727 Micro/Mini USB IC with पूर्णांकegrated अक्षरger
 *
 *			Copyright (C) 2011 Texas Instruments
 *			Copyright (C) 2011 National Semiconductor
 */

#अगर_अघोषित _LP8727_H
#घोषणा _LP8727_H

क्रमागत lp8727_eoc_level अणु
	LP8727_EOC_5P,
	LP8727_EOC_10P,
	LP8727_EOC_16P,
	LP8727_EOC_20P,
	LP8727_EOC_25P,
	LP8727_EOC_33P,
	LP8727_EOC_50P,
पूर्ण;

क्रमागत lp8727_ichg अणु
	LP8727_ICHG_90mA,
	LP8727_ICHG_100mA,
	LP8727_ICHG_400mA,
	LP8727_ICHG_450mA,
	LP8727_ICHG_500mA,
	LP8727_ICHG_600mA,
	LP8727_ICHG_700mA,
	LP8727_ICHG_800mA,
	LP8727_ICHG_900mA,
	LP8727_ICHG_1000mA,
पूर्ण;

/**
 * काष्ठा lp8727_chg_param
 * @eoc_level : end of अक्षरge level setting
 * @ichg      : अक्षरging current
 */
काष्ठा lp8727_chg_param अणु
	क्रमागत lp8727_eoc_level eoc_level;
	क्रमागत lp8727_ichg ichg;
पूर्ण;

/**
 * काष्ठा lp8727_platक्रमm_data
 * @get_batt_present  : check battery status - exists or not
 * @get_batt_level    : get battery voltage (mV)
 * @get_batt_capacity : get battery capacity (%)
 * @get_batt_temp     : get battery temperature
 * @ac                : अक्षरging parameters क्रम AC type अक्षरger
 * @usb               : अक्षरging parameters क्रम USB type अक्षरger
 * @debounce_msec     : पूर्णांकerrupt debounce समय
 */
काष्ठा lp8727_platक्रमm_data अणु
	u8 (*get_batt_present)(व्योम);
	u16 (*get_batt_level)(व्योम);
	u8 (*get_batt_capacity)(व्योम);
	u8 (*get_batt_temp)(व्योम);
	काष्ठा lp8727_chg_param *ac;
	काष्ठा lp8727_chg_param *usb;
	अचिन्हित पूर्णांक debounce_msec;
पूर्ण;

#पूर्ण_अगर
