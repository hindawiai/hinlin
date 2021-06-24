<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  cx18 ADEC header
 *
 *  Derived from cx25840-core.h
 *
 *  Copyright (C) 2007  Hans Verkuil <hverkuil@xs4all.nl>
 *  Copyright (C) 2008  Andy Walls <awalls@md.metrocast.net>
 */

#अगर_अघोषित _CX18_AV_CORE_H_
#घोषणा _CX18_AV_CORE_H_

#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>

काष्ठा cx18;

क्रमागत cx18_av_video_input अणु
	/* Composite video inमाला_दो In1-In8 */
	CX18_AV_COMPOSITE1 = 1,
	CX18_AV_COMPOSITE2,
	CX18_AV_COMPOSITE3,
	CX18_AV_COMPOSITE4,
	CX18_AV_COMPOSITE5,
	CX18_AV_COMPOSITE6,
	CX18_AV_COMPOSITE7,
	CX18_AV_COMPOSITE8,

	/* S-Video inमाला_दो consist of one luma input (In1-In8) ORed with one
	   chroma input (In5-In8) */
	CX18_AV_SVIDEO_LUMA1 = 0x10,
	CX18_AV_SVIDEO_LUMA2 = 0x20,
	CX18_AV_SVIDEO_LUMA3 = 0x30,
	CX18_AV_SVIDEO_LUMA4 = 0x40,
	CX18_AV_SVIDEO_LUMA5 = 0x50,
	CX18_AV_SVIDEO_LUMA6 = 0x60,
	CX18_AV_SVIDEO_LUMA7 = 0x70,
	CX18_AV_SVIDEO_LUMA8 = 0x80,
	CX18_AV_SVIDEO_CHROMA4 = 0x400,
	CX18_AV_SVIDEO_CHROMA5 = 0x500,
	CX18_AV_SVIDEO_CHROMA6 = 0x600,
	CX18_AV_SVIDEO_CHROMA7 = 0x700,
	CX18_AV_SVIDEO_CHROMA8 = 0x800,

	/* S-Video aliases क्रम common luma/chroma combinations */
	CX18_AV_SVIDEO1 = 0x510,
	CX18_AV_SVIDEO2 = 0x620,
	CX18_AV_SVIDEO3 = 0x730,
	CX18_AV_SVIDEO4 = 0x840,

	/* Component Video inमाला_दो consist of one luma input (In1-In8) ORed
	   with a red chroma (In4-In6) and blue chroma input (In7-In8) */
	CX18_AV_COMPONENT_LUMA1 = 0x1000,
	CX18_AV_COMPONENT_LUMA2 = 0x2000,
	CX18_AV_COMPONENT_LUMA3 = 0x3000,
	CX18_AV_COMPONENT_LUMA4 = 0x4000,
	CX18_AV_COMPONENT_LUMA5 = 0x5000,
	CX18_AV_COMPONENT_LUMA6 = 0x6000,
	CX18_AV_COMPONENT_LUMA7 = 0x7000,
	CX18_AV_COMPONENT_LUMA8 = 0x8000,
	CX18_AV_COMPONENT_R_CHROMA4 = 0x40000,
	CX18_AV_COMPONENT_R_CHROMA5 = 0x50000,
	CX18_AV_COMPONENT_R_CHROMA6 = 0x60000,
	CX18_AV_COMPONENT_B_CHROMA7 = 0x700000,
	CX18_AV_COMPONENT_B_CHROMA8 = 0x800000,

	/* Component Video aliases क्रम common combinations */
	CX18_AV_COMPONENT1 = 0x861000,
पूर्ण;

क्रमागत cx18_av_audio_input अणु
	/* Audio inमाला_दो: serial or In4-In8 */
	CX18_AV_AUDIO_SERIAL1,
	CX18_AV_AUDIO_SERIAL2,
	CX18_AV_AUDIO4 = 4,
	CX18_AV_AUDIO5,
	CX18_AV_AUDIO6,
	CX18_AV_AUDIO7,
	CX18_AV_AUDIO8,
पूर्ण;

काष्ठा cx18_av_state अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा v4l2_ctrl_handler hdl;
	काष्ठा v4l2_ctrl *volume;
	पूर्णांक radio;
	v4l2_std_id std;
	क्रमागत cx18_av_video_input vid_input;
	क्रमागत cx18_av_audio_input aud_input;
	u32 audclk_freq;
	पूर्णांक audmode;
	u32 rev;
	पूर्णांक is_initialized;

	/*
	 * The VBI slicer starts operating and counting lines, beginning at
	 * slicer line count of 1, at D lines after the deनिश्चितion of VRESET.
	 * This staring field line, S, is 6 (& 319) or 10 (& 273) क्रम 625 or 525
	 * line प्रणालीs respectively.  Sliced ancillary data captured on VBI
	 * slicer line M is inserted after the VBI slicer is करोne with line M,
	 * when VBI slicer line count is N = M+1.  Thus when the VBI slicer
	 * reports a VBI slicer line number with ancillary data, the IDID0 byte
	 * indicates VBI slicer line N.  The actual field line that the captured
	 * data comes from is
	 *
	 * L = M+(S+D-1) = N-1+(S+D-1) = N + (S+D-2).
	 *
	 * L is the line in the field, not frame, from which the VBI data came.
	 * N is the line reported by the slicer in the ancillary data.
	 * D is the slicer_line_delay value programmed पूर्णांकo रेजिस्टर 0x47f.
	 * S is 6 क्रम 625 line प्रणालीs or 10 क्रम 525 line प्रणालीs
	 * (S+D-2) is the slicer_line_offset used to convert slicer reported
	 * line counts to actual field lines.
	 */
	पूर्णांक slicer_line_delay;
	पूर्णांक slicer_line_offset;
पूर्ण;


/* Registers */
#घोषणा CXADEC_CHIP_TYPE_TIGER     0x837
#घोषणा CXADEC_CHIP_TYPE_MAKO      0x843

#घोषणा CXADEC_HOST_REG1           0x000
#घोषणा CXADEC_HOST_REG2           0x001

#घोषणा CXADEC_CHIP_CTRL           0x100
#घोषणा CXADEC_AFE_CTRL            0x104
#घोषणा CXADEC_PLL_CTRL1           0x108
#घोषणा CXADEC_VID_PLL_FRAC        0x10C
#घोषणा CXADEC_AUX_PLL_FRAC        0x110
#घोषणा CXADEC_PIN_CTRL1           0x114
#घोषणा CXADEC_PIN_CTRL2           0x118
#घोषणा CXADEC_PIN_CFG1            0x11C
#घोषणा CXADEC_PIN_CFG2            0x120

#घोषणा CXADEC_PIN_CFG3            0x124
#घोषणा CXADEC_I2S_MCLK            0x127

#घोषणा CXADEC_AUD_LOCK1           0x128
#घोषणा CXADEC_AUD_LOCK2           0x12C
#घोषणा CXADEC_POWER_CTRL          0x130
#घोषणा CXADEC_AFE_DIAG_CTRL1      0x134
#घोषणा CXADEC_AFE_DIAG_CTRL2      0x138
#घोषणा CXADEC_AFE_DIAG_CTRL3      0x13C
#घोषणा CXADEC_PLL_DIAG_CTRL       0x140
#घोषणा CXADEC_TEST_CTRL1          0x144
#घोषणा CXADEC_TEST_CTRL2          0x148
#घोषणा CXADEC_BIST_STAT           0x14C
#घोषणा CXADEC_DLL1_DIAG_CTRL      0x158
#घोषणा CXADEC_DLL2_DIAG_CTRL      0x15C

/* IR रेजिस्टरs */
#घोषणा CXADEC_IR_CTRL_REG         0x200
#घोषणा CXADEC_IR_TXCLK_REG        0x204
#घोषणा CXADEC_IR_RXCLK_REG        0x208
#घोषणा CXADEC_IR_CDUTY_REG        0x20C
#घोषणा CXADEC_IR_STAT_REG         0x210
#घोषणा CXADEC_IR_IRQEN_REG        0x214
#घोषणा CXADEC_IR_FILTER_REG       0x218
#घोषणा CXADEC_IR_FIFO_REG         0x21C

/* Video Registers */
#घोषणा CXADEC_MODE_CTRL           0x400
#घोषणा CXADEC_OUT_CTRL1           0x404
#घोषणा CXADEC_OUT_CTRL2           0x408
#घोषणा CXADEC_GEN_STAT            0x40C
#घोषणा CXADEC_INT_STAT_MASK       0x410
#घोषणा CXADEC_LUMA_CTRL           0x414

#घोषणा CXADEC_BRIGHTNESS_CTRL_BYTE 0x414
#घोषणा CXADEC_CONTRAST_CTRL_BYTE  0x415
#घोषणा CXADEC_LUMA_CTRL_BYTE_3    0x416

#घोषणा CXADEC_HSCALE_CTRL         0x418
#घोषणा CXADEC_VSCALE_CTRL         0x41C

#घोषणा CXADEC_CHROMA_CTRL         0x420

#घोषणा CXADEC_USAT_CTRL_BYTE      0x420
#घोषणा CXADEC_VSAT_CTRL_BYTE      0x421
#घोषणा CXADEC_HUE_CTRL_BYTE       0x422

#घोषणा CXADEC_VBI_LINE_CTRL1      0x424
#घोषणा CXADEC_VBI_LINE_CTRL2      0x428
#घोषणा CXADEC_VBI_LINE_CTRL3      0x42C
#घोषणा CXADEC_VBI_LINE_CTRL4      0x430
#घोषणा CXADEC_VBI_LINE_CTRL5      0x434
#घोषणा CXADEC_VBI_FC_CFG          0x438
#घोषणा CXADEC_VBI_MISC_CFG1       0x43C
#घोषणा CXADEC_VBI_MISC_CFG2       0x440
#घोषणा CXADEC_VBI_PAY1            0x444
#घोषणा CXADEC_VBI_PAY2            0x448
#घोषणा CXADEC_VBI_CUST1_CFG1      0x44C
#घोषणा CXADEC_VBI_CUST1_CFG2      0x450
#घोषणा CXADEC_VBI_CUST1_CFG3      0x454
#घोषणा CXADEC_VBI_CUST2_CFG1      0x458
#घोषणा CXADEC_VBI_CUST2_CFG2      0x45C
#घोषणा CXADEC_VBI_CUST2_CFG3      0x460
#घोषणा CXADEC_VBI_CUST3_CFG1      0x464
#घोषणा CXADEC_VBI_CUST3_CFG2      0x468
#घोषणा CXADEC_VBI_CUST3_CFG3      0x46C
#घोषणा CXADEC_HORIZ_TIM_CTRL      0x470
#घोषणा CXADEC_VERT_TIM_CTRL       0x474
#घोषणा CXADEC_SRC_COMB_CFG        0x478
#घोषणा CXADEC_CHROMA_VBIOFF_CFG   0x47C
#घोषणा CXADEC_FIELD_COUNT         0x480
#घोषणा CXADEC_MISC_TIM_CTRL       0x484
#घोषणा CXADEC_DFE_CTRL1           0x488
#घोषणा CXADEC_DFE_CTRL2           0x48C
#घोषणा CXADEC_DFE_CTRL3           0x490
#घोषणा CXADEC_PLL_CTRL2           0x494
#घोषणा CXADEC_HTL_CTRL            0x498
#घोषणा CXADEC_COMB_CTRL           0x49C
#घोषणा CXADEC_CRUSH_CTRL          0x4A0
#घोषणा CXADEC_SOFT_RST_CTRL       0x4A4
#घोषणा CXADEC_MV_DT_CTRL2         0x4A8
#घोषणा CXADEC_MV_DT_CTRL3         0x4AC
#घोषणा CXADEC_MISC_DIAG_CTRL      0x4B8

#घोषणा CXADEC_DL_CTL              0x800
#घोषणा CXADEC_DL_CTL_ADDRESS_LOW  0x800   /* Byte 1 in DL_CTL */
#घोषणा CXADEC_DL_CTL_ADDRESS_HIGH 0x801   /* Byte 2 in DL_CTL */
#घोषणा CXADEC_DL_CTL_DATA         0x802   /* Byte 3 in DL_CTL */
#घोषणा CXADEC_DL_CTL_CONTROL      0x803   /* Byte 4 in DL_CTL */

#घोषणा CXADEC_STD_DET_STATUS      0x804

#घोषणा CXADEC_STD_DET_CTL         0x808
#घोषणा CXADEC_STD_DET_CTL_AUD_CTL   0x808 /* Byte 1 in STD_DET_CTL */
#घोषणा CXADEC_STD_DET_CTL_PREF_MODE 0x809 /* Byte 2 in STD_DET_CTL */

#घोषणा CXADEC_DW8051_INT          0x80C
#घोषणा CXADEC_GENERAL_CTL         0x810
#घोषणा CXADEC_AAGC_CTL            0x814
#घोषणा CXADEC_IF_SRC_CTL          0x818
#घोषणा CXADEC_ANLOG_DEMOD_CTL     0x81C
#घोषणा CXADEC_ROT_FREQ_CTL        0x820
#घोषणा CXADEC_FM1_CTL             0x824
#घोषणा CXADEC_PDF_CTL             0x828
#घोषणा CXADEC_DFT1_CTL1           0x82C
#घोषणा CXADEC_DFT1_CTL2           0x830
#घोषणा CXADEC_DFT_STATUS          0x834
#घोषणा CXADEC_DFT2_CTL1           0x838
#घोषणा CXADEC_DFT2_CTL2           0x83C
#घोषणा CXADEC_DFT2_STATUS         0x840
#घोषणा CXADEC_DFT3_CTL1           0x844
#घोषणा CXADEC_DFT3_CTL2           0x848
#घोषणा CXADEC_DFT3_STATUS         0x84C
#घोषणा CXADEC_DFT4_CTL1           0x850
#घोषणा CXADEC_DFT4_CTL2           0x854
#घोषणा CXADEC_DFT4_STATUS         0x858
#घोषणा CXADEC_AM_MTS_DET          0x85C
#घोषणा CXADEC_ANALOG_MUX_CTL      0x860
#घोषणा CXADEC_DIG_PLL_CTL1        0x864
#घोषणा CXADEC_DIG_PLL_CTL2        0x868
#घोषणा CXADEC_DIG_PLL_CTL3        0x86C
#घोषणा CXADEC_DIG_PLL_CTL4        0x870
#घोषणा CXADEC_DIG_PLL_CTL5        0x874
#घोषणा CXADEC_DEEMPH_GAIN_CTL     0x878
#घोषणा CXADEC_DEEMPH_COEF1        0x87C
#घोषणा CXADEC_DEEMPH_COEF2        0x880
#घोषणा CXADEC_DBX1_CTL1           0x884
#घोषणा CXADEC_DBX1_CTL2           0x888
#घोषणा CXADEC_DBX1_STATUS         0x88C
#घोषणा CXADEC_DBX2_CTL1           0x890
#घोषणा CXADEC_DBX2_CTL2           0x894
#घोषणा CXADEC_DBX2_STATUS         0x898
#घोषणा CXADEC_AM_FM_DIFF          0x89C

/* NICAM रेजिस्टरs go here */
#घोषणा CXADEC_NICAM_STATUS        0x8C8
#घोषणा CXADEC_DEMATRIX_CTL        0x8CC

#घोषणा CXADEC_PATH1_CTL1          0x8D0
#घोषणा CXADEC_PATH1_VOL_CTL       0x8D4
#घोषणा CXADEC_PATH1_EQ_CTL        0x8D8
#घोषणा CXADEC_PATH1_SC_CTL        0x8DC

#घोषणा CXADEC_PATH2_CTL1          0x8E0
#घोषणा CXADEC_PATH2_VOL_CTL       0x8E4
#घोषणा CXADEC_PATH2_EQ_CTL        0x8E8
#घोषणा CXADEC_PATH2_SC_CTL        0x8EC

#घोषणा CXADEC_SRC_CTL             0x8F0
#घोषणा CXADEC_SRC_LF_COEF         0x8F4
#घोषणा CXADEC_SRC1_CTL            0x8F8
#घोषणा CXADEC_SRC2_CTL            0x8FC
#घोषणा CXADEC_SRC3_CTL            0x900
#घोषणा CXADEC_SRC4_CTL            0x904
#घोषणा CXADEC_SRC5_CTL            0x908
#घोषणा CXADEC_SRC6_CTL            0x90C

#घोषणा CXADEC_BASEBAND_OUT_SEL    0x910
#घोषणा CXADEC_I2S_IN_CTL          0x914
#घोषणा CXADEC_I2S_OUT_CTL         0x918
#घोषणा CXADEC_AC97_CTL            0x91C
#घोषणा CXADEC_QAM_PDF             0x920
#घोषणा CXADEC_QAM_CONST_DEC       0x924
#घोषणा CXADEC_QAM_ROTATOR_FREQ    0x948

/* Bit definitions / settings used in Mako Audio */
#घोषणा CXADEC_PREF_MODE_MONO_LANGA        0
#घोषणा CXADEC_PREF_MODE_MONO_LANGB        1
#घोषणा CXADEC_PREF_MODE_MONO_LANGC        2
#घोषणा CXADEC_PREF_MODE_FALLBACK          3
#घोषणा CXADEC_PREF_MODE_STEREO            4
#घोषणा CXADEC_PREF_MODE_DUAL_LANG_AC      5
#घोषणा CXADEC_PREF_MODE_DUAL_LANG_BC      6
#घोषणा CXADEC_PREF_MODE_DUAL_LANG_AB      7


#घोषणा CXADEC_DETECT_STEREO               1
#घोषणा CXADEC_DETECT_DUAL                 2
#घोषणा CXADEC_DETECT_TRI                  4
#घोषणा CXADEC_DETECT_SAP                  0x10
#घोषणा CXADEC_DETECT_NO_SIGNAL            0xFF

#घोषणा CXADEC_SELECT_AUDIO_STANDARD_BG    0xF0  /* NICAM BG and A2 BG */
#घोषणा CXADEC_SELECT_AUDIO_STANDARD_DK1   0xF1  /* NICAM DK and A2 DK */
#घोषणा CXADEC_SELECT_AUDIO_STANDARD_DK2   0xF2
#घोषणा CXADEC_SELECT_AUDIO_STANDARD_DK3   0xF3
#घोषणा CXADEC_SELECT_AUDIO_STANDARD_I     0xF4  /* NICAM I and A1 */
#घोषणा CXADEC_SELECT_AUDIO_STANDARD_L     0xF5  /* NICAM L and System L AM */
#घोषणा CXADEC_SELECT_AUDIO_STANDARD_BTSC  0xF6
#घोषणा CXADEC_SELECT_AUDIO_STANDARD_EIAJ  0xF7
#घोषणा CXADEC_SELECT_AUDIO_STANDARD_A2_M  0xF8  /* A2 M */
#घोषणा CXADEC_SELECT_AUDIO_STANDARD_FM    0xF9  /* FM radio */
#घोषणा CXADEC_SELECT_AUDIO_STANDARD_AUTO  0xFF  /* Auto detect */

अटल अंतरभूत काष्ठा cx18_av_state *to_cx18_av_state(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा cx18_av_state, sd);
पूर्ण

अटल अंतरभूत काष्ठा v4l2_subdev *to_sd(काष्ठा v4l2_ctrl *ctrl)
अणु
	वापस &container_of(ctrl->handler, काष्ठा cx18_av_state, hdl)->sd;
पूर्ण

/* ----------------------------------------------------------------------- */
/* cx18_av-core.c							   */
पूर्णांक cx18_av_ग_लिखो(काष्ठा cx18 *cx, u16 addr, u8 value);
पूर्णांक cx18_av_ग_लिखो4(काष्ठा cx18 *cx, u16 addr, u32 value);
पूर्णांक cx18_av_ग_लिखो4_noretry(काष्ठा cx18 *cx, u16 addr, u32 value);
पूर्णांक cx18_av_ग_लिखो_expect(काष्ठा cx18 *cx, u16 addr, u8 value, u8 eval, u8 mask);
पूर्णांक cx18_av_ग_लिखो4_expect(काष्ठा cx18 *cx, u16 addr, u32 value, u32 eval,
			  u32 mask);
u8 cx18_av_पढ़ो(काष्ठा cx18 *cx, u16 addr);
u32 cx18_av_पढ़ो4(काष्ठा cx18 *cx, u16 addr);
पूर्णांक cx18_av_and_or(काष्ठा cx18 *cx, u16 addr, अचिन्हित mask, u8 value);
पूर्णांक cx18_av_and_or4(काष्ठा cx18 *cx, u16 addr, u32 mask, u32 value);
व्योम cx18_av_std_setup(काष्ठा cx18 *cx);

पूर्णांक cx18_av_probe(काष्ठा cx18 *cx);

/* ----------------------------------------------------------------------- */
/* cx18_av-firmware.c                                                      */
पूर्णांक cx18_av_loadfw(काष्ठा cx18 *cx);

/* ----------------------------------------------------------------------- */
/* cx18_av-audio.c                                                         */
पूर्णांक cx18_av_s_घड़ी_freq(काष्ठा v4l2_subdev *sd, u32 freq);
व्योम cx18_av_audio_set_path(काष्ठा cx18 *cx);
बाह्य स्थिर काष्ठा v4l2_ctrl_ops cx18_av_audio_ctrl_ops;

/* ----------------------------------------------------------------------- */
/* cx18_av-vbi.c                                                           */
पूर्णांक cx18_av_decode_vbi_line(काष्ठा v4l2_subdev *sd,
			   काष्ठा v4l2_decode_vbi_line *vbi);
पूर्णांक cx18_av_s_raw_fmt(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_vbi_क्रमmat *fmt);
पूर्णांक cx18_av_g_sliced_fmt(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_sliced_vbi_क्रमmat *fmt);
पूर्णांक cx18_av_s_sliced_fmt(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_sliced_vbi_क्रमmat *fmt);

#पूर्ण_अगर
