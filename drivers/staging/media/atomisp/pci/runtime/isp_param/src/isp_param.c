<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
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

#समावेश "hmm.h"

#समावेश "ia_css_pipeline.h"
#समावेश "ia_css_isp_param.h"

/* Set functions क्रम parameter memory descriptors */

व्योम
ia_css_isp_param_set_mem_init(
    काष्ठा ia_css_isp_param_host_segments *mem_init,
    क्रमागत ia_css_param_class pclass,
    क्रमागत ia_css_isp_memories mem,
    अक्षर *address, माप_प्रकार size)
अणु
	mem_init->params[pclass][mem].address = address;
	mem_init->params[pclass][mem].size = (uपूर्णांक32_t)size;
पूर्ण

व्योम
ia_css_isp_param_set_css_mem_init(
    काष्ठा ia_css_isp_param_css_segments *mem_init,
    क्रमागत ia_css_param_class pclass,
    क्रमागत ia_css_isp_memories mem,
    ia_css_ptr address, माप_प्रकार size)
अणु
	mem_init->params[pclass][mem].address = address;
	mem_init->params[pclass][mem].size = (uपूर्णांक32_t)size;
पूर्ण

व्योम
ia_css_isp_param_set_isp_mem_init(
    काष्ठा ia_css_isp_param_isp_segments *mem_init,
    क्रमागत ia_css_param_class pclass,
    क्रमागत ia_css_isp_memories mem,
    u32 address, माप_प्रकार size)
अणु
	mem_init->params[pclass][mem].address = address;
	mem_init->params[pclass][mem].size = (uपूर्णांक32_t)size;
पूर्ण

/* Get functions क्रम parameter memory descriptors */
स्थिर काष्ठा ia_css_host_data *
ia_css_isp_param_get_mem_init(
    स्थिर काष्ठा ia_css_isp_param_host_segments *mem_init,
    क्रमागत ia_css_param_class pclass,
    क्रमागत ia_css_isp_memories mem)
अणु
	वापस &mem_init->params[pclass][mem];
पूर्ण

स्थिर काष्ठा ia_css_data *
ia_css_isp_param_get_css_mem_init(
    स्थिर काष्ठा ia_css_isp_param_css_segments *mem_init,
    क्रमागत ia_css_param_class pclass,
    क्रमागत ia_css_isp_memories mem)
अणु
	वापस &mem_init->params[pclass][mem];
पूर्ण

स्थिर काष्ठा ia_css_isp_data *
ia_css_isp_param_get_isp_mem_init(
    स्थिर काष्ठा ia_css_isp_param_isp_segments *mem_init,
    क्रमागत ia_css_param_class pclass,
    क्रमागत ia_css_isp_memories mem)
अणु
	वापस &mem_init->params[pclass][mem];
पूर्ण

व्योम
ia_css_init_memory_पूर्णांकerface(
    काष्ठा ia_css_isp_param_css_segments *isp_mem_अगर,
    स्थिर काष्ठा ia_css_isp_param_host_segments *mem_params,
    स्थिर काष्ठा ia_css_isp_param_css_segments *css_params)
अणु
	अचिन्हित पूर्णांक pclass, mem;

	क्रम (pclass = 0; pclass < IA_CSS_NUM_PARAM_CLASSES; pclass++) अणु
		स_रखो(isp_mem_अगर->params[pclass], 0, माप(isp_mem_अगर->params[pclass]));
		क्रम (mem = 0; mem < IA_CSS_NUM_MEMORIES; mem++) अणु
			अगर (!mem_params->params[pclass][mem].address)
				जारी;
			isp_mem_अगर->params[pclass][mem].size = mem_params->params[pclass][mem].size;
			अगर (pclass != IA_CSS_PARAM_CLASS_PARAM)
				isp_mem_अगर->params[pclass][mem].address =
				    css_params->params[pclass][mem].address;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक
ia_css_isp_param_allocate_isp_parameters(
    काष्ठा ia_css_isp_param_host_segments *mem_params,
    काष्ठा ia_css_isp_param_css_segments *css_params,
    स्थिर काष्ठा ia_css_isp_param_isp_segments *mem_initializers) अणु
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक mem, pclass;

	pclass = IA_CSS_PARAM_CLASS_PARAM;
	क्रम (mem = 0; mem < IA_CSS_NUM_MEMORIES; mem++)
	अणु
		क्रम (pclass = 0; pclass < IA_CSS_NUM_PARAM_CLASSES; pclass++) अणु
			u32 size = 0;

			अगर (mem_initializers)
				size = mem_initializers->params[pclass][mem].size;
			mem_params->params[pclass][mem].size = size;
			mem_params->params[pclass][mem].address = शून्य;
			css_params->params[pclass][mem].size = size;
			css_params->params[pclass][mem].address = 0x0;
			अगर (size) अणु
				mem_params->params[pclass][mem].address = kvसुस्मृति(1,
										   size,
										   GFP_KERNEL);
				अगर (!mem_params->params[pclass][mem].address) अणु
					err = -ENOMEM;
					जाओ cleanup;
				पूर्ण
				अगर (pclass != IA_CSS_PARAM_CLASS_PARAM) अणु
					css_params->params[pclass][mem].address = hmm_alloc(size, HMM_BO_PRIVATE, 0, शून्य, 0);
					अगर (!css_params->params[pclass][mem].address) अणु
						err = -ENOMEM;
						जाओ cleanup;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	वापस err;
cleanup:
	ia_css_isp_param_destroy_isp_parameters(mem_params, css_params);
	वापस err;
पूर्ण

व्योम
ia_css_isp_param_destroy_isp_parameters(
    काष्ठा ia_css_isp_param_host_segments *mem_params,
    काष्ठा ia_css_isp_param_css_segments *css_params)
अणु
	अचिन्हित पूर्णांक mem, pclass;

	क्रम (mem = 0; mem < IA_CSS_NUM_MEMORIES; mem++) अणु
		क्रम (pclass = 0; pclass < IA_CSS_NUM_PARAM_CLASSES; pclass++) अणु
			kvमुक्त(mem_params->params[pclass][mem].address);
			अगर (css_params->params[pclass][mem].address)
				hmm_मुक्त(css_params->params[pclass][mem].address);
			mem_params->params[pclass][mem].address = शून्य;
			css_params->params[pclass][mem].address = 0x0;
		पूर्ण
	पूर्ण
पूर्ण

व्योम
ia_css_isp_param_load_fw_params(
    स्थिर अक्षर *fw,
    जोड़ ia_css_all_memory_offsets *mem_offsets,
    स्थिर काष्ठा ia_css_isp_param_memory_offsets *memory_offsets,
    bool init)
अणु
	अचिन्हित पूर्णांक pclass;

	क्रम (pclass = 0; pclass < IA_CSS_NUM_PARAM_CLASSES; pclass++) अणु
		mem_offsets->array[pclass].ptr = शून्य;
		अगर (init)
			mem_offsets->array[pclass].ptr = (व्योम *)(fw + memory_offsets->offsets[pclass]);
	पूर्ण
पूर्ण

पूर्णांक
ia_css_isp_param_copy_isp_mem_अगर_to_ddr(
    काष्ठा ia_css_isp_param_css_segments *ddr,
    स्थिर काष्ठा ia_css_isp_param_host_segments *host,
    क्रमागत ia_css_param_class pclass) अणु
	अचिन्हित पूर्णांक mem;

	क्रम (mem = 0; mem < N_IA_CSS_ISP_MEMORIES; mem++)
	अणु
		माप_प्रकार       size	  = host->params[pclass][mem].size;
		ia_css_ptr ddr_mem_ptr  = ddr->params[pclass][mem].address;
		अक्षर	    *host_mem_ptr = host->params[pclass][mem].address;

		अगर (size != ddr->params[pclass][mem].size)
			वापस -EINVAL;
		अगर (!size)
			जारी;
		hmm_store(ddr_mem_ptr, host_mem_ptr, size);
	पूर्ण
	वापस 0;
पूर्ण

व्योम
ia_css_isp_param_enable_pipeline(
    स्थिर काष्ठा ia_css_isp_param_host_segments *mem_params)
अणु
	/* By protocol b0 of the mandatory uपूर्णांक32_t first field of the
	   input parameter is a disable bit*/
	लघु dmem_offset = 0;

	अगर (mem_params->params[IA_CSS_PARAM_CLASS_PARAM][IA_CSS_ISP_DMEM0].size == 0)
		वापस;

	*(uपूर्णांक32_t *)
	&mem_params->params[IA_CSS_PARAM_CLASS_PARAM][IA_CSS_ISP_DMEM0].address[dmem_offset]
	    = 0x0;
पूर्ण
