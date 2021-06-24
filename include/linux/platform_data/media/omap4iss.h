<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ARCH_ARM_PLAT_OMAP4_ISS_H
#घोषणा ARCH_ARM_PLAT_OMAP4_ISS_H

#समावेश <linux/i2c.h>

काष्ठा iss_device;

क्रमागत iss_पूर्णांकerface_type अणु
	ISS_INTERFACE_CSI2A_PHY1,
	ISS_INTERFACE_CSI2B_PHY2,
पूर्ण;

/**
 * काष्ठा iss_csiphy_lane: CSI2 lane position and polarity
 * @pos: position of the lane
 * @pol: polarity of the lane
 */
काष्ठा iss_csiphy_lane अणु
	u8 pos;
	u8 pol;
पूर्ण;

#घोषणा ISS_CSIPHY1_NUM_DATA_LANES	4
#घोषणा ISS_CSIPHY2_NUM_DATA_LANES	1

/**
 * काष्ठा iss_csiphy_lanes_cfg - CSI2 lane configuration
 * @data: Configuration of one or two data lanes
 * @clk: Clock lane configuration
 */
काष्ठा iss_csiphy_lanes_cfg अणु
	काष्ठा iss_csiphy_lane data[ISS_CSIPHY1_NUM_DATA_LANES];
	काष्ठा iss_csiphy_lane clk;
पूर्ण;

/**
 * काष्ठा iss_csi2_platक्रमm_data - CSI2 पूर्णांकerface platक्रमm data
 * @crc: Enable the cyclic redundancy check
 * @vpclk_भाग: Video port output घड़ी control
 */
काष्ठा iss_csi2_platक्रमm_data अणु
	अचिन्हित crc:1;
	अचिन्हित vpclk_भाग:2;
	काष्ठा iss_csiphy_lanes_cfg lanecfg;
पूर्ण;

काष्ठा iss_subdev_i2c_board_info अणु
	काष्ठा i2c_board_info *board_info;
	पूर्णांक i2c_adapter_id;
पूर्ण;

काष्ठा iss_v4l2_subdevs_group अणु
	काष्ठा iss_subdev_i2c_board_info *subdevs;
	क्रमागत iss_पूर्णांकerface_type पूर्णांकerface;
	जोड़ अणु
		काष्ठा iss_csi2_platक्रमm_data csi2;
	पूर्ण bus; /* gcc < 4.6.0 chokes on anonymous जोड़ initializers */
पूर्ण;

काष्ठा iss_platक्रमm_data अणु
	काष्ठा iss_v4l2_subdevs_group *subdevs;
	व्योम (*set_स्थिरraपूर्णांकs)(काष्ठा iss_device *iss, bool enable);
पूर्ण;

#पूर्ण_अगर
