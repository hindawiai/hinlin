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


#समावेश "../display_mode_lib.h"
#समावेश "../dml_inline_defs.h"
#समावेश "../display_mode_vba.h"
#समावेश "display_mode_vba_21.h"


/*
 * NOTE:
 *   This file is gcc-parsable HW gospel, coming straight from HW engineers.
 *
 * It करोesn't adhere to Linux kernel style and someबार will करो things in odd
 * ways. Unless there is something clearly wrong with it the code should
 * reमुख्य as-is as it provides us with a guarantee from HW that it is correct.
 */
प्रकार काष्ठा अणु
	द्विगुन DPPCLK;
	द्विगुन DISPCLK;
	द्विगुन PixelClock;
	द्विगुन DCFCLKDeepSleep;
	अचिन्हित पूर्णांक DPPPerPlane;
	bool ScalerEnabled;
	क्रमागत scan_direction_class SourceScan;
	अचिन्हित पूर्णांक BlockWidth256BytesY;
	अचिन्हित पूर्णांक BlockHeight256BytesY;
	अचिन्हित पूर्णांक BlockWidth256BytesC;
	अचिन्हित पूर्णांक BlockHeight256BytesC;
	अचिन्हित पूर्णांक InterlaceEnable;
	अचिन्हित पूर्णांक NumberOfCursors;
	अचिन्हित पूर्णांक VBlank;
	अचिन्हित पूर्णांक HTotal;
पूर्ण Pipe;

प्रकार काष्ठा अणु
	bool Enable;
	अचिन्हित पूर्णांक MaxPageTableLevels;
	अचिन्हित पूर्णांक CachedPageTableLevels;
पूर्ण HostVM;

#घोषणा BPP_INVALID 0
#घोषणा BPP_BLENDED_PIPE 0xffffffff
#घोषणा DCN21_MAX_DSC_IMAGE_WIDTH 5184
#घोषणा DCN21_MAX_420_IMAGE_WIDTH 4096

अटल व्योम DisplayPipeConfiguration(काष्ठा display_mode_lib *mode_lib);
अटल व्योम DISPCLKDPPCLKDCFCLKDeepSleepPrefetchParametersWatermarksAndPerक्रमmanceCalculation(
		काष्ठा display_mode_lib *mode_lib);
अटल अचिन्हित पूर्णांक dscceComputeDelay(
		अचिन्हित पूर्णांक bpc,
		द्विगुन bpp,
		अचिन्हित पूर्णांक sliceWidth,
		अचिन्हित पूर्णांक numSlices,
		क्रमागत output_क्रमmat_class pixelFormat);
अटल अचिन्हित पूर्णांक dscComputeDelay(क्रमागत output_क्रमmat_class pixelFormat);
// Super monster function with some 45 argument
अटल bool CalculatePrefetchSchedule(
		काष्ठा display_mode_lib *mode_lib,
		द्विगुन PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData,
		द्विगुन PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly,
		Pipe *myPipe,
		अचिन्हित पूर्णांक DSCDelay,
		द्विगुन DPPCLKDelaySubtotal,
		द्विगुन DPPCLKDelaySCL,
		द्विगुन DPPCLKDelaySCLLBOnly,
		द्विगुन DPPCLKDelayCNVCFormater,
		द्विगुन DPPCLKDelayCNVCCursor,
		द्विगुन DISPCLKDelaySubtotal,
		अचिन्हित पूर्णांक ScalerRecoutWidth,
		क्रमागत output_क्रमmat_class OutputFormat,
		अचिन्हित पूर्णांक MaxInterDCNTileRepeaters,
		अचिन्हित पूर्णांक VStartup,
		अचिन्हित पूर्णांक MaxVStartup,
		अचिन्हित पूर्णांक GPUVMPageTableLevels,
		bool GPUVMEnable,
		HostVM *myHostVM,
		bool DynamicMetadataEnable,
		पूर्णांक DynamicMetadataLinesBeक्रमeActiveRequired,
		अचिन्हित पूर्णांक DynamicMetadataTransmittedBytes,
		bool DCCEnable,
		द्विगुन UrgentLatency,
		द्विगुन UrgentExtraLatency,
		द्विगुन TCalc,
		अचिन्हित पूर्णांक PDEAndMetaPTEBytesFrame,
		अचिन्हित पूर्णांक MetaRowByte,
		अचिन्हित पूर्णांक PixelPTEBytesPerRow,
		द्विगुन PrefetchSourceLinesY,
		अचिन्हित पूर्णांक SwathWidthY,
		द्विगुन BytePerPixelDETY,
		द्विगुन VInitPreFillY,
		अचिन्हित पूर्णांक MaxNumSwathY,
		द्विगुन PrefetchSourceLinesC,
		द्विगुन BytePerPixelDETC,
		द्विगुन VInitPreFillC,
		अचिन्हित पूर्णांक MaxNumSwathC,
		अचिन्हित पूर्णांक SwathHeightY,
		अचिन्हित पूर्णांक SwathHeightC,
		द्विगुन TWait,
		bool XFCEnabled,
		द्विगुन XFCRemoteSurfaceFlipDelay,
		bool ProgressiveToInterlaceUnitInOPP,
		द्विगुन *DSTXAfterScaler,
		द्विगुन *DSTYAfterScaler,
		द्विगुन *DestinationLinesForPrefetch,
		द्विगुन *PrefetchBandwidth,
		द्विगुन *DestinationLinesToRequestVMInVBlank,
		द्विगुन *DestinationLinesToRequestRowInVBlank,
		द्विगुन *VRatioPrefetchY,
		द्विगुन *VRatioPrefetchC,
		द्विगुन *RequiredPrefetchPixDataBWLuma,
		द्विगुन *RequiredPrefetchPixDataBWChroma,
		अचिन्हित पूर्णांक *VStartupRequiredWhenNotEnoughTimeForDynamicMetadata,
		द्विगुन *Tno_bw,
		द्विगुन *prefetch_vmrow_bw,
		अचिन्हित पूर्णांक *swath_width_luma_ub,
		अचिन्हित पूर्णांक *swath_width_chroma_ub,
		अचिन्हित पूर्णांक *VUpdateOffsetPix,
		द्विगुन *VUpdateWidthPix,
		द्विगुन *VReadyOffsetPix);
अटल द्विगुन RoundToDFSGranularityUp(द्विगुन Clock, द्विगुन VCOSpeed);
अटल द्विगुन RoundToDFSGranularityDown(द्विगुन Clock, द्विगुन VCOSpeed);
अटल द्विगुन CalculateDCCConfiguration(
		bool                 DCCEnabled,
		bool                 DCCProgrammingAssumesScanDirectionUnknown,
		अचिन्हित पूर्णांक         ViewportWidth,
		अचिन्हित पूर्णांक         ViewportHeight,
		द्विगुन               DETBufferSize,
		अचिन्हित पूर्णांक         RequestHeight256Byte,
		अचिन्हित पूर्णांक         SwathHeight,
		क्रमागत dm_swizzle_mode TilingFormat,
		अचिन्हित पूर्णांक         BytePerPixel,
		क्रमागत scan_direction_class ScanOrientation,
		अचिन्हित पूर्णांक        *MaxUncompressedBlock,
		अचिन्हित पूर्णांक        *MaxCompressedBlock,
		अचिन्हित पूर्णांक        *Independent64ByteBlock);
अटल द्विगुन CalculatePrefetchSourceLines(
		काष्ठा display_mode_lib *mode_lib,
		द्विगुन VRatio,
		द्विगुन vtaps,
		bool Interlace,
		bool ProgressiveToInterlaceUnitInOPP,
		अचिन्हित पूर्णांक SwathHeight,
		अचिन्हित पूर्णांक ViewportYStart,
		द्विगुन *VInitPreFill,
		अचिन्हित पूर्णांक *MaxNumSwath);
अटल अचिन्हित पूर्णांक CalculateVMAndRowBytes(
		काष्ठा display_mode_lib *mode_lib,
		bool DCCEnable,
		अचिन्हित पूर्णांक BlockHeight256Bytes,
		अचिन्हित पूर्णांक BlockWidth256Bytes,
		क्रमागत source_क्रमmat_class SourcePixelFormat,
		अचिन्हित पूर्णांक SurfaceTiling,
		अचिन्हित पूर्णांक BytePerPixel,
		क्रमागत scan_direction_class ScanDirection,
		अचिन्हित पूर्णांक ViewportWidth,
		अचिन्हित पूर्णांक ViewportHeight,
		अचिन्हित पूर्णांक SwathWidthY,
		bool GPUVMEnable,
		bool HostVMEnable,
		अचिन्हित पूर्णांक HostVMMaxPageTableLevels,
		अचिन्हित पूर्णांक HostVMCachedPageTableLevels,
		अचिन्हित पूर्णांक VMMPageSize,
		अचिन्हित पूर्णांक PTEBufferSizeInRequests,
		अचिन्हित पूर्णांक Pitch,
		अचिन्हित पूर्णांक DCCMetaPitch,
		अचिन्हित पूर्णांक *MacroTileWidth,
		अचिन्हित पूर्णांक *MetaRowByte,
		अचिन्हित पूर्णांक *PixelPTEBytesPerRow,
		bool *PTEBufferSizeNotExceeded,
		अचिन्हित पूर्णांक *dpte_row_width_ub,
		अचिन्हित पूर्णांक *dpte_row_height,
		अचिन्हित पूर्णांक *MetaRequestWidth,
		अचिन्हित पूर्णांक *MetaRequestHeight,
		अचिन्हित पूर्णांक *meta_row_width,
		अचिन्हित पूर्णांक *meta_row_height,
		अचिन्हित पूर्णांक *vm_group_bytes,
		अचिन्हित पूर्णांक *dpte_group_bytes,
		अचिन्हित पूर्णांक *PixelPTEReqWidth,
		अचिन्हित पूर्णांक *PixelPTEReqHeight,
		अचिन्हित पूर्णांक *PTERequestSize,
		अचिन्हित पूर्णांक *DPDE0BytesFrame,
		अचिन्हित पूर्णांक *MetaPTEBytesFrame);

अटल द्विगुन CalculateTWait(
		अचिन्हित पूर्णांक PrefetchMode,
		द्विगुन DRAMClockChangeLatency,
		द्विगुन UrgentLatency,
		द्विगुन SREnterPlusExitTime);
अटल द्विगुन CalculateRemoteSurfaceFlipDelay(
		काष्ठा display_mode_lib *mode_lib,
		द्विगुन VRatio,
		द्विगुन SwathWidth,
		द्विगुन Bpp,
		द्विगुन LineTime,
		द्विगुन XFCTSlvVupdateOffset,
		द्विगुन XFCTSlvVupdateWidth,
		द्विगुन XFCTSlvVपढ़ोyOffset,
		द्विगुन XFCXBUFLatencyTolerance,
		द्विगुन XFCFillBWOverhead,
		द्विगुन XFCSlvChunkSize,
		द्विगुन XFCBusTransportTime,
		द्विगुन TCalc,
		द्विगुन TWait,
		द्विगुन *SrcActiveDrainRate,
		द्विगुन *TInitXFill,
		द्विगुन *TslvChk);
अटल व्योम CalculateActiveRowBandwidth(
		bool GPUVMEnable,
		क्रमागत source_क्रमmat_class SourcePixelFormat,
		द्विगुन VRatio,
		bool DCCEnable,
		द्विगुन LineTime,
		अचिन्हित पूर्णांक MetaRowByteLuma,
		अचिन्हित पूर्णांक MetaRowByteChroma,
		अचिन्हित पूर्णांक meta_row_height_luma,
		अचिन्हित पूर्णांक meta_row_height_chroma,
		अचिन्हित पूर्णांक PixelPTEBytesPerRowLuma,
		अचिन्हित पूर्णांक PixelPTEBytesPerRowChroma,
		अचिन्हित पूर्णांक dpte_row_height_luma,
		अचिन्हित पूर्णांक dpte_row_height_chroma,
		द्विगुन *meta_row_bw,
		द्विगुन *dpte_row_bw);
अटल व्योम CalculateFlipSchedule(
		काष्ठा display_mode_lib *mode_lib,
		द्विगुन PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData,
		द्विगुन PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly,
		द्विगुन UrgentExtraLatency,
		द्विगुन UrgentLatency,
		अचिन्हित पूर्णांक GPUVMMaxPageTableLevels,
		bool HostVMEnable,
		अचिन्हित पूर्णांक HostVMMaxPageTableLevels,
		अचिन्हित पूर्णांक HostVMCachedPageTableLevels,
		bool GPUVMEnable,
		द्विगुन PDEAndMetaPTEBytesPerFrame,
		द्विगुन MetaRowBytes,
		द्विगुन DPTEBytesPerRow,
		द्विगुन BandwidthAvailableForImmediateFlip,
		अचिन्हित पूर्णांक TotImmediateFlipBytes,
		क्रमागत source_क्रमmat_class SourcePixelFormat,
		द्विगुन LineTime,
		द्विगुन VRatio,
		द्विगुन Tno_bw,
		bool DCCEnable,
		अचिन्हित पूर्णांक dpte_row_height,
		अचिन्हित पूर्णांक meta_row_height,
		अचिन्हित पूर्णांक dpte_row_height_chroma,
		अचिन्हित पूर्णांक meta_row_height_chroma,
		द्विगुन *DestinationLinesToRequestVMInImmediateFlip,
		द्विगुन *DestinationLinesToRequestRowInImmediateFlip,
		द्विगुन *final_flip_bw,
		bool *ImmediateFlipSupportedForPipe);
अटल द्विगुन CalculateWriteBackDelay(
		क्रमागत source_क्रमmat_class WritebackPixelFormat,
		द्विगुन WritebackHRatio,
		द्विगुन WritebackVRatio,
		अचिन्हित पूर्णांक WritebackLumaHTaps,
		अचिन्हित पूर्णांक WritebackLumaVTaps,
		अचिन्हित पूर्णांक WritebackChromaHTaps,
		अचिन्हित पूर्णांक WritebackChromaVTaps,
		अचिन्हित पूर्णांक WritebackDestinationWidth);
अटल व्योम CalculateWatermarksAndDRAMSpeedChangeSupport(
		काष्ठा display_mode_lib *mode_lib,
		अचिन्हित पूर्णांक PrefetchMode,
		अचिन्हित पूर्णांक NumberOfActivePlanes,
		अचिन्हित पूर्णांक MaxLineBufferLines,
		अचिन्हित पूर्णांक LineBufferSize,
		अचिन्हित पूर्णांक DPPOutputBufferPixels,
		द्विगुन DETBufferSizeInKByte,
		अचिन्हित पूर्णांक WritebackInterfaceLumaBufferSize,
		अचिन्हित पूर्णांक WritebackInterfaceChromaBufferSize,
		द्विगुन DCFCLK,
		द्विगुन UrgentOutOfOrderReturn,
		द्विगुन ReturnBW,
		bool GPUVMEnable,
		पूर्णांक dpte_group_bytes[],
		अचिन्हित पूर्णांक MetaChunkSize,
		द्विगुन UrgentLatency,
		द्विगुन ExtraLatency,
		द्विगुन WritebackLatency,
		द्विगुन WritebackChunkSize,
		द्विगुन SOCCLK,
		द्विगुन DRAMClockChangeLatency,
		द्विगुन SRExitTime,
		द्विगुन SREnterPlusExitTime,
		द्विगुन DCFCLKDeepSleep,
		पूर्णांक DPPPerPlane[],
		bool DCCEnable[],
		द्विगुन DPPCLK[],
		द्विगुन SwathWidthSingleDPPY[],
		अचिन्हित पूर्णांक SwathHeightY[],
		द्विगुन ReadBandwidthPlaneLuma[],
		अचिन्हित पूर्णांक SwathHeightC[],
		द्विगुन ReadBandwidthPlaneChroma[],
		अचिन्हित पूर्णांक LBBitPerPixel[],
		द्विगुन SwathWidthY[],
		द्विगुन HRatio[],
		अचिन्हित पूर्णांक vtaps[],
		अचिन्हित पूर्णांक VTAPsChroma[],
		द्विगुन VRatio[],
		अचिन्हित पूर्णांक HTotal[],
		द्विगुन PixelClock[],
		अचिन्हित पूर्णांक BlendingAndTiming[],
		द्विगुन BytePerPixelDETY[],
		द्विगुन BytePerPixelDETC[],
		bool WritebackEnable[],
		क्रमागत source_क्रमmat_class WritebackPixelFormat[],
		द्विगुन WritebackDestinationWidth[],
		द्विगुन WritebackDestinationHeight[],
		द्विगुन WritebackSourceHeight[],
		क्रमागत घड़ी_change_support *DRAMClockChangeSupport,
		द्विगुन *UrgentWatermark,
		द्विगुन *WritebackUrgentWatermark,
		द्विगुन *DRAMClockChangeWatermark,
		द्विगुन *WritebackDRAMClockChangeWatermark,
		द्विगुन *StutterExitWatermark,
		द्विगुन *StutterEnterPlusExitWatermark,
		द्विगुन *MinActiveDRAMClockChangeLatencySupported);
अटल व्योम CalculateDCFCLKDeepSleep(
		काष्ठा display_mode_lib *mode_lib,
		अचिन्हित पूर्णांक NumberOfActivePlanes,
		द्विगुन BytePerPixelDETY[],
		द्विगुन BytePerPixelDETC[],
		द्विगुन VRatio[],
		द्विगुन SwathWidthY[],
		पूर्णांक DPPPerPlane[],
		द्विगुन HRatio[],
		द्विगुन PixelClock[],
		द्विगुन PSCL_THROUGHPUT[],
		द्विगुन PSCL_THROUGHPUT_CHROMA[],
		द्विगुन DPPCLK[],
		द्विगुन *DCFCLKDeepSleep);
अटल व्योम CalculateDETBufferSize(
		द्विगुन DETBufferSizeInKByte,
		अचिन्हित पूर्णांक SwathHeightY,
		अचिन्हित पूर्णांक SwathHeightC,
		द्विगुन *DETBufferSizeY,
		द्विगुन *DETBufferSizeC);
अटल व्योम CalculateUrgentBurstFactor(
		अचिन्हित पूर्णांक DETBufferSizeInKByte,
		अचिन्हित पूर्णांक SwathHeightY,
		अचिन्हित पूर्णांक SwathHeightC,
		अचिन्हित पूर्णांक SwathWidthY,
		द्विगुन LineTime,
		द्विगुन UrgentLatency,
		द्विगुन CursorBufferSize,
		अचिन्हित पूर्णांक CursorWidth,
		अचिन्हित पूर्णांक CursorBPP,
		द्विगुन VRatio,
		द्विगुन VRatioPreY,
		द्विगुन VRatioPreC,
		द्विगुन BytePerPixelInDETY,
		द्विगुन BytePerPixelInDETC,
		द्विगुन *UrgentBurstFactorCursor,
		द्विगुन *UrgentBurstFactorCursorPre,
		द्विगुन *UrgentBurstFactorLuma,
		द्विगुन *UrgentBurstFactorLumaPre,
		द्विगुन *UrgentBurstFactorChroma,
		द्विगुन *UrgentBurstFactorChromaPre,
		अचिन्हित पूर्णांक *NotEnoughUrgentLatencyHiding,
		अचिन्हित पूर्णांक *NotEnoughUrgentLatencyHidingPre);

अटल व्योम CalculatePixelDeliveryTimes(
		अचिन्हित पूर्णांक           NumberOfActivePlanes,
		द्विगुन                 VRatio[],
		द्विगुन                 VRatioPrefetchY[],
		द्विगुन                 VRatioPrefetchC[],
		अचिन्हित पूर्णांक           swath_width_luma_ub[],
		अचिन्हित पूर्णांक           swath_width_chroma_ub[],
		पूर्णांक                    DPPPerPlane[],
		द्विगुन                 HRatio[],
		द्विगुन                 PixelClock[],
		द्विगुन                 PSCL_THROUGHPUT[],
		द्विगुन                 PSCL_THROUGHPUT_CHROMA[],
		द्विगुन                 DPPCLK[],
		द्विगुन                 BytePerPixelDETC[],
		क्रमागत scan_direction_class SourceScan[],
		अचिन्हित पूर्णांक           BlockWidth256BytesY[],
		अचिन्हित पूर्णांक           BlockHeight256BytesY[],
		अचिन्हित पूर्णांक           BlockWidth256BytesC[],
		अचिन्हित पूर्णांक           BlockHeight256BytesC[],
		द्विगुन                 DisplayPipeLineDeliveryTimeLuma[],
		द्विगुन                 DisplayPipeLineDeliveryTimeChroma[],
		द्विगुन                 DisplayPipeLineDeliveryTimeLumaPrefetch[],
		द्विगुन                 DisplayPipeLineDeliveryTimeChromaPrefetch[],
		द्विगुन                 DisplayPipeRequestDeliveryTimeLuma[],
		द्विगुन                 DisplayPipeRequestDeliveryTimeChroma[],
		द्विगुन                 DisplayPipeRequestDeliveryTimeLumaPrefetch[],
		द्विगुन                 DisplayPipeRequestDeliveryTimeChromaPrefetch[]);

अटल व्योम CalculateMetaAndPTETimes(
		अचिन्हित पूर्णांक           NumberOfActivePlanes,
		bool                   GPUVMEnable,
		अचिन्हित पूर्णांक           MetaChunkSize,
		अचिन्हित पूर्णांक           MinMetaChunkSizeBytes,
		अचिन्हित पूर्णांक           GPUVMMaxPageTableLevels,
		अचिन्हित पूर्णांक           HTotal[],
		द्विगुन                 VRatio[],
		द्विगुन                 VRatioPrefetchY[],
		द्विगुन                 VRatioPrefetchC[],
		द्विगुन                 DestinationLinesToRequestRowInVBlank[],
		द्विगुन                 DestinationLinesToRequestRowInImmediateFlip[],
		द्विगुन                 DestinationLinesToRequestVMInVBlank[],
		द्विगुन                 DestinationLinesToRequestVMInImmediateFlip[],
		bool                   DCCEnable[],
		द्विगुन                 PixelClock[],
		द्विगुन                 BytePerPixelDETY[],
		द्विगुन                 BytePerPixelDETC[],
		क्रमागत scan_direction_class SourceScan[],
		अचिन्हित पूर्णांक           dpte_row_height[],
		अचिन्हित पूर्णांक           dpte_row_height_chroma[],
		अचिन्हित पूर्णांक           meta_row_width[],
		अचिन्हित पूर्णांक           meta_row_height[],
		अचिन्हित पूर्णांक           meta_req_width[],
		अचिन्हित पूर्णांक           meta_req_height[],
		पूर्णांक                   dpte_group_bytes[],
		अचिन्हित पूर्णांक           PTERequestSizeY[],
		अचिन्हित पूर्णांक           PTERequestSizeC[],
		अचिन्हित पूर्णांक           PixelPTEReqWidthY[],
		अचिन्हित पूर्णांक           PixelPTEReqHeightY[],
		अचिन्हित पूर्णांक           PixelPTEReqWidthC[],
		अचिन्हित पूर्णांक           PixelPTEReqHeightC[],
		अचिन्हित पूर्णांक           dpte_row_width_luma_ub[],
		अचिन्हित पूर्णांक           dpte_row_width_chroma_ub[],
		अचिन्हित पूर्णांक           vm_group_bytes[],
		अचिन्हित पूर्णांक           dpde0_bytes_per_frame_ub_l[],
		अचिन्हित पूर्णांक           dpde0_bytes_per_frame_ub_c[],
		अचिन्हित पूर्णांक           meta_pte_bytes_per_frame_ub_l[],
		अचिन्हित पूर्णांक           meta_pte_bytes_per_frame_ub_c[],
		द्विगुन                 DST_Y_PER_PTE_ROW_NOM_L[],
		द्विगुन                 DST_Y_PER_PTE_ROW_NOM_C[],
		द्विगुन                 DST_Y_PER_META_ROW_NOM_L[],
		द्विगुन                 TimePerMetaChunkNominal[],
		द्विगुन                 TimePerMetaChunkVBlank[],
		द्विगुन                 TimePerMetaChunkFlip[],
		द्विगुन                 समय_per_pte_group_nom_luma[],
		द्विगुन                 समय_per_pte_group_vblank_luma[],
		द्विगुन                 समय_per_pte_group_flip_luma[],
		द्विगुन                 समय_per_pte_group_nom_chroma[],
		द्विगुन                 समय_per_pte_group_vblank_chroma[],
		द्विगुन                 समय_per_pte_group_flip_chroma[],
		द्विगुन                 TimePerVMGroupVBlank[],
		द्विगुन                 TimePerVMGroupFlip[],
		द्विगुन                 TimePerVMRequestVBlank[],
		द्विगुन                 TimePerVMRequestFlip[]);

अटल द्विगुन CalculateExtraLatency(
		द्विगुन UrgentRoundTripAndOutOfOrderLatency,
		पूर्णांक TotalNumberOfActiveDPP,
		पूर्णांक PixelChunkSizeInKByte,
		पूर्णांक TotalNumberOfDCCActiveDPP,
		पूर्णांक MetaChunkSize,
		द्विगुन ReturnBW,
		bool GPUVMEnable,
		bool HostVMEnable,
		पूर्णांक NumberOfActivePlanes,
		पूर्णांक NumberOfDPP[],
		पूर्णांक dpte_group_bytes[],
		द्विगुन PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData,
		द्विगुन PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly,
		पूर्णांक HostVMMaxPageTableLevels,
		पूर्णांक HostVMCachedPageTableLevels);

व्योम dml21_recalculate(काष्ठा display_mode_lib *mode_lib)
अणु
	ModeSupportAndSystemConfiguration(mode_lib);
	PixelClockAdjusपंचांगentForProgressiveToInterlaceUnit(mode_lib);
	DisplayPipeConfiguration(mode_lib);
	DISPCLKDPPCLKDCFCLKDeepSleepPrefetchParametersWatermarksAndPerक्रमmanceCalculation(mode_lib);
पूर्ण

अटल अचिन्हित पूर्णांक dscceComputeDelay(
		अचिन्हित पूर्णांक bpc,
		द्विगुन bpp,
		अचिन्हित पूर्णांक sliceWidth,
		अचिन्हित पूर्णांक numSlices,
		क्रमागत output_क्रमmat_class pixelFormat)
अणु
	// valid bpc         = source bits per component in the set of अणु8, 10, 12पूर्ण
	// valid bpp         = increments of 1/16 of a bit
	//                    min = 6/7/8 in N420/N422/444, respectively
	//                    max = such that compression is 1:1
	//valid sliceWidth  = number of pixels per slice line, must be less than or equal to 5184/numSlices (or 4096/numSlices in 420 mode)
	//valid numSlices   = number of slices in the horiziontal direction per DSC engine in the set of अणु1, 2, 3, 4पूर्ण
	//valid pixelFormat = pixel/color क्रमmat in the set of अणु:N444_RGB, :S422, :N422, :N420पूर्ण

	// fixed value
	अचिन्हित पूर्णांक rcModelSize = 8192;

	// N422/N420 operate at 2 pixels per घड़ी
	अचिन्हित पूर्णांक pixelsPerClock, lstall, D, initalXmitDelay, w, S, ix, wx, p, l0, a, ax, l,
			Delay, pixels;

	अगर (pixelFormat == dm_n422 || pixelFormat == dm_420)
		pixelsPerClock = 2;
	// #all other modes operate at 1 pixel per घड़ी
	अन्यथा
		pixelsPerClock = 1;

	//initial transmit delay as per PPS
	initalXmitDelay = dml_round(rcModelSize / 2.0 / bpp / pixelsPerClock);

	//compute ssm delay
	अगर (bpc == 8)
		D = 81;
	अन्यथा अगर (bpc == 10)
		D = 89;
	अन्यथा
		D = 113;

	//भागide by pixel per cycle to compute slice width as seen by DSC
	w = sliceWidth / pixelsPerClock;

	//422 mode has an additional cycle of delay
	अगर (pixelFormat == dm_s422)
		S = 1;
	अन्यथा
		S = 0;

	//मुख्य calculation क्रम the dscce
	ix = initalXmitDelay + 45;
	wx = (w + 2) / 3;
	p = 3 * wx - w;
	l0 = ix / w;
	a = ix + p * l0;
	ax = (a + 2) / 3 + D + 6 + 1;
	l = (ax + wx - 1) / wx;
	अगर ((ix % w) == 0 && p != 0)
		lstall = 1;
	अन्यथा
		lstall = 0;
	Delay = l * wx * (numSlices - 1) + ax + S + lstall + 22;

	//dsc processes 3 pixel containers per cycle and a container can contain 1 or 2 pixels
	pixels = Delay * 3 * pixelsPerClock;
	वापस pixels;
पूर्ण

अटल अचिन्हित पूर्णांक dscComputeDelay(क्रमागत output_क्रमmat_class pixelFormat)
अणु
	अचिन्हित पूर्णांक Delay = 0;

	अगर (pixelFormat == dm_420) अणु
		//   sfr
		Delay = Delay + 2;
		//   dsccअगर
		Delay = Delay + 0;
		//   dscc - input deserializer
		Delay = Delay + 3;
		//   dscc माला_लो pixels every other cycle
		Delay = Delay + 2;
		//   dscc - input cdc fअगरo
		Delay = Delay + 12;
		//   dscc माला_लो pixels every other cycle
		Delay = Delay + 13;
		//   dscc - cdc uncertaपूर्णांकy
		Delay = Delay + 2;
		//   dscc - output cdc fअगरo
		Delay = Delay + 7;
		//   dscc माला_लो pixels every other cycle
		Delay = Delay + 3;
		//   dscc - cdc uncertaपूर्णांकy
		Delay = Delay + 2;
		//   dscc - output serializer
		Delay = Delay + 1;
		//   sft
		Delay = Delay + 1;
	पूर्ण अन्यथा अगर (pixelFormat == dm_n422) अणु
		//   sfr
		Delay = Delay + 2;
		//   dsccअगर
		Delay = Delay + 1;
		//   dscc - input deserializer
		Delay = Delay + 5;
		//  dscc - input cdc fअगरo
		Delay = Delay + 25;
		//   dscc - cdc uncertaपूर्णांकy
		Delay = Delay + 2;
		//   dscc - output cdc fअगरo
		Delay = Delay + 10;
		//   dscc - cdc uncertaपूर्णांकy
		Delay = Delay + 2;
		//   dscc - output serializer
		Delay = Delay + 1;
		//   sft
		Delay = Delay + 1;
	पूर्ण अन्यथा अणु
		//   sfr
		Delay = Delay + 2;
		//   dsccअगर
		Delay = Delay + 0;
		//   dscc - input deserializer
		Delay = Delay + 3;
		//   dscc - input cdc fअगरo
		Delay = Delay + 12;
		//   dscc - cdc uncertaपूर्णांकy
		Delay = Delay + 2;
		//   dscc - output cdc fअगरo
		Delay = Delay + 7;
		//   dscc - output serializer
		Delay = Delay + 1;
		//   dscc - cdc uncertaपूर्णांकy
		Delay = Delay + 2;
		//   sft
		Delay = Delay + 1;
	पूर्ण

	वापस Delay;
पूर्ण

अटल bool CalculatePrefetchSchedule(
		काष्ठा display_mode_lib *mode_lib,
		द्विगुन PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData,
		द्विगुन PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly,
		Pipe *myPipe,
		अचिन्हित पूर्णांक DSCDelay,
		द्विगुन DPPCLKDelaySubtotal,
		द्विगुन DPPCLKDelaySCL,
		द्विगुन DPPCLKDelaySCLLBOnly,
		द्विगुन DPPCLKDelayCNVCFormater,
		द्विगुन DPPCLKDelayCNVCCursor,
		द्विगुन DISPCLKDelaySubtotal,
		अचिन्हित पूर्णांक ScalerRecoutWidth,
		क्रमागत output_क्रमmat_class OutputFormat,
		अचिन्हित पूर्णांक MaxInterDCNTileRepeaters,
		अचिन्हित पूर्णांक VStartup,
		अचिन्हित पूर्णांक MaxVStartup,
		अचिन्हित पूर्णांक GPUVMPageTableLevels,
		bool GPUVMEnable,
		HostVM *myHostVM,
		bool DynamicMetadataEnable,
		पूर्णांक DynamicMetadataLinesBeक्रमeActiveRequired,
		अचिन्हित पूर्णांक DynamicMetadataTransmittedBytes,
		bool DCCEnable,
		द्विगुन UrgentLatency,
		द्विगुन UrgentExtraLatency,
		द्विगुन TCalc,
		अचिन्हित पूर्णांक PDEAndMetaPTEBytesFrame,
		अचिन्हित पूर्णांक MetaRowByte,
		अचिन्हित पूर्णांक PixelPTEBytesPerRow,
		द्विगुन PrefetchSourceLinesY,
		अचिन्हित पूर्णांक SwathWidthY,
		द्विगुन BytePerPixelDETY,
		द्विगुन VInitPreFillY,
		अचिन्हित पूर्णांक MaxNumSwathY,
		द्विगुन PrefetchSourceLinesC,
		द्विगुन BytePerPixelDETC,
		द्विगुन VInitPreFillC,
		अचिन्हित पूर्णांक MaxNumSwathC,
		अचिन्हित पूर्णांक SwathHeightY,
		अचिन्हित पूर्णांक SwathHeightC,
		द्विगुन TWait,
		bool XFCEnabled,
		द्विगुन XFCRemoteSurfaceFlipDelay,
		bool ProgressiveToInterlaceUnitInOPP,
		द्विगुन *DSTXAfterScaler,
		द्विगुन *DSTYAfterScaler,
		द्विगुन *DestinationLinesForPrefetch,
		द्विगुन *PrefetchBandwidth,
		द्विगुन *DestinationLinesToRequestVMInVBlank,
		द्विगुन *DestinationLinesToRequestRowInVBlank,
		द्विगुन *VRatioPrefetchY,
		द्विगुन *VRatioPrefetchC,
		द्विगुन *RequiredPrefetchPixDataBWLuma,
		द्विगुन *RequiredPrefetchPixDataBWChroma,
		अचिन्हित पूर्णांक *VStartupRequiredWhenNotEnoughTimeForDynamicMetadata,
		द्विगुन *Tno_bw,
		द्विगुन *prefetch_vmrow_bw,
		अचिन्हित पूर्णांक *swath_width_luma_ub,
		अचिन्हित पूर्णांक *swath_width_chroma_ub,
		अचिन्हित पूर्णांक *VUpdateOffsetPix,
		द्विगुन *VUpdateWidthPix,
		द्विगुन *VReadyOffsetPix)
अणु
	bool MyError = false;
	अचिन्हित पूर्णांक DPPCycles, DISPCLKCycles;
	द्विगुन DSTTotalPixelsAfterScaler, TotalRepeaterDelayTime;
	द्विगुन Tdm, LineTime, Tsetup;
	द्विगुन dst_y_prefetch_equ;
	द्विगुन Tsw_oto;
	द्विगुन prefetch_bw_oto;
	द्विगुन Tvm_oto;
	द्विगुन Tr0_oto;
	द्विगुन Tvm_oto_lines;
	द्विगुन Tr0_oto_lines;
	द्विगुन Tsw_oto_lines;
	द्विगुन dst_y_prefetch_oto;
	द्विगुन TimeForFetchingMetaPTE = 0;
	द्विगुन TimeForFetchingRowInVBlank = 0;
	द्विगुन LinesToRequestPrefetchPixelData = 0;
	द्विगुन HostVMInefficiencyFactor;
	अचिन्हित पूर्णांक HostVMDynamicLevels;

	अगर (GPUVMEnable == true && myHostVM->Enable == true) अणु
		HostVMInefficiencyFactor =
				PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData
						/ PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly;
		HostVMDynamicLevels = myHostVM->MaxPageTableLevels
				- myHostVM->CachedPageTableLevels;
	पूर्ण अन्यथा अणु
		HostVMInefficiencyFactor = 1;
		HostVMDynamicLevels = 0;
	पूर्ण

	अगर (myPipe->ScalerEnabled)
		DPPCycles = DPPCLKDelaySubtotal + DPPCLKDelaySCL;
	अन्यथा
		DPPCycles = DPPCLKDelaySubtotal + DPPCLKDelaySCLLBOnly;

	DPPCycles = DPPCycles + DPPCLKDelayCNVCFormater + myPipe->NumberOfCursors * DPPCLKDelayCNVCCursor;

	DISPCLKCycles = DISPCLKDelaySubtotal;

	अगर (myPipe->DPPCLK == 0.0 || myPipe->DISPCLK == 0.0)
		वापस true;

	*DSTXAfterScaler = DPPCycles * myPipe->PixelClock / myPipe->DPPCLK
			+ DISPCLKCycles * myPipe->PixelClock / myPipe->DISPCLK + DSCDelay;

	अगर (myPipe->DPPPerPlane > 1)
		*DSTXAfterScaler = *DSTXAfterScaler + ScalerRecoutWidth;

	अगर (OutputFormat == dm_420 || (myPipe->InterlaceEnable && ProgressiveToInterlaceUnitInOPP))
		*DSTYAfterScaler = 1;
	अन्यथा
		*DSTYAfterScaler = 0;

	DSTTotalPixelsAfterScaler = ((द्विगुन) (*DSTYAfterScaler * myPipe->HTotal)) + *DSTXAfterScaler;
	*DSTYAfterScaler = dml_न्यूनमान(DSTTotalPixelsAfterScaler / myPipe->HTotal, 1);
	*DSTXAfterScaler = DSTTotalPixelsAfterScaler - ((द्विगुन) (*DSTYAfterScaler * myPipe->HTotal));

	*VUpdateOffsetPix = dml_उच्चमान(myPipe->HTotal / 4.0, 1);
	TotalRepeaterDelayTime = MaxInterDCNTileRepeaters * (2.0 / myPipe->DPPCLK + 3.0 / myPipe->DISPCLK);
	*VUpdateWidthPix = (14.0 / myPipe->DCFCLKDeepSleep + 12.0 / myPipe->DPPCLK + TotalRepeaterDelayTime)
			* myPipe->PixelClock;

	*VReadyOffsetPix = dml_max(
			150.0 / myPipe->DPPCLK,
			TotalRepeaterDelayTime + 20.0 / myPipe->DCFCLKDeepSleep + 10.0 / myPipe->DPPCLK)
			* myPipe->PixelClock;

	Tsetup = (द्विगुन) (*VUpdateOffsetPix + *VUpdateWidthPix + *VReadyOffsetPix) / myPipe->PixelClock;

	LineTime = (द्विगुन) myPipe->HTotal / myPipe->PixelClock;

	अगर (DynamicMetadataEnable) अणु
		द्विगुन Tdmbf, Tdmec, Tdmsks;

		Tdm = dml_max(0.0, UrgentExtraLatency - TCalc);
		Tdmbf = DynamicMetadataTransmittedBytes / 4.0 / myPipe->DISPCLK;
		Tdmec = LineTime;
		अगर (DynamicMetadataLinesBeक्रमeActiveRequired == -1)
			Tdmsks = myPipe->VBlank * LineTime / 2.0;
		अन्यथा
			Tdmsks = DynamicMetadataLinesBeक्रमeActiveRequired * LineTime;
		अगर (myPipe->InterlaceEnable && !ProgressiveToInterlaceUnitInOPP)
			Tdmsks = Tdmsks / 2;
		अगर (VStartup * LineTime
				< Tsetup + TWait + UrgentExtraLatency + Tdmbf + Tdmec + Tdmsks) अणु
			MyError = true;
			*VStartupRequiredWhenNotEnoughTimeForDynamicMetadata = (Tsetup + TWait
					+ UrgentExtraLatency + Tdmbf + Tdmec + Tdmsks) / LineTime;
		पूर्ण अन्यथा
			*VStartupRequiredWhenNotEnoughTimeForDynamicMetadata = 0.0;
	पूर्ण अन्यथा
		Tdm = 0;

	अगर (GPUVMEnable) अणु
		अगर (GPUVMPageTableLevels >= 3)
			*Tno_bw = UrgentExtraLatency + UrgentLatency * ((GPUVMPageTableLevels - 2) * (myHostVM->MaxPageTableLevels + 1) - 1);
		अन्यथा
			*Tno_bw = 0;
	पूर्ण अन्यथा अगर (!DCCEnable)
		*Tno_bw = LineTime;
	अन्यथा
		*Tno_bw = LineTime / 4;

	dst_y_prefetch_equ = VStartup - dml_max(TCalc + TWait, XFCRemoteSurfaceFlipDelay) / LineTime
			- (Tsetup + Tdm) / LineTime
			- (*DSTYAfterScaler + *DSTXAfterScaler / myPipe->HTotal);

	Tsw_oto = dml_max(PrefetchSourceLinesY, PrefetchSourceLinesC) * LineTime;

	अगर (myPipe->SourceScan == dm_horz) अणु
		*swath_width_luma_ub = dml_उच्चमान(SwathWidthY - 1, myPipe->BlockWidth256BytesY) + myPipe->BlockWidth256BytesY;
		*swath_width_chroma_ub = dml_उच्चमान(SwathWidthY / 2 - 1, myPipe->BlockWidth256BytesC) + myPipe->BlockWidth256BytesC;
	पूर्ण अन्यथा अणु
		*swath_width_luma_ub = dml_उच्चमान(SwathWidthY - 1, myPipe->BlockHeight256BytesY) + myPipe->BlockHeight256BytesY;
		*swath_width_chroma_ub = dml_उच्चमान(SwathWidthY / 2 - 1, myPipe->BlockHeight256BytesC) + myPipe->BlockHeight256BytesC;
	पूर्ण

	prefetch_bw_oto = (PrefetchSourceLinesY * *swath_width_luma_ub * dml_उच्चमान(BytePerPixelDETY, 1) + PrefetchSourceLinesC * *swath_width_chroma_ub * dml_उच्चमान(BytePerPixelDETC, 2)) / Tsw_oto;


	अगर (GPUVMEnable == true) अणु
		Tvm_oto = dml_max(*Tno_bw + PDEAndMetaPTEBytesFrame * HostVMInefficiencyFactor / prefetch_bw_oto,
				dml_max(UrgentExtraLatency + UrgentLatency * (GPUVMPageTableLevels * (HostVMDynamicLevels + 1) - 1),
					LineTime / 4.0));
	पूर्ण अन्यथा
		Tvm_oto = LineTime / 4.0;

	अगर ((GPUVMEnable == true || DCCEnable == true)) अणु
		Tr0_oto = dml_max(
				(MetaRowByte + PixelPTEBytesPerRow * HostVMInefficiencyFactor) / prefetch_bw_oto,
				dml_max(UrgentLatency * (HostVMDynamicLevels + 1), dml_max(LineTime - Tvm_oto, LineTime / 4)));
	पूर्ण अन्यथा
		Tr0_oto = (LineTime - Tvm_oto) / 2.0;

	Tvm_oto_lines = dml_उच्चमान(4 * Tvm_oto / LineTime, 1) / 4.0;
	Tr0_oto_lines = dml_उच्चमान(4 * Tr0_oto / LineTime, 1) / 4.0;
	Tsw_oto_lines = dml_उच्चमान(4 * Tsw_oto / LineTime, 1) / 4.0;
	dst_y_prefetch_oto = Tvm_oto_lines + 2 * Tr0_oto_lines + Tsw_oto_lines + 0.75;

	dst_y_prefetch_equ = dml_न्यूनमान(4.0 * (dst_y_prefetch_equ + 0.125), 1) / 4.0;

	अगर (dst_y_prefetch_oto < dst_y_prefetch_equ)
		*DestinationLinesForPrefetch = dst_y_prefetch_oto;
	अन्यथा
		*DestinationLinesForPrefetch = dst_y_prefetch_equ;

	dml_prपूर्णांक("DML: VStartup: %d\n", VStartup);
	dml_prपूर्णांक("DML: TCalc: %f\n", TCalc);
	dml_prपूर्णांक("DML: TWait: %f\n", TWait);
	dml_prपूर्णांक("DML: XFCRemoteSurfaceFlipDelay: %f\n", XFCRemoteSurfaceFlipDelay);
	dml_prपूर्णांक("DML: LineTime: %f\n", LineTime);
	dml_prपूर्णांक("DML: Tsetup: %f\n", Tsetup);
	dml_prपूर्णांक("DML: Tdm: %f\n", Tdm);
	dml_prपूर्णांक("DML: DSTYAfterScaler: %f\n", *DSTYAfterScaler);
	dml_prपूर्णांक("DML: DSTXAfterScaler: %f\n", *DSTXAfterScaler);
	dml_prपूर्णांक("DML: HTotal: %d\n", myPipe->HTotal);

	*PrefetchBandwidth = 0;
	*DestinationLinesToRequestVMInVBlank = 0;
	*DestinationLinesToRequestRowInVBlank = 0;
	*VRatioPrefetchY = 0;
	*VRatioPrefetchC = 0;
	*RequiredPrefetchPixDataBWLuma = 0;
	अगर (*DestinationLinesForPrefetch > 1) अणु
		द्विगुन PrefetchBandwidth1 = (PDEAndMetaPTEBytesFrame * HostVMInefficiencyFactor + 2 * MetaRowByte
				+ 2 * PixelPTEBytesPerRow * HostVMInefficiencyFactor
				+ PrefetchSourceLinesY * *swath_width_luma_ub * dml_उच्चमान(BytePerPixelDETY, 1)
				+ PrefetchSourceLinesC * *swath_width_chroma_ub * dml_उच्चमान(BytePerPixelDETC, 2))
				/ (*DestinationLinesForPrefetch * LineTime - *Tno_bw);

		द्विगुन PrefetchBandwidth2 = (PDEAndMetaPTEBytesFrame *
				HostVMInefficiencyFactor + PrefetchSourceLinesY *
				*swath_width_luma_ub * dml_उच्चमान(BytePerPixelDETY, 1) +
				PrefetchSourceLinesC * *swath_width_chroma_ub *
				dml_उच्चमान(BytePerPixelDETC, 2)) /
				(*DestinationLinesForPrefetch * LineTime - *Tno_bw - 2 *
				UrgentLatency * (1 + HostVMDynamicLevels));

		द्विगुन PrefetchBandwidth3 = (2 * MetaRowByte + 2 * PixelPTEBytesPerRow
				* HostVMInefficiencyFactor + PrefetchSourceLinesY *
				*swath_width_luma_ub * dml_उच्चमान(BytePerPixelDETY, 1) +
				PrefetchSourceLinesC * *swath_width_chroma_ub *
				dml_उच्चमान(BytePerPixelDETC, 2)) /
				(*DestinationLinesForPrefetch * LineTime -
				UrgentExtraLatency - UrgentLatency * (GPUVMPageTableLevels
				* (HostVMDynamicLevels + 1) - 1));

		द्विगुन PrefetchBandwidth4 = (PrefetchSourceLinesY * *swath_width_luma_ub *
				dml_उच्चमान(BytePerPixelDETY, 1) + PrefetchSourceLinesC *
				*swath_width_chroma_ub * dml_उच्चमान(BytePerPixelDETC, 2)) /
				(*DestinationLinesForPrefetch * LineTime -
				UrgentExtraLatency - UrgentLatency * (GPUVMPageTableLevels
				* (HostVMDynamicLevels + 1) - 1) - 2 * UrgentLatency *
				(1 + HostVMDynamicLevels));

		अगर (VStartup == MaxVStartup && (PrefetchBandwidth1 > 4 * prefetch_bw_oto) && (*DestinationLinesForPrefetch - dml_उच्चमान(Tsw_oto_lines, 1) / 4.0 - 0.75) * LineTime - *Tno_bw > 0) अणु
			PrefetchBandwidth1 = (PDEAndMetaPTEBytesFrame * HostVMInefficiencyFactor + 2 * MetaRowByte + 2 * PixelPTEBytesPerRow * HostVMInefficiencyFactor) / ((*DestinationLinesForPrefetch - dml_उच्चमान(Tsw_oto_lines, 1) / 4.0 - 0.75) * LineTime - *Tno_bw);
		पूर्ण
		अगर (*Tno_bw + PDEAndMetaPTEBytesFrame * HostVMInefficiencyFactor / PrefetchBandwidth1 >= UrgentExtraLatency + UrgentLatency * (GPUVMPageTableLevels * (HostVMDynamicLevels + 1) - 1) && (MetaRowByte + PixelPTEBytesPerRow * HostVMInefficiencyFactor) / PrefetchBandwidth1 >= UrgentLatency * (1 + HostVMDynamicLevels)) अणु
			*PrefetchBandwidth = PrefetchBandwidth1;
		पूर्ण अन्यथा अगर (*Tno_bw + PDEAndMetaPTEBytesFrame * HostVMInefficiencyFactor / PrefetchBandwidth2 >= UrgentExtraLatency + UrgentLatency * (GPUVMPageTableLevels * (HostVMDynamicLevels + 1) - 1) && (MetaRowByte + PixelPTEBytesPerRow * HostVMInefficiencyFactor) / PrefetchBandwidth2 < UrgentLatency * (1 + HostVMDynamicLevels)) अणु
			*PrefetchBandwidth = PrefetchBandwidth2;
		पूर्ण अन्यथा अगर (*Tno_bw + PDEAndMetaPTEBytesFrame * HostVMInefficiencyFactor / PrefetchBandwidth3 < UrgentExtraLatency + UrgentLatency * (GPUVMPageTableLevels * (HostVMDynamicLevels + 1) - 1) && (MetaRowByte + PixelPTEBytesPerRow * HostVMInefficiencyFactor) / PrefetchBandwidth3 >= UrgentLatency * (1 + HostVMDynamicLevels)) अणु
			*PrefetchBandwidth = PrefetchBandwidth3;
		पूर्ण अन्यथा अणु
			*PrefetchBandwidth = PrefetchBandwidth4;
		पूर्ण

		अगर (GPUVMEnable) अणु
			TimeForFetchingMetaPTE = dml_max(*Tno_bw + (द्विगुन) PDEAndMetaPTEBytesFrame * HostVMInefficiencyFactor / *PrefetchBandwidth,
					dml_max(UrgentExtraLatency + UrgentLatency * (GPUVMPageTableLevels * (HostVMDynamicLevels + 1) - 1), LineTime / 4));
		पूर्ण अन्यथा अणु
// 5/30/2018 - This was an optimization requested from Sy but now NumberOfCursors is no दीर्घer a factor
//             so अगर this needs to be reinstated, then it should be officially करोne in the VBA code as well.
//			अगर (mode_lib->NumberOfCursors > 0 || XFCEnabled)
				TimeForFetchingMetaPTE = LineTime / 4;
//			अन्यथा
//				TimeForFetchingMetaPTE = 0.0;
		पूर्ण

		अगर ((GPUVMEnable == true || DCCEnable == true)) अणु
			TimeForFetchingRowInVBlank =
					dml_max(
							(MetaRowByte + PixelPTEBytesPerRow * HostVMInefficiencyFactor)
									/ *PrefetchBandwidth,
							dml_max(
									UrgentLatency * (1 + HostVMDynamicLevels),
									dml_max(
											(LineTime
													- TimeForFetchingMetaPTE) / 2.0,
											LineTime
													/ 4.0)));
		पूर्ण अन्यथा अणु
// See note above dated 5/30/2018
//			अगर (NumberOfCursors > 0 || XFCEnabled)
				TimeForFetchingRowInVBlank = (LineTime - TimeForFetchingMetaPTE) / 2.0;
//			अन्यथा // TODO: Did someone अन्यथा add this??
//				TimeForFetchingRowInVBlank = 0.0;
		पूर्ण

		*DestinationLinesToRequestVMInVBlank = dml_उच्चमान(4.0 * TimeForFetchingMetaPTE / LineTime, 1.0) / 4.0;

		*DestinationLinesToRequestRowInVBlank = dml_उच्चमान(4.0 * TimeForFetchingRowInVBlank / LineTime, 1.0) / 4.0;

		LinesToRequestPrefetchPixelData = *DestinationLinesForPrefetch
// See note above dated 5/30/2018
//						- ((NumberOfCursors > 0 || GPUVMEnable || DCCEnable) ?
						- ((GPUVMEnable || DCCEnable) ?
								(*DestinationLinesToRequestVMInVBlank + 2 * *DestinationLinesToRequestRowInVBlank) :
								0.0); // TODO: Did someone अन्यथा add this??

		अगर (LinesToRequestPrefetchPixelData > 0) अणु

			*VRatioPrefetchY = (द्विगुन) PrefetchSourceLinesY
					/ LinesToRequestPrefetchPixelData;
			*VRatioPrefetchY = dml_max(*VRatioPrefetchY, 1.0);
			अगर ((SwathHeightY > 4) && (VInitPreFillY > 3)) अणु
				अगर (LinesToRequestPrefetchPixelData > (VInitPreFillY - 3.0) / 2.0) अणु
					*VRatioPrefetchY =
							dml_max(
									(द्विगुन) PrefetchSourceLinesY
											/ LinesToRequestPrefetchPixelData,
									(द्विगुन) MaxNumSwathY
											* SwathHeightY
											/ (LinesToRequestPrefetchPixelData
													- (VInitPreFillY
															- 3.0)
															/ 2.0));
					*VRatioPrefetchY = dml_max(*VRatioPrefetchY, 1.0);
				पूर्ण अन्यथा अणु
					MyError = true;
					*VRatioPrefetchY = 0;
				पूर्ण
			पूर्ण

			*VRatioPrefetchC = (द्विगुन) PrefetchSourceLinesC
					/ LinesToRequestPrefetchPixelData;
			*VRatioPrefetchC = dml_max(*VRatioPrefetchC, 1.0);

			अगर ((SwathHeightC > 4)) अणु
				अगर (LinesToRequestPrefetchPixelData > (VInitPreFillC - 3.0) / 2.0) अणु
					*VRatioPrefetchC =
							dml_max(
									*VRatioPrefetchC,
									(द्विगुन) MaxNumSwathC
											* SwathHeightC
											/ (LinesToRequestPrefetchPixelData
													- (VInitPreFillC
															- 3.0)
															/ 2.0));
					*VRatioPrefetchC = dml_max(*VRatioPrefetchC, 1.0);
				पूर्ण अन्यथा अणु
					MyError = true;
					*VRatioPrefetchC = 0;
				पूर्ण
			पूर्ण

			*RequiredPrefetchPixDataBWLuma = myPipe->DPPPerPlane
					* (द्विगुन) PrefetchSourceLinesY / LinesToRequestPrefetchPixelData
					* dml_उच्चमान(BytePerPixelDETY, 1)
					* *swath_width_luma_ub / LineTime;
			*RequiredPrefetchPixDataBWChroma = myPipe->DPPPerPlane
					* (द्विगुन) PrefetchSourceLinesC / LinesToRequestPrefetchPixelData
					* dml_उच्चमान(BytePerPixelDETC, 2)
					* *swath_width_chroma_ub / LineTime;
		पूर्ण अन्यथा अणु
			MyError = true;
			*VRatioPrefetchY = 0;
			*VRatioPrefetchC = 0;
			*RequiredPrefetchPixDataBWLuma = 0;
			*RequiredPrefetchPixDataBWChroma = 0;
		पूर्ण

		dml_prपूर्णांक("DML: Tvm: %fus\n", TimeForFetchingMetaPTE);
		dml_prपूर्णांक("DML: Tr0: %fus\n", TimeForFetchingRowInVBlank);
		dml_prपूर्णांक("DML: Tsw: %fus\n", (द्विगुन)(*DestinationLinesForPrefetch) * LineTime - TimeForFetchingMetaPTE - TimeForFetchingRowInVBlank);
		dml_prपूर्णांक("DML: Tpre: %fus\n", (द्विगुन)(*DestinationLinesForPrefetch) * LineTime);
		dml_prपूर्णांक("DML: row_bytes = dpte_row_bytes (per_pipe) = PixelPTEBytesPerRow = : %d\n", PixelPTEBytesPerRow);

	पूर्ण अन्यथा अणु
		MyError = true;
	पूर्ण

	अणु
		द्विगुन prefetch_vm_bw;
		द्विगुन prefetch_row_bw;

		अगर (PDEAndMetaPTEBytesFrame == 0) अणु
			prefetch_vm_bw = 0;
		पूर्ण अन्यथा अगर (*DestinationLinesToRequestVMInVBlank > 0) अणु
			prefetch_vm_bw = PDEAndMetaPTEBytesFrame * HostVMInefficiencyFactor / (*DestinationLinesToRequestVMInVBlank * LineTime);
		पूर्ण अन्यथा अणु
			prefetch_vm_bw = 0;
			MyError = true;
		पूर्ण
		अगर (MetaRowByte + PixelPTEBytesPerRow == 0) अणु
			prefetch_row_bw = 0;
		पूर्ण अन्यथा अगर (*DestinationLinesToRequestRowInVBlank > 0) अणु
			prefetch_row_bw = (MetaRowByte + PixelPTEBytesPerRow * HostVMInefficiencyFactor) / (*DestinationLinesToRequestRowInVBlank * LineTime);
		पूर्ण अन्यथा अणु
			prefetch_row_bw = 0;
			MyError = true;
		पूर्ण

		*prefetch_vmrow_bw = dml_max(prefetch_vm_bw, prefetch_row_bw);
	पूर्ण

	अगर (MyError) अणु
		*PrefetchBandwidth = 0;
		TimeForFetchingMetaPTE = 0;
		TimeForFetchingRowInVBlank = 0;
		*DestinationLinesToRequestVMInVBlank = 0;
		*DestinationLinesToRequestRowInVBlank = 0;
		*DestinationLinesForPrefetch = 0;
		LinesToRequestPrefetchPixelData = 0;
		*VRatioPrefetchY = 0;
		*VRatioPrefetchC = 0;
		*RequiredPrefetchPixDataBWLuma = 0;
		*RequiredPrefetchPixDataBWChroma = 0;
	पूर्ण

	वापस MyError;
पूर्ण

अटल द्विगुन RoundToDFSGranularityUp(द्विगुन Clock, द्विगुन VCOSpeed)
अणु
	वापस VCOSpeed * 4 / dml_न्यूनमान(VCOSpeed * 4 / Clock, 1);
पूर्ण

अटल द्विगुन RoundToDFSGranularityDown(द्विगुन Clock, द्विगुन VCOSpeed)
अणु
	वापस VCOSpeed * 4 / dml_उच्चमान(VCOSpeed * 4 / Clock, 1);
पूर्ण

अटल द्विगुन CalculateDCCConfiguration(
		bool DCCEnabled,
		bool DCCProgrammingAssumesScanDirectionUnknown,
		अचिन्हित पूर्णांक ViewportWidth,
		अचिन्हित पूर्णांक ViewportHeight,
		द्विगुन DETBufferSize,
		अचिन्हित पूर्णांक RequestHeight256Byte,
		अचिन्हित पूर्णांक SwathHeight,
		क्रमागत dm_swizzle_mode TilingFormat,
		अचिन्हित पूर्णांक BytePerPixel,
		क्रमागत scan_direction_class ScanOrientation,
		अचिन्हित पूर्णांक *MaxUncompressedBlock,
		अचिन्हित पूर्णांक *MaxCompressedBlock,
		अचिन्हित पूर्णांक *Independent64ByteBlock)
अणु
	द्विगुन MaximumDCCCompressionSurface = 0.0;
	क्रमागत अणु
		REQ_256Bytes,
		REQ_128BytesNonContiguous,
		REQ_128BytesContiguous,
		REQ_NA
	पूर्ण Request = REQ_NA;

	अगर (DCCEnabled == true) अणु
		अगर (DCCProgrammingAssumesScanDirectionUnknown == true) अणु
			अगर (DETBufferSize >= RequestHeight256Byte * ViewportWidth * BytePerPixel
					&& DETBufferSize
							>= 256 / RequestHeight256Byte
									* ViewportHeight) अणु
				Request = REQ_256Bytes;
			पूर्ण अन्यथा अगर ((DETBufferSize
					< RequestHeight256Byte * ViewportWidth * BytePerPixel
					&& (BytePerPixel == 2 || BytePerPixel == 4))
					|| (DETBufferSize
							< 256 / RequestHeight256Byte
									* ViewportHeight
							&& BytePerPixel == 8
							&& (TilingFormat == dm_sw_4kb_d
									|| TilingFormat
											== dm_sw_4kb_d_x
									|| TilingFormat
											== dm_sw_var_d
									|| TilingFormat
											== dm_sw_var_d_x
									|| TilingFormat
											== dm_sw_64kb_d
									|| TilingFormat
											== dm_sw_64kb_d_x
									|| TilingFormat
											== dm_sw_64kb_d_t
									|| TilingFormat
											== dm_sw_64kb_r_x))) अणु
				Request = REQ_128BytesNonContiguous;
			पूर्ण अन्यथा अणु
				Request = REQ_128BytesContiguous;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (BytePerPixel == 1) अणु
				अगर (ScanOrientation == dm_vert || SwathHeight == 16) अणु
					Request = REQ_256Bytes;
				पूर्ण अन्यथा अणु
					Request = REQ_128BytesContiguous;
				पूर्ण
			पूर्ण अन्यथा अगर (BytePerPixel == 2) अणु
				अगर ((ScanOrientation == dm_vert && SwathHeight == 16) || (ScanOrientation != dm_vert && SwathHeight == 8)) अणु
					Request = REQ_256Bytes;
				पूर्ण अन्यथा अगर (ScanOrientation == dm_vert) अणु
					Request = REQ_128BytesContiguous;
				पूर्ण अन्यथा अणु
					Request = REQ_128BytesNonContiguous;
				पूर्ण
			पूर्ण अन्यथा अगर (BytePerPixel == 4) अणु
				अगर (SwathHeight == 8) अणु
					Request = REQ_256Bytes;
				पूर्ण अन्यथा अगर (ScanOrientation == dm_vert) अणु
					Request = REQ_128BytesContiguous;
				पूर्ण अन्यथा अणु
					Request = REQ_128BytesNonContiguous;
				पूर्ण
			पूर्ण अन्यथा अगर (BytePerPixel == 8) अणु
				अगर (TilingFormat == dm_sw_4kb_d || TilingFormat == dm_sw_4kb_d_x
						|| TilingFormat == dm_sw_var_d
						|| TilingFormat == dm_sw_var_d_x
						|| TilingFormat == dm_sw_64kb_d
						|| TilingFormat == dm_sw_64kb_d_x
						|| TilingFormat == dm_sw_64kb_d_t
						|| TilingFormat == dm_sw_64kb_r_x) अणु
					अगर ((ScanOrientation == dm_vert && SwathHeight == 8)
							|| (ScanOrientation != dm_vert
									&& SwathHeight == 4)) अणु
						Request = REQ_256Bytes;
					पूर्ण अन्यथा अगर (ScanOrientation != dm_vert) अणु
						Request = REQ_128BytesContiguous;
					पूर्ण अन्यथा अणु
						Request = REQ_128BytesNonContiguous;
					पूर्ण
				पूर्ण अन्यथा अणु
					अगर (ScanOrientation != dm_vert || SwathHeight == 8) अणु
						Request = REQ_256Bytes;
					पूर्ण अन्यथा अणु
						Request = REQ_128BytesContiguous;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		Request = REQ_NA;
	पूर्ण

	अगर (Request == REQ_256Bytes) अणु
		*MaxUncompressedBlock = 256;
		*MaxCompressedBlock = 256;
		*Independent64ByteBlock = false;
		MaximumDCCCompressionSurface = 4.0;
	पूर्ण अन्यथा अगर (Request == REQ_128BytesContiguous) अणु
		*MaxUncompressedBlock = 128;
		*MaxCompressedBlock = 128;
		*Independent64ByteBlock = false;
		MaximumDCCCompressionSurface = 2.0;
	पूर्ण अन्यथा अगर (Request == REQ_128BytesNonContiguous) अणु
		*MaxUncompressedBlock = 256;
		*MaxCompressedBlock = 64;
		*Independent64ByteBlock = true;
		MaximumDCCCompressionSurface = 4.0;
	पूर्ण अन्यथा अणु
		*MaxUncompressedBlock = 0;
		*MaxCompressedBlock = 0;
		*Independent64ByteBlock = 0;
		MaximumDCCCompressionSurface = 0.0;
	पूर्ण

	वापस MaximumDCCCompressionSurface;
पूर्ण

अटल द्विगुन CalculatePrefetchSourceLines(
		काष्ठा display_mode_lib *mode_lib,
		द्विगुन VRatio,
		द्विगुन vtaps,
		bool Interlace,
		bool ProgressiveToInterlaceUnitInOPP,
		अचिन्हित पूर्णांक SwathHeight,
		अचिन्हित पूर्णांक ViewportYStart,
		द्विगुन *VInitPreFill,
		अचिन्हित पूर्णांक *MaxNumSwath)
अणु
	अचिन्हित पूर्णांक MaxPartialSwath;

	अगर (ProgressiveToInterlaceUnitInOPP)
		*VInitPreFill = dml_न्यूनमान((VRatio + vtaps + 1) / 2.0, 1);
	अन्यथा
		*VInitPreFill = dml_न्यूनमान((VRatio + vtaps + 1 + Interlace * 0.5 * VRatio) / 2.0, 1);

	अगर (!mode_lib->vba.IgnoreViewportPositioning) अणु

		*MaxNumSwath = dml_उच्चमान((*VInitPreFill - 1.0) / SwathHeight, 1) + 1.0;

		अगर (*VInitPreFill > 1.0)
			MaxPartialSwath = (अचिन्हित पूर्णांक) (*VInitPreFill - 2) % SwathHeight;
		अन्यथा
			MaxPartialSwath = (अचिन्हित पूर्णांक) (*VInitPreFill + SwathHeight - 2)
					% SwathHeight;
		MaxPartialSwath = dml_max(1U, MaxPartialSwath);

	पूर्ण अन्यथा अणु

		अगर (ViewportYStart != 0)
			dml_prपूर्णांक(
					"WARNING DML: using viewport y position of 0 even though actual viewport y position is non-zero in prefetch source lines calculation\n");

		*MaxNumSwath = dml_उच्चमान(*VInitPreFill / SwathHeight, 1);

		अगर (*VInitPreFill > 1.0)
			MaxPartialSwath = (अचिन्हित पूर्णांक) (*VInitPreFill - 1) % SwathHeight;
		अन्यथा
			MaxPartialSwath = (अचिन्हित पूर्णांक) (*VInitPreFill + SwathHeight - 1)
					% SwathHeight;
	पूर्ण

	वापस *MaxNumSwath * SwathHeight + MaxPartialSwath;
पूर्ण

अटल अचिन्हित पूर्णांक CalculateVMAndRowBytes(
		काष्ठा display_mode_lib *mode_lib,
		bool DCCEnable,
		अचिन्हित पूर्णांक BlockHeight256Bytes,
		अचिन्हित पूर्णांक BlockWidth256Bytes,
		क्रमागत source_क्रमmat_class SourcePixelFormat,
		अचिन्हित पूर्णांक SurfaceTiling,
		अचिन्हित पूर्णांक BytePerPixel,
		क्रमागत scan_direction_class ScanDirection,
		अचिन्हित पूर्णांक ViewportWidth,
		अचिन्हित पूर्णांक ViewportHeight,
		अचिन्हित पूर्णांक SwathWidth,
		bool GPUVMEnable,
		bool HostVMEnable,
		अचिन्हित पूर्णांक HostVMMaxPageTableLevels,
		अचिन्हित पूर्णांक HostVMCachedPageTableLevels,
		अचिन्हित पूर्णांक VMMPageSize,
		अचिन्हित पूर्णांक PTEBufferSizeInRequests,
		अचिन्हित पूर्णांक Pitch,
		अचिन्हित पूर्णांक DCCMetaPitch,
		अचिन्हित पूर्णांक *MacroTileWidth,
		अचिन्हित पूर्णांक *MetaRowByte,
		अचिन्हित पूर्णांक *PixelPTEBytesPerRow,
		bool *PTEBufferSizeNotExceeded,
		अचिन्हित पूर्णांक *dpte_row_width_ub,
		अचिन्हित पूर्णांक *dpte_row_height,
		अचिन्हित पूर्णांक *MetaRequestWidth,
		अचिन्हित पूर्णांक *MetaRequestHeight,
		अचिन्हित पूर्णांक *meta_row_width,
		अचिन्हित पूर्णांक *meta_row_height,
		अचिन्हित पूर्णांक *vm_group_bytes,
		अचिन्हित पूर्णांक *dpte_group_bytes,
		अचिन्हित पूर्णांक *PixelPTEReqWidth,
		अचिन्हित पूर्णांक *PixelPTEReqHeight,
		अचिन्हित पूर्णांक *PTERequestSize,
		अचिन्हित पूर्णांक *DPDE0BytesFrame,
		अचिन्हित पूर्णांक *MetaPTEBytesFrame)
अणु
	अचिन्हित पूर्णांक MPDEBytesFrame;
	अचिन्हित पूर्णांक DCCMetaSurfaceBytes;
	अचिन्हित पूर्णांक MacroTileSizeBytes;
	अचिन्हित पूर्णांक MacroTileHeight;
	अचिन्हित पूर्णांक ExtraDPDEBytesFrame;
	अचिन्हित पूर्णांक PDEAndMetaPTEBytesFrame;
	अचिन्हित पूर्णांक PixelPTEReqHeightPTEs = 0;

	अगर (DCCEnable == true) अणु
		*MetaRequestHeight = 8 * BlockHeight256Bytes;
		*MetaRequestWidth = 8 * BlockWidth256Bytes;
		अगर (ScanDirection == dm_horz) अणु
			*meta_row_height = *MetaRequestHeight;
			*meta_row_width = dml_उच्चमान((द्विगुन) SwathWidth - 1, *MetaRequestWidth)
					+ *MetaRequestWidth;
			*MetaRowByte = *meta_row_width * *MetaRequestHeight * BytePerPixel / 256.0;
		पूर्ण अन्यथा अणु
			*meta_row_height = *MetaRequestWidth;
			*meta_row_width = dml_उच्चमान((द्विगुन) SwathWidth - 1, *MetaRequestHeight)
					+ *MetaRequestHeight;
			*MetaRowByte = *meta_row_width * *MetaRequestWidth * BytePerPixel / 256.0;
		पूर्ण
		अगर (ScanDirection == dm_horz) अणु
			DCCMetaSurfaceBytes = DCCMetaPitch
					* (dml_उच्चमान(ViewportHeight - 1, 64 * BlockHeight256Bytes)
							+ 64 * BlockHeight256Bytes) * BytePerPixel
					/ 256;
		पूर्ण अन्यथा अणु
			DCCMetaSurfaceBytes = DCCMetaPitch
					* (dml_उच्चमान(
							(द्विगुन) ViewportHeight - 1,
							64 * BlockHeight256Bytes)
							+ 64 * BlockHeight256Bytes) * BytePerPixel
					/ 256;
		पूर्ण
		अगर (GPUVMEnable == true) अणु
			*MetaPTEBytesFrame = (dml_उच्चमान(
					(द्विगुन) (DCCMetaSurfaceBytes - VMMPageSize)
							/ (8 * VMMPageSize),
					1) + 1) * 64;
			MPDEBytesFrame = 128 * ((mode_lib->vba.GPUVMMaxPageTableLevels + 1) * (mode_lib->vba.HostVMMaxPageTableLevels + 1) - 2);
		पूर्ण अन्यथा अणु
			*MetaPTEBytesFrame = 0;
			MPDEBytesFrame = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		*MetaPTEBytesFrame = 0;
		MPDEBytesFrame = 0;
		*MetaRowByte = 0;
	पूर्ण

	अगर (SurfaceTiling == dm_sw_linear || SurfaceTiling == dm_sw_gfx7_2d_thin_gl || SurfaceTiling == dm_sw_gfx7_2d_thin_l_vp) अणु
		MacroTileSizeBytes = 256;
		MacroTileHeight = BlockHeight256Bytes;
	पूर्ण अन्यथा अगर (SurfaceTiling == dm_sw_4kb_s || SurfaceTiling == dm_sw_4kb_s_x
			|| SurfaceTiling == dm_sw_4kb_d || SurfaceTiling == dm_sw_4kb_d_x) अणु
		MacroTileSizeBytes = 4096;
		MacroTileHeight = 4 * BlockHeight256Bytes;
	पूर्ण अन्यथा अगर (SurfaceTiling == dm_sw_64kb_s || SurfaceTiling == dm_sw_64kb_s_t
			|| SurfaceTiling == dm_sw_64kb_s_x || SurfaceTiling == dm_sw_64kb_d
			|| SurfaceTiling == dm_sw_64kb_d_t || SurfaceTiling == dm_sw_64kb_d_x
			|| SurfaceTiling == dm_sw_64kb_r_x) अणु
		MacroTileSizeBytes = 65536;
		MacroTileHeight = 16 * BlockHeight256Bytes;
	पूर्ण अन्यथा अणु
		MacroTileSizeBytes = 262144;
		MacroTileHeight = 32 * BlockHeight256Bytes;
	पूर्ण
	*MacroTileWidth = MacroTileSizeBytes / BytePerPixel / MacroTileHeight;

	अगर (GPUVMEnable == true && (mode_lib->vba.GPUVMMaxPageTableLevels + 1) * (mode_lib->vba.HostVMMaxPageTableLevels + 1) > 2) अणु
		अगर (ScanDirection == dm_horz) अणु
			*DPDE0BytesFrame = 64 * (dml_उच्चमान(((Pitch * (dml_उच्चमान(ViewportHeight - 1, MacroTileHeight) + MacroTileHeight) * BytePerPixel) - MacroTileSizeBytes) / (8 * 2097152), 1) + 1);
		पूर्ण अन्यथा अणु
			*DPDE0BytesFrame = 64 * (dml_उच्चमान(((Pitch * (dml_उच्चमान((द्विगुन) SwathWidth - 1, MacroTileHeight) + MacroTileHeight) * BytePerPixel) - MacroTileSizeBytes) / (8 * 2097152), 1) + 1);
		पूर्ण
		ExtraDPDEBytesFrame = 128 * ((mode_lib->vba.GPUVMMaxPageTableLevels + 1) * (mode_lib->vba.HostVMMaxPageTableLevels + 1) - 3);
	पूर्ण अन्यथा अणु
		*DPDE0BytesFrame = 0;
		ExtraDPDEBytesFrame = 0;
	पूर्ण

	PDEAndMetaPTEBytesFrame = *MetaPTEBytesFrame + MPDEBytesFrame + *DPDE0BytesFrame
			+ ExtraDPDEBytesFrame;

	अगर (HostVMEnable == true) अणु
		PDEAndMetaPTEBytesFrame = PDEAndMetaPTEBytesFrame * (1 + 8 * (HostVMMaxPageTableLevels - HostVMCachedPageTableLevels));
	पूर्ण

	अगर (GPUVMEnable == true) अणु
		द्विगुन FractionOfPTEReturnDrop;

		अगर (SurfaceTiling == dm_sw_linear) अणु
			PixelPTEReqHeightPTEs = 1;
			*PixelPTEReqHeight = 1;
			*PixelPTEReqWidth = 8.0 * VMMPageSize / BytePerPixel;
			*PTERequestSize = 64;
			FractionOfPTEReturnDrop = 0;
		पूर्ण अन्यथा अगर (MacroTileSizeBytes == 4096) अणु
			PixelPTEReqHeightPTEs = 1;
			*PixelPTEReqHeight = MacroTileHeight;
			*PixelPTEReqWidth = 8 * *MacroTileWidth;
			*PTERequestSize = 64;
			अगर (ScanDirection == dm_horz)
				FractionOfPTEReturnDrop = 0;
			अन्यथा
				FractionOfPTEReturnDrop = 7 / 8;
		पूर्ण अन्यथा अगर (VMMPageSize == 4096 && MacroTileSizeBytes > 4096) अणु
			PixelPTEReqHeightPTEs = 16;
			*PixelPTEReqHeight = 16 * BlockHeight256Bytes;
			*PixelPTEReqWidth = 16 * BlockWidth256Bytes;
			*PTERequestSize = 128;
			FractionOfPTEReturnDrop = 0;
		पूर्ण अन्यथा अणु
			PixelPTEReqHeightPTEs = 1;
			*PixelPTEReqHeight = MacroTileHeight;
			*PixelPTEReqWidth = 8 * *MacroTileWidth;
			*PTERequestSize = 64;
			FractionOfPTEReturnDrop = 0;
		पूर्ण

		अगर (SurfaceTiling == dm_sw_linear) अणु
			*dpte_row_height = dml_min(128,
					1 << (अचिन्हित पूर्णांक) dml_न्यूनमान(
						dml_log2(
							(द्विगुन) PTEBufferSizeInRequests * *PixelPTEReqWidth / Pitch),
						1));
			*dpte_row_width_ub = (dml_उच्चमान((द्विगुन) (Pitch * *dpte_row_height - 1) / *PixelPTEReqWidth, 1) + 1) * *PixelPTEReqWidth;
			*PixelPTEBytesPerRow = *dpte_row_width_ub / *PixelPTEReqWidth * *PTERequestSize;
		पूर्ण अन्यथा अगर (ScanDirection == dm_horz) अणु
			*dpte_row_height = *PixelPTEReqHeight;
			*dpte_row_width_ub = (dml_उच्चमान((द्विगुन) (SwathWidth - 1) / *PixelPTEReqWidth, 1) + 1) * *PixelPTEReqWidth;
			*PixelPTEBytesPerRow = *dpte_row_width_ub / *PixelPTEReqWidth * *PTERequestSize;
		पूर्ण अन्यथा अणु
			*dpte_row_height = dml_min(*PixelPTEReqWidth, *MacroTileWidth);
			*dpte_row_width_ub = (dml_उच्चमान((द्विगुन) (SwathWidth - 1) / *PixelPTEReqHeight, 1) + 1) * *PixelPTEReqHeight;
			*PixelPTEBytesPerRow = *dpte_row_width_ub / *PixelPTEReqHeight * *PTERequestSize;
		पूर्ण
		अगर (*PixelPTEBytesPerRow * (1 - FractionOfPTEReturnDrop)
				<= 64 * PTEBufferSizeInRequests) अणु
			*PTEBufferSizeNotExceeded = true;
		पूर्ण अन्यथा अणु
			*PTEBufferSizeNotExceeded = false;
		पूर्ण
	पूर्ण अन्यथा अणु
		*PixelPTEBytesPerRow = 0;
		*PTEBufferSizeNotExceeded = true;
	पूर्ण
	dml_prपूर्णांक("DML: vm_bytes = meta_pte_bytes_per_frame (per_pipe) = MetaPTEBytesFrame = : %d\n", *MetaPTEBytesFrame);

	अगर (HostVMEnable == true) अणु
		*PixelPTEBytesPerRow = *PixelPTEBytesPerRow * (1 + 8 * (HostVMMaxPageTableLevels - HostVMCachedPageTableLevels));
	पूर्ण

	अगर (HostVMEnable == true) अणु
		*vm_group_bytes = 512;
		*dpte_group_bytes = 512;
	पूर्ण अन्यथा अगर (GPUVMEnable == true) अणु
		*vm_group_bytes = 2048;
		अगर (SurfaceTiling != dm_sw_linear && PixelPTEReqHeightPTEs == 1 && ScanDirection != dm_horz) अणु
			*dpte_group_bytes = 512;
		पूर्ण अन्यथा अणु
			*dpte_group_bytes = 2048;
		पूर्ण
	पूर्ण अन्यथा अणु
		*vm_group_bytes = 0;
		*dpte_group_bytes = 0;
	पूर्ण

	वापस PDEAndMetaPTEBytesFrame;
पूर्ण

अटल व्योम DISPCLKDPPCLKDCFCLKDeepSleepPrefetchParametersWatermarksAndPerक्रमmanceCalculation(
		काष्ठा display_mode_lib *mode_lib)
अणु
	काष्ठा vba_vars_st *locals = &mode_lib->vba;
	अचिन्हित पूर्णांक j, k;

	mode_lib->vba.WritebackDISPCLK = 0.0;
	mode_lib->vba.DISPCLKWithRamping = 0;
	mode_lib->vba.DISPCLKWithoutRamping = 0;
	mode_lib->vba.GlobalDPPCLK = 0.0;

	// DISPCLK and DPPCLK Calculation
	//
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		अगर (mode_lib->vba.WritebackEnable[k]) अणु
			mode_lib->vba.WritebackDISPCLK =
					dml_max(
							mode_lib->vba.WritebackDISPCLK,
							CalculateWriteBackDISPCLK(
									mode_lib->vba.WritebackPixelFormat[k],
									mode_lib->vba.PixelClock[k],
									mode_lib->vba.WritebackHRatio[k],
									mode_lib->vba.WritebackVRatio[k],
									mode_lib->vba.WritebackLumaHTaps[k],
									mode_lib->vba.WritebackLumaVTaps[k],
									mode_lib->vba.WritebackChromaHTaps[k],
									mode_lib->vba.WritebackChromaVTaps[k],
									mode_lib->vba.WritebackDestinationWidth[k],
									mode_lib->vba.HTotal[k],
									mode_lib->vba.WritebackChromaLineBufferWidth));
		पूर्ण
	पूर्ण

	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		अगर (mode_lib->vba.HRatio[k] > 1) अणु
			locals->PSCL_THROUGHPUT_LUMA[k] = dml_min(
					mode_lib->vba.MaxDCHUBToPSCLThroughput,
					mode_lib->vba.MaxPSCLToLBThroughput
							* mode_lib->vba.HRatio[k]
							/ dml_उच्चमान(
									mode_lib->vba.htaps[k]
											/ 6.0,
									1));
		पूर्ण अन्यथा अणु
			locals->PSCL_THROUGHPUT_LUMA[k] = dml_min(
					mode_lib->vba.MaxDCHUBToPSCLThroughput,
					mode_lib->vba.MaxPSCLToLBThroughput);
		पूर्ण

		mode_lib->vba.DPPCLKUsingSingleDPPLuma =
				mode_lib->vba.PixelClock[k]
						* dml_max(
								mode_lib->vba.vtaps[k] / 6.0
										* dml_min(
												1.0,
												mode_lib->vba.HRatio[k]),
								dml_max(
										mode_lib->vba.HRatio[k]
												* mode_lib->vba.VRatio[k]
												/ locals->PSCL_THROUGHPUT_LUMA[k],
										1.0));

		अगर ((mode_lib->vba.htaps[k] > 6 || mode_lib->vba.vtaps[k] > 6)
				&& mode_lib->vba.DPPCLKUsingSingleDPPLuma
						< 2 * mode_lib->vba.PixelClock[k]) अणु
			mode_lib->vba.DPPCLKUsingSingleDPPLuma = 2 * mode_lib->vba.PixelClock[k];
		पूर्ण

		अगर ((mode_lib->vba.SourcePixelFormat[k] != dm_420_8
				&& mode_lib->vba.SourcePixelFormat[k] != dm_420_10)) अणु
			locals->PSCL_THROUGHPUT_CHROMA[k] = 0.0;
			locals->DPPCLKUsingSingleDPP[k] =
					mode_lib->vba.DPPCLKUsingSingleDPPLuma;
		पूर्ण अन्यथा अणु
			अगर (mode_lib->vba.HRatio[k] > 1) अणु
				locals->PSCL_THROUGHPUT_CHROMA[k] =
						dml_min(
								mode_lib->vba.MaxDCHUBToPSCLThroughput,
								mode_lib->vba.MaxPSCLToLBThroughput
										* mode_lib->vba.HRatio[k]
										/ 2
										/ dml_उच्चमान(
												mode_lib->vba.HTAPsChroma[k]
														/ 6.0,
												1.0));
			पूर्ण अन्यथा अणु
				locals->PSCL_THROUGHPUT_CHROMA[k] = dml_min(
						mode_lib->vba.MaxDCHUBToPSCLThroughput,
						mode_lib->vba.MaxPSCLToLBThroughput);
			पूर्ण
			mode_lib->vba.DPPCLKUsingSingleDPPChroma =
					mode_lib->vba.PixelClock[k]
							* dml_max(
									mode_lib->vba.VTAPsChroma[k]
											/ 6.0
											* dml_min(
													1.0,
													mode_lib->vba.HRatio[k]
															/ 2),
									dml_max(
											mode_lib->vba.HRatio[k]
													* mode_lib->vba.VRatio[k]
													/ 4
													/ locals->PSCL_THROUGHPUT_CHROMA[k],
											1.0));

			अगर ((mode_lib->vba.HTAPsChroma[k] > 6 || mode_lib->vba.VTAPsChroma[k] > 6)
					&& mode_lib->vba.DPPCLKUsingSingleDPPChroma
							< 2 * mode_lib->vba.PixelClock[k]) अणु
				mode_lib->vba.DPPCLKUsingSingleDPPChroma = 2
						* mode_lib->vba.PixelClock[k];
			पूर्ण

			locals->DPPCLKUsingSingleDPP[k] = dml_max(
					mode_lib->vba.DPPCLKUsingSingleDPPLuma,
					mode_lib->vba.DPPCLKUsingSingleDPPChroma);
		पूर्ण
	पूर्ण

	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		अगर (mode_lib->vba.BlendingAndTiming[k] != k)
			जारी;
		अगर (mode_lib->vba.ODMCombineEnabled[k]) अणु
			mode_lib->vba.DISPCLKWithRamping =
					dml_max(
							mode_lib->vba.DISPCLKWithRamping,
							mode_lib->vba.PixelClock[k] / 2
									* (1
											+ mode_lib->vba.DISPCLKDPPCLKDSCCLKDownSpपढ़ोing
													/ 100)
									* (1
											+ mode_lib->vba.DISPCLKRampingMargin
													/ 100));
			mode_lib->vba.DISPCLKWithoutRamping =
					dml_max(
							mode_lib->vba.DISPCLKWithoutRamping,
							mode_lib->vba.PixelClock[k] / 2
									* (1
											+ mode_lib->vba.DISPCLKDPPCLKDSCCLKDownSpपढ़ोing
													/ 100));
		पूर्ण अन्यथा अगर (!mode_lib->vba.ODMCombineEnabled[k]) अणु
			mode_lib->vba.DISPCLKWithRamping =
					dml_max(
							mode_lib->vba.DISPCLKWithRamping,
							mode_lib->vba.PixelClock[k]
									* (1
											+ mode_lib->vba.DISPCLKDPPCLKDSCCLKDownSpपढ़ोing
													/ 100)
									* (1
											+ mode_lib->vba.DISPCLKRampingMargin
													/ 100));
			mode_lib->vba.DISPCLKWithoutRamping =
					dml_max(
							mode_lib->vba.DISPCLKWithoutRamping,
							mode_lib->vba.PixelClock[k]
									* (1
											+ mode_lib->vba.DISPCLKDPPCLKDSCCLKDownSpपढ़ोing
													/ 100));
		पूर्ण
	पूर्ण

	mode_lib->vba.DISPCLKWithRamping = dml_max(
			mode_lib->vba.DISPCLKWithRamping,
			mode_lib->vba.WritebackDISPCLK);
	mode_lib->vba.DISPCLKWithoutRamping = dml_max(
			mode_lib->vba.DISPCLKWithoutRamping,
			mode_lib->vba.WritebackDISPCLK);

	ASSERT(mode_lib->vba.DISPCLKDPPCLKVCOSpeed != 0);
	mode_lib->vba.DISPCLKWithRampingRoundedToDFSGranularity = RoundToDFSGranularityUp(
			mode_lib->vba.DISPCLKWithRamping,
			mode_lib->vba.DISPCLKDPPCLKVCOSpeed);
	mode_lib->vba.DISPCLKWithoutRampingRoundedToDFSGranularity = RoundToDFSGranularityUp(
			mode_lib->vba.DISPCLKWithoutRamping,
			mode_lib->vba.DISPCLKDPPCLKVCOSpeed);
	mode_lib->vba.MaxDispclkRoundedToDFSGranularity = RoundToDFSGranularityDown(
			mode_lib->vba.soc.घड़ी_limits[mode_lib->vba.soc.num_states - 1].dispclk_mhz,
			mode_lib->vba.DISPCLKDPPCLKVCOSpeed);
	अगर (mode_lib->vba.DISPCLKWithoutRampingRoundedToDFSGranularity
			> mode_lib->vba.MaxDispclkRoundedToDFSGranularity) अणु
		mode_lib->vba.DISPCLK_calculated =
				mode_lib->vba.DISPCLKWithoutRampingRoundedToDFSGranularity;
	पूर्ण अन्यथा अगर (mode_lib->vba.DISPCLKWithRampingRoundedToDFSGranularity
			> mode_lib->vba.MaxDispclkRoundedToDFSGranularity) अणु
		mode_lib->vba.DISPCLK_calculated = mode_lib->vba.MaxDispclkRoundedToDFSGranularity;
	पूर्ण अन्यथा अणु
		mode_lib->vba.DISPCLK_calculated =
				mode_lib->vba.DISPCLKWithRampingRoundedToDFSGranularity;
	पूर्ण
	DTRACE("   dispclk_mhz (calculated) = %f", mode_lib->vba.DISPCLK_calculated);

	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		mode_lib->vba.DPPCLK_calculated[k] = locals->DPPCLKUsingSingleDPP[k]
				/ mode_lib->vba.DPPPerPlane[k]
				* (1 + mode_lib->vba.DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100);
		mode_lib->vba.GlobalDPPCLK = dml_max(
				mode_lib->vba.GlobalDPPCLK,
				mode_lib->vba.DPPCLK_calculated[k]);
	पूर्ण
	mode_lib->vba.GlobalDPPCLK = RoundToDFSGranularityUp(
			mode_lib->vba.GlobalDPPCLK,
			mode_lib->vba.DISPCLKDPPCLKVCOSpeed);
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		mode_lib->vba.DPPCLK_calculated[k] = mode_lib->vba.GlobalDPPCLK / 255
				* dml_उच्चमान(
						mode_lib->vba.DPPCLK_calculated[k] * 255
								/ mode_lib->vba.GlobalDPPCLK,
						1);
		DTRACE("   dppclk_mhz[%i] (calculated) = %f", k, mode_lib->vba.DPPCLK_calculated[k]);
	पूर्ण

	// Urgent and B P-State/DRAM Clock Change Watermark
	DTRACE("   dcfclk_mhz         = %f", mode_lib->vba.DCFCLK);
	DTRACE("   return_bw_to_dcn   = %f", mode_lib->vba.ReturnBandwidthToDCN);
	DTRACE("   return_bus_bw      = %f", mode_lib->vba.ReturnBW);

	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		bool MainPlaneDoesODMCombine = false;

		अगर (mode_lib->vba.SourceScan[k] == dm_horz)
			locals->SwathWidthSingleDPPY[k] = mode_lib->vba.ViewportWidth[k];
		अन्यथा
			locals->SwathWidthSingleDPPY[k] = mode_lib->vba.ViewportHeight[k];

		अगर (mode_lib->vba.ODMCombineEnabled[k] == dm_odm_combine_mode_2to1)
			MainPlaneDoesODMCombine = true;
		क्रम (j = 0; j < mode_lib->vba.NumberOfActivePlanes; ++j)
			अगर (mode_lib->vba.BlendingAndTiming[k] == j
					&& mode_lib->vba.ODMCombineEnabled[k] == dm_odm_combine_mode_2to1)
				MainPlaneDoesODMCombine = true;

		अगर (MainPlaneDoesODMCombine == true)
			locals->SwathWidthY[k] = dml_min(
					(द्विगुन) locals->SwathWidthSingleDPPY[k],
					dml_round(
							mode_lib->vba.HActive[k] / 2.0
									* mode_lib->vba.HRatio[k]));
		अन्यथा
			locals->SwathWidthY[k] = locals->SwathWidthSingleDPPY[k]
					/ mode_lib->vba.DPPPerPlane[k];
	पूर्ण

	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		अगर (mode_lib->vba.SourcePixelFormat[k] == dm_444_64) अणु
			locals->BytePerPixelDETY[k] = 8;
			locals->BytePerPixelDETC[k] = 0;
		पूर्ण अन्यथा अगर (mode_lib->vba.SourcePixelFormat[k] == dm_444_32) अणु
			locals->BytePerPixelDETY[k] = 4;
			locals->BytePerPixelDETC[k] = 0;
		पूर्ण अन्यथा अगर (mode_lib->vba.SourcePixelFormat[k] == dm_444_16 || mode_lib->vba.SourcePixelFormat[k] == dm_mono_16) अणु
			locals->BytePerPixelDETY[k] = 2;
			locals->BytePerPixelDETC[k] = 0;
		पूर्ण अन्यथा अगर (mode_lib->vba.SourcePixelFormat[k] == dm_444_8 || mode_lib->vba.SourcePixelFormat[k] == dm_mono_8) अणु
			locals->BytePerPixelDETY[k] = 1;
			locals->BytePerPixelDETC[k] = 0;
		पूर्ण अन्यथा अगर (mode_lib->vba.SourcePixelFormat[k] == dm_420_8) अणु
			locals->BytePerPixelDETY[k] = 1;
			locals->BytePerPixelDETC[k] = 2;
		पूर्ण अन्यथा अणु // dm_420_10
			locals->BytePerPixelDETY[k] = 4.0 / 3.0;
			locals->BytePerPixelDETC[k] = 8.0 / 3.0;
		पूर्ण
	पूर्ण

	mode_lib->vba.TotalDataReadBandwidth = 0.0;
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		locals->ReadBandwidthPlaneLuma[k] = locals->SwathWidthSingleDPPY[k]
				* dml_उच्चमान(locals->BytePerPixelDETY[k], 1)
				/ (mode_lib->vba.HTotal[k] / mode_lib->vba.PixelClock[k])
				* mode_lib->vba.VRatio[k];
		locals->ReadBandwidthPlaneChroma[k] = locals->SwathWidthSingleDPPY[k]
				/ 2 * dml_उच्चमान(locals->BytePerPixelDETC[k], 2)
				/ (mode_lib->vba.HTotal[k] / mode_lib->vba.PixelClock[k])
				* mode_lib->vba.VRatio[k] / 2;
		DTRACE(
				"   read_bw[%i] = %fBps",
				k,
				locals->ReadBandwidthPlaneLuma[k]
						+ locals->ReadBandwidthPlaneChroma[k]);
		mode_lib->vba.TotalDataReadBandwidth += locals->ReadBandwidthPlaneLuma[k]
				+ locals->ReadBandwidthPlaneChroma[k];
	पूर्ण

	// DCFCLK Deep Sleep
	CalculateDCFCLKDeepSleep(
		mode_lib,
		mode_lib->vba.NumberOfActivePlanes,
		locals->BytePerPixelDETY,
		locals->BytePerPixelDETC,
		mode_lib->vba.VRatio,
		locals->SwathWidthY,
		mode_lib->vba.DPPPerPlane,
		mode_lib->vba.HRatio,
		mode_lib->vba.PixelClock,
		locals->PSCL_THROUGHPUT_LUMA,
		locals->PSCL_THROUGHPUT_CHROMA,
		locals->DPPCLK,
		&mode_lib->vba.DCFCLKDeepSleep);

	// DSCCLK
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		अगर ((mode_lib->vba.BlendingAndTiming[k] != k) || !mode_lib->vba.DSCEnabled[k]) अणु
			locals->DSCCLK_calculated[k] = 0.0;
		पूर्ण अन्यथा अणु
			अगर (mode_lib->vba.OutputFormat[k] == dm_420
					|| mode_lib->vba.OutputFormat[k] == dm_n422)
				mode_lib->vba.DSCFormatFactor = 2;
			अन्यथा
				mode_lib->vba.DSCFormatFactor = 1;
			अगर (mode_lib->vba.ODMCombineEnabled[k])
				locals->DSCCLK_calculated[k] =
						mode_lib->vba.PixelClockBackEnd[k] / 6
								/ mode_lib->vba.DSCFormatFactor
								/ (1
										- mode_lib->vba.DISPCLKDPPCLKDSCCLKDownSpपढ़ोing
												/ 100);
			अन्यथा
				locals->DSCCLK_calculated[k] =
						mode_lib->vba.PixelClockBackEnd[k] / 3
								/ mode_lib->vba.DSCFormatFactor
								/ (1
										- mode_lib->vba.DISPCLKDPPCLKDSCCLKDownSpपढ़ोing
												/ 100);
		पूर्ण
	पूर्ण

	// DSC Delay
	// TODO
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		द्विगुन bpp = mode_lib->vba.OutputBpp[k];
		अचिन्हित पूर्णांक slices = mode_lib->vba.NumberOfDSCSlices[k];

		अगर (mode_lib->vba.DSCEnabled[k] && bpp != 0) अणु
			अगर (!mode_lib->vba.ODMCombineEnabled[k]) अणु
				locals->DSCDelay[k] =
						dscceComputeDelay(
								mode_lib->vba.DSCInputBitPerComponent[k],
								bpp,
								dml_उच्चमान(
										(द्विगुन) mode_lib->vba.HActive[k]
												/ mode_lib->vba.NumberOfDSCSlices[k],
										1),
								slices,
								mode_lib->vba.OutputFormat[k])
								+ dscComputeDelay(
										mode_lib->vba.OutputFormat[k]);
			पूर्ण अन्यथा अणु
				locals->DSCDelay[k] =
						2
								* (dscceComputeDelay(
										mode_lib->vba.DSCInputBitPerComponent[k],
										bpp,
										dml_उच्चमान(
												(द्विगुन) mode_lib->vba.HActive[k]
														/ mode_lib->vba.NumberOfDSCSlices[k],
												1),
										slices / 2.0,
										mode_lib->vba.OutputFormat[k])
										+ dscComputeDelay(
												mode_lib->vba.OutputFormat[k]));
			पूर्ण
			locals->DSCDelay[k] = locals->DSCDelay[k]
					* mode_lib->vba.PixelClock[k]
					/ mode_lib->vba.PixelClockBackEnd[k];
		पूर्ण अन्यथा अणु
			locals->DSCDelay[k] = 0;
		पूर्ण
	पूर्ण

	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k)
		क्रम (j = 0; j < mode_lib->vba.NumberOfActivePlanes; ++j) // NumberOfPlanes
			अगर (j != k && mode_lib->vba.BlendingAndTiming[k] == j
					&& mode_lib->vba.DSCEnabled[j])
				locals->DSCDelay[k] = locals->DSCDelay[j];

	// Prefetch
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		अचिन्हित पूर्णांक PDEAndMetaPTEBytesFrameY;
		अचिन्हित पूर्णांक PixelPTEBytesPerRowY;
		अचिन्हित पूर्णांक MetaRowByteY;
		अचिन्हित पूर्णांक MetaRowByteC;
		अचिन्हित पूर्णांक PDEAndMetaPTEBytesFrameC;
		अचिन्हित पूर्णांक PixelPTEBytesPerRowC;
		bool         PTEBufferSizeNotExceededY;
		bool         PTEBufferSizeNotExceededC;

		Calculate256BBlockSizes(
				mode_lib->vba.SourcePixelFormat[k],
				mode_lib->vba.SurfaceTiling[k],
				dml_उच्चमान(locals->BytePerPixelDETY[k], 1),
				dml_उच्चमान(locals->BytePerPixelDETC[k], 2),
				&locals->BlockHeight256BytesY[k],
				&locals->BlockHeight256BytesC[k],
				&locals->BlockWidth256BytesY[k],
				&locals->BlockWidth256BytesC[k]);

		locals->PrefetchSourceLinesY[k] = CalculatePrefetchSourceLines(
				mode_lib,
				mode_lib->vba.VRatio[k],
				mode_lib->vba.vtaps[k],
				mode_lib->vba.Interlace[k],
				mode_lib->vba.ProgressiveToInterlaceUnitInOPP,
				mode_lib->vba.SwathHeightY[k],
				mode_lib->vba.ViewportYStartY[k],
				&locals->VInitPreFillY[k],
				&locals->MaxNumSwathY[k]);

		अगर ((mode_lib->vba.SourcePixelFormat[k] != dm_444_64
				&& mode_lib->vba.SourcePixelFormat[k] != dm_444_32
				&& mode_lib->vba.SourcePixelFormat[k] != dm_444_16
				&& mode_lib->vba.SourcePixelFormat[k] != dm_444_8)) अणु
			PDEAndMetaPTEBytesFrameC =
					CalculateVMAndRowBytes(
							mode_lib,
							mode_lib->vba.DCCEnable[k],
							locals->BlockHeight256BytesC[k],
							locals->BlockWidth256BytesC[k],
							mode_lib->vba.SourcePixelFormat[k],
							mode_lib->vba.SurfaceTiling[k],
							dml_उच्चमान(
									locals->BytePerPixelDETC[k],
									2),
							mode_lib->vba.SourceScan[k],
							mode_lib->vba.ViewportWidth[k] / 2,
							mode_lib->vba.ViewportHeight[k] / 2,
							locals->SwathWidthY[k] / 2,
							mode_lib->vba.GPUVMEnable,
							mode_lib->vba.HostVMEnable,
							mode_lib->vba.HostVMMaxPageTableLevels,
							mode_lib->vba.HostVMCachedPageTableLevels,
							mode_lib->vba.VMMPageSize,
							mode_lib->vba.PTEBufferSizeInRequestsChroma,
							mode_lib->vba.PitchC[k],
							mode_lib->vba.DCCMetaPitchC[k],
							&locals->MacroTileWidthC[k],
							&MetaRowByteC,
							&PixelPTEBytesPerRowC,
							&PTEBufferSizeNotExceededC,
							&locals->dpte_row_width_chroma_ub[k],
							&locals->dpte_row_height_chroma[k],
							&locals->meta_req_width_chroma[k],
							&locals->meta_req_height_chroma[k],
							&locals->meta_row_width_chroma[k],
							&locals->meta_row_height_chroma[k],
							&locals->vm_group_bytes_chroma,
							&locals->dpte_group_bytes_chroma,
							&locals->PixelPTEReqWidthC[k],
							&locals->PixelPTEReqHeightC[k],
							&locals->PTERequestSizeC[k],
							&locals->dpde0_bytes_per_frame_ub_c[k],
							&locals->meta_pte_bytes_per_frame_ub_c[k]);

			locals->PrefetchSourceLinesC[k] = CalculatePrefetchSourceLines(
					mode_lib,
					mode_lib->vba.VRatio[k] / 2,
					mode_lib->vba.VTAPsChroma[k],
					mode_lib->vba.Interlace[k],
					mode_lib->vba.ProgressiveToInterlaceUnitInOPP,
					mode_lib->vba.SwathHeightC[k],
					mode_lib->vba.ViewportYStartC[k],
					&locals->VInitPreFillC[k],
					&locals->MaxNumSwathC[k]);
		पूर्ण अन्यथा अणु
			PixelPTEBytesPerRowC = 0;
			PDEAndMetaPTEBytesFrameC = 0;
			MetaRowByteC = 0;
			locals->MaxNumSwathC[k] = 0;
			locals->PrefetchSourceLinesC[k] = 0;
			locals->PTEBufferSizeInRequestsForLuma = mode_lib->vba.PTEBufferSizeInRequestsLuma + mode_lib->vba.PTEBufferSizeInRequestsChroma;
		पूर्ण

		PDEAndMetaPTEBytesFrameY = CalculateVMAndRowBytes(
				mode_lib,
				mode_lib->vba.DCCEnable[k],
				locals->BlockHeight256BytesY[k],
				locals->BlockWidth256BytesY[k],
				mode_lib->vba.SourcePixelFormat[k],
				mode_lib->vba.SurfaceTiling[k],
				dml_उच्चमान(locals->BytePerPixelDETY[k], 1),
				mode_lib->vba.SourceScan[k],
				mode_lib->vba.ViewportWidth[k],
				mode_lib->vba.ViewportHeight[k],
				locals->SwathWidthY[k],
				mode_lib->vba.GPUVMEnable,
				mode_lib->vba.HostVMEnable,
				mode_lib->vba.HostVMMaxPageTableLevels,
				mode_lib->vba.HostVMCachedPageTableLevels,
				mode_lib->vba.VMMPageSize,
				locals->PTEBufferSizeInRequestsForLuma,
				mode_lib->vba.PitchY[k],
				mode_lib->vba.DCCMetaPitchY[k],
				&locals->MacroTileWidthY[k],
				&MetaRowByteY,
				&PixelPTEBytesPerRowY,
				&PTEBufferSizeNotExceededY,
				&locals->dpte_row_width_luma_ub[k],
				&locals->dpte_row_height[k],
				&locals->meta_req_width[k],
				&locals->meta_req_height[k],
				&locals->meta_row_width[k],
				&locals->meta_row_height[k],
				&locals->vm_group_bytes[k],
				&locals->dpte_group_bytes[k],
				&locals->PixelPTEReqWidthY[k],
				&locals->PixelPTEReqHeightY[k],
				&locals->PTERequestSizeY[k],
				&locals->dpde0_bytes_per_frame_ub_l[k],
				&locals->meta_pte_bytes_per_frame_ub_l[k]);

		locals->PixelPTEBytesPerRow[k] = PixelPTEBytesPerRowY + PixelPTEBytesPerRowC;
		locals->PDEAndMetaPTEBytesFrame[k] = PDEAndMetaPTEBytesFrameY
				+ PDEAndMetaPTEBytesFrameC;
		locals->MetaRowByte[k] = MetaRowByteY + MetaRowByteC;

		CalculateActiveRowBandwidth(
				mode_lib->vba.GPUVMEnable,
				mode_lib->vba.SourcePixelFormat[k],
				mode_lib->vba.VRatio[k],
				mode_lib->vba.DCCEnable[k],
				mode_lib->vba.HTotal[k] / mode_lib->vba.PixelClock[k],
				MetaRowByteY,
				MetaRowByteC,
				locals->meta_row_height[k],
				locals->meta_row_height_chroma[k],
				PixelPTEBytesPerRowY,
				PixelPTEBytesPerRowC,
				locals->dpte_row_height[k],
				locals->dpte_row_height_chroma[k],
				&locals->meta_row_bw[k],
				&locals->dpte_row_bw[k]);
	पूर्ण

	mode_lib->vba.TotalDCCActiveDPP = 0;
	mode_lib->vba.TotalActiveDPP = 0;
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		mode_lib->vba.TotalActiveDPP = mode_lib->vba.TotalActiveDPP
				+ mode_lib->vba.DPPPerPlane[k];
		अगर (mode_lib->vba.DCCEnable[k])
			mode_lib->vba.TotalDCCActiveDPP = mode_lib->vba.TotalDCCActiveDPP
					+ mode_lib->vba.DPPPerPlane[k];
	पूर्ण

	mode_lib->vba.UrgentOutOfOrderReturnPerChannel = dml_max3(
			mode_lib->vba.UrgentOutOfOrderReturnPerChannelPixelDataOnly,
			mode_lib->vba.UrgentOutOfOrderReturnPerChannelPixelMixedWithVMData,
			mode_lib->vba.UrgentOutOfOrderReturnPerChannelVMDataOnly);

	mode_lib->vba.UrgentRoundTripAndOutOfOrderLatency =
			(mode_lib->vba.RoundTripPingLatencyCycles + 32) / mode_lib->vba.DCFCLK
					+ mode_lib->vba.UrgentOutOfOrderReturnPerChannel
							* mode_lib->vba.NumberOfChannels
							/ mode_lib->vba.ReturnBW;

	mode_lib->vba.UrgentExtraLatency = CalculateExtraLatency(
			mode_lib->vba.UrgentRoundTripAndOutOfOrderLatency,
			mode_lib->vba.TotalActiveDPP,
			mode_lib->vba.PixelChunkSizeInKByte,
			mode_lib->vba.TotalDCCActiveDPP,
			mode_lib->vba.MetaChunkSize,
			mode_lib->vba.ReturnBW,
			mode_lib->vba.GPUVMEnable,
			mode_lib->vba.HostVMEnable,
			mode_lib->vba.NumberOfActivePlanes,
			mode_lib->vba.DPPPerPlane,
			locals->dpte_group_bytes,
			mode_lib->vba.PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData,
			mode_lib->vba.PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly,
			mode_lib->vba.HostVMMaxPageTableLevels,
			mode_lib->vba.HostVMCachedPageTableLevels);


	mode_lib->vba.TCalc = 24.0 / mode_lib->vba.DCFCLKDeepSleep;

	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		अगर (mode_lib->vba.BlendingAndTiming[k] == k) अणु
			अगर (mode_lib->vba.WritebackEnable[k] == true) अणु
				locals->WritebackDelay[mode_lib->vba.VoltageLevel][k] =
						mode_lib->vba.WritebackLatency
								+ CalculateWriteBackDelay(
										mode_lib->vba.WritebackPixelFormat[k],
										mode_lib->vba.WritebackHRatio[k],
										mode_lib->vba.WritebackVRatio[k],
										mode_lib->vba.WritebackLumaHTaps[k],
										mode_lib->vba.WritebackLumaVTaps[k],
										mode_lib->vba.WritebackChromaHTaps[k],
										mode_lib->vba.WritebackChromaVTaps[k],
										mode_lib->vba.WritebackDestinationWidth[k])
										/ mode_lib->vba.DISPCLK;
			पूर्ण अन्यथा
				locals->WritebackDelay[mode_lib->vba.VoltageLevel][k] = 0;
			क्रम (j = 0; j < mode_lib->vba.NumberOfActivePlanes; ++j) अणु
				अगर (mode_lib->vba.BlendingAndTiming[j] == k
						&& mode_lib->vba.WritebackEnable[j] == true) अणु
					locals->WritebackDelay[mode_lib->vba.VoltageLevel][k] =
							dml_max(
									locals->WritebackDelay[mode_lib->vba.VoltageLevel][k],
									mode_lib->vba.WritebackLatency
											+ CalculateWriteBackDelay(
													mode_lib->vba.WritebackPixelFormat[j],
													mode_lib->vba.WritebackHRatio[j],
													mode_lib->vba.WritebackVRatio[j],
													mode_lib->vba.WritebackLumaHTaps[j],
													mode_lib->vba.WritebackLumaVTaps[j],
													mode_lib->vba.WritebackChromaHTaps[j],
													mode_lib->vba.WritebackChromaVTaps[j],
													mode_lib->vba.WritebackDestinationWidth[j])
													/ mode_lib->vba.DISPCLK);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k)
		क्रम (j = 0; j < mode_lib->vba.NumberOfActivePlanes; ++j)
			अगर (mode_lib->vba.BlendingAndTiming[k] == j)
				locals->WritebackDelay[mode_lib->vba.VoltageLevel][k] =
						locals->WritebackDelay[mode_lib->vba.VoltageLevel][j];

	mode_lib->vba.VStartupLines = 13;
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		locals->MaxVStartupLines[k] = mode_lib->vba.VTotal[k] - mode_lib->vba.VActive[k] - dml_max(1.0, dml_उच्चमान(locals->WritebackDelay[mode_lib->vba.VoltageLevel][k] / (mode_lib->vba.HTotal[k] / mode_lib->vba.PixelClock[k]), 1));
	पूर्ण

	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k)
		locals->MaximumMaxVStartupLines = dml_max(locals->MaximumMaxVStartupLines, locals->MaxVStartupLines[k]);

	// We करोn't really care to iterate between the various prefetch modes
	//mode_lib->vba.PrefetchERROR = CalculateMinAndMaxPrefetchMode(mode_lib->vba.AllowDRAMSelfRefreshOrDRAMClockChangeInVblank, &mode_lib->vba.MinPrefetchMode, &mode_lib->vba.MaxPrefetchMode);
	mode_lib->vba.UrgentLatency = dml_max3(mode_lib->vba.UrgentLatencyPixelDataOnly, mode_lib->vba.UrgentLatencyPixelMixedWithVMData, mode_lib->vba.UrgentLatencyVMDataOnly);

	करो अणु
		द्विगुन MaxTotalRDBandwidth = 0;
		द्विगुन MaxTotalRDBandwidthNoUrgentBurst = 0;
		bool DestinationLineTimesForPrefetchLessThan2 = false;
		bool VRatioPrefetchMoreThan4 = false;
		द्विगुन TWait = CalculateTWait(
				mode_lib->vba.PrefetchMode[mode_lib->vba.VoltageLevel][mode_lib->vba.maxMpcComb],
				mode_lib->vba.DRAMClockChangeLatency,
				mode_lib->vba.UrgentLatency,
				mode_lib->vba.SREnterPlusExitTime);

		क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
			Pipe   myPipe;
			HostVM myHostVM;

			अगर (mode_lib->vba.XFCEnabled[k] == true) अणु
				mode_lib->vba.XFCRemoteSurfaceFlipDelay =
						CalculateRemoteSurfaceFlipDelay(
								mode_lib,
								mode_lib->vba.VRatio[k],
								locals->SwathWidthY[k],
								dml_उच्चमान(
										locals->BytePerPixelDETY[k],
										1),
								mode_lib->vba.HTotal[k]
										/ mode_lib->vba.PixelClock[k],
								mode_lib->vba.XFCTSlvVupdateOffset,
								mode_lib->vba.XFCTSlvVupdateWidth,
								mode_lib->vba.XFCTSlvVपढ़ोyOffset,
								mode_lib->vba.XFCXBUFLatencyTolerance,
								mode_lib->vba.XFCFillBWOverhead,
								mode_lib->vba.XFCSlvChunkSize,
								mode_lib->vba.XFCBusTransportTime,
								mode_lib->vba.TCalc,
								TWait,
								&mode_lib->vba.SrcActiveDrainRate,
								&mode_lib->vba.TInitXFill,
								&mode_lib->vba.TslvChk);
			पूर्ण अन्यथा अणु
				mode_lib->vba.XFCRemoteSurfaceFlipDelay = 0;
			पूर्ण

			myPipe.DPPCLK = locals->DPPCLK[k];
			myPipe.DISPCLK = mode_lib->vba.DISPCLK;
			myPipe.PixelClock = mode_lib->vba.PixelClock[k];
			myPipe.DCFCLKDeepSleep = mode_lib->vba.DCFCLKDeepSleep;
			myPipe.DPPPerPlane = mode_lib->vba.DPPPerPlane[k];
			myPipe.ScalerEnabled = mode_lib->vba.ScalerEnabled[k];
			myPipe.SourceScan = mode_lib->vba.SourceScan[k];
			myPipe.BlockWidth256BytesY = locals->BlockWidth256BytesY[k];
			myPipe.BlockHeight256BytesY = locals->BlockHeight256BytesY[k];
			myPipe.BlockWidth256BytesC = locals->BlockWidth256BytesC[k];
			myPipe.BlockHeight256BytesC = locals->BlockHeight256BytesC[k];
			myPipe.InterlaceEnable = mode_lib->vba.Interlace[k];
			myPipe.NumberOfCursors = mode_lib->vba.NumberOfCursors[k];
			myPipe.VBlank = mode_lib->vba.VTotal[k] - mode_lib->vba.VActive[k];
			myPipe.HTotal = mode_lib->vba.HTotal[k];


			myHostVM.Enable = mode_lib->vba.HostVMEnable;
			myHostVM.MaxPageTableLevels = mode_lib->vba.HostVMMaxPageTableLevels;
			myHostVM.CachedPageTableLevels = mode_lib->vba.HostVMCachedPageTableLevels;

			mode_lib->vba.ErrorResult[k] =
					CalculatePrefetchSchedule(
							mode_lib,
							mode_lib->vba.PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData,
							mode_lib->vba.PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly,
							&myPipe,
							locals->DSCDelay[k],
							mode_lib->vba.DPPCLKDelaySubtotal,
							mode_lib->vba.DPPCLKDelaySCL,
							mode_lib->vba.DPPCLKDelaySCLLBOnly,
							mode_lib->vba.DPPCLKDelayCNVCFormater,
							mode_lib->vba.DPPCLKDelayCNVCCursor,
							mode_lib->vba.DISPCLKDelaySubtotal,
							(अचिन्हित पूर्णांक) (locals->SwathWidthY[k]
									/ mode_lib->vba.HRatio[k]),
							mode_lib->vba.OutputFormat[k],
							mode_lib->vba.MaxInterDCNTileRepeaters,
							dml_min(mode_lib->vba.VStartupLines, locals->MaxVStartupLines[k]),
							locals->MaxVStartupLines[k],
							mode_lib->vba.GPUVMMaxPageTableLevels,
							mode_lib->vba.GPUVMEnable,
							&myHostVM,
							mode_lib->vba.DynamicMetadataEnable[k],
							mode_lib->vba.DynamicMetadataLinesBeक्रमeActiveRequired[k],
							mode_lib->vba.DynamicMetadataTransmittedBytes[k],
							mode_lib->vba.DCCEnable[k],
							mode_lib->vba.UrgentLatency,
							mode_lib->vba.UrgentExtraLatency,
							mode_lib->vba.TCalc,
							locals->PDEAndMetaPTEBytesFrame[k],
							locals->MetaRowByte[k],
							locals->PixelPTEBytesPerRow[k],
							locals->PrefetchSourceLinesY[k],
							locals->SwathWidthY[k],
							locals->BytePerPixelDETY[k],
							locals->VInitPreFillY[k],
							locals->MaxNumSwathY[k],
							locals->PrefetchSourceLinesC[k],
							locals->BytePerPixelDETC[k],
							locals->VInitPreFillC[k],
							locals->MaxNumSwathC[k],
							mode_lib->vba.SwathHeightY[k],
							mode_lib->vba.SwathHeightC[k],
							TWait,
							mode_lib->vba.XFCEnabled[k],
							mode_lib->vba.XFCRemoteSurfaceFlipDelay,
							mode_lib->vba.ProgressiveToInterlaceUnitInOPP,
							&locals->DSTXAfterScaler[k],
							&locals->DSTYAfterScaler[k],
							&locals->DestinationLinesForPrefetch[k],
							&locals->PrefetchBandwidth[k],
							&locals->DestinationLinesToRequestVMInVBlank[k],
							&locals->DestinationLinesToRequestRowInVBlank[k],
							&locals->VRatioPrefetchY[k],
							&locals->VRatioPrefetchC[k],
							&locals->RequiredPrefetchPixDataBWLuma[k],
							&locals->RequiredPrefetchPixDataBWChroma[k],
							&locals->VStartupRequiredWhenNotEnoughTimeForDynamicMetadata,
							&locals->Tno_bw[k],
							&locals->prefetch_vmrow_bw[k],
							&locals->swath_width_luma_ub[k],
							&locals->swath_width_chroma_ub[k],
							&mode_lib->vba.VUpdateOffsetPix[k],
							&mode_lib->vba.VUpdateWidthPix[k],
							&mode_lib->vba.VReadyOffsetPix[k]);
			अगर (mode_lib->vba.BlendingAndTiming[k] == k) अणु
				locals->VStartup[k] = dml_min(
						mode_lib->vba.VStartupLines,
						locals->MaxVStartupLines[k]);
				अगर (locals->VStartupRequiredWhenNotEnoughTimeForDynamicMetadata
						!= 0) अणु
					locals->VStartup[k] =
							locals->VStartupRequiredWhenNotEnoughTimeForDynamicMetadata;
				पूर्ण
			पूर्ण अन्यथा अणु
				locals->VStartup[k] =
						dml_min(
								mode_lib->vba.VStartupLines,
								locals->MaxVStartupLines[mode_lib->vba.BlendingAndTiming[k]]);
			पूर्ण
		पूर्ण

		क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
			अचिन्हित पूर्णांक m;

			locals->cursor_bw[k] = 0;
			locals->cursor_bw_pre[k] = 0;
			क्रम (m = 0; m < mode_lib->vba.NumberOfCursors[k]; m++) अणु
				locals->cursor_bw[k] += mode_lib->vba.CursorWidth[k][m] * mode_lib->vba.CursorBPP[k][m] / 8.0 / (mode_lib->vba.HTotal[k] / mode_lib->vba.PixelClock[k]) * mode_lib->vba.VRatio[k];
				locals->cursor_bw_pre[k] += mode_lib->vba.CursorWidth[k][m] * mode_lib->vba.CursorBPP[k][m] / 8.0 / (mode_lib->vba.HTotal[k] / mode_lib->vba.PixelClock[k]) * locals->VRatioPrefetchY[k];
			पूर्ण

			CalculateUrgentBurstFactor(
					mode_lib->vba.DETBufferSizeInKByte,
					mode_lib->vba.SwathHeightY[k],
					mode_lib->vba.SwathHeightC[k],
					locals->SwathWidthY[k],
					mode_lib->vba.HTotal[k] /
					mode_lib->vba.PixelClock[k],
					mode_lib->vba.UrgentLatency,
					mode_lib->vba.CursorBufferSize,
					mode_lib->vba.CursorWidth[k][0] + mode_lib->vba.CursorWidth[k][1],
					dml_max(mode_lib->vba.CursorBPP[k][0], mode_lib->vba.CursorBPP[k][1]),
					mode_lib->vba.VRatio[k],
					locals->VRatioPrefetchY[k],
					locals->VRatioPrefetchC[k],
					locals->BytePerPixelDETY[k],
					locals->BytePerPixelDETC[k],
					&locals->UrgentBurstFactorCursor[k],
					&locals->UrgentBurstFactorCursorPre[k],
					&locals->UrgentBurstFactorLuma[k],
					&locals->UrgentBurstFactorLumaPre[k],
					&locals->UrgentBurstFactorChroma[k],
					&locals->UrgentBurstFactorChromaPre[k],
					&locals->NotEnoughUrgentLatencyHiding,
					&locals->NotEnoughUrgentLatencyHidingPre);

			अगर (mode_lib->vba.UseUrgentBurstBandwidth == false) अणु
				locals->UrgentBurstFactorLuma[k] = 1;
				locals->UrgentBurstFactorChroma[k] = 1;
				locals->UrgentBurstFactorCursor[k] = 1;
				locals->UrgentBurstFactorLumaPre[k] = 1;
				locals->UrgentBurstFactorChromaPre[k] = 1;
				locals->UrgentBurstFactorCursorPre[k] = 1;
			पूर्ण

			MaxTotalRDBandwidth = MaxTotalRDBandwidth +
				dml_max3(locals->prefetch_vmrow_bw[k],
					locals->ReadBandwidthPlaneLuma[k] * locals->UrgentBurstFactorLuma[k]
					+ locals->ReadBandwidthPlaneChroma[k] * locals->UrgentBurstFactorChroma[k] + locals->cursor_bw[k]
					* locals->UrgentBurstFactorCursor[k] + locals->meta_row_bw[k] + locals->dpte_row_bw[k],
					locals->RequiredPrefetchPixDataBWLuma[k] * locals->UrgentBurstFactorLumaPre[k] + locals->RequiredPrefetchPixDataBWChroma[k]
					* locals->UrgentBurstFactorChromaPre[k] + locals->cursor_bw_pre[k] * locals->UrgentBurstFactorCursorPre[k]);

			MaxTotalRDBandwidthNoUrgentBurst = MaxTotalRDBandwidthNoUrgentBurst +
				dml_max3(locals->prefetch_vmrow_bw[k],
					locals->ReadBandwidthPlaneLuma[k] + locals->ReadBandwidthPlaneChroma[k] + locals->cursor_bw[k]
					+ locals->meta_row_bw[k] + locals->dpte_row_bw[k],
					locals->RequiredPrefetchPixDataBWLuma[k] + locals->RequiredPrefetchPixDataBWChroma[k] + locals->cursor_bw_pre[k]);

			अगर (locals->DestinationLinesForPrefetch[k] < 2)
				DestinationLineTimesForPrefetchLessThan2 = true;
			अगर (locals->VRatioPrefetchY[k] > 4 || locals->VRatioPrefetchC[k] > 4)
				VRatioPrefetchMoreThan4 = true;
		पूर्ण
		mode_lib->vba.FractionOfUrgentBandwidth = MaxTotalRDBandwidthNoUrgentBurst / mode_lib->vba.ReturnBW;

		अगर (MaxTotalRDBandwidth <= mode_lib->vba.ReturnBW && locals->NotEnoughUrgentLatencyHiding == 0 && locals->NotEnoughUrgentLatencyHidingPre == 0 && !VRatioPrefetchMoreThan4
				&& !DestinationLineTimesForPrefetchLessThan2)
			mode_lib->vba.PrefetchModeSupported = true;
		अन्यथा अणु
			mode_lib->vba.PrefetchModeSupported = false;
			dml_prपूर्णांक(
					"DML: CalculatePrefetchSchedule ***failed***. Bandwidth violation. Results are NOT valid\n");
		पूर्ण

		अगर (mode_lib->vba.PrefetchModeSupported == true) अणु
			mode_lib->vba.BandwidthAvailableForImmediateFlip = mode_lib->vba.ReturnBW;
			क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
				mode_lib->vba.BandwidthAvailableForImmediateFlip =
						mode_lib->vba.BandwidthAvailableForImmediateFlip
							- dml_max(
								locals->ReadBandwidthPlaneLuma[k] * locals->UrgentBurstFactorLuma[k]
								+ locals->ReadBandwidthPlaneChroma[k] * locals->UrgentBurstFactorChroma[k]
								+ locals->cursor_bw[k] * locals->UrgentBurstFactorCursor[k],
								locals->RequiredPrefetchPixDataBWLuma[k] * locals->UrgentBurstFactorLumaPre[k] +
								locals->RequiredPrefetchPixDataBWChroma[k] * locals->UrgentBurstFactorChromaPre[k] +
								locals->cursor_bw_pre[k] * locals->UrgentBurstFactorCursorPre[k]);
			पूर्ण

			mode_lib->vba.TotImmediateFlipBytes = 0;
			क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
				mode_lib->vba.TotImmediateFlipBytes = mode_lib->vba.TotImmediateFlipBytes + locals->PDEAndMetaPTEBytesFrame[k] + locals->MetaRowByte[k] + locals->PixelPTEBytesPerRow[k];
			पूर्ण
			क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
				CalculateFlipSchedule(
						mode_lib,
						mode_lib->vba.PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData,
						mode_lib->vba.PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly,
						mode_lib->vba.UrgentExtraLatency,
						mode_lib->vba.UrgentLatency,
						mode_lib->vba.GPUVMMaxPageTableLevels,
						mode_lib->vba.HostVMEnable,
						mode_lib->vba.HostVMMaxPageTableLevels,
						mode_lib->vba.HostVMCachedPageTableLevels,
						mode_lib->vba.GPUVMEnable,
						locals->PDEAndMetaPTEBytesFrame[k],
						locals->MetaRowByte[k],
						locals->PixelPTEBytesPerRow[k],
						mode_lib->vba.BandwidthAvailableForImmediateFlip,
						mode_lib->vba.TotImmediateFlipBytes,
						mode_lib->vba.SourcePixelFormat[k],
						mode_lib->vba.HTotal[k] / mode_lib->vba.PixelClock[k],
						mode_lib->vba.VRatio[k],
						locals->Tno_bw[k],
						mode_lib->vba.DCCEnable[k],
						locals->dpte_row_height[k],
						locals->meta_row_height[k],
						locals->dpte_row_height_chroma[k],
						locals->meta_row_height_chroma[k],
						&locals->DestinationLinesToRequestVMInImmediateFlip[k],
						&locals->DestinationLinesToRequestRowInImmediateFlip[k],
						&locals->final_flip_bw[k],
						&locals->ImmediateFlipSupportedForPipe[k]);
			पूर्ण
			mode_lib->vba.total_dcn_पढ़ो_bw_with_flip = 0.0;
			mode_lib->vba.total_dcn_पढ़ो_bw_with_flip_no_urgent_burst = 0.0;
			क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
				mode_lib->vba.total_dcn_पढ़ो_bw_with_flip =
						mode_lib->vba.total_dcn_पढ़ो_bw_with_flip + dml_max3(
							locals->prefetch_vmrow_bw[k],
							locals->final_flip_bw[k] + locals->ReadBandwidthLuma[k] * locals->UrgentBurstFactorLuma[k]
							+ locals->ReadBandwidthChroma[k] * locals->UrgentBurstFactorChroma[k] + locals->cursor_bw[k] * locals->UrgentBurstFactorCursor[k],
							locals->final_flip_bw[k] + locals->RequiredPrefetchPixDataBWLuma[k] * locals->UrgentBurstFactorLumaPre[k]
							+ locals->RequiredPrefetchPixDataBWChroma[k] * locals->UrgentBurstFactorChromaPre[k]
							+ locals->cursor_bw_pre[k] * locals->UrgentBurstFactorCursorPre[k]);
				mode_lib->vba.total_dcn_पढ़ो_bw_with_flip_no_urgent_burst =
				mode_lib->vba.total_dcn_पढ़ो_bw_with_flip_no_urgent_burst +
					dml_max3(locals->prefetch_vmrow_bw[k],
						locals->final_flip_bw[k] + locals->ReadBandwidthPlaneLuma[k] + locals->ReadBandwidthPlaneChroma[k] + locals->cursor_bw[k],
						locals->final_flip_bw[k] + locals->RequiredPrefetchPixDataBWLuma[k] + locals->RequiredPrefetchPixDataBWChroma[k] + locals->cursor_bw_pre[k]);

			पूर्ण
			mode_lib->vba.FractionOfUrgentBandwidthImmediateFlip = mode_lib->vba.total_dcn_पढ़ो_bw_with_flip_no_urgent_burst / mode_lib->vba.ReturnBW;

			mode_lib->vba.ImmediateFlipSupported = true;
			अगर (mode_lib->vba.total_dcn_पढ़ो_bw_with_flip > mode_lib->vba.ReturnBW) अणु
				mode_lib->vba.ImmediateFlipSupported = false;
			पूर्ण
			क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
				अगर (locals->ImmediateFlipSupportedForPipe[k] == false) अणु
					mode_lib->vba.ImmediateFlipSupported = false;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			mode_lib->vba.ImmediateFlipSupported = false;
		पूर्ण

		क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
			अगर (mode_lib->vba.ErrorResult[k]) अणु
				mode_lib->vba.PrefetchModeSupported = false;
				dml_prपूर्णांक(
						"DML: CalculatePrefetchSchedule ***failed***. Prefetch schedule violation. Results are NOT valid\n");
			पूर्ण
		पूर्ण

		mode_lib->vba.VStartupLines = mode_lib->vba.VStartupLines + 1;
	पूर्ण जबतक (!((mode_lib->vba.PrefetchModeSupported
			&& ((!mode_lib->vba.ImmediateFlipSupport && !mode_lib->vba.HostVMEnable)
					|| mode_lib->vba.ImmediateFlipSupported))
			|| locals->MaximumMaxVStartupLines < mode_lib->vba.VStartupLines));

	//Watermarks and NB P-State/DRAM Clock Change Support
	अणु
		क्रमागत घड़ी_change_support DRAMClockChangeSupport; // dummy
		CalculateWatermarksAndDRAMSpeedChangeSupport(
				mode_lib,
				mode_lib->vba.PrefetchMode[mode_lib->vba.VoltageLevel][mode_lib->vba.maxMpcComb],
				mode_lib->vba.NumberOfActivePlanes,
				mode_lib->vba.MaxLineBufferLines,
				mode_lib->vba.LineBufferSize,
				mode_lib->vba.DPPOutputBufferPixels,
				mode_lib->vba.DETBufferSizeInKByte,
				mode_lib->vba.WritebackInterfaceLumaBufferSize,
				mode_lib->vba.WritebackInterfaceChromaBufferSize,
				mode_lib->vba.DCFCLK,
				mode_lib->vba.UrgentOutOfOrderReturnPerChannel * mode_lib->vba.NumberOfChannels,
				mode_lib->vba.ReturnBW,
				mode_lib->vba.GPUVMEnable,
				locals->dpte_group_bytes,
				mode_lib->vba.MetaChunkSize,
				mode_lib->vba.UrgentLatency,
				mode_lib->vba.UrgentExtraLatency,
				mode_lib->vba.WritebackLatency,
				mode_lib->vba.WritebackChunkSize,
				mode_lib->vba.SOCCLK,
				mode_lib->vba.DRAMClockChangeLatency,
				mode_lib->vba.SRExitTime,
				mode_lib->vba.SREnterPlusExitTime,
				mode_lib->vba.DCFCLKDeepSleep,
				mode_lib->vba.DPPPerPlane,
				mode_lib->vba.DCCEnable,
				locals->DPPCLK,
				locals->SwathWidthSingleDPPY,
				mode_lib->vba.SwathHeightY,
				locals->ReadBandwidthPlaneLuma,
				mode_lib->vba.SwathHeightC,
				locals->ReadBandwidthPlaneChroma,
				mode_lib->vba.LBBitPerPixel,
				locals->SwathWidthY,
				mode_lib->vba.HRatio,
				mode_lib->vba.vtaps,
				mode_lib->vba.VTAPsChroma,
				mode_lib->vba.VRatio,
				mode_lib->vba.HTotal,
				mode_lib->vba.PixelClock,
				mode_lib->vba.BlendingAndTiming,
				locals->BytePerPixelDETY,
				locals->BytePerPixelDETC,
				mode_lib->vba.WritebackEnable,
				mode_lib->vba.WritebackPixelFormat,
				mode_lib->vba.WritebackDestinationWidth,
				mode_lib->vba.WritebackDestinationHeight,
				mode_lib->vba.WritebackSourceHeight,
				&DRAMClockChangeSupport,
				&mode_lib->vba.UrgentWatermark,
				&mode_lib->vba.WritebackUrgentWatermark,
				&mode_lib->vba.DRAMClockChangeWatermark,
				&mode_lib->vba.WritebackDRAMClockChangeWatermark,
				&mode_lib->vba.StutterExitWatermark,
				&mode_lib->vba.StutterEnterPlusExitWatermark,
				&mode_lib->vba.MinActiveDRAMClockChangeLatencySupported);
	पूर्ण


	//Display Pipeline Delivery Time in Prefetch, Groups
	CalculatePixelDeliveryTimes(
		mode_lib->vba.NumberOfActivePlanes,
		mode_lib->vba.VRatio,
		locals->VRatioPrefetchY,
		locals->VRatioPrefetchC,
		locals->swath_width_luma_ub,
		locals->swath_width_chroma_ub,
		mode_lib->vba.DPPPerPlane,
		mode_lib->vba.HRatio,
		mode_lib->vba.PixelClock,
		locals->PSCL_THROUGHPUT_LUMA,
		locals->PSCL_THROUGHPUT_CHROMA,
		locals->DPPCLK,
		locals->BytePerPixelDETC,
		mode_lib->vba.SourceScan,
		locals->BlockWidth256BytesY,
		locals->BlockHeight256BytesY,
		locals->BlockWidth256BytesC,
		locals->BlockHeight256BytesC,
		locals->DisplayPipeLineDeliveryTimeLuma,
		locals->DisplayPipeLineDeliveryTimeChroma,
		locals->DisplayPipeLineDeliveryTimeLumaPrefetch,
		locals->DisplayPipeLineDeliveryTimeChromaPrefetch,
		locals->DisplayPipeRequestDeliveryTimeLuma,
		locals->DisplayPipeRequestDeliveryTimeChroma,
		locals->DisplayPipeRequestDeliveryTimeLumaPrefetch,
		locals->DisplayPipeRequestDeliveryTimeChromaPrefetch);

	CalculateMetaAndPTETimes(
		mode_lib->vba.NumberOfActivePlanes,
		mode_lib->vba.GPUVMEnable,
		mode_lib->vba.MetaChunkSize,
		mode_lib->vba.MinMetaChunkSizeBytes,
		mode_lib->vba.GPUVMMaxPageTableLevels,
		mode_lib->vba.HTotal,
		mode_lib->vba.VRatio,
		locals->VRatioPrefetchY,
		locals->VRatioPrefetchC,
		locals->DestinationLinesToRequestRowInVBlank,
		locals->DestinationLinesToRequestRowInImmediateFlip,
		locals->DestinationLinesToRequestVMInVBlank,
		locals->DestinationLinesToRequestVMInImmediateFlip,
		mode_lib->vba.DCCEnable,
		mode_lib->vba.PixelClock,
		locals->BytePerPixelDETY,
		locals->BytePerPixelDETC,
		mode_lib->vba.SourceScan,
		locals->dpte_row_height,
		locals->dpte_row_height_chroma,
		locals->meta_row_width,
		locals->meta_row_height,
		locals->meta_req_width,
		locals->meta_req_height,
		locals->dpte_group_bytes,
		locals->PTERequestSizeY,
		locals->PTERequestSizeC,
		locals->PixelPTEReqWidthY,
		locals->PixelPTEReqHeightY,
		locals->PixelPTEReqWidthC,
		locals->PixelPTEReqHeightC,
		locals->dpte_row_width_luma_ub,
		locals->dpte_row_width_chroma_ub,
		locals->vm_group_bytes,
		locals->dpde0_bytes_per_frame_ub_l,
		locals->dpde0_bytes_per_frame_ub_c,
		locals->meta_pte_bytes_per_frame_ub_l,
		locals->meta_pte_bytes_per_frame_ub_c,
		locals->DST_Y_PER_PTE_ROW_NOM_L,
		locals->DST_Y_PER_PTE_ROW_NOM_C,
		locals->DST_Y_PER_META_ROW_NOM_L,
		locals->TimePerMetaChunkNominal,
		locals->TimePerMetaChunkVBlank,
		locals->TimePerMetaChunkFlip,
		locals->समय_per_pte_group_nom_luma,
		locals->समय_per_pte_group_vblank_luma,
		locals->समय_per_pte_group_flip_luma,
		locals->समय_per_pte_group_nom_chroma,
		locals->समय_per_pte_group_vblank_chroma,
		locals->समय_per_pte_group_flip_chroma,
		locals->TimePerVMGroupVBlank,
		locals->TimePerVMGroupFlip,
		locals->TimePerVMRequestVBlank,
		locals->TimePerVMRequestFlip);


	// Min TTUVBlank
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		अगर (mode_lib->vba.PrefetchMode[mode_lib->vba.VoltageLevel][mode_lib->vba.maxMpcComb] == 0) अणु
			locals->AllowDRAMClockChangeDuringVBlank[k] = true;
			locals->AllowDRAMSelfRefreshDuringVBlank[k] = true;
			locals->MinTTUVBlank[k] = dml_max(
					mode_lib->vba.DRAMClockChangeWatermark,
					dml_max(
							mode_lib->vba.StutterEnterPlusExitWatermark,
							mode_lib->vba.UrgentWatermark));
		पूर्ण अन्यथा अगर (mode_lib->vba.PrefetchMode[mode_lib->vba.VoltageLevel][mode_lib->vba.maxMpcComb] == 1) अणु
			locals->AllowDRAMClockChangeDuringVBlank[k] = false;
			locals->AllowDRAMSelfRefreshDuringVBlank[k] = true;
			locals->MinTTUVBlank[k] = dml_max(
					mode_lib->vba.StutterEnterPlusExitWatermark,
					mode_lib->vba.UrgentWatermark);
		पूर्ण अन्यथा अणु
			locals->AllowDRAMClockChangeDuringVBlank[k] = false;
			locals->AllowDRAMSelfRefreshDuringVBlank[k] = false;
			locals->MinTTUVBlank[k] = mode_lib->vba.UrgentWatermark;
		पूर्ण
		अगर (!mode_lib->vba.DynamicMetadataEnable[k])
			locals->MinTTUVBlank[k] = mode_lib->vba.TCalc
					+ locals->MinTTUVBlank[k];
	पूर्ण

	// DCC Configuration
	mode_lib->vba.ActiveDPPs = 0;
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		locals->MaximumDCCCompressionYSurface[k] = CalculateDCCConfiguration(
			mode_lib->vba.DCCEnable[k],
			false, // We should always know the direction DCCProgrammingAssumesScanDirectionUnknown,
			mode_lib->vba.ViewportWidth[k],
			mode_lib->vba.ViewportHeight[k],
			mode_lib->vba.DETBufferSizeInKByte * 1024,
			locals->BlockHeight256BytesY[k],
			mode_lib->vba.SwathHeightY[k],
			mode_lib->vba.SurfaceTiling[k],
			locals->BytePerPixelDETY[k],
			mode_lib->vba.SourceScan[k],
			&locals->DCCYMaxUncompressedBlock[k],
			&locals->DCCYMaxCompressedBlock[k],
			&locals->DCCYIndependent64ByteBlock[k]);
	पूर्ण

	//XFC Parameters:
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		अगर (mode_lib->vba.XFCEnabled[k] == true) अणु
			द्विगुन TWait;

			locals->XFCSlaveVUpdateOffset[k] = mode_lib->vba.XFCTSlvVupdateOffset;
			locals->XFCSlaveVupdateWidth[k] = mode_lib->vba.XFCTSlvVupdateWidth;
			locals->XFCSlaveVReadyOffset[k] = mode_lib->vba.XFCTSlvVपढ़ोyOffset;
			TWait = CalculateTWait(
					mode_lib->vba.PrefetchMode[mode_lib->vba.VoltageLevel][mode_lib->vba.maxMpcComb],
					mode_lib->vba.DRAMClockChangeLatency,
					mode_lib->vba.UrgentLatency,
					mode_lib->vba.SREnterPlusExitTime);
			mode_lib->vba.XFCRemoteSurfaceFlipDelay = CalculateRemoteSurfaceFlipDelay(
					mode_lib,
					mode_lib->vba.VRatio[k],
					locals->SwathWidthY[k],
					dml_उच्चमान(locals->BytePerPixelDETY[k], 1),
					mode_lib->vba.HTotal[k] / mode_lib->vba.PixelClock[k],
					mode_lib->vba.XFCTSlvVupdateOffset,
					mode_lib->vba.XFCTSlvVupdateWidth,
					mode_lib->vba.XFCTSlvVपढ़ोyOffset,
					mode_lib->vba.XFCXBUFLatencyTolerance,
					mode_lib->vba.XFCFillBWOverhead,
					mode_lib->vba.XFCSlvChunkSize,
					mode_lib->vba.XFCBusTransportTime,
					mode_lib->vba.TCalc,
					TWait,
					&mode_lib->vba.SrcActiveDrainRate,
					&mode_lib->vba.TInitXFill,
					&mode_lib->vba.TslvChk);
					locals->XFCRemoteSurfaceFlipLatency[k] =
					dml_न्यूनमान(
							mode_lib->vba.XFCRemoteSurfaceFlipDelay
									/ (mode_lib->vba.HTotal[k]
											/ mode_lib->vba.PixelClock[k]),
							1);
			locals->XFCTransferDelay[k] =
					dml_उच्चमान(
							mode_lib->vba.XFCBusTransportTime
									/ (mode_lib->vba.HTotal[k]
											/ mode_lib->vba.PixelClock[k]),
							1);
			locals->XFCPreअक्षरgeDelay[k] =
					dml_उच्चमान(
							(mode_lib->vba.XFCBusTransportTime
									+ mode_lib->vba.TInitXFill
									+ mode_lib->vba.TslvChk)
									/ (mode_lib->vba.HTotal[k]
											/ mode_lib->vba.PixelClock[k]),
							1);
			mode_lib->vba.InitFillLevel = mode_lib->vba.XFCXBUFLatencyTolerance
					* mode_lib->vba.SrcActiveDrainRate;
			mode_lib->vba.FinalFillMargin =
					(locals->DestinationLinesToRequestVMInVBlank[k]
							+ locals->DestinationLinesToRequestRowInVBlank[k])
							* mode_lib->vba.HTotal[k]
							/ mode_lib->vba.PixelClock[k]
							* mode_lib->vba.SrcActiveDrainRate
							+ mode_lib->vba.XFCFillConstant;
			mode_lib->vba.FinalFillLevel = mode_lib->vba.XFCRemoteSurfaceFlipDelay
					* mode_lib->vba.SrcActiveDrainRate
					+ mode_lib->vba.FinalFillMargin;
			mode_lib->vba.Reमुख्यingFillLevel = dml_max(
					0.0,
					mode_lib->vba.FinalFillLevel - mode_lib->vba.InitFillLevel);
			mode_lib->vba.TFinalxFill = mode_lib->vba.Reमुख्यingFillLevel
					/ (mode_lib->vba.SrcActiveDrainRate
							* mode_lib->vba.XFCFillBWOverhead / 100);
			locals->XFCPrefetchMargin[k] =
					mode_lib->vba.XFCRemoteSurfaceFlipDelay
							+ mode_lib->vba.TFinalxFill
							+ (locals->DestinationLinesToRequestVMInVBlank[k]
									+ locals->DestinationLinesToRequestRowInVBlank[k])
									* mode_lib->vba.HTotal[k]
									/ mode_lib->vba.PixelClock[k];
		पूर्ण अन्यथा अणु
			locals->XFCSlaveVUpdateOffset[k] = 0;
			locals->XFCSlaveVupdateWidth[k] = 0;
			locals->XFCSlaveVReadyOffset[k] = 0;
			locals->XFCRemoteSurfaceFlipLatency[k] = 0;
			locals->XFCPreअक्षरgeDelay[k] = 0;
			locals->XFCTransferDelay[k] = 0;
			locals->XFCPrefetchMargin[k] = 0;
		पूर्ण
	पूर्ण

	// Stutter Efficiency
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		CalculateDETBufferSize(
			mode_lib->vba.DETBufferSizeInKByte,
			mode_lib->vba.SwathHeightY[k],
			mode_lib->vba.SwathHeightC[k],
			&locals->DETBufferSizeY[k],
			&locals->DETBufferSizeC[k]);

		locals->LinesInDETY[k] = locals->DETBufferSizeY[k]
				/ locals->BytePerPixelDETY[k] / locals->SwathWidthY[k];
		locals->LinesInDETYRoundedDownToSwath[k] = dml_न्यूनमान(
				locals->LinesInDETY[k],
				mode_lib->vba.SwathHeightY[k]);
		locals->FullDETBufferingTimeY[k] =
				locals->LinesInDETYRoundedDownToSwath[k]
						* (mode_lib->vba.HTotal[k]
								/ mode_lib->vba.PixelClock[k])
						/ mode_lib->vba.VRatio[k];
	पूर्ण

	mode_lib->vba.StutterPeriod = 999999.0;
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		अगर (locals->FullDETBufferingTimeY[k] < mode_lib->vba.StutterPeriod) अणु
			mode_lib->vba.StutterPeriod = locals->FullDETBufferingTimeY[k];
			mode_lib->vba.FrameTimeForMinFullDETBufferingTime =
				(द्विगुन) mode_lib->vba.VTotal[k] * mode_lib->vba.HTotal[k]
				/ mode_lib->vba.PixelClock[k];
			locals->BytePerPixelYCriticalPlane = dml_उच्चमान(locals->BytePerPixelDETY[k], 1);
			locals->SwathWidthYCriticalPlane = locals->SwathWidthY[k];
			locals->LinesToFinishSwathTransferStutterCriticalPlane =
				mode_lib->vba.SwathHeightY[k] - (locals->LinesInDETY[k] - locals->LinesInDETYRoundedDownToSwath[k]);
		पूर्ण
	पूर्ण

	mode_lib->vba.AverageReadBandwidth = 0.0;
	mode_lib->vba.TotalRowReadBandwidth = 0.0;
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		अचिन्हित पूर्णांक DCCRateLimit;

		अगर (mode_lib->vba.DCCEnable[k]) अणु
			अगर (locals->DCCYMaxCompressedBlock[k] == 256)
				DCCRateLimit = 4;
			अन्यथा
				DCCRateLimit = 2;

			mode_lib->vba.AverageReadBandwidth =
					mode_lib->vba.AverageReadBandwidth
							+ (locals->ReadBandwidthPlaneLuma[k] + locals->ReadBandwidthPlaneChroma[k]) /
								dml_min(mode_lib->vba.DCCRate[k], DCCRateLimit);
		पूर्ण अन्यथा अणु
			mode_lib->vba.AverageReadBandwidth =
					mode_lib->vba.AverageReadBandwidth
							+ locals->ReadBandwidthPlaneLuma[k]
							+ locals->ReadBandwidthPlaneChroma[k];
		पूर्ण
		mode_lib->vba.TotalRowReadBandwidth = mode_lib->vba.TotalRowReadBandwidth +
		locals->meta_row_bw[k] + locals->dpte_row_bw[k];
	पूर्ण

	mode_lib->vba.AverageDCCCompressionRate = mode_lib->vba.TotalDataReadBandwidth / mode_lib->vba.AverageReadBandwidth;

	mode_lib->vba.PartOfBurstThatFitsInROB =
			dml_min(
					mode_lib->vba.StutterPeriod
							* mode_lib->vba.TotalDataReadBandwidth,
					mode_lib->vba.ROBBufferSizeInKByte * 1024
							* mode_lib->vba.AverageDCCCompressionRate);
	mode_lib->vba.StutterBurstTime = mode_lib->vba.PartOfBurstThatFitsInROB
			/ mode_lib->vba.AverageDCCCompressionRate / mode_lib->vba.ReturnBW
			+ (mode_lib->vba.StutterPeriod * mode_lib->vba.TotalDataReadBandwidth
					- mode_lib->vba.PartOfBurstThatFitsInROB)
					/ (mode_lib->vba.DCFCLK * 64)
					+ mode_lib->vba.StutterPeriod * mode_lib->vba.TotalRowReadBandwidth / mode_lib->vba.ReturnBW;
	mode_lib->vba.StutterBurstTime = dml_max(
		mode_lib->vba.StutterBurstTime,
		(locals->LinesToFinishSwathTransferStutterCriticalPlane * locals->BytePerPixelYCriticalPlane *
		locals->SwathWidthYCriticalPlane / mode_lib->vba.ReturnBW)
	);

	mode_lib->vba.TotalActiveWriteback = 0;
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		अगर (mode_lib->vba.WritebackEnable[k] == true) अणु
			mode_lib->vba.TotalActiveWriteback = mode_lib->vba.TotalActiveWriteback + 1;
		पूर्ण
	पूर्ण

	अगर (mode_lib->vba.TotalActiveWriteback == 0) अणु
		mode_lib->vba.StutterEfficiencyNotIncludingVBlank = (1
				- (mode_lib->vba.SRExitTime + mode_lib->vba.StutterBurstTime)
						/ mode_lib->vba.StutterPeriod) * 100;
	पूर्ण अन्यथा अणु
		mode_lib->vba.StutterEfficiencyNotIncludingVBlank = 0;
	पूर्ण

	mode_lib->vba.SmallestVBlank = 999999;
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		अगर (mode_lib->vba.SynchronizedVBlank || mode_lib->vba.NumberOfActivePlanes == 1) अणु
			mode_lib->vba.VBlankTime = (द्विगुन) (mode_lib->vba.VTotal[k]
					- mode_lib->vba.VActive[k]) * mode_lib->vba.HTotal[k]
					/ mode_lib->vba.PixelClock[k];
		पूर्ण अन्यथा अणु
			mode_lib->vba.VBlankTime = 0;
		पूर्ण
		mode_lib->vba.SmallestVBlank = dml_min(
				mode_lib->vba.SmallestVBlank,
				mode_lib->vba.VBlankTime);
	पूर्ण

	mode_lib->vba.StutterEfficiency = (mode_lib->vba.StutterEfficiencyNotIncludingVBlank / 100
			* (mode_lib->vba.FrameTimeForMinFullDETBufferingTime
					- mode_lib->vba.SmallestVBlank)
			+ mode_lib->vba.SmallestVBlank)
			/ mode_lib->vba.FrameTimeForMinFullDETBufferingTime * 100;
पूर्ण

अटल व्योम DisplayPipeConfiguration(काष्ठा display_mode_lib *mode_lib)
अणु
	// Display Pipe Configuration
	द्विगुन BytePerPixDETY;
	द्विगुन BytePerPixDETC;
	द्विगुन Read256BytesBlockHeightY;
	द्विगुन Read256BytesBlockHeightC;
	द्विगुन Read256BytesBlockWidthY;
	द्विगुन Read256BytesBlockWidthC;
	द्विगुन MaximumSwathHeightY;
	द्विगुन MaximumSwathHeightC;
	द्विगुन MinimumSwathHeightY;
	द्विगुन MinimumSwathHeightC;
	द्विगुन SwathWidth;
	द्विगुन SwathWidthGranularityY;
	द्विगुन SwathWidthGranularityC;
	द्विगुन RoundedUpMaxSwathSizeBytesY;
	द्विगुन RoundedUpMaxSwathSizeBytesC;
	अचिन्हित पूर्णांक j, k;

	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		bool MainPlaneDoesODMCombine = false;

		अगर (mode_lib->vba.SourcePixelFormat[k] == dm_444_64) अणु
			BytePerPixDETY = 8;
			BytePerPixDETC = 0;
		पूर्ण अन्यथा अगर (mode_lib->vba.SourcePixelFormat[k] == dm_444_32) अणु
			BytePerPixDETY = 4;
			BytePerPixDETC = 0;
		पूर्ण अन्यथा अगर (mode_lib->vba.SourcePixelFormat[k] == dm_444_16) अणु
			BytePerPixDETY = 2;
			BytePerPixDETC = 0;
		पूर्ण अन्यथा अगर (mode_lib->vba.SourcePixelFormat[k] == dm_444_8) अणु
			BytePerPixDETY = 1;
			BytePerPixDETC = 0;
		पूर्ण अन्यथा अगर (mode_lib->vba.SourcePixelFormat[k] == dm_420_8) अणु
			BytePerPixDETY = 1;
			BytePerPixDETC = 2;
		पूर्ण अन्यथा अणु
			BytePerPixDETY = 4.0 / 3.0;
			BytePerPixDETC = 8.0 / 3.0;
		पूर्ण

		अगर ((mode_lib->vba.SourcePixelFormat[k] == dm_444_64
				|| mode_lib->vba.SourcePixelFormat[k] == dm_444_32
				|| mode_lib->vba.SourcePixelFormat[k] == dm_444_16
				|| mode_lib->vba.SourcePixelFormat[k] == dm_444_8)) अणु
			अगर (mode_lib->vba.SurfaceTiling[k] == dm_sw_linear) अणु
				Read256BytesBlockHeightY = 1;
			पूर्ण अन्यथा अगर (mode_lib->vba.SourcePixelFormat[k] == dm_444_64) अणु
				Read256BytesBlockHeightY = 4;
			पूर्ण अन्यथा अगर (mode_lib->vba.SourcePixelFormat[k] == dm_444_32
					|| mode_lib->vba.SourcePixelFormat[k] == dm_444_16) अणु
				Read256BytesBlockHeightY = 8;
			पूर्ण अन्यथा अणु
				Read256BytesBlockHeightY = 16;
			पूर्ण
			Read256BytesBlockWidthY = 256 / dml_उच्चमान(BytePerPixDETY, 1)
					/ Read256BytesBlockHeightY;
			Read256BytesBlockHeightC = 0;
			Read256BytesBlockWidthC = 0;
		पूर्ण अन्यथा अणु
			अगर (mode_lib->vba.SurfaceTiling[k] == dm_sw_linear) अणु
				Read256BytesBlockHeightY = 1;
				Read256BytesBlockHeightC = 1;
			पूर्ण अन्यथा अगर (mode_lib->vba.SourcePixelFormat[k] == dm_420_8) अणु
				Read256BytesBlockHeightY = 16;
				Read256BytesBlockHeightC = 8;
			पूर्ण अन्यथा अणु
				Read256BytesBlockHeightY = 8;
				Read256BytesBlockHeightC = 8;
			पूर्ण
			Read256BytesBlockWidthY = 256 / dml_उच्चमान(BytePerPixDETY, 1)
					/ Read256BytesBlockHeightY;
			Read256BytesBlockWidthC = 256 / dml_उच्चमान(BytePerPixDETC, 2)
					/ Read256BytesBlockHeightC;
		पूर्ण

		अगर (mode_lib->vba.SourceScan[k] == dm_horz) अणु
			MaximumSwathHeightY = Read256BytesBlockHeightY;
			MaximumSwathHeightC = Read256BytesBlockHeightC;
		पूर्ण अन्यथा अणु
			MaximumSwathHeightY = Read256BytesBlockWidthY;
			MaximumSwathHeightC = Read256BytesBlockWidthC;
		पूर्ण

		अगर ((mode_lib->vba.SourcePixelFormat[k] == dm_444_64
				|| mode_lib->vba.SourcePixelFormat[k] == dm_444_32
				|| mode_lib->vba.SourcePixelFormat[k] == dm_444_16
				|| mode_lib->vba.SourcePixelFormat[k] == dm_444_8)) अणु
			अगर (mode_lib->vba.SurfaceTiling[k] == dm_sw_linear
					|| (mode_lib->vba.SourcePixelFormat[k] == dm_444_64
							&& (mode_lib->vba.SurfaceTiling[k]
									== dm_sw_4kb_s
									|| mode_lib->vba.SurfaceTiling[k]
											== dm_sw_4kb_s_x
									|| mode_lib->vba.SurfaceTiling[k]
											== dm_sw_64kb_s
									|| mode_lib->vba.SurfaceTiling[k]
											== dm_sw_64kb_s_t
									|| mode_lib->vba.SurfaceTiling[k]
											== dm_sw_64kb_s_x
									|| mode_lib->vba.SurfaceTiling[k]
											== dm_sw_var_s
									|| mode_lib->vba.SurfaceTiling[k]
											== dm_sw_var_s_x)
							&& mode_lib->vba.SourceScan[k] == dm_horz)) अणु
				MinimumSwathHeightY = MaximumSwathHeightY;
			पूर्ण अन्यथा अगर (mode_lib->vba.SourcePixelFormat[k] == dm_444_8
					&& mode_lib->vba.SourceScan[k] != dm_horz) अणु
				MinimumSwathHeightY = MaximumSwathHeightY;
			पूर्ण अन्यथा अणु
				MinimumSwathHeightY = MaximumSwathHeightY / 2.0;
			पूर्ण
			MinimumSwathHeightC = MaximumSwathHeightC;
		पूर्ण अन्यथा अणु
			अगर (mode_lib->vba.SurfaceTiling[k] == dm_sw_linear) अणु
				MinimumSwathHeightY = MaximumSwathHeightY;
				MinimumSwathHeightC = MaximumSwathHeightC;
			पूर्ण अन्यथा अगर (mode_lib->vba.SourcePixelFormat[k] == dm_420_8
					&& mode_lib->vba.SourceScan[k] == dm_horz) अणु
				MinimumSwathHeightY = MaximumSwathHeightY / 2.0;
				MinimumSwathHeightC = MaximumSwathHeightC;
			पूर्ण अन्यथा अगर (mode_lib->vba.SourcePixelFormat[k] == dm_420_10
					&& mode_lib->vba.SourceScan[k] == dm_horz) अणु
				MinimumSwathHeightC = MaximumSwathHeightC / 2.0;
				MinimumSwathHeightY = MaximumSwathHeightY;
			पूर्ण अन्यथा अणु
				MinimumSwathHeightY = MaximumSwathHeightY;
				MinimumSwathHeightC = MaximumSwathHeightC;
			पूर्ण
		पूर्ण

		अगर (mode_lib->vba.SourceScan[k] == dm_horz) अणु
			SwathWidth = mode_lib->vba.ViewportWidth[k];
		पूर्ण अन्यथा अणु
			SwathWidth = mode_lib->vba.ViewportHeight[k];
		पूर्ण

		अगर (mode_lib->vba.ODMCombineEnabled[k] == dm_odm_combine_mode_2to1) अणु
			MainPlaneDoesODMCombine = true;
		पूर्ण
		क्रम (j = 0; j < mode_lib->vba.NumberOfActivePlanes; ++j) अणु
			अगर (mode_lib->vba.BlendingAndTiming[k] == j
					&& mode_lib->vba.ODMCombineEnabled[k] == dm_odm_combine_mode_2to1) अणु
				MainPlaneDoesODMCombine = true;
			पूर्ण
		पूर्ण

		अगर (MainPlaneDoesODMCombine == true) अणु
			SwathWidth = dml_min(
					SwathWidth,
					mode_lib->vba.HActive[k] / 2.0 * mode_lib->vba.HRatio[k]);
		पूर्ण अन्यथा अणु
			SwathWidth = SwathWidth / mode_lib->vba.DPPPerPlane[k];
		पूर्ण

		SwathWidthGranularityY = 256 / dml_उच्चमान(BytePerPixDETY, 1) / MaximumSwathHeightY;
		RoundedUpMaxSwathSizeBytesY = (dml_उच्चमान(
				(द्विगुन) (SwathWidth - 1),
				SwathWidthGranularityY) + SwathWidthGranularityY) * BytePerPixDETY
				* MaximumSwathHeightY;
		अगर (mode_lib->vba.SourcePixelFormat[k] == dm_420_10) अणु
			RoundedUpMaxSwathSizeBytesY = dml_उच्चमान(RoundedUpMaxSwathSizeBytesY, 256)
					+ 256;
		पूर्ण
		अगर (MaximumSwathHeightC > 0) अणु
			SwathWidthGranularityC = 256.0 / dml_उच्चमान(BytePerPixDETC, 2)
					/ MaximumSwathHeightC;
			RoundedUpMaxSwathSizeBytesC = (dml_उच्चमान(
					(द्विगुन) (SwathWidth / 2.0 - 1),
					SwathWidthGranularityC) + SwathWidthGranularityC)
					* BytePerPixDETC * MaximumSwathHeightC;
			अगर (mode_lib->vba.SourcePixelFormat[k] == dm_420_10) अणु
				RoundedUpMaxSwathSizeBytesC = dml_उच्चमान(
						RoundedUpMaxSwathSizeBytesC,
						256) + 256;
			पूर्ण
		पूर्ण अन्यथा
			RoundedUpMaxSwathSizeBytesC = 0.0;

		अगर (RoundedUpMaxSwathSizeBytesY + RoundedUpMaxSwathSizeBytesC
				<= mode_lib->vba.DETBufferSizeInKByte * 1024.0 / 2.0) अणु
			mode_lib->vba.SwathHeightY[k] = MaximumSwathHeightY;
			mode_lib->vba.SwathHeightC[k] = MaximumSwathHeightC;
		पूर्ण अन्यथा अणु
			mode_lib->vba.SwathHeightY[k] = MinimumSwathHeightY;
			mode_lib->vba.SwathHeightC[k] = MinimumSwathHeightC;
		पूर्ण

		CalculateDETBufferSize(
				mode_lib->vba.DETBufferSizeInKByte,
				mode_lib->vba.SwathHeightY[k],
				mode_lib->vba.SwathHeightC[k],
				&mode_lib->vba.DETBufferSizeY[k],
				&mode_lib->vba.DETBufferSizeC[k]);
	पूर्ण
पूर्ण

अटल द्विगुन CalculateTWait(
		अचिन्हित पूर्णांक PrefetchMode,
		द्विगुन DRAMClockChangeLatency,
		द्विगुन UrgentLatency,
		द्विगुन SREnterPlusExitTime)
अणु
	अगर (PrefetchMode == 0) अणु
		वापस dml_max(
				DRAMClockChangeLatency + UrgentLatency,
				dml_max(SREnterPlusExitTime, UrgentLatency));
	पूर्ण अन्यथा अगर (PrefetchMode == 1) अणु
		वापस dml_max(SREnterPlusExitTime, UrgentLatency);
	पूर्ण अन्यथा अणु
		वापस UrgentLatency;
	पूर्ण
पूर्ण

अटल द्विगुन CalculateRemoteSurfaceFlipDelay(
		काष्ठा display_mode_lib *mode_lib,
		द्विगुन VRatio,
		द्विगुन SwathWidth,
		द्विगुन Bpp,
		द्विगुन LineTime,
		द्विगुन XFCTSlvVupdateOffset,
		द्विगुन XFCTSlvVupdateWidth,
		द्विगुन XFCTSlvVपढ़ोyOffset,
		द्विगुन XFCXBUFLatencyTolerance,
		द्विगुन XFCFillBWOverhead,
		द्विगुन XFCSlvChunkSize,
		द्विगुन XFCBusTransportTime,
		द्विगुन TCalc,
		द्विगुन TWait,
		द्विगुन *SrcActiveDrainRate,
		द्विगुन *TInitXFill,
		द्विगुन *TslvChk)
अणु
	द्विगुन TSlvSetup, AvgfillRate, result;

	*SrcActiveDrainRate = VRatio * SwathWidth * Bpp / LineTime;
	TSlvSetup = XFCTSlvVupdateOffset + XFCTSlvVupdateWidth + XFCTSlvVपढ़ोyOffset;
	*TInitXFill = XFCXBUFLatencyTolerance / (1 + XFCFillBWOverhead / 100);
	AvgfillRate = *SrcActiveDrainRate * (1 + XFCFillBWOverhead / 100);
	*TslvChk = XFCSlvChunkSize / AvgfillRate;
	dml_prपूर्णांक(
			"DML::CalculateRemoteSurfaceFlipDelay: SrcActiveDrainRate: %f\n",
			*SrcActiveDrainRate);
	dml_prपूर्णांक("DML::CalculateRemoteSurfaceFlipDelay: TSlvSetup: %f\n", TSlvSetup);
	dml_prपूर्णांक("DML::CalculateRemoteSurfaceFlipDelay: TInitXFill: %f\n", *TInitXFill);
	dml_prपूर्णांक("DML::CalculateRemoteSurfaceFlipDelay: AvgfillRate: %f\n", AvgfillRate);
	dml_prपूर्णांक("DML::CalculateRemoteSurfaceFlipDelay: TslvChk: %f\n", *TslvChk);
	result = 2 * XFCBusTransportTime + TSlvSetup + TCalc + TWait + *TslvChk + *TInitXFill; // TODO: This करोesn't seem to match programming guide
	dml_prपूर्णांक("DML::CalculateRemoteSurfaceFlipDelay: RemoteSurfaceFlipDelay: %f\n", result);
	वापस result;
पूर्ण

अटल द्विगुन CalculateWriteBackDelay(
		क्रमागत source_क्रमmat_class WritebackPixelFormat,
		द्विगुन WritebackHRatio,
		द्विगुन WritebackVRatio,
		अचिन्हित पूर्णांक WritebackLumaHTaps,
		अचिन्हित पूर्णांक WritebackLumaVTaps,
		अचिन्हित पूर्णांक WritebackChromaHTaps,
		अचिन्हित पूर्णांक WritebackChromaVTaps,
		अचिन्हित पूर्णांक WritebackDestinationWidth)
अणु
	द्विगुन CalculateWriteBackDelay =
			dml_max(
					dml_उच्चमान(WritebackLumaHTaps / 4.0, 1) / WritebackHRatio,
					WritebackLumaVTaps * dml_उच्चमान(1.0 / WritebackVRatio, 1)
							* dml_उच्चमान(
									WritebackDestinationWidth
											/ 4.0,
									1)
							+ dml_उच्चमान(1.0 / WritebackVRatio, 1)
									* (dml_उच्चमान(
											WritebackLumaVTaps
													/ 4.0,
											1) + 4));

	अगर (WritebackPixelFormat != dm_444_32) अणु
		CalculateWriteBackDelay =
				dml_max(
						CalculateWriteBackDelay,
						dml_max(
								dml_उच्चमान(
										WritebackChromaHTaps
												/ 2.0,
										1)
										/ (2
												* WritebackHRatio),
								WritebackChromaVTaps
										* dml_उच्चमान(
												1
														/ (2
																* WritebackVRatio),
												1)
										* dml_उच्चमान(
												WritebackDestinationWidth
														/ 2.0
														/ 2.0,
												1)
										+ dml_उच्चमान(
												1
														/ (2
																* WritebackVRatio),
												1)
												* (dml_उच्चमान(
														WritebackChromaVTaps
																/ 4.0,
														1)
														+ 4)));
	पूर्ण
	वापस CalculateWriteBackDelay;
पूर्ण

अटल व्योम CalculateActiveRowBandwidth(
		bool GPUVMEnable,
		क्रमागत source_क्रमmat_class SourcePixelFormat,
		द्विगुन VRatio,
		bool DCCEnable,
		द्विगुन LineTime,
		अचिन्हित पूर्णांक MetaRowByteLuma,
		अचिन्हित पूर्णांक MetaRowByteChroma,
		अचिन्हित पूर्णांक meta_row_height_luma,
		अचिन्हित पूर्णांक meta_row_height_chroma,
		अचिन्हित पूर्णांक PixelPTEBytesPerRowLuma,
		अचिन्हित पूर्णांक PixelPTEBytesPerRowChroma,
		अचिन्हित पूर्णांक dpte_row_height_luma,
		अचिन्हित पूर्णांक dpte_row_height_chroma,
		द्विगुन *meta_row_bw,
		द्विगुन *dpte_row_bw)
अणु
	अगर (DCCEnable != true) अणु
		*meta_row_bw = 0;
	पूर्ण अन्यथा अगर (SourcePixelFormat == dm_420_8 || SourcePixelFormat == dm_420_10) अणु
		*meta_row_bw = VRatio * MetaRowByteLuma / (meta_row_height_luma * LineTime)
				+ VRatio / 2 * MetaRowByteChroma
						/ (meta_row_height_chroma * LineTime);
	पूर्ण अन्यथा अणु
		*meta_row_bw = VRatio * MetaRowByteLuma / (meta_row_height_luma * LineTime);
	पूर्ण

	अगर (GPUVMEnable != true) अणु
		*dpte_row_bw = 0;
	पूर्ण अन्यथा अगर (SourcePixelFormat == dm_420_8 || SourcePixelFormat == dm_420_10) अणु
		*dpte_row_bw = VRatio * PixelPTEBytesPerRowLuma / (dpte_row_height_luma * LineTime)
				+ VRatio / 2 * PixelPTEBytesPerRowChroma
						/ (dpte_row_height_chroma * LineTime);
	पूर्ण अन्यथा अणु
		*dpte_row_bw = VRatio * PixelPTEBytesPerRowLuma / (dpte_row_height_luma * LineTime);
	पूर्ण
पूर्ण

अटल व्योम CalculateFlipSchedule(
		काष्ठा display_mode_lib *mode_lib,
		द्विगुन PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData,
		द्विगुन PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly,
		द्विगुन UrgentExtraLatency,
		द्विगुन UrgentLatency,
		अचिन्हित पूर्णांक GPUVMMaxPageTableLevels,
		bool HostVMEnable,
		अचिन्हित पूर्णांक HostVMMaxPageTableLevels,
		अचिन्हित पूर्णांक HostVMCachedPageTableLevels,
		bool GPUVMEnable,
		द्विगुन PDEAndMetaPTEBytesPerFrame,
		द्विगुन MetaRowBytes,
		द्विगुन DPTEBytesPerRow,
		द्विगुन BandwidthAvailableForImmediateFlip,
		अचिन्हित पूर्णांक TotImmediateFlipBytes,
		क्रमागत source_क्रमmat_class SourcePixelFormat,
		द्विगुन LineTime,
		द्विगुन VRatio,
		द्विगुन Tno_bw,
		bool DCCEnable,
		अचिन्हित पूर्णांक dpte_row_height,
		अचिन्हित पूर्णांक meta_row_height,
		अचिन्हित पूर्णांक dpte_row_height_chroma,
		अचिन्हित पूर्णांक meta_row_height_chroma,
		द्विगुन *DestinationLinesToRequestVMInImmediateFlip,
		द्विगुन *DestinationLinesToRequestRowInImmediateFlip,
		द्विगुन *final_flip_bw,
		bool *ImmediateFlipSupportedForPipe)
अणु
	द्विगुन min_row_समय = 0.0;
	अचिन्हित पूर्णांक HostVMDynamicLevels;
	द्विगुन TimeForFetchingMetaPTEImmediateFlip;
	द्विगुन TimeForFetchingRowInVBlankImmediateFlip;
	द्विगुन ImmediateFlipBW;
	द्विगुन HostVMInefficiencyFactor;
	द्विगुन VRatioClamped;

	अगर (GPUVMEnable == true && HostVMEnable == true) अणु
		HostVMInefficiencyFactor =
				PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData
						/ PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly;
		HostVMDynamicLevels = HostVMMaxPageTableLevels - HostVMCachedPageTableLevels;
	पूर्ण अन्यथा अणु
		HostVMInefficiencyFactor = 1;
		HostVMDynamicLevels = 0;
	पूर्ण

	ImmediateFlipBW = (PDEAndMetaPTEBytesPerFrame + MetaRowBytes + DPTEBytesPerRow)
			* BandwidthAvailableForImmediateFlip / TotImmediateFlipBytes;

	अगर (GPUVMEnable == true) अणु
		TimeForFetchingMetaPTEImmediateFlip = dml_max3(
			Tno_bw + PDEAndMetaPTEBytesPerFrame * HostVMInefficiencyFactor / ImmediateFlipBW,
			UrgentExtraLatency + UrgentLatency * (GPUVMMaxPageTableLevels * (HostVMDynamicLevels + 1) - 1),
			LineTime / 4.0);
	पूर्ण अन्यथा अणु
		TimeForFetchingMetaPTEImmediateFlip = 0;
	पूर्ण

	*DestinationLinesToRequestVMInImmediateFlip = dml_उच्चमान(4.0 * (TimeForFetchingMetaPTEImmediateFlip / LineTime), 1) / 4.0;
	अगर ((GPUVMEnable == true || DCCEnable == true)) अणु
		TimeForFetchingRowInVBlankImmediateFlip = dml_max3((MetaRowBytes + DPTEBytesPerRow) * HostVMInefficiencyFactor / ImmediateFlipBW, UrgentLatency * (HostVMDynamicLevels + 1), LineTime / 4);
	पूर्ण अन्यथा अणु
		TimeForFetchingRowInVBlankImmediateFlip = 0;
	पूर्ण

	*DestinationLinesToRequestRowInImmediateFlip = dml_उच्चमान(4.0 * (TimeForFetchingRowInVBlankImmediateFlip / LineTime), 1) / 4.0;
	*final_flip_bw = dml_max(PDEAndMetaPTEBytesPerFrame * HostVMInefficiencyFactor / (*DestinationLinesToRequestVMInImmediateFlip * LineTime), (MetaRowBytes + DPTEBytesPerRow) * HostVMInefficiencyFactor / (*DestinationLinesToRequestRowInImmediateFlip * LineTime));
	VRatioClamped = (VRatio < 1.0) ? 1.0 : VRatio;
	अगर (SourcePixelFormat == dm_420_8 || SourcePixelFormat == dm_420_10) अणु
		अगर (GPUVMEnable == true && DCCEnable != true) अणु
			min_row_समय = dml_min(
					dpte_row_height * LineTime / VRatioClamped,
					dpte_row_height_chroma * LineTime / (VRatioClamped / 2));
		पूर्ण अन्यथा अगर (GPUVMEnable != true && DCCEnable == true) अणु
			min_row_समय = dml_min(
					meta_row_height * LineTime / VRatioClamped,
					meta_row_height_chroma * LineTime / (VRatioClamped / 2));
		पूर्ण अन्यथा अणु
			min_row_समय = dml_min4(
					dpte_row_height * LineTime / VRatioClamped,
					meta_row_height * LineTime / VRatioClamped,
					dpte_row_height_chroma * LineTime / (VRatioClamped / 2),
					meta_row_height_chroma * LineTime / (VRatioClamped / 2));
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (GPUVMEnable == true && DCCEnable != true) अणु
			min_row_समय = dpte_row_height * LineTime / VRatioClamped;
		पूर्ण अन्यथा अगर (GPUVMEnable != true && DCCEnable == true) अणु
			min_row_समय = meta_row_height * LineTime / VRatioClamped;
		पूर्ण अन्यथा अणु
			min_row_समय = dml_min(
					dpte_row_height * LineTime / VRatioClamped,
					meta_row_height * LineTime / VRatioClamped);
		पूर्ण
	पूर्ण

	अगर (*DestinationLinesToRequestVMInImmediateFlip >= 32
			|| *DestinationLinesToRequestRowInImmediateFlip >= 16
			|| TimeForFetchingMetaPTEImmediateFlip + 2 * TimeForFetchingRowInVBlankImmediateFlip > min_row_समय) अणु
		*ImmediateFlipSupportedForPipe = false;
	पूर्ण अन्यथा अणु
		*ImmediateFlipSupportedForPipe = true;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक TruncToValidBPP(
		द्विगुन DecimalBPP,
		द्विगुन DesiredBPP,
		bool DSCEnabled,
		क्रमागत output_encoder_class Output,
		क्रमागत output_क्रमmat_class Format,
		अचिन्हित पूर्णांक DSCInputBitPerComponent)
अणु
	अगर (Output == dm_hdmi) अणु
		अगर (Format == dm_420) अणु
			अगर (DecimalBPP >= 18 && (DesiredBPP == 0 || DesiredBPP == 18))
				वापस 18;
			अन्यथा अगर (DecimalBPP >= 15 && (DesiredBPP == 0 || DesiredBPP == 15))
				वापस 15;
			अन्यथा अगर (DecimalBPP >= 12 && (DesiredBPP == 0 || DesiredBPP == 12))
				वापस 12;
			अन्यथा
				वापस BPP_INVALID;
		पूर्ण अन्यथा अगर (Format == dm_444) अणु
			अगर (DecimalBPP >= 36 && (DesiredBPP == 0 || DesiredBPP == 36))
				वापस 36;
			अन्यथा अगर (DecimalBPP >= 30 && (DesiredBPP == 0 || DesiredBPP == 30))
				वापस 30;
			अन्यथा अगर (DecimalBPP >= 24 && (DesiredBPP == 0 || DesiredBPP == 24))
				वापस 24;
			अन्यथा अगर (DecimalBPP >= 18 && (DesiredBPP == 0 || DesiredBPP == 18))
				वापस 18;
			अन्यथा
				वापस BPP_INVALID;
		पूर्ण अन्यथा अणु
			अगर (DecimalBPP / 1.5 >= 24 && (DesiredBPP == 0 || DesiredBPP == 24))
				वापस 24;
			अन्यथा अगर (DecimalBPP / 1.5 >= 20 && (DesiredBPP == 0 || DesiredBPP == 20))
				वापस 20;
			अन्यथा अगर (DecimalBPP / 1.5 >= 16 && (DesiredBPP == 0 || DesiredBPP == 16))
				वापस 16;
			अन्यथा
				वापस BPP_INVALID;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (DSCEnabled) अणु
			अगर (Format == dm_420) अणु
				अगर (DesiredBPP == 0) अणु
					अगर (DecimalBPP < 6)
						वापस BPP_INVALID;
					अन्यथा अगर (DecimalBPP >= 1.5 * DSCInputBitPerComponent - 1.0 / 16.0)
						वापस 1.5 * DSCInputBitPerComponent - 1.0 / 16.0;
					अन्यथा
						वापस dml_न्यूनमान(16 * DecimalBPP, 1) / 16.0;
				पूर्ण अन्यथा अणु
					अगर (DecimalBPP < 6
							|| DesiredBPP < 6
							|| DesiredBPP > 1.5 * DSCInputBitPerComponent - 1.0 / 16.0
							|| DecimalBPP < DesiredBPP) अणु
						वापस BPP_INVALID;
					पूर्ण अन्यथा अणु
						वापस DesiredBPP;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अगर (Format == dm_n422) अणु
				अगर (DesiredBPP == 0) अणु
					अगर (DecimalBPP < 7)
						वापस BPP_INVALID;
					अन्यथा अगर (DecimalBPP >= 2 * DSCInputBitPerComponent - 1.0 / 16.0)
						वापस 2 * DSCInputBitPerComponent - 1.0 / 16.0;
					अन्यथा
						वापस dml_न्यूनमान(16 * DecimalBPP, 1) / 16.0;
				पूर्ण अन्यथा अणु
					अगर (DecimalBPP < 7
							|| DesiredBPP < 7
							|| DesiredBPP > 2 * DSCInputBitPerComponent - 1.0 / 16.0
							|| DecimalBPP < DesiredBPP) अणु
						वापस BPP_INVALID;
					पूर्ण अन्यथा अणु
						वापस DesiredBPP;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (DesiredBPP == 0) अणु
					अगर (DecimalBPP < 8)
						वापस BPP_INVALID;
					अन्यथा अगर (DecimalBPP >= 3 * DSCInputBitPerComponent - 1.0 / 16.0)
						वापस 3 * DSCInputBitPerComponent - 1.0 / 16.0;
					अन्यथा
						वापस dml_न्यूनमान(16 * DecimalBPP, 1) / 16.0;
				पूर्ण अन्यथा अणु
					अगर (DecimalBPP < 8
							|| DesiredBPP < 8
							|| DesiredBPP > 3 * DSCInputBitPerComponent - 1.0 / 16.0
							|| DecimalBPP < DesiredBPP) अणु
						वापस BPP_INVALID;
					पूर्ण अन्यथा अणु
						वापस DesiredBPP;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (Format == dm_420) अणु
			अगर (DecimalBPP >= 18 && (DesiredBPP == 0 || DesiredBPP == 18))
				वापस 18;
			अन्यथा अगर (DecimalBPP >= 15 && (DesiredBPP == 0 || DesiredBPP == 15))
				वापस 15;
			अन्यथा अगर (DecimalBPP >= 12 && (DesiredBPP == 0 || DesiredBPP == 12))
				वापस 12;
			अन्यथा
				वापस BPP_INVALID;
		पूर्ण अन्यथा अगर (Format == dm_s422 || Format == dm_n422) अणु
			अगर (DecimalBPP >= 24 && (DesiredBPP == 0 || DesiredBPP == 24))
				वापस 24;
			अन्यथा अगर (DecimalBPP >= 20 && (DesiredBPP == 0 || DesiredBPP == 20))
				वापस 20;
			अन्यथा अगर (DecimalBPP >= 16 && (DesiredBPP == 0 || DesiredBPP == 16))
				वापस 16;
			अन्यथा
				वापस BPP_INVALID;
		पूर्ण अन्यथा अणु
			अगर (DecimalBPP >= 36 && (DesiredBPP == 0 || DesiredBPP == 36))
				वापस 36;
			अन्यथा अगर (DecimalBPP >= 30 && (DesiredBPP == 0 || DesiredBPP == 30))
				वापस 30;
			अन्यथा अगर (DecimalBPP >= 24 && (DesiredBPP == 0 || DesiredBPP == 24))
				वापस 24;
			अन्यथा अगर (DecimalBPP >= 18 && (DesiredBPP == 0 || DesiredBPP == 18))
				वापस 18;
			अन्यथा
				वापस BPP_INVALID;
		पूर्ण
	पूर्ण
पूर्ण

व्योम dml21_ModeSupportAndSystemConfigurationFull(काष्ठा display_mode_lib *mode_lib)
अणु
	काष्ठा vba_vars_st *locals = &mode_lib->vba;

	पूर्णांक i;
	अचिन्हित पूर्णांक j, k, m;

	/*MODE SUPPORT, VOLTAGE STATE AND SOC CONFIGURATION*/

	/*Scale Ratio, taps Support Check*/

	mode_lib->vba.ScaleRatioAndTapsSupport = true;
	क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
		अगर (mode_lib->vba.ScalerEnabled[k] == false
				&& ((mode_lib->vba.SourcePixelFormat[k] != dm_444_64
						&& mode_lib->vba.SourcePixelFormat[k] != dm_444_32
						&& mode_lib->vba.SourcePixelFormat[k] != dm_444_16
						&& mode_lib->vba.SourcePixelFormat[k] != dm_mono_16
						&& mode_lib->vba.SourcePixelFormat[k] != dm_mono_8)
						|| mode_lib->vba.HRatio[k] != 1.0
						|| mode_lib->vba.htaps[k] != 1.0
						|| mode_lib->vba.VRatio[k] != 1.0
						|| mode_lib->vba.vtaps[k] != 1.0)) अणु
			mode_lib->vba.ScaleRatioAndTapsSupport = false;
		पूर्ण अन्यथा अगर (mode_lib->vba.vtaps[k] < 1.0 || mode_lib->vba.vtaps[k] > 8.0
				|| mode_lib->vba.htaps[k] < 1.0 || mode_lib->vba.htaps[k] > 8.0
				|| (mode_lib->vba.htaps[k] > 1.0
						&& (mode_lib->vba.htaps[k] % 2) == 1)
				|| mode_lib->vba.HRatio[k] > mode_lib->vba.MaxHSCLRatio
				|| mode_lib->vba.VRatio[k] > mode_lib->vba.MaxVSCLRatio
				|| mode_lib->vba.HRatio[k] > mode_lib->vba.htaps[k]
				|| mode_lib->vba.VRatio[k] > mode_lib->vba.vtaps[k]
				|| (mode_lib->vba.SourcePixelFormat[k] != dm_444_64
						&& mode_lib->vba.SourcePixelFormat[k] != dm_444_32
						&& mode_lib->vba.SourcePixelFormat[k] != dm_444_16
						&& mode_lib->vba.SourcePixelFormat[k] != dm_mono_16
						&& mode_lib->vba.SourcePixelFormat[k] != dm_mono_8
						&& (mode_lib->vba.HRatio[k] / 2.0
								> mode_lib->vba.HTAPsChroma[k]
								|| mode_lib->vba.VRatio[k] / 2.0
										> mode_lib->vba.VTAPsChroma[k]))) अणु
			mode_lib->vba.ScaleRatioAndTapsSupport = false;
		पूर्ण
	पूर्ण
	/*Source Format, Pixel Format and Scan Support Check*/

	mode_lib->vba.SourceFormatPixelAndScanSupport = true;
	क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
		अगर ((mode_lib->vba.SurfaceTiling[k] == dm_sw_linear
				&& mode_lib->vba.SourceScan[k] != dm_horz)
				|| ((mode_lib->vba.SurfaceTiling[k] == dm_sw_4kb_d
						|| mode_lib->vba.SurfaceTiling[k] == dm_sw_4kb_d_x
						|| mode_lib->vba.SurfaceTiling[k] == dm_sw_64kb_d
						|| mode_lib->vba.SurfaceTiling[k] == dm_sw_64kb_d_t
						|| mode_lib->vba.SurfaceTiling[k] == dm_sw_64kb_d_x
						|| mode_lib->vba.SurfaceTiling[k] == dm_sw_var_d
						|| mode_lib->vba.SurfaceTiling[k] == dm_sw_var_d_x)
						&& mode_lib->vba.SourcePixelFormat[k] != dm_444_64)
				|| (mode_lib->vba.SurfaceTiling[k] == dm_sw_64kb_r_x
						&& (mode_lib->vba.SourcePixelFormat[k] == dm_mono_8
								|| mode_lib->vba.SourcePixelFormat[k]
										== dm_420_8
								|| mode_lib->vba.SourcePixelFormat[k]
										== dm_420_10))
				|| (((mode_lib->vba.SurfaceTiling[k] == dm_sw_gfx7_2d_thin_gl
						|| mode_lib->vba.SurfaceTiling[k]
								== dm_sw_gfx7_2d_thin_l_vp)
						&& !((mode_lib->vba.SourcePixelFormat[k]
								== dm_444_64
								|| mode_lib->vba.SourcePixelFormat[k]
										== dm_444_32)
								&& mode_lib->vba.SourceScan[k]
										== dm_horz
								&& mode_lib->vba.SupportGFX7CompatibleTilingIn32bppAnd64bpp
										== true
								&& mode_lib->vba.DCCEnable[k]
										== false))
						|| (mode_lib->vba.DCCEnable[k] == true
								&& (mode_lib->vba.SurfaceTiling[k]
										== dm_sw_linear
										|| mode_lib->vba.SourcePixelFormat[k]
												== dm_420_8
										|| mode_lib->vba.SourcePixelFormat[k]
												== dm_420_10)))) अणु
			mode_lib->vba.SourceFormatPixelAndScanSupport = false;
		पूर्ण
	पूर्ण
	/*Bandwidth Support Check*/

	क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
		अगर (mode_lib->vba.SourcePixelFormat[k] == dm_444_64) अणु
			locals->BytePerPixelInDETY[k] = 8.0;
			locals->BytePerPixelInDETC[k] = 0.0;
		पूर्ण अन्यथा अगर (mode_lib->vba.SourcePixelFormat[k] == dm_444_32) अणु
			locals->BytePerPixelInDETY[k] = 4.0;
			locals->BytePerPixelInDETC[k] = 0.0;
		पूर्ण अन्यथा अगर (mode_lib->vba.SourcePixelFormat[k] == dm_444_16
				|| mode_lib->vba.SourcePixelFormat[k] == dm_mono_16) अणु
			locals->BytePerPixelInDETY[k] = 2.0;
			locals->BytePerPixelInDETC[k] = 0.0;
		पूर्ण अन्यथा अगर (mode_lib->vba.SourcePixelFormat[k] == dm_mono_8) अणु
			locals->BytePerPixelInDETY[k] = 1.0;
			locals->BytePerPixelInDETC[k] = 0.0;
		पूर्ण अन्यथा अगर (mode_lib->vba.SourcePixelFormat[k] == dm_420_8) अणु
			locals->BytePerPixelInDETY[k] = 1.0;
			locals->BytePerPixelInDETC[k] = 2.0;
		पूर्ण अन्यथा अणु
			locals->BytePerPixelInDETY[k] = 4.0 / 3;
			locals->BytePerPixelInDETC[k] = 8.0 / 3;
		पूर्ण
		अगर (mode_lib->vba.SourceScan[k] == dm_horz) अणु
			locals->SwathWidthYSingleDPP[k] = mode_lib->vba.ViewportWidth[k];
		पूर्ण अन्यथा अणु
			locals->SwathWidthYSingleDPP[k] = mode_lib->vba.ViewportHeight[k];
		पूर्ण
	पूर्ण
	क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
		locals->ReadBandwidthLuma[k] = locals->SwathWidthYSingleDPP[k] * dml_उच्चमान(locals->BytePerPixelInDETY[k], 1.0)
				/ (mode_lib->vba.HTotal[k] / mode_lib->vba.PixelClock[k]) * mode_lib->vba.VRatio[k];
		locals->ReadBandwidthChroma[k] = locals->SwathWidthYSingleDPP[k] / 2 * dml_उच्चमान(locals->BytePerPixelInDETC[k], 2.0)
				/ (mode_lib->vba.HTotal[k] / mode_lib->vba.PixelClock[k]) * mode_lib->vba.VRatio[k] / 2.0;
		locals->ReadBandwidth[k] = locals->ReadBandwidthLuma[k] + locals->ReadBandwidthChroma[k];
	पूर्ण
	क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
		अगर (mode_lib->vba.WritebackEnable[k] == true
				&& mode_lib->vba.WritebackPixelFormat[k] == dm_444_32) अणु
			locals->WriteBandwidth[k] = mode_lib->vba.WritebackDestinationWidth[k]
					* mode_lib->vba.WritebackDestinationHeight[k]
					/ (mode_lib->vba.WritebackSourceHeight[k]
							* mode_lib->vba.HTotal[k]
							/ mode_lib->vba.PixelClock[k]) * 4.0;
		पूर्ण अन्यथा अगर (mode_lib->vba.WritebackEnable[k] == true
				&& mode_lib->vba.WritebackPixelFormat[k] == dm_420_10) अणु
			locals->WriteBandwidth[k] = mode_lib->vba.WritebackDestinationWidth[k]
					* mode_lib->vba.WritebackDestinationHeight[k]
					/ (mode_lib->vba.WritebackSourceHeight[k]
							* mode_lib->vba.HTotal[k]
							/ mode_lib->vba.PixelClock[k]) * 3.0;
		पूर्ण अन्यथा अगर (mode_lib->vba.WritebackEnable[k] == true) अणु
			locals->WriteBandwidth[k] = mode_lib->vba.WritebackDestinationWidth[k]
					* mode_lib->vba.WritebackDestinationHeight[k]
					/ (mode_lib->vba.WritebackSourceHeight[k]
							* mode_lib->vba.HTotal[k]
							/ mode_lib->vba.PixelClock[k]) * 1.5;
		पूर्ण अन्यथा अणु
			locals->WriteBandwidth[k] = 0.0;
		पूर्ण
	पूर्ण
	mode_lib->vba.DCCEnabledInAnyPlane = false;
	क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
		अगर (mode_lib->vba.DCCEnable[k] == true) अणु
			mode_lib->vba.DCCEnabledInAnyPlane = true;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i <= mode_lib->vba.soc.num_states; i++) अणु
		locals->IdealSDPPortBandwidthPerState[i][0] = dml_min3(
				mode_lib->vba.ReturnBusWidth * mode_lib->vba.DCFCLKPerState[i],
				mode_lib->vba.DRAMSpeedPerState[i] * mode_lib->vba.NumberOfChannels
						* mode_lib->vba.DRAMChannelWidth,
				mode_lib->vba.FabricClockPerState[i]
						* mode_lib->vba.FabricDatapathToDCNDataReturn);
		अगर (mode_lib->vba.HostVMEnable == false) अणु
			locals->ReturnBWPerState[i][0] = locals->IdealSDPPortBandwidthPerState[i][0]
					* mode_lib->vba.PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelDataOnly / 100.0;
		पूर्ण अन्यथा अणु
			locals->ReturnBWPerState[i][0] = locals->IdealSDPPortBandwidthPerState[i][0]
					* mode_lib->vba.PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData / 100.0;
		पूर्ण
	पूर्ण
	/*Writeback Latency support check*/

	mode_lib->vba.WritebackLatencySupport = true;
	क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
		अगर (mode_lib->vba.WritebackEnable[k] == true) अणु
			अगर (mode_lib->vba.WritebackPixelFormat[k] == dm_444_32) अणु
				अगर (locals->WriteBandwidth[k]
						> (mode_lib->vba.WritebackInterfaceLumaBufferSize
								+ mode_lib->vba.WritebackInterfaceChromaBufferSize)
								/ mode_lib->vba.WritebackLatency) अणु
					mode_lib->vba.WritebackLatencySupport = false;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (locals->WriteBandwidth[k]
						> 1.5
								* dml_min(
										mode_lib->vba.WritebackInterfaceLumaBufferSize,
										2.0
												* mode_lib->vba.WritebackInterfaceChromaBufferSize)
								/ mode_lib->vba.WritebackLatency) अणु
					mode_lib->vba.WritebackLatencySupport = false;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	/*Re-ordering Buffer Support Check*/

	क्रम (i = 0; i <= mode_lib->vba.soc.num_states; i++) अणु
		locals->UrgentRoundTripAndOutOfOrderLatencyPerState[i] =
				(mode_lib->vba.RoundTripPingLatencyCycles + 32.0) / mode_lib->vba.DCFCLKPerState[i]
				+ dml_max3(mode_lib->vba.UrgentOutOfOrderReturnPerChannelPixelDataOnly,
						mode_lib->vba.UrgentOutOfOrderReturnPerChannelPixelMixedWithVMData,
						mode_lib->vba.UrgentOutOfOrderReturnPerChannelVMDataOnly)
					* mode_lib->vba.NumberOfChannels / locals->ReturnBWPerState[i][0];
		अगर ((mode_lib->vba.ROBBufferSizeInKByte - mode_lib->vba.PixelChunkSizeInKByte) * 1024.0 / locals->ReturnBWPerState[i][0]
				> locals->UrgentRoundTripAndOutOfOrderLatencyPerState[i]) अणु
			locals->ROBSupport[i][0] = true;
		पूर्ण अन्यथा अणु
			locals->ROBSupport[i][0] = false;
		पूर्ण
	पूर्ण
	/*Writeback Mode Support Check*/

	mode_lib->vba.TotalNumberOfActiveWriteback = 0;
	क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
		अगर (mode_lib->vba.WritebackEnable[k] == true) अणु
			अगर (mode_lib->vba.ActiveWritebacksPerPlane[k] == 0)
				mode_lib->vba.ActiveWritebacksPerPlane[k] = 1;
			mode_lib->vba.TotalNumberOfActiveWriteback =
					mode_lib->vba.TotalNumberOfActiveWriteback
							+ mode_lib->vba.ActiveWritebacksPerPlane[k];
		पूर्ण
	पूर्ण
	mode_lib->vba.WritebackModeSupport = true;
	अगर (mode_lib->vba.TotalNumberOfActiveWriteback > mode_lib->vba.MaxNumWriteback) अणु
		mode_lib->vba.WritebackModeSupport = false;
	पूर्ण
	क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
		अगर (mode_lib->vba.WritebackEnable[k] == true
				&& mode_lib->vba.Writeback10bpc420Supported != true
				&& mode_lib->vba.WritebackPixelFormat[k] == dm_420_10) अणु
			mode_lib->vba.WritebackModeSupport = false;
		पूर्ण
	पूर्ण
	/*Writeback Scale Ratio and Taps Support Check*/

	mode_lib->vba.WritebackScaleRatioAndTapsSupport = true;
	क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
		अगर (mode_lib->vba.WritebackEnable[k] == true) अणु
			अगर (mode_lib->vba.WritebackLumaAndChromaScalingSupported == false
					&& (mode_lib->vba.WritebackHRatio[k] != 1.0
							|| mode_lib->vba.WritebackVRatio[k] != 1.0)) अणु
				mode_lib->vba.WritebackScaleRatioAndTapsSupport = false;
			पूर्ण
			अगर (mode_lib->vba.WritebackHRatio[k] > mode_lib->vba.WritebackMaxHSCLRatio
					|| mode_lib->vba.WritebackVRatio[k]
							> mode_lib->vba.WritebackMaxVSCLRatio
					|| mode_lib->vba.WritebackHRatio[k]
							< mode_lib->vba.WritebackMinHSCLRatio
					|| mode_lib->vba.WritebackVRatio[k]
							< mode_lib->vba.WritebackMinVSCLRatio
					|| mode_lib->vba.WritebackLumaHTaps[k]
							> mode_lib->vba.WritebackMaxHSCLTaps
					|| mode_lib->vba.WritebackLumaVTaps[k]
							> mode_lib->vba.WritebackMaxVSCLTaps
					|| mode_lib->vba.WritebackHRatio[k]
							> mode_lib->vba.WritebackLumaHTaps[k]
					|| mode_lib->vba.WritebackVRatio[k]
							> mode_lib->vba.WritebackLumaVTaps[k]
					|| (mode_lib->vba.WritebackLumaHTaps[k] > 2.0
							&& ((mode_lib->vba.WritebackLumaHTaps[k] % 2)
									== 1))
					|| (mode_lib->vba.WritebackPixelFormat[k] != dm_444_32
							&& (mode_lib->vba.WritebackChromaHTaps[k]
									> mode_lib->vba.WritebackMaxHSCLTaps
									|| mode_lib->vba.WritebackChromaVTaps[k]
											> mode_lib->vba.WritebackMaxVSCLTaps
									|| 2.0
											* mode_lib->vba.WritebackHRatio[k]
											> mode_lib->vba.WritebackChromaHTaps[k]
									|| 2.0
											* mode_lib->vba.WritebackVRatio[k]
											> mode_lib->vba.WritebackChromaVTaps[k]
									|| (mode_lib->vba.WritebackChromaHTaps[k] > 2.0
										&& ((mode_lib->vba.WritebackChromaHTaps[k] % 2) == 1))))) अणु
				mode_lib->vba.WritebackScaleRatioAndTapsSupport = false;
			पूर्ण
			अगर (mode_lib->vba.WritebackVRatio[k] < 1.0) अणु
				mode_lib->vba.WritebackLumaVExtra =
						dml_max(1.0 - 2.0 / dml_उच्चमान(1.0 / mode_lib->vba.WritebackVRatio[k], 1.0), 0.0);
			पूर्ण अन्यथा अणु
				mode_lib->vba.WritebackLumaVExtra = -1;
			पूर्ण
			अगर ((mode_lib->vba.WritebackPixelFormat[k] == dm_444_32
					&& mode_lib->vba.WritebackLumaVTaps[k]
							> (mode_lib->vba.WritebackLineBufferLumaBufferSize
									+ mode_lib->vba.WritebackLineBufferChromaBufferSize)
									/ 3.0
									/ mode_lib->vba.WritebackDestinationWidth[k]
									- mode_lib->vba.WritebackLumaVExtra)
					|| (mode_lib->vba.WritebackPixelFormat[k] == dm_420_8
							&& mode_lib->vba.WritebackLumaVTaps[k]
									> mode_lib->vba.WritebackLineBufferLumaBufferSize
											* 8.0 / 10.0 / mode_lib->vba.WritebackDestinationWidth[k]
											- mode_lib->vba.WritebackLumaVExtra)
					|| (mode_lib->vba.WritebackPixelFormat[k] == dm_420_10
							&& mode_lib->vba.WritebackLumaVTaps[k]
									> mode_lib->vba.WritebackLineBufferLumaBufferSize
											* 8.0 / 10.0
											/ mode_lib->vba.WritebackDestinationWidth[k]
											- mode_lib->vba.WritebackLumaVExtra)) अणु
				mode_lib->vba.WritebackScaleRatioAndTapsSupport = false;
			पूर्ण
			अगर (2.0 * mode_lib->vba.WritebackVRatio[k] < 1) अणु
				mode_lib->vba.WritebackChromaVExtra = 0.0;
			पूर्ण अन्यथा अणु
				mode_lib->vba.WritebackChromaVExtra = -1;
			पूर्ण
			अगर ((mode_lib->vba.WritebackPixelFormat[k] == dm_420_8
					&& mode_lib->vba.WritebackChromaVTaps[k]
							> mode_lib->vba.WritebackLineBufferChromaBufferSize
									* 8.0 / 10.0 / mode_lib->vba.WritebackDestinationWidth[k]
									- mode_lib->vba.WritebackChromaVExtra)
					|| (mode_lib->vba.WritebackPixelFormat[k] == dm_420_10
							&& mode_lib->vba.WritebackChromaVTaps[k]
									> mode_lib->vba.WritebackLineBufferChromaBufferSize
											* 8.0 / 10.0
											/ mode_lib->vba.WritebackDestinationWidth[k]
											- mode_lib->vba.WritebackChromaVExtra)) अणु
				mode_lib->vba.WritebackScaleRatioAndTapsSupport = false;
			पूर्ण
		पूर्ण
	पूर्ण
	/*Maximum DISPCLK/DPPCLK Support check*/

	mode_lib->vba.WritebackRequiredDISPCLK = 0.0;
	क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
		अगर (mode_lib->vba.WritebackEnable[k] == true) अणु
			mode_lib->vba.WritebackRequiredDISPCLK =
					dml_max(
							mode_lib->vba.WritebackRequiredDISPCLK,
							CalculateWriteBackDISPCLK(
									mode_lib->vba.WritebackPixelFormat[k],
									mode_lib->vba.PixelClock[k],
									mode_lib->vba.WritebackHRatio[k],
									mode_lib->vba.WritebackVRatio[k],
									mode_lib->vba.WritebackLumaHTaps[k],
									mode_lib->vba.WritebackLumaVTaps[k],
									mode_lib->vba.WritebackChromaHTaps[k],
									mode_lib->vba.WritebackChromaVTaps[k],
									mode_lib->vba.WritebackDestinationWidth[k],
									mode_lib->vba.HTotal[k],
									mode_lib->vba.WritebackChromaLineBufferWidth));
		पूर्ण
	पूर्ण
	क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
		अगर (mode_lib->vba.HRatio[k] > 1.0) अणु
			locals->PSCL_FACTOR[k] = dml_min(
					mode_lib->vba.MaxDCHUBToPSCLThroughput,
					mode_lib->vba.MaxPSCLToLBThroughput
							* mode_lib->vba.HRatio[k]
							/ dml_उच्चमान(
									mode_lib->vba.htaps[k]
											/ 6.0,
									1.0));
		पूर्ण अन्यथा अणु
			locals->PSCL_FACTOR[k] = dml_min(
					mode_lib->vba.MaxDCHUBToPSCLThroughput,
					mode_lib->vba.MaxPSCLToLBThroughput);
		पूर्ण
		अगर (locals->BytePerPixelInDETC[k] == 0.0) अणु
			locals->PSCL_FACTOR_CHROMA[k] = 0.0;
			locals->MinDPPCLKUsingSingleDPP[k] =
					mode_lib->vba.PixelClock[k]
							* dml_max3(
									mode_lib->vba.vtaps[k] / 6.0
											* dml_min(
													1.0,
													mode_lib->vba.HRatio[k]),
									mode_lib->vba.HRatio[k]
											* mode_lib->vba.VRatio[k]
											/ locals->PSCL_FACTOR[k],
									1.0);
			अगर ((mode_lib->vba.htaps[k] > 6.0 || mode_lib->vba.vtaps[k] > 6.0)
					&& locals->MinDPPCLKUsingSingleDPP[k]
							< 2.0 * mode_lib->vba.PixelClock[k]) अणु
				locals->MinDPPCLKUsingSingleDPP[k] = 2.0
						* mode_lib->vba.PixelClock[k];
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (mode_lib->vba.HRatio[k] / 2.0 > 1.0) अणु
				locals->PSCL_FACTOR_CHROMA[k] =
						dml_min(
								mode_lib->vba.MaxDCHUBToPSCLThroughput,
								mode_lib->vba.MaxPSCLToLBThroughput
										* mode_lib->vba.HRatio[k]
										/ 2.0
										/ dml_उच्चमान(
												mode_lib->vba.HTAPsChroma[k]
														/ 6.0,
												1.0));
			पूर्ण अन्यथा अणु
				locals->PSCL_FACTOR_CHROMA[k] = dml_min(
						mode_lib->vba.MaxDCHUBToPSCLThroughput,
						mode_lib->vba.MaxPSCLToLBThroughput);
			पूर्ण
			locals->MinDPPCLKUsingSingleDPP[k] =
					mode_lib->vba.PixelClock[k]
							* dml_max5(
									mode_lib->vba.vtaps[k] / 6.0
											* dml_min(
													1.0,
													mode_lib->vba.HRatio[k]),
									mode_lib->vba.HRatio[k]
											* mode_lib->vba.VRatio[k]
											/ locals->PSCL_FACTOR[k],
									mode_lib->vba.VTAPsChroma[k]
											/ 6.0
											* dml_min(
													1.0,
													mode_lib->vba.HRatio[k]
															/ 2.0),
									mode_lib->vba.HRatio[k]
											* mode_lib->vba.VRatio[k]
											/ 4.0
											/ locals->PSCL_FACTOR_CHROMA[k],
									1.0);
			अगर ((mode_lib->vba.htaps[k] > 6.0 || mode_lib->vba.vtaps[k] > 6.0
					|| mode_lib->vba.HTAPsChroma[k] > 6.0
					|| mode_lib->vba.VTAPsChroma[k] > 6.0)
					&& locals->MinDPPCLKUsingSingleDPP[k]
							< 2.0 * mode_lib->vba.PixelClock[k]) अणु
				locals->MinDPPCLKUsingSingleDPP[k] = 2.0
						* mode_lib->vba.PixelClock[k];
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
		Calculate256BBlockSizes(
				mode_lib->vba.SourcePixelFormat[k],
				mode_lib->vba.SurfaceTiling[k],
				dml_उच्चमान(locals->BytePerPixelInDETY[k], 1.0),
				dml_उच्चमान(locals->BytePerPixelInDETC[k], 2.0),
				&locals->Read256BlockHeightY[k],
				&locals->Read256BlockHeightC[k],
				&locals->Read256BlockWidthY[k],
				&locals->Read256BlockWidthC[k]);
		अगर (mode_lib->vba.SourceScan[k] == dm_horz) अणु
			locals->MaxSwathHeightY[k] = locals->Read256BlockHeightY[k];
			locals->MaxSwathHeightC[k] = locals->Read256BlockHeightC[k];
		पूर्ण अन्यथा अणु
			locals->MaxSwathHeightY[k] = locals->Read256BlockWidthY[k];
			locals->MaxSwathHeightC[k] = locals->Read256BlockWidthC[k];
		पूर्ण
		अगर ((mode_lib->vba.SourcePixelFormat[k] == dm_444_64
				|| mode_lib->vba.SourcePixelFormat[k] == dm_444_32
				|| mode_lib->vba.SourcePixelFormat[k] == dm_444_16
				|| mode_lib->vba.SourcePixelFormat[k] == dm_mono_16
				|| mode_lib->vba.SourcePixelFormat[k] == dm_mono_8)) अणु
			अगर (mode_lib->vba.SurfaceTiling[k] == dm_sw_linear
					|| (mode_lib->vba.SourcePixelFormat[k] == dm_444_64
							&& (mode_lib->vba.SurfaceTiling[k]
									== dm_sw_4kb_s
									|| mode_lib->vba.SurfaceTiling[k]
											== dm_sw_4kb_s_x
									|| mode_lib->vba.SurfaceTiling[k]
											== dm_sw_64kb_s
									|| mode_lib->vba.SurfaceTiling[k]
											== dm_sw_64kb_s_t
									|| mode_lib->vba.SurfaceTiling[k]
											== dm_sw_64kb_s_x
									|| mode_lib->vba.SurfaceTiling[k]
											== dm_sw_var_s
									|| mode_lib->vba.SurfaceTiling[k]
											== dm_sw_var_s_x)
							&& mode_lib->vba.SourceScan[k] == dm_horz)) अणु
				locals->MinSwathHeightY[k] = locals->MaxSwathHeightY[k];
			पूर्ण अन्यथा अणु
				locals->MinSwathHeightY[k] = locals->MaxSwathHeightY[k]
						/ 2.0;
			पूर्ण
			locals->MinSwathHeightC[k] = locals->MaxSwathHeightC[k];
		पूर्ण अन्यथा अणु
			अगर (mode_lib->vba.SurfaceTiling[k] == dm_sw_linear) अणु
				locals->MinSwathHeightY[k] = locals->MaxSwathHeightY[k];
				locals->MinSwathHeightC[k] = locals->MaxSwathHeightC[k];
			पूर्ण अन्यथा अगर (mode_lib->vba.SourcePixelFormat[k] == dm_420_8
					&& mode_lib->vba.SourceScan[k] == dm_horz) अणु
				locals->MinSwathHeightY[k] = locals->MaxSwathHeightY[k]
						/ 2.0;
				locals->MinSwathHeightC[k] = locals->MaxSwathHeightC[k];
			पूर्ण अन्यथा अगर (mode_lib->vba.SourcePixelFormat[k] == dm_420_10
					&& mode_lib->vba.SourceScan[k] == dm_horz) अणु
				locals->MinSwathHeightC[k] = locals->MaxSwathHeightC[k]
						/ 2.0;
				locals->MinSwathHeightY[k] = locals->MaxSwathHeightY[k];
			पूर्ण अन्यथा अणु
				locals->MinSwathHeightY[k] = locals->MaxSwathHeightY[k];
				locals->MinSwathHeightC[k] = locals->MaxSwathHeightC[k];
			पूर्ण
		पूर्ण
		अगर (mode_lib->vba.SurfaceTiling[k] == dm_sw_linear) अणु
			mode_lib->vba.MaximumSwathWidthSupport = 8192.0;
		पूर्ण अन्यथा अणु
			mode_lib->vba.MaximumSwathWidthSupport = 5120.0;
		पूर्ण
		mode_lib->vba.MaximumSwathWidthInDETBuffer =
				dml_min(
						mode_lib->vba.MaximumSwathWidthSupport,
						mode_lib->vba.DETBufferSizeInKByte * 1024.0 / 2.0
								/ (locals->BytePerPixelInDETY[k]
										* locals->MinSwathHeightY[k]
										+ locals->BytePerPixelInDETC[k]
												/ 2.0
												* locals->MinSwathHeightC[k]));
		अगर (locals->BytePerPixelInDETC[k] == 0.0) अणु
			mode_lib->vba.MaximumSwathWidthInLineBuffer =
					mode_lib->vba.LineBufferSize
							* dml_max(mode_lib->vba.HRatio[k], 1.0)
							/ mode_lib->vba.LBBitPerPixel[k]
							/ (mode_lib->vba.vtaps[k]
									+ dml_max(
											dml_उच्चमान(
													mode_lib->vba.VRatio[k],
													1.0)
													- 2,
											0.0));
		पूर्ण अन्यथा अणु
			mode_lib->vba.MaximumSwathWidthInLineBuffer =
					dml_min(
							mode_lib->vba.LineBufferSize
									* dml_max(
											mode_lib->vba.HRatio[k],
											1.0)
									/ mode_lib->vba.LBBitPerPixel[k]
									/ (mode_lib->vba.vtaps[k]
											+ dml_max(
													dml_उच्चमान(
															mode_lib->vba.VRatio[k],
															1.0)
															- 2,
													0.0)),
							2.0 * mode_lib->vba.LineBufferSize
									* dml_max(
											mode_lib->vba.HRatio[k]
													/ 2.0,
											1.0)
									/ mode_lib->vba.LBBitPerPixel[k]
									/ (mode_lib->vba.VTAPsChroma[k]
											+ dml_max(
													dml_उच्चमान(
															mode_lib->vba.VRatio[k]
																	/ 2.0,
															1.0)
															- 2,
													0.0)));
		पूर्ण
		locals->MaximumSwathWidth[k] = dml_min(
				mode_lib->vba.MaximumSwathWidthInDETBuffer,
				mode_lib->vba.MaximumSwathWidthInLineBuffer);
	पूर्ण
	क्रम (i = 0; i <= mode_lib->vba.soc.num_states; i++) अणु
		द्विगुन MaxMaxDispclkRoundedDown = RoundToDFSGranularityDown(
			mode_lib->vba.MaxDispclk[mode_lib->vba.soc.num_states],
			mode_lib->vba.DISPCLKDPPCLKVCOSpeed);

		क्रम (j = 0; j < 2; j++) अणु
			mode_lib->vba.MaxDispclkRoundedDownToDFSGranularity = RoundToDFSGranularityDown(
				mode_lib->vba.MaxDispclk[i],
				mode_lib->vba.DISPCLKDPPCLKVCOSpeed);
			mode_lib->vba.MaxDppclkRoundedDownToDFSGranularity = RoundToDFSGranularityDown(
				mode_lib->vba.MaxDppclk[i],
				mode_lib->vba.DISPCLKDPPCLKVCOSpeed);
			locals->RequiredDISPCLK[i][j] = 0.0;
			locals->DISPCLK_DPPCLK_Support[i][j] = true;
			क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
				mode_lib->vba.PlaneRequiredDISPCLKWithoutODMCombine =
						mode_lib->vba.PixelClock[k]
								* (1.0
										+ mode_lib->vba.DISPCLKDPPCLKDSCCLKDownSpपढ़ोing
												/ 100.0)
								* (1.0
										+ mode_lib->vba.DISPCLKRampingMargin
												/ 100.0);
				अगर (mode_lib->vba.PlaneRequiredDISPCLKWithoutODMCombine >= mode_lib->vba.MaxDispclk[i]
						&& i == mode_lib->vba.soc.num_states)
					mode_lib->vba.PlaneRequiredDISPCLKWithoutODMCombine = mode_lib->vba.PixelClock[k]
							* (1 + mode_lib->vba.DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0);

				mode_lib->vba.PlaneRequiredDISPCLKWithODMCombine = mode_lib->vba.PixelClock[k] / 2
					* (1 + mode_lib->vba.DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0) * (1 + mode_lib->vba.DISPCLKRampingMargin / 100.0);
				अगर (mode_lib->vba.PlaneRequiredDISPCLKWithODMCombine >= mode_lib->vba.MaxDispclk[i]
						&& i == mode_lib->vba.soc.num_states)
					mode_lib->vba.PlaneRequiredDISPCLKWithODMCombine = mode_lib->vba.PixelClock[k] / 2
							* (1 + mode_lib->vba.DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0);

				locals->ODMCombineEnablePerState[i][k] = false;
				mode_lib->vba.PlaneRequiredDISPCLK = mode_lib->vba.PlaneRequiredDISPCLKWithoutODMCombine;
				अगर (mode_lib->vba.ODMCapability) अणु
					अगर (locals->PlaneRequiredDISPCLKWithoutODMCombine > MaxMaxDispclkRoundedDown) अणु
						locals->ODMCombineEnablePerState[i][k] = true;
						mode_lib->vba.PlaneRequiredDISPCLK = mode_lib->vba.PlaneRequiredDISPCLKWithODMCombine;
					पूर्ण अन्यथा अगर (locals->DSCEnabled[k] && (locals->HActive[k] > DCN21_MAX_DSC_IMAGE_WIDTH)) अणु
						locals->ODMCombineEnablePerState[i][k] = true;
						mode_lib->vba.PlaneRequiredDISPCLK = mode_lib->vba.PlaneRequiredDISPCLKWithODMCombine;
					पूर्ण अन्यथा अगर (locals->HActive[k] > DCN21_MAX_420_IMAGE_WIDTH && locals->OutputFormat[k] == dm_420) अणु
						locals->ODMCombineEnablePerState[i][k] = true;
						mode_lib->vba.PlaneRequiredDISPCLK = mode_lib->vba.PlaneRequiredDISPCLKWithODMCombine;
					पूर्ण
				पूर्ण

				अगर (locals->MinDPPCLKUsingSingleDPP[k] * (1.0 + mode_lib->vba.DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0) <= mode_lib->vba.MaxDppclkRoundedDownToDFSGranularity
						&& locals->SwathWidthYSingleDPP[k] <= locals->MaximumSwathWidth[k]
						&& locals->ODMCombineEnablePerState[i][k] == dm_odm_combine_mode_disabled) अणु
					locals->NoOfDPP[i][j][k] = 1;
					locals->RequiredDPPCLK[i][j][k] =
						locals->MinDPPCLKUsingSingleDPP[k] * (1.0 + mode_lib->vba.DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0);
				पूर्ण अन्यथा अणु
					locals->NoOfDPP[i][j][k] = 2;
					locals->RequiredDPPCLK[i][j][k] =
						locals->MinDPPCLKUsingSingleDPP[k] * (1.0 + mode_lib->vba.DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0) / 2.0;
				पूर्ण
				locals->RequiredDISPCLK[i][j] = dml_max(
						locals->RequiredDISPCLK[i][j],
						mode_lib->vba.PlaneRequiredDISPCLK);
				अगर ((locals->MinDPPCLKUsingSingleDPP[k] / locals->NoOfDPP[i][j][k] * (1.0 + mode_lib->vba.DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0)
						> mode_lib->vba.MaxDppclkRoundedDownToDFSGranularity)
						|| (mode_lib->vba.PlaneRequiredDISPCLK > mode_lib->vba.MaxDispclkRoundedDownToDFSGranularity)) अणु
					locals->DISPCLK_DPPCLK_Support[i][j] = false;
				पूर्ण
			पूर्ण
			locals->TotalNumberOfActiveDPP[i][j] = 0.0;
			क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++)
				locals->TotalNumberOfActiveDPP[i][j] = locals->TotalNumberOfActiveDPP[i][j] + locals->NoOfDPP[i][j][k];
			अगर (j == 1) अणु
				जबतक (locals->TotalNumberOfActiveDPP[i][j] < mode_lib->vba.MaxNumDPP
						&& locals->TotalNumberOfActiveDPP[i][j] < 2 * mode_lib->vba.NumberOfActivePlanes) अणु
					द्विगुन BWOfNonSplitPlaneOfMaximumBandwidth;
					अचिन्हित पूर्णांक NumberOfNonSplitPlaneOfMaximumBandwidth;

					BWOfNonSplitPlaneOfMaximumBandwidth = 0;
					NumberOfNonSplitPlaneOfMaximumBandwidth = 0;
					क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
						अगर (locals->ReadBandwidth[k] > BWOfNonSplitPlaneOfMaximumBandwidth && locals->NoOfDPP[i][j][k] == 1) अणु
							BWOfNonSplitPlaneOfMaximumBandwidth = locals->ReadBandwidth[k];
							NumberOfNonSplitPlaneOfMaximumBandwidth = k;
						पूर्ण
					पूर्ण
					locals->NoOfDPP[i][j][NumberOfNonSplitPlaneOfMaximumBandwidth] = 2;
					locals->RequiredDPPCLK[i][j][NumberOfNonSplitPlaneOfMaximumBandwidth] =
						locals->MinDPPCLKUsingSingleDPP[NumberOfNonSplitPlaneOfMaximumBandwidth]
							* (1 + mode_lib->vba.DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100) / 2;
					locals->TotalNumberOfActiveDPP[i][j] = locals->TotalNumberOfActiveDPP[i][j] + 1;
				पूर्ण
			पूर्ण
			अगर (locals->TotalNumberOfActiveDPP[i][j] > mode_lib->vba.MaxNumDPP) अणु
				locals->RequiredDISPCLK[i][j] = 0.0;
				locals->DISPCLK_DPPCLK_Support[i][j] = true;
				क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
					locals->ODMCombineEnablePerState[i][k] = false;
					अगर (locals->SwathWidthYSingleDPP[k] <= locals->MaximumSwathWidth[k]) अणु
						locals->NoOfDPP[i][j][k] = 1;
						locals->RequiredDPPCLK[i][j][k] = locals->MinDPPCLKUsingSingleDPP[k]
							* (1.0 + mode_lib->vba.DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0);
					पूर्ण अन्यथा अणु
						locals->NoOfDPP[i][j][k] = 2;
						locals->RequiredDPPCLK[i][j][k] = locals->MinDPPCLKUsingSingleDPP[k]
										* (1.0 + mode_lib->vba.DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0) / 2.0;
					पूर्ण
					अगर (i != mode_lib->vba.soc.num_states) अणु
						mode_lib->vba.PlaneRequiredDISPCLK =
								mode_lib->vba.PixelClock[k]
										* (1.0 + mode_lib->vba.DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0)
										* (1.0 + mode_lib->vba.DISPCLKRampingMargin / 100.0);
					पूर्ण अन्यथा अणु
						mode_lib->vba.PlaneRequiredDISPCLK = mode_lib->vba.PixelClock[k]
							* (1.0 + mode_lib->vba.DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0);
					पूर्ण
					locals->RequiredDISPCLK[i][j] = dml_max(
							locals->RequiredDISPCLK[i][j],
							mode_lib->vba.PlaneRequiredDISPCLK);
					अगर (locals->MinDPPCLKUsingSingleDPP[k] / locals->NoOfDPP[i][j][k] * (1.0 + mode_lib->vba.DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0)
							> mode_lib->vba.MaxDppclkRoundedDownToDFSGranularity
							|| mode_lib->vba.PlaneRequiredDISPCLK > mode_lib->vba.MaxDispclkRoundedDownToDFSGranularity)
						locals->DISPCLK_DPPCLK_Support[i][j] = false;
				पूर्ण
				locals->TotalNumberOfActiveDPP[i][j] = 0.0;
				क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++)
					locals->TotalNumberOfActiveDPP[i][j] = locals->TotalNumberOfActiveDPP[i][j] + locals->NoOfDPP[i][j][k];
			पूर्ण
			locals->RequiredDISPCLK[i][j] = dml_max(
					locals->RequiredDISPCLK[i][j],
					mode_lib->vba.WritebackRequiredDISPCLK);
			अगर (mode_lib->vba.MaxDispclkRoundedDownToDFSGranularity
					< mode_lib->vba.WritebackRequiredDISPCLK) अणु
				locals->DISPCLK_DPPCLK_Support[i][j] = false;
			पूर्ण
		पूर्ण
	पूर्ण
	/*Viewport Size Check*/

	क्रम (i = 0; i <= mode_lib->vba.soc.num_states; i++) अणु
		locals->ViewportSizeSupport[i][0] = true;
		क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
			अगर (locals->ODMCombineEnablePerState[i][k] == dm_odm_combine_mode_2to1) अणु
				अगर (dml_min(locals->SwathWidthYSingleDPP[k], dml_round(mode_lib->vba.HActive[k] / 2.0 * mode_lib->vba.HRatio[k]))
						> locals->MaximumSwathWidth[k]) अणु
					locals->ViewportSizeSupport[i][0] = false;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (locals->SwathWidthYSingleDPP[k] / 2.0 > locals->MaximumSwathWidth[k]) अणु
					locals->ViewportSizeSupport[i][0] = false;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	/*Total Available Pipes Support Check*/

	क्रम (i = 0; i <= mode_lib->vba.soc.num_states; i++) अणु
		क्रम (j = 0; j < 2; j++) अणु
			अगर (locals->TotalNumberOfActiveDPP[i][j] <= mode_lib->vba.MaxNumDPP)
				locals->TotalAvailablePipesSupport[i][j] = true;
			अन्यथा
				locals->TotalAvailablePipesSupport[i][j] = false;
		पूर्ण
	पूर्ण
	/*Total Available OTG Support Check*/

	mode_lib->vba.TotalNumberOfActiveOTG = 0.0;
	क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
		अगर (mode_lib->vba.BlendingAndTiming[k] == k) अणु
			mode_lib->vba.TotalNumberOfActiveOTG = mode_lib->vba.TotalNumberOfActiveOTG
					+ 1.0;
		पूर्ण
	पूर्ण
	अगर (mode_lib->vba.TotalNumberOfActiveOTG <= mode_lib->vba.MaxNumOTG) अणु
		mode_lib->vba.NumberOfOTGSupport = true;
	पूर्ण अन्यथा अणु
		mode_lib->vba.NumberOfOTGSupport = false;
	पूर्ण
	/*Display IO and DSC Support Check*/

	mode_lib->vba.NonsupportedDSCInputBPC = false;
	क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
		अगर (!(mode_lib->vba.DSCInputBitPerComponent[k] == 12.0
				|| mode_lib->vba.DSCInputBitPerComponent[k] == 10.0
				|| mode_lib->vba.DSCInputBitPerComponent[k] == 8.0)) अणु
			mode_lib->vba.NonsupportedDSCInputBPC = true;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i <= mode_lib->vba.soc.num_states; i++) अणु
		क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
			locals->RequiresDSC[i][k] = false;
			locals->RequiresFEC[i][k] = 0;
			अगर (mode_lib->vba.BlendingAndTiming[k] == k) अणु
				अगर (mode_lib->vba.Output[k] == dm_hdmi) अणु
					locals->RequiresDSC[i][k] = false;
					locals->RequiresFEC[i][k] = 0;
					locals->OutputBppPerState[i][k] = TruncToValidBPP(
							dml_min(600.0, mode_lib->vba.PHYCLKPerState[i]) / mode_lib->vba.PixelClockBackEnd[k] * 24,
							mode_lib->vba.ForcedOutputLinkBPP[k],
							false,
							mode_lib->vba.Output[k],
							mode_lib->vba.OutputFormat[k],
							mode_lib->vba.DSCInputBitPerComponent[k]);
				पूर्ण अन्यथा अगर (mode_lib->vba.Output[k] == dm_dp
						|| mode_lib->vba.Output[k] == dm_edp) अणु
					अगर (mode_lib->vba.Output[k] == dm_edp) अणु
						mode_lib->vba.EffectiveFECOverhead = 0.0;
					पूर्ण अन्यथा अणु
						mode_lib->vba.EffectiveFECOverhead =
								mode_lib->vba.FECOverhead;
					पूर्ण
					अगर (mode_lib->vba.PHYCLKPerState[i] >= 270.0) अणु
						mode_lib->vba.Outbpp = TruncToValidBPP(
								(1.0 - mode_lib->vba.Downspपढ़ोing / 100.0) * 270.0
								* mode_lib->vba.OutputLinkDPLanes[k] / mode_lib->vba.PixelClockBackEnd[k] * 8.0,
								mode_lib->vba.ForcedOutputLinkBPP[k],
								false,
								mode_lib->vba.Output[k],
								mode_lib->vba.OutputFormat[k],
								mode_lib->vba.DSCInputBitPerComponent[k]);
						mode_lib->vba.OutbppDSC = TruncToValidBPP(
								(1.0 - mode_lib->vba.Downspपढ़ोing / 100.0) * (1.0 - mode_lib->vba.EffectiveFECOverhead / 100.0) * 270.0
								* mode_lib->vba.OutputLinkDPLanes[k] / mode_lib->vba.PixelClockBackEnd[k] * 8.0,
								mode_lib->vba.ForcedOutputLinkBPP[k],
								true,
								mode_lib->vba.Output[k],
								mode_lib->vba.OutputFormat[k],
								mode_lib->vba.DSCInputBitPerComponent[k]);
						अगर (mode_lib->vba.DSCEnabled[k] == true) अणु
							locals->RequiresDSC[i][k] = true;
							अगर (mode_lib->vba.Output[k] == dm_dp) अणु
								locals->RequiresFEC[i][k] = true;
							पूर्ण अन्यथा अणु
								locals->RequiresFEC[i][k] = false;
							पूर्ण
							mode_lib->vba.Outbpp = mode_lib->vba.OutbppDSC;
						पूर्ण अन्यथा अणु
							locals->RequiresDSC[i][k] = false;
							locals->RequiresFEC[i][k] = false;
						पूर्ण
						locals->OutputBppPerState[i][k] = mode_lib->vba.Outbpp;
					पूर्ण
					अगर (mode_lib->vba.Outbpp == BPP_INVALID && mode_lib->vba.PHYCLKPerState[i] >= 540.0) अणु
						mode_lib->vba.Outbpp = TruncToValidBPP(
								(1.0 - mode_lib->vba.Downspपढ़ोing / 100.0) * 540.0
								* mode_lib->vba.OutputLinkDPLanes[k] / mode_lib->vba.PixelClockBackEnd[k] * 8.0,
								mode_lib->vba.ForcedOutputLinkBPP[k],
									false,
									mode_lib->vba.Output[k],
									mode_lib->vba.OutputFormat[k],
									mode_lib->vba.DSCInputBitPerComponent[k]);
						mode_lib->vba.OutbppDSC = TruncToValidBPP(
								(1.0 - mode_lib->vba.Downspपढ़ोing / 100.0) * (1.0 - mode_lib->vba.EffectiveFECOverhead / 100.0) * 540.0
								* mode_lib->vba.OutputLinkDPLanes[k] / mode_lib->vba.PixelClockBackEnd[k] * 8.0,
								mode_lib->vba.ForcedOutputLinkBPP[k],
								true,
								mode_lib->vba.Output[k],
								mode_lib->vba.OutputFormat[k],
								mode_lib->vba.DSCInputBitPerComponent[k]);
						अगर (mode_lib->vba.DSCEnabled[k] == true) अणु
							locals->RequiresDSC[i][k] = true;
							अगर (mode_lib->vba.Output[k] == dm_dp) अणु
								locals->RequiresFEC[i][k] = true;
							पूर्ण अन्यथा अणु
								locals->RequiresFEC[i][k] = false;
							पूर्ण
							mode_lib->vba.Outbpp = mode_lib->vba.OutbppDSC;
						पूर्ण अन्यथा अणु
							locals->RequiresDSC[i][k] = false;
							locals->RequiresFEC[i][k] = false;
						पूर्ण
						locals->OutputBppPerState[i][k] = mode_lib->vba.Outbpp;
					पूर्ण
					अगर (mode_lib->vba.Outbpp == BPP_INVALID
							&& mode_lib->vba.PHYCLKPerState[i]
									>= 810.0) अणु
						mode_lib->vba.Outbpp = TruncToValidBPP(
								(1.0 - mode_lib->vba.Downspपढ़ोing / 100.0) * 810.0
								* mode_lib->vba.OutputLinkDPLanes[k] / mode_lib->vba.PixelClockBackEnd[k] * 8.0,
								mode_lib->vba.ForcedOutputLinkBPP[k],
								false,
								mode_lib->vba.Output[k],
								mode_lib->vba.OutputFormat[k],
								mode_lib->vba.DSCInputBitPerComponent[k]);
						mode_lib->vba.OutbppDSC = TruncToValidBPP(
								(1.0 - mode_lib->vba.Downspपढ़ोing / 100.0) * (1.0 - mode_lib->vba.EffectiveFECOverhead / 100.0) * 810.0
								* mode_lib->vba.OutputLinkDPLanes[k] / mode_lib->vba.PixelClockBackEnd[k] * 8.0,
								mode_lib->vba.ForcedOutputLinkBPP[k],
								true,
								mode_lib->vba.Output[k],
								mode_lib->vba.OutputFormat[k],
								mode_lib->vba.DSCInputBitPerComponent[k]);
						अगर (mode_lib->vba.DSCEnabled[k] == true || mode_lib->vba.Outbpp == BPP_INVALID) अणु
							locals->RequiresDSC[i][k] = true;
							अगर (mode_lib->vba.Output[k] == dm_dp) अणु
								locals->RequiresFEC[i][k] = true;
							पूर्ण अन्यथा अणु
								locals->RequiresFEC[i][k] = false;
							पूर्ण
							mode_lib->vba.Outbpp = mode_lib->vba.OutbppDSC;
						पूर्ण अन्यथा अणु
							locals->RequiresDSC[i][k] = false;
							locals->RequiresFEC[i][k] = false;
						पूर्ण
						locals->OutputBppPerState[i][k] =
								mode_lib->vba.Outbpp;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अणु
				locals->OutputBppPerState[i][k] = BPP_BLENDED_PIPE;
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (i = 0; i <= mode_lib->vba.soc.num_states; i++) अणु
		locals->DIOSupport[i] = true;
		क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
			अगर (!mode_lib->vba.skip_dio_check[k]
					&& (locals->OutputBppPerState[i][k] == BPP_INVALID
						|| (mode_lib->vba.OutputFormat[k] == dm_420
							&& mode_lib->vba.Interlace[k] == true
							&& mode_lib->vba.ProgressiveToInterlaceUnitInOPP == true))) अणु
				locals->DIOSupport[i] = false;
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (i = 0; i <= mode_lib->vba.soc.num_states; i++) अणु
		क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
			locals->DSCCLKRequiredMoreThanSupported[i] = false;
			अगर (mode_lib->vba.BlendingAndTiming[k] == k) अणु
				अगर ((mode_lib->vba.Output[k] == dm_dp
						|| mode_lib->vba.Output[k] == dm_edp)) अणु
					अगर (mode_lib->vba.OutputFormat[k] == dm_420
							|| mode_lib->vba.OutputFormat[k]
									== dm_n422) अणु
						mode_lib->vba.DSCFormatFactor = 2;
					पूर्ण अन्यथा अणु
						mode_lib->vba.DSCFormatFactor = 1;
					पूर्ण
					अगर (locals->RequiresDSC[i][k] == true) अणु
						अगर (locals->ODMCombineEnablePerState[i][k] == dm_odm_combine_mode_2to1) अणु
							अगर (mode_lib->vba.PixelClockBackEnd[k] / 6.0 / mode_lib->vba.DSCFormatFactor
									> (1.0 - mode_lib->vba.DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0) * mode_lib->vba.MaxDSCCLK[i]) अणु
								locals->DSCCLKRequiredMoreThanSupported[i] =
										true;
							पूर्ण
						पूर्ण अन्यथा अणु
							अगर (mode_lib->vba.PixelClockBackEnd[k] / 3.0 / mode_lib->vba.DSCFormatFactor
									> (1.0 - mode_lib->vba.DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0) * mode_lib->vba.MaxDSCCLK[i]) अणु
								locals->DSCCLKRequiredMoreThanSupported[i] =
										true;
							पूर्ण
						पूर्ण
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (i = 0; i <= mode_lib->vba.soc.num_states; i++) अणु
		locals->NotEnoughDSCUnits[i] = false;
		mode_lib->vba.TotalDSCUnitsRequired = 0.0;
		क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
			अगर (locals->RequiresDSC[i][k] == true) अणु
				अगर (locals->ODMCombineEnablePerState[i][k] == dm_odm_combine_mode_2to1) अणु
					mode_lib->vba.TotalDSCUnitsRequired =
							mode_lib->vba.TotalDSCUnitsRequired + 2.0;
				पूर्ण अन्यथा अणु
					mode_lib->vba.TotalDSCUnitsRequired =
							mode_lib->vba.TotalDSCUnitsRequired + 1.0;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (mode_lib->vba.TotalDSCUnitsRequired > mode_lib->vba.NumberOfDSC) अणु
			locals->NotEnoughDSCUnits[i] = true;
		पूर्ण
	पूर्ण
	/*DSC Delay per state*/

	क्रम (i = 0; i <= mode_lib->vba.soc.num_states; i++) अणु
		क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
			अगर (mode_lib->vba.BlendingAndTiming[k] != k) अणु
				mode_lib->vba.slices = 0;
			पूर्ण अन्यथा अगर (locals->RequiresDSC[i][k] == 0
					|| locals->RequiresDSC[i][k] == false) अणु
				mode_lib->vba.slices = 0;
			पूर्ण अन्यथा अगर (mode_lib->vba.PixelClockBackEnd[k] > 3200.0) अणु
				mode_lib->vba.slices = dml_उच्चमान(
						mode_lib->vba.PixelClockBackEnd[k] / 400.0,
						4.0);
			पूर्ण अन्यथा अगर (mode_lib->vba.PixelClockBackEnd[k] > 1360.0) अणु
				mode_lib->vba.slices = 8.0;
			पूर्ण अन्यथा अगर (mode_lib->vba.PixelClockBackEnd[k] > 680.0) अणु
				mode_lib->vba.slices = 4.0;
			पूर्ण अन्यथा अगर (mode_lib->vba.PixelClockBackEnd[k] > 340.0) अणु
				mode_lib->vba.slices = 2.0;
			पूर्ण अन्यथा अणु
				mode_lib->vba.slices = 1.0;
			पूर्ण
			अगर (locals->OutputBppPerState[i][k] == BPP_BLENDED_PIPE
					|| locals->OutputBppPerState[i][k] == BPP_INVALID) अणु
				mode_lib->vba.bpp = 0.0;
			पूर्ण अन्यथा अणु
				mode_lib->vba.bpp = locals->OutputBppPerState[i][k];
			पूर्ण
			अगर (locals->RequiresDSC[i][k] == true && mode_lib->vba.bpp != 0.0) अणु
				अगर (locals->ODMCombineEnablePerState[i][k] == dm_odm_combine_mode_disabled) अणु
					locals->DSCDelayPerState[i][k] =
							dscceComputeDelay(
									mode_lib->vba.DSCInputBitPerComponent[k],
									mode_lib->vba.bpp,
									dml_उच्चमान(
											mode_lib->vba.HActive[k]
													/ mode_lib->vba.slices,
											1.0),
									mode_lib->vba.slices,
									mode_lib->vba.OutputFormat[k])
									+ dscComputeDelay(
											mode_lib->vba.OutputFormat[k]);
				पूर्ण अन्यथा अणु
					locals->DSCDelayPerState[i][k] =
							2.0 * (dscceComputeDelay(
											mode_lib->vba.DSCInputBitPerComponent[k],
											mode_lib->vba.bpp,
											dml_उच्चमान(mode_lib->vba.HActive[k] / mode_lib->vba.slices, 1.0),
											mode_lib->vba.slices / 2,
											mode_lib->vba.OutputFormat[k])
									+ dscComputeDelay(mode_lib->vba.OutputFormat[k]));
				पूर्ण
				locals->DSCDelayPerState[i][k] =
						locals->DSCDelayPerState[i][k] * mode_lib->vba.PixelClock[k] / mode_lib->vba.PixelClockBackEnd[k];
			पूर्ण अन्यथा अणु
				locals->DSCDelayPerState[i][k] = 0.0;
			पूर्ण
		पूर्ण
		क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
			क्रम (m = 0; m <= mode_lib->vba.NumberOfActivePlanes - 1; m++) अणु
				क्रम (j = 0; j <= mode_lib->vba.NumberOfActivePlanes - 1; j++) अणु
					अगर (mode_lib->vba.BlendingAndTiming[k] == m && locals->RequiresDSC[i][m] == true)
						locals->DSCDelayPerState[i][k] = locals->DSCDelayPerState[i][m];
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	//Prefetch Check
	क्रम (i = 0; i <= mode_lib->vba.soc.num_states; ++i) अणु
		क्रम (j = 0; j <= 1; ++j) अणु
			locals->TotalNumberOfDCCActiveDPP[i][j] = 0;
			क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
				अगर (mode_lib->vba.DCCEnable[k] == true)
					locals->TotalNumberOfDCCActiveDPP[i][j] = locals->TotalNumberOfDCCActiveDPP[i][j] + locals->NoOfDPP[i][j][k];
			पूर्ण
		पूर्ण
	पूर्ण

	mode_lib->vba.UrgentLatency = dml_max3(
			mode_lib->vba.UrgentLatencyPixelDataOnly,
			mode_lib->vba.UrgentLatencyPixelMixedWithVMData,
			mode_lib->vba.UrgentLatencyVMDataOnly);
	mode_lib->vba.PrefetchERROR = CalculateMinAndMaxPrefetchMode(
			mode_lib->vba.AllowDRAMSelfRefreshOrDRAMClockChangeInVblank,
			&mode_lib->vba.MinPrefetchMode,
			&mode_lib->vba.MaxPrefetchMode);

	क्रम (i = 0; i <= mode_lib->vba.soc.num_states; i++) अणु
		क्रम (j = 0; j < 2; j++) अणु
			क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
				locals->RequiredDPPCLKThisState[k] = locals->RequiredDPPCLK[i][j][k];
				locals->NoOfDPPThisState[k]        = locals->NoOfDPP[i][j][k];
				अगर (locals->ODMCombineEnablePerState[i][k] == dm_odm_combine_mode_2to1) अणु
					locals->SwathWidthYThisState[k] =
						dml_min(locals->SwathWidthYSingleDPP[k], dml_round(mode_lib->vba.HActive[k] / 2.0 * mode_lib->vba.HRatio[k]));
				पूर्ण अन्यथा अणु
					locals->SwathWidthYThisState[k] = locals->SwathWidthYSingleDPP[k] / locals->NoOfDPP[i][j][k];
				पूर्ण
				mode_lib->vba.SwathWidthGranularityY = 256.0
					/ dml_उच्चमान(locals->BytePerPixelInDETY[k], 1.0)
					/ locals->MaxSwathHeightY[k];
				mode_lib->vba.RoundedUpMaxSwathSizeBytesY =
					(dml_उच्चमान(locals->SwathWidthYThisState[k] - 1.0, mode_lib->vba.SwathWidthGranularityY)
					+ mode_lib->vba.SwathWidthGranularityY) * locals->BytePerPixelInDETY[k] * locals->MaxSwathHeightY[k];
				अगर (mode_lib->vba.SourcePixelFormat[k] == dm_420_10) अणु
					mode_lib->vba.RoundedUpMaxSwathSizeBytesY = dml_उच्चमान(
							mode_lib->vba.RoundedUpMaxSwathSizeBytesY,
							256.0) + 256;
				पूर्ण
				अगर (locals->MaxSwathHeightC[k] > 0.0) अणु
					mode_lib->vba.SwathWidthGranularityC = 256.0 / dml_उच्चमान(locals->BytePerPixelInDETC[k], 2.0) / locals->MaxSwathHeightC[k];
					mode_lib->vba.RoundedUpMaxSwathSizeBytesC = (dml_उच्चमान(locals->SwathWidthYThisState[k] / 2.0 - 1.0, mode_lib->vba.SwathWidthGranularityC)
							+ mode_lib->vba.SwathWidthGranularityC) * locals->BytePerPixelInDETC[k] * locals->MaxSwathHeightC[k];
					अगर (mode_lib->vba.SourcePixelFormat[k] == dm_420_10) अणु
						mode_lib->vba.RoundedUpMaxSwathSizeBytesC = dml_उच्चमान(mode_lib->vba.RoundedUpMaxSwathSizeBytesC, 256.0) + 256;
					पूर्ण
				पूर्ण अन्यथा अणु
					mode_lib->vba.RoundedUpMaxSwathSizeBytesC = 0.0;
				पूर्ण
				अगर (mode_lib->vba.RoundedUpMaxSwathSizeBytesY + mode_lib->vba.RoundedUpMaxSwathSizeBytesC
						<= mode_lib->vba.DETBufferSizeInKByte * 1024.0 / 2.0) अणु
					locals->SwathHeightYThisState[k] = locals->MaxSwathHeightY[k];
					locals->SwathHeightCThisState[k] = locals->MaxSwathHeightC[k];
				पूर्ण अन्यथा अणु
					locals->SwathHeightYThisState[k] =
							locals->MinSwathHeightY[k];
					locals->SwathHeightCThisState[k] =
							locals->MinSwathHeightC[k];
				पूर्ण
			पूर्ण

			CalculateDCFCLKDeepSleep(
					mode_lib,
					mode_lib->vba.NumberOfActivePlanes,
					locals->BytePerPixelInDETY,
					locals->BytePerPixelInDETC,
					mode_lib->vba.VRatio,
					locals->SwathWidthYThisState,
					locals->NoOfDPPThisState,
					mode_lib->vba.HRatio,
					mode_lib->vba.PixelClock,
					locals->PSCL_FACTOR,
					locals->PSCL_FACTOR_CHROMA,
					locals->RequiredDPPCLKThisState,
					&mode_lib->vba.ProjectedDCFCLKDeepSleep[0][0]);

			क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
				अगर ((mode_lib->vba.SourcePixelFormat[k] != dm_444_64
						&& mode_lib->vba.SourcePixelFormat[k] != dm_444_32
						&& mode_lib->vba.SourcePixelFormat[k] != dm_444_16
						&& mode_lib->vba.SourcePixelFormat[k] != dm_mono_16
						&& mode_lib->vba.SourcePixelFormat[k] != dm_mono_8)) अणु
					mode_lib->vba.PDEAndMetaPTEBytesPerFrameC = CalculateVMAndRowBytes(
							mode_lib,
							mode_lib->vba.DCCEnable[k],
							locals->Read256BlockHeightC[k],
							locals->Read256BlockWidthC[k],
							mode_lib->vba.SourcePixelFormat[k],
							mode_lib->vba.SurfaceTiling[k],
							dml_उच्चमान(locals->BytePerPixelInDETC[k], 2.0),
							mode_lib->vba.SourceScan[k],
							mode_lib->vba.ViewportWidth[k] / 2.0,
							mode_lib->vba.ViewportHeight[k] / 2.0,
							locals->SwathWidthYThisState[k] / 2.0,
							mode_lib->vba.GPUVMEnable,
							mode_lib->vba.HostVMEnable,
							mode_lib->vba.HostVMMaxPageTableLevels,
							mode_lib->vba.HostVMCachedPageTableLevels,
							mode_lib->vba.VMMPageSize,
							mode_lib->vba.PTEBufferSizeInRequestsChroma,
							mode_lib->vba.PitchC[k],
							0.0,
							&locals->MacroTileWidthC[k],
							&mode_lib->vba.MetaRowBytesC,
							&mode_lib->vba.DPTEBytesPerRowC,
							&locals->PTEBufferSizeNotExceededC[i][j][k],
							locals->dpte_row_width_chroma_ub,
							&locals->dpte_row_height_chroma[k],
							&locals->meta_req_width_chroma[k],
							&locals->meta_req_height_chroma[k],
							&locals->meta_row_width_chroma[k],
							&locals->meta_row_height_chroma[k],
							&locals->vm_group_bytes_chroma,
							&locals->dpte_group_bytes_chroma,
							locals->PixelPTEReqWidthC,
							locals->PixelPTEReqHeightC,
							locals->PTERequestSizeC,
							locals->dpde0_bytes_per_frame_ub_c,
							locals->meta_pte_bytes_per_frame_ub_c);
					locals->PrefetchLinesC[0][0][k] = CalculatePrefetchSourceLines(
							mode_lib,
							mode_lib->vba.VRatio[k]/2,
							mode_lib->vba.VTAPsChroma[k],
							mode_lib->vba.Interlace[k],
							mode_lib->vba.ProgressiveToInterlaceUnitInOPP,
							locals->SwathHeightCThisState[k],
							mode_lib->vba.ViewportYStartC[k],
							&locals->PrefillC[k],
							&locals->MaxNumSwC[k]);
					locals->PTEBufferSizeInRequestsForLuma = mode_lib->vba.PTEBufferSizeInRequestsLuma;
				पूर्ण अन्यथा अणु
					mode_lib->vba.PDEAndMetaPTEBytesPerFrameC = 0.0;
					mode_lib->vba.MetaRowBytesC = 0.0;
					mode_lib->vba.DPTEBytesPerRowC = 0.0;
					locals->PrefetchLinesC[0][0][k] = 0.0;
					locals->PTEBufferSizeNotExceededC[i][j][k] = true;
					locals->PTEBufferSizeInRequestsForLuma = mode_lib->vba.PTEBufferSizeInRequestsLuma + mode_lib->vba.PTEBufferSizeInRequestsChroma;
				पूर्ण
				mode_lib->vba.PDEAndMetaPTEBytesPerFrameY = CalculateVMAndRowBytes(
						mode_lib,
						mode_lib->vba.DCCEnable[k],
						locals->Read256BlockHeightY[k],
						locals->Read256BlockWidthY[k],
						mode_lib->vba.SourcePixelFormat[k],
						mode_lib->vba.SurfaceTiling[k],
						dml_उच्चमान(locals->BytePerPixelInDETY[k], 1.0),
						mode_lib->vba.SourceScan[k],
						mode_lib->vba.ViewportWidth[k],
						mode_lib->vba.ViewportHeight[k],
						locals->SwathWidthYThisState[k],
						mode_lib->vba.GPUVMEnable,
						mode_lib->vba.HostVMEnable,
						mode_lib->vba.HostVMMaxPageTableLevels,
						mode_lib->vba.HostVMCachedPageTableLevels,
						mode_lib->vba.VMMPageSize,
						locals->PTEBufferSizeInRequestsForLuma,
						mode_lib->vba.PitchY[k],
						mode_lib->vba.DCCMetaPitchY[k],
						&locals->MacroTileWidthY[k],
						&mode_lib->vba.MetaRowBytesY,
						&mode_lib->vba.DPTEBytesPerRowY,
						&locals->PTEBufferSizeNotExceededY[i][j][k],
						locals->dpte_row_width_luma_ub,
						&locals->dpte_row_height[k],
						&locals->meta_req_width[k],
						&locals->meta_req_height[k],
						&locals->meta_row_width[k],
						&locals->meta_row_height[k],
						&locals->vm_group_bytes[k],
						&locals->dpte_group_bytes[k],
						locals->PixelPTEReqWidthY,
						locals->PixelPTEReqHeightY,
						locals->PTERequestSizeY,
						locals->dpde0_bytes_per_frame_ub_l,
						locals->meta_pte_bytes_per_frame_ub_l);
				locals->PrefetchLinesY[0][0][k] = CalculatePrefetchSourceLines(
						mode_lib,
						mode_lib->vba.VRatio[k],
						mode_lib->vba.vtaps[k],
						mode_lib->vba.Interlace[k],
						mode_lib->vba.ProgressiveToInterlaceUnitInOPP,
						locals->SwathHeightYThisState[k],
						mode_lib->vba.ViewportYStartY[k],
						&locals->PrefillY[k],
						&locals->MaxNumSwY[k]);
				locals->PDEAndMetaPTEBytesPerFrame[0][0][k] =
						mode_lib->vba.PDEAndMetaPTEBytesPerFrameY + mode_lib->vba.PDEAndMetaPTEBytesPerFrameC;
				locals->MetaRowBytes[0][0][k] = mode_lib->vba.MetaRowBytesY + mode_lib->vba.MetaRowBytesC;
				locals->DPTEBytesPerRow[0][0][k] = mode_lib->vba.DPTEBytesPerRowY + mode_lib->vba.DPTEBytesPerRowC;

				CalculateActiveRowBandwidth(
						mode_lib->vba.GPUVMEnable,
						mode_lib->vba.SourcePixelFormat[k],
						mode_lib->vba.VRatio[k],
						mode_lib->vba.DCCEnable[k],
						mode_lib->vba.HTotal[k] /
						mode_lib->vba.PixelClock[k],
						mode_lib->vba.MetaRowBytesY,
						mode_lib->vba.MetaRowBytesC,
						locals->meta_row_height[k],
						locals->meta_row_height_chroma[k],
						mode_lib->vba.DPTEBytesPerRowY,
						mode_lib->vba.DPTEBytesPerRowC,
						locals->dpte_row_height[k],
						locals->dpte_row_height_chroma[k],
						&locals->meta_row_bw[k],
						&locals->dpte_row_bw[k]);
			पूर्ण
			mode_lib->vba.ExtraLatency = CalculateExtraLatency(
					locals->UrgentRoundTripAndOutOfOrderLatencyPerState[i],
					locals->TotalNumberOfActiveDPP[i][j],
					mode_lib->vba.PixelChunkSizeInKByte,
					locals->TotalNumberOfDCCActiveDPP[i][j],
					mode_lib->vba.MetaChunkSize,
					locals->ReturnBWPerState[i][0],
					mode_lib->vba.GPUVMEnable,
					mode_lib->vba.HostVMEnable,
					mode_lib->vba.NumberOfActivePlanes,
					locals->NoOfDPPThisState,
					locals->dpte_group_bytes,
					mode_lib->vba.PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData,
					mode_lib->vba.PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly,
					mode_lib->vba.HostVMMaxPageTableLevels,
					mode_lib->vba.HostVMCachedPageTableLevels);

			mode_lib->vba.TimeCalc = 24.0 / mode_lib->vba.ProjectedDCFCLKDeepSleep[0][0];
			क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
				अगर (mode_lib->vba.BlendingAndTiming[k] == k) अणु
					अगर (mode_lib->vba.WritebackEnable[k] == true) अणु
						locals->WritebackDelay[i][k] = mode_lib->vba.WritebackLatency
								+ CalculateWriteBackDelay(
										mode_lib->vba.WritebackPixelFormat[k],
										mode_lib->vba.WritebackHRatio[k],
										mode_lib->vba.WritebackVRatio[k],
										mode_lib->vba.WritebackLumaHTaps[k],
										mode_lib->vba.WritebackLumaVTaps[k],
										mode_lib->vba.WritebackChromaHTaps[k],
										mode_lib->vba.WritebackChromaVTaps[k],
										mode_lib->vba.WritebackDestinationWidth[k]) / locals->RequiredDISPCLK[i][j];
					पूर्ण अन्यथा अणु
						locals->WritebackDelay[i][k] = 0.0;
					पूर्ण
					क्रम (m = 0; m <= mode_lib->vba.NumberOfActivePlanes - 1; m++) अणु
						अगर (mode_lib->vba.BlendingAndTiming[m] == k
								&& mode_lib->vba.WritebackEnable[m]
										== true) अणु
							locals->WritebackDelay[i][k] = dml_max(locals->WritebackDelay[i][k],
											mode_lib->vba.WritebackLatency + CalculateWriteBackDelay(
													mode_lib->vba.WritebackPixelFormat[m],
													mode_lib->vba.WritebackHRatio[m],
													mode_lib->vba.WritebackVRatio[m],
													mode_lib->vba.WritebackLumaHTaps[m],
													mode_lib->vba.WritebackLumaVTaps[m],
													mode_lib->vba.WritebackChromaHTaps[m],
													mode_lib->vba.WritebackChromaVTaps[m],
													mode_lib->vba.WritebackDestinationWidth[m]) / locals->RequiredDISPCLK[i][j]);
						पूर्ण
					पूर्ण
				पूर्ण
			पूर्ण
			क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
				क्रम (m = 0; m <= mode_lib->vba.NumberOfActivePlanes - 1; m++) अणु
					अगर (mode_lib->vba.BlendingAndTiming[k] == m) अणु
						locals->WritebackDelay[i][k] = locals->WritebackDelay[i][m];
					पूर्ण
				पूर्ण
			पूर्ण
			mode_lib->vba.MaxMaxVStartup[0][0] = 0;
			क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
				locals->MaximumVStartup[0][0][k] = mode_lib->vba.VTotal[k] - mode_lib->vba.VActive[k]
					- dml_max(1.0, dml_उच्चमान(locals->WritebackDelay[i][k] / (mode_lib->vba.HTotal[k] / mode_lib->vba.PixelClock[k]), 1.0));
				mode_lib->vba.MaxMaxVStartup[0][0] = dml_max(mode_lib->vba.MaxMaxVStartup[0][0], locals->MaximumVStartup[0][0][k]);
			पूर्ण

			mode_lib->vba.NextPrefetchMode = mode_lib->vba.MinPrefetchMode;
			mode_lib->vba.NextMaxVStartup = mode_lib->vba.MaxMaxVStartup[0][0];
			करो अणु
				mode_lib->vba.PrefetchMode[i][j] = mode_lib->vba.NextPrefetchMode;
				mode_lib->vba.MaxVStartup = mode_lib->vba.NextMaxVStartup;

				mode_lib->vba.TWait = CalculateTWait(
						mode_lib->vba.PrefetchMode[i][j],
						mode_lib->vba.DRAMClockChangeLatency,
						mode_lib->vba.UrgentLatency,
						mode_lib->vba.SREnterPlusExitTime);
				क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
					Pipe myPipe;
					HostVM myHostVM;

					अगर (mode_lib->vba.XFCEnabled[k] == true) अणु
						mode_lib->vba.XFCRemoteSurfaceFlipDelay =
								CalculateRemoteSurfaceFlipDelay(
										mode_lib,
										mode_lib->vba.VRatio[k],
										locals->SwathWidthYThisState[k],
										dml_उच्चमान(locals->BytePerPixelInDETY[k], 1.0),
										mode_lib->vba.HTotal[k] / mode_lib->vba.PixelClock[k],
										mode_lib->vba.XFCTSlvVupdateOffset,
										mode_lib->vba.XFCTSlvVupdateWidth,
										mode_lib->vba.XFCTSlvVपढ़ोyOffset,
										mode_lib->vba.XFCXBUFLatencyTolerance,
										mode_lib->vba.XFCFillBWOverhead,
										mode_lib->vba.XFCSlvChunkSize,
										mode_lib->vba.XFCBusTransportTime,
										mode_lib->vba.TimeCalc,
										mode_lib->vba.TWait,
										&mode_lib->vba.SrcActiveDrainRate,
										&mode_lib->vba.TInitXFill,
										&mode_lib->vba.TslvChk);
					पूर्ण अन्यथा अणु
						mode_lib->vba.XFCRemoteSurfaceFlipDelay = 0.0;
					पूर्ण

					myPipe.DPPCLK = locals->RequiredDPPCLK[i][j][k];
					myPipe.DISPCLK = locals->RequiredDISPCLK[i][j];
					myPipe.PixelClock = mode_lib->vba.PixelClock[k];
					myPipe.DCFCLKDeepSleep = mode_lib->vba.ProjectedDCFCLKDeepSleep[0][0];
					myPipe.DPPPerPlane = locals->NoOfDPP[i][j][k];
					myPipe.ScalerEnabled = mode_lib->vba.ScalerEnabled[k];
					myPipe.SourceScan = mode_lib->vba.SourceScan[k];
					myPipe.BlockWidth256BytesY = locals->Read256BlockWidthY[k];
					myPipe.BlockHeight256BytesY = locals->Read256BlockHeightY[k];
					myPipe.BlockWidth256BytesC = locals->Read256BlockWidthC[k];
					myPipe.BlockHeight256BytesC = locals->Read256BlockHeightC[k];
					myPipe.InterlaceEnable = mode_lib->vba.Interlace[k];
					myPipe.NumberOfCursors = mode_lib->vba.NumberOfCursors[k];
					myPipe.VBlank = mode_lib->vba.VTotal[k] - mode_lib->vba.VActive[k];
					myPipe.HTotal = mode_lib->vba.HTotal[k];


					myHostVM.Enable = mode_lib->vba.HostVMEnable;
					myHostVM.MaxPageTableLevels = mode_lib->vba.HostVMMaxPageTableLevels;
					myHostVM.CachedPageTableLevels = mode_lib->vba.HostVMCachedPageTableLevels;


					mode_lib->vba.IsErrorResult[i][j][k] = CalculatePrefetchSchedule(
							mode_lib,
							mode_lib->vba.PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData,
							mode_lib->vba.PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly,
							&myPipe,
							locals->DSCDelayPerState[i][k],
							mode_lib->vba.DPPCLKDelaySubtotal,
							mode_lib->vba.DPPCLKDelaySCL,
							mode_lib->vba.DPPCLKDelaySCLLBOnly,
							mode_lib->vba.DPPCLKDelayCNVCFormater,
							mode_lib->vba.DPPCLKDelayCNVCCursor,
							mode_lib->vba.DISPCLKDelaySubtotal,
							locals->SwathWidthYThisState[k] / mode_lib->vba.HRatio[k],
							mode_lib->vba.OutputFormat[k],
							mode_lib->vba.MaxInterDCNTileRepeaters,
							dml_min(mode_lib->vba.MaxVStartup, locals->MaximumVStartup[0][0][k]),
							locals->MaximumVStartup[0][0][k],
							mode_lib->vba.GPUVMMaxPageTableLevels,
							mode_lib->vba.GPUVMEnable,
							&myHostVM,
							mode_lib->vba.DynamicMetadataEnable[k],
							mode_lib->vba.DynamicMetadataLinesBeक्रमeActiveRequired[k],
							mode_lib->vba.DynamicMetadataTransmittedBytes[k],
							mode_lib->vba.DCCEnable[k],
							mode_lib->vba.UrgentLatency,
							mode_lib->vba.ExtraLatency,
							mode_lib->vba.TimeCalc,
							locals->PDEAndMetaPTEBytesPerFrame[0][0][k],
							locals->MetaRowBytes[0][0][k],
							locals->DPTEBytesPerRow[0][0][k],
							locals->PrefetchLinesY[0][0][k],
							locals->SwathWidthYThisState[k],
							locals->BytePerPixelInDETY[k],
							locals->PrefillY[k],
							locals->MaxNumSwY[k],
							locals->PrefetchLinesC[0][0][k],
							locals->BytePerPixelInDETC[k],
							locals->PrefillC[k],
							locals->MaxNumSwC[k],
							locals->SwathHeightYThisState[k],
							locals->SwathHeightCThisState[k],
							mode_lib->vba.TWait,
							mode_lib->vba.XFCEnabled[k],
							mode_lib->vba.XFCRemoteSurfaceFlipDelay,
							mode_lib->vba.ProgressiveToInterlaceUnitInOPP,
							&locals->dst_x_after_scaler,
							&locals->dst_y_after_scaler,
							&locals->LineTimesForPrefetch[k],
							&locals->PrefetchBW[k],
							&locals->LinesForMetaPTE[k],
							&locals->LinesForMetaAndDPTERow[k],
							&locals->VRatioPreY[i][j][k],
							&locals->VRatioPreC[i][j][k],
							&locals->RequiredPrefetchPixelDataBWLuma[i][j][k],
							&locals->RequiredPrefetchPixelDataBWChroma[i][j][k],
							&locals->VStartupRequiredWhenNotEnoughTimeForDynamicMetadata,
							&locals->Tno_bw[k],
							&locals->prefetch_vmrow_bw[k],
							locals->swath_width_luma_ub,
							locals->swath_width_chroma_ub,
							&mode_lib->vba.VUpdateOffsetPix[k],
							&mode_lib->vba.VUpdateWidthPix[k],
							&mode_lib->vba.VReadyOffsetPix[k]);
				पूर्ण
				mode_lib->vba.MaximumReadBandwidthWithoutPrefetch = 0.0;
				mode_lib->vba.MaximumReadBandwidthWithPrefetch = 0.0;
				क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
					अचिन्हित पूर्णांक m;

					locals->cursor_bw[k] = 0;
					locals->cursor_bw_pre[k] = 0;
					क्रम (m = 0; m < mode_lib->vba.NumberOfCursors[k]; m++) अणु
						locals->cursor_bw[k] = mode_lib->vba.CursorWidth[k][m] * mode_lib->vba.CursorBPP[k][m]
							/ 8.0 / (mode_lib->vba.HTotal[k] / mode_lib->vba.PixelClock[k]) * mode_lib->vba.VRatio[k];
						locals->cursor_bw_pre[k] = mode_lib->vba.CursorWidth[k][m] * mode_lib->vba.CursorBPP[k][m]
							/ 8.0 / (mode_lib->vba.HTotal[k] / mode_lib->vba.PixelClock[k]) * locals->VRatioPreY[i][j][k];
					पूर्ण

					CalculateUrgentBurstFactor(
							mode_lib->vba.DETBufferSizeInKByte,
							locals->SwathHeightYThisState[k],
							locals->SwathHeightCThisState[k],
							locals->SwathWidthYThisState[k],
							mode_lib->vba.HTotal[k] / mode_lib->vba.PixelClock[k],
							mode_lib->vba.UrgentLatency,
							mode_lib->vba.CursorBufferSize,
							mode_lib->vba.CursorWidth[k][0] + mode_lib->vba.CursorWidth[k][1],
							dml_max(mode_lib->vba.CursorBPP[k][0], mode_lib->vba.CursorBPP[k][1]),
							mode_lib->vba.VRatio[k],
							locals->VRatioPreY[i][j][k],
							locals->VRatioPreC[i][j][k],
							locals->BytePerPixelInDETY[k],
							locals->BytePerPixelInDETC[k],
							&locals->UrgentBurstFactorCursor[k],
							&locals->UrgentBurstFactorCursorPre[k],
							&locals->UrgentBurstFactorLuma[k],
							&locals->UrgentBurstFactorLumaPre[k],
							&locals->UrgentBurstFactorChroma[k],
							&locals->UrgentBurstFactorChromaPre[k],
							&locals->NotEnoughUrgentLatencyHiding,
							&locals->NotEnoughUrgentLatencyHidingPre);

					अगर (mode_lib->vba.UseUrgentBurstBandwidth == false) अणु
						locals->UrgentBurstFactorCursor[k] = 1;
						locals->UrgentBurstFactorCursorPre[k] = 1;
						locals->UrgentBurstFactorLuma[k] = 1;
						locals->UrgentBurstFactorLumaPre[k] = 1;
						locals->UrgentBurstFactorChroma[k] = 1;
						locals->UrgentBurstFactorChromaPre[k] = 1;
					पूर्ण

					mode_lib->vba.MaximumReadBandwidthWithoutPrefetch = mode_lib->vba.MaximumReadBandwidthWithoutPrefetch
						+ locals->cursor_bw[k] * locals->UrgentBurstFactorCursor[k] + locals->ReadBandwidthLuma[k]
						* locals->UrgentBurstFactorLuma[k] + locals->ReadBandwidthChroma[k]
						* locals->UrgentBurstFactorChroma[k] + locals->meta_row_bw[k] + locals->dpte_row_bw[k];
					mode_lib->vba.MaximumReadBandwidthWithPrefetch = mode_lib->vba.MaximumReadBandwidthWithPrefetch
						+ dml_max3(locals->prefetch_vmrow_bw[k],
						locals->ReadBandwidthLuma[k] * locals->UrgentBurstFactorLuma[k] + locals->ReadBandwidthChroma[k]
						* locals->UrgentBurstFactorChroma[k] + locals->cursor_bw[k] * locals->UrgentBurstFactorCursor[k]
						+ locals->meta_row_bw[k] + locals->dpte_row_bw[k],
						locals->RequiredPrefetchPixelDataBWLuma[i][j][k] * locals->UrgentBurstFactorLumaPre[k]
						+ locals->RequiredPrefetchPixelDataBWChroma[i][j][k] * locals->UrgentBurstFactorChromaPre[k]
						+ locals->cursor_bw_pre[k] * locals->UrgentBurstFactorCursorPre[k]);
				पूर्ण
				locals->BandwidthWithoutPrefetchSupported[i][0] = true;
				अगर (mode_lib->vba.MaximumReadBandwidthWithoutPrefetch > locals->ReturnBWPerState[i][0]
						|| locals->NotEnoughUrgentLatencyHiding == 1) अणु
					locals->BandwidthWithoutPrefetchSupported[i][0] = false;
				पूर्ण

				locals->PrefetchSupported[i][j] = true;
				अगर (mode_lib->vba.MaximumReadBandwidthWithPrefetch > locals->ReturnBWPerState[i][0]
						|| locals->NotEnoughUrgentLatencyHiding == 1
						|| locals->NotEnoughUrgentLatencyHidingPre == 1) अणु
					locals->PrefetchSupported[i][j] = false;
				पूर्ण
				क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
					अगर (locals->LineTimesForPrefetch[k] < 2.0
							|| locals->LinesForMetaPTE[k] >= 32.0
							|| locals->LinesForMetaAndDPTERow[k] >= 16.0
							|| mode_lib->vba.IsErrorResult[i][j][k] == true) अणु
						locals->PrefetchSupported[i][j] = false;
					पूर्ण
				पूर्ण
				locals->VRatioInPrefetchSupported[i][j] = true;
				क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
					अगर (locals->VRatioPreY[i][j][k] > 4.0
							|| locals->VRatioPreC[i][j][k] > 4.0
							|| mode_lib->vba.IsErrorResult[i][j][k] == true) अणु
						locals->VRatioInPrefetchSupported[i][j] = false;
					पूर्ण
				पूर्ण
				mode_lib->vba.AnyLinesForVMOrRowTooLarge = false;
				क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
					अगर (locals->LinesForMetaAndDPTERow[k] >= 16 || locals->LinesForMetaPTE[k] >= 32) अणु
						mode_lib->vba.AnyLinesForVMOrRowTooLarge = true;
					पूर्ण
				पूर्ण

				अगर (mode_lib->vba.MaxVStartup <= 13 || mode_lib->vba.AnyLinesForVMOrRowTooLarge == false) अणु
					mode_lib->vba.NextMaxVStartup = mode_lib->vba.MaxMaxVStartup[0][0];
					mode_lib->vba.NextPrefetchMode = mode_lib->vba.NextPrefetchMode + 1;
				पूर्ण अन्यथा अणु
					mode_lib->vba.NextMaxVStartup = mode_lib->vba.NextMaxVStartup - 1;
				पूर्ण
			पूर्ण जबतक ((locals->PrefetchSupported[i][j] != true || locals->VRatioInPrefetchSupported[i][j] != true)
					&& (mode_lib->vba.NextMaxVStartup != mode_lib->vba.MaxMaxVStartup[0][0]
						|| mode_lib->vba.NextPrefetchMode < mode_lib->vba.MaxPrefetchMode));

			अगर (locals->PrefetchSupported[i][j] == true && locals->VRatioInPrefetchSupported[i][j] == true) अणु
				mode_lib->vba.BandwidthAvailableForImmediateFlip = locals->ReturnBWPerState[i][0];
				क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
					mode_lib->vba.BandwidthAvailableForImmediateFlip = mode_lib->vba.BandwidthAvailableForImmediateFlip
						- dml_max(locals->ReadBandwidthLuma[k] * locals->UrgentBurstFactorLuma[k]
							+ locals->ReadBandwidthChroma[k] * locals->UrgentBurstFactorChroma[k]
							+ locals->cursor_bw[k] * locals->UrgentBurstFactorCursor[k],
							locals->RequiredPrefetchPixelDataBWLuma[i][j][k] * locals->UrgentBurstFactorLumaPre[k]
							+ locals->RequiredPrefetchPixelDataBWChroma[i][j][k] * locals->UrgentBurstFactorChromaPre[k]
							+ locals->cursor_bw_pre[k] * locals->UrgentBurstFactorCursorPre[k]);
				पूर्ण
				mode_lib->vba.TotImmediateFlipBytes = 0.0;
				क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
					mode_lib->vba.TotImmediateFlipBytes = mode_lib->vba.TotImmediateFlipBytes
						+ locals->PDEAndMetaPTEBytesPerFrame[0][0][k] + locals->MetaRowBytes[0][0][k] + locals->DPTEBytesPerRow[0][0][k];
				पूर्ण

				क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
					CalculateFlipSchedule(
							mode_lib,
							mode_lib->vba.PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData,
							mode_lib->vba.PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly,
							mode_lib->vba.ExtraLatency,
							mode_lib->vba.UrgentLatency,
							mode_lib->vba.GPUVMMaxPageTableLevels,
							mode_lib->vba.HostVMEnable,
							mode_lib->vba.HostVMMaxPageTableLevels,
							mode_lib->vba.HostVMCachedPageTableLevels,
							mode_lib->vba.GPUVMEnable,
							locals->PDEAndMetaPTEBytesPerFrame[0][0][k],
							locals->MetaRowBytes[0][0][k],
							locals->DPTEBytesPerRow[0][0][k],
							mode_lib->vba.BandwidthAvailableForImmediateFlip,
							mode_lib->vba.TotImmediateFlipBytes,
							mode_lib->vba.SourcePixelFormat[k],
							mode_lib->vba.HTotal[k] / mode_lib->vba.PixelClock[k],
							mode_lib->vba.VRatio[k],
							locals->Tno_bw[k],
							mode_lib->vba.DCCEnable[k],
							locals->dpte_row_height[k],
							locals->meta_row_height[k],
							locals->dpte_row_height_chroma[k],
							locals->meta_row_height_chroma[k],
							&locals->DestinationLinesToRequestVMInImmediateFlip[k],
							&locals->DestinationLinesToRequestRowInImmediateFlip[k],
							&locals->final_flip_bw[k],
							&locals->ImmediateFlipSupportedForPipe[k]);
				पूर्ण
				mode_lib->vba.total_dcn_पढ़ो_bw_with_flip = 0.0;
				क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
					mode_lib->vba.total_dcn_पढ़ो_bw_with_flip = mode_lib->vba.total_dcn_पढ़ो_bw_with_flip + dml_max3(
						locals->prefetch_vmrow_bw[k],
						locals->final_flip_bw[k] +  locals->ReadBandwidthLuma[k] * locals->UrgentBurstFactorLuma[k]
						+ locals->ReadBandwidthChroma[k] * locals->UrgentBurstFactorChroma[k]
						+ locals->cursor_bw[k] * locals->UrgentBurstFactorCursor[k],
						locals->final_flip_bw[k] + locals->RequiredPrefetchPixelDataBWLuma[i][j][k]
						* locals->UrgentBurstFactorLumaPre[k] + locals->RequiredPrefetchPixelDataBWChroma[i][j][k]
						* locals->UrgentBurstFactorChromaPre[k] + locals->cursor_bw_pre[k]
						* locals->UrgentBurstFactorCursorPre[k]);
				पूर्ण
				locals->ImmediateFlipSupportedForState[i][j] = true;
				अगर (mode_lib->vba.total_dcn_पढ़ो_bw_with_flip
						> locals->ReturnBWPerState[i][0]) अणु
					locals->ImmediateFlipSupportedForState[i][j] = false;
				पूर्ण
				क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
					अगर (locals->ImmediateFlipSupportedForPipe[k] == false) अणु
						locals->ImmediateFlipSupportedForState[i][j] = false;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अणु
				locals->ImmediateFlipSupportedForState[i][j] = false;
			पूर्ण
			mode_lib->vba.UrgentOutOfOrderReturnPerChannel = dml_max3(
					mode_lib->vba.UrgentOutOfOrderReturnPerChannelPixelDataOnly,
					mode_lib->vba.UrgentOutOfOrderReturnPerChannelPixelMixedWithVMData,
					mode_lib->vba.UrgentOutOfOrderReturnPerChannelVMDataOnly);
			CalculateWatermarksAndDRAMSpeedChangeSupport(
					mode_lib,
					mode_lib->vba.PrefetchMode[i][j],
					mode_lib->vba.NumberOfActivePlanes,
					mode_lib->vba.MaxLineBufferLines,
					mode_lib->vba.LineBufferSize,
					mode_lib->vba.DPPOutputBufferPixels,
					mode_lib->vba.DETBufferSizeInKByte,
					mode_lib->vba.WritebackInterfaceLumaBufferSize,
					mode_lib->vba.WritebackInterfaceChromaBufferSize,
					mode_lib->vba.DCFCLKPerState[i],
					mode_lib->vba.UrgentOutOfOrderReturnPerChannel * mode_lib->vba.NumberOfChannels,
					locals->ReturnBWPerState[i][0],
					mode_lib->vba.GPUVMEnable,
					locals->dpte_group_bytes,
					mode_lib->vba.MetaChunkSize,
					mode_lib->vba.UrgentLatency,
					mode_lib->vba.ExtraLatency,
					mode_lib->vba.WritebackLatency,
					mode_lib->vba.WritebackChunkSize,
					mode_lib->vba.SOCCLKPerState[i],
					mode_lib->vba.DRAMClockChangeLatency,
					mode_lib->vba.SRExitTime,
					mode_lib->vba.SREnterPlusExitTime,
					mode_lib->vba.ProjectedDCFCLKDeepSleep[0][0],
					locals->NoOfDPPThisState,
					mode_lib->vba.DCCEnable,
					locals->RequiredDPPCLKThisState,
					locals->SwathWidthYSingleDPP,
					locals->SwathHeightYThisState,
					locals->ReadBandwidthLuma,
					locals->SwathHeightCThisState,
					locals->ReadBandwidthChroma,
					mode_lib->vba.LBBitPerPixel,
					locals->SwathWidthYThisState,
					mode_lib->vba.HRatio,
					mode_lib->vba.vtaps,
					mode_lib->vba.VTAPsChroma,
					mode_lib->vba.VRatio,
					mode_lib->vba.HTotal,
					mode_lib->vba.PixelClock,
					mode_lib->vba.BlendingAndTiming,
					locals->BytePerPixelInDETY,
					locals->BytePerPixelInDETC,
					mode_lib->vba.WritebackEnable,
					mode_lib->vba.WritebackPixelFormat,
					mode_lib->vba.WritebackDestinationWidth,
					mode_lib->vba.WritebackDestinationHeight,
					mode_lib->vba.WritebackSourceHeight,
					&locals->DRAMClockChangeSupport[i][j],
					&mode_lib->vba.UrgentWatermark,
					&mode_lib->vba.WritebackUrgentWatermark,
					&mode_lib->vba.DRAMClockChangeWatermark,
					&mode_lib->vba.WritebackDRAMClockChangeWatermark,
					&mode_lib->vba.StutterExitWatermark,
					&mode_lib->vba.StutterEnterPlusExitWatermark,
					&mode_lib->vba.MinActiveDRAMClockChangeLatencySupported);
			पूर्ण
		पूर्ण

		/*Vertical Active BW support*/
		अणु
			द्विगुन MaxTotalVActiveRDBandwidth = 0.0;
			क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
				MaxTotalVActiveRDBandwidth = MaxTotalVActiveRDBandwidth + locals->ReadBandwidth[k];
		पूर्ण
		क्रम (i = 0; i <= mode_lib->vba.soc.num_states; ++i) अणु
			locals->MaxTotalVerticalActiveAvailableBandwidth[i][0] = dml_min(
				locals->IdealSDPPortBandwidthPerState[i][0] *
				mode_lib->vba.MaxAveragePercentOfIdealSDPPortBWDisplayCanUseInNormalSystemOperation
				/ 100.0, mode_lib->vba.DRAMSpeedPerState[i] *
				mode_lib->vba.NumberOfChannels *
				mode_lib->vba.DRAMChannelWidth *
				mode_lib->vba.MaxAveragePercentOfIdealDRAMBWDisplayCanUseInNormalSystemOperation
				/ 100.0);

			अगर (MaxTotalVActiveRDBandwidth <= locals->MaxTotalVerticalActiveAvailableBandwidth[i][0]) अणु
				locals->TotalVerticalActiveBandwidthSupport[i][0] = true;
			पूर्ण अन्यथा अणु
				locals->TotalVerticalActiveBandwidthSupport[i][0] = false;
			पूर्ण
		पूर्ण
	पूर्ण

	/*PTE Buffer Size Check*/

	क्रम (i = 0; i <= mode_lib->vba.soc.num_states; i++) अणु
		क्रम (j = 0; j < 2; j++) अणु
			locals->PTEBufferSizeNotExceeded[i][j] = true;
			क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
				अगर (locals->PTEBufferSizeNotExceededY[i][j][k] == false
						|| locals->PTEBufferSizeNotExceededC[i][j][k] == false) अणु
					locals->PTEBufferSizeNotExceeded[i][j] = false;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	/*Cursor Support Check*/

	mode_lib->vba.CursorSupport = true;
	क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
		अगर (mode_lib->vba.CursorWidth[k][0] > 0.0) अणु
			क्रम (m = 0; m < mode_lib->vba.NumberOfCursors[k]; m++) अणु
				अगर (mode_lib->vba.CursorBPP[k][m] == 64 && mode_lib->vba.Cursor64BppSupport == false) अणु
					mode_lib->vba.CursorSupport = false;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	/*Valid Pitch Check*/

	mode_lib->vba.PitchSupport = true;
	क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
		locals->AlignedYPitch[k] = dml_उच्चमान(
				dml_max(mode_lib->vba.PitchY[k], mode_lib->vba.ViewportWidth[k]),
				locals->MacroTileWidthY[k]);
		अगर (locals->AlignedYPitch[k] > mode_lib->vba.PitchY[k]) अणु
			mode_lib->vba.PitchSupport = false;
		पूर्ण
		अगर (mode_lib->vba.DCCEnable[k] == true) अणु
			locals->AlignedDCCMetaPitch[k] = dml_उच्चमान(
					dml_max(
							mode_lib->vba.DCCMetaPitchY[k],
							mode_lib->vba.ViewportWidth[k]),
					64.0 * locals->Read256BlockWidthY[k]);
		पूर्ण अन्यथा अणु
			locals->AlignedDCCMetaPitch[k] = mode_lib->vba.DCCMetaPitchY[k];
		पूर्ण
		अगर (locals->AlignedDCCMetaPitch[k] > mode_lib->vba.DCCMetaPitchY[k]) अणु
			mode_lib->vba.PitchSupport = false;
		पूर्ण
		अगर (mode_lib->vba.SourcePixelFormat[k] != dm_444_64
				&& mode_lib->vba.SourcePixelFormat[k] != dm_444_32
				&& mode_lib->vba.SourcePixelFormat[k] != dm_444_16
				&& mode_lib->vba.SourcePixelFormat[k] != dm_mono_16
				&& mode_lib->vba.SourcePixelFormat[k] != dm_mono_8) अणु
			locals->AlignedCPitch[k] = dml_उच्चमान(
					dml_max(
							mode_lib->vba.PitchC[k],
							mode_lib->vba.ViewportWidth[k] / 2.0),
					locals->MacroTileWidthC[k]);
		पूर्ण अन्यथा अणु
			locals->AlignedCPitch[k] = mode_lib->vba.PitchC[k];
		पूर्ण
		अगर (locals->AlignedCPitch[k] > mode_lib->vba.PitchC[k]) अणु
			mode_lib->vba.PitchSupport = false;
		पूर्ण
	पूर्ण
	/*Mode Support, Voltage State and SOC Configuration*/

	क्रम (i = mode_lib->vba.soc.num_states; i >= 0; i--) अणु
		क्रम (j = 0; j < 2; j++) अणु
			क्रमागत dm_validation_status status = DML_VALIDATION_OK;

			अगर (!mode_lib->vba.ScaleRatioAndTapsSupport) अणु
				status = DML_FAIL_SCALE_RATIO_TAP;
			पूर्ण अन्यथा अगर (!mode_lib->vba.SourceFormatPixelAndScanSupport) अणु
				status = DML_FAIL_SOURCE_PIXEL_FORMAT;
			पूर्ण अन्यथा अगर (!locals->ViewportSizeSupport[i][0]) अणु
				status = DML_FAIL_VIEWPORT_SIZE;
			पूर्ण अन्यथा अगर (!locals->DIOSupport[i]) अणु
				status = DML_FAIL_DIO_SUPPORT;
			पूर्ण अन्यथा अगर (locals->NotEnoughDSCUnits[i]) अणु
				status = DML_FAIL_NOT_ENOUGH_DSC;
			पूर्ण अन्यथा अगर (locals->DSCCLKRequiredMoreThanSupported[i]) अणु
				status = DML_FAIL_DSC_CLK_REQUIRED;
			पूर्ण अन्यथा अगर (!locals->ROBSupport[i][0]) अणु
				status = DML_FAIL_REORDERING_BUFFER;
			पूर्ण अन्यथा अगर (!locals->DISPCLK_DPPCLK_Support[i][j]) अणु
				status = DML_FAIL_DISPCLK_DPPCLK;
			पूर्ण अन्यथा अगर (!locals->TotalAvailablePipesSupport[i][j]) अणु
				status = DML_FAIL_TOTAL_AVAILABLE_PIPES;
			पूर्ण अन्यथा अगर (!mode_lib->vba.NumberOfOTGSupport) अणु
				status = DML_FAIL_NUM_OTG;
			पूर्ण अन्यथा अगर (!mode_lib->vba.WritebackModeSupport) अणु
				status = DML_FAIL_WRITEBACK_MODE;
			पूर्ण अन्यथा अगर (!mode_lib->vba.WritebackLatencySupport) अणु
				status = DML_FAIL_WRITEBACK_LATENCY;
			पूर्ण अन्यथा अगर (!mode_lib->vba.WritebackScaleRatioAndTapsSupport) अणु
				status = DML_FAIL_WRITEBACK_SCALE_RATIO_TAP;
			पूर्ण अन्यथा अगर (!mode_lib->vba.CursorSupport) अणु
				status = DML_FAIL_CURSOR_SUPPORT;
			पूर्ण अन्यथा अगर (!mode_lib->vba.PitchSupport) अणु
				status = DML_FAIL_PITCH_SUPPORT;
			पूर्ण अन्यथा अगर (!locals->TotalVerticalActiveBandwidthSupport[i][0]) अणु
				status = DML_FAIL_TOTAL_V_ACTIVE_BW;
			पूर्ण अन्यथा अगर (!locals->PTEBufferSizeNotExceeded[i][j]) अणु
				status = DML_FAIL_PTE_BUFFER_SIZE;
			पूर्ण अन्यथा अगर (mode_lib->vba.NonsupportedDSCInputBPC) अणु
				status = DML_FAIL_DSC_INPUT_BPC;
			पूर्ण अन्यथा अगर ((mode_lib->vba.HostVMEnable
					&& !locals->ImmediateFlipSupportedForState[i][j])) अणु
				status = DML_FAIL_HOST_VM_IMMEDIATE_FLIP;
			पूर्ण अन्यथा अगर (!locals->PrefetchSupported[i][j]) अणु
				status = DML_FAIL_PREFETCH_SUPPORT;
			पूर्ण अन्यथा अगर (!locals->VRatioInPrefetchSupported[i][j]) अणु
				status = DML_FAIL_V_RATIO_PREFETCH;
			पूर्ण

			अगर (status == DML_VALIDATION_OK) अणु
				locals->ModeSupport[i][j] = true;
			पूर्ण अन्यथा अणु
				locals->ModeSupport[i][j] = false;
			पूर्ण
			locals->ValidationStatus[i] = status;
		पूर्ण
	पूर्ण
	अणु
		अचिन्हित पूर्णांक MaximumMPCCombine = 0;
		mode_lib->vba.VoltageLevel = mode_lib->vba.soc.num_states + 1;
		क्रम (i = mode_lib->vba.VoltageOverrideLevel; i <= mode_lib->vba.soc.num_states; i++) अणु
			अगर (locals->ModeSupport[i][0] == true || locals->ModeSupport[i][1] == true) अणु
				mode_lib->vba.VoltageLevel = i;
				अगर (locals->ModeSupport[i][1] == true && (locals->ModeSupport[i][0] == false
						|| mode_lib->vba.WhenToDoMPCCombine == dm_mpc_always_when_possible
						|| (mode_lib->vba.WhenToDoMPCCombine == dm_mpc_reduce_voltage_and_घड़ीs
							&& ((locals->DRAMClockChangeSupport[i][1] == dm_dram_घड़ी_change_vactive
								&& locals->DRAMClockChangeSupport[i][0] != dm_dram_घड़ी_change_vactive)
							|| (locals->DRAMClockChangeSupport[i][1] == dm_dram_घड़ी_change_vblank
								&& locals->DRAMClockChangeSupport[i][0] == dm_dram_घड़ी_change_unsupported))))) अणु
					MaximumMPCCombine = 1;
				पूर्ण अन्यथा अणु
					MaximumMPCCombine = 0;
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण
		mode_lib->vba.ImmediateFlipSupport =
			locals->ImmediateFlipSupportedForState[mode_lib->vba.VoltageLevel][MaximumMPCCombine];
		क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
			mode_lib->vba.DPPPerPlane[k] = locals->NoOfDPP[mode_lib->vba.VoltageLevel][MaximumMPCCombine][k];
			locals->DPPCLK[k] = locals->RequiredDPPCLK[mode_lib->vba.VoltageLevel][MaximumMPCCombine][k];
		पूर्ण
		mode_lib->vba.DISPCLK = locals->RequiredDISPCLK[mode_lib->vba.VoltageLevel][MaximumMPCCombine];
		mode_lib->vba.maxMpcComb = MaximumMPCCombine;
	पूर्ण
	mode_lib->vba.DCFCLK = mode_lib->vba.DCFCLKPerState[mode_lib->vba.VoltageLevel];
	mode_lib->vba.DRAMSpeed = mode_lib->vba.DRAMSpeedPerState[mode_lib->vba.VoltageLevel];
	mode_lib->vba.FabricClock = mode_lib->vba.FabricClockPerState[mode_lib->vba.VoltageLevel];
	mode_lib->vba.SOCCLK = mode_lib->vba.SOCCLKPerState[mode_lib->vba.VoltageLevel];
	mode_lib->vba.ReturnBW = locals->ReturnBWPerState[mode_lib->vba.VoltageLevel][0];
	क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
		अगर (mode_lib->vba.BlendingAndTiming[k] == k) अणु
			mode_lib->vba.ODMCombineEnabled[k] =
					locals->ODMCombineEnablePerState[mode_lib->vba.VoltageLevel][k];
		पूर्ण अन्यथा अणु
			mode_lib->vba.ODMCombineEnabled[k] = false;
		पूर्ण
		mode_lib->vba.DSCEnabled[k] =
				locals->RequiresDSC[mode_lib->vba.VoltageLevel][k];
		mode_lib->vba.OutputBpp[k] =
				locals->OutputBppPerState[mode_lib->vba.VoltageLevel][k];
	पूर्ण
पूर्ण

अटल व्योम CalculateWatermarksAndDRAMSpeedChangeSupport(
		काष्ठा display_mode_lib *mode_lib,
		अचिन्हित पूर्णांक PrefetchMode,
		अचिन्हित पूर्णांक NumberOfActivePlanes,
		अचिन्हित पूर्णांक MaxLineBufferLines,
		अचिन्हित पूर्णांक LineBufferSize,
		अचिन्हित पूर्णांक DPPOutputBufferPixels,
		द्विगुन DETBufferSizeInKByte,
		अचिन्हित पूर्णांक WritebackInterfaceLumaBufferSize,
		अचिन्हित पूर्णांक WritebackInterfaceChromaBufferSize,
		द्विगुन DCFCLK,
		द्विगुन UrgentOutOfOrderReturn,
		द्विगुन ReturnBW,
		bool GPUVMEnable,
		पूर्णांक dpte_group_bytes[],
		अचिन्हित पूर्णांक MetaChunkSize,
		द्विगुन UrgentLatency,
		द्विगुन ExtraLatency,
		द्विगुन WritebackLatency,
		द्विगुन WritebackChunkSize,
		द्विगुन SOCCLK,
		द्विगुन DRAMClockChangeLatency,
		द्विगुन SRExitTime,
		द्विगुन SREnterPlusExitTime,
		द्विगुन DCFCLKDeepSleep,
		पूर्णांक DPPPerPlane[],
		bool DCCEnable[],
		द्विगुन DPPCLK[],
		द्विगुन SwathWidthSingleDPPY[],
		अचिन्हित पूर्णांक SwathHeightY[],
		द्विगुन ReadBandwidthPlaneLuma[],
		अचिन्हित पूर्णांक SwathHeightC[],
		द्विगुन ReadBandwidthPlaneChroma[],
		अचिन्हित पूर्णांक LBBitPerPixel[],
		द्विगुन SwathWidthY[],
		द्विगुन HRatio[],
		अचिन्हित पूर्णांक vtaps[],
		अचिन्हित पूर्णांक VTAPsChroma[],
		द्विगुन VRatio[],
		अचिन्हित पूर्णांक HTotal[],
		द्विगुन PixelClock[],
		अचिन्हित पूर्णांक BlendingAndTiming[],
		द्विगुन BytePerPixelDETY[],
		द्विगुन BytePerPixelDETC[],
		bool WritebackEnable[],
		क्रमागत source_क्रमmat_class WritebackPixelFormat[],
		द्विगुन WritebackDestinationWidth[],
		द्विगुन WritebackDestinationHeight[],
		द्विगुन WritebackSourceHeight[],
		क्रमागत घड़ी_change_support *DRAMClockChangeSupport,
		द्विगुन *UrgentWatermark,
		द्विगुन *WritebackUrgentWatermark,
		द्विगुन *DRAMClockChangeWatermark,
		द्विगुन *WritebackDRAMClockChangeWatermark,
		द्विगुन *StutterExitWatermark,
		द्विगुन *StutterEnterPlusExitWatermark,
		द्विगुन *MinActiveDRAMClockChangeLatencySupported)
अणु
	द्विगुन EffectiveLBLatencyHidingY;
	द्विगुन EffectiveLBLatencyHidingC;
	द्विगुन DPPOutputBufferLinesY;
	द्विगुन DPPOutputBufferLinesC;
	द्विगुन DETBufferSizeY;
	द्विगुन DETBufferSizeC;
	द्विगुन LinesInDETY[DC__NUM_DPP__MAX];
	द्विगुन LinesInDETC;
	अचिन्हित पूर्णांक LinesInDETYRoundedDownToSwath[DC__NUM_DPP__MAX];
	अचिन्हित पूर्णांक LinesInDETCRoundedDownToSwath;
	द्विगुन FullDETBufferingTimeY[DC__NUM_DPP__MAX];
	द्विगुन FullDETBufferingTimeC;
	द्विगुन ActiveDRAMClockChangeLatencyMarginY;
	द्विगुन ActiveDRAMClockChangeLatencyMarginC;
	द्विगुन WritebackDRAMClockChangeLatencyMargin;
	द्विगुन PlaneWithMinActiveDRAMClockChangeMargin;
	द्विगुन SecondMinActiveDRAMClockChangeMarginOneDisplayInVBLank;
	द्विगुन FullDETBufferingTimeYStutterCriticalPlane = 0;
	द्विगुन TimeToFinishSwathTransferStutterCriticalPlane = 0;
	अचिन्हित पूर्णांक k, j;

	mode_lib->vba.TotalActiveDPP = 0;
	mode_lib->vba.TotalDCCActiveDPP = 0;
	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		mode_lib->vba.TotalActiveDPP = mode_lib->vba.TotalActiveDPP + DPPPerPlane[k];
		अगर (DCCEnable[k] == true) अणु
			mode_lib->vba.TotalDCCActiveDPP = mode_lib->vba.TotalDCCActiveDPP + DPPPerPlane[k];
		पूर्ण
	पूर्ण

	mode_lib->vba.TotalDataReadBandwidth = 0;
	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		mode_lib->vba.TotalDataReadBandwidth = mode_lib->vba.TotalDataReadBandwidth
				+ ReadBandwidthPlaneLuma[k] + ReadBandwidthPlaneChroma[k];
	पूर्ण

	*UrgentWatermark = UrgentLatency + ExtraLatency;

	*DRAMClockChangeWatermark = DRAMClockChangeLatency + *UrgentWatermark;

	mode_lib->vba.TotalActiveWriteback = 0;
	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		अगर (WritebackEnable[k] == true) अणु
			mode_lib->vba.TotalActiveWriteback = mode_lib->vba.TotalActiveWriteback + 1;
		पूर्ण
	पूर्ण

	अगर (mode_lib->vba.TotalActiveWriteback <= 1) अणु
		*WritebackUrgentWatermark = WritebackLatency;
	पूर्ण अन्यथा अणु
		*WritebackUrgentWatermark = WritebackLatency
				+ WritebackChunkSize * 1024.0 / 32.0 / SOCCLK;
	पूर्ण

	अगर (mode_lib->vba.TotalActiveWriteback <= 1) अणु
		*WritebackDRAMClockChangeWatermark = DRAMClockChangeLatency + WritebackLatency;
	पूर्ण अन्यथा अणु
		*WritebackDRAMClockChangeWatermark = DRAMClockChangeLatency + WritebackLatency
				+ WritebackChunkSize * 1024.0 / 32.0 / SOCCLK;
	पूर्ण

	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु

		mode_lib->vba.LBLatencyHidingSourceLinesY = dml_min((द्विगुन) MaxLineBufferLines,
			dml_न्यूनमान(LineBufferSize / LBBitPerPixel[k] / (SwathWidthY[k] / dml_max(HRatio[k], 1.0)), 1))
				- (vtaps[k] - 1);

		mode_lib->vba.LBLatencyHidingSourceLinesC = dml_min((द्विगुन) MaxLineBufferLines,
			dml_न्यूनमान(LineBufferSize / LBBitPerPixel[k] / (SwathWidthY[k] / 2 / dml_max(HRatio[k] / 2, 1.0)), 1))
				- (VTAPsChroma[k] - 1);

		EffectiveLBLatencyHidingY = mode_lib->vba.LBLatencyHidingSourceLinesY / VRatio[k]
				* (HTotal[k] / PixelClock[k]);

		EffectiveLBLatencyHidingC = mode_lib->vba.LBLatencyHidingSourceLinesC
				/ (VRatio[k] / 2) * (HTotal[k] / PixelClock[k]);

		अगर (SwathWidthY[k] > 2 * DPPOutputBufferPixels) अणु
			DPPOutputBufferLinesY = (द्विगुन) DPPOutputBufferPixels / SwathWidthY[k];
		पूर्ण अन्यथा अगर (SwathWidthY[k] > DPPOutputBufferPixels) अणु
			DPPOutputBufferLinesY = 0.5;
		पूर्ण अन्यथा अणु
			DPPOutputBufferLinesY = 1;
		पूर्ण

		अगर (SwathWidthY[k] / 2.0 > 2 * DPPOutputBufferPixels) अणु
			DPPOutputBufferLinesC = (द्विगुन) DPPOutputBufferPixels
					/ (SwathWidthY[k] / 2.0);
		पूर्ण अन्यथा अगर (SwathWidthY[k] / 2.0 > DPPOutputBufferPixels) अणु
			DPPOutputBufferLinesC = 0.5;
		पूर्ण अन्यथा अणु
			DPPOutputBufferLinesC = 1;
		पूर्ण

		CalculateDETBufferSize(
				DETBufferSizeInKByte,
				SwathHeightY[k],
				SwathHeightC[k],
				&DETBufferSizeY,
				&DETBufferSizeC);

		LinesInDETY[k] = DETBufferSizeY / BytePerPixelDETY[k] / SwathWidthY[k];
		LinesInDETYRoundedDownToSwath[k] = dml_न्यूनमान(LinesInDETY[k], SwathHeightY[k]);
		FullDETBufferingTimeY[k] = LinesInDETYRoundedDownToSwath[k]
				* (HTotal[k] / PixelClock[k]) / VRatio[k];
		अगर (BytePerPixelDETC[k] > 0) अणु
			LinesInDETC = DETBufferSizeC / BytePerPixelDETC[k] / (SwathWidthY[k] / 2.0);
			LinesInDETCRoundedDownToSwath = dml_न्यूनमान(LinesInDETC, SwathHeightC[k]);
			FullDETBufferingTimeC = LinesInDETCRoundedDownToSwath
					* (HTotal[k] / PixelClock[k]) / (VRatio[k] / 2);
		पूर्ण अन्यथा अणु
			LinesInDETC = 0;
			FullDETBufferingTimeC = 999999;
		पूर्ण

		ActiveDRAMClockChangeLatencyMarginY = HTotal[k] / PixelClock[k]
				* DPPOutputBufferLinesY + EffectiveLBLatencyHidingY
				+ FullDETBufferingTimeY[k] - *DRAMClockChangeWatermark;

		अगर (NumberOfActivePlanes > 1) अणु
			ActiveDRAMClockChangeLatencyMarginY = ActiveDRAMClockChangeLatencyMarginY
				- (1 - 1.0 / NumberOfActivePlanes) * SwathHeightY[k] * HTotal[k] / PixelClock[k] / VRatio[k];
		पूर्ण

		अगर (BytePerPixelDETC[k] > 0) अणु
			ActiveDRAMClockChangeLatencyMarginC = HTotal[k] / PixelClock[k]
					* DPPOutputBufferLinesC + EffectiveLBLatencyHidingC
					+ FullDETBufferingTimeC - *DRAMClockChangeWatermark;
			अगर (NumberOfActivePlanes > 1) अणु
				ActiveDRAMClockChangeLatencyMarginC = ActiveDRAMClockChangeLatencyMarginC
					- (1 - 1.0 / NumberOfActivePlanes) * SwathHeightC[k] * HTotal[k] / PixelClock[k] / (VRatio[k] / 2);
			पूर्ण
			mode_lib->vba.ActiveDRAMClockChangeLatencyMargin[k] = dml_min(
					ActiveDRAMClockChangeLatencyMarginY,
					ActiveDRAMClockChangeLatencyMarginC);
		पूर्ण अन्यथा अणु
			mode_lib->vba.ActiveDRAMClockChangeLatencyMargin[k] = ActiveDRAMClockChangeLatencyMarginY;
		पूर्ण

		अगर (WritebackEnable[k] == true) अणु
			अगर (WritebackPixelFormat[k] == dm_444_32) अणु
				WritebackDRAMClockChangeLatencyMargin = (WritebackInterfaceLumaBufferSize
					+ WritebackInterfaceChromaBufferSize) / (WritebackDestinationWidth[k]
					* WritebackDestinationHeight[k] / (WritebackSourceHeight[k] * HTotal[k]
					/ PixelClock[k]) * 4) - *WritebackDRAMClockChangeWatermark;
			पूर्ण अन्यथा अणु
				WritebackDRAMClockChangeLatencyMargin = dml_min(
						WritebackInterfaceLumaBufferSize * 8.0 / 10,
						2 * WritebackInterfaceChromaBufferSize * 8.0 / 10) / (WritebackDestinationWidth[k]
							* WritebackDestinationHeight[k] / (WritebackSourceHeight[k] * HTotal[k] / PixelClock[k]))
						- *WritebackDRAMClockChangeWatermark;
			पूर्ण
			mode_lib->vba.ActiveDRAMClockChangeLatencyMargin[k] = dml_min(
					mode_lib->vba.ActiveDRAMClockChangeLatencyMargin[k],
					WritebackDRAMClockChangeLatencyMargin);
		पूर्ण
	पूर्ण

	mode_lib->vba.MinActiveDRAMClockChangeMargin = 999999;
	PlaneWithMinActiveDRAMClockChangeMargin = 0;
	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		अगर (mode_lib->vba.ActiveDRAMClockChangeLatencyMargin[k]
				< mode_lib->vba.MinActiveDRAMClockChangeMargin) अणु
			mode_lib->vba.MinActiveDRAMClockChangeMargin =
					mode_lib->vba.ActiveDRAMClockChangeLatencyMargin[k];
			अगर (BlendingAndTiming[k] == k) अणु
				PlaneWithMinActiveDRAMClockChangeMargin = k;
			पूर्ण अन्यथा अणु
				क्रम (j = 0; j < NumberOfActivePlanes; ++j) अणु
					अगर (BlendingAndTiming[k] == j) अणु
						PlaneWithMinActiveDRAMClockChangeMargin = j;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	*MinActiveDRAMClockChangeLatencySupported = mode_lib->vba.MinActiveDRAMClockChangeMargin + DRAMClockChangeLatency;

	SecondMinActiveDRAMClockChangeMarginOneDisplayInVBLank = 999999;
	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		अगर (!((k == PlaneWithMinActiveDRAMClockChangeMargin) && (BlendingAndTiming[k] == k))
				&& !(BlendingAndTiming[k] == PlaneWithMinActiveDRAMClockChangeMargin)
				&& mode_lib->vba.ActiveDRAMClockChangeLatencyMargin[k]
						< SecondMinActiveDRAMClockChangeMarginOneDisplayInVBLank) अणु
			SecondMinActiveDRAMClockChangeMarginOneDisplayInVBLank =
					mode_lib->vba.ActiveDRAMClockChangeLatencyMargin[k];
		पूर्ण
	पूर्ण

	mode_lib->vba.TotalNumberOfActiveOTG = 0;
	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		अगर (BlendingAndTiming[k] == k) अणु
			mode_lib->vba.TotalNumberOfActiveOTG = mode_lib->vba.TotalNumberOfActiveOTG + 1;
		पूर्ण
	पूर्ण

	अगर (mode_lib->vba.MinActiveDRAMClockChangeMargin > 0 && PrefetchMode == 0) अणु
		*DRAMClockChangeSupport = dm_dram_घड़ी_change_vactive;
	पूर्ण अन्यथा अगर (((mode_lib->vba.SynchronizedVBlank == true
			|| mode_lib->vba.TotalNumberOfActiveOTG == 1
			|| SecondMinActiveDRAMClockChangeMarginOneDisplayInVBLank > 0)
			&& PrefetchMode == 0)) अणु
		*DRAMClockChangeSupport = dm_dram_घड़ी_change_vblank;
	पूर्ण अन्यथा अणु
		*DRAMClockChangeSupport = dm_dram_घड़ी_change_unsupported;
	पूर्ण

	FullDETBufferingTimeYStutterCriticalPlane = FullDETBufferingTimeY[0];
	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		अगर (FullDETBufferingTimeY[k] <= FullDETBufferingTimeYStutterCriticalPlane) अणु
			TimeToFinishSwathTransferStutterCriticalPlane = (SwathHeightY[k]
					- (LinesInDETY[k] - LinesInDETYRoundedDownToSwath[k]))
					* (HTotal[k] / PixelClock[k]) / VRatio[k];
		पूर्ण
	पूर्ण

	*StutterExitWatermark = SRExitTime + mode_lib->vba.LastPixelOfLineExtraWatermark
			+ ExtraLatency + 10 / DCFCLKDeepSleep;
	*StutterEnterPlusExitWatermark = dml_max(
			SREnterPlusExitTime + mode_lib->vba.LastPixelOfLineExtraWatermark
					+ ExtraLatency + 10 / DCFCLKDeepSleep,
			TimeToFinishSwathTransferStutterCriticalPlane);

पूर्ण

अटल व्योम CalculateDCFCLKDeepSleep(
		काष्ठा display_mode_lib *mode_lib,
		अचिन्हित पूर्णांक NumberOfActivePlanes,
		द्विगुन BytePerPixelDETY[],
		द्विगुन BytePerPixelDETC[],
		द्विगुन VRatio[],
		द्विगुन SwathWidthY[],
		पूर्णांक DPPPerPlane[],
		द्विगुन HRatio[],
		द्विगुन PixelClock[],
		द्विगुन PSCL_THROUGHPUT[],
		द्विगुन PSCL_THROUGHPUT_CHROMA[],
		द्विगुन DPPCLK[],
		द्विगुन *DCFCLKDeepSleep)
अणु
	अचिन्हित पूर्णांक k;
	द्विगुन DisplayPipeLineDeliveryTimeLuma;
	द्विगुन DisplayPipeLineDeliveryTimeChroma;
	//द्विगुन   DCFCLKDeepSleepPerPlane[DC__NUM_DPP__MAX];

	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		अगर (VRatio[k] <= 1) अणु
			DisplayPipeLineDeliveryTimeLuma = SwathWidthY[k] * DPPPerPlane[k]
					/ HRatio[k] / PixelClock[k];
		पूर्ण अन्यथा अणु
			DisplayPipeLineDeliveryTimeLuma = SwathWidthY[k] / PSCL_THROUGHPUT[k]
					/ DPPCLK[k];
		पूर्ण
		अगर (BytePerPixelDETC[k] == 0) अणु
			DisplayPipeLineDeliveryTimeChroma = 0;
		पूर्ण अन्यथा अणु
			अगर (VRatio[k] / 2 <= 1) अणु
				DisplayPipeLineDeliveryTimeChroma = SwathWidthY[k] / 2.0
						* DPPPerPlane[k] / (HRatio[k] / 2) / PixelClock[k];
			पूर्ण अन्यथा अणु
				DisplayPipeLineDeliveryTimeChroma = SwathWidthY[k] / 2.0
						/ PSCL_THROUGHPUT_CHROMA[k] / DPPCLK[k];
			पूर्ण
		पूर्ण

		अगर (BytePerPixelDETC[k] > 0) अणु
			mode_lib->vba.DCFCLKDeepSleepPerPlane[k] = dml_max(
					1.1 * SwathWidthY[k] * dml_उच्चमान(BytePerPixelDETY[k], 1)
							/ 32.0 / DisplayPipeLineDeliveryTimeLuma,
					1.1 * SwathWidthY[k] / 2.0
							* dml_उच्चमान(BytePerPixelDETC[k], 2) / 32.0
							/ DisplayPipeLineDeliveryTimeChroma);
		पूर्ण अन्यथा अणु
			mode_lib->vba.DCFCLKDeepSleepPerPlane[k] = 1.1 * SwathWidthY[k]
					* dml_उच्चमान(BytePerPixelDETY[k], 1) / 64.0
					/ DisplayPipeLineDeliveryTimeLuma;
		पूर्ण
		mode_lib->vba.DCFCLKDeepSleepPerPlane[k] = dml_max(
				mode_lib->vba.DCFCLKDeepSleepPerPlane[k],
				PixelClock[k] / 16);

	पूर्ण

	*DCFCLKDeepSleep = 8;
	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		*DCFCLKDeepSleep = dml_max(
				*DCFCLKDeepSleep,
				mode_lib->vba.DCFCLKDeepSleepPerPlane[k]);
	पूर्ण
पूर्ण

अटल व्योम CalculateDETBufferSize(
		द्विगुन DETBufferSizeInKByte,
		अचिन्हित पूर्णांक SwathHeightY,
		अचिन्हित पूर्णांक SwathHeightC,
		द्विगुन *DETBufferSizeY,
		द्विगुन *DETBufferSizeC)
अणु
	अगर (SwathHeightC == 0) अणु
		*DETBufferSizeY = DETBufferSizeInKByte * 1024;
		*DETBufferSizeC = 0;
	पूर्ण अन्यथा अगर (SwathHeightY <= SwathHeightC) अणु
		*DETBufferSizeY = DETBufferSizeInKByte * 1024 / 2;
		*DETBufferSizeC = DETBufferSizeInKByte * 1024 / 2;
	पूर्ण अन्यथा अणु
		*DETBufferSizeY = DETBufferSizeInKByte * 1024 * 2 / 3;
		*DETBufferSizeC = DETBufferSizeInKByte * 1024 / 3;
	पूर्ण
पूर्ण

अटल व्योम CalculateUrgentBurstFactor(
		अचिन्हित पूर्णांक DETBufferSizeInKByte,
		अचिन्हित पूर्णांक SwathHeightY,
		अचिन्हित पूर्णांक SwathHeightC,
		अचिन्हित पूर्णांक SwathWidthY,
		द्विगुन LineTime,
		द्विगुन UrgentLatency,
		द्विगुन CursorBufferSize,
		अचिन्हित पूर्णांक CursorWidth,
		अचिन्हित पूर्णांक CursorBPP,
		द्विगुन VRatio,
		द्विगुन VRatioPreY,
		द्विगुन VRatioPreC,
		द्विगुन BytePerPixelInDETY,
		द्विगुन BytePerPixelInDETC,
		द्विगुन *UrgentBurstFactorCursor,
		द्विगुन *UrgentBurstFactorCursorPre,
		द्विगुन *UrgentBurstFactorLuma,
		द्विगुन *UrgentBurstFactorLumaPre,
		द्विगुन *UrgentBurstFactorChroma,
		द्विगुन *UrgentBurstFactorChromaPre,
		अचिन्हित पूर्णांक *NotEnoughUrgentLatencyHiding,
		अचिन्हित पूर्णांक *NotEnoughUrgentLatencyHidingPre)
अणु
	द्विगुन LinesInDETLuma;
	द्विगुन LinesInDETChroma;
	अचिन्हित पूर्णांक LinesInCursorBuffer;
	द्विगुन CursorBufferSizeInTime;
	द्विगुन CursorBufferSizeInTimePre;
	द्विगुन DETBufferSizeInTimeLuma;
	द्विगुन DETBufferSizeInTimeLumaPre;
	द्विगुन DETBufferSizeInTimeChroma;
	द्विगुन DETBufferSizeInTimeChromaPre;
	द्विगुन DETBufferSizeY;
	द्विगुन DETBufferSizeC;

	*NotEnoughUrgentLatencyHiding = 0;
	*NotEnoughUrgentLatencyHidingPre = 0;

	अगर (CursorWidth > 0) अणु
		LinesInCursorBuffer = 1 << (अचिन्हित पूर्णांक) dml_न्यूनमान(
			dml_log2(CursorBufferSize * 1024.0 / (CursorWidth * CursorBPP / 8.0)), 1.0);
		CursorBufferSizeInTime = LinesInCursorBuffer * LineTime / VRatio;
		अगर (CursorBufferSizeInTime - UrgentLatency <= 0) अणु
			*NotEnoughUrgentLatencyHiding = 1;
			*UrgentBurstFactorCursor = 0;
		पूर्ण अन्यथा अणु
			*UrgentBurstFactorCursor = CursorBufferSizeInTime
					/ (CursorBufferSizeInTime - UrgentLatency);
		पूर्ण
		अगर (VRatioPreY > 0) अणु
			CursorBufferSizeInTimePre = LinesInCursorBuffer * LineTime / VRatioPreY;
			अगर (CursorBufferSizeInTimePre - UrgentLatency <= 0) अणु
				*NotEnoughUrgentLatencyHidingPre = 1;
				*UrgentBurstFactorCursorPre = 0;
			पूर्ण अन्यथा अणु
				*UrgentBurstFactorCursorPre = CursorBufferSizeInTimePre
						/ (CursorBufferSizeInTimePre - UrgentLatency);
			पूर्ण
		पूर्ण अन्यथा अणु
			*UrgentBurstFactorCursorPre = 1;
		पूर्ण
	पूर्ण

	CalculateDETBufferSize(
			DETBufferSizeInKByte,
			SwathHeightY,
			SwathHeightC,
			&DETBufferSizeY,
			&DETBufferSizeC);

	LinesInDETLuma = DETBufferSizeY / BytePerPixelInDETY / SwathWidthY;
	DETBufferSizeInTimeLuma = dml_न्यूनमान(LinesInDETLuma, SwathHeightY) * LineTime / VRatio;
	अगर (DETBufferSizeInTimeLuma - UrgentLatency <= 0) अणु
		*NotEnoughUrgentLatencyHiding = 1;
		*UrgentBurstFactorLuma = 0;
	पूर्ण अन्यथा अणु
		*UrgentBurstFactorLuma = DETBufferSizeInTimeLuma
				/ (DETBufferSizeInTimeLuma - UrgentLatency);
	पूर्ण
	अगर (VRatioPreY > 0) अणु
		DETBufferSizeInTimeLumaPre = dml_न्यूनमान(LinesInDETLuma, SwathHeightY) * LineTime
				/ VRatioPreY;
		अगर (DETBufferSizeInTimeLumaPre - UrgentLatency <= 0) अणु
			*NotEnoughUrgentLatencyHidingPre = 1;
			*UrgentBurstFactorLumaPre = 0;
		पूर्ण अन्यथा अणु
			*UrgentBurstFactorLumaPre = DETBufferSizeInTimeLumaPre
					/ (DETBufferSizeInTimeLumaPre - UrgentLatency);
		पूर्ण
	पूर्ण अन्यथा अणु
		*UrgentBurstFactorLumaPre = 1;
	पूर्ण

	अगर (BytePerPixelInDETC > 0) अणु
		LinesInDETChroma = DETBufferSizeC / BytePerPixelInDETC / (SwathWidthY / 2);
		DETBufferSizeInTimeChroma = dml_न्यूनमान(LinesInDETChroma, SwathHeightC) * LineTime
				/ (VRatio / 2);
		अगर (DETBufferSizeInTimeChroma - UrgentLatency <= 0) अणु
			*NotEnoughUrgentLatencyHiding = 1;
			*UrgentBurstFactorChroma = 0;
		पूर्ण अन्यथा अणु
			*UrgentBurstFactorChroma = DETBufferSizeInTimeChroma
					/ (DETBufferSizeInTimeChroma - UrgentLatency);
		पूर्ण
		अगर (VRatioPreC > 0) अणु
			DETBufferSizeInTimeChromaPre = dml_न्यूनमान(LinesInDETChroma, SwathHeightC)
					* LineTime / VRatioPreC;
			अगर (DETBufferSizeInTimeChromaPre - UrgentLatency <= 0) अणु
				*NotEnoughUrgentLatencyHidingPre = 1;
				*UrgentBurstFactorChromaPre = 0;
			पूर्ण अन्यथा अणु
				*UrgentBurstFactorChromaPre = DETBufferSizeInTimeChromaPre
						/ (DETBufferSizeInTimeChromaPre - UrgentLatency);
			पूर्ण
		पूर्ण अन्यथा अणु
			*UrgentBurstFactorChromaPre = 1;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम CalculatePixelDeliveryTimes(
		अचिन्हित पूर्णांक NumberOfActivePlanes,
		द्विगुन VRatio[],
		द्विगुन VRatioPrefetchY[],
		द्विगुन VRatioPrefetchC[],
		अचिन्हित पूर्णांक swath_width_luma_ub[],
		अचिन्हित पूर्णांक swath_width_chroma_ub[],
		पूर्णांक DPPPerPlane[],
		द्विगुन HRatio[],
		द्विगुन PixelClock[],
		द्विगुन PSCL_THROUGHPUT[],
		द्विगुन PSCL_THROUGHPUT_CHROMA[],
		द्विगुन DPPCLK[],
		द्विगुन BytePerPixelDETC[],
		क्रमागत scan_direction_class SourceScan[],
		अचिन्हित पूर्णांक BlockWidth256BytesY[],
		अचिन्हित पूर्णांक BlockHeight256BytesY[],
		अचिन्हित पूर्णांक BlockWidth256BytesC[],
		अचिन्हित पूर्णांक BlockHeight256BytesC[],
		द्विगुन DisplayPipeLineDeliveryTimeLuma[],
		द्विगुन DisplayPipeLineDeliveryTimeChroma[],
		द्विगुन DisplayPipeLineDeliveryTimeLumaPrefetch[],
		द्विगुन DisplayPipeLineDeliveryTimeChromaPrefetch[],
		द्विगुन DisplayPipeRequestDeliveryTimeLuma[],
		द्विगुन DisplayPipeRequestDeliveryTimeChroma[],
		द्विगुन DisplayPipeRequestDeliveryTimeLumaPrefetch[],
		द्विगुन DisplayPipeRequestDeliveryTimeChromaPrefetch[])
अणु
	द्विगुन req_per_swath_ub;
	अचिन्हित पूर्णांक k;

	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		अगर (VRatio[k] <= 1) अणु
			DisplayPipeLineDeliveryTimeLuma[k] = swath_width_luma_ub[k] * DPPPerPlane[k]
					/ HRatio[k] / PixelClock[k];
		पूर्ण अन्यथा अणु
			DisplayPipeLineDeliveryTimeLuma[k] = swath_width_luma_ub[k]
					/ PSCL_THROUGHPUT[k] / DPPCLK[k];
		पूर्ण

		अगर (BytePerPixelDETC[k] == 0) अणु
			DisplayPipeLineDeliveryTimeChroma[k] = 0;
		पूर्ण अन्यथा अणु
			अगर (VRatio[k] / 2 <= 1) अणु
				DisplayPipeLineDeliveryTimeChroma[k] = swath_width_chroma_ub[k]
						* DPPPerPlane[k] / (HRatio[k] / 2) / PixelClock[k];
			पूर्ण अन्यथा अणु
				DisplayPipeLineDeliveryTimeChroma[k] = swath_width_chroma_ub[k]
						/ PSCL_THROUGHPUT_CHROMA[k] / DPPCLK[k];
			पूर्ण
		पूर्ण

		अगर (VRatioPrefetchY[k] <= 1) अणु
			DisplayPipeLineDeliveryTimeLumaPrefetch[k] = swath_width_luma_ub[k]
					* DPPPerPlane[k] / HRatio[k] / PixelClock[k];
		पूर्ण अन्यथा अणु
			DisplayPipeLineDeliveryTimeLumaPrefetch[k] = swath_width_luma_ub[k]
					/ PSCL_THROUGHPUT[k] / DPPCLK[k];
		पूर्ण

		अगर (BytePerPixelDETC[k] == 0) अणु
			DisplayPipeLineDeliveryTimeChromaPrefetch[k] = 0;
		पूर्ण अन्यथा अणु
			अगर (VRatioPrefetchC[k] <= 1) अणु
				DisplayPipeLineDeliveryTimeChromaPrefetch[k] =
						swath_width_chroma_ub[k] * DPPPerPlane[k]
								/ (HRatio[k] / 2) / PixelClock[k];
			पूर्ण अन्यथा अणु
				DisplayPipeLineDeliveryTimeChromaPrefetch[k] =
						swath_width_chroma_ub[k] / PSCL_THROUGHPUT_CHROMA[k] / DPPCLK[k];
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		अगर (SourceScan[k] == dm_horz) अणु
			req_per_swath_ub = swath_width_luma_ub[k] / BlockWidth256BytesY[k];
		पूर्ण अन्यथा अणु
			req_per_swath_ub = swath_width_luma_ub[k] / BlockHeight256BytesY[k];
		पूर्ण
		DisplayPipeRequestDeliveryTimeLuma[k] = DisplayPipeLineDeliveryTimeLuma[k]
				/ req_per_swath_ub;
		DisplayPipeRequestDeliveryTimeLumaPrefetch[k] =
				DisplayPipeLineDeliveryTimeLumaPrefetch[k] / req_per_swath_ub;
		अगर (BytePerPixelDETC[k] == 0) अणु
			DisplayPipeRequestDeliveryTimeChroma[k] = 0;
			DisplayPipeRequestDeliveryTimeChromaPrefetch[k] = 0;
		पूर्ण अन्यथा अणु
			अगर (SourceScan[k] == dm_horz) अणु
				req_per_swath_ub = swath_width_chroma_ub[k]
						/ BlockWidth256BytesC[k];
			पूर्ण अन्यथा अणु
				req_per_swath_ub = swath_width_chroma_ub[k]
						/ BlockHeight256BytesC[k];
			पूर्ण
			DisplayPipeRequestDeliveryTimeChroma[k] =
					DisplayPipeLineDeliveryTimeChroma[k] / req_per_swath_ub;
			DisplayPipeRequestDeliveryTimeChromaPrefetch[k] =
					DisplayPipeLineDeliveryTimeChromaPrefetch[k] / req_per_swath_ub;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम CalculateMetaAndPTETimes(
		अचिन्हित पूर्णांक NumberOfActivePlanes,
		bool GPUVMEnable,
		अचिन्हित पूर्णांक MetaChunkSize,
		अचिन्हित पूर्णांक MinMetaChunkSizeBytes,
		अचिन्हित पूर्णांक GPUVMMaxPageTableLevels,
		अचिन्हित पूर्णांक HTotal[],
		द्विगुन VRatio[],
		द्विगुन VRatioPrefetchY[],
		द्विगुन VRatioPrefetchC[],
		द्विगुन DestinationLinesToRequestRowInVBlank[],
		द्विगुन DestinationLinesToRequestRowInImmediateFlip[],
		द्विगुन DestinationLinesToRequestVMInVBlank[],
		द्विगुन DestinationLinesToRequestVMInImmediateFlip[],
		bool DCCEnable[],
		द्विगुन PixelClock[],
		द्विगुन BytePerPixelDETY[],
		द्विगुन BytePerPixelDETC[],
		क्रमागत scan_direction_class SourceScan[],
		अचिन्हित पूर्णांक dpte_row_height[],
		अचिन्हित पूर्णांक dpte_row_height_chroma[],
		अचिन्हित पूर्णांक meta_row_width[],
		अचिन्हित पूर्णांक meta_row_height[],
		अचिन्हित पूर्णांक meta_req_width[],
		अचिन्हित पूर्णांक meta_req_height[],
		पूर्णांक dpte_group_bytes[],
		अचिन्हित पूर्णांक PTERequestSizeY[],
		अचिन्हित पूर्णांक PTERequestSizeC[],
		अचिन्हित पूर्णांक PixelPTEReqWidthY[],
		अचिन्हित पूर्णांक PixelPTEReqHeightY[],
		अचिन्हित पूर्णांक PixelPTEReqWidthC[],
		अचिन्हित पूर्णांक PixelPTEReqHeightC[],
		अचिन्हित पूर्णांक dpte_row_width_luma_ub[],
		अचिन्हित पूर्णांक dpte_row_width_chroma_ub[],
		अचिन्हित पूर्णांक vm_group_bytes[],
		अचिन्हित पूर्णांक dpde0_bytes_per_frame_ub_l[],
		अचिन्हित पूर्णांक dpde0_bytes_per_frame_ub_c[],
		अचिन्हित पूर्णांक meta_pte_bytes_per_frame_ub_l[],
		अचिन्हित पूर्णांक meta_pte_bytes_per_frame_ub_c[],
		द्विगुन DST_Y_PER_PTE_ROW_NOM_L[],
		द्विगुन DST_Y_PER_PTE_ROW_NOM_C[],
		द्विगुन DST_Y_PER_META_ROW_NOM_L[],
		द्विगुन TimePerMetaChunkNominal[],
		द्विगुन TimePerMetaChunkVBlank[],
		द्विगुन TimePerMetaChunkFlip[],
		द्विगुन समय_per_pte_group_nom_luma[],
		द्विगुन समय_per_pte_group_vblank_luma[],
		द्विगुन समय_per_pte_group_flip_luma[],
		द्विगुन समय_per_pte_group_nom_chroma[],
		द्विगुन समय_per_pte_group_vblank_chroma[],
		द्विगुन समय_per_pte_group_flip_chroma[],
		द्विगुन TimePerVMGroupVBlank[],
		द्विगुन TimePerVMGroupFlip[],
		द्विगुन TimePerVMRequestVBlank[],
		द्विगुन TimePerVMRequestFlip[])
अणु
	अचिन्हित पूर्णांक meta_chunk_width;
	अचिन्हित पूर्णांक min_meta_chunk_width;
	अचिन्हित पूर्णांक meta_chunk_per_row_पूर्णांक;
	अचिन्हित पूर्णांक meta_row_reमुख्यder;
	अचिन्हित पूर्णांक meta_chunk_threshold;
	अचिन्हित पूर्णांक meta_chunks_per_row_ub;
	अचिन्हित पूर्णांक dpte_group_width_luma;
	अचिन्हित पूर्णांक dpte_group_width_chroma;
	अचिन्हित पूर्णांक dpte_groups_per_row_luma_ub;
	अचिन्हित पूर्णांक dpte_groups_per_row_chroma_ub;
	अचिन्हित पूर्णांक num_group_per_lower_vm_stage;
	अचिन्हित पूर्णांक num_req_per_lower_vm_stage;
	अचिन्हित पूर्णांक k;

	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		अगर (GPUVMEnable == true) अणु
			DST_Y_PER_PTE_ROW_NOM_L[k] = dpte_row_height[k] / VRatio[k];
			अगर (BytePerPixelDETC[k] == 0) अणु
				DST_Y_PER_PTE_ROW_NOM_C[k] = 0;
			पूर्ण अन्यथा अणु
				DST_Y_PER_PTE_ROW_NOM_C[k] = dpte_row_height_chroma[k] / (VRatio[k] / 2);
			पूर्ण
		पूर्ण अन्यथा अणु
			DST_Y_PER_PTE_ROW_NOM_L[k] = 0;
			DST_Y_PER_PTE_ROW_NOM_C[k] = 0;
		पूर्ण
		अगर (DCCEnable[k] == true) अणु
			DST_Y_PER_META_ROW_NOM_L[k] = meta_row_height[k] / VRatio[k];
		पूर्ण अन्यथा अणु
			DST_Y_PER_META_ROW_NOM_L[k] = 0;
		पूर्ण
	पूर्ण

	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		अगर (DCCEnable[k] == true) अणु
			meta_chunk_width = MetaChunkSize * 1024 * 256
					/ dml_उच्चमान(BytePerPixelDETY[k], 1) / meta_row_height[k];
			min_meta_chunk_width = MinMetaChunkSizeBytes * 256
					/ dml_उच्चमान(BytePerPixelDETY[k], 1) / meta_row_height[k];
			meta_chunk_per_row_पूर्णांक = meta_row_width[k] / meta_chunk_width;
			meta_row_reमुख्यder = meta_row_width[k] % meta_chunk_width;
			अगर (SourceScan[k] == dm_horz) अणु
				meta_chunk_threshold = 2 * min_meta_chunk_width - meta_req_width[k];
			पूर्ण अन्यथा अणु
				meta_chunk_threshold = 2 * min_meta_chunk_width
						- meta_req_height[k];
			पूर्ण
			अगर (meta_row_reमुख्यder <= meta_chunk_threshold) अणु
				meta_chunks_per_row_ub = meta_chunk_per_row_पूर्णांक + 1;
			पूर्ण अन्यथा अणु
				meta_chunks_per_row_ub = meta_chunk_per_row_पूर्णांक + 2;
			पूर्ण
			TimePerMetaChunkNominal[k] = meta_row_height[k] / VRatio[k] * HTotal[k]
					/ PixelClock[k] / meta_chunks_per_row_ub;
			TimePerMetaChunkVBlank[k] = DestinationLinesToRequestRowInVBlank[k]
					* HTotal[k] / PixelClock[k] / meta_chunks_per_row_ub;
			TimePerMetaChunkFlip[k] = DestinationLinesToRequestRowInImmediateFlip[k]
					* HTotal[k] / PixelClock[k] / meta_chunks_per_row_ub;
		पूर्ण अन्यथा अणु
			TimePerMetaChunkNominal[k] = 0;
			TimePerMetaChunkVBlank[k] = 0;
			TimePerMetaChunkFlip[k] = 0;
		पूर्ण
	पूर्ण

	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		अगर (GPUVMEnable == true) अणु
			अगर (SourceScan[k] == dm_horz) अणु
				dpte_group_width_luma = dpte_group_bytes[k] / PTERequestSizeY[k]
						* PixelPTEReqWidthY[k];
			पूर्ण अन्यथा अणु
				dpte_group_width_luma = dpte_group_bytes[k] / PTERequestSizeY[k]
						* PixelPTEReqHeightY[k];
			पूर्ण
			dpte_groups_per_row_luma_ub = dml_उच्चमान(
					(भग्न) dpte_row_width_luma_ub[k] / dpte_group_width_luma,
					1);
			समय_per_pte_group_nom_luma[k] = DST_Y_PER_PTE_ROW_NOM_L[k] * HTotal[k]
					/ PixelClock[k] / dpte_groups_per_row_luma_ub;
			समय_per_pte_group_vblank_luma[k] = DestinationLinesToRequestRowInVBlank[k]
					* HTotal[k] / PixelClock[k] / dpte_groups_per_row_luma_ub;
			समय_per_pte_group_flip_luma[k] =
					DestinationLinesToRequestRowInImmediateFlip[k] * HTotal[k]
							/ PixelClock[k]
							/ dpte_groups_per_row_luma_ub;
			अगर (BytePerPixelDETC[k] == 0) अणु
				समय_per_pte_group_nom_chroma[k] = 0;
				समय_per_pte_group_vblank_chroma[k] = 0;
				समय_per_pte_group_flip_chroma[k] = 0;
			पूर्ण अन्यथा अणु
				अगर (SourceScan[k] == dm_horz) अणु
					dpte_group_width_chroma = dpte_group_bytes[k]
							/ PTERequestSizeC[k] * PixelPTEReqWidthC[k];
				पूर्ण अन्यथा अणु
					dpte_group_width_chroma = dpte_group_bytes[k]
							/ PTERequestSizeC[k]
							* PixelPTEReqHeightC[k];
				पूर्ण
				dpte_groups_per_row_chroma_ub = dml_उच्चमान(
						(भग्न) dpte_row_width_chroma_ub[k]
								/ dpte_group_width_chroma,
						1);
				समय_per_pte_group_nom_chroma[k] = DST_Y_PER_PTE_ROW_NOM_C[k]
						* HTotal[k] / PixelClock[k]
						/ dpte_groups_per_row_chroma_ub;
				समय_per_pte_group_vblank_chroma[k] =
						DestinationLinesToRequestRowInVBlank[k] * HTotal[k]
								/ PixelClock[k]
								/ dpte_groups_per_row_chroma_ub;
				समय_per_pte_group_flip_chroma[k] =
						DestinationLinesToRequestRowInImmediateFlip[k]
								* HTotal[k] / PixelClock[k]
								/ dpte_groups_per_row_chroma_ub;
			पूर्ण
		पूर्ण अन्यथा अणु
			समय_per_pte_group_nom_luma[k] = 0;
			समय_per_pte_group_vblank_luma[k] = 0;
			समय_per_pte_group_flip_luma[k] = 0;
			समय_per_pte_group_nom_chroma[k] = 0;
			समय_per_pte_group_vblank_chroma[k] = 0;
			समय_per_pte_group_flip_chroma[k] = 0;
		पूर्ण
	पूर्ण

	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		अगर (GPUVMEnable == true && (DCCEnable[k] == true || GPUVMMaxPageTableLevels > 1)) अणु
			अगर (DCCEnable[k] == false) अणु
				अगर (BytePerPixelDETC[k] > 0) अणु
					num_group_per_lower_vm_stage =
						dml_उच्चमान((द्विगुन) (dpde0_bytes_per_frame_ub_l[k]) / (द्विगुन) (vm_group_bytes[k]), 1)
						+ dml_उच्चमान((द्विगुन) (dpde0_bytes_per_frame_ub_c[k]) / (द्विगुन) (vm_group_bytes[k]), 1);
				पूर्ण अन्यथा अणु
					num_group_per_lower_vm_stage =
							dml_उच्चमान((द्विगुन) (dpde0_bytes_per_frame_ub_l[k]) / (द्विगुन) (vm_group_bytes[k]), 1);
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (GPUVMMaxPageTableLevels == 1) अणु
					अगर (BytePerPixelDETC[k] > 0) अणु
						num_group_per_lower_vm_stage =
							dml_उच्चमान((द्विगुन) (meta_pte_bytes_per_frame_ub_l[k]) / (द्विगुन) (vm_group_bytes[k]), 1)
							+ dml_उच्चमान((द्विगुन) (meta_pte_bytes_per_frame_ub_c[k]) / (द्विगुन) (vm_group_bytes[k]), 1);
					पूर्ण अन्यथा अणु
						num_group_per_lower_vm_stage =
							dml_उच्चमान((द्विगुन) (meta_pte_bytes_per_frame_ub_l[k]) / (द्विगुन) (vm_group_bytes[k]), 1);
					पूर्ण
				पूर्ण अन्यथा अणु
					अगर (BytePerPixelDETC[k] > 0) अणु
						num_group_per_lower_vm_stage =
							dml_उच्चमान((द्विगुन) (dpde0_bytes_per_frame_ub_l[k]) / (द्विगुन) (vm_group_bytes[k]), 1)
							+ dml_उच्चमान((द्विगुन) (dpde0_bytes_per_frame_ub_c[k]) / (द्विगुन) (vm_group_bytes[k]), 1)
							+ dml_उच्चमान((द्विगुन) (meta_pte_bytes_per_frame_ub_l[k]) / (द्विगुन) (vm_group_bytes[k]), 1)
							+ dml_उच्चमान((द्विगुन) (meta_pte_bytes_per_frame_ub_c[k]) / (द्विगुन) (vm_group_bytes[k]), 1);
					पूर्ण अन्यथा अणु
						num_group_per_lower_vm_stage =
							dml_उच्चमान((द्विगुन) (dpde0_bytes_per_frame_ub_l[k]) / (द्विगुन) (vm_group_bytes[k]), 1)
							+ dml_उच्चमान((द्विगुन) (meta_pte_bytes_per_frame_ub_l[k]) / (द्विगुन) (vm_group_bytes[k]), 1);
					पूर्ण
				पूर्ण
			पूर्ण

			अगर (DCCEnable[k] == false) अणु
				अगर (BytePerPixelDETC[k] > 0) अणु
					num_req_per_lower_vm_stage = dpde0_bytes_per_frame_ub_l[k]
							/ 64 + dpde0_bytes_per_frame_ub_c[k] / 64;
				पूर्ण अन्यथा अणु
					num_req_per_lower_vm_stage = dpde0_bytes_per_frame_ub_l[k]
							/ 64;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (GPUVMMaxPageTableLevels == 1) अणु
					अगर (BytePerPixelDETC[k] > 0) अणु
						num_req_per_lower_vm_stage = meta_pte_bytes_per_frame_ub_l[k] / 64
							+ meta_pte_bytes_per_frame_ub_c[k] / 64;
					पूर्ण अन्यथा अणु
						num_req_per_lower_vm_stage = meta_pte_bytes_per_frame_ub_l[k] / 64;
					पूर्ण
				पूर्ण अन्यथा अणु
					अगर (BytePerPixelDETC[k] > 0) अणु
						num_req_per_lower_vm_stage = dpde0_bytes_per_frame_ub_l[k] / 64
							+ dpde0_bytes_per_frame_ub_c[k] / 64
							+ meta_pte_bytes_per_frame_ub_l[k] / 64
							+ meta_pte_bytes_per_frame_ub_c[k] / 64;
					पूर्ण अन्यथा अणु
						num_req_per_lower_vm_stage = dpde0_bytes_per_frame_ub_l[k] / 64
							+ meta_pte_bytes_per_frame_ub_l[k] / 64;
					पूर्ण
				पूर्ण
			पूर्ण

			TimePerVMGroupVBlank[k] = DestinationLinesToRequestVMInVBlank[k] * HTotal[k]
					/ PixelClock[k] / num_group_per_lower_vm_stage;
			TimePerVMGroupFlip[k] = DestinationLinesToRequestVMInImmediateFlip[k]
					* HTotal[k] / PixelClock[k] / num_group_per_lower_vm_stage;
			TimePerVMRequestVBlank[k] = DestinationLinesToRequestVMInVBlank[k]
					* HTotal[k] / PixelClock[k] / num_req_per_lower_vm_stage;
			TimePerVMRequestFlip[k] = DestinationLinesToRequestVMInImmediateFlip[k]
					* HTotal[k] / PixelClock[k] / num_req_per_lower_vm_stage;

			अगर (GPUVMMaxPageTableLevels > 2) अणु
				TimePerVMGroupVBlank[k] = TimePerVMGroupVBlank[k] / 2;
				TimePerVMGroupFlip[k] = TimePerVMGroupFlip[k] / 2;
				TimePerVMRequestVBlank[k] = TimePerVMRequestVBlank[k] / 2;
				TimePerVMRequestFlip[k] = TimePerVMRequestFlip[k] / 2;
			पूर्ण

		पूर्ण अन्यथा अणु
			TimePerVMGroupVBlank[k] = 0;
			TimePerVMGroupFlip[k] = 0;
			TimePerVMRequestVBlank[k] = 0;
			TimePerVMRequestFlip[k] = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल द्विगुन CalculateExtraLatency(
		द्विगुन UrgentRoundTripAndOutOfOrderLatency,
		पूर्णांक TotalNumberOfActiveDPP,
		पूर्णांक PixelChunkSizeInKByte,
		पूर्णांक TotalNumberOfDCCActiveDPP,
		पूर्णांक MetaChunkSize,
		द्विगुन ReturnBW,
		bool GPUVMEnable,
		bool HostVMEnable,
		पूर्णांक NumberOfActivePlanes,
		पूर्णांक NumberOfDPP[],
		पूर्णांक dpte_group_bytes[],
		द्विगुन PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData,
		द्विगुन PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly,
		पूर्णांक HostVMMaxPageTableLevels,
		पूर्णांक HostVMCachedPageTableLevels)
अणु
	द्विगुन CalculateExtraLatency;
	द्विगुन HostVMInefficiencyFactor;
	पूर्णांक HostVMDynamicLevels;

	अगर (GPUVMEnable && HostVMEnable) अणु
		HostVMInefficiencyFactor =
				PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData
						/ PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly;
		HostVMDynamicLevels = HostVMMaxPageTableLevels - HostVMCachedPageTableLevels;
	पूर्ण अन्यथा अणु
		HostVMInefficiencyFactor = 1;
		HostVMDynamicLevels = 0;
	पूर्ण

	CalculateExtraLatency = UrgentRoundTripAndOutOfOrderLatency
			+ (TotalNumberOfActiveDPP * PixelChunkSizeInKByte
					+ TotalNumberOfDCCActiveDPP * MetaChunkSize) * 1024.0
					/ ReturnBW;

	अगर (GPUVMEnable) अणु
		पूर्णांक k;

		क्रम (k = 0; k < NumberOfActivePlanes; k++) अणु
			CalculateExtraLatency = CalculateExtraLatency
					+ NumberOfDPP[k] * dpte_group_bytes[k]
							* (1 + 8 * HostVMDynamicLevels)
							* HostVMInefficiencyFactor / ReturnBW;
		पूर्ण
	पूर्ण
	वापस CalculateExtraLatency;
पूर्ण

