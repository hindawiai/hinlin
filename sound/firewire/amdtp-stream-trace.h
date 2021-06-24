<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * amdtp-stream-trace.h - tracepoपूर्णांक definitions to dump a part of packet data
 *
 * Copyright (c) 2016 Takashi Sakamoto
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM		snd_firewire_lib

#अगर !defined(_AMDTP_STREAM_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _AMDTP_STREAM_TRACE_H

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(amdtp_packet,
	TP_PROTO(स्थिर काष्ठा amdtp_stream *s, u32 cycles, स्थिर __be32 *cip_header, अचिन्हित पूर्णांक payload_length, अचिन्हित पूर्णांक data_blocks, अचिन्हित पूर्णांक data_block_counter, अचिन्हित पूर्णांक packet_index, अचिन्हित पूर्णांक index),
	TP_ARGS(s, cycles, cip_header, payload_length, data_blocks, data_block_counter, packet_index, index),
	TP_STRUCT__entry(
		__field(अचिन्हित पूर्णांक, second)
		__field(अचिन्हित पूर्णांक, cycle)
		__field(पूर्णांक, channel)
		__field(पूर्णांक, src)
		__field(पूर्णांक, dest)
		__dynamic_array(u8, cip_header, cip_header ? 8 : 0)
		__field(अचिन्हित पूर्णांक, payload_quadlets)
		__field(अचिन्हित पूर्णांक, data_blocks)
		__field(अचिन्हित पूर्णांक, data_block_counter)
		__field(अचिन्हित पूर्णांक, packet_index)
		__field(अचिन्हित पूर्णांक, irq)
		__field(अचिन्हित पूर्णांक, index)
	),
	TP_fast_assign(
		__entry->second = cycles / CYCLES_PER_SECOND;
		__entry->cycle = cycles % CYCLES_PER_SECOND;
		__entry->channel = s->context->channel;
		अगर (s->direction == AMDTP_IN_STREAM) अणु
			__entry->src = fw_parent_device(s->unit)->node_id;
			__entry->dest = fw_parent_device(s->unit)->card->node_id;
		पूर्ण अन्यथा अणु
			__entry->src = fw_parent_device(s->unit)->card->node_id;
			__entry->dest = fw_parent_device(s->unit)->node_id;
		पूर्ण
		अगर (cip_header) अणु
			स_नकल(__get_dynamic_array(cip_header), cip_header,
			       __get_dynamic_array_len(cip_header));
		पूर्ण
		__entry->payload_quadlets = payload_length / माप(__be32);
		__entry->data_blocks = data_blocks;
		__entry->data_block_counter = data_block_counter,
		__entry->packet_index = packet_index;
		__entry->irq = !!in_पूर्णांकerrupt();
		__entry->index = index;
	),
	TP_prपूर्णांकk(
		"%02u %04u %04x %04x %02d %03u %02u %03u %02u %01u %02u %s",
		__entry->second,
		__entry->cycle,
		__entry->src,
		__entry->dest,
		__entry->channel,
		__entry->payload_quadlets,
		__entry->data_blocks,
		__entry->data_block_counter,
		__entry->packet_index,
		__entry->irq,
		__entry->index,
		__prपूर्णांक_array(__get_dynamic_array(cip_header),
			      __get_dynamic_array_len(cip_header), 1))
);

#पूर्ण_अगर

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH	.
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता	amdtp-stream-trace
#समावेश <trace/define_trace.h>
