<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* FS-Cache tracepoपूर्णांकs
 *
 * Copyright (C) 2016 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM fscache

#अगर !defined(_TRACE_FSCACHE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_FSCACHE_H

#समावेश <linux/fscache.h>
#समावेश <linux/tracepoपूर्णांक.h>

/*
 * Define क्रमागतs क्रम tracing inक्रमmation.
 */
#अगर_अघोषित __FSCACHE_DECLARE_TRACE_ENUMS_ONCE_ONLY
#घोषणा __FSCACHE_DECLARE_TRACE_ENUMS_ONCE_ONLY

क्रमागत fscache_cookie_trace अणु
	fscache_cookie_collision,
	fscache_cookie_discard,
	fscache_cookie_get_acquire_parent,
	fscache_cookie_get_attach_object,
	fscache_cookie_get_reacquire,
	fscache_cookie_get_रेजिस्टर_netfs,
	fscache_cookie_put_acquire_nobufs,
	fscache_cookie_put_dup_netfs,
	fscache_cookie_put_relinquish,
	fscache_cookie_put_object,
	fscache_cookie_put_parent,
पूर्ण;

क्रमागत fscache_page_trace अणु
	fscache_page_cached,
	fscache_page_inval,
	fscache_page_maybe_release,
	fscache_page_radix_clear_store,
	fscache_page_radix_delete,
	fscache_page_radix_insert,
	fscache_page_radix_pend2store,
	fscache_page_radix_set_pend,
	fscache_page_uncache,
	fscache_page_ग_लिखो,
	fscache_page_ग_लिखो_end,
	fscache_page_ग_लिखो_end_pend,
	fscache_page_ग_लिखो_end_noc,
	fscache_page_ग_लिखो_रुको,
	fscache_page_trace__nr
पूर्ण;

क्रमागत fscache_op_trace अणु
	fscache_op_cancel,
	fscache_op_cancel_all,
	fscache_op_cancelled,
	fscache_op_completed,
	fscache_op_enqueue_async,
	fscache_op_enqueue_mythपढ़ो,
	fscache_op_gc,
	fscache_op_init,
	fscache_op_put,
	fscache_op_run,
	fscache_op_संकेत,
	fscache_op_submit,
	fscache_op_submit_ex,
	fscache_op_work,
	fscache_op_trace__nr
पूर्ण;

क्रमागत fscache_page_op_trace अणु
	fscache_page_op_alloc_one,
	fscache_page_op_attr_changed,
	fscache_page_op_check_consistency,
	fscache_page_op_invalidate,
	fscache_page_op_retr_multi,
	fscache_page_op_retr_one,
	fscache_page_op_ग_लिखो_one,
	fscache_page_op_trace__nr
पूर्ण;

#पूर्ण_अगर

/*
 * Declare tracing inक्रमmation क्रमागतs and their string mappings क्रम display.
 */
#घोषणा fscache_cookie_traces						\
	EM(fscache_cookie_collision,		"*COLLISION*")		\
	EM(fscache_cookie_discard,		"DISCARD")		\
	EM(fscache_cookie_get_acquire_parent,	"GET prn")		\
	EM(fscache_cookie_get_attach_object,	"GET obj")		\
	EM(fscache_cookie_get_reacquire,	"GET raq")		\
	EM(fscache_cookie_get_रेजिस्टर_netfs,	"GET net")		\
	EM(fscache_cookie_put_acquire_nobufs,	"PUT nbf")		\
	EM(fscache_cookie_put_dup_netfs,	"PUT dnt")		\
	EM(fscache_cookie_put_relinquish,	"PUT rlq")		\
	EM(fscache_cookie_put_object,		"PUT obj")		\
	E_(fscache_cookie_put_parent,		"PUT prn")

#घोषणा fscache_page_traces						\
	EM(fscache_page_cached,			"Cached ")		\
	EM(fscache_page_inval,			"InvalPg")		\
	EM(fscache_page_maybe_release,		"MayRels")		\
	EM(fscache_page_uncache,		"Uncache")		\
	EM(fscache_page_radix_clear_store,	"RxCStr ")		\
	EM(fscache_page_radix_delete,		"RxDel  ")		\
	EM(fscache_page_radix_insert,		"RxIns  ")		\
	EM(fscache_page_radix_pend2store,	"RxP2S  ")		\
	EM(fscache_page_radix_set_pend,		"RxSPend ")		\
	EM(fscache_page_ग_लिखो,			"WritePg")		\
	EM(fscache_page_ग_लिखो_end,		"EndPgWr")		\
	EM(fscache_page_ग_लिखो_end_pend,		"EndPgWP")		\
	EM(fscache_page_ग_लिखो_end_noc,		"EndPgNC")		\
	E_(fscache_page_ग_लिखो_रुको,		"WtOnWrt")

#घोषणा fscache_op_traces						\
	EM(fscache_op_cancel,			"Cancel1")		\
	EM(fscache_op_cancel_all,		"CancelA")		\
	EM(fscache_op_cancelled,		"Canclld")		\
	EM(fscache_op_completed,		"Complet")		\
	EM(fscache_op_enqueue_async,		"EnqAsyn")		\
	EM(fscache_op_enqueue_mythपढ़ो,		"EnqMyTh")		\
	EM(fscache_op_gc,			"GC     ")		\
	EM(fscache_op_init,			"Init   ")		\
	EM(fscache_op_put,			"Put    ")		\
	EM(fscache_op_run,			"Run    ")		\
	EM(fscache_op_संकेत,			"Signal ")		\
	EM(fscache_op_submit,			"Submit ")		\
	EM(fscache_op_submit_ex,		"SubmitX")		\
	E_(fscache_op_work,			"Work   ")

#घोषणा fscache_page_op_traces						\
	EM(fscache_page_op_alloc_one,		"Alloc1 ")		\
	EM(fscache_page_op_attr_changed,	"AttrChg")		\
	EM(fscache_page_op_check_consistency,	"CheckCn")		\
	EM(fscache_page_op_invalidate,		"Inval  ")		\
	EM(fscache_page_op_retr_multi,		"RetrMul")		\
	EM(fscache_page_op_retr_one,		"Retr1  ")		\
	E_(fscache_page_op_ग_लिखो_one,		"Write1 ")

/*
 * Export क्रमागत symbols via userspace.
 */
#अघोषित EM
#अघोषित E_
#घोषणा EM(a, b) TRACE_DEFINE_ENUM(a);
#घोषणा E_(a, b) TRACE_DEFINE_ENUM(a);

fscache_cookie_traces;

/*
 * Now redefine the EM() and E_() macros to map the क्रमागतs to the strings that
 * will be prपूर्णांकed in the output.
 */
#अघोषित EM
#अघोषित E_
#घोषणा EM(a, b)	अणु a, b पूर्ण,
#घोषणा E_(a, b)	अणु a, b पूर्ण


TRACE_EVENT(fscache_cookie,
	    TP_PROTO(काष्ठा fscache_cookie *cookie,
		     क्रमागत fscache_cookie_trace where,
		     पूर्णांक usage),

	    TP_ARGS(cookie, where, usage),

	    TP_STRUCT__entry(
		    __field(काष्ठा fscache_cookie *,	cookie		)
		    __field(काष्ठा fscache_cookie *,	parent		)
		    __field(क्रमागत fscache_cookie_trace,	where		)
		    __field(पूर्णांक,			usage		)
		    __field(पूर्णांक,			n_children	)
		    __field(पूर्णांक,			n_active	)
		    __field(u8,				flags		)
			     ),

	    TP_fast_assign(
		    __entry->cookie	= cookie;
		    __entry->parent	= cookie->parent;
		    __entry->where	= where;
		    __entry->usage	= usage;
		    __entry->n_children	= atomic_पढ़ो(&cookie->n_children);
		    __entry->n_active	= atomic_पढ़ो(&cookie->n_active);
		    __entry->flags	= cookie->flags;
			   ),

	    TP_prपूर्णांकk("%s c=%p u=%d p=%p Nc=%d Na=%d f=%02x",
		      __prपूर्णांक_symbolic(__entry->where, fscache_cookie_traces),
		      __entry->cookie, __entry->usage,
		      __entry->parent, __entry->n_children, __entry->n_active,
		      __entry->flags)
	    );

TRACE_EVENT(fscache_netfs,
	    TP_PROTO(काष्ठा fscache_netfs *netfs),

	    TP_ARGS(netfs),

	    TP_STRUCT__entry(
		    __field(काष्ठा fscache_cookie *,	cookie		)
		    __array(अक्षर,			name, 8		)
			     ),

	    TP_fast_assign(
		    __entry->cookie		= netfs->primary_index;
		    म_नकलन(__entry->name, netfs->name, 8);
		    __entry->name[7]		= 0;
			   ),

	    TP_prपूर्णांकk("c=%p n=%s",
		      __entry->cookie, __entry->name)
	    );

TRACE_EVENT(fscache_acquire,
	    TP_PROTO(काष्ठा fscache_cookie *cookie),

	    TP_ARGS(cookie),

	    TP_STRUCT__entry(
		    __field(काष्ठा fscache_cookie *,	cookie		)
		    __field(काष्ठा fscache_cookie *,	parent		)
		    __array(अक्षर,			name, 8		)
		    __field(पूर्णांक,			p_usage		)
		    __field(पूर्णांक,			p_n_children	)
		    __field(u8,				p_flags		)
			     ),

	    TP_fast_assign(
		    __entry->cookie		= cookie;
		    __entry->parent		= cookie->parent;
		    __entry->p_usage		= atomic_पढ़ो(&cookie->parent->usage);
		    __entry->p_n_children	= atomic_पढ़ो(&cookie->parent->n_children);
		    __entry->p_flags		= cookie->parent->flags;
		    स_नकल(__entry->name, cookie->def->name, 8);
		    __entry->name[7]		= 0;
			   ),

	    TP_prपूर्णांकk("c=%p p=%p pu=%d pc=%d pf=%02x n=%s",
		      __entry->cookie, __entry->parent, __entry->p_usage,
		      __entry->p_n_children, __entry->p_flags, __entry->name)
	    );

TRACE_EVENT(fscache_relinquish,
	    TP_PROTO(काष्ठा fscache_cookie *cookie, bool retire),

	    TP_ARGS(cookie, retire),

	    TP_STRUCT__entry(
		    __field(काष्ठा fscache_cookie *,	cookie		)
		    __field(काष्ठा fscache_cookie *,	parent		)
		    __field(पूर्णांक,			usage		)
		    __field(पूर्णांक,			n_children	)
		    __field(पूर्णांक,			n_active	)
		    __field(u8,				flags		)
		    __field(bool,			retire		)
			     ),

	    TP_fast_assign(
		    __entry->cookie	= cookie;
		    __entry->parent	= cookie->parent;
		    __entry->usage	= atomic_पढ़ो(&cookie->usage);
		    __entry->n_children	= atomic_पढ़ो(&cookie->n_children);
		    __entry->n_active	= atomic_पढ़ो(&cookie->n_active);
		    __entry->flags	= cookie->flags;
		    __entry->retire	= retire;
			   ),

	    TP_prपूर्णांकk("c=%p u=%d p=%p Nc=%d Na=%d f=%02x r=%u",
		      __entry->cookie, __entry->usage,
		      __entry->parent, __entry->n_children, __entry->n_active,
		      __entry->flags, __entry->retire)
	    );

TRACE_EVENT(fscache_enable,
	    TP_PROTO(काष्ठा fscache_cookie *cookie),

	    TP_ARGS(cookie),

	    TP_STRUCT__entry(
		    __field(काष्ठा fscache_cookie *,	cookie		)
		    __field(पूर्णांक,			usage		)
		    __field(पूर्णांक,			n_children	)
		    __field(पूर्णांक,			n_active	)
		    __field(u8,				flags		)
			     ),

	    TP_fast_assign(
		    __entry->cookie	= cookie;
		    __entry->usage	= atomic_पढ़ो(&cookie->usage);
		    __entry->n_children	= atomic_पढ़ो(&cookie->n_children);
		    __entry->n_active	= atomic_पढ़ो(&cookie->n_active);
		    __entry->flags	= cookie->flags;
			   ),

	    TP_prपूर्णांकk("c=%p u=%d Nc=%d Na=%d f=%02x",
		      __entry->cookie, __entry->usage,
		      __entry->n_children, __entry->n_active, __entry->flags)
	    );

TRACE_EVENT(fscache_disable,
	    TP_PROTO(काष्ठा fscache_cookie *cookie),

	    TP_ARGS(cookie),

	    TP_STRUCT__entry(
		    __field(काष्ठा fscache_cookie *,	cookie		)
		    __field(पूर्णांक,			usage		)
		    __field(पूर्णांक,			n_children	)
		    __field(पूर्णांक,			n_active	)
		    __field(u8,				flags		)
			     ),

	    TP_fast_assign(
		    __entry->cookie	= cookie;
		    __entry->usage	= atomic_पढ़ो(&cookie->usage);
		    __entry->n_children	= atomic_पढ़ो(&cookie->n_children);
		    __entry->n_active	= atomic_पढ़ो(&cookie->n_active);
		    __entry->flags	= cookie->flags;
			   ),

	    TP_prपूर्णांकk("c=%p u=%d Nc=%d Na=%d f=%02x",
		      __entry->cookie, __entry->usage,
		      __entry->n_children, __entry->n_active, __entry->flags)
	    );

TRACE_EVENT(fscache_osm,
	    TP_PROTO(काष्ठा fscache_object *object,
		     स्थिर काष्ठा fscache_state *state,
		     bool रुको, bool oob, s8 event_num),

	    TP_ARGS(object, state, रुको, oob, event_num),

	    TP_STRUCT__entry(
		    __field(काष्ठा fscache_cookie *,	cookie		)
		    __field(काष्ठा fscache_object *,	object		)
		    __array(अक्षर,			state, 8	)
		    __field(bool,			रुको		)
		    __field(bool,			oob		)
		    __field(s8,				event_num	)
			     ),

	    TP_fast_assign(
		    __entry->cookie		= object->cookie;
		    __entry->object		= object;
		    __entry->रुको		= रुको;
		    __entry->oob		= oob;
		    __entry->event_num		= event_num;
		    स_नकल(__entry->state, state->लघु_name, 8);
			   ),

	    TP_prपूर्णांकk("c=%p o=%p %s %s%sev=%d",
		      __entry->cookie,
		      __entry->object,
		      __entry->state,
		      __prपूर्णांक_symbolic(__entry->रुको,
				       अणु true,  "WAIT" पूर्ण,
				       अणु false, "WORK" पूर्ण),
		      __prपूर्णांक_symbolic(__entry->oob,
				       अणु true,  " OOB " पूर्ण,
				       अणु false, " " पूर्ण),
		      __entry->event_num)
	    );

TRACE_EVENT(fscache_page,
	    TP_PROTO(काष्ठा fscache_cookie *cookie, काष्ठा page *page,
		     क्रमागत fscache_page_trace why),

	    TP_ARGS(cookie, page, why),

	    TP_STRUCT__entry(
		    __field(काष्ठा fscache_cookie *,	cookie		)
		    __field(pgoff_t,			page		)
		    __field(क्रमागत fscache_page_trace,	why		)
			     ),

	    TP_fast_assign(
		    __entry->cookie		= cookie;
		    __entry->page		= page->index;
		    __entry->why		= why;
			   ),

	    TP_prपूर्णांकk("c=%p %s pg=%lx",
		      __entry->cookie,
		      __prपूर्णांक_symbolic(__entry->why, fscache_page_traces),
		      __entry->page)
	    );

TRACE_EVENT(fscache_check_page,
	    TP_PROTO(काष्ठा fscache_cookie *cookie, काष्ठा page *page,
		     व्योम *val, पूर्णांक n),

	    TP_ARGS(cookie, page, val, n),

	    TP_STRUCT__entry(
		    __field(काष्ठा fscache_cookie *,	cookie		)
		    __field(व्योम *,			page		)
		    __field(व्योम *,			val		)
		    __field(पूर्णांक,			n		)
			     ),

	    TP_fast_assign(
		    __entry->cookie		= cookie;
		    __entry->page		= page;
		    __entry->val		= val;
		    __entry->n			= n;
			   ),

	    TP_prपूर्णांकk("c=%p pg=%p val=%p n=%d",
		      __entry->cookie, __entry->page, __entry->val, __entry->n)
	    );

TRACE_EVENT(fscache_wake_cookie,
	    TP_PROTO(काष्ठा fscache_cookie *cookie),

	    TP_ARGS(cookie),

	    TP_STRUCT__entry(
		    __field(काष्ठा fscache_cookie *,	cookie		)
			     ),

	    TP_fast_assign(
		    __entry->cookie		= cookie;
			   ),

	    TP_prपूर्णांकk("c=%p", __entry->cookie)
	    );

TRACE_EVENT(fscache_op,
	    TP_PROTO(काष्ठा fscache_cookie *cookie, काष्ठा fscache_operation *op,
		     क्रमागत fscache_op_trace why),

	    TP_ARGS(cookie, op, why),

	    TP_STRUCT__entry(
		    __field(काष्ठा fscache_cookie *,	cookie		)
		    __field(काष्ठा fscache_operation *,	op		)
		    __field(क्रमागत fscache_op_trace,	why		)
			     ),

	    TP_fast_assign(
		    __entry->cookie		= cookie;
		    __entry->op			= op;
		    __entry->why		= why;
			   ),

	    TP_prपूर्णांकk("c=%p op=%p %s",
		      __entry->cookie, __entry->op,
		      __prपूर्णांक_symbolic(__entry->why, fscache_op_traces))
	    );

TRACE_EVENT(fscache_page_op,
	    TP_PROTO(काष्ठा fscache_cookie *cookie, काष्ठा page *page,
		     काष्ठा fscache_operation *op, क्रमागत fscache_page_op_trace what),

	    TP_ARGS(cookie, page, op, what),

	    TP_STRUCT__entry(
		    __field(काष्ठा fscache_cookie *,	cookie		)
		    __field(pgoff_t,			page		)
		    __field(काष्ठा fscache_operation *,	op		)
		    __field(क्रमागत fscache_page_op_trace,	what		)
			     ),

	    TP_fast_assign(
		    __entry->cookie		= cookie;
		    __entry->page		= page ? page->index : 0;
		    __entry->op			= op;
		    __entry->what		= what;
			   ),

	    TP_prपूर्णांकk("c=%p %s pg=%lx op=%p",
		      __entry->cookie,
		      __prपूर्णांक_symbolic(__entry->what, fscache_page_op_traces),
		      __entry->page, __entry->op)
	    );

TRACE_EVENT(fscache_wrote_page,
	    TP_PROTO(काष्ठा fscache_cookie *cookie, काष्ठा page *page,
		     काष्ठा fscache_operation *op, पूर्णांक ret),

	    TP_ARGS(cookie, page, op, ret),

	    TP_STRUCT__entry(
		    __field(काष्ठा fscache_cookie *,	cookie		)
		    __field(pgoff_t,			page		)
		    __field(काष्ठा fscache_operation *,	op		)
		    __field(पूर्णांक,			ret		)
			     ),

	    TP_fast_assign(
		    __entry->cookie		= cookie;
		    __entry->page		= page->index;
		    __entry->op			= op;
		    __entry->ret		= ret;
			   ),

	    TP_prपूर्णांकk("c=%p pg=%lx op=%p ret=%d",
		      __entry->cookie, __entry->page, __entry->op, __entry->ret)
	    );

TRACE_EVENT(fscache_gang_lookup,
	    TP_PROTO(काष्ठा fscache_cookie *cookie, काष्ठा fscache_operation *op,
		     व्योम **results, पूर्णांक n, pgoff_t store_limit),

	    TP_ARGS(cookie, op, results, n, store_limit),

	    TP_STRUCT__entry(
		    __field(काष्ठा fscache_cookie *,	cookie		)
		    __field(काष्ठा fscache_operation *,	op		)
		    __field(pgoff_t,			results0	)
		    __field(पूर्णांक,			n		)
		    __field(pgoff_t,			store_limit	)
			     ),

	    TP_fast_assign(
		    __entry->cookie		= cookie;
		    __entry->op			= op;
		    __entry->results0		= results[0] ? ((काष्ठा page *)results[0])->index : (pgoff_t)-1;
		    __entry->n			= n;
		    __entry->store_limit	= store_limit;
			   ),

	    TP_prपूर्णांकk("c=%p op=%p r0=%lx n=%d sl=%lx",
		      __entry->cookie, __entry->op, __entry->results0, __entry->n,
		      __entry->store_limit)
	    );

#पूर्ण_अगर /* _TRACE_FSCACHE_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
