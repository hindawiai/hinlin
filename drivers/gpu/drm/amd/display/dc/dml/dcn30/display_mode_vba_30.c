<शैली गुरु>
/*
 * Copyright 2020 Advanced Micro Devices, Inc.
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

#अगर_घोषित CONFIG_DRM_AMD_DC_DCN
#समावेश "dc.h"
#समावेश "dc_link.h"
#समावेश "../display_mode_lib.h"
#समावेश "display_mode_vba_30.h"
#समावेश "../dml_inline_defs.h"


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
	अचिन्हित पूर्णांक DCCEnable;
	bool ODMCombineEnabled;
पूर्ण Pipe;

#घोषणा BPP_INVALID 0
#घोषणा BPP_BLENDED_PIPE 0xffffffff
#घोषणा DCN30_MAX_DSC_IMAGE_WIDTH 5184

अटल व्योम DisplayPipeConfiguration(काष्ठा display_mode_lib *mode_lib);
अटल व्योम DISPCLKDPPCLKDCFCLKDeepSleepPrefetchParametersWatermarksAndPerक्रमmanceCalculation(
		काष्ठा display_mode_lib *mode_lib);
अटल अचिन्हित पूर्णांक dscceComputeDelay(
		अचिन्हित पूर्णांक bpc,
		द्विगुन BPP,
		अचिन्हित पूर्णांक sliceWidth,
		अचिन्हित पूर्णांक numSlices,
		क्रमागत output_क्रमmat_class pixelFormat,
		क्रमागत output_encoder_class Output);
अटल अचिन्हित पूर्णांक dscComputeDelay(
		क्रमागत output_क्रमmat_class pixelFormat,
		क्रमागत output_encoder_class Output);
// Super monster function with some 45 argument
अटल bool CalculatePrefetchSchedule(
		काष्ठा display_mode_lib *mode_lib,
		द्विगुन PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData,
		द्विगुन PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly,
		Pipe *myPipe,
		अचिन्हित पूर्णांक DSCDelay,
		द्विगुन DPPCLKDelaySubtotalPlusCNVCFormater,
		द्विगुन DPPCLKDelaySCL,
		द्विगुन DPPCLKDelaySCLLBOnly,
		द्विगुन DPPCLKDelayCNVCCursor,
		द्विगुन DISPCLKDelaySubtotal,
		अचिन्हित पूर्णांक DPP_RECOUT_WIDTH,
		क्रमागत output_क्रमmat_class OutputFormat,
		अचिन्हित पूर्णांक MaxInterDCNTileRepeaters,
		अचिन्हित पूर्णांक VStartup,
		अचिन्हित पूर्णांक MaxVStartup,
		अचिन्हित पूर्णांक GPUVMPageTableLevels,
		bool GPUVMEnable,
		bool HostVMEnable,
		अचिन्हित पूर्णांक HostVMMaxNonCachedPageTableLevels,
		द्विगुन HostVMMinPageSize,
		bool DynamicMetadataEnable,
		bool DynamicMetadataVMEnabled,
		पूर्णांक DynamicMetadataLinesBeक्रमeActiveRequired,
		अचिन्हित पूर्णांक DynamicMetadataTransmittedBytes,
		द्विगुन UrgentLatency,
		द्विगुन UrgentExtraLatency,
		द्विगुन TCalc,
		अचिन्हित पूर्णांक PDEAndMetaPTEBytesFrame,
		अचिन्हित पूर्णांक MetaRowByte,
		अचिन्हित पूर्णांक PixelPTEBytesPerRow,
		द्विगुन PrefetchSourceLinesY,
		अचिन्हित पूर्णांक SwathWidthY,
		पूर्णांक BytePerPixelY,
		द्विगुन VInitPreFillY,
		अचिन्हित पूर्णांक MaxNumSwathY,
		द्विगुन PrefetchSourceLinesC,
		अचिन्हित पूर्णांक SwathWidthC,
		पूर्णांक BytePerPixelC,
		द्विगुन VInitPreFillC,
		अचिन्हित पूर्णांक MaxNumSwathC,
		दीर्घ swath_width_luma_ub,
		दीर्घ swath_width_chroma_ub,
		अचिन्हित पूर्णांक SwathHeightY,
		अचिन्हित पूर्णांक SwathHeightC,
		द्विगुन TWait,
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
		bool *NotEnoughTimeForDynamicMetadata,
		द्विगुन *Tno_bw,
		द्विगुन *prefetch_vmrow_bw,
		द्विगुन *Tdmdl_vm,
		द्विगुन *Tdmdl,
		अचिन्हित पूर्णांक *VUpdateOffsetPix,
		द्विगुन *VUpdateWidthPix,
		द्विगुन *VReadyOffsetPix);
अटल द्विगुन RoundToDFSGranularityUp(द्विगुन Clock, द्विगुन VCOSpeed);
अटल द्विगुन RoundToDFSGranularityDown(द्विगुन Clock, द्विगुन VCOSpeed);
अटल व्योम CalculateDCCConfiguration(
		bool DCCEnabled,
		bool DCCProgrammingAssumesScanDirectionUnknown,
		क्रमागत source_क्रमmat_class SourcePixelFormat,
		अचिन्हित पूर्णांक ViewportWidthLuma,
		अचिन्हित पूर्णांक ViewportWidthChroma,
		अचिन्हित पूर्णांक ViewportHeightLuma,
		अचिन्हित पूर्णांक ViewportHeightChroma,
		द्विगुन DETBufferSize,
		अचिन्हित पूर्णांक RequestHeight256ByteLuma,
		अचिन्हित पूर्णांक RequestHeight256ByteChroma,
		क्रमागत dm_swizzle_mode TilingFormat,
		अचिन्हित पूर्णांक BytePerPixelY,
		अचिन्हित पूर्णांक BytePerPixelC,
		द्विगुन BytePerPixelDETY,
		द्विगुन BytePerPixelDETC,
		क्रमागत scan_direction_class ScanOrientation,
		अचिन्हित पूर्णांक *MaxUncompressedBlockLuma,
		अचिन्हित पूर्णांक *MaxUncompressedBlockChroma,
		अचिन्हित पूर्णांक *MaxCompressedBlockLuma,
		अचिन्हित पूर्णांक *MaxCompressedBlockChroma,
		अचिन्हित पूर्णांक *IndependentBlockLuma,
		अचिन्हित पूर्णांक *IndependentBlockChroma);
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
		अचिन्हित पूर्णांक SwathWidth,
		अचिन्हित पूर्णांक ViewportHeight,
		bool GPUVMEnable,
		bool HostVMEnable,
		अचिन्हित पूर्णांक HostVMMaxNonCachedPageTableLevels,
		अचिन्हित पूर्णांक GPUVMMinPageSize,
		अचिन्हित पूर्णांक HostVMMinPageSize,
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
अटल व्योम CalculateRowBandwidth(
		bool GPUVMEnable,
		क्रमागत source_क्रमmat_class SourcePixelFormat,
		द्विगुन VRatio,
		द्विगुन VRatioChroma,
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
		अचिन्हित पूर्णांक HostVMMaxNonCachedPageTableLevels,
		bool GPUVMEnable,
		द्विगुन HostVMMinPageSize,
		द्विगुन PDEAndMetaPTEBytesPerFrame,
		द्विगुन MetaRowBytes,
		द्विगुन DPTEBytesPerRow,
		द्विगुन BandwidthAvailableForImmediateFlip,
		अचिन्हित पूर्णांक TotImmediateFlipBytes,
		क्रमागत source_क्रमmat_class SourcePixelFormat,
		द्विगुन LineTime,
		द्विगुन VRatio,
		द्विगुन VRatioChroma,
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
		अचिन्हित पूर्णांक WritebackVTaps,
		दीर्घ WritebackDestinationWidth,
		दीर्घ WritebackDestinationHeight,
		दीर्घ WritebackSourceHeight,
		अचिन्हित पूर्णांक HTotal);
अटल व्योम CalculateDynamicMetadataParameters(
		पूर्णांक MaxInterDCNTileRepeaters,
		द्विगुन DPPCLK,
		द्विगुन DISPCLK,
		द्विगुन DCFClkDeepSleep,
		द्विगुन PixelClock,
		दीर्घ HTotal,
		दीर्घ VBlank,
		दीर्घ DynamicMetadataTransmittedBytes,
		दीर्घ DynamicMetadataLinesBeक्रमeActiveRequired,
		पूर्णांक InterlaceEnable,
		bool ProgressiveToInterlaceUnitInOPP,
		द्विगुन *Tsetup,
		द्विगुन *Tdmbf,
		द्विगुन *Tdmec,
		द्विगुन *Tdmsks);
अटल व्योम CalculateWatermarksAndDRAMSpeedChangeSupport(
		काष्ठा display_mode_lib *mode_lib,
		अचिन्हित पूर्णांक PrefetchMode,
		अचिन्हित पूर्णांक NumberOfActivePlanes,
		अचिन्हित पूर्णांक MaxLineBufferLines,
		अचिन्हित पूर्णांक LineBufferSize,
		अचिन्हित पूर्णांक DPPOutputBufferPixels,
		द्विगुन DETBufferSizeInKByte,
		अचिन्हित पूर्णांक WritebackInterfaceBufferSize,
		द्विगुन DCFCLK,
		द्विगुन ReturnBW,
		bool GPUVMEnable,
		अचिन्हित पूर्णांक dpte_group_bytes[],
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
		अचिन्हित पूर्णांक DPPPerPlane[],
		bool DCCEnable[],
		द्विगुन DPPCLK[],
		द्विगुन DETBufferSizeY[],
		द्विगुन DETBufferSizeC[],
		अचिन्हित पूर्णांक SwathHeightY[],
		अचिन्हित पूर्णांक SwathHeightC[],
		अचिन्हित पूर्णांक LBBitPerPixel[],
		द्विगुन SwathWidthY[],
		द्विगुन SwathWidthC[],
		द्विगुन HRatio[],
		द्विगुन HRatioChroma[],
		अचिन्हित पूर्णांक vtaps[],
		अचिन्हित पूर्णांक VTAPsChroma[],
		द्विगुन VRatio[],
		द्विगुन VRatioChroma[],
		अचिन्हित पूर्णांक HTotal[],
		द्विगुन PixelClock[],
		अचिन्हित पूर्णांक BlendingAndTiming[],
		द्विगुन BytePerPixelDETY[],
		द्विगुन BytePerPixelDETC[],
		द्विगुन DSTXAfterScaler[],
		द्विगुन DSTYAfterScaler[],
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
		पूर्णांक BytePerPixelY[],
		पूर्णांक BytePerPixelC[],
		द्विगुन VRatio[],
		द्विगुन VRatioChroma[],
		द्विगुन SwathWidthY[],
		द्विगुन SwathWidthC[],
		अचिन्हित पूर्णांक DPPPerPlane[],
		द्विगुन HRatio[],
		द्विगुन HRatioChroma[],
		द्विगुन PixelClock[],
		द्विगुन PSCL_THROUGHPUT[],
		द्विगुन PSCL_THROUGHPUT_CHROMA[],
		द्विगुन DPPCLK[],
		द्विगुन ReadBandwidthLuma[],
		द्विगुन ReadBandwidthChroma[],
		पूर्णांक ReturnBusWidth,
		द्विगुन *DCFCLKDeepSleep);
अटल व्योम CalculateUrgentBurstFactor(
		दीर्घ swath_width_luma_ub,
		दीर्घ swath_width_chroma_ub,
		अचिन्हित पूर्णांक DETBufferSizeInKByte,
		अचिन्हित पूर्णांक SwathHeightY,
		अचिन्हित पूर्णांक SwathHeightC,
		द्विगुन LineTime,
		द्विगुन UrgentLatency,
		द्विगुन CursorBufferSize,
		अचिन्हित पूर्णांक CursorWidth,
		अचिन्हित पूर्णांक CursorBPP,
		द्विगुन VRatio,
		द्विगुन VRatioC,
		द्विगुन BytePerPixelInDETY,
		द्विगुन BytePerPixelInDETC,
		द्विगुन DETBufferSizeY,
		द्विगुन DETBufferSizeC,
		द्विगुन *UrgentBurstFactorCursor,
		द्विगुन *UrgentBurstFactorLuma,
		द्विगुन *UrgentBurstFactorChroma,
		bool *NotEnoughUrgentLatencyHiding);

अटल व्योम UseMinimumDCFCLK(
		काष्ठा display_mode_lib *mode_lib,
		पूर्णांक MaxInterDCNTileRepeaters,
		पूर्णांक MaxPrefetchMode,
		द्विगुन FinalDRAMClockChangeLatency,
		द्विगुन SREnterPlusExitTime,
		पूर्णांक ReturnBusWidth,
		पूर्णांक RoundTripPingLatencyCycles,
		पूर्णांक ReorderingBytes,
		पूर्णांक PixelChunkSizeInKByte,
		पूर्णांक MetaChunkSize,
		bool GPUVMEnable,
		पूर्णांक GPUVMMaxPageTableLevels,
		bool HostVMEnable,
		पूर्णांक NumberOfActivePlanes,
		द्विगुन HostVMMinPageSize,
		पूर्णांक HostVMMaxNonCachedPageTableLevels,
		bool DynamicMetadataVMEnabled,
		क्रमागत immediate_flip_requirement ImmediateFlipRequirement,
		bool ProgressiveToInterlaceUnitInOPP,
		द्विगुन MaxAveragePercentOfIdealSDPPortBWDisplayCanUseInNormalSystemOperation,
		द्विगुन PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData,
		द्विगुन PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly,
		द्विगुन PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelDataOnly,
		पूर्णांक VTotal[],
		पूर्णांक VActive[],
		पूर्णांक DynamicMetadataTransmittedBytes[],
		पूर्णांक DynamicMetadataLinesBeक्रमeActiveRequired[],
		bool Interlace[],
		द्विगुन RequiredDPPCLK[][2][DC__NUM_DPP__MAX],
		द्विगुन RequiredDISPCLK[][2],
		द्विगुन UrgLatency[],
		अचिन्हित पूर्णांक NoOfDPP[][2][DC__NUM_DPP__MAX],
		द्विगुन ProjectedDCFCLKDeepSleep[][2],
		द्विगुन MaximumVStartup[][2][DC__NUM_DPP__MAX],
		द्विगुन TotalVActivePixelBandwidth[][2],
		द्विगुन TotalVActiveCursorBandwidth[][2],
		द्विगुन TotalMetaRowBandwidth[][2],
		द्विगुन TotalDPTERowBandwidth[][2],
		अचिन्हित पूर्णांक TotalNumberOfActiveDPP[][2],
		अचिन्हित पूर्णांक TotalNumberOfDCCActiveDPP[][2],
		पूर्णांक dpte_group_bytes[],
		द्विगुन PrefetchLinesY[][2][DC__NUM_DPP__MAX],
		द्विगुन PrefetchLinesC[][2][DC__NUM_DPP__MAX],
		पूर्णांक swath_width_luma_ub_all_states[][2][DC__NUM_DPP__MAX],
		पूर्णांक swath_width_chroma_ub_all_states[][2][DC__NUM_DPP__MAX],
		पूर्णांक BytePerPixelY[],
		पूर्णांक BytePerPixelC[],
		पूर्णांक HTotal[],
		द्विगुन PixelClock[],
		द्विगुन PDEAndMetaPTEBytesPerFrame[][2][DC__NUM_DPP__MAX],
		द्विगुन DPTEBytesPerRow[][2][DC__NUM_DPP__MAX],
		द्विगुन MetaRowBytes[][2][DC__NUM_DPP__MAX],
		bool DynamicMetadataEnable[],
		द्विगुन VActivePixelBandwidth[][2][DC__NUM_DPP__MAX],
		द्विगुन VActiveCursorBandwidth[][2][DC__NUM_DPP__MAX],
		द्विगुन ReadBandwidthLuma[],
		द्विगुन ReadBandwidthChroma[],
		द्विगुन DCFCLKPerState[],
		द्विगुन DCFCLKState[][2]);
अटल व्योम CalculatePixelDeliveryTimes(
		अचिन्हित पूर्णांक NumberOfActivePlanes,
		द्विगुन VRatio[],
		द्विगुन VRatioChroma[],
		द्विगुन VRatioPrefetchY[],
		द्विगुन VRatioPrefetchC[],
		अचिन्हित पूर्णांक swath_width_luma_ub[],
		अचिन्हित पूर्णांक swath_width_chroma_ub[],
		अचिन्हित पूर्णांक DPPPerPlane[],
		द्विगुन HRatio[],
		द्विगुन HRatioChroma[],
		द्विगुन PixelClock[],
		द्विगुन PSCL_THROUGHPUT[],
		द्विगुन PSCL_THROUGHPUT_CHROMA[],
		द्विगुन DPPCLK[],
		पूर्णांक BytePerPixelC[],
		क्रमागत scan_direction_class SourceScan[],
		अचिन्हित पूर्णांक NumberOfCursors[],
		अचिन्हित पूर्णांक CursorWidth[][2],
		अचिन्हित पूर्णांक CursorBPP[][2],
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
		द्विगुन DisplayPipeRequestDeliveryTimeChromaPrefetch[],
		द्विगुन CursorRequestDeliveryTime[],
		द्विगुन CursorRequestDeliveryTimePrefetch[]);

अटल व्योम CalculateMetaAndPTETimes(
		पूर्णांक NumberOfActivePlanes,
		bool GPUVMEnable,
		पूर्णांक MetaChunkSize,
		पूर्णांक MinMetaChunkSizeBytes,
		पूर्णांक HTotal[],
		द्विगुन VRatio[],
		द्विगुन VRatioChroma[],
		द्विगुन DestinationLinesToRequestRowInVBlank[],
		द्विगुन DestinationLinesToRequestRowInImmediateFlip[],
		bool DCCEnable[],
		द्विगुन PixelClock[],
		पूर्णांक BytePerPixelY[],
		पूर्णांक BytePerPixelC[],
		क्रमागत scan_direction_class SourceScan[],
		पूर्णांक dpte_row_height[],
		पूर्णांक dpte_row_height_chroma[],
		पूर्णांक meta_row_width[],
		पूर्णांक meta_row_width_chroma[],
		पूर्णांक meta_row_height[],
		पूर्णांक meta_row_height_chroma[],
		पूर्णांक meta_req_width[],
		पूर्णांक meta_req_width_chroma[],
		पूर्णांक meta_req_height[],
		पूर्णांक meta_req_height_chroma[],
		पूर्णांक dpte_group_bytes[],
		पूर्णांक PTERequestSizeY[],
		पूर्णांक PTERequestSizeC[],
		पूर्णांक PixelPTEReqWidthY[],
		पूर्णांक PixelPTEReqHeightY[],
		पूर्णांक PixelPTEReqWidthC[],
		पूर्णांक PixelPTEReqHeightC[],
		पूर्णांक dpte_row_width_luma_ub[],
		पूर्णांक dpte_row_width_chroma_ub[],
		द्विगुन DST_Y_PER_PTE_ROW_NOM_L[],
		द्विगुन DST_Y_PER_PTE_ROW_NOM_C[],
		द्विगुन DST_Y_PER_META_ROW_NOM_L[],
		द्विगुन DST_Y_PER_META_ROW_NOM_C[],
		द्विगुन TimePerMetaChunkNominal[],
		द्विगुन TimePerChromaMetaChunkNominal[],
		द्विगुन TimePerMetaChunkVBlank[],
		द्विगुन TimePerChromaMetaChunkVBlank[],
		द्विगुन TimePerMetaChunkFlip[],
		द्विगुन TimePerChromaMetaChunkFlip[],
		द्विगुन समय_per_pte_group_nom_luma[],
		द्विगुन समय_per_pte_group_vblank_luma[],
		द्विगुन समय_per_pte_group_flip_luma[],
		द्विगुन समय_per_pte_group_nom_chroma[],
		द्विगुन समय_per_pte_group_vblank_chroma[],
		द्विगुन समय_per_pte_group_flip_chroma[]);

अटल व्योम CalculateVMGroupAndRequestTimes(
		अचिन्हित पूर्णांक NumberOfActivePlanes,
		bool GPUVMEnable,
		अचिन्हित पूर्णांक GPUVMMaxPageTableLevels,
		अचिन्हित पूर्णांक HTotal[],
		पूर्णांक BytePerPixelC[],
		द्विगुन DestinationLinesToRequestVMInVBlank[],
		द्विगुन DestinationLinesToRequestVMInImmediateFlip[],
		bool DCCEnable[],
		द्विगुन PixelClock[],
		पूर्णांक dpte_row_width_luma_ub[],
		पूर्णांक dpte_row_width_chroma_ub[],
		पूर्णांक vm_group_bytes[],
		अचिन्हित पूर्णांक dpde0_bytes_per_frame_ub_l[],
		अचिन्हित पूर्णांक dpde0_bytes_per_frame_ub_c[],
		पूर्णांक meta_pte_bytes_per_frame_ub_l[],
		पूर्णांक meta_pte_bytes_per_frame_ub_c[],
		द्विगुन TimePerVMGroupVBlank[],
		द्विगुन TimePerVMGroupFlip[],
		द्विगुन TimePerVMRequestVBlank[],
		द्विगुन TimePerVMRequestFlip[]);

अटल व्योम CalculateStutterEfficiency(
		पूर्णांक NumberOfActivePlanes,
		दीर्घ ROBBufferSizeInKByte,
		द्विगुन TotalDataReadBandwidth,
		द्विगुन DCFCLK,
		द्विगुन ReturnBW,
		द्विगुन SRExitTime,
		bool SynchronizedVBlank,
		पूर्णांक DPPPerPlane[],
		द्विगुन DETBufferSizeY[],
		पूर्णांक BytePerPixelY[],
		द्विगुन BytePerPixelDETY[],
		द्विगुन SwathWidthY[],
		पूर्णांक SwathHeightY[],
		पूर्णांक SwathHeightC[],
		द्विगुन DCCRateLuma[],
		द्विगुन DCCRateChroma[],
		पूर्णांक HTotal[],
		पूर्णांक VTotal[],
		द्विगुन PixelClock[],
		द्विगुन VRatio[],
		क्रमागत scan_direction_class SourceScan[],
		पूर्णांक BlockHeight256BytesY[],
		पूर्णांक BlockWidth256BytesY[],
		पूर्णांक BlockHeight256BytesC[],
		पूर्णांक BlockWidth256BytesC[],
		पूर्णांक DCCYMaxUncompressedBlock[],
		पूर्णांक DCCCMaxUncompressedBlock[],
		पूर्णांक VActive[],
		bool DCCEnable[],
		bool WritebackEnable[],
		द्विगुन ReadBandwidthPlaneLuma[],
		द्विगुन ReadBandwidthPlaneChroma[],
		द्विगुन meta_row_bw[],
		द्विगुन dpte_row_bw[],
		द्विगुन *StutterEfficiencyNotIncludingVBlank,
		द्विगुन *StutterEfficiency,
		द्विगुन *StutterPeriodOut);

अटल व्योम CalculateSwathAndDETConfiguration(
		bool ForceSingleDPP,
		पूर्णांक NumberOfActivePlanes,
		दीर्घ DETBufferSizeInKByte,
		द्विगुन MaximumSwathWidthLuma[],
		द्विगुन MaximumSwathWidthChroma[],
		क्रमागत scan_direction_class SourceScan[],
		क्रमागत source_क्रमmat_class SourcePixelFormat[],
		क्रमागत dm_swizzle_mode SurfaceTiling[],
		पूर्णांक ViewportWidth[],
		पूर्णांक ViewportHeight[],
		पूर्णांक SurfaceWidthY[],
		पूर्णांक SurfaceWidthC[],
		पूर्णांक SurfaceHeightY[],
		पूर्णांक SurfaceHeightC[],
		पूर्णांक Read256BytesBlockHeightY[],
		पूर्णांक Read256BytesBlockHeightC[],
		पूर्णांक Read256BytesBlockWidthY[],
		पूर्णांक Read256BytesBlockWidthC[],
		क्रमागत odm_combine_mode ODMCombineEnabled[],
		पूर्णांक BlendingAndTiming[],
		पूर्णांक BytePerPixY[],
		पूर्णांक BytePerPixC[],
		द्विगुन BytePerPixDETY[],
		द्विगुन BytePerPixDETC[],
		पूर्णांक HActive[],
		द्विगुन HRatio[],
		द्विगुन HRatioChroma[],
		पूर्णांक DPPPerPlane[],
		पूर्णांक swath_width_luma_ub[],
		पूर्णांक swath_width_chroma_ub[],
		द्विगुन SwathWidth[],
		द्विगुन SwathWidthChroma[],
		पूर्णांक SwathHeightY[],
		पूर्णांक SwathHeightC[],
		द्विगुन DETBufferSizeY[],
		द्विगुन DETBufferSizeC[],
		bool ViewportSizeSupportPerPlane[],
		bool *ViewportSizeSupport);
अटल व्योम CalculateSwathWidth(
		bool ForceSingleDPP,
		पूर्णांक NumberOfActivePlanes,
		क्रमागत source_क्रमmat_class SourcePixelFormat[],
		क्रमागत scan_direction_class SourceScan[],
		अचिन्हित पूर्णांक ViewportWidth[],
		अचिन्हित पूर्णांक ViewportHeight[],
		अचिन्हित पूर्णांक SurfaceWidthY[],
		अचिन्हित पूर्णांक SurfaceWidthC[],
		अचिन्हित पूर्णांक SurfaceHeightY[],
		अचिन्हित पूर्णांक SurfaceHeightC[],
		क्रमागत odm_combine_mode ODMCombineEnabled[],
		पूर्णांक BytePerPixY[],
		पूर्णांक BytePerPixC[],
		पूर्णांक Read256BytesBlockHeightY[],
		पूर्णांक Read256BytesBlockHeightC[],
		पूर्णांक Read256BytesBlockWidthY[],
		पूर्णांक Read256BytesBlockWidthC[],
		पूर्णांक BlendingAndTiming[],
		अचिन्हित पूर्णांक HActive[],
		द्विगुन HRatio[],
		पूर्णांक DPPPerPlane[],
		द्विगुन SwathWidthSingleDPPY[],
		द्विगुन SwathWidthSingleDPPC[],
		द्विगुन SwathWidthY[],
		द्विगुन SwathWidthC[],
		पूर्णांक MaximumSwathHeightY[],
		पूर्णांक MaximumSwathHeightC[],
		अचिन्हित पूर्णांक swath_width_luma_ub[],
		अचिन्हित पूर्णांक swath_width_chroma_ub[]);
अटल द्विगुन CalculateExtraLatency(
		दीर्घ RoundTripPingLatencyCycles,
		दीर्घ ReorderingBytes,
		द्विगुन DCFCLK,
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
		द्विगुन HostVMMinPageSize,
		पूर्णांक HostVMMaxNonCachedPageTableLevels);
अटल द्विगुन CalculateExtraLatencyBytes(
		दीर्घ ReorderingBytes,
		पूर्णांक TotalNumberOfActiveDPP,
		पूर्णांक PixelChunkSizeInKByte,
		पूर्णांक TotalNumberOfDCCActiveDPP,
		पूर्णांक MetaChunkSize,
		bool GPUVMEnable,
		bool HostVMEnable,
		पूर्णांक NumberOfActivePlanes,
		पूर्णांक NumberOfDPP[],
		पूर्णांक dpte_group_bytes[],
		द्विगुन PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData,
		द्विगुन PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly,
		द्विगुन HostVMMinPageSize,
		पूर्णांक HostVMMaxNonCachedPageTableLevels);
अटल द्विगुन CalculateUrgentLatency(
		द्विगुन UrgentLatencyPixelDataOnly,
		द्विगुन UrgentLatencyPixelMixedWithVMData,
		द्विगुन UrgentLatencyVMDataOnly,
		bool DoUrgentLatencyAdjusपंचांगent,
		द्विगुन UrgentLatencyAdjusपंचांगentFabricClockComponent,
		द्विगुन UrgentLatencyAdjusपंचांगentFabricClockReference,
		द्विगुन FabricClockSingle);

अटल bool CalculateBytePerPixelAnd256BBlockSizes(
		क्रमागत source_क्रमmat_class SourcePixelFormat,
		क्रमागत dm_swizzle_mode SurfaceTiling,
		अचिन्हित पूर्णांक *BytePerPixelY,
		अचिन्हित पूर्णांक *BytePerPixelC,
		द्विगुन       *BytePerPixelDETY,
		द्विगुन       *BytePerPixelDETC,
		अचिन्हित पूर्णांक *BlockHeight256BytesY,
		अचिन्हित पूर्णांक *BlockHeight256BytesC,
		अचिन्हित पूर्णांक *BlockWidth256BytesY,
		अचिन्हित पूर्णांक *BlockWidth256BytesC);

व्योम dml30_recalculate(काष्ठा display_mode_lib *mode_lib)
अणु
	ModeSupportAndSystemConfiguration(mode_lib);
	PixelClockAdjusपंचांगentForProgressiveToInterlaceUnit(mode_lib);
	DisplayPipeConfiguration(mode_lib);
	DISPCLKDPPCLKDCFCLKDeepSleepPrefetchParametersWatermarksAndPerक्रमmanceCalculation(mode_lib);
पूर्ण

अटल अचिन्हित पूर्णांक dscceComputeDelay(
		अचिन्हित पूर्णांक bpc,
		द्विगुन BPP,
		अचिन्हित पूर्णांक sliceWidth,
		अचिन्हित पूर्णांक numSlices,
		क्रमागत output_क्रमmat_class pixelFormat,
		क्रमागत output_encoder_class Output)
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
	अचिन्हित पूर्णांक pixelsPerClock, lstall, D, initalXmitDelay, w, s, ix, wx, P, l0, a, ax, L,
			Delay, pixels;

	अगर (pixelFormat == dm_420)
		pixelsPerClock = 2;
	// #all other modes operate at 1 pixel per घड़ी
	अन्यथा अगर (pixelFormat == dm_444)
		pixelsPerClock = 1;
	अन्यथा अगर (pixelFormat == dm_n422)
		pixelsPerClock = 2;
	अन्यथा
		pixelsPerClock = 1;

	//initial transmit delay as per PPS
	initalXmitDelay = dml_round(rcModelSize / 2.0 / BPP / pixelsPerClock);

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
	अगर (pixelFormat == dm_420 || pixelFormat == dm_444 || pixelFormat == dm_n422)
		s = 0;
	अन्यथा
		s = 1;

	//मुख्य calculation क्रम the dscce
	ix = initalXmitDelay + 45;
	wx = (w + 2) / 3;
	P = 3 * wx - w;
	l0 = ix / w;
	a = ix + P * l0;
	ax = (a + 2) / 3 + D + 6 + 1;
	L = (ax + wx - 1) / wx;
	अगर ((ix % w) == 0 && P != 0)
		lstall = 1;
	अन्यथा
		lstall = 0;
	Delay = L * wx * (numSlices - 1) + ax + s + lstall + 22;

	//dsc processes 3 pixel containers per cycle and a container can contain 1 or 2 pixels
	pixels = Delay * 3 * pixelsPerClock;
	वापस pixels;
पूर्ण

अटल अचिन्हित पूर्णांक dscComputeDelay(क्रमागत output_क्रमmat_class pixelFormat, क्रमागत output_encoder_class Output)
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
	पूर्ण
	अन्यथा अणु
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
		द्विगुन DPPCLKDelaySubtotalPlusCNVCFormater,
		द्विगुन DPPCLKDelaySCL,
		द्विगुन DPPCLKDelaySCLLBOnly,
		द्विगुन DPPCLKDelayCNVCCursor,
		द्विगुन DISPCLKDelaySubtotal,
		अचिन्हित पूर्णांक DPP_RECOUT_WIDTH,
		क्रमागत output_क्रमmat_class OutputFormat,
		अचिन्हित पूर्णांक MaxInterDCNTileRepeaters,
		अचिन्हित पूर्णांक VStartup,
		अचिन्हित पूर्णांक MaxVStartup,
		अचिन्हित पूर्णांक GPUVMPageTableLevels,
		bool GPUVMEnable,
		bool HostVMEnable,
		अचिन्हित पूर्णांक HostVMMaxNonCachedPageTableLevels,
		द्विगुन HostVMMinPageSize,
		bool DynamicMetadataEnable,
		bool DynamicMetadataVMEnabled,
		पूर्णांक DynamicMetadataLinesBeक्रमeActiveRequired,
		अचिन्हित पूर्णांक DynamicMetadataTransmittedBytes,
		द्विगुन UrgentLatency,
		द्विगुन UrgentExtraLatency,
		द्विगुन TCalc,
		अचिन्हित पूर्णांक PDEAndMetaPTEBytesFrame,
		अचिन्हित पूर्णांक MetaRowByte,
		अचिन्हित पूर्णांक PixelPTEBytesPerRow,
		द्विगुन PrefetchSourceLinesY,
		अचिन्हित पूर्णांक SwathWidthY,
		पूर्णांक BytePerPixelY,
		द्विगुन VInitPreFillY,
		अचिन्हित पूर्णांक MaxNumSwathY,
		द्विगुन PrefetchSourceLinesC,
		अचिन्हित पूर्णांक SwathWidthC,
		पूर्णांक BytePerPixelC,
		द्विगुन VInitPreFillC,
		अचिन्हित पूर्णांक MaxNumSwathC,
		दीर्घ swath_width_luma_ub,
		दीर्घ swath_width_chroma_ub,
		अचिन्हित पूर्णांक SwathHeightY,
		अचिन्हित पूर्णांक SwathHeightC,
		द्विगुन TWait,
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
		bool *NotEnoughTimeForDynamicMetadata,
		द्विगुन *Tno_bw,
		द्विगुन *prefetch_vmrow_bw,
		द्विगुन *Tdmdl_vm,
		द्विगुन *Tdmdl,
		अचिन्हित पूर्णांक *VUpdateOffsetPix,
		द्विगुन *VUpdateWidthPix,
		द्विगुन *VReadyOffsetPix)
अणु
	bool MyError = false;
	अचिन्हित पूर्णांक DPPCycles = 0, DISPCLKCycles = 0;
	द्विगुन DSTTotalPixelsAfterScaler = 0;
	द्विगुन LineTime = 0, Tsetup = 0;
	द्विगुन dst_y_prefetch_equ = 0;
	द्विगुन Tsw_oto = 0;
	द्विगुन prefetch_bw_oto = 0;
	द्विगुन Tvm_oto = 0;
	द्विगुन Tr0_oto = 0;
	द्विगुन Tvm_oto_lines = 0;
	द्विगुन Tr0_oto_lines = 0;
	द्विगुन dst_y_prefetch_oto = 0;
	द्विगुन TimeForFetchingMetaPTE = 0;
	द्विगुन TimeForFetchingRowInVBlank = 0;
	द्विगुन LinesToRequestPrefetchPixelData = 0;
	द्विगुन HostVMInefficiencyFactor = 0;
	अचिन्हित पूर्णांक HostVMDynamicLevelsTrips = 0;
	द्विगुन trip_to_mem = 0;
	द्विगुन Tvm_trips = 0;
	द्विगुन Tr0_trips = 0;
	द्विगुन Tvm_trips_rounded = 0;
	द्विगुन Tr0_trips_rounded = 0;
	द्विगुन Lsw_oto = 0;
	द्विगुन Tpre_rounded = 0;
	द्विगुन prefetch_bw_equ = 0;
	द्विगुन Tvm_equ = 0;
	द्विगुन Tr0_equ = 0;
	द्विगुन Tdmbf = 0;
	द्विगुन Tdmec = 0;
	द्विगुन Tdmsks = 0;

	अगर (GPUVMEnable == true && HostVMEnable == true) अणु
		HostVMInefficiencyFactor = PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData / PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly;
		HostVMDynamicLevelsTrips = HostVMMaxNonCachedPageTableLevels;
	पूर्ण अन्यथा अणु
		HostVMInefficiencyFactor = 1;
		HostVMDynamicLevelsTrips = 0;
	पूर्ण

	CalculateDynamicMetadataParameters(
			MaxInterDCNTileRepeaters,
			myPipe->DPPCLK,
			myPipe->DISPCLK,
			myPipe->DCFCLKDeepSleep,
			myPipe->PixelClock,
			myPipe->HTotal,
			myPipe->VBlank,
			DynamicMetadataTransmittedBytes,
			DynamicMetadataLinesBeक्रमeActiveRequired,
			myPipe->InterlaceEnable,
			ProgressiveToInterlaceUnitInOPP,
			&Tsetup,
			&Tdmbf,
			&Tdmec,
			&Tdmsks);

	LineTime = myPipe->HTotal / myPipe->PixelClock;
	trip_to_mem = UrgentLatency;
	Tvm_trips = UrgentExtraLatency + trip_to_mem * (GPUVMPageTableLevels * (HostVMDynamicLevelsTrips + 1) - 1);

	अगर (DynamicMetadataVMEnabled == true && GPUVMEnable == true) अणु
		*Tdmdl = TWait + Tvm_trips + trip_to_mem;
	पूर्ण अन्यथा अणु
		*Tdmdl = TWait + UrgentExtraLatency;
	पूर्ण

	अगर (DynamicMetadataEnable == true) अणु
		अगर (VStartup * LineTime < Tsetup + *Tdmdl + Tdmbf + Tdmec + Tdmsks) अणु
			*NotEnoughTimeForDynamicMetadata = true;
		पूर्ण अन्यथा अणु
			*NotEnoughTimeForDynamicMetadata = false;
			dml_prपूर्णांक("DML: Not Enough Time for Dynamic Meta!\n");
			dml_prपूर्णांक("DML: Tdmbf: %fus - time for dmd transfer from dchub to dio output buffer\n", Tdmbf);
			dml_prपूर्णांक("DML: Tdmec: %fus - time dio takes to transfer dmd\n", Tdmec);
			dml_prपूर्णांक("DML: Tdmsks: %fus - time before active dmd must complete transmission at dio\n", Tdmsks);
			dml_prपूर्णांक("DML: Tdmdl: %fus - time for fabric to become ready and fetch dmd \n", *Tdmdl);
		पूर्ण
	पूर्ण अन्यथा अणु
		*NotEnoughTimeForDynamicMetadata = false;
	पूर्ण

	*Tdmdl_vm = (DynamicMetadataEnable == true && DynamicMetadataVMEnabled == true && GPUVMEnable == true ? TWait + Tvm_trips : 0);

	अगर (myPipe->ScalerEnabled)
		DPPCycles = DPPCLKDelaySubtotalPlusCNVCFormater + DPPCLKDelaySCL;
	अन्यथा
		DPPCycles = DPPCLKDelaySubtotalPlusCNVCFormater + DPPCLKDelaySCLLBOnly;

	DPPCycles = DPPCycles + myPipe->NumberOfCursors * DPPCLKDelayCNVCCursor;

	DISPCLKCycles = DISPCLKDelaySubtotal;

	अगर (myPipe->DPPCLK == 0.0 || myPipe->DISPCLK == 0.0)
		वापस true;

	*DSTXAfterScaler = DPPCycles * myPipe->PixelClock / myPipe->DPPCLK + DISPCLKCycles * myPipe->PixelClock / myPipe->DISPCLK
			+ DSCDelay;

	*DSTXAfterScaler = *DSTXAfterScaler + ((myPipe->ODMCombineEnabled)?18:0) + (myPipe->DPPPerPlane - 1) * DPP_RECOUT_WIDTH;

	अगर (OutputFormat == dm_420 || (myPipe->InterlaceEnable && ProgressiveToInterlaceUnitInOPP))
		*DSTYAfterScaler = 1;
	अन्यथा
		*DSTYAfterScaler = 0;

	DSTTotalPixelsAfterScaler = *DSTYAfterScaler * myPipe->HTotal + *DSTXAfterScaler;
	*DSTYAfterScaler = dml_न्यूनमान(DSTTotalPixelsAfterScaler / myPipe->HTotal, 1);
	*DSTXAfterScaler = DSTTotalPixelsAfterScaler - ((द्विगुन) (*DSTYAfterScaler * myPipe->HTotal));

	MyError = false;


	Tr0_trips = trip_to_mem * (HostVMDynamicLevelsTrips + 1);
	Tvm_trips_rounded = dml_उच्चमान(4.0 * Tvm_trips / LineTime, 1) / 4 * LineTime;
	Tr0_trips_rounded = dml_उच्चमान(4.0 * Tr0_trips / LineTime, 1) / 4 * LineTime;

	अगर (GPUVMEnable) अणु
		अगर (GPUVMPageTableLevels >= 3) अणु
			*Tno_bw = UrgentExtraLatency + trip_to_mem * ((GPUVMPageTableLevels - 2) - 1);
		पूर्ण अन्यथा
			*Tno_bw = 0;
	पूर्ण अन्यथा अगर (!myPipe->DCCEnable)
		*Tno_bw = LineTime;
	अन्यथा
		*Tno_bw = LineTime / 4;

	dst_y_prefetch_equ = VStartup - (Tsetup + dml_max(TWait + TCalc, *Tdmdl)) / LineTime
			- (*DSTYAfterScaler + *DSTXAfterScaler / myPipe->HTotal);

	Lsw_oto = dml_max(PrefetchSourceLinesY, PrefetchSourceLinesC);
	Tsw_oto = Lsw_oto * LineTime;

	prefetch_bw_oto = (PrefetchSourceLinesY * swath_width_luma_ub * BytePerPixelY + PrefetchSourceLinesC * swath_width_chroma_ub * BytePerPixelC) / Tsw_oto;

	अगर (GPUVMEnable == true) अणु
		Tvm_oto = dml_max3(*Tno_bw + PDEAndMetaPTEBytesFrame * HostVMInefficiencyFactor / prefetch_bw_oto,
				Tvm_trips,
				LineTime / 4.0);
	पूर्ण अन्यथा
		Tvm_oto = LineTime / 4.0;

	अगर ((GPUVMEnable == true || myPipe->DCCEnable == true)) अणु
		Tr0_oto = dml_max3(
				(MetaRowByte + PixelPTEBytesPerRow * HostVMInefficiencyFactor) / prefetch_bw_oto,
				LineTime - Tvm_oto, LineTime / 4);
	पूर्ण अन्यथा
		Tr0_oto = (LineTime - Tvm_oto) / 2.0;

	Tvm_oto_lines = dml_उच्चमान(4.0 * Tvm_oto / LineTime, 1) / 4.0;
	Tr0_oto_lines = dml_उच्चमान(4.0 * Tr0_oto / LineTime, 1) / 4.0;
	dst_y_prefetch_oto = Tvm_oto_lines + 2 * Tr0_oto_lines + Lsw_oto;

	dst_y_prefetch_equ = dml_न्यूनमान(4.0 * (dst_y_prefetch_equ + 0.125), 1) / 4.0;
	Tpre_rounded = dst_y_prefetch_equ * LineTime;

	dml_prपूर्णांक("DML: dst_y_prefetch_oto: %f\n", dst_y_prefetch_oto);
	dml_prपूर्णांक("DML: dst_y_prefetch_equ: %f\n", dst_y_prefetch_equ);

	dml_prपूर्णांक("DML: LineTime: %f\n", LineTime);
	dml_prपूर्णांक("DML: VStartup: %d\n", VStartup);
	dml_prपूर्णांक("DML: Tvstartup: %fus - time between vstartup and first pixel of active\n", VStartup * LineTime);
	dml_prपूर्णांक("DML: Tsetup: %fus - time from vstartup to vready\n", Tsetup);
	dml_prपूर्णांक("DML: TCalc: %fus - time for calculations in dchub starting at vready\n", TCalc);
	dml_prपूर्णांक("DML: TWait: %fus - time for fabric to become ready max(pstate exit,cstate enter/exit, urgent latency) after TCalc\n", TWait);
	dml_prपूर्णांक("DML: Tdmbf: %fus - time for dmd transfer from dchub to dio output buffer\n", Tdmbf);
	dml_prपूर्णांक("DML: Tdmec: %fus - time dio takes to transfer dmd\n", Tdmec);
	dml_prपूर्णांक("DML: Tdmsks: %fus - time before active dmd must complete transmission at dio\n", Tdmsks);
	dml_prपूर्णांक("DML: Tdmdl_vm: %fus - time for vm stages of dmd \n", *Tdmdl_vm);
	dml_prपूर्णांक("DML: Tdmdl: %fus - time for fabric to become ready and fetch dmd \n", *Tdmdl);
	dml_prपूर्णांक("DML: dst_x_after_scl: %f pixels - number of pixel clocks pipeline and buffer delay after scaler \n", *DSTXAfterScaler);
	dml_prपूर्णांक("DML: dst_y_after_scl: %d lines - number of lines of pipeline and buffer delay after scaler \n", (पूर्णांक)*DSTYAfterScaler);

	*PrefetchBandwidth = 0;
	*DestinationLinesToRequestVMInVBlank = 0;
	*DestinationLinesToRequestRowInVBlank = 0;
	*VRatioPrefetchY = 0;
	*VRatioPrefetchC = 0;
	*RequiredPrefetchPixDataBWLuma = 0;
	अगर (dst_y_prefetch_equ > 1) अणु
		द्विगुन PrefetchBandwidth1 = 0;
		द्विगुन PrefetchBandwidth2 = 0;
		द्विगुन PrefetchBandwidth3 = 0;
		द्विगुन PrefetchBandwidth4 = 0;

		अगर (Tpre_rounded - *Tno_bw > 0)
			PrefetchBandwidth1 = (PDEAndMetaPTEBytesFrame * HostVMInefficiencyFactor + 2 * MetaRowByte
					+ 2 * PixelPTEBytesPerRow * HostVMInefficiencyFactor
					+ PrefetchSourceLinesY * swath_width_luma_ub * BytePerPixelY
					+ PrefetchSourceLinesC * swath_width_chroma_ub * BytePerPixelC)
					/ (Tpre_rounded - *Tno_bw);
		अन्यथा
			PrefetchBandwidth1 = 0;

		अगर (VStartup == MaxVStartup && (PrefetchBandwidth1 > 4 * prefetch_bw_oto) && (Tpre_rounded - Tsw_oto / 4 - 0.75 * LineTime - *Tno_bw) > 0) अणु
			PrefetchBandwidth1 = (PDEAndMetaPTEBytesFrame * HostVMInefficiencyFactor + 2 * MetaRowByte + 2 * PixelPTEBytesPerRow * HostVMInefficiencyFactor) / (Tpre_rounded - Tsw_oto / 4 - 0.75 * LineTime - *Tno_bw);
		पूर्ण

		अगर (Tpre_rounded - *Tno_bw - 2 * Tr0_trips_rounded > 0)
			PrefetchBandwidth2 = (PDEAndMetaPTEBytesFrame *
					HostVMInefficiencyFactor + PrefetchSourceLinesY *
					swath_width_luma_ub * BytePerPixelY +
					PrefetchSourceLinesC * swath_width_chroma_ub *
					BytePerPixelC) /
					(Tpre_rounded - *Tno_bw - 2 * Tr0_trips_rounded);
		अन्यथा
			PrefetchBandwidth2 = 0;

		अगर (Tpre_rounded - Tvm_trips_rounded > 0)
			PrefetchBandwidth3 = (2 * MetaRowByte + 2 * PixelPTEBytesPerRow *
					HostVMInefficiencyFactor + PrefetchSourceLinesY *
					swath_width_luma_ub * BytePerPixelY + PrefetchSourceLinesC *
					swath_width_chroma_ub * BytePerPixelC) / (Tpre_rounded -
					Tvm_trips_rounded);
		अन्यथा
			PrefetchBandwidth3 = 0;

		अगर (VStartup == MaxVStartup && (PrefetchBandwidth3 > 4 * prefetch_bw_oto) && Tpre_rounded - Tsw_oto / 4 - 0.75 * LineTime - Tvm_trips_rounded > 0) अणु
			PrefetchBandwidth3 = (2 * MetaRowByte + 2 * PixelPTEBytesPerRow * HostVMInefficiencyFactor) / (Tpre_rounded - Tsw_oto / 4 - 0.75 * LineTime - Tvm_trips_rounded);
		पूर्ण

		अगर (Tpre_rounded - Tvm_trips_rounded - 2 * Tr0_trips_rounded > 0)
			PrefetchBandwidth4 = (PrefetchSourceLinesY * swath_width_luma_ub * BytePerPixelY + PrefetchSourceLinesC * swath_width_chroma_ub * BytePerPixelC)
					/ (Tpre_rounded - Tvm_trips_rounded - 2 * Tr0_trips_rounded);
		अन्यथा
			PrefetchBandwidth4 = 0;

		अणु
			bool Case1OK;
			bool Case2OK;
			bool Case3OK;

			अगर (PrefetchBandwidth1 > 0) अणु
				अगर (*Tno_bw + PDEAndMetaPTEBytesFrame * HostVMInefficiencyFactor / PrefetchBandwidth1
						>= Tvm_trips_rounded && (MetaRowByte + PixelPTEBytesPerRow * HostVMInefficiencyFactor) / PrefetchBandwidth1 >= Tr0_trips_rounded) अणु
					Case1OK = true;
				पूर्ण अन्यथा अणु
					Case1OK = false;
				पूर्ण
			पूर्ण अन्यथा अणु
				Case1OK = false;
			पूर्ण

			अगर (PrefetchBandwidth2 > 0) अणु
				अगर (*Tno_bw + PDEAndMetaPTEBytesFrame * HostVMInefficiencyFactor / PrefetchBandwidth2
						>= Tvm_trips_rounded && (MetaRowByte + PixelPTEBytesPerRow * HostVMInefficiencyFactor) / PrefetchBandwidth2 < Tr0_trips_rounded) अणु
					Case2OK = true;
				पूर्ण अन्यथा अणु
					Case2OK = false;
				पूर्ण
			पूर्ण अन्यथा अणु
				Case2OK = false;
			पूर्ण

			अगर (PrefetchBandwidth3 > 0) अणु
				अगर (*Tno_bw + PDEAndMetaPTEBytesFrame * HostVMInefficiencyFactor / PrefetchBandwidth3
						< Tvm_trips_rounded && (MetaRowByte + PixelPTEBytesPerRow * HostVMInefficiencyFactor) / PrefetchBandwidth3 >= Tr0_trips_rounded) अणु
					Case3OK = true;
				पूर्ण अन्यथा अणु
					Case3OK = false;
				पूर्ण
			पूर्ण अन्यथा अणु
				Case3OK = false;
			पूर्ण

			अगर (Case1OK) अणु
				prefetch_bw_equ = PrefetchBandwidth1;
			पूर्ण अन्यथा अगर (Case2OK) अणु
				prefetch_bw_equ = PrefetchBandwidth2;
			पूर्ण अन्यथा अगर (Case3OK) अणु
				prefetch_bw_equ = PrefetchBandwidth3;
			पूर्ण अन्यथा अणु
				prefetch_bw_equ = PrefetchBandwidth4;
			पूर्ण

			dml_prपूर्णांक("DML: prefetch_bw_equ: %f\n", prefetch_bw_equ);

			अगर (prefetch_bw_equ > 0) अणु
				अगर (GPUVMEnable) अणु
					Tvm_equ = dml_max3(*Tno_bw + PDEAndMetaPTEBytesFrame * HostVMInefficiencyFactor / prefetch_bw_equ, Tvm_trips, LineTime / 4);
				पूर्ण अन्यथा अणु
					Tvm_equ = LineTime / 4;
				पूर्ण

				अगर ((GPUVMEnable || myPipe->DCCEnable)) अणु
					Tr0_equ = dml_max4(
							(MetaRowByte + PixelPTEBytesPerRow * HostVMInefficiencyFactor) / prefetch_bw_equ,
							Tr0_trips,
							(LineTime - Tvm_equ) / 2,
							LineTime / 4);
				पूर्ण अन्यथा अणु
					Tr0_equ = (LineTime - Tvm_equ) / 2;
				पूर्ण
			पूर्ण अन्यथा अणु
				Tvm_equ = 0;
				Tr0_equ = 0;
				dml_prपूर्णांक("DML: prefetch_bw_equ equals 0! %s:%d\n", __खाता__, __LINE__);
			पूर्ण
		पूर्ण

		अगर (dst_y_prefetch_oto < dst_y_prefetch_equ) अणु
			*DestinationLinesForPrefetch = dst_y_prefetch_oto;
			TimeForFetchingMetaPTE = Tvm_oto;
			TimeForFetchingRowInVBlank = Tr0_oto;
			*PrefetchBandwidth = prefetch_bw_oto;
		पूर्ण अन्यथा अणु
			*DestinationLinesForPrefetch = dst_y_prefetch_equ;
			TimeForFetchingMetaPTE = Tvm_equ;
			TimeForFetchingRowInVBlank = Tr0_equ;
			*PrefetchBandwidth = prefetch_bw_equ;
		पूर्ण

		*DestinationLinesToRequestVMInVBlank = dml_उच्चमान(4.0 * TimeForFetchingMetaPTE / LineTime, 1.0) / 4.0;

		*DestinationLinesToRequestRowInVBlank = dml_उच्चमान(4.0 * TimeForFetchingRowInVBlank / LineTime, 1.0) / 4.0;


		LinesToRequestPrefetchPixelData = *DestinationLinesForPrefetch - *DestinationLinesToRequestVMInVBlank
				- 2 * *DestinationLinesToRequestRowInVBlank;

		अगर (LinesToRequestPrefetchPixelData > 0 && prefetch_bw_equ > 0) अणु

			*VRatioPrefetchY = (द्विगुन) PrefetchSourceLinesY
					/ LinesToRequestPrefetchPixelData;
			*VRatioPrefetchY = dml_max(*VRatioPrefetchY, 1.0);
			अगर ((SwathHeightY > 4) && (VInitPreFillY > 3)) अणु
				अगर (LinesToRequestPrefetchPixelData > (VInitPreFillY - 3.0) / 2.0) अणु
					*VRatioPrefetchY = dml_max((द्विगुन) PrefetchSourceLinesY / LinesToRequestPrefetchPixelData,
						(द्विगुन) MaxNumSwathY * SwathHeightY / (LinesToRequestPrefetchPixelData - (VInitPreFillY - 3.0) / 2.0));
					*VRatioPrefetchY = dml_max(*VRatioPrefetchY, 1.0);
				पूर्ण अन्यथा अणु
					MyError = true;
					dml_prपूर्णांक("DML: MyErr set %s:%d\n", __खाता__, __LINE__);
					*VRatioPrefetchY = 0;
				पूर्ण
			पूर्ण

			*VRatioPrefetchC = (द्विगुन) PrefetchSourceLinesC / LinesToRequestPrefetchPixelData;
			*VRatioPrefetchC = dml_max(*VRatioPrefetchC, 1.0);

			अगर ((SwathHeightC > 4)) अणु
				अगर (LinesToRequestPrefetchPixelData > (VInitPreFillC - 3.0) / 2.0) अणु
					*VRatioPrefetchC = dml_max(*VRatioPrefetchC,
						(द्विगुन) MaxNumSwathC * SwathHeightC / (LinesToRequestPrefetchPixelData - (VInitPreFillC - 3.0) / 2.0));
					*VRatioPrefetchC = dml_max(*VRatioPrefetchC, 1.0);
				पूर्ण अन्यथा अणु
					MyError = true;
					dml_prपूर्णांक("DML: MyErr set %s:%d\n", __खाता__, __LINE__);
					*VRatioPrefetchC = 0;
				पूर्ण
			पूर्ण

			*RequiredPrefetchPixDataBWLuma = (द्विगुन) PrefetchSourceLinesY / LinesToRequestPrefetchPixelData * BytePerPixelY * swath_width_luma_ub / LineTime;
			*RequiredPrefetchPixDataBWChroma = (द्विगुन) PrefetchSourceLinesC / LinesToRequestPrefetchPixelData * BytePerPixelC * swath_width_chroma_ub / LineTime;
		पूर्ण अन्यथा अणु
			MyError = true;
			dml_prपूर्णांक("DML: MyErr set %s:%d\n", __खाता__, __LINE__);
			dml_prपूर्णांक("DML: LinesToRequestPrefetchPixelData: %f, should be > 0\n", LinesToRequestPrefetchPixelData);
			*VRatioPrefetchY = 0;
			*VRatioPrefetchC = 0;
			*RequiredPrefetchPixDataBWLuma = 0;
			*RequiredPrefetchPixDataBWChroma = 0;
		पूर्ण

		dml_prपूर्णांक("DML: Tpre: %fus - sum of tim to request meta pte, 2 x data pte + meta data, swaths\n", (द्विगुन)LinesToRequestPrefetchPixelData * LineTime + 2.0*TimeForFetchingRowInVBlank + TimeForFetchingMetaPTE);
		dml_prपूर्णांक("DML:  Tvm: %fus - time to fetch page tables for meta surface\n", TimeForFetchingMetaPTE);
		dml_prपूर्णांक("DML:  Tr0: %fus - time to fetch first row of data pagetables and first row of meta data (done in parallel)\n", TimeForFetchingRowInVBlank);
		dml_prपूर्णांक("DML:  Tr1: %fus - time to fetch second row of data pagetables and second row of meta data (done in parallel)\n", TimeForFetchingRowInVBlank);
		dml_prपूर्णांक("DML:  Tsw: %fus = time to fetch enough pixel data and cursor data to feed the scalers init position and detile\n", (द्विगुन)LinesToRequestPrefetchPixelData * LineTime);
		dml_prपूर्णांक("DML: To: %fus - time for propagation from scaler to optc\n", (*DSTYAfterScaler + ((*DSTXAfterScaler) / (द्विगुन) myPipe->HTotal)) * LineTime);
		dml_prपूर्णांक("DML: Tvstartup - Tsetup - Tcalc - Twait - Tpre - To > 0\n");
		dml_prपूर्णांक("DML: Tslack(pre): %fus - time left over in schedule\n", VStartup * LineTime - TimeForFetchingMetaPTE - 2 * TimeForFetchingRowInVBlank - (*DSTYAfterScaler + ((*DSTXAfterScaler) / (द्विगुन) myPipe->HTotal)) * LineTime - TWait - TCalc - Tsetup);
		dml_prपूर्णांक("DML: row_bytes = dpte_row_bytes (per_pipe) = PixelPTEBytesPerRow = : %d\n", PixelPTEBytesPerRow);

	पूर्ण अन्यथा अणु
		MyError = true;
		dml_prपूर्णांक("DML: MyErr set %s:%d\n", __खाता__, __LINE__);
	पूर्ण

	अणु
		द्विगुन prefetch_vm_bw = 0;
		द्विगुन prefetch_row_bw = 0;

		अगर (PDEAndMetaPTEBytesFrame == 0) अणु
			prefetch_vm_bw = 0;
		पूर्ण अन्यथा अगर (*DestinationLinesToRequestVMInVBlank > 0) अणु
			prefetch_vm_bw = PDEAndMetaPTEBytesFrame * HostVMInefficiencyFactor / (*DestinationLinesToRequestVMInVBlank * LineTime);
		पूर्ण अन्यथा अणु
			prefetch_vm_bw = 0;
			MyError = true;
			dml_prपूर्णांक("DML: MyErr set %s:%d\n", __खाता__, __LINE__);
		पूर्ण
		अगर (MetaRowByte + PixelPTEBytesPerRow == 0) अणु
			prefetch_row_bw = 0;
		पूर्ण अन्यथा अगर (*DestinationLinesToRequestRowInVBlank > 0) अणु
			prefetch_row_bw = (MetaRowByte + PixelPTEBytesPerRow * HostVMInefficiencyFactor) / (*DestinationLinesToRequestRowInVBlank * LineTime);
		पूर्ण अन्यथा अणु
			prefetch_row_bw = 0;
			MyError = true;
			dml_prपूर्णांक("DML: MyErr set %s:%d\n", __खाता__, __LINE__);
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
	वापस VCOSpeed * 4 / dml_उच्चमान(VCOSpeed * 4.0 / Clock, 1);
पूर्ण

अटल व्योम CalculateDCCConfiguration(
		bool DCCEnabled,
		bool DCCProgrammingAssumesScanDirectionUnknown,
		क्रमागत source_क्रमmat_class SourcePixelFormat,
		अचिन्हित पूर्णांक SurfaceWidthLuma,
		अचिन्हित पूर्णांक SurfaceWidthChroma,
		अचिन्हित पूर्णांक SurfaceHeightLuma,
		अचिन्हित पूर्णांक SurfaceHeightChroma,
		द्विगुन DETBufferSize,
		अचिन्हित पूर्णांक RequestHeight256ByteLuma,
		अचिन्हित पूर्णांक RequestHeight256ByteChroma,
		क्रमागत dm_swizzle_mode TilingFormat,
		अचिन्हित पूर्णांक BytePerPixelY,
		अचिन्हित पूर्णांक BytePerPixelC,
		द्विगुन BytePerPixelDETY,
		द्विगुन BytePerPixelDETC,
		क्रमागत scan_direction_class ScanOrientation,
		अचिन्हित पूर्णांक *MaxUncompressedBlockLuma,
		अचिन्हित पूर्णांक *MaxUncompressedBlockChroma,
		अचिन्हित पूर्णांक *MaxCompressedBlockLuma,
		अचिन्हित पूर्णांक *MaxCompressedBlockChroma,
		अचिन्हित पूर्णांक *IndependentBlockLuma,
		अचिन्हित पूर्णांक *IndependentBlockChroma)
अणु
	पूर्णांक yuv420 = 0;
	पूर्णांक horz_भाग_l = 0;
	पूर्णांक horz_भाग_c = 0;
	पूर्णांक vert_भाग_l = 0;
	पूर्णांक vert_भाग_c = 0;

	पूर्णांक req128_horz_wc_l = 0;
	पूर्णांक req128_horz_wc_c = 0;
	पूर्णांक req128_vert_wc_l = 0;
	पूर्णांक req128_vert_wc_c = 0;
	पूर्णांक segment_order_horz_contiguous_luma = 0;
	पूर्णांक segment_order_horz_contiguous_chroma = 0;
	पूर्णांक segment_order_vert_contiguous_luma = 0;
	पूर्णांक segment_order_vert_contiguous_chroma = 0;

	दीर्घ full_swath_bytes_horz_wc_l = 0;
	दीर्घ full_swath_bytes_horz_wc_c = 0;
	दीर्घ full_swath_bytes_vert_wc_l = 0;
	दीर्घ full_swath_bytes_vert_wc_c = 0;

	दीर्घ swath_buf_size = 0;
	द्विगुन detile_buf_vp_horz_limit = 0;
	द्विगुन detile_buf_vp_vert_limit = 0;

	दीर्घ MAS_vp_horz_limit = 0;
	दीर्घ MAS_vp_vert_limit = 0;
	दीर्घ max_vp_horz_width = 0;
	दीर्घ max_vp_vert_height = 0;
	दीर्घ eff_surf_width_l = 0;
	दीर्घ eff_surf_width_c = 0;
	दीर्घ eff_surf_height_l = 0;
	दीर्घ eff_surf_height_c = 0;

	प्रकार क्रमागत अणु
		REQ_256Bytes,
		REQ_128BytesNonContiguous,
		REQ_128BytesContiguous,
		REQ_NA
	पूर्ण RequestType;

	RequestType   RequestLuma;
	RequestType   RequestChroma;

	yuv420 = ((SourcePixelFormat == dm_420_8 || SourcePixelFormat == dm_420_10 || SourcePixelFormat == dm_420_12) ? 1 : 0);
	horz_भाग_l = 1;
	horz_भाग_c = 1;
	vert_भाग_l = 1;
	vert_भाग_c = 1;

	अगर (BytePerPixelY == 1)
		vert_भाग_l = 0;
	अगर (BytePerPixelC == 1)
		vert_भाग_c = 0;
	अगर (BytePerPixelY == 8
			&& (TilingFormat == dm_sw_64kb_s || TilingFormat == dm_sw_64kb_s_t
					|| TilingFormat == dm_sw_64kb_s_x))
		horz_भाग_l = 0;
	अगर (BytePerPixelC == 8
			&& (TilingFormat == dm_sw_64kb_s || TilingFormat == dm_sw_64kb_s_t
					|| TilingFormat == dm_sw_64kb_s_x))
		horz_भाग_c = 0;

	अगर (BytePerPixelC == 0) अणु
		swath_buf_size = DETBufferSize / 2 - 2 * 256;
		detile_buf_vp_horz_limit = (द्विगुन) swath_buf_size
				/ ((द्विगुन) RequestHeight256ByteLuma * BytePerPixelY
						/ (1 + horz_भाग_l));
		detile_buf_vp_vert_limit = (द्विगुन) swath_buf_size
				/ (256.0 / RequestHeight256ByteLuma / (1 + vert_भाग_l));
	पूर्ण अन्यथा अणु
		swath_buf_size = DETBufferSize / 2 - 2 * 2 * 256;
		detile_buf_vp_horz_limit = (द्विगुन) swath_buf_size
				/ ((द्विगुन) RequestHeight256ByteLuma * BytePerPixelY
						/ (1 + horz_भाग_l)
						+ (द्विगुन) RequestHeight256ByteChroma
								* BytePerPixelC / (1 + horz_भाग_c)
								/ (1 + yuv420));
		detile_buf_vp_vert_limit = (द्विगुन) swath_buf_size
				/ (256.0 / RequestHeight256ByteLuma / (1 + vert_भाग_l)
						+ 256.0 / RequestHeight256ByteChroma
								/ (1 + vert_भाग_c) / (1 + yuv420));
	पूर्ण

	अगर (SourcePixelFormat == dm_420_10) अणु
		detile_buf_vp_horz_limit = 1.5 * detile_buf_vp_horz_limit;
		detile_buf_vp_vert_limit = 1.5 * detile_buf_vp_vert_limit;
	पूर्ण

	detile_buf_vp_horz_limit = dml_न्यूनमान(detile_buf_vp_horz_limit - 1, 16);
	detile_buf_vp_vert_limit = dml_न्यूनमान(detile_buf_vp_vert_limit - 1, 16);

	MAS_vp_horz_limit = 5760;
	MAS_vp_vert_limit = (BytePerPixelC > 0 ? 2880 : 5760);
	max_vp_horz_width = dml_min((द्विगुन) MAS_vp_horz_limit, detile_buf_vp_horz_limit);
	max_vp_vert_height = dml_min((द्विगुन) MAS_vp_vert_limit, detile_buf_vp_vert_limit);
	eff_surf_width_l =
			(SurfaceWidthLuma > max_vp_horz_width ? max_vp_horz_width : SurfaceWidthLuma);
	eff_surf_width_c = eff_surf_width_l / (1 + yuv420);
	eff_surf_height_l = (
			SurfaceHeightLuma > max_vp_vert_height ?
					max_vp_vert_height : SurfaceHeightLuma);
	eff_surf_height_c = eff_surf_height_l / (1 + yuv420);

	full_swath_bytes_horz_wc_l = eff_surf_width_l * RequestHeight256ByteLuma * BytePerPixelY;
	full_swath_bytes_vert_wc_l = eff_surf_height_l * 256 / RequestHeight256ByteLuma;
	अगर (BytePerPixelC > 0) अणु
		full_swath_bytes_horz_wc_c = eff_surf_width_c * RequestHeight256ByteChroma
				* BytePerPixelC;
		full_swath_bytes_vert_wc_c = eff_surf_height_c * 256 / RequestHeight256ByteChroma;
	पूर्ण अन्यथा अणु
		full_swath_bytes_horz_wc_c = 0;
		full_swath_bytes_vert_wc_c = 0;
	पूर्ण

	अगर (SourcePixelFormat == dm_420_10) अणु
		full_swath_bytes_horz_wc_l = dml_उच्चमान(full_swath_bytes_horz_wc_l * 2 / 3, 256);
		full_swath_bytes_horz_wc_c = dml_उच्चमान(full_swath_bytes_horz_wc_c * 2 / 3, 256);
		full_swath_bytes_vert_wc_l = dml_उच्चमान(full_swath_bytes_vert_wc_l * 2 / 3, 256);
		full_swath_bytes_vert_wc_c = dml_उच्चमान(full_swath_bytes_vert_wc_c * 2 / 3, 256);
	पूर्ण

	अगर (2 * full_swath_bytes_horz_wc_l + 2 * full_swath_bytes_horz_wc_c <= DETBufferSize) अणु
		req128_horz_wc_l = 0;
		req128_horz_wc_c = 0;
	पूर्ण अन्यथा अगर (full_swath_bytes_horz_wc_l < 1.5 * full_swath_bytes_horz_wc_c
			&& 2 * full_swath_bytes_horz_wc_l + full_swath_bytes_horz_wc_c
					<= DETBufferSize) अणु
		req128_horz_wc_l = 0;
		req128_horz_wc_c = 1;
	पूर्ण अन्यथा अगर (full_swath_bytes_horz_wc_l >= 1.5 * full_swath_bytes_horz_wc_c
			&& full_swath_bytes_horz_wc_l + 2 * full_swath_bytes_horz_wc_c
					<= DETBufferSize) अणु
		req128_horz_wc_l = 1;
		req128_horz_wc_c = 0;
	पूर्ण अन्यथा अणु
		req128_horz_wc_l = 1;
		req128_horz_wc_c = 1;
	पूर्ण

	अगर (2 * full_swath_bytes_vert_wc_l + 2 * full_swath_bytes_vert_wc_c <= DETBufferSize) अणु
		req128_vert_wc_l = 0;
		req128_vert_wc_c = 0;
	पूर्ण अन्यथा अगर (full_swath_bytes_vert_wc_l < 1.5 * full_swath_bytes_vert_wc_c
			&& 2 * full_swath_bytes_vert_wc_l + full_swath_bytes_vert_wc_c
					<= DETBufferSize) अणु
		req128_vert_wc_l = 0;
		req128_vert_wc_c = 1;
	पूर्ण अन्यथा अगर (full_swath_bytes_vert_wc_l >= 1.5 * full_swath_bytes_vert_wc_c
			&& full_swath_bytes_vert_wc_l + 2 * full_swath_bytes_vert_wc_c
					<= DETBufferSize) अणु
		req128_vert_wc_l = 1;
		req128_vert_wc_c = 0;
	पूर्ण अन्यथा अणु
		req128_vert_wc_l = 1;
		req128_vert_wc_c = 1;
	पूर्ण

	अगर (BytePerPixelY == 2 || (BytePerPixelY == 4 && TilingFormat != dm_sw_64kb_r_x)) अणु
		segment_order_horz_contiguous_luma = 0;
	पूर्ण अन्यथा अणु
		segment_order_horz_contiguous_luma = 1;
	पूर्ण
	अगर ((BytePerPixelY == 8
			&& (TilingFormat == dm_sw_64kb_d || TilingFormat == dm_sw_64kb_d_x
					|| TilingFormat == dm_sw_64kb_d_t
					|| TilingFormat == dm_sw_64kb_r_x))
			|| (BytePerPixelY == 4 && TilingFormat == dm_sw_64kb_r_x)) अणु
		segment_order_vert_contiguous_luma = 0;
	पूर्ण अन्यथा अणु
		segment_order_vert_contiguous_luma = 1;
	पूर्ण
	अगर (BytePerPixelC == 2 || (BytePerPixelC == 4 && TilingFormat != dm_sw_64kb_r_x)) अणु
		segment_order_horz_contiguous_chroma = 0;
	पूर्ण अन्यथा अणु
		segment_order_horz_contiguous_chroma = 1;
	पूर्ण
	अगर ((BytePerPixelC == 8
			&& (TilingFormat == dm_sw_64kb_d || TilingFormat == dm_sw_64kb_d_x
					|| TilingFormat == dm_sw_64kb_d_t
					|| TilingFormat == dm_sw_64kb_r_x))
			|| (BytePerPixelC == 4 && TilingFormat == dm_sw_64kb_r_x)) अणु
		segment_order_vert_contiguous_chroma = 0;
	पूर्ण अन्यथा अणु
		segment_order_vert_contiguous_chroma = 1;
	पूर्ण

	अगर (DCCProgrammingAssumesScanDirectionUnknown == true) अणु
		अगर (req128_horz_wc_l == 0 && req128_vert_wc_l == 0) अणु
			RequestLuma = REQ_256Bytes;
		पूर्ण अन्यथा अगर ((req128_horz_wc_l == 1 && segment_order_horz_contiguous_luma == 0)
				|| (req128_vert_wc_l == 1 && segment_order_vert_contiguous_luma == 0)) अणु
			RequestLuma = REQ_128BytesNonContiguous;
		पूर्ण अन्यथा अणु
			RequestLuma = REQ_128BytesContiguous;
		पूर्ण
		अगर (req128_horz_wc_c == 0 && req128_vert_wc_c == 0) अणु
			RequestChroma = REQ_256Bytes;
		पूर्ण अन्यथा अगर ((req128_horz_wc_c == 1 && segment_order_horz_contiguous_chroma == 0)
				|| (req128_vert_wc_c == 1
						&& segment_order_vert_contiguous_chroma == 0)) अणु
			RequestChroma = REQ_128BytesNonContiguous;
		पूर्ण अन्यथा अणु
			RequestChroma = REQ_128BytesContiguous;
		पूर्ण
	पूर्ण अन्यथा अगर (ScanOrientation != dm_vert) अणु
		अगर (req128_horz_wc_l == 0) अणु
			RequestLuma = REQ_256Bytes;
		पूर्ण अन्यथा अगर (segment_order_horz_contiguous_luma == 0) अणु
			RequestLuma = REQ_128BytesNonContiguous;
		पूर्ण अन्यथा अणु
			RequestLuma = REQ_128BytesContiguous;
		पूर्ण
		अगर (req128_horz_wc_c == 0) अणु
			RequestChroma = REQ_256Bytes;
		पूर्ण अन्यथा अगर (segment_order_horz_contiguous_chroma == 0) अणु
			RequestChroma = REQ_128BytesNonContiguous;
		पूर्ण अन्यथा अणु
			RequestChroma = REQ_128BytesContiguous;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (req128_vert_wc_l == 0) अणु
			RequestLuma = REQ_256Bytes;
		पूर्ण अन्यथा अगर (segment_order_vert_contiguous_luma == 0) अणु
			RequestLuma = REQ_128BytesNonContiguous;
		पूर्ण अन्यथा अणु
			RequestLuma = REQ_128BytesContiguous;
		पूर्ण
		अगर (req128_vert_wc_c == 0) अणु
			RequestChroma = REQ_256Bytes;
		पूर्ण अन्यथा अगर (segment_order_vert_contiguous_chroma == 0) अणु
			RequestChroma = REQ_128BytesNonContiguous;
		पूर्ण अन्यथा अणु
			RequestChroma = REQ_128BytesContiguous;
		पूर्ण
	पूर्ण

	अगर (RequestLuma == REQ_256Bytes) अणु
		*MaxUncompressedBlockLuma = 256;
		*MaxCompressedBlockLuma = 256;
		*IndependentBlockLuma = 0;
	पूर्ण अन्यथा अगर (RequestLuma == REQ_128BytesContiguous) अणु
		*MaxUncompressedBlockLuma = 256;
		*MaxCompressedBlockLuma = 128;
		*IndependentBlockLuma = 128;
	पूर्ण अन्यथा अणु
		*MaxUncompressedBlockLuma = 256;
		*MaxCompressedBlockLuma = 64;
		*IndependentBlockLuma = 64;
	पूर्ण

	अगर (RequestChroma == REQ_256Bytes) अणु
		*MaxUncompressedBlockChroma = 256;
		*MaxCompressedBlockChroma = 256;
		*IndependentBlockChroma = 0;
	पूर्ण अन्यथा अगर (RequestChroma == REQ_128BytesContiguous) अणु
		*MaxUncompressedBlockChroma = 256;
		*MaxCompressedBlockChroma = 128;
		*IndependentBlockChroma = 128;
	पूर्ण अन्यथा अणु
		*MaxUncompressedBlockChroma = 256;
		*MaxCompressedBlockChroma = 64;
		*IndependentBlockChroma = 64;
	पूर्ण

	अगर (DCCEnabled != true || BytePerPixelC == 0) अणु
		*MaxUncompressedBlockChroma = 0;
		*MaxCompressedBlockChroma = 0;
		*IndependentBlockChroma = 0;
	पूर्ण

	अगर (DCCEnabled != true) अणु
		*MaxUncompressedBlockLuma = 0;
		*MaxCompressedBlockLuma = 0;
		*IndependentBlockLuma = 0;
	पूर्ण
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
	अचिन्हित पूर्णांक MaxPartialSwath = 0;

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
		अचिन्हित पूर्णांक SwathWidth,
		अचिन्हित पूर्णांक ViewportHeight,
		bool GPUVMEnable,
		bool HostVMEnable,
		अचिन्हित पूर्णांक HostVMMaxNonCachedPageTableLevels,
		अचिन्हित पूर्णांक GPUVMMinPageSize,
		अचिन्हित पूर्णांक HostVMMinPageSize,
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
	अचिन्हित पूर्णांक MPDEBytesFrame = 0;
	अचिन्हित पूर्णांक DCCMetaSurfaceBytes = 0;
	अचिन्हित पूर्णांक MacroTileSizeBytes = 0;
	अचिन्हित पूर्णांक MacroTileHeight = 0;
	अचिन्हित पूर्णांक ExtraDPDEBytesFrame = 0;
	अचिन्हित पूर्णांक PDEAndMetaPTEBytesFrame = 0;
	अचिन्हित पूर्णांक PixelPTEReqHeightPTEs = 0;
	अचिन्हित पूर्णांक HostVMDynamicLevels = 0;

	द्विगुन FractionOfPTEReturnDrop;

	अगर (GPUVMEnable == true && HostVMEnable == true) अणु
		अगर (HostVMMinPageSize < 2048) अणु
			HostVMDynamicLevels = HostVMMaxNonCachedPageTableLevels;
		पूर्ण अन्यथा अगर (HostVMMinPageSize >= 2048 && HostVMMinPageSize < 1048576) अणु
			HostVMDynamicLevels = dml_max(0, (पूर्णांक) HostVMMaxNonCachedPageTableLevels - 1);
		पूर्ण अन्यथा अणु
			HostVMDynamicLevels = dml_max(0, (पूर्णांक) HostVMMaxNonCachedPageTableLevels - 2);
		पूर्ण
	पूर्ण

	*MetaRequestHeight = 8 * BlockHeight256Bytes;
	*MetaRequestWidth = 8 * BlockWidth256Bytes;
	अगर (ScanDirection != dm_vert) अणु
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
	DCCMetaSurfaceBytes = DCCMetaPitch * (dml_उच्चमान(ViewportHeight - 1, 64 * BlockHeight256Bytes)
					+ 64 * BlockHeight256Bytes) * BytePerPixel / 256;
	अगर (GPUVMEnable == true) अणु
		*MetaPTEBytesFrame = (dml_उच्चमान((द्विगुन) (DCCMetaSurfaceBytes - 4.0 * 1024.0) / (8 * 4.0 * 1024), 1) + 1) * 64;
		MPDEBytesFrame = 128 * (mode_lib->vba.GPUVMMaxPageTableLevels - 1);
	पूर्ण अन्यथा अणु
		*MetaPTEBytesFrame = 0;
		MPDEBytesFrame = 0;
	पूर्ण

	अगर (DCCEnable != true) अणु
		*MetaPTEBytesFrame = 0;
		MPDEBytesFrame = 0;
		*MetaRowByte = 0;
	पूर्ण

	अगर (SurfaceTiling == dm_sw_linear) अणु
		MacroTileSizeBytes = 256;
		MacroTileHeight = BlockHeight256Bytes;
	पूर्ण अन्यथा अणु
		MacroTileSizeBytes = 65536;
		MacroTileHeight = 16 * BlockHeight256Bytes;
	पूर्ण
	*MacroTileWidth = MacroTileSizeBytes / BytePerPixel / MacroTileHeight;

	अगर (GPUVMEnable == true && mode_lib->vba.GPUVMMaxPageTableLevels > 1) अणु
		अगर (ScanDirection != dm_vert) अणु
			*DPDE0BytesFrame = 64 * (dml_उच्चमान(((Pitch * (dml_उच्चमान(ViewportHeight - 1, MacroTileHeight) + MacroTileHeight) * BytePerPixel) - MacroTileSizeBytes) / (8 * 2097152), 1) + 1);
		पूर्ण अन्यथा अणु
			*DPDE0BytesFrame = 64 * (dml_उच्चमान(((Pitch * (dml_उच्चमान((द्विगुन) SwathWidth - 1, MacroTileHeight) + MacroTileHeight) * BytePerPixel) - MacroTileSizeBytes) / (8 * 2097152), 1) + 1);
		पूर्ण
		ExtraDPDEBytesFrame = 128 * (mode_lib->vba.GPUVMMaxPageTableLevels - 2);
	पूर्ण अन्यथा अणु
		*DPDE0BytesFrame = 0;
		ExtraDPDEBytesFrame = 0;
	पूर्ण

	PDEAndMetaPTEBytesFrame = *MetaPTEBytesFrame + MPDEBytesFrame + *DPDE0BytesFrame
			+ ExtraDPDEBytesFrame;

	अगर (HostVMEnable == true) अणु
		PDEAndMetaPTEBytesFrame = PDEAndMetaPTEBytesFrame * (1 + 8 * HostVMDynamicLevels);
	पूर्ण

	अगर (SurfaceTiling == dm_sw_linear) अणु
		PixelPTEReqHeightPTEs = 1;
		*PixelPTEReqHeight = 1;
		*PixelPTEReqWidth = 32768.0 / BytePerPixel;
		*PTERequestSize = 64;
		FractionOfPTEReturnDrop = 0;
	पूर्ण अन्यथा अगर (MacroTileSizeBytes == 4096) अणु
		PixelPTEReqHeightPTEs = 1;
		*PixelPTEReqHeight = MacroTileHeight;
		*PixelPTEReqWidth = 8 * *MacroTileWidth;
		*PTERequestSize = 64;
		अगर (ScanDirection != dm_vert)
			FractionOfPTEReturnDrop = 0;
		अन्यथा
			FractionOfPTEReturnDrop = 7 / 8;
	पूर्ण अन्यथा अगर (GPUVMMinPageSize == 4 && MacroTileSizeBytes > 4096) अणु
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
		*dpte_row_height = dml_min(128, 1 << (अचिन्हित पूर्णांक) dml_न्यूनमान(dml_log2(PTEBufferSizeInRequests * *PixelPTEReqWidth / Pitch), 1));
		*dpte_row_width_ub = (dml_उच्चमान(((द्विगुन) SwathWidth - 1) / *PixelPTEReqWidth, 1) + 1) * *PixelPTEReqWidth;
		*PixelPTEBytesPerRow = *dpte_row_width_ub / *PixelPTEReqWidth * *PTERequestSize;
	पूर्ण अन्यथा अगर (ScanDirection != dm_vert) अणु
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

	अगर (GPUVMEnable != true) अणु
		*PixelPTEBytesPerRow = 0;
		*PTEBufferSizeNotExceeded = true;
	पूर्ण
	dml_prपूर्णांक("DML: vm_bytes = meta_pte_bytes_per_frame (per_pipe) = MetaPTEBytesFrame = : %i\n", *MetaPTEBytesFrame);

	अगर (HostVMEnable == true) अणु
		*PixelPTEBytesPerRow = *PixelPTEBytesPerRow * (1 + 8 * HostVMDynamicLevels);
	पूर्ण

	अगर (HostVMEnable == true) अणु
		*vm_group_bytes = 512;
		*dpte_group_bytes = 512;
	पूर्ण अन्यथा अगर (GPUVMEnable == true) अणु
		*vm_group_bytes = 2048;
		अगर (SurfaceTiling != dm_sw_linear && PixelPTEReqHeightPTEs == 1 && ScanDirection == dm_vert) अणु
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
	काष्ठा vba_vars_st *v = &mode_lib->vba;
	अचिन्हित पूर्णांक j, k;
	दीर्घ ReorderBytes = 0;
	अचिन्हित पूर्णांक PrefetchMode = v->PrefetchModePerState[v->VoltageLevel][v->maxMpcComb];
	द्विगुन MaxTotalRDBandwidth = 0;
	द्विगुन MaxTotalRDBandwidthNoUrgentBurst = 0;
	bool DestinationLineTimesForPrefetchLessThan2 = false;
	bool VRatioPrefetchMoreThan4 = false;
	द्विगुन TWait;

	v->WritebackDISPCLK = 0.0;
	v->DISPCLKWithRamping = 0;
	v->DISPCLKWithoutRamping = 0;
	v->GlobalDPPCLK = 0.0;
	/* DAL custom code: need to update ReturnBW in हाल min dcfclk is overriden */
	v->IdealSDPPortBandwidthPerState[v->VoltageLevel][v->maxMpcComb] = dml_min3(
			v->ReturnBusWidth * v->DCFCLK,
			v->DRAMSpeedPerState[v->VoltageLevel] * v->NumberOfChannels * v->DRAMChannelWidth,
			v->FabricClockPerState[v->VoltageLevel] * v->FabricDatapathToDCNDataReturn);
	अगर (v->HostVMEnable != true) अणु
		v->ReturnBW = v->IdealSDPPortBandwidthPerState[v->VoltageLevel][v->maxMpcComb] * v->PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelDataOnly / 100;
	पूर्ण अन्यथा अणु
		v->ReturnBW = v->IdealSDPPortBandwidthPerState[v->VoltageLevel][v->maxMpcComb] * v->PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData / 100;
	पूर्ण
	/* End DAL custom code */

	// DISPCLK and DPPCLK Calculation
	//
	क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
		अगर (v->WritebackEnable[k]) अणु
			v->WritebackDISPCLK = dml_max(v->WritebackDISPCLK,
				dml30_CalculateWriteBackDISPCLK(
						v->WritebackPixelFormat[k],
						v->PixelClock[k],
						v->WritebackHRatio[k],
						v->WritebackVRatio[k],
						v->WritebackHTaps[k],
						v->WritebackVTaps[k],
						v->WritebackSourceWidth[k],
						v->WritebackDestinationWidth[k],
						v->HTotal[k],
						v->WritebackLineBufferSize));
		पूर्ण
	पूर्ण

	क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
		अगर (v->HRatio[k] > 1) अणु
			v->PSCL_THROUGHPUT_LUMA[k] = dml_min(v->MaxDCHUBToPSCLThroughput,
				v->MaxPSCLToLBThroughput * v->HRatio[k] / dml_उच्चमान(v->htaps[k] / 6.0, 1));
		पूर्ण अन्यथा अणु
			v->PSCL_THROUGHPUT_LUMA[k] = dml_min(
					v->MaxDCHUBToPSCLThroughput,
					v->MaxPSCLToLBThroughput);
		पूर्ण

		v->DPPCLKUsingSingleDPPLuma = v->PixelClock[k]
			* dml_max(v->vtaps[k] / 6.0 * dml_min(1.0, v->HRatio[k]),
				dml_max(v->HRatio[k] * v->VRatio[k] / v->PSCL_THROUGHPUT_LUMA[k], 1.0));

		अगर ((v->htaps[k] > 6 || v->vtaps[k] > 6)
				&& v->DPPCLKUsingSingleDPPLuma < 2 * v->PixelClock[k]) अणु
			v->DPPCLKUsingSingleDPPLuma = 2 * v->PixelClock[k];
		पूर्ण

		अगर ((v->SourcePixelFormat[k] != dm_420_8
				&& v->SourcePixelFormat[k] != dm_420_10
				&& v->SourcePixelFormat[k] != dm_420_12
				&& v->SourcePixelFormat[k] != dm_rgbe_alpha)) अणु
			v->PSCL_THROUGHPUT_CHROMA[k] = 0.0;
			v->DPPCLKUsingSingleDPP[k] = v->DPPCLKUsingSingleDPPLuma;
		पूर्ण अन्यथा अणु
			अगर (v->HRatioChroma[k] > 1) अणु
				v->PSCL_THROUGHPUT_CHROMA[k] = dml_min(v->MaxDCHUBToPSCLThroughput,
					v->MaxPSCLToLBThroughput * v->HRatioChroma[k] / dml_उच्चमान(v->HTAPsChroma[k] / 6.0, 1.0));
			पूर्ण अन्यथा अणु
				v->PSCL_THROUGHPUT_CHROMA[k] = dml_min(
						v->MaxDCHUBToPSCLThroughput,
						v->MaxPSCLToLBThroughput);
			पूर्ण
			v->DPPCLKUsingSingleDPPChroma = v->PixelClock[k]
				* dml_max3(v->VTAPsChroma[k] / 6.0 * dml_min(1.0, v->HRatioChroma[k]),
					v->HRatioChroma[k] * v->VRatioChroma[k] / v->PSCL_THROUGHPUT_CHROMA[k], 1.0);

			अगर ((v->HTAPsChroma[k] > 6 || v->VTAPsChroma[k] > 6)
					&& v->DPPCLKUsingSingleDPPChroma
							< 2 * v->PixelClock[k]) अणु
				v->DPPCLKUsingSingleDPPChroma = 2
						* v->PixelClock[k];
			पूर्ण

			v->DPPCLKUsingSingleDPP[k] = dml_max(
					v->DPPCLKUsingSingleDPPLuma,
					v->DPPCLKUsingSingleDPPChroma);
		पूर्ण
	पूर्ण

	क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
		अगर (v->BlendingAndTiming[k] != k)
			जारी;
		अगर (v->ODMCombineEnabled[k] == dm_odm_combine_mode_4to1) अणु
			v->DISPCLKWithRamping = dml_max(v->DISPCLKWithRamping,
				v->PixelClock[k] / 4 * (1 + v->DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100)
					* (1 + v->DISPCLKRampingMargin / 100));
			v->DISPCLKWithoutRamping = dml_max(v->DISPCLKWithoutRamping,
				v->PixelClock[k] / 4 * (1 + v->DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100));
		पूर्ण अन्यथा अगर (v->ODMCombineEnabled[k] == dm_odm_combine_mode_2to1) अणु
			v->DISPCLKWithRamping = dml_max(v->DISPCLKWithRamping,
				v->PixelClock[k] / 2 * (1 + v->DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100)
					* (1 + v->DISPCLKRampingMargin / 100));
			v->DISPCLKWithoutRamping = dml_max(v->DISPCLKWithoutRamping,
				v->PixelClock[k] / 2 * (1 + v->DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100));
		पूर्ण अन्यथा अणु
			v->DISPCLKWithRamping = dml_max(v->DISPCLKWithRamping,
				v->PixelClock[k] * (1 + v->DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100)
									* (1 + v->DISPCLKRampingMargin / 100));
			v->DISPCLKWithoutRamping = dml_max(v->DISPCLKWithoutRamping,
				v->PixelClock[k] * (1 + v->DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100));
		पूर्ण
	पूर्ण

	v->DISPCLKWithRamping = dml_max(
			v->DISPCLKWithRamping,
			v->WritebackDISPCLK);
	v->DISPCLKWithoutRamping = dml_max(
			v->DISPCLKWithoutRamping,
			v->WritebackDISPCLK);

	ASSERT(v->DISPCLKDPPCLKVCOSpeed != 0);
	v->DISPCLKWithRampingRoundedToDFSGranularity = RoundToDFSGranularityUp(
			v->DISPCLKWithRamping,
			v->DISPCLKDPPCLKVCOSpeed);
	v->DISPCLKWithoutRampingRoundedToDFSGranularity = RoundToDFSGranularityUp(
			v->DISPCLKWithoutRamping,
			v->DISPCLKDPPCLKVCOSpeed);
	v->MaxDispclkRoundedToDFSGranularity = RoundToDFSGranularityDown(
			v->soc.घड़ी_limits[mode_lib->soc.num_states].dispclk_mhz,
			v->DISPCLKDPPCLKVCOSpeed);
	अगर (v->DISPCLKWithoutRampingRoundedToDFSGranularity
			> v->MaxDispclkRoundedToDFSGranularity) अणु
		v->DISPCLK_calculated =
				v->DISPCLKWithoutRampingRoundedToDFSGranularity;
	पूर्ण अन्यथा अगर (v->DISPCLKWithRampingRoundedToDFSGranularity
			> v->MaxDispclkRoundedToDFSGranularity) अणु
		v->DISPCLK_calculated = v->MaxDispclkRoundedToDFSGranularity;
	पूर्ण अन्यथा अणु
		v->DISPCLK_calculated =
				v->DISPCLKWithRampingRoundedToDFSGranularity;
	पूर्ण
	v->DISPCLK = v->DISPCLK_calculated;
	DTRACE("   dispclk_mhz (calculated) = %f", v->DISPCLK_calculated);

	क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
		v->DPPCLK_calculated[k] = v->DPPCLKUsingSingleDPP[k]
				/ v->DPPPerPlane[k]
				* (1 + v->DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100);
		v->GlobalDPPCLK = dml_max(
				v->GlobalDPPCLK,
				v->DPPCLK_calculated[k]);
	पूर्ण
	v->GlobalDPPCLK = RoundToDFSGranularityUp(
			v->GlobalDPPCLK,
			v->DISPCLKDPPCLKVCOSpeed);
	क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
		v->DPPCLK_calculated[k] = v->GlobalDPPCLK / 255
				* dml_उच्चमान(
						v->DPPCLK_calculated[k] * 255.0
								/ v->GlobalDPPCLK,
						1);
		DTRACE("   dppclk_mhz[%i] (calculated) = %f", k, v->DPPCLK_calculated[k]);
		v->DPPCLK[k] = v->DPPCLK_calculated[k];
	पूर्ण

	// Urgent and B P-State/DRAM Clock Change Watermark
	DTRACE("   dcfclk_mhz         = %f", v->DCFCLK);
	DTRACE("   return_bus_bw      = %f", v->ReturnBW);

	क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
		CalculateBytePerPixelAnd256BBlockSizes(
				v->SourcePixelFormat[k],
				v->SurfaceTiling[k],
				&v->BytePerPixelY[k],
				&v->BytePerPixelC[k],
				&v->BytePerPixelDETY[k],
				&v->BytePerPixelDETC[k],
				&v->BlockHeight256BytesY[k],
				&v->BlockHeight256BytesC[k],
				&v->BlockWidth256BytesY[k],
				&v->BlockWidth256BytesC[k]);
	पूर्ण

	CalculateSwathWidth(
			false,
			v->NumberOfActivePlanes,
			v->SourcePixelFormat,
			v->SourceScan,
			v->ViewportWidth,
			v->ViewportHeight,
			v->SurfaceWidthY,
			v->SurfaceWidthC,
			v->SurfaceHeightY,
			v->SurfaceHeightC,
			v->ODMCombineEnabled,
			v->BytePerPixelY,
			v->BytePerPixelC,
			v->BlockHeight256BytesY,
			v->BlockHeight256BytesC,
			v->BlockWidth256BytesY,
			v->BlockWidth256BytesC,
			v->BlendingAndTiming,
			v->HActive,
			v->HRatio,
			v->DPPPerPlane,
			v->SwathWidthSingleDPPY,
			v->SwathWidthSingleDPPC,
			v->SwathWidthY,
			v->SwathWidthC,
			v->dummyपूर्णांकeger3,
			v->dummyपूर्णांकeger4,
			v->swath_width_luma_ub,
			v->swath_width_chroma_ub);


	क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
		v->ReadBandwidthPlaneLuma[k] = v->SwathWidthSingleDPPY[k] * v->BytePerPixelY[k] / (v->HTotal[k] / v->PixelClock[k]) * v->VRatio[k];
		v->ReadBandwidthPlaneChroma[k] = v->SwathWidthSingleDPPC[k] * v->BytePerPixelC[k] / (v->HTotal[k] / v->PixelClock[k]) * v->VRatioChroma[k];
		DTRACE("read_bw[%i] = %fBps", k, v->ReadBandwidthPlaneLuma[k] + v->ReadBandwidthPlaneChroma[k]);
	पूर्ण


	// DCFCLK Deep Sleep
	CalculateDCFCLKDeepSleep(
			mode_lib,
			v->NumberOfActivePlanes,
			v->BytePerPixelY,
			v->BytePerPixelC,
			v->VRatio,
			v->VRatioChroma,
			v->SwathWidthY,
			v->SwathWidthC,
			v->DPPPerPlane,
			v->HRatio,
			v->HRatioChroma,
			v->PixelClock,
			v->PSCL_THROUGHPUT_LUMA,
			v->PSCL_THROUGHPUT_CHROMA,
			v->DPPCLK,
			v->ReadBandwidthPlaneLuma,
			v->ReadBandwidthPlaneChroma,
			v->ReturnBusWidth,
			&v->DCFCLKDeepSleep);

	// DSCCLK
	क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
		अगर ((v->BlendingAndTiming[k] != k) || !v->DSCEnabled[k]) अणु
			v->DSCCLK_calculated[k] = 0.0;
		पूर्ण अन्यथा अणु
			अगर (v->OutputFormat[k] == dm_420)
				v->DSCFormatFactor = 2;
			अन्यथा अगर (v->OutputFormat[k] == dm_444)
				v->DSCFormatFactor = 1;
			अन्यथा अगर (v->OutputFormat[k] == dm_n422)
				v->DSCFormatFactor = 2;
			अन्यथा
				v->DSCFormatFactor = 1;
			अगर (v->ODMCombineEnabled[k] == dm_odm_combine_mode_4to1)
				v->DSCCLK_calculated[k] = v->PixelClockBackEnd[k] / 12
					/ v->DSCFormatFactor / (1 - v->DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100);
			अन्यथा अगर (v->ODMCombineEnabled[k] == dm_odm_combine_mode_2to1)
				v->DSCCLK_calculated[k] = v->PixelClockBackEnd[k] / 6
					/ v->DSCFormatFactor / (1 - v->DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100);
			अन्यथा
				v->DSCCLK_calculated[k] = v->PixelClockBackEnd[k] / 3
					/ v->DSCFormatFactor / (1 - v->DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100);
		पूर्ण
	पूर्ण

	// DSC Delay
	क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
		द्विगुन BPP = v->OutputBppPerState[k][v->VoltageLevel];

		अगर (v->DSCEnabled[k] && BPP != 0) अणु
			अगर (v->ODMCombineEnabled[k] == dm_odm_combine_mode_disabled) अणु
				v->DSCDelay[k] = dscceComputeDelay(v->DSCInputBitPerComponent[k],
						BPP,
						dml_उच्चमान((द्विगुन) v->HActive[k] / v->NumberOfDSCSlices[k], 1),
						v->NumberOfDSCSlices[k],
						v->OutputFormat[k],
						v->Output[k])
					+ dscComputeDelay(v->OutputFormat[k], v->Output[k]);
			पूर्ण अन्यथा अगर (v->ODMCombineEnabled[k] == dm_odm_combine_mode_2to1) अणु
				v->DSCDelay[k] = 2 * dscceComputeDelay(v->DSCInputBitPerComponent[k],
						BPP,
						dml_उच्चमान((द्विगुन) v->HActive[k] / v->NumberOfDSCSlices[k], 1),
						v->NumberOfDSCSlices[k] / 2.0,
						v->OutputFormat[k],
						v->Output[k])
					+ dscComputeDelay(v->OutputFormat[k], v->Output[k]);
			पूर्ण अन्यथा अणु
				v->DSCDelay[k] = 4 * dscceComputeDelay(v->DSCInputBitPerComponent[k],
						BPP,
						dml_उच्चमान((द्विगुन) v->HActive[k] / v->NumberOfDSCSlices[k], 1),
						v->NumberOfDSCSlices[k] / 4.0,
						v->OutputFormat[k],
						v->Output[k])
					+ dscComputeDelay(v->OutputFormat[k], v->Output[k]);
			पूर्ण
			v->DSCDelay[k] = v->DSCDelay[k] * v->PixelClock[k] / v->PixelClockBackEnd[k];
		पूर्ण अन्यथा अणु
			v->DSCDelay[k] = 0;
		पूर्ण
	पूर्ण

	क्रम (k = 0; k < v->NumberOfActivePlanes; ++k)
		क्रम (j = 0; j < v->NumberOfActivePlanes; ++j) // NumberOfPlanes
			अगर (j != k && v->BlendingAndTiming[k] == j
					&& v->DSCEnabled[j])
				v->DSCDelay[k] = v->DSCDelay[j];

	// Prefetch
	क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
		अचिन्हित पूर्णांक PDEAndMetaPTEBytesFrameY = 0;
		अचिन्हित पूर्णांक PixelPTEBytesPerRowY = 0;
		अचिन्हित पूर्णांक MetaRowByteY = 0;
		अचिन्हित पूर्णांक MetaRowByteC = 0;
		अचिन्हित पूर्णांक PDEAndMetaPTEBytesFrameC = 0;
		अचिन्हित पूर्णांक PixelPTEBytesPerRowC = 0;
		bool         PTEBufferSizeNotExceededY = 0;
		bool         PTEBufferSizeNotExceededC = 0;


		अगर (v->SourcePixelFormat[k] == dm_420_8 || v->SourcePixelFormat[k] == dm_420_10 || v->SourcePixelFormat[k] == dm_420_12 || v->SourcePixelFormat[k] == dm_rgbe_alpha) अणु
			अगर ((v->SourcePixelFormat[k] == dm_420_10 || v->SourcePixelFormat[k] == dm_420_12) && v->SourceScan[k] != dm_vert) अणु
				v->PTEBufferSizeInRequestsForLuma = (v->PTEBufferSizeInRequestsLuma + v->PTEBufferSizeInRequestsChroma) / 2;
				v->PTEBufferSizeInRequestsForChroma = v->PTEBufferSizeInRequestsForLuma;
			पूर्ण अन्यथा अणु
				v->PTEBufferSizeInRequestsForLuma = v->PTEBufferSizeInRequestsLuma;
				v->PTEBufferSizeInRequestsForChroma = v->PTEBufferSizeInRequestsChroma;

			पूर्ण
			PDEAndMetaPTEBytesFrameC = CalculateVMAndRowBytes(
					mode_lib,
					v->DCCEnable[k],
					v->BlockHeight256BytesC[k],
					v->BlockWidth256BytesC[k],
					v->SourcePixelFormat[k],
					v->SurfaceTiling[k],
					v->BytePerPixelC[k],
					v->SourceScan[k],
					v->SwathWidthC[k],
					v->ViewportHeightChroma[k],
					v->GPUVMEnable,
					v->HostVMEnable,
					v->HostVMMaxNonCachedPageTableLevels,
					v->GPUVMMinPageSize,
					v->HostVMMinPageSize,
					v->PTEBufferSizeInRequestsForChroma,
					v->PitchC[k],
					v->DCCMetaPitchC[k],
					&v->MacroTileWidthC[k],
					&MetaRowByteC,
					&PixelPTEBytesPerRowC,
					&PTEBufferSizeNotExceededC,
					&v->dpte_row_width_chroma_ub[k],
					&v->dpte_row_height_chroma[k],
					&v->meta_req_width_chroma[k],
					&v->meta_req_height_chroma[k],
					&v->meta_row_width_chroma[k],
					&v->meta_row_height_chroma[k],
					&v->dummyपूर्णांकeger1,
					&v->dummyपूर्णांकeger2,
					&v->PixelPTEReqWidthC[k],
					&v->PixelPTEReqHeightC[k],
					&v->PTERequestSizeC[k],
					&v->dpde0_bytes_per_frame_ub_c[k],
					&v->meta_pte_bytes_per_frame_ub_c[k]);

			v->PrefetchSourceLinesC[k] = CalculatePrefetchSourceLines(
					mode_lib,
					v->VRatioChroma[k],
					v->VTAPsChroma[k],
					v->Interlace[k],
					v->ProgressiveToInterlaceUnitInOPP,
					v->SwathHeightC[k],
					v->ViewportYStartC[k],
					&v->VInitPreFillC[k],
					&v->MaxNumSwathC[k]);
		पूर्ण अन्यथा अणु
			v->PTEBufferSizeInRequestsForLuma = v->PTEBufferSizeInRequestsLuma + v->PTEBufferSizeInRequestsChroma;
			v->PTEBufferSizeInRequestsForChroma = 0;
			PixelPTEBytesPerRowC = 0;
			PDEAndMetaPTEBytesFrameC = 0;
			MetaRowByteC = 0;
			v->MaxNumSwathC[k] = 0;
			v->PrefetchSourceLinesC[k] = 0;
		पूर्ण

		PDEAndMetaPTEBytesFrameY = CalculateVMAndRowBytes(
				mode_lib,
				v->DCCEnable[k],
				v->BlockHeight256BytesY[k],
				v->BlockWidth256BytesY[k],
				v->SourcePixelFormat[k],
				v->SurfaceTiling[k],
				v->BytePerPixelY[k],
				v->SourceScan[k],
				v->SwathWidthY[k],
				v->ViewportHeight[k],
				v->GPUVMEnable,
				v->HostVMEnable,
				v->HostVMMaxNonCachedPageTableLevels,
				v->GPUVMMinPageSize,
				v->HostVMMinPageSize,
				v->PTEBufferSizeInRequestsForLuma,
				v->PitchY[k],
				v->DCCMetaPitchY[k],
				&v->MacroTileWidthY[k],
				&MetaRowByteY,
				&PixelPTEBytesPerRowY,
				&PTEBufferSizeNotExceededY,
				&v->dpte_row_width_luma_ub[k],
				&v->dpte_row_height[k],
				&v->meta_req_width[k],
				&v->meta_req_height[k],
				&v->meta_row_width[k],
				&v->meta_row_height[k],
				&v->vm_group_bytes[k],
				&v->dpte_group_bytes[k],
				&v->PixelPTEReqWidthY[k],
				&v->PixelPTEReqHeightY[k],
				&v->PTERequestSizeY[k],
				&v->dpde0_bytes_per_frame_ub_l[k],
				&v->meta_pte_bytes_per_frame_ub_l[k]);

		v->PrefetchSourceLinesY[k] = CalculatePrefetchSourceLines(
				mode_lib,
				v->VRatio[k],
				v->vtaps[k],
				v->Interlace[k],
				v->ProgressiveToInterlaceUnitInOPP,
				v->SwathHeightY[k],
				v->ViewportYStartY[k],
				&v->VInitPreFillY[k],
				&v->MaxNumSwathY[k]);
		v->PixelPTEBytesPerRow[k] = PixelPTEBytesPerRowY + PixelPTEBytesPerRowC;
		v->PDEAndMetaPTEBytesFrame[k] = PDEAndMetaPTEBytesFrameY
				+ PDEAndMetaPTEBytesFrameC;
		v->MetaRowByte[k] = MetaRowByteY + MetaRowByteC;

		CalculateRowBandwidth(
				v->GPUVMEnable,
				v->SourcePixelFormat[k],
				v->VRatio[k],
				v->VRatioChroma[k],
				v->DCCEnable[k],
				v->HTotal[k] / v->PixelClock[k],
				MetaRowByteY,
				MetaRowByteC,
				v->meta_row_height[k],
				v->meta_row_height_chroma[k],
				PixelPTEBytesPerRowY,
				PixelPTEBytesPerRowC,
				v->dpte_row_height[k],
				v->dpte_row_height_chroma[k],
				&v->meta_row_bw[k],
				&v->dpte_row_bw[k]);
	पूर्ण

	v->TotalDCCActiveDPP = 0;
	v->TotalActiveDPP = 0;
	क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
		v->TotalActiveDPP = v->TotalActiveDPP
				+ v->DPPPerPlane[k];
		अगर (v->DCCEnable[k])
			v->TotalDCCActiveDPP = v->TotalDCCActiveDPP
					+ v->DPPPerPlane[k];
	पूर्ण


	ReorderBytes = v->NumberOfChannels * dml_max3(
		v->UrgentOutOfOrderReturnPerChannelPixelDataOnly,
		v->UrgentOutOfOrderReturnPerChannelPixelMixedWithVMData,
		v->UrgentOutOfOrderReturnPerChannelVMDataOnly);

	v->UrgentExtraLatency = CalculateExtraLatency(
		v->RoundTripPingLatencyCycles,
		ReorderBytes,
		v->DCFCLK,
		v->TotalActiveDPP,
		v->PixelChunkSizeInKByte,
		v->TotalDCCActiveDPP,
		v->MetaChunkSize,
		v->ReturnBW,
		v->GPUVMEnable,
		v->HostVMEnable,
		v->NumberOfActivePlanes,
		v->DPPPerPlane,
		v->dpte_group_bytes,
		v->PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData,
		v->PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly,
		v->HostVMMinPageSize,
		v->HostVMMaxNonCachedPageTableLevels);

	v->TCalc = 24.0 / v->DCFCLKDeepSleep;

	क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
		अगर (v->BlendingAndTiming[k] == k) अणु
			अगर (v->WritebackEnable[k] == true) अणु
				v->WritebackDelay[v->VoltageLevel][k] = v->WritebackLatency +
						CalculateWriteBackDelay(v->WritebackPixelFormat[k],
									v->WritebackHRatio[k],
									v->WritebackVRatio[k],
									v->WritebackVTaps[k],
									v->WritebackDestinationWidth[k],
									v->WritebackDestinationHeight[k],
									v->WritebackSourceHeight[k],
									v->HTotal[k]) / v->DISPCLK;
			पूर्ण अन्यथा
				v->WritebackDelay[v->VoltageLevel][k] = 0;
			क्रम (j = 0; j < v->NumberOfActivePlanes; ++j) अणु
				अगर (v->BlendingAndTiming[j] == k
						&& v->WritebackEnable[j] == true) अणु
					v->WritebackDelay[v->VoltageLevel][k] = dml_max(v->WritebackDelay[v->VoltageLevel][k],
							v->WritebackLatency + CalculateWriteBackDelay(
											v->WritebackPixelFormat[j],
											v->WritebackHRatio[j],
											v->WritebackVRatio[j],
											v->WritebackVTaps[j],
											v->WritebackDestinationWidth[j],
											v->WritebackDestinationHeight[j],
											v->WritebackSourceHeight[j],
											v->HTotal[k]) / v->DISPCLK);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (k = 0; k < v->NumberOfActivePlanes; ++k)
		क्रम (j = 0; j < v->NumberOfActivePlanes; ++j)
			अगर (v->BlendingAndTiming[k] == j)
				v->WritebackDelay[v->VoltageLevel][k] = v->WritebackDelay[v->VoltageLevel][j];

	क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
		v->MaxVStartupLines[k] = v->VTotal[k] - v->VActive[k] - dml_max(1.0, dml_उच्चमान((द्विगुन) v->WritebackDelay[v->VoltageLevel][k] / (v->HTotal[k] / v->PixelClock[k]), 1));
	पूर्ण

	v->MaximumMaxVStartupLines = 0;
	क्रम (k = 0; k < v->NumberOfActivePlanes; ++k)
		v->MaximumMaxVStartupLines = dml_max(v->MaximumMaxVStartupLines, v->MaxVStartupLines[k]);

	अगर (v->DRAMClockChangeLatencyOverride > 0.0) अणु
		v->FinalDRAMClockChangeLatency = v->DRAMClockChangeLatencyOverride;
	पूर्ण अन्यथा अणु
		v->FinalDRAMClockChangeLatency = v->DRAMClockChangeLatency;
	पूर्ण
	v->UrgentLatency = CalculateUrgentLatency(v->UrgentLatencyPixelDataOnly, v->UrgentLatencyPixelMixedWithVMData, v->UrgentLatencyVMDataOnly, v->DoUrgentLatencyAdjusपंचांगent, v->UrgentLatencyAdjusपंचांगentFabricClockComponent, v->UrgentLatencyAdjusपंचांगentFabricClockReference, v->FabricClock);


	v->FractionOfUrgentBandwidth = 0.0;
	v->FractionOfUrgentBandwidthImmediateFlip = 0.0;

	v->VStartupLines = 13;

	करो अणु
		MaxTotalRDBandwidth = 0;
		MaxTotalRDBandwidthNoUrgentBurst = 0;
		DestinationLineTimesForPrefetchLessThan2 = false;
		VRatioPrefetchMoreThan4 = false;
		TWait = CalculateTWait(
				PrefetchMode,
				v->FinalDRAMClockChangeLatency,
				v->UrgentLatency,
				v->SREnterPlusExitTime);

		क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
			Pipe myPipe = अणु 0 पूर्ण;

			myPipe.DPPCLK = v->DPPCLK[k];
			myPipe.DISPCLK = v->DISPCLK;
			myPipe.PixelClock = v->PixelClock[k];
			myPipe.DCFCLKDeepSleep = v->DCFCLKDeepSleep;
			myPipe.DPPPerPlane = v->DPPPerPlane[k];
			myPipe.ScalerEnabled = v->ScalerEnabled[k];
			myPipe.SourceScan = v->SourceScan[k];
			myPipe.BlockWidth256BytesY = v->BlockWidth256BytesY[k];
			myPipe.BlockHeight256BytesY = v->BlockHeight256BytesY[k];
			myPipe.BlockWidth256BytesC = v->BlockWidth256BytesC[k];
			myPipe.BlockHeight256BytesC = v->BlockHeight256BytesC[k];
			myPipe.InterlaceEnable = v->Interlace[k];
			myPipe.NumberOfCursors = v->NumberOfCursors[k];
			myPipe.VBlank = v->VTotal[k] - v->VActive[k];
			myPipe.HTotal = v->HTotal[k];
			myPipe.DCCEnable = v->DCCEnable[k];
			myPipe.ODMCombineEnabled = !!v->ODMCombineEnabled[k];

			v->ErrorResult[k] = CalculatePrefetchSchedule(
					mode_lib,
					v->PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData,
					v->PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly,
					&myPipe,
					v->DSCDelay[k],
					v->DPPCLKDelaySubtotal
							+ v->DPPCLKDelayCNVCFormater,
					v->DPPCLKDelaySCL,
					v->DPPCLKDelaySCLLBOnly,
					v->DPPCLKDelayCNVCCursor,
					v->DISPCLKDelaySubtotal,
					(अचिन्हित पूर्णांक) (v->SwathWidthY[k] / v->HRatio[k]),
					v->OutputFormat[k],
					v->MaxInterDCNTileRepeaters,
					dml_min(v->VStartupLines, v->MaxVStartupLines[k]),
					v->MaxVStartupLines[k],
					v->GPUVMMaxPageTableLevels,
					v->GPUVMEnable,
					v->HostVMEnable,
					v->HostVMMaxNonCachedPageTableLevels,
					v->HostVMMinPageSize,
					v->DynamicMetadataEnable[k],
					v->DynamicMetadataVMEnabled,
					v->DynamicMetadataLinesBeक्रमeActiveRequired[k],
					v->DynamicMetadataTransmittedBytes[k],
					v->UrgentLatency,
					v->UrgentExtraLatency,
					v->TCalc,
					v->PDEAndMetaPTEBytesFrame[k],
					v->MetaRowByte[k],
					v->PixelPTEBytesPerRow[k],
					v->PrefetchSourceLinesY[k],
					v->SwathWidthY[k],
					v->BytePerPixelY[k],
					v->VInitPreFillY[k],
					v->MaxNumSwathY[k],
					v->PrefetchSourceLinesC[k],
					v->SwathWidthC[k],
					v->BytePerPixelC[k],
					v->VInitPreFillC[k],
					v->MaxNumSwathC[k],
					v->swath_width_luma_ub[k],
					v->swath_width_chroma_ub[k],
					v->SwathHeightY[k],
					v->SwathHeightC[k],
					TWait,
					v->ProgressiveToInterlaceUnitInOPP,
					&v->DSTXAfterScaler[k],
					&v->DSTYAfterScaler[k],
					&v->DestinationLinesForPrefetch[k],
					&v->PrefetchBandwidth[k],
					&v->DestinationLinesToRequestVMInVBlank[k],
					&v->DestinationLinesToRequestRowInVBlank[k],
					&v->VRatioPrefetchY[k],
					&v->VRatioPrefetchC[k],
					&v->RequiredPrefetchPixDataBWLuma[k],
					&v->RequiredPrefetchPixDataBWChroma[k],
					&v->NotEnoughTimeForDynamicMetadata[k],
					&v->Tno_bw[k],
					&v->prefetch_vmrow_bw[k],
					&v->Tdmdl_vm[k],
					&v->Tdmdl[k],
					&v->VUpdateOffsetPix[k],
					&v->VUpdateWidthPix[k],
					&v->VReadyOffsetPix[k]);
			अगर (v->BlendingAndTiming[k] == k) अणु
				द्विगुन TotalRepeaterDelayTime = v->MaxInterDCNTileRepeaters * (2 / v->DPPCLK[k] + 3 / v->DISPCLK);
				v->VUpdateWidthPix[k] = (14 / v->DCFCLKDeepSleep + 12 / v->DPPCLK[k] + TotalRepeaterDelayTime) * v->PixelClock[k];
				v->VReadyOffsetPix[k] = dml_max(150.0 / v->DPPCLK[k], TotalRepeaterDelayTime + 20 / v->DCFCLKDeepSleep + 10 / v->DPPCLK[k]) * v->PixelClock[k];
				v->VUpdateOffsetPix[k] = dml_उच्चमान(v->HTotal[k] / 4.0, 1);
				v->VStartup[k] = dml_min(v->VStartupLines, v->MaxVStartupLines[k]);
			पूर्ण अन्यथा अणु
				पूर्णांक x = v->BlendingAndTiming[k];
				द्विगुन TotalRepeaterDelayTime = v->MaxInterDCNTileRepeaters * (2 / v->DPPCLK[k] + 3 / v->DISPCLK);
				v->VUpdateWidthPix[k] = (14 / v->DCFCLKDeepSleep + 12 / v->DPPCLK[k] + TotalRepeaterDelayTime) * v->PixelClock[x];
				v->VReadyOffsetPix[k] = dml_max(150.0 / v->DPPCLK[k], TotalRepeaterDelayTime + 20 / v->DCFCLKDeepSleep + 10 / v->DPPCLK[k]) * v->PixelClock[x];
				v->VUpdateOffsetPix[k] = dml_उच्चमान(v->HTotal[x] / 4.0, 1);
				अगर (!v->MaxVStartupLines[x])
					v->MaxVStartupLines[x] = v->MaxVStartupLines[k];
				v->VStartup[k] = dml_min(v->VStartupLines, v->MaxVStartupLines[x]);
			पूर्ण
		पूर्ण

		v->NotEnoughUrgentLatencyHiding = false;
		v->NotEnoughUrgentLatencyHidingPre = false;

		क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
			v->cursor_bw[k] = v->NumberOfCursors[k]
					* v->CursorWidth[k][0] * v->CursorBPP[k][0]
					/ 8.0
					/ (v->HTotal[k] / v->PixelClock[k])
					* v->VRatio[k];
			v->cursor_bw_pre[k] = v->NumberOfCursors[k]
					* v->CursorWidth[k][0] * v->CursorBPP[k][0]
					/ 8.0
					/ (v->HTotal[k] / v->PixelClock[k])
					* v->VRatioPrefetchY[k];

			CalculateUrgentBurstFactor(
					v->swath_width_luma_ub[k],
					v->swath_width_chroma_ub[k],
					v->DETBufferSizeInKByte,
					v->SwathHeightY[k],
					v->SwathHeightC[k],
					v->HTotal[k] / v->PixelClock[k],
					v->UrgentLatency,
					v->CursorBufferSize,
					v->CursorWidth[k][0],
					v->CursorBPP[k][0],
					v->VRatio[k],
					v->VRatioChroma[k],
					v->BytePerPixelDETY[k],
					v->BytePerPixelDETC[k],
					v->DETBufferSizeY[k],
					v->DETBufferSizeC[k],
					&v->UrgentBurstFactorCursor[k],
					&v->UrgentBurstFactorLuma[k],
					&v->UrgentBurstFactorChroma[k],
					&v->NoUrgentLatencyHiding[k]);

			CalculateUrgentBurstFactor(
					v->swath_width_luma_ub[k],
					v->swath_width_chroma_ub[k],
					v->DETBufferSizeInKByte,
					v->SwathHeightY[k],
					v->SwathHeightC[k],
					v->HTotal[k] / v->PixelClock[k],
					v->UrgentLatency,
					v->CursorBufferSize,
					v->CursorWidth[k][0],
					v->CursorBPP[k][0],
					v->VRatioPrefetchY[k],
					v->VRatioPrefetchC[k],
					v->BytePerPixelDETY[k],
					v->BytePerPixelDETC[k],
					v->DETBufferSizeY[k],
					v->DETBufferSizeC[k],
					&v->UrgentBurstFactorCursorPre[k],
					&v->UrgentBurstFactorLumaPre[k],
					&v->UrgentBurstFactorChromaPre[k],
					&v->NoUrgentLatencyHidingPre[k]);

			MaxTotalRDBandwidth = MaxTotalRDBandwidth +
				dml_max3(v->DPPPerPlane[k] * v->prefetch_vmrow_bw[k],
					v->ReadBandwidthPlaneLuma[k] *
					v->UrgentBurstFactorLuma[k] +
					v->ReadBandwidthPlaneChroma[k] *
					v->UrgentBurstFactorChroma[k] +
					v->cursor_bw[k] *
					v->UrgentBurstFactorCursor[k] +
					v->DPPPerPlane[k] * (v->meta_row_bw[k] + v->dpte_row_bw[k]),
					v->DPPPerPlane[k] * (v->RequiredPrefetchPixDataBWLuma[k] * v->UrgentBurstFactorLumaPre[k] +
						v->RequiredPrefetchPixDataBWChroma[k] * v->UrgentBurstFactorChromaPre[k]) + v->cursor_bw_pre[k] *
					v->UrgentBurstFactorCursorPre[k]);

			MaxTotalRDBandwidthNoUrgentBurst = MaxTotalRDBandwidthNoUrgentBurst +
				dml_max3(v->DPPPerPlane[k] * v->prefetch_vmrow_bw[k],
					v->ReadBandwidthPlaneLuma[k] +
					v->ReadBandwidthPlaneChroma[k] +
					v->cursor_bw[k] +
					v->DPPPerPlane[k] * (v->meta_row_bw[k] + v->dpte_row_bw[k]),
					v->DPPPerPlane[k] * (v->RequiredPrefetchPixDataBWLuma[k] + v->RequiredPrefetchPixDataBWChroma[k]) + v->cursor_bw_pre[k]);

			अगर (v->DestinationLinesForPrefetch[k] < 2)
				DestinationLineTimesForPrefetchLessThan2 = true;
			अगर (v->VRatioPrefetchY[k] > 4 || v->VRatioPrefetchC[k] > 4)
				VRatioPrefetchMoreThan4 = true;
			अगर (v->NoUrgentLatencyHiding[k] == true)
				v->NotEnoughUrgentLatencyHiding = true;

			अगर (v->NoUrgentLatencyHidingPre[k] == true)
				v->NotEnoughUrgentLatencyHidingPre = true;
		पूर्ण
		v->FractionOfUrgentBandwidth = MaxTotalRDBandwidthNoUrgentBurst / v->ReturnBW;


		अगर (MaxTotalRDBandwidth <= v->ReturnBW && v->NotEnoughUrgentLatencyHiding == 0 && v->NotEnoughUrgentLatencyHidingPre == 0 && !VRatioPrefetchMoreThan4
				&& !DestinationLineTimesForPrefetchLessThan2)
			v->PrefetchModeSupported = true;
		अन्यथा अणु
			v->PrefetchModeSupported = false;
			dml_prपूर्णांक("DML: CalculatePrefetchSchedule ***failed***. Bandwidth violation. Results are NOT valid\n");
			dml_prपूर्णांक("DML: MaxTotalRDBandwidth:%f AvailReturnBandwidth:%f\n", MaxTotalRDBandwidth, v->ReturnBW);
			dml_prपूर्णांक("DML: VRatioPrefetch %s more than 4\n", (VRatioPrefetchMoreThan4) ? "is" : "is not");
			dml_prपूर्णांक("DML: DestinationLines for Prefetch %s less than 2\n", (DestinationLineTimesForPrefetchLessThan2) ? "is" : "is not");
		पूर्ण

		अगर (v->PrefetchModeSupported == true && v->ImmediateFlipSupport == true) अणु
			v->BandwidthAvailableForImmediateFlip = v->ReturnBW;
			क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
				v->BandwidthAvailableForImmediateFlip =
						v->BandwidthAvailableForImmediateFlip
								- dml_max(
										v->ReadBandwidthPlaneLuma[k] * v->UrgentBurstFactorLuma[k]
												+ v->ReadBandwidthPlaneChroma[k] * v->UrgentBurstFactorChroma[k]
												+ v->cursor_bw[k] * v->UrgentBurstFactorCursor[k],
										v->DPPPerPlane[k] * (v->RequiredPrefetchPixDataBWLuma[k] * v->UrgentBurstFactorLumaPre[k] +
										v->RequiredPrefetchPixDataBWChroma[k] * v->UrgentBurstFactorChromaPre[k]) +
										v->cursor_bw_pre[k] * v->UrgentBurstFactorCursorPre[k]);
			पूर्ण

			v->TotImmediateFlipBytes = 0;
			क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
				v->TotImmediateFlipBytes = v->TotImmediateFlipBytes + v->DPPPerPlane[k] * (v->PDEAndMetaPTEBytesFrame[k] + v->MetaRowByte[k] + v->PixelPTEBytesPerRow[k]);
			पूर्ण
			क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
				CalculateFlipSchedule(
						mode_lib,
						v->PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData,
						v->PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly,
						v->UrgentExtraLatency,
						v->UrgentLatency,
						v->GPUVMMaxPageTableLevels,
						v->HostVMEnable,
						v->HostVMMaxNonCachedPageTableLevels,
						v->GPUVMEnable,
						v->HostVMMinPageSize,
						v->PDEAndMetaPTEBytesFrame[k],
						v->MetaRowByte[k],
						v->PixelPTEBytesPerRow[k],
						v->BandwidthAvailableForImmediateFlip,
						v->TotImmediateFlipBytes,
						v->SourcePixelFormat[k],
						v->HTotal[k] / v->PixelClock[k],
						v->VRatio[k],
						v->VRatioChroma[k],
						v->Tno_bw[k],
						v->DCCEnable[k],
						v->dpte_row_height[k],
						v->meta_row_height[k],
						v->dpte_row_height_chroma[k],
						v->meta_row_height_chroma[k],
						&v->DestinationLinesToRequestVMInImmediateFlip[k],
						&v->DestinationLinesToRequestRowInImmediateFlip[k],
						&v->final_flip_bw[k],
						&v->ImmediateFlipSupportedForPipe[k]);
			पूर्ण
			v->total_dcn_पढ़ो_bw_with_flip = 0.0;
			v->total_dcn_पढ़ो_bw_with_flip_no_urgent_burst = 0.0;
			क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
				v->total_dcn_पढ़ो_bw_with_flip = v->total_dcn_पढ़ो_bw_with_flip + dml_max3(
					v->DPPPerPlane[k] * v->prefetch_vmrow_bw[k],
					v->DPPPerPlane[k] * v->final_flip_bw[k] +
					v->ReadBandwidthLuma[k] * v->UrgentBurstFactorLuma[k] +
					v->ReadBandwidthChroma[k] * v->UrgentBurstFactorChroma[k] +
					v->cursor_bw[k] * v->UrgentBurstFactorCursor[k],
					v->DPPPerPlane[k] * (v->final_flip_bw[k] +
					v->RequiredPrefetchPixDataBWLuma[k] * v->UrgentBurstFactorLumaPre[k] +
					v->RequiredPrefetchPixDataBWChroma[k] * v->UrgentBurstFactorChromaPre[k]) +
					v->cursor_bw_pre[k] * v->UrgentBurstFactorCursorPre[k]);
				v->total_dcn_पढ़ो_bw_with_flip_no_urgent_burst =
					v->total_dcn_पढ़ो_bw_with_flip_no_urgent_burst +
						dml_max3(v->DPPPerPlane[k] * v->prefetch_vmrow_bw[k],
							v->DPPPerPlane[k] * v->final_flip_bw[k] + v->ReadBandwidthPlaneLuma[k] + v->ReadBandwidthPlaneChroma[k] + v->cursor_bw[k],
							v->DPPPerPlane[k] * (v->final_flip_bw[k] + v->RequiredPrefetchPixDataBWLuma[k] + v->RequiredPrefetchPixDataBWChroma[k]) + v->cursor_bw_pre[k]);

			पूर्ण
			v->FractionOfUrgentBandwidthImmediateFlip = v->total_dcn_पढ़ो_bw_with_flip_no_urgent_burst / v->ReturnBW;

			v->ImmediateFlipSupported = true;
			अगर (v->total_dcn_पढ़ो_bw_with_flip > v->ReturnBW) अणु
				v->ImmediateFlipSupported = false;
				v->total_dcn_पढ़ो_bw_with_flip = MaxTotalRDBandwidth;
			पूर्ण
			क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
				अगर (v->ImmediateFlipSupportedForPipe[k] == false) अणु
					v->ImmediateFlipSupported = false;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			v->ImmediateFlipSupported = false;
		पूर्ण

		क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
			अगर (v->ErrorResult[k] || v->NotEnoughTimeForDynamicMetadata[k]) अणु
				v->PrefetchModeSupported = false;
				dml_prपूर्णांक("DML: CalculatePrefetchSchedule ***failed***. Prefetch schedule violation. Results are NOT valid\n");
			पूर्ण
		पूर्ण

		v->VStartupLines = v->VStartupLines + 1;
		v->PrefetchAndImmediateFlipSupported = (v->PrefetchModeSupported == true && ((!v->ImmediateFlipSupport && !v->HostVMEnable && v->ImmediateFlipRequirement != dm_immediate_flip_required) || v->ImmediateFlipSupported)) ? true : false;

	पूर्ण जबतक (!v->PrefetchModeSupported && v->VStartupLines <= v->MaximumMaxVStartupLines);
	ASSERT(v->PrefetchModeSupported);

	//Watermarks and NB P-State/DRAM Clock Change Support
	अणु
		क्रमागत घड़ी_change_support   DRAMClockChangeSupport = 0; // dummy
		CalculateWatermarksAndDRAMSpeedChangeSupport(
			mode_lib,
			PrefetchMode,
			v->NumberOfActivePlanes,
			v->MaxLineBufferLines,
			v->LineBufferSize,
			v->DPPOutputBufferPixels,
			v->DETBufferSizeInKByte,
			v->WritebackInterfaceBufferSize,
			v->DCFCLK,
			v->ReturnBW,
			v->GPUVMEnable,
			v->dpte_group_bytes,
			v->MetaChunkSize,
			v->UrgentLatency,
			v->UrgentExtraLatency,
			v->WritebackLatency,
			v->WritebackChunkSize,
			v->SOCCLK,
			v->FinalDRAMClockChangeLatency,
			v->SRExitTime,
			v->SREnterPlusExitTime,
			v->DCFCLKDeepSleep,
			v->DPPPerPlane,
			v->DCCEnable,
			v->DPPCLK,
			v->DETBufferSizeY,
			v->DETBufferSizeC,
			v->SwathHeightY,
			v->SwathHeightC,
			v->LBBitPerPixel,
			v->SwathWidthY,
			v->SwathWidthC,
			v->HRatio,
			v->HRatioChroma,
			v->vtaps,
			v->VTAPsChroma,
			v->VRatio,
			v->VRatioChroma,
			v->HTotal,
			v->PixelClock,
			v->BlendingAndTiming,
			v->BytePerPixelDETY,
			v->BytePerPixelDETC,
			v->DSTXAfterScaler,
			v->DSTYAfterScaler,
			v->WritebackEnable,
			v->WritebackPixelFormat,
			v->WritebackDestinationWidth,
			v->WritebackDestinationHeight,
			v->WritebackSourceHeight,
			&DRAMClockChangeSupport,
			&v->UrgentWatermark,
			&v->WritebackUrgentWatermark,
			&v->DRAMClockChangeWatermark,
			&v->WritebackDRAMClockChangeWatermark,
			&v->StutterExitWatermark,
			&v->StutterEnterPlusExitWatermark,
			&v->MinActiveDRAMClockChangeLatencySupported);

		क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
			अगर (v->WritebackEnable[k] == true) अणु
				अगर (v->BlendingAndTiming[k] == k) अणु
					v->ThisVStartup = v->VStartup[k];
				पूर्ण अन्यथा अणु
					क्रम (j = 0; j < v->NumberOfActivePlanes; ++j) अणु
						अगर (v->BlendingAndTiming[k] == j) अणु
							v->ThisVStartup = v->VStartup[j];
						पूर्ण
					पूर्ण
				पूर्ण
				v->WritebackAllowDRAMClockChangeEndPosition[k] = dml_max(0,
					v->ThisVStartup * v->HTotal[k] / v->PixelClock[k] - v->WritebackDRAMClockChangeWatermark);
			पूर्ण अन्यथा अणु
				v->WritebackAllowDRAMClockChangeEndPosition[k] = 0;
			पूर्ण
		पूर्ण

	पूर्ण


	//Display Pipeline Delivery Time in Prefetch, Groups
	CalculatePixelDeliveryTimes(
			v->NumberOfActivePlanes,
			v->VRatio,
			v->VRatioChroma,
			v->VRatioPrefetchY,
			v->VRatioPrefetchC,
			v->swath_width_luma_ub,
			v->swath_width_chroma_ub,
			v->DPPPerPlane,
			v->HRatio,
			v->HRatioChroma,
			v->PixelClock,
			v->PSCL_THROUGHPUT_LUMA,
			v->PSCL_THROUGHPUT_CHROMA,
			v->DPPCLK,
			v->BytePerPixelC,
			v->SourceScan,
			v->NumberOfCursors,
			v->CursorWidth,
			v->CursorBPP,
			v->BlockWidth256BytesY,
			v->BlockHeight256BytesY,
			v->BlockWidth256BytesC,
			v->BlockHeight256BytesC,
			v->DisplayPipeLineDeliveryTimeLuma,
			v->DisplayPipeLineDeliveryTimeChroma,
			v->DisplayPipeLineDeliveryTimeLumaPrefetch,
			v->DisplayPipeLineDeliveryTimeChromaPrefetch,
			v->DisplayPipeRequestDeliveryTimeLuma,
			v->DisplayPipeRequestDeliveryTimeChroma,
			v->DisplayPipeRequestDeliveryTimeLumaPrefetch,
			v->DisplayPipeRequestDeliveryTimeChromaPrefetch,
			v->CursorRequestDeliveryTime,
			v->CursorRequestDeliveryTimePrefetch);

	CalculateMetaAndPTETimes(
			v->NumberOfActivePlanes,
			v->GPUVMEnable,
			v->MetaChunkSize,
			v->MinMetaChunkSizeBytes,
			v->HTotal,
			v->VRatio,
			v->VRatioChroma,
			v->DestinationLinesToRequestRowInVBlank,
			v->DestinationLinesToRequestRowInImmediateFlip,
			v->DCCEnable,
			v->PixelClock,
			v->BytePerPixelY,
			v->BytePerPixelC,
			v->SourceScan,
			v->dpte_row_height,
			v->dpte_row_height_chroma,
			v->meta_row_width,
			v->meta_row_width_chroma,
			v->meta_row_height,
			v->meta_row_height_chroma,
			v->meta_req_width,
			v->meta_req_width_chroma,
			v->meta_req_height,
			v->meta_req_height_chroma,
			v->dpte_group_bytes,
			v->PTERequestSizeY,
			v->PTERequestSizeC,
			v->PixelPTEReqWidthY,
			v->PixelPTEReqHeightY,
			v->PixelPTEReqWidthC,
			v->PixelPTEReqHeightC,
			v->dpte_row_width_luma_ub,
			v->dpte_row_width_chroma_ub,
			v->DST_Y_PER_PTE_ROW_NOM_L,
			v->DST_Y_PER_PTE_ROW_NOM_C,
			v->DST_Y_PER_META_ROW_NOM_L,
			v->DST_Y_PER_META_ROW_NOM_C,
			v->TimePerMetaChunkNominal,
			v->TimePerChromaMetaChunkNominal,
			v->TimePerMetaChunkVBlank,
			v->TimePerChromaMetaChunkVBlank,
			v->TimePerMetaChunkFlip,
			v->TimePerChromaMetaChunkFlip,
			v->समय_per_pte_group_nom_luma,
			v->समय_per_pte_group_vblank_luma,
			v->समय_per_pte_group_flip_luma,
			v->समय_per_pte_group_nom_chroma,
			v->समय_per_pte_group_vblank_chroma,
			v->समय_per_pte_group_flip_chroma);

	CalculateVMGroupAndRequestTimes(
			v->NumberOfActivePlanes,
			v->GPUVMEnable,
			v->GPUVMMaxPageTableLevels,
			v->HTotal,
			v->BytePerPixelC,
			v->DestinationLinesToRequestVMInVBlank,
			v->DestinationLinesToRequestVMInImmediateFlip,
			v->DCCEnable,
			v->PixelClock,
			v->dpte_row_width_luma_ub,
			v->dpte_row_width_chroma_ub,
			v->vm_group_bytes,
			v->dpde0_bytes_per_frame_ub_l,
			v->dpde0_bytes_per_frame_ub_c,
			v->meta_pte_bytes_per_frame_ub_l,
			v->meta_pte_bytes_per_frame_ub_c,
			v->TimePerVMGroupVBlank,
			v->TimePerVMGroupFlip,
			v->TimePerVMRequestVBlank,
			v->TimePerVMRequestFlip);


	// Min TTUVBlank
	क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
		अगर (PrefetchMode == 0) अणु
			v->AllowDRAMClockChangeDuringVBlank[k] = true;
			v->AllowDRAMSelfRefreshDuringVBlank[k] = true;
			v->MinTTUVBlank[k] = dml_max(
					v->DRAMClockChangeWatermark,
					dml_max(
							v->StutterEnterPlusExitWatermark,
							v->UrgentWatermark));
		पूर्ण अन्यथा अगर (PrefetchMode == 1) अणु
			v->AllowDRAMClockChangeDuringVBlank[k] = false;
			v->AllowDRAMSelfRefreshDuringVBlank[k] = true;
			v->MinTTUVBlank[k] = dml_max(
					v->StutterEnterPlusExitWatermark,
					v->UrgentWatermark);
		पूर्ण अन्यथा अणु
			v->AllowDRAMClockChangeDuringVBlank[k] = false;
			v->AllowDRAMSelfRefreshDuringVBlank[k] = false;
			v->MinTTUVBlank[k] = v->UrgentWatermark;
		पूर्ण
		अगर (!v->DynamicMetadataEnable[k])
			v->MinTTUVBlank[k] = v->TCalc
					+ v->MinTTUVBlank[k];
	पूर्ण

	// DCC Configuration
	v->ActiveDPPs = 0;
	क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
		CalculateDCCConfiguration(v->DCCEnable[k], false, // We should always know the direction DCCProgrammingAssumesScanDirectionUnknown,
				v->SourcePixelFormat[k],
				v->SurfaceWidthY[k],
				v->SurfaceWidthC[k],
				v->SurfaceHeightY[k],
				v->SurfaceHeightC[k],
				v->DETBufferSizeInKByte * 1024,
				v->BlockHeight256BytesY[k],
				v->BlockHeight256BytesC[k],
				v->SurfaceTiling[k],
				v->BytePerPixelY[k],
				v->BytePerPixelC[k],
				v->BytePerPixelDETY[k],
				v->BytePerPixelDETC[k],
				v->SourceScan[k],
				&v->DCCYMaxUncompressedBlock[k],
				&v->DCCCMaxUncompressedBlock[k],
				&v->DCCYMaxCompressedBlock[k],
				&v->DCCCMaxCompressedBlock[k],
				&v->DCCYIndependentBlock[k],
				&v->DCCCIndependentBlock[k]);
	पूर्ण

	अणु
		//Maximum Bandwidth Used
		द्विगुन TotalWRBandwidth = 0;
		द्विगुन MaxPerPlaneVActiveWRBandwidth = 0;
		द्विगुन WRBandwidth = 0;
		द्विगुन MaxUsedBW = 0;
		क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
			अगर (v->WritebackEnable[k] == true
					&& v->WritebackPixelFormat[k] == dm_444_32) अणु
				WRBandwidth = v->WritebackDestinationWidth[k] * v->WritebackDestinationHeight[k]
						/ (v->HTotal[k] * v->WritebackSourceHeight[k] / v->PixelClock[k]) * 4;
			पूर्ण अन्यथा अगर (v->WritebackEnable[k] == true) अणु
				WRBandwidth = v->WritebackDestinationWidth[k] * v->WritebackDestinationHeight[k]
						/ (v->HTotal[k] * v->WritebackSourceHeight[k] / v->PixelClock[k]) * 8;
			पूर्ण
			TotalWRBandwidth = TotalWRBandwidth + WRBandwidth;
			MaxPerPlaneVActiveWRBandwidth = dml_max(MaxPerPlaneVActiveWRBandwidth, WRBandwidth);
		पूर्ण

		v->TotalDataReadBandwidth = 0;
		क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
			v->TotalDataReadBandwidth = v->TotalDataReadBandwidth
					+ v->ReadBandwidthPlaneLuma[k]
					+ v->ReadBandwidthPlaneChroma[k];
		पूर्ण

		अणु
			द्विगुन MaxPerPlaneVActiveRDBandwidth = 0;
			क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
				MaxPerPlaneVActiveRDBandwidth = dml_max(MaxPerPlaneVActiveRDBandwidth,
						v->ReadBandwidthPlaneLuma[k] + v->ReadBandwidthPlaneChroma[k]);

			पूर्ण
		पूर्ण

		MaxUsedBW = MaxTotalRDBandwidth + TotalWRBandwidth;
	पूर्ण

	// VStartup Margin
	v->VStartupMargin = 0;
	v->FirstMainPlane = true;
	क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
		अगर (v->BlendingAndTiming[k] == k) अणु
			द्विगुन margin = (v->MaxVStartupLines[k] - v->VStartup[k]) * v->HTotal[k]
					/ v->PixelClock[k];
			अगर (v->FirstMainPlane == true) अणु
				v->VStartupMargin = margin;
				v->FirstMainPlane = false;
			पूर्ण अन्यथा अणु
				v->VStartupMargin = dml_min(v->VStartupMargin, margin);
			पूर्ण
		पूर्ण
	पूर्ण

	// Stutter Efficiency
	CalculateStutterEfficiency(
			v->NumberOfActivePlanes,
			v->ROBBufferSizeInKByte,
			v->TotalDataReadBandwidth,
			v->DCFCLK,
			v->ReturnBW,
			v->SRExitTime,
			v->SynchronizedVBlank,
			v->DPPPerPlane,
			v->DETBufferSizeY,
			v->BytePerPixelY,
			v->BytePerPixelDETY,
			v->SwathWidthY,
			v->SwathHeightY,
			v->SwathHeightC,
			v->DCCRateLuma,
			v->DCCRateChroma,
			v->HTotal,
			v->VTotal,
			v->PixelClock,
			v->VRatio,
			v->SourceScan,
			v->BlockHeight256BytesY,
			v->BlockWidth256BytesY,
			v->BlockHeight256BytesC,
			v->BlockWidth256BytesC,
			v->DCCYMaxUncompressedBlock,
			v->DCCCMaxUncompressedBlock,
			v->VActive,
			v->DCCEnable,
			v->WritebackEnable,
			v->ReadBandwidthPlaneLuma,
			v->ReadBandwidthPlaneChroma,
			v->meta_row_bw,
			v->dpte_row_bw,
			&v->StutterEfficiencyNotIncludingVBlank,
			&v->StutterEfficiency,
			&v->StutterPeriod);
पूर्ण

अटल व्योम DisplayPipeConfiguration(काष्ठा display_mode_lib *mode_lib)
अणु
	// Display Pipe Configuration
	द्विगुन BytePerPixDETY[DC__NUM_DPP__MAX] = अणु 0 पूर्ण;
	द्विगुन BytePerPixDETC[DC__NUM_DPP__MAX] = अणु 0 पूर्ण;
	पूर्णांक BytePerPixY[DC__NUM_DPP__MAX] = अणु 0 पूर्ण;
	पूर्णांक BytePerPixC[DC__NUM_DPP__MAX] = अणु 0 पूर्ण;
	पूर्णांक Read256BytesBlockHeightY[DC__NUM_DPP__MAX] = अणु 0 पूर्ण;
	पूर्णांक Read256BytesBlockHeightC[DC__NUM_DPP__MAX] = अणु 0 पूर्ण;
	पूर्णांक Read256BytesBlockWidthY[DC__NUM_DPP__MAX] = अणु 0 पूर्ण;
	पूर्णांक Read256BytesBlockWidthC[DC__NUM_DPP__MAX] = अणु 0 पूर्ण;
	द्विगुन dummy1[DC__NUM_DPP__MAX] = अणु 0 पूर्ण;
	द्विगुन dummy2[DC__NUM_DPP__MAX] = अणु 0 पूर्ण;
	द्विगुन dummy3[DC__NUM_DPP__MAX] = अणु 0 पूर्ण;
	द्विगुन dummy4[DC__NUM_DPP__MAX] = अणु 0 पूर्ण;
	पूर्णांक dummy5[DC__NUM_DPP__MAX] = अणु 0 पूर्ण;
	पूर्णांक dummy6[DC__NUM_DPP__MAX] = अणु 0 पूर्ण;
	bool dummy7[DC__NUM_DPP__MAX] = अणु 0 पूर्ण;
	bool dummysinglestring = 0;
	अचिन्हित पूर्णांक k;

	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु

		CalculateBytePerPixelAnd256BBlockSizes(
				mode_lib->vba.SourcePixelFormat[k],
				mode_lib->vba.SurfaceTiling[k],
				&BytePerPixY[k],
				&BytePerPixC[k],
				&BytePerPixDETY[k],
				&BytePerPixDETC[k],
				&Read256BytesBlockHeightY[k],
				&Read256BytesBlockHeightC[k],
				&Read256BytesBlockWidthY[k],
				&Read256BytesBlockWidthC[k]);
	पूर्ण
	CalculateSwathAndDETConfiguration(
			false,
			mode_lib->vba.NumberOfActivePlanes,
			mode_lib->vba.DETBufferSizeInKByte,
			dummy1,
			dummy2,
			mode_lib->vba.SourceScan,
			mode_lib->vba.SourcePixelFormat,
			mode_lib->vba.SurfaceTiling,
			mode_lib->vba.ViewportWidth,
			mode_lib->vba.ViewportHeight,
			mode_lib->vba.SurfaceWidthY,
			mode_lib->vba.SurfaceWidthC,
			mode_lib->vba.SurfaceHeightY,
			mode_lib->vba.SurfaceHeightC,
			Read256BytesBlockHeightY,
			Read256BytesBlockHeightC,
			Read256BytesBlockWidthY,
			Read256BytesBlockWidthC,
			mode_lib->vba.ODMCombineEnabled,
			mode_lib->vba.BlendingAndTiming,
			BytePerPixY,
			BytePerPixC,
			BytePerPixDETY,
			BytePerPixDETC,
			mode_lib->vba.HActive,
			mode_lib->vba.HRatio,
			mode_lib->vba.HRatioChroma,
			mode_lib->vba.DPPPerPlane,
			dummy5,
			dummy6,
			dummy3,
			dummy4,
			mode_lib->vba.SwathHeightY,
			mode_lib->vba.SwathHeightC,
			mode_lib->vba.DETBufferSizeY,
			mode_lib->vba.DETBufferSizeC,
			dummy7,
			&dummysinglestring);
पूर्ण

अटल bool CalculateBytePerPixelAnd256BBlockSizes(
		क्रमागत source_क्रमmat_class SourcePixelFormat,
		क्रमागत dm_swizzle_mode SurfaceTiling,
		अचिन्हित पूर्णांक *BytePerPixelY,
		अचिन्हित पूर्णांक *BytePerPixelC,
		द्विगुन       *BytePerPixelDETY,
		द्विगुन       *BytePerPixelDETC,
		अचिन्हित पूर्णांक *BlockHeight256BytesY,
		अचिन्हित पूर्णांक *BlockHeight256BytesC,
		अचिन्हित पूर्णांक *BlockWidth256BytesY,
		अचिन्हित पूर्णांक *BlockWidth256BytesC)
अणु
	अगर (SourcePixelFormat == dm_444_64) अणु
		*BytePerPixelDETY = 8;
		*BytePerPixelDETC = 0;
		*BytePerPixelY = 8;
		*BytePerPixelC = 0;
	पूर्ण अन्यथा अगर (SourcePixelFormat == dm_444_32 || SourcePixelFormat == dm_rgbe) अणु
		*BytePerPixelDETY = 4;
		*BytePerPixelDETC = 0;
		*BytePerPixelY = 4;
		*BytePerPixelC = 0;
	पूर्ण अन्यथा अगर (SourcePixelFormat == dm_444_16) अणु
		*BytePerPixelDETY = 2;
		*BytePerPixelDETC = 0;
		*BytePerPixelY = 2;
		*BytePerPixelC = 0;
	पूर्ण अन्यथा अगर (SourcePixelFormat == dm_444_8) अणु
		*BytePerPixelDETY = 1;
		*BytePerPixelDETC = 0;
		*BytePerPixelY = 1;
		*BytePerPixelC = 0;
	पूर्ण अन्यथा अगर (SourcePixelFormat == dm_rgbe_alpha) अणु
		*BytePerPixelDETY = 4;
		*BytePerPixelDETC = 1;
		*BytePerPixelY = 4;
		*BytePerPixelC = 1;
	पूर्ण अन्यथा अगर (SourcePixelFormat == dm_420_8) अणु
		*BytePerPixelDETY = 1;
		*BytePerPixelDETC = 2;
		*BytePerPixelY = 1;
		*BytePerPixelC = 2;
	पूर्ण अन्यथा अगर (SourcePixelFormat == dm_420_12) अणु
		*BytePerPixelDETY = 2;
		*BytePerPixelDETC = 4;
		*BytePerPixelY = 2;
		*BytePerPixelC = 4;
	पूर्ण अन्यथा अणु
		*BytePerPixelDETY = 4.0 / 3;
		*BytePerPixelDETC = 8.0 / 3;
		*BytePerPixelY = 2;
		*BytePerPixelC = 4;
	पूर्ण

	अगर ((SourcePixelFormat == dm_444_64 || SourcePixelFormat == dm_444_32
			|| SourcePixelFormat == dm_444_16 || SourcePixelFormat == dm_444_8
			|| SourcePixelFormat == dm_mono_16 || SourcePixelFormat == dm_mono_8
			|| SourcePixelFormat == dm_rgbe)) अणु
		अगर (SurfaceTiling == dm_sw_linear) अणु
			*BlockHeight256BytesY = 1;
		पूर्ण अन्यथा अगर (SourcePixelFormat == dm_444_64) अणु
			*BlockHeight256BytesY = 4;
		पूर्ण अन्यथा अगर (SourcePixelFormat == dm_444_8) अणु
			*BlockHeight256BytesY = 16;
		पूर्ण अन्यथा अणु
			*BlockHeight256BytesY = 8;
		पूर्ण
		*BlockWidth256BytesY = 256U / *BytePerPixelY / *BlockHeight256BytesY;
		*BlockHeight256BytesC = 0;
		*BlockWidth256BytesC = 0;
	पूर्ण अन्यथा अणु
		अगर (SurfaceTiling == dm_sw_linear) अणु
			*BlockHeight256BytesY = 1;
			*BlockHeight256BytesC = 1;
		पूर्ण अन्यथा अगर (SourcePixelFormat == dm_rgbe_alpha) अणु
			*BlockHeight256BytesY = 8;
			*BlockHeight256BytesC = 16;
		पूर्ण अन्यथा अगर (SourcePixelFormat == dm_420_8) अणु
			*BlockHeight256BytesY = 16;
			*BlockHeight256BytesC = 8;
		पूर्ण अन्यथा अणु
			*BlockHeight256BytesY = 8;
			*BlockHeight256BytesC = 8;
		पूर्ण
		*BlockWidth256BytesY = 256U / *BytePerPixelY / *BlockHeight256BytesY;
		*BlockWidth256BytesC = 256U / *BytePerPixelC / *BlockHeight256BytesC;
	पूर्ण
	वापस true;
पूर्ण

अटल द्विगुन CalculateTWait(
		अचिन्हित पूर्णांक PrefetchMode,
		द्विगुन DRAMClockChangeLatency,
		द्विगुन UrgentLatency,
		द्विगुन SREnterPlusExitTime)
अणु
	अगर (PrefetchMode == 0) अणु
		वापस dml_max(DRAMClockChangeLatency + UrgentLatency,
				dml_max(SREnterPlusExitTime, UrgentLatency));
	पूर्ण अन्यथा अगर (PrefetchMode == 1) अणु
		वापस dml_max(SREnterPlusExitTime, UrgentLatency);
	पूर्ण अन्यथा अणु
		वापस UrgentLatency;
	पूर्ण
पूर्ण

द्विगुन dml30_CalculateWriteBackDISPCLK(
		क्रमागत source_क्रमmat_class WritebackPixelFormat,
		द्विगुन PixelClock,
		द्विगुन WritebackHRatio,
		द्विगुन WritebackVRatio,
		अचिन्हित पूर्णांक WritebackHTaps,
		अचिन्हित पूर्णांक WritebackVTaps,
		दीर्घ   WritebackSourceWidth,
		दीर्घ   WritebackDestinationWidth,
		अचिन्हित पूर्णांक HTotal,
		अचिन्हित पूर्णांक WritebackLineBufferSize)
अणु
	द्विगुन DISPCLK_H = 0, DISPCLK_V = 0, DISPCLK_HB = 0;

	DISPCLK_H = PixelClock * dml_उच्चमान(WritebackHTaps / 8.0, 1) / WritebackHRatio;
	DISPCLK_V = PixelClock * (WritebackVTaps * dml_उच्चमान(WritebackDestinationWidth / 6.0, 1) + 8.0) / HTotal;
	DISPCLK_HB = PixelClock * WritebackVTaps * (WritebackDestinationWidth * WritebackVTaps - WritebackLineBufferSize / 57.0) / 6.0 / WritebackSourceWidth;
	वापस dml_max3(DISPCLK_H, DISPCLK_V, DISPCLK_HB);
पूर्ण

अटल द्विगुन CalculateWriteBackDelay(
		क्रमागत source_क्रमmat_class WritebackPixelFormat,
		द्विगुन WritebackHRatio,
		द्विगुन WritebackVRatio,
		अचिन्हित पूर्णांक WritebackVTaps,
		दीर्घ         WritebackDestinationWidth,
		दीर्घ         WritebackDestinationHeight,
		दीर्घ         WritebackSourceHeight,
		अचिन्हित पूर्णांक HTotal)
अणु
	द्विगुन CalculateWriteBackDelay = 0;
	द्विगुन Line_length = 0;
	द्विगुन Output_lines_last_notclamped = 0;
	द्विगुन WritebackVInit = 0;

	WritebackVInit = (WritebackVRatio + WritebackVTaps + 1) / 2;
	Line_length = dml_max((द्विगुन) WritebackDestinationWidth, dml_उच्चमान(WritebackDestinationWidth / 6.0, 1) * WritebackVTaps);
	Output_lines_last_notclamped = WritebackDestinationHeight - 1 - dml_उच्चमान((WritebackSourceHeight - WritebackVInit) / WritebackVRatio, 1);
	अगर (Output_lines_last_notclamped < 0) अणु
		CalculateWriteBackDelay = 0;
	पूर्ण अन्यथा अणु
		CalculateWriteBackDelay = Output_lines_last_notclamped * Line_length + (HTotal - WritebackDestinationWidth) + 80;
	पूर्ण
	वापस CalculateWriteBackDelay;
पूर्ण


अटल व्योम CalculateDynamicMetadataParameters(पूर्णांक MaxInterDCNTileRepeaters, द्विगुन DPPCLK, द्विगुन DISPCLK,
		द्विगुन DCFClkDeepSleep, द्विगुन PixelClock, दीर्घ HTotal, दीर्घ VBlank, दीर्घ DynamicMetadataTransmittedBytes,
		दीर्घ DynamicMetadataLinesBeक्रमeActiveRequired, पूर्णांक InterlaceEnable, bool ProgressiveToInterlaceUnitInOPP,
		द्विगुन *Tsetup, द्विगुन *Tdmbf, द्विगुन *Tdmec, द्विगुन *Tdmsks)
अणु
	द्विगुन TotalRepeaterDelayTime = 0;
	द्विगुन VUpdateWidthPix = 0;
	द्विगुन VReadyOffsetPix = 0;
	द्विगुन VUpdateOffsetPix = 0;
	TotalRepeaterDelayTime = MaxInterDCNTileRepeaters * (2 / DPPCLK + 3 / DISPCLK);
	VUpdateWidthPix = (14 / DCFClkDeepSleep + 12 / DPPCLK + TotalRepeaterDelayTime) * PixelClock;
	VReadyOffsetPix = dml_max(150.0 / DPPCLK, TotalRepeaterDelayTime + 20 / DCFClkDeepSleep + 10 / DPPCLK) * PixelClock;
	VUpdateOffsetPix = dml_उच्चमान(HTotal / 4.0, 1);
	*Tsetup = (VUpdateOffsetPix + VUpdateWidthPix + VReadyOffsetPix) / PixelClock;
	*Tdmbf = DynamicMetadataTransmittedBytes / 4.0 / DISPCLK;
	*Tdmec = HTotal / PixelClock;
	अगर (DynamicMetadataLinesBeक्रमeActiveRequired == 0) अणु
		*Tdmsks = VBlank * HTotal / PixelClock / 2.0;
	पूर्ण अन्यथा अणु
		*Tdmsks = DynamicMetadataLinesBeक्रमeActiveRequired * HTotal / PixelClock;
	पूर्ण
	अगर (InterlaceEnable == 1 && ProgressiveToInterlaceUnitInOPP == false) अणु
		*Tdmsks = *Tdmsks / 2;
	पूर्ण
पूर्ण

अटल व्योम CalculateRowBandwidth(
		bool GPUVMEnable,
		क्रमागत source_क्रमmat_class SourcePixelFormat,
		द्विगुन VRatio,
		द्विगुन VRatioChroma,
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
	पूर्ण अन्यथा अगर (SourcePixelFormat == dm_420_8 || SourcePixelFormat == dm_420_10 || SourcePixelFormat == dm_420_12 || SourcePixelFormat == dm_rgbe_alpha) अणु
		*meta_row_bw = VRatio * MetaRowByteLuma / (meta_row_height_luma * LineTime)
				+ VRatioChroma * MetaRowByteChroma
						/ (meta_row_height_chroma * LineTime);
	पूर्ण अन्यथा अणु
		*meta_row_bw = VRatio * MetaRowByteLuma / (meta_row_height_luma * LineTime);
	पूर्ण

	अगर (GPUVMEnable != true) अणु
		*dpte_row_bw = 0;
	पूर्ण अन्यथा अगर (SourcePixelFormat == dm_420_8 || SourcePixelFormat == dm_420_10 || SourcePixelFormat == dm_420_12 || SourcePixelFormat == dm_rgbe_alpha) अणु
		*dpte_row_bw = VRatio * PixelPTEBytesPerRowLuma / (dpte_row_height_luma * LineTime)
				+ VRatioChroma * PixelPTEBytesPerRowChroma
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
		अचिन्हित पूर्णांक HostVMMaxNonCachedPageTableLevels,
		bool GPUVMEnable,
		द्विगुन HostVMMinPageSize,
		द्विगुन PDEAndMetaPTEBytesPerFrame,
		द्विगुन MetaRowBytes,
		द्विगुन DPTEBytesPerRow,
		द्विगुन BandwidthAvailableForImmediateFlip,
		अचिन्हित पूर्णांक TotImmediateFlipBytes,
		क्रमागत source_क्रमmat_class SourcePixelFormat,
		द्विगुन LineTime,
		द्विगुन VRatio,
		द्विगुन VRatioChroma,
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
	अचिन्हित पूर्णांक HostVMDynamicLevelsTrips = 0;
	द्विगुन TimeForFetchingMetaPTEImmediateFlip = 0;
	द्विगुन TimeForFetchingRowInVBlankImmediateFlip = 0;
	द्विगुन ImmediateFlipBW = 0;
	द्विगुन HostVMInefficiencyFactor = 0;

	अगर (GPUVMEnable == true && HostVMEnable == true) अणु
		HostVMInefficiencyFactor = PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData / PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly;
		HostVMDynamicLevelsTrips = HostVMMaxNonCachedPageTableLevels;
	पूर्ण अन्यथा अणु
		HostVMInefficiencyFactor = 1;
		HostVMDynamicLevelsTrips = 0;
	पूर्ण

	अगर (GPUVMEnable == true || DCCEnable == true) अणु
		ImmediateFlipBW = (PDEAndMetaPTEBytesPerFrame + MetaRowBytes + DPTEBytesPerRow) * BandwidthAvailableForImmediateFlip / TotImmediateFlipBytes;
	पूर्ण

	अगर (GPUVMEnable == true) अणु
		TimeForFetchingMetaPTEImmediateFlip = dml_max3(Tno_bw + PDEAndMetaPTEBytesPerFrame * HostVMInefficiencyFactor / ImmediateFlipBW,
				UrgentExtraLatency + UrgentLatency * (GPUVMMaxPageTableLevels * (HostVMDynamicLevelsTrips + 1) - 1), LineTime / 4.0);
	पूर्ण अन्यथा अणु
		TimeForFetchingMetaPTEImmediateFlip = 0;
	पूर्ण

	*DestinationLinesToRequestVMInImmediateFlip = dml_उच्चमान(4.0 * (TimeForFetchingMetaPTEImmediateFlip / LineTime), 1) / 4.0;
	अगर ((GPUVMEnable == true || DCCEnable == true)) अणु
		TimeForFetchingRowInVBlankImmediateFlip = dml_max3((MetaRowBytes + DPTEBytesPerRow * HostVMInefficiencyFactor) / ImmediateFlipBW,
				UrgentLatency * (HostVMDynamicLevelsTrips + 1), LineTime / 4);
	पूर्ण अन्यथा अणु
		TimeForFetchingRowInVBlankImmediateFlip = 0;
	पूर्ण

	*DestinationLinesToRequestRowInImmediateFlip = dml_उच्चमान(4.0 * (TimeForFetchingRowInVBlankImmediateFlip / LineTime), 1) / 4.0;

	अगर (GPUVMEnable == true) अणु
		*final_flip_bw = dml_max(PDEAndMetaPTEBytesPerFrame * HostVMInefficiencyFactor / (*DestinationLinesToRequestVMInImmediateFlip * LineTime),
				(MetaRowBytes + DPTEBytesPerRow * HostVMInefficiencyFactor) / (*DestinationLinesToRequestRowInImmediateFlip * LineTime));
	पूर्ण अन्यथा अगर ((GPUVMEnable == true || DCCEnable == true)) अणु
		*final_flip_bw = (MetaRowBytes + DPTEBytesPerRow * HostVMInefficiencyFactor) / (*DestinationLinesToRequestRowInImmediateFlip * LineTime);
	पूर्ण अन्यथा अणु
		*final_flip_bw = 0;
	पूर्ण


	अगर (SourcePixelFormat == dm_420_8 || SourcePixelFormat == dm_420_10 || SourcePixelFormat == dm_rgbe_alpha) अणु
		अगर (GPUVMEnable == true && DCCEnable != true) अणु
			min_row_समय = dml_min(dpte_row_height * LineTime / VRatio, dpte_row_height_chroma * LineTime / VRatioChroma);
		पूर्ण अन्यथा अगर (GPUVMEnable != true && DCCEnable == true) अणु
			min_row_समय = dml_min(meta_row_height * LineTime / VRatio, meta_row_height_chroma * LineTime / VRatioChroma);
		पूर्ण अन्यथा अणु
			min_row_समय = dml_min4(dpte_row_height * LineTime / VRatio, meta_row_height * LineTime / VRatio,
					dpte_row_height_chroma * LineTime / VRatioChroma, meta_row_height_chroma * LineTime / VRatioChroma);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (GPUVMEnable == true && DCCEnable != true) अणु
			min_row_समय = dpte_row_height * LineTime / VRatio;
		पूर्ण अन्यथा अगर (GPUVMEnable != true && DCCEnable == true) अणु
			min_row_समय = meta_row_height * LineTime / VRatio;
		पूर्ण अन्यथा अणु
			min_row_समय = dml_min(dpte_row_height * LineTime / VRatio, meta_row_height * LineTime / VRatio);
		पूर्ण
	पूर्ण

	अगर (*DestinationLinesToRequestVMInImmediateFlip >= 32 || *DestinationLinesToRequestRowInImmediateFlip >= 16
			|| TimeForFetchingMetaPTEImmediateFlip + 2 * TimeForFetchingRowInVBlankImmediateFlip > min_row_समय) अणु
		*ImmediateFlipSupportedForPipe = false;
	पूर्ण अन्यथा अणु
		*ImmediateFlipSupportedForPipe = true;
	पूर्ण
पूर्ण

अटल द्विगुन TruncToValidBPP(
		द्विगुन LinkBitRate,
		पूर्णांक Lanes,
		दीर्घ HTotal,
		दीर्घ HActive,
		द्विगुन PixelClock,
		द्विगुन DesiredBPP,
		bool DSCEnable,
		क्रमागत output_encoder_class Output,
		क्रमागत output_क्रमmat_class Format,
		अचिन्हित पूर्णांक DSCInputBitPerComponent,
		पूर्णांक DSCSlices,
		पूर्णांक AudioRate,
		पूर्णांक AudioLayout,
		क्रमागत odm_combine_mode ODMCombine)
अणु
	द्विगुन MaxLinkBPP = 0;
	पूर्णांक MinDSCBPP = 0;
	द्विगुन MaxDSCBPP = 0;
	पूर्णांक NonDSCBPP0 = 0;
	पूर्णांक NonDSCBPP1 = 0;
	पूर्णांक NonDSCBPP2 = 0;

	अगर (Format == dm_420) अणु
		NonDSCBPP0 = 12;
		NonDSCBPP1 = 15;
		NonDSCBPP2 = 18;
		MinDSCBPP = 6;
		MaxDSCBPP = 1.5 * DSCInputBitPerComponent - 1.0 / 16;
	पूर्ण अन्यथा अगर (Format == dm_444) अणु
		NonDSCBPP0 = 24;
		NonDSCBPP1 = 30;
		NonDSCBPP2 = 36;
		MinDSCBPP = 8;
		MaxDSCBPP = 3 * DSCInputBitPerComponent - 1.0 / 16;
	पूर्ण अन्यथा अणु
		अगर (Output == dm_hdmi) अणु
			NonDSCBPP0 = 24;
			NonDSCBPP1 = 24;
			NonDSCBPP2 = 24;
		पूर्ण
		अन्यथा अणु
			NonDSCBPP0 = 16;
			NonDSCBPP1 = 20;
			NonDSCBPP2 = 24;
		पूर्ण

		अगर (Format == dm_n422) अणु
			MinDSCBPP = 7;
			MaxDSCBPP = 2 * DSCInputBitPerComponent - 1.0 / 16.0;
		पूर्ण
		अन्यथा अणु
			MinDSCBPP = 8;
			MaxDSCBPP = 3 * DSCInputBitPerComponent - 1.0 / 16.0;
		पूर्ण
	पूर्ण

	अगर (DSCEnable && Output == dm_dp) अणु
		MaxLinkBPP = LinkBitRate / 10 * 8 * Lanes / PixelClock * (1 - 2.4 / 100);
	पूर्ण अन्यथा अणु
		MaxLinkBPP = LinkBitRate / 10 * 8 * Lanes / PixelClock;
	पूर्ण

	अगर (ODMCombine == dm_odm_combine_mode_4to1 && MaxLinkBPP > 16) अणु
		MaxLinkBPP = 16;
	पूर्ण अन्यथा अगर (ODMCombine == dm_odm_combine_mode_2to1 && MaxLinkBPP > 32) अणु
		MaxLinkBPP = 32;
	पूर्ण


	अगर (DesiredBPP == 0) अणु
		अगर (DSCEnable) अणु
			अगर (MaxLinkBPP < MinDSCBPP) अणु
				वापस BPP_INVALID;
			पूर्ण अन्यथा अगर (MaxLinkBPP >= MaxDSCBPP) अणु
				वापस MaxDSCBPP;
			पूर्ण अन्यथा अणु
				वापस dml_न्यूनमान(16.0 * MaxLinkBPP, 1.0) / 16.0;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (MaxLinkBPP >= NonDSCBPP2) अणु
				वापस NonDSCBPP2;
			पूर्ण अन्यथा अगर (MaxLinkBPP >= NonDSCBPP1) अणु
				वापस NonDSCBPP1;
			पूर्ण अन्यथा अगर (MaxLinkBPP >= NonDSCBPP0) अणु
				वापस NonDSCBPP0;
			पूर्ण अन्यथा अणु
				वापस BPP_INVALID;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!((DSCEnable == false && (DesiredBPP == NonDSCBPP2 || DesiredBPP == NonDSCBPP1 || DesiredBPP == NonDSCBPP0 || DesiredBPP == 18)) ||
				(DSCEnable && DesiredBPP >= MinDSCBPP && DesiredBPP <= MaxDSCBPP))) अणु
			वापस BPP_INVALID;
		पूर्ण अन्यथा अणु
			वापस DesiredBPP;
		पूर्ण
	पूर्ण
	वापस BPP_INVALID;
पूर्ण

व्योम dml30_ModeSupportAndSystemConfigurationFull(काष्ठा display_mode_lib *mode_lib)
अणु
	काष्ठा vba_vars_st *v = &mode_lib->vba;
	पूर्णांक MinPrefetchMode = 0;
	पूर्णांक MaxPrefetchMode = 2;
	पूर्णांक i;
	अचिन्हित पूर्णांक j, k, m;
	bool   EnoughWritebackUnits = true;
	bool   WritebackModeSupport = true;
	bool   ViewportExceedsSurface = false;
	द्विगुन MaxTotalVActiveRDBandwidth = 0;
	दीर्घ ReorderingBytes = 0;
	bool NotUrgentLatencyHiding[DC__NUM_DPP__MAX] = अणु 0 पूर्ण;

	/*MODE SUPPORT, VOLTAGE STATE AND SOC CONFIGURATION*/

	/*Scale Ratio, taps Support Check*/

	v->ScaleRatioAndTapsSupport = true;
	क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
		अगर (v->ScalerEnabled[k] == false
				&& ((v->SourcePixelFormat[k] != dm_444_64
						&& v->SourcePixelFormat[k] != dm_444_32
						&& v->SourcePixelFormat[k] != dm_444_16
						&& v->SourcePixelFormat[k] != dm_mono_16
						&& v->SourcePixelFormat[k] != dm_mono_8
						&& v->SourcePixelFormat[k] != dm_rgbe
						&& v->SourcePixelFormat[k] != dm_rgbe_alpha)
						|| v->HRatio[k] != 1.0
						|| v->htaps[k] != 1.0
						|| v->VRatio[k] != 1.0
						|| v->vtaps[k] != 1.0)) अणु
			v->ScaleRatioAndTapsSupport = false;
		पूर्ण अन्यथा अगर (v->vtaps[k] < 1.0 || v->vtaps[k] > 8.0
				|| v->htaps[k] < 1.0 || v->htaps[k] > 8.0
				|| (v->htaps[k] > 1.0
						&& (v->htaps[k] % 2) == 1)
				|| v->HRatio[k] > v->MaxHSCLRatio
				|| v->VRatio[k] > v->MaxVSCLRatio
				|| v->HRatio[k] > v->htaps[k]
				|| v->VRatio[k] > v->vtaps[k]
				|| (v->SourcePixelFormat[k] != dm_444_64
						&& v->SourcePixelFormat[k] != dm_444_32
						&& v->SourcePixelFormat[k] != dm_444_16
						&& v->SourcePixelFormat[k] != dm_mono_16
						&& v->SourcePixelFormat[k] != dm_mono_8
						&& v->SourcePixelFormat[k] != dm_rgbe
						&& (v->VTAPsChroma[k] < 1
							|| v->VTAPsChroma[k] > 8
							|| v->HTAPsChroma[k] < 1
							|| v->HTAPsChroma[k] > 8
							|| (v->HTAPsChroma[k] > 1 && v->HTAPsChroma[k] % 2 == 1)
							|| v->HRatioChroma[k] > v->MaxHSCLRatio
							|| v->VRatioChroma[k] > v->MaxVSCLRatio
							|| v->HRatioChroma[k] > v->HTAPsChroma[k]
							|| v->VRatioChroma[k] > v->VTAPsChroma[k]))) अणु
			v->ScaleRatioAndTapsSupport = false;
		पूर्ण
	पूर्ण
	/*Source Format, Pixel Format and Scan Support Check*/

	v->SourceFormatPixelAndScanSupport = true;
	क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
		अगर ((v->SurfaceTiling[k] == dm_sw_linear && (!(v->SourceScan[k] != dm_vert) || v->DCCEnable[k] == true))
				|| ((v->SurfaceTiling[k] == dm_sw_64kb_d || v->SurfaceTiling[k] == dm_sw_64kb_d_t || v->SurfaceTiling[k] == dm_sw_64kb_d_x)
						&& !(v->SourcePixelFormat[k] == dm_444_64))) अणु
			v->SourceFormatPixelAndScanSupport = false;
		पूर्ण
	पूर्ण
	/*Bandwidth Support Check*/

	क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
		CalculateBytePerPixelAnd256BBlockSizes(
				v->SourcePixelFormat[k],
				v->SurfaceTiling[k],
				&v->BytePerPixelY[k],
				&v->BytePerPixelC[k],
				&v->BytePerPixelInDETY[k],
				&v->BytePerPixelInDETC[k],
				&v->Read256BlockHeightY[k],
				&v->Read256BlockHeightC[k],
				&v->Read256BlockWidthY[k],
				&v->Read256BlockWidthC[k]);
	पूर्ण
	क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
		अगर (v->SourceScan[k] != dm_vert) अणु
			v->SwathWidthYSingleDPP[k] = v->ViewportWidth[k];
			v->SwathWidthCSingleDPP[k] = v->ViewportWidthChroma[k];
		पूर्ण अन्यथा अणु
			v->SwathWidthYSingleDPP[k] = v->ViewportHeight[k];
			v->SwathWidthCSingleDPP[k] = v->ViewportHeightChroma[k];
		पूर्ण
	पूर्ण
	क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
		v->ReadBandwidthLuma[k] = v->SwathWidthYSingleDPP[k] * dml_उच्चमान(v->BytePerPixelInDETY[k], 1.0) / (v->HTotal[k] / v->PixelClock[k]) * v->VRatio[k];
		v->ReadBandwidthChroma[k] = v->SwathWidthYSingleDPP[k] / 2 * dml_उच्चमान(v->BytePerPixelInDETC[k], 2.0) / (v->HTotal[k] / v->PixelClock[k]) * v->VRatio[k] / 2.0;
	पूर्ण
	क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
		अगर (v->WritebackEnable[k] == true
				&& v->WritebackPixelFormat[k] == dm_444_64) अणु
			v->WriteBandwidth[k] = v->WritebackDestinationWidth[k]
					* v->WritebackDestinationHeight[k]
					/ (v->WritebackSourceHeight[k]
							* v->HTotal[k]
							/ v->PixelClock[k]) * 8.0;
		पूर्ण अन्यथा अगर (v->WritebackEnable[k] == true) अणु
			v->WriteBandwidth[k] = v->WritebackDestinationWidth[k]
					* v->WritebackDestinationHeight[k]
					/ (v->WritebackSourceHeight[k]
							* v->HTotal[k]
							/ v->PixelClock[k]) * 4.0;
		पूर्ण अन्यथा अणु
			v->WriteBandwidth[k] = 0.0;
		पूर्ण
	पूर्ण

	/*Writeback Latency support check*/

	v->WritebackLatencySupport = true;
	क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
		अगर (v->WritebackEnable[k] == true) अणु
			अगर (v->WritebackConfiguration == dm_whole_buffer_क्रम_single_stream_no_पूर्णांकerleave ||
			    v->WritebackConfiguration == dm_whole_buffer_क्रम_single_stream_पूर्णांकerleave) अणु
				अगर (v->WriteBandwidth[k]
						> 2.0 * v->WritebackInterfaceBufferSize * 1024
								/ v->WritebackLatency) अणु
					v->WritebackLatencySupport = false;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (v->WriteBandwidth[k]
						> v->WritebackInterfaceBufferSize * 1024
								/ v->WritebackLatency) अणु
					v->WritebackLatencySupport = false;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/*Writeback Mode Support Check*/

	v->TotalNumberOfActiveWriteback = 0;
	क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
		अगर (v->WritebackEnable[k] == true) अणु
			v->TotalNumberOfActiveWriteback =
					v->TotalNumberOfActiveWriteback + 1;
		पूर्ण
	पूर्ण

	अगर (v->TotalNumberOfActiveWriteback > v->MaxNumWriteback) अणु
		EnoughWritebackUnits = false;
	पूर्ण
	अगर (!v->WritebackSupportInterleaveAndUsingWholeBufferForASingleStream
			&& (v->WritebackConfiguration == dm_whole_buffer_क्रम_single_stream_no_पूर्णांकerleave
					|| v->WritebackConfiguration == dm_whole_buffer_क्रम_single_stream_पूर्णांकerleave)) अणु

		WritebackModeSupport = false;
	पूर्ण
	अगर (v->WritebackConfiguration == dm_whole_buffer_क्रम_single_stream_no_पूर्णांकerleave && v->TotalNumberOfActiveWriteback > 1) अणु
		WritebackModeSupport = false;
	पूर्ण

	/*Writeback Scale Ratio and Taps Support Check*/

	v->WritebackScaleRatioAndTapsSupport = true;
	क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
		अगर (v->WritebackEnable[k] == true) अणु
			अगर (v->WritebackHRatio[k] > v->WritebackMaxHSCLRatio
					|| v->WritebackVRatio[k]
							> v->WritebackMaxVSCLRatio
					|| v->WritebackHRatio[k]
							< v->WritebackMinHSCLRatio
					|| v->WritebackVRatio[k]
							< v->WritebackMinVSCLRatio
					|| v->WritebackHTaps[k]
							> v->WritebackMaxHSCLTaps
					|| v->WritebackVTaps[k]
							> v->WritebackMaxVSCLTaps
					|| v->WritebackHRatio[k]
							> v->WritebackHTaps[k]
					|| v->WritebackVRatio[k]
							> v->WritebackVTaps[k]
					|| (v->WritebackHTaps[k] > 2.0
							&& ((v->WritebackHTaps[k] % 2)
									== 1))) अणु
				v->WritebackScaleRatioAndTapsSupport = false;
			पूर्ण
			अगर (2.0 * v->WritebackDestinationWidth[k] * (v->WritebackVTaps[k] - 1) * 57 > v->WritebackLineBufferSize) अणु
				v->WritebackScaleRatioAndTapsSupport = false;
			पूर्ण
		पूर्ण
	पूर्ण
	/*Maximum DISPCLK/DPPCLK Support check*/

	v->WritebackRequiredDISPCLK = 0.0;
	क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
		अगर (v->WritebackEnable[k] == true) अणु
			v->WritebackRequiredDISPCLK = dml_max(v->WritebackRequiredDISPCLK,
					dml30_CalculateWriteBackDISPCLK(
							v->WritebackPixelFormat[k],
							v->PixelClock[k],
							v->WritebackHRatio[k],
							v->WritebackVRatio[k],
							v->WritebackHTaps[k],
							v->WritebackVTaps[k],
							v->WritebackSourceWidth[k],
							v->WritebackDestinationWidth[k],
							v->HTotal[k],
							v->WritebackLineBufferSize));
		पूर्ण
	पूर्ण
	क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
		अगर (v->HRatio[k] > 1.0) अणु
			v->PSCL_FACTOR[k] = dml_min(v->MaxDCHUBToPSCLThroughput, v->MaxPSCLToLBThroughput * v->HRatio[k] / dml_उच्चमान(v->htaps[k] / 6.0, 1.0));
		पूर्ण अन्यथा अणु
			v->PSCL_FACTOR[k] = dml_min(v->MaxDCHUBToPSCLThroughput, v->MaxPSCLToLBThroughput);
		पूर्ण
		अगर (v->BytePerPixelC[k] == 0.0) अणु
			v->PSCL_FACTOR_CHROMA[k] = 0.0;
			v->MinDPPCLKUsingSingleDPP[k] = v->PixelClock[k]
					* dml_max3(v->vtaps[k] / 6.0 * dml_min(1.0, v->HRatio[k]), v->HRatio[k] * v->VRatio[k] / v->PSCL_FACTOR[k], 1.0);
			अगर ((v->htaps[k] > 6.0 || v->vtaps[k] > 6.0) && v->MinDPPCLKUsingSingleDPP[k] < 2.0 * v->PixelClock[k]) अणु
				v->MinDPPCLKUsingSingleDPP[k] = 2.0 * v->PixelClock[k];
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (v->HRatioChroma[k] > 1.0) अणु
				v->PSCL_FACTOR_CHROMA[k] = dml_min(v->MaxDCHUBToPSCLThroughput,
						v->MaxPSCLToLBThroughput * v->HRatioChroma[k] / dml_उच्चमान(v->HTAPsChroma[k] / 6.0, 1.0));
			पूर्ण अन्यथा अणु
				v->PSCL_FACTOR_CHROMA[k] = dml_min(v->MaxDCHUBToPSCLThroughput, v->MaxPSCLToLBThroughput);
			पूर्ण
			v->MinDPPCLKUsingSingleDPP[k] = v->PixelClock[k] * dml_max5(v->vtaps[k] / 6.0 * dml_min(1.0, v->HRatio[k]),
							v->HRatio[k] * v->VRatio[k] / v->PSCL_FACTOR[k],
							v->VTAPsChroma[k] / 6.0 * dml_min(1.0, v->HRatioChroma[k]),
							v->HRatioChroma[k] * v->VRatioChroma[k] / v->PSCL_FACTOR_CHROMA[k],
							1.0);
			अगर ((v->htaps[k] > 6.0 || v->vtaps[k] > 6.0 || v->HTAPsChroma[k] > 6.0 || v->VTAPsChroma[k] > 6.0)
					&& v->MinDPPCLKUsingSingleDPP[k] < 2.0 * v->PixelClock[k]) अणु
				v->MinDPPCLKUsingSingleDPP[k] = 2.0 * v->PixelClock[k];
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
		पूर्णांक MaximumSwathWidthSupportLuma = 0;
		पूर्णांक MaximumSwathWidthSupportChroma = 0;

		अगर (v->SurfaceTiling[k] == dm_sw_linear) अणु
			MaximumSwathWidthSupportLuma = 8192.0;
		पूर्ण अन्यथा अगर (v->SourceScan[k] == dm_vert && v->BytePerPixelC[k] > 0) अणु
			MaximumSwathWidthSupportLuma = 2880.0;
		पूर्ण अन्यथा अणु
			MaximumSwathWidthSupportLuma = 5760.0;
		पूर्ण

		अगर (v->SourcePixelFormat[k] == dm_420_8 || v->SourcePixelFormat[k] == dm_420_10 || v->SourcePixelFormat[k] == dm_420_12) अणु
			MaximumSwathWidthSupportChroma = MaximumSwathWidthSupportLuma / 2.0;
		पूर्ण अन्यथा अणु
			MaximumSwathWidthSupportChroma = MaximumSwathWidthSupportLuma;
		पूर्ण
		v->MaximumSwathWidthInLineBufferLuma = v->LineBufferSize * dml_max(v->HRatio[k], 1.0) / v->LBBitPerPixel[k]
				/ (v->vtaps[k] + dml_max(dml_उच्चमान(v->VRatio[k], 1.0) - 2, 0.0));
		अगर (v->BytePerPixelC[k] == 0.0) अणु
			v->MaximumSwathWidthInLineBufferChroma = 0;
		पूर्ण अन्यथा अणु
			v->MaximumSwathWidthInLineBufferChroma = v->LineBufferSize * dml_max(v->HRatioChroma[k], 1.0) / v->LBBitPerPixel[k]
					/ (v->VTAPsChroma[k] + dml_max(dml_उच्चमान(v->VRatioChroma[k], 1.0) - 2, 0.0));
		पूर्ण
		v->MaximumSwathWidthLuma[k] = dml_min(MaximumSwathWidthSupportLuma, v->MaximumSwathWidthInLineBufferLuma);
		v->MaximumSwathWidthChroma[k] = dml_min(MaximumSwathWidthSupportChroma, v->MaximumSwathWidthInLineBufferChroma);
	पूर्ण

	CalculateSwathAndDETConfiguration(
			true,
			v->NumberOfActivePlanes,
			v->DETBufferSizeInKByte,
			v->MaximumSwathWidthLuma,
			v->MaximumSwathWidthChroma,
			v->SourceScan,
			v->SourcePixelFormat,
			v->SurfaceTiling,
			v->ViewportWidth,
			v->ViewportHeight,
			v->SurfaceWidthY,
			v->SurfaceWidthC,
			v->SurfaceHeightY,
			v->SurfaceHeightC,
			v->Read256BlockHeightY,
			v->Read256BlockHeightC,
			v->Read256BlockWidthY,
			v->Read256BlockWidthC,
			v->odm_combine_dummy,
			v->BlendingAndTiming,
			v->BytePerPixelY,
			v->BytePerPixelC,
			v->BytePerPixelInDETY,
			v->BytePerPixelInDETC,
			v->HActive,
			v->HRatio,
			v->HRatioChroma,
			v->DPPPerPlane,
			v->swath_width_luma_ub,
			v->swath_width_chroma_ub,
			v->SwathWidthY,
			v->SwathWidthC,
			v->SwathHeightY,
			v->SwathHeightC,
			v->DETBufferSizeY,
			v->DETBufferSizeC,
			v->SingleDPPViewportSizeSupportPerPlane,
			&v->ViewportSizeSupport[0][0]);

	क्रम (i = 0; i < v->soc.num_states; i++) अणु
		क्रम (j = 0; j < 2; j++) अणु
			v->MaxDispclkRoundedDownToDFSGranularity = RoundToDFSGranularityDown(v->MaxDispclk[i], v->DISPCLKDPPCLKVCOSpeed);
			v->MaxDppclkRoundedDownToDFSGranularity = RoundToDFSGranularityDown(v->MaxDppclk[i], v->DISPCLKDPPCLKVCOSpeed);
			v->RequiredDISPCLK[i][j] = 0.0;
			v->DISPCLK_DPPCLK_Support[i][j] = true;
			क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
				v->PlaneRequiredDISPCLKWithoutODMCombine = v->PixelClock[k] * (1.0 + v->DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0)
						* (1.0 + v->DISPCLKRampingMargin / 100.0);
				अगर ((v->PlaneRequiredDISPCLKWithoutODMCombine >= v->MaxDispclk[i] && v->MaxDispclk[i] == v->MaxDispclk[mode_lib->soc.num_states]
						&& v->MaxDppclk[i] == v->MaxDppclk[mode_lib->soc.num_states])) अणु
					v->PlaneRequiredDISPCLKWithoutODMCombine = v->PixelClock[k] * (1 + v->DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0);
				पूर्ण
				v->PlaneRequiredDISPCLKWithODMCombine2To1 = v->PixelClock[k] / 2 * (1 + v->DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0)
						* (1 + v->DISPCLKRampingMargin / 100.0);
				अगर ((v->PlaneRequiredDISPCLKWithODMCombine2To1 >= v->MaxDispclk[i] && v->MaxDispclk[i] == v->MaxDispclk[mode_lib->soc.num_states]
						&& v->MaxDppclk[i] == v->MaxDppclk[mode_lib->soc.num_states])) अणु
					v->PlaneRequiredDISPCLKWithODMCombine2To1 = v->PixelClock[k] / 2 * (1 + v->DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0);
				पूर्ण
				v->PlaneRequiredDISPCLKWithODMCombine4To1 = v->PixelClock[k] / 4 * (1 + v->DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0)
						* (1 + v->DISPCLKRampingMargin / 100.0);
				अगर ((v->PlaneRequiredDISPCLKWithODMCombine4To1 >= v->MaxDispclk[i] && v->MaxDispclk[i] == v->MaxDispclk[mode_lib->soc.num_states]
						&& v->MaxDppclk[i] == v->MaxDppclk[mode_lib->soc.num_states])) अणु
					v->PlaneRequiredDISPCLKWithODMCombine4To1 = v->PixelClock[k] / 4 * (1 + v->DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0);
				पूर्ण

				अगर (v->ODMCombinePolicy == dm_odm_combine_policy_none) अणु
					v->ODMCombineEnablePerState[i][k] = dm_odm_combine_mode_disabled;
					v->PlaneRequiredDISPCLK = v->PlaneRequiredDISPCLKWithoutODMCombine;
				पूर्ण अन्यथा अगर (v->ODMCombinePolicy == dm_odm_combine_policy_2to1) अणु
					v->ODMCombineEnablePerState[i][k] = dm_odm_combine_mode_2to1;
					v->PlaneRequiredDISPCLK = v->PlaneRequiredDISPCLKWithODMCombine2To1;
				पूर्ण अन्यथा अगर (v->ODMCombinePolicy == dm_odm_combine_policy_4to1
						|| v->PlaneRequiredDISPCLKWithODMCombine2To1 > v->MaxDispclkRoundedDownToDFSGranularity) अणु
					v->ODMCombineEnablePerState[i][k] = dm_odm_combine_mode_4to1;
					v->PlaneRequiredDISPCLK = v->PlaneRequiredDISPCLKWithODMCombine4To1;
				पूर्ण अन्यथा अगर (v->PlaneRequiredDISPCLKWithoutODMCombine > v->MaxDispclkRoundedDownToDFSGranularity) अणु
					v->ODMCombineEnablePerState[i][k] = dm_odm_combine_mode_2to1;
					v->PlaneRequiredDISPCLK = v->PlaneRequiredDISPCLKWithODMCombine2To1;
				पूर्ण अन्यथा अगर (v->DSCEnabled[k] && (v->HActive[k] > DCN30_MAX_DSC_IMAGE_WIDTH)) अणु
					v->ODMCombineEnablePerState[i][k] = dm_odm_combine_mode_2to1;
					v->PlaneRequiredDISPCLK = v->PlaneRequiredDISPCLKWithODMCombine2To1;
				पूर्ण अन्यथा अणु
					v->ODMCombineEnablePerState[i][k] = dm_odm_combine_mode_disabled;
					v->PlaneRequiredDISPCLK = v->PlaneRequiredDISPCLKWithoutODMCombine;
					/*420 क्रमmat workaround*/
					अगर (v->HActive[k] > 4096 && v->OutputFormat[k] == dm_420) अणु
						v->ODMCombineEnablePerState[i][k] = dm_odm_combine_mode_2to1;
						v->PlaneRequiredDISPCLK = v->PlaneRequiredDISPCLKWithODMCombine2To1;
					पूर्ण
				पूर्ण

				अगर (v->ODMCombineEnablePerState[i][k] == dm_odm_combine_mode_4to1) अणु
					v->MPCCombine[i][j][k] = false;
					v->NoOfDPP[i][j][k] = 4;
					v->RequiredDPPCLK[i][j][k] = v->MinDPPCLKUsingSingleDPP[k] * (1 + v->DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0) / 4;
				पूर्ण अन्यथा अगर (v->ODMCombineEnablePerState[i][k] == dm_odm_combine_mode_2to1) अणु
					v->MPCCombine[i][j][k] = false;
					v->NoOfDPP[i][j][k] = 2;
					v->RequiredDPPCLK[i][j][k] = v->MinDPPCLKUsingSingleDPP[k] * (1 + v->DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0) / 2;
				पूर्ण अन्यथा अगर ((v->WhenToDoMPCCombine == dm_mpc_never
						|| (v->MinDPPCLKUsingSingleDPP[k] * (1 + v->DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0) <= v->MaxDppclkRoundedDownToDFSGranularity
								&& v->SingleDPPViewportSizeSupportPerPlane[k] == true))) अणु
					v->MPCCombine[i][j][k] = false;
					v->NoOfDPP[i][j][k] = 1;
					v->RequiredDPPCLK[i][j][k] = v->MinDPPCLKUsingSingleDPP[k] * (1.0 + v->DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0);
				पूर्ण अन्यथा अणु
					v->MPCCombine[i][j][k] = true;
					v->NoOfDPP[i][j][k] = 2;
					v->RequiredDPPCLK[i][j][k] = v->MinDPPCLKUsingSingleDPP[k] * (1.0 + v->DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0) / 2.0;
				पूर्ण
				v->RequiredDISPCLK[i][j] = dml_max(v->RequiredDISPCLK[i][j], v->PlaneRequiredDISPCLK);
				अगर ((v->MinDPPCLKUsingSingleDPP[k] / v->NoOfDPP[i][j][k] * (1.0 + v->DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0)
						> v->MaxDppclkRoundedDownToDFSGranularity) || (v->PlaneRequiredDISPCLK > v->MaxDispclkRoundedDownToDFSGranularity)) अणु
					v->DISPCLK_DPPCLK_Support[i][j] = false;
				पूर्ण
			पूर्ण
			v->TotalNumberOfActiveDPP[i][j] = 0;
			v->TotalNumberOfSingleDPPPlanes[i][j] = 0;
			क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
				v->TotalNumberOfActiveDPP[i][j] = v->TotalNumberOfActiveDPP[i][j] + v->NoOfDPP[i][j][k];
				अगर (v->NoOfDPP[i][j][k] == 1)
					v->TotalNumberOfSingleDPPPlanes[i][j] = v->TotalNumberOfSingleDPPPlanes[i][j] + 1;
			पूर्ण
			अगर (j == 1 && v->WhenToDoMPCCombine != dm_mpc_never) अणु
				जबतक (!(v->TotalNumberOfActiveDPP[i][j] >= v->MaxNumDPP || v->TotalNumberOfSingleDPPPlanes[i][j] == 0)) अणु
					द्विगुन BWOfNonSplitPlaneOfMaximumBandwidth = 0;
					अचिन्हित पूर्णांक NumberOfNonSplitPlaneOfMaximumBandwidth = 0;
					BWOfNonSplitPlaneOfMaximumBandwidth = 0;
					NumberOfNonSplitPlaneOfMaximumBandwidth = 0;
					क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
						अगर (v->ReadBandwidthLuma[k] + v->ReadBandwidthChroma[k] > BWOfNonSplitPlaneOfMaximumBandwidth
								&& v->ODMCombineEnablePerState[i][k] == dm_odm_combine_mode_disabled && v->MPCCombine[i][j][k] == false) अणु
							BWOfNonSplitPlaneOfMaximumBandwidth = v->ReadBandwidthLuma[k] + v->ReadBandwidthChroma[k];
							NumberOfNonSplitPlaneOfMaximumBandwidth = k;
						पूर्ण
					पूर्ण
					v->MPCCombine[i][j][NumberOfNonSplitPlaneOfMaximumBandwidth] = true;
					v->NoOfDPP[i][j][NumberOfNonSplitPlaneOfMaximumBandwidth] = 2;
					v->RequiredDPPCLK[i][j][NumberOfNonSplitPlaneOfMaximumBandwidth] = v->MinDPPCLKUsingSingleDPP[NumberOfNonSplitPlaneOfMaximumBandwidth]
							* (1 + v->DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100) / 2;
					v->TotalNumberOfActiveDPP[i][j] = v->TotalNumberOfActiveDPP[i][j] + 1;
					v->TotalNumberOfSingleDPPPlanes[i][j] = v->TotalNumberOfSingleDPPPlanes[i][j] - 1;
				पूर्ण
			पूर्ण
			अगर (v->TotalNumberOfActiveDPP[i][j] > v->MaxNumDPP) अणु
				v->RequiredDISPCLK[i][j] = 0.0;
				v->DISPCLK_DPPCLK_Support[i][j] = true;
				क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
					v->ODMCombineEnablePerState[i][k] = dm_odm_combine_mode_disabled;
					अगर (v->SingleDPPViewportSizeSupportPerPlane[k] == false && v->WhenToDoMPCCombine != dm_mpc_never) अणु
						v->MPCCombine[i][j][k] = true;
						v->NoOfDPP[i][j][k] = 2;
						v->RequiredDPPCLK[i][j][k] = v->MinDPPCLKUsingSingleDPP[k] * (1.0 + v->DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0) / 2.0;
					पूर्ण अन्यथा अणु
						v->MPCCombine[i][j][k] = false;
						v->NoOfDPP[i][j][k] = 1;
						v->RequiredDPPCLK[i][j][k] = v->MinDPPCLKUsingSingleDPP[k] * (1.0 + v->DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0);
					पूर्ण
					अगर (!(v->MaxDispclk[i] == v->MaxDispclk[v->soc.num_states - 1] && v->MaxDppclk[i] == v->MaxDppclk[v->soc.num_states - 1])) अणु
						v->PlaneRequiredDISPCLK = v->PixelClock[k] * (1.0 + v->DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0)
								* (1.0 + v->DISPCLKRampingMargin / 100.0);
					पूर्ण अन्यथा अणु
						v->PlaneRequiredDISPCLK = v->PixelClock[k] * (1.0 + v->DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0);
					पूर्ण
					v->RequiredDISPCLK[i][j] = dml_max(v->RequiredDISPCLK[i][j], v->PlaneRequiredDISPCLK);
					अगर ((v->MinDPPCLKUsingSingleDPP[k] / v->NoOfDPP[i][j][k] * (1.0 + v->DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0)
							> v->MaxDppclkRoundedDownToDFSGranularity) || (v->PlaneRequiredDISPCLK > v->MaxDispclkRoundedDownToDFSGranularity)) अणु
						v->DISPCLK_DPPCLK_Support[i][j] = false;
					पूर्ण
				पूर्ण
				v->TotalNumberOfActiveDPP[i][j] = 0.0;
				क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
					v->TotalNumberOfActiveDPP[i][j] = v->TotalNumberOfActiveDPP[i][j] + v->NoOfDPP[i][j][k];
				पूर्ण
			पूर्ण
			v->RequiredDISPCLK[i][j] = dml_max(v->RequiredDISPCLK[i][j], v->WritebackRequiredDISPCLK);
			अगर (v->MaxDispclkRoundedDownToDFSGranularity < v->WritebackRequiredDISPCLK) अणु
				v->DISPCLK_DPPCLK_Support[i][j] = false;
			पूर्ण
		पूर्ण
	पूर्ण

	/*Total Available Pipes Support Check*/

	क्रम (i = 0; i < v->soc.num_states; i++) अणु
		क्रम (j = 0; j < 2; j++) अणु
			अगर (v->TotalNumberOfActiveDPP[i][j] <= v->MaxNumDPP) अणु
				v->TotalAvailablePipesSupport[i][j] = true;
			पूर्ण अन्यथा अणु
				v->TotalAvailablePipesSupport[i][j] = false;
			पूर्ण
		पूर्ण
	पूर्ण
	/*Display IO and DSC Support Check*/

	v->NonsupportedDSCInputBPC = false;
	क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
		अगर (!(v->DSCInputBitPerComponent[k] == 12.0
				|| v->DSCInputBitPerComponent[k] == 10.0
				|| v->DSCInputBitPerComponent[k] == 8.0)) अणु
			v->NonsupportedDSCInputBPC = true;
		पूर्ण
	पूर्ण

	/*Number Of DSC Slices*/
	क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
		अगर (v->BlendingAndTiming[k] == k) अणु
			अगर (v->PixelClockBackEnd[k] > 3200) अणु
				v->NumberOfDSCSlices[k] = dml_उच्चमान(v->PixelClockBackEnd[k] / 400.0, 4.0);
			पूर्ण अन्यथा अगर (v->PixelClockBackEnd[k] > 1360) अणु
				v->NumberOfDSCSlices[k] = 8;
			पूर्ण अन्यथा अगर (v->PixelClockBackEnd[k] > 680) अणु
				v->NumberOfDSCSlices[k] = 4;
			पूर्ण अन्यथा अगर (v->PixelClockBackEnd[k] > 340) अणु
				v->NumberOfDSCSlices[k] = 2;
			पूर्ण अन्यथा अणु
				v->NumberOfDSCSlices[k] = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			v->NumberOfDSCSlices[k] = 0;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < v->soc.num_states; i++) अणु
		क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
			v->RequiresDSC[i][k] = false;
			v->RequiresFEC[i][k] = false;
			अगर (v->BlendingAndTiming[k] == k) अणु
				अगर (v->Output[k] == dm_hdmi) अणु
					v->RequiresDSC[i][k] = false;
					v->RequiresFEC[i][k] = false;
					v->OutputBppPerState[i][k] = TruncToValidBPP(
							dml_min(600.0, v->PHYCLKPerState[i]) * 10,
							3,
							v->HTotal[k],
							v->HActive[k],
							v->PixelClockBackEnd[k],
							v->ForcedOutputLinkBPP[k],
							false,
							v->Output[k],
							v->OutputFormat[k],
							v->DSCInputBitPerComponent[k],
							v->NumberOfDSCSlices[k],
							v->AudioSampleRate[k],
							v->AudioSampleLayout[k],
							v->ODMCombineEnablePerState[i][k]);
				पूर्ण अन्यथा अगर (v->Output[k] == dm_dp || v->Output[k] == dm_edp) अणु
					अगर (v->DSCEnable[k] == true) अणु
						v->RequiresDSC[i][k] = true;
						v->LinkDSCEnable = true;
						अगर (v->Output[k] == dm_dp) अणु
							v->RequiresFEC[i][k] = true;
						पूर्ण अन्यथा अणु
							v->RequiresFEC[i][k] = false;
						पूर्ण
					पूर्ण अन्यथा अणु
						v->RequiresDSC[i][k] = false;
						v->LinkDSCEnable = false;
						v->RequiresFEC[i][k] = false;
					पूर्ण

					v->Outbpp = BPP_INVALID;
					अगर (v->PHYCLKPerState[i] >= 270.0) अणु
						v->Outbpp = TruncToValidBPP(
								(1.0 - v->Downspपढ़ोing / 100.0) * 2700,
								v->OutputLinkDPLanes[k],
								v->HTotal[k],
								v->HActive[k],
								v->PixelClockBackEnd[k],
								v->ForcedOutputLinkBPP[k],
								v->LinkDSCEnable,
								v->Output[k],
								v->OutputFormat[k],
								v->DSCInputBitPerComponent[k],
								v->NumberOfDSCSlices[k],
								v->AudioSampleRate[k],
								v->AudioSampleLayout[k],
								v->ODMCombineEnablePerState[i][k]);
						v->OutputBppPerState[i][k] = v->Outbpp;
						// TODO: Need some other way to handle this nonsense
						// v->OutputTypeAndRatePerState[i][k] = v->Output[k] & " HBR"
					पूर्ण
					अगर (v->Outbpp == BPP_INVALID && v->PHYCLKPerState[i] >= 540.0) अणु
						v->Outbpp = TruncToValidBPP(
								(1.0 - v->Downspपढ़ोing / 100.0) * 5400,
								v->OutputLinkDPLanes[k],
								v->HTotal[k],
								v->HActive[k],
								v->PixelClockBackEnd[k],
								v->ForcedOutputLinkBPP[k],
								v->LinkDSCEnable,
								v->Output[k],
								v->OutputFormat[k],
								v->DSCInputBitPerComponent[k],
								v->NumberOfDSCSlices[k],
								v->AudioSampleRate[k],
								v->AudioSampleLayout[k],
								v->ODMCombineEnablePerState[i][k]);
						v->OutputBppPerState[i][k] = v->Outbpp;
						// TODO: Need some other way to handle this nonsense
						// v->OutputTypeAndRatePerState[i][k] = v->Output[k] & " HBR2"
					पूर्ण
					अगर (v->Outbpp == BPP_INVALID && v->PHYCLKPerState[i] >= 810.0) अणु
						v->Outbpp = TruncToValidBPP(
								(1.0 - v->Downspपढ़ोing / 100.0) * 8100,
								v->OutputLinkDPLanes[k],
								v->HTotal[k],
								v->HActive[k],
								v->PixelClockBackEnd[k],
								v->ForcedOutputLinkBPP[k],
								v->LinkDSCEnable,
								v->Output[k],
								v->OutputFormat[k],
								v->DSCInputBitPerComponent[k],
								v->NumberOfDSCSlices[k],
								v->AudioSampleRate[k],
								v->AudioSampleLayout[k],
								v->ODMCombineEnablePerState[i][k]);
						अगर (v->Outbpp == BPP_INVALID && v->ForcedOutputLinkBPP[k] == 0) अणु
							//अगर (v->Outbpp == BPP_INVALID && v->DSCEnabled[k] == dm_dsc_enable_only_अगर_necessary && v->ForcedOutputLinkBPP[k] == 0) अणु
							v->RequiresDSC[i][k] = true;
							v->LinkDSCEnable = true;
							अगर (v->Output[k] == dm_dp) अणु
								v->RequiresFEC[i][k] = true;
							पूर्ण
							v->Outbpp = TruncToValidBPP(
									(1.0 - v->Downspपढ़ोing / 100.0) * 8100,
									v->OutputLinkDPLanes[k],
									v->HTotal[k],
									v->HActive[k],
									v->PixelClockBackEnd[k],
									v->ForcedOutputLinkBPP[k],
									v->LinkDSCEnable,
									v->Output[k],
									v->OutputFormat[k],
									v->DSCInputBitPerComponent[k],
									v->NumberOfDSCSlices[k],
									v->AudioSampleRate[k],
									v->AudioSampleLayout[k],
									v->ODMCombineEnablePerState[i][k]);
						पूर्ण
						v->OutputBppPerState[i][k] = v->Outbpp;
						// TODO: Need some other way to handle this nonsense
						// v->OutputTypeAndRatePerState[i][k] = v->Output[k] & " HBR3"
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अणु
				v->OutputBppPerState[i][k] = 0;
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < v->soc.num_states; i++) अणु
		v->DIOSupport[i] = true;
		क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
			अगर (!v->skip_dio_check[k] && v->BlendingAndTiming[k] == k && (v->Output[k] == dm_dp || v->Output[k] == dm_edp || v->Output[k] == dm_hdmi)
					&& (v->OutputBppPerState[i][k] == 0
							|| (v->OutputFormat[k] == dm_420 && v->Interlace[k] == true && v->ProgressiveToInterlaceUnitInOPP == true))) अणु
				v->DIOSupport[i] = false;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < v->soc.num_states; ++i) अणु
		v->ODMCombine4To1SupportCheckOK[i] = true;
		क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
			अगर (v->BlendingAndTiming[k] == k && v->ODMCombineEnablePerState[i][k] == dm_odm_combine_mode_4to1
					&& (v->ODMCombine4To1Supported == false || v->Output[k] == dm_dp || v->Output[k] == dm_edp || v->Output[k] == dm_hdmi)) अणु
				v->ODMCombine4To1SupportCheckOK[i] = false;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < v->soc.num_states; i++) अणु
		v->DSCCLKRequiredMoreThanSupported[i] = false;
		क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
			अगर (v->BlendingAndTiming[k] == k) अणु
				अगर (v->Output[k] == dm_dp || v->Output[k] == dm_edp) अणु
					अगर (v->OutputFormat[k] == dm_420) अणु
						v->DSCFormatFactor = 2;
					पूर्ण अन्यथा अगर (v->OutputFormat[k] == dm_444) अणु
						v->DSCFormatFactor = 1;
					पूर्ण अन्यथा अगर (v->OutputFormat[k] == dm_n422) अणु
						v->DSCFormatFactor = 2;
					पूर्ण अन्यथा अणु
						v->DSCFormatFactor = 1;
					पूर्ण
					अगर (v->RequiresDSC[i][k] == true) अणु
						अगर (v->ODMCombineEnablePerState[i][k] == dm_odm_combine_mode_4to1) अणु
							अगर (v->PixelClockBackEnd[k] / 12.0 / v->DSCFormatFactor
									> (1.0 - v->DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0) * v->MaxDSCCLK[i]) अणु
								v->DSCCLKRequiredMoreThanSupported[i] = true;
							पूर्ण
						पूर्ण अन्यथा अगर (v->ODMCombineEnablePerState[i][k] == dm_odm_combine_mode_2to1) अणु
							अगर (v->PixelClockBackEnd[k] / 6.0 / v->DSCFormatFactor
									> (1.0 - v->DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0) * v->MaxDSCCLK[i]) अणु
								v->DSCCLKRequiredMoreThanSupported[i] = true;
							पूर्ण
						पूर्ण अन्यथा अणु
							अगर (v->PixelClockBackEnd[k] / 3.0 / v->DSCFormatFactor
									> (1.0 - v->DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0) * v->MaxDSCCLK[i]) अणु
								v->DSCCLKRequiredMoreThanSupported[i] = true;
							पूर्ण
						पूर्ण
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < v->soc.num_states; i++) अणु
		v->NotEnoughDSCUnits[i] = false;
		v->TotalDSCUnitsRequired = 0.0;
		क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
			अगर (v->RequiresDSC[i][k] == true) अणु
				अगर (v->ODMCombineEnablePerState[i][k] == dm_odm_combine_mode_4to1) अणु
					v->TotalDSCUnitsRequired = v->TotalDSCUnitsRequired + 4.0;
				पूर्ण अन्यथा अगर (v->ODMCombineEnablePerState[i][k] == dm_odm_combine_mode_2to1) अणु
					v->TotalDSCUnitsRequired = v->TotalDSCUnitsRequired + 2.0;
				पूर्ण अन्यथा अणु
					v->TotalDSCUnitsRequired = v->TotalDSCUnitsRequired + 1.0;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (v->TotalDSCUnitsRequired > v->NumberOfDSC) अणु
			v->NotEnoughDSCUnits[i] = true;
		पूर्ण
	पूर्ण
	/*DSC Delay per state*/

	क्रम (i = 0; i < v->soc.num_states; i++) अणु
		क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
			अगर (v->OutputBppPerState[i][k] == BPP_INVALID) अणु
				v->BPP = 0.0;
			पूर्ण अन्यथा अणु
				v->BPP = v->OutputBppPerState[i][k];
			पूर्ण
			अगर (v->RequiresDSC[i][k] == true && v->BPP != 0.0) अणु
				अगर (v->ODMCombineEnablePerState[i][k] == dm_odm_combine_mode_disabled) अणु
					v->DSCDelayPerState[i][k] = dscceComputeDelay(
							v->DSCInputBitPerComponent[k],
							v->BPP,
							dml_उच्चमान(1.0 * v->HActive[k] / v->NumberOfDSCSlices[k], 1.0),
							v->NumberOfDSCSlices[k],
							v->OutputFormat[k],
							v->Output[k]) + dscComputeDelay(v->OutputFormat[k], v->Output[k]);
				पूर्ण अन्यथा अगर (v->ODMCombineEnablePerState[i][k] == dm_odm_combine_mode_2to1) अणु
					v->DSCDelayPerState[i][k] = 2.0
							* dscceComputeDelay(
									v->DSCInputBitPerComponent[k],
									v->BPP,
									dml_उच्चमान(1.0 * v->HActive[k] / v->NumberOfDSCSlices[k], 1.0),
									v->NumberOfDSCSlices[k] / 2,
									v->OutputFormat[k],
									v->Output[k]) + dscComputeDelay(v->OutputFormat[k], v->Output[k]);
				पूर्ण अन्यथा अणु
					v->DSCDelayPerState[i][k] = 4.0
							* (dscceComputeDelay(
									v->DSCInputBitPerComponent[k],
									v->BPP,
									dml_उच्चमान(1.0 * v->HActive[k] / v->NumberOfDSCSlices[k], 1.0),
									v->NumberOfDSCSlices[k] / 4,
									v->OutputFormat[k],
									v->Output[k]) + dscComputeDelay(v->OutputFormat[k], v->Output[k]));
				पूर्ण
				v->DSCDelayPerState[i][k] = v->DSCDelayPerState[i][k] * v->PixelClock[k] / v->PixelClockBackEnd[k];
			पूर्ण अन्यथा अणु
				v->DSCDelayPerState[i][k] = 0.0;
			पूर्ण
		पूर्ण
		क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
			क्रम (m = 0; m <= v->NumberOfActivePlanes - 1; m++) अणु
				अगर (v->BlendingAndTiming[k] == m && v->RequiresDSC[i][m] == true) अणु
					v->DSCDelayPerState[i][k] = v->DSCDelayPerState[i][m];
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	//Calculate Swath, DET Configuration, DCFCLKDeepSleep
	//
	क्रम (i = 0; i < mode_lib->soc.num_states; ++i) अणु
		क्रम (j = 0; j <= 1; ++j) अणु
			क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
				v->RequiredDPPCLKThisState[k] = v->RequiredDPPCLK[i][j][k];
				v->NoOfDPPThisState[k] = v->NoOfDPP[i][j][k];
				v->ODMCombineEnableThisState[k] = v->ODMCombineEnablePerState[i][k];
			पूर्ण

			CalculateSwathAndDETConfiguration(
					false,
					v->NumberOfActivePlanes,
					v->DETBufferSizeInKByte,
					v->MaximumSwathWidthLuma,
					v->MaximumSwathWidthChroma,
					v->SourceScan,
					v->SourcePixelFormat,
					v->SurfaceTiling,
					v->ViewportWidth,
					v->ViewportHeight,
					v->SurfaceWidthY,
					v->SurfaceWidthC,
					v->SurfaceHeightY,
					v->SurfaceHeightC,
					v->Read256BlockHeightY,
					v->Read256BlockHeightC,
					v->Read256BlockWidthY,
					v->Read256BlockWidthC,
					v->ODMCombineEnableThisState,
					v->BlendingAndTiming,
					v->BytePerPixelY,
					v->BytePerPixelC,
					v->BytePerPixelInDETY,
					v->BytePerPixelInDETC,
					v->HActive,
					v->HRatio,
					v->HRatioChroma,
					v->NoOfDPPThisState,
					v->swath_width_luma_ub_this_state,
					v->swath_width_chroma_ub_this_state,
					v->SwathWidthYThisState,
					v->SwathWidthCThisState,
					v->SwathHeightYThisState,
					v->SwathHeightCThisState,
					v->DETBufferSizeYThisState,
					v->DETBufferSizeCThisState,
					v->dummystring,
					&v->ViewportSizeSupport[i][j]);

			क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
				v->swath_width_luma_ub_all_states[i][j][k] = v->swath_width_luma_ub_this_state[k];
				v->swath_width_chroma_ub_all_states[i][j][k] = v->swath_width_chroma_ub_this_state[k];
				v->SwathWidthYAllStates[i][j][k] = v->SwathWidthYThisState[k];
				v->SwathWidthCAllStates[i][j][k] = v->SwathWidthCThisState[k];
				v->SwathHeightYAllStates[i][j][k] = v->SwathHeightYThisState[k];
				v->SwathHeightCAllStates[i][j][k] = v->SwathHeightCThisState[k];
				v->DETBufferSizeYAllStates[i][j][k] = v->DETBufferSizeYThisState[k];
				v->DETBufferSizeCAllStates[i][j][k] = v->DETBufferSizeCThisState[k];
			पूर्ण

		पूर्ण
	पूर्ण
	क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
		v->cursor_bw[k] = v->NumberOfCursors[k] * v->CursorWidth[k][0] * v->CursorBPP[k][0] / 8.0 / (v->HTotal[k] / v->PixelClock[k]) * v->VRatio[k];
	पूर्ण

	क्रम (i = 0; i < v->soc.num_states; i++) अणु
		क्रम (j = 0; j < 2; j++) अणु
			क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
				v->swath_width_luma_ub_this_state[k] = v->swath_width_luma_ub_all_states[i][j][k];
				v->swath_width_chroma_ub_this_state[k] = v->swath_width_chroma_ub_all_states[i][j][k];
				v->SwathWidthYThisState[k] = v->SwathWidthYAllStates[i][j][k];
				v->SwathWidthCThisState[k] = v->SwathWidthCAllStates[i][j][k];
				v->SwathHeightYThisState[k] = v->SwathHeightYAllStates[i][j][k];
				v->SwathHeightCThisState[k] = v->SwathHeightCAllStates[i][j][k];
				v->DETBufferSizeYThisState[k] = v->DETBufferSizeYAllStates[i][j][k];
				v->DETBufferSizeCThisState[k] = v->DETBufferSizeCAllStates[i][j][k];
			पूर्ण

			v->TotalNumberOfDCCActiveDPP[i][j] = 0;
			क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
				अगर (v->DCCEnable[k] == true) अणु
					v->TotalNumberOfDCCActiveDPP[i][j] = v->TotalNumberOfDCCActiveDPP[i][j] + v->NoOfDPP[i][j][k];
				पूर्ण
			पूर्ण

			क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
				अगर (v->SourcePixelFormat[k] == dm_420_8 || v->SourcePixelFormat[k] == dm_420_10 || v->SourcePixelFormat[k] == dm_420_12
						|| v->SourcePixelFormat[k] == dm_rgbe_alpha) अणु

					अगर ((v->SourcePixelFormat[k] == dm_420_10 || v->SourcePixelFormat[k] == dm_420_12) && v->SourceScan[k] != dm_vert) अणु
						v->PTEBufferSizeInRequestsForLuma = (v->PTEBufferSizeInRequestsLuma + v->PTEBufferSizeInRequestsChroma) / 2;
						v->PTEBufferSizeInRequestsForChroma = v->PTEBufferSizeInRequestsForLuma;
					पूर्ण अन्यथा अणु
						v->PTEBufferSizeInRequestsForLuma = v->PTEBufferSizeInRequestsLuma;
						v->PTEBufferSizeInRequestsForChroma = v->PTEBufferSizeInRequestsChroma;
					पूर्ण

					v->PDEAndMetaPTEBytesPerFrameC = CalculateVMAndRowBytes(
							mode_lib,
							v->DCCEnable[k],
							v->Read256BlockHeightC[k],
							v->Read256BlockWidthY[k],
							v->SourcePixelFormat[k],
							v->SurfaceTiling[k],
							v->BytePerPixelC[k],
							v->SourceScan[k],
							v->SwathWidthCThisState[k],
							v->ViewportHeightChroma[k],
							v->GPUVMEnable,
							v->HostVMEnable,
							v->HostVMMaxNonCachedPageTableLevels,
							v->GPUVMMinPageSize,
							v->HostVMMinPageSize,
							v->PTEBufferSizeInRequestsForChroma,
							v->PitchC[k],
							0.0,
							&v->MacroTileWidthC[k],
							&v->MetaRowBytesC,
							&v->DPTEBytesPerRowC,
							&v->PTEBufferSizeNotExceededC[i][j][k],
							&v->dummyपूर्णांकeger7,
							&v->dpte_row_height_chroma[k],
							&v->dummyपूर्णांकeger28,
							&v->dummyपूर्णांकeger26,
							&v->dummyपूर्णांकeger23,
							&v->meta_row_height_chroma[k],
							&v->dummyपूर्णांकeger8,
							&v->dummyपूर्णांकeger9,
							&v->dummyपूर्णांकeger19,
							&v->dummyपूर्णांकeger20,
							&v->dummyपूर्णांकeger17,
							&v->dummyपूर्णांकeger10,
							&v->dummyपूर्णांकeger11);

					v->PrefetchLinesC[i][j][k] = CalculatePrefetchSourceLines(
							mode_lib,
							v->VRatioChroma[k],
							v->VTAPsChroma[k],
							v->Interlace[k],
							v->ProgressiveToInterlaceUnitInOPP,
							v->SwathHeightCThisState[k],
							v->ViewportYStartC[k],
							&v->PrefillC[k],
							&v->MaxNumSwC[k]);
				पूर्ण अन्यथा अणु
					v->PTEBufferSizeInRequestsForLuma = v->PTEBufferSizeInRequestsLuma + v->PTEBufferSizeInRequestsChroma;
					v->PTEBufferSizeInRequestsForChroma = 0;
					v->PDEAndMetaPTEBytesPerFrameC = 0.0;
					v->MetaRowBytesC = 0.0;
					v->DPTEBytesPerRowC = 0.0;
					v->PrefetchLinesC[i][j][k] = 0.0;
					v->PTEBufferSizeNotExceededC[i][j][k] = true;
				पूर्ण
				v->PDEAndMetaPTEBytesPerFrameY = CalculateVMAndRowBytes(
						mode_lib,
						v->DCCEnable[k],
						v->Read256BlockHeightY[k],
						v->Read256BlockWidthY[k],
						v->SourcePixelFormat[k],
						v->SurfaceTiling[k],
						v->BytePerPixelY[k],
						v->SourceScan[k],
						v->SwathWidthYThisState[k],
						v->ViewportHeight[k],
						v->GPUVMEnable,
						v->HostVMEnable,
						v->HostVMMaxNonCachedPageTableLevels,
						v->GPUVMMinPageSize,
						v->HostVMMinPageSize,
						v->PTEBufferSizeInRequestsForLuma,
						v->PitchY[k],
						v->DCCMetaPitchY[k],
						&v->MacroTileWidthY[k],
						&v->MetaRowBytesY,
						&v->DPTEBytesPerRowY,
						&v->PTEBufferSizeNotExceededY[i][j][k],
						v->dummyपूर्णांकeger4,
						&v->dpte_row_height[k],
						&v->dummyपूर्णांकeger29,
						&v->dummyपूर्णांकeger27,
						&v->dummyपूर्णांकeger24,
						&v->meta_row_height[k],
						&v->dummyपूर्णांकeger25,
						&v->dpte_group_bytes[k],
						&v->dummyपूर्णांकeger21,
						&v->dummyपूर्णांकeger22,
						&v->dummyपूर्णांकeger18,
						&v->dummyपूर्णांकeger5,
						&v->dummyपूर्णांकeger6);
				v->PrefetchLinesY[i][j][k] = CalculatePrefetchSourceLines(
						mode_lib,
						v->VRatio[k],
						v->vtaps[k],
						v->Interlace[k],
						v->ProgressiveToInterlaceUnitInOPP,
						v->SwathHeightYThisState[k],
						v->ViewportYStartY[k],
						&v->PrefillY[k],
						&v->MaxNumSwY[k]);
				v->PDEAndMetaPTEBytesPerFrame[i][j][k] = v->PDEAndMetaPTEBytesPerFrameY + v->PDEAndMetaPTEBytesPerFrameC;
				v->MetaRowBytes[i][j][k] = v->MetaRowBytesY + v->MetaRowBytesC;
				v->DPTEBytesPerRow[i][j][k] = v->DPTEBytesPerRowY + v->DPTEBytesPerRowC;

				CalculateRowBandwidth(
						v->GPUVMEnable,
						v->SourcePixelFormat[k],
						v->VRatio[k],
						v->VRatioChroma[k],
						v->DCCEnable[k],
						v->HTotal[k] / v->PixelClock[k],
						v->MetaRowBytesY,
						v->MetaRowBytesC,
						v->meta_row_height[k],
						v->meta_row_height_chroma[k],
						v->DPTEBytesPerRowY,
						v->DPTEBytesPerRowC,
						v->dpte_row_height[k],
						v->dpte_row_height_chroma[k],
						&v->meta_row_bandwidth[i][j][k],
						&v->dpte_row_bandwidth[i][j][k]);
			पूर्ण
			v->UrgLatency[i] = CalculateUrgentLatency(
					v->UrgentLatencyPixelDataOnly,
					v->UrgentLatencyPixelMixedWithVMData,
					v->UrgentLatencyVMDataOnly,
					v->DoUrgentLatencyAdjusपंचांगent,
					v->UrgentLatencyAdjusपंचांगentFabricClockComponent,
					v->UrgentLatencyAdjusपंचांगentFabricClockReference,
					v->FabricClockPerState[i]);

			क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
				CalculateUrgentBurstFactor(
						v->swath_width_luma_ub_this_state[k],
						v->swath_width_chroma_ub_this_state[k],
						v->DETBufferSizeInKByte,
						v->SwathHeightYThisState[k],
						v->SwathHeightCThisState[k],
						v->HTotal[k] / v->PixelClock[k],
						v->UrgLatency[i],
						v->CursorBufferSize,
						v->CursorWidth[k][0],
						v->CursorBPP[k][0],
						v->VRatio[k],
						v->VRatioChroma[k],
						v->BytePerPixelInDETY[k],
						v->BytePerPixelInDETC[k],
						v->DETBufferSizeYThisState[k],
						v->DETBufferSizeCThisState[k],
						&v->UrgentBurstFactorCursor[k],
						&v->UrgentBurstFactorLuma[k],
						&v->UrgentBurstFactorChroma[k],
						&NotUrgentLatencyHiding[k]);
			पूर्ण

			v->NotUrgentLatencyHiding[i][j] = false;
			क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
				अगर (NotUrgentLatencyHiding[k]) अणु
					v->NotUrgentLatencyHiding[i][j] = true;
				पूर्ण
			पूर्ण

			क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
				v->VActivePixelBandwidth[i][j][k] = v->ReadBandwidthLuma[k] * v->UrgentBurstFactorLuma[k]
						+ v->ReadBandwidthChroma[k] * v->UrgentBurstFactorChroma[k];
				v->VActiveCursorBandwidth[i][j][k] = v->cursor_bw[k] * v->UrgentBurstFactorCursor[k];
			पूर्ण

			v->TotalVActivePixelBandwidth[i][j] = 0;
			v->TotalVActiveCursorBandwidth[i][j] = 0;
			v->TotalMetaRowBandwidth[i][j] = 0;
			v->TotalDPTERowBandwidth[i][j] = 0;
			क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
				v->TotalVActivePixelBandwidth[i][j] = v->TotalVActivePixelBandwidth[i][j] + v->VActivePixelBandwidth[i][j][k];
				v->TotalVActiveCursorBandwidth[i][j] = v->TotalVActiveCursorBandwidth[i][j] + v->VActiveCursorBandwidth[i][j][k];
				v->TotalMetaRowBandwidth[i][j] = v->TotalMetaRowBandwidth[i][j] + v->NoOfDPP[i][j][k] * v->meta_row_bandwidth[i][j][k];
				v->TotalDPTERowBandwidth[i][j] = v->TotalDPTERowBandwidth[i][j] + v->NoOfDPP[i][j][k] * v->dpte_row_bandwidth[i][j][k];
			पूर्ण

			CalculateDCFCLKDeepSleep(
					mode_lib,
					v->NumberOfActivePlanes,
					v->BytePerPixelY,
					v->BytePerPixelC,
					v->VRatio,
					v->VRatioChroma,
					v->SwathWidthYThisState,
					v->SwathWidthCThisState,
					v->NoOfDPPThisState,
					v->HRatio,
					v->HRatioChroma,
					v->PixelClock,
					v->PSCL_FACTOR,
					v->PSCL_FACTOR_CHROMA,
					v->RequiredDPPCLKThisState,
					v->ReadBandwidthLuma,
					v->ReadBandwidthChroma,
					v->ReturnBusWidth,
					&v->ProjectedDCFCLKDeepSleep[i][j]);
		पूर्ण
	पूर्ण

	//Calculate Return BW

	क्रम (i = 0; i < mode_lib->soc.num_states; ++i) अणु
		क्रम (j = 0; j <= 1; ++j) अणु
			क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
				अगर (v->BlendingAndTiming[k] == k) अणु
					अगर (v->WritebackEnable[k] == true) अणु
						v->WritebackDelayTime[k] = v->WritebackLatency
								+ CalculateWriteBackDelay(
										v->WritebackPixelFormat[k],
										v->WritebackHRatio[k],
										v->WritebackVRatio[k],
										v->WritebackVTaps[k],
										v->WritebackDestinationWidth[k],
										v->WritebackDestinationHeight[k],
										v->WritebackSourceHeight[k],
										v->HTotal[k]) / v->RequiredDISPCLK[i][j];
					पूर्ण अन्यथा अणु
						v->WritebackDelayTime[k] = 0.0;
					पूर्ण
					क्रम (m = 0; m <= v->NumberOfActivePlanes - 1; m++) अणु
						अगर (v->BlendingAndTiming[m] == k && v->WritebackEnable[m] == true) अणु
							v->WritebackDelayTime[k] = dml_max(
									v->WritebackDelayTime[k],
									v->WritebackLatency
											+ CalculateWriteBackDelay(
													v->WritebackPixelFormat[m],
													v->WritebackHRatio[m],
													v->WritebackVRatio[m],
													v->WritebackVTaps[m],
													v->WritebackDestinationWidth[m],
													v->WritebackDestinationHeight[m],
													v->WritebackSourceHeight[m],
													v->HTotal[m]) / v->RequiredDISPCLK[i][j]);
						पूर्ण
					पूर्ण
				पूर्ण
			पूर्ण
			क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
				क्रम (m = 0; m <= v->NumberOfActivePlanes - 1; m++) अणु
					अगर (v->BlendingAndTiming[k] == m) अणु
						v->WritebackDelayTime[k] = v->WritebackDelayTime[m];
					पूर्ण
				पूर्ण
			पूर्ण
			v->MaxMaxVStartup[i][j] = 0;
			क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
				v->MaximumVStartup[i][j][k] = v->VTotal[k] - v->VActive[k]
						- dml_max(1.0, dml_उच्चमान(1.0 * v->WritebackDelayTime[k] / (v->HTotal[k] / v->PixelClock[k]), 1.0));
				v->MaxMaxVStartup[i][j] = dml_max(v->MaxMaxVStartup[i][j], v->MaximumVStartup[i][j][k]);
			पूर्ण
		पूर्ण
	पूर्ण

	ReorderingBytes = v->NumberOfChannels
			* dml_max3(
					v->UrgentOutOfOrderReturnPerChannelPixelDataOnly,
					v->UrgentOutOfOrderReturnPerChannelPixelMixedWithVMData,
					v->UrgentOutOfOrderReturnPerChannelVMDataOnly);
	v->FinalDRAMClockChangeLatency = (v->DRAMClockChangeLatencyOverride > 0 ? v->DRAMClockChangeLatencyOverride : v->DRAMClockChangeLatency);

	क्रम (i = 0; i < mode_lib->soc.num_states; ++i) अणु
		क्रम (j = 0; j <= 1; ++j) अणु
			v->DCFCLKState[i][j] = v->DCFCLKPerState[i];
		पूर्ण
	पूर्ण

	अगर (v->UseMinimumRequiredDCFCLK == true) अणु
		UseMinimumDCFCLK(
				mode_lib,
				v->MaxInterDCNTileRepeaters,
				MaxPrefetchMode,
				v->FinalDRAMClockChangeLatency,
				v->SREnterPlusExitTime,
				v->ReturnBusWidth,
				v->RoundTripPingLatencyCycles,
				ReorderingBytes,
				v->PixelChunkSizeInKByte,
				v->MetaChunkSize,
				v->GPUVMEnable,
				v->GPUVMMaxPageTableLevels,
				v->HostVMEnable,
				v->NumberOfActivePlanes,
				v->HostVMMinPageSize,
				v->HostVMMaxNonCachedPageTableLevels,
				v->DynamicMetadataVMEnabled,
				v->ImmediateFlipRequirement,
				v->ProgressiveToInterlaceUnitInOPP,
				v->MaxAveragePercentOfIdealSDPPortBWDisplayCanUseInNormalSystemOperation,
				v->PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData,
				v->PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly,
				v->PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelDataOnly,
				v->VTotal,
				v->VActive,
				v->DynamicMetadataTransmittedBytes,
				v->DynamicMetadataLinesBeक्रमeActiveRequired,
				v->Interlace,
				v->RequiredDPPCLK,
				v->RequiredDISPCLK,
				v->UrgLatency,
				v->NoOfDPP,
				v->ProjectedDCFCLKDeepSleep,
				v->MaximumVStartup,
				v->TotalVActivePixelBandwidth,
				v->TotalVActiveCursorBandwidth,
				v->TotalMetaRowBandwidth,
				v->TotalDPTERowBandwidth,
				v->TotalNumberOfActiveDPP,
				v->TotalNumberOfDCCActiveDPP,
				v->dpte_group_bytes,
				v->PrefetchLinesY,
				v->PrefetchLinesC,
				v->swath_width_luma_ub_all_states,
				v->swath_width_chroma_ub_all_states,
				v->BytePerPixelY,
				v->BytePerPixelC,
				v->HTotal,
				v->PixelClock,
				v->PDEAndMetaPTEBytesPerFrame,
				v->DPTEBytesPerRow,
				v->MetaRowBytes,
				v->DynamicMetadataEnable,
				v->VActivePixelBandwidth,
				v->VActiveCursorBandwidth,
				v->ReadBandwidthLuma,
				v->ReadBandwidthChroma,
				v->DCFCLKPerState,
				v->DCFCLKState);

		अगर (v->ClampMinDCFCLK) अणु
			/* Clamp calculated values to actual minimum */
			क्रम (i = 0; i < mode_lib->soc.num_states; ++i) अणु
				क्रम (j = 0; j <= 1; ++j) अणु
					अगर (v->DCFCLKState[i][j] < mode_lib->soc.min_dcfclk) अणु
						v->DCFCLKState[i][j] = mode_lib->soc.min_dcfclk;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < mode_lib->soc.num_states; ++i) अणु
		क्रम (j = 0; j <= 1; ++j) अणु
			v->IdealSDPPortBandwidthPerState[i][j] = dml_min3(
					v->ReturnBusWidth * v->DCFCLKState[i][j],
					v->DRAMSpeedPerState[i] * v->NumberOfChannels * v->DRAMChannelWidth,
					v->FabricClockPerState[i] * v->FabricDatapathToDCNDataReturn);
			अगर (v->HostVMEnable != true) अणु
				v->ReturnBWPerState[i][j] = v->IdealSDPPortBandwidthPerState[i][j] * v->PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelDataOnly
						/ 100;
			पूर्ण अन्यथा अणु
				v->ReturnBWPerState[i][j] = v->IdealSDPPortBandwidthPerState[i][j]
						* v->PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData / 100;
			पूर्ण
		पूर्ण
	पूर्ण

	//Re-ordering Buffer Support Check

	क्रम (i = 0; i < mode_lib->soc.num_states; ++i) अणु
		क्रम (j = 0; j <= 1; ++j) अणु
			अगर ((v->ROBBufferSizeInKByte - v->PixelChunkSizeInKByte) * 1024 / v->ReturnBWPerState[i][j]
					> (v->RoundTripPingLatencyCycles + 32) / v->DCFCLKState[i][j] + ReorderingBytes / v->ReturnBWPerState[i][j]) अणु
				v->ROBSupport[i][j] = true;
			पूर्ण अन्यथा अणु
				v->ROBSupport[i][j] = false;
			पूर्ण
		पूर्ण
	पूर्ण

	//Vertical Active BW support check

	MaxTotalVActiveRDBandwidth = 0;
	क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
		MaxTotalVActiveRDBandwidth = MaxTotalVActiveRDBandwidth + v->ReadBandwidthLuma[k] + v->ReadBandwidthChroma[k];
	पूर्ण

	क्रम (i = 0; i < mode_lib->soc.num_states; ++i) अणु
		क्रम (j = 0; j <= 1; ++j) अणु
			v->MaxTotalVerticalActiveAvailableBandwidth[i][j] = dml_min(
					v->IdealSDPPortBandwidthPerState[i][j] * v->MaxAveragePercentOfIdealSDPPortBWDisplayCanUseInNormalSystemOperation / 100,
					v->DRAMSpeedPerState[i] * v->NumberOfChannels * v->DRAMChannelWidth * v->MaxAveragePercentOfIdealDRAMBWDisplayCanUseInNormalSystemOperation
							/ 100);
			अगर (MaxTotalVActiveRDBandwidth <= v->MaxTotalVerticalActiveAvailableBandwidth[i][j]) अणु
				v->TotalVerticalActiveBandwidthSupport[i][j] = true;
			पूर्ण अन्यथा अणु
				v->TotalVerticalActiveBandwidthSupport[i][j] = false;
			पूर्ण
		पूर्ण
	पूर्ण

	//Prefetch Check

	क्रम (i = 0; i < mode_lib->soc.num_states; ++i) अणु
		क्रम (j = 0; j <= 1; ++j) अणु
			पूर्णांक NextPrefetchModeState = MinPrefetchMode;

			v->TimeCalc = 24 / v->ProjectedDCFCLKDeepSleep[i][j];

			v->BandwidthWithoutPrefetchSupported[i][j] = true;
			अगर (v->TotalVActivePixelBandwidth[i][j] + v->TotalVActiveCursorBandwidth[i][j] + v->TotalMetaRowBandwidth[i][j] + v->TotalDPTERowBandwidth[i][j]
					> v->ReturnBWPerState[i][j] || v->NotUrgentLatencyHiding[i][j]) अणु
				v->BandwidthWithoutPrefetchSupported[i][j] = false;
			पूर्ण

			क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
				v->NoOfDPPThisState[k] = v->NoOfDPP[i][j][k];
				v->swath_width_luma_ub_this_state[k] = v->swath_width_luma_ub_all_states[i][j][k];
				v->swath_width_chroma_ub_this_state[k] = v->swath_width_chroma_ub_all_states[i][j][k];
				v->SwathWidthYThisState[k] = v->SwathWidthYAllStates[i][j][k];
				v->SwathWidthCThisState[k] = v->SwathWidthCAllStates[i][j][k];
				v->SwathHeightYThisState[k] = v->SwathHeightYAllStates[i][j][k];
				v->SwathHeightCThisState[k] = v->SwathHeightCAllStates[i][j][k];
				v->DETBufferSizeYThisState[k] = v->DETBufferSizeYAllStates[i][j][k];
				v->DETBufferSizeCThisState[k] = v->DETBufferSizeCAllStates[i][j][k];
				v->ODMCombineEnabled[k] = v->ODMCombineEnablePerState[i][k];
			पूर्ण

			v->ExtraLatency = CalculateExtraLatency(
					v->RoundTripPingLatencyCycles,
					ReorderingBytes,
					v->DCFCLKState[i][j],
					v->TotalNumberOfActiveDPP[i][j],
					v->PixelChunkSizeInKByte,
					v->TotalNumberOfDCCActiveDPP[i][j],
					v->MetaChunkSize,
					v->ReturnBWPerState[i][j],
					v->GPUVMEnable,
					v->HostVMEnable,
					v->NumberOfActivePlanes,
					v->NoOfDPPThisState,
					v->dpte_group_bytes,
					v->PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData,
					v->PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly,
					v->HostVMMinPageSize,
					v->HostVMMaxNonCachedPageTableLevels);

			v->NextMaxVStartup = v->MaxMaxVStartup[i][j];
			करो अणु
				v->PrefetchModePerState[i][j] = NextPrefetchModeState;
				v->MaxVStartup = v->NextMaxVStartup;

				v->TWait = CalculateTWait(v->PrefetchModePerState[i][j], v->FinalDRAMClockChangeLatency, v->UrgLatency[i], v->SREnterPlusExitTime);

				क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
					Pipe myPipe = अणु 0 पूर्ण;

					myPipe.DPPCLK = v->RequiredDPPCLK[i][j][k];
					myPipe.DISPCLK = v->RequiredDISPCLK[i][j];
					myPipe.PixelClock = v->PixelClock[k];
					myPipe.DCFCLKDeepSleep = v->ProjectedDCFCLKDeepSleep[i][j];
					myPipe.DPPPerPlane = v->NoOfDPP[i][j][k];
					myPipe.ScalerEnabled = v->ScalerEnabled[k];
					myPipe.SourceScan = v->SourceScan[k];
					myPipe.BlockWidth256BytesY = v->Read256BlockWidthY[k];
					myPipe.BlockHeight256BytesY = v->Read256BlockHeightY[k];
					myPipe.BlockWidth256BytesC = v->Read256BlockWidthC[k];
					myPipe.BlockHeight256BytesC = v->Read256BlockHeightC[k];
					myPipe.InterlaceEnable = v->Interlace[k];
					myPipe.NumberOfCursors = v->NumberOfCursors[k];
					myPipe.VBlank = v->VTotal[k] - v->VActive[k];
					myPipe.HTotal = v->HTotal[k];
					myPipe.DCCEnable = v->DCCEnable[k];
					myPipe.ODMCombineEnabled = !!v->ODMCombineEnabled[k];

					v->NoTimeForPrefetch[i][j][k] = CalculatePrefetchSchedule(
							mode_lib,
							v->PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData,
							v->PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly,
							&myPipe,
							v->DSCDelayPerState[i][k],
							v->DPPCLKDelaySubtotal + v->DPPCLKDelayCNVCFormater,
							v->DPPCLKDelaySCL,
							v->DPPCLKDelaySCLLBOnly,
							v->DPPCLKDelayCNVCCursor,
							v->DISPCLKDelaySubtotal,
							v->SwathWidthYThisState[k] / v->HRatio[k],
							v->OutputFormat[k],
							v->MaxInterDCNTileRepeaters,
							dml_min(v->MaxVStartup, v->MaximumVStartup[i][j][k]),
							v->MaximumVStartup[i][j][k],
							v->GPUVMMaxPageTableLevels,
							v->GPUVMEnable,
							v->HostVMEnable,
							v->HostVMMaxNonCachedPageTableLevels,
							v->HostVMMinPageSize,
							v->DynamicMetadataEnable[k],
							v->DynamicMetadataVMEnabled,
							v->DynamicMetadataLinesBeक्रमeActiveRequired[k],
							v->DynamicMetadataTransmittedBytes[k],
							v->UrgLatency[i],
							v->ExtraLatency,
							v->TimeCalc,
							v->PDEAndMetaPTEBytesPerFrame[i][j][k],
							v->MetaRowBytes[i][j][k],
							v->DPTEBytesPerRow[i][j][k],
							v->PrefetchLinesY[i][j][k],
							v->SwathWidthYThisState[k],
							v->BytePerPixelY[k],
							v->PrefillY[k],
							v->MaxNumSwY[k],
							v->PrefetchLinesC[i][j][k],
							v->SwathWidthCThisState[k],
							v->BytePerPixelC[k],
							v->PrefillC[k],
							v->MaxNumSwC[k],
							v->swath_width_luma_ub_this_state[k],
							v->swath_width_chroma_ub_this_state[k],
							v->SwathHeightYThisState[k],
							v->SwathHeightCThisState[k],
							v->TWait,
							v->ProgressiveToInterlaceUnitInOPP,
							&v->DSTXAfterScaler[k],
							&v->DSTYAfterScaler[k],
							&v->LineTimesForPrefetch[k],
							&v->PrefetchBW[k],
							&v->LinesForMetaPTE[k],
							&v->LinesForMetaAndDPTERow[k],
							&v->VRatioPreY[i][j][k],
							&v->VRatioPreC[i][j][k],
							&v->RequiredPrefetchPixelDataBWLuma[i][j][k],
							&v->RequiredPrefetchPixelDataBWChroma[i][j][k],
							&v->NoTimeForDynamicMetadata[i][j][k],
							&v->Tno_bw[k],
							&v->prefetch_vmrow_bw[k],
							&v->Tdmdl_vm[k],
							&v->Tdmdl[k],
							&v->VUpdateOffsetPix[k],
							&v->VUpdateWidthPix[k],
							&v->VReadyOffsetPix[k]);
				पूर्ण

				क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
					CalculateUrgentBurstFactor(
							v->swath_width_luma_ub_this_state[k],
							v->swath_width_chroma_ub_this_state[k],
							v->DETBufferSizeInKByte,
							v->SwathHeightYThisState[k],
							v->SwathHeightCThisState[k],
							v->HTotal[k] / v->PixelClock[k],
							v->UrgentLatency,
							v->CursorBufferSize,
							v->CursorWidth[k][0],
							v->CursorBPP[k][0],
							v->VRatioPreY[i][j][k],
							v->VRatioPreC[i][j][k],
							v->BytePerPixelInDETY[k],
							v->BytePerPixelInDETC[k],
							v->DETBufferSizeYThisState[k],
							v->DETBufferSizeCThisState[k],
							&v->UrgentBurstFactorCursorPre[k],
							&v->UrgentBurstFactorLumaPre[k],
							&v->UrgentBurstFactorChroma[k],
							&v->NoUrgentLatencyHidingPre[k]);
				पूर्ण

				v->MaximumReadBandwidthWithPrefetch = 0.0;
				क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
					v->cursor_bw_pre[k] = v->NumberOfCursors[k] * v->CursorWidth[k][0] * v->CursorBPP[k][0] / 8.0 / (v->HTotal[k] / v->PixelClock[k])
							* v->VRatioPreY[i][j][k];

					v->MaximumReadBandwidthWithPrefetch = v->MaximumReadBandwidthWithPrefetch
							+ dml_max4(
									v->VActivePixelBandwidth[i][j][k],
									v->VActiveCursorBandwidth[i][j][k]
											+ v->NoOfDPP[i][j][k] * (v->meta_row_bandwidth[i][j][k] + v->dpte_row_bandwidth[i][j][k]),
									v->NoOfDPP[i][j][k] * v->prefetch_vmrow_bw[k],
									v->NoOfDPP[i][j][k]
											* (v->RequiredPrefetchPixelDataBWLuma[i][j][k] * v->UrgentBurstFactorLumaPre[k]
													+ v->RequiredPrefetchPixelDataBWChroma[i][j][k]
															* v->UrgentBurstFactorChromaPre[k])
											+ v->cursor_bw_pre[k] * v->UrgentBurstFactorCursorPre[k]);
				पूर्ण

				v->NotEnoughUrgentLatencyHidingPre = false;
				क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
					अगर (v->NoUrgentLatencyHidingPre[k] == true) अणु
						v->NotEnoughUrgentLatencyHidingPre = true;
					पूर्ण
				पूर्ण

				v->PrefetchSupported[i][j] = true;
				अगर (v->BandwidthWithoutPrefetchSupported[i][j] == false || v->MaximumReadBandwidthWithPrefetch > v->ReturnBWPerState[i][j]
						|| v->NotEnoughUrgentLatencyHidingPre == 1) अणु
					v->PrefetchSupported[i][j] = false;
				पूर्ण
				क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
					अगर (v->LineTimesForPrefetch[k] < 2.0 || v->LinesForMetaPTE[k] >= 32.0 || v->LinesForMetaAndDPTERow[k] >= 16.0
							|| v->NoTimeForPrefetch[i][j][k] == true) अणु
						v->PrefetchSupported[i][j] = false;
					पूर्ण
				पूर्ण

				v->DynamicMetadataSupported[i][j] = true;
				क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
					अगर (v->NoTimeForDynamicMetadata[i][j][k] == true) अणु
						v->DynamicMetadataSupported[i][j] = false;
					पूर्ण
				पूर्ण

				v->VRatioInPrefetchSupported[i][j] = true;
				क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
					अगर (v->VRatioPreY[i][j][k] > 4.0 || v->VRatioPreC[i][j][k] > 4.0 || v->NoTimeForPrefetch[i][j][k] == true) अणु
						v->VRatioInPrefetchSupported[i][j] = false;
					पूर्ण
				पूर्ण
				v->AnyLinesForVMOrRowTooLarge = false;
				क्रम (k = 0; k < v->NumberOfActivePlanes; ++k) अणु
					अगर (v->LinesForMetaAndDPTERow[k] >= 16 || v->LinesForMetaPTE[k] >= 32) अणु
						v->AnyLinesForVMOrRowTooLarge = true;
					पूर्ण
				पूर्ण

				अगर (v->PrefetchSupported[i][j] == true && v->VRatioInPrefetchSupported[i][j] == true) अणु
					v->BandwidthAvailableForImmediateFlip = v->ReturnBWPerState[i][j];
					क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
						v->BandwidthAvailableForImmediateFlip = v->BandwidthAvailableForImmediateFlip
								- dml_max(
										v->VActivePixelBandwidth[i][j][k] + v->VActiveCursorBandwidth[i][j][k],
										v->NoOfDPP[i][j][k]
												* (v->RequiredPrefetchPixelDataBWLuma[i][j][k] * v->UrgentBurstFactorLumaPre[k]
														+ v->RequiredPrefetchPixelDataBWChroma[i][j][k]
																* v->UrgentBurstFactorChromaPre[k])
												+ v->cursor_bw_pre[k] * v->UrgentBurstFactorCursorPre[k]);
					पूर्ण
					v->TotImmediateFlipBytes = 0.0;
					क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
						v->TotImmediateFlipBytes = v->TotImmediateFlipBytes + v->NoOfDPP[i][j][k] * v->PDEAndMetaPTEBytesPerFrame[i][j][k]
								+ v->MetaRowBytes[i][j][k] + v->DPTEBytesPerRow[i][j][k];
					पूर्ण

					क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
						CalculateFlipSchedule(
								mode_lib,
								v->PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData,
								v->PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly,
								v->ExtraLatency,
								v->UrgLatency[i],
								v->GPUVMMaxPageTableLevels,
								v->HostVMEnable,
								v->HostVMMaxNonCachedPageTableLevels,
								v->GPUVMEnable,
								v->HostVMMinPageSize,
								v->PDEAndMetaPTEBytesPerFrame[i][j][k],
								v->MetaRowBytes[i][j][k],
								v->DPTEBytesPerRow[i][j][k],
								v->BandwidthAvailableForImmediateFlip,
								v->TotImmediateFlipBytes,
								v->SourcePixelFormat[k],
								v->HTotal[k] / v->PixelClock[k],
								v->VRatio[k],
								v->VRatioChroma[k],
								v->Tno_bw[k],
								v->DCCEnable[k],
								v->dpte_row_height[k],
								v->meta_row_height[k],
								v->dpte_row_height_chroma[k],
								v->meta_row_height_chroma[k],
								&v->DestinationLinesToRequestVMInImmediateFlip[k],
								&v->DestinationLinesToRequestRowInImmediateFlip[k],
								&v->final_flip_bw[k],
								&v->ImmediateFlipSupportedForPipe[k]);
					पूर्ण
					v->total_dcn_पढ़ो_bw_with_flip = 0.0;
					क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
						v->total_dcn_पढ़ो_bw_with_flip = v->total_dcn_पढ़ो_bw_with_flip
								+ dml_max3(
										v->NoOfDPP[i][j][k] * v->prefetch_vmrow_bw[k],
										v->NoOfDPP[i][j][k] * v->final_flip_bw[k] + v->VActivePixelBandwidth[i][j][k]
												+ v->VActiveCursorBandwidth[i][j][k],
										v->NoOfDPP[i][j][k]
												* (v->final_flip_bw[k]
														+ v->RequiredPrefetchPixelDataBWLuma[i][j][k]
																* v->UrgentBurstFactorLumaPre[k]
														+ v->RequiredPrefetchPixelDataBWChroma[i][j][k]
																* v->UrgentBurstFactorChromaPre[k])
												+ v->cursor_bw_pre[k] * v->UrgentBurstFactorCursorPre[k]);
					पूर्ण
					v->ImmediateFlipSupportedForState[i][j] = true;
					अगर (v->total_dcn_पढ़ो_bw_with_flip > v->ReturnBWPerState[i][j]) अणु
						v->ImmediateFlipSupportedForState[i][j] = false;
					पूर्ण
					क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
						अगर (v->ImmediateFlipSupportedForPipe[k] == false) अणु
							v->ImmediateFlipSupportedForState[i][j] = false;
						पूर्ण
					पूर्ण
				पूर्ण अन्यथा अणु
					v->ImmediateFlipSupportedForState[i][j] = false;
				पूर्ण
				अगर (v->MaxVStartup <= 13 || v->AnyLinesForVMOrRowTooLarge == false) अणु
					v->NextMaxVStartup = v->MaxMaxVStartup[i][j];
					NextPrefetchModeState = NextPrefetchModeState + 1;
				पूर्ण अन्यथा अणु
					v->NextMaxVStartup = v->NextMaxVStartup - 1;
				पूर्ण
			पूर्ण जबतक (!((v->PrefetchSupported[i][j] == true && v->DynamicMetadataSupported[i][j] == true && v->VRatioInPrefetchSupported[i][j] == true
					&& ((v->HostVMEnable == false && v->ImmediateFlipRequirement != dm_immediate_flip_required)
							|| v->ImmediateFlipSupportedForState[i][j] == true))
					|| (v->NextMaxVStartup == v->MaxMaxVStartup[i][j] && NextPrefetchModeState > MaxPrefetchMode)));

			CalculateWatermarksAndDRAMSpeedChangeSupport(
					mode_lib,
					v->PrefetchModePerState[i][j],
					v->NumberOfActivePlanes,
					v->MaxLineBufferLines,
					v->LineBufferSize,
					v->DPPOutputBufferPixels,
					v->DETBufferSizeInKByte,
					v->WritebackInterfaceBufferSize,
					v->DCFCLKState[i][j],
					v->ReturnBWPerState[i][j],
					v->GPUVMEnable,
					v->dpte_group_bytes,
					v->MetaChunkSize,
					v->UrgLatency[i],
					v->ExtraLatency,
					v->WritebackLatency,
					v->WritebackChunkSize,
					v->SOCCLKPerState[i],
					v->FinalDRAMClockChangeLatency,
					v->SRExitTime,
					v->SREnterPlusExitTime,
					v->ProjectedDCFCLKDeepSleep[i][j],
					v->NoOfDPPThisState,
					v->DCCEnable,
					v->RequiredDPPCLKThisState,
					v->DETBufferSizeYThisState,
					v->DETBufferSizeCThisState,
					v->SwathHeightYThisState,
					v->SwathHeightCThisState,
					v->LBBitPerPixel,
					v->SwathWidthYThisState,
					v->SwathWidthCThisState,
					v->HRatio,
					v->HRatioChroma,
					v->vtaps,
					v->VTAPsChroma,
					v->VRatio,
					v->VRatioChroma,
					v->HTotal,
					v->PixelClock,
					v->BlendingAndTiming,
					v->BytePerPixelInDETY,
					v->BytePerPixelInDETC,
					v->DSTXAfterScaler,
					v->DSTYAfterScaler,
					v->WritebackEnable,
					v->WritebackPixelFormat,
					v->WritebackDestinationWidth,
					v->WritebackDestinationHeight,
					v->WritebackSourceHeight,
					&v->DRAMClockChangeSupport[i][j],
					&v->UrgentWatermark,
					&v->WritebackUrgentWatermark,
					&v->DRAMClockChangeWatermark,
					&v->WritebackDRAMClockChangeWatermark,
					&v->StutterExitWatermark,
					&v->StutterEnterPlusExitWatermark,
					&v->MinActiveDRAMClockChangeLatencySupported);
		पूर्ण
	पूर्ण

	/*PTE Buffer Size Check*/

	क्रम (i = 0; i < v->soc.num_states; i++) अणु
		क्रम (j = 0; j < 2; j++) अणु
			v->PTEBufferSizeNotExceeded[i][j] = true;
			क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
				अगर (v->PTEBufferSizeNotExceededY[i][j][k] == false || v->PTEBufferSizeNotExceededC[i][j][k] == false) अणु
					v->PTEBufferSizeNotExceeded[i][j] = false;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	/*Cursor Support Check*/

	v->CursorSupport = true;
	क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
		अगर (v->CursorWidth[k][0] > 0.0) अणु
			अगर (v->CursorBPP[k][0] == 64 && v->Cursor64BppSupport == false) अणु
				v->CursorSupport = false;
			पूर्ण
		पूर्ण
	पूर्ण
	/*Valid Pitch Check*/

	v->PitchSupport = true;
	क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
		v->AlignedYPitch[k] = dml_उच्चमान(dml_max(v->PitchY[k], v->SurfaceWidthY[k]), v->MacroTileWidthY[k]);
		अगर (v->DCCEnable[k] == true) अणु
			v->AlignedDCCMetaPitchY[k] = dml_उच्चमान(dml_max(v->DCCMetaPitchY[k], v->SurfaceWidthY[k]), 64.0 * v->Read256BlockWidthY[k]);
		पूर्ण अन्यथा अणु
			v->AlignedDCCMetaPitchY[k] = v->DCCMetaPitchY[k];
		पूर्ण
		अगर (v->SourcePixelFormat[k] != dm_444_64 && v->SourcePixelFormat[k] != dm_444_32 && v->SourcePixelFormat[k] != dm_444_16 && v->SourcePixelFormat[k] != dm_mono_16
				&& v->SourcePixelFormat[k] != dm_rgbe && v->SourcePixelFormat[k] != dm_mono_8) अणु
			v->AlignedCPitch[k] = dml_उच्चमान(dml_max(v->PitchC[k], v->SurfaceWidthC[k]), v->MacroTileWidthC[k]);
			अगर (v->DCCEnable[k] == true) अणु
				v->AlignedDCCMetaPitchC[k] = dml_उच्चमान(dml_max(v->DCCMetaPitchC[k], v->SurfaceWidthC[k]), 64.0 * v->Read256BlockWidthC[k]);
			पूर्ण अन्यथा अणु
				v->AlignedDCCMetaPitchC[k] = v->DCCMetaPitchC[k];
			पूर्ण
		पूर्ण अन्यथा अणु
			v->AlignedCPitch[k] = v->PitchC[k];
			v->AlignedDCCMetaPitchC[k] = v->DCCMetaPitchC[k];
		पूर्ण
		अगर (v->AlignedYPitch[k] > v->PitchY[k] || v->AlignedCPitch[k] > v->PitchC[k] || v->AlignedDCCMetaPitchY[k] > v->DCCMetaPitchY[k]
				|| v->AlignedDCCMetaPitchC[k] > v->DCCMetaPitchC[k]) अणु
			v->PitchSupport = false;
		पूर्ण
	पूर्ण

	क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
		अगर (v->ViewportWidth[k] > v->SurfaceWidthY[k] || v->ViewportHeight[k] > v->SurfaceHeightY[k])
			ViewportExceedsSurface = true;

		अगर (v->SourcePixelFormat[k] != dm_444_64 && v->SourcePixelFormat[k] != dm_444_32 && v->SourcePixelFormat[k] != dm_444_16
				&& v->SourcePixelFormat[k] != dm_444_8 && v->SourcePixelFormat[k] != dm_rgbe) अणु
			अगर (v->ViewportWidthChroma[k] > v->SurfaceWidthC[k] || v->ViewportHeightChroma[k] > v->SurfaceHeightC[k]) अणु
				ViewportExceedsSurface = true;
			पूर्ण
		पूर्ण
	पूर्ण
	/*Mode Support, Voltage State and SOC Configuration*/

	क्रम (i = v->soc.num_states - 1; i >= 0; i--) अणु
		क्रम (j = 0; j < 2; j++) अणु
			अगर (v->ScaleRatioAndTapsSupport == 1 && v->SourceFormatPixelAndScanSupport == 1 && v->ViewportSizeSupport[i][j] == 1
					&& v->DIOSupport[i] == 1 && v->ODMCombine4To1SupportCheckOK[i] == 1
					&& v->NotEnoughDSCUnits[i] == 0 && v->DSCCLKRequiredMoreThanSupported[i] == 0
					&& v->DTBCLKRequiredMoreThanSupported[i] == 0
					&& v->ROBSupport[i][j] == 1 && v->DISPCLK_DPPCLK_Support[i][j] == 1 && v->TotalAvailablePipesSupport[i][j] == 1
					&& EnoughWritebackUnits == 1 && WritebackModeSupport == 1
					&& v->WritebackLatencySupport == 1 && v->WritebackScaleRatioAndTapsSupport == 1 && v->CursorSupport == 1 && v->PitchSupport == 1
					&& ViewportExceedsSurface == 0 && v->PrefetchSupported[i][j] == 1 && v->DynamicMetadataSupported[i][j] == 1
					&& v->TotalVerticalActiveBandwidthSupport[i][j] == 1 && v->VRatioInPrefetchSupported[i][j] == 1
					&& v->PTEBufferSizeNotExceeded[i][j] == 1 && v->NonsupportedDSCInputBPC == 0
					&& ((v->HostVMEnable == 0 && v->ImmediateFlipRequirement != dm_immediate_flip_required)
							|| v->ImmediateFlipSupportedForState[i][j] == true)) अणु
				v->ModeSupport[i][j] = true;
			पूर्ण अन्यथा अणु
				v->ModeSupport[i][j] = false;
			पूर्ण
		पूर्ण
	पूर्ण
	अणु
		अचिन्हित पूर्णांक MaximumMPCCombine = 0;
		क्रम (i = v->soc.num_states; i >= 0; i--) अणु
			अगर (i == v->soc.num_states || v->ModeSupport[i][0] == true || v->ModeSupport[i][1] == true) अणु
				v->VoltageLevel = i;
				v->ModeIsSupported = v->ModeSupport[i][0] == true || v->ModeSupport[i][1] == true;
				अगर (v->ModeSupport[i][1] == true) अणु
					MaximumMPCCombine = 1;
				पूर्ण अन्यथा अणु
					MaximumMPCCombine = 0;
				पूर्ण
			पूर्ण
		पूर्ण
		v->ImmediateFlipSupport = v->ImmediateFlipSupportedForState[v->VoltageLevel][MaximumMPCCombine];
		क्रम (k = 0; k <= v->NumberOfActivePlanes - 1; k++) अणु
			v->MPCCombineEnable[k] = v->MPCCombine[v->VoltageLevel][MaximumMPCCombine][k];
			v->DPPPerPlane[k] = v->NoOfDPP[v->VoltageLevel][MaximumMPCCombine][k];
		पूर्ण
		v->DCFCLK = v->DCFCLKState[v->VoltageLevel][MaximumMPCCombine];
		v->DRAMSpeed = v->DRAMSpeedPerState[v->VoltageLevel];
		v->FabricClock = v->FabricClockPerState[v->VoltageLevel];
		v->SOCCLK = v->SOCCLKPerState[v->VoltageLevel];
		v->ReturnBW = v->ReturnBWPerState[v->VoltageLevel][MaximumMPCCombine];
		v->maxMpcComb = MaximumMPCCombine;
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
		अचिन्हित पूर्णांक WritebackInterfaceBufferSize,
		द्विगुन DCFCLK,
		द्विगुन ReturnBW,
		bool GPUVMEnable,
		अचिन्हित पूर्णांक dpte_group_bytes[],
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
		अचिन्हित पूर्णांक DPPPerPlane[],
		bool DCCEnable[],
		द्विगुन DPPCLK[],
		द्विगुन DETBufferSizeY[],
		द्विगुन DETBufferSizeC[],
		अचिन्हित पूर्णांक SwathHeightY[],
		अचिन्हित पूर्णांक SwathHeightC[],
		अचिन्हित पूर्णांक LBBitPerPixel[],
		द्विगुन SwathWidthY[],
		द्विगुन SwathWidthC[],
		द्विगुन HRatio[],
		द्विगुन HRatioChroma[],
		अचिन्हित पूर्णांक vtaps[],
		अचिन्हित पूर्णांक VTAPsChroma[],
		द्विगुन VRatio[],
		द्विगुन VRatioChroma[],
		अचिन्हित पूर्णांक HTotal[],
		द्विगुन PixelClock[],
		अचिन्हित पूर्णांक BlendingAndTiming[],
		द्विगुन BytePerPixelDETY[],
		द्विगुन BytePerPixelDETC[],
		द्विगुन DSTXAfterScaler[],
		द्विगुन DSTYAfterScaler[],
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
	द्विगुन EffectiveLBLatencyHidingY = 0;
	द्विगुन EffectiveLBLatencyHidingC = 0;
	द्विगुन LinesInDETY[DC__NUM_DPP__MAX] = अणु 0 पूर्ण;
	द्विगुन LinesInDETC = 0;
	अचिन्हित पूर्णांक LinesInDETYRoundedDownToSwath[DC__NUM_DPP__MAX] = अणु 0 पूर्ण;
	अचिन्हित पूर्णांक LinesInDETCRoundedDownToSwath = 0;
	द्विगुन FullDETBufferingTimeY[DC__NUM_DPP__MAX] = अणु 0 पूर्ण;
	द्विगुन FullDETBufferingTimeC = 0;
	द्विगुन ActiveDRAMClockChangeLatencyMarginY = 0;
	द्विगुन ActiveDRAMClockChangeLatencyMarginC = 0;
	द्विगुन WritebackDRAMClockChangeLatencyMargin = 0;
	द्विगुन PlaneWithMinActiveDRAMClockChangeMargin = 0;
	द्विगुन SecondMinActiveDRAMClockChangeMarginOneDisplayInVBLank = 0;
	द्विगुन FullDETBufferingTimeYStutterCriticalPlane = 0;
	द्विगुन TimeToFinishSwathTransferStutterCriticalPlane = 0;
	द्विगुन WritebackDRAMClockChangeLatencyHiding = 0;
	अचिन्हित पूर्णांक k, j;

	mode_lib->vba.TotalActiveDPP = 0;
	mode_lib->vba.TotalDCCActiveDPP = 0;
	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		mode_lib->vba.TotalActiveDPP = mode_lib->vba.TotalActiveDPP + DPPPerPlane[k];
		अगर (DCCEnable[k] == true) अणु
			mode_lib->vba.TotalDCCActiveDPP = mode_lib->vba.TotalDCCActiveDPP + DPPPerPlane[k];
		पूर्ण
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
		*WritebackUrgentWatermark = WritebackLatency + WritebackChunkSize * 1024.0 / 32.0 / SOCCLK;
	पूर्ण

	अगर (mode_lib->vba.TotalActiveWriteback <= 1) अणु
		*WritebackDRAMClockChangeWatermark = DRAMClockChangeLatency + WritebackLatency;
	पूर्ण अन्यथा अणु
		*WritebackDRAMClockChangeWatermark = DRAMClockChangeLatency + WritebackLatency + WritebackChunkSize * 1024.0 / 32.0 / SOCCLK;
	पूर्ण

	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु

		mode_lib->vba.LBLatencyHidingSourceLinesY = dml_min((द्विगुन) MaxLineBufferLines, dml_न्यूनमान(LineBufferSize / LBBitPerPixel[k] / (SwathWidthY[k] / dml_max(HRatio[k], 1.0)), 1)) - (vtaps[k] - 1);

		mode_lib->vba.LBLatencyHidingSourceLinesC = dml_min((द्विगुन) MaxLineBufferLines, dml_न्यूनमान(LineBufferSize / LBBitPerPixel[k] / (SwathWidthC[k] / dml_max(HRatioChroma[k], 1.0)), 1)) - (VTAPsChroma[k] - 1);

		EffectiveLBLatencyHidingY = mode_lib->vba.LBLatencyHidingSourceLinesY / VRatio[k] * (HTotal[k] / PixelClock[k]);

		EffectiveLBLatencyHidingC = mode_lib->vba.LBLatencyHidingSourceLinesC / VRatioChroma[k] * (HTotal[k] / PixelClock[k]);

		LinesInDETY[k] = (द्विगुन) DETBufferSizeY[k] / BytePerPixelDETY[k] / SwathWidthY[k];
		LinesInDETYRoundedDownToSwath[k] = dml_न्यूनमान(LinesInDETY[k], SwathHeightY[k]);
		FullDETBufferingTimeY[k] = LinesInDETYRoundedDownToSwath[k] * (HTotal[k] / PixelClock[k]) / VRatio[k];
		अगर (BytePerPixelDETC[k] > 0) अणु
			LinesInDETC = mode_lib->vba.DETBufferSizeC[k] / BytePerPixelDETC[k] / SwathWidthC[k];
			LinesInDETCRoundedDownToSwath = dml_न्यूनमान(LinesInDETC, SwathHeightC[k]);
			FullDETBufferingTimeC = LinesInDETCRoundedDownToSwath * (HTotal[k] / PixelClock[k]) / VRatioChroma[k];
		पूर्ण अन्यथा अणु
			LinesInDETC = 0;
			FullDETBufferingTimeC = 999999;
		पूर्ण

		ActiveDRAMClockChangeLatencyMarginY = EffectiveLBLatencyHidingY + FullDETBufferingTimeY[k] - *UrgentWatermark - (HTotal[k] / PixelClock[k]) * (DSTXAfterScaler[k] / HTotal[k] + DSTYAfterScaler[k]) - *DRAMClockChangeWatermark;

		अगर (NumberOfActivePlanes > 1) अणु
			ActiveDRAMClockChangeLatencyMarginY = ActiveDRAMClockChangeLatencyMarginY - (1 - 1.0 / NumberOfActivePlanes) * SwathHeightY[k] * HTotal[k] / PixelClock[k] / VRatio[k];
		पूर्ण

		अगर (BytePerPixelDETC[k] > 0) अणु
			ActiveDRAMClockChangeLatencyMarginC = EffectiveLBLatencyHidingC + FullDETBufferingTimeC - *UrgentWatermark - (HTotal[k] / PixelClock[k]) * (DSTXAfterScaler[k] / HTotal[k] + DSTYAfterScaler[k]) - *DRAMClockChangeWatermark;

			अगर (NumberOfActivePlanes > 1) अणु
				ActiveDRAMClockChangeLatencyMarginC = ActiveDRAMClockChangeLatencyMarginC - (1 - 1.0 / NumberOfActivePlanes) * SwathHeightC[k] * HTotal[k] / PixelClock[k] / VRatioChroma[k];
			पूर्ण
			mode_lib->vba.ActiveDRAMClockChangeLatencyMargin[k] = dml_min(ActiveDRAMClockChangeLatencyMarginY, ActiveDRAMClockChangeLatencyMarginC);
		पूर्ण अन्यथा अणु
			mode_lib->vba.ActiveDRAMClockChangeLatencyMargin[k] = ActiveDRAMClockChangeLatencyMarginY;
		पूर्ण

		अगर (WritebackEnable[k] == true) अणु

			WritebackDRAMClockChangeLatencyHiding = WritebackInterfaceBufferSize * 1024 / (WritebackDestinationWidth[k] * WritebackDestinationHeight[k] / (WritebackSourceHeight[k] * HTotal[k] / PixelClock[k]) * 4);
			अगर (WritebackPixelFormat[k] == dm_444_64) अणु
				WritebackDRAMClockChangeLatencyHiding = WritebackDRAMClockChangeLatencyHiding / 2;
			पूर्ण
			अगर (mode_lib->vba.WritebackConfiguration == dm_whole_buffer_क्रम_single_stream_पूर्णांकerleave) अणु
				WritebackDRAMClockChangeLatencyHiding = WritebackDRAMClockChangeLatencyHiding * 2;
			पूर्ण
			WritebackDRAMClockChangeLatencyMargin = WritebackDRAMClockChangeLatencyHiding - mode_lib->vba.WritebackDRAMClockChangeWatermark;
			mode_lib->vba.ActiveDRAMClockChangeLatencyMargin[k] = dml_min(mode_lib->vba.ActiveDRAMClockChangeLatencyMargin[k], WritebackDRAMClockChangeLatencyMargin);
		पूर्ण
	पूर्ण

	mode_lib->vba.MinActiveDRAMClockChangeMargin = 999999;
	PlaneWithMinActiveDRAMClockChangeMargin = 0;
	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		अगर (mode_lib->vba.ActiveDRAMClockChangeLatencyMargin[k] < mode_lib->vba.MinActiveDRAMClockChangeMargin) अणु
			mode_lib->vba.MinActiveDRAMClockChangeMargin = mode_lib->vba.ActiveDRAMClockChangeLatencyMargin[k];
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
		अगर (!((k == PlaneWithMinActiveDRAMClockChangeMargin) && (BlendingAndTiming[k] == k)) && !(BlendingAndTiming[k] == PlaneWithMinActiveDRAMClockChangeMargin) && mode_lib->vba.ActiveDRAMClockChangeLatencyMargin[k] < SecondMinActiveDRAMClockChangeMarginOneDisplayInVBLank) अणु
			SecondMinActiveDRAMClockChangeMarginOneDisplayInVBLank = mode_lib->vba.ActiveDRAMClockChangeLatencyMargin[k];
		पूर्ण
	पूर्ण

	mode_lib->vba.TotalNumberOfActiveOTG = 0;
	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		अगर (BlendingAndTiming[k] == k) अणु
			mode_lib->vba.TotalNumberOfActiveOTG = mode_lib->vba.TotalNumberOfActiveOTG + 1;
		पूर्ण
	पूर्ण

	अगर (mode_lib->vba.MinActiveDRAMClockChangeMargin > 0) अणु
		*DRAMClockChangeSupport = dm_dram_घड़ी_change_vactive;
	पूर्ण अन्यथा अगर (((mode_lib->vba.SynchronizedVBlank == true || mode_lib->vba.TotalNumberOfActiveOTG == 1 || SecondMinActiveDRAMClockChangeMarginOneDisplayInVBLank > 0) && PrefetchMode == 0)) अणु
		*DRAMClockChangeSupport = dm_dram_घड़ी_change_vblank;
	पूर्ण अन्यथा अणु
		*DRAMClockChangeSupport = dm_dram_घड़ी_change_unsupported;
	पूर्ण

	FullDETBufferingTimeYStutterCriticalPlane = FullDETBufferingTimeY[0];
	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		अगर (FullDETBufferingTimeY[k] <= FullDETBufferingTimeYStutterCriticalPlane) अणु
			FullDETBufferingTimeYStutterCriticalPlane = FullDETBufferingTimeY[k];
			TimeToFinishSwathTransferStutterCriticalPlane = (SwathHeightY[k] - (LinesInDETY[k] - LinesInDETYRoundedDownToSwath[k])) * (HTotal[k] / PixelClock[k]) / VRatio[k];
		पूर्ण
	पूर्ण

	*StutterExitWatermark = SRExitTime +  ExtraLatency + 10 / DCFCLKDeepSleep;
	*StutterEnterPlusExitWatermark = dml_max(SREnterPlusExitTime + ExtraLatency + 10 / DCFCLKDeepSleep, TimeToFinishSwathTransferStutterCriticalPlane);

पूर्ण

अटल व्योम CalculateDCFCLKDeepSleep(
		काष्ठा display_mode_lib *mode_lib,
		अचिन्हित पूर्णांक NumberOfActivePlanes,
		पूर्णांक BytePerPixelY[],
		पूर्णांक BytePerPixelC[],
		द्विगुन VRatio[],
		द्विगुन VRatioChroma[],
		द्विगुन SwathWidthY[],
		द्विगुन SwathWidthC[],
		अचिन्हित पूर्णांक DPPPerPlane[],
		द्विगुन HRatio[],
		द्विगुन HRatioChroma[],
		द्विगुन PixelClock[],
		द्विगुन PSCL_THROUGHPUT[],
		द्विगुन PSCL_THROUGHPUT_CHROMA[],
		द्विगुन DPPCLK[],
		द्विगुन ReadBandwidthLuma[],
		द्विगुन ReadBandwidthChroma[],
		पूर्णांक ReturnBusWidth,
		द्विगुन *DCFCLKDeepSleep)
अणु
	द्विगुन DisplayPipeLineDeliveryTimeLuma = 0;
	द्विगुन DisplayPipeLineDeliveryTimeChroma = 0;
	अचिन्हित पूर्णांक k;
	द्विगुन ReadBandwidth = 0.0;

	//द्विगुन   DCFCLKDeepSleepPerPlane[DC__NUM_DPP__MAX];
	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु

		अगर (VRatio[k] <= 1) अणु
			DisplayPipeLineDeliveryTimeLuma = SwathWidthY[k] * DPPPerPlane[k] / HRatio[k] / PixelClock[k];
		पूर्ण अन्यथा अणु
			DisplayPipeLineDeliveryTimeLuma = SwathWidthY[k] / PSCL_THROUGHPUT[k] / DPPCLK[k];
		पूर्ण
		अगर (BytePerPixelC[k] == 0) अणु
			DisplayPipeLineDeliveryTimeChroma = 0;
		पूर्ण अन्यथा अणु
			अगर (VRatioChroma[k] <= 1) अणु
				DisplayPipeLineDeliveryTimeChroma = SwathWidthC[k] * DPPPerPlane[k] / HRatioChroma[k] / PixelClock[k];
			पूर्ण अन्यथा अणु
				DisplayPipeLineDeliveryTimeChroma = SwathWidthC[k] / PSCL_THROUGHPUT_CHROMA[k] / DPPCLK[k];
			पूर्ण
		पूर्ण

		अगर (BytePerPixelC[k] > 0) अणु
			mode_lib->vba.DCFCLKDeepSleepPerPlane[k] = dml_max(1.1 * SwathWidthY[k] * BytePerPixelY[k] / 32.0 / DisplayPipeLineDeliveryTimeLuma, 1.1 * SwathWidthC[k] * BytePerPixelC[k] / 32.0 / DisplayPipeLineDeliveryTimeChroma);
		पूर्ण अन्यथा अणु
			mode_lib->vba.DCFCLKDeepSleepPerPlane[k] = 1.1 * SwathWidthY[k] * BytePerPixelY[k] / 64.0 / DisplayPipeLineDeliveryTimeLuma;
		पूर्ण
		mode_lib->vba.DCFCLKDeepSleepPerPlane[k] = dml_max(mode_lib->vba.DCFCLKDeepSleepPerPlane[k], PixelClock[k] / 16);

	पूर्ण

	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		ReadBandwidth = ReadBandwidth + ReadBandwidthLuma[k] + ReadBandwidthChroma[k];
	पूर्ण

	*DCFCLKDeepSleep = dml_max(8.0, ReadBandwidth / ReturnBusWidth);

	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		*DCFCLKDeepSleep = dml_max(*DCFCLKDeepSleep, mode_lib->vba.DCFCLKDeepSleepPerPlane[k]);
	पूर्ण
पूर्ण

अटल व्योम CalculateUrgentBurstFactor(
		दीर्घ swath_width_luma_ub,
		दीर्घ swath_width_chroma_ub,
		अचिन्हित पूर्णांक DETBufferSizeInKByte,
		अचिन्हित पूर्णांक SwathHeightY,
		अचिन्हित पूर्णांक SwathHeightC,
		द्विगुन LineTime,
		द्विगुन UrgentLatency,
		द्विगुन CursorBufferSize,
		अचिन्हित पूर्णांक CursorWidth,
		अचिन्हित पूर्णांक CursorBPP,
		द्विगुन VRatio,
		द्विगुन VRatioC,
		द्विगुन BytePerPixelInDETY,
		द्विगुन BytePerPixelInDETC,
		द्विगुन DETBufferSizeY,
		द्विगुन DETBufferSizeC,
		द्विगुन *UrgentBurstFactorCursor,
		द्विगुन *UrgentBurstFactorLuma,
		द्विगुन *UrgentBurstFactorChroma,
		bool *NotEnoughUrgentLatencyHiding)
अणु
	द्विगुन LinesInDETLuma = 0;
	द्विगुन LinesInDETChroma = 0;
	अचिन्हित पूर्णांक LinesInCursorBuffer = 0;
	द्विगुन CursorBufferSizeInTime = 0;
	द्विगुन DETBufferSizeInTimeLuma = 0;
	द्विगुन DETBufferSizeInTimeChroma = 0;

	*NotEnoughUrgentLatencyHiding = 0;

	अगर (CursorWidth > 0) अणु
		LinesInCursorBuffer = 1 << (अचिन्हित पूर्णांक) dml_न्यूनमान(dml_log2(CursorBufferSize * 1024.0 / (CursorWidth * CursorBPP / 8.0)), 1.0);
		अगर (VRatio > 0) अणु
			CursorBufferSizeInTime = LinesInCursorBuffer * LineTime / VRatio;
			अगर (CursorBufferSizeInTime - UrgentLatency <= 0) अणु
				*NotEnoughUrgentLatencyHiding = 1;
				*UrgentBurstFactorCursor = 0;
			पूर्ण अन्यथा अणु
				*UrgentBurstFactorCursor = CursorBufferSizeInTime / (CursorBufferSizeInTime - UrgentLatency);
			पूर्ण
		पूर्ण अन्यथा अणु
			*UrgentBurstFactorCursor = 1;
		पूर्ण
	पूर्ण

	LinesInDETLuma = DETBufferSizeY / BytePerPixelInDETY / swath_width_luma_ub;
	अगर (VRatio > 0) अणु
		DETBufferSizeInTimeLuma = dml_न्यूनमान(LinesInDETLuma, SwathHeightY) * LineTime / VRatio;
		अगर (DETBufferSizeInTimeLuma - UrgentLatency <= 0) अणु
			*NotEnoughUrgentLatencyHiding = 1;
			*UrgentBurstFactorLuma = 0;
		पूर्ण अन्यथा अणु
			*UrgentBurstFactorLuma = DETBufferSizeInTimeLuma / (DETBufferSizeInTimeLuma - UrgentLatency);
		पूर्ण
	पूर्ण अन्यथा अणु
		*UrgentBurstFactorLuma = 1;
	पूर्ण

	अगर (BytePerPixelInDETC > 0) अणु
		LinesInDETChroma = DETBufferSizeC / BytePerPixelInDETC / swath_width_chroma_ub;
		अगर (VRatio > 0) अणु
			DETBufferSizeInTimeChroma = dml_न्यूनमान(LinesInDETChroma, SwathHeightC) * LineTime / VRatio;
			अगर (DETBufferSizeInTimeChroma - UrgentLatency <= 0) अणु
				*NotEnoughUrgentLatencyHiding = 1;
				*UrgentBurstFactorChroma = 0;
			पूर्ण अन्यथा अणु
				*UrgentBurstFactorChroma = DETBufferSizeInTimeChroma / (DETBufferSizeInTimeChroma - UrgentLatency);
			पूर्ण
		पूर्ण अन्यथा अणु
			*UrgentBurstFactorChroma = 1;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम CalculatePixelDeliveryTimes(
		अचिन्हित पूर्णांक NumberOfActivePlanes,
		द्विगुन VRatio[],
		द्विगुन VRatioChroma[],
		द्विगुन VRatioPrefetchY[],
		द्विगुन VRatioPrefetchC[],
		अचिन्हित पूर्णांक swath_width_luma_ub[],
		अचिन्हित पूर्णांक swath_width_chroma_ub[],
		अचिन्हित पूर्णांक DPPPerPlane[],
		द्विगुन HRatio[],
		द्विगुन HRatioChroma[],
		द्विगुन PixelClock[],
		द्विगुन PSCL_THROUGHPUT[],
		द्विगुन PSCL_THROUGHPUT_CHROMA[],
		द्विगुन DPPCLK[],
		पूर्णांक BytePerPixelC[],
		क्रमागत scan_direction_class SourceScan[],
		अचिन्हित पूर्णांक NumberOfCursors[],
		अचिन्हित पूर्णांक CursorWidth[][2],
		अचिन्हित पूर्णांक CursorBPP[][2],
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
		द्विगुन DisplayPipeRequestDeliveryTimeChromaPrefetch[],
		द्विगुन CursorRequestDeliveryTime[],
		द्विगुन CursorRequestDeliveryTimePrefetch[])
अणु
	द्विगुन req_per_swath_ub = 0;
	अचिन्हित पूर्णांक k;

	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		अगर (VRatio[k] <= 1) अणु
			DisplayPipeLineDeliveryTimeLuma[k] = swath_width_luma_ub[k] * DPPPerPlane[k] / HRatio[k] / PixelClock[k];
		पूर्ण अन्यथा अणु
			DisplayPipeLineDeliveryTimeLuma[k] = swath_width_luma_ub[k] / PSCL_THROUGHPUT[k] / DPPCLK[k];
		पूर्ण

		अगर (BytePerPixelC[k] == 0) अणु
			DisplayPipeLineDeliveryTimeChroma[k] = 0;
		पूर्ण अन्यथा अणु
			अगर (VRatioChroma[k] <= 1) अणु
				DisplayPipeLineDeliveryTimeChroma[k] = swath_width_chroma_ub[k] * DPPPerPlane[k] / HRatioChroma[k] / PixelClock[k];
			पूर्ण अन्यथा अणु
				DisplayPipeLineDeliveryTimeChroma[k] = swath_width_chroma_ub[k] / PSCL_THROUGHPUT_CHROMA[k] / DPPCLK[k];
			पूर्ण
		पूर्ण

		अगर (VRatioPrefetchY[k] <= 1) अणु
			DisplayPipeLineDeliveryTimeLumaPrefetch[k] = swath_width_luma_ub[k] * DPPPerPlane[k] / HRatio[k] / PixelClock[k];
		पूर्ण अन्यथा अणु
			DisplayPipeLineDeliveryTimeLumaPrefetch[k] = swath_width_luma_ub[k] / PSCL_THROUGHPUT[k] / DPPCLK[k];
		पूर्ण

		अगर (BytePerPixelC[k] == 0) अणु
			DisplayPipeLineDeliveryTimeChromaPrefetch[k] = 0;
		पूर्ण अन्यथा अणु
			अगर (VRatioPrefetchC[k] <= 1) अणु
				DisplayPipeLineDeliveryTimeChromaPrefetch[k] = swath_width_chroma_ub[k] * DPPPerPlane[k] / HRatioChroma[k] / PixelClock[k];
			पूर्ण अन्यथा अणु
				DisplayPipeLineDeliveryTimeChromaPrefetch[k] = swath_width_chroma_ub[k] / PSCL_THROUGHPUT_CHROMA[k] / DPPCLK[k];
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		अगर (SourceScan[k] != dm_vert) अणु
			req_per_swath_ub = swath_width_luma_ub[k] / BlockWidth256BytesY[k];
		पूर्ण अन्यथा अणु
			req_per_swath_ub = swath_width_luma_ub[k] / BlockHeight256BytesY[k];
		पूर्ण
		DisplayPipeRequestDeliveryTimeLuma[k] = DisplayPipeLineDeliveryTimeLuma[k] / req_per_swath_ub;
		DisplayPipeRequestDeliveryTimeLumaPrefetch[k] = DisplayPipeLineDeliveryTimeLumaPrefetch[k] / req_per_swath_ub;
		अगर (BytePerPixelC[k] == 0) अणु
			DisplayPipeRequestDeliveryTimeChroma[k] = 0;
			DisplayPipeRequestDeliveryTimeChromaPrefetch[k] = 0;
		पूर्ण अन्यथा अणु
			अगर (SourceScan[k] != dm_vert) अणु
				req_per_swath_ub = swath_width_chroma_ub[k] / BlockWidth256BytesC[k];
			पूर्ण अन्यथा अणु
				req_per_swath_ub = swath_width_chroma_ub[k] / BlockHeight256BytesC[k];
			पूर्ण
			DisplayPipeRequestDeliveryTimeChroma[k] = DisplayPipeLineDeliveryTimeChroma[k] / req_per_swath_ub;
			DisplayPipeRequestDeliveryTimeChromaPrefetch[k] = DisplayPipeLineDeliveryTimeChromaPrefetch[k] / req_per_swath_ub;
		पूर्ण
	पूर्ण

	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		पूर्णांक cursor_req_per_width = 0;
		cursor_req_per_width = dml_उच्चमान(CursorWidth[k][0] * CursorBPP[k][0] / 256 / 8, 1);
		अगर (NumberOfCursors[k] > 0) अणु
			अगर (VRatio[k] <= 1) अणु
				CursorRequestDeliveryTime[k] = CursorWidth[k][0] / HRatio[k] / PixelClock[k] / cursor_req_per_width;
			पूर्ण अन्यथा अणु
				CursorRequestDeliveryTime[k] = CursorWidth[k][0] / PSCL_THROUGHPUT[k] / DPPCLK[k] / cursor_req_per_width;
			पूर्ण
			अगर (VRatioPrefetchY[k] <= 1) अणु
				CursorRequestDeliveryTimePrefetch[k] = CursorWidth[k][0] / HRatio[k] / PixelClock[k] / cursor_req_per_width;
			पूर्ण अन्यथा अणु
				CursorRequestDeliveryTimePrefetch[k] = CursorWidth[k][0] / PSCL_THROUGHPUT[k] / DPPCLK[k] / cursor_req_per_width;
			पूर्ण
		पूर्ण अन्यथा अणु
			CursorRequestDeliveryTime[k] = 0;
			CursorRequestDeliveryTimePrefetch[k] = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम CalculateMetaAndPTETimes(
		पूर्णांक NumberOfActivePlanes,
		bool GPUVMEnable,
		पूर्णांक MetaChunkSize,
		पूर्णांक MinMetaChunkSizeBytes,
		पूर्णांक HTotal[],
		द्विगुन VRatio[],
		द्विगुन VRatioChroma[],
		द्विगुन DestinationLinesToRequestRowInVBlank[],
		द्विगुन DestinationLinesToRequestRowInImmediateFlip[],
		bool DCCEnable[],
		द्विगुन PixelClock[],
		पूर्णांक BytePerPixelY[],
		पूर्णांक BytePerPixelC[],
		क्रमागत scan_direction_class SourceScan[],
		पूर्णांक dpte_row_height[],
		पूर्णांक dpte_row_height_chroma[],
		पूर्णांक meta_row_width[],
		पूर्णांक meta_row_width_chroma[],
		पूर्णांक meta_row_height[],
		पूर्णांक meta_row_height_chroma[],
		पूर्णांक meta_req_width[],
		पूर्णांक meta_req_width_chroma[],
		पूर्णांक meta_req_height[],
		पूर्णांक meta_req_height_chroma[],
		पूर्णांक dpte_group_bytes[],
		पूर्णांक PTERequestSizeY[],
		पूर्णांक PTERequestSizeC[],
		पूर्णांक PixelPTEReqWidthY[],
		पूर्णांक PixelPTEReqHeightY[],
		पूर्णांक PixelPTEReqWidthC[],
		पूर्णांक PixelPTEReqHeightC[],
		पूर्णांक dpte_row_width_luma_ub[],
		पूर्णांक dpte_row_width_chroma_ub[],
		द्विगुन DST_Y_PER_PTE_ROW_NOM_L[],
		द्विगुन DST_Y_PER_PTE_ROW_NOM_C[],
		द्विगुन DST_Y_PER_META_ROW_NOM_L[],
		द्विगुन DST_Y_PER_META_ROW_NOM_C[],
		द्विगुन TimePerMetaChunkNominal[],
		द्विगुन TimePerChromaMetaChunkNominal[],
		द्विगुन TimePerMetaChunkVBlank[],
		द्विगुन TimePerChromaMetaChunkVBlank[],
		द्विगुन TimePerMetaChunkFlip[],
		द्विगुन TimePerChromaMetaChunkFlip[],
		द्विगुन समय_per_pte_group_nom_luma[],
		द्विगुन समय_per_pte_group_vblank_luma[],
		द्विगुन समय_per_pte_group_flip_luma[],
		द्विगुन समय_per_pte_group_nom_chroma[],
		द्विगुन समय_per_pte_group_vblank_chroma[],
		द्विगुन समय_per_pte_group_flip_chroma[])
अणु
	अचिन्हित पूर्णांक meta_chunk_width = 0;
	अचिन्हित पूर्णांक min_meta_chunk_width = 0;
	अचिन्हित पूर्णांक meta_chunk_per_row_पूर्णांक = 0;
	अचिन्हित पूर्णांक meta_row_reमुख्यder = 0;
	अचिन्हित पूर्णांक meta_chunk_threshold = 0;
	अचिन्हित पूर्णांक meta_chunks_per_row_ub = 0;
	अचिन्हित पूर्णांक meta_chunk_width_chroma = 0;
	अचिन्हित पूर्णांक min_meta_chunk_width_chroma = 0;
	अचिन्हित पूर्णांक meta_chunk_per_row_पूर्णांक_chroma = 0;
	अचिन्हित पूर्णांक meta_row_reमुख्यder_chroma = 0;
	अचिन्हित पूर्णांक meta_chunk_threshold_chroma = 0;
	अचिन्हित पूर्णांक meta_chunks_per_row_ub_chroma = 0;
	अचिन्हित पूर्णांक dpte_group_width_luma = 0;
	अचिन्हित पूर्णांक dpte_groups_per_row_luma_ub = 0;
	अचिन्हित पूर्णांक dpte_group_width_chroma = 0;
	अचिन्हित पूर्णांक dpte_groups_per_row_chroma_ub = 0;
	अचिन्हित पूर्णांक k;

	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		DST_Y_PER_PTE_ROW_NOM_L[k] = dpte_row_height[k] / VRatio[k];
		अगर (BytePerPixelC[k] == 0) अणु
			DST_Y_PER_PTE_ROW_NOM_C[k] = 0;
		पूर्ण अन्यथा अणु
			DST_Y_PER_PTE_ROW_NOM_C[k] = dpte_row_height_chroma[k] / VRatioChroma[k];
		पूर्ण
		DST_Y_PER_META_ROW_NOM_L[k] = meta_row_height[k] / VRatio[k];
		अगर (BytePerPixelC[k] == 0) अणु
			DST_Y_PER_META_ROW_NOM_C[k] = 0;
		पूर्ण अन्यथा अणु
			DST_Y_PER_META_ROW_NOM_C[k] = meta_row_height_chroma[k] / VRatioChroma[k];
		पूर्ण
	पूर्ण

	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		अगर (DCCEnable[k] == true) अणु
			meta_chunk_width = MetaChunkSize * 1024 * 256 / BytePerPixelY[k] / meta_row_height[k];
			min_meta_chunk_width = MinMetaChunkSizeBytes * 256 / BytePerPixelY[k] / meta_row_height[k];
			meta_chunk_per_row_पूर्णांक = meta_row_width[k] / meta_chunk_width;
			meta_row_reमुख्यder = meta_row_width[k] % meta_chunk_width;
			अगर (SourceScan[k] != dm_vert) अणु
				meta_chunk_threshold = 2 * min_meta_chunk_width - meta_req_width[k];
			पूर्ण अन्यथा अणु
				meta_chunk_threshold = 2 * min_meta_chunk_width - meta_req_height[k];
			पूर्ण
			अगर (meta_row_reमुख्यder <= meta_chunk_threshold) अणु
				meta_chunks_per_row_ub = meta_chunk_per_row_पूर्णांक + 1;
			पूर्ण अन्यथा अणु
				meta_chunks_per_row_ub = meta_chunk_per_row_पूर्णांक + 2;
			पूर्ण
			TimePerMetaChunkNominal[k] = meta_row_height[k] / VRatio[k] * HTotal[k] / PixelClock[k] / meta_chunks_per_row_ub;
			TimePerMetaChunkVBlank[k] = DestinationLinesToRequestRowInVBlank[k] * HTotal[k] / PixelClock[k] / meta_chunks_per_row_ub;
			TimePerMetaChunkFlip[k] = DestinationLinesToRequestRowInImmediateFlip[k] * HTotal[k] / PixelClock[k] / meta_chunks_per_row_ub;
			अगर (BytePerPixelC[k] == 0) अणु
				TimePerChromaMetaChunkNominal[k] = 0;
				TimePerChromaMetaChunkVBlank[k] = 0;
				TimePerChromaMetaChunkFlip[k] = 0;
			पूर्ण अन्यथा अणु
				meta_chunk_width_chroma = MetaChunkSize * 1024 * 256 / BytePerPixelC[k] / meta_row_height_chroma[k];
				min_meta_chunk_width_chroma = MinMetaChunkSizeBytes * 256 / BytePerPixelC[k] / meta_row_height_chroma[k];
				meta_chunk_per_row_पूर्णांक_chroma = (द्विगुन) meta_row_width_chroma[k] / meta_chunk_width_chroma;
				meta_row_reमुख्यder_chroma = meta_row_width_chroma[k] % meta_chunk_width_chroma;
				अगर (SourceScan[k] != dm_vert) अणु
					meta_chunk_threshold_chroma = 2 * min_meta_chunk_width_chroma - meta_req_width_chroma[k];
				पूर्ण अन्यथा अणु
					meta_chunk_threshold_chroma = 2 * min_meta_chunk_width_chroma - meta_req_height_chroma[k];
				पूर्ण
				अगर (meta_row_reमुख्यder_chroma <= meta_chunk_threshold_chroma) अणु
					meta_chunks_per_row_ub_chroma = meta_chunk_per_row_पूर्णांक_chroma + 1;
				पूर्ण अन्यथा अणु
					meta_chunks_per_row_ub_chroma = meta_chunk_per_row_पूर्णांक_chroma + 2;
				पूर्ण
				TimePerChromaMetaChunkNominal[k] = meta_row_height_chroma[k] / VRatioChroma[k] * HTotal[k] / PixelClock[k] / meta_chunks_per_row_ub_chroma;
				TimePerChromaMetaChunkVBlank[k] = DestinationLinesToRequestRowInVBlank[k] * HTotal[k] / PixelClock[k] / meta_chunks_per_row_ub_chroma;
				TimePerChromaMetaChunkFlip[k] = DestinationLinesToRequestRowInImmediateFlip[k] * HTotal[k] / PixelClock[k] / meta_chunks_per_row_ub_chroma;
			पूर्ण
		पूर्ण अन्यथा अणु
			TimePerMetaChunkNominal[k] = 0;
			TimePerMetaChunkVBlank[k] = 0;
			TimePerMetaChunkFlip[k] = 0;
			TimePerChromaMetaChunkNominal[k] = 0;
			TimePerChromaMetaChunkVBlank[k] = 0;
			TimePerChromaMetaChunkFlip[k] = 0;
		पूर्ण
	पूर्ण

	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		अगर (GPUVMEnable == true) अणु
			अगर (SourceScan[k] != dm_vert) अणु
				dpte_group_width_luma = dpte_group_bytes[k] / PTERequestSizeY[k] * PixelPTEReqWidthY[k];
			पूर्ण अन्यथा अणु
				dpte_group_width_luma = dpte_group_bytes[k] / PTERequestSizeY[k] * PixelPTEReqHeightY[k];
			पूर्ण
			dpte_groups_per_row_luma_ub = dml_उच्चमान(1.0 * dpte_row_width_luma_ub[k] / dpte_group_width_luma, 1);
			समय_per_pte_group_nom_luma[k] = DST_Y_PER_PTE_ROW_NOM_L[k] * HTotal[k] / PixelClock[k] / dpte_groups_per_row_luma_ub;
			समय_per_pte_group_vblank_luma[k] = DestinationLinesToRequestRowInVBlank[k] * HTotal[k] / PixelClock[k] / dpte_groups_per_row_luma_ub;
			समय_per_pte_group_flip_luma[k] = DestinationLinesToRequestRowInImmediateFlip[k] * HTotal[k] / PixelClock[k] / dpte_groups_per_row_luma_ub;
			अगर (BytePerPixelC[k] == 0) अणु
				समय_per_pte_group_nom_chroma[k] = 0;
				समय_per_pte_group_vblank_chroma[k] = 0;
				समय_per_pte_group_flip_chroma[k] = 0;
			पूर्ण अन्यथा अणु
				अगर (SourceScan[k] != dm_vert) अणु
					dpte_group_width_chroma = dpte_group_bytes[k] / PTERequestSizeC[k] * PixelPTEReqWidthC[k];
				पूर्ण अन्यथा अणु
					dpte_group_width_chroma = dpte_group_bytes[k] / PTERequestSizeC[k] * PixelPTEReqHeightC[k];
				पूर्ण
				dpte_groups_per_row_chroma_ub = dml_उच्चमान(1.0 * dpte_row_width_chroma_ub[k] / dpte_group_width_chroma, 1);
				समय_per_pte_group_nom_chroma[k] = DST_Y_PER_PTE_ROW_NOM_C[k] * HTotal[k] / PixelClock[k] / dpte_groups_per_row_chroma_ub;
				समय_per_pte_group_vblank_chroma[k] = DestinationLinesToRequestRowInVBlank[k] * HTotal[k] / PixelClock[k] / dpte_groups_per_row_chroma_ub;
				समय_per_pte_group_flip_chroma[k] = DestinationLinesToRequestRowInImmediateFlip[k] * HTotal[k] / PixelClock[k] / dpte_groups_per_row_chroma_ub;
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
पूर्ण

अटल व्योम CalculateVMGroupAndRequestTimes(
		अचिन्हित पूर्णांक NumberOfActivePlanes,
		bool GPUVMEnable,
		अचिन्हित पूर्णांक GPUVMMaxPageTableLevels,
		अचिन्हित पूर्णांक HTotal[],
		पूर्णांक BytePerPixelC[],
		द्विगुन DestinationLinesToRequestVMInVBlank[],
		द्विगुन DestinationLinesToRequestVMInImmediateFlip[],
		bool DCCEnable[],
		द्विगुन PixelClock[],
		पूर्णांक dpte_row_width_luma_ub[],
		पूर्णांक dpte_row_width_chroma_ub[],
		पूर्णांक vm_group_bytes[],
		अचिन्हित पूर्णांक dpde0_bytes_per_frame_ub_l[],
		अचिन्हित पूर्णांक dpde0_bytes_per_frame_ub_c[],
		पूर्णांक meta_pte_bytes_per_frame_ub_l[],
		पूर्णांक meta_pte_bytes_per_frame_ub_c[],
		द्विगुन TimePerVMGroupVBlank[],
		द्विगुन TimePerVMGroupFlip[],
		द्विगुन TimePerVMRequestVBlank[],
		द्विगुन TimePerVMRequestFlip[])
अणु
	पूर्णांक num_group_per_lower_vm_stage = 0;
	पूर्णांक num_req_per_lower_vm_stage = 0;
	अचिन्हित पूर्णांक k;

	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		अगर (GPUVMEnable == true && (DCCEnable[k] == true || GPUVMMaxPageTableLevels > 1)) अणु
			अगर (DCCEnable[k] == false) अणु
				अगर (BytePerPixelC[k] > 0) अणु
					num_group_per_lower_vm_stage = dml_उच्चमान((द्विगुन) (dpde0_bytes_per_frame_ub_l[k])
						/ (द्विगुन) (vm_group_bytes[k]), 1) + dml_उच्चमान((द्विगुन) (dpde0_bytes_per_frame_ub_c[k])
									/ (द्विगुन) (vm_group_bytes[k]), 1);
				पूर्ण अन्यथा अणु
					num_group_per_lower_vm_stage = dml_उच्चमान((द्विगुन) (dpde0_bytes_per_frame_ub_l[k])
							/ (द्विगुन) (vm_group_bytes[k]), 1);
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (GPUVMMaxPageTableLevels == 1) अणु
					अगर (BytePerPixelC[k] > 0) अणु
						num_group_per_lower_vm_stage = dml_उच्चमान((द्विगुन) (meta_pte_bytes_per_frame_ub_l[k])
							/ (द्विगुन) (vm_group_bytes[k]), 1) + dml_उच्चमान((द्विगुन) (meta_pte_bytes_per_frame_ub_c[k])
									/ (द्विगुन) (vm_group_bytes[k]), 1);
					पूर्ण अन्यथा अणु
						num_group_per_lower_vm_stage = dml_उच्चमान((द्विगुन) (meta_pte_bytes_per_frame_ub_l[k])
							/ (द्विगुन) (vm_group_bytes[k]), 1);
					पूर्ण
				पूर्ण अन्यथा अणु
					अगर (BytePerPixelC[k] > 0) अणु
						num_group_per_lower_vm_stage = 2 + dml_उच्चमान((द्विगुन) (dpde0_bytes_per_frame_ub_l[k]) / (द्विगुन) (vm_group_bytes[k]), 1)
								+ dml_उच्चमान((द्विगुन) (dpde0_bytes_per_frame_ub_c[k]) / (द्विगुन) (vm_group_bytes[k]), 1)
								+ dml_उच्चमान((द्विगुन) (meta_pte_bytes_per_frame_ub_l[k]) / (द्विगुन) (vm_group_bytes[k]), 1)
								+ dml_उच्चमान((द्विगुन) (meta_pte_bytes_per_frame_ub_c[k]) / (द्विगुन) (vm_group_bytes[k]), 1);
					पूर्ण अन्यथा अणु
						num_group_per_lower_vm_stage = 1 + dml_उच्चमान((द्विगुन) (dpde0_bytes_per_frame_ub_l[k]) / (द्विगुन) (vm_group_bytes[k]), 1)
								+ dml_उच्चमान((द्विगुन) (meta_pte_bytes_per_frame_ub_l[k]) / (द्विगुन) (vm_group_bytes[k]), 1);
					पूर्ण
				पूर्ण
			पूर्ण

			अगर (DCCEnable[k] == false) अणु
				अगर (BytePerPixelC[k] > 0) अणु
					num_req_per_lower_vm_stage = dpde0_bytes_per_frame_ub_l[k] / 64 + dpde0_bytes_per_frame_ub_c[k] / 64;
				पूर्ण अन्यथा अणु
					num_req_per_lower_vm_stage = dpde0_bytes_per_frame_ub_l[k] / 64;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (GPUVMMaxPageTableLevels == 1) अणु
					अगर (BytePerPixelC[k] > 0) अणु
						num_req_per_lower_vm_stage = meta_pte_bytes_per_frame_ub_l[k] / 64
								+ meta_pte_bytes_per_frame_ub_c[k] / 64;
					पूर्ण अन्यथा अणु
						num_req_per_lower_vm_stage = meta_pte_bytes_per_frame_ub_l[k] / 64;
					पूर्ण
				पूर्ण अन्यथा अणु
					अगर (BytePerPixelC[k] > 0) अणु
						num_req_per_lower_vm_stage = dpde0_bytes_per_frame_ub_l[k] / 64
							+ dpde0_bytes_per_frame_ub_c[k] / 64 + meta_pte_bytes_per_frame_ub_l[k]
									/ 64 + meta_pte_bytes_per_frame_ub_c[k] / 64;
					पूर्ण अन्यथा अणु
						num_req_per_lower_vm_stage = dpde0_bytes_per_frame_ub_l[k] / 64
								+ meta_pte_bytes_per_frame_ub_l[k] / 64;
					पूर्ण
				पूर्ण
			पूर्ण

			TimePerVMGroupVBlank[k] = DestinationLinesToRequestVMInVBlank[k] * HTotal[k] / PixelClock[k]
					/ num_group_per_lower_vm_stage;
			TimePerVMGroupFlip[k] = DestinationLinesToRequestVMInImmediateFlip[k] * HTotal[k] / PixelClock[k]
					/ num_group_per_lower_vm_stage;
			TimePerVMRequestVBlank[k] = DestinationLinesToRequestVMInVBlank[k] * HTotal[k] / PixelClock[k]
					/ num_req_per_lower_vm_stage;
			TimePerVMRequestFlip[k] = DestinationLinesToRequestVMInImmediateFlip[k] * HTotal[k] / PixelClock[k]
					/ num_req_per_lower_vm_stage;

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

अटल व्योम CalculateStutterEfficiency(
		पूर्णांक NumberOfActivePlanes,
		दीर्घ ROBBufferSizeInKByte,
		द्विगुन TotalDataReadBandwidth,
		द्विगुन DCFCLK,
		द्विगुन ReturnBW,
		द्विगुन SRExitTime,
		bool SynchronizedVBlank,
		पूर्णांक DPPPerPlane[],
		द्विगुन DETBufferSizeY[],
		पूर्णांक BytePerPixelY[],
		द्विगुन BytePerPixelDETY[],
		द्विगुन SwathWidthY[],
		पूर्णांक SwathHeightY[],
		पूर्णांक SwathHeightC[],
		द्विगुन DCCRateLuma[],
		द्विगुन DCCRateChroma[],
		पूर्णांक HTotal[],
		पूर्णांक VTotal[],
		द्विगुन PixelClock[],
		द्विगुन VRatio[],
		क्रमागत scan_direction_class SourceScan[],
		पूर्णांक BlockHeight256BytesY[],
		पूर्णांक BlockWidth256BytesY[],
		पूर्णांक BlockHeight256BytesC[],
		पूर्णांक BlockWidth256BytesC[],
		पूर्णांक DCCYMaxUncompressedBlock[],
		पूर्णांक DCCCMaxUncompressedBlock[],
		पूर्णांक VActive[],
		bool DCCEnable[],
		bool WritebackEnable[],
		द्विगुन ReadBandwidthPlaneLuma[],
		द्विगुन ReadBandwidthPlaneChroma[],
		द्विगुन meta_row_bw[],
		द्विगुन dpte_row_bw[],
		द्विगुन *StutterEfficiencyNotIncludingVBlank,
		द्विगुन *StutterEfficiency,
		द्विगुन *StutterPeriodOut)
अणु
	द्विगुन FullDETBufferingTimeY[DC__NUM_DPP__MAX] = अणु 0 पूर्ण;
	द्विगुन FrameTimeForMinFullDETBufferingTime = 0;
	द्विगुन StutterPeriod = 0;
	द्विगुन AverageReadBandwidth = 0;
	द्विगुन TotalRowReadBandwidth = 0;
	द्विगुन AverageDCCCompressionRate = 0;
	द्विगुन PartOfBurstThatFitsInROB = 0;
	द्विगुन StutterBurstTime = 0;
	पूर्णांक TotalActiveWriteback = 0;
	द्विगुन VBlankTime = 0;
	द्विगुन SmallestVBlank = 0;
	पूर्णांक BytePerPixelYCriticalPlane = 0;
	द्विगुन SwathWidthYCriticalPlane = 0;
	द्विगुन LinesInDETY[DC__NUM_DPP__MAX] = अणु 0 पूर्ण;
	द्विगुन LinesInDETYRoundedDownToSwath[DC__NUM_DPP__MAX] = अणु 0 पूर्ण;
	द्विगुन LinesToFinishSwathTransferStutterCriticalPlane = 0;
	द्विगुन MaximumEffectiveCompressionLuma = 0;
	द्विगुन    MaximumEffectiveCompressionChroma = 0;
	अचिन्हित पूर्णांक k;

	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		LinesInDETY[k] = DETBufferSizeY[k] / BytePerPixelDETY[k] / SwathWidthY[k];
		LinesInDETYRoundedDownToSwath[k] = dml_न्यूनमान(LinesInDETY[k], SwathHeightY[k]);
		FullDETBufferingTimeY[k] = LinesInDETYRoundedDownToSwath[k] * (HTotal[k] / PixelClock[k]) / VRatio[k];
	पूर्ण

	StutterPeriod = FullDETBufferingTimeY[0];
	FrameTimeForMinFullDETBufferingTime = VTotal[0] * HTotal[0] / PixelClock[0];
	BytePerPixelYCriticalPlane = BytePerPixelY[0];
	SwathWidthYCriticalPlane = SwathWidthY[0];
	LinesToFinishSwathTransferStutterCriticalPlane = SwathHeightY[0]
			- (LinesInDETY[0] - LinesInDETYRoundedDownToSwath[0]);

	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		अगर (FullDETBufferingTimeY[k] < StutterPeriod) अणु
			StutterPeriod = FullDETBufferingTimeY[k];
			FrameTimeForMinFullDETBufferingTime = VTotal[k] * HTotal[k] / PixelClock[k];
			BytePerPixelYCriticalPlane = BytePerPixelY[k];
			SwathWidthYCriticalPlane = SwathWidthY[k];
			LinesToFinishSwathTransferStutterCriticalPlane = SwathHeightY[k]
					- (LinesInDETY[k] - LinesInDETYRoundedDownToSwath[k]);
		पूर्ण
	पूर्ण

	AverageReadBandwidth = 0;
	TotalRowReadBandwidth = 0;
	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		अगर (DCCEnable[k] == true) अणु
			अगर ((SourceScan[k] == dm_vert && BlockWidth256BytesY[k] > SwathHeightY[k])
					|| (SourceScan[k] != dm_vert
							&& BlockHeight256BytesY[k] > SwathHeightY[k])
					|| DCCYMaxUncompressedBlock[k] < 256) अणु
				MaximumEffectiveCompressionLuma = 2;
			पूर्ण अन्यथा अणु
				MaximumEffectiveCompressionLuma = 4;
			पूर्ण
			AverageReadBandwidth = AverageReadBandwidth + ReadBandwidthPlaneLuma[k] / dml_min(DCCRateLuma[k], MaximumEffectiveCompressionLuma);

			अगर (ReadBandwidthPlaneChroma[k] > 0) अणु
				अगर ((SourceScan[k] == dm_vert && BlockWidth256BytesC[k] > SwathHeightC[k])
						|| (SourceScan[k] != dm_vert && BlockHeight256BytesC[k] > SwathHeightC[k])
						|| DCCCMaxUncompressedBlock[k] < 256) अणु
					MaximumEffectiveCompressionChroma = 2;
				पूर्ण अन्यथा अणु
					MaximumEffectiveCompressionChroma = 4;
				पूर्ण
				AverageReadBandwidth = AverageReadBandwidth + ReadBandwidthPlaneChroma[k] / dml_min(DCCRateChroma[k], MaximumEffectiveCompressionChroma);
			पूर्ण
		पूर्ण अन्यथा अणु
			AverageReadBandwidth = AverageReadBandwidth + ReadBandwidthPlaneLuma[k] + ReadBandwidthPlaneChroma[k];
		पूर्ण
		TotalRowReadBandwidth = TotalRowReadBandwidth + DPPPerPlane[k] * (meta_row_bw[k] + dpte_row_bw[k]);
	पूर्ण

	AverageDCCCompressionRate = TotalDataReadBandwidth / AverageReadBandwidth;
	PartOfBurstThatFitsInROB = dml_min(StutterPeriod * TotalDataReadBandwidth, ROBBufferSizeInKByte * 1024 * AverageDCCCompressionRate);
	StutterBurstTime = PartOfBurstThatFitsInROB / AverageDCCCompressionRate / ReturnBW + (StutterPeriod * TotalDataReadBandwidth
			- PartOfBurstThatFitsInROB) / (DCFCLK * 64) + StutterPeriod * TotalRowReadBandwidth / ReturnBW;
	StutterBurstTime = dml_max(StutterBurstTime, LinesToFinishSwathTransferStutterCriticalPlane * BytePerPixelYCriticalPlane * SwathWidthYCriticalPlane / ReturnBW);

	TotalActiveWriteback = 0;
	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		अगर (WritebackEnable[k] == true) अणु
			TotalActiveWriteback = TotalActiveWriteback + 1;
		पूर्ण
	पूर्ण

	अगर (TotalActiveWriteback == 0) अणु
		*StutterEfficiencyNotIncludingVBlank = (1
				- (SRExitTime + StutterBurstTime) / StutterPeriod) * 100;
	पूर्ण अन्यथा अणु
		*StutterEfficiencyNotIncludingVBlank = 0;
	पूर्ण

	अगर (SynchronizedVBlank == true || NumberOfActivePlanes == 1) अणु
		SmallestVBlank = (VTotal[0] - VActive[0]) * HTotal[0] / PixelClock[0];
	पूर्ण अन्यथा अणु
		SmallestVBlank = 0;
	पूर्ण
	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		अगर (SynchronizedVBlank == true || NumberOfActivePlanes == 1) अणु
			VBlankTime = (VTotal[k] - VActive[k]) * HTotal[k] / PixelClock[k];
		पूर्ण अन्यथा अणु
			VBlankTime = 0;
		पूर्ण
		SmallestVBlank = dml_min(SmallestVBlank, VBlankTime);
	पूर्ण

	*StutterEfficiency =  (*StutterEfficiencyNotIncludingVBlank / 100.0 * (FrameTimeForMinFullDETBufferingTime - SmallestVBlank) + SmallestVBlank) / FrameTimeForMinFullDETBufferingTime * 100;

	अगर (StutterPeriodOut)
		*StutterPeriodOut = StutterPeriod;
पूर्ण

अटल व्योम CalculateSwathAndDETConfiguration(
		bool ForceSingleDPP,
		पूर्णांक NumberOfActivePlanes,
		दीर्घ DETBufferSizeInKByte,
		द्विगुन MaximumSwathWidthLuma[],
		द्विगुन MaximumSwathWidthChroma[],
		क्रमागत scan_direction_class SourceScan[],
		क्रमागत source_क्रमmat_class SourcePixelFormat[],
		क्रमागत dm_swizzle_mode SurfaceTiling[],
		पूर्णांक ViewportWidth[],
		पूर्णांक ViewportHeight[],
		पूर्णांक SurfaceWidthY[],
		पूर्णांक SurfaceWidthC[],
		पूर्णांक SurfaceHeightY[],
		पूर्णांक SurfaceHeightC[],
		पूर्णांक Read256BytesBlockHeightY[],
		पूर्णांक Read256BytesBlockHeightC[],
		पूर्णांक Read256BytesBlockWidthY[],
		पूर्णांक Read256BytesBlockWidthC[],
		क्रमागत odm_combine_mode ODMCombineEnabled[],
		पूर्णांक BlendingAndTiming[],
		पूर्णांक BytePerPixY[],
		पूर्णांक BytePerPixC[],
		द्विगुन BytePerPixDETY[],
		द्विगुन BytePerPixDETC[],
		पूर्णांक HActive[],
		द्विगुन HRatio[],
		द्विगुन HRatioChroma[],
		पूर्णांक DPPPerPlane[],
		पूर्णांक swath_width_luma_ub[],
		पूर्णांक swath_width_chroma_ub[],
		द्विगुन SwathWidth[],
		द्विगुन SwathWidthChroma[],
		पूर्णांक SwathHeightY[],
		पूर्णांक SwathHeightC[],
		द्विगुन DETBufferSizeY[],
		द्विगुन DETBufferSizeC[],
		bool ViewportSizeSupportPerPlane[],
		bool *ViewportSizeSupport)
अणु
	पूर्णांक MaximumSwathHeightY[DC__NUM_DPP__MAX] = अणु 0 पूर्ण;
	पूर्णांक MaximumSwathHeightC[DC__NUM_DPP__MAX] = अणु 0 पूर्ण;
	पूर्णांक MinimumSwathHeightY = 0;
	पूर्णांक MinimumSwathHeightC = 0;
	दीर्घ RoundedUpMaxSwathSizeBytesY = 0;
	दीर्घ RoundedUpMaxSwathSizeBytesC = 0;
	दीर्घ RoundedUpMinSwathSizeBytesY = 0;
	दीर्घ RoundedUpMinSwathSizeBytesC = 0;
	दीर्घ RoundedUpSwathSizeBytesY = 0;
	दीर्घ RoundedUpSwathSizeBytesC = 0;
	द्विगुन SwathWidthSingleDPP[DC__NUM_DPP__MAX] = अणु 0 पूर्ण;
	द्विगुन SwathWidthSingleDPPChroma[DC__NUM_DPP__MAX] = अणु 0 पूर्ण;
	पूर्णांक k;

	CalculateSwathWidth(
			ForceSingleDPP,
			NumberOfActivePlanes,
			SourcePixelFormat,
			SourceScan,
			ViewportWidth,
			ViewportHeight,
			SurfaceWidthY,
			SurfaceWidthC,
			SurfaceHeightY,
			SurfaceHeightC,
			ODMCombineEnabled,
			BytePerPixY,
			BytePerPixC,
			Read256BytesBlockHeightY,
			Read256BytesBlockHeightC,
			Read256BytesBlockWidthY,
			Read256BytesBlockWidthC,
			BlendingAndTiming,
			HActive,
			HRatio,
			DPPPerPlane,
			SwathWidthSingleDPP,
			SwathWidthSingleDPPChroma,
			SwathWidth,
			SwathWidthChroma,
			MaximumSwathHeightY,
			MaximumSwathHeightC,
			swath_width_luma_ub,
			swath_width_chroma_ub);

	*ViewportSizeSupport = true;
	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		अगर ((SourcePixelFormat[k] == dm_444_64 || SourcePixelFormat[k] == dm_444_32
				|| SourcePixelFormat[k] == dm_444_16
				|| SourcePixelFormat[k] == dm_mono_16
				|| SourcePixelFormat[k] == dm_mono_8
				|| SourcePixelFormat[k] == dm_rgbe)) अणु
			अगर (SurfaceTiling[k] == dm_sw_linear
				|| (SourcePixelFormat[k] == dm_444_64
					&& (SurfaceTiling[k] == dm_sw_64kb_s || SurfaceTiling[k] == dm_sw_64kb_s_t || SurfaceTiling[k] == dm_sw_64kb_s_x)
					&& SourceScan[k] != dm_vert)) अणु
				MinimumSwathHeightY = MaximumSwathHeightY[k];
			पूर्ण अन्यथा अगर (SourcePixelFormat[k] == dm_444_8 && SourceScan[k] == dm_vert) अणु
				MinimumSwathHeightY = MaximumSwathHeightY[k];
			पूर्ण अन्यथा अणु
				MinimumSwathHeightY = MaximumSwathHeightY[k] / 2;
			पूर्ण
			MinimumSwathHeightC = MaximumSwathHeightC[k];
		पूर्ण अन्यथा अणु
			अगर (SurfaceTiling[k] == dm_sw_linear) अणु
				MinimumSwathHeightY = MaximumSwathHeightY[k];
				MinimumSwathHeightC = MaximumSwathHeightC[k];
			पूर्ण अन्यथा अगर (SourcePixelFormat[k] == dm_rgbe_alpha
					&& SourceScan[k] == dm_vert) अणु
				MinimumSwathHeightY = MaximumSwathHeightY[k] / 2;
				MinimumSwathHeightC = MaximumSwathHeightC[k];
			पूर्ण अन्यथा अगर (SourcePixelFormat[k] == dm_rgbe_alpha) अणु
				MinimumSwathHeightY = MaximumSwathHeightY[k] / 2;
				MinimumSwathHeightC = MaximumSwathHeightC[k] / 2;
			पूर्ण अन्यथा अगर (SourcePixelFormat[k] == dm_420_8 && SourceScan[k] == dm_vert) अणु
				MinimumSwathHeightY = MaximumSwathHeightY[k];
				MinimumSwathHeightC = MaximumSwathHeightC[k] / 2;
			पूर्ण अन्यथा अणु
				MinimumSwathHeightC = MaximumSwathHeightC[k] / 2;
				MinimumSwathHeightY = MaximumSwathHeightY[k] / 2;
			पूर्ण
		पूर्ण

		RoundedUpMaxSwathSizeBytesY = swath_width_luma_ub[k] * BytePerPixDETY[k]
				* MaximumSwathHeightY[k];
		RoundedUpMinSwathSizeBytesY = swath_width_luma_ub[k] * BytePerPixDETY[k]
				* MinimumSwathHeightY;
		अगर (SourcePixelFormat[k] == dm_420_10) अणु
			RoundedUpMaxSwathSizeBytesY = dml_उच्चमान((द्विगुन) RoundedUpMaxSwathSizeBytesY, 256);
			RoundedUpMinSwathSizeBytesY = dml_उच्चमान((द्विगुन) RoundedUpMinSwathSizeBytesY, 256);
		पूर्ण
		RoundedUpMaxSwathSizeBytesC = swath_width_chroma_ub[k] * BytePerPixDETC[k]
				* MaximumSwathHeightC[k];
		RoundedUpMinSwathSizeBytesC = swath_width_chroma_ub[k] * BytePerPixDETC[k]
				* MinimumSwathHeightC;
		अगर (SourcePixelFormat[k] == dm_420_10) अणु
			RoundedUpMaxSwathSizeBytesC = dml_उच्चमान(RoundedUpMaxSwathSizeBytesC, 256);
			RoundedUpMinSwathSizeBytesC = dml_उच्चमान(RoundedUpMinSwathSizeBytesC, 256);
		पूर्ण

		अगर (RoundedUpMaxSwathSizeBytesY + RoundedUpMaxSwathSizeBytesC
				<= DETBufferSizeInKByte * 1024 / 2) अणु
			SwathHeightY[k] = MaximumSwathHeightY[k];
			SwathHeightC[k] = MaximumSwathHeightC[k];
			RoundedUpSwathSizeBytesY = RoundedUpMaxSwathSizeBytesY;
			RoundedUpSwathSizeBytesC = RoundedUpMaxSwathSizeBytesC;
		पूर्ण अन्यथा अगर (RoundedUpMaxSwathSizeBytesY >= 1.5 * RoundedUpMaxSwathSizeBytesC
				&& RoundedUpMinSwathSizeBytesY + RoundedUpMaxSwathSizeBytesC
						<= DETBufferSizeInKByte * 1024 / 2) अणु
			SwathHeightY[k] = MinimumSwathHeightY;
			SwathHeightC[k] = MaximumSwathHeightC[k];
			RoundedUpSwathSizeBytesY = RoundedUpMinSwathSizeBytesY;
			RoundedUpSwathSizeBytesC = RoundedUpMaxSwathSizeBytesC;
		पूर्ण अन्यथा अगर (RoundedUpMaxSwathSizeBytesY < 1.5 * RoundedUpMaxSwathSizeBytesC
				&& RoundedUpMaxSwathSizeBytesY + RoundedUpMinSwathSizeBytesC
						<= DETBufferSizeInKByte * 1024 / 2) अणु
			SwathHeightY[k] = MaximumSwathHeightY[k];
			SwathHeightC[k] = MinimumSwathHeightC;
			RoundedUpSwathSizeBytesY = RoundedUpMaxSwathSizeBytesY;
			RoundedUpSwathSizeBytesC = RoundedUpMinSwathSizeBytesC;
		पूर्ण अन्यथा अणु
			SwathHeightY[k] = MinimumSwathHeightY;
			SwathHeightC[k] = MinimumSwathHeightC;
			RoundedUpSwathSizeBytesY = RoundedUpMinSwathSizeBytesY;
			RoundedUpSwathSizeBytesC = RoundedUpMinSwathSizeBytesC;
		पूर्ण

		अगर (SwathHeightC[k] == 0) अणु
			DETBufferSizeY[k] = DETBufferSizeInKByte * 1024;
			DETBufferSizeC[k] = 0;
		पूर्ण अन्यथा अगर (RoundedUpSwathSizeBytesY <= 1.5 * RoundedUpSwathSizeBytesC) अणु
			DETBufferSizeY[k] = DETBufferSizeInKByte * 1024 / 2;
			DETBufferSizeC[k] = DETBufferSizeInKByte * 1024 / 2;
		पूर्ण अन्यथा अणु
			DETBufferSizeY[k] = DETBufferSizeInKByte * 1024 * 2 / 3;
			DETBufferSizeC[k] = DETBufferSizeInKByte * 1024 / 3;
		पूर्ण

		अगर (RoundedUpMinSwathSizeBytesY + RoundedUpMinSwathSizeBytesC
				> DETBufferSizeInKByte * 1024 / 2
				|| SwathWidth[k] > MaximumSwathWidthLuma[k]
				|| (SwathHeightC[k] > 0
						&& SwathWidthChroma[k] > MaximumSwathWidthChroma[k])) अणु
			*ViewportSizeSupport = false;
			ViewportSizeSupportPerPlane[k] = false;
		पूर्ण अन्यथा अणु
			ViewportSizeSupportPerPlane[k] = true;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम CalculateSwathWidth(
		bool ForceSingleDPP,
		पूर्णांक NumberOfActivePlanes,
		क्रमागत source_क्रमmat_class SourcePixelFormat[],
		क्रमागत scan_direction_class SourceScan[],
		अचिन्हित पूर्णांक ViewportWidth[],
		अचिन्हित पूर्णांक ViewportHeight[],
		अचिन्हित पूर्णांक SurfaceWidthY[],
		अचिन्हित पूर्णांक SurfaceWidthC[],
		अचिन्हित पूर्णांक SurfaceHeightY[],
		अचिन्हित पूर्णांक SurfaceHeightC[],
		क्रमागत odm_combine_mode ODMCombineEnabled[],
		पूर्णांक BytePerPixY[],
		पूर्णांक BytePerPixC[],
		पूर्णांक Read256BytesBlockHeightY[],
		पूर्णांक Read256BytesBlockHeightC[],
		पूर्णांक Read256BytesBlockWidthY[],
		पूर्णांक Read256BytesBlockWidthC[],
		पूर्णांक BlendingAndTiming[],
		अचिन्हित पूर्णांक HActive[],
		द्विगुन HRatio[],
		पूर्णांक DPPPerPlane[],
		द्विगुन SwathWidthSingleDPPY[],
		द्विगुन SwathWidthSingleDPPC[],
		द्विगुन SwathWidthY[],
		द्विगुन SwathWidthC[],
		पूर्णांक MaximumSwathHeightY[],
		पूर्णांक MaximumSwathHeightC[],
		अचिन्हित पूर्णांक swath_width_luma_ub[],
		अचिन्हित पूर्णांक swath_width_chroma_ub[])
अणु
	अचिन्हित पूर्णांक k, j;
	दीर्घ surface_width_ub_l;
	दीर्घ surface_height_ub_l;
	दीर्घ surface_width_ub_c;
	दीर्घ surface_height_ub_c;

	क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
		क्रमागत odm_combine_mode MainPlaneODMCombine = 0;
		surface_width_ub_l = dml_उच्चमान(SurfaceWidthY[k], Read256BytesBlockWidthY[k]);
		surface_height_ub_l = dml_उच्चमान(SurfaceHeightY[k], Read256BytesBlockHeightY[k]);
		surface_width_ub_c = dml_उच्चमान(SurfaceWidthC[k], Read256BytesBlockWidthC[k]);
		surface_height_ub_c = dml_उच्चमान(SurfaceHeightC[k], Read256BytesBlockHeightC[k]);

		अगर (SourceScan[k] != dm_vert) अणु
			SwathWidthSingleDPPY[k] = ViewportWidth[k];
		पूर्ण अन्यथा अणु
			SwathWidthSingleDPPY[k] = ViewportHeight[k];
		पूर्ण

		MainPlaneODMCombine = ODMCombineEnabled[k];
		क्रम (j = 0; j < NumberOfActivePlanes; ++j) अणु
			अगर (BlendingAndTiming[k] == j) अणु
				MainPlaneODMCombine = ODMCombineEnabled[j];
			पूर्ण
		पूर्ण

		अगर (MainPlaneODMCombine == dm_odm_combine_mode_4to1) अणु
			SwathWidthY[k] = dml_min(SwathWidthSingleDPPY[k], dml_round(HActive[k] / 4.0 * HRatio[k]));
		पूर्ण अन्यथा अगर (MainPlaneODMCombine == dm_odm_combine_mode_2to1) अणु
			SwathWidthY[k] = dml_min(SwathWidthSingleDPPY[k], dml_round(HActive[k] / 2.0 * HRatio[k]));
		पूर्ण अन्यथा अगर (DPPPerPlane[k] == 2) अणु
			SwathWidthY[k] = SwathWidthSingleDPPY[k] / 2;
		पूर्ण अन्यथा अणु
			SwathWidthY[k] = SwathWidthSingleDPPY[k];
		पूर्ण

		अगर (SourcePixelFormat[k] == dm_420_8 || SourcePixelFormat[k] == dm_420_10 || SourcePixelFormat[k] == dm_420_12) अणु
			SwathWidthC[k] = SwathWidthY[k] / 2;
			SwathWidthSingleDPPC[k] = SwathWidthSingleDPPY[k] / 2;
		पूर्ण अन्यथा अणु
			SwathWidthC[k] = SwathWidthY[k];
			SwathWidthSingleDPPC[k] = SwathWidthSingleDPPY[k];
		पूर्ण

		अगर (ForceSingleDPP == true) अणु
			SwathWidthY[k] = SwathWidthSingleDPPY[k];
			SwathWidthC[k] = SwathWidthSingleDPPC[k];
		पूर्ण

		surface_width_ub_l  = dml_उच्चमान(SurfaceWidthY[k], Read256BytesBlockWidthY[k]);
		surface_height_ub_l = dml_उच्चमान(SurfaceHeightY[k], Read256BytesBlockHeightY[k]);
		surface_width_ub_c  = dml_उच्चमान(SurfaceWidthC[k], Read256BytesBlockWidthC[k]);
		surface_height_ub_c = dml_उच्चमान(SurfaceHeightC[k], Read256BytesBlockHeightC[k]);

		अगर (SourceScan[k] != dm_vert) अणु
			MaximumSwathHeightY[k] = Read256BytesBlockHeightY[k];
			MaximumSwathHeightC[k] = Read256BytesBlockHeightC[k];
			swath_width_luma_ub[k] = dml_min(surface_width_ub_l, (दीर्घ) dml_उच्चमान(SwathWidthY[k] - 1,
					Read256BytesBlockWidthY[k]) + Read256BytesBlockWidthY[k]);
			अगर (BytePerPixC[k] > 0) अणु
				swath_width_chroma_ub[k] = dml_min(surface_width_ub_c, (दीर्घ) dml_उच्चमान(SwathWidthC[k] - 1,
						Read256BytesBlockWidthC[k]) + Read256BytesBlockWidthC[k]);
			पूर्ण अन्यथा अणु
				swath_width_chroma_ub[k] = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			MaximumSwathHeightY[k] = Read256BytesBlockWidthY[k];
			MaximumSwathHeightC[k] = Read256BytesBlockWidthC[k];
			swath_width_luma_ub[k] = dml_min(surface_height_ub_l, (दीर्घ) dml_उच्चमान(SwathWidthY[k] - 1,
					Read256BytesBlockHeightY[k]) + Read256BytesBlockHeightY[k]);
			अगर (BytePerPixC[k] > 0) अणु
				swath_width_chroma_ub[k] = dml_min(surface_height_ub_c, (दीर्घ) dml_उच्चमान(SwathWidthC[k] - 1,
						Read256BytesBlockHeightC[k]) + Read256BytesBlockHeightC[k]);
			पूर्ण अन्यथा अणु
				swath_width_chroma_ub[k] = 0;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल द्विगुन CalculateExtraLatency(
		दीर्घ RoundTripPingLatencyCycles,
		दीर्घ ReorderingBytes,
		द्विगुन DCFCLK,
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
		द्विगुन HostVMMinPageSize,
		पूर्णांक HostVMMaxNonCachedPageTableLevels)
अणु
	द्विगुन ExtraLatencyBytes = 0;
	ExtraLatencyBytes = CalculateExtraLatencyBytes(
					ReorderingBytes,
					TotalNumberOfActiveDPP,
					PixelChunkSizeInKByte,
					TotalNumberOfDCCActiveDPP,
					MetaChunkSize,
					GPUVMEnable,
					HostVMEnable,
					NumberOfActivePlanes,
					NumberOfDPP,
					dpte_group_bytes,
					PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData,
					PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly,
					HostVMMinPageSize,
					HostVMMaxNonCachedPageTableLevels);

	वापस (RoundTripPingLatencyCycles + 32) / DCFCLK + ExtraLatencyBytes / ReturnBW;
पूर्ण

अटल द्विगुन CalculateExtraLatencyBytes(
		दीर्घ ReorderingBytes,
		पूर्णांक TotalNumberOfActiveDPP,
		पूर्णांक PixelChunkSizeInKByte,
		पूर्णांक TotalNumberOfDCCActiveDPP,
		पूर्णांक MetaChunkSize,
		bool GPUVMEnable,
		bool HostVMEnable,
		पूर्णांक NumberOfActivePlanes,
		पूर्णांक NumberOfDPP[],
		पूर्णांक dpte_group_bytes[],
		द्विगुन PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData,
		द्विगुन PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly,
		द्विगुन HostVMMinPageSize,
		पूर्णांक HostVMMaxNonCachedPageTableLevels)
अणु
	द्विगुन ret = 0;
	द्विगुन HostVMInefficiencyFactor = 0;
	पूर्णांक HostVMDynamicLevels = 0;
	अचिन्हित पूर्णांक k;

	अगर (GPUVMEnable == true && HostVMEnable == true) अणु
		HostVMInefficiencyFactor = PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData / PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly;
		अगर (HostVMMinPageSize < 2048) अणु
			HostVMDynamicLevels = HostVMMaxNonCachedPageTableLevels;
		पूर्ण अन्यथा अगर (HostVMMinPageSize >= 2048 && HostVMMinPageSize < 1048576) अणु
			HostVMDynamicLevels = dml_max(0, (पूर्णांक) HostVMMaxNonCachedPageTableLevels - 1);
		पूर्ण अन्यथा अणु
			HostVMDynamicLevels = dml_max(0, (पूर्णांक) HostVMMaxNonCachedPageTableLevels - 2);
		पूर्ण
	पूर्ण अन्यथा अणु
		HostVMInefficiencyFactor = 1;
		HostVMDynamicLevels = 0;
	पूर्ण

	ret = ReorderingBytes + (TotalNumberOfActiveDPP * PixelChunkSizeInKByte + TotalNumberOfDCCActiveDPP * MetaChunkSize) * 1024.0;

	अगर (GPUVMEnable == true) अणु
		क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
			ret = ret + NumberOfDPP[k] * dpte_group_bytes[k] * (1 + 8 * HostVMDynamicLevels) * HostVMInefficiencyFactor;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण


अटल द्विगुन CalculateUrgentLatency(
		द्विगुन UrgentLatencyPixelDataOnly,
		द्विगुन UrgentLatencyPixelMixedWithVMData,
		द्विगुन UrgentLatencyVMDataOnly,
		bool DoUrgentLatencyAdjusपंचांगent,
		द्विगुन UrgentLatencyAdjusपंचांगentFabricClockComponent,
		द्विगुन UrgentLatencyAdjusपंचांगentFabricClockReference,
		द्विगुन FabricClock)
अणु
	द्विगुन ret;

	ret = dml_max3(UrgentLatencyPixelDataOnly, UrgentLatencyPixelMixedWithVMData, UrgentLatencyVMDataOnly);
	अगर (DoUrgentLatencyAdjusपंचांगent == true) अणु
		ret = ret + UrgentLatencyAdjusपंचांगentFabricClockComponent * (UrgentLatencyAdjusपंचांगentFabricClockReference / FabricClock - 1);
	पूर्ण
	वापस ret;
पूर्ण


अटल व्योम UseMinimumDCFCLK(
		काष्ठा display_mode_lib *mode_lib,
		पूर्णांक MaxInterDCNTileRepeaters,
		पूर्णांक MaxPrefetchMode,
		द्विगुन FinalDRAMClockChangeLatency,
		द्विगुन SREnterPlusExitTime,
		पूर्णांक ReturnBusWidth,
		पूर्णांक RoundTripPingLatencyCycles,
		पूर्णांक ReorderingBytes,
		पूर्णांक PixelChunkSizeInKByte,
		पूर्णांक MetaChunkSize,
		bool GPUVMEnable,
		पूर्णांक GPUVMMaxPageTableLevels,
		bool HostVMEnable,
		पूर्णांक NumberOfActivePlanes,
		द्विगुन HostVMMinPageSize,
		पूर्णांक HostVMMaxNonCachedPageTableLevels,
		bool DynamicMetadataVMEnabled,
		क्रमागत immediate_flip_requirement ImmediateFlipRequirement,
		bool ProgressiveToInterlaceUnitInOPP,
		द्विगुन MaxAveragePercentOfIdealSDPPortBWDisplayCanUseInNormalSystemOperation,
		द्विगुन PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData,
		द्विगुन PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly,
		द्विगुन PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelDataOnly,
		पूर्णांक VTotal[],
		पूर्णांक VActive[],
		पूर्णांक DynamicMetadataTransmittedBytes[],
		पूर्णांक DynamicMetadataLinesBeक्रमeActiveRequired[],
		bool Interlace[],
		द्विगुन RequiredDPPCLK[][2][DC__NUM_DPP__MAX],
		द्विगुन RequiredDISPCLK[][2],
		द्विगुन UrgLatency[],
		अचिन्हित पूर्णांक NoOfDPP[][2][DC__NUM_DPP__MAX],
		द्विगुन ProjectedDCFCLKDeepSleep[][2],
		द्विगुन MaximumVStartup[][2][DC__NUM_DPP__MAX],
		द्विगुन TotalVActivePixelBandwidth[][2],
		द्विगुन TotalVActiveCursorBandwidth[][2],
		द्विगुन TotalMetaRowBandwidth[][2],
		द्विगुन TotalDPTERowBandwidth[][2],
		अचिन्हित पूर्णांक TotalNumberOfActiveDPP[][2],
		अचिन्हित पूर्णांक TotalNumberOfDCCActiveDPP[][2],
		पूर्णांक dpte_group_bytes[],
		द्विगुन PrefetchLinesY[][2][DC__NUM_DPP__MAX],
		द्विगुन PrefetchLinesC[][2][DC__NUM_DPP__MAX],
		पूर्णांक swath_width_luma_ub_all_states[][2][DC__NUM_DPP__MAX],
		पूर्णांक swath_width_chroma_ub_all_states[][2][DC__NUM_DPP__MAX],
		पूर्णांक BytePerPixelY[],
		पूर्णांक BytePerPixelC[],
		पूर्णांक HTotal[],
		द्विगुन PixelClock[],
		द्विगुन PDEAndMetaPTEBytesPerFrame[][2][DC__NUM_DPP__MAX],
		द्विगुन DPTEBytesPerRow[][2][DC__NUM_DPP__MAX],
		द्विगुन MetaRowBytes[][2][DC__NUM_DPP__MAX],
		bool DynamicMetadataEnable[],
		द्विगुन VActivePixelBandwidth[][2][DC__NUM_DPP__MAX],
		द्विगुन VActiveCursorBandwidth[][2][DC__NUM_DPP__MAX],
		द्विगुन ReadBandwidthLuma[],
		द्विगुन ReadBandwidthChroma[],
		द्विगुन DCFCLKPerState[],
		द्विगुन DCFCLKState[][2])
अणु
	द्विगुन   NormalEfficiency = 0;
	द्विगुन   PTEEfficiency = 0;
	द्विगुन   TotalMaxPrefetchFlipDPTERowBandwidth[DC__VOLTAGE_STATES][2] = अणु अणु 0 पूर्ण पूर्ण;
	अचिन्हित पूर्णांक i, j, k;

	NormalEfficiency =  (HostVMEnable == true ? PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData
			: PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelDataOnly) / 100.0;
	PTEEfficiency =  (HostVMEnable == true ? PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly
			/ PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData : 1.0);
	क्रम (i = 0; i < mode_lib->soc.num_states; ++i) अणु
		क्रम (j = 0; j <= 1; ++j) अणु
			द्विगुन PixelDCFCLKCyclesRequiredInPrefetch[DC__NUM_DPP__MAX] = अणु 0 पूर्ण;
			द्विगुन PrefetchPixelLinesTime[DC__NUM_DPP__MAX] = अणु 0 पूर्ण;
			द्विगुन DCFCLKRequiredForPeakBandwidthPerPlane[DC__NUM_DPP__MAX] = अणु 0 पूर्ण;
			द्विगुन DynamicMetadataVMExtraLatency[DC__NUM_DPP__MAX] = अणु 0 पूर्ण;
			द्विगुन MinimumTWait = 0;
			द्विगुन NonDPTEBandwidth = 0;
			द्विगुन DPTEBandwidth = 0;
			द्विगुन DCFCLKRequiredForAverageBandwidth = 0;
			द्विगुन ExtraLatencyBytes = 0;
			द्विगुन ExtraLatencyCycles = 0;
			द्विगुन DCFCLKRequiredForPeakBandwidth = 0;
			पूर्णांक NoOfDPPState[DC__NUM_DPP__MAX] = अणु 0 पूर्ण;
			द्विगुन MinimumTvmPlus2Tr0 = 0;

			TotalMaxPrefetchFlipDPTERowBandwidth[i][j] = 0;
			क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
				TotalMaxPrefetchFlipDPTERowBandwidth[i][j] = TotalMaxPrefetchFlipDPTERowBandwidth[i][j]
					+ NoOfDPP[i][j][k] * DPTEBytesPerRow[i][j][k] / (15.75 * HTotal[k] / PixelClock[k]);
			पूर्ण

			क्रम (k = 0; k <= NumberOfActivePlanes - 1; ++k) अणु
				NoOfDPPState[k] = NoOfDPP[i][j][k];
			पूर्ण

			MinimumTWait = CalculateTWait(MaxPrefetchMode, FinalDRAMClockChangeLatency, UrgLatency[i], SREnterPlusExitTime);
			NonDPTEBandwidth = TotalVActivePixelBandwidth[i][j] + TotalVActiveCursorBandwidth[i][j] + TotalMetaRowBandwidth[i][j];
			DPTEBandwidth =  (HostVMEnable == true || ImmediateFlipRequirement == dm_immediate_flip_required) ?
					TotalMaxPrefetchFlipDPTERowBandwidth[i][j] : TotalDPTERowBandwidth[i][j];
			DCFCLKRequiredForAverageBandwidth = dml_max3(ProjectedDCFCLKDeepSleep[i][j],
					(NonDPTEBandwidth + TotalDPTERowBandwidth[i][j]) / ReturnBusWidth / (MaxAveragePercentOfIdealSDPPortBWDisplayCanUseInNormalSystemOperation / 100),
					(NonDPTEBandwidth + DPTEBandwidth / PTEEfficiency) / NormalEfficiency / ReturnBusWidth);

			ExtraLatencyBytes = CalculateExtraLatencyBytes(ReorderingBytes, TotalNumberOfActiveDPP[i][j], PixelChunkSizeInKByte, TotalNumberOfDCCActiveDPP[i][j],
					MetaChunkSize, GPUVMEnable, HostVMEnable, NumberOfActivePlanes, NoOfDPPState, dpte_group_bytes,
					PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelMixedWithVMData, PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyVMDataOnly,
					HostVMMinPageSize, HostVMMaxNonCachedPageTableLevels);
			ExtraLatencyCycles = RoundTripPingLatencyCycles + 32 + ExtraLatencyBytes / NormalEfficiency / ReturnBusWidth;
			क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
				द्विगुन DCFCLKCyclesRequiredInPrefetch = अणु 0 पूर्ण;
				द्विगुन ExpectedPrefetchBWAcceleration = अणु 0 पूर्ण;
				द्विगुन PrefetchTime = अणु 0 पूर्ण;

				PixelDCFCLKCyclesRequiredInPrefetch[k] = (PrefetchLinesY[i][j][k] * swath_width_luma_ub_all_states[i][j][k] * BytePerPixelY[k]
					+ PrefetchLinesC[i][j][k] * swath_width_chroma_ub_all_states[i][j][k] * BytePerPixelC[k]) / NormalEfficiency / ReturnBusWidth;
				DCFCLKCyclesRequiredInPrefetch = 2 * ExtraLatencyCycles / NoOfDPPState[k] + PDEAndMetaPTEBytesPerFrame[i][j][k] / PTEEfficiency
					/ NormalEfficiency / ReturnBusWidth *  (GPUVMMaxPageTableLevels > 2 ? 1 : 0) + 2 * DPTEBytesPerRow[i][j][k] / PTEEfficiency
					/ NormalEfficiency / ReturnBusWidth + 2 * MetaRowBytes[i][j][k] / NormalEfficiency / ReturnBusWidth + PixelDCFCLKCyclesRequiredInPrefetch[k];
				PrefetchPixelLinesTime[k] = dml_max(PrefetchLinesY[i][j][k], PrefetchLinesC[i][j][k]) * HTotal[k] / PixelClock[k];
				ExpectedPrefetchBWAcceleration = (VActivePixelBandwidth[i][j][k] + VActiveCursorBandwidth[i][j][k]) / (ReadBandwidthLuma[k] + ReadBandwidthChroma[k]);
				DynamicMetadataVMExtraLatency[k] = (GPUVMEnable == true && DynamicMetadataEnable[k] == true && DynamicMetadataVMEnabled == true) ?
						UrgLatency[i] * GPUVMMaxPageTableLevels *  (HostVMEnable == true ? HostVMMaxNonCachedPageTableLevels + 1 : 1) : 0;
				PrefetchTime = (MaximumVStartup[i][j][k] - 1) * HTotal[k] / PixelClock[k] - MinimumTWait - UrgLatency[i] * ((GPUVMMaxPageTableLevels <= 2 ? GPUVMMaxPageTableLevels
						: GPUVMMaxPageTableLevels - 2) * (HostVMEnable == true ? HostVMMaxNonCachedPageTableLevels + 1 : 1) - 1) - DynamicMetadataVMExtraLatency[k];

				अगर (PrefetchTime > 0) अणु
					द्विगुन ExpectedVRatioPrefetch = अणु 0 पूर्ण;
					ExpectedVRatioPrefetch = PrefetchPixelLinesTime[k] / (PrefetchTime * PixelDCFCLKCyclesRequiredInPrefetch[k] / DCFCLKCyclesRequiredInPrefetch);
					DCFCLKRequiredForPeakBandwidthPerPlane[k] = NoOfDPPState[k] * PixelDCFCLKCyclesRequiredInPrefetch[k] / PrefetchPixelLinesTime[k]
						* dml_max(1.0, ExpectedVRatioPrefetch) * dml_max(1.0, ExpectedVRatioPrefetch / 4) * ExpectedPrefetchBWAcceleration;
					अगर (HostVMEnable == true || ImmediateFlipRequirement == dm_immediate_flip_required) अणु
						DCFCLKRequiredForPeakBandwidthPerPlane[k] = DCFCLKRequiredForPeakBandwidthPerPlane[k]
							+ NoOfDPPState[k] * DPTEBandwidth / PTEEfficiency / NormalEfficiency / ReturnBusWidth;
					पूर्ण
				पूर्ण अन्यथा अणु
					DCFCLKRequiredForPeakBandwidthPerPlane[k] = DCFCLKPerState[i];
				पूर्ण
				अगर (DynamicMetadataEnable[k] == true) अणु
					द्विगुन TsetupPipe = अणु 0 पूर्ण;
					द्विगुन TdmbfPipe = अणु 0 पूर्ण;
					द्विगुन TdmsksPipe = अणु 0 पूर्ण;
					द्विगुन TdmecPipe = अणु 0 पूर्ण;
					द्विगुन AllowedTimeForUrgentExtraLatency = अणु 0 पूर्ण;

					CalculateDynamicMetadataParameters(
							MaxInterDCNTileRepeaters,
							RequiredDPPCLK[i][j][k],
							RequiredDISPCLK[i][j],
							ProjectedDCFCLKDeepSleep[i][j],
							PixelClock[k],
							HTotal[k],
							VTotal[k] - VActive[k],
							DynamicMetadataTransmittedBytes[k],
							DynamicMetadataLinesBeक्रमeActiveRequired[k],
							Interlace[k],
							ProgressiveToInterlaceUnitInOPP,
							&TsetupPipe,
							&TdmbfPipe,
							&TdmecPipe,
							&TdmsksPipe);
					AllowedTimeForUrgentExtraLatency = MaximumVStartup[i][j][k] * HTotal[k] / PixelClock[k] - MinimumTWait - TsetupPipe
							- TdmbfPipe - TdmecPipe - TdmsksPipe - DynamicMetadataVMExtraLatency[k];
					अगर (AllowedTimeForUrgentExtraLatency > 0) अणु
						DCFCLKRequiredForPeakBandwidthPerPlane[k] = dml_max(DCFCLKRequiredForPeakBandwidthPerPlane[k],
								ExtraLatencyCycles / AllowedTimeForUrgentExtraLatency);
					पूर्ण अन्यथा अणु
						DCFCLKRequiredForPeakBandwidthPerPlane[k] = DCFCLKPerState[i];
					पूर्ण
				पूर्ण
			पूर्ण
			DCFCLKRequiredForPeakBandwidth = 0;
			क्रम (k = 0; k <= NumberOfActivePlanes - 1; ++k) अणु
				DCFCLKRequiredForPeakBandwidth = DCFCLKRequiredForPeakBandwidth + DCFCLKRequiredForPeakBandwidthPerPlane[k];
			पूर्ण
			MinimumTvmPlus2Tr0 = UrgLatency[i] * (GPUVMEnable == true ? (HostVMEnable == true ?
					(GPUVMMaxPageTableLevels + 2) * (HostVMMaxNonCachedPageTableLevels + 1) - 1 : GPUVMMaxPageTableLevels + 1) : 0);
			क्रम (k = 0; k < NumberOfActivePlanes; ++k) अणु
				द्विगुन MaximumTvmPlus2Tr0PlusTsw = अणु 0 पूर्ण;
				MaximumTvmPlus2Tr0PlusTsw = (MaximumVStartup[i][j][k] - 2) * HTotal[k] / PixelClock[k] - MinimumTWait - DynamicMetadataVMExtraLatency[k];
				अगर (MaximumTvmPlus2Tr0PlusTsw <= MinimumTvmPlus2Tr0 + PrefetchPixelLinesTime[k] / 4) अणु
					DCFCLKRequiredForPeakBandwidth = DCFCLKPerState[i];
				पूर्ण अन्यथा अणु
					DCFCLKRequiredForPeakBandwidth = dml_max3(DCFCLKRequiredForPeakBandwidth, 2 * ExtraLatencyCycles
							/ (MaximumTvmPlus2Tr0PlusTsw - MinimumTvmPlus2Tr0 - PrefetchPixelLinesTime[k] / 4),
						(2 * ExtraLatencyCycles + PixelDCFCLKCyclesRequiredInPrefetch[k]) / (MaximumTvmPlus2Tr0PlusTsw - MinimumTvmPlus2Tr0));
				पूर्ण
			पूर्ण
			DCFCLKState[i][j] = dml_min(DCFCLKPerState[i], 1.05 * (1 + mode_lib->vba.PercentMarginOverMinimumRequiredDCFCLK / 100)
					* dml_max(DCFCLKRequiredForAverageBandwidth, DCFCLKRequiredForPeakBandwidth));
		पूर्ण
	पूर्ण
पूर्ण

#पूर्ण_अगर /* CONFIG_DRM_AMD_DC_DCN */
