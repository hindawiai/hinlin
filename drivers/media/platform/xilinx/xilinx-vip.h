<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Xilinx Video IP Core
 *
 * Copyright (C) 2013-2015 Ideas on Board
 * Copyright (C) 2013-2015 Xilinx, Inc.
 *
 * Contacts: Hyun Kwon <hyun.kwon@xilinx.com>
 *           Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#अगर_अघोषित __XILINX_VIP_H__
#घोषणा __XILINX_VIP_H__

#समावेश <linux/bitops.h>
#समावेश <linux/पन.स>
#समावेश <media/v4l2-subdev.h>

काष्ठा clk;

/*
 * Minimum and maximum width and height common to most video IP cores. IP
 * cores with dअगरferent requirements must define their own values.
 */
#घोषणा XVIP_MIN_WIDTH			32
#घोषणा XVIP_MAX_WIDTH			7680
#घोषणा XVIP_MIN_HEIGHT			32
#घोषणा XVIP_MAX_HEIGHT			7680

/*
 * Pad IDs. IP cores with with multiple inमाला_दो or outमाला_दो should define
 * their own values.
 */
#घोषणा XVIP_PAD_SINK			0
#घोषणा XVIP_PAD_SOURCE			1

/* Xilinx Video IP Control Registers */
#घोषणा XVIP_CTRL_CONTROL			0x0000
#घोषणा XVIP_CTRL_CONTROL_SW_ENABLE		BIT(0)
#घोषणा XVIP_CTRL_CONTROL_REG_UPDATE		BIT(1)
#घोषणा XVIP_CTRL_CONTROL_BYPASS		BIT(4)
#घोषणा XVIP_CTRL_CONTROL_TEST_PATTERN		BIT(5)
#घोषणा XVIP_CTRL_CONTROL_FRAME_SYNC_RESET	BIT(30)
#घोषणा XVIP_CTRL_CONTROL_SW_RESET		BIT(31)
#घोषणा XVIP_CTRL_STATUS			0x0004
#घोषणा XVIP_CTRL_STATUS_PROC_STARTED		BIT(0)
#घोषणा XVIP_CTRL_STATUS_खातापूर्ण			BIT(1)
#घोषणा XVIP_CTRL_ERROR				0x0008
#घोषणा XVIP_CTRL_ERROR_SLAVE_EOL_EARLY		BIT(0)
#घोषणा XVIP_CTRL_ERROR_SLAVE_EOL_LATE		BIT(1)
#घोषणा XVIP_CTRL_ERROR_SLAVE_SOF_EARLY		BIT(2)
#घोषणा XVIP_CTRL_ERROR_SLAVE_SOF_LATE		BIT(3)
#घोषणा XVIP_CTRL_IRQ_ENABLE			0x000c
#घोषणा XVIP_CTRL_IRQ_ENABLE_PROC_STARTED	BIT(0)
#घोषणा XVIP_CTRL_IRQ_खातापूर्ण			BIT(1)
#घोषणा XVIP_CTRL_VERSION			0x0010
#घोषणा XVIP_CTRL_VERSION_MAJOR_MASK		(0xff << 24)
#घोषणा XVIP_CTRL_VERSION_MAJOR_SHIFT		24
#घोषणा XVIP_CTRL_VERSION_MINOR_MASK		(0xff << 16)
#घोषणा XVIP_CTRL_VERSION_MINOR_SHIFT		16
#घोषणा XVIP_CTRL_VERSION_REVISION_MASK		(0xf << 12)
#घोषणा XVIP_CTRL_VERSION_REVISION_SHIFT	12
#घोषणा XVIP_CTRL_VERSION_PATCH_MASK		(0xf << 8)
#घोषणा XVIP_CTRL_VERSION_PATCH_SHIFT		8
#घोषणा XVIP_CTRL_VERSION_INTERNAL_MASK		(0xff << 0)
#घोषणा XVIP_CTRL_VERSION_INTERNAL_SHIFT	0

/* Xilinx Video IP Timing Registers */
#घोषणा XVIP_ACTIVE_SIZE			0x0020
#घोषणा XVIP_ACTIVE_VSIZE_MASK			(0x7ff << 16)
#घोषणा XVIP_ACTIVE_VSIZE_SHIFT			16
#घोषणा XVIP_ACTIVE_HSIZE_MASK			(0x7ff << 0)
#घोषणा XVIP_ACTIVE_HSIZE_SHIFT			0
#घोषणा XVIP_ENCODING				0x0028
#घोषणा XVIP_ENCODING_NBITS_8			(0 << 4)
#घोषणा XVIP_ENCODING_NBITS_10			(1 << 4)
#घोषणा XVIP_ENCODING_NBITS_12			(2 << 4)
#घोषणा XVIP_ENCODING_NBITS_16			(3 << 4)
#घोषणा XVIP_ENCODING_NBITS_MASK		(3 << 4)
#घोषणा XVIP_ENCODING_NBITS_SHIFT		4
#घोषणा XVIP_ENCODING_VIDEO_FORMAT_YUV422	(0 << 0)
#घोषणा XVIP_ENCODING_VIDEO_FORMAT_YUV444	(1 << 0)
#घोषणा XVIP_ENCODING_VIDEO_FORMAT_RGB		(2 << 0)
#घोषणा XVIP_ENCODING_VIDEO_FORMAT_YUV420	(3 << 0)
#घोषणा XVIP_ENCODING_VIDEO_FORMAT_MASK		(3 << 0)
#घोषणा XVIP_ENCODING_VIDEO_FORMAT_SHIFT	0

/**
 * काष्ठा xvip_device - Xilinx Video IP device काष्ठाure
 * @subdev: V4L2 subdevice
 * @dev: (OF) device
 * @iomem: device I/O रेजिस्टर space remapped to kernel भव memory
 * @clk: video core घड़ी
 * @saved_ctrl: saved control रेजिस्टर क्रम resume / suspend
 */
काष्ठा xvip_device अणु
	काष्ठा v4l2_subdev subdev;
	काष्ठा device *dev;
	व्योम __iomem *iomem;
	काष्ठा clk *clk;
	u32 saved_ctrl;
पूर्ण;

/**
 * काष्ठा xvip_video_क्रमmat - Xilinx Video IP video क्रमmat description
 * @vf_code: AXI4 video क्रमmat code
 * @width: AXI4 क्रमmat width in bits per component
 * @pattern: CFA pattern क्रम Mono/Sensor क्रमmats
 * @code: media bus क्रमmat code
 * @bpp: bytes per pixel (when stored in memory)
 * @fourcc: V4L2 pixel क्रमmat FCC identअगरier
 */
काष्ठा xvip_video_क्रमmat अणु
	अचिन्हित पूर्णांक vf_code;
	अचिन्हित पूर्णांक width;
	स्थिर अक्षर *pattern;
	अचिन्हित पूर्णांक code;
	अचिन्हित पूर्णांक bpp;
	u32 fourcc;
पूर्ण;

स्थिर काष्ठा xvip_video_क्रमmat *xvip_get_क्रमmat_by_code(अचिन्हित पूर्णांक code);
स्थिर काष्ठा xvip_video_क्रमmat *xvip_get_क्रमmat_by_fourcc(u32 fourcc);
स्थिर काष्ठा xvip_video_क्रमmat *xvip_of_get_क्रमmat(काष्ठा device_node *node);
व्योम xvip_set_क्रमmat_size(काष्ठा v4l2_mbus_framefmt *क्रमmat,
			  स्थिर काष्ठा v4l2_subdev_क्रमmat *fmt);
पूर्णांक xvip_क्रमागत_mbus_code(काष्ठा v4l2_subdev *subdev,
			काष्ठा v4l2_subdev_pad_config *cfg,
			काष्ठा v4l2_subdev_mbus_code_क्रमागत *code);
पूर्णांक xvip_क्रमागत_frame_size(काष्ठा v4l2_subdev *subdev,
			 काष्ठा v4l2_subdev_pad_config *cfg,
			 काष्ठा v4l2_subdev_frame_size_क्रमागत *fse);

अटल अंतरभूत u32 xvip_पढ़ो(काष्ठा xvip_device *xvip, u32 addr)
अणु
	वापस ioपढ़ो32(xvip->iomem + addr);
पूर्ण

अटल अंतरभूत व्योम xvip_ग_लिखो(काष्ठा xvip_device *xvip, u32 addr, u32 value)
अणु
	ioग_लिखो32(value, xvip->iomem + addr);
पूर्ण

अटल अंतरभूत व्योम xvip_clr(काष्ठा xvip_device *xvip, u32 addr, u32 clr)
अणु
	xvip_ग_लिखो(xvip, addr, xvip_पढ़ो(xvip, addr) & ~clr);
पूर्ण

अटल अंतरभूत व्योम xvip_set(काष्ठा xvip_device *xvip, u32 addr, u32 set)
अणु
	xvip_ग_लिखो(xvip, addr, xvip_पढ़ो(xvip, addr) | set);
पूर्ण

व्योम xvip_clr_or_set(काष्ठा xvip_device *xvip, u32 addr, u32 mask, bool set);
व्योम xvip_clr_and_set(काष्ठा xvip_device *xvip, u32 addr, u32 clr, u32 set);

पूर्णांक xvip_init_resources(काष्ठा xvip_device *xvip);
व्योम xvip_cleanup_resources(काष्ठा xvip_device *xvip);

अटल अंतरभूत व्योम xvip_reset(काष्ठा xvip_device *xvip)
अणु
	xvip_ग_लिखो(xvip, XVIP_CTRL_CONTROL, XVIP_CTRL_CONTROL_SW_RESET);
पूर्ण

अटल अंतरभूत व्योम xvip_start(काष्ठा xvip_device *xvip)
अणु
	xvip_set(xvip, XVIP_CTRL_CONTROL,
		 XVIP_CTRL_CONTROL_SW_ENABLE | XVIP_CTRL_CONTROL_REG_UPDATE);
पूर्ण

अटल अंतरभूत व्योम xvip_stop(काष्ठा xvip_device *xvip)
अणु
	xvip_clr(xvip, XVIP_CTRL_CONTROL, XVIP_CTRL_CONTROL_SW_ENABLE);
पूर्ण

अटल अंतरभूत व्योम xvip_resume(काष्ठा xvip_device *xvip)
अणु
	xvip_ग_लिखो(xvip, XVIP_CTRL_CONTROL,
		   xvip->saved_ctrl | XVIP_CTRL_CONTROL_SW_ENABLE);
पूर्ण

अटल अंतरभूत व्योम xvip_suspend(काष्ठा xvip_device *xvip)
अणु
	xvip->saved_ctrl = xvip_पढ़ो(xvip, XVIP_CTRL_CONTROL);
	xvip_ग_लिखो(xvip, XVIP_CTRL_CONTROL,
		   xvip->saved_ctrl & ~XVIP_CTRL_CONTROL_SW_ENABLE);
पूर्ण

अटल अंतरभूत व्योम xvip_set_frame_size(काष्ठा xvip_device *xvip,
				       स्थिर काष्ठा v4l2_mbus_framefmt *क्रमmat)
अणु
	xvip_ग_लिखो(xvip, XVIP_ACTIVE_SIZE,
		   (क्रमmat->height << XVIP_ACTIVE_VSIZE_SHIFT) |
		   (क्रमmat->width << XVIP_ACTIVE_HSIZE_SHIFT));
पूर्ण

अटल अंतरभूत व्योम xvip_get_frame_size(काष्ठा xvip_device *xvip,
				       काष्ठा v4l2_mbus_framefmt *क्रमmat)
अणु
	u32 reg;

	reg = xvip_पढ़ो(xvip, XVIP_ACTIVE_SIZE);
	क्रमmat->width = (reg & XVIP_ACTIVE_HSIZE_MASK) >>
			XVIP_ACTIVE_HSIZE_SHIFT;
	क्रमmat->height = (reg & XVIP_ACTIVE_VSIZE_MASK) >>
			 XVIP_ACTIVE_VSIZE_SHIFT;
पूर्ण

अटल अंतरभूत व्योम xvip_enable_reg_update(काष्ठा xvip_device *xvip)
अणु
	xvip_set(xvip, XVIP_CTRL_CONTROL, XVIP_CTRL_CONTROL_REG_UPDATE);
पूर्ण

अटल अंतरभूत व्योम xvip_disable_reg_update(काष्ठा xvip_device *xvip)
अणु
	xvip_clr(xvip, XVIP_CTRL_CONTROL, XVIP_CTRL_CONTROL_REG_UPDATE);
पूर्ण

अटल अंतरभूत व्योम xvip_prपूर्णांक_version(काष्ठा xvip_device *xvip)
अणु
	u32 version;

	version = xvip_पढ़ो(xvip, XVIP_CTRL_VERSION);

	dev_info(xvip->dev, "device found, version %u.%02x%x\n",
		 ((version & XVIP_CTRL_VERSION_MAJOR_MASK) >>
		  XVIP_CTRL_VERSION_MAJOR_SHIFT),
		 ((version & XVIP_CTRL_VERSION_MINOR_MASK) >>
		  XVIP_CTRL_VERSION_MINOR_SHIFT),
		 ((version & XVIP_CTRL_VERSION_REVISION_MASK) >>
		  XVIP_CTRL_VERSION_REVISION_SHIFT));
पूर्ण

#पूर्ण_अगर /* __XILINX_VIP_H__ */
