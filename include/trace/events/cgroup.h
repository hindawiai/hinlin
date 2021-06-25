<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM cgroup

#अगर !defined(_TRACE_CGROUP_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_CGROUP_H

#समावेश <linux/cgroup.h>
#समावेश <linux/tracepoपूर्णांक.h>

DECLARE_EVENT_CLASS(cgroup_root,

	TP_PROTO(काष्ठा cgroup_root *root),

	TP_ARGS(root),

	TP_STRUCT__entry(
		__field(	पूर्णांक,		root			)
		__field(	u16,		ss_mask			)
		__string(	name,		root->name		)
	),

	TP_fast_assign(
		__entry->root = root->hierarchy_id;
		__entry->ss_mask = root->subsys_mask;
		__assign_str(name, root->name);
	),

	TP_prपूर्णांकk("root=%d ss_mask=%#x name=%s",
		  __entry->root, __entry->ss_mask, __get_str(name))
);

DEFINE_EVENT(cgroup_root, cgroup_setup_root,

	TP_PROTO(काष्ठा cgroup_root *root),

	TP_ARGS(root)
);

DEFINE_EVENT(cgroup_root, cgroup_destroy_root,

	TP_PROTO(काष्ठा cgroup_root *root),

	TP_ARGS(root)
);

DEFINE_EVENT(cgroup_root, cgroup_remount,

	TP_PROTO(काष्ठा cgroup_root *root),

	TP_ARGS(root)
);

DECLARE_EVENT_CLASS(cgroup,

	TP_PROTO(काष्ठा cgroup *cgrp, स्थिर अक्षर *path),

	TP_ARGS(cgrp, path),

	TP_STRUCT__entry(
		__field(	पूर्णांक,		root			)
		__field(	पूर्णांक,		id			)
		__field(	पूर्णांक,		level			)
		__string(	path,		path			)
	),

	TP_fast_assign(
		__entry->root = cgrp->root->hierarchy_id;
		__entry->id = cgroup_id(cgrp);
		__entry->level = cgrp->level;
		__assign_str(path, path);
	),

	TP_prपूर्णांकk("root=%d id=%d level=%d path=%s",
		  __entry->root, __entry->id, __entry->level, __get_str(path))
);

DEFINE_EVENT(cgroup, cgroup_सूची_गढ़ो,

	TP_PROTO(काष्ठा cgroup *cgrp, स्थिर अक्षर *path),

	TP_ARGS(cgrp, path)
);

DEFINE_EVENT(cgroup, cgroup_सूची_हटाओ,

	TP_PROTO(काष्ठा cgroup *cgrp, स्थिर अक्षर *path),

	TP_ARGS(cgrp, path)
);

DEFINE_EVENT(cgroup, cgroup_release,

	TP_PROTO(काष्ठा cgroup *cgrp, स्थिर अक्षर *path),

	TP_ARGS(cgrp, path)
);

DEFINE_EVENT(cgroup, cgroup_नाम,

	TP_PROTO(काष्ठा cgroup *cgrp, स्थिर अक्षर *path),

	TP_ARGS(cgrp, path)
);

DEFINE_EVENT(cgroup, cgroup_मुक्तze,

	TP_PROTO(काष्ठा cgroup *cgrp, स्थिर अक्षर *path),

	TP_ARGS(cgrp, path)
);

DEFINE_EVENT(cgroup, cgroup_unमुक्तze,

	TP_PROTO(काष्ठा cgroup *cgrp, स्थिर अक्षर *path),

	TP_ARGS(cgrp, path)
);

DECLARE_EVENT_CLASS(cgroup_migrate,

	TP_PROTO(काष्ठा cgroup *dst_cgrp, स्थिर अक्षर *path,
		 काष्ठा task_काष्ठा *task, bool thपढ़ोgroup),

	TP_ARGS(dst_cgrp, path, task, thपढ़ोgroup),

	TP_STRUCT__entry(
		__field(	पूर्णांक,		dst_root		)
		__field(	पूर्णांक,		dst_id			)
		__field(	पूर्णांक,		dst_level		)
		__field(	पूर्णांक,		pid			)
		__string(	dst_path,	path			)
		__string(	comm,		task->comm		)
	),

	TP_fast_assign(
		__entry->dst_root = dst_cgrp->root->hierarchy_id;
		__entry->dst_id = cgroup_id(dst_cgrp);
		__entry->dst_level = dst_cgrp->level;
		__assign_str(dst_path, path);
		__entry->pid = task->pid;
		__assign_str(comm, task->comm);
	),

	TP_prपूर्णांकk("dst_root=%d dst_id=%d dst_level=%d dst_path=%s pid=%d comm=%s",
		  __entry->dst_root, __entry->dst_id, __entry->dst_level,
		  __get_str(dst_path), __entry->pid, __get_str(comm))
);

DEFINE_EVENT(cgroup_migrate, cgroup_attach_task,

	TP_PROTO(काष्ठा cgroup *dst_cgrp, स्थिर अक्षर *path,
		 काष्ठा task_काष्ठा *task, bool thपढ़ोgroup),

	TP_ARGS(dst_cgrp, path, task, thपढ़ोgroup)
);

DEFINE_EVENT(cgroup_migrate, cgroup_transfer_tasks,

	TP_PROTO(काष्ठा cgroup *dst_cgrp, स्थिर अक्षर *path,
		 काष्ठा task_काष्ठा *task, bool thपढ़ोgroup),

	TP_ARGS(dst_cgrp, path, task, thपढ़ोgroup)
);

DECLARE_EVENT_CLASS(cgroup_event,

	TP_PROTO(काष्ठा cgroup *cgrp, स्थिर अक्षर *path, पूर्णांक val),

	TP_ARGS(cgrp, path, val),

	TP_STRUCT__entry(
		__field(	पूर्णांक,		root			)
		__field(	पूर्णांक,		id			)
		__field(	पूर्णांक,		level			)
		__string(	path,		path			)
		__field(	पूर्णांक,		val			)
	),

	TP_fast_assign(
		__entry->root = cgrp->root->hierarchy_id;
		__entry->id = cgroup_id(cgrp);
		__entry->level = cgrp->level;
		__assign_str(path, path);
		__entry->val = val;
	),

	TP_prपूर्णांकk("root=%d id=%d level=%d path=%s val=%d",
		  __entry->root, __entry->id, __entry->level, __get_str(path),
		  __entry->val)
);

DEFINE_EVENT(cgroup_event, cgroup_notअगरy_populated,

	TP_PROTO(काष्ठा cgroup *cgrp, स्थिर अक्षर *path, पूर्णांक val),

	TP_ARGS(cgrp, path, val)
);

DEFINE_EVENT(cgroup_event, cgroup_notअगरy_frozen,

	TP_PROTO(काष्ठा cgroup *cgrp, स्थिर अक्षर *path, पूर्णांक val),

	TP_ARGS(cgrp, path, val)
);

#पूर्ण_अगर /* _TRACE_CGROUP_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
