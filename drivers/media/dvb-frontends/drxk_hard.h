<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश "drxk_map.h"

#घोषणा DRXK_VERSION_MAJOR 0
#घोषणा DRXK_VERSION_MINOR 9
#घोषणा DRXK_VERSION_PATCH 4300

#घोषणा HI_I2C_DELAY        42
#घोषणा HI_I2C_BRIDGE_DELAY 350
#घोषणा DRXK_MAX_RETRIES    100

#घोषणा DRIVER_4400 1

#घोषणा DRXX_JTAGID   0x039210D9
#घोषणा DRXX_J_JTAGID 0x239310D9
#घोषणा DRXX_K_JTAGID 0x039210D9

#घोषणा DRX_UNKNOWN     254
#घोषणा DRX_AUTO        255

#घोषणा DRX_SCU_READY   0
#घोषणा DRXK_MAX_WAITTIME (200)
#घोषणा SCU_RESULT_OK      0
#घोषणा SCU_RESULT_SIZE   -4
#घोषणा SCU_RESULT_INVPAR -3
#घोषणा SCU_RESULT_UNKSTD -2
#घोषणा SCU_RESULT_UNKCMD -1

#अगर_अघोषित DRXK_OFDM_TR_SHUTDOWN_TIMEOUT
#घोषणा DRXK_OFDM_TR_SHUTDOWN_TIMEOUT (200)
#पूर्ण_अगर

#घोषणा DRXK_8VSB_MPEG_BIT_RATE     19392658UL  /*bps*/
#घोषणा DRXK_DVBT_MPEG_BIT_RATE     32000000UL  /*bps*/
#घोषणा DRXK_QAM16_MPEG_BIT_RATE    27000000UL  /*bps*/
#घोषणा DRXK_QAM32_MPEG_BIT_RATE    33000000UL  /*bps*/
#घोषणा DRXK_QAM64_MPEG_BIT_RATE    40000000UL  /*bps*/
#घोषणा DRXK_QAM128_MPEG_BIT_RATE   46000000UL  /*bps*/
#घोषणा DRXK_QAM256_MPEG_BIT_RATE   52000000UL  /*bps*/
#घोषणा DRXK_MAX_MPEG_BIT_RATE      52000000UL  /*bps*/

#घोषणा   IQM_CF_OUT_ENA_OFDM__M                                            0x4
#घोषणा     IQM_FS_ADJ_SEL_B_QAM                                            0x1
#घोषणा     IQM_FS_ADJ_SEL_B_OFF                                            0x0
#घोषणा     IQM_FS_ADJ_SEL_B_VSB                                            0x2
#घोषणा     IQM_RC_ADJ_SEL_B_OFF                                            0x0
#घोषणा     IQM_RC_ADJ_SEL_B_QAM                                            0x1
#घोषणा     IQM_RC_ADJ_SEL_B_VSB                                            0x2

क्रमागत operation_mode अणु
	OM_NONE,
	OM_QAM_ITU_A,
	OM_QAM_ITU_B,
	OM_QAM_ITU_C,
	OM_DVBT
पूर्ण;

क्रमागत drx_घातer_mode अणु
	DRX_POWER_UP = 0,
	DRX_POWER_MODE_1,
	DRX_POWER_MODE_2,
	DRX_POWER_MODE_3,
	DRX_POWER_MODE_4,
	DRX_POWER_MODE_5,
	DRX_POWER_MODE_6,
	DRX_POWER_MODE_7,
	DRX_POWER_MODE_8,

	DRX_POWER_MODE_9,
	DRX_POWER_MODE_10,
	DRX_POWER_MODE_11,
	DRX_POWER_MODE_12,
	DRX_POWER_MODE_13,
	DRX_POWER_MODE_14,
	DRX_POWER_MODE_15,
	DRX_POWER_MODE_16,
	DRX_POWER_DOWN = 255
पूर्ण;


/* Intermediate घातer mode क्रम DRXK, घातer करोwn OFDM घड़ी करोमुख्य */
#अगर_अघोषित DRXK_POWER_DOWN_OFDM
#घोषणा DRXK_POWER_DOWN_OFDM        DRX_POWER_MODE_1
#पूर्ण_अगर

/* Intermediate घातer mode क्रम DRXK, घातer करोwn core (sysclk) */
#अगर_अघोषित DRXK_POWER_DOWN_CORE
#घोषणा DRXK_POWER_DOWN_CORE        DRX_POWER_MODE_9
#पूर्ण_अगर

/* Intermediate घातer mode क्रम DRXK, घातer करोwn pll (only osc runs) */
#अगर_अघोषित DRXK_POWER_DOWN_PLL
#घोषणा DRXK_POWER_DOWN_PLL         DRX_POWER_MODE_10
#पूर्ण_अगर


क्रमागत agc_ctrl_mode अणु
	DRXK_AGC_CTRL_AUTO = 0,
	DRXK_AGC_CTRL_USER,
	DRXK_AGC_CTRL_OFF
पूर्ण;

क्रमागत e_drxk_state अणु
	DRXK_UNINITIALIZED = 0,
	DRXK_STOPPED,
	DRXK_DTV_STARTED,
	DRXK_ATV_STARTED,
	DRXK_POWERED_DOWN,
	DRXK_NO_DEV			/* If drxk init failed */
पूर्ण;

क्रमागत e_drxk_coef_array_index अणु
	DRXK_COEF_IDX_MN = 0,
	DRXK_COEF_IDX_FM    ,
	DRXK_COEF_IDX_L     ,
	DRXK_COEF_IDX_LP    ,
	DRXK_COEF_IDX_BG    ,
	DRXK_COEF_IDX_DK    ,
	DRXK_COEF_IDX_I     ,
	DRXK_COEF_IDX_MAX
पूर्ण;
क्रमागत e_drxk_sअगर_attenuation अणु
	DRXK_SIF_ATTENUATION_0DB,
	DRXK_SIF_ATTENUATION_3DB,
	DRXK_SIF_ATTENUATION_6DB,
	DRXK_SIF_ATTENUATION_9DB
पूर्ण;
क्रमागत e_drxk_स्थिरellation अणु
	DRX_CONSTELLATION_BPSK = 0,
	DRX_CONSTELLATION_QPSK,
	DRX_CONSTELLATION_PSK8,
	DRX_CONSTELLATION_QAM16,
	DRX_CONSTELLATION_QAM32,
	DRX_CONSTELLATION_QAM64,
	DRX_CONSTELLATION_QAM128,
	DRX_CONSTELLATION_QAM256,
	DRX_CONSTELLATION_QAM512,
	DRX_CONSTELLATION_QAM1024,
	DRX_CONSTELLATION_UNKNOWN = DRX_UNKNOWN,
	DRX_CONSTELLATION_AUTO    = DRX_AUTO
पूर्ण;
क्रमागत e_drxk_पूर्णांकerleave_mode अणु
	DRXK_QAM_I12_J17    = 16,
	DRXK_QAM_I_UNKNOWN  = DRX_UNKNOWN
पूर्ण;
क्रमागत अणु
	DRXK_SPIN_A1 = 0,
	DRXK_SPIN_A2,
	DRXK_SPIN_A3,
	DRXK_SPIN_UNKNOWN
पूर्ण;

क्रमागत drxk_cfg_dvbt_sqi_speed अणु
	DRXK_DVBT_SQI_SPEED_FAST = 0,
	DRXK_DVBT_SQI_SPEED_MEDIUM,
	DRXK_DVBT_SQI_SPEED_SLOW,
	DRXK_DVBT_SQI_SPEED_UNKNOWN = DRX_UNKNOWN
पूर्ण ;

क्रमागत drx_ffपंचांगode_t अणु
	DRX_FFTMODE_2K = 0,
	DRX_FFTMODE_4K,
	DRX_FFTMODE_8K,
	DRX_FFTMODE_UNKNOWN = DRX_UNKNOWN,
	DRX_FFTMODE_AUTO    = DRX_AUTO
पूर्ण;

क्रमागत drxmpeg_str_width_t अणु
	DRX_MPEG_STR_WIDTH_1,
	DRX_MPEG_STR_WIDTH_8
पूर्ण;

क्रमागत drx_qam_lock_range_t अणु
	DRX_QAM_LOCKRANGE_NORMAL,
	DRX_QAM_LOCKRANGE_EXTENDED
पूर्ण;

काष्ठा drxk_cfg_dvbt_echo_thres_t अणु
	u16             threshold;
	क्रमागत drx_ffपंचांगode_t      fft_mode;
पूर्ण ;

काष्ठा s_cfg_agc अणु
	क्रमागत agc_ctrl_mode     ctrl_mode;        /* off, user, स्वतः */
	u16            output_level;     /* range dependent on AGC */
	u16            min_output_level;  /* range dependent on AGC */
	u16            max_output_level;  /* range dependent on AGC */
	u16            speed;           /* range dependent on AGC */
	u16            top;             /* rf-agc take over poपूर्णांक */
	u16            cut_off_current;   /* rf-agc is accelerated अगर output current
					   is below cut-off current */
	u16            ingain_tgt_max;
	u16            fast_clip_ctrl_delay;
पूर्ण;

काष्ठा s_cfg_pre_saw अणु
	u16        reference; /* pre SAW reference value, range 0 .. 31 */
	bool          use_pre_saw; /* TRUE algorithms must use pre SAW sense */
पूर्ण;

काष्ठा drxk_ofdm_sc_cmd_t अणु
	u16 cmd;        /* Command number */
	u16 subcmd;     /* Sub-command parameter*/
	u16 param0;     /* General purpous param */
	u16 param1;     /* General purpous param */
	u16 param2;     /* General purpous param */
	u16 param3;     /* General purpous param */
	u16 param4;     /* General purpous param */
पूर्ण;

काष्ठा drxk_state अणु
	काष्ठा dvb_frontend frontend;
	काष्ठा dtv_frontend_properties props;
	काष्ठा device *dev;

	काष्ठा i2c_adapter *i2c;
	u8     demod_address;
	व्योम  *priv;

	काष्ठा mutex mutex;

	u32    m_instance;           /* Channel 1,2,3 or 4 */

	पूर्णांक    m_chunk_size;
	u8 chunk[256];

	bool   m_has_lna;
	bool   m_has_dvbt;
	bool   m_has_dvbc;
	bool   m_has_audio;
	bool   m_has_atv;
	bool   m_has_oob;
	bool   m_has_sawsw;         /* TRUE अगर mat_tx is available */
	bool   m_has_gpio1;         /* TRUE अगर mat_rx is available */
	bool   m_has_gpio2;         /* TRUE अगर GPIO is available */
	bool   m_has_irqn;          /* TRUE अगर IRQN is available */
	u16    m_osc_घड़ी_freq;
	u16    m_hi_cfg_timing_भाग;
	u16    m_hi_cfg_bridge_delay;
	u16    m_hi_cfg_wake_up_key;
	u16    m_hi_cfg_समयout;
	u16    m_hi_cfg_ctrl;
	s32    m_sys_घड़ी_freq;      /* प्रणाली घड़ी frequency in kHz */

	क्रमागत e_drxk_state    m_drxk_state;      /* State of Drxk (init,stopped,started) */
	क्रमागत operation_mode m_operation_mode;  /* digital standards */
	काष्ठा s_cfg_agc     m_vsb_rf_agc_cfg;    /* settings क्रम VSB RF-AGC */
	काष्ठा s_cfg_agc     m_vsb_अगर_agc_cfg;    /* settings क्रम VSB IF-AGC */
	u16                m_vsb_pga_cfg;      /* settings क्रम VSB PGA */
	काष्ठा s_cfg_pre_saw  m_vsb_pre_saw_cfg;   /* settings क्रम pre SAW sense */
	s32    m_Quality83percent;  /* MER level (*0.1 dB) क्रम 83% quality indication */
	s32    m_Quality93percent;  /* MER level (*0.1 dB) क्रम 93% quality indication */
	bool   m_smart_ant_inverted;
	bool   m_b_debug_enable_bridge;
	bool   m_b_p_करोwn_खोलो_bridge;  /* only खोलो DRXK bridge beक्रमe घातer-करोwn once it has been accessed */
	bool   m_b_घातer_करोwn;        /* Power करोwn when not used */

	u32    m_iqm_fs_rate_ofs;      /* frequency shअगरt as written to DRXK रेजिस्टर (28bit fixpoपूर्णांक) */

	bool   m_enable_mpeg_output;  /* If TRUE, enable MPEG output */
	bool   m_insert_rs_byte;      /* If TRUE, insert RS byte */
	bool   m_enable_parallel;    /* If TRUE, parallel out otherwise serial */
	bool   m_invert_data;        /* If TRUE, invert DATA संकेतs */
	bool   m_invert_err;         /* If TRUE, invert ERR संकेत */
	bool   m_invert_str;         /* If TRUE, invert STR संकेतs */
	bool   m_invert_val;         /* If TRUE, invert VAL संकेतs */
	bool   m_invert_clk;         /* If TRUE, invert CLK संकेतs */
	bool   m_dvbc_अटल_clk;
	bool   m_dvbt_अटल_clk;     /* If TRUE, अटल MPEG घड़ीrate will
					 be used, otherwise घड़ीrate will
					 adapt to the bitrate of the TS */
	u32    m_dvbt_bitrate;
	u32    m_dvbc_bitrate;

	u8     m_ts_data_strength;
	u8     m_ts_घड़ीk_strength;

	bool   m_itut_annex_c;      /* If true, uses ITU-T DVB-C Annex C, instead of Annex A */

	क्रमागत drxmpeg_str_width_t  m_width_str;    /* MPEG start width */
	u32    m_mpeg_ts_अटल_bitrate;          /* Maximum bitrate in b/s in हाल
						    अटल घड़ीrate is selected */

	/* LARGE_INTEGER   m_startTime; */     /* Contains the समय of the last demod start */
	s32    m_mpeg_lock_समय_out;      /* WaitForLockStatus Timeout (counts from start समय) */
	s32    m_demod_lock_समय_out;     /* WaitForLockStatus Timeout (counts from start समय) */

	bool   m_disable_te_ihandling;

	bool   m_rf_agc_pol;
	bool   m_अगर_agc_pol;

	काष्ठा s_cfg_agc    m_atv_rf_agc_cfg;  /* settings क्रम ATV RF-AGC */
	काष्ठा s_cfg_agc    m_atv_अगर_agc_cfg;  /* settings क्रम ATV IF-AGC */
	काष्ठा s_cfg_pre_saw m_atv_pre_saw_cfg; /* settings क्रम ATV pre SAW sense */
	bool              m_phase_correction_bypass;
	s16               m_atv_top_vid_peak;
	u16               m_atv_top_noise_th;
	क्रमागत e_drxk_sअगर_attenuation m_sअगर_attenuation;
	bool              m_enable_cvbs_output;
	bool              m_enable_sअगर_output;
	bool              m_b_mirror_freq_spect;
	क्रमागत e_drxk_स्थिरellation  m_स्थिरellation; /* स्थिरellation type of the channel */
	u32               m_curr_symbol_rate;       /* Current QAM symbol rate */
	काष्ठा s_cfg_agc    m_qam_rf_agc_cfg;          /* settings क्रम QAM RF-AGC */
	काष्ठा s_cfg_agc    m_qam_अगर_agc_cfg;          /* settings क्रम QAM IF-AGC */
	u16               m_qam_pga_cfg;            /* settings क्रम QAM PGA */
	काष्ठा s_cfg_pre_saw m_qam_pre_saw_cfg;         /* settings क्रम QAM pre SAW sense */
	क्रमागत e_drxk_पूर्णांकerleave_mode m_qam_पूर्णांकerleave_mode; /* QAM Interleave mode */
	u16               m_fec_rs_plen;
	u16               m_fec_rs_prescale;

	क्रमागत drxk_cfg_dvbt_sqi_speed m_sqi_speed;

	u16               m_gpio;
	u16               m_gpio_cfg;

	काष्ठा s_cfg_agc    m_dvbt_rf_agc_cfg;     /* settings क्रम QAM RF-AGC */
	काष्ठा s_cfg_agc    m_dvbt_अगर_agc_cfg;     /* settings क्रम QAM IF-AGC */
	काष्ठा s_cfg_pre_saw m_dvbt_pre_saw_cfg;    /* settings क्रम QAM pre SAW sense */

	u16               m_agcfast_clip_ctrl_delay;
	bool              m_adc_comp_passed;
	u16               m_adcCompCoef[64];
	u16               m_adc_state;

	u8               *m_microcode;
	पूर्णांक               m_microcode_length;
	bool		  m_drxk_a3_rom_code;
	bool              m_drxk_a3_patch_code;

	bool              m_rfmirror;
	u8                m_device_spin;
	u32               m_iqm_rc_rate;

	क्रमागत drx_घातer_mode m_current_घातer_mode;

	/* when true, aव्योमs other devices to use the I2C bus */
	bool		  drxk_i2c_exclusive_lock;

	/*
	 * Configurable parameters at the driver. They stores the values found
	 * at काष्ठा drxk_config.
	 */

	u16	uio_mask;	/* Bits used by UIO */

	bool	enable_merr_cfg;
	bool	single_master;
	bool	no_i2c_bridge;
	bool	antenna_dvbt;
	u16	antenna_gpio;

	क्रमागत fe_status fe_status;

	/* Firmware */
	स्थिर अक्षर *microcode_name;
	काष्ठा completion fw_रुको_load;
	स्थिर काष्ठा firmware *fw;
	पूर्णांक qam_demod_parameter_count;
पूर्ण;

#घोषणा NEVER_LOCK 0
#घोषणा NOT_LOCKED 1
#घोषणा DEMOD_LOCK 2
#घोषणा FEC_LOCK   3
#घोषणा MPEG_LOCK  4

