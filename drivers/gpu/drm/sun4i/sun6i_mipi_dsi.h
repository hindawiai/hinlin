<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 2016 Allwinnertech Co., Ltd.
 * Copyright (C) 2017-2018 Bootlin
 *
 * Maxime Ripard <maxime.ripard@bootlin.com>
 */

#अगर_अघोषित _SUN6I_MIPI_DSI_H_
#घोषणा _SUN6I_MIPI_DSI_H_

#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_mipi_dsi.h>

#घोषणा SUN6I_DSI_TCON_DIV	4

काष्ठा sun6i_dsi अणु
	काष्ठा drm_connector	connector;
	काष्ठा drm_encoder	encoder;
	काष्ठा mipi_dsi_host	host;

	काष्ठा clk		*bus_clk;
	काष्ठा clk		*mod_clk;
	काष्ठा regmap		*regs;
	काष्ठा regulator	*regulator;
	काष्ठा reset_control	*reset;
	काष्ठा phy		*dphy;

	काष्ठा device		*dev;
	काष्ठा mipi_dsi_device	*device;
	काष्ठा drm_device	*drm;
	काष्ठा drm_panel	*panel;
पूर्ण;

अटल अंतरभूत काष्ठा sun6i_dsi *host_to_sun6i_dsi(काष्ठा mipi_dsi_host *host)
अणु
	वापस container_of(host, काष्ठा sun6i_dsi, host);
पूर्ण;

अटल अंतरभूत काष्ठा sun6i_dsi *connector_to_sun6i_dsi(काष्ठा drm_connector *connector)
अणु
	वापस container_of(connector, काष्ठा sun6i_dsi, connector);
पूर्ण;

अटल अंतरभूत काष्ठा sun6i_dsi *encoder_to_sun6i_dsi(स्थिर काष्ठा drm_encoder *encoder)
अणु
	वापस container_of(encoder, काष्ठा sun6i_dsi, encoder);
पूर्ण;

#पूर्ण_अगर /* _SUN6I_MIPI_DSI_H_ */
