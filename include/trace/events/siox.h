<शैली गुरु>
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM siox

#अगर !defined(_TRACE_SIOX_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_SIOX_H

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(siox_set_data,
	    TP_PROTO(स्थिर काष्ठा siox_master *smaster,
		     स्थिर काष्ठा siox_device *sdevice,
		     अचिन्हित पूर्णांक devno, माप_प्रकार bufoffset),
	    TP_ARGS(smaster, sdevice, devno, bufoffset),
	    TP_STRUCT__entry(
			     __field(पूर्णांक, busno)
			     __field(अचिन्हित पूर्णांक, devno)
			     __field(माप_प्रकार, inbytes)
			     __dynamic_array(u8, buf, sdevice->inbytes)
			    ),
	    TP_fast_assign(
			   __entry->busno = smaster->busno;
			   __entry->devno = devno;
			   __entry->inbytes = sdevice->inbytes;
			   स_नकल(__get_dynamic_array(buf),
				  smaster->buf + bufoffset, sdevice->inbytes);
			  ),
	    TP_prपूर्णांकk("siox-%d-%u [%*phD]",
		      __entry->busno,
		      __entry->devno,
		      (पूर्णांक)__entry->inbytes, __get_dynamic_array(buf)
		     )
);

TRACE_EVENT(siox_get_data,
	    TP_PROTO(स्थिर काष्ठा siox_master *smaster,
		     स्थिर काष्ठा siox_device *sdevice,
		     अचिन्हित पूर्णांक devno, u8 status_clean,
		     माप_प्रकार bufoffset),
	    TP_ARGS(smaster, sdevice, devno, status_clean, bufoffset),
	    TP_STRUCT__entry(
			     __field(पूर्णांक, busno)
			     __field(अचिन्हित पूर्णांक, devno)
			     __field(u8, status_clean)
			     __field(माप_प्रकार, outbytes)
			     __dynamic_array(u8, buf, sdevice->outbytes)
			    ),
	    TP_fast_assign(
			   __entry->busno = smaster->busno;
			   __entry->devno = devno;
			   __entry->status_clean = status_clean;
			   __entry->outbytes = sdevice->outbytes;
			   स_नकल(__get_dynamic_array(buf),
				  smaster->buf + bufoffset, sdevice->outbytes);
			  ),
	    TP_prपूर्णांकk("siox-%d-%u (%02hhx) [%*phD]",
		      __entry->busno,
		      __entry->devno,
		      __entry->status_clean,
		      (पूर्णांक)__entry->outbytes, __get_dynamic_array(buf)
		     )
);

#पूर्ण_अगर /* अगर !defined(_TRACE_SIOX_H) || defined(TRACE_HEADER_MULTI_READ) */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
