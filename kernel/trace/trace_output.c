<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * trace_output.c
 *
 * Copyright (C) 2008 Red Hat Inc, Steven Rostedt <srostedt@redhat.com>
 *
 */
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/sched/mm.h>

#समावेश "trace_output.h"

/* must be a घातer of 2 */
#घोषणा EVENT_HASHSIZE	128

DECLARE_RWSEM(trace_event_sem);

अटल काष्ठा hlist_head event_hash[EVENT_HASHSIZE] __पढ़ो_mostly;

अटल पूर्णांक next_event_type = __TRACE_LAST_TYPE;

क्रमागत prपूर्णांक_line_t trace_prपूर्णांक_bमाला_दो_msg_only(काष्ठा trace_iterator *iter)
अणु
	काष्ठा trace_seq *s = &iter->seq;
	काष्ठा trace_entry *entry = iter->ent;
	काष्ठा bमाला_दो_entry *field;

	trace_assign_type(field, entry);

	trace_seq_माला_दो(s, field->str);

	वापस trace_handle_वापस(s);
पूर्ण

क्रमागत prपूर्णांक_line_t trace_prपूर्णांक_bprपूर्णांकk_msg_only(काष्ठा trace_iterator *iter)
अणु
	काष्ठा trace_seq *s = &iter->seq;
	काष्ठा trace_entry *entry = iter->ent;
	काष्ठा bprपूर्णांक_entry *field;

	trace_assign_type(field, entry);

	trace_seq_bम_लिखो(s, field->fmt, field->buf);

	वापस trace_handle_वापस(s);
पूर्ण

क्रमागत prपूर्णांक_line_t trace_prपूर्णांक_prपूर्णांकk_msg_only(काष्ठा trace_iterator *iter)
अणु
	काष्ठा trace_seq *s = &iter->seq;
	काष्ठा trace_entry *entry = iter->ent;
	काष्ठा prपूर्णांक_entry *field;

	trace_assign_type(field, entry);

	trace_seq_माला_दो(s, field->buf);

	वापस trace_handle_वापस(s);
पूर्ण

स्थिर अक्षर *
trace_prपूर्णांक_flags_seq(काष्ठा trace_seq *p, स्थिर अक्षर *delim,
		      अचिन्हित दीर्घ flags,
		      स्थिर काष्ठा trace_prपूर्णांक_flags *flag_array)
अणु
	अचिन्हित दीर्घ mask;
	स्थिर अक्षर *str;
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);
	पूर्णांक i, first = 1;

	क्रम (i = 0;  flag_array[i].name && flags; i++) अणु

		mask = flag_array[i].mask;
		अगर ((flags & mask) != mask)
			जारी;

		str = flag_array[i].name;
		flags &= ~mask;
		अगर (!first && delim)
			trace_seq_माला_दो(p, delim);
		अन्यथा
			first = 0;
		trace_seq_माला_दो(p, str);
	पूर्ण

	/* check क्रम left over flags */
	अगर (flags) अणु
		अगर (!first && delim)
			trace_seq_माला_दो(p, delim);
		trace_seq_म_लिखो(p, "0x%lx", flags);
	पूर्ण

	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(trace_prपूर्णांक_flags_seq);

स्थिर अक्षर *
trace_prपूर्णांक_symbols_seq(काष्ठा trace_seq *p, अचिन्हित दीर्घ val,
			स्थिर काष्ठा trace_prपूर्णांक_flags *symbol_array)
अणु
	पूर्णांक i;
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);

	क्रम (i = 0;  symbol_array[i].name; i++) अणु

		अगर (val != symbol_array[i].mask)
			जारी;

		trace_seq_माला_दो(p, symbol_array[i].name);
		अवरोध;
	पूर्ण

	अगर (ret == (स्थिर अक्षर *)(trace_seq_buffer_ptr(p)))
		trace_seq_म_लिखो(p, "0x%lx", val);

	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(trace_prपूर्णांक_symbols_seq);

#अगर BITS_PER_LONG == 32
स्थिर अक्षर *
trace_prपूर्णांक_flags_seq_u64(काष्ठा trace_seq *p, स्थिर अक्षर *delim,
		      अचिन्हित दीर्घ दीर्घ flags,
		      स्थिर काष्ठा trace_prपूर्णांक_flags_u64 *flag_array)
अणु
	अचिन्हित दीर्घ दीर्घ mask;
	स्थिर अक्षर *str;
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);
	पूर्णांक i, first = 1;

	क्रम (i = 0;  flag_array[i].name && flags; i++) अणु

		mask = flag_array[i].mask;
		अगर ((flags & mask) != mask)
			जारी;

		str = flag_array[i].name;
		flags &= ~mask;
		अगर (!first && delim)
			trace_seq_माला_दो(p, delim);
		अन्यथा
			first = 0;
		trace_seq_माला_दो(p, str);
	पूर्ण

	/* check क्रम left over flags */
	अगर (flags) अणु
		अगर (!first && delim)
			trace_seq_माला_दो(p, delim);
		trace_seq_म_लिखो(p, "0x%llx", flags);
	पूर्ण

	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(trace_prपूर्णांक_flags_seq_u64);

स्थिर अक्षर *
trace_prपूर्णांक_symbols_seq_u64(काष्ठा trace_seq *p, अचिन्हित दीर्घ दीर्घ val,
			 स्थिर काष्ठा trace_prपूर्णांक_flags_u64 *symbol_array)
अणु
	पूर्णांक i;
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);

	क्रम (i = 0;  symbol_array[i].name; i++) अणु

		अगर (val != symbol_array[i].mask)
			जारी;

		trace_seq_माला_दो(p, symbol_array[i].name);
		अवरोध;
	पूर्ण

	अगर (ret == (स्थिर अक्षर *)(trace_seq_buffer_ptr(p)))
		trace_seq_म_लिखो(p, "0x%llx", val);

	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(trace_prपूर्णांक_symbols_seq_u64);
#पूर्ण_अगर

स्थिर अक्षर *
trace_prपूर्णांक_biपंचांगask_seq(काष्ठा trace_seq *p, व्योम *biपंचांगask_ptr,
			अचिन्हित पूर्णांक biपंचांगask_size)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);

	trace_seq_biपंचांगask(p, biपंचांगask_ptr, biपंचांगask_size * 8);
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(trace_prपूर्णांक_biपंचांगask_seq);

/**
 * trace_prपूर्णांक_hex_seq - prपूर्णांक buffer as hex sequence
 * @p: trace seq काष्ठा to ग_लिखो to
 * @buf: The buffer to prपूर्णांक
 * @buf_len: Length of @buf in bytes
 * @concatenate: Prपूर्णांक @buf as single hex string or with spacing
 *
 * Prपूर्णांकs the passed buffer as a hex sequence either as a whole,
 * single hex string अगर @concatenate is true or with spacing after
 * each byte in हाल @concatenate is false.
 */
स्थिर अक्षर *
trace_prपूर्णांक_hex_seq(काष्ठा trace_seq *p, स्थिर अचिन्हित अक्षर *buf, पूर्णांक buf_len,
		    bool concatenate)
अणु
	पूर्णांक i;
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);
	स्थिर अक्षर *fmt = concatenate ? "%*phN" : "%*ph";

	क्रम (i = 0; i < buf_len; i += 16)
		trace_seq_म_लिखो(p, fmt, min(buf_len - i, 16), &buf[i]);
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(trace_prपूर्णांक_hex_seq);

स्थिर अक्षर *
trace_prपूर्णांक_array_seq(काष्ठा trace_seq *p, स्थिर व्योम *buf, पूर्णांक count,
		      माप_प्रकार el_size)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);
	स्थिर अक्षर *prefix = "";
	व्योम *ptr = (व्योम *)buf;
	माप_प्रकार buf_len = count * el_size;

	trace_seq_अ_दो(p, '{');

	जबतक (ptr < buf + buf_len) अणु
		चयन (el_size) अणु
		हाल 1:
			trace_seq_म_लिखो(p, "%s0x%x", prefix,
					 *(u8 *)ptr);
			अवरोध;
		हाल 2:
			trace_seq_म_लिखो(p, "%s0x%x", prefix,
					 *(u16 *)ptr);
			अवरोध;
		हाल 4:
			trace_seq_म_लिखो(p, "%s0x%x", prefix,
					 *(u32 *)ptr);
			अवरोध;
		हाल 8:
			trace_seq_म_लिखो(p, "%s0x%llx", prefix,
					 *(u64 *)ptr);
			अवरोध;
		शेष:
			trace_seq_म_लिखो(p, "BAD SIZE:%zu 0x%x", el_size,
					 *(u8 *)ptr);
			el_size = 1;
		पूर्ण
		prefix = ",";
		ptr += el_size;
	पूर्ण

	trace_seq_अ_दो(p, '}');
	trace_seq_अ_दो(p, 0);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(trace_prपूर्णांक_array_seq);

स्थिर अक्षर *
trace_prपूर्णांक_hex_dump_seq(काष्ठा trace_seq *p, स्थिर अक्षर *prefix_str,
			 पूर्णांक prefix_type, पूर्णांक rowsize, पूर्णांक groupsize,
			 स्थिर व्योम *buf, माप_प्रकार len, bool ascii)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);

	trace_seq_अ_दो(p, '\n');
	trace_seq_hex_dump(p, prefix_str, prefix_type,
			   rowsize, groupsize, buf, len, ascii);
	trace_seq_अ_दो(p, 0);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(trace_prपूर्णांक_hex_dump_seq);

पूर्णांक trace_raw_output_prep(काष्ठा trace_iterator *iter,
			  काष्ठा trace_event *trace_event)
अणु
	काष्ठा trace_event_call *event;
	काष्ठा trace_seq *s = &iter->seq;
	काष्ठा trace_seq *p = &iter->पंचांगp_seq;
	काष्ठा trace_entry *entry;

	event = container_of(trace_event, काष्ठा trace_event_call, event);
	entry = iter->ent;

	अगर (entry->type != event->event.type) अणु
		WARN_ON_ONCE(1);
		वापस TRACE_TYPE_UNHANDLED;
	पूर्ण

	trace_seq_init(p);
	trace_seq_म_लिखो(s, "%s: ", trace_event_name(event));

	वापस trace_handle_वापस(s);
पूर्ण
EXPORT_SYMBOL(trace_raw_output_prep);

व्योम trace_event_म_लिखो(काष्ठा trace_iterator *iter, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;

	बहु_शुरू(ap, fmt);
	trace_check_भ_लिखो(iter, trace_event_क्रमmat(iter, fmt), ap);
	बहु_पूर्ण(ap);
पूर्ण
EXPORT_SYMBOL(trace_event_म_लिखो);

अटल पूर्णांक trace_output_raw(काष्ठा trace_iterator *iter, अक्षर *name,
			    अक्षर *fmt, बहु_सूची ap)
अणु
	काष्ठा trace_seq *s = &iter->seq;

	trace_seq_म_लिखो(s, "%s: ", name);
	trace_seq_भ_लिखो(s, trace_event_क्रमmat(iter, fmt), ap);

	वापस trace_handle_वापस(s);
पूर्ण

पूर्णांक trace_output_call(काष्ठा trace_iterator *iter, अक्षर *name, अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	पूर्णांक ret;

	बहु_शुरू(ap, fmt);
	ret = trace_output_raw(iter, name, fmt, ap);
	बहु_पूर्ण(ap);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(trace_output_call);

#अगर_घोषित CONFIG_KRETPROBES
अटल अंतरभूत स्थिर अक्षर *kretprobed(स्थिर अक्षर *name)
अणु
	अटल स्थिर अक्षर tramp_name[] = "kretprobe_trampoline";
	पूर्णांक size = माप(tramp_name);

	अगर (म_भेदन(tramp_name, name, size) == 0)
		वापस "[unknown/kretprobe'd]";
	वापस name;
पूर्ण
#अन्यथा
अटल अंतरभूत स्थिर अक्षर *kretprobed(स्थिर अक्षर *name)
अणु
	वापस name;
पूर्ण
#पूर्ण_अगर /* CONFIG_KRETPROBES */

व्योम
trace_seq_prपूर्णांक_sym(काष्ठा trace_seq *s, अचिन्हित दीर्घ address, bool offset)
अणु
#अगर_घोषित CONFIG_KALLSYMS
	अक्षर str[KSYM_SYMBOL_LEN];
	स्थिर अक्षर *name;

	अगर (offset)
		sprपूर्णांक_symbol(str, address);
	अन्यथा
		kallsyms_lookup(address, शून्य, शून्य, शून्य, str);
	name = kretprobed(str);

	अगर (name && म_माप(name)) अणु
		trace_seq_माला_दो(s, name);
		वापस;
	पूर्ण
#पूर्ण_अगर
	trace_seq_म_लिखो(s, "0x%08lx", address);
पूर्ण

#अगर_अघोषित CONFIG_64BIT
# define IP_FMT "%08lx"
#अन्यथा
# define IP_FMT "%016lx"
#पूर्ण_अगर

अटल पूर्णांक seq_prपूर्णांक_user_ip(काष्ठा trace_seq *s, काष्ठा mm_काष्ठा *mm,
			     अचिन्हित दीर्घ ip, अचिन्हित दीर्घ sym_flags)
अणु
	काष्ठा file *file = शून्य;
	अचिन्हित दीर्घ vmstart = 0;
	पूर्णांक ret = 1;

	अगर (s->full)
		वापस 0;

	अगर (mm) अणु
		स्थिर काष्ठा vm_area_काष्ठा *vma;

		mmap_पढ़ो_lock(mm);
		vma = find_vma(mm, ip);
		अगर (vma) अणु
			file = vma->vm_file;
			vmstart = vma->vm_start;
		पूर्ण
		अगर (file) अणु
			ret = trace_seq_path(s, &file->f_path);
			अगर (ret)
				trace_seq_म_लिखो(s, "[+0x%lx]",
						 ip - vmstart);
		पूर्ण
		mmap_पढ़ो_unlock(mm);
	पूर्ण
	अगर (ret && ((sym_flags & TRACE_ITER_SYM_ADDR) || !file))
		trace_seq_म_लिखो(s, " <" IP_FMT ">", ip);
	वापस !trace_seq_has_overflowed(s);
पूर्ण

पूर्णांक
seq_prपूर्णांक_ip_sym(काष्ठा trace_seq *s, अचिन्हित दीर्घ ip, अचिन्हित दीर्घ sym_flags)
अणु
	अगर (!ip) अणु
		trace_seq_अ_दो(s, '0');
		जाओ out;
	पूर्ण

	trace_seq_prपूर्णांक_sym(s, ip, sym_flags & TRACE_ITER_SYM_OFFSET);

	अगर (sym_flags & TRACE_ITER_SYM_ADDR)
		trace_seq_म_लिखो(s, " <" IP_FMT ">", ip);

 out:
	वापस !trace_seq_has_overflowed(s);
पूर्ण

/**
 * trace_prपूर्णांक_lat_fmt - prपूर्णांक the irq, preempt and lockdep fields
 * @s: trace seq काष्ठा to ग_लिखो to
 * @entry: The trace entry field from the ring buffer
 *
 * Prपूर्णांकs the generic fields of irqs off, in hard or softirq, preempt
 * count.
 */
पूर्णांक trace_prपूर्णांक_lat_fmt(काष्ठा trace_seq *s, काष्ठा trace_entry *entry)
अणु
	अक्षर hardsoft_irq;
	अक्षर need_resched;
	अक्षर irqs_off;
	पूर्णांक hardirq;
	पूर्णांक softirq;
	पूर्णांक nmi;

	nmi = entry->flags & TRACE_FLAG_NMI;
	hardirq = entry->flags & TRACE_FLAG_HARसूचीQ;
	softirq = entry->flags & TRACE_FLAG_SOFTIRQ;

	irqs_off =
		(entry->flags & TRACE_FLAG_IRQS_OFF) ? 'd' :
		(entry->flags & TRACE_FLAG_IRQS_NOSUPPORT) ? 'X' :
		'.';

	चयन (entry->flags & (TRACE_FLAG_NEED_RESCHED |
				TRACE_FLAG_PREEMPT_RESCHED)) अणु
	हाल TRACE_FLAG_NEED_RESCHED | TRACE_FLAG_PREEMPT_RESCHED:
		need_resched = 'N';
		अवरोध;
	हाल TRACE_FLAG_NEED_RESCHED:
		need_resched = 'n';
		अवरोध;
	हाल TRACE_FLAG_PREEMPT_RESCHED:
		need_resched = 'p';
		अवरोध;
	शेष:
		need_resched = '.';
		अवरोध;
	पूर्ण

	hardsoft_irq =
		(nmi && hardirq)     ? 'Z' :
		nmi                  ? 'z' :
		(hardirq && softirq) ? 'H' :
		hardirq              ? 'h' :
		softirq              ? 's' :
		                       '.' ;

	trace_seq_म_लिखो(s, "%c%c%c",
			 irqs_off, need_resched, hardsoft_irq);

	अगर (entry->preempt_count)
		trace_seq_म_लिखो(s, "%x", entry->preempt_count);
	अन्यथा
		trace_seq_अ_दो(s, '.');

	वापस !trace_seq_has_overflowed(s);
पूर्ण

अटल पूर्णांक
lat_prपूर्णांक_generic(काष्ठा trace_seq *s, काष्ठा trace_entry *entry, पूर्णांक cpu)
अणु
	अक्षर comm[TASK_COMM_LEN];

	trace_find_cmdline(entry->pid, comm);

	trace_seq_म_लिखो(s, "%8.8s-%-7d %3d",
			 comm, entry->pid, cpu);

	वापस trace_prपूर्णांक_lat_fmt(s, entry);
पूर्ण

#अघोषित MARK
#घोषणा MARK(v, s) अणु.val = v, .sym = sपूर्ण
/* trace overhead mark */
अटल स्थिर काष्ठा trace_mark अणु
	अचिन्हित दीर्घ दीर्घ	val; /* unit: nsec */
	अक्षर			sym;
पूर्ण mark[] = अणु
	MARK(1000000000ULL	, '$'), /* 1 sec */
	MARK(100000000ULL	, '@'), /* 100 msec */
	MARK(10000000ULL	, '*'), /* 10 msec */
	MARK(1000000ULL		, '#'), /* 1000 usecs */
	MARK(100000ULL		, '!'), /* 100 usecs */
	MARK(10000ULL		, '+'), /* 10 usecs */
पूर्ण;
#अघोषित MARK

अक्षर trace_find_mark(अचिन्हित दीर्घ दीर्घ d)
अणु
	पूर्णांक i;
	पूर्णांक size = ARRAY_SIZE(mark);

	क्रम (i = 0; i < size; i++) अणु
		अगर (d > mark[i].val)
			अवरोध;
	पूर्ण

	वापस (i == size) ? ' ' : mark[i].sym;
पूर्ण

अटल पूर्णांक
lat_prपूर्णांक_बारtamp(काष्ठा trace_iterator *iter, u64 next_ts)
अणु
	काष्ठा trace_array *tr = iter->tr;
	अचिन्हित दीर्घ verbose = tr->trace_flags & TRACE_ITER_VERBOSE;
	अचिन्हित दीर्घ in_ns = iter->iter_flags & TRACE_खाता_TIME_IN_NS;
	अचिन्हित दीर्घ दीर्घ असल_ts = iter->ts - iter->array_buffer->समय_start;
	अचिन्हित दीर्घ दीर्घ rel_ts = next_ts - iter->ts;
	काष्ठा trace_seq *s = &iter->seq;

	अगर (in_ns) अणु
		असल_ts = ns2usecs(असल_ts);
		rel_ts = ns2usecs(rel_ts);
	पूर्ण

	अगर (verbose && in_ns) अणु
		अचिन्हित दीर्घ असल_usec = करो_भाग(असल_ts, USEC_PER_MSEC);
		अचिन्हित दीर्घ असल_msec = (अचिन्हित दीर्घ)असल_ts;
		अचिन्हित दीर्घ rel_usec = करो_भाग(rel_ts, USEC_PER_MSEC);
		अचिन्हित दीर्घ rel_msec = (अचिन्हित दीर्घ)rel_ts;

		trace_seq_म_लिखो(
			s, "[%08llx] %ld.%03ldms (+%ld.%03ldms): ",
			ns2usecs(iter->ts),
			असल_msec, असल_usec,
			rel_msec, rel_usec);

	पूर्ण अन्यथा अगर (verbose && !in_ns) अणु
		trace_seq_म_लिखो(
			s, "[%016llx] %lld (+%lld): ",
			iter->ts, असल_ts, rel_ts);

	पूर्ण अन्यथा अगर (!verbose && in_ns) अणु
		trace_seq_म_लिखो(
			s, " %4lldus%c: ",
			असल_ts,
			trace_find_mark(rel_ts * NSEC_PER_USEC));

	पूर्ण अन्यथा अणु /* !verbose && !in_ns */
		trace_seq_म_लिखो(s, " %4lld: ", असल_ts);
	पूर्ण

	वापस !trace_seq_has_overflowed(s);
पूर्ण

अटल व्योम trace_prपूर्णांक_समय(काष्ठा trace_seq *s, काष्ठा trace_iterator *iter,
			     अचिन्हित दीर्घ दीर्घ ts)
अणु
	अचिन्हित दीर्घ secs, usec_rem;
	अचिन्हित दीर्घ दीर्घ t;

	अगर (iter->iter_flags & TRACE_खाता_TIME_IN_NS) अणु
		t = ns2usecs(ts);
		usec_rem = करो_भाग(t, USEC_PER_SEC);
		secs = (अचिन्हित दीर्घ)t;
		trace_seq_म_लिखो(s, " %5lu.%06lu", secs, usec_rem);
	पूर्ण अन्यथा
		trace_seq_म_लिखो(s, " %12llu", ts);
पूर्ण

पूर्णांक trace_prपूर्णांक_context(काष्ठा trace_iterator *iter)
अणु
	काष्ठा trace_array *tr = iter->tr;
	काष्ठा trace_seq *s = &iter->seq;
	काष्ठा trace_entry *entry = iter->ent;
	अक्षर comm[TASK_COMM_LEN];

	trace_find_cmdline(entry->pid, comm);

	trace_seq_म_लिखो(s, "%16s-%-7d ", comm, entry->pid);

	अगर (tr->trace_flags & TRACE_ITER_RECORD_TGID) अणु
		अचिन्हित पूर्णांक tgid = trace_find_tgid(entry->pid);

		अगर (!tgid)
			trace_seq_म_लिखो(s, "(-------) ");
		अन्यथा
			trace_seq_म_लिखो(s, "(%7d) ", tgid);
	पूर्ण

	trace_seq_म_लिखो(s, "[%03d] ", iter->cpu);

	अगर (tr->trace_flags & TRACE_ITER_IRQ_INFO)
		trace_prपूर्णांक_lat_fmt(s, entry);

	trace_prपूर्णांक_समय(s, iter, iter->ts);
	trace_seq_माला_दो(s, ": ");

	वापस !trace_seq_has_overflowed(s);
पूर्ण

पूर्णांक trace_prपूर्णांक_lat_context(काष्ठा trace_iterator *iter)
अणु
	काष्ठा trace_entry *entry, *next_entry;
	काष्ठा trace_array *tr = iter->tr;
	काष्ठा trace_seq *s = &iter->seq;
	अचिन्हित दीर्घ verbose = (tr->trace_flags & TRACE_ITER_VERBOSE);
	u64 next_ts;

	next_entry = trace_find_next_entry(iter, शून्य, &next_ts);
	अगर (!next_entry)
		next_ts = iter->ts;

	/* trace_find_next_entry() may change iter->ent */
	entry = iter->ent;

	अगर (verbose) अणु
		अक्षर comm[TASK_COMM_LEN];

		trace_find_cmdline(entry->pid, comm);

		trace_seq_म_लिखो(
			s, "%16s %7d %3d %d %08x %08lx ",
			comm, entry->pid, iter->cpu, entry->flags,
			entry->preempt_count, iter->idx);
	पूर्ण अन्यथा अणु
		lat_prपूर्णांक_generic(s, entry, iter->cpu);
	पूर्ण

	lat_prपूर्णांक_बारtamp(iter, next_ts);

	वापस !trace_seq_has_overflowed(s);
पूर्ण

/**
 * ftrace_find_event - find a रेजिस्टरed event
 * @type: the type of event to look क्रम
 *
 * Returns an event of type @type otherwise शून्य
 * Called with trace_event_पढ़ो_lock() held.
 */
काष्ठा trace_event *ftrace_find_event(पूर्णांक type)
अणु
	काष्ठा trace_event *event;
	अचिन्हित key;

	key = type & (EVENT_HASHSIZE - 1);

	hlist_क्रम_each_entry(event, &event_hash[key], node) अणु
		अगर (event->type == type)
			वापस event;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल LIST_HEAD(ftrace_event_list);

अटल पूर्णांक trace_search_list(काष्ठा list_head **list)
अणु
	काष्ठा trace_event *e;
	पूर्णांक next = __TRACE_LAST_TYPE;

	अगर (list_empty(&ftrace_event_list)) अणु
		*list = &ftrace_event_list;
		वापस next;
	पूर्ण

	/*
	 * We used up all possible max events,
	 * lets see अगर somebody मुक्तd one.
	 */
	list_क्रम_each_entry(e, &ftrace_event_list, list) अणु
		अगर (e->type != next)
			अवरोध;
		next++;
	पूर्ण

	/* Did we used up all 65 thousand events??? */
	अगर (next > TRACE_EVENT_TYPE_MAX)
		वापस 0;

	*list = &e->list;
	वापस next;
पूर्ण

व्योम trace_event_पढ़ो_lock(व्योम)
अणु
	करोwn_पढ़ो(&trace_event_sem);
पूर्ण

व्योम trace_event_पढ़ो_unlock(व्योम)
अणु
	up_पढ़ो(&trace_event_sem);
पूर्ण

/**
 * रेजिस्टर_trace_event - रेजिस्टर output क्रम an event type
 * @event: the event type to रेजिस्टर
 *
 * Event types are stored in a hash and this hash is used to
 * find a way to prपूर्णांक an event. If the @event->type is set
 * then it will use that type, otherwise it will assign a
 * type to use.
 *
 * If you assign your own type, please make sure it is added
 * to the trace_type क्रमागत in trace.h, to aव्योम collisions
 * with the dynamic types.
 *
 * Returns the event type number or zero on error.
 */
पूर्णांक रेजिस्टर_trace_event(काष्ठा trace_event *event)
अणु
	अचिन्हित key;
	पूर्णांक ret = 0;

	करोwn_ग_लिखो(&trace_event_sem);

	अगर (WARN_ON(!event))
		जाओ out;

	अगर (WARN_ON(!event->funcs))
		जाओ out;

	INIT_LIST_HEAD(&event->list);

	अगर (!event->type) अणु
		काष्ठा list_head *list = शून्य;

		अगर (next_event_type > TRACE_EVENT_TYPE_MAX) अणु

			event->type = trace_search_list(&list);
			अगर (!event->type)
				जाओ out;

		पूर्ण अन्यथा अणु

			event->type = next_event_type++;
			list = &ftrace_event_list;
		पूर्ण

		अगर (WARN_ON(ftrace_find_event(event->type)))
			जाओ out;

		list_add_tail(&event->list, list);

	पूर्ण अन्यथा अगर (event->type > __TRACE_LAST_TYPE) अणु
		prपूर्णांकk(KERN_WARNING "Need to add type to trace.h\n");
		WARN_ON(1);
		जाओ out;
	पूर्ण अन्यथा अणु
		/* Is this event alपढ़ोy used */
		अगर (ftrace_find_event(event->type))
			जाओ out;
	पूर्ण

	अगर (event->funcs->trace == शून्य)
		event->funcs->trace = trace_nop_prपूर्णांक;
	अगर (event->funcs->raw == शून्य)
		event->funcs->raw = trace_nop_prपूर्णांक;
	अगर (event->funcs->hex == शून्य)
		event->funcs->hex = trace_nop_prपूर्णांक;
	अगर (event->funcs->binary == शून्य)
		event->funcs->binary = trace_nop_prपूर्णांक;

	key = event->type & (EVENT_HASHSIZE - 1);

	hlist_add_head(&event->node, &event_hash[key]);

	ret = event->type;
 out:
	up_ग_लिखो(&trace_event_sem);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_trace_event);

/*
 * Used by module code with the trace_event_sem held क्रम ग_लिखो.
 */
पूर्णांक __unरेजिस्टर_trace_event(काष्ठा trace_event *event)
अणु
	hlist_del(&event->node);
	list_del(&event->list);
	वापस 0;
पूर्ण

/**
 * unरेजिस्टर_trace_event - हटाओ a no दीर्घer used event
 * @event: the event to हटाओ
 */
पूर्णांक unरेजिस्टर_trace_event(काष्ठा trace_event *event)
अणु
	करोwn_ग_लिखो(&trace_event_sem);
	__unरेजिस्टर_trace_event(event);
	up_ग_लिखो(&trace_event_sem);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_trace_event);

/*
 * Standard events
 */

क्रमागत prपूर्णांक_line_t trace_nop_prपूर्णांक(काष्ठा trace_iterator *iter, पूर्णांक flags,
				  काष्ठा trace_event *event)
अणु
	trace_seq_म_लिखो(&iter->seq, "type: %d\n", iter->ent->type);

	वापस trace_handle_वापस(&iter->seq);
पूर्ण

अटल व्योम prपूर्णांक_fn_trace(काष्ठा trace_seq *s, अचिन्हित दीर्घ ip,
			   अचिन्हित दीर्घ parent_ip, पूर्णांक flags)
अणु
	seq_prपूर्णांक_ip_sym(s, ip, flags);

	अगर ((flags & TRACE_ITER_PRINT_PARENT) && parent_ip) अणु
		trace_seq_माला_दो(s, " <-");
		seq_prपूर्णांक_ip_sym(s, parent_ip, flags);
	पूर्ण
पूर्ण

/* TRACE_FN */
अटल क्रमागत prपूर्णांक_line_t trace_fn_trace(काष्ठा trace_iterator *iter, पूर्णांक flags,
					काष्ठा trace_event *event)
अणु
	काष्ठा ftrace_entry *field;
	काष्ठा trace_seq *s = &iter->seq;

	trace_assign_type(field, iter->ent);

	prपूर्णांक_fn_trace(s, field->ip, field->parent_ip, flags);
	trace_seq_अ_दो(s, '\n');

	वापस trace_handle_वापस(s);
पूर्ण

अटल क्रमागत prपूर्णांक_line_t trace_fn_raw(काष्ठा trace_iterator *iter, पूर्णांक flags,
				      काष्ठा trace_event *event)
अणु
	काष्ठा ftrace_entry *field;

	trace_assign_type(field, iter->ent);

	trace_seq_म_लिखो(&iter->seq, "%lx %lx\n",
			 field->ip,
			 field->parent_ip);

	वापस trace_handle_वापस(&iter->seq);
पूर्ण

अटल क्रमागत prपूर्णांक_line_t trace_fn_hex(काष्ठा trace_iterator *iter, पूर्णांक flags,
				      काष्ठा trace_event *event)
अणु
	काष्ठा ftrace_entry *field;
	काष्ठा trace_seq *s = &iter->seq;

	trace_assign_type(field, iter->ent);

	SEQ_PUT_HEX_FIELD(s, field->ip);
	SEQ_PUT_HEX_FIELD(s, field->parent_ip);

	वापस trace_handle_वापस(s);
पूर्ण

अटल क्रमागत prपूर्णांक_line_t trace_fn_bin(काष्ठा trace_iterator *iter, पूर्णांक flags,
				      काष्ठा trace_event *event)
अणु
	काष्ठा ftrace_entry *field;
	काष्ठा trace_seq *s = &iter->seq;

	trace_assign_type(field, iter->ent);

	SEQ_PUT_FIELD(s, field->ip);
	SEQ_PUT_FIELD(s, field->parent_ip);

	वापस trace_handle_वापस(s);
पूर्ण

अटल काष्ठा trace_event_functions trace_fn_funcs = अणु
	.trace		= trace_fn_trace,
	.raw		= trace_fn_raw,
	.hex		= trace_fn_hex,
	.binary		= trace_fn_bin,
पूर्ण;

अटल काष्ठा trace_event trace_fn_event = अणु
	.type		= TRACE_FN,
	.funcs		= &trace_fn_funcs,
पूर्ण;

/* TRACE_CTX an TRACE_WAKE */
अटल क्रमागत prपूर्णांक_line_t trace_ctxwake_prपूर्णांक(काष्ठा trace_iterator *iter,
					     अक्षर *delim)
अणु
	काष्ठा ctx_चयन_entry *field;
	अक्षर comm[TASK_COMM_LEN];
	पूर्णांक S, T;


	trace_assign_type(field, iter->ent);

	T = task_index_to_अक्षर(field->next_state);
	S = task_index_to_अक्षर(field->prev_state);
	trace_find_cmdline(field->next_pid, comm);
	trace_seq_म_लिखो(&iter->seq,
			 " %7d:%3d:%c %s [%03d] %7d:%3d:%c %s\n",
			 field->prev_pid,
			 field->prev_prio,
			 S, delim,
			 field->next_cpu,
			 field->next_pid,
			 field->next_prio,
			 T, comm);

	वापस trace_handle_वापस(&iter->seq);
पूर्ण

अटल क्रमागत prपूर्णांक_line_t trace_ctx_prपूर्णांक(काष्ठा trace_iterator *iter, पूर्णांक flags,
					 काष्ठा trace_event *event)
अणु
	वापस trace_ctxwake_prपूर्णांक(iter, "==>");
पूर्ण

अटल क्रमागत prपूर्णांक_line_t trace_wake_prपूर्णांक(काष्ठा trace_iterator *iter,
					  पूर्णांक flags, काष्ठा trace_event *event)
अणु
	वापस trace_ctxwake_prपूर्णांक(iter, "  +");
पूर्ण

अटल पूर्णांक trace_ctxwake_raw(काष्ठा trace_iterator *iter, अक्षर S)
अणु
	काष्ठा ctx_चयन_entry *field;
	पूर्णांक T;

	trace_assign_type(field, iter->ent);

	अगर (!S)
		S = task_index_to_अक्षर(field->prev_state);
	T = task_index_to_अक्षर(field->next_state);
	trace_seq_म_लिखो(&iter->seq, "%d %d %c %d %d %d %c\n",
			 field->prev_pid,
			 field->prev_prio,
			 S,
			 field->next_cpu,
			 field->next_pid,
			 field->next_prio,
			 T);

	वापस trace_handle_वापस(&iter->seq);
पूर्ण

अटल क्रमागत prपूर्णांक_line_t trace_ctx_raw(काष्ठा trace_iterator *iter, पूर्णांक flags,
				       काष्ठा trace_event *event)
अणु
	वापस trace_ctxwake_raw(iter, 0);
पूर्ण

अटल क्रमागत prपूर्णांक_line_t trace_wake_raw(काष्ठा trace_iterator *iter, पूर्णांक flags,
					काष्ठा trace_event *event)
अणु
	वापस trace_ctxwake_raw(iter, '+');
पूर्ण


अटल पूर्णांक trace_ctxwake_hex(काष्ठा trace_iterator *iter, अक्षर S)
अणु
	काष्ठा ctx_चयन_entry *field;
	काष्ठा trace_seq *s = &iter->seq;
	पूर्णांक T;

	trace_assign_type(field, iter->ent);

	अगर (!S)
		S = task_index_to_अक्षर(field->prev_state);
	T = task_index_to_अक्षर(field->next_state);

	SEQ_PUT_HEX_FIELD(s, field->prev_pid);
	SEQ_PUT_HEX_FIELD(s, field->prev_prio);
	SEQ_PUT_HEX_FIELD(s, S);
	SEQ_PUT_HEX_FIELD(s, field->next_cpu);
	SEQ_PUT_HEX_FIELD(s, field->next_pid);
	SEQ_PUT_HEX_FIELD(s, field->next_prio);
	SEQ_PUT_HEX_FIELD(s, T);

	वापस trace_handle_वापस(s);
पूर्ण

अटल क्रमागत prपूर्णांक_line_t trace_ctx_hex(काष्ठा trace_iterator *iter, पूर्णांक flags,
				       काष्ठा trace_event *event)
अणु
	वापस trace_ctxwake_hex(iter, 0);
पूर्ण

अटल क्रमागत prपूर्णांक_line_t trace_wake_hex(काष्ठा trace_iterator *iter, पूर्णांक flags,
					काष्ठा trace_event *event)
अणु
	वापस trace_ctxwake_hex(iter, '+');
पूर्ण

अटल क्रमागत prपूर्णांक_line_t trace_ctxwake_bin(काष्ठा trace_iterator *iter,
					   पूर्णांक flags, काष्ठा trace_event *event)
अणु
	काष्ठा ctx_चयन_entry *field;
	काष्ठा trace_seq *s = &iter->seq;

	trace_assign_type(field, iter->ent);

	SEQ_PUT_FIELD(s, field->prev_pid);
	SEQ_PUT_FIELD(s, field->prev_prio);
	SEQ_PUT_FIELD(s, field->prev_state);
	SEQ_PUT_FIELD(s, field->next_cpu);
	SEQ_PUT_FIELD(s, field->next_pid);
	SEQ_PUT_FIELD(s, field->next_prio);
	SEQ_PUT_FIELD(s, field->next_state);

	वापस trace_handle_वापस(s);
पूर्ण

अटल काष्ठा trace_event_functions trace_ctx_funcs = अणु
	.trace		= trace_ctx_prपूर्णांक,
	.raw		= trace_ctx_raw,
	.hex		= trace_ctx_hex,
	.binary		= trace_ctxwake_bin,
पूर्ण;

अटल काष्ठा trace_event trace_ctx_event = अणु
	.type		= TRACE_CTX,
	.funcs		= &trace_ctx_funcs,
पूर्ण;

अटल काष्ठा trace_event_functions trace_wake_funcs = अणु
	.trace		= trace_wake_prपूर्णांक,
	.raw		= trace_wake_raw,
	.hex		= trace_wake_hex,
	.binary		= trace_ctxwake_bin,
पूर्ण;

अटल काष्ठा trace_event trace_wake_event = अणु
	.type		= TRACE_WAKE,
	.funcs		= &trace_wake_funcs,
पूर्ण;

/* TRACE_STACK */

अटल क्रमागत prपूर्णांक_line_t trace_stack_prपूर्णांक(काष्ठा trace_iterator *iter,
					   पूर्णांक flags, काष्ठा trace_event *event)
अणु
	काष्ठा stack_entry *field;
	काष्ठा trace_seq *s = &iter->seq;
	अचिन्हित दीर्घ *p;
	अचिन्हित दीर्घ *end;

	trace_assign_type(field, iter->ent);
	end = (अचिन्हित दीर्घ *)((दीर्घ)iter->ent + iter->ent_size);

	trace_seq_माला_दो(s, "<stack trace>\n");

	क्रम (p = field->caller; p && p < end && *p != अच_दीर्घ_उच्च; p++) अणु

		अगर (trace_seq_has_overflowed(s))
			अवरोध;

		trace_seq_माला_दो(s, " => ");
		seq_prपूर्णांक_ip_sym(s, *p, flags);
		trace_seq_अ_दो(s, '\n');
	पूर्ण

	वापस trace_handle_वापस(s);
पूर्ण

अटल काष्ठा trace_event_functions trace_stack_funcs = अणु
	.trace		= trace_stack_prपूर्णांक,
पूर्ण;

अटल काष्ठा trace_event trace_stack_event = अणु
	.type		= TRACE_STACK,
	.funcs		= &trace_stack_funcs,
पूर्ण;

/* TRACE_USER_STACK */
अटल क्रमागत prपूर्णांक_line_t trace_user_stack_prपूर्णांक(काष्ठा trace_iterator *iter,
						पूर्णांक flags, काष्ठा trace_event *event)
अणु
	काष्ठा trace_array *tr = iter->tr;
	काष्ठा userstack_entry *field;
	काष्ठा trace_seq *s = &iter->seq;
	काष्ठा mm_काष्ठा *mm = शून्य;
	अचिन्हित पूर्णांक i;

	trace_assign_type(field, iter->ent);

	trace_seq_माला_दो(s, "<user stack trace>\n");

	अगर (tr->trace_flags & TRACE_ITER_SYM_USEROBJ) अणु
		काष्ठा task_काष्ठा *task;
		/*
		 * we करो the lookup on the thपढ़ो group leader,
		 * since inभागidual thपढ़ोs might have alपढ़ोy quit!
		 */
		rcu_पढ़ो_lock();
		task = find_task_by_vpid(field->tgid);
		अगर (task)
			mm = get_task_mm(task);
		rcu_पढ़ो_unlock();
	पूर्ण

	क्रम (i = 0; i < FTRACE_STACK_ENTRIES; i++) अणु
		अचिन्हित दीर्घ ip = field->caller[i];

		अगर (!ip || trace_seq_has_overflowed(s))
			अवरोध;

		trace_seq_माला_दो(s, " => ");
		seq_prपूर्णांक_user_ip(s, mm, ip, flags);
		trace_seq_अ_दो(s, '\n');
	पूर्ण

	अगर (mm)
		mmput(mm);

	वापस trace_handle_वापस(s);
पूर्ण

अटल काष्ठा trace_event_functions trace_user_stack_funcs = अणु
	.trace		= trace_user_stack_prपूर्णांक,
पूर्ण;

अटल काष्ठा trace_event trace_user_stack_event = अणु
	.type		= TRACE_USER_STACK,
	.funcs		= &trace_user_stack_funcs,
पूर्ण;

/* TRACE_HWLAT */
अटल क्रमागत prपूर्णांक_line_t
trace_hwlat_prपूर्णांक(काष्ठा trace_iterator *iter, पूर्णांक flags,
		  काष्ठा trace_event *event)
अणु
	काष्ठा trace_entry *entry = iter->ent;
	काष्ठा trace_seq *s = &iter->seq;
	काष्ठा hwlat_entry *field;

	trace_assign_type(field, entry);

	trace_seq_म_लिखो(s, "#%-5u inner/outer(us): %4llu/%-5llu ts:%lld.%09ld count:%d",
			 field->seqnum,
			 field->duration,
			 field->outer_duration,
			 (दीर्घ दीर्घ)field->बारtamp.tv_sec,
			 field->बारtamp.tv_nsec, field->count);

	अगर (field->nmi_count) अणु
		/*
		 * The generic sched_घड़ी() is not NMI safe, thus
		 * we only record the count and not the समय.
		 */
		अगर (!IS_ENABLED(CONFIG_GENERIC_SCHED_CLOCK))
			trace_seq_म_लिखो(s, " nmi-total:%llu",
					 field->nmi_total_ts);
		trace_seq_म_लिखो(s, " nmi-count:%u",
				 field->nmi_count);
	पूर्ण

	trace_seq_अ_दो(s, '\n');

	वापस trace_handle_वापस(s);
पूर्ण


अटल क्रमागत prपूर्णांक_line_t
trace_hwlat_raw(काष्ठा trace_iterator *iter, पूर्णांक flags,
		काष्ठा trace_event *event)
अणु
	काष्ठा hwlat_entry *field;
	काष्ठा trace_seq *s = &iter->seq;

	trace_assign_type(field, iter->ent);

	trace_seq_म_लिखो(s, "%llu %lld %lld %09ld %u\n",
			 field->duration,
			 field->outer_duration,
			 (दीर्घ दीर्घ)field->बारtamp.tv_sec,
			 field->बारtamp.tv_nsec,
			 field->seqnum);

	वापस trace_handle_वापस(s);
पूर्ण

अटल काष्ठा trace_event_functions trace_hwlat_funcs = अणु
	.trace		= trace_hwlat_prपूर्णांक,
	.raw		= trace_hwlat_raw,
पूर्ण;

अटल काष्ठा trace_event trace_hwlat_event = अणु
	.type		= TRACE_HWLAT,
	.funcs		= &trace_hwlat_funcs,
पूर्ण;

/* TRACE_BPUTS */
अटल क्रमागत prपूर्णांक_line_t
trace_bमाला_दो_prपूर्णांक(काष्ठा trace_iterator *iter, पूर्णांक flags,
		   काष्ठा trace_event *event)
अणु
	काष्ठा trace_entry *entry = iter->ent;
	काष्ठा trace_seq *s = &iter->seq;
	काष्ठा bमाला_दो_entry *field;

	trace_assign_type(field, entry);

	seq_prपूर्णांक_ip_sym(s, field->ip, flags);
	trace_seq_माला_दो(s, ": ");
	trace_seq_माला_दो(s, field->str);

	वापस trace_handle_वापस(s);
पूर्ण


अटल क्रमागत prपूर्णांक_line_t
trace_bमाला_दो_raw(काष्ठा trace_iterator *iter, पूर्णांक flags,
		काष्ठा trace_event *event)
अणु
	काष्ठा bमाला_दो_entry *field;
	काष्ठा trace_seq *s = &iter->seq;

	trace_assign_type(field, iter->ent);

	trace_seq_म_लिखो(s, ": %lx : ", field->ip);
	trace_seq_माला_दो(s, field->str);

	वापस trace_handle_वापस(s);
पूर्ण

अटल काष्ठा trace_event_functions trace_bमाला_दो_funcs = अणु
	.trace		= trace_bमाला_दो_prपूर्णांक,
	.raw		= trace_bमाला_दो_raw,
पूर्ण;

अटल काष्ठा trace_event trace_bमाला_दो_event = अणु
	.type		= TRACE_BPUTS,
	.funcs		= &trace_bमाला_दो_funcs,
पूर्ण;

/* TRACE_BPRINT */
अटल क्रमागत prपूर्णांक_line_t
trace_bprपूर्णांक_prपूर्णांक(काष्ठा trace_iterator *iter, पूर्णांक flags,
		   काष्ठा trace_event *event)
अणु
	काष्ठा trace_entry *entry = iter->ent;
	काष्ठा trace_seq *s = &iter->seq;
	काष्ठा bprपूर्णांक_entry *field;

	trace_assign_type(field, entry);

	seq_prपूर्णांक_ip_sym(s, field->ip, flags);
	trace_seq_माला_दो(s, ": ");
	trace_seq_bम_लिखो(s, field->fmt, field->buf);

	वापस trace_handle_वापस(s);
पूर्ण


अटल क्रमागत prपूर्णांक_line_t
trace_bprपूर्णांक_raw(काष्ठा trace_iterator *iter, पूर्णांक flags,
		 काष्ठा trace_event *event)
अणु
	काष्ठा bprपूर्णांक_entry *field;
	काष्ठा trace_seq *s = &iter->seq;

	trace_assign_type(field, iter->ent);

	trace_seq_म_लिखो(s, ": %lx : ", field->ip);
	trace_seq_bम_लिखो(s, field->fmt, field->buf);

	वापस trace_handle_वापस(s);
पूर्ण

अटल काष्ठा trace_event_functions trace_bprपूर्णांक_funcs = अणु
	.trace		= trace_bprपूर्णांक_prपूर्णांक,
	.raw		= trace_bprपूर्णांक_raw,
पूर्ण;

अटल काष्ठा trace_event trace_bprपूर्णांक_event = अणु
	.type		= TRACE_BPRINT,
	.funcs		= &trace_bprपूर्णांक_funcs,
पूर्ण;

/* TRACE_PRINT */
अटल क्रमागत prपूर्णांक_line_t trace_prपूर्णांक_prपूर्णांक(काष्ठा trace_iterator *iter,
					   पूर्णांक flags, काष्ठा trace_event *event)
अणु
	काष्ठा prपूर्णांक_entry *field;
	काष्ठा trace_seq *s = &iter->seq;

	trace_assign_type(field, iter->ent);

	seq_prपूर्णांक_ip_sym(s, field->ip, flags);
	trace_seq_म_लिखो(s, ": %s", field->buf);

	वापस trace_handle_वापस(s);
पूर्ण

अटल क्रमागत prपूर्णांक_line_t trace_prपूर्णांक_raw(काष्ठा trace_iterator *iter, पूर्णांक flags,
					 काष्ठा trace_event *event)
अणु
	काष्ठा prपूर्णांक_entry *field;

	trace_assign_type(field, iter->ent);

	trace_seq_म_लिखो(&iter->seq, "# %lx %s", field->ip, field->buf);

	वापस trace_handle_वापस(&iter->seq);
पूर्ण

अटल काष्ठा trace_event_functions trace_prपूर्णांक_funcs = अणु
	.trace		= trace_prपूर्णांक_prपूर्णांक,
	.raw		= trace_prपूर्णांक_raw,
पूर्ण;

अटल काष्ठा trace_event trace_prपूर्णांक_event = अणु
	.type	 	= TRACE_PRINT,
	.funcs		= &trace_prपूर्णांक_funcs,
पूर्ण;

अटल क्रमागत prपूर्णांक_line_t trace_raw_data(काष्ठा trace_iterator *iter, पूर्णांक flags,
					 काष्ठा trace_event *event)
अणु
	काष्ठा raw_data_entry *field;
	पूर्णांक i;

	trace_assign_type(field, iter->ent);

	trace_seq_म_लिखो(&iter->seq, "# %x buf:", field->id);

	क्रम (i = 0; i < iter->ent_size - दुरत्व(काष्ठा raw_data_entry, buf); i++)
		trace_seq_म_लिखो(&iter->seq, " %02x",
				 (अचिन्हित अक्षर)field->buf[i]);

	trace_seq_अ_दो(&iter->seq, '\n');

	वापस trace_handle_वापस(&iter->seq);
पूर्ण

अटल काष्ठा trace_event_functions trace_raw_data_funcs = अणु
	.trace		= trace_raw_data,
	.raw		= trace_raw_data,
पूर्ण;

अटल काष्ठा trace_event trace_raw_data_event = अणु
	.type	 	= TRACE_RAW_DATA,
	.funcs		= &trace_raw_data_funcs,
पूर्ण;

अटल क्रमागत prपूर्णांक_line_t
trace_func_repeats_raw(काष्ठा trace_iterator *iter, पूर्णांक flags,
			 काष्ठा trace_event *event)
अणु
	काष्ठा func_repeats_entry *field;
	काष्ठा trace_seq *s = &iter->seq;

	trace_assign_type(field, iter->ent);

	trace_seq_म_लिखो(s, "%lu %lu %u %llu\n",
			 field->ip,
			 field->parent_ip,
			 field->count,
			 FUNC_REPEATS_GET_DELTA_TS(field));

	वापस trace_handle_वापस(s);
पूर्ण

अटल क्रमागत prपूर्णांक_line_t
trace_func_repeats_prपूर्णांक(काष्ठा trace_iterator *iter, पूर्णांक flags,
			 काष्ठा trace_event *event)
अणु
	काष्ठा func_repeats_entry *field;
	काष्ठा trace_seq *s = &iter->seq;

	trace_assign_type(field, iter->ent);

	prपूर्णांक_fn_trace(s, field->ip, field->parent_ip, flags);
	trace_seq_म_लिखो(s, " (repeats: %u, last_ts:", field->count);
	trace_prपूर्णांक_समय(s, iter,
			 iter->ts - FUNC_REPEATS_GET_DELTA_TS(field));
	trace_seq_माला_दो(s, ")\n");

	वापस trace_handle_वापस(s);
पूर्ण

अटल काष्ठा trace_event_functions trace_func_repeats_funcs = अणु
	.trace		= trace_func_repeats_prपूर्णांक,
	.raw		= trace_func_repeats_raw,
पूर्ण;

अटल काष्ठा trace_event trace_func_repeats_event = अणु
	.type	 	= TRACE_FUNC_REPEATS,
	.funcs		= &trace_func_repeats_funcs,
पूर्ण;

अटल काष्ठा trace_event *events[] __initdata = अणु
	&trace_fn_event,
	&trace_ctx_event,
	&trace_wake_event,
	&trace_stack_event,
	&trace_user_stack_event,
	&trace_bमाला_दो_event,
	&trace_bprपूर्णांक_event,
	&trace_prपूर्णांक_event,
	&trace_hwlat_event,
	&trace_raw_data_event,
	&trace_func_repeats_event,
	शून्य
पूर्ण;

__init अटल पूर्णांक init_events(व्योम)
अणु
	काष्ठा trace_event *event;
	पूर्णांक i, ret;

	क्रम (i = 0; events[i]; i++) अणु
		event = events[i];

		ret = रेजिस्टर_trace_event(event);
		अगर (!ret) अणु
			prपूर्णांकk(KERN_WARNING "event %d failed to register\n",
			       event->type);
			WARN_ON_ONCE(1);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
early_initcall(init_events);
