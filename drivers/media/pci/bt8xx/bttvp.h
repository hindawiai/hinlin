<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*

    bttv - Bt848 frame grabber driver

    bttv's *निजी* header file  --  nobody other than bttv itself
    should ever include this file.

    (c) 2000-2002 Gerd Knorr <kraxel@bytesex.org>

*/

#अगर_अघोषित _BTTVP_H_
#घोषणा _BTTVP_H_

#समावेश <linux/types.h>
#समावेश <linux/रुको.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश <linux/pci.h>
#समावेश <linux/input.h>
#समावेश <linux/mutex.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/device.h>
#समावेश <यंत्र/पन.स>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/videobuf-dma-sg.h>
#समावेश <media/tveeprom.h>
#समावेश <media/rc-core.h>
#समावेश <media/i2c/ir-kbd-i2c.h>
#समावेश <media/drv-पूर्णांकf/tea575x.h>

#समावेश "bt848.h"
#समावेश "bttv.h"
#समावेश "btcx-risc.h"

#अगर_घोषित __KERNEL__

#घोषणा FORMAT_FLAGS_DITHER       0x01
#घोषणा FORMAT_FLAGS_PACKED       0x02
#घोषणा FORMAT_FLAGS_PLANAR       0x04
#घोषणा FORMAT_FLAGS_RAW          0x08
#घोषणा FORMAT_FLAGS_CrCb         0x10

#घोषणा RISC_SLOT_O_VBI        4
#घोषणा RISC_SLOT_O_FIELD      6
#घोषणा RISC_SLOT_E_VBI       10
#घोषणा RISC_SLOT_E_FIELD     12
#घोषणा RISC_SLOT_LOOP        14

#घोषणा RESOURCE_OVERLAY       1
#घोषणा RESOURCE_VIDEO_STREAM  2
#घोषणा RESOURCE_VBI           4
#घोषणा RESOURCE_VIDEO_READ    8

#घोषणा RAW_LINES            640
#घोषणा RAW_BPL             1024

#घोषणा UNSET (-1U)

/* Min. value in VDELAY रेजिस्टर. */
#घोषणा MIN_VDELAY 2
/* Even to get Cb first, odd क्रम Cr. */
#घोषणा MAX_HDELAY (0x3FF & -2)
/* Limits scaled width, which must be a multiple of 4. */
#घोषणा MAX_HACTIVE (0x3FF & -4)

#घोषणा BTTV_NORMS    (\
		V4L2_STD_PAL    | V4L2_STD_PAL_N | \
		V4L2_STD_PAL_Nc | V4L2_STD_SECAM | \
		V4L2_STD_NTSC   | V4L2_STD_PAL_M | \
		V4L2_STD_PAL_60)
/* ---------------------------------------------------------- */

काष्ठा bttv_tvnorm अणु
	पूर्णांक   v4l2_id;
	अक्षर  *name;
	u32   Fsc;
	u16   swidth, sheight; /* scaled standard width, height */
	u16   totalwidth;
	u8    adelay, bdelay, अगरorm;
	u32   scaledtwidth;
	u16   hdelayx1, hactivex1;
	u16   vdelay;
	u8    vbipack;
	u16   vtotal;
	पूर्णांक   sram;
	/* ITU-R frame line number of the first VBI line we can
	   capture, of the first and second field. The last possible line
	   is determined by cropcap.bounds. */
	u16   vbistart[2];
	/* Horizontally this counts fCLKx1 samples following the leading
	   edge of the horizontal sync pulse, vertically ITU-R frame line
	   numbers of the first field बार two (2, 4, 6, ... 524 or 624). */
	काष्ठा v4l2_cropcap cropcap;
पूर्ण;
बाह्य स्थिर काष्ठा bttv_tvnorm bttv_tvnorms[];

काष्ठा bttv_क्रमmat अणु
	पूर्णांक  fourcc;          /* video4linux 2      */
	पूर्णांक  btक्रमmat;        /* BT848_COLOR_FMT_*  */
	पूर्णांक  btswap;          /* BT848_COLOR_CTL_*  */
	पूर्णांक  depth;           /* bit/pixel          */
	पूर्णांक  flags;
	पूर्णांक  hshअगरt,vshअगरt;   /* क्रम planar modes   */
पूर्ण;

काष्ठा bttv_ir अणु
	काष्ठा rc_dev           *dev;
	काष्ठा bttv		*btv;
	काष्ठा समयr_list       समयr;

	अक्षर                    name[32];
	अक्षर                    phys[32];

	/* Usual gpio संकेतling */
	u32                     mask_keycode;
	u32                     mask_keyकरोwn;
	u32                     mask_keyup;
	u32                     polling;
	u32                     last_gpio;
	पूर्णांक                     shअगरt_by;
	पूर्णांक                     rc5_remote_gap;

	/* RC5 gpio */
	bool			rc5_gpio;   /* Is RC5 legacy GPIO enabled? */
	u32                     last_bit;   /* last raw bit seen */
	u32                     code;       /* raw code under स्थिरruction */
	kसमय_प्रकार						base_समय;  /* समय of last seen code */
	bool                    active;     /* building raw code */
पूर्ण;


/* ---------------------------------------------------------- */

काष्ठा bttv_geometry अणु
	u8  vtc,crop,comb;
	u16 width,hscale,hdelay;
	u16 sheight,vscale,vdelay,vtotal;
पूर्ण;

काष्ठा bttv_buffer अणु
	/* common v4l buffer stuff -- must be first */
	काष्ठा videobuf_buffer     vb;

	/* bttv specअगरic */
	स्थिर काष्ठा bttv_क्रमmat   *fmt;
	अचिन्हित पूर्णांक               tvnorm;
	पूर्णांक                        btक्रमmat;
	पूर्णांक                        btswap;
	काष्ठा bttv_geometry       geo;
	काष्ठा btcx_riscmem        top;
	काष्ठा btcx_riscmem        bottom;
	काष्ठा v4l2_rect           crop;
	अचिन्हित पूर्णांक               vbi_skip[2];
	अचिन्हित पूर्णांक               vbi_count[2];
पूर्ण;

काष्ठा bttv_buffer_set अणु
	काष्ठा bttv_buffer     *top;       /* top field buffer    */
	काष्ठा bttv_buffer     *bottom;    /* bottom field buffer */
	अचिन्हित पूर्णांक           top_irq;
	अचिन्हित पूर्णांक           frame_irq;
पूर्ण;

काष्ठा bttv_overlay अणु
	अचिन्हित पूर्णांक           tvnorm;
	काष्ठा v4l2_rect       w;
	क्रमागत v4l2_field        field;
	काष्ठा v4l2_clip       *clips;
	पूर्णांक                    nclips;
	पूर्णांक                    setup_ok;
पूर्ण;

काष्ठा bttv_vbi_fmt अणु
	काष्ठा v4l2_vbi_क्रमmat fmt;

	/* fmt.start[] and count[] refer to this video standard. */
	स्थिर काष्ठा bttv_tvnorm *tvnorm;

	/* Earliest possible start of video capturing with this
	   v4l2_vbi_क्रमmat, in काष्ठा bttv_crop.rect units. */
	__s32                  end;
पूर्ण;

/* bttv-vbi.c */
व्योम bttv_vbi_fmt_reset(काष्ठा bttv_vbi_fmt *f, अचिन्हित पूर्णांक norm);

काष्ठा bttv_crop अणु
	/* A cropping rectangle in काष्ठा bttv_tvnorm.cropcap units. */
	काष्ठा v4l2_rect       rect;

	/* Scaled image size limits with this crop rect. Divide
	   max_height, but not min_height, by two when capturing
	   single fields. See also bttv_crop_reset() and
	   bttv_crop_adjust() in bttv-driver.c. */
	__s32                  min_scaled_width;
	__s32                  min_scaled_height;
	__s32                  max_scaled_width;
	__s32                  max_scaled_height;
पूर्ण;

काष्ठा bttv_fh अणु
	/* This must be the first field in this काष्ठा */
	काष्ठा v4l2_fh		 fh;

	काष्ठा bttv              *btv;
	पूर्णांक resources;
	क्रमागत v4l2_buf_type       type;

	/* video capture */
	काष्ठा videobuf_queue    cap;
	स्थिर काष्ठा bttv_क्रमmat *fmt;
	पूर्णांक                      width;
	पूर्णांक                      height;

	/* video overlay */
	स्थिर काष्ठा bttv_क्रमmat *ovfmt;
	काष्ठा bttv_overlay      ov;

	/* Application called VIDIOC_S_SELECTION. */
	पूर्णांक                      करो_crop;

	/* vbi capture */
	काष्ठा videobuf_queue    vbi;
	/* Current VBI capture winकरोw as seen through this fh (cannot
	   be global क्रम compatibility with earlier drivers). Protected
	   by काष्ठा bttv.lock and काष्ठा bttv_fh.vbi.lock. */
	काष्ठा bttv_vbi_fmt      vbi_fmt;
पूर्ण;

/* ---------------------------------------------------------- */
/* bttv-risc.c                                                */

/* risc code generators - capture */
पूर्णांक bttv_risc_packed(काष्ठा bttv *btv, काष्ठा btcx_riscmem *risc,
		     काष्ठा scatterlist *sglist,
		     अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक bpl,
		     अचिन्हित पूर्णांक pitch, अचिन्हित पूर्णांक skip_lines,
		     अचिन्हित पूर्णांक store_lines);

/* control dma रेजिस्टर + risc मुख्य loop */
व्योम bttv_set_dma(काष्ठा bttv *btv, पूर्णांक override);
पूर्णांक bttv_risc_init_मुख्य(काष्ठा bttv *btv);
पूर्णांक bttv_risc_hook(काष्ठा bttv *btv, पूर्णांक slot, काष्ठा btcx_riscmem *risc,
		   पूर्णांक irqflags);

/* capture buffer handling */
पूर्णांक bttv_buffer_risc(काष्ठा bttv *btv, काष्ठा bttv_buffer *buf);
पूर्णांक bttv_buffer_activate_video(काष्ठा bttv *btv,
			       काष्ठा bttv_buffer_set *set);
पूर्णांक bttv_buffer_activate_vbi(काष्ठा bttv *btv,
			     काष्ठा bttv_buffer *vbi);
व्योम bttv_dma_मुक्त(काष्ठा videobuf_queue *q, काष्ठा bttv *btv,
		   काष्ठा bttv_buffer *buf);

/* overlay handling */
पूर्णांक bttv_overlay_risc(काष्ठा bttv *btv, काष्ठा bttv_overlay *ov,
		      स्थिर काष्ठा bttv_क्रमmat *fmt,
		      काष्ठा bttv_buffer *buf);


/* ---------------------------------------------------------- */
/* bttv-vbi.c                                                 */

पूर्णांक bttv_try_fmt_vbi_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f);
पूर्णांक bttv_g_fmt_vbi_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f);
पूर्णांक bttv_s_fmt_vbi_cap(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_क्रमmat *f);

बाह्य स्थिर काष्ठा videobuf_queue_ops bttv_vbi_qops;

/* ---------------------------------------------------------- */
/* bttv-gpio.c */

बाह्य काष्ठा bus_type bttv_sub_bus_type;
पूर्णांक bttv_sub_add_device(काष्ठा bttv_core *core, अक्षर *name);
पूर्णांक bttv_sub_del_devices(काष्ठा bttv_core *core);

/* ---------------------------------------------------------- */
/* bttv-cards.c                                               */

बाह्य पूर्णांक no_overlay;

/* ---------------------------------------------------------- */
/* bttv-input.c                                               */

बाह्य व्योम init_bttv_i2c_ir(काष्ठा bttv *btv);

/* ---------------------------------------------------------- */
/* bttv-i2c.c                                                 */
बाह्य पूर्णांक init_bttv_i2c(काष्ठा bttv *btv);
बाह्य पूर्णांक fini_bttv_i2c(काष्ठा bttv *btv);

/* ---------------------------------------------------------- */
/* bttv-driver.c                                              */

/* insmod options */
बाह्य अचिन्हित पूर्णांक bttv_verbose;
बाह्य अचिन्हित पूर्णांक bttv_debug;
बाह्य अचिन्हित पूर्णांक bttv_gpio;
बाह्य व्योम bttv_gpio_tracking(काष्ठा bttv *btv, अक्षर *comment);

#घोषणा dprपूर्णांकk(fmt, ...)			\
करो अणु						\
	अगर (bttv_debug >= 1)			\
		pr_debug(fmt, ##__VA_ARGS__);	\
पूर्ण जबतक (0)
#घोषणा dprपूर्णांकk_cont(fmt, ...)			\
करो अणु						\
	अगर (bttv_debug >= 1)			\
		pr_cont(fmt, ##__VA_ARGS__);	\
पूर्ण जबतक (0)
#घोषणा d2prपूर्णांकk(fmt, ...)			\
करो अणु						\
	अगर (bttv_debug >= 2)			\
		prपूर्णांकk(fmt, ##__VA_ARGS__);	\
पूर्ण जबतक (0)

#घोषणा BTTV_MAX_FBUF   0x208000
#घोषणा BTTV_TIMEOUT    msecs_to_jअगरfies(500)    /* 0.5 seconds */
#घोषणा BTTV_FREE_IDLE  msecs_to_jअगरfies(1000)   /* one second */


काष्ठा bttv_pll_info अणु
	अचिन्हित पूर्णांक pll_अगरreq;    /* PLL input frequency        */
	अचिन्हित पूर्णांक pll_ofreq;    /* PLL output frequency       */
	अचिन्हित पूर्णांक pll_crystal;  /* Crystal used क्रम input     */
	अचिन्हित पूर्णांक pll_current;  /* Currently programmed ofreq */
पूर्ण;

/* क्रम gpio-connected remote control */
काष्ठा bttv_input अणु
	काष्ठा input_dev      *dev;
	अक्षर                  name[32];
	अक्षर                  phys[32];
	u32                   mask_keycode;
	u32                   mask_keyकरोwn;
पूर्ण;

काष्ठा bttv_suspend_state अणु
	u32  gpio_enable;
	u32  gpio_data;
	पूर्णांक  disabled;
	पूर्णांक  loop_irq;
	काष्ठा bttv_buffer_set video;
	काष्ठा bttv_buffer     *vbi;
पूर्ण;

काष्ठा bttv_tea575x_gpio अणु
	u8 data, clk, wren, most;
पूर्ण;

काष्ठा bttv अणु
	काष्ठा bttv_core c;

	/* pci device config */
	अचिन्हित लघु id;
	अचिन्हित अक्षर revision;
	अचिन्हित अक्षर __iomem *bt848_mmio;   /* poपूर्णांकer to mmio */

	/* card configuration info */
	अचिन्हित पूर्णांक cardid;   /* pci subप्रणाली id (bt878 based ones) */
	अचिन्हित पूर्णांक tuner_type;  /* tuner chip type */
	अचिन्हित पूर्णांक tda9887_conf;
	अचिन्हित पूर्णांक svhs, dig;
	अचिन्हित पूर्णांक has_saa6588:1;
	काष्ठा bttv_pll_info pll;
	पूर्णांक triton1;
	पूर्णांक gpioirq;

	पूर्णांक use_i2c_hw;

	/* old gpio पूर्णांकerface */
	पूर्णांक shutकरोwn;

	व्योम (*volume_gpio)(काष्ठा bttv *btv, __u16 volume);
	व्योम (*audio_mode_gpio)(काष्ठा bttv *btv, काष्ठा v4l2_tuner *tuner, पूर्णांक set);

	/* new gpio पूर्णांकerface */
	spinlock_t gpio_lock;

	/* i2c layer */
	काष्ठा i2c_algo_bit_data   i2c_algo;
	काष्ठा i2c_client          i2c_client;
	पूर्णांक                        i2c_state, i2c_rc;
	पूर्णांक                        i2c_करोne;
	रुको_queue_head_t          i2c_queue;
	काष्ठा v4l2_subdev	  *sd_msp34xx;
	काष्ठा v4l2_subdev	  *sd_tvaudio;
	काष्ठा v4l2_subdev	  *sd_tda7432;

	/* video4linux (1) */
	काष्ठा video_device video_dev;
	काष्ठा video_device radio_dev;
	काष्ठा video_device vbi_dev;

	/* controls */
	काष्ठा v4l2_ctrl_handler   ctrl_handler;
	काष्ठा v4l2_ctrl_handler   radio_ctrl_handler;

	/* infrared remote */
	पूर्णांक has_remote;
	काष्ठा bttv_ir *remote;

	/* I2C remote data */
	काष्ठा IR_i2c_init_data    init_data;

	/* locking */
	spinlock_t s_lock;
	काष्ठा mutex lock;
	पूर्णांक resources;

	/* video state */
	अचिन्हित पूर्णांक input;
	अचिन्हित पूर्णांक audio_input;
	अचिन्हित पूर्णांक mute;
	अचिन्हित दीर्घ tv_freq;
	अचिन्हित पूर्णांक tvnorm;
	v4l2_std_id std;
	पूर्णांक hue, contrast, bright, saturation;
	काष्ठा v4l2_framebuffer fbuf;
	अचिन्हित पूर्णांक field_count;

	/* various options */
	पूर्णांक opt_combfilter;
	पूर्णांक opt_स्वतःmute;
	पूर्णांक opt_vcr_hack;
	पूर्णांक opt_uv_ratio;

	/* radio data/state */
	पूर्णांक has_radio;
	पूर्णांक has_radio_tuner;
	पूर्णांक radio_user;
	पूर्णांक radio_uses_msp_demodulator;
	अचिन्हित दीर्घ radio_freq;

	/* miro/pinnacle + Aimslab VHX
	   philips matchbox (tea5757 radio tuner) support */
	पूर्णांक has_tea575x;
	काष्ठा bttv_tea575x_gpio tea_gpio;
	काष्ठा snd_tea575x tea;

	/* ISA stuff (Terratec Active Radio Upgrade) */
	पूर्णांक mbox_ior;
	पूर्णांक mbox_iow;
	पूर्णांक mbox_csel;

	/* चयन status क्रम multi-controller cards */
	अक्षर sw_status[4];

	/* risc memory management data
	   - must acquire s_lock beक्रमe changing these
	   - only the irq handler is supported to touch top + bottom + vcurr */
	काष्ठा btcx_riscmem     मुख्य;
	काष्ठा bttv_buffer      *screen;    /* overlay             */
	काष्ठा list_head        capture;    /* video capture queue */
	काष्ठा list_head        vcapture;   /* vbi capture queue   */
	काष्ठा bttv_buffer_set  curr;       /* active buffers      */
	काष्ठा bttv_buffer      *cvbi;      /* active vbi buffer   */
	पूर्णांक                     loop_irq;
	पूर्णांक                     new_input;

	अचिन्हित दीर्घ cap_ctl;
	अचिन्हित दीर्घ dma_on;
	काष्ठा समयr_list समयout;
	काष्ठा bttv_suspend_state state;

	/* stats */
	अचिन्हित पूर्णांक errors;
	अचिन्हित पूर्णांक framedrop;
	अचिन्हित पूर्णांक irq_total;
	अचिन्हित पूर्णांक irq_me;

	अचिन्हित पूर्णांक users;
	काष्ठा bttv_fh init;

	/* used to make dvb-bt8xx स्वतःloadable */
	काष्ठा work_काष्ठा request_module_wk;

	/* Default (0) and current (1) video capturing and overlay
	   cropping parameters in bttv_tvnorm.cropcap units. Protected
	   by bttv.lock. */
	काष्ठा bttv_crop crop[2];

	/* Earliest possible start of video capturing in
	   bttv_tvnorm.cropcap line units. Set by check_alloc_btres()
	   and मुक्त_btres(). Protected by bttv.lock. */
	__s32			vbi_end;

	/* Latest possible end of VBI capturing (= crop[x].rect.top when
	   VIDEO_RESOURCES are locked). Set by check_alloc_btres()
	   and मुक्त_btres(). Protected by bttv.lock. */
	__s32			crop_start;
पूर्ण;

अटल अंतरभूत काष्ठा bttv *to_bttv(काष्ठा v4l2_device *v4l2_dev)
अणु
	वापस container_of(v4l2_dev, काष्ठा bttv, c.v4l2_dev);
पूर्ण

/* our devices */
#घोषणा BTTV_MAX 32
बाह्य अचिन्हित पूर्णांक bttv_num;
बाह्य काष्ठा bttv *bttvs[BTTV_MAX];

अटल अंतरभूत अचिन्हित पूर्णांक bttv_muxsel(स्थिर काष्ठा bttv *btv,
				       अचिन्हित पूर्णांक input)
अणु
	वापस (bttv_tvcards[btv->c.type].muxsel >> (input * 2)) & 3;
पूर्ण

#पूर्ण_अगर

#घोषणा btग_लिखो(dat,adr)    ग_लिखोl((dat), btv->bt848_mmio+(adr))
#घोषणा btपढ़ो(adr)         पढ़ोl(btv->bt848_mmio+(adr))

#घोषणा btand(dat,adr)      btग_लिखो((dat) & btपढ़ो(adr), adr)
#घोषणा btor(dat,adr)       btग_लिखो((dat) | btपढ़ो(adr), adr)
#घोषणा btaor(dat,mask,adr) btग_लिखो((dat) | ((mask) & btपढ़ो(adr)), adr)

#पूर्ण_अगर /* _BTTVP_H_ */
