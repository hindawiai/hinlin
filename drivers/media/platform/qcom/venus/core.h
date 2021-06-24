<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2012-2016, The Linux Foundation. All rights reserved.
 * Copyright (C) 2017 Linaro Ltd.
 */

#अगर_अघोषित __VENUS_CORE_H_
#घोषणा __VENUS_CORE_H_

#समावेश <linux/list.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>

#समावेश "dbgfs.h"
#समावेश "hfi.h"
#समावेश "hfi_platform.h"

#घोषणा VDBGL	"VenusLow : "
#घोषणा VDBGM	"VenusMed : "
#घोषणा VDBGH	"VenusHigh: "
#घोषणा VDBGFW	"VenusFW  : "

#घोषणा VIDC_CLKS_NUM_MAX		4
#घोषणा VIDC_VCODEC_CLKS_NUM_MAX	2
#घोषणा VIDC_PMDOMAINS_NUM_MAX		3
#घोषणा VIDC_RESETS_NUM_MAX		2

बाह्य पूर्णांक venus_fw_debug;

काष्ठा freq_tbl अणु
	अचिन्हित पूर्णांक load;
	अचिन्हित दीर्घ freq;
पूर्ण;

काष्ठा reg_val अणु
	u32 reg;
	u32 value;
पूर्ण;

काष्ठा bw_tbl अणु
	u32 mbs_per_sec;
	u32 avg;
	u32 peak;
	u32 avg_10bit;
	u32 peak_10bit;
पूर्ण;

काष्ठा venus_resources अणु
	u64 dma_mask;
	स्थिर काष्ठा freq_tbl *freq_tbl;
	अचिन्हित पूर्णांक freq_tbl_size;
	स्थिर काष्ठा bw_tbl *bw_tbl_enc;
	अचिन्हित पूर्णांक bw_tbl_enc_size;
	स्थिर काष्ठा bw_tbl *bw_tbl_dec;
	अचिन्हित पूर्णांक bw_tbl_dec_size;
	स्थिर काष्ठा reg_val *reg_tbl;
	अचिन्हित पूर्णांक reg_tbl_size;
	स्थिर अक्षर * स्थिर clks[VIDC_CLKS_NUM_MAX];
	अचिन्हित पूर्णांक clks_num;
	स्थिर अक्षर * स्थिर vcodec0_clks[VIDC_VCODEC_CLKS_NUM_MAX];
	स्थिर अक्षर * स्थिर vcodec1_clks[VIDC_VCODEC_CLKS_NUM_MAX];
	अचिन्हित पूर्णांक vcodec_clks_num;
	स्थिर अक्षर * स्थिर vcodec_pmकरोमुख्यs[VIDC_PMDOMAINS_NUM_MAX];
	अचिन्हित पूर्णांक vcodec_pmकरोमुख्यs_num;
	स्थिर अक्षर **opp_pmकरोमुख्य;
	अचिन्हित पूर्णांक vcodec_num;
	स्थिर अक्षर * स्थिर resets[VIDC_RESETS_NUM_MAX];
	अचिन्हित पूर्णांक resets_num;
	क्रमागत hfi_version hfi_version;
	u32 max_load;
	अचिन्हित पूर्णांक vmem_id;
	u32 vmem_size;
	u32 vmem_addr;
	u32 cp_start;
	u32 cp_size;
	u32 cp_nonpixel_start;
	u32 cp_nonpixel_size;
	स्थिर अक्षर *fwname;
पूर्ण;

काष्ठा venus_क्रमmat अणु
	u32 pixfmt;
	अचिन्हित पूर्णांक num_planes;
	u32 type;
	u32 flags;
पूर्ण;

/**
 * काष्ठा venus_core - holds core parameters valid क्रम all instances
 *
 * @base:	IO memory base address
 * @vbअगर_base:	IO memory vbअगर base address
 * @cpu_base:	IO memory cpu base address
 * @cpu_cs_base:	IO memory cpu_cs base address
 * @cpu_ic_base:	IO memory cpu_ic base address
 * @wrapper_base:	IO memory wrapper base address
 * @wrapper_tz_base:	IO memory wrapper TZ base address
 * @aon_base:	AON base address
 * @irq:		Venus irq
 * @clks:	an array of काष्ठा clk poपूर्णांकers
 * @vcodec0_clks: an array of vcodec0 काष्ठा clk poपूर्णांकers
 * @vcodec1_clks: an array of vcodec1 काष्ठा clk poपूर्णांकers
 * @video_path: an पूर्णांकerconnect handle to video to/from memory path
 * @cpucfg_path: an पूर्णांकerconnect handle to cpu configuration path
 * @opp_table: an device OPP table handle
 * @has_opp_table: करोes OPP table exist
 * @pmकरोमुख्यs:	an array of pmकरोमुख्यs काष्ठा device poपूर्णांकers
 * @opp_dl_venus: an device-link क्रम device OPP
 * @opp_pmकरोमुख्य: an OPP घातer-करोमुख्य
 * @resets: an array of reset संकेतs
 * @vdev_dec:	a reference to video device काष्ठाure क्रम decoder instances
 * @vdev_enc:	a reference to video device काष्ठाure क्रम encoder instances
 * @v4l2_dev:	a holder क्रम v4l2 device काष्ठाure
 * @res:		a reference to venus resources काष्ठाure
 * @dev:		convenience काष्ठा device poपूर्णांकer
 * @dev_dec:	convenience काष्ठा device poपूर्णांकer क्रम decoder device
 * @dev_enc:	convenience काष्ठा device poपूर्णांकer क्रम encoder device
 * @use_tz:	a flag that suggests presence of trustzone
 * @fw:		काष्ठाure of firmware parameters
 * @lock:	a lock क्रम this strucure
 * @instances:	a list_head of all instances
 * @insts_count:	num of instances
 * @state:	the state of the venus core
 * @करोne:	a completion क्रम sync HFI operations
 * @error:	an error वापसed during last HFI sync operations
 * @sys_error:	an error flag that संकेत प्रणाली error event
 * @core_ops:	the core operations
 * @pm_ops:	a poपूर्णांकer to pm operations
 * @pm_lock:	a lock क्रम PM operations
 * @enc_codecs:	encoders supported by this core
 * @dec_codecs:	decoders supported by this core
 * @max_sessions_supported:	holds the maximum number of sessions
 * @priv:	a निजी filed क्रम HFI operations
 * @ops:		the core HFI operations
 * @work:	a delayed work क्रम handling प्रणाली fatal error
 * @caps:	an array of supported HFI capabilities
 * @codecs_count: platक्रमm codecs count
 * @core0_usage_count: usage counter क्रम core0
 * @core1_usage_count: usage counter क्रम core1
 * @root:	debugfs root directory
 */
काष्ठा venus_core अणु
	व्योम __iomem *base;
	व्योम __iomem *vbअगर_base;
	व्योम __iomem *cpu_base;
	व्योम __iomem *cpu_cs_base;
	व्योम __iomem *cpu_ic_base;
	व्योम __iomem *wrapper_base;
	व्योम __iomem *wrapper_tz_base;
	व्योम __iomem *aon_base;
	पूर्णांक irq;
	काष्ठा clk *clks[VIDC_CLKS_NUM_MAX];
	काष्ठा clk *vcodec0_clks[VIDC_VCODEC_CLKS_NUM_MAX];
	काष्ठा clk *vcodec1_clks[VIDC_VCODEC_CLKS_NUM_MAX];
	काष्ठा icc_path *video_path;
	काष्ठा icc_path *cpucfg_path;
	काष्ठा opp_table *opp_table;
	bool has_opp_table;
	काष्ठा device *pmकरोमुख्यs[VIDC_PMDOMAINS_NUM_MAX];
	काष्ठा device_link *opp_dl_venus;
	काष्ठा device *opp_pmकरोमुख्य;
	काष्ठा reset_control *resets[VIDC_RESETS_NUM_MAX];
	काष्ठा video_device *vdev_dec;
	काष्ठा video_device *vdev_enc;
	काष्ठा v4l2_device v4l2_dev;
	स्थिर काष्ठा venus_resources *res;
	काष्ठा device *dev;
	काष्ठा device *dev_dec;
	काष्ठा device *dev_enc;
	अचिन्हित पूर्णांक use_tz;
	काष्ठा video_firmware अणु
		काष्ठा device *dev;
		काष्ठा iommu_करोमुख्य *iommu_करोमुख्य;
		माप_प्रकार mapped_mem_size;
		phys_addr_t mem_phys;
		माप_प्रकार mem_size;
	पूर्ण fw;
	काष्ठा mutex lock;
	काष्ठा list_head instances;
	atomic_t insts_count;
	अचिन्हित पूर्णांक state;
	काष्ठा completion करोne;
	अचिन्हित पूर्णांक error;
	bool sys_error;
	स्थिर काष्ठा hfi_core_ops *core_ops;
	स्थिर काष्ठा venus_pm_ops *pm_ops;
	काष्ठा mutex pm_lock;
	अचिन्हित दीर्घ enc_codecs;
	अचिन्हित दीर्घ dec_codecs;
	अचिन्हित पूर्णांक max_sessions_supported;
	व्योम *priv;
	स्थिर काष्ठा hfi_ops *ops;
	काष्ठा delayed_work work;
	काष्ठा hfi_plat_caps caps[MAX_CODEC_NUM];
	अचिन्हित पूर्णांक codecs_count;
	अचिन्हित पूर्णांक core0_usage_count;
	अचिन्हित पूर्णांक core1_usage_count;
	काष्ठा dentry *root;
पूर्ण;

काष्ठा vdec_controls अणु
	u32 post_loop_deb_mode;
	u32 profile;
	u32 level;
	u32 display_delay;
	u32 display_delay_enable;
	u64 conceal_color;
पूर्ण;

काष्ठा venc_controls अणु
	u16 gop_size;
	u32 num_p_frames;
	u32 num_b_frames;
	u32 bitrate_mode;
	u32 bitrate;
	u32 bitrate_peak;
	u32 rc_enable;
	u32 स्थिर_quality;
	u32 frame_skip_mode;

	u32 h264_i_period;
	u32 h264_entropy_mode;
	u32 h264_i_qp;
	u32 h264_p_qp;
	u32 h264_b_qp;
	u32 h264_min_qp;
	u32 h264_max_qp;
	u32 h264_i_min_qp;
	u32 h264_i_max_qp;
	u32 h264_p_min_qp;
	u32 h264_p_max_qp;
	u32 h264_b_min_qp;
	u32 h264_b_max_qp;
	u32 h264_loop_filter_mode;
	s32 h264_loop_filter_alpha;
	s32 h264_loop_filter_beta;

	u32 hevc_i_qp;
	u32 hevc_p_qp;
	u32 hevc_b_qp;
	u32 hevc_min_qp;
	u32 hevc_max_qp;
	u32 hevc_i_min_qp;
	u32 hevc_i_max_qp;
	u32 hevc_p_min_qp;
	u32 hevc_p_max_qp;
	u32 hevc_b_min_qp;
	u32 hevc_b_max_qp;

	u32 vp8_min_qp;
	u32 vp8_max_qp;

	u32 multi_slice_mode;
	u32 multi_slice_max_bytes;
	u32 multi_slice_max_mb;

	u32 header_mode;
	bool aud_enable;

	काष्ठा अणु
		u32 h264;
		u32 mpeg4;
		u32 hevc;
		u32 vp8;
		u32 vp9;
	पूर्ण profile;
	काष्ठा अणु
		u32 h264;
		u32 mpeg4;
		u32 hevc;
		u32 vp9;
	पूर्ण level;

	u32 base_priority_id;
	u32 ltr_count;
	काष्ठा v4l2_ctrl_hdr10_cll_info cll;
	काष्ठा v4l2_ctrl_hdr10_mastering_display mastering;
पूर्ण;

काष्ठा venus_buffer अणु
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head list;
	dma_addr_t dma_addr;
	u32 size;
	काष्ठा list_head reg_list;
	u32 flags;
	काष्ठा list_head ref_list;
पूर्ण;

काष्ठा घड़ी_data अणु
	u32 core_id;
	अचिन्हित दीर्घ freq;
	अचिन्हित दीर्घ vpp_freq;
	अचिन्हित दीर्घ vsp_freq;
पूर्ण;

#घोषणा to_venus_buffer(ptr)	container_of(ptr, काष्ठा venus_buffer, vb)

क्रमागत venus_dec_state अणु
	VENUS_DEC_STATE_DEINIT		= 0,
	VENUS_DEC_STATE_INIT		= 1,
	VENUS_DEC_STATE_CAPTURE_SETUP	= 2,
	VENUS_DEC_STATE_STOPPED		= 3,
	VENUS_DEC_STATE_SEEK		= 4,
	VENUS_DEC_STATE_DRAIN		= 5,
	VENUS_DEC_STATE_DECODING	= 6,
	VENUS_DEC_STATE_DRC		= 7,
पूर्ण;

काष्ठा venus_ts_metadata अणु
	bool used;
	u64 ts_ns;
	u64 ts_us;
	u32 flags;
	काष्ठा v4l2_समयcode tc;
पूर्ण;

/**
 * काष्ठा venus_inst - holds per instance parameters
 *
 * @list:	used क्रम attach an instance to the core
 * @lock:	instance lock
 * @core:	a reference to the core काष्ठा
 * @clk_data:	घड़ी data per core ID
 * @dpbbufs:	a list of decoded picture buffers
 * @पूर्णांकernalbufs:	a list of पूर्णांकernal bufferes
 * @रेजिस्टरedbufs:	a list of रेजिस्टरed capture bufferes
 * @delayed_process:	a list of delayed buffers
 * @delayed_process_work:	a work_काष्ठा क्रम process delayed buffers
 * @ctrl_handler:	v4l control handler
 * @controls:	a जोड़ of decoder and encoder control parameters
 * @fh:	 a holder of v4l file handle काष्ठाure
 * @streamon_cap: stream on flag क्रम capture queue
 * @streamon_out: stream on flag क्रम output queue
 * @width:	current capture width
 * @height:	current capture height
 * @crop:	current crop rectangle
 * @out_width:	current output width
 * @out_height:	current output height
 * @colorspace:	current color space
 * @ycbcr_enc:	current YCbCr encoding
 * @quantization:	current quantization
 * @xfer_func:	current xfer function
 * @codec_state:	current codec API state (see DEC/ENC_STATE_)
 * @reconf_रुको:	रुको queue क्रम resolution change event
 * @subscriptions:	used to hold current events subscriptions
 * @buf_count:		used to count number of buffers (reqbuf(0))
 * @tss:		बारtamp metadata
 * @payloads:		cache plane payload to use it क्रम घड़ी/BW scaling
 * @fps:		holds current FPS
 * @समयperframe:	holds current समय per frame काष्ठाure
 * @fmt_out:	a reference to output क्रमmat काष्ठाure
 * @fmt_cap:	a reference to capture क्रमmat काष्ठाure
 * @num_input_bufs:	holds number of input buffers
 * @num_output_bufs:	holds number of output buffers
 * @input_buf_size:	holds input buffer size
 * @output_buf_size:	holds output buffer size
 * @output2_buf_size:	holds secondary decoder output buffer size
 * @dpb_buftype:	decoded picture buffer type
 * @dpb_fmt:		decoded picture buffer raw क्रमmat
 * @opb_buftype:	output picture buffer type
 * @opb_fmt:		output picture buffer raw क्रमmat
 * @reconfig:	a flag उठाओd by decoder when the stream resolution changed
 * @hfi_codec:		current codec क्रम this instance in HFI space
 * @sequence_cap:	a sequence counter क्रम capture queue
 * @sequence_out:	a sequence counter क्रम output queue
 * @m2m_dev:	a reference to m2m device काष्ठाure
 * @m2m_ctx:	a reference to m2m context काष्ठाure
 * @state:	current state of the instance
 * @करोne:	a completion क्रम sync HFI operation
 * @error:	an error वापसed during last HFI sync operation
 * @session_error:	a flag rised by HFI पूर्णांकerface in हाल of session error
 * @ops:		HFI operations
 * @priv:	a निजी क्रम HFI operations callbacks
 * @session_type:	the type of the session (decoder or encoder)
 * @hprop:	a जोड़ used as a holder by get property
 * @core_acquired:	the Core has been acquired
 * @bit_depth:		current bitstream bit-depth
 * @pic_काष्ठा:		bitstream progressive vs पूर्णांकerlaced
 * @next_buf_last: a flag to mark next queued capture buffer as last
 * @drain_active:	Drain sequence is in progress
 */
काष्ठा venus_inst अणु
	काष्ठा list_head list;
	काष्ठा mutex lock;
	काष्ठा venus_core *core;
	काष्ठा घड़ी_data clk_data;
	काष्ठा list_head dpbbufs;
	काष्ठा list_head पूर्णांकernalbufs;
	काष्ठा list_head रेजिस्टरedbufs;
	काष्ठा list_head delayed_process;
	काष्ठा work_काष्ठा delayed_process_work;

	काष्ठा v4l2_ctrl_handler ctrl_handler;
	जोड़ अणु
		काष्ठा vdec_controls dec;
		काष्ठा venc_controls enc;
	पूर्ण controls;
	काष्ठा v4l2_fh fh;
	अचिन्हित पूर्णांक streamon_cap, streamon_out;
	u32 width;
	u32 height;
	काष्ठा v4l2_rect crop;
	u32 out_width;
	u32 out_height;
	u32 colorspace;
	u8 ycbcr_enc;
	u8 quantization;
	u8 xfer_func;
	क्रमागत venus_dec_state codec_state;
	रुको_queue_head_t reconf_रुको;
	अचिन्हित पूर्णांक subscriptions;
	पूर्णांक buf_count;
	काष्ठा venus_ts_metadata tss[VIDEO_MAX_FRAME];
	अचिन्हित दीर्घ payloads[VIDEO_MAX_FRAME];
	u64 fps;
	काष्ठा v4l2_fract समयperframe;
	स्थिर काष्ठा venus_क्रमmat *fmt_out;
	स्थिर काष्ठा venus_क्रमmat *fmt_cap;
	अचिन्हित पूर्णांक num_input_bufs;
	अचिन्हित पूर्णांक num_output_bufs;
	अचिन्हित पूर्णांक input_buf_size;
	अचिन्हित पूर्णांक output_buf_size;
	अचिन्हित पूर्णांक output2_buf_size;
	u32 dpb_buftype;
	u32 dpb_fmt;
	u32 opb_buftype;
	u32 opb_fmt;
	bool reconfig;
	u32 hfi_codec;
	u32 sequence_cap;
	u32 sequence_out;
	काष्ठा v4l2_m2m_dev *m2m_dev;
	काष्ठा v4l2_m2m_ctx *m2m_ctx;
	अचिन्हित पूर्णांक state;
	काष्ठा completion करोne;
	अचिन्हित पूर्णांक error;
	bool session_error;
	स्थिर काष्ठा hfi_inst_ops *ops;
	u32 session_type;
	जोड़ hfi_get_property hprop;
	अचिन्हित पूर्णांक core_acquired: 1;
	अचिन्हित पूर्णांक bit_depth;
	अचिन्हित पूर्णांक pic_काष्ठा;
	bool next_buf_last;
	bool drain_active;
पूर्ण;

#घोषणा IS_V1(core)	((core)->res->hfi_version == HFI_VERSION_1XX)
#घोषणा IS_V3(core)	((core)->res->hfi_version == HFI_VERSION_3XX)
#घोषणा IS_V4(core)	((core)->res->hfi_version == HFI_VERSION_4XX)
#घोषणा IS_V6(core)	((core)->res->hfi_version == HFI_VERSION_6XX)

#घोषणा ctrl_to_inst(ctrl)	\
	container_of((ctrl)->handler, काष्ठा venus_inst, ctrl_handler)

अटल अंतरभूत काष्ठा venus_inst *to_inst(काष्ठा file *filp)
अणु
	वापस container_of(filp->निजी_data, काष्ठा venus_inst, fh);
पूर्ण

अटल अंतरभूत व्योम *to_hfi_priv(काष्ठा venus_core *core)
अणु
	वापस core->priv;
पूर्ण

अटल अंतरभूत काष्ठा hfi_plat_caps *
venus_caps_by_codec(काष्ठा venus_core *core, u32 codec, u32 करोमुख्य)
अणु
	अचिन्हित पूर्णांक c;

	क्रम (c = 0; c < core->codecs_count; c++) अणु
		अगर (core->caps[c].codec == codec &&
		    core->caps[c].करोमुख्य == करोमुख्य)
			वापस &core->caps[c];
	पूर्ण

	वापस शून्य;
पूर्ण

#पूर्ण_अगर
