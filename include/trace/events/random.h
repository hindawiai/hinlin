<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM अक्रमom

#अगर !defined(_TRACE_RANDOM_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_RANDOM_H

#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(add_device_अक्रमomness,
	TP_PROTO(पूर्णांक bytes, अचिन्हित दीर्घ IP),

	TP_ARGS(bytes, IP),

	TP_STRUCT__entry(
		__field(	  पूर्णांक,	bytes			)
		__field(अचिन्हित दीर्घ,	IP			)
	),

	TP_fast_assign(
		__entry->bytes		= bytes;
		__entry->IP		= IP;
	),

	TP_prपूर्णांकk("bytes %d caller %pS",
		__entry->bytes, (व्योम *)__entry->IP)
);

DECLARE_EVENT_CLASS(अक्रमom__mix_pool_bytes,
	TP_PROTO(स्थिर अक्षर *pool_name, पूर्णांक bytes, अचिन्हित दीर्घ IP),

	TP_ARGS(pool_name, bytes, IP),

	TP_STRUCT__entry(
		__field( स्थिर अक्षर *,	pool_name		)
		__field(	  पूर्णांक,	bytes			)
		__field(अचिन्हित दीर्घ,	IP			)
	),

	TP_fast_assign(
		__entry->pool_name	= pool_name;
		__entry->bytes		= bytes;
		__entry->IP		= IP;
	),

	TP_prपूर्णांकk("%s pool: bytes %d caller %pS",
		  __entry->pool_name, __entry->bytes, (व्योम *)__entry->IP)
);

DEFINE_EVENT(अक्रमom__mix_pool_bytes, mix_pool_bytes,
	TP_PROTO(स्थिर अक्षर *pool_name, पूर्णांक bytes, अचिन्हित दीर्घ IP),

	TP_ARGS(pool_name, bytes, IP)
);

DEFINE_EVENT(अक्रमom__mix_pool_bytes, mix_pool_bytes_nolock,
	TP_PROTO(स्थिर अक्षर *pool_name, पूर्णांक bytes, अचिन्हित दीर्घ IP),

	TP_ARGS(pool_name, bytes, IP)
);

TRACE_EVENT(credit_entropy_bits,
	TP_PROTO(स्थिर अक्षर *pool_name, पूर्णांक bits, पूर्णांक entropy_count,
		 अचिन्हित दीर्घ IP),

	TP_ARGS(pool_name, bits, entropy_count, IP),

	TP_STRUCT__entry(
		__field( स्थिर अक्षर *,	pool_name		)
		__field(	  पूर्णांक,	bits			)
		__field(	  पूर्णांक,	entropy_count		)
		__field(अचिन्हित दीर्घ,	IP			)
	),

	TP_fast_assign(
		__entry->pool_name	= pool_name;
		__entry->bits		= bits;
		__entry->entropy_count	= entropy_count;
		__entry->IP		= IP;
	),

	TP_prपूर्णांकk("%s pool: bits %d entropy_count %d caller %pS",
		  __entry->pool_name, __entry->bits,
		  __entry->entropy_count, (व्योम *)__entry->IP)
);

TRACE_EVENT(debit_entropy,
	TP_PROTO(स्थिर अक्षर *pool_name, पूर्णांक debit_bits),

	TP_ARGS(pool_name, debit_bits),

	TP_STRUCT__entry(
		__field( स्थिर अक्षर *,	pool_name		)
		__field(	  पूर्णांक,	debit_bits		)
	),

	TP_fast_assign(
		__entry->pool_name	= pool_name;
		__entry->debit_bits	= debit_bits;
	),

	TP_prपूर्णांकk("%s: debit_bits %d", __entry->pool_name,
		  __entry->debit_bits)
);

TRACE_EVENT(add_input_अक्रमomness,
	TP_PROTO(पूर्णांक input_bits),

	TP_ARGS(input_bits),

	TP_STRUCT__entry(
		__field(	  पूर्णांक,	input_bits		)
	),

	TP_fast_assign(
		__entry->input_bits	= input_bits;
	),

	TP_prपूर्णांकk("input_pool_bits %d", __entry->input_bits)
);

TRACE_EVENT(add_disk_अक्रमomness,
	TP_PROTO(dev_t dev, पूर्णांक input_bits),

	TP_ARGS(dev, input_bits),

	TP_STRUCT__entry(
		__field(	dev_t,	dev			)
		__field(	  पूर्णांक,	input_bits		)
	),

	TP_fast_assign(
		__entry->dev		= dev;
		__entry->input_bits	= input_bits;
	),

	TP_prपूर्णांकk("dev %d,%d input_pool_bits %d", MAJOR(__entry->dev),
		  MINOR(__entry->dev), __entry->input_bits)
);

DECLARE_EVENT_CLASS(अक्रमom__get_अक्रमom_bytes,
	TP_PROTO(पूर्णांक nbytes, अचिन्हित दीर्घ IP),

	TP_ARGS(nbytes, IP),

	TP_STRUCT__entry(
		__field(	  पूर्णांक,	nbytes			)
		__field(अचिन्हित दीर्घ,	IP			)
	),

	TP_fast_assign(
		__entry->nbytes		= nbytes;
		__entry->IP		= IP;
	),

	TP_prपूर्णांकk("nbytes %d caller %pS", __entry->nbytes, (व्योम *)__entry->IP)
);

DEFINE_EVENT(अक्रमom__get_अक्रमom_bytes, get_अक्रमom_bytes,
	TP_PROTO(पूर्णांक nbytes, अचिन्हित दीर्घ IP),

	TP_ARGS(nbytes, IP)
);

DEFINE_EVENT(अक्रमom__get_अक्रमom_bytes, get_अक्रमom_bytes_arch,
	TP_PROTO(पूर्णांक nbytes, अचिन्हित दीर्घ IP),

	TP_ARGS(nbytes, IP)
);

DECLARE_EVENT_CLASS(अक्रमom__extract_entropy,
	TP_PROTO(स्थिर अक्षर *pool_name, पूर्णांक nbytes, पूर्णांक entropy_count,
		 अचिन्हित दीर्घ IP),

	TP_ARGS(pool_name, nbytes, entropy_count, IP),

	TP_STRUCT__entry(
		__field( स्थिर अक्षर *,	pool_name		)
		__field(	  पूर्णांक,	nbytes			)
		__field(	  पूर्णांक,	entropy_count		)
		__field(अचिन्हित दीर्घ,	IP			)
	),

	TP_fast_assign(
		__entry->pool_name	= pool_name;
		__entry->nbytes		= nbytes;
		__entry->entropy_count	= entropy_count;
		__entry->IP		= IP;
	),

	TP_prपूर्णांकk("%s pool: nbytes %d entropy_count %d caller %pS",
		  __entry->pool_name, __entry->nbytes, __entry->entropy_count,
		  (व्योम *)__entry->IP)
);


DEFINE_EVENT(अक्रमom__extract_entropy, extract_entropy,
	TP_PROTO(स्थिर अक्षर *pool_name, पूर्णांक nbytes, पूर्णांक entropy_count,
		 अचिन्हित दीर्घ IP),

	TP_ARGS(pool_name, nbytes, entropy_count, IP)
);

TRACE_EVENT(uअक्रमom_पढ़ो,
	TP_PROTO(पूर्णांक got_bits, पूर्णांक pool_left, पूर्णांक input_left),

	TP_ARGS(got_bits, pool_left, input_left),

	TP_STRUCT__entry(
		__field(	  पूर्णांक,	got_bits		)
		__field(	  पूर्णांक,	pool_left		)
		__field(	  पूर्णांक,	input_left		)
	),

	TP_fast_assign(
		__entry->got_bits	= got_bits;
		__entry->pool_left	= pool_left;
		__entry->input_left	= input_left;
	),

	TP_prपूर्णांकk("got_bits %d nonblocking_pool_entropy_left %d "
		  "input_entropy_left %d", __entry->got_bits,
		  __entry->pool_left, __entry->input_left)
);

TRACE_EVENT(pअक्रमom_u32,

	TP_PROTO(अचिन्हित पूर्णांक ret),

	TP_ARGS(ret),

	TP_STRUCT__entry(
		__field(   अचिन्हित पूर्णांक, ret)
	),

	TP_fast_assign(
		__entry->ret = ret;
	),

	TP_prपूर्णांकk("ret=%u" , __entry->ret)
);

#पूर्ण_अगर /* _TRACE_RANDOM_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
