<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  ec.c - ACPI Embedded Controller Driver (v3)
 *
 *  Copyright (C) 2001-2015 Intel Corporation
 *    Author: 2014, 2015 Lv Zheng <lv.zheng@पूर्णांकel.com>
 *            2006, 2007 Alexey Starikovskiy <alexey.y.starikovskiy@पूर्णांकel.com>
 *            2006       Denis Sadykov <denis.m.sadykov@पूर्णांकel.com>
 *            2004       Luming Yu <luming.yu@पूर्णांकel.com>
 *            2001, 2002 Andy Grover <andrew.grover@पूर्णांकel.com>
 *            2001, 2002 Paul Diefenbaugh <paul.s.diefenbaugh@पूर्णांकel.com>
 *  Copyright (C) 2008      Alexey Starikovskiy <astarikovskiy@suse.de>
 */

/* Uncomment next line to get verbose prपूर्णांकout */
/* #घोषणा DEBUG */
#घोषणा pr_fmt(fmt) "ACPI: EC: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/suspend.h>
#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>
#समावेश <यंत्र/पन.स>

#समावेश "internal.h"

#घोषणा ACPI_EC_CLASS			"embedded_controller"
#घोषणा ACPI_EC_DEVICE_NAME		"Embedded Controller"

/* EC status रेजिस्टर */
#घोषणा ACPI_EC_FLAG_OBF	0x01	/* Output buffer full */
#घोषणा ACPI_EC_FLAG_IBF	0x02	/* Input buffer full */
#घोषणा ACPI_EC_FLAG_CMD	0x08	/* Input buffer contains a command */
#घोषणा ACPI_EC_FLAG_BURST	0x10	/* burst mode */
#घोषणा ACPI_EC_FLAG_SCI	0x20	/* EC-SCI occurred */

/*
 * The SCI_EVT clearing timing is not defined by the ACPI specअगरication.
 * This leads to lots of practical timing issues क्रम the host EC driver.
 * The following variations are defined (from the target EC firmware's
 * perspective):
 * STATUS: After indicating SCI_EVT edge triggered IRQ to the host, the
 *         target can clear SCI_EVT at any समय so दीर्घ as the host can see
 *         the indication by पढ़ोing the status रेजिस्टर (EC_SC). So the
 *         host should re-check SCI_EVT after the first समय the SCI_EVT
 *         indication is seen, which is the same समय the query request
 *         (QR_EC) is written to the command रेजिस्टर (EC_CMD). SCI_EVT set
 *         at any later समय could indicate another event. Normally such
 *         kind of EC firmware has implemented an event queue and will
 *         वापस 0x00 to indicate "no outstanding event".
 * QUERY: After seeing the query request (QR_EC) written to the command
 *        रेजिस्टर (EC_CMD) by the host and having prepared the responding
 *        event value in the data रेजिस्टर (EC_DATA), the target can safely
 *        clear SCI_EVT because the target can confirm that the current
 *        event is being handled by the host. The host then should check
 *        SCI_EVT right after पढ़ोing the event response from the data
 *        रेजिस्टर (EC_DATA).
 * EVENT: After seeing the event response पढ़ो from the data रेजिस्टर
 *        (EC_DATA) by the host, the target can clear SCI_EVT. As the
 *        target requires समय to notice the change in the data रेजिस्टर
 *        (EC_DATA), the host may be required to रुको additional guarding
 *        समय beक्रमe checking the SCI_EVT again. Such guarding may not be
 *        necessary अगर the host is notअगरied via another IRQ.
 */
#घोषणा ACPI_EC_EVT_TIMING_STATUS	0x00
#घोषणा ACPI_EC_EVT_TIMING_QUERY	0x01
#घोषणा ACPI_EC_EVT_TIMING_EVENT	0x02

/* EC commands */
क्रमागत ec_command अणु
	ACPI_EC_COMMAND_READ = 0x80,
	ACPI_EC_COMMAND_WRITE = 0x81,
	ACPI_EC_BURST_ENABLE = 0x82,
	ACPI_EC_BURST_DISABLE = 0x83,
	ACPI_EC_COMMAND_QUERY = 0x84,
पूर्ण;

#घोषणा ACPI_EC_DELAY		500	/* Wait 500ms max. during EC ops */
#घोषणा ACPI_EC_UDELAY_GLK	1000	/* Wait 1ms max. to get global lock */
#घोषणा ACPI_EC_UDELAY_POLL	550	/* Wait 1ms क्रम EC transaction polling */
#घोषणा ACPI_EC_CLEAR_MAX	100	/* Maximum number of events to query
					 * when trying to clear the EC */
#घोषणा ACPI_EC_MAX_QUERIES	16	/* Maximum number of parallel queries */

क्रमागत अणु
	EC_FLAGS_QUERY_ENABLED,		/* Query is enabled */
	EC_FLAGS_QUERY_PENDING,		/* Query is pending */
	EC_FLAGS_QUERY_GUARDING,	/* Guard क्रम SCI_EVT check */
	EC_FLAGS_EVENT_HANDLER_INSTALLED,	/* Event handler installed */
	EC_FLAGS_EC_HANDLER_INSTALLED,	/* OpReg handler installed */
	EC_FLAGS_QUERY_METHODS_INSTALLED, /* _Qxx handlers installed */
	EC_FLAGS_STARTED,		/* Driver is started */
	EC_FLAGS_STOPPED,		/* Driver is stopped */
	EC_FLAGS_EVENTS_MASKED,		/* Events masked */
पूर्ण;

#घोषणा ACPI_EC_COMMAND_POLL		0x01 /* Available क्रम command byte */
#घोषणा ACPI_EC_COMMAND_COMPLETE	0x02 /* Completed last byte */

/* ec.c is compiled in acpi namespace so this shows up as acpi.ec_delay param */
अटल अचिन्हित पूर्णांक ec_delay __पढ़ो_mostly = ACPI_EC_DELAY;
module_param(ec_delay, uपूर्णांक, 0644);
MODULE_PARM_DESC(ec_delay, "Timeout(ms) waited until an EC command completes");

अटल अचिन्हित पूर्णांक ec_max_queries __पढ़ो_mostly = ACPI_EC_MAX_QUERIES;
module_param(ec_max_queries, uपूर्णांक, 0644);
MODULE_PARM_DESC(ec_max_queries, "Maximum parallel _Qxx evaluations");

अटल bool ec_busy_polling __पढ़ो_mostly;
module_param(ec_busy_polling, bool, 0644);
MODULE_PARM_DESC(ec_busy_polling, "Use busy polling to advance EC transaction");

अटल अचिन्हित पूर्णांक ec_polling_guard __पढ़ो_mostly = ACPI_EC_UDELAY_POLL;
module_param(ec_polling_guard, uपूर्णांक, 0644);
MODULE_PARM_DESC(ec_polling_guard, "Guard time(us) between EC accesses in polling modes");

अटल अचिन्हित पूर्णांक ec_event_clearing __पढ़ो_mostly = ACPI_EC_EVT_TIMING_QUERY;

/*
 * If the number of false पूर्णांकerrupts per one transaction exceeds
 * this threshold, will think there is a GPE storm happened and
 * will disable the GPE क्रम normal transaction.
 */
अटल अचिन्हित पूर्णांक ec_storm_threshold  __पढ़ो_mostly = 8;
module_param(ec_storm_threshold, uपूर्णांक, 0644);
MODULE_PARM_DESC(ec_storm_threshold, "Maxim false GPE numbers not considered as GPE storm");

अटल bool ec_मुक्तze_events __पढ़ो_mostly = false;
module_param(ec_मुक्तze_events, bool, 0644);
MODULE_PARM_DESC(ec_मुक्तze_events, "Disabling event handling during suspend/resume");

अटल bool ec_no_wakeup __पढ़ो_mostly;
module_param(ec_no_wakeup, bool, 0644);
MODULE_PARM_DESC(ec_no_wakeup, "Do not wake up from suspend-to-idle");

काष्ठा acpi_ec_query_handler अणु
	काष्ठा list_head node;
	acpi_ec_query_func func;
	acpi_handle handle;
	व्योम *data;
	u8 query_bit;
	काष्ठा kref kref;
पूर्ण;

काष्ठा transaction अणु
	स्थिर u8 *wdata;
	u8 *rdata;
	अचिन्हित लघु irq_count;
	u8 command;
	u8 wi;
	u8 ri;
	u8 wlen;
	u8 rlen;
	u8 flags;
पूर्ण;

काष्ठा acpi_ec_query अणु
	काष्ठा transaction transaction;
	काष्ठा work_काष्ठा work;
	काष्ठा acpi_ec_query_handler *handler;
पूर्ण;

अटल पूर्णांक acpi_ec_query(काष्ठा acpi_ec *ec, u8 *data);
अटल व्योम advance_transaction(काष्ठा acpi_ec *ec, bool पूर्णांकerrupt);
अटल व्योम acpi_ec_event_handler(काष्ठा work_काष्ठा *work);
अटल व्योम acpi_ec_event_processor(काष्ठा work_काष्ठा *work);

काष्ठा acpi_ec *first_ec;
EXPORT_SYMBOL(first_ec);

अटल काष्ठा acpi_ec *boot_ec;
अटल bool boot_ec_is_ecdt = false;
अटल काष्ठा workqueue_काष्ठा *ec_wq;
अटल काष्ठा workqueue_काष्ठा *ec_query_wq;

अटल पूर्णांक EC_FLAGS_CORRECT_ECDT; /* Needs ECDT port address correction */
अटल पूर्णांक EC_FLAGS_IGNORE_DSDT_GPE; /* Needs ECDT GPE as correction setting */
अटल पूर्णांक EC_FLAGS_CLEAR_ON_RESUME; /* Needs acpi_ec_clear() on boot/resume */

/* --------------------------------------------------------------------------
 *                           Logging/Debugging
 * -------------------------------------------------------------------------- */

/*
 * Splitters used by the developers to track the boundary of the EC
 * handling processes.
 */
#अगर_घोषित DEBUG
#घोषणा EC_DBG_SEP	" "
#घोषणा EC_DBG_DRV	"+++++"
#घोषणा EC_DBG_STM	"====="
#घोषणा EC_DBG_REQ	"*****"
#घोषणा EC_DBG_EVT	"#####"
#अन्यथा
#घोषणा EC_DBG_SEP	""
#घोषणा EC_DBG_DRV
#घोषणा EC_DBG_STM
#घोषणा EC_DBG_REQ
#घोषणा EC_DBG_EVT
#पूर्ण_अगर

#घोषणा ec_log_raw(fmt, ...) \
	pr_info(fmt "\n", ##__VA_ARGS__)
#घोषणा ec_dbg_raw(fmt, ...) \
	pr_debug(fmt "\n", ##__VA_ARGS__)
#घोषणा ec_log(filter, fmt, ...) \
	ec_log_raw(filter EC_DBG_SEP fmt EC_DBG_SEP filter, ##__VA_ARGS__)
#घोषणा ec_dbg(filter, fmt, ...) \
	ec_dbg_raw(filter EC_DBG_SEP fmt EC_DBG_SEP filter, ##__VA_ARGS__)

#घोषणा ec_log_drv(fmt, ...) \
	ec_log(EC_DBG_DRV, fmt, ##__VA_ARGS__)
#घोषणा ec_dbg_drv(fmt, ...) \
	ec_dbg(EC_DBG_DRV, fmt, ##__VA_ARGS__)
#घोषणा ec_dbg_sपंचांग(fmt, ...) \
	ec_dbg(EC_DBG_STM, fmt, ##__VA_ARGS__)
#घोषणा ec_dbg_req(fmt, ...) \
	ec_dbg(EC_DBG_REQ, fmt, ##__VA_ARGS__)
#घोषणा ec_dbg_evt(fmt, ...) \
	ec_dbg(EC_DBG_EVT, fmt, ##__VA_ARGS__)
#घोषणा ec_dbg_ref(ec, fmt, ...) \
	ec_dbg_raw("%lu: " fmt, ec->reference_count, ## __VA_ARGS__)

/* --------------------------------------------------------------------------
 *                           Device Flags
 * -------------------------------------------------------------------------- */

अटल bool acpi_ec_started(काष्ठा acpi_ec *ec)
अणु
	वापस test_bit(EC_FLAGS_STARTED, &ec->flags) &&
	       !test_bit(EC_FLAGS_STOPPED, &ec->flags);
पूर्ण

अटल bool acpi_ec_event_enabled(काष्ठा acpi_ec *ec)
अणु
	/*
	 * There is an OSPM early stage logic. During the early stages
	 * (boot/resume), OSPMs shouldn't enable the event handling, only
	 * the EC transactions are allowed to be perक्रमmed.
	 */
	अगर (!test_bit(EC_FLAGS_QUERY_ENABLED, &ec->flags))
		वापस false;
	/*
	 * However, disabling the event handling is experimental क्रम late
	 * stage (suspend), and is controlled by the boot parameter of
	 * "ec_freeze_events":
	 * 1. true:  The EC event handling is disabled beक्रमe entering
	 *           the noirq stage.
	 * 2. false: The EC event handling is स्वतःmatically disabled as
	 *           soon as the EC driver is stopped.
	 */
	अगर (ec_मुक्तze_events)
		वापस acpi_ec_started(ec);
	अन्यथा
		वापस test_bit(EC_FLAGS_STARTED, &ec->flags);
पूर्ण

अटल bool acpi_ec_flushed(काष्ठा acpi_ec *ec)
अणु
	वापस ec->reference_count == 1;
पूर्ण

/* --------------------------------------------------------------------------
 *                           EC Registers
 * -------------------------------------------------------------------------- */

अटल अंतरभूत u8 acpi_ec_पढ़ो_status(काष्ठा acpi_ec *ec)
अणु
	u8 x = inb(ec->command_addr);

	ec_dbg_raw("EC_SC(R) = 0x%2.2x "
		   "SCI_EVT=%d BURST=%d CMD=%d IBF=%d OBF=%d",
		   x,
		   !!(x & ACPI_EC_FLAG_SCI),
		   !!(x & ACPI_EC_FLAG_BURST),
		   !!(x & ACPI_EC_FLAG_CMD),
		   !!(x & ACPI_EC_FLAG_IBF),
		   !!(x & ACPI_EC_FLAG_OBF));
	वापस x;
पूर्ण

अटल अंतरभूत u8 acpi_ec_पढ़ो_data(काष्ठा acpi_ec *ec)
अणु
	u8 x = inb(ec->data_addr);

	ec->बारtamp = jअगरfies;
	ec_dbg_raw("EC_DATA(R) = 0x%2.2x", x);
	वापस x;
पूर्ण

अटल अंतरभूत व्योम acpi_ec_ग_लिखो_cmd(काष्ठा acpi_ec *ec, u8 command)
अणु
	ec_dbg_raw("EC_SC(W) = 0x%2.2x", command);
	outb(command, ec->command_addr);
	ec->बारtamp = jअगरfies;
पूर्ण

अटल अंतरभूत व्योम acpi_ec_ग_लिखो_data(काष्ठा acpi_ec *ec, u8 data)
अणु
	ec_dbg_raw("EC_DATA(W) = 0x%2.2x", data);
	outb(data, ec->data_addr);
	ec->बारtamp = jअगरfies;
पूर्ण

#अगर defined(DEBUG) || defined(CONFIG_DYNAMIC_DEBUG)
अटल स्थिर अक्षर *acpi_ec_cmd_string(u8 cmd)
अणु
	चयन (cmd) अणु
	हाल 0x80:
		वापस "RD_EC";
	हाल 0x81:
		वापस "WR_EC";
	हाल 0x82:
		वापस "BE_EC";
	हाल 0x83:
		वापस "BD_EC";
	हाल 0x84:
		वापस "QR_EC";
	पूर्ण
	वापस "UNKNOWN";
पूर्ण
#अन्यथा
#घोषणा acpi_ec_cmd_string(cmd)		"UNDEF"
#पूर्ण_अगर

/* --------------------------------------------------------------------------
 *                           GPE Registers
 * -------------------------------------------------------------------------- */

अटल अंतरभूत bool acpi_ec_gpe_status_set(काष्ठा acpi_ec *ec)
अणु
	acpi_event_status gpe_status = 0;

	(व्योम)acpi_get_gpe_status(शून्य, ec->gpe, &gpe_status);
	वापस !!(gpe_status & ACPI_EVENT_FLAG_STATUS_SET);
पूर्ण

अटल अंतरभूत व्योम acpi_ec_enable_gpe(काष्ठा acpi_ec *ec, bool खोलो)
अणु
	अगर (खोलो)
		acpi_enable_gpe(शून्य, ec->gpe);
	अन्यथा अणु
		BUG_ON(ec->reference_count < 1);
		acpi_set_gpe(शून्य, ec->gpe, ACPI_GPE_ENABLE);
	पूर्ण
	अगर (acpi_ec_gpe_status_set(ec)) अणु
		/*
		 * On some platक्रमms, EN=1 ग_लिखोs cannot trigger GPE. So
		 * software need to manually trigger a pseuकरो GPE event on
		 * EN=1 ग_लिखोs.
		 */
		ec_dbg_raw("Polling quirk");
		advance_transaction(ec, false);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम acpi_ec_disable_gpe(काष्ठा acpi_ec *ec, bool बंद)
अणु
	अगर (बंद)
		acpi_disable_gpe(शून्य, ec->gpe);
	अन्यथा अणु
		BUG_ON(ec->reference_count < 1);
		acpi_set_gpe(शून्य, ec->gpe, ACPI_GPE_DISABLE);
	पूर्ण
पूर्ण

/* --------------------------------------------------------------------------
 *                           Transaction Management
 * -------------------------------------------------------------------------- */

अटल व्योम acpi_ec_submit_request(काष्ठा acpi_ec *ec)
अणु
	ec->reference_count++;
	अगर (test_bit(EC_FLAGS_EVENT_HANDLER_INSTALLED, &ec->flags) &&
	    ec->gpe >= 0 && ec->reference_count == 1)
		acpi_ec_enable_gpe(ec, true);
पूर्ण

अटल व्योम acpi_ec_complete_request(काष्ठा acpi_ec *ec)
अणु
	bool flushed = false;

	ec->reference_count--;
	अगर (test_bit(EC_FLAGS_EVENT_HANDLER_INSTALLED, &ec->flags) &&
	    ec->gpe >= 0 && ec->reference_count == 0)
		acpi_ec_disable_gpe(ec, true);
	flushed = acpi_ec_flushed(ec);
	अगर (flushed)
		wake_up(&ec->रुको);
पूर्ण

अटल व्योम acpi_ec_mask_events(काष्ठा acpi_ec *ec)
अणु
	अगर (!test_bit(EC_FLAGS_EVENTS_MASKED, &ec->flags)) अणु
		अगर (ec->gpe >= 0)
			acpi_ec_disable_gpe(ec, false);
		अन्यथा
			disable_irq_nosync(ec->irq);

		ec_dbg_drv("Polling enabled");
		set_bit(EC_FLAGS_EVENTS_MASKED, &ec->flags);
	पूर्ण
पूर्ण

अटल व्योम acpi_ec_unmask_events(काष्ठा acpi_ec *ec)
अणु
	अगर (test_bit(EC_FLAGS_EVENTS_MASKED, &ec->flags)) अणु
		clear_bit(EC_FLAGS_EVENTS_MASKED, &ec->flags);
		अगर (ec->gpe >= 0)
			acpi_ec_enable_gpe(ec, false);
		अन्यथा
			enable_irq(ec->irq);

		ec_dbg_drv("Polling disabled");
	पूर्ण
पूर्ण

/*
 * acpi_ec_submit_flushable_request() - Increase the reference count unless
 *                                      the flush operation is not in
 *                                      progress
 * @ec: the EC device
 *
 * This function must be used beक्रमe taking a new action that should hold
 * the reference count.  If this function वापसs false, then the action
 * must be discarded or it will prevent the flush operation from being
 * completed.
 */
अटल bool acpi_ec_submit_flushable_request(काष्ठा acpi_ec *ec)
अणु
	अगर (!acpi_ec_started(ec))
		वापस false;
	acpi_ec_submit_request(ec);
	वापस true;
पूर्ण

अटल व्योम acpi_ec_submit_query(काष्ठा acpi_ec *ec)
अणु
	acpi_ec_mask_events(ec);
	अगर (!acpi_ec_event_enabled(ec))
		वापस;
	अगर (!test_and_set_bit(EC_FLAGS_QUERY_PENDING, &ec->flags)) अणु
		ec_dbg_evt("Command(%s) submitted/blocked",
			   acpi_ec_cmd_string(ACPI_EC_COMMAND_QUERY));
		ec->nr_pending_queries++;
		queue_work(ec_wq, &ec->work);
	पूर्ण
पूर्ण

अटल व्योम acpi_ec_complete_query(काष्ठा acpi_ec *ec)
अणु
	अगर (test_and_clear_bit(EC_FLAGS_QUERY_PENDING, &ec->flags))
		ec_dbg_evt("Command(%s) unblocked",
			   acpi_ec_cmd_string(ACPI_EC_COMMAND_QUERY));
	acpi_ec_unmask_events(ec);
पूर्ण

अटल अंतरभूत व्योम __acpi_ec_enable_event(काष्ठा acpi_ec *ec)
अणु
	अगर (!test_and_set_bit(EC_FLAGS_QUERY_ENABLED, &ec->flags))
		ec_log_drv("event unblocked");
	/*
	 * Unconditionally invoke this once after enabling the event
	 * handling mechanism to detect the pending events.
	 */
	advance_transaction(ec, false);
पूर्ण

अटल अंतरभूत व्योम __acpi_ec_disable_event(काष्ठा acpi_ec *ec)
अणु
	अगर (test_and_clear_bit(EC_FLAGS_QUERY_ENABLED, &ec->flags))
		ec_log_drv("event blocked");
पूर्ण

/*
 * Process _Q events that might have accumulated in the EC.
 * Run with locked ec mutex.
 */
अटल व्योम acpi_ec_clear(काष्ठा acpi_ec *ec)
अणु
	पूर्णांक i, status;
	u8 value = 0;

	क्रम (i = 0; i < ACPI_EC_CLEAR_MAX; i++) अणु
		status = acpi_ec_query(ec, &value);
		अगर (status || !value)
			अवरोध;
	पूर्ण
	अगर (unlikely(i == ACPI_EC_CLEAR_MAX))
		pr_warn("Warning: Maximum of %d stale EC events cleared\n", i);
	अन्यथा
		pr_info("%d stale EC events cleared\n", i);
पूर्ण

अटल व्योम acpi_ec_enable_event(काष्ठा acpi_ec *ec)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ec->lock, flags);
	अगर (acpi_ec_started(ec))
		__acpi_ec_enable_event(ec);
	spin_unlock_irqrestore(&ec->lock, flags);

	/* Drain additional events अगर hardware requires that */
	अगर (EC_FLAGS_CLEAR_ON_RESUME)
		acpi_ec_clear(ec);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल व्योम __acpi_ec_flush_work(व्योम)
अणु
	drain_workqueue(ec_wq); /* flush ec->work */
	flush_workqueue(ec_query_wq); /* flush queries */
पूर्ण

अटल व्योम acpi_ec_disable_event(काष्ठा acpi_ec *ec)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ec->lock, flags);
	__acpi_ec_disable_event(ec);
	spin_unlock_irqrestore(&ec->lock, flags);

	/*
	 * When ec_मुक्तze_events is true, we need to flush events in
	 * the proper position beक्रमe entering the noirq stage.
	 */
	__acpi_ec_flush_work();
पूर्ण

व्योम acpi_ec_flush_work(व्योम)
अणु
	/* Without ec_wq there is nothing to flush. */
	अगर (!ec_wq)
		वापस;

	__acpi_ec_flush_work();
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल bool acpi_ec_guard_event(काष्ठा acpi_ec *ec)
अणु
	bool guarded = true;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ec->lock, flags);
	/*
	 * If firmware SCI_EVT clearing timing is "event", we actually
	 * करोn't know when the SCI_EVT will be cleared by firmware after
	 * evaluating _Qxx, so we need to re-check SCI_EVT after रुकोing an
	 * acceptable period.
	 *
	 * The guarding period begins when EC_FLAGS_QUERY_PENDING is
	 * flagged, which means SCI_EVT check has just been perक्रमmed.
	 * But अगर the current transaction is ACPI_EC_COMMAND_QUERY, the
	 * guarding should have alपढ़ोy been perक्रमmed (via
	 * EC_FLAGS_QUERY_GUARDING) and should not be applied so that the
	 * ACPI_EC_COMMAND_QUERY transaction can be transitioned पूर्णांकo
	 * ACPI_EC_COMMAND_POLL state immediately.
	 */
	अगर (ec_event_clearing == ACPI_EC_EVT_TIMING_STATUS ||
	    ec_event_clearing == ACPI_EC_EVT_TIMING_QUERY ||
	    !test_bit(EC_FLAGS_QUERY_PENDING, &ec->flags) ||
	    (ec->curr && ec->curr->command == ACPI_EC_COMMAND_QUERY))
		guarded = false;
	spin_unlock_irqrestore(&ec->lock, flags);
	वापस guarded;
पूर्ण

अटल पूर्णांक ec_transaction_polled(काष्ठा acpi_ec *ec)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&ec->lock, flags);
	अगर (ec->curr && (ec->curr->flags & ACPI_EC_COMMAND_POLL))
		ret = 1;
	spin_unlock_irqrestore(&ec->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक ec_transaction_completed(काष्ठा acpi_ec *ec)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&ec->lock, flags);
	अगर (ec->curr && (ec->curr->flags & ACPI_EC_COMMAND_COMPLETE))
		ret = 1;
	spin_unlock_irqrestore(&ec->lock, flags);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम ec_transaction_transition(काष्ठा acpi_ec *ec, अचिन्हित दीर्घ flag)
अणु
	ec->curr->flags |= flag;
	अगर (ec->curr->command == ACPI_EC_COMMAND_QUERY) अणु
		अगर (ec_event_clearing == ACPI_EC_EVT_TIMING_STATUS &&
		    flag == ACPI_EC_COMMAND_POLL)
			acpi_ec_complete_query(ec);
		अगर (ec_event_clearing == ACPI_EC_EVT_TIMING_QUERY &&
		    flag == ACPI_EC_COMMAND_COMPLETE)
			acpi_ec_complete_query(ec);
		अगर (ec_event_clearing == ACPI_EC_EVT_TIMING_EVENT &&
		    flag == ACPI_EC_COMMAND_COMPLETE)
			set_bit(EC_FLAGS_QUERY_GUARDING, &ec->flags);
	पूर्ण
पूर्ण

अटल व्योम acpi_ec_spurious_पूर्णांकerrupt(काष्ठा acpi_ec *ec, काष्ठा transaction *t)
अणु
	अगर (t->irq_count < ec_storm_threshold)
		++t->irq_count;

	/* Trigger अगर the threshold is 0 too. */
	अगर (t->irq_count == ec_storm_threshold)
		acpi_ec_mask_events(ec);
पूर्ण

अटल व्योम advance_transaction(काष्ठा acpi_ec *ec, bool पूर्णांकerrupt)
अणु
	काष्ठा transaction *t = ec->curr;
	bool wakeup = false;
	u8 status;

	ec_dbg_sपंचांग("%s (%d)", पूर्णांकerrupt ? "IRQ" : "TASK", smp_processor_id());

	/*
	 * Clear GPE_STS upfront to allow subsequent hardware GPE_STS 0->1
	 * changes to always trigger a GPE पूर्णांकerrupt.
	 *
	 * GPE STS is a W1C रेजिस्टर, which means:
	 *
	 * 1. Software can clear it without worrying about clearing the other
	 *    GPEs' STS bits when the hardware sets them in parallel.
	 *
	 * 2. As दीर्घ as software can ensure only clearing it when it is set,
	 *    hardware won't set it in parallel.
	 */
	अगर (ec->gpe >= 0 && acpi_ec_gpe_status_set(ec))
		acpi_clear_gpe(शून्य, ec->gpe);

	status = acpi_ec_पढ़ो_status(ec);

	/*
	 * Another IRQ or a guarded polling mode advancement is detected,
	 * the next QR_EC submission is then allowed.
	 */
	अगर (!t || !(t->flags & ACPI_EC_COMMAND_POLL)) अणु
		अगर (ec_event_clearing == ACPI_EC_EVT_TIMING_EVENT &&
		    (!ec->nr_pending_queries ||
		     test_bit(EC_FLAGS_QUERY_GUARDING, &ec->flags))) अणु
			clear_bit(EC_FLAGS_QUERY_GUARDING, &ec->flags);
			acpi_ec_complete_query(ec);
		पूर्ण
		अगर (!t)
			जाओ out;
	पूर्ण

	अगर (t->flags & ACPI_EC_COMMAND_POLL) अणु
		अगर (t->wlen > t->wi) अणु
			अगर (!(status & ACPI_EC_FLAG_IBF))
				acpi_ec_ग_लिखो_data(ec, t->wdata[t->wi++]);
			अन्यथा अगर (पूर्णांकerrupt && !(status & ACPI_EC_FLAG_SCI))
				acpi_ec_spurious_पूर्णांकerrupt(ec, t);
		पूर्ण अन्यथा अगर (t->rlen > t->ri) अणु
			अगर (status & ACPI_EC_FLAG_OBF) अणु
				t->rdata[t->ri++] = acpi_ec_पढ़ो_data(ec);
				अगर (t->rlen == t->ri) अणु
					ec_transaction_transition(ec, ACPI_EC_COMMAND_COMPLETE);
					wakeup = true;
					अगर (t->command == ACPI_EC_COMMAND_QUERY)
						ec_dbg_evt("Command(%s) completed by hardware",
							   acpi_ec_cmd_string(ACPI_EC_COMMAND_QUERY));
				पूर्ण
			पूर्ण अन्यथा अगर (पूर्णांकerrupt && !(status & ACPI_EC_FLAG_SCI)) अणु
				acpi_ec_spurious_पूर्णांकerrupt(ec, t);
			पूर्ण
		पूर्ण अन्यथा अगर (t->wlen == t->wi && !(status & ACPI_EC_FLAG_IBF)) अणु
			ec_transaction_transition(ec, ACPI_EC_COMMAND_COMPLETE);
			wakeup = true;
		पूर्ण
	पूर्ण अन्यथा अगर (!(status & ACPI_EC_FLAG_IBF)) अणु
		acpi_ec_ग_लिखो_cmd(ec, t->command);
		ec_transaction_transition(ec, ACPI_EC_COMMAND_POLL);
	पूर्ण

out:
	अगर (status & ACPI_EC_FLAG_SCI)
		acpi_ec_submit_query(ec);

	अगर (wakeup && पूर्णांकerrupt)
		wake_up(&ec->रुको);
पूर्ण

अटल व्योम start_transaction(काष्ठा acpi_ec *ec)
अणु
	ec->curr->irq_count = ec->curr->wi = ec->curr->ri = 0;
	ec->curr->flags = 0;
पूर्ण

अटल पूर्णांक ec_guard(काष्ठा acpi_ec *ec)
अणु
	अचिन्हित दीर्घ guard = usecs_to_jअगरfies(ec->polling_guard);
	अचिन्हित दीर्घ समयout = ec->बारtamp + guard;

	/* Ensure guarding period beक्रमe polling EC status */
	करो अणु
		अगर (ec->busy_polling) अणु
			/* Perक्रमm busy polling */
			अगर (ec_transaction_completed(ec))
				वापस 0;
			udelay(jअगरfies_to_usecs(guard));
		पूर्ण अन्यथा अणु
			/*
			 * Perक्रमm रुको polling
			 * 1. Wait the transaction to be completed by the
			 *    GPE handler after the transaction enters
			 *    ACPI_EC_COMMAND_POLL state.
			 * 2. A special guarding logic is also required
			 *    क्रम event clearing mode "event" beक्रमe the
			 *    transaction enters ACPI_EC_COMMAND_POLL
			 *    state.
			 */
			अगर (!ec_transaction_polled(ec) &&
			    !acpi_ec_guard_event(ec))
				अवरोध;
			अगर (रुको_event_समयout(ec->रुको,
					       ec_transaction_completed(ec),
					       guard))
				वापस 0;
		पूर्ण
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));
	वापस -ETIME;
पूर्ण

अटल पूर्णांक ec_poll(काष्ठा acpi_ec *ec)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक repeat = 5; /* number of command restarts */

	जबतक (repeat--) अणु
		अचिन्हित दीर्घ delay = jअगरfies +
			msecs_to_jअगरfies(ec_delay);
		करो अणु
			अगर (!ec_guard(ec))
				वापस 0;
			spin_lock_irqsave(&ec->lock, flags);
			advance_transaction(ec, false);
			spin_unlock_irqrestore(&ec->lock, flags);
		पूर्ण जबतक (समय_beक्रमe(jअगरfies, delay));
		pr_debug("controller reset, restart transaction\n");
		spin_lock_irqsave(&ec->lock, flags);
		start_transaction(ec);
		spin_unlock_irqrestore(&ec->lock, flags);
	पूर्ण
	वापस -ETIME;
पूर्ण

अटल पूर्णांक acpi_ec_transaction_unlocked(काष्ठा acpi_ec *ec,
					काष्ठा transaction *t)
अणु
	अचिन्हित दीर्घ पंचांगp;
	पूर्णांक ret = 0;

	/* start transaction */
	spin_lock_irqsave(&ec->lock, पंचांगp);
	/* Enable GPE क्रम command processing (IBF=0/OBF=1) */
	अगर (!acpi_ec_submit_flushable_request(ec)) अणु
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण
	ec_dbg_ref(ec, "Increase command");
	/* following two actions should be kept atomic */
	ec->curr = t;
	ec_dbg_req("Command(%s) started", acpi_ec_cmd_string(t->command));
	start_transaction(ec);
	spin_unlock_irqrestore(&ec->lock, पंचांगp);

	ret = ec_poll(ec);

	spin_lock_irqsave(&ec->lock, पंचांगp);
	अगर (t->irq_count == ec_storm_threshold)
		acpi_ec_unmask_events(ec);
	ec_dbg_req("Command(%s) stopped", acpi_ec_cmd_string(t->command));
	ec->curr = शून्य;
	/* Disable GPE क्रम command processing (IBF=0/OBF=1) */
	acpi_ec_complete_request(ec);
	ec_dbg_ref(ec, "Decrease command");
unlock:
	spin_unlock_irqrestore(&ec->lock, पंचांगp);
	वापस ret;
पूर्ण

अटल पूर्णांक acpi_ec_transaction(काष्ठा acpi_ec *ec, काष्ठा transaction *t)
अणु
	पूर्णांक status;
	u32 glk;

	अगर (!ec || (!t) || (t->wlen && !t->wdata) || (t->rlen && !t->rdata))
		वापस -EINVAL;
	अगर (t->rdata)
		स_रखो(t->rdata, 0, t->rlen);

	mutex_lock(&ec->mutex);
	अगर (ec->global_lock) अणु
		status = acpi_acquire_global_lock(ACPI_EC_UDELAY_GLK, &glk);
		अगर (ACPI_FAILURE(status)) अणु
			status = -ENODEV;
			जाओ unlock;
		पूर्ण
	पूर्ण

	status = acpi_ec_transaction_unlocked(ec, t);

	अगर (ec->global_lock)
		acpi_release_global_lock(glk);
unlock:
	mutex_unlock(&ec->mutex);
	वापस status;
पूर्ण

अटल पूर्णांक acpi_ec_burst_enable(काष्ठा acpi_ec *ec)
अणु
	u8 d;
	काष्ठा transaction t = अणु.command = ACPI_EC_BURST_ENABLE,
				.wdata = शून्य, .rdata = &d,
				.wlen = 0, .rlen = 1पूर्ण;

	वापस acpi_ec_transaction(ec, &t);
पूर्ण

अटल पूर्णांक acpi_ec_burst_disable(काष्ठा acpi_ec *ec)
अणु
	काष्ठा transaction t = अणु.command = ACPI_EC_BURST_DISABLE,
				.wdata = शून्य, .rdata = शून्य,
				.wlen = 0, .rlen = 0पूर्ण;

	वापस (acpi_ec_पढ़ो_status(ec) & ACPI_EC_FLAG_BURST) ?
				acpi_ec_transaction(ec, &t) : 0;
पूर्ण

अटल पूर्णांक acpi_ec_पढ़ो(काष्ठा acpi_ec *ec, u8 address, u8 *data)
अणु
	पूर्णांक result;
	u8 d;
	काष्ठा transaction t = अणु.command = ACPI_EC_COMMAND_READ,
				.wdata = &address, .rdata = &d,
				.wlen = 1, .rlen = 1पूर्ण;

	result = acpi_ec_transaction(ec, &t);
	*data = d;
	वापस result;
पूर्ण

अटल पूर्णांक acpi_ec_ग_लिखो(काष्ठा acpi_ec *ec, u8 address, u8 data)
अणु
	u8 wdata[2] = अणु address, data पूर्ण;
	काष्ठा transaction t = अणु.command = ACPI_EC_COMMAND_WRITE,
				.wdata = wdata, .rdata = शून्य,
				.wlen = 2, .rlen = 0पूर्ण;

	वापस acpi_ec_transaction(ec, &t);
पूर्ण

पूर्णांक ec_पढ़ो(u8 addr, u8 *val)
अणु
	पूर्णांक err;
	u8 temp_data;

	अगर (!first_ec)
		वापस -ENODEV;

	err = acpi_ec_पढ़ो(first_ec, addr, &temp_data);

	अगर (!err) अणु
		*val = temp_data;
		वापस 0;
	पूर्ण
	वापस err;
पूर्ण
EXPORT_SYMBOL(ec_पढ़ो);

पूर्णांक ec_ग_लिखो(u8 addr, u8 val)
अणु
	पूर्णांक err;

	अगर (!first_ec)
		वापस -ENODEV;

	err = acpi_ec_ग_लिखो(first_ec, addr, val);

	वापस err;
पूर्ण
EXPORT_SYMBOL(ec_ग_लिखो);

पूर्णांक ec_transaction(u8 command,
		   स्थिर u8 *wdata, अचिन्हित wdata_len,
		   u8 *rdata, अचिन्हित rdata_len)
अणु
	काष्ठा transaction t = अणु.command = command,
				.wdata = wdata, .rdata = rdata,
				.wlen = wdata_len, .rlen = rdata_lenपूर्ण;

	अगर (!first_ec)
		वापस -ENODEV;

	वापस acpi_ec_transaction(first_ec, &t);
पूर्ण
EXPORT_SYMBOL(ec_transaction);

/* Get the handle to the EC device */
acpi_handle ec_get_handle(व्योम)
अणु
	अगर (!first_ec)
		वापस शून्य;
	वापस first_ec->handle;
पूर्ण
EXPORT_SYMBOL(ec_get_handle);

अटल व्योम acpi_ec_start(काष्ठा acpi_ec *ec, bool resuming)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ec->lock, flags);
	अगर (!test_and_set_bit(EC_FLAGS_STARTED, &ec->flags)) अणु
		ec_dbg_drv("Starting EC");
		/* Enable GPE क्रम event processing (SCI_EVT=1) */
		अगर (!resuming) अणु
			acpi_ec_submit_request(ec);
			ec_dbg_ref(ec, "Increase driver");
		पूर्ण
		ec_log_drv("EC started");
	पूर्ण
	spin_unlock_irqrestore(&ec->lock, flags);
पूर्ण

अटल bool acpi_ec_stopped(काष्ठा acpi_ec *ec)
अणु
	अचिन्हित दीर्घ flags;
	bool flushed;

	spin_lock_irqsave(&ec->lock, flags);
	flushed = acpi_ec_flushed(ec);
	spin_unlock_irqrestore(&ec->lock, flags);
	वापस flushed;
पूर्ण

अटल व्योम acpi_ec_stop(काष्ठा acpi_ec *ec, bool suspending)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ec->lock, flags);
	अगर (acpi_ec_started(ec)) अणु
		ec_dbg_drv("Stopping EC");
		set_bit(EC_FLAGS_STOPPED, &ec->flags);
		spin_unlock_irqrestore(&ec->lock, flags);
		रुको_event(ec->रुको, acpi_ec_stopped(ec));
		spin_lock_irqsave(&ec->lock, flags);
		/* Disable GPE क्रम event processing (SCI_EVT=1) */
		अगर (!suspending) अणु
			acpi_ec_complete_request(ec);
			ec_dbg_ref(ec, "Decrease driver");
		पूर्ण अन्यथा अगर (!ec_मुक्तze_events)
			__acpi_ec_disable_event(ec);
		clear_bit(EC_FLAGS_STARTED, &ec->flags);
		clear_bit(EC_FLAGS_STOPPED, &ec->flags);
		ec_log_drv("EC stopped");
	पूर्ण
	spin_unlock_irqrestore(&ec->lock, flags);
पूर्ण

अटल व्योम acpi_ec_enter_noirq(काष्ठा acpi_ec *ec)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ec->lock, flags);
	ec->busy_polling = true;
	ec->polling_guard = 0;
	ec_log_drv("interrupt blocked");
	spin_unlock_irqrestore(&ec->lock, flags);
पूर्ण

अटल व्योम acpi_ec_leave_noirq(काष्ठा acpi_ec *ec)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ec->lock, flags);
	ec->busy_polling = ec_busy_polling;
	ec->polling_guard = ec_polling_guard;
	ec_log_drv("interrupt unblocked");
	spin_unlock_irqrestore(&ec->lock, flags);
पूर्ण

व्योम acpi_ec_block_transactions(व्योम)
अणु
	काष्ठा acpi_ec *ec = first_ec;

	अगर (!ec)
		वापस;

	mutex_lock(&ec->mutex);
	/* Prevent transactions from being carried out */
	acpi_ec_stop(ec, true);
	mutex_unlock(&ec->mutex);
पूर्ण

व्योम acpi_ec_unblock_transactions(व्योम)
अणु
	/*
	 * Allow transactions to happen again (this function is called from
	 * atomic context during wakeup, so we करोn't need to acquire the mutex).
	 */
	अगर (first_ec)
		acpi_ec_start(first_ec, true);
पूर्ण

/* --------------------------------------------------------------------------
                                Event Management
   -------------------------------------------------------------------------- */
अटल काष्ठा acpi_ec_query_handler *
acpi_ec_get_query_handler_by_value(काष्ठा acpi_ec *ec, u8 value)
अणु
	काष्ठा acpi_ec_query_handler *handler;

	mutex_lock(&ec->mutex);
	list_क्रम_each_entry(handler, &ec->list, node) अणु
		अगर (value == handler->query_bit) अणु
			kref_get(&handler->kref);
			mutex_unlock(&ec->mutex);
			वापस handler;
		पूर्ण
	पूर्ण
	mutex_unlock(&ec->mutex);
	वापस शून्य;
पूर्ण

अटल व्योम acpi_ec_query_handler_release(काष्ठा kref *kref)
अणु
	काष्ठा acpi_ec_query_handler *handler =
		container_of(kref, काष्ठा acpi_ec_query_handler, kref);

	kमुक्त(handler);
पूर्ण

अटल व्योम acpi_ec_put_query_handler(काष्ठा acpi_ec_query_handler *handler)
अणु
	kref_put(&handler->kref, acpi_ec_query_handler_release);
पूर्ण

पूर्णांक acpi_ec_add_query_handler(काष्ठा acpi_ec *ec, u8 query_bit,
			      acpi_handle handle, acpi_ec_query_func func,
			      व्योम *data)
अणु
	काष्ठा acpi_ec_query_handler *handler =
	    kzalloc(माप(काष्ठा acpi_ec_query_handler), GFP_KERNEL);

	अगर (!handler)
		वापस -ENOMEM;

	handler->query_bit = query_bit;
	handler->handle = handle;
	handler->func = func;
	handler->data = data;
	mutex_lock(&ec->mutex);
	kref_init(&handler->kref);
	list_add(&handler->node, &ec->list);
	mutex_unlock(&ec->mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_ec_add_query_handler);

अटल व्योम acpi_ec_हटाओ_query_handlers(काष्ठा acpi_ec *ec,
					  bool हटाओ_all, u8 query_bit)
अणु
	काष्ठा acpi_ec_query_handler *handler, *पंचांगp;
	LIST_HEAD(मुक्त_list);

	mutex_lock(&ec->mutex);
	list_क्रम_each_entry_safe(handler, पंचांगp, &ec->list, node) अणु
		अगर (हटाओ_all || query_bit == handler->query_bit) अणु
			list_del_init(&handler->node);
			list_add(&handler->node, &मुक्त_list);
		पूर्ण
	पूर्ण
	mutex_unlock(&ec->mutex);
	list_क्रम_each_entry_safe(handler, पंचांगp, &मुक्त_list, node)
		acpi_ec_put_query_handler(handler);
पूर्ण

व्योम acpi_ec_हटाओ_query_handler(काष्ठा acpi_ec *ec, u8 query_bit)
अणु
	acpi_ec_हटाओ_query_handlers(ec, false, query_bit);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_ec_हटाओ_query_handler);

अटल काष्ठा acpi_ec_query *acpi_ec_create_query(u8 *pval)
अणु
	काष्ठा acpi_ec_query *q;
	काष्ठा transaction *t;

	q = kzalloc(माप (काष्ठा acpi_ec_query), GFP_KERNEL);
	अगर (!q)
		वापस शून्य;
	INIT_WORK(&q->work, acpi_ec_event_processor);
	t = &q->transaction;
	t->command = ACPI_EC_COMMAND_QUERY;
	t->rdata = pval;
	t->rlen = 1;
	वापस q;
पूर्ण

अटल व्योम acpi_ec_delete_query(काष्ठा acpi_ec_query *q)
अणु
	अगर (q) अणु
		अगर (q->handler)
			acpi_ec_put_query_handler(q->handler);
		kमुक्त(q);
	पूर्ण
पूर्ण

अटल व्योम acpi_ec_event_processor(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा acpi_ec_query *q = container_of(work, काष्ठा acpi_ec_query, work);
	काष्ठा acpi_ec_query_handler *handler = q->handler;

	ec_dbg_evt("Query(0x%02x) started", handler->query_bit);
	अगर (handler->func)
		handler->func(handler->data);
	अन्यथा अगर (handler->handle)
		acpi_evaluate_object(handler->handle, शून्य, शून्य, शून्य);
	ec_dbg_evt("Query(0x%02x) stopped", handler->query_bit);
	acpi_ec_delete_query(q);
पूर्ण

अटल पूर्णांक acpi_ec_query(काष्ठा acpi_ec *ec, u8 *data)
अणु
	u8 value = 0;
	पूर्णांक result;
	काष्ठा acpi_ec_query *q;

	q = acpi_ec_create_query(&value);
	अगर (!q)
		वापस -ENOMEM;

	/*
	 * Query the EC to find out which _Qxx method we need to evaluate.
	 * Note that successful completion of the query causes the ACPI_EC_SCI
	 * bit to be cleared (and thus clearing the पूर्णांकerrupt source).
	 */
	result = acpi_ec_transaction(ec, &q->transaction);
	अगर (!value)
		result = -ENODATA;
	अगर (result)
		जाओ err_निकास;

	q->handler = acpi_ec_get_query_handler_by_value(ec, value);
	अगर (!q->handler) अणु
		result = -ENODATA;
		जाओ err_निकास;
	पूर्ण

	/*
	 * It is reported that _Qxx are evaluated in a parallel way on
	 * Winकरोws:
	 * https://bugzilla.kernel.org/show_bug.cgi?id=94411
	 *
	 * Put this log entry beक्रमe schedule_work() in order to make
	 * it appearing beक्रमe any other log entries occurred during the
	 * work queue execution.
	 */
	ec_dbg_evt("Query(0x%02x) scheduled", value);
	अगर (!queue_work(ec_query_wq, &q->work)) अणु
		ec_dbg_evt("Query(0x%02x) overlapped", value);
		result = -EBUSY;
	पूर्ण

err_निकास:
	अगर (result)
		acpi_ec_delete_query(q);
	अगर (data)
		*data = value;
	वापस result;
पूर्ण

अटल व्योम acpi_ec_check_event(काष्ठा acpi_ec *ec)
अणु
	अचिन्हित दीर्घ flags;

	अगर (ec_event_clearing == ACPI_EC_EVT_TIMING_EVENT) अणु
		अगर (ec_guard(ec)) अणु
			spin_lock_irqsave(&ec->lock, flags);
			/*
			 * Take care of the SCI_EVT unless no one अन्यथा is
			 * taking care of it.
			 */
			अगर (!ec->curr)
				advance_transaction(ec, false);
			spin_unlock_irqrestore(&ec->lock, flags);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम acpi_ec_event_handler(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा acpi_ec *ec = container_of(work, काष्ठा acpi_ec, work);

	ec_dbg_evt("Event started");

	spin_lock_irqsave(&ec->lock, flags);
	जबतक (ec->nr_pending_queries) अणु
		spin_unlock_irqrestore(&ec->lock, flags);
		(व्योम)acpi_ec_query(ec, शून्य);
		spin_lock_irqsave(&ec->lock, flags);
		ec->nr_pending_queries--;
		/*
		 * Beक्रमe निकास, make sure that this work item can be
		 * scheduled again. There might be QR_EC failures, leaving
		 * EC_FLAGS_QUERY_PENDING uncleared and preventing this work
		 * item from being scheduled again.
		 */
		अगर (!ec->nr_pending_queries) अणु
			अगर (ec_event_clearing == ACPI_EC_EVT_TIMING_STATUS ||
			    ec_event_clearing == ACPI_EC_EVT_TIMING_QUERY)
				acpi_ec_complete_query(ec);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ec->lock, flags);

	ec_dbg_evt("Event stopped");

	acpi_ec_check_event(ec);
पूर्ण

अटल व्योम acpi_ec_handle_पूर्णांकerrupt(काष्ठा acpi_ec *ec)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ec->lock, flags);
	advance_transaction(ec, true);
	spin_unlock_irqrestore(&ec->lock, flags);
पूर्ण

अटल u32 acpi_ec_gpe_handler(acpi_handle gpe_device,
			       u32 gpe_number, व्योम *data)
अणु
	acpi_ec_handle_पूर्णांकerrupt(data);
	वापस ACPI_INTERRUPT_HANDLED;
पूर्ण

अटल irqवापस_t acpi_ec_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	acpi_ec_handle_पूर्णांकerrupt(data);
	वापस IRQ_HANDLED;
पूर्ण

/* --------------------------------------------------------------------------
 *                           Address Space Management
 * -------------------------------------------------------------------------- */

अटल acpi_status
acpi_ec_space_handler(u32 function, acpi_physical_address address,
		      u32 bits, u64 *value64,
		      व्योम *handler_context, व्योम *region_context)
अणु
	काष्ठा acpi_ec *ec = handler_context;
	पूर्णांक result = 0, i, bytes = bits / 8;
	u8 *value = (u8 *)value64;

	अगर ((address > 0xFF) || !value || !handler_context)
		वापस AE_BAD_PARAMETER;

	अगर (function != ACPI_READ && function != ACPI_WRITE)
		वापस AE_BAD_PARAMETER;

	अगर (ec->busy_polling || bits > 8)
		acpi_ec_burst_enable(ec);

	क्रम (i = 0; i < bytes; ++i, ++address, ++value)
		result = (function == ACPI_READ) ?
			acpi_ec_पढ़ो(ec, address, value) :
			acpi_ec_ग_लिखो(ec, address, *value);

	अगर (ec->busy_polling || bits > 8)
		acpi_ec_burst_disable(ec);

	चयन (result) अणु
	हाल -EINVAL:
		वापस AE_BAD_PARAMETER;
	हाल -ENODEV:
		वापस AE_NOT_FOUND;
	हाल -ETIME:
		वापस AE_TIME;
	शेष:
		वापस AE_OK;
	पूर्ण
पूर्ण

/* --------------------------------------------------------------------------
 *                             Driver Interface
 * -------------------------------------------------------------------------- */

अटल acpi_status
ec_parse_io_ports(काष्ठा acpi_resource *resource, व्योम *context);

अटल व्योम acpi_ec_मुक्त(काष्ठा acpi_ec *ec)
अणु
	अगर (first_ec == ec)
		first_ec = शून्य;
	अगर (boot_ec == ec)
		boot_ec = शून्य;
	kमुक्त(ec);
पूर्ण

अटल काष्ठा acpi_ec *acpi_ec_alloc(व्योम)
अणु
	काष्ठा acpi_ec *ec = kzalloc(माप(काष्ठा acpi_ec), GFP_KERNEL);

	अगर (!ec)
		वापस शून्य;
	mutex_init(&ec->mutex);
	init_रुकोqueue_head(&ec->रुको);
	INIT_LIST_HEAD(&ec->list);
	spin_lock_init(&ec->lock);
	INIT_WORK(&ec->work, acpi_ec_event_handler);
	ec->बारtamp = jअगरfies;
	ec->busy_polling = true;
	ec->polling_guard = 0;
	ec->gpe = -1;
	ec->irq = -1;
	वापस ec;
पूर्ण

अटल acpi_status
acpi_ec_रेजिस्टर_query_methods(acpi_handle handle, u32 level,
			       व्योम *context, व्योम **वापस_value)
अणु
	अक्षर node_name[5];
	काष्ठा acpi_buffer buffer = अणु माप(node_name), node_name पूर्ण;
	काष्ठा acpi_ec *ec = context;
	पूर्णांक value = 0;
	acpi_status status;

	status = acpi_get_name(handle, ACPI_SINGLE_NAME, &buffer);

	अगर (ACPI_SUCCESS(status) && माला_पूछो(node_name, "_Q%x", &value) == 1)
		acpi_ec_add_query_handler(ec, value, handle, शून्य, शून्य);
	वापस AE_OK;
पूर्ण

अटल acpi_status
ec_parse_device(acpi_handle handle, u32 Level, व्योम *context, व्योम **retval)
अणु
	acpi_status status;
	अचिन्हित दीर्घ दीर्घ पंचांगp = 0;
	काष्ठा acpi_ec *ec = context;

	/* clear addr values, ec_parse_io_ports depend on it */
	ec->command_addr = ec->data_addr = 0;

	status = acpi_walk_resources(handle, METHOD_NAME__CRS,
				     ec_parse_io_ports, ec);
	अगर (ACPI_FAILURE(status))
		वापस status;
	अगर (ec->data_addr == 0 || ec->command_addr == 0)
		वापस AE_OK;

	अगर (boot_ec && boot_ec_is_ecdt && EC_FLAGS_IGNORE_DSDT_GPE) अणु
		/*
		 * Always inherit the GPE number setting from the ECDT
		 * EC.
		 */
		ec->gpe = boot_ec->gpe;
	पूर्ण अन्यथा अणु
		/* Get GPE bit assignment (EC events). */
		/* TODO: Add support क्रम _GPE वापसing a package */
		status = acpi_evaluate_पूर्णांकeger(handle, "_GPE", शून्य, &पंचांगp);
		अगर (ACPI_SUCCESS(status))
			ec->gpe = पंचांगp;

		/*
		 * Errors are non-fatal, allowing क्रम ACPI Reduced Hardware
		 * platक्रमms which use GpioInt instead of GPE.
		 */
	पूर्ण
	/* Use the global lock क्रम all EC transactions? */
	पंचांगp = 0;
	acpi_evaluate_पूर्णांकeger(handle, "_GLK", शून्य, &पंचांगp);
	ec->global_lock = पंचांगp;
	ec->handle = handle;
	वापस AE_CTRL_TERMINATE;
पूर्ण

अटल bool install_gpe_event_handler(काष्ठा acpi_ec *ec)
अणु
	acpi_status status;

	status = acpi_install_gpe_raw_handler(शून्य, ec->gpe,
					      ACPI_GPE_EDGE_TRIGGERED,
					      &acpi_ec_gpe_handler, ec);
	अगर (ACPI_FAILURE(status))
		वापस false;

	अगर (test_bit(EC_FLAGS_STARTED, &ec->flags) && ec->reference_count >= 1)
		acpi_ec_enable_gpe(ec, true);

	वापस true;
पूर्ण

अटल bool install_gpio_irq_event_handler(काष्ठा acpi_ec *ec)
अणु
	वापस request_irq(ec->irq, acpi_ec_irq_handler, IRQF_SHARED,
			   "ACPI EC", ec) >= 0;
पूर्ण

/**
 * ec_install_handlers - Install service callbacks and रेजिस्टर query methods.
 * @ec: Target EC.
 * @device: ACPI device object corresponding to @ec.
 *
 * Install a handler क्रम the EC address space type unless it has been installed
 * alपढ़ोy.  If @device is not शून्य, also look क्रम EC query methods in the
 * namespace and रेजिस्टर them, and install an event (either GPE or GPIO IRQ)
 * handler क्रम the EC, अगर possible.
 *
 * Return:
 * -ENODEV अगर the address space handler cannot be installed, which means
 *  "unable to handle transactions",
 * -EPROBE_DEFER अगर GPIO IRQ acquisition needs to be deferred,
 * or 0 (success) otherwise.
 */
अटल पूर्णांक ec_install_handlers(काष्ठा acpi_ec *ec, काष्ठा acpi_device *device)
अणु
	acpi_status status;

	acpi_ec_start(ec, false);

	अगर (!test_bit(EC_FLAGS_EC_HANDLER_INSTALLED, &ec->flags)) अणु
		acpi_ec_enter_noirq(ec);
		status = acpi_install_address_space_handler(ec->handle,
							    ACPI_ADR_SPACE_EC,
							    &acpi_ec_space_handler,
							    शून्य, ec);
		अगर (ACPI_FAILURE(status)) अणु
			acpi_ec_stop(ec, false);
			वापस -ENODEV;
		पूर्ण
		set_bit(EC_FLAGS_EC_HANDLER_INSTALLED, &ec->flags);
	पूर्ण

	अगर (!device)
		वापस 0;

	अगर (ec->gpe < 0) अणु
		/* ACPI reduced hardware platक्रमms use a GpioInt from _CRS. */
		पूर्णांक irq = acpi_dev_gpio_irq_get(device, 0);
		/*
		 * Bail out right away क्रम deferred probing or complete the
		 * initialization regardless of any other errors.
		 */
		अगर (irq == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		अन्यथा अगर (irq >= 0)
			ec->irq = irq;
	पूर्ण

	अगर (!test_bit(EC_FLAGS_QUERY_METHODS_INSTALLED, &ec->flags)) अणु
		/* Find and रेजिस्टर all query methods */
		acpi_walk_namespace(ACPI_TYPE_METHOD, ec->handle, 1,
				    acpi_ec_रेजिस्टर_query_methods,
				    शून्य, ec, शून्य);
		set_bit(EC_FLAGS_QUERY_METHODS_INSTALLED, &ec->flags);
	पूर्ण
	अगर (!test_bit(EC_FLAGS_EVENT_HANDLER_INSTALLED, &ec->flags)) अणु
		bool पढ़ोy = false;

		अगर (ec->gpe >= 0)
			पढ़ोy = install_gpe_event_handler(ec);
		अन्यथा अगर (ec->irq >= 0)
			पढ़ोy = install_gpio_irq_event_handler(ec);

		अगर (पढ़ोy) अणु
			set_bit(EC_FLAGS_EVENT_HANDLER_INSTALLED, &ec->flags);
			acpi_ec_leave_noirq(ec);
		पूर्ण
		/*
		 * Failures to install an event handler are not fatal, because
		 * the EC can be polled क्रम events.
		 */
	पूर्ण
	/* EC is fully operational, allow queries */
	acpi_ec_enable_event(ec);

	वापस 0;
पूर्ण

अटल व्योम ec_हटाओ_handlers(काष्ठा acpi_ec *ec)
अणु
	अगर (test_bit(EC_FLAGS_EC_HANDLER_INSTALLED, &ec->flags)) अणु
		अगर (ACPI_FAILURE(acpi_हटाओ_address_space_handler(ec->handle,
					ACPI_ADR_SPACE_EC, &acpi_ec_space_handler)))
			pr_err("failed to remove space handler\n");
		clear_bit(EC_FLAGS_EC_HANDLER_INSTALLED, &ec->flags);
	पूर्ण

	/*
	 * Stops handling the EC transactions after removing the operation
	 * region handler. This is required because _REG(DISCONNECT)
	 * invoked during the removal can result in new EC transactions.
	 *
	 * Flushes the EC requests and thus disables the GPE beक्रमe
	 * removing the GPE handler. This is required by the current ACPICA
	 * GPE core. ACPICA GPE core will स्वतःmatically disable a GPE when
	 * it is indicated but there is no way to handle it. So the drivers
	 * must disable the GPEs prior to removing the GPE handlers.
	 */
	acpi_ec_stop(ec, false);

	अगर (test_bit(EC_FLAGS_EVENT_HANDLER_INSTALLED, &ec->flags)) अणु
		अगर (ec->gpe >= 0 &&
		    ACPI_FAILURE(acpi_हटाओ_gpe_handler(शून्य, ec->gpe,
				 &acpi_ec_gpe_handler)))
			pr_err("failed to remove gpe handler\n");

		अगर (ec->irq >= 0)
			मुक्त_irq(ec->irq, ec);

		clear_bit(EC_FLAGS_EVENT_HANDLER_INSTALLED, &ec->flags);
	पूर्ण
	अगर (test_bit(EC_FLAGS_QUERY_METHODS_INSTALLED, &ec->flags)) अणु
		acpi_ec_हटाओ_query_handlers(ec, true, 0);
		clear_bit(EC_FLAGS_QUERY_METHODS_INSTALLED, &ec->flags);
	पूर्ण
पूर्ण

अटल पूर्णांक acpi_ec_setup(काष्ठा acpi_ec *ec, काष्ठा acpi_device *device)
अणु
	पूर्णांक ret;

	ret = ec_install_handlers(ec, device);
	अगर (ret)
		वापस ret;

	/* First EC capable of handling transactions */
	अगर (!first_ec)
		first_ec = ec;

	pr_info("EC_CMD/EC_SC=0x%lx, EC_DATA=0x%lx\n", ec->command_addr,
		ec->data_addr);

	अगर (test_bit(EC_FLAGS_EVENT_HANDLER_INSTALLED, &ec->flags)) अणु
		अगर (ec->gpe >= 0)
			pr_info("GPE=0x%x\n", ec->gpe);
		अन्यथा
			pr_info("IRQ=%d\n", ec->irq);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक acpi_ec_add(काष्ठा acpi_device *device)
अणु
	काष्ठा acpi_ec *ec;
	पूर्णांक ret;

	म_नकल(acpi_device_name(device), ACPI_EC_DEVICE_NAME);
	म_नकल(acpi_device_class(device), ACPI_EC_CLASS);

	अगर (boot_ec && (boot_ec->handle == device->handle ||
	    !म_भेद(acpi_device_hid(device), ACPI_ECDT_HID))) अणु
		/* Fast path: this device corresponds to the boot EC. */
		ec = boot_ec;
	पूर्ण अन्यथा अणु
		acpi_status status;

		ec = acpi_ec_alloc();
		अगर (!ec)
			वापस -ENOMEM;

		status = ec_parse_device(device->handle, 0, ec, शून्य);
		अगर (status != AE_CTRL_TERMINATE) अणु
			ret = -EINVAL;
			जाओ err;
		पूर्ण

		अगर (boot_ec && ec->command_addr == boot_ec->command_addr &&
		    ec->data_addr == boot_ec->data_addr) अणु
			/*
			 * Trust PNP0C09 namespace location rather than
			 * ECDT ID. But trust ECDT GPE rather than _GPE
			 * because of ASUS quirks, so करो not change
			 * boot_ec->gpe to ec->gpe.
			 */
			boot_ec->handle = ec->handle;
			acpi_handle_debug(ec->handle, "duplicated.\n");
			acpi_ec_मुक्त(ec);
			ec = boot_ec;
		पूर्ण
	पूर्ण

	ret = acpi_ec_setup(ec, device);
	अगर (ret)
		जाओ err;

	अगर (ec == boot_ec)
		acpi_handle_info(boot_ec->handle,
				 "Boot %s EC initialization complete\n",
				 boot_ec_is_ecdt ? "ECDT" : "DSDT");

	acpi_handle_info(ec->handle,
			 "EC: Used to handle transactions and events\n");

	device->driver_data = ec;

	ret = !!request_region(ec->data_addr, 1, "EC data");
	WARN(!ret, "Could not request EC data io port 0x%lx", ec->data_addr);
	ret = !!request_region(ec->command_addr, 1, "EC cmd");
	WARN(!ret, "Could not request EC cmd io port 0x%lx", ec->command_addr);

	/* Reprobe devices depending on the EC */
	acpi_walk_dep_device_list(ec->handle);

	acpi_handle_debug(ec->handle, "enumerated.\n");
	वापस 0;

err:
	अगर (ec != boot_ec)
		acpi_ec_मुक्त(ec);

	वापस ret;
पूर्ण

अटल पूर्णांक acpi_ec_हटाओ(काष्ठा acpi_device *device)
अणु
	काष्ठा acpi_ec *ec;

	अगर (!device)
		वापस -EINVAL;

	ec = acpi_driver_data(device);
	release_region(ec->data_addr, 1);
	release_region(ec->command_addr, 1);
	device->driver_data = शून्य;
	अगर (ec != boot_ec) अणु
		ec_हटाओ_handlers(ec);
		acpi_ec_मुक्त(ec);
	पूर्ण
	वापस 0;
पूर्ण

अटल acpi_status
ec_parse_io_ports(काष्ठा acpi_resource *resource, व्योम *context)
अणु
	काष्ठा acpi_ec *ec = context;

	अगर (resource->type != ACPI_RESOURCE_TYPE_IO)
		वापस AE_OK;

	/*
	 * The first address region वापसed is the data port, and
	 * the second address region वापसed is the status/command
	 * port.
	 */
	अगर (ec->data_addr == 0)
		ec->data_addr = resource->data.io.minimum;
	अन्यथा अगर (ec->command_addr == 0)
		ec->command_addr = resource->data.io.minimum;
	अन्यथा
		वापस AE_CTRL_TERMINATE;

	वापस AE_OK;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id ec_device_ids[] = अणु
	अणु"PNP0C09", 0पूर्ण,
	अणुACPI_ECDT_HID, 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;

/*
 * This function is not Winकरोws-compatible as Winकरोws never क्रमागतerates the
 * namespace EC beक्रमe the मुख्य ACPI device क्रमागतeration process. It is
 * retained क्रम historical reason and will be deprecated in the future.
 */
व्योम __init acpi_ec_dsdt_probe(व्योम)
अणु
	काष्ठा acpi_ec *ec;
	acpi_status status;
	पूर्णांक ret;

	/*
	 * If a platक्रमm has ECDT, there is no need to proceed as the
	 * following probe is not a part of the ACPI device क्रमागतeration,
	 * executing _STA is not safe, and thus this probe may risk of
	 * picking up an invalid EC device.
	 */
	अगर (boot_ec)
		वापस;

	ec = acpi_ec_alloc();
	अगर (!ec)
		वापस;

	/*
	 * At this poपूर्णांक, the namespace is initialized, so start to find
	 * the namespace objects.
	 */
	status = acpi_get_devices(ec_device_ids[0].id, ec_parse_device, ec, शून्य);
	अगर (ACPI_FAILURE(status) || !ec->handle) अणु
		acpi_ec_मुक्त(ec);
		वापस;
	पूर्ण

	/*
	 * When the DSDT EC is available, always re-configure boot EC to
	 * have _REG evaluated. _REG can only be evaluated after the
	 * namespace initialization.
	 * At this poपूर्णांक, the GPE is not fully initialized, so करो not to
	 * handle the events.
	 */
	ret = acpi_ec_setup(ec, शून्य);
	अगर (ret) अणु
		acpi_ec_मुक्त(ec);
		वापस;
	पूर्ण

	boot_ec = ec;

	acpi_handle_info(ec->handle,
			 "Boot DSDT EC used to handle transactions\n");
पूर्ण

/*
 * acpi_ec_ecdt_start - Finalize the boot ECDT EC initialization.
 *
 * First, look क्रम an ACPI handle क्रम the boot ECDT EC अगर acpi_ec_add() has not
 * found a matching object in the namespace.
 *
 * Next, in हाल the DSDT EC is not functioning, it is still necessary to
 * provide a functional ECDT EC to handle events, so add an extra device object
 * to represent it (see https://bugzilla.kernel.org/show_bug.cgi?id=115021).
 *
 * This is useful on platक्रमms with valid ECDT and invalid DSDT EC settings,
 * like ASUS X550ZE (see https://bugzilla.kernel.org/show_bug.cgi?id=196847).
 */
अटल व्योम __init acpi_ec_ecdt_start(व्योम)
अणु
	काष्ठा acpi_table_ecdt *ecdt_ptr;
	acpi_handle handle;
	acpi_status status;

	/* Bail out अगर a matching EC has been found in the namespace. */
	अगर (!boot_ec || boot_ec->handle != ACPI_ROOT_OBJECT)
		वापस;

	/* Look up the object poपूर्णांकed to from the ECDT in the namespace. */
	status = acpi_get_table(ACPI_SIG_ECDT, 1,
				(काष्ठा acpi_table_header **)&ecdt_ptr);
	अगर (ACPI_FAILURE(status))
		वापस;

	status = acpi_get_handle(शून्य, ecdt_ptr->id, &handle);
	अगर (ACPI_SUCCESS(status)) अणु
		boot_ec->handle = handle;

		/* Add a special ACPI device object to represent the boot EC. */
		acpi_bus_रेजिस्टर_early_device(ACPI_BUS_TYPE_ECDT_EC);
	पूर्ण

	acpi_put_table((काष्ठा acpi_table_header *)ecdt_ptr);
पूर्ण

/*
 * On some hardware it is necessary to clear events accumulated by the EC during
 * sleep. These ECs stop reporting GPEs until they are manually polled, अगर too
 * many events are accumulated. (e.g. Samsung Series 5/9 notebooks)
 *
 * https://bugzilla.kernel.org/show_bug.cgi?id=44161
 *
 * Ideally, the EC should also be inकाष्ठाed NOT to accumulate events during
 * sleep (which Winकरोws seems to करो somehow), but the पूर्णांकerface to control this
 * behaviour is not known at this समय.
 *
 * Models known to be affected are Samsung 530Uxx/535Uxx/540Uxx/550Pxx/900Xxx,
 * however it is very likely that other Samsung models are affected.
 *
 * On प्रणालीs which करोn't accumulate _Q events during sleep, this extra check
 * should be harmless.
 */
अटल पूर्णांक ec_clear_on_resume(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	pr_debug("Detected system needing EC poll on resume.\n");
	EC_FLAGS_CLEAR_ON_RESUME = 1;
	ec_event_clearing = ACPI_EC_EVT_TIMING_STATUS;
	वापस 0;
पूर्ण

/*
 * Some ECDTs contain wrong रेजिस्टर addresses.
 * MSI MS-171F
 * https://bugzilla.kernel.org/show_bug.cgi?id=12461
 */
अटल पूर्णांक ec_correct_ecdt(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	pr_debug("Detected system needing ECDT address correction.\n");
	EC_FLAGS_CORRECT_ECDT = 1;
	वापस 0;
पूर्ण

/*
 * Some DSDTs contain wrong GPE setting.
 * Asus FX502VD/VE, GL702VMK, X550VXK, X580VD
 * https://bugzilla.kernel.org/show_bug.cgi?id=195651
 */
अटल पूर्णांक ec_honor_ecdt_gpe(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	pr_debug("Detected system needing ignore DSDT GPE setting.\n");
	EC_FLAGS_IGNORE_DSDT_GPE = 1;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id ec_dmi_table[] __initस्थिर = अणु
	अणु
	ec_correct_ecdt, "MSI MS-171F", अणु
	DMI_MATCH(DMI_SYS_VENDOR, "Micro-Star"),
	DMI_MATCH(DMI_PRODUCT_NAME, "MS-171F"),पूर्ण, शून्यपूर्ण,
	अणु
	ec_honor_ecdt_gpe, "ASUS FX502VD", अणु
	DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
	DMI_MATCH(DMI_PRODUCT_NAME, "FX502VD"),पूर्ण, शून्यपूर्ण,
	अणु
	ec_honor_ecdt_gpe, "ASUS FX502VE", अणु
	DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
	DMI_MATCH(DMI_PRODUCT_NAME, "FX502VE"),पूर्ण, शून्यपूर्ण,
	अणु
	ec_honor_ecdt_gpe, "ASUS GL702VMK", अणु
	DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
	DMI_MATCH(DMI_PRODUCT_NAME, "GL702VMK"),पूर्ण, शून्यपूर्ण,
	अणु
	ec_honor_ecdt_gpe, "ASUS X550VXK", अणु
	DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
	DMI_MATCH(DMI_PRODUCT_NAME, "X550VXK"),पूर्ण, शून्यपूर्ण,
	अणु
	ec_honor_ecdt_gpe, "ASUS X580VD", अणु
	DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
	DMI_MATCH(DMI_PRODUCT_NAME, "X580VD"),पूर्ण, शून्यपूर्ण,
	अणु
	ec_clear_on_resume, "Samsung hardware", अणु
	DMI_MATCH(DMI_SYS_VENDOR, "SAMSUNG ELECTRONICS CO., LTD.")पूर्ण, शून्यपूर्ण,
	अणुपूर्ण,
पूर्ण;

व्योम __init acpi_ec_ecdt_probe(व्योम)
अणु
	काष्ठा acpi_table_ecdt *ecdt_ptr;
	काष्ठा acpi_ec *ec;
	acpi_status status;
	पूर्णांक ret;

	/* Generate a boot ec context. */
	dmi_check_प्रणाली(ec_dmi_table);
	status = acpi_get_table(ACPI_SIG_ECDT, 1,
				(काष्ठा acpi_table_header **)&ecdt_ptr);
	अगर (ACPI_FAILURE(status))
		वापस;

	अगर (!ecdt_ptr->control.address || !ecdt_ptr->data.address) अणु
		/*
		 * Asus X50GL:
		 * https://bugzilla.kernel.org/show_bug.cgi?id=11880
		 */
		जाओ out;
	पूर्ण

	ec = acpi_ec_alloc();
	अगर (!ec)
		जाओ out;

	अगर (EC_FLAGS_CORRECT_ECDT) अणु
		ec->command_addr = ecdt_ptr->data.address;
		ec->data_addr = ecdt_ptr->control.address;
	पूर्ण अन्यथा अणु
		ec->command_addr = ecdt_ptr->control.address;
		ec->data_addr = ecdt_ptr->data.address;
	पूर्ण

	/*
	 * Ignore the GPE value on Reduced Hardware platक्रमms.
	 * Some products have this set to an erroneous value.
	 */
	अगर (!acpi_gbl_reduced_hardware)
		ec->gpe = ecdt_ptr->gpe;

	ec->handle = ACPI_ROOT_OBJECT;

	/*
	 * At this poपूर्णांक, the namespace is not initialized, so करो not find
	 * the namespace objects, or handle the events.
	 */
	ret = acpi_ec_setup(ec, शून्य);
	अगर (ret) अणु
		acpi_ec_मुक्त(ec);
		जाओ out;
	पूर्ण

	boot_ec = ec;
	boot_ec_is_ecdt = true;

	pr_info("Boot ECDT EC used to handle transactions\n");

out:
	acpi_put_table((काष्ठा acpi_table_header *)ecdt_ptr);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक acpi_ec_suspend(काष्ठा device *dev)
अणु
	काष्ठा acpi_ec *ec =
		acpi_driver_data(to_acpi_device(dev));

	अगर (!pm_suspend_no_platक्रमm() && ec_मुक्तze_events)
		acpi_ec_disable_event(ec);
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_ec_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा acpi_ec *ec = acpi_driver_data(to_acpi_device(dev));

	/*
	 * The SCI handler करोesn't run at this poपूर्णांक, so the GPE can be
	 * masked at the low level without side effects.
	 */
	अगर (ec_no_wakeup && test_bit(EC_FLAGS_STARTED, &ec->flags) &&
	    ec->gpe >= 0 && ec->reference_count >= 1)
		acpi_set_gpe(शून्य, ec->gpe, ACPI_GPE_DISABLE);

	acpi_ec_enter_noirq(ec);

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_ec_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा acpi_ec *ec = acpi_driver_data(to_acpi_device(dev));

	acpi_ec_leave_noirq(ec);

	अगर (ec_no_wakeup && test_bit(EC_FLAGS_STARTED, &ec->flags) &&
	    ec->gpe >= 0 && ec->reference_count >= 1)
		acpi_set_gpe(शून्य, ec->gpe, ACPI_GPE_ENABLE);

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_ec_resume(काष्ठा device *dev)
अणु
	काष्ठा acpi_ec *ec =
		acpi_driver_data(to_acpi_device(dev));

	acpi_ec_enable_event(ec);
	वापस 0;
पूर्ण

व्योम acpi_ec_mark_gpe_क्रम_wake(व्योम)
अणु
	अगर (first_ec && !ec_no_wakeup)
		acpi_mark_gpe_क्रम_wake(शून्य, first_ec->gpe);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_ec_mark_gpe_क्रम_wake);

व्योम acpi_ec_set_gpe_wake_mask(u8 action)
अणु
	अगर (pm_suspend_no_platक्रमm() && first_ec && !ec_no_wakeup)
		acpi_set_gpe_wake_mask(शून्य, first_ec->gpe, action);
पूर्ण

bool acpi_ec_dispatch_gpe(व्योम)
अणु
	u32 ret;

	अगर (!first_ec)
		वापस acpi_any_gpe_status_set(U32_MAX);

	/*
	 * Report wakeup अगर the status bit is set क्रम any enabled GPE other
	 * than the EC one.
	 */
	अगर (acpi_any_gpe_status_set(first_ec->gpe))
		वापस true;

	/*
	 * Dispatch the EC GPE in-band, but करो not report wakeup in any हाल
	 * to allow the caller to process events properly after that.
	 */
	ret = acpi_dispatch_gpe(शून्य, first_ec->gpe);
	अगर (ret == ACPI_INTERRUPT_HANDLED)
		pm_pr_dbg("ACPI EC GPE dispatched\n");

	/* Flush the event and query workqueues. */
	acpi_ec_flush_work();

	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा dev_pm_ops acpi_ec_pm = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(acpi_ec_suspend_noirq, acpi_ec_resume_noirq)
	SET_SYSTEM_SLEEP_PM_OPS(acpi_ec_suspend, acpi_ec_resume)
पूर्ण;

अटल पूर्णांक param_set_event_clearing(स्थिर अक्षर *val,
				    स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक result = 0;

	अगर (!म_भेदन(val, "status", माप("status") - 1)) अणु
		ec_event_clearing = ACPI_EC_EVT_TIMING_STATUS;
		pr_info("Assuming SCI_EVT clearing on EC_SC accesses\n");
	पूर्ण अन्यथा अगर (!म_भेदन(val, "query", माप("query") - 1)) अणु
		ec_event_clearing = ACPI_EC_EVT_TIMING_QUERY;
		pr_info("Assuming SCI_EVT clearing on QR_EC writes\n");
	पूर्ण अन्यथा अगर (!म_भेदन(val, "event", माप("event") - 1)) अणु
		ec_event_clearing = ACPI_EC_EVT_TIMING_EVENT;
		pr_info("Assuming SCI_EVT clearing on event reads\n");
	पूर्ण अन्यथा
		result = -EINVAL;
	वापस result;
पूर्ण

अटल पूर्णांक param_get_event_clearing(अक्षर *buffer,
				    स्थिर काष्ठा kernel_param *kp)
अणु
	चयन (ec_event_clearing) अणु
	हाल ACPI_EC_EVT_TIMING_STATUS:
		वापस प्र_लिखो(buffer, "status\n");
	हाल ACPI_EC_EVT_TIMING_QUERY:
		वापस प्र_लिखो(buffer, "query\n");
	हाल ACPI_EC_EVT_TIMING_EVENT:
		वापस प्र_लिखो(buffer, "event\n");
	शेष:
		वापस प्र_लिखो(buffer, "invalid\n");
	पूर्ण
	वापस 0;
पूर्ण

module_param_call(ec_event_clearing, param_set_event_clearing, param_get_event_clearing,
		  शून्य, 0644);
MODULE_PARM_DESC(ec_event_clearing, "Assumed SCI_EVT clearing timing");

अटल काष्ठा acpi_driver acpi_ec_driver = अणु
	.name = "ec",
	.class = ACPI_EC_CLASS,
	.ids = ec_device_ids,
	.ops = अणु
		.add = acpi_ec_add,
		.हटाओ = acpi_ec_हटाओ,
		पूर्ण,
	.drv.pm = &acpi_ec_pm,
पूर्ण;

अटल व्योम acpi_ec_destroy_workqueues(व्योम)
अणु
	अगर (ec_wq) अणु
		destroy_workqueue(ec_wq);
		ec_wq = शून्य;
	पूर्ण
	अगर (ec_query_wq) अणु
		destroy_workqueue(ec_query_wq);
		ec_query_wq = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक acpi_ec_init_workqueues(व्योम)
अणु
	अगर (!ec_wq)
		ec_wq = alloc_ordered_workqueue("kec", 0);

	अगर (!ec_query_wq)
		ec_query_wq = alloc_workqueue("kec_query", 0, ec_max_queries);

	अगर (!ec_wq || !ec_query_wq) अणु
		acpi_ec_destroy_workqueues();
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id acpi_ec_no_wakeup[] = अणु
	अणु
		.ident = "Thinkpad X1 Carbon 6th",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_FAMILY, "Thinkpad X1 Carbon 6th"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "ThinkPad X1 Carbon 6th",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_FAMILY, "ThinkPad X1 Carbon 6th"),
		पूर्ण,
	पूर्ण,
	अणु
		.ident = "ThinkPad X1 Yoga 3rd",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_FAMILY, "ThinkPad X1 Yoga 3rd"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

व्योम __init acpi_ec_init(व्योम)
अणु
	पूर्णांक result;

	result = acpi_ec_init_workqueues();
	अगर (result)
		वापस;

	/*
	 * Disable EC wakeup on following प्रणालीs to prevent periodic
	 * wakeup from EC GPE.
	 */
	अगर (dmi_check_प्रणाली(acpi_ec_no_wakeup)) अणु
		ec_no_wakeup = true;
		pr_debug("Disabling EC wakeup on suspend-to-idle\n");
	पूर्ण

	/* Driver must be रेजिस्टरed after acpi_ec_init_workqueues(). */
	acpi_bus_रेजिस्टर_driver(&acpi_ec_driver);

	acpi_ec_ecdt_start();
पूर्ण

/* EC driver currently not unloadable */
#अगर 0
अटल व्योम __निकास acpi_ec_निकास(व्योम)
अणु

	acpi_bus_unरेजिस्टर_driver(&acpi_ec_driver);
	acpi_ec_destroy_workqueues();
पूर्ण
#पूर्ण_अगर	/* 0 */
