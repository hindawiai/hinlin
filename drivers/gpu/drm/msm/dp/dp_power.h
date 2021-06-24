<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2012-2020, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _DP_POWER_H_
#घोषणा _DP_POWER_H_

#समावेश "dp_parser.h"

/**
 * sruct dp_घातer - DisplayPort's घातer related data
 *
 * @init: initializes the regulators/core घड़ीs/GPIOs/pinctrl
 * @deinit: turns off the regulators/core घड़ीs/GPIOs/pinctrl
 * @clk_enable: enable/disable the DP घड़ीs
 * @set_pixel_clk_parent: set the parent of DP pixel घड़ी
 */
काष्ठा dp_घातer अणु
	bool core_clks_on;
	bool link_clks_on;
	bool stream_clks_on;
पूर्ण;

/**
 * dp_घातer_init() - enable घातer supplies क्रम display controller
 *
 * @घातer: instance of घातer module
 * @flip: bool क्रम flipping gpio direction
 * वापस: 0 अगर success or error अगर failure.
 *
 * This API will turn on the regulators and configures gpio's
 * aux/hpd.
 */
पूर्णांक dp_घातer_init(काष्ठा dp_घातer *घातer, bool flip);

/**
 * dp_घातer_deinit() - turn off regulators and gpios.
 *
 * @घातer: instance of घातer module
 * वापस: 0 क्रम success
 *
 * This API turns off घातer and regulators.
 */
पूर्णांक dp_घातer_deinit(काष्ठा dp_घातer *घातer);

/**
 * dp_घातer_clk_status() - display controller घड़ीs status
 *
 * @घातer: instance of घातer module
 * @pm_type: type of pm, core/ctrl/phy
 * वापस: status of घातer घड़ीs
 *
 * This API वापस status of DP घड़ीs
 */

पूर्णांक dp_घातer_clk_status(काष्ठा dp_घातer *dp_घातer, क्रमागत dp_pm_type pm_type);

/**
 * dp_घातer_clk_enable() - enable display controller घड़ीs
 *
 * @घातer: instance of घातer module
 * @pm_type: type of pm, core/ctrl/phy
 * @enable: enables or disables
 * वापस: poपूर्णांकer to allocated घातer module data
 *
 * This API will call setrate and enable क्रम DP घड़ीs
 */

पूर्णांक dp_घातer_clk_enable(काष्ठा dp_घातer *घातer, क्रमागत dp_pm_type pm_type,
				bool enable);

/**
 * dp_घातer_client_init() - initialize घड़ी and regulator modules
 *
 * @घातer: instance of घातer module
 * वापस: 0 क्रम success, error क्रम failure.
 *
 * This API will configure the DisplayPort's घड़ीs and regulator
 * modules.
 */
पूर्णांक dp_घातer_client_init(काष्ठा dp_घातer *घातer);

/**
 * dp_घातer_clinet_deinit() - de-initialize घड़ी and regulator modules
 *
 * @घातer: instance of घातer module
 * वापस: 0 क्रम success, error क्रम failure.
 *
 * This API will de-initialize the DisplayPort's घड़ीs and regulator
 * modueles.
 */
व्योम dp_घातer_client_deinit(काष्ठा dp_घातer *घातer);

/**
 * dp_घातer_get() - configure and get the DisplayPort घातer module data
 *
 * @parser: instance of parser module
 * वापस: poपूर्णांकer to allocated घातer module data
 *
 * This API will configure the DisplayPort's घातer module and provides
 * methods to be called by the client to configure the घातer related
 * modueles.
 */
काष्ठा dp_घातer *dp_घातer_get(काष्ठा device *dev, काष्ठा dp_parser *parser);

#पूर्ण_अगर /* _DP_POWER_H_ */
