<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2010 - 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#अगर_अघोषित _IA_CSS_ISP_PARAM_H_
#घोषणा _IA_CSS_ISP_PARAM_H_

#समावेश <ia_css_err.h>
#समावेश "ia_css_isp_param_types.h"

/* Set functions क्रम parameter memory descriptors */
व्योम
ia_css_isp_param_set_mem_init(
    काष्ठा ia_css_isp_param_host_segments *mem_init,
    क्रमागत ia_css_param_class pclass,
    क्रमागत ia_css_isp_memories mem,
    अक्षर *address, माप_प्रकार size);

व्योम
ia_css_isp_param_set_css_mem_init(
    काष्ठा ia_css_isp_param_css_segments *mem_init,
    क्रमागत ia_css_param_class pclass,
    क्रमागत ia_css_isp_memories mem,
    ia_css_ptr address, माप_प्रकार size);

व्योम
ia_css_isp_param_set_isp_mem_init(
    काष्ठा ia_css_isp_param_isp_segments *mem_init,
    क्रमागत ia_css_param_class pclass,
    क्रमागत ia_css_isp_memories mem,
    u32 address, माप_प्रकार size);

/* Get functions क्रम parameter memory descriptors */
स्थिर काष्ठा ia_css_host_data *
ia_css_isp_param_get_mem_init(
    स्थिर काष्ठा ia_css_isp_param_host_segments *mem_init,
    क्रमागत ia_css_param_class pclass,
    क्रमागत ia_css_isp_memories mem);

स्थिर काष्ठा ia_css_data *
ia_css_isp_param_get_css_mem_init(
    स्थिर काष्ठा ia_css_isp_param_css_segments *mem_init,
    क्रमागत ia_css_param_class pclass,
    क्रमागत ia_css_isp_memories mem);

स्थिर काष्ठा ia_css_isp_data *
ia_css_isp_param_get_isp_mem_init(
    स्थिर काष्ठा ia_css_isp_param_isp_segments *mem_init,
    क्रमागत ia_css_param_class pclass,
    क्रमागत ia_css_isp_memories mem);

/* Initialize the memory पूर्णांकerface sizes and addresses */
व्योम
ia_css_init_memory_पूर्णांकerface(
    काष्ठा ia_css_isp_param_css_segments *isp_mem_अगर,
    स्थिर काष्ठा ia_css_isp_param_host_segments *mem_params,
    स्थिर काष्ठा ia_css_isp_param_css_segments *css_params);

/* Allocate memory parameters */
पूर्णांक
ia_css_isp_param_allocate_isp_parameters(
    काष्ठा ia_css_isp_param_host_segments *mem_params,
    काष्ठा ia_css_isp_param_css_segments *css_params,
    स्थिर काष्ठा ia_css_isp_param_isp_segments *mem_initializers);

/* Destroy memory parameters */
व्योम
ia_css_isp_param_destroy_isp_parameters(
    काष्ठा ia_css_isp_param_host_segments *mem_params,
    काष्ठा ia_css_isp_param_css_segments *css_params);

/* Load fw parameters */
व्योम
ia_css_isp_param_load_fw_params(
    स्थिर अक्षर *fw,
    जोड़ ia_css_all_memory_offsets *mem_offsets,
    स्थिर काष्ठा ia_css_isp_param_memory_offsets *memory_offsets,
    bool init);

/* Copy host parameter images to ddr */
पूर्णांक
ia_css_isp_param_copy_isp_mem_अगर_to_ddr(
    काष्ठा ia_css_isp_param_css_segments *ddr,
    स्थिर काष्ठा ia_css_isp_param_host_segments *host,
    क्रमागत ia_css_param_class pclass);

/* Enable a pipeline by setting the control field in the isp dmem parameters */
व्योम
ia_css_isp_param_enable_pipeline(
    स्थिर काष्ठा ia_css_isp_param_host_segments *mem_params);

#पूर्ण_अगर /* _IA_CSS_ISP_PARAM_H_ */
