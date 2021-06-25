<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2015, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित __MSM_DSI_CFG_H__
#घोषणा __MSM_DSI_CFG_H__

#समावेश "dsi.h"

#घोषणा MSM_DSI_VER_MAJOR_V2	0x02
#घोषणा MSM_DSI_VER_MAJOR_6G	0x03
#घोषणा MSM_DSI_6G_VER_MINOR_V1_0	0x10000000
#घोषणा MSM_DSI_6G_VER_MINOR_V1_1	0x10010000
#घोषणा MSM_DSI_6G_VER_MINOR_V1_1_1	0x10010001
#घोषणा MSM_DSI_6G_VER_MINOR_V1_2	0x10020000
#घोषणा MSM_DSI_6G_VER_MINOR_V1_3	0x10030000
#घोषणा MSM_DSI_6G_VER_MINOR_V1_3_1	0x10030001
#घोषणा MSM_DSI_6G_VER_MINOR_V1_4_1	0x10040001
#घोषणा MSM_DSI_6G_VER_MINOR_V1_4_2	0x10040002
#घोषणा MSM_DSI_6G_VER_MINOR_V2_1_0	0x20010000
#घोषणा MSM_DSI_6G_VER_MINOR_V2_2_0	0x20000000
#घोषणा MSM_DSI_6G_VER_MINOR_V2_2_1	0x20020001
#घोषणा MSM_DSI_6G_VER_MINOR_V2_3_0	0x20030000
#घोषणा MSM_DSI_6G_VER_MINOR_V2_4_0	0x20040000
#घोषणा MSM_DSI_6G_VER_MINOR_V2_4_1	0x20040001

#घोषणा MSM_DSI_V2_VER_MINOR_8064	0x0

#घोषणा DSI_6G_REG_SHIFT	4

काष्ठा msm_dsi_config अणु
	u32 io_offset;
	काष्ठा dsi_reg_config reg_cfg;
	स्थिर अक्षर * स्थिर *bus_clk_names;
	स्थिर पूर्णांक num_bus_clks;
	स्थिर resource_माप_प्रकार io_start[DSI_MAX];
	स्थिर पूर्णांक num_dsi;
पूर्ण;

काष्ठा msm_dsi_host_cfg_ops अणु
	पूर्णांक (*link_clk_set_rate)(काष्ठा msm_dsi_host *msm_host);
	पूर्णांक (*link_clk_enable)(काष्ठा msm_dsi_host *msm_host);
	व्योम (*link_clk_disable)(काष्ठा msm_dsi_host *msm_host);
	पूर्णांक (*clk_init_ver)(काष्ठा msm_dsi_host *msm_host);
	पूर्णांक (*tx_buf_alloc)(काष्ठा msm_dsi_host *msm_host, पूर्णांक size);
	व्योम* (*tx_buf_get)(काष्ठा msm_dsi_host *msm_host);
	व्योम (*tx_buf_put)(काष्ठा msm_dsi_host *msm_host);
	पूर्णांक (*dma_base_get)(काष्ठा msm_dsi_host *msm_host, uपूर्णांक64_t *iova);
	पूर्णांक (*calc_clk_rate)(काष्ठा msm_dsi_host *msm_host, bool is_dual_dsi);
पूर्ण;

काष्ठा msm_dsi_cfg_handler अणु
	u32 major;
	u32 minor;
	स्थिर काष्ठा msm_dsi_config *cfg;
	स्थिर काष्ठा msm_dsi_host_cfg_ops *ops;
पूर्ण;

स्थिर काष्ठा msm_dsi_cfg_handler *msm_dsi_cfg_get(u32 major, u32 minor);

#पूर्ण_अगर /* __MSM_DSI_CFG_H__ */

