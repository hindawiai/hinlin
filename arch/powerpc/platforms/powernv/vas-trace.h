<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM	vas

#अगर !defined(_VAS_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)

#घोषणा _VAS_TRACE_H
#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/vas.h>

TRACE_EVENT(	vas_rx_win_खोलो,

		TP_PROTO(काष्ठा task_काष्ठा *tsk,
			 पूर्णांक vasid,
			 पूर्णांक cop,
			 काष्ठा vas_rx_win_attr *rxattr),

		TP_ARGS(tsk, vasid, cop, rxattr),

		TP_STRUCT__entry(
			__field(काष्ठा task_काष्ठा *, tsk)
			__field(पूर्णांक, pid)
			__field(पूर्णांक, cop)
			__field(पूर्णांक, vasid)
			__field(काष्ठा vas_rx_win_attr *, rxattr)
			__field(पूर्णांक, lnotअगरy_lpid)
			__field(पूर्णांक, lnotअगरy_pid)
			__field(पूर्णांक, lnotअगरy_tid)
		),

		TP_fast_assign(
			__entry->pid = tsk->pid;
			__entry->vasid = vasid;
			__entry->cop = cop;
			__entry->lnotअगरy_lpid = rxattr->lnotअगरy_lpid;
			__entry->lnotअगरy_pid = rxattr->lnotअगरy_pid;
			__entry->lnotअगरy_tid = rxattr->lnotअगरy_tid;
		),

		TP_prपूर्णांकk("pid=%d, vasid=%d, cop=%d, lpid=%d, pid=%d, tid=%d",
			__entry->pid, __entry->vasid, __entry->cop,
			__entry->lnotअगरy_lpid, __entry->lnotअगरy_pid,
			__entry->lnotअगरy_tid)
);

TRACE_EVENT(	vas_tx_win_खोलो,

		TP_PROTO(काष्ठा task_काष्ठा *tsk,
			 पूर्णांक vasid,
			 पूर्णांक cop,
			 काष्ठा vas_tx_win_attr *txattr),

		TP_ARGS(tsk, vasid, cop, txattr),

		TP_STRUCT__entry(
			__field(काष्ठा task_काष्ठा *, tsk)
			__field(पूर्णांक, pid)
			__field(पूर्णांक, cop)
			__field(पूर्णांक, vasid)
			__field(काष्ठा vas_tx_win_attr *, txattr)
			__field(पूर्णांक, lpid)
			__field(पूर्णांक, pidr)
		),

		TP_fast_assign(
			__entry->pid = tsk->pid;
			__entry->vasid = vasid;
			__entry->cop = cop;
			__entry->lpid = txattr->lpid;
			__entry->pidr = txattr->pidr;
		),

		TP_prपूर्णांकk("pid=%d, vasid=%d, cop=%d, lpid=%d, pidr=%d",
			__entry->pid, __entry->vasid, __entry->cop,
			__entry->lpid, __entry->pidr)
);

TRACE_EVENT(	vas_paste_crb,

		TP_PROTO(काष्ठा task_काष्ठा *tsk,
			काष्ठा vas_winकरोw *win),

		TP_ARGS(tsk, win),

		TP_STRUCT__entry(
			__field(काष्ठा task_काष्ठा *, tsk)
			__field(काष्ठा vas_winकरोw *, win)
			__field(पूर्णांक, pid)
			__field(पूर्णांक, vasid)
			__field(पूर्णांक, winid)
			__field(अचिन्हित दीर्घ, paste_kaddr)
		),

		TP_fast_assign(
			__entry->pid = tsk->pid;
			__entry->vasid = win->vinst->vas_id;
			__entry->winid = win->winid;
			__entry->paste_kaddr = (अचिन्हित दीर्घ)win->paste_kaddr
		),

		TP_prपूर्णांकk("pid=%d, vasid=%d, winid=%d, paste_kaddr=0x%016lx\n",
			__entry->pid, __entry->vasid, __entry->winid,
			__entry->paste_kaddr)
);

#पूर्ण_अगर /* _VAS_TRACE_H */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH ../../arch/घातerpc/platक्रमms/घातernv
#घोषणा TRACE_INCLUDE_खाता vas-trace
#समावेश <trace/define_trace.h>
