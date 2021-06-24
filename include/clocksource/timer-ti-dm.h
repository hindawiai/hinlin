<शैली गुरु>
/*
 * OMAP Dual-Mode Timers
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - https://www.ti.com/
 * Tarun Kanti DebBarma <tarun.kanti@ti.com>
 * Thara Gopinath <thara@ti.com>
 *
 * Platक्रमm device conversion and hwmod support.
 *
 * Copyright (C) 2005 Nokia Corporation
 * Author: Lauri Leukkunen <lauri.leukkunen@nokia.com>
 * PWM and घड़ी framwork support by Timo Teras.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
 * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY सूचीECT, INसूचीECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * You should have received a copy of the  GNU General Public License aदीर्घ
 * with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
 * 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>

#अगर_अघोषित __CLOCKSOURCE_DMTIMER_H
#घोषणा __CLOCKSOURCE_DMTIMER_H

/* घड़ी sources */
#घोषणा OMAP_TIMER_SRC_SYS_CLK			0x00
#घोषणा OMAP_TIMER_SRC_32_KHZ			0x01
#घोषणा OMAP_TIMER_SRC_EXT_CLK			0x02

/* समयr पूर्णांकerrupt enable bits */
#घोषणा OMAP_TIMER_INT_CAPTURE			(1 << 2)
#घोषणा OMAP_TIMER_INT_OVERFLOW			(1 << 1)
#घोषणा OMAP_TIMER_INT_MATCH			(1 << 0)

/* trigger types */
#घोषणा OMAP_TIMER_TRIGGER_NONE			0x00
#घोषणा OMAP_TIMER_TRIGGER_OVERFLOW		0x01
#घोषणा OMAP_TIMER_TRIGGER_OVERFLOW_AND_COMPARE	0x02

/* posted mode types */
#घोषणा OMAP_TIMER_NONPOSTED			0x00
#घोषणा OMAP_TIMER_POSTED			0x01

/* समयr capabilities used in hwmod database */
#घोषणा OMAP_TIMER_SECURE				0x80000000
#घोषणा OMAP_TIMER_ALWON				0x40000000
#घोषणा OMAP_TIMER_HAS_PWM				0x20000000
#घोषणा OMAP_TIMER_NEEDS_RESET				0x10000000
#घोषणा OMAP_TIMER_HAS_DSP_IRQ				0x08000000

/*
 * समयr errata flags
 *
 * Errata i103/i767 impacts all OMAP3/4/5 devices including AM33xx. This
 * errata prevents us from using posted mode on these devices, unless the
 * समयr counter रेजिस्टर is never पढ़ो. For more details please refer to
 * the OMAP3/4/5 errata करोcuments.
 */
#घोषणा OMAP_TIMER_ERRATA_I103_I767			0x80000000

काष्ठा समयr_regs अणु
	u32 tidr;
	u32 tier;
	u32 twer;
	u32 tclr;
	u32 tcrr;
	u32 tldr;
	u32 ttrg;
	u32 twps;
	u32 पंचांगar;
	u32 tcar1;
	u32 tsicr;
	u32 tcar2;
	u32 tpir;
	u32 tnir;
	u32 tcvr;
	u32 tocr;
	u32 towr;
पूर्ण;

काष्ठा omap_dm_समयr अणु
	पूर्णांक id;
	पूर्णांक irq;
	काष्ठा clk *fclk;

	व्योम __iomem	*io_base;
	व्योम __iomem	*irq_stat;	/* TISR/IRQSTATUS पूर्णांकerrupt status */
	व्योम __iomem	*irq_ena;	/* irq enable */
	व्योम __iomem	*irq_dis;	/* irq disable, only on v2 ip */
	व्योम __iomem	*pend;		/* ग_लिखो pending */
	व्योम __iomem	*func_base;	/* function रेजिस्टर base */

	atomic_t enabled;
	अचिन्हित दीर्घ rate;
	अचिन्हित reserved:1;
	अचिन्हित posted:1;
	काष्ठा समयr_regs context;
	पूर्णांक revision;
	u32 capability;
	u32 errata;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा list_head node;
	काष्ठा notअगरier_block nb;
पूर्ण;

पूर्णांक omap_dm_समयr_reserve_sysसमयr(पूर्णांक id);
काष्ठा omap_dm_समयr *omap_dm_समयr_request_by_cap(u32 cap);

पूर्णांक omap_dm_समयr_get_irq(काष्ठा omap_dm_समयr *समयr);

u32 omap_dm_समयr_modअगरy_idlect_mask(u32 inpuपंचांगask);

पूर्णांक omap_dm_समयr_trigger(काष्ठा omap_dm_समयr *समयr);

पूर्णांक omap_dm_समयrs_active(व्योम);

/*
 * Do not use the defines below, they are not needed. They should be only
 * used by dmसमयr.c and sys_समयr related code.
 */

/*
 * The पूर्णांकerrupt रेजिस्टरs are dअगरferent between v1 and v2 ip.
 * These रेजिस्टरs are offsets from समयr->iobase.
 */
#घोषणा OMAP_TIMER_ID_OFFSET		0x00
#घोषणा OMAP_TIMER_OCP_CFG_OFFSET	0x10

#घोषणा OMAP_TIMER_V1_SYS_STAT_OFFSET	0x14
#घोषणा OMAP_TIMER_V1_STAT_OFFSET	0x18
#घोषणा OMAP_TIMER_V1_INT_EN_OFFSET	0x1c

#घोषणा OMAP_TIMER_V2_IRQSTATUS_RAW	0x24
#घोषणा OMAP_TIMER_V2_IRQSTATUS		0x28
#घोषणा OMAP_TIMER_V2_IRQENABLE_SET	0x2c
#घोषणा OMAP_TIMER_V2_IRQENABLE_CLR	0x30

/*
 * The functional रेजिस्टरs have a dअगरferent base on v1 and v2 ip.
 * These रेजिस्टरs are offsets from समयr->func_base. The func_base
 * is samae as io_base क्रम v1 and io_base + 0x14 क्रम v2 ip.
 *
 */
#घोषणा OMAP_TIMER_V2_FUNC_OFFSET		0x14

#घोषणा _OMAP_TIMER_WAKEUP_EN_OFFSET	0x20
#घोषणा _OMAP_TIMER_CTRL_OFFSET		0x24
#घोषणा		OMAP_TIMER_CTRL_GPOCFG		(1 << 14)
#घोषणा		OMAP_TIMER_CTRL_CAPTMODE	(1 << 13)
#घोषणा		OMAP_TIMER_CTRL_PT		(1 << 12)
#घोषणा		OMAP_TIMER_CTRL_TCM_LOWTOHIGH	(0x1 << 8)
#घोषणा		OMAP_TIMER_CTRL_TCM_HIGHTOLOW	(0x2 << 8)
#घोषणा		OMAP_TIMER_CTRL_TCM_BOTHEDGES	(0x3 << 8)
#घोषणा		OMAP_TIMER_CTRL_SCPWM		(1 << 7)
#घोषणा		OMAP_TIMER_CTRL_CE		(1 << 6) /* compare enable */
#घोषणा		OMAP_TIMER_CTRL_PRE		(1 << 5) /* prescaler enable */
#घोषणा		OMAP_TIMER_CTRL_PTV_SHIFT	2 /* prescaler value shअगरt */
#घोषणा		OMAP_TIMER_CTRL_POSTED		(1 << 2)
#घोषणा		OMAP_TIMER_CTRL_AR		(1 << 1) /* स्वतः-reload enable */
#घोषणा		OMAP_TIMER_CTRL_ST		(1 << 0) /* start समयr */
#घोषणा _OMAP_TIMER_COUNTER_OFFSET	0x28
#घोषणा _OMAP_TIMER_LOAD_OFFSET		0x2c
#घोषणा _OMAP_TIMER_TRIGGER_OFFSET	0x30
#घोषणा _OMAP_TIMER_WRITE_PEND_OFFSET	0x34
#घोषणा		WP_NONE			0	/* no ग_लिखो pending bit */
#घोषणा		WP_TCLR			(1 << 0)
#घोषणा		WP_TCRR			(1 << 1)
#घोषणा		WP_TLDR			(1 << 2)
#घोषणा		WP_TTGR			(1 << 3)
#घोषणा		WP_TMAR			(1 << 4)
#घोषणा		WP_TPIR			(1 << 5)
#घोषणा		WP_TNIR			(1 << 6)
#घोषणा		WP_TCVR			(1 << 7)
#घोषणा		WP_TOCR			(1 << 8)
#घोषणा		WP_TOWR			(1 << 9)
#घोषणा _OMAP_TIMER_MATCH_OFFSET	0x38
#घोषणा _OMAP_TIMER_CAPTURE_OFFSET	0x3c
#घोषणा _OMAP_TIMER_IF_CTRL_OFFSET	0x40
#घोषणा _OMAP_TIMER_CAPTURE2_OFFSET		0x44	/* TCAR2, 34xx only */
#घोषणा _OMAP_TIMER_TICK_POS_OFFSET		0x48	/* TPIR, 34xx only */
#घोषणा _OMAP_TIMER_TICK_NEG_OFFSET		0x4c	/* TNIR, 34xx only */
#घोषणा _OMAP_TIMER_TICK_COUNT_OFFSET		0x50	/* TCVR, 34xx only */
#घोषणा _OMAP_TIMER_TICK_INT_MASK_SET_OFFSET	0x54	/* TOCR, 34xx only */
#घोषणा _OMAP_TIMER_TICK_INT_MASK_COUNT_OFFSET	0x58	/* TOWR, 34xx only */

/* रेजिस्टर offsets with the ग_लिखो pending bit encoded */
#घोषणा	WPSHIFT					16

#घोषणा OMAP_TIMER_WAKEUP_EN_REG		(_OMAP_TIMER_WAKEUP_EN_OFFSET \
							| (WP_NONE << WPSHIFT))

#घोषणा OMAP_TIMER_CTRL_REG			(_OMAP_TIMER_CTRL_OFFSET \
							| (WP_TCLR << WPSHIFT))

#घोषणा OMAP_TIMER_COUNTER_REG			(_OMAP_TIMER_COUNTER_OFFSET \
							| (WP_TCRR << WPSHIFT))

#घोषणा OMAP_TIMER_LOAD_REG			(_OMAP_TIMER_LOAD_OFFSET \
							| (WP_TLDR << WPSHIFT))

#घोषणा OMAP_TIMER_TRIGGER_REG			(_OMAP_TIMER_TRIGGER_OFFSET \
							| (WP_TTGR << WPSHIFT))

#घोषणा OMAP_TIMER_WRITE_PEND_REG		(_OMAP_TIMER_WRITE_PEND_OFFSET \
							| (WP_NONE << WPSHIFT))

#घोषणा OMAP_TIMER_MATCH_REG			(_OMAP_TIMER_MATCH_OFFSET \
							| (WP_TMAR << WPSHIFT))

#घोषणा OMAP_TIMER_CAPTURE_REG			(_OMAP_TIMER_CAPTURE_OFFSET \
							| (WP_NONE << WPSHIFT))

#घोषणा OMAP_TIMER_IF_CTRL_REG			(_OMAP_TIMER_IF_CTRL_OFFSET \
							| (WP_NONE << WPSHIFT))

#घोषणा OMAP_TIMER_CAPTURE2_REG			(_OMAP_TIMER_CAPTURE2_OFFSET \
							| (WP_NONE << WPSHIFT))

#घोषणा OMAP_TIMER_TICK_POS_REG			(_OMAP_TIMER_TICK_POS_OFFSET \
							| (WP_TPIR << WPSHIFT))

#घोषणा OMAP_TIMER_TICK_NEG_REG			(_OMAP_TIMER_TICK_NEG_OFFSET \
							| (WP_TNIR << WPSHIFT))

#घोषणा OMAP_TIMER_TICK_COUNT_REG		(_OMAP_TIMER_TICK_COUNT_OFFSET \
							| (WP_TCVR << WPSHIFT))

#घोषणा OMAP_TIMER_TICK_INT_MASK_SET_REG				\
		(_OMAP_TIMER_TICK_INT_MASK_SET_OFFSET | (WP_TOCR << WPSHIFT))

#घोषणा OMAP_TIMER_TICK_INT_MASK_COUNT_REG				\
		(_OMAP_TIMER_TICK_INT_MASK_COUNT_OFFSET | (WP_TOWR << WPSHIFT))

/*
 * The below are अंतरभूतd to optimize code size क्रम प्रणाली समयrs. Other code
 * should not need these at all.
 */
#अगर defined(CONFIG_ARCH_OMAP1) || defined(CONFIG_ARCH_OMAP2PLUS)
अटल अंतरभूत u32 __omap_dm_समयr_पढ़ो(काष्ठा omap_dm_समयr *समयr, u32 reg,
						पूर्णांक posted)
अणु
	अगर (posted)
		जबतक (पढ़ोl_relaxed(समयr->pend) & (reg >> WPSHIFT))
			cpu_relax();

	वापस पढ़ोl_relaxed(समयr->func_base + (reg & 0xff));
पूर्ण

अटल अंतरभूत व्योम __omap_dm_समयr_ग_लिखो(काष्ठा omap_dm_समयr *समयr,
					u32 reg, u32 val, पूर्णांक posted)
अणु
	अगर (posted)
		जबतक (पढ़ोl_relaxed(समयr->pend) & (reg >> WPSHIFT))
			cpu_relax();

	ग_लिखोl_relaxed(val, समयr->func_base + (reg & 0xff));
पूर्ण

अटल अंतरभूत व्योम __omap_dm_समयr_init_regs(काष्ठा omap_dm_समयr *समयr)
अणु
	u32 tidr;

	/* Assume v1 ip अगर bits [31:16] are zero */
	tidr = पढ़ोl_relaxed(समयr->io_base);
	अगर (!(tidr >> 16)) अणु
		समयr->revision = 1;
		समयr->irq_stat = समयr->io_base + OMAP_TIMER_V1_STAT_OFFSET;
		समयr->irq_ena = समयr->io_base + OMAP_TIMER_V1_INT_EN_OFFSET;
		समयr->irq_dis = समयr->io_base + OMAP_TIMER_V1_INT_EN_OFFSET;
		समयr->pend = समयr->io_base + _OMAP_TIMER_WRITE_PEND_OFFSET;
		समयr->func_base = समयr->io_base;
	पूर्ण अन्यथा अणु
		समयr->revision = 2;
		समयr->irq_stat = समयr->io_base + OMAP_TIMER_V2_IRQSTATUS;
		समयr->irq_ena = समयr->io_base + OMAP_TIMER_V2_IRQENABLE_SET;
		समयr->irq_dis = समयr->io_base + OMAP_TIMER_V2_IRQENABLE_CLR;
		समयr->pend = समयr->io_base +
			_OMAP_TIMER_WRITE_PEND_OFFSET +
				OMAP_TIMER_V2_FUNC_OFFSET;
		समयr->func_base = समयr->io_base + OMAP_TIMER_V2_FUNC_OFFSET;
	पूर्ण
पूर्ण

/*
 * __omap_dm_समयr_enable_posted - enables ग_लिखो posted mode
 * @समयr:      poपूर्णांकer to समयr instance handle
 *
 * Enables the ग_लिखो posted mode क्रम the समयr. When posted mode is enabled
 * ग_लिखोs to certain समयr रेजिस्टरs are immediately acknowledged by the
 * पूर्णांकernal bus and hence prevents stalling the CPU रुकोing क्रम the ग_लिखो to
 * complete. Enabling this feature can improve perक्रमmance क्रम writing to the
 * समयr रेजिस्टरs.
 */
अटल अंतरभूत व्योम __omap_dm_समयr_enable_posted(काष्ठा omap_dm_समयr *समयr)
अणु
	अगर (समयr->posted)
		वापस;

	अगर (समयr->errata & OMAP_TIMER_ERRATA_I103_I767) अणु
		समयr->posted = OMAP_TIMER_NONPOSTED;
		__omap_dm_समयr_ग_लिखो(समयr, OMAP_TIMER_IF_CTRL_REG, 0, 0);
		वापस;
	पूर्ण

	__omap_dm_समयr_ग_लिखो(समयr, OMAP_TIMER_IF_CTRL_REG,
			      OMAP_TIMER_CTRL_POSTED, 0);
	समयr->context.tsicr = OMAP_TIMER_CTRL_POSTED;
	समयr->posted = OMAP_TIMER_POSTED;
पूर्ण

/**
 * __omap_dm_समयr_override_errata - override errata flags क्रम a समयr
 * @समयr:      poपूर्णांकer to समयr handle
 * @errata:	errata flags to be ignored
 *
 * For a given समयr, override a समयr errata by clearing the flags
 * specअगरied by the errata argument. A specअगरic erratum should only be
 * overridden क्रम a समयr अगर the समयr is used in such a way the erratum
 * has no impact.
 */
अटल अंतरभूत व्योम __omap_dm_समयr_override_errata(काष्ठा omap_dm_समयr *समयr,
						   u32 errata)
अणु
	समयr->errata &= ~errata;
पूर्ण

अटल अंतरभूत व्योम __omap_dm_समयr_stop(काष्ठा omap_dm_समयr *समयr,
					पूर्णांक posted, अचिन्हित दीर्घ rate)
अणु
	u32 l;

	l = __omap_dm_समयr_पढ़ो(समयr, OMAP_TIMER_CTRL_REG, posted);
	अगर (l & OMAP_TIMER_CTRL_ST) अणु
		l &= ~0x1;
		__omap_dm_समयr_ग_लिखो(समयr, OMAP_TIMER_CTRL_REG, l, posted);
#अगर_घोषित CONFIG_ARCH_OMAP2PLUS
		/* Readback to make sure ग_लिखो has completed */
		__omap_dm_समयr_पढ़ो(समयr, OMAP_TIMER_CTRL_REG, posted);
		/*
		 * Wait क्रम functional घड़ी period x 3.5 to make sure that
		 * समयr is stopped
		 */
		udelay(3500000 / rate + 1);
#पूर्ण_अगर
	पूर्ण

	/* Ack possibly pending पूर्णांकerrupt */
	ग_लिखोl_relaxed(OMAP_TIMER_INT_OVERFLOW, समयr->irq_stat);
पूर्ण

अटल अंतरभूत व्योम __omap_dm_समयr_load_start(काष्ठा omap_dm_समयr *समयr,
						u32 ctrl, अचिन्हित पूर्णांक load,
						पूर्णांक posted)
अणु
	__omap_dm_समयr_ग_लिखो(समयr, OMAP_TIMER_COUNTER_REG, load, posted);
	__omap_dm_समयr_ग_लिखो(समयr, OMAP_TIMER_CTRL_REG, ctrl, posted);
पूर्ण

अटल अंतरभूत व्योम __omap_dm_समयr_पूर्णांक_enable(काष्ठा omap_dm_समयr *समयr,
						अचिन्हित पूर्णांक value)
अणु
	ग_लिखोl_relaxed(value, समयr->irq_ena);
	__omap_dm_समयr_ग_लिखो(समयr, OMAP_TIMER_WAKEUP_EN_REG, value, 0);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
__omap_dm_समयr_पढ़ो_counter(काष्ठा omap_dm_समयr *समयr, पूर्णांक posted)
अणु
	वापस __omap_dm_समयr_पढ़ो(समयr, OMAP_TIMER_COUNTER_REG, posted);
पूर्ण

अटल अंतरभूत व्योम __omap_dm_समयr_ग_लिखो_status(काष्ठा omap_dm_समयr *समयr,
						अचिन्हित पूर्णांक value)
अणु
	ग_लिखोl_relaxed(value, समयr->irq_stat);
पूर्ण
#पूर्ण_अगर /* CONFIG_ARCH_OMAP1 || CONFIG_ARCH_OMAP2PLUS */
#पूर्ण_अगर /* __CLOCKSOURCE_DMTIMER_H */
