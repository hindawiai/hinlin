<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) 2001, 2002, 2003 Broadcom Corporation
 * Copyright (C) 2007 Ralf Baechle <ralf@linux-mips.org>
 * Copyright (C) 2007 MIPS Technologies, Inc.
 *    written by Ralf Baechle <ralf@linux-mips.org>
 */

#अघोषित DEBUG

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/fs.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/रुको.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/sibyte/sb1250.h>

#अगर defined(CONFIG_SIBYTE_BCM1x55) || defined(CONFIG_SIBYTE_BCM1x80)
#समावेश <यंत्र/sibyte/bcm1480_regs.h>
#समावेश <यंत्र/sibyte/bcm1480_scd.h>
#समावेश <यंत्र/sibyte/bcm1480_पूर्णांक.h>
#या_अगर defined(CONFIG_SIBYTE_SB1250) || defined(CONFIG_SIBYTE_BCM112X)
#समावेश <यंत्र/sibyte/sb1250_regs.h>
#समावेश <यंत्र/sibyte/sb1250_scd.h>
#समावेश <यंत्र/sibyte/sb1250_पूर्णांक.h>
#अन्यथा
#त्रुटि invalid SiByte UART configuration
#पूर्ण_अगर

#अगर defined(CONFIG_SIBYTE_BCM1x55) || defined(CONFIG_SIBYTE_BCM1x80)
#अघोषित K_INT_TRACE_FREEZE
#घोषणा K_INT_TRACE_FREEZE K_BCM1480_INT_TRACE_FREEZE
#अघोषित K_INT_PERF_CNT
#घोषणा K_INT_PERF_CNT K_BCM1480_INT_PERF_CNT
#पूर्ण_अगर

#समावेश <linux/uaccess.h>

#घोषणा SBPROF_TB_MAJOR 240

प्रकार u64 tb_sample_t[6*256];

क्रमागत खोलो_status अणु
	SB_CLOSED,
	SB_OPENING,
	SB_OPEN
पूर्ण;

काष्ठा sbprof_tb अणु
	रुको_queue_head_t	tb_sync;
	रुको_queue_head_t	tb_पढ़ो;
	काष्ठा mutex		lock;
	क्रमागत खोलो_status	खोलो;
	tb_sample_t		*sbprof_tbbuf;
	पूर्णांक			next_tb_sample;

	अस्थिर पूर्णांक		tb_enable;
	अस्थिर पूर्णांक		tb_armed;

पूर्ण;

अटल काष्ठा sbprof_tb sbp;

#घोषणा MAX_SAMPLE_BYTES (24*1024*1024)
#घोषणा MAX_TBSAMPLE_BYTES (12*1024*1024)

#घोषणा MAX_SAMPLES (MAX_SAMPLE_BYTES/माप(u_पूर्णांक32_t))
#घोषणा TB_SAMPLE_SIZE (माप(tb_sample_t))
#घोषणा MAX_TB_SAMPLES (MAX_TBSAMPLE_BYTES/TB_SAMPLE_SIZE)

/* ioctls */
#घोषणा SBPROF_ZBSTART		_IOW('s', 0, पूर्णांक)
#घोषणा SBPROF_ZBSTOP		_IOW('s', 1, पूर्णांक)
#घोषणा SBPROF_ZBWAITFULL	_IOW('s', 2, पूर्णांक)

/*
 * Routines क्रम using 40-bit SCD cycle counter
 *
 * Client responsible क्रम either handling पूर्णांकerrupts or making sure
 * the cycles counter never saturates, e.g., by करोing
 * zclk_समयr_init(0) at least every 2^40 - 1 ZCLKs.
 */

/*
 * Configures SCD counter 0 to count ZCLKs starting from val;
 * Configures SCD counters1,2,3 to count nothing.
 * Must not be called जबतक gathering ZBbus profiles.
 */

#घोषणा zclk_समयr_init(val) \
  __यंत्र__ __अस्थिर__ (".set push;" \
			".set mips64;" \
			"la   $8, 0xb00204c0;" /* SCD perf_cnt_cfg */ \
			"sd   %0, 0x10($8);"   /* ग_लिखो val to counter0 */ \
			"sd   %1, 0($8);"      /* config counter0 क्रम zclks*/ \
			".set pop" \
			: /* no outमाला_दो */ \
						     /* enable, counter0 */ \
			: /* inमाला_दो */ "r"(val), "r" ((1ULL << 33) | 1ULL) \
			: /* modअगरies */ "$8" )


/* Reads SCD counter 0 and माला_दो result in value
   अचिन्हित दीर्घ दीर्घ val; */
#घोषणा zclk_get(val) \
  __यंत्र__ __अस्थिर__ (".set push;" \
			".set mips64;" \
			"la   $8, 0xb00204c0;" /* SCD perf_cnt_cfg */ \
			"ld   %0, 0x10($8);"   /* ग_लिखो val to counter0 */ \
			".set pop" \
			: /* outमाला_दो */ "=r"(val) \
			: /* inमाला_दो */ \
			: /* modअगरies */ "$8" )

#घोषणा DEVNAME "sb_tbprof"

#घोषणा TB_FULL (sbp.next_tb_sample == MAX_TB_SAMPLES)

/*
 * Support क्रम ZBbus sampling using the trace buffer
 *
 * We use the SCD perक्रमmance counter पूर्णांकerrupt, caused by a Zclk counter
 * overflow, to trigger the start of tracing.
 *
 * We set the trace buffer to sample everything and मुक्तze on
 * overflow.
 *
 * We map the पूर्णांकerrupt क्रम trace_buffer_मुक्तze to handle it on CPU 0.
 *
 */

अटल u64 tb_period;

अटल व्योम arm_tb(व्योम)
अणु
	u64 scdperfcnt;
	u64 next = (1ULL << 40) - tb_period;
	u64 tb_options = M_SCD_TRACE_CFG_FREEZE_FULL;

	/*
	 * Generate an SCD_PERFCNT पूर्णांकerrupt in TB_PERIOD Zclks to
	 * trigger start of trace.  XXX vary sampling period
	 */
	__raw_ग_लिखोq(0, IOADDR(A_SCD_PERF_CNT_1));
	scdperfcnt = __raw_पढ़ोq(IOADDR(A_SCD_PERF_CNT_CFG));

	/*
	 * Unक्रमtunately, in Pass 2 we must clear all counters to knock करोwn
	 * a previous पूर्णांकerrupt request.  This means that bus profiling
	 * requires ALL of the SCD perf counters.
	 */
#अगर defined(CONFIG_SIBYTE_BCM1x55) || defined(CONFIG_SIBYTE_BCM1x80)
	__raw_ग_लिखोq((scdperfcnt & ~M_SPC_CFG_SRC1) |
						/* keep counters 0,2,3,4,5,6,7 as is */
		     V_SPC_CFG_SRC1(1),		/* counter 1 counts cycles */
		     IOADDR(A_BCM1480_SCD_PERF_CNT_CFG0));
	__raw_ग_लिखोq(
		     M_SPC_CFG_ENABLE |		/* enable counting */
		     M_SPC_CFG_CLEAR |		/* clear all counters */
		     V_SPC_CFG_SRC1(1),		/* counter 1 counts cycles */
		     IOADDR(A_BCM1480_SCD_PERF_CNT_CFG1));
#अन्यथा
	__raw_ग_लिखोq((scdperfcnt & ~M_SPC_CFG_SRC1) |
						/* keep counters 0,2,3 as is */
		     M_SPC_CFG_ENABLE |		/* enable counting */
		     M_SPC_CFG_CLEAR |		/* clear all counters */
		     V_SPC_CFG_SRC1(1),		/* counter 1 counts cycles */
		     IOADDR(A_SCD_PERF_CNT_CFG));
#पूर्ण_अगर
	__raw_ग_लिखोq(next, IOADDR(A_SCD_PERF_CNT_1));
	/* Reset the trace buffer */
	__raw_ग_लिखोq(M_SCD_TRACE_CFG_RESET, IOADDR(A_SCD_TRACE_CFG));
#अगर 0 && defined(M_SCD_TRACE_CFG_FORCECNT)
	/* XXXKW may want to expose control to the data-collector */
	tb_options |= M_SCD_TRACE_CFG_FORCECNT;
#पूर्ण_अगर
	__raw_ग_लिखोq(tb_options, IOADDR(A_SCD_TRACE_CFG));
	sbp.tb_armed = 1;
पूर्ण

अटल irqवापस_t sbprof_tb_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक i;

	pr_debug(DEVNAME ": tb_intr\n");

	अगर (sbp.next_tb_sample < MAX_TB_SAMPLES) अणु
		/* XXX should use XKPHYS to make ग_लिखोs bypass L2 */
		u64 *p = sbp.sbprof_tbbuf[sbp.next_tb_sample++];
		/* Read out trace */
		__raw_ग_लिखोq(M_SCD_TRACE_CFG_START_READ,
			     IOADDR(A_SCD_TRACE_CFG));
		__यंत्र__ __अस्थिर__ ("sync" : : : "memory");
		/* Loop runs backwards because bundles are पढ़ो out in reverse order */
		क्रम (i = 256 * 6; i > 0; i -= 6) अणु
			/* Subscripts decrease to put bundle in the order */
			/*   t0 lo, t0 hi, t1 lo, t1 hi, t2 lo, t2 hi */
			p[i - 1] = __raw_पढ़ोq(IOADDR(A_SCD_TRACE_READ));
			/* पढ़ो t2 hi */
			p[i - 2] = __raw_पढ़ोq(IOADDR(A_SCD_TRACE_READ));
			/* पढ़ो t2 lo */
			p[i - 3] = __raw_पढ़ोq(IOADDR(A_SCD_TRACE_READ));
			/* पढ़ो t1 hi */
			p[i - 4] = __raw_पढ़ोq(IOADDR(A_SCD_TRACE_READ));
			/* पढ़ो t1 lo */
			p[i - 5] = __raw_पढ़ोq(IOADDR(A_SCD_TRACE_READ));
			/* पढ़ो t0 hi */
			p[i - 6] = __raw_पढ़ोq(IOADDR(A_SCD_TRACE_READ));
			/* पढ़ो t0 lo */
		पूर्ण
		अगर (!sbp.tb_enable) अणु
			pr_debug(DEVNAME ": tb_intr shutdown\n");
			__raw_ग_लिखोq(M_SCD_TRACE_CFG_RESET,
				     IOADDR(A_SCD_TRACE_CFG));
			sbp.tb_armed = 0;
			wake_up_पूर्णांकerruptible(&sbp.tb_sync);
		पूर्ण अन्यथा अणु
			/* knock करोwn current पूर्णांकerrupt and get another one later */
			arm_tb();
		पूर्ण
	पूर्ण अन्यथा अणु
		/* No more trace buffer samples */
		pr_debug(DEVNAME ": tb_intr full\n");
		__raw_ग_लिखोq(M_SCD_TRACE_CFG_RESET, IOADDR(A_SCD_TRACE_CFG));
		sbp.tb_armed = 0;
		अगर (!sbp.tb_enable)
			wake_up_पूर्णांकerruptible(&sbp.tb_sync);
		wake_up_पूर्णांकerruptible(&sbp.tb_पढ़ो);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t sbprof_pc_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	prपूर्णांकk(DEVNAME ": unexpected pc_intr");
	वापस IRQ_NONE;
पूर्ण

/*
 * Requires: Alपढ़ोy called zclk_समयr_init with a value that won't
 *	     saturate 40 bits.	No subsequent use of SCD perक्रमmance counters
 *	     or trace buffer.
 */

अटल पूर्णांक sbprof_zbprof_start(काष्ठा file *filp)
अणु
	u64 scdperfcnt;
	पूर्णांक err;

	अगर (xchg(&sbp.tb_enable, 1))
		वापस -EBUSY;

	pr_debug(DEVNAME ": starting\n");

	sbp.next_tb_sample = 0;
	filp->f_pos = 0;

	err = request_irq(K_INT_TRACE_FREEZE, sbprof_tb_पूर्णांकr, 0,
			  DEVNAME " trace freeze", &sbp);
	अगर (err)
		वापस -EBUSY;

	/* Make sure there isn't a perf-cnt पूर्णांकerrupt रुकोing */
	scdperfcnt = __raw_पढ़ोq(IOADDR(A_SCD_PERF_CNT_CFG));
	/* Disable and clear counters, override SRC_1 */
	__raw_ग_लिखोq((scdperfcnt & ~(M_SPC_CFG_SRC1 | M_SPC_CFG_ENABLE)) |
		     M_SPC_CFG_ENABLE | M_SPC_CFG_CLEAR | V_SPC_CFG_SRC1(1),
		     IOADDR(A_SCD_PERF_CNT_CFG));

	/*
	 * We grab this पूर्णांकerrupt to prevent others from trying to use
	 * it, even though we करोn't want to service the पूर्णांकerrupts
	 * (they only feed पूर्णांकo the trace-on-पूर्णांकerrupt mechanism)
	 */
	अगर (request_irq(K_INT_PERF_CNT, sbprof_pc_पूर्णांकr, 0, DEVNAME " scd perfcnt", &sbp)) अणु
		मुक्त_irq(K_INT_TRACE_FREEZE, &sbp);
		वापस -EBUSY;
	पूर्ण

	/*
	 * I need the core to mask these, but the पूर्णांकerrupt mapper to
	 *  pass them through.	I am exploiting my knowledge that
	 *  cp0_status masks out IP[5]. krw
	 */
#अगर defined(CONFIG_SIBYTE_BCM1x55) || defined(CONFIG_SIBYTE_BCM1x80)
	__raw_ग_लिखोq(K_BCM1480_INT_MAP_I3,
		     IOADDR(A_BCM1480_IMR_REGISTER(0, R_BCM1480_IMR_INTERRUPT_MAP_BASE_L) +
			    ((K_BCM1480_INT_PERF_CNT & 0x3f) << 3)));
#अन्यथा
	__raw_ग_लिखोq(K_INT_MAP_I3,
		     IOADDR(A_IMR_REGISTER(0, R_IMR_INTERRUPT_MAP_BASE) +
			    (K_INT_PERF_CNT << 3)));
#पूर्ण_अगर

	/* Initialize address traps */
	__raw_ग_लिखोq(0, IOADDR(A_ADDR_TRAP_UP_0));
	__raw_ग_लिखोq(0, IOADDR(A_ADDR_TRAP_UP_1));
	__raw_ग_लिखोq(0, IOADDR(A_ADDR_TRAP_UP_2));
	__raw_ग_लिखोq(0, IOADDR(A_ADDR_TRAP_UP_3));

	__raw_ग_लिखोq(0, IOADDR(A_ADDR_TRAP_DOWN_0));
	__raw_ग_लिखोq(0, IOADDR(A_ADDR_TRAP_DOWN_1));
	__raw_ग_लिखोq(0, IOADDR(A_ADDR_TRAP_DOWN_2));
	__raw_ग_लिखोq(0, IOADDR(A_ADDR_TRAP_DOWN_3));

	__raw_ग_लिखोq(0, IOADDR(A_ADDR_TRAP_CFG_0));
	__raw_ग_लिखोq(0, IOADDR(A_ADDR_TRAP_CFG_1));
	__raw_ग_लिखोq(0, IOADDR(A_ADDR_TRAP_CFG_2));
	__raw_ग_लिखोq(0, IOADDR(A_ADDR_TRAP_CFG_3));

	/* Initialize Trace Event 0-7 */
	/*				when पूर्णांकerrupt	*/
	__raw_ग_लिखोq(M_SCD_TREVT_INTERRUPT, IOADDR(A_SCD_TRACE_EVENT_0));
	__raw_ग_लिखोq(0, IOADDR(A_SCD_TRACE_EVENT_1));
	__raw_ग_लिखोq(0, IOADDR(A_SCD_TRACE_EVENT_2));
	__raw_ग_लिखोq(0, IOADDR(A_SCD_TRACE_EVENT_3));
	__raw_ग_लिखोq(0, IOADDR(A_SCD_TRACE_EVENT_4));
	__raw_ग_लिखोq(0, IOADDR(A_SCD_TRACE_EVENT_5));
	__raw_ग_लिखोq(0, IOADDR(A_SCD_TRACE_EVENT_6));
	__raw_ग_लिखोq(0, IOADDR(A_SCD_TRACE_EVENT_7));

	/* Initialize Trace Sequence 0-7 */
	/*				     Start on event 0 (पूर्णांकerrupt) */
	__raw_ग_लिखोq(V_SCD_TRSEQ_FUNC_START | 0x0fff,
		     IOADDR(A_SCD_TRACE_SEQUENCE_0));
	/*			  dsamp when d used | asamp when a used */
	__raw_ग_लिखोq(M_SCD_TRSEQ_ASAMPLE | M_SCD_TRSEQ_DSAMPLE |
		     K_SCD_TRSEQ_TRIGGER_ALL,
		     IOADDR(A_SCD_TRACE_SEQUENCE_1));
	__raw_ग_लिखोq(0, IOADDR(A_SCD_TRACE_SEQUENCE_2));
	__raw_ग_लिखोq(0, IOADDR(A_SCD_TRACE_SEQUENCE_3));
	__raw_ग_लिखोq(0, IOADDR(A_SCD_TRACE_SEQUENCE_4));
	__raw_ग_लिखोq(0, IOADDR(A_SCD_TRACE_SEQUENCE_5));
	__raw_ग_लिखोq(0, IOADDR(A_SCD_TRACE_SEQUENCE_6));
	__raw_ग_लिखोq(0, IOADDR(A_SCD_TRACE_SEQUENCE_7));

	/* Now indicate the PERF_CNT पूर्णांकerrupt as a trace-relevant पूर्णांकerrupt */
#अगर defined(CONFIG_SIBYTE_BCM1x55) || defined(CONFIG_SIBYTE_BCM1x80)
	__raw_ग_लिखोq(1ULL << (K_BCM1480_INT_PERF_CNT & 0x3f),
		     IOADDR(A_BCM1480_IMR_REGISTER(0, R_BCM1480_IMR_INTERRUPT_TRACE_L)));
#अन्यथा
	__raw_ग_लिखोq(1ULL << K_INT_PERF_CNT,
		     IOADDR(A_IMR_REGISTER(0, R_IMR_INTERRUPT_TRACE)));
#पूर्ण_अगर
	arm_tb();

	pr_debug(DEVNAME ": done starting\n");

	वापस 0;
पूर्ण

अटल पूर्णांक sbprof_zbprof_stop(व्योम)
अणु
	पूर्णांक err = 0;

	pr_debug(DEVNAME ": stopping\n");

	अगर (sbp.tb_enable) अणु
		/*
		 * XXXKW there is a winकरोw here where the पूर्णांकr handler may run,
		 * see the disable, and करो the wake_up beक्रमe this sleep
		 * happens.
		 */
		pr_debug(DEVNAME ": wait for disarm\n");
		err = रुको_event_पूर्णांकerruptible(sbp.tb_sync, !sbp.tb_armed);
		pr_debug(DEVNAME ": disarm complete, stat %d\n", err);

		अगर (err)
			वापस err;

		sbp.tb_enable = 0;
		मुक्त_irq(K_INT_TRACE_FREEZE, &sbp);
		मुक्त_irq(K_INT_PERF_CNT, &sbp);
	पूर्ण

	pr_debug(DEVNAME ": done stopping\n");

	वापस err;
पूर्ण

अटल पूर्णांक sbprof_tb_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	पूर्णांक minor;

	minor = iminor(inode);
	अगर (minor != 0)
		वापस -ENODEV;

	अगर (xchg(&sbp.खोलो, SB_OPENING) != SB_CLOSED)
		वापस -EBUSY;

	स_रखो(&sbp, 0, माप(काष्ठा sbprof_tb));
	sbp.sbprof_tbbuf = vzalloc(MAX_TBSAMPLE_BYTES);
	अगर (!sbp.sbprof_tbbuf) अणु
		sbp.खोलो = SB_CLOSED;
		wmb();
		वापस -ENOMEM;
	पूर्ण

	init_रुकोqueue_head(&sbp.tb_sync);
	init_रुकोqueue_head(&sbp.tb_पढ़ो);
	mutex_init(&sbp.lock);

	sbp.खोलो = SB_OPEN;
	wmb();

	वापस 0;
पूर्ण

अटल पूर्णांक sbprof_tb_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	पूर्णांक minor;

	minor = iminor(inode);
	अगर (minor != 0 || sbp.खोलो != SB_CLOSED)
		वापस -ENODEV;

	mutex_lock(&sbp.lock);

	अगर (sbp.tb_armed || sbp.tb_enable)
		sbprof_zbprof_stop();

	vमुक्त(sbp.sbprof_tbbuf);
	sbp.खोलो = SB_CLOSED;
	wmb();

	mutex_unlock(&sbp.lock);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार sbprof_tb_पढ़ो(काष्ठा file *filp, अक्षर *buf,
			      माप_प्रकार size, loff_t *offp)
अणु
	पूर्णांक cur_sample, sample_off, cur_count, sample_left;
	अक्षर *src;
	पूर्णांक   count   =	 0;
	अक्षर *dest    =	 buf;
	दीर्घ  cur_off = *offp;

	अगर (!access_ok(buf, size))
		वापस -EFAULT;

	mutex_lock(&sbp.lock);

	count = 0;
	cur_sample = cur_off / TB_SAMPLE_SIZE;
	sample_off = cur_off % TB_SAMPLE_SIZE;
	sample_left = TB_SAMPLE_SIZE - sample_off;

	जबतक (size && (cur_sample < sbp.next_tb_sample)) अणु
		पूर्णांक err;

		cur_count = size < sample_left ? size : sample_left;
		src = (अक्षर *)(((दीर्घ)sbp.sbprof_tbbuf[cur_sample])+sample_off);
		err = __copy_to_user(dest, src, cur_count);
		अगर (err) अणु
			*offp = cur_off + cur_count - err;
			mutex_unlock(&sbp.lock);
			वापस err;
		पूर्ण
		pr_debug(DEVNAME ": read from sample %d, %d bytes\n",
			 cur_sample, cur_count);
		size -= cur_count;
		sample_left -= cur_count;
		अगर (!sample_left) अणु
			cur_sample++;
			sample_off = 0;
			sample_left = TB_SAMPLE_SIZE;
		पूर्ण अन्यथा अणु
			sample_off += cur_count;
		पूर्ण
		cur_off += cur_count;
		dest += cur_count;
		count += cur_count;
	पूर्ण
	*offp = cur_off;
	mutex_unlock(&sbp.lock);

	वापस count;
पूर्ण

अटल दीर्घ sbprof_tb_ioctl(काष्ठा file *filp,
			    अचिन्हित पूर्णांक command,
			    अचिन्हित दीर्घ arg)
अणु
	पूर्णांक err = 0;

	चयन (command) अणु
	हाल SBPROF_ZBSTART:
		mutex_lock(&sbp.lock);
		err = sbprof_zbprof_start(filp);
		mutex_unlock(&sbp.lock);
		अवरोध;

	हाल SBPROF_ZBSTOP:
		mutex_lock(&sbp.lock);
		err = sbprof_zbprof_stop();
		mutex_unlock(&sbp.lock);
		अवरोध;

	हाल SBPROF_ZBWAITFULL: अणु
		err = रुको_event_पूर्णांकerruptible(sbp.tb_पढ़ो, TB_FULL);
		अगर (err)
			अवरोध;

		err = put_user(TB_FULL, (पूर्णांक *) arg);
		अवरोध;
	पूर्ण

	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा file_operations sbprof_tb_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= sbprof_tb_खोलो,
	.release	= sbprof_tb_release,
	.पढ़ो		= sbprof_tb_पढ़ो,
	.unlocked_ioctl = sbprof_tb_ioctl,
	.compat_ioctl	= sbprof_tb_ioctl,
	.mmap		= शून्य,
	.llseek		= शेष_llseek,
पूर्ण;

अटल काष्ठा class *tb_class;
अटल काष्ठा device *tb_dev;

अटल पूर्णांक __init sbprof_tb_init(व्योम)
अणु
	काष्ठा device *dev;
	काष्ठा class *tbc;
	पूर्णांक err;

	अगर (रेजिस्टर_chrdev(SBPROF_TB_MAJOR, DEVNAME, &sbprof_tb_fops)) अणु
		prपूर्णांकk(KERN_WARNING DEVNAME ": initialization failed (dev %d)\n",
		       SBPROF_TB_MAJOR);
		वापस -EIO;
	पूर्ण

	tbc = class_create(THIS_MODULE, "sb_tracebuffer");
	अगर (IS_ERR(tbc)) अणु
		err = PTR_ERR(tbc);
		जाओ out_chrdev;
	पूर्ण

	tb_class = tbc;

	dev = device_create(tbc, शून्य, MKDEV(SBPROF_TB_MAJOR, 0), शून्य, "tb");
	अगर (IS_ERR(dev)) अणु
		err = PTR_ERR(dev);
		जाओ out_class;
	पूर्ण
	tb_dev = dev;

	sbp.खोलो = SB_CLOSED;
	wmb();
	tb_period = zbbus_mhz * 10000LL;
	pr_info(DEVNAME ": initialized - tb_period = %lld\n",
		(दीर्घ दीर्घ) tb_period);
	वापस 0;

out_class:
	class_destroy(tb_class);
out_chrdev:
	unरेजिस्टर_chrdev(SBPROF_TB_MAJOR, DEVNAME);

	वापस err;
पूर्ण

अटल व्योम __निकास sbprof_tb_cleanup(व्योम)
अणु
	device_destroy(tb_class, MKDEV(SBPROF_TB_MAJOR, 0));
	unरेजिस्टर_chrdev(SBPROF_TB_MAJOR, DEVNAME);
	class_destroy(tb_class);
पूर्ण

module_init(sbprof_tb_init);
module_निकास(sbprof_tb_cleanup);

MODULE_ALIAS_CHARDEV_MAJOR(SBPROF_TB_MAJOR);
MODULE_AUTHOR("Ralf Baechle <ralf@linux-mips.org>");
MODULE_LICENSE("GPL");
