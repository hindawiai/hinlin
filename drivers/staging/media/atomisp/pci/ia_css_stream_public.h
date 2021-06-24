<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
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

#अगर_अघोषित __IA_CSS_STREAM_PUBLIC_H
#घोषणा __IA_CSS_STREAM_PUBLIC_H

/* @file
 * This file contains support क्रम configuring and controlling streams
 */

#समावेश <type_support.h>
#समावेश "ia_css_types.h"
#समावेश "ia_css_pipe_public.h"
#समावेश "ia_css_metadata.h"
#समावेश "ia_css_tpg.h"
#समावेश "ia_css_prbs.h"
#समावेश "ia_css_input_port.h"

/* Input modes, these क्रमागतerate all supported input modes.
 *  Note that not all ISP modes support all input modes.
 */
क्रमागत ia_css_input_mode अणु
	IA_CSS_INPUT_MODE_SENSOR, /** data from sensor */
	IA_CSS_INPUT_MODE_FIFO,   /** data from input-fअगरo */
	IA_CSS_INPUT_MODE_TPG,    /** data from test-pattern generator */
	IA_CSS_INPUT_MODE_PRBS,   /** data from pseuकरो-अक्रमom bit stream */
	IA_CSS_INPUT_MODE_MEMORY, /** data from a frame in memory */
	IA_CSS_INPUT_MODE_BUFFERED_SENSOR /** data is sent through mipi buffer */
पूर्ण;

/* Structure of the MIPI buffer configuration
 */
काष्ठा ia_css_mipi_buffer_config अणु
	अचिन्हित पूर्णांक size_mem_words; /** The frame size in the प्रणाली memory
					  words (32B) */
	bool contiguous;	     /** Allocated memory physically
					  contiguously or not. \deprecatedअणुWill be false always.पूर्ण*/
	अचिन्हित पूर्णांक nof_mipi_buffers; /** The number of MIPI buffers required क्रम this
					stream */
पूर्ण;

क्रमागत अणु
	IA_CSS_STREAM_ISYS_STREAM_0 = 0,
	IA_CSS_STREAM_DEFAULT_ISYS_STREAM_IDX = IA_CSS_STREAM_ISYS_STREAM_0,
	IA_CSS_STREAM_ISYS_STREAM_1,
	IA_CSS_STREAM_MAX_ISYS_STREAM_PER_CH
पूर्ण;

/* This is input data configuration क्रम one MIPI data type. We can have
 *  multiple of this in one भव channel.
 */
काष्ठा ia_css_stream_isys_stream_config अणु
	काष्ठा ia_css_resolution  input_res; /** Resolution of input data */
	क्रमागत atomisp_input_क्रमmat क्रमmat; /** Format of input stream. This data
					       क्रमmat will be mapped to MIPI data
					       type पूर्णांकernally. */
	पूर्णांक linked_isys_stream_id; /** शेष value is -1, other value means
							current isys_stream shares the same buffer with
							indicated isys_stream*/
	bool valid; /** indicate whether other fields have valid value */
पूर्ण;

काष्ठा ia_css_stream_input_config अणु
	काष्ठा ia_css_resolution  input_res; /** Resolution of input data */
	काष्ठा ia_css_resolution  effective_res; /** Resolution of input data.
							Used क्रम CSS 2400/1 System and deprecated क्रम other
							प्रणालीs (replaced by input_effective_res in
							ia_css_pipe_config) */
	क्रमागत atomisp_input_क्रमmat क्रमmat; /** Format of input stream. This data
					       क्रमmat will be mapped to MIPI data
					       type पूर्णांकernally. */
	क्रमागत ia_css_bayer_order bayer_order; /** Bayer order क्रम RAW streams */
पूर्ण;

/* Input stream description. This describes how input will flow पूर्णांकo the
 *  CSS. This is used to program the CSS hardware.
 */
काष्ठा ia_css_stream_config अणु
	क्रमागत ia_css_input_mode    mode; /** Input mode */
	जोड़ अणु
		काष्ठा ia_css_input_port  port; /** Port, क्रम sensor only. */
		काष्ठा ia_css_tpg_config  tpg;  /** TPG configuration */
		काष्ठा ia_css_prbs_config prbs; /** PRBS configuration */
	पूर्ण source; /** Source of input data */
	अचिन्हित पूर्णांक	      channel_id; /** Channel on which input data
						   will arrive. Use this field
						   to specअगरy भव channel id.
						   Valid values are: 0, 1, 2, 3 */
	काष्ठा ia_css_stream_isys_stream_config
		isys_config[IA_CSS_STREAM_MAX_ISYS_STREAM_PER_CH];
	काष्ठा ia_css_stream_input_config input_config;

	/* Currently, Android and Winकरोws platक्रमms पूर्णांकerpret the binning_factor parameter
	 * dअगरferently. In Android, the binning factor is expressed in the क्रमm
	 * 2^N * 2^N, whereas in Winकरोws platक्रमm, the binning factor is N*N
	 * To use the Winकरोws method of specअगरication, the caller has to define
	 * macro USE_WINDOWS_BINNING_FACTOR. This is क्रम backward compatibility only
	 * and will be deprecated. In the future,all platक्रमms will use the N*N method
	 */
	/* ISP2401 */
	अचिन्हित पूर्णांक sensor_binning_factor; /** Binning factor used by sensor
						 to produce image data. This is
						 used क्रम shading correction. */
	अचिन्हित पूर्णांक pixels_per_घड़ी; /** Number of pixels per घड़ी, which can be
					    1, 2 or 4. */
	bool online; /** offline will activate RAW copy on SP, use this क्रम
			  continuous capture. */
	/* ISYS2401 usage: ISP receives data directly from sensor, no copy. */
	अचिन्हित पूर्णांक init_num_cont_raw_buf; /** initial number of raw buffers to
					     allocate */
	अचिन्हित पूर्णांक target_num_cont_raw_buf; /** total number of raw buffers to
					     allocate */
	bool pack_raw_pixels; /** Pack pixels in the raw buffers */
	bool continuous; /** Use SP copy feature to continuously capture frames
			      to प्रणाली memory and run pipes in offline mode */
	bool disable_cont_viewfinder; /** disable continuous viewfinder क्रम ZSL use हाल */
	s32 flash_gpio_pin; /** pin on which the flash is connected, -1 क्रम no flash */
	पूर्णांक left_padding; /** The number of input-क्रमmatter left-paddings, -1 क्रम शेष from binary.*/
	काष्ठा ia_css_mipi_buffer_config
		mipi_buffer_config; /** mipi buffer configuration */
	काष्ठा ia_css_metadata_config
		metadata_config;     /** Metadata configuration. */
	bool ia_css_enable_raw_buffer_locking; /** Enable Raw Buffer Locking क्रम HALv3 Support */
	bool lock_all;
	/** Lock all RAW buffers (true) or lock only buffers processed by
	     video or preview pipe (false).
	     This setting needs to be enabled to allow raw buffer locking
	     without continuous viewfinder. */
पूर्ण;

काष्ठा ia_css_stream;

/* Stream info, this काष्ठा describes properties of a stream after it has been
 *  created.
 */
काष्ठा ia_css_stream_info अणु
	काष्ठा ia_css_metadata_info metadata_info;
	/** Info about the metadata layout, this contains the stride. */
पूर्ण;

/* @brief Load शेष stream configuration
 * @param[in,out]	stream_config The stream configuration.
 * @वापस	None
 *
 * This function will reset the stream configuration to the शेष state:
@code
	स_रखो(stream_config, 0, माप(*stream_config));
	stream_config->online = true;
	stream_config->left_padding = -1;
@endcode
 */
व्योम ia_css_stream_config_शेषs(काष्ठा ia_css_stream_config *stream_config);

/*
 * create the पूर्णांकernal काष्ठाures and fill in the configuration data and pipes
 */

/* @brief Creates a stream
* @param[in]	stream_config The stream configuration.
* @param[in]	num_pipes The number of pipes to incorporate in the stream.
* @param[in]	pipes The pipes.
* @param[out]	stream The stream.
* @वापस	0 or the error code.
*
* This function will create a stream with a given configuration and given pipes.
*/
पूर्णांक
ia_css_stream_create(स्थिर काष्ठा ia_css_stream_config *stream_config,
		     पूर्णांक num_pipes,
		     काष्ठा ia_css_pipe *pipes[],
		     काष्ठा ia_css_stream **stream);

/* @brief Destroys a stream
 * @param[in]	stream The stream.
 * @वापस	0 or the error code.
 *
 * This function will destroy a given stream.
 */
पूर्णांक
ia_css_stream_destroy(काष्ठा ia_css_stream *stream);

/* @brief Provides inक्रमmation about a stream
 * @param[in]	stream The stream.
 * @param[out]	stream_info The inक्रमmation about the stream.
 * @वापस	0 or the error code.
 *
 * This function will destroy a given stream.
 */
पूर्णांक
ia_css_stream_get_info(स्थिर काष्ठा ia_css_stream *stream,
		       काष्ठा ia_css_stream_info *stream_info);

/* @brief load (rebuild) a stream that was unloaded.
 * @param[in]	stream The stream
 * @वापस		0 or the error code
 *
 * Rebuild a stream, including allocating काष्ठाs, setting configuration and
 * building the required pipes.
 */
पूर्णांक
ia_css_stream_load(काष्ठा ia_css_stream *stream);

/* @brief Starts the stream.
 * @param[in]	stream The stream.
 * @वापस 0 or the error code.
 *
 * The dynamic data in
 * the buffers are not used and need to be queued with a separate call
 * to ia_css_pipe_enqueue_buffer.
 * NOTE: this function will only send start event to corresponding
 * thपढ़ो and will not start SP any more.
 */
पूर्णांक
ia_css_stream_start(काष्ठा ia_css_stream *stream);

/* @brief Stop the stream.
 * @param[in]	stream The stream.
 * @वापस	0 or the error code.
 *
 * NOTE: this function will send stop event to pipes beदीर्घ to this
 * stream but will not terminate thपढ़ोs.
 */
पूर्णांक
ia_css_stream_stop(काष्ठा ia_css_stream *stream);

/* @brief Check अगर a stream has stopped
 * @param[in]	stream The stream.
 * @वापस	boolean flag
 *
 * This function will check अगर the stream has stopped and वापस the correspondent boolean flag.
 */
bool
ia_css_stream_has_stopped(काष्ठा ia_css_stream *stream);

/* @brief	destroy a stream according to the stream seed previosly saved in the seed array.
 * @param[in]	stream The stream.
 * @वापस	0 (no other errors are generated now)
 *
 * Destroy the stream and all the pipes related to it.
 */
पूर्णांक
ia_css_stream_unload(काष्ठा ia_css_stream *stream);

/* @brief Returns stream क्रमmat
 * @param[in]	stream The stream.
 * @वापस	क्रमmat of the string
 *
 * This function will वापस the stream क्रमmat.
 */
क्रमागत atomisp_input_क्रमmat
ia_css_stream_get_क्रमmat(स्थिर काष्ठा ia_css_stream *stream);

/* @brief Check अगर the stream is configured क्रम 2 pixels per घड़ी
 * @param[in]	stream The stream.
 * @वापस	boolean flag
 *
 * This function will check अगर the stream is configured क्रम 2 pixels per घड़ी and
 * वापस the correspondent boolean flag.
 */
bool
ia_css_stream_get_two_pixels_per_घड़ी(स्थिर काष्ठा ia_css_stream *stream);

/* @brief Sets the output frame stride (at the last pipe)
 * @param[in]	stream The stream
 * @param[in]	output_padded_width - the output buffer stride.
 * @वापस	ia_css_err
 *
 * This function will Set the output frame stride (at the last pipe)
 */
पूर्णांक
ia_css_stream_set_output_padded_width(काष्ठा ia_css_stream *stream,
				      अचिन्हित पूर्णांक output_padded_width);

/* @brief Return max number of continuous RAW frames.
 * @param[in]	stream The stream.
 * @param[out]	buffer_depth The maximum number of continuous RAW frames.
 * @वापस	0 or -EINVAL
 *
 * This function will वापस the maximum number of continuous RAW frames
 * the प्रणाली can support.
 */
पूर्णांक
ia_css_stream_get_max_buffer_depth(काष्ठा ia_css_stream *stream,
				   पूर्णांक *buffer_depth);

/* @brief Set nr of continuous RAW frames to use.
 *
 * @param[in]	stream The stream.
 * @param[in]	buffer_depth	Number of frames to set.
 * @वापस	0 or error code upon error.
 *
 * Set the number of continuous frames to use during continuous modes.
 */
पूर्णांक
ia_css_stream_set_buffer_depth(काष्ठा ia_css_stream *stream, पूर्णांक buffer_depth);

/* @brief Get number of continuous RAW frames to use.
 * @param[in]	stream The stream.
 * @param[out]	buffer_depth The number of frames to use
 * @वापस	0 or -EINVAL
 *
 * Get the currently set number of continuous frames
 * to use during continuous modes.
 */
पूर्णांक
ia_css_stream_get_buffer_depth(काष्ठा ia_css_stream *stream, पूर्णांक *buffer_depth);

/* ===== CAPTURE ===== */

/* @brief Configure the continuous capture
 *
 * @param[in]	stream		The stream.
 * @param[in]	num_captures	The number of RAW frames to be processed to
 *				YUV. Setting this to -1 will make continuous
 *				capture run until it is stopped.
 *				This number will also be used to allocate RAW
 *				buffers. To allow the viewfinder to also
 *				keep operating, 2 extra buffers will always be
 *				allocated.
 *				If the offset is negative and the skip setting
 *				is greater than 0, additional buffers may be
 *				needed.
 * @param[in]	skip		Skip N frames in between captures. This can be
 *				used to select a slower capture frame rate than
 *				the sensor output frame rate.
 * @param[in]	offset		Start the RAW-to-YUV processing at RAW buffer
 *				with this offset. This allows the user to
 *				process RAW frames that were captured in the
 *				past or future.
 * @वापस			0 or error code upon error.
 *
 *  For example, to capture the current frame plus the 2 previous
 *  frames and 2 subsequent frames, you would call
 *  ia_css_stream_capture(5, 0, -2).
 */
पूर्णांक
ia_css_stream_capture(काष्ठा ia_css_stream *stream,
		      पूर्णांक num_captures,
		      अचिन्हित पूर्णांक skip,
		      पूर्णांक offset);

/* @brief Specअगरy which raw frame to tag based on exp_id found in frame info
 *
 * @param[in]	stream The stream.
 * @param[in]	exp_id	The exposure id of the raw frame to tag.
 *
 * @वापस			0 or error code upon error.
 *
 * This function allows the user to tag a raw frame based on the exposure id
 * found in the viewfinder frames' frame info.
 */
पूर्णांक
ia_css_stream_capture_frame(काष्ठा ia_css_stream *stream,
			    अचिन्हित पूर्णांक exp_id);

/* ===== VIDEO ===== */

/* @brief Send streaming data पूर्णांकo the css input FIFO
 *
 * @param[in]	stream	The stream.
 * @param[in]	data	Poपूर्णांकer to the pixels to be send.
 * @param[in]	width	Width of the input frame.
 * @param[in]	height	Height of the input frame.
 * @वापस	None
 *
 * Send streaming data पूर्णांकo the css input FIFO. This is क्रम testing purposes
 * only. This uses the channel ID and input क्रमmat as set by the user with
 * the regular functions क्रम this.
 * This function blocks until the entire frame has been written पूर्णांकo the
 * input FIFO.
 *
 * Note:
 * For higher flexibility the ia_css_stream_send_input_frame is replaced by
 * three separate functions:
 * 1) ia_css_stream_start_input_frame
 * 2) ia_css_stream_send_input_line
 * 3) ia_css_stream_end_input_frame
 * In this way it is possible to stream multiple frames on dअगरferent
 * channel ID's on a line basis. It will be possible to simulate
 * line-पूर्णांकerleaved Stereo 3D muxed on 1 mipi port.
 * These 3 functions are क्रम testing purpose only and can be used in
 * conjunction with ia_css_stream_send_input_frame
 */
व्योम
ia_css_stream_send_input_frame(स्थिर काष्ठा ia_css_stream *stream,
			       स्थिर अचिन्हित लघु *data,
			       अचिन्हित पूर्णांक width,
			       अचिन्हित पूर्णांक height);

/* @brief Start an input frame on the CSS input FIFO.
 *
 * @param[in]	stream The stream.
 * @वापस	None
 *
 * Starts the streaming to mipi frame by sending SoF क्रम channel channel_id.
 * It will use the input_क्रमmat and two_pixels_per_घड़ी as provided by
 * the user.
 * For the "correct" use-हाल, input_क्रमmat and two_pixels_per_घड़ी must match
 * with the values as set by the user with the regular functions.
 * To simulate an error, the user can provide "incorrect" values क्रम
 * input_क्रमmat and/or two_pixels_per_घड़ी.
 */
व्योम
ia_css_stream_start_input_frame(स्थिर काष्ठा ia_css_stream *stream);

/* @brief Send a line of input data पूर्णांकo the CSS input FIFO.
 *
 * @param[in]	stream		The stream.
 * @param[in]	data	Array of the first line of image data.
 * @param	width	The width (in pixels) of the first line.
 * @param[in]	data2	Array of the second line of image data.
 * @param	width2	The width (in pixels) of the second line.
 * @वापस	None
 *
 * Sends 1 frame line. Start with SoL followed by width bytes of data, followed
 * by width2 bytes of data2 and followed by and EoL
 * It will use the input_क्रमmat and two_pixels_per_घड़ी settings as provided
 * with the ia_css_stream_start_input_frame function call.
 *
 * This function blocks until the entire line has been written पूर्णांकo the
 * input FIFO.
 */
व्योम
ia_css_stream_send_input_line(स्थिर काष्ठा ia_css_stream *stream,
			      स्थिर अचिन्हित लघु *data,
			      अचिन्हित पूर्णांक width,
			      स्थिर अचिन्हित लघु *data2,
			      अचिन्हित पूर्णांक width2);

/* @brief Send a line of input embedded data पूर्णांकo the CSS input FIFO.
 *
 * @param[in]	stream     Poपूर्णांकer of the stream.
 * @param[in]	क्रमmat     Format of the embedded data.
 * @param[in]	data       Poपूर्णांकer of the embedded data line.
 * @param[in]	width      The width (in pixels) of the line.
 * @वापस		None
 *
 * Sends one embedded data line to input fअगरo. Start with SoL followed by
 * width bytes of data, and followed by and EoL.
 * It will use the two_pixels_per_घड़ी settings as provided with the
 * ia_css_stream_start_input_frame function call.
 *
 * This function blocks until the entire line has been written पूर्णांकo the
 * input FIFO.
 */
व्योम
ia_css_stream_send_input_embedded_line(स्थिर काष्ठा ia_css_stream *stream,
				       क्रमागत atomisp_input_क्रमmat क्रमmat,
				       स्थिर अचिन्हित लघु *data,
				       अचिन्हित पूर्णांक width);

/* @brief End an input frame on the CSS input FIFO.
 *
 * @param[in]	stream	The stream.
 * @वापस	None
 *
 * Send the end-of-frame संकेत पूर्णांकo the CSS input FIFO.
 */
व्योम
ia_css_stream_end_input_frame(स्थिर काष्ठा ia_css_stream *stream);

/* @brief send a request flash command to SP
 *
 * @param[in]	stream The stream.
 * @वापस	None
 *
 * Driver needs to call this function to send a flash request command
 * to SP, SP will be responsible क्रम चयनing on/off the flash at proper
 * समय. Due to the SP multi-thपढ़ोing environment, this request may have
 * one-frame delay, the driver needs to check the flashed flag in frame info
 * to determine which frame is being flashed.
 */
व्योम
ia_css_stream_request_flash(काष्ठा ia_css_stream *stream);

/* @brief Configure a stream with filter coefficients.
 *	   @deprecated अणुReplaced by
 *				   ia_css_pipe_set_isp_config_on_pipe()पूर्ण
 *
 * @param[in]	stream The stream.
 * @param[in]	config	The set of filter coefficients.
 * @param[in]   pipe Pipe to be updated when set isp config, शून्य means to
 *		   update all pipes in the stream.
 * @वापस		0 or error code upon error.
 *
 * This function configures the filter coefficients क्रम an image
 * stream. For image pipes that करो not execute any ISP filters, this
 * function will have no effect.
 * It is safe to call this function जबतक the image stream is running,
 * in fact this is the expected behavior most of the समय. Proper
 * resource locking and द्विगुन buffering is in place to allow क्रम this.
 */
पूर्णांक
ia_css_stream_set_isp_config_on_pipe(काष्ठा ia_css_stream *stream,
				     स्थिर काष्ठा ia_css_isp_config *config,
				     काष्ठा ia_css_pipe *pipe);

/* @brief Configure a stream with filter coefficients.
 *	   @deprecated अणुReplaced by
 *				   ia_css_pipe_set_isp_config()पूर्ण
 * @param[in]	stream	The stream.
 * @param[in]	config	The set of filter coefficients.
 * @वापस		0 or error code upon error.
 *
 * This function configures the filter coefficients क्रम an image
 * stream. For image pipes that करो not execute any ISP filters, this
 * function will have no effect. All pipes of a stream will be updated.
 * See ::ia_css_stream_set_isp_config_on_pipe() क्रम the per-pipe alternative.
 * It is safe to call this function जबतक the image stream is running,
 * in fact this is the expected behaviour most of the समय. Proper
 * resource locking and द्विगुन buffering is in place to allow क्रम this.
 */
पूर्णांक
ia_css_stream_set_isp_config(
    काष्ठा ia_css_stream *stream,
    स्थिर काष्ठा ia_css_isp_config *config);

/* @brief Get selected configuration settings
 * @param[in]	stream	The stream.
 * @param[out]	config	Configuration settings.
 * @वापस		None
 */
व्योम
ia_css_stream_get_isp_config(स्थिर काष्ठा ia_css_stream *stream,
			     काष्ठा ia_css_isp_config *config);

/* @brief allocate continuous raw frames क्रम continuous capture
 * @param[in]	stream The stream.
 * @वापस 0 or error code.
 *
 *  because this allocation takes a दीर्घ समय (around 120ms per frame),
 *  we separate the allocation part and update part to let driver call
 *  this function without locking. This function is the allocation part
 *  and next one is update part
 */
पूर्णांक
ia_css_alloc_continuous_frame_reमुख्य(काष्ठा ia_css_stream *stream);

/* @brief allocate continuous raw frames क्रम continuous capture
 * @param[in]	stream The stream.
 * @वापस	0 or error code.
 *
 *  because this allocation takes a दीर्घ समय (around 120ms per frame),
 *  we separate the allocation part and update part to let driver call
 *  this function without locking. This function is the update part
 */
पूर्णांक
ia_css_update_continuous_frames(काष्ठा ia_css_stream *stream);

/* @brief ia_css_unlock_raw_frame . unlock a raw frame (HALv3 Support)
 * @param[in]	stream The stream.
 * @param[in]   exp_id exposure id that uniquely identअगरies the locked Raw Frame Buffer
 * @वापस      ia_css_err 0 or error code
 *
 * As part of HALv3 Feature requirement, SP locks raw buffer until the Application
 * releases its reference to a raw buffer (which are managed by SP), this function allows
 * application to explicitly unlock that buffer in SP.
 */
पूर्णांक
ia_css_unlock_raw_frame(काष्ठा ia_css_stream *stream, uपूर्णांक32_t exp_id);

/* @brief ia_css_en_dz_capt_pipe . Enable/Disable digital zoom क्रम capture pipe
 * @param[in]   stream The stream.
 * @param[in]   enable - true, disable - false
 * @वापस      None
 *
 * Enables or disables digital zoom क्रम capture pipe in provided stream, अगर capture pipe
 * exists. This function sets enable_zoom flag in CAPTURE_PP stage of the capture pipe.
 * In process_zoom_and_motion(), decision to enable or disable zoom क्रम every stage depends
 * on this flag.
 */
व्योम
ia_css_en_dz_capt_pipe(काष्ठा ia_css_stream *stream, bool enable);
#पूर्ण_अगर /* __IA_CSS_STREAM_PUBLIC_H */
