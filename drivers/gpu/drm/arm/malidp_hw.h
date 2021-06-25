<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * (C) COPYRIGHT 2013-2016 ARM Limited. All rights reserved.
 *
 * ARM Mali DP hardware manipulation routines.
 */

#अगर_अघोषित __MALIDP_HW_H__
#घोषणा __MALIDP_HW_H__

#समावेश <linux/bitops.h>
#समावेश "malidp_regs.h"

काष्ठा videomode;
काष्ठा clk;

/* Mali DP IP blocks */
क्रमागत अणु
	MALIDP_DE_BLOCK = 0,
	MALIDP_SE_BLOCK,
	MALIDP_DC_BLOCK
पूर्ण;

/* Mali DP layer IDs */
क्रमागत अणु
	DE_VIDEO1 = BIT(0),
	DE_GRAPHICS1 = BIT(1),
	DE_GRAPHICS2 = BIT(2), /* used only in DP500 */
	DE_VIDEO2 = BIT(3),
	DE_SMART = BIT(4),
	SE_MEMWRITE = BIT(5),
पूर्ण;

क्रमागत rotation_features अणु
	ROTATE_NONE,		/* करोes not support rotation at all */
	ROTATE_ANY,		/* supports rotation on any buffers */
	ROTATE_COMPRESSED,	/* supports rotation only on compressed buffers */
पूर्ण;

काष्ठा malidp_क्रमmat_id अणु
	u32 क्रमmat;		/* DRM fourcc */
	u8 layer;		/* biपंचांगask of layers supporting it */
	u8 id;			/* used पूर्णांकernally */
पूर्ण;

#घोषणा MALIDP_INVALID_FORMAT_ID	0xff

/*
 * hide the dअगरferences between रेजिस्टर maps
 * by using a common काष्ठाure to hold the
 * base रेजिस्टर offsets
 */

काष्ठा malidp_irq_map अणु
	u32 irq_mask;		/* mask of IRQs that can be enabled in the block */
	u32 vsync_irq;		/* IRQ bit used क्रम संकेतing during VSYNC */
	u32 err_mask;		/* mask of bits that represent errors */
पूर्ण;

काष्ठा malidp_layer अणु
	u16 id;			/* layer ID */
	u16 base;		/* address offset क्रम the रेजिस्टर bank */
	u16 ptr;		/* address offset क्रम the poपूर्णांकer रेजिस्टर */
	u16 stride_offset;	/* offset to the first stride रेजिस्टर. */
	s16 yuv2rgb_offset;	/* offset to the YUV->RGB matrix entries */
	u16 mmu_ctrl_offset;    /* offset to the MMU control रेजिस्टर */
	क्रमागत rotation_features rot;	/* type of rotation supported */
	/* address offset क्रम the AFBC decoder रेजिस्टरs */
	u16 afbc_decoder_offset;
पूर्ण;

क्रमागत malidp_scaling_coeff_set अणु
	MALIDP_UPSCALING_COEFFS = 1,
	MALIDP_DOWNSCALING_1_5_COEFFS = 2,
	MALIDP_DOWNSCALING_2_COEFFS = 3,
	MALIDP_DOWNSCALING_2_75_COEFFS = 4,
	MALIDP_DOWNSCALING_4_COEFFS = 5,
पूर्ण;

काष्ठा malidp_se_config अणु
	u8 scale_enable : 1;
	u8 enhancer_enable : 1;
	u8 hcoeff : 3;
	u8 vcoeff : 3;
	u8 plane_src_id;
	u16 input_w, input_h;
	u16 output_w, output_h;
	u32 h_init_phase, h_delta_phase;
	u32 v_init_phase, v_delta_phase;
पूर्ण;

/* regmap features */
#घोषणा MALIDP_REGMAP_HAS_CLEARIRQ				BIT(0)
#घोषणा MALIDP_DEVICE_AFBC_SUPPORT_SPLIT			BIT(1)
#घोषणा MALIDP_DEVICE_AFBC_YUV_420_10_SUPPORT_SPLIT		BIT(2)
#घोषणा MALIDP_DEVICE_AFBC_YUYV_USE_422_P2			BIT(3)

काष्ठा malidp_hw_regmap अणु
	/* address offset of the DE रेजिस्टर bank */
	/* is always 0x0000 */
	/* address offset of the DE coefficients रेजिस्टरs */
	स्थिर u16 coeffs_base;
	/* address offset of the SE रेजिस्टरs bank */
	स्थिर u16 se_base;
	/* address offset of the DC रेजिस्टरs bank */
	स्थिर u16 dc_base;

	/* address offset क्रम the output depth रेजिस्टर */
	स्थिर u16 out_depth_base;

	/* biपंचांगap with रेजिस्टर map features */
	स्थिर u8 features;

	/* list of supported layers */
	स्थिर u8 n_layers;
	स्थिर काष्ठा malidp_layer *layers;

	स्थिर काष्ठा malidp_irq_map de_irq_map;
	स्थिर काष्ठा malidp_irq_map se_irq_map;
	स्थिर काष्ठा malidp_irq_map dc_irq_map;

	/* list of supported pixel क्रमmats क्रम each layer */
	स्थिर काष्ठा malidp_क्रमmat_id *pixel_क्रमmats;
	स्थिर u8 n_pixel_क्रमmats;

	/* pitch alignment requirement in bytes */
	स्थिर u8 bus_align_bytes;
पूर्ण;

/* device features */
/* Unlike DP550/650, DP500 has 3 stride रेजिस्टरs in its video layer. */
#घोषणा MALIDP_DEVICE_LV_HAS_3_STRIDES	BIT(0)

काष्ठा malidp_hw_device;

/*
 * Static काष्ठाure containing hardware specअगरic data and poपूर्णांकers to
 * functions that behave dअगरferently between various versions of the IP.
 */
काष्ठा malidp_hw अणु
	स्थिर काष्ठा malidp_hw_regmap map;

	/*
	 * Validate the driver instance against the hardware bits
	 */
	पूर्णांक (*query_hw)(काष्ठा malidp_hw_device *hwdev);

	/*
	 * Set the hardware पूर्णांकo config mode, पढ़ोy to accept mode changes
	 */
	व्योम (*enter_config_mode)(काष्ठा malidp_hw_device *hwdev);

	/*
	 * Tell hardware to निकास configuration mode
	 */
	व्योम (*leave_config_mode)(काष्ठा malidp_hw_device *hwdev);

	/*
	 * Query अगर hardware is in configuration mode
	 */
	bool (*in_config_mode)(काष्ठा malidp_hw_device *hwdev);

	/*
	 * Set/clear configuration valid flag क्रम hardware parameters that can
	 * be changed outside the configuration mode to the given value.
	 * Hardware will use the new settings when config valid is set,
	 * after the end of the current buffer scanout, and will ignore
	 * any new values क्रम those parameters अगर config valid flag is cleared
	 */
	व्योम (*set_config_valid)(काष्ठा malidp_hw_device *hwdev, u8 value);

	/*
	 * Set a new mode in hardware. Requires the hardware to be in
	 * configuration mode beक्रमe this function is called.
	 */
	व्योम (*modeset)(काष्ठा malidp_hw_device *hwdev, काष्ठा videomode *m);

	/*
	 * Calculate the required rotation memory given the active area
	 * and the buffer क्रमmat.
	 */
	पूर्णांक (*roपंचांगem_required)(काष्ठा malidp_hw_device *hwdev, u16 w, u16 h,
			       u32 fmt, bool has_modअगरier);

	पूर्णांक (*se_set_scaling_coeffs)(काष्ठा malidp_hw_device *hwdev,
				     काष्ठा malidp_se_config *se_config,
				     काष्ठा malidp_se_config *old_config);

	दीर्घ (*se_calc_mclk)(काष्ठा malidp_hw_device *hwdev,
			     काष्ठा malidp_se_config *se_config,
			     काष्ठा videomode *vm);
	/*
	 * Enable writing to memory the content of the next frame
	 * @param hwdev - malidp_hw_device काष्ठाure containing the HW description
	 * @param addrs - array of addresses क्रम each plane
	 * @param pitches - array of pitches क्रम each plane
	 * @param num_planes - number of planes to be written
	 * @param w - width of the output frame
	 * @param h - height of the output frame
	 * @param fmt_id - पूर्णांकernal क्रमmat ID of output buffer
	 */
	पूर्णांक (*enable_memग_लिखो)(काष्ठा malidp_hw_device *hwdev, dma_addr_t *addrs,
			       s32 *pitches, पूर्णांक num_planes, u16 w, u16 h, u32 fmt_id,
			       स्थिर s16 *rgb2yuv_coeffs);

	/*
	 * Disable the writing to memory of the next frame's content.
	 */
	व्योम (*disable_memग_लिखो)(काष्ठा malidp_hw_device *hwdev);

	u8 features;
पूर्ण;

/* Supported variants of the hardware */
क्रमागत अणु
	MALIDP_500 = 0,
	MALIDP_550,
	MALIDP_650,
	/* keep the next entry last */
	MALIDP_MAX_DEVICES
पूर्ण;

बाह्य स्थिर काष्ठा malidp_hw malidp_device[MALIDP_MAX_DEVICES];

/*
 * Structure used by the driver during runसमय operation.
 */
काष्ठा malidp_hw_device अणु
	काष्ठा malidp_hw *hw;
	व्योम __iomem *regs;

	/* APB घड़ी */
	काष्ठा clk *pclk;
	/* AXI घड़ी */
	काष्ठा clk *aclk;
	/* मुख्य घड़ी क्रम display core */
	काष्ठा clk *mclk;
	/* pixel घड़ी क्रम display core */
	काष्ठा clk *pxlclk;

	u8 min_line_size;
	u16 max_line_size;
	u32 output_color_depth;

	/* track the device PM state */
	bool pm_suspended;

	/* track the SE memory ग_लिखोback state */
	u8 mw_state;

	/* size of memory used क्रम rotating layers, up to two banks available */
	u32 rotation_memory[2];

	/* priority level of RQOS रेजिस्टर used क्रम driven the ARQOS संकेत */
	u32 arqos_value;
पूर्ण;

अटल अंतरभूत u32 malidp_hw_पढ़ो(काष्ठा malidp_hw_device *hwdev, u32 reg)
अणु
	WARN_ON(hwdev->pm_suspended);
	वापस पढ़ोl(hwdev->regs + reg);
पूर्ण

अटल अंतरभूत व्योम malidp_hw_ग_लिखो(काष्ठा malidp_hw_device *hwdev,
				   u32 value, u32 reg)
अणु
	WARN_ON(hwdev->pm_suspended);
	ग_लिखोl(value, hwdev->regs + reg);
पूर्ण

अटल अंतरभूत व्योम malidp_hw_setbits(काष्ठा malidp_hw_device *hwdev,
				     u32 mask, u32 reg)
अणु
	u32 data = malidp_hw_पढ़ो(hwdev, reg);

	data |= mask;
	malidp_hw_ग_लिखो(hwdev, data, reg);
पूर्ण

अटल अंतरभूत व्योम malidp_hw_clearbits(काष्ठा malidp_hw_device *hwdev,
				       u32 mask, u32 reg)
अणु
	u32 data = malidp_hw_पढ़ो(hwdev, reg);

	data &= ~mask;
	malidp_hw_ग_लिखो(hwdev, data, reg);
पूर्ण

अटल अंतरभूत u32 malidp_get_block_base(काष्ठा malidp_hw_device *hwdev,
					u8 block)
अणु
	चयन (block) अणु
	हाल MALIDP_SE_BLOCK:
		वापस hwdev->hw->map.se_base;
	हाल MALIDP_DC_BLOCK:
		वापस hwdev->hw->map.dc_base;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम malidp_hw_disable_irq(काष्ठा malidp_hw_device *hwdev,
					 u8 block, u32 irq)
अणु
	u32 base = malidp_get_block_base(hwdev, block);

	malidp_hw_clearbits(hwdev, irq, base + MALIDP_REG_MASKIRQ);
पूर्ण

अटल अंतरभूत व्योम malidp_hw_enable_irq(काष्ठा malidp_hw_device *hwdev,
					u8 block, u32 irq)
अणु
	u32 base = malidp_get_block_base(hwdev, block);

	malidp_hw_setbits(hwdev, irq, base + MALIDP_REG_MASKIRQ);
पूर्ण

पूर्णांक malidp_de_irq_init(काष्ठा drm_device *drm, पूर्णांक irq);
व्योम malidp_se_irq_hw_init(काष्ठा malidp_hw_device *hwdev);
व्योम malidp_de_irq_hw_init(काष्ठा malidp_hw_device *hwdev);
व्योम malidp_de_irq_fini(काष्ठा malidp_hw_device *hwdev);
पूर्णांक malidp_se_irq_init(काष्ठा drm_device *drm, पूर्णांक irq);
व्योम malidp_se_irq_fini(काष्ठा malidp_hw_device *hwdev);

u8 malidp_hw_get_क्रमmat_id(स्थिर काष्ठा malidp_hw_regmap *map,
			   u8 layer_id, u32 क्रमmat, bool has_modअगरier);

पूर्णांक malidp_क्रमmat_get_bpp(u32 fmt);

अटल अंतरभूत u8 malidp_hw_get_pitch_align(काष्ठा malidp_hw_device *hwdev, bool rotated)
अणु
	/*
	 * only hardware that cannot करो 8 bytes bus alignments have further
	 * स्थिरraपूर्णांकs on rotated planes
	 */
	अगर (hwdev->hw->map.bus_align_bytes == 8)
		वापस 8;
	अन्यथा
		वापस hwdev->hw->map.bus_align_bytes << (rotated ? 2 : 0);
पूर्ण

/* U16.16 */
#घोषणा FP_1_00000	0x00010000	/* 1.0 */
#घोषणा FP_0_66667	0x0000AAAA	/* 0.6667 = 1/1.5 */
#घोषणा FP_0_50000	0x00008000	/* 0.5 = 1/2 */
#घोषणा FP_0_36363	0x00005D17	/* 0.36363 = 1/2.75 */
#घोषणा FP_0_25000	0x00004000	/* 0.25 = 1/4 */

अटल अंतरभूत क्रमागत malidp_scaling_coeff_set
malidp_se_select_coeffs(u32 upscale_factor)
अणु
	वापस (upscale_factor >= FP_1_00000) ? MALIDP_UPSCALING_COEFFS :
	       (upscale_factor >= FP_0_66667) ? MALIDP_DOWNSCALING_1_5_COEFFS :
	       (upscale_factor >= FP_0_50000) ? MALIDP_DOWNSCALING_2_COEFFS :
	       (upscale_factor >= FP_0_36363) ? MALIDP_DOWNSCALING_2_75_COEFFS :
	       MALIDP_DOWNSCALING_4_COEFFS;
पूर्ण

#अघोषित FP_0_25000
#अघोषित FP_0_36363
#अघोषित FP_0_50000
#अघोषित FP_0_66667
#अघोषित FP_1_00000

अटल अंतरभूत व्योम malidp_se_set_enh_coeffs(काष्ठा malidp_hw_device *hwdev)
अणु
	अटल स्थिर s32 enhancer_coeffs[] = अणु
		-8, -8, -8, -8, 128, -8, -8, -8, -8
	पूर्ण;
	u32 val = MALIDP_SE_SET_ENH_LIMIT_LOW(MALIDP_SE_ENH_LOW_LEVEL) |
		  MALIDP_SE_SET_ENH_LIMIT_HIGH(MALIDP_SE_ENH_HIGH_LEVEL);
	u32 image_enh = hwdev->hw->map.se_base +
			((hwdev->hw->map.features & MALIDP_REGMAP_HAS_CLEARIRQ) ?
			 0x10 : 0xC) + MALIDP_SE_IMAGE_ENH;
	u32 enh_coeffs = image_enh + MALIDP_SE_ENH_COEFF0;
	पूर्णांक i;

	malidp_hw_ग_लिखो(hwdev, val, image_enh);
	क्रम (i = 0; i < ARRAY_SIZE(enhancer_coeffs); ++i)
		malidp_hw_ग_लिखो(hwdev, enhancer_coeffs[i], enh_coeffs + i * 4);
पूर्ण

/*
 * background color components are defined as 12bits values,
 * they will be shअगरted right when stored on hardware that
 * supports only 8bits per channel
 */
#घोषणा MALIDP_BGND_COLOR_R		0x000
#घोषणा MALIDP_BGND_COLOR_G		0x000
#घोषणा MALIDP_BGND_COLOR_B		0x000

#घोषणा MALIDP_COLORADJ_NUM_COEFFS	12
#घोषणा MALIDP_COEFFTAB_NUM_COEFFS	64

#घोषणा MALIDP_GAMMA_LUT_SIZE		4096

#घोषणा AFBC_SIZE_MASK		AFBC_FORMAT_MOD_BLOCK_SIZE_MASK
#घोषणा AFBC_SIZE_16X16		AFBC_FORMAT_MOD_BLOCK_SIZE_16x16
#घोषणा AFBC_YTR		AFBC_FORMAT_MOD_YTR
#घोषणा AFBC_SPARSE		AFBC_FORMAT_MOD_SPARSE
#घोषणा AFBC_CBR		AFBC_FORMAT_MOD_CBR
#घोषणा AFBC_SPLIT		AFBC_FORMAT_MOD_SPLIT
#घोषणा AFBC_TILED		AFBC_FORMAT_MOD_TILED
#घोषणा AFBC_SC			AFBC_FORMAT_MOD_SC

#घोषणा AFBC_MOD_VALID_BITS	(AFBC_SIZE_MASK | AFBC_YTR | AFBC_SPLIT | \
				 AFBC_SPARSE | AFBC_CBR | AFBC_TILED | AFBC_SC)

बाह्य स्थिर u64 malidp_क्रमmat_modअगरiers[];

#पूर्ण_अगर  /* __MALIDP_HW_H__ */
