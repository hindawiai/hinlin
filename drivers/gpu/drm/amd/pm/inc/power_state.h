<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
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
#अगर_अघोषित PP_POWERSTATE_H
#घोषणा PP_POWERSTATE_H

काष्ठा pp_hw_घातer_state अणु
	अचिन्हित पूर्णांक magic;
पूर्ण;

काष्ठा pp_घातer_state;


#घोषणा PP_INVALID_POWER_STATE_ID (0)


/*
 * An item of a list containing Power States.
 */

काष्ठा PP_StateLinkedList अणु
	काष्ठा pp_घातer_state *next;
	काष्ठा pp_घातer_state *prev;
पूर्ण;


क्रमागत PP_StateUILabel अणु
	PP_StateUILabel_None,
	PP_StateUILabel_Battery,
	PP_StateUILabel_MiddleLow,
	PP_StateUILabel_Balanced,
	PP_StateUILabel_MiddleHigh,
	PP_StateUILabel_Perक्रमmance,
	PP_StateUILabel_BACO
पूर्ण;

क्रमागत PP_StateClassअगरicationFlag अणु
	PP_StateClassअगरicationFlag_Boot                = 0x0001,
	PP_StateClassअगरicationFlag_Thermal             = 0x0002,
	PP_StateClassअगरicationFlag_LimitedPowerSource  = 0x0004,
	PP_StateClassअगरicationFlag_Rest                = 0x0008,
	PP_StateClassअगरicationFlag_Forced              = 0x0010,
	PP_StateClassअगरicationFlag_User3DPerक्रमmance   = 0x0020,
	PP_StateClassअगरicationFlag_User2DPerक्रमmance   = 0x0040,
	PP_StateClassअगरicationFlag_3DPerक्रमmance       = 0x0080,
	PP_StateClassअगरicationFlag_ACOverdriveTemplate   = 0x0100,
	PP_StateClassअगरicationFlag_Uvd                 = 0x0200,
	PP_StateClassअगरicationFlag_3DPerक्रमmanceLow    = 0x0400,
	PP_StateClassअगरicationFlag_ACPI                = 0x0800,
	PP_StateClassअगरicationFlag_HD2                 = 0x1000,
	PP_StateClassअगरicationFlag_UvdHD               = 0x2000,
	PP_StateClassअगरicationFlag_UvdSD               = 0x4000,
	PP_StateClassअगरicationFlag_UserDCPerक्रमmance    = 0x8000,
	PP_StateClassअगरicationFlag_DCOverdriveTemplate   = 0x10000,
	PP_StateClassअगरicationFlag_BACO                  = 0x20000,
	PP_StateClassअगरicationFlag_LimitedPowerSource_2  = 0x40000,
	PP_StateClassअगरicationFlag_ULV                   = 0x80000,
	PP_StateClassअगरicationFlag_UvdMVC               = 0x100000,
पूर्ण;

प्रकार अचिन्हित पूर्णांक PP_StateClassअगरicationFlags;

काष्ठा PP_StateClassअगरicationBlock अणु
	क्रमागत PP_StateUILabel         ui_label;
	क्रमागत PP_StateClassअगरicationFlag  flags;
	पूर्णांक                          bios_index;
	bool                      temporary_state;
	bool                      to_be_deleted;
पूर्ण;

काष्ठा PP_StatePcieBlock अणु
	अचिन्हित पूर्णांक lanes;
पूर्ण;

क्रमागत PP_RefreshrateSource अणु
	PP_RefreshrateSource_EDID,
	PP_RefreshrateSource_Explicit
पूर्ण;

काष्ठा PP_StateDisplayBlock अणु
	bool              disableFrameModulation;
	bool              limitRefreshrate;
	क्रमागत PP_RefreshrateSource refreshrateSource;
	पूर्णांक                  explicitRefreshrate;
	पूर्णांक                  edidRefreshrateIndex;
	bool              enableVariBright;
पूर्ण;

काष्ठा PP_StateMemroyBlock अणु
	bool              dllOff;
	uपूर्णांक8_t                 m3arb;
	uपूर्णांक8_t                 unused[3];
पूर्ण;

काष्ठा PP_StateSoftwareAlgorithmBlock अणु
	bool disableLoadBalancing;
	bool enableSleepForTimestamps;
पूर्ण;

#घोषणा PP_TEMPERATURE_UNITS_PER_CENTIGRADES 1000

/**
 * Type to hold a temperature range.
 */
काष्ठा PP_TemperatureRange अणु
	पूर्णांक min;
	पूर्णांक max;
	पूर्णांक edge_emergency_max;
	पूर्णांक hotspot_min;
	पूर्णांक hotspot_crit_max;
	पूर्णांक hotspot_emergency_max;
	पूर्णांक mem_min;
	पूर्णांक mem_crit_max;
	पूर्णांक mem_emergency_max;
पूर्ण;

काष्ठा PP_StateValidationBlock अणु
	bool singleDisplayOnly;
	bool disallowOnDC;
	uपूर्णांक8_t supportedPowerLevels;
पूर्ण;

काष्ठा PP_UVD_CLOCKS अणु
	uपूर्णांक32_t VCLK;
	uपूर्णांक32_t DCLK;
पूर्ण;

/**
* Structure to hold a PowerPlay Power State.
*/
काष्ठा pp_घातer_state अणु
	uपूर्णांक32_t                            id;
	काष्ठा PP_StateLinkedList                  orderedList;
	काष्ठा PP_StateLinkedList                  allStatesList;

	काष्ठा PP_StateClassअगरicationBlock         classअगरication;
	काष्ठा PP_StateValidationBlock             validation;
	काष्ठा PP_StatePcieBlock                   pcie;
	काष्ठा PP_StateDisplayBlock                display;
	काष्ठा PP_StateMemroyBlock                 memory;
	काष्ठा PP_TemperatureRange                 temperatures;
	काष्ठा PP_StateSoftwareAlgorithmBlock      software;
	काष्ठा PP_UVD_CLOCKS                       uvd_घड़ीs;
	काष्ठा pp_hw_घातer_state  hardware;
पूर्ण;

क्रमागत PP_MMProfilingState अणु
	PP_MMProfilingState_NA = 0,
	PP_MMProfilingState_Started,
	PP_MMProfilingState_Stopped
पूर्ण;

काष्ठा pp_घड़ी_engine_request अणु
	अचिन्हित दीर्घ client_type;
	अचिन्हित दीर्घ ctx_id;
	uपूर्णांक64_t  context_handle;
	अचिन्हित दीर्घ sclk;
	अचिन्हित दीर्घ sclk_hard_min;
	अचिन्हित दीर्घ mclk;
	अचिन्हित दीर्घ iclk;
	अचिन्हित दीर्घ evclk;
	अचिन्हित दीर्घ ecclk;
	अचिन्हित दीर्घ ecclk_hard_min;
	अचिन्हित दीर्घ vclk;
	अचिन्हित दीर्घ dclk;
	अचिन्हित दीर्घ sclk_over_drive;
	अचिन्हित दीर्घ mclk_over_drive;
	अचिन्हित दीर्घ sclk_threshold;
	अचिन्हित दीर्घ flag;
	अचिन्हित दीर्घ vclk_उच्चमानing;
	अचिन्हित दीर्घ dclk_उच्चमानing;
	अचिन्हित दीर्घ num_cus;
	अचिन्हित दीर्घ pm_flag;
	क्रमागत PP_MMProfilingState mm_profiling_state;
पूर्ण;

#पूर्ण_अगर
