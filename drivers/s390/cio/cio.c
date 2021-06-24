<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *   S/390 common I/O routines -- low level i/o calls
 *
 *    Copyright IBM Corp. 1999, 2008
 *    Author(s): Ingo Adlung (adlung@de.ibm.com)
 *		 Cornelia Huck (cornelia.huck@de.ibm.com)
 *		 Arnd Bergmann (arndb@de.ibm.com)
 *		 Martin Schwidefsky (schwidefsky@de.ibm.com)
 */

#घोषणा KMSG_COMPONENT "cio"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/ftrace.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <यंत्र/cपन.स>
#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/irq_regs.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/ipl.h>
#समावेश <यंत्र/chpid.h>
#समावेश <यंत्र/airq.h>
#समावेश <यंत्र/isc.h>
#समावेश <linux/sched/cpuसमय.स>
#समावेश <यंत्र/fcx.h>
#समावेश <यंत्र/nmi.h>
#समावेश <यंत्र/crw.h>
#समावेश "cio.h"
#समावेश "css.h"
#समावेश "chsc.h"
#समावेश "ioasm.h"
#समावेश "io_sch.h"
#समावेश "blacklist.h"
#समावेश "cio_debug.h"
#समावेश "chp.h"
#समावेश "trace.h"

debug_info_t *cio_debug_msg_id;
debug_info_t *cio_debug_trace_id;
debug_info_t *cio_debug_crw_id;

DEFINE_PER_CPU_ALIGNED(काष्ठा irb, cio_irb);
EXPORT_PER_CPU_SYMBOL(cio_irb);

/*
 * Function: cio_debug_init
 * Initializes three debug logs क्रम common I/O:
 * - cio_msg logs generic cio messages
 * - cio_trace logs the calling of dअगरferent functions
 * - cio_crw logs machine check related cio messages
 */
अटल पूर्णांक __init cio_debug_init(व्योम)
अणु
	cio_debug_msg_id = debug_रेजिस्टर("cio_msg", 16, 1, 11 * माप(दीर्घ));
	अगर (!cio_debug_msg_id)
		जाओ out_unरेजिस्टर;
	debug_रेजिस्टर_view(cio_debug_msg_id, &debug_प्र_लिखो_view);
	debug_set_level(cio_debug_msg_id, 2);
	cio_debug_trace_id = debug_रेजिस्टर("cio_trace", 16, 1, 16);
	अगर (!cio_debug_trace_id)
		जाओ out_unरेजिस्टर;
	debug_रेजिस्टर_view(cio_debug_trace_id, &debug_hex_ascii_view);
	debug_set_level(cio_debug_trace_id, 2);
	cio_debug_crw_id = debug_रेजिस्टर("cio_crw", 8, 1, 8 * माप(दीर्घ));
	अगर (!cio_debug_crw_id)
		जाओ out_unरेजिस्टर;
	debug_रेजिस्टर_view(cio_debug_crw_id, &debug_प्र_लिखो_view);
	debug_set_level(cio_debug_crw_id, 4);
	वापस 0;

out_unरेजिस्टर:
	debug_unरेजिस्टर(cio_debug_msg_id);
	debug_unरेजिस्टर(cio_debug_trace_id);
	debug_unरेजिस्टर(cio_debug_crw_id);
	वापस -1;
पूर्ण

arch_initcall (cio_debug_init);

पूर्णांक cio_set_options(काष्ठा subchannel *sch, पूर्णांक flags)
अणु
	काष्ठा io_subchannel_निजी *priv = to_io_निजी(sch);

	priv->options.suspend = (flags & DOIO_ALLOW_SUSPEND) != 0;
	priv->options.prefetch = (flags & DOIO_DENY_PREFETCH) != 0;
	priv->options.पूर्णांकer = (flags & DOIO_SUPPRESS_INTER) != 0;
	वापस 0;
पूर्ण

अटल पूर्णांक
cio_start_handle_notoper(काष्ठा subchannel *sch, __u8 lpm)
अणु
	अक्षर dbf_text[15];

	अगर (lpm != 0)
		sch->lpm &= ~lpm;
	अन्यथा
		sch->lpm = 0;

	CIO_MSG_EVENT(2, "cio_start: 'not oper' status for "
		      "subchannel 0.%x.%04x!\n", sch->schid.ssid,
		      sch->schid.sch_no);

	अगर (cio_update_schib(sch))
		वापस -ENODEV;

	प्र_लिखो(dbf_text, "no%s", dev_name(&sch->dev));
	CIO_TRACE_EVENT(0, dbf_text);
	CIO_HEX_EVENT(0, &sch->schib, माप (काष्ठा schib));

	वापस (sch->lpm ? -EACCES : -ENODEV);
पूर्ण

पूर्णांक
cio_start_key (काष्ठा subchannel *sch,	/* subchannel काष्ठाure */
	       काष्ठा ccw1 * cpa,	/* logical channel prog addr */
	       __u8 lpm,		/* logical path mask */
	       __u8 key)                /* storage key */
अणु
	काष्ठा io_subchannel_निजी *priv = to_io_निजी(sch);
	जोड़ orb *orb = &priv->orb;
	पूर्णांक ccode;

	CIO_TRACE_EVENT(5, "stIO");
	CIO_TRACE_EVENT(5, dev_name(&sch->dev));

	स_रखो(orb, 0, माप(जोड़ orb));
	/* sch is always under 2G. */
	orb->cmd.पूर्णांकparm = (u32)(addr_t)sch;
	orb->cmd.fmt = 1;

	orb->cmd.pfch = priv->options.prefetch == 0;
	orb->cmd.spnd = priv->options.suspend;
	orb->cmd.ssic = priv->options.suspend && priv->options.पूर्णांकer;
	orb->cmd.lpm = (lpm != 0) ? lpm : sch->lpm;
	/*
	 * क्रम 64 bit we always support 64 bit IDAWs with 4k page size only
	 */
	orb->cmd.c64 = 1;
	orb->cmd.i2k = 0;
	orb->cmd.key = key >> 4;
	/* issue "Start Subchannel" */
	orb->cmd.cpa = (__u32) __pa(cpa);
	ccode = ssch(sch->schid, orb);

	/* process condition code */
	CIO_HEX_EVENT(5, &ccode, माप(ccode));

	चयन (ccode) अणु
	हाल 0:
		/*
		 * initialize device status inक्रमmation
		 */
		sch->schib.scsw.cmd.actl |= SCSW_ACTL_START_PEND;
		वापस 0;
	हाल 1:		/* status pending */
	हाल 2:		/* busy */
		वापस -EBUSY;
	हाल 3:		/* device/path not operational */
		वापस cio_start_handle_notoper(sch, lpm);
	शेष:
		वापस ccode;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(cio_start_key);

पूर्णांक
cio_start (काष्ठा subchannel *sch, काष्ठा ccw1 *cpa, __u8 lpm)
अणु
	वापस cio_start_key(sch, cpa, lpm, PAGE_DEFAULT_KEY);
पूर्ण
EXPORT_SYMBOL_GPL(cio_start);

/*
 * resume suspended I/O operation
 */
पूर्णांक
cio_resume (काष्ठा subchannel *sch)
अणु
	पूर्णांक ccode;

	CIO_TRACE_EVENT(4, "resIO");
	CIO_TRACE_EVENT(4, dev_name(&sch->dev));

	ccode = rsch (sch->schid);

	CIO_HEX_EVENT(4, &ccode, माप(ccode));

	चयन (ccode) अणु
	हाल 0:
		sch->schib.scsw.cmd.actl |= SCSW_ACTL_RESUME_PEND;
		वापस 0;
	हाल 1:
		वापस -EBUSY;
	हाल 2:
		वापस -EINVAL;
	शेष:
		/*
		 * useless to रुको क्रम request completion
		 *  as device is no दीर्घer operational !
		 */
		वापस -ENODEV;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(cio_resume);

/*
 * halt I/O operation
 */
पूर्णांक
cio_halt(काष्ठा subchannel *sch)
अणु
	पूर्णांक ccode;

	अगर (!sch)
		वापस -ENODEV;

	CIO_TRACE_EVENT(2, "haltIO");
	CIO_TRACE_EVENT(2, dev_name(&sch->dev));

	/*
	 * Issue "Halt subchannel" and process condition code
	 */
	ccode = hsch (sch->schid);

	CIO_HEX_EVENT(2, &ccode, माप(ccode));

	चयन (ccode) अणु
	हाल 0:
		sch->schib.scsw.cmd.actl |= SCSW_ACTL_HALT_PEND;
		वापस 0;
	हाल 1:		/* status pending */
	हाल 2:		/* busy */
		वापस -EBUSY;
	शेष:		/* device not operational */
		वापस -ENODEV;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(cio_halt);

/*
 * Clear I/O operation
 */
पूर्णांक
cio_clear(काष्ठा subchannel *sch)
अणु
	पूर्णांक ccode;

	अगर (!sch)
		वापस -ENODEV;

	CIO_TRACE_EVENT(2, "clearIO");
	CIO_TRACE_EVENT(2, dev_name(&sch->dev));

	/*
	 * Issue "Clear subchannel" and process condition code
	 */
	ccode = csch (sch->schid);

	CIO_HEX_EVENT(2, &ccode, माप(ccode));

	चयन (ccode) अणु
	हाल 0:
		sch->schib.scsw.cmd.actl |= SCSW_ACTL_CLEAR_PEND;
		वापस 0;
	शेष:		/* device not operational */
		वापस -ENODEV;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(cio_clear);

/*
 * Function: cio_cancel
 * Issues a "Cancel Subchannel" on the specअगरied subchannel
 * Note: We करोn't need any fancy पूर्णांकparms and flags here
 *	 since xsch is executed synchronously.
 * Only क्रम common I/O पूर्णांकernal use as क्रम now.
 */
पूर्णांक
cio_cancel (काष्ठा subchannel *sch)
अणु
	पूर्णांक ccode;

	अगर (!sch)
		वापस -ENODEV;

	CIO_TRACE_EVENT(2, "cancelIO");
	CIO_TRACE_EVENT(2, dev_name(&sch->dev));

	ccode = xsch (sch->schid);

	CIO_HEX_EVENT(2, &ccode, माप(ccode));

	चयन (ccode) अणु
	हाल 0:		/* success */
		/* Update inक्रमmation in scsw. */
		अगर (cio_update_schib(sch))
			वापस -ENODEV;
		वापस 0;
	हाल 1:		/* status pending */
		वापस -EBUSY;
	हाल 2:		/* not applicable */
		वापस -EINVAL;
	शेष:	/* not oper */
		वापस -ENODEV;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(cio_cancel);

/**
 * cio_cancel_halt_clear - Cancel running I/O by perक्रमming cancel, halt
 * and clear ordinally अगर subchannel is valid.
 * @sch: subchannel on which to perक्रमm the cancel_halt_clear operation
 * @iretry: the number of the बार reमुख्यed to retry the next operation
 *
 * This should be called repeatedly since halt/clear are asynchronous
 * operations. We करो one try with cio_cancel, three tries with cio_halt,
 * 255 tries with cio_clear. The caller should initialize @iretry with
 * the value 255 क्रम its first call to this, and keep using the same
 * @iretry in the subsequent calls until it माला_लो a non -EBUSY वापस.
 *
 * Returns 0 अगर device now idle, -ENODEV क्रम device not operational,
 * -EBUSY अगर an पूर्णांकerrupt is expected (either from halt/clear or from a
 * status pending), and -EIO अगर out of retries.
 */
पूर्णांक cio_cancel_halt_clear(काष्ठा subchannel *sch, पूर्णांक *iretry)
अणु
	पूर्णांक ret;

	अगर (cio_update_schib(sch))
		वापस -ENODEV;
	अगर (!sch->schib.pmcw.ena)
		/* Not operational -> करोne. */
		वापस 0;
	/* Stage 1: cancel io. */
	अगर (!(scsw_actl(&sch->schib.scsw) & SCSW_ACTL_HALT_PEND) &&
	    !(scsw_actl(&sch->schib.scsw) & SCSW_ACTL_CLEAR_PEND)) अणु
		अगर (!scsw_is_पंचांग(&sch->schib.scsw)) अणु
			ret = cio_cancel(sch);
			अगर (ret != -EINVAL)
				वापस ret;
		पूर्ण
		/*
		 * Cancel io unsuccessful or not applicable (transport mode).
		 * Continue with asynchronous inकाष्ठाions.
		 */
		*iretry = 3;	/* 3 halt retries. */
	पूर्ण
	/* Stage 2: halt io. */
	अगर (!(scsw_actl(&sch->schib.scsw) & SCSW_ACTL_CLEAR_PEND)) अणु
		अगर (*iretry) अणु
			*iretry -= 1;
			ret = cio_halt(sch);
			अगर (ret != -EBUSY)
				वापस (ret == 0) ? -EBUSY : ret;
		पूर्ण
		/* Halt io unsuccessful. */
		*iretry = 255;	/* 255 clear retries. */
	पूर्ण
	/* Stage 3: clear io. */
	अगर (*iretry) अणु
		*iretry -= 1;
		ret = cio_clear(sch);
		वापस (ret == 0) ? -EBUSY : ret;
	पूर्ण
	/* Function was unsuccessful */
	वापस -EIO;
पूर्ण
EXPORT_SYMBOL_GPL(cio_cancel_halt_clear);

अटल व्योम cio_apply_config(काष्ठा subchannel *sch, काष्ठा schib *schib)
अणु
	schib->pmcw.पूर्णांकparm = sch->config.पूर्णांकparm;
	schib->pmcw.mbi = sch->config.mbi;
	schib->pmcw.isc = sch->config.isc;
	schib->pmcw.ena = sch->config.ena;
	schib->pmcw.mme = sch->config.mme;
	schib->pmcw.mp = sch->config.mp;
	schib->pmcw.csense = sch->config.csense;
	schib->pmcw.mbfc = sch->config.mbfc;
	अगर (sch->config.mbfc)
		schib->mba = sch->config.mba;
पूर्ण

अटल पूर्णांक cio_check_config(काष्ठा subchannel *sch, काष्ठा schib *schib)
अणु
	वापस (schib->pmcw.पूर्णांकparm == sch->config.पूर्णांकparm) &&
		(schib->pmcw.mbi == sch->config.mbi) &&
		(schib->pmcw.isc == sch->config.isc) &&
		(schib->pmcw.ena == sch->config.ena) &&
		(schib->pmcw.mme == sch->config.mme) &&
		(schib->pmcw.mp == sch->config.mp) &&
		(schib->pmcw.csense == sch->config.csense) &&
		(schib->pmcw.mbfc == sch->config.mbfc) &&
		(!sch->config.mbfc || (schib->mba == sch->config.mba));
पूर्ण

/*
 * cio_commit_config - apply configuration to the subchannel
 */
पूर्णांक cio_commit_config(काष्ठा subchannel *sch)
अणु
	पूर्णांक ccode, retry, ret = 0;
	काष्ठा schib schib;
	काष्ठा irb irb;

	अगर (stsch(sch->schid, &schib) || !css_sch_is_valid(&schib))
		वापस -ENODEV;

	क्रम (retry = 0; retry < 5; retry++) अणु
		/* copy desired changes to local schib */
		cio_apply_config(sch, &schib);
		ccode = msch(sch->schid, &schib);
		अगर (ccode < 0) /* -EIO अगर msch माला_लो a program check. */
			वापस ccode;
		चयन (ccode) अणु
		हाल 0: /* successful */
			अगर (stsch(sch->schid, &schib) ||
			    !css_sch_is_valid(&schib))
				वापस -ENODEV;
			अगर (cio_check_config(sch, &schib)) अणु
				/* commit changes from local schib */
				स_नकल(&sch->schib, &schib, माप(schib));
				वापस 0;
			पूर्ण
			ret = -EAGAIN;
			अवरोध;
		हाल 1: /* status pending */
			ret = -EBUSY;
			अगर (tsch(sch->schid, &irb))
				वापस ret;
			अवरोध;
		हाल 2: /* busy */
			udelay(100); /* allow क्रम recovery */
			ret = -EBUSY;
			अवरोध;
		हाल 3: /* not operational */
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(cio_commit_config);

/**
 * cio_update_schib - Perक्रमm stsch and update schib अगर subchannel is valid.
 * @sch: subchannel on which to perक्रमm stsch
 * Return zero on success, -ENODEV otherwise.
 */
पूर्णांक cio_update_schib(काष्ठा subchannel *sch)
अणु
	काष्ठा schib schib;

	अगर (stsch(sch->schid, &schib) || !css_sch_is_valid(&schib))
		वापस -ENODEV;

	स_नकल(&sch->schib, &schib, माप(schib));
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cio_update_schib);

/**
 * cio_enable_subchannel - enable a subchannel.
 * @sch: subchannel to be enabled
 * @पूर्णांकparm: पूर्णांकerruption parameter to set
 */
पूर्णांक cio_enable_subchannel(काष्ठा subchannel *sch, u32 पूर्णांकparm)
अणु
	पूर्णांक ret;

	CIO_TRACE_EVENT(2, "ensch");
	CIO_TRACE_EVENT(2, dev_name(&sch->dev));

	अगर (sch_is_pseuकरो_sch(sch))
		वापस -EINVAL;
	अगर (cio_update_schib(sch))
		वापस -ENODEV;

	sch->config.ena = 1;
	sch->config.isc = sch->isc;
	sch->config.पूर्णांकparm = पूर्णांकparm;

	ret = cio_commit_config(sch);
	अगर (ret == -EIO) अणु
		/*
		 * Got a program check in msch. Try without
		 * the concurrent sense bit the next समय.
		 */
		sch->config.csense = 0;
		ret = cio_commit_config(sch);
	पूर्ण
	CIO_HEX_EVENT(2, &ret, माप(ret));
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(cio_enable_subchannel);

/**
 * cio_disable_subchannel - disable a subchannel.
 * @sch: subchannel to disable
 */
पूर्णांक cio_disable_subchannel(काष्ठा subchannel *sch)
अणु
	पूर्णांक ret;

	CIO_TRACE_EVENT(2, "dissch");
	CIO_TRACE_EVENT(2, dev_name(&sch->dev));

	अगर (sch_is_pseuकरो_sch(sch))
		वापस 0;
	अगर (cio_update_schib(sch))
		वापस -ENODEV;

	sch->config.ena = 0;
	ret = cio_commit_config(sch);

	CIO_HEX_EVENT(2, &ret, माप(ret));
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(cio_disable_subchannel);

/*
 * करो_cio_पूर्णांकerrupt() handles all normal I/O device IRQ's
 */
अटल irqवापस_t करो_cio_पूर्णांकerrupt(पूर्णांक irq, व्योम *dummy)
अणु
	काष्ठा tpi_info *tpi_info;
	काष्ठा subchannel *sch;
	काष्ठा irb *irb;

	set_cpu_flag(CIF_NOHZ_DELAY);
	tpi_info = (काष्ठा tpi_info *) &get_irq_regs()->पूर्णांक_code;
	trace_s390_cio_पूर्णांकerrupt(tpi_info);
	irb = this_cpu_ptr(&cio_irb);
	sch = (काष्ठा subchannel *)(अचिन्हित दीर्घ) tpi_info->पूर्णांकparm;
	अगर (!sch) अणु
		/* Clear pending पूर्णांकerrupt condition. */
		inc_irq_stat(IRQIO_CIO);
		tsch(tpi_info->schid, irb);
		वापस IRQ_HANDLED;
	पूर्ण
	spin_lock(sch->lock);
	/* Store पूर्णांकerrupt response block to lowcore. */
	अगर (tsch(tpi_info->schid, irb) == 0) अणु
		/* Keep subchannel inक्रमmation word up to date. */
		स_नकल (&sch->schib.scsw, &irb->scsw, माप (irb->scsw));
		/* Call पूर्णांकerrupt handler अगर there is one. */
		अगर (sch->driver && sch->driver->irq)
			sch->driver->irq(sch);
		अन्यथा
			inc_irq_stat(IRQIO_CIO);
	पूर्ण अन्यथा
		inc_irq_stat(IRQIO_CIO);
	spin_unlock(sch->lock);

	वापस IRQ_HANDLED;
पूर्ण

व्योम __init init_cio_पूर्णांकerrupts(व्योम)
अणु
	irq_set_chip_and_handler(IO_INTERRUPT,
				 &dummy_irq_chip, handle_percpu_irq);
	अगर (request_irq(IO_INTERRUPT, करो_cio_पूर्णांकerrupt, 0, "I/O", शून्य))
		panic("Failed to register I/O interrupt\n");
पूर्ण

#अगर_घोषित CONFIG_CCW_CONSOLE
अटल काष्ठा subchannel *console_sch;
अटल काष्ठा lock_class_key console_sch_key;

/*
 * Use cio_tsch to update the subchannel status and call the पूर्णांकerrupt handler
 * अगर status had been pending. Called with the subchannel's lock held.
 */
व्योम cio_tsch(काष्ठा subchannel *sch)
अणु
	काष्ठा irb *irb;
	पूर्णांक irq_context;

	irb = this_cpu_ptr(&cio_irb);
	/* Store पूर्णांकerrupt response block to lowcore. */
	अगर (tsch(sch->schid, irb) != 0)
		/* Not status pending or not operational. */
		वापस;
	स_नकल(&sch->schib.scsw, &irb->scsw, माप(जोड़ scsw));
	/* Call पूर्णांकerrupt handler with updated status. */
	irq_context = in_पूर्णांकerrupt();
	अगर (!irq_context) अणु
		local_bh_disable();
		irq_enter();
	पूर्ण
	kstat_incr_irq_this_cpu(IO_INTERRUPT);
	अगर (sch->driver && sch->driver->irq)
		sch->driver->irq(sch);
	अन्यथा
		inc_irq_stat(IRQIO_CIO);
	अगर (!irq_context) अणु
		irq_निकास();
		_local_bh_enable();
	पूर्ण
पूर्ण

अटल पूर्णांक cio_test_क्रम_console(काष्ठा subchannel_id schid, व्योम *data)
अणु
	काष्ठा schib schib;

	अगर (stsch(schid, &schib) != 0)
		वापस -ENXIO;
	अगर ((schib.pmcw.st == SUBCHANNEL_TYPE_IO) && schib.pmcw.dnv &&
	    (schib.pmcw.dev == console_devno)) अणु
		console_irq = schid.sch_no;
		वापस 1; /* found */
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cio_get_console_sch_no(व्योम)
अणु
	काष्ठा subchannel_id schid;
	काष्ठा schib schib;

	init_subchannel_id(&schid);
	अगर (console_irq != -1) अणु
		/* VM provided us with the irq number of the console. */
		schid.sch_no = console_irq;
		अगर (stsch(schid, &schib) != 0 ||
		    (schib.pmcw.st != SUBCHANNEL_TYPE_IO) || !schib.pmcw.dnv)
			वापस -1;
		console_devno = schib.pmcw.dev;
	पूर्ण अन्यथा अगर (console_devno != -1) अणु
		/* At least the console device number is known. */
		क्रम_each_subchannel(cio_test_क्रम_console, शून्य);
	पूर्ण
	वापस console_irq;
पूर्ण

काष्ठा subchannel *cio_probe_console(व्योम)
अणु
	काष्ठा subchannel_id schid;
	काष्ठा subchannel *sch;
	काष्ठा schib schib;
	पूर्णांक sch_no, ret;

	sch_no = cio_get_console_sch_no();
	अगर (sch_no == -1) अणु
		pr_warn("No CCW console was found\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण
	init_subchannel_id(&schid);
	schid.sch_no = sch_no;
	ret = stsch(schid, &schib);
	अगर (ret)
		वापस ERR_PTR(-ENODEV);

	sch = css_alloc_subchannel(schid, &schib);
	अगर (IS_ERR(sch))
		वापस sch;

	lockdep_set_class(sch->lock, &console_sch_key);
	isc_रेजिस्टर(CONSOLE_ISC);
	sch->config.isc = CONSOLE_ISC;
	sch->config.पूर्णांकparm = (u32)(addr_t)sch;
	ret = cio_commit_config(sch);
	अगर (ret) अणु
		isc_unरेजिस्टर(CONSOLE_ISC);
		put_device(&sch->dev);
		वापस ERR_PTR(ret);
	पूर्ण
	console_sch = sch;
	वापस sch;
पूर्ण

पूर्णांक cio_is_console(काष्ठा subchannel_id schid)
अणु
	अगर (!console_sch)
		वापस 0;
	वापस schid_equal(&schid, &console_sch->schid);
पूर्ण

व्योम cio_रेजिस्टर_early_subchannels(व्योम)
अणु
	पूर्णांक ret;

	अगर (!console_sch)
		वापस;

	ret = css_रेजिस्टर_subchannel(console_sch);
	अगर (ret)
		put_device(&console_sch->dev);
पूर्ण
#पूर्ण_अगर /* CONFIG_CCW_CONSOLE */

/**
 * cio_पंचांग_start_key - perक्रमm start function
 * @sch: subchannel on which to perक्रमm the start function
 * @tcw: transport-command word to be started
 * @lpm: mask of paths to use
 * @key: storage key to use क्रम storage access
 *
 * Start the tcw on the given subchannel. Return zero on success, non-zero
 * otherwise.
 */
पूर्णांक cio_पंचांग_start_key(काष्ठा subchannel *sch, काष्ठा tcw *tcw, u8 lpm, u8 key)
अणु
	पूर्णांक cc;
	जोड़ orb *orb = &to_io_निजी(sch)->orb;

	स_रखो(orb, 0, माप(जोड़ orb));
	orb->पंचांग.पूर्णांकparm = (u32) (addr_t) sch;
	orb->पंचांग.key = key >> 4;
	orb->पंचांग.b = 1;
	orb->पंचांग.lpm = lpm ? lpm : sch->lpm;
	orb->पंचांग.tcw = (u32) (addr_t) tcw;
	cc = ssch(sch->schid, orb);
	चयन (cc) अणु
	हाल 0:
		वापस 0;
	हाल 1:
	हाल 2:
		वापस -EBUSY;
	शेष:
		वापस cio_start_handle_notoper(sch, lpm);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(cio_पंचांग_start_key);

/**
 * cio_पंचांग_पूर्णांकrg - perक्रमm पूर्णांकerrogate function
 * @sch: subchannel on which to perक्रमm the पूर्णांकerrogate function
 *
 * If the specअगरied subchannel is running in transport-mode, perक्रमm the
 * पूर्णांकerrogate function. Return zero on success, non-zero otherwie.
 */
पूर्णांक cio_पंचांग_पूर्णांकrg(काष्ठा subchannel *sch)
अणु
	पूर्णांक cc;

	अगर (!to_io_निजी(sch)->orb.पंचांग.b)
		वापस -EINVAL;
	cc = xsch(sch->schid);
	चयन (cc) अणु
	हाल 0:
	हाल 2:
		वापस 0;
	हाल 1:
		वापस -EBUSY;
	शेष:
		वापस -ENODEV;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(cio_पंचांग_पूर्णांकrg);
