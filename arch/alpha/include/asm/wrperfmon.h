<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Definitions क्रम use with the Alpha wrperfmon PAL call.
 */

#अगर_अघोषित __ALPHA_WRPERFMON_H
#घोषणा __ALPHA_WRPERFMON_H

/* Following commands are implemented on all CPUs */
#घोषणा PERFMON_CMD_DISABLE 0
#घोषणा PERFMON_CMD_ENABLE 1
#घोषणा PERFMON_CMD_DESIRED_EVENTS 2
#घोषणा PERFMON_CMD_LOGGING_OPTIONS 3
/* Following commands on EV5/EV56/PCA56 only */
#घोषणा PERFMON_CMD_INT_FREQ 4
#घोषणा PERFMON_CMD_ENABLE_CLEAR 7
/* Following commands are on EV5 and better CPUs */
#घोषणा PERFMON_CMD_READ 5
#घोषणा PERFMON_CMD_WRITE 6
/* Following command are on EV6 and better CPUs */
#घोषणा PERFMON_CMD_ENABLE_WRITE 7
/* Following command are on EV67 and better CPUs */
#घोषणा PERFMON_CMD_I_STAT 8
#घोषणा PERFMON_CMD_PMPC 9


/* EV5/EV56/PCA56 Counters */
#घोषणा EV5_PCTR_0 (1UL<<0)
#घोषणा EV5_PCTR_1 (1UL<<1)
#घोषणा EV5_PCTR_2 (1UL<<2)

#घोषणा EV5_PCTR_0_COUNT_SHIFT 48
#घोषणा EV5_PCTR_1_COUNT_SHIFT 32
#घोषणा EV5_PCTR_2_COUNT_SHIFT 16

#घोषणा EV5_PCTR_0_COUNT_MASK 0xffffUL
#घोषणा EV5_PCTR_1_COUNT_MASK 0xffffUL
#घोषणा EV5_PCTR_2_COUNT_MASK 0x3fffUL

/* EV6 Counters */
#घोषणा EV6_PCTR_0 (1UL<<0)
#घोषणा EV6_PCTR_1 (1UL<<1)

#घोषणा EV6_PCTR_0_COUNT_SHIFT 28
#घोषणा EV6_PCTR_1_COUNT_SHIFT 6

#घोषणा EV6_PCTR_0_COUNT_MASK 0xfffffUL
#घोषणा EV6_PCTR_1_COUNT_MASK 0xfffffUL

/* EV67 (and subsequent) counters */
#घोषणा EV67_PCTR_0 (1UL<<0)
#घोषणा EV67_PCTR_1 (1UL<<1)

#घोषणा EV67_PCTR_0_COUNT_SHIFT 28
#घोषणा EV67_PCTR_1_COUNT_SHIFT 6

#घोषणा EV67_PCTR_0_COUNT_MASK 0xfffffUL
#घोषणा EV67_PCTR_1_COUNT_MASK 0xfffffUL


/*
 * The Alpha Architecure Handbook, vers. 4 (1998) appears to have a mहै_छाप
 *  in Table E-23 regarding the bits that set the event PCTR 1 counts.
 *  Hopefully what we have here is correct.
 */
#घोषणा EV6_PCTR_0_EVENT_MASK 0x10UL
#घोषणा EV6_PCTR_1_EVENT_MASK 0x0fUL

/* EV6 Events */
#घोषणा EV6_PCTR_0_CYCLES (0UL << 4)
#घोषणा EV6_PCTR_0_INSTRUCTIONS (1UL << 4)

#घोषणा EV6_PCTR_1_CYCLES 0
#घोषणा EV6_PCTR_1_BRANCHES 1
#घोषणा EV6_PCTR_1_BRANCH_MISPREDICTS 2
#घोषणा EV6_PCTR_1_DTB_SINGLE_MISSES 3
#घोषणा EV6_PCTR_1_DTB_DOUBLE_MISSES 4
#घोषणा EV6_PCTR_1_ITB_MISSES 5
#घोषणा EV6_PCTR_1_UNALIGNED_TRAPS 6
#घोषणा EV6_PCTR_1_REPLY_TRAPS 7

/* From the Alpha Architecture Reference Manual, 4th edn., 2002 */
#घोषणा EV67_PCTR_MODE_MASK 0x10UL
#घोषणा EV67_PCTR_EVENT_MASK 0x0CUL

#घोषणा EV67_PCTR_MODE_PROखाताME (1UL<<4)
#घोषणा EV67_PCTR_MODE_AGGREGATE (0UL<<4)

#घोषणा EV67_PCTR_INSTR_CYCLES (0UL<<2)
#घोषणा EV67_PCTR_CYCLES_UNDEF (1UL<<2)
#घोषणा EV67_PCTR_INSTR_BCACHEMISS (2UL<<2)
#घोषणा EV67_PCTR_CYCLES_MBOX (3UL<<2)

#पूर्ण_अगर
