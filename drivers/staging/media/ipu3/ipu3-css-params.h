<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2018 Intel Corporation */

#अगर_अघोषित __IPU3_PARAMS_H
#घोषणा __IPU3_PARAMS_H

पूर्णांक imgu_css_cfg_acc(काष्ठा imgu_css *css, अचिन्हित पूर्णांक pipe,
		     काष्ठा ipu3_uapi_flags *use,
		     काष्ठा imgu_abi_acc_param *acc,
		     काष्ठा imgu_abi_acc_param *acc_old,
		     काष्ठा ipu3_uapi_acc_param *acc_user);

पूर्णांक imgu_css_cfg_vmem0(काष्ठा imgu_css *css, अचिन्हित पूर्णांक pipe,
		       काष्ठा ipu3_uapi_flags *use,
		       व्योम *vmem0, व्योम *vmem0_old,
		       काष्ठा ipu3_uapi_params *user);

पूर्णांक imgu_css_cfg_dmem0(काष्ठा imgu_css *css, अचिन्हित पूर्णांक pipe,
		       काष्ठा ipu3_uapi_flags *use,
		       व्योम *dmem0, व्योम *dmem0_old,
		       काष्ठा ipu3_uapi_params *user);

व्योम imgu_css_cfg_gdc_table(काष्ठा imgu_abi_gdc_warp_param *gdc,
			    पूर्णांक frame_in_x, पूर्णांक frame_in_y,
			    पूर्णांक frame_out_x, पूर्णांक frame_out_y,
			    पूर्णांक env_w, पूर्णांक env_h);

#पूर्ण_अगर /*__IPU3_PARAMS_H */
