<शैली गुरु>
/*
 *  Copyright 2020 Advanced Micro Devices, Inc.
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
 */
#अगर_अघोषित SMU_11_0_7_PPTABLE_H
#घोषणा SMU_11_0_7_PPTABLE_H


#घोषणा SMU_11_0_7_TABLE_FORMAT_REVISION                  15

//// POWERPLAYTABLE::ulPlatक्रमmCaps
#घोषणा SMU_11_0_7_PP_PLATFORM_CAP_POWERPLAY              0x1            // This cap indicates whether CCC need to show Powerplay page.
#घोषणा SMU_11_0_7_PP_PLATFORM_CAP_SBIOSPOWERSOURCE       0x2            // This cap indicates whether घातer source notअगरicaiton is करोne by SBIOS instead of OS.
#घोषणा SMU_11_0_7_PP_PLATFORM_CAP_HARDWAREDC             0x4            // This cap indicates whether DC mode notअगरicaiton is करोne by GPIO pin directly.
#घोषणा SMU_11_0_7_PP_PLATFORM_CAP_BACO                   0x8            // This cap indicates whether board supports the BACO circuitry.
#घोषणा SMU_11_0_7_PP_PLATFORM_CAP_MACO                   0x10           // This cap indicates whether board supports the MACO circuitry.
#घोषणा SMU_11_0_7_PP_PLATFORM_CAP_SHADOWPSTATE           0x20           // This cap indicates whether board supports the Shaकरोw Pstate.

// SMU_11_0_7_PP_THERMALCONTROLLER - Thermal Controller Type
#घोषणा SMU_11_0_7_PP_THERMALCONTROLLER_NONE              0
#घोषणा SMU_11_0_7_PP_THERMALCONTROLLER_SIENNA_CICHLID    28

#घोषणा SMU_11_0_7_PP_OVERDRIVE_VERSION                   0x81           // OverDrive 8 Table Version 0.2
#घोषणा SMU_11_0_7_PP_POWERSAVINGCLOCK_VERSION            0x01           // Power Saving Clock Table Version 1.00

क्रमागत SMU_11_0_7_ODFEATURE_CAP अणु
    SMU_11_0_7_ODCAP_GFXCLK_LIMITS = 0, 
    SMU_11_0_7_ODCAP_GFXCLK_CURVE,    
    SMU_11_0_7_ODCAP_UCLK_LIMITS,           
    SMU_11_0_7_ODCAP_POWER_LIMIT,        
    SMU_11_0_7_ODCAP_FAN_ACOUSTIC_LIMIT,   
    SMU_11_0_7_ODCAP_FAN_SPEED_MIN,       
    SMU_11_0_7_ODCAP_TEMPERATURE_FAN,     
    SMU_11_0_7_ODCAP_TEMPERATURE_SYSTEM,  
    SMU_11_0_7_ODCAP_MEMORY_TIMING_TUNE,  
    SMU_11_0_7_ODCAP_FAN_ZERO_RPM_CONTROL, 
    SMU_11_0_7_ODCAP_AUTO_UV_ENGINE,   
    SMU_11_0_7_ODCAP_AUTO_OC_ENGINE,     
    SMU_11_0_7_ODCAP_AUTO_OC_MEMORY,     
    SMU_11_0_7_ODCAP_FAN_CURVE,
    SMU_11_0_ODCAP_AUTO_FAN_ACOUSTIC_LIMIT,
    SMU_11_0_7_ODCAP_POWER_MODE,          
    SMU_11_0_7_ODCAP_COUNT,             
पूर्ण;

क्रमागत SMU_11_0_7_ODFEATURE_ID अणु
    SMU_11_0_7_ODFEATURE_GFXCLK_LIMITS         = 1 << SMU_11_0_7_ODCAP_GFXCLK_LIMITS,            //GFXCLK Limit feature
    SMU_11_0_7_ODFEATURE_GFXCLK_CURVE          = 1 << SMU_11_0_7_ODCAP_GFXCLK_CURVE,             //GFXCLK Curve feature
    SMU_11_0_7_ODFEATURE_UCLK_LIMITS           = 1 << SMU_11_0_7_ODCAP_UCLK_LIMITS,              //UCLK Limit feature
    SMU_11_0_7_ODFEATURE_POWER_LIMIT           = 1 << SMU_11_0_7_ODCAP_POWER_LIMIT,              //Power Limit feature
    SMU_11_0_7_ODFEATURE_FAN_ACOUSTIC_LIMIT    = 1 << SMU_11_0_7_ODCAP_FAN_ACOUSTIC_LIMIT,       //Fan Acoustic RPM feature
    SMU_11_0_7_ODFEATURE_FAN_SPEED_MIN         = 1 << SMU_11_0_7_ODCAP_FAN_SPEED_MIN,            //Minimum Fan Speed feature
    SMU_11_0_7_ODFEATURE_TEMPERATURE_FAN       = 1 << SMU_11_0_7_ODCAP_TEMPERATURE_FAN,          //Fan Target Temperature Limit feature
    SMU_11_0_7_ODFEATURE_TEMPERATURE_SYSTEM    = 1 << SMU_11_0_7_ODCAP_TEMPERATURE_SYSTEM,       //Operating Temperature Limit feature
    SMU_11_0_7_ODFEATURE_MEMORY_TIMING_TUNE    = 1 << SMU_11_0_7_ODCAP_MEMORY_TIMING_TUNE,       //AC Timing Tuning feature
    SMU_11_0_7_ODFEATURE_FAN_ZERO_RPM_CONTROL  = 1 << SMU_11_0_7_ODCAP_FAN_ZERO_RPM_CONTROL,     //Zero RPM feature
    SMU_11_0_7_ODFEATURE_AUTO_UV_ENGINE        = 1 << SMU_11_0_7_ODCAP_AUTO_UV_ENGINE,           //Auto Under Volt GFXCLK feature
    SMU_11_0_7_ODFEATURE_AUTO_OC_ENGINE        = 1 << SMU_11_0_7_ODCAP_AUTO_OC_ENGINE,           //Auto Over Clock GFXCLK feature
    SMU_11_0_7_ODFEATURE_AUTO_OC_MEMORY        = 1 << SMU_11_0_7_ODCAP_AUTO_OC_MEMORY,           //Auto Over Clock MCLK feature
    SMU_11_0_7_ODFEATURE_FAN_CURVE             = 1 << SMU_11_0_7_ODCAP_FAN_CURVE,                //Fan Curve feature
    SMU_11_0_ODFEATURE_AUTO_FAN_ACOUSTIC_LIMIT = 1 << SMU_11_0_ODCAP_AUTO_FAN_ACOUSTIC_LIMIT,  //Auto Fan Acoustic RPM feature
    SMU_11_0_7_ODFEATURE_POWER_MODE            = 1 << SMU_11_0_7_ODCAP_POWER_MODE,               //Optimized GPU Power Mode feature
    SMU_11_0_7_ODFEATURE_COUNT                 = 16,
पूर्ण;

#घोषणा SMU_11_0_7_MAX_ODFEATURE    32          //Maximum Number of OD Features

क्रमागत SMU_11_0_7_ODSETTING_ID अणु
    SMU_11_0_7_ODSETTING_GFXCLKFMAX = 0,
    SMU_11_0_7_ODSETTING_GFXCLKFMIN,
    SMU_11_0_7_ODSETTING_CUSTOM_GFX_VF_CURVE_A,
    SMU_11_0_7_ODSETTING_CUSTOM_GFX_VF_CURVE_B,
    SMU_11_0_7_ODSETTING_CUSTOM_GFX_VF_CURVE_C,
    SMU_11_0_7_ODSETTING_CUSTOM_CURVE_VFT_FMIN,
    SMU_11_0_7_ODSETTING_UCLKFMIN,
    SMU_11_0_7_ODSETTING_UCLKFMAX,
    SMU_11_0_7_ODSETTING_POWERPERCENTAGE,
    SMU_11_0_7_ODSETTING_FANRPMMIN,
    SMU_11_0_7_ODSETTING_FANRPMACOUSTICLIMIT,
    SMU_11_0_7_ODSETTING_FANTARGETTEMPERATURE,
    SMU_11_0_7_ODSETTING_OPERATINGTEMPMAX,
    SMU_11_0_7_ODSETTING_ACTIMING,
    SMU_11_0_7_ODSETTING_FAN_ZERO_RPM_CONTROL,
    SMU_11_0_7_ODSETTING_AUTOUVENGINE,
    SMU_11_0_7_ODSETTING_AUTOOCENGINE,
    SMU_11_0_7_ODSETTING_AUTOOCMEMORY,
    SMU_11_0_7_ODSETTING_FAN_CURVE_TEMPERATURE_1,
    SMU_11_0_7_ODSETTING_FAN_CURVE_SPEED_1,
    SMU_11_0_7_ODSETTING_FAN_CURVE_TEMPERATURE_2,
    SMU_11_0_7_ODSETTING_FAN_CURVE_SPEED_2,
    SMU_11_0_7_ODSETTING_FAN_CURVE_TEMPERATURE_3,
    SMU_11_0_7_ODSETTING_FAN_CURVE_SPEED_3,
    SMU_11_0_7_ODSETTING_FAN_CURVE_TEMPERATURE_4,
    SMU_11_0_7_ODSETTING_FAN_CURVE_SPEED_4,
    SMU_11_0_7_ODSETTING_FAN_CURVE_TEMPERATURE_5,
    SMU_11_0_7_ODSETTING_FAN_CURVE_SPEED_5,
    SMU_11_0_7_ODSETTING_AUTO_FAN_ACOUSTIC_LIMIT,
    SMU_11_0_7_ODSETTING_POWER_MODE,
    SMU_11_0_7_ODSETTING_COUNT,
पूर्ण;
#घोषणा SMU_11_0_7_MAX_ODSETTING    64          //Maximum Number of ODSettings

क्रमागत SMU_11_0_7_PWRMODE_SETTING अणु
    SMU_11_0_7_PMSETTING_POWER_LIMIT_QUIET = 0,
    SMU_11_0_7_PMSETTING_POWER_LIMIT_BALANCE,
    SMU_11_0_7_PMSETTING_POWER_LIMIT_TURBO,
    SMU_11_0_7_PMSETTING_POWER_LIMIT_RAGE,
    SMU_11_0_7_PMSETTING_ACOUSTIC_TEMP_QUIET,
    SMU_11_0_7_PMSETTING_ACOUSTIC_TEMP_BALANCE,
    SMU_11_0_7_PMSETTING_ACOUSTIC_TEMP_TURBO,
    SMU_11_0_7_PMSETTING_ACOUSTIC_TEMP_RAGE,
पूर्ण;
#घोषणा SMU_11_0_7_MAX_PMSETTING      32        //Maximum Number of PowerMode Settings

काष्ठा smu_11_0_7_overdrive_table
अणु
    uपूर्णांक8_t  revision;                                        //Revision = SMU_11_0_7_PP_OVERDRIVE_VERSION
    uपूर्णांक8_t  reserve[3];                                      //Zero filled field reserved क्रम future use
    uपूर्णांक32_t feature_count;                                   //Total number of supported features
    uपूर्णांक32_t setting_count;                                   //Total number of supported settings
    uपूर्णांक8_t  cap[SMU_11_0_7_MAX_ODFEATURE];                   //OD feature support flags
    uपूर्णांक32_t max[SMU_11_0_7_MAX_ODSETTING];                   //शेष maximum settings
    uपूर्णांक32_t min[SMU_11_0_7_MAX_ODSETTING];                   //शेष minimum settings
    पूर्णांक16_t  pm_setting[SMU_11_0_7_MAX_PMSETTING];            //Optimized घातer mode feature settings
पूर्ण __attribute__((packed));

क्रमागत SMU_11_0_7_PPCLOCK_ID अणु
    SMU_11_0_7_PPCLOCK_GFXCLK = 0,
    SMU_11_0_7_PPCLOCK_SOCCLK,
    SMU_11_0_7_PPCLOCK_UCLK,
    SMU_11_0_7_PPCLOCK_FCLK,
    SMU_11_0_7_PPCLOCK_DCLK_0,
    SMU_11_0_7_PPCLOCK_VCLK_0,
    SMU_11_0_7_PPCLOCK_DCLK_1,
    SMU_11_0_7_PPCLOCK_VCLK_1,
    SMU_11_0_7_PPCLOCK_DCEFCLK,
    SMU_11_0_7_PPCLOCK_DISPCLK,
    SMU_11_0_7_PPCLOCK_PIXCLK,
    SMU_11_0_7_PPCLOCK_PHYCLK,
    SMU_11_0_7_PPCLOCK_DTBCLK,
    SMU_11_0_7_PPCLOCK_COUNT,
पूर्ण;
#घोषणा SMU_11_0_7_MAX_PPCLOCK      16          //Maximum Number of PP Clocks

काष्ठा smu_11_0_7_घातer_saving_घड़ी_प्रकारable
अणु
    uपूर्णांक8_t  revision;                                        //Revision = SMU_11_0_7_PP_POWERSAVINGCLOCK_VERSION
    uपूर्णांक8_t  reserve[3];                                      //Zero filled field reserved क्रम future use
    uपूर्णांक32_t count;                                           //घातer_saving_घड़ी_count = SMU_11_0_7_PPCLOCK_COUNT
    uपूर्णांक32_t max[SMU_11_0_7_MAX_PPCLOCK];                       //PowerSavingClock Mode Clock Maximum array In MHz
    uपूर्णांक32_t min[SMU_11_0_7_MAX_PPCLOCK];                       //PowerSavingClock Mode Clock Minimum array In MHz
पूर्ण __attribute__((packed));

काष्ठा smu_11_0_7_घातerplay_table
अणु
      काष्ठा atom_common_table_header header;       //For sienna_cichlid, header.क्रमmat_revision = 15, header.content_revision = 0
      uपूर्णांक8_t  table_revision;                      //For sienna_cichlid, table_revision = 2
      uपूर्णांक16_t table_size;                          //Driver portion table size. The offset to smc_pptable including header size
      uपूर्णांक32_t golden_pp_id;                        //PPGen use only: PP Table ID on the Golden Data Base
      uपूर्णांक32_t golden_revision;                     //PPGen use only: PP Table Revision on the Golden Data Base
      uपूर्णांक16_t क्रमmat_id;                           //PPGen use only: PPTable क्रम dअगरferent ASICs. For sienna_cichlid this should be 0x80
      uपूर्णांक32_t platक्रमm_caps;                       //POWERPLAYABLE::ulPlatक्रमmCaps
                                                    
      uपूर्णांक8_t  thermal_controller_type;             //one of SMU_11_0_7_PP_THERMALCONTROLLER

      uपूर्णांक16_t small_घातer_limit1;
      uपूर्णांक16_t small_घातer_limit2;
      uपूर्णांक16_t boost_घातer_limit;                   //For Gemini Board, when the slave adapter is in BACO mode, the master adapter will use this boost घातer limit instead of the शेष घातer limit to boost the घातer limit.
      uपूर्णांक16_t software_shutकरोwn_temp;

      uपूर्णांक16_t reserve[8];                          //Zero filled field reserved क्रम future use

      काष्ठा smu_11_0_7_घातer_saving_घड़ी_प्रकारable      घातer_saving_घड़ी;
      काष्ठा smu_11_0_7_overdrive_table               overdrive_table;

      PPTable_t smc_pptable;                        //PPTable_t in smu11_driver_अगर.h
पूर्ण __attribute__((packed));

#पूर्ण_अगर
