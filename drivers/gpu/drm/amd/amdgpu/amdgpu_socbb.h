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
#अगर_अघोषित __AMDGPU_SOCBB_H__
#घोषणा __AMDGPU_SOCBB_H__

काष्ठा gpu_info_voltage_scaling_v1_0 अणु
	uपूर्णांक32_t state;
	uपूर्णांक32_t dscclk_mhz;
	uपूर्णांक32_t dcfclk_mhz;
	uपूर्णांक32_t socclk_mhz;
	uपूर्णांक32_t dram_speed_mts;
	uपूर्णांक32_t fabricclk_mhz;
	uपूर्णांक32_t dispclk_mhz;
	uपूर्णांक32_t phyclk_mhz;
	uपूर्णांक32_t dppclk_mhz;
पूर्ण;

काष्ठा gpu_info_soc_bounding_box_v1_0 अणु
	uपूर्णांक32_t sr_निकास_समय_us;
	uपूर्णांक32_t sr_enter_plus_निकास_समय_us;
	uपूर्णांक32_t urgent_latency_us;
	uपूर्णांक32_t urgent_latency_pixel_data_only_us;
	uपूर्णांक32_t urgent_latency_pixel_mixed_with_vm_data_us;
	uपूर्णांक32_t urgent_latency_vm_data_only_us;
	uपूर्णांक32_t ग_लिखोback_latency_us;
	uपूर्णांक32_t ideal_dram_bw_after_urgent_percent;
	uपूर्णांक32_t pct_ideal_dram_sdp_bw_after_urgent_pixel_only; // PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelDataOnly
	uपूर्णांक32_t pct_ideal_dram_sdp_bw_after_urgent_pixel_and_vm;
	uपूर्णांक32_t pct_ideal_dram_sdp_bw_after_urgent_vm_only;
	uपूर्णांक32_t max_avg_sdp_bw_use_normal_percent;
	uपूर्णांक32_t max_avg_dram_bw_use_normal_percent;
	uपूर्णांक32_t max_request_size_bytes;
	uपूर्णांक32_t करोwnspपढ़ो_percent;
	uपूर्णांक32_t dram_page_खोलो_समय_ns;
	uपूर्णांक32_t dram_rw_turnaround_समय_ns;
	uपूर्णांक32_t dram_वापस_buffer_per_channel_bytes;
	uपूर्णांक32_t dram_channel_width_bytes;
	uपूर्णांक32_t fabric_datapath_to_dcn_data_वापस_bytes;
	uपूर्णांक32_t dcn_करोwnspपढ़ो_percent;
	uपूर्णांक32_t dispclk_dppclk_vco_speed_mhz;
	uपूर्णांक32_t dfs_vco_period_ps;
	uपूर्णांक32_t urgent_out_of_order_वापस_per_channel_pixel_only_bytes;
	uपूर्णांक32_t urgent_out_of_order_वापस_per_channel_pixel_and_vm_bytes;
	uपूर्णांक32_t urgent_out_of_order_वापस_per_channel_vm_only_bytes;
	uपूर्णांक32_t round_trip_ping_latency_dcfclk_cycles;
	uपूर्णांक32_t urgent_out_of_order_वापस_per_channel_bytes;
	uपूर्णांक32_t channel_पूर्णांकerleave_bytes;
	uपूर्णांक32_t num_banks;
	uपूर्णांक32_t num_chans;
	uपूर्णांक32_t vmm_page_size_bytes;
	uपूर्णांक32_t dram_घड़ी_change_latency_us;
	uपूर्णांक32_t ग_लिखोback_dram_घड़ी_change_latency_us;
	uपूर्णांक32_t वापस_bus_width_bytes;
	uपूर्णांक32_t voltage_override;
	uपूर्णांक32_t xfc_bus_transport_समय_us;
	uपूर्णांक32_t xfc_xbuf_latency_tolerance_us;
	uपूर्णांक32_t use_urgent_burst_bw;
	uपूर्णांक32_t num_states;
	काष्ठा gpu_info_voltage_scaling_v1_0 घड़ी_limits[8];
पूर्ण;

#पूर्ण_अगर
