<शैली गुरु>
/*
  Copyright (c), 2004-2005,2007-2010 Trident Microप्रणालीs, Inc.
  All rights reserved.

  Redistribution and use in source and binary क्रमms, with or without
  modअगरication, are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
  * Redistributions in binary क्रमm must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the करोcumentation
	and/or other materials provided with the distribution.
  * Neither the name of Trident Microप्रणालीs nor Hauppauge Computer Works
    nor the names of its contributors may be used to enकरोrse or promote
	products derived from this software without specअगरic prior written
	permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
  LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.

  DRXJ specअगरic implementation of DRX driver
  authors: Dragan Savic, Milos Nikolic, Mihajlo Katona, Tao Ding, Paul Janssen

  The Linux DVB Driver क्रम Micronas DRX39xx family (drx3933j) was
  written by Devin Heiपंचांगueller <devin.heiपंचांगueller@kernelद_असल.com>

  This program is मुक्त software; you can redistribute it and/or modअगरy
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the

  GNU General Public License क्रम more details.

  You should have received a copy of the GNU General Public License
  aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

/*-----------------------------------------------------------------------------
INCLUDE खाताS
----------------------------------------------------------------------------*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s: " fmt, __func__

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <यंत्र/भाग64.h>

#समावेश <media/dvb_frontend.h>
#समावेश "drx39xxj.h"

#समावेश "drxj.h"
#समावेश "drxj_map.h"

/*============================================================================*/
/*=== DEFINES ================================================================*/
/*============================================================================*/

#घोषणा DRX39XX_MAIN_FIRMWARE "dvb-fe-drxj-mc-1.0.8.fw"

/*
* \मrief Maximum u32 value.
*/
#अगर_अघोषित MAX_U32
#घोषणा MAX_U32  ((u32) (0xFFFFFFFFL))
#पूर्ण_अगर

/* Customer configurable hardware settings, etc */
#अगर_अघोषित MPEG_SERIAL_OUTPUT_PIN_DRIVE_STRENGTH
#घोषणा MPEG_SERIAL_OUTPUT_PIN_DRIVE_STRENGTH 0x02
#पूर्ण_अगर

#अगर_अघोषित MPEG_PARALLEL_OUTPUT_PIN_DRIVE_STRENGTH
#घोषणा MPEG_PARALLEL_OUTPUT_PIN_DRIVE_STRENGTH 0x02
#पूर्ण_अगर

#अगर_अघोषित MPEG_OUTPUT_CLK_DRIVE_STRENGTH
#घोषणा MPEG_OUTPUT_CLK_DRIVE_STRENGTH 0x06
#पूर्ण_अगर

#अगर_अघोषित OOB_CRX_DRIVE_STRENGTH
#घोषणा OOB_CRX_DRIVE_STRENGTH 0x02
#पूर्ण_अगर

#अगर_अघोषित OOB_DRX_DRIVE_STRENGTH
#घोषणा OOB_DRX_DRIVE_STRENGTH 0x02
#पूर्ण_अगर
/*** START DJCOMBO patches to DRXJ रेजिस्टरmap स्थिरants *********************/
/*** रेजिस्टरmap 200706071303 from drxj **************************************/
#घोषणा   ATV_TOP_CR_AMP_TH_FM                                              0x0
#घोषणा   ATV_TOP_CR_AMP_TH_L                                               0xA
#घोषणा   ATV_TOP_CR_AMP_TH_LP                                              0xA
#घोषणा   ATV_TOP_CR_AMP_TH_BG                                              0x8
#घोषणा   ATV_TOP_CR_AMP_TH_DK                                              0x8
#घोषणा   ATV_TOP_CR_AMP_TH_I                                               0x8
#घोषणा     ATV_TOP_CR_CONT_CR_D_MN                                         0x18
#घोषणा     ATV_TOP_CR_CONT_CR_D_FM                                         0x0
#घोषणा     ATV_TOP_CR_CONT_CR_D_L                                          0x20
#घोषणा     ATV_TOP_CR_CONT_CR_D_LP                                         0x20
#घोषणा     ATV_TOP_CR_CONT_CR_D_BG                                         0x18
#घोषणा     ATV_TOP_CR_CONT_CR_D_DK                                         0x18
#घोषणा     ATV_TOP_CR_CONT_CR_D_I                                          0x18
#घोषणा     ATV_TOP_CR_CONT_CR_I_MN                                         0x80
#घोषणा     ATV_TOP_CR_CONT_CR_I_FM                                         0x0
#घोषणा     ATV_TOP_CR_CONT_CR_I_L                                          0x80
#घोषणा     ATV_TOP_CR_CONT_CR_I_LP                                         0x80
#घोषणा     ATV_TOP_CR_CONT_CR_I_BG                                         0x80
#घोषणा     ATV_TOP_CR_CONT_CR_I_DK                                         0x80
#घोषणा     ATV_TOP_CR_CONT_CR_I_I                                          0x80
#घोषणा     ATV_TOP_CR_CONT_CR_P_MN                                         0x4
#घोषणा     ATV_TOP_CR_CONT_CR_P_FM                                         0x0
#घोषणा     ATV_TOP_CR_CONT_CR_P_L                                          0x4
#घोषणा     ATV_TOP_CR_CONT_CR_P_LP                                         0x4
#घोषणा     ATV_TOP_CR_CONT_CR_P_BG                                         0x4
#घोषणा     ATV_TOP_CR_CONT_CR_P_DK                                         0x4
#घोषणा     ATV_TOP_CR_CONT_CR_P_I                                          0x4
#घोषणा   ATV_TOP_CR_OVM_TH_MN                                              0xA0
#घोषणा   ATV_TOP_CR_OVM_TH_FM                                              0x0
#घोषणा   ATV_TOP_CR_OVM_TH_L                                               0xA0
#घोषणा   ATV_TOP_CR_OVM_TH_LP                                              0xA0
#घोषणा   ATV_TOP_CR_OVM_TH_BG                                              0xA0
#घोषणा   ATV_TOP_CR_OVM_TH_DK                                              0xA0
#घोषणा   ATV_TOP_CR_OVM_TH_I                                               0xA0
#घोषणा     ATV_TOP_EQU0_EQU_C0_FM                                          0x0
#घोषणा     ATV_TOP_EQU0_EQU_C0_L                                           0x3
#घोषणा     ATV_TOP_EQU0_EQU_C0_LP                                          0x3
#घोषणा     ATV_TOP_EQU0_EQU_C0_BG                                          0x7
#घोषणा     ATV_TOP_EQU0_EQU_C0_DK                                          0x0
#घोषणा     ATV_TOP_EQU0_EQU_C0_I                                           0x3
#घोषणा     ATV_TOP_EQU1_EQU_C1_FM                                          0x0
#घोषणा     ATV_TOP_EQU1_EQU_C1_L                                           0x1F6
#घोषणा     ATV_TOP_EQU1_EQU_C1_LP                                          0x1F6
#घोषणा     ATV_TOP_EQU1_EQU_C1_BG                                          0x197
#घोषणा     ATV_TOP_EQU1_EQU_C1_DK                                          0x198
#घोषणा     ATV_TOP_EQU1_EQU_C1_I                                           0x1F6
#घोषणा     ATV_TOP_EQU2_EQU_C2_FM                                          0x0
#घोषणा     ATV_TOP_EQU2_EQU_C2_L                                           0x28
#घोषणा     ATV_TOP_EQU2_EQU_C2_LP                                          0x28
#घोषणा     ATV_TOP_EQU2_EQU_C2_BG                                          0xC5
#घोषणा     ATV_TOP_EQU2_EQU_C2_DK                                          0xB0
#घोषणा     ATV_TOP_EQU2_EQU_C2_I                                           0x28
#घोषणा     ATV_TOP_EQU3_EQU_C3_FM                                          0x0
#घोषणा     ATV_TOP_EQU3_EQU_C3_L                                           0x192
#घोषणा     ATV_TOP_EQU3_EQU_C3_LP                                          0x192
#घोषणा     ATV_TOP_EQU3_EQU_C3_BG                                          0x12E
#घोषणा     ATV_TOP_EQU3_EQU_C3_DK                                          0x18E
#घोषणा     ATV_TOP_EQU3_EQU_C3_I                                           0x192
#घोषणा     ATV_TOP_STD_MODE_MN                                             0x0
#घोषणा     ATV_TOP_STD_MODE_FM                                             0x1
#घोषणा     ATV_TOP_STD_MODE_L                                              0x0
#घोषणा     ATV_TOP_STD_MODE_LP                                             0x0
#घोषणा     ATV_TOP_STD_MODE_BG                                             0x0
#घोषणा     ATV_TOP_STD_MODE_DK                                             0x0
#घोषणा     ATV_TOP_STD_MODE_I                                              0x0
#घोषणा     ATV_TOP_STD_VID_POL_MN                                          0x0
#घोषणा     ATV_TOP_STD_VID_POL_FM                                          0x0
#घोषणा     ATV_TOP_STD_VID_POL_L                                           0x2
#घोषणा     ATV_TOP_STD_VID_POL_LP                                          0x2
#घोषणा     ATV_TOP_STD_VID_POL_BG                                          0x0
#घोषणा     ATV_TOP_STD_VID_POL_DK                                          0x0
#घोषणा     ATV_TOP_STD_VID_POL_I                                           0x0
#घोषणा   ATV_TOP_VID_AMP_MN                                                0x380
#घोषणा   ATV_TOP_VID_AMP_FM                                                0x0
#घोषणा   ATV_TOP_VID_AMP_L                                                 0xF50
#घोषणा   ATV_TOP_VID_AMP_LP                                                0xF50
#घोषणा   ATV_TOP_VID_AMP_BG                                                0x380
#घोषणा   ATV_TOP_VID_AMP_DK                                                0x394
#घोषणा   ATV_TOP_VID_AMP_I                                                 0x3D8
#घोषणा   IQM_CF_OUT_ENA_OFDM__M                                            0x4
#घोषणा     IQM_FS_ADJ_SEL_B_QAM                                            0x1
#घोषणा     IQM_FS_ADJ_SEL_B_OFF                                            0x0
#घोषणा     IQM_FS_ADJ_SEL_B_VSB                                            0x2
#घोषणा     IQM_RC_ADJ_SEL_B_OFF                                            0x0
#घोषणा     IQM_RC_ADJ_SEL_B_QAM                                            0x1
#घोषणा     IQM_RC_ADJ_SEL_B_VSB                                            0x2
/*** END DJCOMBO patches to DRXJ रेजिस्टरmap *********************************/

#समावेश "drx_driver_version.h"

/* #घोषणा DRX_DEBUG */
#अगर_घोषित DRX_DEBUG
#समावेश <मानकपन.स>
#पूर्ण_अगर

/*-----------------------------------------------------------------------------
ENUMS
----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
DEFINES
----------------------------------------------------------------------------*/
#अगर_अघोषित DRXJ_WAKE_UP_KEY
#घोषणा DRXJ_WAKE_UP_KEY (demod->my_i2c_dev_addr->i2c_addr)
#पूर्ण_अगर

/*
* \def DRXJ_DEF_I2C_ADDR
* \मrief Default I2C address of a demodulator instance.
*/
#घोषणा DRXJ_DEF_I2C_ADDR (0x52)

/*
* \def DRXJ_DEF_DEMOD_DEV_ID
* \मrief Default device identअगरier of a demodultor instance.
*/
#घोषणा DRXJ_DEF_DEMOD_DEV_ID      (1)

/*
* \def DRXJ_SCAN_TIMEOUT
* \मrief Timeout value क्रम रुकोing on demod lock during channel scan (millisec).
*/
#घोषणा DRXJ_SCAN_TIMEOUT    1000

/*
* \def HI_I2C_DELAY
* \मrief HI timing delay क्रम I2C timing (in nano seconds)
*
*  Used to compute HI_CFG_DIV
*/
#घोषणा HI_I2C_DELAY    42

/*
* \def HI_I2C_BRIDGE_DELAY
* \मrief HI timing delay क्रम I2C timing (in nano seconds)
*
*  Used to compute HI_CFG_BDL
*/
#घोषणा HI_I2C_BRIDGE_DELAY   750

/*
* \मrief Time Winकरोw क्रम MER and SER Measurement in Units of Segment duration.
*/
#घोषणा VSB_TOP_MEASUREMENT_PERIOD  64
#घोषणा SYMBOLS_PER_SEGMENT         832

/*
* \मrief bit rate and segment rate स्थिरants used क्रम SER and BER.
*/
/* values taken from the QAM microcode */
#घोषणा DRXJ_QAM_SL_SIG_POWER_QAM_UNKNOWN 0
#घोषणा DRXJ_QAM_SL_SIG_POWER_QPSK        32768
#घोषणा DRXJ_QAM_SL_SIG_POWER_QAM8        24576
#घोषणा DRXJ_QAM_SL_SIG_POWER_QAM16       40960
#घोषणा DRXJ_QAM_SL_SIG_POWER_QAM32       20480
#घोषणा DRXJ_QAM_SL_SIG_POWER_QAM64       43008
#घोषणा DRXJ_QAM_SL_SIG_POWER_QAM128      20992
#घोषणा DRXJ_QAM_SL_SIG_POWER_QAM256      43520
/*
* \मrief Min supported symbolrates.
*/
#अगर_अघोषित DRXJ_QAM_SYMBOLRATE_MIN
#घोषणा DRXJ_QAM_SYMBOLRATE_MIN          (520000)
#पूर्ण_अगर

/*
* \मrief Max supported symbolrates.
*/
#अगर_अघोषित DRXJ_QAM_SYMBOLRATE_MAX
#घोषणा DRXJ_QAM_SYMBOLRATE_MAX         (7233000)
#पूर्ण_अगर

/*
* \def DRXJ_QAM_MAX_WAITTIME
* \मrief Maximal रुको समय क्रम QAM स्वतः स्थिरellation in ms
*/
#अगर_अघोषित DRXJ_QAM_MAX_WAITTIME
#घोषणा DRXJ_QAM_MAX_WAITTIME 900
#पूर्ण_अगर

#अगर_अघोषित DRXJ_QAM_FEC_LOCK_WAITTIME
#घोषणा DRXJ_QAM_FEC_LOCK_WAITTIME 150
#पूर्ण_अगर

#अगर_अघोषित DRXJ_QAM_DEMOD_LOCK_EXT_WAITTIME
#घोषणा DRXJ_QAM_DEMOD_LOCK_EXT_WAITTIME 200
#पूर्ण_अगर

/*
* \def SCU status and results
* \मrief SCU
*/
#घोषणा DRX_SCU_READY               0
#घोषणा DRXJ_MAX_WAITTIME           100	/* ms */
#घोषणा FEC_RS_MEASUREMENT_PERIOD   12894	/* 1 sec */
#घोषणा FEC_RS_MEASUREMENT_PRESCALE 1	/* n sec */

/*
* \def DRX_AUD_MAX_DEVIATION
* \मrief Needed क्रम calculation of prescale feature in AUD
*/
#अगर_अघोषित DRXJ_AUD_MAX_FM_DEVIATION
#घोषणा DRXJ_AUD_MAX_FM_DEVIATION  100	/* kHz */
#पूर्ण_अगर

/*
* \मrief Needed क्रम calculation of NICAM prescale feature in AUD
*/
#अगर_अघोषित DRXJ_AUD_MAX_NICAM_PRESCALE
#घोषणा DRXJ_AUD_MAX_NICAM_PRESCALE  (9)	/* dB */
#पूर्ण_अगर

/*
* \मrief Needed क्रम calculation of NICAM prescale feature in AUD
*/
#अगर_अघोषित DRXJ_AUD_MAX_WAITTIME
#घोषणा DRXJ_AUD_MAX_WAITTIME  250	/* ms */
#पूर्ण_अगर

/* ATV config changed flags */
#घोषणा DRXJ_ATV_CHANGED_COEF          (0x00000001UL)
#घोषणा DRXJ_ATV_CHANGED_PEAK_FLT      (0x00000008UL)
#घोषणा DRXJ_ATV_CHANGED_NOISE_FLT     (0x00000010UL)
#घोषणा DRXJ_ATV_CHANGED_OUTPUT        (0x00000020UL)
#घोषणा DRXJ_ATV_CHANGED_SIF_ATT       (0x00000040UL)

/* UIO define */
#घोषणा DRX_UIO_MODE_FIRMWARE_SMA DRX_UIO_MODE_FIRMWARE0
#घोषणा DRX_UIO_MODE_FIRMWARE_SAW DRX_UIO_MODE_FIRMWARE1

/*
 * MICROCODE RELATED DEFINES
 */

/* Magic word क्रम checking correct Endianness of microcode data */
#घोषणा DRX_UCODE_MAGIC_WORD         ((((u16)'H')<<8)+((u16)'L'))

/* CRC flag in ucode header, flags field. */
#घोषणा DRX_UCODE_CRC_FLAG           (0x0001)

/*
 * Maximum size of buffer used to verअगरy the microcode.
 * Must be an even number
 */
#घोषणा DRX_UCODE_MAX_BUF_SIZE       (DRXDAP_MAX_RCHUNKSIZE)

#अगर DRX_UCODE_MAX_BUF_SIZE & 1
#त्रुटि DRX_UCODE_MAX_BUF_SIZE must be an even number
#पूर्ण_अगर

/*
 * Power mode macros
 */

#घोषणा DRX_ISPOWERDOWNMODE(mode) ((mode == DRX_POWER_MODE_9) || \
				       (mode == DRX_POWER_MODE_10) || \
				       (mode == DRX_POWER_MODE_11) || \
				       (mode == DRX_POWER_MODE_12) || \
				       (mode == DRX_POWER_MODE_13) || \
				       (mode == DRX_POWER_MODE_14) || \
				       (mode == DRX_POWER_MODE_15) || \
				       (mode == DRX_POWER_MODE_16) || \
				       (mode == DRX_POWER_DOWN))

/* Pin safe mode macro */
#घोषणा DRXJ_PIN_SAFE_MODE 0x0000
/*============================================================================*/
/*=== GLOBAL VARIABLEs =======================================================*/
/*============================================================================*/
/*
*/

/*
* \मrief Temporary रेजिस्टर definitions.
*        (रेजिस्टर definitions that are not yet available in रेजिस्टर master)
*/

/*****************************************************************************/
/* Audio block 0x103 is ग_लिखो only. To aव्योम shaकरोwing in driver accessing   */
/* RAM addresses directly. This must be READ ONLY to aव्योम problems.         */
/* Writing to the पूर्णांकerface addresses are more than only writing the RAM     */
/* locations                                                                 */
/*****************************************************************************/
/*
* \मrief RAM location of MODUS रेजिस्टरs
*/
#घोषणा AUD_DEM_RAM_MODUS_HI__A              0x10204A3
#घोषणा AUD_DEM_RAM_MODUS_HI__M              0xF000

#घोषणा AUD_DEM_RAM_MODUS_LO__A              0x10204A4
#घोषणा AUD_DEM_RAM_MODUS_LO__M              0x0FFF

/*
* \मrief RAM location of I2S config रेजिस्टरs
*/
#घोषणा AUD_DEM_RAM_I2S_CONFIG1__A           0x10204B1
#घोषणा AUD_DEM_RAM_I2S_CONFIG2__A           0x10204B2

/*
* \मrief RAM location of DCO config रेजिस्टरs
*/
#घोषणा AUD_DEM_RAM_DCO_B_HI__A              0x1020461
#घोषणा AUD_DEM_RAM_DCO_B_LO__A              0x1020462
#घोषणा AUD_DEM_RAM_DCO_A_HI__A              0x1020463
#घोषणा AUD_DEM_RAM_DCO_A_LO__A              0x1020464

/*
* \मrief RAM location of Threshold रेजिस्टरs
*/
#घोषणा AUD_DEM_RAM_NICAM_THRSHLD__A         0x102045A
#घोषणा AUD_DEM_RAM_A2_THRSHLD__A            0x10204BB
#घोषणा AUD_DEM_RAM_BTSC_THRSHLD__A          0x10204A6

/*
* \मrief RAM location of Carrier Threshold रेजिस्टरs
*/
#घोषणा AUD_DEM_RAM_CM_A_THRSHLD__A          0x10204AF
#घोषणा AUD_DEM_RAM_CM_B_THRSHLD__A          0x10204B0

/*
* \मrief FM Matrix रेजिस्टर fix
*/
#अगर_घोषित AUD_DEM_WR_FM_MATRIX__A
#अघोषित  AUD_DEM_WR_FM_MATRIX__A
#पूर्ण_अगर
#घोषणा AUD_DEM_WR_FM_MATRIX__A              0x105006F

/*============================================================================*/
/*
* \मrief Defines required क्रम audio
*/
#घोषणा AUD_VOLUME_ZERO_DB                      115
#घोषणा AUD_VOLUME_DB_MIN                       -60
#घोषणा AUD_VOLUME_DB_MAX                       12
#घोषणा AUD_CARRIER_STRENGTH_QP_0DB             0x4000
#घोषणा AUD_CARRIER_STRENGTH_QP_0DB_LOG10T100   421
#घोषणा AUD_MAX_AVC_REF_LEVEL                   15
#घोषणा AUD_I2S_FREQUENCY_MAX                   48000UL
#घोषणा AUD_I2S_FREQUENCY_MIN                   12000UL
#घोषणा AUD_RDS_ARRAY_SIZE                      18

/*
* \मrief Needed क्रम calculation of prescale feature in AUD
*/
#अगर_अघोषित DRX_AUD_MAX_FM_DEVIATION
#घोषणा DRX_AUD_MAX_FM_DEVIATION  (100)	/* kHz */
#पूर्ण_अगर

/*
* \मrief Needed क्रम calculation of NICAM prescale feature in AUD
*/
#अगर_अघोषित DRX_AUD_MAX_NICAM_PRESCALE
#घोषणा DRX_AUD_MAX_NICAM_PRESCALE  (9)	/* dB */
#पूर्ण_अगर

/*============================================================================*/
/* Values क्रम I2S Master/Slave pin configurations */
#घोषणा SIO_PDR_I2S_CL_CFG_MODE__MASTER      0x0004
#घोषणा SIO_PDR_I2S_CL_CFG_DRIVE__MASTER     0x0008
#घोषणा SIO_PDR_I2S_CL_CFG_MODE__SLAVE       0x0004
#घोषणा SIO_PDR_I2S_CL_CFG_DRIVE__SLAVE      0x0000

#घोषणा SIO_PDR_I2S_DA_CFG_MODE__MASTER      0x0003
#घोषणा SIO_PDR_I2S_DA_CFG_DRIVE__MASTER     0x0008
#घोषणा SIO_PDR_I2S_DA_CFG_MODE__SLAVE       0x0003
#घोषणा SIO_PDR_I2S_DA_CFG_DRIVE__SLAVE      0x0008

#घोषणा SIO_PDR_I2S_WS_CFG_MODE__MASTER      0x0004
#घोषणा SIO_PDR_I2S_WS_CFG_DRIVE__MASTER     0x0008
#घोषणा SIO_PDR_I2S_WS_CFG_MODE__SLAVE       0x0004
#घोषणा SIO_PDR_I2S_WS_CFG_DRIVE__SLAVE      0x0000

/*============================================================================*/
/*=== REGISTER ACCESS MACROS =================================================*/
/*============================================================================*/

/*
* This macro is used to create byte arrays क्रम block ग_लिखोs.
* Block ग_लिखोs speed up I2C traffic between host and demod.
* The macro takes care of the required byte order in a 16 bits word.
* x -> lowbyte(x), highbyte(x)
*/
#घोषणा DRXJ_16TO8(x) ((u8) (((u16)x) & 0xFF)), \
		       ((u8)((((u16)x)>>8)&0xFF))
/*
* This macro is used to convert byte array to 16 bit रेजिस्टर value क्रम block पढ़ो.
* Block पढ़ो speed up I2C traffic between host and demod.
* The macro takes care of the required byte order in a 16 bits word.
*/
#घोषणा DRXJ_8TO16(x) ((u16) (x[0] | (x[1] << 8)))

/*============================================================================*/
/*=== MISC DEFINES ===========================================================*/
/*============================================================================*/

/*============================================================================*/
/*=== HI COMMAND RELATED DEFINES =============================================*/
/*============================================================================*/

/*
* \मrief General maximum number of retries क्रम ucode command पूर्णांकerfaces
*/
#घोषणा DRXJ_MAX_RETRIES (100)

/*============================================================================*/
/*=== STANDARD RELATED MACROS ================================================*/
/*============================================================================*/

#घोषणा DRXJ_ISATVSTD(std) ((std == DRX_STANDARD_PAL_SECAM_BG) || \
			       (std == DRX_STANDARD_PAL_SECAM_DK) || \
			       (std == DRX_STANDARD_PAL_SECAM_I) || \
			       (std == DRX_STANDARD_PAL_SECAM_L) || \
			       (std == DRX_STANDARD_PAL_SECAM_LP) || \
			       (std == DRX_STANDARD_NTSC) || \
			       (std == DRX_STANDARD_FM))

#घोषणा DRXJ_ISQAMSTD(std) ((std == DRX_STANDARD_ITU_A) || \
			       (std == DRX_STANDARD_ITU_B) || \
			       (std == DRX_STANDARD_ITU_C) || \
			       (std == DRX_STANDARD_ITU_D))

/*-----------------------------------------------------------------------------
GLOBAL VARIABLES
----------------------------------------------------------------------------*/
/*
 * DRXJ DAP काष्ठाures
 */

अटल पूर्णांक drxdap_fasi_पढ़ो_block(काष्ठा i2c_device_addr *dev_addr,
				      u32 addr,
				      u16 datasize,
				      u8 *data, u32 flags);


अटल पूर्णांक drxj_dap_पढ़ो_modअगरy_ग_लिखो_reg16(काष्ठा i2c_device_addr *dev_addr,
						 u32 waddr,
						 u32 raddr,
						 u16 wdata, u16 *rdata);

अटल पूर्णांक drxj_dap_पढ़ो_reg16(काष्ठा i2c_device_addr *dev_addr,
				      u32 addr,
				      u16 *data, u32 flags);

अटल पूर्णांक drxdap_fasi_पढ़ो_reg32(काष्ठा i2c_device_addr *dev_addr,
				      u32 addr,
				      u32 *data, u32 flags);

अटल पूर्णांक drxdap_fasi_ग_लिखो_block(काष्ठा i2c_device_addr *dev_addr,
				       u32 addr,
				       u16 datasize,
				       u8 *data, u32 flags);

अटल पूर्णांक drxj_dap_ग_लिखो_reg16(काष्ठा i2c_device_addr *dev_addr,
				       u32 addr,
				       u16 data, u32 flags);

अटल पूर्णांक drxdap_fasi_ग_लिखो_reg32(काष्ठा i2c_device_addr *dev_addr,
				       u32 addr,
				       u32 data, u32 flags);

अटल काष्ठा drxj_data drxj_data_g = अणु
	false,			/* has_lna : true अगर LNA (aka PGA) present      */
	false,			/* has_oob : true अगर OOB supported              */
	false,			/* has_ntsc: true अगर NTSC supported             */
	false,			/* has_btsc: true अगर BTSC supported             */
	false,			/* has_smatx: true अगर SMA_TX pin is available   */
	false,			/* has_smarx: true अगर SMA_RX pin is available   */
	false,			/* has_gpio : true अगर GPIO pin is available     */
	false,			/* has_irqn : true अगर IRQN pin is available     */
	0,			/* mfx A1/A2/A... */

	/* tuner settings */
	false,			/* tuner mirrors RF संकेत    */
	/* standard/channel settings */
	DRX_STANDARD_UNKNOWN,	/* current standard           */
	DRX_CONSTELLATION_AUTO,	/* स्थिरellation              */
	0,			/* frequency in KHz           */
	DRX_BANDWIDTH_UNKNOWN,	/* curr_bandwidth              */
	DRX_MIRROR_NO,		/* mirror                     */

	/* संकेत quality inक्रमmation: */
	/* शेष values taken from the QAM Programming guide */
	/*   fec_bits_desired should not be less than 4000000    */
	4000000,		/* fec_bits_desired    */
	5,			/* fec_vd_plen         */
	4,			/* qam_vd_prescale     */
	0xFFFF,			/* qamVDPeriod       */
	204 * 8,		/* fec_rs_plen annex A */
	1,			/* fec_rs_prescale     */
	FEC_RS_MEASUREMENT_PERIOD,	/* fec_rs_period     */
	true,			/* reset_pkt_err_acc    */
	0,			/* pkt_err_acc_start    */

	/* HI configuration */
	0,			/* hi_cfg_timing_भाग    */
	0,			/* hi_cfg_bridge_delay  */
	0,			/* hi_cfg_wake_up_key    */
	0,			/* hi_cfg_ctrl         */
	0,			/* HICfgTimeout      */
	/* UIO configuration */
	DRX_UIO_MODE_DISABLE,	/* uio_sma_rx_mode      */
	DRX_UIO_MODE_DISABLE,	/* uio_sma_tx_mode      */
	DRX_UIO_MODE_DISABLE,	/* uioASELMode       */
	DRX_UIO_MODE_DISABLE,	/* uio_irqn_mode       */
	/* FS setting */
	0UL,			/* iqm_fs_rate_ofs      */
	false,			/* pos_image          */
	/* RC setting */
	0UL,			/* iqm_rc_rate_ofs      */
	/* AUD inक्रमmation */
/*   false,                  * flagSetAUDकरोne    */
/*   false,                  * detectedRDS       */
/*   true,                   * flagASDRequest    */
/*   false,                  * flagHDevClear     */
/*   false,                  * flagHDevSet       */
/*   (u16) 0xFFF,          * rdsLastCount      */

	/* ATV configuration */
	0UL,			/* flags cfg changes */
	/* shaकरोw of ATV_TOP_EQU0__A */
	अणु-5,
	 ATV_TOP_EQU0_EQU_C0_FM,
	 ATV_TOP_EQU0_EQU_C0_L,
	 ATV_TOP_EQU0_EQU_C0_LP,
	 ATV_TOP_EQU0_EQU_C0_BG,
	 ATV_TOP_EQU0_EQU_C0_DK,
	 ATV_TOP_EQU0_EQU_C0_Iपूर्ण,
	/* shaकरोw of ATV_TOP_EQU1__A */
	अणु-50,
	 ATV_TOP_EQU1_EQU_C1_FM,
	 ATV_TOP_EQU1_EQU_C1_L,
	 ATV_TOP_EQU1_EQU_C1_LP,
	 ATV_TOP_EQU1_EQU_C1_BG,
	 ATV_TOP_EQU1_EQU_C1_DK,
	 ATV_TOP_EQU1_EQU_C1_Iपूर्ण,
	/* shaकरोw of ATV_TOP_EQU2__A */
	अणु210,
	 ATV_TOP_EQU2_EQU_C2_FM,
	 ATV_TOP_EQU2_EQU_C2_L,
	 ATV_TOP_EQU2_EQU_C2_LP,
	 ATV_TOP_EQU2_EQU_C2_BG,
	 ATV_TOP_EQU2_EQU_C2_DK,
	 ATV_TOP_EQU2_EQU_C2_Iपूर्ण,
	/* shaकरोw of ATV_TOP_EQU3__A */
	अणु-160,
	 ATV_TOP_EQU3_EQU_C3_FM,
	 ATV_TOP_EQU3_EQU_C3_L,
	 ATV_TOP_EQU3_EQU_C3_LP,
	 ATV_TOP_EQU3_EQU_C3_BG,
	 ATV_TOP_EQU3_EQU_C3_DK,
	 ATV_TOP_EQU3_EQU_C3_Iपूर्ण,
	false,			/* flag: true=bypass             */
	ATV_TOP_VID_PEAK__PRE,	/* shaकरोw of ATV_TOP_VID_PEAK__A */
	ATV_TOP_NOISE_TH__PRE,	/* shaकरोw of ATV_TOP_NOISE_TH__A */
	true,			/* flag CVBS output enable       */
	false,			/* flag SIF output enable        */
	DRXJ_SIF_ATTENUATION_0DB,	/* current SIF att setting       */
	अणु			/* qam_rf_agc_cfg */
	 DRX_STANDARD_ITU_B,	/* standard            */
	 DRX_AGC_CTRL_AUTO,	/* ctrl_mode            */
	 0,			/* output_level         */
	 0,			/* min_output_level      */
	 0xFFFF,		/* max_output_level      */
	 0x0000,		/* speed               */
	 0x0000,		/* top                 */
	 0x0000			/* c.o.c.              */
	 पूर्ण,
	अणु			/* qam_अगर_agc_cfg */
	 DRX_STANDARD_ITU_B,	/* standard            */
	 DRX_AGC_CTRL_AUTO,	/* ctrl_mode            */
	 0,			/* output_level         */
	 0,			/* min_output_level      */
	 0xFFFF,		/* max_output_level      */
	 0x0000,		/* speed               */
	 0x0000,		/* top    (करोn't care) */
	 0x0000			/* c.o.c. (करोn't care) */
	 पूर्ण,
	अणु			/* vsb_rf_agc_cfg */
	 DRX_STANDARD_8VSB,	/* standard       */
	 DRX_AGC_CTRL_AUTO,	/* ctrl_mode       */
	 0,			/* output_level    */
	 0,			/* min_output_level */
	 0xFFFF,		/* max_output_level */
	 0x0000,		/* speed          */
	 0x0000,		/* top    (करोn't care) */
	 0x0000			/* c.o.c. (करोn't care) */
	 पूर्ण,
	अणु			/* vsb_अगर_agc_cfg */
	 DRX_STANDARD_8VSB,	/* standard       */
	 DRX_AGC_CTRL_AUTO,	/* ctrl_mode       */
	 0,			/* output_level    */
	 0,			/* min_output_level */
	 0xFFFF,		/* max_output_level */
	 0x0000,		/* speed          */
	 0x0000,		/* top    (करोn't care) */
	 0x0000			/* c.o.c. (करोn't care) */
	 पूर्ण,
	0,			/* qam_pga_cfg */
	0,			/* vsb_pga_cfg */
	अणु			/* qam_pre_saw_cfg */
	 DRX_STANDARD_ITU_B,	/* standard  */
	 0,			/* reference */
	 false			/* use_pre_saw */
	 पूर्ण,
	अणु			/* vsb_pre_saw_cfg */
	 DRX_STANDARD_8VSB,	/* standard  */
	 0,			/* reference */
	 false			/* use_pre_saw */
	 पूर्ण,

	/* Version inक्रमmation */
#अगर_अघोषित _CH_
	अणु
	 "01234567890",		/* human पढ़ोable version microcode             */
	 "01234567890"		/* human पढ़ोable version device specअगरic code  */
	 पूर्ण,
	अणु
	 अणु			/* काष्ठा drx_version क्रम microcode                   */
	  DRX_MODULE_UNKNOWN,
	  (अक्षर *)(शून्य),
	  0,
	  0,
	  0,
	  (अक्षर *)(शून्य)
	  पूर्ण,
	 अणु			/* काष्ठा drx_version क्रम device specअगरic code */
	  DRX_MODULE_UNKNOWN,
	  (अक्षर *)(शून्य),
	  0,
	  0,
	  0,
	  (अक्षर *)(शून्य)
	  पूर्ण
	 पूर्ण,
	अणु
	 अणु			/* काष्ठा drx_version_list क्रम microcode */
	  (काष्ठा drx_version *) (शून्य),
	  (काष्ठा drx_version_list *) (शून्य)
	  पूर्ण,
	 अणु			/* काष्ठा drx_version_list क्रम device specअगरic code */
	  (काष्ठा drx_version *) (शून्य),
	  (काष्ठा drx_version_list *) (शून्य)
	  पूर्ण
	 पूर्ण,
#पूर्ण_अगर
	false,			/* smart_ant_inverted */
	/* Tracking filter setting क्रम OOB  */
	अणु
	 12000,
	 9300,
	 6600,
	 5280,
	 3700,
	 3000,
	 2000,
	 0पूर्ण,
	false,			/* oob_घातer_on           */
	0,			/* mpeg_ts_अटल_bitrate  */
	false,			/* disable_te_ihandling   */
	false,			/* bit_reverse_mpeg_outout */
	DRXJ_MPEGOUTPUT_CLOCK_RATE_AUTO,	/* mpeg_output_घड़ी_rate */
	DRXJ_MPEG_START_WIDTH_1CLKCYC,	/* mpeg_start_width */

	/* Pre SAW & Agc configuration क्रम ATV */
	अणु
	 DRX_STANDARD_NTSC,	/* standard     */
	 7,			/* reference    */
	 true			/* use_pre_saw    */
	 पूर्ण,
	अणु			/* ATV RF-AGC */
	 DRX_STANDARD_NTSC,	/* standard              */
	 DRX_AGC_CTRL_AUTO,	/* ctrl_mode              */
	 0,			/* output_level           */
	 0,			/* min_output_level (d.c.) */
	 0,			/* max_output_level (d.c.) */
	 3,			/* speed                 */
	 9500,			/* top                   */
	 4000			/* cut-off current       */
	 पूर्ण,
	अणु			/* ATV IF-AGC */
	 DRX_STANDARD_NTSC,	/* standard              */
	 DRX_AGC_CTRL_AUTO,	/* ctrl_mode              */
	 0,			/* output_level           */
	 0,			/* min_output_level (d.c.) */
	 0,			/* max_output_level (d.c.) */
	 3,			/* speed                 */
	 2400,			/* top                   */
	 0			/* c.o.c.         (d.c.) */
	 पूर्ण,
	140,			/* ATV PGA config */
	0,			/* curr_symbol_rate */

	false,			/* pdr_safe_mode     */
	SIO_PDR_GPIO_CFG__PRE,	/* pdr_safe_restore_val_gpio  */
	SIO_PDR_VSYNC_CFG__PRE,	/* pdr_safe_restore_val_v_sync */
	SIO_PDR_SMA_RX_CFG__PRE,	/* pdr_safe_restore_val_sma_rx */
	SIO_PDR_SMA_TX_CFG__PRE,	/* pdr_safe_restore_val_sma_tx */

	4,			/* oob_pre_saw            */
	DRXJ_OOB_LO_POW_MINUS10DB,	/* oob_lo_घात             */
	अणु
	 false			/* aud_data, only first member */
	 पूर्ण,
पूर्ण;

/*
* \खar drxj_शेष_addr_g
* \मrief Default I2C address and device identअगरier.
*/
अटल काष्ठा i2c_device_addr drxj_शेष_addr_g = अणु
	DRXJ_DEF_I2C_ADDR,	/* i2c address */
	DRXJ_DEF_DEMOD_DEV_ID	/* device id */
पूर्ण;

/*
* \खar drxj_शेष_comm_attr_g
* \मrief Default common attributes of a drxj demodulator instance.
*/
अटल काष्ठा drx_common_attr drxj_शेष_comm_attr_g = अणु
	शून्य,			/* ucode file           */
	true,			/* ucode verअगरy चयन  */
	अणु0पूर्ण,			/* version record       */

	44000,			/* IF in kHz in हाल no tuner instance is used  */
	(151875 - 0),		/* प्रणाली घड़ी frequency in kHz                */
	0,			/* oscillator frequency kHz                     */
	0,			/* oscillator deviation in ppm, चिन्हित          */
	false,			/* If true mirror frequency spectrum            */
	अणु
	 /* MPEG output configuration */
	 true,			/* If true, enable MPEG output   */
	 false,			/* If true, insert RS byte       */
	 false,			/* If true, parallel out otherwise serial */
	 false,			/* If true, invert DATA संकेतs  */
	 false,			/* If true, invert ERR संकेत    */
	 false,			/* If true, invert STR संकेतs   */
	 false,			/* If true, invert VAL संकेतs   */
	 false,			/* If true, invert CLK संकेतs   */
	 true,			/* If true, अटल MPEG घड़ीrate will
				   be used, otherwise घड़ीrate will
				   adapt to the bitrate of the TS */
	 19392658UL,		/* Maximum bitrate in b/s in हाल
				   अटल घड़ीrate is selected */
	 DRX_MPEG_STR_WIDTH_1	/* MPEG Start width in घड़ी cycles */
	 पूर्ण,
	/* Initilisations below can be omitted, they require no user input and
	   are initially 0, शून्य or false. The compiler will initialize them to these
	   values when omitted.  */
	false,			/* is_खोलोed */

	/* SCAN */
	शून्य,			/* no scan params yet               */
	0,			/* current scan index               */
	0,			/* next scan frequency              */
	false,			/* scan पढ़ोy flag                  */
	0,			/* max channels to scan             */
	0,			/* nr of channels scanned           */
	शून्य,			/* शेष scan function            */
	शून्य,			/* शेष context poपूर्णांकer          */
	0,			/* millisec to रुको क्रम demod lock  */
	DRXJ_DEMOD_LOCK,	/* desired lock               */
	false,

	/* Power management */
	DRX_POWER_UP,

	/* Tuner */
	1,			/* nr of I2C port to which tuner is    */
	0L,			/* minimum RF input frequency, in kHz  */
	0L,			/* maximum RF input frequency, in kHz  */
	false,			/* Rf Agc Polarity                     */
	false,			/* If Agc Polarity                     */
	false,			/* tuner slow mode                     */

	अणु			/* current channel (all 0)             */
	 0UL			/* channel.frequency */
	 पूर्ण,
	DRX_STANDARD_UNKNOWN,	/* current standard */
	DRX_STANDARD_UNKNOWN,	/* previous standard */
	DRX_STANDARD_UNKNOWN,	/* di_cache_standard   */
	false,			/* use_bootloader */
	0UL,			/* capabilities */
	0			/* mfx */
पूर्ण;

/*
* \खar drxj_शेष_demod_g
* \मrief Default drxj demodulator instance.
*/
अटल काष्ठा drx_demod_instance drxj_शेष_demod_g = अणु
	&drxj_शेष_addr_g,	/* i2c address & device id */
	&drxj_शेष_comm_attr_g,	/* demod common attributes */
	&drxj_data_g		/* demod device specअगरic attributes */
पूर्ण;

/*
* \मrief Default audio data काष्ठाure क्रम DRK demodulator instance.
*
* This काष्ठाure is DRXK specअगरic.
*
*/
अटल काष्ठा drx_aud_data drxj_शेष_aud_data_g = अणु
	false,			/* audio_is_active */
	DRX_AUD_STANDARD_AUTO,	/* audio_standard  */

	/* i2sdata */
	अणु
	 false,			/* output_enable   */
	 48000,			/* frequency      */
	 DRX_I2S_MODE_MASTER,	/* mode           */
	 DRX_I2S_WORDLENGTH_32,	/* word_length     */
	 DRX_I2S_POLARITY_RIGHT,	/* polarity       */
	 DRX_I2S_FORMAT_WS_WITH_DATA	/* क्रमmat         */
	 पूर्ण,
	/* volume            */
	अणु
	 true,			/* mute;          */
	 0,			/* volume         */
	 DRX_AUD_AVC_OFF,	/* avc_mode        */
	 0,			/* avc_ref_level    */
	 DRX_AUD_AVC_MAX_GAIN_12DB,	/* avc_max_gain     */
	 DRX_AUD_AVC_MAX_ATTEN_24DB,	/* avc_max_atten    */
	 0,			/* strength_left   */
	 0			/* strength_right  */
	 पूर्ण,
	DRX_AUD_AUTO_SOUND_SELECT_ON_CHANGE_ON,	/* स्वतः_sound */
	/*  ass_thresholds */
	अणु
	 440,			/* A2    */
	 12,			/* BTSC  */
	 700,			/* NICAM */
	 पूर्ण,
	/* carrier */
	अणु
	 /* a */
	 अणु
	  42,			/* thres */
	  DRX_NO_CARRIER_NOISE,	/* opt   */
	  0,			/* shअगरt */
	  0			/* dco   */
	  पूर्ण,
	 /* b */
	 अणु
	  42,			/* thres */
	  DRX_NO_CARRIER_MUTE,	/* opt   */
	  0,			/* shअगरt */
	  0			/* dco   */
	  पूर्ण,

	 पूर्ण,
	/* mixer */
	अणु
	 DRX_AUD_SRC_STEREO_OR_A,	/* source_i2s */
	 DRX_AUD_I2S_MATRIX_STEREO,	/* matrix_i2s */
	 DRX_AUD_FM_MATRIX_SOUND_A	/* matrix_fm  */
	 पूर्ण,
	DRX_AUD_DEVIATION_NORMAL,	/* deviation */
	DRX_AUD_AVSYNC_OFF,	/* av_sync */

	/* prescale */
	अणु
	 DRX_AUD_MAX_FM_DEVIATION,	/* fm_deviation */
	 DRX_AUD_MAX_NICAM_PRESCALE	/* nicam_gain */
	 पूर्ण,
	DRX_AUD_FM_DEEMPH_75US,	/* deemph */
	DRX_BTSC_STEREO,	/* btsc_detect */
	0,			/* rds_data_counter */
	false			/* rds_data_present */
पूर्ण;

/*-----------------------------------------------------------------------------
STRUCTURES
----------------------------------------------------------------------------*/
काष्ठा drxjeq_stat अणु
	u16 eq_mse;
	u8 eq_mode;
	u8 eq_ctrl;
	u8 eq_stat;
पूर्ण;

/* HI command */
काष्ठा drxj_hi_cmd अणु
	u16 cmd;
	u16 param1;
	u16 param2;
	u16 param3;
	u16 param4;
	u16 param5;
	u16 param6;
पूर्ण;

/*============================================================================*/
/*=== MICROCODE RELATED STRUCTURES ===========================================*/
/*============================================================================*/

/*
 * काष्ठा drxu_code_block_hdr - Structure of the microcode block headers
 *
 * @addr:	Destination address of the data in this block
 * @size:	Size of the block data following this header counted in
 *		16 bits words
 * @CRC:	CRC value of the data block, only valid अगर CRC flag is
 *		set.
 */
काष्ठा drxu_code_block_hdr अणु
	u32 addr;
	u16 size;
	u16 flags;
	u16 CRC;
पूर्ण;

/*-----------------------------------------------------------------------------
FUNCTIONS
----------------------------------------------------------------------------*/
/* Some prototypes */
अटल पूर्णांक
hi_command(काष्ठा i2c_device_addr *dev_addr,
	   स्थिर काष्ठा drxj_hi_cmd *cmd, u16 *result);

अटल पूर्णांक
ctrl_lock_status(काष्ठा drx_demod_instance *demod, क्रमागत drx_lock_status *lock_stat);

अटल पूर्णांक
ctrl_घातer_mode(काष्ठा drx_demod_instance *demod, क्रमागत drx_घातer_mode *mode);

अटल पूर्णांक घातer_करोwn_aud(काष्ठा drx_demod_instance *demod);

अटल पूर्णांक
ctrl_set_cfg_pre_saw(काष्ठा drx_demod_instance *demod, काष्ठा drxj_cfg_pre_saw *pre_saw);

अटल पूर्णांक
ctrl_set_cfg_afe_gain(काष्ठा drx_demod_instance *demod, काष्ठा drxj_cfg_afe_gain *afe_gain);

/*============================================================================*/
/*============================================================================*/
/*==                          HELPER FUNCTIONS                              ==*/
/*============================================================================*/
/*============================================================================*/


/*============================================================================*/

/*
* \पn u32 frac28(u32 N, u32 D)
* \मrief Compute: (1<<28)*N/D
* \param N 32 bits
* \param D 32 bits
* \लeturn (1<<28)*N/D
* This function is used to aव्योम भग्नing-poपूर्णांक calculations as they may
* not be present on the target platक्रमm.

* frac28 perक्रमms an अचिन्हित 28/28 bits भागision to 32-bit fixed poपूर्णांक
* fraction used क्रम setting the Frequency Shअगरter रेजिस्टरs.
* N and D can hold numbers up to width: 28-bits.
* The 4 bits पूर्णांकeger part and the 28 bits fractional part are calculated.

* Usage condition: ((1<<28)*n)/d < ((1<<32)-1) => (n/d) < 15.999

* N: 0...(1<<28)-1 = 268435454
* D: 0...(1<<28)-1
* Q: 0...(1<<32)-1
*/
अटल u32 frac28(u32 N, u32 D)
अणु
	पूर्णांक i = 0;
	u32 Q1 = 0;
	u32 R0 = 0;

	R0 = (N % D) << 4;	/* 32-28 == 4 shअगरts possible at max */
	Q1 = N / D;		/* पूर्णांकeger part, only the 4 least signअगरicant bits
				   will be visible in the result */

	/* भागision using radix 16, 7 nibbles in the result */
	क्रम (i = 0; i < 7; i++) अणु
		Q1 = (Q1 << 4) | R0 / D;
		R0 = (R0 % D) << 4;
	पूर्ण
	/* rounding */
	अगर ((R0 >> 3) >= D)
		Q1++;

	वापस Q1;
पूर्ण

/*
* \पn u32 log1_बार100( u32 x)
* \मrief Compute: 100*log10(x)
* \param x 32 bits
* \लeturn 100*log10(x)
*
* 100*log10(x)
* = 100*(log2(x)/log2(10)))
* = (100*(2^15)*log2(x))/((2^15)*log2(10))
* = ((200*(2^15)*log2(x))/((2^15)*log2(10)))/2
* = ((200*(2^15)*(log2(x/y)+log2(y)))/((2^15)*log2(10)))/2
* = ((200*(2^15)*log2(x/y))+(200*(2^15)*log2(y)))/((2^15)*log2(10)))/2
*
* where y = 2^k and 1<= (x/y) < 2
*/

अटल u32 log1_बार100(u32 x)
अणु
	अटल स्थिर u8 scale = 15;
	अटल स्थिर u8 index_width = 5;
	/*
	   log2lut[n] = (1<<scale) * 200 * log2( 1.0 + ( (1.0/(1<<INDEXWIDTH)) * n ))
	   0 <= n < ((1<<INDEXWIDTH)+1)
	 */

	अटल स्थिर u32 log2lut[] = अणु
		0,		/* 0.000000 */
		290941,		/* 290941.300628 */
		573196,		/* 573196.476418 */
		847269,		/* 847269.179851 */
		1113620,	/* 1113620.489452 */
		1372674,	/* 1372673.576986 */
		1624818,	/* 1624817.752104 */
		1870412,	/* 1870411.981536 */
		2109788,	/* 2109787.962654 */
		2343253,	/* 2343252.817465 */
		2571091,	/* 2571091.461923 */
		2793569,	/* 2793568.696416 */
		3010931,	/* 3010931.055901 */
		3223408,	/* 3223408.452106 */
		3431216,	/* 3431215.635215 */
		3634553,	/* 3634553.498355 */
		3833610,	/* 3833610.244726 */
		4028562,	/* 4028562.434393 */
		4219576,	/* 4219575.925308 */
		4406807,	/* 4406806.721144 */
		4590402,	/* 4590401.736809 */
		4770499,	/* 4770499.491025 */
		4947231,	/* 4947230.734179 */
		5120719,	/* 5120719.018555 */
		5291081,	/* 5291081.217197 */
		5458428,	/* 5458427.996830 */
		5622864,	/* 5622864.249668 */
		5784489,	/* 5784489.488298 */
		5943398,	/* 5943398.207380 */
		6099680,	/* 6099680.215452 */
		6253421,	/* 6253420.939751 */
		6404702,	/* 6404701.706649 */
		6553600,	/* 6553600.000000 */
	पूर्ण;

	u8 i = 0;
	u32 y = 0;
	u32 d = 0;
	u32 k = 0;
	u32 r = 0;

	अगर (x == 0)
		वापस 0;

	/* Scale x (normalize) */
	/* computing y in log(x/y) = log(x) - log(y) */
	अगर ((x & (((u32) (-1)) << (scale + 1))) == 0) अणु
		क्रम (k = scale; k > 0; k--) अणु
			अगर (x & (((u32) 1) << scale))
				अवरोध;
			x <<= 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (k = scale; k < 31; k++) अणु
			अगर ((x & (((u32) (-1)) << (scale + 1))) == 0)
				अवरोध;
			x >>= 1;
		पूर्ण
	पूर्ण
	/*
	   Now x has binary poपूर्णांक between bit[scale] and bit[scale-1]
	   and 1.0 <= x < 2.0 */

	/* correction क्रम भागision: log(x) = log(x/y)+log(y) */
	y = k * ((((u32) 1) << scale) * 200);

	/* हटाओ पूर्णांकeger part */
	x &= ((((u32) 1) << scale) - 1);
	/* get index */
	i = (u8) (x >> (scale - index_width));
	/* compute delta (x-a) */
	d = x & ((((u32) 1) << (scale - index_width)) - 1);
	/* compute log, multiplication ( d* (.. )) must be within range ! */
	y += log2lut[i] +
	    ((d * (log2lut[i + 1] - log2lut[i])) >> (scale - index_width));
	/* Conver to log10() */
	y /= 108853;		/* (log2(10) << scale) */
	r = (y >> 1);
	/* rounding */
	अगर (y & ((u32)1))
		r++;

	वापस r;

पूर्ण

/*
* \पn u32 frac_बार1e6( u16 N, u32 D)
* \मrief Compute: (N/D) * 1000000.
* \param N nominator 16-bits.
* \param D denominator 32-bits.
* \लeturn u32
* \लetval ((N/D) * 1000000), 32 bits
*
* No check on D=0!
*/
अटल u32 frac_बार1e6(u32 N, u32 D)
अणु
	u32 reमुख्यder = 0;
	u32 frac = 0;

	/*
	   frac = (N * 1000000) / D
	   To let it fit in a 32 bits computation:
	   frac = (N * (1000000 >> 4)) / (D >> 4)
	   This would result in a problem in हाल D < 16 (भाग by 0).
	   So we करो it more elaborate as shown below.
	 */
	frac = (((u32) N) * (1000000 >> 4)) / D;
	frac <<= 4;
	reमुख्यder = (((u32) N) * (1000000 >> 4)) % D;
	reमुख्यder <<= 4;
	frac += reमुख्यder / D;
	reमुख्यder = reमुख्यder % D;
	अगर ((reमुख्यder * 2) > D)
		frac++;

	वापस frac;
पूर्ण

/*============================================================================*/


/*
* \मrief Values क्रम NICAM prescaler gain. Computed from dB to पूर्णांकeger
*        and rounded. For calc used क्रमmula: 16*10^(prescaleGain[dB]/20).
*
*/
#अगर 0
/* Currently, unused as we lack support क्रम analog TV */
अटल स्थिर u16 nicam_presc_table_val[43] = अणु
	1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 4, 4,
	5, 5, 6, 6, 7, 8, 9, 10, 11, 13, 14, 16,
	18, 20, 23, 25, 28, 32, 36, 40, 45,
	51, 57, 64, 71, 80, 90, 101, 113, 127
पूर्ण;
#पूर्ण_अगर

/*============================================================================*/
/*==                        END HELPER FUNCTIONS                            ==*/
/*============================================================================*/

/*============================================================================*/
/*============================================================================*/
/*==                      DRXJ DAP FUNCTIONS                                ==*/
/*============================================================================*/
/*============================================================================*/

/*
   This layer takes care of some device specअगरic रेजिस्टर access protocols:
   -conversion to लघु address क्रमmat
   -access to audio block
   This layer is placed between the drx_dap_fasi and the rest of the drxj
   specअगरic implementation. This layer can use address map knowledge whereas
   dap_fasi may not use memory map knowledge.

   * For audio currently only 16 bits पढ़ो and ग_लिखो रेजिस्टर access is
     supported. More is not needed. RMW and 32 or 8 bit access on audio
     रेजिस्टरs will have undefined behaviour. Flags (RMW, CRC reset, broadcast
     single/multi master) will be ignored.

   TODO: check ignoring single/multimaster is ok क्रम AUD access ?
*/

#घोषणा DRXJ_ISAUDWRITE(addr) (((((addr)>>16)&1) == 1) ? true : false)
#घोषणा DRXJ_DAP_AUDTRIF_TIMEOUT 80	/* millisec */
/*============================================================================*/

/*
* \पn bool is_handled_by_aud_tr_अगर( u32 addr )
* \मrief Check अगर this address is handled by the audio token ring पूर्णांकerface.
* \param addr
* \लeturn bool
* \लetval true  Yes, handled by audio token ring पूर्णांकerface
* \लetval false No, not handled by audio token ring पूर्णांकerface
*
*/
अटल
bool is_handled_by_aud_tr_अगर(u32 addr)
अणु
	bool retval = false;

	अगर ((DRXDAP_FASI_ADDR2BLOCK(addr) == 4) &&
	    (DRXDAP_FASI_ADDR2BANK(addr) > 1) &&
	    (DRXDAP_FASI_ADDR2BANK(addr) < 6)) अणु
		retval = true;
	पूर्ण

	वापस retval;
पूर्ण

/*============================================================================*/

पूर्णांक drxbsp_i2c_ग_लिखो_पढ़ो(काष्ठा i2c_device_addr *w_dev_addr,
				 u16 w_count,
				 u8 *wData,
				 काष्ठा i2c_device_addr *r_dev_addr,
				 u16 r_count, u8 *r_data)
अणु
	काष्ठा drx39xxj_state *state;
	काष्ठा i2c_msg msg[2];
	अचिन्हित पूर्णांक num_msgs;

	अगर (w_dev_addr == शून्य) अणु
		/* Read only */
		state = r_dev_addr->user_data;
		msg[0].addr = r_dev_addr->i2c_addr >> 1;
		msg[0].flags = I2C_M_RD;
		msg[0].buf = r_data;
		msg[0].len = r_count;
		num_msgs = 1;
	पूर्ण अन्यथा अगर (r_dev_addr == शून्य) अणु
		/* Write only */
		state = w_dev_addr->user_data;
		msg[0].addr = w_dev_addr->i2c_addr >> 1;
		msg[0].flags = 0;
		msg[0].buf = wData;
		msg[0].len = w_count;
		num_msgs = 1;
	पूर्ण अन्यथा अणु
		/* Both ग_लिखो and पढ़ो */
		state = w_dev_addr->user_data;
		msg[0].addr = w_dev_addr->i2c_addr >> 1;
		msg[0].flags = 0;
		msg[0].buf = wData;
		msg[0].len = w_count;
		msg[1].addr = r_dev_addr->i2c_addr >> 1;
		msg[1].flags = I2C_M_RD;
		msg[1].buf = r_data;
		msg[1].len = r_count;
		num_msgs = 2;
	पूर्ण

	अगर (state->i2c == शून्य) अणु
		pr_err("i2c was zero, aborting\n");
		वापस 0;
	पूर्ण
	अगर (i2c_transfer(state->i2c, msg, num_msgs) != num_msgs) अणु
		pr_warn("drx3933: I2C write/read failed\n");
		वापस -EREMOTEIO;
	पूर्ण

#अगर_घोषित DJH_DEBUG
	अगर (w_dev_addr == शून्य || r_dev_addr == शून्य)
		वापस 0;

	state = w_dev_addr->user_data;

	अगर (state->i2c == शून्य)
		वापस 0;

	msg[0].addr = w_dev_addr->i2c_addr;
	msg[0].flags = 0;
	msg[0].buf = wData;
	msg[0].len = w_count;
	msg[1].addr = r_dev_addr->i2c_addr;
	msg[1].flags = I2C_M_RD;
	msg[1].buf = r_data;
	msg[1].len = r_count;
	num_msgs = 2;

	pr_debug("drx3933 i2c operation addr=%x i2c=%p, wc=%x rc=%x\n",
	       w_dev_addr->i2c_addr, state->i2c, w_count, r_count);

	अगर (i2c_transfer(state->i2c, msg, 2) != 2) अणु
		pr_warn("drx3933: I2C write/read failed\n");
		वापस -EREMOTEIO;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

/*============================================================================*/

/*****************************
*
* पूर्णांक drxdap_fasi_पढ़ो_block (
*      काष्ठा i2c_device_addr *dev_addr,      -- address of I2C device
*      u32 addr,         -- address of chip रेजिस्टर/memory
*      u16            datasize,     -- number of bytes to पढ़ो
*      u8 *data,         -- data to receive
*      u32 flags)        -- special device flags
*
* Read block data from chip address. Because the chip is word oriented,
* the number of bytes to पढ़ो must be even.
*
* Make sure that the buffer to receive the data is large enough.
*
* Although this function expects an even number of bytes, it is still byte
* oriented, and the data पढ़ो back is NOT translated to the endianness of
* the target platक्रमm.
*
* Output:
* - 0     अगर पढ़ोing was successful
*                  in that हाल: data पढ़ो is in *data.
* - -EIO  अगर anything went wrong
*
******************************/

अटल पूर्णांक drxdap_fasi_पढ़ो_block(काष्ठा i2c_device_addr *dev_addr,
					 u32 addr,
					 u16 datasize,
					 u8 *data, u32 flags)
अणु
	u8 buf[4];
	u16 bufx;
	पूर्णांक rc;
	u16 overhead_size = 0;

	/* Check parameters ******************************************************* */
	अगर (dev_addr == शून्य)
		वापस -EINVAL;

	overhead_size = (IS_I2C_10BIT(dev_addr->i2c_addr) ? 2 : 1) +
	    (DRXDAP_FASI_LONG_FORMAT(addr) ? 4 : 2);

	अगर ((DRXDAP_FASI_OFFSET_TOO_LARGE(addr)) ||
	    ((!(DRXDAPFASI_LONG_ADDR_ALLOWED)) &&
	     DRXDAP_FASI_LONG_FORMAT(addr)) ||
	    (overhead_size > (DRXDAP_MAX_WCHUNKSIZE)) ||
	    ((datasize != 0) && (data == शून्य)) || ((datasize & 1) == 1)) अणु
		वापस -EINVAL;
	पूर्ण

	/* ReadModअगरyWrite & mode flag bits are not allowed */
	flags &= (~DRXDAP_FASI_RMW & ~DRXDAP_FASI_MODEFLAGS);
#अगर DRXDAP_SINGLE_MASTER
	flags |= DRXDAP_FASI_SINGLE_MASTER;
#पूर्ण_अगर

	/* Read block from I2C **************************************************** */
	करो अणु
		u16 toकरो = (datasize < DRXDAP_MAX_RCHUNKSIZE ?
			      datasize : DRXDAP_MAX_RCHUNKSIZE);

		bufx = 0;

		addr &= ~DRXDAP_FASI_FLAGS;
		addr |= flags;

#अगर ((DRXDAPFASI_LONG_ADDR_ALLOWED == 1) && (DRXDAPFASI_SHORT_ADDR_ALLOWED == 1))
		/* लघु क्रमmat address preferred but दीर्घ क्रमmat otherwise */
		अगर (DRXDAP_FASI_LONG_FORMAT(addr)) अणु
#पूर्ण_अगर
#अगर (DRXDAPFASI_LONG_ADDR_ALLOWED == 1)
			buf[bufx++] = (u8) (((addr << 1) & 0xFF) | 0x01);
			buf[bufx++] = (u8) ((addr >> 16) & 0xFF);
			buf[bufx++] = (u8) ((addr >> 24) & 0xFF);
			buf[bufx++] = (u8) ((addr >> 7) & 0xFF);
#पूर्ण_अगर
#अगर ((DRXDAPFASI_LONG_ADDR_ALLOWED == 1) && (DRXDAPFASI_SHORT_ADDR_ALLOWED == 1))
		पूर्ण अन्यथा अणु
#पूर्ण_अगर
#अगर (DRXDAPFASI_SHORT_ADDR_ALLOWED == 1)
			buf[bufx++] = (u8) ((addr << 1) & 0xFF);
			buf[bufx++] =
			    (u8) (((addr >> 16) & 0x0F) |
				    ((addr >> 18) & 0xF0));
#पूर्ण_अगर
#अगर ((DRXDAPFASI_LONG_ADDR_ALLOWED == 1) && (DRXDAPFASI_SHORT_ADDR_ALLOWED == 1))
		पूर्ण
#पूर्ण_अगर

#अगर DRXDAP_SINGLE_MASTER
		/*
		 * In single master mode, split the पढ़ो and ग_लिखो actions.
		 * No special action is needed क्रम ग_लिखो chunks here.
		 */
		rc = drxbsp_i2c_ग_लिखो_पढ़ो(dev_addr, bufx, buf,
					   शून्य, 0, शून्य);
		अगर (rc == 0)
			rc = drxbsp_i2c_ग_लिखो_पढ़ो(शून्य, 0, शून्य, dev_addr, toकरो, data);
#अन्यथा
		/* In multi master mode, करो everything in one RW action */
		rc = drxbsp_i2c_ग_लिखो_पढ़ो(dev_addr, bufx, buf, dev_addr, toकरो,
					  data);
#पूर्ण_अगर
		data += toकरो;
		addr += (toकरो >> 1);
		datasize -= toकरो;
	पूर्ण जबतक (datasize && rc == 0);

	वापस rc;
पूर्ण


/*****************************
*
* पूर्णांक drxdap_fasi_पढ़ो_reg16 (
*     काष्ठा i2c_device_addr *dev_addr, -- address of I2C device
*     u32 addr,    -- address of chip रेजिस्टर/memory
*     u16 *data,    -- data to receive
*     u32 flags)   -- special device flags
*
* Read one 16-bit रेजिस्टर or memory location. The data received back is
* converted back to the target platक्रमm's endianness.
*
* Output:
* - 0     अगर पढ़ोing was successful
*                  in that हाल: पढ़ो data is at *data
* - -EIO  अगर anything went wrong
*
******************************/

अटल पूर्णांक drxdap_fasi_पढ़ो_reg16(काष्ठा i2c_device_addr *dev_addr,
					 u32 addr,
					 u16 *data, u32 flags)
अणु
	u8 buf[माप(*data)];
	पूर्णांक rc;

	अगर (!data)
		वापस -EINVAL;

	rc = drxdap_fasi_पढ़ो_block(dev_addr, addr, माप(*data), buf, flags);
	*data = buf[0] + (((u16) buf[1]) << 8);
	वापस rc;
पूर्ण

/*****************************
*
* पूर्णांक drxdap_fasi_पढ़ो_reg32 (
*     काष्ठा i2c_device_addr *dev_addr, -- address of I2C device
*     u32 addr,    -- address of chip रेजिस्टर/memory
*     u32 *data,    -- data to receive
*     u32 flags)   -- special device flags
*
* Read one 32-bit रेजिस्टर or memory location. The data received back is
* converted back to the target platक्रमm's endianness.
*
* Output:
* - 0     अगर पढ़ोing was successful
*                  in that हाल: पढ़ो data is at *data
* - -EIO  अगर anything went wrong
*
******************************/

अटल पूर्णांक drxdap_fasi_पढ़ो_reg32(काष्ठा i2c_device_addr *dev_addr,
					 u32 addr,
					 u32 *data, u32 flags)
अणु
	u8 buf[माप(*data)];
	पूर्णांक rc;

	अगर (!data)
		वापस -EINVAL;

	rc = drxdap_fasi_पढ़ो_block(dev_addr, addr, माप(*data), buf, flags);
	*data = (((u32) buf[0]) << 0) +
	    (((u32) buf[1]) << 8) +
	    (((u32) buf[2]) << 16) + (((u32) buf[3]) << 24);
	वापस rc;
पूर्ण

/*****************************
*
* पूर्णांक drxdap_fasi_ग_लिखो_block (
*      काष्ठा i2c_device_addr *dev_addr,    -- address of I2C device
*      u32 addr,       -- address of chip रेजिस्टर/memory
*      u16            datasize,   -- number of bytes to पढ़ो
*      u8 *data,       -- data to receive
*      u32 flags)      -- special device flags
*
* Write block data to chip address. Because the chip is word oriented,
* the number of bytes to ग_लिखो must be even.
*
* Although this function expects an even number of bytes, it is still byte
* oriented, and the data being written is NOT translated from the endianness of
* the target platक्रमm.
*
* Output:
* - 0     अगर writing was successful
* - -EIO  अगर anything went wrong
*
******************************/

अटल पूर्णांक drxdap_fasi_ग_लिखो_block(काष्ठा i2c_device_addr *dev_addr,
					  u32 addr,
					  u16 datasize,
					  u8 *data, u32 flags)
अणु
	u8 buf[DRXDAP_MAX_WCHUNKSIZE];
	पूर्णांक st = -EIO;
	पूर्णांक first_err = 0;
	u16 overhead_size = 0;
	u16 block_size = 0;

	/* Check parameters ******************************************************* */
	अगर (dev_addr == शून्य)
		वापस -EINVAL;

	overhead_size = (IS_I2C_10BIT(dev_addr->i2c_addr) ? 2 : 1) +
	    (DRXDAP_FASI_LONG_FORMAT(addr) ? 4 : 2);

	अगर ((DRXDAP_FASI_OFFSET_TOO_LARGE(addr)) ||
	    ((!(DRXDAPFASI_LONG_ADDR_ALLOWED)) &&
	     DRXDAP_FASI_LONG_FORMAT(addr)) ||
	    (overhead_size > (DRXDAP_MAX_WCHUNKSIZE)) ||
	    ((datasize != 0) && (data == शून्य)) || ((datasize & 1) == 1))
		वापस -EINVAL;

	flags &= DRXDAP_FASI_FLAGS;
	flags &= ~DRXDAP_FASI_MODEFLAGS;
#अगर DRXDAP_SINGLE_MASTER
	flags |= DRXDAP_FASI_SINGLE_MASTER;
#पूर्ण_अगर

	/* Write block to I2C ***************************************************** */
	block_size = ((DRXDAP_MAX_WCHUNKSIZE) - overhead_size) & ~1;
	करो अणु
		u16 toकरो = 0;
		u16 bufx = 0;

		/* Buffer device address */
		addr &= ~DRXDAP_FASI_FLAGS;
		addr |= flags;
#अगर (((DRXDAPFASI_LONG_ADDR_ALLOWED) == 1) && ((DRXDAPFASI_SHORT_ADDR_ALLOWED) == 1))
		/* लघु क्रमmat address preferred but दीर्घ क्रमmat otherwise */
		अगर (DRXDAP_FASI_LONG_FORMAT(addr)) अणु
#पूर्ण_अगर
#अगर ((DRXDAPFASI_LONG_ADDR_ALLOWED) == 1)
			buf[bufx++] = (u8) (((addr << 1) & 0xFF) | 0x01);
			buf[bufx++] = (u8) ((addr >> 16) & 0xFF);
			buf[bufx++] = (u8) ((addr >> 24) & 0xFF);
			buf[bufx++] = (u8) ((addr >> 7) & 0xFF);
#पूर्ण_अगर
#अगर (((DRXDAPFASI_LONG_ADDR_ALLOWED) == 1) && ((DRXDAPFASI_SHORT_ADDR_ALLOWED) == 1))
		पूर्ण अन्यथा अणु
#पूर्ण_अगर
#अगर ((DRXDAPFASI_SHORT_ADDR_ALLOWED) == 1)
			buf[bufx++] = (u8) ((addr << 1) & 0xFF);
			buf[bufx++] =
			    (u8) (((addr >> 16) & 0x0F) |
				    ((addr >> 18) & 0xF0));
#पूर्ण_अगर
#अगर (((DRXDAPFASI_LONG_ADDR_ALLOWED) == 1) && ((DRXDAPFASI_SHORT_ADDR_ALLOWED) == 1))
		पूर्ण
#पूर्ण_अगर

		/*
		   In single master mode block_size can be 0. In such a हाल this I2C
		   sequense will be visible: (1) ग_लिखो address अणुi2c addr,
		   4 bytes chip addressपूर्ण (2) ग_लिखो data अणुi2c addr, 4 bytes data पूर्ण
		   (3) ग_लिखो address (4) ग_लिखो data etc...
		   Address must be rewritten because HI is reset after data transport and
		   expects an address.
		 */
		toकरो = (block_size < datasize ? block_size : datasize);
		अगर (toकरो == 0) अणु
			u16 overhead_size_i2c_addr = 0;
			u16 data_block_size = 0;

			overhead_size_i2c_addr =
			    (IS_I2C_10BIT(dev_addr->i2c_addr) ? 2 : 1);
			data_block_size =
			    (DRXDAP_MAX_WCHUNKSIZE - overhead_size_i2c_addr) & ~1;

			/* ग_लिखो device address */
			st = drxbsp_i2c_ग_लिखो_पढ़ो(dev_addr,
						  (u16) (bufx),
						  buf,
						  (काष्ठा i2c_device_addr *)(शून्य),
						  0, (u8 *)(शून्य));

			अगर ((st != 0) && (first_err == 0)) अणु
				/* at the end, वापस the first error encountered */
				first_err = st;
			पूर्ण
			bufx = 0;
			toकरो =
			    (data_block_size <
			     datasize ? data_block_size : datasize);
		पूर्ण
		स_नकल(&buf[bufx], data, toकरो);
		/* ग_लिखो (address अगर can करो and) data */
		st = drxbsp_i2c_ग_लिखो_पढ़ो(dev_addr,
					  (u16) (bufx + toकरो),
					  buf,
					  (काष्ठा i2c_device_addr *)(शून्य),
					  0, (u8 *)(शून्य));

		अगर ((st != 0) && (first_err == 0)) अणु
			/* at the end, वापस the first error encountered */
			first_err = st;
		पूर्ण
		datasize -= toकरो;
		data += toकरो;
		addr += (toकरो >> 1);
	पूर्ण जबतक (datasize);

	वापस first_err;
पूर्ण

/*****************************
*
* पूर्णांक drxdap_fasi_ग_लिखो_reg16 (
*     काष्ठा i2c_device_addr *dev_addr, -- address of I2C device
*     u32 addr,    -- address of chip रेजिस्टर/memory
*     u16            data,    -- data to send
*     u32 flags)   -- special device flags
*
* Write one 16-bit रेजिस्टर or memory location. The data being written is
* converted from the target platक्रमm's endianness to little endian.
*
* Output:
* - 0     अगर writing was successful
* - -EIO  अगर anything went wrong
*
******************************/

अटल पूर्णांक drxdap_fasi_ग_लिखो_reg16(काष्ठा i2c_device_addr *dev_addr,
					  u32 addr,
					  u16 data, u32 flags)
अणु
	u8 buf[माप(data)];

	buf[0] = (u8) ((data >> 0) & 0xFF);
	buf[1] = (u8) ((data >> 8) & 0xFF);

	वापस drxdap_fasi_ग_लिखो_block(dev_addr, addr, माप(data), buf, flags);
पूर्ण

/*****************************
*
* पूर्णांक drxdap_fasi_पढ़ो_modअगरy_ग_लिखो_reg16 (
*      काष्ठा i2c_device_addr *dev_addr,   -- address of I2C device
*      u32 waddr,     -- address of chip रेजिस्टर/memory
*      u32 raddr,     -- chip address to पढ़ो back from
*      u16            wdata,     -- data to send
*      u16 *rdata)     -- data to receive back
*
* Write 16-bit data, then पढ़ो back the original contents of that location.
* Requires दीर्घ addressing क्रमmat to be allowed.
*
* Beक्रमe sending data, the data is converted to little endian. The
* data received back is converted back to the target platक्रमm's endianness.
*
* WARNING: This function is only guaranteed to work अगर there is one
* master on the I2C bus.
*
* Output:
* - 0     अगर पढ़ोing was successful
*                  in that हाल: पढ़ो back data is at *rdata
* - -EIO  अगर anything went wrong
*
******************************/

अटल पूर्णांक drxdap_fasi_पढ़ो_modअगरy_ग_लिखो_reg16(काष्ठा i2c_device_addr *dev_addr,
						    u32 waddr,
						    u32 raddr,
						    u16 wdata, u16 *rdata)
अणु
	पूर्णांक rc = -EIO;

#अगर (DRXDAPFASI_LONG_ADDR_ALLOWED == 1)
	अगर (rdata == शून्य)
		वापस -EINVAL;

	rc = drxdap_fasi_ग_लिखो_reg16(dev_addr, waddr, wdata, DRXDAP_FASI_RMW);
	अगर (rc == 0)
		rc = drxdap_fasi_पढ़ो_reg16(dev_addr, raddr, rdata, 0);
#पूर्ण_अगर

	वापस rc;
पूर्ण

/*****************************
*
* पूर्णांक drxdap_fasi_ग_लिखो_reg32 (
*     काष्ठा i2c_device_addr *dev_addr, -- address of I2C device
*     u32 addr,    -- address of chip रेजिस्टर/memory
*     u32            data,    -- data to send
*     u32 flags)   -- special device flags
*
* Write one 32-bit रेजिस्टर or memory location. The data being written is
* converted from the target platक्रमm's endianness to little endian.
*
* Output:
* - 0     अगर writing was successful
* - -EIO  अगर anything went wrong
*
******************************/

अटल पूर्णांक drxdap_fasi_ग_लिखो_reg32(काष्ठा i2c_device_addr *dev_addr,
					  u32 addr,
					  u32 data, u32 flags)
अणु
	u8 buf[माप(data)];

	buf[0] = (u8) ((data >> 0) & 0xFF);
	buf[1] = (u8) ((data >> 8) & 0xFF);
	buf[2] = (u8) ((data >> 16) & 0xFF);
	buf[3] = (u8) ((data >> 24) & 0xFF);

	वापस drxdap_fasi_ग_लिखो_block(dev_addr, addr, माप(data), buf, flags);
पूर्ण

/*============================================================================*/

/*
* \पn पूर्णांक drxj_dap_rm_ग_लिखो_reg16लघु
* \मrief Read modअगरy ग_लिखो 16 bits audio रेजिस्टर using लघु क्रमmat only.
* \param dev_addr
* \param waddr    Address to ग_लिखो to
* \param raddr    Address to पढ़ो from (usually SIO_HI_RA_RAM_S0_RMWBUF__A)
* \param wdata    Data to ग_लिखो
* \param rdata    Buffer क्रम data to पढ़ो
* \लeturn पूर्णांक
* \लetval 0 Success
* \लetval -EIO Timeout, I2C error, illegal bank
*
* 16 bits रेजिस्टर पढ़ो modअगरy ग_लिखो access using लघु addressing क्रमmat only.
* Requires knowledge of the रेजिस्टरmap, thus device dependent.
* Using DAP FASI directly to aव्योम endless recursion of RMWs to audio रेजिस्टरs.
*
*/

/* TODO correct define should be #अगर ( DRXDAPFASI_SHORT_ADDR_ALLOWED==1 )
   See comments drxj_dap_पढ़ो_modअगरy_ग_लिखो_reg16 */
#अगर (DRXDAPFASI_LONG_ADDR_ALLOWED == 0)
अटल पूर्णांक drxj_dap_rm_ग_लिखो_reg16लघु(काष्ठा i2c_device_addr *dev_addr,
					      u32 waddr,
					      u32 raddr,
					      u16 wdata, u16 *rdata)
अणु
	पूर्णांक rc;

	अगर (rdata == शून्य)
		वापस -EINVAL;

	/* Set RMW flag */
	rc = drxdap_fasi_ग_लिखो_reg16(dev_addr,
					      SIO_HI_RA_RAM_S0_FLG_ACC__A,
					      SIO_HI_RA_RAM_S0_FLG_ACC_S0_RWM__M,
					      0x0000);
	अगर (rc == 0) अणु
		/* Write new data: triggers RMW */
		rc = drxdap_fasi_ग_लिखो_reg16(dev_addr, waddr, wdata,
						      0x0000);
	पूर्ण
	अगर (rc == 0) अणु
		/* Read old data */
		rc = drxdap_fasi_पढ़ो_reg16(dev_addr, raddr, rdata,
						     0x0000);
	पूर्ण
	अगर (rc == 0) अणु
		/* Reset RMW flag */
		rc = drxdap_fasi_ग_लिखो_reg16(dev_addr,
						      SIO_HI_RA_RAM_S0_FLG_ACC__A,
						      0, 0x0000);
	पूर्ण

	वापस rc;
पूर्ण
#पूर्ण_अगर

/*============================================================================*/

अटल पूर्णांक drxj_dap_पढ़ो_modअगरy_ग_लिखो_reg16(काष्ठा i2c_device_addr *dev_addr,
						 u32 waddr,
						 u32 raddr,
						 u16 wdata, u16 *rdata)
अणु
	/* TODO: correct लघु/दीर्घ addressing क्रमmat decision,
	   now दीर्घ क्रमmat has higher prio then लघु because लघु also
	   needs virt bnks (not impl yet) क्रम certain audio रेजिस्टरs */
#अगर (DRXDAPFASI_LONG_ADDR_ALLOWED == 1)
	वापस drxdap_fasi_पढ़ो_modअगरy_ग_लिखो_reg16(dev_addr,
							  waddr,
							  raddr, wdata, rdata);
#अन्यथा
	वापस drxj_dap_rm_ग_लिखो_reg16लघु(dev_addr, waddr, raddr, wdata, rdata);
#पूर्ण_अगर
पूर्ण


/*============================================================================*/

/*
* \पn पूर्णांक drxj_dap_पढ़ो_aud_reg16
* \मrief Read 16 bits audio रेजिस्टर
* \param dev_addr
* \param addr
* \param data
* \लeturn पूर्णांक
* \लetval 0 Success
* \लetval -EIO Timeout, I2C error, illegal bank
*
* 16 bits रेजिस्टर पढ़ो access via audio token ring पूर्णांकerface.
*
*/
अटल पूर्णांक drxj_dap_पढ़ो_aud_reg16(काष्ठा i2c_device_addr *dev_addr,
					 u32 addr, u16 *data)
अणु
	u32 start_समयr = 0;
	u32 current_समयr = 0;
	u32 delta_समयr = 0;
	u16 tr_status = 0;
	पूर्णांक stat = -EIO;

	/* No पढ़ो possible क्रम bank 3, वापस with error */
	अगर (DRXDAP_FASI_ADDR2BANK(addr) == 3) अणु
		stat = -EINVAL;
	पूर्ण अन्यथा अणु
		स्थिर u32 ग_लिखो_bit = ((dr_xaddr_t) 1) << 16;

		/* Force reset ग_लिखो bit */
		addr &= (~ग_लिखो_bit);

		/* Set up पढ़ो */
		start_समयr = jअगरfies_to_msecs(jअगरfies);
		करो अणु
			/* RMW to aud TR IF until request is granted or समयout */
			stat = drxj_dap_पढ़ो_modअगरy_ग_लिखो_reg16(dev_addr,
							     addr,
							     SIO_HI_RA_RAM_S0_RMWBUF__A,
							     0x0000, &tr_status);

			अगर (stat != 0)
				अवरोध;

			current_समयr = jअगरfies_to_msecs(jअगरfies);
			delta_समयr = current_समयr - start_समयr;
			अगर (delta_समयr > DRXJ_DAP_AUDTRIF_TIMEOUT) अणु
				stat = -EIO;
				अवरोध;
			पूर्ण

		पूर्ण जबतक (((tr_status & AUD_TOP_TR_CTR_FIFO_LOCK__M) ==
			  AUD_TOP_TR_CTR_FIFO_LOCK_LOCKED) ||
			 ((tr_status & AUD_TOP_TR_CTR_FIFO_FULL__M) ==
			  AUD_TOP_TR_CTR_FIFO_FULL_FULL));
	पूर्ण			/* अगर ( DRXDAP_FASI_ADDR2BANK(addr)!=3 ) */

	/* Wait क्रम पढ़ो पढ़ोy status or समयout */
	अगर (stat == 0) अणु
		start_समयr = jअगरfies_to_msecs(jअगरfies);

		जबतक ((tr_status & AUD_TOP_TR_CTR_FIFO_RD_RDY__M) !=
		       AUD_TOP_TR_CTR_FIFO_RD_RDY_READY) अणु
			stat = drxj_dap_पढ़ो_reg16(dev_addr,
						  AUD_TOP_TR_CTR__A,
						  &tr_status, 0x0000);
			अगर (stat != 0)
				अवरोध;

			current_समयr = jअगरfies_to_msecs(jअगरfies);
			delta_समयr = current_समयr - start_समयr;
			अगर (delta_समयr > DRXJ_DAP_AUDTRIF_TIMEOUT) अणु
				stat = -EIO;
				अवरोध;
			पूर्ण
		पूर्ण		/* जबतक ( ... ) */
	पूर्ण

	/* Read value */
	अगर (stat == 0)
		stat = drxj_dap_पढ़ो_modअगरy_ग_लिखो_reg16(dev_addr,
						     AUD_TOP_TR_RD_REG__A,
						     SIO_HI_RA_RAM_S0_RMWBUF__A,
						     0x0000, data);
	वापस stat;
पूर्ण

/*============================================================================*/

अटल पूर्णांक drxj_dap_पढ़ो_reg16(काष्ठा i2c_device_addr *dev_addr,
				      u32 addr,
				      u16 *data, u32 flags)
अणु
	पूर्णांक stat = -EIO;

	/* Check param */
	अगर ((dev_addr == शून्य) || (data == शून्य))
		वापस -EINVAL;

	अगर (is_handled_by_aud_tr_अगर(addr))
		stat = drxj_dap_पढ़ो_aud_reg16(dev_addr, addr, data);
	अन्यथा
		stat = drxdap_fasi_पढ़ो_reg16(dev_addr, addr, data, flags);

	वापस stat;
पूर्ण
/*============================================================================*/

/*
* \पn पूर्णांक drxj_dap_ग_लिखो_aud_reg16
* \मrief Write 16 bits audio रेजिस्टर
* \param dev_addr
* \param addr
* \param data
* \लeturn पूर्णांक
* \लetval 0 Success
* \लetval -EIO Timeout, I2C error, illegal bank
*
* 16 bits रेजिस्टर ग_लिखो access via audio token ring पूर्णांकerface.
*
*/
अटल पूर्णांक drxj_dap_ग_लिखो_aud_reg16(काष्ठा i2c_device_addr *dev_addr,
					  u32 addr, u16 data)
अणु
	पूर्णांक stat = -EIO;

	/* No ग_लिखो possible क्रम bank 2, वापस with error */
	अगर (DRXDAP_FASI_ADDR2BANK(addr) == 2) अणु
		stat = -EINVAL;
	पूर्ण अन्यथा अणु
		u32 start_समयr = 0;
		u32 current_समयr = 0;
		u32 delta_समयr = 0;
		u16 tr_status = 0;
		स्थिर u32 ग_लिखो_bit = ((dr_xaddr_t) 1) << 16;

		/* Force ग_लिखो bit */
		addr |= ग_लिखो_bit;
		start_समयr = jअगरfies_to_msecs(jअगरfies);
		करो अणु
			/* RMW to aud TR IF until request is granted or समयout */
			stat = drxj_dap_पढ़ो_modअगरy_ग_लिखो_reg16(dev_addr,
							     addr,
							     SIO_HI_RA_RAM_S0_RMWBUF__A,
							     data, &tr_status);
			अगर (stat != 0)
				अवरोध;

			current_समयr = jअगरfies_to_msecs(jअगरfies);
			delta_समयr = current_समयr - start_समयr;
			अगर (delta_समयr > DRXJ_DAP_AUDTRIF_TIMEOUT) अणु
				stat = -EIO;
				अवरोध;
			पूर्ण

		पूर्ण जबतक (((tr_status & AUD_TOP_TR_CTR_FIFO_LOCK__M) ==
			  AUD_TOP_TR_CTR_FIFO_LOCK_LOCKED) ||
			 ((tr_status & AUD_TOP_TR_CTR_FIFO_FULL__M) ==
			  AUD_TOP_TR_CTR_FIFO_FULL_FULL));

	पूर्ण			/* अगर ( DRXDAP_FASI_ADDR2BANK(addr)!=2 ) */

	वापस stat;
पूर्ण

/*============================================================================*/

अटल पूर्णांक drxj_dap_ग_लिखो_reg16(काष्ठा i2c_device_addr *dev_addr,
				       u32 addr,
				       u16 data, u32 flags)
अणु
	पूर्णांक stat = -EIO;

	/* Check param */
	अगर (dev_addr == शून्य)
		वापस -EINVAL;

	अगर (is_handled_by_aud_tr_अगर(addr))
		stat = drxj_dap_ग_लिखो_aud_reg16(dev_addr, addr, data);
	अन्यथा
		stat = drxdap_fasi_ग_लिखो_reg16(dev_addr,
							    addr, data, flags);

	वापस stat;
पूर्ण

/*============================================================================*/

/* Free data ram in SIO HI */
#घोषणा SIO_HI_RA_RAM_USR_BEGIN__A 0x420040
#घोषणा SIO_HI_RA_RAM_USR_END__A   0x420060

#घोषणा DRXJ_HI_ATOMIC_BUF_START (SIO_HI_RA_RAM_USR_BEGIN__A)
#घोषणा DRXJ_HI_ATOMIC_BUF_END   (SIO_HI_RA_RAM_USR_BEGIN__A + 7)
#घोषणा DRXJ_HI_ATOMIC_READ      SIO_HI_RA_RAM_PAR_3_ACP_RW_READ
#घोषणा DRXJ_HI_ATOMIC_WRITE     SIO_HI_RA_RAM_PAR_3_ACP_RW_WRITE

/*
* \पn पूर्णांक drxj_dap_atomic_पढ़ो_ग_लिखो_block()
* \मrief Basic access routine क्रम atomic पढ़ो or ग_लिखो access
* \param dev_addr  poपूर्णांकer to i2c dev address
* \param addr     destination/source address
* \param datasize size of data buffer in bytes
* \param data     poपूर्णांकer to data buffer
* \लeturn पूर्णांक
* \लetval 0 Success
* \लetval -EIO Timeout, I2C error, illegal bank
*
*/
अटल
पूर्णांक drxj_dap_atomic_पढ़ो_ग_लिखो_block(काष्ठा i2c_device_addr *dev_addr,
					  u32 addr,
					  u16 datasize,
					  u8 *data, bool पढ़ो_flag)
अणु
	काष्ठा drxj_hi_cmd hi_cmd;
	पूर्णांक rc;
	u16 word;
	u16 dummy = 0;
	u16 i = 0;

	/* Parameter check */
	अगर (!data || !dev_addr || ((datasize % 2)) || ((datasize / 2) > 8))
		वापस -EINVAL;

	/* Set up HI parameters to पढ़ो or ग_लिखो n bytes */
	hi_cmd.cmd = SIO_HI_RA_RAM_CMD_ATOMIC_COPY;
	hi_cmd.param1 =
	    (u16) ((DRXDAP_FASI_ADDR2BLOCK(DRXJ_HI_ATOMIC_BUF_START) << 6) +
		     DRXDAP_FASI_ADDR2BANK(DRXJ_HI_ATOMIC_BUF_START));
	hi_cmd.param2 =
	    (u16) DRXDAP_FASI_ADDR2OFFSET(DRXJ_HI_ATOMIC_BUF_START);
	hi_cmd.param3 = (u16) ((datasize / 2) - 1);
	अगर (!पढ़ो_flag)
		hi_cmd.param3 |= DRXJ_HI_ATOMIC_WRITE;
	अन्यथा
		hi_cmd.param3 |= DRXJ_HI_ATOMIC_READ;
	hi_cmd.param4 = (u16) ((DRXDAP_FASI_ADDR2BLOCK(addr) << 6) +
				DRXDAP_FASI_ADDR2BANK(addr));
	hi_cmd.param5 = (u16) DRXDAP_FASI_ADDR2OFFSET(addr);

	अगर (!पढ़ो_flag) अणु
		/* ग_लिखो data to buffer */
		क्रम (i = 0; i < (datasize / 2); i++) अणु

			word = ((u16) data[2 * i]);
			word += (((u16) data[(2 * i) + 1]) << 8);
			drxj_dap_ग_लिखो_reg16(dev_addr,
					     (DRXJ_HI_ATOMIC_BUF_START + i),
					    word, 0);
		पूर्ण
	पूर्ण

	rc = hi_command(dev_addr, &hi_cmd, &dummy);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	अगर (पढ़ो_flag) अणु
		/* पढ़ो data from buffer */
		क्रम (i = 0; i < (datasize / 2); i++) अणु
			rc = drxj_dap_पढ़ो_reg16(dev_addr,
						 (DRXJ_HI_ATOMIC_BUF_START + i),
						 &word, 0);
			अगर (rc) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			data[2 * i] = (u8) (word & 0xFF);
			data[(2 * i) + 1] = (u8) (word >> 8);
		पूर्ण
	पूर्ण

	वापस 0;

rw_error:
	वापस rc;

पूर्ण

/*============================================================================*/

/*
* \पn पूर्णांक drxj_dap_atomic_पढ़ो_reg32()
* \मrief Atomic पढ़ो of 32 bits words
*/
अटल
पूर्णांक drxj_dap_atomic_पढ़ो_reg32(काष्ठा i2c_device_addr *dev_addr,
				     u32 addr,
				     u32 *data, u32 flags)
अणु
	u8 buf[माप(*data)] = अणु 0 पूर्ण;
	पूर्णांक rc;
	u32 word = 0;

	अगर (!data)
		वापस -EINVAL;

	rc = drxj_dap_atomic_पढ़ो_ग_लिखो_block(dev_addr, addr,
					      माप(*data), buf, true);

	अगर (rc < 0)
		वापस 0;

	word = (u32) buf[3];
	word <<= 8;
	word |= (u32) buf[2];
	word <<= 8;
	word |= (u32) buf[1];
	word <<= 8;
	word |= (u32) buf[0];

	*data = word;

	वापस rc;
पूर्ण

/*============================================================================*/

/*============================================================================*/
/*==                        END DRXJ DAP FUNCTIONS                          ==*/
/*============================================================================*/

/*============================================================================*/
/*============================================================================*/
/*==                      HOST INTERFACE FUNCTIONS                          ==*/
/*============================================================================*/
/*============================================================================*/

/*
* \पn पूर्णांक hi_cfg_command()
* \मrief Configure HI with settings stored in the demod काष्ठाure.
* \param demod Demodulator.
* \लeturn पूर्णांक.
*
* This routine was created because to much orthogonal settings have
* been put पूर्णांकo one HI API function (configure). Especially the I2C bridge
* enable/disable should not need re-configuration of the HI.
*
*/
अटल पूर्णांक hi_cfg_command(स्थिर काष्ठा drx_demod_instance *demod)
अणु
	काष्ठा drxj_data *ext_attr = (काष्ठा drxj_data *) (शून्य);
	काष्ठा drxj_hi_cmd hi_cmd;
	u16 result = 0;
	पूर्णांक rc;

	ext_attr = (काष्ठा drxj_data *) demod->my_ext_attr;

	hi_cmd.cmd = SIO_HI_RA_RAM_CMD_CONFIG;
	hi_cmd.param1 = SIO_HI_RA_RAM_PAR_1_PAR1_SEC_KEY;
	hi_cmd.param2 = ext_attr->hi_cfg_timing_भाग;
	hi_cmd.param3 = ext_attr->hi_cfg_bridge_delay;
	hi_cmd.param4 = ext_attr->hi_cfg_wake_up_key;
	hi_cmd.param5 = ext_attr->hi_cfg_ctrl;
	hi_cmd.param6 = ext_attr->hi_cfg_transmit;

	rc = hi_command(demod->my_i2c_dev_addr, &hi_cmd, &result);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/* Reset घातer करोwn flag (set one call only) */
	ext_attr->hi_cfg_ctrl &= (~(SIO_HI_RA_RAM_PAR_5_CFG_SLEEP_ZZZ));

	वापस 0;

rw_error:
	वापस rc;
पूर्ण

/*
* \पn पूर्णांक hi_command()
* \मrief Configure HI with settings stored in the demod काष्ठाure.
* \param dev_addr I2C address.
* \param cmd HI command.
* \param result HI command result.
* \लeturn पूर्णांक.
*
* Sends command to HI
*
*/
अटल पूर्णांक
hi_command(काष्ठा i2c_device_addr *dev_addr, स्थिर काष्ठा drxj_hi_cmd *cmd, u16 *result)
अणु
	u16 रुको_cmd = 0;
	u16 nr_retries = 0;
	bool घातerकरोwn_cmd = false;
	पूर्णांक rc;

	/* Write parameters */
	चयन (cmd->cmd) अणु

	हाल SIO_HI_RA_RAM_CMD_CONFIG:
	हाल SIO_HI_RA_RAM_CMD_ATOMIC_COPY:
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_HI_RA_RAM_PAR_6__A, cmd->param6, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_HI_RA_RAM_PAR_5__A, cmd->param5, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_HI_RA_RAM_PAR_4__A, cmd->param4, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_HI_RA_RAM_PAR_3__A, cmd->param3, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		fallthrough;
	हाल SIO_HI_RA_RAM_CMD_BRDCTRL:
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_HI_RA_RAM_PAR_2__A, cmd->param2, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_HI_RA_RAM_PAR_1__A, cmd->param1, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		fallthrough;
	हाल SIO_HI_RA_RAM_CMD_शून्य:
		/* No parameters */
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Write command */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_HI_RA_RAM_CMD__A, cmd->cmd, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	अगर ((cmd->cmd) == SIO_HI_RA_RAM_CMD_RESET)
		msleep(1);

	/* Detect घातer करोwn to omit पढ़ोing result */
	घातerकरोwn_cmd = (bool) ((cmd->cmd == SIO_HI_RA_RAM_CMD_CONFIG) &&
				  (((cmd->
				     param5) & SIO_HI_RA_RAM_PAR_5_CFG_SLEEP__M)
				   == SIO_HI_RA_RAM_PAR_5_CFG_SLEEP_ZZZ));
	अगर (!घातerकरोwn_cmd) अणु
		/* Wait until command rdy */
		करो अणु
			nr_retries++;
			अगर (nr_retries > DRXJ_MAX_RETRIES) अणु
				pr_err("timeout\n");
				जाओ rw_error;
			पूर्ण

			rc = drxj_dap_पढ़ो_reg16(dev_addr, SIO_HI_RA_RAM_CMD__A, &रुको_cmd, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
		पूर्ण जबतक (रुको_cmd != 0);

		/* Read result */
		rc = drxj_dap_पढ़ो_reg16(dev_addr, SIO_HI_RA_RAM_RES__A, result, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण

	पूर्ण
	/* अगर ( घातerकरोwn_cmd == true ) */
	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*
* \पn पूर्णांक init_hi( स्थिर काष्ठा drx_demod_instance *demod )
* \मrief Initialise and configurate HI.
* \param demod poपूर्णांकer to demod data.
* \लeturn पूर्णांक Return status.
* \लetval 0 Success.
* \लetval -EIO Failure.
*
* Needs to know Psys (System Clock period) and Posc (Osc Clock period)
* Need to store configuration in driver because of the way I2C
* bridging is controlled.
*
*/
अटल पूर्णांक init_hi(स्थिर काष्ठा drx_demod_instance *demod)
अणु
	काष्ठा drxj_data *ext_attr = (काष्ठा drxj_data *) (शून्य);
	काष्ठा drx_common_attr *common_attr = (काष्ठा drx_common_attr *) (शून्य);
	काष्ठा i2c_device_addr *dev_addr = (काष्ठा i2c_device_addr *)(शून्य);
	पूर्णांक rc;

	ext_attr = (काष्ठा drxj_data *) demod->my_ext_attr;
	common_attr = (काष्ठा drx_common_attr *) demod->my_common_attr;
	dev_addr = demod->my_i2c_dev_addr;

	/* PATCH क्रम bug 5003, HI ucode v3.1.0 */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, 0x4301D7, 0x801, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/* Timing भाग, 250ns/Psys */
	/* Timing भाग, = ( delay (nano seconds) * sysclk (kHz) )/ 1000 */
	ext_attr->hi_cfg_timing_भाग =
	    (u16) ((common_attr->sys_घड़ी_freq / 1000) * HI_I2C_DELAY) / 1000;
	/* Clipping */
	अगर ((ext_attr->hi_cfg_timing_भाग) > SIO_HI_RA_RAM_PAR_2_CFG_DIV__M)
		ext_attr->hi_cfg_timing_भाग = SIO_HI_RA_RAM_PAR_2_CFG_DIV__M;
	/* Bridge delay, uses oscilator घड़ी */
	/* Delay = ( delay (nano seconds) * oscclk (kHz) )/ 1000 */
	/* SDA brdige delay */
	ext_attr->hi_cfg_bridge_delay =
	    (u16) ((common_attr->osc_घड़ी_freq / 1000) * HI_I2C_BRIDGE_DELAY) /
	    1000;
	/* Clipping */
	अगर ((ext_attr->hi_cfg_bridge_delay) > SIO_HI_RA_RAM_PAR_3_CFG_DBL_SDA__M)
		ext_attr->hi_cfg_bridge_delay = SIO_HI_RA_RAM_PAR_3_CFG_DBL_SDA__M;
	/* SCL bridge delay, same as SDA क्रम now */
	ext_attr->hi_cfg_bridge_delay += ((ext_attr->hi_cfg_bridge_delay) <<
				      SIO_HI_RA_RAM_PAR_3_CFG_DBL_SCL__B);
	/* Wakeup key, setting the पढ़ो flag (as suggest in the करोcumentation) करोes
	   not always result पूर्णांकo a working solution (barebones worked VI2C failed).
	   Not setting the bit works in all हालs . */
	ext_attr->hi_cfg_wake_up_key = DRXJ_WAKE_UP_KEY;
	/* port/bridge/घातer करोwn ctrl */
	ext_attr->hi_cfg_ctrl = (SIO_HI_RA_RAM_PAR_5_CFG_SLV0_SLAVE);
	/* transit mode समय out delay and watch करोg भागider */
	ext_attr->hi_cfg_transmit = SIO_HI_RA_RAM_PAR_6__PRE;

	rc = hi_cfg_command(demod);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	वापस 0;

rw_error:
	वापस rc;
पूर्ण

/*============================================================================*/
/*==                   END HOST INTERFACE FUNCTIONS                         ==*/
/*============================================================================*/

/*============================================================================*/
/*============================================================================*/
/*==                        AUXILIARY FUNCTIONS                             ==*/
/*============================================================================*/
/*============================================================================*/

/*
* \पn पूर्णांक get_device_capabilities()
* \मrief Get and store device capabilities.
* \param demod  Poपूर्णांकer to demodulator instance.
* \लeturn पूर्णांक.
* \लeturn 0    Success
* \लetval -EIO Failure
*
* Depending on pullकरोwns on MDx pins the following पूर्णांकernals are set:
*  * common_attr->osc_घड़ी_freq
*  * ext_attr->has_lna
*  * ext_attr->has_ntsc
*  * ext_attr->has_btsc
*  * ext_attr->has_oob
*
*/
अटल पूर्णांक get_device_capabilities(काष्ठा drx_demod_instance *demod)
अणु
	काष्ठा drx_common_attr *common_attr = (काष्ठा drx_common_attr *) (शून्य);
	काष्ठा drxj_data *ext_attr = (काष्ठा drxj_data *) शून्य;
	काष्ठा i2c_device_addr *dev_addr = (काष्ठा i2c_device_addr *)(शून्य);
	u16 sio_pdr_ohw_cfg = 0;
	u32 sio_top_jtagid_lo = 0;
	u16 bid = 0;
	पूर्णांक rc;

	common_attr = (काष्ठा drx_common_attr *) demod->my_common_attr;
	ext_attr = (काष्ठा drxj_data *) demod->my_ext_attr;
	dev_addr = demod->my_i2c_dev_addr;

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_TOP_COMM_KEY__A, SIO_TOP_COMM_KEY_KEY, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_पढ़ो_reg16(dev_addr, SIO_PDR_OHW_CFG__A, &sio_pdr_ohw_cfg, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_TOP_COMM_KEY__A, SIO_TOP_COMM_KEY__PRE, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	चयन ((sio_pdr_ohw_cfg & SIO_PDR_OHW_CFG_FREF_SEL__M)) अणु
	हाल 0:
		/* ignore (bypass ?) */
		अवरोध;
	हाल 1:
		/* 27 MHz */
		common_attr->osc_घड़ी_freq = 27000;
		अवरोध;
	हाल 2:
		/* 20.25 MHz */
		common_attr->osc_घड़ी_freq = 20250;
		अवरोध;
	हाल 3:
		/* 4 MHz */
		common_attr->osc_घड़ी_freq = 4000;
		अवरोध;
	शेष:
		वापस -EIO;
	पूर्ण

	/*
	   Determine device capabilities
	   Based on pinning v47
	 */
	rc = drxdap_fasi_पढ़ो_reg32(dev_addr, SIO_TOP_JTAGID_LO__A, &sio_top_jtagid_lo, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	ext_attr->mfx = (u8) ((sio_top_jtagid_lo >> 29) & 0xF);

	चयन ((sio_top_jtagid_lo >> 12) & 0xFF) अणु
	हाल 0x31:
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_TOP_COMM_KEY__A, SIO_TOP_COMM_KEY_KEY, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_पढ़ो_reg16(dev_addr, SIO_PDR_UIO_IN_HI__A, &bid, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		bid = (bid >> 10) & 0xf;
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_TOP_COMM_KEY__A, SIO_TOP_COMM_KEY__PRE, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण

		ext_attr->has_lna = true;
		ext_attr->has_ntsc = false;
		ext_attr->has_btsc = false;
		ext_attr->has_oob = false;
		ext_attr->has_smatx = true;
		ext_attr->has_smarx = false;
		ext_attr->has_gpio = false;
		ext_attr->has_irqn = false;
		अवरोध;
	हाल 0x33:
		ext_attr->has_lna = false;
		ext_attr->has_ntsc = false;
		ext_attr->has_btsc = false;
		ext_attr->has_oob = false;
		ext_attr->has_smatx = true;
		ext_attr->has_smarx = false;
		ext_attr->has_gpio = false;
		ext_attr->has_irqn = false;
		अवरोध;
	हाल 0x45:
		ext_attr->has_lna = true;
		ext_attr->has_ntsc = true;
		ext_attr->has_btsc = false;
		ext_attr->has_oob = false;
		ext_attr->has_smatx = true;
		ext_attr->has_smarx = true;
		ext_attr->has_gpio = true;
		ext_attr->has_irqn = false;
		अवरोध;
	हाल 0x46:
		ext_attr->has_lna = false;
		ext_attr->has_ntsc = true;
		ext_attr->has_btsc = false;
		ext_attr->has_oob = false;
		ext_attr->has_smatx = true;
		ext_attr->has_smarx = true;
		ext_attr->has_gpio = true;
		ext_attr->has_irqn = false;
		अवरोध;
	हाल 0x41:
		ext_attr->has_lna = true;
		ext_attr->has_ntsc = true;
		ext_attr->has_btsc = true;
		ext_attr->has_oob = false;
		ext_attr->has_smatx = true;
		ext_attr->has_smarx = true;
		ext_attr->has_gpio = true;
		ext_attr->has_irqn = false;
		अवरोध;
	हाल 0x43:
		ext_attr->has_lna = false;
		ext_attr->has_ntsc = true;
		ext_attr->has_btsc = true;
		ext_attr->has_oob = false;
		ext_attr->has_smatx = true;
		ext_attr->has_smarx = true;
		ext_attr->has_gpio = true;
		ext_attr->has_irqn = false;
		अवरोध;
	हाल 0x32:
		ext_attr->has_lna = true;
		ext_attr->has_ntsc = false;
		ext_attr->has_btsc = false;
		ext_attr->has_oob = true;
		ext_attr->has_smatx = true;
		ext_attr->has_smarx = true;
		ext_attr->has_gpio = true;
		ext_attr->has_irqn = true;
		अवरोध;
	हाल 0x34:
		ext_attr->has_lna = false;
		ext_attr->has_ntsc = true;
		ext_attr->has_btsc = true;
		ext_attr->has_oob = true;
		ext_attr->has_smatx = true;
		ext_attr->has_smarx = true;
		ext_attr->has_gpio = true;
		ext_attr->has_irqn = true;
		अवरोध;
	हाल 0x42:
		ext_attr->has_lna = true;
		ext_attr->has_ntsc = true;
		ext_attr->has_btsc = true;
		ext_attr->has_oob = true;
		ext_attr->has_smatx = true;
		ext_attr->has_smarx = true;
		ext_attr->has_gpio = true;
		ext_attr->has_irqn = true;
		अवरोध;
	हाल 0x44:
		ext_attr->has_lna = false;
		ext_attr->has_ntsc = true;
		ext_attr->has_btsc = true;
		ext_attr->has_oob = true;
		ext_attr->has_smatx = true;
		ext_attr->has_smarx = true;
		ext_attr->has_gpio = true;
		ext_attr->has_irqn = true;
		अवरोध;
	शेष:
		/* Unknown device variant */
		वापस -EIO;
		अवरोध;
	पूर्ण

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*
* \पn पूर्णांक घातer_up_device()
* \मrief Power up device.
* \param demod  Poपूर्णांकer to demodulator instance.
* \लeturn पूर्णांक.
* \लeturn 0    Success
* \लetval -EIO Failure, I2C or max retries reached
*
*/

#अगर_अघोषित DRXJ_MAX_RETRIES_POWERUP
#घोषणा DRXJ_MAX_RETRIES_POWERUP 10
#पूर्ण_अगर

अटल पूर्णांक घातer_up_device(काष्ठा drx_demod_instance *demod)
अणु
	काष्ठा i2c_device_addr *dev_addr = (काष्ठा i2c_device_addr *)(शून्य);
	u8 data = 0;
	u16 retry_count = 0;
	काष्ठा i2c_device_addr wake_up_addr;

	dev_addr = demod->my_i2c_dev_addr;
	wake_up_addr.i2c_addr = DRXJ_WAKE_UP_KEY;
	wake_up_addr.i2c_dev_id = dev_addr->i2c_dev_id;
	wake_up_addr.user_data = dev_addr->user_data;
	/*
	 * I2C access may fail in this हाल: no ack
	 * dummy ग_लिखो must be used to wake uop device, dummy पढ़ो must be used to
	 * reset HI state machine (aव्योमing actual ग_लिखोs)
	 */
	करो अणु
		data = 0;
		drxbsp_i2c_ग_लिखो_पढ़ो(&wake_up_addr, 1, &data,
				      (काष्ठा i2c_device_addr *)(शून्य), 0,
				     (u8 *)(शून्य));
		msleep(10);
		retry_count++;
	पूर्ण जबतक ((drxbsp_i2c_ग_लिखो_पढ़ो
		  ((काष्ठा i2c_device_addr *) (शून्य), 0, (u8 *)(शून्य), dev_addr, 1,
		   &data)
		  != 0) && (retry_count < DRXJ_MAX_RETRIES_POWERUP));

	/* Need some recovery समय .... */
	msleep(10);

	अगर (retry_count == DRXJ_MAX_RETRIES_POWERUP)
		वापस -EIO;

	वापस 0;
पूर्ण

/*----------------------------------------------------------------------------*/
/* MPEG Output Configuration Functions - begin                                */
/*----------------------------------------------------------------------------*/
/*
* \पn पूर्णांक ctrl_set_cfg_mpeg_output()
* \मrief Set MPEG output configuration of the device.
* \param devmod  Poपूर्णांकer to demodulator instance.
* \param cfg_data Poपूर्णांकer to mpeg output configuaration.
* \लeturn पूर्णांक.
*
*  Configure MPEG output parameters.
*
*/
अटल पूर्णांक
ctrl_set_cfg_mpeg_output(काष्ठा drx_demod_instance *demod, काष्ठा drx_cfg_mpeg_output *cfg_data)
अणु
	काष्ठा i2c_device_addr *dev_addr = (काष्ठा i2c_device_addr *)(शून्य);
	काष्ठा drxj_data *ext_attr = (काष्ठा drxj_data *) (शून्य);
	काष्ठा drx_common_attr *common_attr = (काष्ठा drx_common_attr *) (शून्य);
	पूर्णांक rc;
	u16 fec_oc_reg_mode = 0;
	u16 fec_oc_reg_ipr_mode = 0;
	u16 fec_oc_reg_ipr_invert = 0;
	u32 max_bit_rate = 0;
	u32 rcn_rate = 0;
	u32 nr_bits = 0;
	u16 sio_pdr_md_cfg = 0;
	/* data mask क्रम the output data byte */
	u16 invert_data_mask =
	    FEC_OC_IPR_INVERT_MD7__M | FEC_OC_IPR_INVERT_MD6__M |
	    FEC_OC_IPR_INVERT_MD5__M | FEC_OC_IPR_INVERT_MD4__M |
	    FEC_OC_IPR_INVERT_MD3__M | FEC_OC_IPR_INVERT_MD2__M |
	    FEC_OC_IPR_INVERT_MD1__M | FEC_OC_IPR_INVERT_MD0__M;

	/* check arguments */
	अगर ((demod == शून्य) || (cfg_data == शून्य))
		वापस -EINVAL;

	dev_addr = demod->my_i2c_dev_addr;
	ext_attr = (काष्ठा drxj_data *) demod->my_ext_attr;
	common_attr = (काष्ठा drx_common_attr *) demod->my_common_attr;

	अगर (cfg_data->enable_mpeg_output == true) अणु
		/* quick and dirty patch to set MPEG in हाल current std is not
		   producing MPEG */
		चयन (ext_attr->standard) अणु
		हाल DRX_STANDARD_8VSB:
		हाल DRX_STANDARD_ITU_A:
		हाल DRX_STANDARD_ITU_B:
		हाल DRX_STANDARD_ITU_C:
			अवरोध;
		शेष:
			वापस 0;
		पूर्ण

		rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_OCR_INVERT__A, 0, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		चयन (ext_attr->standard) अणु
		हाल DRX_STANDARD_8VSB:
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_FCT_USAGE__A, 7, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण	/* 2048 bytes fअगरo ram */
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_TMD_CTL_UPD_RATE__A, 10, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_TMD_INT_UPD_RATE__A, 10, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_AVR_PARM_A__A, 5, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_AVR_PARM_B__A, 7, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_RCN_GAIN__A, 10, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			/* Low Water Mark क्रम synchronization  */
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_SNC_LWM__A, 3, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			/* High Water Mark क्रम synchronization */
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_SNC_HWM__A, 5, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			अवरोध;
		हाल DRX_STANDARD_ITU_A:
		हाल DRX_STANDARD_ITU_C:
			चयन (ext_attr->स्थिरellation) अणु
			हाल DRX_CONSTELLATION_QAM256:
				nr_bits = 8;
				अवरोध;
			हाल DRX_CONSTELLATION_QAM128:
				nr_bits = 7;
				अवरोध;
			हाल DRX_CONSTELLATION_QAM64:
				nr_bits = 6;
				अवरोध;
			हाल DRX_CONSTELLATION_QAM32:
				nr_bits = 5;
				अवरोध;
			हाल DRX_CONSTELLATION_QAM16:
				nr_bits = 4;
				अवरोध;
			शेष:
				वापस -EIO;
			पूर्ण	/* ext_attr->स्थिरellation */
			/* max_bit_rate = symbol_rate * nr_bits * coef */
			/* coef = 188/204                          */
			max_bit_rate =
			    (ext_attr->curr_symbol_rate / 8) * nr_bits * 188;
			fallthrough;	/* as b/c Annex A/C need following settings */
		हाल DRX_STANDARD_ITU_B:
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_FCT_USAGE__A, FEC_OC_FCT_USAGE__PRE, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_TMD_CTL_UPD_RATE__A, FEC_OC_TMD_CTL_UPD_RATE__PRE, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_TMD_INT_UPD_RATE__A, 5, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_AVR_PARM_A__A, FEC_OC_AVR_PARM_A__PRE, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_AVR_PARM_B__A, FEC_OC_AVR_PARM_B__PRE, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			अगर (cfg_data->अटल_clk == true) अणु
				rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_RCN_GAIN__A, 0xD, 0);
				अगर (rc != 0) अणु
					pr_err("error %d\n", rc);
					जाओ rw_error;
				पूर्ण
			पूर्ण अन्यथा अणु
				rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_RCN_GAIN__A, FEC_OC_RCN_GAIN__PRE, 0);
				अगर (rc != 0) अणु
					pr_err("error %d\n", rc);
					जाओ rw_error;
				पूर्ण
			पूर्ण
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_SNC_LWM__A, 2, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_SNC_HWM__A, 12, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण		/* चयन (standard) */

		/* Check insertion of the Reed-Solomon parity bytes */
		rc = drxj_dap_पढ़ो_reg16(dev_addr, FEC_OC_MODE__A, &fec_oc_reg_mode, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_पढ़ो_reg16(dev_addr, FEC_OC_IPR_MODE__A, &fec_oc_reg_ipr_mode, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		अगर (cfg_data->insert_rs_byte == true) अणु
			/* enable parity symbol क्रमward */
			fec_oc_reg_mode |= FEC_OC_MODE_PARITY__M;
			/* MVAL disable during parity bytes */
			fec_oc_reg_ipr_mode |= FEC_OC_IPR_MODE_MVAL_DIS_PAR__M;
			चयन (ext_attr->standard) अणु
			हाल DRX_STANDARD_8VSB:
				rcn_rate = 0x004854D3;
				अवरोध;
			हाल DRX_STANDARD_ITU_B:
				fec_oc_reg_mode |= FEC_OC_MODE_TRANSPARENT__M;
				चयन (ext_attr->स्थिरellation) अणु
				हाल DRX_CONSTELLATION_QAM256:
					rcn_rate = 0x008945E7;
					अवरोध;
				हाल DRX_CONSTELLATION_QAM64:
					rcn_rate = 0x005F64D4;
					अवरोध;
				शेष:
					वापस -EIO;
				पूर्ण
				अवरोध;
			हाल DRX_STANDARD_ITU_A:
			हाल DRX_STANDARD_ITU_C:
				/* insert_rs_byte = true -> coef = 188/188 -> 1, RS bits are in MPEG output */
				rcn_rate =
				    (frac28
				     (max_bit_rate,
				      (u32) (common_attr->sys_घड़ी_freq / 8))) /
				    188;
				अवरोध;
			शेष:
				वापस -EIO;
			पूर्ण	/* ext_attr->standard */
		पूर्ण अन्यथा अणु	/* insert_rs_byte == false */

			/* disable parity symbol क्रमward */
			fec_oc_reg_mode &= (~FEC_OC_MODE_PARITY__M);
			/* MVAL enable during parity bytes */
			fec_oc_reg_ipr_mode &= (~FEC_OC_IPR_MODE_MVAL_DIS_PAR__M);
			चयन (ext_attr->standard) अणु
			हाल DRX_STANDARD_8VSB:
				rcn_rate = 0x0041605C;
				अवरोध;
			हाल DRX_STANDARD_ITU_B:
				fec_oc_reg_mode &= (~FEC_OC_MODE_TRANSPARENT__M);
				चयन (ext_attr->स्थिरellation) अणु
				हाल DRX_CONSTELLATION_QAM256:
					rcn_rate = 0x0082D6A0;
					अवरोध;
				हाल DRX_CONSTELLATION_QAM64:
					rcn_rate = 0x005AEC1A;
					अवरोध;
				शेष:
					वापस -EIO;
				पूर्ण
				अवरोध;
			हाल DRX_STANDARD_ITU_A:
			हाल DRX_STANDARD_ITU_C:
				/* insert_rs_byte = false -> coef = 188/204, RS bits not in MPEG output */
				rcn_rate =
				    (frac28
				     (max_bit_rate,
				      (u32) (common_attr->sys_घड़ी_freq / 8))) /
				    204;
				अवरोध;
			शेष:
				वापस -EIO;
			पूर्ण	/* ext_attr->standard */
		पूर्ण

		अगर (cfg_data->enable_parallel == true) अणु	/* MPEG data output is parallel -> clear ipr_mode[0] */
			fec_oc_reg_ipr_mode &= (~(FEC_OC_IPR_MODE_SERIAL__M));
		पूर्ण अन्यथा अणु	/* MPEG data output is serial -> set ipr_mode[0] */
			fec_oc_reg_ipr_mode |= FEC_OC_IPR_MODE_SERIAL__M;
		पूर्ण

		/* Control slective inversion of output bits */
		अगर (cfg_data->invert_data == true)
			fec_oc_reg_ipr_invert |= invert_data_mask;
		अन्यथा
			fec_oc_reg_ipr_invert &= (~(invert_data_mask));

		अगर (cfg_data->invert_err == true)
			fec_oc_reg_ipr_invert |= FEC_OC_IPR_INVERT_MERR__M;
		अन्यथा
			fec_oc_reg_ipr_invert &= (~(FEC_OC_IPR_INVERT_MERR__M));

		अगर (cfg_data->invert_str == true)
			fec_oc_reg_ipr_invert |= FEC_OC_IPR_INVERT_MSTRT__M;
		अन्यथा
			fec_oc_reg_ipr_invert &= (~(FEC_OC_IPR_INVERT_MSTRT__M));

		अगर (cfg_data->invert_val == true)
			fec_oc_reg_ipr_invert |= FEC_OC_IPR_INVERT_MVAL__M;
		अन्यथा
			fec_oc_reg_ipr_invert &= (~(FEC_OC_IPR_INVERT_MVAL__M));

		अगर (cfg_data->invert_clk == true)
			fec_oc_reg_ipr_invert |= FEC_OC_IPR_INVERT_MCLK__M;
		अन्यथा
			fec_oc_reg_ipr_invert &= (~(FEC_OC_IPR_INVERT_MCLK__M));


		अगर (cfg_data->अटल_clk == true) अणु	/* Static mode */
			u32 dto_rate = 0;
			u32 bit_rate = 0;
			u16 fec_oc_dto_burst_len = 0;
			u16 fec_oc_dto_period = 0;

			fec_oc_dto_burst_len = FEC_OC_DTO_BURST_LEN__PRE;

			चयन (ext_attr->standard) अणु
			हाल DRX_STANDARD_8VSB:
				fec_oc_dto_period = 4;
				अगर (cfg_data->insert_rs_byte == true)
					fec_oc_dto_burst_len = 208;
				अवरोध;
			हाल DRX_STANDARD_ITU_A:
				अणु
					u32 symbol_rate_th = 6400000;
					अगर (cfg_data->insert_rs_byte == true) अणु
						fec_oc_dto_burst_len = 204;
						symbol_rate_th = 5900000;
					पूर्ण
					अगर (ext_attr->curr_symbol_rate >=
					    symbol_rate_th) अणु
						fec_oc_dto_period = 0;
					पूर्ण अन्यथा अणु
						fec_oc_dto_period = 1;
					पूर्ण
				पूर्ण
				अवरोध;
			हाल DRX_STANDARD_ITU_B:
				fec_oc_dto_period = 1;
				अगर (cfg_data->insert_rs_byte == true)
					fec_oc_dto_burst_len = 128;
				अवरोध;
			हाल DRX_STANDARD_ITU_C:
				fec_oc_dto_period = 1;
				अगर (cfg_data->insert_rs_byte == true)
					fec_oc_dto_burst_len = 204;
				अवरोध;
			शेष:
				वापस -EIO;
			पूर्ण
			bit_rate =
			    common_attr->sys_घड़ी_freq * 1000 / (fec_oc_dto_period +
							       2);
			dto_rate =
			    frac28(bit_rate, common_attr->sys_घड़ी_freq * 1000);
			dto_rate >>= 3;
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_DTO_RATE_HI__A, (u16)((dto_rate >> 16) & FEC_OC_DTO_RATE_HI__M), 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_DTO_RATE_LO__A, (u16)(dto_rate & FEC_OC_DTO_RATE_LO_RATE_LO__M), 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_DTO_MODE__A, FEC_OC_DTO_MODE_DYNAMIC__M | FEC_OC_DTO_MODE_OFFSET_ENABLE__M, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_FCT_MODE__A, FEC_OC_FCT_MODE_RAT_ENA__M | FEC_OC_FCT_MODE_VIRT_ENA__M, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_DTO_BURST_LEN__A, fec_oc_dto_burst_len, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			अगर (ext_attr->mpeg_output_घड़ी_rate != DRXJ_MPEGOUTPUT_CLOCK_RATE_AUTO)
				fec_oc_dto_period = ext_attr->mpeg_output_घड़ी_rate - 1;
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_DTO_PERIOD__A, fec_oc_dto_period, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
		पूर्ण अन्यथा अणु	/* Dynamic mode */

			rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_DTO_MODE__A, FEC_OC_DTO_MODE_DYNAMIC__M, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_FCT_MODE__A, 0, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
		पूर्ण

		rc = drxdap_fasi_ग_लिखो_reg32(dev_addr, FEC_OC_RCN_CTL_RATE_LO__A, rcn_rate, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण

		/* Write appropriate रेजिस्टरs with requested configuration */
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_MODE__A, fec_oc_reg_mode, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_IPR_MODE__A, fec_oc_reg_ipr_mode, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_IPR_INVERT__A, fec_oc_reg_ipr_invert, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण

		/* enabling क्रम both parallel and serial now */
		/*  Write magic word to enable pdr reg ग_लिखो */
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_TOP_COMM_KEY__A, 0xFABA, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		/*  Set MPEG TS pads to outpuपंचांगode */
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_MSTRT_CFG__A, 0x0013, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_MERR_CFG__A, 0x0013, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_MCLK_CFG__A, MPEG_OUTPUT_CLK_DRIVE_STRENGTH << SIO_PDR_MCLK_CFG_DRIVE__B | 0x03 << SIO_PDR_MCLK_CFG_MODE__B, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_MVAL_CFG__A, 0x0013, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		sio_pdr_md_cfg =
		    MPEG_SERIAL_OUTPUT_PIN_DRIVE_STRENGTH <<
		    SIO_PDR_MD0_CFG_DRIVE__B | 0x03 << SIO_PDR_MD0_CFG_MODE__B;
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_MD0_CFG__A, sio_pdr_md_cfg, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		अगर (cfg_data->enable_parallel == true) अणु	/* MPEG data output is parallel -> set MD1 to MD7 to output mode */
			sio_pdr_md_cfg =
			    MPEG_PARALLEL_OUTPUT_PIN_DRIVE_STRENGTH <<
			    SIO_PDR_MD0_CFG_DRIVE__B | 0x03 <<
			    SIO_PDR_MD0_CFG_MODE__B;
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_MD0_CFG__A, sio_pdr_md_cfg, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_MD1_CFG__A, sio_pdr_md_cfg, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_MD2_CFG__A, sio_pdr_md_cfg, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_MD3_CFG__A, sio_pdr_md_cfg, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_MD4_CFG__A, sio_pdr_md_cfg, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_MD5_CFG__A, sio_pdr_md_cfg, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_MD6_CFG__A, sio_pdr_md_cfg, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_MD7_CFG__A, sio_pdr_md_cfg, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
		पूर्ण अन्यथा अणु	/* MPEG data output is serial -> set MD1 to MD7 to tri-state */
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_MD1_CFG__A, 0x0000, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_MD2_CFG__A, 0x0000, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_MD3_CFG__A, 0x0000, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_MD4_CFG__A, 0x0000, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_MD5_CFG__A, 0x0000, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_MD6_CFG__A, 0x0000, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_MD7_CFG__A, 0x0000, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
		पूर्ण
		/*  Enable Monitor Bus output over MPEG pads and ctl input */
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_MON_CFG__A, 0x0000, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		/*  Write nomagic word to enable pdr reg ग_लिखो */
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_TOP_COMM_KEY__A, 0x0000, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*  Write magic word to enable pdr reg ग_लिखो */
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_TOP_COMM_KEY__A, 0xFABA, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		/*  Set MPEG TS pads to inpuपंचांगode */
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_MSTRT_CFG__A, 0x0000, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_MERR_CFG__A, 0x0000, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_MCLK_CFG__A, 0x0000, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_MVAL_CFG__A, 0x0000, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_MD0_CFG__A, 0x0000, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_MD1_CFG__A, 0x0000, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_MD2_CFG__A, 0x0000, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_MD3_CFG__A, 0x0000, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_MD4_CFG__A, 0x0000, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_MD5_CFG__A, 0x0000, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_MD6_CFG__A, 0x0000, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_MD7_CFG__A, 0x0000, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		/* Enable Monitor Bus output over MPEG pads and ctl input */
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_MON_CFG__A, 0x0000, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		/* Write nomagic word to enable pdr reg ग_लिखो */
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_TOP_COMM_KEY__A, 0x0000, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
	पूर्ण

	/* save values क्रम restore after re-acquire */
	common_attr->mpeg_cfg.enable_mpeg_output = cfg_data->enable_mpeg_output;

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* MPEG Output Configuration Functions - end                                  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* miscellaneous configurations - begin                           */
/*----------------------------------------------------------------------------*/

/*
* \पn पूर्णांक set_mpegtei_handling()
* \मrief Activate MPEG TEI handling settings.
* \param devmod  Poपूर्णांकer to demodulator instance.
* \लeturn पूर्णांक.
*
* This routine should be called during a set channel of QAM/VSB
*
*/
अटल पूर्णांक set_mpegtei_handling(काष्ठा drx_demod_instance *demod)
अणु
	काष्ठा drxj_data *ext_attr = (काष्ठा drxj_data *) (शून्य);
	काष्ठा i2c_device_addr *dev_addr = (काष्ठा i2c_device_addr *)(शून्य);
	पूर्णांक rc;
	u16 fec_oc_dpr_mode = 0;
	u16 fec_oc_snc_mode = 0;
	u16 fec_oc_ems_mode = 0;

	dev_addr = demod->my_i2c_dev_addr;
	ext_attr = (काष्ठा drxj_data *) demod->my_ext_attr;

	rc = drxj_dap_पढ़ो_reg16(dev_addr, FEC_OC_DPR_MODE__A, &fec_oc_dpr_mode, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_पढ़ो_reg16(dev_addr, FEC_OC_SNC_MODE__A, &fec_oc_snc_mode, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_पढ़ो_reg16(dev_addr, FEC_OC_EMS_MODE__A, &fec_oc_ems_mode, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/* reset to शेष, allow TEI bit to be changed */
	fec_oc_dpr_mode &= (~FEC_OC_DPR_MODE_ERR_DISABLE__M);
	fec_oc_snc_mode &= (~(FEC_OC_SNC_MODE_ERROR_CTL__M |
			   FEC_OC_SNC_MODE_CORR_DISABLE__M));
	fec_oc_ems_mode &= (~FEC_OC_EMS_MODE_MODE__M);

	अगर (ext_attr->disable_te_ihandling) अणु
		/* करो not change TEI bit */
		fec_oc_dpr_mode |= FEC_OC_DPR_MODE_ERR_DISABLE__M;
		fec_oc_snc_mode |= FEC_OC_SNC_MODE_CORR_DISABLE__M |
		    ((0x2) << (FEC_OC_SNC_MODE_ERROR_CTL__B));
		fec_oc_ems_mode |= ((0x01) << (FEC_OC_EMS_MODE_MODE__B));
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_DPR_MODE__A, fec_oc_dpr_mode, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_SNC_MODE__A, fec_oc_snc_mode, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_EMS_MODE__A, fec_oc_ems_mode, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*----------------------------------------------------------------------------*/
/*
* \पn पूर्णांक bit_reverse_mpeg_output()
* \मrief Set MPEG output bit-endian settings.
* \param devmod  Poपूर्णांकer to demodulator instance.
* \लeturn पूर्णांक.
*
* This routine should be called during a set channel of QAM/VSB
*
*/
अटल पूर्णांक bit_reverse_mpeg_output(काष्ठा drx_demod_instance *demod)
अणु
	काष्ठा drxj_data *ext_attr = (काष्ठा drxj_data *) (शून्य);
	काष्ठा i2c_device_addr *dev_addr = (काष्ठा i2c_device_addr *)(शून्य);
	पूर्णांक rc;
	u16 fec_oc_ipr_mode = 0;

	dev_addr = demod->my_i2c_dev_addr;
	ext_attr = (काष्ठा drxj_data *) demod->my_ext_attr;

	rc = drxj_dap_पढ़ो_reg16(dev_addr, FEC_OC_IPR_MODE__A, &fec_oc_ipr_mode, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/* reset to शेष (normal bit order) */
	fec_oc_ipr_mode &= (~FEC_OC_IPR_MODE_REVERSE_ORDER__M);

	अगर (ext_attr->bit_reverse_mpeg_outout)
		fec_oc_ipr_mode |= FEC_OC_IPR_MODE_REVERSE_ORDER__M;

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_IPR_MODE__A, fec_oc_ipr_mode, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*----------------------------------------------------------------------------*/
/*
* \पn पूर्णांक set_mpeg_start_width()
* \मrief Set MPEG start width.
* \param devmod  Poपूर्णांकer to demodulator instance.
* \लeturn पूर्णांक.
*
* This routine should be called during a set channel of QAM/VSB
*
*/
अटल पूर्णांक set_mpeg_start_width(काष्ठा drx_demod_instance *demod)
अणु
	काष्ठा drxj_data *ext_attr = (काष्ठा drxj_data *) (शून्य);
	काष्ठा i2c_device_addr *dev_addr = (काष्ठा i2c_device_addr *)(शून्य);
	काष्ठा drx_common_attr *common_attr = (काष्ठा drx_common_attr *) शून्य;
	पूर्णांक rc;
	u16 fec_oc_comm_mb = 0;

	dev_addr = demod->my_i2c_dev_addr;
	ext_attr = (काष्ठा drxj_data *) demod->my_ext_attr;
	common_attr = demod->my_common_attr;

	अगर ((common_attr->mpeg_cfg.अटल_clk == true)
	    && (common_attr->mpeg_cfg.enable_parallel == false)) अणु
		rc = drxj_dap_पढ़ो_reg16(dev_addr, FEC_OC_COMM_MB__A, &fec_oc_comm_mb, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		fec_oc_comm_mb &= ~FEC_OC_COMM_MB_CTL_ON;
		अगर (ext_attr->mpeg_start_width == DRXJ_MPEG_START_WIDTH_8CLKCYC)
			fec_oc_comm_mb |= FEC_OC_COMM_MB_CTL_ON;
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_COMM_MB__A, fec_oc_comm_mb, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
	पूर्ण

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*----------------------------------------------------------------------------*/
/* miscellaneous configurations - end                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* UIO Configuration Functions - begin                                        */
/*----------------------------------------------------------------------------*/
/*
* \पn पूर्णांक ctrl_set_uio_cfg()
* \मrief Configure modus opअक्रमi UIO.
* \param demod Poपूर्णांकer to demodulator instance.
* \param uio_cfg Poपूर्णांकer to a configuration setting क्रम a certain UIO.
* \लeturn पूर्णांक.
*/
अटल पूर्णांक ctrl_set_uio_cfg(काष्ठा drx_demod_instance *demod, काष्ठा drxuio_cfg *uio_cfg)
अणु
	काष्ठा drxj_data *ext_attr = (काष्ठा drxj_data *) (शून्य);
	पूर्णांक rc;

	अगर ((uio_cfg == शून्य) || (demod == शून्य))
		वापस -EINVAL;

	ext_attr = (काष्ठा drxj_data *) demod->my_ext_attr;

	/*  Write magic word to enable pdr reg ग_लिखो               */
	rc = drxj_dap_ग_लिखो_reg16(demod->my_i2c_dev_addr, SIO_TOP_COMM_KEY__A, SIO_TOP_COMM_KEY_KEY, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	चयन (uio_cfg->uio) अणु
      /*====================================================================*/
	हाल DRX_UIO1:
		/* DRX_UIO1: SMA_TX UIO-1 */
		अगर (!ext_attr->has_smatx)
			वापस -EIO;
		चयन (uio_cfg->mode) अणु
		हाल DRX_UIO_MODE_FIRMWARE_SMA:
		हाल DRX_UIO_MODE_FIRMWARE_SAW:
		हाल DRX_UIO_MODE_READWRITE:
			ext_attr->uio_sma_tx_mode = uio_cfg->mode;
			अवरोध;
		हाल DRX_UIO_MODE_DISABLE:
			ext_attr->uio_sma_tx_mode = uio_cfg->mode;
			/* pad configuration रेजिस्टर is set 0 - input mode */
			rc = drxj_dap_ग_लिखो_reg16(demod->my_i2c_dev_addr, SIO_PDR_SMA_TX_CFG__A, 0, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण		/* चयन ( uio_cfg->mode ) */
		अवरोध;
      /*====================================================================*/
	हाल DRX_UIO2:
		/* DRX_UIO2: SMA_RX UIO-2 */
		अगर (!ext_attr->has_smarx)
			वापस -EIO;
		चयन (uio_cfg->mode) अणु
		हाल DRX_UIO_MODE_FIRMWARE0:
		हाल DRX_UIO_MODE_READWRITE:
			ext_attr->uio_sma_rx_mode = uio_cfg->mode;
			अवरोध;
		हाल DRX_UIO_MODE_DISABLE:
			ext_attr->uio_sma_rx_mode = uio_cfg->mode;
			/* pad configuration रेजिस्टर is set 0 - input mode */
			rc = drxj_dap_ग_लिखो_reg16(demod->my_i2c_dev_addr, SIO_PDR_SMA_RX_CFG__A, 0, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण		/* चयन ( uio_cfg->mode ) */
		अवरोध;
      /*====================================================================*/
	हाल DRX_UIO3:
		/* DRX_UIO3: GPIO UIO-3 */
		अगर (!ext_attr->has_gpio)
			वापस -EIO;
		चयन (uio_cfg->mode) अणु
		हाल DRX_UIO_MODE_FIRMWARE0:
		हाल DRX_UIO_MODE_READWRITE:
			ext_attr->uio_gpio_mode = uio_cfg->mode;
			अवरोध;
		हाल DRX_UIO_MODE_DISABLE:
			ext_attr->uio_gpio_mode = uio_cfg->mode;
			/* pad configuration रेजिस्टर is set 0 - input mode */
			rc = drxj_dap_ग_लिखो_reg16(demod->my_i2c_dev_addr, SIO_PDR_GPIO_CFG__A, 0, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण		/* चयन ( uio_cfg->mode ) */
		अवरोध;
      /*====================================================================*/
	हाल DRX_UIO4:
		/* DRX_UIO4: IRQN UIO-4 */
		अगर (!ext_attr->has_irqn)
			वापस -EIO;
		चयन (uio_cfg->mode) अणु
		हाल DRX_UIO_MODE_READWRITE:
			ext_attr->uio_irqn_mode = uio_cfg->mode;
			अवरोध;
		हाल DRX_UIO_MODE_DISABLE:
			/* pad configuration रेजिस्टर is set 0 - input mode */
			rc = drxj_dap_ग_लिखो_reg16(demod->my_i2c_dev_addr, SIO_PDR_IRQN_CFG__A, 0, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			ext_attr->uio_irqn_mode = uio_cfg->mode;
			अवरोध;
		हाल DRX_UIO_MODE_FIRMWARE0:
		शेष:
			वापस -EINVAL;
		पूर्ण		/* चयन ( uio_cfg->mode ) */
		अवरोध;
      /*====================================================================*/
	शेष:
		वापस -EINVAL;
	पूर्ण			/* चयन ( uio_cfg->uio ) */

	/*  Write magic word to disable pdr reg ग_लिखो               */
	rc = drxj_dap_ग_लिखो_reg16(demod->my_i2c_dev_addr, SIO_TOP_COMM_KEY__A, 0x0000, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*
* \पn पूर्णांक ctrl_uio_ग_लिखो()
* \मrief Write to a UIO.
* \param demod Poपूर्णांकer to demodulator instance.
* \param uio_data Poपूर्णांकer to data container क्रम a certain UIO.
* \लeturn पूर्णांक.
*/
अटल पूर्णांक
ctrl_uio_ग_लिखो(काष्ठा drx_demod_instance *demod, काष्ठा drxuio_data *uio_data)
अणु
	काष्ठा drxj_data *ext_attr = (काष्ठा drxj_data *) (शून्य);
	पूर्णांक rc;
	u16 pin_cfg_value = 0;
	u16 value = 0;

	अगर ((uio_data == शून्य) || (demod == शून्य))
		वापस -EINVAL;

	ext_attr = (काष्ठा drxj_data *) demod->my_ext_attr;

	/*  Write magic word to enable pdr reg ग_लिखो               */
	rc = drxj_dap_ग_लिखो_reg16(demod->my_i2c_dev_addr, SIO_TOP_COMM_KEY__A, SIO_TOP_COMM_KEY_KEY, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	चयन (uio_data->uio) अणु
      /*====================================================================*/
	हाल DRX_UIO1:
		/* DRX_UIO1: SMA_TX UIO-1 */
		अगर (!ext_attr->has_smatx)
			वापस -EIO;
		अगर ((ext_attr->uio_sma_tx_mode != DRX_UIO_MODE_READWRITE)
		    && (ext_attr->uio_sma_tx_mode != DRX_UIO_MODE_FIRMWARE_SAW)) अणु
			वापस -EIO;
		पूर्ण
		pin_cfg_value = 0;
		/* io_pad_cfg रेजिस्टर (8 bit reg.) MSB bit is 1 (शेष value) */
		pin_cfg_value |= 0x0113;
		/* io_pad_cfg_mode output mode is drive always */
		/* io_pad_cfg_drive is set to घातer 2 (23 mA) */

		/* ग_लिखो to io pad configuration रेजिस्टर - output mode */
		rc = drxj_dap_ग_लिखो_reg16(demod->my_i2c_dev_addr, SIO_PDR_SMA_TX_CFG__A, pin_cfg_value, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण

		/* use corresponding bit in io data output registar */
		rc = drxj_dap_पढ़ो_reg16(demod->my_i2c_dev_addr, SIO_PDR_UIO_OUT_LO__A, &value, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		अगर (!uio_data->value)
			value &= 0x7FFF;	/* ग_लिखो zero to 15th bit - 1st UIO */
		अन्यथा
			value |= 0x8000;	/* ग_लिखो one to 15th bit - 1st UIO */

		/* ग_लिखो back to io data output रेजिस्टर */
		rc = drxj_dap_ग_लिखो_reg16(demod->my_i2c_dev_addr, SIO_PDR_UIO_OUT_LO__A, value, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		अवरोध;
   /*======================================================================*/
	हाल DRX_UIO2:
		/* DRX_UIO2: SMA_RX UIO-2 */
		अगर (!ext_attr->has_smarx)
			वापस -EIO;
		अगर (ext_attr->uio_sma_rx_mode != DRX_UIO_MODE_READWRITE)
			वापस -EIO;

		pin_cfg_value = 0;
		/* io_pad_cfg रेजिस्टर (8 bit reg.) MSB bit is 1 (शेष value) */
		pin_cfg_value |= 0x0113;
		/* io_pad_cfg_mode output mode is drive always */
		/* io_pad_cfg_drive is set to घातer 2 (23 mA) */

		/* ग_लिखो to io pad configuration रेजिस्टर - output mode */
		rc = drxj_dap_ग_लिखो_reg16(demod->my_i2c_dev_addr, SIO_PDR_SMA_RX_CFG__A, pin_cfg_value, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण

		/* use corresponding bit in io data output registar */
		rc = drxj_dap_पढ़ो_reg16(demod->my_i2c_dev_addr, SIO_PDR_UIO_OUT_LO__A, &value, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		अगर (!uio_data->value)
			value &= 0xBFFF;	/* ग_लिखो zero to 14th bit - 2nd UIO */
		अन्यथा
			value |= 0x4000;	/* ग_लिखो one to 14th bit - 2nd UIO */

		/* ग_लिखो back to io data output रेजिस्टर */
		rc = drxj_dap_ग_लिखो_reg16(demod->my_i2c_dev_addr, SIO_PDR_UIO_OUT_LO__A, value, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		अवरोध;
   /*====================================================================*/
	हाल DRX_UIO3:
		/* DRX_UIO3: ASEL UIO-3 */
		अगर (!ext_attr->has_gpio)
			वापस -EIO;
		अगर (ext_attr->uio_gpio_mode != DRX_UIO_MODE_READWRITE)
			वापस -EIO;

		pin_cfg_value = 0;
		/* io_pad_cfg रेजिस्टर (8 bit reg.) MSB bit is 1 (शेष value) */
		pin_cfg_value |= 0x0113;
		/* io_pad_cfg_mode output mode is drive always */
		/* io_pad_cfg_drive is set to घातer 2 (23 mA) */

		/* ग_लिखो to io pad configuration रेजिस्टर - output mode */
		rc = drxj_dap_ग_लिखो_reg16(demod->my_i2c_dev_addr, SIO_PDR_GPIO_CFG__A, pin_cfg_value, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण

		/* use corresponding bit in io data output registar */
		rc = drxj_dap_पढ़ो_reg16(demod->my_i2c_dev_addr, SIO_PDR_UIO_OUT_HI__A, &value, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		अगर (!uio_data->value)
			value &= 0xFFFB;	/* ग_लिखो zero to 2nd bit - 3rd UIO */
		अन्यथा
			value |= 0x0004;	/* ग_लिखो one to 2nd bit - 3rd UIO */

		/* ग_लिखो back to io data output रेजिस्टर */
		rc = drxj_dap_ग_लिखो_reg16(demod->my_i2c_dev_addr, SIO_PDR_UIO_OUT_HI__A, value, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		अवरोध;
   /*=====================================================================*/
	हाल DRX_UIO4:
		/* DRX_UIO4: IRQN UIO-4 */
		अगर (!ext_attr->has_irqn)
			वापस -EIO;

		अगर (ext_attr->uio_irqn_mode != DRX_UIO_MODE_READWRITE)
			वापस -EIO;

		pin_cfg_value = 0;
		/* io_pad_cfg रेजिस्टर (8 bit reg.) MSB bit is 1 (शेष value) */
		pin_cfg_value |= 0x0113;
		/* io_pad_cfg_mode output mode is drive always */
		/* io_pad_cfg_drive is set to घातer 2 (23 mA) */

		/* ग_लिखो to io pad configuration रेजिस्टर - output mode */
		rc = drxj_dap_ग_लिखो_reg16(demod->my_i2c_dev_addr, SIO_PDR_IRQN_CFG__A, pin_cfg_value, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण

		/* use corresponding bit in io data output registar */
		rc = drxj_dap_पढ़ो_reg16(demod->my_i2c_dev_addr, SIO_PDR_UIO_OUT_LO__A, &value, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		अगर (uio_data->value == false)
			value &= 0xEFFF;	/* ग_लिखो zero to 12th bit - 4th UIO */
		अन्यथा
			value |= 0x1000;	/* ग_लिखो one to 12th bit - 4th UIO */

		/* ग_लिखो back to io data output रेजिस्टर */
		rc = drxj_dap_ग_लिखो_reg16(demod->my_i2c_dev_addr, SIO_PDR_UIO_OUT_LO__A, value, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		अवरोध;
      /*=====================================================================*/
	शेष:
		वापस -EINVAL;
	पूर्ण			/* चयन ( uio_data->uio ) */

	/*  Write magic word to disable pdr reg ग_लिखो               */
	rc = drxj_dap_ग_लिखो_reg16(demod->my_i2c_dev_addr, SIO_TOP_COMM_KEY__A, 0x0000, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*---------------------------------------------------------------------------*/
/* UIO Configuration Functions - end                                         */
/*---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* I2C Bridge Functions - begin                                               */
/*----------------------------------------------------------------------------*/
/*
* \पn पूर्णांक ctrl_i2c_bridge()
* \मrief Open or बंद the I2C चयन to tuner.
* \param demod Poपूर्णांकer to demodulator instance.
* \param bridge_बंदd Poपूर्णांकer to bool indication अगर bridge is बंदd not.
* \लeturn पूर्णांक.

*/
अटल पूर्णांक
ctrl_i2c_bridge(काष्ठा drx_demod_instance *demod, bool *bridge_बंदd)
अणु
	काष्ठा drxj_hi_cmd hi_cmd;
	u16 result = 0;

	/* check arguments */
	अगर (bridge_बंदd == शून्य)
		वापस -EINVAL;

	hi_cmd.cmd = SIO_HI_RA_RAM_CMD_BRDCTRL;
	hi_cmd.param1 = SIO_HI_RA_RAM_PAR_1_PAR1_SEC_KEY;
	अगर (*bridge_बंदd)
		hi_cmd.param2 = SIO_HI_RA_RAM_PAR_2_BRD_CFG_CLOSED;
	अन्यथा
		hi_cmd.param2 = SIO_HI_RA_RAM_PAR_2_BRD_CFG_OPEN;

	वापस hi_command(demod->my_i2c_dev_addr, &hi_cmd, &result);
पूर्ण

/*----------------------------------------------------------------------------*/
/* I2C Bridge Functions - end                                                 */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Smart antenna Functions - begin                                            */
/*----------------------------------------------------------------------------*/
/*
* \पn पूर्णांक smart_ant_init()
* \मrief Initialize Smart Antenna.
* \param poपूर्णांकer to काष्ठा drx_demod_instance.
* \लeturn पूर्णांक.
*
*/
अटल पूर्णांक smart_ant_init(काष्ठा drx_demod_instance *demod)
अणु
	काष्ठा drxj_data *ext_attr = शून्य;
	काष्ठा i2c_device_addr *dev_addr = शून्य;
	काष्ठा drxuio_cfg uio_cfg = अणु DRX_UIO1, DRX_UIO_MODE_FIRMWARE_SMA पूर्ण;
	पूर्णांक rc;
	u16 data = 0;

	dev_addr = demod->my_i2c_dev_addr;
	ext_attr = (काष्ठा drxj_data *) demod->my_ext_attr;

	/*  Write magic word to enable pdr reg ग_लिखो               */
	rc = drxj_dap_ग_लिखो_reg16(demod->my_i2c_dev_addr, SIO_TOP_COMM_KEY__A, SIO_TOP_COMM_KEY_KEY, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	/* init smart antenna */
	rc = drxj_dap_पढ़ो_reg16(dev_addr, SIO_SA_TX_COMMAND__A, &data, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	अगर (ext_attr->smart_ant_inverted) अणु
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_SA_TX_COMMAND__A, (data | SIO_SA_TX_COMMAND_TX_INVERT__M) | SIO_SA_TX_COMMAND_TX_ENABLE__M, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
	पूर्ण अन्यथा अणु
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_SA_TX_COMMAND__A, (data & (~SIO_SA_TX_COMMAND_TX_INVERT__M)) | SIO_SA_TX_COMMAND_TX_ENABLE__M, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
	पूर्ण

	/* config SMA_TX pin to smart antenna mode */
	rc = ctrl_set_uio_cfg(demod, &uio_cfg);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(demod->my_i2c_dev_addr, SIO_PDR_SMA_TX_CFG__A, 0x13, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(demod->my_i2c_dev_addr, SIO_PDR_SMA_TX_GPIO_FNC__A, 0x03, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/*  Write magic word to disable pdr reg ग_लिखो               */
	rc = drxj_dap_ग_लिखो_reg16(demod->my_i2c_dev_addr, SIO_TOP_COMM_KEY__A, 0x0000, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

अटल पूर्णांक scu_command(काष्ठा i2c_device_addr *dev_addr, काष्ठा drxjscu_cmd *cmd)
अणु
	पूर्णांक rc;
	u16 cur_cmd = 0;
	अचिन्हित दीर्घ समयout;

	/* Check param */
	अगर (cmd == शून्य)
		वापस -EINVAL;

	/* Wait until SCU command पूर्णांकerface is पढ़ोy to receive command */
	rc = drxj_dap_पढ़ो_reg16(dev_addr, SCU_RAM_COMMAND__A, &cur_cmd, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	अगर (cur_cmd != DRX_SCU_READY)
		वापस -EIO;

	चयन (cmd->parameter_len) अणु
	हाल 5:
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_PARAM_4__A, *(cmd->parameter + 4), 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		fallthrough;
	हाल 4:
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_PARAM_3__A, *(cmd->parameter + 3), 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		fallthrough;
	हाल 3:
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_PARAM_2__A, *(cmd->parameter + 2), 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		fallthrough;
	हाल 2:
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_PARAM_1__A, *(cmd->parameter + 1), 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		fallthrough;
	हाल 1:
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_PARAM_0__A, *(cmd->parameter + 0), 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		fallthrough;
	हाल 0:
		/* करो nothing */
		अवरोध;
	शेष:
		/* this number of parameters is not supported */
		वापस -EIO;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_COMMAND__A, cmd->command, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/* Wait until SCU has processed command */
	समयout = jअगरfies + msecs_to_jअगरfies(DRXJ_MAX_WAITTIME);
	जबतक (समय_is_after_jअगरfies(समयout)) अणु
		rc = drxj_dap_पढ़ो_reg16(dev_addr, SCU_RAM_COMMAND__A, &cur_cmd, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		अगर (cur_cmd == DRX_SCU_READY)
			अवरोध;
		usleep_range(1000, 2000);
	पूर्ण

	अगर (cur_cmd != DRX_SCU_READY)
		वापस -EIO;

	/* पढ़ो results */
	अगर ((cmd->result_len > 0) && (cmd->result != शून्य)) अणु
		s16 err;

		चयन (cmd->result_len) अणु
		हाल 4:
			rc = drxj_dap_पढ़ो_reg16(dev_addr, SCU_RAM_PARAM_3__A, cmd->result + 3, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			fallthrough;
		हाल 3:
			rc = drxj_dap_पढ़ो_reg16(dev_addr, SCU_RAM_PARAM_2__A, cmd->result + 2, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			fallthrough;
		हाल 2:
			rc = drxj_dap_पढ़ो_reg16(dev_addr, SCU_RAM_PARAM_1__A, cmd->result + 1, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			fallthrough;
		हाल 1:
			rc = drxj_dap_पढ़ो_reg16(dev_addr, SCU_RAM_PARAM_0__A, cmd->result + 0, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			fallthrough;
		हाल 0:
			/* करो nothing */
			अवरोध;
		शेष:
			/* this number of parameters is not supported */
			वापस -EIO;
		पूर्ण

		/* Check अगर an error was reported by SCU */
		err = cmd->result[0];

		/* check a few fixed error codes */
		अगर ((err == (s16) SCU_RAM_PARAM_0_RESULT_UNKSTD)
		    || (err == (s16) SCU_RAM_PARAM_0_RESULT_UNKCMD)
		    || (err == (s16) SCU_RAM_PARAM_0_RESULT_INVPAR)
		    || (err == (s16) SCU_RAM_PARAM_0_RESULT_SIZE)
		    ) अणु
			वापस -EINVAL;
		पूर्ण
		/* here it is assumed that negative means error, and positive no error */
		अन्यथा अगर (err < 0)
			वापस -EIO;
		अन्यथा
			वापस 0;
	पूर्ण

	वापस 0;

rw_error:
	वापस rc;
पूर्ण

/*
* \पn पूर्णांक DRXJ_DAP_SCUAtomicReadWriteBlock()
* \मrief Basic access routine क्रम SCU atomic पढ़ो or ग_लिखो access
* \param dev_addr  poपूर्णांकer to i2c dev address
* \param addr     destination/source address
* \param datasize size of data buffer in bytes
* \param data     poपूर्णांकer to data buffer
* \लeturn पूर्णांक
* \लetval 0 Success
* \लetval -EIO Timeout, I2C error, illegal bank
*
*/
#घोषणा ADDR_AT_SCU_SPACE(x) ((x - 0x82E000) * 2)
अटल
पूर्णांक drxj_dap_scu_atomic_पढ़ो_ग_लिखो_block(काष्ठा i2c_device_addr *dev_addr, u32 addr, u16 datasize,	/* max 30 bytes because the limit of SCU parameter */
					      u8 *data, bool पढ़ो_flag)
अणु
	काष्ठा drxjscu_cmd scu_cmd;
	पूर्णांक rc;
	u16 set_param_parameters[18];
	u16 cmd_result[15];

	/* Parameter check */
	अगर (!data || !dev_addr || (datasize % 2) || ((datasize / 2) > 16))
		वापस -EINVAL;

	set_param_parameters[1] = (u16) ADDR_AT_SCU_SPACE(addr);
	अगर (पढ़ो_flag) अणु		/* पढ़ो */
		set_param_parameters[0] = ((~(0x0080)) & datasize);
		scu_cmd.parameter_len = 2;
		scu_cmd.result_len = datasize / 2 + 2;
	पूर्ण अन्यथा अणु
		पूर्णांक i = 0;

		set_param_parameters[0] = 0x0080 | datasize;
		क्रम (i = 0; i < (datasize / 2); i++) अणु
			set_param_parameters[i + 2] =
			    (data[2 * i] | (data[(2 * i) + 1] << 8));
		पूर्ण
		scu_cmd.parameter_len = datasize / 2 + 2;
		scu_cmd.result_len = 1;
	पूर्ण

	scu_cmd.command =
	    SCU_RAM_COMMAND_STANDARD_TOP |
	    SCU_RAM_COMMAND_CMD_AUX_SCU_ATOMIC_ACCESS;
	scu_cmd.result = cmd_result;
	scu_cmd.parameter = set_param_parameters;
	rc = scu_command(dev_addr, &scu_cmd);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	अगर (पढ़ो_flag) अणु
		पूर्णांक i = 0;
		/* पढ़ो data from buffer */
		क्रम (i = 0; i < (datasize / 2); i++) अणु
			data[2 * i] = (u8) (scu_cmd.result[i + 2] & 0xFF);
			data[(2 * i) + 1] = (u8) (scu_cmd.result[i + 2] >> 8);
		पूर्ण
	पूर्ण

	वापस 0;

rw_error:
	वापस rc;

पूर्ण

/*============================================================================*/

/*
* \पn पूर्णांक DRXJ_DAP_AtomicReadReg16()
* \मrief Atomic पढ़ो of 16 bits words
*/
अटल
पूर्णांक drxj_dap_scu_atomic_पढ़ो_reg16(काष्ठा i2c_device_addr *dev_addr,
					 u32 addr,
					 u16 *data, u32 flags)
अणु
	u8 buf[2] = अणु 0 पूर्ण;
	पूर्णांक rc;
	u16 word = 0;

	अगर (!data)
		वापस -EINVAL;

	rc = drxj_dap_scu_atomic_पढ़ो_ग_लिखो_block(dev_addr, addr, 2, buf, true);
	अगर (rc < 0)
		वापस rc;

	word = (u16) (buf[0] + (buf[1] << 8));

	*data = word;

	वापस rc;
पूर्ण

/*============================================================================*/
/*
* \पn पूर्णांक drxj_dap_scu_atomic_ग_लिखो_reg16()
* \मrief Atomic पढ़ो of 16 bits words
*/
अटल
पूर्णांक drxj_dap_scu_atomic_ग_लिखो_reg16(काष्ठा i2c_device_addr *dev_addr,
					  u32 addr,
					  u16 data, u32 flags)
अणु
	u8 buf[2];
	पूर्णांक rc;

	buf[0] = (u8) (data & 0xff);
	buf[1] = (u8) ((data >> 8) & 0xff);

	rc = drxj_dap_scu_atomic_पढ़ो_ग_लिखो_block(dev_addr, addr, 2, buf, false);

	वापस rc;
पूर्ण

/* -------------------------------------------------------------------------- */
/*
* \मrief Measure result of ADC synchronisation
* \param demod demod instance
* \param count (वापसed) count
* \लeturn पूर्णांक.
* \लetval 0    Success
* \लetval -EIO Failure: I2C error
*
*/
अटल पूर्णांक adc_sync_measurement(काष्ठा drx_demod_instance *demod, u16 *count)
अणु
	काष्ठा i2c_device_addr *dev_addr = शून्य;
	पूर्णांक rc;
	u16 data = 0;

	dev_addr = demod->my_i2c_dev_addr;

	/* Start measurement */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_AF_COMM_EXEC__A, IQM_AF_COMM_EXEC_ACTIVE, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_AF_START_LOCK__A, 1, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/* Wait at least 3*128*(1/sysclk) <<< 1 millisec */
	msleep(1);

	*count = 0;
	rc = drxj_dap_पढ़ो_reg16(dev_addr, IQM_AF_PHASE0__A, &data, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	अगर (data == 127)
		*count = *count + 1;
	rc = drxj_dap_पढ़ो_reg16(dev_addr, IQM_AF_PHASE1__A, &data, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	अगर (data == 127)
		*count = *count + 1;
	rc = drxj_dap_पढ़ो_reg16(dev_addr, IQM_AF_PHASE2__A, &data, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	अगर (data == 127)
		*count = *count + 1;

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*
* \मrief Synchronize analog and digital घड़ी करोमुख्यs
* \param demod demod instance
* \लeturn पूर्णांक.
* \लetval 0    Success
* \लetval -EIO Failure: I2C error or failure to synchronize
*
* An IQM reset will also reset the results of this synchronization.
* After an IQM reset this routine needs to be called again.
*
*/

अटल पूर्णांक adc_synchronization(काष्ठा drx_demod_instance *demod)
अणु
	काष्ठा i2c_device_addr *dev_addr = शून्य;
	पूर्णांक rc;
	u16 count = 0;

	dev_addr = demod->my_i2c_dev_addr;

	rc = adc_sync_measurement(demod, &count);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	अगर (count == 1) अणु
		/* Try sampling on a dअगरferent edge */
		u16 clk_neg = 0;

		rc = drxj_dap_पढ़ो_reg16(dev_addr, IQM_AF_CLKNEG__A, &clk_neg, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण

		clk_neg ^= IQM_AF_CLKNEG_CLKNEGDATA__M;
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_AF_CLKNEG__A, clk_neg, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण

		rc = adc_sync_measurement(demod, &count);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
	पूर्ण

	/* TODO: implement fallback scenarios */
	अगर (count < 2)
		वापस -EIO;

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*============================================================================*/
/*==                      END AUXILIARY FUNCTIONS                           ==*/
/*============================================================================*/

/*============================================================================*/
/*============================================================================*/
/*==                8VSB & QAM COMMON DATAPATH FUNCTIONS                    ==*/
/*============================================================================*/
/*============================================================================*/
/*
* \पn पूर्णांक init_agc ()
* \मrief Initialize AGC क्रम all standards.
* \param demod instance of demodulator.
* \param channel poपूर्णांकer to channel data.
* \लeturn पूर्णांक.
*/
अटल पूर्णांक init_agc(काष्ठा drx_demod_instance *demod)
अणु
	काष्ठा i2c_device_addr *dev_addr = शून्य;
	काष्ठा drx_common_attr *common_attr = शून्य;
	काष्ठा drxj_data *ext_attr = शून्य;
	काष्ठा drxj_cfg_agc *p_agc_rf_settings = शून्य;
	काष्ठा drxj_cfg_agc *p_agc_अगर_settings = शून्य;
	पूर्णांक rc;
	u16 ingain_tgt_max = 0;
	u16 clp_dir_to = 0;
	u16 sns_sum_max = 0;
	u16 clp_sum_max = 0;
	u16 sns_dir_to = 0;
	u16 ki_innergain_min = 0;
	u16 agc_ki = 0;
	u16 ki_max = 0;
	u16 अगर_iaccu_hi_tgt_min = 0;
	u16 data = 0;
	u16 agc_ki_dgain = 0;
	u16 ki_min = 0;
	u16 clp_ctrl_mode = 0;
	u16 agc_rf = 0;
	u16 agc_अगर = 0;

	dev_addr = demod->my_i2c_dev_addr;
	common_attr = (काष्ठा drx_common_attr *) demod->my_common_attr;
	ext_attr = (काष्ठा drxj_data *) demod->my_ext_attr;

	चयन (ext_attr->standard) अणु
	हाल DRX_STANDARD_8VSB:
		clp_sum_max = 1023;
		clp_dir_to = (u16) (-9);
		sns_sum_max = 1023;
		sns_dir_to = (u16) (-9);
		ki_innergain_min = (u16) (-32768);
		ki_max = 0x032C;
		agc_ki_dgain = 0xC;
		अगर_iaccu_hi_tgt_min = 2047;
		ki_min = 0x0117;
		ingain_tgt_max = 16383;
		clp_ctrl_mode = 0;
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_KI_MINGAIN__A, 0x7fff, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_KI_MAXGAIN__A, 0x0, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_CLP_SUM__A, 0, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_CLP_CYCCNT__A, 0, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_CLP_सूची_WD__A, 0, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_CLP_सूची_STP__A, 1, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_SNS_SUM__A, 0, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_SNS_CYCCNT__A, 0, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_SNS_सूची_WD__A, 0, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_SNS_सूची_STP__A, 1, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_INGAIN__A, 1024, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_VSB_AGC_POW_TGT__A, 22600, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_INGAIN_TGT__A, 13200, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		p_agc_अगर_settings = &(ext_attr->vsb_अगर_agc_cfg);
		p_agc_rf_settings = &(ext_attr->vsb_rf_agc_cfg);
		अवरोध;
#अगर_अघोषित DRXJ_VSB_ONLY
	हाल DRX_STANDARD_ITU_A:
	हाल DRX_STANDARD_ITU_C:
	हाल DRX_STANDARD_ITU_B:
		ingain_tgt_max = 5119;
		clp_sum_max = 1023;
		clp_dir_to = (u16) (-5);
		sns_sum_max = 127;
		sns_dir_to = (u16) (-3);
		ki_innergain_min = 0;
		ki_max = 0x0657;
		अगर_iaccu_hi_tgt_min = 2047;
		agc_ki_dgain = 0x7;
		ki_min = 0x0117;
		clp_ctrl_mode = 0;
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_KI_MINGAIN__A, 0x7fff, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_KI_MAXGAIN__A, 0x0, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_CLP_SUM__A, 0, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_CLP_CYCCNT__A, 0, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_CLP_सूची_WD__A, 0, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_CLP_सूची_STP__A, 1, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_SNS_SUM__A, 0, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_SNS_CYCCNT__A, 0, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_SNS_सूची_WD__A, 0, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_SNS_सूची_STP__A, 1, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		p_agc_अगर_settings = &(ext_attr->qam_अगर_agc_cfg);
		p_agc_rf_settings = &(ext_attr->qam_rf_agc_cfg);
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_INGAIN_TGT__A, p_agc_अगर_settings->top, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण

		rc = drxj_dap_पढ़ो_reg16(dev_addr, SCU_RAM_AGC_KI__A, &agc_ki, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		agc_ki &= 0xf000;
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_KI__A, agc_ki, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		अवरोध;
#पूर्ण_अगर
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* क्रम new AGC पूर्णांकerface */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_INGAIN_TGT_MIN__A, p_agc_अगर_settings->top, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_INGAIN__A, p_agc_अगर_settings->top, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण	/* Gain fed from inner to outer AGC */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_INGAIN_TGT_MAX__A, ingain_tgt_max, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_IF_IACCU_HI_TGT_MIN__A, अगर_iaccu_hi_tgt_min, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_IF_IACCU_HI__A, 0, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण	/* set to p_agc_settings->top beक्रमe */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_IF_IACCU_LO__A, 0, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_RF_IACCU_HI__A, 0, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_RF_IACCU_LO__A, 0, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_RF_MAX__A, 32767, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_CLP_SUM_MAX__A, clp_sum_max, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_SNS_SUM_MAX__A, sns_sum_max, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_KI_INNERGAIN_MIN__A, ki_innergain_min, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_FAST_SNS_CTRL_DELAY__A, 50, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_KI_CYCLEN__A, 500, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_SNS_CYCLEN__A, 500, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_KI_MAXMINGAIN_TH__A, 20, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_KI_MIN__A, ki_min, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_KI_MAX__A, ki_max, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_KI_RED__A, 0, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_CLP_SUM_MIN__A, 8, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_CLP_CYCLEN__A, 500, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_CLP_सूची_TO__A, clp_dir_to, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_SNS_SUM_MIN__A, 8, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_SNS_सूची_TO__A, sns_dir_to, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_FAST_CLP_CTRL_DELAY__A, 50, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_CLP_CTRL_MODE__A, clp_ctrl_mode, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	agc_rf = 0x800 + p_agc_rf_settings->cut_off_current;
	अगर (common_attr->tuner_rf_agc_pol == true)
		agc_rf = 0x87ff - agc_rf;

	agc_अगर = 0x800;
	अगर (common_attr->tuner_अगर_agc_pol == true)
		agc_rf = 0x87ff - agc_rf;

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_AF_AGC_RF__A, agc_rf, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_AF_AGC_IF__A, agc_अगर, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/* Set/restore Ki DGAIN factor */
	rc = drxj_dap_पढ़ो_reg16(dev_addr, SCU_RAM_AGC_KI__A, &data, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	data &= ~SCU_RAM_AGC_KI_DGAIN__M;
	data |= (agc_ki_dgain << SCU_RAM_AGC_KI_DGAIN__B);
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_AGC_KI__A, data, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*
* \पn पूर्णांक set_frequency ()
* \मrief Set frequency shअगरt.
* \param demod instance of demodulator.
* \param channel poपूर्णांकer to channel data.
* \param tuner_freq_offset residual frequency from tuner.
* \लeturn पूर्णांक.
*/
अटल पूर्णांक
set_frequency(काष्ठा drx_demod_instance *demod,
	      काष्ठा drx_channel *channel, s32 tuner_freq_offset)
अणु
	काष्ठा i2c_device_addr *dev_addr = demod->my_i2c_dev_addr;
	काष्ठा drxj_data *ext_attr = demod->my_ext_attr;
	पूर्णांक rc;
	s32 sampling_frequency = 0;
	s32 frequency_shअगरt = 0;
	s32 अगर_freq_actual = 0;
	s32 rf_freq_residual = -1 * tuner_freq_offset;
	s32 adc_freq = 0;
	s32 पूर्णांकermediate_freq = 0;
	u32 iqm_fs_rate_ofs = 0;
	bool adc_flip = true;
	bool select_pos_image = false;
	bool rf_mirror;
	bool tuner_mirror;
	bool image_to_select;
	s32 fm_frequency_shअगरt = 0;

	rf_mirror = (ext_attr->mirror == DRX_MIRROR_YES) ? true : false;
	tuner_mirror = demod->my_common_attr->mirror_freq_spect ? false : true;
	/*
	   Program frequency shअगरter
	   No need to account क्रम mirroring on RF
	 */
	चयन (ext_attr->standard) अणु
	हाल DRX_STANDARD_ITU_A:
	हाल DRX_STANDARD_ITU_C:
	हाल DRX_STANDARD_PAL_SECAM_LP:
	हाल DRX_STANDARD_8VSB:
		select_pos_image = true;
		अवरोध;
	हाल DRX_STANDARD_FM:
		/* After IQM FS sound carrier must appear at 4 Mhz in spect.
		   Sound carrier is alपढ़ोy 3Mhz above centre frequency due
		   to tuner setting so now add an extra shअगरt of 1MHz... */
		fm_frequency_shअगरt = 1000;
		fallthrough;
	हाल DRX_STANDARD_ITU_B:
	हाल DRX_STANDARD_NTSC:
	हाल DRX_STANDARD_PAL_SECAM_BG:
	हाल DRX_STANDARD_PAL_SECAM_DK:
	हाल DRX_STANDARD_PAL_SECAM_I:
	हाल DRX_STANDARD_PAL_SECAM_L:
		select_pos_image = false;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	पूर्णांकermediate_freq = demod->my_common_attr->पूर्णांकermediate_freq;
	sampling_frequency = demod->my_common_attr->sys_घड़ी_freq / 3;
	अगर (tuner_mirror)
		अगर_freq_actual = पूर्णांकermediate_freq + rf_freq_residual + fm_frequency_shअगरt;
	अन्यथा
		अगर_freq_actual = पूर्णांकermediate_freq - rf_freq_residual - fm_frequency_shअगरt;
	अगर (अगर_freq_actual > sampling_frequency / 2) अणु
		/* adc mirrors */
		adc_freq = sampling_frequency - अगर_freq_actual;
		adc_flip = true;
	पूर्ण अन्यथा अणु
		/* adc करोesn't mirror */
		adc_freq = अगर_freq_actual;
		adc_flip = false;
	पूर्ण

	frequency_shअगरt = adc_freq;
	image_to_select =
	    (bool) (rf_mirror ^ tuner_mirror ^ adc_flip ^ select_pos_image);
	iqm_fs_rate_ofs = frac28(frequency_shअगरt, sampling_frequency);

	अगर (image_to_select)
		iqm_fs_rate_ofs = ~iqm_fs_rate_ofs + 1;

	/* Program frequency shअगरter with tuner offset compensation */
	/* frequency_shअगरt += tuner_freq_offset; TODO */
	rc = drxdap_fasi_ग_लिखो_reg32(dev_addr, IQM_FS_RATE_OFS_LO__A, iqm_fs_rate_ofs, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	ext_attr->iqm_fs_rate_ofs = iqm_fs_rate_ofs;
	ext_attr->pos_image = (bool) (rf_mirror ^ tuner_mirror ^ select_pos_image);

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*
* \पn पूर्णांक get_acc_pkt_err()
* \मrief Retrieve संकेत strength क्रम VSB and QAM.
* \param demod Poपूर्णांकer to demod instance
* \param packet_err Poपूर्णांकer to packet error
* \लeturn पूर्णांक.
* \लetval 0 sig_strength contains valid data.
* \लetval -EINVAL sig_strength is शून्य.
* \लetval -EIO Erroneous data, sig_strength contains invalid data.
*/
#अगर_घोषित DRXJ_SIGNAL_ACCUM_ERR
अटल पूर्णांक get_acc_pkt_err(काष्ठा drx_demod_instance *demod, u16 *packet_err)
अणु
	पूर्णांक rc;
	अटल u16 pkt_err;
	अटल u16 last_pkt_err;
	u16 data = 0;
	काष्ठा drxj_data *ext_attr = शून्य;
	काष्ठा i2c_device_addr *dev_addr = शून्य;

	ext_attr = (काष्ठा drxj_data *) demod->my_ext_attr;
	dev_addr = demod->my_i2c_dev_addr;

	rc = drxj_dap_पढ़ो_reg16(dev_addr, SCU_RAM_FEC_ACCUM_PKT_FAILURES__A, &data, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	अगर (ext_attr->reset_pkt_err_acc) अणु
		last_pkt_err = data;
		pkt_err = 0;
		ext_attr->reset_pkt_err_acc = false;
	पूर्ण

	अगर (data < last_pkt_err) अणु
		pkt_err += 0xffff - last_pkt_err;
		pkt_err += data;
	पूर्ण अन्यथा अणु
		pkt_err += (data - last_pkt_err);
	पूर्ण
	*packet_err = pkt_err;
	last_pkt_err = data;

	वापस 0;
rw_error:
	वापस rc;
पूर्ण
#पूर्ण_अगर


/*============================================================================*/

/*
* \पn पूर्णांक set_agc_rf ()
* \मrief Configure RF AGC
* \param demod instance of demodulator.
* \param agc_settings AGC configuration काष्ठाure
* \लeturn पूर्णांक.
*/
अटल पूर्णांक
set_agc_rf(काष्ठा drx_demod_instance *demod, काष्ठा drxj_cfg_agc *agc_settings, bool atomic)
अणु
	काष्ठा i2c_device_addr *dev_addr = शून्य;
	काष्ठा drxj_data *ext_attr = शून्य;
	काष्ठा drxj_cfg_agc *p_agc_settings = शून्य;
	काष्ठा drx_common_attr *common_attr = शून्य;
	पूर्णांक rc;
	drx_ग_लिखो_reg16func_t scu_wr16 = शून्य;
	drx_पढ़ो_reg16func_t scu_rr16 = शून्य;

	common_attr = (काष्ठा drx_common_attr *) demod->my_common_attr;
	dev_addr = demod->my_i2c_dev_addr;
	ext_attr = (काष्ठा drxj_data *) demod->my_ext_attr;

	अगर (atomic) अणु
		scu_rr16 = drxj_dap_scu_atomic_पढ़ो_reg16;
		scu_wr16 = drxj_dap_scu_atomic_ग_लिखो_reg16;
	पूर्ण अन्यथा अणु
		scu_rr16 = drxj_dap_पढ़ो_reg16;
		scu_wr16 = drxj_dap_ग_लिखो_reg16;
	पूर्ण

	/* Configure AGC only अगर standard is currently active */
	अगर ((ext_attr->standard == agc_settings->standard) ||
	    (DRXJ_ISQAMSTD(ext_attr->standard) &&
	     DRXJ_ISQAMSTD(agc_settings->standard)) ||
	    (DRXJ_ISATVSTD(ext_attr->standard) &&
	     DRXJ_ISATVSTD(agc_settings->standard))) अणु
		u16 data = 0;

		चयन (agc_settings->ctrl_mode) अणु
		हाल DRX_AGC_CTRL_AUTO:

			/* Enable RF AGC DAC */
			rc = drxj_dap_पढ़ो_reg16(dev_addr, IQM_AF_STDBY__A, &data, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			data |= IQM_AF_STDBY_STDBY_TAGC_RF_A2_ACTIVE;
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_AF_STDBY__A, data, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण

			/* Enable SCU RF AGC loop */
			rc = (*scu_rr16)(dev_addr, SCU_RAM_AGC_KI__A, &data, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			data &= ~SCU_RAM_AGC_KI_RF__M;
			अगर (ext_attr->standard == DRX_STANDARD_8VSB)
				data |= (2 << SCU_RAM_AGC_KI_RF__B);
			अन्यथा अगर (DRXJ_ISQAMSTD(ext_attr->standard))
				data |= (5 << SCU_RAM_AGC_KI_RF__B);
			अन्यथा
				data |= (4 << SCU_RAM_AGC_KI_RF__B);

			अगर (common_attr->tuner_rf_agc_pol)
				data |= SCU_RAM_AGC_KI_INV_RF_POL__M;
			अन्यथा
				data &= ~SCU_RAM_AGC_KI_INV_RF_POL__M;
			rc = (*scu_wr16)(dev_addr, SCU_RAM_AGC_KI__A, data, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण

			/* Set speed ( using complementary reduction value ) */
			rc = (*scu_rr16)(dev_addr, SCU_RAM_AGC_KI_RED__A, &data, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			data &= ~SCU_RAM_AGC_KI_RED_RAGC_RED__M;
			rc = (*scu_wr16)(dev_addr, SCU_RAM_AGC_KI_RED__A, (~(agc_settings->speed << SCU_RAM_AGC_KI_RED_RAGC_RED__B) & SCU_RAM_AGC_KI_RED_RAGC_RED__M) | data, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण

			अगर (agc_settings->standard == DRX_STANDARD_8VSB)
				p_agc_settings = &(ext_attr->vsb_अगर_agc_cfg);
			अन्यथा अगर (DRXJ_ISQAMSTD(agc_settings->standard))
				p_agc_settings = &(ext_attr->qam_अगर_agc_cfg);
			अन्यथा अगर (DRXJ_ISATVSTD(agc_settings->standard))
				p_agc_settings = &(ext_attr->atv_अगर_agc_cfg);
			अन्यथा
				वापस -EINVAL;

			/* Set TOP, only अगर IF-AGC is in AUTO mode */
			अगर (p_agc_settings->ctrl_mode == DRX_AGC_CTRL_AUTO) अणु
				rc = (*scu_wr16)(dev_addr, SCU_RAM_AGC_IF_IACCU_HI_TGT_MAX__A, agc_settings->top, 0);
				अगर (rc != 0) अणु
					pr_err("error %d\n", rc);
					जाओ rw_error;
				पूर्ण
				rc = (*scu_wr16)(dev_addr, SCU_RAM_AGC_IF_IACCU_HI_TGT__A, agc_settings->top, 0);
				अगर (rc != 0) अणु
					pr_err("error %d\n", rc);
					जाओ rw_error;
				पूर्ण
			पूर्ण

			/* Cut-Off current */
			rc = (*scu_wr16)(dev_addr, SCU_RAM_AGC_RF_IACCU_HI_CO__A, agc_settings->cut_off_current, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			अवरोध;
		हाल DRX_AGC_CTRL_USER:

			/* Enable RF AGC DAC */
			rc = drxj_dap_पढ़ो_reg16(dev_addr, IQM_AF_STDBY__A, &data, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			data |= IQM_AF_STDBY_STDBY_TAGC_RF_A2_ACTIVE;
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_AF_STDBY__A, data, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण

			/* Disable SCU RF AGC loop */
			rc = (*scu_rr16)(dev_addr, SCU_RAM_AGC_KI__A, &data, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			data &= ~SCU_RAM_AGC_KI_RF__M;
			अगर (common_attr->tuner_rf_agc_pol)
				data |= SCU_RAM_AGC_KI_INV_RF_POL__M;
			अन्यथा
				data &= ~SCU_RAM_AGC_KI_INV_RF_POL__M;
			rc = (*scu_wr16)(dev_addr, SCU_RAM_AGC_KI__A, data, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण

			/* Write value to output pin */
			rc = (*scu_wr16)(dev_addr, SCU_RAM_AGC_RF_IACCU_HI__A, agc_settings->output_level, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			अवरोध;
		हाल DRX_AGC_CTRL_OFF:

			/* Disable RF AGC DAC */
			rc = drxj_dap_पढ़ो_reg16(dev_addr, IQM_AF_STDBY__A, &data, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			data &= (~IQM_AF_STDBY_STDBY_TAGC_RF_A2_ACTIVE);
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_AF_STDBY__A, data, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण

			/* Disable SCU RF AGC loop */
			rc = (*scu_rr16)(dev_addr, SCU_RAM_AGC_KI__A, &data, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			data &= ~SCU_RAM_AGC_KI_RF__M;
			rc = (*scu_wr16)(dev_addr, SCU_RAM_AGC_KI__A, data, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण		/* चयन ( agcsettings->ctrl_mode ) */
	पूर्ण

	/* Store rf agc settings */
	चयन (agc_settings->standard) अणु
	हाल DRX_STANDARD_8VSB:
		ext_attr->vsb_rf_agc_cfg = *agc_settings;
		अवरोध;
#अगर_अघोषित DRXJ_VSB_ONLY
	हाल DRX_STANDARD_ITU_A:
	हाल DRX_STANDARD_ITU_B:
	हाल DRX_STANDARD_ITU_C:
		ext_attr->qam_rf_agc_cfg = *agc_settings;
		अवरोध;
#पूर्ण_अगर
	शेष:
		वापस -EIO;
	पूर्ण

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*
* \पn पूर्णांक set_agc_अगर ()
* \मrief Configure If AGC
* \param demod instance of demodulator.
* \param agc_settings AGC configuration काष्ठाure
* \लeturn पूर्णांक.
*/
अटल पूर्णांक
set_agc_अगर(काष्ठा drx_demod_instance *demod, काष्ठा drxj_cfg_agc *agc_settings, bool atomic)
अणु
	काष्ठा i2c_device_addr *dev_addr = शून्य;
	काष्ठा drxj_data *ext_attr = शून्य;
	काष्ठा drxj_cfg_agc *p_agc_settings = शून्य;
	काष्ठा drx_common_attr *common_attr = शून्य;
	drx_ग_लिखो_reg16func_t scu_wr16 = शून्य;
	drx_पढ़ो_reg16func_t scu_rr16 = शून्य;
	पूर्णांक rc;

	common_attr = (काष्ठा drx_common_attr *) demod->my_common_attr;
	dev_addr = demod->my_i2c_dev_addr;
	ext_attr = (काष्ठा drxj_data *) demod->my_ext_attr;

	अगर (atomic) अणु
		scu_rr16 = drxj_dap_scu_atomic_पढ़ो_reg16;
		scu_wr16 = drxj_dap_scu_atomic_ग_लिखो_reg16;
	पूर्ण अन्यथा अणु
		scu_rr16 = drxj_dap_पढ़ो_reg16;
		scu_wr16 = drxj_dap_ग_लिखो_reg16;
	पूर्ण

	/* Configure AGC only अगर standard is currently active */
	अगर ((ext_attr->standard == agc_settings->standard) ||
	    (DRXJ_ISQAMSTD(ext_attr->standard) &&
	     DRXJ_ISQAMSTD(agc_settings->standard)) ||
	    (DRXJ_ISATVSTD(ext_attr->standard) &&
	     DRXJ_ISATVSTD(agc_settings->standard))) अणु
		u16 data = 0;

		चयन (agc_settings->ctrl_mode) अणु
		हाल DRX_AGC_CTRL_AUTO:
			/* Enable IF AGC DAC */
			rc = drxj_dap_पढ़ो_reg16(dev_addr, IQM_AF_STDBY__A, &data, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			data |= IQM_AF_STDBY_STDBY_TAGC_IF_A2_ACTIVE;
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_AF_STDBY__A, data, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण

			/* Enable SCU IF AGC loop */
			rc = (*scu_rr16)(dev_addr, SCU_RAM_AGC_KI__A, &data, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			data &= ~SCU_RAM_AGC_KI_IF_AGC_DISABLE__M;
			data &= ~SCU_RAM_AGC_KI_IF__M;
			अगर (ext_attr->standard == DRX_STANDARD_8VSB)
				data |= (3 << SCU_RAM_AGC_KI_IF__B);
			अन्यथा अगर (DRXJ_ISQAMSTD(ext_attr->standard))
				data |= (6 << SCU_RAM_AGC_KI_IF__B);
			अन्यथा
				data |= (5 << SCU_RAM_AGC_KI_IF__B);

			अगर (common_attr->tuner_अगर_agc_pol)
				data |= SCU_RAM_AGC_KI_INV_IF_POL__M;
			अन्यथा
				data &= ~SCU_RAM_AGC_KI_INV_IF_POL__M;
			rc = (*scu_wr16)(dev_addr, SCU_RAM_AGC_KI__A, data, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण

			/* Set speed (using complementary reduction value) */
			rc = (*scu_rr16)(dev_addr, SCU_RAM_AGC_KI_RED__A, &data, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			data &= ~SCU_RAM_AGC_KI_RED_IAGC_RED__M;
			rc = (*scu_wr16) (dev_addr, SCU_RAM_AGC_KI_RED__A, (~(agc_settings->speed << SCU_RAM_AGC_KI_RED_IAGC_RED__B) & SCU_RAM_AGC_KI_RED_IAGC_RED__M) | data, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण

			अगर (agc_settings->standard == DRX_STANDARD_8VSB)
				p_agc_settings = &(ext_attr->vsb_rf_agc_cfg);
			अन्यथा अगर (DRXJ_ISQAMSTD(agc_settings->standard))
				p_agc_settings = &(ext_attr->qam_rf_agc_cfg);
			अन्यथा अगर (DRXJ_ISATVSTD(agc_settings->standard))
				p_agc_settings = &(ext_attr->atv_rf_agc_cfg);
			अन्यथा
				वापस -EINVAL;

			/* Restore TOP */
			अगर (p_agc_settings->ctrl_mode == DRX_AGC_CTRL_AUTO) अणु
				rc = (*scu_wr16)(dev_addr, SCU_RAM_AGC_IF_IACCU_HI_TGT_MAX__A, p_agc_settings->top, 0);
				अगर (rc != 0) अणु
					pr_err("error %d\n", rc);
					जाओ rw_error;
				पूर्ण
				rc = (*scu_wr16)(dev_addr, SCU_RAM_AGC_IF_IACCU_HI_TGT__A, p_agc_settings->top, 0);
				अगर (rc != 0) अणु
					pr_err("error %d\n", rc);
					जाओ rw_error;
				पूर्ण
			पूर्ण अन्यथा अणु
				rc = (*scu_wr16)(dev_addr, SCU_RAM_AGC_IF_IACCU_HI_TGT_MAX__A, 0, 0);
				अगर (rc != 0) अणु
					pr_err("error %d\n", rc);
					जाओ rw_error;
				पूर्ण
				rc = (*scu_wr16)(dev_addr, SCU_RAM_AGC_IF_IACCU_HI_TGT__A, 0, 0);
				अगर (rc != 0) अणु
					pr_err("error %d\n", rc);
					जाओ rw_error;
				पूर्ण
			पूर्ण
			अवरोध;

		हाल DRX_AGC_CTRL_USER:

			/* Enable IF AGC DAC */
			rc = drxj_dap_पढ़ो_reg16(dev_addr, IQM_AF_STDBY__A, &data, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			data |= IQM_AF_STDBY_STDBY_TAGC_IF_A2_ACTIVE;
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_AF_STDBY__A, data, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण

			/* Disable SCU IF AGC loop */
			rc = (*scu_rr16)(dev_addr, SCU_RAM_AGC_KI__A, &data, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			data &= ~SCU_RAM_AGC_KI_IF_AGC_DISABLE__M;
			data |= SCU_RAM_AGC_KI_IF_AGC_DISABLE__M;
			अगर (common_attr->tuner_अगर_agc_pol)
				data |= SCU_RAM_AGC_KI_INV_IF_POL__M;
			अन्यथा
				data &= ~SCU_RAM_AGC_KI_INV_IF_POL__M;
			rc = (*scu_wr16)(dev_addr, SCU_RAM_AGC_KI__A, data, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण

			/* Write value to output pin */
			rc = (*scu_wr16)(dev_addr, SCU_RAM_AGC_IF_IACCU_HI_TGT_MAX__A, agc_settings->output_level, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			अवरोध;

		हाल DRX_AGC_CTRL_OFF:

			/* Disable If AGC DAC */
			rc = drxj_dap_पढ़ो_reg16(dev_addr, IQM_AF_STDBY__A, &data, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			data &= (~IQM_AF_STDBY_STDBY_TAGC_IF_A2_ACTIVE);
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_AF_STDBY__A, data, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण

			/* Disable SCU IF AGC loop */
			rc = (*scu_rr16)(dev_addr, SCU_RAM_AGC_KI__A, &data, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			data &= ~SCU_RAM_AGC_KI_IF_AGC_DISABLE__M;
			data |= SCU_RAM_AGC_KI_IF_AGC_DISABLE__M;
			rc = (*scu_wr16)(dev_addr, SCU_RAM_AGC_KI__A, data, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण		/* चयन ( agcsettings->ctrl_mode ) */

		/* always set the top to support configurations without अगर-loop */
		rc = (*scu_wr16) (dev_addr, SCU_RAM_AGC_INGAIN_TGT_MIN__A, agc_settings->top, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
	पूर्ण

	/* Store अगर agc settings */
	चयन (agc_settings->standard) अणु
	हाल DRX_STANDARD_8VSB:
		ext_attr->vsb_अगर_agc_cfg = *agc_settings;
		अवरोध;
#अगर_अघोषित DRXJ_VSB_ONLY
	हाल DRX_STANDARD_ITU_A:
	हाल DRX_STANDARD_ITU_B:
	हाल DRX_STANDARD_ITU_C:
		ext_attr->qam_अगर_agc_cfg = *agc_settings;
		अवरोध;
#पूर्ण_अगर
	शेष:
		वापस -EIO;
	पूर्ण

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*
* \पn पूर्णांक set_iqm_af ()
* \मrief Configure IQM AF रेजिस्टरs
* \param demod instance of demodulator.
* \param active
* \लeturn पूर्णांक.
*/
अटल पूर्णांक set_iqm_af(काष्ठा drx_demod_instance *demod, bool active)
अणु
	u16 data = 0;
	काष्ठा i2c_device_addr *dev_addr = शून्य;
	पूर्णांक rc;

	dev_addr = demod->my_i2c_dev_addr;

	/* Configure IQM */
	rc = drxj_dap_पढ़ो_reg16(dev_addr, IQM_AF_STDBY__A, &data, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	अगर (!active)
		data &= ((~IQM_AF_STDBY_STDBY_ADC_A2_ACTIVE) & (~IQM_AF_STDBY_STDBY_AMP_A2_ACTIVE) & (~IQM_AF_STDBY_STDBY_PD_A2_ACTIVE) & (~IQM_AF_STDBY_STDBY_TAGC_IF_A2_ACTIVE) & (~IQM_AF_STDBY_STDBY_TAGC_RF_A2_ACTIVE));
	अन्यथा
		data |= (IQM_AF_STDBY_STDBY_ADC_A2_ACTIVE | IQM_AF_STDBY_STDBY_AMP_A2_ACTIVE | IQM_AF_STDBY_STDBY_PD_A2_ACTIVE | IQM_AF_STDBY_STDBY_TAGC_IF_A2_ACTIVE | IQM_AF_STDBY_STDBY_TAGC_RF_A2_ACTIVE);
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_AF_STDBY__A, data, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*============================================================================*/
/*==              END 8VSB & QAM COMMON DATAPATH FUNCTIONS                  ==*/
/*============================================================================*/

/*============================================================================*/
/*============================================================================*/
/*==                       8VSB DATAPATH FUNCTIONS                          ==*/
/*============================================================================*/
/*============================================================================*/

/*
* \पn पूर्णांक घातer_करोwn_vsb ()
* \मrief Powr करोwn QAM related blocks.
* \param demod instance of demodulator.
* \param channel poपूर्णांकer to channel data.
* \लeturn पूर्णांक.
*/
अटल पूर्णांक घातer_करोwn_vsb(काष्ठा drx_demod_instance *demod, bool primary)
अणु
	काष्ठा i2c_device_addr *dev_addr = demod->my_i2c_dev_addr;
	काष्ठा drxjscu_cmd cmd_scu = अणु /* command     */ 0,
		/* parameter_len */ 0,
		/* result_len    */ 0,
		/* *parameter   */ शून्य,
		/* *result      */ शून्य
	पूर्ण;
	काष्ठा drx_cfg_mpeg_output cfg_mpeg_output;
	पूर्णांक rc;
	u16 cmd_result = 0;

	/*
	   STOP demodulator
	   reset of FEC and VSB HW
	 */
	cmd_scu.command = SCU_RAM_COMMAND_STANDARD_VSB |
	    SCU_RAM_COMMAND_CMD_DEMOD_STOP;
	cmd_scu.parameter_len = 0;
	cmd_scu.result_len = 1;
	cmd_scu.parameter = शून्य;
	cmd_scu.result = &cmd_result;
	rc = scu_command(dev_addr, &cmd_scu);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/* stop all comm_exec */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_COMM_EXEC__A, FEC_COMM_EXEC_STOP, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, VSB_COMM_EXEC__A, VSB_COMM_EXEC_STOP, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	अगर (primary) अणु
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_COMM_EXEC__A, IQM_COMM_EXEC_STOP, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = set_iqm_af(demod, false);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
	पूर्ण अन्यथा अणु
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_FS_COMM_EXEC__A, IQM_FS_COMM_EXEC_STOP, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_FD_COMM_EXEC__A, IQM_FD_COMM_EXEC_STOP, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_RC_COMM_EXEC__A, IQM_RC_COMM_EXEC_STOP, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_RT_COMM_EXEC__A, IQM_RT_COMM_EXEC_STOP, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_CF_COMM_EXEC__A, IQM_CF_COMM_EXEC_STOP, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
	पूर्ण

	cfg_mpeg_output.enable_mpeg_output = false;
	rc = ctrl_set_cfg_mpeg_output(demod, &cfg_mpeg_output);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*
* \पn पूर्णांक set_vsb_leak_n_gain ()
* \मrief Set ATSC demod.
* \param demod instance of demodulator.
* \लeturn पूर्णांक.
*/
अटल पूर्णांक set_vsb_leak_n_gain(काष्ठा drx_demod_instance *demod)
अणु
	काष्ठा i2c_device_addr *dev_addr = शून्य;
	पूर्णांक rc;

	अटल स्थिर u8 vsb_ffe_leak_gain_ram0[] = अणु
		DRXJ_16TO8(0x8),	/* FFETRAINLKRATIO1  */
		DRXJ_16TO8(0x8),	/* FFETRAINLKRATIO2  */
		DRXJ_16TO8(0x8),	/* FFETRAINLKRATIO3  */
		DRXJ_16TO8(0xf),	/* FFETRAINLKRATIO4  */
		DRXJ_16TO8(0xf),	/* FFETRAINLKRATIO5  */
		DRXJ_16TO8(0xf),	/* FFETRAINLKRATIO6  */
		DRXJ_16TO8(0xf),	/* FFETRAINLKRATIO7  */
		DRXJ_16TO8(0xf),	/* FFETRAINLKRATIO8  */
		DRXJ_16TO8(0xf),	/* FFETRAINLKRATIO9  */
		DRXJ_16TO8(0x8),	/* FFETRAINLKRATIO10  */
		DRXJ_16TO8(0x8),	/* FFETRAINLKRATIO11 */
		DRXJ_16TO8(0x8),	/* FFETRAINLKRATIO12 */
		DRXJ_16TO8(0x10),	/* FFERCA1TRAINLKRATIO1 */
		DRXJ_16TO8(0x10),	/* FFERCA1TRAINLKRATIO2 */
		DRXJ_16TO8(0x10),	/* FFERCA1TRAINLKRATIO3 */
		DRXJ_16TO8(0x20),	/* FFERCA1TRAINLKRATIO4 */
		DRXJ_16TO8(0x20),	/* FFERCA1TRAINLKRATIO5 */
		DRXJ_16TO8(0x20),	/* FFERCA1TRAINLKRATIO6 */
		DRXJ_16TO8(0x20),	/* FFERCA1TRAINLKRATIO7 */
		DRXJ_16TO8(0x20),	/* FFERCA1TRAINLKRATIO8 */
		DRXJ_16TO8(0x20),	/* FFERCA1TRAINLKRATIO9 */
		DRXJ_16TO8(0x10),	/* FFERCA1TRAINLKRATIO10 */
		DRXJ_16TO8(0x10),	/* FFERCA1TRAINLKRATIO11 */
		DRXJ_16TO8(0x10),	/* FFERCA1TRAINLKRATIO12 */
		DRXJ_16TO8(0x10),	/* FFERCA1DATALKRATIO1 */
		DRXJ_16TO8(0x10),	/* FFERCA1DATALKRATIO2 */
		DRXJ_16TO8(0x10),	/* FFERCA1DATALKRATIO3 */
		DRXJ_16TO8(0x20),	/* FFERCA1DATALKRATIO4 */
		DRXJ_16TO8(0x20),	/* FFERCA1DATALKRATIO5 */
		DRXJ_16TO8(0x20),	/* FFERCA1DATALKRATIO6 */
		DRXJ_16TO8(0x20),	/* FFERCA1DATALKRATIO7 */
		DRXJ_16TO8(0x20),	/* FFERCA1DATALKRATIO8 */
		DRXJ_16TO8(0x20),	/* FFERCA1DATALKRATIO9 */
		DRXJ_16TO8(0x10),	/* FFERCA1DATALKRATIO10 */
		DRXJ_16TO8(0x10),	/* FFERCA1DATALKRATIO11 */
		DRXJ_16TO8(0x10),	/* FFERCA1DATALKRATIO12 */
		DRXJ_16TO8(0x10),	/* FFERCA2TRAINLKRATIO1 */
		DRXJ_16TO8(0x10),	/* FFERCA2TRAINLKRATIO2 */
		DRXJ_16TO8(0x10),	/* FFERCA2TRAINLKRATIO3 */
		DRXJ_16TO8(0x20),	/* FFERCA2TRAINLKRATIO4 */
		DRXJ_16TO8(0x20),	/* FFERCA2TRAINLKRATIO5 */
		DRXJ_16TO8(0x20),	/* FFERCA2TRAINLKRATIO6 */
		DRXJ_16TO8(0x20),	/* FFERCA2TRAINLKRATIO7 */
		DRXJ_16TO8(0x20),	/* FFERCA2TRAINLKRATIO8 */
		DRXJ_16TO8(0x20),	/* FFERCA2TRAINLKRATIO9 */
		DRXJ_16TO8(0x10),	/* FFERCA2TRAINLKRATIO10 */
		DRXJ_16TO8(0x10),	/* FFERCA2TRAINLKRATIO11 */
		DRXJ_16TO8(0x10),	/* FFERCA2TRAINLKRATIO12 */
		DRXJ_16TO8(0x10),	/* FFERCA2DATALKRATIO1 */
		DRXJ_16TO8(0x10),	/* FFERCA2DATALKRATIO2 */
		DRXJ_16TO8(0x10),	/* FFERCA2DATALKRATIO3 */
		DRXJ_16TO8(0x20),	/* FFERCA2DATALKRATIO4 */
		DRXJ_16TO8(0x20),	/* FFERCA2DATALKRATIO5 */
		DRXJ_16TO8(0x20),	/* FFERCA2DATALKRATIO6 */
		DRXJ_16TO8(0x20),	/* FFERCA2DATALKRATIO7 */
		DRXJ_16TO8(0x20),	/* FFERCA2DATALKRATIO8 */
		DRXJ_16TO8(0x20),	/* FFERCA2DATALKRATIO9 */
		DRXJ_16TO8(0x10),	/* FFERCA2DATALKRATIO10 */
		DRXJ_16TO8(0x10),	/* FFERCA2DATALKRATIO11 */
		DRXJ_16TO8(0x10),	/* FFERCA2DATALKRATIO12 */
		DRXJ_16TO8(0x07),	/* FFEDDM1TRAINLKRATIO1 */
		DRXJ_16TO8(0x07),	/* FFEDDM1TRAINLKRATIO2 */
		DRXJ_16TO8(0x07),	/* FFEDDM1TRAINLKRATIO3 */
		DRXJ_16TO8(0x0e),	/* FFEDDM1TRAINLKRATIO4 */
		DRXJ_16TO8(0x0e),	/* FFEDDM1TRAINLKRATIO5 */
		DRXJ_16TO8(0x0e),	/* FFEDDM1TRAINLKRATIO6 */
		DRXJ_16TO8(0x0e),	/* FFEDDM1TRAINLKRATIO7 */
		DRXJ_16TO8(0x0e),	/* FFEDDM1TRAINLKRATIO8 */
		DRXJ_16TO8(0x0e),	/* FFEDDM1TRAINLKRATIO9 */
		DRXJ_16TO8(0x07),	/* FFEDDM1TRAINLKRATIO10 */
		DRXJ_16TO8(0x07),	/* FFEDDM1TRAINLKRATIO11 */
		DRXJ_16TO8(0x07),	/* FFEDDM1TRAINLKRATIO12 */
		DRXJ_16TO8(0x07),	/* FFEDDM1DATALKRATIO1 */
		DRXJ_16TO8(0x07),	/* FFEDDM1DATALKRATIO2 */
		DRXJ_16TO8(0x07),	/* FFEDDM1DATALKRATIO3 */
		DRXJ_16TO8(0x0e),	/* FFEDDM1DATALKRATIO4 */
		DRXJ_16TO8(0x0e),	/* FFEDDM1DATALKRATIO5 */
		DRXJ_16TO8(0x0e),	/* FFEDDM1DATALKRATIO6 */
		DRXJ_16TO8(0x0e),	/* FFEDDM1DATALKRATIO7 */
		DRXJ_16TO8(0x0e),	/* FFEDDM1DATALKRATIO8 */
		DRXJ_16TO8(0x0e),	/* FFEDDM1DATALKRATIO9 */
		DRXJ_16TO8(0x07),	/* FFEDDM1DATALKRATIO10 */
		DRXJ_16TO8(0x07),	/* FFEDDM1DATALKRATIO11 */
		DRXJ_16TO8(0x07),	/* FFEDDM1DATALKRATIO12 */
		DRXJ_16TO8(0x06),	/* FFEDDM2TRAINLKRATIO1 */
		DRXJ_16TO8(0x06),	/* FFEDDM2TRAINLKRATIO2 */
		DRXJ_16TO8(0x06),	/* FFEDDM2TRAINLKRATIO3 */
		DRXJ_16TO8(0x0c),	/* FFEDDM2TRAINLKRATIO4 */
		DRXJ_16TO8(0x0c),	/* FFEDDM2TRAINLKRATIO5 */
		DRXJ_16TO8(0x0c),	/* FFEDDM2TRAINLKRATIO6 */
		DRXJ_16TO8(0x0c),	/* FFEDDM2TRAINLKRATIO7 */
		DRXJ_16TO8(0x0c),	/* FFEDDM2TRAINLKRATIO8 */
		DRXJ_16TO8(0x0c),	/* FFEDDM2TRAINLKRATIO9 */
		DRXJ_16TO8(0x06),	/* FFEDDM2TRAINLKRATIO10 */
		DRXJ_16TO8(0x06),	/* FFEDDM2TRAINLKRATIO11 */
		DRXJ_16TO8(0x06),	/* FFEDDM2TRAINLKRATIO12 */
		DRXJ_16TO8(0x06),	/* FFEDDM2DATALKRATIO1 */
		DRXJ_16TO8(0x06),	/* FFEDDM2DATALKRATIO2 */
		DRXJ_16TO8(0x06),	/* FFEDDM2DATALKRATIO3 */
		DRXJ_16TO8(0x0c),	/* FFEDDM2DATALKRATIO4 */
		DRXJ_16TO8(0x0c),	/* FFEDDM2DATALKRATIO5 */
		DRXJ_16TO8(0x0c),	/* FFEDDM2DATALKRATIO6 */
		DRXJ_16TO8(0x0c),	/* FFEDDM2DATALKRATIO7 */
		DRXJ_16TO8(0x0c),	/* FFEDDM2DATALKRATIO8 */
		DRXJ_16TO8(0x0c),	/* FFEDDM2DATALKRATIO9 */
		DRXJ_16TO8(0x06),	/* FFEDDM2DATALKRATIO10 */
		DRXJ_16TO8(0x06),	/* FFEDDM2DATALKRATIO11 */
		DRXJ_16TO8(0x06),	/* FFEDDM2DATALKRATIO12 */
		DRXJ_16TO8(0x2020),	/* FIRTRAINGAIN1 */
		DRXJ_16TO8(0x2020),	/* FIRTRAINGAIN2 */
		DRXJ_16TO8(0x2020),	/* FIRTRAINGAIN3 */
		DRXJ_16TO8(0x4040),	/* FIRTRAINGAIN4 */
		DRXJ_16TO8(0x4040),	/* FIRTRAINGAIN5 */
		DRXJ_16TO8(0x4040),	/* FIRTRAINGAIN6 */
		DRXJ_16TO8(0x4040),	/* FIRTRAINGAIN7 */
		DRXJ_16TO8(0x4040),	/* FIRTRAINGAIN8 */
		DRXJ_16TO8(0x4040),	/* FIRTRAINGAIN9 */
		DRXJ_16TO8(0x2020),	/* FIRTRAINGAIN10 */
		DRXJ_16TO8(0x2020),	/* FIRTRAINGAIN11 */
		DRXJ_16TO8(0x2020),	/* FIRTRAINGAIN12 */
		DRXJ_16TO8(0x0808),	/* FIRRCA1GAIN1 */
		DRXJ_16TO8(0x0808),	/* FIRRCA1GAIN2 */
		DRXJ_16TO8(0x0808),	/* FIRRCA1GAIN3 */
		DRXJ_16TO8(0x1010),	/* FIRRCA1GAIN4 */
		DRXJ_16TO8(0x1010),	/* FIRRCA1GAIN5 */
		DRXJ_16TO8(0x1010),	/* FIRRCA1GAIN6 */
		DRXJ_16TO8(0x1010),	/* FIRRCA1GAIN7 */
		DRXJ_16TO8(0x1010)	/* FIRRCA1GAIN8 */
	पूर्ण;

	अटल स्थिर u8 vsb_ffe_leak_gain_ram1[] = अणु
		DRXJ_16TO8(0x1010),	/* FIRRCA1GAIN9 */
		DRXJ_16TO8(0x0808),	/* FIRRCA1GAIN10 */
		DRXJ_16TO8(0x0808),	/* FIRRCA1GAIN11 */
		DRXJ_16TO8(0x0808),	/* FIRRCA1GAIN12 */
		DRXJ_16TO8(0x0808),	/* FIRRCA2GAIN1 */
		DRXJ_16TO8(0x0808),	/* FIRRCA2GAIN2 */
		DRXJ_16TO8(0x0808),	/* FIRRCA2GAIN3 */
		DRXJ_16TO8(0x1010),	/* FIRRCA2GAIN4 */
		DRXJ_16TO8(0x1010),	/* FIRRCA2GAIN5 */
		DRXJ_16TO8(0x1010),	/* FIRRCA2GAIN6 */
		DRXJ_16TO8(0x1010),	/* FIRRCA2GAIN7 */
		DRXJ_16TO8(0x1010),	/* FIRRCA2GAIN8 */
		DRXJ_16TO8(0x1010),	/* FIRRCA2GAIN9 */
		DRXJ_16TO8(0x0808),	/* FIRRCA2GAIN10 */
		DRXJ_16TO8(0x0808),	/* FIRRCA2GAIN11 */
		DRXJ_16TO8(0x0808),	/* FIRRCA2GAIN12 */
		DRXJ_16TO8(0x0303),	/* FIRDDM1GAIN1 */
		DRXJ_16TO8(0x0303),	/* FIRDDM1GAIN2 */
		DRXJ_16TO8(0x0303),	/* FIRDDM1GAIN3 */
		DRXJ_16TO8(0x0606),	/* FIRDDM1GAIN4 */
		DRXJ_16TO8(0x0606),	/* FIRDDM1GAIN5 */
		DRXJ_16TO8(0x0606),	/* FIRDDM1GAIN6 */
		DRXJ_16TO8(0x0606),	/* FIRDDM1GAIN7 */
		DRXJ_16TO8(0x0606),	/* FIRDDM1GAIN8 */
		DRXJ_16TO8(0x0606),	/* FIRDDM1GAIN9 */
		DRXJ_16TO8(0x0303),	/* FIRDDM1GAIN10 */
		DRXJ_16TO8(0x0303),	/* FIRDDM1GAIN11 */
		DRXJ_16TO8(0x0303),	/* FIRDDM1GAIN12 */
		DRXJ_16TO8(0x0303),	/* FIRDDM2GAIN1 */
		DRXJ_16TO8(0x0303),	/* FIRDDM2GAIN2 */
		DRXJ_16TO8(0x0303),	/* FIRDDM2GAIN3 */
		DRXJ_16TO8(0x0505),	/* FIRDDM2GAIN4 */
		DRXJ_16TO8(0x0505),	/* FIRDDM2GAIN5 */
		DRXJ_16TO8(0x0505),	/* FIRDDM2GAIN6 */
		DRXJ_16TO8(0x0505),	/* FIRDDM2GAIN7 */
		DRXJ_16TO8(0x0505),	/* FIRDDM2GAIN8 */
		DRXJ_16TO8(0x0505),	/* FIRDDM2GAIN9 */
		DRXJ_16TO8(0x0303),	/* FIRDDM2GAIN10 */
		DRXJ_16TO8(0x0303),	/* FIRDDM2GAIN11 */
		DRXJ_16TO8(0x0303),	/* FIRDDM2GAIN12 */
		DRXJ_16TO8(0x001f),	/* DFETRAINLKRATIO */
		DRXJ_16TO8(0x01ff),	/* DFERCA1TRAINLKRATIO */
		DRXJ_16TO8(0x01ff),	/* DFERCA1DATALKRATIO */
		DRXJ_16TO8(0x004f),	/* DFERCA2TRAINLKRATIO */
		DRXJ_16TO8(0x004f),	/* DFERCA2DATALKRATIO */
		DRXJ_16TO8(0x01ff),	/* DFEDDM1TRAINLKRATIO */
		DRXJ_16TO8(0x01ff),	/* DFEDDM1DATALKRATIO */
		DRXJ_16TO8(0x0352),	/* DFEDDM2TRAINLKRATIO */
		DRXJ_16TO8(0x0352),	/* DFEDDM2DATALKRATIO */
		DRXJ_16TO8(0x0000),	/* DFETRAINGAIN */
		DRXJ_16TO8(0x2020),	/* DFERCA1GAIN */
		DRXJ_16TO8(0x1010),	/* DFERCA2GAIN */
		DRXJ_16TO8(0x1818),	/* DFEDDM1GAIN */
		DRXJ_16TO8(0x1212)	/* DFEDDM2GAIN */
	पूर्ण;

	dev_addr = demod->my_i2c_dev_addr;
	rc = drxdap_fasi_ग_लिखो_block(dev_addr, VSB_SYSCTRL_RAM0_FFETRAINLKRATIO1__A, माप(vsb_ffe_leak_gain_ram0), ((u8 *)vsb_ffe_leak_gain_ram0), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxdap_fasi_ग_लिखो_block(dev_addr, VSB_SYSCTRL_RAM1_FIRRCA1GAIN9__A, माप(vsb_ffe_leak_gain_ram1), ((u8 *)vsb_ffe_leak_gain_ram1), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*
* \पn पूर्णांक set_vsb()
* \मrief Set 8VSB demod.
* \param demod instance of demodulator.
* \लeturn पूर्णांक.
*
*/
अटल पूर्णांक set_vsb(काष्ठा drx_demod_instance *demod)
अणु
	काष्ठा i2c_device_addr *dev_addr = शून्य;
	पूर्णांक rc;
	काष्ठा drx_common_attr *common_attr = शून्य;
	काष्ठा drxjscu_cmd cmd_scu;
	काष्ठा drxj_data *ext_attr = शून्य;
	u16 cmd_result = 0;
	u16 cmd_param = 0;
	अटल स्थिर u8 vsb_taps_re[] = अणु
		DRXJ_16TO8(-2),	/* re0  */
		DRXJ_16TO8(4),	/* re1  */
		DRXJ_16TO8(1),	/* re2  */
		DRXJ_16TO8(-4),	/* re3  */
		DRXJ_16TO8(1),	/* re4  */
		DRXJ_16TO8(4),	/* re5  */
		DRXJ_16TO8(-3),	/* re6  */
		DRXJ_16TO8(-3),	/* re7  */
		DRXJ_16TO8(6),	/* re8  */
		DRXJ_16TO8(1),	/* re9  */
		DRXJ_16TO8(-9),	/* re10 */
		DRXJ_16TO8(3),	/* re11 */
		DRXJ_16TO8(12),	/* re12 */
		DRXJ_16TO8(-9),	/* re13 */
		DRXJ_16TO8(-15),	/* re14 */
		DRXJ_16TO8(17),	/* re15 */
		DRXJ_16TO8(19),	/* re16 */
		DRXJ_16TO8(-29),	/* re17 */
		DRXJ_16TO8(-22),	/* re18 */
		DRXJ_16TO8(45),	/* re19 */
		DRXJ_16TO8(25),	/* re20 */
		DRXJ_16TO8(-70),	/* re21 */
		DRXJ_16TO8(-28),	/* re22 */
		DRXJ_16TO8(111),	/* re23 */
		DRXJ_16TO8(30),	/* re24 */
		DRXJ_16TO8(-201),	/* re25 */
		DRXJ_16TO8(-31),	/* re26 */
		DRXJ_16TO8(629)	/* re27 */
	पूर्ण;

	dev_addr = demod->my_i2c_dev_addr;
	common_attr = (काष्ठा drx_common_attr *) demod->my_common_attr;
	ext_attr = (काष्ठा drxj_data *) demod->my_ext_attr;

	/* stop all comm_exec */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_COMM_EXEC__A, FEC_COMM_EXEC_STOP, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, VSB_COMM_EXEC__A, VSB_COMM_EXEC_STOP, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_FS_COMM_EXEC__A, IQM_FS_COMM_EXEC_STOP, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_FD_COMM_EXEC__A, IQM_FD_COMM_EXEC_STOP, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_RC_COMM_EXEC__A, IQM_RC_COMM_EXEC_STOP, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_RT_COMM_EXEC__A, IQM_RT_COMM_EXEC_STOP, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_CF_COMM_EXEC__A, IQM_CF_COMM_EXEC_STOP, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/* reset demodulator */
	cmd_scu.command = SCU_RAM_COMMAND_STANDARD_VSB
	    | SCU_RAM_COMMAND_CMD_DEMOD_RESET;
	cmd_scu.parameter_len = 0;
	cmd_scu.result_len = 1;
	cmd_scu.parameter = शून्य;
	cmd_scu.result = &cmd_result;
	rc = scu_command(dev_addr, &cmd_scu);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_AF_DCF_BYPASS__A, 1, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_FS_ADJ_SEL__A, IQM_FS_ADJ_SEL_B_VSB, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_RC_ADJ_SEL__A, IQM_RC_ADJ_SEL_B_VSB, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	ext_attr->iqm_rc_rate_ofs = 0x00AD0D79;
	rc = drxdap_fasi_ग_लिखो_reg32(dev_addr, IQM_RC_RATE_OFS_LO__A, ext_attr->iqm_rc_rate_ofs, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, VSB_TOP_CFAGC_GAINSHIFT__A, 4, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, VSB_TOP_CYGN1TRK__A, 1, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_RC_CROUT_ENA__A, 1, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_RC_STRETCH__A, 28, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_RT_ACTIVE__A, 0, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_CF_SYMMETRIC__A, 0, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_CF_MIDTAP__A, 3, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_CF_OUT_ENA__A, IQM_CF_OUT_ENA_VSB__M, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_CF_SCALE__A, 1393, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_CF_SCALE_SH__A, 0, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_CF_POW_MEAS_LEN__A, 1, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxdap_fasi_ग_लिखो_block(dev_addr, IQM_CF_TAP_RE0__A, माप(vsb_taps_re), ((u8 *)vsb_taps_re), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxdap_fasi_ग_लिखो_block(dev_addr, IQM_CF_TAP_IM0__A, माप(vsb_taps_re), ((u8 *)vsb_taps_re), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, VSB_TOP_BNTHRESH__A, 330, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण	/* set higher threshold */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, VSB_TOP_CLPLASTNUM__A, 90, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण	/* burst detection on   */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, VSB_TOP_SNRTH_RCA1__A, 0x0042, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण	/* drop thresholds by 1 dB */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, VSB_TOP_SNRTH_RCA2__A, 0x0053, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण	/* drop thresholds by 2 dB */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, VSB_TOP_EQCTRL__A, 0x1, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण	/* cma on               */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_GPIO__A, 0, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण	/* GPIO               */

	/* Initialize the FEC Subप्रणाली */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_TOP_ANNEX__A, FEC_TOP_ANNEX_D, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	अणु
		u16 fec_oc_snc_mode = 0;
		rc = drxj_dap_पढ़ो_reg16(dev_addr, FEC_OC_SNC_MODE__A, &fec_oc_snc_mode, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		/* output data even when not locked */
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_SNC_MODE__A, fec_oc_snc_mode | FEC_OC_SNC_MODE_UNLOCK_ENABLE__M, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
	पूर्ण

	/* set clip */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_AF_CLP_LEN__A, 0, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_AF_CLP_TH__A, 470, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_AF_SNS_LEN__A, 0, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, VSB_TOP_SNRTH_PT__A, 0xD4, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	/* no transparent, no A&C framing; parity is set in mpegoutput */
	अणु
		u16 fec_oc_reg_mode = 0;
		rc = drxj_dap_पढ़ो_reg16(dev_addr, FEC_OC_MODE__A, &fec_oc_reg_mode, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_MODE__A, fec_oc_reg_mode & (~(FEC_OC_MODE_TRANSPARENT__M | FEC_OC_MODE_CLEAR__M | FEC_OC_MODE_RETAIN_FRAMING__M)), 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_DI_TIMEOUT_LO__A, 0, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण	/* समयout counter क्रम restarting */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_DI_TIMEOUT_HI__A, 3, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_RS_MODE__A, 0, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण	/* bypass disabled */
	/* initialize RS packet error measurement parameters */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_RS_MEASUREMENT_PERIOD__A, FEC_RS_MEASUREMENT_PERIOD, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_RS_MEASUREMENT_PRESCALE__A, FEC_RS_MEASUREMENT_PRESCALE, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/* init measurement period of MER/SER */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, VSB_TOP_MEASUREMENT_PERIOD__A, VSB_TOP_MEASUREMENT_PERIOD, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxdap_fasi_ग_लिखो_reg32(dev_addr, SCU_RAM_FEC_ACCUM_CW_CORRECTED_LO__A, 0, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_FEC_MEAS_COUNT__A, 0, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_FEC_ACCUM_PKT_FAILURES__A, 0, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, VSB_TOP_CKGN1TRK__A, 128, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	/* B-Input to ADC, PGA+filter in standby */
	अगर (!ext_attr->has_lna) अणु
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_AF_AMUX__A, 0x02, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
	पूर्ण

	/* turn on IQMAF. It has to be in front of setAgc**() */
	rc = set_iqm_af(demod, true);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = adc_synchronization(demod);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = init_agc(demod);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = set_agc_अगर(demod, &(ext_attr->vsb_अगर_agc_cfg), false);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = set_agc_rf(demod, &(ext_attr->vsb_rf_agc_cfg), false);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	अणु
		/* TODO fix this, store a काष्ठा drxj_cfg_afe_gain काष्ठाure in काष्ठा drxj_data instead
		   of only the gain */
		काष्ठा drxj_cfg_afe_gain vsb_pga_cfg = अणु DRX_STANDARD_8VSB, 0 पूर्ण;

		vsb_pga_cfg.gain = ext_attr->vsb_pga_cfg;
		rc = ctrl_set_cfg_afe_gain(demod, &vsb_pga_cfg);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
	पूर्ण
	rc = ctrl_set_cfg_pre_saw(demod, &(ext_attr->vsb_pre_saw_cfg));
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/* Mpeg output has to be in front of FEC active */
	rc = set_mpegtei_handling(demod);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = bit_reverse_mpeg_output(demod);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = set_mpeg_start_width(demod);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	अणु
		/* TODO: move to set_standard after hardware reset value problem is solved */
		/* Configure initial MPEG output */
		काष्ठा drx_cfg_mpeg_output cfg_mpeg_output;

		स_नकल(&cfg_mpeg_output, &common_attr->mpeg_cfg, माप(cfg_mpeg_output));
		cfg_mpeg_output.enable_mpeg_output = true;

		rc = ctrl_set_cfg_mpeg_output(demod, &cfg_mpeg_output);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
	पूर्ण

	/* TBD: what parameters should be set */
	cmd_param = 0x00;	/* Default mode AGC on, etc */
	cmd_scu.command = SCU_RAM_COMMAND_STANDARD_VSB
	    | SCU_RAM_COMMAND_CMD_DEMOD_SET_PARAM;
	cmd_scu.parameter_len = 1;
	cmd_scu.result_len = 1;
	cmd_scu.parameter = &cmd_param;
	cmd_scu.result = &cmd_result;
	rc = scu_command(dev_addr, &cmd_scu);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, VSB_TOP_BEAGC_GAINSHIFT__A, 0x0004, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, VSB_TOP_SNRTH_PT__A, 0x00D2, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, VSB_TOP_SYSSMTRNCTRL__A, VSB_TOP_SYSSMTRNCTRL__PRE | VSB_TOP_SYSSMTRNCTRL_NCOTIMEOUTCNTEN__M, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, VSB_TOP_BEDETCTRL__A, 0x142, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, VSB_TOP_LBAGCREFLVL__A, 640, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, VSB_TOP_CYGN1ACQ__A, 4, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, VSB_TOP_CYGN1TRK__A, 2, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, VSB_TOP_CYGN2TRK__A, 3, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/* start demodulator */
	cmd_scu.command = SCU_RAM_COMMAND_STANDARD_VSB
	    | SCU_RAM_COMMAND_CMD_DEMOD_START;
	cmd_scu.parameter_len = 0;
	cmd_scu.result_len = 1;
	cmd_scu.parameter = शून्य;
	cmd_scu.result = &cmd_result;
	rc = scu_command(dev_addr, &cmd_scu);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_COMM_EXEC__A, IQM_COMM_EXEC_ACTIVE, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, VSB_COMM_EXEC__A, VSB_COMM_EXEC_ACTIVE, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_COMM_EXEC__A, FEC_COMM_EXEC_ACTIVE, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*
* \पn अटल लघु get_vsb_post_rs_pck_err(काष्ठा i2c_device_addr *dev_addr, u16 *PckErrs)
* \मrief Get the values of packet error in 8VSB mode
* \लeturn Error code
*/
अटल पूर्णांक get_vsb_post_rs_pck_err(काष्ठा i2c_device_addr *dev_addr,
				   u32 *pck_errs, u32 *pck_count)
अणु
	पूर्णांक rc;
	u16 data = 0;
	u16 period = 0;
	u16 prescale = 0;
	u16 packet_errors_mant = 0;
	u16 packet_errors_exp = 0;

	rc = drxj_dap_पढ़ो_reg16(dev_addr, FEC_RS_NR_FAILURES__A, &data, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	packet_errors_mant = data & FEC_RS_NR_FAILURES_FIXED_MANT__M;
	packet_errors_exp = (data & FEC_RS_NR_FAILURES_EXP__M)
	    >> FEC_RS_NR_FAILURES_EXP__B;
	period = FEC_RS_MEASUREMENT_PERIOD;
	prescale = FEC_RS_MEASUREMENT_PRESCALE;
	/* packet error rate = (error packet number) per second */
	/* 77.3 us is समय क्रम per packet */
	अगर (period * prescale == 0) अणु
		pr_err("error: period and/or prescale is zero!\n");
		वापस -EIO;
	पूर्ण
	*pck_errs = packet_errors_mant * (1 << packet_errors_exp);
	*pck_count = period * prescale * 77;

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*
* \पn अटल लघु GetVSBBer(काष्ठा i2c_device_addr *dev_addr, u32 *ber)
* \मrief Get the values of ber in VSB mode
* \लeturn Error code
*/
अटल पूर्णांक get_vs_bpost_viterbi_ber(काष्ठा i2c_device_addr *dev_addr,
				    u32 *ber, u32 *cnt)
अणु
	पूर्णांक rc;
	u16 data = 0;
	u16 period = 0;
	u16 prescale = 0;
	u16 bit_errors_mant = 0;
	u16 bit_errors_exp = 0;

	rc = drxj_dap_पढ़ो_reg16(dev_addr, FEC_RS_NR_BIT_ERRORS__A, &data, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	period = FEC_RS_MEASUREMENT_PERIOD;
	prescale = FEC_RS_MEASUREMENT_PRESCALE;

	bit_errors_mant = data & FEC_RS_NR_BIT_ERRORS_FIXED_MANT__M;
	bit_errors_exp = (data & FEC_RS_NR_BIT_ERRORS_EXP__M)
	    >> FEC_RS_NR_BIT_ERRORS_EXP__B;

	*cnt = period * prescale * 207 * ((bit_errors_exp > 2) ? 1 : 8);

	अगर (((bit_errors_mant << bit_errors_exp) >> 3) > 68700)
		*ber = (*cnt) * 26570;
	अन्यथा अणु
		अगर (period * prescale == 0) अणु
			pr_err("error: period and/or prescale is zero!\n");
			वापस -EIO;
		पूर्ण
		*ber = bit_errors_mant << ((bit_errors_exp > 2) ?
			(bit_errors_exp - 3) : bit_errors_exp);
	पूर्ण

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*
* \पn अटल लघु get_vs_bpre_viterbi_ber(काष्ठा i2c_device_addr *dev_addr, u32 *ber)
* \मrief Get the values of ber in VSB mode
* \लeturn Error code
*/
अटल पूर्णांक get_vs_bpre_viterbi_ber(काष्ठा i2c_device_addr *dev_addr,
				   u32 *ber, u32 *cnt)
अणु
	u16 data = 0;
	पूर्णांक rc;

	rc = drxj_dap_पढ़ो_reg16(dev_addr, VSB_TOP_NR_SYM_ERRS__A, &data, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		वापस -EIO;
	पूर्ण
	*ber = data;
	*cnt = VSB_TOP_MEASUREMENT_PERIOD * SYMBOLS_PER_SEGMENT;

	वापस 0;
पूर्ण

/*
* \पn अटल पूर्णांक get_vsbmer(काष्ठा i2c_device_addr *dev_addr, u16 *mer)
* \मrief Get the values of MER
* \लeturn Error code
*/
अटल पूर्णांक get_vsbmer(काष्ठा i2c_device_addr *dev_addr, u16 *mer)
अणु
	पूर्णांक rc;
	u16 data_hi = 0;

	rc = drxj_dap_पढ़ो_reg16(dev_addr, VSB_TOP_ERR_ENERGY_H__A, &data_hi, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	*mer =
	    (u16) (log1_बार100(21504) - log1_बार100((data_hi << 6) / 52));

	वापस 0;
rw_error:
	वापस rc;
पूर्ण


/*============================================================================*/
/*==                     END 8VSB DATAPATH FUNCTIONS                        ==*/
/*============================================================================*/

/*============================================================================*/
/*============================================================================*/
/*==                       QAM DATAPATH FUNCTIONS                           ==*/
/*============================================================================*/
/*============================================================================*/

/*
* \पn पूर्णांक घातer_करोwn_qam ()
* \मrief Powr करोwn QAM related blocks.
* \param demod instance of demodulator.
* \param channel poपूर्णांकer to channel data.
* \लeturn पूर्णांक.
*/
अटल पूर्णांक घातer_करोwn_qam(काष्ठा drx_demod_instance *demod, bool primary)
अणु
	काष्ठा drxjscu_cmd cmd_scu = अणु /* command      */ 0,
		/* parameter_len */ 0,
		/* result_len    */ 0,
		/* *parameter   */ शून्य,
		/* *result      */ शून्य
	पूर्ण;
	पूर्णांक rc;
	काष्ठा i2c_device_addr *dev_addr = demod->my_i2c_dev_addr;
	काष्ठा drx_cfg_mpeg_output cfg_mpeg_output;
	काष्ठा drx_common_attr *common_attr = demod->my_common_attr;
	u16 cmd_result = 0;

	/*
	   STOP demodulator
	   resets IQM, QAM and FEC HW blocks
	 */
	/* stop all comm_exec */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_COMM_EXEC__A, FEC_COMM_EXEC_STOP, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_COMM_EXEC__A, QAM_COMM_EXEC_STOP, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	cmd_scu.command = SCU_RAM_COMMAND_STANDARD_QAM |
	    SCU_RAM_COMMAND_CMD_DEMOD_STOP;
	cmd_scu.parameter_len = 0;
	cmd_scu.result_len = 1;
	cmd_scu.parameter = शून्य;
	cmd_scu.result = &cmd_result;
	rc = scu_command(dev_addr, &cmd_scu);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	अगर (primary) अणु
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_COMM_EXEC__A, IQM_COMM_EXEC_STOP, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = set_iqm_af(demod, false);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
	पूर्ण अन्यथा अणु
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_FS_COMM_EXEC__A, IQM_FS_COMM_EXEC_STOP, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_FD_COMM_EXEC__A, IQM_FD_COMM_EXEC_STOP, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_RC_COMM_EXEC__A, IQM_RC_COMM_EXEC_STOP, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_RT_COMM_EXEC__A, IQM_RT_COMM_EXEC_STOP, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_CF_COMM_EXEC__A, IQM_CF_COMM_EXEC_STOP, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
	पूर्ण

	स_नकल(&cfg_mpeg_output, &common_attr->mpeg_cfg, माप(cfg_mpeg_output));
	cfg_mpeg_output.enable_mpeg_output = false;

	rc = ctrl_set_cfg_mpeg_output(demod, &cfg_mpeg_output);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*============================================================================*/

/*
* \पn पूर्णांक set_qam_measurement ()
* \मrief Setup of the QAM Measuremnt पूर्णांकervals क्रम संकेत quality
* \param demod instance of demod.
* \param स्थिरellation current स्थिरellation.
* \लeturn पूर्णांक.
*
*  NOTE:
*  Take पूर्णांकo account that क्रम certain settings the errorcounters can overflow.
*  The implementation करोes not check this.
*
*  TODO: overriding the ext_attr->fec_bits_desired by स्थिरellation dependent
*  स्थिरants to get a measurement period of approx. 1 sec. Remove fec_bits_desired
*  field ?
*
*/
#अगर_अघोषित DRXJ_VSB_ONLY
अटल पूर्णांक
set_qam_measurement(काष्ठा drx_demod_instance *demod,
		    क्रमागत drx_modulation स्थिरellation, u32 symbol_rate)
अणु
	काष्ठा i2c_device_addr *dev_addr = शून्य;	/* device address क्रम I2C ग_लिखोs */
	काष्ठा drxj_data *ext_attr = शून्य;	/* Global data container क्रम DRXJ specअगरic data */
	पूर्णांक rc;
	u32 fec_bits_desired = 0;	/* BER accounting period */
	u16 fec_rs_plen = 0;	/* defines RS BER measurement period */
	u16 fec_rs_prescale = 0;	/* ReedSolomon Measurement Prescale */
	u32 fec_rs_period = 0;	/* Value क्रम corresponding I2C रेजिस्टर */
	u32 fec_rs_bit_cnt = 0;	/* Actual precise amount of bits */
	u32 fec_oc_snc_fail_period = 0;	/* Value क्रम corresponding I2C रेजिस्टर */
	u32 qam_vd_period = 0;	/* Value क्रम corresponding I2C रेजिस्टर */
	u32 qam_vd_bit_cnt = 0;	/* Actual precise amount of bits */
	u16 fec_vd_plen = 0;	/* no of trellis symbols: VD SER measur period */
	u16 qam_vd_prescale = 0;	/* Viterbi Measurement Prescale */

	dev_addr = demod->my_i2c_dev_addr;
	ext_attr = (काष्ठा drxj_data *) demod->my_ext_attr;

	fec_bits_desired = ext_attr->fec_bits_desired;
	fec_rs_prescale = ext_attr->fec_rs_prescale;

	चयन (स्थिरellation) अणु
	हाल DRX_CONSTELLATION_QAM16:
		fec_bits_desired = 4 * symbol_rate;
		अवरोध;
	हाल DRX_CONSTELLATION_QAM32:
		fec_bits_desired = 5 * symbol_rate;
		अवरोध;
	हाल DRX_CONSTELLATION_QAM64:
		fec_bits_desired = 6 * symbol_rate;
		अवरोध;
	हाल DRX_CONSTELLATION_QAM128:
		fec_bits_desired = 7 * symbol_rate;
		अवरोध;
	हाल DRX_CONSTELLATION_QAM256:
		fec_bits_desired = 8 * symbol_rate;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Parameters क्रम Reed-Solomon Decoder */
	/* fecrs_period = (पूर्णांक)उच्चमान(FEC_BITS_DESIRED/(fecrs_prescale*plen)) */
	/* rs_bit_cnt   = fecrs_period*fecrs_prescale*plen                  */
	/*     result is within 32 bit arithmetic ->                        */
	/*     no need क्रम mult or frac functions                           */

	/* TODO: use स्थिरant instead of calculation and हटाओ the fec_rs_plen in ext_attr */
	चयन (ext_attr->standard) अणु
	हाल DRX_STANDARD_ITU_A:
	हाल DRX_STANDARD_ITU_C:
		fec_rs_plen = 204 * 8;
		अवरोध;
	हाल DRX_STANDARD_ITU_B:
		fec_rs_plen = 128 * 7;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ext_attr->fec_rs_plen = fec_rs_plen;	/* क्रम getSigQual */
	fec_rs_bit_cnt = fec_rs_prescale * fec_rs_plen;	/* temp storage   */
	अगर (fec_rs_bit_cnt == 0) अणु
		pr_err("error: fec_rs_bit_cnt is zero!\n");
		वापस -EIO;
	पूर्ण
	fec_rs_period = fec_bits_desired / fec_rs_bit_cnt + 1;	/* उच्चमान */
	अगर (ext_attr->standard != DRX_STANDARD_ITU_B)
		fec_oc_snc_fail_period = fec_rs_period;

	/* limit to max 16 bit value (I2C रेजिस्टर width) अगर needed */
	अगर (fec_rs_period > 0xFFFF)
		fec_rs_period = 0xFFFF;

	/* ग_लिखो corresponding रेजिस्टरs */
	चयन (ext_attr->standard) अणु
	हाल DRX_STANDARD_ITU_A:
	हाल DRX_STANDARD_ITU_C:
		अवरोध;
	हाल DRX_STANDARD_ITU_B:
		चयन (स्थिरellation) अणु
		हाल DRX_CONSTELLATION_QAM64:
			fec_rs_period = 31581;
			fec_oc_snc_fail_period = 17932;
			अवरोध;
		हाल DRX_CONSTELLATION_QAM256:
			fec_rs_period = 45446;
			fec_oc_snc_fail_period = 25805;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_OC_SNC_FAIL_PERIOD__A, (u16)fec_oc_snc_fail_period, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_RS_MEASUREMENT_PERIOD__A, (u16)fec_rs_period, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_RS_MEASUREMENT_PRESCALE__A, fec_rs_prescale, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	ext_attr->fec_rs_period = (u16) fec_rs_period;
	ext_attr->fec_rs_prescale = fec_rs_prescale;
	rc = drxdap_fasi_ग_लिखो_reg32(dev_addr, SCU_RAM_FEC_ACCUM_CW_CORRECTED_LO__A, 0, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_FEC_MEAS_COUNT__A, 0, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_FEC_ACCUM_PKT_FAILURES__A, 0, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	अगर (ext_attr->standard == DRX_STANDARD_ITU_B) अणु
		/* Parameters क्रम Viterbi Decoder */
		/* qamvd_period = (पूर्णांक)उच्चमान(FEC_BITS_DESIRED/                      */
		/*                    (qamvd_prescale*plen*(qam_स्थिरellation+1))) */
		/* vd_bit_cnt   = qamvd_period*qamvd_prescale*plen                 */
		/*     result is within 32 bit arithmetic ->                       */
		/*     no need क्रम mult or frac functions                          */

		/* a(8 bit) * b(8 bit) = 16 bit result => mult32 not needed */
		fec_vd_plen = ext_attr->fec_vd_plen;
		qam_vd_prescale = ext_attr->qam_vd_prescale;
		qam_vd_bit_cnt = qam_vd_prescale * fec_vd_plen;	/* temp storage */

		चयन (स्थिरellation) अणु
		हाल DRX_CONSTELLATION_QAM64:
			/* a(16 bit) * b(4 bit) = 20 bit result => mult32 not needed */
			qam_vd_period =
			    qam_vd_bit_cnt * (QAM_TOP_CONSTELLATION_QAM64 + 1)
			    * (QAM_TOP_CONSTELLATION_QAM64 + 1);
			अवरोध;
		हाल DRX_CONSTELLATION_QAM256:
			/* a(16 bit) * b(5 bit) = 21 bit result => mult32 not needed */
			qam_vd_period =
			    qam_vd_bit_cnt * (QAM_TOP_CONSTELLATION_QAM256 + 1)
			    * (QAM_TOP_CONSTELLATION_QAM256 + 1);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अगर (qam_vd_period == 0) अणु
			pr_err("error: qam_vd_period is zero!\n");
			वापस -EIO;
		पूर्ण
		qam_vd_period = fec_bits_desired / qam_vd_period;
		/* limit to max 16 bit value (I2C रेजिस्टर width) अगर needed */
		अगर (qam_vd_period > 0xFFFF)
			qam_vd_period = 0xFFFF;

		/* a(16 bit) * b(16 bit) = 32 bit result => mult32 not needed */
		qam_vd_bit_cnt *= qam_vd_period;

		rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_VD_MEASUREMENT_PERIOD__A, (u16)qam_vd_period, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_VD_MEASUREMENT_PRESCALE__A, qam_vd_prescale, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		ext_attr->qam_vd_period = (u16) qam_vd_period;
		ext_attr->qam_vd_prescale = qam_vd_prescale;
	पूर्ण

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*============================================================================*/

/*
* \पn पूर्णांक set_qam16 ()
* \मrief QAM16 specअगरic setup
* \param demod instance of demod.
* \लeturn पूर्णांक.
*/
अटल पूर्णांक set_qam16(काष्ठा drx_demod_instance *demod)
अणु
	काष्ठा i2c_device_addr *dev_addr = demod->my_i2c_dev_addr;
	पूर्णांक rc;
	अटल स्थिर u8 qam_dq_qual_fun[] = अणु
		DRXJ_16TO8(2),	/* fun0  */
		DRXJ_16TO8(2),	/* fun1  */
		DRXJ_16TO8(2),	/* fun2  */
		DRXJ_16TO8(2),	/* fun3  */
		DRXJ_16TO8(3),	/* fun4  */
		DRXJ_16TO8(3),	/* fun5  */
	पूर्ण;
	अटल स्थिर u8 qam_eq_cma_rad[] = अणु
		DRXJ_16TO8(13517),	/* RAD0  */
		DRXJ_16TO8(13517),	/* RAD1  */
		DRXJ_16TO8(13517),	/* RAD2  */
		DRXJ_16TO8(13517),	/* RAD3  */
		DRXJ_16TO8(13517),	/* RAD4  */
		DRXJ_16TO8(13517),	/* RAD5  */
	पूर्ण;

	rc = drxdap_fasi_ग_लिखो_block(dev_addr, QAM_DQ_QUAL_FUN0__A, माप(qam_dq_qual_fun), ((u8 *)qam_dq_qual_fun), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxdap_fasi_ग_लिखो_block(dev_addr, SCU_RAM_QAM_EQ_CMA_RAD0__A, माप(qam_eq_cma_rad), ((u8 *)qam_eq_cma_rad), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_RTH__A, 140, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_FTH__A, 50, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_PTH__A, 120, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_QTH__A, 230, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_CTH__A, 95, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_MTH__A, 105, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_RATE_LIM__A, 40, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_FREQ_LIM__A, 56, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_COUNT_LIM__A, 3, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_MEDIAN_AV_MULT__A, 16, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_RADIUS_AV_LIMIT__A, 220, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_LCAVG_OFFSET1__A, 25, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_LCAVG_OFFSET2__A, 6, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_LCAVG_OFFSET3__A, (u16)(-24), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_LCAVG_OFFSET4__A, (u16)(-65), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_LCAVG_OFFSET5__A, (u16)(-127), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CA_FINE__A, 15, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CA_COARSE__A, 40, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CP_FINE__A, 2, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CP_MEDIUM__A, 20, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CP_COARSE__A, 255, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CI_FINE__A, 2, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CI_MEDIUM__A, 10, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CI_COARSE__A, 50, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_EP_FINE__A, 12, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_EP_MEDIUM__A, 24, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_EP_COARSE__A, 24, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_EI_FINE__A, 12, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_EI_MEDIUM__A, 16, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_EI_COARSE__A, 16, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CF_FINE__A, 16, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CF_MEDIUM__A, 32, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CF_COARSE__A, 240, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CF1_FINE__A, 5, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CF1_MEDIUM__A, 15, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CF1_COARSE__A, 32, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_SL_SIG_POWER__A, 40960, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*============================================================================*/

/*
* \पn पूर्णांक set_qam32 ()
* \मrief QAM32 specअगरic setup
* \param demod instance of demod.
* \लeturn पूर्णांक.
*/
अटल पूर्णांक set_qam32(काष्ठा drx_demod_instance *demod)
अणु
	काष्ठा i2c_device_addr *dev_addr = demod->my_i2c_dev_addr;
	पूर्णांक rc;
	अटल स्थिर u8 qam_dq_qual_fun[] = अणु
		DRXJ_16TO8(3),	/* fun0  */
		DRXJ_16TO8(3),	/* fun1  */
		DRXJ_16TO8(3),	/* fun2  */
		DRXJ_16TO8(3),	/* fun3  */
		DRXJ_16TO8(4),	/* fun4  */
		DRXJ_16TO8(4),	/* fun5  */
	पूर्ण;
	अटल स्थिर u8 qam_eq_cma_rad[] = अणु
		DRXJ_16TO8(6707),	/* RAD0  */
		DRXJ_16TO8(6707),	/* RAD1  */
		DRXJ_16TO8(6707),	/* RAD2  */
		DRXJ_16TO8(6707),	/* RAD3  */
		DRXJ_16TO8(6707),	/* RAD4  */
		DRXJ_16TO8(6707),	/* RAD5  */
	पूर्ण;

	rc = drxdap_fasi_ग_लिखो_block(dev_addr, QAM_DQ_QUAL_FUN0__A, माप(qam_dq_qual_fun), ((u8 *)qam_dq_qual_fun), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxdap_fasi_ग_लिखो_block(dev_addr, SCU_RAM_QAM_EQ_CMA_RAD0__A, माप(qam_eq_cma_rad), ((u8 *)qam_eq_cma_rad), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_RTH__A, 90, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_FTH__A, 50, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_PTH__A, 100, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_QTH__A, 170, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_CTH__A, 80, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_MTH__A, 100, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_RATE_LIM__A, 40, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_FREQ_LIM__A, 56, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_COUNT_LIM__A, 3, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_MEDIAN_AV_MULT__A, 12, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_RADIUS_AV_LIMIT__A, 140, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_LCAVG_OFFSET1__A, (u16)(-8), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_LCAVG_OFFSET2__A, (u16)(-16), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_LCAVG_OFFSET3__A, (u16)(-26), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_LCAVG_OFFSET4__A, (u16)(-56), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_LCAVG_OFFSET5__A, (u16)(-86), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CA_FINE__A, 15, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CA_COARSE__A, 40, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CP_FINE__A, 2, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CP_MEDIUM__A, 20, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CP_COARSE__A, 255, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CI_FINE__A, 2, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CI_MEDIUM__A, 10, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CI_COARSE__A, 50, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_EP_FINE__A, 12, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_EP_MEDIUM__A, 24, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_EP_COARSE__A, 24, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_EI_FINE__A, 12, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_EI_MEDIUM__A, 16, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_EI_COARSE__A, 16, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CF_FINE__A, 16, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CF_MEDIUM__A, 32, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CF_COARSE__A, 176, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CF1_FINE__A, 5, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CF1_MEDIUM__A, 15, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CF1_COARSE__A, 8, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_SL_SIG_POWER__A, 20480, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*============================================================================*/

/*
* \पn पूर्णांक set_qam64 ()
* \मrief QAM64 specअगरic setup
* \param demod instance of demod.
* \लeturn पूर्णांक.
*/
अटल पूर्णांक set_qam64(काष्ठा drx_demod_instance *demod)
अणु
	काष्ठा i2c_device_addr *dev_addr = demod->my_i2c_dev_addr;
	पूर्णांक rc;
	अटल स्थिर u8 qam_dq_qual_fun[] = अणु
		/* this is hw reset value. no necessary to re-ग_लिखो */
		DRXJ_16TO8(4),	/* fun0  */
		DRXJ_16TO8(4),	/* fun1  */
		DRXJ_16TO8(4),	/* fun2  */
		DRXJ_16TO8(4),	/* fun3  */
		DRXJ_16TO8(6),	/* fun4  */
		DRXJ_16TO8(6),	/* fun5  */
	पूर्ण;
	अटल स्थिर u8 qam_eq_cma_rad[] = अणु
		DRXJ_16TO8(13336),	/* RAD0  */
		DRXJ_16TO8(12618),	/* RAD1  */
		DRXJ_16TO8(11988),	/* RAD2  */
		DRXJ_16TO8(13809),	/* RAD3  */
		DRXJ_16TO8(13809),	/* RAD4  */
		DRXJ_16TO8(15609),	/* RAD5  */
	पूर्ण;

	rc = drxdap_fasi_ग_लिखो_block(dev_addr, QAM_DQ_QUAL_FUN0__A, माप(qam_dq_qual_fun), ((u8 *)qam_dq_qual_fun), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxdap_fasi_ग_लिखो_block(dev_addr, SCU_RAM_QAM_EQ_CMA_RAD0__A, माप(qam_eq_cma_rad), ((u8 *)qam_eq_cma_rad), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_RTH__A, 105, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_FTH__A, 60, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_PTH__A, 100, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_QTH__A, 195, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_CTH__A, 80, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_MTH__A, 84, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_RATE_LIM__A, 40, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_FREQ_LIM__A, 32, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_COUNT_LIM__A, 3, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_MEDIAN_AV_MULT__A, 12, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_RADIUS_AV_LIMIT__A, 141, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_LCAVG_OFFSET1__A, 7, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_LCAVG_OFFSET2__A, 0, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_LCAVG_OFFSET3__A, (u16)(-15), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_LCAVG_OFFSET4__A, (u16)(-45), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_LCAVG_OFFSET5__A, (u16)(-80), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CA_FINE__A, 15, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CA_COARSE__A, 40, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CP_FINE__A, 2, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CP_MEDIUM__A, 30, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CP_COARSE__A, 255, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CI_FINE__A, 2, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CI_MEDIUM__A, 15, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CI_COARSE__A, 80, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_EP_FINE__A, 12, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_EP_MEDIUM__A, 24, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_EP_COARSE__A, 24, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_EI_FINE__A, 12, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_EI_MEDIUM__A, 16, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_EI_COARSE__A, 16, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CF_FINE__A, 16, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CF_MEDIUM__A, 48, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CF_COARSE__A, 160, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CF1_FINE__A, 5, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CF1_MEDIUM__A, 15, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CF1_COARSE__A, 32, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_SL_SIG_POWER__A, 43008, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*============================================================================*/

/*
* \पn पूर्णांक set_qam128 ()
* \मrief QAM128 specअगरic setup
* \param demod: instance of demod.
* \लeturn पूर्णांक.
*/
अटल पूर्णांक set_qam128(काष्ठा drx_demod_instance *demod)
अणु
	काष्ठा i2c_device_addr *dev_addr = demod->my_i2c_dev_addr;
	पूर्णांक rc;
	अटल स्थिर u8 qam_dq_qual_fun[] = अणु
		DRXJ_16TO8(6),	/* fun0  */
		DRXJ_16TO8(6),	/* fun1  */
		DRXJ_16TO8(6),	/* fun2  */
		DRXJ_16TO8(6),	/* fun3  */
		DRXJ_16TO8(9),	/* fun4  */
		DRXJ_16TO8(9),	/* fun5  */
	पूर्ण;
	अटल स्थिर u8 qam_eq_cma_rad[] = अणु
		DRXJ_16TO8(6164),	/* RAD0  */
		DRXJ_16TO8(6598),	/* RAD1  */
		DRXJ_16TO8(6394),	/* RAD2  */
		DRXJ_16TO8(6409),	/* RAD3  */
		DRXJ_16TO8(6656),	/* RAD4  */
		DRXJ_16TO8(7238),	/* RAD5  */
	पूर्ण;

	rc = drxdap_fasi_ग_लिखो_block(dev_addr, QAM_DQ_QUAL_FUN0__A, माप(qam_dq_qual_fun), ((u8 *)qam_dq_qual_fun), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxdap_fasi_ग_लिखो_block(dev_addr, SCU_RAM_QAM_EQ_CMA_RAD0__A, माप(qam_eq_cma_rad), ((u8 *)qam_eq_cma_rad), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_RTH__A, 50, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_FTH__A, 60, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_PTH__A, 100, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_QTH__A, 140, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_CTH__A, 80, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_MTH__A, 100, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_RATE_LIM__A, 40, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_FREQ_LIM__A, 32, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_COUNT_LIM__A, 3, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_MEDIAN_AV_MULT__A, 8, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_RADIUS_AV_LIMIT__A, 65, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_LCAVG_OFFSET1__A, 5, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_LCAVG_OFFSET2__A, 3, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_LCAVG_OFFSET3__A, (u16)(-1), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_LCAVG_OFFSET4__A, 12, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_LCAVG_OFFSET5__A, (u16)(-23), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CA_FINE__A, 15, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CA_COARSE__A, 40, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CP_FINE__A, 2, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CP_MEDIUM__A, 40, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CP_COARSE__A, 255, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CI_FINE__A, 2, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CI_MEDIUM__A, 20, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CI_COARSE__A, 80, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_EP_FINE__A, 12, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_EP_MEDIUM__A, 24, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_EP_COARSE__A, 24, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_EI_FINE__A, 12, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_EI_MEDIUM__A, 16, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_EI_COARSE__A, 16, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CF_FINE__A, 16, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CF_MEDIUM__A, 32, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CF_COARSE__A, 144, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CF1_FINE__A, 5, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CF1_MEDIUM__A, 15, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CF1_COARSE__A, 16, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_SL_SIG_POWER__A, 20992, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*============================================================================*/

/*
* \पn पूर्णांक set_qam256 ()
* \मrief QAM256 specअगरic setup
* \param demod: instance of demod.
* \लeturn पूर्णांक.
*/
अटल पूर्णांक set_qam256(काष्ठा drx_demod_instance *demod)
अणु
	काष्ठा i2c_device_addr *dev_addr = demod->my_i2c_dev_addr;
	पूर्णांक rc;
	अटल स्थिर u8 qam_dq_qual_fun[] = अणु
		DRXJ_16TO8(8),	/* fun0  */
		DRXJ_16TO8(8),	/* fun1  */
		DRXJ_16TO8(8),	/* fun2  */
		DRXJ_16TO8(8),	/* fun3  */
		DRXJ_16TO8(12),	/* fun4  */
		DRXJ_16TO8(12),	/* fun5  */
	पूर्ण;
	अटल स्थिर u8 qam_eq_cma_rad[] = अणु
		DRXJ_16TO8(12345),	/* RAD0  */
		DRXJ_16TO8(12345),	/* RAD1  */
		DRXJ_16TO8(13626),	/* RAD2  */
		DRXJ_16TO8(12931),	/* RAD3  */
		DRXJ_16TO8(14719),	/* RAD4  */
		DRXJ_16TO8(15356),	/* RAD5  */
	पूर्ण;

	rc = drxdap_fasi_ग_लिखो_block(dev_addr, QAM_DQ_QUAL_FUN0__A, माप(qam_dq_qual_fun), ((u8 *)qam_dq_qual_fun), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxdap_fasi_ग_लिखो_block(dev_addr, SCU_RAM_QAM_EQ_CMA_RAD0__A, माप(qam_eq_cma_rad), ((u8 *)qam_eq_cma_rad), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_RTH__A, 50, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_FTH__A, 60, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_PTH__A, 100, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_QTH__A, 150, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_CTH__A, 80, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_MTH__A, 110, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_RATE_LIM__A, 40, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_FREQ_LIM__A, 16, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_COUNT_LIM__A, 3, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_MEDIAN_AV_MULT__A, 8, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_RADIUS_AV_LIMIT__A, 74, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_LCAVG_OFFSET1__A, 18, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_LCAVG_OFFSET2__A, 13, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_LCAVG_OFFSET3__A, 7, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_LCAVG_OFFSET4__A, 0, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_LCAVG_OFFSET5__A, (u16)(-8), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CA_FINE__A, 15, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CA_COARSE__A, 40, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CP_FINE__A, 2, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CP_MEDIUM__A, 50, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CP_COARSE__A, 255, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CI_FINE__A, 2, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CI_MEDIUM__A, 25, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CI_COARSE__A, 80, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_EP_FINE__A, 12, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_EP_MEDIUM__A, 24, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_EP_COARSE__A, 24, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_EI_FINE__A, 12, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_EI_MEDIUM__A, 16, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_EI_COARSE__A, 16, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CF_FINE__A, 16, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CF_MEDIUM__A, 48, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CF_COARSE__A, 80, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CF1_FINE__A, 5, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CF1_MEDIUM__A, 15, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_LC_CF1_COARSE__A, 16, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_SL_SIG_POWER__A, 43520, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*============================================================================*/
#घोषणा QAM_SET_OP_ALL 0x1
#घोषणा QAM_SET_OP_CONSTELLATION 0x2
#घोषणा QAM_SET_OP_SPECTRUM 0X4

/*
* \पn पूर्णांक set_qam ()
* \मrief Set QAM demod.
* \param demod:   instance of demod.
* \param channel: poपूर्णांकer to channel data.
* \लeturn पूर्णांक.
*/
अटल पूर्णांक
set_qam(काष्ठा drx_demod_instance *demod,
	काष्ठा drx_channel *channel, s32 tuner_freq_offset, u32 op)
अणु
	काष्ठा i2c_device_addr *dev_addr = शून्य;
	काष्ठा drxj_data *ext_attr = शून्य;
	काष्ठा drx_common_attr *common_attr = शून्य;
	पूर्णांक rc;
	u32 adc_frequency = 0;
	u32 iqm_rc_rate = 0;
	u16 cmd_result = 0;
	u16 lc_symbol_freq = 0;
	u16 iqm_rc_stretch = 0;
	u16 set_env_parameters = 0;
	u16 set_param_parameters[2] = अणु 0 पूर्ण;
	काष्ठा drxjscu_cmd cmd_scu = अणु /* command      */ 0,
		/* parameter_len */ 0,
		/* result_len    */ 0,
		/* parameter    */ शून्य,
		/* result       */ शून्य
	पूर्ण;
	अटल स्थिर u8 qam_a_taps[] = अणु
		DRXJ_16TO8(-1),	/* re0  */
		DRXJ_16TO8(1),	/* re1  */
		DRXJ_16TO8(1),	/* re2  */
		DRXJ_16TO8(-1),	/* re3  */
		DRXJ_16TO8(-1),	/* re4  */
		DRXJ_16TO8(2),	/* re5  */
		DRXJ_16TO8(1),	/* re6  */
		DRXJ_16TO8(-2),	/* re7  */
		DRXJ_16TO8(0),	/* re8  */
		DRXJ_16TO8(3),	/* re9  */
		DRXJ_16TO8(-1),	/* re10 */
		DRXJ_16TO8(-3),	/* re11 */
		DRXJ_16TO8(4),	/* re12 */
		DRXJ_16TO8(1),	/* re13 */
		DRXJ_16TO8(-8),	/* re14 */
		DRXJ_16TO8(4),	/* re15 */
		DRXJ_16TO8(13),	/* re16 */
		DRXJ_16TO8(-13),	/* re17 */
		DRXJ_16TO8(-19),	/* re18 */
		DRXJ_16TO8(28),	/* re19 */
		DRXJ_16TO8(25),	/* re20 */
		DRXJ_16TO8(-53),	/* re21 */
		DRXJ_16TO8(-31),	/* re22 */
		DRXJ_16TO8(96),	/* re23 */
		DRXJ_16TO8(37),	/* re24 */
		DRXJ_16TO8(-190),	/* re25 */
		DRXJ_16TO8(-40),	/* re26 */
		DRXJ_16TO8(619)	/* re27 */
	पूर्ण;
	अटल स्थिर u8 qam_b64_taps[] = अणु
		DRXJ_16TO8(0),	/* re0  */
		DRXJ_16TO8(-2),	/* re1  */
		DRXJ_16TO8(1),	/* re2  */
		DRXJ_16TO8(2),	/* re3  */
		DRXJ_16TO8(-2),	/* re4  */
		DRXJ_16TO8(0),	/* re5  */
		DRXJ_16TO8(4),	/* re6  */
		DRXJ_16TO8(-2),	/* re7  */
		DRXJ_16TO8(-4),	/* re8  */
		DRXJ_16TO8(4),	/* re9  */
		DRXJ_16TO8(3),	/* re10 */
		DRXJ_16TO8(-6),	/* re11 */
		DRXJ_16TO8(0),	/* re12 */
		DRXJ_16TO8(6),	/* re13 */
		DRXJ_16TO8(-5),	/* re14 */
		DRXJ_16TO8(-3),	/* re15 */
		DRXJ_16TO8(11),	/* re16 */
		DRXJ_16TO8(-4),	/* re17 */
		DRXJ_16TO8(-19),	/* re18 */
		DRXJ_16TO8(19),	/* re19 */
		DRXJ_16TO8(28),	/* re20 */
		DRXJ_16TO8(-45),	/* re21 */
		DRXJ_16TO8(-36),	/* re22 */
		DRXJ_16TO8(90),	/* re23 */
		DRXJ_16TO8(42),	/* re24 */
		DRXJ_16TO8(-185),	/* re25 */
		DRXJ_16TO8(-46),	/* re26 */
		DRXJ_16TO8(614)	/* re27 */
	पूर्ण;
	अटल स्थिर u8 qam_b256_taps[] = अणु
		DRXJ_16TO8(-2),	/* re0  */
		DRXJ_16TO8(4),	/* re1  */
		DRXJ_16TO8(1),	/* re2  */
		DRXJ_16TO8(-4),	/* re3  */
		DRXJ_16TO8(0),	/* re4  */
		DRXJ_16TO8(4),	/* re5  */
		DRXJ_16TO8(-2),	/* re6  */
		DRXJ_16TO8(-4),	/* re7  */
		DRXJ_16TO8(5),	/* re8  */
		DRXJ_16TO8(2),	/* re9  */
		DRXJ_16TO8(-8),	/* re10 */
		DRXJ_16TO8(2),	/* re11 */
		DRXJ_16TO8(11),	/* re12 */
		DRXJ_16TO8(-8),	/* re13 */
		DRXJ_16TO8(-15),	/* re14 */
		DRXJ_16TO8(16),	/* re15 */
		DRXJ_16TO8(19),	/* re16 */
		DRXJ_16TO8(-27),	/* re17 */
		DRXJ_16TO8(-22),	/* re18 */
		DRXJ_16TO8(44),	/* re19 */
		DRXJ_16TO8(26),	/* re20 */
		DRXJ_16TO8(-69),	/* re21 */
		DRXJ_16TO8(-28),	/* re22 */
		DRXJ_16TO8(110),	/* re23 */
		DRXJ_16TO8(31),	/* re24 */
		DRXJ_16TO8(-201),	/* re25 */
		DRXJ_16TO8(-32),	/* re26 */
		DRXJ_16TO8(628)	/* re27 */
	पूर्ण;
	अटल स्थिर u8 qam_c_taps[] = अणु
		DRXJ_16TO8(-3),	/* re0  */
		DRXJ_16TO8(3),	/* re1  */
		DRXJ_16TO8(2),	/* re2  */
		DRXJ_16TO8(-4),	/* re3  */
		DRXJ_16TO8(0),	/* re4  */
		DRXJ_16TO8(4),	/* re5  */
		DRXJ_16TO8(-1),	/* re6  */
		DRXJ_16TO8(-4),	/* re7  */
		DRXJ_16TO8(3),	/* re8  */
		DRXJ_16TO8(3),	/* re9  */
		DRXJ_16TO8(-5),	/* re10 */
		DRXJ_16TO8(0),	/* re11 */
		DRXJ_16TO8(9),	/* re12 */
		DRXJ_16TO8(-4),	/* re13 */
		DRXJ_16TO8(-12),	/* re14 */
		DRXJ_16TO8(10),	/* re15 */
		DRXJ_16TO8(16),	/* re16 */
		DRXJ_16TO8(-21),	/* re17 */
		DRXJ_16TO8(-20),	/* re18 */
		DRXJ_16TO8(37),	/* re19 */
		DRXJ_16TO8(25),	/* re20 */
		DRXJ_16TO8(-62),	/* re21 */
		DRXJ_16TO8(-28),	/* re22 */
		DRXJ_16TO8(105),	/* re23 */
		DRXJ_16TO8(31),	/* re24 */
		DRXJ_16TO8(-197),	/* re25 */
		DRXJ_16TO8(-33),	/* re26 */
		DRXJ_16TO8(626)	/* re27 */
	पूर्ण;

	dev_addr = demod->my_i2c_dev_addr;
	ext_attr = (काष्ठा drxj_data *) demod->my_ext_attr;
	common_attr = (काष्ठा drx_common_attr *) demod->my_common_attr;

	अगर ((op & QAM_SET_OP_ALL) || (op & QAM_SET_OP_CONSTELLATION)) अणु
		अगर (ext_attr->standard == DRX_STANDARD_ITU_B) अणु
			चयन (channel->स्थिरellation) अणु
			हाल DRX_CONSTELLATION_QAM256:
				iqm_rc_rate = 0x00AE3562;
				lc_symbol_freq =
				    QAM_LC_SYMBOL_FREQ_FREQ_QAM_B_256;
				channel->symbolrate = 5360537;
				iqm_rc_stretch = IQM_RC_STRETCH_QAM_B_256;
				अवरोध;
			हाल DRX_CONSTELLATION_QAM64:
				iqm_rc_rate = 0x00C05A0E;
				lc_symbol_freq = 409;
				channel->symbolrate = 5056941;
				iqm_rc_stretch = IQM_RC_STRETCH_QAM_B_64;
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			adc_frequency = (common_attr->sys_घड़ी_freq * 1000) / 3;
			अगर (channel->symbolrate == 0) अणु
				pr_err("error: channel symbolrate is zero!\n");
				वापस -EIO;
			पूर्ण
			iqm_rc_rate =
			    (adc_frequency / channel->symbolrate) * (1 << 21) +
			    (frac28
			     ((adc_frequency % channel->symbolrate),
			      channel->symbolrate) >> 7) - (1 << 23);
			lc_symbol_freq =
			    (u16) (frac28
				     (channel->symbolrate +
				      (adc_frequency >> 13),
				      adc_frequency) >> 16);
			अगर (lc_symbol_freq > 511)
				lc_symbol_freq = 511;

			iqm_rc_stretch = 21;
		पूर्ण

		अगर (ext_attr->standard == DRX_STANDARD_ITU_A) अणु
			set_env_parameters = QAM_TOP_ANNEX_A;	/* annex             */
			set_param_parameters[0] = channel->स्थिरellation;	/* स्थिरellation     */
			set_param_parameters[1] = DRX_INTERLEAVEMODE_I12_J17;	/* पूर्णांकerleave mode   */
		पूर्ण अन्यथा अगर (ext_attr->standard == DRX_STANDARD_ITU_B) अणु
			set_env_parameters = QAM_TOP_ANNEX_B;	/* annex             */
			set_param_parameters[0] = channel->स्थिरellation;	/* स्थिरellation     */
			set_param_parameters[1] = channel->पूर्णांकerleavemode;	/* पूर्णांकerleave mode   */
		पूर्ण अन्यथा अगर (ext_attr->standard == DRX_STANDARD_ITU_C) अणु
			set_env_parameters = QAM_TOP_ANNEX_C;	/* annex             */
			set_param_parameters[0] = channel->स्थिरellation;	/* स्थिरellation     */
			set_param_parameters[1] = DRX_INTERLEAVEMODE_I12_J17;	/* पूर्णांकerleave mode   */
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (op & QAM_SET_OP_ALL) अणु
		/*
		   STEP 1: reset demodulator
		   resets IQM, QAM and FEC HW blocks
		   resets SCU variables
		 */
		/* stop all comm_exec */
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_COMM_EXEC__A, FEC_COMM_EXEC_STOP, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_COMM_EXEC__A, QAM_COMM_EXEC_STOP, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_FS_COMM_EXEC__A, IQM_FS_COMM_EXEC_STOP, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_FD_COMM_EXEC__A, IQM_FD_COMM_EXEC_STOP, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_RC_COMM_EXEC__A, IQM_RC_COMM_EXEC_STOP, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_RT_COMM_EXEC__A, IQM_RT_COMM_EXEC_STOP, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_CF_COMM_EXEC__A, IQM_CF_COMM_EXEC_STOP, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण

		cmd_scu.command = SCU_RAM_COMMAND_STANDARD_QAM |
		    SCU_RAM_COMMAND_CMD_DEMOD_RESET;
		cmd_scu.parameter_len = 0;
		cmd_scu.result_len = 1;
		cmd_scu.parameter = शून्य;
		cmd_scu.result = &cmd_result;
		rc = scu_command(dev_addr, &cmd_scu);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
	पूर्ण

	अगर ((op & QAM_SET_OP_ALL) || (op & QAM_SET_OP_CONSTELLATION)) अणु
		/*
		   STEP 2: configure demodulator
		   -set env
		   -set params (resets IQM,QAM,FEC HW; initializes some SCU variables )
		 */
		cmd_scu.command = SCU_RAM_COMMAND_STANDARD_QAM |
		    SCU_RAM_COMMAND_CMD_DEMOD_SET_ENV;
		cmd_scu.parameter_len = 1;
		cmd_scu.result_len = 1;
		cmd_scu.parameter = &set_env_parameters;
		cmd_scu.result = &cmd_result;
		rc = scu_command(dev_addr, &cmd_scu);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण

		cmd_scu.command = SCU_RAM_COMMAND_STANDARD_QAM |
		    SCU_RAM_COMMAND_CMD_DEMOD_SET_PARAM;
		cmd_scu.parameter_len = 2;
		cmd_scu.result_len = 1;
		cmd_scu.parameter = set_param_parameters;
		cmd_scu.result = &cmd_result;
		rc = scu_command(dev_addr, &cmd_scu);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		/* set symbol rate */
		rc = drxdap_fasi_ग_लिखो_reg32(dev_addr, IQM_RC_RATE_OFS_LO__A, iqm_rc_rate, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		ext_attr->iqm_rc_rate_ofs = iqm_rc_rate;
		rc = set_qam_measurement(demod, channel->स्थिरellation, channel->symbolrate);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
	पूर्ण
	/* STEP 3: enable the प्रणाली in a mode where the ADC provides valid संकेत
	   setup स्थिरellation independent रेजिस्टरs */
	/* from qam_cmd.py script (qam_driver_b) */
	/* TODO: हटाओ re-ग_लिखोs of HW reset values */
	अगर ((op & QAM_SET_OP_ALL) || (op & QAM_SET_OP_SPECTRUM)) अणु
		rc = set_frequency(demod, channel, tuner_freq_offset);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
	पूर्ण

	अगर ((op & QAM_SET_OP_ALL) || (op & QAM_SET_OP_CONSTELLATION)) अणु

		rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_LC_SYMBOL_FREQ__A, lc_symbol_freq, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_RC_STRETCH__A, iqm_rc_stretch, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
	पूर्ण

	अगर (op & QAM_SET_OP_ALL) अणु
		अगर (!ext_attr->has_lna) अणु
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_AF_AMUX__A, 0x02, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_CF_SYMMETRIC__A, 0, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_CF_MIDTAP__A, 3, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_CF_OUT_ENA__A, IQM_CF_OUT_ENA_QAM__M, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण

		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_WR_RSV_0__A, 0x5f, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण	/* scu temporary shut करोwn agc */

		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_AF_SYNC_SEL__A, 3, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_AF_CLP_LEN__A, 0, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_AF_CLP_TH__A, 448, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_AF_SNS_LEN__A, 0, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_AF_PDREF__A, 4, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_AF_STDBY__A, 0x10, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_AF_PGA_GAIN__A, 11, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण

		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_CF_POW_MEAS_LEN__A, 1, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_CF_SCALE_SH__A, IQM_CF_SCALE_SH__PRE, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण	/*! reset शेष val ! */

		rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_SY_TIMEOUT__A, QAM_SY_TIMEOUT__PRE, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण	/*! reset शेष val ! */
		अगर (ext_attr->standard == DRX_STANDARD_ITU_B) अणु
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_SY_SYNC_LWM__A, QAM_SY_SYNC_LWM__PRE, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण	/*! reset शेष val ! */
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_SY_SYNC_AWM__A, QAM_SY_SYNC_AWM__PRE, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण	/*! reset शेष val ! */
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_SY_SYNC_HWM__A, QAM_SY_SYNC_HWM__PRE, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण	/*! reset शेष val ! */
		पूर्ण अन्यथा अणु
			चयन (channel->स्थिरellation) अणु
			हाल DRX_CONSTELLATION_QAM16:
			हाल DRX_CONSTELLATION_QAM64:
			हाल DRX_CONSTELLATION_QAM256:
				rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_SY_SYNC_LWM__A, 0x03, 0);
				अगर (rc != 0) अणु
					pr_err("error %d\n", rc);
					जाओ rw_error;
				पूर्ण
				rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_SY_SYNC_AWM__A, 0x04, 0);
				अगर (rc != 0) अणु
					pr_err("error %d\n", rc);
					जाओ rw_error;
				पूर्ण
				rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_SY_SYNC_HWM__A, QAM_SY_SYNC_HWM__PRE, 0);
				अगर (rc != 0) अणु
					pr_err("error %d\n", rc);
					जाओ rw_error;
				पूर्ण	/*! reset शेष val ! */
				अवरोध;
			हाल DRX_CONSTELLATION_QAM32:
			हाल DRX_CONSTELLATION_QAM128:
				rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_SY_SYNC_LWM__A, 0x03, 0);
				अगर (rc != 0) अणु
					pr_err("error %d\n", rc);
					जाओ rw_error;
				पूर्ण
				rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_SY_SYNC_AWM__A, 0x05, 0);
				अगर (rc != 0) अणु
					pr_err("error %d\n", rc);
					जाओ rw_error;
				पूर्ण
				rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_SY_SYNC_HWM__A, 0x06, 0);
				अगर (rc != 0) अणु
					pr_err("error %d\n", rc);
					जाओ rw_error;
				पूर्ण
				अवरोध;
			शेष:
				वापस -EIO;
			पूर्ण	/* चयन */
		पूर्ण

		rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_LC_MODE__A, QAM_LC_MODE__PRE, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण	/*! reset शेष val ! */
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_LC_RATE_LIMIT__A, 3, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_LC_LPF_FACTORP__A, 4, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_LC_LPF_FACTORI__A, 4, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_LC_MODE__A, 7, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_LC_QUAL_TAB0__A, 1, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_LC_QUAL_TAB1__A, 1, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_LC_QUAL_TAB2__A, 1, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_LC_QUAL_TAB3__A, 1, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_LC_QUAL_TAB4__A, 2, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_LC_QUAL_TAB5__A, 2, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_LC_QUAL_TAB6__A, 2, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_LC_QUAL_TAB8__A, 2, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_LC_QUAL_TAB9__A, 2, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_LC_QUAL_TAB10__A, 2, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_LC_QUAL_TAB12__A, 2, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_LC_QUAL_TAB15__A, 3, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_LC_QUAL_TAB16__A, 3, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_LC_QUAL_TAB20__A, 4, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_LC_QUAL_TAB25__A, 4, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण

		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_FS_ADJ_SEL__A, 1, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_RC_ADJ_SEL__A, 1, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_CF_ADJ_SEL__A, 1, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_CF_POW_MEAS_LEN__A, 0, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_GPIO__A, 0, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण

		/* No more resets of the IQM, current standard correctly set =>
		   now AGCs can be configured. */
		/* turn on IQMAF. It has to be in front of setAgc**() */
		rc = set_iqm_af(demod, true);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = adc_synchronization(demod);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण

		rc = init_agc(demod);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = set_agc_अगर(demod, &(ext_attr->qam_अगर_agc_cfg), false);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = set_agc_rf(demod, &(ext_attr->qam_rf_agc_cfg), false);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		अणु
			/* TODO fix this, store a काष्ठा drxj_cfg_afe_gain काष्ठाure in काष्ठा drxj_data instead
			   of only the gain */
			काष्ठा drxj_cfg_afe_gain qam_pga_cfg = अणु DRX_STANDARD_ITU_B, 0 पूर्ण;

			qam_pga_cfg.gain = ext_attr->qam_pga_cfg;
			rc = ctrl_set_cfg_afe_gain(demod, &qam_pga_cfg);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
		पूर्ण
		rc = ctrl_set_cfg_pre_saw(demod, &(ext_attr->qam_pre_saw_cfg));
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
	पूर्ण

	अगर ((op & QAM_SET_OP_ALL) || (op & QAM_SET_OP_CONSTELLATION)) अणु
		अगर (ext_attr->standard == DRX_STANDARD_ITU_A) अणु
			rc = drxdap_fasi_ग_लिखो_block(dev_addr, IQM_CF_TAP_RE0__A, माप(qam_a_taps), ((u8 *)qam_a_taps), 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxdap_fasi_ग_लिखो_block(dev_addr, IQM_CF_TAP_IM0__A, माप(qam_a_taps), ((u8 *)qam_a_taps), 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
		पूर्ण अन्यथा अगर (ext_attr->standard == DRX_STANDARD_ITU_B) अणु
			चयन (channel->स्थिरellation) अणु
			हाल DRX_CONSTELLATION_QAM64:
				rc = drxdap_fasi_ग_लिखो_block(dev_addr, IQM_CF_TAP_RE0__A, माप(qam_b64_taps), ((u8 *)qam_b64_taps), 0);
				अगर (rc != 0) अणु
					pr_err("error %d\n", rc);
					जाओ rw_error;
				पूर्ण
				rc = drxdap_fasi_ग_लिखो_block(dev_addr, IQM_CF_TAP_IM0__A, माप(qam_b64_taps), ((u8 *)qam_b64_taps), 0);
				अगर (rc != 0) अणु
					pr_err("error %d\n", rc);
					जाओ rw_error;
				पूर्ण
				अवरोध;
			हाल DRX_CONSTELLATION_QAM256:
				rc = drxdap_fasi_ग_लिखो_block(dev_addr, IQM_CF_TAP_RE0__A, माप(qam_b256_taps), ((u8 *)qam_b256_taps), 0);
				अगर (rc != 0) अणु
					pr_err("error %d\n", rc);
					जाओ rw_error;
				पूर्ण
				rc = drxdap_fasi_ग_लिखो_block(dev_addr, IQM_CF_TAP_IM0__A, माप(qam_b256_taps), ((u8 *)qam_b256_taps), 0);
				अगर (rc != 0) अणु
					pr_err("error %d\n", rc);
					जाओ rw_error;
				पूर्ण
				अवरोध;
			शेष:
				वापस -EIO;
			पूर्ण
		पूर्ण अन्यथा अगर (ext_attr->standard == DRX_STANDARD_ITU_C) अणु
			rc = drxdap_fasi_ग_लिखो_block(dev_addr, IQM_CF_TAP_RE0__A, माप(qam_c_taps), ((u8 *)qam_c_taps), 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxdap_fasi_ग_लिखो_block(dev_addr, IQM_CF_TAP_IM0__A, माप(qam_c_taps), ((u8 *)qam_c_taps), 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
		पूर्ण

		/* SETP 4: स्थिरellation specअगरic setup */
		चयन (channel->स्थिरellation) अणु
		हाल DRX_CONSTELLATION_QAM16:
			rc = set_qam16(demod);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			अवरोध;
		हाल DRX_CONSTELLATION_QAM32:
			rc = set_qam32(demod);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			अवरोध;
		हाल DRX_CONSTELLATION_QAM64:
			rc = set_qam64(demod);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			अवरोध;
		हाल DRX_CONSTELLATION_QAM128:
			rc = set_qam128(demod);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			अवरोध;
		हाल DRX_CONSTELLATION_QAM256:
			rc = set_qam256(demod);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			अवरोध;
		शेष:
			वापस -EIO;
		पूर्ण		/* चयन */
	पूर्ण

	अगर ((op & QAM_SET_OP_ALL)) अणु
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_CF_SCALE_SH__A, 0, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण

		/* Mpeg output has to be in front of FEC active */
		rc = set_mpegtei_handling(demod);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = bit_reverse_mpeg_output(demod);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = set_mpeg_start_width(demod);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		अणु
			/* TODO: move to set_standard after hardware reset value problem is solved */
			/* Configure initial MPEG output */
			काष्ठा drx_cfg_mpeg_output cfg_mpeg_output;

			स_नकल(&cfg_mpeg_output, &common_attr->mpeg_cfg, माप(cfg_mpeg_output));
			cfg_mpeg_output.enable_mpeg_output = true;

			rc = ctrl_set_cfg_mpeg_output(demod, &cfg_mpeg_output);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर ((op & QAM_SET_OP_ALL) || (op & QAM_SET_OP_CONSTELLATION)) अणु

		/* STEP 5: start QAM demodulator (starts FEC, QAM and IQM HW) */
		cmd_scu.command = SCU_RAM_COMMAND_STANDARD_QAM |
		    SCU_RAM_COMMAND_CMD_DEMOD_START;
		cmd_scu.parameter_len = 0;
		cmd_scu.result_len = 1;
		cmd_scu.parameter = शून्य;
		cmd_scu.result = &cmd_result;
		rc = scu_command(dev_addr, &cmd_scu);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_COMM_EXEC__A, IQM_COMM_EXEC_ACTIVE, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_COMM_EXEC__A, QAM_COMM_EXEC_ACTIVE, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, FEC_COMM_EXEC__A, FEC_COMM_EXEC_ACTIVE, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*============================================================================*/
अटल पूर्णांक ctrl_get_qam_sig_quality(काष्ठा drx_demod_instance *demod);

अटल पूर्णांक qam_flip_spec(काष्ठा drx_demod_instance *demod, काष्ठा drx_channel *channel)
अणु
	काष्ठा i2c_device_addr *dev_addr = demod->my_i2c_dev_addr;
	काष्ठा drxj_data *ext_attr = demod->my_ext_attr;
	पूर्णांक rc;
	u32 iqm_fs_rate_ofs = 0;
	u32 iqm_fs_rate_lo = 0;
	u16 qam_ctl_ena = 0;
	u16 data = 0;
	u16 equ_mode = 0;
	u16 fsm_state = 0;
	पूर्णांक i = 0;
	पूर्णांक ofsofs = 0;

	/* Silence the controlling of lc, equ, and the acquisition state machine */
	rc = drxj_dap_पढ़ो_reg16(dev_addr, SCU_RAM_QAM_CTL_ENA__A, &qam_ctl_ena, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_CTL_ENA__A, qam_ctl_ena & ~(SCU_RAM_QAM_CTL_ENA_ACQ__M | SCU_RAM_QAM_CTL_ENA_EQU__M | SCU_RAM_QAM_CTL_ENA_LC__M), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/* मुक्तze the frequency control loop */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_LC_CF__A, 0, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_LC_CF1__A, 0, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_atomic_पढ़ो_reg32(dev_addr, IQM_FS_RATE_OFS_LO__A, &iqm_fs_rate_ofs, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_atomic_पढ़ो_reg32(dev_addr, IQM_FS_RATE_LO__A, &iqm_fs_rate_lo, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	ofsofs = iqm_fs_rate_lo - iqm_fs_rate_ofs;
	iqm_fs_rate_ofs = ~iqm_fs_rate_ofs + 1;
	iqm_fs_rate_ofs -= 2 * ofsofs;

	/* मुक्तze dq/fq updating */
	rc = drxj_dap_पढ़ो_reg16(dev_addr, QAM_DQ_MODE__A, &data, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	data = (data & 0xfff9);
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_DQ_MODE__A, data, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_FQ_MODE__A, data, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/* lc_cp / _ci / _ca */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_LC_CI__A, 0, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_LC_EP__A, 0, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_FQ_LA_FACTOR__A, 0, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/* flip the spec */
	rc = drxdap_fasi_ग_लिखो_reg32(dev_addr, IQM_FS_RATE_OFS_LO__A, iqm_fs_rate_ofs, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	ext_attr->iqm_fs_rate_ofs = iqm_fs_rate_ofs;
	ext_attr->pos_image = (ext_attr->pos_image) ? false : true;

	/* मुक्तze dq/fq updating */
	rc = drxj_dap_पढ़ो_reg16(dev_addr, QAM_DQ_MODE__A, &data, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	equ_mode = data;
	data = (data & 0xfff9);
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_DQ_MODE__A, data, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_FQ_MODE__A, data, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	क्रम (i = 0; i < 28; i++) अणु
		rc = drxj_dap_पढ़ो_reg16(dev_addr, QAM_DQ_TAP_IM_EL0__A + (2 * i), &data, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_DQ_TAP_IM_EL0__A + (2 * i), -data, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 24; i++) अणु
		rc = drxj_dap_पढ़ो_reg16(dev_addr, QAM_FQ_TAP_IM_EL0__A + (2 * i), &data, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_FQ_TAP_IM_EL0__A + (2 * i), -data, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
	पूर्ण

	data = equ_mode;
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_DQ_MODE__A, data, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, QAM_FQ_MODE__A, data, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_FSM_STATE_TGT__A, 4, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	i = 0;
	जबतक ((fsm_state != 4) && (i++ < 100)) अणु
		rc = drxj_dap_पढ़ो_reg16(dev_addr, SCU_RAM_QAM_FSM_STATE__A, &fsm_state, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_QAM_CTL_ENA__A, (qam_ctl_ena | 0x0016), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	वापस 0;
rw_error:
	वापस rc;

पूर्ण

#घोषणा  NO_LOCK        0x0
#घोषणा  DEMOD_LOCKED   0x1
#घोषणा  SYNC_FLIPPED   0x2
#घोषणा  SPEC_MIRRORED  0x4
/*
* \पn पूर्णांक qam64स्वतः ()
* \मrief स्वतः करो sync pattern चयनing and mirroring.
* \param demod:   instance of demod.
* \param channel: poपूर्णांकer to channel data.
* \param tuner_freq_offset: tuner frequency offset.
* \param lock_status: poपूर्णांकer to lock status.
* \लeturn पूर्णांक.
*/
अटल पूर्णांक
qam64स्वतः(काष्ठा drx_demod_instance *demod,
	  काष्ठा drx_channel *channel,
	  s32 tuner_freq_offset, क्रमागत drx_lock_status *lock_status)
अणु
	काष्ठा drxj_data *ext_attr = demod->my_ext_attr;
	काष्ठा i2c_device_addr *dev_addr = demod->my_i2c_dev_addr;
	काष्ठा drx39xxj_state *state = dev_addr->user_data;
	काष्ठा dtv_frontend_properties *p = &state->frontend.dtv_property_cache;
	पूर्णांक rc;
	u32 lck_state = NO_LOCK;
	u32 start_समय = 0;
	u32 d_locked_समय = 0;
	u32 समयout_ofs = 0;
	u16 data = 0;

	/* बाह्यal attributes क्रम storing acquired channel स्थिरellation */
	*lock_status = DRX_NOT_LOCKED;
	start_समय = jअगरfies_to_msecs(jअगरfies);
	lck_state = NO_LOCK;
	करो अणु
		rc = ctrl_lock_status(demod, lock_status);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण

		चयन (lck_state) अणु
		हाल NO_LOCK:
			अगर (*lock_status == DRXJ_DEMOD_LOCK) अणु
				rc = ctrl_get_qam_sig_quality(demod);
				अगर (rc != 0) अणु
					pr_err("error %d\n", rc);
					जाओ rw_error;
				पूर्ण
				अगर (p->cnr.stat[0].svalue > 20800) अणु
					lck_state = DEMOD_LOCKED;
					/* some delay to see अगर fec_lock possible TODO find the right value */
					समयout_ofs += DRXJ_QAM_DEMOD_LOCK_EXT_WAITTIME;	/* see something, रुकोing दीर्घer */
					d_locked_समय = jअगरfies_to_msecs(jअगरfies);
				पूर्ण
			पूर्ण
			अवरोध;
		हाल DEMOD_LOCKED:
			अगर ((*lock_status == DRXJ_DEMOD_LOCK) &&	/* still demod_lock in 150ms */
			    ((jअगरfies_to_msecs(jअगरfies) - d_locked_समय) >
			     DRXJ_QAM_FEC_LOCK_WAITTIME)) अणु
				rc = drxj_dap_पढ़ो_reg16(demod->my_i2c_dev_addr, QAM_SY_TIMEOUT__A, &data, 0);
				अगर (rc != 0) अणु
					pr_err("error %d\n", rc);
					जाओ rw_error;
				पूर्ण
				rc = drxj_dap_ग_लिखो_reg16(demod->my_i2c_dev_addr, QAM_SY_TIMEOUT__A, data | 0x1, 0);
				अगर (rc != 0) अणु
					pr_err("error %d\n", rc);
					जाओ rw_error;
				पूर्ण
				lck_state = SYNC_FLIPPED;
				msleep(10);
			पूर्ण
			अवरोध;
		हाल SYNC_FLIPPED:
			अगर (*lock_status == DRXJ_DEMOD_LOCK) अणु
				अगर (channel->mirror == DRX_MIRROR_AUTO) अणु
					/* flip sync pattern back */
					rc = drxj_dap_पढ़ो_reg16(demod->my_i2c_dev_addr, QAM_SY_TIMEOUT__A, &data, 0);
					अगर (rc != 0) अणु
						pr_err("error %d\n", rc);
						जाओ rw_error;
					पूर्ण
					rc = drxj_dap_ग_लिखो_reg16(demod->my_i2c_dev_addr, QAM_SY_TIMEOUT__A, data & 0xFFFE, 0);
					अगर (rc != 0) अणु
						pr_err("error %d\n", rc);
						जाओ rw_error;
					पूर्ण
					/* flip spectrum */
					ext_attr->mirror = DRX_MIRROR_YES;
					rc = qam_flip_spec(demod, channel);
					अगर (rc != 0) अणु
						pr_err("error %d\n", rc);
						जाओ rw_error;
					पूर्ण
					lck_state = SPEC_MIRRORED;
					/* reset समयr TODO: still need 500ms? */
					start_समय = d_locked_समय =
					    jअगरfies_to_msecs(jअगरfies);
					समयout_ofs = 0;
				पूर्ण अन्यथा अणु	/* no need to रुको lock */

					start_समय =
					    jअगरfies_to_msecs(jअगरfies) -
					    DRXJ_QAM_MAX_WAITTIME - समयout_ofs;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल SPEC_MIRRORED:
			अगर ((*lock_status == DRXJ_DEMOD_LOCK) &&	/* still demod_lock in 150ms */
			    ((jअगरfies_to_msecs(jअगरfies) - d_locked_समय) >
			     DRXJ_QAM_FEC_LOCK_WAITTIME)) अणु
				rc = ctrl_get_qam_sig_quality(demod);
				अगर (rc != 0) अणु
					pr_err("error %d\n", rc);
					जाओ rw_error;
				पूर्ण
				अगर (p->cnr.stat[0].svalue > 20800) अणु
					rc = drxj_dap_पढ़ो_reg16(demod->my_i2c_dev_addr, QAM_SY_TIMEOUT__A, &data, 0);
					अगर (rc != 0) अणु
						pr_err("error %d\n", rc);
						जाओ rw_error;
					पूर्ण
					rc = drxj_dap_ग_लिखो_reg16(demod->my_i2c_dev_addr, QAM_SY_TIMEOUT__A, data | 0x1, 0);
					अगर (rc != 0) अणु
						pr_err("error %d\n", rc);
						जाओ rw_error;
					पूर्ण
					/* no need to रुको lock */
					start_समय =
					    jअगरfies_to_msecs(jअगरfies) -
					    DRXJ_QAM_MAX_WAITTIME - समयout_ofs;
				पूर्ण
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		msleep(10);
	पूर्ण जबतक
	    ((*lock_status != DRX_LOCKED) &&
	     (*lock_status != DRX_NEVER_LOCK) &&
	     ((jअगरfies_to_msecs(jअगरfies) - start_समय) <
	      (DRXJ_QAM_MAX_WAITTIME + समयout_ofs))
	    );
	/* Returning control to application ... */

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*
* \पn पूर्णांक qam256स्वतः ()
* \मrief स्वतः करो sync pattern चयनing and mirroring.
* \param demod:   instance of demod.
* \param channel: poपूर्णांकer to channel data.
* \param tuner_freq_offset: tuner frequency offset.
* \param lock_status: poपूर्णांकer to lock status.
* \लeturn पूर्णांक.
*/
अटल पूर्णांक
qam256स्वतः(काष्ठा drx_demod_instance *demod,
	   काष्ठा drx_channel *channel,
	   s32 tuner_freq_offset, क्रमागत drx_lock_status *lock_status)
अणु
	काष्ठा drxj_data *ext_attr = demod->my_ext_attr;
	काष्ठा i2c_device_addr *dev_addr = demod->my_i2c_dev_addr;
	काष्ठा drx39xxj_state *state = dev_addr->user_data;
	काष्ठा dtv_frontend_properties *p = &state->frontend.dtv_property_cache;
	पूर्णांक rc;
	u32 lck_state = NO_LOCK;
	u32 start_समय = 0;
	u32 d_locked_समय = 0;
	u32 समयout_ofs = DRXJ_QAM_DEMOD_LOCK_EXT_WAITTIME;

	/* बाह्यal attributes क्रम storing acquired channel स्थिरellation */
	*lock_status = DRX_NOT_LOCKED;
	start_समय = jअगरfies_to_msecs(jअगरfies);
	lck_state = NO_LOCK;
	करो अणु
		rc = ctrl_lock_status(demod, lock_status);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		चयन (lck_state) अणु
		हाल NO_LOCK:
			अगर (*lock_status == DRXJ_DEMOD_LOCK) अणु
				rc = ctrl_get_qam_sig_quality(demod);
				अगर (rc != 0) अणु
					pr_err("error %d\n", rc);
					जाओ rw_error;
				पूर्ण
				अगर (p->cnr.stat[0].svalue > 26800) अणु
					lck_state = DEMOD_LOCKED;
					समयout_ofs += DRXJ_QAM_DEMOD_LOCK_EXT_WAITTIME;	/* see something, रुको दीर्घer */
					d_locked_समय = jअगरfies_to_msecs(jअगरfies);
				पूर्ण
			पूर्ण
			अवरोध;
		हाल DEMOD_LOCKED:
			अगर (*lock_status == DRXJ_DEMOD_LOCK) अणु
				अगर ((channel->mirror == DRX_MIRROR_AUTO) &&
				    ((jअगरfies_to_msecs(jअगरfies) - d_locked_समय) >
				     DRXJ_QAM_FEC_LOCK_WAITTIME)) अणु
					ext_attr->mirror = DRX_MIRROR_YES;
					rc = qam_flip_spec(demod, channel);
					अगर (rc != 0) अणु
						pr_err("error %d\n", rc);
						जाओ rw_error;
					पूर्ण
					lck_state = SPEC_MIRRORED;
					/* reset समयr TODO: still need 300ms? */
					start_समय = jअगरfies_to_msecs(jअगरfies);
					समयout_ofs = -DRXJ_QAM_MAX_WAITTIME / 2;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल SPEC_MIRRORED:
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		msleep(10);
	पूर्ण जबतक
	    ((*lock_status < DRX_LOCKED) &&
	     (*lock_status != DRX_NEVER_LOCK) &&
	     ((jअगरfies_to_msecs(jअगरfies) - start_समय) <
	      (DRXJ_QAM_MAX_WAITTIME + समयout_ofs)));

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*
* \पn पूर्णांक set_qam_channel ()
* \मrief Set QAM channel according to the requested स्थिरellation.
* \param demod:   instance of demod.
* \param channel: poपूर्णांकer to channel data.
* \लeturn पूर्णांक.
*/
अटल पूर्णांक
set_qam_channel(काष्ठा drx_demod_instance *demod,
	       काष्ठा drx_channel *channel, s32 tuner_freq_offset)
अणु
	काष्ठा drxj_data *ext_attr = शून्य;
	पूर्णांक rc;
	क्रमागत drx_lock_status lock_status = DRX_NOT_LOCKED;
	bool स्वतः_flag = false;

	/* बाह्यal attributes क्रम storing acquired channel स्थिरellation */
	ext_attr = (काष्ठा drxj_data *) demod->my_ext_attr;

	/* set QAM channel स्थिरellation */
	चयन (channel->स्थिरellation) अणु
	हाल DRX_CONSTELLATION_QAM16:
	हाल DRX_CONSTELLATION_QAM32:
	हाल DRX_CONSTELLATION_QAM128:
		वापस -EINVAL;
	हाल DRX_CONSTELLATION_QAM64:
	हाल DRX_CONSTELLATION_QAM256:
		अगर (ext_attr->standard != DRX_STANDARD_ITU_B)
			वापस -EINVAL;

		ext_attr->स्थिरellation = channel->स्थिरellation;
		अगर (channel->mirror == DRX_MIRROR_AUTO)
			ext_attr->mirror = DRX_MIRROR_NO;
		अन्यथा
			ext_attr->mirror = channel->mirror;

		rc = set_qam(demod, channel, tuner_freq_offset, QAM_SET_OP_ALL);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण

		अगर (channel->स्थिरellation == DRX_CONSTELLATION_QAM64)
			rc = qam64स्वतः(demod, channel, tuner_freq_offset,
				       &lock_status);
		अन्यथा
			rc = qam256स्वतः(demod, channel, tuner_freq_offset,
					&lock_status);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		अवरोध;
	हाल DRX_CONSTELLATION_AUTO:	/* क्रम channel scan */
		अगर (ext_attr->standard == DRX_STANDARD_ITU_B) अणु
			u16 qam_ctl_ena = 0;

			स्वतः_flag = true;

			/* try to lock शेष QAM स्थिरellation: QAM256 */
			channel->स्थिरellation = DRX_CONSTELLATION_QAM256;
			ext_attr->स्थिरellation = DRX_CONSTELLATION_QAM256;
			अगर (channel->mirror == DRX_MIRROR_AUTO)
				ext_attr->mirror = DRX_MIRROR_NO;
			अन्यथा
				ext_attr->mirror = channel->mirror;
			rc = set_qam(demod, channel, tuner_freq_offset,
				     QAM_SET_OP_ALL);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = qam256स्वतः(demod, channel, tuner_freq_offset,
					&lock_status);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण

			अगर (lock_status >= DRX_LOCKED) अणु
				channel->स्थिरellation = DRX_CONSTELLATION_AUTO;
				अवरोध;
			पूर्ण

			/* QAM254 not locked. Try QAM64 स्थिरellation */
			channel->स्थिरellation = DRX_CONSTELLATION_QAM64;
			ext_attr->स्थिरellation = DRX_CONSTELLATION_QAM64;
			अगर (channel->mirror == DRX_MIRROR_AUTO)
				ext_attr->mirror = DRX_MIRROR_NO;
			अन्यथा
				ext_attr->mirror = channel->mirror;

			rc = drxj_dap_पढ़ो_reg16(demod->my_i2c_dev_addr,
						     SCU_RAM_QAM_CTL_ENA__A,
						     &qam_ctl_ena, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxj_dap_ग_लिखो_reg16(demod->my_i2c_dev_addr,
						      SCU_RAM_QAM_CTL_ENA__A,
						      qam_ctl_ena & ~SCU_RAM_QAM_CTL_ENA_ACQ__M, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxj_dap_ग_लिखो_reg16(demod->my_i2c_dev_addr,
						      SCU_RAM_QAM_FSM_STATE_TGT__A,
						      0x2, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण	/* क्रमce to rate hunting */

			rc = set_qam(demod, channel, tuner_freq_offset,
				     QAM_SET_OP_CONSTELLATION);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxj_dap_ग_लिखो_reg16(demod->my_i2c_dev_addr,
						      SCU_RAM_QAM_CTL_ENA__A,
						      qam_ctl_ena, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण

			rc = qam64स्वतः(demod, channel, tuner_freq_offset,
				       &lock_status);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण

			channel->स्थिरellation = DRX_CONSTELLATION_AUTO;
		पूर्ण अन्यथा अगर (ext_attr->standard == DRX_STANDARD_ITU_C) अणु
			u16 qam_ctl_ena = 0;

			channel->स्थिरellation = DRX_CONSTELLATION_QAM64;
			ext_attr->स्थिरellation = DRX_CONSTELLATION_QAM64;
			स्वतः_flag = true;

			अगर (channel->mirror == DRX_MIRROR_AUTO)
				ext_attr->mirror = DRX_MIRROR_NO;
			अन्यथा
				ext_attr->mirror = channel->mirror;
			rc = drxj_dap_पढ़ो_reg16(demod->my_i2c_dev_addr,
						     SCU_RAM_QAM_CTL_ENA__A,
						     &qam_ctl_ena, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxj_dap_ग_लिखो_reg16(demod->my_i2c_dev_addr,
						      SCU_RAM_QAM_CTL_ENA__A,
						      qam_ctl_ena & ~SCU_RAM_QAM_CTL_ENA_ACQ__M, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxj_dap_ग_लिखो_reg16(demod->my_i2c_dev_addr,
						      SCU_RAM_QAM_FSM_STATE_TGT__A,
						      0x2, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण	/* क्रमce to rate hunting */

			rc = set_qam(demod, channel, tuner_freq_offset,
				     QAM_SET_OP_CONSTELLATION);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = drxj_dap_ग_लिखो_reg16(demod->my_i2c_dev_addr,
						      SCU_RAM_QAM_CTL_ENA__A,
						      qam_ctl_ena, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			rc = qam64स्वतः(demod, channel, tuner_freq_offset,
				       &lock_status);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			channel->स्थिरellation = DRX_CONSTELLATION_AUTO;
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
rw_error:
	/* restore starting value */
	अगर (स्वतः_flag)
		channel->स्थिरellation = DRX_CONSTELLATION_AUTO;
	वापस rc;
पूर्ण

/*============================================================================*/

/*
* \पn अटल लघु get_qamrs_err_count(काष्ठा i2c_device_addr *dev_addr)
* \मrief Get RS error count in QAM mode (used क्रम post RS BER calculation)
* \लeturn Error code
*
* precondition: measurement period & measurement prescale must be set
*
*/
अटल पूर्णांक
get_qamrs_err_count(काष्ठा i2c_device_addr *dev_addr,
		    काष्ठा drxjrs_errors *rs_errors)
अणु
	पूर्णांक rc;
	u16 nr_bit_errors = 0,
	    nr_symbol_errors = 0,
	    nr_packet_errors = 0, nr_failures = 0, nr_snc_par_fail_count = 0;

	/* check arguments */
	अगर (dev_addr == शून्य)
		वापस -EINVAL;

	/* all reported errors are received in the  */
	/* most recently finished measurement period */
	/*   no of pre RS bit errors */
	rc = drxj_dap_पढ़ो_reg16(dev_addr, FEC_RS_NR_BIT_ERRORS__A, &nr_bit_errors, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	/*   no of symbol errors      */
	rc = drxj_dap_पढ़ो_reg16(dev_addr, FEC_RS_NR_SYMBOL_ERRORS__A, &nr_symbol_errors, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	/*   no of packet errors      */
	rc = drxj_dap_पढ़ो_reg16(dev_addr, FEC_RS_NR_PACKET_ERRORS__A, &nr_packet_errors, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	/*   no of failures to decode */
	rc = drxj_dap_पढ़ो_reg16(dev_addr, FEC_RS_NR_FAILURES__A, &nr_failures, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	/*   no of post RS bit erros  */
	rc = drxj_dap_पढ़ो_reg16(dev_addr, FEC_OC_SNC_FAIL_COUNT__A, &nr_snc_par_fail_count, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	/* TODO: NOTE */
	/* These रेजिस्टर values are fetched in non-atomic fashion           */
	/* It is possible that the पढ़ो values contain unrelated inक्रमmation */

	rs_errors->nr_bit_errors = nr_bit_errors & FEC_RS_NR_BIT_ERRORS__M;
	rs_errors->nr_symbol_errors = nr_symbol_errors & FEC_RS_NR_SYMBOL_ERRORS__M;
	rs_errors->nr_packet_errors = nr_packet_errors & FEC_RS_NR_PACKET_ERRORS__M;
	rs_errors->nr_failures = nr_failures & FEC_RS_NR_FAILURES__M;
	rs_errors->nr_snc_par_fail_count =
	    nr_snc_par_fail_count & FEC_OC_SNC_FAIL_COUNT__M;

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*============================================================================*/

/*
 * \पn पूर्णांक get_sig_strength()
 * \मrief Retrieve संकेत strength क्रम VSB and QAM.
 * \param demod Poपूर्णांकer to demod instance
 * \param u16-t Poपूर्णांकer to संकेत strength data; range 0, .. , 100.
 * \लeturn पूर्णांक.
 * \लetval 0 sig_strength contains valid data.
 * \लetval -EINVAL sig_strength is शून्य.
 * \लetval -EIO Erroneous data, sig_strength contains invalid data.
 */
#घोषणा DRXJ_AGC_TOP    0x2800
#घोषणा DRXJ_AGC_SNS    0x1600
#घोषणा DRXJ_RFAGC_MAX  0x3fff
#घोषणा DRXJ_RFAGC_MIN  0x800

अटल पूर्णांक get_sig_strength(काष्ठा drx_demod_instance *demod, u16 *sig_strength)
अणु
	काष्ठा i2c_device_addr *dev_addr = demod->my_i2c_dev_addr;
	पूर्णांक rc;
	u16 rf_gain = 0;
	u16 अगर_gain = 0;
	u16 अगर_agc_sns = 0;
	u16 अगर_agc_top = 0;
	u16 rf_agc_max = 0;
	u16 rf_agc_min = 0;

	rc = drxj_dap_पढ़ो_reg16(dev_addr, IQM_AF_AGC_IF__A, &अगर_gain, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	अगर_gain &= IQM_AF_AGC_IF__M;
	rc = drxj_dap_पढ़ो_reg16(dev_addr, IQM_AF_AGC_RF__A, &rf_gain, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rf_gain &= IQM_AF_AGC_RF__M;

	अगर_agc_sns = DRXJ_AGC_SNS;
	अगर_agc_top = DRXJ_AGC_TOP;
	rf_agc_max = DRXJ_RFAGC_MAX;
	rf_agc_min = DRXJ_RFAGC_MIN;

	अगर (अगर_gain > अगर_agc_top) अणु
		अगर (rf_gain > rf_agc_max)
			*sig_strength = 100;
		अन्यथा अगर (rf_gain > rf_agc_min) अणु
			अगर (rf_agc_max == rf_agc_min) अणु
				pr_err("error: rf_agc_max == rf_agc_min\n");
				वापस -EIO;
			पूर्ण
			*sig_strength =
			75 + 25 * (rf_gain - rf_agc_min) / (rf_agc_max -
								rf_agc_min);
		पूर्ण अन्यथा
			*sig_strength = 75;
	पूर्ण अन्यथा अगर (अगर_gain > अगर_agc_sns) अणु
		अगर (अगर_agc_top == अगर_agc_sns) अणु
			pr_err("error: if_agc_top == if_agc_sns\n");
			वापस -EIO;
		पूर्ण
		*sig_strength =
		20 + 55 * (अगर_gain - अगर_agc_sns) / (अगर_agc_top - अगर_agc_sns);
	पूर्ण अन्यथा अणु
		अगर (!अगर_agc_sns) अणु
			pr_err("error: if_agc_sns is zero!\n");
			वापस -EIO;
		पूर्ण
		*sig_strength = (20 * अगर_gain / अगर_agc_sns);
	पूर्ण

	अगर (*sig_strength <= 7)
		*sig_strength = 0;

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*
* \पn पूर्णांक ctrl_get_qam_sig_quality()
* \मrief Retrieve QAM संकेत quality from device.
* \param devmod Poपूर्णांकer to demodulator instance.
* \param sig_quality Poपूर्णांकer to संकेत quality data.
* \लeturn पूर्णांक.
* \लetval 0 sig_quality contains valid data.
* \लetval -EINVAL sig_quality is शून्य.
* \लetval -EIO Erroneous data, sig_quality contains invalid data.

*  Pre-condition: Device must be started and in lock.
*/
अटल पूर्णांक
ctrl_get_qam_sig_quality(काष्ठा drx_demod_instance *demod)
अणु
	काष्ठा i2c_device_addr *dev_addr = demod->my_i2c_dev_addr;
	काष्ठा drxj_data *ext_attr = demod->my_ext_attr;
	काष्ठा drx39xxj_state *state = dev_addr->user_data;
	काष्ठा dtv_frontend_properties *p = &state->frontend.dtv_property_cache;
	काष्ठा drxjrs_errors measuredrs_errors = अणु 0, 0, 0, 0, 0 पूर्ण;
	क्रमागत drx_modulation स्थिरellation = ext_attr->स्थिरellation;
	पूर्णांक rc;

	u32 pre_bit_err_rs = 0;	/* pre RedSolomon Bit Error Rate */
	u32 post_bit_err_rs = 0;	/* post RedSolomon Bit Error Rate */
	u32 pkt_errs = 0;	/* no of packet errors in RS */
	u16 qam_sl_err_घातer = 0;	/* accumulated error between raw and sliced symbols */
	u16 qsym_err_vd = 0;	/* quadrature symbol errors in QAM_VD */
	u16 fec_oc_period = 0;	/* SNC sync failure measurement period */
	u16 fec_rs_prescale = 0;	/* ReedSolomon Measurement Prescale */
	u16 fec_rs_period = 0;	/* Value क्रम corresponding I2C रेजिस्टर */
	/* calculation स्थिरants */
	u32 rs_bit_cnt = 0;	/* RedSolomon Bit Count */
	u32 qam_sl_sig_घातer = 0;	/* used क्रम MER, depends of QAM स्थिरellation */
	/* पूर्णांकermediate results */
	u32 e = 0;		/* exponent value used क्रम QAM BER/SER */
	u32 m = 0;		/* mantisa value used क्रम QAM BER/SER */
	u32 ber_cnt = 0;	/* BER count */
	/* संकेत quality info */
	u32 qam_sl_mer = 0;	/* QAM MER */
	u32 qam_pre_rs_ber = 0;	/* Pre RedSolomon BER */
	u32 qam_post_rs_ber = 0;	/* Post RedSolomon BER */
	u32 qam_vd_ser = 0;	/* ViterbiDecoder SER */
	u16 qam_vd_prescale = 0;	/* Viterbi Measurement Prescale */
	u16 qam_vd_period = 0;	/* Viterbi Measurement period */
	u32 vd_bit_cnt = 0;	/* ViterbiDecoder Bit Count */

	p->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	/* पढ़ो the physical रेजिस्टरs */
	/*   Get the RS error data */
	rc = get_qamrs_err_count(dev_addr, &measuredrs_errors);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	/* get the रेजिस्टर value needed क्रम MER */
	rc = drxj_dap_पढ़ो_reg16(dev_addr, QAM_SL_ERR_POWER__A, &qam_sl_err_घातer, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	/* get the रेजिस्टर value needed क्रम post RS BER */
	rc = drxj_dap_पढ़ो_reg16(dev_addr, FEC_OC_SNC_FAIL_PERIOD__A, &fec_oc_period, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/* get स्थिरants needed क्रम संकेत quality calculation */
	fec_rs_period = ext_attr->fec_rs_period;
	fec_rs_prescale = ext_attr->fec_rs_prescale;
	rs_bit_cnt = fec_rs_period * fec_rs_prescale * ext_attr->fec_rs_plen;
	qam_vd_period = ext_attr->qam_vd_period;
	qam_vd_prescale = ext_attr->qam_vd_prescale;
	vd_bit_cnt = qam_vd_period * qam_vd_prescale * ext_attr->fec_vd_plen;

	/* DRXJ_QAM_SL_SIG_POWER_QAMxxx  * 4     */
	चयन (स्थिरellation) अणु
	हाल DRX_CONSTELLATION_QAM16:
		qam_sl_sig_घातer = DRXJ_QAM_SL_SIG_POWER_QAM16 << 2;
		अवरोध;
	हाल DRX_CONSTELLATION_QAM32:
		qam_sl_sig_घातer = DRXJ_QAM_SL_SIG_POWER_QAM32 << 2;
		अवरोध;
	हाल DRX_CONSTELLATION_QAM64:
		qam_sl_sig_घातer = DRXJ_QAM_SL_SIG_POWER_QAM64 << 2;
		अवरोध;
	हाल DRX_CONSTELLATION_QAM128:
		qam_sl_sig_घातer = DRXJ_QAM_SL_SIG_POWER_QAM128 << 2;
		अवरोध;
	हाल DRX_CONSTELLATION_QAM256:
		qam_sl_sig_घातer = DRXJ_QAM_SL_SIG_POWER_QAM256 << 2;
		अवरोध;
	शेष:
		वापस -EIO;
	पूर्ण

	/* ------------------------------ */
	/* MER Calculation                */
	/* ------------------------------ */
	/* MER is good अगर it is above 27.5 क्रम QAM256 or 21.5 क्रम QAM64 */

	/* 10.0*log10(qam_sl_sig_घातer * 4.0 / qam_sl_err_घातer); */
	अगर (qam_sl_err_घातer == 0)
		qam_sl_mer = 0;
	अन्यथा
		qam_sl_mer = log1_बार100(qam_sl_sig_घातer) - log1_बार100((u32)qam_sl_err_घातer);

	/* ----------------------------------------- */
	/* Pre Viterbi Symbol Error Rate Calculation */
	/* ----------------------------------------- */
	/* pre viterbi SER is good अगर it is below 0.025 */

	/* get the रेजिस्टर value */
	/*   no of quadrature symbol errors */
	rc = drxj_dap_पढ़ो_reg16(dev_addr, QAM_VD_NR_QSYM_ERRORS__A, &qsym_err_vd, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	/* Extract the Exponent and the Mantisa  */
	/* of number of quadrature symbol errors */
	e = (qsym_err_vd & QAM_VD_NR_QSYM_ERRORS_EXP__M) >>
	    QAM_VD_NR_QSYM_ERRORS_EXP__B;
	m = (qsym_err_vd & QAM_VD_NR_SYMBOL_ERRORS_FIXED_MANT__M) >>
	    QAM_VD_NR_SYMBOL_ERRORS_FIXED_MANT__B;

	अगर ((m << e) >> 3 > 549752)
		qam_vd_ser = 500000 * vd_bit_cnt * ((e > 2) ? 1 : 8) / 8;
	अन्यथा
		qam_vd_ser = m << ((e > 2) ? (e - 3) : e);

	/* --------------------------------------- */
	/* pre and post RedSolomon BER Calculation */
	/* --------------------------------------- */
	/* pre RS BER is good अगर it is below 3.5e-4 */

	/* get the रेजिस्टर values */
	pre_bit_err_rs = (u32) measuredrs_errors.nr_bit_errors;
	pkt_errs = post_bit_err_rs = (u32) measuredrs_errors.nr_snc_par_fail_count;

	/* Extract the Exponent and the Mantisa of the */
	/* pre Reed-Solomon bit error count            */
	e = (pre_bit_err_rs & FEC_RS_NR_BIT_ERRORS_EXP__M) >>
	    FEC_RS_NR_BIT_ERRORS_EXP__B;
	m = (pre_bit_err_rs & FEC_RS_NR_BIT_ERRORS_FIXED_MANT__M) >>
	    FEC_RS_NR_BIT_ERRORS_FIXED_MANT__B;

	ber_cnt = m << e;

	/*qam_pre_rs_ber = frac_बार1e6( ber_cnt, rs_bit_cnt ); */
	अगर (m > (rs_bit_cnt >> (e + 1)) || (rs_bit_cnt >> e) == 0)
		qam_pre_rs_ber = 500000 * rs_bit_cnt >> e;
	अन्यथा
		qam_pre_rs_ber = ber_cnt;

	/* post RS BER = 1000000* (11.17 * FEC_OC_SNC_FAIL_COUNT__A) /  */
	/*               (1504.0 * FEC_OC_SNC_FAIL_PERIOD__A)  */
	/*
	   => c = (1000000*100*11.17)/1504 =
	   post RS BER = (( c* FEC_OC_SNC_FAIL_COUNT__A) /
	   (100 * FEC_OC_SNC_FAIL_PERIOD__A)
	   *100 and /100 is क्रम more precision.
	   => (20 bits * 12 bits) /(16 bits * 7 bits)  => safe in 32 bits computation

	   Precision errors still possible.
	 */
	अगर (!fec_oc_period) अणु
		qam_post_rs_ber = 0xFFFFFFFF;
	पूर्ण अन्यथा अणु
		e = post_bit_err_rs * 742686;
		m = fec_oc_period * 100;
		qam_post_rs_ber = e / m;
	पूर्ण

	/* fill संकेत quality data काष्ठाure */
	p->pre_bit_count.stat[0].scale = FE_SCALE_COUNTER;
	p->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
	p->pre_bit_error.stat[0].scale = FE_SCALE_COUNTER;
	p->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
	p->block_error.stat[0].scale = FE_SCALE_COUNTER;
	p->cnr.stat[0].scale = FE_SCALE_DECIBEL;

	p->cnr.stat[0].svalue = ((u16) qam_sl_mer) * 100;
	अगर (ext_attr->standard == DRX_STANDARD_ITU_B) अणु
		p->pre_bit_error.stat[0].uvalue += qam_vd_ser;
		p->pre_bit_count.stat[0].uvalue += vd_bit_cnt * ((e > 2) ? 1 : 8) / 8;
	पूर्ण अन्यथा अणु
		p->pre_bit_error.stat[0].uvalue += qam_pre_rs_ber;
		p->pre_bit_count.stat[0].uvalue += rs_bit_cnt >> e;
	पूर्ण

	p->post_bit_error.stat[0].uvalue += qam_post_rs_ber;
	p->post_bit_count.stat[0].uvalue += rs_bit_cnt >> e;

	p->block_error.stat[0].uvalue += pkt_errs;

#अगर_घोषित DRXJ_SIGNAL_ACCUM_ERR
	rc = get_acc_pkt_err(demod, &sig_quality->packet_error);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
#पूर्ण_अगर

	वापस 0;
rw_error:
	p->pre_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->pre_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	वापस rc;
पूर्ण

#पूर्ण_अगर /* #अगर_अघोषित DRXJ_VSB_ONLY */

/*============================================================================*/
/*==                     END QAM DATAPATH FUNCTIONS                         ==*/
/*============================================================================*/

/*============================================================================*/
/*============================================================================*/
/*==                       ATV DATAPATH FUNCTIONS                           ==*/
/*============================================================================*/
/*============================================================================*/

/*
   Implementation notes.

   NTSC/FM AGCs

      Four AGCs are used क्रम NTSC:
      (1) RF (used to attenuate the input संकेत in हाल of to much घातer)
      (2) IF (used to attenuate the input संकेत in हाल of to much घातer)
      (3) Video AGC (used to amplअगरy the output संकेत in हाल input to low)
      (4) SIF AGC (used to amplअगरy the output संकेत in हाल input to low)

      Video AGC is coupled to RF and IF. SIF AGC is not coupled. It is assumed
      that the coupling between Video AGC and the RF and IF AGCs also works in
      favor of the SIF AGC.

      Three AGCs are used क्रम FM:
      (1) RF (used to attenuate the input संकेत in हाल of to much घातer)
      (2) IF (used to attenuate the input संकेत in हाल of to much घातer)
      (3) SIF AGC (used to amplअगरy the output संकेत in हाल input to low)

      The SIF AGC is now coupled to the RF/IF AGCs.
      The SIF AGC is needed क्रम both SIF output and the पूर्णांकernal SIF संकेत to
      the AUD block.

      RF and IF AGCs DACs are part of AFE, Video and SIF AGC DACs are part of
      the ATV block. The AGC control algorithms are all implemented in
      microcode.

   ATV SETTINGS

      (Shaकरोw settings will not be used क्रम now, they will be implemented
       later on because of the schedule)

      Several HW/SCU "settings" can be used क्रम ATV. The standard selection
      will reset most of these settings. To aव्योम that the end user application
      has to perक्रमm these settings each समय the ATV or FM standards is
      selected the driver will shaकरोw these settings. This enables the end user
      to perक्रमm the settings only once after a drx_खोलो(). The driver must
      ग_लिखो the shaकरोw settings to HW/SCU in हाल:
	 ( setstandard FM/ATV) ||
	 ( settings have changed && FM/ATV standard is active)
      The shaकरोw settings will be stored in the device specअगरic data container.
      A set of flags will be defined to flag changes in shaकरोw settings.
      A routine will be implemented to ग_लिखो all changed shaकरोw settings to
      HW/SCU.

      The "settings" will consist of: AGC settings, filter settings etc.

      Disadvantage of use of shaकरोw settings:
      Direct changes in HW/SCU रेजिस्टरs will not be reflected in the
      shaकरोw settings and these changes will be overwritten during a next
      update. This can happen during evaluation. This will not be a problem
      क्रम normal customer usage.
*/
/* -------------------------------------------------------------------------- */

/*
* \पn पूर्णांक घातer_करोwn_atv ()
* \मrief Power करोwn ATV.
* \param demod instance of demodulator
* \param standard either NTSC or FM (sub stअक्रमard क्रम ATV )
* \लeturn पूर्णांक.
*
*  Stops and thus resets ATV and IQM block
*  SIF and CVBS ADC are घातered करोwn
*  Calls audio घातer करोwn
*/
अटल पूर्णांक
घातer_करोwn_atv(काष्ठा drx_demod_instance *demod, क्रमागत drx_standard standard, bool primary)
अणु
	काष्ठा i2c_device_addr *dev_addr = demod->my_i2c_dev_addr;
	काष्ठा drxjscu_cmd cmd_scu = अणु /* command      */ 0,
		/* parameter_len */ 0,
		/* result_len    */ 0,
		/* *parameter   */ शून्य,
		/* *result      */ शून्य
	पूर्ण;
	पूर्णांक rc;
	u16 cmd_result = 0;

	/* ATV NTSC */

	/* Stop ATV SCU (will reset ATV and IQM hardware */
	cmd_scu.command = SCU_RAM_COMMAND_STANDARD_ATV |
	    SCU_RAM_COMMAND_CMD_DEMOD_STOP;
	cmd_scu.parameter_len = 0;
	cmd_scu.result_len = 1;
	cmd_scu.parameter = शून्य;
	cmd_scu.result = &cmd_result;
	rc = scu_command(dev_addr, &cmd_scu);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	/* Disable ATV outमाला_दो (ATV reset enables CVBS, unकरो this) */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, ATV_TOP_STDBY__A, (ATV_TOP_STDBY_SIF_STDBY_STANDBY & (~ATV_TOP_STDBY_CVBS_STDBY_A2_ACTIVE)), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, ATV_COMM_EXEC__A, ATV_COMM_EXEC_STOP, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	अगर (primary) अणु
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_COMM_EXEC__A, IQM_COMM_EXEC_STOP, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = set_iqm_af(demod, false);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
	पूर्ण अन्यथा अणु
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_FS_COMM_EXEC__A, IQM_FS_COMM_EXEC_STOP, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_FD_COMM_EXEC__A, IQM_FD_COMM_EXEC_STOP, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_RC_COMM_EXEC__A, IQM_RC_COMM_EXEC_STOP, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_RT_COMM_EXEC__A, IQM_RT_COMM_EXEC_STOP, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_CF_COMM_EXEC__A, IQM_CF_COMM_EXEC_STOP, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
	पूर्ण
	rc = घातer_करोwn_aud(demod);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*============================================================================*/

/*
* \मrief Power up AUD.
* \param demod instance of demodulator
* \लeturn पूर्णांक.
*
*/
अटल पूर्णांक घातer_करोwn_aud(काष्ठा drx_demod_instance *demod)
अणु
	काष्ठा i2c_device_addr *dev_addr = शून्य;
	काष्ठा drxj_data *ext_attr = शून्य;
	पूर्णांक rc;

	dev_addr = (काष्ठा i2c_device_addr *)demod->my_i2c_dev_addr;
	ext_attr = (काष्ठा drxj_data *) demod->my_ext_attr;

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, AUD_COMM_EXEC__A, AUD_COMM_EXEC_STOP, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	ext_attr->aud_data.audio_is_active = false;

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*
* \पn पूर्णांक set_orx_nsu_aox()
* \मrief Configure OrxNsuAox क्रम OOB
* \param demod instance of demodulator.
* \param active
* \लeturn पूर्णांक.
*/
अटल पूर्णांक set_orx_nsu_aox(काष्ठा drx_demod_instance *demod, bool active)
अणु
	काष्ठा i2c_device_addr *dev_addr = demod->my_i2c_dev_addr;
	पूर्णांक rc;
	u16 data = 0;

	/* Configure NSU_AOX */
	rc = drxj_dap_पढ़ो_reg16(dev_addr, ORX_NSU_AOX_STDBY_W__A, &data, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	अगर (!active)
		data &= ((~ORX_NSU_AOX_STDBY_W_STDBYADC_A2_ON) & (~ORX_NSU_AOX_STDBY_W_STDBYAMP_A2_ON) & (~ORX_NSU_AOX_STDBY_W_STDBYBIAS_A2_ON) & (~ORX_NSU_AOX_STDBY_W_STDBYPLL_A2_ON) & (~ORX_NSU_AOX_STDBY_W_STDBYPD_A2_ON) & (~ORX_NSU_AOX_STDBY_W_STDBYTAGC_IF_A2_ON) & (~ORX_NSU_AOX_STDBY_W_STDBYTAGC_RF_A2_ON) & (~ORX_NSU_AOX_STDBY_W_STDBYFLT_A2_ON));
	अन्यथा
		data |= (ORX_NSU_AOX_STDBY_W_STDBYADC_A2_ON | ORX_NSU_AOX_STDBY_W_STDBYAMP_A2_ON | ORX_NSU_AOX_STDBY_W_STDBYBIAS_A2_ON | ORX_NSU_AOX_STDBY_W_STDBYPLL_A2_ON | ORX_NSU_AOX_STDBY_W_STDBYPD_A2_ON | ORX_NSU_AOX_STDBY_W_STDBYTAGC_IF_A2_ON | ORX_NSU_AOX_STDBY_W_STDBYTAGC_RF_A2_ON | ORX_NSU_AOX_STDBY_W_STDBYFLT_A2_ON);
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, ORX_NSU_AOX_STDBY_W__A, data, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*
* \पn पूर्णांक ctrl_set_oob()
* \मrief Set OOB channel to be used.
* \param demod instance of demodulator
* \param oob_param OOB parameters क्रम channel setting.
* \पrequency should be in KHz
* \लeturn पूर्णांक.
*
* Accepts  only. Returns error otherwise.
* Demapper value is written after scu_command START
* because START command causes COMM_EXEC transition
* from 0 to 1 which causes all रेजिस्टरs to be
* overwritten with initial value
*
*/

/* Nyquist filter impulse response */
#घोषणा IMPULSE_COSINE_ALPHA_0_3    अणु-3, -4, -1, 6, 10, 7, -5, -20, -25, -10, 29, 79, 123, 140पूर्ण	/*वर्ग_मूल उठाओd-cosine filter with alpha=0.3 */
#घोषणा IMPULSE_COSINE_ALPHA_0_5    अणु 2, 0, -2, -2, 2, 5, 2, -10, -20, -14, 20, 74, 125, 145पूर्ण	/*वर्ग_मूल उठाओd-cosine filter with alpha=0.5 */
#घोषणा IMPULSE_COSINE_ALPHA_RO_0_5 अणु 0, 0, 1, 2, 3, 0, -7, -15, -16,  0, 34, 77, 114, 128पूर्ण	/*full उठाओd-cosine filter with alpha=0.5 (receiver only) */

/* Coefficients क्रम the nyquist filter (total: 27 taps) */
#घोषणा NYQFILTERLEN 27

अटल पूर्णांक ctrl_set_oob(काष्ठा drx_demod_instance *demod, काष्ठा drxoob *oob_param)
अणु
	पूर्णांक rc;
	s32 freq = 0;	/* KHz */
	काष्ठा i2c_device_addr *dev_addr = शून्य;
	काष्ठा drxj_data *ext_attr = शून्य;
	u16 i = 0;
	bool mirror_freq_spect_oob = false;
	u16 trk_filter_value = 0;
	काष्ठा drxjscu_cmd scu_cmd;
	u16 set_param_parameters[3];
	u16 cmd_result[2] = अणु 0, 0 पूर्ण;
	s16 nyquist_coeffs[4][(NYQFILTERLEN + 1) / 2] = अणु
		IMPULSE_COSINE_ALPHA_0_3,	/* Target Mode 0 */
		IMPULSE_COSINE_ALPHA_0_3,	/* Target Mode 1 */
		IMPULSE_COSINE_ALPHA_0_5,	/* Target Mode 2 */
		IMPULSE_COSINE_ALPHA_RO_0_5	/* Target Mode 3 */
	पूर्ण;
	u8 mode_val[4] = अणु 2, 2, 0, 1 पूर्ण;
	u8 pfi_coeffs[4][6] = अणु
		अणुDRXJ_16TO8(-92), DRXJ_16TO8(-108), DRXJ_16TO8(100)पूर्ण,	/* TARGET_MODE = 0:     PFI_A = -23/32; PFI_B = -54/32;  PFI_C = 25/32; fg = 0.5 MHz (Att=26dB) */
		अणुDRXJ_16TO8(-64), DRXJ_16TO8(-80), DRXJ_16TO8(80)पूर्ण,	/* TARGET_MODE = 1:     PFI_A = -16/32; PFI_B = -40/32;  PFI_C = 20/32; fg = 1.0 MHz (Att=28dB) */
		अणुDRXJ_16TO8(-80), DRXJ_16TO8(-98), DRXJ_16TO8(92)पूर्ण,	/* TARGET_MODE = 2, 3:  PFI_A = -20/32; PFI_B = -49/32;  PFI_C = 23/32; fg = 0.8 MHz (Att=25dB) */
		अणुDRXJ_16TO8(-80), DRXJ_16TO8(-98), DRXJ_16TO8(92)पूर्ण	/* TARGET_MODE = 2, 3:  PFI_A = -20/32; PFI_B = -49/32;  PFI_C = 23/32; fg = 0.8 MHz (Att=25dB) */
	पूर्ण;
	u16 mode_index;

	dev_addr = demod->my_i2c_dev_addr;
	ext_attr = (काष्ठा drxj_data *) demod->my_ext_attr;
	mirror_freq_spect_oob = ext_attr->mirror_freq_spect_oob;

	/* Check parameters */
	अगर (oob_param == शून्य) अणु
		/* घातer off oob module  */
		scu_cmd.command = SCU_RAM_COMMAND_STANDARD_OOB
		    | SCU_RAM_COMMAND_CMD_DEMOD_STOP;
		scu_cmd.parameter_len = 0;
		scu_cmd.result_len = 1;
		scu_cmd.result = cmd_result;
		rc = scu_command(dev_addr, &scu_cmd);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = set_orx_nsu_aox(demod, false);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, ORX_COMM_EXEC__A, ORX_COMM_EXEC_STOP, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण

		ext_attr->oob_घातer_on = false;
		वापस 0;
	पूर्ण

	freq = oob_param->frequency;
	अगर ((freq < 70000) || (freq > 130000))
		वापस -EIO;
	freq = (freq - 50000) / 50;

	अणु
		u16 index = 0;
		u16 reमुख्यder = 0;
		u16 *trk_filtercfg = ext_attr->oob_trk_filter_cfg;

		index = (u16) ((freq - 400) / 200);
		reमुख्यder = (u16) ((freq - 400) % 200);
		trk_filter_value =
		    trk_filtercfg[index] - (trk_filtercfg[index] -
					   trk_filtercfg[index +
							1]) / 10 * reमुख्यder /
		    20;
	पूर्ण

   /********/
	/* Stop  */
   /********/
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, ORX_COMM_EXEC__A, ORX_COMM_EXEC_STOP, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	scu_cmd.command = SCU_RAM_COMMAND_STANDARD_OOB
	    | SCU_RAM_COMMAND_CMD_DEMOD_STOP;
	scu_cmd.parameter_len = 0;
	scu_cmd.result_len = 1;
	scu_cmd.result = cmd_result;
	rc = scu_command(dev_addr, &scu_cmd);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
   /********/
	/* Reset */
   /********/
	scu_cmd.command = SCU_RAM_COMMAND_STANDARD_OOB
	    | SCU_RAM_COMMAND_CMD_DEMOD_RESET;
	scu_cmd.parameter_len = 0;
	scu_cmd.result_len = 1;
	scu_cmd.result = cmd_result;
	rc = scu_command(dev_addr, &scu_cmd);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
   /**********/
	/* SET_ENV */
   /**********/
	/* set frequency, spectrum inversion and data rate */
	scu_cmd.command = SCU_RAM_COMMAND_STANDARD_OOB
	    | SCU_RAM_COMMAND_CMD_DEMOD_SET_ENV;
	scu_cmd.parameter_len = 3;
	/* 1-data rate;2-frequency */
	चयन (oob_param->standard) अणु
	हाल DRX_OOB_MODE_A:
		अगर (
			   /* संकेत is transmitted inverted */
			   ((oob_param->spectrum_inverted == true) &&
			    /* and tuner is not mirroring the संकेत */
			    (!mirror_freq_spect_oob)) |
			   /* or */
			   /* संकेत is transmitted noninverted */
			   ((oob_param->spectrum_inverted == false) &&
			    /* and tuner is mirroring the संकेत */
			    (mirror_freq_spect_oob))
		    )
			set_param_parameters[0] =
			    SCU_RAM_ORX_RF_RX_DATA_RATE_2048KBPS_INVSPEC;
		अन्यथा
			set_param_parameters[0] =
			    SCU_RAM_ORX_RF_RX_DATA_RATE_2048KBPS_REGSPEC;
		अवरोध;
	हाल DRX_OOB_MODE_B_GRADE_A:
		अगर (
			   /* संकेत is transmitted inverted */
			   ((oob_param->spectrum_inverted == true) &&
			    /* and tuner is not mirroring the संकेत */
			    (!mirror_freq_spect_oob)) |
			   /* or */
			   /* संकेत is transmitted noninverted */
			   ((oob_param->spectrum_inverted == false) &&
			    /* and tuner is mirroring the संकेत */
			    (mirror_freq_spect_oob))
		    )
			set_param_parameters[0] =
			    SCU_RAM_ORX_RF_RX_DATA_RATE_1544KBPS_INVSPEC;
		अन्यथा
			set_param_parameters[0] =
			    SCU_RAM_ORX_RF_RX_DATA_RATE_1544KBPS_REGSPEC;
		अवरोध;
	हाल DRX_OOB_MODE_B_GRADE_B:
	शेष:
		अगर (
			   /* संकेत is transmitted inverted */
			   ((oob_param->spectrum_inverted == true) &&
			    /* and tuner is not mirroring the संकेत */
			    (!mirror_freq_spect_oob)) |
			   /* or */
			   /* संकेत is transmitted noninverted */
			   ((oob_param->spectrum_inverted == false) &&
			    /* and tuner is mirroring the संकेत */
			    (mirror_freq_spect_oob))
		    )
			set_param_parameters[0] =
			    SCU_RAM_ORX_RF_RX_DATA_RATE_3088KBPS_INVSPEC;
		अन्यथा
			set_param_parameters[0] =
			    SCU_RAM_ORX_RF_RX_DATA_RATE_3088KBPS_REGSPEC;
		अवरोध;
	पूर्ण
	set_param_parameters[1] = (u16) (freq & 0xFFFF);
	set_param_parameters[2] = trk_filter_value;
	scu_cmd.parameter = set_param_parameters;
	scu_cmd.result_len = 1;
	scu_cmd.result = cmd_result;
	mode_index = mode_val[(set_param_parameters[0] & 0xC0) >> 6];
	rc = scu_command(dev_addr, &scu_cmd);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_TOP_COMM_KEY__A, 0xFABA, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण	/*  Write magic word to enable pdr reg ग_लिखो  */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_OOB_CRX_CFG__A, OOB_CRX_DRIVE_STRENGTH << SIO_PDR_OOB_CRX_CFG_DRIVE__B | 0x03 << SIO_PDR_OOB_CRX_CFG_MODE__B, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_PDR_OOB_DRX_CFG__A, OOB_DRX_DRIVE_STRENGTH << SIO_PDR_OOB_DRX_CFG_DRIVE__B | 0x03 << SIO_PDR_OOB_DRX_CFG_MODE__B, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_TOP_COMM_KEY__A, 0x0000, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण	/*  Write magic word to disable pdr reg ग_लिखो */

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, ORX_TOP_COMM_KEY__A, 0, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, ORX_FWP_AAG_LEN_W__A, 16000, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, ORX_FWP_AAG_THR_W__A, 40, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/* ddc */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, ORX_DDC_OFO_SET_W__A, ORX_DDC_OFO_SET_W__PRE, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/* nsu */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, ORX_NSU_AOX_LOPOW_W__A, ext_attr->oob_lo_घात, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/* initialization क्रम target mode */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_TARGET_MODE__A, SCU_RAM_ORX_TARGET_MODE_2048KBPS_SQRT, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_FREQ_GAIN_CORR__A, SCU_RAM_ORX_FREQ_GAIN_CORR_2048KBPS, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/* Reset bits क्रम timing and freq. recovery */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_RST_CPH__A, 0x0001, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_RST_CTI__A, 0x0002, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_RST_KRN__A, 0x0004, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_RST_KRP__A, 0x0008, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/* AGN_LOCK = अणु2048>>3, -2048, 8, -8, 0, 1पूर्ण; */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_AGN_LOCK_TH__A, 2048 >> 3, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_AGN_LOCK_TOTH__A, (u16)(-2048), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_AGN_ONLOCK_TTH__A, 8, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_AGN_UNLOCK_TTH__A, (u16)(-8), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_AGN_LOCK_MASK__A, 1, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/* DGN_LOCK = अणु10, -2048, 8, -8, 0, 1<<1पूर्ण; */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_DGN_LOCK_TH__A, 10, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_DGN_LOCK_TOTH__A, (u16)(-2048), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_DGN_ONLOCK_TTH__A, 8, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_DGN_UNLOCK_TTH__A, (u16)(-8), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_DGN_LOCK_MASK__A, 1 << 1, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/* FRQ_LOCK = अणु15,-2048, 8, -8, 0, 1<<2पूर्ण; */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_FRQ_LOCK_TH__A, 17, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_FRQ_LOCK_TOTH__A, (u16)(-2048), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_FRQ_ONLOCK_TTH__A, 8, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_FRQ_UNLOCK_TTH__A, (u16)(-8), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_FRQ_LOCK_MASK__A, 1 << 2, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/* PHA_LOCK = अणु5000, -2048, 8, -8, 0, 1<<3पूर्ण; */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_PHA_LOCK_TH__A, 3000, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_PHA_LOCK_TOTH__A, (u16)(-2048), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_PHA_ONLOCK_TTH__A, 8, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_PHA_UNLOCK_TTH__A, (u16)(-8), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_PHA_LOCK_MASK__A, 1 << 3, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/* TIM_LOCK = अणु300,      -2048, 8, -8, 0, 1<<4पूर्ण; */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_TIM_LOCK_TH__A, 400, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_TIM_LOCK_TOTH__A, (u16)(-2048), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_TIM_ONLOCK_TTH__A, 8, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_TIM_UNLOCK_TTH__A, (u16)(-8), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_TIM_LOCK_MASK__A, 1 << 4, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/* EQU_LOCK = अणु20,      -2048, 8, -8, 0, 1<<5पूर्ण; */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_EQU_LOCK_TH__A, 20, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_EQU_LOCK_TOTH__A, (u16)(-2048), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_EQU_ONLOCK_TTH__A, 4, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_EQU_UNLOCK_TTH__A, (u16)(-4), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_ORX_EQU_LOCK_MASK__A, 1 << 5, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/* PRE-Filter coefficients (PFI) */
	rc = drxdap_fasi_ग_लिखो_block(dev_addr, ORX_FWP_PFI_A_W__A, माप(pfi_coeffs[mode_index]), ((u8 *)pfi_coeffs[mode_index]), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, ORX_TOP_MDE_W__A, mode_index, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/* NYQUIST-Filter coefficients (NYQ) */
	क्रम (i = 0; i < (NYQFILTERLEN + 1) / 2; i++) अणु
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, ORX_FWP_NYQ_ADR_W__A, i, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, ORX_FWP_NYQ_COF_RW__A, nyquist_coeffs[mode_index][i], 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, ORX_FWP_NYQ_ADR_W__A, 31, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, ORX_COMM_EXEC__A, ORX_COMM_EXEC_ACTIVE, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	/********/
	/* Start */
	/********/
	scu_cmd.command = SCU_RAM_COMMAND_STANDARD_OOB
	    | SCU_RAM_COMMAND_CMD_DEMOD_START;
	scu_cmd.parameter_len = 0;
	scu_cmd.result_len = 1;
	scu_cmd.result = cmd_result;
	rc = scu_command(dev_addr, &scu_cmd);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = set_orx_nsu_aox(demod, true);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, ORX_NSU_AOX_STHR_W__A, ext_attr->oob_pre_saw, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	ext_attr->oob_घातer_on = true;

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*============================================================================*/
/*==                     END OOB DATAPATH FUNCTIONS                         ==*/
/*============================================================================*/

/*=============================================================================
  ===== MC command related functions ==========================================
  ===========================================================================*/

/*=============================================================================
  ===== ctrl_set_channel() ==========================================================
  ===========================================================================*/
/*
* \पn पूर्णांक ctrl_set_channel()
* \मrief Select a new transmission channel.
* \param demod instance of demod.
* \param channel Poपूर्णांकer to channel data.
* \लeturn पूर्णांक.
*
* In हाल the tuner module is not used and in हाल of NTSC/FM the pogrammer
* must tune the tuner to the centre frequency of the NTSC/FM channel.
*
*/
अटल पूर्णांक
ctrl_set_channel(काष्ठा drx_demod_instance *demod, काष्ठा drx_channel *channel)
अणु
	पूर्णांक rc;
	s32 tuner_freq_offset = 0;
	काष्ठा drxj_data *ext_attr = शून्य;
	काष्ठा i2c_device_addr *dev_addr = शून्य;
	क्रमागत drx_standard standard = DRX_STANDARD_UNKNOWN;
#अगर_अघोषित DRXJ_VSB_ONLY
	u32 min_symbol_rate = 0;
	u32 max_symbol_rate = 0;
	पूर्णांक bandwidth_temp = 0;
	पूर्णांक bandwidth = 0;
#पूर्ण_अगर
   /*== check arguments ======================================================*/
	अगर ((demod == शून्य) || (channel == शून्य))
		वापस -EINVAL;

	dev_addr = demod->my_i2c_dev_addr;
	ext_attr = (काष्ठा drxj_data *) demod->my_ext_attr;
	standard = ext_attr->standard;

	/* check valid standards */
	चयन (standard) अणु
	हाल DRX_STANDARD_8VSB:
#अगर_अघोषित DRXJ_VSB_ONLY
	हाल DRX_STANDARD_ITU_A:
	हाल DRX_STANDARD_ITU_B:
	हाल DRX_STANDARD_ITU_C:
#पूर्ण_अगर /* DRXJ_VSB_ONLY */
		अवरोध;
	हाल DRX_STANDARD_UNKNOWN:
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* check bandwidth QAM annex B, NTSC and 8VSB */
	अगर ((standard == DRX_STANDARD_ITU_B) ||
	    (standard == DRX_STANDARD_8VSB) ||
	    (standard == DRX_STANDARD_NTSC)) अणु
		चयन (channel->bandwidth) अणु
		हाल DRX_BANDWIDTH_6MHZ:
		हाल DRX_BANDWIDTH_UNKNOWN:
			channel->bandwidth = DRX_BANDWIDTH_6MHZ;
			अवरोध;
		हाल DRX_BANDWIDTH_8MHZ:
		हाल DRX_BANDWIDTH_7MHZ:
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* For QAM annex A and annex C:
	   -check symbolrate and स्थिरellation
	   -derive bandwidth from symbolrate (input bandwidth is ignored)
	 */
#अगर_अघोषित DRXJ_VSB_ONLY
	अगर ((standard == DRX_STANDARD_ITU_A) ||
	    (standard == DRX_STANDARD_ITU_C)) अणु
		काष्ठा drxuio_cfg uio_cfg = अणु DRX_UIO1, DRX_UIO_MODE_FIRMWARE_SAW पूर्ण;
		पूर्णांक bw_rolloff_factor = 0;

		bw_rolloff_factor = (standard == DRX_STANDARD_ITU_A) ? 115 : 113;
		min_symbol_rate = DRXJ_QAM_SYMBOLRATE_MIN;
		max_symbol_rate = DRXJ_QAM_SYMBOLRATE_MAX;
		/* config SMA_TX pin to SAW चयन mode */
		rc = ctrl_set_uio_cfg(demod, &uio_cfg);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण

		अगर (channel->symbolrate < min_symbol_rate ||
		    channel->symbolrate > max_symbol_rate) अणु
			वापस -EINVAL;
		पूर्ण

		चयन (channel->स्थिरellation) अणु
		हाल DRX_CONSTELLATION_QAM16:
		हाल DRX_CONSTELLATION_QAM32:
		हाल DRX_CONSTELLATION_QAM64:
		हाल DRX_CONSTELLATION_QAM128:
		हाल DRX_CONSTELLATION_QAM256:
			bandwidth_temp = channel->symbolrate * bw_rolloff_factor;
			bandwidth = bandwidth_temp / 100;

			अगर ((bandwidth_temp % 100) >= 50)
				bandwidth++;

			अगर (bandwidth <= 6100000) अणु
				channel->bandwidth = DRX_BANDWIDTH_6MHZ;
			पूर्ण अन्यथा अगर ((bandwidth > 6100000)
				   && (bandwidth <= 7100000)) अणु
				channel->bandwidth = DRX_BANDWIDTH_7MHZ;
			पूर्ण अन्यथा अगर (bandwidth > 7100000) अणु
				channel->bandwidth = DRX_BANDWIDTH_8MHZ;
			पूर्ण
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* For QAM annex B:
	   -check स्थिरellation
	 */
	अगर (standard == DRX_STANDARD_ITU_B) अणु
		चयन (channel->स्थिरellation) अणु
		हाल DRX_CONSTELLATION_AUTO:
		हाल DRX_CONSTELLATION_QAM256:
		हाल DRX_CONSTELLATION_QAM64:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		चयन (channel->पूर्णांकerleavemode) अणु
		हाल DRX_INTERLEAVEMODE_I128_J1:
		हाल DRX_INTERLEAVEMODE_I128_J1_V2:
		हाल DRX_INTERLEAVEMODE_I128_J2:
		हाल DRX_INTERLEAVEMODE_I64_J2:
		हाल DRX_INTERLEAVEMODE_I128_J3:
		हाल DRX_INTERLEAVEMODE_I32_J4:
		हाल DRX_INTERLEAVEMODE_I128_J4:
		हाल DRX_INTERLEAVEMODE_I16_J8:
		हाल DRX_INTERLEAVEMODE_I128_J5:
		हाल DRX_INTERLEAVEMODE_I8_J16:
		हाल DRX_INTERLEAVEMODE_I128_J6:
		हाल DRX_INTERLEAVEMODE_I128_J7:
		हाल DRX_INTERLEAVEMODE_I128_J8:
		हाल DRX_INTERLEAVEMODE_I12_J17:
		हाल DRX_INTERLEAVEMODE_I5_J4:
		हाल DRX_INTERLEAVEMODE_B52_M240:
		हाल DRX_INTERLEAVEMODE_B52_M720:
		हाल DRX_INTERLEAVEMODE_UNKNOWN:
		हाल DRX_INTERLEAVEMODE_AUTO:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर ((ext_attr->uio_sma_tx_mode) == DRX_UIO_MODE_FIRMWARE_SAW) अणु
		/* SAW SW, user UIO is used क्रम चयनable SAW */
		काष्ठा drxuio_data uio1 = अणु DRX_UIO1, false पूर्ण;

		चयन (channel->bandwidth) अणु
		हाल DRX_BANDWIDTH_8MHZ:
			uio1.value = true;
			अवरोध;
		हाल DRX_BANDWIDTH_7MHZ:
			uio1.value = false;
			अवरोध;
		हाल DRX_BANDWIDTH_6MHZ:
			uio1.value = false;
			अवरोध;
		हाल DRX_BANDWIDTH_UNKNOWN:
		शेष:
			वापस -EINVAL;
		पूर्ण

		rc = ctrl_uio_ग_लिखो(demod, &uio1);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* DRXJ_VSB_ONLY */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_COMM_EXEC__A, SCU_COMM_EXEC_ACTIVE, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	tuner_freq_offset = 0;

   /*== Setup demod क्रम specअगरic standard ====================================*/
	चयन (standard) अणु
	हाल DRX_STANDARD_8VSB:
		अगर (channel->mirror == DRX_MIRROR_AUTO)
			ext_attr->mirror = DRX_MIRROR_NO;
		अन्यथा
			ext_attr->mirror = channel->mirror;
		rc = set_vsb(demod);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = set_frequency(demod, channel, tuner_freq_offset);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		अवरोध;
#अगर_अघोषित DRXJ_VSB_ONLY
	हाल DRX_STANDARD_ITU_A:
	हाल DRX_STANDARD_ITU_B:
	हाल DRX_STANDARD_ITU_C:
		rc = set_qam_channel(demod, channel, tuner_freq_offset);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		अवरोध;
#पूर्ण_अगर
	हाल DRX_STANDARD_UNKNOWN:
	शेष:
		वापस -EIO;
	पूर्ण

	/* flag the packet error counter reset */
	ext_attr->reset_pkt_err_acc = true;

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*=============================================================================
  ===== SigQuality() ==========================================================
  ===========================================================================*/

/*
* \पn पूर्णांक ctrl_sig_quality()
* \मrief Retrieve संकेत quality क्रमm device.
* \param devmod Poपूर्णांकer to demodulator instance.
* \param sig_quality Poपूर्णांकer to संकेत quality data.
* \लeturn पूर्णांक.
* \लetval 0 sig_quality contains valid data.
* \लetval -EINVAL sig_quality is शून्य.
* \लetval -EIO Erroneous data, sig_quality contains invalid data.

*/
अटल पूर्णांक
ctrl_sig_quality(काष्ठा drx_demod_instance *demod,
		 क्रमागत drx_lock_status lock_status)
अणु
	काष्ठा i2c_device_addr *dev_addr = demod->my_i2c_dev_addr;
	काष्ठा drxj_data *ext_attr = demod->my_ext_attr;
	काष्ठा drx39xxj_state *state = dev_addr->user_data;
	काष्ठा dtv_frontend_properties *p = &state->frontend.dtv_property_cache;
	क्रमागत drx_standard standard = ext_attr->standard;
	पूर्णांक rc;
	u32 ber, cnt, err, pkt;
	u16 mer, strength = 0;

	rc = get_sig_strength(demod, &strength);
	अगर (rc < 0) अणु
		pr_err("error getting signal strength %d\n", rc);
		p->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण अन्यथा अणु
		p->strength.stat[0].scale = FE_SCALE_RELATIVE;
		p->strength.stat[0].uvalue = 65535UL *  strength/ 100;
	पूर्ण

	चयन (standard) अणु
	हाल DRX_STANDARD_8VSB:
#अगर_घोषित DRXJ_SIGNAL_ACCUM_ERR
		rc = get_acc_pkt_err(demod, &pkt);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
#पूर्ण_अगर
		अगर (lock_status != DRXJ_DEMOD_LOCK && lock_status != DRX_LOCKED) अणु
			p->pre_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
			p->pre_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
			p->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
			p->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
			p->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
			p->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
			p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		पूर्ण अन्यथा अणु
			rc = get_vsb_post_rs_pck_err(dev_addr, &err, &pkt);
			अगर (rc != 0) अणु
				pr_err("error %d getting UCB\n", rc);
				p->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
			पूर्ण अन्यथा अणु
				p->block_error.stat[0].scale = FE_SCALE_COUNTER;
				p->block_error.stat[0].uvalue += err;
				p->block_count.stat[0].scale = FE_SCALE_COUNTER;
				p->block_count.stat[0].uvalue += pkt;
			पूर्ण

			/* PostViterbi is compute in steps of 10^(-6) */
			rc = get_vs_bpre_viterbi_ber(dev_addr, &ber, &cnt);
			अगर (rc != 0) अणु
				pr_err("error %d getting pre-ber\n", rc);
				p->pre_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
			पूर्ण अन्यथा अणु
				p->pre_bit_error.stat[0].scale = FE_SCALE_COUNTER;
				p->pre_bit_error.stat[0].uvalue += ber;
				p->pre_bit_count.stat[0].scale = FE_SCALE_COUNTER;
				p->pre_bit_count.stat[0].uvalue += cnt;
			पूर्ण

			rc = get_vs_bpost_viterbi_ber(dev_addr, &ber, &cnt);
			अगर (rc != 0) अणु
				pr_err("error %d getting post-ber\n", rc);
				p->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
			पूर्ण अन्यथा अणु
				p->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
				p->post_bit_error.stat[0].uvalue += ber;
				p->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
				p->post_bit_count.stat[0].uvalue += cnt;
			पूर्ण
			rc = get_vsbmer(dev_addr, &mer);
			अगर (rc != 0) अणु
				pr_err("error %d getting MER\n", rc);
				p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
			पूर्ण अन्यथा अणु
				p->cnr.stat[0].svalue = mer * 100;
				p->cnr.stat[0].scale = FE_SCALE_DECIBEL;
			पूर्ण
		पूर्ण
		अवरोध;
#अगर_अघोषित DRXJ_VSB_ONLY
	हाल DRX_STANDARD_ITU_A:
	हाल DRX_STANDARD_ITU_B:
	हाल DRX_STANDARD_ITU_C:
		rc = ctrl_get_qam_sig_quality(demod);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		अवरोध;
#पूर्ण_अगर
	शेष:
		वापस -EIO;
	पूर्ण

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*============================================================================*/

/*
* \पn पूर्णांक ctrl_lock_status()
* \मrief Retrieve lock status .
* \param dev_addr Poपूर्णांकer to demodulator device address.
* \param lock_stat Poपूर्णांकer to lock status काष्ठाure.
* \लeturn पूर्णांक.
*
*/
अटल पूर्णांक
ctrl_lock_status(काष्ठा drx_demod_instance *demod, क्रमागत drx_lock_status *lock_stat)
अणु
	क्रमागत drx_standard standard = DRX_STANDARD_UNKNOWN;
	काष्ठा drxj_data *ext_attr = शून्य;
	काष्ठा i2c_device_addr *dev_addr = शून्य;
	काष्ठा drxjscu_cmd cmd_scu = अणु /* command      */ 0,
		/* parameter_len */ 0,
		/* result_len    */ 0,
		/* *parameter   */ शून्य,
		/* *result      */ शून्य
	पूर्ण;
	पूर्णांक rc;
	u16 cmd_result[2] = अणु 0, 0 पूर्ण;
	u16 demod_lock = SCU_RAM_PARAM_1_RES_DEMOD_GET_LOCK_DEMOD_LOCKED;

	/* check arguments */
	अगर ((demod == शून्य) || (lock_stat == शून्य))
		वापस -EINVAL;

	dev_addr = demod->my_i2c_dev_addr;
	ext_attr = (काष्ठा drxj_data *) demod->my_ext_attr;
	standard = ext_attr->standard;

	*lock_stat = DRX_NOT_LOCKED;

	/* define the SCU command code */
	चयन (standard) अणु
	हाल DRX_STANDARD_8VSB:
		cmd_scu.command = SCU_RAM_COMMAND_STANDARD_VSB |
		    SCU_RAM_COMMAND_CMD_DEMOD_GET_LOCK;
		demod_lock |= 0x6;
		अवरोध;
#अगर_अघोषित DRXJ_VSB_ONLY
	हाल DRX_STANDARD_ITU_A:
	हाल DRX_STANDARD_ITU_B:
	हाल DRX_STANDARD_ITU_C:
		cmd_scu.command = SCU_RAM_COMMAND_STANDARD_QAM |
		    SCU_RAM_COMMAND_CMD_DEMOD_GET_LOCK;
		अवरोध;
#पूर्ण_अगर
	हाल DRX_STANDARD_UNKNOWN:
	शेष:
		वापस -EIO;
	पूर्ण

	/* define the SCU command parameters and execute the command */
	cmd_scu.parameter_len = 0;
	cmd_scu.result_len = 2;
	cmd_scu.parameter = शून्य;
	cmd_scu.result = cmd_result;
	rc = scu_command(dev_addr, &cmd_scu);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/* set the lock status */
	अगर (cmd_scu.result[1] < demod_lock) अणु
		/* 0x0000 NOT LOCKED */
		*lock_stat = DRX_NOT_LOCKED;
	पूर्ण अन्यथा अगर (cmd_scu.result[1] < SCU_RAM_PARAM_1_RES_DEMOD_GET_LOCK_LOCKED) अणु
		*lock_stat = DRXJ_DEMOD_LOCK;
	पूर्ण अन्यथा अगर (cmd_scu.result[1] <
		   SCU_RAM_PARAM_1_RES_DEMOD_GET_LOCK_NEVER_LOCK) अणु
		/* 0x8000 DEMOD + FEC LOCKED (प्रणाली lock) */
		*lock_stat = DRX_LOCKED;
	पूर्ण अन्यथा अणु
		/* 0xC000 NEVER LOCKED */
		/* (प्रणाली will never be able to lock to the संकेत) */
		*lock_stat = DRX_NEVER_LOCK;
	पूर्ण

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*============================================================================*/

/*
* \पn पूर्णांक ctrl_set_standard()
* \मrief Set modulation standard to be used.
* \param standard Modulation standard.
* \लeturn पूर्णांक.
*
* Setup stuff क्रम the desired demodulation standard.
* Disable and घातer करोwn the previous selected demodulation standard
*
*/
अटल पूर्णांक
ctrl_set_standard(काष्ठा drx_demod_instance *demod, क्रमागत drx_standard *standard)
अणु
	काष्ठा drxj_data *ext_attr = शून्य;
	पूर्णांक rc;
	क्रमागत drx_standard prev_standard;

	/* check arguments */
	अगर ((standard == शून्य) || (demod == शून्य))
		वापस -EINVAL;

	ext_attr = (काष्ठा drxj_data *) demod->my_ext_attr;
	prev_standard = ext_attr->standard;

	/*
	   Stop and घातer करोwn previous standard
	 */
	चयन (prev_standard) अणु
#अगर_अघोषित DRXJ_VSB_ONLY
	हाल DRX_STANDARD_ITU_A:
	हाल DRX_STANDARD_ITU_B:
	हाल DRX_STANDARD_ITU_C:
		rc = घातer_करोwn_qam(demod, false);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		अवरोध;
#पूर्ण_अगर
	हाल DRX_STANDARD_8VSB:
		rc = घातer_करोwn_vsb(demod, false);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		अवरोध;
	हाल DRX_STANDARD_UNKNOWN:
		/* Do nothing */
		अवरोध;
	हाल DRX_STANDARD_AUTO:
	शेष:
		वापस -EINVAL;
	पूर्ण

	/*
	   Initialize channel independent रेजिस्टरs
	   Power up new standard
	 */
	ext_attr->standard = *standard;

	चयन (*standard) अणु
#अगर_अघोषित DRXJ_VSB_ONLY
	हाल DRX_STANDARD_ITU_A:
	हाल DRX_STANDARD_ITU_B:
	हाल DRX_STANDARD_ITU_C:
		करो अणु
			u16 dummy;
			rc = drxj_dap_पढ़ो_reg16(demod->my_i2c_dev_addr, SCU_RAM_VERSION_HI__A, &dummy, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
		पूर्ण जबतक (0);
		अवरोध;
#पूर्ण_अगर
	हाल DRX_STANDARD_8VSB:
		rc = set_vsb_leak_n_gain(demod);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		अवरोध;
	शेष:
		ext_attr->standard = DRX_STANDARD_UNKNOWN;
		वापस -EINVAL;
	पूर्ण

	वापस 0;
rw_error:
	/* Don't know what the standard is now ... try again */
	ext_attr->standard = DRX_STANDARD_UNKNOWN;
	वापस rc;
पूर्ण

/*============================================================================*/

अटल व्योम drxj_reset_mode(काष्ठा drxj_data *ext_attr)
अणु
	/* Initialize शेष AFE configuration क्रम QAM */
	अगर (ext_attr->has_lna) अणु
		/* IF AGC off, PGA active */
#अगर_अघोषित DRXJ_VSB_ONLY
		ext_attr->qam_अगर_agc_cfg.standard = DRX_STANDARD_ITU_B;
		ext_attr->qam_अगर_agc_cfg.ctrl_mode = DRX_AGC_CTRL_OFF;
		ext_attr->qam_pga_cfg = 140 + (11 * 13);
#पूर्ण_अगर
		ext_attr->vsb_अगर_agc_cfg.standard = DRX_STANDARD_8VSB;
		ext_attr->vsb_अगर_agc_cfg.ctrl_mode = DRX_AGC_CTRL_OFF;
		ext_attr->vsb_pga_cfg = 140 + (11 * 13);
	पूर्ण अन्यथा अणु
		/* IF AGC on, PGA not active */
#अगर_अघोषित DRXJ_VSB_ONLY
		ext_attr->qam_अगर_agc_cfg.standard = DRX_STANDARD_ITU_B;
		ext_attr->qam_अगर_agc_cfg.ctrl_mode = DRX_AGC_CTRL_AUTO;
		ext_attr->qam_अगर_agc_cfg.min_output_level = 0;
		ext_attr->qam_अगर_agc_cfg.max_output_level = 0x7FFF;
		ext_attr->qam_अगर_agc_cfg.speed = 3;
		ext_attr->qam_अगर_agc_cfg.top = 1297;
		ext_attr->qam_pga_cfg = 140;
#पूर्ण_अगर
		ext_attr->vsb_अगर_agc_cfg.standard = DRX_STANDARD_8VSB;
		ext_attr->vsb_अगर_agc_cfg.ctrl_mode = DRX_AGC_CTRL_AUTO;
		ext_attr->vsb_अगर_agc_cfg.min_output_level = 0;
		ext_attr->vsb_अगर_agc_cfg.max_output_level = 0x7FFF;
		ext_attr->vsb_अगर_agc_cfg.speed = 3;
		ext_attr->vsb_अगर_agc_cfg.top = 1024;
		ext_attr->vsb_pga_cfg = 140;
	पूर्ण
	/* TODO: हटाओ min_output_level and max_output_level क्रम both QAM and VSB after */
	/* mc has not used them */
#अगर_अघोषित DRXJ_VSB_ONLY
	ext_attr->qam_rf_agc_cfg.standard = DRX_STANDARD_ITU_B;
	ext_attr->qam_rf_agc_cfg.ctrl_mode = DRX_AGC_CTRL_AUTO;
	ext_attr->qam_rf_agc_cfg.min_output_level = 0;
	ext_attr->qam_rf_agc_cfg.max_output_level = 0x7FFF;
	ext_attr->qam_rf_agc_cfg.speed = 3;
	ext_attr->qam_rf_agc_cfg.top = 9500;
	ext_attr->qam_rf_agc_cfg.cut_off_current = 4000;
	ext_attr->qam_pre_saw_cfg.standard = DRX_STANDARD_ITU_B;
	ext_attr->qam_pre_saw_cfg.reference = 0x07;
	ext_attr->qam_pre_saw_cfg.use_pre_saw = true;
#पूर्ण_अगर
	/* Initialize शेष AFE configuration क्रम VSB */
	ext_attr->vsb_rf_agc_cfg.standard = DRX_STANDARD_8VSB;
	ext_attr->vsb_rf_agc_cfg.ctrl_mode = DRX_AGC_CTRL_AUTO;
	ext_attr->vsb_rf_agc_cfg.min_output_level = 0;
	ext_attr->vsb_rf_agc_cfg.max_output_level = 0x7FFF;
	ext_attr->vsb_rf_agc_cfg.speed = 3;
	ext_attr->vsb_rf_agc_cfg.top = 9500;
	ext_attr->vsb_rf_agc_cfg.cut_off_current = 4000;
	ext_attr->vsb_pre_saw_cfg.standard = DRX_STANDARD_8VSB;
	ext_attr->vsb_pre_saw_cfg.reference = 0x07;
	ext_attr->vsb_pre_saw_cfg.use_pre_saw = true;
पूर्ण

/*
* \पn पूर्णांक ctrl_घातer_mode()
* \मrief Set the घातer mode of the device to the specअगरied घातer mode
* \param demod Poपूर्णांकer to demodulator instance.
* \param mode  Poपूर्णांकer to new घातer mode.
* \लeturn पूर्णांक.
* \लetval 0          Success
* \लetval -EIO       I2C error or other failure
* \लetval -EINVAL Invalid mode argument.
*
*
*/
अटल पूर्णांक
ctrl_घातer_mode(काष्ठा drx_demod_instance *demod, क्रमागत drx_घातer_mode *mode)
अणु
	काष्ठा drx_common_attr *common_attr = (काष्ठा drx_common_attr *) शून्य;
	काष्ठा drxj_data *ext_attr = (काष्ठा drxj_data *) शून्य;
	काष्ठा i2c_device_addr *dev_addr = (काष्ठा i2c_device_addr *)शून्य;
	पूर्णांक rc;
	u16 sio_cc_pwd_mode = 0;

	common_attr = (काष्ठा drx_common_attr *) demod->my_common_attr;
	ext_attr = (काष्ठा drxj_data *) demod->my_ext_attr;
	dev_addr = demod->my_i2c_dev_addr;

	/* Check arguments */
	अगर (mode == शून्य)
		वापस -EINVAL;

	/* If alपढ़ोy in requested घातer mode, करो nothing */
	अगर (common_attr->current_घातer_mode == *mode)
		वापस 0;

	चयन (*mode) अणु
	हाल DRX_POWER_UP:
	हाल DRXJ_POWER_DOWN_MAIN_PATH:
		sio_cc_pwd_mode = SIO_CC_PWD_MODE_LEVEL_NONE;
		अवरोध;
	हाल DRXJ_POWER_DOWN_CORE:
		sio_cc_pwd_mode = SIO_CC_PWD_MODE_LEVEL_CLOCK;
		अवरोध;
	हाल DRXJ_POWER_DOWN_PLL:
		sio_cc_pwd_mode = SIO_CC_PWD_MODE_LEVEL_PLL;
		अवरोध;
	हाल DRX_POWER_DOWN:
		sio_cc_pwd_mode = SIO_CC_PWD_MODE_LEVEL_OSC;
		अवरोध;
	शेष:
		/* Unknow sleep mode */
		वापस -EINVAL;
	पूर्ण

	/* Check अगर device needs to be घातered up */
	अगर ((common_attr->current_घातer_mode != DRX_POWER_UP)) अणु
		rc = घातer_up_device(demod);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
	पूर्ण

	अगर (*mode == DRX_POWER_UP) अणु
		/* Restore analog & pin configuration */

		/* Initialize शेष AFE configuration क्रम VSB */
		drxj_reset_mode(ext_attr);
	पूर्ण अन्यथा अणु
		/* Power करोwn to requested mode */
		/* Backup some रेजिस्टर settings */
		/* Set pins with possible pull-ups connected to them in input mode */
		/* Analog घातer करोwn */
		/* ADC घातer करोwn */
		/* Power करोwn device */
		/* stop all comm_exec */
		/*
		   Stop and घातer करोwn previous standard
		 */

		चयन (ext_attr->standard) अणु
		हाल DRX_STANDARD_ITU_A:
		हाल DRX_STANDARD_ITU_B:
		हाल DRX_STANDARD_ITU_C:
			rc = घातer_करोwn_qam(demod, true);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			अवरोध;
		हाल DRX_STANDARD_8VSB:
			rc = घातer_करोwn_vsb(demod, true);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			अवरोध;
		हाल DRX_STANDARD_PAL_SECAM_BG:
		हाल DRX_STANDARD_PAL_SECAM_DK:
		हाल DRX_STANDARD_PAL_SECAM_I:
		हाल DRX_STANDARD_PAL_SECAM_L:
		हाल DRX_STANDARD_PAL_SECAM_LP:
		हाल DRX_STANDARD_NTSC:
		हाल DRX_STANDARD_FM:
			rc = घातer_करोwn_atv(demod, ext_attr->standard, true);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
			अवरोध;
		हाल DRX_STANDARD_UNKNOWN:
			/* Do nothing */
			अवरोध;
		हाल DRX_STANDARD_AUTO:
		शेष:
			वापस -EIO;
		पूर्ण
		ext_attr->standard = DRX_STANDARD_UNKNOWN;
	पूर्ण

	अगर (*mode != DRXJ_POWER_DOWN_MAIN_PATH) अणु
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_CC_PWD_MODE__A, sio_cc_pwd_mode, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_CC_UPDATE__A, SIO_CC_UPDATE_KEY, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण

		अगर ((*mode != DRX_POWER_UP)) अणु
			/* Initialize HI, wakeup key especially beक्रमe put IC to sleep */
			rc = init_hi(demod);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण

			ext_attr->hi_cfg_ctrl |= SIO_HI_RA_RAM_PAR_5_CFG_SLEEP_ZZZ;
			rc = hi_cfg_command(demod);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
		पूर्ण
	पूर्ण

	common_attr->current_घातer_mode = *mode;

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*============================================================================*/
/*== CTRL Set/Get Config related functions ===================================*/
/*============================================================================*/

/*
* \पn पूर्णांक ctrl_set_cfg_pre_saw()
* \मrief Set Pre-saw reference.
* \param demod demod instance
* \param u16 *
* \लeturn पूर्णांक.
*
* Check arguments
* Dispatch handling to standard specअगरic function.
*
*/
अटल पूर्णांक
ctrl_set_cfg_pre_saw(काष्ठा drx_demod_instance *demod, काष्ठा drxj_cfg_pre_saw *pre_saw)
अणु
	काष्ठा i2c_device_addr *dev_addr = शून्य;
	काष्ठा drxj_data *ext_attr = शून्य;
	पूर्णांक rc;

	dev_addr = demod->my_i2c_dev_addr;
	ext_attr = (काष्ठा drxj_data *) demod->my_ext_attr;

	/* check arguments */
	अगर ((pre_saw == शून्य) || (pre_saw->reference > IQM_AF_PDREF__M)
	    ) अणु
		वापस -EINVAL;
	पूर्ण

	/* Only अगर standard is currently active */
	अगर ((ext_attr->standard == pre_saw->standard) ||
	    (DRXJ_ISQAMSTD(ext_attr->standard) &&
	     DRXJ_ISQAMSTD(pre_saw->standard)) ||
	    (DRXJ_ISATVSTD(ext_attr->standard) &&
	     DRXJ_ISATVSTD(pre_saw->standard))) अणु
		rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_AF_PDREF__A, pre_saw->reference, 0);
		अगर (rc != 0) अणु
			pr_err("error %d\n", rc);
			जाओ rw_error;
		पूर्ण
	पूर्ण

	/* Store pre-saw settings */
	चयन (pre_saw->standard) अणु
	हाल DRX_STANDARD_8VSB:
		ext_attr->vsb_pre_saw_cfg = *pre_saw;
		अवरोध;
#अगर_अघोषित DRXJ_VSB_ONLY
	हाल DRX_STANDARD_ITU_A:
	हाल DRX_STANDARD_ITU_B:
	हाल DRX_STANDARD_ITU_C:
		ext_attr->qam_pre_saw_cfg = *pre_saw;
		अवरोध;
#पूर्ण_अगर
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*============================================================================*/

/*
* \पn पूर्णांक ctrl_set_cfg_afe_gain()
* \मrief Set AFE Gain.
* \param demod demod instance
* \param u16 *
* \लeturn पूर्णांक.
*
* Check arguments
* Dispatch handling to standard specअगरic function.
*
*/
अटल पूर्णांक
ctrl_set_cfg_afe_gain(काष्ठा drx_demod_instance *demod, काष्ठा drxj_cfg_afe_gain *afe_gain)
अणु
	काष्ठा i2c_device_addr *dev_addr = शून्य;
	काष्ठा drxj_data *ext_attr = शून्य;
	पूर्णांक rc;
	u8 gain = 0;

	/* check arguments */
	अगर (afe_gain == शून्य)
		वापस -EINVAL;

	dev_addr = demod->my_i2c_dev_addr;
	ext_attr = (काष्ठा drxj_data *) demod->my_ext_attr;

	चयन (afe_gain->standard) अणु
	हाल DRX_STANDARD_8VSB:	fallthrough;
#अगर_अघोषित DRXJ_VSB_ONLY
	हाल DRX_STANDARD_ITU_A:
	हाल DRX_STANDARD_ITU_B:
	हाल DRX_STANDARD_ITU_C:
#पूर्ण_अगर
		/* Do nothing */
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* TODO PGA gain is also written by microcode (at least by QAM and VSB)
	   So I (PJ) think पूर्णांकerface requires choice between स्वतः, user mode */

	अगर (afe_gain->gain >= 329)
		gain = 15;
	अन्यथा अगर (afe_gain->gain <= 147)
		gain = 0;
	अन्यथा
		gain = (afe_gain->gain - 140 + 6) / 13;

	/* Only अगर standard is currently active */
	अगर (ext_attr->standard == afe_gain->standard) अणु
			rc = drxj_dap_ग_लिखो_reg16(dev_addr, IQM_AF_PGA_GAIN__A, gain, 0);
			अगर (rc != 0) अणु
				pr_err("error %d\n", rc);
				जाओ rw_error;
			पूर्ण
		पूर्ण

	/* Store AFE Gain settings */
	चयन (afe_gain->standard) अणु
	हाल DRX_STANDARD_8VSB:
		ext_attr->vsb_pga_cfg = gain * 13 + 140;
		अवरोध;
#अगर_अघोषित DRXJ_VSB_ONLY
	हाल DRX_STANDARD_ITU_A:
	हाल DRX_STANDARD_ITU_B:
	हाल DRX_STANDARD_ITU_C:
		ext_attr->qam_pga_cfg = gain * 13 + 140;
		अवरोध;
#पूर्ण_अगर
	शेष:
		वापस -EIO;
	पूर्ण

	वापस 0;
rw_error:
	वापस rc;
पूर्ण

/*============================================================================*/


/*=============================================================================
===== EXPORTED FUNCTIONS ====================================================*/

अटल पूर्णांक drx_ctrl_u_code(काष्ठा drx_demod_instance *demod,
		       काष्ठा drxu_code_info *mc_info,
		       क्रमागत drxu_code_action action);
अटल पूर्णांक drxj_set_lna_state(काष्ठा drx_demod_instance *demod, bool state);

/*
* \पn drxj_खोलो()
* \मrief Open the demod instance, configure device, configure drxdriver
* \लeturn Status_t Return status.
*
* drxj_खोलो() can be called with a शून्य ucode image => no ucode upload.
* This means that drxj_खोलो() must NOT contain SCU commands or, in general,
* rely on SCU or AUD ucode to be present.
*
*/

अटल पूर्णांक drxj_खोलो(काष्ठा drx_demod_instance *demod)
अणु
	काष्ठा i2c_device_addr *dev_addr = शून्य;
	काष्ठा drxj_data *ext_attr = शून्य;
	काष्ठा drx_common_attr *common_attr = शून्य;
	u32 driver_version = 0;
	काष्ठा drxu_code_info ucode_info;
	काष्ठा drx_cfg_mpeg_output cfg_mpeg_output;
	पूर्णांक rc;
	क्रमागत drx_घातer_mode घातer_mode = DRX_POWER_UP;

	अगर ((demod == शून्य) ||
	    (demod->my_common_attr == शून्य) ||
	    (demod->my_ext_attr == शून्य) ||
	    (demod->my_i2c_dev_addr == शून्य) ||
	    (demod->my_common_attr->is_खोलोed)) अणु
		वापस -EINVAL;
	पूर्ण

	/* Check arguments */
	अगर (demod->my_ext_attr == शून्य)
		वापस -EINVAL;

	dev_addr = demod->my_i2c_dev_addr;
	ext_attr = (काष्ठा drxj_data *) demod->my_ext_attr;
	common_attr = (काष्ठा drx_common_attr *) demod->my_common_attr;

	rc = ctrl_घातer_mode(demod, &घातer_mode);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	अगर (घातer_mode != DRX_POWER_UP) अणु
		rc = -EINVAL;
		pr_err("failed to powerup device\n");
		जाओ rw_error;
	पूर्ण

	/* has to be in front of setIqmAf and setOrxNsuAox */
	rc = get_device_capabilities(demod);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/*
	 * Soft reset of sys- and osc-घड़ीकरोमुख्य
	 *
	 * HACK: On winकरोws, it ग_लिखोs a 0x07 here, instead of just 0x03.
	 * As we didn't load the firmware here yet, we should करो the same.
	 * Btw, this is coherent with DRX-K, where we send reset codes
	 * क्रम modulation (OFTM, in DRX-k), SYS and OSC घड़ी करोमुख्यs.
	 */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_CC_SOFT_RST__A, (0x04 | SIO_CC_SOFT_RST_SYS__M | SIO_CC_SOFT_RST_OSC__M), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SIO_CC_UPDATE__A, SIO_CC_UPDATE_KEY, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	msleep(1);

	/* TODO first make sure that everything keeps working beक्रमe enabling this */
	/* PowerDownAnalogBlocks() */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, ATV_TOP_STDBY__A, (~ATV_TOP_STDBY_CVBS_STDBY_A2_ACTIVE) | ATV_TOP_STDBY_SIF_STDBY_STANDBY, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = set_iqm_af(demod, false);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = set_orx_nsu_aox(demod, false);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = init_hi(demod);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/* disable mpegoutput pins */
	स_नकल(&cfg_mpeg_output, &common_attr->mpeg_cfg, माप(cfg_mpeg_output));
	cfg_mpeg_output.enable_mpeg_output = false;

	rc = ctrl_set_cfg_mpeg_output(demod, &cfg_mpeg_output);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	/* Stop AUD Inक्रमm SetAudio it will need to करो all setting */
	rc = घातer_करोwn_aud(demod);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	/* Stop SCU */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_COMM_EXEC__A, SCU_COMM_EXEC_STOP, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/* Upload microcode */
	अगर (common_attr->microcode_file != शून्य) अणु
		/* Dirty trick to use common ucode upload & verअगरy,
		   pretend device is alपढ़ोy खोलो */
		common_attr->is_खोलोed = true;
		ucode_info.mc_file = common_attr->microcode_file;

		अगर (DRX_ISPOWERDOWNMODE(demod->my_common_attr->current_घातer_mode)) अणु
			pr_err("Should powerup before loading the firmware.");
			वापस -EINVAL;
		पूर्ण

		rc = drx_ctrl_u_code(demod, &ucode_info, UCODE_UPLOAD);
		अगर (rc != 0) अणु
			pr_err("error %d while uploading the firmware\n", rc);
			जाओ rw_error;
		पूर्ण
		अगर (common_attr->verअगरy_microcode == true) अणु
			rc = drx_ctrl_u_code(demod, &ucode_info, UCODE_VERIFY);
			अगर (rc != 0) अणु
				pr_err("error %d while verifying the firmware\n",
				       rc);
				जाओ rw_error;
			पूर्ण
		पूर्ण
		common_attr->is_खोलोed = false;
	पूर्ण

	/* Run SCU क्रम a little जबतक to initialize microcode version numbers */
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_COMM_EXEC__A, SCU_COMM_EXEC_ACTIVE, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/* Initialize scan समयout */
	common_attr->scan_demod_lock_समयout = DRXJ_SCAN_TIMEOUT;
	common_attr->scan_desired_lock = DRX_LOCKED;

	drxj_reset_mode(ext_attr);
	ext_attr->standard = DRX_STANDARD_UNKNOWN;

	rc = smart_ant_init(demod);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/* Stamp driver version number in SCU data RAM in BCD code
	   Done to enable field application engineers to retrieve drxdriver version
	   via I2C from SCU RAM
	 */
	driver_version = (VERSION_MAJOR / 100) % 10;
	driver_version <<= 4;
	driver_version += (VERSION_MAJOR / 10) % 10;
	driver_version <<= 4;
	driver_version += (VERSION_MAJOR % 10);
	driver_version <<= 4;
	driver_version += (VERSION_MINOR % 10);
	driver_version <<= 4;
	driver_version += (VERSION_PATCH / 1000) % 10;
	driver_version <<= 4;
	driver_version += (VERSION_PATCH / 100) % 10;
	driver_version <<= 4;
	driver_version += (VERSION_PATCH / 10) % 10;
	driver_version <<= 4;
	driver_version += (VERSION_PATCH % 10);
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_DRIVER_VER_HI__A, (u16)(driver_version >> 16), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_RAM_DRIVER_VER_LO__A, (u16)(driver_version & 0xFFFF), 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = ctrl_set_oob(demod, शून्य);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	/* refresh the audio data काष्ठाure with शेष */
	ext_attr->aud_data = drxj_शेष_aud_data_g;

	demod->my_common_attr->is_खोलोed = true;
	drxj_set_lna_state(demod, false);
	वापस 0;
rw_error:
	common_attr->is_खोलोed = false;
	वापस rc;
पूर्ण

/*============================================================================*/
/*
* \पn drxj_बंद()
* \मrief Close the demod instance, घातer करोwn the device
* \लeturn Status_t Return status.
*
*/
अटल पूर्णांक drxj_बंद(काष्ठा drx_demod_instance *demod)
अणु
	काष्ठा i2c_device_addr *dev_addr = demod->my_i2c_dev_addr;
	पूर्णांक rc;
	क्रमागत drx_घातer_mode घातer_mode = DRX_POWER_UP;

	अगर ((demod->my_common_attr == शून्य) ||
	    (demod->my_ext_attr == शून्य) ||
	    (demod->my_i2c_dev_addr == शून्य) ||
	    (!demod->my_common_attr->is_खोलोed)) अणु
		वापस -EINVAL;
	पूर्ण

	/* घातer up */
	rc = ctrl_घातer_mode(demod, &घातer_mode);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	rc = drxj_dap_ग_लिखो_reg16(dev_addr, SCU_COMM_EXEC__A, SCU_COMM_EXEC_ACTIVE, 0);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण
	घातer_mode = DRX_POWER_DOWN;
	rc = ctrl_घातer_mode(demod, &घातer_mode);
	अगर (rc != 0) अणु
		pr_err("error %d\n", rc);
		जाओ rw_error;
	पूर्ण

	DRX_ATTR_ISOPENED(demod) = false;

	वापस 0;
rw_error:
	DRX_ATTR_ISOPENED(demod) = false;

	वापस rc;
पूर्ण

/*
 * Microcode related functions
 */

/*
 * drx_u_code_compute_crc	- Compute CRC of block of microcode data.
 * @block_data: Poपूर्णांकer to microcode data.
 * @nr_words:   Size of microcode block (number of 16 bits words).
 *
 * वापसs The computed CRC residue.
 */
अटल u16 drx_u_code_compute_crc(u8 *block_data, u16 nr_words)
अणु
	u16 i = 0;
	u16 j = 0;
	u32 crc_word = 0;
	u32 carry = 0;

	जबतक (i < nr_words) अणु
		crc_word |= (u32)be16_to_cpu(*(__be16 *)(block_data));
		क्रम (j = 0; j < 16; j++) अणु
			crc_word <<= 1;
			अगर (carry != 0)
				crc_word ^= 0x80050000UL;
			carry = crc_word & 0x80000000UL;
		पूर्ण
		i++;
		block_data += (माप(u16));
	पूर्ण
	वापस (u16)(crc_word >> 16);
पूर्ण

/*
 * drx_check_firmware - checks अगर the loaded firmware is valid
 *
 * @demod:	demod काष्ठाure
 * @mc_data:	poपूर्णांकer to the start of the firmware
 * @size:	firmware size
 */
अटल पूर्णांक drx_check_firmware(काष्ठा drx_demod_instance *demod, u8 *mc_data,
			  अचिन्हित size)
अणु
	काष्ठा drxu_code_block_hdr block_hdr;
	पूर्णांक i;
	अचिन्हित count = 2 * माप(u16);
	u32 mc_dev_type, mc_version, mc_base_version;
	u16 mc_nr_of_blks = be16_to_cpu(*(__be16 *)(mc_data + माप(u16)));

	/*
	 * Scan microcode blocks first क्रम version info
	 * and firmware check
	 */

	/* Clear version block */
	DRX_ATTR_MCRECORD(demod).aux_type = 0;
	DRX_ATTR_MCRECORD(demod).mc_dev_type = 0;
	DRX_ATTR_MCRECORD(demod).mc_version = 0;
	DRX_ATTR_MCRECORD(demod).mc_base_version = 0;

	क्रम (i = 0; i < mc_nr_of_blks; i++) अणु
		अगर (count + 3 * माप(u16) + माप(u32) > size)
			जाओ eof;

		/* Process block header */
		block_hdr.addr = be32_to_cpu(*(__be32 *)(mc_data + count));
		count += माप(u32);
		block_hdr.size = be16_to_cpu(*(__be16 *)(mc_data + count));
		count += माप(u16);
		block_hdr.flags = be16_to_cpu(*(__be16 *)(mc_data + count));
		count += माप(u16);
		block_hdr.CRC = be16_to_cpu(*(__be16 *)(mc_data + count));
		count += माप(u16);

		pr_debug("%u: addr %u, size %u, flags 0x%04x, CRC 0x%04x\n",
			count, block_hdr.addr, block_hdr.size, block_hdr.flags,
			block_hdr.CRC);

		अगर (block_hdr.flags & 0x8) अणु
			u8 *auxblk = ((व्योम *)mc_data) + block_hdr.addr;
			u16 auxtype;

			अगर (block_hdr.addr + माप(u16) > size)
				जाओ eof;

			auxtype = be16_to_cpu(*(__be16 *)(auxblk));

			/* Aux block. Check type */
			अगर (DRX_ISMCVERTYPE(auxtype)) अणु
				अगर (block_hdr.addr + 2 * माप(u16) + 2 * माप (u32) > size)
					जाओ eof;

				auxblk += माप(u16);
				mc_dev_type = be32_to_cpu(*(__be32 *)(auxblk));
				auxblk += माप(u32);
				mc_version = be32_to_cpu(*(__be32 *)(auxblk));
				auxblk += माप(u32);
				mc_base_version = be32_to_cpu(*(__be32 *)(auxblk));

				DRX_ATTR_MCRECORD(demod).aux_type = auxtype;
				DRX_ATTR_MCRECORD(demod).mc_dev_type = mc_dev_type;
				DRX_ATTR_MCRECORD(demod).mc_version = mc_version;
				DRX_ATTR_MCRECORD(demod).mc_base_version = mc_base_version;

				pr_info("Firmware dev %x, ver %x, base ver %x\n",
					mc_dev_type, mc_version, mc_base_version);

			पूर्ण
		पूर्ण अन्यथा अगर (count + block_hdr.size * माप(u16) > size)
			जाओ eof;

		count += block_hdr.size * माप(u16);
	पूर्ण
	वापस 0;
eof:
	pr_err("Firmware is truncated at pos %u/%u\n", count, size);
	वापस -EINVAL;
पूर्ण

/*
 * drx_ctrl_u_code - Handle microcode upload or verअगरy.
 * @dev_addr: Address of device.
 * @mc_info:  Poपूर्णांकer to inक्रमmation about microcode data.
 * @action:  Either UCODE_UPLOAD or UCODE_VERIFY
 *
 * This function वापसs:
 *	0:
 *		- In हाल of UCODE_UPLOAD: code is successfully uploaded.
 *               - In हाल of UCODE_VERIFY: image on device is equal to
 *		  image provided to this control function.
 *	-EIO:
 *		- In हाल of UCODE_UPLOAD: I2C error.
 *		- In हाल of UCODE_VERIFY: I2C error or image on device
 *		  is not equal to image provided to this control function.
 *	-EINVAL:
 *		- Invalid arguments.
 *		- Provided image is corrupt
 */
अटल पूर्णांक drx_ctrl_u_code(काष्ठा drx_demod_instance *demod,
		       काष्ठा drxu_code_info *mc_info,
		       क्रमागत drxu_code_action action)
अणु
	काष्ठा i2c_device_addr *dev_addr = demod->my_i2c_dev_addr;
	पूर्णांक rc;
	u16 i = 0;
	u16 mc_nr_of_blks = 0;
	u16 mc_magic_word = 0;
	स्थिर u8 *mc_data_init = शून्य;
	u8 *mc_data = शून्य;
	अचिन्हित size;
	अक्षर *mc_file;

	/* Check arguments */
	अगर (!mc_info || !mc_info->mc_file)
		वापस -EINVAL;

	mc_file = mc_info->mc_file;

	अगर (!demod->firmware) अणु
		स्थिर काष्ठा firmware *fw = शून्य;

		rc = request_firmware(&fw, mc_file, demod->i2c->dev.parent);
		अगर (rc < 0) अणु
			pr_err("Couldn't read firmware %s\n", mc_file);
			वापस rc;
		पूर्ण
		demod->firmware = fw;

		अगर (demod->firmware->size < 2 * माप(u16)) अणु
			rc = -EINVAL;
			pr_err("Firmware is too short!\n");
			जाओ release;
		पूर्ण

		pr_info("Firmware %s, size %zu\n",
			mc_file, demod->firmware->size);
	पूर्ण

	mc_data_init = demod->firmware->data;
	size = demod->firmware->size;

	mc_data = (व्योम *)mc_data_init;
	/* Check data */
	mc_magic_word = be16_to_cpu(*(__be16 *)(mc_data));
	mc_data += माप(u16);
	mc_nr_of_blks = be16_to_cpu(*(__be16 *)(mc_data));
	mc_data += माप(u16);

	अगर ((mc_magic_word != DRX_UCODE_MAGIC_WORD) || (mc_nr_of_blks == 0)) अणु
		rc = -EINVAL;
		pr_err("Firmware magic word doesn't match\n");
		जाओ release;
	पूर्ण

	अगर (action == UCODE_UPLOAD) अणु
		rc = drx_check_firmware(demod, (u8 *)mc_data_init, size);
		अगर (rc)
			जाओ release;
		pr_info("Uploading firmware %s\n", mc_file);
	पूर्ण अन्यथा अणु
		pr_info("Verifying if firmware upload was ok.\n");
	पूर्ण

	/* Process microcode blocks */
	क्रम (i = 0; i < mc_nr_of_blks; i++) अणु
		काष्ठा drxu_code_block_hdr block_hdr;
		u16 mc_block_nr_bytes = 0;

		/* Process block header */
		block_hdr.addr = be32_to_cpu(*(__be32 *)(mc_data));
		mc_data += माप(u32);
		block_hdr.size = be16_to_cpu(*(__be16 *)(mc_data));
		mc_data += माप(u16);
		block_hdr.flags = be16_to_cpu(*(__be16 *)(mc_data));
		mc_data += माप(u16);
		block_hdr.CRC = be16_to_cpu(*(__be16 *)(mc_data));
		mc_data += माप(u16);

		pr_debug("%zd: addr %u, size %u, flags 0x%04x, CRC 0x%04x\n",
			(mc_data - mc_data_init), block_hdr.addr,
			 block_hdr.size, block_hdr.flags, block_hdr.CRC);

		/* Check block header on:
		   - data larger than 64Kb
		   - अगर CRC enabled check CRC
		 */
		अगर ((block_hdr.size > 0x7FFF) ||
		    (((block_hdr.flags & DRX_UCODE_CRC_FLAG) != 0) &&
		     (block_hdr.CRC != drx_u_code_compute_crc(mc_data, block_hdr.size)))
		    ) अणु
			/* Wrong data ! */
			rc = -EINVAL;
			pr_err("firmware CRC is wrong\n");
			जाओ release;
		पूर्ण

		अगर (!block_hdr.size)
			जारी;

		mc_block_nr_bytes = block_hdr.size * ((u16) माप(u16));

		/* Perक्रमm the desired action */
		चयन (action) अणु
		हाल UCODE_UPLOAD:	/* Upload microcode */
			अगर (drxdap_fasi_ग_लिखो_block(dev_addr,
							block_hdr.addr,
							mc_block_nr_bytes,
							mc_data, 0x0000)) अणु
				rc = -EIO;
				pr_err("error writing firmware at pos %zd\n",
				       mc_data - mc_data_init);
				जाओ release;
			पूर्ण
			अवरोध;
		हाल UCODE_VERIFY: अणु	/* Verअगरy uploaded microcode */
			पूर्णांक result = 0;
			u8 mc_data_buffer[DRX_UCODE_MAX_BUF_SIZE];
			u32 bytes_to_comp = 0;
			u32 bytes_left = mc_block_nr_bytes;
			u32 curr_addr = block_hdr.addr;
			u8 *curr_ptr = mc_data;

			जबतक (bytes_left != 0) अणु
				अगर (bytes_left > DRX_UCODE_MAX_BUF_SIZE)
					bytes_to_comp = DRX_UCODE_MAX_BUF_SIZE;
				अन्यथा
					bytes_to_comp = bytes_left;

				अगर (drxdap_fasi_पढ़ो_block(dev_addr,
						    curr_addr,
						    (u16)bytes_to_comp,
						    (u8 *)mc_data_buffer,
						    0x0000)) अणु
					pr_err("error reading firmware at pos %zd\n",
					       mc_data - mc_data_init);
					वापस -EIO;
				पूर्ण

				result = स_भेद(curr_ptr, mc_data_buffer,
						bytes_to_comp);

				अगर (result) अणु
					pr_err("error verifying firmware at pos %zd\n",
					       mc_data - mc_data_init);
					वापस -EIO;
				पूर्ण

				curr_addr += ((dr_xaddr_t)(bytes_to_comp / 2));
				curr_ptr =&(curr_ptr[bytes_to_comp]);
				bytes_left -=((u32) bytes_to_comp);
			पूर्ण
			अवरोध;
		पूर्ण
		शेष:
			वापस -EINVAL;

		पूर्ण
		mc_data += mc_block_nr_bytes;
	पूर्ण

	वापस 0;

release:
	release_firmware(demod->firmware);
	demod->firmware = शून्य;

	वापस rc;
पूर्ण

/* caller is expected to check अगर lna is supported beक्रमe enabling */
अटल पूर्णांक drxj_set_lna_state(काष्ठा drx_demod_instance *demod, bool state)
अणु
	काष्ठा drxuio_cfg uio_cfg;
	काष्ठा drxuio_data uio_data;
	पूर्णांक result;

	uio_cfg.uio = DRX_UIO1;
	uio_cfg.mode = DRX_UIO_MODE_READWRITE;
	/* Configure user-I/O #3: enable पढ़ो/ग_लिखो */
	result = ctrl_set_uio_cfg(demod, &uio_cfg);
	अगर (result) अणु
		pr_err("Failed to setup LNA GPIO!\n");
		वापस result;
	पूर्ण

	uio_data.uio = DRX_UIO1;
	uio_data.value = state;
	result = ctrl_uio_ग_लिखो(demod, &uio_data);
	अगर (result != 0) अणु
		pr_err("Failed to %sable LNA!\n",
		       state ? "en" : "dis");
		वापस result;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * The Linux DVB Driver क्रम Micronas DRX39xx family (drx3933j)
 *
 * Written by Devin Heiपंचांगueller <devin.heiपंचांगueller@kernelद_असल.com>
 */

अटल पूर्णांक drx39xxj_set_घातerstate(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा drx39xxj_state *state = fe->demodulator_priv;
	काष्ठा drx_demod_instance *demod = state->demod;
	पूर्णांक result;
	क्रमागत drx_घातer_mode घातer_mode;

	अगर (enable)
		घातer_mode = DRX_POWER_UP;
	अन्यथा
		घातer_mode = DRX_POWER_DOWN;

	result = ctrl_घातer_mode(demod, &घातer_mode);
	अगर (result != 0) अणु
		pr_err("Power state change failed\n");
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक drx39xxj_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा drx39xxj_state *state = fe->demodulator_priv;
	काष्ठा drx_demod_instance *demod = state->demod;
	पूर्णांक result;
	क्रमागत drx_lock_status lock_status;

	*status = 0;

	result = ctrl_lock_status(demod, &lock_status);
	अगर (result != 0) अणु
		pr_err("drx39xxj: could not get lock status!\n");
		*status = 0;
	पूर्ण

	चयन (lock_status) अणु
	हाल DRX_NEVER_LOCK:
		*status = 0;
		pr_err("drx says NEVER_LOCK\n");
		अवरोध;
	हाल DRX_NOT_LOCKED:
		*status = 0;
		अवरोध;
	हाल DRX_LOCK_STATE_1:
	हाल DRX_LOCK_STATE_2:
	हाल DRX_LOCK_STATE_3:
	हाल DRX_LOCK_STATE_4:
	हाल DRX_LOCK_STATE_5:
	हाल DRX_LOCK_STATE_6:
	हाल DRX_LOCK_STATE_7:
	हाल DRX_LOCK_STATE_8:
	हाल DRX_LOCK_STATE_9:
		*status = FE_HAS_SIGNAL
		    | FE_HAS_CARRIER | FE_HAS_VITERBI | FE_HAS_SYNC;
		अवरोध;
	हाल DRX_LOCKED:
		*status = FE_HAS_SIGNAL
		    | FE_HAS_CARRIER
		    | FE_HAS_VITERBI | FE_HAS_SYNC | FE_HAS_LOCK;
		अवरोध;
	शेष:
		pr_err("Lock state unknown %d\n", lock_status);
	पूर्ण
	ctrl_sig_quality(demod, lock_status);

	वापस 0;
पूर्ण

अटल पूर्णांक drx39xxj_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;

	अगर (p->pre_bit_error.stat[0].scale == FE_SCALE_NOT_AVAILABLE) अणु
		*ber = 0;
		वापस 0;
	पूर्ण

	अगर (!p->pre_bit_count.stat[0].uvalue) अणु
		अगर (!p->pre_bit_error.stat[0].uvalue)
			*ber = 0;
		अन्यथा
			*ber = 1000000;
	पूर्ण अन्यथा अणु
		*ber = frac_बार1e6(p->pre_bit_error.stat[0].uvalue,
				     p->pre_bit_count.stat[0].uvalue);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक drx39xxj_पढ़ो_संकेत_strength(काष्ठा dvb_frontend *fe,
					 u16 *strength)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;

	अगर (p->strength.stat[0].scale == FE_SCALE_NOT_AVAILABLE) अणु
		*strength = 0;
		वापस 0;
	पूर्ण

	*strength = p->strength.stat[0].uvalue;
	वापस 0;
पूर्ण

अटल पूर्णांक drx39xxj_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	u64 पंचांगp64;

	अगर (p->cnr.stat[0].scale == FE_SCALE_NOT_AVAILABLE) अणु
		*snr = 0;
		वापस 0;
	पूर्ण

	पंचांगp64 = p->cnr.stat[0].svalue;
	करो_भाग(पंचांगp64, 10);
	*snr = पंचांगp64;
	वापस 0;
पूर्ण

अटल पूर्णांक drx39xxj_पढ़ो_ucblocks(काष्ठा dvb_frontend *fe, u32 *ucb)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;

	अगर (p->block_error.stat[0].scale == FE_SCALE_NOT_AVAILABLE) अणु
		*ucb = 0;
		वापस 0;
	पूर्ण

	*ucb = p->block_error.stat[0].uvalue;
	वापस 0;
पूर्ण

अटल पूर्णांक drx39xxj_set_frontend(काष्ठा dvb_frontend *fe)
अणु
#अगर_घोषित DJH_DEBUG
	पूर्णांक i;
#पूर्ण_अगर
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा drx39xxj_state *state = fe->demodulator_priv;
	काष्ठा drx_demod_instance *demod = state->demod;
	क्रमागत drx_standard standard = DRX_STANDARD_8VSB;
	काष्ठा drx_channel channel;
	पूर्णांक result;
	अटल स्थिर काष्ठा drx_channel def_channel = अणु
		/* frequency      */ 0,
		/* bandwidth      */ DRX_BANDWIDTH_6MHZ,
		/* mirror         */ DRX_MIRROR_NO,
		/* स्थिरellation  */ DRX_CONSTELLATION_AUTO,
		/* hierarchy      */ DRX_HIERARCHY_UNKNOWN,
		/* priority       */ DRX_PRIORITY_UNKNOWN,
		/* coderate       */ DRX_CODERATE_UNKNOWN,
		/* guard          */ DRX_GUARD_UNKNOWN,
		/* ffपंचांगode        */ DRX_FFTMODE_UNKNOWN,
		/* classअगरication */ DRX_CLASSIFICATION_AUTO,
		/* symbolrate     */ 5057000,
		/* पूर्णांकerleavemode */ DRX_INTERLEAVEMODE_UNKNOWN,
		/* ldpc           */ DRX_LDPC_UNKNOWN,
		/* carrier        */ DRX_CARRIER_UNKNOWN,
		/* frame mode     */ DRX_FRAMEMODE_UNKNOWN
	पूर्ण;
	u32 स्थिरellation = DRX_CONSTELLATION_AUTO;

	/* Bring the demod out of sleep */
	drx39xxj_set_घातerstate(fe, 1);

	अगर (fe->ops.tuner_ops.set_params) अणु
		u32 पूर्णांक_freq;

		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);

		/* Set tuner to desired frequency and standard */
		fe->ops.tuner_ops.set_params(fe);

		/* Use the tuner's IF */
		अगर (fe->ops.tuner_ops.get_अगर_frequency) अणु
			fe->ops.tuner_ops.get_अगर_frequency(fe, &पूर्णांक_freq);
			demod->my_common_attr->पूर्णांकermediate_freq = पूर्णांक_freq / 1000;
		पूर्ण

		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण

	चयन (p->delivery_प्रणाली) अणु
	हाल SYS_ATSC:
		standard = DRX_STANDARD_8VSB;
		अवरोध;
	हाल SYS_DVBC_ANNEX_B:
		standard = DRX_STANDARD_ITU_B;

		चयन (p->modulation) अणु
		हाल QAM_64:
			स्थिरellation = DRX_CONSTELLATION_QAM64;
			अवरोध;
		हाल QAM_256:
			स्थिरellation = DRX_CONSTELLATION_QAM256;
			अवरोध;
		शेष:
			स्थिरellation = DRX_CONSTELLATION_AUTO;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	/* Set the standard (will be घातered up अगर necessary */
	result = ctrl_set_standard(demod, &standard);
	अगर (result != 0) अणु
		pr_err("Failed to set standard! result=%02x\n",
			result);
		वापस -EINVAL;
	पूर्ण

	/* set channel parameters */
	channel = def_channel;
	channel.frequency = p->frequency / 1000;
	channel.bandwidth = DRX_BANDWIDTH_6MHZ;
	channel.स्थिरellation = स्थिरellation;

	/* program channel */
	result = ctrl_set_channel(demod, &channel);
	अगर (result != 0) अणु
		pr_err("Failed to set channel!\n");
		वापस -EINVAL;
	पूर्ण
	/* Just क्रम giggles, let's shut off the LNA again.... */
	drxj_set_lna_state(demod, false);

	/* After set_frontend, except क्रम strength, stats aren't available */
	p->strength.stat[0].scale = FE_SCALE_RELATIVE;

	वापस 0;
पूर्ण

अटल पूर्णांक drx39xxj_sleep(काष्ठा dvb_frontend *fe)
अणु
	/* घातer-करोwn the demodulator */
	वापस drx39xxj_set_घातerstate(fe, 0);
पूर्ण

अटल पूर्णांक drx39xxj_i2c_gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable)
अणु
	काष्ठा drx39xxj_state *state = fe->demodulator_priv;
	काष्ठा drx_demod_instance *demod = state->demod;
	bool i2c_gate_state;
	पूर्णांक result;

#अगर_घोषित DJH_DEBUG
	pr_debug("i2c gate call: enable=%d state=%d\n", enable,
	       state->i2c_gate_खोलो);
#पूर्ण_अगर

	अगर (enable)
		i2c_gate_state = true;
	अन्यथा
		i2c_gate_state = false;

	अगर (state->i2c_gate_खोलो == enable) अणु
		/* We're alपढ़ोy in the desired state */
		वापस 0;
	पूर्ण

	result = ctrl_i2c_bridge(demod, &i2c_gate_state);
	अगर (result != 0) अणु
		pr_err("drx39xxj: could not open i2c gate [%d]\n",
		       result);
		dump_stack();
	पूर्ण अन्यथा अणु
		state->i2c_gate_खोलो = enable;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक drx39xxj_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा drx39xxj_state *state = fe->demodulator_priv;
	काष्ठा drx_demod_instance *demod = state->demod;
	पूर्णांक rc = 0;

	अगर (fe->निकास == DVB_FE_DEVICE_RESUME) अणु
		/* so drxj_खोलो() करोes what it needs to करो */
		demod->my_common_attr->is_खोलोed = false;
		rc = drxj_खोलो(demod);
		अगर (rc != 0)
			pr_err("drx39xxj_init(): DRX open failed rc=%d!\n", rc);
	पूर्ण अन्यथा
		drx39xxj_set_घातerstate(fe, 1);

	वापस rc;
पूर्ण

अटल पूर्णांक drx39xxj_set_lna(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा drx39xxj_state *state = fe->demodulator_priv;
	काष्ठा drx_demod_instance *demod = state->demod;
	काष्ठा drxj_data *ext_attr = demod->my_ext_attr;

	अगर (c->lna) अणु
		अगर (!ext_attr->has_lna) अणु
			pr_err("LNA is not supported on this device!\n");
			वापस -EINVAL;

		पूर्ण
	पूर्ण

	वापस drxj_set_lna_state(demod, c->lna);
पूर्ण

अटल पूर्णांक drx39xxj_get_tune_settings(काष्ठा dvb_frontend *fe,
				      काष्ठा dvb_frontend_tune_settings *tune)
अणु
	tune->min_delay_ms = 1000;
	वापस 0;
पूर्ण

अटल व्योम drx39xxj_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा drx39xxj_state *state = fe->demodulator_priv;
	काष्ठा drx_demod_instance *demod = state->demod;

	/* अगर device is हटाओd करोn't access it */
	अगर (fe->निकास != DVB_FE_DEVICE_REMOVED)
		drxj_बंद(demod);

	kमुक्त(demod->my_ext_attr);
	kमुक्त(demod->my_common_attr);
	kमुक्त(demod->my_i2c_dev_addr);
	release_firmware(demod->firmware);
	kमुक्त(demod);
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops drx39xxj_ops;

काष्ठा dvb_frontend *drx39xxj_attach(काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा drx39xxj_state *state = शून्य;
	काष्ठा i2c_device_addr *demod_addr = शून्य;
	काष्ठा drx_common_attr *demod_comm_attr = शून्य;
	काष्ठा drxj_data *demod_ext_attr = शून्य;
	काष्ठा drx_demod_instance *demod = शून्य;
	काष्ठा dtv_frontend_properties *p;
	पूर्णांक result;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा drx39xxj_state), GFP_KERNEL);
	अगर (state == शून्य)
		जाओ error;

	demod = kmemdup(&drxj_शेष_demod_g,
			माप(काष्ठा drx_demod_instance), GFP_KERNEL);
	अगर (demod == शून्य)
		जाओ error;

	demod_addr = kmemdup(&drxj_शेष_addr_g,
			     माप(काष्ठा i2c_device_addr), GFP_KERNEL);
	अगर (demod_addr == शून्य)
		जाओ error;

	demod_comm_attr = kmemdup(&drxj_शेष_comm_attr_g,
				  माप(काष्ठा drx_common_attr), GFP_KERNEL);
	अगर (demod_comm_attr == शून्य)
		जाओ error;

	demod_ext_attr = kmemdup(&drxj_data_g, माप(काष्ठा drxj_data),
				 GFP_KERNEL);
	अगर (demod_ext_attr == शून्य)
		जाओ error;

	/* setup the state */
	state->i2c = i2c;
	state->demod = demod;

	/* setup the demod data */
	demod->my_i2c_dev_addr = demod_addr;
	demod->my_common_attr = demod_comm_attr;
	demod->my_i2c_dev_addr->user_data = state;
	demod->my_common_attr->microcode_file = DRX39XX_MAIN_FIRMWARE;
	demod->my_common_attr->verअगरy_microcode = true;
	demod->my_common_attr->पूर्णांकermediate_freq = 5000;
	demod->my_common_attr->current_घातer_mode = DRX_POWER_DOWN;
	demod->my_ext_attr = demod_ext_attr;
	((काष्ठा drxj_data *)demod_ext_attr)->uio_sma_tx_mode = DRX_UIO_MODE_READWRITE;
	demod->i2c = i2c;

	result = drxj_खोलो(demod);
	अगर (result != 0) अणु
		pr_err("DRX open failed!  Aborting\n");
		जाओ error;
	पूर्ण

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &drx39xxj_ops,
	       माप(काष्ठा dvb_frontend_ops));

	state->frontend.demodulator_priv = state;

	/* Initialize stats - needed क्रम DVBv5 stats to work */
	p = &state->frontend.dtv_property_cache;
	p->strength.len = 1;
	p->pre_bit_count.len = 1;
	p->pre_bit_error.len = 1;
	p->post_bit_count.len = 1;
	p->post_bit_error.len = 1;
	p->block_count.len = 1;
	p->block_error.len = 1;
	p->cnr.len = 1;

	p->strength.stat[0].scale = FE_SCALE_RELATIVE;
	p->pre_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->pre_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->block_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->block_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	वापस &state->frontend;

error:
	kमुक्त(demod_ext_attr);
	kमुक्त(demod_comm_attr);
	kमुक्त(demod_addr);
	kमुक्त(demod);
	kमुक्त(state);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(drx39xxj_attach);

अटल स्थिर काष्ठा dvb_frontend_ops drx39xxj_ops = अणु
	.delsys = अणु SYS_ATSC, SYS_DVBC_ANNEX_B पूर्ण,
	.info = अणु
		 .name = "Micronas DRX39xxj family Frontend",
		 .frequency_min_hz =  51 * MHz,
		 .frequency_max_hz = 858 * MHz,
		 .frequency_stepsize_hz = 62500,
		 .caps = FE_CAN_QAM_64 | FE_CAN_QAM_256 | FE_CAN_8VSB
	पूर्ण,

	.init = drx39xxj_init,
	.i2c_gate_ctrl = drx39xxj_i2c_gate_ctrl,
	.sleep = drx39xxj_sleep,
	.set_frontend = drx39xxj_set_frontend,
	.get_tune_settings = drx39xxj_get_tune_settings,
	.पढ़ो_status = drx39xxj_पढ़ो_status,
	.पढ़ो_ber = drx39xxj_पढ़ो_ber,
	.पढ़ो_संकेत_strength = drx39xxj_पढ़ो_संकेत_strength,
	.पढ़ो_snr = drx39xxj_पढ़ो_snr,
	.पढ़ो_ucblocks = drx39xxj_पढ़ो_ucblocks,
	.release = drx39xxj_release,
	.set_lna = drx39xxj_set_lna,
पूर्ण;

MODULE_DESCRIPTION("Micronas DRX39xxj Frontend");
MODULE_AUTHOR("Devin Heitmueller");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(DRX39XX_MAIN_FIRMWARE);
