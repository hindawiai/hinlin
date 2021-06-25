<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * v4l2 device driver क्रम cx2388x based TV cards
 *
 * (c) 2003,04 Gerd Knorr <kraxel@bytesex.org> [SUSE Lअसल]
 */

#अगर_अघोषित CX88_H
#घोषणा CX88_H

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/pci.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/refcount.h>

#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/tuner.h>
#समावेश <media/tveeprom.h>
#समावेश <media/videobuf2-dma-sg.h>
#समावेश <media/drv-पूर्णांकf/cx2341x.h>
#समावेश <media/videobuf2-dvb.h>
#समावेश <media/i2c/ir-kbd-i2c.h>
#समावेश <media/i2c/wm8775.h>

#समावेश "cx88-reg.h"
#समावेश "tuner-xc2028.h"

#समावेश <linux/mutex.h>

#घोषणा CX88_VERSION "1.0.0"

#घोषणा UNSET (-1U)

#घोषणा CX88_MAXBOARDS 8

/* Max number of inमाला_दो by card */
#घोषणा MAX_CX88_INPUT 8

/* ----------------------------------------------------------- */
/* defines and क्रमागतs                                           */

/* Currently unsupported by the driver: PAL/H, NTSC/Kr, SECAM/LC */
#घोषणा CX88_NORMS (V4L2_STD_ALL		\
		    & ~V4L2_STD_PAL_H		\
		    & ~V4L2_STD_NTSC_M_KR	\
		    & ~V4L2_STD_SECAM_LC)

#घोषणा FORMAT_FLAGS_PACKED       0x01
#घोषणा FORMAT_FLAGS_PLANAR       0x02

#घोषणा VBI_LINE_PAL_COUNT              18
#घोषणा VBI_LINE_NTSC_COUNT             12
#घोषणा VBI_LINE_LENGTH           2048

#घोषणा AUD_RDS_LINES		     4

/* need "shadow" रेजिस्टरs क्रम some ग_लिखो-only ones ... */
#घोषणा SHADOW_AUD_VOL_CTL           1
#घोषणा SHADOW_AUD_BAL_CTL           2
#घोषणा SHADOW_MAX                   3

/* FM Radio deemphasis type */
क्रमागत cx88_deemph_type अणु
	FM_NO_DEEMPH = 0,
	FM_DEEMPH_50,
	FM_DEEMPH_75
पूर्ण;

क्रमागत cx88_board_type अणु
	CX88_BOARD_NONE = 0,
	CX88_MPEG_DVB,
	CX88_MPEG_BLACKBIRD
पूर्ण;

क्रमागत cx8802_board_access अणु
	CX8802_DRVCTL_SHARED    = 1,
	CX8802_DRVCTL_EXCLUSIVE = 2,
पूर्ण;

/* ----------------------------------------------------------- */
/* tv norms                                                    */

अटल अंतरभूत अचिन्हित पूर्णांक norm_maxw(v4l2_std_id norm)
अणु
	वापस 720;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक norm_maxh(v4l2_std_id norm)
अणु
	वापस (norm & V4L2_STD_525_60) ? 480 : 576;
पूर्ण

/* ----------------------------------------------------------- */
/* अटल data                                                 */

काष्ठा cx8800_fmt अणु
	u32   fourcc;          /* v4l2 क्रमmat id */
	पूर्णांक   depth;
	पूर्णांक   flags;
	u32   cxक्रमmat;
पूर्ण;

/* ----------------------------------------------------------- */
/* SRAM memory management data (see cx88-core.c)               */

#घोषणा SRAM_CH21 0   /* video */
#घोषणा SRAM_CH22 1
#घोषणा SRAM_CH23 2
#घोषणा SRAM_CH24 3   /* vbi   */
#घोषणा SRAM_CH25 4   /* audio */
#घोषणा SRAM_CH26 5
#घोषणा SRAM_CH28 6   /* mpeg */
#घोषणा SRAM_CH27 7   /* audio rds */
/* more */

काष्ठा sram_channel अणु
	स्थिर अक्षर *name;
	u32  cmds_start;
	u32  ctrl_start;
	u32  cdt;
	u32  fअगरo_start;
	u32  fअगरo_size;
	u32  ptr1_reg;
	u32  ptr2_reg;
	u32  cnt1_reg;
	u32  cnt2_reg;
पूर्ण;

बाह्य स्थिर काष्ठा sram_channel cx88_sram_channels[];

/* ----------------------------------------------------------- */
/* card configuration                                          */

#घोषणा CX88_BOARD_NOAUTO               UNSET
#घोषणा CX88_BOARD_UNKNOWN                  0
#घोषणा CX88_BOARD_HAUPPAUGE                1
#घोषणा CX88_BOARD_GDI                      2
#घोषणा CX88_BOARD_PIXELVIEW                3
#घोषणा CX88_BOARD_ATI_WONDER_PRO           4
#घोषणा CX88_BOARD_WINFAST2000XP_EXPERT     5
#घोषणा CX88_BOARD_AVERTV_STUDIO_303        6
#घोषणा CX88_BOARD_MSI_TVANYWHERE_MASTER    7
#घोषणा CX88_BOARD_WINFAST_DV2000           8
#घोषणा CX88_BOARD_LEADTEK_PVR2000          9
#घोषणा CX88_BOARD_IODATA_GVVCP3PCI        10
#घोषणा CX88_BOARD_PROLINK_PLAYTVPVR       11
#घोषणा CX88_BOARD_ASUS_PVR_416            12
#घोषणा CX88_BOARD_MSI_TVANYWHERE          13
#घोषणा CX88_BOARD_KWORLD_DVB_T            14
#घोषणा CX88_BOARD_DVICO_FUSIONHDTV_DVB_T1 15
#घोषणा CX88_BOARD_KWORLD_LTV883           16
#घोषणा CX88_BOARD_DVICO_FUSIONHDTV_3_GOLD_Q  17
#घोषणा CX88_BOARD_HAUPPAUGE_DVB_T1        18
#घोषणा CX88_BOARD_CONEXANT_DVB_T1         19
#घोषणा CX88_BOARD_PROVIDEO_PV259          20
#घोषणा CX88_BOARD_DVICO_FUSIONHDTV_DVB_T_PLUS 21
#घोषणा CX88_BOARD_PCHDTV_HD3000           22
#घोषणा CX88_BOARD_DNTV_LIVE_DVB_T         23
#घोषणा CX88_BOARD_HAUPPAUGE_ROSLYN        24
#घोषणा CX88_BOARD_DIGITALLOGIC_MEC        25
#घोषणा CX88_BOARD_IODATA_GVBCTV7E         26
#घोषणा CX88_BOARD_PIXELVIEW_PLAYTV_ULTRA_PRO 27
#घोषणा CX88_BOARD_DVICO_FUSIONHDTV_3_GOLD_T  28
#घोषणा CX88_BOARD_ADSTECH_DVB_T_PCI          29
#घोषणा CX88_BOARD_TERRATEC_CINERGY_1400_DVB_T1  30
#घोषणा CX88_BOARD_DVICO_FUSIONHDTV_5_GOLD 31
#घोषणा CX88_BOARD_AVERMEDIA_ULTRATV_MC_550 32
#घोषणा CX88_BOARD_KWORLD_VSTREAM_EXPERT_DVD 33
#घोषणा CX88_BOARD_ATI_HDTVWONDER          34
#घोषणा CX88_BOARD_WINFAST_DTV1000         35
#घोषणा CX88_BOARD_AVERTV_303              36
#घोषणा CX88_BOARD_HAUPPAUGE_NOVASPLUS_S1  37
#घोषणा CX88_BOARD_HAUPPAUGE_NOVASE2_S1    38
#घोषणा CX88_BOARD_KWORLD_DVBS_100         39
#घोषणा CX88_BOARD_HAUPPAUGE_HVR1100       40
#घोषणा CX88_BOARD_HAUPPAUGE_HVR1100LP     41
#घोषणा CX88_BOARD_DNTV_LIVE_DVB_T_PRO     42
#घोषणा CX88_BOARD_KWORLD_DVB_T_CX22702    43
#घोषणा CX88_BOARD_DVICO_FUSIONHDTV_DVB_T_DUAL 44
#घोषणा CX88_BOARD_KWORLD_HARDWARE_MPEG_TV_XPERT 45
#घोषणा CX88_BOARD_DVICO_FUSIONHDTV_DVB_T_HYBRID 46
#घोषणा CX88_BOARD_PCHDTV_HD5500           47
#घोषणा CX88_BOARD_KWORLD_MCE200_DELUXE    48
#घोषणा CX88_BOARD_PIXELVIEW_PLAYTV_P7000  49
#घोषणा CX88_BOARD_NPGTECH_REALTV_TOP10FM  50
#घोषणा CX88_BOARD_WINFAST_DTV2000H        51
#घोषणा CX88_BOARD_GENIATECH_DVBS          52
#घोषणा CX88_BOARD_HAUPPAUGE_HVR3000       53
#घोषणा CX88_BOARD_NORWOOD_MICRO           54
#घोषणा CX88_BOARD_TE_DTV_250_OEM_SWANN    55
#घोषणा CX88_BOARD_HAUPPAUGE_HVR1300       56
#घोषणा CX88_BOARD_ADSTECH_PTV_390         57
#घोषणा CX88_BOARD_PINNACLE_PCTV_HD_800i   58
#घोषणा CX88_BOARD_DVICO_FUSIONHDTV_5_PCI_न_अंकO 59
#घोषणा CX88_BOARD_PINNACLE_HYBRID_PCTV    60
#घोषणा CX88_BOARD_WINFAST_TV2000_XP_GLOBAL 61
#घोषणा CX88_BOARD_POWERCOLOR_REAL_ANGEL   62
#घोषणा CX88_BOARD_GENIATECH_X8000_MT      63
#घोषणा CX88_BOARD_DVICO_FUSIONHDTV_DVB_T_PRO 64
#घोषणा CX88_BOARD_DVICO_FUSIONHDTV_7_GOLD 65
#घोषणा CX88_BOARD_PROLINK_PV_8000GT       66
#घोषणा CX88_BOARD_KWORLD_ATSC_120         67
#घोषणा CX88_BOARD_HAUPPAUGE_HVR4000       68
#घोषणा CX88_BOARD_HAUPPAUGE_HVR4000LITE   69
#घोषणा CX88_BOARD_TEVII_S460              70
#घोषणा CX88_BOARD_OMICOM_SS4_PCI          71
#घोषणा CX88_BOARD_TBS_8920                72
#घोषणा CX88_BOARD_TEVII_S420              73
#घोषणा CX88_BOARD_PROLINK_PV_GLOBAL_XTREME 74
#घोषणा CX88_BOARD_PROF_7300               75
#घोषणा CX88_BOARD_SATTRADE_ST4200         76
#घोषणा CX88_BOARD_TBS_8910                77
#घोषणा CX88_BOARD_PROF_6200               78
#घोषणा CX88_BOARD_TERRATEC_CINERGY_HT_PCI_MKII 79
#घोषणा CX88_BOARD_HAUPPAUGE_IRONLY        80
#घोषणा CX88_BOARD_WINFAST_DTV1800H        81
#घोषणा CX88_BOARD_WINFAST_DTV2000H_J      82
#घोषणा CX88_BOARD_PROF_7301               83
#घोषणा CX88_BOARD_SAMSUNG_SMT_7020        84
#घोषणा CX88_BOARD_TWINHAN_VP1027_DVBS     85
#घोषणा CX88_BOARD_TEVII_S464              86
#घोषणा CX88_BOARD_WINFAST_DTV2000H_PLUS   87
#घोषणा CX88_BOARD_WINFAST_DTV1800H_XC4000 88
#घोषणा CX88_BOARD_WINFAST_TV2000_XP_GLOBAL_6F36 89
#घोषणा CX88_BOARD_WINFAST_TV2000_XP_GLOBAL_6F43 90
#घोषणा CX88_BOARD_NOTONLYTV_LV3H          91

क्रमागत cx88_itype अणु
	CX88_VMUX_COMPOSITE1 = 1,
	CX88_VMUX_COMPOSITE2,
	CX88_VMUX_COMPOSITE3,
	CX88_VMUX_COMPOSITE4,
	CX88_VMUX_SVIDEO,
	CX88_VMUX_TELEVISION,
	CX88_VMUX_CABLE,
	CX88_VMUX_DVB,
	CX88_VMUX_DEBUG,
	CX88_RADIO,
पूर्ण;

काष्ठा cx88_input अणु
	क्रमागत cx88_itype type;
	u32             gpio0, gpio1, gpio2, gpio3;
	अचिन्हित पूर्णांक    vmux:2;
	अचिन्हित पूर्णांक    audioroute:4;
पूर्ण;

क्रमागत cx88_audio_chip अणु
	CX88_AUDIO_WM8775 = 1,
	CX88_AUDIO_TVAUDIO,
पूर्ण;

काष्ठा cx88_board अणु
	स्थिर अक्षर              *name;
	अचिन्हित पूर्णांक            tuner_type;
	अचिन्हित पूर्णांक		radio_type;
	अचिन्हित अक्षर		tuner_addr;
	अचिन्हित अक्षर		radio_addr;
	पूर्णांक                     tda9887_conf;
	काष्ठा cx88_input       input[MAX_CX88_INPUT];
	काष्ठा cx88_input       radio;
	क्रमागत cx88_board_type    mpeg;
	क्रमागत cx88_audio_chip	audio_chip;
	पूर्णांक			num_frontends;

	/* Used क्रम I2S devices */
	पूर्णांक			i2sinअ_दोntl;
पूर्ण;

काष्ठा cx88_subid अणु
	u16     subvenकरोr;
	u16     subdevice;
	u32     card;
पूर्ण;

क्रमागत cx88_tvaudio अणु
	WW_NONE = 1,
	WW_BTSC,
	WW_BG,
	WW_DK,
	WW_I,
	WW_L,
	WW_EIAJ,
	WW_I2SPT,
	WW_FM,
	WW_I2SADC,
	WW_M
पूर्ण;

#घोषणा INPUT(nr) (core->board.input[nr])

/* ----------------------------------------------------------- */
/* device / file handle status                                 */

#घोषणा RESOURCE_OVERLAY       1
#घोषणा RESOURCE_VIDEO         2
#घोषणा RESOURCE_VBI           4

#घोषणा BUFFER_TIMEOUT     msecs_to_jअगरfies(2000)

काष्ठा cx88_riscmem अणु
	अचिन्हित पूर्णांक   size;
	__le32         *cpu;
	__le32         *jmp;
	dma_addr_t     dma;
पूर्ण;

/* buffer क्रम one video frame */
काष्ठा cx88_buffer अणु
	/* common v4l buffer stuff -- must be first */
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head       list;

	/* cx88 specअगरic */
	अचिन्हित पूर्णांक           bpl;
	काष्ठा cx88_riscmem    risc;
पूर्ण;

काष्ठा cx88_dmaqueue अणु
	काष्ठा list_head       active;
	u32                    count;
पूर्ण;

काष्ठा cx8800_dev;
काष्ठा cx8802_dev;

काष्ठा cx88_core अणु
	काष्ठा list_head           devlist;
	refcount_t		   refcount;

	/* board name */
	पूर्णांक                        nr;
	अक्षर                       name[32];
	u32			   model;

	/* pci stuff */
	पूर्णांक                        pci_bus;
	पूर्णांक                        pci_slot;
	u32                        __iomem *lmmio;
	u8                         __iomem *bmmio;
	u32                        shaकरोw[SHADOW_MAX];
	पूर्णांक                        pci_irqmask;

	/* i2c i/o */
	काष्ठा i2c_adapter         i2c_adap;
	काष्ठा i2c_algo_bit_data   i2c_algo;
	काष्ठा i2c_client          i2c_client;
	u32                        i2c_state, i2c_rc;

	/* config info -- analog */
	काष्ठा v4l2_device	   v4l2_dev;
	काष्ठा v4l2_ctrl_handler   video_hdl;
	काष्ठा v4l2_ctrl	   *chroma_agc;
	काष्ठा v4l2_ctrl_handler   audio_hdl;
	काष्ठा v4l2_subdev	   *sd_wm8775;
	काष्ठा i2c_client	   *i2c_rtc;
	अचिन्हित पूर्णांक               boardnr;
	काष्ठा cx88_board	   board;

	/* Supported V4L _STD_ tuner क्रमmats */
	अचिन्हित पूर्णांक               tuner_क्रमmats;

	/* config info -- dvb */
#अगर IS_ENABLED(CONFIG_VIDEO_CX88_DVB)
	पूर्णांक	(*prev_set_voltage)(काष्ठा dvb_frontend *fe,
				    क्रमागत fe_sec_voltage voltage);
#पूर्ण_अगर
	व्योम	(*gate_ctrl)(काष्ठा cx88_core *core, पूर्णांक खोलो);

	/* state info */
	काष्ठा task_काष्ठा         *kthपढ़ो;
	v4l2_std_id                tvnorm;
	अचिन्हित पूर्णांक		   width, height;
	अचिन्हित पूर्णांक		   field;
	क्रमागत cx88_tvaudio          tvaudio;
	u32                        audiomode_manual;
	u32                        audiomode_current;
	u32                        input;
	u32                        last_analog_input;
	u32                        astat;
	u32			   use_nicam;
	अचिन्हित दीर्घ		   last_change;

	/* IR remote control state */
	काष्ठा cx88_IR             *ir;

	/* I2C remote data */
	काष्ठा IR_i2c_init_data    init_data;
	काष्ठा wm8775_platक्रमm_data wm8775_data;

	काष्ठा mutex               lock;
	/* various v4l controls */
	u32                        freq;

	/*
	 * cx88-video needs to access cx8802 क्रम hybrid tuner pll access and
	 * क्रम vb2_is_busy() checks.
	 */
	काष्ठा cx8802_dev          *dvbdev;
	/* cx88-blackbird needs to access cx8800 क्रम vb2_is_busy() checks */
	काष्ठा cx8800_dev          *v4ldev;
	क्रमागत cx88_board_type       active_type_id;
	पूर्णांक			   active_ref;
	पूर्णांक			   active_fe_id;
पूर्ण;

अटल अंतरभूत काष्ठा cx88_core *to_core(काष्ठा v4l2_device *v4l2_dev)
अणु
	वापस container_of(v4l2_dev, काष्ठा cx88_core, v4l2_dev);
पूर्ण

#घोषणा call_hw(core, grpid, o, f, args...) \
	करो अणु							\
		अगर (!core->i2c_rc) अणु				\
			अगर (core->gate_ctrl)			\
				core->gate_ctrl(core, 1);	\
			v4l2_device_call_all(&core->v4l2_dev,	\
					     grpid, o, f, ##args); \
			अगर (core->gate_ctrl)			\
				core->gate_ctrl(core, 0);	\
		पूर्ण						\
	पूर्ण जबतक (0)

#घोषणा call_all(core, o, f, args...) call_hw(core, 0, o, f, ##args)

#घोषणा WM8775_GID      (1 << 0)

#घोषणा wm8775_s_ctrl(core, id, val) \
	करो अणु								\
		काष्ठा v4l2_ctrl *ctrl_ =				\
			v4l2_ctrl_find(core->sd_wm8775->ctrl_handler, id);\
		अगर (ctrl_ && !core->i2c_rc) अणु				\
			अगर (core->gate_ctrl)				\
				core->gate_ctrl(core, 1);		\
			v4l2_ctrl_s_ctrl(ctrl_, val);			\
			अगर (core->gate_ctrl)				\
				core->gate_ctrl(core, 0);		\
		पूर्ण							\
	पूर्ण जबतक (0)

#घोषणा wm8775_g_ctrl(core, id) \
	(अणु								\
		काष्ठा v4l2_ctrl *ctrl_ =				\
			v4l2_ctrl_find(core->sd_wm8775->ctrl_handler, id);\
		s32 val = 0;						\
		अगर (ctrl_ && !core->i2c_rc) अणु				\
			अगर (core->gate_ctrl)				\
				core->gate_ctrl(core, 1);		\
			val = v4l2_ctrl_g_ctrl(ctrl_);			\
			अगर (core->gate_ctrl)				\
				core->gate_ctrl(core, 0);		\
		पूर्ण							\
		val;							\
	पूर्ण)

/* ----------------------------------------------------------- */
/* function 0: video stuff                                     */

काष्ठा cx8800_suspend_state अणु
	पूर्णांक                        disabled;
पूर्ण;

काष्ठा cx8800_dev अणु
	काष्ठा cx88_core           *core;
	spinlock_t                 slock;

	/* various device info */
	अचिन्हित पूर्णांक               resources;
	काष्ठा video_device        video_dev;
	काष्ठा video_device        vbi_dev;
	काष्ठा video_device        radio_dev;

	/* pci i/o */
	काष्ठा pci_dev             *pci;
	अचिन्हित अक्षर              pci_rev, pci_lat;

	स्थिर काष्ठा cx8800_fmt    *fmt;

	/* capture queues */
	काष्ठा cx88_dmaqueue       vidq;
	काष्ठा vb2_queue           vb2_vidq;
	काष्ठा cx88_dmaqueue       vbiq;
	काष्ठा vb2_queue           vb2_vbiq;

	/* various v4l controls */

	/* other global state info */
	काष्ठा cx8800_suspend_state state;
पूर्ण;

/* ----------------------------------------------------------- */
/* function 1: audio/alsa stuff                                */
/* =============> moved to cx88-alsa.c <====================== */

/* ----------------------------------------------------------- */
/* function 2: mpeg stuff                                      */

काष्ठा cx8802_suspend_state अणु
	पूर्णांक                        disabled;
पूर्ण;

काष्ठा cx8802_driver अणु
	काष्ठा cx88_core *core;

	/* List of drivers attached to device */
	काष्ठा list_head drvlist;

	/* Type of driver and access required */
	क्रमागत cx88_board_type type_id;
	क्रमागत cx8802_board_access hw_access;

	/* MPEG 8802 पूर्णांकernal only */
	पूर्णांक (*suspend)(काष्ठा pci_dev *pci_dev, pm_message_t state);
	पूर्णांक (*resume)(काष्ठा pci_dev *pci_dev);

	/* Callers to the following functions must hold core->lock */

	/* MPEG 8802 -> mini driver - Driver probe and configuration */
	पूर्णांक (*probe)(काष्ठा cx8802_driver *drv);
	पूर्णांक (*हटाओ)(काष्ठा cx8802_driver *drv);

	/* MPEG 8802 -> mini driver - Access क्रम hardware control */
	पूर्णांक (*advise_acquire)(काष्ठा cx8802_driver *drv);
	पूर्णांक (*advise_release)(काष्ठा cx8802_driver *drv);

	/* MPEG 8802 <- mini driver - Access क्रम hardware control */
	पूर्णांक (*request_acquire)(काष्ठा cx8802_driver *drv);
	पूर्णांक (*request_release)(काष्ठा cx8802_driver *drv);
पूर्ण;

काष्ठा cx8802_dev अणु
	काष्ठा cx88_core           *core;
	spinlock_t                 slock;

	/* pci i/o */
	काष्ठा pci_dev             *pci;
	अचिन्हित अक्षर              pci_rev, pci_lat;

	/* dma queues */
	काष्ठा cx88_dmaqueue       mpegq;
	काष्ठा vb2_queue           vb2_mpegq;
	u32                        ts_packet_size;
	u32                        ts_packet_count;

	/* other global state info */
	काष्ठा cx8802_suspend_state state;

	/* क्रम blackbird only */
	काष्ठा list_head           devlist;
#अगर IS_ENABLED(CONFIG_VIDEO_CX88_BLACKBIRD)
	काष्ठा video_device        mpeg_dev;
	u32                        mailbox;

	/* mpeg params */
	काष्ठा cx2341x_handler     cxhdl;

#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_VIDEO_CX88_DVB)
	/* क्रम dvb only */
	काष्ठा vb2_dvb_frontends frontends;
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_VIDEO_CX88_VP3054)
	/* For VP3045 secondary I2C bus support */
	काष्ठा vp3054_i2c_state	   *vp3054;
#पूर्ण_अगर
	/* क्रम चयनing modulation types */
	अचिन्हित अक्षर              ts_gen_cntrl;

	/* List of attached drivers; must hold core->lock to access */
	काष्ठा list_head	   drvlist;

	काष्ठा work_काष्ठा	   request_module_wk;
पूर्ण;

/* ----------------------------------------------------------- */

#घोषणा cx_पढ़ो(reg)             पढ़ोl(core->lmmio + ((reg) >> 2))
#घोषणा cx_ग_लिखो(reg, value)     ग_लिखोl((value), core->lmmio + ((reg) >> 2))
#घोषणा cx_ग_लिखोb(reg, value)    ग_लिखोb((value), core->bmmio + (reg))

#घोषणा cx_anकरोr(reg, mask, value) \
	ग_लिखोl((पढ़ोl(core->lmmio + ((reg) >> 2)) & ~(mask)) |\
	((value) & (mask)), core->lmmio + ((reg) >> 2))
#घोषणा cx_set(reg, bit)         cx_anकरोr((reg), (bit), (bit))
#घोषणा cx_clear(reg, bit)       cx_anकरोr((reg), (bit), 0)

#घोषणा cx_रुको(d) अणु अगर (need_resched()) schedule(); अन्यथा udelay(d); पूर्ण

/* shaकरोw रेजिस्टरs */
#घोषणा cx_sपढ़ो(sreg)		    (core->shaकरोw[sreg])
#घोषणा cx_sग_लिखो(sreg, reg, value) \
	(core->shaकरोw[sreg] = value, \
	ग_लिखोl(core->shaकरोw[sreg], core->lmmio + ((reg) >> 2)))
#घोषणा cx_sanकरोr(sreg, reg, mask, value) \
	(core->shaकरोw[sreg] = (core->shaकरोw[sreg] & ~(mask)) | \
			       ((value) & (mask)), \
				ग_लिखोl(core->shaकरोw[sreg], \
				       core->lmmio + ((reg) >> 2)))

/* ----------------------------------------------------------- */
/* cx88-core.c                                                 */

बाह्य अचिन्हित पूर्णांक cx88_core_debug;

व्योम cx88_prपूर्णांक_irqbits(स्थिर अक्षर *tag, स्थिर अक्षर *strings[],
			पूर्णांक len, u32 bits, u32 mask);

पूर्णांक cx88_core_irq(काष्ठा cx88_core *core, u32 status);
व्योम cx88_wakeup(काष्ठा cx88_core *core,
		 काष्ठा cx88_dmaqueue *q, u32 count);
व्योम cx88_shutकरोwn(काष्ठा cx88_core *core);
पूर्णांक cx88_reset(काष्ठा cx88_core *core);

बाह्य पूर्णांक
cx88_risc_buffer(काष्ठा pci_dev *pci, काष्ठा cx88_riscmem *risc,
		 काष्ठा scatterlist *sglist,
		 अचिन्हित पूर्णांक top_offset, अचिन्हित पूर्णांक bottom_offset,
		 अचिन्हित पूर्णांक bpl, अचिन्हित पूर्णांक padding, अचिन्हित पूर्णांक lines);
बाह्य पूर्णांक
cx88_risc_databuffer(काष्ठा pci_dev *pci, काष्ठा cx88_riscmem *risc,
		     काष्ठा scatterlist *sglist, अचिन्हित पूर्णांक bpl,
		     अचिन्हित पूर्णांक lines, अचिन्हित पूर्णांक lpi);

व्योम cx88_risc_disयंत्र(काष्ठा cx88_core *core,
		      काष्ठा cx88_riscmem *risc);
पूर्णांक cx88_sram_channel_setup(काष्ठा cx88_core *core,
			    स्थिर काष्ठा sram_channel *ch,
			    अचिन्हित पूर्णांक bpl, u32 risc);
व्योम cx88_sram_channel_dump(काष्ठा cx88_core *core,
			    स्थिर काष्ठा sram_channel *ch);

पूर्णांक cx88_set_scale(काष्ठा cx88_core *core, अचिन्हित पूर्णांक width,
		   अचिन्हित पूर्णांक height, क्रमागत v4l2_field field);
पूर्णांक cx88_set_tvnorm(काष्ठा cx88_core *core, v4l2_std_id norm);

व्योम cx88_vdev_init(काष्ठा cx88_core *core,
		    काष्ठा pci_dev *pci,
		    काष्ठा video_device *vfd,
		    स्थिर काष्ठा video_device *ढाँचा_,
		    स्थिर अक्षर *type);
काष्ठा cx88_core *cx88_core_get(काष्ठा pci_dev *pci);
व्योम cx88_core_put(काष्ठा cx88_core *core,
		   काष्ठा pci_dev *pci);

पूर्णांक cx88_start_audio_dma(काष्ठा cx88_core *core);
पूर्णांक cx88_stop_audio_dma(काष्ठा cx88_core *core);

/* ----------------------------------------------------------- */
/* cx88-vbi.c                                                  */

/* Can be used as g_vbi_fmt, try_vbi_fmt and s_vbi_fmt */
पूर्णांक cx8800_vbi_fmt(काष्ठा file *file, व्योम *priv,
		   काष्ठा v4l2_क्रमmat *f);

व्योम cx8800_stop_vbi_dma(काष्ठा cx8800_dev *dev);
पूर्णांक cx8800_restart_vbi_queue(काष्ठा cx8800_dev *dev, काष्ठा cx88_dmaqueue *q);

बाह्य स्थिर काष्ठा vb2_ops cx8800_vbi_qops;

/* ----------------------------------------------------------- */
/* cx88-i2c.c                                                  */

पूर्णांक cx88_i2c_init(काष्ठा cx88_core *core, काष्ठा pci_dev *pci);

/* ----------------------------------------------------------- */
/* cx88-cards.c                                                */

पूर्णांक cx88_tuner_callback(व्योम *dev, पूर्णांक component, पूर्णांक command, पूर्णांक arg);
पूर्णांक cx88_get_resources(स्थिर काष्ठा cx88_core *core,
		       काष्ठा pci_dev *pci);
काष्ठा cx88_core *cx88_core_create(काष्ठा pci_dev *pci, पूर्णांक nr);
व्योम cx88_setup_xc3028(काष्ठा cx88_core *core, काष्ठा xc2028_ctrl *ctl);

/* ----------------------------------------------------------- */
/* cx88-tvaudio.c                                              */

व्योम cx88_set_tvaudio(काष्ठा cx88_core *core);
व्योम cx88_newstation(काष्ठा cx88_core *core);
व्योम cx88_get_stereo(काष्ठा cx88_core *core, काष्ठा v4l2_tuner *t);
व्योम cx88_set_stereo(काष्ठा cx88_core *core, u32 mode, पूर्णांक manual);
पूर्णांक cx88_audio_thपढ़ो(व्योम *data);

पूर्णांक cx8802_रेजिस्टर_driver(काष्ठा cx8802_driver *drv);
पूर्णांक cx8802_unरेजिस्टर_driver(काष्ठा cx8802_driver *drv);

/* Caller must hold core->lock */
काष्ठा cx8802_driver *cx8802_get_driver(काष्ठा cx8802_dev *dev,
					क्रमागत cx88_board_type btype);

/* ----------------------------------------------------------- */
/* cx88-dsp.c                                                  */

s32 cx88_dsp_detect_stereo_sap(काष्ठा cx88_core *core);

/* ----------------------------------------------------------- */
/* cx88-input.c                                                */

पूर्णांक cx88_ir_init(काष्ठा cx88_core *core, काष्ठा pci_dev *pci);
पूर्णांक cx88_ir_fini(काष्ठा cx88_core *core);
व्योम cx88_ir_irq(काष्ठा cx88_core *core);
पूर्णांक cx88_ir_start(काष्ठा cx88_core *core);
व्योम cx88_ir_stop(काष्ठा cx88_core *core);
व्योम cx88_i2c_init_ir(काष्ठा cx88_core *core);

/* ----------------------------------------------------------- */
/* cx88-mpeg.c                                                 */

पूर्णांक cx8802_buf_prepare(काष्ठा vb2_queue *q, काष्ठा cx8802_dev *dev,
		       काष्ठा cx88_buffer *buf);
व्योम cx8802_buf_queue(काष्ठा cx8802_dev *dev, काष्ठा cx88_buffer *buf);
व्योम cx8802_cancel_buffers(काष्ठा cx8802_dev *dev);
पूर्णांक cx8802_start_dma(काष्ठा cx8802_dev    *dev,
		     काष्ठा cx88_dmaqueue *q,
		     काष्ठा cx88_buffer   *buf);

/* ----------------------------------------------------------- */
/* cx88-video.c*/
पूर्णांक cx88_क्रमागत_input(काष्ठा cx88_core *core, काष्ठा v4l2_input *i);
पूर्णांक cx88_set_freq(काष्ठा cx88_core  *core, स्थिर काष्ठा v4l2_frequency *f);
पूर्णांक cx88_video_mux(काष्ठा cx88_core *core, अचिन्हित पूर्णांक input);
पूर्णांक cx88_querycap(काष्ठा file *file, काष्ठा cx88_core *core,
		  काष्ठा v4l2_capability *cap);

#पूर्ण_अगर
