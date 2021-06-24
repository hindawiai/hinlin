<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SAA7146_VV__
#घोषणा __SAA7146_VV__

#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/drv-पूर्णांकf/saa7146.h>
#समावेश <media/videobuf-dma-sg.h>

#घोषणा MAX_SAA7146_CAPTURE_BUFFERS	32	/* arbitrary */
#घोषणा BUFFER_TIMEOUT     (HZ/2)  /* 0.5 seconds */

#घोषणा WRITE_RPS0(x) करो अणु \
	dev->d_rps0.cpu_addr[ count++ ] = cpu_to_le32(x); \
	पूर्ण जबतक (0);

#घोषणा WRITE_RPS1(x) करो अणु \
	dev->d_rps1.cpu_addr[ count++ ] = cpu_to_le32(x); \
	पूर्ण जबतक (0);

काष्ठा	saa7146_video_dma अणु
	u32 base_odd;
	u32 base_even;
	u32 prot_addr;
	u32 pitch;
	u32 base_page;
	u32 num_line_byte;
पूर्ण;

#घोषणा FORMAT_BYTE_SWAP	0x1
#घोषणा FORMAT_IS_PLANAR	0x2

काष्ठा saa7146_क्रमmat अणु
	u32	pixelक्रमmat;
	u32	trans;
	u8	depth;
	u8	flags;
	u8	swap;
पूर्ण;

काष्ठा saa7146_standard
अणु
	अक्षर          *name;
	v4l2_std_id   id;

	पूर्णांक v_offset;	/* number of lines of vertical offset beक्रमe processing */
	पूर्णांक v_field;	/* number of lines in a field क्रम HPS to process */

	पूर्णांक h_offset;	/* horizontal offset of processing winकरोw */
	पूर्णांक h_pixels;	/* number of horizontal pixels to process */

	पूर्णांक v_max_out;
	पूर्णांक h_max_out;
पूर्ण;

/* buffer क्रम one video/vbi frame */
काष्ठा saa7146_buf अणु
	/* common v4l buffer stuff -- must be first */
	काष्ठा videobuf_buffer vb;

	/* saa7146 specअगरic */
	काष्ठा v4l2_pix_क्रमmat  *fmt;
	पूर्णांक (*activate)(काष्ठा saa7146_dev *dev,
			काष्ठा saa7146_buf *buf,
			काष्ठा saa7146_buf *next);

	/* page tables */
	काष्ठा saa7146_pgtable  pt[3];
पूर्ण;

काष्ठा saa7146_dmaqueue अणु
	काष्ठा saa7146_dev	*dev;
	काष्ठा saa7146_buf	*curr;
	काष्ठा list_head	queue;
	काष्ठा समयr_list	समयout;
पूर्ण;

काष्ठा saa7146_overlay अणु
	काष्ठा saa7146_fh	*fh;
	काष्ठा v4l2_winकरोw	win;
	काष्ठा v4l2_clip	clips[16];
	पूर्णांक			nclips;
पूर्ण;

/* per खोलो data */
काष्ठा saa7146_fh अणु
	/* Must be the first field! */
	काष्ठा v4l2_fh		fh;
	काष्ठा saa7146_dev	*dev;

	/* video capture */
	काष्ठा videobuf_queue	video_q;

	/* vbi capture */
	काष्ठा videobuf_queue	vbi_q;

	अचिन्हित पूर्णांक resources;	/* resource management क्रम device खोलो */
पूर्ण;

#घोषणा STATUS_OVERLAY	0x01
#घोषणा STATUS_CAPTURE	0x02

काष्ठा saa7146_vv
अणु
	/* vbi capture */
	काष्ठा saa7146_dmaqueue		vbi_dmaq;
	काष्ठा v4l2_vbi_क्रमmat		vbi_fmt;
	काष्ठा समयr_list		vbi_पढ़ो_समयout;
	काष्ठा file			*vbi_पढ़ो_समयout_file;
	/* vbi workaround पूर्णांकerrupt queue */
	रुको_queue_head_t		vbi_wq;
	पूर्णांक				vbi_fieldcount;
	काष्ठा saa7146_fh		*vbi_streaming;

	पूर्णांक				video_status;
	काष्ठा saa7146_fh		*video_fh;

	/* video overlay */
	काष्ठा saa7146_overlay		ov;
	काष्ठा v4l2_framebuffer		ov_fb;
	काष्ठा saa7146_क्रमmat		*ov_fmt;
	काष्ठा saa7146_fh		*ov_suspend;

	/* video capture */
	काष्ठा saa7146_dmaqueue		video_dmaq;
	काष्ठा v4l2_pix_क्रमmat		video_fmt;
	क्रमागत v4l2_field			last_field;

	/* common: fixme? shouldn't this be in saa7146_fh?
	   (this leads to a more complicated question: shall the driver
	   store the dअगरferent settings (क्रम example S_INPUT) क्रम every खोलो
	   and restore it appropriately, or should all settings be common क्रम
	   all खोलोs? currently, we करो the latter, like all other
	   drivers करो... */
	काष्ठा saa7146_standard	*standard;

	पूर्णांक	vflip;
	पूर्णांक	hflip;
	पूर्णांक	current_hps_source;
	पूर्णांक	current_hps_sync;

	काष्ठा saa7146_dma	d_clipping;	/* poपूर्णांकer to clipping memory */

	अचिन्हित पूर्णांक resources;	/* resource management क्रम device */
पूर्ण;

/* flags */
#घोषणा SAA7146_USE_PORT_B_FOR_VBI	0x2     /* use input port b क्रम vbi hardware bug workaround */

काष्ठा saa7146_ext_vv
अणु
	/* inक्रमmation about the video capabilities of the device */
	पूर्णांक	inमाला_दो;
	पूर्णांक	audios;
	u32	capabilities;
	पूर्णांक	flags;

	/* additionally supported transmission standards */
	काष्ठा saa7146_standard *stds;
	पूर्णांक num_stds;
	पूर्णांक (*std_callback)(काष्ठा saa7146_dev*, काष्ठा saa7146_standard *);

	/* the extension can override this */
	काष्ठा v4l2_ioctl_ops vid_ops;
	काष्ठा v4l2_ioctl_ops vbi_ops;
	/* poपूर्णांकer to the saa7146 core ops */
	स्थिर काष्ठा v4l2_ioctl_ops *core_ops;

	काष्ठा v4l2_file_operations vbi_fops;
पूर्ण;

काष्ठा saa7146_use_ops  अणु
	व्योम (*init)(काष्ठा saa7146_dev *, काष्ठा saa7146_vv *);
	पूर्णांक(*खोलो)(काष्ठा saa7146_dev *, काष्ठा file *);
	व्योम (*release)(काष्ठा saa7146_dev *, काष्ठा file *);
	व्योम (*irq_करोne)(काष्ठा saa7146_dev *, अचिन्हित दीर्घ status);
	sमाप_प्रकार (*पढ़ो)(काष्ठा file *, अक्षर __user *, माप_प्रकार, loff_t *);
पूर्ण;

/* from saa7146_fops.c */
पूर्णांक saa7146_रेजिस्टर_device(काष्ठा video_device *vid, काष्ठा saa7146_dev *dev, अक्षर *name, पूर्णांक type);
पूर्णांक saa7146_unरेजिस्टर_device(काष्ठा video_device *vid, काष्ठा saa7146_dev *dev);
व्योम saa7146_buffer_finish(काष्ठा saa7146_dev *dev, काष्ठा saa7146_dmaqueue *q, पूर्णांक state);
व्योम saa7146_buffer_next(काष्ठा saa7146_dev *dev, काष्ठा saa7146_dmaqueue *q,पूर्णांक vbi);
पूर्णांक saa7146_buffer_queue(काष्ठा saa7146_dev *dev, काष्ठा saa7146_dmaqueue *q, काष्ठा saa7146_buf *buf);
व्योम saa7146_buffer_समयout(काष्ठा समयr_list *t);
व्योम saa7146_dma_मुक्त(काष्ठा saa7146_dev* dev,काष्ठा videobuf_queue *q,
						काष्ठा saa7146_buf *buf);

पूर्णांक saa7146_vv_init(काष्ठा saa7146_dev* dev, काष्ठा saa7146_ext_vv *ext_vv);
पूर्णांक saa7146_vv_release(काष्ठा saa7146_dev* dev);

/* from saa7146_hlp.c */
पूर्णांक saa7146_enable_overlay(काष्ठा saa7146_fh *fh);
व्योम saa7146_disable_overlay(काष्ठा saa7146_fh *fh);

व्योम saa7146_set_capture(काष्ठा saa7146_dev *dev, काष्ठा saa7146_buf *buf, काष्ठा saa7146_buf *next);
व्योम saa7146_ग_लिखो_out_dma(काष्ठा saa7146_dev* dev, पूर्णांक which, काष्ठा saa7146_video_dma* vdma) ;
व्योम saa7146_set_hps_source_and_sync(काष्ठा saa7146_dev *saa, पूर्णांक source, पूर्णांक sync);
व्योम saa7146_set_gpio(काष्ठा saa7146_dev *saa, u8 pin, u8 data);

/* from saa7146_video.c */
बाह्य स्थिर काष्ठा v4l2_ioctl_ops saa7146_video_ioctl_ops;
बाह्य स्थिर काष्ठा v4l2_ioctl_ops saa7146_vbi_ioctl_ops;
बाह्य स्थिर काष्ठा saa7146_use_ops saa7146_video_uops;
पूर्णांक saa7146_start_preview(काष्ठा saa7146_fh *fh);
पूर्णांक saa7146_stop_preview(काष्ठा saa7146_fh *fh);
दीर्घ saa7146_video_करो_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, व्योम *arg);
पूर्णांक saa7146_s_ctrl(काष्ठा v4l2_ctrl *ctrl);

/* from saa7146_vbi.c */
बाह्य स्थिर काष्ठा saa7146_use_ops saa7146_vbi_uops;

/* resource management functions */
पूर्णांक saa7146_res_get(काष्ठा saa7146_fh *fh, अचिन्हित पूर्णांक bit);
व्योम saa7146_res_मुक्त(काष्ठा saa7146_fh *fh, अचिन्हित पूर्णांक bits);

#घोषणा RESOURCE_DMA1_HPS	0x1
#घोषणा RESOURCE_DMA2_CLP	0x2
#घोषणा RESOURCE_DMA3_BRS	0x4

/* saa7146 source inमाला_दो */
#घोषणा SAA7146_HPS_SOURCE_PORT_A	0x00
#घोषणा SAA7146_HPS_SOURCE_PORT_B	0x01
#घोषणा SAA7146_HPS_SOURCE_YPB_CPA	0x02
#घोषणा SAA7146_HPS_SOURCE_YPA_CPB	0x03

/* sync inमाला_दो */
#घोषणा SAA7146_HPS_SYNC_PORT_A		0x00
#घोषणा SAA7146_HPS_SYNC_PORT_B		0x01

/* some memory sizes */
/* max. 16 clipping rectangles */
#घोषणा SAA7146_CLIPPING_MEM	(16 * 4 * माप(u32))

/* some defines क्रम the various clipping-modes */
#घोषणा SAA7146_CLIPPING_RECT		0x4
#घोषणा SAA7146_CLIPPING_RECT_INVERTED	0x5
#घोषणा SAA7146_CLIPPING_MASK		0x6
#घोषणा SAA7146_CLIPPING_MASK_INVERTED	0x7

/* output क्रमmats: each entry holds four inक्रमmation */
#घोषणा RGB08_COMPOSED	0x0217 /* composed is used in the sense of "not-planar" */
/* this means: planar?=0, yuv2rgb-conversation-mode=2, dither=yes(=1), क्रमmat-mode = 7 */
#घोषणा RGB15_COMPOSED	0x0213
#घोषणा RGB16_COMPOSED	0x0210
#घोषणा RGB24_COMPOSED	0x0201
#घोषणा RGB32_COMPOSED	0x0202

#घोषणा Y8			0x0006
#घोषणा YUV411_COMPOSED		0x0003
#घोषणा YUV422_COMPOSED		0x0000
/* this means: planar?=1, yuv2rgb-conversion-mode=0, dither=no(=0), क्रमmat-mode = b */
#घोषणा YUV411_DECOMPOSED	0x100b
#घोषणा YUV422_DECOMPOSED	0x1009
#घोषणा YUV420_DECOMPOSED	0x100a

#घोषणा IS_PLANAR(x) (x & 0xf000)

/* misc defines */
#घोषणा SAA7146_NO_SWAP		(0x0)
#घोषणा SAA7146_TWO_BYTE_SWAP	(0x1)
#घोषणा SAA7146_FOUR_BYTE_SWAP	(0x2)

#पूर्ण_अगर
