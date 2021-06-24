<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (C) 2018 Linus Walleij <linus.walleij@linaro.org>
 * Parts of this file were based on the MCDE driver by Marcus Lorentzon
 * (C) ST-Ericsson SA 2013
 */
#समावेश <drm/drm_simple_kms_helper.h>

#अगर_अघोषित _MCDE_DRM_H_
#घोषणा _MCDE_DRM_H_

/* Shared basic रेजिस्टरs */
#घोषणा MCDE_CR 0x00000000
#घोषणा MCDE_CR_IFIFOEMPTYLINECOUNT_V422_SHIFT 0
#घोषणा MCDE_CR_IFIFOEMPTYLINECOUNT_V422_MASK 0x0000003F
#घोषणा MCDE_CR_IFIFOCTRLEN BIT(15)
#घोषणा MCDE_CR_UFRECOVERY_MODE_V422 BIT(16)
#घोषणा MCDE_CR_WRAP_MODE_V422_SHIFT BIT(17)
#घोषणा MCDE_CR_AUTOCLKG_EN BIT(30)
#घोषणा MCDE_CR_MCDEEN BIT(31)

#घोषणा MCDE_CONF0 0x00000004
#घोषणा MCDE_CONF0_SYNCMUX0 BIT(0)
#घोषणा MCDE_CONF0_SYNCMUX1 BIT(1)
#घोषणा MCDE_CONF0_SYNCMUX2 BIT(2)
#घोषणा MCDE_CONF0_SYNCMUX3 BIT(3)
#घोषणा MCDE_CONF0_SYNCMUX4 BIT(4)
#घोषणा MCDE_CONF0_SYNCMUX5 BIT(5)
#घोषणा MCDE_CONF0_SYNCMUX6 BIT(6)
#घोषणा MCDE_CONF0_SYNCMUX7 BIT(7)
#घोषणा MCDE_CONF0_IFIFOCTRLWTRMRKLVL_SHIFT 12
#घोषणा MCDE_CONF0_IFIFOCTRLWTRMRKLVL_MASK 0x00007000
#घोषणा MCDE_CONF0_OUTMUX0_SHIFT 16
#घोषणा MCDE_CONF0_OUTMUX0_MASK 0x00070000
#घोषणा MCDE_CONF0_OUTMUX1_SHIFT 19
#घोषणा MCDE_CONF0_OUTMUX1_MASK 0x00380000
#घोषणा MCDE_CONF0_OUTMUX2_SHIFT 22
#घोषणा MCDE_CONF0_OUTMUX2_MASK 0x01C00000
#घोषणा MCDE_CONF0_OUTMUX3_SHIFT 25
#घोषणा MCDE_CONF0_OUTMUX3_MASK 0x0E000000
#घोषणा MCDE_CONF0_OUTMUX4_SHIFT 28
#घोषणा MCDE_CONF0_OUTMUX4_MASK 0x70000000

#घोषणा MCDE_SSP 0x00000008
#घोषणा MCDE_AIS 0x00000100
#घोषणा MCDE_IMSCERR 0x00000110
#घोषणा MCDE_RISERR 0x00000120
#घोषणा MCDE_MISERR 0x00000130
#घोषणा MCDE_SISERR 0x00000140

क्रमागत mcde_flow_mode अणु
	/* One-shot mode: flow stops after one frame */
	MCDE_COMMAND_ONESHOT_FLOW,
	/* Command mode with tearing effect (TE) IRQ sync */
	MCDE_COMMAND_TE_FLOW,
	/*
	 * Command mode with bus turn-around (BTA) and tearing effect
	 * (TE) IRQ sync.
	 */
	MCDE_COMMAND_BTA_TE_FLOW,
	/* Video mode with tearing effect (TE) sync IRQ */
	MCDE_VIDEO_TE_FLOW,
	/* Video mode with the क्रमmatter itself as sync source */
	MCDE_VIDEO_FORMATTER_FLOW,
	/* DPI video with the क्रमmatter itsels as sync source */
	MCDE_DPI_FORMATTER_FLOW,
पूर्ण;

काष्ठा mcde अणु
	काष्ठा drm_device drm;
	काष्ठा device *dev;
	काष्ठा drm_panel *panel;
	काष्ठा drm_bridge *bridge;
	काष्ठा drm_connector *connector;
	काष्ठा drm_simple_display_pipe pipe;
	काष्ठा mipi_dsi_device *mdsi;
	bool dpi_output;
	s16 stride;
	क्रमागत mcde_flow_mode flow_mode;
	अचिन्हित पूर्णांक flow_active;
	spinlock_t flow_lock; /* Locks the channel flow control */

	व्योम __iomem *regs;

	काष्ठा clk *mcde_clk;
	काष्ठा clk *lcd_clk;
	काष्ठा clk *hdmi_clk;
	/* Handles to the घड़ी भागiders क्रम FIFO A and B */
	काष्ठा clk *fअगरoa_clk;
	काष्ठा clk *fअगरob_clk;
	/* Locks the MCDE FIFO control रेजिस्टर A and B */
	spinlock_t fअगरo_crx1_lock;

	काष्ठा regulator *epod;
	काष्ठा regulator *vana;
पूर्ण;

#घोषणा to_mcde(dev) container_of(dev, काष्ठा mcde, drm)

अटल अंतरभूत bool mcde_flow_is_video(काष्ठा mcde *mcde)
अणु
	वापस (mcde->flow_mode == MCDE_VIDEO_TE_FLOW ||
		mcde->flow_mode == MCDE_VIDEO_FORMATTER_FLOW);
पूर्ण

bool mcde_dsi_irq(काष्ठा mipi_dsi_device *mdsi);
व्योम mcde_dsi_te_request(काष्ठा mipi_dsi_device *mdsi);
व्योम mcde_dsi_enable(काष्ठा drm_bridge *bridge);
व्योम mcde_dsi_disable(काष्ठा drm_bridge *bridge);
बाह्य काष्ठा platक्रमm_driver mcde_dsi_driver;

व्योम mcde_display_irq(काष्ठा mcde *mcde);
व्योम mcde_display_disable_irqs(काष्ठा mcde *mcde);
पूर्णांक mcde_display_init(काष्ठा drm_device *drm);

पूर्णांक mcde_init_घड़ी_भागider(काष्ठा mcde *mcde);

#पूर्ण_अगर /* _MCDE_DRM_H_ */
