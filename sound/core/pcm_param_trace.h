<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM snd_pcm

#अगर !defined(_PCM_PARAMS_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _PCM_PARAMS_TRACE_H

#समावेश <linux/tracepoपूर्णांक.h>

#घोषणा HW_PARAM_ENTRY(param) अणुSNDRV_PCM_HW_PARAM_##param, #paramपूर्ण
#घोषणा hw_param_labels			\
	HW_PARAM_ENTRY(ACCESS),		\
	HW_PARAM_ENTRY(FORMAT),		\
	HW_PARAM_ENTRY(SUBFORMAT),	\
	HW_PARAM_ENTRY(SAMPLE_BITS),	\
	HW_PARAM_ENTRY(FRAME_BITS),	\
	HW_PARAM_ENTRY(CHANNELS),	\
	HW_PARAM_ENTRY(RATE),		\
	HW_PARAM_ENTRY(PERIOD_TIME),	\
	HW_PARAM_ENTRY(PERIOD_SIZE),	\
	HW_PARAM_ENTRY(PERIOD_BYTES),	\
	HW_PARAM_ENTRY(PERIODS),	\
	HW_PARAM_ENTRY(BUFFER_TIME),	\
	HW_PARAM_ENTRY(BUFFER_SIZE),	\
	HW_PARAM_ENTRY(BUFFER_BYTES),	\
	HW_PARAM_ENTRY(TICK_TIME)

TRACE_EVENT(hw_mask_param,
	TP_PROTO(काष्ठा snd_pcm_substream *substream, snd_pcm_hw_param_t type, पूर्णांक index, स्थिर काष्ठा snd_mask *prev, स्थिर काष्ठा snd_mask *curr),
	TP_ARGS(substream, type, index, prev, curr),
	TP_STRUCT__entry(
		__field(पूर्णांक, card)
		__field(पूर्णांक, device)
		__field(पूर्णांक, subdevice)
		__field(पूर्णांक, direction)
		__field(snd_pcm_hw_param_t, type)
		__field(पूर्णांक, index)
		__field(पूर्णांक, total)
		__array(__u32, prev_bits, 8)
		__array(__u32, curr_bits, 8)
	),
	TP_fast_assign(
		__entry->card = substream->pcm->card->number;
		__entry->device = substream->pcm->device;
		__entry->subdevice = substream->number;
		__entry->direction = substream->stream;
		__entry->type = type;
		__entry->index = index;
		__entry->total = substream->runसमय->hw_स्थिरraपूर्णांकs.rules_num;
		स_नकल(__entry->prev_bits, prev->bits, माप(__u32) * 8);
		स_नकल(__entry->curr_bits, curr->bits, माप(__u32) * 8);
	),
	TP_prपूर्णांकk("pcmC%dD%d%s:%d %03d/%03d %s %08x%08x%08x%08x %08x%08x%08x%08x",
		  __entry->card,
		  __entry->device,
		  __entry->direction ? "c" : "p",
		  __entry->subdevice,
		  __entry->index,
		  __entry->total,
		  __prपूर्णांक_symbolic(__entry->type, hw_param_labels),
		  __entry->prev_bits[3], __entry->prev_bits[2],
		  __entry->prev_bits[1], __entry->prev_bits[0],
		  __entry->curr_bits[3], __entry->curr_bits[2],
		  __entry->curr_bits[1], __entry->curr_bits[0]
	)
);

TRACE_EVENT(hw_पूर्णांकerval_param,
	TP_PROTO(काष्ठा snd_pcm_substream *substream, snd_pcm_hw_param_t type, पूर्णांक index, स्थिर काष्ठा snd_पूर्णांकerval *prev, स्थिर काष्ठा snd_पूर्णांकerval *curr),
	TP_ARGS(substream, type, index, prev, curr),
	TP_STRUCT__entry(
		__field(पूर्णांक, card)
		__field(पूर्णांक, device)
		__field(पूर्णांक, subdevice)
		__field(पूर्णांक, direction)
		__field(snd_pcm_hw_param_t, type)
		__field(पूर्णांक, index)
		__field(पूर्णांक, total)
		__field(अचिन्हित पूर्णांक, prev_min)
		__field(अचिन्हित पूर्णांक, prev_max)
		__field(अचिन्हित पूर्णांक, prev_खोलोmin)
		__field(अचिन्हित पूर्णांक, prev_खोलोmax)
		__field(अचिन्हित पूर्णांक, prev_पूर्णांकeger)
		__field(अचिन्हित पूर्णांक, prev_empty)
		__field(अचिन्हित पूर्णांक, curr_min)
		__field(अचिन्हित पूर्णांक, curr_max)
		__field(अचिन्हित पूर्णांक, curr_खोलोmin)
		__field(अचिन्हित पूर्णांक, curr_खोलोmax)
		__field(अचिन्हित पूर्णांक, curr_पूर्णांकeger)
		__field(अचिन्हित पूर्णांक, curr_empty)
	),
	TP_fast_assign(
		__entry->card = substream->pcm->card->number;
		__entry->device = substream->pcm->device;
		__entry->subdevice = substream->number;
		__entry->direction = substream->stream;
		__entry->type = type;
		__entry->index = index;
		__entry->total = substream->runसमय->hw_स्थिरraपूर्णांकs.rules_num;
		__entry->prev_min = prev->min;
		__entry->prev_max = prev->max;
		__entry->prev_खोलोmin = prev->खोलोmin;
		__entry->prev_खोलोmax = prev->खोलोmax;
		__entry->prev_पूर्णांकeger = prev->पूर्णांकeger;
		__entry->prev_empty = prev->empty;
		__entry->curr_min = curr->min;
		__entry->curr_max = curr->max;
		__entry->curr_खोलोmin = curr->खोलोmin;
		__entry->curr_खोलोmax = curr->खोलोmax;
		__entry->curr_पूर्णांकeger = curr->पूर्णांकeger;
		__entry->curr_empty = curr->empty;
	),
	TP_prपूर्णांकk("pcmC%dD%d%s:%d %03d/%03d %s %d %d %s%u %u%s %d %d %s%u %u%s",
		  __entry->card,
		  __entry->device,
		  __entry->direction ? "c" : "p",
		  __entry->subdevice,
		  __entry->index,
		  __entry->total,
		  __prपूर्णांक_symbolic(__entry->type, hw_param_labels),
		  __entry->prev_empty,
		  __entry->prev_पूर्णांकeger,
		  __entry->prev_खोलोmin ? "(" : "[",
		  __entry->prev_min,
		  __entry->prev_max,
		  __entry->prev_खोलोmax ? ")" : "]",
		  __entry->curr_empty,
		  __entry->curr_पूर्णांकeger,
		  __entry->curr_खोलोmin ? "(" : "[",
		  __entry->curr_min,
		  __entry->curr_max,
		  __entry->curr_खोलोmax ? ")" : "]"
	)
);

#पूर्ण_अगर /* _PCM_PARAMS_TRACE_H */

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता pcm_param_trace
#समावेश <trace/define_trace.h>
