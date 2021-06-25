<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	STB0899 Multistandard Frontend driver
	Copyright (C) Manu Abraham (abraham.manu@gmail.com)

	Copyright (C) ST Microelectronics

*/

#अगर_अघोषित __STB0899_PRIV_H
#घोषणा __STB0899_PRIV_H

#समावेश <media/dvb_frontend.h>
#समावेश "stb0899_drv.h"

#घोषणा FE_ERROR				0
#घोषणा FE_NOTICE				1
#घोषणा FE_INFO					2
#घोषणा FE_DEBUG				3
#घोषणा FE_DEBUGREG				4

#घोषणा dprपूर्णांकk(x, y, z, क्रमmat, arg...) करो अणु						\
	अगर (z) अणु									\
		अगर	((*x > FE_ERROR) && (*x > y))					\
			prपूर्णांकk(KERN_ERR "%s: " क्रमmat "\n", __func__ , ##arg);		\
		अन्यथा अगर	((*x > FE_NOTICE) && (*x > y))					\
			prपूर्णांकk(KERN_NOTICE "%s: " क्रमmat "\n", __func__ , ##arg);	\
		अन्यथा अगर ((*x > FE_INFO) && (*x > y))					\
			prपूर्णांकk(KERN_INFO "%s: " क्रमmat "\n", __func__ , ##arg);		\
		अन्यथा अगर ((*x > FE_DEBUG) && (*x > y))					\
			prपूर्णांकk(KERN_DEBUG "%s: " क्रमmat "\n", __func__ , ##arg);	\
	पूर्ण अन्यथा अणु									\
		अगर (*x > y)								\
			prपूर्णांकk(क्रमmat, ##arg);						\
	पूर्ण										\
पूर्ण जबतक(0)

#घोषणा INRANGE(val, x, y)			(((x <= val) && (val <= y)) ||		\
						 ((y <= val) && (val <= x)) ? 1 : 0)

#घोषणा BYTE0					0
#घोषणा BYTE1					8
#घोषणा BYTE2					16
#घोषणा BYTE3					24

#घोषणा GETBYTE(x, y)				(((x) >> (y)) & 0xff)
#घोषणा MAKEWORD32(a, b, c, d)			(((a) << 24) | ((b) << 16) | ((c) << 8) | (d))
#घोषणा MAKEWORD16(a, b)			(((a) << 8) | (b))

#घोषणा LSB(x)					((x & 0xff))
#घोषणा MSB(y)					((y >> 8) & 0xff)


#घोषणा STB0899_GETFIELD(bitf, val)		((val >> STB0899_OFFST_##bitf) & ((1 << STB0899_WIDTH_##bitf) - 1))


#घोषणा STB0899_SETFIELD(mask, val, width, offset)      (mask & (~(((1 << width) - 1) <<	\
							 offset))) | ((val &			\
							 ((1 << width) - 1)) << offset)

#घोषणा STB0899_SETFIELD_VAL(bitf, mask, val)	(mask = (mask & (~(((1 << STB0899_WIDTH_##bitf) - 1) <<\
							 STB0899_OFFST_##bitf))) | \
							 (val << STB0899_OFFST_##bitf))


क्रमागत stb0899_status अणु
	NOAGC1	= 0,
	AGC1OK,
	NOTIMING,
	ANALOGCARRIER,
	TIMINGOK,
	NOAGC2,
	AGC2OK,
	NOCARRIER,
	CARRIEROK,
	NODATA,
	FALSELOCK,
	DATAOK,
	OUTOFRANGE,
	RANGEOK,
	DVBS2_DEMOD_LOCK,
	DVBS2_DEMOD_NOLOCK,
	DVBS2_FEC_LOCK,
	DVBS2_FEC_NOLOCK
पूर्ण;

क्रमागत stb0899_modcod अणु
	STB0899_DUMMY_PLF,
	STB0899_QPSK_14,
	STB0899_QPSK_13,
	STB0899_QPSK_25,
	STB0899_QPSK_12,
	STB0899_QPSK_35,
	STB0899_QPSK_23,
	STB0899_QPSK_34,
	STB0899_QPSK_45,
	STB0899_QPSK_56,
	STB0899_QPSK_89,
	STB0899_QPSK_910,
	STB0899_8PSK_35,
	STB0899_8PSK_23,
	STB0899_8PSK_34,
	STB0899_8PSK_56,
	STB0899_8PSK_89,
	STB0899_8PSK_910,
	STB0899_16APSK_23,
	STB0899_16APSK_34,
	STB0899_16APSK_45,
	STB0899_16APSK_56,
	STB0899_16APSK_89,
	STB0899_16APSK_910,
	STB0899_32APSK_34,
	STB0899_32APSK_45,
	STB0899_32APSK_56,
	STB0899_32APSK_89,
	STB0899_32APSK_910
पूर्ण;

क्रमागत stb0899_frame अणु
	STB0899_LONG_FRAME,
	STB0899_SHORT_FRAME
पूर्ण;

क्रमागत stb0899_alpha अणु
	RRC_20,
	RRC_25,
	RRC_35
पूर्ण;

काष्ठा stb0899_tab अणु
	s32 real;
	s32 पढ़ो;
पूर्ण;

क्रमागत stb0899_fec अणु
	STB0899_FEC_1_2			= 13,
	STB0899_FEC_2_3			= 18,
	STB0899_FEC_3_4			= 21,
	STB0899_FEC_5_6			= 24,
	STB0899_FEC_6_7			= 25,
	STB0899_FEC_7_8			= 26
पूर्ण;

काष्ठा stb0899_params अणु
	u32	freq;					/* Frequency	*/
	u32	srate;					/* Symbol rate	*/
	क्रमागत fe_code_rate fecrate;
पूर्ण;

काष्ठा stb0899_पूर्णांकernal अणु
	u32			master_clk;
	u32			freq;			/* Demod पूर्णांकernal Frequency		*/
	u32			srate;			/* Demod पूर्णांकernal Symbol rate		*/
	क्रमागत stb0899_fec	fecrate;		/* Demod पूर्णांकernal FEC rate		*/
	s32			srch_range;		/* Demod पूर्णांकernal Search Range		*/
	s32			sub_range;		/* Demod current sub range (Hz)		*/
	s32			tuner_step;		/* Tuner step (Hz)			*/
	s32			tuner_offst;		/* Relative offset to carrier (Hz)	*/
	u32			tuner_bw;		/* Current bandwidth of the tuner (Hz)	*/

	s32			mclk;			/* Masterघड़ी Divider factor (binary)	*/
	s32			rolloff;		/* Current RollOff of the filter (x100)	*/

	s16			derot_freq;		/* Current derotator frequency (Hz)	*/
	s16			derot_percent;

	s16			direction;		/* Current derotator search direction	*/
	s16			derot_step;		/* Derotator step (binary value)	*/
	s16			t_derot;		/* Derotator समय स्थिरant (ms)		*/
	s16			t_data;			/* Data recovery समय स्थिरant (ms)	*/
	s16			sub_dir;		/* Direction of the next sub range	*/

	s16			t_agc1;			/* Agc1 समय स्थिरant (ms)		*/
	s16			t_agc2;			/* Agc2 समय स्थिरant (ms)		*/

	u32			lock;			/* Demod पूर्णांकernal lock state		*/
	क्रमागत stb0899_status	status;			/* Demod पूर्णांकernal status		*/

	/* DVB-S2 */
	s32			agc_gain;		/* RF AGC Gain				*/
	s32			center_freq;		/* Nominal carrier frequency		*/
	s32			av_frame_coarse;	/* Coarse carrier freq search frames	*/
	s32			av_frame_fine;		/* Fine carrier freq search frames	*/

	s16			step_size;		/* Carrier frequency search step size	*/

	क्रमागत stb0899_alpha	rrc_alpha;
	क्रमागत stb0899_inversion	inversion;
	क्रमागत stb0899_modcod	modcod;
	u8			pilots;			/* Pilots found				*/

	क्रमागत stb0899_frame	frame_length;
	u8			v_status;		/* VSTATUS				*/
	u8			err_ctrl;		/* ERRCTRLn				*/
पूर्ण;

काष्ठा stb0899_state अणु
	काष्ठा i2c_adapter		*i2c;
	काष्ठा stb0899_config		*config;
	काष्ठा dvb_frontend		frontend;

	u32				*verbose;	/* Cached module verbosity level	*/

	काष्ठा stb0899_पूर्णांकernal		पूर्णांकernal;	/* Device पूर्णांकernal parameters		*/

	/*	cached params from API	*/
	क्रमागत fe_delivery_प्रणाली		delsys;
	काष्ठा stb0899_params		params;

	u32				rx_freq;	/* DiSEqC 2.0 receiver freq		*/
	काष्ठा mutex			search_lock;
पूर्ण;
/* stb0899.c		*/
बाह्य पूर्णांक stb0899_पढ़ो_reg(काष्ठा stb0899_state *state,
			    अचिन्हित पूर्णांक reg);

बाह्य u32 _stb0899_पढ़ो_s2reg(काष्ठा stb0899_state *state,
			       u32 stb0899_i2cdev,
			       u32 stb0899_base_addr,
			       u16 stb0899_reg_offset);

बाह्य पूर्णांक stb0899_पढ़ो_regs(काष्ठा stb0899_state *state,
			     अचिन्हित पूर्णांक reg, u8 *buf,
			     u32 count);

बाह्य पूर्णांक stb0899_ग_लिखो_regs(काष्ठा stb0899_state *state,
			      अचिन्हित पूर्णांक reg, u8 *data,
			      u32 count);

बाह्य पूर्णांक stb0899_ग_लिखो_reg(काष्ठा stb0899_state *state,
			     अचिन्हित पूर्णांक reg,
			     u8 data);

बाह्य पूर्णांक stb0899_ग_लिखो_s2reg(काष्ठा stb0899_state *state,
			       u32 stb0899_i2cdev,
			       u32 stb0899_base_addr,
			       u16 stb0899_reg_offset,
			       u32 stb0899_data);

बाह्य पूर्णांक stb0899_i2c_gate_ctrl(काष्ठा dvb_frontend *fe, पूर्णांक enable);


#घोषणा STB0899_READ_S2REG(DEVICE, REG)		(_stb0899_पढ़ो_s2reg(state, DEVICE, STB0899_BASE_##REG, STB0899_OFF0_##REG))
//#घोषणा STB0899_WRITE_S2REG(DEVICE, REG, DATA)	(_stb0899_ग_लिखो_s2reg(state, DEVICE, STB0899_BASE_##REG, STB0899_OFF0_##REG, DATA))

/* stb0899_algo.c	*/
बाह्य क्रमागत stb0899_status stb0899_dvbs_algo(काष्ठा stb0899_state *state);
बाह्य क्रमागत stb0899_status stb0899_dvbs2_algo(काष्ठा stb0899_state *state);
बाह्य दीर्घ stb0899_carr_width(काष्ठा stb0899_state *state);

#पूर्ण_अगर //__STB0899_PRIV_H
