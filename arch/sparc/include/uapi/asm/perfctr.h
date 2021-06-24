<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*----------------------------------------
  PERFORMANCE INSTRUMENTATION  
  Guillaume Thouvenin           08/10/98
  David S. Miller               10/06/98
  ---------------------------------------*/
#अगर_अघोषित PERF_COUNTER_API
#घोषणा PERF_COUNTER_API

/* sys_perfctr() पूर्णांकerface.  First arg is operation code
 * from क्रमागतeration below.  The meaning of further arguments
 * are determined by the operation code.
 *
 * NOTE: This प्रणाली call is no दीर्घer provided, use the perf_events
 *       infraकाष्ठाure.
 *
 * Poपूर्णांकers which are passed by the user are poपूर्णांकers to 64-bit
 * पूर्णांकegers.
 *
 * Once enabled, perक्रमmance counter state is retained until the
 * process either निकासs or perक्रमms an exec.  That is, perक्रमmance
 * counters reमुख्य enabled क्रम विभाजन/clone children.
 */
क्रमागत perfctr_opcode अणु
	/* Enable UltraSparc perक्रमmance counters, ARG0 is poपूर्णांकer
	 * to 64-bit accumulator क्रम D0 counter in PIC, ARG1 is poपूर्णांकer
	 * to 64-bit accumulator क्रम D1 counter.  ARG2 is a poपूर्णांकer to
	 * the initial PCR रेजिस्टर value to use.
	 */
	PERFCTR_ON,

	/* Disable UltraSparc perक्रमmance counters.  The PCR is written
	 * with zero and the user counter accumulator poपूर्णांकers and
	 * working PCR रेजिस्टर value are क्रमgotten.
	 */
	PERFCTR_OFF,

	/* Add current D0 and D1 PIC values पूर्णांकo user poपूर्णांकers given
	 * in PERFCTR_ON operation.  The PIC is cleared beक्रमe वापसing.
	 */
	PERFCTR_READ,

	/* Clear the PIC रेजिस्टर. */
	PERFCTR_CLRPIC,

	/* Begin using a new PCR value, the poपूर्णांकer to which is passed
	 * in ARG0.  The PIC is also cleared after the new PCR value is
	 * written.
	 */
	PERFCTR_SETPCR,

	/* Store in poपूर्णांकer given in ARG0 the current PCR रेजिस्टर value
	 * being used.
	 */
	PERFCTR_GETPCR
पूर्ण;

#घोषणा  PRIV 0x00000001
#घोषणा  SYS  0x00000002
#घोषणा  USR  0x00000004

/* Pic.S0 Selection Bit Field Encoding, Ultra-I/II  */
#घोषणा  CYCLE_CNT            0x00000000
#घोषणा  INSTR_CNT            0x00000010
#घोषणा  DISPATCH0_IC_MISS    0x00000020
#घोषणा  DISPATCH0_STOREBUF   0x00000030
#घोषणा  IC_REF               0x00000080
#घोषणा  DC_RD                0x00000090
#घोषणा  DC_WR                0x000000A0
#घोषणा  LOAD_USE             0x000000B0
#घोषणा  EC_REF               0x000000C0
#घोषणा  EC_WRITE_HIT_RDO     0x000000D0
#घोषणा  EC_SNOOP_INV         0x000000E0
#घोषणा  EC_RD_HIT            0x000000F0

/* Pic.S0 Selection Bit Field Encoding, Ultra-III  */
#घोषणा  US3_CYCLE_CNT	      	0x00000000
#घोषणा  US3_INSTR_CNT	      	0x00000010
#घोषणा  US3_DISPATCH0_IC_MISS	0x00000020
#घोषणा  US3_DISPATCH0_BR_TGT	0x00000030
#घोषणा  US3_DISPATCH0_2ND_BR	0x00000040
#घोषणा  US3_RSTALL_STOREQ	0x00000050
#घोषणा  US3_RSTALL_IU_USE	0x00000060
#घोषणा  US3_IC_REF		0x00000080
#घोषणा  US3_DC_RD		0x00000090
#घोषणा  US3_DC_WR		0x000000a0
#घोषणा  US3_EC_REF		0x000000c0
#घोषणा  US3_EC_WR_HIT_RTO	0x000000d0
#घोषणा  US3_EC_SNOOP_INV	0x000000e0
#घोषणा  US3_EC_RD_MISS		0x000000f0
#घोषणा  US3_PC_PORT0_RD	0x00000100
#घोषणा  US3_SI_SNOOP		0x00000110
#घोषणा  US3_SI_CIQ_FLOW	0x00000120
#घोषणा  US3_SI_OWNED		0x00000130
#घोषणा  US3_SW_COUNT_0		0x00000140
#घोषणा  US3_IU_BR_MISS_TAKEN	0x00000150
#घोषणा  US3_IU_BR_COUNT_TAKEN	0x00000160
#घोषणा  US3_DISP_RS_MISPRED	0x00000170
#घोषणा  US3_FA_PIPE_COMPL	0x00000180
#घोषणा  US3_MC_READS_0		0x00000200
#घोषणा  US3_MC_READS_1		0x00000210
#घोषणा  US3_MC_READS_2		0x00000220
#घोषणा  US3_MC_READS_3		0x00000230
#घोषणा  US3_MC_STALLS_0	0x00000240
#घोषणा  US3_MC_STALLS_2	0x00000250

/* Pic.S1 Selection Bit Field Encoding, Ultra-I/II  */
#घोषणा  CYCLE_CNT_D1         0x00000000
#घोषणा  INSTR_CNT_D1         0x00000800
#घोषणा  DISPATCH0_IC_MISPRED 0x00001000
#घोषणा  DISPATCH0_FP_USE     0x00001800
#घोषणा  IC_HIT               0x00004000
#घोषणा  DC_RD_HIT            0x00004800
#घोषणा  DC_WR_HIT            0x00005000
#घोषणा  LOAD_USE_RAW         0x00005800
#घोषणा  EC_HIT               0x00006000
#घोषणा  EC_WB                0x00006800
#घोषणा  EC_SNOOP_CB          0x00007000
#घोषणा  EC_IT_HIT            0x00007800

/* Pic.S1 Selection Bit Field Encoding, Ultra-III  */
#घोषणा  US3_CYCLE_CNT_D1	0x00000000
#घोषणा  US3_INSTR_CNT_D1	0x00000800
#घोषणा  US3_DISPATCH0_MISPRED	0x00001000
#घोषणा  US3_IC_MISS_CANCELLED	0x00001800
#घोषणा  US3_RE_ENDIAN_MISS	0x00002000
#घोषणा  US3_RE_FPU_BYPASS	0x00002800
#घोषणा  US3_RE_DC_MISS		0x00003000
#घोषणा  US3_RE_EC_MISS		0x00003800
#घोषणा  US3_IC_MISS		0x00004000
#घोषणा  US3_DC_RD_MISS		0x00004800
#घोषणा  US3_DC_WR_MISS		0x00005000
#घोषणा  US3_RSTALL_FP_USE	0x00005800
#घोषणा  US3_EC_MISSES		0x00006000
#घोषणा  US3_EC_WB		0x00006800
#घोषणा  US3_EC_SNOOP_CB	0x00007000
#घोषणा  US3_EC_IC_MISS		0x00007800
#घोषणा  US3_RE_PC_MISS		0x00008000
#घोषणा  US3_ITLB_MISS		0x00008800
#घोषणा  US3_DTLB_MISS		0x00009000
#घोषणा  US3_WC_MISS		0x00009800
#घोषणा  US3_WC_SNOOP_CB	0x0000a000
#घोषणा  US3_WC_SCRUBBED	0x0000a800
#घोषणा  US3_WC_WB_WO_READ	0x0000b000
#घोषणा  US3_PC_SOFT_HIT	0x0000c000
#घोषणा  US3_PC_SNOOP_INV	0x0000c800
#घोषणा  US3_PC_HARD_HIT	0x0000d000
#घोषणा  US3_PC_PORT1_RD	0x0000d800
#घोषणा  US3_SW_COUNT_1		0x0000e000
#घोषणा  US3_IU_STAT_BR_MIS_UNTAKEN	0x0000e800
#घोषणा  US3_IU_STAT_BR_COUNT_UNTAKEN	0x0000f000
#घोषणा  US3_PC_MS_MISSES	0x0000f800
#घोषणा  US3_MC_WRITES_0	0x00010800
#घोषणा  US3_MC_WRITES_1	0x00011000
#घोषणा  US3_MC_WRITES_2	0x00011800
#घोषणा  US3_MC_WRITES_3	0x00012000
#घोषणा  US3_MC_STALLS_1	0x00012800
#घोषणा  US3_MC_STALLS_3	0x00013000
#घोषणा  US3_RE_RAW_MISS	0x00013800
#घोषणा  US3_FM_PIPE_COMPLETION	0x00014000

काष्ठा vcounter_काष्ठा अणु
  अचिन्हित दीर्घ दीर्घ vcnt0;
  अचिन्हित दीर्घ दीर्घ vcnt1;
पूर्ण;

#पूर्ण_अगर /* !(PERF_COUNTER_API) */
