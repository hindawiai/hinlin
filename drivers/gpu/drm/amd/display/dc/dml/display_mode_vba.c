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
#समावेश "display_mode_vba.h"
#समावेश "dml_inline_defs.h"

/*
 * NOTE:
 *   This file is gcc-parsable HW gospel, coming straight from HW engineers.
 *
 * It करोesn't adhere to Linux kernel style and someबार will करो things in odd
 * ways. Unless there is something clearly wrong with it the code should
 * reमुख्य as-is as it provides us with a guarantee from HW that it is correct.
 */


अटल व्योम fetch_socbb_params(काष्ठा display_mode_lib *mode_lib);
अटल व्योम fetch_ip_params(काष्ठा display_mode_lib *mode_lib);
अटल व्योम fetch_pipe_params(काष्ठा display_mode_lib *mode_lib);
अटल व्योम recalculate_params(
		काष्ठा display_mode_lib *mode_lib,
		स्थिर display_e2e_pipe_params_st *pipes,
		अचिन्हित पूर्णांक num_pipes);

अटल अचिन्हित पूर्णांक CursorBppEnumToBits(क्रमागत cursor_bpp ebpp);

अचिन्हित पूर्णांक dml_get_voltage_level(
		काष्ठा display_mode_lib *mode_lib,
		स्थिर display_e2e_pipe_params_st *pipes,
		अचिन्हित पूर्णांक num_pipes)
अणु
	bool need_recalculate = स_भेद(&mode_lib->soc, &mode_lib->vba.soc, माप(mode_lib->vba.soc)) != 0
			|| स_भेद(&mode_lib->ip, &mode_lib->vba.ip, माप(mode_lib->vba.ip)) != 0
			|| num_pipes != mode_lib->vba.cache_num_pipes
			|| स_भेद(pipes, mode_lib->vba.cache_pipes,
					माप(display_e2e_pipe_params_st) * num_pipes) != 0;

	mode_lib->vba.soc = mode_lib->soc;
	mode_lib->vba.ip = mode_lib->ip;
	स_नकल(mode_lib->vba.cache_pipes, pipes, माप(*pipes) * num_pipes);
	mode_lib->vba.cache_num_pipes = num_pipes;

	अगर (need_recalculate && pipes[0].clks_cfg.dppclk_mhz != 0)
		mode_lib->funcs.recalculate(mode_lib);
	अन्यथा अणु
		fetch_socbb_params(mode_lib);
		fetch_ip_params(mode_lib);
		fetch_pipe_params(mode_lib);
		PixelClockAdjusपंचांगentForProgressiveToInterlaceUnit(mode_lib);
	पूर्ण
	mode_lib->funcs.validate(mode_lib);

	वापस mode_lib->vba.VoltageLevel;
पूर्ण

#घोषणा dml_get_attr_func(attr, var)  द्विगुन get_##attr(काष्ठा display_mode_lib *mode_lib, स्थिर display_e2e_pipe_params_st *pipes, अचिन्हित पूर्णांक num_pipes) \
अणु \
	recalculate_params(mode_lib, pipes, num_pipes); \
	वापस var; \
पूर्ण

dml_get_attr_func(clk_dcf_deepsleep, mode_lib->vba.DCFCLKDeepSleep);
dml_get_attr_func(wm_urgent, mode_lib->vba.UrgentWatermark);
dml_get_attr_func(wm_memory_trip, mode_lib->vba.UrgentLatency);
dml_get_attr_func(wm_ग_लिखोback_urgent, mode_lib->vba.WritebackUrgentWatermark);
dml_get_attr_func(wm_stutter_निकास, mode_lib->vba.StutterExitWatermark);
dml_get_attr_func(wm_stutter_enter_निकास, mode_lib->vba.StutterEnterPlusExitWatermark);
dml_get_attr_func(wm_dram_घड़ी_change, mode_lib->vba.DRAMClockChangeWatermark);
dml_get_attr_func(wm_ग_लिखोback_dram_घड़ी_change, mode_lib->vba.WritebackDRAMClockChangeWatermark);
dml_get_attr_func(stutter_efficiency, mode_lib->vba.StutterEfficiency);
dml_get_attr_func(stutter_efficiency_no_vblank, mode_lib->vba.StutterEfficiencyNotIncludingVBlank);
dml_get_attr_func(stutter_period, mode_lib->vba.StutterPeriod);
dml_get_attr_func(urgent_latency, mode_lib->vba.UrgentLatency);
dml_get_attr_func(urgent_extra_latency, mode_lib->vba.UrgentExtraLatency);
dml_get_attr_func(nonurgent_latency, mode_lib->vba.NonUrgentLatencyTolerance);
dml_get_attr_func(dram_घड़ी_change_latency, mode_lib->vba.MinActiveDRAMClockChangeLatencySupported);
dml_get_attr_func(dispclk_calculated, mode_lib->vba.DISPCLK_calculated);
dml_get_attr_func(total_data_पढ़ो_bw, mode_lib->vba.TotalDataReadBandwidth);
dml_get_attr_func(वापस_bw, mode_lib->vba.ReturnBW);
dml_get_attr_func(tcalc, mode_lib->vba.TCalc);
dml_get_attr_func(fraction_of_urgent_bandwidth, mode_lib->vba.FractionOfUrgentBandwidth);
dml_get_attr_func(fraction_of_urgent_bandwidth_imm_flip, mode_lib->vba.FractionOfUrgentBandwidthImmediateFlip);

#घोषणा dml_get_pipe_attr_func(attr, var)  द्विगुन get_##attr(काष्ठा display_mode_lib *mode_lib, स्थिर display_e2e_pipe_params_st *pipes, अचिन्हित पूर्णांक num_pipes, अचिन्हित पूर्णांक which_pipe) \
अणु\
	अचिन्हित पूर्णांक which_plane; \
	recalculate_params(mode_lib, pipes, num_pipes); \
	which_plane = mode_lib->vba.pipe_plane[which_pipe]; \
	वापस var[which_plane]; \
पूर्ण

dml_get_pipe_attr_func(dsc_delay, mode_lib->vba.DSCDelay);
dml_get_pipe_attr_func(dppclk_calculated, mode_lib->vba.DPPCLK_calculated);
dml_get_pipe_attr_func(dscclk_calculated, mode_lib->vba.DSCCLK_calculated);
dml_get_pipe_attr_func(min_ttu_vblank, mode_lib->vba.MinTTUVBlank);
dml_get_pipe_attr_func(min_ttu_vblank_in_us, mode_lib->vba.MinTTUVBlank);
dml_get_pipe_attr_func(vratio_prefetch_l, mode_lib->vba.VRatioPrefetchY);
dml_get_pipe_attr_func(vratio_prefetch_c, mode_lib->vba.VRatioPrefetchC);
dml_get_pipe_attr_func(dst_x_after_scaler, mode_lib->vba.DSTXAfterScaler);
dml_get_pipe_attr_func(dst_y_after_scaler, mode_lib->vba.DSTYAfterScaler);
dml_get_pipe_attr_func(dst_y_per_vm_vblank, mode_lib->vba.DestinationLinesToRequestVMInVBlank);
dml_get_pipe_attr_func(dst_y_per_row_vblank, mode_lib->vba.DestinationLinesToRequestRowInVBlank);
dml_get_pipe_attr_func(dst_y_prefetch, mode_lib->vba.DestinationLinesForPrefetch);
dml_get_pipe_attr_func(dst_y_per_vm_flip, mode_lib->vba.DestinationLinesToRequestVMInImmediateFlip);
dml_get_pipe_attr_func(dst_y_per_row_flip, mode_lib->vba.DestinationLinesToRequestRowInImmediateFlip);
dml_get_pipe_attr_func(refcyc_per_vm_group_vblank, mode_lib->vba.TimePerVMGroupVBlank);
dml_get_pipe_attr_func(refcyc_per_vm_group_flip, mode_lib->vba.TimePerVMGroupFlip);
dml_get_pipe_attr_func(refcyc_per_vm_req_vblank, mode_lib->vba.TimePerVMRequestVBlank);
dml_get_pipe_attr_func(refcyc_per_vm_req_flip, mode_lib->vba.TimePerVMRequestFlip);
dml_get_pipe_attr_func(refcyc_per_vm_group_vblank_in_us, mode_lib->vba.TimePerVMGroupVBlank);
dml_get_pipe_attr_func(refcyc_per_vm_group_flip_in_us, mode_lib->vba.TimePerVMGroupFlip);
dml_get_pipe_attr_func(refcyc_per_vm_req_vblank_in_us, mode_lib->vba.TimePerVMRequestVBlank);
dml_get_pipe_attr_func(refcyc_per_vm_req_flip_in_us, mode_lib->vba.TimePerVMRequestFlip);
dml_get_pipe_attr_func(refcyc_per_vm_dmdata_in_us, mode_lib->vba.Tdmdl_vm);
dml_get_pipe_attr_func(dmdata_dl_delta_in_us, mode_lib->vba.Tdmdl);
dml_get_pipe_attr_func(refcyc_per_line_delivery_l_in_us, mode_lib->vba.DisplayPipeLineDeliveryTimeLuma);
dml_get_pipe_attr_func(refcyc_per_line_delivery_c_in_us, mode_lib->vba.DisplayPipeLineDeliveryTimeChroma);
dml_get_pipe_attr_func(refcyc_per_line_delivery_pre_l_in_us, mode_lib->vba.DisplayPipeLineDeliveryTimeLumaPrefetch);
dml_get_pipe_attr_func(refcyc_per_line_delivery_pre_c_in_us, mode_lib->vba.DisplayPipeLineDeliveryTimeChromaPrefetch);
dml_get_pipe_attr_func(refcyc_per_req_delivery_l_in_us, mode_lib->vba.DisplayPipeRequestDeliveryTimeLuma);
dml_get_pipe_attr_func(refcyc_per_req_delivery_c_in_us, mode_lib->vba.DisplayPipeRequestDeliveryTimeChroma);
dml_get_pipe_attr_func(refcyc_per_req_delivery_pre_l_in_us, mode_lib->vba.DisplayPipeRequestDeliveryTimeLumaPrefetch);
dml_get_pipe_attr_func(refcyc_per_req_delivery_pre_c_in_us, mode_lib->vba.DisplayPipeRequestDeliveryTimeChromaPrefetch);
dml_get_pipe_attr_func(refcyc_per_cursor_req_delivery_in_us, mode_lib->vba.CursorRequestDeliveryTime);
dml_get_pipe_attr_func(refcyc_per_cursor_req_delivery_pre_in_us, mode_lib->vba.CursorRequestDeliveryTimePrefetch);
dml_get_pipe_attr_func(refcyc_per_meta_chunk_nom_l_in_us, mode_lib->vba.TimePerMetaChunkNominal);
dml_get_pipe_attr_func(refcyc_per_meta_chunk_nom_c_in_us, mode_lib->vba.TimePerChromaMetaChunkNominal);
dml_get_pipe_attr_func(refcyc_per_meta_chunk_vblank_l_in_us, mode_lib->vba.TimePerMetaChunkVBlank);
dml_get_pipe_attr_func(refcyc_per_meta_chunk_vblank_c_in_us, mode_lib->vba.TimePerChromaMetaChunkVBlank);
dml_get_pipe_attr_func(refcyc_per_meta_chunk_flip_l_in_us, mode_lib->vba.TimePerMetaChunkFlip);
dml_get_pipe_attr_func(refcyc_per_meta_chunk_flip_c_in_us, mode_lib->vba.TimePerChromaMetaChunkFlip);

dml_get_pipe_attr_func(vstartup, mode_lib->vba.VStartup);
dml_get_pipe_attr_func(vupdate_offset, mode_lib->vba.VUpdateOffsetPix);
dml_get_pipe_attr_func(vupdate_width, mode_lib->vba.VUpdateWidthPix);
dml_get_pipe_attr_func(vपढ़ोy_offset, mode_lib->vba.VReadyOffsetPix);

द्विगुन get_total_immediate_flip_bytes(
		काष्ठा display_mode_lib *mode_lib,
		स्थिर display_e2e_pipe_params_st *pipes,
		अचिन्हित पूर्णांक num_pipes)
अणु
	recalculate_params(mode_lib, pipes, num_pipes);
	वापस mode_lib->vba.TotImmediateFlipBytes;
पूर्ण

द्विगुन get_total_immediate_flip_bw(
		काष्ठा display_mode_lib *mode_lib,
		स्थिर display_e2e_pipe_params_st *pipes,
		अचिन्हित पूर्णांक num_pipes)
अणु
	अचिन्हित पूर्णांक k;
	द्विगुन immediate_flip_bw = 0.0;
	recalculate_params(mode_lib, pipes, num_pipes);
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k)
		immediate_flip_bw += mode_lib->vba.ImmediateFlipBW[k];
	वापस immediate_flip_bw;
पूर्ण

द्विगुन get_total_prefetch_bw(
		काष्ठा display_mode_lib *mode_lib,
		स्थिर display_e2e_pipe_params_st *pipes,
		अचिन्हित पूर्णांक num_pipes)
अणु
	अचिन्हित पूर्णांक k;
	द्विगुन total_prefetch_bw = 0.0;

	recalculate_params(mode_lib, pipes, num_pipes);
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k)
		total_prefetch_bw += mode_lib->vba.PrefetchBandwidth[k];
	वापस total_prefetch_bw;
पूर्ण

अटल व्योम fetch_socbb_params(काष्ठा display_mode_lib *mode_lib)
अणु
	soc_bounding_box_st *soc = &mode_lib->vba.soc;
	पूर्णांक i;

	// SOC Bounding Box Parameters
	mode_lib->vba.ReturnBusWidth = soc->वापस_bus_width_bytes;
	mode_lib->vba.NumberOfChannels = soc->num_chans;
	mode_lib->vba.PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelDataOnly =
			soc->pct_ideal_dram_sdp_bw_after_urgent_pixel_only; // there's always that one bastard variable that's so दीर्घ it throws everything out of alignment!
	mode_lib->vba.PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData =
			soc->pct_ideal_dram_sdp_bw_after_urgent_pixel_and_vm;
	mode_lib->vba.PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly =
			soc->pct_ideal_dram_sdp_bw_after_urgent_vm_only;
	mode_lib->vba.MaxAveragePercentOfIdealSDPPortBWDisplayCanUseInNormalSystemOperation =
			soc->max_avg_sdp_bw_use_normal_percent;
	mode_lib->vba.MaxAveragePercentOfIdealDRAMBWDisplayCanUseInNormalSystemOperation =
			soc->max_avg_dram_bw_use_normal_percent;
	mode_lib->vba.UrgentLatencyPixelDataOnly = soc->urgent_latency_pixel_data_only_us;
	mode_lib->vba.UrgentLatencyPixelMixedWithVMData = soc->urgent_latency_pixel_mixed_with_vm_data_us;
	mode_lib->vba.UrgentLatencyVMDataOnly = soc->urgent_latency_vm_data_only_us;
	mode_lib->vba.RoundTripPingLatencyCycles = soc->round_trip_ping_latency_dcfclk_cycles;
	mode_lib->vba.UrgentOutOfOrderReturnPerChannelPixelDataOnly =
			soc->urgent_out_of_order_वापस_per_channel_pixel_only_bytes;
	mode_lib->vba.UrgentOutOfOrderReturnPerChannelPixelMixedWithVMData =
			soc->urgent_out_of_order_वापस_per_channel_pixel_and_vm_bytes;
	mode_lib->vba.UrgentOutOfOrderReturnPerChannelVMDataOnly =
			soc->urgent_out_of_order_वापस_per_channel_vm_only_bytes;
	mode_lib->vba.WritebackLatency = soc->ग_लिखोback_latency_us;
	mode_lib->vba.SRExitTime = soc->sr_निकास_समय_us;
	mode_lib->vba.SREnterPlusExitTime = soc->sr_enter_plus_निकास_समय_us;
	mode_lib->vba.DRAMClockChangeLatency = soc->dram_घड़ी_change_latency_us;
	mode_lib->vba.DummyPStateCheck = soc->dram_घड़ी_change_latency_us == soc->dummy_pstate_latency_us;
	mode_lib->vba.DRAMClockChangeSupportsVActive = !soc->disable_dram_घड़ी_change_vactive_support ||
			mode_lib->vba.DummyPStateCheck;
	mode_lib->vba.AllowDramClockChangeOneDisplayVactive = soc->allow_dram_घड़ी_one_display_vactive;

	mode_lib->vba.Downspपढ़ोing = soc->करोwnspपढ़ो_percent;
	mode_lib->vba.DRAMChannelWidth = soc->dram_channel_width_bytes;   // new!
	mode_lib->vba.FabricDatapathToDCNDataReturn = soc->fabric_datapath_to_dcn_data_वापस_bytes; // new!
	mode_lib->vba.DISPCLKDPPCLKDSCCLKDownSpपढ़ोing = soc->dcn_करोwnspपढ़ो_percent;   // new
	mode_lib->vba.DISPCLKDPPCLKVCOSpeed = soc->dispclk_dppclk_vco_speed_mhz;   // new
	mode_lib->vba.VMMPageSize = soc->vmm_page_size_bytes;
	mode_lib->vba.GPUVMMinPageSize = soc->gpuvm_min_page_size_bytes / 1024;
	mode_lib->vba.HostVMMinPageSize = soc->hostvm_min_page_size_bytes / 1024;
	// Set the voltage scaling घड़ीs as the शेषs. Most of these will
	// be set to dअगरferent values by the test
	क्रम (i = 0; i < mode_lib->vba.soc.num_states; i++)
		अगर (soc->घड़ी_limits[i].state == mode_lib->vba.VoltageLevel)
			अवरोध;

	mode_lib->vba.DCFCLK = soc->घड़ी_limits[i].dcfclk_mhz;
	mode_lib->vba.SOCCLK = soc->घड़ी_limits[i].socclk_mhz;
	mode_lib->vba.DRAMSpeed = soc->घड़ी_limits[i].dram_speed_mts;
	mode_lib->vba.FabricClock = soc->घड़ी_limits[i].fabricclk_mhz;

	mode_lib->vba.XFCBusTransportTime = soc->xfc_bus_transport_समय_us;
	mode_lib->vba.XFCXBUFLatencyTolerance = soc->xfc_xbuf_latency_tolerance_us;
	mode_lib->vba.UseUrgentBurstBandwidth = soc->use_urgent_burst_bw;

	mode_lib->vba.SupportGFX7CompatibleTilingIn32bppAnd64bpp = false;
	mode_lib->vba.WritebackLumaAndChromaScalingSupported = true;
	mode_lib->vba.MaxHSCLRatio = 4;
	mode_lib->vba.MaxVSCLRatio = 4;
	mode_lib->vba.Cursor64BppSupport = true;
	क्रम (i = 0; i <= mode_lib->vba.soc.num_states; i++) अणु
		mode_lib->vba.DCFCLKPerState[i] = soc->घड़ी_limits[i].dcfclk_mhz;
		mode_lib->vba.FabricClockPerState[i] = soc->घड़ी_limits[i].fabricclk_mhz;
		mode_lib->vba.SOCCLKPerState[i] = soc->घड़ी_limits[i].socclk_mhz;
		mode_lib->vba.PHYCLKPerState[i] = soc->घड़ी_limits[i].phyclk_mhz;
		mode_lib->vba.PHYCLKD18PerState[i] = soc->घड़ी_limits[i].phyclk_d18_mhz;
		mode_lib->vba.MaxDppclk[i] = soc->घड़ी_limits[i].dppclk_mhz;
		mode_lib->vba.MaxDSCCLK[i] = soc->घड़ी_limits[i].dscclk_mhz;
		mode_lib->vba.DRAMSpeedPerState[i] = soc->घड़ी_limits[i].dram_speed_mts;
		//mode_lib->vba.DRAMSpeedPerState[i] = soc->घड़ी_limits[i].dram_speed_mhz;
		mode_lib->vba.MaxDispclk[i] = soc->घड़ी_limits[i].dispclk_mhz;
		mode_lib->vba.DTBCLKPerState[i] = soc->घड़ी_limits[i].dtbclk_mhz;
	पूर्ण

	mode_lib->vba.DoUrgentLatencyAdjusपंचांगent =
		soc->करो_urgent_latency_adjusपंचांगent;
	mode_lib->vba.UrgentLatencyAdjusपंचांगentFabricClockComponent =
		soc->urgent_latency_adjusपंचांगent_fabric_घड़ी_component_us;
	mode_lib->vba.UrgentLatencyAdjusपंचांगentFabricClockReference =
		soc->urgent_latency_adjusपंचांगent_fabric_घड़ी_reference_mhz;
पूर्ण

अटल व्योम fetch_ip_params(काष्ठा display_mode_lib *mode_lib)
अणु
	ip_params_st *ip = &mode_lib->vba.ip;

	// IP Parameters
	mode_lib->vba.UseMinimumRequiredDCFCLK = ip->use_min_dcfclk;
	mode_lib->vba.ClampMinDCFCLK = ip->clamp_min_dcfclk;
	mode_lib->vba.MaxNumDPP = ip->max_num_dpp;
	mode_lib->vba.MaxNumOTG = ip->max_num_otg;
	mode_lib->vba.MaxNumHDMIFRLOutमाला_दो = ip->max_num_hdmi_frl_outमाला_दो;
	mode_lib->vba.MaxNumWriteback = ip->max_num_wb;
	mode_lib->vba.CursorChunkSize = ip->cursor_chunk_size;
	mode_lib->vba.CursorBufferSize = ip->cursor_buffer_size;

	mode_lib->vba.MaxDCHUBToPSCLThroughput = ip->max_dchub_pscl_bw_pix_per_clk;
	mode_lib->vba.MaxPSCLToLBThroughput = ip->max_pscl_lb_bw_pix_per_clk;
	mode_lib->vba.ROBBufferSizeInKByte = ip->rob_buffer_size_kbytes;
	mode_lib->vba.DETBufferSizeInKByte = ip->det_buffer_size_kbytes;

	mode_lib->vba.PixelChunkSizeInKByte = ip->pixel_chunk_size_kbytes;
	mode_lib->vba.MetaChunkSize = ip->meta_chunk_size_kbytes;
	mode_lib->vba.MinMetaChunkSizeBytes = ip->min_meta_chunk_size_bytes;
	mode_lib->vba.WritebackChunkSize = ip->ग_लिखोback_chunk_size_kbytes;
	mode_lib->vba.LineBufferSize = ip->line_buffer_size_bits;
	mode_lib->vba.MaxLineBufferLines = ip->max_line_buffer_lines;
	mode_lib->vba.PTEBufferSizeInRequestsLuma = ip->dpte_buffer_size_in_pte_reqs_luma;
	mode_lib->vba.PTEBufferSizeInRequestsChroma = ip->dpte_buffer_size_in_pte_reqs_chroma;
	mode_lib->vba.DPPOutputBufferPixels = ip->dpp_output_buffer_pixels;
	mode_lib->vba.OPPOutputBufferLines = ip->opp_output_buffer_lines;
	mode_lib->vba.MaxHSCLRatio = ip->max_hscl_ratio;
	mode_lib->vba.MaxVSCLRatio = ip->max_vscl_ratio;
	mode_lib->vba.WritebackInterfaceLumaBufferSize = ip->ग_लिखोback_luma_buffer_size_kbytes * 1024;
	mode_lib->vba.WritebackInterfaceChromaBufferSize = ip->ग_लिखोback_chroma_buffer_size_kbytes * 1024;

	mode_lib->vba.WritebackInterfaceBufferSize = ip->ग_लिखोback_पूर्णांकerface_buffer_size_kbytes;
	mode_lib->vba.WritebackLineBufferSize = ip->ग_लिखोback_line_buffer_buffer_size;

	mode_lib->vba.WritebackChromaLineBufferWidth =
			ip->ग_लिखोback_chroma_line_buffer_width_pixels;
	mode_lib->vba.WritebackLineBufferLumaBufferSize =
			ip->ग_लिखोback_line_buffer_luma_buffer_size;
	mode_lib->vba.WritebackLineBufferChromaBufferSize =
			ip->ग_लिखोback_line_buffer_chroma_buffer_size;
	mode_lib->vba.Writeback10bpc420Supported = ip->ग_लिखोback_10bpc420_supported;
	mode_lib->vba.WritebackMaxHSCLRatio = ip->ग_लिखोback_max_hscl_ratio;
	mode_lib->vba.WritebackMaxVSCLRatio = ip->ग_लिखोback_max_vscl_ratio;
	mode_lib->vba.WritebackMinHSCLRatio = ip->ग_लिखोback_min_hscl_ratio;
	mode_lib->vba.WritebackMinVSCLRatio = ip->ग_लिखोback_min_vscl_ratio;
	mode_lib->vba.WritebackMaxHSCLTaps = ip->ग_लिखोback_max_hscl_taps;
	mode_lib->vba.WritebackMaxVSCLTaps = ip->ग_लिखोback_max_vscl_taps;
	mode_lib->vba.WritebackConfiguration = dm_normal;
	mode_lib->vba.GPUVMMaxPageTableLevels = ip->gpuvm_max_page_table_levels;
	mode_lib->vba.HostVMMaxNonCachedPageTableLevels = ip->hostvm_max_page_table_levels;
	mode_lib->vba.HostVMMaxPageTableLevels = ip->hostvm_max_page_table_levels;
	mode_lib->vba.HostVMCachedPageTableLevels = ip->hostvm_cached_page_table_levels;
	mode_lib->vba.MaxInterDCNTileRepeaters = ip->max_पूर्णांकer_dcn_tile_repeaters;
	mode_lib->vba.NumberOfDSC = ip->num_dsc;
	mode_lib->vba.ODMCapability = ip->odm_capable;
	mode_lib->vba.DISPCLKRampingMargin = ip->dispclk_ramp_margin_percent;

	mode_lib->vba.XFCSupported = ip->xfc_supported;
	mode_lib->vba.XFCFillBWOverhead = ip->xfc_fill_bw_overhead_percent;
	mode_lib->vba.XFCFillConstant = ip->xfc_fill_स्थिरant_bytes;
	mode_lib->vba.DPPCLKDelaySubtotal = ip->dppclk_delay_subtotal;
	mode_lib->vba.DPPCLKDelaySCL = ip->dppclk_delay_scl;
	mode_lib->vba.DPPCLKDelaySCLLBOnly = ip->dppclk_delay_scl_lb_only;
	mode_lib->vba.DPPCLKDelayCNVCFormater = ip->dppclk_delay_cnvc_क्रमmatter;
	mode_lib->vba.DPPCLKDelayCNVCCursor = ip->dppclk_delay_cnvc_cursor;
	mode_lib->vba.DISPCLKDelaySubtotal = ip->dispclk_delay_subtotal;
	mode_lib->vba.DynamicMetadataVMEnabled = ip->dynamic_metadata_vm_enabled;
	mode_lib->vba.ODMCombine4To1Supported = ip->odm_combine_4to1_supported;
	mode_lib->vba.ProgressiveToInterlaceUnitInOPP = ip->ptoi_supported;
	mode_lib->vba.PDEProcessingBufIn64KBReqs = ip->pde_proc_buffer_size_64k_reqs;
	mode_lib->vba.PTEGroupSize = ip->pte_group_size_bytes;
	mode_lib->vba.SupportGFX7CompatibleTilingIn32bppAnd64bpp = ip->gfx7_compat_tiling_supported;
पूर्ण

अटल व्योम fetch_pipe_params(काष्ठा display_mode_lib *mode_lib)
अणु
	display_e2e_pipe_params_st *pipes = mode_lib->vba.cache_pipes;
	ip_params_st *ip = &mode_lib->vba.ip;

	अचिन्हित पूर्णांक OTGInstPlane[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक j, k;
	bool PlaneVisited[DC__NUM_DPP__MAX];
	bool visited[DC__NUM_DPP__MAX];

	// Convert Pipes to Planes
	क्रम (k = 0; k < mode_lib->vba.cache_num_pipes; ++k)
		visited[k] = false;

	mode_lib->vba.NumberOfActivePlanes = 0;
	mode_lib->vba.ImmediateFlipSupport = false;
	mode_lib->vba.ImmediateFlipRequirement = dm_immediate_flip_not_required;
	क्रम (j = 0; j < mode_lib->vba.cache_num_pipes; ++j) अणु
		display_pipe_source_params_st *src = &pipes[j].pipe.src;
		display_pipe_dest_params_st *dst = &pipes[j].pipe.dest;
		scaler_ratio_depth_st *scl = &pipes[j].pipe.scale_ratio_depth;
		scaler_taps_st *taps = &pipes[j].pipe.scale_taps;
		display_output_params_st *करोut = &pipes[j].करोut;
		display_घड़ीs_and_cfg_st *clks = &pipes[j].clks_cfg;

		अगर (visited[j])
			जारी;
		visited[j] = true;

		mode_lib->vba.pipe_plane[j] = mode_lib->vba.NumberOfActivePlanes;

		mode_lib->vba.DPPPerPlane[mode_lib->vba.NumberOfActivePlanes] = 1;
		mode_lib->vba.SourceScan[mode_lib->vba.NumberOfActivePlanes] =
				(क्रमागत scan_direction_class) (src->source_scan);
		mode_lib->vba.ViewportWidth[mode_lib->vba.NumberOfActivePlanes] =
				src->viewport_width;
		mode_lib->vba.ViewportWidthChroma[mode_lib->vba.NumberOfActivePlanes] =
				src->viewport_width_c;
		mode_lib->vba.ViewportHeight[mode_lib->vba.NumberOfActivePlanes] =
				src->viewport_height;
		mode_lib->vba.ViewportHeightChroma[mode_lib->vba.NumberOfActivePlanes] =
				src->viewport_height_c;
		mode_lib->vba.ViewportYStartY[mode_lib->vba.NumberOfActivePlanes] =
				src->viewport_y_y;
		mode_lib->vba.ViewportYStartC[mode_lib->vba.NumberOfActivePlanes] =
				src->viewport_y_c;
		mode_lib->vba.PitchY[mode_lib->vba.NumberOfActivePlanes] = src->data_pitch;
		mode_lib->vba.SurfaceWidthY[mode_lib->vba.NumberOfActivePlanes] = src->surface_width_y;
		mode_lib->vba.SurfaceHeightY[mode_lib->vba.NumberOfActivePlanes] = src->surface_height_y;
		mode_lib->vba.PitchC[mode_lib->vba.NumberOfActivePlanes] = src->data_pitch_c;
		mode_lib->vba.SurfaceHeightC[mode_lib->vba.NumberOfActivePlanes] = src->surface_height_c;
		mode_lib->vba.SurfaceWidthC[mode_lib->vba.NumberOfActivePlanes] = src->surface_width_c;
		mode_lib->vba.DCCMetaPitchY[mode_lib->vba.NumberOfActivePlanes] = src->meta_pitch;
		mode_lib->vba.DCCMetaPitchC[mode_lib->vba.NumberOfActivePlanes] = src->meta_pitch_c;
		mode_lib->vba.HRatio[mode_lib->vba.NumberOfActivePlanes] = scl->hscl_ratio;
		mode_lib->vba.HRatioChroma[mode_lib->vba.NumberOfActivePlanes] = scl->hscl_ratio_c;
		mode_lib->vba.VRatio[mode_lib->vba.NumberOfActivePlanes] = scl->vscl_ratio;
		mode_lib->vba.VRatioChroma[mode_lib->vba.NumberOfActivePlanes] = scl->vscl_ratio_c;
		mode_lib->vba.ScalerEnabled[mode_lib->vba.NumberOfActivePlanes] = scl->scl_enable;
		mode_lib->vba.Interlace[mode_lib->vba.NumberOfActivePlanes] = dst->पूर्णांकerlaced;
		अगर (dst->पूर्णांकerlaced && !ip->ptoi_supported) अणु
			mode_lib->vba.VRatio[mode_lib->vba.NumberOfActivePlanes] *= 2.0;
			mode_lib->vba.VRatioChroma[mode_lib->vba.NumberOfActivePlanes] *= 2.0;
		पूर्ण
		mode_lib->vba.htaps[mode_lib->vba.NumberOfActivePlanes] = taps->htaps;
		mode_lib->vba.vtaps[mode_lib->vba.NumberOfActivePlanes] = taps->vtaps;
		mode_lib->vba.HTAPsChroma[mode_lib->vba.NumberOfActivePlanes] = taps->htaps_c;
		mode_lib->vba.VTAPsChroma[mode_lib->vba.NumberOfActivePlanes] = taps->vtaps_c;
		mode_lib->vba.HTotal[mode_lib->vba.NumberOfActivePlanes] = dst->htotal;
		mode_lib->vba.VTotal[mode_lib->vba.NumberOfActivePlanes] = dst->vtotal;
		mode_lib->vba.DCCEnable[mode_lib->vba.NumberOfActivePlanes] =
				src->dcc_use_global ?
						ip->dcc_supported : src->dcc && ip->dcc_supported;
		mode_lib->vba.DCCRate[mode_lib->vba.NumberOfActivePlanes] = src->dcc_rate;
		/* TODO: Needs to be set based on src->dcc_rate_luma/chroma */
		mode_lib->vba.DCCRateLuma[mode_lib->vba.NumberOfActivePlanes] = src->dcc_rate;
		mode_lib->vba.DCCRateChroma[mode_lib->vba.NumberOfActivePlanes] = src->dcc_rate_chroma;
		mode_lib->vba.SourcePixelFormat[mode_lib->vba.NumberOfActivePlanes] = (क्रमागत source_क्रमmat_class) (src->source_क्रमmat);
		mode_lib->vba.HActive[mode_lib->vba.NumberOfActivePlanes] = dst->hactive;
		mode_lib->vba.VActive[mode_lib->vba.NumberOfActivePlanes] = dst->vactive;
		mode_lib->vba.SurfaceTiling[mode_lib->vba.NumberOfActivePlanes] =
				(क्रमागत dm_swizzle_mode) (src->sw_mode);
		mode_lib->vba.ScalerRecoutWidth[mode_lib->vba.NumberOfActivePlanes] =
				dst->recout_width; // TODO: or should this be full_recout_width???...maybe only when in hsplit mode?
		mode_lib->vba.ODMCombineEnabled[mode_lib->vba.NumberOfActivePlanes] =
				dst->odm_combine;
		mode_lib->vba.OutputFormat[mode_lib->vba.NumberOfActivePlanes] =
				(क्रमागत output_क्रमmat_class) (करोut->output_क्रमmat);
		mode_lib->vba.OutputBpp[mode_lib->vba.NumberOfActivePlanes] =
				करोut->output_bpp;
		mode_lib->vba.Output[mode_lib->vba.NumberOfActivePlanes] =
				(क्रमागत output_encoder_class) (करोut->output_type);
		mode_lib->vba.skip_dio_check[mode_lib->vba.NumberOfActivePlanes] =
				करोut->is_भव;

		अगर (!करोut->dsc_enable)
			mode_lib->vba.ForcedOutputLinkBPP[mode_lib->vba.NumberOfActivePlanes] = करोut->output_bpp;
		अन्यथा
			mode_lib->vba.ForcedOutputLinkBPP[mode_lib->vba.NumberOfActivePlanes] = 0.0;

		mode_lib->vba.OutputLinkDPLanes[mode_lib->vba.NumberOfActivePlanes] =
				करोut->dp_lanes;
		/* TODO: Needs to be set based on करोut->audio.audio_sample_rate_khz/sample_layout */
		mode_lib->vba.AudioSampleRate[mode_lib->vba.NumberOfActivePlanes] =
			करोut->max_audio_sample_rate;
		mode_lib->vba.AudioSampleLayout[mode_lib->vba.NumberOfActivePlanes] =
			1;
		mode_lib->vba.DRAMClockChangeLatencyOverride = 0.0;
		mode_lib->vba.DSCEnabled[mode_lib->vba.NumberOfActivePlanes] = करोut->dsc_enable;
		mode_lib->vba.DSCEnable[mode_lib->vba.NumberOfActivePlanes] = करोut->dsc_enable;
		mode_lib->vba.NumberOfDSCSlices[mode_lib->vba.NumberOfActivePlanes] =
				करोut->dsc_slices;
		अगर (!करोut->dsc_input_bpc) अणु
			mode_lib->vba.DSCInputBitPerComponent[mode_lib->vba.NumberOfActivePlanes] =
				ip->maximum_dsc_bits_per_component;
		पूर्ण अन्यथा अणु
			mode_lib->vba.DSCInputBitPerComponent[mode_lib->vba.NumberOfActivePlanes] =
				करोut->dsc_input_bpc;
		पूर्ण
		mode_lib->vba.WritebackEnable[mode_lib->vba.NumberOfActivePlanes] = करोut->wb_enable;
		mode_lib->vba.ActiveWritebacksPerPlane[mode_lib->vba.NumberOfActivePlanes] =
				करोut->num_active_wb;
		mode_lib->vba.WritebackSourceHeight[mode_lib->vba.NumberOfActivePlanes] =
				करोut->wb.wb_src_height;
		mode_lib->vba.WritebackSourceWidth[mode_lib->vba.NumberOfActivePlanes] =
				करोut->wb.wb_src_width;
		mode_lib->vba.WritebackDestinationWidth[mode_lib->vba.NumberOfActivePlanes] =
				करोut->wb.wb_dst_width;
		mode_lib->vba.WritebackDestinationHeight[mode_lib->vba.NumberOfActivePlanes] =
				करोut->wb.wb_dst_height;
		mode_lib->vba.WritebackHRatio[mode_lib->vba.NumberOfActivePlanes] =
				करोut->wb.wb_hratio;
		mode_lib->vba.WritebackVRatio[mode_lib->vba.NumberOfActivePlanes] =
				करोut->wb.wb_vratio;
		mode_lib->vba.WritebackPixelFormat[mode_lib->vba.NumberOfActivePlanes] =
				(क्रमागत source_क्रमmat_class) (करोut->wb.wb_pixel_क्रमmat);
		mode_lib->vba.WritebackHTaps[mode_lib->vba.NumberOfActivePlanes] =
				करोut->wb.wb_htaps_luma;
		mode_lib->vba.WritebackVTaps[mode_lib->vba.NumberOfActivePlanes] =
				करोut->wb.wb_vtaps_luma;
		mode_lib->vba.WritebackLumaHTaps[mode_lib->vba.NumberOfActivePlanes] =
				करोut->wb.wb_htaps_luma;
		mode_lib->vba.WritebackLumaVTaps[mode_lib->vba.NumberOfActivePlanes] =
				करोut->wb.wb_vtaps_luma;
		mode_lib->vba.WritebackChromaHTaps[mode_lib->vba.NumberOfActivePlanes] =
				करोut->wb.wb_htaps_chroma;
		mode_lib->vba.WritebackChromaVTaps[mode_lib->vba.NumberOfActivePlanes] =
				करोut->wb.wb_vtaps_chroma;
		mode_lib->vba.WritebackHRatio[mode_lib->vba.NumberOfActivePlanes] =
				करोut->wb.wb_hratio;
		mode_lib->vba.WritebackVRatio[mode_lib->vba.NumberOfActivePlanes] =
				करोut->wb.wb_vratio;

		mode_lib->vba.DynamicMetadataEnable[mode_lib->vba.NumberOfActivePlanes] =
				src->dynamic_metadata_enable;
		mode_lib->vba.DynamicMetadataLinesBeक्रमeActiveRequired[mode_lib->vba.NumberOfActivePlanes] =
				src->dynamic_metadata_lines_beक्रमe_active;
		mode_lib->vba.DynamicMetadataTransmittedBytes[mode_lib->vba.NumberOfActivePlanes] =
				src->dynamic_metadata_xmit_bytes;

		mode_lib->vba.XFCEnabled[mode_lib->vba.NumberOfActivePlanes] = src->xfc_enable
				&& ip->xfc_supported;
		mode_lib->vba.XFCSlvChunkSize = src->xfc_params.xfc_slv_chunk_size_bytes;
		mode_lib->vba.XFCTSlvVupdateOffset = src->xfc_params.xfc_tslv_vupdate_offset_us;
		mode_lib->vba.XFCTSlvVupdateWidth = src->xfc_params.xfc_tslv_vupdate_width_us;
		mode_lib->vba.XFCTSlvVपढ़ोyOffset = src->xfc_params.xfc_tslv_vपढ़ोy_offset_us;
		mode_lib->vba.PixelClock[mode_lib->vba.NumberOfActivePlanes] = dst->pixel_rate_mhz;
		mode_lib->vba.PixelClockBackEnd[mode_lib->vba.NumberOfActivePlanes] = dst->pixel_rate_mhz;
		mode_lib->vba.DPPCLK[mode_lib->vba.NumberOfActivePlanes] = clks->dppclk_mhz;
		अगर (ip->is_line_buffer_bpp_fixed)
			mode_lib->vba.LBBitPerPixel[mode_lib->vba.NumberOfActivePlanes] =
					ip->line_buffer_fixed_bpp;
		अन्यथा अणु
			अचिन्हित पूर्णांक lb_depth;

			चयन (scl->lb_depth) अणु
			हाल dm_lb_6:
				lb_depth = 18;
				अवरोध;
			हाल dm_lb_8:
				lb_depth = 24;
				अवरोध;
			हाल dm_lb_10:
				lb_depth = 30;
				अवरोध;
			हाल dm_lb_12:
				lb_depth = 36;
				अवरोध;
			हाल dm_lb_16:
				lb_depth = 48;
				अवरोध;
			हाल dm_lb_19:
				lb_depth = 57;
				अवरोध;
			शेष:
				lb_depth = 36;
			पूर्ण
			mode_lib->vba.LBBitPerPixel[mode_lib->vba.NumberOfActivePlanes] = lb_depth;
		पूर्ण
		mode_lib->vba.NumberOfCursors[mode_lib->vba.NumberOfActivePlanes] = 0;
		// The DML spपढ़ोsheet assumes that the two cursors utilize the same amount of bandwidth. We'll
		// calculate things a little more accurately
		क्रम (k = 0; k < DC__NUM_CURSOR__MAX; ++k) अणु
			चयन (k) अणु
			हाल 0:
				mode_lib->vba.CursorBPP[mode_lib->vba.NumberOfActivePlanes][0] =
						CursorBppEnumToBits(
								(क्रमागत cursor_bpp) (src->cur0_bpp));
				mode_lib->vba.CursorWidth[mode_lib->vba.NumberOfActivePlanes][0] =
						src->cur0_src_width;
				अगर (src->cur0_src_width > 0)
					mode_lib->vba.NumberOfCursors[mode_lib->vba.NumberOfActivePlanes]++;
				अवरोध;
			हाल 1:
				mode_lib->vba.CursorBPP[mode_lib->vba.NumberOfActivePlanes][1] =
						CursorBppEnumToBits(
								(क्रमागत cursor_bpp) (src->cur1_bpp));
				mode_lib->vba.CursorWidth[mode_lib->vba.NumberOfActivePlanes][1] =
						src->cur1_src_width;
				अगर (src->cur1_src_width > 0)
					mode_lib->vba.NumberOfCursors[mode_lib->vba.NumberOfActivePlanes]++;
				अवरोध;
			शेष:
				dml_prपूर्णांक(
						"ERROR: Number of cursors specified exceeds supported maximum\n")
				;
			पूर्ण
		पूर्ण

		OTGInstPlane[mode_lib->vba.NumberOfActivePlanes] = dst->otg_inst;

		अगर (j == 0)
			mode_lib->vba.UseMaximumVStartup = dst->use_maximum_vstartup;
		अन्यथा
			mode_lib->vba.UseMaximumVStartup = mode_lib->vba.UseMaximumVStartup
									|| dst->use_maximum_vstartup;

		अगर (dst->odm_combine && !src->is_hsplit)
			dml_prपूर्णांक(
					"ERROR: ODM Combine is specified but is_hsplit has not be specified for pipe %i\n",
					j);

		अगर (src->is_hsplit) अणु
			क्रम (k = j + 1; k < mode_lib->vba.cache_num_pipes; ++k) अणु
				display_pipe_source_params_st *src_k = &pipes[k].pipe.src;
				display_pipe_dest_params_st *dst_k = &pipes[k].pipe.dest;

				अगर (src_k->is_hsplit && !visited[k]
						&& src->hsplit_grp == src_k->hsplit_grp) अणु
					mode_lib->vba.pipe_plane[k] =
							mode_lib->vba.NumberOfActivePlanes;
					mode_lib->vba.DPPPerPlane[mode_lib->vba.NumberOfActivePlanes]++;
					अगर (mode_lib->vba.SourceScan[mode_lib->vba.NumberOfActivePlanes]
							== dm_horz) अणु
						mode_lib->vba.ViewportWidth[mode_lib->vba.NumberOfActivePlanes] +=
								src_k->viewport_width;
						mode_lib->vba.ViewportWidthChroma[mode_lib->vba.NumberOfActivePlanes] +=
								src_k->viewport_width_c;
						mode_lib->vba.ScalerRecoutWidth[mode_lib->vba.NumberOfActivePlanes] +=
								dst_k->recout_width;
					पूर्ण अन्यथा अणु
						mode_lib->vba.ViewportHeight[mode_lib->vba.NumberOfActivePlanes] +=
								src_k->viewport_height;
						mode_lib->vba.ViewportHeightChroma[mode_lib->vba.NumberOfActivePlanes] +=
								src_k->viewport_height_c;
					पूर्ण

					visited[k] = true;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (pipes[k].pipe.src.immediate_flip) अणु
			mode_lib->vba.ImmediateFlipSupport = true;
			mode_lib->vba.ImmediateFlipRequirement = dm_immediate_flip_required;
		पूर्ण

		mode_lib->vba.NumberOfActivePlanes++;
	पूर्ण

	// handle overlays through BlendingAndTiming
	// BlendingAndTiming tells you which instance to look at to get timing, the so called 'master'

	क्रम (j = 0; j < mode_lib->vba.NumberOfActivePlanes; ++j)
		PlaneVisited[j] = false;

	क्रम (j = 0; j < mode_lib->vba.NumberOfActivePlanes; ++j) अणु
		क्रम (k = j + 1; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
			अगर (!PlaneVisited[k] && OTGInstPlane[j] == OTGInstPlane[k]) अणु
				// करोesn't matter, so choose the smaller one
				mode_lib->vba.BlendingAndTiming[j] = j;
				PlaneVisited[j] = true;
				mode_lib->vba.BlendingAndTiming[k] = j;
				PlaneVisited[k] = true;
			पूर्ण
		पूर्ण

		अगर (!PlaneVisited[j]) अणु
			mode_lib->vba.BlendingAndTiming[j] = j;
			PlaneVisited[j] = true;
		पूर्ण
	पूर्ण

	// TODO: ODMCombineEnabled => 2 * DPPPerPlane...actually maybe not since all pipes are specअगरied
	// Do we want the dscclk to स्वतःmatically be halved? Guess not since the value is specअगरied
	mode_lib->vba.SynchronizedVBlank = pipes[0].pipe.dest.synchronized_vblank_all_planes;
	क्रम (k = 1; k < mode_lib->vba.cache_num_pipes; ++k) अणु
		ASSERT(mode_lib->vba.SynchronizedVBlank == pipes[k].pipe.dest.synchronized_vblank_all_planes);
	पूर्ण

	mode_lib->vba.GPUVMEnable = false;
	mode_lib->vba.HostVMEnable = false;
	mode_lib->vba.OverrideGPUVMPageTableLevels = 0;
	mode_lib->vba.OverrideHostVMPageTableLevels = 0;

	क्रम (k = 0; k < mode_lib->vba.cache_num_pipes; ++k) अणु
		mode_lib->vba.GPUVMEnable = mode_lib->vba.GPUVMEnable || !!pipes[k].pipe.src.gpuvm || !!pipes[k].pipe.src.vm;
		mode_lib->vba.OverrideGPUVMPageTableLevels =
				(pipes[k].pipe.src.gpuvm_levels_क्रमce_en
						&& mode_lib->vba.OverrideGPUVMPageTableLevels
								< pipes[k].pipe.src.gpuvm_levels_क्रमce) ?
						pipes[k].pipe.src.gpuvm_levels_क्रमce :
						mode_lib->vba.OverrideGPUVMPageTableLevels;

		mode_lib->vba.HostVMEnable = mode_lib->vba.HostVMEnable || !!pipes[k].pipe.src.hostvm || !!pipes[k].pipe.src.vm;
		mode_lib->vba.OverrideHostVMPageTableLevels =
				(pipes[k].pipe.src.hostvm_levels_क्रमce_en
						&& mode_lib->vba.OverrideHostVMPageTableLevels
								< pipes[k].pipe.src.hostvm_levels_क्रमce) ?
						pipes[k].pipe.src.hostvm_levels_क्रमce :
						mode_lib->vba.OverrideHostVMPageTableLevels;
	पूर्ण

	mode_lib->vba.AllowDRAMSelfRefreshOrDRAMClockChangeInVblank = dm_try_to_allow_self_refresh_and_mclk_चयन;

	अगर (mode_lib->vba.OverrideGPUVMPageTableLevels)
		mode_lib->vba.GPUVMMaxPageTableLevels = mode_lib->vba.OverrideGPUVMPageTableLevels;

	अगर (mode_lib->vba.OverrideHostVMPageTableLevels)
		mode_lib->vba.HostVMMaxPageTableLevels = mode_lib->vba.OverrideHostVMPageTableLevels;

	mode_lib->vba.GPUVMEnable = mode_lib->vba.GPUVMEnable && !!ip->gpuvm_enable;
	mode_lib->vba.HostVMEnable = mode_lib->vba.HostVMEnable && !!ip->hostvm_enable;
पूर्ण

// in wm mode we pull the parameters needed from the display_e2e_pipe_params_st काष्ठाs
// rather than working them out as in recalculate_ms
अटल व्योम recalculate_params(
		काष्ठा display_mode_lib *mode_lib,
		स्थिर display_e2e_pipe_params_st *pipes,
		अचिन्हित पूर्णांक num_pipes)
अणु
	// This is only safe to use स_भेद because there are non-POD types in काष्ठा display_mode_lib
	अगर (स_भेद(&mode_lib->soc, &mode_lib->vba.soc, माप(mode_lib->vba.soc)) != 0
			|| स_भेद(&mode_lib->ip, &mode_lib->vba.ip, माप(mode_lib->vba.ip)) != 0
			|| num_pipes != mode_lib->vba.cache_num_pipes
			|| स_भेद(
					pipes,
					mode_lib->vba.cache_pipes,
					माप(display_e2e_pipe_params_st) * num_pipes) != 0) अणु
		mode_lib->vba.soc = mode_lib->soc;
		mode_lib->vba.ip = mode_lib->ip;
		स_नकल(mode_lib->vba.cache_pipes, pipes, माप(*pipes) * num_pipes);
		mode_lib->vba.cache_num_pipes = num_pipes;
		mode_lib->funcs.recalculate(mode_lib);
	पूर्ण
पूर्ण

bool Calculate256BBlockSizes(
		क्रमागत source_क्रमmat_class SourcePixelFormat,
		क्रमागत dm_swizzle_mode SurfaceTiling,
		अचिन्हित पूर्णांक BytePerPixelY,
		अचिन्हित पूर्णांक BytePerPixelC,
		अचिन्हित पूर्णांक *BlockHeight256BytesY,
		अचिन्हित पूर्णांक *BlockHeight256BytesC,
		अचिन्हित पूर्णांक *BlockWidth256BytesY,
		अचिन्हित पूर्णांक *BlockWidth256BytesC)
अणु
	अगर ((SourcePixelFormat == dm_444_64 || SourcePixelFormat == dm_444_32
			|| SourcePixelFormat == dm_444_16 || SourcePixelFormat == dm_444_8)) अणु
		अगर (SurfaceTiling == dm_sw_linear) अणु
			*BlockHeight256BytesY = 1;
		पूर्ण अन्यथा अगर (SourcePixelFormat == dm_444_64) अणु
			*BlockHeight256BytesY = 4;
		पूर्ण अन्यथा अगर (SourcePixelFormat == dm_444_8) अणु
			*BlockHeight256BytesY = 16;
		पूर्ण अन्यथा अणु
			*BlockHeight256BytesY = 8;
		पूर्ण
		*BlockWidth256BytesY = 256 / BytePerPixelY / *BlockHeight256BytesY;
		*BlockHeight256BytesC = 0;
		*BlockWidth256BytesC = 0;
	पूर्ण अन्यथा अणु
		अगर (SurfaceTiling == dm_sw_linear) अणु
			*BlockHeight256BytesY = 1;
			*BlockHeight256BytesC = 1;
		पूर्ण अन्यथा अगर (SourcePixelFormat == dm_420_8) अणु
			*BlockHeight256BytesY = 16;
			*BlockHeight256BytesC = 8;
		पूर्ण अन्यथा अणु
			*BlockHeight256BytesY = 8;
			*BlockHeight256BytesC = 8;
		पूर्ण
		*BlockWidth256BytesY = 256 / BytePerPixelY / *BlockHeight256BytesY;
		*BlockWidth256BytesC = 256 / BytePerPixelC / *BlockHeight256BytesC;
	पूर्ण
	वापस true;
पूर्ण

bool CalculateMinAndMaxPrefetchMode(
		क्रमागत self_refresh_affinity AllowDRAMSelfRefreshOrDRAMClockChangeInVblank,
		अचिन्हित पूर्णांक *MinPrefetchMode,
		अचिन्हित पूर्णांक *MaxPrefetchMode)
अणु
	अगर (AllowDRAMSelfRefreshOrDRAMClockChangeInVblank
			== dm_neither_self_refresh_nor_mclk_चयन) अणु
		*MinPrefetchMode = 2;
		*MaxPrefetchMode = 2;
		वापस false;
	पूर्ण अन्यथा अगर (AllowDRAMSelfRefreshOrDRAMClockChangeInVblank == dm_allow_self_refresh) अणु
		*MinPrefetchMode = 1;
		*MaxPrefetchMode = 1;
		वापस false;
	पूर्ण अन्यथा अगर (AllowDRAMSelfRefreshOrDRAMClockChangeInVblank
			== dm_allow_self_refresh_and_mclk_चयन) अणु
		*MinPrefetchMode = 0;
		*MaxPrefetchMode = 0;
		वापस false;
	पूर्ण अन्यथा अगर (AllowDRAMSelfRefreshOrDRAMClockChangeInVblank
			== dm_try_to_allow_self_refresh_and_mclk_चयन) अणु
		*MinPrefetchMode = 0;
		*MaxPrefetchMode = 2;
		वापस false;
	पूर्ण
	*MinPrefetchMode = 0;
	*MaxPrefetchMode = 2;
	वापस true;
पूर्ण

व्योम PixelClockAdjusपंचांगentForProgressiveToInterlaceUnit(काष्ठा display_mode_lib *mode_lib)
अणु
	अचिन्हित पूर्णांक k;

	//Progressive To Interlace Unit Effect
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		अगर (mode_lib->vba.Interlace[k] == 1
				&& mode_lib->vba.ProgressiveToInterlaceUnitInOPP == true) अणु
			mode_lib->vba.PixelClock[k] = 2 * mode_lib->vba.PixelClockBackEnd[k];
		पूर्ण
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक CursorBppEnumToBits(क्रमागत cursor_bpp ebpp)
अणु
	चयन (ebpp) अणु
	हाल dm_cur_2bit:
		वापस 2;
	हाल dm_cur_32bit:
		वापस 32;
	हाल dm_cur_64bit:
		वापस 64;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

व्योम ModeSupportAndSystemConfiguration(काष्ठा display_mode_lib *mode_lib)
अणु
	soc_bounding_box_st *soc = &mode_lib->vba.soc;
	अचिन्हित पूर्णांक k;
	अचिन्हित पूर्णांक total_pipes = 0;

	mode_lib->vba.VoltageLevel = mode_lib->vba.cache_pipes[0].clks_cfg.voltage;
	mode_lib->vba.ReturnBW = mode_lib->vba.ReturnBWPerState[mode_lib->vba.VoltageLevel][mode_lib->vba.maxMpcComb];
	अगर (mode_lib->vba.ReturnBW == 0)
		mode_lib->vba.ReturnBW = mode_lib->vba.ReturnBWPerState[mode_lib->vba.VoltageLevel][0];
	mode_lib->vba.FabricAndDRAMBandwidth = mode_lib->vba.FabricAndDRAMBandwidthPerState[mode_lib->vba.VoltageLevel];

	fetch_socbb_params(mode_lib);
	fetch_ip_params(mode_lib);
	fetch_pipe_params(mode_lib);

	mode_lib->vba.DCFCLK = mode_lib->vba.cache_pipes[0].clks_cfg.dcfclk_mhz;
	mode_lib->vba.SOCCLK = mode_lib->vba.cache_pipes[0].clks_cfg.socclk_mhz;
	अगर (mode_lib->vba.cache_pipes[0].clks_cfg.dispclk_mhz > 0.0)
		mode_lib->vba.DISPCLK = mode_lib->vba.cache_pipes[0].clks_cfg.dispclk_mhz;
	अन्यथा
		mode_lib->vba.DISPCLK = soc->घड़ी_limits[mode_lib->vba.VoltageLevel].dispclk_mhz;

	// Total Available Pipes Support Check
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k)
		total_pipes += mode_lib->vba.DPPPerPlane[k];
	ASSERT(total_pipes <= DC__NUM_DPP__MAX);
पूर्ण

द्विगुन CalculateWriteBackDISPCLK(
		क्रमागत source_क्रमmat_class WritebackPixelFormat,
		द्विगुन PixelClock,
		द्विगुन WritebackHRatio,
		द्विगुन WritebackVRatio,
		अचिन्हित पूर्णांक WritebackLumaHTaps,
		अचिन्हित पूर्णांक WritebackLumaVTaps,
		अचिन्हित पूर्णांक WritebackChromaHTaps,
		अचिन्हित पूर्णांक WritebackChromaVTaps,
		द्विगुन WritebackDestinationWidth,
		अचिन्हित पूर्णांक HTotal,
		अचिन्हित पूर्णांक WritebackChromaLineBufferWidth)
अणु
	द्विगुन CalculateWriteBackDISPCLK = 1.01 * PixelClock * dml_max(
		dml_उच्चमान(WritebackLumaHTaps / 4.0, 1) / WritebackHRatio,
		dml_max((WritebackLumaVTaps * dml_उच्चमान(1.0 / WritebackVRatio, 1) * dml_उच्चमान(WritebackDestinationWidth / 4.0, 1)
			+ dml_उच्चमान(WritebackDestinationWidth / 4.0, 1)) / (द्विगुन) HTotal + dml_उच्चमान(1.0 / WritebackVRatio, 1)
			* (dml_उच्चमान(WritebackLumaVTaps / 4.0, 1) + 4.0) / (द्विगुन) HTotal,
			dml_उच्चमान(1.0 / WritebackVRatio, 1) * WritebackDestinationWidth / (द्विगुन) HTotal));
	अगर (WritebackPixelFormat != dm_444_32) अणु
		CalculateWriteBackDISPCLK = dml_max(CalculateWriteBackDISPCLK, 1.01 * PixelClock * dml_max(
			dml_उच्चमान(WritebackChromaHTaps / 2.0, 1) / (2 * WritebackHRatio),
			dml_max((WritebackChromaVTaps * dml_उच्चमान(1 / (2 * WritebackVRatio), 1) * dml_उच्चमान(WritebackDestinationWidth / 2.0 / 2.0, 1)
				+ dml_उच्चमान(WritebackDestinationWidth / 2.0 / WritebackChromaLineBufferWidth, 1)) / HTotal
				+ dml_उच्चमान(1 / (2 * WritebackVRatio), 1) * (dml_उच्चमान(WritebackChromaVTaps / 4.0, 1) + 4) / HTotal,
				dml_उच्चमान(1.0 / (2 * WritebackVRatio), 1) * WritebackDestinationWidth / 2.0 / HTotal)));
	पूर्ण
	वापस CalculateWriteBackDISPCLK;
पूर्ण

