<शैली गुरु>
/*
 * Copyright 2017 Advanced Micro Devices, Inc.
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
 * Authors: AMD
 *
 */

#समावेश "display_mode_lib.h"
#समावेश "dc_features.h"
#समावेश "dcn20/display_mode_vba_20.h"
#समावेश "dcn20/display_rq_dlg_calc_20.h"
#समावेश "dcn20/display_mode_vba_20v2.h"
#समावेश "dcn20/display_rq_dlg_calc_20v2.h"
#समावेश "dcn21/display_mode_vba_21.h"
#समावेश "dcn21/display_rq_dlg_calc_21.h"
#समावेश "dcn30/display_mode_vba_30.h"
#समावेश "dcn30/display_rq_dlg_calc_30.h"
#समावेश "dml_logger.h"

स्थिर काष्ठा dml_funcs dml20_funcs = अणु
	.validate = dml20_ModeSupportAndSystemConfigurationFull,
	.recalculate = dml20_recalculate,
	.rq_dlg_get_dlg_reg = dml20_rq_dlg_get_dlg_reg,
	.rq_dlg_get_rq_reg = dml20_rq_dlg_get_rq_reg
पूर्ण;

स्थिर काष्ठा dml_funcs dml20v2_funcs = अणु
	.validate = dml20v2_ModeSupportAndSystemConfigurationFull,
	.recalculate = dml20v2_recalculate,
	.rq_dlg_get_dlg_reg = dml20v2_rq_dlg_get_dlg_reg,
	.rq_dlg_get_rq_reg = dml20v2_rq_dlg_get_rq_reg
पूर्ण;

स्थिर काष्ठा dml_funcs dml21_funcs = अणु
        .validate = dml21_ModeSupportAndSystemConfigurationFull,
        .recalculate = dml21_recalculate,
        .rq_dlg_get_dlg_reg = dml21_rq_dlg_get_dlg_reg,
        .rq_dlg_get_rq_reg = dml21_rq_dlg_get_rq_reg
पूर्ण;

स्थिर काष्ठा dml_funcs dml30_funcs = अणु
	.validate = dml30_ModeSupportAndSystemConfigurationFull,
	.recalculate = dml30_recalculate,
	.rq_dlg_get_dlg_reg = dml30_rq_dlg_get_dlg_reg,
	.rq_dlg_get_rq_reg = dml30_rq_dlg_get_rq_reg
पूर्ण;

व्योम dml_init_instance(काष्ठा display_mode_lib *lib,
		स्थिर काष्ठा _vcs_dpi_soc_bounding_box_st *soc_bb,
		स्थिर काष्ठा _vcs_dpi_ip_params_st *ip_params,
		क्रमागत dml_project project)
अणु
	lib->soc = *soc_bb;
	lib->ip = *ip_params;
	lib->project = project;
	चयन (project) अणु
	हाल DML_PROJECT_NAVI10:
		lib->funcs = dml20_funcs;
		अवरोध;
	हाल DML_PROJECT_NAVI10v2:
		lib->funcs = dml20v2_funcs;
		अवरोध;
        हाल DML_PROJECT_DCN21:
                lib->funcs = dml21_funcs;
                अवरोध;
	हाल DML_PROJECT_DCN30:
		lib->funcs = dml30_funcs;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

स्थिर अक्षर *dml_get_status_message(क्रमागत dm_validation_status status)
अणु
	चयन (status) अणु
	हाल DML_VALIDATION_OK:                   वापस "Validation OK";
	हाल DML_FAIL_SCALE_RATIO_TAP:            वापस "Scale ratio/tap";
	हाल DML_FAIL_SOURCE_PIXEL_FORMAT:        वापस "Source pixel format";
	हाल DML_FAIL_VIEWPORT_SIZE:              वापस "Viewport size";
	हाल DML_FAIL_TOTAL_V_ACTIVE_BW:          वापस "Total vertical active bandwidth";
	हाल DML_FAIL_DIO_SUPPORT:                वापस "DIO support";
	हाल DML_FAIL_NOT_ENOUGH_DSC:             वापस "Not enough DSC Units";
	हाल DML_FAIL_DSC_CLK_REQUIRED:           वापस "DSC clock required";
	हाल DML_FAIL_URGENT_LATENCY:             वापस "Urgent latency";
	हाल DML_FAIL_REORDERING_BUFFER:          वापस "Re-ordering buffer";
	हाल DML_FAIL_DISPCLK_DPPCLK:             वापस "Dispclk and Dppclk";
	हाल DML_FAIL_TOTAL_AVAILABLE_PIPES:      वापस "Total available pipes";
	हाल DML_FAIL_NUM_OTG:                    वापस "Number of OTG";
	हाल DML_FAIL_WRITEBACK_MODE:             वापस "Writeback mode";
	हाल DML_FAIL_WRITEBACK_LATENCY:          वापस "Writeback latency";
	हाल DML_FAIL_WRITEBACK_SCALE_RATIO_TAP:  वापस "Writeback scale ratio/tap";
	हाल DML_FAIL_CURSOR_SUPPORT:             वापस "Cursor support";
	हाल DML_FAIL_PITCH_SUPPORT:              वापस "Pitch support";
	हाल DML_FAIL_PTE_BUFFER_SIZE:            वापस "PTE buffer size";
	हाल DML_FAIL_DSC_INPUT_BPC:              वापस "DSC input bpc";
	हाल DML_FAIL_PREFETCH_SUPPORT:           वापस "Prefetch support";
	हाल DML_FAIL_V_RATIO_PREFETCH:           वापस "Vertical ratio prefetch";
	शेष:                                  वापस "Unknown Status";
	पूर्ण
पूर्ण

व्योम dml_log_pipe_params(
		काष्ठा display_mode_lib *mode_lib,
		display_e2e_pipe_params_st *pipes,
		पूर्णांक pipe_cnt)
अणु
	display_pipe_source_params_st *pipe_src;
	display_pipe_dest_params_st   *pipe_dest;
	scaler_ratio_depth_st         *scale_ratio_depth;
	scaler_taps_st                *scale_taps;
	display_output_params_st      *करोut;
	display_घड़ीs_and_cfg_st     *clks_cfg;
	पूर्णांक i;

	क्रम (i = 0; i < pipe_cnt; i++) अणु
		pipe_src = &(pipes[i].pipe.src);
		pipe_dest = &(pipes[i].pipe.dest);
		scale_ratio_depth = &(pipes[i].pipe.scale_ratio_depth);
		scale_taps = &(pipes[i].pipe.scale_taps);
		करोut = &(pipes[i].करोut);
		clks_cfg = &(pipes[i].clks_cfg);

		dml_prपूर्णांक("DML PARAMS: =====================================\n");
		dml_prपूर्णांक("DML PARAMS: PIPE [%d] SOURCE PARAMS:\n", i);
		dml_prपूर्णांक("DML PARAMS:     source_format              = %d\n", pipe_src->source_क्रमmat);
		dml_prपूर्णांक("DML PARAMS:     dcc                        = %d\n", pipe_src->dcc);
		dml_prपूर्णांक("DML PARAMS:     dcc_rate                   = %d\n", pipe_src->dcc_rate);
		dml_prपूर्णांक("DML PARAMS:     dcc_use_global             = %d\n", pipe_src->dcc_use_global);
		dml_prपूर्णांक("DML PARAMS:     vm                         = %d\n", pipe_src->vm);
		dml_prपूर्णांक("DML PARAMS:     gpuvm                      = %d\n", pipe_src->gpuvm);
		dml_prपूर्णांक("DML PARAMS:     hostvm                     = %d\n", pipe_src->hostvm);
		dml_prपूर्णांक("DML PARAMS:     gpuvm_levels_force_en      = %d\n", pipe_src->gpuvm_levels_क्रमce_en);
		dml_prपूर्णांक("DML PARAMS:     gpuvm_levels_force         = %d\n", pipe_src->gpuvm_levels_क्रमce);
		dml_prपूर्णांक("DML PARAMS:     source_scan                = %d\n", pipe_src->source_scan);
		dml_prपूर्णांक("DML PARAMS:     sw_mode                    = %d\n", pipe_src->sw_mode);
		dml_prपूर्णांक("DML PARAMS:     macro_tile_size            = %d\n", pipe_src->macro_tile_size);
		dml_prपूर्णांक("DML PARAMS:     viewport_width             = %d\n", pipe_src->viewport_width);
		dml_prपूर्णांक("DML PARAMS:     viewport_height            = %d\n", pipe_src->viewport_height);
		dml_prपूर्णांक("DML PARAMS:     viewport_y_y               = %d\n", pipe_src->viewport_y_y);
		dml_prपूर्णांक("DML PARAMS:     viewport_y_c               = %d\n", pipe_src->viewport_y_c);
		dml_prपूर्णांक("DML PARAMS:     viewport_width_c           = %d\n", pipe_src->viewport_width_c);
		dml_prपूर्णांक("DML PARAMS:     viewport_height_c          = %d\n", pipe_src->viewport_height_c);
		dml_prपूर्णांक("DML PARAMS:     data_pitch                 = %d\n", pipe_src->data_pitch);
		dml_prपूर्णांक("DML PARAMS:     data_pitch_c               = %d\n", pipe_src->data_pitch_c);
		dml_prपूर्णांक("DML PARAMS:     meta_pitch                 = %d\n", pipe_src->meta_pitch);
		dml_prपूर्णांक("DML PARAMS:     meta_pitch_c               = %d\n", pipe_src->meta_pitch_c);
		dml_prपूर्णांक("DML PARAMS:     cur0_src_width             = %d\n", pipe_src->cur0_src_width);
		dml_prपूर्णांक("DML PARAMS:     cur0_bpp                   = %d\n", pipe_src->cur0_bpp);
		dml_prपूर्णांक("DML PARAMS:     cur1_src_width             = %d\n", pipe_src->cur1_src_width);
		dml_prपूर्णांक("DML PARAMS:     cur1_bpp                   = %d\n", pipe_src->cur1_bpp);
		dml_prपूर्णांक("DML PARAMS:     num_cursors                = %d\n", pipe_src->num_cursors);
		dml_prपूर्णांक("DML PARAMS:     is_hsplit                  = %d\n", pipe_src->is_hsplit);
		dml_prपूर्णांक("DML PARAMS:     hsplit_grp                 = %d\n", pipe_src->hsplit_grp);
		dml_prपूर्णांक("DML PARAMS:     dynamic_metadata_enable    = %d\n", pipe_src->dynamic_metadata_enable);
		dml_prपूर्णांक("DML PARAMS:     dmdata_lines_before_active = %d\n", pipe_src->dynamic_metadata_lines_beक्रमe_active);
		dml_prपूर्णांक("DML PARAMS:     dmdata_xmit_bytes          = %d\n", pipe_src->dynamic_metadata_xmit_bytes);
		dml_prपूर्णांक("DML PARAMS:     immediate_flip             = %d\n", pipe_src->immediate_flip);
		dml_prपूर्णांक("DML PARAMS:     v_total_min                = %d\n", pipe_src->v_total_min);
		dml_prपूर्णांक("DML PARAMS:     v_total_max                = %d\n", pipe_src->v_total_max);
		dml_prपूर्णांक("DML PARAMS: =====================================\n");

		dml_prपूर्णांक("DML PARAMS: PIPE [%d] DESTINATION PARAMS:\n", i);
		dml_prपूर्णांक("DML PARAMS:     recout_width               = %d\n", pipe_dest->recout_width);
		dml_prपूर्णांक("DML PARAMS:     recout_height              = %d\n", pipe_dest->recout_height);
		dml_prपूर्णांक("DML PARAMS:     full_recout_width          = %d\n", pipe_dest->full_recout_width);
		dml_prपूर्णांक("DML PARAMS:     full_recout_height         = %d\n", pipe_dest->full_recout_height);
		dml_prपूर्णांक("DML PARAMS:     hblank_start               = %d\n", pipe_dest->hblank_start);
		dml_prपूर्णांक("DML PARAMS:     hblank_end                 = %d\n", pipe_dest->hblank_end);
		dml_prपूर्णांक("DML PARAMS:     vblank_start               = %d\n", pipe_dest->vblank_start);
		dml_prपूर्णांक("DML PARAMS:     vblank_end                 = %d\n", pipe_dest->vblank_end);
		dml_prपूर्णांक("DML PARAMS:     htotal                     = %d\n", pipe_dest->htotal);
		dml_prपूर्णांक("DML PARAMS:     vtotal                     = %d\n", pipe_dest->vtotal);
		dml_prपूर्णांक("DML PARAMS:     vactive                    = %d\n", pipe_dest->vactive);
		dml_prपूर्णांक("DML PARAMS:     hactive                    = %d\n", pipe_dest->hactive);
		dml_prपूर्णांक("DML PARAMS:     vstartup_start             = %d\n", pipe_dest->vstartup_start);
		dml_prपूर्णांक("DML PARAMS:     vupdate_offset             = %d\n", pipe_dest->vupdate_offset);
		dml_prपूर्णांक("DML PARAMS:     vupdate_width              = %d\n", pipe_dest->vupdate_width);
		dml_prपूर्णांक("DML PARAMS:     vready_offset              = %d\n", pipe_dest->vपढ़ोy_offset);
		dml_prपूर्णांक("DML PARAMS:     interlaced                 = %d\n", pipe_dest->पूर्णांकerlaced);
		dml_prपूर्णांक("DML PARAMS:     pixel_rate_mhz             = %3.2f\n", pipe_dest->pixel_rate_mhz);
		dml_prपूर्णांक("DML PARAMS:     sync_vblank_all_planes     = %d\n", pipe_dest->synchronized_vblank_all_planes);
		dml_prपूर्णांक("DML PARAMS:     otg_inst                   = %d\n", pipe_dest->otg_inst);
		dml_prपूर्णांक("DML PARAMS:     odm_combine                = %d\n", pipe_dest->odm_combine);
		dml_prपूर्णांक("DML PARAMS:     use_maximum_vstartup       = %d\n", pipe_dest->use_maximum_vstartup);
		dml_prपूर्णांक("DML PARAMS:     vtotal_max                 = %d\n", pipe_dest->vtotal_max);
		dml_prपूर्णांक("DML PARAMS:     vtotal_min                 = %d\n", pipe_dest->vtotal_min);
		dml_prपूर्णांक("DML PARAMS: =====================================\n");

		dml_prपूर्णांक("DML PARAMS: PIPE [%d] SCALER PARAMS:\n", i);
		dml_prपूर्णांक("DML PARAMS:     hscl_ratio                 = %3.4f\n", scale_ratio_depth->hscl_ratio);
		dml_prपूर्णांक("DML PARAMS:     vscl_ratio                 = %3.4f\n", scale_ratio_depth->vscl_ratio);
		dml_prपूर्णांक("DML PARAMS:     hscl_ratio_c               = %3.4f\n", scale_ratio_depth->hscl_ratio_c);
		dml_prपूर्णांक("DML PARAMS:     vscl_ratio_c               = %3.4f\n", scale_ratio_depth->vscl_ratio_c);
		dml_prपूर्णांक("DML PARAMS:     vinit                      = %3.4f\n", scale_ratio_depth->vinit);
		dml_prपूर्णांक("DML PARAMS:     vinit_c                    = %3.4f\n", scale_ratio_depth->vinit_c);
		dml_prपूर्णांक("DML PARAMS:     vinit_bot                  = %3.4f\n", scale_ratio_depth->vinit_bot);
		dml_prपूर्णांक("DML PARAMS:     vinit_bot_c                = %3.4f\n", scale_ratio_depth->vinit_bot_c);
		dml_prपूर्णांक("DML PARAMS:     lb_depth                   = %d\n", scale_ratio_depth->lb_depth);
		dml_prपूर्णांक("DML PARAMS:     scl_enable                 = %d\n", scale_ratio_depth->scl_enable);
		dml_prपूर्णांक("DML PARAMS:     htaps                      = %d\n", scale_taps->htaps);
		dml_prपूर्णांक("DML PARAMS:     vtaps                      = %d\n", scale_taps->vtaps);
		dml_prपूर्णांक("DML PARAMS:     htaps_c                    = %d\n", scale_taps->htaps_c);
		dml_prपूर्णांक("DML PARAMS:     vtaps_c                    = %d\n", scale_taps->vtaps_c);
		dml_prपूर्णांक("DML PARAMS: =====================================\n");

		dml_prपूर्णांक("DML PARAMS: PIPE [%d] DISPLAY OUTPUT PARAMS:\n", i);
		dml_prपूर्णांक("DML PARAMS:     output_type                = %d\n", करोut->output_type);
		dml_prपूर्णांक("DML PARAMS:     output_format              = %d\n", करोut->output_क्रमmat);
		dml_prपूर्णांक("DML PARAMS:     dsc_input_bpc              = %d\n", करोut->dsc_input_bpc);
		dml_prपूर्णांक("DML PARAMS:     output_bpp                 = %3.4f\n", करोut->output_bpp);
		dml_prपूर्णांक("DML PARAMS:     dp_lanes                   = %d\n", करोut->dp_lanes);
		dml_prपूर्णांक("DML PARAMS:     dsc_enable                 = %d\n", करोut->dsc_enable);
		dml_prपूर्णांक("DML PARAMS:     dsc_slices                 = %d\n", करोut->dsc_slices);
		dml_prपूर्णांक("DML PARAMS:     wb_enable                  = %d\n", करोut->wb_enable);
		dml_prपूर्णांक("DML PARAMS:     num_active_wb              = %d\n", करोut->num_active_wb);
		dml_prपूर्णांक("DML PARAMS: =====================================\n");

		dml_prपूर्णांक("DML PARAMS: PIPE [%d] CLOCK CONFIG PARAMS:\n", i);
		dml_prपूर्णांक("DML PARAMS:     voltage                    = %d\n", clks_cfg->voltage);
		dml_prपूर्णांक("DML PARAMS:     dppclk_mhz                 = %3.2f\n", clks_cfg->dppclk_mhz);
		dml_prपूर्णांक("DML PARAMS:     refclk_mhz                 = %3.2f\n", clks_cfg->refclk_mhz);
		dml_prपूर्णांक("DML PARAMS:     dispclk_mhz                = %3.2f\n", clks_cfg->dispclk_mhz);
		dml_prपूर्णांक("DML PARAMS:     dcfclk_mhz                 = %3.2f\n", clks_cfg->dcfclk_mhz);
		dml_prपूर्णांक("DML PARAMS:     socclk_mhz                 = %3.2f\n", clks_cfg->socclk_mhz);
		dml_prपूर्णांक("DML PARAMS: =====================================\n");
	पूर्ण
पूर्ण

व्योम dml_log_mode_support_params(काष्ठा display_mode_lib *mode_lib)
अणु
	पूर्णांक i;

	क्रम (i = mode_lib->vba.soc.num_states; i >= 0; i--) अणु
		dml_prपूर्णांक("DML SUPPORT: ===============================================\n");
		dml_prपूर्णांक("DML SUPPORT: Voltage State %d\n", i);
		dml_prपूर्णांक("DML SUPPORT:     Mode Supported              : %s\n", mode_lib->vba.ModeSupport[i][0] ? "Supported" : "NOT Supported");
		dml_prपूर्णांक("DML SUPPORT:     Mode Supported (pipe split) : %s\n", mode_lib->vba.ModeSupport[i][1] ? "Supported" : "NOT Supported");
		dml_prपूर्णांक("DML SUPPORT:     Scale Ratio And Taps                : %s\n", mode_lib->vba.ScaleRatioAndTapsSupport ? "Supported" : "NOT Supported");
		dml_prपूर्णांक("DML SUPPORT:     Source Format Pixel And Scan        : %s\n", mode_lib->vba.SourceFormatPixelAndScanSupport ? "Supported" : "NOT Supported");
		dml_prपूर्णांक("DML SUPPORT:     Viewport Size                       : [%s, %s]\n", mode_lib->vba.ViewportSizeSupport[i][0] ? "Supported" : "NOT Supported", mode_lib->vba.ViewportSizeSupport[i][1] ? "Supported" : "NOT Supported");
		dml_prपूर्णांक("DML SUPPORT:     DIO Support                         : %s\n", mode_lib->vba.DIOSupport[i] ? "Supported" : "NOT Supported");
		dml_prपूर्णांक("DML SUPPORT:     ODM Combine 4To1 Support Check      : %s\n", mode_lib->vba.ODMCombine4To1SupportCheckOK[i] ? "Supported" : "NOT Supported");
		dml_prपूर्णांक("DML SUPPORT:     DSC Units                           : %s\n", mode_lib->vba.NotEnoughDSCUnits[i] ? "Not Supported" : "Supported");
		dml_prपूर्णांक("DML SUPPORT:     DSCCLK Required                     : %s\n", mode_lib->vba.DSCCLKRequiredMoreThanSupported[i] ? "Not Supported" : "Supported");
		dml_prपूर्णांक("DML SUPPORT:     DTBCLK Required                     : %s\n", mode_lib->vba.DTBCLKRequiredMoreThanSupported[i] ? "Not Supported" : "Supported");
		dml_prपूर्णांक("DML SUPPORT:     Re-ordering Buffer                  : [%s, %s]\n", mode_lib->vba.ROBSupport[i][0] ? "Supported" : "NOT Supported", mode_lib->vba.ROBSupport[i][1] ? "Supported" : "NOT Supported");
		dml_prपूर्णांक("DML SUPPORT:     DISPCLK and DPPCLK                  : [%s, %s]\n", mode_lib->vba.DISPCLK_DPPCLK_Support[i][0] ? "Supported" : "NOT Supported", mode_lib->vba.DISPCLK_DPPCLK_Support[i][1] ? "Supported" : "NOT Supported");
		dml_prपूर्णांक("DML SUPPORT:     Total Available Pipes               : [%s, %s]\n", mode_lib->vba.TotalAvailablePipesSupport[i][0] ? "Supported" : "NOT Supported", mode_lib->vba.TotalAvailablePipesSupport[i][1] ? "Supported" : "NOT Supported");
		dml_prपूर्णांक("DML SUPPORT:     Writeback Latency                   : %s\n", mode_lib->vba.WritebackLatencySupport ? "Supported" : "NOT Supported");
		dml_prपूर्णांक("DML SUPPORT:     Writeback Scale Ratio And Taps      : %s\n", mode_lib->vba.WritebackScaleRatioAndTapsSupport ? "Supported" : "NOT Supported");
		dml_prपूर्णांक("DML SUPPORT:     Cursor                              : %s\n", mode_lib->vba.CursorSupport ? "Supported" : "NOT Supported");
		dml_prपूर्णांक("DML SUPPORT:     Pitch                               : %s\n", mode_lib->vba.PitchSupport ? "Supported" : "NOT Supported");
		dml_prपूर्णांक("DML SUPPORT:     Prefetch                            : [%s, %s]\n", mode_lib->vba.PrefetchSupported[i][0] ? "Supported" : "NOT Supported", mode_lib->vba.PrefetchSupported[i][1] ? "Supported" : "NOT Supported");
		dml_prपूर्णांक("DML SUPPORT:     Dynamic Metadata                    : [%s, %s]\n", mode_lib->vba.DynamicMetadataSupported[i][0] ? "Supported" : "NOT Supported", mode_lib->vba.DynamicMetadataSupported[i][1] ? "Supported" : "NOT Supported");
		dml_prपूर्णांक("DML SUPPORT:     Total Vertical Active Bandwidth     : [%s, %s]\n", mode_lib->vba.TotalVerticalActiveBandwidthSupport[i][0] ? "Supported" : "NOT Supported", mode_lib->vba.TotalVerticalActiveBandwidthSupport[i][1] ? "Supported" : "NOT Supported");
		dml_prपूर्णांक("DML SUPPORT:     VRatio In Prefetch                  : [%s, %s]\n", mode_lib->vba.VRatioInPrefetchSupported[i][0] ? "Supported" : "NOT Supported", mode_lib->vba.VRatioInPrefetchSupported[i][1] ? "Supported" : "NOT Supported");
		dml_prपूर्णांक("DML SUPPORT:     PTE Buffer Size Not Exceeded        : [%s, %s]\n", mode_lib->vba.PTEBufferSizeNotExceeded[i][0] ? "Supported" : "NOT Supported", mode_lib->vba.PTEBufferSizeNotExceeded[i][1] ? "Supported" : "NOT Supported");
		dml_prपूर्णांक("DML SUPPORT:     DSC Input BPC                       : %s\n", mode_lib->vba.NonsupportedDSCInputBPC ? "Not Supported" : "Supported");
		dml_prपूर्णांक("DML SUPPORT:     HostVMEnable                        : %d\n", mode_lib->vba.HostVMEnable);
		dml_prपूर्णांक("DML SUPPORT:     ImmediateFlipSupportedForState      : [%d, %d]\n", mode_lib->vba.ImmediateFlipSupportedForState[i][0], mode_lib->vba.ImmediateFlipSupportedForState[i][1]);
	पूर्ण
पूर्ण
