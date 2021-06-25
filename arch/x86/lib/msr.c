<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/export.h>
#समावेश <linux/percpu.h>
#समावेश <linux/preempt.h>
#समावेश <यंत्र/msr.h>
#घोषणा CREATE_TRACE_POINTS
#समावेश <यंत्र/msr-trace.h>

काष्ठा msr *msrs_alloc(व्योम)
अणु
	काष्ठा msr *msrs = शून्य;

	msrs = alloc_percpu(काष्ठा msr);
	अगर (!msrs) अणु
		pr_warn("%s: error allocating msrs\n", __func__);
		वापस शून्य;
	पूर्ण

	वापस msrs;
पूर्ण
EXPORT_SYMBOL(msrs_alloc);

व्योम msrs_मुक्त(काष्ठा msr *msrs)
अणु
	मुक्त_percpu(msrs);
पूर्ण
EXPORT_SYMBOL(msrs_मुक्त);

/**
 * Read an MSR with error handling
 *
 * @msr: MSR to पढ़ो
 * @m: value to पढ़ो पूर्णांकo
 *
 * It वापसs पढ़ो data only on success, otherwise it करोesn't change the output
 * argument @m.
 *
 */
अटल पूर्णांक msr_पढ़ो(u32 msr, काष्ठा msr *m)
अणु
	पूर्णांक err;
	u64 val;

	err = rdmsrl_safe(msr, &val);
	अगर (!err)
		m->q = val;

	वापस err;
पूर्ण

/**
 * Write an MSR with error handling
 *
 * @msr: MSR to ग_लिखो
 * @m: value to ग_लिखो
 */
अटल पूर्णांक msr_ग_लिखो(u32 msr, काष्ठा msr *m)
अणु
	वापस wrmsrl_safe(msr, m->q);
पूर्ण

अटल अंतरभूत पूर्णांक __flip_bit(u32 msr, u8 bit, bool set)
अणु
	काष्ठा msr m, m1;
	पूर्णांक err = -EINVAL;

	अगर (bit > 63)
		वापस err;

	err = msr_पढ़ो(msr, &m);
	अगर (err)
		वापस err;

	m1 = m;
	अगर (set)
		m1.q |=  BIT_64(bit);
	अन्यथा
		m1.q &= ~BIT_64(bit);

	अगर (m1.q == m.q)
		वापस 0;

	err = msr_ग_लिखो(msr, &m1);
	अगर (err)
		वापस err;

	वापस 1;
पूर्ण

/**
 * Set @bit in a MSR @msr.
 *
 * Retval:
 * < 0: An error was encountered.
 * = 0: Bit was alपढ़ोy set.
 * > 0: Hardware accepted the MSR ग_लिखो.
 */
पूर्णांक msr_set_bit(u32 msr, u8 bit)
अणु
	वापस __flip_bit(msr, bit, true);
पूर्ण

/**
 * Clear @bit in a MSR @msr.
 *
 * Retval:
 * < 0: An error was encountered.
 * = 0: Bit was alपढ़ोy cleared.
 * > 0: Hardware accepted the MSR ग_लिखो.
 */
पूर्णांक msr_clear_bit(u32 msr, u8 bit)
अणु
	वापस __flip_bit(msr, bit, false);
पूर्ण

#अगर_घोषित CONFIG_TRACEPOINTS
व्योम करो_trace_ग_लिखो_msr(अचिन्हित पूर्णांक msr, u64 val, पूर्णांक failed)
अणु
	trace_ग_लिखो_msr(msr, val, failed);
पूर्ण
EXPORT_SYMBOL(करो_trace_ग_लिखो_msr);
EXPORT_TRACEPOINT_SYMBOL(ग_लिखो_msr);

व्योम करो_trace_पढ़ो_msr(अचिन्हित पूर्णांक msr, u64 val, पूर्णांक failed)
अणु
	trace_पढ़ो_msr(msr, val, failed);
पूर्ण
EXPORT_SYMBOL(करो_trace_पढ़ो_msr);
EXPORT_TRACEPOINT_SYMBOL(पढ़ो_msr);

व्योम करो_trace_rdpmc(अचिन्हित counter, u64 val, पूर्णांक failed)
अणु
	trace_rdpmc(counter, val, failed);
पूर्ण
EXPORT_SYMBOL(करो_trace_rdpmc);
EXPORT_TRACEPOINT_SYMBOL(rdpmc);

#पूर्ण_अगर
