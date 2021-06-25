<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2014, Michael Ellerman, IBM Corp.
 */

#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/mman.h>

#समावेश "trace.h"


काष्ठा trace_buffer *trace_buffer_allocate(u64 size)
अणु
	काष्ठा trace_buffer *tb;

	अगर (size < माप(*tb)) अणु
		ख_लिखो(मानक_त्रुटि, "Error: trace buffer too small\n");
		वापस शून्य;
	पूर्ण

	tb = mmap(शून्य, size, PROT_READ | PROT_WRITE,
		  MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	अगर (tb == MAP_FAILED) अणु
		लिखो_त्रुटि("mmap");
		वापस शून्य;
	पूर्ण

	tb->size = size;
	tb->tail = tb->data;
	tb->overflow = false;

	वापस tb;
पूर्ण

अटल bool trace_check_bounds(काष्ठा trace_buffer *tb, व्योम *p)
अणु
	वापस p < ((व्योम *)tb + tb->size);
पूर्ण

अटल bool trace_check_alloc(काष्ठा trace_buffer *tb, व्योम *p)
अणु
	/*
	 * If we ever overflowed करोn't allow any more input. This prevents us
	 * from dropping a large item and then later logging a small one. The
	 * buffer should just stop when overflow happened, not be patchy. If
	 * you're overflowing, make your buffer bigger.
	 */
	अगर (tb->overflow)
		वापस false;

	अगर (!trace_check_bounds(tb, p)) अणु
		tb->overflow = true;
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम *trace_alloc(काष्ठा trace_buffer *tb, पूर्णांक bytes)
अणु
	व्योम *p, *newtail;

	p = tb->tail;
	newtail = tb->tail + bytes;
	अगर (!trace_check_alloc(tb, newtail))
		वापस शून्य;

	tb->tail = newtail;

	वापस p;
पूर्ण

अटल काष्ठा trace_entry *trace_alloc_entry(काष्ठा trace_buffer *tb, पूर्णांक payload_size)
अणु
	काष्ठा trace_entry *e;

	e = trace_alloc(tb, माप(*e) + payload_size);
	अगर (e)
		e->length = payload_size;

	वापस e;
पूर्ण

पूर्णांक trace_log_reg(काष्ठा trace_buffer *tb, u64 reg, u64 value)
अणु
	काष्ठा trace_entry *e;
	u64 *p;

	e = trace_alloc_entry(tb, माप(reg) + माप(value));
	अगर (!e)
		वापस -ENOSPC;

	e->type = TRACE_TYPE_REG;
	p = (u64 *)e->data;
	*p++ = reg;
	*p++ = value;

	वापस 0;
पूर्ण

पूर्णांक trace_log_counter(काष्ठा trace_buffer *tb, u64 value)
अणु
	काष्ठा trace_entry *e;
	u64 *p;

	e = trace_alloc_entry(tb, माप(value));
	अगर (!e)
		वापस -ENOSPC;

	e->type = TRACE_TYPE_COUNTER;
	p = (u64 *)e->data;
	*p++ = value;

	वापस 0;
पूर्ण

पूर्णांक trace_log_string(काष्ठा trace_buffer *tb, अक्षर *str)
अणु
	काष्ठा trace_entry *e;
	अक्षर *p;
	पूर्णांक len;

	len = म_माप(str);

	/* We शून्य terminate to make prपूर्णांकing easier */
	e = trace_alloc_entry(tb, len + 1);
	अगर (!e)
		वापस -ENOSPC;

	e->type = TRACE_TYPE_STRING;
	p = (अक्षर *)e->data;
	स_नकल(p, str, len);
	p += len;
	*p = '\0';

	वापस 0;
पूर्ण

पूर्णांक trace_log_indent(काष्ठा trace_buffer *tb)
अणु
	काष्ठा trace_entry *e;

	e = trace_alloc_entry(tb, 0);
	अगर (!e)
		वापस -ENOSPC;

	e->type = TRACE_TYPE_INDENT;

	वापस 0;
पूर्ण

पूर्णांक trace_log_outdent(काष्ठा trace_buffer *tb)
अणु
	काष्ठा trace_entry *e;

	e = trace_alloc_entry(tb, 0);
	अगर (!e)
		वापस -ENOSPC;

	e->type = TRACE_TYPE_OUTDENT;

	वापस 0;
पूर्ण

अटल व्योम trace_prपूर्णांक_header(पूर्णांक seq, पूर्णांक prefix)
अणु
	म_लिखो("%*s[%d]: ", prefix, "", seq);
पूर्ण

अटल अक्षर *trace_decode_reg(पूर्णांक reg)
अणु
	चयन (reg) अणु
		हाल 769: वापस "SPRN_MMCR2"; अवरोध;
		हाल 770: वापस "SPRN_MMCRA"; अवरोध;
		हाल 779: वापस "SPRN_MMCR0"; अवरोध;
		हाल 804: वापस "SPRN_EBBHR"; अवरोध;
		हाल 805: वापस "SPRN_EBBRR"; अवरोध;
		हाल 806: वापस "SPRN_BESCR"; अवरोध;
		हाल 800: वापस "SPRN_BESCRS"; अवरोध;
		हाल 801: वापस "SPRN_BESCRSU"; अवरोध;
		हाल 802: वापस "SPRN_BESCRR"; अवरोध;
		हाल 803: वापस "SPRN_BESCRRU"; अवरोध;
		हाल 771: वापस "SPRN_PMC1"; अवरोध;
		हाल 772: वापस "SPRN_PMC2"; अवरोध;
		हाल 773: वापस "SPRN_PMC3"; अवरोध;
		हाल 774: वापस "SPRN_PMC4"; अवरोध;
		हाल 775: वापस "SPRN_PMC5"; अवरोध;
		हाल 776: वापस "SPRN_PMC6"; अवरोध;
		हाल 780: वापस "SPRN_SIAR"; अवरोध;
		हाल 781: वापस "SPRN_SDAR"; अवरोध;
		हाल 768: वापस "SPRN_SIER"; अवरोध;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम trace_prपूर्णांक_reg(काष्ठा trace_entry *e)
अणु
	u64 *p, *reg, *value;
	अक्षर *name;

	p = (u64 *)e->data;
	reg = p++;
	value = p;

	name = trace_decode_reg(*reg);
	अगर (name)
		म_लिखो("register %-10s = 0x%016llx\n", name, *value);
	अन्यथा
		म_लिखो("register %lld = 0x%016llx\n", *reg, *value);
पूर्ण

अटल व्योम trace_prपूर्णांक_counter(काष्ठा trace_entry *e)
अणु
	u64 *value;

	value = (u64 *)e->data;
	म_लिखो("counter = %lld\n", *value);
पूर्ण

अटल व्योम trace_prपूर्णांक_string(काष्ठा trace_entry *e)
अणु
	अक्षर *str;

	str = (अक्षर *)e->data;
	माला_दो(str);
पूर्ण

#घोषणा BASE_PREFIX	2
#घोषणा PREFIX_DELTA	8

अटल व्योम trace_prपूर्णांक_entry(काष्ठा trace_entry *e, पूर्णांक seq, पूर्णांक *prefix)
अणु
	चयन (e->type) अणु
	हाल TRACE_TYPE_REG:
		trace_prपूर्णांक_header(seq, *prefix);
		trace_prपूर्णांक_reg(e);
		अवरोध;
	हाल TRACE_TYPE_COUNTER:
		trace_prपूर्णांक_header(seq, *prefix);
		trace_prपूर्णांक_counter(e);
		अवरोध;
	हाल TRACE_TYPE_STRING:
		trace_prपूर्णांक_header(seq, *prefix);
		trace_prपूर्णांक_string(e);
		अवरोध;
	हाल TRACE_TYPE_INDENT:
		trace_prपूर्णांक_header(seq, *prefix);
		माला_दो("{");
		*prefix += PREFIX_DELTA;
		अवरोध;
	हाल TRACE_TYPE_OUTDENT:
		*prefix -= PREFIX_DELTA;
		अगर (*prefix < BASE_PREFIX)
			*prefix = BASE_PREFIX;
		trace_prपूर्णांक_header(seq, *prefix);
		माला_दो("}");
		अवरोध;
	शेष:
		trace_prपूर्णांक_header(seq, *prefix);
		म_लिखो("entry @ %p type %d\n", e, e->type);
		अवरोध;
	पूर्ण
पूर्ण

व्योम trace_buffer_prपूर्णांक(काष्ठा trace_buffer *tb)
अणु
	काष्ठा trace_entry *e;
	पूर्णांक i, prefix;
	व्योम *p;

	म_लिखो("Trace buffer dump:\n");
	म_लिखो("  address  %p \n", tb);
	म_लिखो("  tail     %p\n", tb->tail);
	म_लिखो("  size     %llu\n", tb->size);
	म_लिखो("  overflow %s\n", tb->overflow ? "TRUE" : "false");
	म_लिखो("  Content:\n");

	p = tb->data;

	i = 0;
	prefix = BASE_PREFIX;

	जबतक (trace_check_bounds(tb, p) && p < tb->tail) अणु
		e = p;

		trace_prपूर्णांक_entry(e, i, &prefix);

		i++;
		p = (व्योम *)e + माप(*e) + e->length;
	पूर्ण
पूर्ण

व्योम trace_prपूर्णांक_location(काष्ठा trace_buffer *tb)
अणु
	म_लिखो("Trace buffer 0x%llx bytes @ %p\n", tb->size, tb);
पूर्ण
