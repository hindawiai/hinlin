<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) STMicroelectronics SA 2015
 * Authors: Yannick Fertre <yannick.fertre@st.com>
 *          Hugues Fruchet <hugues.fruchet@st.com>
 */

#अगर_अघोषित HVA_H
#घोषणा HVA_H

#समावेश <media/v4l2-ctrls.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/v4l2-mem2स्मृति.स>

#घोषणा fh_to_ctx(f)    (container_of(f, काष्ठा hva_ctx, fh))

#घोषणा hva_to_dev(h)   (h->dev)

#घोषणा ctx_to_dev(c)   (c->hva_dev->dev)

#घोषणा ctx_to_hdev(c)  (c->hva_dev)

#घोषणा HVA_NAME	"st-hva"
#घोषणा HVA_PREFIX	"[---:----]"

बाह्य स्थिर काष्ठा hva_enc nv12h264enc;
बाह्य स्थिर काष्ठा hva_enc nv21h264enc;

/**
 * काष्ठा hva_frameinfo - inक्रमmation about hva frame
 *
 * @pixelक्रमmat:    fourcc code क्रम uncompressed video क्रमmat
 * @width:          width of frame
 * @height:         height of frame
 * @aligned_width:  width of frame (with encoder alignment स्थिरraपूर्णांक)
 * @aligned_height: height of frame (with encoder alignment स्थिरraपूर्णांक)
 * @size:           maximum size in bytes required क्रम data
*/
काष्ठा hva_frameinfo अणु
	u32	pixelक्रमmat;
	u32	width;
	u32	height;
	u32	aligned_width;
	u32	aligned_height;
	u32	size;
पूर्ण;

/**
 * काष्ठा hva_streaminfo - inक्रमmation about hva stream
 *
 * @streamक्रमmat: fourcc code of compressed video क्रमmat (H.264...)
 * @width:        width of stream
 * @height:       height of stream
 * @profile:      profile string
 * @level:        level string
 */
काष्ठा hva_streaminfo अणु
	u32	streamक्रमmat;
	u32	width;
	u32	height;
	u8	profile[32];
	u8	level[32];
पूर्ण;

/**
 * काष्ठा hva_controls - hva controls set
 *
 * @समय_per_frame: समय per frame in seconds
 * @bitrate_mode:   bitrate mode (स्थिरant bitrate or variable bitrate)
 * @gop_size:       groupe of picture size
 * @bitrate:        bitrate (in bps)
 * @aspect:         video aspect
 * @profile:        H.264 profile
 * @level:          H.264 level
 * @entropy_mode:   H.264 entropy mode (CABAC or CVLC)
 * @cpb_size:       coded picture buffer size (in kB)
 * @dct8x8:         transक्रमm mode 8x8 enable
 * @qpmin:          minimum quantizer
 * @qpmax:          maximum quantizer
 * @vui_sar:        pixel aspect ratio enable
 * @vui_sar_idc:    pixel aspect ratio identअगरier
 * @sei_fp:         sei frame packing arrangement enable
 * @sei_fp_type:    sei frame packing arrangement type
 */
काष्ठा hva_controls अणु
	काष्ठा v4l2_fract					समय_per_frame;
	क्रमागत v4l2_mpeg_video_bitrate_mode			bitrate_mode;
	u32							gop_size;
	u32							bitrate;
	क्रमागत v4l2_mpeg_video_aspect				aspect;
	क्रमागत v4l2_mpeg_video_h264_profile			profile;
	क्रमागत v4l2_mpeg_video_h264_level				level;
	क्रमागत v4l2_mpeg_video_h264_entropy_mode			entropy_mode;
	u32							cpb_size;
	bool							dct8x8;
	u32							qpmin;
	u32							qpmax;
	bool							vui_sar;
	क्रमागत v4l2_mpeg_video_h264_vui_sar_idc			vui_sar_idc;
	bool							sei_fp;
	क्रमागत v4l2_mpeg_video_h264_sei_fp_arrangement_type	sei_fp_type;
पूर्ण;

/**
 * काष्ठा hva_frame - hva frame buffer (output)
 *
 * @vbuf:     video buffer inक्रमmation क्रम V4L2
 * @list:     V4L2 m2m list that the frame beदीर्घs to
 * @info:     frame inक्रमmation (width, height, क्रमmat, alignment...)
 * @paddr:    physical address (क्रम hardware)
 * @vaddr:    भव address (kernel can पढ़ो/ग_लिखो)
 * @prepared: true अगर vaddr/paddr are resolved
 */
काष्ठा hva_frame अणु
	काष्ठा vb2_v4l2_buffer	vbuf;
	काष्ठा list_head	list;
	काष्ठा hva_frameinfo	info;
	dma_addr_t		paddr;
	व्योम			*vaddr;
	bool			prepared;
पूर्ण;

/*
 * to_hva_frame() - cast काष्ठा vb2_v4l2_buffer * to काष्ठा hva_frame *
 */
#घोषणा to_hva_frame(vb) \
	container_of(vb, काष्ठा hva_frame, vbuf)

/**
 * काष्ठा hva_stream - hva stream buffer (capture)
 *
 * @vbuf:       video buffer inक्रमmation क्रम V4L2
 * @list:       V4L2 m2m list that the frame beदीर्घs to
 * @paddr:      physical address (क्रम hardware)
 * @vaddr:      भव address (kernel can पढ़ो/ग_लिखो)
 * @prepared:   true अगर vaddr/paddr are resolved
 * @size:       size of the buffer in bytes
 * @bytesused:  number of bytes occupied by data in the buffer
 */
काष्ठा hva_stream अणु
	काष्ठा vb2_v4l2_buffer	vbuf;
	काष्ठा list_head	list;
	dma_addr_t		paddr;
	व्योम			*vaddr;
	bool			prepared;
	अचिन्हित पूर्णांक		size;
	अचिन्हित पूर्णांक		bytesused;
पूर्ण;

/*
 * to_hva_stream() - cast काष्ठा vb2_v4l2_buffer * to काष्ठा hva_stream *
 */
#घोषणा to_hva_stream(vb) \
	container_of(vb, काष्ठा hva_stream, vbuf)

#अगर_घोषित CONFIG_VIDEO_STI_HVA_DEBUGFS
/**
 * काष्ठा hva_ctx_dbg - instance context debug info
 *
 * @debugfs_entry:      debugfs entry
 * @is_valid_period:    true अगर the sequence is valid क्रम perक्रमmance
 * @begin:              start समय of last HW task
 * @total_duration:     total HW processing durations in 0.1ms
 * @cnt_duration:       number of HW processings
 * @min_duration:       minimum HW processing duration in 0.1ms
 * @max_duration:       maximum HW processing duration in 0.1ms
 * @avg_duration:       average HW processing duration in 0.1ms
 * @max_fps:            maximum frames encoded per second (in 0.1Hz)
 * @total_period:       total encoding periods in 0.1ms
 * @cnt_period:         number of periods
 * @min_period:         minimum encoding period in 0.1ms
 * @max_period:         maximum encoding period in 0.1ms
 * @avg_period:         average encoding period in 0.1ms
 * @total_stream_size:  total number of encoded bytes
 * @avg_fps:            average frames encoded per second (in 0.1Hz)
 * @winकरोw_duration:    duration of the sampling winकरोw in 0.1ms
 * @cnt_winकरोw:         number of samples in the winकरोw
 * @winकरोw_stream_size: number of encoded bytes upon the sampling winकरोw
 * @last_bitrate:       bitrate upon the last sampling winकरोw
 * @min_bitrate:        minimum bitrate in kbps
 * @max_bitrate:        maximum bitrate in kbps
 * @avg_bitrate:        average bitrate in kbps
 */
काष्ठा hva_ctx_dbg अणु
	काष्ठा dentry	*debugfs_entry;
	bool		is_valid_period;
	kसमय_प्रकार		begin;
	u32		total_duration;
	u32		cnt_duration;
	u32		min_duration;
	u32		max_duration;
	u32		avg_duration;
	u32		max_fps;
	u32		total_period;
	u32		cnt_period;
	u32		min_period;
	u32		max_period;
	u32		avg_period;
	u32		total_stream_size;
	u32		avg_fps;
	u32		winकरोw_duration;
	u32		cnt_winकरोw;
	u32		winकरोw_stream_size;
	u32		last_bitrate;
	u32		min_bitrate;
	u32		max_bitrate;
	u32		avg_bitrate;
पूर्ण;
#पूर्ण_अगर

काष्ठा hva_dev;
काष्ठा hva_enc;

/**
 * काष्ठा hva_ctx - context of hva instance
 *
 * @hva_dev:         the device that this instance is associated with
 * @fh:              V4L2 file handle
 * @ctrl_handler:    V4L2 controls handler
 * @ctrls:           hva controls set
 * @id:              instance identअगरier
 * @पातing:        true अगर current job पातed
 * @name:            instance name (debug purpose)
 * @run_work:        encode work
 * @lock:            mutex used to lock access of this context
 * @flags:           validity of streaminfo and frameinfo fields
 * @frame_num:       frame number
 * @stream_num:      stream number
 * @max_stream_size: maximum size in bytes required क्रम stream data
 * @colorspace:      colorspace identअगरier
 * @xfer_func:       transfer function identअगरier
 * @ycbcr_enc:       Y'CbCr encoding identअगरier
 * @quantization:    quantization identअगरier
 * @streaminfo:      stream properties
 * @frameinfo:       frame properties
 * @enc:             current encoder
 * @priv:            निजी codec data क्रम this instance, allocated
 *                   by encoder @खोलो समय
 * @hw_err:          true अगर hardware error detected
 * @encoded_frames:  number of encoded frames
 * @sys_errors:      number of प्रणाली errors (memory, resource, pm...)
 * @encode_errors:   number of encoding errors (hw/driver errors)
 * @frame_errors:    number of frame errors (क्रमmat, size, header...)
 * @dbg:             context debug info
 */
काष्ठा hva_ctx अणु
	काष्ठा hva_dev			*hva_dev;
	काष्ठा v4l2_fh			fh;
	काष्ठा v4l2_ctrl_handler	ctrl_handler;
	काष्ठा hva_controls		ctrls;
	u8				id;
	bool				पातing;
	अक्षर				name[100];
	काष्ठा work_काष्ठा		run_work;
	/* mutex protecting this data काष्ठाure */
	काष्ठा mutex			lock;
	u32				flags;
	u32				frame_num;
	u32				stream_num;
	u32				max_stream_size;
	क्रमागत v4l2_colorspace		colorspace;
	क्रमागत v4l2_xfer_func		xfer_func;
	क्रमागत v4l2_ycbcr_encoding	ycbcr_enc;
	क्रमागत v4l2_quantization		quantization;
	काष्ठा hva_streaminfo		streaminfo;
	काष्ठा hva_frameinfo		frameinfo;
	काष्ठा hva_enc			*enc;
	व्योम				*priv;
	bool				hw_err;
	u32				encoded_frames;
	u32				sys_errors;
	u32				encode_errors;
	u32				frame_errors;
#अगर_घोषित CONFIG_VIDEO_STI_HVA_DEBUGFS
	काष्ठा hva_ctx_dbg		dbg;
#पूर्ण_अगर
पूर्ण;

#घोषणा HVA_FLAG_STREAMINFO	0x0001
#घोषणा HVA_FLAG_FRAMEINFO	0x0002

#अगर_घोषित CONFIG_VIDEO_STI_HVA_DEBUGFS
/**
 * काष्ठा hva_dev_dbg - device debug info
 *
 * @debugfs_entry: debugfs entry
 * @last_ctx:      debug inक्रमmation about last running instance context
 */
काष्ठा hva_dev_dbg अणु
	काष्ठा dentry	*debugfs_entry;
	काष्ठा hva_ctx	last_ctx;
पूर्ण;
#पूर्ण_अगर

#घोषणा HVA_MAX_INSTANCES	16
#घोषणा HVA_MAX_ENCODERS	10
#घोषणा HVA_MAX_FORMATS		HVA_MAX_ENCODERS

/**
 * काष्ठा hva_dev - असलtraction क्रम hva entity
 *
 * @v4l2_dev:            V4L2 device
 * @vdev:                video device
 * @pdev:                platक्रमm device
 * @dev:                 device
 * @lock:                mutex used क्रम critical sections & V4L2 ops
 *                       serialization
 * @m2m_dev:             memory-to-memory V4L2 device inक्रमmation
 * @instances:           खोलोed instances
 * @nb_of_instances:     number of खोलोed instances
 * @instance_id:         rolling counter identअगरying an instance (debug purpose)
 * @regs:                रेजिस्टर io memory access
 * @esram_addr:          esram address
 * @esram_size:          esram size
 * @clk:                 hva घड़ी
 * @irq_its:             status पूर्णांकerruption
 * @irq_err:             error पूर्णांकerruption
 * @work_queue:          work queue to handle the encode jobs
 * @protect_mutex:       mutex used to lock access of hardware
 * @पूर्णांकerrupt:           completion पूर्णांकerrupt
 * @ip_version:          IP hardware version
 * @encoders:            रेजिस्टरed encoders
 * @nb_of_encoders:      number of रेजिस्टरed encoders
 * @pixelक्रमmats:        supported uncompressed video क्रमmats
 * @nb_of_pixelक्रमmats:  number of supported umcompressed video क्रमmats
 * @streamक्रमmats:       supported compressed video क्रमmats
 * @nb_of_streamक्रमmats: number of supported compressed video क्रमmats
 * @sfl_reg:             status fअगरo level रेजिस्टर value
 * @sts_reg:             status रेजिस्टर value
 * @lmi_err_reg:         local memory पूर्णांकerface error रेजिस्टर value
 * @emi_err_reg:         बाह्यal memory पूर्णांकerface error रेजिस्टर value
 * @hec_mअगर_err_reg:     HEC memory पूर्णांकerface error रेजिस्टर value
 * @dbg:                 device debug info
 */
काष्ठा hva_dev अणु
	काष्ठा v4l2_device	v4l2_dev;
	काष्ठा video_device	*vdev;
	काष्ठा platक्रमm_device	*pdev;
	काष्ठा device		*dev;
	/* mutex protecting vb2_queue काष्ठाure */
	काष्ठा mutex		lock;
	काष्ठा v4l2_m2m_dev	*m2m_dev;
	काष्ठा hva_ctx		*instances[HVA_MAX_INSTANCES];
	अचिन्हित पूर्णांक		nb_of_instances;
	अचिन्हित पूर्णांक		instance_id;
	व्योम __iomem		*regs;
	u32			esram_addr;
	u32			esram_size;
	काष्ठा clk		*clk;
	पूर्णांक			irq_its;
	पूर्णांक			irq_err;
	काष्ठा workqueue_काष्ठा *work_queue;
	/* mutex protecting hardware access */
	काष्ठा mutex		protect_mutex;
	काष्ठा completion	पूर्णांकerrupt;
	अचिन्हित दीर्घ पूर्णांक	ip_version;
	स्थिर काष्ठा hva_enc	*encoders[HVA_MAX_ENCODERS];
	u32			nb_of_encoders;
	u32			pixelक्रमmats[HVA_MAX_FORMATS];
	u32			nb_of_pixelक्रमmats;
	u32			streamक्रमmats[HVA_MAX_FORMATS];
	u32			nb_of_streamक्रमmats;
	u32			sfl_reg;
	u32			sts_reg;
	u32			lmi_err_reg;
	u32			emi_err_reg;
	u32			hec_mअगर_err_reg;
#अगर_घोषित CONFIG_VIDEO_STI_HVA_DEBUGFS
	काष्ठा hva_dev_dbg	dbg;
#पूर्ण_अगर
पूर्ण;

/**
 * काष्ठा hva_enc - hva encoder
 *
 * @name:         encoder name
 * @streamक्रमmat: fourcc code क्रम compressed video क्रमmat (H.264...)
 * @pixelक्रमmat:  fourcc code क्रम uncompressed video क्रमmat
 * @max_width:    maximum width of frame क्रम this encoder
 * @max_height:   maximum height of frame क्रम this encoder
 * @खोलो:         खोलो encoder
 * @बंद:        बंद encoder
 * @encode:       encode a frame (काष्ठा hva_frame) in a stream
 *                (काष्ठा hva_stream)
 */

काष्ठा hva_enc अणु
	स्थिर अक्षर	*name;
	u32		streamक्रमmat;
	u32		pixelक्रमmat;
	u32		max_width;
	u32		max_height;
	पूर्णांक		(*खोलो)(काष्ठा hva_ctx *ctx);
	पूर्णांक		(*बंद)(काष्ठा hva_ctx *ctx);
	पूर्णांक		(*encode)(काष्ठा hva_ctx *ctx, काष्ठा hva_frame *frame,
				  काष्ठा hva_stream *stream);
पूर्ण;

#अगर_घोषित CONFIG_VIDEO_STI_HVA_DEBUGFS
व्योम hva_debugfs_create(काष्ठा hva_dev *hva);
व्योम hva_debugfs_हटाओ(काष्ठा hva_dev *hva);
व्योम hva_dbg_ctx_create(काष्ठा hva_ctx *ctx);
व्योम hva_dbg_ctx_हटाओ(काष्ठा hva_ctx *ctx);
व्योम hva_dbg_perf_begin(काष्ठा hva_ctx *ctx);
व्योम hva_dbg_perf_end(काष्ठा hva_ctx *ctx, काष्ठा hva_stream *stream);
#पूर्ण_अगर

#पूर्ण_अगर /* HVA_H */
