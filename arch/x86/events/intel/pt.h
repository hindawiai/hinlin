<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Intel(R) Processor Trace PMU driver क्रम perf
 * Copyright (c) 2013-2014, Intel Corporation.
 *
 * Intel PT is specअगरied in the Intel Architecture Inकाष्ठाion Set Extensions
 * Programming Reference:
 * http://software.पूर्णांकel.com/en-us/पूर्णांकel-isa-extensions
 */

#अगर_अघोषित __INTEL_PT_H__
#घोषणा __INTEL_PT_H__

/*
 * Single-entry ToPA: when this बंद to region boundary, चयन
 * buffers to aव्योम losing data.
 */
#घोषणा TOPA_PMI_MARGIN 512

#घोषणा TOPA_SHIFT 12

अटल अंतरभूत अचिन्हित पूर्णांक sizes(अचिन्हित पूर्णांक tsz)
अणु
	वापस 1 << (tsz + TOPA_SHIFT);
पूर्ण;

काष्ठा topa_entry अणु
	u64	end	: 1;
	u64	rsvd0	: 1;
	u64	पूर्णांकr	: 1;
	u64	rsvd1	: 1;
	u64	stop	: 1;
	u64	rsvd2	: 1;
	u64	size	: 4;
	u64	rsvd3	: 2;
	u64	base	: 36;
	u64	rsvd4	: 16;
पूर्ण;

/* TSC to Core Crystal Clock Ratio */
#घोषणा CPUID_TSC_LEAF		0x15

काष्ठा pt_pmu अणु
	काष्ठा pmu		pmu;
	u32			caps[PT_CPUID_REGS_NUM * PT_CPUID_LEAVES];
	bool			vmx;
	bool			branch_en_always_on;
	अचिन्हित दीर्घ		max_nonturbo_ratio;
	अचिन्हित पूर्णांक		tsc_art_num;
	अचिन्हित पूर्णांक		tsc_art_den;
पूर्ण;

/**
 * काष्ठा pt_buffer - buffer configuration; one buffer per task_काष्ठा or
 *		cpu, depending on perf event configuration
 * @tables:	list of ToPA tables in this buffer
 * @first:	लघुhand क्रम first topa table
 * @last:	लघुhand क्रम last topa table
 * @cur:	current topa table
 * @nr_pages:	buffer size in pages
 * @cur_idx:	current output region's index within @cur table
 * @output_off:	offset within the current output region
 * @data_size:	running total of the amount of data in this buffer
 * @lost:	अगर data was lost/truncated
 * @head:	logical ग_लिखो offset inside the buffer
 * @snapshot:	अगर this is क्रम a snapshot/overग_लिखो counter
 * @single:	use Single Range Output instead of ToPA
 * @stop_pos:	STOP topa entry index
 * @पूर्णांकr_pos:	INT topa entry index
 * @stop_te:	STOP topa entry poपूर्णांकer
 * @पूर्णांकr_te:	INT topa entry poपूर्णांकer
 * @data_pages:	array of pages from perf
 * @topa_index:	table of topa entries indexed by page offset
 */
काष्ठा pt_buffer अणु
	काष्ठा list_head	tables;
	काष्ठा topa		*first, *last, *cur;
	अचिन्हित पूर्णांक		cur_idx;
	माप_प्रकार			output_off;
	अचिन्हित दीर्घ		nr_pages;
	local_t			data_size;
	local64_t		head;
	bool			snapshot;
	bool			single;
	दीर्घ			stop_pos, पूर्णांकr_pos;
	काष्ठा topa_entry	*stop_te, *पूर्णांकr_te;
	व्योम			**data_pages;
पूर्ण;

#घोषणा PT_FILTERS_NUM	4

/**
 * काष्ठा pt_filter - IP range filter configuration
 * @msr_a:	range start, goes to RTIT_ADDRn_A
 * @msr_b:	range end, goes to RTIT_ADDRn_B
 * @config:	4-bit field in RTIT_CTL
 */
काष्ठा pt_filter अणु
	अचिन्हित दीर्घ	msr_a;
	अचिन्हित दीर्घ	msr_b;
	अचिन्हित दीर्घ	config;
पूर्ण;

/**
 * काष्ठा pt_filters - IP range filtering context
 * @filter:	filters defined क्रम this context
 * @nr_filters:	number of defined filters in the @filter array
 */
काष्ठा pt_filters अणु
	काष्ठा pt_filter	filter[PT_FILTERS_NUM];
	अचिन्हित पूर्णांक		nr_filters;
पूर्ण;

/**
 * काष्ठा pt - per-cpu pt context
 * @handle:		perf output handle
 * @filters:		last configured filters
 * @handle_nmi:		करो handle PT PMI on this cpu, there's an active event
 * @vmx_on:		1 अगर VMX is ON on this cpu
 * @output_base:	cached RTIT_OUTPUT_BASE MSR value
 * @output_mask:	cached RTIT_OUTPUT_MASK MSR value
 */
काष्ठा pt अणु
	काष्ठा perf_output_handle handle;
	काष्ठा pt_filters	filters;
	पूर्णांक			handle_nmi;
	पूर्णांक			vmx_on;
	u64			output_base;
	u64			output_mask;
पूर्ण;

#पूर्ण_अगर /* __INTEL_PT_H__ */
