<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2014 Traphandler
 * Copyright (C) 2014 Free Electrons
 * Copyright (C) 2014 Aपंचांगel
 *
 * Author: Jean-Jacques Hiblot <jjhiblot@traphandler.com>
 * Author: Boris BREZILLON <boris.brezillon@मुक्त-electrons.com>
 */

#अगर_अघोषित DRM_ATMEL_HLCDC_H
#घोषणा DRM_ATMEL_HLCDC_H

#समावेश <linux/regmap.h>

#समावेश <drm/drm_plane.h>

#घोषणा ATMEL_HLCDC_LAYER_CHER			0x0
#घोषणा ATMEL_HLCDC_LAYER_CHDR			0x4
#घोषणा ATMEL_HLCDC_LAYER_CHSR			0x8
#घोषणा ATMEL_HLCDC_LAYER_EN			BIT(0)
#घोषणा ATMEL_HLCDC_LAYER_UPDATE		BIT(1)
#घोषणा ATMEL_HLCDC_LAYER_A2Q			BIT(2)
#घोषणा ATMEL_HLCDC_LAYER_RST			BIT(8)

#घोषणा ATMEL_HLCDC_LAYER_IER			0xc
#घोषणा ATMEL_HLCDC_LAYER_IDR			0x10
#घोषणा ATMEL_HLCDC_LAYER_IMR			0x14
#घोषणा ATMEL_HLCDC_LAYER_ISR			0x18
#घोषणा ATMEL_HLCDC_LAYER_DFETCH		BIT(0)
#घोषणा ATMEL_HLCDC_LAYER_LFETCH		BIT(1)
#घोषणा ATMEL_HLCDC_LAYER_DMA_IRQ(p)		BIT(2 + (8 * (p)))
#घोषणा ATMEL_HLCDC_LAYER_DSCR_IRQ(p)		BIT(3 + (8 * (p)))
#घोषणा ATMEL_HLCDC_LAYER_ADD_IRQ(p)		BIT(4 + (8 * (p)))
#घोषणा ATMEL_HLCDC_LAYER_DONE_IRQ(p)		BIT(5 + (8 * (p)))
#घोषणा ATMEL_HLCDC_LAYER_OVR_IRQ(p)		BIT(6 + (8 * (p)))

#घोषणा ATMEL_HLCDC_LAYER_PLANE_HEAD(p)		(((p) * 0x10) + 0x1c)
#घोषणा ATMEL_HLCDC_LAYER_PLANE_ADDR(p)		(((p) * 0x10) + 0x20)
#घोषणा ATMEL_HLCDC_LAYER_PLANE_CTRL(p)		(((p) * 0x10) + 0x24)
#घोषणा ATMEL_HLCDC_LAYER_PLANE_NEXT(p)		(((p) * 0x10) + 0x28)

#घोषणा ATMEL_HLCDC_LAYER_DMA_CFG		0
#घोषणा ATMEL_HLCDC_LAYER_DMA_SIF		BIT(0)
#घोषणा ATMEL_HLCDC_LAYER_DMA_BLEN_MASK		GENMASK(5, 4)
#घोषणा ATMEL_HLCDC_LAYER_DMA_BLEN_SINGLE	(0 << 4)
#घोषणा ATMEL_HLCDC_LAYER_DMA_BLEN_INCR4	(1 << 4)
#घोषणा ATMEL_HLCDC_LAYER_DMA_BLEN_INCR8	(2 << 4)
#घोषणा ATMEL_HLCDC_LAYER_DMA_BLEN_INCR16	(3 << 4)
#घोषणा ATMEL_HLCDC_LAYER_DMA_DLBO		BIT(8)
#घोषणा ATMEL_HLCDC_LAYER_DMA_ROTDIS		BIT(12)
#घोषणा ATMEL_HLCDC_LAYER_DMA_LOCKDIS		BIT(13)

#घोषणा ATMEL_HLCDC_LAYER_FORMAT_CFG		1
#घोषणा ATMEL_HLCDC_LAYER_RGB			(0 << 0)
#घोषणा ATMEL_HLCDC_LAYER_CLUT			(1 << 0)
#घोषणा ATMEL_HLCDC_LAYER_YUV			(2 << 0)
#घोषणा ATMEL_HLCDC_RGB_MODE(m)			\
	(ATMEL_HLCDC_LAYER_RGB | (((m) & 0xf) << 4))
#घोषणा ATMEL_HLCDC_CLUT_MODE(m)		\
	(ATMEL_HLCDC_LAYER_CLUT | (((m) & 0x3) << 8))
#घोषणा ATMEL_HLCDC_YUV_MODE(m)			\
	(ATMEL_HLCDC_LAYER_YUV | (((m) & 0xf) << 12))
#घोषणा ATMEL_HLCDC_YUV422ROT			BIT(16)
#घोषणा ATMEL_HLCDC_YUV422SWP			BIT(17)
#घोषणा ATMEL_HLCDC_DSCALEOPT			BIT(20)

#घोषणा ATMEL_HLCDC_C1_MODE			ATMEL_HLCDC_CLUT_MODE(0)
#घोषणा ATMEL_HLCDC_C2_MODE			ATMEL_HLCDC_CLUT_MODE(1)
#घोषणा ATMEL_HLCDC_C4_MODE			ATMEL_HLCDC_CLUT_MODE(2)
#घोषणा ATMEL_HLCDC_C8_MODE			ATMEL_HLCDC_CLUT_MODE(3)

#घोषणा ATMEL_HLCDC_XRGB4444_MODE		ATMEL_HLCDC_RGB_MODE(0)
#घोषणा ATMEL_HLCDC_ARGB4444_MODE		ATMEL_HLCDC_RGB_MODE(1)
#घोषणा ATMEL_HLCDC_RGBA4444_MODE		ATMEL_HLCDC_RGB_MODE(2)
#घोषणा ATMEL_HLCDC_RGB565_MODE			ATMEL_HLCDC_RGB_MODE(3)
#घोषणा ATMEL_HLCDC_ARGB1555_MODE		ATMEL_HLCDC_RGB_MODE(4)
#घोषणा ATMEL_HLCDC_XRGB8888_MODE		ATMEL_HLCDC_RGB_MODE(9)
#घोषणा ATMEL_HLCDC_RGB888_MODE			ATMEL_HLCDC_RGB_MODE(10)
#घोषणा ATMEL_HLCDC_ARGB8888_MODE		ATMEL_HLCDC_RGB_MODE(12)
#घोषणा ATMEL_HLCDC_RGBA8888_MODE		ATMEL_HLCDC_RGB_MODE(13)

#घोषणा ATMEL_HLCDC_AYUV_MODE			ATMEL_HLCDC_YUV_MODE(0)
#घोषणा ATMEL_HLCDC_YUYV_MODE			ATMEL_HLCDC_YUV_MODE(1)
#घोषणा ATMEL_HLCDC_UYVY_MODE			ATMEL_HLCDC_YUV_MODE(2)
#घोषणा ATMEL_HLCDC_YVYU_MODE			ATMEL_HLCDC_YUV_MODE(3)
#घोषणा ATMEL_HLCDC_VYUY_MODE			ATMEL_HLCDC_YUV_MODE(4)
#घोषणा ATMEL_HLCDC_NV61_MODE			ATMEL_HLCDC_YUV_MODE(5)
#घोषणा ATMEL_HLCDC_YUV422_MODE			ATMEL_HLCDC_YUV_MODE(6)
#घोषणा ATMEL_HLCDC_NV21_MODE			ATMEL_HLCDC_YUV_MODE(7)
#घोषणा ATMEL_HLCDC_YUV420_MODE			ATMEL_HLCDC_YUV_MODE(8)

#घोषणा ATMEL_HLCDC_LAYER_POS(x, y)		((x) | ((y) << 16))
#घोषणा ATMEL_HLCDC_LAYER_SIZE(w, h)		(((w) - 1) | (((h) - 1) << 16))

#घोषणा ATMEL_HLCDC_LAYER_CRKEY			BIT(0)
#घोषणा ATMEL_HLCDC_LAYER_INV			BIT(1)
#घोषणा ATMEL_HLCDC_LAYER_ITER2BL		BIT(2)
#घोषणा ATMEL_HLCDC_LAYER_ITER			BIT(3)
#घोषणा ATMEL_HLCDC_LAYER_REVALPHA		BIT(4)
#घोषणा ATMEL_HLCDC_LAYER_GAEN			BIT(5)
#घोषणा ATMEL_HLCDC_LAYER_LAEN			BIT(6)
#घोषणा ATMEL_HLCDC_LAYER_OVR			BIT(7)
#घोषणा ATMEL_HLCDC_LAYER_DMA			BIT(8)
#घोषणा ATMEL_HLCDC_LAYER_REP			BIT(9)
#घोषणा ATMEL_HLCDC_LAYER_DSTKEY		BIT(10)
#घोषणा ATMEL_HLCDC_LAYER_DISCEN		BIT(11)
#घोषणा ATMEL_HLCDC_LAYER_GA_SHIFT		16
#घोषणा ATMEL_HLCDC_LAYER_GA_MASK		\
	GENMASK(23, ATMEL_HLCDC_LAYER_GA_SHIFT)
#घोषणा ATMEL_HLCDC_LAYER_GA(x)			\
	((x) << ATMEL_HLCDC_LAYER_GA_SHIFT)

#घोषणा ATMEL_HLCDC_LAYER_DISC_POS(x, y)	((x) | ((y) << 16))
#घोषणा ATMEL_HLCDC_LAYER_DISC_SIZE(w, h)	(((w) - 1) | (((h) - 1) << 16))

#घोषणा ATMEL_HLCDC_LAYER_SCALER_FACTORS(x, y)	((x) | ((y) << 16))
#घोषणा ATMEL_HLCDC_LAYER_SCALER_ENABLE		BIT(31)

#घोषणा ATMEL_HLCDC_LAYER_MAX_PLANES		3

#घोषणा ATMEL_HLCDC_DMA_CHANNEL_DSCR_RESERVED	BIT(0)
#घोषणा ATMEL_HLCDC_DMA_CHANNEL_DSCR_LOADED	BIT(1)
#घोषणा ATMEL_HLCDC_DMA_CHANNEL_DSCR_DONE	BIT(2)
#घोषणा ATMEL_HLCDC_DMA_CHANNEL_DSCR_OVERRUN	BIT(3)

#घोषणा ATMEL_HLCDC_CLUT_SIZE			256

#घोषणा ATMEL_HLCDC_MAX_LAYERS			6

/**
 * Aपंचांगel HLCDC Layer रेजिस्टरs layout काष्ठाure
 *
 * Each HLCDC layer has its own रेजिस्टर organization and a given रेजिस्टर
 * can be placed dअगरferently on 2 dअगरferent layers depending on its
 * capabilities.
 * This काष्ठाure stores common रेजिस्टरs layout क्रम a given layer and is
 * used by HLCDC layer code to choose the appropriate रेजिस्टर to ग_लिखो to
 * or to पढ़ो from.
 *
 * For all fields, a value of zero means "unsupported".
 *
 * See Aपंचांगel's datasheet क्रम a detailled description of these रेजिस्टरs.
 *
 * @xstride: xstride रेजिस्टरs
 * @pstride: pstride रेजिस्टरs
 * @pos: position रेजिस्टर
 * @size: displayed size रेजिस्टर
 * @memsize: memory size रेजिस्टर
 * @शेष_color: शेष color रेजिस्टर
 * @chroma_key: chroma key रेजिस्टर
 * @chroma_key_mask: chroma key mask रेजिस्टर
 * @general_config: general layer config रेजिस्टर
 * @sacler_config: scaler factors रेजिस्टर
 * @phicoeffs: X/Y PHI coefficient रेजिस्टरs
 * @disc_pos: discard area position रेजिस्टर
 * @disc_size: discard area size रेजिस्टर
 * @csc: color space conversion रेजिस्टर
 */
काष्ठा aपंचांगel_hlcdc_layer_cfg_layout अणु
	पूर्णांक xstride[ATMEL_HLCDC_LAYER_MAX_PLANES];
	पूर्णांक pstride[ATMEL_HLCDC_LAYER_MAX_PLANES];
	पूर्णांक pos;
	पूर्णांक size;
	पूर्णांक memsize;
	पूर्णांक शेष_color;
	पूर्णांक chroma_key;
	पूर्णांक chroma_key_mask;
	पूर्णांक general_config;
	पूर्णांक scaler_config;
	काष्ठा अणु
		पूर्णांक x;
		पूर्णांक y;
	पूर्ण phicoeffs;
	पूर्णांक disc_pos;
	पूर्णांक disc_size;
	पूर्णांक csc;
पूर्ण;

/**
 * Aपंचांगel HLCDC DMA descriptor काष्ठाure
 *
 * This काष्ठाure is used by the HLCDC DMA engine to schedule a DMA transfer.
 *
 * The काष्ठाure fields must reमुख्य in this specअगरic order, because they're
 * used by the HLCDC DMA engine, which expect them in this order.
 * HLCDC DMA descriptors must be aligned on 64 bits.
 *
 * @addr: buffer DMA address
 * @ctrl: DMA transfer options
 * @next: next DMA descriptor to fetch
 * @self: descriptor DMA address
 */
काष्ठा aपंचांगel_hlcdc_dma_channel_dscr अणु
	dma_addr_t addr;
	u32 ctrl;
	dma_addr_t next;
	dma_addr_t self;
पूर्ण __aligned(माप(u64));

/**
 * Aपंचांगel HLCDC layer types
 */
क्रमागत aपंचांगel_hlcdc_layer_type अणु
	ATMEL_HLCDC_NO_LAYER,
	ATMEL_HLCDC_BASE_LAYER,
	ATMEL_HLCDC_OVERLAY_LAYER,
	ATMEL_HLCDC_CURSOR_LAYER,
	ATMEL_HLCDC_PP_LAYER,
पूर्ण;

/**
 * Aपंचांगel HLCDC Supported क्रमmats काष्ठाure
 *
 * This काष्ठाure list all the क्रमmats supported by a given layer.
 *
 * @nक्रमmats: number of supported क्रमmats
 * @क्रमmats: supported क्रमmats
 */
काष्ठा aपंचांगel_hlcdc_क्रमmats अणु
	पूर्णांक nक्रमmats;
	u32 *क्रमmats;
पूर्ण;

/**
 * Aपंचांगel HLCDC Layer description काष्ठाure
 *
 * This काष्ठाure describes the capabilities provided by a given layer.
 *
 * @name: layer name
 * @type: layer type
 * @id: layer id
 * @regs_offset: offset of the layer रेजिस्टरs from the HLCDC रेजिस्टरs base
 * @cfgs_offset: CFGX रेजिस्टरs offset from the layer रेजिस्टरs base
 * @क्रमmats: supported क्रमmats
 * @layout: config रेजिस्टरs layout
 * @max_width: maximum width supported by this layer (0 means unlimited)
 * @max_height: maximum height supported by this layer (0 means unlimited)
 */
काष्ठा aपंचांगel_hlcdc_layer_desc अणु
	स्थिर अक्षर *name;
	क्रमागत aपंचांगel_hlcdc_layer_type type;
	पूर्णांक id;
	पूर्णांक regs_offset;
	पूर्णांक cfgs_offset;
	पूर्णांक clut_offset;
	काष्ठा aपंचांगel_hlcdc_क्रमmats *क्रमmats;
	काष्ठा aपंचांगel_hlcdc_layer_cfg_layout layout;
	पूर्णांक max_width;
	पूर्णांक max_height;
पूर्ण;

/**
 * Aपंचांगel HLCDC Layer.
 *
 * A layer can be a DRM plane of a post processing layer used to render
 * HLCDC composition पूर्णांकo memory.
 *
 * @desc: layer description
 * @regmap: poपूर्णांकer to the HLCDC regmap
 */
काष्ठा aपंचांगel_hlcdc_layer अणु
	स्थिर काष्ठा aपंचांगel_hlcdc_layer_desc *desc;
	काष्ठा regmap *regmap;
पूर्ण;

/**
 * Aपंचांगel HLCDC Plane.
 *
 * @base: base DRM plane काष्ठाure
 * @layer: HLCDC layer काष्ठाure
 * @properties: poपूर्णांकer to the property definitions काष्ठाure
 */
काष्ठा aपंचांगel_hlcdc_plane अणु
	काष्ठा drm_plane base;
	काष्ठा aपंचांगel_hlcdc_layer layer;
पूर्ण;

अटल अंतरभूत काष्ठा aपंचांगel_hlcdc_plane *
drm_plane_to_aपंचांगel_hlcdc_plane(काष्ठा drm_plane *p)
अणु
	वापस container_of(p, काष्ठा aपंचांगel_hlcdc_plane, base);
पूर्ण

अटल अंतरभूत काष्ठा aपंचांगel_hlcdc_plane *
aपंचांगel_hlcdc_layer_to_plane(काष्ठा aपंचांगel_hlcdc_layer *layer)
अणु
	वापस container_of(layer, काष्ठा aपंचांगel_hlcdc_plane, layer);
पूर्ण

/**
 * Aपंचांगel HLCDC Display Controller description काष्ठाure.
 *
 * This काष्ठाure describes the HLCDC IP capabilities and depends on the
 * HLCDC IP version (or Aपंचांगel SoC family).
 *
 * @min_width: minimum width supported by the Display Controller
 * @min_height: minimum height supported by the Display Controller
 * @max_width: maximum width supported by the Display Controller
 * @max_height: maximum height supported by the Display Controller
 * @max_spw: maximum vertical/horizontal pulse width
 * @max_vpw: maximum vertical back/front porch width
 * @max_hpw: maximum horizontal back/front porch width
 * @conflicting_output_क्रमmats: true अगर RGBXXX output क्रमmats conflict with
 *				each other.
 * @fixed_clksrc: true अगर घड़ी source is fixed
 * @layers: a layer description table describing available layers
 * @nlayers: layer description table size
 */
काष्ठा aपंचांगel_hlcdc_dc_desc अणु
	पूर्णांक min_width;
	पूर्णांक min_height;
	पूर्णांक max_width;
	पूर्णांक max_height;
	पूर्णांक max_spw;
	पूर्णांक max_vpw;
	पूर्णांक max_hpw;
	bool conflicting_output_क्रमmats;
	bool fixed_clksrc;
	स्थिर काष्ठा aपंचांगel_hlcdc_layer_desc *layers;
	पूर्णांक nlayers;
पूर्ण;

/**
 * Aपंचांगel HLCDC Display Controller.
 *
 * @desc: HLCDC Display Controller description
 * @dscrpool: DMA coherent pool used to allocate DMA descriptors
 * @hlcdc: poपूर्णांकer to the aपंचांगel_hlcdc काष्ठाure provided by the MFD device
 * @fbdev: framebuffer device attached to the Display Controller
 * @crtc: CRTC provided by the display controller
 * @planes: instantiated planes
 * @layers: active HLCDC layers
 * @suspend: used to store the HLCDC state when entering suspend
 */
काष्ठा aपंचांगel_hlcdc_dc अणु
	स्थिर काष्ठा aपंचांगel_hlcdc_dc_desc *desc;
	काष्ठा dma_pool *dscrpool;
	काष्ठा aपंचांगel_hlcdc *hlcdc;
	काष्ठा drm_crtc *crtc;
	काष्ठा aपंचांगel_hlcdc_layer *layers[ATMEL_HLCDC_MAX_LAYERS];
	काष्ठा अणु
		u32 imr;
		काष्ठा drm_atomic_state *state;
	पूर्ण suspend;
पूर्ण;

बाह्य काष्ठा aपंचांगel_hlcdc_क्रमmats aपंचांगel_hlcdc_plane_rgb_क्रमmats;
बाह्य काष्ठा aपंचांगel_hlcdc_क्रमmats aपंचांगel_hlcdc_plane_rgb_and_yuv_क्रमmats;

अटल अंतरभूत व्योम aपंचांगel_hlcdc_layer_ग_लिखो_reg(काष्ठा aपंचांगel_hlcdc_layer *layer,
					       अचिन्हित पूर्णांक reg, u32 val)
अणु
	regmap_ग_लिखो(layer->regmap, layer->desc->regs_offset + reg, val);
पूर्ण

अटल अंतरभूत u32 aपंचांगel_hlcdc_layer_पढ़ो_reg(काष्ठा aपंचांगel_hlcdc_layer *layer,
					     अचिन्हित पूर्णांक reg)
अणु
	u32 val;

	regmap_पढ़ो(layer->regmap, layer->desc->regs_offset + reg, &val);

	वापस val;
पूर्ण

अटल अंतरभूत व्योम aपंचांगel_hlcdc_layer_ग_लिखो_cfg(काष्ठा aपंचांगel_hlcdc_layer *layer,
					       अचिन्हित पूर्णांक cfgid, u32 val)
अणु
	aपंचांगel_hlcdc_layer_ग_लिखो_reg(layer,
				    layer->desc->cfgs_offset +
				    (cfgid * माप(u32)), val);
पूर्ण

अटल अंतरभूत u32 aपंचांगel_hlcdc_layer_पढ़ो_cfg(काष्ठा aपंचांगel_hlcdc_layer *layer,
					     अचिन्हित पूर्णांक cfgid)
अणु
	वापस aपंचांगel_hlcdc_layer_पढ़ो_reg(layer,
					  layer->desc->cfgs_offset +
					  (cfgid * माप(u32)));
पूर्ण

अटल अंतरभूत व्योम aपंचांगel_hlcdc_layer_ग_लिखो_clut(काष्ठा aपंचांगel_hlcdc_layer *layer,
						अचिन्हित पूर्णांक c, u32 val)
अणु
	regmap_ग_लिखो(layer->regmap,
		     layer->desc->clut_offset + c * माप(u32),
		     val);
पूर्ण

अटल अंतरभूत व्योम aपंचांगel_hlcdc_layer_init(काष्ठा aपंचांगel_hlcdc_layer *layer,
				स्थिर काष्ठा aपंचांगel_hlcdc_layer_desc *desc,
				काष्ठा regmap *regmap)
अणु
	layer->desc = desc;
	layer->regmap = regmap;
पूर्ण

क्रमागत drm_mode_status
aपंचांगel_hlcdc_dc_mode_valid(काष्ठा aपंचांगel_hlcdc_dc *dc,
			  स्थिर काष्ठा drm_display_mode *mode);

पूर्णांक aपंचांगel_hlcdc_create_planes(काष्ठा drm_device *dev);
व्योम aपंचांगel_hlcdc_plane_irq(काष्ठा aपंचांगel_hlcdc_plane *plane);

पूर्णांक aपंचांगel_hlcdc_plane_prepare_disc_area(काष्ठा drm_crtc_state *c_state);
पूर्णांक aपंचांगel_hlcdc_plane_prepare_ahb_routing(काष्ठा drm_crtc_state *c_state);

व्योम aपंचांगel_hlcdc_crtc_irq(काष्ठा drm_crtc *c);

पूर्णांक aपंचांगel_hlcdc_crtc_create(काष्ठा drm_device *dev);

पूर्णांक aपंचांगel_hlcdc_create_outमाला_दो(काष्ठा drm_device *dev);
पूर्णांक aपंचांगel_hlcdc_encoder_get_bus_fmt(काष्ठा drm_encoder *encoder);

#पूर्ण_अगर /* DRM_ATMEL_HLCDC_H */
