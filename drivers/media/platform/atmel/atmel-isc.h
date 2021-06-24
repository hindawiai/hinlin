<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Microchip Image Sensor Controller (ISC) driver header file
 *
 * Copyright (C) 2016-2019 Microchip Technology, Inc.
 *
 * Author: Songjun Wu
 * Author: Eugen Hristev <eugen.hristev@microchip.com>
 *
 */
#अगर_अघोषित _ATMEL_ISC_H_

#घोषणा ISC_MAX_SUPPORT_WIDTH   2592
#घोषणा ISC_MAX_SUPPORT_HEIGHT  1944

#घोषणा ISC_CLK_MAX_DIV		255

क्रमागत isc_clk_id अणु
	ISC_ISPCK = 0,
	ISC_MCK = 1,
पूर्ण;

काष्ठा isc_clk अणु
	काष्ठा clk_hw   hw;
	काष्ठा clk      *clk;
	काष्ठा regmap   *regmap;
	spinlock_t	lock;	/* serialize access to घड़ी रेजिस्टरs */
	u8		id;
	u8		parent_id;
	u32		भाग;
	काष्ठा device	*dev;
पूर्ण;

#घोषणा to_isc_clk(v) container_of(v, काष्ठा isc_clk, hw)

काष्ठा isc_buffer अणु
	काष्ठा vb2_v4l2_buffer  vb;
	काष्ठा list_head	list;
पूर्ण;

काष्ठा isc_subdev_entity अणु
	काष्ठा v4l2_subdev		*sd;
	काष्ठा v4l2_async_subdev	*asd;
	काष्ठा device_node		*epn;
	काष्ठा v4l2_async_notअगरier      notअगरier;

	u32 pfe_cfg0;

	काष्ठा list_head list;
पूर्ण;

/*
 * काष्ठा isc_क्रमmat - ISC media bus क्रमmat inक्रमmation
			This काष्ठाure represents the पूर्णांकerface between the ISC
			and the sensor. It's the input क्रमmat received by
			the ISC.
 * @fourcc:		Fourcc code क्रम this क्रमmat
 * @mbus_code:		V4L2 media bus क्रमmat code.
 * @cfa_baycfg:		If this क्रमmat is RAW BAYER, indicate the type of bayer.
			this is either BGBG, RGRG, etc.
 * @pfe_cfg0_bps:	Number of hardware data lines connected to the ISC
 */

काष्ठा isc_क्रमmat अणु
	u32	fourcc;
	u32	mbus_code;
	u32	cfa_baycfg;

	bool	sd_support;
	u32	pfe_cfg0_bps;
पूर्ण;

/* Pipeline biपंचांगap */
#घोषणा WB_ENABLE	BIT(0)
#घोषणा CFA_ENABLE	BIT(1)
#घोषणा CC_ENABLE	BIT(2)
#घोषणा GAM_ENABLE	BIT(3)
#घोषणा GAM_BENABLE	BIT(4)
#घोषणा GAM_GENABLE	BIT(5)
#घोषणा GAM_RENABLE	BIT(6)
#घोषणा CSC_ENABLE	BIT(7)
#घोषणा CBC_ENABLE	BIT(8)
#घोषणा SUB422_ENABLE	BIT(9)
#घोषणा SUB420_ENABLE	BIT(10)

#घोषणा GAM_ENABLES	(GAM_RENABLE | GAM_GENABLE | GAM_BENABLE | GAM_ENABLE)

/*
 * काष्ठा fmt_config - ISC क्रमmat configuration and पूर्णांकernal pipeline
			This काष्ठाure represents the पूर्णांकernal configuration
			of the ISC.
			It also holds the क्रमmat that ISC will present to v4l2.
 * @sd_क्रमmat:		Poपूर्णांकer to an isc_क्रमmat काष्ठा that holds the sensor
			configuration.
 * @fourcc:		Fourcc code क्रम this क्रमmat.
 * @bpp:		Bytes per pixel in the current क्रमmat.
 * @rlp_cfg_mode:	Configuration of the RLP (rounding, limiting packaging)
 * @dcfg_imode:		Configuration of the input of the DMA module
 * @dctrl_dview:	Configuration of the output of the DMA module
 * @bits_pipeline:	Configuration of the pipeline, which modules are enabled
 */
काष्ठा fmt_config अणु
	काष्ठा isc_क्रमmat	*sd_क्रमmat;

	u32			fourcc;
	u8			bpp;

	u32			rlp_cfg_mode;
	u32			dcfg_imode;
	u32			dctrl_dview;

	u32			bits_pipeline;
पूर्ण;

#घोषणा HIST_ENTRIES		512
#घोषणा HIST_BAYER		(ISC_HIS_CFG_MODE_B + 1)

क्रमागतअणु
	HIST_INIT = 0,
	HIST_ENABLED,
	HIST_DISABLED,
पूर्ण;

काष्ठा isc_ctrls अणु
	काष्ठा v4l2_ctrl_handler handler;

	u32 brightness;
	u32 contrast;
	u8 gamma_index;
#घोषणा ISC_WB_NONE	0
#घोषणा ISC_WB_AUTO	1
#घोषणा ISC_WB_ONETIME	2
	u8 awb;

	/* one क्रम each component : GR, R, GB, B */
	u32 gain[HIST_BAYER];
	s32 offset[HIST_BAYER];

	u32 hist_entry[HIST_ENTRIES];
	u32 hist_count[HIST_BAYER];
	u8 hist_id;
	u8 hist_stat;
#घोषणा HIST_MIN_INDEX		0
#घोषणा HIST_MAX_INDEX		1
	u32 hist_minmax[HIST_BAYER][2];
पूर्ण;

#घोषणा ISC_PIPE_LINE_NODE_NUM	11

/*
 * काष्ठा isc_device - ISC device driver data/config काष्ठा
 * @regmap:		Register map
 * @hघड़ी:		Hघड़ी घड़ी input (refer datasheet)
 * @ispck:		iscpck घड़ी (refer datasheet)
 * @isc_clks:		ISC घड़ीs
 *
 * @dev:		Registered device driver
 * @v4l2_dev:		v4l2 रेजिस्टरed device
 * @video_dev:		रेजिस्टरed video device
 *
 * @vb2_vidq:		video buffer 2 video queue
 * @dma_queue_lock:	lock to serialize the dma buffer queue
 * @dma_queue:		the queue क्रम dma buffers
 * @cur_frm:		current isc frame/buffer
 * @sequence:		current frame number
 * @stop:		true अगर isc is not streaming, false अगर streaming
 * @comp:		completion reference that संकेतs frame completion
 *
 * @fmt:		current v42l क्रमmat
 * @user_क्रमmats:	list of क्रमmats that are supported and agreed with sd
 * @num_user_क्रमmats:	how many क्रमmats are in user_क्रमmats
 *
 * @config:		current ISC क्रमmat configuration
 * @try_config:		the current ISC try क्रमmat , not yet activated
 *
 * @ctrls:		holds inक्रमmation about ISC controls
 * @करो_wb_ctrl:		control regarding the DO_WHITE_BALANCE button
 * @awb_work:		workqueue reference क्रम स्वतःwhitebalance histogram
 *			analysis
 *
 * @lock:		lock क्रम serializing userspace file operations
 *			with ISC operations
 * @awb_lock:		lock क्रम serializing awb work queue operations
 *			with DMA/buffer operations
 *
 * @pipeline:		configuration of the ISC pipeline
 *
 * @current_subdev:	current subdevice: the sensor
 * @subdev_entities:	list of subdevice entitites
 */
काष्ठा isc_device अणु
	काष्ठा regmap		*regmap;
	काष्ठा clk		*hघड़ी;
	काष्ठा clk		*ispck;
	काष्ठा isc_clk		isc_clks[2];

	काष्ठा device		*dev;
	काष्ठा v4l2_device	v4l2_dev;
	काष्ठा video_device	video_dev;

	काष्ठा vb2_queue	vb2_vidq;
	spinlock_t		dma_queue_lock; /* serialize access to dma queue */
	काष्ठा list_head	dma_queue;
	काष्ठा isc_buffer	*cur_frm;
	अचिन्हित पूर्णांक		sequence;
	bool			stop;
	काष्ठा completion	comp;

	काष्ठा v4l2_क्रमmat	fmt;
	काष्ठा isc_क्रमmat	**user_क्रमmats;
	अचिन्हित पूर्णांक		num_user_क्रमmats;

	काष्ठा fmt_config	config;
	काष्ठा fmt_config	try_config;

	काष्ठा isc_ctrls	ctrls;
	काष्ठा work_काष्ठा	awb_work;

	काष्ठा mutex		lock; /* serialize access to file operations */
	spinlock_t		awb_lock; /* serialize access to DMA buffers from awb work queue */

	काष्ठा regmap_field	*pipeline[ISC_PIPE_LINE_NODE_NUM];

	काष्ठा isc_subdev_entity	*current_subdev;
	काष्ठा list_head		subdev_entities;

	काष्ठा अणु
#घोषणा ISC_CTRL_DO_WB 1
#घोषणा ISC_CTRL_R_GAIN 2
#घोषणा ISC_CTRL_B_GAIN 3
#घोषणा ISC_CTRL_GR_GAIN 4
#घोषणा ISC_CTRL_GB_GAIN 5
#घोषणा ISC_CTRL_R_OFF 6
#घोषणा ISC_CTRL_B_OFF 7
#घोषणा ISC_CTRL_GR_OFF 8
#घोषणा ISC_CTRL_GB_OFF 9
		काष्ठा v4l2_ctrl	*awb_ctrl;
		काष्ठा v4l2_ctrl	*करो_wb_ctrl;
		काष्ठा v4l2_ctrl	*r_gain_ctrl;
		काष्ठा v4l2_ctrl	*b_gain_ctrl;
		काष्ठा v4l2_ctrl	*gr_gain_ctrl;
		काष्ठा v4l2_ctrl	*gb_gain_ctrl;
		काष्ठा v4l2_ctrl	*r_off_ctrl;
		काष्ठा v4l2_ctrl	*b_off_ctrl;
		काष्ठा v4l2_ctrl	*gr_off_ctrl;
		काष्ठा v4l2_ctrl	*gb_off_ctrl;
	पूर्ण;
पूर्ण;

#घोषणा GAMMA_MAX	2
#घोषणा GAMMA_ENTRIES	64

#घोषणा ATMEL_ISC_NAME "atmel-isc"

बाह्य काष्ठा isc_क्रमmat क्रमmats_list[];
बाह्य स्थिर काष्ठा isc_क्रमmat controller_क्रमmats[];
बाह्य स्थिर u32 isc_gamma_table[GAMMA_MAX + 1][GAMMA_ENTRIES];
बाह्य स्थिर काष्ठा regmap_config isc_regmap_config;
बाह्य स्थिर काष्ठा v4l2_async_notअगरier_operations isc_async_ops;

irqवापस_t isc_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
पूर्णांक isc_pipeline_init(काष्ठा isc_device *isc);
पूर्णांक isc_clk_init(काष्ठा isc_device *isc);
व्योम isc_subdev_cleanup(काष्ठा isc_device *isc);
व्योम isc_clk_cleanup(काष्ठा isc_device *isc);

#पूर्ण_अगर
