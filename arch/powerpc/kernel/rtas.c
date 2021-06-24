<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Procedures क्रम पूर्णांकerfacing to the RTAS on CHRP machines.
 *
 * Peter Bergner, IBM	March 2001.
 * Copyright (C) 2001 IBM.
 */

#समावेश <मानकतर्क.स>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/capability.h>
#समावेश <linux/delay.h>
#समावेश <linux/cpu.h>
#समावेश <linux/sched.h>
#समावेश <linux/smp.h>
#समावेश <linux/completion.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/memblock.h>
#समावेश <linux/slab.h>
#समावेश <linux/reboot.h>
#समावेश <linux/syscalls.h>

#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/param.h>
#समावेश <यंत्र/delay.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/syscalls.h>
#समावेश <यंत्र/smp.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/topology.h>
#समावेश <यंत्र/paca.h>

/* This is here deliberately so it's only used in this file */
व्योम enter_rtas(अचिन्हित दीर्घ);

काष्ठा rtas_t rtas = अणु
	.lock = __ARCH_SPIN_LOCK_UNLOCKED
पूर्ण;
EXPORT_SYMBOL(rtas);

DEFINE_SPINLOCK(rtas_data_buf_lock);
EXPORT_SYMBOL(rtas_data_buf_lock);

अक्षर rtas_data_buf[RTAS_DATA_BUF_SIZE] __cacheline_aligned;
EXPORT_SYMBOL(rtas_data_buf);

अचिन्हित दीर्घ rtas_rmo_buf;

/*
 * If non-शून्य, this माला_लो called when the kernel terminates.
 * This is करोne like this so rtas_flash can be a module.
 */
व्योम (*rtas_flash_term_hook)(पूर्णांक);
EXPORT_SYMBOL(rtas_flash_term_hook);

/* RTAS use home made raw locking instead of spin_lock_irqsave
 * because those can be called from within really nasty contexts
 * such as having the समयbase stopped which would lockup with
 * normal locks and spinlock debugging enabled
 */
अटल अचिन्हित दीर्घ lock_rtas(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	preempt_disable();
	arch_spin_lock(&rtas.lock);
	वापस flags;
पूर्ण

अटल व्योम unlock_rtas(अचिन्हित दीर्घ flags)
अणु
	arch_spin_unlock(&rtas.lock);
	local_irq_restore(flags);
	preempt_enable();
पूर्ण

/*
 * call_rtas_display_status and call_rtas_display_status_delay
 * are deचिन्हित only क्रम very early low-level debugging, which
 * is why the token is hard-coded to 10.
 */
अटल व्योम call_rtas_display_status(अचिन्हित अक्षर c)
अणु
	अचिन्हित दीर्घ s;

	अगर (!rtas.base)
		वापस;

	s = lock_rtas();
	rtas_call_unlocked(&rtas.args, 10, 1, 1, शून्य, c);
	unlock_rtas(s);
पूर्ण

अटल व्योम call_rtas_display_status_delay(अक्षर c)
अणु
	अटल पूर्णांक pending_newline = 0;  /* did last ग_लिखो end with unprपूर्णांकed newline? */
	अटल पूर्णांक width = 16;

	अगर (c == '\n') अणु	
		जबतक (width-- > 0)
			call_rtas_display_status(' ');
		width = 16;
		mdelay(500);
		pending_newline = 1;
	पूर्ण अन्यथा अणु
		अगर (pending_newline) अणु
			call_rtas_display_status('\r');
			call_rtas_display_status('\n');
		पूर्ण 
		pending_newline = 0;
		अगर (width--) अणु
			call_rtas_display_status(c);
			udelay(10000);
		पूर्ण
	पूर्ण
पूर्ण

व्योम __init udbg_init_rtas_panel(व्योम)
अणु
	udbg_अ_दो = call_rtas_display_status_delay;
पूर्ण

#अगर_घोषित CONFIG_UDBG_RTAS_CONSOLE

/* If you think you're dying beक्रमe early_init_dt_scan_rtas() करोes its
 * work, you can hard code the token values क्रम your firmware here and
 * hardcode rtas.base/entry etc.
 */
अटल अचिन्हित पूर्णांक rtas_अक्षर_दो_token = RTAS_UNKNOWN_SERVICE;
अटल अचिन्हित पूर्णांक rtas_अक्षर_लो_token = RTAS_UNKNOWN_SERVICE;

अटल व्योम udbg_rtascon_अ_दो(अक्षर c)
अणु
	पूर्णांक tries;

	अगर (!rtas.base)
		वापस;

	/* Add CRs beक्रमe LFs */
	अगर (c == '\n')
		udbg_rtascon_अ_दो('\r');

	/* अगर there is more than one अक्षरacter to be displayed, रुको a bit */
	क्रम (tries = 0; tries < 16; tries++) अणु
		अगर (rtas_call(rtas_अक्षर_दो_token, 1, 1, शून्य, c) == 0)
			अवरोध;
		udelay(1000);
	पूर्ण
पूर्ण

अटल पूर्णांक udbg_rtascon_अ_लो_poll(व्योम)
अणु
	पूर्णांक c;

	अगर (!rtas.base)
		वापस -1;

	अगर (rtas_call(rtas_अक्षर_लो_token, 0, 2, &c))
		वापस -1;

	वापस c;
पूर्ण

अटल पूर्णांक udbg_rtascon_अ_लो(व्योम)
अणु
	पूर्णांक c;

	जबतक ((c = udbg_rtascon_अ_लो_poll()) == -1)
		;

	वापस c;
पूर्ण


व्योम __init udbg_init_rtas_console(व्योम)
अणु
	udbg_अ_दो = udbg_rtascon_अ_दो;
	udbg_अ_लो = udbg_rtascon_अ_लो;
	udbg_अ_लो_poll = udbg_rtascon_अ_लो_poll;
पूर्ण
#पूर्ण_अगर /* CONFIG_UDBG_RTAS_CONSOLE */

व्योम rtas_progress(अक्षर *s, अचिन्हित लघु hex)
अणु
	काष्ठा device_node *root;
	पूर्णांक width;
	स्थिर __be32 *p;
	अक्षर *os;
	अटल पूर्णांक display_अक्षरacter, set_indicator;
	अटल पूर्णांक display_width, display_lines, क्रमm_feed;
	अटल स्थिर पूर्णांक *row_width;
	अटल DEFINE_SPINLOCK(progress_lock);
	अटल पूर्णांक current_line;
	अटल पूर्णांक pending_newline = 0;  /* did last ग_लिखो end with unprपूर्णांकed newline? */

	अगर (!rtas.base)
		वापस;

	अगर (display_width == 0) अणु
		display_width = 0x10;
		अगर ((root = of_find_node_by_path("/rtas"))) अणु
			अगर ((p = of_get_property(root,
					"ibm,display-line-length", शून्य)))
				display_width = be32_to_cpu(*p);
			अगर ((p = of_get_property(root,
					"ibm,form-feed", शून्य)))
				क्रमm_feed = be32_to_cpu(*p);
			अगर ((p = of_get_property(root,
					"ibm,display-number-of-lines", शून्य)))
				display_lines = be32_to_cpu(*p);
			row_width = of_get_property(root,
					"ibm,display-truncation-length", शून्य);
			of_node_put(root);
		पूर्ण
		display_अक्षरacter = rtas_token("display-character");
		set_indicator = rtas_token("set-indicator");
	पूर्ण

	अगर (display_अक्षरacter == RTAS_UNKNOWN_SERVICE) अणु
		/* use hex display अगर available */
		अगर (set_indicator != RTAS_UNKNOWN_SERVICE)
			rtas_call(set_indicator, 3, 1, शून्य, 6, 0, hex);
		वापस;
	पूर्ण

	spin_lock(&progress_lock);

	/*
	 * Last ग_लिखो ended with newline, but we didn't prपूर्णांक it since
	 * it would just clear the bottom line of output. Prपूर्णांक it now
	 * instead.
	 *
	 * If no newline is pending and क्रमm feed is supported, clear the
	 * display with a क्रमm feed; otherwise, prपूर्णांक a CR to start output
	 * at the beginning of the line.
	 */
	अगर (pending_newline) अणु
		rtas_call(display_अक्षरacter, 1, 1, शून्य, '\r');
		rtas_call(display_अक्षरacter, 1, 1, शून्य, '\n');
		pending_newline = 0;
	पूर्ण अन्यथा अणु
		current_line = 0;
		अगर (क्रमm_feed)
			rtas_call(display_अक्षरacter, 1, 1, शून्य,
				  (अक्षर)क्रमm_feed);
		अन्यथा
			rtas_call(display_अक्षरacter, 1, 1, शून्य, '\r');
	पूर्ण
 
	अगर (row_width)
		width = row_width[current_line];
	अन्यथा
		width = display_width;
	os = s;
	जबतक (*os) अणु
		अगर (*os == '\n' || *os == '\r') अणु
			/* If newline is the last अक्षरacter, save it
			 * until next call to aव्योम bumping up the
			 * display output.
			 */
			अगर (*os == '\n' && !os[1]) अणु
				pending_newline = 1;
				current_line++;
				अगर (current_line > display_lines-1)
					current_line = display_lines-1;
				spin_unlock(&progress_lock);
				वापस;
			पूर्ण
 
			/* RTAS wants CR-LF, not just LF */
 
			अगर (*os == '\n') अणु
				rtas_call(display_अक्षरacter, 1, 1, शून्य, '\r');
				rtas_call(display_अक्षरacter, 1, 1, शून्य, '\n');
			पूर्ण अन्यथा अणु
				/* CR might be used to re-draw a line, so we'll
				 * leave it alone and not add LF.
				 */
				rtas_call(display_अक्षरacter, 1, 1, शून्य, *os);
			पूर्ण
 
			अगर (row_width)
				width = row_width[current_line];
			अन्यथा
				width = display_width;
		पूर्ण अन्यथा अणु
			width--;
			rtas_call(display_अक्षरacter, 1, 1, शून्य, *os);
		पूर्ण
 
		os++;
 
		/* अगर we overग_लिखो the screen length */
		अगर (width <= 0)
			जबतक ((*os != 0) && (*os != '\n') && (*os != '\r'))
				os++;
	पूर्ण
 
	spin_unlock(&progress_lock);
पूर्ण
EXPORT_SYMBOL(rtas_progress);		/* needed by rtas_flash module */

पूर्णांक rtas_token(स्थिर अक्षर *service)
अणु
	स्थिर __be32 *tokp;
	अगर (rtas.dev == शून्य)
		वापस RTAS_UNKNOWN_SERVICE;
	tokp = of_get_property(rtas.dev, service, शून्य);
	वापस tokp ? be32_to_cpu(*tokp) : RTAS_UNKNOWN_SERVICE;
पूर्ण
EXPORT_SYMBOL(rtas_token);

पूर्णांक rtas_service_present(स्थिर अक्षर *service)
अणु
	वापस rtas_token(service) != RTAS_UNKNOWN_SERVICE;
पूर्ण
EXPORT_SYMBOL(rtas_service_present);

#अगर_घोषित CONFIG_RTAS_ERROR_LOGGING
/*
 * Return the firmware-specअगरied size of the error log buffer
 *  क्रम all rtas calls that require an error buffer argument.
 *  This includes 'check-exception' and 'rtas-last-error'.
 */
पूर्णांक rtas_get_error_log_max(व्योम)
अणु
	अटल पूर्णांक rtas_error_log_max;
	अगर (rtas_error_log_max)
		वापस rtas_error_log_max;

	rtas_error_log_max = rtas_token ("rtas-error-log-max");
	अगर ((rtas_error_log_max == RTAS_UNKNOWN_SERVICE) ||
	    (rtas_error_log_max > RTAS_ERROR_LOG_MAX)) अणु
		prपूर्णांकk (KERN_WARNING "RTAS: bad log buffer size %d\n",
			rtas_error_log_max);
		rtas_error_log_max = RTAS_ERROR_LOG_MAX;
	पूर्ण
	वापस rtas_error_log_max;
पूर्ण
EXPORT_SYMBOL(rtas_get_error_log_max);


अटल अक्षर rtas_err_buf[RTAS_ERROR_LOG_MAX];
अटल पूर्णांक rtas_last_error_token;

/** Return a copy of the detailed error text associated with the
 *  most recent failed call to rtas.  Because the error text
 *  might go stale अगर there are any other पूर्णांकervening rtas calls,
 *  this routine must be called atomically with whatever produced
 *  the error (i.e. with rtas.lock still held from the previous call).
 */
अटल अक्षर *__fetch_rtas_last_error(अक्षर *altbuf)
अणु
	काष्ठा rtas_args err_args, save_args;
	u32 bufsz;
	अक्षर *buf = शून्य;

	अगर (rtas_last_error_token == -1)
		वापस शून्य;

	bufsz = rtas_get_error_log_max();

	err_args.token = cpu_to_be32(rtas_last_error_token);
	err_args.nargs = cpu_to_be32(2);
	err_args.nret = cpu_to_be32(1);
	err_args.args[0] = cpu_to_be32(__pa(rtas_err_buf));
	err_args.args[1] = cpu_to_be32(bufsz);
	err_args.args[2] = 0;

	save_args = rtas.args;
	rtas.args = err_args;

	enter_rtas(__pa(&rtas.args));

	err_args = rtas.args;
	rtas.args = save_args;

	/* Log the error in the unlikely हाल that there was one. */
	अगर (unlikely(err_args.args[2] == 0)) अणु
		अगर (altbuf) अणु
			buf = altbuf;
		पूर्ण अन्यथा अणु
			buf = rtas_err_buf;
			अगर (slab_is_available())
				buf = kदो_स्मृति(RTAS_ERROR_LOG_MAX, GFP_ATOMIC);
		पूर्ण
		अगर (buf)
			स_नकल(buf, rtas_err_buf, RTAS_ERROR_LOG_MAX);
	पूर्ण

	वापस buf;
पूर्ण

#घोषणा get_errorlog_buffer()	kदो_स्मृति(RTAS_ERROR_LOG_MAX, GFP_KERNEL)

#अन्यथा /* CONFIG_RTAS_ERROR_LOGGING */
#घोषणा __fetch_rtas_last_error(x)	शून्य
#घोषणा get_errorlog_buffer()		शून्य
#पूर्ण_अगर


अटल व्योम
va_rtas_call_unlocked(काष्ठा rtas_args *args, पूर्णांक token, पूर्णांक nargs, पूर्णांक nret,
		      बहु_सूची list)
अणु
	पूर्णांक i;

	args->token = cpu_to_be32(token);
	args->nargs = cpu_to_be32(nargs);
	args->nret  = cpu_to_be32(nret);
	args->rets  = &(args->args[nargs]);

	क्रम (i = 0; i < nargs; ++i)
		args->args[i] = cpu_to_be32(बहु_तर्क(list, __u32));

	क्रम (i = 0; i < nret; ++i)
		args->rets[i] = 0;

	enter_rtas(__pa(args));
पूर्ण

व्योम rtas_call_unlocked(काष्ठा rtas_args *args, पूर्णांक token, पूर्णांक nargs, पूर्णांक nret, ...)
अणु
	बहु_सूची list;

	बहु_शुरू(list, nret);
	va_rtas_call_unlocked(args, token, nargs, nret, list);
	बहु_पूर्ण(list);
पूर्ण

पूर्णांक rtas_call(पूर्णांक token, पूर्णांक nargs, पूर्णांक nret, पूर्णांक *outमाला_दो, ...)
अणु
	बहु_सूची list;
	पूर्णांक i;
	अचिन्हित दीर्घ s;
	काष्ठा rtas_args *rtas_args;
	अक्षर *buff_copy = शून्य;
	पूर्णांक ret;

	अगर (!rtas.entry || token == RTAS_UNKNOWN_SERVICE)
		वापस -1;

	s = lock_rtas();

	/* We use the global rtas args buffer */
	rtas_args = &rtas.args;

	बहु_शुरू(list, outमाला_दो);
	va_rtas_call_unlocked(rtas_args, token, nargs, nret, list);
	बहु_पूर्ण(list);

	/* A -1 वापस code indicates that the last command couldn't
	   be completed due to a hardware error. */
	अगर (be32_to_cpu(rtas_args->rets[0]) == -1)
		buff_copy = __fetch_rtas_last_error(शून्य);

	अगर (nret > 1 && outमाला_दो != शून्य)
		क्रम (i = 0; i < nret-1; ++i)
			outमाला_दो[i] = be32_to_cpu(rtas_args->rets[i+1]);
	ret = (nret > 0)? be32_to_cpu(rtas_args->rets[0]): 0;

	unlock_rtas(s);

	अगर (buff_copy) अणु
		log_error(buff_copy, ERR_TYPE_RTAS_LOG, 0);
		अगर (slab_is_available())
			kमुक्त(buff_copy);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rtas_call);

/* For RTAS_BUSY (-2), delay क्रम 1 millisecond.  For an extended busy status
 * code of 990n, perक्रमm the hपूर्णांकed delay of 10^n (last digit) milliseconds.
 */
अचिन्हित पूर्णांक rtas_busy_delay_समय(पूर्णांक status)
अणु
	पूर्णांक order;
	अचिन्हित पूर्णांक ms = 0;

	अगर (status == RTAS_BUSY) अणु
		ms = 1;
	पूर्ण अन्यथा अगर (status >= RTAS_EXTENDED_DELAY_MIN &&
		   status <= RTAS_EXTENDED_DELAY_MAX) अणु
		order = status - RTAS_EXTENDED_DELAY_MIN;
		क्रम (ms = 1; order > 0; order--)
			ms *= 10;
	पूर्ण

	वापस ms;
पूर्ण
EXPORT_SYMBOL(rtas_busy_delay_समय);

/* For an RTAS busy status code, perक्रमm the hपूर्णांकed delay. */
अचिन्हित पूर्णांक rtas_busy_delay(पूर्णांक status)
अणु
	अचिन्हित पूर्णांक ms;

	might_sleep();
	ms = rtas_busy_delay_समय(status);
	अगर (ms && need_resched())
		msleep(ms);

	वापस ms;
पूर्ण
EXPORT_SYMBOL(rtas_busy_delay);

अटल पूर्णांक rtas_error_rc(पूर्णांक rtas_rc)
अणु
	पूर्णांक rc;

	चयन (rtas_rc) अणु
		हाल -1: 		/* Hardware Error */
			rc = -EIO;
			अवरोध;
		हाल -3:		/* Bad indicator/करोमुख्य/etc */
			rc = -EINVAL;
			अवरोध;
		हाल -9000:		/* Isolation error */
			rc = -EFAULT;
			अवरोध;
		हाल -9001:		/* Outstanding TCE/PTE */
			rc = -EEXIST;
			अवरोध;
		हाल -9002:		/* No usable slot */
			rc = -ENODEV;
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_ERR "%s: unexpected RTAS error %d\n",
					__func__, rtas_rc);
			rc = -दुस्फल;
			अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

पूर्णांक rtas_get_घातer_level(पूर्णांक घातerकरोमुख्य, पूर्णांक *level)
अणु
	पूर्णांक token = rtas_token("get-power-level");
	पूर्णांक rc;

	अगर (token == RTAS_UNKNOWN_SERVICE)
		वापस -ENOENT;

	जबतक ((rc = rtas_call(token, 1, 2, level, घातerकरोमुख्य)) == RTAS_BUSY)
		udelay(1);

	अगर (rc < 0)
		वापस rtas_error_rc(rc);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(rtas_get_घातer_level);

पूर्णांक rtas_set_घातer_level(पूर्णांक घातerकरोमुख्य, पूर्णांक level, पूर्णांक *setlevel)
अणु
	पूर्णांक token = rtas_token("set-power-level");
	पूर्णांक rc;

	अगर (token == RTAS_UNKNOWN_SERVICE)
		वापस -ENOENT;

	करो अणु
		rc = rtas_call(token, 2, 2, setlevel, घातerकरोमुख्य, level);
	पूर्ण जबतक (rtas_busy_delay(rc));

	अगर (rc < 0)
		वापस rtas_error_rc(rc);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(rtas_set_घातer_level);

पूर्णांक rtas_get_sensor(पूर्णांक sensor, पूर्णांक index, पूर्णांक *state)
अणु
	पूर्णांक token = rtas_token("get-sensor-state");
	पूर्णांक rc;

	अगर (token == RTAS_UNKNOWN_SERVICE)
		वापस -ENOENT;

	करो अणु
		rc = rtas_call(token, 2, 2, state, sensor, index);
	पूर्ण जबतक (rtas_busy_delay(rc));

	अगर (rc < 0)
		वापस rtas_error_rc(rc);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(rtas_get_sensor);

पूर्णांक rtas_get_sensor_fast(पूर्णांक sensor, पूर्णांक index, पूर्णांक *state)
अणु
	पूर्णांक token = rtas_token("get-sensor-state");
	पूर्णांक rc;

	अगर (token == RTAS_UNKNOWN_SERVICE)
		वापस -ENOENT;

	rc = rtas_call(token, 2, 2, state, sensor, index);
	WARN_ON(rc == RTAS_BUSY || (rc >= RTAS_EXTENDED_DELAY_MIN &&
				    rc <= RTAS_EXTENDED_DELAY_MAX));

	अगर (rc < 0)
		वापस rtas_error_rc(rc);
	वापस rc;
पूर्ण

bool rtas_indicator_present(पूर्णांक token, पूर्णांक *maxindex)
अणु
	पूर्णांक proplen, count, i;
	स्थिर काष्ठा indicator_elem अणु
		__be32 token;
		__be32 maxindex;
	पूर्ण *indicators;

	indicators = of_get_property(rtas.dev, "rtas-indicators", &proplen);
	अगर (!indicators)
		वापस false;

	count = proplen / माप(काष्ठा indicator_elem);

	क्रम (i = 0; i < count; i++) अणु
		अगर (__be32_to_cpu(indicators[i].token) != token)
			जारी;
		अगर (maxindex)
			*maxindex = __be32_to_cpu(indicators[i].maxindex);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण
EXPORT_SYMBOL(rtas_indicator_present);

पूर्णांक rtas_set_indicator(पूर्णांक indicator, पूर्णांक index, पूर्णांक new_value)
अणु
	पूर्णांक token = rtas_token("set-indicator");
	पूर्णांक rc;

	अगर (token == RTAS_UNKNOWN_SERVICE)
		वापस -ENOENT;

	करो अणु
		rc = rtas_call(token, 3, 1, शून्य, indicator, index, new_value);
	पूर्ण जबतक (rtas_busy_delay(rc));

	अगर (rc < 0)
		वापस rtas_error_rc(rc);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(rtas_set_indicator);

/*
 * Ignoring RTAS extended delay
 */
पूर्णांक rtas_set_indicator_fast(पूर्णांक indicator, पूर्णांक index, पूर्णांक new_value)
अणु
	पूर्णांक rc;
	पूर्णांक token = rtas_token("set-indicator");

	अगर (token == RTAS_UNKNOWN_SERVICE)
		वापस -ENOENT;

	rc = rtas_call(token, 3, 1, शून्य, indicator, index, new_value);

	WARN_ON(rc == RTAS_BUSY || (rc >= RTAS_EXTENDED_DELAY_MIN &&
				    rc <= RTAS_EXTENDED_DELAY_MAX));

	अगर (rc < 0)
		वापस rtas_error_rc(rc);

	वापस rc;
पूर्ण

/**
 * rtas_ibm_suspend_me() - Call ibm,suspend-me to suspend the LPAR.
 *
 * @fw_status: RTAS call status will be placed here अगर not शून्य.
 *
 * rtas_ibm_suspend_me() should be called only on a CPU which has
 * received H_CONTINUE from the H_JOIN hcall. All other active CPUs
 * should be रुकोing to वापस from H_JOIN.
 *
 * rtas_ibm_suspend_me() may suspend execution of the OS
 * indefinitely. Callers should take appropriate measures upon वापस, such as
 * resetting watchकरोg facilities.
 *
 * Callers may choose to retry this call अगर @fw_status is
 * %RTAS_THREADS_ACTIVE.
 *
 * Return:
 * 0          - The partition has resumed from suspend, possibly after
 *              migration to a dअगरferent host.
 * -ECANCELED - The operation was पातed.
 * -EAGAIN    - There were other CPUs not in H_JOIN at the समय of the call.
 * -EBUSY     - Some other condition prevented the suspend from succeeding.
 * -EIO       - Hardware/platक्रमm error.
 */
पूर्णांक rtas_ibm_suspend_me(पूर्णांक *fw_status)
अणु
	पूर्णांक fwrc;
	पूर्णांक ret;

	fwrc = rtas_call(rtas_token("ibm,suspend-me"), 0, 1, शून्य);

	चयन (fwrc) अणु
	हाल 0:
		ret = 0;
		अवरोध;
	हाल RTAS_SUSPEND_ABORTED:
		ret = -ECANCELED;
		अवरोध;
	हाल RTAS_THREADS_ACTIVE:
		ret = -EAGAIN;
		अवरोध;
	हाल RTAS_NOT_SUSPENDABLE:
	हाल RTAS_OUTSTANDING_COPROC:
		ret = -EBUSY;
		अवरोध;
	हाल -1:
	शेष:
		ret = -EIO;
		अवरोध;
	पूर्ण

	अगर (fw_status)
		*fw_status = fwrc;

	वापस ret;
पूर्ण

व्योम __noवापस rtas_restart(अक्षर *cmd)
अणु
	अगर (rtas_flash_term_hook)
		rtas_flash_term_hook(SYS_RESTART);
	prपूर्णांकk("RTAS system-reboot returned %d\n",
	       rtas_call(rtas_token("system-reboot"), 0, 1, शून्य));
	क्रम (;;);
पूर्ण

व्योम rtas_घातer_off(व्योम)
अणु
	अगर (rtas_flash_term_hook)
		rtas_flash_term_hook(SYS_POWER_OFF);
	/* allow घातer on only with घातer button press */
	prपूर्णांकk("RTAS power-off returned %d\n",
	       rtas_call(rtas_token("power-off"), 2, 1, शून्य, -1, -1));
	क्रम (;;);
पूर्ण

व्योम __noवापस rtas_halt(व्योम)
अणु
	अगर (rtas_flash_term_hook)
		rtas_flash_term_hook(SYS_HALT);
	/* allow घातer on only with घातer button press */
	prपूर्णांकk("RTAS power-off returned %d\n",
	       rtas_call(rtas_token("power-off"), 2, 1, शून्य, -1, -1));
	क्रम (;;);
पूर्ण

/* Must be in the RMO region, so we place it here */
अटल अक्षर rtas_os_term_buf[2048];

व्योम rtas_os_term(अक्षर *str)
अणु
	पूर्णांक status;

	/*
	 * Firmware with the ibm,extended-os-term property is guaranteed
	 * to always वापस from an ibm,os-term call. Earlier versions without
	 * this property may terminate the partition which we want to aव्योम
	 * since it पूर्णांकerferes with panic_समयout.
	 */
	अगर (RTAS_UNKNOWN_SERVICE == rtas_token("ibm,os-term") ||
	    RTAS_UNKNOWN_SERVICE == rtas_token("ibm,extended-os-term"))
		वापस;

	snम_लिखो(rtas_os_term_buf, 2048, "OS panic: %s", str);

	करो अणु
		status = rtas_call(rtas_token("ibm,os-term"), 1, 1, शून्य,
				   __pa(rtas_os_term_buf));
	पूर्ण जबतक (rtas_busy_delay(status));

	अगर (status != 0)
		prपूर्णांकk(KERN_EMERG "ibm,os-term call failed %d\n", status);
पूर्ण

/**
 * rtas_activate_firmware() - Activate a new version of firmware.
 *
 * Activate a new version of partition firmware. The OS must call this
 * after resuming from a partition hibernation or migration in order
 * to मुख्यtain the ability to perक्रमm live firmware updates. It's not
 * catastrophic क्रम this method to be असलent or to fail; just log the
 * condition in that हाल.
 *
 * Context: This function may sleep.
 */
व्योम rtas_activate_firmware(व्योम)
अणु
	पूर्णांक token;
	पूर्णांक fwrc;

	token = rtas_token("ibm,activate-firmware");
	अगर (token == RTAS_UNKNOWN_SERVICE) अणु
		pr_notice("ibm,activate-firmware method unavailable\n");
		वापस;
	पूर्ण

	करो अणु
		fwrc = rtas_call(token, 0, 1, शून्य);
	पूर्ण जबतक (rtas_busy_delay(fwrc));

	अगर (fwrc)
		pr_err("ibm,activate-firmware failed (%i)\n", fwrc);
पूर्ण

#अगर_घोषित CONFIG_PPC_PSERIES
/**
 * rtas_call_reentrant() - Used क्रम reentrant rtas calls
 * @token:	Token क्रम desired reentrant RTAS call
 * @nargs:	Number of Input Parameters
 * @nret:	Number of Output Parameters
 * @outमाला_दो:	Array of outमाला_दो
 * @...:	Inमाला_दो क्रम desired RTAS call
 *
 * According to LoPAR करोcumentation, only "ibm,int-on", "ibm,int-off",
 * "ibm,get-xive" and "ibm,set-xive" are currently reentrant.
 * Reentrant calls need their own rtas_args buffer, so not using rtas.args, but
 * PACA one instead.
 *
 * Return:	-1 on error,
 *		First output value of RTAS call अगर (nret > 0),
 *		0 otherwise,
 */
पूर्णांक rtas_call_reentrant(पूर्णांक token, पूर्णांक nargs, पूर्णांक nret, पूर्णांक *outमाला_दो, ...)
अणु
	बहु_सूची list;
	काष्ठा rtas_args *args;
	अचिन्हित दीर्घ flags;
	पूर्णांक i, ret = 0;

	अगर (!rtas.entry || token == RTAS_UNKNOWN_SERVICE)
		वापस -1;

	local_irq_save(flags);
	preempt_disable();

	/* We use the per-cpu (PACA) rtas args buffer */
	args = local_paca->rtas_args_reentrant;

	बहु_शुरू(list, outमाला_दो);
	va_rtas_call_unlocked(args, token, nargs, nret, list);
	बहु_पूर्ण(list);

	अगर (nret > 1 && outमाला_दो)
		क्रम (i = 0; i < nret - 1; ++i)
			outमाला_दो[i] = be32_to_cpu(args->rets[i + 1]);

	अगर (nret > 0)
		ret = be32_to_cpu(args->rets[0]);

	local_irq_restore(flags);
	preempt_enable();

	वापस ret;
पूर्ण

#पूर्ण_अगर /* CONFIG_PPC_PSERIES */

/**
 * Find a specअगरic pseries error log in an RTAS extended event log.
 * @log: RTAS error/event log
 * @section_id: two अक्षरacter section identअगरier
 *
 * Returns a poपूर्णांकer to the specअगरied errorlog or शून्य अगर not found.
 */
काष्ठा pseries_errorlog *get_pseries_errorlog(काष्ठा rtas_error_log *log,
					      uपूर्णांक16_t section_id)
अणु
	काष्ठा rtas_ext_event_log_v6 *ext_log =
		(काष्ठा rtas_ext_event_log_v6 *)log->buffer;
	काष्ठा pseries_errorlog *sect;
	अचिन्हित अक्षर *p, *log_end;
	uपूर्णांक32_t ext_log_length = rtas_error_extended_log_length(log);
	uपूर्णांक8_t log_क्रमmat = rtas_ext_event_log_क्रमmat(ext_log);
	uपूर्णांक32_t company_id = rtas_ext_event_company_id(ext_log);

	/* Check that we understand the क्रमmat */
	अगर (ext_log_length < माप(काष्ठा rtas_ext_event_log_v6) ||
	    log_क्रमmat != RTAS_V6EXT_LOG_FORMAT_EVENT_LOG ||
	    company_id != RTAS_V6EXT_COMPANY_ID_IBM)
		वापस शून्य;

	log_end = log->buffer + ext_log_length;
	p = ext_log->venकरोr_log;

	जबतक (p < log_end) अणु
		sect = (काष्ठा pseries_errorlog *)p;
		अगर (pseries_errorlog_id(sect) == section_id)
			वापस sect;
		p += pseries_errorlog_length(sect);
	पूर्ण

	वापस शून्य;
पूर्ण

#अगर_घोषित CONFIG_PPC_RTAS_FILTER

/*
 * The sys_rtas syscall, as originally deचिन्हित, allows root to pass
 * arbitrary physical addresses to RTAS calls. A number of RTAS calls
 * can be abused to ग_लिखो to arbitrary memory and करो other things that
 * are potentially harmful to प्रणाली पूर्णांकegrity, and thus should only
 * be used inside the kernel and not exposed to userspace.
 *
 * All known legitimate users of the sys_rtas syscall will only ever
 * pass addresses that fall within the RMO buffer, and use a known
 * subset of RTAS calls.
 *
 * Accordingly, we filter RTAS requests to check that the call is
 * permitted, and that provided poपूर्णांकers fall within the RMO buffer.
 * The rtas_filters list contains an entry क्रम each permitted call,
 * with the indexes of the parameters which are expected to contain
 * addresses and sizes of buffers allocated inside the RMO buffer.
 */
काष्ठा rtas_filter अणु
	स्थिर अक्षर *name;
	पूर्णांक token;
	/* Indexes पूर्णांकo the args buffer, -1 अगर not used */
	पूर्णांक buf_idx1;
	पूर्णांक size_idx1;
	पूर्णांक buf_idx2;
	पूर्णांक size_idx2;

	पूर्णांक fixed_size;
पूर्ण;

अटल काष्ठा rtas_filter rtas_filters[] __ro_after_init = अणु
	अणु "ibm,activate-firmware", -1, -1, -1, -1, -1 पूर्ण,
	अणु "ibm,configure-connector", -1, 0, -1, 1, -1, 4096 पूर्ण,	/* Special हालd */
	अणु "display-character", -1, -1, -1, -1, -1 पूर्ण,
	अणु "ibm,display-message", -1, 0, -1, -1, -1 पूर्ण,
	अणु "ibm,errinjct", -1, 2, -1, -1, -1, 1024 पूर्ण,
	अणु "ibm,close-errinjct", -1, -1, -1, -1, -1 पूर्ण,
	अणु "ibm,open-errinjct", -1, -1, -1, -1, -1 पूर्ण,
	अणु "ibm,get-config-addr-info2", -1, -1, -1, -1, -1 पूर्ण,
	अणु "ibm,get-dynamic-sensor-state", -1, 1, -1, -1, -1 पूर्ण,
	अणु "ibm,get-indices", -1, 2, 3, -1, -1 पूर्ण,
	अणु "get-power-level", -1, -1, -1, -1, -1 पूर्ण,
	अणु "get-sensor-state", -1, -1, -1, -1, -1 पूर्ण,
	अणु "ibm,get-system-parameter", -1, 1, 2, -1, -1 पूर्ण,
	अणु "get-time-of-day", -1, -1, -1, -1, -1 पूर्ण,
	अणु "ibm,get-vpd", -1, 0, -1, 1, 2 पूर्ण,
	अणु "ibm,lpar-perftools", -1, 2, 3, -1, -1 पूर्ण,
	अणु "ibm,platform-dump", -1, 4, 5, -1, -1 पूर्ण,
	अणु "ibm,read-slot-reset-state", -1, -1, -1, -1, -1 पूर्ण,
	अणु "ibm,scan-log-dump", -1, 0, 1, -1, -1 पूर्ण,
	अणु "ibm,set-dynamic-indicator", -1, 2, -1, -1, -1 पूर्ण,
	अणु "ibm,set-eeh-option", -1, -1, -1, -1, -1 पूर्ण,
	अणु "set-indicator", -1, -1, -1, -1, -1 पूर्ण,
	अणु "set-power-level", -1, -1, -1, -1, -1 पूर्ण,
	अणु "set-time-for-power-on", -1, -1, -1, -1, -1 पूर्ण,
	अणु "ibm,set-system-parameter", -1, 1, -1, -1, -1 पूर्ण,
	अणु "set-time-of-day", -1, -1, -1, -1, -1 पूर्ण,
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	अणु "ibm,suspend-me", -1, -1, -1, -1, -1 पूर्ण,
	अणु "ibm,update-nodes", -1, 0, -1, -1, -1, 4096 पूर्ण,
	अणु "ibm,update-properties", -1, 0, -1, -1, -1, 4096 पूर्ण,
#पूर्ण_अगर
	अणु "ibm,physical-attestation", -1, 0, 1, -1, -1 पूर्ण,
पूर्ण;

अटल bool in_rmo_buf(u32 base, u32 end)
अणु
	वापस base >= rtas_rmo_buf &&
		base < (rtas_rmo_buf + RTAS_USER_REGION_SIZE) &&
		base <= end &&
		end >= rtas_rmo_buf &&
		end < (rtas_rmo_buf + RTAS_USER_REGION_SIZE);
पूर्ण

अटल bool block_rtas_call(पूर्णांक token, पूर्णांक nargs,
			    काष्ठा rtas_args *args)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rtas_filters); i++) अणु
		काष्ठा rtas_filter *f = &rtas_filters[i];
		u32 base, size, end;

		अगर (token != f->token)
			जारी;

		अगर (f->buf_idx1 != -1) अणु
			base = be32_to_cpu(args->args[f->buf_idx1]);
			अगर (f->size_idx1 != -1)
				size = be32_to_cpu(args->args[f->size_idx1]);
			अन्यथा अगर (f->fixed_size)
				size = f->fixed_size;
			अन्यथा
				size = 1;

			end = base + size - 1;
			अगर (!in_rmo_buf(base, end))
				जाओ err;
		पूर्ण

		अगर (f->buf_idx2 != -1) अणु
			base = be32_to_cpu(args->args[f->buf_idx2]);
			अगर (f->size_idx2 != -1)
				size = be32_to_cpu(args->args[f->size_idx2]);
			अन्यथा अगर (f->fixed_size)
				size = f->fixed_size;
			अन्यथा
				size = 1;
			end = base + size - 1;

			/*
			 * Special हाल क्रम ibm,configure-connector where the
			 * address can be 0
			 */
			अगर (!म_भेद(f->name, "ibm,configure-connector") &&
			    base == 0)
				वापस false;

			अगर (!in_rmo_buf(base, end))
				जाओ err;
		पूर्ण

		वापस false;
	पूर्ण

err:
	pr_err_ratelimited("sys_rtas: RTAS call blocked - exploit attempt?\n");
	pr_err_ratelimited("sys_rtas: token=0x%x, nargs=%d (called by %s)\n",
			   token, nargs, current->comm);
	वापस true;
पूर्ण

अटल व्योम __init rtas_syscall_filter_init(व्योम)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(rtas_filters); i++)
		rtas_filters[i].token = rtas_token(rtas_filters[i].name);
पूर्ण

#अन्यथा

अटल bool block_rtas_call(पूर्णांक token, पूर्णांक nargs,
			    काष्ठा rtas_args *args)
अणु
	वापस false;
पूर्ण

अटल व्योम __init rtas_syscall_filter_init(व्योम)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_PPC_RTAS_FILTER */

/* We assume to be passed big endian arguments */
SYSCALL_DEFINE1(rtas, काष्ठा rtas_args __user *, uargs)
अणु
	काष्ठा rtas_args args;
	अचिन्हित दीर्घ flags;
	अक्षर *buff_copy, *errbuf = शून्य;
	पूर्णांक nargs, nret, token;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (!rtas.entry)
		वापस -EINVAL;

	अगर (copy_from_user(&args, uargs, 3 * माप(u32)) != 0)
		वापस -EFAULT;

	nargs = be32_to_cpu(args.nargs);
	nret  = be32_to_cpu(args.nret);
	token = be32_to_cpu(args.token);

	अगर (nargs >= ARRAY_SIZE(args.args)
	    || nret > ARRAY_SIZE(args.args)
	    || nargs + nret > ARRAY_SIZE(args.args))
		वापस -EINVAL;

	/* Copy in args. */
	अगर (copy_from_user(args.args, uargs->args,
			   nargs * माप(rtas_arg_t)) != 0)
		वापस -EFAULT;

	अगर (token == RTAS_UNKNOWN_SERVICE)
		वापस -EINVAL;

	args.rets = &args.args[nargs];
	स_रखो(args.rets, 0, nret * माप(rtas_arg_t));

	अगर (block_rtas_call(token, nargs, &args))
		वापस -EINVAL;

	/* Need to handle ibm,suspend_me call specially */
	अगर (token == rtas_token("ibm,suspend-me")) अणु

		/*
		 * rtas_ibm_suspend_me assumes the streamid handle is in cpu
		 * endian, or at least the hcall within it requires it.
		 */
		पूर्णांक rc = 0;
		u64 handle = ((u64)be32_to_cpu(args.args[0]) << 32)
		              | be32_to_cpu(args.args[1]);
		rc = rtas_syscall_dispatch_ibm_suspend_me(handle);
		अगर (rc == -EAGAIN)
			args.rets[0] = cpu_to_be32(RTAS_NOT_SUSPENDABLE);
		अन्यथा अगर (rc == -EIO)
			args.rets[0] = cpu_to_be32(-1);
		अन्यथा अगर (rc)
			वापस rc;
		जाओ copy_वापस;
	पूर्ण

	buff_copy = get_errorlog_buffer();

	flags = lock_rtas();

	rtas.args = args;
	enter_rtas(__pa(&rtas.args));
	args = rtas.args;

	/* A -1 वापस code indicates that the last command couldn't
	   be completed due to a hardware error. */
	अगर (be32_to_cpu(args.rets[0]) == -1)
		errbuf = __fetch_rtas_last_error(buff_copy);

	unlock_rtas(flags);

	अगर (buff_copy) अणु
		अगर (errbuf)
			log_error(errbuf, ERR_TYPE_RTAS_LOG, 0);
		kमुक्त(buff_copy);
	पूर्ण

 copy_वापस:
	/* Copy out args. */
	अगर (copy_to_user(uargs->args + nargs,
			 args.args + nargs,
			 nret * माप(rtas_arg_t)) != 0)
		वापस -EFAULT;

	वापस 0;
पूर्ण

/*
 * Call early during boot, beक्रमe mem init, to retrieve the RTAS
 * inक्रमmation from the device-tree and allocate the RMO buffer क्रम userland
 * accesses.
 */
व्योम __init rtas_initialize(व्योम)
अणु
	अचिन्हित दीर्घ rtas_region = RTAS_INSTANTIATE_MAX;
	u32 base, size, entry;
	पूर्णांक no_base, no_size, no_entry;

	/* Get RTAS dev node and fill up our "rtas" काष्ठाure with infos
	 * about it.
	 */
	rtas.dev = of_find_node_by_name(शून्य, "rtas");
	अगर (!rtas.dev)
		वापस;

	no_base = of_property_पढ़ो_u32(rtas.dev, "linux,rtas-base", &base);
	no_size = of_property_पढ़ो_u32(rtas.dev, "rtas-size", &size);
	अगर (no_base || no_size) अणु
		of_node_put(rtas.dev);
		rtas.dev = शून्य;
		वापस;
	पूर्ण

	rtas.base = base;
	rtas.size = size;
	no_entry = of_property_पढ़ो_u32(rtas.dev, "linux,rtas-entry", &entry);
	rtas.entry = no_entry ? rtas.base : entry;

	/* If RTAS was found, allocate the RMO buffer क्रम it and look क्रम
	 * the stop-self token अगर any
	 */
#अगर_घोषित CONFIG_PPC64
	अगर (firmware_has_feature(FW_FEATURE_LPAR))
		rtas_region = min(ppc64_rma_size, RTAS_INSTANTIATE_MAX);
#पूर्ण_अगर
	rtas_rmo_buf = memblock_phys_alloc_range(RTAS_USER_REGION_SIZE, PAGE_SIZE,
						 0, rtas_region);
	अगर (!rtas_rmo_buf)
		panic("ERROR: RTAS: Failed to allocate %lx bytes below %pa\n",
		      PAGE_SIZE, &rtas_region);

#अगर_घोषित CONFIG_RTAS_ERROR_LOGGING
	rtas_last_error_token = rtas_token("rtas-last-error");
#पूर्ण_अगर

	rtas_syscall_filter_init();
पूर्ण

पूर्णांक __init early_init_dt_scan_rtas(अचिन्हित दीर्घ node,
		स्थिर अक्षर *uname, पूर्णांक depth, व्योम *data)
अणु
	स्थिर u32 *basep, *entryp, *sizep;

	अगर (depth != 1 || म_भेद(uname, "rtas") != 0)
		वापस 0;

	basep  = of_get_flat_dt_prop(node, "linux,rtas-base", शून्य);
	entryp = of_get_flat_dt_prop(node, "linux,rtas-entry", शून्य);
	sizep  = of_get_flat_dt_prop(node, "rtas-size", शून्य);

	अगर (basep && entryp && sizep) अणु
		rtas.base = *basep;
		rtas.entry = *entryp;
		rtas.size = *sizep;
	पूर्ण

#अगर_घोषित CONFIG_UDBG_RTAS_CONSOLE
	basep = of_get_flat_dt_prop(node, "put-term-char", शून्य);
	अगर (basep)
		rtas_अक्षर_दो_token = *basep;

	basep = of_get_flat_dt_prop(node, "get-term-char", शून्य);
	अगर (basep)
		rtas_अक्षर_लो_token = *basep;

	अगर (rtas_अक्षर_दो_token != RTAS_UNKNOWN_SERVICE &&
	    rtas_अक्षर_लो_token != RTAS_UNKNOWN_SERVICE)
		udbg_init_rtas_console();

#पूर्ण_अगर

	/* अवरोध now */
	वापस 1;
पूर्ण

अटल arch_spinlock_t समयbase_lock;
अटल u64 समयbase = 0;

व्योम rtas_give_समयbase(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	hard_irq_disable();
	arch_spin_lock(&समयbase_lock);
	rtas_call(rtas_token("freeze-time-base"), 0, 1, शून्य);
	समयbase = get_tb();
	arch_spin_unlock(&समयbase_lock);

	जबतक (समयbase)
		barrier();
	rtas_call(rtas_token("thaw-time-base"), 0, 1, शून्य);
	local_irq_restore(flags);
पूर्ण

व्योम rtas_take_समयbase(व्योम)
अणु
	जबतक (!समयbase)
		barrier();
	arch_spin_lock(&समयbase_lock);
	set_tb(समयbase >> 32, समयbase & 0xffffffff);
	समयbase = 0;
	arch_spin_unlock(&समयbase_lock);
पूर्ण
