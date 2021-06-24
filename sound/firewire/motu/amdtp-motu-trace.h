<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * amdtp-motu-trace.h - tracepoपूर्णांक definitions to dump a part of packet data
 *
 * Copyright (c) 2017 Takashi Sakamoto
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM		snd_firewire_motu

#अगर !defined(_SND_FIREWIRE_MOTU_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _SND_FIREWIRE_MOTU_TRACE_H

#समावेश <linux/tracepoपूर्णांक.h>

अटल व्योम copy_sph(u32 *frame, __be32 *buffer, अचिन्हित पूर्णांक data_blocks,
		     अचिन्हित पूर्णांक data_block_quadlets);
अटल व्योम copy_message(u64 *frames, __be32 *buffer, अचिन्हित पूर्णांक data_blocks,
			 अचिन्हित पूर्णांक data_block_quadlets);

TRACE_EVENT(data_block_sph,
	TP_PROTO(काष्ठा amdtp_stream *s, अचिन्हित पूर्णांक data_blocks, __be32 *buffer),
	TP_ARGS(s, data_blocks, buffer),
	TP_STRUCT__entry(
		__field(पूर्णांक, src)
		__field(पूर्णांक, dst)
		__field(अचिन्हित पूर्णांक, data_blocks)
		__dynamic_array(u32, tstamps, data_blocks)
	),
	TP_fast_assign(
		अगर (s->direction == AMDTP_IN_STREAM) अणु
			__entry->src = fw_parent_device(s->unit)->node_id;
			__entry->dst = fw_parent_device(s->unit)->card->node_id;
		पूर्ण अन्यथा अणु
			__entry->src = fw_parent_device(s->unit)->card->node_id;
			__entry->dst = fw_parent_device(s->unit)->node_id;
		पूर्ण
		__entry->data_blocks = data_blocks;
		copy_sph(__get_dynamic_array(tstamps), buffer, data_blocks, s->data_block_quadlets);
	),
	TP_prपूर्णांकk(
		"%04x %04x %u %s",
		__entry->src,
		__entry->dst,
		__entry->data_blocks,
		__prपूर्णांक_array(__get_dynamic_array(tstamps), __entry->data_blocks, 4)
	)
);

TRACE_EVENT(data_block_message,
	TP_PROTO(काष्ठा amdtp_stream *s, अचिन्हित पूर्णांक data_blocks, __be32 *buffer),
	TP_ARGS(s, data_blocks, buffer),
	TP_STRUCT__entry(
		__field(पूर्णांक, src)
		__field(पूर्णांक, dst)
		__field(अचिन्हित पूर्णांक, data_blocks)
		__dynamic_array(u64, messages, data_blocks)
	),
	TP_fast_assign(
		अगर (s->direction == AMDTP_IN_STREAM) अणु
			__entry->src = fw_parent_device(s->unit)->node_id;
			__entry->dst = fw_parent_device(s->unit)->card->node_id;
		पूर्ण अन्यथा अणु
			__entry->src = fw_parent_device(s->unit)->card->node_id;
			__entry->dst = fw_parent_device(s->unit)->node_id;
		पूर्ण
		__entry->data_blocks = data_blocks;
		copy_message(__get_dynamic_array(messages), buffer, data_blocks, s->data_block_quadlets);
	),
	TP_prपूर्णांकk(
		"%04x %04x %u %s",
		__entry->src,
		__entry->dst,
		__entry->data_blocks,
		__prपूर्णांक_array(__get_dynamic_array(messages), __entry->data_blocks, 8)
	)
);

#पूर्ण_अगर

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH	.
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता	amdtp-motu-trace
#समावेश <trace/define_trace.h>
