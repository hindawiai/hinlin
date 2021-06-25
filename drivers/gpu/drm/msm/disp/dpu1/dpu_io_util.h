<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2012, 2017-2018, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित __DPU_IO_UTIL_H__
#घोषणा __DPU_IO_UTIL_H__

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/types.h>

#घोषणा DEV_DBG(fmt, args...)   pr_debug(fmt, ##args)
#घोषणा DEV_INFO(fmt, args...)  pr_info(fmt, ##args)
#घोषणा DEV_WARN(fmt, args...)  pr_warn(fmt, ##args)
#घोषणा DEV_ERR(fmt, args...)   pr_err(fmt, ##args)

क्रमागत dss_clk_type अणु
	DSS_CLK_AHB, /* no set rate. rate controlled through rpm */
	DSS_CLK_PCLK,
पूर्ण;

काष्ठा dss_clk अणु
	काष्ठा clk *clk; /* clk handle */
	अक्षर clk_name[32];
	क्रमागत dss_clk_type type;
	अचिन्हित दीर्घ rate;
	अचिन्हित दीर्घ max_rate;
पूर्ण;

काष्ठा dss_module_घातer अणु
	अचिन्हित पूर्णांक num_clk;
	काष्ठा dss_clk *clk_config;
पूर्ण;

पूर्णांक msm_dss_get_clk(काष्ठा device *dev, काष्ठा dss_clk *clk_arry, पूर्णांक num_clk);
व्योम msm_dss_put_clk(काष्ठा dss_clk *clk_arry, पूर्णांक num_clk);
पूर्णांक msm_dss_clk_set_rate(काष्ठा dss_clk *clk_arry, पूर्णांक num_clk);
पूर्णांक msm_dss_enable_clk(काष्ठा dss_clk *clk_arry, पूर्णांक num_clk, पूर्णांक enable);
पूर्णांक msm_dss_parse_घड़ी(काष्ठा platक्रमm_device *pdev,
		काष्ठा dss_module_घातer *mp);
#पूर्ण_अगर /* __DPU_IO_UTIL_H__ */
