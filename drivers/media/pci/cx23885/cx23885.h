<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Driver क्रम the Conexant CX23885 PCIe bridge
 *
 *  Copyright (c) 2006 Steven Toth <stoth@linuxtv.org>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/pci.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/slab.h>

#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/tuner.h>
#समावेश <media/tveeprom.h>
#समावेश <media/videobuf2-dma-sg.h>
#समावेश <media/videobuf2-dvb.h>
#समावेश <media/rc-core.h>

#समावेश "cx23885-reg.h"
#समावेश "media/drv-intf/cx2341x.h"

#समावेश <linux/mutex.h>

#घोषणा CX23885_VERSION "0.0.4"

#घोषणा UNSET (-1U)

#घोषणा CX23885_MAXBOARDS 8

/* Max number of inमाला_दो by card */
#घोषणा MAX_CX23885_INPUT 8
#घोषणा INPUT(nr) (&cx23885_boards[dev->board].input[nr])

#घोषणा BUFFER_TIMEOUT     (HZ)  /* 0.5 seconds */

#घोषणा CX23885_BOARD_NOAUTO               UNSET
#घोषणा CX23885_BOARD_UNKNOWN                  0
#घोषणा CX23885_BOARD_HAUPPAUGE_HVR1800lp      1
#घोषणा CX23885_BOARD_HAUPPAUGE_HVR1800        2
#घोषणा CX23885_BOARD_HAUPPAUGE_HVR1250        3
#घोषणा CX23885_BOARD_DVICO_FUSIONHDTV_5_EXP   4
#घोषणा CX23885_BOARD_HAUPPAUGE_HVR1500Q       5
#घोषणा CX23885_BOARD_HAUPPAUGE_HVR1500        6
#घोषणा CX23885_BOARD_HAUPPAUGE_HVR1200        7
#घोषणा CX23885_BOARD_HAUPPAUGE_HVR1700        8
#घोषणा CX23885_BOARD_HAUPPAUGE_HVR1400        9
#घोषणा CX23885_BOARD_DVICO_FUSIONHDTV_7_DUAL_EXP 10
#घोषणा CX23885_BOARD_DVICO_FUSIONHDTV_DVB_T_DUAL_EXP 11
#घोषणा CX23885_BOARD_LEADTEK_WINFAST_PXDVR3200_H 12
#घोषणा CX23885_BOARD_COMPRO_VIDEOMATE_E650F   13
#घोषणा CX23885_BOARD_TBS_6920                 14
#घोषणा CX23885_BOARD_TEVII_S470               15
#घोषणा CX23885_BOARD_DVBWORLD_2005            16
#घोषणा CX23885_BOARD_NETUP_DUAL_DVBS2_CI      17
#घोषणा CX23885_BOARD_HAUPPAUGE_HVR1270        18
#घोषणा CX23885_BOARD_HAUPPAUGE_HVR1275        19
#घोषणा CX23885_BOARD_HAUPPAUGE_HVR1255        20
#घोषणा CX23885_BOARD_HAUPPAUGE_HVR1210        21
#घोषणा CX23885_BOARD_MYGICA_X8506             22
#घोषणा CX23885_BOARD_MAGICPRO_PROHDTVE2       23
#घोषणा CX23885_BOARD_HAUPPAUGE_HVR1850        24
#घोषणा CX23885_BOARD_COMPRO_VIDEOMATE_E800    25
#घोषणा CX23885_BOARD_HAUPPAUGE_HVR1290        26
#घोषणा CX23885_BOARD_MYGICA_X8558PRO          27
#घोषणा CX23885_BOARD_LEADTEK_WINFAST_PXTV1200 28
#घोषणा CX23885_BOARD_GOTVIEW_X5_3D_HYBRID     29
#घोषणा CX23885_BOARD_NETUP_DUAL_DVB_T_C_CI_RF 30
#घोषणा CX23885_BOARD_LEADTEK_WINFAST_PXDVR3200_H_XC4000 31
#घोषणा CX23885_BOARD_MPX885                   32
#घोषणा CX23885_BOARD_MYGICA_X8507             33
#घोषणा CX23885_BOARD_TERRATEC_CINERGY_T_PCIE_DUAL 34
#घोषणा CX23885_BOARD_TEVII_S471               35
#घोषणा CX23885_BOARD_HAUPPAUGE_HVR1255_22111  36
#घोषणा CX23885_BOARD_PROF_8000                37
#घोषणा CX23885_BOARD_HAUPPAUGE_HVR4400        38
#घोषणा CX23885_BOARD_AVERMEDIA_HC81R          39
#घोषणा CX23885_BOARD_TBS_6981                 40
#घोषणा CX23885_BOARD_TBS_6980                 41
#घोषणा CX23885_BOARD_LEADTEK_WINFAST_PXPVR2200 42
#घोषणा CX23885_BOARD_HAUPPAUGE_IMPACTVCBE     43
#घोषणा CX23885_BOARD_DVICO_FUSIONHDTV_DVB_T_DUAL_EXP2 44
#घोषणा CX23885_BOARD_DVBSKY_T9580             45
#घोषणा CX23885_BOARD_DVBSKY_T980C             46
#घोषणा CX23885_BOARD_DVBSKY_S950C             47
#घोषणा CX23885_BOARD_TT_CT2_4500_CI           48
#घोषणा CX23885_BOARD_DVBSKY_S950              49
#घोषणा CX23885_BOARD_DVBSKY_S952              50
#घोषणा CX23885_BOARD_DVBSKY_T982              51
#घोषणा CX23885_BOARD_HAUPPAUGE_HVR5525        52
#घोषणा CX23885_BOARD_HAUPPAUGE_STARBURST      53
#घोषणा CX23885_BOARD_VIEWCAST_260E            54
#घोषणा CX23885_BOARD_VIEWCAST_460E            55
#घोषणा CX23885_BOARD_HAUPPAUGE_QUADHD_DVB     56
#घोषणा CX23885_BOARD_HAUPPAUGE_QUADHD_ATSC    57
#घोषणा CX23885_BOARD_HAUPPAUGE_HVR1265_K4     58
#घोषणा CX23885_BOARD_HAUPPAUGE_STARBURST2     59
#घोषणा CX23885_BOARD_HAUPPAUGE_QUADHD_DVB_885 60
#घोषणा CX23885_BOARD_HAUPPAUGE_QUADHD_ATSC_885 61
#घोषणा CX23885_BOARD_AVERMEDIA_CE310B         62

#घोषणा GPIO_0 0x00000001
#घोषणा GPIO_1 0x00000002
#घोषणा GPIO_2 0x00000004
#घोषणा GPIO_3 0x00000008
#घोषणा GPIO_4 0x00000010
#घोषणा GPIO_5 0x00000020
#घोषणा GPIO_6 0x00000040
#घोषणा GPIO_7 0x00000080
#घोषणा GPIO_8 0x00000100
#घोषणा GPIO_9 0x00000200
#घोषणा GPIO_10 0x00000400
#घोषणा GPIO_11 0x00000800
#घोषणा GPIO_12 0x00001000
#घोषणा GPIO_13 0x00002000
#घोषणा GPIO_14 0x00004000
#घोषणा GPIO_15 0x00008000

/* Currently unsupported by the driver: PAL/H, NTSC/Kr, SECAM B/G/H/LC */
#घोषणा CX23885_NORMS (\
	V4L2_STD_NTSC_M |  V4L2_STD_NTSC_M_JP |  V4L2_STD_NTSC_443 | \
	V4L2_STD_PAL_BG |  V4L2_STD_PAL_DK    |  V4L2_STD_PAL_I    | \
	V4L2_STD_PAL_M  |  V4L2_STD_PAL_N     |  V4L2_STD_PAL_Nc   | \
	V4L2_STD_PAL_60 |  V4L2_STD_SECAM_L   |  V4L2_STD_SECAM_DK)

काष्ठा cx23885_fmt अणु
	u32   fourcc;          /* v4l2 क्रमmat id */
	पूर्णांक   depth;
	पूर्णांक   flags;
	u32   cxक्रमmat;
पूर्ण;

काष्ठा cx23885_tvnorm अणु
	अक्षर		*name;
	v4l2_std_id	id;
	u32		cxअगरormat;
	u32		cxoक्रमmat;
पूर्ण;

क्रमागत cx23885_itype अणु
	CX23885_VMUX_COMPOSITE1 = 1,
	CX23885_VMUX_COMPOSITE2,
	CX23885_VMUX_COMPOSITE3,
	CX23885_VMUX_COMPOSITE4,
	CX23885_VMUX_SVIDEO,
	CX23885_VMUX_COMPONENT,
	CX23885_VMUX_TELEVISION,
	CX23885_VMUX_CABLE,
	CX23885_VMUX_DVB,
	CX23885_VMUX_DEBUG,
	CX23885_RADIO,
पूर्ण;

क्रमागत cx23885_src_sel_type अणु
	CX23885_SRC_SEL_EXT_656_VIDEO = 0,
	CX23885_SRC_SEL_PARALLEL_MPEG_VIDEO
पूर्ण;

काष्ठा cx23885_riscmem अणु
	अचिन्हित पूर्णांक   size;
	__le32         *cpu;
	__le32         *jmp;
	dma_addr_t     dma;
पूर्ण;

/* buffer क्रम one video frame */
काष्ठा cx23885_buffer अणु
	/* common v4l buffer stuff -- must be first */
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head queue;

	/* cx23885 specअगरic */
	अचिन्हित पूर्णांक           bpl;
	काष्ठा cx23885_riscmem risc;
	काष्ठा cx23885_fmt     *fmt;
	u32                    count;
पूर्ण;

काष्ठा cx23885_input अणु
	क्रमागत cx23885_itype type;
	अचिन्हित पूर्णांक    vmux;
	अचिन्हित पूर्णांक    amux;
	u32             gpio0, gpio1, gpio2, gpio3;
पूर्ण;

प्रकार क्रमागत अणु
	CX23885_MPEG_UNDEFINED = 0,
	CX23885_MPEG_DVB,
	CX23885_ANALOG_VIDEO,
	CX23885_MPEG_ENCODER,
पूर्ण port_t;

काष्ठा cx23885_board अणु
	अक्षर                    *name;
	port_t			porta, portb, portc;
	पूर्णांक		num_fds_portb, num_fds_portc;
	अचिन्हित पूर्णांक		tuner_type;
	अचिन्हित पूर्णांक		radio_type;
	अचिन्हित अक्षर		tuner_addr;
	अचिन्हित अक्षर		radio_addr;
	अचिन्हित पूर्णांक		tuner_bus;

	/* Venकरोrs can and करो run the PCIe bridge at dअगरferent
	 * घड़ी rates, driven physically by crystals on the PCBs.
	 * The core has to accommodate this. This allows the user
	 * to add new boards with new frequencys. The value is
	 * expressed in Hz.
	 *
	 * The core framework will शेष this value based on
	 * current designs, but it can vary.
	 */
	u32			clk_freq;
	काष्ठा cx23885_input    input[MAX_CX23885_INPUT];
	पूर्णांक			ci_type; /* क्रम NetUP */
	/* Force bottom field first during DMA (888 workaround) */
	u32                     क्रमce_bff;
पूर्ण;

काष्ठा cx23885_subid अणु
	u16     subvenकरोr;
	u16     subdevice;
	u32     card;
पूर्ण;

काष्ठा cx23885_i2c अणु
	काष्ठा cx23885_dev *dev;

	पूर्णांक                        nr;

	/* i2c i/o */
	काष्ठा i2c_adapter         i2c_adap;
	काष्ठा i2c_client          i2c_client;
	u32                        i2c_rc;

	/* 885 रेजिस्टरs used क्रम raw address */
	u32                        i2c_period;
	u32                        reg_ctrl;
	u32                        reg_stat;
	u32                        reg_addr;
	u32                        reg_rdata;
	u32                        reg_wdata;
पूर्ण;

काष्ठा cx23885_dmaqueue अणु
	काष्ठा list_head       active;
	u32                    count;
पूर्ण;

काष्ठा cx23885_tsport अणु
	काष्ठा cx23885_dev *dev;

	अचिन्हित                   nr;
	पूर्णांक                        sram_chno;

	काष्ठा vb2_dvb_frontends   frontends;

	/* dma queues */
	काष्ठा cx23885_dmaqueue    mpegq;
	u32                        ts_packet_size;
	u32                        ts_packet_count;

	पूर्णांक                        width;
	पूर्णांक                        height;

	spinlock_t                 slock;

	/* रेजिस्टरs */
	u32                        reg_gpcnt;
	u32                        reg_gpcnt_ctl;
	u32                        reg_dma_ctl;
	u32                        reg_lngth;
	u32                        reg_hw_sop_ctrl;
	u32                        reg_gen_ctrl;
	u32                        reg_bd_pkt_status;
	u32                        reg_sop_status;
	u32                        reg_fअगरo_ovfl_stat;
	u32                        reg_vld_misc;
	u32                        reg_ts_clk_en;
	u32                        reg_ts_पूर्णांक_msk;
	u32                        reg_ts_पूर्णांक_stat;
	u32                        reg_src_sel;

	/* Default रेजिस्टर vals */
	पूर्णांक                        pci_irqmask;
	u32                        dma_ctl_val;
	u32                        ts_पूर्णांक_msk_val;
	u32                        gen_ctrl_val;
	u32                        ts_clk_en_val;
	u32                        src_sel_val;
	u32                        vld_misc_val;
	u32                        hw_sop_ctrl_val;

	/* Allow a single tsport to have multiple frontends */
	u32                        num_frontends;
	व्योम                (*gate_ctrl)(काष्ठा cx23885_tsport *port, पूर्णांक खोलो);
	व्योम                       *port_priv;

	/* Workaround क्रम a temp dvb_frontend that the tuner can attached to */
	काष्ठा dvb_frontend analog_fe;

	काष्ठा i2c_client *i2c_client_demod;
	काष्ठा i2c_client *i2c_client_tuner;
	काष्ठा i2c_client *i2c_client_sec;
	काष्ठा i2c_client *i2c_client_ci;

	पूर्णांक (*set_frontend)(काष्ठा dvb_frontend *fe);
	पूर्णांक (*fe_set_voltage)(काष्ठा dvb_frontend *fe,
			      क्रमागत fe_sec_voltage voltage);
पूर्ण;

काष्ठा cx23885_kernel_ir अणु
	काष्ठा cx23885_dev	*cx;
	अक्षर			*name;
	अक्षर			*phys;

	काष्ठा rc_dev		*rc;
पूर्ण;

काष्ठा cx23885_audio_buffer अणु
	अचिन्हित पूर्णांक		bpl;
	काष्ठा cx23885_riscmem	risc;
	व्योम			*vaddr;
	काष्ठा scatterlist	*sglist;
	पूर्णांक			sglen;
	अचिन्हित दीर्घ		nr_pages;
पूर्ण;

काष्ठा cx23885_audio_dev अणु
	काष्ठा cx23885_dev	*dev;

	काष्ठा pci_dev		*pci;

	काष्ठा snd_card		*card;

	spinlock_t		lock;

	atomic_t		count;

	अचिन्हित पूर्णांक		dma_size;
	अचिन्हित पूर्णांक		period_size;
	अचिन्हित पूर्णांक		num_periods;

	काष्ठा cx23885_audio_buffer   *buf;

	काष्ठा snd_pcm_substream *substream;
पूर्ण;

काष्ठा cx23885_dev अणु
	atomic_t                   refcount;
	काष्ठा v4l2_device	   v4l2_dev;
	काष्ठा v4l2_ctrl_handler   ctrl_handler;

	/* pci stuff */
	काष्ठा pci_dev             *pci;
	अचिन्हित अक्षर              pci_rev, pci_lat;
	पूर्णांक                        pci_bus, pci_slot;
	u32                        __iomem *lmmio;
	u8                         __iomem *bmmio;
	पूर्णांक                        pci_irqmask;
	spinlock_t		   pci_irqmask_lock; /* protects mask reg too */
	पूर्णांक                        hwrevision;

	/* This valud is board specअगरic and is used to configure the
	 * AV core so we see nice clean and stable video and audio. */
	u32                        clk_freq;

	/* I2C adapters: Master 1 & 2 (External) & Master 3 (Internal only) */
	काष्ठा cx23885_i2c         i2c_bus[3];

	पूर्णांक                        nr;
	काष्ठा mutex               lock;
	काष्ठा mutex               gpio_lock;

	/* board details */
	अचिन्हित पूर्णांक               board;
	अक्षर                       name[32];

	काष्ठा cx23885_tsport      ts1, ts2;

	/* sram configuration */
	काष्ठा sram_channel        *sram_channels;

	क्रमागत अणु
		CX23885_BRIDGE_UNDEFINED = 0,
		CX23885_BRIDGE_885 = 885,
		CX23885_BRIDGE_887 = 887,
		CX23885_BRIDGE_888 = 888,
	पूर्ण bridge;

	/* Analog video */
	अचिन्हित पूर्णांक               input;
	अचिन्हित पूर्णांक               audinput; /* Selectable audio input */
	u32                        tvaudio;
	v4l2_std_id                tvnorm;
	अचिन्हित पूर्णांक               tuner_type;
	अचिन्हित अक्षर              tuner_addr;
	अचिन्हित पूर्णांक               tuner_bus;
	अचिन्हित पूर्णांक               radio_type;
	अचिन्हित अक्षर              radio_addr;
	काष्ठा v4l2_subdev	   *sd_cx25840;
	काष्ठा work_काष्ठा	   cx25840_work;

	/* Infrared */
	काष्ठा v4l2_subdev         *sd_ir;
	काष्ठा work_काष्ठा	   ir_rx_work;
	अचिन्हित दीर्घ		   ir_rx_notअगरications;
	काष्ठा work_काष्ठा	   ir_tx_work;
	अचिन्हित दीर्घ		   ir_tx_notअगरications;

	काष्ठा cx23885_kernel_ir   *kernel_ir;
	atomic_t		   ir_input_stopping;

	/* V4l */
	u32                        freq;
	काष्ठा video_device        *video_dev;
	काष्ठा video_device        *vbi_dev;

	/* video capture */
	काष्ठा cx23885_fmt         *fmt;
	अचिन्हित पूर्णांक               width, height;
	अचिन्हित		   field;

	काष्ठा cx23885_dmaqueue    vidq;
	काष्ठा vb2_queue           vb2_vidq;
	काष्ठा cx23885_dmaqueue    vbiq;
	काष्ठा vb2_queue           vb2_vbiq;

	spinlock_t                 slock;

	/* MPEG Encoder ONLY settings */
	u32                        cx23417_mailbox;
	काष्ठा cx2341x_handler     cxhdl;
	काष्ठा video_device        *v4l_device;
	काष्ठा vb2_queue           vb2_mpegq;
	काष्ठा cx23885_tvnorm      encodernorm;

	/* Analog raw audio */
	काष्ठा cx23885_audio_dev   *audio_dev;

	/* Does the प्रणाली require periodic DMA resets? */
	अचिन्हित पूर्णांक		need_dma_reset:1;
पूर्ण;

अटल अंतरभूत काष्ठा cx23885_dev *to_cx23885(काष्ठा v4l2_device *v4l2_dev)
अणु
	वापस container_of(v4l2_dev, काष्ठा cx23885_dev, v4l2_dev);
पूर्ण

#घोषणा call_all(dev, o, f, args...) \
	v4l2_device_call_all(&dev->v4l2_dev, 0, o, f, ##args)

#घोषणा CX23885_HW_888_IR  (1 << 0)
#घोषणा CX23885_HW_AV_CORE (1 << 1)

#घोषणा call_hw(dev, grpid, o, f, args...) \
	v4l2_device_call_all(&dev->v4l2_dev, grpid, o, f, ##args)

बाह्य काष्ठा v4l2_subdev *cx23885_find_hw(काष्ठा cx23885_dev *dev, u32 hw);

#घोषणा SRAM_CH01  0 /* Video A */
#घोषणा SRAM_CH02  1 /* VBI A */
#घोषणा SRAM_CH03  2 /* Video B */
#घोषणा SRAM_CH04  3 /* Transport via B */
#घोषणा SRAM_CH05  4 /* VBI B */
#घोषणा SRAM_CH06  5 /* Video C */
#घोषणा SRAM_CH07  6 /* Transport via C */
#घोषणा SRAM_CH08  7 /* Audio Internal A */
#घोषणा SRAM_CH09  8 /* Audio Internal B */
#घोषणा SRAM_CH10  9 /* Audio External */
#घोषणा SRAM_CH11 10 /* COMB_3D_N */
#घोषणा SRAM_CH12 11 /* Comb 3D N1 */
#घोषणा SRAM_CH13 12 /* Comb 3D N2 */
#घोषणा SRAM_CH14 13 /* MOE Vid */
#घोषणा SRAM_CH15 14 /* MOE RSLT */

काष्ठा sram_channel अणु
	अक्षर *name;
	u32  cmds_start;
	u32  ctrl_start;
	u32  cdt;
	u32  fअगरo_start;
	u32  fअगरo_size;
	u32  ptr1_reg;
	u32  ptr2_reg;
	u32  cnt1_reg;
	u32  cnt2_reg;
	u32  jumponly;
पूर्ण;

/* ----------------------------------------------------------- */

#घोषणा cx_पढ़ो(reg)             पढ़ोl(dev->lmmio + ((reg)>>2))
#घोषणा cx_ग_लिखो(reg, value)     ग_लिखोl((value), dev->lmmio + ((reg)>>2))

#घोषणा cx_anकरोr(reg, mask, value) \
  ग_लिखोl((पढ़ोl(dev->lmmio+((reg)>>2)) & ~(mask)) |\
  ((value) & (mask)), dev->lmmio+((reg)>>2))

#घोषणा cx_set(reg, bit)          cx_anकरोr((reg), (bit), (bit))
#घोषणा cx_clear(reg, bit)        cx_anकरोr((reg), (bit), 0)

/* ----------------------------------------------------------- */
/* cx23885-core.c                                              */

बाह्य पूर्णांक cx23885_sram_channel_setup(काष्ठा cx23885_dev *dev,
	काष्ठा sram_channel *ch,
	अचिन्हित पूर्णांक bpl, u32 risc);

बाह्य व्योम cx23885_sram_channel_dump(काष्ठा cx23885_dev *dev,
	काष्ठा sram_channel *ch);

बाह्य पूर्णांक cx23885_risc_buffer(काष्ठा pci_dev *pci, काष्ठा cx23885_riscmem *risc,
	काष्ठा scatterlist *sglist,
	अचिन्हित पूर्णांक top_offset, अचिन्हित पूर्णांक bottom_offset,
	अचिन्हित पूर्णांक bpl, अचिन्हित पूर्णांक padding, अचिन्हित पूर्णांक lines);

बाह्य पूर्णांक cx23885_risc_vbibuffer(काष्ठा pci_dev *pci,
	काष्ठा cx23885_riscmem *risc, काष्ठा scatterlist *sglist,
	अचिन्हित पूर्णांक top_offset, अचिन्हित पूर्णांक bottom_offset,
	अचिन्हित पूर्णांक bpl, अचिन्हित पूर्णांक padding, अचिन्हित पूर्णांक lines);

पूर्णांक cx23885_start_dma(काष्ठा cx23885_tsport *port,
			     काष्ठा cx23885_dmaqueue *q,
			     काष्ठा cx23885_buffer   *buf);
व्योम cx23885_cancel_buffers(काष्ठा cx23885_tsport *port);


बाह्य व्योम cx23885_gpio_set(काष्ठा cx23885_dev *dev, u32 mask);
बाह्य व्योम cx23885_gpio_clear(काष्ठा cx23885_dev *dev, u32 mask);
बाह्य u32 cx23885_gpio_get(काष्ठा cx23885_dev *dev, u32 mask);
बाह्य व्योम cx23885_gpio_enable(काष्ठा cx23885_dev *dev, u32 mask,
	पूर्णांक asoutput);

बाह्य व्योम cx23885_irq_add_enable(काष्ठा cx23885_dev *dev, u32 mask);
बाह्य व्योम cx23885_irq_enable(काष्ठा cx23885_dev *dev, u32 mask);
बाह्य व्योम cx23885_irq_disable(काष्ठा cx23885_dev *dev, u32 mask);
बाह्य व्योम cx23885_irq_हटाओ(काष्ठा cx23885_dev *dev, u32 mask);

/* ----------------------------------------------------------- */
/* cx23885-cards.c                                             */
बाह्य काष्ठा cx23885_board cx23885_boards[];
बाह्य स्थिर अचिन्हित पूर्णांक cx23885_bcount;

बाह्य काष्ठा cx23885_subid cx23885_subids[];
बाह्य स्थिर अचिन्हित पूर्णांक cx23885_idcount;

बाह्य पूर्णांक cx23885_tuner_callback(व्योम *priv, पूर्णांक component,
	पूर्णांक command, पूर्णांक arg);
बाह्य व्योम cx23885_card_list(काष्ठा cx23885_dev *dev);
बाह्य पूर्णांक  cx23885_ir_init(काष्ठा cx23885_dev *dev);
बाह्य व्योम cx23885_ir_pci_पूर्णांक_enable(काष्ठा cx23885_dev *dev);
बाह्य व्योम cx23885_ir_fini(काष्ठा cx23885_dev *dev);
बाह्य व्योम cx23885_gpio_setup(काष्ठा cx23885_dev *dev);
बाह्य व्योम cx23885_card_setup(काष्ठा cx23885_dev *dev);
बाह्य व्योम cx23885_card_setup_pre_i2c(काष्ठा cx23885_dev *dev);

बाह्य पूर्णांक cx23885_dvb_रेजिस्टर(काष्ठा cx23885_tsport *port);
बाह्य पूर्णांक cx23885_dvb_unरेजिस्टर(काष्ठा cx23885_tsport *port);

बाह्य पूर्णांक cx23885_buf_prepare(काष्ठा cx23885_buffer *buf,
			       काष्ठा cx23885_tsport *port);
बाह्य व्योम cx23885_buf_queue(काष्ठा cx23885_tsport *port,
			      काष्ठा cx23885_buffer *buf);
बाह्य व्योम cx23885_मुक्त_buffer(काष्ठा cx23885_dev *dev,
				काष्ठा cx23885_buffer *buf);

/* ----------------------------------------------------------- */
/* cx23885-video.c                                             */
/* Video */
बाह्य पूर्णांक cx23885_video_रेजिस्टर(काष्ठा cx23885_dev *dev);
बाह्य व्योम cx23885_video_unरेजिस्टर(काष्ठा cx23885_dev *dev);
बाह्य पूर्णांक cx23885_video_irq(काष्ठा cx23885_dev *dev, u32 status);
बाह्य व्योम cx23885_video_wakeup(काष्ठा cx23885_dev *dev,
	काष्ठा cx23885_dmaqueue *q, u32 count);
पूर्णांक cx23885_क्रमागत_input(काष्ठा cx23885_dev *dev, काष्ठा v4l2_input *i);
पूर्णांक cx23885_set_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i);
पूर्णांक cx23885_get_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i);
पूर्णांक cx23885_set_frequency(काष्ठा file *file, व्योम *priv, स्थिर काष्ठा v4l2_frequency *f);
पूर्णांक cx23885_set_tvnorm(काष्ठा cx23885_dev *dev, v4l2_std_id norm);

/* ----------------------------------------------------------- */
/* cx23885-vbi.c                                               */
बाह्य पूर्णांक cx23885_vbi_fmt(काष्ठा file *file, व्योम *priv,
	काष्ठा v4l2_क्रमmat *f);
बाह्य व्योम cx23885_vbi_समयout(अचिन्हित दीर्घ data);
बाह्य स्थिर काष्ठा vb2_ops cx23885_vbi_qops;
बाह्य पूर्णांक cx23885_vbi_irq(काष्ठा cx23885_dev *dev, u32 status);

/* cx23885-i2c.c                                                */
बाह्य पूर्णांक cx23885_i2c_रेजिस्टर(काष्ठा cx23885_i2c *bus);
बाह्य पूर्णांक cx23885_i2c_unरेजिस्टर(काष्ठा cx23885_i2c *bus);
बाह्य व्योम cx23885_av_clk(काष्ठा cx23885_dev *dev, पूर्णांक enable);

/* ----------------------------------------------------------- */
/* cx23885-417.c                                               */
बाह्य पूर्णांक cx23885_417_रेजिस्टर(काष्ठा cx23885_dev *dev);
बाह्य व्योम cx23885_417_unरेजिस्टर(काष्ठा cx23885_dev *dev);
बाह्य पूर्णांक cx23885_irq_417(काष्ठा cx23885_dev *dev, u32 status);
बाह्य व्योम cx23885_417_check_encoder(काष्ठा cx23885_dev *dev);
बाह्य व्योम cx23885_mc417_init(काष्ठा cx23885_dev *dev);
बाह्य पूर्णांक mc417_memory_पढ़ो(काष्ठा cx23885_dev *dev, u32 address, u32 *value);
बाह्य पूर्णांक mc417_memory_ग_लिखो(काष्ठा cx23885_dev *dev, u32 address, u32 value);
बाह्य पूर्णांक mc417_रेजिस्टर_पढ़ो(काष्ठा cx23885_dev *dev,
				u16 address, u32 *value);
बाह्य पूर्णांक mc417_रेजिस्टर_ग_लिखो(काष्ठा cx23885_dev *dev,
				u16 address, u32 value);
बाह्य व्योम mc417_gpio_set(काष्ठा cx23885_dev *dev, u32 mask);
बाह्य व्योम mc417_gpio_clear(काष्ठा cx23885_dev *dev, u32 mask);
बाह्य व्योम mc417_gpio_enable(काष्ठा cx23885_dev *dev, u32 mask, पूर्णांक asoutput);

/* ----------------------------------------------------------- */
/* cx23885-alsa.c                                             */
बाह्य काष्ठा cx23885_audio_dev *cx23885_audio_रेजिस्टर(
					काष्ठा cx23885_dev *dev);
बाह्य व्योम cx23885_audio_unरेजिस्टर(काष्ठा cx23885_dev *dev);
बाह्य पूर्णांक cx23885_audio_irq(काष्ठा cx23885_dev *dev, u32 status, u32 mask);
बाह्य पूर्णांक cx23885_risc_databuffer(काष्ठा pci_dev *pci,
				   काष्ठा cx23885_riscmem *risc,
				   काष्ठा scatterlist *sglist,
				   अचिन्हित पूर्णांक bpl,
				   अचिन्हित पूर्णांक lines,
				   अचिन्हित पूर्णांक lpi);

/* ----------------------------------------------------------- */
/* tv norms                                                    */

अटल अंतरभूत अचिन्हित पूर्णांक norm_maxh(v4l2_std_id norm)
अणु
	वापस (norm & V4L2_STD_525_60) ? 480 : 576;
पूर्ण
