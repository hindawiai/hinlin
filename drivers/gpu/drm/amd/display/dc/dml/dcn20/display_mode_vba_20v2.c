<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
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
#समावेश "display_mode_vba_20v2.h"
#समावेश "../dml_inline_defs.h"

/*
 * NOTE:
 *   This file is gcc-parseable HW gospel, coming straight from HW engineers.
 *
 * It करोesn't adhere to Linux kernel style and someबार will करो things in odd
 * ways. Unless there is something clearly wrong with it the code should
 * reमुख्य as-is as it provides us with a guarantee from HW that it is correct.
 */

#घोषणा BPP_INVALID 0
#घोषणा BPP_BLENDED_PIPE 0xffffffff
#घोषणा DCN20_MAX_DSC_IMAGE_WIDTH 5184
#घोषणा DCN20_MAX_420_IMAGE_WIDTH 4096

अटल द्विगुन adjust_ReturnBW(
		काष्ठा display_mode_lib *mode_lib,
		द्विगुन ReturnBW,
		bool DCCEnabledAnyPlane,
		द्विगुन ReturnBandwidthToDCN);
अटल अचिन्हित पूर्णांक dscceComputeDelay(
		अचिन्हित पूर्णांक bpc,
		द्विगुन bpp,
		अचिन्हित पूर्णांक sliceWidth,
		अचिन्हित पूर्णांक numSlices,
		क्रमागत output_क्रमmat_class pixelFormat);
अटल अचिन्हित पूर्णांक dscComputeDelay(क्रमागत output_क्रमmat_class pixelFormat);
अटल bool CalculateDelayAfterScaler(
		काष्ठा display_mode_lib *mode_lib,
		द्विगुन ReturnBW,
		द्विगुन ReadBandwidthPlaneLuma,
		द्विगुन ReadBandwidthPlaneChroma,
		द्विगुन TotalDataReadBandwidth,
		द्विगुन DisplayPipeLineDeliveryTimeLuma,
		द्विगुन DisplayPipeLineDeliveryTimeChroma,
		द्विगुन DPPCLK,
		द्विगुन DISPCLK,
		द्विगुन PixelClock,
		अचिन्हित पूर्णांक DSCDelay,
		अचिन्हित पूर्णांक DPPPerPlane,
		bool ScalerEnabled,
		अचिन्हित पूर्णांक NumberOfCursors,
		द्विगुन DPPCLKDelaySubtotal,
		द्विगुन DPPCLKDelaySCL,
		द्विगुन DPPCLKDelaySCLLBOnly,
		द्विगुन DPPCLKDelayCNVCFormater,
		द्विगुन DPPCLKDelayCNVCCursor,
		द्विगुन DISPCLKDelaySubtotal,
		अचिन्हित पूर्णांक ScalerRecoutWidth,
		क्रमागत output_क्रमmat_class OutputFormat,
		अचिन्हित पूर्णांक HTotal,
		अचिन्हित पूर्णांक SwathWidthSingleDPPY,
		द्विगुन BytePerPixelDETY,
		द्विगुन BytePerPixelDETC,
		अचिन्हित पूर्णांक SwathHeightY,
		अचिन्हित पूर्णांक SwathHeightC,
		bool Interlace,
		bool ProgressiveToInterlaceUnitInOPP,
		द्विगुन *DSTXAfterScaler,
		द्विगुन *DSTYAfterScaler
		);
// Super monster function with some 45 argument
अटल bool CalculatePrefetchSchedule(
		काष्ठा display_mode_lib *mode_lib,
		द्विगुन DPPCLK,
		द्विगुन DISPCLK,
		द्विगुन PixelClock,
		द्विगुन DCFCLKDeepSleep,
		अचिन्हित पूर्णांक DPPPerPlane,
		अचिन्हित पूर्णांक NumberOfCursors,
		अचिन्हित पूर्णांक VBlank,
		अचिन्हित पूर्णांक HTotal,
		अचिन्हित पूर्णांक MaxInterDCNTileRepeaters,
		अचिन्हित पूर्णांक VStartup,
		अचिन्हित पूर्णांक PageTableLevels,
		bool GPUVMEnable,
		bool DynamicMetadataEnable,
		अचिन्हित पूर्णांक DynamicMetadataLinesBeक्रमeActiveRequired,
		अचिन्हित पूर्णांक DynamicMetadataTransmittedBytes,
		bool DCCEnable,
		द्विगुन UrgentLatencyPixelDataOnly,
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
		bool InterlaceEnable,
		bool ProgressiveToInterlaceUnitInOPP,
		द्विगुन DSTXAfterScaler,
		द्विगुन DSTYAfterScaler,
		द्विगुन *DestinationLinesForPrefetch,
		द्विगुन *PrefetchBandwidth,
		द्विगुन *DestinationLinesToRequestVMInVBlank,
		द्विगुन *DestinationLinesToRequestRowInVBlank,
		द्विगुन *VRatioPrefetchY,
		द्विगुन *VRatioPrefetchC,
		द्विगुन *RequiredPrefetchPixDataBW,
		द्विगुन *Tno_bw,
		अचिन्हित पूर्णांक *VUpdateOffsetPix,
		द्विगुन *VUpdateWidthPix,
		द्विगुन *VReadyOffsetPix);
अटल द्विगुन RoundToDFSGranularityUp(द्विगुन Clock, द्विगुन VCOSpeed);
अटल द्विगुन RoundToDFSGranularityDown(द्विगुन Clock, द्विगुन VCOSpeed);
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
		अचिन्हित पूर्णांक VMMPageSize,
		अचिन्हित पूर्णांक PTEBufferSizeInRequestsLuma,
		अचिन्हित पूर्णांक PDEProcessingBufIn64KBReqs,
		अचिन्हित पूर्णांक Pitch,
		अचिन्हित पूर्णांक DCCMetaPitch,
		अचिन्हित पूर्णांक *MacroTileWidth,
		अचिन्हित पूर्णांक *MetaRowByte,
		अचिन्हित पूर्णांक *PixelPTEBytesPerRow,
		bool *PTEBufferSizeNotExceeded,
		अचिन्हित पूर्णांक *dpte_row_height,
		अचिन्हित पूर्णांक *meta_row_height);
अटल द्विगुन CalculateTWait(
		अचिन्हित पूर्णांक PrefetchMode,
		द्विगुन DRAMClockChangeLatency,
		द्विगुन UrgentLatencyPixelDataOnly,
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
		द्विगुन *dpte_row_bw,
		द्विगुन *qual_row_bw);
अटल व्योम CalculateFlipSchedule(
		काष्ठा display_mode_lib *mode_lib,
		द्विगुन UrgentExtraLatency,
		द्विगुन UrgentLatencyPixelDataOnly,
		अचिन्हित पूर्णांक GPUVMMaxPageTableLevels,
		bool GPUVMEnable,
		द्विगुन BandwidthAvailableForImmediateFlip,
		अचिन्हित पूर्णांक TotImmediateFlipBytes,
		क्रमागत source_क्रमmat_class SourcePixelFormat,
		अचिन्हित पूर्णांक ImmediateFlipBytes,
		द्विगुन LineTime,
		द्विगुन VRatio,
		द्विगुन Tno_bw,
		द्विगुन PDEAndMetaPTEBytesFrame,
		अचिन्हित पूर्णांक MetaRowByte,
		अचिन्हित पूर्णांक PixelPTEBytesPerRow,
		bool DCCEnable,
		अचिन्हित पूर्णांक dpte_row_height,
		अचिन्हित पूर्णांक meta_row_height,
		द्विगुन qual_row_bw,
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

अटल व्योम dml20v2_DisplayPipeConfiguration(काष्ठा display_mode_lib *mode_lib);
अटल व्योम dml20v2_DISPCLKDPPCLKDCFCLKDeepSleepPrefetchParametersWatermarksAndPerक्रमmanceCalculation(
		काष्ठा display_mode_lib *mode_lib);

व्योम dml20v2_recalculate(काष्ठा display_mode_lib *mode_lib)
अणु
	ModeSupportAndSystemConfiguration(mode_lib);
	mode_lib->vba.FabricAndDRAMBandwidth = dml_min(
		mode_lib->vba.DRAMSpeed * mode_lib->vba.NumberOfChannels * mode_lib->vba.DRAMChannelWidth,
		mode_lib->vba.FabricClock * mode_lib->vba.FabricDatapathToDCNDataReturn) / 1000.0;
	PixelClockAdjusपंचांगentForProgressiveToInterlaceUnit(mode_lib);
	dml20v2_DisplayPipeConfiguration(mode_lib);
	dml20v2_DISPCLKDPPCLKDCFCLKDeepSleepPrefetchParametersWatermarksAndPerक्रमmanceCalculation(mode_lib);
पूर्ण

अटल द्विगुन adjust_ReturnBW(
		काष्ठा display_mode_lib *mode_lib,
		द्विगुन ReturnBW,
		bool DCCEnabledAnyPlane,
		द्विगुन ReturnBandwidthToDCN)
अणु
	द्विगुन CriticalCompression;

	अगर (DCCEnabledAnyPlane
			&& ReturnBandwidthToDCN
					> mode_lib->vba.DCFCLK * mode_lib->vba.ReturnBusWidth / 4.0)
		ReturnBW =
				dml_min(
						ReturnBW,
						ReturnBandwidthToDCN * 4
								* (1.0
										- mode_lib->vba.UrgentLatencyPixelDataOnly
												/ ((mode_lib->vba.ROBBufferSizeInKByte
														- mode_lib->vba.PixelChunkSizeInKByte)
														* 1024
														/ ReturnBandwidthToDCN
														- mode_lib->vba.DCFCLK
																* mode_lib->vba.ReturnBusWidth
																/ 4)
										+ mode_lib->vba.UrgentLatencyPixelDataOnly));

	CriticalCompression = 2.0 * mode_lib->vba.ReturnBusWidth * mode_lib->vba.DCFCLK
			* mode_lib->vba.UrgentLatencyPixelDataOnly
			/ (ReturnBandwidthToDCN * mode_lib->vba.UrgentLatencyPixelDataOnly
					+ (mode_lib->vba.ROBBufferSizeInKByte
							- mode_lib->vba.PixelChunkSizeInKByte)
							* 1024);

	अगर (DCCEnabledAnyPlane && CriticalCompression > 1.0 && CriticalCompression < 4.0)
		ReturnBW =
				dml_min(
						ReturnBW,
						4.0 * ReturnBandwidthToDCN
								* (mode_lib->vba.ROBBufferSizeInKByte
										- mode_lib->vba.PixelChunkSizeInKByte)
								* 1024
								* mode_lib->vba.ReturnBusWidth
								* mode_lib->vba.DCFCLK
								* mode_lib->vba.UrgentLatencyPixelDataOnly
								/ dml_घात(
										(ReturnBandwidthToDCN
												* mode_lib->vba.UrgentLatencyPixelDataOnly
												+ (mode_lib->vba.ROBBufferSizeInKByte
														- mode_lib->vba.PixelChunkSizeInKByte)
														* 1024),
										2));

	वापस ReturnBW;
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
	अचिन्हित पूर्णांक pixelsPerClock, lstall, D, initalXmitDelay, w, s, ix, wx, p, l0, a, ax, l,
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
		s = 1;
	अन्यथा
		s = 0;

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
	Delay = l * wx * (numSlices - 1) + ax + s + lstall + 22;

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

अटल bool CalculateDelayAfterScaler(
		काष्ठा display_mode_lib *mode_lib,
		द्विगुन ReturnBW,
		द्विगुन ReadBandwidthPlaneLuma,
		द्विगुन ReadBandwidthPlaneChroma,
		द्विगुन TotalDataReadBandwidth,
		द्विगुन DisplayPipeLineDeliveryTimeLuma,
		द्विगुन DisplayPipeLineDeliveryTimeChroma,
		द्विगुन DPPCLK,
		द्विगुन DISPCLK,
		द्विगुन PixelClock,
		अचिन्हित पूर्णांक DSCDelay,
		अचिन्हित पूर्णांक DPPPerPlane,
		bool ScalerEnabled,
		अचिन्हित पूर्णांक NumberOfCursors,
		द्विगुन DPPCLKDelaySubtotal,
		द्विगुन DPPCLKDelaySCL,
		द्विगुन DPPCLKDelaySCLLBOnly,
		द्विगुन DPPCLKDelayCNVCFormater,
		द्विगुन DPPCLKDelayCNVCCursor,
		द्विगुन DISPCLKDelaySubtotal,
		अचिन्हित पूर्णांक ScalerRecoutWidth,
		क्रमागत output_क्रमmat_class OutputFormat,
		अचिन्हित पूर्णांक HTotal,
		अचिन्हित पूर्णांक SwathWidthSingleDPPY,
		द्विगुन BytePerPixelDETY,
		द्विगुन BytePerPixelDETC,
		अचिन्हित पूर्णांक SwathHeightY,
		अचिन्हित पूर्णांक SwathHeightC,
		bool Interlace,
		bool ProgressiveToInterlaceUnitInOPP,
		द्विगुन *DSTXAfterScaler,
		द्विगुन *DSTYAfterScaler
		)
अणु
	अचिन्हित पूर्णांक DPPCycles, DISPCLKCycles;
	द्विगुन DataFabricLineDeliveryTimeLuma;
	द्विगुन DataFabricLineDeliveryTimeChroma;
	द्विगुन DSTTotalPixelsAfterScaler;

	DataFabricLineDeliveryTimeLuma = SwathWidthSingleDPPY * SwathHeightY * dml_उच्चमान(BytePerPixelDETY, 1) / (mode_lib->vba.ReturnBW * ReadBandwidthPlaneLuma / TotalDataReadBandwidth);
	mode_lib->vba.LastPixelOfLineExtraWatermark = dml_max(mode_lib->vba.LastPixelOfLineExtraWatermark, DataFabricLineDeliveryTimeLuma - DisplayPipeLineDeliveryTimeLuma);

	अगर (BytePerPixelDETC != 0) अणु
		DataFabricLineDeliveryTimeChroma = SwathWidthSingleDPPY / 2 * SwathHeightC * dml_उच्चमान(BytePerPixelDETC, 2) / (mode_lib->vba.ReturnBW * ReadBandwidthPlaneChroma / TotalDataReadBandwidth);
		mode_lib->vba.LastPixelOfLineExtraWatermark = dml_max(mode_lib->vba.LastPixelOfLineExtraWatermark, DataFabricLineDeliveryTimeChroma - DisplayPipeLineDeliveryTimeChroma);
	पूर्ण

	अगर (ScalerEnabled)
		DPPCycles = DPPCLKDelaySubtotal + DPPCLKDelaySCL;
	अन्यथा
		DPPCycles = DPPCLKDelaySubtotal + DPPCLKDelaySCLLBOnly;

	DPPCycles = DPPCycles + DPPCLKDelayCNVCFormater + NumberOfCursors * DPPCLKDelayCNVCCursor;

	DISPCLKCycles = DISPCLKDelaySubtotal;

	अगर (DPPCLK == 0.0 || DISPCLK == 0.0)
		वापस true;

	*DSTXAfterScaler = DPPCycles * PixelClock / DPPCLK + DISPCLKCycles * PixelClock / DISPCLK
			+ DSCDelay;

	अगर (DPPPerPlane > 1)
		*DSTXAfterScaler = *DSTXAfterScaler + ScalerRecoutWidth;

	अगर (OutputFormat == dm_420 || (Interlace && ProgressiveToInterlaceUnitInOPP))
		*DSTYAfterScaler = 1;
	अन्यथा
		*DSTYAfterScaler = 0;

	DSTTotalPixelsAfterScaler = ((द्विगुन) (*DSTYAfterScaler * HTotal)) + *DSTXAfterScaler;
	*DSTYAfterScaler = dml_न्यूनमान(DSTTotalPixelsAfterScaler / HTotal, 1);
	*DSTXAfterScaler = DSTTotalPixelsAfterScaler - ((द्विगुन) (*DSTYAfterScaler * HTotal));

	वापस true;
पूर्ण

अटल bool CalculatePrefetchSchedule(
		काष्ठा display_mode_lib *mode_lib,
		द्विगुन DPPCLK,
		द्विगुन DISPCLK,
		द्विगुन PixelClock,
		द्विगुन DCFCLKDeepSleep,
		अचिन्हित पूर्णांक DPPPerPlane,
		अचिन्हित पूर्णांक NumberOfCursors,
		अचिन्हित पूर्णांक VBlank,
		अचिन्हित पूर्णांक HTotal,
		अचिन्हित पूर्णांक MaxInterDCNTileRepeaters,
		अचिन्हित पूर्णांक VStartup,
		अचिन्हित पूर्णांक PageTableLevels,
		bool GPUVMEnable,
		bool DynamicMetadataEnable,
		अचिन्हित पूर्णांक DynamicMetadataLinesBeक्रमeActiveRequired,
		अचिन्हित पूर्णांक DynamicMetadataTransmittedBytes,
		bool DCCEnable,
		द्विगुन UrgentLatencyPixelDataOnly,
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
		bool InterlaceEnable,
		bool ProgressiveToInterlaceUnitInOPP,
		द्विगुन DSTXAfterScaler,
		द्विगुन DSTYAfterScaler,
		द्विगुन *DestinationLinesForPrefetch,
		द्विगुन *PrefetchBandwidth,
		द्विगुन *DestinationLinesToRequestVMInVBlank,
		द्विगुन *DestinationLinesToRequestRowInVBlank,
		द्विगुन *VRatioPrefetchY,
		द्विगुन *VRatioPrefetchC,
		द्विगुन *RequiredPrefetchPixDataBW,
		द्विगुन *Tno_bw,
		अचिन्हित पूर्णांक *VUpdateOffsetPix,
		द्विगुन *VUpdateWidthPix,
		द्विगुन *VReadyOffsetPix)
अणु
	bool MyError = false;
	द्विगुन TotalRepeaterDelayTime;
	द्विगुन Tdm, LineTime, Tsetup;
	द्विगुन dst_y_prefetch_equ;
	द्विगुन Tsw_oto;
	द्विगुन prefetch_bw_oto;
	द्विगुन Tvm_oto;
	द्विगुन Tr0_oto;
	द्विगुन Tpre_oto;
	द्विगुन dst_y_prefetch_oto;
	द्विगुन TimeForFetchingMetaPTE = 0;
	द्विगुन TimeForFetchingRowInVBlank = 0;
	द्विगुन LinesToRequestPrefetchPixelData = 0;

	*VUpdateOffsetPix = dml_उच्चमान(HTotal / 4.0, 1);
	TotalRepeaterDelayTime = MaxInterDCNTileRepeaters * (2.0 / DPPCLK + 3.0 / DISPCLK);
	*VUpdateWidthPix = (14.0 / DCFCLKDeepSleep + 12.0 / DPPCLK + TotalRepeaterDelayTime)
			* PixelClock;

	*VReadyOffsetPix = dml_max(
			150.0 / DPPCLK,
			TotalRepeaterDelayTime + 20.0 / DCFCLKDeepSleep + 10.0 / DPPCLK)
			* PixelClock;

	Tsetup = (द्विगुन) (*VUpdateOffsetPix + *VUpdateWidthPix + *VReadyOffsetPix) / PixelClock;

	LineTime = (द्विगुन) HTotal / PixelClock;

	अगर (DynamicMetadataEnable) अणु
		द्विगुन Tdmbf, Tdmec, Tdmsks;

		Tdm = dml_max(0.0, UrgentExtraLatency - TCalc);
		Tdmbf = DynamicMetadataTransmittedBytes / 4.0 / DISPCLK;
		Tdmec = LineTime;
		अगर (DynamicMetadataLinesBeक्रमeActiveRequired == 0)
			Tdmsks = VBlank * LineTime / 2.0;
		अन्यथा
			Tdmsks = DynamicMetadataLinesBeक्रमeActiveRequired * LineTime;
		अगर (InterlaceEnable && !ProgressiveToInterlaceUnitInOPP)
			Tdmsks = Tdmsks / 2;
		अगर (VStartup * LineTime
				< Tsetup + TWait + UrgentExtraLatency + Tdmbf + Tdmec + Tdmsks) अणु
			MyError = true;
		पूर्ण
	पूर्ण अन्यथा
		Tdm = 0;

	अगर (GPUVMEnable) अणु
		अगर (PageTableLevels == 4)
			*Tno_bw = UrgentExtraLatency + UrgentLatencyPixelDataOnly;
		अन्यथा अगर (PageTableLevels == 3)
			*Tno_bw = UrgentExtraLatency;
		अन्यथा
			*Tno_bw = 0;
	पूर्ण अन्यथा अगर (DCCEnable)
		*Tno_bw = LineTime;
	अन्यथा
		*Tno_bw = LineTime / 4;

	dst_y_prefetch_equ = VStartup - dml_max(TCalc + TWait, XFCRemoteSurfaceFlipDelay) / LineTime
			- (Tsetup + Tdm) / LineTime
			- (DSTYAfterScaler + DSTXAfterScaler / HTotal);

	Tsw_oto = dml_max(PrefetchSourceLinesY, PrefetchSourceLinesC) * LineTime;

	prefetch_bw_oto = (MetaRowByte + PixelPTEBytesPerRow
			+ PrefetchSourceLinesY * SwathWidthY * dml_उच्चमान(BytePerPixelDETY, 1)
			+ PrefetchSourceLinesC * SwathWidthY / 2 * dml_उच्चमान(BytePerPixelDETC, 2))
			/ Tsw_oto;

	अगर (GPUVMEnable == true) अणु
		Tvm_oto =
				dml_max(
						*Tno_bw + PDEAndMetaPTEBytesFrame / prefetch_bw_oto,
						dml_max(
								UrgentExtraLatency
										+ UrgentLatencyPixelDataOnly
												* (PageTableLevels
														- 1),
								LineTime / 4.0));
	पूर्ण अन्यथा
		Tvm_oto = LineTime / 4.0;

	अगर ((GPUVMEnable == true || DCCEnable == true)) अणु
		Tr0_oto = dml_max(
				(MetaRowByte + PixelPTEBytesPerRow) / prefetch_bw_oto,
				dml_max(UrgentLatencyPixelDataOnly, dml_max(LineTime - Tvm_oto, LineTime / 4)));
	पूर्ण अन्यथा
		Tr0_oto = LineTime - Tvm_oto;

	Tpre_oto = Tvm_oto + Tr0_oto + Tsw_oto;

	dst_y_prefetch_oto = Tpre_oto / LineTime;

	अगर (dst_y_prefetch_oto < dst_y_prefetch_equ)
		*DestinationLinesForPrefetch = dst_y_prefetch_oto;
	अन्यथा
		*DestinationLinesForPrefetch = dst_y_prefetch_equ;

	*DestinationLinesForPrefetch = dml_न्यूनमान(4.0 * (*DestinationLinesForPrefetch + 0.125), 1)
			/ 4;

	dml_prपूर्णांक("DML: VStartup: %d\n", VStartup);
	dml_prपूर्णांक("DML: TCalc: %f\n", TCalc);
	dml_prपूर्णांक("DML: TWait: %f\n", TWait);
	dml_prपूर्णांक("DML: XFCRemoteSurfaceFlipDelay: %f\n", XFCRemoteSurfaceFlipDelay);
	dml_prपूर्णांक("DML: LineTime: %f\n", LineTime);
	dml_prपूर्णांक("DML: Tsetup: %f\n", Tsetup);
	dml_prपूर्णांक("DML: Tdm: %f\n", Tdm);
	dml_prपूर्णांक("DML: DSTYAfterScaler: %f\n", DSTYAfterScaler);
	dml_prपूर्णांक("DML: DSTXAfterScaler: %f\n", DSTXAfterScaler);
	dml_prपूर्णांक("DML: HTotal: %d\n", HTotal);

	*PrefetchBandwidth = 0;
	*DestinationLinesToRequestVMInVBlank = 0;
	*DestinationLinesToRequestRowInVBlank = 0;
	*VRatioPrefetchY = 0;
	*VRatioPrefetchC = 0;
	*RequiredPrefetchPixDataBW = 0;
	अगर (*DestinationLinesForPrefetch > 1) अणु
		*PrefetchBandwidth = (PDEAndMetaPTEBytesFrame + 2 * MetaRowByte
				+ 2 * PixelPTEBytesPerRow
				+ PrefetchSourceLinesY * SwathWidthY * dml_उच्चमान(BytePerPixelDETY, 1)
				+ PrefetchSourceLinesC * SwathWidthY / 2
						* dml_उच्चमान(BytePerPixelDETC, 2))
				/ (*DestinationLinesForPrefetch * LineTime - *Tno_bw);
		अगर (GPUVMEnable) अणु
			TimeForFetchingMetaPTE =
					dml_max(
							*Tno_bw
									+ (द्विगुन) PDEAndMetaPTEBytesFrame
											/ *PrefetchBandwidth,
							dml_max(
									UrgentExtraLatency
											+ UrgentLatencyPixelDataOnly
													* (PageTableLevels
															- 1),
									LineTime / 4));
		पूर्ण अन्यथा अणु
			अगर (NumberOfCursors > 0 || XFCEnabled)
				TimeForFetchingMetaPTE = LineTime / 4;
			अन्यथा
				TimeForFetchingMetaPTE = 0.0;
		पूर्ण

		अगर ((GPUVMEnable == true || DCCEnable == true)) अणु
			TimeForFetchingRowInVBlank =
					dml_max(
							(MetaRowByte + PixelPTEBytesPerRow)
									/ *PrefetchBandwidth,
							dml_max(
									UrgentLatencyPixelDataOnly,
									dml_max(
											LineTime
													- TimeForFetchingMetaPTE,
											LineTime
													/ 4.0)));
		पूर्ण अन्यथा अणु
			अगर (NumberOfCursors > 0 || XFCEnabled)
				TimeForFetchingRowInVBlank = LineTime - TimeForFetchingMetaPTE;
			अन्यथा
				TimeForFetchingRowInVBlank = 0.0;
		पूर्ण

		*DestinationLinesToRequestVMInVBlank = dml_न्यूनमान(
				4.0 * (TimeForFetchingMetaPTE / LineTime + 0.125),
				1) / 4.0;

		*DestinationLinesToRequestRowInVBlank = dml_न्यूनमान(
				4.0 * (TimeForFetchingRowInVBlank / LineTime + 0.125),
				1) / 4.0;

		LinesToRequestPrefetchPixelData =
				*DestinationLinesForPrefetch
						- ((NumberOfCursors > 0 || GPUVMEnable
								|| DCCEnable) ?
								(*DestinationLinesToRequestVMInVBlank
										+ *DestinationLinesToRequestRowInVBlank) :
								0.0);

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

			*RequiredPrefetchPixDataBW =
					DPPPerPlane
							* ((द्विगुन) PrefetchSourceLinesY
									/ LinesToRequestPrefetchPixelData
									* dml_उच्चमान(
											BytePerPixelDETY,
											1)
									+ (द्विगुन) PrefetchSourceLinesC
											/ LinesToRequestPrefetchPixelData
											* dml_उच्चमान(
													BytePerPixelDETC,
													2)
											/ 2)
							* SwathWidthY / LineTime;
		पूर्ण अन्यथा अणु
			MyError = true;
			*VRatioPrefetchY = 0;
			*VRatioPrefetchC = 0;
			*RequiredPrefetchPixDataBW = 0;
		पूर्ण

	पूर्ण अन्यथा अणु
		MyError = true;
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
		*RequiredPrefetchPixDataBW = 0;
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
		अचिन्हित पूर्णांक VMMPageSize,
		अचिन्हित पूर्णांक PTEBufferSizeInRequestsLuma,
		अचिन्हित पूर्णांक PDEProcessingBufIn64KBReqs,
		अचिन्हित पूर्णांक Pitch,
		अचिन्हित पूर्णांक DCCMetaPitch,
		अचिन्हित पूर्णांक *MacroTileWidth,
		अचिन्हित पूर्णांक *MetaRowByte,
		अचिन्हित पूर्णांक *PixelPTEBytesPerRow,
		bool *PTEBufferSizeNotExceeded,
		अचिन्हित पूर्णांक *dpte_row_height,
		अचिन्हित पूर्णांक *meta_row_height)
अणु
	अचिन्हित पूर्णांक MetaRequestHeight;
	अचिन्हित पूर्णांक MetaRequestWidth;
	अचिन्हित पूर्णांक MetaSurfWidth;
	अचिन्हित पूर्णांक MetaSurfHeight;
	अचिन्हित पूर्णांक MPDEBytesFrame;
	अचिन्हित पूर्णांक MetaPTEBytesFrame;
	अचिन्हित पूर्णांक DCCMetaSurfaceBytes;

	अचिन्हित पूर्णांक MacroTileSizeBytes;
	अचिन्हित पूर्णांक MacroTileHeight;
	अचिन्हित पूर्णांक DPDE0BytesFrame;
	अचिन्हित पूर्णांक ExtraDPDEBytesFrame;
	अचिन्हित पूर्णांक PDEAndMetaPTEBytesFrame;

	अगर (DCCEnable == true) अणु
		MetaRequestHeight = 8 * BlockHeight256Bytes;
		MetaRequestWidth = 8 * BlockWidth256Bytes;
		अगर (ScanDirection == dm_horz) अणु
			*meta_row_height = MetaRequestHeight;
			MetaSurfWidth = dml_उच्चमान((द्विगुन) SwathWidth - 1, MetaRequestWidth)
					+ MetaRequestWidth;
			*MetaRowByte = MetaSurfWidth * MetaRequestHeight * BytePerPixel / 256.0;
		पूर्ण अन्यथा अणु
			*meta_row_height = MetaRequestWidth;
			MetaSurfHeight = dml_उच्चमान((द्विगुन) SwathWidth - 1, MetaRequestHeight)
					+ MetaRequestHeight;
			*MetaRowByte = MetaSurfHeight * MetaRequestWidth * BytePerPixel / 256.0;
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
			MetaPTEBytesFrame = (dml_उच्चमान(
					(द्विगुन) (DCCMetaSurfaceBytes - VMMPageSize)
							/ (8 * VMMPageSize),
					1) + 1) * 64;
			MPDEBytesFrame = 128 * (mode_lib->vba.GPUVMMaxPageTableLevels - 1);
		पूर्ण अन्यथा अणु
			MetaPTEBytesFrame = 0;
			MPDEBytesFrame = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		MetaPTEBytesFrame = 0;
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

	अगर (GPUVMEnable == true && mode_lib->vba.GPUVMMaxPageTableLevels > 1) अणु
		अगर (ScanDirection == dm_horz) अणु
			DPDE0BytesFrame =
					64
							* (dml_उच्चमान(
									((Pitch
											* (dml_उच्चमान(
													ViewportHeight
															- 1,
													MacroTileHeight)
													+ MacroTileHeight)
											* BytePerPixel)
											- MacroTileSizeBytes)
											/ (8
													* 2097152),
									1) + 1);
		पूर्ण अन्यथा अणु
			DPDE0BytesFrame =
					64
							* (dml_उच्चमान(
									((Pitch
											* (dml_उच्चमान(
													(द्विगुन) SwathWidth
															- 1,
													MacroTileHeight)
													+ MacroTileHeight)
											* BytePerPixel)
											- MacroTileSizeBytes)
											/ (8
													* 2097152),
									1) + 1);
		पूर्ण
		ExtraDPDEBytesFrame = 128 * (mode_lib->vba.GPUVMMaxPageTableLevels - 2);
	पूर्ण अन्यथा अणु
		DPDE0BytesFrame = 0;
		ExtraDPDEBytesFrame = 0;
	पूर्ण

	PDEAndMetaPTEBytesFrame = MetaPTEBytesFrame + MPDEBytesFrame + DPDE0BytesFrame
			+ ExtraDPDEBytesFrame;

	अगर (GPUVMEnable == true) अणु
		अचिन्हित पूर्णांक PTERequestSize;
		अचिन्हित पूर्णांक PixelPTEReqHeight;
		अचिन्हित पूर्णांक PixelPTEReqWidth;
		द्विगुन FractionOfPTEReturnDrop;
		अचिन्हित पूर्णांक EffectivePDEProcessingBufIn64KBReqs;

		अगर (SurfaceTiling == dm_sw_linear) अणु
			PixelPTEReqHeight = 1;
			PixelPTEReqWidth = 8.0 * VMMPageSize / BytePerPixel;
			PTERequestSize = 64;
			FractionOfPTEReturnDrop = 0;
		पूर्ण अन्यथा अगर (MacroTileSizeBytes == 4096) अणु
			PixelPTEReqHeight = MacroTileHeight;
			PixelPTEReqWidth = 8 * *MacroTileWidth;
			PTERequestSize = 64;
			अगर (ScanDirection == dm_horz)
				FractionOfPTEReturnDrop = 0;
			अन्यथा
				FractionOfPTEReturnDrop = 7 / 8;
		पूर्ण अन्यथा अगर (VMMPageSize == 4096 && MacroTileSizeBytes > 4096) अणु
			PixelPTEReqHeight = 16 * BlockHeight256Bytes;
			PixelPTEReqWidth = 16 * BlockWidth256Bytes;
			PTERequestSize = 128;
			FractionOfPTEReturnDrop = 0;
		पूर्ण अन्यथा अणु
			PixelPTEReqHeight = MacroTileHeight;
			PixelPTEReqWidth = 8 * *MacroTileWidth;
			PTERequestSize = 64;
			FractionOfPTEReturnDrop = 0;
		पूर्ण

		अगर (SourcePixelFormat == dm_420_8 || SourcePixelFormat == dm_420_10)
			EffectivePDEProcessingBufIn64KBReqs = PDEProcessingBufIn64KBReqs / 2;
		अन्यथा
			EffectivePDEProcessingBufIn64KBReqs = PDEProcessingBufIn64KBReqs;

		अगर (SurfaceTiling == dm_sw_linear) अणु
			*dpte_row_height =
					dml_min(
							128,
							1
									<< (अचिन्हित पूर्णांक) dml_न्यूनमान(
											dml_log2(
													dml_min(
															(द्विगुन) PTEBufferSizeInRequestsLuma
																	* PixelPTEReqWidth,
															EffectivePDEProcessingBufIn64KBReqs
																	* 65536.0
																	/ BytePerPixel)
															/ Pitch),
											1));
			*PixelPTEBytesPerRow = PTERequestSize
					* (dml_उच्चमान(
							(द्विगुन) (Pitch * *dpte_row_height - 1)
									/ PixelPTEReqWidth,
							1) + 1);
		पूर्ण अन्यथा अगर (ScanDirection == dm_horz) अणु
			*dpte_row_height = PixelPTEReqHeight;
			*PixelPTEBytesPerRow = PTERequestSize
					* (dml_उच्चमान(((द्विगुन) SwathWidth - 1) / PixelPTEReqWidth, 1)
							+ 1);
		पूर्ण अन्यथा अणु
			*dpte_row_height = dml_min(PixelPTEReqWidth, *MacroTileWidth);
			*PixelPTEBytesPerRow = PTERequestSize
					* (dml_उच्चमान(
							((द्विगुन) SwathWidth - 1)
									/ PixelPTEReqHeight,
							1) + 1);
		पूर्ण
		अगर (*PixelPTEBytesPerRow * (1 - FractionOfPTEReturnDrop)
				<= 64 * PTEBufferSizeInRequestsLuma) अणु
			*PTEBufferSizeNotExceeded = true;
		पूर्ण अन्यथा अणु
			*PTEBufferSizeNotExceeded = false;
		पूर्ण
	पूर्ण अन्यथा अणु
		*PixelPTEBytesPerRow = 0;
		*PTEBufferSizeNotExceeded = true;
	पूर्ण

	वापस PDEAndMetaPTEBytesFrame;
पूर्ण

अटल व्योम dml20v2_DISPCLKDPPCLKDCFCLKDeepSleepPrefetchParametersWatermarksAndPerक्रमmanceCalculation(
		काष्ठा display_mode_lib *mode_lib)
अणु
	अचिन्हित पूर्णांक j, k;

	mode_lib->vba.WritebackDISPCLK = 0.0;
	mode_lib->vba.DISPCLKWithRamping = 0;
	mode_lib->vba.DISPCLKWithoutRamping = 0;
	mode_lib->vba.GlobalDPPCLK = 0.0;

	// dml_ml->vba.DISPCLK and dml_ml->vba.DPPCLK Calculation
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
			mode_lib->vba.PSCL_THROUGHPUT_LUMA[k] = dml_min(
					mode_lib->vba.MaxDCHUBToPSCLThroughput,
					mode_lib->vba.MaxPSCLToLBThroughput
							* mode_lib->vba.HRatio[k]
							/ dml_उच्चमान(
									mode_lib->vba.htaps[k]
											/ 6.0,
									1));
		पूर्ण अन्यथा अणु
			mode_lib->vba.PSCL_THROUGHPUT_LUMA[k] = dml_min(
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
												/ mode_lib->vba.PSCL_THROUGHPUT_LUMA[k],
										1.0));

		अगर ((mode_lib->vba.htaps[k] > 6 || mode_lib->vba.vtaps[k] > 6)
				&& mode_lib->vba.DPPCLKUsingSingleDPPLuma
						< 2 * mode_lib->vba.PixelClock[k]) अणु
			mode_lib->vba.DPPCLKUsingSingleDPPLuma = 2 * mode_lib->vba.PixelClock[k];
		पूर्ण

		अगर ((mode_lib->vba.SourcePixelFormat[k] != dm_420_8
				&& mode_lib->vba.SourcePixelFormat[k] != dm_420_10)) अणु
			mode_lib->vba.PSCL_THROUGHPUT_CHROMA[k] = 0.0;
			mode_lib->vba.DPPCLKUsingSingleDPP[k] =
					mode_lib->vba.DPPCLKUsingSingleDPPLuma;
		पूर्ण अन्यथा अणु
			अगर (mode_lib->vba.HRatio[k] > 1) अणु
				mode_lib->vba.PSCL_THROUGHPUT_CHROMA[k] =
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
				mode_lib->vba.PSCL_THROUGHPUT_CHROMA[k] = dml_min(
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
													/ mode_lib->vba.PSCL_THROUGHPUT_CHROMA[k],
											1.0));

			अगर ((mode_lib->vba.HTAPsChroma[k] > 6 || mode_lib->vba.VTAPsChroma[k] > 6)
					&& mode_lib->vba.DPPCLKUsingSingleDPPChroma
							< 2 * mode_lib->vba.PixelClock[k]) अणु
				mode_lib->vba.DPPCLKUsingSingleDPPChroma = 2
						* mode_lib->vba.PixelClock[k];
			पूर्ण

			mode_lib->vba.DPPCLKUsingSingleDPP[k] = dml_max(
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
			mode_lib->vba.soc.घड़ी_limits[mode_lib->vba.soc.num_states].dispclk_mhz,
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
		अगर (mode_lib->vba.DPPPerPlane[k] == 0) अणु
			mode_lib->vba.DPPCLK_calculated[k] = 0;
		पूर्ण अन्यथा अणु
			mode_lib->vba.DPPCLK_calculated[k] = mode_lib->vba.DPPCLKUsingSingleDPP[k]
					/ mode_lib->vba.DPPPerPlane[k]
					* (1 + mode_lib->vba.DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100);
		पूर्ण
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

	// Urgent Watermark
	mode_lib->vba.DCCEnabledAnyPlane = false;
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k)
		अगर (mode_lib->vba.DCCEnable[k])
			mode_lib->vba.DCCEnabledAnyPlane = true;

	mode_lib->vba.ReturnBandwidthToDCN = dml_min(
			mode_lib->vba.ReturnBusWidth * mode_lib->vba.DCFCLK,
			mode_lib->vba.FabricAndDRAMBandwidth * 1000)
			* mode_lib->vba.PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelDataOnly / 100;

	mode_lib->vba.ReturnBW = mode_lib->vba.ReturnBandwidthToDCN;
	mode_lib->vba.ReturnBW = adjust_ReturnBW(
			mode_lib,
			mode_lib->vba.ReturnBW,
			mode_lib->vba.DCCEnabledAnyPlane,
			mode_lib->vba.ReturnBandwidthToDCN);

	// Let's करो this calculation again??
	mode_lib->vba.ReturnBandwidthToDCN = dml_min(
			mode_lib->vba.ReturnBusWidth * mode_lib->vba.DCFCLK,
			mode_lib->vba.FabricAndDRAMBandwidth * 1000);
	mode_lib->vba.ReturnBW = adjust_ReturnBW(
			mode_lib,
			mode_lib->vba.ReturnBW,
			mode_lib->vba.DCCEnabledAnyPlane,
			mode_lib->vba.ReturnBandwidthToDCN);

	DTRACE("   dcfclk_mhz         = %f", mode_lib->vba.DCFCLK);
	DTRACE("   return_bw_to_dcn   = %f", mode_lib->vba.ReturnBandwidthToDCN);
	DTRACE("   return_bus_bw      = %f", mode_lib->vba.ReturnBW);

	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		bool MainPlaneDoesODMCombine = false;

		अगर (mode_lib->vba.SourceScan[k] == dm_horz)
			mode_lib->vba.SwathWidthSingleDPPY[k] = mode_lib->vba.ViewportWidth[k];
		अन्यथा
			mode_lib->vba.SwathWidthSingleDPPY[k] = mode_lib->vba.ViewportHeight[k];

		अगर (mode_lib->vba.ODMCombineEnabled[k] == dm_odm_combine_mode_2to1)
			MainPlaneDoesODMCombine = true;
		क्रम (j = 0; j < mode_lib->vba.NumberOfActivePlanes; ++j)
			अगर (mode_lib->vba.BlendingAndTiming[k] == j
					&& mode_lib->vba.ODMCombineEnabled[k] == dm_odm_combine_mode_2to1)
				MainPlaneDoesODMCombine = true;

		अगर (MainPlaneDoesODMCombine == true)
			mode_lib->vba.SwathWidthY[k] = dml_min(
					(द्विगुन) mode_lib->vba.SwathWidthSingleDPPY[k],
					dml_round(
							mode_lib->vba.HActive[k] / 2.0
									* mode_lib->vba.HRatio[k]));
		अन्यथा अणु
			अगर (mode_lib->vba.DPPPerPlane[k] == 0) अणु
				mode_lib->vba.SwathWidthY[k] = 0;
			पूर्ण अन्यथा अणु
				mode_lib->vba.SwathWidthY[k] = mode_lib->vba.SwathWidthSingleDPPY[k]
						/ mode_lib->vba.DPPPerPlane[k];
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		अगर (mode_lib->vba.SourcePixelFormat[k] == dm_444_64) अणु
			mode_lib->vba.BytePerPixelDETY[k] = 8;
			mode_lib->vba.BytePerPixelDETC[k] = 0;
		पूर्ण अन्यथा अगर (mode_lib->vba.SourcePixelFormat[k] == dm_444_32) अणु
			mode_lib->vba.BytePerPixelDETY[k] = 4;
			mode_lib->vba.BytePerPixelDETC[k] = 0;
		पूर्ण अन्यथा अगर (mode_lib->vba.SourcePixelFormat[k] == dm_444_16) अणु
			mode_lib->vba.BytePerPixelDETY[k] = 2;
			mode_lib->vba.BytePerPixelDETC[k] = 0;
		पूर्ण अन्यथा अगर (mode_lib->vba.SourcePixelFormat[k] == dm_444_8) अणु
			mode_lib->vba.BytePerPixelDETY[k] = 1;
			mode_lib->vba.BytePerPixelDETC[k] = 0;
		पूर्ण अन्यथा अगर (mode_lib->vba.SourcePixelFormat[k] == dm_420_8) अणु
			mode_lib->vba.BytePerPixelDETY[k] = 1;
			mode_lib->vba.BytePerPixelDETC[k] = 2;
		पूर्ण अन्यथा अणु // dm_420_10
			mode_lib->vba.BytePerPixelDETY[k] = 4.0 / 3.0;
			mode_lib->vba.BytePerPixelDETC[k] = 8.0 / 3.0;
		पूर्ण
	पूर्ण

	mode_lib->vba.TotalDataReadBandwidth = 0.0;
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		mode_lib->vba.ReadBandwidthPlaneLuma[k] = mode_lib->vba.SwathWidthSingleDPPY[k]
				* dml_उच्चमान(mode_lib->vba.BytePerPixelDETY[k], 1)
				/ (mode_lib->vba.HTotal[k] / mode_lib->vba.PixelClock[k])
				* mode_lib->vba.VRatio[k];
		mode_lib->vba.ReadBandwidthPlaneChroma[k] = mode_lib->vba.SwathWidthSingleDPPY[k]
				/ 2 * dml_उच्चमान(mode_lib->vba.BytePerPixelDETC[k], 2)
				/ (mode_lib->vba.HTotal[k] / mode_lib->vba.PixelClock[k])
				* mode_lib->vba.VRatio[k] / 2;
		DTRACE(
				"   read_bw[%i] = %fBps",
				k,
				mode_lib->vba.ReadBandwidthPlaneLuma[k]
						+ mode_lib->vba.ReadBandwidthPlaneChroma[k]);
		mode_lib->vba.TotalDataReadBandwidth += mode_lib->vba.ReadBandwidthPlaneLuma[k]
				+ mode_lib->vba.ReadBandwidthPlaneChroma[k];
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

	mode_lib->vba.UrgentRoundTripAndOutOfOrderLatency =
			(mode_lib->vba.RoundTripPingLatencyCycles + 32) / mode_lib->vba.DCFCLK
					+ mode_lib->vba.UrgentOutOfOrderReturnPerChannelPixelDataOnly
							* mode_lib->vba.NumberOfChannels
							/ mode_lib->vba.ReturnBW;

	mode_lib->vba.LastPixelOfLineExtraWatermark = 0;
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
			अगर (mode_lib->vba.VRatio[k] <= 1.0)
				mode_lib->vba.DisplayPipeLineDeliveryTimeLuma[k] =
						(द्विगुन) mode_lib->vba.SwathWidthY[k]
								* mode_lib->vba.DPPPerPlane[k]
								/ mode_lib->vba.HRatio[k]
								/ mode_lib->vba.PixelClock[k];
			अन्यथा
				mode_lib->vba.DisplayPipeLineDeliveryTimeLuma[k] =
						(द्विगुन) mode_lib->vba.SwathWidthY[k]
								/ mode_lib->vba.PSCL_THROUGHPUT_LUMA[k]
								/ mode_lib->vba.DPPCLK[k];

			अगर (mode_lib->vba.BytePerPixelDETC[k] == 0)
				mode_lib->vba.DisplayPipeLineDeliveryTimeChroma[k] = 0.0;
			अन्यथा अगर (mode_lib->vba.VRatio[k] / 2.0 <= 1.0)
				mode_lib->vba.DisplayPipeLineDeliveryTimeChroma[k] =
						mode_lib->vba.SwathWidthY[k] / 2.0
								* mode_lib->vba.DPPPerPlane[k]
								/ (mode_lib->vba.HRatio[k] / 2.0)
								/ mode_lib->vba.PixelClock[k];
			अन्यथा
				mode_lib->vba.DisplayPipeLineDeliveryTimeChroma[k] =
						mode_lib->vba.SwathWidthY[k] / 2.0
								/ mode_lib->vba.PSCL_THROUGHPUT_CHROMA[k]
								/ mode_lib->vba.DPPCLK[k];
		पूर्ण

	mode_lib->vba.UrgentExtraLatency = mode_lib->vba.UrgentRoundTripAndOutOfOrderLatency
			+ (mode_lib->vba.TotalActiveDPP * mode_lib->vba.PixelChunkSizeInKByte
					+ mode_lib->vba.TotalDCCActiveDPP
							* mode_lib->vba.MetaChunkSize) * 1024.0
					/ mode_lib->vba.ReturnBW;

	अगर (mode_lib->vba.GPUVMEnable)
		mode_lib->vba.UrgentExtraLatency += mode_lib->vba.TotalActiveDPP
				* mode_lib->vba.PTEGroupSize / mode_lib->vba.ReturnBW;

	mode_lib->vba.UrgentWatermark = mode_lib->vba.UrgentLatencyPixelDataOnly
			+ mode_lib->vba.LastPixelOfLineExtraWatermark
			+ mode_lib->vba.UrgentExtraLatency;

	DTRACE("   urgent_extra_latency = %fus", mode_lib->vba.UrgentExtraLatency);
	DTRACE("   wm_urgent = %fus", mode_lib->vba.UrgentWatermark);

	mode_lib->vba.UrgentLatency = mode_lib->vba.UrgentLatencyPixelDataOnly;

	mode_lib->vba.TotalActiveWriteback = 0;
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		अगर (mode_lib->vba.WritebackEnable[k])
			mode_lib->vba.TotalActiveWriteback = mode_lib->vba.TotalActiveWriteback + mode_lib->vba.ActiveWritebacksPerPlane[k];
	पूर्ण

	अगर (mode_lib->vba.TotalActiveWriteback <= 1)
		mode_lib->vba.WritebackUrgentWatermark = mode_lib->vba.WritebackLatency;
	अन्यथा
		mode_lib->vba.WritebackUrgentWatermark = mode_lib->vba.WritebackLatency
				+ mode_lib->vba.WritebackChunkSize * 1024.0 / 32
						/ mode_lib->vba.SOCCLK;

	DTRACE("   wm_wb_urgent = %fus", mode_lib->vba.WritebackUrgentWatermark);

	// NB P-State/DRAM Clock Change Watermark
	mode_lib->vba.DRAMClockChangeWatermark = mode_lib->vba.DRAMClockChangeLatency
			+ mode_lib->vba.UrgentWatermark;

	DTRACE("   wm_pstate_change = %fus", mode_lib->vba.DRAMClockChangeWatermark);

	DTRACE("   calculating wb pstate watermark");
	DTRACE("      total wb outputs %d", mode_lib->vba.TotalActiveWriteback);
	DTRACE("      socclk frequency %f Mhz", mode_lib->vba.SOCCLK);

	अगर (mode_lib->vba.TotalActiveWriteback <= 1)
		mode_lib->vba.WritebackDRAMClockChangeWatermark =
				mode_lib->vba.DRAMClockChangeLatency
						+ mode_lib->vba.WritebackLatency;
	अन्यथा
		mode_lib->vba.WritebackDRAMClockChangeWatermark =
				mode_lib->vba.DRAMClockChangeLatency
						+ mode_lib->vba.WritebackLatency
						+ mode_lib->vba.WritebackChunkSize * 1024.0 / 32
								/ mode_lib->vba.SOCCLK;

	DTRACE("   wm_wb_pstate %fus", mode_lib->vba.WritebackDRAMClockChangeWatermark);

	// Stutter Efficiency
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		mode_lib->vba.LinesInDETY[k] = mode_lib->vba.DETBufferSizeY[k]
				/ mode_lib->vba.BytePerPixelDETY[k] / mode_lib->vba.SwathWidthY[k];
		mode_lib->vba.LinesInDETYRoundedDownToSwath[k] = dml_न्यूनमान(
				mode_lib->vba.LinesInDETY[k],
				mode_lib->vba.SwathHeightY[k]);
		mode_lib->vba.FullDETBufferingTimeY[k] =
				mode_lib->vba.LinesInDETYRoundedDownToSwath[k]
						* (mode_lib->vba.HTotal[k]
								/ mode_lib->vba.PixelClock[k])
						/ mode_lib->vba.VRatio[k];
		अगर (mode_lib->vba.BytePerPixelDETC[k] > 0) अणु
			mode_lib->vba.LinesInDETC[k] = mode_lib->vba.DETBufferSizeC[k]
					/ mode_lib->vba.BytePerPixelDETC[k]
					/ (mode_lib->vba.SwathWidthY[k] / 2);
			mode_lib->vba.LinesInDETCRoundedDownToSwath[k] = dml_न्यूनमान(
					mode_lib->vba.LinesInDETC[k],
					mode_lib->vba.SwathHeightC[k]);
			mode_lib->vba.FullDETBufferingTimeC[k] =
					mode_lib->vba.LinesInDETCRoundedDownToSwath[k]
							* (mode_lib->vba.HTotal[k]
									/ mode_lib->vba.PixelClock[k])
							/ (mode_lib->vba.VRatio[k] / 2);
		पूर्ण अन्यथा अणु
			mode_lib->vba.LinesInDETC[k] = 0;
			mode_lib->vba.LinesInDETCRoundedDownToSwath[k] = 0;
			mode_lib->vba.FullDETBufferingTimeC[k] = 999999;
		पूर्ण
	पूर्ण

	mode_lib->vba.MinFullDETBufferingTime = 999999.0;
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		अगर (mode_lib->vba.FullDETBufferingTimeY[k]
				< mode_lib->vba.MinFullDETBufferingTime) अणु
			mode_lib->vba.MinFullDETBufferingTime =
					mode_lib->vba.FullDETBufferingTimeY[k];
			mode_lib->vba.FrameTimeForMinFullDETBufferingTime =
					(द्विगुन) mode_lib->vba.VTotal[k] * mode_lib->vba.HTotal[k]
							/ mode_lib->vba.PixelClock[k];
		पूर्ण
		अगर (mode_lib->vba.FullDETBufferingTimeC[k]
				< mode_lib->vba.MinFullDETBufferingTime) अणु
			mode_lib->vba.MinFullDETBufferingTime =
					mode_lib->vba.FullDETBufferingTimeC[k];
			mode_lib->vba.FrameTimeForMinFullDETBufferingTime =
					(द्विगुन) mode_lib->vba.VTotal[k] * mode_lib->vba.HTotal[k]
							/ mode_lib->vba.PixelClock[k];
		पूर्ण
	पूर्ण

	mode_lib->vba.AverageReadBandwidthGBytePerSecond = 0.0;
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		अगर (mode_lib->vba.DCCEnable[k]) अणु
			mode_lib->vba.AverageReadBandwidthGBytePerSecond =
					mode_lib->vba.AverageReadBandwidthGBytePerSecond
							+ mode_lib->vba.ReadBandwidthPlaneLuma[k]
									/ mode_lib->vba.DCCRate[k]
									/ 1000
							+ mode_lib->vba.ReadBandwidthPlaneChroma[k]
									/ mode_lib->vba.DCCRate[k]
									/ 1000;
		पूर्ण अन्यथा अणु
			mode_lib->vba.AverageReadBandwidthGBytePerSecond =
					mode_lib->vba.AverageReadBandwidthGBytePerSecond
							+ mode_lib->vba.ReadBandwidthPlaneLuma[k]
									/ 1000
							+ mode_lib->vba.ReadBandwidthPlaneChroma[k]
									/ 1000;
		पूर्ण
		अगर (mode_lib->vba.DCCEnable[k]) अणु
			mode_lib->vba.AverageReadBandwidthGBytePerSecond =
					mode_lib->vba.AverageReadBandwidthGBytePerSecond
							+ mode_lib->vba.ReadBandwidthPlaneLuma[k]
									/ 1000 / 256
							+ mode_lib->vba.ReadBandwidthPlaneChroma[k]
									/ 1000 / 256;
		पूर्ण
		अगर (mode_lib->vba.GPUVMEnable) अणु
			mode_lib->vba.AverageReadBandwidthGBytePerSecond =
					mode_lib->vba.AverageReadBandwidthGBytePerSecond
							+ mode_lib->vba.ReadBandwidthPlaneLuma[k]
									/ 1000 / 512
							+ mode_lib->vba.ReadBandwidthPlaneChroma[k]
									/ 1000 / 512;
		पूर्ण
	पूर्ण

	mode_lib->vba.PartOfBurstThatFitsInROB =
			dml_min(
					mode_lib->vba.MinFullDETBufferingTime
							* mode_lib->vba.TotalDataReadBandwidth,
					mode_lib->vba.ROBBufferSizeInKByte * 1024
							* mode_lib->vba.TotalDataReadBandwidth
							/ (mode_lib->vba.AverageReadBandwidthGBytePerSecond
									* 1000));
	mode_lib->vba.StutterBurstTime = mode_lib->vba.PartOfBurstThatFitsInROB
			* (mode_lib->vba.AverageReadBandwidthGBytePerSecond * 1000)
			/ mode_lib->vba.TotalDataReadBandwidth / mode_lib->vba.ReturnBW
			+ (mode_lib->vba.MinFullDETBufferingTime
					* mode_lib->vba.TotalDataReadBandwidth
					- mode_lib->vba.PartOfBurstThatFitsInROB)
					/ (mode_lib->vba.DCFCLK * 64);
	अगर (mode_lib->vba.TotalActiveWriteback == 0) अणु
		mode_lib->vba.StutterEfficiencyNotIncludingVBlank = (1
				- (mode_lib->vba.SRExitTime + mode_lib->vba.StutterBurstTime)
						/ mode_lib->vba.MinFullDETBufferingTime) * 100;
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

	// dml_ml->vba.DCFCLK Deep Sleep
	mode_lib->vba.DCFCLKDeepSleep = 8.0;

	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; k++) अणु
		अगर (mode_lib->vba.BytePerPixelDETC[k] > 0) अणु
			mode_lib->vba.DCFCLKDeepSleepPerPlane[k] =
					dml_max(
							1.1 * mode_lib->vba.SwathWidthY[k]
									* dml_उच्चमान(
											mode_lib->vba.BytePerPixelDETY[k],
											1) / 32
									/ mode_lib->vba.DisplayPipeLineDeliveryTimeLuma[k],
							1.1 * mode_lib->vba.SwathWidthY[k] / 2.0
									* dml_उच्चमान(
											mode_lib->vba.BytePerPixelDETC[k],
											2) / 32
									/ mode_lib->vba.DisplayPipeLineDeliveryTimeChroma[k]);
		पूर्ण अन्यथा
			mode_lib->vba.DCFCLKDeepSleepPerPlane[k] = 1.1 * mode_lib->vba.SwathWidthY[k]
					* dml_उच्चमान(mode_lib->vba.BytePerPixelDETY[k], 1) / 64.0
					/ mode_lib->vba.DisplayPipeLineDeliveryTimeLuma[k];
		mode_lib->vba.DCFCLKDeepSleepPerPlane[k] = dml_max(
				mode_lib->vba.DCFCLKDeepSleepPerPlane[k],
				mode_lib->vba.PixelClock[k] / 16.0);
		mode_lib->vba.DCFCLKDeepSleep = dml_max(
				mode_lib->vba.DCFCLKDeepSleep,
				mode_lib->vba.DCFCLKDeepSleepPerPlane[k]);

		DTRACE(
				"   dcfclk_deepsleep_per_plane[%i] = %fMHz",
				k,
				mode_lib->vba.DCFCLKDeepSleepPerPlane[k]);
	पूर्ण

	DTRACE("   dcfclk_deepsleep_mhz = %fMHz", mode_lib->vba.DCFCLKDeepSleep);

	// Stutter Watermark
	mode_lib->vba.StutterExitWatermark = mode_lib->vba.SRExitTime
			+ mode_lib->vba.LastPixelOfLineExtraWatermark
			+ mode_lib->vba.UrgentExtraLatency + 10 / mode_lib->vba.DCFCLKDeepSleep;
	mode_lib->vba.StutterEnterPlusExitWatermark = mode_lib->vba.SREnterPlusExitTime
			+ mode_lib->vba.LastPixelOfLineExtraWatermark
			+ mode_lib->vba.UrgentExtraLatency;

	DTRACE("   wm_cstate_exit       = %fus", mode_lib->vba.StutterExitWatermark);
	DTRACE("   wm_cstate_enter_exit = %fus", mode_lib->vba.StutterEnterPlusExitWatermark);

	// Urgent Latency Supported
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		mode_lib->vba.EffectiveDETPlusLBLinesLuma =
				dml_न्यूनमान(
						mode_lib->vba.LinesInDETY[k]
								+ dml_min(
										mode_lib->vba.LinesInDETY[k]
												* mode_lib->vba.DPPCLK[k]
												* mode_lib->vba.BytePerPixelDETY[k]
												* mode_lib->vba.PSCL_THROUGHPUT_LUMA[k]
												/ (mode_lib->vba.ReturnBW
														/ mode_lib->vba.DPPPerPlane[k]),
										(द्विगुन) mode_lib->vba.EffectiveLBLatencyHidingSourceLinesLuma),
						mode_lib->vba.SwathHeightY[k]);

		mode_lib->vba.UrgentLatencySupportUsLuma = mode_lib->vba.EffectiveDETPlusLBLinesLuma
				* (mode_lib->vba.HTotal[k] / mode_lib->vba.PixelClock[k])
				/ mode_lib->vba.VRatio[k]
				- mode_lib->vba.EffectiveDETPlusLBLinesLuma
						* mode_lib->vba.SwathWidthY[k]
						* mode_lib->vba.BytePerPixelDETY[k]
						/ (mode_lib->vba.ReturnBW
								/ mode_lib->vba.DPPPerPlane[k]);

		अगर (mode_lib->vba.BytePerPixelDETC[k] > 0) अणु
			mode_lib->vba.EffectiveDETPlusLBLinesChroma =
					dml_न्यूनमान(
							mode_lib->vba.LinesInDETC[k]
									+ dml_min(
											mode_lib->vba.LinesInDETC[k]
													* mode_lib->vba.DPPCLK[k]
													* mode_lib->vba.BytePerPixelDETC[k]
													* mode_lib->vba.PSCL_THROUGHPUT_CHROMA[k]
													/ (mode_lib->vba.ReturnBW
															/ mode_lib->vba.DPPPerPlane[k]),
											(द्विगुन) mode_lib->vba.EffectiveLBLatencyHidingSourceLinesChroma),
							mode_lib->vba.SwathHeightC[k]);
			mode_lib->vba.UrgentLatencySupportUsChroma =
					mode_lib->vba.EffectiveDETPlusLBLinesChroma
							* (mode_lib->vba.HTotal[k]
									/ mode_lib->vba.PixelClock[k])
							/ (mode_lib->vba.VRatio[k] / 2)
							- mode_lib->vba.EffectiveDETPlusLBLinesChroma
									* (mode_lib->vba.SwathWidthY[k]
											/ 2)
									* mode_lib->vba.BytePerPixelDETC[k]
									/ (mode_lib->vba.ReturnBW
											/ mode_lib->vba.DPPPerPlane[k]);
			mode_lib->vba.UrgentLatencySupportUs[k] = dml_min(
					mode_lib->vba.UrgentLatencySupportUsLuma,
					mode_lib->vba.UrgentLatencySupportUsChroma);
		पूर्ण अन्यथा अणु
			mode_lib->vba.UrgentLatencySupportUs[k] =
					mode_lib->vba.UrgentLatencySupportUsLuma;
		पूर्ण
	पूर्ण

	mode_lib->vba.MinUrgentLatencySupportUs = 999999;
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		mode_lib->vba.MinUrgentLatencySupportUs = dml_min(
				mode_lib->vba.MinUrgentLatencySupportUs,
				mode_lib->vba.UrgentLatencySupportUs[k]);
	पूर्ण

	// Non-Urgent Latency Tolerance
	mode_lib->vba.NonUrgentLatencyTolerance = mode_lib->vba.MinUrgentLatencySupportUs
			- mode_lib->vba.UrgentWatermark;

	// DSCCLK
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		अगर ((mode_lib->vba.BlendingAndTiming[k] != k) || !mode_lib->vba.DSCEnabled[k]) अणु
			mode_lib->vba.DSCCLK_calculated[k] = 0.0;
		पूर्ण अन्यथा अणु
			अगर (mode_lib->vba.OutputFormat[k] == dm_420
					|| mode_lib->vba.OutputFormat[k] == dm_n422)
				mode_lib->vba.DSCFormatFactor = 2;
			अन्यथा
				mode_lib->vba.DSCFormatFactor = 1;
			अगर (mode_lib->vba.ODMCombineEnabled[k])
				mode_lib->vba.DSCCLK_calculated[k] =
						mode_lib->vba.PixelClockBackEnd[k] / 6
								/ mode_lib->vba.DSCFormatFactor
								/ (1
										- mode_lib->vba.DISPCLKDPPCLKDSCCLKDownSpपढ़ोing
												/ 100);
			अन्यथा
				mode_lib->vba.DSCCLK_calculated[k] =
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
				mode_lib->vba.DSCDelay[k] =
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
				mode_lib->vba.DSCDelay[k] =
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
			mode_lib->vba.DSCDelay[k] = mode_lib->vba.DSCDelay[k]
					* mode_lib->vba.PixelClock[k]
					/ mode_lib->vba.PixelClockBackEnd[k];
		पूर्ण अन्यथा अणु
			mode_lib->vba.DSCDelay[k] = 0;
		पूर्ण
	पूर्ण

	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k)
		क्रम (j = 0; j < mode_lib->vba.NumberOfActivePlanes; ++j) // NumberOfPlanes
			अगर (j != k && mode_lib->vba.BlendingAndTiming[k] == j
					&& mode_lib->vba.DSCEnabled[j])
				mode_lib->vba.DSCDelay[k] = mode_lib->vba.DSCDelay[j];

	// Prefetch
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		अचिन्हित पूर्णांक PDEAndMetaPTEBytesFrameY;
		अचिन्हित पूर्णांक PixelPTEBytesPerRowY;
		अचिन्हित पूर्णांक MetaRowByteY;
		अचिन्हित पूर्णांक MetaRowByteC;
		अचिन्हित पूर्णांक PDEAndMetaPTEBytesFrameC;
		अचिन्हित पूर्णांक PixelPTEBytesPerRowC;

		Calculate256BBlockSizes(
				mode_lib->vba.SourcePixelFormat[k],
				mode_lib->vba.SurfaceTiling[k],
				dml_उच्चमान(mode_lib->vba.BytePerPixelDETY[k], 1),
				dml_उच्चमान(mode_lib->vba.BytePerPixelDETC[k], 2),
				&mode_lib->vba.BlockHeight256BytesY[k],
				&mode_lib->vba.BlockHeight256BytesC[k],
				&mode_lib->vba.BlockWidth256BytesY[k],
				&mode_lib->vba.BlockWidth256BytesC[k]);
		PDEAndMetaPTEBytesFrameY = CalculateVMAndRowBytes(
				mode_lib,
				mode_lib->vba.DCCEnable[k],
				mode_lib->vba.BlockHeight256BytesY[k],
				mode_lib->vba.BlockWidth256BytesY[k],
				mode_lib->vba.SourcePixelFormat[k],
				mode_lib->vba.SurfaceTiling[k],
				dml_उच्चमान(mode_lib->vba.BytePerPixelDETY[k], 1),
				mode_lib->vba.SourceScan[k],
				mode_lib->vba.ViewportWidth[k],
				mode_lib->vba.ViewportHeight[k],
				mode_lib->vba.SwathWidthY[k],
				mode_lib->vba.GPUVMEnable,
				mode_lib->vba.VMMPageSize,
				mode_lib->vba.PTEBufferSizeInRequestsLuma,
				mode_lib->vba.PDEProcessingBufIn64KBReqs,
				mode_lib->vba.PitchY[k],
				mode_lib->vba.DCCMetaPitchY[k],
				&mode_lib->vba.MacroTileWidthY[k],
				&MetaRowByteY,
				&PixelPTEBytesPerRowY,
				&mode_lib->vba.PTEBufferSizeNotExceeded[mode_lib->vba.VoltageLevel][0],
				&mode_lib->vba.dpte_row_height[k],
				&mode_lib->vba.meta_row_height[k]);
		mode_lib->vba.PrefetchSourceLinesY[k] = CalculatePrefetchSourceLines(
				mode_lib,
				mode_lib->vba.VRatio[k],
				mode_lib->vba.vtaps[k],
				mode_lib->vba.Interlace[k],
				mode_lib->vba.ProgressiveToInterlaceUnitInOPP,
				mode_lib->vba.SwathHeightY[k],
				mode_lib->vba.ViewportYStartY[k],
				&mode_lib->vba.VInitPreFillY[k],
				&mode_lib->vba.MaxNumSwathY[k]);

		अगर ((mode_lib->vba.SourcePixelFormat[k] != dm_444_64
				&& mode_lib->vba.SourcePixelFormat[k] != dm_444_32
				&& mode_lib->vba.SourcePixelFormat[k] != dm_444_16
				&& mode_lib->vba.SourcePixelFormat[k] != dm_444_8)) अणु
			PDEAndMetaPTEBytesFrameC =
					CalculateVMAndRowBytes(
							mode_lib,
							mode_lib->vba.DCCEnable[k],
							mode_lib->vba.BlockHeight256BytesC[k],
							mode_lib->vba.BlockWidth256BytesC[k],
							mode_lib->vba.SourcePixelFormat[k],
							mode_lib->vba.SurfaceTiling[k],
							dml_उच्चमान(
									mode_lib->vba.BytePerPixelDETC[k],
									2),
							mode_lib->vba.SourceScan[k],
							mode_lib->vba.ViewportWidth[k] / 2,
							mode_lib->vba.ViewportHeight[k] / 2,
							mode_lib->vba.SwathWidthY[k] / 2,
							mode_lib->vba.GPUVMEnable,
							mode_lib->vba.VMMPageSize,
							mode_lib->vba.PTEBufferSizeInRequestsLuma,
							mode_lib->vba.PDEProcessingBufIn64KBReqs,
							mode_lib->vba.PitchC[k],
							0,
							&mode_lib->vba.MacroTileWidthC[k],
							&MetaRowByteC,
							&PixelPTEBytesPerRowC,
							&mode_lib->vba.PTEBufferSizeNotExceeded[mode_lib->vba.VoltageLevel][0],
							&mode_lib->vba.dpte_row_height_chroma[k],
							&mode_lib->vba.meta_row_height_chroma[k]);
			mode_lib->vba.PrefetchSourceLinesC[k] = CalculatePrefetchSourceLines(
					mode_lib,
					mode_lib->vba.VRatio[k] / 2,
					mode_lib->vba.VTAPsChroma[k],
					mode_lib->vba.Interlace[k],
					mode_lib->vba.ProgressiveToInterlaceUnitInOPP,
					mode_lib->vba.SwathHeightC[k],
					mode_lib->vba.ViewportYStartC[k],
					&mode_lib->vba.VInitPreFillC[k],
					&mode_lib->vba.MaxNumSwathC[k]);
		पूर्ण अन्यथा अणु
			PixelPTEBytesPerRowC = 0;
			PDEAndMetaPTEBytesFrameC = 0;
			MetaRowByteC = 0;
			mode_lib->vba.MaxNumSwathC[k] = 0;
			mode_lib->vba.PrefetchSourceLinesC[k] = 0;
		पूर्ण

		mode_lib->vba.PixelPTEBytesPerRow[k] = PixelPTEBytesPerRowY + PixelPTEBytesPerRowC;
		mode_lib->vba.PDEAndMetaPTEBytesFrame[k] = PDEAndMetaPTEBytesFrameY
				+ PDEAndMetaPTEBytesFrameC;
		mode_lib->vba.MetaRowByte[k] = MetaRowByteY + MetaRowByteC;

		CalculateActiveRowBandwidth(
				mode_lib->vba.GPUVMEnable,
				mode_lib->vba.SourcePixelFormat[k],
				mode_lib->vba.VRatio[k],
				mode_lib->vba.DCCEnable[k],
				mode_lib->vba.HTotal[k] / mode_lib->vba.PixelClock[k],
				MetaRowByteY,
				MetaRowByteC,
				mode_lib->vba.meta_row_height[k],
				mode_lib->vba.meta_row_height_chroma[k],
				PixelPTEBytesPerRowY,
				PixelPTEBytesPerRowC,
				mode_lib->vba.dpte_row_height[k],
				mode_lib->vba.dpte_row_height_chroma[k],
				&mode_lib->vba.meta_row_bw[k],
				&mode_lib->vba.dpte_row_bw[k],
				&mode_lib->vba.qual_row_bw[k]);
	पूर्ण

	mode_lib->vba.TCalc = 24.0 / mode_lib->vba.DCFCLKDeepSleep;

	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		अगर (mode_lib->vba.BlendingAndTiming[k] == k) अणु
			अगर (mode_lib->vba.WritebackEnable[k] == true) अणु
				mode_lib->vba.WritebackDelay[mode_lib->vba.VoltageLevel][k] =
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
				mode_lib->vba.WritebackDelay[mode_lib->vba.VoltageLevel][k] = 0;
			क्रम (j = 0; j < mode_lib->vba.NumberOfActivePlanes; ++j) अणु
				अगर (mode_lib->vba.BlendingAndTiming[j] == k
						&& mode_lib->vba.WritebackEnable[j] == true) अणु
					mode_lib->vba.WritebackDelay[mode_lib->vba.VoltageLevel][k] =
							dml_max(
									mode_lib->vba.WritebackDelay[mode_lib->vba.VoltageLevel][k],
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
				mode_lib->vba.WritebackDelay[mode_lib->vba.VoltageLevel][k] =
						mode_lib->vba.WritebackDelay[mode_lib->vba.VoltageLevel][j];

	mode_lib->vba.VStartupLines = 13;
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		mode_lib->vba.MaxVStartupLines[k] =
				mode_lib->vba.VTotal[k] - mode_lib->vba.VActive[k]
						- dml_max(
								1.0,
								dml_उच्चमान(
										mode_lib->vba.WritebackDelay[mode_lib->vba.VoltageLevel][k]
												/ (mode_lib->vba.HTotal[k]
														/ mode_lib->vba.PixelClock[k]),
										1));
	पूर्ण

	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k)
		mode_lib->vba.MaximumMaxVStartupLines = dml_max(
				mode_lib->vba.MaximumMaxVStartupLines,
				mode_lib->vba.MaxVStartupLines[k]);

	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		mode_lib->vba.cursor_bw[k] = 0.0;
		क्रम (j = 0; j < mode_lib->vba.NumberOfCursors[k]; ++j)
			mode_lib->vba.cursor_bw[k] += mode_lib->vba.CursorWidth[k][j]
					* mode_lib->vba.CursorBPP[k][j] / 8.0
					/ (mode_lib->vba.HTotal[k] / mode_lib->vba.PixelClock[k])
					* mode_lib->vba.VRatio[k];
	पूर्ण

	करो अणु
		द्विगुन MaxTotalRDBandwidth = 0;
		bool DestinationLineTimesForPrefetchLessThan2 = false;
		bool VRatioPrefetchMoreThan4 = false;
		bool prefetch_vm_bw_valid = true;
		bool prefetch_row_bw_valid = true;
		द्विगुन TWait = CalculateTWait(
				mode_lib->vba.PrefetchMode[mode_lib->vba.VoltageLevel][mode_lib->vba.maxMpcComb],
				mode_lib->vba.DRAMClockChangeLatency,
				mode_lib->vba.UrgentLatencyPixelDataOnly,
				mode_lib->vba.SREnterPlusExitTime);

		क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
			अगर (mode_lib->vba.XFCEnabled[k] == true) अणु
				mode_lib->vba.XFCRemoteSurfaceFlipDelay =
						CalculateRemoteSurfaceFlipDelay(
								mode_lib,
								mode_lib->vba.VRatio[k],
								mode_lib->vba.SwathWidthY[k],
								dml_उच्चमान(
										mode_lib->vba.BytePerPixelDETY[k],
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

			CalculateDelayAfterScaler(mode_lib, mode_lib->vba.ReturnBW, mode_lib->vba.ReadBandwidthPlaneLuma[k], mode_lib->vba.ReadBandwidthPlaneChroma[k], mode_lib->vba.TotalDataReadBandwidth,
					mode_lib->vba.DisplayPipeLineDeliveryTimeLuma[k], mode_lib->vba.DisplayPipeLineDeliveryTimeChroma[k],
					mode_lib->vba.DPPCLK[k], mode_lib->vba.DISPCLK, mode_lib->vba.PixelClock[k], mode_lib->vba.DSCDelay[k], mode_lib->vba.DPPPerPlane[k], mode_lib->vba.ScalerEnabled[k], mode_lib->vba.NumberOfCursors[k],
					mode_lib->vba.DPPCLKDelaySubtotal, mode_lib->vba.DPPCLKDelaySCL, mode_lib->vba.DPPCLKDelaySCLLBOnly, mode_lib->vba.DPPCLKDelayCNVCFormater, mode_lib->vba.DPPCLKDelayCNVCCursor, mode_lib->vba.DISPCLKDelaySubtotal,
					mode_lib->vba.SwathWidthY[k] / mode_lib->vba.HRatio[k], mode_lib->vba.OutputFormat[k], mode_lib->vba.HTotal[k],
					mode_lib->vba.SwathWidthSingleDPPY[k], mode_lib->vba.BytePerPixelDETY[k], mode_lib->vba.BytePerPixelDETC[k], mode_lib->vba.SwathHeightY[k], mode_lib->vba.SwathHeightC[k], mode_lib->vba.Interlace[k],
					mode_lib->vba.ProgressiveToInterlaceUnitInOPP, &mode_lib->vba.DSTXAfterScaler[k], &mode_lib->vba.DSTYAfterScaler[k]);

			mode_lib->vba.ErrorResult[k] =
					CalculatePrefetchSchedule(
							mode_lib,
							mode_lib->vba.DPPCLK[k],
							mode_lib->vba.DISPCLK,
							mode_lib->vba.PixelClock[k],
							mode_lib->vba.DCFCLKDeepSleep,
							mode_lib->vba.DPPPerPlane[k],
							mode_lib->vba.NumberOfCursors[k],
							mode_lib->vba.VTotal[k]
									- mode_lib->vba.VActive[k],
							mode_lib->vba.HTotal[k],
							mode_lib->vba.MaxInterDCNTileRepeaters,
							dml_min(
									mode_lib->vba.VStartupLines,
									mode_lib->vba.MaxVStartupLines[k]),
							mode_lib->vba.GPUVMMaxPageTableLevels,
							mode_lib->vba.GPUVMEnable,
							mode_lib->vba.DynamicMetadataEnable[k],
							mode_lib->vba.DynamicMetadataLinesBeक्रमeActiveRequired[k],
							mode_lib->vba.DynamicMetadataTransmittedBytes[k],
							mode_lib->vba.DCCEnable[k],
							mode_lib->vba.UrgentLatencyPixelDataOnly,
							mode_lib->vba.UrgentExtraLatency,
							mode_lib->vba.TCalc,
							mode_lib->vba.PDEAndMetaPTEBytesFrame[k],
							mode_lib->vba.MetaRowByte[k],
							mode_lib->vba.PixelPTEBytesPerRow[k],
							mode_lib->vba.PrefetchSourceLinesY[k],
							mode_lib->vba.SwathWidthY[k],
							mode_lib->vba.BytePerPixelDETY[k],
							mode_lib->vba.VInitPreFillY[k],
							mode_lib->vba.MaxNumSwathY[k],
							mode_lib->vba.PrefetchSourceLinesC[k],
							mode_lib->vba.BytePerPixelDETC[k],
							mode_lib->vba.VInitPreFillC[k],
							mode_lib->vba.MaxNumSwathC[k],
							mode_lib->vba.SwathHeightY[k],
							mode_lib->vba.SwathHeightC[k],
							TWait,
							mode_lib->vba.XFCEnabled[k],
							mode_lib->vba.XFCRemoteSurfaceFlipDelay,
							mode_lib->vba.Interlace[k],
							mode_lib->vba.ProgressiveToInterlaceUnitInOPP,
							mode_lib->vba.DSTXAfterScaler[k],
							mode_lib->vba.DSTYAfterScaler[k],
							&mode_lib->vba.DestinationLinesForPrefetch[k],
							&mode_lib->vba.PrefetchBandwidth[k],
							&mode_lib->vba.DestinationLinesToRequestVMInVBlank[k],
							&mode_lib->vba.DestinationLinesToRequestRowInVBlank[k],
							&mode_lib->vba.VRatioPrefetchY[k],
							&mode_lib->vba.VRatioPrefetchC[k],
							&mode_lib->vba.RequiredPrefetchPixDataBWLuma[k],
							&mode_lib->vba.Tno_bw[k],
							&mode_lib->vba.VUpdateOffsetPix[k],
							&mode_lib->vba.VUpdateWidthPix[k],
							&mode_lib->vba.VReadyOffsetPix[k]);

			अगर (mode_lib->vba.BlendingAndTiming[k] == k) अणु
				mode_lib->vba.VStartup[k] = dml_min(
						mode_lib->vba.VStartupLines,
						mode_lib->vba.MaxVStartupLines[k]);
				अगर (mode_lib->vba.VStartupRequiredWhenNotEnoughTimeForDynamicMetadata
						!= 0) अणु
					mode_lib->vba.VStartup[k] =
							mode_lib->vba.VStartupRequiredWhenNotEnoughTimeForDynamicMetadata;
				पूर्ण
			पूर्ण अन्यथा अणु
				mode_lib->vba.VStartup[k] =
						dml_min(
								mode_lib->vba.VStartupLines,
								mode_lib->vba.MaxVStartupLines[mode_lib->vba.BlendingAndTiming[k]]);
			पूर्ण
		पूर्ण

		क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु

			अगर (mode_lib->vba.PDEAndMetaPTEBytesFrame[k] == 0)
				mode_lib->vba.prefetch_vm_bw[k] = 0;
			अन्यथा अगर (mode_lib->vba.DestinationLinesToRequestVMInVBlank[k] > 0) अणु
				mode_lib->vba.prefetch_vm_bw[k] =
						(द्विगुन) mode_lib->vba.PDEAndMetaPTEBytesFrame[k]
								/ (mode_lib->vba.DestinationLinesToRequestVMInVBlank[k]
										* mode_lib->vba.HTotal[k]
										/ mode_lib->vba.PixelClock[k]);
			पूर्ण अन्यथा अणु
				mode_lib->vba.prefetch_vm_bw[k] = 0;
				prefetch_vm_bw_valid = false;
			पूर्ण
			अगर (mode_lib->vba.MetaRowByte[k] + mode_lib->vba.PixelPTEBytesPerRow[k]
					== 0)
				mode_lib->vba.prefetch_row_bw[k] = 0;
			अन्यथा अगर (mode_lib->vba.DestinationLinesToRequestRowInVBlank[k] > 0) अणु
				mode_lib->vba.prefetch_row_bw[k] =
						(द्विगुन) (mode_lib->vba.MetaRowByte[k]
								+ mode_lib->vba.PixelPTEBytesPerRow[k])
								/ (mode_lib->vba.DestinationLinesToRequestRowInVBlank[k]
										* mode_lib->vba.HTotal[k]
										/ mode_lib->vba.PixelClock[k]);
			पूर्ण अन्यथा अणु
				mode_lib->vba.prefetch_row_bw[k] = 0;
				prefetch_row_bw_valid = false;
			पूर्ण

			MaxTotalRDBandwidth =
					MaxTotalRDBandwidth + mode_lib->vba.cursor_bw[k]
							+ dml_max(
									mode_lib->vba.prefetch_vm_bw[k],
									dml_max(
											mode_lib->vba.prefetch_row_bw[k],
											dml_max(
													mode_lib->vba.ReadBandwidthPlaneLuma[k]
															+ mode_lib->vba.ReadBandwidthPlaneChroma[k],
													mode_lib->vba.RequiredPrefetchPixDataBWLuma[k])
													+ mode_lib->vba.meta_row_bw[k]
													+ mode_lib->vba.dpte_row_bw[k]));

			अगर (mode_lib->vba.DestinationLinesForPrefetch[k] < 2)
				DestinationLineTimesForPrefetchLessThan2 = true;
			अगर (mode_lib->vba.VRatioPrefetchY[k] > 4
					|| mode_lib->vba.VRatioPrefetchC[k] > 4)
				VRatioPrefetchMoreThan4 = true;
		पूर्ण

		अगर (MaxTotalRDBandwidth <= mode_lib->vba.ReturnBW && prefetch_vm_bw_valid
				&& prefetch_row_bw_valid && !VRatioPrefetchMoreThan4
				&& !DestinationLineTimesForPrefetchLessThan2)
			mode_lib->vba.PrefetchModeSupported = true;
		अन्यथा अणु
			mode_lib->vba.PrefetchModeSupported = false;
			dml_prपूर्णांक(
					"DML: CalculatePrefetchSchedule ***failed***. Bandwidth violation. Results are NOT valid\n");
		पूर्ण

		अगर (mode_lib->vba.PrefetchModeSupported == true) अणु
			द्विगुन final_flip_bw[DC__NUM_DPP__MAX];
			अचिन्हित पूर्णांक ImmediateFlipBytes[DC__NUM_DPP__MAX];
			द्विगुन total_dcn_पढ़ो_bw_with_flip = 0;

			mode_lib->vba.BandwidthAvailableForImmediateFlip = mode_lib->vba.ReturnBW;
			क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
				mode_lib->vba.BandwidthAvailableForImmediateFlip =
						mode_lib->vba.BandwidthAvailableForImmediateFlip
								- mode_lib->vba.cursor_bw[k]
								- dml_max(
										mode_lib->vba.ReadBandwidthPlaneLuma[k]
												+ mode_lib->vba.ReadBandwidthPlaneChroma[k]
												+ mode_lib->vba.qual_row_bw[k],
										mode_lib->vba.PrefetchBandwidth[k]);
			पूर्ण

			क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
				ImmediateFlipBytes[k] = 0;
				अगर ((mode_lib->vba.SourcePixelFormat[k] != dm_420_8
						&& mode_lib->vba.SourcePixelFormat[k] != dm_420_10)) अणु
					ImmediateFlipBytes[k] =
							mode_lib->vba.PDEAndMetaPTEBytesFrame[k]
									+ mode_lib->vba.MetaRowByte[k]
									+ mode_lib->vba.PixelPTEBytesPerRow[k];
				पूर्ण
			पूर्ण
			mode_lib->vba.TotImmediateFlipBytes = 0;
			क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
				अगर ((mode_lib->vba.SourcePixelFormat[k] != dm_420_8
						&& mode_lib->vba.SourcePixelFormat[k] != dm_420_10)) अणु
					mode_lib->vba.TotImmediateFlipBytes =
							mode_lib->vba.TotImmediateFlipBytes
									+ ImmediateFlipBytes[k];
				पूर्ण
			पूर्ण
			क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
				CalculateFlipSchedule(
						mode_lib,
						mode_lib->vba.UrgentExtraLatency,
						mode_lib->vba.UrgentLatencyPixelDataOnly,
						mode_lib->vba.GPUVMMaxPageTableLevels,
						mode_lib->vba.GPUVMEnable,
						mode_lib->vba.BandwidthAvailableForImmediateFlip,
						mode_lib->vba.TotImmediateFlipBytes,
						mode_lib->vba.SourcePixelFormat[k],
						ImmediateFlipBytes[k],
						mode_lib->vba.HTotal[k]
								/ mode_lib->vba.PixelClock[k],
						mode_lib->vba.VRatio[k],
						mode_lib->vba.Tno_bw[k],
						mode_lib->vba.PDEAndMetaPTEBytesFrame[k],
						mode_lib->vba.MetaRowByte[k],
						mode_lib->vba.PixelPTEBytesPerRow[k],
						mode_lib->vba.DCCEnable[k],
						mode_lib->vba.dpte_row_height[k],
						mode_lib->vba.meta_row_height[k],
						mode_lib->vba.qual_row_bw[k],
						&mode_lib->vba.DestinationLinesToRequestVMInImmediateFlip[k],
						&mode_lib->vba.DestinationLinesToRequestRowInImmediateFlip[k],
						&final_flip_bw[k],
						&mode_lib->vba.ImmediateFlipSupportedForPipe[k]);
			पूर्ण
			क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
				total_dcn_पढ़ो_bw_with_flip =
						total_dcn_पढ़ो_bw_with_flip
								+ mode_lib->vba.cursor_bw[k]
								+ dml_max(
										mode_lib->vba.prefetch_vm_bw[k],
										dml_max(
												mode_lib->vba.prefetch_row_bw[k],
												final_flip_bw[k]
														+ dml_max(
																mode_lib->vba.ReadBandwidthPlaneLuma[k]
																		+ mode_lib->vba.ReadBandwidthPlaneChroma[k],
																mode_lib->vba.RequiredPrefetchPixDataBWLuma[k])));
			पूर्ण
			mode_lib->vba.ImmediateFlipSupported = true;
			अगर (total_dcn_पढ़ो_bw_with_flip > mode_lib->vba.ReturnBW) अणु
				mode_lib->vba.ImmediateFlipSupported = false;
			पूर्ण
			क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
				अगर (mode_lib->vba.ImmediateFlipSupportedForPipe[k] == false) अणु
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
			&& (!mode_lib->vba.ImmediateFlipSupport
					|| mode_lib->vba.ImmediateFlipSupported))
			|| mode_lib->vba.MaximumMaxVStartupLines < mode_lib->vba.VStartupLines));

	//Display Pipeline Delivery Time in Prefetch
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		अगर (mode_lib->vba.VRatioPrefetchY[k] <= 1) अणु
			mode_lib->vba.DisplayPipeLineDeliveryTimeLumaPrefetch[k] =
					mode_lib->vba.SwathWidthY[k] * mode_lib->vba.DPPPerPlane[k]
							/ mode_lib->vba.HRatio[k]
							/ mode_lib->vba.PixelClock[k];
		पूर्ण अन्यथा अणु
			mode_lib->vba.DisplayPipeLineDeliveryTimeLumaPrefetch[k] =
					mode_lib->vba.SwathWidthY[k]
							/ mode_lib->vba.PSCL_THROUGHPUT_LUMA[k]
							/ mode_lib->vba.DPPCLK[k];
		पूर्ण
		अगर (mode_lib->vba.BytePerPixelDETC[k] == 0) अणु
			mode_lib->vba.DisplayPipeLineDeliveryTimeChromaPrefetch[k] = 0;
		पूर्ण अन्यथा अणु
			अगर (mode_lib->vba.VRatioPrefetchC[k] <= 1) अणु
				mode_lib->vba.DisplayPipeLineDeliveryTimeChromaPrefetch[k] =
						mode_lib->vba.SwathWidthY[k]
								* mode_lib->vba.DPPPerPlane[k]
								/ mode_lib->vba.HRatio[k]
								/ mode_lib->vba.PixelClock[k];
			पूर्ण अन्यथा अणु
				mode_lib->vba.DisplayPipeLineDeliveryTimeChromaPrefetch[k] =
						mode_lib->vba.SwathWidthY[k]
								/ mode_lib->vba.PSCL_THROUGHPUT_LUMA[k]
								/ mode_lib->vba.DPPCLK[k];
			पूर्ण
		पूर्ण
	पूर्ण

	// Min TTUVBlank
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		अगर (mode_lib->vba.PrefetchMode[mode_lib->vba.VoltageLevel][mode_lib->vba.maxMpcComb] == 0) अणु
			mode_lib->vba.AllowDRAMClockChangeDuringVBlank[k] = true;
			mode_lib->vba.AllowDRAMSelfRefreshDuringVBlank[k] = true;
			mode_lib->vba.MinTTUVBlank[k] = dml_max(
					mode_lib->vba.DRAMClockChangeWatermark,
					dml_max(
							mode_lib->vba.StutterEnterPlusExitWatermark,
							mode_lib->vba.UrgentWatermark));
		पूर्ण अन्यथा अगर (mode_lib->vba.PrefetchMode[mode_lib->vba.VoltageLevel][mode_lib->vba.maxMpcComb] == 1) अणु
			mode_lib->vba.AllowDRAMClockChangeDuringVBlank[k] = false;
			mode_lib->vba.AllowDRAMSelfRefreshDuringVBlank[k] = true;
			mode_lib->vba.MinTTUVBlank[k] = dml_max(
					mode_lib->vba.StutterEnterPlusExitWatermark,
					mode_lib->vba.UrgentWatermark);
		पूर्ण अन्यथा अणु
			mode_lib->vba.AllowDRAMClockChangeDuringVBlank[k] = false;
			mode_lib->vba.AllowDRAMSelfRefreshDuringVBlank[k] = false;
			mode_lib->vba.MinTTUVBlank[k] = mode_lib->vba.UrgentWatermark;
		पूर्ण
		अगर (!mode_lib->vba.DynamicMetadataEnable[k])
			mode_lib->vba.MinTTUVBlank[k] = mode_lib->vba.TCalc
					+ mode_lib->vba.MinTTUVBlank[k];
	पूर्ण

	// DCC Configuration
	mode_lib->vba.ActiveDPPs = 0;
	// NB P-State/DRAM Clock Change Support
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		mode_lib->vba.ActiveDPPs = mode_lib->vba.ActiveDPPs + mode_lib->vba.DPPPerPlane[k];
	पूर्ण

	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		द्विगुन EffectiveLBLatencyHidingY;
		द्विगुन EffectiveLBLatencyHidingC;
		द्विगुन DPPOutputBufferLinesY;
		द्विगुन DPPOutputBufferLinesC;
		द्विगुन DPPOPPBufferingY;
		द्विगुन MaxDETBufferingTimeY;
		द्विगुन ActiveDRAMClockChangeLatencyMarginY;

		mode_lib->vba.LBLatencyHidingSourceLinesY =
				dml_min(
						mode_lib->vba.MaxLineBufferLines,
						(अचिन्हित पूर्णांक) dml_न्यूनमान(
								(द्विगुन) mode_lib->vba.LineBufferSize
										/ mode_lib->vba.LBBitPerPixel[k]
										/ (mode_lib->vba.SwathWidthY[k]
												/ dml_max(
														mode_lib->vba.HRatio[k],
														1.0)),
								1)) - (mode_lib->vba.vtaps[k] - 1);

		mode_lib->vba.LBLatencyHidingSourceLinesC =
				dml_min(
						mode_lib->vba.MaxLineBufferLines,
						(अचिन्हित पूर्णांक) dml_न्यूनमान(
								(द्विगुन) mode_lib->vba.LineBufferSize
										/ mode_lib->vba.LBBitPerPixel[k]
										/ (mode_lib->vba.SwathWidthY[k]
												/ 2.0
												/ dml_max(
														mode_lib->vba.HRatio[k]
																/ 2,
														1.0)),
								1))
						- (mode_lib->vba.VTAPsChroma[k] - 1);

		EffectiveLBLatencyHidingY = mode_lib->vba.LBLatencyHidingSourceLinesY
				/ mode_lib->vba.VRatio[k]
				* (mode_lib->vba.HTotal[k] / mode_lib->vba.PixelClock[k]);

		EffectiveLBLatencyHidingC = mode_lib->vba.LBLatencyHidingSourceLinesC
				/ (mode_lib->vba.VRatio[k] / 2)
				* (mode_lib->vba.HTotal[k] / mode_lib->vba.PixelClock[k]);

		अगर (mode_lib->vba.SwathWidthY[k] > 2 * mode_lib->vba.DPPOutputBufferPixels) अणु
			DPPOutputBufferLinesY = mode_lib->vba.DPPOutputBufferPixels
					/ mode_lib->vba.SwathWidthY[k];
		पूर्ण अन्यथा अगर (mode_lib->vba.SwathWidthY[k] > mode_lib->vba.DPPOutputBufferPixels) अणु
			DPPOutputBufferLinesY = 0.5;
		पूर्ण अन्यथा अणु
			DPPOutputBufferLinesY = 1;
		पूर्ण

		अगर (mode_lib->vba.SwathWidthY[k] / 2 > 2 * mode_lib->vba.DPPOutputBufferPixels) अणु
			DPPOutputBufferLinesC = mode_lib->vba.DPPOutputBufferPixels
					/ (mode_lib->vba.SwathWidthY[k] / 2);
		पूर्ण अन्यथा अगर (mode_lib->vba.SwathWidthY[k] / 2 > mode_lib->vba.DPPOutputBufferPixels) अणु
			DPPOutputBufferLinesC = 0.5;
		पूर्ण अन्यथा अणु
			DPPOutputBufferLinesC = 1;
		पूर्ण

		DPPOPPBufferingY = (mode_lib->vba.HTotal[k] / mode_lib->vba.PixelClock[k])
				* (DPPOutputBufferLinesY + mode_lib->vba.OPPOutputBufferLines);
		MaxDETBufferingTimeY = mode_lib->vba.FullDETBufferingTimeY[k]
				+ (mode_lib->vba.LinesInDETY[k]
						- mode_lib->vba.LinesInDETYRoundedDownToSwath[k])
						/ mode_lib->vba.SwathHeightY[k]
						* (mode_lib->vba.HTotal[k]
								/ mode_lib->vba.PixelClock[k]);

		ActiveDRAMClockChangeLatencyMarginY = DPPOPPBufferingY + EffectiveLBLatencyHidingY
				+ MaxDETBufferingTimeY - mode_lib->vba.DRAMClockChangeWatermark;

		अगर (mode_lib->vba.ActiveDPPs > 1) अणु
			ActiveDRAMClockChangeLatencyMarginY =
					ActiveDRAMClockChangeLatencyMarginY
							- (1 - 1 / (mode_lib->vba.ActiveDPPs - 1))
									* mode_lib->vba.SwathHeightY[k]
									* (mode_lib->vba.HTotal[k]
											/ mode_lib->vba.PixelClock[k]);
		पूर्ण

		अगर (mode_lib->vba.BytePerPixelDETC[k] > 0) अणु
			द्विगुन DPPOPPBufferingC = (mode_lib->vba.HTotal[k]
					/ mode_lib->vba.PixelClock[k])
					* (DPPOutputBufferLinesC
							+ mode_lib->vba.OPPOutputBufferLines);
			द्विगुन MaxDETBufferingTimeC =
					mode_lib->vba.FullDETBufferingTimeC[k]
							+ (mode_lib->vba.LinesInDETC[k]
									- mode_lib->vba.LinesInDETCRoundedDownToSwath[k])
									/ mode_lib->vba.SwathHeightC[k]
									* (mode_lib->vba.HTotal[k]
											/ mode_lib->vba.PixelClock[k]);
			द्विगुन ActiveDRAMClockChangeLatencyMarginC = DPPOPPBufferingC
					+ EffectiveLBLatencyHidingC + MaxDETBufferingTimeC
					- mode_lib->vba.DRAMClockChangeWatermark;

			अगर (mode_lib->vba.ActiveDPPs > 1) अणु
				ActiveDRAMClockChangeLatencyMarginC =
						ActiveDRAMClockChangeLatencyMarginC
								- (1
										- 1
												/ (mode_lib->vba.ActiveDPPs
														- 1))
										* mode_lib->vba.SwathHeightC[k]
										* (mode_lib->vba.HTotal[k]
												/ mode_lib->vba.PixelClock[k]);
			पूर्ण
			mode_lib->vba.ActiveDRAMClockChangeLatencyMargin[k] = dml_min(
					ActiveDRAMClockChangeLatencyMarginY,
					ActiveDRAMClockChangeLatencyMarginC);
		पूर्ण अन्यथा अणु
			mode_lib->vba.ActiveDRAMClockChangeLatencyMargin[k] =
					ActiveDRAMClockChangeLatencyMarginY;
		पूर्ण

		अगर (mode_lib->vba.WritebackEnable[k]) अणु
			द्विगुन WritebackDRAMClockChangeLatencyMargin;

			अगर (mode_lib->vba.WritebackPixelFormat[k] == dm_444_32) अणु
				WritebackDRAMClockChangeLatencyMargin =
						(द्विगुन) (mode_lib->vba.WritebackInterfaceLumaBufferSize
								+ mode_lib->vba.WritebackInterfaceChromaBufferSize)
								/ (mode_lib->vba.WritebackDestinationWidth[k]
										* mode_lib->vba.WritebackDestinationHeight[k]
										/ (mode_lib->vba.WritebackSourceHeight[k]
												* mode_lib->vba.HTotal[k]
												/ mode_lib->vba.PixelClock[k])
										* 4)
								- mode_lib->vba.WritebackDRAMClockChangeWatermark;
			पूर्ण अन्यथा अगर (mode_lib->vba.WritebackPixelFormat[k] == dm_420_10) अणु
				WritebackDRAMClockChangeLatencyMargin =
						dml_min(
								(द्विगुन) mode_lib->vba.WritebackInterfaceLumaBufferSize
										* 8.0 / 10,
								2.0
										* mode_lib->vba.WritebackInterfaceChromaBufferSize
										* 8 / 10)
								/ (mode_lib->vba.WritebackDestinationWidth[k]
										* mode_lib->vba.WritebackDestinationHeight[k]
										/ (mode_lib->vba.WritebackSourceHeight[k]
												* mode_lib->vba.HTotal[k]
												/ mode_lib->vba.PixelClock[k]))
								- mode_lib->vba.WritebackDRAMClockChangeWatermark;
			पूर्ण अन्यथा अणु
				WritebackDRAMClockChangeLatencyMargin =
						dml_min(
								(द्विगुन) mode_lib->vba.WritebackInterfaceLumaBufferSize,
								2.0
										* mode_lib->vba.WritebackInterfaceChromaBufferSize)
								/ (mode_lib->vba.WritebackDestinationWidth[k]
										* mode_lib->vba.WritebackDestinationHeight[k]
										/ (mode_lib->vba.WritebackSourceHeight[k]
												* mode_lib->vba.HTotal[k]
												/ mode_lib->vba.PixelClock[k]))
								- mode_lib->vba.WritebackDRAMClockChangeWatermark;
			पूर्ण
			mode_lib->vba.ActiveDRAMClockChangeLatencyMargin[k] = dml_min(
					mode_lib->vba.ActiveDRAMClockChangeLatencyMargin[k],
					WritebackDRAMClockChangeLatencyMargin);
		पूर्ण
	पूर्ण

	अणु
	भग्न SecondMinActiveDRAMClockChangeMarginOneDisplayInVBLank = 999999;
	पूर्णांक PlaneWithMinActiveDRAMClockChangeMargin = -1;

	mode_lib->vba.MinActiveDRAMClockChangeMargin = 999999;
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		अगर (mode_lib->vba.ActiveDRAMClockChangeLatencyMargin[k]
				< mode_lib->vba.MinActiveDRAMClockChangeMargin) अणु
			mode_lib->vba.MinActiveDRAMClockChangeMargin =
					mode_lib->vba.ActiveDRAMClockChangeLatencyMargin[k];
			अगर (mode_lib->vba.BlendingAndTiming[k] == k) अणु
				PlaneWithMinActiveDRAMClockChangeMargin = k;
			पूर्ण अन्यथा अणु
				क्रम (j = 0; j < mode_lib->vba.NumberOfActivePlanes; ++j) अणु
					अगर (mode_lib->vba.BlendingAndTiming[k] == j) अणु
						PlaneWithMinActiveDRAMClockChangeMargin = j;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	mode_lib->vba.MinActiveDRAMClockChangeLatencySupported =
			mode_lib->vba.MinActiveDRAMClockChangeMargin
					+ mode_lib->vba.DRAMClockChangeLatency;
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		अगर (!((k == PlaneWithMinActiveDRAMClockChangeMargin) && (mode_lib->vba.BlendingAndTiming[k] == k))
				&& !(mode_lib->vba.BlendingAndTiming[k] == PlaneWithMinActiveDRAMClockChangeMargin)
				&& mode_lib->vba.ActiveDRAMClockChangeLatencyMargin[k]
						< SecondMinActiveDRAMClockChangeMarginOneDisplayInVBLank) अणु
			SecondMinActiveDRAMClockChangeMarginOneDisplayInVBLank =
					mode_lib->vba.ActiveDRAMClockChangeLatencyMargin[k];
		पूर्ण
	पूर्ण

	अगर (mode_lib->vba.DRAMClockChangeSupportsVActive &&
			mode_lib->vba.MinActiveDRAMClockChangeMargin > 60) अणु
		mode_lib->vba.DRAMClockChangeWatermark += 25;

		क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
			अगर (mode_lib->vba.PrefetchMode[mode_lib->vba.VoltageLevel][mode_lib->vba.maxMpcComb] == 0) अणु
				अगर (mode_lib->vba.DRAMClockChangeWatermark >
				dml_max(mode_lib->vba.StutterEnterPlusExitWatermark, mode_lib->vba.UrgentWatermark))
					mode_lib->vba.MinTTUVBlank[k] += 25;
			पूर्ण
		पूर्ण

		mode_lib->vba.DRAMClockChangeSupport[0][0] = dm_dram_घड़ी_change_vactive;
	पूर्ण अन्यथा अगर (mode_lib->vba.DummyPStateCheck &&
			mode_lib->vba.MinActiveDRAMClockChangeMargin > 0) अणु
		mode_lib->vba.DRAMClockChangeSupport[0][0] = dm_dram_घड़ी_change_vactive;
	पूर्ण अन्यथा अणु
		अगर ((mode_lib->vba.SynchronizedVBlank
				|| mode_lib->vba.NumberOfActivePlanes == 1
				|| (SecondMinActiveDRAMClockChangeMarginOneDisplayInVBLank > 0 &&
						mode_lib->vba.AllowDramClockChangeOneDisplayVactive))
					&& mode_lib->vba.PrefetchMode[mode_lib->vba.VoltageLevel][mode_lib->vba.maxMpcComb] == 0) अणु
			mode_lib->vba.DRAMClockChangeSupport[0][0] = dm_dram_घड़ी_change_vblank;
			क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
				अगर (!mode_lib->vba.AllowDRAMClockChangeDuringVBlank[k]) अणु
					mode_lib->vba.DRAMClockChangeSupport[0][0] =
							dm_dram_घड़ी_change_unsupported;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			mode_lib->vba.DRAMClockChangeSupport[0][0] = dm_dram_घड़ी_change_unsupported;
		पूर्ण
	पूर्ण
	पूर्ण
	क्रम (k = 0; k <= mode_lib->vba.soc.num_states; k++)
		क्रम (j = 0; j < 2; j++)
			mode_lib->vba.DRAMClockChangeSupport[k][j] = mode_lib->vba.DRAMClockChangeSupport[0][0];

	//XFC Parameters:
	क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
		अगर (mode_lib->vba.XFCEnabled[k] == true) अणु
			द्विगुन TWait;

			mode_lib->vba.XFCSlaveVUpdateOffset[k] = mode_lib->vba.XFCTSlvVupdateOffset;
			mode_lib->vba.XFCSlaveVupdateWidth[k] = mode_lib->vba.XFCTSlvVupdateWidth;
			mode_lib->vba.XFCSlaveVReadyOffset[k] = mode_lib->vba.XFCTSlvVपढ़ोyOffset;
			TWait = CalculateTWait(
					mode_lib->vba.PrefetchMode[mode_lib->vba.VoltageLevel][mode_lib->vba.maxMpcComb],
					mode_lib->vba.DRAMClockChangeLatency,
					mode_lib->vba.UrgentLatencyPixelDataOnly,
					mode_lib->vba.SREnterPlusExitTime);
			mode_lib->vba.XFCRemoteSurfaceFlipDelay = CalculateRemoteSurfaceFlipDelay(
					mode_lib,
					mode_lib->vba.VRatio[k],
					mode_lib->vba.SwathWidthY[k],
					dml_उच्चमान(mode_lib->vba.BytePerPixelDETY[k], 1),
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
			mode_lib->vba.XFCRemoteSurfaceFlipLatency[k] =
					dml_न्यूनमान(
							mode_lib->vba.XFCRemoteSurfaceFlipDelay
									/ (mode_lib->vba.HTotal[k]
											/ mode_lib->vba.PixelClock[k]),
							1);
			mode_lib->vba.XFCTransferDelay[k] =
					dml_उच्चमान(
							mode_lib->vba.XFCBusTransportTime
									/ (mode_lib->vba.HTotal[k]
											/ mode_lib->vba.PixelClock[k]),
							1);
			mode_lib->vba.XFCPreअक्षरgeDelay[k] =
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
					(mode_lib->vba.DestinationLinesToRequestVMInVBlank[k]
							+ mode_lib->vba.DestinationLinesToRequestRowInVBlank[k])
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
			mode_lib->vba.XFCPrefetchMargin[k] =
					mode_lib->vba.XFCRemoteSurfaceFlipDelay
							+ mode_lib->vba.TFinalxFill
							+ (mode_lib->vba.DestinationLinesToRequestVMInVBlank[k]
									+ mode_lib->vba.DestinationLinesToRequestRowInVBlank[k])
									* mode_lib->vba.HTotal[k]
									/ mode_lib->vba.PixelClock[k];
		पूर्ण अन्यथा अणु
			mode_lib->vba.XFCSlaveVUpdateOffset[k] = 0;
			mode_lib->vba.XFCSlaveVupdateWidth[k] = 0;
			mode_lib->vba.XFCSlaveVReadyOffset[k] = 0;
			mode_lib->vba.XFCRemoteSurfaceFlipLatency[k] = 0;
			mode_lib->vba.XFCPreअक्षरgeDelay[k] = 0;
			mode_lib->vba.XFCTransferDelay[k] = 0;
			mode_lib->vba.XFCPrefetchMargin[k] = 0;
		पूर्ण
	पूर्ण
	अणु
		अचिन्हित पूर्णांक VStartupMargin = 0;
		bool FirstMainPlane = true;

		क्रम (k = 0; k < mode_lib->vba.NumberOfActivePlanes; ++k) अणु
			अगर (mode_lib->vba.BlendingAndTiming[k] == k) अणु
				अचिन्हित पूर्णांक Margin = (mode_lib->vba.MaxVStartupLines[k] - mode_lib->vba.VStartup[k])
						* mode_lib->vba.HTotal[k] / mode_lib->vba.PixelClock[k];

				अगर (FirstMainPlane) अणु
					VStartupMargin = Margin;
					FirstMainPlane = false;
				पूर्ण अन्यथा
					VStartupMargin = dml_min(VStartupMargin, Margin);
		पूर्ण

		अगर (mode_lib->vba.UseMaximumVStartup) अणु
			अगर (mode_lib->vba.VTotal_Max[k] == mode_lib->vba.VTotal[k]) अणु
				//only use max vstart अगर it is not drr or lateflip.
				mode_lib->vba.VStartup[k] = mode_lib->vba.MaxVStartupLines[mode_lib->vba.BlendingAndTiming[k]];
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण
पूर्ण

अटल व्योम dml20v2_DisplayPipeConfiguration(काष्ठा display_mode_lib *mode_lib)
अणु
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
			अगर (mode_lib->vba.DPPPerPlane[k] == 0)
				SwathWidth = 0;
			अन्यथा
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

		अगर (mode_lib->vba.SwathHeightC[k] == 0) अणु
			mode_lib->vba.DETBufferSizeY[k] = mode_lib->vba.DETBufferSizeInKByte * 1024;
			mode_lib->vba.DETBufferSizeC[k] = 0;
		पूर्ण अन्यथा अगर (mode_lib->vba.SwathHeightY[k] <= mode_lib->vba.SwathHeightC[k]) अणु
			mode_lib->vba.DETBufferSizeY[k] = mode_lib->vba.DETBufferSizeInKByte
					* 1024.0 / 2;
			mode_lib->vba.DETBufferSizeC[k] = mode_lib->vba.DETBufferSizeInKByte
					* 1024.0 / 2;
		पूर्ण अन्यथा अणु
			mode_lib->vba.DETBufferSizeY[k] = mode_lib->vba.DETBufferSizeInKByte
					* 1024.0 * 2 / 3;
			mode_lib->vba.DETBufferSizeC[k] = mode_lib->vba.DETBufferSizeInKByte
					* 1024.0 / 3;
		पूर्ण
	पूर्ण
पूर्ण

अटल द्विगुन CalculateTWait(
		अचिन्हित पूर्णांक PrefetchMode,
		द्विगुन DRAMClockChangeLatency,
		द्विगुन UrgentLatencyPixelDataOnly,
		द्विगुन SREnterPlusExitTime)
अणु
	अगर (PrefetchMode == 0) अणु
		वापस dml_max(
				DRAMClockChangeLatency + UrgentLatencyPixelDataOnly,
				dml_max(SREnterPlusExitTime, UrgentLatencyPixelDataOnly));
	पूर्ण अन्यथा अगर (PrefetchMode == 1) अणु
		वापस dml_max(SREnterPlusExitTime, UrgentLatencyPixelDataOnly);
	पूर्ण अन्यथा अणु
		वापस UrgentLatencyPixelDataOnly;
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
		द्विगुन *dpte_row_bw,
		द्विगुन *qual_row_bw)
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

	अगर ((SourcePixelFormat == dm_420_8 || SourcePixelFormat == dm_420_10)) अणु
		*qual_row_bw = *meta_row_bw + *dpte_row_bw;
	पूर्ण अन्यथा अणु
		*qual_row_bw = 0;
	पूर्ण
पूर्ण

अटल व्योम CalculateFlipSchedule(
		काष्ठा display_mode_lib *mode_lib,
		द्विगुन UrgentExtraLatency,
		द्विगुन UrgentLatencyPixelDataOnly,
		अचिन्हित पूर्णांक GPUVMMaxPageTableLevels,
		bool GPUVMEnable,
		द्विगुन BandwidthAvailableForImmediateFlip,
		अचिन्हित पूर्णांक TotImmediateFlipBytes,
		क्रमागत source_क्रमmat_class SourcePixelFormat,
		अचिन्हित पूर्णांक ImmediateFlipBytes,
		द्विगुन LineTime,
		द्विगुन VRatio,
		द्विगुन Tno_bw,
		द्विगुन PDEAndMetaPTEBytesFrame,
		अचिन्हित पूर्णांक MetaRowByte,
		अचिन्हित पूर्णांक PixelPTEBytesPerRow,
		bool DCCEnable,
		अचिन्हित पूर्णांक dpte_row_height,
		अचिन्हित पूर्णांक meta_row_height,
		द्विगुन qual_row_bw,
		द्विगुन *DestinationLinesToRequestVMInImmediateFlip,
		द्विगुन *DestinationLinesToRequestRowInImmediateFlip,
		द्विगुन *final_flip_bw,
		bool *ImmediateFlipSupportedForPipe)
अणु
	द्विगुन min_row_समय = 0.0;

	अगर (SourcePixelFormat == dm_420_8 || SourcePixelFormat == dm_420_10) अणु
		*DestinationLinesToRequestVMInImmediateFlip = 0.0;
		*DestinationLinesToRequestRowInImmediateFlip = 0.0;
		*final_flip_bw = qual_row_bw;
		*ImmediateFlipSupportedForPipe = true;
	पूर्ण अन्यथा अणु
		द्विगुन TimeForFetchingMetaPTEImmediateFlip;
		द्विगुन TimeForFetchingRowInVBlankImmediateFlip;

		अगर (GPUVMEnable == true) अणु
			mode_lib->vba.ImmediateFlipBW[0] = BandwidthAvailableForImmediateFlip
					* ImmediateFlipBytes / TotImmediateFlipBytes;
			TimeForFetchingMetaPTEImmediateFlip =
					dml_max(
							Tno_bw
									+ PDEAndMetaPTEBytesFrame
											/ mode_lib->vba.ImmediateFlipBW[0],
							dml_max(
									UrgentExtraLatency
											+ UrgentLatencyPixelDataOnly
													* (GPUVMMaxPageTableLevels
															- 1),
									LineTime / 4.0));
		पूर्ण अन्यथा अणु
			TimeForFetchingMetaPTEImmediateFlip = 0;
		पूर्ण

		*DestinationLinesToRequestVMInImmediateFlip = dml_न्यूनमान(
				4.0 * (TimeForFetchingMetaPTEImmediateFlip / LineTime + 0.125),
				1) / 4.0;

		अगर ((GPUVMEnable == true || DCCEnable == true)) अणु
			mode_lib->vba.ImmediateFlipBW[0] = BandwidthAvailableForImmediateFlip
					* ImmediateFlipBytes / TotImmediateFlipBytes;
			TimeForFetchingRowInVBlankImmediateFlip = dml_max(
					(MetaRowByte + PixelPTEBytesPerRow)
							/ mode_lib->vba.ImmediateFlipBW[0],
					dml_max(UrgentLatencyPixelDataOnly, LineTime / 4.0));
		पूर्ण अन्यथा अणु
			TimeForFetchingRowInVBlankImmediateFlip = 0;
		पूर्ण

		*DestinationLinesToRequestRowInImmediateFlip = dml_न्यूनमान(
				4.0 * (TimeForFetchingRowInVBlankImmediateFlip / LineTime + 0.125),
				1) / 4.0;

		अगर (GPUVMEnable == true) अणु
			*final_flip_bw =
					dml_max(
							PDEAndMetaPTEBytesFrame
									/ (*DestinationLinesToRequestVMInImmediateFlip
											* LineTime),
							(MetaRowByte + PixelPTEBytesPerRow)
									/ (TimeForFetchingRowInVBlankImmediateFlip
											* LineTime));
		पूर्ण अन्यथा अगर (MetaRowByte + PixelPTEBytesPerRow > 0) अणु
			*final_flip_bw = (MetaRowByte + PixelPTEBytesPerRow)
					/ (TimeForFetchingRowInVBlankImmediateFlip * LineTime);
		पूर्ण अन्यथा अणु
			*final_flip_bw = 0;
		पूर्ण

		अगर (GPUVMEnable && !DCCEnable)
			min_row_समय = dpte_row_height * LineTime / VRatio;
		अन्यथा अगर (!GPUVMEnable && DCCEnable)
			min_row_समय = meta_row_height * LineTime / VRatio;
		अन्यथा
			min_row_समय = dml_min(dpte_row_height, meta_row_height) * LineTime
					/ VRatio;

		अगर (*DestinationLinesToRequestVMInImmediateFlip >= 8
				|| *DestinationLinesToRequestRowInImmediateFlip >= 16
				|| TimeForFetchingMetaPTEImmediateFlip
						+ 2 * TimeForFetchingRowInVBlankImmediateFlip
						> min_row_समय)
			*ImmediateFlipSupportedForPipe = false;
		अन्यथा
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

व्योम dml20v2_ModeSupportAndSystemConfigurationFull(काष्ठा display_mode_lib *mode_lib)
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
	mode_lib->vba.UrgentLatency = mode_lib->vba.UrgentLatencyPixelDataOnly;
	क्रम (i = 0; i <= mode_lib->vba.soc.num_states; i++) अणु
		locals->FabricAndDRAMBandwidthPerState[i] = dml_min(
				mode_lib->vba.DRAMSpeedPerState[i] * mode_lib->vba.NumberOfChannels
						* mode_lib->vba.DRAMChannelWidth,
				mode_lib->vba.FabricClockPerState[i]
						* mode_lib->vba.FabricDatapathToDCNDataReturn) / 1000;
		locals->ReturnBWToDCNPerState = dml_min(locals->ReturnBusWidth * locals->DCFCLKPerState[i],
				locals->FabricAndDRAMBandwidthPerState[i] * 1000)
				* locals->PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelDataOnly / 100;

		locals->ReturnBWPerState[i][0] = locals->ReturnBWToDCNPerState;

		अगर (locals->DCCEnabledInAnyPlane == true && locals->ReturnBWToDCNPerState > locals->DCFCLKPerState[i] * locals->ReturnBusWidth / 4) अणु
			locals->ReturnBWPerState[i][0] = dml_min(locals->ReturnBWPerState[i][0],
					locals->ReturnBWToDCNPerState * 4 * (1 - locals->UrgentLatency /
					((locals->ROBBufferSizeInKByte - locals->PixelChunkSizeInKByte) * 1024
					/ (locals->ReturnBWToDCNPerState - locals->DCFCLKPerState[i]
					* locals->ReturnBusWidth / 4) + locals->UrgentLatency)));
		पूर्ण
		locals->CriticalPoपूर्णांक = 2 * locals->ReturnBusWidth * locals->DCFCLKPerState[i] *
				locals->UrgentLatency / (locals->ReturnBWToDCNPerState * locals->UrgentLatency
				+ (locals->ROBBufferSizeInKByte - locals->PixelChunkSizeInKByte) * 1024);

		अगर (locals->DCCEnabledInAnyPlane && locals->CriticalPoपूर्णांक > 1 && locals->CriticalPoपूर्णांक < 4) अणु
			locals->ReturnBWPerState[i][0] = dml_min(locals->ReturnBWPerState[i][0],
				4 * locals->ReturnBWToDCNPerState *
				(locals->ROBBufferSizeInKByte - locals->PixelChunkSizeInKByte) * 1024
				* locals->ReturnBusWidth * locals->DCFCLKPerState[i] * locals->UrgentLatency /
				dml_घात((locals->ReturnBWToDCNPerState * locals->UrgentLatency
				+ (locals->ROBBufferSizeInKByte - locals->PixelChunkSizeInKByte) * 1024), 2));
		पूर्ण

		locals->ReturnBWToDCNPerState = dml_min(locals->ReturnBusWidth *
				locals->DCFCLKPerState[i], locals->FabricAndDRAMBandwidthPerState[i] * 1000);

		अगर (locals->DCCEnabledInAnyPlane == true && locals->ReturnBWToDCNPerState > locals->DCFCLKPerState[i] * locals->ReturnBusWidth / 4) अणु
			locals->ReturnBWPerState[i][0] = dml_min(locals->ReturnBWPerState[i][0],
					locals->ReturnBWToDCNPerState * 4 * (1 - locals->UrgentLatency /
					((locals->ROBBufferSizeInKByte - locals->PixelChunkSizeInKByte) * 1024
					/ (locals->ReturnBWToDCNPerState - locals->DCFCLKPerState[i]
					* locals->ReturnBusWidth / 4) + locals->UrgentLatency)));
		पूर्ण
		locals->CriticalPoपूर्णांक = 2 * locals->ReturnBusWidth * locals->DCFCLKPerState[i] *
				locals->UrgentLatency / (locals->ReturnBWToDCNPerState * locals->UrgentLatency
				+ (locals->ROBBufferSizeInKByte - locals->PixelChunkSizeInKByte) * 1024);

		अगर (locals->DCCEnabledInAnyPlane && locals->CriticalPoपूर्णांक > 1 && locals->CriticalPoपूर्णांक < 4) अणु
			locals->ReturnBWPerState[i][0] = dml_min(locals->ReturnBWPerState[i][0],
				4 * locals->ReturnBWToDCNPerState *
				(locals->ROBBufferSizeInKByte - locals->PixelChunkSizeInKByte) * 1024
				* locals->ReturnBusWidth * locals->DCFCLKPerState[i] * locals->UrgentLatency /
				dml_घात((locals->ReturnBWToDCNPerState * locals->UrgentLatency
				+ (locals->ROBBufferSizeInKByte - locals->PixelChunkSizeInKByte) * 1024), 2));
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
				+ locals->UrgentOutOfOrderReturnPerChannel * mode_lib->vba.NumberOfChannels / locals->ReturnBWPerState[i][0];
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
						mode_lib->vba.PixelClock[k] * (1.0 + mode_lib->vba.DISPCLKDPPCLKDSCCLKDownSpपढ़ोing / 100.0)
								* (1.0 + mode_lib->vba.DISPCLKRampingMargin / 100.0);
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
					पूर्ण अन्यथा अगर (locals->DSCEnabled[k] && (locals->HActive[k] > DCN20_MAX_DSC_IMAGE_WIDTH)) अणु
						locals->ODMCombineEnablePerState[i][k] = true;
						mode_lib->vba.PlaneRequiredDISPCLK = mode_lib->vba.PlaneRequiredDISPCLKWithODMCombine;
					पूर्ण अन्यथा अगर (locals->HActive[k] > DCN20_MAX_420_IMAGE_WIDTH && locals->OutputFormat[k] == dm_420) अणु
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
			locals->RequiresDSC[i][k] = 0;
			locals->RequiresFEC[i][k] = 0;
			अगर (mode_lib->vba.BlendingAndTiming[k] == k) अणु
				अगर (mode_lib->vba.Output[k] == dm_hdmi) अणु
					locals->RequiresDSC[i][k] = 0;
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
	क्रम (i = 0; i <= mode_lib->vba.soc.num_states; i++) अणु
		क्रम (j = 0; j < 2; j++) अणु
			क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
				अगर (locals->ODMCombineEnablePerState[i][k] == dm_odm_combine_mode_2to1)
					locals->SwathWidthYPerState[i][j][k] = dml_min(locals->SwathWidthYSingleDPP[k], dml_round(locals->HActive[k] / 2 * locals->HRatio[k]));
				अन्यथा
					locals->SwathWidthYPerState[i][j][k] = locals->SwathWidthYSingleDPP[k] / locals->NoOfDPP[i][j][k];
				locals->SwathWidthGranularityY = 256  / dml_उच्चमान(locals->BytePerPixelInDETY[k], 1) / locals->MaxSwathHeightY[k];
				locals->RoundedUpMaxSwathSizeBytesY = (dml_उच्चमान(locals->SwathWidthYPerState[i][j][k] - 1, locals->SwathWidthGranularityY)
						+ locals->SwathWidthGranularityY) * locals->BytePerPixelInDETY[k] * locals->MaxSwathHeightY[k];
				अगर (locals->SourcePixelFormat[k] == dm_420_10) अणु
					locals->RoundedUpMaxSwathSizeBytesY = dml_उच्चमान(locals->RoundedUpMaxSwathSizeBytesY, 256) + 256;
				पूर्ण
				अगर (locals->MaxSwathHeightC[k] > 0) अणु
					locals->SwathWidthGranularityC = 256 / dml_उच्चमान(locals->BytePerPixelInDETC[k], 2) / locals->MaxSwathHeightC[k];

					locals->RoundedUpMaxSwathSizeBytesC = (dml_उच्चमान(locals->SwathWidthYPerState[i][j][k] / 2 - 1, locals->SwathWidthGranularityC)
					+ locals->SwathWidthGranularityC) * locals->BytePerPixelInDETC[k] * locals->MaxSwathHeightC[k];
				पूर्ण
				अगर (locals->SourcePixelFormat[k] == dm_420_10) अणु
					locals->RoundedUpMaxSwathSizeBytesC = dml_उच्चमान(locals->RoundedUpMaxSwathSizeBytesC, 256)  + 256;
				पूर्ण अन्यथा अणु
					locals->RoundedUpMaxSwathSizeBytesC = 0;
				पूर्ण

				अगर (locals->RoundedUpMaxSwathSizeBytesY + locals->RoundedUpMaxSwathSizeBytesC <= locals->DETBufferSizeInKByte * 1024 / 2) अणु
					locals->SwathHeightYPerState[i][j][k] = locals->MaxSwathHeightY[k];
					locals->SwathHeightCPerState[i][j][k] = locals->MaxSwathHeightC[k];
				पूर्ण अन्यथा अणु
					locals->SwathHeightYPerState[i][j][k] = locals->MinSwathHeightY[k];
					locals->SwathHeightCPerState[i][j][k] = locals->MinSwathHeightC[k];
				पूर्ण

				अगर (locals->BytePerPixelInDETC[k] == 0) अणु
					locals->LinesInDETLuma = locals->DETBufferSizeInKByte * 1024 / locals->BytePerPixelInDETY[k] / locals->SwathWidthYPerState[i][j][k];
					locals->LinesInDETChroma = 0;
				पूर्ण अन्यथा अगर (locals->SwathHeightYPerState[i][j][k] <= locals->SwathHeightCPerState[i][j][k]) अणु
					locals->LinesInDETLuma = locals->DETBufferSizeInKByte * 1024 / 2 / locals->BytePerPixelInDETY[k] /
							locals->SwathWidthYPerState[i][j][k];
					locals->LinesInDETChroma = locals->DETBufferSizeInKByte * 1024 / 2 / locals->BytePerPixelInDETC[k] / (locals->SwathWidthYPerState[i][j][k] / 2);
				पूर्ण अन्यथा अणु
					locals->LinesInDETLuma = locals->DETBufferSizeInKByte * 1024 * 2 / 3 / locals->BytePerPixelInDETY[k] / locals->SwathWidthYPerState[i][j][k];
					locals->LinesInDETChroma = locals->DETBufferSizeInKByte * 1024 / 3 / locals->BytePerPixelInDETY[k] / (locals->SwathWidthYPerState[i][j][k] / 2);
				पूर्ण

				locals->EffectiveLBLatencyHidingSourceLinesLuma = dml_min(locals->MaxLineBufferLines,
					dml_न्यूनमान(locals->LineBufferSize / locals->LBBitPerPixel[k] / (locals->SwathWidthYPerState[i][j][k]
					/ dml_max(locals->HRatio[k], 1)), 1)) - (locals->vtaps[k] - 1);

				locals->EffectiveLBLatencyHidingSourceLinesChroma =  dml_min(locals->MaxLineBufferLines,
						dml_न्यूनमान(locals->LineBufferSize / locals->LBBitPerPixel[k]
						/ (locals->SwathWidthYPerState[i][j][k] / 2
						/ dml_max(locals->HRatio[k] / 2, 1)), 1)) - (locals->VTAPsChroma[k] - 1);

				locals->EffectiveDETLBLinesLuma = dml_न्यूनमान(locals->LinesInDETLuma +  dml_min(
						locals->LinesInDETLuma * locals->RequiredDISPCLK[i][j] * locals->BytePerPixelInDETY[k] *
						locals->PSCL_FACTOR[k] / locals->ReturnBWPerState[i][0],
						locals->EffectiveLBLatencyHidingSourceLinesLuma),
						locals->SwathHeightYPerState[i][j][k]);

				locals->EffectiveDETLBLinesChroma = dml_न्यूनमान(locals->LinesInDETChroma + dml_min(
						locals->LinesInDETChroma * locals->RequiredDISPCLK[i][j] * locals->BytePerPixelInDETC[k] *
						locals->PSCL_FACTOR_CHROMA[k] / locals->ReturnBWPerState[i][0],
						locals->EffectiveLBLatencyHidingSourceLinesChroma),
						locals->SwathHeightCPerState[i][j][k]);

				अगर (locals->BytePerPixelInDETC[k] == 0) अणु
					locals->UrgentLatencySupportUsPerState[i][j][k] = locals->EffectiveDETLBLinesLuma * (locals->HTotal[k] / locals->PixelClock[k])
							/ locals->VRatio[k] - locals->EffectiveDETLBLinesLuma * locals->SwathWidthYPerState[i][j][k] *
								dml_उच्चमान(locals->BytePerPixelInDETY[k], 1) / (locals->ReturnBWPerState[i][0] / locals->NoOfDPP[i][j][k]);
				पूर्ण अन्यथा अणु
					locals->UrgentLatencySupportUsPerState[i][j][k] = dml_min(
						locals->EffectiveDETLBLinesLuma * (locals->HTotal[k] / locals->PixelClock[k])
						/ locals->VRatio[k] - locals->EffectiveDETLBLinesLuma * locals->SwathWidthYPerState[i][j][k] *
						dml_उच्चमान(locals->BytePerPixelInDETY[k], 1) / (locals->ReturnBWPerState[i][0] / locals->NoOfDPP[i][j][k]),
							locals->EffectiveDETLBLinesChroma * (locals->HTotal[k] / locals->PixelClock[k]) / (locals->VRatio[k] / 2) -
							locals->EffectiveDETLBLinesChroma * locals->SwathWidthYPerState[i][j][k] / 2 *
							dml_उच्चमान(locals->BytePerPixelInDETC[k], 2) / (locals->ReturnBWPerState[i][0] / locals->NoOfDPP[i][j][k]));
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i <= locals->soc.num_states; i++) अणु
		क्रम (j = 0; j < 2; j++) अणु
			locals->UrgentLatencySupport[i][j] = true;
			क्रम (k = 0; k < locals->NumberOfActivePlanes; k++) अणु
				अगर (locals->UrgentLatencySupportUsPerState[i][j][k] < locals->UrgentLatency)
					locals->UrgentLatencySupport[i][j] = false;
			पूर्ण
		पूर्ण
	पूर्ण


	/*Prefetch Check*/
	क्रम (i = 0; i <= locals->soc.num_states; i++) अणु
		क्रम (j = 0; j < 2; j++) अणु
			locals->TotalNumberOfDCCActiveDPP[i][j] = 0;
			क्रम (k = 0; k < locals->NumberOfActivePlanes; k++) अणु
				अगर (locals->DCCEnable[k] == true) अणु
					locals->TotalNumberOfDCCActiveDPP[i][j] =
						locals->TotalNumberOfDCCActiveDPP[i][j] + locals->NoOfDPP[i][j][k];
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	CalculateMinAndMaxPrefetchMode(locals->AllowDRAMSelfRefreshOrDRAMClockChangeInVblank, &locals->MinPrefetchMode, &locals->MaxPrefetchMode);

	locals->MaxTotalVActiveRDBandwidth = 0;
	क्रम (k = 0; k < locals->NumberOfActivePlanes; k++) अणु
		locals->MaxTotalVActiveRDBandwidth = locals->MaxTotalVActiveRDBandwidth + locals->ReadBandwidth[k];
	पूर्ण

	क्रम (i = 0; i <= locals->soc.num_states; i++) अणु
		क्रम (j = 0; j < 2; j++) अणु
			क्रम (k = 0; k < locals->NumberOfActivePlanes; k++) अणु
				locals->NoOfDPPThisState[k] = locals->NoOfDPP[i][j][k];
				locals->RequiredDPPCLKThisState[k] = locals->RequiredDPPCLK[i][j][k];
				locals->SwathHeightYThisState[k] = locals->SwathHeightYPerState[i][j][k];
				locals->SwathHeightCThisState[k] = locals->SwathHeightCPerState[i][j][k];
				locals->SwathWidthYThisState[k] = locals->SwathWidthYPerState[i][j][k];
				mode_lib->vba.ProjectedDCFCLKDeepSleep[0][0] = dml_max(
						mode_lib->vba.ProjectedDCFCLKDeepSleep[0][0],
						mode_lib->vba.PixelClock[k] / 16.0);
				अगर (mode_lib->vba.BytePerPixelInDETC[k] == 0.0) अणु
					अगर (mode_lib->vba.VRatio[k] <= 1.0) अणु
						mode_lib->vba.ProjectedDCFCLKDeepSleep[0][0] =
								dml_max(
										mode_lib->vba.ProjectedDCFCLKDeepSleep[0][0],
										1.1
												* dml_उच्चमान(
														mode_lib->vba.BytePerPixelInDETY[k],
														1.0)
												/ 64.0
												* mode_lib->vba.HRatio[k]
												* mode_lib->vba.PixelClock[k]
												/ mode_lib->vba.NoOfDPP[i][j][k]);
					पूर्ण अन्यथा अणु
						mode_lib->vba.ProjectedDCFCLKDeepSleep[0][0] =
								dml_max(
										mode_lib->vba.ProjectedDCFCLKDeepSleep[0][0],
										1.1
												* dml_उच्चमान(
														mode_lib->vba.BytePerPixelInDETY[k],
														1.0)
												/ 64.0
												* mode_lib->vba.PSCL_FACTOR[k]
												* mode_lib->vba.RequiredDPPCLK[i][j][k]);
					पूर्ण
				पूर्ण अन्यथा अणु
					अगर (mode_lib->vba.VRatio[k] <= 1.0) अणु
						mode_lib->vba.ProjectedDCFCLKDeepSleep[0][0] =
								dml_max(
										mode_lib->vba.ProjectedDCFCLKDeepSleep[0][0],
										1.1
												* dml_उच्चमान(
														mode_lib->vba.BytePerPixelInDETY[k],
														1.0)
												/ 32.0
												* mode_lib->vba.HRatio[k]
												* mode_lib->vba.PixelClock[k]
												/ mode_lib->vba.NoOfDPP[i][j][k]);
					पूर्ण अन्यथा अणु
						mode_lib->vba.ProjectedDCFCLKDeepSleep[0][0] =
								dml_max(
										mode_lib->vba.ProjectedDCFCLKDeepSleep[0][0],
										1.1
												* dml_उच्चमान(
														mode_lib->vba.BytePerPixelInDETY[k],
														1.0)
												/ 32.0
												* mode_lib->vba.PSCL_FACTOR[k]
												* mode_lib->vba.RequiredDPPCLK[i][j][k]);
					पूर्ण
					अगर (mode_lib->vba.VRatio[k] / 2.0 <= 1.0) अणु
						mode_lib->vba.ProjectedDCFCLKDeepSleep[0][0] =
								dml_max(
										mode_lib->vba.ProjectedDCFCLKDeepSleep[0][0],
										1.1
												* dml_उच्चमान(
														mode_lib->vba.BytePerPixelInDETC[k],
														2.0)
												/ 32.0
												* mode_lib->vba.HRatio[k]
												/ 2.0
												* mode_lib->vba.PixelClock[k]
												/ mode_lib->vba.NoOfDPP[i][j][k]);
					पूर्ण अन्यथा अणु
						mode_lib->vba.ProjectedDCFCLKDeepSleep[0][0] =
								dml_max(
										mode_lib->vba.ProjectedDCFCLKDeepSleep[0][0],
										1.1
												* dml_उच्चमान(
														mode_lib->vba.BytePerPixelInDETC[k],
														2.0)
												/ 32.0
												* mode_lib->vba.PSCL_FACTOR_CHROMA[k]
												* mode_lib->vba.RequiredDPPCLK[i][j][k]);
					पूर्ण
				पूर्ण
			पूर्ण
			क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
				mode_lib->vba.PDEAndMetaPTEBytesPerFrameY = CalculateVMAndRowBytes(
						mode_lib,
						mode_lib->vba.DCCEnable[k],
						mode_lib->vba.Read256BlockHeightY[k],
						mode_lib->vba.Read256BlockWidthY[k],
						mode_lib->vba.SourcePixelFormat[k],
						mode_lib->vba.SurfaceTiling[k],
						dml_उच्चमान(mode_lib->vba.BytePerPixelInDETY[k], 1.0),
						mode_lib->vba.SourceScan[k],
						mode_lib->vba.ViewportWidth[k],
						mode_lib->vba.ViewportHeight[k],
						mode_lib->vba.SwathWidthYPerState[i][j][k],
						mode_lib->vba.GPUVMEnable,
						mode_lib->vba.VMMPageSize,
						mode_lib->vba.PTEBufferSizeInRequestsLuma,
						mode_lib->vba.PDEProcessingBufIn64KBReqs,
						mode_lib->vba.PitchY[k],
						mode_lib->vba.DCCMetaPitchY[k],
						&mode_lib->vba.MacroTileWidthY[k],
						&mode_lib->vba.MetaRowBytesY,
						&mode_lib->vba.DPTEBytesPerRowY,
						&mode_lib->vba.PTEBufferSizeNotExceededY[i][j][k],
						&mode_lib->vba.dpte_row_height[k],
						&mode_lib->vba.meta_row_height[k]);
				mode_lib->vba.PrefetchLinesY[0][0][k] = CalculatePrefetchSourceLines(
						mode_lib,
						mode_lib->vba.VRatio[k],
						mode_lib->vba.vtaps[k],
						mode_lib->vba.Interlace[k],
						mode_lib->vba.ProgressiveToInterlaceUnitInOPP,
						mode_lib->vba.SwathHeightYPerState[i][j][k],
						mode_lib->vba.ViewportYStartY[k],
						&mode_lib->vba.PrefillY[k],
						&mode_lib->vba.MaxNumSwY[k]);
				अगर ((mode_lib->vba.SourcePixelFormat[k] != dm_444_64
						&& mode_lib->vba.SourcePixelFormat[k] != dm_444_32
						&& mode_lib->vba.SourcePixelFormat[k] != dm_444_16
						&& mode_lib->vba.SourcePixelFormat[k] != dm_mono_16
						&& mode_lib->vba.SourcePixelFormat[k] != dm_mono_8)) अणु
					mode_lib->vba.PDEAndMetaPTEBytesPerFrameC = CalculateVMAndRowBytes(
							mode_lib,
							mode_lib->vba.DCCEnable[k],
							mode_lib->vba.Read256BlockHeightY[k],
							mode_lib->vba.Read256BlockWidthY[k],
							mode_lib->vba.SourcePixelFormat[k],
							mode_lib->vba.SurfaceTiling[k],
							dml_उच्चमान(mode_lib->vba.BytePerPixelInDETC[k], 2.0),
							mode_lib->vba.SourceScan[k],
							mode_lib->vba.ViewportWidth[k] / 2.0,
							mode_lib->vba.ViewportHeight[k] / 2.0,
							mode_lib->vba.SwathWidthYPerState[i][j][k] / 2.0,
							mode_lib->vba.GPUVMEnable,
							mode_lib->vba.VMMPageSize,
							mode_lib->vba.PTEBufferSizeInRequestsLuma,
							mode_lib->vba.PDEProcessingBufIn64KBReqs,
							mode_lib->vba.PitchC[k],
							0.0,
							&mode_lib->vba.MacroTileWidthC[k],
							&mode_lib->vba.MetaRowBytesC,
							&mode_lib->vba.DPTEBytesPerRowC,
							&mode_lib->vba.PTEBufferSizeNotExceededC[i][j][k],
							&mode_lib->vba.dpte_row_height_chroma[k],
							&mode_lib->vba.meta_row_height_chroma[k]);
					mode_lib->vba.PrefetchLinesC[0][0][k] = CalculatePrefetchSourceLines(
							mode_lib,
							mode_lib->vba.VRatio[k] / 2.0,
							mode_lib->vba.VTAPsChroma[k],
							mode_lib->vba.Interlace[k],
							mode_lib->vba.ProgressiveToInterlaceUnitInOPP,
							mode_lib->vba.SwathHeightCPerState[i][j][k],
							mode_lib->vba.ViewportYStartC[k],
							&mode_lib->vba.PrefillC[k],
							&mode_lib->vba.MaxNumSwC[k]);
				पूर्ण अन्यथा अणु
					mode_lib->vba.PDEAndMetaPTEBytesPerFrameC = 0.0;
					mode_lib->vba.MetaRowBytesC = 0.0;
					mode_lib->vba.DPTEBytesPerRowC = 0.0;
					locals->PrefetchLinesC[0][0][k] = 0.0;
					locals->PTEBufferSizeNotExceededC[i][j][k] = true;
					locals->PTEBufferSizeInRequestsForLuma = mode_lib->vba.PTEBufferSizeInRequestsLuma + mode_lib->vba.PTEBufferSizeInRequestsChroma;
				पूर्ण
				locals->PDEAndMetaPTEBytesPerFrame[0][0][k] =
						mode_lib->vba.PDEAndMetaPTEBytesPerFrameY + mode_lib->vba.PDEAndMetaPTEBytesPerFrameC;
				locals->MetaRowBytes[0][0][k] = mode_lib->vba.MetaRowBytesY + mode_lib->vba.MetaRowBytesC;
				locals->DPTEBytesPerRow[0][0][k] = mode_lib->vba.DPTEBytesPerRowY + mode_lib->vba.DPTEBytesPerRowC;

				CalculateActiveRowBandwidth(
						mode_lib->vba.GPUVMEnable,
						mode_lib->vba.SourcePixelFormat[k],
						mode_lib->vba.VRatio[k],
						mode_lib->vba.DCCEnable[k],
						mode_lib->vba.HTotal[k] / mode_lib->vba.PixelClock[k],
						mode_lib->vba.MetaRowBytesY,
						mode_lib->vba.MetaRowBytesC,
						mode_lib->vba.meta_row_height[k],
						mode_lib->vba.meta_row_height_chroma[k],
						mode_lib->vba.DPTEBytesPerRowY,
						mode_lib->vba.DPTEBytesPerRowC,
						mode_lib->vba.dpte_row_height[k],
						mode_lib->vba.dpte_row_height_chroma[k],
						&mode_lib->vba.meta_row_bw[k],
						&mode_lib->vba.dpte_row_bw[k],
						&mode_lib->vba.qual_row_bw[k]);
			पूर्ण
			mode_lib->vba.ExtraLatency =
					mode_lib->vba.UrgentRoundTripAndOutOfOrderLatencyPerState[i]
							+ (mode_lib->vba.TotalNumberOfActiveDPP[i][j]
									* mode_lib->vba.PixelChunkSizeInKByte
									+ mode_lib->vba.TotalNumberOfDCCActiveDPP[i][j]
											* mode_lib->vba.MetaChunkSize)
									* 1024.0
									/ mode_lib->vba.ReturnBWPerState[i][0];
			अगर (mode_lib->vba.GPUVMEnable == true) अणु
				mode_lib->vba.ExtraLatency = mode_lib->vba.ExtraLatency
						+ mode_lib->vba.TotalNumberOfActiveDPP[i][j]
								* mode_lib->vba.PTEGroupSize
								/ mode_lib->vba.ReturnBWPerState[i][0];
			पूर्ण
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
			क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
				क्रम (m = 0; m < locals->NumberOfCursors[k]; m++)
					locals->cursor_bw[k] = locals->NumberOfCursors[k] * locals->CursorWidth[k][m] * locals->CursorBPP[k][m]
						/ 8 / (locals->HTotal[k] / locals->PixelClock[k]) * locals->VRatio[k];
			पूर्ण

			क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
				locals->MaximumVStartup[0][0][k] = mode_lib->vba.VTotal[k] - mode_lib->vba.VActive[k]
					- dml_max(1.0, dml_उच्चमान(locals->WritebackDelay[i][k] / (mode_lib->vba.HTotal[k] / mode_lib->vba.PixelClock[k]), 1.0));
			पूर्ण

			mode_lib->vba.NextPrefetchMode = mode_lib->vba.MinPrefetchMode;
			करो अणु
				mode_lib->vba.PrefetchMode[i][j] = mode_lib->vba.NextPrefetchMode;
				mode_lib->vba.NextPrefetchMode = mode_lib->vba.NextPrefetchMode + 1;

				mode_lib->vba.TWait = CalculateTWait(
						mode_lib->vba.PrefetchMode[i][j],
						mode_lib->vba.DRAMClockChangeLatency,
						mode_lib->vba.UrgentLatency,
						mode_lib->vba.SREnterPlusExitTime);
				क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु

					अगर (mode_lib->vba.XFCEnabled[k] == true) अणु
						mode_lib->vba.XFCRemoteSurfaceFlipDelay =
								CalculateRemoteSurfaceFlipDelay(
										mode_lib,
										mode_lib->vba.VRatio[k],
										locals->SwathWidthYPerState[i][j][k],
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

					CalculateDelayAfterScaler(mode_lib, mode_lib->vba.ReturnBWPerState[i][0], mode_lib->vba.ReadBandwidthLuma[k], mode_lib->vba.ReadBandwidthChroma[k], mode_lib->vba.MaxTotalVActiveRDBandwidth,
						mode_lib->vba.DisplayPipeLineDeliveryTimeLuma[k], mode_lib->vba.DisplayPipeLineDeliveryTimeChroma[k],
						mode_lib->vba.RequiredDPPCLK[i][j][k], mode_lib->vba.RequiredDISPCLK[i][j], mode_lib->vba.PixelClock[k], mode_lib->vba.DSCDelayPerState[i][k], mode_lib->vba.NoOfDPP[i][j][k], mode_lib->vba.ScalerEnabled[k], mode_lib->vba.NumberOfCursors[k],
						mode_lib->vba.DPPCLKDelaySubtotal, mode_lib->vba.DPPCLKDelaySCL, mode_lib->vba.DPPCLKDelaySCLLBOnly, mode_lib->vba.DPPCLKDelayCNVCFormater, mode_lib->vba.DPPCLKDelayCNVCCursor, mode_lib->vba.DISPCLKDelaySubtotal,
						mode_lib->vba.SwathWidthYPerState[i][j][k] / mode_lib->vba.HRatio[k], mode_lib->vba.OutputFormat[k], mode_lib->vba.HTotal[k],
						mode_lib->vba.SwathWidthYSingleDPP[k], mode_lib->vba.BytePerPixelInDETY[k], mode_lib->vba.BytePerPixelInDETC[k], mode_lib->vba.SwathHeightYThisState[k], mode_lib->vba.SwathHeightCThisState[k], mode_lib->vba.Interlace[k], mode_lib->vba.ProgressiveToInterlaceUnitInOPP,
						&mode_lib->vba.DSTXAfterScaler[k], &mode_lib->vba.DSTYAfterScaler[k]);

					mode_lib->vba.IsErrorResult[i][j][k] =
							CalculatePrefetchSchedule(
									mode_lib,
									mode_lib->vba.RequiredDPPCLK[i][j][k],
									mode_lib->vba.RequiredDISPCLK[i][j],
									mode_lib->vba.PixelClock[k],
									mode_lib->vba.ProjectedDCFCLKDeepSleep[0][0],
									mode_lib->vba.NoOfDPP[i][j][k],
									mode_lib->vba.NumberOfCursors[k],
									mode_lib->vba.VTotal[k]
											- mode_lib->vba.VActive[k],
									mode_lib->vba.HTotal[k],
									mode_lib->vba.MaxInterDCNTileRepeaters,
									mode_lib->vba.MaximumVStartup[0][0][k],
									mode_lib->vba.GPUVMMaxPageTableLevels,
									mode_lib->vba.GPUVMEnable,
									mode_lib->vba.DynamicMetadataEnable[k],
									mode_lib->vba.DynamicMetadataLinesBeक्रमeActiveRequired[k],
									mode_lib->vba.DynamicMetadataTransmittedBytes[k],
									mode_lib->vba.DCCEnable[k],
									mode_lib->vba.UrgentLatencyPixelDataOnly,
									mode_lib->vba.ExtraLatency,
									mode_lib->vba.TimeCalc,
									mode_lib->vba.PDEAndMetaPTEBytesPerFrame[0][0][k],
									mode_lib->vba.MetaRowBytes[0][0][k],
									mode_lib->vba.DPTEBytesPerRow[0][0][k],
									mode_lib->vba.PrefetchLinesY[0][0][k],
									mode_lib->vba.SwathWidthYPerState[i][j][k],
									mode_lib->vba.BytePerPixelInDETY[k],
									mode_lib->vba.PrefillY[k],
									mode_lib->vba.MaxNumSwY[k],
									mode_lib->vba.PrefetchLinesC[0][0][k],
									mode_lib->vba.BytePerPixelInDETC[k],
									mode_lib->vba.PrefillC[k],
									mode_lib->vba.MaxNumSwC[k],
									mode_lib->vba.SwathHeightYPerState[i][j][k],
									mode_lib->vba.SwathHeightCPerState[i][j][k],
									mode_lib->vba.TWait,
									mode_lib->vba.XFCEnabled[k],
									mode_lib->vba.XFCRemoteSurfaceFlipDelay,
									mode_lib->vba.Interlace[k],
									mode_lib->vba.ProgressiveToInterlaceUnitInOPP,
									mode_lib->vba.DSTXAfterScaler[k],
									mode_lib->vba.DSTYAfterScaler[k],
									&mode_lib->vba.LineTimesForPrefetch[k],
									&mode_lib->vba.PrefetchBW[k],
									&mode_lib->vba.LinesForMetaPTE[k],
									&mode_lib->vba.LinesForMetaAndDPTERow[k],
									&mode_lib->vba.VRatioPreY[i][j][k],
									&mode_lib->vba.VRatioPreC[i][j][k],
									&mode_lib->vba.RequiredPrefetchPixelDataBWLuma[i][j][k],
									&mode_lib->vba.Tno_bw[k],
									&mode_lib->vba.VUpdateOffsetPix[k],
									&mode_lib->vba.VUpdateWidthPix[k],
									&mode_lib->vba.VReadyOffsetPix[k]);
				पूर्ण
				mode_lib->vba.MaximumReadBandwidthWithoutPrefetch = 0.0;
				mode_lib->vba.MaximumReadBandwidthWithPrefetch = 0.0;
				locals->prefetch_vm_bw_valid = true;
				locals->prefetch_row_bw_valid = true;
				क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
					अगर (locals->PDEAndMetaPTEBytesPerFrame[0][0][k] == 0)
						locals->prefetch_vm_bw[k] = 0;
					अन्यथा अगर (locals->LinesForMetaPTE[k] > 0)
						locals->prefetch_vm_bw[k] = locals->PDEAndMetaPTEBytesPerFrame[0][0][k]
							/ (locals->LinesForMetaPTE[k] * locals->HTotal[k] / locals->PixelClock[k]);
					अन्यथा अणु
						locals->prefetch_vm_bw[k] = 0;
						locals->prefetch_vm_bw_valid = false;
					पूर्ण
					अगर (locals->MetaRowBytes[0][0][k] + locals->DPTEBytesPerRow[0][0][k] == 0)
						locals->prefetch_row_bw[k] = 0;
					अन्यथा अगर (locals->LinesForMetaAndDPTERow[k] > 0)
						locals->prefetch_row_bw[k] = (locals->MetaRowBytes[0][0][k] + locals->DPTEBytesPerRow[0][0][k])
							/ (locals->LinesForMetaAndDPTERow[k] * locals->HTotal[k] / locals->PixelClock[k]);
					अन्यथा अणु
						locals->prefetch_row_bw[k] = 0;
						locals->prefetch_row_bw_valid = false;
					पूर्ण

					mode_lib->vba.MaximumReadBandwidthWithoutPrefetch = mode_lib->vba.MaximumReadBandwidthWithPrefetch
							+ mode_lib->vba.cursor_bw[k] + mode_lib->vba.ReadBandwidth[k] + mode_lib->vba.meta_row_bw[k] + mode_lib->vba.dpte_row_bw[k];
					mode_lib->vba.MaximumReadBandwidthWithPrefetch =
							mode_lib->vba.MaximumReadBandwidthWithPrefetch
									+ mode_lib->vba.cursor_bw[k]
									+ dml_max3(
											mode_lib->vba.prefetch_vm_bw[k],
											mode_lib->vba.prefetch_row_bw[k],
											dml_max(mode_lib->vba.ReadBandwidth[k],
											mode_lib->vba.RequiredPrefetchPixelDataBWLuma[i][j][k])
											+ mode_lib->vba.meta_row_bw[k] + mode_lib->vba.dpte_row_bw[k]);
				पूर्ण
				locals->BandwidthWithoutPrefetchSupported[i][0] = true;
				अगर (mode_lib->vba.MaximumReadBandwidthWithoutPrefetch > locals->ReturnBWPerState[i][0]) अणु
					locals->BandwidthWithoutPrefetchSupported[i][0] = false;
				पूर्ण

				locals->PrefetchSupported[i][j] = true;
				अगर (mode_lib->vba.MaximumReadBandwidthWithPrefetch > locals->ReturnBWPerState[i][0]) अणु
					locals->PrefetchSupported[i][j] = false;
				पूर्ण
				क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
					अगर (locals->LineTimesForPrefetch[k] < 2.0
							|| locals->LinesForMetaPTE[k] >= 8.0
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
			पूर्ण जबतक ((locals->PrefetchSupported[i][j] != true || locals->VRatioInPrefetchSupported[i][j] != true)
					&& mode_lib->vba.NextPrefetchMode < mode_lib->vba.MaxPrefetchMode);

			अगर (mode_lib->vba.PrefetchSupported[i][j] == true
					&& mode_lib->vba.VRatioInPrefetchSupported[i][j] == true) अणु
				mode_lib->vba.BandwidthAvailableForImmediateFlip =
						mode_lib->vba.ReturnBWPerState[i][0];
				क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
					mode_lib->vba.BandwidthAvailableForImmediateFlip =
							mode_lib->vba.BandwidthAvailableForImmediateFlip
									- mode_lib->vba.cursor_bw[k]
									- dml_max(
											mode_lib->vba.ReadBandwidth[k] + mode_lib->vba.qual_row_bw[k],
											mode_lib->vba.PrefetchBW[k]);
				पूर्ण
				क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
					mode_lib->vba.ImmediateFlipBytes[k] = 0.0;
					अगर ((mode_lib->vba.SourcePixelFormat[k] != dm_420_8
							&& mode_lib->vba.SourcePixelFormat[k] != dm_420_10)) अणु
						mode_lib->vba.ImmediateFlipBytes[k] =
								mode_lib->vba.PDEAndMetaPTEBytesPerFrame[0][0][k]
										+ mode_lib->vba.MetaRowBytes[0][0][k]
										+ mode_lib->vba.DPTEBytesPerRow[0][0][k];
					पूर्ण
				पूर्ण
				mode_lib->vba.TotImmediateFlipBytes = 0.0;
				क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
					अगर ((mode_lib->vba.SourcePixelFormat[k] != dm_420_8
							&& mode_lib->vba.SourcePixelFormat[k] != dm_420_10)) अणु
						mode_lib->vba.TotImmediateFlipBytes =
								mode_lib->vba.TotImmediateFlipBytes
										+ mode_lib->vba.ImmediateFlipBytes[k];
					पूर्ण
				पूर्ण

				क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
					CalculateFlipSchedule(
							mode_lib,
							mode_lib->vba.ExtraLatency,
							mode_lib->vba.UrgentLatencyPixelDataOnly,
							mode_lib->vba.GPUVMMaxPageTableLevels,
							mode_lib->vba.GPUVMEnable,
							mode_lib->vba.BandwidthAvailableForImmediateFlip,
							mode_lib->vba.TotImmediateFlipBytes,
							mode_lib->vba.SourcePixelFormat[k],
							mode_lib->vba.ImmediateFlipBytes[k],
							mode_lib->vba.HTotal[k]
									/ mode_lib->vba.PixelClock[k],
							mode_lib->vba.VRatio[k],
							mode_lib->vba.Tno_bw[k],
							mode_lib->vba.PDEAndMetaPTEBytesPerFrame[0][0][k],
							mode_lib->vba.MetaRowBytes[0][0][k],
							mode_lib->vba.DPTEBytesPerRow[0][0][k],
							mode_lib->vba.DCCEnable[k],
							mode_lib->vba.dpte_row_height[k],
							mode_lib->vba.meta_row_height[k],
							mode_lib->vba.qual_row_bw[k],
							&mode_lib->vba.DestinationLinesToRequestVMInImmediateFlip[k],
							&mode_lib->vba.DestinationLinesToRequestRowInImmediateFlip[k],
							&mode_lib->vba.final_flip_bw[k],
							&mode_lib->vba.ImmediateFlipSupportedForPipe[k]);
				पूर्ण
				mode_lib->vba.total_dcn_पढ़ो_bw_with_flip = 0.0;
				क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
					mode_lib->vba.total_dcn_पढ़ो_bw_with_flip =
							mode_lib->vba.total_dcn_पढ़ो_bw_with_flip
									+ mode_lib->vba.cursor_bw[k]
									+ dml_max3(
											mode_lib->vba.prefetch_vm_bw[k],
											mode_lib->vba.prefetch_row_bw[k],
											mode_lib->vba.final_flip_bw[k]
													+ dml_max(
															mode_lib->vba.ReadBandwidth[k],
															mode_lib->vba.RequiredPrefetchPixelDataBWLuma[i][j][k]));
				पूर्ण
				mode_lib->vba.ImmediateFlipSupportedForState[i][j] = true;
				अगर (mode_lib->vba.total_dcn_पढ़ो_bw_with_flip
						> mode_lib->vba.ReturnBWPerState[i][0]) अणु
					mode_lib->vba.ImmediateFlipSupportedForState[i][j] = false;
				पूर्ण
				क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
					अगर (mode_lib->vba.ImmediateFlipSupportedForPipe[k] == false) अणु
						mode_lib->vba.ImmediateFlipSupportedForState[i][j] = false;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अणु
				mode_lib->vba.ImmediateFlipSupportedForState[i][j] = false;
			पूर्ण
		पूर्ण
	पूर्ण

	/*Vertical Active BW support*/
	क्रम (i = 0; i <= mode_lib->vba.soc.num_states; i++) अणु
		mode_lib->vba.MaxTotalVerticalActiveAvailableBandwidth[i][0] = dml_min(mode_lib->vba.ReturnBusWidth *
				mode_lib->vba.DCFCLKPerState[i], mode_lib->vba.FabricAndDRAMBandwidthPerState[i] * 1000) *
				mode_lib->vba.MaxAveragePercentOfIdealDRAMBWDisplayCanUseInNormalSystemOperation / 100;
		अगर (mode_lib->vba.MaxTotalVActiveRDBandwidth <= mode_lib->vba.MaxTotalVerticalActiveAvailableBandwidth[i][0])
			mode_lib->vba.TotalVerticalActiveBandwidthSupport[i][0] = true;
		अन्यथा
			mode_lib->vba.TotalVerticalActiveBandwidthSupport[i][0] = false;
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
		क्रम (j = 0; j < 2; j++) अणु
			अगर (mode_lib->vba.CursorWidth[k][j] > 0.0) अणु
				अगर (dml_न्यूनमान(
						dml_न्यूनमान(
								mode_lib->vba.CursorBufferSize
										- mode_lib->vba.CursorChunkSize,
								mode_lib->vba.CursorChunkSize) * 1024.0
								/ (mode_lib->vba.CursorWidth[k][j]
										* mode_lib->vba.CursorBPP[k][j]
										/ 8.0),
						1.0)
						* (mode_lib->vba.HTotal[k] / mode_lib->vba.PixelClock[k])
						/ mode_lib->vba.VRatio[k] < mode_lib->vba.UrgentLatencyPixelDataOnly
						|| (mode_lib->vba.CursorBPP[k][j] == 64.0
								&& mode_lib->vba.Cursor64BppSupport == false)) अणु
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

			अगर (mode_lib->vba.ScaleRatioAndTapsSupport != true) अणु
				status = DML_FAIL_SCALE_RATIO_TAP;
			पूर्ण अन्यथा अगर (mode_lib->vba.SourceFormatPixelAndScanSupport != true) अणु
				status = DML_FAIL_SOURCE_PIXEL_FORMAT;
			पूर्ण अन्यथा अगर (locals->ViewportSizeSupport[i][0] != true) अणु
				status = DML_FAIL_VIEWPORT_SIZE;
			पूर्ण अन्यथा अगर (locals->DIOSupport[i] != true) अणु
				status = DML_FAIL_DIO_SUPPORT;
			पूर्ण अन्यथा अगर (locals->NotEnoughDSCUnits[i] != false) अणु
				status = DML_FAIL_NOT_ENOUGH_DSC;
			पूर्ण अन्यथा अगर (locals->DSCCLKRequiredMoreThanSupported[i] != false) अणु
				status = DML_FAIL_DSC_CLK_REQUIRED;
			पूर्ण अन्यथा अगर (locals->UrgentLatencySupport[i][j] != true) अणु
				status = DML_FAIL_URGENT_LATENCY;
			पूर्ण अन्यथा अगर (locals->ROBSupport[i][0] != true) अणु
				status = DML_FAIL_REORDERING_BUFFER;
			पूर्ण अन्यथा अगर (locals->DISPCLK_DPPCLK_Support[i][j] != true) अणु
				status = DML_FAIL_DISPCLK_DPPCLK;
			पूर्ण अन्यथा अगर (locals->TotalAvailablePipesSupport[i][j] != true) अणु
				status = DML_FAIL_TOTAL_AVAILABLE_PIPES;
			पूर्ण अन्यथा अगर (mode_lib->vba.NumberOfOTGSupport != true) अणु
				status = DML_FAIL_NUM_OTG;
			पूर्ण अन्यथा अगर (mode_lib->vba.WritebackModeSupport != true) अणु
				status = DML_FAIL_WRITEBACK_MODE;
			पूर्ण अन्यथा अगर (mode_lib->vba.WritebackLatencySupport != true) अणु
				status = DML_FAIL_WRITEBACK_LATENCY;
			पूर्ण अन्यथा अगर (mode_lib->vba.WritebackScaleRatioAndTapsSupport != true) अणु
				status = DML_FAIL_WRITEBACK_SCALE_RATIO_TAP;
			पूर्ण अन्यथा अगर (mode_lib->vba.CursorSupport != true) अणु
				status = DML_FAIL_CURSOR_SUPPORT;
			पूर्ण अन्यथा अगर (mode_lib->vba.PitchSupport != true) अणु
				status = DML_FAIL_PITCH_SUPPORT;
			पूर्ण अन्यथा अगर (locals->PrefetchSupported[i][j] != true) अणु
				status = DML_FAIL_PREFETCH_SUPPORT;
			पूर्ण अन्यथा अगर (locals->TotalVerticalActiveBandwidthSupport[i][0] != true) अणु
				status = DML_FAIL_TOTAL_V_ACTIVE_BW;
			पूर्ण अन्यथा अगर (locals->VRatioInPrefetchSupported[i][j] != true) अणु
				status = DML_FAIL_V_RATIO_PREFETCH;
			पूर्ण अन्यथा अगर (locals->PTEBufferSizeNotExceeded[i][j] != true) अणु
				status = DML_FAIL_PTE_BUFFER_SIZE;
			पूर्ण अन्यथा अगर (mode_lib->vba.NonsupportedDSCInputBPC != false) अणु
				status = DML_FAIL_DSC_INPUT_BPC;
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
						|| mode_lib->vba.WhenToDoMPCCombine == dm_mpc_always_when_possible)) अणु
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
	mode_lib->vba.FabricAndDRAMBandwidth = locals->FabricAndDRAMBandwidthPerState[mode_lib->vba.VoltageLevel];
	क्रम (k = 0; k <= mode_lib->vba.NumberOfActivePlanes - 1; k++) अणु
		अगर (mode_lib->vba.BlendingAndTiming[k] == k) अणु
			mode_lib->vba.ODMCombineEnabled[k] =
					locals->ODMCombineEnablePerState[mode_lib->vba.VoltageLevel][k];
		पूर्ण अन्यथा अणु
			mode_lib->vba.ODMCombineEnabled[k] = 0;
		पूर्ण
		mode_lib->vba.DSCEnabled[k] =
				locals->RequiresDSC[mode_lib->vba.VoltageLevel][k];
		mode_lib->vba.OutputBpp[k] =
				locals->OutputBppPerState[mode_lib->vba.VoltageLevel][k];
	पूर्ण
पूर्ण
