<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM mmap_lock

#अगर !defined(_TRACE_MMAP_LOCK_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_MMAP_LOCK_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/types.h>

काष्ठा mm_काष्ठा;

बाह्य पूर्णांक trace_mmap_lock_reg(व्योम);
बाह्य व्योम trace_mmap_lock_unreg(व्योम);

TRACE_EVENT_FN(mmap_lock_start_locking,

	TP_PROTO(काष्ठा mm_काष्ठा *mm, स्थिर अक्षर *memcg_path, bool ग_लिखो),

	TP_ARGS(mm, memcg_path, ग_लिखो),

	TP_STRUCT__entry(
		__field(काष्ठा mm_काष्ठा *, mm)
		__string(memcg_path, memcg_path)
		__field(bool, ग_लिखो)
	),

	TP_fast_assign(
		__entry->mm = mm;
		__assign_str(memcg_path, memcg_path);
		__entry->ग_लिखो = ग_लिखो;
	),

	TP_prपूर्णांकk(
		"mm=%p memcg_path=%s write=%s\n",
		__entry->mm,
		__get_str(memcg_path),
		__entry->ग_लिखो ? "true" : "false"
	),

	trace_mmap_lock_reg, trace_mmap_lock_unreg
);

TRACE_EVENT_FN(mmap_lock_acquire_वापसed,

	TP_PROTO(काष्ठा mm_काष्ठा *mm, स्थिर अक्षर *memcg_path, bool ग_लिखो,
		bool success),

	TP_ARGS(mm, memcg_path, ग_लिखो, success),

	TP_STRUCT__entry(
		__field(काष्ठा mm_काष्ठा *, mm)
		__string(memcg_path, memcg_path)
		__field(bool, ग_लिखो)
		__field(bool, success)
	),

	TP_fast_assign(
		__entry->mm = mm;
		__assign_str(memcg_path, memcg_path);
		__entry->ग_लिखो = ग_लिखो;
		__entry->success = success;
	),

	TP_prपूर्णांकk(
		"mm=%p memcg_path=%s write=%s success=%s\n",
		__entry->mm,
		__get_str(memcg_path),
		__entry->ग_लिखो ? "true" : "false",
		__entry->success ? "true" : "false"
	),

	trace_mmap_lock_reg, trace_mmap_lock_unreg
);

TRACE_EVENT_FN(mmap_lock_released,

	TP_PROTO(काष्ठा mm_काष्ठा *mm, स्थिर अक्षर *memcg_path, bool ग_लिखो),

	TP_ARGS(mm, memcg_path, ग_लिखो),

	TP_STRUCT__entry(
		__field(काष्ठा mm_काष्ठा *, mm)
		__string(memcg_path, memcg_path)
		__field(bool, ग_लिखो)
	),

	TP_fast_assign(
		__entry->mm = mm;
		__assign_str(memcg_path, memcg_path);
		__entry->ग_लिखो = ग_लिखो;
	),

	TP_prपूर्णांकk(
		"mm=%p memcg_path=%s write=%s\n",
		__entry->mm,
		__get_str(memcg_path),
		__entry->ग_लिखो ? "true" : "false"
	),

	trace_mmap_lock_reg, trace_mmap_lock_unreg
);

#पूर्ण_अगर /* _TRACE_MMAP_LOCK_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
