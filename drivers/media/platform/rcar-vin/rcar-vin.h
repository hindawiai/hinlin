<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Driver क्रम Renesas R-Car VIN
 *
 * Copyright (C) 2016 Renesas Electronics Corp.
 * Copyright (C) 2011-2013 Renesas Solutions Corp.
 * Copyright (C) 2013 Cogent Embedded, Inc., <source@cogentembedded.com>
 * Copyright (C) 2008 Magnus Damm
 *
 * Based on the soc-camera rcar_vin driver
 */

#अगर_अघोषित __RCAR_VIN__
#घोषणा __RCAR_VIN__

#समावेश <linux/kref.h>

#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-dev.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-fwnode.h>
#समावेश <media/videobuf2-v4l2.h>

/* Number of HW buffers */
#घोषणा HW_BUFFER_NUM 3

/* Address alignment mask क्रम HW buffers */
#घोषणा HW_BUFFER_MASK 0x7f

/* Max number on VIN instances that can be in a प्रणाली */
#घोषणा RCAR_VIN_NUM 8

काष्ठा rvin_group;

क्रमागत model_id अणु
	RCAR_H1,
	RCAR_M1,
	RCAR_GEN2,
	RCAR_GEN3,
पूर्ण;

क्रमागत rvin_csi_id अणु
	RVIN_CSI20,
	RVIN_CSI21,
	RVIN_CSI40,
	RVIN_CSI41,
	RVIN_CSI_MAX,
पूर्ण;

/**
 * क्रमागत rvin_dma_state - DMA states
 * @STOPPED:   No operation in progress
 * @STARTING:  Capture starting up
 * @RUNNING:   Operation in progress have buffers
 * @STOPPING:  Stopping operation
 * @SUSPENDED: Capture is suspended
 */
क्रमागत rvin_dma_state अणु
	STOPPED = 0,
	STARTING,
	RUNNING,
	STOPPING,
	SUSPENDED,
पूर्ण;

/**
 * क्रमागत rvin_buffer_type
 *
 * Describes how a buffer is given to the hardware. To be able
 * to capture SEQ_TB/BT it's needed to capture to the same vb2
 * buffer twice so the type of buffer needs to be kept.
 *
 * @FULL: One capture fills the whole vb2 buffer
 * @HALF_TOP: One capture fills the top half of the vb2 buffer
 * @HALF_BOTTOM: One capture fills the bottom half of the vb2 buffer
 */
क्रमागत rvin_buffer_type अणु
	FULL,
	HALF_TOP,
	HALF_BOTTOM,
पूर्ण;

/**
 * काष्ठा rvin_video_क्रमmat - Data क्रमmat stored in memory
 * @fourcc:	Pixelक्रमmat
 * @bpp:	Bytes per pixel
 */
काष्ठा rvin_video_क्रमmat अणु
	u32 fourcc;
	u8 bpp;
पूर्ण;

/**
 * काष्ठा rvin_parallel_entity - Parallel video input endpoपूर्णांक descriptor
 * @asd:	sub-device descriptor क्रम async framework
 * @subdev:	subdevice matched using async framework
 * @mbus_type:	media bus type
 * @bus:	media bus parallel configuration
 * @source_pad:	source pad of remote subdevice
 * @sink_pad:	sink pad of remote subdevice
 *
 */
काष्ठा rvin_parallel_entity अणु
	काष्ठा v4l2_async_subdev *asd;
	काष्ठा v4l2_subdev *subdev;

	क्रमागत v4l2_mbus_type mbus_type;
	काष्ठा v4l2_fwnode_bus_parallel bus;

	अचिन्हित पूर्णांक source_pad;
	अचिन्हित पूर्णांक sink_pad;
पूर्ण;

/**
 * काष्ठा rvin_group_route - describes a route from a channel of a
 *	CSI-2 receiver to a VIN
 *
 * @csi:	CSI-2 receiver ID.
 * @channel:	Output channel of the CSI-2 receiver.
 * @vin:	VIN ID.
 * @mask:	Biपंचांगask of the dअगरferent CHSEL रेजिस्टर values that
 *		allow क्रम a route from @csi + @chan to @vin.
 *
 * .. note::
 *	Each R-Car CSI-2 receiver has four output channels facing the VIN
 *	devices, each channel can carry one CSI-2 Virtual Channel (VC).
 *	There is no correlation between channel number and CSI-2 VC. It's
 *	up to the CSI-2 receiver driver to configure which VC is output
 *	on which channel, the VIN devices only care about output channels.
 *
 *	There are in some हालs multiple CHSEL रेजिस्टर settings which would
 *	allow क्रम the same route from @csi + @channel to @vin. For example
 *	on R-Car H3 both the CHSEL values 0 and 3 allow क्रम a route from
 *	CSI40/VC0 to VIN0. All possible CHSEL values क्रम a route need to be
 *	recorded as a biपंचांगask in @mask, in this example bit 0 and 3 should
 *	be set.
 */
काष्ठा rvin_group_route अणु
	क्रमागत rvin_csi_id csi;
	अचिन्हित पूर्णांक channel;
	अचिन्हित पूर्णांक vin;
	अचिन्हित पूर्णांक mask;
पूर्ण;

/**
 * काष्ठा rvin_info - Inक्रमmation about the particular VIN implementation
 * @model:		VIN model
 * @use_mc:		use media controller instead of controlling subdevice
 * @nv12:		support outputing NV12 pixel क्रमmat
 * @max_width:		max input width the VIN supports
 * @max_height:		max input height the VIN supports
 * @routes:		list of possible routes from the CSI-2 recivers to
 *			all VINs. The list mush be शून्य terminated.
 */
काष्ठा rvin_info अणु
	क्रमागत model_id model;
	bool use_mc;
	bool nv12;

	अचिन्हित पूर्णांक max_width;
	अचिन्हित पूर्णांक max_height;
	स्थिर काष्ठा rvin_group_route *routes;
पूर्ण;

/**
 * काष्ठा rvin_dev - Renesas VIN device काष्ठाure
 * @dev:		(OF) device
 * @base:		device I/O रेजिस्टर space remapped to भव memory
 * @info:		info about VIN instance
 *
 * @vdev:		V4L2 video device associated with VIN
 * @v4l2_dev:		V4L2 device
 * @ctrl_handler:	V4L2 control handler
 * @notअगरier:		V4L2 asynchronous subdevs notअगरier
 *
 * @parallel:		parallel input subdevice descriptor
 *
 * @group:		Gen3 CSI group
 * @id:			Gen3 group id क्रम this VIN
 * @pad:		media pad क्रम the video device entity
 *
 * @lock:		protects @queue
 * @queue:		vb2 buffers queue
 * @scratch:		cpu address क्रम scratch buffer
 * @scratch_phys:	physical address of the scratch buffer
 *
 * @qlock:		protects @buf_hw, @buf_list, @sequence and @state
 * @buf_hw:		Keeps track of buffers given to HW slot
 * @buf_list:		list of queued buffers
 * @sequence:		V4L2 buffers sequence number
 * @state:		keeps track of operation state
 *
 * @is_csi:		flag to mark the VIN as using a CSI-2 subdevice
 * @chsel:		Cached value of the current CSI-2 channel selection
 *
 * @mbus_code:		media bus क्रमmat code
 * @क्रमmat:		active V4L2 pixel क्रमmat
 *
 * @crop:		active cropping
 * @compose:		active composing
 * @src_rect:		active size of the video source
 * @std:		active video standard of the video source
 *
 * @alpha:		Alpha component to fill in क्रम supported pixel क्रमmats
 */
काष्ठा rvin_dev अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	स्थिर काष्ठा rvin_info *info;

	काष्ठा video_device vdev;
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा v4l2_ctrl_handler ctrl_handler;
	काष्ठा v4l2_async_notअगरier notअगरier;

	काष्ठा rvin_parallel_entity parallel;

	काष्ठा rvin_group *group;
	अचिन्हित पूर्णांक id;
	काष्ठा media_pad pad;

	काष्ठा mutex lock;
	काष्ठा vb2_queue queue;
	व्योम *scratch;
	dma_addr_t scratch_phys;

	spinlock_t qlock;
	काष्ठा अणु
		काष्ठा vb2_v4l2_buffer *buffer;
		क्रमागत rvin_buffer_type type;
		dma_addr_t phys;
	पूर्ण buf_hw[HW_BUFFER_NUM];
	काष्ठा list_head buf_list;
	अचिन्हित पूर्णांक sequence;
	क्रमागत rvin_dma_state state;

	bool is_csi;
	अचिन्हित पूर्णांक chsel;

	u32 mbus_code;
	काष्ठा v4l2_pix_क्रमmat क्रमmat;

	काष्ठा v4l2_rect crop;
	काष्ठा v4l2_rect compose;
	काष्ठा v4l2_rect src_rect;
	v4l2_std_id std;

	अचिन्हित पूर्णांक alpha;
पूर्ण;

#घोषणा vin_to_source(vin)		((vin)->parallel.subdev)

/* Debug */
#घोषणा vin_dbg(d, fmt, arg...)		dev_dbg(d->dev, fmt, ##arg)
#घोषणा vin_info(d, fmt, arg...)	dev_info(d->dev, fmt, ##arg)
#घोषणा vin_warn(d, fmt, arg...)	dev_warn(d->dev, fmt, ##arg)
#घोषणा vin_err(d, fmt, arg...)		dev_err(d->dev, fmt, ##arg)

/**
 * काष्ठा rvin_group - VIN CSI2 group inक्रमmation
 * @refcount:		number of VIN instances using the group
 *
 * @mdev:		media device which represents the group
 *
 * @lock:		protects the count, notअगरier, vin and csi members
 * @count:		number of enabled VIN instances found in DT
 * @notअगरier:		group notअगरier क्रम CSI-2 async subdevices
 * @vin:		VIN instances which are part of the group
 * @csi:		array of pairs of fwnode and subdev poपूर्णांकers
 *			to all CSI-2 subdevices.
 */
काष्ठा rvin_group अणु
	काष्ठा kref refcount;

	काष्ठा media_device mdev;

	काष्ठा mutex lock;
	अचिन्हित पूर्णांक count;
	काष्ठा v4l2_async_notअगरier notअगरier;
	काष्ठा rvin_dev *vin[RCAR_VIN_NUM];

	काष्ठा अणु
		काष्ठा v4l2_async_subdev *asd;
		काष्ठा v4l2_subdev *subdev;
	पूर्ण csi[RVIN_CSI_MAX];
पूर्ण;

पूर्णांक rvin_dma_रेजिस्टर(काष्ठा rvin_dev *vin, पूर्णांक irq);
व्योम rvin_dma_unरेजिस्टर(काष्ठा rvin_dev *vin);

पूर्णांक rvin_v4l2_रेजिस्टर(काष्ठा rvin_dev *vin);
व्योम rvin_v4l2_unरेजिस्टर(काष्ठा rvin_dev *vin);

स्थिर काष्ठा rvin_video_क्रमmat *rvin_क्रमmat_from_pixel(काष्ठा rvin_dev *vin,
						       u32 pixelक्रमmat);


/* Cropping, composing and scaling */
व्योम rvin_crop_scale_comp(काष्ठा rvin_dev *vin);

पूर्णांक rvin_set_channel_routing(काष्ठा rvin_dev *vin, u8 chsel);
व्योम rvin_set_alpha(काष्ठा rvin_dev *vin, अचिन्हित पूर्णांक alpha);

पूर्णांक rvin_start_streaming(काष्ठा rvin_dev *vin);
व्योम rvin_stop_streaming(काष्ठा rvin_dev *vin);

#पूर्ण_अगर
