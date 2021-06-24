<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * File:         sound/soc/codecs/ssm2602.h
 * Author:       Clअगरf Cai <Clअगरf.Cai@analog.com>
 *
 * Created:      Tue June 06 2008
 *
 * Modअगरied:
 *               Copyright 2008 Analog Devices Inc.
 *
 * Bugs:         Enter bugs at http://blackfin.uclinux.org/
 */

#अगर_अघोषित _SSM2602_H
#घोषणा _SSM2602_H

#समावेश <linux/regmap.h>

काष्ठा device;

क्रमागत ssm2602_type अणु
	SSM2602,
	SSM2604,
पूर्ण;

बाह्य स्थिर काष्ठा regmap_config ssm2602_regmap_config;

पूर्णांक ssm2602_probe(काष्ठा device *dev, क्रमागत ssm2602_type type,
	काष्ठा regmap *regmap);

/* SSM2602 Codec Register definitions */

#घोषणा SSM2602_LINVOL   0x00
#घोषणा SSM2602_RINVOL   0x01
#घोषणा SSM2602_LOUT1V   0x02
#घोषणा SSM2602_ROUT1V   0x03
#घोषणा SSM2602_APANA    0x04
#घोषणा SSM2602_APDIGI   0x05
#घोषणा SSM2602_PWR      0x06
#घोषणा SSM2602_IFACE    0x07
#घोषणा SSM2602_SRATE    0x08
#घोषणा SSM2602_ACTIVE   0x09
#घोषणा SSM2602_RESET	 0x0f

/*SSM2602 Codec Register Field definitions
 *(Mask value to extract the corresponding Register field)
 */

/*Left ADC Volume Control (SSM2602_REG_LEFT_ADC_VOL)*/
#घोषणा     LINVOL_LIN_VOL                0x01F   /* Left Channel PGA Volume control                      */
#घोषणा     LINVOL_LIN_ENABLE_MUTE        0x080   /* Left Channel Input Mute                              */
#घोषणा     LINVOL_LRIN_BOTH              0x100   /* Left Channel Line Input Volume update                */

/*Right ADC Volume Control (SSM2602_REG_RIGHT_ADC_VOL)*/
#घोषणा     RINVOL_RIN_VOL                0x01F   /* Right Channel PGA Volume control                     */
#घोषणा     RINVOL_RIN_ENABLE_MUTE        0x080   /* Right Channel Input Mute                             */
#घोषणा     RINVOL_RLIN_BOTH              0x100   /* Right Channel Line Input Volume update               */

/*Left DAC Volume Control (SSM2602_REG_LEFT_DAC_VOL)*/
#घोषणा     LOUT1V_LHP_VOL                0x07F   /* Left Channel Headphone volume control                */
#घोषणा     LOUT1V_ENABLE_LZC             0x080   /* Left Channel Zero cross detect enable                */
#घोषणा     LOUT1V_LRHP_BOTH              0x100   /* Left Channel Headphone volume update                 */

/*Right DAC Volume Control (SSM2602_REG_RIGHT_DAC_VOL)*/
#घोषणा     ROUT1V_RHP_VOL                0x07F   /* Right Channel Headphone volume control               */
#घोषणा     ROUT1V_ENABLE_RZC             0x080   /* Right Channel Zero cross detect enable               */
#घोषणा     ROUT1V_RLHP_BOTH              0x100   /* Right Channel Headphone volume update                */

/*Analogue Audio Path Control (SSM2602_REG_ANALOGUE_PATH)*/
#घोषणा     APANA_ENABLE_MIC_BOOST       0x001   /* Primary Microphone Amplअगरier gain booster control    */
#घोषणा     APANA_ENABLE_MIC_MUTE        0x002   /* Microphone Mute Control                              */
#घोषणा     APANA_ADC_IN_SELECT          0x004   /* Microphone/Line IN select to ADC (1=MIC, 0=Line In)  */
#घोषणा     APANA_ENABLE_BYPASS          0x008   /* Line input bypass to line output                     */
#घोषणा     APANA_SELECT_DAC             0x010   /* Select DAC (1=Select DAC, 0=Don't Select DAC)        */
#घोषणा     APANA_ENABLE_SIDETONE        0x020   /* Enable/Disable Side Tone                             */
#घोषणा     APANA_SIDETONE_ATTN          0x0C0   /* Side Tone Attenuation                                */
#घोषणा     APANA_ENABLE_MIC_BOOST2      0x100   /* Secondary Microphone Amplअगरier gain booster control  */

/*Digital Audio Path Control (SSM2602_REG_DIGITAL_PATH)*/
#घोषणा     APDIGI_ENABLE_ADC_HPF         0x001   /* Enable/Disable ADC Highpass Filter                   */
#घोषणा     APDIGI_DE_EMPHASIS            0x006   /* De-Emphasis Control                                  */
#घोषणा     APDIGI_ENABLE_DAC_MUTE        0x008   /* DAC Mute Control                                     */
#घोषणा     APDIGI_STORE_OFFSET           0x010   /* Store/Clear DC offset when HPF is disabled           */

/*Power Down Control (SSM2602_REG_POWER)
 *(1=Enable PowerDown, 0=Disable PowerDown)
 */
#घोषणा     PWR_LINE_IN_PDN            0x001   /* Line Input Power Down                                */
#घोषणा     PWR_MIC_PDN                0x002   /* Microphone Input & Bias Power Down                   */
#घोषणा     PWR_ADC_PDN                0x004   /* ADC Power Down                                       */
#घोषणा     PWR_DAC_PDN                0x008   /* DAC Power Down                                       */
#घोषणा     PWR_OUT_PDN                0x010   /* Outमाला_दो Power Down                                   */
#घोषणा     PWR_OSC_PDN                0x020   /* Oscillator Power Down                                */
#घोषणा     PWR_CLK_OUT_PDN            0x040   /* CLKOUT Power Down                                    */
#घोषणा     PWR_POWER_OFF              0x080   /* POWEROFF Mode                                        */

/*Digital Audio Interface Format (SSM2602_REG_DIGITAL_IFACE)*/
#घोषणा     IFACE_IFACE_FORMAT           0x003   /* Digital Audio input क्रमmat control                   */
#घोषणा     IFACE_AUDIO_DATA_LEN         0x00C   /* Audio Data word length control                       */
#घोषणा     IFACE_DAC_LR_POLARITY        0x010   /* Polarity Control क्रम घड़ीs in RJ,LJ and I2S modes   */
#घोषणा     IFACE_DAC_LR_SWAP            0x020   /* Swap DAC data control                                */
#घोषणा     IFACE_ENABLE_MASTER          0x040   /* Enable/Disable Master Mode                           */
#घोषणा     IFACE_BCLK_INVERT            0x080   /* Bit Clock Inversion control                          */

/*Sampling Control (SSM2602_REG_SAMPLING_CTRL)*/
#घोषणा     SRATE_ENABLE_USB_MODE        0x001   /* Enable/Disable USB Mode                              */
#घोषणा     SRATE_BOS_RATE               0x002   /* Base Over-Sampling rate                              */
#घोषणा     SRATE_SAMPLE_RATE            0x03C   /* Clock setting condition (Sampling rate control)      */
#घोषणा     SRATE_CORECLK_DIV2           0x040   /* Core Clock भागider select                            */
#घोषणा     SRATE_CLKOUT_DIV2            0x080   /* Clock Out भागider select                             */

/*Active Control (SSM2602_REG_ACTIVE_CTRL)*/
#घोषणा     ACTIVE_ACTIVATE_CODEC         0x001   /* Activate Codec Digital Audio Interface               */

/*********************************************************************/

#घोषणा SSM2602_CACHEREGNUM 	10

क्रमागत ssm2602_clk अणु
	SSM2602_SYSCLK,
	SSM2602_CLK_CLKOUT,
	SSM2602_CLK_XTO
पूर्ण;

#पूर्ण_अगर
