<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * vsp1_pipe.h  --  R-Car VSP1 Pipeline
 *
 * Copyright (C) 2013-2015 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */
#अगर_अघोषित __VSP1_PIPE_H__
#घोषणा __VSP1_PIPE_H__

#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/रुको.h>

#समावेश <media/media-entity.h>

काष्ठा vsp1_dl_list;
काष्ठा vsp1_rwpf;

/*
 * काष्ठा vsp1_क्रमmat_info - VSP1 video क्रमmat description
 * @fourcc: V4L2 pixel क्रमmat FCC identअगरier
 * @mbus: media bus क्रमmat code
 * @hwfmt: VSP1 hardware क्रमmat
 * @swap: swap रेजिस्टर control
 * @planes: number of planes
 * @bpp: bits per pixel
 * @swap_yc: the Y and C components are swapped (Y comes beक्रमe C)
 * @swap_uv: the U and V components are swapped (V comes beक्रमe U)
 * @hsub: horizontal subsampling factor
 * @vsub: vertical subsampling factor
 * @alpha: has an alpha channel
 */
काष्ठा vsp1_क्रमmat_info अणु
	u32 fourcc;
	अचिन्हित पूर्णांक mbus;
	अचिन्हित पूर्णांक hwfmt;
	अचिन्हित पूर्णांक swap;
	अचिन्हित पूर्णांक planes;
	अचिन्हित पूर्णांक bpp[3];
	bool swap_yc;
	bool swap_uv;
	अचिन्हित पूर्णांक hsub;
	अचिन्हित पूर्णांक vsub;
	bool alpha;
पूर्ण;

क्रमागत vsp1_pipeline_state अणु
	VSP1_PIPELINE_STOPPED,
	VSP1_PIPELINE_RUNNING,
	VSP1_PIPELINE_STOPPING,
पूर्ण;

/*
 * काष्ठा vsp1_partition_winकरोw - Partition winकरोw coordinates
 * @left: horizontal coordinate of the partition start in pixels relative to the
 *	  left edge of the image
 * @width: partition width in pixels
 */
काष्ठा vsp1_partition_winकरोw अणु
	अचिन्हित पूर्णांक left;
	अचिन्हित पूर्णांक width;
पूर्ण;

/*
 * काष्ठा vsp1_partition - A description of a slice क्रम the partition algorithm
 * @rpf: The RPF partition winकरोw configuration
 * @uds_sink: The UDS input partition winकरोw configuration
 * @uds_source: The UDS output partition winकरोw configuration
 * @sru: The SRU partition winकरोw configuration
 * @wpf: The WPF partition winकरोw configuration
 */
काष्ठा vsp1_partition अणु
	काष्ठा vsp1_partition_winकरोw rpf;
	काष्ठा vsp1_partition_winकरोw uds_sink;
	काष्ठा vsp1_partition_winकरोw uds_source;
	काष्ठा vsp1_partition_winकरोw sru;
	काष्ठा vsp1_partition_winकरोw wpf;
पूर्ण;

/*
 * काष्ठा vsp1_pipeline - A VSP1 hardware pipeline
 * @pipe: the media pipeline
 * @irqlock: protects the pipeline state
 * @state: current state
 * @wq: रुको queue to रुको क्रम state change completion
 * @frame_end: frame end पूर्णांकerrupt handler
 * @lock: protects the pipeline use count and stream count
 * @kref: pipeline reference count
 * @stream_count: number of streaming video nodes
 * @buffers_पढ़ोy: biपंचांगask of RPFs and WPFs with at least one buffer available
 * @sequence: frame sequence number
 * @num_inमाला_दो: number of RPFs
 * @inमाला_दो: array of RPFs in the pipeline (indexed by RPF index)
 * @output: WPF at the output of the pipeline
 * @brx: BRx entity, अगर present
 * @hgo: HGO entity, अगर present
 * @hgt: HGT entity, अगर present
 * @lअगर: LIF entity, अगर present
 * @uds: UDS entity, अगर present
 * @uds_input: entity at the input of the UDS, अगर the UDS is present
 * @entities: list of entities in the pipeline
 * @stream_config: cached stream configuration क्रम video pipelines
 * @configured: when false the @stream_config shall be written to the hardware
 * @पूर्णांकerlaced: True when the pipeline is configured in पूर्णांकerlaced mode
 * @partitions: The number of partitions used to process one frame
 * @partition: The current partition क्रम configuration to process
 * @part_table: The pre-calculated partitions used by the pipeline
 */
काष्ठा vsp1_pipeline अणु
	काष्ठा media_pipeline pipe;

	spinlock_t irqlock;
	क्रमागत vsp1_pipeline_state state;
	रुको_queue_head_t wq;

	व्योम (*frame_end)(काष्ठा vsp1_pipeline *pipe, अचिन्हित पूर्णांक completion);

	काष्ठा mutex lock;
	काष्ठा kref kref;
	अचिन्हित पूर्णांक stream_count;
	अचिन्हित पूर्णांक buffers_पढ़ोy;
	अचिन्हित पूर्णांक sequence;

	अचिन्हित पूर्णांक num_inमाला_दो;
	काष्ठा vsp1_rwpf *inमाला_दो[VSP1_MAX_RPF];
	काष्ठा vsp1_rwpf *output;
	काष्ठा vsp1_entity *brx;
	काष्ठा vsp1_entity *hgo;
	काष्ठा vsp1_entity *hgt;
	काष्ठा vsp1_entity *lअगर;
	काष्ठा vsp1_entity *uds;
	काष्ठा vsp1_entity *uds_input;

	/*
	 * The order of this list must be identical to the order of the entities
	 * in the pipeline, as it is assumed by the partition algorithm that we
	 * can walk this list in sequence.
	 */
	काष्ठा list_head entities;

	काष्ठा vsp1_dl_body *stream_config;
	bool configured;
	bool पूर्णांकerlaced;

	अचिन्हित पूर्णांक partitions;
	काष्ठा vsp1_partition *partition;
	काष्ठा vsp1_partition *part_table;
पूर्ण;

व्योम vsp1_pipeline_reset(काष्ठा vsp1_pipeline *pipe);
व्योम vsp1_pipeline_init(काष्ठा vsp1_pipeline *pipe);

व्योम vsp1_pipeline_run(काष्ठा vsp1_pipeline *pipe);
bool vsp1_pipeline_stopped(काष्ठा vsp1_pipeline *pipe);
पूर्णांक vsp1_pipeline_stop(काष्ठा vsp1_pipeline *pipe);
bool vsp1_pipeline_पढ़ोy(काष्ठा vsp1_pipeline *pipe);

व्योम vsp1_pipeline_frame_end(काष्ठा vsp1_pipeline *pipe);

व्योम vsp1_pipeline_propagate_alpha(काष्ठा vsp1_pipeline *pipe,
				   काष्ठा vsp1_dl_body *dlb,
				   अचिन्हित पूर्णांक alpha);

व्योम vsp1_pipeline_propagate_partition(काष्ठा vsp1_pipeline *pipe,
				       काष्ठा vsp1_partition *partition,
				       अचिन्हित पूर्णांक index,
				       काष्ठा vsp1_partition_winकरोw *winकरोw);

स्थिर काष्ठा vsp1_क्रमmat_info *vsp1_get_क्रमmat_info(काष्ठा vsp1_device *vsp1,
						    u32 fourcc);

#पूर्ण_अगर /* __VSP1_PIPE_H__ */
