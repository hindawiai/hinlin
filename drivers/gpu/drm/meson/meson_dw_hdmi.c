<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 * Copyright (C) 2015 Amlogic, Inc. All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/reset.h>

#समावेश <drm/bridge/dw_hdmi.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश <linux/media-bus-क्रमmat.h>
#समावेश <linux/videodev2.h>

#समावेश "meson_drv.h"
#समावेश "meson_dw_hdmi.h"
#समावेश "meson_registers.h"
#समावेश "meson_vclk.h"
#समावेश "meson_venc.h"

#घोषणा DRIVER_NAME "meson-dw-hdmi"
#घोषणा DRIVER_DESC "Amlogic Meson HDMI-TX DRM driver"

/**
 * DOC: HDMI Output
 *
 * HDMI Output is composed of :
 *
 * - A Synopsys DesignWare HDMI Controller IP
 * - A TOP control block controlling the Clocks and PHY
 * - A custom HDMI PHY in order convert video to TMDS संकेत
 *
 * .. code::
 *
 *    ___________________________________
 *   |            HDMI TOP               |<= HPD
 *   |___________________________________|
 *   |                  |                |
 *   |  Synopsys HDMI   |   HDMI PHY     |=> TMDS
 *   |    Controller    |________________|
 *   |___________________________________|<=> DDC
 *
 *
 * The HDMI TOP block only supports HPD sensing.
 * The Synopsys HDMI Controller पूर्णांकerrupt is routed
 * through the TOP Block पूर्णांकerrupt.
 * Communication to the TOP Block and the Synopsys
 * HDMI Controller is करोne a pair of addr+पढ़ो/ग_लिखो
 * रेजिस्टरs.
 * The HDMI PHY is configured by रेजिस्टरs in the
 * HHI रेजिस्टर block.
 *
 * Pixel data arrives in 4:4:4 क्रमmat from the VENC
 * block and the VPU HDMI mux selects either the ENCI
 * encoder क्रम the 576i or 480i क्रमmats or the ENCP
 * encoder क्रम all the other क्रमmats including
 * पूर्णांकerlaced HD क्रमmats.
 * The VENC uses a DVI encoder on top of the ENCI
 * or ENCP encoders to generate DVI timings क्रम the
 * HDMI controller.
 *
 * GXBB, GXL and GXM embeds the Synopsys DesignWare
 * HDMI TX IP version 2.01a with HDCP and I2C & S/PDIF
 * audio source पूर्णांकerfaces.
 *
 * We handle the following features :
 *
 * - HPD Rise & Fall पूर्णांकerrupt
 * - HDMI Controller Interrupt
 * - HDMI PHY Init क्रम 480i to 1080p60
 * - VENC & HDMI Clock setup क्रम 480i to 1080p60
 * - VENC Mode setup क्रम 480i to 1080p60
 *
 * What is missing :
 *
 * - PHY, Clock and Mode setup क्रम 2k && 4k modes
 * - SDDC Scrambling mode क्रम HDMI 2.0a
 * - HDCP Setup
 * - CEC Management
 */

/* TOP Block Communication Channel */
#घोषणा HDMITX_TOP_ADDR_REG	0x0
#घोषणा HDMITX_TOP_DATA_REG	0x4
#घोषणा HDMITX_TOP_CTRL_REG	0x8
#घोषणा HDMITX_TOP_G12A_OFFSET	0x8000

/* Controller Communication Channel */
#घोषणा HDMITX_DWC_ADDR_REG	0x10
#घोषणा HDMITX_DWC_DATA_REG	0x14
#घोषणा HDMITX_DWC_CTRL_REG	0x18

/* HHI Registers */
#घोषणा HHI_MEM_PD_REG0		0x100 /* 0x40 */
#घोषणा HHI_HDMI_CLK_CNTL	0x1cc /* 0x73 */
#घोषणा HHI_HDMI_PHY_CNTL0	0x3a0 /* 0xe8 */
#घोषणा HHI_HDMI_PHY_CNTL1	0x3a4 /* 0xe9 */
#घोषणा HHI_HDMI_PHY_CNTL2	0x3a8 /* 0xea */
#घोषणा HHI_HDMI_PHY_CNTL3	0x3ac /* 0xeb */
#घोषणा HHI_HDMI_PHY_CNTL4	0x3b0 /* 0xec */
#घोषणा HHI_HDMI_PHY_CNTL5	0x3b4 /* 0xed */

अटल DEFINE_SPINLOCK(reg_lock);

क्रमागत meson_venc_source अणु
	MESON_VENC_SOURCE_NONE = 0,
	MESON_VENC_SOURCE_ENCI = 1,
	MESON_VENC_SOURCE_ENCP = 2,
पूर्ण;

काष्ठा meson_dw_hdmi;

काष्ठा meson_dw_hdmi_data अणु
	अचिन्हित पूर्णांक	(*top_पढ़ो)(काष्ठा meson_dw_hdmi *dw_hdmi,
				    अचिन्हित पूर्णांक addr);
	व्योम		(*top_ग_लिखो)(काष्ठा meson_dw_hdmi *dw_hdmi,
				     अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक data);
	अचिन्हित पूर्णांक	(*dwc_पढ़ो)(काष्ठा meson_dw_hdmi *dw_hdmi,
				    अचिन्हित पूर्णांक addr);
	व्योम		(*dwc_ग_लिखो)(काष्ठा meson_dw_hdmi *dw_hdmi,
				     अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक data);
पूर्ण;

काष्ठा meson_dw_hdmi अणु
	काष्ठा drm_encoder encoder;
	काष्ठा drm_bridge bridge;
	काष्ठा dw_hdmi_plat_data dw_plat_data;
	काष्ठा meson_drm *priv;
	काष्ठा device *dev;
	व्योम __iomem *hdmitx;
	स्थिर काष्ठा meson_dw_hdmi_data *data;
	काष्ठा reset_control *hdmitx_apb;
	काष्ठा reset_control *hdmitx_ctrl;
	काष्ठा reset_control *hdmitx_phy;
	काष्ठा regulator *hdmi_supply;
	u32 irq_stat;
	काष्ठा dw_hdmi *hdmi;
	अचिन्हित दीर्घ output_bus_fmt;
पूर्ण;
#घोषणा encoder_to_meson_dw_hdmi(x) \
	container_of(x, काष्ठा meson_dw_hdmi, encoder)
#घोषणा bridge_to_meson_dw_hdmi(x) \
	container_of(x, काष्ठा meson_dw_hdmi, bridge)

अटल अंतरभूत पूर्णांक dw_hdmi_is_compatible(काष्ठा meson_dw_hdmi *dw_hdmi,
					स्थिर अक्षर *compat)
अणु
	वापस of_device_is_compatible(dw_hdmi->dev->of_node, compat);
पूर्ण

/* PHY (via TOP bridge) and Controller dedicated रेजिस्टर पूर्णांकerface */

अटल अचिन्हित पूर्णांक dw_hdmi_top_पढ़ो(काष्ठा meson_dw_hdmi *dw_hdmi,
				     अचिन्हित पूर्णांक addr)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक data;

	spin_lock_irqsave(&reg_lock, flags);

	/* ADDR must be written twice */
	ग_लिखोl(addr & 0xffff, dw_hdmi->hdmitx + HDMITX_TOP_ADDR_REG);
	ग_लिखोl(addr & 0xffff, dw_hdmi->hdmitx + HDMITX_TOP_ADDR_REG);

	/* Read needs a second DATA पढ़ो */
	data = पढ़ोl(dw_hdmi->hdmitx + HDMITX_TOP_DATA_REG);
	data = पढ़ोl(dw_hdmi->hdmitx + HDMITX_TOP_DATA_REG);

	spin_unlock_irqrestore(&reg_lock, flags);

	वापस data;
पूर्ण

अटल अचिन्हित पूर्णांक dw_hdmi_g12a_top_पढ़ो(काष्ठा meson_dw_hdmi *dw_hdmi,
					  अचिन्हित पूर्णांक addr)
अणु
	वापस पढ़ोl(dw_hdmi->hdmitx + HDMITX_TOP_G12A_OFFSET + (addr << 2));
पूर्ण

अटल अंतरभूत व्योम dw_hdmi_top_ग_लिखो(काष्ठा meson_dw_hdmi *dw_hdmi,
				     अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक data)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&reg_lock, flags);

	/* ADDR must be written twice */
	ग_लिखोl(addr & 0xffff, dw_hdmi->hdmitx + HDMITX_TOP_ADDR_REG);
	ग_लिखोl(addr & 0xffff, dw_hdmi->hdmitx + HDMITX_TOP_ADDR_REG);

	/* Write needs single DATA ग_लिखो */
	ग_लिखोl(data, dw_hdmi->hdmitx + HDMITX_TOP_DATA_REG);

	spin_unlock_irqrestore(&reg_lock, flags);
पूर्ण

अटल अंतरभूत व्योम dw_hdmi_g12a_top_ग_लिखो(काष्ठा meson_dw_hdmi *dw_hdmi,
					  अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक data)
अणु
	ग_लिखोl(data, dw_hdmi->hdmitx + HDMITX_TOP_G12A_OFFSET + (addr << 2));
पूर्ण

/* Helper to change specअगरic bits in PHY रेजिस्टरs */
अटल अंतरभूत व्योम dw_hdmi_top_ग_लिखो_bits(काष्ठा meson_dw_hdmi *dw_hdmi,
					  अचिन्हित पूर्णांक addr,
					  अचिन्हित पूर्णांक mask,
					  अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक data = dw_hdmi->data->top_पढ़ो(dw_hdmi, addr);

	data &= ~mask;
	data |= val;

	dw_hdmi->data->top_ग_लिखो(dw_hdmi, addr, data);
पूर्ण

अटल अचिन्हित पूर्णांक dw_hdmi_dwc_पढ़ो(काष्ठा meson_dw_hdmi *dw_hdmi,
				     अचिन्हित पूर्णांक addr)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक data;

	spin_lock_irqsave(&reg_lock, flags);

	/* ADDR must be written twice */
	ग_लिखोl(addr & 0xffff, dw_hdmi->hdmitx + HDMITX_DWC_ADDR_REG);
	ग_लिखोl(addr & 0xffff, dw_hdmi->hdmitx + HDMITX_DWC_ADDR_REG);

	/* Read needs a second DATA पढ़ो */
	data = पढ़ोl(dw_hdmi->hdmitx + HDMITX_DWC_DATA_REG);
	data = पढ़ोl(dw_hdmi->hdmitx + HDMITX_DWC_DATA_REG);

	spin_unlock_irqrestore(&reg_lock, flags);

	वापस data;
पूर्ण

अटल अचिन्हित पूर्णांक dw_hdmi_g12a_dwc_पढ़ो(काष्ठा meson_dw_hdmi *dw_hdmi,
					  अचिन्हित पूर्णांक addr)
अणु
	वापस पढ़ोb(dw_hdmi->hdmitx + addr);
पूर्ण

अटल अंतरभूत व्योम dw_hdmi_dwc_ग_लिखो(काष्ठा meson_dw_hdmi *dw_hdmi,
				     अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक data)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&reg_lock, flags);

	/* ADDR must be written twice */
	ग_लिखोl(addr & 0xffff, dw_hdmi->hdmitx + HDMITX_DWC_ADDR_REG);
	ग_लिखोl(addr & 0xffff, dw_hdmi->hdmitx + HDMITX_DWC_ADDR_REG);

	/* Write needs single DATA ग_लिखो */
	ग_लिखोl(data, dw_hdmi->hdmitx + HDMITX_DWC_DATA_REG);

	spin_unlock_irqrestore(&reg_lock, flags);
पूर्ण

अटल अंतरभूत व्योम dw_hdmi_g12a_dwc_ग_लिखो(काष्ठा meson_dw_hdmi *dw_hdmi,
					  अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक data)
अणु
	ग_लिखोb(data, dw_hdmi->hdmitx + addr);
पूर्ण

/* Helper to change specअगरic bits in controller रेजिस्टरs */
अटल अंतरभूत व्योम dw_hdmi_dwc_ग_लिखो_bits(काष्ठा meson_dw_hdmi *dw_hdmi,
					  अचिन्हित पूर्णांक addr,
					  अचिन्हित पूर्णांक mask,
					  अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक data = dw_hdmi->data->dwc_पढ़ो(dw_hdmi, addr);

	data &= ~mask;
	data |= val;

	dw_hdmi->data->dwc_ग_लिखो(dw_hdmi, addr, data);
पूर्ण

/* Bridge */

/* Setup PHY bandwidth modes */
अटल व्योम meson_hdmi_phy_setup_mode(काष्ठा meson_dw_hdmi *dw_hdmi,
				      स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा meson_drm *priv = dw_hdmi->priv;
	अचिन्हित पूर्णांक pixel_घड़ी = mode->घड़ी;

	/* For 420, pixel घड़ी is half unlike venc घड़ी */
	अगर (dw_hdmi->output_bus_fmt == MEDIA_BUS_FMT_UYYVYY8_0_5X24)
		pixel_घड़ी /= 2;

	अगर (dw_hdmi_is_compatible(dw_hdmi, "amlogic,meson-gxl-dw-hdmi") ||
	    dw_hdmi_is_compatible(dw_hdmi, "amlogic,meson-gxm-dw-hdmi")) अणु
		अगर (pixel_घड़ी >= 371250) अणु
			/* 5.94Gbps, 3.7125Gbps */
			regmap_ग_लिखो(priv->hhi, HHI_HDMI_PHY_CNTL0, 0x333d3282);
			regmap_ग_लिखो(priv->hhi, HHI_HDMI_PHY_CNTL3, 0x2136315b);
		पूर्ण अन्यथा अगर (pixel_घड़ी >= 297000) अणु
			/* 2.97Gbps */
			regmap_ग_लिखो(priv->hhi, HHI_HDMI_PHY_CNTL0, 0x33303382);
			regmap_ग_लिखो(priv->hhi, HHI_HDMI_PHY_CNTL3, 0x2036315b);
		पूर्ण अन्यथा अगर (pixel_घड़ी >= 148500) अणु
			/* 1.485Gbps */
			regmap_ग_लिखो(priv->hhi, HHI_HDMI_PHY_CNTL0, 0x33303362);
			regmap_ग_लिखो(priv->hhi, HHI_HDMI_PHY_CNTL3, 0x2016315b);
		पूर्ण अन्यथा अणु
			/* 742.5Mbps, and below */
			regmap_ग_लिखो(priv->hhi, HHI_HDMI_PHY_CNTL0, 0x33604142);
			regmap_ग_लिखो(priv->hhi, HHI_HDMI_PHY_CNTL3, 0x0016315b);
		पूर्ण
	पूर्ण अन्यथा अगर (dw_hdmi_is_compatible(dw_hdmi,
					 "amlogic,meson-gxbb-dw-hdmi")) अणु
		अगर (pixel_घड़ी >= 371250) अणु
			/* 5.94Gbps, 3.7125Gbps */
			regmap_ग_लिखो(priv->hhi, HHI_HDMI_PHY_CNTL0, 0x33353245);
			regmap_ग_लिखो(priv->hhi, HHI_HDMI_PHY_CNTL3, 0x2100115b);
		पूर्ण अन्यथा अगर (pixel_घड़ी >= 297000) अणु
			/* 2.97Gbps */
			regmap_ग_लिखो(priv->hhi, HHI_HDMI_PHY_CNTL0, 0x33634283);
			regmap_ग_लिखो(priv->hhi, HHI_HDMI_PHY_CNTL3, 0xb000115b);
		पूर्ण अन्यथा अणु
			/* 1.485Gbps, and below */
			regmap_ग_लिखो(priv->hhi, HHI_HDMI_PHY_CNTL0, 0x33632122);
			regmap_ग_लिखो(priv->hhi, HHI_HDMI_PHY_CNTL3, 0x2000115b);
		पूर्ण
	पूर्ण अन्यथा अगर (dw_hdmi_is_compatible(dw_hdmi,
					 "amlogic,meson-g12a-dw-hdmi")) अणु
		अगर (pixel_घड़ी >= 371250) अणु
			/* 5.94Gbps, 3.7125Gbps */
			regmap_ग_लिखो(priv->hhi, HHI_HDMI_PHY_CNTL0, 0x37eb65c4);
			regmap_ग_लिखो(priv->hhi, HHI_HDMI_PHY_CNTL3, 0x2ab0ff3b);
			regmap_ग_लिखो(priv->hhi, HHI_HDMI_PHY_CNTL5, 0x0000080b);
		पूर्ण अन्यथा अगर (pixel_घड़ी >= 297000) अणु
			/* 2.97Gbps */
			regmap_ग_लिखो(priv->hhi, HHI_HDMI_PHY_CNTL0, 0x33eb6262);
			regmap_ग_लिखो(priv->hhi, HHI_HDMI_PHY_CNTL3, 0x2ab0ff3b);
			regmap_ग_लिखो(priv->hhi, HHI_HDMI_PHY_CNTL5, 0x00000003);
		पूर्ण अन्यथा अणु
			/* 1.485Gbps, and below */
			regmap_ग_लिखो(priv->hhi, HHI_HDMI_PHY_CNTL0, 0x33eb4242);
			regmap_ग_लिखो(priv->hhi, HHI_HDMI_PHY_CNTL3, 0x2ab0ff3b);
			regmap_ग_लिखो(priv->hhi, HHI_HDMI_PHY_CNTL5, 0x00000003);
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम meson_dw_hdmi_phy_reset(काष्ठा meson_dw_hdmi *dw_hdmi)
अणु
	काष्ठा meson_drm *priv = dw_hdmi->priv;

	/* Enable and software reset */
	regmap_update_bits(priv->hhi, HHI_HDMI_PHY_CNTL1, 0xf, 0xf);

	mdelay(2);

	/* Enable and unreset */
	regmap_update_bits(priv->hhi, HHI_HDMI_PHY_CNTL1, 0xf, 0xe);

	mdelay(2);
पूर्ण

अटल व्योम dw_hdmi_set_vclk(काष्ठा meson_dw_hdmi *dw_hdmi,
			     स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा meson_drm *priv = dw_hdmi->priv;
	पूर्णांक vic = drm_match_cea_mode(mode);
	अचिन्हित पूर्णांक phy_freq;
	अचिन्हित पूर्णांक vclk_freq;
	अचिन्हित पूर्णांक venc_freq;
	अचिन्हित पूर्णांक hdmi_freq;

	vclk_freq = mode->घड़ी;

	/* For 420, pixel घड़ी is half unlike venc घड़ी */
	अगर (dw_hdmi->output_bus_fmt == MEDIA_BUS_FMT_UYYVYY8_0_5X24)
		vclk_freq /= 2;

	/* TMDS घड़ी is pixel_घड़ी * 10 */
	phy_freq = vclk_freq * 10;

	अगर (!vic) अणु
		meson_vclk_setup(priv, MESON_VCLK_TARGET_DMT, phy_freq,
				 vclk_freq, vclk_freq, vclk_freq, false);
		वापस;
	पूर्ण

	/* 480i/576i needs global pixel करोubling */
	अगर (mode->flags & DRM_MODE_FLAG_DBLCLK)
		vclk_freq *= 2;

	venc_freq = vclk_freq;
	hdmi_freq = vclk_freq;

	/* VENC द्विगुन pixels क्रम 1080i, 720p and YUV420 modes */
	अगर (meson_venc_hdmi_venc_repeat(vic) ||
	    dw_hdmi->output_bus_fmt == MEDIA_BUS_FMT_UYYVYY8_0_5X24)
		venc_freq *= 2;

	vclk_freq = max(venc_freq, hdmi_freq);

	अगर (mode->flags & DRM_MODE_FLAG_DBLCLK)
		venc_freq /= 2;

	DRM_DEBUG_DRIVER("vclk:%d phy=%d venc=%d hdmi=%d enci=%d\n",
		phy_freq, vclk_freq, venc_freq, hdmi_freq,
		priv->venc.hdmi_use_enci);

	meson_vclk_setup(priv, MESON_VCLK_TARGET_HDMI, phy_freq, vclk_freq,
			 venc_freq, hdmi_freq, priv->venc.hdmi_use_enci);
पूर्ण

अटल पूर्णांक dw_hdmi_phy_init(काष्ठा dw_hdmi *hdmi, व्योम *data,
			    स्थिर काष्ठा drm_display_info *display,
			    स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा meson_dw_hdmi *dw_hdmi = (काष्ठा meson_dw_hdmi *)data;
	काष्ठा meson_drm *priv = dw_hdmi->priv;
	अचिन्हित पूर्णांक wr_clk =
		पढ़ोl_relaxed(priv->io_base + _REG(VPU_HDMI_SETTING));

	DRM_DEBUG_DRIVER("\"%s\" div%d\n", mode->name,
			 mode->घड़ी > 340000 ? 40 : 10);

	/* Enable घड़ीs */
	regmap_update_bits(priv->hhi, HHI_HDMI_CLK_CNTL, 0xffff, 0x100);

	/* Bring HDMITX MEM output of घातer करोwn */
	regmap_update_bits(priv->hhi, HHI_MEM_PD_REG0, 0xff << 8, 0);

	/* Bring out of reset */
	dw_hdmi->data->top_ग_लिखो(dw_hdmi, HDMITX_TOP_SW_RESET,  0);

	/* Enable पूर्णांकernal pixclk, पंचांगds_clk, spdअगर_clk, i2s_clk, cecclk */
	dw_hdmi_top_ग_लिखो_bits(dw_hdmi, HDMITX_TOP_CLK_CNTL,
			       0x3, 0x3);

	/* Enable cec_clk and hdcp22_पंचांगdsclk_en */
	dw_hdmi_top_ग_लिखो_bits(dw_hdmi, HDMITX_TOP_CLK_CNTL,
			       0x3 << 4, 0x3 << 4);

	/* Enable normal output to PHY */
	dw_hdmi->data->top_ग_लिखो(dw_hdmi, HDMITX_TOP_BIST_CNTL, BIT(12));

	/* TMDS pattern setup */
	अगर (mode->घड़ी > 340000 &&
	    dw_hdmi->output_bus_fmt == MEDIA_BUS_FMT_YUV8_1X24) अणु
		dw_hdmi->data->top_ग_लिखो(dw_hdmi, HDMITX_TOP_TMDS_CLK_PTTN_01,
				  0);
		dw_hdmi->data->top_ग_लिखो(dw_hdmi, HDMITX_TOP_TMDS_CLK_PTTN_23,
				  0x03ff03ff);
	पूर्ण अन्यथा अणु
		dw_hdmi->data->top_ग_लिखो(dw_hdmi, HDMITX_TOP_TMDS_CLK_PTTN_01,
				  0x001f001f);
		dw_hdmi->data->top_ग_लिखो(dw_hdmi, HDMITX_TOP_TMDS_CLK_PTTN_23,
				  0x001f001f);
	पूर्ण

	/* Load TMDS pattern */
	dw_hdmi->data->top_ग_लिखो(dw_hdmi, HDMITX_TOP_TMDS_CLK_PTTN_CNTL, 0x1);
	msleep(20);
	dw_hdmi->data->top_ग_लिखो(dw_hdmi, HDMITX_TOP_TMDS_CLK_PTTN_CNTL, 0x2);

	/* Setup PHY parameters */
	meson_hdmi_phy_setup_mode(dw_hdmi, mode);

	/* Setup PHY */
	regmap_update_bits(priv->hhi, HHI_HDMI_PHY_CNTL1,
			   0xffff << 16, 0x0390 << 16);

	/* BIT_INVERT */
	अगर (dw_hdmi_is_compatible(dw_hdmi, "amlogic,meson-gxl-dw-hdmi") ||
	    dw_hdmi_is_compatible(dw_hdmi, "amlogic,meson-gxm-dw-hdmi") ||
	    dw_hdmi_is_compatible(dw_hdmi, "amlogic,meson-g12a-dw-hdmi"))
		regmap_update_bits(priv->hhi, HHI_HDMI_PHY_CNTL1,
				   BIT(17), 0);
	अन्यथा
		regmap_update_bits(priv->hhi, HHI_HDMI_PHY_CNTL1,
				   BIT(17), BIT(17));

	/* Disable घड़ी, fअगरo, fअगरo_wr */
	regmap_update_bits(priv->hhi, HHI_HDMI_PHY_CNTL1, 0xf, 0);

	dw_hdmi_set_high_पंचांगds_घड़ी_ratio(hdmi, display);

	msleep(100);

	/* Reset PHY 3 बार in a row */
	meson_dw_hdmi_phy_reset(dw_hdmi);
	meson_dw_hdmi_phy_reset(dw_hdmi);
	meson_dw_hdmi_phy_reset(dw_hdmi);

	/* Temporary Disable VENC video stream */
	अगर (priv->venc.hdmi_use_enci)
		ग_लिखोl_relaxed(0, priv->io_base + _REG(ENCI_VIDEO_EN));
	अन्यथा
		ग_लिखोl_relaxed(0, priv->io_base + _REG(ENCP_VIDEO_EN));

	/* Temporary Disable HDMI video stream to HDMI-TX */
	ग_लिखोl_bits_relaxed(0x3, 0,
			    priv->io_base + _REG(VPU_HDMI_SETTING));
	ग_लिखोl_bits_relaxed(0xf << 8, 0,
			    priv->io_base + _REG(VPU_HDMI_SETTING));

	/* Re-Enable VENC video stream */
	अगर (priv->venc.hdmi_use_enci)
		ग_लिखोl_relaxed(1, priv->io_base + _REG(ENCI_VIDEO_EN));
	अन्यथा
		ग_लिखोl_relaxed(1, priv->io_base + _REG(ENCP_VIDEO_EN));

	/* Push back HDMI घड़ी settings */
	ग_लिखोl_bits_relaxed(0xf << 8, wr_clk & (0xf << 8),
			    priv->io_base + _REG(VPU_HDMI_SETTING));

	/* Enable and Select HDMI video source क्रम HDMI-TX */
	अगर (priv->venc.hdmi_use_enci)
		ग_लिखोl_bits_relaxed(0x3, MESON_VENC_SOURCE_ENCI,
				    priv->io_base + _REG(VPU_HDMI_SETTING));
	अन्यथा
		ग_लिखोl_bits_relaxed(0x3, MESON_VENC_SOURCE_ENCP,
				    priv->io_base + _REG(VPU_HDMI_SETTING));

	वापस 0;
पूर्ण

अटल व्योम dw_hdmi_phy_disable(काष्ठा dw_hdmi *hdmi,
				व्योम *data)
अणु
	काष्ठा meson_dw_hdmi *dw_hdmi = (काष्ठा meson_dw_hdmi *)data;
	काष्ठा meson_drm *priv = dw_hdmi->priv;

	DRM_DEBUG_DRIVER("\n");

	regmap_ग_लिखो(priv->hhi, HHI_HDMI_PHY_CNTL0, 0);
पूर्ण

अटल क्रमागत drm_connector_status dw_hdmi_पढ़ो_hpd(काष्ठा dw_hdmi *hdmi,
			     व्योम *data)
अणु
	काष्ठा meson_dw_hdmi *dw_hdmi = (काष्ठा meson_dw_hdmi *)data;

	वापस !!dw_hdmi->data->top_पढ़ो(dw_hdmi, HDMITX_TOP_STAT0) ?
		connector_status_connected : connector_status_disconnected;
पूर्ण

अटल व्योम dw_hdmi_setup_hpd(काष्ठा dw_hdmi *hdmi,
			      व्योम *data)
अणु
	काष्ठा meson_dw_hdmi *dw_hdmi = (काष्ठा meson_dw_hdmi *)data;

	/* Setup HPD Filter */
	dw_hdmi->data->top_ग_लिखो(dw_hdmi, HDMITX_TOP_HPD_FILTER,
			  (0xa << 12) | 0xa0);

	/* Clear पूर्णांकerrupts */
	dw_hdmi->data->top_ग_लिखो(dw_hdmi, HDMITX_TOP_INTR_STAT_CLR,
			  HDMITX_TOP_INTR_HPD_RISE | HDMITX_TOP_INTR_HPD_FALL);

	/* Unmask पूर्णांकerrupts */
	dw_hdmi_top_ग_लिखो_bits(dw_hdmi, HDMITX_TOP_INTR_MASKN,
			HDMITX_TOP_INTR_HPD_RISE | HDMITX_TOP_INTR_HPD_FALL,
			HDMITX_TOP_INTR_HPD_RISE | HDMITX_TOP_INTR_HPD_FALL);
पूर्ण

अटल स्थिर काष्ठा dw_hdmi_phy_ops meson_dw_hdmi_phy_ops = अणु
	.init = dw_hdmi_phy_init,
	.disable = dw_hdmi_phy_disable,
	.पढ़ो_hpd = dw_hdmi_पढ़ो_hpd,
	.setup_hpd = dw_hdmi_setup_hpd,
पूर्ण;

अटल irqवापस_t dw_hdmi_top_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा meson_dw_hdmi *dw_hdmi = dev_id;
	u32 stat;

	stat = dw_hdmi->data->top_पढ़ो(dw_hdmi, HDMITX_TOP_INTR_STAT);
	dw_hdmi->data->top_ग_लिखो(dw_hdmi, HDMITX_TOP_INTR_STAT_CLR, stat);

	/* HPD Events, handle in the thपढ़ोed पूर्णांकerrupt handler */
	अगर (stat & (HDMITX_TOP_INTR_HPD_RISE | HDMITX_TOP_INTR_HPD_FALL)) अणु
		dw_hdmi->irq_stat = stat;
		वापस IRQ_WAKE_THREAD;
	पूर्ण

	/* HDMI Controller Interrupt */
	अगर (stat & 1)
		वापस IRQ_NONE;

	/* TOFIX Handle HDCP Interrupts */

	वापस IRQ_HANDLED;
पूर्ण

/* Thपढ़ोed पूर्णांकerrupt handler to manage HPD events */
अटल irqवापस_t dw_hdmi_top_thपढ़ो_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा meson_dw_hdmi *dw_hdmi = dev_id;
	u32 stat = dw_hdmi->irq_stat;

	/* HPD Events */
	अगर (stat & (HDMITX_TOP_INTR_HPD_RISE | HDMITX_TOP_INTR_HPD_FALL)) अणु
		bool hpd_connected = false;

		अगर (stat & HDMITX_TOP_INTR_HPD_RISE)
			hpd_connected = true;

		dw_hdmi_setup_rx_sense(dw_hdmi->hdmi, hpd_connected,
				       hpd_connected);

		drm_helper_hpd_irq_event(dw_hdmi->encoder.dev);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल क्रमागत drm_mode_status
dw_hdmi_mode_valid(काष्ठा dw_hdmi *hdmi, व्योम *data,
		   स्थिर काष्ठा drm_display_info *display_info,
		   स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा meson_dw_hdmi *dw_hdmi = data;
	काष्ठा meson_drm *priv = dw_hdmi->priv;
	bool is_hdmi2_sink = display_info->hdmi.scdc.supported;
	अचिन्हित पूर्णांक phy_freq;
	अचिन्हित पूर्णांक vclk_freq;
	अचिन्हित पूर्णांक venc_freq;
	अचिन्हित पूर्णांक hdmi_freq;
	पूर्णांक vic = drm_match_cea_mode(mode);
	क्रमागत drm_mode_status status;

	DRM_DEBUG_DRIVER("Modeline " DRM_MODE_FMT "\n", DRM_MODE_ARG(mode));

	/* If sink करोes not support 540MHz, reject the non-420 HDMI2 modes */
	अगर (display_info->max_पंचांगds_घड़ी &&
	    mode->घड़ी > display_info->max_पंचांगds_घड़ी &&
	    !drm_mode_is_420_only(display_info, mode) &&
	    !drm_mode_is_420_also(display_info, mode))
		वापस MODE_BAD;

	/* Check against non-VIC supported modes */
	अगर (!vic) अणु
		status = meson_venc_hdmi_supported_mode(mode);
		अगर (status != MODE_OK)
			वापस status;

		वापस meson_vclk_dmt_supported_freq(priv, mode->घड़ी);
	/* Check against supported VIC modes */
	पूर्ण अन्यथा अगर (!meson_venc_hdmi_supported_vic(vic))
		वापस MODE_BAD;

	vclk_freq = mode->घड़ी;

	/* For 420, pixel घड़ी is half unlike venc घड़ी */
	अगर (drm_mode_is_420_only(display_info, mode) ||
	    (!is_hdmi2_sink &&
	     drm_mode_is_420_also(display_info, mode)))
		vclk_freq /= 2;

	/* TMDS घड़ी is pixel_घड़ी * 10 */
	phy_freq = vclk_freq * 10;

	/* 480i/576i needs global pixel करोubling */
	अगर (mode->flags & DRM_MODE_FLAG_DBLCLK)
		vclk_freq *= 2;

	venc_freq = vclk_freq;
	hdmi_freq = vclk_freq;

	/* VENC द्विगुन pixels क्रम 1080i, 720p and YUV420 modes */
	अगर (meson_venc_hdmi_venc_repeat(vic) ||
	    drm_mode_is_420_only(display_info, mode) ||
	    (!is_hdmi2_sink &&
	     drm_mode_is_420_also(display_info, mode)))
		venc_freq *= 2;

	vclk_freq = max(venc_freq, hdmi_freq);

	अगर (mode->flags & DRM_MODE_FLAG_DBLCLK)
		venc_freq /= 2;

	dev_dbg(dw_hdmi->dev, "%s: vclk:%d phy=%d venc=%d hdmi=%d\n",
		__func__, phy_freq, vclk_freq, venc_freq, hdmi_freq);

	वापस meson_vclk_vic_supported_freq(priv, phy_freq, vclk_freq);
पूर्ण

/* Encoder */

अटल स्थिर u32 meson_dw_hdmi_out_bus_fmts[] = अणु
	MEDIA_BUS_FMT_YUV8_1X24,
	MEDIA_BUS_FMT_UYYVYY8_0_5X24,
पूर्ण;

अटल व्योम meson_venc_hdmi_encoder_destroy(काष्ठा drm_encoder *encoder)
अणु
	drm_encoder_cleanup(encoder);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs meson_venc_hdmi_encoder_funcs = अणु
	.destroy        = meson_venc_hdmi_encoder_destroy,
पूर्ण;

अटल u32 *
meson_venc_hdmi_encoder_get_inp_bus_fmts(काष्ठा drm_bridge *bridge,
					काष्ठा drm_bridge_state *bridge_state,
					काष्ठा drm_crtc_state *crtc_state,
					काष्ठा drm_connector_state *conn_state,
					u32 output_fmt,
					अचिन्हित पूर्णांक *num_input_fmts)
अणु
	u32 *input_fmts = शून्य;
	पूर्णांक i;

	*num_input_fmts = 0;

	क्रम (i = 0 ; i < ARRAY_SIZE(meson_dw_hdmi_out_bus_fmts) ; ++i) अणु
		अगर (output_fmt == meson_dw_hdmi_out_bus_fmts[i]) अणु
			*num_input_fmts = 1;
			input_fmts = kसुस्मृति(*num_input_fmts,
					     माप(*input_fmts),
					     GFP_KERNEL);
			अगर (!input_fmts)
				वापस शून्य;

			input_fmts[0] = output_fmt;

			अवरोध;
		पूर्ण
	पूर्ण

	वापस input_fmts;
पूर्ण

अटल पूर्णांक meson_venc_hdmi_encoder_atomic_check(काष्ठा drm_bridge *bridge,
					काष्ठा drm_bridge_state *bridge_state,
					काष्ठा drm_crtc_state *crtc_state,
					काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा meson_dw_hdmi *dw_hdmi = bridge_to_meson_dw_hdmi(bridge);

	dw_hdmi->output_bus_fmt = bridge_state->output_bus_cfg.क्रमmat;

	DRM_DEBUG_DRIVER("output_bus_fmt %lx\n", dw_hdmi->output_bus_fmt);

	वापस 0;
पूर्ण

अटल व्योम meson_venc_hdmi_encoder_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा meson_dw_hdmi *dw_hdmi = bridge_to_meson_dw_hdmi(bridge);
	काष्ठा meson_drm *priv = dw_hdmi->priv;

	DRM_DEBUG_DRIVER("\n");

	ग_लिखोl_bits_relaxed(0x3, 0,
			    priv->io_base + _REG(VPU_HDMI_SETTING));

	ग_लिखोl_relaxed(0, priv->io_base + _REG(ENCI_VIDEO_EN));
	ग_लिखोl_relaxed(0, priv->io_base + _REG(ENCP_VIDEO_EN));
पूर्ण

अटल व्योम meson_venc_hdmi_encoder_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा meson_dw_hdmi *dw_hdmi = bridge_to_meson_dw_hdmi(bridge);
	काष्ठा meson_drm *priv = dw_hdmi->priv;

	DRM_DEBUG_DRIVER("%s\n", priv->venc.hdmi_use_enci ? "VENCI" : "VENCP");

	अगर (priv->venc.hdmi_use_enci)
		ग_लिखोl_relaxed(1, priv->io_base + _REG(ENCI_VIDEO_EN));
	अन्यथा
		ग_लिखोl_relaxed(1, priv->io_base + _REG(ENCP_VIDEO_EN));
पूर्ण

अटल व्योम meson_venc_hdmi_encoder_mode_set(काष्ठा drm_bridge *bridge,
				   स्थिर काष्ठा drm_display_mode *mode,
				   स्थिर काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा meson_dw_hdmi *dw_hdmi = bridge_to_meson_dw_hdmi(bridge);
	काष्ठा meson_drm *priv = dw_hdmi->priv;
	पूर्णांक vic = drm_match_cea_mode(mode);
	अचिन्हित पूर्णांक ycrcb_map = VPU_HDMI_OUTPUT_CBYCR;
	bool yuv420_mode = false;

	DRM_DEBUG_DRIVER("\"%s\" vic %d\n", mode->name, vic);

	अगर (dw_hdmi->output_bus_fmt == MEDIA_BUS_FMT_UYYVYY8_0_5X24) अणु
		ycrcb_map = VPU_HDMI_OUTPUT_CRYCB;
		yuv420_mode = true;
	पूर्ण

	/* VENC + VENC-DVI Mode setup */
	meson_venc_hdmi_mode_set(priv, vic, ycrcb_map, yuv420_mode, mode);

	/* VCLK Set घड़ी */
	dw_hdmi_set_vclk(dw_hdmi, mode);

	अगर (dw_hdmi->output_bus_fmt == MEDIA_BUS_FMT_UYYVYY8_0_5X24)
		/* Setup YUV420 to HDMI-TX, no 10bit diphering */
		ग_लिखोl_relaxed(2 | (2 << 2),
			       priv->io_base + _REG(VPU_HDMI_FMT_CTRL));
	अन्यथा
		/* Setup YUV444 to HDMI-TX, no 10bit diphering */
		ग_लिखोl_relaxed(0, priv->io_base + _REG(VPU_HDMI_FMT_CTRL));
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs meson_venc_hdmi_encoder_bridge_funcs = अणु
	.atomic_duplicate_state = drm_atomic_helper_bridge_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_bridge_destroy_state,
	.atomic_get_input_bus_fmts = meson_venc_hdmi_encoder_get_inp_bus_fmts,
	.atomic_reset = drm_atomic_helper_bridge_reset,
	.atomic_check = meson_venc_hdmi_encoder_atomic_check,
	.enable	= meson_venc_hdmi_encoder_enable,
	.disable = meson_venc_hdmi_encoder_disable,
	.mode_set = meson_venc_hdmi_encoder_mode_set,
पूर्ण;

/* DW HDMI Regmap */

अटल पूर्णांक meson_dw_hdmi_reg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg,
				  अचिन्हित पूर्णांक *result)
अणु
	काष्ठा meson_dw_hdmi *dw_hdmi = context;

	*result = dw_hdmi->data->dwc_पढ़ो(dw_hdmi, reg);

	वापस 0;

पूर्ण

अटल पूर्णांक meson_dw_hdmi_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
				   अचिन्हित पूर्णांक val)
अणु
	काष्ठा meson_dw_hdmi *dw_hdmi = context;

	dw_hdmi->data->dwc_ग_लिखो(dw_hdmi, reg, val);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config meson_dw_hdmi_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 8,
	.reg_पढ़ो = meson_dw_hdmi_reg_पढ़ो,
	.reg_ग_लिखो = meson_dw_hdmi_reg_ग_लिखो,
	.max_रेजिस्टर = 0x10000,
	.fast_io = true,
पूर्ण;

अटल स्थिर काष्ठा meson_dw_hdmi_data meson_dw_hdmi_gx_data = अणु
	.top_पढ़ो = dw_hdmi_top_पढ़ो,
	.top_ग_लिखो = dw_hdmi_top_ग_लिखो,
	.dwc_पढ़ो = dw_hdmi_dwc_पढ़ो,
	.dwc_ग_लिखो = dw_hdmi_dwc_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा meson_dw_hdmi_data meson_dw_hdmi_g12a_data = अणु
	.top_पढ़ो = dw_hdmi_g12a_top_पढ़ो,
	.top_ग_लिखो = dw_hdmi_g12a_top_ग_लिखो,
	.dwc_पढ़ो = dw_hdmi_g12a_dwc_पढ़ो,
	.dwc_ग_लिखो = dw_hdmi_g12a_dwc_ग_लिखो,
पूर्ण;

अटल bool meson_hdmi_connector_is_available(काष्ठा device *dev)
अणु
	काष्ठा device_node *ep, *remote;

	/* HDMI Connector is on the second port, first endpoपूर्णांक */
	ep = of_graph_get_endpoपूर्णांक_by_regs(dev->of_node, 1, 0);
	अगर (!ep)
		वापस false;

	/* If the endpoपूर्णांक node exists, consider it enabled */
	remote = of_graph_get_remote_port(ep);
	अगर (remote) अणु
		of_node_put(ep);
		वापस true;
	पूर्ण

	of_node_put(ep);
	of_node_put(remote);

	वापस false;
पूर्ण

अटल व्योम meson_dw_hdmi_init(काष्ठा meson_dw_hdmi *meson_dw_hdmi)
अणु
	काष्ठा meson_drm *priv = meson_dw_hdmi->priv;

	/* Enable घड़ीs */
	regmap_update_bits(priv->hhi, HHI_HDMI_CLK_CNTL, 0xffff, 0x100);

	/* Bring HDMITX MEM output of घातer करोwn */
	regmap_update_bits(priv->hhi, HHI_MEM_PD_REG0, 0xff << 8, 0);

	/* Reset HDMITX APB & TX & PHY */
	reset_control_reset(meson_dw_hdmi->hdmitx_apb);
	reset_control_reset(meson_dw_hdmi->hdmitx_ctrl);
	reset_control_reset(meson_dw_hdmi->hdmitx_phy);

	/* Enable APB3 fail on error */
	अगर (!meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A)) अणु
		ग_लिखोl_bits_relaxed(BIT(15), BIT(15),
				    meson_dw_hdmi->hdmitx + HDMITX_TOP_CTRL_REG);
		ग_लिखोl_bits_relaxed(BIT(15), BIT(15),
				    meson_dw_hdmi->hdmitx + HDMITX_DWC_CTRL_REG);
	पूर्ण

	/* Bring out of reset */
	meson_dw_hdmi->data->top_ग_लिखो(meson_dw_hdmi,
				       HDMITX_TOP_SW_RESET,  0);

	msleep(20);

	meson_dw_hdmi->data->top_ग_लिखो(meson_dw_hdmi,
				       HDMITX_TOP_CLK_CNTL, 0xff);

	/* Enable HDMI-TX Interrupt */
	meson_dw_hdmi->data->top_ग_लिखो(meson_dw_hdmi, HDMITX_TOP_INTR_STAT_CLR,
				       HDMITX_TOP_INTR_CORE);

	meson_dw_hdmi->data->top_ग_लिखो(meson_dw_hdmi, HDMITX_TOP_INTR_MASKN,
				       HDMITX_TOP_INTR_CORE);

पूर्ण

अटल व्योम meson_disable_regulator(व्योम *data)
अणु
	regulator_disable(data);
पूर्ण

अटल व्योम meson_disable_clk(व्योम *data)
अणु
	clk_disable_unprepare(data);
पूर्ण

अटल पूर्णांक meson_enable_clk(काष्ठा device *dev, अक्षर *name)
अणु
	काष्ठा clk *clk;
	पूर्णांक ret;

	clk = devm_clk_get(dev, name);
	अगर (IS_ERR(clk)) अणु
		dev_err(dev, "Unable to get %s pclk\n", name);
		वापस PTR_ERR(clk);
	पूर्ण

	ret = clk_prepare_enable(clk);
	अगर (!ret)
		ret = devm_add_action_or_reset(dev, meson_disable_clk, clk);

	वापस ret;
पूर्ण

अटल पूर्णांक meson_dw_hdmi_bind(काष्ठा device *dev, काष्ठा device *master,
				व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	स्थिर काष्ठा meson_dw_hdmi_data *match;
	काष्ठा meson_dw_hdmi *meson_dw_hdmi;
	काष्ठा drm_device *drm = data;
	काष्ठा meson_drm *priv = drm->dev_निजी;
	काष्ठा dw_hdmi_plat_data *dw_plat_data;
	काष्ठा drm_bridge *next_bridge;
	काष्ठा drm_encoder *encoder;
	काष्ठा resource *res;
	पूर्णांक irq;
	पूर्णांक ret;

	DRM_DEBUG_DRIVER("\n");

	अगर (!meson_hdmi_connector_is_available(dev)) अणु
		dev_info(drm->dev, "HDMI Output connector not available\n");
		वापस -ENODEV;
	पूर्ण

	match = of_device_get_match_data(&pdev->dev);
	अगर (!match) अणु
		dev_err(&pdev->dev, "failed to get match data\n");
		वापस -ENODEV;
	पूर्ण

	meson_dw_hdmi = devm_kzalloc(dev, माप(*meson_dw_hdmi),
				     GFP_KERNEL);
	अगर (!meson_dw_hdmi)
		वापस -ENOMEM;

	meson_dw_hdmi->priv = priv;
	meson_dw_hdmi->dev = dev;
	meson_dw_hdmi->data = match;
	dw_plat_data = &meson_dw_hdmi->dw_plat_data;
	encoder = &meson_dw_hdmi->encoder;

	meson_dw_hdmi->hdmi_supply = devm_regulator_get_optional(dev, "hdmi");
	अगर (IS_ERR(meson_dw_hdmi->hdmi_supply)) अणु
		अगर (PTR_ERR(meson_dw_hdmi->hdmi_supply) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		meson_dw_hdmi->hdmi_supply = शून्य;
	पूर्ण अन्यथा अणु
		ret = regulator_enable(meson_dw_hdmi->hdmi_supply);
		अगर (ret)
			वापस ret;
		ret = devm_add_action_or_reset(dev, meson_disable_regulator,
					       meson_dw_hdmi->hdmi_supply);
		अगर (ret)
			वापस ret;
	पूर्ण

	meson_dw_hdmi->hdmitx_apb = devm_reset_control_get_exclusive(dev,
						"hdmitx_apb");
	अगर (IS_ERR(meson_dw_hdmi->hdmitx_apb)) अणु
		dev_err(dev, "Failed to get hdmitx_apb reset\n");
		वापस PTR_ERR(meson_dw_hdmi->hdmitx_apb);
	पूर्ण

	meson_dw_hdmi->hdmitx_ctrl = devm_reset_control_get_exclusive(dev,
						"hdmitx");
	अगर (IS_ERR(meson_dw_hdmi->hdmitx_ctrl)) अणु
		dev_err(dev, "Failed to get hdmitx reset\n");
		वापस PTR_ERR(meson_dw_hdmi->hdmitx_ctrl);
	पूर्ण

	meson_dw_hdmi->hdmitx_phy = devm_reset_control_get_exclusive(dev,
						"hdmitx_phy");
	अगर (IS_ERR(meson_dw_hdmi->hdmitx_phy)) अणु
		dev_err(dev, "Failed to get hdmitx_phy reset\n");
		वापस PTR_ERR(meson_dw_hdmi->hdmitx_phy);
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	meson_dw_hdmi->hdmitx = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(meson_dw_hdmi->hdmitx))
		वापस PTR_ERR(meson_dw_hdmi->hdmitx);

	ret = meson_enable_clk(dev, "isfr");
	अगर (ret)
		वापस ret;

	ret = meson_enable_clk(dev, "iahb");
	अगर (ret)
		वापस ret;

	ret = meson_enable_clk(dev, "venci");
	अगर (ret)
		वापस ret;

	dw_plat_data->regm = devm_regmap_init(dev, शून्य, meson_dw_hdmi,
					      &meson_dw_hdmi_regmap_config);
	अगर (IS_ERR(dw_plat_data->regm))
		वापस PTR_ERR(dw_plat_data->regm);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_thपढ़ोed_irq(dev, irq, dw_hdmi_top_irq,
					dw_hdmi_top_thपढ़ो_irq, IRQF_SHARED,
					"dw_hdmi_top_irq", meson_dw_hdmi);
	अगर (ret) अणु
		dev_err(dev, "Failed to request hdmi top irq\n");
		वापस ret;
	पूर्ण

	/* Encoder */

	ret = drm_encoder_init(drm, encoder, &meson_venc_hdmi_encoder_funcs,
			       DRM_MODE_ENCODER_TMDS, "meson_hdmi");
	अगर (ret) अणु
		dev_err(priv->dev, "Failed to init HDMI encoder\n");
		वापस ret;
	पूर्ण

	meson_dw_hdmi->bridge.funcs = &meson_venc_hdmi_encoder_bridge_funcs;
	drm_bridge_attach(encoder, &meson_dw_hdmi->bridge, शून्य, 0);

	encoder->possible_crtcs = BIT(0);

	meson_dw_hdmi_init(meson_dw_hdmi);

	DRM_DEBUG_DRIVER("encoder initialized\n");

	/* Bridge / Connector */

	dw_plat_data->priv_data = meson_dw_hdmi;
	dw_plat_data->mode_valid = dw_hdmi_mode_valid;
	dw_plat_data->phy_ops = &meson_dw_hdmi_phy_ops;
	dw_plat_data->phy_name = "meson_dw_hdmi_phy";
	dw_plat_data->phy_data = meson_dw_hdmi;
	dw_plat_data->input_bus_encoding = V4L2_YCBCR_ENC_709;
	dw_plat_data->ycbcr_420_allowed = true;

	अगर (dw_hdmi_is_compatible(meson_dw_hdmi, "amlogic,meson-gxl-dw-hdmi") ||
	    dw_hdmi_is_compatible(meson_dw_hdmi, "amlogic,meson-gxm-dw-hdmi") ||
	    dw_hdmi_is_compatible(meson_dw_hdmi, "amlogic,meson-g12a-dw-hdmi"))
		dw_plat_data->use_drm_infoframe = true;

	platक्रमm_set_drvdata(pdev, meson_dw_hdmi);

	meson_dw_hdmi->hdmi = dw_hdmi_probe(pdev,
					    &meson_dw_hdmi->dw_plat_data);
	अगर (IS_ERR(meson_dw_hdmi->hdmi))
		वापस PTR_ERR(meson_dw_hdmi->hdmi);

	next_bridge = of_drm_find_bridge(pdev->dev.of_node);
	अगर (next_bridge)
		drm_bridge_attach(encoder, next_bridge,
				  &meson_dw_hdmi->bridge, 0);

	DRM_DEBUG_DRIVER("HDMI controller initialized\n");

	वापस 0;
पूर्ण

अटल व्योम meson_dw_hdmi_unbind(काष्ठा device *dev, काष्ठा device *master,
				   व्योम *data)
अणु
	काष्ठा meson_dw_hdmi *meson_dw_hdmi = dev_get_drvdata(dev);

	dw_hdmi_unbind(meson_dw_hdmi->hdmi);
पूर्ण

अटल स्थिर काष्ठा component_ops meson_dw_hdmi_ops = अणु
	.bind	= meson_dw_hdmi_bind,
	.unbind	= meson_dw_hdmi_unbind,
पूर्ण;

अटल पूर्णांक __maybe_unused meson_dw_hdmi_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा meson_dw_hdmi *meson_dw_hdmi = dev_get_drvdata(dev);

	अगर (!meson_dw_hdmi)
		वापस 0;

	/* Reset TOP */
	meson_dw_hdmi->data->top_ग_लिखो(meson_dw_hdmi,
				       HDMITX_TOP_SW_RESET, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused meson_dw_hdmi_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा meson_dw_hdmi *meson_dw_hdmi = dev_get_drvdata(dev);

	अगर (!meson_dw_hdmi)
		वापस 0;

	meson_dw_hdmi_init(meson_dw_hdmi);

	dw_hdmi_resume(meson_dw_hdmi->hdmi);

	वापस 0;
पूर्ण

अटल पूर्णांक meson_dw_hdmi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस component_add(&pdev->dev, &meson_dw_hdmi_ops);
पूर्ण

अटल पूर्णांक meson_dw_hdmi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &meson_dw_hdmi_ops);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops meson_dw_hdmi_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(meson_dw_hdmi_pm_suspend,
				meson_dw_hdmi_pm_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id meson_dw_hdmi_of_table[] = अणु
	अणु .compatible = "amlogic,meson-gxbb-dw-hdmi",
	  .data = &meson_dw_hdmi_gx_data पूर्ण,
	अणु .compatible = "amlogic,meson-gxl-dw-hdmi",
	  .data = &meson_dw_hdmi_gx_data पूर्ण,
	अणु .compatible = "amlogic,meson-gxm-dw-hdmi",
	  .data = &meson_dw_hdmi_gx_data पूर्ण,
	अणु .compatible = "amlogic,meson-g12a-dw-hdmi",
	  .data = &meson_dw_hdmi_g12a_data पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, meson_dw_hdmi_of_table);

अटल काष्ठा platक्रमm_driver meson_dw_hdmi_platक्रमm_driver = अणु
	.probe		= meson_dw_hdmi_probe,
	.हटाओ		= meson_dw_hdmi_हटाओ,
	.driver		= अणु
		.name		= DRIVER_NAME,
		.of_match_table	= meson_dw_hdmi_of_table,
		.pm = &meson_dw_hdmi_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(meson_dw_hdmi_platक्रमm_driver);

MODULE_AUTHOR("Neil Armstrong <narmstrong@baylibre.com>");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
