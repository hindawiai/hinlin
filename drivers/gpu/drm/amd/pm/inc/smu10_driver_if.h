<शैली गुरु>
/*
 * Copyright 2017 Advanced Micro Devices, Inc.
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

#अगर_अघोषित SMU10_DRIVER_IF_H
#घोषणा SMU10_DRIVER_IF_H

#घोषणा SMU10_DRIVER_IF_VERSION 0x6

#घोषणा NUM_DSPCLK_LEVELS 8

प्रकार काष्ठा अणु
	पूर्णांक32_t value;
	uपूर्णांक32_t numFractionalBits;
पूर्ण FloatInIntFormat_t;

प्रकार क्रमागत अणु
	DSPCLK_DCEFCLK = 0,
	DSPCLK_DISPCLK,
	DSPCLK_PIXCLK,
	DSPCLK_PHYCLK,
	DSPCLK_COUNT,
पूर्ण DSPCLK_e;

प्रकार काष्ठा अणु
	uपूर्णांक16_t Freq;
	uपूर्णांक16_t Vid;
पूर्ण DisplayClockTable_t;


प्रकार काष्ठा अणु
	uपूर्णांक16_t MinClock; /* This is either DCFCLK or SOCCLK (in MHz) */
	uपूर्णांक16_t MaxClock; /* This is either DCFCLK or SOCCLK (in MHz) */
	uपूर्णांक16_t MinMclk;
	uपूर्णांक16_t MaxMclk;

	uपूर्णांक8_t  WmSetting;
	uपूर्णांक8_t  WmType;
	uपूर्णांक8_t  Padding[2];
पूर्ण WatermarkRowGeneric_t;

#घोषणा NUM_WM_RANGES 4

प्रकार क्रमागत अणु
	WM_SOCCLK = 0,
	WM_DCFCLK,
	WM_COUNT,
पूर्ण WM_CLOCK_e;

प्रकार काष्ठा अणु
	WatermarkRowGeneric_t WatermarkRow[WM_COUNT][NUM_WM_RANGES];
	uपूर्णांक32_t              MmHubPadding[7];
पूर्ण Watermarks_t;

प्रकार क्रमागत अणु
	CUSTOM_DPM_SETTING_GFXCLK,
	CUSTOM_DPM_SETTING_CCLK,
	CUSTOM_DPM_SETTING_FCLK_CCX,
	CUSTOM_DPM_SETTING_FCLK_GFX,
	CUSTOM_DPM_SETTING_FCLK_STALLS,
	CUSTOM_DPM_SETTING_LCLK,
	CUSTOM_DPM_SETTING_COUNT,
पूर्ण CUSTOM_DPM_SETTING_e;

प्रकार काष्ठा अणु
	uपूर्णांक8_t             ActiveHystLimit;
	uपूर्णांक8_t             IdleHystLimit;
	uपूर्णांक8_t             FPS;
	uपूर्णांक8_t             MinActiveFreqType;
	FloatInIntFormat_t  MinActiveFreq;
	FloatInIntFormat_t  PD_Data_limit;
	FloatInIntFormat_t  PD_Data_समय_स्थिरant;
	FloatInIntFormat_t  PD_Data_error_coeff;
	FloatInIntFormat_t  PD_Data_error_rate_coeff;
पूर्ण DpmActivityMonitorCoeffExt_t;

प्रकार काष्ठा अणु
	DpmActivityMonitorCoeffExt_t DpmActivityMonitorCoeff[CUSTOM_DPM_SETTING_COUNT];
पूर्ण CustomDpmSettings_t;

#घोषणा NUM_SOCCLK_DPM_LEVELS  8
#घोषणा NUM_DCEFCLK_DPM_LEVELS 4
#घोषणा NUM_FCLK_DPM_LEVELS    4
#घोषणा NUM_MEMCLK_DPM_LEVELS  4

प्रकार काष्ठा अणु
	uपूर्णांक32_t  Freq; /* In MHz */
	uपूर्णांक32_t  Vol;  /* Millivolts with 2 fractional bits */
पूर्ण DpmClock_t;

प्रकार काष्ठा अणु
	DpmClock_t DcefClocks[NUM_DCEFCLK_DPM_LEVELS];
	DpmClock_t SocClocks[NUM_SOCCLK_DPM_LEVELS];
	DpmClock_t FClocks[NUM_FCLK_DPM_LEVELS];
	DpmClock_t MemClocks[NUM_MEMCLK_DPM_LEVELS];
पूर्ण DpmClocks_t;

#पूर्ण_अगर
