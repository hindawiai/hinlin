<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * thपढ़ो-stack.h: Synthesize a thपढ़ो's stack using call / वापस events
 * Copyright (c) 2014, Intel Corporation.
 */

#अगर_अघोषित __PERF_THREAD_STACK_H
#घोषणा __PERF_THREAD_STACK_H

#समावेश <sys/types.h>

#समावेश <linux/types.h>

काष्ठा thपढ़ो;
काष्ठा comm;
काष्ठा ip_callchain;
काष्ठा symbol;
काष्ठा dso;
काष्ठा perf_sample;
काष्ठा addr_location;
काष्ठा call_path;

/*
 * Call/Return flags.
 *
 * CALL_RETURN_NO_CALL: 'return' but no matching 'call'
 * CALL_RETURN_NO_RETURN: 'call' but no matching 'return'
 * CALL_RETURN_NON_CALL: a branch but not a 'call' to the start of a dअगरferent
 *                       symbol
 */
क्रमागत अणु
	CALL_RETURN_NO_CALL	= 1 << 0,
	CALL_RETURN_NO_RETURN	= 1 << 1,
	CALL_RETURN_NON_CALL	= 1 << 2,
पूर्ण;

/**
 * काष्ठा call_वापस - paired call/वापस inक्रमmation.
 * @thपढ़ो: thपढ़ो in which call/वापस occurred
 * @comm: comm in which call/वापस occurred
 * @cp: call path
 * @call_समय: बारtamp of call (अगर known)
 * @वापस_समय: बारtamp of वापस (अगर known)
 * @branch_count: number of branches seen between call and वापस
 * @insn_count: approx. number of inकाष्ठाions between call and वापस
 * @cyc_count: approx. number of cycles between call and वापस
 * @call_ref: बाह्यal reference to 'call' sample (e.g. db_id)
 * @वापस_ref:  बाह्यal reference to 'return' sample (e.g. db_id)
 * @db_id: id used क्रम db-export
 * @parent_db_id: id of parent call used क्रम db-export
 * @flags: Call/Return flags
 */
काष्ठा call_वापस अणु
	काष्ठा thपढ़ो *thपढ़ो;
	काष्ठा comm *comm;
	काष्ठा call_path *cp;
	u64 call_समय;
	u64 वापस_समय;
	u64 branch_count;
	u64 insn_count;
	u64 cyc_count;
	u64 call_ref;
	u64 वापस_ref;
	u64 db_id;
	u64 parent_db_id;
	u32 flags;
पूर्ण;

/**
 * काष्ठा call_वापस_processor - provides a call-back to consume call-वापस
 *                                inक्रमmation.
 * @cpr: call path root
 * @process: call-back that accepts call/वापस inक्रमmation
 * @data: anonymous data क्रम call-back
 */
काष्ठा call_वापस_processor अणु
	काष्ठा call_path_root *cpr;
	पूर्णांक (*process)(काष्ठा call_वापस *cr, u64 *parent_db_id, व्योम *data);
	व्योम *data;
पूर्ण;

पूर्णांक thपढ़ो_stack__event(काष्ठा thपढ़ो *thपढ़ो, पूर्णांक cpu, u32 flags, u64 from_ip,
			u64 to_ip, u16 insn_len, u64 trace_nr, bool callstack,
			अचिन्हित पूर्णांक br_stack_sz, bool mispred_all);
व्योम thपढ़ो_stack__set_trace_nr(काष्ठा thपढ़ो *thपढ़ो, पूर्णांक cpu, u64 trace_nr);
व्योम thपढ़ो_stack__sample(काष्ठा thपढ़ो *thपढ़ो, पूर्णांक cpu, काष्ठा ip_callchain *chain,
			  माप_प्रकार sz, u64 ip, u64 kernel_start);
व्योम thपढ़ो_stack__sample_late(काष्ठा thपढ़ो *thपढ़ो, पूर्णांक cpu,
			       काष्ठा ip_callchain *chain, माप_प्रकार sz, u64 ip,
			       u64 kernel_start);
व्योम thपढ़ो_stack__br_sample(काष्ठा thपढ़ो *thपढ़ो, पूर्णांक cpu,
			     काष्ठा branch_stack *dst, अचिन्हित पूर्णांक sz);
व्योम thपढ़ो_stack__br_sample_late(काष्ठा thपढ़ो *thपढ़ो, पूर्णांक cpu,
				  काष्ठा branch_stack *dst, अचिन्हित पूर्णांक sz,
				  u64 sample_ip, u64 kernel_start);
पूर्णांक thपढ़ो_stack__flush(काष्ठा thपढ़ो *thपढ़ो);
व्योम thपढ़ो_stack__मुक्त(काष्ठा thपढ़ो *thपढ़ो);
माप_प्रकार thपढ़ो_stack__depth(काष्ठा thपढ़ो *thपढ़ो, पूर्णांक cpu);

काष्ठा call_वापस_processor *
call_वापस_processor__new(पूर्णांक (*process)(काष्ठा call_वापस *cr, u64 *parent_db_id, व्योम *data),
			   व्योम *data);
व्योम call_वापस_processor__मुक्त(काष्ठा call_वापस_processor *crp);
पूर्णांक thपढ़ो_stack__process(काष्ठा thपढ़ो *thपढ़ो, काष्ठा comm *comm,
			  काष्ठा perf_sample *sample,
			  काष्ठा addr_location *from_al,
			  काष्ठा addr_location *to_al, u64 ref,
			  काष्ठा call_वापस_processor *crp);

#पूर्ण_अगर
