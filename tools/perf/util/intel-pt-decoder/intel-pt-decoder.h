<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * पूर्णांकel_pt_decoder.h: Intel Processor Trace support
 * Copyright (c) 2013-2014, Intel Corporation.
 */

#अगर_अघोषित INCLUDE__INTEL_PT_DECODER_H__
#घोषणा INCLUDE__INTEL_PT_DECODER_H__

#समावेश <मानक_निवेशt.h>
#समावेश <मानकघोष.स>
#समावेश <stdbool.h>

#समावेश "intel-pt-insn-decoder.h"

#घोषणा INTEL_PT_IN_TX		(1 << 0)
#घोषणा INTEL_PT_ABORT_TX	(1 << 1)
#घोषणा INTEL_PT_ASYNC		(1 << 2)
#घोषणा INTEL_PT_FUP_IP		(1 << 3)
#घोषणा INTEL_PT_SAMPLE_IPC	(1 << 4)

क्रमागत पूर्णांकel_pt_sample_type अणु
	INTEL_PT_BRANCH		= 1 << 0,
	INTEL_PT_INSTRUCTION	= 1 << 1,
	INTEL_PT_TRANSACTION	= 1 << 2,
	INTEL_PT_PTW		= 1 << 3,
	INTEL_PT_MWAIT_OP	= 1 << 4,
	INTEL_PT_PWR_ENTRY	= 1 << 5,
	INTEL_PT_EX_STOP	= 1 << 6,
	INTEL_PT_PWR_EXIT	= 1 << 7,
	INTEL_PT_CBR_CHG	= 1 << 8,
	INTEL_PT_TRACE_BEGIN	= 1 << 9,
	INTEL_PT_TRACE_END	= 1 << 10,
	INTEL_PT_BLK_ITEMS	= 1 << 11,
	INTEL_PT_PSB_EVT	= 1 << 12,
पूर्ण;

क्रमागत पूर्णांकel_pt_period_type अणु
	INTEL_PT_PERIOD_NONE,
	INTEL_PT_PERIOD_INSTRUCTIONS,
	INTEL_PT_PERIOD_TICKS,
	INTEL_PT_PERIOD_MTC,
पूर्ण;

क्रमागत अणु
	INTEL_PT_ERR_NOMEM = 1,
	INTEL_PT_ERR_INTERN,
	INTEL_PT_ERR_BADPKT,
	INTEL_PT_ERR_NODATA,
	INTEL_PT_ERR_NOINSN,
	INTEL_PT_ERR_MISMAT,
	INTEL_PT_ERR_OVR,
	INTEL_PT_ERR_LOST,
	INTEL_PT_ERR_UNK,
	INTEL_PT_ERR_NELOOP,
	INTEL_PT_ERR_MAX,
पूर्ण;

क्रमागत पूर्णांकel_pt_param_flags अणु
	/*
	 * FUP packet can contain next linear inकाष्ठाion poपूर्णांकer instead of
	 * current linear inकाष्ठाion poपूर्णांकer.
	 */
	INTEL_PT_FUP_WITH_NLIP	= 1 << 0,
पूर्ण;

क्रमागत पूर्णांकel_pt_blk_type अणु
	INTEL_PT_GP_REGS	= 1,
	INTEL_PT_PEBS_BASIC	= 4,
	INTEL_PT_PEBS_MEM	= 5,
	INTEL_PT_LBR_0		= 8,
	INTEL_PT_LBR_1		= 9,
	INTEL_PT_LBR_2		= 10,
	INTEL_PT_XMM		= 16,
	INTEL_PT_BLK_TYPE_MAX
पूर्ण;

/*
 * The block type numbers are not sequential but here they are given sequential
 * positions to aव्योम wasting space क्रम array placement.
 */
क्रमागत पूर्णांकel_pt_blk_type_pos अणु
	INTEL_PT_GP_REGS_POS,
	INTEL_PT_PEBS_BASIC_POS,
	INTEL_PT_PEBS_MEM_POS,
	INTEL_PT_LBR_0_POS,
	INTEL_PT_LBR_1_POS,
	INTEL_PT_LBR_2_POS,
	INTEL_PT_XMM_POS,
	INTEL_PT_BLK_TYPE_CNT
पूर्ण;

/* Get the array position क्रम a block type */
अटल अंतरभूत पूर्णांक पूर्णांकel_pt_blk_type_pos(क्रमागत पूर्णांकel_pt_blk_type blk_type)
अणु
#घोषणा BLK_TYPE(bt) [INTEL_PT_##bt] = INTEL_PT_##bt##_POS + 1
	स्थिर पूर्णांक map[INTEL_PT_BLK_TYPE_MAX] = अणु
		BLK_TYPE(GP_REGS),
		BLK_TYPE(PEBS_BASIC),
		BLK_TYPE(PEBS_MEM),
		BLK_TYPE(LBR_0),
		BLK_TYPE(LBR_1),
		BLK_TYPE(LBR_2),
		BLK_TYPE(XMM),
	पूर्ण;
#अघोषित BLK_TYPE

	वापस blk_type < INTEL_PT_BLK_TYPE_MAX ? map[blk_type] - 1 : -1;
पूर्ण

#घोषणा INTEL_PT_BLK_ITEM_ID_CNT	32

/*
 * Use जोड़s so that the block items can be accessed by name or by array index.
 * There is an array of 32-bit masks क्रम each block type, which indicate which
 * values are present. Then arrays of 32 64-bit values क्रम each block type.
 */
काष्ठा पूर्णांकel_pt_blk_items अणु
	जोड़ अणु
		uपूर्णांक32_t mask[INTEL_PT_BLK_TYPE_CNT];
		काष्ठा अणु
			uपूर्णांक32_t has_rflags:1;
			uपूर्णांक32_t has_rip:1;
			uपूर्णांक32_t has_rax:1;
			uपूर्णांक32_t has_rcx:1;
			uपूर्णांक32_t has_rdx:1;
			uपूर्णांक32_t has_rbx:1;
			uपूर्णांक32_t has_rsp:1;
			uपूर्णांक32_t has_rbp:1;
			uपूर्णांक32_t has_rsi:1;
			uपूर्णांक32_t has_rdi:1;
			uपूर्णांक32_t has_r8:1;
			uपूर्णांक32_t has_r9:1;
			uपूर्णांक32_t has_r10:1;
			uपूर्णांक32_t has_r11:1;
			uपूर्णांक32_t has_r12:1;
			uपूर्णांक32_t has_r13:1;
			uपूर्णांक32_t has_r14:1;
			uपूर्णांक32_t has_r15:1;
			uपूर्णांक32_t has_unused_0:14;
			uपूर्णांक32_t has_ip:1;
			uपूर्णांक32_t has_applicable_counters:1;
			uपूर्णांक32_t has_बारtamp:1;
			uपूर्णांक32_t has_unused_1:29;
			uपूर्णांक32_t has_mem_access_address:1;
			uपूर्णांक32_t has_mem_aux_info:1;
			uपूर्णांक32_t has_mem_access_latency:1;
			uपूर्णांक32_t has_tsx_aux_info:1;
			uपूर्णांक32_t has_unused_2:28;
			uपूर्णांक32_t has_lbr_0;
			uपूर्णांक32_t has_lbr_1;
			uपूर्णांक32_t has_lbr_2;
			uपूर्णांक32_t has_xmm;
		पूर्ण;
	पूर्ण;
	जोड़ अणु
		uपूर्णांक64_t val[INTEL_PT_BLK_TYPE_CNT][INTEL_PT_BLK_ITEM_ID_CNT];
		काष्ठा अणु
			काष्ठा अणु
				uपूर्णांक64_t rflags;
				uपूर्णांक64_t rip;
				uपूर्णांक64_t rax;
				uपूर्णांक64_t rcx;
				uपूर्णांक64_t rdx;
				uपूर्णांक64_t rbx;
				uपूर्णांक64_t rsp;
				uपूर्णांक64_t rbp;
				uपूर्णांक64_t rsi;
				uपूर्णांक64_t rdi;
				uपूर्णांक64_t r8;
				uपूर्णांक64_t r9;
				uपूर्णांक64_t r10;
				uपूर्णांक64_t r11;
				uपूर्णांक64_t r12;
				uपूर्णांक64_t r13;
				uपूर्णांक64_t r14;
				uपूर्णांक64_t r15;
				uपूर्णांक64_t unused_0[INTEL_PT_BLK_ITEM_ID_CNT - 18];
			पूर्ण;
			काष्ठा अणु
				uपूर्णांक64_t ip;
				uपूर्णांक64_t applicable_counters;
				uपूर्णांक64_t बारtamp;
				uपूर्णांक64_t unused_1[INTEL_PT_BLK_ITEM_ID_CNT - 3];
			पूर्ण;
			काष्ठा अणु
				uपूर्णांक64_t mem_access_address;
				uपूर्णांक64_t mem_aux_info;
				uपूर्णांक64_t mem_access_latency;
				uपूर्णांक64_t tsx_aux_info;
				uपूर्णांक64_t unused_2[INTEL_PT_BLK_ITEM_ID_CNT - 4];
			पूर्ण;
			uपूर्णांक64_t lbr_0[INTEL_PT_BLK_ITEM_ID_CNT];
			uपूर्णांक64_t lbr_1[INTEL_PT_BLK_ITEM_ID_CNT];
			uपूर्णांक64_t lbr_2[INTEL_PT_BLK_ITEM_ID_CNT];
			uपूर्णांक64_t xmm[INTEL_PT_BLK_ITEM_ID_CNT];
		पूर्ण;
	पूर्ण;
	bool is_32_bit;
पूर्ण;

काष्ठा पूर्णांकel_pt_state अणु
	क्रमागत पूर्णांकel_pt_sample_type type;
	bool from_nr;
	bool to_nr;
	पूर्णांक err;
	uपूर्णांक64_t from_ip;
	uपूर्णांक64_t to_ip;
	uपूर्णांक64_t tot_insn_cnt;
	uपूर्णांक64_t tot_cyc_cnt;
	uपूर्णांक64_t बारtamp;
	uपूर्णांक64_t est_बारtamp;
	uपूर्णांक64_t trace_nr;
	uपूर्णांक64_t ptw_payload;
	uपूर्णांक64_t mरुको_payload;
	uपूर्णांक64_t pwre_payload;
	uपूर्णांक64_t pwrx_payload;
	uपूर्णांक64_t cbr_payload;
	uपूर्णांक64_t psb_offset;
	uपूर्णांक32_t cbr;
	uपूर्णांक32_t flags;
	क्रमागत पूर्णांकel_pt_insn_op insn_op;
	पूर्णांक insn_len;
	अक्षर insn[INTEL_PT_INSN_BUF_SZ];
	काष्ठा पूर्णांकel_pt_blk_items items;
पूर्ण;

काष्ठा पूर्णांकel_pt_insn;

काष्ठा पूर्णांकel_pt_buffer अणु
	स्थिर अचिन्हित अक्षर *buf;
	माप_प्रकार len;
	bool consecutive;
	uपूर्णांक64_t ref_बारtamp;
	uपूर्णांक64_t trace_nr;
पूर्ण;

प्रकार पूर्णांक (*पूर्णांकel_pt_lookahead_cb_t)(काष्ठा पूर्णांकel_pt_buffer *, व्योम *);

काष्ठा पूर्णांकel_pt_params अणु
	पूर्णांक (*get_trace)(काष्ठा पूर्णांकel_pt_buffer *buffer, व्योम *data);
	पूर्णांक (*walk_insn)(काष्ठा पूर्णांकel_pt_insn *पूर्णांकel_pt_insn,
			 uपूर्णांक64_t *insn_cnt_ptr, uपूर्णांक64_t *ip, uपूर्णांक64_t to_ip,
			 uपूर्णांक64_t max_insn_cnt, व्योम *data);
	bool (*pgd_ip)(uपूर्णांक64_t ip, व्योम *data);
	पूर्णांक (*lookahead)(व्योम *data, पूर्णांकel_pt_lookahead_cb_t cb, व्योम *cb_data);
	व्योम *data;
	bool वापस_compression;
	bool branch_enable;
	uपूर्णांक64_t ctl;
	uपूर्णांक64_t period;
	क्रमागत पूर्णांकel_pt_period_type period_type;
	अचिन्हित max_non_turbo_ratio;
	अचिन्हित पूर्णांक mtc_period;
	uपूर्णांक32_t tsc_ctc_ratio_n;
	uपूर्णांक32_t tsc_ctc_ratio_d;
	क्रमागत पूर्णांकel_pt_param_flags flags;
	अचिन्हित पूर्णांक quick;
पूर्ण;

काष्ठा पूर्णांकel_pt_decoder;

काष्ठा पूर्णांकel_pt_decoder *पूर्णांकel_pt_decoder_new(काष्ठा पूर्णांकel_pt_params *params);
व्योम पूर्णांकel_pt_decoder_मुक्त(काष्ठा पूर्णांकel_pt_decoder *decoder);

स्थिर काष्ठा पूर्णांकel_pt_state *पूर्णांकel_pt_decode(काष्ठा पूर्णांकel_pt_decoder *decoder);

पूर्णांक पूर्णांकel_pt_fast_क्रमward(काष्ठा पूर्णांकel_pt_decoder *decoder, uपूर्णांक64_t बारtamp);

अचिन्हित अक्षर *पूर्णांकel_pt_find_overlap(अचिन्हित अक्षर *buf_a, माप_प्रकार len_a,
				     अचिन्हित अक्षर *buf_b, माप_प्रकार len_b,
				     bool have_tsc, bool *consecutive);

पूर्णांक पूर्णांकel_pt__म_त्रुटि(पूर्णांक code, अक्षर *buf, माप_प्रकार buflen);

#पूर्ण_अगर
