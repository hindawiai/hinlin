<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */
#अगर_अघोषित __AMDGPU_NBIO_H__
#घोषणा __AMDGPU_NBIO_H__

/*
 * amdgpu nbio functions
 */
काष्ठा nbio_hdp_flush_reg अणु
	u32 ref_and_mask_cp0;
	u32 ref_and_mask_cp1;
	u32 ref_and_mask_cp2;
	u32 ref_and_mask_cp3;
	u32 ref_and_mask_cp4;
	u32 ref_and_mask_cp5;
	u32 ref_and_mask_cp6;
	u32 ref_and_mask_cp7;
	u32 ref_and_mask_cp8;
	u32 ref_and_mask_cp9;
	u32 ref_and_mask_sdma0;
	u32 ref_and_mask_sdma1;
	u32 ref_and_mask_sdma2;
	u32 ref_and_mask_sdma3;
	u32 ref_and_mask_sdma4;
	u32 ref_and_mask_sdma5;
	u32 ref_and_mask_sdma6;
	u32 ref_and_mask_sdma7;
पूर्ण;

काष्ठा amdgpu_nbio_ras_funcs अणु
	व्योम (*handle_ras_controller_पूर्णांकr_no_bअगरring)(काष्ठा amdgpu_device *adev);
	व्योम (*handle_ras_err_event_athub_पूर्णांकr_no_bअगरring)(काष्ठा amdgpu_device *adev);
	पूर्णांक (*init_ras_controller_पूर्णांकerrupt)(काष्ठा amdgpu_device *adev);
	पूर्णांक (*init_ras_err_event_athub_पूर्णांकerrupt)(काष्ठा amdgpu_device *adev);
	व्योम (*query_ras_error_count)(काष्ठा amdgpu_device *adev,
				      व्योम *ras_error_status);
	पूर्णांक (*ras_late_init)(काष्ठा amdgpu_device *adev);
	व्योम (*ras_fini)(काष्ठा amdgpu_device *adev);
पूर्ण;

काष्ठा amdgpu_nbio_funcs अणु
	स्थिर काष्ठा nbio_hdp_flush_reg *hdp_flush_reg;
	u32 (*get_hdp_flush_req_offset)(काष्ठा amdgpu_device *adev);
	u32 (*get_hdp_flush_करोne_offset)(काष्ठा amdgpu_device *adev);
	u32 (*get_pcie_index_offset)(काष्ठा amdgpu_device *adev);
	u32 (*get_pcie_data_offset)(काष्ठा amdgpu_device *adev);
	u32 (*get_pcie_port_index_offset)(काष्ठा amdgpu_device *adev);
	u32 (*get_pcie_port_data_offset)(काष्ठा amdgpu_device *adev);
	u32 (*get_rev_id)(काष्ठा amdgpu_device *adev);
	व्योम (*mc_access_enable)(काष्ठा amdgpu_device *adev, bool enable);
	u32 (*get_memsize)(काष्ठा amdgpu_device *adev);
	व्योम (*sdma_करोorbell_range)(काष्ठा amdgpu_device *adev, पूर्णांक instance,
			bool use_करोorbell, पूर्णांक करोorbell_index, पूर्णांक करोorbell_size);
	व्योम (*vcn_करोorbell_range)(काष्ठा amdgpu_device *adev, bool use_करोorbell,
				   पूर्णांक करोorbell_index, पूर्णांक instance);
	व्योम (*enable_करोorbell_aperture)(काष्ठा amdgpu_device *adev,
					 bool enable);
	व्योम (*enable_करोorbell_selfring_aperture)(काष्ठा amdgpu_device *adev,
						  bool enable);
	व्योम (*ih_करोorbell_range)(काष्ठा amdgpu_device *adev,
				  bool use_करोorbell, पूर्णांक करोorbell_index);
	व्योम (*enable_करोorbell_पूर्णांकerrupt)(काष्ठा amdgpu_device *adev,
					  bool enable);
	व्योम (*update_medium_grain_घड़ी_gating)(काष्ठा amdgpu_device *adev,
						 bool enable);
	व्योम (*update_medium_grain_light_sleep)(काष्ठा amdgpu_device *adev,
						bool enable);
	व्योम (*get_घड़ीgating_state)(काष्ठा amdgpu_device *adev,
				      u32 *flags);
	व्योम (*ih_control)(काष्ठा amdgpu_device *adev);
	व्योम (*init_रेजिस्टरs)(काष्ठा amdgpu_device *adev);
	व्योम (*remap_hdp_रेजिस्टरs)(काष्ठा amdgpu_device *adev);
	व्योम (*enable_aspm)(काष्ठा amdgpu_device *adev,
			    bool enable);
	व्योम (*program_aspm)(काष्ठा amdgpu_device *adev);
पूर्ण;

काष्ठा amdgpu_nbio अणु
	स्थिर काष्ठा nbio_hdp_flush_reg *hdp_flush_reg;
	काष्ठा amdgpu_irq_src ras_controller_irq;
	काष्ठा amdgpu_irq_src ras_err_event_athub_irq;
	काष्ठा ras_common_अगर *ras_अगर;
	स्थिर काष्ठा amdgpu_nbio_funcs *funcs;
	स्थिर काष्ठा amdgpu_nbio_ras_funcs *ras_funcs;
पूर्ण;

पूर्णांक amdgpu_nbio_ras_late_init(काष्ठा amdgpu_device *adev);
व्योम amdgpu_nbio_ras_fini(काष्ठा amdgpu_device *adev);
#पूर्ण_अगर
