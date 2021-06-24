<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2013 - 2014 Texas Instruments, Inc.
 *
 * Benoit Parrot <bparrot@ti.com>
 * Lad, Prabhakar <prabhakar.csengg@gmail.com>
 */

#अगर_अघोषित AM437X_VPFE_H
#घोषणा AM437X_VPFE_H

#समावेश <linux/am437x-vpfe.h>
#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/videodev2.h>

#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "am437x-vpfe_regs.h"

क्रमागत vpfe_pin_pol अणु
	VPFE_PINPOL_POSITIVE = 0,
	VPFE_PINPOL_NEGATIVE,
पूर्ण;

क्रमागत vpfe_hw_अगर_type अणु
	/* Raw Bayer */
	VPFE_RAW_BAYER = 0,
	/* BT656 - 8 bit */
	VPFE_BT656,
	/* BT656 - 10 bit */
	VPFE_BT656_10BIT,
	/* YCbCr - 8 bit with बाह्यal sync */
	VPFE_YCBCR_SYNC_8,
	/* YCbCr - 16 bit with बाह्यal sync */
	VPFE_YCBCR_SYNC_16,
पूर्ण;

/* पूर्णांकerface description */
काष्ठा vpfe_hw_अगर_param अणु
	क्रमागत vpfe_hw_अगर_type अगर_type;
	क्रमागत vpfe_pin_pol hdpol;
	क्रमागत vpfe_pin_pol vdpol;
	अचिन्हित पूर्णांक bus_width;
पूर्ण;

#घोषणा VPFE_MAX_SUBDEV		1
#घोषणा VPFE_MAX_INPUTS		1

काष्ठा vpfe_std_info अणु
	पूर्णांक active_pixels;
	पूर्णांक active_lines;
	/* current frame क्रमmat */
	पूर्णांक frame_क्रमmat;
पूर्ण;

काष्ठा vpfe_route अणु
	u32 input;
	u32 output;
पूर्ण;

काष्ठा vpfe_subdev_info अणु
	/* Sub device group id */
	पूर्णांक grp_id;
	/* inमाला_दो available at the sub device */
	काष्ठा v4l2_input inमाला_दो[VPFE_MAX_INPUTS];
	/* Sub dev routing inक्रमmation क्रम each input */
	काष्ठा vpfe_route *routes;
	/* check अगर sub dev supports routing */
	पूर्णांक can_route;
	/* ccdc bus/पूर्णांकerface configuration */
	काष्ठा vpfe_hw_अगर_param vpfe_param;
	काष्ठा v4l2_subdev *sd;
पूर्ण;

काष्ठा vpfe_config अणु
	/* inक्रमmation about each subdev */
	काष्ठा vpfe_subdev_info sub_devs[VPFE_MAX_SUBDEV];
	/* Flat array, arranged in groups */
	काष्ठा v4l2_async_subdev *asd[VPFE_MAX_SUBDEV];
पूर्ण;

काष्ठा vpfe_cap_buffer अणु
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head list;
पूर्ण;

क्रमागत ccdc_pixfmt अणु
	CCDC_PIXFMT_RAW = 0,
	CCDC_PIXFMT_YCBCR_16BIT,
	CCDC_PIXFMT_YCBCR_8BIT,
पूर्ण;

क्रमागत ccdc_frmfmt अणु
	CCDC_FRMFMT_PROGRESSIVE = 0,
	CCDC_FRMFMT_INTERLACED,
पूर्ण;

/* PIXEL ORDER IN MEMORY from LSB to MSB */
/* only applicable क्रम 8-bit input mode  */
क्रमागत ccdc_pixorder अणु
	CCDC_PIXORDER_YCBYCR,
	CCDC_PIXORDER_CBYCRY,
पूर्ण;

क्रमागत ccdc_buftype अणु
	CCDC_BUFTYPE_FLD_INTERLEAVED,
	CCDC_BUFTYPE_FLD_SEPARATED
पूर्ण;


/* वापसs the highest bit used क्रम the gamma */
अटल अंतरभूत u8 ccdc_gamma_width_max_bit(क्रमागत vpfe_ccdc_gamma_width width)
अणु
	वापस 15 - width;
पूर्ण

/* वापसs the highest bit used क्रम this data size */
अटल अंतरभूत u8 ccdc_data_size_max_bit(क्रमागत vpfe_ccdc_data_size sz)
अणु
	वापस sz == VPFE_CCDC_DATA_8BITS ? 7 : 15 - sz;
पूर्ण

/* Structure क्रम CCDC configuration parameters क्रम raw capture mode */
काष्ठा ccdc_params_raw अणु
	/* pixel क्रमmat */
	क्रमागत ccdc_pixfmt pix_fmt;
	/* progressive or पूर्णांकerlaced frame */
	क्रमागत ccdc_frmfmt frm_fmt;
	काष्ठा v4l2_rect win;
	/* Current Format Bytes Per Pixels */
	अचिन्हित पूर्णांक bytesperpixel;
	/* Current Format Bytes per Lines
	 * (Aligned to 32 bytes) used क्रम HORZ_INFO
	 */
	अचिन्हित पूर्णांक bytesperline;
	/* field id polarity */
	क्रमागत vpfe_pin_pol fid_pol;
	/* vertical sync polarity */
	क्रमागत vpfe_pin_pol vd_pol;
	/* horizontal sync polarity */
	क्रमागत vpfe_pin_pol hd_pol;
	/* पूर्णांकerleaved or separated fields */
	क्रमागत ccdc_buftype buf_type;
	/*
	 * enable to store the image in inverse
	 * order in memory(bottom to top)
	 */
	अचिन्हित अक्षर image_invert_enable;
	/* configurable parameters */
	काष्ठा vpfe_ccdc_config_params_raw config_params;
पूर्ण;

काष्ठा ccdc_params_ycbcr अणु
	/* pixel क्रमmat */
	क्रमागत ccdc_pixfmt pix_fmt;
	/* progressive or पूर्णांकerlaced frame */
	क्रमागत ccdc_frmfmt frm_fmt;
	काष्ठा v4l2_rect win;
	/* Current Format Bytes Per Pixels */
	अचिन्हित पूर्णांक bytesperpixel;
	/* Current Format Bytes per Lines
	 * (Aligned to 32 bytes) used क्रम HORZ_INFO
	 */
	अचिन्हित पूर्णांक bytesperline;
	/* field id polarity */
	क्रमागत vpfe_pin_pol fid_pol;
	/* vertical sync polarity */
	क्रमागत vpfe_pin_pol vd_pol;
	/* horizontal sync polarity */
	क्रमागत vpfe_pin_pol hd_pol;
	/* enable BT.656 embedded sync mode */
	पूर्णांक bt656_enable;
	/* cb:y:cr:y or y:cb:y:cr in memory */
	क्रमागत ccdc_pixorder pix_order;
	/* पूर्णांकerleaved or separated fields  */
	क्रमागत ccdc_buftype buf_type;
पूर्ण;

/*
 * CCDC operational configuration
 */
काष्ठा ccdc_config अणु
	/* CCDC पूर्णांकerface type */
	क्रमागत vpfe_hw_अगर_type अगर_type;
	/* Raw Bayer configuration */
	काष्ठा ccdc_params_raw bayer;
	/* YCbCr configuration */
	काष्ठा ccdc_params_ycbcr ycbcr;
	/* ccdc base address */
	व्योम __iomem *base_addr;
पूर्ण;

काष्ठा vpfe_ccdc अणु
	काष्ठा ccdc_config ccdc_cfg;
	u32 ccdc_ctx[VPFE_REG_END / माप(u32)];
पूर्ण;

/*
 * काष्ठा vpfe_fmt - VPFE media bus क्रमmat inक्रमmation
 * fourcc: V4L2 pixel क्रमmat code
 * code: V4L2 media bus क्रमmat code
 * bitsperpixel: Bits per pixel over the bus
 */
काष्ठा vpfe_fmt अणु
	u32 fourcc;
	u32 code;
	u32 bitsperpixel;
पूर्ण;

/*
 * When क्रमmats[] is modअगरied make sure to adjust this value also.
 * Expect compile समय warnings अगर VPFE_NUM_FORMATS is smaller then
 * the number of elements in क्रमmats[].
 */
#घोषणा VPFE_NUM_FORMATS	10

काष्ठा vpfe_device अणु
	/* V4l2 specअगरic parameters */
	/* Identअगरies video device क्रम this channel */
	काष्ठा video_device video_dev;
	/* sub devices */
	काष्ठा v4l2_subdev **sd;
	/* vpfe cfg */
	काष्ठा vpfe_config *cfg;
	/* V4l2 device */
	काष्ठा v4l2_device v4l2_dev;
	/* parent device */
	काष्ठा device *pdev;
	/* subdevice async Notअगरier */
	काष्ठा v4l2_async_notअगरier notअगरier;
	/* Indicates id of the field which is being displayed */
	अचिन्हित field;
	अचिन्हित sequence;
	/* current पूर्णांकerface type */
	काष्ठा vpfe_hw_अगर_param vpfe_अगर_params;
	/* ptr to currently selected sub device */
	काष्ठा vpfe_subdev_info *current_subdev;
	/* current input at the sub device */
	पूर्णांक current_input;
	/* Keeps track of the inक्रमmation about the standard */
	काष्ठा vpfe_std_info std_info;
	/* std index पूर्णांकo std table */
	पूर्णांक std_index;
	/* IRQs used when CCDC output to SDRAM */
	अचिन्हित पूर्णांक irq;
	/* Poपूर्णांकer poपूर्णांकing to current v4l2_buffer */
	काष्ठा vpfe_cap_buffer *cur_frm;
	/* Poपूर्णांकer poपूर्णांकing to next v4l2_buffer */
	काष्ठा vpfe_cap_buffer *next_frm;
	/* Used to store pixel क्रमmat */
	काष्ठा v4l2_क्रमmat fmt;
	/* Used to keep a reference to the current vpfe_fmt */
	काष्ठा vpfe_fmt *current_vpfe_fmt;
	काष्ठा vpfe_fmt	*active_fmt[VPFE_NUM_FORMATS];
	अचिन्हित पूर्णांक num_active_fmt;

	/*
	 * used when IMP is chained to store the crop winकरोw which
	 * is dअगरferent from the image winकरोw
	 */
	काष्ठा v4l2_rect crop;
	/* Buffer queue used in video-buf */
	काष्ठा vb2_queue buffer_queue;
	/* Queue of filled frames */
	काष्ठा list_head dma_queue;
	/* IRQ lock क्रम DMA queue */
	spinlock_t dma_queue_lock;
	/* lock used to access this काष्ठाure */
	काष्ठा mutex lock;
	/*
	 * offset where second field starts from the starting of the
	 * buffer क्रम field separated YCbCr क्रमmats
	 */
	u32 field_off;
	काष्ठा vpfe_ccdc ccdc;
	पूर्णांक stopping;
	काष्ठा completion capture_stop;
पूर्ण;

#पूर्ण_अगर	/* AM437X_VPFE_H */
