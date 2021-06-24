<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Driver header क्रम S5P HDMI chip.
 *
 * Copyright (c) 2011 Samsung Electronics, Co. Ltd
 * Contact: Tomasz Stanislawski <t.stanislaws@samsung.com>
 */

#अगर_अघोषित S5P_HDMI_H
#घोषणा S5P_HDMI_H

काष्ठा i2c_board_info;

/**
 * @hdmiphy_bus: controller id क्रम HDMIPHY bus
 * @hdmiphy_info: ढाँचा क्रम HDMIPHY I2C device
 * @mhl_bus: controller id क्रम MHL control bus
 * @mhl_info: ढाँचा क्रम MHL I2C device
 * @hpd_gpio: GPIO क्रम Hot-Plug-Detect pin
 *
 * शून्य poपूर्णांकer क्रम *_info fields indicates that
 * the corresponding chip is not present
 */
काष्ठा s5p_hdmi_platक्रमm_data अणु
	पूर्णांक hdmiphy_bus;
	काष्ठा i2c_board_info *hdmiphy_info;
	पूर्णांक mhl_bus;
	काष्ठा i2c_board_info *mhl_info;
	पूर्णांक hpd_gpio;
पूर्ण;

#पूर्ण_अगर /* S5P_HDMI_H */
