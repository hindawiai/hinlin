<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM hda_controller
#घोषणा TRACE_INCLUDE_खाता hda_controller_trace

#अगर !defined(_TRACE_HDA_CONTROLLER_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_HDA_CONTROLLER_H

#समावेश <linux/tracepoपूर्णांक.h>

काष्ठा azx;
काष्ठा azx_dev;

TRACE_EVENT(azx_pcm_trigger,

	TP_PROTO(काष्ठा azx *chip, काष्ठा azx_dev *dev, पूर्णांक cmd),

	TP_ARGS(chip, dev, cmd),

	TP_STRUCT__entry(
		__field( पूर्णांक, card )
		__field( पूर्णांक, idx )
		__field( पूर्णांक, cmd )
	),

	TP_fast_assign(
		__entry->card = (chip)->card->number;
		__entry->idx = (dev)->core.index;
		__entry->cmd = cmd;
	),

	TP_prपूर्णांकk("[%d:%d] cmd=%d", __entry->card, __entry->idx, __entry->cmd)
);

TRACE_EVENT(azx_get_position,

    TP_PROTO(काष्ठा azx *chip, काष्ठा azx_dev *dev, अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक delay),

	    TP_ARGS(chip, dev, pos, delay),

	TP_STRUCT__entry(
		__field( पूर्णांक, card )
		__field( पूर्णांक, idx )
		__field( अचिन्हित पूर्णांक, pos )
		__field( अचिन्हित पूर्णांक, delay )
	),

	TP_fast_assign(
		__entry->card = (chip)->card->number;
		__entry->idx = (dev)->core.index;
		__entry->pos = pos;
		__entry->delay = delay;
	),

	TP_prपूर्णांकk("[%d:%d] pos=%u, delay=%u", __entry->card, __entry->idx, __entry->pos, __entry->delay)
);

DECLARE_EVENT_CLASS(azx_pcm,
	TP_PROTO(काष्ठा azx *chip, काष्ठा azx_dev *azx_dev),

	TP_ARGS(chip, azx_dev),

	TP_STRUCT__entry(
		__field( अचिन्हित अक्षर, stream_tag )
	),

	TP_fast_assign(
		__entry->stream_tag = (azx_dev)->core.stream_tag;
	),

	TP_prपूर्णांकk("stream_tag: %d", __entry->stream_tag)
);

DEFINE_EVENT(azx_pcm, azx_pcm_खोलो,
	TP_PROTO(काष्ठा azx *chip, काष्ठा azx_dev *azx_dev),
	TP_ARGS(chip, azx_dev)
);

DEFINE_EVENT(azx_pcm, azx_pcm_बंद,
	TP_PROTO(काष्ठा azx *chip, काष्ठा azx_dev *azx_dev),
	TP_ARGS(chip, azx_dev)
);

DEFINE_EVENT(azx_pcm, azx_pcm_hw_params,
	TP_PROTO(काष्ठा azx *chip, काष्ठा azx_dev *azx_dev),
	TP_ARGS(chip, azx_dev)
);

DEFINE_EVENT(azx_pcm, azx_pcm_prepare,
	TP_PROTO(काष्ठा azx *chip, काष्ठा azx_dev *azx_dev),
	TP_ARGS(chip, azx_dev)
);

#पूर्ण_अगर /* _TRACE_HDA_CONTROLLER_H */

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#समावेश <trace/define_trace.h>
