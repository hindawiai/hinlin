<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * पूर्णांकel_pt_decoder.c: Intel Processor Trace support
 * Copyright (c) 2013-2014, Intel Corporation.
 */

#अगर_अघोषित _GNU_SOURCE
#घोषणा _GNU_SOURCE
#पूर्ण_अगर
#समावेश <मानककोष.स>
#समावेश <stdbool.h>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <मानक_निवेशt.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <linux/compiler.h>
#समावेश <linux/माला.स>
#समावेश <linux/zभाग.स>

#समावेश "../auxtrace.h"

#समावेश "intel-pt-insn-decoder.h"
#समावेश "intel-pt-pkt-decoder.h"
#समावेश "intel-pt-decoder.h"
#समावेश "intel-pt-log.h"

#घोषणा BITULL(x) (1ULL << (x))

/* IA32_RTIT_CTL MSR bits */
#घोषणा INTEL_PT_CYC_ENABLE		BITULL(1)
#घोषणा INTEL_PT_CYC_THRESHOLD		(BITULL(22) | BITULL(21) | BITULL(20) | BITULL(19))
#घोषणा INTEL_PT_CYC_THRESHOLD_SHIFT	19

#घोषणा INTEL_PT_BLK_SIZE 1024

#घोषणा BIT63 (((uपूर्णांक64_t)1 << 63))

#घोषणा INTEL_PT_RETURN 1

/* Maximum number of loops with no packets consumed i.e. stuck in a loop */
#घोषणा INTEL_PT_MAX_LOOPS 10000

काष्ठा पूर्णांकel_pt_blk अणु
	काष्ठा पूर्णांकel_pt_blk *prev;
	uपूर्णांक64_t ip[INTEL_PT_BLK_SIZE];
पूर्ण;

काष्ठा पूर्णांकel_pt_stack अणु
	काष्ठा पूर्णांकel_pt_blk *blk;
	काष्ठा पूर्णांकel_pt_blk *spare;
	पूर्णांक pos;
पूर्ण;

क्रमागत पूर्णांकel_pt_pkt_state अणु
	INTEL_PT_STATE_NO_PSB,
	INTEL_PT_STATE_NO_IP,
	INTEL_PT_STATE_ERR_RESYNC,
	INTEL_PT_STATE_IN_SYNC,
	INTEL_PT_STATE_TNT_CONT,
	INTEL_PT_STATE_TNT,
	INTEL_PT_STATE_TIP,
	INTEL_PT_STATE_TIP_PGD,
	INTEL_PT_STATE_FUP,
	INTEL_PT_STATE_FUP_NO_TIP,
	INTEL_PT_STATE_FUP_IN_PSB,
	INTEL_PT_STATE_RESAMPLE,
पूर्ण;

अटल अंतरभूत bool पूर्णांकel_pt_sample_समय(क्रमागत पूर्णांकel_pt_pkt_state pkt_state)
अणु
	चयन (pkt_state) अणु
	हाल INTEL_PT_STATE_NO_PSB:
	हाल INTEL_PT_STATE_NO_IP:
	हाल INTEL_PT_STATE_ERR_RESYNC:
	हाल INTEL_PT_STATE_IN_SYNC:
	हाल INTEL_PT_STATE_TNT_CONT:
	हाल INTEL_PT_STATE_RESAMPLE:
		वापस true;
	हाल INTEL_PT_STATE_TNT:
	हाल INTEL_PT_STATE_TIP:
	हाल INTEL_PT_STATE_TIP_PGD:
	हाल INTEL_PT_STATE_FUP:
	हाल INTEL_PT_STATE_FUP_NO_TIP:
	हाल INTEL_PT_STATE_FUP_IN_PSB:
		वापस false;
	शेष:
		वापस true;
	पूर्ण;
पूर्ण

#अगर_घोषित INTEL_PT_STRICT
#घोषणा INTEL_PT_STATE_ERR1	INTEL_PT_STATE_NO_PSB
#घोषणा INTEL_PT_STATE_ERR2	INTEL_PT_STATE_NO_PSB
#घोषणा INTEL_PT_STATE_ERR3	INTEL_PT_STATE_NO_PSB
#घोषणा INTEL_PT_STATE_ERR4	INTEL_PT_STATE_NO_PSB
#अन्यथा
#घोषणा INTEL_PT_STATE_ERR1	(decoder->pkt_state)
#घोषणा INTEL_PT_STATE_ERR2	INTEL_PT_STATE_NO_IP
#घोषणा INTEL_PT_STATE_ERR3	INTEL_PT_STATE_ERR_RESYNC
#घोषणा INTEL_PT_STATE_ERR4	INTEL_PT_STATE_IN_SYNC
#पूर्ण_अगर

काष्ठा पूर्णांकel_pt_decoder अणु
	पूर्णांक (*get_trace)(काष्ठा पूर्णांकel_pt_buffer *buffer, व्योम *data);
	पूर्णांक (*walk_insn)(काष्ठा पूर्णांकel_pt_insn *पूर्णांकel_pt_insn,
			 uपूर्णांक64_t *insn_cnt_ptr, uपूर्णांक64_t *ip, uपूर्णांक64_t to_ip,
			 uपूर्णांक64_t max_insn_cnt, व्योम *data);
	bool (*pgd_ip)(uपूर्णांक64_t ip, व्योम *data);
	पूर्णांक (*lookahead)(व्योम *data, पूर्णांकel_pt_lookahead_cb_t cb, व्योम *cb_data);
	व्योम *data;
	काष्ठा पूर्णांकel_pt_state state;
	स्थिर अचिन्हित अक्षर *buf;
	माप_प्रकार len;
	bool वापस_compression;
	bool branch_enable;
	bool mtc_insn;
	bool pge;
	bool have_पंचांगa;
	bool have_cyc;
	bool fixup_last_mtc;
	bool have_last_ip;
	bool in_psb;
	bool hop;
	bool leap;
	bool nr;
	bool next_nr;
	क्रमागत पूर्णांकel_pt_param_flags flags;
	uपूर्णांक64_t pos;
	uपूर्णांक64_t last_ip;
	uपूर्णांक64_t ip;
	uपूर्णांक64_t pip_payload;
	uपूर्णांक64_t बारtamp;
	uपूर्णांक64_t tsc_बारtamp;
	uपूर्णांक64_t ref_बारtamp;
	uपूर्णांक64_t buf_बारtamp;
	uपूर्णांक64_t sample_बारtamp;
	uपूर्णांक64_t ret_addr;
	uपूर्णांक64_t ctc_बारtamp;
	uपूर्णांक64_t ctc_delta;
	uपूर्णांक64_t cycle_cnt;
	uपूर्णांक64_t cyc_ref_बारtamp;
	uपूर्णांक32_t last_mtc;
	uपूर्णांक32_t tsc_ctc_ratio_n;
	uपूर्णांक32_t tsc_ctc_ratio_d;
	uपूर्णांक32_t tsc_ctc_mult;
	uपूर्णांक32_t tsc_slip;
	uपूर्णांक32_t ctc_rem_mask;
	पूर्णांक mtc_shअगरt;
	काष्ठा पूर्णांकel_pt_stack stack;
	क्रमागत पूर्णांकel_pt_pkt_state pkt_state;
	क्रमागत पूर्णांकel_pt_pkt_ctx pkt_ctx;
	क्रमागत पूर्णांकel_pt_pkt_ctx prev_pkt_ctx;
	क्रमागत पूर्णांकel_pt_blk_type blk_type;
	पूर्णांक blk_type_pos;
	काष्ठा पूर्णांकel_pt_pkt packet;
	काष्ठा पूर्णांकel_pt_pkt tnt;
	पूर्णांक pkt_step;
	पूर्णांक pkt_len;
	पूर्णांक last_packet_type;
	अचिन्हित पूर्णांक cbr;
	अचिन्हित पूर्णांक cbr_seen;
	अचिन्हित पूर्णांक max_non_turbo_ratio;
	द्विगुन max_non_turbo_ratio_fp;
	द्विगुन cbr_cyc_to_tsc;
	द्विगुन calc_cyc_to_tsc;
	bool have_calc_cyc_to_tsc;
	पूर्णांक exec_mode;
	अचिन्हित पूर्णांक insn_bytes;
	uपूर्णांक64_t period;
	क्रमागत पूर्णांकel_pt_period_type period_type;
	uपूर्णांक64_t tot_insn_cnt;
	uपूर्णांक64_t period_insn_cnt;
	uपूर्णांक64_t period_mask;
	uपूर्णांक64_t period_ticks;
	uपूर्णांक64_t last_masked_बारtamp;
	uपूर्णांक64_t tot_cyc_cnt;
	uपूर्णांक64_t sample_tot_cyc_cnt;
	uपूर्णांक64_t base_cyc_cnt;
	uपूर्णांक64_t cyc_cnt_बारtamp;
	uपूर्णांक64_t ctl;
	uपूर्णांक64_t cyc_threshold;
	द्विगुन tsc_to_cyc;
	bool continuous_period;
	bool overflow;
	bool set_fup_tx_flags;
	bool set_fup_ptw;
	bool set_fup_mरुको;
	bool set_fup_pwre;
	bool set_fup_exstop;
	bool set_fup_bep;
	bool sample_cyc;
	अचिन्हित पूर्णांक fup_tx_flags;
	अचिन्हित पूर्णांक tx_flags;
	uपूर्णांक64_t fup_ptw_payload;
	uपूर्णांक64_t fup_mरुको_payload;
	uपूर्णांक64_t fup_pwre_payload;
	uपूर्णांक64_t cbr_payload;
	uपूर्णांक64_t बारtamp_insn_cnt;
	uपूर्णांक64_t sample_insn_cnt;
	uपूर्णांक64_t stuck_ip;
	पूर्णांक no_progress;
	पूर्णांक stuck_ip_prd;
	पूर्णांक stuck_ip_cnt;
	uपूर्णांक64_t psb_ip;
	स्थिर अचिन्हित अक्षर *next_buf;
	माप_प्रकार next_len;
	अचिन्हित अक्षर temp_buf[INTEL_PT_PKT_MAX_SZ];
पूर्ण;

अटल uपूर्णांक64_t पूर्णांकel_pt_lower_घातer_of_2(uपूर्णांक64_t x)
अणु
	पूर्णांक i;

	क्रम (i = 0; x != 1; i++)
		x >>= 1;

	वापस x << i;
पूर्ण

अटल uपूर्णांक64_t पूर्णांकel_pt_cyc_threshold(uपूर्णांक64_t ctl)
अणु
	अगर (!(ctl & INTEL_PT_CYC_ENABLE))
		वापस 0;

	वापस (ctl & INTEL_PT_CYC_THRESHOLD) >> INTEL_PT_CYC_THRESHOLD_SHIFT;
पूर्ण

अटल व्योम पूर्णांकel_pt_setup_period(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	अगर (decoder->period_type == INTEL_PT_PERIOD_TICKS) अणु
		uपूर्णांक64_t period;

		period = पूर्णांकel_pt_lower_घातer_of_2(decoder->period);
		decoder->period_mask  = ~(period - 1);
		decoder->period_ticks = period;
	पूर्ण
पूर्ण

अटल uपूर्णांक64_t multभाग(uपूर्णांक64_t t, uपूर्णांक32_t n, uपूर्णांक32_t d)
अणु
	अगर (!d)
		वापस 0;
	वापस (t / d) * n + ((t % d) * n) / d;
पूर्ण

काष्ठा पूर्णांकel_pt_decoder *पूर्णांकel_pt_decoder_new(काष्ठा पूर्णांकel_pt_params *params)
अणु
	काष्ठा पूर्णांकel_pt_decoder *decoder;

	अगर (!params->get_trace || !params->walk_insn)
		वापस शून्य;

	decoder = zalloc(माप(काष्ठा पूर्णांकel_pt_decoder));
	अगर (!decoder)
		वापस शून्य;

	decoder->get_trace          = params->get_trace;
	decoder->walk_insn          = params->walk_insn;
	decoder->pgd_ip             = params->pgd_ip;
	decoder->lookahead          = params->lookahead;
	decoder->data               = params->data;
	decoder->वापस_compression = params->वापस_compression;
	decoder->branch_enable      = params->branch_enable;
	decoder->hop                = params->quick >= 1;
	decoder->leap               = params->quick >= 2;

	decoder->flags              = params->flags;

	decoder->ctl                = params->ctl;
	decoder->period             = params->period;
	decoder->period_type        = params->period_type;

	decoder->max_non_turbo_ratio    = params->max_non_turbo_ratio;
	decoder->max_non_turbo_ratio_fp = params->max_non_turbo_ratio;

	decoder->cyc_threshold = पूर्णांकel_pt_cyc_threshold(decoder->ctl);

	पूर्णांकel_pt_setup_period(decoder);

	decoder->mtc_shअगरt = params->mtc_period;
	decoder->ctc_rem_mask = (1 << decoder->mtc_shअगरt) - 1;

	decoder->tsc_ctc_ratio_n = params->tsc_ctc_ratio_n;
	decoder->tsc_ctc_ratio_d = params->tsc_ctc_ratio_d;

	अगर (!decoder->tsc_ctc_ratio_n)
		decoder->tsc_ctc_ratio_d = 0;

	अगर (decoder->tsc_ctc_ratio_d) अणु
		अगर (!(decoder->tsc_ctc_ratio_n % decoder->tsc_ctc_ratio_d))
			decoder->tsc_ctc_mult = decoder->tsc_ctc_ratio_n /
						decoder->tsc_ctc_ratio_d;
	पूर्ण

	/*
	 * A TSC packet can slip past MTC packets so that the बारtamp appears
	 * to go backwards. One estimate is that can be up to about 40 CPU
	 * cycles, which is certainly less than 0x1000 TSC ticks, but accept
	 * slippage an order of magnitude more to be on the safe side.
	 */
	decoder->tsc_slip = 0x10000;

	पूर्णांकel_pt_log("timestamp: mtc_shift %u\n", decoder->mtc_shअगरt);
	पूर्णांकel_pt_log("timestamp: tsc_ctc_ratio_n %u\n", decoder->tsc_ctc_ratio_n);
	पूर्णांकel_pt_log("timestamp: tsc_ctc_ratio_d %u\n", decoder->tsc_ctc_ratio_d);
	पूर्णांकel_pt_log("timestamp: tsc_ctc_mult %u\n", decoder->tsc_ctc_mult);
	पूर्णांकel_pt_log("timestamp: tsc_slip %#x\n", decoder->tsc_slip);

	अगर (decoder->hop)
		पूर्णांकel_pt_log("Hop mode: decoding FUP and TIPs, but not TNT\n");

	वापस decoder;
पूर्ण

अटल व्योम पूर्णांकel_pt_pop_blk(काष्ठा पूर्णांकel_pt_stack *stack)
अणु
	काष्ठा पूर्णांकel_pt_blk *blk = stack->blk;

	stack->blk = blk->prev;
	अगर (!stack->spare)
		stack->spare = blk;
	अन्यथा
		मुक्त(blk);
पूर्ण

अटल uपूर्णांक64_t पूर्णांकel_pt_pop(काष्ठा पूर्णांकel_pt_stack *stack)
अणु
	अगर (!stack->pos) अणु
		अगर (!stack->blk)
			वापस 0;
		पूर्णांकel_pt_pop_blk(stack);
		अगर (!stack->blk)
			वापस 0;
		stack->pos = INTEL_PT_BLK_SIZE;
	पूर्ण
	वापस stack->blk->ip[--stack->pos];
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_alloc_blk(काष्ठा पूर्णांकel_pt_stack *stack)
अणु
	काष्ठा पूर्णांकel_pt_blk *blk;

	अगर (stack->spare) अणु
		blk = stack->spare;
		stack->spare = शून्य;
	पूर्ण अन्यथा अणु
		blk = दो_स्मृति(माप(काष्ठा पूर्णांकel_pt_blk));
		अगर (!blk)
			वापस -ENOMEM;
	पूर्ण

	blk->prev = stack->blk;
	stack->blk = blk;
	stack->pos = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_push(काष्ठा पूर्णांकel_pt_stack *stack, uपूर्णांक64_t ip)
अणु
	पूर्णांक err;

	अगर (!stack->blk || stack->pos == INTEL_PT_BLK_SIZE) अणु
		err = पूर्णांकel_pt_alloc_blk(stack);
		अगर (err)
			वापस err;
	पूर्ण

	stack->blk->ip[stack->pos++] = ip;
	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_pt_clear_stack(काष्ठा पूर्णांकel_pt_stack *stack)
अणु
	जबतक (stack->blk)
		पूर्णांकel_pt_pop_blk(stack);
	stack->pos = 0;
पूर्ण

अटल व्योम पूर्णांकel_pt_मुक्त_stack(काष्ठा पूर्णांकel_pt_stack *stack)
अणु
	पूर्णांकel_pt_clear_stack(stack);
	zमुक्त(&stack->blk);
	zमुक्त(&stack->spare);
पूर्ण

व्योम पूर्णांकel_pt_decoder_मुक्त(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	पूर्णांकel_pt_मुक्त_stack(&decoder->stack);
	मुक्त(decoder);
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_ext_err(पूर्णांक code)
अणु
	चयन (code) अणु
	हाल -ENOMEM:
		वापस INTEL_PT_ERR_NOMEM;
	हाल -ENOSYS:
		वापस INTEL_PT_ERR_INTERN;
	हाल -EBADMSG:
		वापस INTEL_PT_ERR_BADPKT;
	हाल -ENODATA:
		वापस INTEL_PT_ERR_NODATA;
	हाल -EILSEQ:
		वापस INTEL_PT_ERR_NOINSN;
	हाल -ENOENT:
		वापस INTEL_PT_ERR_MISMAT;
	हाल -EOVERFLOW:
		वापस INTEL_PT_ERR_OVR;
	हाल -ENOSPC:
		वापस INTEL_PT_ERR_LOST;
	हाल -ELOOP:
		वापस INTEL_PT_ERR_NELOOP;
	शेष:
		वापस INTEL_PT_ERR_UNK;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *पूर्णांकel_pt_err_msgs[] = अणु
	[INTEL_PT_ERR_NOMEM]  = "Memory allocation failed",
	[INTEL_PT_ERR_INTERN] = "Internal error",
	[INTEL_PT_ERR_BADPKT] = "Bad packet",
	[INTEL_PT_ERR_NODATA] = "No more data",
	[INTEL_PT_ERR_NOINSN] = "Failed to get instruction",
	[INTEL_PT_ERR_MISMAT] = "Trace doesn't match instruction",
	[INTEL_PT_ERR_OVR]    = "Overflow packet",
	[INTEL_PT_ERR_LOST]   = "Lost trace data",
	[INTEL_PT_ERR_UNK]    = "Unknown error!",
	[INTEL_PT_ERR_NELOOP] = "Never-ending loop",
पूर्ण;

पूर्णांक पूर्णांकel_pt__म_त्रुटि(पूर्णांक code, अक्षर *buf, माप_प्रकार buflen)
अणु
	अगर (code < 1 || code >= INTEL_PT_ERR_MAX)
		code = INTEL_PT_ERR_UNK;
	strlcpy(buf, पूर्णांकel_pt_err_msgs[code], buflen);
	वापस 0;
पूर्ण

अटल uपूर्णांक64_t पूर्णांकel_pt_calc_ip(स्थिर काष्ठा पूर्णांकel_pt_pkt *packet,
				 uपूर्णांक64_t last_ip)
अणु
	uपूर्णांक64_t ip;

	चयन (packet->count) अणु
	हाल 1:
		ip = (last_ip & (uपूर्णांक64_t)0xffffffffffff0000ULL) |
		     packet->payload;
		अवरोध;
	हाल 2:
		ip = (last_ip & (uपूर्णांक64_t)0xffffffff00000000ULL) |
		     packet->payload;
		अवरोध;
	हाल 3:
		ip = packet->payload;
		/* Sign-extend 6-byte ip */
		अगर (ip & (uपूर्णांक64_t)0x800000000000ULL)
			ip |= (uपूर्णांक64_t)0xffff000000000000ULL;
		अवरोध;
	हाल 4:
		ip = (last_ip & (uपूर्णांक64_t)0xffff000000000000ULL) |
		     packet->payload;
		अवरोध;
	हाल 6:
		ip = packet->payload;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस ip;
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_pt_set_last_ip(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	decoder->last_ip = पूर्णांकel_pt_calc_ip(&decoder->packet, decoder->last_ip);
	decoder->have_last_ip = true;
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_pt_set_ip(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	पूर्णांकel_pt_set_last_ip(decoder);
	decoder->ip = decoder->last_ip;
पूर्ण

अटल व्योम पूर्णांकel_pt_decoder_log_packet(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	पूर्णांकel_pt_log_packet(&decoder->packet, decoder->pkt_len, decoder->pos,
			    decoder->buf);
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_bug(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	पूर्णांकel_pt_log("ERROR: Internal error\n");
	decoder->pkt_state = INTEL_PT_STATE_NO_PSB;
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_pt_clear_tx_flags(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	decoder->tx_flags = 0;
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_pt_update_in_tx(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	decoder->tx_flags = decoder->packet.payload & INTEL_PT_IN_TX;
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_pt_update_pip(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	decoder->pip_payload = decoder->packet.payload;
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_pt_update_nr(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	decoder->next_nr = decoder->pip_payload & 1;
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_pt_set_nr(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	decoder->nr = decoder->pip_payload & 1;
	decoder->next_nr = decoder->nr;
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_pt_set_pip(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	पूर्णांकel_pt_update_pip(decoder);
	पूर्णांकel_pt_set_nr(decoder);
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_bad_packet(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	पूर्णांकel_pt_clear_tx_flags(decoder);
	decoder->have_पंचांगa = false;
	decoder->pkt_len = 1;
	decoder->pkt_step = 1;
	पूर्णांकel_pt_decoder_log_packet(decoder);
	अगर (decoder->pkt_state != INTEL_PT_STATE_NO_PSB) अणु
		पूर्णांकel_pt_log("ERROR: Bad packet\n");
		decoder->pkt_state = INTEL_PT_STATE_ERR1;
	पूर्ण
	वापस -EBADMSG;
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_pt_update_sample_समय(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	decoder->sample_बारtamp = decoder->बारtamp;
	decoder->sample_insn_cnt = decoder->बारtamp_insn_cnt;
पूर्ण

अटल व्योम पूर्णांकel_pt_reposition(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	decoder->ip = 0;
	decoder->pkt_state = INTEL_PT_STATE_NO_PSB;
	decoder->बारtamp = 0;
	decoder->have_पंचांगa = false;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_data(काष्ठा पूर्णांकel_pt_decoder *decoder, bool reposition)
अणु
	काष्ठा पूर्णांकel_pt_buffer buffer = अणु .buf = 0, पूर्ण;
	पूर्णांक ret;

	decoder->pkt_step = 0;

	पूर्णांकel_pt_log("Getting more data\n");
	ret = decoder->get_trace(&buffer, decoder->data);
	अगर (ret)
		वापस ret;
	decoder->buf = buffer.buf;
	decoder->len = buffer.len;
	अगर (!decoder->len) अणु
		पूर्णांकel_pt_log("No more data\n");
		वापस -ENODATA;
	पूर्ण
	decoder->buf_बारtamp = buffer.ref_बारtamp;
	अगर (!buffer.consecutive || reposition) अणु
		पूर्णांकel_pt_reposition(decoder);
		decoder->ref_बारtamp = buffer.ref_बारtamp;
		decoder->state.trace_nr = buffer.trace_nr;
		पूर्णांकel_pt_log("Reference timestamp 0x%" PRIx64 "\n",
			     decoder->ref_बारtamp);
		वापस -ENOLINK;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_next_data(काष्ठा पूर्णांकel_pt_decoder *decoder,
				  bool reposition)
अणु
	अगर (!decoder->next_buf)
		वापस पूर्णांकel_pt_get_data(decoder, reposition);

	decoder->buf = decoder->next_buf;
	decoder->len = decoder->next_len;
	decoder->next_buf = 0;
	decoder->next_len = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_split_packet(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	अचिन्हित अक्षर *buf = decoder->temp_buf;
	माप_प्रकार old_len, len, n;
	पूर्णांक ret;

	old_len = decoder->len;
	len = decoder->len;
	स_नकल(buf, decoder->buf, len);

	ret = पूर्णांकel_pt_get_data(decoder, false);
	अगर (ret) अणु
		decoder->pos += old_len;
		वापस ret < 0 ? ret : -EINVAL;
	पूर्ण

	n = INTEL_PT_PKT_MAX_SZ - len;
	अगर (n > decoder->len)
		n = decoder->len;
	स_नकल(buf + len, decoder->buf, n);
	len += n;

	decoder->prev_pkt_ctx = decoder->pkt_ctx;
	ret = पूर्णांकel_pt_get_packet(buf, len, &decoder->packet, &decoder->pkt_ctx);
	अगर (ret < (पूर्णांक)old_len) अणु
		decoder->next_buf = decoder->buf;
		decoder->next_len = decoder->len;
		decoder->buf = buf;
		decoder->len = old_len;
		वापस पूर्णांकel_pt_bad_packet(decoder);
	पूर्ण

	decoder->next_buf = decoder->buf + (ret - old_len);
	decoder->next_len = decoder->len - (ret - old_len);

	decoder->buf = buf;
	decoder->len = ret;

	वापस ret;
पूर्ण

काष्ठा पूर्णांकel_pt_pkt_info अणु
	काष्ठा पूर्णांकel_pt_decoder	  *decoder;
	काष्ठा पूर्णांकel_pt_pkt       packet;
	uपूर्णांक64_t                  pos;
	पूर्णांक                       pkt_len;
	पूर्णांक                       last_packet_type;
	व्योम                      *data;
पूर्ण;

प्रकार पूर्णांक (*पूर्णांकel_pt_pkt_cb_t)(काष्ठा पूर्णांकel_pt_pkt_info *pkt_info);

/* Lookahead packets in current buffer */
अटल पूर्णांक पूर्णांकel_pt_pkt_lookahead(काष्ठा पूर्णांकel_pt_decoder *decoder,
				  पूर्णांकel_pt_pkt_cb_t cb, व्योम *data)
अणु
	काष्ठा पूर्णांकel_pt_pkt_info pkt_info;
	स्थिर अचिन्हित अक्षर *buf = decoder->buf;
	क्रमागत पूर्णांकel_pt_pkt_ctx pkt_ctx = decoder->pkt_ctx;
	माप_प्रकार len = decoder->len;
	पूर्णांक ret;

	pkt_info.decoder          = decoder;
	pkt_info.pos              = decoder->pos;
	pkt_info.pkt_len          = decoder->pkt_step;
	pkt_info.last_packet_type = decoder->last_packet_type;
	pkt_info.data             = data;

	जबतक (1) अणु
		करो अणु
			pkt_info.pos += pkt_info.pkt_len;
			buf          += pkt_info.pkt_len;
			len          -= pkt_info.pkt_len;

			अगर (!len)
				वापस INTEL_PT_NEED_MORE_BYTES;

			ret = पूर्णांकel_pt_get_packet(buf, len, &pkt_info.packet,
						  &pkt_ctx);
			अगर (!ret)
				वापस INTEL_PT_NEED_MORE_BYTES;
			अगर (ret < 0)
				वापस ret;

			pkt_info.pkt_len = ret;
		पूर्ण जबतक (pkt_info.packet.type == INTEL_PT_PAD);

		ret = cb(&pkt_info);
		अगर (ret)
			वापस 0;

		pkt_info.last_packet_type = pkt_info.packet.type;
	पूर्ण
पूर्ण

काष्ठा पूर्णांकel_pt_calc_cyc_to_tsc_info अणु
	uपूर्णांक64_t        cycle_cnt;
	अचिन्हित पूर्णांक    cbr;
	uपूर्णांक32_t        last_mtc;
	uपूर्णांक64_t        ctc_बारtamp;
	uपूर्णांक64_t        ctc_delta;
	uपूर्णांक64_t        tsc_बारtamp;
	uपूर्णांक64_t        बारtamp;
	bool            have_पंचांगa;
	bool            fixup_last_mtc;
	bool            from_mtc;
	द्विगुन          cbr_cyc_to_tsc;
पूर्ण;

/*
 * MTC provides a 8-bit slice of CTC but the TMA packet only provides the lower
 * 16 bits of CTC. If mtc_shअगरt > 8 then some of the MTC bits are not in the CTC
 * provided by the TMA packet. Fix-up the last_mtc calculated from the TMA
 * packet by copying the missing bits from the current MTC assuming the least
 * dअगरference between the two, and that the current MTC comes after last_mtc.
 */
अटल व्योम पूर्णांकel_pt_fixup_last_mtc(uपूर्णांक32_t mtc, पूर्णांक mtc_shअगरt,
				    uपूर्णांक32_t *last_mtc)
अणु
	uपूर्णांक32_t first_missing_bit = 1U << (16 - mtc_shअगरt);
	uपूर्णांक32_t mask = ~(first_missing_bit - 1);

	*last_mtc |= mtc & mask;
	अगर (*last_mtc >= mtc) अणु
		*last_mtc -= first_missing_bit;
		*last_mtc &= 0xff;
	पूर्ण
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_calc_cyc_cb(काष्ठा पूर्णांकel_pt_pkt_info *pkt_info)
अणु
	काष्ठा पूर्णांकel_pt_decoder *decoder = pkt_info->decoder;
	काष्ठा पूर्णांकel_pt_calc_cyc_to_tsc_info *data = pkt_info->data;
	uपूर्णांक64_t बारtamp;
	द्विगुन cyc_to_tsc;
	अचिन्हित पूर्णांक cbr;
	uपूर्णांक32_t mtc, mtc_delta, ctc, fc, ctc_rem;

	चयन (pkt_info->packet.type) अणु
	हाल INTEL_PT_TNT:
	हाल INTEL_PT_TIP_PGE:
	हाल INTEL_PT_TIP:
	हाल INTEL_PT_FUP:
	हाल INTEL_PT_PSB:
	हाल INTEL_PT_PIP:
	हाल INTEL_PT_MODE_EXEC:
	हाल INTEL_PT_MODE_TSX:
	हाल INTEL_PT_PSBEND:
	हाल INTEL_PT_PAD:
	हाल INTEL_PT_VMCS:
	हाल INTEL_PT_MNT:
	हाल INTEL_PT_PTWRITE:
	हाल INTEL_PT_PTWRITE_IP:
	हाल INTEL_PT_BBP:
	हाल INTEL_PT_BIP:
	हाल INTEL_PT_BEP:
	हाल INTEL_PT_BEP_IP:
		वापस 0;

	हाल INTEL_PT_MTC:
		अगर (!data->have_पंचांगa)
			वापस 0;

		mtc = pkt_info->packet.payload;
		अगर (decoder->mtc_shअगरt > 8 && data->fixup_last_mtc) अणु
			data->fixup_last_mtc = false;
			पूर्णांकel_pt_fixup_last_mtc(mtc, decoder->mtc_shअगरt,
						&data->last_mtc);
		पूर्ण
		अगर (mtc > data->last_mtc)
			mtc_delta = mtc - data->last_mtc;
		अन्यथा
			mtc_delta = mtc + 256 - data->last_mtc;
		data->ctc_delta += mtc_delta << decoder->mtc_shअगरt;
		data->last_mtc = mtc;

		अगर (decoder->tsc_ctc_mult) अणु
			बारtamp = data->ctc_बारtamp +
				data->ctc_delta * decoder->tsc_ctc_mult;
		पूर्ण अन्यथा अणु
			बारtamp = data->ctc_बारtamp +
				multभाग(data->ctc_delta,
					decoder->tsc_ctc_ratio_n,
					decoder->tsc_ctc_ratio_d);
		पूर्ण

		अगर (बारtamp < data->बारtamp)
			वापस 1;

		अगर (pkt_info->last_packet_type != INTEL_PT_CYC) अणु
			data->बारtamp = बारtamp;
			वापस 0;
		पूर्ण

		अवरोध;

	हाल INTEL_PT_TSC:
		/*
		 * For now, करो not support using TSC packets - refer
		 * पूर्णांकel_pt_calc_cyc_to_tsc().
		 */
		अगर (data->from_mtc)
			वापस 1;
		बारtamp = pkt_info->packet.payload |
			    (data->बारtamp & (0xffULL << 56));
		अगर (data->from_mtc && बारtamp < data->बारtamp &&
		    data->बारtamp - बारtamp < decoder->tsc_slip)
			वापस 1;
		अगर (बारtamp < data->बारtamp)
			बारtamp += (1ULL << 56);
		अगर (pkt_info->last_packet_type != INTEL_PT_CYC) अणु
			अगर (data->from_mtc)
				वापस 1;
			data->tsc_बारtamp = बारtamp;
			data->बारtamp = बारtamp;
			वापस 0;
		पूर्ण
		अवरोध;

	हाल INTEL_PT_TMA:
		अगर (data->from_mtc)
			वापस 1;

		अगर (!decoder->tsc_ctc_ratio_d)
			वापस 0;

		ctc = pkt_info->packet.payload;
		fc = pkt_info->packet.count;
		ctc_rem = ctc & decoder->ctc_rem_mask;

		data->last_mtc = (ctc >> decoder->mtc_shअगरt) & 0xff;

		data->ctc_बारtamp = data->tsc_बारtamp - fc;
		अगर (decoder->tsc_ctc_mult) अणु
			data->ctc_बारtamp -= ctc_rem * decoder->tsc_ctc_mult;
		पूर्ण अन्यथा अणु
			data->ctc_बारtamp -=
				multभाग(ctc_rem, decoder->tsc_ctc_ratio_n,
					decoder->tsc_ctc_ratio_d);
		पूर्ण

		data->ctc_delta = 0;
		data->have_पंचांगa = true;
		data->fixup_last_mtc = true;

		वापस 0;

	हाल INTEL_PT_CYC:
		data->cycle_cnt += pkt_info->packet.payload;
		वापस 0;

	हाल INTEL_PT_CBR:
		cbr = pkt_info->packet.payload;
		अगर (data->cbr && data->cbr != cbr)
			वापस 1;
		data->cbr = cbr;
		data->cbr_cyc_to_tsc = decoder->max_non_turbo_ratio_fp / cbr;
		वापस 0;

	हाल INTEL_PT_TIP_PGD:
	हाल INTEL_PT_TRACESTOP:
	हाल INTEL_PT_EXSTOP:
	हाल INTEL_PT_EXSTOP_IP:
	हाल INTEL_PT_MWAIT:
	हाल INTEL_PT_PWRE:
	हाल INTEL_PT_PWRX:
	हाल INTEL_PT_OVF:
	हाल INTEL_PT_BAD: /* Does not happen */
	शेष:
		वापस 1;
	पूर्ण

	अगर (!data->cbr && decoder->cbr) अणु
		data->cbr = decoder->cbr;
		data->cbr_cyc_to_tsc = decoder->cbr_cyc_to_tsc;
	पूर्ण

	अगर (!data->cycle_cnt)
		वापस 1;

	cyc_to_tsc = (द्विगुन)(बारtamp - decoder->बारtamp) / data->cycle_cnt;

	अगर (data->cbr && cyc_to_tsc > data->cbr_cyc_to_tsc &&
	    cyc_to_tsc / data->cbr_cyc_to_tsc > 1.25) अणु
		पूर्णांकel_pt_log("Timestamp: calculated %g TSC ticks per cycle too big (c.f. CBR-based value %g), pos " x64_fmt "\n",
			     cyc_to_tsc, data->cbr_cyc_to_tsc, pkt_info->pos);
		वापस 1;
	पूर्ण

	decoder->calc_cyc_to_tsc = cyc_to_tsc;
	decoder->have_calc_cyc_to_tsc = true;

	अगर (data->cbr) अणु
		पूर्णांकel_pt_log("Timestamp: calculated %g TSC ticks per cycle c.f. CBR-based value %g, pos " x64_fmt "\n",
			     cyc_to_tsc, data->cbr_cyc_to_tsc, pkt_info->pos);
	पूर्ण अन्यथा अणु
		पूर्णांकel_pt_log("Timestamp: calculated %g TSC ticks per cycle c.f. unknown CBR-based value, pos " x64_fmt "\n",
			     cyc_to_tsc, pkt_info->pos);
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम पूर्णांकel_pt_calc_cyc_to_tsc(काष्ठा पूर्णांकel_pt_decoder *decoder,
				     bool from_mtc)
अणु
	काष्ठा पूर्णांकel_pt_calc_cyc_to_tsc_info data = अणु
		.cycle_cnt      = 0,
		.cbr            = 0,
		.last_mtc       = decoder->last_mtc,
		.ctc_बारtamp  = decoder->ctc_बारtamp,
		.ctc_delta      = decoder->ctc_delta,
		.tsc_बारtamp  = decoder->tsc_बारtamp,
		.बारtamp      = decoder->बारtamp,
		.have_पंचांगa       = decoder->have_पंचांगa,
		.fixup_last_mtc = decoder->fixup_last_mtc,
		.from_mtc       = from_mtc,
		.cbr_cyc_to_tsc = 0,
	पूर्ण;

	/*
	 * For now, करो not support using TSC packets क्रम at least the reasons:
	 * 1) timing might have stopped
	 * 2) TSC packets within PSB+ can slip against CYC packets
	 */
	अगर (!from_mtc)
		वापस;

	पूर्णांकel_pt_pkt_lookahead(decoder, पूर्णांकel_pt_calc_cyc_cb, &data);
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_next_packet(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	पूर्णांक ret;

	decoder->last_packet_type = decoder->packet.type;

	करो अणु
		decoder->pos += decoder->pkt_step;
		decoder->buf += decoder->pkt_step;
		decoder->len -= decoder->pkt_step;

		अगर (!decoder->len) अणु
			ret = पूर्णांकel_pt_get_next_data(decoder, false);
			अगर (ret)
				वापस ret;
		पूर्ण

		decoder->prev_pkt_ctx = decoder->pkt_ctx;
		ret = पूर्णांकel_pt_get_packet(decoder->buf, decoder->len,
					  &decoder->packet, &decoder->pkt_ctx);
		अगर (ret == INTEL_PT_NEED_MORE_BYTES && BITS_PER_LONG == 32 &&
		    decoder->len < INTEL_PT_PKT_MAX_SZ && !decoder->next_buf) अणु
			ret = पूर्णांकel_pt_get_split_packet(decoder);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
		अगर (ret <= 0)
			वापस पूर्णांकel_pt_bad_packet(decoder);

		decoder->pkt_len = ret;
		decoder->pkt_step = ret;
		पूर्णांकel_pt_decoder_log_packet(decoder);
	पूर्ण जबतक (decoder->packet.type == INTEL_PT_PAD);

	वापस 0;
पूर्ण

अटल uपूर्णांक64_t पूर्णांकel_pt_next_period(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	uपूर्णांक64_t बारtamp, masked_बारtamp;

	बारtamp = decoder->बारtamp + decoder->बारtamp_insn_cnt;
	masked_बारtamp = बारtamp & decoder->period_mask;
	अगर (decoder->continuous_period) अणु
		अगर (masked_बारtamp > decoder->last_masked_बारtamp)
			वापस 1;
	पूर्ण अन्यथा अणु
		बारtamp += 1;
		masked_बारtamp = बारtamp & decoder->period_mask;
		अगर (masked_बारtamp > decoder->last_masked_बारtamp) अणु
			decoder->last_masked_बारtamp = masked_बारtamp;
			decoder->continuous_period = true;
		पूर्ण
	पूर्ण

	अगर (masked_बारtamp < decoder->last_masked_बारtamp)
		वापस decoder->period_ticks;

	वापस decoder->period_ticks - (बारtamp - masked_बारtamp);
पूर्ण

अटल uपूर्णांक64_t पूर्णांकel_pt_next_sample(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	चयन (decoder->period_type) अणु
	हाल INTEL_PT_PERIOD_INSTRUCTIONS:
		वापस decoder->period - decoder->period_insn_cnt;
	हाल INTEL_PT_PERIOD_TICKS:
		वापस पूर्णांकel_pt_next_period(decoder);
	हाल INTEL_PT_PERIOD_NONE:
	हाल INTEL_PT_PERIOD_MTC:
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_pt_sample_insn(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	uपूर्णांक64_t बारtamp, masked_बारtamp;

	चयन (decoder->period_type) अणु
	हाल INTEL_PT_PERIOD_INSTRUCTIONS:
		decoder->period_insn_cnt = 0;
		अवरोध;
	हाल INTEL_PT_PERIOD_TICKS:
		बारtamp = decoder->बारtamp + decoder->बारtamp_insn_cnt;
		masked_बारtamp = बारtamp & decoder->period_mask;
		अगर (masked_बारtamp > decoder->last_masked_बारtamp)
			decoder->last_masked_बारtamp = masked_बारtamp;
		अन्यथा
			decoder->last_masked_बारtamp += decoder->period_ticks;
		अवरोध;
	हाल INTEL_PT_PERIOD_NONE:
	हाल INTEL_PT_PERIOD_MTC:
	शेष:
		अवरोध;
	पूर्ण

	decoder->state.type |= INTEL_PT_INSTRUCTION;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_walk_insn(काष्ठा पूर्णांकel_pt_decoder *decoder,
			      काष्ठा पूर्णांकel_pt_insn *पूर्णांकel_pt_insn, uपूर्णांक64_t ip)
अणु
	uपूर्णांक64_t max_insn_cnt, insn_cnt = 0;
	पूर्णांक err;

	अगर (!decoder->mtc_insn)
		decoder->mtc_insn = true;

	max_insn_cnt = पूर्णांकel_pt_next_sample(decoder);

	err = decoder->walk_insn(पूर्णांकel_pt_insn, &insn_cnt, &decoder->ip, ip,
				 max_insn_cnt, decoder->data);

	decoder->tot_insn_cnt += insn_cnt;
	decoder->बारtamp_insn_cnt += insn_cnt;
	decoder->sample_insn_cnt += insn_cnt;
	decoder->period_insn_cnt += insn_cnt;

	अगर (err) अणु
		decoder->no_progress = 0;
		decoder->pkt_state = INTEL_PT_STATE_ERR2;
		पूर्णांकel_pt_log_at("ERROR: Failed to get instruction",
				decoder->ip);
		अगर (err == -ENOENT)
			वापस -ENOLINK;
		वापस -EILSEQ;
	पूर्ण

	अगर (ip && decoder->ip == ip) अणु
		err = -EAGAIN;
		जाओ out;
	पूर्ण

	अगर (max_insn_cnt && insn_cnt >= max_insn_cnt)
		पूर्णांकel_pt_sample_insn(decoder);

	अगर (पूर्णांकel_pt_insn->branch == INTEL_PT_BR_NO_BRANCH) अणु
		decoder->state.type = INTEL_PT_INSTRUCTION;
		decoder->state.from_ip = decoder->ip;
		decoder->state.to_ip = 0;
		decoder->ip += पूर्णांकel_pt_insn->length;
		err = INTEL_PT_RETURN;
		जाओ out;
	पूर्ण

	अगर (पूर्णांकel_pt_insn->op == INTEL_PT_OP_CALL) अणु
		/* Zero-length calls are excluded */
		अगर (पूर्णांकel_pt_insn->branch != INTEL_PT_BR_UNCONDITIONAL ||
		    पूर्णांकel_pt_insn->rel) अणु
			err = पूर्णांकel_pt_push(&decoder->stack, decoder->ip +
					    पूर्णांकel_pt_insn->length);
			अगर (err)
				जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (पूर्णांकel_pt_insn->op == INTEL_PT_OP_RET) अणु
		decoder->ret_addr = पूर्णांकel_pt_pop(&decoder->stack);
	पूर्ण

	अगर (पूर्णांकel_pt_insn->branch == INTEL_PT_BR_UNCONDITIONAL) अणु
		पूर्णांक cnt = decoder->no_progress++;

		decoder->state.from_ip = decoder->ip;
		decoder->ip += पूर्णांकel_pt_insn->length +
				पूर्णांकel_pt_insn->rel;
		decoder->state.to_ip = decoder->ip;
		err = INTEL_PT_RETURN;

		/*
		 * Check क्रम being stuck in a loop.  This can happen अगर a
		 * decoder error results in the decoder erroneously setting the
		 * ip to an address that is itself in an infinite loop that
		 * consumes no packets.  When that happens, there must be an
		 * unconditional branch.
		 */
		अगर (cnt) अणु
			अगर (cnt == 1) अणु
				decoder->stuck_ip = decoder->state.to_ip;
				decoder->stuck_ip_prd = 1;
				decoder->stuck_ip_cnt = 1;
			पूर्ण अन्यथा अगर (cnt > INTEL_PT_MAX_LOOPS ||
				   decoder->state.to_ip == decoder->stuck_ip) अणु
				पूर्णांकel_pt_log_at("ERROR: Never-ending loop",
						decoder->state.to_ip);
				decoder->pkt_state = INTEL_PT_STATE_ERR_RESYNC;
				err = -ELOOP;
				जाओ out;
			पूर्ण अन्यथा अगर (!--decoder->stuck_ip_cnt) अणु
				decoder->stuck_ip_prd += 1;
				decoder->stuck_ip_cnt = decoder->stuck_ip_prd;
				decoder->stuck_ip = decoder->state.to_ip;
			पूर्ण
		पूर्ण
		जाओ out_no_progress;
	पूर्ण
out:
	decoder->no_progress = 0;
out_no_progress:
	decoder->state.insn_op = पूर्णांकel_pt_insn->op;
	decoder->state.insn_len = पूर्णांकel_pt_insn->length;
	स_नकल(decoder->state.insn, पूर्णांकel_pt_insn->buf,
	       INTEL_PT_INSN_BUF_SZ);

	अगर (decoder->tx_flags & INTEL_PT_IN_TX)
		decoder->state.flags |= INTEL_PT_IN_TX;

	वापस err;
पूर्ण

अटल bool पूर्णांकel_pt_fup_event(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	bool ret = false;

	अगर (decoder->set_fup_tx_flags) अणु
		decoder->set_fup_tx_flags = false;
		decoder->tx_flags = decoder->fup_tx_flags;
		decoder->state.type = INTEL_PT_TRANSACTION;
		अगर (decoder->fup_tx_flags & INTEL_PT_ABORT_TX)
			decoder->state.type |= INTEL_PT_BRANCH;
		decoder->state.from_ip = decoder->ip;
		decoder->state.to_ip = 0;
		decoder->state.flags = decoder->fup_tx_flags;
		वापस true;
	पूर्ण
	अगर (decoder->set_fup_ptw) अणु
		decoder->set_fup_ptw = false;
		decoder->state.type = INTEL_PT_PTW;
		decoder->state.flags |= INTEL_PT_FUP_IP;
		decoder->state.from_ip = decoder->ip;
		decoder->state.to_ip = 0;
		decoder->state.ptw_payload = decoder->fup_ptw_payload;
		वापस true;
	पूर्ण
	अगर (decoder->set_fup_mरुको) अणु
		decoder->set_fup_mरुको = false;
		decoder->state.type = INTEL_PT_MWAIT_OP;
		decoder->state.from_ip = decoder->ip;
		decoder->state.to_ip = 0;
		decoder->state.mरुको_payload = decoder->fup_mरुको_payload;
		ret = true;
	पूर्ण
	अगर (decoder->set_fup_pwre) अणु
		decoder->set_fup_pwre = false;
		decoder->state.type |= INTEL_PT_PWR_ENTRY;
		decoder->state.type &= ~INTEL_PT_BRANCH;
		decoder->state.from_ip = decoder->ip;
		decoder->state.to_ip = 0;
		decoder->state.pwre_payload = decoder->fup_pwre_payload;
		ret = true;
	पूर्ण
	अगर (decoder->set_fup_exstop) अणु
		decoder->set_fup_exstop = false;
		decoder->state.type |= INTEL_PT_EX_STOP;
		decoder->state.type &= ~INTEL_PT_BRANCH;
		decoder->state.flags |= INTEL_PT_FUP_IP;
		decoder->state.from_ip = decoder->ip;
		decoder->state.to_ip = 0;
		ret = true;
	पूर्ण
	अगर (decoder->set_fup_bep) अणु
		decoder->set_fup_bep = false;
		decoder->state.type |= INTEL_PT_BLK_ITEMS;
		decoder->state.type &= ~INTEL_PT_BRANCH;
		decoder->state.from_ip = decoder->ip;
		decoder->state.to_ip = 0;
		ret = true;
	पूर्ण
	वापस ret;
पूर्ण

अटल अंतरभूत bool पूर्णांकel_pt_fup_with_nlip(काष्ठा पूर्णांकel_pt_decoder *decoder,
					  काष्ठा पूर्णांकel_pt_insn *पूर्णांकel_pt_insn,
					  uपूर्णांक64_t ip, पूर्णांक err)
अणु
	वापस decoder->flags & INTEL_PT_FUP_WITH_NLIP && !err &&
	       पूर्णांकel_pt_insn->branch == INTEL_PT_BR_INसूचीECT &&
	       ip == decoder->ip + पूर्णांकel_pt_insn->length;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_walk_fup(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	काष्ठा पूर्णांकel_pt_insn पूर्णांकel_pt_insn;
	uपूर्णांक64_t ip;
	पूर्णांक err;

	ip = decoder->last_ip;

	जबतक (1) अणु
		err = पूर्णांकel_pt_walk_insn(decoder, &पूर्णांकel_pt_insn, ip);
		अगर (err == INTEL_PT_RETURN)
			वापस 0;
		अगर (err == -EAGAIN ||
		    पूर्णांकel_pt_fup_with_nlip(decoder, &पूर्णांकel_pt_insn, ip, err)) अणु
			bool no_tip = decoder->pkt_state != INTEL_PT_STATE_FUP;

			decoder->pkt_state = INTEL_PT_STATE_IN_SYNC;
			अगर (पूर्णांकel_pt_fup_event(decoder) && no_tip)
				वापस 0;
			वापस -EAGAIN;
		पूर्ण
		decoder->set_fup_tx_flags = false;
		अगर (err)
			वापस err;

		अगर (पूर्णांकel_pt_insn.branch == INTEL_PT_BR_INसूचीECT) अणु
			पूर्णांकel_pt_log_at("ERROR: Unexpected indirect branch",
					decoder->ip);
			decoder->pkt_state = INTEL_PT_STATE_ERR_RESYNC;
			वापस -ENOENT;
		पूर्ण

		अगर (पूर्णांकel_pt_insn.branch == INTEL_PT_BR_CONDITIONAL) अणु
			पूर्णांकel_pt_log_at("ERROR: Unexpected conditional branch",
					decoder->ip);
			decoder->pkt_state = INTEL_PT_STATE_ERR_RESYNC;
			वापस -ENOENT;
		पूर्ण

		पूर्णांकel_pt_bug(decoder);
	पूर्ण
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_walk_tip(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	काष्ठा पूर्णांकel_pt_insn पूर्णांकel_pt_insn;
	पूर्णांक err;

	err = पूर्णांकel_pt_walk_insn(decoder, &पूर्णांकel_pt_insn, 0);
	अगर (err == INTEL_PT_RETURN &&
	    decoder->pgd_ip &&
	    decoder->pkt_state == INTEL_PT_STATE_TIP_PGD &&
	    (decoder->state.type & INTEL_PT_BRANCH) &&
	    decoder->pgd_ip(decoder->state.to_ip, decoder->data)) अणु
		/* Unconditional branch leaving filter region */
		decoder->no_progress = 0;
		decoder->pge = false;
		decoder->continuous_period = false;
		decoder->pkt_state = INTEL_PT_STATE_IN_SYNC;
		decoder->state.type |= INTEL_PT_TRACE_END;
		पूर्णांकel_pt_update_nr(decoder);
		वापस 0;
	पूर्ण
	अगर (err == INTEL_PT_RETURN)
		वापस 0;
	अगर (err)
		वापस err;

	पूर्णांकel_pt_update_nr(decoder);

	अगर (पूर्णांकel_pt_insn.branch == INTEL_PT_BR_INसूचीECT) अणु
		अगर (decoder->pkt_state == INTEL_PT_STATE_TIP_PGD) अणु
			decoder->pge = false;
			decoder->continuous_period = false;
			decoder->pkt_state = INTEL_PT_STATE_IN_SYNC;
			decoder->state.from_ip = decoder->ip;
			अगर (decoder->packet.count == 0) अणु
				decoder->state.to_ip = 0;
			पूर्ण अन्यथा अणु
				decoder->state.to_ip = decoder->last_ip;
				decoder->ip = decoder->last_ip;
			पूर्ण
			decoder->state.type |= INTEL_PT_TRACE_END;
		पूर्ण अन्यथा अणु
			decoder->pkt_state = INTEL_PT_STATE_IN_SYNC;
			decoder->state.from_ip = decoder->ip;
			अगर (decoder->packet.count == 0) अणु
				decoder->state.to_ip = 0;
			पूर्ण अन्यथा अणु
				decoder->state.to_ip = decoder->last_ip;
				decoder->ip = decoder->last_ip;
			पूर्ण
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (पूर्णांकel_pt_insn.branch == INTEL_PT_BR_CONDITIONAL) अणु
		uपूर्णांक64_t to_ip = decoder->ip + पूर्णांकel_pt_insn.length +
				 पूर्णांकel_pt_insn.rel;

		अगर (decoder->pgd_ip &&
		    decoder->pkt_state == INTEL_PT_STATE_TIP_PGD &&
		    decoder->pgd_ip(to_ip, decoder->data)) अणु
			/* Conditional branch leaving filter region */
			decoder->pge = false;
			decoder->continuous_period = false;
			decoder->pkt_state = INTEL_PT_STATE_IN_SYNC;
			decoder->ip = to_ip;
			decoder->state.from_ip = decoder->ip;
			decoder->state.to_ip = to_ip;
			decoder->state.type |= INTEL_PT_TRACE_END;
			वापस 0;
		पूर्ण
		पूर्णांकel_pt_log_at("ERROR: Conditional branch when expecting indirect branch",
				decoder->ip);
		decoder->pkt_state = INTEL_PT_STATE_ERR_RESYNC;
		वापस -ENOENT;
	पूर्ण

	वापस पूर्णांकel_pt_bug(decoder);
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_walk_tnt(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	काष्ठा पूर्णांकel_pt_insn पूर्णांकel_pt_insn;
	पूर्णांक err;

	जबतक (1) अणु
		err = पूर्णांकel_pt_walk_insn(decoder, &पूर्णांकel_pt_insn, 0);
		अगर (err == INTEL_PT_RETURN)
			वापस 0;
		अगर (err)
			वापस err;

		अगर (पूर्णांकel_pt_insn.op == INTEL_PT_OP_RET) अणु
			अगर (!decoder->वापस_compression) अणु
				पूर्णांकel_pt_log_at("ERROR: RET when expecting conditional branch",
						decoder->ip);
				decoder->pkt_state = INTEL_PT_STATE_ERR3;
				वापस -ENOENT;
			पूर्ण
			अगर (!decoder->ret_addr) अणु
				पूर्णांकel_pt_log_at("ERROR: Bad RET compression (stack empty)",
						decoder->ip);
				decoder->pkt_state = INTEL_PT_STATE_ERR3;
				वापस -ENOENT;
			पूर्ण
			अगर (!(decoder->tnt.payload & BIT63)) अणु
				पूर्णांकel_pt_log_at("ERROR: Bad RET compression (TNT=N)",
						decoder->ip);
				decoder->pkt_state = INTEL_PT_STATE_ERR3;
				वापस -ENOENT;
			पूर्ण
			decoder->tnt.count -= 1;
			अगर (decoder->tnt.count)
				decoder->pkt_state = INTEL_PT_STATE_TNT_CONT;
			अन्यथा
				decoder->pkt_state = INTEL_PT_STATE_IN_SYNC;
			decoder->tnt.payload <<= 1;
			decoder->state.from_ip = decoder->ip;
			decoder->ip = decoder->ret_addr;
			decoder->state.to_ip = decoder->ip;
			वापस 0;
		पूर्ण

		अगर (पूर्णांकel_pt_insn.branch == INTEL_PT_BR_INसूचीECT) अणु
			/* Handle deferred TIPs */
			err = पूर्णांकel_pt_get_next_packet(decoder);
			अगर (err)
				वापस err;
			अगर (decoder->packet.type != INTEL_PT_TIP ||
			    decoder->packet.count == 0) अणु
				पूर्णांकel_pt_log_at("ERROR: Missing deferred TIP for indirect branch",
						decoder->ip);
				decoder->pkt_state = INTEL_PT_STATE_ERR3;
				decoder->pkt_step = 0;
				वापस -ENOENT;
			पूर्ण
			पूर्णांकel_pt_set_last_ip(decoder);
			decoder->state.from_ip = decoder->ip;
			decoder->state.to_ip = decoder->last_ip;
			decoder->ip = decoder->last_ip;
			पूर्णांकel_pt_update_nr(decoder);
			वापस 0;
		पूर्ण

		अगर (पूर्णांकel_pt_insn.branch == INTEL_PT_BR_CONDITIONAL) अणु
			decoder->tnt.count -= 1;
			अगर (decoder->tnt.count)
				decoder->pkt_state = INTEL_PT_STATE_TNT_CONT;
			अन्यथा
				decoder->pkt_state = INTEL_PT_STATE_IN_SYNC;
			अगर (decoder->tnt.payload & BIT63) अणु
				decoder->tnt.payload <<= 1;
				decoder->state.from_ip = decoder->ip;
				decoder->ip += पूर्णांकel_pt_insn.length +
					       पूर्णांकel_pt_insn.rel;
				decoder->state.to_ip = decoder->ip;
				वापस 0;
			पूर्ण
			/* Inकाष्ठाion sample क्रम a non-taken branch */
			अगर (decoder->state.type & INTEL_PT_INSTRUCTION) अणु
				decoder->tnt.payload <<= 1;
				decoder->state.type = INTEL_PT_INSTRUCTION;
				decoder->state.from_ip = decoder->ip;
				decoder->state.to_ip = 0;
				decoder->ip += पूर्णांकel_pt_insn.length;
				वापस 0;
			पूर्ण
			decoder->sample_cyc = false;
			decoder->ip += पूर्णांकel_pt_insn.length;
			अगर (!decoder->tnt.count) अणु
				पूर्णांकel_pt_update_sample_समय(decoder);
				वापस -EAGAIN;
			पूर्ण
			decoder->tnt.payload <<= 1;
			जारी;
		पूर्ण

		वापस पूर्णांकel_pt_bug(decoder);
	पूर्ण
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_mode_tsx(काष्ठा पूर्णांकel_pt_decoder *decoder, bool *no_tip)
अणु
	अचिन्हित पूर्णांक fup_tx_flags;
	पूर्णांक err;

	fup_tx_flags = decoder->packet.payload &
		       (INTEL_PT_IN_TX | INTEL_PT_ABORT_TX);
	err = पूर्णांकel_pt_get_next_packet(decoder);
	अगर (err)
		वापस err;
	अगर (decoder->packet.type == INTEL_PT_FUP) अणु
		decoder->fup_tx_flags = fup_tx_flags;
		decoder->set_fup_tx_flags = true;
		अगर (!(decoder->fup_tx_flags & INTEL_PT_ABORT_TX))
			*no_tip = true;
	पूर्ण अन्यथा अणु
		पूर्णांकel_pt_log_at("ERROR: Missing FUP after MODE.TSX",
				decoder->pos);
		पूर्णांकel_pt_update_in_tx(decoder);
	पूर्ण
	वापस 0;
पूर्ण

अटल uपूर्णांक64_t पूर्णांकel_pt_8b_tsc(uपूर्णांक64_t बारtamp, uपूर्णांक64_t ref_बारtamp)
अणु
	बारtamp |= (ref_बारtamp & (0xffULL << 56));

	अगर (बारtamp < ref_बारtamp) अणु
		अगर (ref_बारtamp - बारtamp > (1ULL << 55))
			बारtamp += (1ULL << 56);
	पूर्ण अन्यथा अणु
		अगर (बारtamp - ref_बारtamp > (1ULL << 55))
			बारtamp -= (1ULL << 56);
	पूर्ण

	वापस बारtamp;
पूर्ण

अटल व्योम पूर्णांकel_pt_calc_tsc_बारtamp(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	uपूर्णांक64_t बारtamp;

	decoder->have_पंचांगa = false;

	अगर (decoder->ref_बारtamp) अणु
		बारtamp = पूर्णांकel_pt_8b_tsc(decoder->packet.payload,
					    decoder->ref_बारtamp);
		decoder->tsc_बारtamp = बारtamp;
		decoder->बारtamp = बारtamp;
		decoder->ref_बारtamp = 0;
		decoder->बारtamp_insn_cnt = 0;
	पूर्ण अन्यथा अगर (decoder->बारtamp) अणु
		बारtamp = decoder->packet.payload |
			    (decoder->बारtamp & (0xffULL << 56));
		decoder->tsc_बारtamp = बारtamp;
		अगर (बारtamp < decoder->बारtamp &&
		    decoder->बारtamp - बारtamp < decoder->tsc_slip) अणु
			पूर्णांकel_pt_log_to("Suppressing backwards timestamp",
					बारtamp);
			बारtamp = decoder->बारtamp;
		पूर्ण
		अगर (बारtamp < decoder->बारtamp) अणु
			पूर्णांकel_pt_log_to("Wraparound timestamp", बारtamp);
			बारtamp += (1ULL << 56);
			decoder->tsc_बारtamp = बारtamp;
		पूर्ण
		decoder->बारtamp = बारtamp;
		decoder->बारtamp_insn_cnt = 0;
	पूर्ण

	अगर (decoder->last_packet_type == INTEL_PT_CYC) अणु
		decoder->cyc_ref_बारtamp = decoder->बारtamp;
		decoder->cycle_cnt = 0;
		decoder->have_calc_cyc_to_tsc = false;
		पूर्णांकel_pt_calc_cyc_to_tsc(decoder, false);
	पूर्ण

	पूर्णांकel_pt_log_to("Setting timestamp", decoder->बारtamp);
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_overflow(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	पूर्णांकel_pt_log("ERROR: Buffer overflow\n");
	पूर्णांकel_pt_clear_tx_flags(decoder);
	पूर्णांकel_pt_set_nr(decoder);
	decoder->बारtamp_insn_cnt = 0;
	decoder->pkt_state = INTEL_PT_STATE_ERR_RESYNC;
	decoder->overflow = true;
	वापस -EOVERFLOW;
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_pt_mtc_cyc_cnt_pge(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	अगर (decoder->have_cyc)
		वापस;

	decoder->cyc_cnt_बारtamp = decoder->बारtamp;
	decoder->base_cyc_cnt = decoder->tot_cyc_cnt;
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_pt_mtc_cyc_cnt_cbr(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	decoder->tsc_to_cyc = decoder->cbr / decoder->max_non_turbo_ratio_fp;

	अगर (decoder->pge)
		पूर्णांकel_pt_mtc_cyc_cnt_pge(decoder);
पूर्ण

अटल अंतरभूत व्योम पूर्णांकel_pt_mtc_cyc_cnt_upd(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	uपूर्णांक64_t tot_cyc_cnt, tsc_delta;

	अगर (decoder->have_cyc)
		वापस;

	decoder->sample_cyc = true;

	अगर (!decoder->pge || decoder->बारtamp <= decoder->cyc_cnt_बारtamp)
		वापस;

	tsc_delta = decoder->बारtamp - decoder->cyc_cnt_बारtamp;
	tot_cyc_cnt = tsc_delta * decoder->tsc_to_cyc + decoder->base_cyc_cnt;

	अगर (tot_cyc_cnt > decoder->tot_cyc_cnt)
		decoder->tot_cyc_cnt = tot_cyc_cnt;
पूर्ण

अटल व्योम पूर्णांकel_pt_calc_पंचांगa(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	uपूर्णांक32_t ctc = decoder->packet.payload;
	uपूर्णांक32_t fc = decoder->packet.count;
	uपूर्णांक32_t ctc_rem = ctc & decoder->ctc_rem_mask;

	अगर (!decoder->tsc_ctc_ratio_d)
		वापस;

	अगर (decoder->pge && !decoder->in_psb)
		पूर्णांकel_pt_mtc_cyc_cnt_pge(decoder);
	अन्यथा
		पूर्णांकel_pt_mtc_cyc_cnt_upd(decoder);

	decoder->last_mtc = (ctc >> decoder->mtc_shअगरt) & 0xff;
	decoder->ctc_बारtamp = decoder->tsc_बारtamp - fc;
	अगर (decoder->tsc_ctc_mult) अणु
		decoder->ctc_बारtamp -= ctc_rem * decoder->tsc_ctc_mult;
	पूर्ण अन्यथा अणु
		decoder->ctc_बारtamp -= multभाग(ctc_rem,
						  decoder->tsc_ctc_ratio_n,
						  decoder->tsc_ctc_ratio_d);
	पूर्ण
	decoder->ctc_delta = 0;
	decoder->have_पंचांगa = true;
	decoder->fixup_last_mtc = true;
	पूर्णांकel_pt_log("CTC timestamp " x64_fmt " last MTC %#x  CTC rem %#x\n",
		     decoder->ctc_बारtamp, decoder->last_mtc, ctc_rem);
पूर्ण

अटल व्योम पूर्णांकel_pt_calc_mtc_बारtamp(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	uपूर्णांक64_t बारtamp;
	uपूर्णांक32_t mtc, mtc_delta;

	अगर (!decoder->have_पंचांगa)
		वापस;

	mtc = decoder->packet.payload;

	अगर (decoder->mtc_shअगरt > 8 && decoder->fixup_last_mtc) अणु
		decoder->fixup_last_mtc = false;
		पूर्णांकel_pt_fixup_last_mtc(mtc, decoder->mtc_shअगरt,
					&decoder->last_mtc);
	पूर्ण

	अगर (mtc > decoder->last_mtc)
		mtc_delta = mtc - decoder->last_mtc;
	अन्यथा
		mtc_delta = mtc + 256 - decoder->last_mtc;

	decoder->ctc_delta += mtc_delta << decoder->mtc_shअगरt;

	अगर (decoder->tsc_ctc_mult) अणु
		बारtamp = decoder->ctc_बारtamp +
			    decoder->ctc_delta * decoder->tsc_ctc_mult;
	पूर्ण अन्यथा अणु
		बारtamp = decoder->ctc_बारtamp +
			    multभाग(decoder->ctc_delta,
				    decoder->tsc_ctc_ratio_n,
				    decoder->tsc_ctc_ratio_d);
	पूर्ण

	अगर (बारtamp < decoder->बारtamp)
		पूर्णांकel_pt_log("Suppressing MTC timestamp " x64_fmt " less than current timestamp " x64_fmt "\n",
			     बारtamp, decoder->बारtamp);
	अन्यथा
		decoder->बारtamp = बारtamp;

	पूर्णांकel_pt_mtc_cyc_cnt_upd(decoder);

	decoder->बारtamp_insn_cnt = 0;
	decoder->last_mtc = mtc;

	अगर (decoder->last_packet_type == INTEL_PT_CYC) अणु
		decoder->cyc_ref_बारtamp = decoder->बारtamp;
		decoder->cycle_cnt = 0;
		decoder->have_calc_cyc_to_tsc = false;
		पूर्णांकel_pt_calc_cyc_to_tsc(decoder, true);
	पूर्ण

	पूर्णांकel_pt_log_to("Setting timestamp", decoder->बारtamp);
पूर्ण

अटल व्योम पूर्णांकel_pt_calc_cbr(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	अचिन्हित पूर्णांक cbr = decoder->packet.payload & 0xff;

	decoder->cbr_payload = decoder->packet.payload;

	अगर (decoder->cbr == cbr)
		वापस;

	decoder->cbr = cbr;
	decoder->cbr_cyc_to_tsc = decoder->max_non_turbo_ratio_fp / cbr;

	पूर्णांकel_pt_mtc_cyc_cnt_cbr(decoder);
पूर्ण

अटल व्योम पूर्णांकel_pt_calc_cyc_बारtamp(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	uपूर्णांक64_t बारtamp = decoder->cyc_ref_बारtamp;

	decoder->have_cyc = true;

	decoder->cycle_cnt += decoder->packet.payload;
	अगर (decoder->pge)
		decoder->tot_cyc_cnt += decoder->packet.payload;
	decoder->sample_cyc = true;

	अगर (!decoder->cyc_ref_बारtamp)
		वापस;

	अगर (decoder->have_calc_cyc_to_tsc)
		बारtamp += decoder->cycle_cnt * decoder->calc_cyc_to_tsc;
	अन्यथा अगर (decoder->cbr)
		बारtamp += decoder->cycle_cnt * decoder->cbr_cyc_to_tsc;
	अन्यथा
		वापस;

	अगर (बारtamp < decoder->बारtamp)
		पूर्णांकel_pt_log("Suppressing CYC timestamp " x64_fmt " less than current timestamp " x64_fmt "\n",
			     बारtamp, decoder->बारtamp);
	अन्यथा
		decoder->बारtamp = बारtamp;

	decoder->बारtamp_insn_cnt = 0;

	पूर्णांकel_pt_log_to("Setting timestamp", decoder->बारtamp);
पूर्ण

अटल व्योम पूर्णांकel_pt_bbp(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	अगर (decoder->prev_pkt_ctx == INTEL_PT_NO_CTX) अणु
		स_रखो(decoder->state.items.mask, 0, माप(decoder->state.items.mask));
		decoder->state.items.is_32_bit = false;
	पूर्ण
	decoder->blk_type = decoder->packet.payload;
	decoder->blk_type_pos = पूर्णांकel_pt_blk_type_pos(decoder->blk_type);
	अगर (decoder->blk_type == INTEL_PT_GP_REGS)
		decoder->state.items.is_32_bit = decoder->packet.count;
	अगर (decoder->blk_type_pos < 0) अणु
		पूर्णांकel_pt_log("WARNING: Unknown block type %u\n",
			     decoder->blk_type);
	पूर्ण अन्यथा अगर (decoder->state.items.mask[decoder->blk_type_pos]) अणु
		पूर्णांकel_pt_log("WARNING: Duplicate block type %u\n",
			     decoder->blk_type);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_pt_bip(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	uपूर्णांक32_t id = decoder->packet.count;
	uपूर्णांक32_t bit = 1 << id;
	पूर्णांक pos = decoder->blk_type_pos;

	अगर (pos < 0 || id >= INTEL_PT_BLK_ITEM_ID_CNT) अणु
		पूर्णांकel_pt_log("WARNING: Unknown block item %u type %d\n",
			     id, decoder->blk_type);
		वापस;
	पूर्ण

	अगर (decoder->state.items.mask[pos] & bit) अणु
		पूर्णांकel_pt_log("WARNING: Duplicate block item %u type %d\n",
			     id, decoder->blk_type);
	पूर्ण

	decoder->state.items.mask[pos] |= bit;
	decoder->state.items.val[pos][id] = decoder->packet.payload;
पूर्ण

/* Walk PSB+ packets when alपढ़ोy in sync. */
अटल पूर्णांक पूर्णांकel_pt_walk_psbend(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	पूर्णांक err;

	decoder->in_psb = true;

	जबतक (1) अणु
		err = पूर्णांकel_pt_get_next_packet(decoder);
		अगर (err)
			जाओ out;

		चयन (decoder->packet.type) अणु
		हाल INTEL_PT_PSBEND:
			err = 0;
			जाओ out;

		हाल INTEL_PT_TIP_PGD:
		हाल INTEL_PT_TIP_PGE:
		हाल INTEL_PT_TIP:
		हाल INTEL_PT_TNT:
		हाल INTEL_PT_TRACESTOP:
		हाल INTEL_PT_BAD:
		हाल INTEL_PT_PSB:
		हाल INTEL_PT_PTWRITE:
		हाल INTEL_PT_PTWRITE_IP:
		हाल INTEL_PT_EXSTOP:
		हाल INTEL_PT_EXSTOP_IP:
		हाल INTEL_PT_MWAIT:
		हाल INTEL_PT_PWRE:
		हाल INTEL_PT_PWRX:
		हाल INTEL_PT_BBP:
		हाल INTEL_PT_BIP:
		हाल INTEL_PT_BEP:
		हाल INTEL_PT_BEP_IP:
			decoder->have_पंचांगa = false;
			पूर्णांकel_pt_log("ERROR: Unexpected packet\n");
			err = -EAGAIN;
			जाओ out;

		हाल INTEL_PT_OVF:
			err = पूर्णांकel_pt_overflow(decoder);
			जाओ out;

		हाल INTEL_PT_TSC:
			पूर्णांकel_pt_calc_tsc_बारtamp(decoder);
			अवरोध;

		हाल INTEL_PT_TMA:
			पूर्णांकel_pt_calc_पंचांगa(decoder);
			अवरोध;

		हाल INTEL_PT_CBR:
			पूर्णांकel_pt_calc_cbr(decoder);
			अवरोध;

		हाल INTEL_PT_MODE_EXEC:
			decoder->exec_mode = decoder->packet.payload;
			अवरोध;

		हाल INTEL_PT_PIP:
			पूर्णांकel_pt_set_pip(decoder);
			अवरोध;

		हाल INTEL_PT_FUP:
			decoder->pge = true;
			अगर (decoder->packet.count) अणु
				पूर्णांकel_pt_set_last_ip(decoder);
				decoder->psb_ip = decoder->last_ip;
			पूर्ण
			अवरोध;

		हाल INTEL_PT_MODE_TSX:
			पूर्णांकel_pt_update_in_tx(decoder);
			अवरोध;

		हाल INTEL_PT_MTC:
			पूर्णांकel_pt_calc_mtc_बारtamp(decoder);
			अगर (decoder->period_type == INTEL_PT_PERIOD_MTC)
				decoder->state.type |= INTEL_PT_INSTRUCTION;
			अवरोध;

		हाल INTEL_PT_CYC:
			पूर्णांकel_pt_calc_cyc_बारtamp(decoder);
			अवरोध;

		हाल INTEL_PT_VMCS:
		हाल INTEL_PT_MNT:
		हाल INTEL_PT_PAD:
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
out:
	decoder->in_psb = false;

	वापस err;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_walk_fup_tip(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	पूर्णांक err;

	अगर (decoder->tx_flags & INTEL_PT_ABORT_TX) अणु
		decoder->tx_flags = 0;
		decoder->state.flags &= ~INTEL_PT_IN_TX;
		decoder->state.flags |= INTEL_PT_ABORT_TX;
	पूर्ण अन्यथा अणु
		decoder->state.flags |= INTEL_PT_ASYNC;
	पूर्ण

	जबतक (1) अणु
		err = पूर्णांकel_pt_get_next_packet(decoder);
		अगर (err)
			वापस err;

		चयन (decoder->packet.type) अणु
		हाल INTEL_PT_TNT:
		हाल INTEL_PT_FUP:
		हाल INTEL_PT_TRACESTOP:
		हाल INTEL_PT_PSB:
		हाल INTEL_PT_TSC:
		हाल INTEL_PT_TMA:
		हाल INTEL_PT_MODE_TSX:
		हाल INTEL_PT_BAD:
		हाल INTEL_PT_PSBEND:
		हाल INTEL_PT_PTWRITE:
		हाल INTEL_PT_PTWRITE_IP:
		हाल INTEL_PT_EXSTOP:
		हाल INTEL_PT_EXSTOP_IP:
		हाल INTEL_PT_MWAIT:
		हाल INTEL_PT_PWRE:
		हाल INTEL_PT_PWRX:
		हाल INTEL_PT_BBP:
		हाल INTEL_PT_BIP:
		हाल INTEL_PT_BEP:
		हाल INTEL_PT_BEP_IP:
			पूर्णांकel_pt_log("ERROR: Missing TIP after FUP\n");
			decoder->pkt_state = INTEL_PT_STATE_ERR3;
			decoder->pkt_step = 0;
			वापस -ENOENT;

		हाल INTEL_PT_CBR:
			पूर्णांकel_pt_calc_cbr(decoder);
			अवरोध;

		हाल INTEL_PT_OVF:
			वापस पूर्णांकel_pt_overflow(decoder);

		हाल INTEL_PT_TIP_PGD:
			decoder->state.from_ip = decoder->ip;
			अगर (decoder->packet.count == 0) अणु
				decoder->state.to_ip = 0;
			पूर्ण अन्यथा अणु
				पूर्णांकel_pt_set_ip(decoder);
				decoder->state.to_ip = decoder->ip;
			पूर्ण
			decoder->pge = false;
			decoder->continuous_period = false;
			decoder->state.type |= INTEL_PT_TRACE_END;
			पूर्णांकel_pt_update_nr(decoder);
			वापस 0;

		हाल INTEL_PT_TIP_PGE:
			decoder->pge = true;
			पूर्णांकel_pt_log("Omitting PGE ip " x64_fmt "\n",
				     decoder->ip);
			decoder->state.from_ip = 0;
			अगर (decoder->packet.count == 0) अणु
				decoder->state.to_ip = 0;
			पूर्ण अन्यथा अणु
				पूर्णांकel_pt_set_ip(decoder);
				decoder->state.to_ip = decoder->ip;
			पूर्ण
			decoder->state.type |= INTEL_PT_TRACE_BEGIN;
			पूर्णांकel_pt_mtc_cyc_cnt_pge(decoder);
			पूर्णांकel_pt_set_nr(decoder);
			वापस 0;

		हाल INTEL_PT_TIP:
			decoder->state.from_ip = decoder->ip;
			अगर (decoder->packet.count == 0) अणु
				decoder->state.to_ip = 0;
			पूर्ण अन्यथा अणु
				पूर्णांकel_pt_set_ip(decoder);
				decoder->state.to_ip = decoder->ip;
			पूर्ण
			पूर्णांकel_pt_update_nr(decoder);
			वापस 0;

		हाल INTEL_PT_PIP:
			पूर्णांकel_pt_update_pip(decoder);
			अवरोध;

		हाल INTEL_PT_MTC:
			पूर्णांकel_pt_calc_mtc_बारtamp(decoder);
			अगर (decoder->period_type == INTEL_PT_PERIOD_MTC)
				decoder->state.type |= INTEL_PT_INSTRUCTION;
			अवरोध;

		हाल INTEL_PT_CYC:
			पूर्णांकel_pt_calc_cyc_बारtamp(decoder);
			अवरोध;

		हाल INTEL_PT_MODE_EXEC:
			decoder->exec_mode = decoder->packet.payload;
			अवरोध;

		हाल INTEL_PT_VMCS:
		हाल INTEL_PT_MNT:
		हाल INTEL_PT_PAD:
			अवरोध;

		शेष:
			वापस पूर्णांकel_pt_bug(decoder);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_resample(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	decoder->pkt_state = INTEL_PT_STATE_IN_SYNC;
	decoder->state.type = INTEL_PT_INSTRUCTION;
	decoder->state.from_ip = decoder->ip;
	decoder->state.to_ip = 0;
	वापस 0;
पूर्ण

#घोषणा HOP_PROCESS	0
#घोषणा HOP_IGNORE	1
#घोषणा HOP_RETURN	2
#घोषणा HOP_AGAIN	3

अटल पूर्णांक पूर्णांकel_pt_scan_क्रम_psb(काष्ठा पूर्णांकel_pt_decoder *decoder);

/* Hop mode: Ignore TNT, करो not walk code, but get ip from FUPs and TIPs */
अटल पूर्णांक पूर्णांकel_pt_hop_trace(काष्ठा पूर्णांकel_pt_decoder *decoder, bool *no_tip, पूर्णांक *err)
अणु
	/* Leap from PSB to PSB, getting ip from FUP within PSB+ */
	अगर (decoder->leap && !decoder->in_psb && decoder->packet.type != INTEL_PT_PSB) अणु
		*err = पूर्णांकel_pt_scan_क्रम_psb(decoder);
		अगर (*err)
			वापस HOP_RETURN;
	पूर्ण

	चयन (decoder->packet.type) अणु
	हाल INTEL_PT_TNT:
		वापस HOP_IGNORE;

	हाल INTEL_PT_TIP_PGD:
		अगर (!decoder->packet.count) अणु
			पूर्णांकel_pt_set_nr(decoder);
			वापस HOP_IGNORE;
		पूर्ण
		पूर्णांकel_pt_set_ip(decoder);
		decoder->state.type |= INTEL_PT_TRACE_END;
		decoder->state.from_ip = 0;
		decoder->state.to_ip = decoder->ip;
		पूर्णांकel_pt_update_nr(decoder);
		वापस HOP_RETURN;

	हाल INTEL_PT_TIP:
		अगर (!decoder->packet.count) अणु
			पूर्णांकel_pt_set_nr(decoder);
			वापस HOP_IGNORE;
		पूर्ण
		पूर्णांकel_pt_set_ip(decoder);
		decoder->state.type = INTEL_PT_INSTRUCTION;
		decoder->state.from_ip = decoder->ip;
		decoder->state.to_ip = 0;
		पूर्णांकel_pt_update_nr(decoder);
		वापस HOP_RETURN;

	हाल INTEL_PT_FUP:
		अगर (!decoder->packet.count)
			वापस HOP_IGNORE;
		पूर्णांकel_pt_set_ip(decoder);
		अगर (पूर्णांकel_pt_fup_event(decoder))
			वापस HOP_RETURN;
		अगर (!decoder->branch_enable)
			*no_tip = true;
		अगर (*no_tip) अणु
			decoder->state.type = INTEL_PT_INSTRUCTION;
			decoder->state.from_ip = decoder->ip;
			decoder->state.to_ip = 0;
			वापस HOP_RETURN;
		पूर्ण
		*err = पूर्णांकel_pt_walk_fup_tip(decoder);
		अगर (!*err)
			decoder->pkt_state = INTEL_PT_STATE_RESAMPLE;
		वापस HOP_RETURN;

	हाल INTEL_PT_PSB:
		decoder->state.psb_offset = decoder->pos;
		decoder->psb_ip = 0;
		decoder->last_ip = 0;
		decoder->have_last_ip = true;
		*err = पूर्णांकel_pt_walk_psbend(decoder);
		अगर (*err == -EAGAIN)
			वापस HOP_AGAIN;
		अगर (*err)
			वापस HOP_RETURN;
		decoder->state.type = INTEL_PT_PSB_EVT;
		अगर (decoder->psb_ip) अणु
			decoder->state.type |= INTEL_PT_INSTRUCTION;
			decoder->ip = decoder->psb_ip;
		पूर्ण
		decoder->state.from_ip = decoder->psb_ip;
		decoder->state.to_ip = 0;
		वापस HOP_RETURN;

	हाल INTEL_PT_BAD:
	हाल INTEL_PT_PAD:
	हाल INTEL_PT_TIP_PGE:
	हाल INTEL_PT_TSC:
	हाल INTEL_PT_TMA:
	हाल INTEL_PT_MODE_EXEC:
	हाल INTEL_PT_MODE_TSX:
	हाल INTEL_PT_MTC:
	हाल INTEL_PT_CYC:
	हाल INTEL_PT_VMCS:
	हाल INTEL_PT_PSBEND:
	हाल INTEL_PT_CBR:
	हाल INTEL_PT_TRACESTOP:
	हाल INTEL_PT_PIP:
	हाल INTEL_PT_OVF:
	हाल INTEL_PT_MNT:
	हाल INTEL_PT_PTWRITE:
	हाल INTEL_PT_PTWRITE_IP:
	हाल INTEL_PT_EXSTOP:
	हाल INTEL_PT_EXSTOP_IP:
	हाल INTEL_PT_MWAIT:
	हाल INTEL_PT_PWRE:
	हाल INTEL_PT_PWRX:
	हाल INTEL_PT_BBP:
	हाल INTEL_PT_BIP:
	हाल INTEL_PT_BEP:
	हाल INTEL_PT_BEP_IP:
	शेष:
		वापस HOP_PROCESS;
	पूर्ण
पूर्ण

काष्ठा पूर्णांकel_pt_psb_info अणु
	काष्ठा पूर्णांकel_pt_pkt fup_packet;
	bool fup;
	पूर्णांक after_psbend;
पूर्ण;

/* Lookahead and get the FUP packet from PSB+ */
अटल पूर्णांक पूर्णांकel_pt_psb_lookahead_cb(काष्ठा पूर्णांकel_pt_pkt_info *pkt_info)
अणु
	काष्ठा पूर्णांकel_pt_psb_info *data = pkt_info->data;

	चयन (pkt_info->packet.type) अणु
	हाल INTEL_PT_PAD:
	हाल INTEL_PT_MNT:
	हाल INTEL_PT_TSC:
	हाल INTEL_PT_TMA:
	हाल INTEL_PT_MODE_EXEC:
	हाल INTEL_PT_MODE_TSX:
	हाल INTEL_PT_MTC:
	हाल INTEL_PT_CYC:
	हाल INTEL_PT_VMCS:
	हाल INTEL_PT_CBR:
	हाल INTEL_PT_PIP:
		अगर (data->after_psbend) अणु
			data->after_psbend -= 1;
			अगर (!data->after_psbend)
				वापस 1;
		पूर्ण
		अवरोध;

	हाल INTEL_PT_FUP:
		अगर (data->after_psbend)
			वापस 1;
		अगर (data->fup || pkt_info->packet.count == 0)
			वापस 1;
		data->fup_packet = pkt_info->packet;
		data->fup = true;
		अवरोध;

	हाल INTEL_PT_PSBEND:
		अगर (!data->fup)
			वापस 1;
		/* Keep going to check क्रम a TIP.PGE */
		data->after_psbend = 6;
		अवरोध;

	हाल INTEL_PT_TIP_PGE:
		/* Ignore FUP in PSB+ अगर followed by TIP.PGE */
		अगर (data->after_psbend)
			data->fup = false;
		वापस 1;

	हाल INTEL_PT_PTWRITE:
	हाल INTEL_PT_PTWRITE_IP:
	हाल INTEL_PT_EXSTOP:
	हाल INTEL_PT_EXSTOP_IP:
	हाल INTEL_PT_MWAIT:
	हाल INTEL_PT_PWRE:
	हाल INTEL_PT_PWRX:
	हाल INTEL_PT_BBP:
	हाल INTEL_PT_BIP:
	हाल INTEL_PT_BEP:
	हाल INTEL_PT_BEP_IP:
		अगर (data->after_psbend) अणु
			data->after_psbend -= 1;
			अगर (!data->after_psbend)
				वापस 1;
			अवरोध;
		पूर्ण
		वापस 1;

	हाल INTEL_PT_OVF:
	हाल INTEL_PT_BAD:
	हाल INTEL_PT_TNT:
	हाल INTEL_PT_TIP_PGD:
	हाल INTEL_PT_TIP:
	हाल INTEL_PT_PSB:
	हाल INTEL_PT_TRACESTOP:
	शेष:
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_psb(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	पूर्णांक err;

	decoder->last_ip = 0;
	decoder->psb_ip = 0;
	decoder->have_last_ip = true;
	पूर्णांकel_pt_clear_stack(&decoder->stack);
	err = पूर्णांकel_pt_walk_psbend(decoder);
	अगर (err)
		वापस err;
	decoder->state.type = INTEL_PT_PSB_EVT;
	decoder->state.from_ip = decoder->psb_ip;
	decoder->state.to_ip = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_fup_in_psb(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	पूर्णांक err;

	अगर (decoder->ip != decoder->last_ip) अणु
		err = पूर्णांकel_pt_walk_fup(decoder);
		अगर (!err || err != -EAGAIN)
			वापस err;
	पूर्ण

	decoder->pkt_state = INTEL_PT_STATE_IN_SYNC;
	err = पूर्णांकel_pt_psb(decoder);
	अगर (err) अणु
		decoder->pkt_state = INTEL_PT_STATE_ERR3;
		वापस -ENOENT;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool पूर्णांकel_pt_psb_with_fup(काष्ठा पूर्णांकel_pt_decoder *decoder, पूर्णांक *err)
अणु
	काष्ठा पूर्णांकel_pt_psb_info data = अणु .fup = false पूर्ण;

	अगर (!decoder->branch_enable || !decoder->pge)
		वापस false;

	पूर्णांकel_pt_pkt_lookahead(decoder, पूर्णांकel_pt_psb_lookahead_cb, &data);
	अगर (!data.fup)
		वापस false;

	decoder->packet = data.fup_packet;
	पूर्णांकel_pt_set_last_ip(decoder);
	decoder->pkt_state = INTEL_PT_STATE_FUP_IN_PSB;

	*err = पूर्णांकel_pt_fup_in_psb(decoder);

	वापस true;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_walk_trace(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	पूर्णांक last_packet_type = INTEL_PT_PAD;
	bool no_tip = false;
	पूर्णांक err;

	जबतक (1) अणु
		err = पूर्णांकel_pt_get_next_packet(decoder);
		अगर (err)
			वापस err;
next:
		अगर (decoder->cyc_threshold) अणु
			अगर (decoder->sample_cyc && last_packet_type != INTEL_PT_CYC)
				decoder->sample_cyc = false;
			last_packet_type = decoder->packet.type;
		पूर्ण

		अगर (decoder->hop) अणु
			चयन (पूर्णांकel_pt_hop_trace(decoder, &no_tip, &err)) अणु
			हाल HOP_IGNORE:
				जारी;
			हाल HOP_RETURN:
				वापस err;
			हाल HOP_AGAIN:
				जाओ next;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण

		चयन (decoder->packet.type) अणु
		हाल INTEL_PT_TNT:
			अगर (!decoder->packet.count)
				अवरोध;
			decoder->tnt = decoder->packet;
			decoder->pkt_state = INTEL_PT_STATE_TNT;
			err = पूर्णांकel_pt_walk_tnt(decoder);
			अगर (err == -EAGAIN)
				अवरोध;
			वापस err;

		हाल INTEL_PT_TIP_PGD:
			अगर (decoder->packet.count != 0)
				पूर्णांकel_pt_set_last_ip(decoder);
			decoder->pkt_state = INTEL_PT_STATE_TIP_PGD;
			वापस पूर्णांकel_pt_walk_tip(decoder);

		हाल INTEL_PT_TIP_PGE: अणु
			decoder->pge = true;
			पूर्णांकel_pt_mtc_cyc_cnt_pge(decoder);
			पूर्णांकel_pt_set_nr(decoder);
			अगर (decoder->packet.count == 0) अणु
				पूर्णांकel_pt_log_at("Skipping zero TIP.PGE",
						decoder->pos);
				अवरोध;
			पूर्ण
			पूर्णांकel_pt_set_ip(decoder);
			decoder->state.from_ip = 0;
			decoder->state.to_ip = decoder->ip;
			decoder->state.type |= INTEL_PT_TRACE_BEGIN;
			/*
			 * In hop mode, resample to get the to_ip as an
			 * "instruction" sample.
			 */
			अगर (decoder->hop)
				decoder->pkt_state = INTEL_PT_STATE_RESAMPLE;
			वापस 0;
		पूर्ण

		हाल INTEL_PT_OVF:
			वापस पूर्णांकel_pt_overflow(decoder);

		हाल INTEL_PT_TIP:
			अगर (decoder->packet.count != 0)
				पूर्णांकel_pt_set_last_ip(decoder);
			decoder->pkt_state = INTEL_PT_STATE_TIP;
			वापस पूर्णांकel_pt_walk_tip(decoder);

		हाल INTEL_PT_FUP:
			अगर (decoder->packet.count == 0) अणु
				पूर्णांकel_pt_log_at("Skipping zero FUP",
						decoder->pos);
				no_tip = false;
				अवरोध;
			पूर्ण
			पूर्णांकel_pt_set_last_ip(decoder);
			अगर (!decoder->branch_enable) अणु
				decoder->ip = decoder->last_ip;
				अगर (पूर्णांकel_pt_fup_event(decoder))
					वापस 0;
				no_tip = false;
				अवरोध;
			पूर्ण
			अगर (decoder->set_fup_mरुको)
				no_tip = true;
			अगर (no_tip)
				decoder->pkt_state = INTEL_PT_STATE_FUP_NO_TIP;
			अन्यथा
				decoder->pkt_state = INTEL_PT_STATE_FUP;
			err = पूर्णांकel_pt_walk_fup(decoder);
			अगर (err != -EAGAIN)
				वापस err;
			अगर (no_tip) अणु
				no_tip = false;
				अवरोध;
			पूर्ण
			वापस पूर्णांकel_pt_walk_fup_tip(decoder);

		हाल INTEL_PT_TRACESTOP:
			decoder->pge = false;
			decoder->continuous_period = false;
			पूर्णांकel_pt_clear_tx_flags(decoder);
			decoder->have_पंचांगa = false;
			अवरोध;

		हाल INTEL_PT_PSB:
			decoder->state.psb_offset = decoder->pos;
			decoder->psb_ip = 0;
			अगर (पूर्णांकel_pt_psb_with_fup(decoder, &err))
				वापस err;
			err = पूर्णांकel_pt_psb(decoder);
			अगर (err == -EAGAIN)
				जाओ next;
			वापस err;

		हाल INTEL_PT_PIP:
			पूर्णांकel_pt_update_pip(decoder);
			अवरोध;

		हाल INTEL_PT_MTC:
			पूर्णांकel_pt_calc_mtc_बारtamp(decoder);
			अगर (decoder->period_type != INTEL_PT_PERIOD_MTC)
				अवरोध;
			/*
			 * Ensure that there has been an inकाष्ठाion since the
			 * last MTC.
			 */
			अगर (!decoder->mtc_insn)
				अवरोध;
			decoder->mtc_insn = false;
			/* Ensure that there is a बारtamp */
			अगर (!decoder->बारtamp)
				अवरोध;
			decoder->state.type = INTEL_PT_INSTRUCTION;
			decoder->state.from_ip = decoder->ip;
			decoder->state.to_ip = 0;
			decoder->mtc_insn = false;
			वापस 0;

		हाल INTEL_PT_TSC:
			पूर्णांकel_pt_calc_tsc_बारtamp(decoder);
			अवरोध;

		हाल INTEL_PT_TMA:
			पूर्णांकel_pt_calc_पंचांगa(decoder);
			अवरोध;

		हाल INTEL_PT_CYC:
			पूर्णांकel_pt_calc_cyc_बारtamp(decoder);
			अवरोध;

		हाल INTEL_PT_CBR:
			पूर्णांकel_pt_calc_cbr(decoder);
			अगर (decoder->cbr != decoder->cbr_seen) अणु
				decoder->state.type = 0;
				वापस 0;
			पूर्ण
			अवरोध;

		हाल INTEL_PT_MODE_EXEC:
			decoder->exec_mode = decoder->packet.payload;
			अवरोध;

		हाल INTEL_PT_MODE_TSX:
			/* MODE_TSX need not be followed by FUP */
			अगर (!decoder->pge || decoder->in_psb) अणु
				पूर्णांकel_pt_update_in_tx(decoder);
				अवरोध;
			पूर्ण
			err = पूर्णांकel_pt_mode_tsx(decoder, &no_tip);
			अगर (err)
				वापस err;
			जाओ next;

		हाल INTEL_PT_BAD: /* Does not happen */
			वापस पूर्णांकel_pt_bug(decoder);

		हाल INTEL_PT_PSBEND:
		हाल INTEL_PT_VMCS:
		हाल INTEL_PT_MNT:
		हाल INTEL_PT_PAD:
			अवरोध;

		हाल INTEL_PT_PTWRITE_IP:
			decoder->fup_ptw_payload = decoder->packet.payload;
			err = पूर्णांकel_pt_get_next_packet(decoder);
			अगर (err)
				वापस err;
			अगर (decoder->packet.type == INTEL_PT_FUP) अणु
				decoder->set_fup_ptw = true;
				no_tip = true;
			पूर्ण अन्यथा अणु
				पूर्णांकel_pt_log_at("ERROR: Missing FUP after PTWRITE",
						decoder->pos);
			पूर्ण
			जाओ next;

		हाल INTEL_PT_PTWRITE:
			decoder->state.type = INTEL_PT_PTW;
			decoder->state.from_ip = decoder->ip;
			decoder->state.to_ip = 0;
			decoder->state.ptw_payload = decoder->packet.payload;
			वापस 0;

		हाल INTEL_PT_MWAIT:
			decoder->fup_mरुको_payload = decoder->packet.payload;
			decoder->set_fup_mरुको = true;
			अवरोध;

		हाल INTEL_PT_PWRE:
			अगर (decoder->set_fup_mरुको) अणु
				decoder->fup_pwre_payload =
							decoder->packet.payload;
				decoder->set_fup_pwre = true;
				अवरोध;
			पूर्ण
			decoder->state.type = INTEL_PT_PWR_ENTRY;
			decoder->state.from_ip = decoder->ip;
			decoder->state.to_ip = 0;
			decoder->state.pwrx_payload = decoder->packet.payload;
			वापस 0;

		हाल INTEL_PT_EXSTOP_IP:
			err = पूर्णांकel_pt_get_next_packet(decoder);
			अगर (err)
				वापस err;
			अगर (decoder->packet.type == INTEL_PT_FUP) अणु
				decoder->set_fup_exstop = true;
				no_tip = true;
			पूर्ण अन्यथा अणु
				पूर्णांकel_pt_log_at("ERROR: Missing FUP after EXSTOP",
						decoder->pos);
			पूर्ण
			जाओ next;

		हाल INTEL_PT_EXSTOP:
			decoder->state.type = INTEL_PT_EX_STOP;
			decoder->state.from_ip = decoder->ip;
			decoder->state.to_ip = 0;
			वापस 0;

		हाल INTEL_PT_PWRX:
			decoder->state.type = INTEL_PT_PWR_EXIT;
			decoder->state.from_ip = decoder->ip;
			decoder->state.to_ip = 0;
			decoder->state.pwrx_payload = decoder->packet.payload;
			वापस 0;

		हाल INTEL_PT_BBP:
			पूर्णांकel_pt_bbp(decoder);
			अवरोध;

		हाल INTEL_PT_BIP:
			पूर्णांकel_pt_bip(decoder);
			अवरोध;

		हाल INTEL_PT_BEP:
			decoder->state.type = INTEL_PT_BLK_ITEMS;
			decoder->state.from_ip = decoder->ip;
			decoder->state.to_ip = 0;
			वापस 0;

		हाल INTEL_PT_BEP_IP:
			err = पूर्णांकel_pt_get_next_packet(decoder);
			अगर (err)
				वापस err;
			अगर (decoder->packet.type == INTEL_PT_FUP) अणु
				decoder->set_fup_bep = true;
				no_tip = true;
			पूर्ण अन्यथा अणु
				पूर्णांकel_pt_log_at("ERROR: Missing FUP after BEP",
						decoder->pos);
			पूर्ण
			जाओ next;

		शेष:
			वापस पूर्णांकel_pt_bug(decoder);
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत bool पूर्णांकel_pt_have_ip(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	वापस decoder->packet.count &&
	       (decoder->have_last_ip || decoder->packet.count == 3 ||
		decoder->packet.count == 6);
पूर्ण

/* Walk PSB+ packets to get in sync. */
अटल पूर्णांक पूर्णांकel_pt_walk_psb(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	पूर्णांक err;

	decoder->in_psb = true;

	जबतक (1) अणु
		err = पूर्णांकel_pt_get_next_packet(decoder);
		अगर (err)
			जाओ out;

		चयन (decoder->packet.type) अणु
		हाल INTEL_PT_TIP_PGD:
			decoder->continuous_period = false;
			__fallthrough;
		हाल INTEL_PT_TIP_PGE:
		हाल INTEL_PT_TIP:
		हाल INTEL_PT_PTWRITE:
		हाल INTEL_PT_PTWRITE_IP:
		हाल INTEL_PT_EXSTOP:
		हाल INTEL_PT_EXSTOP_IP:
		हाल INTEL_PT_MWAIT:
		हाल INTEL_PT_PWRE:
		हाल INTEL_PT_PWRX:
		हाल INTEL_PT_BBP:
		हाल INTEL_PT_BIP:
		हाल INTEL_PT_BEP:
		हाल INTEL_PT_BEP_IP:
			पूर्णांकel_pt_log("ERROR: Unexpected packet\n");
			err = -ENOENT;
			जाओ out;

		हाल INTEL_PT_FUP:
			decoder->pge = true;
			अगर (पूर्णांकel_pt_have_ip(decoder)) अणु
				uपूर्णांक64_t current_ip = decoder->ip;

				पूर्णांकel_pt_set_ip(decoder);
				decoder->psb_ip = decoder->ip;
				अगर (current_ip)
					पूर्णांकel_pt_log_to("Setting IP",
							decoder->ip);
			पूर्ण
			अवरोध;

		हाल INTEL_PT_MTC:
			पूर्णांकel_pt_calc_mtc_बारtamp(decoder);
			अवरोध;

		हाल INTEL_PT_TSC:
			पूर्णांकel_pt_calc_tsc_बारtamp(decoder);
			अवरोध;

		हाल INTEL_PT_TMA:
			पूर्णांकel_pt_calc_पंचांगa(decoder);
			अवरोध;

		हाल INTEL_PT_CYC:
			पूर्णांकel_pt_calc_cyc_बारtamp(decoder);
			अवरोध;

		हाल INTEL_PT_CBR:
			पूर्णांकel_pt_calc_cbr(decoder);
			अवरोध;

		हाल INTEL_PT_PIP:
			पूर्णांकel_pt_set_pip(decoder);
			अवरोध;

		हाल INTEL_PT_MODE_EXEC:
			decoder->exec_mode = decoder->packet.payload;
			अवरोध;

		हाल INTEL_PT_MODE_TSX:
			पूर्णांकel_pt_update_in_tx(decoder);
			अवरोध;

		हाल INTEL_PT_TRACESTOP:
			decoder->pge = false;
			decoder->continuous_period = false;
			पूर्णांकel_pt_clear_tx_flags(decoder);
			__fallthrough;

		हाल INTEL_PT_TNT:
			decoder->have_पंचांगa = false;
			पूर्णांकel_pt_log("ERROR: Unexpected packet\n");
			अगर (decoder->ip)
				decoder->pkt_state = INTEL_PT_STATE_ERR4;
			अन्यथा
				decoder->pkt_state = INTEL_PT_STATE_ERR3;
			err = -ENOENT;
			जाओ out;

		हाल INTEL_PT_BAD: /* Does not happen */
			err = पूर्णांकel_pt_bug(decoder);
			जाओ out;

		हाल INTEL_PT_OVF:
			err = पूर्णांकel_pt_overflow(decoder);
			जाओ out;

		हाल INTEL_PT_PSBEND:
			err = 0;
			जाओ out;

		हाल INTEL_PT_PSB:
		हाल INTEL_PT_VMCS:
		हाल INTEL_PT_MNT:
		हाल INTEL_PT_PAD:
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
out:
	decoder->in_psb = false;

	वापस err;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_walk_to_ip(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	पूर्णांक err;

	जबतक (1) अणु
		err = पूर्णांकel_pt_get_next_packet(decoder);
		अगर (err)
			वापस err;

		चयन (decoder->packet.type) अणु
		हाल INTEL_PT_TIP_PGD:
			decoder->continuous_period = false;
			decoder->pge = false;
			अगर (पूर्णांकel_pt_have_ip(decoder))
				पूर्णांकel_pt_set_ip(decoder);
			अगर (!decoder->ip)
				अवरोध;
			decoder->state.type |= INTEL_PT_TRACE_END;
			वापस 0;

		हाल INTEL_PT_TIP_PGE:
			decoder->pge = true;
			पूर्णांकel_pt_mtc_cyc_cnt_pge(decoder);
			अगर (पूर्णांकel_pt_have_ip(decoder))
				पूर्णांकel_pt_set_ip(decoder);
			अगर (!decoder->ip)
				अवरोध;
			decoder->state.type |= INTEL_PT_TRACE_BEGIN;
			वापस 0;

		हाल INTEL_PT_TIP:
			decoder->pge = true;
			अगर (पूर्णांकel_pt_have_ip(decoder))
				पूर्णांकel_pt_set_ip(decoder);
			अगर (!decoder->ip)
				अवरोध;
			वापस 0;

		हाल INTEL_PT_FUP:
			अगर (पूर्णांकel_pt_have_ip(decoder))
				पूर्णांकel_pt_set_ip(decoder);
			अगर (decoder->ip)
				वापस 0;
			अवरोध;

		हाल INTEL_PT_MTC:
			पूर्णांकel_pt_calc_mtc_बारtamp(decoder);
			अवरोध;

		हाल INTEL_PT_TSC:
			पूर्णांकel_pt_calc_tsc_बारtamp(decoder);
			अवरोध;

		हाल INTEL_PT_TMA:
			पूर्णांकel_pt_calc_पंचांगa(decoder);
			अवरोध;

		हाल INTEL_PT_CYC:
			पूर्णांकel_pt_calc_cyc_बारtamp(decoder);
			अवरोध;

		हाल INTEL_PT_CBR:
			पूर्णांकel_pt_calc_cbr(decoder);
			अवरोध;

		हाल INTEL_PT_PIP:
			पूर्णांकel_pt_set_pip(decoder);
			अवरोध;

		हाल INTEL_PT_MODE_EXEC:
			decoder->exec_mode = decoder->packet.payload;
			अवरोध;

		हाल INTEL_PT_MODE_TSX:
			पूर्णांकel_pt_update_in_tx(decoder);
			अवरोध;

		हाल INTEL_PT_OVF:
			वापस पूर्णांकel_pt_overflow(decoder);

		हाल INTEL_PT_BAD: /* Does not happen */
			वापस पूर्णांकel_pt_bug(decoder);

		हाल INTEL_PT_TRACESTOP:
			decoder->pge = false;
			decoder->continuous_period = false;
			पूर्णांकel_pt_clear_tx_flags(decoder);
			decoder->have_पंचांगa = false;
			अवरोध;

		हाल INTEL_PT_PSB:
			decoder->state.psb_offset = decoder->pos;
			decoder->psb_ip = 0;
			decoder->last_ip = 0;
			decoder->have_last_ip = true;
			पूर्णांकel_pt_clear_stack(&decoder->stack);
			err = पूर्णांकel_pt_walk_psb(decoder);
			अगर (err)
				वापस err;
			decoder->state.type = INTEL_PT_PSB_EVT;
			decoder->state.from_ip = decoder->psb_ip;
			decoder->state.to_ip = 0;
			वापस 0;

		हाल INTEL_PT_TNT:
		हाल INTEL_PT_PSBEND:
		हाल INTEL_PT_VMCS:
		हाल INTEL_PT_MNT:
		हाल INTEL_PT_PAD:
		हाल INTEL_PT_PTWRITE:
		हाल INTEL_PT_PTWRITE_IP:
		हाल INTEL_PT_EXSTOP:
		हाल INTEL_PT_EXSTOP_IP:
		हाल INTEL_PT_MWAIT:
		हाल INTEL_PT_PWRE:
		हाल INTEL_PT_PWRX:
		हाल INTEL_PT_BBP:
		हाल INTEL_PT_BIP:
		हाल INTEL_PT_BEP:
		हाल INTEL_PT_BEP_IP:
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_sync_ip(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	पूर्णांक err;

	decoder->set_fup_tx_flags = false;
	decoder->set_fup_ptw = false;
	decoder->set_fup_mरुको = false;
	decoder->set_fup_pwre = false;
	decoder->set_fup_exstop = false;
	decoder->set_fup_bep = false;

	अगर (!decoder->branch_enable) अणु
		decoder->pkt_state = INTEL_PT_STATE_IN_SYNC;
		decoder->overflow = false;
		decoder->state.type = 0; /* Do not have a sample */
		वापस 0;
	पूर्ण

	पूर्णांकel_pt_log("Scanning for full IP\n");
	err = पूर्णांकel_pt_walk_to_ip(decoder);
	अगर (err || ((decoder->state.type & INTEL_PT_PSB_EVT) && !decoder->ip))
		वापस err;

	/* In hop mode, resample to get the to_ip as an "instruction" sample */
	अगर (decoder->hop)
		decoder->pkt_state = INTEL_PT_STATE_RESAMPLE;
	अन्यथा
		decoder->pkt_state = INTEL_PT_STATE_IN_SYNC;
	decoder->overflow = false;

	decoder->state.from_ip = 0;
	decoder->state.to_ip = decoder->ip;
	पूर्णांकel_pt_log_to("Setting IP", decoder->ip);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_part_psb(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	स्थिर अचिन्हित अक्षर *end = decoder->buf + decoder->len;
	माप_प्रकार i;

	क्रम (i = INTEL_PT_PSB_LEN - 1; i; i--) अणु
		अगर (i > decoder->len)
			जारी;
		अगर (!स_भेद(end - i, INTEL_PT_PSB_STR, i))
			वापस i;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_rest_psb(काष्ठा पूर्णांकel_pt_decoder *decoder, पूर्णांक part_psb)
अणु
	माप_प्रकार rest_psb = INTEL_PT_PSB_LEN - part_psb;
	स्थिर अक्षर *psb = INTEL_PT_PSB_STR;

	अगर (rest_psb > decoder->len ||
	    स_भेद(decoder->buf, psb + part_psb, rest_psb))
		वापस 0;

	वापस rest_psb;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_get_split_psb(काष्ठा पूर्णांकel_pt_decoder *decoder,
				  पूर्णांक part_psb)
अणु
	पूर्णांक rest_psb, ret;

	decoder->pos += decoder->len;
	decoder->len = 0;

	ret = पूर्णांकel_pt_get_next_data(decoder, false);
	अगर (ret)
		वापस ret;

	rest_psb = पूर्णांकel_pt_rest_psb(decoder, part_psb);
	अगर (!rest_psb)
		वापस 0;

	decoder->pos -= part_psb;
	decoder->next_buf = decoder->buf + rest_psb;
	decoder->next_len = decoder->len - rest_psb;
	स_नकल(decoder->temp_buf, INTEL_PT_PSB_STR, INTEL_PT_PSB_LEN);
	decoder->buf = decoder->temp_buf;
	decoder->len = INTEL_PT_PSB_LEN;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_scan_क्रम_psb(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	अचिन्हित अक्षर *next;
	पूर्णांक ret;

	पूर्णांकel_pt_log("Scanning for PSB\n");
	जबतक (1) अणु
		अगर (!decoder->len) अणु
			ret = पूर्णांकel_pt_get_next_data(decoder, false);
			अगर (ret)
				वापस ret;
		पूर्ण

		next = memmem(decoder->buf, decoder->len, INTEL_PT_PSB_STR,
			      INTEL_PT_PSB_LEN);
		अगर (!next) अणु
			पूर्णांक part_psb;

			part_psb = पूर्णांकel_pt_part_psb(decoder);
			अगर (part_psb) अणु
				ret = पूर्णांकel_pt_get_split_psb(decoder, part_psb);
				अगर (ret)
					वापस ret;
			पूर्ण अन्यथा अणु
				decoder->pos += decoder->len;
				decoder->len = 0;
			पूर्ण
			जारी;
		पूर्ण

		decoder->pkt_step = next - decoder->buf;
		वापस पूर्णांकel_pt_get_next_packet(decoder);
	पूर्ण
पूर्ण

अटल पूर्णांक पूर्णांकel_pt_sync(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	पूर्णांक err;

	decoder->pge = false;
	decoder->continuous_period = false;
	decoder->have_last_ip = false;
	decoder->last_ip = 0;
	decoder->psb_ip = 0;
	decoder->ip = 0;
	पूर्णांकel_pt_clear_stack(&decoder->stack);

	err = पूर्णांकel_pt_scan_क्रम_psb(decoder);
	अगर (err)
		वापस err;

	decoder->have_last_ip = true;
	decoder->pkt_state = INTEL_PT_STATE_NO_IP;

	err = पूर्णांकel_pt_walk_psb(decoder);
	अगर (err)
		वापस err;

	decoder->state.type = INTEL_PT_PSB_EVT; /* Only PSB sample */
	decoder->state.from_ip = decoder->psb_ip;
	decoder->state.to_ip = 0;

	अगर (decoder->ip) अणु
		/*
		 * In hop mode, resample to get the PSB FUP ip as an
		 * "instruction" sample.
		 */
		अगर (decoder->hop)
			decoder->pkt_state = INTEL_PT_STATE_RESAMPLE;
		अन्यथा
			decoder->pkt_state = INTEL_PT_STATE_IN_SYNC;
	पूर्ण

	वापस 0;
पूर्ण

अटल uपूर्णांक64_t पूर्णांकel_pt_est_बारtamp(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	uपूर्णांक64_t est = decoder->sample_insn_cnt << 1;

	अगर (!decoder->cbr || !decoder->max_non_turbo_ratio)
		जाओ out;

	est *= decoder->max_non_turbo_ratio;
	est /= decoder->cbr;
out:
	वापस decoder->sample_बारtamp + est;
पूर्ण

स्थिर काष्ठा पूर्णांकel_pt_state *पूर्णांकel_pt_decode(काष्ठा पूर्णांकel_pt_decoder *decoder)
अणु
	पूर्णांक err;

	करो अणु
		decoder->state.type = INTEL_PT_BRANCH;
		decoder->state.flags = 0;

		चयन (decoder->pkt_state) अणु
		हाल INTEL_PT_STATE_NO_PSB:
			err = पूर्णांकel_pt_sync(decoder);
			अवरोध;
		हाल INTEL_PT_STATE_NO_IP:
			decoder->have_last_ip = false;
			decoder->last_ip = 0;
			decoder->ip = 0;
			__fallthrough;
		हाल INTEL_PT_STATE_ERR_RESYNC:
			err = पूर्णांकel_pt_sync_ip(decoder);
			अवरोध;
		हाल INTEL_PT_STATE_IN_SYNC:
			err = पूर्णांकel_pt_walk_trace(decoder);
			अवरोध;
		हाल INTEL_PT_STATE_TNT:
		हाल INTEL_PT_STATE_TNT_CONT:
			err = पूर्णांकel_pt_walk_tnt(decoder);
			अगर (err == -EAGAIN)
				err = पूर्णांकel_pt_walk_trace(decoder);
			अवरोध;
		हाल INTEL_PT_STATE_TIP:
		हाल INTEL_PT_STATE_TIP_PGD:
			err = पूर्णांकel_pt_walk_tip(decoder);
			अवरोध;
		हाल INTEL_PT_STATE_FUP:
			err = पूर्णांकel_pt_walk_fup(decoder);
			अगर (err == -EAGAIN)
				err = पूर्णांकel_pt_walk_fup_tip(decoder);
			अवरोध;
		हाल INTEL_PT_STATE_FUP_NO_TIP:
			err = पूर्णांकel_pt_walk_fup(decoder);
			अगर (err == -EAGAIN)
				err = पूर्णांकel_pt_walk_trace(decoder);
			अवरोध;
		हाल INTEL_PT_STATE_FUP_IN_PSB:
			err = पूर्णांकel_pt_fup_in_psb(decoder);
			अवरोध;
		हाल INTEL_PT_STATE_RESAMPLE:
			err = पूर्णांकel_pt_resample(decoder);
			अवरोध;
		शेष:
			err = पूर्णांकel_pt_bug(decoder);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (err == -ENOLINK);

	अगर (err) अणु
		decoder->state.err = पूर्णांकel_pt_ext_err(err);
		decoder->state.from_ip = decoder->ip;
		पूर्णांकel_pt_update_sample_समय(decoder);
		decoder->sample_tot_cyc_cnt = decoder->tot_cyc_cnt;
		पूर्णांकel_pt_set_nr(decoder);
	पूर्ण अन्यथा अणु
		decoder->state.err = 0;
		अगर (decoder->cbr != decoder->cbr_seen) अणु
			decoder->cbr_seen = decoder->cbr;
			अगर (!decoder->state.type) अणु
				decoder->state.from_ip = decoder->ip;
				decoder->state.to_ip = 0;
			पूर्ण
			decoder->state.type |= INTEL_PT_CBR_CHG;
			decoder->state.cbr_payload = decoder->cbr_payload;
			decoder->state.cbr = decoder->cbr;
		पूर्ण
		अगर (पूर्णांकel_pt_sample_समय(decoder->pkt_state)) अणु
			पूर्णांकel_pt_update_sample_समय(decoder);
			अगर (decoder->sample_cyc) अणु
				decoder->sample_tot_cyc_cnt = decoder->tot_cyc_cnt;
				decoder->state.flags |= INTEL_PT_SAMPLE_IPC;
				decoder->sample_cyc = false;
			पूर्ण
		पूर्ण
		/*
		 * When using only TSC/MTC to compute cycles, IPC can be
		 * sampled as soon as the cycle count changes.
		 */
		अगर (!decoder->have_cyc)
			decoder->state.flags |= INTEL_PT_SAMPLE_IPC;
	पूर्ण

	 /* Let PSB event always have TSC बारtamp */
	अगर ((decoder->state.type & INTEL_PT_PSB_EVT) && decoder->tsc_बारtamp)
		decoder->sample_बारtamp = decoder->tsc_बारtamp;

	decoder->state.from_nr = decoder->nr;
	decoder->state.to_nr = decoder->next_nr;
	decoder->nr = decoder->next_nr;

	decoder->state.बारtamp = decoder->sample_बारtamp;
	decoder->state.est_बारtamp = पूर्णांकel_pt_est_बारtamp(decoder);
	decoder->state.tot_insn_cnt = decoder->tot_insn_cnt;
	decoder->state.tot_cyc_cnt = decoder->sample_tot_cyc_cnt;

	वापस &decoder->state;
पूर्ण

/**
 * पूर्णांकel_pt_next_psb - move buffer poपूर्णांकer to the start of the next PSB packet.
 * @buf: poपूर्णांकer to buffer poपूर्णांकer
 * @len: size of buffer
 *
 * Updates the buffer poपूर्णांकer to poपूर्णांक to the start of the next PSB packet अगर
 * there is one, otherwise the buffer poपूर्णांकer is unchanged.  If @buf is updated,
 * @len is adjusted accordingly.
 *
 * Return: %true अगर a PSB packet is found, %false otherwise.
 */
अटल bool पूर्णांकel_pt_next_psb(अचिन्हित अक्षर **buf, माप_प्रकार *len)
अणु
	अचिन्हित अक्षर *next;

	next = memmem(*buf, *len, INTEL_PT_PSB_STR, INTEL_PT_PSB_LEN);
	अगर (next) अणु
		*len -= next - *buf;
		*buf = next;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * पूर्णांकel_pt_step_psb - move buffer poपूर्णांकer to the start of the following PSB
 *                     packet.
 * @buf: poपूर्णांकer to buffer poपूर्णांकer
 * @len: size of buffer
 *
 * Updates the buffer poपूर्णांकer to poपूर्णांक to the start of the following PSB packet
 * (skipping the PSB at @buf itself) अगर there is one, otherwise the buffer
 * poपूर्णांकer is unchanged.  If @buf is updated, @len is adjusted accordingly.
 *
 * Return: %true अगर a PSB packet is found, %false otherwise.
 */
अटल bool पूर्णांकel_pt_step_psb(अचिन्हित अक्षर **buf, माप_प्रकार *len)
अणु
	अचिन्हित अक्षर *next;

	अगर (!*len)
		वापस false;

	next = memmem(*buf + 1, *len - 1, INTEL_PT_PSB_STR, INTEL_PT_PSB_LEN);
	अगर (next) अणु
		*len -= next - *buf;
		*buf = next;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * पूर्णांकel_pt_last_psb - find the last PSB packet in a buffer.
 * @buf: buffer
 * @len: size of buffer
 *
 * This function finds the last PSB in a buffer.
 *
 * Return: A poपूर्णांकer to the last PSB in @buf अगर found, %शून्य otherwise.
 */
अटल अचिन्हित अक्षर *पूर्णांकel_pt_last_psb(अचिन्हित अक्षर *buf, माप_प्रकार len)
अणु
	स्थिर अक्षर *n = INTEL_PT_PSB_STR;
	अचिन्हित अक्षर *p;
	माप_प्रकार k;

	अगर (len < INTEL_PT_PSB_LEN)
		वापस शून्य;

	k = len - INTEL_PT_PSB_LEN + 1;
	जबतक (1) अणु
		p = memrchr(buf, n[0], k);
		अगर (!p)
			वापस शून्य;
		अगर (!स_भेद(p + 1, n + 1, INTEL_PT_PSB_LEN - 1))
			वापस p;
		k = p - buf;
		अगर (!k)
			वापस शून्य;
	पूर्ण
पूर्ण

/**
 * पूर्णांकel_pt_next_tsc - find and वापस next TSC.
 * @buf: buffer
 * @len: size of buffer
 * @tsc: TSC value वापसed
 * @rem: वापसs reमुख्यing size when TSC is found
 *
 * Find a TSC packet in @buf and वापस the TSC value.  This function assumes
 * that @buf starts at a PSB and that PSB+ will contain TSC and so stops अगर a
 * PSBEND packet is found.
 *
 * Return: %true अगर TSC is found, false otherwise.
 */
अटल bool पूर्णांकel_pt_next_tsc(अचिन्हित अक्षर *buf, माप_प्रकार len, uपूर्णांक64_t *tsc,
			      माप_प्रकार *rem)
अणु
	क्रमागत पूर्णांकel_pt_pkt_ctx ctx = INTEL_PT_NO_CTX;
	काष्ठा पूर्णांकel_pt_pkt packet;
	पूर्णांक ret;

	जबतक (len) अणु
		ret = पूर्णांकel_pt_get_packet(buf, len, &packet, &ctx);
		अगर (ret <= 0)
			वापस false;
		अगर (packet.type == INTEL_PT_TSC) अणु
			*tsc = packet.payload;
			*rem = len;
			वापस true;
		पूर्ण
		अगर (packet.type == INTEL_PT_PSBEND)
			वापस false;
		buf += ret;
		len -= ret;
	पूर्ण
	वापस false;
पूर्ण

/**
 * पूर्णांकel_pt_tsc_cmp - compare 7-byte TSCs.
 * @tsc1: first TSC to compare
 * @tsc2: second TSC to compare
 *
 * This function compares 7-byte TSC values allowing क्रम the possibility that
 * TSC wrapped around.  Generally it is not possible to know अगर TSC has wrapped
 * around so क्रम that purpose this function assumes the असलolute dअगरference is
 * less than half the maximum dअगरference.
 *
 * Return: %-1 अगर @tsc1 is beक्रमe @tsc2, %0 अगर @tsc1 == @tsc2, %1 अगर @tsc1 is
 * after @tsc2.
 */
अटल पूर्णांक पूर्णांकel_pt_tsc_cmp(uपूर्णांक64_t tsc1, uपूर्णांक64_t tsc2)
अणु
	स्थिर uपूर्णांक64_t halfway = (1ULL << 55);

	अगर (tsc1 == tsc2)
		वापस 0;

	अगर (tsc1 < tsc2) अणु
		अगर (tsc2 - tsc1 < halfway)
			वापस -1;
		अन्यथा
			वापस 1;
	पूर्ण अन्यथा अणु
		अगर (tsc1 - tsc2 < halfway)
			वापस 1;
		अन्यथा
			वापस -1;
	पूर्ण
पूर्ण

#घोषणा MAX_PADDING (PERF_AUXTRACE_RECORD_ALIGNMENT - 1)

/**
 * adj_क्रम_padding - adjust overlap to account क्रम padding.
 * @buf_b: second buffer
 * @buf_a: first buffer
 * @len_a: size of first buffer
 *
 * @buf_a might have up to 7 bytes of padding appended. Adjust the overlap
 * accordingly.
 *
 * Return: A poपूर्णांकer पूर्णांकo @buf_b from where non-overlapped data starts
 */
अटल अचिन्हित अक्षर *adj_क्रम_padding(अचिन्हित अक्षर *buf_b,
				      अचिन्हित अक्षर *buf_a, माप_प्रकार len_a)
अणु
	अचिन्हित अक्षर *p = buf_b - MAX_PADDING;
	अचिन्हित अक्षर *q = buf_a + len_a - MAX_PADDING;
	पूर्णांक i;

	क्रम (i = MAX_PADDING; i; i--, p++, q++) अणु
		अगर (*p != *q)
			अवरोध;
	पूर्ण

	वापस p;
पूर्ण

/**
 * पूर्णांकel_pt_find_overlap_tsc - determine start of non-overlapped trace data
 *                             using TSC.
 * @buf_a: first buffer
 * @len_a: size of first buffer
 * @buf_b: second buffer
 * @len_b: size of second buffer
 * @consecutive: वापसs true अगर there is data in buf_b that is consecutive
 *               to buf_a
 *
 * If the trace contains TSC we can look at the last TSC of @buf_a and the
 * first TSC of @buf_b in order to determine अगर the buffers overlap, and then
 * walk क्रमward in @buf_b until a later TSC is found.  A precondition is that
 * @buf_a and @buf_b are positioned at a PSB.
 *
 * Return: A poपूर्णांकer पूर्णांकo @buf_b from where non-overlapped data starts, or
 * @buf_b + @len_b अगर there is no non-overlapped data.
 */
अटल अचिन्हित अक्षर *पूर्णांकel_pt_find_overlap_tsc(अचिन्हित अक्षर *buf_a,
						माप_प्रकार len_a,
						अचिन्हित अक्षर *buf_b,
						माप_प्रकार len_b, bool *consecutive)
अणु
	uपूर्णांक64_t tsc_a, tsc_b;
	अचिन्हित अक्षर *p;
	माप_प्रकार len, rem_a, rem_b;

	p = पूर्णांकel_pt_last_psb(buf_a, len_a);
	अगर (!p)
		वापस buf_b; /* No PSB in buf_a => no overlap */

	len = len_a - (p - buf_a);
	अगर (!पूर्णांकel_pt_next_tsc(p, len, &tsc_a, &rem_a)) अणु
		/* The last PSB+ in buf_a is incomplete, so go back one more */
		len_a -= len;
		p = पूर्णांकel_pt_last_psb(buf_a, len_a);
		अगर (!p)
			वापस buf_b; /* No full PSB+ => assume no overlap */
		len = len_a - (p - buf_a);
		अगर (!पूर्णांकel_pt_next_tsc(p, len, &tsc_a, &rem_a))
			वापस buf_b; /* No TSC in buf_a => assume no overlap */
	पूर्ण

	जबतक (1) अणु
		/* Ignore PSB+ with no TSC */
		अगर (पूर्णांकel_pt_next_tsc(buf_b, len_b, &tsc_b, &rem_b)) अणु
			पूर्णांक cmp = पूर्णांकel_pt_tsc_cmp(tsc_a, tsc_b);

			/* Same TSC, so buffers are consecutive */
			अगर (!cmp && rem_b >= rem_a) अणु
				अचिन्हित अक्षर *start;

				*consecutive = true;
				start = buf_b + len_b - (rem_b - rem_a);
				वापस adj_क्रम_padding(start, buf_a, len_a);
			पूर्ण
			अगर (cmp < 0)
				वापस buf_b; /* tsc_a < tsc_b => no overlap */
		पूर्ण

		अगर (!पूर्णांकel_pt_step_psb(&buf_b, &len_b))
			वापस buf_b + len_b; /* No PSB in buf_b => no data */
	पूर्ण
पूर्ण

/**
 * पूर्णांकel_pt_find_overlap - determine start of non-overlapped trace data.
 * @buf_a: first buffer
 * @len_a: size of first buffer
 * @buf_b: second buffer
 * @len_b: size of second buffer
 * @have_tsc: can use TSC packets to detect overlap
 * @consecutive: वापसs true अगर there is data in buf_b that is consecutive
 *               to buf_a
 *
 * When trace samples or snapshots are recorded there is the possibility that
 * the data overlaps.  Note that, क्रम the purposes of decoding, data is only
 * useful अगर it begins with a PSB packet.
 *
 * Return: A poपूर्णांकer पूर्णांकo @buf_b from where non-overlapped data starts, or
 * @buf_b + @len_b अगर there is no non-overlapped data.
 */
अचिन्हित अक्षर *पूर्णांकel_pt_find_overlap(अचिन्हित अक्षर *buf_a, माप_प्रकार len_a,
				     अचिन्हित अक्षर *buf_b, माप_प्रकार len_b,
				     bool have_tsc, bool *consecutive)
अणु
	अचिन्हित अक्षर *found;

	/* Buffer 'b' must start at PSB so throw away everything beक्रमe that */
	अगर (!पूर्णांकel_pt_next_psb(&buf_b, &len_b))
		वापस buf_b + len_b; /* No PSB */

	अगर (!पूर्णांकel_pt_next_psb(&buf_a, &len_a))
		वापस buf_b; /* No overlap */

	अगर (have_tsc) अणु
		found = पूर्णांकel_pt_find_overlap_tsc(buf_a, len_a, buf_b, len_b,
						  consecutive);
		अगर (found)
			वापस found;
	पूर्ण

	/*
	 * Buffer 'b' cannot end within buffer 'a' so, क्रम comparison purposes,
	 * we can ignore the first part of buffer 'a'.
	 */
	जबतक (len_b < len_a) अणु
		अगर (!पूर्णांकel_pt_step_psb(&buf_a, &len_a))
			वापस buf_b; /* No overlap */
	पूर्ण

	/* Now len_b >= len_a */
	जबतक (1) अणु
		/* Potential overlap so check the bytes */
		found = memmem(buf_a, len_a, buf_b, len_a);
		अगर (found) अणु
			*consecutive = true;
			वापस adj_क्रम_padding(buf_b + len_a, buf_a, len_a);
		पूर्ण

		/* Try again at next PSB in buffer 'a' */
		अगर (!पूर्णांकel_pt_step_psb(&buf_a, &len_a))
			वापस buf_b; /* No overlap */
	पूर्ण
पूर्ण

/**
 * काष्ठा fast_क्रमward_data - data used by पूर्णांकel_pt_ff_cb().
 * @बारtamp: बारtamp to fast क्रमward towards
 * @buf_बारtamp: buffer बारtamp of last buffer with trace data earlier than
 *                 the fast क्रमward बारtamp.
 */
काष्ठा fast_क्रमward_data अणु
	uपूर्णांक64_t बारtamp;
	uपूर्णांक64_t buf_बारtamp;
पूर्ण;

/**
 * पूर्णांकel_pt_ff_cb - fast क्रमward lookahead callback.
 * @buffer: Intel PT trace buffer
 * @data: opaque poपूर्णांकer to fast क्रमward data (काष्ठा fast_क्रमward_data)
 *
 * Determine अगर @buffer trace is past the fast क्रमward बारtamp.
 *
 * Return: 1 (stop lookahead) अगर @buffer trace is past the fast क्रमward
 *         बारtamp, and 0 otherwise.
 */
अटल पूर्णांक पूर्णांकel_pt_ff_cb(काष्ठा पूर्णांकel_pt_buffer *buffer, व्योम *data)
अणु
	काष्ठा fast_क्रमward_data *d = data;
	अचिन्हित अक्षर *buf;
	uपूर्णांक64_t tsc;
	माप_प्रकार rem;
	माप_प्रकार len;

	buf = (अचिन्हित अक्षर *)buffer->buf;
	len = buffer->len;

	अगर (!पूर्णांकel_pt_next_psb(&buf, &len) ||
	    !पूर्णांकel_pt_next_tsc(buf, len, &tsc, &rem))
		वापस 0;

	tsc = पूर्णांकel_pt_8b_tsc(tsc, buffer->ref_बारtamp);

	पूर्णांकel_pt_log("Buffer 1st timestamp " x64_fmt " ref timestamp " x64_fmt "\n",
		     tsc, buffer->ref_बारtamp);

	/*
	 * If the buffer contains a बारtamp earlier that the fast क्रमward
	 * बारtamp, then record it, अन्यथा stop.
	 */
	अगर (tsc < d->बारtamp)
		d->buf_बारtamp = buffer->ref_बारtamp;
	अन्यथा
		वापस 1;

	वापस 0;
पूर्ण

/**
 * पूर्णांकel_pt_fast_क्रमward - reposition decoder क्रमwards.
 * @decoder: Intel PT decoder
 * @बारtamp: बारtamp to fast क्रमward towards
 *
 * Reposition decoder at the last PSB with a बारtamp earlier than @बारtamp.
 *
 * Return: 0 on success or negative error code on failure.
 */
पूर्णांक पूर्णांकel_pt_fast_क्रमward(काष्ठा पूर्णांकel_pt_decoder *decoder, uपूर्णांक64_t बारtamp)
अणु
	काष्ठा fast_क्रमward_data d = अणु .बारtamp = बारtamp पूर्ण;
	अचिन्हित अक्षर *buf;
	माप_प्रकार len;
	पूर्णांक err;

	पूर्णांकel_pt_log("Fast forward towards timestamp " x64_fmt "\n", बारtamp);

	/* Find buffer बारtamp of buffer to fast क्रमward to */
	err = decoder->lookahead(decoder->data, पूर्णांकel_pt_ff_cb, &d);
	अगर (err < 0)
		वापस err;

	/* Walk to buffer with same buffer बारtamp */
	अगर (d.buf_बारtamp) अणु
		करो अणु
			decoder->pos += decoder->len;
			decoder->len = 0;
			err = पूर्णांकel_pt_get_next_data(decoder, true);
			/* -ENOLINK means non-consecutive trace */
			अगर (err && err != -ENOLINK)
				वापस err;
		पूर्ण जबतक (decoder->buf_बारtamp != d.buf_बारtamp);
	पूर्ण

	अगर (!decoder->buf)
		वापस 0;

	buf = (अचिन्हित अक्षर *)decoder->buf;
	len = decoder->len;

	अगर (!पूर्णांकel_pt_next_psb(&buf, &len))
		वापस 0;

	/*
	 * Walk PSBs जबतक the PSB बारtamp is less than the fast क्रमward
	 * बारtamp.
	 */
	करो अणु
		uपूर्णांक64_t tsc;
		माप_प्रकार rem;

		अगर (!पूर्णांकel_pt_next_tsc(buf, len, &tsc, &rem))
			अवरोध;
		tsc = पूर्णांकel_pt_8b_tsc(tsc, decoder->buf_बारtamp);
		/*
		 * A TSC packet can slip past MTC packets but, after fast
		 * क्रमward, decoding starts at the TSC बारtamp. That means
		 * the बारtamps may not be exactly the same as the बारtamps
		 * that would have been decoded without fast क्रमward.
		 */
		अगर (tsc < बारtamp) अणु
			पूर्णांकel_pt_log("Fast forward to next PSB timestamp " x64_fmt "\n", tsc);
			decoder->pos += decoder->len - len;
			decoder->buf = buf;
			decoder->len = len;
			पूर्णांकel_pt_reposition(decoder);
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण जबतक (पूर्णांकel_pt_step_psb(&buf, &len));

	वापस 0;
पूर्ण
