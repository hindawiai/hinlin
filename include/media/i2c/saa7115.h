<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    saa7115.h - definition क्रम saa7111/3/4/5 inमाला_दो and frequency flags

    Copyright (C) 2006 Hans Verkuil (hverkuil@xs4all.nl)

*/

#अगर_अघोषित _SAA7115_H_
#घोषणा _SAA7115_H_

/* s_routing inमाला_दो, outमाला_दो, and config */

/* SAA7111/3/4/5 HW inमाला_दो */
#घोषणा SAA7115_COMPOSITE0 0
#घोषणा SAA7115_COMPOSITE1 1
#घोषणा SAA7115_COMPOSITE2 2
#घोषणा SAA7115_COMPOSITE3 3
#घोषणा SAA7115_COMPOSITE4 4 /* not available क्रम the saa7111/3 */
#घोषणा SAA7115_COMPOSITE5 5 /* not available क्रम the saa7111/3 */
#घोषणा SAA7115_SVIDEO0    6
#घोषणा SAA7115_SVIDEO1    7
#घोषणा SAA7115_SVIDEO2    8
#घोषणा SAA7115_SVIDEO3    9

/* outमाला_दो */
#घोषणा SAA7115_IPORT_ON	1
#घोषणा SAA7115_IPORT_OFF	0

/* SAA7111 specअगरic outमाला_दो. */
#घोषणा SAA7111_VBI_BYPASS	2
#घोषणा SAA7111_FMT_YUV422      0x00
#घोषणा SAA7111_FMT_RGB		0x40
#घोषणा SAA7111_FMT_CCIR	0x80
#घोषणा SAA7111_FMT_YUV411	0xc0

/* config flags */
/*
 * Register 0x85 should set bit 0 to 0 (it's 1 by शेष). This bit
 * controls the IDQ संकेत polarity which is set to 'inverted' अगर the bit
 * it 1 and to 'default' अगर it is 0.
 */
#घोषणा SAA7115_IDQ_IS_DEFAULT  (1 << 0)

/* s_crystal_freq values and flags */

/* SAA7115 v4l2_crystal_freq frequency values */
#घोषणा SAA7115_FREQ_32_11_MHZ  32110000   /* 32.11 MHz crystal, SAA7114/5 only */
#घोषणा SAA7115_FREQ_24_576_MHZ 24576000   /* 24.576 MHz crystal */

/* SAA7115 v4l2_crystal_freq audio घड़ी control flags */
#घोषणा SAA7115_FREQ_FL_UCGC         (1 << 0) /* SA 3A[7], UCGC, SAA7115 only */
#घोषणा SAA7115_FREQ_FL_CGCDIV       (1 << 1) /* SA 3A[6], CGCDIV, SAA7115 only */
#घोषणा SAA7115_FREQ_FL_APLL         (1 << 2) /* SA 3A[3], APLL, SAA7114/5 only */
#घोषणा SAA7115_FREQ_FL_DOUBLE_ASCLK (1 << 3) /* SA 39, LRDIV, SAA7114/5 only */

/* ===== SAA7113 Config क्रमागतs ===== */

/* Register 0x08 "Horizontal time constant" [Bit 3..4]:
 * Should be set to "Fast Locking Mode" according to the datasheet,
 * and that is the शेष setting in the gm7113c_init table.
 * saa7113_init sets this value to "VTR Mode". */
क्रमागत saa7113_r08_htc अणु
	SAA7113_HTC_TV_MODE = 0x00,
	SAA7113_HTC_VTR_MODE,			/* Default क्रम saa7113_init */
	SAA7113_HTC_FAST_LOCKING_MODE = 0x03	/* Default क्रम gm7113c_init */
पूर्ण;

/* Register 0x10 "Output format selection" [Bit 6..7]:
 * Defaults to ITU_656 as specअगरied in datasheet. */
क्रमागत saa7113_r10_ofts अणु
	SAA7113_OFTS_ITU_656 = 0x0,	/* Default */
	SAA7113_OFTS_VFLAG_BY_VREF,
	SAA7113_OFTS_VFLAG_BY_DATA_TYPE
पूर्ण;

/*
 * Register 0x12 "Output control" [Bit 0..3 Or Bit 4..7]:
 * This is used to select what data is output on the RTS0 and RTS1 pins.
 * RTS1 [Bit 4..7] Defaults to DOT_IN. (This value can not be set क्रम RTS0)
 * RTS0 [Bit 0..3] Defaults to VIPB in gm7113c_init as specअगरied
 * in the datasheet, but is set to HREF_HS in the saa7113_init table.
 */
क्रमागत saa7113_r12_rts अणु
	SAA7113_RTS_DOT_IN = 0,		/* OBS: Only क्रम RTS1 (Default RTS1) */
	SAA7113_RTS_VIPB,		/* Default RTS0 For gm7113c_init */
	SAA7113_RTS_GPSW,
	SAA7115_RTS_HL,
	SAA7113_RTS_VL,
	SAA7113_RTS_DL,
	SAA7113_RTS_PLIN,
	SAA7113_RTS_HREF_HS,		/* Default RTS0 For saa7113_init */
	SAA7113_RTS_HS,
	SAA7113_RTS_HQ,
	SAA7113_RTS_ODD,
	SAA7113_RTS_VS,
	SAA7113_RTS_V123,
	SAA7113_RTS_VGATE,
	SAA7113_RTS_VREF,
	SAA7113_RTS_FID
पूर्ण;

/**
 * काष्ठा saa7115_platक्रमm_data - Allow overriding शेष initialization
 *
 * @saa7113_क्रमce_gm7113c_init:	Force the use of the gm7113c_init table
 *				instead of saa7113_init table
 *				(saa7113 only)
 * @saa7113_r08_htc:		[R_08 - Bit 3..4]
 * @saa7113_r10_vrln:		[R_10 - Bit 3]
 *				शेष: Disabled क्रम gm7113c_init
 *					 Enabled क्रम saa7113c_init
 * @saa7113_r10_ofts:		[R_10 - Bit 6..7]
 * @saa7113_r12_rts0:		[R_12 - Bit 0..3]
 * @saa7113_r12_rts1:		[R_12 - Bit 4..7]
 * @saa7113_r13_adlsb:		[R_13 - Bit 7] - शेष: disabled
 */
काष्ठा saa7115_platक्रमm_data अणु
	bool saa7113_क्रमce_gm7113c_init;
	क्रमागत saa7113_r08_htc *saa7113_r08_htc;
	bool *saa7113_r10_vrln;
	क्रमागत saa7113_r10_ofts *saa7113_r10_ofts;
	क्रमागत saa7113_r12_rts *saa7113_r12_rts0;
	क्रमागत saa7113_r12_rts *saa7113_r12_rts1;
	bool *saa7113_r13_adlsb;
पूर्ण;

#पूर्ण_अगर
