<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * File:	mca.c
 * Purpose:	Generic MCA handling layer
 *
 * Copyright (C) 2003 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 *
 * Copyright (C) 2002 Dell Inc.
 * Copyright (C) Matt Domsch <Matt_Domsch@dell.com>
 *
 * Copyright (C) 2002 Intel
 * Copyright (C) Jenna Hall <jenna.s.hall@पूर्णांकel.com>
 *
 * Copyright (C) 2001 Intel
 * Copyright (C) Fred Lewis <frederick.v.lewis@पूर्णांकel.com>
 *
 * Copyright (C) 2000 Intel
 * Copyright (C) Chuck Fleckenstein <cfleck@co.पूर्णांकel.com>
 *
 * Copyright (C) 1999, 2004-2008 Silicon Graphics, Inc.
 * Copyright (C) Vijay Chander <vijay@engr.sgi.com>
 *
 * Copyright (C) 2006 FUJITSU LIMITED
 * Copyright (C) Hidetoshi Seto <seto.hidetoshi@jp.fujitsu.com>
 *
 * 2000-03-29 Chuck Fleckenstein <cfleck@co.पूर्णांकel.com>
 *	      Fixed PAL/SAL update issues, began MCA bug fixes, logging issues,
 *	      added min save state dump, added INIT handler.
 *
 * 2001-01-03 Fred Lewis <frederick.v.lewis@पूर्णांकel.com>
 *	      Added setup of CMCI and CPEI IRQs, logging of corrected platक्रमm
 *	      errors, completed code क्रम logging of corrected & uncorrected
 *	      machine check errors, and updated क्रम conक्रमmance with Nov. 2000
 *	      revision of the SAL 3.0 spec.
 *
 * 2002-01-04 Jenna Hall <jenna.s.hall@पूर्णांकel.com>
 *	      Aligned MCA stack to 16 bytes, added platक्रमm vs. CPU error flag,
 *	      set SAL शेष वापस values, changed error record काष्ठाure to
 *	      linked list, added init call to sal_get_state_info_size().
 *
 * 2002-03-25 Matt Domsch <Matt_Domsch@dell.com>
 *	      GUID cleanups.
 *
 * 2003-04-15 David Mosberger-Tang <davidm@hpl.hp.com>
 *	      Added INIT backtrace support.
 *
 * 2003-12-08 Keith Owens <kaos@sgi.com>
 *	      smp_call_function() must not be called from पूर्णांकerrupt context
 *	      (can deadlock on tasklist_lock).
 *	      Use keventd to call smp_call_function().
 *
 * 2004-02-01 Keith Owens <kaos@sgi.com>
 *	      Aव्योम deadlock when using prपूर्णांकk() क्रम MCA and INIT records.
 *	      Delete all record prपूर्णांकing code, moved to salinfo_decode in user
 *	      space.  Mark variables and functions अटल where possible.
 *	      Delete dead variables and functions.  Reorder to हटाओ the need
 *	      क्रम क्रमward declarations and to consolidate related code.
 *
 * 2005-08-12 Keith Owens <kaos@sgi.com>
 *	      Convert MCA/INIT handlers to use per event stacks and SAL/OS
 *	      state.
 *
 * 2005-10-07 Keith Owens <kaos@sgi.com>
 *	      Add notअगरy_die() hooks.
 *
 * 2006-09-15 Hidetoshi Seto <seto.hidetoshi@jp.fujitsu.com>
 *	      Add prपूर्णांकing support क्रम MCA/INIT.
 *
 * 2007-04-27 Russ Anderson <rja@sgi.com>
 *	      Support multiple cpus going through OS_MCA in the same event.
 */
#समावेश <linux/jअगरfies.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/memblock.h>
#समावेश <linux/acpi.h>
#समावेश <linux/समयr.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/smp.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/cpu.h>
#समावेश <linux/gfp.h>

#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/efi.h>
#समावेश <यंत्र/meminit.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/sal.h>
#समावेश <यंत्र/mca.h>
#समावेश <यंत्र/mca_यंत्र.h>
#समावेश <यंत्र/kexec.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/tlb.h>

#समावेश "mca_drv.h"
#समावेश "entry.h"
#समावेश "irq.h"

#अगर defined(IA64_MCA_DEBUG_INFO)
# define IA64_MCA_DEBUG(fmt...) prपूर्णांकk(fmt)
#अन्यथा
# define IA64_MCA_DEBUG(fmt...) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा NOTIFY_INIT(event, regs, arg, spin)				\
करो अणु									\
	अगर ((notअगरy_die((event), "INIT", (regs), (arg), 0, 0)		\
			== NOTIFY_STOP) && ((spin) == 1))		\
		ia64_mca_spin(__func__);				\
पूर्ण जबतक (0)

#घोषणा NOTIFY_MCA(event, regs, arg, spin)				\
करो अणु									\
	अगर ((notअगरy_die((event), "MCA", (regs), (arg), 0, 0)		\
			== NOTIFY_STOP) && ((spin) == 1))		\
		ia64_mca_spin(__func__);				\
पूर्ण जबतक (0)

/* Used by mca_यंत्र.S */
DEFINE_PER_CPU(u64, ia64_mca_data); /* == __per_cpu_mca[smp_processor_id()] */
DEFINE_PER_CPU(u64, ia64_mca_per_cpu_pte); /* PTE to map per-CPU area */
DEFINE_PER_CPU(u64, ia64_mca_pal_pte);	    /* PTE to map PAL code */
DEFINE_PER_CPU(u64, ia64_mca_pal_base);    /* vaddr PAL code granule */
DEFINE_PER_CPU(u64, ia64_mca_tr_reload);   /* Flag क्रम TR reload */

अचिन्हित दीर्घ __per_cpu_mca[NR_CPUS];

/* In mca_यंत्र.S */
बाह्य व्योम			ia64_os_init_dispatch_monarch (व्योम);
बाह्य व्योम			ia64_os_init_dispatch_slave (व्योम);

अटल पूर्णांक monarch_cpu = -1;

अटल ia64_mc_info_t		ia64_mc_info;

#घोषणा MAX_CPE_POLL_INTERVAL (15*60*HZ) /* 15 minutes */
#घोषणा MIN_CPE_POLL_INTERVAL (2*60*HZ)  /* 2 minutes */
#घोषणा CMC_POLL_INTERVAL     (1*60*HZ)  /* 1 minute */
#घोषणा CPE_HISTORY_LENGTH    5
#घोषणा CMC_HISTORY_LENGTH    5

अटल काष्ठा समयr_list cpe_poll_समयr;
अटल काष्ठा समयr_list cmc_poll_समयr;
/*
 * This variable tells whether we are currently in polling mode.
 * Start with this in the wrong state so we won't play w/ समयrs
 * beक्रमe the प्रणाली is पढ़ोy.
 */
अटल पूर्णांक cmc_polling_enabled = 1;

/*
 * Clearing this variable prevents CPE polling from getting activated
 * in mca_late_init.  Use it अगर your प्रणाली करोesn't provide a CPEI,
 * but encounters problems retrieving CPE logs.  This should only be
 * necessary क्रम debugging.
 */
अटल पूर्णांक cpe_poll_enabled = 1;

बाह्य व्योम salinfo_log_wakeup(पूर्णांक type, u8 *buffer, u64 size, पूर्णांक irqsafe);

अटल पूर्णांक mca_init __initdata;

/*
 * limited & delayed prपूर्णांकing support क्रम MCA/INIT handler
 */

#घोषणा mprपूर्णांकk(fmt...) ia64_mca_prपूर्णांकk(fmt)

#घोषणा MLOGBUF_SIZE (512+256*NR_CPUS)
#घोषणा MLOGBUF_MSGMAX 256
अटल अक्षर mlogbuf[MLOGBUF_SIZE];
अटल DEFINE_SPINLOCK(mlogbuf_wlock);	/* mca context only */
अटल DEFINE_SPINLOCK(mlogbuf_rlock);	/* normal context only */
अटल अचिन्हित दीर्घ mlogbuf_start;
अटल अचिन्हित दीर्घ mlogbuf_end;
अटल अचिन्हित पूर्णांक mlogbuf_finished = 0;
अटल अचिन्हित दीर्घ mlogbuf_बारtamp = 0;

अटल पूर्णांक loglevel_save = -1;
#घोषणा BREAK_LOGLEVEL(__console_loglevel)		\
	oops_in_progress = 1;				\
	अगर (loglevel_save < 0)				\
		loglevel_save = __console_loglevel;	\
	__console_loglevel = 15;

#घोषणा RESTORE_LOGLEVEL(__console_loglevel)		\
	अगर (loglevel_save >= 0) अणु			\
		__console_loglevel = loglevel_save;	\
		loglevel_save = -1;			\
	पूर्ण						\
	mlogbuf_finished = 0;				\
	oops_in_progress = 0;

/*
 * Push messages पूर्णांकo buffer, prपूर्णांक them later अगर not urgent.
 */
व्योम ia64_mca_prपूर्णांकk(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक prपूर्णांकed_len;
	अक्षर temp_buf[MLOGBUF_MSGMAX];
	अक्षर *p;

	बहु_शुरू(args, fmt);
	prपूर्णांकed_len = vscnम_लिखो(temp_buf, माप(temp_buf), fmt, args);
	बहु_पूर्ण(args);

	/* Copy the output पूर्णांकo mlogbuf */
	अगर (oops_in_progress) अणु
		/* mlogbuf was abanकरोned, use prपूर्णांकk directly instead. */
		prपूर्णांकk("%s", temp_buf);
	पूर्ण अन्यथा अणु
		spin_lock(&mlogbuf_wlock);
		क्रम (p = temp_buf; *p; p++) अणु
			अचिन्हित दीर्घ next = (mlogbuf_end + 1) % MLOGBUF_SIZE;
			अगर (next != mlogbuf_start) अणु
				mlogbuf[mlogbuf_end] = *p;
				mlogbuf_end = next;
			पूर्ण अन्यथा अणु
				/* buffer full */
				अवरोध;
			पूर्ण
		पूर्ण
		mlogbuf[mlogbuf_end] = '\0';
		spin_unlock(&mlogbuf_wlock);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ia64_mca_prपूर्णांकk);

/*
 * Prपूर्णांक buffered messages.
 *  NOTE: call this after वापसing normal context. (ex. from salinfod)
 */
व्योम ia64_mlogbuf_dump(व्योम)
अणु
	अक्षर temp_buf[MLOGBUF_MSGMAX];
	अक्षर *p;
	अचिन्हित दीर्घ index;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक prपूर्णांकed_len;

	/* Get output from mlogbuf */
	जबतक (mlogbuf_start != mlogbuf_end) अणु
		temp_buf[0] = '\0';
		p = temp_buf;
		prपूर्णांकed_len = 0;

		spin_lock_irqsave(&mlogbuf_rlock, flags);

		index = mlogbuf_start;
		जबतक (index != mlogbuf_end) अणु
			*p = mlogbuf[index];
			index = (index + 1) % MLOGBUF_SIZE;
			अगर (!*p)
				अवरोध;
			p++;
			अगर (++prपूर्णांकed_len >= MLOGBUF_MSGMAX - 1)
				अवरोध;
		पूर्ण
		*p = '\0';
		अगर (temp_buf[0])
			prपूर्णांकk("%s", temp_buf);
		mlogbuf_start = index;

		mlogbuf_बारtamp = 0;
		spin_unlock_irqrestore(&mlogbuf_rlock, flags);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ia64_mlogbuf_dump);

/*
 * Call this अगर प्रणाली is going to करोwn or अगर immediate flushing messages to
 * console is required. (ex. recovery was failed, crash dump is going to be
 * invoked, दीर्घ-रुको rendezvous etc.)
 *  NOTE: this should be called from monarch.
 */
अटल व्योम ia64_mlogbuf_finish(पूर्णांक रुको)
अणु
	BREAK_LOGLEVEL(console_loglevel);

	spin_lock_init(&mlogbuf_rlock);
	ia64_mlogbuf_dump();
	prपूर्णांकk(KERN_EMERG "mlogbuf_finish: printing switched to urgent mode, "
		"MCA/INIT might be dodgy or fail.\n");

	अगर (!रुको)
		वापस;

	/* रुको क्रम console */
	prपूर्णांकk("Delaying for 5 seconds...\n");
	udelay(5*1000000);

	mlogbuf_finished = 1;
पूर्ण

/*
 * Prपूर्णांक buffered messages from INIT context.
 */
अटल व्योम ia64_mlogbuf_dump_from_init(व्योम)
अणु
	अगर (mlogbuf_finished)
		वापस;

	अगर (mlogbuf_बारtamp &&
			समय_beक्रमe(jअगरfies, mlogbuf_बारtamp + 30 * HZ)) अणु
		prपूर्णांकk(KERN_ERR "INIT: mlogbuf_dump is interrupted by INIT "
			" and the system seems to be messed up.\n");
		ia64_mlogbuf_finish(0);
		वापस;
	पूर्ण

	अगर (!spin_trylock(&mlogbuf_rlock)) अणु
		prपूर्णांकk(KERN_ERR "INIT: mlogbuf_dump is interrupted by INIT. "
			"Generated messages other than stack dump will be "
			"buffered to mlogbuf and will be printed later.\n");
		prपूर्णांकk(KERN_ERR "INIT: If messages would not printed after "
			"this INIT, wait 30sec and assert INIT again.\n");
		अगर (!mlogbuf_बारtamp)
			mlogbuf_बारtamp = jअगरfies;
		वापस;
	पूर्ण
	spin_unlock(&mlogbuf_rlock);
	ia64_mlogbuf_dump();
पूर्ण

अटल अंतरभूत व्योम
ia64_mca_spin(स्थिर अक्षर *func)
अणु
	अगर (monarch_cpu == smp_processor_id())
		ia64_mlogbuf_finish(0);
	mprपूर्णांकk(KERN_EMERG "%s: spinning here, not returning to SAL\n", func);
	जबतक (1)
		cpu_relax();
पूर्ण
/*
 * IA64_MCA log support
 */
#घोषणा IA64_MAX_LOGS		2	/* Double-buffering क्रम nested MCAs */
#घोषणा IA64_MAX_LOG_TYPES      4   /* MCA, INIT, CMC, CPE */

प्रकार काष्ठा ia64_state_log_s
अणु
	spinlock_t	isl_lock;
	पूर्णांक		isl_index;
	अचिन्हित दीर्घ	isl_count;
	ia64_err_rec_t  *isl_log[IA64_MAX_LOGS]; /* need space to store header + error log */
पूर्ण ia64_state_log_t;

अटल ia64_state_log_t ia64_state_log[IA64_MAX_LOG_TYPES];

#घोषणा IA64_LOG_LOCK_INIT(it) spin_lock_init(&ia64_state_log[it].isl_lock)
#घोषणा IA64_LOG_LOCK(it)      spin_lock_irqsave(&ia64_state_log[it].isl_lock, s)
#घोषणा IA64_LOG_UNLOCK(it)    spin_unlock_irqrestore(&ia64_state_log[it].isl_lock,s)
#घोषणा IA64_LOG_NEXT_INDEX(it)    ia64_state_log[it].isl_index
#घोषणा IA64_LOG_CURR_INDEX(it)    1 - ia64_state_log[it].isl_index
#घोषणा IA64_LOG_INDEX_INC(it) \
    अणुia64_state_log[it].isl_index = 1 - ia64_state_log[it].isl_index; \
    ia64_state_log[it].isl_count++;पूर्ण
#घोषणा IA64_LOG_INDEX_DEC(it) \
    ia64_state_log[it].isl_index = 1 - ia64_state_log[it].isl_index
#घोषणा IA64_LOG_NEXT_BUFFER(it)   (व्योम *)((ia64_state_log[it].isl_log[IA64_LOG_NEXT_INDEX(it)]))
#घोषणा IA64_LOG_CURR_BUFFER(it)   (व्योम *)((ia64_state_log[it].isl_log[IA64_LOG_CURR_INDEX(it)]))
#घोषणा IA64_LOG_COUNT(it)         ia64_state_log[it].isl_count

अटल अंतरभूत व्योम ia64_log_allocate(पूर्णांक it, u64 size)
अणु
	ia64_state_log[it].isl_log[IA64_LOG_CURR_INDEX(it)] =
		(ia64_err_rec_t *)memblock_alloc(size, SMP_CACHE_BYTES);
	अगर (!ia64_state_log[it].isl_log[IA64_LOG_CURR_INDEX(it)])
		panic("%s: Failed to allocate %llu bytes\n", __func__, size);

	ia64_state_log[it].isl_log[IA64_LOG_NEXT_INDEX(it)] =
		(ia64_err_rec_t *)memblock_alloc(size, SMP_CACHE_BYTES);
	अगर (!ia64_state_log[it].isl_log[IA64_LOG_NEXT_INDEX(it)])
		panic("%s: Failed to allocate %llu bytes\n", __func__, size);
पूर्ण

/*
 * ia64_log_init
 *	Reset the OS ia64 log buffer
 * Inमाला_दो   :   info_type   (SAL_INFO_TYPE_अणुMCA,INIT,CMC,CPEपूर्ण)
 * Outमाला_दो	:	None
 */
अटल व्योम __init
ia64_log_init(पूर्णांक sal_info_type)
अणु
	u64	max_size = 0;

	IA64_LOG_NEXT_INDEX(sal_info_type) = 0;
	IA64_LOG_LOCK_INIT(sal_info_type);

	// SAL will tell us the maximum size of any error record of this type
	max_size = ia64_sal_get_state_info_size(sal_info_type);
	अगर (!max_size)
		/* alloc_booपंचांगem() करोesn't like zero-sized allocations! */
		वापस;

	// set up OS data काष्ठाures to hold error info
	ia64_log_allocate(sal_info_type, max_size);
पूर्ण

/*
 * ia64_log_get
 *
 *	Get the current MCA log from SAL and copy it पूर्णांकo the OS log buffer.
 *
 *  Inमाला_दो  :   info_type   (SAL_INFO_TYPE_अणुMCA,INIT,CMC,CPEपूर्ण)
 *              irq_safe    whether you can use prपूर्णांकk at this poपूर्णांक
 *  Outमाला_दो :   size        (total record length)
 *              *buffer     (ptr to error record)
 *
 */
अटल u64
ia64_log_get(पूर्णांक sal_info_type, u8 **buffer, पूर्णांक irq_safe)
अणु
	sal_log_record_header_t     *log_buffer;
	u64                         total_len = 0;
	अचिन्हित दीर्घ               s;

	IA64_LOG_LOCK(sal_info_type);

	/* Get the process state inक्रमmation */
	log_buffer = IA64_LOG_NEXT_BUFFER(sal_info_type);

	total_len = ia64_sal_get_state_info(sal_info_type, (u64 *)log_buffer);

	अगर (total_len) अणु
		IA64_LOG_INDEX_INC(sal_info_type);
		IA64_LOG_UNLOCK(sal_info_type);
		अगर (irq_safe) अणु
			IA64_MCA_DEBUG("%s: SAL error record type %d retrieved. Record length = %ld\n",
				       __func__, sal_info_type, total_len);
		पूर्ण
		*buffer = (u8 *) log_buffer;
		वापस total_len;
	पूर्ण अन्यथा अणु
		IA64_LOG_UNLOCK(sal_info_type);
		वापस 0;
	पूर्ण
पूर्ण

/*
 *  ia64_mca_log_sal_error_record
 *
 *  This function retrieves a specअगरied error record type from SAL
 *  and wakes up any processes रुकोing क्रम error records.
 *
 *  Inमाला_दो  :   sal_info_type   (Type of error record MCA/CMC/CPE)
 *              FIXME: हटाओ MCA and irq_safe.
 */
अटल व्योम
ia64_mca_log_sal_error_record(पूर्णांक sal_info_type)
अणु
	u8 *buffer;
	sal_log_record_header_t *rh;
	u64 size;
	पूर्णांक irq_safe = sal_info_type != SAL_INFO_TYPE_MCA;
#अगर_घोषित IA64_MCA_DEBUG_INFO
	अटल स्थिर अक्षर * स्थिर rec_name[] = अणु "MCA", "INIT", "CMC", "CPE" पूर्ण;
#पूर्ण_अगर

	size = ia64_log_get(sal_info_type, &buffer, irq_safe);
	अगर (!size)
		वापस;

	salinfo_log_wakeup(sal_info_type, buffer, size, irq_safe);

	अगर (irq_safe)
		IA64_MCA_DEBUG("CPU %d: SAL log contains %s error record\n",
			smp_processor_id(),
			sal_info_type < ARRAY_SIZE(rec_name) ? rec_name[sal_info_type] : "UNKNOWN");

	/* Clear logs from corrected errors in हाल there's no user-level logger */
	rh = (sal_log_record_header_t *)buffer;
	अगर (rh->severity == sal_log_severity_corrected)
		ia64_sal_clear_state_info(sal_info_type);
पूर्ण

/*
 * search_mca_table
 *  See अगर the MCA surfaced in an inकाष्ठाion range
 *  that has been tagged as recoverable.
 *
 *  Inमाला_दो
 *	first	First address range to check
 *	last	Last address range to check
 *	ip	Inकाष्ठाion poपूर्णांकer, address we are looking क्रम
 *
 * Return value:
 *      1 on Success (in the table)/ 0 on Failure (not in the  table)
 */
पूर्णांक
search_mca_table (स्थिर काष्ठा mca_table_entry *first,
                स्थिर काष्ठा mca_table_entry *last,
                अचिन्हित दीर्घ ip)
अणु
        स्थिर काष्ठा mca_table_entry *curr;
        u64 curr_start, curr_end;

        curr = first;
        जबतक (curr <= last) अणु
                curr_start = (u64) &curr->start_addr + curr->start_addr;
                curr_end = (u64) &curr->end_addr + curr->end_addr;

                अगर ((ip >= curr_start) && (ip <= curr_end)) अणु
                        वापस 1;
                पूर्ण
                curr++;
        पूर्ण
        वापस 0;
पूर्ण

/* Given an address, look क्रम it in the mca tables. */
पूर्णांक mca_recover_range(अचिन्हित दीर्घ addr)
अणु
	बाह्य काष्ठा mca_table_entry __start___mca_table[];
	बाह्य काष्ठा mca_table_entry __stop___mca_table[];

	वापस search_mca_table(__start___mca_table, __stop___mca_table-1, addr);
पूर्ण
EXPORT_SYMBOL_GPL(mca_recover_range);

पूर्णांक cpe_vector = -1;
पूर्णांक ia64_cpe_irq = -1;

अटल irqवापस_t
ia64_mca_cpe_पूर्णांक_handler (पूर्णांक cpe_irq, व्योम *arg)
अणु
	अटल अचिन्हित दीर्घ	cpe_history[CPE_HISTORY_LENGTH];
	अटल पूर्णांक		index;
	अटल DEFINE_SPINLOCK(cpe_history_lock);

	IA64_MCA_DEBUG("%s: received interrupt vector = %#x on CPU %d\n",
		       __func__, cpe_irq, smp_processor_id());

	/* SAL spec states this should run w/ पूर्णांकerrupts enabled */
	local_irq_enable();

	spin_lock(&cpe_history_lock);
	अगर (!cpe_poll_enabled && cpe_vector >= 0) अणु

		पूर्णांक i, count = 1; /* we know 1 happened now */
		अचिन्हित दीर्घ now = jअगरfies;

		क्रम (i = 0; i < CPE_HISTORY_LENGTH; i++) अणु
			अगर (now - cpe_history[i] <= HZ)
				count++;
		पूर्ण

		IA64_MCA_DEBUG(KERN_INFO "CPE threshold %d/%d\n", count, CPE_HISTORY_LENGTH);
		अगर (count >= CPE_HISTORY_LENGTH) अणु

			cpe_poll_enabled = 1;
			spin_unlock(&cpe_history_lock);
			disable_irq_nosync(local_vector_to_irq(IA64_CPE_VECTOR));

			/*
			 * Corrected errors will still be corrected, but
			 * make sure there's a log somewhere that indicates
			 * something is generating more than we can handle.
			 */
			prपूर्णांकk(KERN_WARNING "WARNING: Switching to polling CPE handler; error records may be lost\n");

			mod_समयr(&cpe_poll_समयr, jअगरfies + MIN_CPE_POLL_INTERVAL);

			/* lock alपढ़ोy released, get out now */
			जाओ out;
		पूर्ण अन्यथा अणु
			cpe_history[index++] = now;
			अगर (index == CPE_HISTORY_LENGTH)
				index = 0;
		पूर्ण
	पूर्ण
	spin_unlock(&cpe_history_lock);
out:
	/* Get the CPE error record and log it */
	ia64_mca_log_sal_error_record(SAL_INFO_TYPE_CPE);

	local_irq_disable();

	वापस IRQ_HANDLED;
पूर्ण

/*
 * ia64_mca_रेजिस्टर_cpev
 *
 *  Register the corrected platक्रमm error vector with SAL.
 *
 *  Inमाला_दो
 *      cpev        Corrected Platक्रमm Error Vector number
 *
 *  Outमाला_दो
 *      None
 */
व्योम
ia64_mca_रेजिस्टर_cpev (पूर्णांक cpev)
अणु
	/* Register the CPE पूर्णांकerrupt vector with SAL */
	काष्ठा ia64_sal_retval isrv;

	isrv = ia64_sal_mc_set_params(SAL_MC_PARAM_CPE_INT, SAL_MC_PARAM_MECHANISM_INT, cpev, 0, 0);
	अगर (isrv.status) अणु
		prपूर्णांकk(KERN_ERR "Failed to register Corrected Platform "
		       "Error interrupt vector with SAL (status %ld)\n", isrv.status);
		वापस;
	पूर्ण

	IA64_MCA_DEBUG("%s: corrected platform error "
		       "vector %#x registered\n", __func__, cpev);
पूर्ण

/*
 * ia64_mca_cmc_vector_setup
 *
 *  Setup the corrected machine check vector रेजिस्टर in the processor.
 *  (The पूर्णांकerrupt is masked on boot. ia64_mca_late_init unmask this.)
 *  This function is invoked on a per-processor basis.
 *
 * Inमाला_दो
 *      None
 *
 * Outमाला_दो
 *	None
 */
व्योम
ia64_mca_cmc_vector_setup (व्योम)
अणु
	cmcv_reg_t	cmcv;

	cmcv.cmcv_regval	= 0;
	cmcv.cmcv_mask		= 1;        /* Mask/disable पूर्णांकerrupt at first */
	cmcv.cmcv_vector	= IA64_CMC_VECTOR;
	ia64_setreg(_IA64_REG_CR_CMCV, cmcv.cmcv_regval);

	IA64_MCA_DEBUG("%s: CPU %d corrected machine check vector %#x registered.\n",
		       __func__, smp_processor_id(), IA64_CMC_VECTOR);

	IA64_MCA_DEBUG("%s: CPU %d CMCV = %#016lx\n",
		       __func__, smp_processor_id(), ia64_getreg(_IA64_REG_CR_CMCV));
पूर्ण

/*
 * ia64_mca_cmc_vector_disable
 *
 *  Mask the corrected machine check vector रेजिस्टर in the processor.
 *  This function is invoked on a per-processor basis.
 *
 * Inमाला_दो
 *      dummy(unused)
 *
 * Outमाला_दो
 *	None
 */
अटल व्योम
ia64_mca_cmc_vector_disable (व्योम *dummy)
अणु
	cmcv_reg_t	cmcv;

	cmcv.cmcv_regval = ia64_getreg(_IA64_REG_CR_CMCV);

	cmcv.cmcv_mask = 1; /* Mask/disable पूर्णांकerrupt */
	ia64_setreg(_IA64_REG_CR_CMCV, cmcv.cmcv_regval);

	IA64_MCA_DEBUG("%s: CPU %d corrected machine check vector %#x disabled.\n",
		       __func__, smp_processor_id(), cmcv.cmcv_vector);
पूर्ण

/*
 * ia64_mca_cmc_vector_enable
 *
 *  Unmask the corrected machine check vector रेजिस्टर in the processor.
 *  This function is invoked on a per-processor basis.
 *
 * Inमाला_दो
 *      dummy(unused)
 *
 * Outमाला_दो
 *	None
 */
अटल व्योम
ia64_mca_cmc_vector_enable (व्योम *dummy)
अणु
	cmcv_reg_t	cmcv;

	cmcv.cmcv_regval = ia64_getreg(_IA64_REG_CR_CMCV);

	cmcv.cmcv_mask = 0; /* Unmask/enable पूर्णांकerrupt */
	ia64_setreg(_IA64_REG_CR_CMCV, cmcv.cmcv_regval);

	IA64_MCA_DEBUG("%s: CPU %d corrected machine check vector %#x enabled.\n",
		       __func__, smp_processor_id(), cmcv.cmcv_vector);
पूर्ण

/*
 * ia64_mca_cmc_vector_disable_keventd
 *
 * Called via keventd (smp_call_function() is not safe in पूर्णांकerrupt context) to
 * disable the cmc पूर्णांकerrupt vector.
 */
अटल व्योम
ia64_mca_cmc_vector_disable_keventd(काष्ठा work_काष्ठा *unused)
अणु
	on_each_cpu(ia64_mca_cmc_vector_disable, शून्य, 0);
पूर्ण

/*
 * ia64_mca_cmc_vector_enable_keventd
 *
 * Called via keventd (smp_call_function() is not safe in पूर्णांकerrupt context) to
 * enable the cmc पूर्णांकerrupt vector.
 */
अटल व्योम
ia64_mca_cmc_vector_enable_keventd(काष्ठा work_काष्ठा *unused)
अणु
	on_each_cpu(ia64_mca_cmc_vector_enable, शून्य, 0);
पूर्ण

/*
 * ia64_mca_wakeup
 *
 *	Send an पूर्णांकer-cpu पूर्णांकerrupt to wake-up a particular cpu.
 *
 *  Inमाला_दो  :   cpuid
 *  Outमाला_दो :   None
 */
अटल व्योम
ia64_mca_wakeup(पूर्णांक cpu)
अणु
	ia64_send_ipi(cpu, IA64_MCA_WAKEUP_VECTOR, IA64_IPI_DM_INT, 0);
पूर्ण

/*
 * ia64_mca_wakeup_all
 *
 *	Wakeup all the slave cpus which have rendez'ed previously.
 *
 *  Inमाला_दो  :   None
 *  Outमाला_दो :   None
 */
अटल व्योम
ia64_mca_wakeup_all(व्योम)
अणु
	पूर्णांक cpu;

	/* Clear the Rendez checkin flag क्रम all cpus */
	क्रम_each_online_cpu(cpu) अणु
		अगर (ia64_mc_info.imi_rendez_checkin[cpu] == IA64_MCA_RENDEZ_CHECKIN_DONE)
			ia64_mca_wakeup(cpu);
	पूर्ण

पूर्ण

/*
 * ia64_mca_rendez_पूर्णांकerrupt_handler
 *
 *	This is handler used to put slave processors पूर्णांकo spinloop
 *	जबतक the monarch processor करोes the mca handling and later
 *	wake each slave up once the monarch is करोne.  The state
 *	IA64_MCA_RENDEZ_CHECKIN_DONE indicates the cpu is rendez'ed
 *	in SAL.  The state IA64_MCA_RENDEZ_CHECKIN_NOTDONE indicates
 *	the cpu has come out of OS rendezvous.
 *
 *  Inमाला_दो  :   None
 *  Outमाला_दो :   None
 */
अटल irqवापस_t
ia64_mca_rendez_पूर्णांक_handler(पूर्णांक rendez_irq, व्योम *arg)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक cpu = smp_processor_id();
	काष्ठा ia64_mca_notअगरy_die nd =
		अणु .sos = शून्य, .monarch_cpu = &monarch_cpu पूर्ण;

	/* Mask all पूर्णांकerrupts */
	local_irq_save(flags);

	NOTIFY_MCA(DIE_MCA_RENDZVOUS_ENTER, get_irq_regs(), (दीर्घ)&nd, 1);

	ia64_mc_info.imi_rendez_checkin[cpu] = IA64_MCA_RENDEZ_CHECKIN_DONE;
	/* Register with the SAL monarch that the slave has
	 * reached SAL
	 */
	ia64_sal_mc_rendez();

	NOTIFY_MCA(DIE_MCA_RENDZVOUS_PROCESS, get_irq_regs(), (दीर्घ)&nd, 1);

	/* Wait क्रम the monarch cpu to निकास. */
	जबतक (monarch_cpu != -1)
	       cpu_relax();	/* spin until monarch leaves */

	NOTIFY_MCA(DIE_MCA_RENDZVOUS_LEAVE, get_irq_regs(), (दीर्घ)&nd, 1);

	ia64_mc_info.imi_rendez_checkin[cpu] = IA64_MCA_RENDEZ_CHECKIN_NOTDONE;
	/* Enable all पूर्णांकerrupts */
	local_irq_restore(flags);
	वापस IRQ_HANDLED;
पूर्ण

/*
 * ia64_mca_wakeup_पूर्णांक_handler
 *
 *	The पूर्णांकerrupt handler क्रम processing the पूर्णांकer-cpu पूर्णांकerrupt to the
 *	slave cpu which was spinning in the rendez loop.
 *	Since this spinning is करोne by turning off the पूर्णांकerrupts and
 *	polling on the wakeup-पूर्णांकerrupt bit in the IRR, there is
 *	nothing useful to be करोne in the handler.
 *
 *  Inमाला_दो  :   wakeup_irq  (Wakeup-पूर्णांकerrupt bit)
 *	arg		(Interrupt handler specअगरic argument)
 *  Outमाला_दो :   None
 *
 */
अटल irqवापस_t
ia64_mca_wakeup_पूर्णांक_handler(पूर्णांक wakeup_irq, व्योम *arg)
अणु
	वापस IRQ_HANDLED;
पूर्ण

/* Function poपूर्णांकer क्रम extra MCA recovery */
पूर्णांक (*ia64_mca_ucmc_extension)
	(व्योम*,काष्ठा ia64_sal_os_state*)
	= शून्य;

पूर्णांक
ia64_reg_MCA_extension(पूर्णांक (*fn)(व्योम *, काष्ठा ia64_sal_os_state *))
अणु
	अगर (ia64_mca_ucmc_extension)
		वापस 1;

	ia64_mca_ucmc_extension = fn;
	वापस 0;
पूर्ण

व्योम
ia64_unreg_MCA_extension(व्योम)
अणु
	अगर (ia64_mca_ucmc_extension)
		ia64_mca_ucmc_extension = शून्य;
पूर्ण

EXPORT_SYMBOL(ia64_reg_MCA_extension);
EXPORT_SYMBOL(ia64_unreg_MCA_extension);


अटल अंतरभूत व्योम
copy_reg(स्थिर u64 *fr, u64 fnat, अचिन्हित दीर्घ *tr, अचिन्हित दीर्घ *tnat)
अणु
	u64 fslot, tslot, nat;
	*tr = *fr;
	fslot = ((अचिन्हित दीर्घ)fr >> 3) & 63;
	tslot = ((अचिन्हित दीर्घ)tr >> 3) & 63;
	*tnat &= ~(1UL << tslot);
	nat = (fnat >> fslot) & 1;
	*tnat |= (nat << tslot);
पूर्ण

/* Change the comm field on the MCA/INT task to include the pid that
 * was पूर्णांकerrupted, it makes क्रम easier debugging.  If that pid was 0
 * (swapper or nested MCA/INIT) then use the start of the previous comm
 * field suffixed with its cpu.
 */

अटल व्योम
ia64_mca_modअगरy_comm(स्थिर काष्ठा task_काष्ठा *previous_current)
अणु
	अक्षर *p, comm[माप(current->comm)];
	अगर (previous_current->pid)
		snम_लिखो(comm, माप(comm), "%s %d",
			current->comm, previous_current->pid);
	अन्यथा अणु
		पूर्णांक l;
		अगर ((p = म_अक्षर(previous_current->comm, ' ')))
			l = p - previous_current->comm;
		अन्यथा
			l = म_माप(previous_current->comm);
		snम_लिखो(comm, माप(comm), "%s %*s %d",
			current->comm, l, previous_current->comm,
			task_thपढ़ो_info(previous_current)->cpu);
	पूर्ण
	स_नकल(current->comm, comm, माप(current->comm));
पूर्ण

अटल व्योम
finish_pt_regs(काष्ठा pt_regs *regs, काष्ठा ia64_sal_os_state *sos,
		अचिन्हित दीर्घ *nat)
अणु
	स्थिर काष्ठा pal_min_state_area *ms = sos->pal_min_state;
	स्थिर u64 *bank;

	/* If ipsr.ic then use pmsa_अणुiip,ipsr,अगरsपूर्ण, अन्यथा use
	 * pmsa_अणुxip,xpsr,xfsपूर्ण
	 */
	अगर (ia64_psr(regs)->ic) अणु
		regs->cr_iip = ms->pmsa_iip;
		regs->cr_ipsr = ms->pmsa_ipsr;
		regs->cr_अगरs = ms->pmsa_अगरs;
	पूर्ण अन्यथा अणु
		regs->cr_iip = ms->pmsa_xip;
		regs->cr_ipsr = ms->pmsa_xpsr;
		regs->cr_अगरs = ms->pmsa_xfs;

		sos->iip = ms->pmsa_iip;
		sos->ipsr = ms->pmsa_ipsr;
		sos->अगरs = ms->pmsa_अगरs;
	पूर्ण
	regs->pr = ms->pmsa_pr;
	regs->b0 = ms->pmsa_br0;
	regs->ar_rsc = ms->pmsa_rsc;
	copy_reg(&ms->pmsa_gr[1-1], ms->pmsa_nat_bits, &regs->r1, nat);
	copy_reg(&ms->pmsa_gr[2-1], ms->pmsa_nat_bits, &regs->r2, nat);
	copy_reg(&ms->pmsa_gr[3-1], ms->pmsa_nat_bits, &regs->r3, nat);
	copy_reg(&ms->pmsa_gr[8-1], ms->pmsa_nat_bits, &regs->r8, nat);
	copy_reg(&ms->pmsa_gr[9-1], ms->pmsa_nat_bits, &regs->r9, nat);
	copy_reg(&ms->pmsa_gr[10-1], ms->pmsa_nat_bits, &regs->r10, nat);
	copy_reg(&ms->pmsa_gr[11-1], ms->pmsa_nat_bits, &regs->r11, nat);
	copy_reg(&ms->pmsa_gr[12-1], ms->pmsa_nat_bits, &regs->r12, nat);
	copy_reg(&ms->pmsa_gr[13-1], ms->pmsa_nat_bits, &regs->r13, nat);
	copy_reg(&ms->pmsa_gr[14-1], ms->pmsa_nat_bits, &regs->r14, nat);
	copy_reg(&ms->pmsa_gr[15-1], ms->pmsa_nat_bits, &regs->r15, nat);
	अगर (ia64_psr(regs)->bn)
		bank = ms->pmsa_bank1_gr;
	अन्यथा
		bank = ms->pmsa_bank0_gr;
	copy_reg(&bank[16-16], ms->pmsa_nat_bits, &regs->r16, nat);
	copy_reg(&bank[17-16], ms->pmsa_nat_bits, &regs->r17, nat);
	copy_reg(&bank[18-16], ms->pmsa_nat_bits, &regs->r18, nat);
	copy_reg(&bank[19-16], ms->pmsa_nat_bits, &regs->r19, nat);
	copy_reg(&bank[20-16], ms->pmsa_nat_bits, &regs->r20, nat);
	copy_reg(&bank[21-16], ms->pmsa_nat_bits, &regs->r21, nat);
	copy_reg(&bank[22-16], ms->pmsa_nat_bits, &regs->r22, nat);
	copy_reg(&bank[23-16], ms->pmsa_nat_bits, &regs->r23, nat);
	copy_reg(&bank[24-16], ms->pmsa_nat_bits, &regs->r24, nat);
	copy_reg(&bank[25-16], ms->pmsa_nat_bits, &regs->r25, nat);
	copy_reg(&bank[26-16], ms->pmsa_nat_bits, &regs->r26, nat);
	copy_reg(&bank[27-16], ms->pmsa_nat_bits, &regs->r27, nat);
	copy_reg(&bank[28-16], ms->pmsa_nat_bits, &regs->r28, nat);
	copy_reg(&bank[29-16], ms->pmsa_nat_bits, &regs->r29, nat);
	copy_reg(&bank[30-16], ms->pmsa_nat_bits, &regs->r30, nat);
	copy_reg(&bank[31-16], ms->pmsa_nat_bits, &regs->r31, nat);
पूर्ण

/* On entry to this routine, we are running on the per cpu stack, see
 * mca_यंत्र.h.  The original stack has not been touched by this event.  Some of
 * the original stack's रेजिस्टरs will be in the RBS on this stack.  This stack
 * also contains a partial pt_regs and चयन_stack, the rest of the data is in
 * PAL minstate.
 *
 * The first thing to करो is modअगरy the original stack to look like a blocked
 * task so we can run backtrace on the original task.  Also mark the per cpu
 * stack as current to ensure that we use the correct task state, it also means
 * that we can करो backtrace on the MCA/INIT handler code itself.
 */

अटल काष्ठा task_काष्ठा *
ia64_mca_modअगरy_original_stack(काष्ठा pt_regs *regs,
		स्थिर काष्ठा चयन_stack *sw,
		काष्ठा ia64_sal_os_state *sos,
		स्थिर अक्षर *type)
अणु
	अक्षर *p;
	ia64_va va;
	बाह्य अक्षर ia64_leave_kernel[];	/* Need यंत्र address, not function descriptor */
	स्थिर काष्ठा pal_min_state_area *ms = sos->pal_min_state;
	काष्ठा task_काष्ठा *previous_current;
	काष्ठा pt_regs *old_regs;
	काष्ठा चयन_stack *old_sw;
	अचिन्हित size = माप(काष्ठा pt_regs) +
			माप(काष्ठा चयन_stack) + 16;
	अचिन्हित दीर्घ *old_bspstore, *old_bsp;
	अचिन्हित दीर्घ *new_bspstore, *new_bsp;
	अचिन्हित दीर्घ old_unat, old_rnat, new_rnat, nat;
	u64 slots, loadrs = regs->loadrs;
	u64 r12 = ms->pmsa_gr[12-1], r13 = ms->pmsa_gr[13-1];
	u64 ar_bspstore = regs->ar_bspstore;
	u64 ar_bsp = regs->ar_bspstore + (loadrs >> 16);
	स्थिर अक्षर *msg;
	पूर्णांक cpu = smp_processor_id();

	previous_current = curr_task(cpu);
	ia64_set_curr_task(cpu, current);
	अगर ((p = म_अक्षर(current->comm, ' ')))
		*p = '\0';

	/* Best efक्रमt attempt to cope with MCA/INIT delivered जबतक in
	 * physical mode.
	 */
	regs->cr_ipsr = ms->pmsa_ipsr;
	अगर (ia64_psr(regs)->dt == 0) अणु
		va.l = r12;
		अगर (va.f.reg == 0) अणु
			va.f.reg = 7;
			r12 = va.l;
		पूर्ण
		va.l = r13;
		अगर (va.f.reg == 0) अणु
			va.f.reg = 7;
			r13 = va.l;
		पूर्ण
	पूर्ण
	अगर (ia64_psr(regs)->rt == 0) अणु
		va.l = ar_bspstore;
		अगर (va.f.reg == 0) अणु
			va.f.reg = 7;
			ar_bspstore = va.l;
		पूर्ण
		va.l = ar_bsp;
		अगर (va.f.reg == 0) अणु
			va.f.reg = 7;
			ar_bsp = va.l;
		पूर्ण
	पूर्ण

	/* mca_यंत्र.S ia64_old_stack() cannot assume that the dirty रेजिस्टरs
	 * have been copied to the old stack, the old stack may fail the
	 * validation tests below.  So ia64_old_stack() must restore the dirty
	 * रेजिस्टरs from the new stack.  The old and new bspstore probably
	 * have dअगरferent alignments, so loadrs calculated on the old bsp
	 * cannot be used to restore from the new bsp.  Calculate a suitable
	 * loadrs क्रम the new stack and save it in the new pt_regs, where
	 * ia64_old_stack() can get it.
	 */
	old_bspstore = (अचिन्हित दीर्घ *)ar_bspstore;
	old_bsp = (अचिन्हित दीर्घ *)ar_bsp;
	slots = ia64_rse_num_regs(old_bspstore, old_bsp);
	new_bspstore = (अचिन्हित दीर्घ *)((u64)current + IA64_RBS_OFFSET);
	new_bsp = ia64_rse_skip_regs(new_bspstore, slots);
	regs->loadrs = (new_bsp - new_bspstore) * 8 << 16;

	/* Verअगरy the previous stack state beक्रमe we change it */
	अगर (user_mode(regs)) अणु
		msg = "occurred in user space";
		/* previous_current is guaranteed to be valid when the task was
		 * in user space, so ...
		 */
		ia64_mca_modअगरy_comm(previous_current);
		जाओ no_mod;
	पूर्ण

	अगर (r13 != sos->prev_IA64_KR_CURRENT) अणु
		msg = "inconsistent previous current and r13";
		जाओ no_mod;
	पूर्ण

	अगर (!mca_recover_range(ms->pmsa_iip)) अणु
		अगर ((r12 - r13) >= KERNEL_STACK_SIZE) अणु
			msg = "inconsistent r12 and r13";
			जाओ no_mod;
		पूर्ण
		अगर ((ar_bspstore - r13) >= KERNEL_STACK_SIZE) अणु
			msg = "inconsistent ar.bspstore and r13";
			जाओ no_mod;
		पूर्ण
		va.p = old_bspstore;
		अगर (va.f.reg < 5) अणु
			msg = "old_bspstore is in the wrong region";
			जाओ no_mod;
		पूर्ण
		अगर ((ar_bsp - r13) >= KERNEL_STACK_SIZE) अणु
			msg = "inconsistent ar.bsp and r13";
			जाओ no_mod;
		पूर्ण
		size += (ia64_rse_skip_regs(old_bspstore, slots) - old_bspstore) * 8;
		अगर (ar_bspstore + size > r12) अणु
			msg = "no room for blocked state";
			जाओ no_mod;
		पूर्ण
	पूर्ण

	ia64_mca_modअगरy_comm(previous_current);

	/* Make the original task look blocked.  First stack a काष्ठा pt_regs,
	 * describing the state at the समय of पूर्णांकerrupt.  mca_यंत्र.S built a
	 * partial pt_regs, copy it and fill in the blanks using minstate.
	 */
	p = (अक्षर *)r12 - माप(*regs);
	old_regs = (काष्ठा pt_regs *)p;
	स_नकल(old_regs, regs, माप(*regs));
	old_regs->loadrs = loadrs;
	old_unat = old_regs->ar_unat;
	finish_pt_regs(old_regs, sos, &old_unat);

	/* Next stack a काष्ठा चयन_stack.  mca_यंत्र.S built a partial
	 * चयन_stack, copy it and fill in the blanks using pt_regs and
	 * minstate.
	 *
	 * In the synthesized चयन_stack, b0 poपूर्णांकs to ia64_leave_kernel,
	 * ar.pfs is set to 0.
	 *
	 * unwind.c::unw_unwind() करोes special processing क्रम पूर्णांकerrupt frames.
	 * It checks अगर the PRED_NON_SYSCALL predicate is set, अगर the predicate
	 * is clear then unw_unwind() करोes _not_ adjust bsp over pt_regs.  Not
	 * that this is करोcumented, of course.  Set PRED_NON_SYSCALL in the
	 * चयन_stack on the original stack so it will unwind correctly when
	 * unwind.c पढ़ोs pt_regs.
	 *
	 * thपढ़ो.ksp is updated to poपूर्णांक to the synthesized चयन_stack.
	 */
	p -= माप(काष्ठा चयन_stack);
	old_sw = (काष्ठा चयन_stack *)p;
	स_नकल(old_sw, sw, माप(*sw));
	old_sw->caller_unat = old_unat;
	old_sw->ar_fpsr = old_regs->ar_fpsr;
	copy_reg(&ms->pmsa_gr[4-1], ms->pmsa_nat_bits, &old_sw->r4, &old_unat);
	copy_reg(&ms->pmsa_gr[5-1], ms->pmsa_nat_bits, &old_sw->r5, &old_unat);
	copy_reg(&ms->pmsa_gr[6-1], ms->pmsa_nat_bits, &old_sw->r6, &old_unat);
	copy_reg(&ms->pmsa_gr[7-1], ms->pmsa_nat_bits, &old_sw->r7, &old_unat);
	old_sw->b0 = (u64)ia64_leave_kernel;
	old_sw->b1 = ms->pmsa_br1;
	old_sw->ar_pfs = 0;
	old_sw->ar_unat = old_unat;
	old_sw->pr = old_regs->pr | (1UL << PRED_NON_SYSCALL);
	previous_current->thपढ़ो.ksp = (u64)p - 16;

	/* Finally copy the original stack's रेजिस्टरs back to its RBS.
	 * Registers from ar.bspstore through ar.bsp at the समय of the event
	 * are in the current RBS, copy them back to the original stack.  The
	 * copy must be करोne रेजिस्टर by रेजिस्टर because the original bspstore
	 * and the current one have dअगरferent alignments, so the saved RNAT
	 * data occurs at dअगरferent places.
	 *
	 * mca_यंत्र करोes cover, so the old_bsp alपढ़ोy includes all रेजिस्टरs at
	 * the समय of MCA/INIT.  It also करोes flushrs, so all रेजिस्टरs beक्रमe
	 * this function have been written to backing store on the MCA/INIT
	 * stack.
	 */
	new_rnat = ia64_get_rnat(ia64_rse_rnat_addr(new_bspstore));
	old_rnat = regs->ar_rnat;
	जबतक (slots--) अणु
		अगर (ia64_rse_is_rnat_slot(new_bspstore)) अणु
			new_rnat = ia64_get_rnat(new_bspstore++);
		पूर्ण
		अगर (ia64_rse_is_rnat_slot(old_bspstore)) अणु
			*old_bspstore++ = old_rnat;
			old_rnat = 0;
		पूर्ण
		nat = (new_rnat >> ia64_rse_slot_num(new_bspstore)) & 1UL;
		old_rnat &= ~(1UL << ia64_rse_slot_num(old_bspstore));
		old_rnat |= (nat << ia64_rse_slot_num(old_bspstore));
		*old_bspstore++ = *new_bspstore++;
	पूर्ण
	old_sw->ar_bspstore = (अचिन्हित दीर्घ)old_bspstore;
	old_sw->ar_rnat = old_rnat;

	sos->prev_task = previous_current;
	वापस previous_current;

no_mod:
	mprपूर्णांकk(KERN_INFO "cpu %d, %s %s, original stack not modified\n",
			smp_processor_id(), type, msg);
	old_unat = regs->ar_unat;
	finish_pt_regs(regs, sos, &old_unat);
	वापस previous_current;
पूर्ण

/* The monarch/slave पूर्णांकeraction is based on monarch_cpu and requires that all
 * slaves have entered rendezvous beक्रमe the monarch leaves.  If any cpu has
 * not entered rendezvous yet then रुको a bit.  The assumption is that any
 * slave that has not rendezvoused after a reasonable समय is never going to करो
 * so.  In this context, slave includes cpus that respond to the MCA rendezvous
 * पूर्णांकerrupt, as well as cpus that receive the INIT slave event.
 */

अटल व्योम
ia64_रुको_क्रम_slaves(पूर्णांक monarch, स्थिर अक्षर *type)
अणु
	पूर्णांक c, i , रुको;

	/*
	 * रुको 5 seconds total क्रम slaves (arbitrary)
	 */
	क्रम (i = 0; i < 5000; i++) अणु
		रुको = 0;
		क्रम_each_online_cpu(c) अणु
			अगर (c == monarch)
				जारी;
			अगर (ia64_mc_info.imi_rendez_checkin[c]
					== IA64_MCA_RENDEZ_CHECKIN_NOTDONE) अणु
				udelay(1000);		/* लघु रुको */
				रुको = 1;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!रुको)
			जाओ all_in;
	पूर्ण

	/*
	 * Maybe slave(s) dead. Prपूर्णांक buffered messages immediately.
	 */
	ia64_mlogbuf_finish(0);
	mprपूर्णांकk(KERN_INFO "OS %s slave did not rendezvous on cpu", type);
	क्रम_each_online_cpu(c) अणु
		अगर (c == monarch)
			जारी;
		अगर (ia64_mc_info.imi_rendez_checkin[c] == IA64_MCA_RENDEZ_CHECKIN_NOTDONE)
			mprपूर्णांकk(" %d", c);
	पूर्ण
	mprपूर्णांकk("\n");
	वापस;

all_in:
	mprपूर्णांकk(KERN_INFO "All OS %s slaves have reached rendezvous\n", type);
	वापस;
पूर्ण

/*  mca_insert_tr
 *
 *  Switch rid when TR reload and needed!
 *  iord: 1: itr, 2: itr;
 *
*/
अटल व्योम mca_insert_tr(u64 iord)
अणु

	पूर्णांक i;
	u64 old_rr;
	काष्ठा ia64_tr_entry *p;
	अचिन्हित दीर्घ psr;
	पूर्णांक cpu = smp_processor_id();

	अगर (!ia64_idtrs[cpu])
		वापस;

	psr = ia64_clear_ic();
	क्रम (i = IA64_TR_ALLOC_BASE; i < IA64_TR_ALLOC_MAX; i++) अणु
		p = ia64_idtrs[cpu] + (iord - 1) * IA64_TR_ALLOC_MAX;
		अगर (p->pte & 0x1) अणु
			old_rr = ia64_get_rr(p->अगरa);
			अगर (old_rr != p->rr) अणु
				ia64_set_rr(p->अगरa, p->rr);
				ia64_srlz_d();
			पूर्ण
			ia64_ptr(iord, p->अगरa, p->itir >> 2);
			ia64_srlz_i();
			अगर (iord & 0x1) अणु
				ia64_itr(0x1, i, p->अगरa, p->pte, p->itir >> 2);
				ia64_srlz_i();
			पूर्ण
			अगर (iord & 0x2) अणु
				ia64_itr(0x2, i, p->अगरa, p->pte, p->itir >> 2);
				ia64_srlz_i();
			पूर्ण
			अगर (old_rr != p->rr) अणु
				ia64_set_rr(p->अगरa, old_rr);
				ia64_srlz_d();
			पूर्ण
		पूर्ण
	पूर्ण
	ia64_set_psr(psr);
पूर्ण

/*
 * ia64_mca_handler
 *
 *	This is uncorrectable machine check handler called from OS_MCA
 *	dispatch code which is in turn called from SAL_CHECK().
 *	This is the place where the core of OS MCA handling is करोne.
 *	Right now the logs are extracted and displayed in a well-defined
 *	क्रमmat. This handler code is supposed to be run only on the
 *	monarch processor. Once the monarch is करोne with MCA handling
 *	further MCA logging is enabled by clearing logs.
 *	Monarch also has the duty of sending wakeup-IPIs to pull the
 *	slave processors out of rendezvous spinloop.
 *
 *	If multiple processors call पूर्णांकo OS_MCA, the first will become
 *	the monarch.  Subsequent cpus will be recorded in the mca_cpu
 *	biपंचांगask.  After the first monarch has processed its MCA, it
 *	will wake up the next cpu in the mca_cpu biपंचांगask and then go
 *	पूर्णांकo the rendezvous loop.  When all processors have serviced
 *	their MCA, the last monarch मुक्तs up the rest of the processors.
 */
व्योम
ia64_mca_handler(काष्ठा pt_regs *regs, काष्ठा चयन_stack *sw,
		 काष्ठा ia64_sal_os_state *sos)
अणु
	पूर्णांक recover, cpu = smp_processor_id();
	काष्ठा task_काष्ठा *previous_current;
	काष्ठा ia64_mca_notअगरy_die nd =
		अणु .sos = sos, .monarch_cpu = &monarch_cpu, .data = &recover पूर्ण;
	अटल atomic_t mca_count;
	अटल cpumask_t mca_cpu;

	अगर (atomic_add_वापस(1, &mca_count) == 1) अणु
		monarch_cpu = cpu;
		sos->monarch = 1;
	पूर्ण अन्यथा अणु
		cpumask_set_cpu(cpu, &mca_cpu);
		sos->monarch = 0;
	पूर्ण
	mprपूर्णांकk(KERN_INFO "Entered OS MCA handler. PSP=%lx cpu=%d "
		"monarch=%ld\n", sos->proc_state_param, cpu, sos->monarch);

	previous_current = ia64_mca_modअगरy_original_stack(regs, sw, sos, "MCA");

	NOTIFY_MCA(DIE_MCA_MONARCH_ENTER, regs, (दीर्घ)&nd, 1);

	ia64_mc_info.imi_rendez_checkin[cpu] = IA64_MCA_RENDEZ_CHECKIN_CONCURRENT_MCA;
	अगर (sos->monarch) अणु
		ia64_रुको_क्रम_slaves(cpu, "MCA");

		/* Wakeup all the processors which are spinning in the
		 * rendezvous loop.  They will leave SAL, then spin in the OS
		 * with पूर्णांकerrupts disabled until this monarch cpu leaves the
		 * MCA handler.  That माला_लो control back to the OS so we can
		 * backtrace the other cpus, backtrace when spinning in SAL
		 * करोes not work.
		 */
		ia64_mca_wakeup_all();
	पूर्ण अन्यथा अणु
		जबतक (cpumask_test_cpu(cpu, &mca_cpu))
			cpu_relax();	/* spin until monarch wakes us */
	पूर्ण

	NOTIFY_MCA(DIE_MCA_MONARCH_PROCESS, regs, (दीर्घ)&nd, 1);

	/* Get the MCA error record and log it */
	ia64_mca_log_sal_error_record(SAL_INFO_TYPE_MCA);

	/* MCA error recovery */
	recover = (ia64_mca_ucmc_extension
		&& ia64_mca_ucmc_extension(
			IA64_LOG_CURR_BUFFER(SAL_INFO_TYPE_MCA),
			sos));

	अगर (recover) अणु
		sal_log_record_header_t *rh = IA64_LOG_CURR_BUFFER(SAL_INFO_TYPE_MCA);
		rh->severity = sal_log_severity_corrected;
		ia64_sal_clear_state_info(SAL_INFO_TYPE_MCA);
		sos->os_status = IA64_MCA_CORRECTED;
	पूर्ण अन्यथा अणु
		/* Dump buffered message to console */
		ia64_mlogbuf_finish(1);
	पूर्ण

	अगर (__this_cpu_पढ़ो(ia64_mca_tr_reload)) अणु
		mca_insert_tr(0x1); /*Reload dynamic itrs*/
		mca_insert_tr(0x2); /*Reload dynamic itrs*/
	पूर्ण

	NOTIFY_MCA(DIE_MCA_MONARCH_LEAVE, regs, (दीर्घ)&nd, 1);

	अगर (atomic_dec_वापस(&mca_count) > 0) अणु
		पूर्णांक i;

		/* wake up the next monarch cpu,
		 * and put this cpu in the rendez loop.
		 */
		क्रम_each_online_cpu(i) अणु
			अगर (cpumask_test_cpu(i, &mca_cpu)) अणु
				monarch_cpu = i;
				cpumask_clear_cpu(i, &mca_cpu);	/* wake next cpu */
				जबतक (monarch_cpu != -1)
					cpu_relax();	/* spin until last cpu leaves */
				ia64_set_curr_task(cpu, previous_current);
				ia64_mc_info.imi_rendez_checkin[cpu]
						= IA64_MCA_RENDEZ_CHECKIN_NOTDONE;
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण
	ia64_set_curr_task(cpu, previous_current);
	ia64_mc_info.imi_rendez_checkin[cpu] = IA64_MCA_RENDEZ_CHECKIN_NOTDONE;
	monarch_cpu = -1;	/* This मुक्तs the slaves and previous monarchs */
पूर्ण

अटल DECLARE_WORK(cmc_disable_work, ia64_mca_cmc_vector_disable_keventd);
अटल DECLARE_WORK(cmc_enable_work, ia64_mca_cmc_vector_enable_keventd);

/*
 * ia64_mca_cmc_पूर्णांक_handler
 *
 *  This is corrected machine check पूर्णांकerrupt handler.
 *	Right now the logs are extracted and displayed in a well-defined
 *	क्रमmat.
 *
 * Inमाला_दो
 *      पूर्णांकerrupt number
 *      client data arg ptr
 *
 * Outमाला_दो
 *	None
 */
अटल irqवापस_t
ia64_mca_cmc_पूर्णांक_handler(पूर्णांक cmc_irq, व्योम *arg)
अणु
	अटल अचिन्हित दीर्घ	cmc_history[CMC_HISTORY_LENGTH];
	अटल पूर्णांक		index;
	अटल DEFINE_SPINLOCK(cmc_history_lock);

	IA64_MCA_DEBUG("%s: received interrupt vector = %#x on CPU %d\n",
		       __func__, cmc_irq, smp_processor_id());

	/* SAL spec states this should run w/ पूर्णांकerrupts enabled */
	local_irq_enable();

	spin_lock(&cmc_history_lock);
	अगर (!cmc_polling_enabled) अणु
		पूर्णांक i, count = 1; /* we know 1 happened now */
		अचिन्हित दीर्घ now = jअगरfies;

		क्रम (i = 0; i < CMC_HISTORY_LENGTH; i++) अणु
			अगर (now - cmc_history[i] <= HZ)
				count++;
		पूर्ण

		IA64_MCA_DEBUG(KERN_INFO "CMC threshold %d/%d\n", count, CMC_HISTORY_LENGTH);
		अगर (count >= CMC_HISTORY_LENGTH) अणु

			cmc_polling_enabled = 1;
			spin_unlock(&cmc_history_lock);
			/* If we're being hit with CMC interrupts, we won't
			 * ever execute the schedule_work() below.  Need to
			 * disable CMC पूर्णांकerrupts on this processor now.
			 */
			ia64_mca_cmc_vector_disable(शून्य);
			schedule_work(&cmc_disable_work);

			/*
			 * Corrected errors will still be corrected, but
			 * make sure there's a log somewhere that indicates
			 * something is generating more than we can handle.
			 */
			prपूर्णांकk(KERN_WARNING "WARNING: Switching to polling CMC handler; error records may be lost\n");

			mod_समयr(&cmc_poll_समयr, jअगरfies + CMC_POLL_INTERVAL);

			/* lock alपढ़ोy released, get out now */
			जाओ out;
		पूर्ण अन्यथा अणु
			cmc_history[index++] = now;
			अगर (index == CMC_HISTORY_LENGTH)
				index = 0;
		पूर्ण
	पूर्ण
	spin_unlock(&cmc_history_lock);
out:
	/* Get the CMC error record and log it */
	ia64_mca_log_sal_error_record(SAL_INFO_TYPE_CMC);

	local_irq_disable();

	वापस IRQ_HANDLED;
पूर्ण

/*
 *  ia64_mca_cmc_पूर्णांक_caller
 *
 * 	Triggered by sw पूर्णांकerrupt from CMC polling routine.  Calls
 * 	real पूर्णांकerrupt handler and either triggers a sw पूर्णांकerrupt
 * 	on the next cpu or करोes cleanup at the end.
 *
 * Inमाला_दो
 *	पूर्णांकerrupt number
 *	client data arg ptr
 * Outमाला_दो
 * 	handled
 */
अटल irqवापस_t
ia64_mca_cmc_पूर्णांक_caller(पूर्णांक cmc_irq, व्योम *arg)
अणु
	अटल पूर्णांक start_count = -1;
	अचिन्हित पूर्णांक cpuid;

	cpuid = smp_processor_id();

	/* If first cpu, update count */
	अगर (start_count == -1)
		start_count = IA64_LOG_COUNT(SAL_INFO_TYPE_CMC);

	ia64_mca_cmc_पूर्णांक_handler(cmc_irq, arg);

	cpuid = cpumask_next(cpuid+1, cpu_online_mask);

	अगर (cpuid < nr_cpu_ids) अणु
		ia64_send_ipi(cpuid, IA64_CMCP_VECTOR, IA64_IPI_DM_INT, 0);
	पूर्ण अन्यथा अणु
		/* If no log record, चयन out of polling mode */
		अगर (start_count == IA64_LOG_COUNT(SAL_INFO_TYPE_CMC)) अणु

			prपूर्णांकk(KERN_WARNING "Returning to interrupt driven CMC handler\n");
			schedule_work(&cmc_enable_work);
			cmc_polling_enabled = 0;

		पूर्ण अन्यथा अणु

			mod_समयr(&cmc_poll_समयr, jअगरfies + CMC_POLL_INTERVAL);
		पूर्ण

		start_count = -1;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 *  ia64_mca_cmc_poll
 *
 *	Poll क्रम Corrected Machine Checks (CMCs)
 *
 * Inमाला_दो   :   dummy(unused)
 * Outमाला_दो  :   None
 *
 */
अटल व्योम
ia64_mca_cmc_poll (काष्ठा समयr_list *unused)
अणु
	/* Trigger a CMC पूर्णांकerrupt cascade  */
	ia64_send_ipi(cpumask_first(cpu_online_mask), IA64_CMCP_VECTOR,
							IA64_IPI_DM_INT, 0);
पूर्ण

/*
 *  ia64_mca_cpe_पूर्णांक_caller
 *
 * 	Triggered by sw पूर्णांकerrupt from CPE polling routine.  Calls
 * 	real पूर्णांकerrupt handler and either triggers a sw पूर्णांकerrupt
 * 	on the next cpu or करोes cleanup at the end.
 *
 * Inमाला_दो
 *	पूर्णांकerrupt number
 *	client data arg ptr
 * Outमाला_दो
 * 	handled
 */
अटल irqवापस_t
ia64_mca_cpe_पूर्णांक_caller(पूर्णांक cpe_irq, व्योम *arg)
अणु
	अटल पूर्णांक start_count = -1;
	अटल पूर्णांक poll_समय = MIN_CPE_POLL_INTERVAL;
	अचिन्हित पूर्णांक cpuid;

	cpuid = smp_processor_id();

	/* If first cpu, update count */
	अगर (start_count == -1)
		start_count = IA64_LOG_COUNT(SAL_INFO_TYPE_CPE);

	ia64_mca_cpe_पूर्णांक_handler(cpe_irq, arg);

	cpuid = cpumask_next(cpuid+1, cpu_online_mask);

	अगर (cpuid < NR_CPUS) अणु
		ia64_send_ipi(cpuid, IA64_CPEP_VECTOR, IA64_IPI_DM_INT, 0);
	पूर्ण अन्यथा अणु
		/*
		 * If a log was recorded, increase our polling frequency,
		 * otherwise, backoff or वापस to पूर्णांकerrupt mode.
		 */
		अगर (start_count != IA64_LOG_COUNT(SAL_INFO_TYPE_CPE)) अणु
			poll_समय = max(MIN_CPE_POLL_INTERVAL, poll_समय / 2);
		पूर्ण अन्यथा अगर (cpe_vector < 0) अणु
			poll_समय = min(MAX_CPE_POLL_INTERVAL, poll_समय * 2);
		पूर्ण अन्यथा अणु
			poll_समय = MIN_CPE_POLL_INTERVAL;

			prपूर्णांकk(KERN_WARNING "Returning to interrupt driven CPE handler\n");
			enable_irq(local_vector_to_irq(IA64_CPE_VECTOR));
			cpe_poll_enabled = 0;
		पूर्ण

		अगर (cpe_poll_enabled)
			mod_समयr(&cpe_poll_समयr, jअगरfies + poll_समय);
		start_count = -1;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 *  ia64_mca_cpe_poll
 *
 *	Poll क्रम Corrected Platक्रमm Errors (CPEs), trigger पूर्णांकerrupt
 *	on first cpu, from there it will trickle through all the cpus.
 *
 * Inमाला_दो   :   dummy(unused)
 * Outमाला_दो  :   None
 *
 */
अटल व्योम
ia64_mca_cpe_poll (काष्ठा समयr_list *unused)
अणु
	/* Trigger a CPE पूर्णांकerrupt cascade  */
	ia64_send_ipi(cpumask_first(cpu_online_mask), IA64_CPEP_VECTOR,
							IA64_IPI_DM_INT, 0);
पूर्ण

अटल पूर्णांक
शेष_monarch_init_process(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ val, व्योम *data)
अणु
	पूर्णांक c;
	काष्ठा task_काष्ठा *g, *t;
	अगर (val != DIE_INIT_MONARCH_PROCESS)
		वापस NOTIFY_DONE;
#अगर_घोषित CONFIG_KEXEC
	अगर (atomic_पढ़ो(&kdump_in_progress))
		वापस NOTIFY_DONE;
#पूर्ण_अगर

	/*
	 * FIXME: mlogbuf will brim over with INIT stack dumps.
	 * To enable show_stack from INIT, we use oops_in_progress which should
	 * be used in real oops. This would cause something wrong after INIT.
	 */
	BREAK_LOGLEVEL(console_loglevel);
	ia64_mlogbuf_dump_from_init();

	prपूर्णांकk(KERN_ERR "Processes interrupted by INIT -");
	क्रम_each_online_cpu(c) अणु
		काष्ठा ia64_sal_os_state *s;
		t = __va(__per_cpu_mca[c] + IA64_MCA_CPU_INIT_STACK_OFFSET);
		s = (काष्ठा ia64_sal_os_state *)((अक्षर *)t + MCA_SOS_OFFSET);
		g = s->prev_task;
		अगर (g) अणु
			अगर (g->pid)
				prपूर्णांकk(" %d", g->pid);
			अन्यथा
				prपूर्णांकk(" %d (cpu %d task 0x%p)", g->pid, task_cpu(g), g);
		पूर्ण
	पूर्ण
	prपूर्णांकk("\n\n");
	अगर (पढ़ो_trylock(&tasklist_lock)) अणु
		करो_each_thपढ़ो (g, t) अणु
			prपूर्णांकk("\nBacktrace of pid %d (%s)\n", t->pid, t->comm);
			show_stack(t, शून्य, KERN_DEFAULT);
		पूर्ण जबतक_each_thपढ़ो (g, t);
		पढ़ो_unlock(&tasklist_lock);
	पूर्ण
	/* FIXME: This will not restore zapped prपूर्णांकk locks. */
	RESTORE_LOGLEVEL(console_loglevel);
	वापस NOTIFY_DONE;
पूर्ण

/*
 * C portion of the OS INIT handler
 *
 * Called from ia64_os_init_dispatch
 *
 * Inमाला_दो: poपूर्णांकer to pt_regs where processor info was saved.  SAL/OS state क्रम
 * this event.  This code is used क्रम both monarch and slave INIT events, see
 * sos->monarch.
 *
 * All INIT events चयन to the INIT stack and change the previous process to
 * blocked status.  If one of the INIT events is the monarch then we are
 * probably processing the nmi button/command.  Use the monarch cpu to dump all
 * the processes.  The slave INIT events all spin until the monarch cpu
 * वापसs.  We can also get INIT slave events क्रम MCA, in which हाल the MCA
 * process is the monarch.
 */

व्योम
ia64_init_handler(काष्ठा pt_regs *regs, काष्ठा चयन_stack *sw,
		  काष्ठा ia64_sal_os_state *sos)
अणु
	अटल atomic_t slaves;
	अटल atomic_t monarchs;
	काष्ठा task_काष्ठा *previous_current;
	पूर्णांक cpu = smp_processor_id();
	काष्ठा ia64_mca_notअगरy_die nd =
		अणु .sos = sos, .monarch_cpu = &monarch_cpu पूर्ण;

	NOTIFY_INIT(DIE_INIT_ENTER, regs, (दीर्घ)&nd, 0);

	mprपूर्णांकk(KERN_INFO "Entered OS INIT handler. PSP=%lx cpu=%d monarch=%ld\n",
		sos->proc_state_param, cpu, sos->monarch);
	salinfo_log_wakeup(SAL_INFO_TYPE_INIT, शून्य, 0, 0);

	previous_current = ia64_mca_modअगरy_original_stack(regs, sw, sos, "INIT");
	sos->os_status = IA64_INIT_RESUME;

	/* FIXME: Workaround क्रम broken proms that drive all INIT events as
	 * slaves.  The last slave that enters is promoted to be a monarch.
	 * Remove this code in September 2006, that gives platक्रमms a year to
	 * fix their proms and get their customers updated.
	 */
	अगर (!sos->monarch && atomic_add_वापस(1, &slaves) == num_online_cpus()) अणु
		mprपूर्णांकk(KERN_WARNING "%s: Promoting cpu %d to monarch.\n",
		        __func__, cpu);
		atomic_dec(&slaves);
		sos->monarch = 1;
	पूर्ण

	/* FIXME: Workaround क्रम broken proms that drive all INIT events as
	 * monarchs.  Second and subsequent monarchs are demoted to slaves.
	 * Remove this code in September 2006, that gives platक्रमms a year to
	 * fix their proms and get their customers updated.
	 */
	अगर (sos->monarch && atomic_add_वापस(1, &monarchs) > 1) अणु
		mprपूर्णांकk(KERN_WARNING "%s: Demoting cpu %d to slave.\n",
			       __func__, cpu);
		atomic_dec(&monarchs);
		sos->monarch = 0;
	पूर्ण

	अगर (!sos->monarch) अणु
		ia64_mc_info.imi_rendez_checkin[cpu] = IA64_MCA_RENDEZ_CHECKIN_INIT;

#अगर_घोषित CONFIG_KEXEC
		जबतक (monarch_cpu == -1 && !atomic_पढ़ो(&kdump_in_progress))
			udelay(1000);
#अन्यथा
		जबतक (monarch_cpu == -1)
			cpu_relax();	/* spin until monarch enters */
#पूर्ण_अगर

		NOTIFY_INIT(DIE_INIT_SLAVE_ENTER, regs, (दीर्घ)&nd, 1);
		NOTIFY_INIT(DIE_INIT_SLAVE_PROCESS, regs, (दीर्घ)&nd, 1);

#अगर_घोषित CONFIG_KEXEC
		जबतक (monarch_cpu != -1 && !atomic_पढ़ो(&kdump_in_progress))
			udelay(1000);
#अन्यथा
		जबतक (monarch_cpu != -1)
			cpu_relax();	/* spin until monarch leaves */
#पूर्ण_अगर

		NOTIFY_INIT(DIE_INIT_SLAVE_LEAVE, regs, (दीर्घ)&nd, 1);

		mprपूर्णांकk("Slave on cpu %d returning to normal service.\n", cpu);
		ia64_set_curr_task(cpu, previous_current);
		ia64_mc_info.imi_rendez_checkin[cpu] = IA64_MCA_RENDEZ_CHECKIN_NOTDONE;
		atomic_dec(&slaves);
		वापस;
	पूर्ण

	monarch_cpu = cpu;
	NOTIFY_INIT(DIE_INIT_MONARCH_ENTER, regs, (दीर्घ)&nd, 1);

	/*
	 * Wait क्रम a bit.  On some machines (e.g., HP's zx2000 and zx6000, INIT can be
	 * generated via the BMC's command-line पूर्णांकerface, but since the console is on the
	 * same serial line, the user will need some समय to चयन out of the BMC beक्रमe
	 * the dump begins.
	 */
	mprपूर्णांकk("Delaying for 5 seconds...\n");
	udelay(5*1000000);
	ia64_रुको_क्रम_slaves(cpu, "INIT");
	/* If nobody पूर्णांकercepts DIE_INIT_MONARCH_PROCESS then we drop through
	 * to शेष_monarch_init_process() above and just prपूर्णांक all the
	 * tasks.
	 */
	NOTIFY_INIT(DIE_INIT_MONARCH_PROCESS, regs, (दीर्घ)&nd, 1);
	NOTIFY_INIT(DIE_INIT_MONARCH_LEAVE, regs, (दीर्घ)&nd, 1);

	mprपूर्णांकk("\nINIT dump complete.  Monarch on cpu %d returning to normal service.\n", cpu);
	atomic_dec(&monarchs);
	ia64_set_curr_task(cpu, previous_current);
	monarch_cpu = -1;
	वापस;
पूर्ण

अटल पूर्णांक __init
ia64_mca_disable_cpe_polling(अक्षर *str)
अणु
	cpe_poll_enabled = 0;
	वापस 1;
पूर्ण

__setup("disable_cpe_poll", ia64_mca_disable_cpe_polling);

/* Minimal क्रमmat of the MCA/INIT stacks.  The pseuकरो processes that run on
 * these stacks can never sleep, they cannot वापस from the kernel to user
 * space, they करो not appear in a normal ps listing.  So there is no need to
 * क्रमmat most of the fields.
 */

अटल व्योम
क्रमmat_mca_init_stack(व्योम *mca_data, अचिन्हित दीर्घ offset,
		स्थिर अक्षर *type, पूर्णांक cpu)
अणु
	काष्ठा task_काष्ठा *p = (काष्ठा task_काष्ठा *)((अक्षर *)mca_data + offset);
	काष्ठा thपढ़ो_info *ti;
	स_रखो(p, 0, KERNEL_STACK_SIZE);
	ti = task_thपढ़ो_info(p);
	ti->flags = _TIF_MCA_INIT;
	ti->preempt_count = 1;
	ti->task = p;
	ti->cpu = cpu;
	p->stack = ti;
	p->state = TASK_UNINTERRUPTIBLE;
	cpumask_set_cpu(cpu, &p->cpus_mask);
	INIT_LIST_HEAD(&p->tasks);
	p->parent = p->real_parent = p->group_leader = p;
	INIT_LIST_HEAD(&p->children);
	INIT_LIST_HEAD(&p->sibling);
	म_नकलन(p->comm, type, माप(p->comm)-1);
पूर्ण

/* Caller prevents this from being called after init */
अटल व्योम * __ref mca_booपंचांगem(व्योम)
अणु
	वापस memblock_alloc(माप(काष्ठा ia64_mca_cpu), KERNEL_STACK_SIZE);
पूर्ण

/* Do per-CPU MCA-related initialization.  */
व्योम
ia64_mca_cpu_init(व्योम *cpu_data)
अणु
	व्योम *pal_vaddr;
	व्योम *data;
	दीर्घ sz = माप(काष्ठा ia64_mca_cpu);
	पूर्णांक cpu = smp_processor_id();
	अटल पूर्णांक first_समय = 1;

	/*
	 * Structure will alपढ़ोy be allocated अगर cpu has been online,
	 * then offlined.
	 */
	अगर (__per_cpu_mca[cpu]) अणु
		data = __va(__per_cpu_mca[cpu]);
	पूर्ण अन्यथा अणु
		अगर (first_समय) अणु
			data = mca_booपंचांगem();
			first_समय = 0;
		पूर्ण अन्यथा
			data = (व्योम *)__get_मुक्त_pages(GFP_ATOMIC,
							get_order(sz));
		अगर (!data)
			panic("Could not allocate MCA memory for cpu %d\n",
					cpu);
	पूर्ण
	क्रमmat_mca_init_stack(data, दुरत्व(काष्ठा ia64_mca_cpu, mca_stack),
		"MCA", cpu);
	क्रमmat_mca_init_stack(data, दुरत्व(काष्ठा ia64_mca_cpu, init_stack),
		"INIT", cpu);
	__this_cpu_ग_लिखो(ia64_mca_data, (__per_cpu_mca[cpu] = __pa(data)));

	/*
	 * Stash away a copy of the PTE needed to map the per-CPU page.
	 * We may need it during MCA recovery.
	 */
	__this_cpu_ग_लिखो(ia64_mca_per_cpu_pte,
		pte_val(mk_pte_phys(__pa(cpu_data), PAGE_KERNEL)));

	/*
	 * Also, stash away a copy of the PAL address and the PTE
	 * needed to map it.
	 */
	pal_vaddr = efi_get_pal_addr();
	अगर (!pal_vaddr)
		वापस;
	__this_cpu_ग_लिखो(ia64_mca_pal_base,
		GRANULEROUNDDOWN((अचिन्हित दीर्घ) pal_vaddr));
	__this_cpu_ग_लिखो(ia64_mca_pal_pte, pte_val(mk_pte_phys(__pa(pal_vaddr),
							      PAGE_KERNEL)));
पूर्ण

अटल पूर्णांक ia64_mca_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	अगर (!cmc_polling_enabled)
		ia64_mca_cmc_vector_enable(शून्य);
	local_irq_restore(flags);
	वापस 0;
पूर्ण

/*
 * ia64_mca_init
 *
 *  Do all the प्रणाली level mca specअगरic initialization.
 *
 *	1. Register spinloop and wakeup request पूर्णांकerrupt vectors
 *
 *	2. Register OS_MCA handler entry poपूर्णांक
 *
 *	3. Register OS_INIT handler entry poपूर्णांक
 *
 *  4. Initialize MCA/CMC/INIT related log buffers मुख्यtained by the OS.
 *
 *  Note that this initialization is करोne very early beक्रमe some kernel
 *  services are available.
 *
 *  Inमाला_दो  :   None
 *
 *  Outमाला_दो :   None
 */
व्योम __init
ia64_mca_init(व्योम)
अणु
	ia64_fptr_t *init_hldlr_ptr_monarch = (ia64_fptr_t *)ia64_os_init_dispatch_monarch;
	ia64_fptr_t *init_hldlr_ptr_slave = (ia64_fptr_t *)ia64_os_init_dispatch_slave;
	ia64_fptr_t *mca_hldlr_ptr = (ia64_fptr_t *)ia64_os_mca_dispatch;
	पूर्णांक i;
	दीर्घ rc;
	काष्ठा ia64_sal_retval isrv;
	अचिन्हित दीर्घ समयout = IA64_MCA_RENDEZ_TIMEOUT; /* platक्रमm specअगरic */
	अटल काष्ठा notअगरier_block शेष_init_monarch_nb = अणु
		.notअगरier_call = शेष_monarch_init_process,
		.priority = 0/* we need to notअगरied last */
	पूर्ण;

	IA64_MCA_DEBUG("%s: begin\n", __func__);

	/* Clear the Rendez checkin flag क्रम all cpus */
	क्रम(i = 0 ; i < NR_CPUS; i++)
		ia64_mc_info.imi_rendez_checkin[i] = IA64_MCA_RENDEZ_CHECKIN_NOTDONE;

	/*
	 * Register the rendezvous spinloop and wakeup mechanism with SAL
	 */

	/* Register the rendezvous पूर्णांकerrupt vector with SAL */
	जबतक (1) अणु
		isrv = ia64_sal_mc_set_params(SAL_MC_PARAM_RENDEZ_INT,
					      SAL_MC_PARAM_MECHANISM_INT,
					      IA64_MCA_RENDEZ_VECTOR,
					      समयout,
					      SAL_MC_PARAM_RZ_ALWAYS);
		rc = isrv.status;
		अगर (rc == 0)
			अवरोध;
		अगर (rc == -2) अणु
			prपूर्णांकk(KERN_INFO "Increasing MCA rendezvous timeout from "
				"%ld to %ld milliseconds\n", समयout, isrv.v0);
			समयout = isrv.v0;
			NOTIFY_MCA(DIE_MCA_NEW_TIMEOUT, शून्य, समयout, 0);
			जारी;
		पूर्ण
		prपूर्णांकk(KERN_ERR "Failed to register rendezvous interrupt "
		       "with SAL (status %ld)\n", rc);
		वापस;
	पूर्ण

	/* Register the wakeup पूर्णांकerrupt vector with SAL */
	isrv = ia64_sal_mc_set_params(SAL_MC_PARAM_RENDEZ_WAKEUP,
				      SAL_MC_PARAM_MECHANISM_INT,
				      IA64_MCA_WAKEUP_VECTOR,
				      0, 0);
	rc = isrv.status;
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "Failed to register wakeup interrupt with SAL "
		       "(status %ld)\n", rc);
		वापस;
	पूर्ण

	IA64_MCA_DEBUG("%s: registered MCA rendezvous spinloop and wakeup mech.\n", __func__);

	ia64_mc_info.imi_mca_handler        = ia64_tpa(mca_hldlr_ptr->fp);
	/*
	 * XXX - disable SAL checksum by setting size to 0; should be
	 *	ia64_tpa(ia64_os_mca_dispatch_end) - ia64_tpa(ia64_os_mca_dispatch);
	 */
	ia64_mc_info.imi_mca_handler_size	= 0;

	/* Register the os mca handler with SAL */
	अगर ((rc = ia64_sal_set_vectors(SAL_VECTOR_OS_MCA,
				       ia64_mc_info.imi_mca_handler,
				       ia64_tpa(mca_hldlr_ptr->gp),
				       ia64_mc_info.imi_mca_handler_size,
				       0, 0, 0)))
	अणु
		prपूर्णांकk(KERN_ERR "Failed to register OS MCA handler with SAL "
		       "(status %ld)\n", rc);
		वापस;
	पूर्ण

	IA64_MCA_DEBUG("%s: registered OS MCA handler with SAL at 0x%lx, gp = 0x%lx\n", __func__,
		       ia64_mc_info.imi_mca_handler, ia64_tpa(mca_hldlr_ptr->gp));

	/*
	 * XXX - disable SAL checksum by setting size to 0, should be
	 * size of the actual init handler in mca_यंत्र.S.
	 */
	ia64_mc_info.imi_monarch_init_handler		= ia64_tpa(init_hldlr_ptr_monarch->fp);
	ia64_mc_info.imi_monarch_init_handler_size	= 0;
	ia64_mc_info.imi_slave_init_handler		= ia64_tpa(init_hldlr_ptr_slave->fp);
	ia64_mc_info.imi_slave_init_handler_size	= 0;

	IA64_MCA_DEBUG("%s: OS INIT handler at %lx\n", __func__,
		       ia64_mc_info.imi_monarch_init_handler);

	/* Register the os init handler with SAL */
	अगर ((rc = ia64_sal_set_vectors(SAL_VECTOR_OS_INIT,
				       ia64_mc_info.imi_monarch_init_handler,
				       ia64_tpa(ia64_getreg(_IA64_REG_GP)),
				       ia64_mc_info.imi_monarch_init_handler_size,
				       ia64_mc_info.imi_slave_init_handler,
				       ia64_tpa(ia64_getreg(_IA64_REG_GP)),
				       ia64_mc_info.imi_slave_init_handler_size)))
	अणु
		prपूर्णांकk(KERN_ERR "Failed to register m/s INIT handlers with SAL "
		       "(status %ld)\n", rc);
		वापस;
	पूर्ण
	अगर (रेजिस्टर_die_notअगरier(&शेष_init_monarch_nb)) अणु
		prपूर्णांकk(KERN_ERR "Failed to register default monarch INIT process\n");
		वापस;
	पूर्ण

	IA64_MCA_DEBUG("%s: registered OS INIT handler with SAL\n", __func__);

	/* Initialize the areas set aside by the OS to buffer the
	 * platक्रमm/processor error states क्रम MCA/INIT/CMC
	 * handling.
	 */
	ia64_log_init(SAL_INFO_TYPE_MCA);
	ia64_log_init(SAL_INFO_TYPE_INIT);
	ia64_log_init(SAL_INFO_TYPE_CMC);
	ia64_log_init(SAL_INFO_TYPE_CPE);

	mca_init = 1;
	prपूर्णांकk(KERN_INFO "MCA related initialization done\n");
पूर्ण


/*
 * These pieces cannot be करोne in ia64_mca_init() because it is called beक्रमe
 * early_irq_init() which would wipe out our percpu irq registrations. But we
 * cannot leave them until ia64_mca_late_init() because by then all the other
 * processors have been brought online and have set their own CMC vectors to
 * poपूर्णांक at a non-existant action. Called from arch_early_irq_init().
 */
व्योम __init ia64_mca_irq_init(व्योम)
अणु
	/*
	 *  Configure the CMCI/P vector and handler. Interrupts क्रम CMC are
	 *  per-processor, so AP CMC पूर्णांकerrupts are setup in smp_callin() (smpboot.c).
	 */
	रेजिस्टर_percpu_irq(IA64_CMC_VECTOR, ia64_mca_cmc_पूर्णांक_handler, 0,
			    "cmc_hndlr");
	रेजिस्टर_percpu_irq(IA64_CMCP_VECTOR, ia64_mca_cmc_पूर्णांक_caller, 0,
			    "cmc_poll");
	ia64_mca_cmc_vector_setup();       /* Setup vector on BSP */

	/* Setup the MCA rendezvous पूर्णांकerrupt vector */
	रेजिस्टर_percpu_irq(IA64_MCA_RENDEZ_VECTOR, ia64_mca_rendez_पूर्णांक_handler,
			    0, "mca_rdzv");

	/* Setup the MCA wakeup पूर्णांकerrupt vector */
	रेजिस्टर_percpu_irq(IA64_MCA_WAKEUP_VECTOR, ia64_mca_wakeup_पूर्णांक_handler,
			    0, "mca_wkup");

	/* Setup the CPEI/P handler */
	रेजिस्टर_percpu_irq(IA64_CPEP_VECTOR, ia64_mca_cpe_पूर्णांक_caller, 0,
			    "cpe_poll");
पूर्ण

/*
 * ia64_mca_late_init
 *
 *	Opportunity to setup things that require initialization later
 *	than ia64_mca_init.  Setup a समयr to poll क्रम CPEs अगर the
 *	platक्रमm करोesn't support an पूर्णांकerrupt driven mechanism.
 *
 *  Inमाला_दो  :   None
 *  Outमाला_दो :   Status
 */
अटल पूर्णांक __init
ia64_mca_late_init(व्योम)
अणु
	अगर (!mca_init)
		वापस 0;

	/* Setup the CMCI/P vector and handler */
	समयr_setup(&cmc_poll_समयr, ia64_mca_cmc_poll, 0);

	/* Unmask/enable the vector */
	cmc_polling_enabled = 0;
	cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "ia64/mca:online",
			  ia64_mca_cpu_online, शून्य);
	IA64_MCA_DEBUG("%s: CMCI/P setup and enabled.\n", __func__);

	/* Setup the CPEI/P vector and handler */
	cpe_vector = acpi_request_vector(ACPI_INTERRUPT_CPEI);
	समयr_setup(&cpe_poll_समयr, ia64_mca_cpe_poll, 0);

	अणु
		अचिन्हित पूर्णांक irq;

		अगर (cpe_vector >= 0) अणु
			/* If platक्रमm supports CPEI, enable the irq. */
			irq = local_vector_to_irq(cpe_vector);
			अगर (irq > 0) अणु
				cpe_poll_enabled = 0;
				irq_set_status_flags(irq, IRQ_PER_CPU);
				अगर (request_irq(irq, ia64_mca_cpe_पूर्णांक_handler,
						0, "cpe_hndlr", शून्य))
					pr_err("Failed to register cpe_hndlr interrupt\n");
				ia64_cpe_irq = irq;
				ia64_mca_रेजिस्टर_cpev(cpe_vector);
				IA64_MCA_DEBUG("%s: CPEI/P setup and enabled.\n",
					__func__);
				वापस 0;
			पूर्ण
			prपूर्णांकk(KERN_ERR "%s: Failed to find irq for CPE "
					"interrupt handler, vector %d\n",
					__func__, cpe_vector);
		पूर्ण
		/* If platक्रमm करोesn't support CPEI, get the समयr going. */
		अगर (cpe_poll_enabled) अणु
			ia64_mca_cpe_poll(0UL);
			IA64_MCA_DEBUG("%s: CPEP setup and enabled.\n", __func__);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

device_initcall(ia64_mca_late_init);
