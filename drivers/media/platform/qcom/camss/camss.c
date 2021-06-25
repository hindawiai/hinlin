<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * camss.c
 *
 * Qualcomm MSM Camera Subप्रणाली - Core
 *
 * Copyright (c) 2015, The Linux Foundation. All rights reserved.
 * Copyright (C) 2015-2018 Linaro Ltd.
 */
#समावेश <linux/clk.h>
#समावेश <linux/media-bus-क्रमmat.h>
#समावेश <linux/media.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>

#समावेश <media/media-device.h>
#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-mc.h>
#समावेश <media/v4l2-fwnode.h>

#समावेश "camss.h"

#घोषणा CAMSS_CLOCK_MARGIN_NUMERATOR 105
#घोषणा CAMSS_CLOCK_MARGIN_DENOMINATOR 100

अटल स्थिर काष्ठा resources csiphy_res_8x16[] = अणु
	/* CSIPHY0 */
	अणु
		.regulator = अणु शून्य पूर्ण,
		.घड़ी = अणु "top_ahb", "ispif_ahb", "ahb", "csiphy0_timer" पूर्ण,
		.घड़ी_rate = अणु अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 100000000, 200000000 पूर्ण पूर्ण,
		.reg = अणु "csiphy0", "csiphy0_clk_mux" पूर्ण,
		.पूर्णांकerrupt = अणु "csiphy0" पूर्ण
	पूर्ण,

	/* CSIPHY1 */
	अणु
		.regulator = अणु शून्य पूर्ण,
		.घड़ी = अणु "top_ahb", "ispif_ahb", "ahb", "csiphy1_timer" पूर्ण,
		.घड़ी_rate = अणु अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 100000000, 200000000 पूर्ण पूर्ण,
		.reg = अणु "csiphy1", "csiphy1_clk_mux" पूर्ण,
		.पूर्णांकerrupt = अणु "csiphy1" पूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा resources csid_res_8x16[] = अणु
	/* CSID0 */
	अणु
		.regulator = अणु "vdda" पूर्ण,
		.घड़ी = अणु "top_ahb", "ispif_ahb", "csi0_ahb", "ahb",
			   "csi0", "csi0_phy", "csi0_pix", "csi0_rdi" पूर्ण,
		.घड़ी_rate = अणु अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 100000000, 200000000 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण पूर्ण,
		.reg = अणु "csid0" पूर्ण,
		.पूर्णांकerrupt = अणु "csid0" पूर्ण
	पूर्ण,

	/* CSID1 */
	अणु
		.regulator = अणु "vdda" पूर्ण,
		.घड़ी = अणु "top_ahb", "ispif_ahb", "csi1_ahb", "ahb",
			   "csi1", "csi1_phy", "csi1_pix", "csi1_rdi" पूर्ण,
		.घड़ी_rate = अणु अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 100000000, 200000000 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण पूर्ण,
		.reg = अणु "csid1" पूर्ण,
		.पूर्णांकerrupt = अणु "csid1" पूर्ण
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा resources_ispअगर ispअगर_res_8x16 = अणु
	/* ISPIF */
	.घड़ी = अणु "top_ahb", "ahb", "ispif_ahb",
		   "csi0", "csi0_pix", "csi0_rdi",
		   "csi1", "csi1_pix", "csi1_rdi" पूर्ण,
	.घड़ी_क्रम_reset = अणु "vfe0", "csi_vfe0" पूर्ण,
	.reg = अणु "ispif", "csi_clk_mux" पूर्ण,
	.पूर्णांकerrupt = "ispif"

पूर्ण;

अटल स्थिर काष्ठा resources vfe_res_8x16[] = अणु
	/* VFE0 */
	अणु
		.regulator = अणु शून्य पूर्ण,
		.घड़ी = अणु "top_ahb", "vfe0", "csi_vfe0",
			   "vfe_ahb", "vfe_axi", "ahb" पूर्ण,
		.घड़ी_rate = अणु अणु 0 पूर्ण,
				अणु 50000000, 80000000, 100000000, 160000000,
				  177780000, 200000000, 266670000, 320000000,
				  400000000, 465000000 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण पूर्ण,
		.reg = अणु "vfe0" पूर्ण,
		.पूर्णांकerrupt = अणु "vfe0" पूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा resources csiphy_res_8x96[] = अणु
	/* CSIPHY0 */
	अणु
		.regulator = अणु शून्य पूर्ण,
		.घड़ी = अणु "top_ahb", "ispif_ahb", "ahb", "csiphy0_timer" पूर्ण,
		.घड़ी_rate = अणु अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 100000000, 200000000, 266666667 पूर्ण पूर्ण,
		.reg = अणु "csiphy0", "csiphy0_clk_mux" पूर्ण,
		.पूर्णांकerrupt = अणु "csiphy0" पूर्ण
	पूर्ण,

	/* CSIPHY1 */
	अणु
		.regulator = अणु शून्य पूर्ण,
		.घड़ी = अणु "top_ahb", "ispif_ahb", "ahb", "csiphy1_timer" पूर्ण,
		.घड़ी_rate = अणु अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 100000000, 200000000, 266666667 पूर्ण पूर्ण,
		.reg = अणु "csiphy1", "csiphy1_clk_mux" पूर्ण,
		.पूर्णांकerrupt = अणु "csiphy1" पूर्ण
	पूर्ण,

	/* CSIPHY2 */
	अणु
		.regulator = अणु शून्य पूर्ण,
		.घड़ी = अणु "top_ahb", "ispif_ahb", "ahb", "csiphy2_timer" पूर्ण,
		.घड़ी_rate = अणु अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 100000000, 200000000, 266666667 पूर्ण पूर्ण,
		.reg = अणु "csiphy2", "csiphy2_clk_mux" पूर्ण,
		.पूर्णांकerrupt = अणु "csiphy2" पूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा resources csid_res_8x96[] = अणु
	/* CSID0 */
	अणु
		.regulator = अणु "vdda" पूर्ण,
		.घड़ी = अणु "top_ahb", "ispif_ahb", "csi0_ahb", "ahb",
			   "csi0", "csi0_phy", "csi0_pix", "csi0_rdi" पूर्ण,
		.घड़ी_rate = अणु अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 100000000, 200000000, 266666667 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण पूर्ण,
		.reg = अणु "csid0" पूर्ण,
		.पूर्णांकerrupt = अणु "csid0" पूर्ण
	पूर्ण,

	/* CSID1 */
	अणु
		.regulator = अणु "vdda" पूर्ण,
		.घड़ी = अणु "top_ahb", "ispif_ahb", "csi1_ahb", "ahb",
			   "csi1", "csi1_phy", "csi1_pix", "csi1_rdi" पूर्ण,
		.घड़ी_rate = अणु अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 100000000, 200000000, 266666667 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण पूर्ण,
		.reg = अणु "csid1" पूर्ण,
		.पूर्णांकerrupt = अणु "csid1" पूर्ण
	पूर्ण,

	/* CSID2 */
	अणु
		.regulator = अणु "vdda" पूर्ण,
		.घड़ी = अणु "top_ahb", "ispif_ahb", "csi2_ahb", "ahb",
			   "csi2", "csi2_phy", "csi2_pix", "csi2_rdi" पूर्ण,
		.घड़ी_rate = अणु अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 100000000, 200000000, 266666667 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण पूर्ण,
		.reg = अणु "csid2" पूर्ण,
		.पूर्णांकerrupt = अणु "csid2" पूर्ण
	पूर्ण,

	/* CSID3 */
	अणु
		.regulator = अणु "vdda" पूर्ण,
		.घड़ी = अणु "top_ahb", "ispif_ahb", "csi3_ahb", "ahb",
			   "csi3", "csi3_phy", "csi3_pix", "csi3_rdi" पूर्ण,
		.घड़ी_rate = अणु अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 100000000, 200000000, 266666667 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण पूर्ण,
		.reg = अणु "csid3" पूर्ण,
		.पूर्णांकerrupt = अणु "csid3" पूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा resources_ispअगर ispअगर_res_8x96 = अणु
	/* ISPIF */
	.घड़ी = अणु "top_ahb", "ahb", "ispif_ahb",
		   "csi0", "csi0_pix", "csi0_rdi",
		   "csi1", "csi1_pix", "csi1_rdi",
		   "csi2", "csi2_pix", "csi2_rdi",
		   "csi3", "csi3_pix", "csi3_rdi" पूर्ण,
	.घड़ी_क्रम_reset = अणु "vfe0", "csi_vfe0", "vfe1", "csi_vfe1" पूर्ण,
	.reg = अणु "ispif", "csi_clk_mux" पूर्ण,
	.पूर्णांकerrupt = "ispif"
पूर्ण;

अटल स्थिर काष्ठा resources vfe_res_8x96[] = अणु
	/* VFE0 */
	अणु
		.regulator = अणु शून्य पूर्ण,
		.घड़ी = अणु "top_ahb", "ahb", "vfe0", "csi_vfe0", "vfe_ahb",
			   "vfe0_ahb", "vfe_axi", "vfe0_stream"पूर्ण,
		.घड़ी_rate = अणु अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 75000000, 100000000, 300000000,
				  320000000, 480000000, 600000000 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण पूर्ण,
		.reg = अणु "vfe0" पूर्ण,
		.पूर्णांकerrupt = अणु "vfe0" पूर्ण
	पूर्ण,

	/* VFE1 */
	अणु
		.regulator = अणु शून्य पूर्ण,
		.घड़ी = अणु "top_ahb", "ahb", "vfe1", "csi_vfe1", "vfe_ahb",
			   "vfe1_ahb", "vfe_axi", "vfe1_stream"पूर्ण,
		.घड़ी_rate = अणु अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 75000000, 100000000, 300000000,
				  320000000, 480000000, 600000000 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण पूर्ण,
		.reg = अणु "vfe1" पूर्ण,
		.पूर्णांकerrupt = अणु "vfe1" पूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा resources csiphy_res_660[] = अणु
	/* CSIPHY0 */
	अणु
		.regulator = अणु शून्य पूर्ण,
		.घड़ी = अणु "top_ahb", "ispif_ahb", "ahb", "csiphy0_timer",
			   "csi0_phy", "csiphy_ahb2crif" पूर्ण,
		.घड़ी_rate = अणु अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 100000000, 200000000, 269333333 पूर्ण,
				अणु 0 पूर्ण पूर्ण,
		.reg = अणु "csiphy0", "csiphy0_clk_mux" पूर्ण,
		.पूर्णांकerrupt = अणु "csiphy0" पूर्ण
	पूर्ण,

	/* CSIPHY1 */
	अणु
		.regulator = अणु शून्य पूर्ण,
		.घड़ी = अणु "top_ahb", "ispif_ahb", "ahb", "csiphy1_timer",
			   "csi1_phy", "csiphy_ahb2crif" पूर्ण,
		.घड़ी_rate = अणु अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 100000000, 200000000, 269333333 पूर्ण,
				अणु 0 पूर्ण पूर्ण,
		.reg = अणु "csiphy1", "csiphy1_clk_mux" पूर्ण,
		.पूर्णांकerrupt = अणु "csiphy1" पूर्ण
	पूर्ण,

	/* CSIPHY2 */
	अणु
		.regulator = अणु शून्य पूर्ण,
		.घड़ी = अणु "top_ahb", "ispif_ahb", "ahb", "csiphy2_timer",
			   "csi2_phy", "csiphy_ahb2crif" पूर्ण,
		.घड़ी_rate = अणु अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 100000000, 200000000, 269333333 पूर्ण,
				अणु 0 पूर्ण पूर्ण,
		.reg = अणु "csiphy2", "csiphy2_clk_mux" पूर्ण,
		.पूर्णांकerrupt = अणु "csiphy2" पूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा resources csid_res_660[] = अणु
	/* CSID0 */
	अणु
		.regulator = अणु "vdda", "vdd_sec" पूर्ण,
		.घड़ी = अणु "top_ahb", "ispif_ahb", "csi0_ahb", "ahb",
			   "csi0", "csi0_phy", "csi0_pix", "csi0_rdi",
			   "cphy_csid0" पूर्ण,
		.घड़ी_rate = अणु अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 100000000, 200000000, 310000000,
				  404000000, 465000000 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण पूर्ण,
		.reg = अणु "csid0" पूर्ण,
		.पूर्णांकerrupt = अणु "csid0" पूर्ण
	पूर्ण,

	/* CSID1 */
	अणु
		.regulator = अणु "vdda", "vdd_sec" पूर्ण,
		.घड़ी = अणु "top_ahb", "ispif_ahb", "csi1_ahb", "ahb",
			   "csi1", "csi1_phy", "csi1_pix", "csi1_rdi",
			   "cphy_csid1" पूर्ण,
		.घड़ी_rate = अणु अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 100000000, 200000000, 310000000,
				  404000000, 465000000 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण पूर्ण,
		.reg = अणु "csid1" पूर्ण,
		.पूर्णांकerrupt = अणु "csid1" पूर्ण
	पूर्ण,

	/* CSID2 */
	अणु
		.regulator = अणु "vdda", "vdd_sec" पूर्ण,
		.घड़ी = अणु "top_ahb", "ispif_ahb", "csi2_ahb", "ahb",
			   "csi2", "csi2_phy", "csi2_pix", "csi2_rdi",
			   "cphy_csid2" पूर्ण,
		.घड़ी_rate = अणु अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 100000000, 200000000, 310000000,
				  404000000, 465000000 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण पूर्ण,
		.reg = अणु "csid2" पूर्ण,
		.पूर्णांकerrupt = अणु "csid2" पूर्ण
	पूर्ण,

	/* CSID3 */
	अणु
		.regulator = अणु "vdda", "vdd_sec" पूर्ण,
		.घड़ी = अणु "top_ahb", "ispif_ahb", "csi3_ahb", "ahb",
			   "csi3", "csi3_phy", "csi3_pix", "csi3_rdi",
			   "cphy_csid3" पूर्ण,
		.घड़ी_rate = अणु अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 100000000, 200000000, 310000000,
				  404000000, 465000000 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण पूर्ण,
		.reg = अणु "csid3" पूर्ण,
		.पूर्णांकerrupt = अणु "csid3" पूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा resources_ispअगर ispअगर_res_660 = अणु
	/* ISPIF */
	.घड़ी = अणु "top_ahb", "ahb", "ispif_ahb",
		   "csi0", "csi0_pix", "csi0_rdi",
		   "csi1", "csi1_pix", "csi1_rdi",
		   "csi2", "csi2_pix", "csi2_rdi",
		   "csi3", "csi3_pix", "csi3_rdi" पूर्ण,
	.घड़ी_क्रम_reset = अणु "vfe0", "csi_vfe0", "vfe1", "csi_vfe1" पूर्ण,
	.reg = अणु "ispif", "csi_clk_mux" पूर्ण,
	.पूर्णांकerrupt = "ispif"
पूर्ण;

अटल स्थिर काष्ठा resources vfe_res_660[] = अणु
	/* VFE0 */
	अणु
		.regulator = अणु शून्य पूर्ण,
		.घड़ी = अणु "throttle_axi", "top_ahb", "ahb", "vfe0",
			   "csi_vfe0", "vfe_ahb", "vfe0_ahb", "vfe_axi",
			   "vfe0_stream"पूर्ण,
		.घड़ी_rate = अणु अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 120000000, 200000000, 256000000,
				  300000000, 404000000, 480000000,
				  540000000, 576000000 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण पूर्ण,
		.reg = अणु "vfe0" पूर्ण,
		.पूर्णांकerrupt = अणु "vfe0" पूर्ण
	पूर्ण,

	/* VFE1 */
	अणु
		.regulator = अणु शून्य पूर्ण,
		.घड़ी = अणु "throttle_axi", "top_ahb", "ahb", "vfe1",
			   "csi_vfe1", "vfe_ahb", "vfe1_ahb", "vfe_axi",
			   "vfe1_stream"पूर्ण,
		.घड़ी_rate = अणु अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 120000000, 200000000, 256000000,
				  300000000, 404000000, 480000000,
				  540000000, 576000000 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण पूर्ण,
		.reg = अणु "vfe1" पूर्ण,
		.पूर्णांकerrupt = अणु "vfe1" पूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा resources csiphy_res_845[] = अणु
	/* CSIPHY0 */
	अणु
		.regulator = अणु शून्य पूर्ण,
		.घड़ी = अणु "camnoc_axi", "soc_ahb", "slow_ahb_src",
				"cpas_ahb", "cphy_rx_src", "csiphy0",
				"csiphy0_timer_src", "csiphy0_timer" पूर्ण,
		.घड़ी_rate = अणु अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 19200000, 240000000, 269333333 पूर्ण पूर्ण,
		.reg = अणु "csiphy0" पूर्ण,
		.पूर्णांकerrupt = अणु "csiphy0" पूर्ण
	पूर्ण,

	/* CSIPHY1 */
	अणु
		.regulator = अणु शून्य पूर्ण,
		.घड़ी = अणु "camnoc_axi", "soc_ahb", "slow_ahb_src",
				"cpas_ahb", "cphy_rx_src", "csiphy1",
				"csiphy1_timer_src", "csiphy1_timer" पूर्ण,
		.घड़ी_rate = अणु अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 19200000, 240000000, 269333333 पूर्ण पूर्ण,
		.reg = अणु "csiphy1" पूर्ण,
		.पूर्णांकerrupt = अणु "csiphy1" पूर्ण
	पूर्ण,

	/* CSIPHY2 */
	अणु
		.regulator = अणु शून्य पूर्ण,
		.घड़ी = अणु "camnoc_axi", "soc_ahb", "slow_ahb_src",
				"cpas_ahb", "cphy_rx_src", "csiphy2",
				"csiphy2_timer_src", "csiphy2_timer" पूर्ण,
		.घड़ी_rate = अणु अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 19200000, 240000000, 269333333 पूर्ण पूर्ण,
		.reg = अणु "csiphy2" पूर्ण,
		.पूर्णांकerrupt = अणु "csiphy2" पूर्ण
	पूर्ण,

	/* CSIPHY3 */
	अणु
		.regulator = अणु शून्य पूर्ण,
		.घड़ी = अणु "camnoc_axi", "soc_ahb", "slow_ahb_src",
				"cpas_ahb", "cphy_rx_src", "csiphy3",
				"csiphy3_timer_src", "csiphy3_timer" पूर्ण,
		.घड़ी_rate = अणु अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 19200000, 240000000, 269333333 पूर्ण पूर्ण,
		.reg = अणु "csiphy3" पूर्ण,
		.पूर्णांकerrupt = अणु "csiphy3" पूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा resources csid_res_845[] = अणु
	/* CSID0 */
	अणु
		.regulator = अणु "vdda-csi0" पूर्ण,
		.घड़ी = अणु "cpas_ahb", "cphy_rx_src", "slow_ahb_src",
				"soc_ahb", "vfe0", "vfe0_src",
				"vfe0_cphy_rx", "csi0",
				"csi0_src" पूर्ण,
		.घड़ी_rate = अणु अणु 0 पूर्ण,
				अणु 384000000 पूर्ण,
				अणु 80000000 पूर्ण,
				अणु 0 पूर्ण,
				अणु 19200000, 100000000, 320000000, 404000000, 480000000, 600000000 पूर्ण,
				अणु 320000000 पूर्ण,
				अणु 0 पूर्ण,
				अणु 19200000, 75000000, 384000000, 538666667 पूर्ण,
				अणु 384000000 पूर्ण पूर्ण,
		.reg = अणु "csid0" पूर्ण,
		.पूर्णांकerrupt = अणु "csid0" पूर्ण
	पूर्ण,

	/* CSID1 */
	अणु
		.regulator = अणु "vdda-csi1" पूर्ण,
		.घड़ी = अणु "cpas_ahb", "cphy_rx_src", "slow_ahb_src",
				"soc_ahb", "vfe1", "vfe1_src",
				"vfe1_cphy_rx", "csi1",
				"csi1_src" पूर्ण,
		.घड़ी_rate = अणु अणु 0 पूर्ण,
				अणु 384000000 पूर्ण,
				अणु 80000000 पूर्ण,
				अणु 0 पूर्ण,
				अणु 19200000, 100000000, 320000000, 404000000, 480000000, 600000000 पूर्ण,
				अणु 320000000 पूर्ण,
				अणु 0 पूर्ण,
				अणु 19200000, 75000000, 384000000, 538666667 पूर्ण,
				अणु 384000000 पूर्ण पूर्ण,
		.reg = अणु "csid1" पूर्ण,
		.पूर्णांकerrupt = अणु "csid1" पूर्ण
	पूर्ण,

	/* CSID2 */
	अणु
		.regulator = अणु "vdda-csi2" पूर्ण,
		.घड़ी = अणु "cpas_ahb", "cphy_rx_src", "slow_ahb_src",
				"soc_ahb", "vfe_lite", "vfe_lite_src",
				"vfe_lite_cphy_rx", "csi2",
				"csi2_src" पूर्ण,
		.घड़ी_rate = अणु अणु 0 पूर्ण,
				अणु 384000000 पूर्ण,
				अणु 80000000 पूर्ण,
				अणु 0 पूर्ण,
				अणु 19200000, 100000000, 320000000, 404000000, 480000000, 600000000 पूर्ण,
				अणु 320000000 पूर्ण,
				अणु 0 पूर्ण,
				अणु 19200000, 75000000, 384000000, 538666667 पूर्ण,
				अणु 384000000 पूर्ण पूर्ण,
		.reg = अणु "csid2" पूर्ण,
		.पूर्णांकerrupt = अणु "csid2" पूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा resources vfe_res_845[] = अणु
	/* VFE0 */
	अणु
		.regulator = अणु शून्य पूर्ण,
		.घड़ी = अणु "camnoc_axi", "cpas_ahb", "slow_ahb_src",
				"soc_ahb", "vfe0", "vfe0_axi",
				"vfe0_src", "csi0",
				"csi0_src"पूर्ण,
		.घड़ी_rate = अणु अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 80000000 पूर्ण,
				अणु 0 पूर्ण,
				अणु 19200000, 100000000, 320000000, 404000000, 480000000, 600000000 पूर्ण,
				अणु 0 पूर्ण,
				अणु 320000000 पूर्ण,
				अणु 19200000, 75000000, 384000000, 538666667 पूर्ण,
				अणु 384000000 पूर्ण पूर्ण,
		.reg = अणु "vfe0" पूर्ण,
		.पूर्णांकerrupt = अणु "vfe0" पूर्ण
	पूर्ण,

	/* VFE1 */
	अणु
		.regulator = अणु शून्य पूर्ण,
		.घड़ी = अणु "camnoc_axi", "cpas_ahb", "slow_ahb_src",
				"soc_ahb", "vfe1", "vfe1_axi",
				"vfe1_src", "csi1",
				"csi1_src"पूर्ण,
		.घड़ी_rate = अणु अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 80000000 पूर्ण,
				अणु 0 पूर्ण,
				अणु 19200000, 100000000, 320000000, 404000000, 480000000, 600000000 पूर्ण,
				अणु 0 पूर्ण,
				अणु 320000000 पूर्ण,
				अणु 19200000, 75000000, 384000000, 538666667 पूर्ण,
				अणु 384000000 पूर्ण पूर्ण,
		.reg = अणु "vfe1" पूर्ण,
		.पूर्णांकerrupt = अणु "vfe1" पूर्ण
	पूर्ण,

	/* VFE-lite */
	अणु
		.regulator = अणु शून्य पूर्ण,
		.घड़ी = अणु "camnoc_axi", "cpas_ahb", "slow_ahb_src",
				"soc_ahb", "vfe_lite",
				"vfe_lite_src", "csi2",
				"csi2_src"पूर्ण,
		.घड़ी_rate = अणु अणु 0 पूर्ण,
				अणु 0 पूर्ण,
				अणु 80000000 पूर्ण,
				अणु 0 पूर्ण,
				अणु 19200000, 100000000, 320000000, 404000000, 480000000, 600000000 पूर्ण,
				अणु 320000000 पूर्ण,
				अणु 19200000, 75000000, 384000000, 538666667 पूर्ण,
				अणु 384000000 पूर्ण पूर्ण,
		.reg = अणु "vfe_lite" पूर्ण,
		.पूर्णांकerrupt = अणु "vfe_lite" पूर्ण
	पूर्ण
पूर्ण;

/*
 * camss_add_घड़ी_margin - Add margin to घड़ी frequency rate
 * @rate: Clock frequency rate
 *
 * When making calculations with physical घड़ी frequency values
 * some safety margin must be added. Add it.
 */
अंतरभूत व्योम camss_add_घड़ी_margin(u64 *rate)
अणु
	*rate *= CAMSS_CLOCK_MARGIN_NUMERATOR;
	*rate = भाग_u64(*rate, CAMSS_CLOCK_MARGIN_DENOMINATOR);
पूर्ण

/*
 * camss_enable_घड़ीs - Enable multiple घड़ीs
 * @nघड़ीs: Number of घड़ीs in घड़ी array
 * @घड़ी: Clock array
 * @dev: Device
 *
 * Return 0 on success or a negative error code otherwise
 */
पूर्णांक camss_enable_घड़ीs(पूर्णांक nघड़ीs, काष्ठा camss_घड़ी *घड़ी,
			काष्ठा device *dev)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < nघड़ीs; i++) अणु
		ret = clk_prepare_enable(घड़ी[i].clk);
		अगर (ret) अणु
			dev_err(dev, "clock enable failed: %d\n", ret);
			जाओ error;
		पूर्ण
	पूर्ण

	वापस 0;

error:
	क्रम (i--; i >= 0; i--)
		clk_disable_unprepare(घड़ी[i].clk);

	वापस ret;
पूर्ण

/*
 * camss_disable_घड़ीs - Disable multiple घड़ीs
 * @nघड़ीs: Number of घड़ीs in घड़ी array
 * @घड़ी: Clock array
 */
व्योम camss_disable_घड़ीs(पूर्णांक nघड़ीs, काष्ठा camss_घड़ी *घड़ी)
अणु
	पूर्णांक i;

	क्रम (i = nघड़ीs - 1; i >= 0; i--)
		clk_disable_unprepare(घड़ी[i].clk);
पूर्ण

/*
 * camss_find_sensor - Find a linked media entity which represents a sensor
 * @entity: Media entity to start searching from
 *
 * Return a poपूर्णांकer to sensor media entity or शून्य अगर not found
 */
काष्ठा media_entity *camss_find_sensor(काष्ठा media_entity *entity)
अणु
	काष्ठा media_pad *pad;

	जबतक (1) अणु
		pad = &entity->pads[0];
		अगर (!(pad->flags & MEDIA_PAD_FL_SINK))
			वापस शून्य;

		pad = media_entity_remote_pad(pad);
		अगर (!pad || !is_media_entity_v4l2_subdev(pad->entity))
			वापस शून्य;

		entity = pad->entity;

		अगर (entity->function == MEDIA_ENT_F_CAM_SENSOR)
			वापस entity;
	पूर्ण
पूर्ण

/**
 * camss_get_link_freq - Get link frequency from sensor
 * @entity: Media entity in the current pipeline
 * @bpp: Number of bits per pixel क्रम the current क्रमmat
 * @lanes: Number of lanes in the link to the sensor
 *
 * Return link frequency on success or a negative error code otherwise
 */
s64 camss_get_link_freq(काष्ठा media_entity *entity, अचिन्हित पूर्णांक bpp,
			अचिन्हित पूर्णांक lanes)
अणु
	काष्ठा media_entity *sensor;
	काष्ठा v4l2_subdev *subdev;

	sensor = camss_find_sensor(entity);
	अगर (!sensor)
		वापस -ENODEV;

	subdev = media_entity_to_v4l2_subdev(sensor);

	वापस v4l2_get_link_freq(subdev->ctrl_handler, bpp, 2 * lanes);
पूर्ण

/*
 * camss_get_pixel_घड़ी - Get pixel घड़ी rate from sensor
 * @entity: Media entity in the current pipeline
 * @pixel_घड़ी: Received pixel घड़ी value
 *
 * Return 0 on success or a negative error code otherwise
 */
पूर्णांक camss_get_pixel_घड़ी(काष्ठा media_entity *entity, u64 *pixel_घड़ी)
अणु
	काष्ठा media_entity *sensor;
	काष्ठा v4l2_subdev *subdev;
	काष्ठा v4l2_ctrl *ctrl;

	sensor = camss_find_sensor(entity);
	अगर (!sensor)
		वापस -ENODEV;

	subdev = media_entity_to_v4l2_subdev(sensor);

	ctrl = v4l2_ctrl_find(subdev->ctrl_handler, V4L2_CID_PIXEL_RATE);

	अगर (!ctrl)
		वापस -EINVAL;

	*pixel_घड़ी = v4l2_ctrl_g_ctrl_पूर्णांक64(ctrl);

	वापस 0;
पूर्ण

पूर्णांक camss_pm_करोमुख्य_on(काष्ठा camss *camss, पूर्णांक id)
अणु
	पूर्णांक ret = 0;

	अगर (id < camss->vfe_num) अणु
		काष्ठा vfe_device *vfe = &camss->vfe[id];

		ret = vfe->ops->pm_करोमुख्य_on(vfe);
	पूर्ण

	वापस ret;
पूर्ण

व्योम camss_pm_करोमुख्य_off(काष्ठा camss *camss, पूर्णांक id)
अणु
	अगर (id < camss->vfe_num) अणु
		काष्ठा vfe_device *vfe = &camss->vfe[id];

		vfe->ops->pm_करोमुख्य_off(vfe);
	पूर्ण
पूर्ण

/*
 * camss_of_parse_endpoपूर्णांक_node - Parse port endpoपूर्णांक node
 * @dev: Device
 * @node: Device node to be parsed
 * @csd: Parsed data from port endpoपूर्णांक node
 *
 * Return 0 on success or a negative error code on failure
 */
अटल पूर्णांक camss_of_parse_endpoपूर्णांक_node(काष्ठा device *dev,
					काष्ठा device_node *node,
					काष्ठा camss_async_subdev *csd)
अणु
	काष्ठा csiphy_lanes_cfg *lncfg = &csd->पूर्णांकerface.csi2.lane_cfg;
	काष्ठा v4l2_fwnode_bus_mipi_csi2 *mipi_csi2;
	काष्ठा v4l2_fwnode_endpoपूर्णांक vep = अणु अणु 0 पूर्ण पूर्ण;
	अचिन्हित पूर्णांक i;

	v4l2_fwnode_endpoपूर्णांक_parse(of_fwnode_handle(node), &vep);

	csd->पूर्णांकerface.csiphy_id = vep.base.port;

	mipi_csi2 = &vep.bus.mipi_csi2;
	lncfg->clk.pos = mipi_csi2->घड़ी_lane;
	lncfg->clk.pol = mipi_csi2->lane_polarities[0];
	lncfg->num_data = mipi_csi2->num_data_lanes;

	lncfg->data = devm_kसुस्मृति(dev,
				   lncfg->num_data, माप(*lncfg->data),
				   GFP_KERNEL);
	अगर (!lncfg->data)
		वापस -ENOMEM;

	क्रम (i = 0; i < lncfg->num_data; i++) अणु
		lncfg->data[i].pos = mipi_csi2->data_lanes[i];
		lncfg->data[i].pol = mipi_csi2->lane_polarities[i + 1];
	पूर्ण

	वापस 0;
पूर्ण

/*
 * camss_of_parse_ports - Parse ports node
 * @dev: Device
 * @notअगरier: v4l2_device notअगरier data
 *
 * Return number of "port" nodes found in "ports" node
 */
अटल पूर्णांक camss_of_parse_ports(काष्ठा camss *camss)
अणु
	काष्ठा device *dev = camss->dev;
	काष्ठा device_node *node = शून्य;
	काष्ठा device_node *remote = शून्य;
	पूर्णांक ret, num_subdevs = 0;

	क्रम_each_endpoपूर्णांक_of_node(dev->of_node, node) अणु
		काष्ठा camss_async_subdev *csd;

		अगर (!of_device_is_available(node))
			जारी;

		remote = of_graph_get_remote_port_parent(node);
		अगर (!remote) अणु
			dev_err(dev, "Cannot get remote parent\n");
			ret = -EINVAL;
			जाओ err_cleanup;
		पूर्ण

		csd = v4l2_async_notअगरier_add_fwnode_subdev(
			&camss->notअगरier, of_fwnode_handle(remote),
			काष्ठा camss_async_subdev);
		of_node_put(remote);
		अगर (IS_ERR(csd)) अणु
			ret = PTR_ERR(csd);
			जाओ err_cleanup;
		पूर्ण

		ret = camss_of_parse_endpoपूर्णांक_node(dev, node, csd);
		अगर (ret < 0)
			जाओ err_cleanup;

		num_subdevs++;
	पूर्ण

	वापस num_subdevs;

err_cleanup:
	of_node_put(node);
	वापस ret;
पूर्ण

/*
 * camss_init_subdevices - Initialize subdev काष्ठाures and resources
 * @camss: CAMSS device
 *
 * Return 0 on success or a negative error code on failure
 */
अटल पूर्णांक camss_init_subdevices(काष्ठा camss *camss)
अणु
	स्थिर काष्ठा resources *csiphy_res;
	स्थिर काष्ठा resources *csid_res;
	स्थिर काष्ठा resources_ispअगर *ispअगर_res;
	स्थिर काष्ठा resources *vfe_res;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (camss->version == CAMSS_8x16) अणु
		csiphy_res = csiphy_res_8x16;
		csid_res = csid_res_8x16;
		ispअगर_res = &ispअगर_res_8x16;
		vfe_res = vfe_res_8x16;
	पूर्ण अन्यथा अगर (camss->version == CAMSS_8x96) अणु
		csiphy_res = csiphy_res_8x96;
		csid_res = csid_res_8x96;
		ispअगर_res = &ispअगर_res_8x96;
		vfe_res = vfe_res_8x96;
	पूर्ण अन्यथा अगर (camss->version == CAMSS_660) अणु
		csiphy_res = csiphy_res_660;
		csid_res = csid_res_660;
		ispअगर_res = &ispअगर_res_660;
		vfe_res = vfe_res_660;
	पूर्ण  अन्यथा अगर (camss->version == CAMSS_845) अणु
		csiphy_res = csiphy_res_845;
		csid_res = csid_res_845;
		/* Titan VFEs करोn't have an ISPIF  */
		ispअगर_res = शून्य;
		vfe_res = vfe_res_845;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < camss->csiphy_num; i++) अणु
		ret = msm_csiphy_subdev_init(camss, &camss->csiphy[i],
					     &csiphy_res[i], i);
		अगर (ret < 0) अणु
			dev_err(camss->dev,
				"Failed to init csiphy%d sub-device: %d\n",
				i, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < camss->csid_num; i++) अणु
		ret = msm_csid_subdev_init(camss, &camss->csid[i],
					   &csid_res[i], i);
		अगर (ret < 0) अणु
			dev_err(camss->dev,
				"Failed to init csid%d sub-device: %d\n",
				i, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = msm_ispअगर_subdev_init(camss, ispअगर_res);
	अगर (ret < 0) अणु
		dev_err(camss->dev, "Failed to init ispif sub-device: %d\n",
		ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < camss->vfe_num; i++) अणु
		ret = msm_vfe_subdev_init(camss, &camss->vfe[i],
					  &vfe_res[i], i);
		अगर (ret < 0) अणु
			dev_err(camss->dev,
				"Fail to init vfe%d sub-device: %d\n", i, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * camss_रेजिस्टर_entities - Register subdev nodes and create links
 * @camss: CAMSS device
 *
 * Return 0 on success or a negative error code on failure
 */
अटल पूर्णांक camss_रेजिस्टर_entities(काष्ठा camss *camss)
अणु
	पूर्णांक i, j, k;
	पूर्णांक ret;

	क्रम (i = 0; i < camss->csiphy_num; i++) अणु
		ret = msm_csiphy_रेजिस्टर_entity(&camss->csiphy[i],
						 &camss->v4l2_dev);
		अगर (ret < 0) अणु
			dev_err(camss->dev,
				"Failed to register csiphy%d entity: %d\n",
				i, ret);
			जाओ err_reg_csiphy;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < camss->csid_num; i++) अणु
		ret = msm_csid_रेजिस्टर_entity(&camss->csid[i],
					       &camss->v4l2_dev);
		अगर (ret < 0) अणु
			dev_err(camss->dev,
				"Failed to register csid%d entity: %d\n",
				i, ret);
			जाओ err_reg_csid;
		पूर्ण
	पूर्ण

	ret = msm_ispअगर_रेजिस्टर_entities(camss->ispअगर,
					  &camss->v4l2_dev);
	अगर (ret < 0) अणु
		dev_err(camss->dev, "Failed to register ispif entities: %d\n",
		ret);
		जाओ err_reg_ispअगर;
	पूर्ण

	क्रम (i = 0; i < camss->vfe_num; i++) अणु
		ret = msm_vfe_रेजिस्टर_entities(&camss->vfe[i],
						&camss->v4l2_dev);
		अगर (ret < 0) अणु
			dev_err(camss->dev,
				"Failed to register vfe%d entities: %d\n",
				i, ret);
			जाओ err_reg_vfe;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < camss->csiphy_num; i++) अणु
		क्रम (j = 0; j < camss->csid_num; j++) अणु
			ret = media_create_pad_link(
				&camss->csiphy[i].subdev.entity,
				MSM_CSIPHY_PAD_SRC,
				&camss->csid[j].subdev.entity,
				MSM_CSID_PAD_SINK,
				0);
			अगर (ret < 0) अणु
				dev_err(camss->dev,
					"Failed to link %s->%s entities: %d\n",
					camss->csiphy[i].subdev.entity.name,
					camss->csid[j].subdev.entity.name,
					ret);
				जाओ err_link;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (camss->ispअगर) अणु
		क्रम (i = 0; i < camss->csid_num; i++) अणु
			क्रम (j = 0; j < camss->ispअगर->line_num; j++) अणु
				ret = media_create_pad_link(
					&camss->csid[i].subdev.entity,
					MSM_CSID_PAD_SRC,
					&camss->ispअगर->line[j].subdev.entity,
					MSM_ISPIF_PAD_SINK,
					0);
				अगर (ret < 0) अणु
					dev_err(camss->dev,
						"Failed to link %s->%s entities: %d\n",
						camss->csid[i].subdev.entity.name,
						camss->ispअगर->line[j].subdev.entity.name,
						ret);
					जाओ err_link;
				पूर्ण
			पूर्ण
		पूर्ण

		क्रम (i = 0; i < camss->ispअगर->line_num; i++)
			क्रम (k = 0; k < camss->vfe_num; k++)
				क्रम (j = 0; j < camss->vfe[k].line_num; j++) अणु
					काष्ठा v4l2_subdev *ispअगर = &camss->ispअगर->line[i].subdev;
					काष्ठा v4l2_subdev *vfe = &camss->vfe[k].line[j].subdev;

					ret = media_create_pad_link(&ispअगर->entity,
								    MSM_ISPIF_PAD_SRC,
								    &vfe->entity,
								    MSM_VFE_PAD_SINK,
								    0);
					अगर (ret < 0) अणु
						dev_err(camss->dev,
							"Failed to link %s->%s entities: %d\n",
							ispअगर->entity.name,
							vfe->entity.name,
							ret);
						जाओ err_link;
					पूर्ण
				पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < camss->csid_num; i++)
			क्रम (k = 0; k < camss->vfe_num; k++)
				क्रम (j = 0; j < camss->vfe[k].line_num; j++) अणु
					काष्ठा v4l2_subdev *csid = &camss->csid[i].subdev;
					काष्ठा v4l2_subdev *vfe = &camss->vfe[k].line[j].subdev;

					ret = media_create_pad_link(&csid->entity,
								    MSM_CSID_PAD_SRC,
								    &vfe->entity,
								    MSM_VFE_PAD_SINK,
								    0);
					अगर (ret < 0) अणु
						dev_err(camss->dev,
							"Failed to link %s->%s entities: %d\n",
							csid->entity.name,
							vfe->entity.name,
							ret);
						जाओ err_link;
					पूर्ण
				पूर्ण
	पूर्ण

	वापस 0;

err_link:
	i = camss->vfe_num;
err_reg_vfe:
	क्रम (i--; i >= 0; i--)
		msm_vfe_unरेजिस्टर_entities(&camss->vfe[i]);

err_reg_ispअगर:
	msm_ispअगर_unरेजिस्टर_entities(camss->ispअगर);

	i = camss->csid_num;
err_reg_csid:
	क्रम (i--; i >= 0; i--)
		msm_csid_unरेजिस्टर_entity(&camss->csid[i]);

	i = camss->csiphy_num;
err_reg_csiphy:
	क्रम (i--; i >= 0; i--)
		msm_csiphy_unरेजिस्टर_entity(&camss->csiphy[i]);

	वापस ret;
पूर्ण

/*
 * camss_unरेजिस्टर_entities - Unरेजिस्टर subdev nodes
 * @camss: CAMSS device
 *
 * Return 0 on success or a negative error code on failure
 */
अटल व्योम camss_unरेजिस्टर_entities(काष्ठा camss *camss)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < camss->csiphy_num; i++)
		msm_csiphy_unरेजिस्टर_entity(&camss->csiphy[i]);

	क्रम (i = 0; i < camss->csid_num; i++)
		msm_csid_unरेजिस्टर_entity(&camss->csid[i]);

	msm_ispअगर_unरेजिस्टर_entities(camss->ispअगर);

	क्रम (i = 0; i < camss->vfe_num; i++)
		msm_vfe_unरेजिस्टर_entities(&camss->vfe[i]);
पूर्ण

अटल पूर्णांक camss_subdev_notअगरier_bound(काष्ठा v4l2_async_notअगरier *async,
				       काष्ठा v4l2_subdev *subdev,
				       काष्ठा v4l2_async_subdev *asd)
अणु
	काष्ठा camss *camss = container_of(async, काष्ठा camss, notअगरier);
	काष्ठा camss_async_subdev *csd =
		container_of(asd, काष्ठा camss_async_subdev, asd);
	u8 id = csd->पूर्णांकerface.csiphy_id;
	काष्ठा csiphy_device *csiphy = &camss->csiphy[id];

	csiphy->cfg.csi2 = &csd->पूर्णांकerface.csi2;
	subdev->host_priv = csiphy;

	वापस 0;
पूर्ण

अटल पूर्णांक camss_subdev_notअगरier_complete(काष्ठा v4l2_async_notअगरier *async)
अणु
	काष्ठा camss *camss = container_of(async, काष्ठा camss, notअगरier);
	काष्ठा v4l2_device *v4l2_dev = &camss->v4l2_dev;
	काष्ठा v4l2_subdev *sd;
	पूर्णांक ret;

	list_क्रम_each_entry(sd, &v4l2_dev->subdevs, list) अणु
		अगर (sd->host_priv) अणु
			काष्ठा media_entity *sensor = &sd->entity;
			काष्ठा csiphy_device *csiphy =
					(काष्ठा csiphy_device *) sd->host_priv;
			काष्ठा media_entity *input = &csiphy->subdev.entity;
			अचिन्हित पूर्णांक i;

			क्रम (i = 0; i < sensor->num_pads; i++) अणु
				अगर (sensor->pads[i].flags & MEDIA_PAD_FL_SOURCE)
					अवरोध;
			पूर्ण
			अगर (i == sensor->num_pads) अणु
				dev_err(camss->dev,
					"No source pad in external entity\n");
				वापस -EINVAL;
			पूर्ण

			ret = media_create_pad_link(sensor, i,
				input, MSM_CSIPHY_PAD_SINK,
				MEDIA_LNK_FL_IMMUTABLE | MEDIA_LNK_FL_ENABLED);
			अगर (ret < 0) अणु
				dev_err(camss->dev,
					"Failed to link %s->%s entities: %d\n",
					sensor->name, input->name, ret);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	ret = v4l2_device_रेजिस्टर_subdev_nodes(&camss->v4l2_dev);
	अगर (ret < 0)
		वापस ret;

	वापस media_device_रेजिस्टर(&camss->media_dev);
पूर्ण

अटल स्थिर काष्ठा v4l2_async_notअगरier_operations camss_subdev_notअगरier_ops = अणु
	.bound = camss_subdev_notअगरier_bound,
	.complete = camss_subdev_notअगरier_complete,
पूर्ण;

अटल स्थिर काष्ठा media_device_ops camss_media_ops = अणु
	.link_notअगरy = v4l2_pipeline_link_notअगरy,
पूर्ण;

अटल पूर्णांक camss_configure_pd(काष्ठा camss *camss)
अणु
	पूर्णांक nbr_pm_करोमुख्यs = 0;
	पूर्णांक last_pm_करोमुख्य = 0;
	पूर्णांक i;
	पूर्णांक ret;

	अगर (camss->version == CAMSS_8x96 ||
	    camss->version == CAMSS_660)
		nbr_pm_करोमुख्यs = PM_DOMAIN_GEN1_COUNT;
	अन्यथा अगर (camss->version == CAMSS_845)
		nbr_pm_करोमुख्यs = PM_DOMAIN_GEN2_COUNT;

	क्रम (i = 0; i < nbr_pm_करोमुख्यs; i++) अणु
		camss->genpd[i] = dev_pm_करोमुख्य_attach_by_id(camss->dev, i);
		अगर (IS_ERR(camss->genpd[i])) अणु
			ret = PTR_ERR(camss->genpd[i]);
			जाओ fail_pm;
		पूर्ण

		camss->genpd_link[i] = device_link_add(camss->dev, camss->genpd[i],
						       DL_FLAG_STATELESS | DL_FLAG_PM_RUNTIME |
						       DL_FLAG_RPM_ACTIVE);
		अगर (!camss->genpd_link[i]) अणु
			dev_pm_करोमुख्य_detach(camss->genpd[i], true);
			ret = -EINVAL;
			जाओ fail_pm;
		पूर्ण

		last_pm_करोमुख्य = i;
	पूर्ण

	वापस 0;

fail_pm:
	क्रम (i = 0; i < last_pm_करोमुख्य; i++) अणु
		device_link_del(camss->genpd_link[i]);
		dev_pm_करोमुख्य_detach(camss->genpd[i], true);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * camss_probe - Probe CAMSS platक्रमm device
 * @pdev: Poपूर्णांकer to CAMSS platक्रमm device
 *
 * Return 0 on success or a negative error code on failure
 */
अटल पूर्णांक camss_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा camss *camss;
	पूर्णांक num_subdevs, ret;

	camss = kzalloc(माप(*camss), GFP_KERNEL);
	अगर (!camss)
		वापस -ENOMEM;

	atomic_set(&camss->ref_count, 0);
	camss->dev = dev;
	platक्रमm_set_drvdata(pdev, camss);

	अगर (of_device_is_compatible(dev->of_node, "qcom,msm8916-camss")) अणु
		camss->version = CAMSS_8x16;
		camss->csiphy_num = 2;
		camss->csid_num = 2;
		camss->vfe_num = 1;
	पूर्ण अन्यथा अगर (of_device_is_compatible(dev->of_node,
					   "qcom,msm8996-camss")) अणु
		camss->version = CAMSS_8x96;
		camss->csiphy_num = 3;
		camss->csid_num = 4;
		camss->vfe_num = 2;
	पूर्ण अन्यथा अगर (of_device_is_compatible(dev->of_node,
					   "qcom,sdm660-camss")) अणु
		camss->version = CAMSS_660;
		camss->csiphy_num = 3;
		camss->csid_num = 4;
		camss->vfe_num = 2;
	पूर्ण अन्यथा अगर (of_device_is_compatible(dev->of_node,
					   "qcom,sdm845-camss")) अणु
		camss->version = CAMSS_845;
		camss->csiphy_num = 4;
		camss->csid_num = 3;
		camss->vfe_num = 3;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		जाओ err_मुक्त;
	पूर्ण

	camss->csiphy = devm_kसुस्मृति(dev, camss->csiphy_num,
				     माप(*camss->csiphy), GFP_KERNEL);
	अगर (!camss->csiphy) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण

	camss->csid = devm_kसुस्मृति(dev, camss->csid_num, माप(*camss->csid),
				   GFP_KERNEL);
	अगर (!camss->csid) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण

	अगर (camss->version == CAMSS_8x16 ||
	    camss->version == CAMSS_8x96) अणु
		camss->ispअगर = devm_kसुस्मृति(dev, 1, माप(*camss->ispअगर), GFP_KERNEL);
		अगर (!camss->ispअगर) अणु
			ret = -ENOMEM;
			जाओ err_मुक्त;
		पूर्ण
	पूर्ण

	camss->vfe = devm_kसुस्मृति(dev, camss->vfe_num, माप(*camss->vfe),
				  GFP_KERNEL);
	अगर (!camss->vfe) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण

	v4l2_async_notअगरier_init(&camss->notअगरier);

	num_subdevs = camss_of_parse_ports(camss);
	अगर (num_subdevs < 0) अणु
		ret = num_subdevs;
		जाओ err_cleanup;
	पूर्ण

	ret = camss_init_subdevices(camss);
	अगर (ret < 0)
		जाओ err_cleanup;

	ret = dma_set_mask_and_coherent(dev, 0xffffffff);
	अगर (ret)
		जाओ err_cleanup;

	camss->media_dev.dev = camss->dev;
	strscpy(camss->media_dev.model, "Qualcomm Camera Subsystem",
		माप(camss->media_dev.model));
	camss->media_dev.ops = &camss_media_ops;
	media_device_init(&camss->media_dev);

	camss->v4l2_dev.mdev = &camss->media_dev;
	ret = v4l2_device_रेजिस्टर(camss->dev, &camss->v4l2_dev);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to register V4L2 device: %d\n", ret);
		जाओ err_cleanup;
	पूर्ण

	ret = camss_रेजिस्टर_entities(camss);
	अगर (ret < 0)
		जाओ err_रेजिस्टर_entities;

	अगर (num_subdevs) अणु
		camss->notअगरier.ops = &camss_subdev_notअगरier_ops;

		ret = v4l2_async_notअगरier_रेजिस्टर(&camss->v4l2_dev,
						   &camss->notअगरier);
		अगर (ret) अणु
			dev_err(dev,
				"Failed to register async subdev nodes: %d\n",
				ret);
			जाओ err_रेजिस्टर_subdevs;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = v4l2_device_रेजिस्टर_subdev_nodes(&camss->v4l2_dev);
		अगर (ret < 0) अणु
			dev_err(dev, "Failed to register subdev nodes: %d\n",
				ret);
			जाओ err_रेजिस्टर_subdevs;
		पूर्ण

		ret = media_device_रेजिस्टर(&camss->media_dev);
		अगर (ret < 0) अणु
			dev_err(dev, "Failed to register media device: %d\n",
				ret);
			जाओ err_रेजिस्टर_subdevs;
		पूर्ण
	पूर्ण

	ret = camss_configure_pd(camss);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to configure power domains: %d\n", ret);
		वापस ret;
	पूर्ण

	pm_runसमय_enable(dev);

	वापस 0;

err_रेजिस्टर_subdevs:
	camss_unरेजिस्टर_entities(camss);
err_रेजिस्टर_entities:
	v4l2_device_unरेजिस्टर(&camss->v4l2_dev);
err_cleanup:
	v4l2_async_notअगरier_cleanup(&camss->notअगरier);
err_मुक्त:
	kमुक्त(camss);

	वापस ret;
पूर्ण

व्योम camss_delete(काष्ठा camss *camss)
अणु
	पूर्णांक nbr_pm_करोमुख्यs = 0;
	पूर्णांक i;

	v4l2_device_unरेजिस्टर(&camss->v4l2_dev);
	media_device_unरेजिस्टर(&camss->media_dev);
	media_device_cleanup(&camss->media_dev);

	pm_runसमय_disable(camss->dev);

	अगर (camss->version == CAMSS_8x96 ||
	    camss->version == CAMSS_660)
		nbr_pm_करोमुख्यs = PM_DOMAIN_GEN1_COUNT;
	अन्यथा अगर (camss->version == CAMSS_845)
		nbr_pm_करोमुख्यs = PM_DOMAIN_GEN2_COUNT;

	क्रम (i = 0; i < nbr_pm_करोमुख्यs; i++) अणु
		device_link_del(camss->genpd_link[i]);
		dev_pm_करोमुख्य_detach(camss->genpd[i], true);
	पूर्ण

	kमुक्त(camss);
पूर्ण

/*
 * camss_हटाओ - Remove CAMSS platक्रमm device
 * @pdev: Poपूर्णांकer to CAMSS platक्रमm device
 *
 * Always वापसs 0.
 */
अटल पूर्णांक camss_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा camss *camss = platक्रमm_get_drvdata(pdev);

	v4l2_async_notअगरier_unरेजिस्टर(&camss->notअगरier);
	v4l2_async_notअगरier_cleanup(&camss->notअगरier);
	camss_unरेजिस्टर_entities(camss);

	अगर (atomic_पढ़ो(&camss->ref_count) == 0)
		camss_delete(camss);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id camss_dt_match[] = अणु
	अणु .compatible = "qcom,msm8916-camss" पूर्ण,
	अणु .compatible = "qcom,msm8996-camss" पूर्ण,
	अणु .compatible = "qcom,sdm660-camss" पूर्ण,
	अणु .compatible = "qcom,sdm845-camss" पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, camss_dt_match);

अटल पूर्णांक __maybe_unused camss_runसमय_suspend(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused camss_runसमय_resume(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops camss_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(camss_runसमय_suspend, camss_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver qcom_camss_driver = अणु
	.probe = camss_probe,
	.हटाओ = camss_हटाओ,
	.driver = अणु
		.name = "qcom-camss",
		.of_match_table = camss_dt_match,
		.pm = &camss_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(qcom_camss_driver);

MODULE_ALIAS("platform:qcom-camss");
MODULE_DESCRIPTION("Qualcomm Camera Subsystem driver");
MODULE_AUTHOR("Todor Tomov <todor.tomov@linaro.org>");
MODULE_LICENSE("GPL v2");
