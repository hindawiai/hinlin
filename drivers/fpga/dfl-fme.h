<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Header file क्रम FPGA Management Engine (FME) Driver
 *
 * Copyright (C) 2017-2018 Intel Corporation, Inc.
 *
 * Authors:
 *   Kang Luwei <luwei.kang@पूर्णांकel.com>
 *   Xiao Guangrong <guangrong.xiao@linux.पूर्णांकel.com>
 *   Wu Hao <hao.wu@पूर्णांकel.com>
 *   Joseph Grecco <joe.grecco@पूर्णांकel.com>
 *   Enno Luebbers <enno.luebbers@पूर्णांकel.com>
 *   Tim Whisonant <tim.whisonant@पूर्णांकel.com>
 *   Ananda Ravuri <ananda.ravuri@पूर्णांकel.com>
 *   Henry Mitchel <henry.mitchel@पूर्णांकel.com>
 */

#अगर_अघोषित __DFL_FME_H
#घोषणा __DFL_FME_H

/**
 * काष्ठा dfl_fme - dfl fme निजी data
 *
 * @mgr: FME's FPGA manager platक्रमm device.
 * @region_list: linked list of FME's FPGA regions.
 * @bridge_list: linked list of FME's FPGA bridges.
 * @pdata: fme platक्रमm device's pdata.
 */
काष्ठा dfl_fme अणु
	काष्ठा platक्रमm_device *mgr;
	काष्ठा list_head region_list;
	काष्ठा list_head bridge_list;
	काष्ठा dfl_feature_platक्रमm_data *pdata;
पूर्ण;

बाह्य स्थिर काष्ठा dfl_feature_ops fme_pr_mgmt_ops;
बाह्य स्थिर काष्ठा dfl_feature_id fme_pr_mgmt_id_table[];
बाह्य स्थिर काष्ठा dfl_feature_ops fme_global_err_ops;
बाह्य स्थिर काष्ठा dfl_feature_id fme_global_err_id_table[];
बाह्य स्थिर काष्ठा attribute_group fme_global_err_group;
बाह्य स्थिर काष्ठा dfl_feature_ops fme_perf_ops;
बाह्य स्थिर काष्ठा dfl_feature_id fme_perf_id_table[];

#पूर्ण_अगर /* __DFL_FME_H */
