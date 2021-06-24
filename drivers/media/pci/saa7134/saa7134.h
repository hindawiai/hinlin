<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *
 * v4l2 device driver क्रम philips saa7134 based TV cards
 *
 * (c) 2001,02 Gerd Knorr <kraxel@bytesex.org>
 */

#घोषणा SAA7134_VERSION "0, 2, 17"

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/pci.h>
#समावेश <linux/i2c.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/input.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pm_qos.h>

#समावेश <यंत्र/पन.स>

#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/tuner.h>
#समावेश <media/rc-core.h>
#समावेश <media/i2c/ir-kbd-i2c.h>
#समावेश <media/videobuf2-dma-sg.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#अगर IS_ENABLED(CONFIG_VIDEO_SAA7134_DVB)
#समावेश <media/videobuf2-dvb.h>
#पूर्ण_अगर
#समावेश "tda8290.h"

#घोषणा UNSET (-1U)

/* ----------------------------------------------------------- */
/* क्रमागतs                                                       */

क्रमागत saa7134_tvaudio_mode अणु
	TVAUDIO_FM_MONO       = 1,
	TVAUDIO_FM_BG_STEREO  = 2,
	TVAUDIO_FM_SAT_STEREO = 3,
	TVAUDIO_FM_K_STEREO   = 4,
	TVAUDIO_NICAM_AM      = 5,
	TVAUDIO_NICAM_FM      = 6,
पूर्ण;

क्रमागत saa7134_audio_in अणु
	TV    = 1,
	LINE1 = 2,
	LINE2 = 3,
	LINE2_LEFT,
पूर्ण;

क्रमागत saa7134_video_out अणु
	CCIR656 = 1,
पूर्ण;

/* ----------------------------------------------------------- */
/* अटल data                                                 */

काष्ठा saa7134_tvnorm अणु
	अक्षर          *name;
	v4l2_std_id   id;

	/* video decoder */
	अचिन्हित पूर्णांक  sync_control;
	अचिन्हित पूर्णांक  luma_control;
	अचिन्हित पूर्णांक  chroma_ctrl1;
	अचिन्हित पूर्णांक  chroma_gain;
	अचिन्हित पूर्णांक  chroma_ctrl2;
	अचिन्हित पूर्णांक  vgate_misc;

	/* video scaler */
	अचिन्हित पूर्णांक  h_start;
	अचिन्हित पूर्णांक  h_stop;
	अचिन्हित पूर्णांक  video_v_start;
	अचिन्हित पूर्णांक  video_v_stop;
	अचिन्हित पूर्णांक  vbi_v_start_0;
	अचिन्हित पूर्णांक  vbi_v_stop_0;
	अचिन्हित पूर्णांक  src_timing;
	अचिन्हित पूर्णांक  vbi_v_start_1;
पूर्ण;

काष्ठा saa7134_tvaudio अणु
	अक्षर         *name;
	v4l2_std_id  std;
	क्रमागत         saa7134_tvaudio_mode mode;
	पूर्णांक          carr1;
	पूर्णांक          carr2;
पूर्ण;

काष्ठा saa7134_क्रमmat अणु
	अचिन्हित पूर्णांक   fourcc;
	अचिन्हित पूर्णांक   depth;
	अचिन्हित पूर्णांक   pm;
	अचिन्हित पूर्णांक   vshअगरt;   /* vertical करोwnsampling (क्रम planar yuv) */
	अचिन्हित पूर्णांक   hshअगरt;   /* horizontal करोwnsampling (क्रम planar yuv) */
	अचिन्हित पूर्णांक   bswap:1;
	अचिन्हित पूर्णांक   wswap:1;
	अचिन्हित पूर्णांक   yuv:1;
	अचिन्हित पूर्णांक   planar:1;
	अचिन्हित पूर्णांक   uvswap:1;
पूर्ण;

काष्ठा saa7134_card_ir अणु
	काष्ठा rc_dev		*dev;

	अक्षर                    phys[32];

	u32			polling;
	u32			last_gpio;
	u32			mask_keycode, mask_keyकरोwn, mask_keyup;

	bool                    running;

	काष्ठा समयr_list       समयr;

	/* IR core raw decoding */
	u32                     raw_decode;
पूर्ण;

/* ----------------------------------------------------------- */
/* card configuration                                          */

#घोषणा SAA7134_BOARD_NOAUTO        UNSET
#घोषणा SAA7134_BOARD_UNKNOWN           0
#घोषणा SAA7134_BOARD_PROTEUS_PRO       1
#घोषणा SAA7134_BOARD_FLYVIDEO3000      2
#घोषणा SAA7134_BOARD_FLYVIDEO2000      3
#घोषणा SAA7134_BOARD_EMPRESS           4
#घोषणा SAA7134_BOARD_MONSTERTV         5
#घोषणा SAA7134_BOARD_MD9717            6
#घोषणा SAA7134_BOARD_TVSTATION_RDS     7
#घोषणा SAA7134_BOARD_CINERGY400	8
#घोषणा SAA7134_BOARD_MD5044		9
#घोषणा SAA7134_BOARD_KWORLD           10
#घोषणा SAA7134_BOARD_CINERGY600       11
#घोषणा SAA7134_BOARD_MD7134           12
#घोषणा SAA7134_BOARD_TYPHOON_90031    13
#घोषणा SAA7134_BOARD_ELSA             14
#घोषणा SAA7134_BOARD_ELSA_500TV       15
#घोषणा SAA7134_BOARD_ASUSTeK_TVFM7134 16
#घोषणा SAA7134_BOARD_VA1000POWER      17
#घोषणा SAA7134_BOARD_BMK_MPEX_NOTUNER 18
#घोषणा SAA7134_BOARD_VIDEOMATE_TV     19
#घोषणा SAA7134_BOARD_CRONOS_PLUS      20
#घोषणा SAA7134_BOARD_10MOONSTVMASTER  21
#घोषणा SAA7134_BOARD_MD2819           22
#घोषणा SAA7134_BOARD_BMK_MPEX_TUNER   23
#घोषणा SAA7134_BOARD_TVSTATION_DVR    24
#घोषणा SAA7134_BOARD_ASUSTEK_TVFM7133	25
#घोषणा SAA7134_BOARD_PINNACLE_PCTV_STEREO 26
#घोषणा SAA7134_BOARD_MANLI_MTV002     27
#घोषणा SAA7134_BOARD_MANLI_MTV001     28
#घोषणा SAA7134_BOARD_TG3000TV         29
#घोषणा SAA7134_BOARD_ECS_TVP3XP       30
#घोषणा SAA7134_BOARD_ECS_TVP3XP_4CB5  31
#घोषणा SAA7134_BOARD_AVACSSMARTTV     32
#घोषणा SAA7134_BOARD_AVERMEDIA_DVD_EZMAKER 33
#घोषणा SAA7134_BOARD_NOVAC_PRIMETV7133 34
#घोषणा SAA7134_BOARD_AVERMEDIA_STUDIO_305 35
#घोषणा SAA7134_BOARD_UPMOST_PURPLE_TV 36
#घोषणा SAA7134_BOARD_ITEMS_MTV005     37
#घोषणा SAA7134_BOARD_CINERGY200       38
#घोषणा SAA7134_BOARD_FLYTVPLATINUM_MINI 39
#घोषणा SAA7134_BOARD_VIDEOMATE_TV_PVR 40
#घोषणा SAA7134_BOARD_VIDEOMATE_TV_GOLD_PLUS 41
#घोषणा SAA7134_BOARD_SABRENT_SBTTVFM  42
#घोषणा SAA7134_BOARD_ZOLID_XPERT_TV7134 43
#घोषणा SAA7134_BOARD_EMPIRE_PCI_TV_RADIO_LE 44
#घोषणा SAA7134_BOARD_AVERMEDIA_STUDIO_307    45
#घोषणा SAA7134_BOARD_AVERMEDIA_CARDBUS 46
#घोषणा SAA7134_BOARD_CINERGY400_CARDBUS 47
#घोषणा SAA7134_BOARD_CINERGY600_MK3   48
#घोषणा SAA7134_BOARD_VIDEOMATE_GOLD_PLUS 49
#घोषणा SAA7134_BOARD_PINNACLE_300I_DVBT_PAL 50
#घोषणा SAA7134_BOARD_PROVIDEO_PV952   51
#घोषणा SAA7134_BOARD_AVERMEDIA_305    52
#घोषणा SAA7134_BOARD_ASUSTeK_TVFM7135 53
#घोषणा SAA7134_BOARD_FLYTVPLATINUM_FM 54
#घोषणा SAA7134_BOARD_FLYDVBTDUO 55
#घोषणा SAA7134_BOARD_AVERMEDIA_307    56
#घोषणा SAA7134_BOARD_AVERMEDIA_GO_007_FM 57
#घोषणा SAA7134_BOARD_ADS_INSTANT_TV 58
#घोषणा SAA7134_BOARD_KWORLD_VSTREAM_XPERT 59
#घोषणा SAA7134_BOARD_FLYDVBT_DUO_CARDBUS 60
#घोषणा SAA7134_BOARD_PHILIPS_TOUGH 61
#घोषणा SAA7134_BOARD_VIDEOMATE_TV_GOLD_PLUSII 62
#घोषणा SAA7134_BOARD_KWORLD_XPERT 63
#घोषणा SAA7134_BOARD_FLYTV_DIGIMATRIX 64
#घोषणा SAA7134_BOARD_KWORLD_TERMINATOR 65
#घोषणा SAA7134_BOARD_YUAN_TUN900 66
#घोषणा SAA7134_BOARD_BEHOLD_409FM 67
#घोषणा SAA7134_BOARD_GOTVIEW_7135 68
#घोषणा SAA7134_BOARD_PHILIPS_EUROPA  69
#घोषणा SAA7134_BOARD_VIDEOMATE_DVBT_300 70
#घोषणा SAA7134_BOARD_VIDEOMATE_DVBT_200 71
#घोषणा SAA7134_BOARD_RTD_VFG7350 72
#घोषणा SAA7134_BOARD_RTD_VFG7330 73
#घोषणा SAA7134_BOARD_FLYTVPLATINUM_MINI2 74
#घोषणा SAA7134_BOARD_AVERMEDIA_AVERTVHD_A180 75
#घोषणा SAA7134_BOARD_MONSTERTV_MOBILE 76
#घोषणा SAA7134_BOARD_PINNACLE_PCTV_110i 77
#घोषणा SAA7134_BOARD_ASUSTeK_P7131_DUAL 78
#घोषणा SAA7134_BOARD_SEDNA_PC_TV_CARDBUS     79
#घोषणा SAA7134_BOARD_ASUSTEK_DIGIMATRIX_TV 80
#घोषणा SAA7134_BOARD_PHILIPS_TIGER  81
#घोषणा SAA7134_BOARD_MSI_TVATANYWHERE_PLUS  82
#घोषणा SAA7134_BOARD_CINERGY250PCI 83
#घोषणा SAA7134_BOARD_FLYDVB_TRIO 84
#घोषणा SAA7134_BOARD_AVERMEDIA_777 85
#घोषणा SAA7134_BOARD_FLYDVBT_LR301 86
#घोषणा SAA7134_BOARD_ADS_DUO_CARDBUS_PTV331 87
#घोषणा SAA7134_BOARD_TEVION_DVBT_220RF 88
#घोषणा SAA7134_BOARD_ELSA_700TV       89
#घोषणा SAA7134_BOARD_KWORLD_ATSC110   90
#घोषणा SAA7134_BOARD_AVERMEDIA_A169_B 91
#घोषणा SAA7134_BOARD_AVERMEDIA_A169_B1 92
#घोषणा SAA7134_BOARD_MD7134_BRIDGE_2     93
#घोषणा SAA7134_BOARD_FLYDVBT_HYBRID_CARDBUS 94
#घोषणा SAA7134_BOARD_FLYVIDEO3000_NTSC 95
#घोषणा SAA7134_BOARD_MEDION_MD8800_QUADRO 96
#घोषणा SAA7134_BOARD_FLYDVBS_LR300 97
#घोषणा SAA7134_BOARD_PROTEUS_2309 98
#घोषणा SAA7134_BOARD_AVERMEDIA_A16AR   99
#घोषणा SAA7134_BOARD_ASUS_EUROPA2_HYBRID 100
#घोषणा SAA7134_BOARD_PINNACLE_PCTV_310i  101
#घोषणा SAA7134_BOARD_AVERMEDIA_STUDIO_507 102
#घोषणा SAA7134_BOARD_VIDEOMATE_DVBT_200A  103
#घोषणा SAA7134_BOARD_HAUPPAUGE_HVR1110    104
#घोषणा SAA7134_BOARD_CINERGY_HT_PCMCIA    105
#घोषणा SAA7134_BOARD_ENCORE_ENLTV         106
#घोषणा SAA7134_BOARD_ENCORE_ENLTV_FM      107
#घोषणा SAA7134_BOARD_CINERGY_HT_PCI       108
#घोषणा SAA7134_BOARD_PHILIPS_TIGER_S      109
#घोषणा SAA7134_BOARD_AVERMEDIA_M102	   110
#घोषणा SAA7134_BOARD_ASUS_P7131_4871	   111
#घोषणा SAA7134_BOARD_ASUSTeK_P7131_HYBRID_LNA 112
#घोषणा SAA7134_BOARD_ECS_TVP3XP_4CB6  113
#घोषणा SAA7134_BOARD_KWORLD_DVBT_210 114
#घोषणा SAA7134_BOARD_SABRENT_TV_PCB05     115
#घोषणा SAA7134_BOARD_10MOONSTVMASTER3     116
#घोषणा SAA7134_BOARD_AVERMEDIA_SUPER_007  117
#घोषणा SAA7134_BOARD_BEHOLD_401	118
#घोषणा SAA7134_BOARD_BEHOLD_403	119
#घोषणा SAA7134_BOARD_BEHOLD_403FM	120
#घोषणा SAA7134_BOARD_BEHOLD_405	121
#घोषणा SAA7134_BOARD_BEHOLD_405FM	122
#घोषणा SAA7134_BOARD_BEHOLD_407	123
#घोषणा SAA7134_BOARD_BEHOLD_407FM	124
#घोषणा SAA7134_BOARD_BEHOLD_409	125
#घोषणा SAA7134_BOARD_BEHOLD_505FM	126
#घोषणा SAA7134_BOARD_BEHOLD_507_9FM	127
#घोषणा SAA7134_BOARD_BEHOLD_COLUMBUS_TVFM 128
#घोषणा SAA7134_BOARD_BEHOLD_607FM_MK3	129
#घोषणा SAA7134_BOARD_BEHOLD_M6		130
#घोषणा SAA7134_BOARD_TWINHAN_DTV_DVB_3056 131
#घोषणा SAA7134_BOARD_GENIUS_TVGO_A11MCE   132
#घोषणा SAA7134_BOARD_PHILIPS_SNAKE        133
#घोषणा SAA7134_BOARD_CREATIX_CTX953       134
#घोषणा SAA7134_BOARD_MSI_TVANYWHERE_AD11  135
#घोषणा SAA7134_BOARD_AVERMEDIA_CARDBUS_506 136
#घोषणा SAA7134_BOARD_AVERMEDIA_A16D       137
#घोषणा SAA7134_BOARD_AVERMEDIA_M115       138
#घोषणा SAA7134_BOARD_VIDEOMATE_T750       139
#घोषणा SAA7134_BOARD_AVERMEDIA_A700_PRO    140
#घोषणा SAA7134_BOARD_AVERMEDIA_A700_HYBRID 141
#घोषणा SAA7134_BOARD_BEHOLD_H6      142
#घोषणा SAA7134_BOARD_BEHOLD_M63      143
#घोषणा SAA7134_BOARD_BEHOLD_M6_EXTRA    144
#घोषणा SAA7134_BOARD_AVERMEDIA_M103    145
#घोषणा SAA7134_BOARD_ASUSTeK_P7131_ANALOG 146
#घोषणा SAA7134_BOARD_ASUSTeK_TIGER_3IN1   147
#घोषणा SAA7134_BOARD_ENCORE_ENLTV_FM53 148
#घोषणा SAA7134_BOARD_AVERMEDIA_M135A    149
#घोषणा SAA7134_BOARD_REAL_ANGEL_220     150
#घोषणा SAA7134_BOARD_ADS_INSTANT_HDTV_PCI  151
#घोषणा SAA7134_BOARD_ASUSTeK_TIGER         152
#घोषणा SAA7134_BOARD_KWORLD_PLUS_TV_ANALOG 153
#घोषणा SAA7134_BOARD_AVERMEDIA_GO_007_FM_PLUS 154
#घोषणा SAA7134_BOARD_HAUPPAUGE_HVR1150     155
#घोषणा SAA7134_BOARD_HAUPPAUGE_HVR1120   156
#घोषणा SAA7134_BOARD_AVERMEDIA_STUDIO_507UA 157
#घोषणा SAA7134_BOARD_AVERMEDIA_CARDBUS_501 158
#घोषणा SAA7134_BOARD_BEHOLD_505RDS_MK5     159
#घोषणा SAA7134_BOARD_BEHOLD_507RDS_MK3     160
#घोषणा SAA7134_BOARD_BEHOLD_507RDS_MK5     161
#घोषणा SAA7134_BOARD_BEHOLD_607FM_MK5      162
#घोषणा SAA7134_BOARD_BEHOLD_609FM_MK3      163
#घोषणा SAA7134_BOARD_BEHOLD_609FM_MK5      164
#घोषणा SAA7134_BOARD_BEHOLD_607RDS_MK3     165
#घोषणा SAA7134_BOARD_BEHOLD_607RDS_MK5     166
#घोषणा SAA7134_BOARD_BEHOLD_609RDS_MK3     167
#घोषणा SAA7134_BOARD_BEHOLD_609RDS_MK5     168
#घोषणा SAA7134_BOARD_VIDEOMATE_S350        169
#घोषणा SAA7134_BOARD_AVERMEDIA_STUDIO_505  170
#घोषणा SAA7134_BOARD_BEHOLD_X7             171
#घोषणा SAA7134_BOARD_ROVERMEDIA_LINK_PRO_FM 172
#घोषणा SAA7134_BOARD_ZOLID_HYBRID_PCI		173
#घोषणा SAA7134_BOARD_ASUS_EUROPA_HYBRID	174
#घोषणा SAA7134_BOARD_LEADTEK_WINFAST_DTV1000S 175
#घोषणा SAA7134_BOARD_BEHOLD_505RDS_MK3     176
#घोषणा SAA7134_BOARD_HAWELL_HW_404M7		177
#घोषणा SAA7134_BOARD_BEHOLD_H7             178
#घोषणा SAA7134_BOARD_BEHOLD_A7             179
#घोषणा SAA7134_BOARD_AVERMEDIA_M733A       180
#घोषणा SAA7134_BOARD_TECHNOTREND_BUDGET_T3000 181
#घोषणा SAA7134_BOARD_KWORLD_PCI_SBTVD_FULLSEG 182
#घोषणा SAA7134_BOARD_VIDEOMATE_M1F         183
#घोषणा SAA7134_BOARD_ENCORE_ENLTV_FM3      184
#घोषणा SAA7134_BOARD_MAGICPRO_PROHDTV_PRO2 185
#घोषणा SAA7134_BOARD_BEHOLD_501            186
#घोषणा SAA7134_BOARD_BEHOLD_503FM          187
#घोषणा SAA7134_BOARD_SENSORAY811_911       188
#घोषणा SAA7134_BOARD_KWORLD_PC150U         189
#घोषणा SAA7134_BOARD_ASUSTeK_PS3_100      190
#घोषणा SAA7134_BOARD_HAWELL_HW_9004V1      191
#घोषणा SAA7134_BOARD_AVERMEDIA_A706		192
#घोषणा SAA7134_BOARD_WIS_VOYAGER           193
#घोषणा SAA7134_BOARD_AVERMEDIA_505         194
#घोषणा SAA7134_BOARD_LEADTEK_WINFAST_TV2100_FM 195
#घोषणा SAA7134_BOARD_SNAZIO_TVPVR_PRO      196

#घोषणा SAA7134_MAXBOARDS 32
#घोषणा SAA7134_INPUT_MAX 8

/* ----------------------------------------------------------- */
/* Since we support 2 remote types, lets tell them apart       */

#घोषणा SAA7134_REMOTE_GPIO  1
#घोषणा SAA7134_REMOTE_I2C   2

/* ----------------------------------------------------------- */
/* Video Output Port Register Initialization Options           */

#घोषणा SET_T_CODE_POLARITY_NON_INVERTED	(1 << 0)
#घोषणा SET_CLOCK_NOT_DELAYED			(1 << 1)
#घोषणा SET_CLOCK_INVERTED			(1 << 2)
#घोषणा SET_VSYNC_OFF				(1 << 3)

क्रमागत saa7134_input_types अणु
	SAA7134_NO_INPUT = 0,
	SAA7134_INPUT_MUTE,
	SAA7134_INPUT_RADIO,
	SAA7134_INPUT_TV,
	SAA7134_INPUT_TV_MONO,
	SAA7134_INPUT_COMPOSITE,
	SAA7134_INPUT_COMPOSITE0,
	SAA7134_INPUT_COMPOSITE1,
	SAA7134_INPUT_COMPOSITE2,
	SAA7134_INPUT_COMPOSITE3,
	SAA7134_INPUT_COMPOSITE4,
	SAA7134_INPUT_SVIDEO,
	SAA7134_INPUT_SVIDEO0,
	SAA7134_INPUT_SVIDEO1,
	SAA7134_INPUT_COMPOSITE_OVER_SVIDEO,
पूर्ण;

काष्ठा saa7134_input अणु
	क्रमागत saa7134_input_types type;
	अचिन्हित पूर्णांक             vmux;
	क्रमागत saa7134_audio_in    amux;
	अचिन्हित पूर्णांक             gpio;
पूर्ण;

क्रमागत saa7134_mpeg_type अणु
	SAA7134_MPEG_UNUSED,
	SAA7134_MPEG_EMPRESS,
	SAA7134_MPEG_DVB,
	SAA7134_MPEG_GO7007,
पूर्ण;

क्रमागत saa7134_mpeg_ts_type अणु
	SAA7134_MPEG_TS_PARALLEL = 0,
	SAA7134_MPEG_TS_SERIAL,
पूर्ण;

काष्ठा saa7134_board अणु
	अक्षर                    *name;
	अचिन्हित पूर्णांक            audio_घड़ी;

	/* input चयनing */
	अचिन्हित पूर्णांक            gpiomask;
	काष्ठा saa7134_input    inमाला_दो[SAA7134_INPUT_MAX];
	काष्ठा saa7134_input    radio;
	काष्ठा saa7134_input    mute;

	/* i2c chip info */
	अचिन्हित पूर्णांक            tuner_type;
	अचिन्हित पूर्णांक		radio_type;
	अचिन्हित अक्षर		tuner_addr;
	अचिन्हित अक्षर		radio_addr;
	अचिन्हित अक्षर		empress_addr;
	अचिन्हित अक्षर		rds_addr;

	अचिन्हित पूर्णांक            tda9887_conf;
	काष्ठा tda829x_config   tda829x_conf;

	/* peripheral I/O */
	क्रमागत saa7134_video_out  video_out;
	क्रमागत saa7134_mpeg_type  mpeg;
	क्रमागत saa7134_mpeg_ts_type ts_type;
	अचिन्हित पूर्णांक            vid_port_opts;
	अचिन्हित पूर्णांक            ts_क्रमce_val:1;
पूर्ण;

#घोषणा card_has_radio(dev)   (SAA7134_NO_INPUT != saa7134_boards[dev->board].radio.type)
#घोषणा card_is_empress(dev)  (SAA7134_MPEG_EMPRESS == saa7134_boards[dev->board].mpeg)
#घोषणा card_is_dvb(dev)      (SAA7134_MPEG_DVB     == saa7134_boards[dev->board].mpeg)
#घोषणा card_is_go7007(dev)   (SAA7134_MPEG_GO7007  == saa7134_boards[dev->board].mpeg)
#घोषणा card_has_mpeg(dev)    (SAA7134_MPEG_UNUSED  != saa7134_boards[dev->board].mpeg)
#घोषणा card(dev)             (saa7134_boards[dev->board])
#घोषणा card_in(dev,n)        (saa7134_boards[dev->board].inमाला_दो[n])

#घोषणा V4L2_CID_PRIVATE_INVERT      (V4L2_CID_USER_SAA7134_BASE + 0)
#घोषणा V4L2_CID_PRIVATE_Y_ODD       (V4L2_CID_USER_SAA7134_BASE + 1)
#घोषणा V4L2_CID_PRIVATE_Y_EVEN      (V4L2_CID_USER_SAA7134_BASE + 2)
#घोषणा V4L2_CID_PRIVATE_AUTOMUTE    (V4L2_CID_USER_SAA7134_BASE + 3)

/* ----------------------------------------------------------- */
/* device / file handle status                                 */

#घोषणा RESOURCE_OVERLAY       1
#घोषणा RESOURCE_VIDEO         2
#घोषणा RESOURCE_VBI           4
#घोषणा RESOURCE_EMPRESS       8

#घोषणा INTERLACE_AUTO         0
#घोषणा INTERLACE_ON           1
#घोषणा INTERLACE_OFF          2

#घोषणा BUFFER_TIMEOUT     msecs_to_jअगरfies(500)  /* 0.5 seconds */
#घोषणा TS_BUFFER_TIMEOUT  msecs_to_jअगरfies(1000)  /* 1 second */

काष्ठा saa7134_dev;
काष्ठा saa7134_dma;

/* saa7134 page table */
काष्ठा saa7134_pgtable अणु
	अचिन्हित पूर्णांक               size;
	__le32                     *cpu;
	dma_addr_t                 dma;
पूर्ण;

/* tvaudio thपढ़ो status */
काष्ठा saa7134_thपढ़ो अणु
	काष्ठा task_काष्ठा         *thपढ़ो;
	अचिन्हित पूर्णांक               scan1;
	अचिन्हित पूर्णांक               scan2;
	अचिन्हित पूर्णांक               mode;
	अचिन्हित पूर्णांक		   stopped;
पूर्ण;

/* buffer क्रम one video/vbi/ts frame */
काष्ठा saa7134_buf अणु
	/* common v4l buffer stuff -- must be first */
	काष्ठा vb2_v4l2_buffer vb2;

	/* saa7134 specअगरic */
	अचिन्हित पूर्णांक            top_seen;
	पूर्णांक (*activate)(काष्ठा saa7134_dev *dev,
			काष्ठा saa7134_buf *buf,
			काष्ठा saa7134_buf *next);

	काष्ठा list_head	entry;
पूर्ण;

काष्ठा saa7134_dmaqueue अणु
	काष्ठा saa7134_dev         *dev;
	काष्ठा saa7134_buf         *curr;
	काष्ठा list_head           queue;
	काष्ठा समयr_list          समयout;
	अचिन्हित पूर्णांक               need_two;
	अचिन्हित पूर्णांक               seq_nr;
	काष्ठा saa7134_pgtable     pt;
पूर्ण;

/* dmasound dsp status */
काष्ठा saa7134_dmasound अणु
	काष्ठा mutex               lock;
	पूर्णांक                        minor_mixer;
	पूर्णांक                        minor_dsp;
	अचिन्हित पूर्णांक               users_dsp;

	/* mixer */
	क्रमागत saa7134_audio_in      input;
	अचिन्हित पूर्णांक               count;
	अचिन्हित पूर्णांक               line1;
	अचिन्हित पूर्णांक               line2;

	/* dsp */
	अचिन्हित पूर्णांक               afmt;
	अचिन्हित पूर्णांक               rate;
	अचिन्हित पूर्णांक               channels;
	अचिन्हित पूर्णांक               recording_on;
	अचिन्हित पूर्णांक               dma_running;
	अचिन्हित पूर्णांक               blocks;
	अचिन्हित पूर्णांक               blksize;
	अचिन्हित पूर्णांक               bufsize;
	काष्ठा saa7134_pgtable     pt;
	व्योम			   *vaddr;
	काष्ठा scatterlist	   *sglist;
	पूर्णांक                        sglen;
	अचिन्हित दीर्घ              nr_pages;
	अचिन्हित पूर्णांक               dma_blk;
	अचिन्हित पूर्णांक               पढ़ो_offset;
	अचिन्हित पूर्णांक               पढ़ो_count;
	व्योम *			   priv_data;
	काष्ठा snd_pcm_substream   *substream;
पूर्ण;

/* ts/mpeg status */
काष्ठा saa7134_ts अणु
	/* TS capture */
	पूर्णांक                        nr_packets;
	पूर्णांक                        nr_bufs;
पूर्ण;

/* ts/mpeg ops */
काष्ठा saa7134_mpeg_ops अणु
	क्रमागत saa7134_mpeg_type     type;
	काष्ठा list_head           next;
	पूर्णांक                        (*init)(काष्ठा saa7134_dev *dev);
	पूर्णांक                        (*fini)(काष्ठा saa7134_dev *dev);
	व्योम                       (*संकेत_change)(काष्ठा saa7134_dev *dev);
	व्योम                       (*irq_ts_करोne)(काष्ठा saa7134_dev *dev,
						  अचिन्हित दीर्घ status);
पूर्ण;

क्रमागत saa7134_pads अणु
	SAA7134_PAD_IF_INPUT,
	SAA7134_PAD_VID_OUT,
	SAA7134_NUM_PADS
पूर्ण;

/* global device status */
काष्ठा saa7134_dev अणु
	काष्ठा list_head           devlist;
	काष्ठा mutex               lock;
	spinlock_t                 slock;
	काष्ठा v4l2_device         v4l2_dev;
	/* workकाष्ठा क्रम loading modules */
	काष्ठा work_काष्ठा request_module_wk;

	/* insmod option/स्वतःdetected */
	पूर्णांक                        स्वतःdetected;

	/* various device info */
	अचिन्हित पूर्णांक               resources;
	काष्ठा video_device        *video_dev;
	काष्ठा video_device        *radio_dev;
	काष्ठा video_device        *vbi_dev;
	काष्ठा saa7134_dmasound    dmasound;

	/* infrared remote */
	पूर्णांक                        has_remote;
	काष्ठा saa7134_card_ir     *remote;

	/* pci i/o */
	अक्षर                       name[32];
	पूर्णांक                        nr;
	काष्ठा pci_dev             *pci;
	अचिन्हित अक्षर              pci_rev,pci_lat;
	__u32                      __iomem *lmmio;
	__u8                       __iomem *bmmio;

	/* config info */
	अचिन्हित पूर्णांक               board;
	अचिन्हित पूर्णांक               tuner_type;
	अचिन्हित पूर्णांक		   radio_type;
	अचिन्हित अक्षर		   tuner_addr;
	अचिन्हित अक्षर		   radio_addr;

	अचिन्हित पूर्णांक               tda9887_conf;
	अचिन्हित पूर्णांक               gpio_value;

	/* i2c i/o */
	काष्ठा i2c_adapter         i2c_adap;
	काष्ठा i2c_client          i2c_client;
	अचिन्हित अक्षर              eedata[256];
	पूर्णांक			   has_rds;

	/* video overlay */
	काष्ठा v4l2_framebuffer    ovbuf;
	काष्ठा saa7134_क्रमmat      *ovfmt;
	अचिन्हित पूर्णांक               ovenable;
	क्रमागत v4l2_field            ovfield;
	काष्ठा v4l2_winकरोw         win;
	काष्ठा v4l2_clip           clips[8];
	अचिन्हित पूर्णांक               nclips;
	काष्ठा v4l2_fh		   *overlay_owner;


	/* video+ts+vbi capture */
	काष्ठा saa7134_dmaqueue    video_q;
	काष्ठा vb2_queue           video_vbq;
	काष्ठा saa7134_dmaqueue    vbi_q;
	काष्ठा vb2_queue           vbi_vbq;
	क्रमागत v4l2_field		   field;
	काष्ठा saa7134_क्रमmat      *fmt;
	अचिन्हित पूर्णांक               width, height;
	अचिन्हित पूर्णांक               vbi_hlen, vbi_vlen;
	काष्ठा pm_qos_request	   qos_request;

	/* SAA7134_MPEG_* */
	काष्ठा saa7134_ts          ts;
	काष्ठा saa7134_dmaqueue    ts_q;
	क्रमागत v4l2_field		   ts_field;
	पूर्णांक                        ts_started;
	काष्ठा saa7134_mpeg_ops    *mops;

	/* SAA7134_MPEG_EMPRESS only */
	काष्ठा video_device        *empress_dev;
	काष्ठा v4l2_subdev	   *empress_sd;
	काष्ठा vb2_queue           empress_vbq;
	काष्ठा work_काष्ठा         empress_workqueue;
	पूर्णांक                        empress_started;
	काष्ठा v4l2_ctrl_handler   empress_ctrl_handler;

	/* various v4l controls */
	काष्ठा saa7134_tvnorm      *tvnorm;              /* video */
	काष्ठा saa7134_tvaudio     *tvaudio;
	काष्ठा v4l2_ctrl_handler   ctrl_handler;
	अचिन्हित पूर्णांक               ctl_input;
	पूर्णांक                        ctl_bright;
	पूर्णांक                        ctl_contrast;
	पूर्णांक                        ctl_hue;
	पूर्णांक                        ctl_saturation;
	पूर्णांक                        ctl_mute;             /* audio */
	पूर्णांक                        ctl_volume;
	पूर्णांक                        ctl_invert;           /* निजी */
	पूर्णांक                        ctl_mirror;
	पूर्णांक                        ctl_y_odd;
	पूर्णांक                        ctl_y_even;
	पूर्णांक                        ctl_स्वतःmute;

	/* crop */
	काष्ठा v4l2_rect           crop_bounds;
	काष्ठा v4l2_rect           crop_defrect;
	काष्ठा v4l2_rect           crop_current;

	/* other global state info */
	अचिन्हित पूर्णांक               स्वतःmute;
	काष्ठा saa7134_thपढ़ो      thपढ़ो;
	काष्ठा saa7134_input       *input;
	काष्ठा saa7134_input       *hw_input;
	अचिन्हित पूर्णांक               hw_mute;
	पूर्णांक                        last_carrier;
	पूर्णांक                        noसंकेत;
	अचिन्हित पूर्णांक               insuspend;
	काष्ठा v4l2_ctrl_handler   radio_ctrl_handler;

	/* I2C keyboard data */
	काष्ठा IR_i2c_init_data    init_data;

#अगर_घोषित CONFIG_MEDIA_CONTROLLER
	काष्ठा media_device *media_dev;

	काष्ठा media_entity input_ent[SAA7134_INPUT_MAX + 1];
	काष्ठा media_pad input_pad[SAA7134_INPUT_MAX + 1];

	काष्ठा media_entity demod;
	काष्ठा media_pad demod_pad[SAA7134_NUM_PADS];

	काष्ठा media_pad video_pad, vbi_pad;
	काष्ठा media_entity *decoder;
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_VIDEO_SAA7134_DVB)
	/* SAA7134_MPEG_DVB only */
	काष्ठा vb2_dvb_frontends frontends;
	पूर्णांक (*original_demod_sleep)(काष्ठा dvb_frontend *fe);
	पूर्णांक (*original_set_voltage)(काष्ठा dvb_frontend *fe,
				    क्रमागत fe_sec_voltage voltage);
	पूर्णांक (*original_set_high_voltage)(काष्ठा dvb_frontend *fe, दीर्घ arg);
#पूर्ण_अगर
	व्योम (*gate_ctrl)(काष्ठा saa7134_dev *dev, पूर्णांक खोलो);
पूर्ण;

/* ----------------------------------------------------------- */

#घोषणा saa_पढ़ोl(reg)             पढ़ोl(dev->lmmio + (reg))
#घोषणा saa_ग_लिखोl(reg,value)      ग_लिखोl((value), dev->lmmio + (reg));
#घोषणा saa_anकरोrl(reg,mask,value) \
  ग_लिखोl((पढ़ोl(dev->lmmio+(reg)) & ~(mask)) |\
  ((value) & (mask)), dev->lmmio+(reg))
#घोषणा saa_setl(reg,bit)          saa_anकरोrl((reg),(bit),(bit))
#घोषणा saa_clearl(reg,bit)        saa_anकरोrl((reg),(bit),0)

#घोषणा saa_पढ़ोb(reg)             पढ़ोb(dev->bmmio + (reg))
#घोषणा saa_ग_लिखोb(reg,value)      ग_लिखोb((value), dev->bmmio + (reg));
#घोषणा saa_anकरोrb(reg,mask,value) \
  ग_लिखोb((पढ़ोb(dev->bmmio+(reg)) & ~(mask)) |\
  ((value) & (mask)), dev->bmmio+(reg))
#घोषणा saa_setb(reg,bit)          saa_anकरोrb((reg),(bit),(bit))
#घोषणा saa_clearb(reg,bit)        saa_anकरोrb((reg),(bit),0)

#घोषणा saa_रुको(us) अणु udelay(us); पूर्ण

#घोषणा SAA7134_NORMS	(\
		V4L2_STD_PAL    | V4L2_STD_PAL_N | \
		V4L2_STD_PAL_Nc | V4L2_STD_SECAM | \
		V4L2_STD_NTSC   | V4L2_STD_PAL_M | \
		V4L2_STD_PAL_60)

#घोषणा GRP_EMPRESS (1)
#घोषणा saa_call_all(dev, o, f, args...) करो अणु				\
	अगर (dev->gate_ctrl)						\
		dev->gate_ctrl(dev, 1);					\
	v4l2_device_call_all(&(dev)->v4l2_dev, 0, o, f , ##args);	\
	अगर (dev->gate_ctrl)						\
		dev->gate_ctrl(dev, 0);					\
पूर्ण जबतक (0)

#घोषणा saa_call_empress(dev, o, f, args...) (अणु				\
	दीर्घ _rc;							\
	अगर (dev->gate_ctrl)						\
		dev->gate_ctrl(dev, 1);					\
	_rc = v4l2_device_call_until_err(&(dev)->v4l2_dev,		\
					 GRP_EMPRESS, o, f , ##args);	\
	अगर (dev->gate_ctrl)						\
		dev->gate_ctrl(dev, 0);					\
	_rc;								\
पूर्ण)

अटल अंतरभूत bool is_empress(काष्ठा file *file)
अणु
	काष्ठा video_device *vdev = video_devdata(file);
	काष्ठा saa7134_dev *dev = video_get_drvdata(vdev);

	वापस vdev->queue == &dev->empress_vbq;
पूर्ण

/* ----------------------------------------------------------- */
/* saa7134-core.c                                              */

बाह्य काष्ठा list_head  saa7134_devlist;
बाह्य काष्ठा mutex saa7134_devlist_lock;
बाह्य पूर्णांक saa7134_no_overlay;
बाह्य bool saa7134_userptr;

व्योम saa7134_track_gpio(काष्ठा saa7134_dev *dev, स्थिर अक्षर *msg);
व्योम saa7134_set_gpio(काष्ठा saa7134_dev *dev, पूर्णांक bit_no, पूर्णांक value);

#घोषणा SAA7134_PGTABLE_SIZE 4096

पूर्णांक saa7134_pgtable_alloc(काष्ठा pci_dev *pci, काष्ठा saa7134_pgtable *pt);
पूर्णांक  saa7134_pgtable_build(काष्ठा pci_dev *pci, काष्ठा saa7134_pgtable *pt,
			   काष्ठा scatterlist *list, अचिन्हित पूर्णांक length,
			   अचिन्हित पूर्णांक startpage);
व्योम saa7134_pgtable_मुक्त(काष्ठा pci_dev *pci, काष्ठा saa7134_pgtable *pt);

पूर्णांक saa7134_buffer_count(अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक count);
पूर्णांक saa7134_buffer_startpage(काष्ठा saa7134_buf *buf);
अचिन्हित दीर्घ saa7134_buffer_base(काष्ठा saa7134_buf *buf);

पूर्णांक saa7134_buffer_queue(काष्ठा saa7134_dev *dev, काष्ठा saa7134_dmaqueue *q,
			 काष्ठा saa7134_buf *buf);
व्योम saa7134_buffer_finish(काष्ठा saa7134_dev *dev, काष्ठा saa7134_dmaqueue *q,
			   अचिन्हित पूर्णांक state);
व्योम saa7134_buffer_next(काष्ठा saa7134_dev *dev, काष्ठा saa7134_dmaqueue *q);
व्योम saa7134_buffer_समयout(काष्ठा समयr_list *t);
व्योम saa7134_stop_streaming(काष्ठा saa7134_dev *dev, काष्ठा saa7134_dmaqueue *q);

पूर्णांक saa7134_set_dmabits(काष्ठा saa7134_dev *dev);

बाह्य पूर्णांक (*saa7134_dmasound_init)(काष्ठा saa7134_dev *dev);
बाह्य पूर्णांक (*saa7134_dmasound_निकास)(काष्ठा saa7134_dev *dev);


/* ----------------------------------------------------------- */
/* saa7134-cards.c                                             */

बाह्य काष्ठा saa7134_board saa7134_boards[];
बाह्य स्थिर अक्षर * स्थिर saa7134_input_name[];
बाह्य स्थिर अचिन्हित पूर्णांक saa7134_bcount;
बाह्य काष्ठा pci_device_id saa7134_pci_tbl[];

बाह्य पूर्णांक saa7134_board_init1(काष्ठा saa7134_dev *dev);
बाह्य पूर्णांक saa7134_board_init2(काष्ठा saa7134_dev *dev);
पूर्णांक saa7134_tuner_callback(व्योम *priv, पूर्णांक component, पूर्णांक command, पूर्णांक arg);


/* ----------------------------------------------------------- */
/* saa7134-i2c.c                                               */

पूर्णांक saa7134_i2c_रेजिस्टर(काष्ठा saa7134_dev *dev);
पूर्णांक saa7134_i2c_unरेजिस्टर(काष्ठा saa7134_dev *dev);


/* ----------------------------------------------------------- */
/* saa7134-video.c                                             */

बाह्य अचिन्हित पूर्णांक video_debug;
बाह्य काष्ठा video_device saa7134_video_ढाँचा;
बाह्य काष्ठा video_device saa7134_radio_ढाँचा;

व्योम saa7134_vb2_buffer_queue(काष्ठा vb2_buffer *vb);
पूर्णांक saa7134_vb2_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count);
व्योम saa7134_vb2_stop_streaming(काष्ठा vb2_queue *vq);

पूर्णांक saa7134_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id id);
पूर्णांक saa7134_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *id);
पूर्णांक saa7134_querystd(काष्ठा file *file, व्योम *priv, v4l2_std_id *std);
पूर्णांक saa7134_क्रमागत_input(काष्ठा file *file, व्योम *priv, काष्ठा v4l2_input *i);
पूर्णांक saa7134_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i);
पूर्णांक saa7134_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i);
पूर्णांक saa7134_querycap(काष्ठा file *file, व्योम  *priv,
					काष्ठा v4l2_capability *cap);
पूर्णांक saa7134_g_tuner(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_tuner *t);
पूर्णांक saa7134_s_tuner(काष्ठा file *file, व्योम *priv,
					स्थिर काष्ठा v4l2_tuner *t);
पूर्णांक saa7134_g_frequency(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_frequency *f);
पूर्णांक saa7134_s_frequency(काष्ठा file *file, व्योम *priv,
					स्थिर काष्ठा v4l2_frequency *f);

पूर्णांक saa7134_videoport_init(काष्ठा saa7134_dev *dev);
व्योम saa7134_set_tvnorm_hw(काष्ठा saa7134_dev *dev);

पूर्णांक saa7134_video_init1(काष्ठा saa7134_dev *dev);
पूर्णांक saa7134_video_init2(काष्ठा saa7134_dev *dev);
व्योम saa7134_irq_video_संकेतchange(काष्ठा saa7134_dev *dev);
व्योम saa7134_irq_video_करोne(काष्ठा saa7134_dev *dev, अचिन्हित दीर्घ status);
व्योम saa7134_video_fini(काष्ठा saa7134_dev *dev);


/* ----------------------------------------------------------- */
/* saa7134-ts.c                                                */

#घोषणा TS_PACKET_SIZE 188 /* TS packets 188 bytes */

पूर्णांक saa7134_ts_buffer_init(काष्ठा vb2_buffer *vb2);
पूर्णांक saa7134_ts_buffer_prepare(काष्ठा vb2_buffer *vb2);
पूर्णांक saa7134_ts_queue_setup(काष्ठा vb2_queue *q,
			   अचिन्हित पूर्णांक *nbuffers, अचिन्हित पूर्णांक *nplanes,
			   अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[]);
पूर्णांक saa7134_ts_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count);
व्योम saa7134_ts_stop_streaming(काष्ठा vb2_queue *vq);

बाह्य काष्ठा vb2_ops saa7134_ts_qops;

पूर्णांक saa7134_ts_init1(काष्ठा saa7134_dev *dev);
पूर्णांक saa7134_ts_fini(काष्ठा saa7134_dev *dev);
व्योम saa7134_irq_ts_करोne(काष्ठा saa7134_dev *dev, अचिन्हित दीर्घ status);

पूर्णांक saa7134_ts_रेजिस्टर(काष्ठा saa7134_mpeg_ops *ops);
व्योम saa7134_ts_unरेजिस्टर(काष्ठा saa7134_mpeg_ops *ops);

पूर्णांक saa7134_ts_init_hw(काष्ठा saa7134_dev *dev);

पूर्णांक saa7134_ts_start(काष्ठा saa7134_dev *dev);
पूर्णांक saa7134_ts_stop(काष्ठा saa7134_dev *dev);

/* ----------------------------------------------------------- */
/* saa7134-vbi.c                                               */

बाह्य स्थिर काष्ठा vb2_ops saa7134_vbi_qops;
बाह्य काष्ठा video_device saa7134_vbi_ढाँचा;

पूर्णांक saa7134_vbi_init1(काष्ठा saa7134_dev *dev);
पूर्णांक saa7134_vbi_fini(काष्ठा saa7134_dev *dev);
व्योम saa7134_irq_vbi_करोne(काष्ठा saa7134_dev *dev, अचिन्हित दीर्घ status);


/* ----------------------------------------------------------- */
/* saa7134-tvaudio.c                                           */

पूर्णांक saa7134_tvaudio_rx2mode(u32 rx);

व्योम saa7134_tvaudio_seपंचांगute(काष्ठा saa7134_dev *dev);
व्योम saa7134_tvaudio_setinput(काष्ठा saa7134_dev *dev,
			      काष्ठा saa7134_input *in);
व्योम saa7134_tvaudio_setvolume(काष्ठा saa7134_dev *dev, पूर्णांक level);
पूर्णांक saa7134_tvaudio_माला_लोtereo(काष्ठा saa7134_dev *dev);

व्योम saa7134_tvaudio_init(काष्ठा saa7134_dev *dev);
पूर्णांक saa7134_tvaudio_init2(काष्ठा saa7134_dev *dev);
पूर्णांक saa7134_tvaudio_fini(काष्ठा saa7134_dev *dev);
पूर्णांक saa7134_tvaudio_करो_scan(काष्ठा saa7134_dev *dev);
पूर्णांक saa7134_tvaudio_बंद(काष्ठा saa7134_dev *dev);

पूर्णांक saa_dsp_ग_लिखोl(काष्ठा saa7134_dev *dev, पूर्णांक reg, u32 value);

व्योम saa7134_enable_i2s(काष्ठा saa7134_dev *dev);

/* ----------------------------------------------------------- */
/* saa7134-oss.c                                               */

बाह्य स्थिर काष्ठा file_operations saa7134_dsp_fops;
बाह्य स्थिर काष्ठा file_operations saa7134_mixer_fops;

पूर्णांक saa7134_oss_init1(काष्ठा saa7134_dev *dev);
पूर्णांक saa7134_oss_fini(काष्ठा saa7134_dev *dev);
व्योम saa7134_irq_oss_करोne(काष्ठा saa7134_dev *dev, अचिन्हित दीर्घ status);

/* ----------------------------------------------------------- */
/* saa7134-input.c                                             */

#अगर defined(CONFIG_VIDEO_SAA7134_RC)
पूर्णांक  saa7134_input_init1(काष्ठा saa7134_dev *dev);
व्योम saa7134_input_fini(काष्ठा saa7134_dev *dev);
व्योम saa7134_input_irq(काष्ठा saa7134_dev *dev);
व्योम saa7134_probe_i2c_ir(काष्ठा saa7134_dev *dev);
पूर्णांक saa7134_ir_खोलो(काष्ठा rc_dev *dev);
व्योम saa7134_ir_बंद(काष्ठा rc_dev *dev);
#अन्यथा
#घोषणा saa7134_input_init1(dev)	((व्योम)0)
#घोषणा saa7134_input_fini(dev)		((व्योम)0)
#घोषणा saa7134_input_irq(dev)		((व्योम)0)
#घोषणा saa7134_probe_i2c_ir(dev)	((व्योम)0)
#घोषणा saa7134_ir_खोलो(dev)		((व्योम)0)
#घोषणा saa7134_ir_बंद(dev)		((व्योम)0)
#पूर्ण_अगर
