<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * cxd2880_tnrdmd.h
 * Sony CXD2880 DVB-T2/T tuner + demodulator driver
 * common control पूर्णांकerface
 *
 * Copyright (C) 2016, 2017, 2018 Sony Semiconductor Solutions Corporation
 */

#अगर_अघोषित CXD2880_TNRDMD_H
#घोषणा CXD2880_TNRDMD_H

#समावेश <linux/atomic.h>

#समावेश "cxd2880_common.h"
#समावेश "cxd2880_io.h"
#समावेश "cxd2880_dtv.h"
#समावेश "cxd2880_dvbt.h"
#समावेश "cxd2880_dvbt2.h"

#घोषणा CXD2880_TNRDMD_MAX_CFG_MEM_COUNT 100

#घोषणा slvt_unमुक्तze_reg(tnr_dmd) ((व्योम)((tnr_dmd)->io->ग_लिखो_reg\
((tnr_dmd)->io, CXD2880_IO_TGT_DMD, 0x01, 0x00)))

#घोषणा CXD2880_TNRDMD_INTERRUPT_TYPE_BUF_UNDERFLOW     0x0001
#घोषणा CXD2880_TNRDMD_INTERRUPT_TYPE_BUF_OVERFLOW      0x0002
#घोषणा CXD2880_TNRDMD_INTERRUPT_TYPE_BUF_ALMOST_EMPTY  0x0004
#घोषणा CXD2880_TNRDMD_INTERRUPT_TYPE_BUF_ALMOST_FULL   0x0008
#घोषणा CXD2880_TNRDMD_INTERRUPT_TYPE_BUF_RRDY	  0x0010
#घोषणा CXD2880_TNRDMD_INTERRUPT_TYPE_ILLEGAL_COMMAND      0x0020
#घोषणा CXD2880_TNRDMD_INTERRUPT_TYPE_ILLEGAL_ACCESS       0x0040
#घोषणा CXD2880_TNRDMD_INTERRUPT_TYPE_CPU_ERROR	    0x0100
#घोषणा CXD2880_TNRDMD_INTERRUPT_TYPE_LOCK		 0x0200
#घोषणा CXD2880_TNRDMD_INTERRUPT_TYPE_INV_LOCK	     0x0400
#घोषणा CXD2880_TNRDMD_INTERRUPT_TYPE_NOOFDM	       0x0800
#घोषणा CXD2880_TNRDMD_INTERRUPT_TYPE_EWS		  0x1000
#घोषणा CXD2880_TNRDMD_INTERRUPT_TYPE_EEW		  0x2000
#घोषणा CXD2880_TNRDMD_INTERRUPT_TYPE_FEC_FAIL	     0x4000

#घोषणा CXD2880_TNRDMD_INTERRUPT_LOCK_SEL_L1POST_OK	0x01
#घोषणा CXD2880_TNRDMD_INTERRUPT_LOCK_SEL_DMD_LOCK	 0x02
#घोषणा CXD2880_TNRDMD_INTERRUPT_LOCK_SEL_TS_LOCK	  0x04

क्रमागत cxd2880_tnrdmd_chip_id अणु
	CXD2880_TNRDMD_CHIP_ID_UNKNOWN = 0x00,
	CXD2880_TNRDMD_CHIP_ID_CXD2880_ES1_0X = 0x62,
	CXD2880_TNRDMD_CHIP_ID_CXD2880_ES1_11 = 0x6a
पूर्ण;

#घोषणा CXD2880_TNRDMD_CHIP_ID_VALID(chip_id) \
	(((chip_id) == CXD2880_TNRDMD_CHIP_ID_CXD2880_ES1_0X) || \
	 ((chip_id) == CXD2880_TNRDMD_CHIP_ID_CXD2880_ES1_11))

क्रमागत cxd2880_tnrdmd_state अणु
	CXD2880_TNRDMD_STATE_UNKNOWN,
	CXD2880_TNRDMD_STATE_SLEEP,
	CXD2880_TNRDMD_STATE_ACTIVE,
	CXD2880_TNRDMD_STATE_INVALID
पूर्ण;

क्रमागत cxd2880_tnrdmd_भागermode अणु
	CXD2880_TNRDMD_DIVERMODE_SINGLE,
	CXD2880_TNRDMD_DIVERMODE_MAIN,
	CXD2880_TNRDMD_DIVERMODE_SUB
पूर्ण;

क्रमागत cxd2880_tnrdmd_घड़ीmode अणु
	CXD2880_TNRDMD_CLOCKMODE_UNKNOWN,
	CXD2880_TNRDMD_CLOCKMODE_A,
	CXD2880_TNRDMD_CLOCKMODE_B,
	CXD2880_TNRDMD_CLOCKMODE_C
पूर्ण;

क्रमागत cxd2880_tnrdmd_tsout_अगर अणु
	CXD2880_TNRDMD_TSOUT_IF_TS,
	CXD2880_TNRDMD_TSOUT_IF_SPI,
	CXD2880_TNRDMD_TSOUT_IF_SDIO
पूर्ण;

क्रमागत cxd2880_tnrdmd_xtal_share अणु
	CXD2880_TNRDMD_XTAL_SHARE_NONE,
	CXD2880_TNRDMD_XTAL_SHARE_EXTREF,
	CXD2880_TNRDMD_XTAL_SHARE_MASTER,
	CXD2880_TNRDMD_XTAL_SHARE_SLAVE
पूर्ण;

क्रमागत cxd2880_tnrdmd_spectrum_sense अणु
	CXD2880_TNRDMD_SPECTRUM_NORMAL,
	CXD2880_TNRDMD_SPECTRUM_INV
पूर्ण;

क्रमागत cxd2880_tnrdmd_cfg_id अणु
	CXD2880_TNRDMD_CFG_OUTPUT_SEL_MSB,
	CXD2880_TNRDMD_CFG_TSVALID_ACTIVE_HI,
	CXD2880_TNRDMD_CFG_TSSYNC_ACTIVE_HI,
	CXD2880_TNRDMD_CFG_TSERR_ACTIVE_HI,
	CXD2880_TNRDMD_CFG_LATCH_ON_POSEDGE,
	CXD2880_TNRDMD_CFG_TSCLK_CONT,
	CXD2880_TNRDMD_CFG_TSCLK_MASK,
	CXD2880_TNRDMD_CFG_TSVALID_MASK,
	CXD2880_TNRDMD_CFG_TSERR_MASK,
	CXD2880_TNRDMD_CFG_TSERR_VALID_DIS,
	CXD2880_TNRDMD_CFG_TSPIN_CURRENT,
	CXD2880_TNRDMD_CFG_TSPIN_PULLUP_MANUAL,
	CXD2880_TNRDMD_CFG_TSPIN_PULLUP,
	CXD2880_TNRDMD_CFG_TSCLK_FREQ,
	CXD2880_TNRDMD_CFG_TSBYTECLK_MANUAL,
	CXD2880_TNRDMD_CFG_TS_PACKET_GAP,
	CXD2880_TNRDMD_CFG_TS_BACKWARDS_COMPATIBLE,
	CXD2880_TNRDMD_CFG_PWM_VALUE,
	CXD2880_TNRDMD_CFG_INTERRUPT,
	CXD2880_TNRDMD_CFG_INTERRUPT_LOCK_SEL,
	CXD2880_TNRDMD_CFG_INTERRUPT_INV_LOCK_SEL,
	CXD2880_TNRDMD_CFG_TS_BUF_ALMOST_EMPTY_THRS,
	CXD2880_TNRDMD_CFG_TS_BUF_ALMOST_FULL_THRS,
	CXD2880_TNRDMD_CFG_TS_BUF_RRDY_THRS,
	CXD2880_TNRDMD_CFG_FIXED_CLOCKMODE,
	CXD2880_TNRDMD_CFG_CABLE_INPUT,
	CXD2880_TNRDMD_CFG_DVBT2_FEF_INTERMITTENT_BASE,
	CXD2880_TNRDMD_CFG_DVBT2_FEF_INTERMITTENT_LITE,
	CXD2880_TNRDMD_CFG_BLINDTUNE_DVBT2_FIRST,
	CXD2880_TNRDMD_CFG_DVBT_BERN_PERIOD,
	CXD2880_TNRDMD_CFG_DVBT_VBER_PERIOD,
	CXD2880_TNRDMD_CFG_DVBT_PER_MES,
	CXD2880_TNRDMD_CFG_DVBT2_BBER_MES,
	CXD2880_TNRDMD_CFG_DVBT2_LBER_MES,
	CXD2880_TNRDMD_CFG_DVBT2_PER_MES,
पूर्ण;

क्रमागत cxd2880_tnrdmd_lock_result अणु
	CXD2880_TNRDMD_LOCK_RESULT_NOTDETECT,
	CXD2880_TNRDMD_LOCK_RESULT_LOCKED,
	CXD2880_TNRDMD_LOCK_RESULT_UNLOCKED
पूर्ण;

क्रमागत cxd2880_tnrdmd_gpio_mode अणु
	CXD2880_TNRDMD_GPIO_MODE_OUTPUT = 0x00,
	CXD2880_TNRDMD_GPIO_MODE_INPUT = 0x01,
	CXD2880_TNRDMD_GPIO_MODE_INT = 0x02,
	CXD2880_TNRDMD_GPIO_MODE_FEC_FAIL = 0x03,
	CXD2880_TNRDMD_GPIO_MODE_PWM = 0x04,
	CXD2880_TNRDMD_GPIO_MODE_EWS = 0x05,
	CXD2880_TNRDMD_GPIO_MODE_EEW = 0x06
पूर्ण;

क्रमागत cxd2880_tnrdmd_serial_ts_clk अणु
	CXD2880_TNRDMD_SERIAL_TS_CLK_FULL,
	CXD2880_TNRDMD_SERIAL_TS_CLK_HALF
पूर्ण;

काष्ठा cxd2880_tnrdmd_cfg_mem अणु
	क्रमागत cxd2880_io_tgt tgt;
	u8 bank;
	u8 address;
	u8 value;
	u8 bit_mask;
पूर्ण;

काष्ठा cxd2880_tnrdmd_pid_cfg अणु
	u8 is_en;
	u16 pid;
पूर्ण;

काष्ठा cxd2880_tnrdmd_pid_ftr_cfg अणु
	u8 is_negative;
	काष्ठा cxd2880_tnrdmd_pid_cfg pid_cfg[32];
पूर्ण;

काष्ठा cxd2880_tnrdmd_lna_thrs अणु
	u8 off_on;
	u8 on_off;
पूर्ण;

काष्ठा cxd2880_tnrdmd_lna_thrs_tbl_air अणु
	काष्ठा cxd2880_tnrdmd_lna_thrs thrs[24];
पूर्ण;

काष्ठा cxd2880_tnrdmd_lna_thrs_tbl_cable अणु
	काष्ठा cxd2880_tnrdmd_lna_thrs thrs[32];
पूर्ण;

काष्ठा cxd2880_tnrdmd_create_param अणु
	क्रमागत cxd2880_tnrdmd_tsout_अगर ts_output_अगर;
	u8 en_पूर्णांकernal_lकरो;
	क्रमागत cxd2880_tnrdmd_xtal_share xtal_share_type;
	u8 xosc_cap;
	u8 xosc_i;
	u8 is_cxd2881gg;
	u8 stationary_use;
पूर्ण;

काष्ठा cxd2880_tnrdmd_भागer_create_param अणु
	क्रमागत cxd2880_tnrdmd_tsout_अगर ts_output_अगर;
	u8 en_पूर्णांकernal_lकरो;
	u8 xosc_cap_मुख्य;
	u8 xosc_i_मुख्य;
	u8 xosc_i_sub;
	u8 is_cxd2881gg;
	u8 stationary_use;
पूर्ण;

काष्ठा cxd2880_tnrdmd अणु
	काष्ठा cxd2880_tnrdmd *भागer_sub;
	काष्ठा cxd2880_io *io;
	काष्ठा cxd2880_tnrdmd_create_param create_param;
	क्रमागत cxd2880_tnrdmd_भागermode भागer_mode;
	क्रमागत cxd2880_tnrdmd_घड़ीmode fixed_clk_mode;
	u8 is_cable_input;
	u8 en_fef_पूर्णांकmtnt_base;
	u8 en_fef_पूर्णांकmtnt_lite;
	u8 blind_tune_dvbt2_first;
	पूर्णांक (*rf_lvl_cmpstn)(काष्ठा cxd2880_tnrdmd *tnr_dmd,
			     पूर्णांक *rf_lvl_db);
	काष्ठा cxd2880_tnrdmd_lna_thrs_tbl_air *lna_thrs_tbl_air;
	काष्ठा cxd2880_tnrdmd_lna_thrs_tbl_cable *lna_thrs_tbl_cable;
	u8 srl_ts_clk_mod_cnts;
	क्रमागत cxd2880_tnrdmd_serial_ts_clk srl_ts_clk_frq;
	u8 ts_byte_clk_manual_setting;
	u8 is_ts_backwards_compatible_mode;
	काष्ठा cxd2880_tnrdmd_cfg_mem cfg_mem[CXD2880_TNRDMD_MAX_CFG_MEM_COUNT];
	u8 cfg_mem_last_entry;
	काष्ठा cxd2880_tnrdmd_pid_ftr_cfg pid_ftr_cfg;
	u8 pid_ftr_cfg_en;
	व्योम *user;
	क्रमागत cxd2880_tnrdmd_chip_id chip_id;
	क्रमागत cxd2880_tnrdmd_state state;
	क्रमागत cxd2880_tnrdmd_घड़ीmode clk_mode;
	u32 frequency_khz;
	क्रमागत cxd2880_dtv_sys sys;
	क्रमागत cxd2880_dtv_bandwidth bandwidth;
	u8 scan_mode;
	atomic_t cancel;
पूर्ण;

पूर्णांक cxd2880_tnrdmd_create(काष्ठा cxd2880_tnrdmd *tnr_dmd,
			  काष्ठा cxd2880_io *io,
			  काष्ठा cxd2880_tnrdmd_create_param
			  *create_param);

पूर्णांक cxd2880_tnrdmd_भागer_create(काष्ठा cxd2880_tnrdmd
				*tnr_dmd_मुख्य,
				काष्ठा cxd2880_io *io_मुख्य,
				काष्ठा cxd2880_tnrdmd *tnr_dmd_sub,
				काष्ठा cxd2880_io *io_sub,
				काष्ठा
				cxd2880_tnrdmd_भागer_create_param
				*create_param);

पूर्णांक cxd2880_tnrdmd_init1(काष्ठा cxd2880_tnrdmd *tnr_dmd);

पूर्णांक cxd2880_tnrdmd_init2(काष्ठा cxd2880_tnrdmd *tnr_dmd);

पूर्णांक cxd2880_tnrdmd_check_पूर्णांकernal_cpu_status(काष्ठा cxd2880_tnrdmd
					     *tnr_dmd,
					     u8 *task_completed);

पूर्णांक cxd2880_tnrdmd_common_tune_setting1(काष्ठा cxd2880_tnrdmd
					*tnr_dmd,
					क्रमागत cxd2880_dtv_sys sys,
					u32 frequency_khz,
					क्रमागत cxd2880_dtv_bandwidth
					bandwidth, u8 one_seg_opt,
					u8 one_seg_opt_shft_dir);

पूर्णांक cxd2880_tnrdmd_common_tune_setting2(काष्ठा cxd2880_tnrdmd
					*tnr_dmd,
					क्रमागत cxd2880_dtv_sys sys,
					u8 en_fef_पूर्णांकmtnt_ctrl);

पूर्णांक cxd2880_tnrdmd_sleep(काष्ठा cxd2880_tnrdmd *tnr_dmd);

पूर्णांक cxd2880_tnrdmd_set_cfg(काष्ठा cxd2880_tnrdmd *tnr_dmd,
			   क्रमागत cxd2880_tnrdmd_cfg_id id,
			   पूर्णांक value);

पूर्णांक cxd2880_tnrdmd_gpio_set_cfg(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				u8 id,
				u8 en,
				क्रमागत cxd2880_tnrdmd_gpio_mode mode,
				u8 खोलो_drain, u8 invert);

पूर्णांक cxd2880_tnrdmd_gpio_set_cfg_sub(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				    u8 id,
				    u8 en,
				    क्रमागत cxd2880_tnrdmd_gpio_mode
				    mode, u8 खोलो_drain,
				    u8 invert);

पूर्णांक cxd2880_tnrdmd_gpio_पढ़ो(काष्ठा cxd2880_tnrdmd *tnr_dmd,
			     u8 id, u8 *value);

पूर्णांक cxd2880_tnrdmd_gpio_पढ़ो_sub(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				 u8 id, u8 *value);

पूर्णांक cxd2880_tnrdmd_gpio_ग_लिखो(काष्ठा cxd2880_tnrdmd *tnr_dmd,
			      u8 id, u8 value);

पूर्णांक cxd2880_tnrdmd_gpio_ग_लिखो_sub(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				  u8 id, u8 value);

पूर्णांक cxd2880_tnrdmd_पूर्णांकerrupt_पढ़ो(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				  u16 *value);

पूर्णांक cxd2880_tnrdmd_पूर्णांकerrupt_clear(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				   u16 value);

पूर्णांक cxd2880_tnrdmd_ts_buf_clear(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				u8 clear_overflow_flag,
				u8 clear_underflow_flag,
				u8 clear_buf);

पूर्णांक cxd2880_tnrdmd_chip_id(काष्ठा cxd2880_tnrdmd *tnr_dmd,
			   क्रमागत cxd2880_tnrdmd_chip_id *chip_id);

पूर्णांक cxd2880_tnrdmd_set_and_save_reg_bits(काष्ठा cxd2880_tnrdmd
					 *tnr_dmd,
					 क्रमागत cxd2880_io_tgt tgt,
					 u8 bank, u8 address,
					 u8 value, u8 bit_mask);

पूर्णांक cxd2880_tnrdmd_set_scan_mode(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				 क्रमागत cxd2880_dtv_sys sys,
				 u8 scan_mode_end);

पूर्णांक cxd2880_tnrdmd_set_pid_ftr(काष्ठा cxd2880_tnrdmd *tnr_dmd,
			       काष्ठा cxd2880_tnrdmd_pid_ftr_cfg
			       *pid_ftr_cfg);

पूर्णांक cxd2880_tnrdmd_set_rf_lvl_cmpstn(काष्ठा cxd2880_tnrdmd
				     *tnr_dmd,
				     पूर्णांक (*rf_lvl_cmpstn)
				     (काष्ठा cxd2880_tnrdmd *,
				     पूर्णांक *));

पूर्णांक cxd2880_tnrdmd_set_rf_lvl_cmpstn_sub(काष्ठा cxd2880_tnrdmd *tnr_dmd,
					 पूर्णांक (*rf_lvl_cmpstn)
					 (काष्ठा cxd2880_tnrdmd *,
					 पूर्णांक *));

पूर्णांक cxd2880_tnrdmd_set_lna_thrs(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				काष्ठा
				cxd2880_tnrdmd_lna_thrs_tbl_air
				*tbl_air,
				काष्ठा
				cxd2880_tnrdmd_lna_thrs_tbl_cable
				*tbl_cable);

पूर्णांक cxd2880_tnrdmd_set_lna_thrs_sub(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				    काष्ठा
				    cxd2880_tnrdmd_lna_thrs_tbl_air
				    *tbl_air,
				    काष्ठा
				    cxd2880_tnrdmd_lna_thrs_tbl_cable
				    *tbl_cable);

पूर्णांक cxd2880_tnrdmd_set_ts_pin_high_low(काष्ठा cxd2880_tnrdmd
				       *tnr_dmd, u8 en, u8 value);

पूर्णांक cxd2880_tnrdmd_set_ts_output(काष्ठा cxd2880_tnrdmd *tnr_dmd,
				 u8 en);

पूर्णांक slvt_मुक्तze_reg(काष्ठा cxd2880_tnrdmd *tnr_dmd);

#पूर्ण_अगर
