<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Memory mapped I/O tracing
 *
 * Copyright (C) 2008 Pekka Paalanen <pq@iki.fi>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/mmiotrace.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>

#समावेश <linux/atomic.h>

#समावेश "trace.h"
#समावेश "trace_output.h"

काष्ठा header_iter अणु
	काष्ठा pci_dev *dev;
पूर्ण;

अटल काष्ठा trace_array *mmio_trace_array;
अटल bool overrun_detected;
अटल अचिन्हित दीर्घ prev_overruns;
अटल atomic_t dropped_count;

अटल व्योम mmio_reset_data(काष्ठा trace_array *tr)
अणु
	overrun_detected = false;
	prev_overruns = 0;

	tracing_reset_online_cpus(&tr->array_buffer);
पूर्ण

अटल पूर्णांक mmio_trace_init(काष्ठा trace_array *tr)
अणु
	pr_debug("in %s\n", __func__);
	mmio_trace_array = tr;

	mmio_reset_data(tr);
	enable_mmiotrace();
	वापस 0;
पूर्ण

अटल व्योम mmio_trace_reset(काष्ठा trace_array *tr)
अणु
	pr_debug("in %s\n", __func__);

	disable_mmiotrace();
	mmio_reset_data(tr);
	mmio_trace_array = शून्य;
पूर्ण

अटल व्योम mmio_trace_start(काष्ठा trace_array *tr)
अणु
	pr_debug("in %s\n", __func__);
	mmio_reset_data(tr);
पूर्ण

अटल व्योम mmio_prपूर्णांक_pcidev(काष्ठा trace_seq *s, स्थिर काष्ठा pci_dev *dev)
अणु
	पूर्णांक i;
	resource_माप_प्रकार start, end;
	स्थिर काष्ठा pci_driver *drv = pci_dev_driver(dev);

	trace_seq_म_लिखो(s, "PCIDEV %02x%02x %04x%04x %x",
			 dev->bus->number, dev->devfn,
			 dev->venकरोr, dev->device, dev->irq);
	क्रम (i = 0; i < 7; i++) अणु
		start = dev->resource[i].start;
		trace_seq_म_लिखो(s, " %llx",
			(अचिन्हित दीर्घ दीर्घ)(start |
			(dev->resource[i].flags & PCI_REGION_FLAG_MASK)));
	पूर्ण
	क्रम (i = 0; i < 7; i++) अणु
		start = dev->resource[i].start;
		end = dev->resource[i].end;
		trace_seq_म_लिखो(s, " %llx",
			dev->resource[i].start < dev->resource[i].end ?
			(अचिन्हित दीर्घ दीर्घ)(end - start) + 1 : 0);
	पूर्ण
	अगर (drv)
		trace_seq_म_लिखो(s, " %s\n", drv->name);
	अन्यथा
		trace_seq_माला_दो(s, " \n");
पूर्ण

अटल व्योम destroy_header_iter(काष्ठा header_iter *hiter)
अणु
	अगर (!hiter)
		वापस;
	pci_dev_put(hiter->dev);
	kमुक्त(hiter);
पूर्ण

अटल व्योम mmio_pipe_खोलो(काष्ठा trace_iterator *iter)
अणु
	काष्ठा header_iter *hiter;
	काष्ठा trace_seq *s = &iter->seq;

	trace_seq_माला_दो(s, "VERSION 20070824\n");

	hiter = kzalloc(माप(*hiter), GFP_KERNEL);
	अगर (!hiter)
		वापस;

	hiter->dev = pci_get_device(PCI_ANY_ID, PCI_ANY_ID, शून्य);
	iter->निजी = hiter;
पूर्ण

/* XXX: This is not called when the pipe is बंदd! */
अटल व्योम mmio_बंद(काष्ठा trace_iterator *iter)
अणु
	काष्ठा header_iter *hiter = iter->निजी;
	destroy_header_iter(hiter);
	iter->निजी = शून्य;
पूर्ण

अटल अचिन्हित दीर्घ count_overruns(काष्ठा trace_iterator *iter)
अणु
	अचिन्हित दीर्घ cnt = atomic_xchg(&dropped_count, 0);
	अचिन्हित दीर्घ over = ring_buffer_overruns(iter->array_buffer->buffer);

	अगर (over > prev_overruns)
		cnt += over - prev_overruns;
	prev_overruns = over;
	वापस cnt;
पूर्ण

अटल sमाप_प्रकार mmio_पढ़ो(काष्ठा trace_iterator *iter, काष्ठा file *filp,
				अक्षर __user *ubuf, माप_प्रकार cnt, loff_t *ppos)
अणु
	sमाप_प्रकार ret;
	काष्ठा header_iter *hiter = iter->निजी;
	काष्ठा trace_seq *s = &iter->seq;
	अचिन्हित दीर्घ n;

	n = count_overruns(iter);
	अगर (n) अणु
		/* XXX: This is later than where events were lost. */
		trace_seq_म_लिखो(s, "MARK 0.000000 Lost %lu events.\n", n);
		अगर (!overrun_detected)
			pr_warn("mmiotrace has lost events\n");
		overrun_detected = true;
		जाओ prपूर्णांक_out;
	पूर्ण

	अगर (!hiter)
		वापस 0;

	mmio_prपूर्णांक_pcidev(s, hiter->dev);
	hiter->dev = pci_get_device(PCI_ANY_ID, PCI_ANY_ID, hiter->dev);

	अगर (!hiter->dev) अणु
		destroy_header_iter(hiter);
		iter->निजी = शून्य;
	पूर्ण

prपूर्णांक_out:
	ret = trace_seq_to_user(s, ubuf, cnt);
	वापस (ret == -EBUSY) ? 0 : ret;
पूर्ण

अटल क्रमागत prपूर्णांक_line_t mmio_prपूर्णांक_rw(काष्ठा trace_iterator *iter)
अणु
	काष्ठा trace_entry *entry = iter->ent;
	काष्ठा trace_mmiotrace_rw *field;
	काष्ठा mmiotrace_rw *rw;
	काष्ठा trace_seq *s	= &iter->seq;
	अचिन्हित दीर्घ दीर्घ t	= ns2usecs(iter->ts);
	अचिन्हित दीर्घ usec_rem	= करो_भाग(t, USEC_PER_SEC);
	अचिन्हित secs		= (अचिन्हित दीर्घ)t;

	trace_assign_type(field, entry);
	rw = &field->rw;

	चयन (rw->opcode) अणु
	हाल MMIO_READ:
		trace_seq_म_लिखो(s,
			"R %d %u.%06lu %d 0x%llx 0x%lx 0x%lx %d\n",
			rw->width, secs, usec_rem, rw->map_id,
			(अचिन्हित दीर्घ दीर्घ)rw->phys,
			rw->value, rw->pc, 0);
		अवरोध;
	हाल MMIO_WRITE:
		trace_seq_म_लिखो(s,
			"W %d %u.%06lu %d 0x%llx 0x%lx 0x%lx %d\n",
			rw->width, secs, usec_rem, rw->map_id,
			(अचिन्हित दीर्घ दीर्घ)rw->phys,
			rw->value, rw->pc, 0);
		अवरोध;
	हाल MMIO_UNKNOWN_OP:
		trace_seq_म_लिखो(s,
			"UNKNOWN %u.%06lu %d 0x%llx %02lx,%02lx,"
			"%02lx 0x%lx %d\n",
			secs, usec_rem, rw->map_id,
			(अचिन्हित दीर्घ दीर्घ)rw->phys,
			(rw->value >> 16) & 0xff, (rw->value >> 8) & 0xff,
			(rw->value >> 0) & 0xff, rw->pc, 0);
		अवरोध;
	शेष:
		trace_seq_माला_दो(s, "rw what?\n");
		अवरोध;
	पूर्ण

	वापस trace_handle_वापस(s);
पूर्ण

अटल क्रमागत prपूर्णांक_line_t mmio_prपूर्णांक_map(काष्ठा trace_iterator *iter)
अणु
	काष्ठा trace_entry *entry = iter->ent;
	काष्ठा trace_mmiotrace_map *field;
	काष्ठा mmiotrace_map *m;
	काष्ठा trace_seq *s	= &iter->seq;
	अचिन्हित दीर्घ दीर्घ t	= ns2usecs(iter->ts);
	अचिन्हित दीर्घ usec_rem	= करो_भाग(t, USEC_PER_SEC);
	अचिन्हित secs		= (अचिन्हित दीर्घ)t;

	trace_assign_type(field, entry);
	m = &field->map;

	चयन (m->opcode) अणु
	हाल MMIO_PROBE:
		trace_seq_म_लिखो(s,
			"MAP %u.%06lu %d 0x%llx 0x%lx 0x%lx 0x%lx %d\n",
			secs, usec_rem, m->map_id,
			(अचिन्हित दीर्घ दीर्घ)m->phys, m->virt, m->len,
			0UL, 0);
		अवरोध;
	हाल MMIO_UNPROBE:
		trace_seq_म_लिखो(s,
			"UNMAP %u.%06lu %d 0x%lx %d\n",
			secs, usec_rem, m->map_id, 0UL, 0);
		अवरोध;
	शेष:
		trace_seq_माला_दो(s, "map what?\n");
		अवरोध;
	पूर्ण

	वापस trace_handle_वापस(s);
पूर्ण

अटल क्रमागत prपूर्णांक_line_t mmio_prपूर्णांक_mark(काष्ठा trace_iterator *iter)
अणु
	काष्ठा trace_entry *entry = iter->ent;
	काष्ठा prपूर्णांक_entry *prपूर्णांक = (काष्ठा prपूर्णांक_entry *)entry;
	स्थिर अक्षर *msg		= prपूर्णांक->buf;
	काष्ठा trace_seq *s	= &iter->seq;
	अचिन्हित दीर्घ दीर्घ t	= ns2usecs(iter->ts);
	अचिन्हित दीर्घ usec_rem	= करो_भाग(t, USEC_PER_SEC);
	अचिन्हित secs		= (अचिन्हित दीर्घ)t;

	/* The trailing newline must be in the message. */
	trace_seq_म_लिखो(s, "MARK %u.%06lu %s", secs, usec_rem, msg);

	वापस trace_handle_वापस(s);
पूर्ण

अटल क्रमागत prपूर्णांक_line_t mmio_prपूर्णांक_line(काष्ठा trace_iterator *iter)
अणु
	चयन (iter->ent->type) अणु
	हाल TRACE_MMIO_RW:
		वापस mmio_prपूर्णांक_rw(iter);
	हाल TRACE_MMIO_MAP:
		वापस mmio_prपूर्णांक_map(iter);
	हाल TRACE_PRINT:
		वापस mmio_prपूर्णांक_mark(iter);
	शेष:
		वापस TRACE_TYPE_HANDLED; /* ignore unknown entries */
	पूर्ण
पूर्ण

अटल काष्ठा tracer mmio_tracer __पढ़ो_mostly =
अणु
	.name		= "mmiotrace",
	.init		= mmio_trace_init,
	.reset		= mmio_trace_reset,
	.start		= mmio_trace_start,
	.pipe_खोलो	= mmio_pipe_खोलो,
	.बंद		= mmio_बंद,
	.पढ़ो		= mmio_पढ़ो,
	.prपूर्णांक_line	= mmio_prपूर्णांक_line,
	.noboot		= true,
पूर्ण;

__init अटल पूर्णांक init_mmio_trace(व्योम)
अणु
	वापस रेजिस्टर_tracer(&mmio_tracer);
पूर्ण
device_initcall(init_mmio_trace);

अटल व्योम __trace_mmiotrace_rw(काष्ठा trace_array *tr,
				काष्ठा trace_array_cpu *data,
				काष्ठा mmiotrace_rw *rw)
अणु
	काष्ठा trace_event_call *call = &event_mmiotrace_rw;
	काष्ठा trace_buffer *buffer = tr->array_buffer.buffer;
	काष्ठा ring_buffer_event *event;
	काष्ठा trace_mmiotrace_rw *entry;
	अचिन्हित पूर्णांक trace_ctx;

	trace_ctx = tracing_gen_ctx_flags(0);
	event = trace_buffer_lock_reserve(buffer, TRACE_MMIO_RW,
					  माप(*entry), trace_ctx);
	अगर (!event) अणु
		atomic_inc(&dropped_count);
		वापस;
	पूर्ण
	entry	= ring_buffer_event_data(event);
	entry->rw			= *rw;

	अगर (!call_filter_check_discard(call, entry, buffer, event))
		trace_buffer_unlock_commit(tr, buffer, event, trace_ctx);
पूर्ण

व्योम mmio_trace_rw(काष्ठा mmiotrace_rw *rw)
अणु
	काष्ठा trace_array *tr = mmio_trace_array;
	काष्ठा trace_array_cpu *data = per_cpu_ptr(tr->array_buffer.data, smp_processor_id());
	__trace_mmiotrace_rw(tr, data, rw);
पूर्ण

अटल व्योम __trace_mmiotrace_map(काष्ठा trace_array *tr,
				काष्ठा trace_array_cpu *data,
				काष्ठा mmiotrace_map *map)
अणु
	काष्ठा trace_event_call *call = &event_mmiotrace_map;
	काष्ठा trace_buffer *buffer = tr->array_buffer.buffer;
	काष्ठा ring_buffer_event *event;
	काष्ठा trace_mmiotrace_map *entry;
	अचिन्हित पूर्णांक trace_ctx;

	trace_ctx = tracing_gen_ctx_flags(0);
	event = trace_buffer_lock_reserve(buffer, TRACE_MMIO_MAP,
					  माप(*entry), trace_ctx);
	अगर (!event) अणु
		atomic_inc(&dropped_count);
		वापस;
	पूर्ण
	entry	= ring_buffer_event_data(event);
	entry->map			= *map;

	अगर (!call_filter_check_discard(call, entry, buffer, event))
		trace_buffer_unlock_commit(tr, buffer, event, trace_ctx);
पूर्ण

व्योम mmio_trace_mapping(काष्ठा mmiotrace_map *map)
अणु
	काष्ठा trace_array *tr = mmio_trace_array;
	काष्ठा trace_array_cpu *data;

	preempt_disable();
	data = per_cpu_ptr(tr->array_buffer.data, smp_processor_id());
	__trace_mmiotrace_map(tr, data, map);
	preempt_enable();
पूर्ण

पूर्णांक mmio_trace_prपूर्णांकk(स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	वापस trace_vprपूर्णांकk(0, fmt, args);
पूर्ण
