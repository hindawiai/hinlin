<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
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
#अगर_अघोषित __DAL_DDC_SERVICE_TYPES_H__
#घोषणा __DAL_DDC_SERVICE_TYPES_H__

/* 0010FA करोngles (ST Micro) बाह्यal converter chip id */
#घोषणा DP_BRANCH_DEVICE_ID_0010FA 0x0010FA
/* 0022B9 बाह्यal converter chip id */
#घोषणा DP_BRANCH_DEVICE_ID_0022B9 0x0022B9
#घोषणा DP_BRANCH_DEVICE_ID_00001A 0x00001A
#घोषणा DP_BRANCH_DEVICE_ID_0080E1 0x0080e1
#घोषणा DP_BRANCH_DEVICE_ID_90CC24 0x90CC24
#घोषणा DP_BRANCH_DEVICE_ID_00E04C 0x00E04C
#घोषणा DP_BRANCH_DEVICE_ID_006037 0x006037

क्रमागत ddc_result अणु
	DDC_RESULT_UNKNOWN = 0,
	DDC_RESULT_SUCESSFULL,
	DDC_RESULT_FAILED_CHANNEL_BUSY,
	DDC_RESULT_FAILED_TIMEOUT,
	DDC_RESULT_FAILED_PROTOCOL_ERROR,
	DDC_RESULT_FAILED_NACK,
	DDC_RESULT_FAILED_INCOMPLETE,
	DDC_RESULT_FAILED_OPERATION,
	DDC_RESULT_FAILED_INVALID_OPERATION,
	DDC_RESULT_FAILED_BUFFER_OVERFLOW,
	DDC_RESULT_FAILED_HPD_DISCON
पूर्ण;

क्रमागत ddc_service_type अणु
	DDC_SERVICE_TYPE_CONNECTOR,
	DDC_SERVICE_TYPE_DISPLAY_PORT_MST,
पूर्ण;

/**
 * display sink capability
 */
काष्ठा display_sink_capability अणु
	/* करोngle type (DP converter, CV smart करोngle) */
	क्रमागत display_करोngle_type करोngle_type;

	/**********************************************************
	 capabilities going INTO SINK DEVICE (stream capabilities)
	 **********************************************************/
	/* Dongle's करोwnstream count. */
	uपूर्णांक32_t करोwnstrm_sink_count;
	/* Is करोngle's करोwnstream count info field (करोwnstrm_sink_count)
	 * valid. */
	bool करोwnstrm_sink_count_valid;

	/* Maximum additional audio delay in microsecond (us) */
	uपूर्णांक32_t additional_audio_delay;
	/* Audio latency value in microsecond (us) */
	uपूर्णांक32_t audio_latency;
	/* Interlace video latency value in microsecond (us) */
	uपूर्णांक32_t video_latency_पूर्णांकerlace;
	/* Progressive video latency value in microsecond (us) */
	uपूर्णांक32_t video_latency_progressive;
	/* Dongle caps: Maximum pixel घड़ी supported over करोngle क्रम HDMI */
	uपूर्णांक32_t max_hdmi_pixel_घड़ी;
	/* Dongle caps: Maximum deep color supported over करोngle क्रम HDMI */
	क्रमागत dc_color_depth max_hdmi_deep_color;

	/************************************************************
	 capabilities going OUT OF SOURCE DEVICE (link capabilities)
	 ************************************************************/
	/* support क्रम Spपढ़ो Spectrum(SS) */
	bool ss_supported;
	/* DP link settings (laneCount, linkRate, Spपढ़ो) */
	uपूर्णांक32_t dp_link_lane_count;
	uपूर्णांक32_t dp_link_rate;
	uपूर्णांक32_t dp_link_spead;

	/* If करोngle_type == DISPLAY_DONGLE_DP_HDMI_CONVERTER,
	indicates 'Frame Sequential-to-lllFrame Pack' conversion capability.*/
	bool is_dp_hdmi_s3d_converter;
	/* to check अगर we have queried the display capability
	 * क्रम eDP panel alपढ़ोy. */
	bool is_edp_sink_cap_valid;

	क्रमागत ddc_transaction_type transaction_type;
	क्रमागत संकेत_type संकेत;
पूर्ण;

काष्ठा av_sync_data अणु
	uपूर्णांक8_t av_granularity;/* DPCD 00023h */
	uपूर्णांक8_t aud_dec_lat1;/* DPCD 00024h */
	uपूर्णांक8_t aud_dec_lat2;/* DPCD 00025h */
	uपूर्णांक8_t aud_pp_lat1;/* DPCD 00026h */
	uपूर्णांक8_t aud_pp_lat2;/* DPCD 00027h */
	uपूर्णांक8_t vid_पूर्णांकer_lat;/* DPCD 00028h */
	uपूर्णांक8_t vid_prog_lat;/* DPCD 00029h */
	uपूर्णांक8_t aud_del_ins1;/* DPCD 0002Bh */
	uपूर्णांक8_t aud_del_ins2;/* DPCD 0002Ch */
	uपूर्णांक8_t aud_del_ins3;/* DPCD 0002Dh */
पूर्ण;

#पूर्ण_अगर /* __DAL_DDC_SERVICE_TYPES_H__ */
