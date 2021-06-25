<शैली गुरु>
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM iscsi

#अगर !defined(_TRACE_ISCSI_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_ISCSI_H

#समावेश <linux/tracepoपूर्णांक.h>

/* max debug message length */
#घोषणा ISCSI_MSG_MAX	256

/*
 * Declare tracepoपूर्णांक helper function.
 */
व्योम iscsi_dbg_trace(व्योम (*trace)(काष्ठा device *dev, काष्ठा va_क्रमmat *),
		     काष्ठा device *dev, स्थिर अक्षर *fmt, ...);

/*
 * Declare event class क्रम iscsi debug messages.
 */
DECLARE_EVENT_CLASS(iscsi_log_msg,

	TP_PROTO(काष्ठा device *dev, काष्ठा va_क्रमmat *vaf),

	TP_ARGS(dev, vaf),

	TP_STRUCT__entry(
		__string(dname, 	dev_name(dev)		)
		__dynamic_array(अक्षर,	msg, ISCSI_MSG_MAX	)
	),

	TP_fast_assign(
		__assign_str(dname, dev_name(dev));
		vsnम_लिखो(__get_str(msg), ISCSI_MSG_MAX, vaf->fmt, *vaf->va);
	),

	TP_prपूर्णांकk("%s: %s",__get_str(dname),  __get_str(msg)
	)
);

/*
 * Define event to capture iscsi connection debug messages.
 */
DEFINE_EVENT(iscsi_log_msg, iscsi_dbg_conn,
	TP_PROTO(काष्ठा device *dev, काष्ठा va_क्रमmat *vaf),

	TP_ARGS(dev, vaf)
);

/*
 * Define event to capture iscsi session debug messages.
 */
DEFINE_EVENT(iscsi_log_msg, iscsi_dbg_session,
	TP_PROTO(काष्ठा device *dev, काष्ठा va_क्रमmat *vaf),

	TP_ARGS(dev, vaf)
);

/*
 * Define event to capture iscsi error handling debug messages.
 */
DEFINE_EVENT(iscsi_log_msg, iscsi_dbg_eh,
        TP_PROTO(काष्ठा device *dev, काष्ठा va_क्रमmat *vaf),

        TP_ARGS(dev, vaf)
);

/*
 * Define event to capture iscsi tcp debug messages.
 */
DEFINE_EVENT(iscsi_log_msg, iscsi_dbg_tcp,
        TP_PROTO(काष्ठा device *dev, काष्ठा va_क्रमmat *vaf),

        TP_ARGS(dev, vaf)
);

/*
 * Define event to capture iscsi sw tcp debug messages.
 */
DEFINE_EVENT(iscsi_log_msg, iscsi_dbg_sw_tcp,
	TP_PROTO(काष्ठा device *dev, काष्ठा va_क्रमmat *vaf),

	TP_ARGS(dev, vaf)
);

/*
 * Define event to capture iscsi transport session debug messages.
 */
DEFINE_EVENT(iscsi_log_msg, iscsi_dbg_trans_session,
	TP_PROTO(काष्ठा device *dev, काष्ठा va_क्रमmat *vaf),

	TP_ARGS(dev, vaf)
);

/*
 * Define event to capture iscsi transport connection debug messages.
 */
DEFINE_EVENT(iscsi_log_msg, iscsi_dbg_trans_conn,
	TP_PROTO(काष्ठा device *dev, काष्ठा va_क्रमmat *vaf),

	TP_ARGS(dev, vaf)
);

#पूर्ण_अगर /* _TRACE_ISCSI_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
