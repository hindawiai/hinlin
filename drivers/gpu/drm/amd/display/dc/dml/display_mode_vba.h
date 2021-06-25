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


#अगर_अघोषित __DML2_DISPLAY_MODE_VBA_H__
#घोषणा __DML2_DISPLAY_MODE_VBA_H__

काष्ठा display_mode_lib;

व्योम ModeSupportAndSystemConfiguration(काष्ठा display_mode_lib *mode_lib);

#घोषणा dml_get_attr_decl(attr) द्विगुन get_##attr(काष्ठा display_mode_lib *mode_lib, स्थिर display_e2e_pipe_params_st *pipes, अचिन्हित पूर्णांक num_pipes)

dml_get_attr_decl(clk_dcf_deepsleep);
dml_get_attr_decl(wm_urgent);
dml_get_attr_decl(wm_memory_trip);
dml_get_attr_decl(wm_ग_लिखोback_urgent);
dml_get_attr_decl(wm_stutter_निकास);
dml_get_attr_decl(wm_stutter_enter_निकास);
dml_get_attr_decl(wm_dram_घड़ी_change);
dml_get_attr_decl(wm_ग_लिखोback_dram_घड़ी_change);
dml_get_attr_decl(stutter_efficiency_no_vblank);
dml_get_attr_decl(stutter_efficiency);
dml_get_attr_decl(stutter_period);
dml_get_attr_decl(urgent_latency);
dml_get_attr_decl(urgent_extra_latency);
dml_get_attr_decl(nonurgent_latency);
dml_get_attr_decl(dram_घड़ी_change_latency);
dml_get_attr_decl(dispclk_calculated);
dml_get_attr_decl(total_data_पढ़ो_bw);
dml_get_attr_decl(वापस_bw);
dml_get_attr_decl(tcalc);
dml_get_attr_decl(fraction_of_urgent_bandwidth);
dml_get_attr_decl(fraction_of_urgent_bandwidth_imm_flip);

#घोषणा dml_get_pipe_attr_decl(attr) द्विगुन get_##attr(काष्ठा display_mode_lib *mode_lib, स्थिर display_e2e_pipe_params_st *pipes, अचिन्हित पूर्णांक num_pipes, अचिन्हित पूर्णांक which_pipe)

dml_get_pipe_attr_decl(dsc_delay);
dml_get_pipe_attr_decl(dppclk_calculated);
dml_get_pipe_attr_decl(dscclk_calculated);
dml_get_pipe_attr_decl(min_ttu_vblank);
dml_get_pipe_attr_decl(min_ttu_vblank_in_us);
dml_get_pipe_attr_decl(vratio_prefetch_l);
dml_get_pipe_attr_decl(vratio_prefetch_c);
dml_get_pipe_attr_decl(dst_x_after_scaler);
dml_get_pipe_attr_decl(dst_y_after_scaler);
dml_get_pipe_attr_decl(dst_y_per_vm_vblank);
dml_get_pipe_attr_decl(dst_y_per_row_vblank);
dml_get_pipe_attr_decl(dst_y_prefetch);
dml_get_pipe_attr_decl(dst_y_per_vm_flip);
dml_get_pipe_attr_decl(dst_y_per_row_flip);
dml_get_pipe_attr_decl(refcyc_per_vm_group_vblank);
dml_get_pipe_attr_decl(refcyc_per_vm_group_flip);
dml_get_pipe_attr_decl(refcyc_per_vm_req_vblank);
dml_get_pipe_attr_decl(refcyc_per_vm_req_flip);
dml_get_pipe_attr_decl(refcyc_per_vm_group_vblank_in_us);
dml_get_pipe_attr_decl(refcyc_per_vm_group_flip_in_us);
dml_get_pipe_attr_decl(refcyc_per_vm_req_vblank_in_us);
dml_get_pipe_attr_decl(refcyc_per_vm_req_flip_in_us);
dml_get_pipe_attr_decl(refcyc_per_vm_dmdata_in_us);
dml_get_pipe_attr_decl(dmdata_dl_delta_in_us);
dml_get_pipe_attr_decl(refcyc_per_line_delivery_l_in_us);
dml_get_pipe_attr_decl(refcyc_per_line_delivery_c_in_us);
dml_get_pipe_attr_decl(refcyc_per_line_delivery_pre_l_in_us);
dml_get_pipe_attr_decl(refcyc_per_line_delivery_pre_c_in_us);
dml_get_pipe_attr_decl(refcyc_per_req_delivery_l_in_us);
dml_get_pipe_attr_decl(refcyc_per_req_delivery_c_in_us);
dml_get_pipe_attr_decl(refcyc_per_req_delivery_pre_l_in_us);
dml_get_pipe_attr_decl(refcyc_per_req_delivery_pre_c_in_us);
dml_get_pipe_attr_decl(refcyc_per_cursor_req_delivery_in_us);
dml_get_pipe_attr_decl(refcyc_per_cursor_req_delivery_pre_in_us);
dml_get_pipe_attr_decl(refcyc_per_meta_chunk_nom_l_in_us);
dml_get_pipe_attr_decl(refcyc_per_meta_chunk_nom_c_in_us);
dml_get_pipe_attr_decl(refcyc_per_meta_chunk_vblank_l_in_us);
dml_get_pipe_attr_decl(refcyc_per_meta_chunk_vblank_c_in_us);
dml_get_pipe_attr_decl(refcyc_per_meta_chunk_flip_l_in_us);
dml_get_pipe_attr_decl(refcyc_per_meta_chunk_flip_c_in_us);

dml_get_pipe_attr_decl(vstartup);
dml_get_pipe_attr_decl(vupdate_offset);
dml_get_pipe_attr_decl(vupdate_width);
dml_get_pipe_attr_decl(vपढ़ोy_offset);

द्विगुन get_total_immediate_flip_bytes(
		काष्ठा display_mode_lib *mode_lib,
		स्थिर display_e2e_pipe_params_st *pipes,
		अचिन्हित पूर्णांक num_pipes);
द्विगुन get_total_immediate_flip_bw(
		काष्ठा display_mode_lib *mode_lib,
		स्थिर display_e2e_pipe_params_st *pipes,
		अचिन्हित पूर्णांक num_pipes);
द्विगुन get_total_prefetch_bw(
		काष्ठा display_mode_lib *mode_lib,
		स्थिर display_e2e_pipe_params_st *pipes,
		अचिन्हित पूर्णांक num_pipes);
अचिन्हित पूर्णांक dml_get_voltage_level(
		काष्ठा display_mode_lib *mode_lib,
		स्थिर display_e2e_pipe_params_st *pipes,
		अचिन्हित पूर्णांक num_pipes);

व्योम PixelClockAdjusपंचांगentForProgressiveToInterlaceUnit(काष्ठा display_mode_lib *mode_lib);

bool Calculate256BBlockSizes(
		क्रमागत source_क्रमmat_class SourcePixelFormat,
		क्रमागत dm_swizzle_mode SurfaceTiling,
		अचिन्हित पूर्णांक BytePerPixelY,
		अचिन्हित पूर्णांक BytePerPixelC,
		अचिन्हित पूर्णांक *BlockHeight256BytesY,
		अचिन्हित पूर्णांक *BlockHeight256BytesC,
		अचिन्हित पूर्णांक *BlockWidth256BytesY,
		अचिन्हित पूर्णांक *BlockWidth256BytesC);

काष्ठा vba_vars_st अणु
	ip_params_st ip;
	soc_bounding_box_st soc;

	पूर्णांक maxMpcComb;
	bool UseMaximumVStartup;

	द्विगुन WritebackDISPCLK;
	द्विगुन DPPCLKUsingSingleDPPLuma;
	द्विगुन DPPCLKUsingSingleDPPChroma;
	द्विगुन DISPCLKWithRamping;
	द्विगुन DISPCLKWithoutRamping;
	द्विगुन GlobalDPPCLK;
	द्विगुन DISPCLKWithRampingRoundedToDFSGranularity;
	द्विगुन DISPCLKWithoutRampingRoundedToDFSGranularity;
	द्विगुन MaxDispclkRoundedToDFSGranularity;
	bool DCCEnabledAnyPlane;
	द्विगुन ReturnBandwidthToDCN;
	अचिन्हित पूर्णांक TotalActiveDPP;
	अचिन्हित पूर्णांक TotalDCCActiveDPP;
	द्विगुन UrgentRoundTripAndOutOfOrderLatency;
	द्विगुन StutterPeriod;
	द्विगुन FrameTimeForMinFullDETBufferingTime;
	द्विगुन AverageReadBandwidth;
	द्विगुन TotalRowReadBandwidth;
	द्विगुन PartOfBurstThatFitsInROB;
	द्विगुन StutterBurstTime;
	अचिन्हित पूर्णांक NextPrefetchMode;
	द्विगुन NextMaxVStartup;
	द्विगुन VBlankTime;
	द्विगुन SmallestVBlank;
	द्विगुन DCFCLKDeepSleepPerPlane[DC__NUM_DPP__MAX];
	द्विगुन EffectiveDETPlusLBLinesLuma;
	द्विगुन EffectiveDETPlusLBLinesChroma;
	द्विगुन UrgentLatencySupportUsLuma;
	द्विगुन UrgentLatencySupportUsChroma;
	अचिन्हित पूर्णांक DSCFormatFactor;

	bool DummyPStateCheck;
	bool DRAMClockChangeSupportsVActive;
	bool PrefetchModeSupported;
	bool PrefetchAndImmediateFlipSupported;
	क्रमागत self_refresh_affinity AllowDRAMSelfRefreshOrDRAMClockChangeInVblank; // Mode Support only
	द्विगुन XFCRemoteSurfaceFlipDelay;
	द्विगुन TInitXFill;
	द्विगुन TslvChk;
	द्विगुन SrcActiveDrainRate;
	bool ImmediateFlipSupported;
	क्रमागत mpc_combine_affinity WhenToDoMPCCombine; // Mode Support only

	bool PrefetchERROR;

	अचिन्हित पूर्णांक VStartupLines;
	अचिन्हित पूर्णांक ActiveDPPs;
	अचिन्हित पूर्णांक LBLatencyHidingSourceLinesY;
	अचिन्हित पूर्णांक LBLatencyHidingSourceLinesC;
	द्विगुन ActiveDRAMClockChangeLatencyMargin[DC__NUM_DPP__MAX];
	द्विगुन MinActiveDRAMClockChangeMargin;
	द्विगुन InitFillLevel;
	द्विगुन FinalFillMargin;
	द्विगुन FinalFillLevel;
	द्विगुन Reमुख्यingFillLevel;
	द्विगुन TFinalxFill;

	//
	// SOC Bounding Box Parameters
	//
	द्विगुन SRExitTime;
	द्विगुन SREnterPlusExitTime;
	द्विगुन UrgentLatencyPixelDataOnly;
	द्विगुन UrgentLatencyPixelMixedWithVMData;
	द्विगुन UrgentLatencyVMDataOnly;
	द्विगुन UrgentLatency; // max of the above three
	द्विगुन WritebackLatency;
	द्विगुन PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelDataOnly; // Mode Support
	द्विगुन PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData; // Mode Support
	द्विगुन PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly; // Mode Support
	द्विगुन MaxAveragePercentOfIdealSDPPortBWDisplayCanUseInNormalSystemOperation; // Mode Support
	द्विगुन MaxAveragePercentOfIdealDRAMBWDisplayCanUseInNormalSystemOperation; // Mode Support
	द्विगुन NumberOfChannels;
	द्विगुन DRAMChannelWidth;
	द्विगुन FabricDatapathToDCNDataReturn;
	द्विगुन ReturnBusWidth;
	द्विगुन Downspपढ़ोing;
	द्विगुन DISPCLKDPPCLKDSCCLKDownSpपढ़ोing;
	द्विगुन DISPCLKDPPCLKVCOSpeed;
	द्विगुन RoundTripPingLatencyCycles;
	द्विगुन UrgentOutOfOrderReturnPerChannel;
	द्विगुन UrgentOutOfOrderReturnPerChannelPixelDataOnly;
	द्विगुन UrgentOutOfOrderReturnPerChannelPixelMixedWithVMData;
	द्विगुन UrgentOutOfOrderReturnPerChannelVMDataOnly;
	अचिन्हित पूर्णांक VMMPageSize;
	द्विगुन DRAMClockChangeLatency;
	द्विगुन XFCBusTransportTime;
	bool UseUrgentBurstBandwidth;
	द्विगुन XFCXBUFLatencyTolerance;

	//
	// IP Parameters
	//
	अचिन्हित पूर्णांक ROBBufferSizeInKByte;
	द्विगुन DETBufferSizeInKByte;
	द्विगुन DETBufferSizeInTime;
	अचिन्हित पूर्णांक DPPOutputBufferPixels;
	अचिन्हित पूर्णांक OPPOutputBufferLines;
	अचिन्हित पूर्णांक PixelChunkSizeInKByte;
	द्विगुन ReturnBW;
	bool GPUVMEnable;
	bool HostVMEnable;
	अचिन्हित पूर्णांक GPUVMMaxPageTableLevels;
	अचिन्हित पूर्णांक HostVMMaxPageTableLevels;
	अचिन्हित पूर्णांक HostVMCachedPageTableLevels;
	अचिन्हित पूर्णांक OverrideGPUVMPageTableLevels;
	अचिन्हित पूर्णांक OverrideHostVMPageTableLevels;
	अचिन्हित पूर्णांक MetaChunkSize;
	अचिन्हित पूर्णांक MinMetaChunkSizeBytes;
	अचिन्हित पूर्णांक WritebackChunkSize;
	bool ODMCapability;
	अचिन्हित पूर्णांक NumberOfDSC;
	अचिन्हित पूर्णांक LineBufferSize;
	अचिन्हित पूर्णांक MaxLineBufferLines;
	अचिन्हित पूर्णांक WritebackInterfaceLumaBufferSize;
	अचिन्हित पूर्णांक WritebackInterfaceChromaBufferSize;
	अचिन्हित पूर्णांक WritebackChromaLineBufferWidth;
	क्रमागत ग_लिखोback_config WritebackConfiguration;
	द्विगुन MaxDCHUBToPSCLThroughput;
	द्विगुन MaxPSCLToLBThroughput;
	अचिन्हित पूर्णांक PTEBufferSizeInRequestsLuma;
	अचिन्हित पूर्णांक PTEBufferSizeInRequestsChroma;
	द्विगुन DISPCLKRampingMargin;
	अचिन्हित पूर्णांक MaxInterDCNTileRepeaters;
	bool XFCSupported;
	द्विगुन XFCSlvChunkSize;
	द्विगुन XFCFillBWOverhead;
	द्विगुन XFCFillConstant;
	द्विगुन XFCTSlvVupdateOffset;
	द्विगुन XFCTSlvVupdateWidth;
	द्विगुन XFCTSlvVपढ़ोyOffset;
	द्विगुन DPPCLKDelaySubtotal;
	द्विगुन DPPCLKDelaySCL;
	द्विगुन DPPCLKDelaySCLLBOnly;
	द्विगुन DPPCLKDelayCNVCFormater;
	द्विगुन DPPCLKDelayCNVCCursor;
	द्विगुन DISPCLKDelaySubtotal;
	bool ProgressiveToInterlaceUnitInOPP;
	// Pipe/Plane Parameters
	पूर्णांक VoltageLevel;
	द्विगुन FabricClock;
	द्विगुन DRAMSpeed;
	द्विगुन DISPCLK;
	द्विगुन SOCCLK;
	द्विगुन DCFCLK;

	अचिन्हित पूर्णांक NumberOfActivePlanes;
	अचिन्हित पूर्णांक NumberOfDSCSlices[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक ViewportWidth[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक ViewportHeight[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक ViewportYStartY[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक ViewportYStartC[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक PitchY[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक PitchC[DC__NUM_DPP__MAX];
	द्विगुन HRatio[DC__NUM_DPP__MAX];
	द्विगुन VRatio[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक htaps[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक vtaps[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक HTAPsChroma[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक VTAPsChroma[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक HTotal[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक VTotal[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक VTotal_Max[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक VTotal_Min[DC__NUM_DPP__MAX];
	पूर्णांक DPPPerPlane[DC__NUM_DPP__MAX];
	द्विगुन PixelClock[DC__NUM_DPP__MAX];
	द्विगुन PixelClockBackEnd[DC__NUM_DPP__MAX];
	bool DCCEnable[DC__NUM_DPP__MAX];
	bool FECEnable[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक DCCMetaPitchY[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक DCCMetaPitchC[DC__NUM_DPP__MAX];
	क्रमागत scan_direction_class SourceScan[DC__NUM_DPP__MAX];
	क्रमागत source_क्रमmat_class SourcePixelFormat[DC__NUM_DPP__MAX];
	bool WritebackEnable[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक ActiveWritebacksPerPlane[DC__NUM_DPP__MAX];
	द्विगुन WritebackDestinationWidth[DC__NUM_DPP__MAX];
	द्विगुन WritebackDestinationHeight[DC__NUM_DPP__MAX];
	द्विगुन WritebackSourceHeight[DC__NUM_DPP__MAX];
	क्रमागत source_क्रमmat_class WritebackPixelFormat[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक WritebackLumaHTaps[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक WritebackLumaVTaps[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक WritebackChromaHTaps[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक WritebackChromaVTaps[DC__NUM_DPP__MAX];
	द्विगुन WritebackHRatio[DC__NUM_DPP__MAX];
	द्विगुन WritebackVRatio[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक HActive[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक VActive[DC__NUM_DPP__MAX];
	bool Interlace[DC__NUM_DPP__MAX];
	क्रमागत dm_swizzle_mode SurfaceTiling[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक ScalerRecoutWidth[DC__NUM_DPP__MAX];
	bool DynamicMetadataEnable[DC__NUM_DPP__MAX];
	पूर्णांक DynamicMetadataLinesBeक्रमeActiveRequired[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक DynamicMetadataTransmittedBytes[DC__NUM_DPP__MAX];
	द्विगुन DCCRate[DC__NUM_DPP__MAX];
	द्विगुन AverageDCCCompressionRate;
	क्रमागत odm_combine_mode ODMCombineEnabled[DC__NUM_DPP__MAX];
	द्विगुन OutputBpp[DC__NUM_DPP__MAX];
	bool DSCEnabled[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक DSCInputBitPerComponent[DC__NUM_DPP__MAX];
	क्रमागत output_क्रमmat_class OutputFormat[DC__NUM_DPP__MAX];
	क्रमागत output_encoder_class Output[DC__NUM_DPP__MAX];
	bool skip_dio_check[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक BlendingAndTiming[DC__NUM_DPP__MAX];
	bool SynchronizedVBlank;
	अचिन्हित पूर्णांक NumberOfCursors[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक CursorWidth[DC__NUM_DPP__MAX][DC__NUM_CURSOR__MAX];
	अचिन्हित पूर्णांक CursorBPP[DC__NUM_DPP__MAX][DC__NUM_CURSOR__MAX];
	bool XFCEnabled[DC__NUM_DPP__MAX];
	bool ScalerEnabled[DC__NUM_DPP__MAX];

	// Intermediates/Inक्रमmational
	bool ImmediateFlipSupport;
	द्विगुन DETBufferSizeY[DC__NUM_DPP__MAX];
	द्विगुन DETBufferSizeC[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक SwathHeightY[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक SwathHeightC[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक LBBitPerPixel[DC__NUM_DPP__MAX];
	द्विगुन LastPixelOfLineExtraWatermark;
	द्विगुन TotalDataReadBandwidth;
	अचिन्हित पूर्णांक TotalActiveWriteback;
	अचिन्हित पूर्णांक EffectiveLBLatencyHidingSourceLinesLuma;
	अचिन्हित पूर्णांक EffectiveLBLatencyHidingSourceLinesChroma;
	द्विगुन BandwidthAvailableForImmediateFlip;
	अचिन्हित पूर्णांक PrefetchMode[DC__VOLTAGE_STATES][2];
	अचिन्हित पूर्णांक PrefetchModePerState[DC__VOLTAGE_STATES][2];
	अचिन्हित पूर्णांक MinPrefetchMode;
	अचिन्हित पूर्णांक MaxPrefetchMode;
	bool AnyLinesForVMOrRowTooLarge;
	द्विगुन MaxVStartup;
	bool IgnoreViewportPositioning;
	bool ErrorResult[DC__NUM_DPP__MAX];
	//
	// Calculated dml_ml->vba.Outमाला_दो
	//
	द्विगुन DCFCLKDeepSleep;
	द्विगुन UrgentWatermark;
	द्विगुन UrgentExtraLatency;
	द्विगुन WritebackUrgentWatermark;
	द्विगुन StutterExitWatermark;
	द्विगुन StutterEnterPlusExitWatermark;
	द्विगुन DRAMClockChangeWatermark;
	द्विगुन WritebackDRAMClockChangeWatermark;
	द्विगुन StutterEfficiency;
	द्विगुन StutterEfficiencyNotIncludingVBlank;
	द्विगुन NonUrgentLatencyTolerance;
	द्विगुन MinActiveDRAMClockChangeLatencySupported;

	// These are the घड़ीs calcuated by the library but they are not actually
	// used explicitly. They are fetched by tests and then possibly used. The
	// ultimate values to use are the ones specअगरied by the parameters to DML
	द्विगुन DISPCLK_calculated;
	द्विगुन DPPCLK_calculated[DC__NUM_DPP__MAX];

	अचिन्हित पूर्णांक VUpdateOffsetPix[DC__NUM_DPP__MAX];
	द्विगुन VUpdateWidthPix[DC__NUM_DPP__MAX];
	द्विगुन VReadyOffsetPix[DC__NUM_DPP__MAX];

	अचिन्हित पूर्णांक TotImmediateFlipBytes;
	द्विगुन TCalc;

	display_e2e_pipe_params_st cache_pipes[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक cache_num_pipes;
	अचिन्हित पूर्णांक pipe_plane[DC__NUM_DPP__MAX];

	/* vba mode support */
	/*inमाला_दो*/
	bool SupportGFX7CompatibleTilingIn32bppAnd64bpp;
	द्विगुन MaxHSCLRatio;
	द्विगुन MaxVSCLRatio;
	अचिन्हित पूर्णांक MaxNumWriteback;
	bool WritebackLumaAndChromaScalingSupported;
	bool Cursor64BppSupport;
	द्विगुन DCFCLKPerState[DC__VOLTAGE_STATES];
	द्विगुन DCFCLKState[DC__VOLTAGE_STATES][2];
	द्विगुन FabricClockPerState[DC__VOLTAGE_STATES];
	द्विगुन SOCCLKPerState[DC__VOLTAGE_STATES];
	द्विगुन PHYCLKPerState[DC__VOLTAGE_STATES];
	द्विगुन DTBCLKPerState[DC__VOLTAGE_STATES];
	द्विगुन MaxDppclk[DC__VOLTAGE_STATES];
	द्विगुन MaxDSCCLK[DC__VOLTAGE_STATES];
	द्विगुन DRAMSpeedPerState[DC__VOLTAGE_STATES];
	द्विगुन MaxDispclk[DC__VOLTAGE_STATES];
	पूर्णांक VoltageOverrideLevel;

	/*outमाला_दो*/
	bool ScaleRatioAndTapsSupport;
	bool SourceFormatPixelAndScanSupport;
	द्विगुन TotalBandwidthConsumedGBytePerSecond;
	bool DCCEnabledInAnyPlane;
	bool WritebackLatencySupport;
	bool WritebackModeSupport;
	bool Writeback10bpc420Supported;
	bool BandwidthSupport[DC__VOLTAGE_STATES];
	अचिन्हित पूर्णांक TotalNumberOfActiveWriteback;
	द्विगुन CriticalPoपूर्णांक;
	द्विगुन ReturnBWToDCNPerState;
	bool IsErrorResult[DC__VOLTAGE_STATES][2][DC__NUM_DPP__MAX];
	bool prefetch_vm_bw_valid;
	bool prefetch_row_bw_valid;
	bool NumberOfOTGSupport;
	bool NonsupportedDSCInputBPC;
	bool WritebackScaleRatioAndTapsSupport;
	bool CursorSupport;
	bool PitchSupport;
	क्रमागत dm_validation_status ValidationStatus[DC__VOLTAGE_STATES];

	द्विगुन WritebackLineBufferLumaBufferSize;
	द्विगुन WritebackLineBufferChromaBufferSize;
	द्विगुन WritebackMinHSCLRatio;
	द्विगुन WritebackMinVSCLRatio;
	द्विगुन WritebackMaxHSCLRatio;
	द्विगुन WritebackMaxVSCLRatio;
	द्विगुन WritebackMaxHSCLTaps;
	द्विगुन WritebackMaxVSCLTaps;
	अचिन्हित पूर्णांक MaxNumDPP;
	अचिन्हित पूर्णांक MaxNumOTG;
	द्विगुन CursorBufferSize;
	द्विगुन CursorChunkSize;
	अचिन्हित पूर्णांक Mode;
	द्विगुन OutputLinkDPLanes[DC__NUM_DPP__MAX];
	द्विगुन ForcedOutputLinkBPP[DC__NUM_DPP__MAX]; // Mode Support only
	द्विगुन ImmediateFlipBW[DC__NUM_DPP__MAX];
	द्विगुन MaxMaxVStartup[DC__VOLTAGE_STATES][2];

	द्विगुन WritebackLumaVExtra;
	द्विगुन WritebackChromaVExtra;
	द्विगुन WritebackRequiredDISPCLK;
	द्विगुन MaximumSwathWidthSupport;
	द्विगुन MaximumSwathWidthInDETBuffer;
	द्विगुन MaximumSwathWidthInLineBuffer;
	द्विगुन MaxDispclkRoundedDownToDFSGranularity;
	द्विगुन MaxDppclkRoundedDownToDFSGranularity;
	द्विगुन PlaneRequiredDISPCLKWithoutODMCombine;
	द्विगुन PlaneRequiredDISPCLKWithODMCombine;
	द्विगुन PlaneRequiredDISPCLK;
	द्विगुन TotalNumberOfActiveOTG;
	द्विगुन FECOverhead;
	द्विगुन EffectiveFECOverhead;
	द्विगुन Outbpp;
	अचिन्हित पूर्णांक OutbppDSC;
	द्विगुन TotalDSCUnitsRequired;
	द्विगुन bpp;
	अचिन्हित पूर्णांक slices;
	द्विगुन SwathWidthGranularityY;
	द्विगुन RoundedUpMaxSwathSizeBytesY;
	द्विगुन SwathWidthGranularityC;
	द्विगुन RoundedUpMaxSwathSizeBytesC;
	द्विगुन EffectiveDETLBLinesLuma;
	द्विगुन EffectiveDETLBLinesChroma;
	द्विगुन ProjectedDCFCLKDeepSleep[DC__VOLTAGE_STATES][2];
	द्विगुन PDEAndMetaPTEBytesPerFrameY;
	द्विगुन PDEAndMetaPTEBytesPerFrameC;
	अचिन्हित पूर्णांक MetaRowBytesY;
	अचिन्हित पूर्णांक MetaRowBytesC;
	अचिन्हित पूर्णांक DPTEBytesPerRowC;
	अचिन्हित पूर्णांक DPTEBytesPerRowY;
	द्विगुन ExtraLatency;
	द्विगुन TimeCalc;
	द्विगुन TWait;
	द्विगुन MaximumReadBandwidthWithPrefetch;
	द्विगुन MaximumReadBandwidthWithoutPrefetch;
	द्विगुन total_dcn_पढ़ो_bw_with_flip;
	द्विगुन total_dcn_पढ़ो_bw_with_flip_no_urgent_burst;
	द्विगुन FractionOfUrgentBandwidth;
	द्विगुन FractionOfUrgentBandwidthImmediateFlip; // Mode Support debugging output

	/* ms locals */
	द्विगुन IdealSDPPortBandwidthPerState[DC__VOLTAGE_STATES][2];
	अचिन्हित पूर्णांक NoOfDPP[DC__VOLTAGE_STATES][2][DC__NUM_DPP__MAX];
	पूर्णांक NoOfDPPThisState[DC__NUM_DPP__MAX];
	क्रमागत odm_combine_mode ODMCombineEnablePerState[DC__VOLTAGE_STATES][DC__NUM_DPP__MAX];
	द्विगुन SwathWidthYThisState[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक SwathHeightCPerState[DC__VOLTAGE_STATES][2][DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक SwathHeightYThisState[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक SwathHeightCThisState[DC__NUM_DPP__MAX];
	द्विगुन VRatioPreY[DC__VOLTAGE_STATES][2][DC__NUM_DPP__MAX];
	द्विगुन VRatioPreC[DC__VOLTAGE_STATES][2][DC__NUM_DPP__MAX];
	द्विगुन RequiredPrefetchPixelDataBWLuma[DC__VOLTAGE_STATES][2][DC__NUM_DPP__MAX];
	द्विगुन RequiredPrefetchPixelDataBWChroma[DC__VOLTAGE_STATES][2][DC__NUM_DPP__MAX];
	द्विगुन RequiredDPPCLK[DC__VOLTAGE_STATES][2][DC__NUM_DPP__MAX];
	द्विगुन RequiredDPPCLKThisState[DC__NUM_DPP__MAX];
	bool PTEBufferSizeNotExceededY[DC__VOLTAGE_STATES][2][DC__NUM_DPP__MAX];
	bool PTEBufferSizeNotExceededC[DC__VOLTAGE_STATES][2][DC__NUM_DPP__MAX];
	bool BandwidthWithoutPrefetchSupported[DC__VOLTAGE_STATES][2];
	bool PrefetchSupported[DC__VOLTAGE_STATES][2];
	bool VRatioInPrefetchSupported[DC__VOLTAGE_STATES][2];
	द्विगुन RequiredDISPCLK[DC__VOLTAGE_STATES][2];
	bool DISPCLK_DPPCLK_Support[DC__VOLTAGE_STATES][2];
	bool TotalAvailablePipesSupport[DC__VOLTAGE_STATES][2];
	अचिन्हित पूर्णांक TotalNumberOfActiveDPP[DC__VOLTAGE_STATES][2];
	अचिन्हित पूर्णांक TotalNumberOfDCCActiveDPP[DC__VOLTAGE_STATES][2];
	bool ModeSupport[DC__VOLTAGE_STATES][2];
	द्विगुन ReturnBWPerState[DC__VOLTAGE_STATES][2];
	bool DIOSupport[DC__VOLTAGE_STATES];
	bool NotEnoughDSCUnits[DC__VOLTAGE_STATES];
	bool DSCCLKRequiredMoreThanSupported[DC__VOLTAGE_STATES];
	bool DTBCLKRequiredMoreThanSupported[DC__VOLTAGE_STATES];
	द्विगुन UrgentRoundTripAndOutOfOrderLatencyPerState[DC__VOLTAGE_STATES];
	bool ROBSupport[DC__VOLTAGE_STATES][2];
	bool PTEBufferSizeNotExceeded[DC__VOLTAGE_STATES][2];
	bool TotalVerticalActiveBandwidthSupport[DC__VOLTAGE_STATES][2];
	द्विगुन MaxTotalVerticalActiveAvailableBandwidth[DC__VOLTAGE_STATES][2];
	द्विगुन PrefetchBW[DC__NUM_DPP__MAX];
	द्विगुन PDEAndMetaPTEBytesPerFrame[DC__VOLTAGE_STATES][2][DC__NUM_DPP__MAX];
	द्विगुन MetaRowBytes[DC__VOLTAGE_STATES][2][DC__NUM_DPP__MAX];
	द्विगुन DPTEBytesPerRow[DC__VOLTAGE_STATES][2][DC__NUM_DPP__MAX];
	द्विगुन PrefetchLinesY[DC__VOLTAGE_STATES][2][DC__NUM_DPP__MAX];
	द्विगुन PrefetchLinesC[DC__VOLTAGE_STATES][2][DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक MaxNumSwY[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक MaxNumSwC[DC__NUM_DPP__MAX];
	द्विगुन PrefillY[DC__NUM_DPP__MAX];
	द्विगुन PrefillC[DC__NUM_DPP__MAX];
	द्विगुन LineTimesForPrefetch[DC__NUM_DPP__MAX];
	द्विगुन LinesForMetaPTE[DC__NUM_DPP__MAX];
	द्विगुन LinesForMetaAndDPTERow[DC__NUM_DPP__MAX];
	द्विगुन MinDPPCLKUsingSingleDPP[DC__NUM_DPP__MAX];
	द्विगुन SwathWidthYSingleDPP[DC__NUM_DPP__MAX];
	द्विगुन BytePerPixelInDETY[DC__NUM_DPP__MAX];
	द्विगुन BytePerPixelInDETC[DC__NUM_DPP__MAX];
	bool RequiresDSC[DC__VOLTAGE_STATES][DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक NumberOfDSCSlice[DC__VOLTAGE_STATES][DC__NUM_DPP__MAX];
	द्विगुन RequiresFEC[DC__VOLTAGE_STATES][DC__NUM_DPP__MAX];
	द्विगुन OutputBppPerState[DC__VOLTAGE_STATES][DC__NUM_DPP__MAX];
	द्विगुन DSCDelayPerState[DC__VOLTAGE_STATES][DC__NUM_DPP__MAX];
	bool ViewportSizeSupport[DC__VOLTAGE_STATES][2];
	अचिन्हित पूर्णांक Read256BlockHeightY[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक Read256BlockWidthY[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक Read256BlockHeightC[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक Read256BlockWidthC[DC__NUM_DPP__MAX];
	द्विगुन MaxSwathHeightY[DC__NUM_DPP__MAX];
	द्विगुन MaxSwathHeightC[DC__NUM_DPP__MAX];
	द्विगुन MinSwathHeightY[DC__NUM_DPP__MAX];
	द्विगुन MinSwathHeightC[DC__NUM_DPP__MAX];
	द्विगुन ReadBandwidthLuma[DC__NUM_DPP__MAX];
	द्विगुन ReadBandwidthChroma[DC__NUM_DPP__MAX];
	द्विगुन ReadBandwidth[DC__NUM_DPP__MAX];
	द्विगुन WriteBandwidth[DC__NUM_DPP__MAX];
	द्विगुन PSCL_FACTOR[DC__NUM_DPP__MAX];
	द्विगुन PSCL_FACTOR_CHROMA[DC__NUM_DPP__MAX];
	द्विगुन MaximumVStartup[DC__VOLTAGE_STATES][2][DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक MacroTileWidthY[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक MacroTileWidthC[DC__NUM_DPP__MAX];
	द्विगुन AlignedDCCMetaPitch[DC__NUM_DPP__MAX];
	द्विगुन AlignedYPitch[DC__NUM_DPP__MAX];
	द्विगुन AlignedCPitch[DC__NUM_DPP__MAX];
	द्विगुन MaximumSwathWidth[DC__NUM_DPP__MAX];
	द्विगुन cursor_bw[DC__NUM_DPP__MAX];
	द्विगुन cursor_bw_pre[DC__NUM_DPP__MAX];
	द्विगुन Tno_bw[DC__NUM_DPP__MAX];
	द्विगुन prefetch_vmrow_bw[DC__NUM_DPP__MAX];
	द्विगुन DestinationLinesToRequestVMInImmediateFlip[DC__NUM_DPP__MAX];
	द्विगुन DestinationLinesToRequestRowInImmediateFlip[DC__NUM_DPP__MAX];
	द्विगुन final_flip_bw[DC__NUM_DPP__MAX];
	bool ImmediateFlipSupportedForState[DC__VOLTAGE_STATES][2];
	द्विगुन WritebackDelay[DC__VOLTAGE_STATES][DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक vm_group_bytes[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक dpte_group_bytes[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक dpte_row_height[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक meta_req_height[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक meta_req_width[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक meta_row_height[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक meta_row_width[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक dpte_row_height_chroma[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक meta_req_height_chroma[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक meta_req_width_chroma[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक meta_row_height_chroma[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक meta_row_width_chroma[DC__NUM_DPP__MAX];
	bool ImmediateFlipSupportedForPipe[DC__NUM_DPP__MAX];
	द्विगुन meta_row_bw[DC__NUM_DPP__MAX];
	द्विगुन dpte_row_bw[DC__NUM_DPP__MAX];
	द्विगुन DisplayPipeLineDeliveryTimeLuma[DC__NUM_DPP__MAX];                     // WM
	द्विगुन DisplayPipeLineDeliveryTimeChroma[DC__NUM_DPP__MAX];                     // WM
	द्विगुन DisplayPipeRequestDeliveryTimeLuma[DC__NUM_DPP__MAX];
	द्विगुन DisplayPipeRequestDeliveryTimeChroma[DC__NUM_DPP__MAX];
	क्रमागत घड़ी_change_support DRAMClockChangeSupport[DC__VOLTAGE_STATES][2];
	द्विगुन UrgentBurstFactorCursor[DC__NUM_DPP__MAX];
	द्विगुन UrgentBurstFactorCursorPre[DC__NUM_DPP__MAX];
	द्विगुन UrgentBurstFactorLuma[DC__NUM_DPP__MAX];
	द्विगुन UrgentBurstFactorLumaPre[DC__NUM_DPP__MAX];
	द्विगुन UrgentBurstFactorChroma[DC__NUM_DPP__MAX];
	द्विगुन UrgentBurstFactorChromaPre[DC__NUM_DPP__MAX];


	bool           MPCCombine[DC__VOLTAGE_STATES][2][DC__NUM_DPP__MAX];
	द्विगुन         SwathWidthCSingleDPP[DC__NUM_DPP__MAX];
	द्विगुन         MaximumSwathWidthInLineBufferLuma;
	द्विगुन         MaximumSwathWidthInLineBufferChroma;
	द्विगुन         MaximumSwathWidthLuma[DC__NUM_DPP__MAX];
	द्विगुन         MaximumSwathWidthChroma[DC__NUM_DPP__MAX];
	क्रमागत odm_combine_mode odm_combine_dummy[DC__NUM_DPP__MAX];
	द्विगुन         dummy1[DC__NUM_DPP__MAX];
	द्विगुन         dummy2[DC__NUM_DPP__MAX];
	द्विगुन         dummy3[DC__NUM_DPP__MAX];
	द्विगुन         dummy4[DC__NUM_DPP__MAX];
	द्विगुन         dummy5;
	द्विगुन         dummy6;
	द्विगुन         dummy7[DC__NUM_DPP__MAX];
	द्विगुन         dummy8[DC__NUM_DPP__MAX];
	द्विगुन         dummy13[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक        dummyपूर्णांकeger1ms[DC__NUM_DPP__MAX];
	द्विगुन        dummyपूर्णांकeger2ms[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक        dummyपूर्णांकeger3[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक        dummyपूर्णांकeger4[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक        dummyपूर्णांकeger5;
	अचिन्हित पूर्णांक        dummyपूर्णांकeger6;
	अचिन्हित पूर्णांक        dummyपूर्णांकeger7;
	अचिन्हित पूर्णांक        dummyपूर्णांकeger8;
	अचिन्हित पूर्णांक        dummyपूर्णांकeger9;
	अचिन्हित पूर्णांक        dummyपूर्णांकeger10;
	अचिन्हित पूर्णांक        dummyपूर्णांकeger11;
	अचिन्हित पूर्णांक        dummyपूर्णांकeger12;
	अचिन्हित पूर्णांक        dummyपूर्णांकeger30;
	अचिन्हित पूर्णांक        dummyपूर्णांकeger31;
	अचिन्हित पूर्णांक        dummyपूर्णांकeger32;
	अचिन्हित पूर्णांक        dummyपूर्णांकegerarr1[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक        dummyपूर्णांकegerarr2[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक        dummyपूर्णांकegerarr3[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक        dummyपूर्णांकegerarr4[DC__NUM_DPP__MAX];
	bool           dummysinglestring;
	bool           SingleDPPViewportSizeSupportPerPlane[DC__NUM_DPP__MAX];
	द्विगुन         PlaneRequiredDISPCLKWithODMCombine2To1;
	द्विगुन         PlaneRequiredDISPCLKWithODMCombine4To1;
	अचिन्हित पूर्णांक   TotalNumberOfSingleDPPPlanes[DC__VOLTAGE_STATES][2];
	bool           LinkDSCEnable;
	bool           ODMCombine4To1SupportCheckOK[DC__VOLTAGE_STATES];
	क्रमागत odm_combine_mode ODMCombineEnableThisState[DC__NUM_DPP__MAX];
	द्विगुन   SwathWidthCThisState[DC__NUM_DPP__MAX];
	bool           ViewportSizeSupportPerPlane[DC__NUM_DPP__MAX];
	द्विगुन         AlignedDCCMetaPitchY[DC__NUM_DPP__MAX];
	द्विगुन         AlignedDCCMetaPitchC[DC__NUM_DPP__MAX];

	अचिन्हित पूर्णांक NotEnoughUrgentLatencyHiding;
	अचिन्हित पूर्णांक NotEnoughUrgentLatencyHidingPre;
	पूर्णांक PTEBufferSizeInRequestsForLuma;
	पूर्णांक PTEBufferSizeInRequestsForChroma;

	// Missing from VBA
	पूर्णांक dpte_group_bytes_chroma;
	अचिन्हित पूर्णांक vm_group_bytes_chroma;
	द्विगुन dst_x_after_scaler;
	द्विगुन dst_y_after_scaler;
	अचिन्हित पूर्णांक VStartupRequiredWhenNotEnoughTimeForDynamicMetadata;

	/* perf locals*/
	द्विगुन PrefetchBandwidth[DC__NUM_DPP__MAX];
	द्विगुन VInitPreFillY[DC__NUM_DPP__MAX];
	द्विगुन VInitPreFillC[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक MaxNumSwathY[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक MaxNumSwathC[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक VStartup[DC__NUM_DPP__MAX];
	द्विगुन DSTYAfterScaler[DC__NUM_DPP__MAX];
	द्विगुन DSTXAfterScaler[DC__NUM_DPP__MAX];
	bool AllowDRAMClockChangeDuringVBlank[DC__NUM_DPP__MAX];
	bool AllowDRAMSelfRefreshDuringVBlank[DC__NUM_DPP__MAX];
	द्विगुन VRatioPrefetchY[DC__NUM_DPP__MAX];
	द्विगुन VRatioPrefetchC[DC__NUM_DPP__MAX];
	द्विगुन DestinationLinesForPrefetch[DC__NUM_DPP__MAX];
	द्विगुन DestinationLinesToRequestVMInVBlank[DC__NUM_DPP__MAX];
	द्विगुन DestinationLinesToRequestRowInVBlank[DC__NUM_DPP__MAX];
	द्विगुन MinTTUVBlank[DC__NUM_DPP__MAX];
	द्विगुन BytePerPixelDETY[DC__NUM_DPP__MAX];
	द्विगुन BytePerPixelDETC[DC__NUM_DPP__MAX];
	द्विगुन SwathWidthY[DC__NUM_DPP__MAX];
	द्विगुन SwathWidthSingleDPPY[DC__NUM_DPP__MAX];
	द्विगुन CursorRequestDeliveryTime[DC__NUM_DPP__MAX];
	द्विगुन CursorRequestDeliveryTimePrefetch[DC__NUM_DPP__MAX];
	द्विगुन ReadBandwidthPlaneLuma[DC__NUM_DPP__MAX];
	द्विगुन ReadBandwidthPlaneChroma[DC__NUM_DPP__MAX];
	द्विगुन DisplayPipeLineDeliveryTimeLumaPrefetch[DC__NUM_DPP__MAX];
	द्विगुन DisplayPipeLineDeliveryTimeChromaPrefetch[DC__NUM_DPP__MAX];
	द्विगुन DisplayPipeRequestDeliveryTimeLumaPrefetch[DC__NUM_DPP__MAX];
	द्विगुन DisplayPipeRequestDeliveryTimeChromaPrefetch[DC__NUM_DPP__MAX];
	द्विगुन PixelPTEBytesPerRow[DC__NUM_DPP__MAX];
	द्विगुन PDEAndMetaPTEBytesFrame[DC__NUM_DPP__MAX];
	द्विगुन MetaRowByte[DC__NUM_DPP__MAX];
	द्विगुन PrefetchSourceLinesY[DC__NUM_DPP__MAX];
	द्विगुन RequiredPrefetchPixDataBWLuma[DC__NUM_DPP__MAX];
	द्विगुन RequiredPrefetchPixDataBWChroma[DC__NUM_DPP__MAX];
	द्विगुन PrefetchSourceLinesC[DC__NUM_DPP__MAX];
	द्विगुन PSCL_THROUGHPUT_LUMA[DC__NUM_DPP__MAX];
	द्विगुन PSCL_THROUGHPUT_CHROMA[DC__NUM_DPP__MAX];
	द्विगुन DSCCLK_calculated[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक DSCDelay[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक MaxVStartupLines[DC__NUM_DPP__MAX];
	द्विगुन DPPCLKUsingSingleDPP[DC__NUM_DPP__MAX];
	द्विगुन DPPCLK[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक DCCYMaxUncompressedBlock[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक DCCYMaxCompressedBlock[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक DCCYIndependent64ByteBlock[DC__NUM_DPP__MAX];
	द्विगुन MaximumDCCCompressionYSurface[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक BlockHeight256BytesY[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक BlockHeight256BytesC[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक BlockWidth256BytesY[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक BlockWidth256BytesC[DC__NUM_DPP__MAX];
	द्विगुन XFCSlaveVUpdateOffset[DC__NUM_DPP__MAX];
	द्विगुन XFCSlaveVupdateWidth[DC__NUM_DPP__MAX];
	द्विगुन XFCSlaveVReadyOffset[DC__NUM_DPP__MAX];
	द्विगुन XFCTransferDelay[DC__NUM_DPP__MAX];
	द्विगुन XFCPreअक्षरgeDelay[DC__NUM_DPP__MAX];
	द्विगुन XFCRemoteSurfaceFlipLatency[DC__NUM_DPP__MAX];
	द्विगुन XFCPrefetchMargin[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक dpte_row_width_luma_ub[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक dpte_row_width_chroma_ub[DC__NUM_DPP__MAX];
	द्विगुन FullDETBufferingTimeY[DC__NUM_DPP__MAX];                     // WM
	द्विगुन FullDETBufferingTimeC[DC__NUM_DPP__MAX];                     // WM
	द्विगुन DST_Y_PER_PTE_ROW_NOM_L[DC__NUM_DPP__MAX];
	द्विगुन DST_Y_PER_PTE_ROW_NOM_C[DC__NUM_DPP__MAX];
	द्विगुन DST_Y_PER_META_ROW_NOM_L[DC__NUM_DPP__MAX];
	द्विगुन TimePerMetaChunkNominal[DC__NUM_DPP__MAX];
	द्विगुन TimePerMetaChunkVBlank[DC__NUM_DPP__MAX];
	द्विगुन TimePerMetaChunkFlip[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक swath_width_luma_ub[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक swath_width_chroma_ub[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक PixelPTEReqWidthY[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक PixelPTEReqHeightY[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक PTERequestSizeY[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक PixelPTEReqWidthC[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक PixelPTEReqHeightC[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक PTERequestSizeC[DC__NUM_DPP__MAX];
	द्विगुन समय_per_pte_group_nom_luma[DC__NUM_DPP__MAX];
	द्विगुन समय_per_pte_group_nom_chroma[DC__NUM_DPP__MAX];
	द्विगुन समय_per_pte_group_vblank_luma[DC__NUM_DPP__MAX];
	द्विगुन समय_per_pte_group_vblank_chroma[DC__NUM_DPP__MAX];
	द्विगुन समय_per_pte_group_flip_luma[DC__NUM_DPP__MAX];
	द्विगुन समय_per_pte_group_flip_chroma[DC__NUM_DPP__MAX];
	द्विगुन TimePerVMGroupVBlank[DC__NUM_DPP__MAX];
	द्विगुन TimePerVMGroupFlip[DC__NUM_DPP__MAX];
	द्विगुन TimePerVMRequestVBlank[DC__NUM_DPP__MAX];
	द्विगुन TimePerVMRequestFlip[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक dpde0_bytes_per_frame_ub_l[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक meta_pte_bytes_per_frame_ub_l[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक dpde0_bytes_per_frame_ub_c[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक meta_pte_bytes_per_frame_ub_c[DC__NUM_DPP__MAX];
	द्विगुन LinesToFinishSwathTransferStutterCriticalPlane;
	अचिन्हित पूर्णांक BytePerPixelYCriticalPlane;
	द्विगुन SwathWidthYCriticalPlane;
	द्विगुन LinesInDETY[DC__NUM_DPP__MAX];
	द्विगुन LinesInDETYRoundedDownToSwath[DC__NUM_DPP__MAX];

	द्विगुन SwathWidthSingleDPPC[DC__NUM_DPP__MAX];
	द्विगुन SwathWidthC[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक BytePerPixelY[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक BytePerPixelC[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक dummyपूर्णांकeger1;
	अचिन्हित पूर्णांक dummyपूर्णांकeger2;
	द्विगुन FinalDRAMClockChangeLatency;
	द्विगुन Tdmdl_vm[DC__NUM_DPP__MAX];
	द्विगुन Tdmdl[DC__NUM_DPP__MAX];
	द्विगुन TSetup[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक ThisVStartup;
	bool WritebackAllowDRAMClockChangeEndPosition[DC__NUM_DPP__MAX];
	द्विगुन DST_Y_PER_META_ROW_NOM_C[DC__NUM_DPP__MAX];
	द्विगुन TimePerChromaMetaChunkNominal[DC__NUM_DPP__MAX];
	द्विगुन TimePerChromaMetaChunkVBlank[DC__NUM_DPP__MAX];
	द्विगुन TimePerChromaMetaChunkFlip[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक DCCCMaxUncompressedBlock[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक DCCCMaxCompressedBlock[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक DCCCIndependent64ByteBlock[DC__NUM_DPP__MAX];
	द्विगुन VStartupMargin;
	bool NotEnoughTimeForDynamicMetadata[DC__NUM_DPP__MAX];

	/* Missing from VBA */
	अचिन्हित पूर्णांक MaximumMaxVStartupLines;
	द्विगुन FabricAndDRAMBandwidth;
	द्विगुन LinesInDETLuma;
	द्विगुन LinesInDETChroma;
	अचिन्हित पूर्णांक ImmediateFlipBytes[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक LinesInDETC[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक LinesInDETCRoundedDownToSwath[DC__NUM_DPP__MAX];
	द्विगुन UrgentLatencySupportUsPerState[DC__VOLTAGE_STATES][2][DC__NUM_DPP__MAX];
	द्विगुन UrgentLatencySupportUs[DC__NUM_DPP__MAX];
	द्विगुन FabricAndDRAMBandwidthPerState[DC__VOLTAGE_STATES];
	bool UrgentLatencySupport[DC__VOLTAGE_STATES][2];
	अचिन्हित पूर्णांक SwathWidthYPerState[DC__VOLTAGE_STATES][2][DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक SwathHeightYPerState[DC__VOLTAGE_STATES][2][DC__NUM_DPP__MAX];
	द्विगुन qual_row_bw[DC__NUM_DPP__MAX];
	द्विगुन prefetch_row_bw[DC__NUM_DPP__MAX];
	द्विगुन prefetch_vm_bw[DC__NUM_DPP__MAX];

	द्विगुन PTEGroupSize;
	अचिन्हित पूर्णांक PDEProcessingBufIn64KBReqs;

	द्विगुन MaxTotalVActiveRDBandwidth;
	bool DoUrgentLatencyAdjusपंचांगent;
	द्विगुन UrgentLatencyAdjusपंचांगentFabricClockComponent;
	द्विगुन UrgentLatencyAdjusपंचांगentFabricClockReference;
	द्विगुन MinUrgentLatencySupportUs;
	द्विगुन MinFullDETBufferingTime;
	द्विगुन AverageReadBandwidthGBytePerSecond;
	bool   FirstMainPlane;

	अचिन्हित पूर्णांक ViewportWidthChroma[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक ViewportHeightChroma[DC__NUM_DPP__MAX];
	द्विगुन HRatioChroma[DC__NUM_DPP__MAX];
	द्विगुन VRatioChroma[DC__NUM_DPP__MAX];
	पूर्णांक WritebackSourceWidth[DC__NUM_DPP__MAX];

	bool ModeIsSupported;
	bool ODMCombine4To1Supported;

	अचिन्हित पूर्णांक SurfaceWidthY[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक SurfaceWidthC[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक SurfaceHeightY[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक SurfaceHeightC[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक WritebackHTaps[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक WritebackVTaps[DC__NUM_DPP__MAX];
	bool DSCEnable[DC__NUM_DPP__MAX];

	द्विगुन DRAMClockChangeLatencyOverride;

	द्विगुन GPUVMMinPageSize;
	द्विगुन HostVMMinPageSize;

	bool   MPCCombineEnable[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक HostVMMaxNonCachedPageTableLevels;
	bool   DynamicMetadataVMEnabled;
	द्विगुन       WritebackInterfaceBufferSize;
	द्विगुन       WritebackLineBufferSize;

	द्विगुन DCCRateLuma[DC__NUM_DPP__MAX];
	द्विगुन DCCRateChroma[DC__NUM_DPP__MAX];

	द्विगुन PHYCLKD18PerState[DC__VOLTAGE_STATES];

	bool WritebackSupportInterleaveAndUsingWholeBufferForASingleStream;
	bool NumberOfHDMIFRLSupport;
	अचिन्हित पूर्णांक MaxNumHDMIFRLOutमाला_दो;
	पूर्णांक    AudioSampleRate[DC__NUM_DPP__MAX];
	पूर्णांक    AudioSampleLayout[DC__NUM_DPP__MAX];

	पूर्णांक PercentMarginOverMinimumRequiredDCFCLK;
	bool DynamicMetadataSupported[DC__VOLTAGE_STATES][2];
	क्रमागत immediate_flip_requirement ImmediateFlipRequirement;
	द्विगुन DETBufferSizeYThisState[DC__NUM_DPP__MAX];
	द्विगुन DETBufferSizeCThisState[DC__NUM_DPP__MAX];
	bool NoUrgentLatencyHiding[DC__NUM_DPP__MAX];
	bool NoUrgentLatencyHidingPre[DC__NUM_DPP__MAX];
	पूर्णांक swath_width_luma_ub_this_state[DC__NUM_DPP__MAX];
	पूर्णांक swath_width_chroma_ub_this_state[DC__NUM_DPP__MAX];
	द्विगुन UrgLatency[DC__VOLTAGE_STATES];
	द्विगुन VActiveCursorBandwidth[DC__VOLTAGE_STATES][2][DC__NUM_DPP__MAX];
	द्विगुन VActivePixelBandwidth[DC__VOLTAGE_STATES][2][DC__NUM_DPP__MAX];
	bool NoTimeForPrefetch[DC__VOLTAGE_STATES][2][DC__NUM_DPP__MAX];
	bool NoTimeForDynamicMetadata[DC__VOLTAGE_STATES][2][DC__NUM_DPP__MAX];
	द्विगुन dpte_row_bandwidth[DC__VOLTAGE_STATES][2][DC__NUM_DPP__MAX];
	द्विगुन meta_row_bandwidth[DC__VOLTAGE_STATES][2][DC__NUM_DPP__MAX];
	द्विगुन DETBufferSizeYAllStates[DC__VOLTAGE_STATES][2][DC__NUM_DPP__MAX];
	द्विगुन DETBufferSizeCAllStates[DC__VOLTAGE_STATES][2][DC__NUM_DPP__MAX];
	पूर्णांक swath_width_luma_ub_all_states[DC__VOLTAGE_STATES][2][DC__NUM_DPP__MAX];
	पूर्णांक swath_width_chroma_ub_all_states[DC__VOLTAGE_STATES][2][DC__NUM_DPP__MAX];
	bool NotUrgentLatencyHiding[DC__VOLTAGE_STATES][2];
	अचिन्हित पूर्णांक SwathHeightYAllStates[DC__VOLTAGE_STATES][2][DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक SwathHeightCAllStates[DC__VOLTAGE_STATES][2][DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक SwathWidthYAllStates[DC__VOLTAGE_STATES][2][DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक SwathWidthCAllStates[DC__VOLTAGE_STATES][2][DC__NUM_DPP__MAX];
	द्विगुन TotalDPTERowBandwidth[DC__VOLTAGE_STATES][2];
	द्विगुन TotalMetaRowBandwidth[DC__VOLTAGE_STATES][2];
	द्विगुन TotalVActiveCursorBandwidth[DC__VOLTAGE_STATES][2];
	द्विगुन TotalVActivePixelBandwidth[DC__VOLTAGE_STATES][2];
	द्विगुन WritebackDelayTime[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक DCCYIndependentBlock[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक DCCCIndependentBlock[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक dummyपूर्णांकeger15;
	अचिन्हित पूर्णांक dummyपूर्णांकeger16;
	अचिन्हित पूर्णांक dummyपूर्णांकeger17;
	अचिन्हित पूर्णांक dummyपूर्णांकeger18;
	अचिन्हित पूर्णांक dummyपूर्णांकeger19;
	अचिन्हित पूर्णांक dummyपूर्णांकeger20;
	अचिन्हित पूर्णांक dummyपूर्णांकeger21;
	अचिन्हित पूर्णांक dummyपूर्णांकeger22;
	अचिन्हित पूर्णांक dummyपूर्णांकeger23;
	अचिन्हित पूर्णांक dummyपूर्णांकeger24;
	अचिन्हित पूर्णांक dummyपूर्णांकeger25;
	अचिन्हित पूर्णांक dummyपूर्णांकeger26;
	अचिन्हित पूर्णांक dummyपूर्णांकeger27;
	अचिन्हित पूर्णांक dummyपूर्णांकeger28;
	अचिन्हित पूर्णांक dummyपूर्णांकeger29;
	bool dummystring[DC__NUM_DPP__MAX];
	द्विगुन BPP;
	क्रमागत odm_combine_policy ODMCombinePolicy;
	bool UseMinimumRequiredDCFCLK;
	bool ClampMinDCFCLK;
	bool AllowDramClockChangeOneDisplayVactive;

पूर्ण;

bool CalculateMinAndMaxPrefetchMode(
		क्रमागत self_refresh_affinity AllowDRAMSelfRefreshOrDRAMClockChangeInVblank,
		अचिन्हित पूर्णांक *MinPrefetchMode,
		अचिन्हित पूर्णांक *MaxPrefetchMode);

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
		अचिन्हित पूर्णांक WritebackChromaLineBufferWidth);

#पूर्ण_अगर /* _DML2_DISPLAY_MODE_VBA_H_ */
