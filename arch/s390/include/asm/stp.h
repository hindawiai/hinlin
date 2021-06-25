<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Copyright IBM Corp. 2006
 *  Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com)
 */
#अगर_अघोषित __S390_STP_H
#घोषणा __S390_STP_H

#समावेश <linux/compiler.h>

/* notअगरier क्रम syncs */
बाह्य काष्ठा atomic_notअगरier_head s390_epoch_delta_notअगरier;

/* STP पूर्णांकerruption parameter */
काष्ठा stp_irq_parm अणु
	u32		: 14;
	u32 tsc		:  1;	/* Timing status change */
	u32 lac		:  1;	/* Link availability change */
	u32 tcpc	:  1;	/* Time control parameter change */
	u32		: 15;
पूर्ण __packed;

#घोषणा STP_OP_SYNC	1
#घोषणा STP_OP_CTRL	3

काष्ठा stp_sstpi अणु
	u32		: 32;
	u32 tu		:  1;
	u32 lu		:  1;
	u32		:  6;
	u32 stratum	:  8;
	u32 vbits	: 16;
	u32 leaps	: 16;
	u32 पंचांगd		:  4;
	u32 ctn		:  4;
	u32		:  3;
	u32 c		:  1;
	u32 tst		:  4;
	u32 tzo		: 16;
	u32 dsto	: 16;
	u32 ctrl	: 16;
	u32		: 16;
	u32 tto;
	u32		: 32;
	u32 ctnid[3];
	u32		: 32;
	u32 toकरोff[4];
	u32 rsvd[48];
पूर्ण __packed;

काष्ठा stp_tzib अणु
	u32 tzan	: 16;
	u32		: 16;
	u32 tzo		: 16;
	u32 dsto	: 16;
	u32 stn;
	u32 dstn;
	u64 dst_on_alg;
	u64 dst_off_alg;
पूर्ण __packed;

काष्ठा stp_tcpib अणु
	u32 atcode	: 4;
	u32 ntcode	: 4;
	u32 d		: 1;
	u32		: 23;
	s32 tto;
	काष्ठा stp_tzib atzib;
	काष्ठा stp_tzib ntzib;
	s32 adst_offset : 16;
	s32 ndst_offset : 16;
	u32 rsvd1;
	u64 ntzib_update;
	u64 ndsto_update;
पूर्ण __packed;

काष्ठा stp_lsoib अणु
	u32 p		: 1;
	u32		: 31;
	s32 also	: 16;
	s32 nlso	: 16;
	u64 nlsout;
पूर्ण __packed;

काष्ठा stp_stzi अणु
	u32 rsvd0[3];
	u64 data_ts;
	u32 rsvd1[22];
	काष्ठा stp_tcpib tcpib;
	काष्ठा stp_lsoib lsoib;
पूर्ण __packed;

/* Functions needed by the machine check handler */
पूर्णांक stp_sync_check(व्योम);
पूर्णांक stp_island_check(व्योम);
व्योम stp_queue_work(व्योम);

#पूर्ण_अगर /* __S390_STP_H */
