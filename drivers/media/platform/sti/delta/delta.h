<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) STMicroelectronics SA 2015
 * Author: Hugues Fruchet <hugues.fruchet@st.com> क्रम STMicroelectronics.
 */

#अगर_अघोषित DELTA_H
#घोषणा DELTA_H

#समावेश <linux/rpmsg.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-mem2स्मृति.स>

#समावेश "delta-cfg.h"

/*
 * क्रमागत delta_state - state of decoding instance
 *
 *@DELTA_STATE_WF_FORMAT:
 *	Wait क्रम compressed क्रमmat to be set by V4L2 client in order
 *	to know what is the relevant decoder to खोलो.
 *
 *@DELTA_STATE_WF_STREAMINFO:
 *	Wait क्रम stream inक्रमmation to be available (bitstream
 *	header parsing is करोne).
 *
 *@DELTA_STATE_READY:
 *	Decoding instance is पढ़ोy to decode compressed access unit.
 *
 *@DELTA_STATE_WF_EOS:
 *	Decoding instance is रुकोing क्रम EOS (End Of Stream) completion.
 *
 *@DELTA_STATE_EOS:
 *	EOS (End Of Stream) is completed (संकेतed to user). Decoding instance
 *	should then be बंदd.
 */
क्रमागत delta_state अणु
	DELTA_STATE_WF_FORMAT,
	DELTA_STATE_WF_STREAMINFO,
	DELTA_STATE_READY,
	DELTA_STATE_WF_EOS,
	DELTA_STATE_EOS
पूर्ण;

/*
 * काष्ठा delta_streaminfo - inक्रमmation about stream to decode
 *
 * @flags:		validity of fields (crop, pixelaspect, other)
 * @width:		width of video stream
 * @height:		height ""
 * @streamक्रमmat:	fourcc compressed क्रमmat of video (MJPEG, MPEG2, ...)
 * @dpb:		number of frames needed to decode a single frame
 *			(h264 dpb, up to 16)
 * @crop:		cropping winकरोw inside decoded frame (1920x1080@0,0
 *			inside 1920x1088 frame क्रम ex.)
 * @pixelaspect:	pixel aspect ratio of video (4/3, 5/4)
 * @field:		पूर्णांकerlaced or not
 * @profile:		profile string
 * @level:		level string
 * @other:		other string inक्रमmation from codec
 * @colorspace:		colorspace identअगरier
 * @xfer_func:		transfer function identअगरier
 * @ycbcr_enc:		Y'CbCr encoding identअगरier
 * @quantization:	quantization identअगरier
 */
काष्ठा delta_streaminfo अणु
	u32 flags;
	u32 streamक्रमmat;
	u32 width;
	u32 height;
	u32 dpb;
	काष्ठा v4l2_rect crop;
	काष्ठा v4l2_fract pixelaspect;
	क्रमागत v4l2_field field;
	u8 profile[32];
	u8 level[32];
	u8 other[32];
	क्रमागत v4l2_colorspace colorspace;
	क्रमागत v4l2_xfer_func xfer_func;
	क्रमागत v4l2_ycbcr_encoding ycbcr_enc;
	क्रमागत v4l2_quantization quantization;
पूर्ण;

#घोषणा DELTA_STREAMINFO_FLAG_CROP		0x0001
#घोषणा DELTA_STREAMINFO_FLAG_PIXELASPECT	0x0002
#घोषणा DELTA_STREAMINFO_FLAG_OTHER		0x0004

/*
 * काष्ठा delta_au - access unit काष्ठाure.
 *
 * @vbuf:	video buffer inक्रमmation क्रम V4L2
 * @list:	V4L2 m2m list that the frame beदीर्घs to
 * @prepared:	अगर set vaddr/paddr are resolved
 * @vaddr:	भव address (kernel can पढ़ो/ग_लिखो)
 * @paddr:	physical address (क्रम hardware)
 * @flags:	access unit type (V4L2_BUF_FLAG_KEYFRAME/PFRAME/BFRAME)
 * @dts:	decoding बारtamp of this access unit
 */
काष्ठा delta_au अणु
	काष्ठा vb2_v4l2_buffer vbuf;	/* keep first */
	काष्ठा list_head list;	/* keep second */

	bool prepared;
	u32 size;
	व्योम *vaddr;
	dma_addr_t paddr;
	u32 flags;
	u64 dts;
पूर्ण;

/*
 * काष्ठा delta_frameinfo - inक्रमmation about decoded frame
 *
 * @flags:		validity of fields (crop, pixelaspect)
 * @pixelक्रमmat:	fourcc code क्रम uncompressed video क्रमmat
 * @width:		width of frame
 * @height:		height of frame
 * @aligned_width:	width of frame (with encoder or decoder alignment
 *			स्थिरraपूर्णांक)
 * @aligned_height:	height of frame (with encoder or decoder alignment
 *			स्थिरraपूर्णांक)
 * @size:		maximum size in bytes required क्रम data
 * @crop:		cropping winकरोw inside frame (1920x1080@0,0
 *			inside 1920x1088 frame क्रम ex.)
 * @pixelaspect:	pixel aspect ratio of video (4/3, 5/4)
 * @field:		पूर्णांकerlaced mode
 * @colorspace:		colorspace identअगरier
 * @xfer_func:		transfer function identअगरier
 * @ycbcr_enc:		Y'CbCr encoding identअगरier
 * @quantization:	quantization identअगरier
 */
काष्ठा delta_frameinfo अणु
	u32 flags;
	u32 pixelक्रमmat;
	u32 width;
	u32 height;
	u32 aligned_width;
	u32 aligned_height;
	u32 size;
	काष्ठा v4l2_rect crop;
	काष्ठा v4l2_fract pixelaspect;
	क्रमागत v4l2_field field;
	क्रमागत v4l2_colorspace colorspace;
	क्रमागत v4l2_xfer_func xfer_func;
	क्रमागत v4l2_ycbcr_encoding ycbcr_enc;
	क्रमागत v4l2_quantization quantization;
पूर्ण;

#घोषणा DELTA_FRAMEINFO_FLAG_CROP		0x0001
#घोषणा DELTA_FRAMEINFO_FLAG_PIXELASPECT	0x0002

/*
 * काष्ठा delta_frame - frame काष्ठाure.
 *
 * @vbuf:	video buffer inक्रमmation क्रम V4L2
 * @list:	V4L2 m2m list that the frame beदीर्घs to
 * @info:	frame inक्रमmation (width, height, क्रमmat, alignment...)
 * @prepared:	अगर set pix/vaddr/paddr are resolved
 * @index:	frame index, aligned on V4L2 wow
 * @vaddr:	भव address (kernel can पढ़ो/ग_लिखो)
 * @paddr:	physical address (क्रम hardware)
 * @state:	frame state क्रम frame lअगरecycle tracking
 *		(DELTA_FRAME_FREE/DEC/OUT/REC/...)
 * @flags:	frame type (V4L2_BUF_FLAG_KEYFRAME/PFRAME/BFRAME)
 * @dts:	decoding बारtamp of this frame
 * @field:	field order क्रम पूर्णांकerlaced frame
 */
काष्ठा delta_frame अणु
	काष्ठा vb2_v4l2_buffer vbuf;	/* keep first */
	काष्ठा list_head list;	/* keep second */

	काष्ठा delta_frameinfo info;
	bool prepared;
	u32 index;
	व्योम *vaddr;
	dma_addr_t paddr;
	u32 state;
	u32 flags;
	u64 dts;
	क्रमागत v4l2_field field;
पूर्ण;

/* frame state क्रम frame lअगरecycle tracking */
#घोषणा DELTA_FRAME_FREE	0x00 /* is मुक्त and can be used क्रम decoding */
#घोषणा DELTA_FRAME_REF		0x01 /* is a reference frame */
#घोषणा DELTA_FRAME_BSY		0x02 /* is owned by decoder and busy */
#घोषणा DELTA_FRAME_DEC		0x04 /* contains decoded content */
#घोषणा DELTA_FRAME_OUT		0x08 /* has been given to user */
#घोषणा DELTA_FRAME_RDY		0x10 /* is पढ़ोy but still held by decoder */
#घोषणा DELTA_FRAME_M2M		0x20 /* is owned by mem2mem framework */

/*
 * काष्ठा delta_dts - decoding बारtamp.
 *
 * @list:	list to chain बारtamps
 * @val:	बारtamp in microseconds
 */
काष्ठा delta_dts अणु
	काष्ठा list_head list;
	u64 val;
पूर्ण;

काष्ठा delta_buf अणु
	u32 size;
	व्योम *vaddr;
	dma_addr_t paddr;
	स्थिर अक्षर *name;
	अचिन्हित दीर्घ attrs;
पूर्ण;

काष्ठा delta_ipc_ctx अणु
	पूर्णांक cb_err;
	u32 copro_hdl;
	काष्ठा completion करोne;
	काष्ठा delta_buf ipc_buf_काष्ठा;
	काष्ठा delta_buf *ipc_buf;
पूर्ण;

काष्ठा delta_ipc_param अणु
	u32 size;
	व्योम *data;
पूर्ण;

काष्ठा delta_ctx;

/*
 * काष्ठा delta_dec - decoder काष्ठाure.
 *
 * @name:		name of this decoder
 * @streamक्रमmat:	input stream क्रमmat that this decoder support
 * @pixelक्रमmat:	pixel क्रमmat of decoded frame that this decoder support
 * @max_width:		(optional) maximum width that can decode this decoder
 *			अगर not set, maximum width is DELTA_MAX_WIDTH
 * @max_height:		(optional) maximum height that can decode this decoder
 *			अगर not set, maximum height is DELTA_MAX_HEIGHT
 * @pm:			(optional) अगर set, decoder will manage घातer on its own
 * @खोलो:		खोलो this decoder
 * @बंद:		बंद this decoder
 * @setup_frame:	setup frame to be used by decoder, see below
 * @get_streaminfo:	get stream related infos, see below
 * @get_frameinfo:	get decoded frame related infos, see below
 * @set_frameinfo:	(optional) set decoded frame related infos, see below
 * @setup_frame:	setup frame to be used by decoder, see below
 * @decode:		decode a single access unit, see below
 * @get_frame:		get the next decoded frame available, see below
 * @recycle:		recycle the given frame, see below
 * @flush:		(optional) flush decoder, see below
 * @drain:		(optional) drain decoder, see below
 */
काष्ठा delta_dec अणु
	स्थिर अक्षर *name;
	u32 streamक्रमmat;
	u32 pixelक्रमmat;
	u32 max_width;
	u32 max_height;
	bool pm;

	/*
	 * decoder ops
	 */
	पूर्णांक (*खोलो)(काष्ठा delta_ctx *ctx);
	पूर्णांक (*बंद)(काष्ठा delta_ctx *ctx);

	/*
	 * setup_frame() - setup frame to be used by decoder
	 * @ctx:	(in) instance
	 * @frame:	(in) frame to use
	 *  @frame.index	(in) identअगरier of frame
	 *  @frame.vaddr	(in) भव address (kernel can पढ़ो/ग_लिखो)
	 *  @frame.paddr	(in) physical address (क्रम hardware)
	 *
	 * Frame is to be allocated by caller, then given
	 * to decoder through this call.
	 * Several frames must be given to decoder (dpb),
	 * each frame is identअगरied using its index.
	 */
	पूर्णांक (*setup_frame)(काष्ठा delta_ctx *ctx, काष्ठा delta_frame *frame);

	/*
	 * get_streaminfo() - get stream related infos
	 * @ctx:	(in) instance
	 * @streaminfo:	(out) width, height, dpb,...
	 *
	 * Precondition: stream header must have been successfully
	 * parsed to have this call successful & @streaminfo valid.
	 * Header parsing must be करोne using decode(), giving
	 * explicitly header access unit or first access unit of bitstream.
	 * If no valid header is found, get_streaminfo will वापस -ENODATA,
	 * in this हाल the next bitstream access unit must be decoded till
	 * get_streaminfo becomes successful.
	 */
	पूर्णांक (*get_streaminfo)(काष्ठा delta_ctx *ctx,
			      काष्ठा delta_streaminfo *streaminfo);

	/*
	 * get_frameinfo() - get decoded frame related infos
	 * @ctx:	(in) instance
	 * @frameinfo:	(out) width, height, alignment, crop, ...
	 *
	 * Precondition: get_streaminfo() must be successful
	 */
	पूर्णांक (*get_frameinfo)(काष्ठा delta_ctx *ctx,
			     काष्ठा delta_frameinfo *frameinfo);

	/*
	 * set_frameinfo() - set decoded frame related infos
	 * @ctx:	(in) instance
	 * @frameinfo:	(out) width, height, alignment, crop, ...
	 *
	 * Optional.
	 * Typically used to negotiate with decoder the output
	 * frame अगर decoder can करो post-processing.
	 */
	पूर्णांक (*set_frameinfo)(काष्ठा delta_ctx *ctx,
			     काष्ठा delta_frameinfo *frameinfo);

	/*
	 * decode() - decode a single access unit
	 * @ctx:	(in) instance
	 * @au:		(in/out) access unit
	 *  @au.size	(in) size of au to decode
	 *  @au.vaddr	(in) भव address (kernel can पढ़ो/ग_लिखो)
	 *  @au.paddr	(in) physical address (क्रम hardware)
	 *  @au.flags	(out) au type (V4L2_BUF_FLAG_KEYFRAME/
	 *			PFRAME/BFRAME)
	 *
	 * Decode the access unit given. Decode is synchronous;
	 * access unit memory is no more needed after this call.
	 * After this call, none, one or several frames could
	 * have been decoded, which can be retrieved using
	 * get_frame().
	 */
	पूर्णांक (*decode)(काष्ठा delta_ctx *ctx, काष्ठा delta_au *au);

	/*
	 * get_frame() - get the next decoded frame available
	 * @ctx:	(in) instance
	 * @frame:	(out) frame with decoded data:
	 *  @frame.index	(out) identअगरier of frame
	 *  @frame.field	(out) field order क्रम पूर्णांकerlaced frame
	 *  @frame.state	(out) frame state क्रम frame lअगरecycle tracking
	 *  @frame.flags	(out) frame type (V4L2_BUF_FLAG_KEYFRAME/
	 *			PFRAME/BFRAME)
	 *
	 * Get the next available decoded frame.
	 * If no frame is available, -ENODATA is वापसed.
	 * If a frame is available, frame काष्ठाure is filled with
	 * relevant data, frame.index identअगरying this exact frame.
	 * When this frame is no more needed by upper layers,
	 * recycle() must be called giving this frame identअगरier.
	 */
	पूर्णांक (*get_frame)(काष्ठा delta_ctx *ctx, काष्ठा delta_frame **frame);

	/*
	 * recycle() - recycle the given frame
	 * @ctx:	(in) instance
	 * @frame:	(in) frame to recycle:
	 *  @frame.index	(in) identअगरier of frame
	 *
	 * recycle() is to be called by user when the decoded frame
	 * is no more needed (composition/display करोne).
	 * This frame will then be reused by decoder to proceed
	 * with next frame decoding.
	 * If not enough frames have been provided through setup_frame(),
	 * or recycle() is not called fast enough, the decoder can run out
	 * of available frames to proceed with decoding (starvation).
	 * This हाल is guarded by wq_recycle रुको queue which ensures that
	 * decoder is called only अगर at least one frame is available.
	 */
	पूर्णांक (*recycle)(काष्ठा delta_ctx *ctx, काष्ठा delta_frame *frame);

	/*
	 * flush() - flush decoder
	 * @ctx:	(in) instance
	 *
	 * Optional.
	 * Reset decoder context and discard all पूर्णांकernal buffers.
	 * This allows implementation of seek, which leads to discontinuity
	 * of input bitstream that decoder must know to restart its पूर्णांकernal
	 * decoding logic.
	 */
	पूर्णांक (*flush)(काष्ठा delta_ctx *ctx);

	/*
	 * drain() - drain decoder
	 * @ctx:	(in) instance
	 *
	 * Optional.
	 * Mark decoder pending frames (decoded but not yet output) as पढ़ोy
	 * so that they can be output to client at EOS (End Of Stream).
	 * get_frame() is to be called in a loop right after drain() to
	 * get all those pending frames.
	 */
	पूर्णांक (*drain)(काष्ठा delta_ctx *ctx);
पूर्ण;

काष्ठा delta_dev;

/*
 * काष्ठा delta_ctx - instance काष्ठाure.
 *
 * @flags:		validity of fields (streaminfo)
 * @fh:			V4L2 file handle
 * @dev:		device context
 * @dec:		selected decoder context क्रम this instance
 * @ipc_ctx:		context of IPC communication with firmware
 * @state:		instance state
 * @frame_num:		frame number
 * @au_num:		access unit number
 * @max_au_size:	max size of an access unit
 * @streaminfo:		stream inक्रमmation (width, height, dpb, पूर्णांकerlacing...)
 * @frameinfo:		frame inक्रमmation (width, height, क्रमmat, alignment...)
 * @nb_of_frames:	number of frames available क्रम decoding
 * @frames:		array of decoding frames to keep track of frame
 *			state and manage frame recycling
 * @decoded_frames:	nb of decoded frames from खोलोing
 * @output_frames:	nb of output frames from खोलोing
 * @dropped_frames:	nb of frames dropped (ie access unit not parsed
 *			or frame decoded but not output)
 * @stream_errors:	nb of stream errors (corrupted, not supported, ...)
 * @decode_errors:	nb of decode errors (firmware error)
 * @sys_errors:		nb of प्रणाली errors (memory, ipc, ...)
 * @dts:		FIFO of decoding बारtamp.
 *			output frames are बारtamped with incoming access
 *			unit बारtamps using this fअगरo.
 * @name:		string naming this instance (debug purpose)
 * @run_work:		decoding work
 * @lock:		lock क्रम decoding work serialization
 * @पातing:		true अगर current job पातed
 * @priv:		निजी decoder context क्रम this instance, allocated
 *			by decoder @खोलो समय.
 */
काष्ठा delta_ctx अणु
	u32 flags;
	काष्ठा v4l2_fh fh;
	काष्ठा delta_dev *dev;
	स्थिर काष्ठा delta_dec *dec;
	काष्ठा delta_ipc_ctx ipc_ctx;

	क्रमागत delta_state state;
	u32 frame_num;
	u32 au_num;
	माप_प्रकार max_au_size;
	काष्ठा delta_streaminfo streaminfo;
	काष्ठा delta_frameinfo frameinfo;
	u32 nb_of_frames;
	काष्ठा delta_frame *frames[DELTA_MAX_FRAMES];
	u32 decoded_frames;
	u32 output_frames;
	u32 dropped_frames;
	u32 stream_errors;
	u32 decode_errors;
	u32 sys_errors;
	काष्ठा list_head dts;
	अक्षर name[100];
	काष्ठा work_काष्ठा run_work;
	काष्ठा mutex lock;
	bool पातing;
	व्योम *priv;
पूर्ण;

#घोषणा DELTA_FLAG_STREAMINFO 0x0001
#घोषणा DELTA_FLAG_FRAMEINFO 0x0002

#घोषणा DELTA_MAX_FORMATS  DELTA_MAX_DECODERS

/*
 * काष्ठा delta_dev - device काष्ठा, 1 per probe (so single one क्रम
 * all platक्रमm lअगरe)
 *
 * @v4l2_dev:		v4l2 device
 * @vdev:		v4l2 video device
 * @pdev:		platक्रमm device
 * @dev:		device
 * @m2m_dev:		memory-to-memory V4L2 device
 * @lock:		device lock, क्रम crit section & V4L2 ops serialization.
 * @clk_delta:		delta मुख्य घड़ी
 * @clk_st231:		st231 coprocessor मुख्य घड़ी
 * @clk_flash_promip:	flash promip घड़ी
 * @decoders:		list of रेजिस्टरed decoders
 * @nb_of_decoders:	nb of रेजिस्टरed decoders
 * @pixelक्रमmats:	supported uncompressed video क्रमmats
 * @nb_of_pixelक्रमmats:	number of supported umcompressed video क्रमmats
 * @streamक्रमmats:	supported compressed video क्रमmats
 * @nb_of_streamक्रमmats:number of supported compressed video क्रमmats
 * @instance_id:	rolling counter identअगरying an instance (debug purpose)
 * @work_queue:		decoding job work queue
 * @rpmsg_driver:	rpmsg IPC driver
 * @rpmsg_device:	rpmsg IPC device
 */
काष्ठा delta_dev अणु
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा video_device *vdev;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा device *dev;
	काष्ठा v4l2_m2m_dev *m2m_dev;
	काष्ठा mutex lock;
	काष्ठा clk *clk_delta;
	काष्ठा clk *clk_st231;
	काष्ठा clk *clk_flash_promip;
	स्थिर काष्ठा delta_dec *decoders[DELTA_MAX_DECODERS];
	u32 nb_of_decoders;
	u32 pixelक्रमmats[DELTA_MAX_FORMATS];
	u32 nb_of_pixelक्रमmats;
	u32 streamक्रमmats[DELTA_MAX_FORMATS];
	u32 nb_of_streamक्रमmats;
	u8 instance_id;
	काष्ठा workqueue_काष्ठा *work_queue;
	काष्ठा rpmsg_driver rpmsg_driver;
	काष्ठा rpmsg_device *rpmsg_device;
पूर्ण;

अटल अंतरभूत अक्षर *frame_type_str(u32 flags)
अणु
	अगर (flags & V4L2_BUF_FLAG_KEYFRAME)
		वापस "I";
	अगर (flags & V4L2_BUF_FLAG_PFRAME)
		वापस "P";
	अगर (flags & V4L2_BUF_FLAG_BFRAME)
		वापस "B";
	अगर (flags & V4L2_BUF_FLAG_LAST)
		वापस "EOS";
	वापस "?";
पूर्ण

अटल अंतरभूत अक्षर *frame_field_str(क्रमागत v4l2_field field)
अणु
	अगर (field == V4L2_FIELD_NONE)
		वापस "-";
	अगर (field == V4L2_FIELD_TOP)
		वापस "T";
	अगर (field == V4L2_FIELD_BOTTOM)
		वापस "B";
	अगर (field == V4L2_FIELD_INTERLACED)
		वापस "I";
	अगर (field == V4L2_FIELD_INTERLACED_TB)
		वापस "TB";
	अगर (field == V4L2_FIELD_INTERLACED_BT)
		वापस "BT";
	वापस "?";
पूर्ण

अटल अंतरभूत अक्षर *frame_state_str(u32 state, अक्षर *str, अचिन्हित पूर्णांक len)
अणु
	snम_लिखो(str, len, "%s %s %s %s %s %s",
		 (state & DELTA_FRAME_REF)  ? "ref" : "   ",
		 (state & DELTA_FRAME_BSY)  ? "bsy" : "   ",
		 (state & DELTA_FRAME_DEC)  ? "dec" : "   ",
		 (state & DELTA_FRAME_OUT)  ? "out" : "   ",
		 (state & DELTA_FRAME_M2M)  ? "m2m" : "   ",
		 (state & DELTA_FRAME_RDY)  ? "rdy" : "   ");
	वापस str;
पूर्ण

पूर्णांक delta_get_frameinfo_शेष(काष्ठा delta_ctx *ctx,
				काष्ठा delta_frameinfo *frameinfo);
पूर्णांक delta_recycle_शेष(काष्ठा delta_ctx *pctx,
			  काष्ठा delta_frame *frame);

पूर्णांक delta_get_मुक्त_frame(काष्ठा delta_ctx *ctx,
			 काष्ठा delta_frame **pframe);

पूर्णांक delta_get_sync(काष्ठा delta_ctx *ctx);
व्योम delta_put_स्वतःsuspend(काष्ठा delta_ctx *ctx);

#पूर्ण_अगर /* DELTA_H */
