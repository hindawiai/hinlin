<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM snd_pcm
#घोषणा TRACE_INCLUDE_खाता pcm_trace

#अगर !defined(_PCM_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _PCM_TRACE_H

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(hwptr,
	TP_PROTO(काष्ठा snd_pcm_substream *substream, snd_pcm_uframes_t pos, bool irq),
	TP_ARGS(substream, pos, irq),
	TP_STRUCT__entry(
		__field( bool, in_पूर्णांकerrupt )
		__field( अचिन्हित पूर्णांक, card )
		__field( अचिन्हित पूर्णांक, device )
		__field( अचिन्हित पूर्णांक, number )
		__field( अचिन्हित पूर्णांक, stream )
		__field( snd_pcm_uframes_t, pos )
		__field( snd_pcm_uframes_t, period_size )
		__field( snd_pcm_uframes_t, buffer_size )
		__field( snd_pcm_uframes_t, old_hw_ptr )
		__field( snd_pcm_uframes_t, hw_ptr_base )
	),
	TP_fast_assign(
		__entry->in_पूर्णांकerrupt = (irq);
		__entry->card = (substream)->pcm->card->number;
		__entry->device = (substream)->pcm->device;
		__entry->number = (substream)->number;
		__entry->stream = (substream)->stream;
		__entry->pos = (pos);
		__entry->period_size = (substream)->runसमय->period_size;
		__entry->buffer_size = (substream)->runसमय->buffer_size;
		__entry->old_hw_ptr = (substream)->runसमय->status->hw_ptr;
		__entry->hw_ptr_base = (substream)->runसमय->hw_ptr_base;
	),
	TP_prपूर्णांकk("pcmC%dD%d%s/sub%d: %s: pos=%lu, old=%lu, base=%lu, period=%lu, buf=%lu",
		  __entry->card, __entry->device,
		  __entry->stream == SNDRV_PCM_STREAM_PLAYBACK ? "p" : "c",
		  __entry->number,
		  __entry->in_पूर्णांकerrupt ? "IRQ" : "POS",
		  (अचिन्हित दीर्घ)__entry->pos,
		  (अचिन्हित दीर्घ)__entry->old_hw_ptr,
		  (अचिन्हित दीर्घ)__entry->hw_ptr_base,
		  (अचिन्हित दीर्घ)__entry->period_size,
		  (अचिन्हित दीर्घ)__entry->buffer_size)
);

TRACE_EVENT(xrun,
	TP_PROTO(काष्ठा snd_pcm_substream *substream),
	TP_ARGS(substream),
	TP_STRUCT__entry(
		__field( अचिन्हित पूर्णांक, card )
		__field( अचिन्हित पूर्णांक, device )
		__field( अचिन्हित पूर्णांक, number )
		__field( अचिन्हित पूर्णांक, stream )
		__field( snd_pcm_uframes_t, period_size )
		__field( snd_pcm_uframes_t, buffer_size )
		__field( snd_pcm_uframes_t, old_hw_ptr )
		__field( snd_pcm_uframes_t, hw_ptr_base )
	),
	TP_fast_assign(
		__entry->card = (substream)->pcm->card->number;
		__entry->device = (substream)->pcm->device;
		__entry->number = (substream)->number;
		__entry->stream = (substream)->stream;
		__entry->period_size = (substream)->runसमय->period_size;
		__entry->buffer_size = (substream)->runसमय->buffer_size;
		__entry->old_hw_ptr = (substream)->runसमय->status->hw_ptr;
		__entry->hw_ptr_base = (substream)->runसमय->hw_ptr_base;
	),
	TP_prपूर्णांकk("pcmC%dD%d%s/sub%d: XRUN: old=%lu, base=%lu, period=%lu, buf=%lu",
		  __entry->card, __entry->device,
		  __entry->stream == SNDRV_PCM_STREAM_PLAYBACK ? "p" : "c",
		  __entry->number,
		  (अचिन्हित दीर्घ)__entry->old_hw_ptr,
		  (अचिन्हित दीर्घ)__entry->hw_ptr_base,
		  (अचिन्हित दीर्घ)__entry->period_size,
		  (अचिन्हित दीर्घ)__entry->buffer_size)
);

TRACE_EVENT(hw_ptr_error,
	TP_PROTO(काष्ठा snd_pcm_substream *substream, स्थिर अक्षर *why),
	TP_ARGS(substream, why),
	TP_STRUCT__entry(
		__field( अचिन्हित पूर्णांक, card )
		__field( अचिन्हित पूर्णांक, device )
		__field( अचिन्हित पूर्णांक, number )
		__field( अचिन्हित पूर्णांक, stream )
		__field( स्थिर अक्षर *, reason )
	),
	TP_fast_assign(
		__entry->card = (substream)->pcm->card->number;
		__entry->device = (substream)->pcm->device;
		__entry->number = (substream)->number;
		__entry->stream = (substream)->stream;
		__entry->reason = (why);
	),
	TP_prपूर्णांकk("pcmC%dD%d%s/sub%d: ERROR: %s",
		  __entry->card, __entry->device,
		  __entry->stream == SNDRV_PCM_STREAM_PLAYBACK ? "p" : "c",
		  __entry->number, __entry->reason)
);

TRACE_EVENT(applptr,
	TP_PROTO(काष्ठा snd_pcm_substream *substream, snd_pcm_uframes_t prev, snd_pcm_uframes_t curr),
	TP_ARGS(substream, prev, curr),
	TP_STRUCT__entry(
		__field( अचिन्हित पूर्णांक, card )
		__field( अचिन्हित पूर्णांक, device )
		__field( अचिन्हित पूर्णांक, number )
		__field( अचिन्हित पूर्णांक, stream )
		__field( snd_pcm_uframes_t, prev )
		__field( snd_pcm_uframes_t, curr )
		__field( snd_pcm_uframes_t, avail )
		__field( snd_pcm_uframes_t, period_size )
		__field( snd_pcm_uframes_t, buffer_size )
	),
	TP_fast_assign(
		__entry->card = (substream)->pcm->card->number;
		__entry->device = (substream)->pcm->device;
		__entry->number = (substream)->number;
		__entry->stream = (substream)->stream;
		__entry->prev = (prev);
		__entry->curr = (curr);
		__entry->avail = (substream)->stream ? snd_pcm_capture_avail(substream->runसमय) : snd_pcm_playback_avail(substream->runसमय);
		__entry->period_size = (substream)->runसमय->period_size;
		__entry->buffer_size = (substream)->runसमय->buffer_size;
	),
	TP_prपूर्णांकk("pcmC%dD%d%s/sub%d: prev=%lu, curr=%lu, avail=%lu, period=%lu, buf=%lu",
		__entry->card,
		__entry->device,
		__entry->stream ? "c" : "p",
		__entry->number,
		__entry->prev,
		__entry->curr,
		__entry->avail,
		__entry->period_size,
		__entry->buffer_size
	)
);

#पूर्ण_अगर /* _PCM_TRACE_H */

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#समावेश <trace/define_trace.h>
