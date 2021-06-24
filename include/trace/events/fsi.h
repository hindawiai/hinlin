<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM fsi

#अगर !defined(_TRACE_FSI_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_FSI_H

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_EVENT(fsi_master_पढ़ो,
	TP_PROTO(स्थिर काष्ठा fsi_master *master, पूर्णांक link, पूर्णांक id,
			uपूर्णांक32_t addr, माप_प्रकार size),
	TP_ARGS(master, link, id, addr, size),
	TP_STRUCT__entry(
		__field(पूर्णांक,	master_idx)
		__field(पूर्णांक,	link)
		__field(पूर्णांक,	id)
		__field(__u32,	addr)
		__field(माप_प्रकार,	size)
	),
	TP_fast_assign(
		__entry->master_idx = master->idx;
		__entry->link = link;
		__entry->id = id;
		__entry->addr = addr;
		__entry->size = size;
	),
	TP_prपूर्णांकk("fsi%d:%02d:%02d %08x[%zu]",
		__entry->master_idx,
		__entry->link,
		__entry->id,
		__entry->addr,
		__entry->size
	)
);

TRACE_EVENT(fsi_master_ग_लिखो,
	TP_PROTO(स्थिर काष्ठा fsi_master *master, पूर्णांक link, पूर्णांक id,
			uपूर्णांक32_t addr, माप_प्रकार size, स्थिर व्योम *data),
	TP_ARGS(master, link, id, addr, size, data),
	TP_STRUCT__entry(
		__field(पूर्णांक,	master_idx)
		__field(पूर्णांक,	link)
		__field(पूर्णांक,	id)
		__field(__u32,	addr)
		__field(माप_प्रकार,	size)
		__field(__u32,	data)
	),
	TP_fast_assign(
		__entry->master_idx = master->idx;
		__entry->link = link;
		__entry->id = id;
		__entry->addr = addr;
		__entry->size = size;
		__entry->data = 0;
		स_नकल(&__entry->data, data, size);
	),
	TP_prपूर्णांकk("fsi%d:%02d:%02d %08x[%zu] <= {%*ph}",
		__entry->master_idx,
		__entry->link,
		__entry->id,
		__entry->addr,
		__entry->size,
		(पूर्णांक)__entry->size, &__entry->data
	)
);

TRACE_EVENT(fsi_master_rw_result,
	TP_PROTO(स्थिर काष्ठा fsi_master *master, पूर्णांक link, पूर्णांक id,
			uपूर्णांक32_t addr, माप_प्रकार size,
			bool ग_लिखो, स्थिर व्योम *data, पूर्णांक ret),
	TP_ARGS(master, link, id, addr, size, ग_लिखो, data, ret),
	TP_STRUCT__entry(
		__field(पूर्णांक,	master_idx)
		__field(पूर्णांक,	link)
		__field(पूर्णांक,	id)
		__field(__u32,	addr)
		__field(माप_प्रकार,	size)
		__field(bool,	ग_लिखो)
		__field(__u32,	data)
		__field(पूर्णांक,	ret)
	),
	TP_fast_assign(
		__entry->master_idx = master->idx;
		__entry->link = link;
		__entry->id = id;
		__entry->addr = addr;
		__entry->size = size;
		__entry->ग_लिखो = ग_लिखो;
		__entry->data = 0;
		__entry->ret = ret;
		अगर (__entry->ग_लिखो || !__entry->ret)
			स_नकल(&__entry->data, data, size);
	),
	TP_prपूर्णांकk("fsi%d:%02d:%02d %08x[%zu] %s {%*ph} ret %d",
		__entry->master_idx,
		__entry->link,
		__entry->id,
		__entry->addr,
		__entry->size,
		__entry->ग_लिखो ? "<=" : "=>",
		(पूर्णांक)__entry->size, &__entry->data,
		__entry->ret
	)
);

TRACE_EVENT(fsi_master_अवरोध,
	TP_PROTO(स्थिर काष्ठा fsi_master *master, पूर्णांक link),
	TP_ARGS(master, link),
	TP_STRUCT__entry(
		__field(पूर्णांक,	master_idx)
		__field(पूर्णांक,	link)
	),
	TP_fast_assign(
		__entry->master_idx = master->idx;
		__entry->link = link;
	),
	TP_prपूर्णांकk("fsi%d:%d",
		__entry->master_idx,
		__entry->link
	)
);


#पूर्ण_अगर /* _TRACE_FSI_H */

#समावेश <trace/define_trace.h>
