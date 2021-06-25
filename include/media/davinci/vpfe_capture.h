<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2008-2009 Texas Instruments Inc
 */

#अगर_अघोषित _VPFE_CAPTURE_H
#घोषणा _VPFE_CAPTURE_H

#अगर_घोषित __KERNEL__

/* Header files */
#समावेश <media/v4l2-dev.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/clk.h>
#समावेश <linux/i2c.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/videobuf-dma-contig.h>
#समावेश <media/davinci/vpfe_types.h>

#घोषणा VPFE_CAPTURE_NUM_DECODERS        5

/* Macros */
#घोषणा VPFE_MAJOR_RELEASE              0
#घोषणा VPFE_MINOR_RELEASE              0
#घोषणा VPFE_BUILD                      1
#घोषणा VPFE_CAPTURE_VERSION_CODE       ((VPFE_MAJOR_RELEASE << 16) | \
					(VPFE_MINOR_RELEASE << 8)  | \
					VPFE_BUILD)

#घोषणा CAPTURE_DRV_NAME		"vpfe-capture"

काष्ठा vpfe_pixel_क्रमmat अणु
	u32 pixelक्रमmat;
	/* bytes per pixel */
	पूर्णांक bpp;
पूर्ण;

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
	/* Sub device name */
	अक्षर name[32];
	/* Sub device group id */
	पूर्णांक grp_id;
	/* Number of inमाला_दो supported */
	पूर्णांक num_inमाला_दो;
	/* inमाला_दो available at the sub device */
	काष्ठा v4l2_input *inमाला_दो;
	/* Sub dev routing inक्रमmation क्रम each input */
	काष्ठा vpfe_route *routes;
	/* check अगर sub dev supports routing */
	पूर्णांक can_route;
	/* ccdc bus/पूर्णांकerface configuration */
	काष्ठा vpfe_hw_अगर_param ccdc_अगर_params;
	/* i2c subdevice board info */
	काष्ठा i2c_board_info board_info;
पूर्ण;

काष्ठा vpfe_config अणु
	/* Number of sub devices connected to vpfe */
	पूर्णांक num_subdevs;
	/* i2c bus adapter no */
	पूर्णांक i2c_adapter_id;
	/* inक्रमmation about each subdev */
	काष्ठा vpfe_subdev_info *sub_devs;
	/* evm card info */
	अक्षर *card_name;
	/* ccdc name */
	अक्षर *ccdc;
	/* vpfe घड़ी */
	काष्ठा clk *vpssclk;
	काष्ठा clk *slaveclk;
	/* Function क्रम Clearing the पूर्णांकerrupt */
	व्योम (*clr_पूर्णांकr)(पूर्णांक vdपूर्णांक);
पूर्ण;

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
	/* number of खोलो instances of the channel */
	u32 usrs;
	/* Indicates id of the field which is being displayed */
	u32 field_id;
	/* flag to indicate whether decoder is initialized */
	u8 initialized;
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
	/* CCDC IRQs used when CCDC/ISIF output to SDRAM */
	अचिन्हित पूर्णांक ccdc_irq0;
	अचिन्हित पूर्णांक ccdc_irq1;
	/* number of buffers in fbuffers */
	u32 numbuffers;
	/* List of buffer poपूर्णांकers क्रम storing frames */
	u8 *fbuffers[VIDEO_MAX_FRAME];
	/* Poपूर्णांकer poपूर्णांकing to current v4l2_buffer */
	काष्ठा videobuf_buffer *cur_frm;
	/* Poपूर्णांकer poपूर्णांकing to next v4l2_buffer */
	काष्ठा videobuf_buffer *next_frm;
	/*
	 * This field keeps track of type of buffer exchange mechanism
	 * user has selected
	 */
	क्रमागत v4l2_memory memory;
	/* Used to store pixel क्रमmat */
	काष्ठा v4l2_क्रमmat fmt;
	/*
	 * used when IMP is chained to store the crop winकरोw which
	 * is dअगरferent from the image winकरोw
	 */
	काष्ठा v4l2_rect crop;
	/* Buffer queue used in video-buf */
	काष्ठा videobuf_queue buffer_queue;
	/* Queue of filled frames */
	काष्ठा list_head dma_queue;
	/* Used in video-buf */
	spinlock_t irqlock;
	/* IRQ lock क्रम DMA queue */
	spinlock_t dma_queue_lock;
	/* lock used to access this काष्ठाure */
	काष्ठा mutex lock;
	/* number of users perक्रमming IO */
	u32 io_usrs;
	/* Indicates whether streaming started */
	u8 started;
	/*
	 * offset where second field starts from the starting of the
	 * buffer क्रम field separated YCbCr क्रमmats
	 */
	u32 field_off;
पूर्ण;

/* File handle काष्ठाure */
काष्ठा vpfe_fh अणु
	काष्ठा v4l2_fh fh;
	काष्ठा vpfe_device *vpfe_dev;
	/* Indicates whether this file handle is करोing IO */
	u8 io_allowed;
पूर्ण;

काष्ठा vpfe_config_params अणु
	u8 min_numbuffers;
	u8 numbuffers;
	u32 min_bufsize;
	u32 device_bufsize;
पूर्ण;

#पूर्ण_अगर				/* End of __KERNEL__ */
#पूर्ण_अगर				/* _DAVINCI_VPFE_H */
