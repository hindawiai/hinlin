<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * rcar_du_drv.h  --  R-Car Display Unit DRM driver
 *
 * Copyright (C) 2013-2015 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#अगर_अघोषित __RCAR_DU_DRV_H__
#घोषणा __RCAR_DU_DRV_H__

#समावेश <linux/kernel.h>
#समावेश <linux/रुको.h>

#समावेश <drm/drm_device.h>

#समावेश "rcar_cmm.h"
#समावेश "rcar_du_crtc.h"
#समावेश "rcar_du_group.h"
#समावेश "rcar_du_vsp.h"

काष्ठा clk;
काष्ठा device;
काष्ठा drm_bridge;
काष्ठा drm_property;
काष्ठा rcar_du_device;

#घोषणा RCAR_DU_FEATURE_CRTC_IRQ_CLOCK	BIT(0)	/* Per-CRTC IRQ and घड़ी */
#घोषणा RCAR_DU_FEATURE_VSP1_SOURCE	BIT(1)	/* Has inमाला_दो from VSP1 */
#घोषणा RCAR_DU_FEATURE_INTERLACED	BIT(2)	/* HW supports पूर्णांकerlaced */
#घोषणा RCAR_DU_FEATURE_TVM_SYNC	BIT(3)	/* Has TV चयन/sync modes */

#घोषणा RCAR_DU_QUIRK_ALIGN_128B	BIT(0)	/* Align pitches to 128 bytes */

/*
 * काष्ठा rcar_du_output_routing - Output routing specअगरication
 * @possible_crtcs: biपंचांगask of possible CRTCs क्रम the output
 * @port: device tree port number corresponding to this output route
 *
 * The DU has 5 possible outमाला_दो (DPAD0/1, LVDS0/1, TCON). Output routing data
 * specअगरy the valid SoC outमाला_दो, which CRTCs can drive the output, and the type
 * of in-SoC encoder क्रम the output.
 */
काष्ठा rcar_du_output_routing अणु
	अचिन्हित पूर्णांक possible_crtcs;
	अचिन्हित पूर्णांक port;
पूर्ण;

/*
 * काष्ठा rcar_du_device_info - DU model-specअगरic inक्रमmation
 * @gen: device generation (2 or 3)
 * @features: device features (RCAR_DU_FEATURE_*)
 * @quirks: device quirks (RCAR_DU_QUIRK_*)
 * @channels_mask: bit mask of available DU channels
 * @routes: array of CRTC to output routes, indexed by output (RCAR_DU_OUTPUT_*)
 * @num_lvds: number of पूर्णांकernal LVDS encoders
 * @dpll_mask: bit mask of DU channels equipped with a DPLL
 * @lvds_clk_mask: biपंचांगask of channels that can use the LVDS घड़ी as करोt घड़ी
 */
काष्ठा rcar_du_device_info अणु
	अचिन्हित पूर्णांक gen;
	अचिन्हित पूर्णांक features;
	अचिन्हित पूर्णांक quirks;
	अचिन्हित पूर्णांक channels_mask;
	काष्ठा rcar_du_output_routing routes[RCAR_DU_OUTPUT_MAX];
	अचिन्हित पूर्णांक num_lvds;
	अचिन्हित पूर्णांक dpll_mask;
	अचिन्हित पूर्णांक lvds_clk_mask;
पूर्ण;

#घोषणा RCAR_DU_MAX_CRTCS		4
#घोषणा RCAR_DU_MAX_GROUPS		DIV_ROUND_UP(RCAR_DU_MAX_CRTCS, 2)
#घोषणा RCAR_DU_MAX_VSPS		4
#घोषणा RCAR_DU_MAX_LVDS		2

काष्ठा rcar_du_device अणु
	काष्ठा device *dev;
	स्थिर काष्ठा rcar_du_device_info *info;

	व्योम __iomem *mmio;

	काष्ठा drm_device ddev;

	काष्ठा rcar_du_crtc crtcs[RCAR_DU_MAX_CRTCS];
	अचिन्हित पूर्णांक num_crtcs;

	काष्ठा rcar_du_group groups[RCAR_DU_MAX_GROUPS];
	काष्ठा platक्रमm_device *cmms[RCAR_DU_MAX_CRTCS];
	काष्ठा rcar_du_vsp vsps[RCAR_DU_MAX_VSPS];
	काष्ठा drm_bridge *lvds[RCAR_DU_MAX_LVDS];

	काष्ठा अणु
		काष्ठा drm_property *colorkey;
	पूर्ण props;

	अचिन्हित पूर्णांक dpad0_source;
	अचिन्हित पूर्णांक dpad1_source;
	अचिन्हित पूर्णांक vspd1_sink;
पूर्ण;

अटल अंतरभूत काष्ठा rcar_du_device *to_rcar_du_device(काष्ठा drm_device *dev)
अणु
	वापस container_of(dev, काष्ठा rcar_du_device, ddev);
पूर्ण

अटल अंतरभूत bool rcar_du_has(काष्ठा rcar_du_device *rcdu,
			       अचिन्हित पूर्णांक feature)
अणु
	वापस rcdu->info->features & feature;
पूर्ण

अटल अंतरभूत bool rcar_du_needs(काष्ठा rcar_du_device *rcdu,
				 अचिन्हित पूर्णांक quirk)
अणु
	वापस rcdu->info->quirks & quirk;
पूर्ण

अटल अंतरभूत u32 rcar_du_पढ़ो(काष्ठा rcar_du_device *rcdu, u32 reg)
अणु
	वापस ioपढ़ो32(rcdu->mmio + reg);
पूर्ण

अटल अंतरभूत व्योम rcar_du_ग_लिखो(काष्ठा rcar_du_device *rcdu, u32 reg, u32 data)
अणु
	ioग_लिखो32(data, rcdu->mmio + reg);
पूर्ण

#पूर्ण_अगर /* __RCAR_DU_DRV_H__ */
