<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Xilinx Video Timing Controller
 *
 * Copyright (C) 2013-2015 Ideas on Board
 * Copyright (C) 2013-2015 Xilinx, Inc.
 *
 * Contacts: Hyun Kwon <hyun.kwon@xilinx.com>
 *           Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "xilinx-vip.h"
#समावेश "xilinx-vtc.h"

#घोषणा XVTC_CONTROL_FIELD_ID_POL_SRC		(1 << 26)
#घोषणा XVTC_CONTROL_ACTIVE_CHROMA_POL_SRC	(1 << 25)
#घोषणा XVTC_CONTROL_ACTIVE_VIDEO_POL_SRC	(1 << 24)
#घोषणा XVTC_CONTROL_HSYNC_POL_SRC		(1 << 23)
#घोषणा XVTC_CONTROL_VSYNC_POL_SRC		(1 << 22)
#घोषणा XVTC_CONTROL_HBLANK_POL_SRC		(1 << 21)
#घोषणा XVTC_CONTROL_VBLANK_POL_SRC		(1 << 20)
#घोषणा XVTC_CONTROL_CHROMA_SRC			(1 << 18)
#घोषणा XVTC_CONTROL_VBLANK_HOFF_SRC		(1 << 17)
#घोषणा XVTC_CONTROL_VSYNC_END_SRC		(1 << 16)
#घोषणा XVTC_CONTROL_VSYNC_START_SRC		(1 << 15)
#घोषणा XVTC_CONTROL_ACTIVE_VSIZE_SRC		(1 << 14)
#घोषणा XVTC_CONTROL_FRAME_VSIZE_SRC		(1 << 13)
#घोषणा XVTC_CONTROL_HSYNC_END_SRC		(1 << 11)
#घोषणा XVTC_CONTROL_HSYNC_START_SRC		(1 << 10)
#घोषणा XVTC_CONTROL_ACTIVE_HSIZE_SRC		(1 << 9)
#घोषणा XVTC_CONTROL_FRAME_HSIZE_SRC		(1 << 8)
#घोषणा XVTC_CONTROL_SYNC_ENABLE		(1 << 5)
#घोषणा XVTC_CONTROL_DET_ENABLE			(1 << 3)
#घोषणा XVTC_CONTROL_GEN_ENABLE			(1 << 2)

#घोषणा XVTC_STATUS_FSYNC(n)			((n) << 16)
#घोषणा XVTC_STATUS_GEN_ACTIVE_VIDEO		(1 << 13)
#घोषणा XVTC_STATUS_GEN_VBLANK			(1 << 12)
#घोषणा XVTC_STATUS_DET_ACTIVE_VIDEO		(1 << 11)
#घोषणा XVTC_STATUS_DET_VBLANK			(1 << 10)
#घोषणा XVTC_STATUS_LOCK_LOSS			(1 << 9)
#घोषणा XVTC_STATUS_LOCK			(1 << 8)

#घोषणा XVTC_ERROR_ACTIVE_CHROMA_LOCK		(1 << 21)
#घोषणा XVTC_ERROR_ACTIVE_VIDEO_LOCK		(1 << 20)
#घोषणा XVTC_ERROR_HSYNC_LOCK			(1 << 19)
#घोषणा XVTC_ERROR_VSYNC_LOCK			(1 << 18)
#घोषणा XVTC_ERROR_HBLANK_LOCK			(1 << 17)
#घोषणा XVTC_ERROR_VBLANK_LOCK			(1 << 16)

#घोषणा XVTC_IRQ_ENABLE_FSYNC(n)		((n) << 16)
#घोषणा XVTC_IRQ_ENABLE_GEN_ACTIVE_VIDEO	(1 << 13)
#घोषणा XVTC_IRQ_ENABLE_GEN_VBLANK		(1 << 12)
#घोषणा XVTC_IRQ_ENABLE_DET_ACTIVE_VIDEO	(1 << 11)
#घोषणा XVTC_IRQ_ENABLE_DET_VBLANK		(1 << 10)
#घोषणा XVTC_IRQ_ENABLE_LOCK_LOSS		(1 << 9)
#घोषणा XVTC_IRQ_ENABLE_LOCK			(1 << 8)

/*
 * The following रेजिस्टरs exist in two blocks, one at 0x0020 क्रम the detector
 * and one at 0x0060 क्रम the generator.
 */

#घोषणा XVTC_DETECTOR_OFFSET			0x0020
#घोषणा XVTC_GENERATOR_OFFSET			0x0060

#घोषणा XVTC_ACTIVE_SIZE			0x0000
#घोषणा XVTC_ACTIVE_VSIZE_SHIFT			16
#घोषणा XVTC_ACTIVE_VSIZE_MASK			(0x1fff << 16)
#घोषणा XVTC_ACTIVE_HSIZE_SHIFT			0
#घोषणा XVTC_ACTIVE_HSIZE_MASK			(0x1fff << 0)

#घोषणा XVTC_TIMING_STATUS			0x0004
#घोषणा XVTC_TIMING_STATUS_ACTIVE_VIDEO		(1 << 2)
#घोषणा XVTC_TIMING_STATUS_VBLANK		(1 << 1)
#घोषणा XVTC_TIMING_STATUS_LOCKED		(1 << 0)

#घोषणा XVTC_ENCODING				0x0008
#घोषणा XVTC_ENCODING_CHROMA_PARITY_SHIFT	8
#घोषणा XVTC_ENCODING_CHROMA_PARITY_MASK	(3 << 8)
#घोषणा XVTC_ENCODING_CHROMA_PARITY_EVEN_ALL	(0 << 8)
#घोषणा XVTC_ENCODING_CHROMA_PARITY_ODD_ALL	(1 << 8)
#घोषणा XVTC_ENCODING_CHROMA_PARITY_EVEN_EVEN	(2 << 8)
#घोषणा XVTC_ENCODING_CHROMA_PARITY_ODD_EVEN	(3 << 8)
#घोषणा XVTC_ENCODING_VIDEO_FORMAT_SHIFT	0
#घोषणा XVTC_ENCODING_VIDEO_FORMAT_MASK		(0xf << 0)
#घोषणा XVTC_ENCODING_VIDEO_FORMAT_YUV422	(0 << 0)
#घोषणा XVTC_ENCODING_VIDEO_FORMAT_YUV444	(1 << 0)
#घोषणा XVTC_ENCODING_VIDEO_FORMAT_RGB		(2 << 0)
#घोषणा XVTC_ENCODING_VIDEO_FORMAT_YUV420	(3 << 0)

#घोषणा XVTC_POLARITY				0x000c
#घोषणा XVTC_POLARITY_ACTIVE_CHROMA_POL		(1 << 5)
#घोषणा XVTC_POLARITY_ACTIVE_VIDEO_POL		(1 << 4)
#घोषणा XVTC_POLARITY_HSYNC_POL			(1 << 3)
#घोषणा XVTC_POLARITY_VSYNC_POL			(1 << 2)
#घोषणा XVTC_POLARITY_HBLANK_POL		(1 << 1)
#घोषणा XVTC_POLARITY_VBLANK_POL		(1 << 0)

#घोषणा XVTC_HSIZE				0x0010
#घोषणा XVTC_HSIZE_MASK				(0x1fff << 0)

#घोषणा XVTC_VSIZE				0x0014
#घोषणा XVTC_VSIZE_MASK				(0x1fff << 0)

#घोषणा XVTC_HSYNC				0x0018
#घोषणा XVTC_HSYNC_END_SHIFT			16
#घोषणा XVTC_HSYNC_END_MASK			(0x1fff << 16)
#घोषणा XVTC_HSYNC_START_SHIFT			0
#घोषणा XVTC_HSYNC_START_MASK			(0x1fff << 0)

#घोषणा XVTC_F0_VBLANK_H			0x001c
#घोषणा XVTC_F0_VBLANK_HEND_SHIFT		16
#घोषणा XVTC_F0_VBLANK_HEND_MASK		(0x1fff << 16)
#घोषणा XVTC_F0_VBLANK_HSTART_SHIFT		0
#घोषणा XVTC_F0_VBLANK_HSTART_MASK		(0x1fff << 0)

#घोषणा XVTC_F0_VSYNC_V				0x0020
#घोषणा XVTC_F0_VSYNC_VEND_SHIFT		16
#घोषणा XVTC_F0_VSYNC_VEND_MASK			(0x1fff << 16)
#घोषणा XVTC_F0_VSYNC_VSTART_SHIFT		0
#घोषणा XVTC_F0_VSYNC_VSTART_MASK		(0x1fff << 0)

#घोषणा XVTC_F0_VSYNC_H				0x0024
#घोषणा XVTC_F0_VSYNC_HEND_SHIFT		16
#घोषणा XVTC_F0_VSYNC_HEND_MASK			(0x1fff << 16)
#घोषणा XVTC_F0_VSYNC_HSTART_SHIFT		0
#घोषणा XVTC_F0_VSYNC_HSTART_MASK		(0x1fff << 0)

#घोषणा XVTC_FRAME_SYNC_CONFIG(n)		(0x0100 + 4 * (n))
#घोषणा XVTC_FRAME_SYNC_V_START_SHIFT		16
#घोषणा XVTC_FRAME_SYNC_V_START_MASK		(0x1fff << 16)
#घोषणा XVTC_FRAME_SYNC_H_START_SHIFT		0
#घोषणा XVTC_FRAME_SYNC_H_START_MASK		(0x1fff << 0)

#घोषणा XVTC_GENERATOR_GLOBAL_DELAY		0x0104

/**
 * काष्ठा xvtc_device - Xilinx Video Timing Controller device काष्ठाure
 * @xvip: Xilinx Video IP device
 * @list: entry in the global VTC list
 * @has_detector: the VTC has a timing detector
 * @has_generator: the VTC has a timing generator
 * @config: generator timings configuration
 */
काष्ठा xvtc_device अणु
	काष्ठा xvip_device xvip;
	काष्ठा list_head list;

	bool has_detector;
	bool has_generator;

	काष्ठा xvtc_config config;
पूर्ण;

अटल LIST_HEAD(xvtc_list);
अटल DEFINE_MUTEX(xvtc_lock);

अटल अंतरभूत व्योम xvtc_gen_ग_लिखो(काष्ठा xvtc_device *xvtc, u32 addr, u32 value)
अणु
	xvip_ग_लिखो(&xvtc->xvip, XVTC_GENERATOR_OFFSET + addr, value);
पूर्ण

/* -----------------------------------------------------------------------------
 * Generator Operations
 */

पूर्णांक xvtc_generator_start(काष्ठा xvtc_device *xvtc,
			 स्थिर काष्ठा xvtc_config *config)
अणु
	पूर्णांक ret;

	अगर (!xvtc->has_generator)
		वापस -ENXIO;

	ret = clk_prepare_enable(xvtc->xvip.clk);
	अगर (ret < 0)
		वापस ret;

	/* We करोn't care about the chroma active संकेत, encoding parameters are
	 * not important क्रम now.
	 */
	xvtc_gen_ग_लिखो(xvtc, XVTC_POLARITY,
		       XVTC_POLARITY_ACTIVE_CHROMA_POL |
		       XVTC_POLARITY_ACTIVE_VIDEO_POL |
		       XVTC_POLARITY_HSYNC_POL | XVTC_POLARITY_VSYNC_POL |
		       XVTC_POLARITY_HBLANK_POL | XVTC_POLARITY_VBLANK_POL);

	/* Hardcode the polarity to active high, as required by the video in to
	 * AXI4-stream core.
	 */
	xvtc_gen_ग_लिखो(xvtc, XVTC_ENCODING, 0);

	/* Configure the timings. The VBLANK and VSYNC संकेतs निश्चितion and
	 * deनिश्चितion are hardcoded to the first pixel of the line.
	 */
	xvtc_gen_ग_लिखो(xvtc, XVTC_ACTIVE_SIZE,
		       (config->vblank_start << XVTC_ACTIVE_VSIZE_SHIFT) |
		       (config->hblank_start << XVTC_ACTIVE_HSIZE_SHIFT));
	xvtc_gen_ग_लिखो(xvtc, XVTC_HSIZE, config->hsize);
	xvtc_gen_ग_लिखो(xvtc, XVTC_VSIZE, config->vsize);
	xvtc_gen_ग_लिखो(xvtc, XVTC_HSYNC,
		       (config->hsync_end << XVTC_HSYNC_END_SHIFT) |
		       (config->hsync_start << XVTC_HSYNC_START_SHIFT));
	xvtc_gen_ग_लिखो(xvtc, XVTC_F0_VBLANK_H, 0);
	xvtc_gen_ग_लिखो(xvtc, XVTC_F0_VSYNC_V,
		       (config->vsync_end << XVTC_F0_VSYNC_VEND_SHIFT) |
		       (config->vsync_start << XVTC_F0_VSYNC_VSTART_SHIFT));
	xvtc_gen_ग_लिखो(xvtc, XVTC_F0_VSYNC_H, 0);

	/* Enable the generator. Set the source of all generator parameters to
	 * generator रेजिस्टरs.
	 */
	xvip_ग_लिखो(&xvtc->xvip, XVIP_CTRL_CONTROL,
		   XVTC_CONTROL_ACTIVE_CHROMA_POL_SRC |
		   XVTC_CONTROL_ACTIVE_VIDEO_POL_SRC |
		   XVTC_CONTROL_HSYNC_POL_SRC | XVTC_CONTROL_VSYNC_POL_SRC |
		   XVTC_CONTROL_HBLANK_POL_SRC | XVTC_CONTROL_VBLANK_POL_SRC |
		   XVTC_CONTROL_CHROMA_SRC | XVTC_CONTROL_VBLANK_HOFF_SRC |
		   XVTC_CONTROL_VSYNC_END_SRC | XVTC_CONTROL_VSYNC_START_SRC |
		   XVTC_CONTROL_ACTIVE_VSIZE_SRC |
		   XVTC_CONTROL_FRAME_VSIZE_SRC | XVTC_CONTROL_HSYNC_END_SRC |
		   XVTC_CONTROL_HSYNC_START_SRC |
		   XVTC_CONTROL_ACTIVE_HSIZE_SRC |
		   XVTC_CONTROL_FRAME_HSIZE_SRC | XVTC_CONTROL_GEN_ENABLE |
		   XVIP_CTRL_CONTROL_REG_UPDATE);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xvtc_generator_start);

पूर्णांक xvtc_generator_stop(काष्ठा xvtc_device *xvtc)
अणु
	अगर (!xvtc->has_generator)
		वापस -ENXIO;

	xvip_ग_लिखो(&xvtc->xvip, XVIP_CTRL_CONTROL, 0);

	clk_disable_unprepare(xvtc->xvip.clk);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xvtc_generator_stop);

काष्ठा xvtc_device *xvtc_of_get(काष्ठा device_node *np)
अणु
	काष्ठा device_node *xvtc_node;
	काष्ठा xvtc_device *found = शून्य;
	काष्ठा xvtc_device *xvtc;

	अगर (!of_find_property(np, "xlnx,vtc", शून्य))
		वापस शून्य;

	xvtc_node = of_parse_phandle(np, "xlnx,vtc", 0);
	अगर (xvtc_node == शून्य)
		वापस ERR_PTR(-EINVAL);

	mutex_lock(&xvtc_lock);
	list_क्रम_each_entry(xvtc, &xvtc_list, list) अणु
		अगर (xvtc->xvip.dev->of_node == xvtc_node) अणु
			found = xvtc;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&xvtc_lock);

	of_node_put(xvtc_node);

	अगर (!found)
		वापस ERR_PTR(-EPROBE_DEFER);

	वापस found;
पूर्ण
EXPORT_SYMBOL_GPL(xvtc_of_get);

व्योम xvtc_put(काष्ठा xvtc_device *xvtc)
अणु
पूर्ण
EXPORT_SYMBOL_GPL(xvtc_put);

/* -----------------------------------------------------------------------------
 * Registration and Unregistration
 */

अटल व्योम xvtc_रेजिस्टर_device(काष्ठा xvtc_device *xvtc)
अणु
	mutex_lock(&xvtc_lock);
	list_add_tail(&xvtc->list, &xvtc_list);
	mutex_unlock(&xvtc_lock);
पूर्ण

अटल व्योम xvtc_unरेजिस्टर_device(काष्ठा xvtc_device *xvtc)
अणु
	mutex_lock(&xvtc_lock);
	list_del(&xvtc->list);
	mutex_unlock(&xvtc_lock);
पूर्ण

/* -----------------------------------------------------------------------------
 * Platक्रमm Device Driver
 */

अटल पूर्णांक xvtc_parse_of(काष्ठा xvtc_device *xvtc)
अणु
	काष्ठा device_node *node = xvtc->xvip.dev->of_node;

	xvtc->has_detector = of_property_पढ़ो_bool(node, "xlnx,detector");
	xvtc->has_generator = of_property_पढ़ो_bool(node, "xlnx,generator");

	वापस 0;
पूर्ण

अटल पूर्णांक xvtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xvtc_device *xvtc;
	पूर्णांक ret;

	xvtc = devm_kzalloc(&pdev->dev, माप(*xvtc), GFP_KERNEL);
	अगर (!xvtc)
		वापस -ENOMEM;

	xvtc->xvip.dev = &pdev->dev;

	ret = xvtc_parse_of(xvtc);
	अगर (ret < 0)
		वापस ret;

	ret = xvip_init_resources(&xvtc->xvip);
	अगर (ret < 0)
		वापस ret;

	platक्रमm_set_drvdata(pdev, xvtc);

	xvip_prपूर्णांक_version(&xvtc->xvip);

	xvtc_रेजिस्टर_device(xvtc);

	वापस 0;
पूर्ण

अटल पूर्णांक xvtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xvtc_device *xvtc = platक्रमm_get_drvdata(pdev);

	xvtc_unरेजिस्टर_device(xvtc);

	xvip_cleanup_resources(&xvtc->xvip);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id xvtc_of_id_table[] = अणु
	अणु .compatible = "xlnx,v-tc-6.1" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, xvtc_of_id_table);

अटल काष्ठा platक्रमm_driver xvtc_driver = अणु
	.driver = अणु
		.name = "xilinx-vtc",
		.of_match_table = xvtc_of_id_table,
	पूर्ण,
	.probe = xvtc_probe,
	.हटाओ = xvtc_हटाओ,
पूर्ण;

module_platक्रमm_driver(xvtc_driver);

MODULE_AUTHOR("Laurent Pinchart <laurent.pinchart@ideasonboard.com>");
MODULE_DESCRIPTION("Xilinx Video Timing Controller Driver");
MODULE_LICENSE("GPL v2");
