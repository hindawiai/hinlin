<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM hda

#अगर !defined(__HDAC_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा __HDAC_TRACE_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/device.h>
#समावेश <sound/hdaudपन.स>

#अगर_अघोषित HDAC_MSG_MAX
#घोषणा HDAC_MSG_MAX	500
#पूर्ण_अगर

काष्ठा hdac_bus;
काष्ठा hdac_codec;

TRACE_EVENT(hda_send_cmd,
	TP_PROTO(काष्ठा hdac_bus *bus, अचिन्हित पूर्णांक cmd),
	TP_ARGS(bus, cmd),
	TP_STRUCT__entry(__dynamic_array(अक्षर, msg, HDAC_MSG_MAX)),
	TP_fast_assign(
		snम_लिखो(__get_str(msg), HDAC_MSG_MAX,
			 "[%s:%d] val=0x%08x",
			 dev_name((bus)->dev), (cmd) >> 28, cmd);
	),
	TP_prपूर्णांकk("%s", __get_str(msg))
);

TRACE_EVENT(hda_get_response,
	TP_PROTO(काष्ठा hdac_bus *bus, अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक res),
	TP_ARGS(bus, addr, res),
	TP_STRUCT__entry(__dynamic_array(अक्षर, msg, HDAC_MSG_MAX)),
	TP_fast_assign(
		snम_लिखो(__get_str(msg), HDAC_MSG_MAX,
			 "[%s:%d] val=0x%08x",
			 dev_name((bus)->dev), addr, res);
	),
	TP_prपूर्णांकk("%s", __get_str(msg))
);

TRACE_EVENT(hda_unsol_event,
	TP_PROTO(काष्ठा hdac_bus *bus, u32 res, u32 res_ex),
	TP_ARGS(bus, res, res_ex),
	TP_STRUCT__entry(__dynamic_array(अक्षर, msg, HDAC_MSG_MAX)),
	TP_fast_assign(
		snम_लिखो(__get_str(msg), HDAC_MSG_MAX,
			 "[%s:%d] res=0x%08x, res_ex=0x%08x",
			 dev_name((bus)->dev), res_ex & 0x0f, res, res_ex);
	),
	TP_prपूर्णांकk("%s", __get_str(msg))
);

DECLARE_EVENT_CLASS(hdac_stream,
	TP_PROTO(काष्ठा hdac_bus *bus, काष्ठा hdac_stream *azx_dev),

	TP_ARGS(bus, azx_dev),

	TP_STRUCT__entry(
		__field(अचिन्हित अक्षर, stream_tag)
	),

	TP_fast_assign(
		__entry->stream_tag = (azx_dev)->stream_tag;
	),

	TP_prपूर्णांकk("stream_tag: %d", __entry->stream_tag)
);

DEFINE_EVENT(hdac_stream, snd_hdac_stream_start,
	TP_PROTO(काष्ठा hdac_bus *bus, काष्ठा hdac_stream *azx_dev),
	TP_ARGS(bus, azx_dev)
);

DEFINE_EVENT(hdac_stream, snd_hdac_stream_stop,
	TP_PROTO(काष्ठा hdac_bus *bus, काष्ठा hdac_stream *azx_dev),
	TP_ARGS(bus, azx_dev)
);

#पूर्ण_अगर /* __HDAC_TRACE_H */

/* This part must be outside protection */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .

#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता trace

#समावेश <trace/define_trace.h>
