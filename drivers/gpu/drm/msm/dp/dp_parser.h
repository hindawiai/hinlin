<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2012-2020, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _DP_PARSER_H_
#घोषणा _DP_PARSER_H_

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/phy/phy-dp.h>

#समावेश "dpu_io_util.h"
#समावेश "msm_drv.h"

#घोषणा DP_LABEL "MDSS DP DISPLAY"
#घोषणा DP_MAX_PIXEL_CLK_KHZ	675000
#घोषणा DP_MAX_NUM_DP_LANES	4

क्रमागत dp_pm_type अणु
	DP_CORE_PM,
	DP_CTRL_PM,
	DP_STREAM_PM,
	DP_PHY_PM,
	DP_MAX_PM
पूर्ण;

काष्ठा dss_io_data अणु
	u32 len;
	व्योम __iomem *base;
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *dp_parser_pm_name(क्रमागत dp_pm_type module)
अणु
	चयन (module) अणु
	हाल DP_CORE_PM:	वापस "DP_CORE_PM";
	हाल DP_CTRL_PM:	वापस "DP_CTRL_PM";
	हाल DP_STREAM_PM:	वापस "DP_STREAM_PM";
	हाल DP_PHY_PM:		वापस "DP_PHY_PM";
	शेष:		वापस "???";
	पूर्ण
पूर्ण

/**
 * काष्ठा dp_display_data  - display related device tree data.
 *
 * @ctrl_node: referece to controller device
 * @phy_node:  reference to phy device
 * @is_active: is the controller currently active
 * @name: name of the display
 * @display_type: type of the display
 */
काष्ठा dp_display_data अणु
	काष्ठा device_node *ctrl_node;
	काष्ठा device_node *phy_node;
	bool is_active;
	स्थिर अक्षर *name;
	स्थिर अक्षर *display_type;
पूर्ण;

/**
 * काष्ठा dp_ctrl_resource - controller's IO related data
 *
 * @dp_controller: Display Port controller mapped memory address
 * @phy_io: phy's mapped memory address
 */
काष्ठा dp_io अणु
	काष्ठा dss_io_data dp_controller;
	काष्ठा phy *phy;
	जोड़ phy_configure_opts phy_opts;
पूर्ण;

/**
 * काष्ठा dp_pinctrl - DP's pin control
 *
 * @pin: pin-controller's instance
 * @state_active: active state pin control
 * @state_hpd_active: hpd active state pin control
 * @state_suspend: suspend state pin control
 */
काष्ठा dp_pinctrl अणु
	काष्ठा pinctrl *pin;
	काष्ठा pinctrl_state *state_active;
	काष्ठा pinctrl_state *state_hpd_active;
	काष्ठा pinctrl_state *state_suspend;
पूर्ण;

#घोषणा DP_DEV_REGULATOR_MAX	4

/* Regulators क्रम DP devices */
काष्ठा dp_reg_entry अणु
	अक्षर name[32];
	पूर्णांक enable_load;
	पूर्णांक disable_load;
पूर्ण;

काष्ठा dp_regulator_cfg अणु
	पूर्णांक num;
	काष्ठा dp_reg_entry regs[DP_DEV_REGULATOR_MAX];
पूर्ण;

/**
 * काष्ठा dp_parser - DP parser's data exposed to clients
 *
 * @pdev: platक्रमm data of the client
 * @mp: gpio, regulator and घड़ी related data
 * @pinctrl: pin-control related data
 * @disp_data: controller's display related data
 * @parse: function to be called by client to parse device tree.
 */
काष्ठा dp_parser अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा dss_module_घातer mp[DP_MAX_PM];
	काष्ठा dp_pinctrl pinctrl;
	काष्ठा dp_io io;
	काष्ठा dp_display_data disp_data;
	स्थिर काष्ठा dp_regulator_cfg *regulator_cfg;
	u32 max_dp_lanes;

	पूर्णांक (*parse)(काष्ठा dp_parser *parser);
पूर्ण;

/**
 * dp_parser_get() - get the DP's device tree parser module
 *
 * @pdev: platक्रमm data of the client
 * वापस: poपूर्णांकer to dp_parser काष्ठाure.
 *
 * This function provides client capability to parse the
 * device tree and populate the data काष्ठाures. The data
 * related to घड़ी, regulators, pin-control and other
 * can be parsed using this module.
 */
काष्ठा dp_parser *dp_parser_get(काष्ठा platक्रमm_device *pdev);

#पूर्ण_अगर
