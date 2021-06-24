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

 DRXJ specअगरic header file

 Authors: Dragan Savic, Milos Nikolic, Mihajlo Katona, Tao Ding, Paul Janssen
*/

#अगर_अघोषित __DRXJ_H__
#घोषणा __DRXJ_H__
/*-------------------------------------------------------------------------
INCLUDES
-------------------------------------------------------------------------*/

#समावेश "drx_driver.h"
#समावेश "drx_dap_fasi.h"

/* Check DRX-J specअगरic dap condition */
/* Multi master mode and लघु addr क्रमmat only will not work.
   RMW, CRC reset, broadcast and चयनing back to single master mode
   cannot be करोne with लघु addr only in multi master mode. */
#अगर ((DRXDAP_SINGLE_MASTER == 0) && (DRXDAPFASI_LONG_ADDR_ALLOWED == 0))
#त्रुटि "Multi master mode and short addressing only is an illegal combination"
	*;			/* Generate a fatal compiler error to make sure it stops here,
				   this is necessary because not all compilers stop after a #त्रुटि. */
#पूर्ण_अगर

/*-------------------------------------------------------------------------
TYPEDEFS
-------------------------------------------------------------------------*/
/*============================================================================*/
/*============================================================================*/
/*== code support ============================================================*/
/*============================================================================*/
/*============================================================================*/

/*============================================================================*/
/*============================================================================*/
/*== SCU cmd अगर  =============================================================*/
/*============================================================================*/
/*============================================================================*/

	काष्ठा drxjscu_cmd अणु
		u16 command;
			/*< Command number */
		u16 parameter_len;
			/*< Data length in byte */
		u16 result_len;
			/*< result length in byte */
		u16 *parameter;
			/*< General purpous param */
		u16 *result;
			/*< General purpous param */पूर्ण;

/*============================================================================*/
/*============================================================================*/
/*== CTRL CFG related data काष्ठाures ========================================*/
/*============================================================================*/
/*============================================================================*/

/* extra पूर्णांकermediate lock state क्रम VSB,QAM,NTSC */
#घोषणा DRXJ_DEMOD_LOCK       (DRX_LOCK_STATE_1)

/* OOB lock states */
#घोषणा DRXJ_OOB_AGC_LOCK     (DRX_LOCK_STATE_1)	/* analog gain control lock */
#घोषणा DRXJ_OOB_SYNC_LOCK    (DRX_LOCK_STATE_2)	/* digital gain control lock */

/* Intermediate घातermodes क्रम DRXJ */
#घोषणा DRXJ_POWER_DOWN_MAIN_PATH   DRX_POWER_MODE_8
#घोषणा DRXJ_POWER_DOWN_CORE        DRX_POWER_MODE_9
#घोषणा DRXJ_POWER_DOWN_PLL         DRX_POWER_MODE_10

/* supstition क्रम GPIO FNC mux */
#घोषणा APP_O                 (0x0000)

/*#घोषणा DRX_CTRL_BASE         (0x0000)*/

#घोषणा DRXJ_CTRL_CFG_BASE    (0x1000)
	क्रमागत drxj_cfg_type अणु
		DRXJ_CFG_AGC_RF = DRXJ_CTRL_CFG_BASE,
		DRXJ_CFG_AGC_IF,
		DRXJ_CFG_AGC_INTERNAL,
		DRXJ_CFG_PRE_SAW,
		DRXJ_CFG_AFE_GAIN,
		DRXJ_CFG_SYMBOL_CLK_OFFSET,
		DRXJ_CFG_ACCUM_CR_RS_CW_ERR,
		DRXJ_CFG_FEC_MERS_SEQ_COUNT,
		DRXJ_CFG_OOB_MISC,
		DRXJ_CFG_SMART_ANT,
		DRXJ_CFG_OOB_PRE_SAW,
		DRXJ_CFG_VSB_MISC,
		DRXJ_CFG_RESET_PACKET_ERR,

		/* ATV (FM) */
		DRXJ_CFG_ATV_OUTPUT,	/* also क्रम FM (SIF control) but not likely */
		DRXJ_CFG_ATV_MISC,
		DRXJ_CFG_ATV_EQU_COEF,
		DRXJ_CFG_ATV_AGC_STATUS,	/* also क्रम FM ( IF,RF, audioAGC ) */

		DRXJ_CFG_MPEG_OUTPUT_MISC,
		DRXJ_CFG_HW_CFG,
		DRXJ_CFG_OOB_LO_POW,

		DRXJ_CFG_MAX	/* dummy, never to be used */पूर्ण;

/*
* /काष्ठा क्रमागत drxj_cfg_smart_ant_io * smart antenna i/o.
*/
क्रमागत drxj_cfg_smart_ant_io अणु
	DRXJ_SMT_ANT_OUTPUT = 0,
	DRXJ_SMT_ANT_INPUT
पूर्ण;

/*
* /काष्ठा काष्ठा drxj_cfg_smart_ant * Set smart antenna.
*/
	काष्ठा drxj_cfg_smart_ant अणु
		क्रमागत drxj_cfg_smart_ant_io io;
		u16 ctrl_data;
	पूर्ण;

/*
* /काष्ठा DRXJAGCSTATUS_t
* AGC status inक्रमmation from the DRXJ-IQM-AF.
*/
काष्ठा drxj_agc_status अणु
	u16 IFAGC;
	u16 RFAGC;
	u16 digital_agc;
पूर्ण;

/* DRXJ_CFG_AGC_RF, DRXJ_CFG_AGC_IF */

/*
* /काष्ठा क्रमागत drxj_agc_ctrl_mode * Available AGCs modes in the DRXJ.
*/
	क्रमागत drxj_agc_ctrl_mode अणु
		DRX_AGC_CTRL_AUTO = 0,
		DRX_AGC_CTRL_USER,
		DRX_AGC_CTRL_OFFपूर्ण;

/*
* /काष्ठा काष्ठा drxj_cfg_agc * Generic पूर्णांकerface क्रम all AGCs present on the DRXJ.
*/
	काष्ठा drxj_cfg_agc अणु
		क्रमागत drx_standard standard;	/* standard क्रम which these settings apply */
		क्रमागत drxj_agc_ctrl_mode ctrl_mode;	/* off, user, स्वतः          */
		u16 output_level;	/* range dependent on AGC   */
		u16 min_output_level;	/* range dependent on AGC   */
		u16 max_output_level;	/* range dependent on AGC   */
		u16 speed;	/* range dependent on AGC   */
		u16 top;	/* rf-agc take over poपूर्णांक   */
		u16 cut_off_current;	/* rf-agc is accelerated अगर output current
					   is below cut-off current                */पूर्ण;

/* DRXJ_CFG_PRE_SAW */

/*
* /काष्ठा काष्ठा drxj_cfg_pre_saw * Interface to configure pre SAW sense.
*/
	काष्ठा drxj_cfg_pre_saw अणु
		क्रमागत drx_standard standard;	/* standard to which these settings apply */
		u16 reference;	/* pre SAW reference value, range 0 .. 31 */
		bool use_pre_saw;	/* true algorithms must use pre SAW sense */पूर्ण;

/* DRXJ_CFG_AFE_GAIN */

/*
* /काष्ठा काष्ठा drxj_cfg_afe_gain * Interface to configure gain of AFE (LNA + PGA).
*/
	काष्ठा drxj_cfg_afe_gain अणु
		क्रमागत drx_standard standard;	/* standard to which these settings apply */
		u16 gain;	/* gain in 0.1 dB steps, DRXJ range 140 .. 335 */पूर्ण;

/*
* /काष्ठा drxjrs_errors
* Available failure inक्रमmation in DRXJ_FEC_RS.
*
* Container क्रम errors that are received in the most recently finished measurement period
*
*/
	काष्ठा drxjrs_errors अणु
		u16 nr_bit_errors;
				/*< no of pre RS bit errors          */
		u16 nr_symbol_errors;
				/*< no of pre RS symbol errors       */
		u16 nr_packet_errors;
				/*< no of pre RS packet errors       */
		u16 nr_failures;
				/*< no of post RS failures to decode */
		u16 nr_snc_par_fail_count;
				/*< no of post RS bit erros          */
	पूर्ण;

/*
* /काष्ठा काष्ठा drxj_cfg_vsb_misc * symbol error rate
*/
	काष्ठा drxj_cfg_vsb_misc अणु
		u32 symb_error;
			      /*< symbol error rate sps */पूर्ण;

/*
* /क्रमागत क्रमागत drxj_mpeg_output_घड़ी_rate * Mpeg output घड़ी rate.
*
*/
	क्रमागत drxj_mpeg_start_width अणु
		DRXJ_MPEG_START_WIDTH_1CLKCYC,
		DRXJ_MPEG_START_WIDTH_8CLKCYCपूर्ण;

/*
* /क्रमागत क्रमागत drxj_mpeg_output_घड़ी_rate * Mpeg output घड़ी rate.
*
*/
	क्रमागत drxj_mpeg_output_घड़ी_rate अणु
		DRXJ_MPEGOUTPUT_CLOCK_RATE_AUTO,
		DRXJ_MPEGOUTPUT_CLOCK_RATE_75973K,
		DRXJ_MPEGOUTPUT_CLOCK_RATE_50625K,
		DRXJ_MPEGOUTPUT_CLOCK_RATE_37968K,
		DRXJ_MPEGOUTPUT_CLOCK_RATE_30375K,
		DRXJ_MPEGOUTPUT_CLOCK_RATE_25313K,
		DRXJ_MPEGOUTPUT_CLOCK_RATE_21696Kपूर्ण;

/*
* /काष्ठा DRXJCfgMisc_t
* Change TEI bit of MPEG output
* reverse MPEG output bit order
* set MPEG output घड़ी rate
*/
	काष्ठा drxj_cfg_mpeg_output_misc अणु
		bool disable_tei_handling;	      /*< अगर true pass (not change) TEI bit */
		bool bit_reverse_mpeg_outout;	      /*< अगर true, parallel: msb on MD0; serial: lsb out first */
		क्रमागत drxj_mpeg_output_घड़ी_rate mpeg_output_घड़ी_rate;
						      /*< set MPEG output घड़ी rate that overwirtes the derived one from symbol rate */
		क्रमागत drxj_mpeg_start_width mpeg_start_width;  /*< set MPEG output start width */पूर्ण;

/*
* /क्रमागत क्रमागत drxj_xtal_freq * Supported बाह्यal crystal reference frequency.
*/
	क्रमागत drxj_xtal_freq अणु
		DRXJ_XTAL_FREQ_RSVD,
		DRXJ_XTAL_FREQ_27MHZ,
		DRXJ_XTAL_FREQ_20P25MHZ,
		DRXJ_XTAL_FREQ_4MHZपूर्ण;

/*
* /क्रमागत क्रमागत drxj_xtal_freq * Supported बाह्यal crystal reference frequency.
*/
	क्रमागत drxji2c_speed अणु
		DRXJ_I2C_SPEED_400KBPS,
		DRXJ_I2C_SPEED_100KBPSपूर्ण;

/*
* /काष्ठा काष्ठा drxj_cfg_hw_cfg * Get hw configuration, such as crystal reference frequency, I2C speed, etc...
*/
	काष्ठा drxj_cfg_hw_cfg अणु
		क्रमागत drxj_xtal_freq xtal_freq;
				   /*< crystal reference frequency */
		क्रमागत drxji2c_speed i2c_speed;
				   /*< 100 or 400 kbps */पूर्ण;

/*
 *  DRXJ_CFG_ATV_MISC
 */
	काष्ठा drxj_cfg_atv_misc अणु
		s16 peak_filter;	/* -8 .. 15 */
		u16 noise_filter;	/* 0 .. 15 */पूर्ण;

/*
 *  काष्ठा drxj_cfg_oob_misc */
#घोषणा   DRXJ_OOB_STATE_RESET                                        0x0
#घोषणा   DRXJ_OOB_STATE_AGN_HUNT                                     0x1
#घोषणा   DRXJ_OOB_STATE_DGN_HUNT                                     0x2
#घोषणा   DRXJ_OOB_STATE_AGC_HUNT                                     0x3
#घोषणा   DRXJ_OOB_STATE_FRQ_HUNT                                     0x4
#घोषणा   DRXJ_OOB_STATE_PHA_HUNT                                     0x8
#घोषणा   DRXJ_OOB_STATE_TIM_HUNT                                     0x10
#घोषणा   DRXJ_OOB_STATE_EQU_HUNT                                     0x20
#घोषणा   DRXJ_OOB_STATE_EQT_HUNT                                     0x30
#घोषणा   DRXJ_OOB_STATE_SYNC                                         0x40

काष्ठा drxj_cfg_oob_misc अणु
	काष्ठा drxj_agc_status agc;
	bool eq_lock;
	bool sym_timing_lock;
	bool phase_lock;
	bool freq_lock;
	bool dig_gain_lock;
	bool ana_gain_lock;
	u8 state;
पूर्ण;

/*
 *  Index of in array of coef
 */
	क्रमागत drxj_cfg_oob_lo_घातer अणु
		DRXJ_OOB_LO_POW_MINUS0DB = 0,
		DRXJ_OOB_LO_POW_MINUS5DB,
		DRXJ_OOB_LO_POW_MINUS10DB,
		DRXJ_OOB_LO_POW_MINUS15DB,
		DRXJ_OOB_LO_POW_MAXपूर्ण;

/*
 *  DRXJ_CFG_ATV_EQU_COEF
 */
	काष्ठा drxj_cfg_atv_equ_coef अणु
		s16 coef0;	/* -256 .. 255 */
		s16 coef1;	/* -256 .. 255 */
		s16 coef2;	/* -256 .. 255 */
		s16 coef3;	/* -256 .. 255 */पूर्ण;

/*
 *  Index of in array of coef
 */
	क्रमागत drxj_coef_array_index अणु
		DRXJ_COEF_IDX_MN = 0,
		DRXJ_COEF_IDX_FM,
		DRXJ_COEF_IDX_L,
		DRXJ_COEF_IDX_LP,
		DRXJ_COEF_IDX_BG,
		DRXJ_COEF_IDX_DK,
		DRXJ_COEF_IDX_I,
		DRXJ_COEF_IDX_MAXपूर्ण;

/*
 *  DRXJ_CFG_ATV_OUTPUT
 */

/*
* /क्रमागत DRXJAttenuation_t
* Attenuation setting क्रम SIF AGC.
*
*/
	क्रमागत drxjsअगर_attenuation अणु
		DRXJ_SIF_ATTENUATION_0DB,
		DRXJ_SIF_ATTENUATION_3DB,
		DRXJ_SIF_ATTENUATION_6DB,
		DRXJ_SIF_ATTENUATION_9DBपूर्ण;

/*
* /काष्ठा काष्ठा drxj_cfg_atv_output * SIF attenuation setting.
*
*/
काष्ठा drxj_cfg_atv_output अणु
	bool enable_cvbs_output;	/* true= enabled */
	bool enable_sअगर_output;	/* true= enabled */
	क्रमागत drxjsअगर_attenuation sअगर_attenuation;
पूर्ण;

/*
   DRXJ_CFG_ATV_AGC_STATUS (get only)
*/
/* TODO : AFE पूर्णांकerface not yet finished, subject to change */
	काष्ठा drxj_cfg_atv_agc_status अणु
		u16 rf_agc_gain;	/* 0 .. 877 uA */
		u16 अगर_agc_gain;	/* 0 .. 877  uA */
		s16 video_agc_gain;	/* -75 .. 1972 in 0.1 dB steps */
		s16 audio_agc_gain;	/* -4 .. 1020 in 0.1 dB steps */
		u16 rf_agc_loop_gain;	/* 0 .. 7 */
		u16 अगर_agc_loop_gain;	/* 0 .. 7 */
		u16 video_agc_loop_gain;	/* 0 .. 7 */पूर्ण;

/*============================================================================*/
/*============================================================================*/
/*== CTRL related data काष्ठाures ============================================*/
/*============================================================================*/
/*============================================================================*/

/* NONE */

/*============================================================================*/
/*============================================================================*/

/*========================================*/
/*
* /काष्ठा काष्ठा drxj_data * DRXJ specअगरic attributes.
*
* Global data container क्रम DRXJ specअगरic data.
*
*/
	काष्ठा drxj_data अणु
		/* device capabilities (determined during drx_खोलो()) */
		bool has_lna;		  /*< true अगर LNA (aka PGA) present */
		bool has_oob;		  /*< true अगर OOB supported */
		bool has_ntsc;		  /*< true अगर NTSC supported */
		bool has_btsc;		  /*< true अगर BTSC supported */
		bool has_smatx;	  /*< true अगर mat_tx is available */
		bool has_smarx;	  /*< true अगर mat_rx is available */
		bool has_gpio;		  /*< true अगर GPIO is available */
		bool has_irqn;		  /*< true अगर IRQN is available */
		/* A1/A2/A... */
		u8 mfx;		  /*< metal fix */

		/* tuner settings */
		bool mirror_freq_spect_oob;/*< tuner inversion (true = tuner mirrors the संकेत */

		/* standard/channel settings */
		क्रमागत drx_standard standard;	  /*< current standard inक्रमmation                     */
		क्रमागत drx_modulation स्थिरellation;
					  /*< current स्थिरellation                            */
		s32 frequency; /*< center संकेत frequency in KHz                   */
		क्रमागत drx_bandwidth curr_bandwidth;
					  /*< current channel bandwidth                        */
		क्रमागत drx_mirror mirror;	  /*< current channel mirror                           */

		/* संकेत quality inक्रमmation */
		u32 fec_bits_desired;	  /*< BER accounting period                            */
		u16 fec_vd_plen;	  /*< no of trellis symbols: VD SER measurement period */
		u16 qam_vd_prescale;	  /*< Viterbi Measurement Prescale                     */
		u16 qam_vd_period;	  /*< Viterbi Measurement period                       */
		u16 fec_rs_plen;	  /*< defines RS BER measurement period                */
		u16 fec_rs_prescale;	  /*< ReedSolomon Measurement Prescale                 */
		u16 fec_rs_period;	  /*< ReedSolomon Measurement period                   */
		bool reset_pkt_err_acc;	  /*< Set a flag to reset accumulated packet error     */
		u16 pkt_err_acc_start;	  /*< Set a flag to reset accumulated packet error     */

		/* HI configuration */
		u16 hi_cfg_timing_भाग;	  /*< HI Configure() parameter 2                       */
		u16 hi_cfg_bridge_delay;	  /*< HI Configure() parameter 3                       */
		u16 hi_cfg_wake_up_key;	  /*< HI Configure() parameter 4                       */
		u16 hi_cfg_ctrl;	  /*< HI Configure() parameter 5                       */
		u16 hi_cfg_transmit;	  /*< HI Configure() parameter 6                       */

		/* UIO configuration */
		क्रमागत drxuio_mode uio_sma_rx_mode;/*< current mode of SmaRx pin                        */
		क्रमागत drxuio_mode uio_sma_tx_mode;/*< current mode of SmaTx pin                        */
		क्रमागत drxuio_mode uio_gpio_mode; /*< current mode of ASEL pin                         */
		क्रमागत drxuio_mode uio_irqn_mode; /*< current mode of IRQN pin                         */

		/* IQM fs frequecy shअगरt and inversion */
		u32 iqm_fs_rate_ofs;	   /*< frequency shअगरter setting after setchannel      */
		bool pos_image;	   /*< True: positive image                            */
		/* IQM RC frequecy shअगरt */
		u32 iqm_rc_rate_ofs;	   /*< frequency shअगरter setting after setchannel      */

		/* ATV configuration */
		u32 atv_cfg_changed_flags; /*< flag: flags cfg changes */
		s16 atv_top_equ0[DRXJ_COEF_IDX_MAX];	     /*< shaकरोw of ATV_TOP_EQU0__A */
		s16 atv_top_equ1[DRXJ_COEF_IDX_MAX];	     /*< shaकरोw of ATV_TOP_EQU1__A */
		s16 atv_top_equ2[DRXJ_COEF_IDX_MAX];	     /*< shaकरोw of ATV_TOP_EQU2__A */
		s16 atv_top_equ3[DRXJ_COEF_IDX_MAX];	     /*< shaकरोw of ATV_TOP_EQU3__A */
		bool phase_correction_bypass;/*< flag: true=bypass */
		s16 atv_top_vid_peak;	  /*< shaकरोw of ATV_TOP_VID_PEAK__A */
		u16 atv_top_noise_th;	  /*< shaकरोw of ATV_TOP_NOISE_TH__A */
		bool enable_cvbs_output;  /*< flag CVBS output enable */
		bool enable_sअगर_output;	  /*< flag SIF output enable */
		 क्रमागत drxjsअगर_attenuation sअगर_attenuation;
					  /*< current SIF att setting */
		/* Agc configuration क्रम QAM and VSB */
		काष्ठा drxj_cfg_agc qam_rf_agc_cfg; /*< qam RF AGC config */
		काष्ठा drxj_cfg_agc qam_अगर_agc_cfg; /*< qam IF AGC config */
		काष्ठा drxj_cfg_agc vsb_rf_agc_cfg; /*< vsb RF AGC config */
		काष्ठा drxj_cfg_agc vsb_अगर_agc_cfg; /*< vsb IF AGC config */

		/* PGA gain configuration क्रम QAM and VSB */
		u16 qam_pga_cfg;	  /*< qam PGA config */
		u16 vsb_pga_cfg;	  /*< vsb PGA config */

		/* Pre SAW configuration क्रम QAM and VSB */
		काष्ठा drxj_cfg_pre_saw qam_pre_saw_cfg;
					  /*< qam pre SAW config */
		काष्ठा drxj_cfg_pre_saw vsb_pre_saw_cfg;
					  /*< qam pre SAW config */

		/* Version inक्रमmation */
		अक्षर v_text[2][12];	  /*< allocated text versions */
		काष्ठा drx_version v_version[2]; /*< allocated versions काष्ठाs */
		काष्ठा drx_version_list v_list_elements[2];
					  /*< allocated version list */

		/* smart antenna configuration */
		bool smart_ant_inverted;

		/* Tracking filter setting क्रम OOB */
		u16 oob_trk_filter_cfg[8];
		bool oob_घातer_on;

		/* MPEG अटल bitrate setting */
		u32 mpeg_ts_अटल_bitrate;  /*< bitrate अटल MPEG output */
		bool disable_te_ihandling;  /*< MPEG TS TEI handling */
		bool bit_reverse_mpeg_outout;/*< MPEG output bit order */
		 क्रमागत drxj_mpeg_output_घड़ी_rate mpeg_output_घड़ी_rate;
					    /*< MPEG output घड़ी rate */
		 क्रमागत drxj_mpeg_start_width mpeg_start_width;
					    /*< MPEG Start width */

		/* Pre SAW & Agc configuration क्रम ATV */
		काष्ठा drxj_cfg_pre_saw atv_pre_saw_cfg;
					  /*< atv pre SAW config */
		काष्ठा drxj_cfg_agc atv_rf_agc_cfg; /*< atv RF AGC config */
		काष्ठा drxj_cfg_agc atv_अगर_agc_cfg; /*< atv IF AGC config */
		u16 atv_pga_cfg;	  /*< atv pga config    */

		u32 curr_symbol_rate;

		/* pin-safe mode */
		bool pdr_safe_mode;	    /*< PDR safe mode activated      */
		u16 pdr_safe_restore_val_gpio;
		u16 pdr_safe_restore_val_v_sync;
		u16 pdr_safe_restore_val_sma_rx;
		u16 pdr_safe_restore_val_sma_tx;

		/* OOB pre-saw value */
		u16 oob_pre_saw;
		क्रमागत drxj_cfg_oob_lo_घातer oob_lo_घात;

		काष्ठा drx_aud_data aud_data;
				    /*< audio storage                  */पूर्ण;

/*-------------------------------------------------------------------------
Access MACROS
-------------------------------------------------------------------------*/
/*
* \मrief Compilable references to attributes
* \param d poपूर्णांकer to demod instance
*
* Used as मुख्य reference to an attribute field.
* Can be used by both macro implementation and function implementation.
* These macros are defined to aव्योम duplication of code in macro and function
* definitions that handle access of demod common or extended attributes.
*
*/

#घोषणा DRXJ_ATTR_BTSC_DETECT(d)                       \
			(((काष्ठा drxj_data *)(d)->my_ext_attr)->aud_data.btsc_detect)

/*-------------------------------------------------------------------------
DEFINES
-------------------------------------------------------------------------*/

/*
* \def DRXJ_NTSC_CARRIER_FREQ_OFFSET
* \मrief Offset from picture carrier to centre frequency in kHz, in RF करोमुख्य
*
* For NTSC standard.
* NTSC channels are listed by their picture carrier frequency (Fpc).
* The function DRX_CTRL_SET_CHANNEL requires the centre frequency as input.
* In हाल the tuner module is not used the DRX-J requires that the tuner is
* tuned to the centre frequency of the channel:
*
* Fcentre = Fpc + DRXJ_NTSC_CARRIER_FREQ_OFFSET
*
*/
#घोषणा DRXJ_NTSC_CARRIER_FREQ_OFFSET           ((s32)(1750))

/*
* \def DRXJ_PAL_SECAM_BG_CARRIER_FREQ_OFFSET
* \मrief Offset from picture carrier to centre frequency in kHz, in RF करोमुख्य
*
* For PAL/SECAM - BG standard. This define is needed in हाल the tuner module
* is NOT used. PAL/SECAM channels are listed by their picture carrier frequency (Fpc).
* The DRX-J requires that the tuner is tuned to:
* Fpc + DRXJ_PAL_SECAM_BG_CARRIER_FREQ_OFFSET
*
* In हाल the tuner module is used the drxdriver takes care of this.
* In हाल the tuner module is NOT used the application programmer must take
* care of this.
*
*/
#घोषणा DRXJ_PAL_SECAM_BG_CARRIER_FREQ_OFFSET   ((s32)(2375))

/*
* \def DRXJ_PAL_SECAM_DKIL_CARRIER_FREQ_OFFSET
* \मrief Offset from picture carrier to centre frequency in kHz, in RF करोमुख्य
*
* For PAL/SECAM - DK, I, L standards. This define is needed in हाल the tuner module
* is NOT used. PAL/SECAM channels are listed by their picture carrier frequency (Fpc).
* The DRX-J requires that the tuner is tuned to:
* Fpc + DRXJ_PAL_SECAM_DKIL_CARRIER_FREQ_OFFSET
*
* In हाल the tuner module is used the drxdriver takes care of this.
* In हाल the tuner module is NOT used the application programmer must take
* care of this.
*
*/
#घोषणा DRXJ_PAL_SECAM_DKIL_CARRIER_FREQ_OFFSET ((s32)(2775))

/*
* \def DRXJ_PAL_SECAM_LP_CARRIER_FREQ_OFFSET
* \मrief Offset from picture carrier to centre frequency in kHz, in RF करोमुख्य
*
* For PAL/SECAM - LP standard. This define is needed in हाल the tuner module
* is NOT used. PAL/SECAM channels are listed by their picture carrier frequency (Fpc).
* The DRX-J requires that the tuner is tuned to:
* Fpc + DRXJ_PAL_SECAM_LP_CARRIER_FREQ_OFFSET
*
* In हाल the tuner module is used the drxdriver takes care of this.
* In हाल the tuner module is NOT used the application programmer must take
* care of this.
*/
#घोषणा DRXJ_PAL_SECAM_LP_CARRIER_FREQ_OFFSET   ((s32)(-3255))

/*
* \def DRXJ_FM_CARRIER_FREQ_OFFSET
* \मrief Offset from sound carrier to centre frequency in kHz, in RF करोमुख्य
*
* For FM standard.
* FM channels are listed by their sound carrier frequency (Fsc).
* The function DRX_CTRL_SET_CHANNEL requires the Ffm frequency (see below) as
* input.
* In हाल the tuner module is not used the DRX-J requires that the tuner is
* tuned to the Ffm frequency of the channel.
*
* Ffm = Fsc + DRXJ_FM_CARRIER_FREQ_OFFSET
*
*/
#घोषणा DRXJ_FM_CARRIER_FREQ_OFFSET             ((s32)(-3000))

/* Revision types -------------------------------------------------------*/

#घोषणा DRXJ_TYPE_ID (0x3946000DUL)

/* Macros ---------------------------------------------------------------*/

/* Convert OOB lock status to string */
#घोषणा DRXJ_STR_OOB_LOCKSTATUS(x) ( \
	(x == DRX_NEVER_LOCK) ? "Never" : \
	(x == DRX_NOT_LOCKED) ? "No" : \
	(x == DRX_LOCKED) ? "Locked" : \
	(x == DRX_LOCK_STATE_1) ? "AGC lock" : \
	(x == DRX_LOCK_STATE_2) ? "sync lock" : \
	"(Invalid)")

#पूर्ण_अगर				/* __DRXJ_H__ */
