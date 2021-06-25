<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Inक्रमmation क्रम the Marvell Armada MMP camera
 */

#समावेश <media/v4l2-mediabus.h>

क्रमागत dphy3_algo अणु
	DPHY3_ALGO_DEFAULT = 0,
	DPHY3_ALGO_PXA910,
	DPHY3_ALGO_PXA2128
पूर्ण;

काष्ठा mmp_camera_platक्रमm_data अणु
	क्रमागत v4l2_mbus_type bus_type;
	पूर्णांक mclk_src;	/* which घड़ी source the MCLK derives from */
	पूर्णांक mclk_भाग;	/* Clock Divider Value क्रम MCLK */
	/*
	 * MIPI support
	 */
	पूर्णांक dphy[3];		/* DPHY: CSI2_DPHY3, CSI2_DPHY5, CSI2_DPHY6 */
	क्रमागत dphy3_algo dphy3_algo;	/* algos क्रम calculate CSI2_DPHY3 */
	पूर्णांक lane;		/* ccic used lane number; 0 means DVP mode */
	पूर्णांक lane_clk;
पूर्ण;
