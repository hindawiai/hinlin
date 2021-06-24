<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* DVB USB compliant Linux driver क्रम the AZUREWAVE DVB-S/S2 USB2.0 (AZ6027)
 * receiver.
 *
 * Copyright (C) 2009 Adams.Xu <adams.xu@azwave.com.cn>
 *
 * see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
 */
#समावेश "az6027.h"

#समावेश "stb0899_drv.h"
#समावेश "stb0899_reg.h"
#समावेश "stb0899_cfg.h"

#समावेश "stb6100.h"
#समावेश "stb6100_cfg.h"
#समावेश <media/dvb_ca_en50221.h>

पूर्णांक dvb_usb_az6027_debug;
module_param_named(debug, dvb_usb_az6027_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "set debugging level (1=info,xfer=2,rc=4 (or-able))." DVB_USB_DEBUG_STATUS);

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

काष्ठा az6027_device_state अणु
	काष्ठा dvb_ca_en50221 ca;
	काष्ठा mutex ca_mutex;
	u8 घातer_state;
पूर्ण;

अटल स्थिर काष्ठा stb0899_s1_reg az6027_stb0899_s1_init_1[] = अणु

	/* 0x0000000b, SYSREG */
	अणु STB0899_DEV_ID		, 0x30 पूर्ण,
	अणु STB0899_DISCNTRL1		, 0x32 पूर्ण,
	अणु STB0899_DISCNTRL2		, 0x80 पूर्ण,
	अणु STB0899_DISRX_ST0		, 0x04 पूर्ण,
	अणु STB0899_DISRX_ST1		, 0x00 पूर्ण,
	अणु STB0899_DISPARITY		, 0x00 पूर्ण,
	अणु STB0899_DISSTATUS		, 0x20 पूर्ण,
	अणु STB0899_DISF22		, 0x99 पूर्ण,
	अणु STB0899_DISF22RX		, 0xa8 पूर्ण,
	/* SYSREG ? */
	अणु STB0899_ACRPRESC		, 0x11 पूर्ण,
	अणु STB0899_ACRDIV1		, 0x0a पूर्ण,
	अणु STB0899_ACRDIV2		, 0x05 पूर्ण,
	अणु STB0899_DACR1			, 0x00 पूर्ण,
	अणु STB0899_DACR2			, 0x00 पूर्ण,
	अणु STB0899_OUTCFG		, 0x00 पूर्ण,
	अणु STB0899_MODECFG		, 0x00 पूर्ण,
	अणु STB0899_IRQSTATUS_3		, 0xfe पूर्ण,
	अणु STB0899_IRQSTATUS_2		, 0x03 पूर्ण,
	अणु STB0899_IRQSTATUS_1		, 0x7c पूर्ण,
	अणु STB0899_IRQSTATUS_0		, 0xf4 पूर्ण,
	अणु STB0899_IRQMSK_3		, 0xf3 पूर्ण,
	अणु STB0899_IRQMSK_2		, 0xfc पूर्ण,
	अणु STB0899_IRQMSK_1		, 0xff पूर्ण,
	अणु STB0899_IRQMSK_0		, 0xff पूर्ण,
	अणु STB0899_IRQCFG		, 0x00 पूर्ण,
	अणु STB0899_I2CCFG		, 0x88 पूर्ण,
	अणु STB0899_I2CRPT		, 0x58 पूर्ण,
	अणु STB0899_IOPVALUE5		, 0x00 पूर्ण,
	अणु STB0899_IOPVALUE4		, 0x33 पूर्ण,
	अणु STB0899_IOPVALUE3		, 0x6d पूर्ण,
	अणु STB0899_IOPVALUE2		, 0x90 पूर्ण,
	अणु STB0899_IOPVALUE1		, 0x60 पूर्ण,
	अणु STB0899_IOPVALUE0		, 0x00 पूर्ण,
	अणु STB0899_GPIO00CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO01CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO02CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO03CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO04CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO05CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO06CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO07CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO08CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO09CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO10CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO11CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO12CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO13CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO14CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO15CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO16CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO17CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO18CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO19CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO20CFG		, 0x82 पूर्ण,
	अणु STB0899_SDATCFG		, 0xb8 पूर्ण,
	अणु STB0899_SCLTCFG		, 0xba पूर्ण,
	अणु STB0899_AGCRFCFG		, 0x1c पूर्ण, /* 0x11 */
	अणु STB0899_GPIO22		, 0x82 पूर्ण, /* AGCBB2CFG */
	अणु STB0899_GPIO21		, 0x91 पूर्ण, /* AGCBB1CFG */
	अणु STB0899_सूचीCLKCFG		, 0x82 पूर्ण,
	अणु STB0899_CLKOUT27CFG		, 0x7e पूर्ण,
	अणु STB0899_STDBYCFG		, 0x82 पूर्ण,
	अणु STB0899_CS0CFG		, 0x82 पूर्ण,
	अणु STB0899_CS1CFG		, 0x82 पूर्ण,
	अणु STB0899_DISEQCOCFG		, 0x20 पूर्ण,
	अणु STB0899_GPIO32CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO33CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO34CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO35CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO36CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO37CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO38CFG		, 0x82 पूर्ण,
	अणु STB0899_GPIO39CFG		, 0x82 पूर्ण,
	अणु STB0899_NCOARSE		, 0x17 पूर्ण, /* 0x15 = 27 Mhz Clock, F/3 = 198MHz, F/6 = 99MHz */
	अणु STB0899_SYNTCTRL		, 0x02 पूर्ण, /* 0x00 = CLK from CLKI, 0x02 = CLK from XTALI */
	अणु STB0899_FILTCTRL		, 0x00 पूर्ण,
	अणु STB0899_SYSCTRL		, 0x01 पूर्ण,
	अणु STB0899_STOPCLK1		, 0x20 पूर्ण,
	अणु STB0899_STOPCLK2		, 0x00 पूर्ण,
	अणु STB0899_INTBUFSTATUS		, 0x00 पूर्ण,
	अणु STB0899_INTBUFCTRL		, 0x0a पूर्ण,
	अणु 0xffff			, 0xff पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा stb0899_s1_reg az6027_stb0899_s1_init_3[] = अणु
	अणु STB0899_DEMOD			, 0x00 पूर्ण,
	अणु STB0899_RCOMPC		, 0xc9 पूर्ण,
	अणु STB0899_AGC1CN		, 0x01 पूर्ण,
	अणु STB0899_AGC1REF		, 0x10 पूर्ण,
	अणु STB0899_RTC			, 0x23 पूर्ण,
	अणु STB0899_TMGCFG		, 0x4e पूर्ण,
	अणु STB0899_AGC2REF		, 0x34 पूर्ण,
	अणु STB0899_TLSR			, 0x84 पूर्ण,
	अणु STB0899_CFD			, 0xf7 पूर्ण,
	अणु STB0899_ACLC			, 0x87 पूर्ण,
	अणु STB0899_BCLC			, 0x94 पूर्ण,
	अणु STB0899_EQON			, 0x41 पूर्ण,
	अणु STB0899_LDT			, 0xf1 पूर्ण,
	अणु STB0899_LDT2			, 0xe3 पूर्ण,
	अणु STB0899_EQUALREF		, 0xb4 पूर्ण,
	अणु STB0899_TMGRAMP		, 0x10 पूर्ण,
	अणु STB0899_TMGTHD		, 0x30 पूर्ण,
	अणु STB0899_IDCCOMP		, 0xfd पूर्ण,
	अणु STB0899_QDCCOMP		, 0xff पूर्ण,
	अणु STB0899_POWERI		, 0x0c पूर्ण,
	अणु STB0899_POWERQ		, 0x0f पूर्ण,
	अणु STB0899_RCOMP			, 0x6c पूर्ण,
	अणु STB0899_AGCIQIN		, 0x80 पूर्ण,
	अणु STB0899_AGC2I1		, 0x06 पूर्ण,
	अणु STB0899_AGC2I2		, 0x00 पूर्ण,
	अणु STB0899_TLIR			, 0x30 पूर्ण,
	अणु STB0899_RTF			, 0x7f पूर्ण,
	अणु STB0899_DSTATUS		, 0x00 पूर्ण,
	अणु STB0899_LDI			, 0xbc पूर्ण,
	अणु STB0899_CFRM			, 0xea पूर्ण,
	अणु STB0899_CFRL			, 0x31 पूर्ण,
	अणु STB0899_NIRM			, 0x2b पूर्ण,
	अणु STB0899_NIRL			, 0x80 पूर्ण,
	अणु STB0899_ISYMB			, 0x1d पूर्ण,
	अणु STB0899_QSYMB			, 0xa6 पूर्ण,
	अणु STB0899_SFRH			, 0x2f पूर्ण,
	अणु STB0899_SFRM			, 0x68 पूर्ण,
	अणु STB0899_SFRL			, 0x40 पूर्ण,
	अणु STB0899_SFRUPH		, 0x2f पूर्ण,
	अणु STB0899_SFRUPM		, 0x68 पूर्ण,
	अणु STB0899_SFRUPL		, 0x40 पूर्ण,
	अणु STB0899_EQUAI1		, 0x02 पूर्ण,
	अणु STB0899_EQUAQ1		, 0xff पूर्ण,
	अणु STB0899_EQUAI2		, 0x04 पूर्ण,
	अणु STB0899_EQUAQ2		, 0x05 पूर्ण,
	अणु STB0899_EQUAI3		, 0x02 पूर्ण,
	अणु STB0899_EQUAQ3		, 0xfd पूर्ण,
	अणु STB0899_EQUAI4		, 0x03 पूर्ण,
	अणु STB0899_EQUAQ4		, 0x07 पूर्ण,
	अणु STB0899_EQUAI5		, 0x08 पूर्ण,
	अणु STB0899_EQUAQ5		, 0xf5 पूर्ण,
	अणु STB0899_DSTATUS2		, 0x00 पूर्ण,
	अणु STB0899_VSTATUS		, 0x00 पूर्ण,
	अणु STB0899_VERROR		, 0x86 पूर्ण,
	अणु STB0899_IQSWAP		, 0x2a पूर्ण,
	अणु STB0899_ECNT1M		, 0x00 पूर्ण,
	अणु STB0899_ECNT1L		, 0x00 पूर्ण,
	अणु STB0899_ECNT2M		, 0x00 पूर्ण,
	अणु STB0899_ECNT2L		, 0x00 पूर्ण,
	अणु STB0899_ECNT3M		, 0x0a पूर्ण,
	अणु STB0899_ECNT3L		, 0xad पूर्ण,
	अणु STB0899_FECAUTO1		, 0x06 पूर्ण,
	अणु STB0899_FECM			, 0x01 पूर्ण,
	अणु STB0899_VTH12			, 0xb0 पूर्ण,
	अणु STB0899_VTH23			, 0x7a पूर्ण,
	अणु STB0899_VTH34			, 0x58 पूर्ण,
	अणु STB0899_VTH56			, 0x38 पूर्ण,
	अणु STB0899_VTH67			, 0x34 पूर्ण,
	अणु STB0899_VTH78			, 0x24 पूर्ण,
	अणु STB0899_PRVIT			, 0xff पूर्ण,
	अणु STB0899_VITSYNC		, 0x19 पूर्ण,
	अणु STB0899_RSULC			, 0xb1 पूर्ण, /* DVB = 0xb1, DSS = 0xa1 */
	अणु STB0899_TSULC			, 0x42 पूर्ण,
	अणु STB0899_RSLLC			, 0x41 पूर्ण,
	अणु STB0899_TSLPL			, 0x12 पूर्ण,
	अणु STB0899_TSCFGH		, 0x0c पूर्ण,
	अणु STB0899_TSCFGM		, 0x00 पूर्ण,
	अणु STB0899_TSCFGL		, 0x00 पूर्ण,
	अणु STB0899_TSOUT			, 0x69 पूर्ण, /* 0x0d क्रम CAM */
	अणु STB0899_RSSYNCDEL		, 0x00 पूर्ण,
	अणु STB0899_TSINHDELH		, 0x02 पूर्ण,
	अणु STB0899_TSINHDELM		, 0x00 पूर्ण,
	अणु STB0899_TSINHDELL		, 0x00 पूर्ण,
	अणु STB0899_TSLLSTKM		, 0x1b पूर्ण,
	अणु STB0899_TSLLSTKL		, 0xb3 पूर्ण,
	अणु STB0899_TSULSTKM		, 0x00 पूर्ण,
	अणु STB0899_TSULSTKL		, 0x00 पूर्ण,
	अणु STB0899_PCKLENUL		, 0xbc पूर्ण,
	अणु STB0899_PCKLENLL		, 0xcc पूर्ण,
	अणु STB0899_RSPCKLEN		, 0xbd पूर्ण,
	अणु STB0899_TSSTATUS		, 0x90 पूर्ण,
	अणु STB0899_ERRCTRL1		, 0xb6 पूर्ण,
	अणु STB0899_ERRCTRL2		, 0x95 पूर्ण,
	अणु STB0899_ERRCTRL3		, 0x8d पूर्ण,
	अणु STB0899_DMONMSK1		, 0x27 पूर्ण,
	अणु STB0899_DMONMSK0		, 0x03 पूर्ण,
	अणु STB0899_DEMAPVIT		, 0x5c पूर्ण,
	अणु STB0899_PLPARM		, 0x19 पूर्ण,
	अणु STB0899_PDELCTRL		, 0x48 पूर्ण,
	अणु STB0899_PDELCTRL2		, 0x00 पूर्ण,
	अणु STB0899_BBHCTRL1		, 0x00 पूर्ण,
	अणु STB0899_BBHCTRL2		, 0x00 पूर्ण,
	अणु STB0899_HYSTTHRESH		, 0x77 पूर्ण,
	अणु STB0899_MATCSTM		, 0x00 पूर्ण,
	अणु STB0899_MATCSTL		, 0x00 पूर्ण,
	अणु STB0899_UPLCSTM		, 0x00 पूर्ण,
	अणु STB0899_UPLCSTL		, 0x00 पूर्ण,
	अणु STB0899_DFLCSTM		, 0x00 पूर्ण,
	अणु STB0899_DFLCSTL		, 0x00 पूर्ण,
	अणु STB0899_SYNCCST		, 0x00 पूर्ण,
	अणु STB0899_SYNCDCSTM		, 0x00 पूर्ण,
	अणु STB0899_SYNCDCSTL		, 0x00 पूर्ण,
	अणु STB0899_ISI_ENTRY		, 0x00 पूर्ण,
	अणु STB0899_ISI_BIT_EN		, 0x00 पूर्ण,
	अणु STB0899_MATSTRM		, 0xf0 पूर्ण,
	अणु STB0899_MATSTRL		, 0x02 पूर्ण,
	अणु STB0899_UPLSTRM		, 0x45 पूर्ण,
	अणु STB0899_UPLSTRL		, 0x60 पूर्ण,
	अणु STB0899_DFLSTRM		, 0xe3 पूर्ण,
	अणु STB0899_DFLSTRL		, 0x00 पूर्ण,
	अणु STB0899_SYNCSTR		, 0x47 पूर्ण,
	अणु STB0899_SYNCDSTRM		, 0x05 पूर्ण,
	अणु STB0899_SYNCDSTRL		, 0x18 पूर्ण,
	अणु STB0899_CFGPDELSTATUS1	, 0x19 पूर्ण,
	अणु STB0899_CFGPDELSTATUS2	, 0x2b पूर्ण,
	अणु STB0899_BBFERRORM		, 0x00 पूर्ण,
	अणु STB0899_BBFERRORL		, 0x01 पूर्ण,
	अणु STB0899_UPKTERRORM		, 0x00 पूर्ण,
	अणु STB0899_UPKTERRORL		, 0x00 पूर्ण,
	अणु 0xffff			, 0xff पूर्ण,
पूर्ण;



अटल काष्ठा stb0899_config az6027_stb0899_config = अणु
	.init_dev		= az6027_stb0899_s1_init_1,
	.init_s2_demod		= stb0899_s2_init_2,
	.init_s1_demod		= az6027_stb0899_s1_init_3,
	.init_s2_fec		= stb0899_s2_init_4,
	.init_tst		= stb0899_s1_init_5,

	.demod_address		= 0xd0, /* 0x68, 0xd0 >> 1 */

	.xtal_freq		= 27000000,
	.inversion		= IQ_SWAP_ON,

	.lo_clk			= 76500000,
	.hi_clk			= 99000000,

	.esno_ave		= STB0899_DVBS2_ESNO_AVE,
	.esno_quant		= STB0899_DVBS2_ESNO_QUANT,
	.avframes_coarse	= STB0899_DVBS2_AVFRAMES_COARSE,
	.avframes_fine		= STB0899_DVBS2_AVFRAMES_FINE,
	.miss_threshold		= STB0899_DVBS2_MISS_THRESHOLD,
	.uwp_threshold_acq	= STB0899_DVBS2_UWP_THRESHOLD_ACQ,
	.uwp_threshold_track	= STB0899_DVBS2_UWP_THRESHOLD_TRACK,
	.uwp_threshold_sof	= STB0899_DVBS2_UWP_THRESHOLD_SOF,
	.sof_search_समयout	= STB0899_DVBS2_SOF_SEARCH_TIMEOUT,

	.btr_nco_bits		= STB0899_DVBS2_BTR_NCO_BITS,
	.btr_gain_shअगरt_offset	= STB0899_DVBS2_BTR_GAIN_SHIFT_OFFSET,
	.crl_nco_bits		= STB0899_DVBS2_CRL_NCO_BITS,
	.ldpc_max_iter		= STB0899_DVBS2_LDPC_MAX_ITER,

	.tuner_get_frequency	= stb6100_get_frequency,
	.tuner_set_frequency	= stb6100_set_frequency,
	.tuner_set_bandwidth	= stb6100_set_bandwidth,
	.tuner_get_bandwidth	= stb6100_get_bandwidth,
	.tuner_set_rfsiggain	= शून्य,
पूर्ण;

अटल काष्ठा stb6100_config az6027_stb6100_config = अणु
	.tuner_address	= 0xc0,
	.refघड़ी	= 27000000,
पूर्ण;


/* check क्रम mutex FIXME */
अटल पूर्णांक az6027_usb_in_op(काष्ठा dvb_usb_device *d, u8 req,
			    u16 value, u16 index, u8 *b, पूर्णांक blen)
अणु
	पूर्णांक ret = -1;
	अगर (mutex_lock_पूर्णांकerruptible(&d->usb_mutex))
		वापस -EAGAIN;

	ret = usb_control_msg(d->udev,
			      usb_rcvctrlpipe(d->udev, 0),
			      req,
			      USB_TYPE_VENDOR | USB_सूची_IN,
			      value,
			      index,
			      b,
			      blen,
			      2000);

	अगर (ret < 0) अणु
		warn("usb in operation failed. (%d)", ret);
		ret = -EIO;
	पूर्ण अन्यथा
		ret = 0;

	deb_xfer("in: req. %02x, val: %04x, ind: %04x, buffer: ", req, value, index);
	debug_dump(b, blen, deb_xfer);

	mutex_unlock(&d->usb_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक az6027_usb_out_op(काष्ठा dvb_usb_device *d,
			     u8 req,
			     u16 value,
			     u16 index,
			     u8 *b,
			     पूर्णांक blen)
अणु
	पूर्णांक ret;

	deb_xfer("out: req. %02x, val: %04x, ind: %04x, buffer: ", req, value, index);
	debug_dump(b, blen, deb_xfer);

	अगर (mutex_lock_पूर्णांकerruptible(&d->usb_mutex))
		वापस -EAGAIN;

	ret = usb_control_msg(d->udev,
			      usb_sndctrlpipe(d->udev, 0),
			      req,
			      USB_TYPE_VENDOR | USB_सूची_OUT,
			      value,
			      index,
			      b,
			      blen,
			      2000);

	अगर (ret != blen) अणु
		warn("usb out operation failed. (%d)", ret);
		mutex_unlock(&d->usb_mutex);
		वापस -EIO;
	पूर्ण अन्यथाअणु
		mutex_unlock(&d->usb_mutex);
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक az6027_streaming_ctrl(काष्ठा dvb_usb_adapter *adap, पूर्णांक onoff)
अणु
	पूर्णांक ret;
	u8 req;
	u16 value;
	u16 index;
	पूर्णांक blen;

	deb_info("%s %d", __func__, onoff);

	req = 0xBC;
	value = onoff;
	index = 0;
	blen = 0;

	ret = az6027_usb_out_op(adap->dev, req, value, index, शून्य, blen);
	अगर (ret != 0)
		warn("usb out operation failed. (%d)", ret);

	वापस ret;
पूर्ण

/* keys क्रम the enबंदd remote control */
अटल काष्ठा rc_map_table rc_map_az6027_table[] = अणु
	अणु 0x01, KEY_1 पूर्ण,
	अणु 0x02, KEY_2 पूर्ण,
पूर्ण;

/* remote control stuff (करोes not work with my box) */
अटल पूर्णांक az6027_rc_query(काष्ठा dvb_usb_device *d, u32 *event, पूर्णांक *state)
अणु
	वापस 0;
पूर्ण

/*
पूर्णांक az6027_घातer_ctrl(काष्ठा dvb_usb_device *d, पूर्णांक onoff)
अणु
	u8 v = onoff;
	वापस az6027_usb_out_op(d,0xBC,v,3,शून्य,1);
पूर्ण
*/

अटल पूर्णांक az6027_ci_पढ़ो_attribute_mem(काष्ठा dvb_ca_en50221 *ca,
					पूर्णांक slot,
					पूर्णांक address)
अणु
	काष्ठा dvb_usb_device *d = (काष्ठा dvb_usb_device *)ca->data;
	काष्ठा az6027_device_state *state = (काष्ठा az6027_device_state *)d->priv;

	पूर्णांक ret;
	u8 req;
	u16 value;
	u16 index;
	पूर्णांक blen;
	u8 *b;

	अगर (slot != 0)
		वापस -EINVAL;

	b = kदो_स्मृति(12, GFP_KERNEL);
	अगर (!b)
		वापस -ENOMEM;

	mutex_lock(&state->ca_mutex);

	req = 0xC1;
	value = address;
	index = 0;
	blen = 1;

	ret = az6027_usb_in_op(d, req, value, index, b, blen);
	अगर (ret < 0) अणु
		warn("usb in operation failed. (%d)", ret);
		ret = -EINVAL;
	पूर्ण अन्यथा अणु
		ret = b[0];
	पूर्ण

	mutex_unlock(&state->ca_mutex);
	kमुक्त(b);
	वापस ret;
पूर्ण

अटल पूर्णांक az6027_ci_ग_लिखो_attribute_mem(काष्ठा dvb_ca_en50221 *ca,
					 पूर्णांक slot,
					 पूर्णांक address,
					 u8 value)
अणु
	काष्ठा dvb_usb_device *d = (काष्ठा dvb_usb_device *)ca->data;
	काष्ठा az6027_device_state *state = (काष्ठा az6027_device_state *)d->priv;

	पूर्णांक ret;
	u8 req;
	u16 value1;
	u16 index;
	पूर्णांक blen;

	deb_info("%s %d", __func__, slot);
	अगर (slot != 0)
		वापस -EINVAL;

	mutex_lock(&state->ca_mutex);
	req = 0xC2;
	value1 = address;
	index = value;
	blen = 0;

	ret = az6027_usb_out_op(d, req, value1, index, शून्य, blen);
	अगर (ret != 0)
		warn("usb out operation failed. (%d)", ret);

	mutex_unlock(&state->ca_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक az6027_ci_पढ़ो_cam_control(काष्ठा dvb_ca_en50221 *ca,
				      पूर्णांक slot,
				      u8 address)
अणु
	काष्ठा dvb_usb_device *d = (काष्ठा dvb_usb_device *)ca->data;
	काष्ठा az6027_device_state *state = (काष्ठा az6027_device_state *)d->priv;

	पूर्णांक ret;
	u8 req;
	u16 value;
	u16 index;
	पूर्णांक blen;
	u8 *b;

	अगर (slot != 0)
		वापस -EINVAL;

	b = kदो_स्मृति(12, GFP_KERNEL);
	अगर (!b)
		वापस -ENOMEM;

	mutex_lock(&state->ca_mutex);

	req = 0xC3;
	value = address;
	index = 0;
	blen = 2;

	ret = az6027_usb_in_op(d, req, value, index, b, blen);
	अगर (ret < 0) अणु
		warn("usb in operation failed. (%d)", ret);
		ret = -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (b[0] == 0)
			warn("Read CI IO error");

		ret = b[1];
		deb_info("read cam data = %x from 0x%x", b[1], value);
	पूर्ण

	mutex_unlock(&state->ca_mutex);
	kमुक्त(b);
	वापस ret;
पूर्ण

अटल पूर्णांक az6027_ci_ग_लिखो_cam_control(काष्ठा dvb_ca_en50221 *ca,
				       पूर्णांक slot,
				       u8 address,
				       u8 value)
अणु
	काष्ठा dvb_usb_device *d = (काष्ठा dvb_usb_device *)ca->data;
	काष्ठा az6027_device_state *state = (काष्ठा az6027_device_state *)d->priv;

	पूर्णांक ret;
	u8 req;
	u16 value1;
	u16 index;
	पूर्णांक blen;

	अगर (slot != 0)
		वापस -EINVAL;

	mutex_lock(&state->ca_mutex);
	req = 0xC4;
	value1 = address;
	index = value;
	blen = 0;

	ret = az6027_usb_out_op(d, req, value1, index, शून्य, blen);
	अगर (ret != 0) अणु
		warn("usb out operation failed. (%d)", ret);
		जाओ failed;
	पूर्ण

failed:
	mutex_unlock(&state->ca_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक CI_CamReady(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot)
अणु
	काष्ठा dvb_usb_device *d = (काष्ठा dvb_usb_device *)ca->data;

	पूर्णांक ret;
	u8 req;
	u16 value;
	u16 index;
	पूर्णांक blen;
	u8 *b;

	b = kदो_स्मृति(12, GFP_KERNEL);
	अगर (!b)
		वापस -ENOMEM;

	req = 0xC8;
	value = 0;
	index = 0;
	blen = 1;

	ret = az6027_usb_in_op(d, req, value, index, b, blen);
	अगर (ret < 0) अणु
		warn("usb in operation failed. (%d)", ret);
		ret = -EIO;
	पूर्ण अन्यथाअणु
		ret = b[0];
	पूर्ण
	kमुक्त(b);
	वापस ret;
पूर्ण

अटल पूर्णांक az6027_ci_slot_reset(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot)
अणु
	काष्ठा dvb_usb_device *d = (काष्ठा dvb_usb_device *)ca->data;
	काष्ठा az6027_device_state *state = (काष्ठा az6027_device_state *)d->priv;

	पूर्णांक ret, i;
	u8 req;
	u16 value;
	u16 index;
	पूर्णांक blen;

	mutex_lock(&state->ca_mutex);

	req = 0xC6;
	value = 1;
	index = 0;
	blen = 0;

	ret = az6027_usb_out_op(d, req, value, index, शून्य, blen);
	अगर (ret != 0) अणु
		warn("usb out operation failed. (%d)", ret);
		जाओ failed;
	पूर्ण

	msleep(500);
	req = 0xC6;
	value = 0;
	index = 0;
	blen = 0;

	ret = az6027_usb_out_op(d, req, value, index, शून्य, blen);
	अगर (ret != 0) अणु
		warn("usb out operation failed. (%d)", ret);
		जाओ failed;
	पूर्ण

	क्रम (i = 0; i < 15; i++) अणु
		msleep(100);

		अगर (CI_CamReady(ca, slot)) अणु
			deb_info("CAM Ready");
			अवरोध;
		पूर्ण
	पूर्ण
	msleep(5000);

failed:
	mutex_unlock(&state->ca_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक az6027_ci_slot_shutकरोwn(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक az6027_ci_slot_ts_enable(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot)
अणु
	काष्ठा dvb_usb_device *d = (काष्ठा dvb_usb_device *)ca->data;
	काष्ठा az6027_device_state *state = (काष्ठा az6027_device_state *)d->priv;

	पूर्णांक ret;
	u8 req;
	u16 value;
	u16 index;
	पूर्णांक blen;

	deb_info("%s", __func__);
	mutex_lock(&state->ca_mutex);
	req = 0xC7;
	value = 1;
	index = 0;
	blen = 0;

	ret = az6027_usb_out_op(d, req, value, index, शून्य, blen);
	अगर (ret != 0) अणु
		warn("usb out operation failed. (%d)", ret);
		जाओ failed;
	पूर्ण

failed:
	mutex_unlock(&state->ca_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक az6027_ci_poll_slot_status(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot, पूर्णांक खोलो)
अणु
	काष्ठा dvb_usb_device *d = (काष्ठा dvb_usb_device *)ca->data;
	काष्ठा az6027_device_state *state = (काष्ठा az6027_device_state *)d->priv;
	पूर्णांक ret;
	u8 req;
	u16 value;
	u16 index;
	पूर्णांक blen;
	u8 *b;

	b = kदो_स्मृति(12, GFP_KERNEL);
	अगर (!b)
		वापस -ENOMEM;
	mutex_lock(&state->ca_mutex);

	req = 0xC5;
	value = 0;
	index = 0;
	blen = 1;

	ret = az6027_usb_in_op(d, req, value, index, b, blen);
	अगर (ret < 0) अणु
		warn("usb in operation failed. (%d)", ret);
		ret = -EIO;
	पूर्ण अन्यथा
		ret = 0;

	अगर (!ret && b[0] == 1) अणु
		ret = DVB_CA_EN50221_POLL_CAM_PRESENT |
		      DVB_CA_EN50221_POLL_CAM_READY;
	पूर्ण

	mutex_unlock(&state->ca_mutex);
	kमुक्त(b);
	वापस ret;
पूर्ण


अटल व्योम az6027_ci_uninit(काष्ठा dvb_usb_device *d)
अणु
	काष्ठा az6027_device_state *state;

	deb_info("%s", __func__);

	अगर (शून्य == d)
		वापस;

	state = (काष्ठा az6027_device_state *)d->priv;
	अगर (शून्य == state)
		वापस;

	अगर (शून्य == state->ca.data)
		वापस;

	dvb_ca_en50221_release(&state->ca);

	स_रखो(&state->ca, 0, माप(state->ca));
पूर्ण


अटल पूर्णांक az6027_ci_init(काष्ठा dvb_usb_adapter *a)
अणु
	काष्ठा dvb_usb_device *d = a->dev;
	काष्ठा az6027_device_state *state = (काष्ठा az6027_device_state *)d->priv;
	पूर्णांक ret;

	deb_info("%s", __func__);

	mutex_init(&state->ca_mutex);

	state->ca.owner			= THIS_MODULE;
	state->ca.पढ़ो_attribute_mem	= az6027_ci_पढ़ो_attribute_mem;
	state->ca.ग_लिखो_attribute_mem	= az6027_ci_ग_लिखो_attribute_mem;
	state->ca.पढ़ो_cam_control	= az6027_ci_पढ़ो_cam_control;
	state->ca.ग_लिखो_cam_control	= az6027_ci_ग_लिखो_cam_control;
	state->ca.slot_reset		= az6027_ci_slot_reset;
	state->ca.slot_shutकरोwn		= az6027_ci_slot_shutकरोwn;
	state->ca.slot_ts_enable	= az6027_ci_slot_ts_enable;
	state->ca.poll_slot_status	= az6027_ci_poll_slot_status;
	state->ca.data			= d;

	ret = dvb_ca_en50221_init(&a->dvb_adap,
				  &state->ca,
				  0, /* flags */
				  1);/* n_slots */
	अगर (ret != 0) अणु
		err("Cannot initialize CI: Error %d.", ret);
		स_रखो(&state->ca, 0, माप(state->ca));
		वापस ret;
	पूर्ण

	deb_info("CI initialized.");

	वापस 0;
पूर्ण

/*
अटल पूर्णांक az6027_पढ़ो_mac_addr(काष्ठा dvb_usb_device *d, u8 mac[6])
अणु
	az6027_usb_in_op(d, 0xb7, 6, 0, &mac[0], 6);
	वापस 0;
पूर्ण
*/

अटल पूर्णांक az6027_set_voltage(काष्ठा dvb_frontend *fe,
			      क्रमागत fe_sec_voltage voltage)
अणु

	u8 buf;
	काष्ठा dvb_usb_adapter *adap = fe->dvb->priv;

	काष्ठा i2c_msg i2c_msg = अणु
		.addr	= 0x99,
		.flags	= 0,
		.buf	= &buf,
		.len	= 1
	पूर्ण;

	/*
	 * 2   --18v
	 * 1   --13v
	 * 0   --off
	 */
	चयन (voltage) अणु
	हाल SEC_VOLTAGE_13:
		buf = 1;
		i2c_transfer(&adap->dev->i2c_adap, &i2c_msg, 1);
		अवरोध;

	हाल SEC_VOLTAGE_18:
		buf = 2;
		i2c_transfer(&adap->dev->i2c_adap, &i2c_msg, 1);
		अवरोध;

	हाल SEC_VOLTAGE_OFF:
		buf = 0;
		i2c_transfer(&adap->dev->i2c_adap, &i2c_msg, 1);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक az6027_frontend_घातeron(काष्ठा dvb_usb_adapter *adap)
अणु
	पूर्णांक ret;
	u8 req;
	u16 value;
	u16 index;
	पूर्णांक blen;

	req = 0xBC;
	value = 1; /* घातer on */
	index = 3;
	blen = 0;

	ret = az6027_usb_out_op(adap->dev, req, value, index, शून्य, blen);
	अगर (ret != 0)
		वापस -EIO;

	वापस 0;
पूर्ण
अटल पूर्णांक az6027_frontend_reset(काष्ठा dvb_usb_adapter *adap)
अणु
	पूर्णांक ret;
	u8 req;
	u16 value;
	u16 index;
	पूर्णांक blen;

	/* reset demodulator */
	req = 0xC0;
	value = 1; /* high */
	index = 3;
	blen = 0;

	ret = az6027_usb_out_op(adap->dev, req, value, index, शून्य, blen);
	अगर (ret != 0)
		वापस -EIO;

	req = 0xC0;
	value = 0; /* low */
	index = 3;
	blen = 0;
	msleep_पूर्णांकerruptible(200);

	ret = az6027_usb_out_op(adap->dev, req, value, index, शून्य, blen);
	अगर (ret != 0)
		वापस -EIO;

	msleep_पूर्णांकerruptible(200);

	req = 0xC0;
	value = 1; /*high */
	index = 3;
	blen = 0;

	ret = az6027_usb_out_op(adap->dev, req, value, index, शून्य, blen);
	अगर (ret != 0)
		वापस -EIO;

	msleep_पूर्णांकerruptible(200);
	वापस 0;
पूर्ण

अटल पूर्णांक az6027_frontend_tsbypass(काष्ठा dvb_usb_adapter *adap, पूर्णांक onoff)
अणु
	पूर्णांक ret;
	u8 req;
	u16 value;
	u16 index;
	पूर्णांक blen;

	/* TS passthrough */
	req = 0xC7;
	value = onoff;
	index = 0;
	blen = 0;

	ret = az6027_usb_out_op(adap->dev, req, value, index, शून्य, blen);
	अगर (ret != 0)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक az6027_frontend_attach(काष्ठा dvb_usb_adapter *adap)
अणु

	az6027_frontend_घातeron(adap);
	az6027_frontend_reset(adap);

	deb_info("adap = %p, dev = %p\n", adap, adap->dev);
	adap->fe_adap[0].fe = stb0899_attach(&az6027_stb0899_config, &adap->dev->i2c_adap);

	अगर (adap->fe_adap[0].fe) अणु
		deb_info("found STB0899 DVB-S/DVB-S2 frontend @0x%02x", az6027_stb0899_config.demod_address);
		अगर (stb6100_attach(adap->fe_adap[0].fe, &az6027_stb6100_config, &adap->dev->i2c_adap)) अणु
			deb_info("found STB6100 DVB-S/DVB-S2 frontend @0x%02x", az6027_stb6100_config.tuner_address);
			adap->fe_adap[0].fe->ops.set_voltage = az6027_set_voltage;
			az6027_ci_init(adap);
		पूर्ण अन्यथा अणु
			adap->fe_adap[0].fe = शून्य;
		पूर्ण
	पूर्ण अन्यथा
		warn("no front-end attached\n");

	az6027_frontend_tsbypass(adap, 0);

	वापस 0;
पूर्ण

अटल काष्ठा dvb_usb_device_properties az6027_properties;

अटल व्योम az6027_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा dvb_usb_device *d = usb_get_पूर्णांकfdata(पूर्णांकf);
	az6027_ci_uninit(d);
	dvb_usb_device_निकास(पूर्णांकf);
पूर्ण


अटल पूर्णांक az6027_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			    स्थिर काष्ठा usb_device_id *id)
अणु
	वापस dvb_usb_device_init(पूर्णांकf,
				   &az6027_properties,
				   THIS_MODULE,
				   शून्य,
				   adapter_nr);
पूर्ण

/* I2C */
अटल पूर्णांक az6027_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg msg[], पूर्णांक num)
अणु
	काष्ठा dvb_usb_device *d = i2c_get_adapdata(adap);
	पूर्णांक i = 0, j = 0, len = 0;
	u16 index;
	u16 value;
	पूर्णांक length;
	u8 req;
	u8 *data;

	data = kदो_स्मृति(256, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	अगर (mutex_lock_पूर्णांकerruptible(&d->i2c_mutex) < 0) अणु
		kमुक्त(data);
		वापस -EAGAIN;
	पूर्ण

	अगर (num > 2)
		warn("more than 2 i2c messages at a time is not handled yet. TODO.");

	क्रम (i = 0; i < num; i++) अणु

		अगर (msg[i].addr == 0x99) अणु
			req = 0xBE;
			index = 0;
			value = msg[i].buf[0] & 0x00ff;
			length = 1;
			az6027_usb_out_op(d, req, value, index, data, length);
		पूर्ण

		अगर (msg[i].addr == 0xd0) अणु
			/* ग_लिखो/पढ़ो request */
			अगर (i + 1 < num && (msg[i + 1].flags & I2C_M_RD)) अणु
				req = 0xB9;
				index = (((msg[i].buf[0] << 8) & 0xff00) | (msg[i].buf[1] & 0x00ff));
				value = msg[i].addr + (msg[i].len << 8);
				length = msg[i + 1].len + 6;
				az6027_usb_in_op(d, req, value, index, data, length);
				len = msg[i + 1].len;
				क्रम (j = 0; j < len; j++)
					msg[i + 1].buf[j] = data[j + 5];

				i++;
			पूर्ण अन्यथा अणु

				/* demod 16bit addr */
				req = 0xBD;
				index = (((msg[i].buf[0] << 8) & 0xff00) | (msg[i].buf[1] & 0x00ff));
				value = msg[i].addr + (2 << 8);
				length = msg[i].len - 2;
				len = msg[i].len - 2;
				क्रम (j = 0; j < len; j++)
					data[j] = msg[i].buf[j + 2];
				az6027_usb_out_op(d, req, value, index, data, length);
			पूर्ण
		पूर्ण

		अगर (msg[i].addr == 0xc0) अणु
			अगर (msg[i].flags & I2C_M_RD) अणु

				req = 0xB9;
				index = 0x0;
				value = msg[i].addr;
				length = msg[i].len + 6;
				az6027_usb_in_op(d, req, value, index, data, length);
				len = msg[i].len;
				क्रम (j = 0; j < len; j++)
					msg[i].buf[j] = data[j + 5];

			पूर्ण अन्यथा अणु

				req = 0xBD;
				index = msg[i].buf[0] & 0x00FF;
				value = msg[i].addr + (1 << 8);
				length = msg[i].len - 1;
				len = msg[i].len - 1;

				क्रम (j = 0; j < len; j++)
					data[j] = msg[i].buf[j + 1];

				az6027_usb_out_op(d, req, value, index, data, length);
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&d->i2c_mutex);
	kमुक्त(data);

	वापस i;
पूर्ण


अटल u32 az6027_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल काष्ठा i2c_algorithm az6027_i2c_algo = अणु
	.master_xfer   = az6027_i2c_xfer,
	.functionality = az6027_i2c_func,
पूर्ण;

अटल पूर्णांक az6027_identअगरy_state(काष्ठा usb_device *udev,
				 स्थिर काष्ठा dvb_usb_device_properties *props,
				 स्थिर काष्ठा dvb_usb_device_description **desc,
				 पूर्णांक *cold)
अणु
	u8 *b;
	s16 ret;

	b = kदो_स्मृति(16, GFP_KERNEL);
	अगर (!b)
		वापस -ENOMEM;

	ret = usb_control_msg(udev,
				  usb_rcvctrlpipe(udev, 0),
				  0xb7,
				  USB_TYPE_VENDOR | USB_सूची_IN,
				  6,
				  0,
				  b,
				  6,
				  USB_CTRL_GET_TIMEOUT);

	*cold = ret <= 0;
	kमुक्त(b);
	deb_info("cold: %d\n", *cold);
	वापस 0;
पूर्ण


अटल काष्ठा usb_device_id az6027_usb_table[] = अणु
	अणु USB_DEVICE(USB_VID_AZUREWAVE, USB_PID_AZUREWAVE_AZ6027) पूर्ण,
	अणु USB_DEVICE(USB_VID_TERRATEC,  USB_PID_TERRATEC_DVBS2CI_V1) पूर्ण,
	अणु USB_DEVICE(USB_VID_TERRATEC,  USB_PID_TERRATEC_DVBS2CI_V2) पूर्ण,
	अणु USB_DEVICE(USB_VID_TECHNISAT, USB_PID_TECHNISAT_USB2_HDCI_V1) पूर्ण,
	अणु USB_DEVICE(USB_VID_TECHNISAT, USB_PID_TECHNISAT_USB2_HDCI_V2) पूर्ण,
	अणु USB_DEVICE(USB_VID_ELGATO, USB_PID_ELGATO_EYETV_SAT) पूर्ण,
	अणु USB_DEVICE(USB_VID_ELGATO, USB_PID_ELGATO_EYETV_SAT_V2) पूर्ण,
	अणु USB_DEVICE(USB_VID_ELGATO, USB_PID_ELGATO_EYETV_SAT_V3) पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(usb, az6027_usb_table);

अटल काष्ठा dvb_usb_device_properties az6027_properties = अणु
	.caps = DVB_USB_IS_AN_I2C_ADAPTER,
	.usb_ctrl = CYPRESS_FX2,
	.firmware            = "dvb-usb-az6027-03.fw",
	.no_reconnect        = 1,

	.size_of_priv     = माप(काष्ठा az6027_device_state),
	.identअगरy_state		= az6027_identअगरy_state,
	.num_adapters = 1,
	.adapter = अणु
		अणु
		.num_frontends = 1,
		.fe = अणुअणु
			.streaming_ctrl   = az6027_streaming_ctrl,
			.frontend_attach  = az6027_frontend_attach,

			/* parameter क्रम the MPEG2-data transfer */
			.stream = अणु
				.type = USB_BULK,
				.count = 10,
				.endpoपूर्णांक = 0x02,
				.u = अणु
					.bulk = अणु
						.buffersize = 4096,
					पूर्ण
				पूर्ण
			पूर्ण,
		पूर्णपूर्ण,
		पूर्ण
	पूर्ण,
/*
	.घातer_ctrl       = az6027_घातer_ctrl,
	.पढ़ो_mac_address = az6027_पढ़ो_mac_addr,
 */
	.rc.legacy = अणु
		.rc_map_table     = rc_map_az6027_table,
		.rc_map_size      = ARRAY_SIZE(rc_map_az6027_table),
		.rc_पूर्णांकerval      = 400,
		.rc_query         = az6027_rc_query,
	पूर्ण,

	.i2c_algo         = &az6027_i2c_algo,

	.num_device_descs = 8,
	.devices = अणु
		अणु
			.name = "AZUREWAVE DVB-S/S2 USB2.0 (AZ6027)",
			.cold_ids = अणु &az6027_usb_table[0], शून्य पूर्ण,
			.warm_ids = अणु शून्य पूर्ण,
		पूर्ण, अणु
			.name = "TERRATEC S7",
			.cold_ids = अणु &az6027_usb_table[1], शून्य पूर्ण,
			.warm_ids = अणु शून्य पूर्ण,
		पूर्ण, अणु
			.name = "TERRATEC S7 MKII",
			.cold_ids = अणु &az6027_usb_table[2], शून्य पूर्ण,
			.warm_ids = अणु शून्य पूर्ण,
		पूर्ण, अणु
			.name = "Technisat SkyStar USB 2 HD CI",
			.cold_ids = अणु &az6027_usb_table[3], शून्य पूर्ण,
			.warm_ids = अणु शून्य पूर्ण,
		पूर्ण, अणु
			.name = "Technisat SkyStar USB 2 HD CI",
			.cold_ids = अणु &az6027_usb_table[4], शून्य पूर्ण,
			.warm_ids = अणु शून्य पूर्ण,
		पूर्ण, अणु
			.name = "Elgato EyeTV Sat",
			.cold_ids = अणु &az6027_usb_table[5], शून्य पूर्ण,
			.warm_ids = अणु शून्य पूर्ण,
		पूर्ण, अणु
			.name = "Elgato EyeTV Sat",
			.cold_ids = अणु &az6027_usb_table[6], शून्य पूर्ण,
			.warm_ids = अणु शून्य पूर्ण,
		पूर्ण, अणु
			.name = "Elgato EyeTV Sat",
			.cold_ids = अणु &az6027_usb_table[7], शून्य पूर्ण,
			.warm_ids = अणु शून्य पूर्ण,
		पूर्ण,
		अणु शून्य पूर्ण,
	पूर्ण
पूर्ण;

/* usb specअगरic object needed to रेजिस्टर this driver with the usb subप्रणाली */
अटल काष्ठा usb_driver az6027_usb_driver = अणु
	.name		= "dvb_usb_az6027",
	.probe		= az6027_usb_probe,
	.disconnect	= az6027_usb_disconnect,
	.id_table	= az6027_usb_table,
पूर्ण;

module_usb_driver(az6027_usb_driver);

MODULE_AUTHOR("Adams Xu <Adams.xu@azwave.com.cn>");
MODULE_DESCRIPTION("Driver for AZUREWAVE DVB-S/S2 USB2.0 (AZ6027)");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");
