<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम the Conexant CX23885 PCIe bridge
 *
 *  Copyright (c) 2006 Steven Toth <stoth@linuxtv.org>
 */

#समावेश "cx23885.h"

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/fs.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/file.h>
#समावेश <linux/suspend.h>

#समावेश <media/v4l2-common.h>

#समावेश <media/dvb_ca_en50221.h>
#समावेश "s5h1409.h"
#समावेश "s5h1411.h"
#समावेश "mt2131.h"
#समावेश "tda8290.h"
#समावेश "tda18271.h"
#समावेश "lgdt330x.h"
#समावेश "xc4000.h"
#समावेश "xc5000.h"
#समावेश "max2165.h"
#समावेश "tda10048.h"
#समावेश "tuner-xc2028.h"
#समावेश "tuner-simple.h"
#समावेश "dib7000p.h"
#समावेश "dib0070.h"
#समावेश "dibx000_common.h"
#समावेश "zl10353.h"
#समावेश "stv0900.h"
#समावेश "stv0900_reg.h"
#समावेश "stv6110.h"
#समावेश "lnbh24.h"
#समावेश "cx24116.h"
#समावेश "cx24117.h"
#समावेश "cimax2.h"
#समावेश "lgs8gxx.h"
#समावेश "netup-eeprom.h"
#समावेश "netup-init.h"
#समावेश "lgdt3305.h"
#समावेश "atbm8830.h"
#समावेश "ts2020.h"
#समावेश "ds3000.h"
#समावेश "cx23885-f300.h"
#समावेश "altera-ci.h"
#समावेश "stv0367.h"
#समावेश "drxk.h"
#समावेश "mt2063.h"
#समावेश "stv090x.h"
#समावेश "stb6100.h"
#समावेश "stb6100_cfg.h"
#समावेश "tda10071.h"
#समावेश "a8293.h"
#समावेश "mb86a20s.h"
#समावेश "si2165.h"
#समावेश "si2168.h"
#समावेश "si2157.h"
#समावेश "sp2.h"
#समावेश "m88ds3103.h"
#समावेश "m88rs6000t.h"
#समावेश "lgdt3306a.h"

अटल अचिन्हित पूर्णांक debug;

#घोषणा dprपूर्णांकk(level, fmt, arg...)\
	करो अणु अगर (debug >= level)\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s dvb: " fmt), \
			__func__, ##arg); \
	पूर्ण जबतक (0)

/* ------------------------------------------------------------------ */

अटल अचिन्हित पूर्णांक alt_tuner;
module_param(alt_tuner, पूर्णांक, 0644);
MODULE_PARM_DESC(alt_tuner, "Enable alternate tuner configuration");

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

/* ------------------------------------------------------------------ */

अटल पूर्णांक queue_setup(काष्ठा vb2_queue *q,
			   अचिन्हित पूर्णांक *num_buffers, अचिन्हित पूर्णांक *num_planes,
			   अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा cx23885_tsport *port = q->drv_priv;

	port->ts_packet_size  = 188 * 4;
	port->ts_packet_count = 32;
	*num_planes = 1;
	sizes[0] = port->ts_packet_size * port->ts_packet_count;
	*num_buffers = 32;
	वापस 0;
पूर्ण


अटल पूर्णांक buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा cx23885_tsport *port = vb->vb2_queue->drv_priv;
	काष्ठा cx23885_buffer *buf =
		container_of(vbuf, काष्ठा cx23885_buffer, vb);

	वापस cx23885_buf_prepare(buf, port);
पूर्ण

अटल व्योम buffer_finish(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा cx23885_tsport *port = vb->vb2_queue->drv_priv;
	काष्ठा cx23885_dev *dev = port->dev;
	काष्ठा cx23885_buffer *buf = container_of(vbuf,
		काष्ठा cx23885_buffer, vb);

	cx23885_मुक्त_buffer(dev, buf);
पूर्ण

अटल व्योम buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा cx23885_tsport *port = vb->vb2_queue->drv_priv;
	काष्ठा cx23885_buffer   *buf = container_of(vbuf,
		काष्ठा cx23885_buffer, vb);

	cx23885_buf_queue(port, buf);
पूर्ण

अटल व्योम cx23885_dvb_gate_ctrl(काष्ठा cx23885_tsport  *port, पूर्णांक खोलो)
अणु
	काष्ठा vb2_dvb_frontends *f;
	काष्ठा vb2_dvb_frontend *fe;

	f = &port->frontends;

	अगर (f->gate <= 1) /* undefined or fe0 */
		fe = vb2_dvb_get_frontend(f, 1);
	अन्यथा
		fe = vb2_dvb_get_frontend(f, f->gate);

	अगर (fe && fe->dvb.frontend && fe->dvb.frontend->ops.i2c_gate_ctrl)
		fe->dvb.frontend->ops.i2c_gate_ctrl(fe->dvb.frontend, खोलो);
पूर्ण

अटल पूर्णांक cx23885_start_streaming(काष्ठा vb2_queue *q, अचिन्हित पूर्णांक count)
अणु
	काष्ठा cx23885_tsport *port = q->drv_priv;
	काष्ठा cx23885_dmaqueue *dmaq = &port->mpegq;
	काष्ठा cx23885_buffer *buf = list_entry(dmaq->active.next,
			काष्ठा cx23885_buffer, queue);

	cx23885_start_dma(port, dmaq, buf);
	वापस 0;
पूर्ण

अटल व्योम cx23885_stop_streaming(काष्ठा vb2_queue *q)
अणु
	काष्ठा cx23885_tsport *port = q->drv_priv;

	cx23885_cancel_buffers(port);
पूर्ण

अटल स्थिर काष्ठा vb2_ops dvb_qops = अणु
	.queue_setup    = queue_setup,
	.buf_prepare  = buffer_prepare,
	.buf_finish = buffer_finish,
	.buf_queue    = buffer_queue,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
	.start_streaming = cx23885_start_streaming,
	.stop_streaming = cx23885_stop_streaming,
पूर्ण;

अटल काष्ठा s5h1409_config hauppauge_generic_config = अणु
	.demod_address = 0x32 >> 1,
	.output_mode   = S5H1409_SERIAL_OUTPUT,
	.gpio          = S5H1409_GPIO_ON,
	.qam_अगर        = 44000,
	.inversion     = S5H1409_INVERSION_OFF,
	.status_mode   = S5H1409_DEMODLOCKING,
	.mpeg_timing   = S5H1409_MPEGTIMING_CONTINUOUS_NONINVERTING_CLOCK,
पूर्ण;

अटल काष्ठा tda10048_config hauppauge_hvr1200_config = अणु
	.demod_address    = 0x10 >> 1,
	.output_mode      = TDA10048_SERIAL_OUTPUT,
	.fwbulkग_लिखोlen   = TDA10048_BULKWRITE_200,
	.inversion        = TDA10048_INVERSION_ON,
	.dtv6_अगर_freq_khz = TDA10048_IF_3300,
	.dtv7_अगर_freq_khz = TDA10048_IF_3800,
	.dtv8_अगर_freq_khz = TDA10048_IF_4300,
	.clk_freq_khz     = TDA10048_CLK_16000,
पूर्ण;

अटल काष्ठा tda10048_config hauppauge_hvr1210_config = अणु
	.demod_address    = 0x10 >> 1,
	.output_mode      = TDA10048_SERIAL_OUTPUT,
	.fwbulkग_लिखोlen   = TDA10048_BULKWRITE_200,
	.inversion        = TDA10048_INVERSION_ON,
	.dtv6_अगर_freq_khz = TDA10048_IF_3300,
	.dtv7_अगर_freq_khz = TDA10048_IF_3500,
	.dtv8_अगर_freq_khz = TDA10048_IF_4000,
	.clk_freq_khz     = TDA10048_CLK_16000,
पूर्ण;

अटल काष्ठा s5h1409_config hauppauge_ezqam_config = अणु
	.demod_address = 0x32 >> 1,
	.output_mode   = S5H1409_SERIAL_OUTPUT,
	.gpio          = S5H1409_GPIO_OFF,
	.qam_अगर        = 4000,
	.inversion     = S5H1409_INVERSION_ON,
	.status_mode   = S5H1409_DEMODLOCKING,
	.mpeg_timing   = S5H1409_MPEGTIMING_CONTINUOUS_NONINVERTING_CLOCK,
पूर्ण;

अटल काष्ठा s5h1409_config hauppauge_hvr1800lp_config = अणु
	.demod_address = 0x32 >> 1,
	.output_mode   = S5H1409_SERIAL_OUTPUT,
	.gpio          = S5H1409_GPIO_OFF,
	.qam_अगर        = 44000,
	.inversion     = S5H1409_INVERSION_OFF,
	.status_mode   = S5H1409_DEMODLOCKING,
	.mpeg_timing   = S5H1409_MPEGTIMING_CONTINUOUS_NONINVERTING_CLOCK,
पूर्ण;

अटल काष्ठा s5h1409_config hauppauge_hvr1500_config = अणु
	.demod_address = 0x32 >> 1,
	.output_mode   = S5H1409_SERIAL_OUTPUT,
	.gpio          = S5H1409_GPIO_OFF,
	.inversion     = S5H1409_INVERSION_OFF,
	.status_mode   = S5H1409_DEMODLOCKING,
	.mpeg_timing   = S5H1409_MPEGTIMING_CONTINUOUS_NONINVERTING_CLOCK,
पूर्ण;

अटल काष्ठा mt2131_config hauppauge_generic_tunerconfig = अणु
	0x61
पूर्ण;

अटल काष्ठा lgdt330x_config fusionhdtv_5_express = अणु
	.demod_chip = LGDT3303,
	.serial_mpeg = 0x40,
पूर्ण;

अटल काष्ठा s5h1409_config hauppauge_hvr1500q_config = अणु
	.demod_address = 0x32 >> 1,
	.output_mode   = S5H1409_SERIAL_OUTPUT,
	.gpio          = S5H1409_GPIO_ON,
	.qam_अगर        = 44000,
	.inversion     = S5H1409_INVERSION_OFF,
	.status_mode   = S5H1409_DEMODLOCKING,
	.mpeg_timing   = S5H1409_MPEGTIMING_CONTINUOUS_NONINVERTING_CLOCK,
पूर्ण;

अटल काष्ठा s5h1409_config dvico_s5h1409_config = अणु
	.demod_address = 0x32 >> 1,
	.output_mode   = S5H1409_SERIAL_OUTPUT,
	.gpio          = S5H1409_GPIO_ON,
	.qam_अगर        = 44000,
	.inversion     = S5H1409_INVERSION_OFF,
	.status_mode   = S5H1409_DEMODLOCKING,
	.mpeg_timing   = S5H1409_MPEGTIMING_CONTINUOUS_NONINVERTING_CLOCK,
पूर्ण;

अटल काष्ठा s5h1411_config dvico_s5h1411_config = अणु
	.output_mode   = S5H1411_SERIAL_OUTPUT,
	.gpio          = S5H1411_GPIO_ON,
	.qam_अगर        = S5H1411_IF_44000,
	.vsb_अगर        = S5H1411_IF_44000,
	.inversion     = S5H1411_INVERSION_OFF,
	.status_mode   = S5H1411_DEMODLOCKING,
	.mpeg_timing   = S5H1411_MPEGTIMING_CONTINUOUS_NONINVERTING_CLOCK,
पूर्ण;

अटल काष्ठा s5h1411_config hcw_s5h1411_config = अणु
	.output_mode   = S5H1411_SERIAL_OUTPUT,
	.gpio          = S5H1411_GPIO_OFF,
	.vsb_अगर        = S5H1411_IF_44000,
	.qam_अगर        = S5H1411_IF_4000,
	.inversion     = S5H1411_INVERSION_ON,
	.status_mode   = S5H1411_DEMODLOCKING,
	.mpeg_timing   = S5H1411_MPEGTIMING_CONTINUOUS_NONINVERTING_CLOCK,
पूर्ण;

अटल काष्ठा xc5000_config hauppauge_hvr1500q_tunerconfig = अणु
	.i2c_address      = 0x61,
	.अगर_khz           = 5380,
पूर्ण;

अटल काष्ठा xc5000_config dvico_xc5000_tunerconfig = अणु
	.i2c_address      = 0x64,
	.अगर_khz           = 5380,
पूर्ण;

अटल काष्ठा tda829x_config tda829x_no_probe = अणु
	.probe_tuner = TDA829X_DONT_PROBE,
पूर्ण;

अटल काष्ठा tda18271_std_map hauppauge_tda18271_std_map = अणु
	.atsc_6   = अणु .अगर_freq = 5380, .agc_mode = 3, .std = 3,
		      .अगर_lvl = 6, .rfagc_top = 0x37 पूर्ण,
	.qam_6    = अणु .अगर_freq = 4000, .agc_mode = 3, .std = 0,
		      .अगर_lvl = 6, .rfagc_top = 0x37 पूर्ण,
पूर्ण;

अटल काष्ठा tda18271_std_map hauppauge_hvr1200_tda18271_std_map = अणु
	.dvbt_6   = अणु .अगर_freq = 3300, .agc_mode = 3, .std = 4,
		      .अगर_lvl = 1, .rfagc_top = 0x37, पूर्ण,
	.dvbt_7   = अणु .अगर_freq = 3800, .agc_mode = 3, .std = 5,
		      .अगर_lvl = 1, .rfagc_top = 0x37, पूर्ण,
	.dvbt_8   = अणु .अगर_freq = 4300, .agc_mode = 3, .std = 6,
		      .अगर_lvl = 1, .rfagc_top = 0x37, पूर्ण,
पूर्ण;

अटल काष्ठा tda18271_config hauppauge_tda18271_config = अणु
	.std_map = &hauppauge_tda18271_std_map,
	.gate    = TDA18271_GATE_ANALOG,
	.output_opt = TDA18271_OUTPUT_LT_OFF,
पूर्ण;

अटल काष्ठा tda18271_config hauppauge_hvr1200_tuner_config = अणु
	.std_map = &hauppauge_hvr1200_tda18271_std_map,
	.gate    = TDA18271_GATE_ANALOG,
	.output_opt = TDA18271_OUTPUT_LT_OFF,
पूर्ण;

अटल काष्ठा tda18271_config hauppauge_hvr1210_tuner_config = अणु
	.gate    = TDA18271_GATE_DIGITAL,
	.output_opt = TDA18271_OUTPUT_LT_OFF,
पूर्ण;

अटल काष्ठा tda18271_config hauppauge_hvr4400_tuner_config = अणु
	.gate    = TDA18271_GATE_DIGITAL,
	.output_opt = TDA18271_OUTPUT_LT_OFF,
पूर्ण;

अटल काष्ठा tda18271_std_map hauppauge_hvr127x_std_map = अणु
	.atsc_6   = अणु .अगर_freq = 3250, .agc_mode = 3, .std = 4,
		      .अगर_lvl = 1, .rfagc_top = 0x58 पूर्ण,
	.qam_6    = अणु .अगर_freq = 4000, .agc_mode = 3, .std = 5,
		      .अगर_lvl = 1, .rfagc_top = 0x58 पूर्ण,
पूर्ण;

अटल काष्ठा tda18271_config hauppauge_hvr127x_config = अणु
	.std_map = &hauppauge_hvr127x_std_map,
	.output_opt = TDA18271_OUTPUT_LT_OFF,
पूर्ण;

अटल काष्ठा lgdt3305_config hauppauge_lgdt3305_config = अणु
	.i2c_addr           = 0x0e,
	.mpeg_mode          = LGDT3305_MPEG_SERIAL,
	.tpclk_edge         = LGDT3305_TPCLK_FALLING_EDGE,
	.tpvalid_polarity   = LGDT3305_TP_VALID_HIGH,
	.deny_i2c_rptr      = 1,
	.spectral_inversion = 1,
	.qam_अगर_khz         = 4000,
	.vsb_अगर_khz         = 3250,
पूर्ण;

अटल काष्ठा dibx000_agc_config xc3028_agc_config = अणु
	BAND_VHF | BAND_UHF,	/* band_caps */

	/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_freq_pwm_भाग=0,
	 * P_agc_inv_pwm1=0, P_agc_inv_pwm2=0,
	 * P_agc_inh_dc_rv_est=0, P_agc_समय_est=3, P_agc_मुक्तze=0,
	 * P_agc_nb_est=2, P_agc_ग_लिखो=0
	 */
	(0 << 15) | (0 << 14) | (0 << 11) | (0 << 10) | (0 << 9) | (0 << 8) |
		(3 << 5) | (0 << 4) | (2 << 1) | (0 << 0), /* setup */

	712,	/* inv_gain */
	21,	/* समय_stabiliz */

	0,	/* alpha_level */
	118,	/* thlock */

	0,	/* wbd_inv */
	2867,	/* wbd_ref */
	0,	/* wbd_sel */
	2,	/* wbd_alpha */

	0,	/* agc1_max */
	0,	/* agc1_min */
	39718,	/* agc2_max */
	9930,	/* agc2_min */
	0,	/* agc1_pt1 */
	0,	/* agc1_pt2 */
	0,	/* agc1_pt3 */
	0,	/* agc1_slope1 */
	0,	/* agc1_slope2 */
	0,	/* agc2_pt1 */
	128,	/* agc2_pt2 */
	29,	/* agc2_slope1 */
	29,	/* agc2_slope2 */

	17,	/* alpha_mant */
	27,	/* alpha_exp */
	23,	/* beta_mant */
	51,	/* beta_exp */

	1,	/* perक्रमm_agc_softsplit */
पूर्ण;

/* PLL Configuration क्रम COFDM BW_MHz = 8.000000
 * With बाह्यal घड़ी = 30.000000 */
अटल काष्ठा dibx000_bandwidth_config xc3028_bw_config = अणु
	60000,	/* पूर्णांकernal */
	30000,	/* sampling */
	1,	/* pll_cfg: preभाग */
	8,	/* pll_cfg: ratio */
	3,	/* pll_cfg: range */
	1,	/* pll_cfg: reset */
	0,	/* pll_cfg: bypass */
	0,	/* misc: refभाग */
	0,	/* misc: bypclk_भाग */
	1,	/* misc: IO_CLK_en_core */
	1,	/* misc: ADClkSrc */
	0,	/* misc: modulo */
	(3 << 14) | (1 << 12) | (524 << 0), /* sad_cfg: refsel, sel, freq_15k */
	(1 << 25) | 5816102, /* अगरreq = 5.200000 MHz */
	20452225, /* timf */
	30000000  /* xtal_hz */
पूर्ण;

अटल काष्ठा dib7000p_config hauppauge_hvr1400_dib7000_config = अणु
	.output_mpeg2_in_188_bytes = 1,
	.hostbus_भागersity = 1,
	.tuner_is_baseband = 0,
	.update_lna  = शून्य,

	.agc_config_count = 1,
	.agc = &xc3028_agc_config,
	.bw  = &xc3028_bw_config,

	.gpio_dir = DIB7000P_GPIO_DEFAULT_सूचीECTIONS,
	.gpio_val = DIB7000P_GPIO_DEFAULT_VALUES,
	.gpio_pwm_pos = DIB7000P_GPIO_DEFAULT_PWM_POS,

	.pwm_freq_भाग = 0,
	.agc_control  = शून्य,
	.spur_protect = 0,

	.output_mode = OUTMODE_MPEG2_SERIAL,
पूर्ण;

अटल काष्ठा zl10353_config dvico_fusionhdtv_xc3028 = अणु
	.demod_address = 0x0f,
	.अगर2           = 45600,
	.no_tuner      = 1,
	.disable_i2c_gate_ctrl = 1,
पूर्ण;

अटल काष्ठा stv0900_reg stv0900_ts_regs[] = अणु
	अणु R0900_TSGENERAL, 0x00 पूर्ण,
	अणु R0900_P1_TSSPEED, 0x40 पूर्ण,
	अणु R0900_P2_TSSPEED, 0x40 पूर्ण,
	अणु R0900_P1_TSCFGM, 0xc0 पूर्ण,
	अणु R0900_P2_TSCFGM, 0xc0 पूर्ण,
	अणु R0900_P1_TSCFGH, 0xe0 पूर्ण,
	अणु R0900_P2_TSCFGH, 0xe0 पूर्ण,
	अणु R0900_P1_TSCFGL, 0x20 पूर्ण,
	अणु R0900_P2_TSCFGL, 0x20 पूर्ण,
	अणु 0xffff, 0xff पूर्ण, /* terminate */
पूर्ण;

अटल काष्ठा stv0900_config netup_stv0900_config = अणु
	.demod_address = 0x68,
	.demod_mode = 1, /* dual */
	.xtal = 8000000,
	.clkmode = 3,/* 0-CLKI, 2-XTALI, अन्यथा AUTO */
	.diseqc_mode = 2,/* 2/3 PWM */
	.ts_config_regs = stv0900_ts_regs,
	.tun1_maddress = 0,/* 0x60 */
	.tun2_maddress = 3,/* 0x63 */
	.tun1_adc = 1,/* 1 Vpp */
	.tun2_adc = 1,/* 1 Vpp */
पूर्ण;

अटल काष्ठा stv6110_config netup_stv6110_tunerconfig_a = अणु
	.i2c_address = 0x60,
	.mclk = 16000000,
	.clk_भाग = 1,
	.gain = 8, /* +16 dB  - maximum gain */
पूर्ण;

अटल काष्ठा stv6110_config netup_stv6110_tunerconfig_b = अणु
	.i2c_address = 0x63,
	.mclk = 16000000,
	.clk_भाग = 1,
	.gain = 8, /* +16 dB  - maximum gain */
पूर्ण;

अटल काष्ठा cx24116_config tbs_cx24116_config = अणु
	.demod_address = 0x55,
पूर्ण;

अटल काष्ठा cx24117_config tbs_cx24117_config = अणु
	.demod_address = 0x55,
पूर्ण;

अटल काष्ठा ds3000_config tevii_ds3000_config = अणु
	.demod_address = 0x68,
पूर्ण;

अटल काष्ठा ts2020_config tevii_ts2020_config  = अणु
	.tuner_address = 0x60,
	.clk_out_भाग = 1,
	.frequency_भाग = 1146000,
पूर्ण;

अटल काष्ठा cx24116_config dvbworld_cx24116_config = अणु
	.demod_address = 0x05,
पूर्ण;

अटल काष्ठा lgs8gxx_config mygica_x8506_lgs8gl5_config = अणु
	.prod = LGS8GXX_PROD_LGS8GL5,
	.demod_address = 0x19,
	.serial_ts = 0,
	.ts_clk_pol = 1,
	.ts_clk_gated = 1,
	.अगर_clk_freq = 30400, /* 30.4 MHz */
	.अगर_freq = 5380, /* 5.38 MHz */
	.अगर_neg_center = 1,
	.ext_adc = 0,
	.adc_चिन्हित = 0,
	.अगर_neg_edge = 0,
पूर्ण;

अटल काष्ठा xc5000_config mygica_x8506_xc5000_config = अणु
	.i2c_address = 0x61,
	.अगर_khz = 5380,
पूर्ण;

अटल काष्ठा mb86a20s_config mygica_x8507_mb86a20s_config = अणु
	.demod_address = 0x10,
पूर्ण;

अटल काष्ठा xc5000_config mygica_x8507_xc5000_config = अणु
	.i2c_address = 0x61,
	.अगर_khz = 4000,
पूर्ण;

अटल काष्ठा stv090x_config prof_8000_stv090x_config = अणु
	.device                 = STV0903,
	.demod_mode             = STV090x_SINGLE,
	.clk_mode               = STV090x_CLK_EXT,
	.xtal                   = 27000000,
	.address                = 0x6A,
	.ts1_mode               = STV090x_TSMODE_PARALLEL_PUNCTURED,
	.repeater_level         = STV090x_RPTLEVEL_64,
	.adc1_range             = STV090x_ADC_2Vpp,
	.diseqc_envelope_mode   = false,

	.tuner_get_frequency    = stb6100_get_frequency,
	.tuner_set_frequency    = stb6100_set_frequency,
	.tuner_set_bandwidth    = stb6100_set_bandwidth,
	.tuner_get_bandwidth    = stb6100_get_bandwidth,
पूर्ण;

अटल काष्ठा stb6100_config prof_8000_stb6100_config = अणु
	.tuner_address = 0x60,
	.refघड़ी = 27000000,
पूर्ण;

अटल काष्ठा lgdt3306a_config hauppauge_quadHD_ATSC_a_config = अणु
	.i2c_addr               = 0x59,
	.qam_अगर_khz             = 4000,
	.vsb_अगर_khz             = 3250,
	.deny_i2c_rptr          = 1, /* Disabled */
	.spectral_inversion     = 0, /* Disabled */
	.mpeg_mode              = LGDT3306A_MPEG_SERIAL,
	.tpclk_edge             = LGDT3306A_TPCLK_RISING_EDGE,
	.tpvalid_polarity       = LGDT3306A_TP_VALID_HIGH,
	.xtalMHz                = 25, /* 24 or 25 */
पूर्ण;

अटल काष्ठा lgdt3306a_config hauppauge_quadHD_ATSC_b_config = अणु
	.i2c_addr               = 0x0e,
	.qam_अगर_khz             = 4000,
	.vsb_अगर_khz             = 3250,
	.deny_i2c_rptr          = 1, /* Disabled */
	.spectral_inversion     = 0, /* Disabled */
	.mpeg_mode              = LGDT3306A_MPEG_SERIAL,
	.tpclk_edge             = LGDT3306A_TPCLK_RISING_EDGE,
	.tpvalid_polarity       = LGDT3306A_TP_VALID_HIGH,
	.xtalMHz                = 25, /* 24 or 25 */
पूर्ण;

अटल पूर्णांक p8000_set_voltage(काष्ठा dvb_frontend *fe,
			     क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा cx23885_tsport *port = fe->dvb->priv;
	काष्ठा cx23885_dev *dev = port->dev;

	अगर (voltage == SEC_VOLTAGE_18)
		cx_ग_लिखो(MC417_RWD, 0x00001e00);
	अन्यथा अगर (voltage == SEC_VOLTAGE_13)
		cx_ग_लिखो(MC417_RWD, 0x00001a00);
	अन्यथा
		cx_ग_लिखो(MC417_RWD, 0x00001800);
	वापस 0;
पूर्ण

अटल पूर्णांक dvbsky_t9580_set_voltage(काष्ठा dvb_frontend *fe,
					क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा cx23885_tsport *port = fe->dvb->priv;
	काष्ठा cx23885_dev *dev = port->dev;

	cx23885_gpio_enable(dev, GPIO_0 | GPIO_1, 1);

	चयन (voltage) अणु
	हाल SEC_VOLTAGE_13:
		cx23885_gpio_set(dev, GPIO_1);
		cx23885_gpio_clear(dev, GPIO_0);
		अवरोध;
	हाल SEC_VOLTAGE_18:
		cx23885_gpio_set(dev, GPIO_1);
		cx23885_gpio_set(dev, GPIO_0);
		अवरोध;
	हाल SEC_VOLTAGE_OFF:
		cx23885_gpio_clear(dev, GPIO_1);
		cx23885_gpio_clear(dev, GPIO_0);
		अवरोध;
	पूर्ण

	/* call the frontend set_voltage function */
	port->fe_set_voltage(fe, voltage);

	वापस 0;
पूर्ण

अटल पूर्णांक dvbsky_s952_portc_set_voltage(काष्ठा dvb_frontend *fe,
					क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा cx23885_tsport *port = fe->dvb->priv;
	काष्ठा cx23885_dev *dev = port->dev;

	cx23885_gpio_enable(dev, GPIO_12 | GPIO_13, 1);

	चयन (voltage) अणु
	हाल SEC_VOLTAGE_13:
		cx23885_gpio_set(dev, GPIO_13);
		cx23885_gpio_clear(dev, GPIO_12);
		अवरोध;
	हाल SEC_VOLTAGE_18:
		cx23885_gpio_set(dev, GPIO_13);
		cx23885_gpio_set(dev, GPIO_12);
		अवरोध;
	हाल SEC_VOLTAGE_OFF:
		cx23885_gpio_clear(dev, GPIO_13);
		cx23885_gpio_clear(dev, GPIO_12);
		अवरोध;
	पूर्ण
	/* call the frontend set_voltage function */
	वापस port->fe_set_voltage(fe, voltage);
पूर्ण

अटल पूर्णांक cx23885_sp2_ci_ctrl(व्योम *priv, u8 पढ़ो, पूर्णांक addr,
				u8 data, पूर्णांक *mem)
अणु
	/* MC417 */
	#घोषणा SP2_DATA              0x000000ff
	#घोषणा SP2_WR                0x00008000
	#घोषणा SP2_RD                0x00004000
	#घोषणा SP2_ACK               0x00001000
	#घोषणा SP2_ADHI              0x00000800
	#घोषणा SP2_ADLO              0x00000400
	#घोषणा SP2_CS1               0x00000200
	#घोषणा SP2_CS0               0x00000100
	#घोषणा SP2_EN_ALL            0x00001000
	#घोषणा SP2_CTRL_OFF          (SP2_CS1 | SP2_CS0 | SP2_WR | SP2_RD)

	काष्ठा cx23885_tsport *port = priv;
	काष्ठा cx23885_dev *dev = port->dev;
	पूर्णांक ret;
	पूर्णांक पंचांगp = 0;
	अचिन्हित दीर्घ समयout;

	mutex_lock(&dev->gpio_lock);

	/* ग_लिखो addr */
	cx_ग_लिखो(MC417_OEN, SP2_EN_ALL);
	cx_ग_लिखो(MC417_RWD, SP2_CTRL_OFF |
				SP2_ADLO | (0xff & addr));
	cx_clear(MC417_RWD, SP2_ADLO);
	cx_ग_लिखो(MC417_RWD, SP2_CTRL_OFF |
				SP2_ADHI | (0xff & (addr >> 8)));
	cx_clear(MC417_RWD, SP2_ADHI);

	अगर (पढ़ो)
		/* data in */
		cx_ग_लिखो(MC417_OEN, SP2_EN_ALL | SP2_DATA);
	अन्यथा
		/* data out */
		cx_ग_लिखो(MC417_RWD, SP2_CTRL_OFF | data);

	/* chip select 0 */
	cx_clear(MC417_RWD, SP2_CS0);

	/* पढ़ो/ग_लिखो */
	cx_clear(MC417_RWD, (पढ़ो) ? SP2_RD : SP2_WR);

	/* रुको क्रम a maximum of 1 msec */
	समयout = jअगरfies + msecs_to_jअगरfies(1);
	जबतक (!समय_after(jअगरfies, समयout)) अणु
		पंचांगp = cx_पढ़ो(MC417_RWD);
		अगर ((पंचांगp & SP2_ACK) == 0)
			अवरोध;
		usleep_range(50, 100);
	पूर्ण

	cx_set(MC417_RWD, SP2_CTRL_OFF);
	*mem = पंचांगp & 0xff;

	mutex_unlock(&dev->gpio_lock);

	अगर (!पढ़ो) अणु
		अगर (*mem < 0) अणु
			ret = -EREMOTEIO;
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;
err:
	वापस ret;
पूर्ण

अटल पूर्णांक cx23885_dvb_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा cx23885_tsport *port = fe->dvb->priv;
	काष्ठा cx23885_dev *dev = port->dev;

	चयन (dev->board) अणु
	हाल CX23885_BOARD_HAUPPAUGE_HVR1275:
		चयन (p->modulation) अणु
		हाल VSB_8:
			cx23885_gpio_clear(dev, GPIO_5);
			अवरोध;
		हाल QAM_64:
		हाल QAM_256:
		शेष:
			cx23885_gpio_set(dev, GPIO_5);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल CX23885_BOARD_MYGICA_X8506:
	हाल CX23885_BOARD_MYGICA_X8507:
	हाल CX23885_BOARD_MAGICPRO_PROHDTVE2:
		/* Select Digital TV */
		cx23885_gpio_set(dev, GPIO_0);
		अवरोध;
	पूर्ण

	/* Call the real set_frontend */
	अगर (port->set_frontend)
		वापस port->set_frontend(fe);

	वापस 0;
पूर्ण

अटल व्योम cx23885_set_frontend_hook(काष्ठा cx23885_tsport *port,
				     काष्ठा dvb_frontend *fe)
अणु
	port->set_frontend = fe->ops.set_frontend;
	fe->ops.set_frontend = cx23885_dvb_set_frontend;
पूर्ण

अटल काष्ठा lgs8gxx_config magicpro_prohdtve2_lgs8g75_config = अणु
	.prod = LGS8GXX_PROD_LGS8G75,
	.demod_address = 0x19,
	.serial_ts = 0,
	.ts_clk_pol = 1,
	.ts_clk_gated = 1,
	.अगर_clk_freq = 30400, /* 30.4 MHz */
	.अगर_freq = 6500, /* 6.50 MHz */
	.अगर_neg_center = 1,
	.ext_adc = 0,
	.adc_चिन्हित = 1,
	.adc_vpp = 2, /* 1.6 Vpp */
	.अगर_neg_edge = 1,
पूर्ण;

अटल काष्ठा xc5000_config magicpro_prohdtve2_xc5000_config = अणु
	.i2c_address = 0x61,
	.अगर_khz = 6500,
पूर्ण;

अटल काष्ठा atbm8830_config mygica_x8558pro_atbm8830_cfg1 = अणु
	.prod = ATBM8830_PROD_8830,
	.demod_address = 0x44,
	.serial_ts = 0,
	.ts_sampling_edge = 1,
	.ts_clk_gated = 0,
	.osc_clk_freq = 30400, /* in kHz */
	.अगर_freq = 0, /* zero IF */
	.zअगर_swap_iq = 1,
	.agc_min = 0x2E,
	.agc_max = 0xFF,
	.agc_hold_loop = 0,
पूर्ण;

अटल काष्ठा max2165_config mygic_x8558pro_max2165_cfg1 = अणु
	.i2c_address = 0x60,
	.osc_clk = 20
पूर्ण;

अटल काष्ठा atbm8830_config mygica_x8558pro_atbm8830_cfg2 = अणु
	.prod = ATBM8830_PROD_8830,
	.demod_address = 0x44,
	.serial_ts = 1,
	.ts_sampling_edge = 1,
	.ts_clk_gated = 0,
	.osc_clk_freq = 30400, /* in kHz */
	.अगर_freq = 0, /* zero IF */
	.zअगर_swap_iq = 1,
	.agc_min = 0x2E,
	.agc_max = 0xFF,
	.agc_hold_loop = 0,
पूर्ण;

अटल काष्ठा max2165_config mygic_x8558pro_max2165_cfg2 = अणु
	.i2c_address = 0x60,
	.osc_clk = 20
पूर्ण;
अटल काष्ठा stv0367_config netup_stv0367_config[] = अणु
	अणु
		.demod_address = 0x1c,
		.xtal = 27000000,
		.अगर_khz = 4500,
		.अगर_iq_mode = 0,
		.ts_mode = 1,
		.clk_pol = 0,
	पूर्ण, अणु
		.demod_address = 0x1d,
		.xtal = 27000000,
		.अगर_khz = 4500,
		.अगर_iq_mode = 0,
		.ts_mode = 1,
		.clk_pol = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा xc5000_config netup_xc5000_config[] = अणु
	अणु
		.i2c_address = 0x61,
		.अगर_khz = 4500,
	पूर्ण, अणु
		.i2c_address = 0x64,
		.अगर_khz = 4500,
	पूर्ण,
पूर्ण;

अटल काष्ठा drxk_config terratec_drxk_config[] = अणु
	अणु
		.adr = 0x29,
		.no_i2c_bridge = 1,
	पूर्ण, अणु
		.adr = 0x2a,
		.no_i2c_bridge = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा mt2063_config terratec_mt2063_config[] = अणु
	अणु
		.tuner_address = 0x60,
	पूर्ण, अणु
		.tuner_address = 0x67,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा tda10071_platक्रमm_data hauppauge_tda10071_pdata = अणु
	.clk = 40444000, /* 40.444 MHz */
	.i2c_wr_max = 64,
	.ts_mode = TDA10071_TS_SERIAL,
	.pll_multiplier = 20,
	.tuner_i2c_addr = 0x54,
पूर्ण;

अटल स्थिर काष्ठा m88ds3103_config dvbsky_t9580_m88ds3103_config = अणु
	.i2c_addr = 0x68,
	.घड़ी = 27000000,
	.i2c_wr_max = 33,
	.घड़ी_out = 0,
	.ts_mode = M88DS3103_TS_PARALLEL,
	.ts_clk = 16000,
	.ts_clk_pol = 1,
	.lnb_en_pol = 1,
	.lnb_hv_pol = 0,
	.agc = 0x99,
पूर्ण;

अटल स्थिर काष्ठा m88ds3103_config dvbsky_s950c_m88ds3103_config = अणु
	.i2c_addr = 0x68,
	.घड़ी = 27000000,
	.i2c_wr_max = 33,
	.घड़ी_out = 0,
	.ts_mode = M88DS3103_TS_CI,
	.ts_clk = 10000,
	.ts_clk_pol = 1,
	.lnb_en_pol = 1,
	.lnb_hv_pol = 0,
	.agc = 0x99,
पूर्ण;

अटल स्थिर काष्ठा m88ds3103_config hauppauge_hvr5525_m88ds3103_config = अणु
	.i2c_addr = 0x69,
	.घड़ी = 27000000,
	.i2c_wr_max = 33,
	.ts_mode = M88DS3103_TS_PARALLEL,
	.ts_clk = 16000,
	.ts_clk_pol = 1,
	.agc = 0x99,
पूर्ण;

अटल काष्ठा lgdt3306a_config hauppauge_hvr1265k4_config = अणु
	.i2c_addr               = 0x59,
	.qam_अगर_khz             = 4000,
	.vsb_अगर_khz             = 3250,
	.deny_i2c_rptr          = 1, /* Disabled */
	.spectral_inversion     = 0, /* Disabled */
	.mpeg_mode              = LGDT3306A_MPEG_SERIAL,
	.tpclk_edge             = LGDT3306A_TPCLK_RISING_EDGE,
	.tpvalid_polarity       = LGDT3306A_TP_VALID_HIGH,
	.xtalMHz                = 25, /* 24 or 25 */
पूर्ण;

अटल पूर्णांक netup_altera_fpga_rw(व्योम *device, पूर्णांक flag, पूर्णांक data, पूर्णांक पढ़ो)
अणु
	काष्ठा cx23885_dev *dev = (काष्ठा cx23885_dev *)device;
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(1);
	uपूर्णांक32_t mem = 0;

	mem = cx_पढ़ो(MC417_RWD);
	अगर (पढ़ो)
		cx_set(MC417_OEN, ALT_DATA);
	अन्यथा अणु
		cx_clear(MC417_OEN, ALT_DATA);/* D0-D7 out */
		mem &= ~ALT_DATA;
		mem |= (data & ALT_DATA);
	पूर्ण

	अगर (flag)
		mem |= ALT_AD_RG;
	अन्यथा
		mem &= ~ALT_AD_RG;

	mem &= ~ALT_CS;
	अगर (पढ़ो)
		mem = (mem & ~ALT_RD) | ALT_WR;
	अन्यथा
		mem = (mem & ~ALT_WR) | ALT_RD;

	cx_ग_लिखो(MC417_RWD, mem);  /* start RW cycle */

	क्रम (;;) अणु
		mem = cx_पढ़ो(MC417_RWD);
		अगर ((mem & ALT_RDY) == 0)
			अवरोध;
		अगर (समय_after(jअगरfies, समयout))
			अवरोध;
		udelay(1);
	पूर्ण

	cx_set(MC417_RWD, ALT_RD | ALT_WR | ALT_CS);
	अगर (पढ़ो)
		वापस mem & ALT_DATA;

	वापस 0;
पूर्ण;

अटल पूर्णांक dib7070_tuner_reset(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	काष्ठा dib7000p_ops *dib7000p_ops = fe->sec_priv;

	वापस dib7000p_ops->set_gpio(fe, 8, 0, !onoff);
पूर्ण

अटल पूर्णांक dib7070_tuner_sleep(काष्ठा dvb_frontend *fe, पूर्णांक onoff)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा dib0070_config dib7070p_dib0070_config = अणु
	.i2c_address = DEFAULT_DIB0070_I2C_ADDRESS,
	.reset = dib7070_tuner_reset,
	.sleep = dib7070_tuner_sleep,
	.घड़ी_khz = 12000,
	.freq_offset_khz_vhf = 550,
	/* .flip_chip = 1, */
पूर्ण;

/* DIB7070 generic */
अटल काष्ठा dibx000_agc_config dib7070_agc_config = अणु
	.band_caps = BAND_UHF | BAND_VHF | BAND_LBAND | BAND_SBAND,

	/*
	 * P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_freq_pwm_भाग=5,
	 * P_agc_inv_pwm1=0, P_agc_inv_pwm2=0, P_agc_inh_dc_rv_est=0,
	 * P_agc_समय_est=3, P_agc_मुक्तze=0, P_agc_nb_est=5, P_agc_ग_लिखो=0
	 */
	.setup = (0 << 15) | (0 << 14) | (5 << 11) | (0 << 10) | (0 << 9) |
		 (0 << 8) | (3 << 5) | (0 << 4) | (5 << 1) | (0 << 0),
	.inv_gain = 600,
	.समय_stabiliz = 10,
	.alpha_level = 0,
	.thlock = 118,
	.wbd_inv = 0,
	.wbd_ref = 3530,
	.wbd_sel = 1,
	.wbd_alpha = 5,
	.agc1_max = 65535,
	.agc1_min = 0,
	.agc2_max = 65535,
	.agc2_min = 0,
	.agc1_pt1 = 0,
	.agc1_pt2 = 40,
	.agc1_pt3 = 183,
	.agc1_slope1 = 206,
	.agc1_slope2 = 255,
	.agc2_pt1 = 72,
	.agc2_pt2 = 152,
	.agc2_slope1 = 88,
	.agc2_slope2 = 90,
	.alpha_mant = 17,
	.alpha_exp = 27,
	.beta_mant = 23,
	.beta_exp = 51,
	.perक्रमm_agc_softsplit = 0,
पूर्ण;

अटल काष्ठा dibx000_bandwidth_config dib7070_bw_config_12_mhz = अणु
	.पूर्णांकernal = 60000,
	.sampling = 15000,
	.pll_preभाग = 1,
	.pll_ratio = 20,
	.pll_range = 3,
	.pll_reset = 1,
	.pll_bypass = 0,
	.enable_refभाग = 0,
	.bypclk_भाग = 0,
	.IO_CLK_en_core = 1,
	.ADClkSrc = 1,
	.modulo = 2,
	/* refsel, sel, freq_15k */
	.sad_cfg = (3 << 14) | (1 << 12) | (524 << 0),
	.अगरreq = (0 << 25) | 0,
	.timf = 20452225,
	.xtal_hz = 12000000,
पूर्ण;

अटल काष्ठा dib7000p_config dib7070p_dib7000p_config = अणु
	/* .output_mode = OUTMODE_MPEG2_FIFO, */
	.output_mode = OUTMODE_MPEG2_SERIAL,
	/* .output_mode = OUTMODE_MPEG2_PAR_GATED_CLK, */
	.output_mpeg2_in_188_bytes = 1,

	.agc_config_count = 1,
	.agc = &dib7070_agc_config,
	.bw  = &dib7070_bw_config_12_mhz,
	.tuner_is_baseband = 1,
	.spur_protect = 1,

	.gpio_dir = 0xfcef, /* DIB7000P_GPIO_DEFAULT_सूचीECTIONS, */
	.gpio_val = 0x0110, /* DIB7000P_GPIO_DEFAULT_VALUES, */
	.gpio_pwm_pos = DIB7000P_GPIO_DEFAULT_PWM_POS,

	.hostbus_भागersity = 1,
पूर्ण;

अटल पूर्णांक dvb_रेजिस्टर_ci_mac(काष्ठा cx23885_tsport *port)
अणु
	काष्ठा cx23885_dev *dev = port->dev;
	काष्ठा i2c_client *client_ci = शून्य;
	काष्ठा vb2_dvb_frontend *fe0;

	fe0 = vb2_dvb_get_frontend(&port->frontends, 1);
	अगर (!fe0)
		वापस -EINVAL;

	चयन (dev->board) अणु
	हाल CX23885_BOARD_NETUP_DUAL_DVBS2_CI: अणु
		अटल काष्ठा netup_card_info cinfo;

		netup_get_card_info(&dev->i2c_bus[0].i2c_adap, &cinfo);
		स_नकल(port->frontends.adapter.proposed_mac,
				cinfo.port[port->nr - 1].mac, 6);
		pr_info("NetUP Dual DVB-S2 CI card port%d MAC=%pM\n",
			port->nr, port->frontends.adapter.proposed_mac);

		netup_ci_init(port);
		वापस 0;
		पूर्ण
	हाल CX23885_BOARD_NETUP_DUAL_DVB_T_C_CI_RF: अणु
		काष्ठा altera_ci_config netup_ci_cfg = अणु
			.dev = dev,/* magic number to identअगरy*/
			.adapter = &port->frontends.adapter,/* क्रम CI */
			.demux = &fe0->dvb.demux,/* क्रम hw pid filter */
			.fpga_rw = netup_altera_fpga_rw,
		पूर्ण;

		altera_ci_init(&netup_ci_cfg, port->nr);
		वापस 0;
		पूर्ण
	हाल CX23885_BOARD_TEVII_S470: अणु
		u8 eeprom[256]; /* 24C02 i2c eeprom */

		अगर (port->nr != 1)
			वापस 0;

		/* Read entire EEPROM */
		dev->i2c_bus[0].i2c_client.addr = 0xa0 >> 1;
		tveeprom_पढ़ो(&dev->i2c_bus[0].i2c_client, eeprom, माप(eeprom));
		pr_info("TeVii S470 MAC= %pM\n", eeprom + 0xa0);
		स_नकल(port->frontends.adapter.proposed_mac, eeprom + 0xa0, 6);
		वापस 0;
		पूर्ण
	हाल CX23885_BOARD_DVBSKY_T9580:
	हाल CX23885_BOARD_DVBSKY_S950:
	हाल CX23885_BOARD_DVBSKY_S952:
	हाल CX23885_BOARD_DVBSKY_T982: अणु
		u8 eeprom[256]; /* 24C02 i2c eeprom */

		अगर (port->nr > 2)
			वापस 0;

		/* Read entire EEPROM */
		dev->i2c_bus[0].i2c_client.addr = 0xa0 >> 1;
		tveeprom_पढ़ो(&dev->i2c_bus[0].i2c_client, eeprom,
				माप(eeprom));
		pr_info("%s port %d MAC address: %pM\n",
			cx23885_boards[dev->board].name, port->nr,
			eeprom + 0xc0 + (port->nr-1) * 8);
		स_नकल(port->frontends.adapter.proposed_mac, eeprom + 0xc0 +
			(port->nr-1) * 8, 6);
		वापस 0;
		पूर्ण
	हाल CX23885_BOARD_DVBSKY_S950C:
	हाल CX23885_BOARD_DVBSKY_T980C:
	हाल CX23885_BOARD_TT_CT2_4500_CI: अणु
		u8 eeprom[256]; /* 24C02 i2c eeprom */
		काष्ठा sp2_config sp2_config;
		काष्ठा i2c_board_info info;
		काष्ठा cx23885_i2c *i2c_bus = &dev->i2c_bus[0];

		/* attach CI */
		स_रखो(&sp2_config, 0, माप(sp2_config));
		sp2_config.dvb_adap = &port->frontends.adapter;
		sp2_config.priv = port;
		sp2_config.ci_control = cx23885_sp2_ci_ctrl;
		स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
		strscpy(info.type, "sp2", I2C_NAME_SIZE);
		info.addr = 0x40;
		info.platक्रमm_data = &sp2_config;
		request_module(info.type);
		client_ci = i2c_new_client_device(&i2c_bus->i2c_adap, &info);
		अगर (!i2c_client_has_driver(client_ci))
			वापस -ENODEV;
		अगर (!try_module_get(client_ci->dev.driver->owner)) अणु
			i2c_unरेजिस्टर_device(client_ci);
			वापस -ENODEV;
		पूर्ण
		port->i2c_client_ci = client_ci;

		अगर (port->nr != 1)
			वापस 0;

		/* Read entire EEPROM */
		dev->i2c_bus[0].i2c_client.addr = 0xa0 >> 1;
		tveeprom_पढ़ो(&dev->i2c_bus[0].i2c_client, eeprom,
				माप(eeprom));
		pr_info("%s MAC address: %pM\n",
			cx23885_boards[dev->board].name, eeprom + 0xc0);
		स_नकल(port->frontends.adapter.proposed_mac, eeprom + 0xc0, 6);
		वापस 0;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dvb_रेजिस्टर(काष्ठा cx23885_tsport *port)
अणु
	काष्ठा dib7000p_ops dib7000p_ops;
	काष्ठा cx23885_dev *dev = port->dev;
	काष्ठा cx23885_i2c *i2c_bus = शून्य, *i2c_bus2 = शून्य;
	काष्ठा vb2_dvb_frontend *fe0, *fe1 = शून्य;
	काष्ठा si2168_config si2168_config;
	काष्ठा si2165_platक्रमm_data si2165_pdata;
	काष्ठा si2157_config si2157_config;
	काष्ठा ts2020_config ts2020_config;
	काष्ठा m88ds3103_platक्रमm_data m88ds3103_pdata;
	काष्ठा m88rs6000t_config m88rs6000t_config = अणुपूर्ण;
	काष्ठा a8293_platक्रमm_data a8293_pdata = अणुपूर्ण;
	काष्ठा i2c_board_info info;
	काष्ठा i2c_adapter *adapter;
	काष्ठा i2c_client *client_demod = शून्य, *client_tuner = शून्य;
	काष्ठा i2c_client *client_sec = शून्य;
	पूर्णांक (*p_set_voltage)(काष्ठा dvb_frontend *fe,
			     क्रमागत fe_sec_voltage voltage) = शून्य;
	पूर्णांक mfe_shared = 0; /* bus not shared by शेष */
	पूर्णांक ret;

	/* Get the first frontend */
	fe0 = vb2_dvb_get_frontend(&port->frontends, 1);
	अगर (!fe0)
		वापस -EINVAL;

	/* init काष्ठा vb2_dvb */
	fe0->dvb.name = dev->name;

	/* multi-frontend gate control is undefined or शेषs to fe0 */
	port->frontends.gate = 0;

	/* Sets the gate control callback to be used by i2c command calls */
	port->gate_ctrl = cx23885_dvb_gate_ctrl;

	/* init frontend */
	चयन (dev->board) अणु
	हाल CX23885_BOARD_HAUPPAUGE_HVR1250:
		i2c_bus = &dev->i2c_bus[0];
		fe0->dvb.frontend = dvb_attach(s5h1409_attach,
						&hauppauge_generic_config,
						&i2c_bus->i2c_adap);
		अगर (fe0->dvb.frontend == शून्य)
			अवरोध;
		dvb_attach(mt2131_attach, fe0->dvb.frontend,
			   &i2c_bus->i2c_adap,
			   &hauppauge_generic_tunerconfig, 0);
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_HVR1270:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1275:
		i2c_bus = &dev->i2c_bus[0];
		fe0->dvb.frontend = dvb_attach(lgdt3305_attach,
					       &hauppauge_lgdt3305_config,
					       &i2c_bus->i2c_adap);
		अगर (fe0->dvb.frontend == शून्य)
			अवरोध;
		dvb_attach(tda18271_attach, fe0->dvb.frontend,
			   0x60, &dev->i2c_bus[1].i2c_adap,
			   &hauppauge_hvr127x_config);
		अगर (dev->board == CX23885_BOARD_HAUPPAUGE_HVR1275)
			cx23885_set_frontend_hook(port, fe0->dvb.frontend);
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_HVR1255:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1255_22111:
		i2c_bus = &dev->i2c_bus[0];
		fe0->dvb.frontend = dvb_attach(s5h1411_attach,
					       &hcw_s5h1411_config,
					       &i2c_bus->i2c_adap);
		अगर (fe0->dvb.frontend == शून्य)
			अवरोध;

		dvb_attach(tda18271_attach, fe0->dvb.frontend,
			   0x60, &dev->i2c_bus[1].i2c_adap,
			   &hauppauge_tda18271_config);

		tda18271_attach(&dev->ts1.analog_fe,
			0x60, &dev->i2c_bus[1].i2c_adap,
			&hauppauge_tda18271_config);

		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_HVR1800:
		i2c_bus = &dev->i2c_bus[0];
		चयन (alt_tuner) अणु
		हाल 1:
			fe0->dvb.frontend =
				dvb_attach(s5h1409_attach,
					   &hauppauge_ezqam_config,
					   &i2c_bus->i2c_adap);
			अगर (fe0->dvb.frontend == शून्य)
				अवरोध;

			dvb_attach(tda829x_attach, fe0->dvb.frontend,
				   &dev->i2c_bus[1].i2c_adap, 0x42,
				   &tda829x_no_probe);
			dvb_attach(tda18271_attach, fe0->dvb.frontend,
				   0x60, &dev->i2c_bus[1].i2c_adap,
				   &hauppauge_tda18271_config);
			अवरोध;
		हाल 0:
		शेष:
			fe0->dvb.frontend =
				dvb_attach(s5h1409_attach,
					   &hauppauge_generic_config,
					   &i2c_bus->i2c_adap);
			अगर (fe0->dvb.frontend == शून्य)
				अवरोध;
			dvb_attach(mt2131_attach, fe0->dvb.frontend,
				   &i2c_bus->i2c_adap,
				   &hauppauge_generic_tunerconfig, 0);
		पूर्ण
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_HVR1800lp:
		i2c_bus = &dev->i2c_bus[0];
		fe0->dvb.frontend = dvb_attach(s5h1409_attach,
						&hauppauge_hvr1800lp_config,
						&i2c_bus->i2c_adap);
		अगर (fe0->dvb.frontend == शून्य)
			अवरोध;
		dvb_attach(mt2131_attach, fe0->dvb.frontend,
			   &i2c_bus->i2c_adap,
			   &hauppauge_generic_tunerconfig, 0);
		अवरोध;
	हाल CX23885_BOARD_DVICO_FUSIONHDTV_5_EXP:
		i2c_bus = &dev->i2c_bus[0];
		fe0->dvb.frontend = dvb_attach(lgdt330x_attach,
					       &fusionhdtv_5_express,
					       0x0e,
					       &i2c_bus->i2c_adap);
		अगर (fe0->dvb.frontend == शून्य)
			अवरोध;
		dvb_attach(simple_tuner_attach, fe0->dvb.frontend,
			   &i2c_bus->i2c_adap, 0x61,
			   TUNER_LG_TDVS_H06XF);
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_HVR1500Q:
		i2c_bus = &dev->i2c_bus[1];
		fe0->dvb.frontend = dvb_attach(s5h1409_attach,
						&hauppauge_hvr1500q_config,
						&dev->i2c_bus[0].i2c_adap);
		अगर (fe0->dvb.frontend == शून्य)
			अवरोध;
		dvb_attach(xc5000_attach, fe0->dvb.frontend,
			   &i2c_bus->i2c_adap,
			   &hauppauge_hvr1500q_tunerconfig);
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_HVR1500:
		i2c_bus = &dev->i2c_bus[1];
		fe0->dvb.frontend = dvb_attach(s5h1409_attach,
						&hauppauge_hvr1500_config,
						&dev->i2c_bus[0].i2c_adap);
		अगर (fe0->dvb.frontend != शून्य) अणु
			काष्ठा dvb_frontend *fe;
			काष्ठा xc2028_config cfg = अणु
				.i2c_adap  = &i2c_bus->i2c_adap,
				.i2c_addr  = 0x61,
			पूर्ण;
			अटल काष्ठा xc2028_ctrl ctl = अणु
				.fname       = XC2028_DEFAULT_FIRMWARE,
				.max_len     = 64,
				.demod       = XC3028_FE_OREN538,
			पूर्ण;

			fe = dvb_attach(xc2028_attach,
					fe0->dvb.frontend, &cfg);
			अगर (fe != शून्य && fe->ops.tuner_ops.set_config != शून्य)
				fe->ops.tuner_ops.set_config(fe, &ctl);
		पूर्ण
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_HVR1200:
	हाल CX23885_BOARD_HAUPPAUGE_HVR1700:
		i2c_bus = &dev->i2c_bus[0];
		fe0->dvb.frontend = dvb_attach(tda10048_attach,
			&hauppauge_hvr1200_config,
			&i2c_bus->i2c_adap);
		अगर (fe0->dvb.frontend == शून्य)
			अवरोध;
		dvb_attach(tda829x_attach, fe0->dvb.frontend,
			   &dev->i2c_bus[1].i2c_adap, 0x42,
			   &tda829x_no_probe);
		dvb_attach(tda18271_attach, fe0->dvb.frontend,
			   0x60, &dev->i2c_bus[1].i2c_adap,
			   &hauppauge_hvr1200_tuner_config);
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_HVR1210:
		i2c_bus = &dev->i2c_bus[0];
		fe0->dvb.frontend = dvb_attach(tda10048_attach,
			&hauppauge_hvr1210_config,
			&i2c_bus->i2c_adap);
		अगर (fe0->dvb.frontend != शून्य) अणु
			dvb_attach(tda18271_attach, fe0->dvb.frontend,
				0x60, &dev->i2c_bus[1].i2c_adap,
				&hauppauge_hvr1210_tuner_config);
		पूर्ण
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_HVR1400:
		i2c_bus = &dev->i2c_bus[0];

		अगर (!dvb_attach(dib7000p_attach, &dib7000p_ops))
			वापस -ENODEV;

		fe0->dvb.frontend = dib7000p_ops.init(&i2c_bus->i2c_adap,
			0x12, &hauppauge_hvr1400_dib7000_config);
		अगर (fe0->dvb.frontend != शून्य) अणु
			काष्ठा dvb_frontend *fe;
			काष्ठा xc2028_config cfg = अणु
				.i2c_adap  = &dev->i2c_bus[1].i2c_adap,
				.i2c_addr  = 0x64,
			पूर्ण;
			अटल काष्ठा xc2028_ctrl ctl = अणु
				.fname   = XC3028L_DEFAULT_FIRMWARE,
				.max_len = 64,
				.demod   = XC3028_FE_DIBCOM52,
				/* This is true क्रम all demods with
					v36 firmware? */
				.type    = XC2028_D2633,
			पूर्ण;

			fe = dvb_attach(xc2028_attach,
					fe0->dvb.frontend, &cfg);
			अगर (fe != शून्य && fe->ops.tuner_ops.set_config != शून्य)
				fe->ops.tuner_ops.set_config(fe, &ctl);
		पूर्ण
		अवरोध;
	हाल CX23885_BOARD_DVICO_FUSIONHDTV_7_DUAL_EXP:
		i2c_bus = &dev->i2c_bus[port->nr - 1];

		fe0->dvb.frontend = dvb_attach(s5h1409_attach,
						&dvico_s5h1409_config,
						&i2c_bus->i2c_adap);
		अगर (fe0->dvb.frontend == शून्य)
			fe0->dvb.frontend = dvb_attach(s5h1411_attach,
							&dvico_s5h1411_config,
							&i2c_bus->i2c_adap);
		अगर (fe0->dvb.frontend != शून्य)
			dvb_attach(xc5000_attach, fe0->dvb.frontend,
				   &i2c_bus->i2c_adap,
				   &dvico_xc5000_tunerconfig);
		अवरोध;
	हाल CX23885_BOARD_DVICO_FUSIONHDTV_DVB_T_DUAL_EXP: अणु
		i2c_bus = &dev->i2c_bus[port->nr - 1];

		fe0->dvb.frontend = dvb_attach(zl10353_attach,
					       &dvico_fusionhdtv_xc3028,
					       &i2c_bus->i2c_adap);
		अगर (fe0->dvb.frontend != शून्य) अणु
			काष्ठा dvb_frontend      *fe;
			काष्ठा xc2028_config	  cfg = अणु
				.i2c_adap  = &i2c_bus->i2c_adap,
				.i2c_addr  = 0x61,
			पूर्ण;
			अटल काष्ठा xc2028_ctrl ctl = अणु
				.fname       = XC2028_DEFAULT_FIRMWARE,
				.max_len     = 64,
				.demod       = XC3028_FE_ZARLINK456,
			पूर्ण;

			fe = dvb_attach(xc2028_attach, fe0->dvb.frontend,
					&cfg);
			अगर (fe != शून्य && fe->ops.tuner_ops.set_config != शून्य)
				fe->ops.tuner_ops.set_config(fe, &ctl);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल CX23885_BOARD_DVICO_FUSIONHDTV_DVB_T_DUAL_EXP2: अणु
		i2c_bus = &dev->i2c_bus[port->nr - 1];
		/* cxusb_ctrl_msg(adap->dev, CMD_DIGITAL, शून्य, 0, शून्य, 0); */
		/* cxusb_bluebird_gpio_pulse(adap->dev, 0x02, 1); */

		अगर (!dvb_attach(dib7000p_attach, &dib7000p_ops))
			वापस -ENODEV;

		अगर (dib7000p_ops.i2c_क्रमागतeration(&i2c_bus->i2c_adap, 1, 0x12, &dib7070p_dib7000p_config) < 0) अणु
			pr_warn("Unable to enumerate dib7000p\n");
			वापस -ENODEV;
		पूर्ण
		fe0->dvb.frontend = dib7000p_ops.init(&i2c_bus->i2c_adap, 0x80, &dib7070p_dib7000p_config);
		अगर (fe0->dvb.frontend != शून्य) अणु
			काष्ठा i2c_adapter *tun_i2c;

			fe0->dvb.frontend->sec_priv = kmemdup(&dib7000p_ops, माप(dib7000p_ops), GFP_KERNEL);
			अगर (!fe0->dvb.frontend->sec_priv)
				वापस -ENOMEM;
			tun_i2c = dib7000p_ops.get_i2c_master(fe0->dvb.frontend, DIBX000_I2C_INTERFACE_TUNER, 1);
			अगर (!dvb_attach(dib0070_attach, fe0->dvb.frontend, tun_i2c, &dib7070p_dib0070_config))
				वापस -ENODEV;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल CX23885_BOARD_LEADTEK_WINFAST_PXDVR3200_H:
	हाल CX23885_BOARD_COMPRO_VIDEOMATE_E650F:
	हाल CX23885_BOARD_COMPRO_VIDEOMATE_E800:
		i2c_bus = &dev->i2c_bus[0];

		fe0->dvb.frontend = dvb_attach(zl10353_attach,
			&dvico_fusionhdtv_xc3028,
			&i2c_bus->i2c_adap);
		अगर (fe0->dvb.frontend != शून्य) अणु
			काष्ठा dvb_frontend      *fe;
			काष्ठा xc2028_config	  cfg = अणु
				.i2c_adap  = &dev->i2c_bus[1].i2c_adap,
				.i2c_addr  = 0x61,
			पूर्ण;
			अटल काष्ठा xc2028_ctrl ctl = अणु
				.fname       = XC2028_DEFAULT_FIRMWARE,
				.max_len     = 64,
				.demod       = XC3028_FE_ZARLINK456,
			पूर्ण;

			fe = dvb_attach(xc2028_attach, fe0->dvb.frontend,
				&cfg);
			अगर (fe != शून्य && fe->ops.tuner_ops.set_config != शून्य)
				fe->ops.tuner_ops.set_config(fe, &ctl);
		पूर्ण
		अवरोध;
	हाल CX23885_BOARD_LEADTEK_WINFAST_PXDVR3200_H_XC4000:
		i2c_bus = &dev->i2c_bus[0];

		fe0->dvb.frontend = dvb_attach(zl10353_attach,
					       &dvico_fusionhdtv_xc3028,
					       &i2c_bus->i2c_adap);
		अगर (fe0->dvb.frontend != शून्य) अणु
			काष्ठा dvb_frontend	*fe;
			काष्ठा xc4000_config	cfg = अणु
				.i2c_address	  = 0x61,
				.शेष_pm	  = 0,
				.dvb_amplitude	  = 134,
				.set_smoothedcvbs = 1,
				.अगर_khz		  = 4560
			पूर्ण;

			fe = dvb_attach(xc4000_attach, fe0->dvb.frontend,
					&dev->i2c_bus[1].i2c_adap, &cfg);
			अगर (!fe) अणु
				pr_err("%s/2: xc4000 attach failed\n",
				       dev->name);
				जाओ frontend_detach;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल CX23885_BOARD_TBS_6920:
		i2c_bus = &dev->i2c_bus[1];

		fe0->dvb.frontend = dvb_attach(cx24116_attach,
					&tbs_cx24116_config,
					&i2c_bus->i2c_adap);
		अगर (fe0->dvb.frontend != शून्य)
			fe0->dvb.frontend->ops.set_voltage = f300_set_voltage;

		अवरोध;
	हाल CX23885_BOARD_TBS_6980:
	हाल CX23885_BOARD_TBS_6981:
		i2c_bus = &dev->i2c_bus[1];

		चयन (port->nr) अणु
		/* PORT B */
		हाल 1:
			fe0->dvb.frontend = dvb_attach(cx24117_attach,
					&tbs_cx24117_config,
					&i2c_bus->i2c_adap);
			अवरोध;
		/* PORT C */
		हाल 2:
			fe0->dvb.frontend = dvb_attach(cx24117_attach,
					&tbs_cx24117_config,
					&i2c_bus->i2c_adap);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल CX23885_BOARD_TEVII_S470:
		i2c_bus = &dev->i2c_bus[1];

		fe0->dvb.frontend = dvb_attach(ds3000_attach,
					&tevii_ds3000_config,
					&i2c_bus->i2c_adap);
		अगर (fe0->dvb.frontend != शून्य) अणु
			dvb_attach(ts2020_attach, fe0->dvb.frontend,
				&tevii_ts2020_config, &i2c_bus->i2c_adap);
			fe0->dvb.frontend->ops.set_voltage = f300_set_voltage;
		पूर्ण

		अवरोध;
	हाल CX23885_BOARD_DVBWORLD_2005:
		i2c_bus = &dev->i2c_bus[1];

		fe0->dvb.frontend = dvb_attach(cx24116_attach,
			&dvbworld_cx24116_config,
			&i2c_bus->i2c_adap);
		अवरोध;
	हाल CX23885_BOARD_NETUP_DUAL_DVBS2_CI:
		i2c_bus = &dev->i2c_bus[0];
		चयन (port->nr) अणु
		/* port B */
		हाल 1:
			fe0->dvb.frontend = dvb_attach(stv0900_attach,
							&netup_stv0900_config,
							&i2c_bus->i2c_adap, 0);
			अगर (fe0->dvb.frontend != शून्य) अणु
				अगर (dvb_attach(stv6110_attach,
						fe0->dvb.frontend,
						&netup_stv6110_tunerconfig_a,
						&i2c_bus->i2c_adap)) अणु
					अगर (!dvb_attach(lnbh24_attach,
							fe0->dvb.frontend,
							&i2c_bus->i2c_adap,
							LNBH24_PCL | LNBH24_TTX,
							LNBH24_TEN, 0x09))
						pr_err("No LNBH24 found!\n");

				पूर्ण
			पूर्ण
			अवरोध;
		/* port C */
		हाल 2:
			fe0->dvb.frontend = dvb_attach(stv0900_attach,
							&netup_stv0900_config,
							&i2c_bus->i2c_adap, 1);
			अगर (fe0->dvb.frontend != शून्य) अणु
				अगर (dvb_attach(stv6110_attach,
						fe0->dvb.frontend,
						&netup_stv6110_tunerconfig_b,
						&i2c_bus->i2c_adap)) अणु
					अगर (!dvb_attach(lnbh24_attach,
							fe0->dvb.frontend,
							&i2c_bus->i2c_adap,
							LNBH24_PCL | LNBH24_TTX,
							LNBH24_TEN, 0x0a))
						pr_err("No LNBH24 found!\n");

				पूर्ण
			पूर्ण
			अवरोध;
		पूर्ण
		अवरोध;
	हाल CX23885_BOARD_MYGICA_X8506:
		i2c_bus = &dev->i2c_bus[0];
		i2c_bus2 = &dev->i2c_bus[1];
		fe0->dvb.frontend = dvb_attach(lgs8gxx_attach,
			&mygica_x8506_lgs8gl5_config,
			&i2c_bus->i2c_adap);
		अगर (fe0->dvb.frontend == शून्य)
			अवरोध;
		dvb_attach(xc5000_attach, fe0->dvb.frontend,
			   &i2c_bus2->i2c_adap, &mygica_x8506_xc5000_config);
		cx23885_set_frontend_hook(port, fe0->dvb.frontend);
		अवरोध;
	हाल CX23885_BOARD_MYGICA_X8507:
		i2c_bus = &dev->i2c_bus[0];
		i2c_bus2 = &dev->i2c_bus[1];
		fe0->dvb.frontend = dvb_attach(mb86a20s_attach,
			&mygica_x8507_mb86a20s_config,
			&i2c_bus->i2c_adap);
		अगर (fe0->dvb.frontend == शून्य)
			अवरोध;

		dvb_attach(xc5000_attach, fe0->dvb.frontend,
			   &i2c_bus2->i2c_adap,
			   &mygica_x8507_xc5000_config);
		cx23885_set_frontend_hook(port, fe0->dvb.frontend);
		अवरोध;
	हाल CX23885_BOARD_MAGICPRO_PROHDTVE2:
		i2c_bus = &dev->i2c_bus[0];
		i2c_bus2 = &dev->i2c_bus[1];
		fe0->dvb.frontend = dvb_attach(lgs8gxx_attach,
			&magicpro_prohdtve2_lgs8g75_config,
			&i2c_bus->i2c_adap);
		अगर (fe0->dvb.frontend == शून्य)
			अवरोध;
		dvb_attach(xc5000_attach, fe0->dvb.frontend,
			   &i2c_bus2->i2c_adap,
			   &magicpro_prohdtve2_xc5000_config);
		cx23885_set_frontend_hook(port, fe0->dvb.frontend);
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_HVR1850:
		i2c_bus = &dev->i2c_bus[0];
		fe0->dvb.frontend = dvb_attach(s5h1411_attach,
			&hcw_s5h1411_config,
			&i2c_bus->i2c_adap);
		अगर (fe0->dvb.frontend == शून्य)
			अवरोध;
		dvb_attach(tda18271_attach, fe0->dvb.frontend,
			   0x60, &dev->i2c_bus[0].i2c_adap,
			   &hauppauge_tda18271_config);

		tda18271_attach(&dev->ts1.analog_fe,
			0x60, &dev->i2c_bus[1].i2c_adap,
			&hauppauge_tda18271_config);

		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_HVR1290:
		i2c_bus = &dev->i2c_bus[0];
		fe0->dvb.frontend = dvb_attach(s5h1411_attach,
			&hcw_s5h1411_config,
			&i2c_bus->i2c_adap);
		अगर (fe0->dvb.frontend == शून्य)
			अवरोध;
		dvb_attach(tda18271_attach, fe0->dvb.frontend,
			   0x60, &dev->i2c_bus[0].i2c_adap,
			   &hauppauge_tda18271_config);
		अवरोध;
	हाल CX23885_BOARD_MYGICA_X8558PRO:
		चयन (port->nr) अणु
		/* port B */
		हाल 1:
			i2c_bus = &dev->i2c_bus[0];
			fe0->dvb.frontend = dvb_attach(atbm8830_attach,
				&mygica_x8558pro_atbm8830_cfg1,
				&i2c_bus->i2c_adap);
			अगर (fe0->dvb.frontend == शून्य)
				अवरोध;
			dvb_attach(max2165_attach, fe0->dvb.frontend,
				   &i2c_bus->i2c_adap,
				   &mygic_x8558pro_max2165_cfg1);
			अवरोध;
		/* port C */
		हाल 2:
			i2c_bus = &dev->i2c_bus[1];
			fe0->dvb.frontend = dvb_attach(atbm8830_attach,
				&mygica_x8558pro_atbm8830_cfg2,
				&i2c_bus->i2c_adap);
			अगर (fe0->dvb.frontend == शून्य)
				अवरोध;
			dvb_attach(max2165_attach, fe0->dvb.frontend,
				   &i2c_bus->i2c_adap,
				   &mygic_x8558pro_max2165_cfg2);
		पूर्ण
		अवरोध;
	हाल CX23885_BOARD_NETUP_DUAL_DVB_T_C_CI_RF:
		अगर (port->nr > 2)
			वापस 0;

		i2c_bus = &dev->i2c_bus[0];
		mfe_shared = 1;/* MFE */
		port->frontends.gate = 0;/* not clear क्रम me yet */
		/* ports B, C */
		/* MFE frontend 1 DVB-T */
		fe0->dvb.frontend = dvb_attach(stv0367ter_attach,
					&netup_stv0367_config[port->nr - 1],
					&i2c_bus->i2c_adap);
		अगर (fe0->dvb.frontend == शून्य)
			अवरोध;
		अगर (शून्य == dvb_attach(xc5000_attach, fe0->dvb.frontend,
					&i2c_bus->i2c_adap,
					&netup_xc5000_config[port->nr - 1]))
			जाओ frontend_detach;
		/* load xc5000 firmware */
		fe0->dvb.frontend->ops.tuner_ops.init(fe0->dvb.frontend);

		/* MFE frontend 2 */
		fe1 = vb2_dvb_get_frontend(&port->frontends, 2);
		अगर (fe1 == शून्य)
			जाओ frontend_detach;
		/* DVB-C init */
		fe1->dvb.frontend = dvb_attach(stv0367cab_attach,
					&netup_stv0367_config[port->nr - 1],
					&i2c_bus->i2c_adap);
		अगर (fe1->dvb.frontend == शून्य)
			अवरोध;

		fe1->dvb.frontend->id = 1;
		अगर (शून्य == dvb_attach(xc5000_attach,
				       fe1->dvb.frontend,
				       &i2c_bus->i2c_adap,
				       &netup_xc5000_config[port->nr - 1]))
			जाओ frontend_detach;
		अवरोध;
	हाल CX23885_BOARD_TERRATEC_CINERGY_T_PCIE_DUAL:
		i2c_bus = &dev->i2c_bus[0];
		i2c_bus2 = &dev->i2c_bus[1];

		चयन (port->nr) अणु
		/* port b */
		हाल 1:
			fe0->dvb.frontend = dvb_attach(drxk_attach,
					&terratec_drxk_config[0],
					&i2c_bus->i2c_adap);
			अगर (fe0->dvb.frontend == शून्य)
				अवरोध;
			अगर (!dvb_attach(mt2063_attach,
					fe0->dvb.frontend,
					&terratec_mt2063_config[0],
					&i2c_bus2->i2c_adap))
				जाओ frontend_detach;
			अवरोध;
		/* port c */
		हाल 2:
			fe0->dvb.frontend = dvb_attach(drxk_attach,
					&terratec_drxk_config[1],
					&i2c_bus->i2c_adap);
			अगर (fe0->dvb.frontend == शून्य)
				अवरोध;
			अगर (!dvb_attach(mt2063_attach,
					fe0->dvb.frontend,
					&terratec_mt2063_config[1],
					&i2c_bus2->i2c_adap))
				जाओ frontend_detach;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल CX23885_BOARD_TEVII_S471:
		i2c_bus = &dev->i2c_bus[1];

		fe0->dvb.frontend = dvb_attach(ds3000_attach,
					&tevii_ds3000_config,
					&i2c_bus->i2c_adap);
		अगर (fe0->dvb.frontend == शून्य)
			अवरोध;
		dvb_attach(ts2020_attach, fe0->dvb.frontend,
			   &tevii_ts2020_config, &i2c_bus->i2c_adap);
		अवरोध;
	हाल CX23885_BOARD_PROF_8000:
		i2c_bus = &dev->i2c_bus[0];

		fe0->dvb.frontend = dvb_attach(stv090x_attach,
						&prof_8000_stv090x_config,
						&i2c_bus->i2c_adap,
						STV090x_DEMODULATOR_0);
		अगर (fe0->dvb.frontend == शून्य)
			अवरोध;
		अगर (!dvb_attach(stb6100_attach,
				fe0->dvb.frontend,
				&prof_8000_stb6100_config,
				&i2c_bus->i2c_adap))
			जाओ frontend_detach;

		fe0->dvb.frontend->ops.set_voltage = p8000_set_voltage;
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_HVR4400: अणु
		काष्ठा tda10071_platक्रमm_data tda10071_pdata = hauppauge_tda10071_pdata;
		काष्ठा a8293_platक्रमm_data a8293_pdata = अणुपूर्ण;

		i2c_bus = &dev->i2c_bus[0];
		i2c_bus2 = &dev->i2c_bus[1];
		चयन (port->nr) अणु
		/* port b */
		हाल 1:
			/* attach demod + tuner combo */
			स_रखो(&info, 0, माप(info));
			strscpy(info.type, "tda10071_cx24118", I2C_NAME_SIZE);
			info.addr = 0x05;
			info.platक्रमm_data = &tda10071_pdata;
			request_module("tda10071");
			client_demod = i2c_new_client_device(&i2c_bus->i2c_adap, &info);
			अगर (!i2c_client_has_driver(client_demod))
				जाओ frontend_detach;
			अगर (!try_module_get(client_demod->dev.driver->owner)) अणु
				i2c_unरेजिस्टर_device(client_demod);
				जाओ frontend_detach;
			पूर्ण
			fe0->dvb.frontend = tda10071_pdata.get_dvb_frontend(client_demod);
			port->i2c_client_demod = client_demod;

			/* attach SEC */
			a8293_pdata.dvb_frontend = fe0->dvb.frontend;
			स_रखो(&info, 0, माप(info));
			strscpy(info.type, "a8293", I2C_NAME_SIZE);
			info.addr = 0x0b;
			info.platक्रमm_data = &a8293_pdata;
			request_module("a8293");
			client_sec = i2c_new_client_device(&i2c_bus->i2c_adap, &info);
			अगर (!i2c_client_has_driver(client_sec))
				जाओ frontend_detach;
			अगर (!try_module_get(client_sec->dev.driver->owner)) अणु
				i2c_unरेजिस्टर_device(client_sec);
				जाओ frontend_detach;
			पूर्ण
			port->i2c_client_sec = client_sec;
			अवरोध;
		/* port c */
		हाल 2:
			/* attach frontend */
			स_रखो(&si2165_pdata, 0, माप(si2165_pdata));
			si2165_pdata.fe = &fe0->dvb.frontend;
			si2165_pdata.chip_mode = SI2165_MODE_PLL_XTAL;
			si2165_pdata.ref_freq_hz = 16000000;
			स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
			strscpy(info.type, "si2165", I2C_NAME_SIZE);
			info.addr = 0x64;
			info.platक्रमm_data = &si2165_pdata;
			request_module(info.type);
			client_demod = i2c_new_client_device(&i2c_bus->i2c_adap, &info);
			अगर (!i2c_client_has_driver(client_demod))
				जाओ frontend_detach;
			अगर (!try_module_get(client_demod->dev.driver->owner)) अणु
				i2c_unरेजिस्टर_device(client_demod);
				जाओ frontend_detach;
			पूर्ण
			port->i2c_client_demod = client_demod;

			अगर (fe0->dvb.frontend == शून्य)
				अवरोध;
			fe0->dvb.frontend->ops.i2c_gate_ctrl = शून्य;
			अगर (!dvb_attach(tda18271_attach,
					fe0->dvb.frontend,
					0x60, &i2c_bus2->i2c_adap,
				  &hauppauge_hvr4400_tuner_config))
				जाओ frontend_detach;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल CX23885_BOARD_HAUPPAUGE_STARBURST: अणु
		काष्ठा tda10071_platक्रमm_data tda10071_pdata = hauppauge_tda10071_pdata;
		काष्ठा a8293_platक्रमm_data a8293_pdata = अणुपूर्ण;

		i2c_bus = &dev->i2c_bus[0];

		/* attach demod + tuner combo */
		स_रखो(&info, 0, माप(info));
		strscpy(info.type, "tda10071_cx24118", I2C_NAME_SIZE);
		info.addr = 0x05;
		info.platक्रमm_data = &tda10071_pdata;
		request_module("tda10071");
		client_demod = i2c_new_client_device(&i2c_bus->i2c_adap, &info);
		अगर (!i2c_client_has_driver(client_demod))
			जाओ frontend_detach;
		अगर (!try_module_get(client_demod->dev.driver->owner)) अणु
			i2c_unरेजिस्टर_device(client_demod);
			जाओ frontend_detach;
		पूर्ण
		fe0->dvb.frontend = tda10071_pdata.get_dvb_frontend(client_demod);
		port->i2c_client_demod = client_demod;

		/* attach SEC */
		a8293_pdata.dvb_frontend = fe0->dvb.frontend;
		स_रखो(&info, 0, माप(info));
		strscpy(info.type, "a8293", I2C_NAME_SIZE);
		info.addr = 0x0b;
		info.platक्रमm_data = &a8293_pdata;
		request_module("a8293");
		client_sec = i2c_new_client_device(&i2c_bus->i2c_adap, &info);
		अगर (!i2c_client_has_driver(client_sec))
			जाओ frontend_detach;
		अगर (!try_module_get(client_sec->dev.driver->owner)) अणु
			i2c_unरेजिस्टर_device(client_sec);
			जाओ frontend_detach;
		पूर्ण
		port->i2c_client_sec = client_sec;
		अवरोध;
	पूर्ण
	हाल CX23885_BOARD_DVBSKY_T9580:
	हाल CX23885_BOARD_DVBSKY_S950:
		i2c_bus = &dev->i2c_bus[0];
		i2c_bus2 = &dev->i2c_bus[1];
		चयन (port->nr) अणु
		/* port b - satellite */
		हाल 1:
			/* attach frontend */
			fe0->dvb.frontend = dvb_attach(m88ds3103_attach,
					&dvbsky_t9580_m88ds3103_config,
					&i2c_bus2->i2c_adap, &adapter);
			अगर (fe0->dvb.frontend == शून्य)
				अवरोध;

			/* attach tuner */
			स_रखो(&ts2020_config, 0, माप(ts2020_config));
			ts2020_config.fe = fe0->dvb.frontend;
			ts2020_config.get_agc_pwm = m88ds3103_get_agc_pwm;
			स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
			strscpy(info.type, "ts2020", I2C_NAME_SIZE);
			info.addr = 0x60;
			info.platक्रमm_data = &ts2020_config;
			request_module(info.type);
			client_tuner = i2c_new_client_device(adapter, &info);
			अगर (!i2c_client_has_driver(client_tuner))
				जाओ frontend_detach;
			अगर (!try_module_get(client_tuner->dev.driver->owner)) अणु
				i2c_unरेजिस्टर_device(client_tuner);
				जाओ frontend_detach;
			पूर्ण

			/* delegate संकेत strength measurement to tuner */
			fe0->dvb.frontend->ops.पढ़ो_संकेत_strength =
				fe0->dvb.frontend->ops.tuner_ops.get_rf_strength;

			/*
			 * क्रम setting the voltage we need to set GPIOs on
			 * the card.
			 */
			port->fe_set_voltage =
				fe0->dvb.frontend->ops.set_voltage;
			fe0->dvb.frontend->ops.set_voltage =
				dvbsky_t9580_set_voltage;

			port->i2c_client_tuner = client_tuner;

			अवरोध;
		/* port c - terrestrial/cable */
		हाल 2:
			/* attach frontend */
			स_रखो(&si2168_config, 0, माप(si2168_config));
			si2168_config.i2c_adapter = &adapter;
			si2168_config.fe = &fe0->dvb.frontend;
			si2168_config.ts_mode = SI2168_TS_SERIAL;
			स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
			strscpy(info.type, "si2168", I2C_NAME_SIZE);
			info.addr = 0x64;
			info.platक्रमm_data = &si2168_config;
			request_module(info.type);
			client_demod = i2c_new_client_device(&i2c_bus->i2c_adap, &info);
			अगर (!i2c_client_has_driver(client_demod))
				जाओ frontend_detach;
			अगर (!try_module_get(client_demod->dev.driver->owner)) अणु
				i2c_unरेजिस्टर_device(client_demod);
				जाओ frontend_detach;
			पूर्ण
			port->i2c_client_demod = client_demod;

			/* attach tuner */
			स_रखो(&si2157_config, 0, माप(si2157_config));
			si2157_config.fe = fe0->dvb.frontend;
			si2157_config.अगर_port = 1;
			स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
			strscpy(info.type, "si2157", I2C_NAME_SIZE);
			info.addr = 0x60;
			info.platक्रमm_data = &si2157_config;
			request_module(info.type);
			client_tuner = i2c_new_client_device(adapter, &info);
			अगर (!i2c_client_has_driver(client_tuner))
				जाओ frontend_detach;

			अगर (!try_module_get(client_tuner->dev.driver->owner)) अणु
				i2c_unरेजिस्टर_device(client_tuner);
				जाओ frontend_detach;
			पूर्ण
			port->i2c_client_tuner = client_tuner;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल CX23885_BOARD_DVBSKY_T980C:
	हाल CX23885_BOARD_TT_CT2_4500_CI:
		i2c_bus = &dev->i2c_bus[0];
		i2c_bus2 = &dev->i2c_bus[1];

		/* attach frontend */
		स_रखो(&si2168_config, 0, माप(si2168_config));
		si2168_config.i2c_adapter = &adapter;
		si2168_config.fe = &fe0->dvb.frontend;
		si2168_config.ts_mode = SI2168_TS_PARALLEL;
		स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
		strscpy(info.type, "si2168", I2C_NAME_SIZE);
		info.addr = 0x64;
		info.platक्रमm_data = &si2168_config;
		request_module(info.type);
		client_demod = i2c_new_client_device(&i2c_bus2->i2c_adap, &info);
		अगर (!i2c_client_has_driver(client_demod))
			जाओ frontend_detach;
		अगर (!try_module_get(client_demod->dev.driver->owner)) अणु
			i2c_unरेजिस्टर_device(client_demod);
			जाओ frontend_detach;
		पूर्ण
		port->i2c_client_demod = client_demod;

		/* attach tuner */
		स_रखो(&si2157_config, 0, माप(si2157_config));
		si2157_config.fe = fe0->dvb.frontend;
		si2157_config.अगर_port = 1;
		स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
		strscpy(info.type, "si2157", I2C_NAME_SIZE);
		info.addr = 0x60;
		info.platक्रमm_data = &si2157_config;
		request_module(info.type);
		client_tuner = i2c_new_client_device(adapter, &info);
		अगर (!i2c_client_has_driver(client_tuner))
			जाओ frontend_detach;
		अगर (!try_module_get(client_tuner->dev.driver->owner)) अणु
			i2c_unरेजिस्टर_device(client_tuner);
			जाओ frontend_detach;
		पूर्ण
		port->i2c_client_tuner = client_tuner;
		अवरोध;
	हाल CX23885_BOARD_DVBSKY_S950C:
		i2c_bus = &dev->i2c_bus[0];
		i2c_bus2 = &dev->i2c_bus[1];

		/* attach frontend */
		fe0->dvb.frontend = dvb_attach(m88ds3103_attach,
				&dvbsky_s950c_m88ds3103_config,
				&i2c_bus2->i2c_adap, &adapter);
		अगर (fe0->dvb.frontend == शून्य)
			अवरोध;

		/* attach tuner */
		स_रखो(&ts2020_config, 0, माप(ts2020_config));
		ts2020_config.fe = fe0->dvb.frontend;
		ts2020_config.get_agc_pwm = m88ds3103_get_agc_pwm;
		स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
		strscpy(info.type, "ts2020", I2C_NAME_SIZE);
		info.addr = 0x60;
		info.platक्रमm_data = &ts2020_config;
		request_module(info.type);
		client_tuner = i2c_new_client_device(adapter, &info);
		अगर (!i2c_client_has_driver(client_tuner))
			जाओ frontend_detach;
		अगर (!try_module_get(client_tuner->dev.driver->owner)) अणु
			i2c_unरेजिस्टर_device(client_tuner);
			जाओ frontend_detach;
		पूर्ण

		/* delegate संकेत strength measurement to tuner */
		fe0->dvb.frontend->ops.पढ़ो_संकेत_strength =
			fe0->dvb.frontend->ops.tuner_ops.get_rf_strength;

		port->i2c_client_tuner = client_tuner;
		अवरोध;
	हाल CX23885_BOARD_DVBSKY_S952:
		/* attach frontend */
		स_रखो(&m88ds3103_pdata, 0, माप(m88ds3103_pdata));
		m88ds3103_pdata.clk = 27000000;
		m88ds3103_pdata.i2c_wr_max = 33;
		m88ds3103_pdata.agc = 0x99;
		m88ds3103_pdata.clk_out = M88DS3103_CLOCK_OUT_DISABLED;
		m88ds3103_pdata.lnb_en_pol = 1;

		चयन (port->nr) अणु
		/* port b */
		हाल 1:
			i2c_bus = &dev->i2c_bus[1];
			m88ds3103_pdata.ts_mode = M88DS3103_TS_PARALLEL;
			m88ds3103_pdata.ts_clk = 16000;
			m88ds3103_pdata.ts_clk_pol = 1;
			p_set_voltage = dvbsky_t9580_set_voltage;
			अवरोध;
		/* port c */
		हाल 2:
			i2c_bus = &dev->i2c_bus[0];
			m88ds3103_pdata.ts_mode = M88DS3103_TS_SERIAL;
			m88ds3103_pdata.ts_clk = 96000;
			m88ds3103_pdata.ts_clk_pol = 0;
			p_set_voltage = dvbsky_s952_portc_set_voltage;
			अवरोध;
		शेष:
			वापस 0;
		पूर्ण

		स_रखो(&info, 0, माप(info));
		strscpy(info.type, "m88ds3103", I2C_NAME_SIZE);
		info.addr = 0x68;
		info.platक्रमm_data = &m88ds3103_pdata;
		request_module(info.type);
		client_demod = i2c_new_client_device(&i2c_bus->i2c_adap, &info);
		अगर (!i2c_client_has_driver(client_demod))
			जाओ frontend_detach;
		अगर (!try_module_get(client_demod->dev.driver->owner)) अणु
			i2c_unरेजिस्टर_device(client_demod);
			जाओ frontend_detach;
		पूर्ण
		port->i2c_client_demod = client_demod;
		adapter = m88ds3103_pdata.get_i2c_adapter(client_demod);
		fe0->dvb.frontend = m88ds3103_pdata.get_dvb_frontend(client_demod);

		/* attach tuner */
		स_रखो(&ts2020_config, 0, माप(ts2020_config));
		ts2020_config.fe = fe0->dvb.frontend;
		ts2020_config.get_agc_pwm = m88ds3103_get_agc_pwm;
		स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
		strscpy(info.type, "ts2020", I2C_NAME_SIZE);
		info.addr = 0x60;
		info.platक्रमm_data = &ts2020_config;
		request_module(info.type);
		client_tuner = i2c_new_client_device(adapter, &info);
		अगर (!i2c_client_has_driver(client_tuner))
			जाओ frontend_detach;
		अगर (!try_module_get(client_tuner->dev.driver->owner)) अणु
			i2c_unरेजिस्टर_device(client_tuner);
			जाओ frontend_detach;
		पूर्ण

		/* delegate संकेत strength measurement to tuner */
		fe0->dvb.frontend->ops.पढ़ो_संकेत_strength =
			fe0->dvb.frontend->ops.tuner_ops.get_rf_strength;

		/*
		 * क्रम setting the voltage we need to set GPIOs on
		 * the card.
		 */
		port->fe_set_voltage =
			fe0->dvb.frontend->ops.set_voltage;
		fe0->dvb.frontend->ops.set_voltage = p_set_voltage;

		port->i2c_client_tuner = client_tuner;
		अवरोध;
	हाल CX23885_BOARD_DVBSKY_T982:
		स_रखो(&si2168_config, 0, माप(si2168_config));
		चयन (port->nr) अणु
		/* port b */
		हाल 1:
			i2c_bus = &dev->i2c_bus[1];
			si2168_config.ts_mode = SI2168_TS_PARALLEL;
			अवरोध;
		/* port c */
		हाल 2:
			i2c_bus = &dev->i2c_bus[0];
			si2168_config.ts_mode = SI2168_TS_SERIAL;
			अवरोध;
		पूर्ण

		/* attach frontend */
		si2168_config.i2c_adapter = &adapter;
		si2168_config.fe = &fe0->dvb.frontend;
		स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
		strscpy(info.type, "si2168", I2C_NAME_SIZE);
		info.addr = 0x64;
		info.platक्रमm_data = &si2168_config;
		request_module(info.type);
		client_demod = i2c_new_client_device(&i2c_bus->i2c_adap, &info);
		अगर (!i2c_client_has_driver(client_demod))
			जाओ frontend_detach;
		अगर (!try_module_get(client_demod->dev.driver->owner)) अणु
			i2c_unरेजिस्टर_device(client_demod);
			जाओ frontend_detach;
		पूर्ण
		port->i2c_client_demod = client_demod;

		/* attach tuner */
		स_रखो(&si2157_config, 0, माप(si2157_config));
		si2157_config.fe = fe0->dvb.frontend;
		si2157_config.अगर_port = 1;
		स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
		strscpy(info.type, "si2157", I2C_NAME_SIZE);
		info.addr = 0x60;
		info.platक्रमm_data = &si2157_config;
		request_module(info.type);
		client_tuner = i2c_new_client_device(adapter, &info);
		अगर (!i2c_client_has_driver(client_tuner))
			जाओ frontend_detach;
		अगर (!try_module_get(client_tuner->dev.driver->owner)) अणु
			i2c_unरेजिस्टर_device(client_tuner);
			जाओ frontend_detach;
		पूर्ण
		port->i2c_client_tuner = client_tuner;
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_STARBURST2:
	हाल CX23885_BOARD_HAUPPAUGE_HVR5525:
		i2c_bus = &dev->i2c_bus[0];
		i2c_bus2 = &dev->i2c_bus[1];

		चयन (port->nr) अणु

		/* port b - satellite */
		हाल 1:
			/* attach frontend */
			fe0->dvb.frontend = dvb_attach(m88ds3103_attach,
					&hauppauge_hvr5525_m88ds3103_config,
					&i2c_bus->i2c_adap, &adapter);
			अगर (fe0->dvb.frontend == शून्य)
				अवरोध;

			/* attach SEC */
			a8293_pdata.dvb_frontend = fe0->dvb.frontend;
			स_रखो(&info, 0, माप(info));
			strscpy(info.type, "a8293", I2C_NAME_SIZE);
			info.addr = 0x0b;
			info.platक्रमm_data = &a8293_pdata;
			request_module("a8293");
			client_sec = i2c_new_client_device(&i2c_bus->i2c_adap, &info);
			अगर (!i2c_client_has_driver(client_sec))
				जाओ frontend_detach;
			अगर (!try_module_get(client_sec->dev.driver->owner)) अणु
				i2c_unरेजिस्टर_device(client_sec);
				जाओ frontend_detach;
			पूर्ण
			port->i2c_client_sec = client_sec;

			/* attach tuner */
			स_रखो(&m88rs6000t_config, 0, माप(m88rs6000t_config));
			m88rs6000t_config.fe = fe0->dvb.frontend;
			स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
			strscpy(info.type, "m88rs6000t", I2C_NAME_SIZE);
			info.addr = 0x21;
			info.platक्रमm_data = &m88rs6000t_config;
			request_module("%s", info.type);
			client_tuner = i2c_new_client_device(adapter, &info);
			अगर (!i2c_client_has_driver(client_tuner))
				जाओ frontend_detach;
			अगर (!try_module_get(client_tuner->dev.driver->owner)) अणु
				i2c_unरेजिस्टर_device(client_tuner);
				जाओ frontend_detach;
			पूर्ण
			port->i2c_client_tuner = client_tuner;

			/* delegate संकेत strength measurement to tuner */
			fe0->dvb.frontend->ops.पढ़ो_संकेत_strength =
				fe0->dvb.frontend->ops.tuner_ops.get_rf_strength;
			अवरोध;
		/* port c - terrestrial/cable */
		हाल 2:
			/* attach frontend */
			स_रखो(&si2168_config, 0, माप(si2168_config));
			si2168_config.i2c_adapter = &adapter;
			si2168_config.fe = &fe0->dvb.frontend;
			si2168_config.ts_mode = SI2168_TS_SERIAL;
			स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
			strscpy(info.type, "si2168", I2C_NAME_SIZE);
			info.addr = 0x64;
			info.platक्रमm_data = &si2168_config;
			request_module("%s", info.type);
			client_demod = i2c_new_client_device(&i2c_bus->i2c_adap, &info);
			अगर (!i2c_client_has_driver(client_demod))
				जाओ frontend_detach;
			अगर (!try_module_get(client_demod->dev.driver->owner)) अणु
				i2c_unरेजिस्टर_device(client_demod);
				जाओ frontend_detach;
			पूर्ण
			port->i2c_client_demod = client_demod;

			/* attach tuner */
			स_रखो(&si2157_config, 0, माप(si2157_config));
			si2157_config.fe = fe0->dvb.frontend;
			si2157_config.अगर_port = 1;
			स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
			strscpy(info.type, "si2157", I2C_NAME_SIZE);
			info.addr = 0x60;
			info.platक्रमm_data = &si2157_config;
			request_module("%s", info.type);
			client_tuner = i2c_new_client_device(&i2c_bus2->i2c_adap, &info);
			अगर (!i2c_client_has_driver(client_tuner)) अणु
				module_put(client_demod->dev.driver->owner);
				i2c_unरेजिस्टर_device(client_demod);
				port->i2c_client_demod = शून्य;
				जाओ frontend_detach;
			पूर्ण
			अगर (!try_module_get(client_tuner->dev.driver->owner)) अणु
				i2c_unरेजिस्टर_device(client_tuner);
				module_put(client_demod->dev.driver->owner);
				i2c_unरेजिस्टर_device(client_demod);
				port->i2c_client_demod = शून्य;
				जाओ frontend_detach;
			पूर्ण
			port->i2c_client_tuner = client_tuner;

			dev->ts1.analog_fe.tuner_priv = client_tuner;
			स_नकल(&dev->ts1.analog_fe.ops.tuner_ops,
			       &fe0->dvb.frontend->ops.tuner_ops,
			       माप(काष्ठा dvb_tuner_ops));

			अवरोध;
		पूर्ण
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_DVB:
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_DVB_885:
		pr_info("%s(): board=%d port=%d\n", __func__,
			dev->board, port->nr);
		चयन (port->nr) अणु
		/* port b - Terrestrial/cable */
		हाल 1:
			/* attach frontend */
			स_रखो(&si2168_config, 0, माप(si2168_config));
			si2168_config.i2c_adapter = &adapter;
			si2168_config.fe = &fe0->dvb.frontend;
			si2168_config.ts_mode = SI2168_TS_SERIAL;
			स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
			strscpy(info.type, "si2168", I2C_NAME_SIZE);
			info.addr = 0x64;
			info.platक्रमm_data = &si2168_config;
			request_module("%s", info.type);
			client_demod = i2c_new_client_device(&dev->i2c_bus[0].i2c_adap, &info);
			अगर (!i2c_client_has_driver(client_demod))
				जाओ frontend_detach;
			अगर (!try_module_get(client_demod->dev.driver->owner)) अणु
				i2c_unरेजिस्टर_device(client_demod);
				जाओ frontend_detach;
			पूर्ण
			port->i2c_client_demod = client_demod;

			/* attach tuner */
			स_रखो(&si2157_config, 0, माप(si2157_config));
			si2157_config.fe = fe0->dvb.frontend;
			si2157_config.अगर_port = 1;
			स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
			strscpy(info.type, "si2157", I2C_NAME_SIZE);
			info.addr = 0x60;
			info.platक्रमm_data = &si2157_config;
			request_module("%s", info.type);
			client_tuner = i2c_new_client_device(&dev->i2c_bus[1].i2c_adap, &info);
			अगर (!i2c_client_has_driver(client_tuner)) अणु
				module_put(client_demod->dev.driver->owner);
				i2c_unरेजिस्टर_device(client_demod);
				port->i2c_client_demod = शून्य;
				जाओ frontend_detach;
			पूर्ण
			अगर (!try_module_get(client_tuner->dev.driver->owner)) अणु
				i2c_unरेजिस्टर_device(client_tuner);
				module_put(client_demod->dev.driver->owner);
				i2c_unरेजिस्टर_device(client_demod);
				port->i2c_client_demod = शून्य;
				जाओ frontend_detach;
			पूर्ण
			port->i2c_client_tuner = client_tuner;

			/* we only attach tuner क्रम analog on the 888 version */
			अगर (dev->board == CX23885_BOARD_HAUPPAUGE_QUADHD_DVB) अणु
				pr_info("%s(): QUADHD_DVB analog setup\n",
					__func__);
				dev->ts1.analog_fe.tuner_priv = client_tuner;
				स_नकल(&dev->ts1.analog_fe.ops.tuner_ops,
				       &fe0->dvb.frontend->ops.tuner_ops,
				       माप(काष्ठा dvb_tuner_ops));
			पूर्ण
			अवरोध;

		/* port c - terrestrial/cable */
		हाल 2:
			/* attach frontend */
			स_रखो(&si2168_config, 0, माप(si2168_config));
			si2168_config.i2c_adapter = &adapter;
			si2168_config.fe = &fe0->dvb.frontend;
			si2168_config.ts_mode = SI2168_TS_SERIAL;
			स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
			strscpy(info.type, "si2168", I2C_NAME_SIZE);
			info.addr = 0x66;
			info.platक्रमm_data = &si2168_config;
			request_module("%s", info.type);
			client_demod = i2c_new_client_device(&dev->i2c_bus[0].i2c_adap, &info);
			अगर (!i2c_client_has_driver(client_demod))
				जाओ frontend_detach;
			अगर (!try_module_get(client_demod->dev.driver->owner)) अणु
				i2c_unरेजिस्टर_device(client_demod);
				जाओ frontend_detach;
			पूर्ण
			port->i2c_client_demod = client_demod;

			/* attach tuner */
			स_रखो(&si2157_config, 0, माप(si2157_config));
			si2157_config.fe = fe0->dvb.frontend;
			si2157_config.अगर_port = 1;
			स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
			strscpy(info.type, "si2157", I2C_NAME_SIZE);
			info.addr = 0x62;
			info.platक्रमm_data = &si2157_config;
			request_module("%s", info.type);
			client_tuner = i2c_new_client_device(&dev->i2c_bus[1].i2c_adap, &info);
			अगर (!i2c_client_has_driver(client_tuner)) अणु
				module_put(client_demod->dev.driver->owner);
				i2c_unरेजिस्टर_device(client_demod);
				port->i2c_client_demod = शून्य;
				जाओ frontend_detach;
			पूर्ण
			अगर (!try_module_get(client_tuner->dev.driver->owner)) अणु
				i2c_unरेजिस्टर_device(client_tuner);
				module_put(client_demod->dev.driver->owner);
				i2c_unरेजिस्टर_device(client_demod);
				port->i2c_client_demod = शून्य;
				जाओ frontend_detach;
			पूर्ण
			port->i2c_client_tuner = client_tuner;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_ATSC:
	हाल CX23885_BOARD_HAUPPAUGE_QUADHD_ATSC_885:
		pr_info("%s(): board=%d port=%d\n", __func__,
			dev->board, port->nr);
		चयन (port->nr) अणु
		/* port b - Terrestrial/cable */
		हाल 1:
			/* attach frontend */
			i2c_bus = &dev->i2c_bus[0];
			fe0->dvb.frontend = dvb_attach(lgdt3306a_attach,
				&hauppauge_quadHD_ATSC_a_config, &i2c_bus->i2c_adap);
			अगर (fe0->dvb.frontend == शून्य)
				अवरोध;

			/* attach tuner */
			स_रखो(&si2157_config, 0, माप(si2157_config));
			si2157_config.fe = fe0->dvb.frontend;
			si2157_config.अगर_port = 1;
			si2157_config.inversion = 1;
			स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
			strscpy(info.type, "si2157", I2C_NAME_SIZE);
			info.addr = 0x60;
			info.platक्रमm_data = &si2157_config;
			request_module("%s", info.type);
			client_tuner = i2c_new_client_device(&dev->i2c_bus[1].i2c_adap, &info);
			अगर (!i2c_client_has_driver(client_tuner)) अणु
				module_put(client_demod->dev.driver->owner);
				i2c_unरेजिस्टर_device(client_demod);
				port->i2c_client_demod = शून्य;
				जाओ frontend_detach;
			पूर्ण
			अगर (!try_module_get(client_tuner->dev.driver->owner)) अणु
				i2c_unरेजिस्टर_device(client_tuner);
				module_put(client_demod->dev.driver->owner);
				i2c_unरेजिस्टर_device(client_demod);
				port->i2c_client_demod = शून्य;
				जाओ frontend_detach;
			पूर्ण
			port->i2c_client_tuner = client_tuner;

			/* we only attach tuner क्रम analog on the 888 version */
			अगर (dev->board == CX23885_BOARD_HAUPPAUGE_QUADHD_ATSC) अणु
				pr_info("%s(): QUADHD_ATSC analog setup\n",
					__func__);
				dev->ts1.analog_fe.tuner_priv = client_tuner;
				स_नकल(&dev->ts1.analog_fe.ops.tuner_ops,
				       &fe0->dvb.frontend->ops.tuner_ops,
				       माप(काष्ठा dvb_tuner_ops));
			पूर्ण
			अवरोध;

		/* port c - terrestrial/cable */
		हाल 2:
			/* attach frontend */
			i2c_bus = &dev->i2c_bus[0];
			fe0->dvb.frontend = dvb_attach(lgdt3306a_attach,
				&hauppauge_quadHD_ATSC_b_config, &i2c_bus->i2c_adap);
			अगर (fe0->dvb.frontend == शून्य)
				अवरोध;

			/* attach tuner */
			स_रखो(&si2157_config, 0, माप(si2157_config));
			si2157_config.fe = fe0->dvb.frontend;
			si2157_config.अगर_port = 1;
			si2157_config.inversion = 1;
			स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
			strscpy(info.type, "si2157", I2C_NAME_SIZE);
			info.addr = 0x62;
			info.platक्रमm_data = &si2157_config;
			request_module("%s", info.type);
			client_tuner = i2c_new_client_device(&dev->i2c_bus[1].i2c_adap, &info);
			अगर (!i2c_client_has_driver(client_tuner)) अणु
				module_put(client_demod->dev.driver->owner);
				i2c_unरेजिस्टर_device(client_demod);
				port->i2c_client_demod = शून्य;
				जाओ frontend_detach;
			पूर्ण
			अगर (!try_module_get(client_tuner->dev.driver->owner)) अणु
				i2c_unरेजिस्टर_device(client_tuner);
				module_put(client_demod->dev.driver->owner);
				i2c_unरेजिस्टर_device(client_demod);
				port->i2c_client_demod = शून्य;
				जाओ frontend_detach;
			पूर्ण
			port->i2c_client_tuner = client_tuner;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल CX23885_BOARD_HAUPPAUGE_HVR1265_K4:
		चयन (port->nr) अणु
		/* port c - Terrestrial/cable */
		हाल 2:
			/* attach frontend */
			i2c_bus = &dev->i2c_bus[0];
			fe0->dvb.frontend = dvb_attach(lgdt3306a_attach,
					&hauppauge_hvr1265k4_config,
					&i2c_bus->i2c_adap);
			अगर (fe0->dvb.frontend == शून्य)
				अवरोध;

			/* attach tuner */
			स_रखो(&si2157_config, 0, माप(si2157_config));
			si2157_config.fe = fe0->dvb.frontend;
			si2157_config.अगर_port = 1;
			si2157_config.inversion = 1;
			स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
			strscpy(info.type, "si2157", I2C_NAME_SIZE);
			info.addr = 0x60;
			info.platक्रमm_data = &si2157_config;
			request_module("%s", info.type);
			client_tuner = i2c_new_client_device(&dev->i2c_bus[1].i2c_adap, &info);
			अगर (!i2c_client_has_driver(client_tuner))
				जाओ frontend_detach;

			अगर (!try_module_get(client_tuner->dev.driver->owner)) अणु
				i2c_unरेजिस्टर_device(client_tuner);
				client_tuner = शून्य;
				जाओ frontend_detach;
			पूर्ण
			port->i2c_client_tuner = client_tuner;

			dev->ts1.analog_fe.tuner_priv = client_tuner;
			स_नकल(&dev->ts1.analog_fe.ops.tuner_ops,
			       &fe0->dvb.frontend->ops.tuner_ops,
			       माप(काष्ठा dvb_tuner_ops));
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		pr_info("%s: The frontend of your DVB/ATSC card  isn't supported yet\n",
			dev->name);
		अवरोध;
	पूर्ण

	अगर ((शून्य == fe0->dvb.frontend) || (fe1 && शून्य == fe1->dvb.frontend)) अणु
		pr_err("%s: frontend initialization failed\n",
		       dev->name);
		जाओ frontend_detach;
	पूर्ण

	/* define general-purpose callback poपूर्णांकer */
	fe0->dvb.frontend->callback = cx23885_tuner_callback;
	अगर (fe1)
		fe1->dvb.frontend->callback = cx23885_tuner_callback;
#अगर 0
	/* Ensure all frontends negotiate bus access */
	fe0->dvb.frontend->ops.ts_bus_ctrl = cx23885_dvb_bus_ctrl;
	अगर (fe1)
		fe1->dvb.frontend->ops.ts_bus_ctrl = cx23885_dvb_bus_ctrl;
#पूर्ण_अगर

	/* Put the tuner in standby to keep it quiet */
	call_all(dev, tuner, standby);

	अगर (fe0->dvb.frontend->ops.analog_ops.standby)
		fe0->dvb.frontend->ops.analog_ops.standby(fe0->dvb.frontend);

	/* रेजिस्टर everything */
	ret = vb2_dvb_रेजिस्टर_bus(&port->frontends, THIS_MODULE, port,
				   &dev->pci->dev, शून्य,
				   adapter_nr, mfe_shared);
	अगर (ret)
		जाओ frontend_detach;

	ret = dvb_रेजिस्टर_ci_mac(port);
	अगर (ret)
		जाओ frontend_detach;

	वापस 0;

frontend_detach:
	/* हटाओ I2C client क्रम SEC */
	client_sec = port->i2c_client_sec;
	अगर (client_sec) अणु
		module_put(client_sec->dev.driver->owner);
		i2c_unरेजिस्टर_device(client_sec);
		port->i2c_client_sec = शून्य;
	पूर्ण

	/* हटाओ I2C client क्रम tuner */
	client_tuner = port->i2c_client_tuner;
	अगर (client_tuner) अणु
		module_put(client_tuner->dev.driver->owner);
		i2c_unरेजिस्टर_device(client_tuner);
		port->i2c_client_tuner = शून्य;
	पूर्ण

	/* हटाओ I2C client क्रम demodulator */
	client_demod = port->i2c_client_demod;
	अगर (client_demod) अणु
		module_put(client_demod->dev.driver->owner);
		i2c_unरेजिस्टर_device(client_demod);
		port->i2c_client_demod = शून्य;
	पूर्ण

	port->gate_ctrl = शून्य;
	vb2_dvb_dealloc_frontends(&port->frontends);
	वापस -EINVAL;
पूर्ण

पूर्णांक cx23885_dvb_रेजिस्टर(काष्ठा cx23885_tsport *port)
अणु

	काष्ठा vb2_dvb_frontend *fe0;
	काष्ठा cx23885_dev *dev = port->dev;
	पूर्णांक err, i;

	/* Here we need to allocate the correct number of frontends,
	 * as reflected in the cards काष्ठा. The reality is that currently
	 * no cx23885 boards support this - yet. But, अगर we करोn't modअगरy this
	 * code then the second frontend would never be allocated (later)
	 * and fail with error beक्रमe the attach in dvb_रेजिस्टर().
	 * Without these changes we risk an OOPS later. The changes here
	 * are क्रम safety, and should provide a good foundation क्रम the
	 * future addition of any multi-frontend cx23885 based boards.
	 */
	pr_info("%s() allocating %d frontend(s)\n", __func__,
		port->num_frontends);

	क्रम (i = 1; i <= port->num_frontends; i++) अणु
		काष्ठा vb2_queue *q;

		अगर (vb2_dvb_alloc_frontend(
			&port->frontends, i) == शून्य) अणु
			pr_err("%s() failed to alloc\n", __func__);
			वापस -ENOMEM;
		पूर्ण

		fe0 = vb2_dvb_get_frontend(&port->frontends, i);
		अगर (!fe0)
			वापस -EINVAL;

		dprपूर्णांकk(1, "%s\n", __func__);
		dprपूर्णांकk(1, " ->probed by Card=%d Name=%s, PCI %02x:%02x\n",
			dev->board,
			dev->name,
			dev->pci_bus,
			dev->pci_slot);

		/* dvb stuff */
		/* We have to init the queue क्रम each frontend on a port. */
		pr_info("%s: cx23885 based dvb card\n", dev->name);
		q = &fe0->dvb.dvbq;
		q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		q->io_modes = VB2_MMAP | VB2_USERPTR | VB2_DMABUF | VB2_READ;
		q->gfp_flags = GFP_DMA32;
		q->min_buffers_needed = 2;
		q->drv_priv = port;
		q->buf_काष्ठा_size = माप(काष्ठा cx23885_buffer);
		q->ops = &dvb_qops;
		q->mem_ops = &vb2_dma_sg_memops;
		q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
		q->lock = &dev->lock;
		q->dev = &dev->pci->dev;

		err = vb2_queue_init(q);
		अगर (err < 0)
			वापस err;
	पूर्ण
	err = dvb_रेजिस्टर(port);
	अगर (err != 0)
		pr_err("%s() dvb_register failed err = %d\n",
		       __func__, err);

	वापस err;
पूर्ण

पूर्णांक cx23885_dvb_unरेजिस्टर(काष्ठा cx23885_tsport *port)
अणु
	काष्ठा vb2_dvb_frontend *fe0;
	काष्ठा i2c_client *client;

	fe0 = vb2_dvb_get_frontend(&port->frontends, 1);

	अगर (fe0 && fe0->dvb.frontend)
		vb2_dvb_unरेजिस्टर_bus(&port->frontends);

	/* हटाओ I2C client क्रम CI */
	client = port->i2c_client_ci;
	अगर (client) अणु
		module_put(client->dev.driver->owner);
		i2c_unरेजिस्टर_device(client);
	पूर्ण

	/* हटाओ I2C client क्रम SEC */
	client = port->i2c_client_sec;
	अगर (client) अणु
		module_put(client->dev.driver->owner);
		i2c_unरेजिस्टर_device(client);
	पूर्ण

	/* हटाओ I2C client क्रम tuner */
	client = port->i2c_client_tuner;
	अगर (client) अणु
		module_put(client->dev.driver->owner);
		i2c_unरेजिस्टर_device(client);
	पूर्ण

	/* हटाओ I2C client क्रम demodulator */
	client = port->i2c_client_demod;
	अगर (client) अणु
		module_put(client->dev.driver->owner);
		i2c_unरेजिस्टर_device(client);
	पूर्ण

	चयन (port->dev->board) अणु
	हाल CX23885_BOARD_NETUP_DUAL_DVBS2_CI:
		netup_ci_निकास(port);
		अवरोध;
	हाल CX23885_BOARD_NETUP_DUAL_DVB_T_C_CI_RF:
		altera_ci_release(port->dev, port->nr);
		अवरोध;
	पूर्ण

	port->gate_ctrl = शून्य;

	वापस 0;
पूर्ण
