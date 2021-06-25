<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * zoran - Iomega Buz driver
 *
 * Copyright (C) 1999 Rainer Johanni <Rainer@Johanni.de>
 *
 * based on
 *
 * zoran.0.0.3 Copyright (C) 1998 Dave Perks <dperks@ibm.net>
 *
 * and
 *
 * bttv - Bt848 frame grabber driver
 * Copyright (C) 1996,97,98 Ralph  Metzler (rjkm@thp.uni-koeln.de)
 *                        & Marcus Metzler (mocm@thp.uni-koeln.de)
 */

#अगर_अघोषित _BUZ_H_
#घोषणा _BUZ_H_

#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/videobuf2-core.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-dma-contig.h>

#घोषणा ZR_NORM_PAL 0
#घोषणा ZR_NORM_NTSC 1
#घोषणा ZR_NORM_SECAM 2

काष्ठा zr_buffer अणु
	/* common v4l buffer stuff -- must be first */
	काष्ठा vb2_v4l2_buffer          vbuf;
	काष्ठा list_head                queue;
पूर्ण;

अटल अंतरभूत काष्ठा zr_buffer *vb2_to_zr_buffer(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);

	वापस container_of(vbuf, काष्ठा zr_buffer, vbuf);
पूर्ण

#घोषणा ZORAN_NAME    "ZORAN"	/* name of the device */

#घोषणा ZR_DEVNAME(zr) ((zr)->name)

#घोषणा   BUZ_MAX_WIDTH   (zr->timing->wa)
#घोषणा   BUZ_MAX_HEIGHT  (zr->timing->ha)
#घोषणा   BUZ_MIN_WIDTH    32	/* never display less than 32 pixels */
#घोषणा   BUZ_MIN_HEIGHT   24	/* never display less than 24 rows */

#घोषणा BUZ_NUM_STAT_COM    4
#घोषणा BUZ_MASK_STAT_COM   3

#घोषणा BUZ_MAX_FRAME     256	/* Must be a घातer of 2 */
#घोषणा BUZ_MASK_FRAME    255	/* Must be BUZ_MAX_FRAME-1 */

#घोषणा BUZ_MAX_INPUT       16

#अगर VIDEO_MAX_FRAME <= 32
#   define   V4L_MAX_FRAME   32
#या_अगर VIDEO_MAX_FRAME <= 64
#   define   V4L_MAX_FRAME   64
#अन्यथा
#   error   "Too many video frame buffers to handle"
#पूर्ण_अगर
#घोषणा   V4L_MASK_FRAME   (V4L_MAX_FRAME - 1)

#घोषणा MAX_FRAME (BUZ_MAX_FRAME > VIDEO_MAX_FRAME ? BUZ_MAX_FRAME : VIDEO_MAX_FRAME)

#समावेश "zr36057.h"

क्रमागत card_type अणु
	UNKNOWN = -1,

	/* Pinnacle/Miro */
	DC10_OLD,		/* DC30 like */
	DC10_NEW,		/* DC10_PLUS like */
	DC10_PLUS,
	DC30,
	DC30_PLUS,

	/* Linux Media Lअसल */
	LML33,
	LML33R10,

	/* Iomega */
	BUZ,

	/* AverMedia */
	AVS6EYES,

	/* total number of cards */
	NUM_CARDS
पूर्ण;

क्रमागत zoran_codec_mode अणु
	BUZ_MODE_IDLE,		/* nothing going on */
	BUZ_MODE_MOTION_COMPRESS,	/* grabbing frames */
	BUZ_MODE_MOTION_DECOMPRESS,	/* playing frames */
	BUZ_MODE_STILL_COMPRESS,	/* still frame conversion */
	BUZ_MODE_STILL_DECOMPRESS	/* still frame conversion */
पूर्ण;

क्रमागत zoran_map_mode अणु
	ZORAN_MAP_MODE_NONE,
	ZORAN_MAP_MODE_RAW,
	ZORAN_MAP_MODE_JPG_REC,
	ZORAN_MAP_MODE_JPG_PLAY,
पूर्ण;

क्रमागत gpio_type अणु
	ZR_GPIO_JPEG_SLEEP = 0,
	ZR_GPIO_JPEG_RESET,
	ZR_GPIO_JPEG_FRAME,
	ZR_GPIO_VID_सूची,
	ZR_GPIO_VID_EN,
	ZR_GPIO_VID_RESET,
	ZR_GPIO_CLK_SEL1,
	ZR_GPIO_CLK_SEL2,
	ZR_GPIO_MAX,
पूर्ण;

क्रमागत gpcs_type अणु
	GPCS_JPEG_RESET = 0,
	GPCS_JPEG_START,
	GPCS_MAX,
पूर्ण;

काष्ठा zoran_क्रमmat अणु
	अक्षर *name;
	__u32 fourcc;
	पूर्णांक colorspace;
	पूर्णांक depth;
	__u32 flags;
	__u32 vfespfr;
पूर्ण;

/* flags */
#घोषणा ZORAN_FORMAT_COMPRESSED BIT(0)
#घोषणा ZORAN_FORMAT_OVERLAY BIT(1)
#घोषणा ZORAN_FORMAT_CAPTURE BIT(2)
#घोषणा ZORAN_FORMAT_PLAYBACK BIT(3)

/* v4l-capture settings */
काष्ठा zoran_v4l_settings अणु
	पूर्णांक width, height, bytesperline;	/* capture size */
	स्थिर काष्ठा zoran_क्रमmat *क्रमmat;	/* capture क्रमmat */
पूर्ण;

/* jpg-capture/-playback settings */
काष्ठा zoran_jpg_settings अणु
	पूर्णांक decimation;		/* this bit is used to set everything to शेष */
	पूर्णांक hor_dcm, ver_dcm, पंचांगp_dcm;	/* capture decimation settings (पंचांगp_dcm=1 means both fields) */
	पूर्णांक field_per_buff, odd_even;	/* field-settings (odd_even=1 (+पंचांगp_dcm=1) means top-field-first) */
	पूर्णांक img_x, img_y, img_width, img_height;	/* crop settings (subframe capture) */
	काष्ठा v4l2_jpegcompression jpg_comp;	/* JPEG-specअगरic capture settings */
पूर्ण;


काष्ठा zoran;

/* zoran_fh contains per-खोलो() settings */
काष्ठा zoran_fh अणु
	काष्ठा v4l2_fh fh;
	काष्ठा zoran *zr;
पूर्ण;

काष्ठा card_info अणु
	क्रमागत card_type type;
	अक्षर name[32];
	स्थिर अक्षर *i2c_decoder;	/* i2c decoder device */
	स्थिर अचिन्हित लघु *addrs_decoder;
	स्थिर अक्षर *i2c_encoder;	/* i2c encoder device */
	स्थिर अचिन्हित लघु *addrs_encoder;
	u16 video_vfe, video_codec;			/* videocodec types */
	u16 audio_chip;					/* audio type */

	पूर्णांक inमाला_दो;		/* number of video inमाला_दो */
	काष्ठा input अणु
		पूर्णांक muxsel;
		अक्षर name[32];
	पूर्ण input[BUZ_MAX_INPUT];

	v4l2_std_id norms;
	स्थिर काष्ठा tvnorm *tvn[3];	/* supported TV norms */

	u32 jpeg_पूर्णांक;		/* JPEG पूर्णांकerrupt */
	u32 vsync_पूर्णांक;		/* VSYNC पूर्णांकerrupt */
	s8 gpio[ZR_GPIO_MAX];
	u8 gpcs[GPCS_MAX];

	काष्ठा vfe_polarity vfe_pol;
	u8 gpio_pol[ZR_GPIO_MAX];

	/* is the /GWS line connected? */
	u8 gws_not_connected;

	/* avs6eyes mux setting */
	u8 input_mux;

	व्योम (*init)(काष्ठा zoran *zr);
पूर्ण;

काष्ठा zoran अणु
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा v4l2_ctrl_handler hdl;
	काष्ठा video_device *video_dev;
	काष्ठा vb2_queue vq;

	काष्ठा i2c_adapter i2c_adapter;	/* */
	काष्ठा i2c_algo_bit_data i2c_algo;	/* */
	u32 i2cbr;

	काष्ठा v4l2_subdev *decoder;	/* video decoder sub-device */
	काष्ठा v4l2_subdev *encoder;	/* video encoder sub-device */

	काष्ठा videocodec *codec;	/* video codec */
	काष्ठा videocodec *vfe;	/* video front end */

	काष्ठा mutex lock;	/* file ops serialize lock */

	u8 initialized;		/* flag अगर zoran has been correctly initialized */
	काष्ठा card_info card;
	स्थिर काष्ठा tvnorm *timing;

	अचिन्हित लघु id;	/* number of this device */
	अक्षर name[32];		/* name of this device */
	काष्ठा pci_dev *pci_dev;	/* PCI device */
	अचिन्हित अक्षर revision;	/* revision of zr36057 */
	अचिन्हित अक्षर __iomem *zr36057_mem;/* poपूर्णांकer to mapped IO memory */

	spinlock_t spinlock;	/* Spinlock */

	/* Video क्रम Linux parameters */
	पूर्णांक input;	/* card's norm and input */
	v4l2_std_id norm;

	/* Current buffer params */
	अचिन्हित पूर्णांक buffer_size;

	काष्ठा zoran_v4l_settings v4l_settings;	/* काष्ठाure with a lot of things to play with */

	/* Buz MJPEG parameters */
	क्रमागत zoran_codec_mode codec_mode;	/* status of codec */
	काष्ठा zoran_jpg_settings jpg_settings;	/* काष्ठाure with a lot of things to play with */

	/* grab queue counts/indices, mask with BUZ_MASK_STAT_COM beक्रमe using as index */
	/* (dma_head - dma_tail) is number active in DMA, must be <= BUZ_NUM_STAT_COM */
	/* (value & BUZ_MASK_STAT_COM) corresponds to index in stat_com table */
	अचिन्हित दीर्घ jpg_que_head;	/* Index where to put next buffer which is queued */
	अचिन्हित दीर्घ jpg_dma_head;	/* Index of next buffer which goes पूर्णांकo stat_com */
	अचिन्हित दीर्घ jpg_dma_tail;	/* Index of last buffer in stat_com */
	अचिन्हित दीर्घ jpg_que_tail;	/* Index of last buffer in queue */
	अचिन्हित दीर्घ jpg_seq_num;	/* count of frames since grab/play started */
	अचिन्हित दीर्घ jpg_err_seq;	/* last seq_num beक्रमe error */
	अचिन्हित दीर्घ jpg_err_shअगरt;
	अचिन्हित दीर्घ jpg_queued_num;	/* count of frames queued since grab/play started */
	अचिन्हित दीर्घ vbseq;

	/* zr36057's code buffer table */
	__le32 *stat_com;		/* stat_com[i] is indexed by dma_head/tail & BUZ_MASK_STAT_COM */

	/* Additional stuff क्रम testing */
	अचिन्हित पूर्णांक ghost_पूर्णांक;
	पूर्णांक पूर्णांकr_counter_GIRQ1;
	पूर्णांक पूर्णांकr_counter_GIRQ0;
	पूर्णांक पूर्णांकr_counter_cod_rep_irq;
	पूर्णांक पूर्णांकr_counter_jpeg_rep_irq;
	पूर्णांक field_counter;
	पूर्णांक irq1_in;
	पूर्णांक irq1_out;
	पूर्णांक jpeg_in;
	पूर्णांक jpeg_out;
	पूर्णांक JPEG_0;
	पूर्णांक JPEG_1;
	पूर्णांक end_event_missed;
	पूर्णांक jpeg_missed;
	पूर्णांक jpeg_error;
	पूर्णांक num_errors;
	पूर्णांक jpeg_max_missed;
	पूर्णांक jpeg_min_missed;
	अचिन्हित पूर्णांक prepared;
	अचिन्हित पूर्णांक queued;

	u32 last_isr;
	अचिन्हित दीर्घ frame_num;
	पूर्णांक running;
	पूर्णांक buf_in_reserve;

	dma_addr_t p_sc;
	__le32 *stat_comb;
	dma_addr_t p_scb;
	क्रमागत zoran_map_mode map_mode;
	काष्ठा list_head queued_bufs;
	spinlock_t queued_bufs_lock; /* Protects queued_bufs */
	काष्ठा zr_buffer *inuse[BUZ_NUM_STAT_COM * 2];
पूर्ण;

अटल अंतरभूत काष्ठा zoran *to_zoran(काष्ठा v4l2_device *v4l2_dev)
अणु
	वापस container_of(v4l2_dev, काष्ठा zoran, v4l2_dev);
पूर्ण

/* There was something called _ALPHA_BUZ that used the PCI address instead of
 * the kernel iomapped address क्रम btपढ़ो/btग_लिखो.  */
#घोषणा btग_लिखो(dat, adr)    ग_लिखोl((dat), zr->zr36057_mem + (adr))
#घोषणा btपढ़ो(adr)         पढ़ोl(zr->zr36057_mem + (adr))

#घोषणा btand(dat, adr)      btग_लिखो((dat) & btपढ़ो(adr), adr)
#घोषणा btor(dat, adr)       btग_लिखो((dat) | btपढ़ो(adr), adr)
#घोषणा btaor(dat, mask, adr) btग_लिखो((dat) | ((mask) & btपढ़ो(adr)), adr)

#पूर्ण_अगर

पूर्णांक zoran_queue_init(काष्ठा zoran *zr, काष्ठा vb2_queue *vq);
व्योम zoran_queue_निकास(काष्ठा zoran *zr);
पूर्णांक zr_set_buf(काष्ठा zoran *zr);
