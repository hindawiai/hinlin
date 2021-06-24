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

#अगर_अघोषित __IA_CSS_PIPE_PUBLIC_H
#घोषणा __IA_CSS_PIPE_PUBLIC_H

/* @file
 * This file contains the खुला पूर्णांकerface क्रम CSS pipes.
 */

#समावेश <type_support.h>
#समावेश <ia_css_err.h>
#समावेश <ia_css_types.h>
#समावेश <ia_css_frame_खुला.h>
#समावेश <ia_css_buffer.h>
/* ISP2401 */
#समावेश <ia_css_acc_types.h>

क्रमागत अणु
	IA_CSS_PIPE_OUTPUT_STAGE_0 = 0,
	IA_CSS_PIPE_OUTPUT_STAGE_1,
	IA_CSS_PIPE_MAX_OUTPUT_STAGE,
पूर्ण;

/* Enumeration of pipe modes. This mode can be used to create
 *  an image pipe क्रम this mode. These pipes can be combined
 *  to configure and run streams on the ISP.
 *
 *  For example, one can create a preview and capture pipe to
 *  create a continuous capture stream.
 */
क्रमागत ia_css_pipe_mode अणु
	IA_CSS_PIPE_MODE_PREVIEW,	/** Preview pipe */
	IA_CSS_PIPE_MODE_VIDEO,		/** Video pipe */
	IA_CSS_PIPE_MODE_CAPTURE,	/** Still capture pipe */
	IA_CSS_PIPE_MODE_ACC,		/** Accelerated pipe */
	IA_CSS_PIPE_MODE_COPY,		/** Copy pipe, only used क्रम embedded/image data copying */
	IA_CSS_PIPE_MODE_YUVPP,		/** YUV post processing pipe, used क्रम all use हालs with YUV input,
									क्रम SoC sensor and बाह्यal ISP */
पूर्ण;

/* Temporary define  */
#घोषणा IA_CSS_PIPE_MODE_NUM (IA_CSS_PIPE_MODE_YUVPP + 1)

/**
 * Enumeration of pipe versions.
 * the order should match with definition in sh_css_defs.h
 */
क्रमागत ia_css_pipe_version अणु
	IA_CSS_PIPE_VERSION_1 = 1,		/** ISP1.0 pipe */
	IA_CSS_PIPE_VERSION_2_2 = 2,		/** ISP2.2 pipe */
	IA_CSS_PIPE_VERSION_2_6_1 = 3,		/** ISP2.6.1 pipe */
	IA_CSS_PIPE_VERSION_2_7 = 4		/** ISP2.7 pipe */
पूर्ण;

/**
 * Pipe configuration काष्ठाure.
 * Resolution properties are filled by Driver, kernel configurations are
 * set by AIC
 */
काष्ठा ia_css_pipe_config अणु
	क्रमागत ia_css_pipe_mode mode;
	/** mode, indicates which mode the pipe should use. */
	क्रमागत ia_css_pipe_version isp_pipe_version;
	/** pipe version, indicates which imaging pipeline the pipe should use. */
	काष्ठा ia_css_resolution input_effective_res;
	/** input effective resolution */
	काष्ठा ia_css_resolution bayer_ds_out_res;
	/** bayer करोwn scaling */
	काष्ठा ia_css_resolution capt_pp_in_res;
	/** capture post processing input resolution */
	काष्ठा ia_css_resolution vf_pp_in_res;

	/** ISP2401: view finder post processing input resolution */
	काष्ठा ia_css_resolution output_प्रणाली_in_res;
	/** For IPU3 only: use output_प्रणाली_in_res to specअगरy what input resolution
	     will OSYS receive, this resolution is equal to the output resolution of GDC
	     अगर not determined CSS will set output_प्रणाली_in_res with मुख्य osys output pin resolution
	     All other IPUs may ignore this property */
	काष्ठा ia_css_resolution dvs_crop_out_res;
	/** dvs crop, video only, not in use yet. Use dvs_envelope below. */
	काष्ठा ia_css_frame_info output_info[IA_CSS_PIPE_MAX_OUTPUT_STAGE];
	/** output of YUV scaling */
	काष्ठा ia_css_frame_info vf_output_info[IA_CSS_PIPE_MAX_OUTPUT_STAGE];
	/** output of VF YUV scaling */
	काष्ठा ia_css_fw_info *acc_extension;
	/** Pipeline extension accelerator */
	काष्ठा ia_css_fw_info **acc_stages;
	/** Standalone accelerator stages */
	u32 num_acc_stages;
	/** Number of standalone accelerator stages */
	काष्ठा ia_css_capture_config शेष_capture_config;
	/** Default capture config क्रम initial capture pipe configuration. */
	काष्ठा ia_css_resolution dvs_envelope; /** temporary */
	क्रमागत ia_css_frame_delay dvs_frame_delay;
	/** indicates the DVS loop delay in frame periods */
	पूर्णांक acc_num_execs;
	/** For acceleration pipes only: determine how many बार the pipe
	     should be run. Setting this to -1 means it will run until
	     stopped. */
	bool enable_dz;
	/** Disabling digital zoom क्रम a pipeline, अगर this is set to false,
	     then setting a zoom factor will have no effect.
	     In some use हालs this provides better perक्रमmance. */
	bool enable_dpc;
	/** Disabling "Defect Pixel Correction" क्रम a pipeline, अगर this is set
	     to false. In some use हालs this provides better perक्रमmance. */
	bool enable_vfpp_bci;
	/** Enabling BCI mode will cause yuv_scale binary to be picked up
	     instead of vf_pp. This only applies to viewfinder post
	     processing stages. */

/* ISP2401 */
	bool enable_luma_only;
	/** Enabling of monochrome mode क्रम a pipeline. If enabled only luma processing
	     will be करोne. */
	bool enable_tnr;
	/** Enabling of TNR (temporal noise reduction). This is only applicable to video
	     pipes. Non video-pipes should always set this parameter to false. */

	काष्ठा ia_css_isp_config *p_isp_config;
	/** Poपूर्णांकer to ISP configuration */
	काष्ठा ia_css_resolution gdc_in_buffer_res;
	/** GDC in buffer resolution. */
	काष्ठा ia_css_poपूर्णांक gdc_in_buffer_offset;
	/** GDC in buffer offset - indicates the pixel coordinates of the first valid pixel inside the buffer */

/* ISP2401 */
	काष्ठा ia_css_coordinate पूर्णांकernal_frame_origin_bqs_on_sctbl;
	/** Origin of पूर्णांकernal frame positioned on shading table at shading correction in ISP.
	     NOTE: Shading table is larger than or equal to पूर्णांकernal frame.
		   Shading table has shading gains and पूर्णांकernal frame has bayer data.
		   The origin of पूर्णांकernal frame is used in shading correction in ISP
		   to retrieve shading gains which correspond to bayer data. */
पूर्ण;

/**
 * Default settings क्रम newly created pipe configurations.
 */
#घोषणा DEFAULT_PIPE_CONFIG अणु \
	.mode			= IA_CSS_PIPE_MODE_PREVIEW, \
	.isp_pipe_version	= 1, \
	.output_info		= अणुIA_CSS_BINARY_DEFAULT_FRAME_INFOपूर्ण, \
	.vf_output_info		= अणुIA_CSS_BINARY_DEFAULT_FRAME_INFOपूर्ण, \
	.शेष_capture_config	= DEFAULT_CAPTURE_CONFIG, \
	.dvs_frame_delay	= IA_CSS_FRAME_DELAY_1, \
	.acc_num_execs		= -1, \
पूर्ण

/* Pipe info, this काष्ठा describes properties of a pipe after it's stream has
 * been created.
 * ~~~** DO NOT ADD NEW FIELD **~~~ This काष्ठाure will be deprecated.
 *           - On the Behalf of CSS-API Committee.
 */
काष्ठा ia_css_pipe_info अणु
	काष्ठा ia_css_frame_info output_info[IA_CSS_PIPE_MAX_OUTPUT_STAGE];
	/** Info about output resolution. This contains the stride which
	     should be used क्रम memory allocation. */
	काष्ठा ia_css_frame_info vf_output_info[IA_CSS_PIPE_MAX_OUTPUT_STAGE];
	/** Info about viewfinder output resolution (optional). This contains
	     the stride that should be used क्रम memory allocation. */
	काष्ठा ia_css_frame_info raw_output_info;
	/** Raw output resolution. This indicates the resolution of the
	     RAW bayer output क्रम pipes that support this. Currently, only the
	     still capture pipes support this feature. When this resolution is
	     smaller than the input resolution, cropping will be perक्रमmed by
	     the ISP. The first cropping that will be perक्रमmed is on the upper
	     left corner where we crop 8 lines and 8 columns to हटाओ the
	     pixels normally used to initialize the ISP filters.
	     This is why the raw output resolution should normally be set to
	     the input resolution - 8x8. */
	/* ISP2401 */
	काष्ठा ia_css_resolution output_प्रणाली_in_res_info;
	/** For IPU3 only. Info about output प्रणाली in resolution which is considered
	     as gdc out resolution. */
	काष्ठा ia_css_shading_info shading_info;
	/** After an image pipe is created, this field will contain the info
	     क्रम the shading correction. */
	काष्ठा ia_css_grid_info  grid_info;
	/** After an image pipe is created, this field will contain the grid
	     info क्रम 3A and DVS. */
	पूर्णांक num_invalid_frames;
	/** The very first frames in a started stream करो not contain valid data.
	     In this field, the CSS-firmware communicates to the host-driver how
	     many initial frames will contain invalid data; this allows the
	     host-driver to discard those initial invalid frames and start it's
	     output at the first valid frame. */
पूर्ण;

/**
 * Defaults क्रम ia_css_pipe_info काष्ठाs.
 */
#घोषणा DEFAULT_PIPE_INFO अणु\
	.output_info		= अणुIA_CSS_BINARY_DEFAULT_FRAME_INFOपूर्ण, \
	.vf_output_info		= अणुIA_CSS_BINARY_DEFAULT_FRAME_INFOपूर्ण, \
	.raw_output_info	= IA_CSS_BINARY_DEFAULT_FRAME_INFO, \
	.shading_info		= DEFAULT_SHADING_INFO, \
	.grid_info		= DEFAULT_GRID_INFO, \
पूर्ण

/* @brief Load शेष pipe configuration
 * @param[out]	pipe_config The pipe configuration.
 * @वापस	None
 *
 * This function will load the शेष pipe configuration:
@code
	काष्ठा ia_css_pipe_config def_config = अणु
		IA_CSS_PIPE_MODE_PREVIEW,  // mode
		1,      // isp_pipe_version
		अणु0, 0पूर्ण, // bayer_ds_out_res
		अणु0, 0पूर्ण, // capt_pp_in_res
		अणु0, 0पूर्ण, // vf_pp_in_res
		अणु0, 0पूर्ण, // dvs_crop_out_res
		अणुअणु0, 0पूर्ण, 0, 0, 0, 0पूर्ण, // output_info
		अणुअणु0, 0पूर्ण, 0, 0, 0, 0पूर्ण, // second_output_info
		अणुअणु0, 0पूर्ण, 0, 0, 0, 0पूर्ण, // vf_output_info
		अणुअणु0, 0पूर्ण, 0, 0, 0, 0पूर्ण, // second_vf_output_info
		शून्य,   // acc_extension
		शून्य,   // acc_stages
		0,      // num_acc_stages
		अणु
			IA_CSS_CAPTURE_MODE_RAW, // mode
			false, // enable_xnr
			false  // enable_raw_output
		पूर्ण,      // शेष_capture_config
		अणु0, 0पूर्ण, // dvs_envelope
		1,      // dvs_frame_delay
		-1,     // acc_num_execs
		true,   // enable_dz
		शून्य,   // p_isp_config
	पूर्ण;
@endcode
 */
व्योम ia_css_pipe_config_शेषs(काष्ठा ia_css_pipe_config *pipe_config);

/* @brief Create a pipe
 * @param[in]	config The pipe configuration.
 * @param[out]	pipe The pipe.
 * @वापस	0 or the error code.
 *
 * This function will create a pipe with the given
 * configuration.
 */
पूर्णांक
ia_css_pipe_create(स्थिर काष्ठा ia_css_pipe_config *config,
		   काष्ठा ia_css_pipe **pipe);

/* @brief Destroy a pipe
 * @param[in]	pipe The pipe.
 * @वापस	0 or the error code.
 *
 * This function will destroy a given pipe.
 */
पूर्णांक
ia_css_pipe_destroy(काष्ठा ia_css_pipe *pipe);

/* @brief Provides inक्रमmation about a pipe
 * @param[in]	pipe The pipe.
 * @param[out]	pipe_info The pipe inक्रमmation.
 * @वापस	0 or -EINVAL.
 *
 * This function will provide inक्रमmation about a given pipe.
 */
पूर्णांक
ia_css_pipe_get_info(स्थिर काष्ठा ia_css_pipe *pipe,
		     काष्ठा ia_css_pipe_info *pipe_info);

/* @brief Configure a pipe with filter coefficients.
 * @param[in]	pipe	The pipe.
 * @param[in]	config	The poपूर्णांकer to ISP configuration.
 * @वापस		0 or error code upon error.
 *
 * This function configures the filter coefficients क्रम an image
 * pipe.
 */
पूर्णांक
ia_css_pipe_set_isp_config(काष्ठा ia_css_pipe *pipe,
			   काष्ठा ia_css_isp_config *config);

/* @brief Controls when the Event generator उठाओs an IRQ to the Host.
 *
 * @param[in]	pipe	The pipe.
 * @param[in]	or_mask	Binary or of क्रमागत ia_css_event_irq_mask_type. Each pipe
			related event that is part of this mask will directly
			उठाओ an IRQ to	the Host when the event occurs in the
			CSS.
 * @param[in]	and_mask Binary or of क्रमागत ia_css_event_irq_mask_type. An event
			IRQ क्रम the Host is only उठाओd after all pipe related
			events have occurred at least once क्रम all the active
			pipes. Events are remembered and करोn't need to occurred
			at the same moment in समय. There is no control over
			the order of these events. Once an IRQ has been उठाओd
			all remembered events are reset.
 * @वापस		0.
 *
 Controls when the Event generator in the CSS उठाओs an IRQ to the Host.
 The मुख्य purpose of this function is to reduce the amount of पूर्णांकerrupts
 between the CSS and the Host. This will help saving घातer as it wakes up the
 Host less often. In हाल both or_mask and and_mask are
 IA_CSS_EVENT_TYPE_NONE क्रम all pipes, no event IRQ's will be उठाओd. An
 exception holds क्रम IA_CSS_EVENT_TYPE_PORT_खातापूर्ण, क्रम this event an IRQ is always
 उठाओd.
 Note that events are still queued and the Host can poll क्रम them. The
 or_mask and and_mask may be active at the same समय\न
 \न
 Default values, क्रम all pipe id's, after ia_css_init:\न
 or_mask = IA_CSS_EVENT_TYPE_ALL\न
 and_mask = IA_CSS_EVENT_TYPE_NONE\न
 \न
 Examples\न
 \code
 ia_css_pipe_set_irq_mask(h_pipe,
 IA_CSS_EVENT_TYPE_3A_STATISTICS_DONE |
 IA_CSS_EVENT_TYPE_DIS_STATISTICS_DONE ,
 IA_CSS_EVENT_TYPE_NONE);
 \endcode
 The event generator will only उठाओ an पूर्णांकerrupt to the Host when there are
 3A or DIS statistics available from the preview pipe. It will not generate
 an पूर्णांकerrupt क्रम any other event of the preview pipe e.g when there is an
 output frame available.

 \code
 ia_css_pipe_set_irq_mask(h_pipe_preview,
	IA_CSS_EVENT_TYPE_NONE,
	IA_CSS_EVENT_TYPE_OUTPUT_FRAME_DONE |
	IA_CSS_EVENT_TYPE_3A_STATISTICS_DONE );

 ia_css_pipe_set_irq_mask(h_pipe_capture,
	IA_CSS_EVENT_TYPE_NONE,
	IA_CSS_EVENT_TYPE_OUTPUT_FRAME_DONE );
 \endcode
 The event generator will only उठाओ an पूर्णांकerrupt to the Host when there is
 both a frame करोne and 3A event available from the preview pipe AND when there
 is a frame करोne available from the capture pipe. Note that these events
 may occur at dअगरferent moments in समय. Also the order of the events is not
 relevant.

 \code
 ia_css_pipe_set_irq_mask(h_pipe_preview,
	IA_CSS_EVENT_TYPE_OUTPUT_FRAME_DONE,
	IA_CSS_EVENT_TYPE_ALL );

 ia_css_pipe_set_irq_mask(h_pipe_capture,
	IA_CSS_EVENT_TYPE_OUTPUT_FRAME_DONE,
	IA_CSS_EVENT_TYPE_ALL );
 \endcode
 The event generator will only उठाओ an पूर्णांकerrupt to the Host when there is an
 output frame from the preview pipe OR an output frame from the capture pipe.
 All other events (3A, VF output, pipeline करोne) will not उठाओ an पूर्णांकerrupt
 to the Host. These events are not lost but always stored in the event queue.
 */
पूर्णांक
ia_css_pipe_set_irq_mask(काष्ठा ia_css_pipe *pipe,
			 अचिन्हित पूर्णांक or_mask,
			 अचिन्हित पूर्णांक and_mask);

/* @brief Reads the current event IRQ mask from the CSS.
 *
 * @param[in]	pipe The pipe.
 * @param[out]	or_mask	Current or_mask. The bits in this mask are a binary or
		of क्रमागत ia_css_event_irq_mask_type. Poपूर्णांकer may be शून्य.
 * @param[out]	and_mask Current and_mask.The bits in this mask are a binary or
		of क्रमागत ia_css_event_irq_mask_type. Poपूर्णांकer may be शून्य.
 * @वापस	0.
 *
 Reads the current event IRQ mask from the CSS. Reading वापसs the actual
 values as used by the SP and not any mirrored values stored at the Host.\न
\न
Precondition:\न
SP must be running.\न

*/
पूर्णांक
ia_css_event_get_irq_mask(स्थिर काष्ठा ia_css_pipe *pipe,
			  अचिन्हित पूर्णांक *or_mask,
			  अचिन्हित पूर्णांक *and_mask);

/* @brief Queue a buffer क्रम an image pipe.
 *
 * @param[in] pipe	The pipe that will own the buffer.
 * @param[in] buffer	Poपूर्णांकer to the buffer.
 *			Note that the caller reमुख्यs owner of the buffer
 *			काष्ठाure. Only the data poपूर्णांकer within it will
 *			be passed पूर्णांकo the पूर्णांकernal queues.
 * @वापस		IA_CSS_INTERNAL_ERROR in हाल of unexpected errors,
 *			0 otherwise.
 *
 * This function adds a buffer (which has a certain buffer type) to the queue
 * क्रम this type. This queue is owned by the image pipe. After this function
 * completes successfully, the buffer is now owned by the image pipe and should
 * no दीर्घer be accessed by any other code until it माला_लो dequeued. The image
 * pipe will dequeue buffers from this queue, use them and वापस them to the
 * host code via an पूर्णांकerrupt. Buffers will be consumed in the same order they
 * get queued, but may be वापसed to the host out of order.
 */
पूर्णांक
ia_css_pipe_enqueue_buffer(काष्ठा ia_css_pipe *pipe,
			   स्थिर काष्ठा ia_css_buffer *buffer);

/* @brief Dequeue a buffer from an image pipe.
 *
 * @param[in]    pipe	 The pipeline that the buffer queue beदीर्घs to.
 * @param[in,out] buffer The buffer is used to lookup the type which determines
 *			 which पूर्णांकernal queue to use.
 *			 The resulting buffer poपूर्णांकer is written पूर्णांकo the dta
 *			 field.
 * @वापस		 IA_CSS_ERR_NO_BUFFER अगर the queue is empty or
 *			 0 otherwise.
 *
 * This function dequeues a buffer from a buffer queue. The queue is indicated
 * by the buffer type argument. This function can be called after an पूर्णांकerrupt
 * has been generated that संकेतled that a new buffer was available and can
 * be used in a polling-like situation where the NO_BUFFER वापस value is used
 * to determine whether a buffer was available or not.
 */
पूर्णांक
ia_css_pipe_dequeue_buffer(काष्ठा ia_css_pipe *pipe,
			   काष्ठा ia_css_buffer *buffer);

/* @brief  Set the state (Enable or Disable) of the Extension stage in the
 *          given pipe.
 * @param[in] pipe         Pipe handle.
 * @param[in] fw_handle    Extension firmware Handle (ia_css_fw_info.handle)
 * @param[in] enable       Enable Flag (1 to enable ; 0 to disable)
 *
 * @वापस
 * 0			: Success
 * -EINVAL		: Invalid Parameters
 * -EBUSY	: Inactive QOS Pipe
 *					(No active stream with this pipe)
 *
 * This function will request state change (enable or disable) क्रम the Extension
 * stage (firmware handle) in the given pipe.
 *
 * Note:
 *	1. Extension can be enabled/disabled only on QOS Extensions
 *	2. Extension can be enabled/disabled only with an active QOS Pipe
 *	3. Initial(Default) state of QOS Extensions is Disabled
 *	4. State change cannot be guaranteed immediately OR on frame boundary
 *
 */
पूर्णांक
ia_css_pipe_set_qos_ext_state(काष्ठा ia_css_pipe *pipe,
			      u32 fw_handle,
			      bool  enable);

/* @brief  Get the state (Enable or Disable) of the Extension stage in the
 *          given pipe.
 * @param[in]  pipe        Pipe handle.
 * @param[in]  fw_handle   Extension firmware Handle (ia_css_fw_info.handle)
 * @param[out] *enable     Enable Flag
 *
 * @वापस
 * 0			: Success
 * -EINVAL		: Invalid Parameters
 * -EBUSY	: Inactive QOS Pipe
 *					(No active stream with this pipe)
 *
 * This function will query the state of the Extension stage (firmware handle)
 * in the given Pipe.
 *
 * Note:
 *	1. Extension state can be queried only on QOS Extensions
 *	2. Extension can be enabled/disabled only with an active QOS Pipe
 *	3. Initial(Default) state of QOS Extensions is Disabled.
 *
 */
पूर्णांक
ia_css_pipe_get_qos_ext_state(काष्ठा ia_css_pipe *pipe,
			      u32 fw_handle,
			      bool *enable);

/* ISP2401  */
/* @brief  Update mapped CSS and ISP arguments क्रम QoS pipe during SP runसमय.
 * @param[in] pipe	Pipe handle.
 * @param[in] fw_handle	Extension firmware Handle (ia_css_fw_info.handle).
 * @param[in] css_seg	Parameter memory descriptors क्रम CSS segments.
 * @param[in] isp_seg	Parameter memory descriptors क्रम ISP segments.
 *
 * @वापस
 * 0			: Success
 * -EINVAL		: Invalid Parameters
 * -EBUSY	: Inactive QOS Pipe
 *					(No active stream with this pipe)
 *
 * \deprecatedअणुThis पूर्णांकerface is used to temporarily support a late-developed,
 * specअगरic use-हाल on a specअगरic IPU2 platक्रमm. It will not be supported or
 * मुख्यtained on IPU3 or further.पूर्ण
 */
पूर्णांक
ia_css_pipe_update_qos_ext_mapped_arg(काष्ठा ia_css_pipe *pipe,
				      u32 fw_handle,
				      काष्ठा ia_css_isp_param_css_segments *css_seg,
				      काष्ठा ia_css_isp_param_isp_segments *isp_seg);

/* @brief Get selected configuration settings
 * @param[in]	pipe	The pipe.
 * @param[out]	config	Configuration settings.
 * @वापस		None
 */
व्योम
ia_css_pipe_get_isp_config(काष्ठा ia_css_pipe *pipe,
			   काष्ठा ia_css_isp_config *config);

/* @brief Set the scaler lut on this pipe. A copy of lut is made in the inuit
 *         address space. So the LUT can be मुक्तd by caller.
 * @param[in]  pipe        Pipe handle.
 * @param[in]  lut         Look up tabel
 *
 * @वापस
 * 0			: Success
 * -EINVAL		: Invalid Parameters
 *
 * Note:
 * 1) Note that both GDC's are programmed with the same table.
 * 2) Current implementation ignores the pipe and overrides the
 *    global lut. This will be fixed in the future
 * 3) This function must be called beक्रमe stream start
 *
 */
पूर्णांक
ia_css_pipe_set_bci_scaler_lut(काष्ठा ia_css_pipe *pipe,
			       स्थिर व्योम *lut);
/* @brief Checking of DVS statistics ability
 * @param[in]	pipe_info	The pipe info.
 * @वापस		true - has DVS statistics ability
 *			false - otherwise
 */
bool ia_css_pipe_has_dvs_stats(काष्ठा ia_css_pipe_info *pipe_info);

/* ISP2401 */
/* @brief Override the frameक्रमmat set on the output pins.
 * @param[in]  pipe        Pipe handle.
 * @param[in]  output_pin  Pin index to set the क्रमmat on
 *                         0 - मुख्य output pin
 *                         1 - display output pin
 * @param[in]  क्रमmat      Format to set
 *
 * @वापस
 * 0		: Success
 * -EINVAL	: Invalid Parameters
 * -EINVAL	: Pipe misses binary info
 *
 * Note:
 * 1) This is an optional function to override the क्रमmats set in the pipe.
 * 2) Only overriding with IA_CSS_FRAME_FORMAT_NV12_TILEY is currently allowed.
 * 3) This function is only to be used on pipes that use the output प्रणाली.
 * 4) If this function is used, it MUST be called after ia_css_pipe_create.
 * 5) If this function is used, this function MUST be called beक्रमe ia_css_stream_start.
 */
पूर्णांक
ia_css_pipe_override_frame_क्रमmat(काष्ठा ia_css_pipe *pipe,
				  पूर्णांक output_pin,
				  क्रमागत ia_css_frame_क्रमmat क्रमmat);

#पूर्ण_अगर /* __IA_CSS_PIPE_PUBLIC_H */
