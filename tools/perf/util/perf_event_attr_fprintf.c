<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <पूर्णांकtypes.h>
#समावेश <मानकपन.स>
#समावेश <stdbool.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/perf_event.h>
#समावेश "util/evsel_fprintf.h"

काष्ठा bit_names अणु
	पूर्णांक bit;
	स्थिर अक्षर *name;
पूर्ण;

अटल व्योम __p_bits(अक्षर *buf, माप_प्रकार size, u64 value, काष्ठा bit_names *bits)
अणु
	bool first_bit = true;
	पूर्णांक i = 0;

	करो अणु
		अगर (value & bits[i].bit) अणु
			buf += scnम_लिखो(buf, size, "%s%s", first_bit ? "" : "|", bits[i].name);
			first_bit = false;
		पूर्ण
	पूर्ण जबतक (bits[++i].name != शून्य);
पूर्ण

अटल व्योम __p_sample_type(अक्षर *buf, माप_प्रकार size, u64 value)
अणु
#घोषणा bit_name(n) अणु PERF_SAMPLE_##n, #n पूर्ण
	काष्ठा bit_names bits[] = अणु
		bit_name(IP), bit_name(TID), bit_name(TIME), bit_name(ADDR),
		bit_name(READ), bit_name(CALLCHAIN), bit_name(ID), bit_name(CPU),
		bit_name(PERIOD), bit_name(STREAM_ID), bit_name(RAW),
		bit_name(BRANCH_STACK), bit_name(REGS_USER), bit_name(STACK_USER),
		bit_name(IDENTIFIER), bit_name(REGS_INTR), bit_name(DATA_SRC),
		bit_name(WEIGHT), bit_name(PHYS_ADDR), bit_name(AUX),
		bit_name(CGROUP), bit_name(DATA_PAGE_SIZE), bit_name(CODE_PAGE_SIZE),
		bit_name(WEIGHT_STRUCT),
		अणु .name = शून्य, पूर्ण
	पूर्ण;
#अघोषित bit_name
	__p_bits(buf, size, value, bits);
पूर्ण

अटल व्योम __p_branch_sample_type(अक्षर *buf, माप_प्रकार size, u64 value)
अणु
#घोषणा bit_name(n) अणु PERF_SAMPLE_BRANCH_##n, #n पूर्ण
	काष्ठा bit_names bits[] = अणु
		bit_name(USER), bit_name(KERNEL), bit_name(HV), bit_name(ANY),
		bit_name(ANY_CALL), bit_name(ANY_RETURN), bit_name(IND_CALL),
		bit_name(ABORT_TX), bit_name(IN_TX), bit_name(NO_TX),
		bit_name(COND), bit_name(CALL_STACK), bit_name(IND_JUMP),
		bit_name(CALL), bit_name(NO_FLAGS), bit_name(NO_CYCLES),
		bit_name(HW_INDEX),
		अणु .name = शून्य, पूर्ण
	पूर्ण;
#अघोषित bit_name
	__p_bits(buf, size, value, bits);
पूर्ण

अटल व्योम __p_पढ़ो_क्रमmat(अक्षर *buf, माप_प्रकार size, u64 value)
अणु
#घोषणा bit_name(n) अणु PERF_FORMAT_##n, #n पूर्ण
	काष्ठा bit_names bits[] = अणु
		bit_name(TOTAL_TIME_ENABLED), bit_name(TOTAL_TIME_RUNNING),
		bit_name(ID), bit_name(GROUP),
		अणु .name = शून्य, पूर्ण
	पूर्ण;
#अघोषित bit_name
	__p_bits(buf, size, value, bits);
पूर्ण

#घोषणा BUF_SIZE		1024

#घोषणा p_hex(val)		snम_लिखो(buf, BUF_SIZE, "%#"PRIx64, (uपूर्णांक64_t)(val))
#घोषणा p_अचिन्हित(val)		snम_लिखो(buf, BUF_SIZE, "%"PRIu64, (uपूर्णांक64_t)(val))
#घोषणा p_चिन्हित(val)		snम_लिखो(buf, BUF_SIZE, "%"PRId64, (पूर्णांक64_t)(val))
#घोषणा p_sample_type(val)	__p_sample_type(buf, BUF_SIZE, val)
#घोषणा p_branch_sample_type(val) __p_branch_sample_type(buf, BUF_SIZE, val)
#घोषणा p_पढ़ो_क्रमmat(val)	__p_पढ़ो_क्रमmat(buf, BUF_SIZE, val)

#घोषणा PRINT_ATTRn(_n, _f, _p)				\
करो अणु							\
	अगर (attr->_f) अणु					\
		_p(attr->_f);				\
		ret += attr__ख_लिखो(fp, _n, buf, priv);\
	पूर्ण						\
पूर्ण जबतक (0)

#घोषणा PRINT_ATTRf(_f, _p)	PRINT_ATTRn(#_f, _f, _p)

पूर्णांक perf_event_attr__ख_लिखो(खाता *fp, काष्ठा perf_event_attr *attr,
			     attr__ख_लिखो_f attr__ख_लिखो, व्योम *priv)
अणु
	अक्षर buf[BUF_SIZE];
	पूर्णांक ret = 0;

	PRINT_ATTRf(type, p_अचिन्हित);
	PRINT_ATTRf(size, p_अचिन्हित);
	PRINT_ATTRf(config, p_hex);
	PRINT_ATTRn("{ sample_period, sample_freq }", sample_period, p_अचिन्हित);
	PRINT_ATTRf(sample_type, p_sample_type);
	PRINT_ATTRf(पढ़ो_क्रमmat, p_पढ़ो_क्रमmat);

	PRINT_ATTRf(disabled, p_अचिन्हित);
	PRINT_ATTRf(inherit, p_अचिन्हित);
	PRINT_ATTRf(pinned, p_अचिन्हित);
	PRINT_ATTRf(exclusive, p_अचिन्हित);
	PRINT_ATTRf(exclude_user, p_अचिन्हित);
	PRINT_ATTRf(exclude_kernel, p_अचिन्हित);
	PRINT_ATTRf(exclude_hv, p_अचिन्हित);
	PRINT_ATTRf(exclude_idle, p_अचिन्हित);
	PRINT_ATTRf(mmap, p_अचिन्हित);
	PRINT_ATTRf(comm, p_अचिन्हित);
	PRINT_ATTRf(freq, p_अचिन्हित);
	PRINT_ATTRf(inherit_stat, p_अचिन्हित);
	PRINT_ATTRf(enable_on_exec, p_अचिन्हित);
	PRINT_ATTRf(task, p_अचिन्हित);
	PRINT_ATTRf(watermark, p_अचिन्हित);
	PRINT_ATTRf(precise_ip, p_अचिन्हित);
	PRINT_ATTRf(mmap_data, p_अचिन्हित);
	PRINT_ATTRf(sample_id_all, p_अचिन्हित);
	PRINT_ATTRf(exclude_host, p_अचिन्हित);
	PRINT_ATTRf(exclude_guest, p_अचिन्हित);
	PRINT_ATTRf(exclude_callchain_kernel, p_अचिन्हित);
	PRINT_ATTRf(exclude_callchain_user, p_अचिन्हित);
	PRINT_ATTRf(mmap2, p_अचिन्हित);
	PRINT_ATTRf(comm_exec, p_अचिन्हित);
	PRINT_ATTRf(use_घड़ीid, p_अचिन्हित);
	PRINT_ATTRf(context_चयन, p_अचिन्हित);
	PRINT_ATTRf(ग_लिखो_backward, p_अचिन्हित);
	PRINT_ATTRf(namespaces, p_अचिन्हित);
	PRINT_ATTRf(ksymbol, p_अचिन्हित);
	PRINT_ATTRf(bpf_event, p_अचिन्हित);
	PRINT_ATTRf(aux_output, p_अचिन्हित);
	PRINT_ATTRf(cgroup, p_अचिन्हित);
	PRINT_ATTRf(text_poke, p_अचिन्हित);
	PRINT_ATTRf(build_id, p_अचिन्हित);

	PRINT_ATTRn("{ wakeup_events, wakeup_watermark }", wakeup_events, p_अचिन्हित);
	PRINT_ATTRf(bp_type, p_अचिन्हित);
	PRINT_ATTRn("{ bp_addr, config1 }", bp_addr, p_hex);
	PRINT_ATTRn("{ bp_len, config2 }", bp_len, p_hex);
	PRINT_ATTRf(branch_sample_type, p_branch_sample_type);
	PRINT_ATTRf(sample_regs_user, p_hex);
	PRINT_ATTRf(sample_stack_user, p_अचिन्हित);
	PRINT_ATTRf(घड़ीid, p_चिन्हित);
	PRINT_ATTRf(sample_regs_पूर्णांकr, p_hex);
	PRINT_ATTRf(aux_watermark, p_अचिन्हित);
	PRINT_ATTRf(sample_max_stack, p_अचिन्हित);
	PRINT_ATTRf(aux_sample_size, p_अचिन्हित);
	PRINT_ATTRf(text_poke, p_अचिन्हित);

	वापस ret;
पूर्ण
