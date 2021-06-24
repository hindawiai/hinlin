<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright(C) 2015 Linaro Limited. All rights reserved.
 * Author: Mathieu Poirier <mathieu.poirier@linaro.org>
 */

#अगर_अघोषित INCLUDE__UTIL_PERF_CS_ETM_H__
#घोषणा INCLUDE__UTIL_PERF_CS_ETM_H__

#समावेश "util/event.h"
#समावेश <linux/bits.h>

काष्ठा perf_session;

/*
 * Versioning header in हाल things need to change in the future.  That way
 * decoding of old snapshot is still possible.
 */
क्रमागत अणु
	/* Starting with 0x0 */
	CS_HEADER_VERSION,
	/* PMU->type (32 bit), total # of CPUs (32 bit) */
	CS_PMU_TYPE_CPUS,
	CS_ETM_SNAPSHOT,
	CS_HEADER_VERSION_MAX,
पूर्ण;

/*
 * Update the version क्रम new क्रमmat.
 *
 * New version 1 क्रमmat adds a param count to the per cpu metadata.
 * This allows easy adding of new metadata parameters.
 * Requires that new params always added after current ones.
 * Also allows client पढ़ोer to handle file versions that are dअगरferent by
 * checking the number of params in the file vs the number expected.
 */
#घोषणा CS_HEADER_CURRENT_VERSION 1

/* Beginning of header common to both ETMv3 and V4 */
क्रमागत अणु
	CS_ETM_MAGIC,
	CS_ETM_CPU,
	/* Number of trace config params in following ETM specअगरic block */
	CS_ETM_NR_TRC_PARAMS,
	CS_ETM_COMMON_BLK_MAX_V1,
पूर्ण;

/* ETMv3/PTM metadata */
क्रमागत अणु
	/* Dynamic, configurable parameters */
	CS_ETM_ETMCR = CS_ETM_COMMON_BLK_MAX_V1,
	CS_ETM_ETMTRACEIDR,
	/* RO, taken from sysFS */
	CS_ETM_ETMCCER,
	CS_ETM_ETMIDR,
	CS_ETM_PRIV_MAX,
पूर्ण;

/* define fixed version 0 length - allow new क्रमmat पढ़ोer to पढ़ो old files. */
#घोषणा CS_ETM_NR_TRC_PARAMS_V0 (CS_ETM_ETMIDR - CS_ETM_ETMCR + 1)

/* ETMv4 metadata */
क्रमागत अणु
	/* Dynamic, configurable parameters */
	CS_ETMV4_TRCCONFIGR = CS_ETM_COMMON_BLK_MAX_V1,
	CS_ETMV4_TRCTRACEIDR,
	/* RO, taken from sysFS */
	CS_ETMV4_TRCIDR0,
	CS_ETMV4_TRCIDR1,
	CS_ETMV4_TRCIDR2,
	CS_ETMV4_TRCIDR8,
	CS_ETMV4_TRCAUTHSTATUS,
	CS_ETMV4_PRIV_MAX,
पूर्ण;

/* define fixed version 0 length - allow new क्रमmat पढ़ोer to पढ़ो old files. */
#घोषणा CS_ETMV4_NR_TRC_PARAMS_V0 (CS_ETMV4_TRCAUTHSTATUS - CS_ETMV4_TRCCONFIGR + 1)

/*
 * ETMv3 exception encoding number:
 * See Embedded Trace Macrocell specअगरication (ARM IHI 0014Q)
 * table 7-12 Encoding of Exception[3:0] क्रम non-ARMv7-M processors.
 */
क्रमागत अणु
	CS_ETMV3_EXC_NONE = 0,
	CS_ETMV3_EXC_DEBUG_HALT = 1,
	CS_ETMV3_EXC_SMC = 2,
	CS_ETMV3_EXC_HYP = 3,
	CS_ETMV3_EXC_ASYNC_DATA_ABORT = 4,
	CS_ETMV3_EXC_JAZELLE_THUMBEE = 5,
	CS_ETMV3_EXC_PE_RESET = 8,
	CS_ETMV3_EXC_UNDEFINED_INSTR = 9,
	CS_ETMV3_EXC_SVC = 10,
	CS_ETMV3_EXC_PREFETCH_ABORT = 11,
	CS_ETMV3_EXC_DATA_FAULT = 12,
	CS_ETMV3_EXC_GENERIC = 13,
	CS_ETMV3_EXC_IRQ = 14,
	CS_ETMV3_EXC_FIQ = 15,
पूर्ण;

/*
 * ETMv4 exception encoding number:
 * See ARM Embedded Trace Macrocell Architecture Specअगरication (ARM IHI 0064D)
 * table 6-12 Possible values क्रम the TYPE field in an Exception inकाष्ठाion
 * trace packet, क्रम ARMv7-A/R and ARMv8-A/R PEs.
 */
क्रमागत अणु
	CS_ETMV4_EXC_RESET = 0,
	CS_ETMV4_EXC_DEBUG_HALT = 1,
	CS_ETMV4_EXC_CALL = 2,
	CS_ETMV4_EXC_TRAP = 3,
	CS_ETMV4_EXC_SYSTEM_ERROR = 4,
	CS_ETMV4_EXC_INST_DEBUG = 6,
	CS_ETMV4_EXC_DATA_DEBUG = 7,
	CS_ETMV4_EXC_ALIGNMENT = 10,
	CS_ETMV4_EXC_INST_FAULT = 11,
	CS_ETMV4_EXC_DATA_FAULT = 12,
	CS_ETMV4_EXC_IRQ = 14,
	CS_ETMV4_EXC_FIQ = 15,
	CS_ETMV4_EXC_END = 31,
पूर्ण;

क्रमागत cs_eपंचांग_sample_type अणु
	CS_ETM_EMPTY,
	CS_ETM_RANGE,
	CS_ETM_DISCONTINUITY,
	CS_ETM_EXCEPTION,
	CS_ETM_EXCEPTION_RET,
पूर्ण;

क्रमागत cs_eपंचांग_isa अणु
	CS_ETM_ISA_UNKNOWN,
	CS_ETM_ISA_A64,
	CS_ETM_ISA_A32,
	CS_ETM_ISA_T32,
पूर्ण;

काष्ठा cs_eपंचांग_queue;

काष्ठा cs_eपंचांग_packet अणु
	क्रमागत cs_eपंचांग_sample_type sample_type;
	क्रमागत cs_eपंचांग_isa isa;
	u64 start_addr;
	u64 end_addr;
	u32 instr_count;
	u32 last_instr_type;
	u32 last_instr_subtype;
	u32 flags;
	u32 exception_number;
	u8 last_instr_cond;
	u8 last_instr_taken_branch;
	u8 last_instr_size;
	u8 trace_chan_id;
	पूर्णांक cpu;
पूर्ण;

#घोषणा CS_ETM_PACKET_MAX_BUFFER 1024

/*
 * When working with per-thपढ़ो scenarios the process under trace can
 * be scheduled on any CPU and as such, more than one traceID may be
 * associated with the same process.  Since a traceID of '0' is illegal
 * as per the CoreSight architecture, use that specअगरic value to
 * identअगरy the queue where all packets (with any traceID) are
 * aggregated.
 */
#घोषणा CS_ETM_PER_THREAD_TRACEID 0

काष्ठा cs_eपंचांग_packet_queue अणु
	u32 packet_count;
	u32 head;
	u32 tail;
	u32 instr_count;
	u64 बारtamp;
	u64 next_बारtamp;
	काष्ठा cs_eपंचांग_packet packet_buffer[CS_ETM_PACKET_MAX_BUFFER];
पूर्ण;

#घोषणा KiB(x) ((x) * 1024)
#घोषणा MiB(x) ((x) * 1024 * 1024)

#घोषणा CS_ETM_INVAL_ADDR 0xdeadbeefdeadbeefUL

#घोषणा BMVAL(val, lsb, msb)	((val & GENMASK(msb, lsb)) >> lsb)

#घोषणा CS_ETM_HEADER_SIZE (CS_HEADER_VERSION_MAX * माप(u64))

#घोषणा __perf_cs_eपंचांगv3_magic 0x3030303030303030ULL
#घोषणा __perf_cs_eपंचांगv4_magic 0x4040404040404040ULL
#घोषणा CS_ETMV3_PRIV_SIZE (CS_ETM_PRIV_MAX * माप(u64))
#घोषणा CS_ETMV4_PRIV_SIZE (CS_ETMV4_PRIV_MAX * माप(u64))

#अगर_घोषित HAVE_CSTRACE_SUPPORT
पूर्णांक cs_eपंचांग__process_auxtrace_info(जोड़ perf_event *event,
				  काष्ठा perf_session *session);
पूर्णांक cs_eपंचांग__get_cpu(u8 trace_chan_id, पूर्णांक *cpu);
पूर्णांक cs_eपंचांग__get_pid_fmt(u8 trace_chan_id, u64 *pid_fmt);
पूर्णांक cs_eपंचांग__eपंचांगq_set_tid(काष्ठा cs_eपंचांग_queue *eपंचांगq,
			 pid_t tid, u8 trace_chan_id);
bool cs_eपंचांग__eपंचांगq_is_समयless(काष्ठा cs_eपंचांग_queue *eपंचांगq);
व्योम cs_eपंचांग__eपंचांगq_set_traceid_queue_बारtamp(काष्ठा cs_eपंचांग_queue *eपंचांगq,
					      u8 trace_chan_id);
काष्ठा cs_eपंचांग_packet_queue
*cs_eपंचांग__eपंचांगq_get_packet_queue(काष्ठा cs_eपंचांग_queue *eपंचांगq, u8 trace_chan_id);
#अन्यथा
अटल अंतरभूत पूर्णांक
cs_eपंचांग__process_auxtrace_info(जोड़ perf_event *event __maybe_unused,
			      काष्ठा perf_session *session __maybe_unused)
अणु
	वापस -1;
पूर्ण

अटल अंतरभूत पूर्णांक cs_eपंचांग__get_cpu(u8 trace_chan_id __maybe_unused,
				  पूर्णांक *cpu __maybe_unused)
अणु
	वापस -1;
पूर्ण

अटल अंतरभूत पूर्णांक cs_eपंचांग__eपंचांगq_set_tid(
				काष्ठा cs_eपंचांग_queue *eपंचांगq __maybe_unused,
				pid_t tid __maybe_unused,
				u8 trace_chan_id __maybe_unused)
अणु
	वापस -1;
पूर्ण

अटल अंतरभूत bool cs_eपंचांग__eपंचांगq_is_समयless(
				काष्ठा cs_eपंचांग_queue *eपंचांगq __maybe_unused)
अणु
	/* What अन्यथा to वापस? */
	वापस true;
पूर्ण

अटल अंतरभूत व्योम cs_eपंचांग__eपंचांगq_set_traceid_queue_बारtamp(
				काष्ठा cs_eपंचांग_queue *eपंचांगq __maybe_unused,
				u8 trace_chan_id __maybe_unused) अणुपूर्ण

अटल अंतरभूत काष्ठा cs_eपंचांग_packet_queue *cs_eपंचांग__eपंचांगq_get_packet_queue(
				काष्ठा cs_eपंचांग_queue *eपंचांगq __maybe_unused,
				u8 trace_chan_id __maybe_unused)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
