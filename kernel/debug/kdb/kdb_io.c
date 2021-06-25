<शैली गुरु>
/*
 * Kernel Debugger Architecture Independent Console I/O handler
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (c) 1999-2006 Silicon Graphics, Inc.  All Rights Reserved.
 * Copyright (c) 2009 Wind River Systems, Inc.  All Rights Reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/console.h>
#समावेश <linux/माला.स>
#समावेश <linux/sched.h>
#समावेश <linux/smp.h>
#समावेश <linux/nmi.h>
#समावेश <linux/delay.h>
#समावेश <linux/kgdb.h>
#समावेश <linux/kdb.h>
#समावेश <linux/kallsyms.h>
#समावेश "kdb_private.h"

#घोषणा CMD_BUFLEN 256
अक्षर kdb_prompt_str[CMD_BUFLEN];

पूर्णांक kdb_trap_prपूर्णांकk;
पूर्णांक kdb_म_लिखो_cpu = -1;

अटल पूर्णांक kgdb_transition_check(अक्षर *buffer)
अणु
	अगर (buffer[0] != '+' && buffer[0] != '$') अणु
		KDB_STATE_SET(KGDB_TRANS);
		kdb_म_लिखो("%s", buffer);
	पूर्ण अन्यथा अणु
		पूर्णांक slen = म_माप(buffer);
		अगर (slen > 3 && buffer[slen - 3] == '#') अणु
			kdb_gdb_state_pass(buffer);
			म_नकल(buffer, "kgdb");
			KDB_STATE_SET(DOING_KGDB);
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/**
 * kdb_handle_escape() - validity check on an accumulated escape sequence.
 * @buf:	Accumulated escape अक्षरacters to be examined. Note that buf
 *		is not a string, it is an array of अक्षरacters and need not be
 *		nil terminated.
 * @sz:		Number of accumulated escape अक्षरacters.
 *
 * Return: -1 अगर the escape sequence is unwanted, 0 अगर it is incomplete,
 * otherwise it वापसs a mapped key value to pass to the upper layers.
 */
अटल पूर्णांक kdb_handle_escape(अक्षर *buf, माप_प्रकार sz)
अणु
	अक्षर *lastkey = buf + sz - 1;

	चयन (sz) अणु
	हाल 1:
		अगर (*lastkey == '\e')
			वापस 0;
		अवरोध;

	हाल 2: /* \e<something> */
		अगर (*lastkey == '[')
			वापस 0;
		अवरोध;

	हाल 3:
		चयन (*lastkey) अणु
		हाल 'A': /* \e[A, up arrow */
			वापस 16;
		हाल 'B': /* \e[B, करोwn arrow */
			वापस 14;
		हाल 'C': /* \e[C, right arrow */
			वापस 6;
		हाल 'D': /* \e[D, left arrow */
			वापस 2;
		हाल '1': /* \e[<1,3,4>], may be home, del, end */
		हाल '3':
		हाल '4':
			वापस 0;
		पूर्ण
		अवरोध;

	हाल 4:
		अगर (*lastkey == '~') अणु
			चयन (buf[2]) अणु
			हाल '1': /* \e[1~, home */
				वापस 1;
			हाल '3': /* \e[3~, del */
				वापस 4;
			हाल '4': /* \e[4~, end */
				वापस 5;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

	वापस -1;
पूर्ण

/**
 * kdb_अक्षर_लो() - Read a single अक्षरacter from a kdb console (or consoles).
 *
 * Other than polling the various consoles that are currently enabled,
 * most of the work करोne in this function is dealing with escape sequences.
 *
 * An escape key could be the start of a vt100 control sequence such as \e[D
 * (left arrow) or it could be a अक्षरacter in its own right.  The standard
 * method क्रम detecting the dअगरference is to रुको क्रम 2 seconds to see अगर there
 * are any other अक्षरacters.  kdb is complicated by the lack of a समयr service
 * (पूर्णांकerrupts are off), by multiple input sources. Escape sequence processing
 * has to be करोne as states in the polling loop.
 *
 * Return: The key pressed or a control code derived from an escape sequence.
 */
अक्षर kdb_अक्षर_लो(व्योम)
अणु
#घोषणा ESCAPE_UDELAY 1000
#घोषणा ESCAPE_DELAY (2*1000000/ESCAPE_UDELAY) /* 2 seconds worth of udelays */
	अक्षर buf[4];	/* दीर्घest vt100 escape sequence is 4 bytes */
	अक्षर *pbuf = buf;
	पूर्णांक escape_delay = 0;
	get_अक्षर_func *f, *f_prev = शून्य;
	पूर्णांक key;

	क्रम (f = &kdb_poll_funcs[0]; ; ++f) अणु
		अगर (*f == शून्य) अणु
			/* Reset NMI watchकरोg once per poll loop */
			touch_nmi_watchकरोg();
			f = &kdb_poll_funcs[0];
		पूर्ण

		key = (*f)();
		अगर (key == -1) अणु
			अगर (escape_delay) अणु
				udelay(ESCAPE_UDELAY);
				अगर (--escape_delay == 0)
					वापस '\e';
			पूर्ण
			जारी;
		पूर्ण

		/*
		 * When the first अक्षरacter is received (or we get a change
		 * input source) we set ourselves up to handle an escape
		 * sequences (just in हाल).
		 */
		अगर (f_prev != f) अणु
			f_prev = f;
			pbuf = buf;
			escape_delay = ESCAPE_DELAY;
		पूर्ण

		*pbuf++ = key;
		key = kdb_handle_escape(buf, pbuf - buf);
		अगर (key < 0) /* no escape sequence; वापस best अक्षरacter */
			वापस buf[pbuf - buf == 2 ? 1 : 0];
		अगर (key > 0)
			वापस key;
	पूर्ण

	unreachable();
पूर्ण

/*
 * kdb_पढ़ो
 *
 *	This function पढ़ोs a string of अक्षरacters, terminated by
 *	a newline, or by reaching the end of the supplied buffer,
 *	from the current kernel debugger console device.
 * Parameters:
 *	buffer	- Address of अक्षरacter buffer to receive input अक्षरacters.
 *	bufsize - size, in bytes, of the अक्षरacter buffer
 * Returns:
 *	Returns a poपूर्णांकer to the buffer containing the received
 *	अक्षरacter string.  This string will be terminated by a
 *	newline अक्षरacter.
 * Locking:
 *	No locks are required to be held upon entry to this
 *	function.  It is not reentrant - it relies on the fact
 *	that जबतक kdb is running on only one "master debug" cpu.
 * Remarks:
 *	The buffer size must be >= 2.
 */

अटल अक्षर *kdb_पढ़ो(अक्षर *buffer, माप_प्रकार bufsize)
अणु
	अक्षर *cp = buffer;
	अक्षर *bufend = buffer+bufsize-2;	/* Reserve space क्रम newline
						 * and null byte */
	अक्षर *lastअक्षर;
	अक्षर *p_पंचांगp;
	अक्षर पंचांगp;
	अटल अक्षर पंचांगpbuffer[CMD_BUFLEN];
	पूर्णांक len = म_माप(buffer);
	पूर्णांक len_पंचांगp;
	पूर्णांक tab = 0;
	पूर्णांक count;
	पूर्णांक i;
	पूर्णांक diag, dtab_count;
	पूर्णांक key, buf_size, ret;


	diag = kdbgetपूर्णांकenv("DTABCOUNT", &dtab_count);
	अगर (diag)
		dtab_count = 30;

	अगर (len > 0) अणु
		cp += len;
		अगर (*(buffer+len-1) == '\n')
			cp--;
	पूर्ण

	lastअक्षर = cp;
	*cp = '\0';
	kdb_म_लिखो("%s", buffer);
poll_again:
	key = kdb_अक्षर_लो();
	अगर (key != 9)
		tab = 0;
	चयन (key) अणु
	हाल 8: /* backspace */
		अगर (cp > buffer) अणु
			अगर (cp < lastअक्षर) अणु
				स_नकल(पंचांगpbuffer, cp, lastअक्षर - cp);
				स_नकल(cp-1, पंचांगpbuffer, lastअक्षर - cp);
			पूर्ण
			*(--lastअक्षर) = '\0';
			--cp;
			kdb_म_लिखो("\b%s \r", cp);
			पंचांगp = *cp;
			*cp = '\0';
			kdb_म_लिखो(kdb_prompt_str);
			kdb_म_लिखो("%s", buffer);
			*cp = पंचांगp;
		पूर्ण
		अवरोध;
	हाल 13: /* enter */
		*lastअक्षर++ = '\n';
		*lastअक्षर++ = '\0';
		अगर (!KDB_STATE(KGDB_TRANS)) अणु
			KDB_STATE_SET(KGDB_TRANS);
			kdb_म_लिखो("%s", buffer);
		पूर्ण
		kdb_म_लिखो("\n");
		वापस buffer;
	हाल 4: /* Del */
		अगर (cp < lastअक्षर) अणु
			स_नकल(पंचांगpbuffer, cp+1, lastअक्षर - cp - 1);
			स_नकल(cp, पंचांगpbuffer, lastअक्षर - cp - 1);
			*(--lastअक्षर) = '\0';
			kdb_म_लिखो("%s \r", cp);
			पंचांगp = *cp;
			*cp = '\0';
			kdb_म_लिखो(kdb_prompt_str);
			kdb_म_लिखो("%s", buffer);
			*cp = पंचांगp;
		पूर्ण
		अवरोध;
	हाल 1: /* Home */
		अगर (cp > buffer) अणु
			kdb_म_लिखो("\r");
			kdb_म_लिखो(kdb_prompt_str);
			cp = buffer;
		पूर्ण
		अवरोध;
	हाल 5: /* End */
		अगर (cp < lastअक्षर) अणु
			kdb_म_लिखो("%s", cp);
			cp = lastअक्षर;
		पूर्ण
		अवरोध;
	हाल 2: /* Left */
		अगर (cp > buffer) अणु
			kdb_म_लिखो("\b");
			--cp;
		पूर्ण
		अवरोध;
	हाल 14: /* Down */
		स_रखो(पंचांगpbuffer, ' ',
		       म_माप(kdb_prompt_str) + (lastअक्षर-buffer));
		*(पंचांगpbuffer+म_माप(kdb_prompt_str) +
		  (lastअक्षर-buffer)) = '\0';
		kdb_म_लिखो("\r%s\r", पंचांगpbuffer);
		*lastअक्षर = (अक्षर)key;
		*(lastअक्षर+1) = '\0';
		वापस lastअक्षर;
	हाल 6: /* Right */
		अगर (cp < lastअक्षर) अणु
			kdb_म_लिखो("%c", *cp);
			++cp;
		पूर्ण
		अवरोध;
	हाल 16: /* Up */
		स_रखो(पंचांगpbuffer, ' ',
		       म_माप(kdb_prompt_str) + (lastअक्षर-buffer));
		*(पंचांगpbuffer+म_माप(kdb_prompt_str) +
		  (lastअक्षर-buffer)) = '\0';
		kdb_म_लिखो("\r%s\r", पंचांगpbuffer);
		*lastअक्षर = (अक्षर)key;
		*(lastअक्षर+1) = '\0';
		वापस lastअक्षर;
	हाल 9: /* Tab */
		अगर (tab < 2)
			++tab;
		p_पंचांगp = buffer;
		जबतक (*p_पंचांगp == ' ')
			p_पंचांगp++;
		अगर (p_पंचांगp > cp)
			अवरोध;
		स_नकल(पंचांगpbuffer, p_पंचांगp, cp-p_पंचांगp);
		*(पंचांगpbuffer + (cp-p_पंचांगp)) = '\0';
		p_पंचांगp = म_खोजप(पंचांगpbuffer, ' ');
		अगर (p_पंचांगp)
			++p_पंचांगp;
		अन्यथा
			p_पंचांगp = पंचांगpbuffer;
		len = म_माप(p_पंचांगp);
		buf_size = माप(पंचांगpbuffer) - (p_पंचांगp - पंचांगpbuffer);
		count = kallsyms_symbol_complete(p_पंचांगp, buf_size);
		अगर (tab == 2 && count > 0) अणु
			kdb_म_लिखो("\n%d symbols are found.", count);
			अगर (count > dtab_count) अणु
				count = dtab_count;
				kdb_म_लिखो(" But only first %d symbols will"
					   " be printed.\nYou can change the"
					   " environment variable DTABCOUNT.",
					   count);
			पूर्ण
			kdb_म_लिखो("\n");
			क्रम (i = 0; i < count; i++) अणु
				ret = kallsyms_symbol_next(p_पंचांगp, i, buf_size);
				अगर (WARN_ON(!ret))
					अवरोध;
				अगर (ret != -E2BIG)
					kdb_म_लिखो("%s ", p_पंचांगp);
				अन्यथा
					kdb_म_लिखो("%s... ", p_पंचांगp);
				*(p_पंचांगp + len) = '\0';
			पूर्ण
			अगर (i >= dtab_count)
				kdb_म_लिखो("...");
			kdb_म_लिखो("\n");
			kdb_म_लिखो(kdb_prompt_str);
			kdb_म_लिखो("%s", buffer);
		पूर्ण अन्यथा अगर (tab != 2 && count > 0) अणु
			len_पंचांगp = म_माप(p_पंचांगp);
			म_नकलन(p_पंचांगp+len_पंचांगp, cp, lastअक्षर-cp+1);
			len_पंचांगp = म_माप(p_पंचांगp);
			म_नकलन(cp, p_पंचांगp+len, len_पंचांगp-len + 1);
			len = len_पंचांगp - len;
			kdb_म_लिखो("%s", cp);
			cp += len;
			lastअक्षर += len;
		पूर्ण
		kdb_nextline = 1; /* reset output line number */
		अवरोध;
	शेष:
		अगर (key >= 32 && lastअक्षर < bufend) अणु
			अगर (cp < lastअक्षर) अणु
				स_नकल(पंचांगpbuffer, cp, lastअक्षर - cp);
				स_नकल(cp+1, पंचांगpbuffer, lastअक्षर - cp);
				*++lastअक्षर = '\0';
				*cp = key;
				kdb_म_लिखो("%s\r", cp);
				++cp;
				पंचांगp = *cp;
				*cp = '\0';
				kdb_म_लिखो(kdb_prompt_str);
				kdb_म_लिखो("%s", buffer);
				*cp = पंचांगp;
			पूर्ण अन्यथा अणु
				*++lastअक्षर = '\0';
				*cp++ = key;
				/* The kgdb transition check will hide
				 * prपूर्णांकed अक्षरacters अगर we think that
				 * kgdb is connecting, until the check
				 * fails */
				अगर (!KDB_STATE(KGDB_TRANS)) अणु
					अगर (kgdb_transition_check(buffer))
						वापस buffer;
				पूर्ण अन्यथा अणु
					kdb_म_लिखो("%c", key);
				पूर्ण
			पूर्ण
			/* Special escape to kgdb */
			अगर (lastअक्षर - buffer >= 5 &&
			    म_भेद(lastअक्षर - 5, "$?#3f") == 0) अणु
				kdb_gdb_state_pass(lastअक्षर - 5);
				म_नकल(buffer, "kgdb");
				KDB_STATE_SET(DOING_KGDB);
				वापस buffer;
			पूर्ण
			अगर (lastअक्षर - buffer >= 11 &&
			    म_भेद(lastअक्षर - 11, "$qSupported") == 0) अणु
				kdb_gdb_state_pass(lastअक्षर - 11);
				म_नकल(buffer, "kgdb");
				KDB_STATE_SET(DOING_KGDB);
				वापस buffer;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
	जाओ poll_again;
पूर्ण

/*
 * kdb_माला_लोtr
 *
 *	Prपूर्णांक the prompt string and पढ़ो a command from the
 *	input device.
 *
 * Parameters:
 *	buffer	Address of buffer to receive command
 *	bufsize Size of buffer in bytes
 *	prompt	Poपूर्णांकer to string to use as prompt string
 * Returns:
 *	Poपूर्णांकer to command buffer.
 * Locking:
 *	None.
 * Remarks:
 *	For SMP kernels, the processor number will be
 *	substituted क्रम %d, %x or %o in the prompt.
 */

अक्षर *kdb_माला_लोtr(अक्षर *buffer, माप_प्रकार bufsize, स्थिर अक्षर *prompt)
अणु
	अगर (prompt && kdb_prompt_str != prompt)
		strscpy(kdb_prompt_str, prompt, CMD_BUFLEN);
	kdb_म_लिखो(kdb_prompt_str);
	kdb_nextline = 1;	/* Prompt and input resets line number */
	वापस kdb_पढ़ो(buffer, bufsize);
पूर्ण

/*
 * kdb_input_flush
 *
 *	Get rid of any buffered console input.
 *
 * Parameters:
 *	none
 * Returns:
 *	nothing
 * Locking:
 *	none
 * Remarks:
 *	Call this function whenever you want to flush input.  If there is any
 *	outstanding input, it ignores all अक्षरacters until there has been no
 *	data क्रम approximately 1ms.
 */

अटल व्योम kdb_input_flush(व्योम)
अणु
	get_अक्षर_func *f;
	पूर्णांक res;
	पूर्णांक flush_delay = 1;
	जबतक (flush_delay) अणु
		flush_delay--;
empty:
		touch_nmi_watchकरोg();
		क्रम (f = &kdb_poll_funcs[0]; *f; ++f) अणु
			res = (*f)();
			अगर (res != -1) अणु
				flush_delay = 1;
				जाओ empty;
			पूर्ण
		पूर्ण
		अगर (flush_delay)
			mdelay(1);
	पूर्ण
पूर्ण

/*
 * kdb_म_लिखो
 *
 *	Prपूर्णांक a string to the output device(s).
 *
 * Parameters:
 *	म_लिखो-like क्रमmat and optional args.
 * Returns:
 *	0
 * Locking:
 *	None.
 * Remarks:
 *	use 'kdbcons->write()' to avoid polluting 'log_buf' with
 *	kdb output.
 *
 *  If the user is करोing a cmd args | grep srch
 *  then kdb_grepping_flag is set.
 *  In that हाल we need to accumulate full lines (ending in \न) beक्रमe
 *  searching क्रम the pattern.
 */

अटल अक्षर kdb_buffer[256];	/* A bit too big to go on stack */
अटल अक्षर *next_avail = kdb_buffer;
अटल पूर्णांक  size_avail;
अटल पूर्णांक  suspend_grep;

/*
 * search arg1 to see अगर it contains arg2
 * (kdमुख्य.c provides flags क्रम ^pat and pat$)
 *
 * वापस 1 क्रम found, 0 क्रम not found
 */
अटल पूर्णांक kdb_search_string(अक्षर *searched, अक्षर *searchक्रम)
अणु
	अक्षर firstअक्षर, *cp;
	पूर्णांक len1, len2;

	/* not counting the newline at the end of "searched" */
	len1 = म_माप(searched)-1;
	len2 = म_माप(searchक्रम);
	अगर (len1 < len2)
		वापस 0;
	अगर (kdb_grep_leading && kdb_grep_trailing && len1 != len2)
		वापस 0;
	अगर (kdb_grep_leading) अणु
		अगर (!म_भेदन(searched, searchक्रम, len2))
			वापस 1;
	पूर्ण अन्यथा अगर (kdb_grep_trailing) अणु
		अगर (!म_भेदन(searched+len1-len2, searchक्रम, len2))
			वापस 1;
	पूर्ण अन्यथा अणु
		firstअक्षर = *searchक्रम;
		cp = searched;
		जबतक ((cp = म_अक्षर(cp, firstअक्षर))) अणु
			अगर (!म_भेदन(cp, searchक्रम, len2))
				वापस 1;
			cp++;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम kdb_msg_ग_लिखो(स्थिर अक्षर *msg, पूर्णांक msg_len)
अणु
	काष्ठा console *c;
	स्थिर अक्षर *cp;
	पूर्णांक len;

	अगर (msg_len == 0)
		वापस;

	cp = msg;
	len = msg_len;

	जबतक (len--) अणु
		dbg_io_ops->ग_लिखो_अक्षर(*cp);
		cp++;
	पूर्ण

	क्रम_each_console(c) अणु
		अगर (!(c->flags & CON_ENABLED))
			जारी;
		अगर (c == dbg_io_ops->cons)
			जारी;
		/*
		 * Set oops_in_progress to encourage the console drivers to
		 * disregard their पूर्णांकernal spin locks: in the current calling
		 * context the risk of deadlock is a bigger problem than risks
		 * due to re-entering the console driver. We operate directly on
		 * oops_in_progress rather than using bust_spinlocks() because
		 * the calls bust_spinlocks() makes on निकास are not appropriate
		 * क्रम this calling context.
		 */
		++oops_in_progress;
		c->ग_लिखो(c, msg, msg_len);
		--oops_in_progress;
		touch_nmi_watchकरोg();
	पूर्ण
पूर्ण

पूर्णांक vkdb_म_लिखो(क्रमागत kdb_msgsrc src, स्थिर अक्षर *fmt, बहु_सूची ap)
अणु
	पूर्णांक diag;
	पूर्णांक linecount;
	पूर्णांक colcount;
	पूर्णांक logging, saved_loglevel = 0;
	पूर्णांक retlen = 0;
	पूर्णांक fnd, len;
	पूर्णांक this_cpu, old_cpu;
	अक्षर *cp, *cp2, *cphold = शून्य, replaced_byte = ' ';
	अक्षर *moreprompt = "more> ";
	अचिन्हित दीर्घ flags;

	/* Serialize kdb_म_लिखो अगर multiple cpus try to ग_लिखो at once.
	 * But अगर any cpu goes recursive in kdb, just prपूर्णांक the output,
	 * even अगर it is पूर्णांकerleaved with any other text.
	 */
	local_irq_save(flags);
	this_cpu = smp_processor_id();
	क्रम (;;) अणु
		old_cpu = cmpxchg(&kdb_म_लिखो_cpu, -1, this_cpu);
		अगर (old_cpu == -1 || old_cpu == this_cpu)
			अवरोध;

		cpu_relax();
	पूर्ण

	diag = kdbgetपूर्णांकenv("LINES", &linecount);
	अगर (diag || linecount <= 1)
		linecount = 24;

	diag = kdbgetपूर्णांकenv("COLUMNS", &colcount);
	अगर (diag || colcount <= 1)
		colcount = 80;

	diag = kdbgetपूर्णांकenv("LOGGING", &logging);
	अगर (diag)
		logging = 0;

	अगर (!kdb_grepping_flag || suspend_grep) अणु
		/* normally, every vsnम_लिखो starts a new buffer */
		next_avail = kdb_buffer;
		size_avail = माप(kdb_buffer);
	पूर्ण
	vsnम_लिखो(next_avail, size_avail, fmt, ap);

	/*
	 * If kdb_parse() found that the command was cmd xxx | grep yyy
	 * then kdb_grepping_flag is set, and kdb_grep_string contains yyy
	 *
	 * Accumulate the prपूर्णांक data up to a newline beक्रमe searching it.
	 * (vsnम_लिखो करोes null-terminate the string that it generates)
	 */

	/* skip the search अगर prपूर्णांकs are temporarily unconditional */
	अगर (!suspend_grep && kdb_grepping_flag) अणु
		cp = म_अक्षर(kdb_buffer, '\n');
		अगर (!cp) अणु
			/*
			 * Special हालs that करोn't end with newlines
			 * but should be written without one:
			 *   The "[nn]kdb> " prompt should
			 *   appear at the front of the buffer.
			 *
			 *   The "[nn]more " prompt should also be
			 *     (MOREPROMPT -> moreprompt)
			 *   written *   but we prपूर्णांक that ourselves,
			 *   we set the suspend_grep flag to make
			 *   it unconditional.
			 *
			 */
			अगर (next_avail == kdb_buffer) अणु
				/*
				 * these should occur after a newline,
				 * so they will be at the front of the
				 * buffer
				 */
				cp2 = kdb_buffer;
				len = म_माप(kdb_prompt_str);
				अगर (!म_भेदन(cp2, kdb_prompt_str, len)) अणु
					/*
					 * We're about to start a new
					 * command, so we can go back
					 * to normal mode.
					 */
					kdb_grepping_flag = 0;
					जाओ kdb_prपूर्णांकit;
				पूर्ण
			पूर्ण
			/* no newline; करोn't search/ग_लिखो the buffer
			   until one is there */
			len = म_माप(kdb_buffer);
			next_avail = kdb_buffer + len;
			size_avail = माप(kdb_buffer) - len;
			जाओ kdb_prपूर्णांक_out;
		पूर्ण

		/*
		 * The newline is present; prपूर्णांक through it or discard
		 * it, depending on the results of the search.
		 */
		cp++;	 	     /* to byte after the newline */
		replaced_byte = *cp; /* remember what/where it was */
		cphold = cp;
		*cp = '\0';	     /* end the string क्रम our search */

		/*
		 * We now have a newline at the end of the string
		 * Only जारी with this output अगर it contains the
		 * search string.
		 */
		fnd = kdb_search_string(kdb_buffer, kdb_grep_string);
		अगर (!fnd) अणु
			/*
			 * At this poपूर्णांक the complete line at the start
			 * of kdb_buffer can be discarded, as it करोes
			 * not contain what the user is looking क्रम.
			 * Shअगरt the buffer left.
			 */
			*cphold = replaced_byte;
			म_नकल(kdb_buffer, cphold);
			len = म_माप(kdb_buffer);
			next_avail = kdb_buffer + len;
			size_avail = माप(kdb_buffer) - len;
			जाओ kdb_prपूर्णांक_out;
		पूर्ण
		अगर (kdb_grepping_flag >= KDB_GREPPING_FLAG_SEARCH) अणु
			/*
			 * This was a पूर्णांकeractive search (using '/' at more
			 * prompt) and it has completed. Replace the \0 with
			 * its original value to ensure multi-line strings
			 * are handled properly, and वापस to normal mode.
			 */
			*cphold = replaced_byte;
			kdb_grepping_flag = 0;
		पूर्ण
		/*
		 * at this poपूर्णांक the string is a full line and
		 * should be prपूर्णांकed, up to the null.
		 */
	पूर्ण
kdb_prपूर्णांकit:

	/*
	 * Write to all consoles.
	 */
	retlen = म_माप(kdb_buffer);
	cp = (अक्षर *) prपूर्णांकk_skip_headers(kdb_buffer);
	अगर (!dbg_kdb_mode && kgdb_connected)
		gdbstub_msg_ग_लिखो(cp, retlen - (cp - kdb_buffer));
	अन्यथा
		kdb_msg_ग_लिखो(cp, retlen - (cp - kdb_buffer));

	अगर (logging) अणु
		saved_loglevel = console_loglevel;
		console_loglevel = CONSOLE_LOGLEVEL_SILENT;
		अगर (prपूर्णांकk_get_level(kdb_buffer) || src == KDB_MSGSRC_PRINTK)
			prपूर्णांकk("%s", kdb_buffer);
		अन्यथा
			pr_info("%s", kdb_buffer);
	पूर्ण

	अगर (KDB_STATE(PAGER)) अणु
		/*
		 * Check prपूर्णांकed string to decide how to bump the
		 * kdb_nextline to control when the more prompt should
		 * show up.
		 */
		पूर्णांक got = 0;
		len = retlen;
		जबतक (len--) अणु
			अगर (kdb_buffer[len] == '\n') अणु
				kdb_nextline++;
				got = 0;
			पूर्ण अन्यथा अगर (kdb_buffer[len] == '\r') अणु
				got = 0;
			पूर्ण अन्यथा अणु
				got++;
			पूर्ण
		पूर्ण
		kdb_nextline += got / (colcount + 1);
	पूर्ण

	/* check क्रम having reached the LINES number of prपूर्णांकed lines */
	अगर (kdb_nextline >= linecount) अणु
		अक्षर ch;

		/* Watch out क्रम recursion here.  Any routine that calls
		 * kdb_म_लिखो will come back through here.  And kdb_पढ़ो
		 * uses kdb_म_लिखो to echo on serial consoles ...
		 */
		kdb_nextline = 1;	/* In हाल of recursion */

		/*
		 * Pause until cr.
		 */
		moreprompt = kdbदो_पर्या("MOREPROMPT");
		अगर (moreprompt == शून्य)
			moreprompt = "more> ";

		kdb_input_flush();
		kdb_msg_ग_लिखो(moreprompt, म_माप(moreprompt));

		अगर (logging)
			prपूर्णांकk("%s", moreprompt);

		ch = kdb_अक्षर_लो();
		kdb_nextline = 1;	/* Really set output line 1 */

		/* empty and reset the buffer: */
		kdb_buffer[0] = '\0';
		next_avail = kdb_buffer;
		size_avail = माप(kdb_buffer);
		अगर ((ch == 'q') || (ch == 'Q')) अणु
			/* user hit q or Q */
			KDB_FLAG_SET(CMD_INTERRUPT); /* command पूर्णांकerrupted */
			KDB_STATE_CLEAR(PAGER);
			/* end of command output; back to normal mode */
			kdb_grepping_flag = 0;
			kdb_म_लिखो("\n");
		पूर्ण अन्यथा अगर (ch == ' ') अणु
			kdb_म_लिखो("\r");
			suspend_grep = 1; /* क्रम this recursion */
		पूर्ण अन्यथा अगर (ch == '\n' || ch == '\r') अणु
			kdb_nextline = linecount - 1;
			kdb_म_लिखो("\r");
			suspend_grep = 1; /* क्रम this recursion */
		पूर्ण अन्यथा अगर (ch == '/' && !kdb_grepping_flag) अणु
			kdb_म_लिखो("\r");
			kdb_माला_लोtr(kdb_grep_string, KDB_GREP_STRLEN,
				   kdbदो_पर्या("SEARCHPROMPT") ?: "search> ");
			*म_अक्षरnul(kdb_grep_string, '\n') = '\0';
			kdb_grepping_flag += KDB_GREPPING_FLAG_SEARCH;
			suspend_grep = 1; /* क्रम this recursion */
		पूर्ण अन्यथा अगर (ch) अणु
			/* user hit something unexpected */
			suspend_grep = 1; /* क्रम this recursion */
			अगर (ch != '/')
				kdb_म_लिखो(
				    "\nOnly 'q', 'Q' or '/' are processed at "
				    "more prompt, input ignored\n");
			अन्यथा
				kdb_म_लिखो("\n'/' cannot be used during | "
					   "grep filtering, input ignored\n");
		पूर्ण अन्यथा अगर (kdb_grepping_flag) अणु
			/* user hit enter */
			suspend_grep = 1; /* क्रम this recursion */
			kdb_म_लिखो("\n");
		पूर्ण
		kdb_input_flush();
	पूर्ण

	/*
	 * For grep searches, shअगरt the prपूर्णांकed string left.
	 *  replaced_byte contains the अक्षरacter that was overwritten with
	 *  the terminating null, and cphold poपूर्णांकs to the null.
	 * Then adjust the notion of available space in the buffer.
	 */
	अगर (kdb_grepping_flag && !suspend_grep) अणु
		*cphold = replaced_byte;
		म_नकल(kdb_buffer, cphold);
		len = म_माप(kdb_buffer);
		next_avail = kdb_buffer + len;
		size_avail = माप(kdb_buffer) - len;
	पूर्ण

kdb_prपूर्णांक_out:
	suspend_grep = 0; /* end of what may have been a recursive call */
	अगर (logging)
		console_loglevel = saved_loglevel;
	/* kdb_म_लिखो_cpu locked the code above. */
	smp_store_release(&kdb_म_लिखो_cpu, old_cpu);
	local_irq_restore(flags);
	वापस retlen;
पूर्ण

पूर्णांक kdb_म_लिखो(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	पूर्णांक r;

	बहु_शुरू(ap, fmt);
	r = vkdb_म_लिखो(KDB_MSGSRC_INTERNAL, fmt, ap);
	बहु_पूर्ण(ap);

	वापस r;
पूर्ण
EXPORT_SYMBOL_GPL(kdb_म_लिखो);
