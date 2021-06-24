<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2014-2015, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _CORESIGHT_CORESIGHT_ETM_H
#घोषणा _CORESIGHT_CORESIGHT_ETM_H

#समावेश <यंत्र/local.h>
#समावेश <linux/spinlock.h>
#समावेश "coresight-priv.h"

/*
 * Device रेजिस्टरs:
 * 0x000 - 0x2FC: Trace         रेजिस्टरs
 * 0x300 - 0x314: Management    रेजिस्टरs
 * 0x318 - 0xEFC: Trace         रेजिस्टरs
 *
 * Coresight रेजिस्टरs
 * 0xF00 - 0xF9C: Management    रेजिस्टरs
 * 0xFA0 - 0xFA4: Management    रेजिस्टरs in PFTv1.0
 *                Trace         रेजिस्टरs in PFTv1.1
 * 0xFA8 - 0xFFC: Management    रेजिस्टरs
 */

/* Trace रेजिस्टरs (0x000-0x2FC) */
#घोषणा ETMCR			0x000
#घोषणा ETMCCR			0x004
#घोषणा ETMTRIGGER		0x008
#घोषणा ETMSR			0x010
#घोषणा ETMSCR			0x014
#घोषणा ETMTSSCR		0x018
#घोषणा ETMTECR2		0x01c
#घोषणा ETMTEEVR		0x020
#घोषणा ETMTECR1		0x024
#घोषणा ETMFFLR			0x02c
#घोषणा ETMACVRn(n)		(0x040 + (n * 4))
#घोषणा ETMACTRn(n)		(0x080 + (n * 4))
#घोषणा ETMCNTRLDVRn(n)		(0x140 + (n * 4))
#घोषणा ETMCNTENRn(n)		(0x150 + (n * 4))
#घोषणा ETMCNTRLDEVRn(n)	(0x160 + (n * 4))
#घोषणा ETMCNTVRn(n)		(0x170 + (n * 4))
#घोषणा ETMSQ12EVR		0x180
#घोषणा ETMSQ21EVR		0x184
#घोषणा ETMSQ23EVR		0x188
#घोषणा ETMSQ31EVR		0x18c
#घोषणा ETMSQ32EVR		0x190
#घोषणा ETMSQ13EVR		0x194
#घोषणा ETMSQR			0x19c
#घोषणा ETMEXTOUTEVRn(n)	(0x1a0 + (n * 4))
#घोषणा ETMCIDCVRn(n)		(0x1b0 + (n * 4))
#घोषणा ETMCIDCMR		0x1bc
#घोषणा ETMIMPSPEC0		0x1c0
#घोषणा ETMIMPSPEC1		0x1c4
#घोषणा ETMIMPSPEC2		0x1c8
#घोषणा ETMIMPSPEC3		0x1cc
#घोषणा ETMIMPSPEC4		0x1d0
#घोषणा ETMIMPSPEC5		0x1d4
#घोषणा ETMIMPSPEC6		0x1d8
#घोषणा ETMIMPSPEC7		0x1dc
#घोषणा ETMSYNCFR		0x1e0
#घोषणा ETMIDR			0x1e4
#घोषणा ETMCCER			0x1e8
#घोषणा ETMEXTINSELR		0x1ec
#घोषणा ETMTESSEICR		0x1f0
#घोषणा ETMEIBCR		0x1f4
#घोषणा ETMTSEVR		0x1f8
#घोषणा ETMAUXCR		0x1fc
#घोषणा ETMTRACEIDR		0x200
#घोषणा ETMVMIDCVR		0x240
/* Management रेजिस्टरs (0x300-0x314) */
#घोषणा ETMOSLAR		0x300
#घोषणा ETMOSLSR		0x304
#घोषणा ETMOSSRR		0x308
#घोषणा ETMPDCR			0x310
#घोषणा ETMPDSR			0x314
#घोषणा ETM_MAX_ADDR_CMP	16
#घोषणा ETM_MAX_CNTR		4
#घोषणा ETM_MAX_CTXID_CMP	3

/* Register definition */
/* ETMCR - 0x00 */
#घोषणा ETMCR_PWD_DWN		BIT(0)
#घोषणा ETMCR_STALL_MODE	BIT(7)
#घोषणा ETMCR_BRANCH_BROADCAST	BIT(8)
#घोषणा ETMCR_ETM_PRG		BIT(10)
#घोषणा ETMCR_ETM_EN		BIT(11)
#घोषणा ETMCR_CYC_ACC		BIT(12)
#घोषणा ETMCR_CTXID_SIZE	(BIT(14)|BIT(15))
#घोषणा ETMCR_TIMESTAMP_EN	BIT(28)
#घोषणा ETMCR_RETURN_STACK	BIT(29)
/* ETMCCR - 0x04 */
#घोषणा ETMCCR_FIFOFULL		BIT(23)
/* ETMPDCR - 0x310 */
#घोषणा ETMPDCR_PWD_UP		BIT(3)
/* ETMTECR1 - 0x024 */
#घोषणा ETMTECR1_ADDR_COMP_1	BIT(0)
#घोषणा ETMTECR1_INC_EXC	BIT(24)
#घोषणा ETMTECR1_START_STOP	BIT(25)
/* ETMCCER - 0x1E8 */
#घोषणा ETMCCER_TIMESTAMP	BIT(22)
#घोषणा ETMCCER_RETSTACK	BIT(23)

#घोषणा ETM_MODE_EXCLUDE	BIT(0)
#घोषणा ETM_MODE_CYCACC		BIT(1)
#घोषणा ETM_MODE_STALL		BIT(2)
#घोषणा ETM_MODE_TIMESTAMP	BIT(3)
#घोषणा ETM_MODE_CTXID		BIT(4)
#घोषणा ETM_MODE_BBROAD		BIT(5)
#घोषणा ETM_MODE_RET_STACK	BIT(6)
#घोषणा ETM_MODE_ALL		(ETM_MODE_EXCLUDE | ETM_MODE_CYCACC | \
				 ETM_MODE_STALL | ETM_MODE_TIMESTAMP | \
				 ETM_MODE_BBROAD | ETM_MODE_RET_STACK | \
				 ETM_MODE_CTXID | ETM_MODE_EXCL_KERN | \
				 ETM_MODE_EXCL_USER)

#घोषणा ETM_SQR_MASK		0x3
#घोषणा ETM_TRACEID_MASK	0x3f
#घोषणा ETM_EVENT_MASK		0x1ffff
#घोषणा ETM_SYNC_MASK		0xfff
#घोषणा ETM_ALL_MASK		0xffffffff

#घोषणा ETMSR_PROG_BIT		1
#घोषणा ETM_SEQ_STATE_MAX_VAL	(0x2)
#घोषणा PORT_SIZE_MASK		(GENMASK(21, 21) | GENMASK(6, 4))

#घोषणा ETM_HARD_WIRE_RES_A	/* Hard wired, always true */	\
				((0x0f << 0)	|		\
				/* Resource index A */		\
				(0x06 << 4))

#घोषणा ETM_ADD_COMP_0		/* Single addr comparator 1 */	\
				((0x00 << 7)	|		\
				/* Resource index B */		\
				(0x00 << 11))

#घोषणा ETM_EVENT_NOT_A		BIT(14) /* NOT(A) */

#घोषणा ETM_DEFAULT_EVENT_VAL	(ETM_HARD_WIRE_RES_A	|	\
				 ETM_ADD_COMP_0		|	\
				 ETM_EVENT_NOT_A)

/**
 * काष्ठा eपंचांग_config - configuration inक्रमmation related to an ETM
 * @mode:	controls various modes supported by this ETM/PTM.
 * @ctrl:	used in conjunction with @mode.
 * @trigger_event: setting क्रम रेजिस्टर ETMTRIGGER.
 * @startstop_ctrl: setting क्रम रेजिस्टर ETMTSSCR.
 * @enable_event: setting क्रम रेजिस्टर ETMTEEVR.
 * @enable_ctrl1: setting क्रम रेजिस्टर ETMTECR1.
 * @enable_ctrl2: setting क्रम रेजिस्टर ETMTECR2.
 * @fअगरofull_level: setting क्रम रेजिस्टर ETMFFLR.
 * @addr_idx:	index क्रम the address comparator selection.
 * @addr_val:	value क्रम address comparator रेजिस्टर.
 * @addr_acctype: access type क्रम address comparator रेजिस्टर.
 * @addr_type:	current status of the comparator रेजिस्टर.
 * @cntr_idx:	index क्रम the counter रेजिस्टर selection.
 * @cntr_rld_val: reload value of a counter रेजिस्टर.
 * @cntr_event:	control क्रम counter enable रेजिस्टर.
 * @cntr_rld_event: value क्रम counter reload event रेजिस्टर.
 * @cntr_val:	counter value रेजिस्टर.
 * @seq_12_event: event causing the transition from 1 to 2.
 * @seq_21_event: event causing the transition from 2 to 1.
 * @seq_23_event: event causing the transition from 2 to 3.
 * @seq_31_event: event causing the transition from 3 to 1.
 * @seq_32_event: event causing the transition from 3 to 2.
 * @seq_13_event: event causing the transition from 1 to 3.
 * @seq_curr_state: current value of the sequencer रेजिस्टर.
 * @ctxid_idx: index क्रम the context ID रेजिस्टरs.
 * @ctxid_pid: value क्रम the context ID to trigger on.
 * @ctxid_mask: mask applicable to all the context IDs.
 * @sync_freq:	Synchronisation frequency.
 * @बारtamp_event: Defines an event that requests the insertion
 *		     of a बारtamp पूर्णांकo the trace stream.
 */
काष्ठा eपंचांग_config अणु
	u32				mode;
	u32				ctrl;
	u32				trigger_event;
	u32				startstop_ctrl;
	u32				enable_event;
	u32				enable_ctrl1;
	u32				enable_ctrl2;
	u32				fअगरofull_level;
	u8				addr_idx;
	u32				addr_val[ETM_MAX_ADDR_CMP];
	u32				addr_acctype[ETM_MAX_ADDR_CMP];
	u32				addr_type[ETM_MAX_ADDR_CMP];
	u8				cntr_idx;
	u32				cntr_rld_val[ETM_MAX_CNTR];
	u32				cntr_event[ETM_MAX_CNTR];
	u32				cntr_rld_event[ETM_MAX_CNTR];
	u32				cntr_val[ETM_MAX_CNTR];
	u32				seq_12_event;
	u32				seq_21_event;
	u32				seq_23_event;
	u32				seq_31_event;
	u32				seq_32_event;
	u32				seq_13_event;
	u32				seq_curr_state;
	u8				ctxid_idx;
	u32				ctxid_pid[ETM_MAX_CTXID_CMP];
	u32				ctxid_mask;
	u32				sync_freq;
	u32				बारtamp_event;
पूर्ण;

/**
 * काष्ठा eपंचांग_drvdata - specअगरics associated to an ETM component
 * @base:	memory mapped base address क्रम this component.
 * @atclk:	optional घड़ी क्रम the core parts of the ETM.
 * @csdev:	component vitals needed by the framework.
 * @spinlock:	only one at a समय pls.
 * @cpu:	the cpu this component is affined to.
 * @port_size:	port size as reported by ETMCR bit 4-6 and 21.
 * @arch:	ETM/PTM version number.
 * @use_cpu14:	true अगर management रेजिस्टरs need to be accessed via CP14.
 * @mode:	this tracer's mode, i.e sysFS, Perf or disabled.
 * @sticky_enable: true अगर ETM base configuration has been करोne.
 * @boot_enable:true अगर we should start tracing at boot समय.
 * @os_unlock:	true अगर access to management रेजिस्टरs is allowed.
 * @nr_addr_cmp:Number of pairs of address comparators as found in ETMCCR.
 * @nr_cntr:	Number of counters as found in ETMCCR bit 13-15.
 * @nr_ext_inp:	Number of बाह्यal input as found in ETMCCR bit 17-19.
 * @nr_ext_out:	Number of बाह्यal output as found in ETMCCR bit 20-22.
 * @nr_ctxid_cmp: Number of contextID comparators as found in ETMCCR bit 24-25.
 * @eपंचांगccr:	value of रेजिस्टर ETMCCR.
 * @eपंचांगccer:	value of रेजिस्टर ETMCCER.
 * @traceid:	value of the current ID क्रम this component.
 * @config:	काष्ठाure holding configuration parameters.
 */
काष्ठा eपंचांग_drvdata अणु
	व्योम __iomem			*base;
	काष्ठा clk			*atclk;
	काष्ठा coresight_device		*csdev;
	spinlock_t			spinlock;
	पूर्णांक				cpu;
	पूर्णांक				port_size;
	u8				arch;
	bool				use_cp14;
	local_t				mode;
	bool				sticky_enable;
	bool				boot_enable;
	bool				os_unlock;
	u8				nr_addr_cmp;
	u8				nr_cntr;
	u8				nr_ext_inp;
	u8				nr_ext_out;
	u8				nr_ctxid_cmp;
	u32				eपंचांगccr;
	u32				eपंचांगccer;
	u32				traceid;
	काष्ठा eपंचांग_config		config;
पूर्ण;

अटल अंतरभूत व्योम eपंचांग_ग_लिखोl(काष्ठा eपंचांग_drvdata *drvdata,
			      u32 val, u32 off)
अणु
	अगर (drvdata->use_cp14) अणु
		अगर (eपंचांग_ग_लिखोl_cp14(off, val)) अणु
			dev_err(&drvdata->csdev->dev,
				"invalid CP14 access to ETM reg: %#x", off);
		पूर्ण
	पूर्ण अन्यथा अणु
		ग_लिखोl_relaxed(val, drvdata->base + off);
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक eपंचांग_पढ़ोl(काष्ठा eपंचांग_drvdata *drvdata, u32 off)
अणु
	u32 val;

	अगर (drvdata->use_cp14) अणु
		अगर (eपंचांग_पढ़ोl_cp14(off, &val)) अणु
			dev_err(&drvdata->csdev->dev,
				"invalid CP14 access to ETM reg: %#x", off);
		पूर्ण
	पूर्ण अन्यथा अणु
		val = पढ़ोl_relaxed(drvdata->base + off);
	पूर्ण

	वापस val;
पूर्ण

बाह्य स्थिर काष्ठा attribute_group *coresight_eपंचांग_groups[];
पूर्णांक eपंचांग_get_trace_id(काष्ठा eपंचांग_drvdata *drvdata);
व्योम eपंचांग_set_शेष(काष्ठा eपंचांग_config *config);
व्योम eपंचांग_config_trace_mode(काष्ठा eपंचांग_config *config);
काष्ठा eपंचांग_config *get_eपंचांग_config(काष्ठा eपंचांग_drvdata *drvdata);
#पूर्ण_अगर
