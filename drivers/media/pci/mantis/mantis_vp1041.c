<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
	Mantis VP-1041 driver

	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

*/

#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <media/dmxdev.h>
#समावेश <media/dvbdev.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_net.h>

#समावेश "mantis_common.h"
#समावेश "mantis_ioc.h"
#समावेश "mantis_dvb.h"
#समावेश "mantis_vp1041.h"
#समावेश "stb0899_reg.h"
#समावेश "stb0899_drv.h"
#समावेश "stb0899_cfg.h"
#समावेश "stb6100_cfg.h"
#समावेश "stb6100.h"
#समावेश "lnbp21.h"

#घोषणा MANTIS_MODEL_NAME	"VP-1041"
#घोषणा MANTIS_DEV_TYPE		"DSS/DVB-S/DVB-S2"

अटल स्थिर काष्ठा stb0899_s1_reg vp1041_stb0899_s1_init_1[] = अणु

	/* 0x0000000b, *//* SYSREG */
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

अटल स्थिर काष्ठा stb0899_s1_reg vp1041_stb0899_s1_init_3[] = अणु
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

अटल काष्ठा stb0899_config vp1041_stb0899_config = अणु
	.init_dev		= vp1041_stb0899_s1_init_1,
	.init_s2_demod		= stb0899_s2_init_2,
	.init_s1_demod		= vp1041_stb0899_s1_init_3,
	.init_s2_fec		= stb0899_s2_init_4,
	.init_tst		= stb0899_s1_init_5,

	.demod_address		= 0x68, /*  0xd0 >> 1 */

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

अटल काष्ठा stb6100_config vp1041_stb6100_config = अणु
	.tuner_address	= 0x60,
	.refघड़ी	= 27000000,
पूर्ण;

अटल पूर्णांक vp1041_frontend_init(काष्ठा mantis_pci *mantis, काष्ठा dvb_frontend *fe)
अणु
	काष्ठा i2c_adapter *adapter	= &mantis->adapter;

	पूर्णांक err = 0;

	err = mantis_frontend_घातer(mantis, POWER_ON);
	अगर (err == 0) अणु
		mantis_frontend_soft_reset(mantis);
		msleep(250);
		mantis->fe = dvb_attach(stb0899_attach, &vp1041_stb0899_config, adapter);
		अगर (mantis->fe) अणु
			dprपूर्णांकk(MANTIS_ERROR, 1,
				"found STB0899 DVB-S/DVB-S2 frontend @0x%02x",
				vp1041_stb0899_config.demod_address);

			अगर (dvb_attach(stb6100_attach, mantis->fe, &vp1041_stb6100_config, adapter)) अणु
				अगर (!dvb_attach(lnbp21_attach, mantis->fe, adapter, 0, 0))
					dprपूर्णांकk(MANTIS_ERROR, 1, "No LNBP21 found!");
			पूर्ण
		पूर्ण अन्यथा अणु
			वापस -EREMOTEIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		dprपूर्णांकk(MANTIS_ERROR, 1, "Frontend on <%s> POWER ON failed! <%d>",
			adapter->name,
			err);

		वापस -EIO;
	पूर्ण


	dprपूर्णांकk(MANTIS_ERROR, 1, "Done!");

	वापस 0;
पूर्ण

काष्ठा mantis_hwconfig vp1041_config = अणु
	.model_name	= MANTIS_MODEL_NAME,
	.dev_type	= MANTIS_DEV_TYPE,
	.ts_size	= MANTIS_TS_188,

	.baud_rate	= MANTIS_BAUD_9600,
	.parity		= MANTIS_PARITY_NONE,
	.bytes		= 0,

	.frontend_init	= vp1041_frontend_init,
	.घातer		= GPIF_A12,
	.reset		= GPIF_A13,
पूर्ण;
