<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#अगर_अघोषित VEGA10_PROCESSPPTABLES_H
#घोषणा VEGA10_PROCESSPPTABLES_H

#समावेश "hwmgr.h"

क्रमागत Vega10_I2CLineID अणु
	Vega10_I2CLineID_DDC1 = 0x90,
	Vega10_I2CLineID_DDC2 = 0x91,
	Vega10_I2CLineID_DDC3 = 0x92,
	Vega10_I2CLineID_DDC4 = 0x93,
	Vega10_I2CLineID_DDC5 = 0x94,
	Vega10_I2CLineID_DDC6 = 0x95,
	Vega10_I2CLineID_SCLSDA = 0x96,
	Vega10_I2CLineID_DDCVGA = 0x97
पूर्ण;

#घोषणा Vega10_I2C_DDC1DATA          0
#घोषणा Vega10_I2C_DDC1CLK           1
#घोषणा Vega10_I2C_DDC2DATA          2
#घोषणा Vega10_I2C_DDC2CLK           3
#घोषणा Vega10_I2C_DDC3DATA          4
#घोषणा Vega10_I2C_DDC3CLK           5
#घोषणा Vega10_I2C_SDA               40
#घोषणा Vega10_I2C_SCL               41
#घोषणा Vega10_I2C_DDC4DATA          65
#घोषणा Vega10_I2C_DDC4CLK           66
#घोषणा Vega10_I2C_DDC5DATA          0x48
#घोषणा Vega10_I2C_DDC5CLK           0x49
#घोषणा Vega10_I2C_DDC6DATA          0x4a
#घोषणा Vega10_I2C_DDC6CLK           0x4b
#घोषणा Vega10_I2C_DDCVGADATA        0x4c
#घोषणा Vega10_I2C_DDCVGACLK         0x4d

बाह्य स्थिर काष्ठा pp_table_func vega10_pptable_funcs;
बाह्य पूर्णांक vega10_get_number_of_घातerplay_table_entries(काष्ठा pp_hwmgr *hwmgr);
बाह्य पूर्णांक vega10_get_घातerplay_table_entry(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t entry_index,
		काष्ठा pp_घातer_state *घातer_state, पूर्णांक (*call_back_func)(काष्ठा pp_hwmgr *, व्योम *,
				काष्ठा pp_घातer_state *, व्योम *, uपूर्णांक32_t));
बाह्य पूर्णांक vega10_baco_set_cap(काष्ठा pp_hwmgr *hwmgr);
#पूर्ण_अगर
