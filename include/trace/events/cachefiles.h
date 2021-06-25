<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* CacheFiles tracepoपूर्णांकs
 *
 * Copyright (C) 2016 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM cachefiles

#अगर !defined(_TRACE_CACHEखाताS_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_CACHEखाताS_H

#समावेश <linux/tracepoपूर्णांक.h>

/*
 * Define क्रमागतs क्रम tracing inक्रमmation.
 */
#अगर_अघोषित __CACHEखाताS_DECLARE_TRACE_ENUMS_ONCE_ONLY
#घोषणा __CACHEखाताS_DECLARE_TRACE_ENUMS_ONCE_ONLY

क्रमागत cachefiles_obj_ref_trace अणु
	cachefiles_obj_put_रुको_retry = fscache_obj_ref__nr_traces,
	cachefiles_obj_put_रुको_समयo,
	cachefiles_obj_ref__nr_traces
पूर्ण;

#पूर्ण_अगर

/*
 * Define क्रमागत -> string mappings क्रम display.
 */
#घोषणा cachefiles_obj_समाप्त_traces				\
	EM(FSCACHE_OBJECT_IS_STALE,	"stale")		\
	EM(FSCACHE_OBJECT_NO_SPACE,	"no_space")		\
	EM(FSCACHE_OBJECT_WAS_RETIRED,	"was_retired")		\
	E_(FSCACHE_OBJECT_WAS_CULLED,	"was_culled")

#घोषणा cachefiles_obj_ref_traces					\
	EM(fscache_obj_get_add_to_deps,		"GET add_to_deps")	\
	EM(fscache_obj_get_queue,		"GET queue")		\
	EM(fscache_obj_put_alloc_fail,		"PUT alloc_fail")	\
	EM(fscache_obj_put_attach_fail,		"PUT attach_fail")	\
	EM(fscache_obj_put_drop_obj,		"PUT drop_obj")		\
	EM(fscache_obj_put_enq_dep,		"PUT enq_dep")		\
	EM(fscache_obj_put_queue,		"PUT queue")		\
	EM(fscache_obj_put_work,		"PUT work")		\
	EM(cachefiles_obj_put_रुको_retry,	"PUT wait_retry")	\
	E_(cachefiles_obj_put_रुको_समयo,	"PUT wait_timeo")

/*
 * Export क्रमागत symbols via userspace.
 */
#अघोषित EM
#अघोषित E_
#घोषणा EM(a, b) TRACE_DEFINE_ENUM(a);
#घोषणा E_(a, b) TRACE_DEFINE_ENUM(a);

cachefiles_obj_समाप्त_traces;
cachefiles_obj_ref_traces;

/*
 * Now redefine the EM() and E_() macros to map the क्रमागतs to the strings that
 * will be prपूर्णांकed in the output.
 */
#अघोषित EM
#अघोषित E_
#घोषणा EM(a, b)	अणु a, b पूर्ण,
#घोषणा E_(a, b)	अणु a, b पूर्ण


TRACE_EVENT(cachefiles_ref,
	    TP_PROTO(काष्ठा cachefiles_object *obj,
		     काष्ठा fscache_cookie *cookie,
		     क्रमागत cachefiles_obj_ref_trace why,
		     पूर्णांक usage),

	    TP_ARGS(obj, cookie, why, usage),

	    /* Note that obj may be शून्य */
	    TP_STRUCT__entry(
		    __field(काष्ठा cachefiles_object *,		obj		)
		    __field(काष्ठा fscache_cookie *,		cookie		)
		    __field(क्रमागत cachefiles_obj_ref_trace,	why		)
		    __field(पूर्णांक,				usage		)
			     ),

	    TP_fast_assign(
		    __entry->obj	= obj;
		    __entry->cookie	= cookie;
		    __entry->usage	= usage;
		    __entry->why	= why;
			   ),

	    TP_prपूर्णांकk("c=%p o=%p u=%d %s",
		      __entry->cookie, __entry->obj, __entry->usage,
		      __prपूर्णांक_symbolic(__entry->why, cachefiles_obj_ref_traces))
	    );

TRACE_EVENT(cachefiles_lookup,
	    TP_PROTO(काष्ठा cachefiles_object *obj,
		     काष्ठा dentry *de,
		     काष्ठा inode *inode),

	    TP_ARGS(obj, de, inode),

	    TP_STRUCT__entry(
		    __field(काष्ठा cachefiles_object *,	obj	)
		    __field(काष्ठा dentry *,		de	)
		    __field(काष्ठा inode *,		inode	)
			     ),

	    TP_fast_assign(
		    __entry->obj	= obj;
		    __entry->de		= de;
		    __entry->inode	= inode;
			   ),

	    TP_prपूर्णांकk("o=%p d=%p i=%p",
		      __entry->obj, __entry->de, __entry->inode)
	    );

TRACE_EVENT(cachefiles_सूची_गढ़ो,
	    TP_PROTO(काष्ठा cachefiles_object *obj,
		     काष्ठा dentry *de, पूर्णांक ret),

	    TP_ARGS(obj, de, ret),

	    TP_STRUCT__entry(
		    __field(काष्ठा cachefiles_object *,	obj	)
		    __field(काष्ठा dentry *,		de	)
		    __field(पूर्णांक,			ret	)
			     ),

	    TP_fast_assign(
		    __entry->obj	= obj;
		    __entry->de		= de;
		    __entry->ret	= ret;
			   ),

	    TP_prपूर्णांकk("o=%p d=%p r=%u",
		      __entry->obj, __entry->de, __entry->ret)
	    );

TRACE_EVENT(cachefiles_create,
	    TP_PROTO(काष्ठा cachefiles_object *obj,
		     काष्ठा dentry *de, पूर्णांक ret),

	    TP_ARGS(obj, de, ret),

	    TP_STRUCT__entry(
		    __field(काष्ठा cachefiles_object *,	obj	)
		    __field(काष्ठा dentry *,		de	)
		    __field(पूर्णांक,			ret	)
			     ),

	    TP_fast_assign(
		    __entry->obj	= obj;
		    __entry->de		= de;
		    __entry->ret	= ret;
			   ),

	    TP_prपूर्णांकk("o=%p d=%p r=%u",
		      __entry->obj, __entry->de, __entry->ret)
	    );

TRACE_EVENT(cachefiles_unlink,
	    TP_PROTO(काष्ठा cachefiles_object *obj,
		     काष्ठा dentry *de,
		     क्रमागत fscache_why_object_समाप्तed why),

	    TP_ARGS(obj, de, why),

	    /* Note that obj may be शून्य */
	    TP_STRUCT__entry(
		    __field(काष्ठा cachefiles_object *,	obj		)
		    __field(काष्ठा dentry *,		de		)
		    __field(क्रमागत fscache_why_object_समाप्तed, why		)
			     ),

	    TP_fast_assign(
		    __entry->obj	= obj;
		    __entry->de		= de;
		    __entry->why	= why;
			   ),

	    TP_prपूर्णांकk("o=%p d=%p w=%s",
		      __entry->obj, __entry->de,
		      __prपूर्णांक_symbolic(__entry->why, cachefiles_obj_समाप्त_traces))
	    );

TRACE_EVENT(cachefiles_नाम,
	    TP_PROTO(काष्ठा cachefiles_object *obj,
		     काष्ठा dentry *de,
		     काष्ठा dentry *to,
		     क्रमागत fscache_why_object_समाप्तed why),

	    TP_ARGS(obj, de, to, why),

	    /* Note that obj may be शून्य */
	    TP_STRUCT__entry(
		    __field(काष्ठा cachefiles_object *,	obj		)
		    __field(काष्ठा dentry *,		de		)
		    __field(काष्ठा dentry *,		to		)
		    __field(क्रमागत fscache_why_object_समाप्तed, why		)
			     ),

	    TP_fast_assign(
		    __entry->obj	= obj;
		    __entry->de		= de;
		    __entry->to		= to;
		    __entry->why	= why;
			   ),

	    TP_prपूर्णांकk("o=%p d=%p t=%p w=%s",
		      __entry->obj, __entry->de, __entry->to,
		      __prपूर्णांक_symbolic(__entry->why, cachefiles_obj_समाप्त_traces))
	    );

TRACE_EVENT(cachefiles_mark_active,
	    TP_PROTO(काष्ठा cachefiles_object *obj,
		     काष्ठा dentry *de),

	    TP_ARGS(obj, de),

	    /* Note that obj may be शून्य */
	    TP_STRUCT__entry(
		    __field(काष्ठा cachefiles_object *,	obj		)
		    __field(काष्ठा dentry *,		de		)
			     ),

	    TP_fast_assign(
		    __entry->obj	= obj;
		    __entry->de		= de;
			   ),

	    TP_prपूर्णांकk("o=%p d=%p",
		      __entry->obj, __entry->de)
	    );

TRACE_EVENT(cachefiles_रुको_active,
	    TP_PROTO(काष्ठा cachefiles_object *obj,
		     काष्ठा dentry *de,
		     काष्ठा cachefiles_object *xobj),

	    TP_ARGS(obj, de, xobj),

	    /* Note that obj may be शून्य */
	    TP_STRUCT__entry(
		    __field(काष्ठा cachefiles_object *,	obj		)
		    __field(काष्ठा dentry *,		de		)
		    __field(काष्ठा cachefiles_object *,	xobj		)
		    __field(u16,			flags		)
		    __field(u16,			fsc_flags	)
			     ),

	    TP_fast_assign(
		    __entry->obj	= obj;
		    __entry->de		= de;
		    __entry->xobj	= xobj;
		    __entry->flags	= xobj->flags;
		    __entry->fsc_flags	= xobj->fscache.flags;
			   ),

	    TP_prपूर्णांकk("o=%p d=%p wo=%p wf=%x wff=%x",
		      __entry->obj, __entry->de, __entry->xobj,
		      __entry->flags, __entry->fsc_flags)
	    );

TRACE_EVENT(cachefiles_mark_inactive,
	    TP_PROTO(काष्ठा cachefiles_object *obj,
		     काष्ठा dentry *de,
		     काष्ठा inode *inode),

	    TP_ARGS(obj, de, inode),

	    /* Note that obj may be शून्य */
	    TP_STRUCT__entry(
		    __field(काष्ठा cachefiles_object *,	obj		)
		    __field(काष्ठा dentry *,		de		)
		    __field(काष्ठा inode *,		inode		)
			     ),

	    TP_fast_assign(
		    __entry->obj	= obj;
		    __entry->de		= de;
		    __entry->inode	= inode;
			   ),

	    TP_prपूर्णांकk("o=%p d=%p i=%p",
		      __entry->obj, __entry->de, __entry->inode)
	    );

TRACE_EVENT(cachefiles_mark_buried,
	    TP_PROTO(काष्ठा cachefiles_object *obj,
		     काष्ठा dentry *de,
		     क्रमागत fscache_why_object_समाप्तed why),

	    TP_ARGS(obj, de, why),

	    /* Note that obj may be शून्य */
	    TP_STRUCT__entry(
		    __field(काष्ठा cachefiles_object *,	obj		)
		    __field(काष्ठा dentry *,		de		)
		    __field(क्रमागत fscache_why_object_समाप्तed, why		)
			     ),

	    TP_fast_assign(
		    __entry->obj	= obj;
		    __entry->de		= de;
		    __entry->why	= why;
			   ),

	    TP_prपूर्णांकk("o=%p d=%p w=%s",
		      __entry->obj, __entry->de,
		      __prपूर्णांक_symbolic(__entry->why, cachefiles_obj_समाप्त_traces))
	    );

#पूर्ण_अगर /* _TRACE_CACHEखाताS_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
