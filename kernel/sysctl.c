<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sysctl.c: General linux प्रणाली control पूर्णांकerface
 *
 * Begun 24 March 1995, Stephen Tweedie
 * Added /proc support, Dec 1995
 * Added bdflush entry and पूर्णांकvec min/max checking, 2/23/96, Tom Dyas.
 * Added hooks क्रम /proc/sys/net (minor, minor patch), 96/4/1, Mike Shaver.
 * Added kernel/java-अणुपूर्णांकerpreter,appletviewerपूर्ण, 96/5/10, Mike Shaver.
 * Dynamic registration fixes, Stephen Tweedie.
 * Added kswapd-पूर्णांकerval, ctrl-alt-del, prपूर्णांकk stuff, 1/8/97, Chris Horn.
 * Made sysctl support optional via CONFIG_SYSCTL, 1/10/97, Chris
 *  Horn.
 * Added proc_करोuदीर्घvec_ms_jअगरfies_minmax, 09/08/99, Carlos H. Bauer.
 * Added proc_करोuदीर्घvec_minmax, 09/08/99, Carlos H. Bauer.
 * Changed linked lists to use list.h instead of lists.h, 02/24/00, Bill
 *  Wendling.
 * The list_क्रम_each() macro wasn't appropriate क्रम the sysctl loop.
 *  Removed it and replaced it with older style, 03/23/00, Bill Wendling
 */

#समावेश <linux/module.h>
#समावेश <linux/aपन.स>
#समावेश <linux/mm.h>
#समावेश <linux/swap.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/security.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/kmemleak.h>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kobject.h>
#समावेश <linux/net.h>
#समावेश <linux/sysrq.h>
#समावेश <linux/highuid.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/compaction.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/initrd.h>
#समावेश <linux/key.h>
#समावेश <linux/बार.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/dcache.h>
#समावेश <linux/dnotअगरy.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/vmस्थिति.स>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/acpi.h>
#समावेश <linux/reboot.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/pipe_fs_i.h>
#समावेश <linux/oom.h>
#समावेश <linux/kmod.h>
#समावेश <linux/capability.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/sched/sysctl.h>
#समावेश <linux/sched/coredump.h>
#समावेश <linux/kexec.h>
#समावेश <linux/bpf.h>
#समावेश <linux/mount.h>
#समावेश <linux/userfaultfd_k.h>
#समावेश <linux/coredump.h>
#समावेश <linux/latencytop.h>
#समावेश <linux/pid.h>

#समावेश "../lib/kstrtox.h"

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/processor.h>

#अगर_घोषित CONFIG_X86
#समावेश <यंत्र/nmi.h>
#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/पन.स>
#पूर्ण_अगर
#अगर_घोषित CONFIG_SPARC
#समावेश <यंत्र/setup.h>
#पूर्ण_अगर
#अगर_घोषित CONFIG_BSD_PROCESS_ACCT
#समावेश <linux/acct.h>
#पूर्ण_अगर
#अगर_घोषित CONFIG_RT_MUTEXES
#समावेश <linux/rपंचांगutex.h>
#पूर्ण_अगर
#अगर defined(CONFIG_PROVE_LOCKING) || defined(CONFIG_LOCK_STAT)
#समावेश <linux/lockdep.h>
#पूर्ण_अगर
#अगर_घोषित CONFIG_CHR_DEV_SG
#समावेश <scsi/sg.h>
#पूर्ण_अगर
#अगर_घोषित CONFIG_STACKLEAK_RUNTIME_DISABLE
#समावेश <linux/stackleak.h>
#पूर्ण_अगर
#अगर_घोषित CONFIG_LOCKUP_DETECTOR
#समावेश <linux/nmi.h>
#पूर्ण_अगर

#अगर defined(CONFIG_SYSCTL)

/* Constants used क्रम minimum and  maximum */
#अगर_घोषित CONFIG_LOCKUP_DETECTOR
अटल पूर्णांक sixty = 60;
#पूर्ण_अगर

अटल पूर्णांक __maybe_unused neg_one = -1;
अटल पूर्णांक __maybe_unused two = 2;
अटल पूर्णांक __maybe_unused four = 4;
अटल अचिन्हित दीर्घ zero_ul;
अटल अचिन्हित दीर्घ one_ul = 1;
अटल अचिन्हित दीर्घ दीर्घ_max = दीर्घ_उच्च;
अटल पूर्णांक one_hundred = 100;
अटल पूर्णांक two_hundred = 200;
अटल पूर्णांक one_thousand = 1000;
#अगर_घोषित CONFIG_PRINTK
अटल पूर्णांक ten_thousand = 10000;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PERF_EVENTS
अटल पूर्णांक six_hundred_क्रमty_kb = 640 * 1024;
#पूर्ण_अगर

/* this is needed क्रम the proc_करोuदीर्घvec_minmax of vm_dirty_bytes */
अटल अचिन्हित दीर्घ dirty_bytes_min = 2 * PAGE_SIZE;

/* this is needed क्रम the proc_करोपूर्णांकvec_minmax क्रम [fs_]overflow UID and GID */
अटल पूर्णांक maxolduid = 65535;
अटल पूर्णांक minolduid;

अटल पूर्णांक ngroups_max = NGROUPS_MAX;
अटल स्थिर पूर्णांक cap_last_cap = CAP_LAST_CAP;

/*
 * This is needed क्रम proc_करोuदीर्घvec_minmax of sysctl_hung_task_समयout_secs
 * and hung_task_check_पूर्णांकerval_secs
 */
#अगर_घोषित CONFIG_DETECT_HUNG_TASK
अटल अचिन्हित दीर्घ hung_task_समयout_max = (दीर्घ_उच्च/HZ);
#पूर्ण_अगर

#अगर_घोषित CONFIG_INOTIFY_USER
#समावेश <linux/inotअगरy.h>
#पूर्ण_अगर
#अगर_घोषित CONFIG_FANOTIFY
#समावेश <linux/fanotअगरy.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_PROC_SYSCTL

/**
 * क्रमागत sysctl_ग_लिखोs_mode - supported sysctl ग_लिखो modes
 *
 * @SYSCTL_WRITES_LEGACY: each ग_लिखो syscall must fully contain the sysctl value
 *	to be written, and multiple ग_लिखोs on the same sysctl file descriptor
 *	will reग_लिखो the sysctl value, regardless of file position. No warning
 *	is issued when the initial position is not 0.
 * @SYSCTL_WRITES_WARN: same as above but warn when the initial file position is
 *	not 0.
 * @SYSCTL_WRITES_STRICT: ग_लिखोs to numeric sysctl entries must always be at
 *	file position 0 and the value must be fully contained in the buffer
 *	sent to the ग_लिखो syscall. If dealing with strings respect the file
 *	position, but restrict this to the max length of the buffer, anything
 *	passed the max length will be ignored. Multiple ग_लिखोs will append
 *	to the buffer.
 *
 * These ग_लिखो modes control how current file position affects the behavior of
 * updating sysctl values through the proc पूर्णांकerface on each ग_लिखो.
 */
क्रमागत sysctl_ग_लिखोs_mode अणु
	SYSCTL_WRITES_LEGACY		= -1,
	SYSCTL_WRITES_WARN		= 0,
	SYSCTL_WRITES_STRICT		= 1,
पूर्ण;

अटल क्रमागत sysctl_ग_लिखोs_mode sysctl_ग_लिखोs_strict = SYSCTL_WRITES_STRICT;
#पूर्ण_अगर /* CONFIG_PROC_SYSCTL */

#अगर defined(HAVE_ARCH_PICK_MMAP_LAYOUT) || \
    defined(CONFIG_ARCH_WANT_DEFAULT_TOPDOWN_MMAP_LAYOUT)
पूर्णांक sysctl_legacy_va_layout;
#पूर्ण_अगर

#अगर_घोषित CONFIG_COMPACTION
अटल पूर्णांक min_extfrag_threshold;
अटल पूर्णांक max_extfrag_threshold = 1000;
#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_SYSCTL */

#अगर defined(CONFIG_BPF_SYSCALL) && defined(CONFIG_SYSCTL)
अटल पूर्णांक bpf_stats_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			     व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा अटल_key *key = (काष्ठा अटल_key *)table->data;
	अटल पूर्णांक saved_val;
	पूर्णांक val, ret;
	काष्ठा ctl_table पंचांगp = अणु
		.data   = &val,
		.maxlen = माप(val),
		.mode   = table->mode,
		.extra1 = SYSCTL_ZERO,
		.extra2 = SYSCTL_ONE,
	पूर्ण;

	अगर (ग_लिखो && !capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	mutex_lock(&bpf_stats_enabled_mutex);
	val = saved_val;
	ret = proc_करोपूर्णांकvec_minmax(&पंचांगp, ग_लिखो, buffer, lenp, ppos);
	अगर (ग_लिखो && !ret && val != saved_val) अणु
		अगर (val)
			अटल_key_slow_inc(key);
		अन्यथा
			अटल_key_slow_dec(key);
		saved_val = val;
	पूर्ण
	mutex_unlock(&bpf_stats_enabled_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक bpf_unpriv_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			      व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक ret, unpriv_enable = *(पूर्णांक *)table->data;
	bool locked_state = unpriv_enable == 1;
	काष्ठा ctl_table पंचांगp = *table;

	अगर (ग_लिखो && !capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	पंचांगp.data = &unpriv_enable;
	ret = proc_करोपूर्णांकvec_minmax(&पंचांगp, ग_लिखो, buffer, lenp, ppos);
	अगर (ग_लिखो && !ret) अणु
		अगर (locked_state && unpriv_enable != 1)
			वापस -EPERM;
		*(पूर्णांक *)table->data = unpriv_enable;
	पूर्ण
	वापस ret;
पूर्ण
#पूर्ण_अगर /* CONFIG_BPF_SYSCALL && CONFIG_SYSCTL */

/*
 * /proc/sys support
 */

#अगर_घोषित CONFIG_PROC_SYSCTL

अटल पूर्णांक _proc_करो_string(अक्षर *data, पूर्णांक maxlen, पूर्णांक ग_लिखो,
		अक्षर *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	माप_प्रकार len;
	अक्षर c, *p;

	अगर (!data || !maxlen || !*lenp) अणु
		*lenp = 0;
		वापस 0;
	पूर्ण

	अगर (ग_लिखो) अणु
		अगर (sysctl_ग_लिखोs_strict == SYSCTL_WRITES_STRICT) अणु
			/* Only जारी ग_लिखोs not past the end of buffer. */
			len = म_माप(data);
			अगर (len > maxlen - 1)
				len = maxlen - 1;

			अगर (*ppos > len)
				वापस 0;
			len = *ppos;
		पूर्ण अन्यथा अणु
			/* Start writing from beginning of buffer. */
			len = 0;
		पूर्ण

		*ppos += *lenp;
		p = buffer;
		जबतक ((p - buffer) < *lenp && len < maxlen - 1) अणु
			c = *(p++);
			अगर (c == 0 || c == '\n')
				अवरोध;
			data[len++] = c;
		पूर्ण
		data[len] = 0;
	पूर्ण अन्यथा अणु
		len = म_माप(data);
		अगर (len > maxlen)
			len = maxlen;

		अगर (*ppos > len) अणु
			*lenp = 0;
			वापस 0;
		पूर्ण

		data += *ppos;
		len  -= *ppos;

		अगर (len > *lenp)
			len = *lenp;
		अगर (len)
			स_नकल(buffer, data, len);
		अगर (len < *lenp) अणु
			buffer[len] = '\n';
			len++;
		पूर्ण
		*lenp = len;
		*ppos += len;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम warn_sysctl_ग_लिखो(काष्ठा ctl_table *table)
अणु
	pr_warn_once("%s wrote to %s when file position was not 0!\n"
		"This will not be supported in the future. To silence this\n"
		"warning, set kernel.sysctl_writes_strict = -1\n",
		current->comm, table->procname);
पूर्ण

/**
 * proc_first_pos_non_zero_ignore - check अगर first position is allowed
 * @ppos: file position
 * @table: the sysctl table
 *
 * Returns true अगर the first position is non-zero and the sysctl_ग_लिखोs_strict
 * mode indicates this is not allowed क्रम numeric input types. String proc
 * handlers can ignore the वापस value.
 */
अटल bool proc_first_pos_non_zero_ignore(loff_t *ppos,
					   काष्ठा ctl_table *table)
अणु
	अगर (!*ppos)
		वापस false;

	चयन (sysctl_ग_लिखोs_strict) अणु
	हाल SYSCTL_WRITES_STRICT:
		वापस true;
	हाल SYSCTL_WRITES_WARN:
		warn_sysctl_ग_लिखो(table);
		वापस false;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/**
 * proc_करोstring - पढ़ो a string sysctl
 * @table: the sysctl table
 * @ग_लिखो: %TRUE अगर this is a ग_लिखो to the sysctl file
 * @buffer: the user buffer
 * @lenp: the size of the user buffer
 * @ppos: file position
 *
 * Reads/ग_लिखोs a string from/to the user buffer. If the kernel
 * buffer provided is not large enough to hold the string, the
 * string is truncated. The copied string is %शून्य-terminated.
 * If the string is being पढ़ो by the user process, it is copied
 * and a newline '\n' is added. It is truncated अगर the buffer is
 * not large enough.
 *
 * Returns 0 on success.
 */
पूर्णांक proc_करोstring(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		  व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	अगर (ग_लिखो)
		proc_first_pos_non_zero_ignore(ppos, table);

	वापस _proc_करो_string(table->data, table->maxlen, ग_लिखो, buffer, lenp,
			ppos);
पूर्ण

अटल माप_प्रकार proc_skip_spaces(अक्षर **buf)
अणु
	माप_प्रकार ret;
	अक्षर *पंचांगp = skip_spaces(*buf);
	ret = पंचांगp - *buf;
	*buf = पंचांगp;
	वापस ret;
पूर्ण

अटल व्योम proc_skip_अक्षर(अक्षर **buf, माप_प्रकार *size, स्थिर अक्षर v)
अणु
	जबतक (*size) अणु
		अगर (**buf != v)
			अवरोध;
		(*size)--;
		(*buf)++;
	पूर्ण
पूर्ण

/**
 * म_से_अदीर्घ_lenient - parse an ASCII क्रमmatted पूर्णांकeger from a buffer and only
 *                   fail on overflow
 *
 * @cp: kernel buffer containing the string to parse
 * @endp: poपूर्णांकer to store the trailing अक्षरacters
 * @base: the base to use
 * @res: where the parsed पूर्णांकeger will be stored
 *
 * In हाल of success 0 is वापसed and @res will contain the parsed पूर्णांकeger,
 * @endp will hold any trailing अक्षरacters.
 * This function will fail the parse on overflow. If there wasn't an overflow
 * the function will defer the decision what अक्षरacters count as invalid to the
 * caller.
 */
अटल पूर्णांक म_से_अदीर्घ_lenient(स्थिर अक्षर *cp, अक्षर **endp, अचिन्हित पूर्णांक base,
			   अचिन्हित दीर्घ *res)
अणु
	अचिन्हित दीर्घ दीर्घ result;
	अचिन्हित पूर्णांक rv;

	cp = _parse_पूर्णांकeger_fixup_radix(cp, &base);
	rv = _parse_पूर्णांकeger(cp, base, &result);
	अगर ((rv & KSTRTOX_OVERFLOW) || (result != (अचिन्हित दीर्घ)result))
		वापस -दुस्फल;

	cp += rv;

	अगर (endp)
		*endp = (अक्षर *)cp;

	*res = (अचिन्हित दीर्घ)result;
	वापस 0;
पूर्ण

#घोषणा TMPBUFLEN 22
/**
 * proc_get_दीर्घ - पढ़ोs an ASCII क्रमmatted पूर्णांकeger from a user buffer
 *
 * @buf: a kernel buffer
 * @size: size of the kernel buffer
 * @val: this is where the number will be stored
 * @neg: set to %TRUE अगर number is negative
 * @perm_tr: a vector which contains the allowed trailers
 * @perm_tr_len: size of the perm_tr vector
 * @tr: poपूर्णांकer to store the trailer अक्षरacter
 *
 * In हाल of success %0 is वापसed and @buf and @size are updated with
 * the amount of bytes पढ़ो. If @tr is non-शून्य and a trailing
 * अक्षरacter exists (size is non-zero after वापसing from this
 * function), @tr is updated with the trailing अक्षरacter.
 */
अटल पूर्णांक proc_get_दीर्घ(अक्षर **buf, माप_प्रकार *size,
			  अचिन्हित दीर्घ *val, bool *neg,
			  स्थिर अक्षर *perm_tr, अचिन्हित perm_tr_len, अक्षर *tr)
अणु
	पूर्णांक len;
	अक्षर *p, पंचांगp[TMPBUFLEN];

	अगर (!*size)
		वापस -EINVAL;

	len = *size;
	अगर (len > TMPBUFLEN - 1)
		len = TMPBUFLEN - 1;

	स_नकल(पंचांगp, *buf, len);

	पंचांगp[len] = 0;
	p = पंचांगp;
	अगर (*p == '-' && *size > 1) अणु
		*neg = true;
		p++;
	पूर्ण अन्यथा
		*neg = false;
	अगर (!है_अंक(*p))
		वापस -EINVAL;

	अगर (म_से_अदीर्घ_lenient(p, &p, 0, val))
		वापस -EINVAL;

	len = p - पंचांगp;

	/* We करोn't know अगर the next अक्षर is whitespace thus we may accept
	 * invalid पूर्णांकegers (e.g. 1234...a) or two पूर्णांकegers instead of one
	 * (e.g. 123...1). So lets not allow such large numbers. */
	अगर (len == TMPBUFLEN - 1)
		वापस -EINVAL;

	अगर (len < *size && perm_tr_len && !स_प्रथम(perm_tr, *p, perm_tr_len))
		वापस -EINVAL;

	अगर (tr && (len < *size))
		*tr = *p;

	*buf += len;
	*size -= len;

	वापस 0;
पूर्ण

/**
 * proc_put_दीर्घ - converts an पूर्णांकeger to a decimal ASCII क्रमmatted string
 *
 * @buf: the user buffer
 * @size: the size of the user buffer
 * @val: the पूर्णांकeger to be converted
 * @neg: sign of the number, %TRUE क्रम negative
 *
 * In हाल of success @buf and @size are updated with the amount of bytes
 * written.
 */
अटल व्योम proc_put_दीर्घ(व्योम **buf, माप_प्रकार *size, अचिन्हित दीर्घ val, bool neg)
अणु
	पूर्णांक len;
	अक्षर पंचांगp[TMPBUFLEN], *p = पंचांगp;

	प्र_लिखो(p, "%s%lu", neg ? "-" : "", val);
	len = म_माप(पंचांगp);
	अगर (len > *size)
		len = *size;
	स_नकल(*buf, पंचांगp, len);
	*size -= len;
	*buf += len;
पूर्ण
#अघोषित TMPBUFLEN

अटल व्योम proc_put_अक्षर(व्योम **buf, माप_प्रकार *size, अक्षर c)
अणु
	अगर (*size) अणु
		अक्षर **buffer = (अक्षर **)buf;
		**buffer = c;

		(*size)--;
		(*buffer)++;
		*buf = *buffer;
	पूर्ण
पूर्ण

अटल पूर्णांक करो_proc_करोपूर्णांकvec_conv(bool *negp, अचिन्हित दीर्घ *lvalp,
				 पूर्णांक *valp,
				 पूर्णांक ग_लिखो, व्योम *data)
अणु
	अगर (ग_लिखो) अणु
		अगर (*negp) अणु
			अगर (*lvalp > (अचिन्हित दीर्घ) पूर्णांक_उच्च + 1)
				वापस -EINVAL;
			*valp = -*lvalp;
		पूर्ण अन्यथा अणु
			अगर (*lvalp > (अचिन्हित दीर्घ) पूर्णांक_उच्च)
				वापस -EINVAL;
			*valp = *lvalp;
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक val = *valp;
		अगर (val < 0) अणु
			*negp = true;
			*lvalp = -(अचिन्हित दीर्घ)val;
		पूर्ण अन्यथा अणु
			*negp = false;
			*lvalp = (अचिन्हित दीर्घ)val;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक करो_proc_करोuपूर्णांकvec_conv(अचिन्हित दीर्घ *lvalp,
				  अचिन्हित पूर्णांक *valp,
				  पूर्णांक ग_लिखो, व्योम *data)
अणु
	अगर (ग_लिखो) अणु
		अगर (*lvalp > अच_पूर्णांक_उच्च)
			वापस -EINVAL;
		*valp = *lvalp;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक val = *valp;
		*lvalp = (अचिन्हित दीर्घ)val;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर अक्षर proc_wspace_sep[] = अणु ' ', '\t', '\n' पूर्ण;

अटल पूर्णांक __करो_proc_करोपूर्णांकvec(व्योम *tbl_data, काष्ठा ctl_table *table,
		  पूर्णांक ग_लिखो, व्योम *buffer,
		  माप_प्रकार *lenp, loff_t *ppos,
		  पूर्णांक (*conv)(bool *negp, अचिन्हित दीर्घ *lvalp, पूर्णांक *valp,
			      पूर्णांक ग_लिखो, व्योम *data),
		  व्योम *data)
अणु
	पूर्णांक *i, vleft, first = 1, err = 0;
	माप_प्रकार left;
	अक्षर *p;
	
	अगर (!tbl_data || !table->maxlen || !*lenp || (*ppos && !ग_लिखो)) अणु
		*lenp = 0;
		वापस 0;
	पूर्ण
	
	i = (पूर्णांक *) tbl_data;
	vleft = table->maxlen / माप(*i);
	left = *lenp;

	अगर (!conv)
		conv = करो_proc_करोपूर्णांकvec_conv;

	अगर (ग_लिखो) अणु
		अगर (proc_first_pos_non_zero_ignore(ppos, table))
			जाओ out;

		अगर (left > PAGE_SIZE - 1)
			left = PAGE_SIZE - 1;
		p = buffer;
	पूर्ण

	क्रम (; left && vleft--; i++, first=0) अणु
		अचिन्हित दीर्घ lval;
		bool neg;

		अगर (ग_लिखो) अणु
			left -= proc_skip_spaces(&p);

			अगर (!left)
				अवरोध;
			err = proc_get_दीर्घ(&p, &left, &lval, &neg,
					     proc_wspace_sep,
					     माप(proc_wspace_sep), शून्य);
			अगर (err)
				अवरोध;
			अगर (conv(&neg, &lval, i, 1, data)) अणु
				err = -EINVAL;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (conv(&neg, &lval, i, 0, data)) अणु
				err = -EINVAL;
				अवरोध;
			पूर्ण
			अगर (!first)
				proc_put_अक्षर(&buffer, &left, '\t');
			proc_put_दीर्घ(&buffer, &left, lval, neg);
		पूर्ण
	पूर्ण

	अगर (!ग_लिखो && !first && left && !err)
		proc_put_अक्षर(&buffer, &left, '\n');
	अगर (ग_लिखो && !err && left)
		left -= proc_skip_spaces(&p);
	अगर (ग_लिखो && first)
		वापस err ? : -EINVAL;
	*lenp -= left;
out:
	*ppos += *lenp;
	वापस err;
पूर्ण

अटल पूर्णांक करो_proc_करोपूर्णांकvec(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		  व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos,
		  पूर्णांक (*conv)(bool *negp, अचिन्हित दीर्घ *lvalp, पूर्णांक *valp,
			      पूर्णांक ग_लिखो, व्योम *data),
		  व्योम *data)
अणु
	वापस __करो_proc_करोपूर्णांकvec(table->data, table, ग_लिखो,
			buffer, lenp, ppos, conv, data);
पूर्ण

अटल पूर्णांक करो_proc_करोuपूर्णांकvec_w(अचिन्हित पूर्णांक *tbl_data,
			       काष्ठा ctl_table *table,
			       व्योम *buffer,
			       माप_प्रकार *lenp, loff_t *ppos,
			       पूर्णांक (*conv)(अचिन्हित दीर्घ *lvalp,
					   अचिन्हित पूर्णांक *valp,
					   पूर्णांक ग_लिखो, व्योम *data),
			       व्योम *data)
अणु
	अचिन्हित दीर्घ lval;
	पूर्णांक err = 0;
	माप_प्रकार left;
	bool neg;
	अक्षर *p = buffer;

	left = *lenp;

	अगर (proc_first_pos_non_zero_ignore(ppos, table))
		जाओ bail_early;

	अगर (left > PAGE_SIZE - 1)
		left = PAGE_SIZE - 1;

	left -= proc_skip_spaces(&p);
	अगर (!left) अणु
		err = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	err = proc_get_दीर्घ(&p, &left, &lval, &neg,
			     proc_wspace_sep,
			     माप(proc_wspace_sep), शून्य);
	अगर (err || neg) अणु
		err = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	अगर (conv(&lval, tbl_data, 1, data)) अणु
		err = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	अगर (!err && left)
		left -= proc_skip_spaces(&p);

out_मुक्त:
	अगर (err)
		वापस -EINVAL;

	वापस 0;

	/* This is in keeping with old __करो_proc_करोपूर्णांकvec() */
bail_early:
	*ppos += *lenp;
	वापस err;
पूर्ण

अटल पूर्णांक करो_proc_करोuपूर्णांकvec_r(अचिन्हित पूर्णांक *tbl_data, व्योम *buffer,
			       माप_प्रकार *lenp, loff_t *ppos,
			       पूर्णांक (*conv)(अचिन्हित दीर्घ *lvalp,
					   अचिन्हित पूर्णांक *valp,
					   पूर्णांक ग_लिखो, व्योम *data),
			       व्योम *data)
अणु
	अचिन्हित दीर्घ lval;
	पूर्णांक err = 0;
	माप_प्रकार left;

	left = *lenp;

	अगर (conv(&lval, tbl_data, 0, data)) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	proc_put_दीर्घ(&buffer, &left, lval, false);
	अगर (!left)
		जाओ out;

	proc_put_अक्षर(&buffer, &left, '\n');

out:
	*lenp -= left;
	*ppos += *lenp;

	वापस err;
पूर्ण

अटल पूर्णांक __करो_proc_करोuपूर्णांकvec(व्योम *tbl_data, काष्ठा ctl_table *table,
			       पूर्णांक ग_लिखो, व्योम *buffer,
			       माप_प्रकार *lenp, loff_t *ppos,
			       पूर्णांक (*conv)(अचिन्हित दीर्घ *lvalp,
					   अचिन्हित पूर्णांक *valp,
					   पूर्णांक ग_लिखो, व्योम *data),
			       व्योम *data)
अणु
	अचिन्हित पूर्णांक *i, vleft;

	अगर (!tbl_data || !table->maxlen || !*lenp || (*ppos && !ग_लिखो)) अणु
		*lenp = 0;
		वापस 0;
	पूर्ण

	i = (अचिन्हित पूर्णांक *) tbl_data;
	vleft = table->maxlen / माप(*i);

	/*
	 * Arrays are not supported, keep this simple. *Do not* add
	 * support क्रम them.
	 */
	अगर (vleft != 1) अणु
		*lenp = 0;
		वापस -EINVAL;
	पूर्ण

	अगर (!conv)
		conv = करो_proc_करोuपूर्णांकvec_conv;

	अगर (ग_लिखो)
		वापस करो_proc_करोuपूर्णांकvec_w(i, table, buffer, lenp, ppos,
					   conv, data);
	वापस करो_proc_करोuपूर्णांकvec_r(i, buffer, lenp, ppos, conv, data);
पूर्ण

अटल पूर्णांक करो_proc_करोuपूर्णांकvec(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			     व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos,
			     पूर्णांक (*conv)(अचिन्हित दीर्घ *lvalp,
					 अचिन्हित पूर्णांक *valp,
					 पूर्णांक ग_लिखो, व्योम *data),
			     व्योम *data)
अणु
	वापस __करो_proc_करोuपूर्णांकvec(table->data, table, ग_लिखो,
				   buffer, lenp, ppos, conv, data);
पूर्ण

/**
 * proc_करोपूर्णांकvec - पढ़ो a vector of पूर्णांकegers
 * @table: the sysctl table
 * @ग_लिखो: %TRUE अगर this is a ग_लिखो to the sysctl file
 * @buffer: the user buffer
 * @lenp: the size of the user buffer
 * @ppos: file position
 *
 * Reads/ग_लिखोs up to table->maxlen/माप(अचिन्हित पूर्णांक) पूर्णांकeger
 * values from/to the user buffer, treated as an ASCII string. 
 *
 * Returns 0 on success.
 */
पूर्णांक proc_करोपूर्णांकvec(काष्ठा ctl_table *table, पूर्णांक ग_लिखो, व्योम *buffer,
		  माप_प्रकार *lenp, loff_t *ppos)
अणु
	वापस करो_proc_करोपूर्णांकvec(table, ग_लिखो, buffer, lenp, ppos, शून्य, शून्य);
पूर्ण

#अगर_घोषित CONFIG_COMPACTION
अटल पूर्णांक proc_करोपूर्णांकvec_minmax_warn_RT_change(काष्ठा ctl_table *table,
		पूर्णांक ग_लिखो, व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक ret, old;

	अगर (!IS_ENABLED(CONFIG_PREEMPT_RT) || !ग_लिखो)
		वापस proc_करोपूर्णांकvec_minmax(table, ग_लिखो, buffer, lenp, ppos);

	old = *(पूर्णांक *)table->data;
	ret = proc_करोपूर्णांकvec_minmax(table, ग_लिखो, buffer, lenp, ppos);
	अगर (ret)
		वापस ret;
	अगर (old != *(पूर्णांक *)table->data)
		pr_warn_once("sysctl attribute %s changed by %s[%d]\n",
			     table->procname, current->comm,
			     task_pid_nr(current));
	वापस ret;
पूर्ण
#पूर्ण_अगर

/**
 * proc_करोuपूर्णांकvec - पढ़ो a vector of अचिन्हित पूर्णांकegers
 * @table: the sysctl table
 * @ग_लिखो: %TRUE अगर this is a ग_लिखो to the sysctl file
 * @buffer: the user buffer
 * @lenp: the size of the user buffer
 * @ppos: file position
 *
 * Reads/ग_लिखोs up to table->maxlen/माप(अचिन्हित पूर्णांक) अचिन्हित पूर्णांकeger
 * values from/to the user buffer, treated as an ASCII string.
 *
 * Returns 0 on success.
 */
पूर्णांक proc_करोuपूर्णांकvec(काष्ठा ctl_table *table, पूर्णांक ग_लिखो, व्योम *buffer,
		माप_प्रकार *lenp, loff_t *ppos)
अणु
	वापस करो_proc_करोuपूर्णांकvec(table, ग_लिखो, buffer, lenp, ppos,
				 करो_proc_करोuपूर्णांकvec_conv, शून्य);
पूर्ण

/*
 * Taपूर्णांक values can only be increased
 * This means we can safely use a temporary.
 */
अटल पूर्णांक proc_taपूर्णांक(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			       व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा ctl_table t;
	अचिन्हित दीर्घ पंचांगptaपूर्णांक = get_taपूर्णांक();
	पूर्णांक err;

	अगर (ग_लिखो && !capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	t = *table;
	t.data = &पंचांगptaपूर्णांक;
	err = proc_करोuदीर्घvec_minmax(&t, ग_लिखो, buffer, lenp, ppos);
	अगर (err < 0)
		वापस err;

	अगर (ग_लिखो) अणु
		पूर्णांक i;

		/*
		 * If we are relying on panic_on_taपूर्णांक not producing
		 * false positives due to userspace input, bail out
		 * beक्रमe setting the requested taपूर्णांक flags.
		 */
		अगर (panic_on_taपूर्णांक_nousertaपूर्णांक && (पंचांगptaपूर्णांक & panic_on_taपूर्णांक))
			वापस -EINVAL;

		/*
		 * Poor man's atomic or. Not worth adding a primitive
		 * to everyone's atomic.h क्रम this
		 */
		क्रम (i = 0; i < TAINT_FLAGS_COUNT; i++)
			अगर ((1UL << i) & पंचांगptaपूर्णांक)
				add_taपूर्णांक(i, LOCKDEP_STILL_OK);
	पूर्ण

	वापस err;
पूर्ण

#अगर_घोषित CONFIG_PRINTK
अटल पूर्णांक proc_करोपूर्णांकvec_minmax_sysadmin(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	अगर (ग_लिखो && !capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	वापस proc_करोपूर्णांकvec_minmax(table, ग_लिखो, buffer, lenp, ppos);
पूर्ण
#पूर्ण_अगर

/**
 * काष्ठा करो_proc_करोपूर्णांकvec_minmax_conv_param - proc_करोपूर्णांकvec_minmax() range checking काष्ठाure
 * @min: poपूर्णांकer to minimum allowable value
 * @max: poपूर्णांकer to maximum allowable value
 *
 * The करो_proc_करोपूर्णांकvec_minmax_conv_param काष्ठाure provides the
 * minimum and maximum values क्रम करोing range checking क्रम those sysctl
 * parameters that use the proc_करोपूर्णांकvec_minmax() handler.
 */
काष्ठा करो_proc_करोपूर्णांकvec_minmax_conv_param अणु
	पूर्णांक *min;
	पूर्णांक *max;
पूर्ण;

अटल पूर्णांक करो_proc_करोपूर्णांकvec_minmax_conv(bool *negp, अचिन्हित दीर्घ *lvalp,
					पूर्णांक *valp,
					पूर्णांक ग_लिखो, व्योम *data)
अणु
	पूर्णांक पंचांगp, ret;
	काष्ठा करो_proc_करोपूर्णांकvec_minmax_conv_param *param = data;
	/*
	 * If writing, first करो so via a temporary local पूर्णांक so we can
	 * bounds-check it beक्रमe touching *valp.
	 */
	पूर्णांक *ip = ग_लिखो ? &पंचांगp : valp;

	ret = करो_proc_करोपूर्णांकvec_conv(negp, lvalp, ip, ग_लिखो, data);
	अगर (ret)
		वापस ret;

	अगर (ग_लिखो) अणु
		अगर ((param->min && *param->min > पंचांगp) ||
		    (param->max && *param->max < पंचांगp))
			वापस -EINVAL;
		*valp = पंचांगp;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * proc_करोपूर्णांकvec_minmax - पढ़ो a vector of पूर्णांकegers with min/max values
 * @table: the sysctl table
 * @ग_लिखो: %TRUE अगर this is a ग_लिखो to the sysctl file
 * @buffer: the user buffer
 * @lenp: the size of the user buffer
 * @ppos: file position
 *
 * Reads/ग_लिखोs up to table->maxlen/माप(अचिन्हित पूर्णांक) पूर्णांकeger
 * values from/to the user buffer, treated as an ASCII string.
 *
 * This routine will ensure the values are within the range specअगरied by
 * table->extra1 (min) and table->extra2 (max).
 *
 * Returns 0 on success or -EINVAL on ग_लिखो when the range check fails.
 */
पूर्णांक proc_करोपूर्णांकvec_minmax(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		  व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा करो_proc_करोपूर्णांकvec_minmax_conv_param param = अणु
		.min = (पूर्णांक *) table->extra1,
		.max = (पूर्णांक *) table->extra2,
	पूर्ण;
	वापस करो_proc_करोपूर्णांकvec(table, ग_लिखो, buffer, lenp, ppos,
				करो_proc_करोपूर्णांकvec_minmax_conv, &param);
पूर्ण

/**
 * काष्ठा करो_proc_करोuपूर्णांकvec_minmax_conv_param - proc_करोuपूर्णांकvec_minmax() range checking काष्ठाure
 * @min: poपूर्णांकer to minimum allowable value
 * @max: poपूर्णांकer to maximum allowable value
 *
 * The करो_proc_करोuपूर्णांकvec_minmax_conv_param काष्ठाure provides the
 * minimum and maximum values क्रम करोing range checking क्रम those sysctl
 * parameters that use the proc_करोuपूर्णांकvec_minmax() handler.
 */
काष्ठा करो_proc_करोuपूर्णांकvec_minmax_conv_param अणु
	अचिन्हित पूर्णांक *min;
	अचिन्हित पूर्णांक *max;
पूर्ण;

अटल पूर्णांक करो_proc_करोuपूर्णांकvec_minmax_conv(अचिन्हित दीर्घ *lvalp,
					 अचिन्हित पूर्णांक *valp,
					 पूर्णांक ग_लिखो, व्योम *data)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक पंचांगp;
	काष्ठा करो_proc_करोuपूर्णांकvec_minmax_conv_param *param = data;
	/* ग_लिखो via temporary local uपूर्णांक क्रम bounds-checking */
	अचिन्हित पूर्णांक *up = ग_लिखो ? &पंचांगp : valp;

	ret = करो_proc_करोuपूर्णांकvec_conv(lvalp, up, ग_लिखो, data);
	अगर (ret)
		वापस ret;

	अगर (ग_लिखो) अणु
		अगर ((param->min && *param->min > पंचांगp) ||
		    (param->max && *param->max < पंचांगp))
			वापस -दुस्फल;

		*valp = पंचांगp;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * proc_करोuपूर्णांकvec_minmax - पढ़ो a vector of अचिन्हित पूर्णांकs with min/max values
 * @table: the sysctl table
 * @ग_लिखो: %TRUE अगर this is a ग_लिखो to the sysctl file
 * @buffer: the user buffer
 * @lenp: the size of the user buffer
 * @ppos: file position
 *
 * Reads/ग_लिखोs up to table->maxlen/माप(अचिन्हित पूर्णांक) अचिन्हित पूर्णांकeger
 * values from/to the user buffer, treated as an ASCII string. Negative
 * strings are not allowed.
 *
 * This routine will ensure the values are within the range specअगरied by
 * table->extra1 (min) and table->extra2 (max). There is a final sanity
 * check क्रम अच_पूर्णांक_उच्च to aव्योम having to support wrap around uses from
 * userspace.
 *
 * Returns 0 on success or -दुस्फल on ग_लिखो when the range check fails.
 */
पूर्णांक proc_करोuपूर्णांकvec_minmax(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			  व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा करो_proc_करोuपूर्णांकvec_minmax_conv_param param = अणु
		.min = (अचिन्हित पूर्णांक *) table->extra1,
		.max = (अचिन्हित पूर्णांक *) table->extra2,
	पूर्ण;
	वापस करो_proc_करोuपूर्णांकvec(table, ग_लिखो, buffer, lenp, ppos,
				 करो_proc_करोuपूर्णांकvec_minmax_conv, &param);
पूर्ण

/**
 * proc_करोu8vec_minmax - पढ़ो a vector of अचिन्हित अक्षरs with min/max values
 * @table: the sysctl table
 * @ग_लिखो: %TRUE अगर this is a ग_लिखो to the sysctl file
 * @buffer: the user buffer
 * @lenp: the size of the user buffer
 * @ppos: file position
 *
 * Reads/ग_लिखोs up to table->maxlen/माप(u8) अचिन्हित अक्षरs
 * values from/to the user buffer, treated as an ASCII string. Negative
 * strings are not allowed.
 *
 * This routine will ensure the values are within the range specअगरied by
 * table->extra1 (min) and table->extra2 (max).
 *
 * Returns 0 on success or an error on ग_लिखो when the range check fails.
 */
पूर्णांक proc_करोu8vec_minmax(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा ctl_table पंचांगp;
	अचिन्हित पूर्णांक min = 0, max = 255U, val;
	u8 *data = table->data;
	काष्ठा करो_proc_करोuपूर्णांकvec_minmax_conv_param param = अणु
		.min = &min,
		.max = &max,
	पूर्ण;
	पूर्णांक res;

	/* Do not support arrays yet. */
	अगर (table->maxlen != माप(u8))
		वापस -EINVAL;

	अगर (table->extra1) अणु
		min = *(अचिन्हित पूर्णांक *) table->extra1;
		अगर (min > 255U)
			वापस -EINVAL;
	पूर्ण
	अगर (table->extra2) अणु
		max = *(अचिन्हित पूर्णांक *) table->extra2;
		अगर (max > 255U)
			वापस -EINVAL;
	पूर्ण

	पंचांगp = *table;

	पंचांगp.maxlen = माप(val);
	पंचांगp.data = &val;
	val = *data;
	res = करो_proc_करोuपूर्णांकvec(&पंचांगp, ग_लिखो, buffer, lenp, ppos,
				करो_proc_करोuपूर्णांकvec_minmax_conv, &param);
	अगर (res)
		वापस res;
	अगर (ग_लिखो)
		*data = val;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(proc_करोu8vec_minmax);

अटल पूर्णांक करो_proc_करोpipe_max_size_conv(अचिन्हित दीर्घ *lvalp,
					अचिन्हित पूर्णांक *valp,
					पूर्णांक ग_लिखो, व्योम *data)
अणु
	अगर (ग_लिखो) अणु
		अचिन्हित पूर्णांक val;

		val = round_pipe_size(*lvalp);
		अगर (val == 0)
			वापस -EINVAL;

		*valp = val;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक val = *valp;
		*lvalp = (अचिन्हित दीर्घ) val;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक proc_करोpipe_max_size(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	वापस करो_proc_करोuपूर्णांकvec(table, ग_लिखो, buffer, lenp, ppos,
				 करो_proc_करोpipe_max_size_conv, शून्य);
पूर्ण

अटल व्योम validate_coredump_safety(व्योम)
अणु
#अगर_घोषित CONFIG_COREDUMP
	अगर (suid_dumpable == SUID_DUMP_ROOT &&
	    core_pattern[0] != '/' && core_pattern[0] != '|') अणु
		prपूर्णांकk(KERN_WARNING
"Unsafe core_pattern used with fs.suid_dumpable=2.\n"
"Pipe handler or fully qualified core dump path required.\n"
"Set kernel.core_pattern before fs.suid_dumpable.\n"
		);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक proc_करोपूर्णांकvec_minmax_coredump(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक error = proc_करोपूर्णांकvec_minmax(table, ग_लिखो, buffer, lenp, ppos);
	अगर (!error)
		validate_coredump_safety();
	वापस error;
पूर्ण

#अगर_घोषित CONFIG_COREDUMP
अटल पूर्णांक proc_करोstring_coredump(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		  व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक error = proc_करोstring(table, ग_लिखो, buffer, lenp, ppos);
	अगर (!error)
		validate_coredump_safety();
	वापस error;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_MAGIC_SYSRQ
अटल पूर्णांक sysrq_sysctl_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक पंचांगp, ret;

	पंचांगp = sysrq_mask();

	ret = __करो_proc_करोपूर्णांकvec(&पंचांगp, table, ग_लिखो, buffer,
			       lenp, ppos, शून्य, शून्य);
	अगर (ret || !ग_लिखो)
		वापस ret;

	अगर (ग_लिखो)
		sysrq_toggle_support(पंचांगp);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __करो_proc_करोuदीर्घvec_minmax(व्योम *data, काष्ठा ctl_table *table,
		पूर्णांक ग_लिखो, व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos,
		अचिन्हित दीर्घ convmul, अचिन्हित दीर्घ convभाग)
अणु
	अचिन्हित दीर्घ *i, *min, *max;
	पूर्णांक vleft, first = 1, err = 0;
	माप_प्रकार left;
	अक्षर *p;

	अगर (!data || !table->maxlen || !*lenp || (*ppos && !ग_लिखो)) अणु
		*lenp = 0;
		वापस 0;
	पूर्ण

	i = (अचिन्हित दीर्घ *) data;
	min = (अचिन्हित दीर्घ *) table->extra1;
	max = (अचिन्हित दीर्घ *) table->extra2;
	vleft = table->maxlen / माप(अचिन्हित दीर्घ);
	left = *lenp;

	अगर (ग_लिखो) अणु
		अगर (proc_first_pos_non_zero_ignore(ppos, table))
			जाओ out;

		अगर (left > PAGE_SIZE - 1)
			left = PAGE_SIZE - 1;
		p = buffer;
	पूर्ण

	क्रम (; left && vleft--; i++, first = 0) अणु
		अचिन्हित दीर्घ val;

		अगर (ग_लिखो) अणु
			bool neg;

			left -= proc_skip_spaces(&p);
			अगर (!left)
				अवरोध;

			err = proc_get_दीर्घ(&p, &left, &val, &neg,
					     proc_wspace_sep,
					     माप(proc_wspace_sep), शून्य);
			अगर (err)
				अवरोध;
			अगर (neg)
				जारी;
			val = convmul * val / convभाग;
			अगर ((min && val < *min) || (max && val > *max)) अणु
				err = -EINVAL;
				अवरोध;
			पूर्ण
			*i = val;
		पूर्ण अन्यथा अणु
			val = convभाग * (*i) / convmul;
			अगर (!first)
				proc_put_अक्षर(&buffer, &left, '\t');
			proc_put_दीर्घ(&buffer, &left, val, false);
		पूर्ण
	पूर्ण

	अगर (!ग_लिखो && !first && left && !err)
		proc_put_अक्षर(&buffer, &left, '\n');
	अगर (ग_लिखो && !err)
		left -= proc_skip_spaces(&p);
	अगर (ग_लिखो && first)
		वापस err ? : -EINVAL;
	*lenp -= left;
out:
	*ppos += *lenp;
	वापस err;
पूर्ण

अटल पूर्णांक करो_proc_करोuदीर्घvec_minmax(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos, अचिन्हित दीर्घ convmul,
		अचिन्हित दीर्घ convभाग)
अणु
	वापस __करो_proc_करोuदीर्घvec_minmax(table->data, table, ग_लिखो,
			buffer, lenp, ppos, convmul, convभाग);
पूर्ण

/**
 * proc_करोuदीर्घvec_minmax - पढ़ो a vector of दीर्घ पूर्णांकegers with min/max values
 * @table: the sysctl table
 * @ग_लिखो: %TRUE अगर this is a ग_लिखो to the sysctl file
 * @buffer: the user buffer
 * @lenp: the size of the user buffer
 * @ppos: file position
 *
 * Reads/ग_लिखोs up to table->maxlen/माप(अचिन्हित दीर्घ) अचिन्हित दीर्घ
 * values from/to the user buffer, treated as an ASCII string.
 *
 * This routine will ensure the values are within the range specअगरied by
 * table->extra1 (min) and table->extra2 (max).
 *
 * Returns 0 on success.
 */
पूर्णांक proc_करोuदीर्घvec_minmax(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			   व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
    वापस करो_proc_करोuदीर्घvec_minmax(table, ग_लिखो, buffer, lenp, ppos, 1l, 1l);
पूर्ण

/**
 * proc_करोuदीर्घvec_ms_jअगरfies_minmax - पढ़ो a vector of millisecond values with min/max values
 * @table: the sysctl table
 * @ग_लिखो: %TRUE अगर this is a ग_लिखो to the sysctl file
 * @buffer: the user buffer
 * @lenp: the size of the user buffer
 * @ppos: file position
 *
 * Reads/ग_लिखोs up to table->maxlen/माप(अचिन्हित दीर्घ) अचिन्हित दीर्घ
 * values from/to the user buffer, treated as an ASCII string. The values
 * are treated as milliseconds, and converted to jअगरfies when they are stored.
 *
 * This routine will ensure the values are within the range specअगरied by
 * table->extra1 (min) and table->extra2 (max).
 *
 * Returns 0 on success.
 */
पूर्णांक proc_करोuदीर्घvec_ms_jअगरfies_minmax(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				      व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
    वापस करो_proc_करोuदीर्घvec_minmax(table, ग_लिखो, buffer,
				     lenp, ppos, HZ, 1000l);
पूर्ण


अटल पूर्णांक करो_proc_करोपूर्णांकvec_jअगरfies_conv(bool *negp, अचिन्हित दीर्घ *lvalp,
					 पूर्णांक *valp,
					 पूर्णांक ग_लिखो, व्योम *data)
अणु
	अगर (ग_लिखो) अणु
		अगर (*lvalp > पूर्णांक_उच्च / HZ)
			वापस 1;
		*valp = *negp ? -(*lvalp*HZ) : (*lvalp*HZ);
	पूर्ण अन्यथा अणु
		पूर्णांक val = *valp;
		अचिन्हित दीर्घ lval;
		अगर (val < 0) अणु
			*negp = true;
			lval = -(अचिन्हित दीर्घ)val;
		पूर्ण अन्यथा अणु
			*negp = false;
			lval = (अचिन्हित दीर्घ)val;
		पूर्ण
		*lvalp = lval / HZ;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक करो_proc_करोपूर्णांकvec_userhz_jअगरfies_conv(bool *negp, अचिन्हित दीर्घ *lvalp,
						पूर्णांक *valp,
						पूर्णांक ग_लिखो, व्योम *data)
अणु
	अगर (ग_लिखो) अणु
		अगर (USER_HZ < HZ && *lvalp > (दीर्घ_उच्च / HZ) * USER_HZ)
			वापस 1;
		*valp = घड़ी_प्रकार_to_jअगरfies(*negp ? -*lvalp : *lvalp);
	पूर्ण अन्यथा अणु
		पूर्णांक val = *valp;
		अचिन्हित दीर्घ lval;
		अगर (val < 0) अणु
			*negp = true;
			lval = -(अचिन्हित दीर्घ)val;
		पूर्ण अन्यथा अणु
			*negp = false;
			lval = (अचिन्हित दीर्घ)val;
		पूर्ण
		*lvalp = jअगरfies_to_घड़ी_प्रकार(lval);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक करो_proc_करोपूर्णांकvec_ms_jअगरfies_conv(bool *negp, अचिन्हित दीर्घ *lvalp,
					    पूर्णांक *valp,
					    पूर्णांक ग_लिखो, व्योम *data)
अणु
	अगर (ग_लिखो) अणु
		अचिन्हित दीर्घ jअगर = msecs_to_jअगरfies(*negp ? -*lvalp : *lvalp);

		अगर (jअगर > पूर्णांक_उच्च)
			वापस 1;
		*valp = (पूर्णांक)jअगर;
	पूर्ण अन्यथा अणु
		पूर्णांक val = *valp;
		अचिन्हित दीर्घ lval;
		अगर (val < 0) अणु
			*negp = true;
			lval = -(अचिन्हित दीर्घ)val;
		पूर्ण अन्यथा अणु
			*negp = false;
			lval = (अचिन्हित दीर्घ)val;
		पूर्ण
		*lvalp = jअगरfies_to_msecs(lval);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * proc_करोपूर्णांकvec_jअगरfies - पढ़ो a vector of पूर्णांकegers as seconds
 * @table: the sysctl table
 * @ग_लिखो: %TRUE अगर this is a ग_लिखो to the sysctl file
 * @buffer: the user buffer
 * @lenp: the size of the user buffer
 * @ppos: file position
 *
 * Reads/ग_लिखोs up to table->maxlen/माप(अचिन्हित पूर्णांक) पूर्णांकeger
 * values from/to the user buffer, treated as an ASCII string. 
 * The values पढ़ो are assumed to be in seconds, and are converted पूर्णांकo
 * jअगरfies.
 *
 * Returns 0 on success.
 */
पूर्णांक proc_करोपूर्णांकvec_jअगरfies(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			  व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
    वापस करो_proc_करोपूर्णांकvec(table,ग_लिखो,buffer,lenp,ppos,
		    	    करो_proc_करोपूर्णांकvec_jअगरfies_conv,शून्य);
पूर्ण

/**
 * proc_करोपूर्णांकvec_userhz_jअगरfies - पढ़ो a vector of पूर्णांकegers as 1/USER_HZ seconds
 * @table: the sysctl table
 * @ग_लिखो: %TRUE अगर this is a ग_लिखो to the sysctl file
 * @buffer: the user buffer
 * @lenp: the size of the user buffer
 * @ppos: poपूर्णांकer to the file position
 *
 * Reads/ग_लिखोs up to table->maxlen/माप(अचिन्हित पूर्णांक) पूर्णांकeger
 * values from/to the user buffer, treated as an ASCII string. 
 * The values पढ़ो are assumed to be in 1/USER_HZ seconds, and 
 * are converted पूर्णांकo jअगरfies.
 *
 * Returns 0 on success.
 */
पूर्णांक proc_करोपूर्णांकvec_userhz_jअगरfies(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				 व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
    वापस करो_proc_करोपूर्णांकvec(table,ग_लिखो,buffer,lenp,ppos,
		    	    करो_proc_करोपूर्णांकvec_userhz_jअगरfies_conv,शून्य);
पूर्ण

/**
 * proc_करोपूर्णांकvec_ms_jअगरfies - पढ़ो a vector of पूर्णांकegers as 1 milliseconds
 * @table: the sysctl table
 * @ग_लिखो: %TRUE अगर this is a ग_लिखो to the sysctl file
 * @buffer: the user buffer
 * @lenp: the size of the user buffer
 * @ppos: file position
 * @ppos: the current position in the file
 *
 * Reads/ग_लिखोs up to table->maxlen/माप(अचिन्हित पूर्णांक) पूर्णांकeger
 * values from/to the user buffer, treated as an ASCII string. 
 * The values पढ़ो are assumed to be in 1/1000 seconds, and 
 * are converted पूर्णांकo jअगरfies.
 *
 * Returns 0 on success.
 */
पूर्णांक proc_करोपूर्णांकvec_ms_jअगरfies(काष्ठा ctl_table *table, पूर्णांक ग_लिखो, व्योम *buffer,
		माप_प्रकार *lenp, loff_t *ppos)
अणु
	वापस करो_proc_करोपूर्णांकvec(table, ग_लिखो, buffer, lenp, ppos,
				करो_proc_करोपूर्णांकvec_ms_jअगरfies_conv, शून्य);
पूर्ण

अटल पूर्णांक proc_करो_cad_pid(काष्ठा ctl_table *table, पूर्णांक ग_लिखो, व्योम *buffer,
		माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा pid *new_pid;
	pid_t पंचांगp;
	पूर्णांक r;

	पंचांगp = pid_vnr(cad_pid);

	r = __करो_proc_करोपूर्णांकvec(&पंचांगp, table, ग_लिखो, buffer,
			       lenp, ppos, शून्य, शून्य);
	अगर (r || !ग_लिखो)
		वापस r;

	new_pid = find_get_pid(पंचांगp);
	अगर (!new_pid)
		वापस -ESRCH;

	put_pid(xchg(&cad_pid, new_pid));
	वापस 0;
पूर्ण

/**
 * proc_करो_large_biपंचांगap - पढ़ो/ग_लिखो from/to a large biपंचांगap
 * @table: the sysctl table
 * @ग_लिखो: %TRUE अगर this is a ग_लिखो to the sysctl file
 * @buffer: the user buffer
 * @lenp: the size of the user buffer
 * @ppos: file position
 *
 * The biपंचांगap is stored at table->data and the biपंचांगap length (in bits)
 * in table->maxlen.
 *
 * We use a range comma separated क्रमmat (e.g. 1,3-4,10-10) so that
 * large biपंचांगaps may be represented in a compact manner. Writing पूर्णांकo
 * the file will clear the biपंचांगap then update it with the given input.
 *
 * Returns 0 on success.
 */
पूर्णांक proc_करो_large_biपंचांगap(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			 व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक err = 0;
	bool first = 1;
	माप_प्रकार left = *lenp;
	अचिन्हित दीर्घ biपंचांगap_len = table->maxlen;
	अचिन्हित दीर्घ *biपंचांगap = *(अचिन्हित दीर्घ **) table->data;
	अचिन्हित दीर्घ *पंचांगp_biपंचांगap = शून्य;
	अक्षर tr_a[] = अणु '-', ',', '\n' }, tr_b[] = { ',', '\n', 0 पूर्ण, c;

	अगर (!biपंचांगap || !biपंचांगap_len || !left || (*ppos && !ग_लिखो)) अणु
		*lenp = 0;
		वापस 0;
	पूर्ण

	अगर (ग_लिखो) अणु
		अक्षर *p = buffer;
		माप_प्रकार skipped = 0;

		अगर (left > PAGE_SIZE - 1) अणु
			left = PAGE_SIZE - 1;
			/* How much of the buffer we'll skip this pass */
			skipped = *lenp - left;
		पूर्ण

		पंचांगp_biपंचांगap = biपंचांगap_zalloc(biपंचांगap_len, GFP_KERNEL);
		अगर (!पंचांगp_biपंचांगap)
			वापस -ENOMEM;
		proc_skip_अक्षर(&p, &left, '\n');
		जबतक (!err && left) अणु
			अचिन्हित दीर्घ val_a, val_b;
			bool neg;
			माप_प्रकार saved_left;

			/* In हाल we stop parsing mid-number, we can reset */
			saved_left = left;
			err = proc_get_दीर्घ(&p, &left, &val_a, &neg, tr_a,
					     माप(tr_a), &c);
			/*
			 * If we consumed the entirety of a truncated buffer or
			 * only one अक्षर is left (may be a "-"), then stop here,
			 * reset, & come back क्रम more.
			 */
			अगर ((left <= 1) && skipped) अणु
				left = saved_left;
				अवरोध;
			पूर्ण

			अगर (err)
				अवरोध;
			अगर (val_a >= biपंचांगap_len || neg) अणु
				err = -EINVAL;
				अवरोध;
			पूर्ण

			val_b = val_a;
			अगर (left) अणु
				p++;
				left--;
			पूर्ण

			अगर (c == '-') अणु
				err = proc_get_दीर्घ(&p, &left, &val_b,
						     &neg, tr_b, माप(tr_b),
						     &c);
				/*
				 * If we consumed all of a truncated buffer or
				 * then stop here, reset, & come back क्रम more.
				 */
				अगर (!left && skipped) अणु
					left = saved_left;
					अवरोध;
				पूर्ण

				अगर (err)
					अवरोध;
				अगर (val_b >= biपंचांगap_len || neg ||
				    val_a > val_b) अणु
					err = -EINVAL;
					अवरोध;
				पूर्ण
				अगर (left) अणु
					p++;
					left--;
				पूर्ण
			पूर्ण

			biपंचांगap_set(पंचांगp_biपंचांगap, val_a, val_b - val_a + 1);
			first = 0;
			proc_skip_अक्षर(&p, &left, '\n');
		पूर्ण
		left += skipped;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ bit_a, bit_b = 0;

		जबतक (left) अणु
			bit_a = find_next_bit(biपंचांगap, biपंचांगap_len, bit_b);
			अगर (bit_a >= biपंचांगap_len)
				अवरोध;
			bit_b = find_next_zero_bit(biपंचांगap, biपंचांगap_len,
						   bit_a + 1) - 1;

			अगर (!first)
				proc_put_अक्षर(&buffer, &left, ',');
			proc_put_दीर्घ(&buffer, &left, bit_a, false);
			अगर (bit_a != bit_b) अणु
				proc_put_अक्षर(&buffer, &left, '-');
				proc_put_दीर्घ(&buffer, &left, bit_b, false);
			पूर्ण

			first = 0; bit_b++;
		पूर्ण
		proc_put_अक्षर(&buffer, &left, '\n');
	पूर्ण

	अगर (!err) अणु
		अगर (ग_लिखो) अणु
			अगर (*ppos)
				biपंचांगap_or(biपंचांगap, biपंचांगap, पंचांगp_biपंचांगap, biपंचांगap_len);
			अन्यथा
				biपंचांगap_copy(biपंचांगap, पंचांगp_biपंचांगap, biपंचांगap_len);
		पूर्ण
		*lenp -= left;
		*ppos += *lenp;
	पूर्ण

	biपंचांगap_मुक्त(पंचांगp_biपंचांगap);
	वापस err;
पूर्ण

#अन्यथा /* CONFIG_PROC_SYSCTL */

पूर्णांक proc_करोstring(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		  व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	वापस -ENOSYS;
पूर्ण

पूर्णांक proc_करोपूर्णांकvec(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		  व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	वापस -ENOSYS;
पूर्ण

पूर्णांक proc_करोuपूर्णांकvec(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		  व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	वापस -ENOSYS;
पूर्ण

पूर्णांक proc_करोपूर्णांकvec_minmax(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		    व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	वापस -ENOSYS;
पूर्ण

पूर्णांक proc_करोuपूर्णांकvec_minmax(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			  व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	वापस -ENOSYS;
पूर्ण

पूर्णांक proc_करोu8vec_minmax(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	वापस -ENOSYS;
पूर्ण

पूर्णांक proc_करोपूर्णांकvec_jअगरfies(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		    व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	वापस -ENOSYS;
पूर्ण

पूर्णांक proc_करोपूर्णांकvec_userhz_jअगरfies(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		    व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	वापस -ENOSYS;
पूर्ण

पूर्णांक proc_करोपूर्णांकvec_ms_jअगरfies(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			     व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	वापस -ENOSYS;
पूर्ण

पूर्णांक proc_करोuदीर्घvec_minmax(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		    व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	वापस -ENOSYS;
पूर्ण

पूर्णांक proc_करोuदीर्घvec_ms_jअगरfies_minmax(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
				      व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	वापस -ENOSYS;
पूर्ण

पूर्णांक proc_करो_large_biपंचांगap(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			 व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	वापस -ENOSYS;
पूर्ण

#पूर्ण_अगर /* CONFIG_PROC_SYSCTL */

#अगर defined(CONFIG_SYSCTL)
पूर्णांक proc_करो_अटल_key(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
		       व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	काष्ठा अटल_key *key = (काष्ठा अटल_key *)table->data;
	अटल DEFINE_MUTEX(अटल_key_mutex);
	पूर्णांक val, ret;
	काष्ठा ctl_table पंचांगp = अणु
		.data   = &val,
		.maxlen = माप(val),
		.mode   = table->mode,
		.extra1 = SYSCTL_ZERO,
		.extra2 = SYSCTL_ONE,
	पूर्ण;

	अगर (ग_लिखो && !capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	mutex_lock(&अटल_key_mutex);
	val = अटल_key_enabled(key);
	ret = proc_करोपूर्णांकvec_minmax(&पंचांगp, ग_लिखो, buffer, lenp, ppos);
	अगर (ग_लिखो && !ret) अणु
		अगर (val)
			अटल_key_enable(key);
		अन्यथा
			अटल_key_disable(key);
	पूर्ण
	mutex_unlock(&अटल_key_mutex);
	वापस ret;
पूर्ण

अटल काष्ठा ctl_table kern_table[] = अणु
	अणु
		.procname	= "sched_child_runs_first",
		.data		= &sysctl_sched_child_runs_first,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#अगर_घोषित CONFIG_SCHEDSTATS
	अणु
		.procname	= "sched_schedstats",
		.data		= शून्य,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= sysctl_schedstats,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_SCHEDSTATS */
#अगर_घोषित CONFIG_NUMA_BALANCING
	अणु
		.procname	= "numa_balancing",
		.data		= शून्य, /* filled in by handler */
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= sysctl_numa_balancing,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_NUMA_BALANCING */
	अणु
		.procname	= "sched_rt_period_us",
		.data		= &sysctl_sched_rt_period,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= sched_rt_handler,
	पूर्ण,
	अणु
		.procname	= "sched_rt_runtime_us",
		.data		= &sysctl_sched_rt_runसमय,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= sched_rt_handler,
	पूर्ण,
	अणु
		.procname	= "sched_deadline_period_max_us",
		.data		= &sysctl_sched_dl_period_max,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "sched_deadline_period_min_us",
		.data		= &sysctl_sched_dl_period_min,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "sched_rr_timeslice_ms",
		.data		= &sysctl_sched_rr_बारlice,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= sched_rr_handler,
	पूर्ण,
#अगर_घोषित CONFIG_UCLAMP_TASK
	अणु
		.procname	= "sched_util_clamp_min",
		.data		= &sysctl_sched_uclamp_util_min,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= sysctl_sched_uclamp_handler,
	पूर्ण,
	अणु
		.procname	= "sched_util_clamp_max",
		.data		= &sysctl_sched_uclamp_util_max,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= sysctl_sched_uclamp_handler,
	पूर्ण,
	अणु
		.procname	= "sched_util_clamp_min_rt_default",
		.data		= &sysctl_sched_uclamp_util_min_rt_शेष,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= sysctl_sched_uclamp_handler,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SCHED_AUTOGROUP
	अणु
		.procname	= "sched_autogroup_enabled",
		.data		= &sysctl_sched_स्वतःgroup_enabled,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CFS_BANDWIDTH
	अणु
		.procname	= "sched_cfs_bandwidth_slice_us",
		.data		= &sysctl_sched_cfs_bandwidth_slice,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ONE,
	पूर्ण,
#पूर्ण_अगर
#अगर defined(CONFIG_ENERGY_MODEL) && defined(CONFIG_CPU_FREQ_GOV_SCHEDUTIL)
	अणु
		.procname	= "sched_energy_aware",
		.data		= &sysctl_sched_energy_aware,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= sched_energy_aware_handler,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PROVE_LOCKING
	अणु
		.procname	= "prove_locking",
		.data		= &prove_locking,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_LOCK_STAT
	अणु
		.procname	= "lock_stat",
		.data		= &lock_stat,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.procname	= "panic",
		.data		= &panic_समयout,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#अगर_घोषित CONFIG_COREDUMP
	अणु
		.procname	= "core_uses_pid",
		.data		= &core_uses_pid,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "core_pattern",
		.data		= core_pattern,
		.maxlen		= CORENAME_MAX_SIZE,
		.mode		= 0644,
		.proc_handler	= proc_करोstring_coredump,
	पूर्ण,
	अणु
		.procname	= "core_pipe_limit",
		.data		= &core_pipe_limit,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PROC_SYSCTL
	अणु
		.procname	= "tainted",
		.maxlen 	= माप(दीर्घ),
		.mode		= 0644,
		.proc_handler	= proc_taपूर्णांक,
	पूर्ण,
	अणु
		.procname	= "sysctl_writes_strict",
		.data		= &sysctl_ग_लिखोs_strict,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &neg_one,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_LATENCYTOP
	अणु
		.procname	= "latencytop",
		.data		= &latencytop_enabled,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= sysctl_latencytop,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_BLK_DEV_INITRD
	अणु
		.procname	= "real-root-dev",
		.data		= &real_root_dev,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.procname	= "print-fatal-signals",
		.data		= &prपूर्णांक_fatal_संकेतs,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#अगर_घोषित CONFIG_SPARC
	अणु
		.procname	= "reboot-cmd",
		.data		= reboot_command,
		.maxlen		= 256,
		.mode		= 0644,
		.proc_handler	= proc_करोstring,
	पूर्ण,
	अणु
		.procname	= "stop-a",
		.data		= &stop_a_enabled,
		.maxlen		= माप (पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "scons-poweroff",
		.data		= &scons_pwroff,
		.maxlen		= माप (पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SPARC64
	अणु
		.procname	= "tsb-ratio",
		.data		= &sysctl_tsb_ratio,
		.maxlen		= माप (पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PARISC
	अणु
		.procname	= "soft-power",
		.data		= &pwrsw_enabled,
		.maxlen		= माप (पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SYSCTL_ARCH_UNALIGN_ALLOW
	अणु
		.procname	= "unaligned-trap",
		.data		= &unaligned_enabled,
		.maxlen		= माप (पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.procname	= "ctrl-alt-del",
		.data		= &C_A_D,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#अगर_घोषित CONFIG_FUNCTION_TRACER
	अणु
		.procname	= "ftrace_enabled",
		.data		= &ftrace_enabled,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= ftrace_enable_sysctl,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_STACK_TRACER
	अणु
		.procname	= "stack_tracer_enabled",
		.data		= &stack_tracer_enabled,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= stack_trace_sysctl,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_TRACING
	अणु
		.procname	= "ftrace_dump_on_oops",
		.data		= &ftrace_dump_on_oops,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "traceoff_on_warning",
		.data		= &__disable_trace_on_warning,
		.maxlen		= माप(__disable_trace_on_warning),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "tracepoint_printk",
		.data		= &tracepoपूर्णांक_prपूर्णांकk,
		.maxlen		= माप(tracepoपूर्णांक_prपूर्णांकk),
		.mode		= 0644,
		.proc_handler	= tracepoपूर्णांक_prपूर्णांकk_sysctl,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_KEXEC_CORE
	अणु
		.procname	= "kexec_load_disabled",
		.data		= &kexec_load_disabled,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		/* only handle a transition from शेष "0" to "1" */
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ONE,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_MODULES
	अणु
		.procname	= "modprobe",
		.data		= &modprobe_path,
		.maxlen		= KMOD_PATH_LEN,
		.mode		= 0644,
		.proc_handler	= proc_करोstring,
	पूर्ण,
	अणु
		.procname	= "modules_disabled",
		.data		= &modules_disabled,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		/* only handle a transition from शेष "0" to "1" */
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ONE,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_UEVENT_HELPER
	अणु
		.procname	= "hotplug",
		.data		= &uevent_helper,
		.maxlen		= UEVENT_HELPER_PATH_LEN,
		.mode		= 0644,
		.proc_handler	= proc_करोstring,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_CHR_DEV_SG
	अणु
		.procname	= "sg-big-buff",
		.data		= &sg_big_buff,
		.maxlen		= माप (पूर्णांक),
		.mode		= 0444,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_BSD_PROCESS_ACCT
	अणु
		.procname	= "acct",
		.data		= &acct_parm,
		.maxlen		= 3*माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_MAGIC_SYSRQ
	अणु
		.procname	= "sysrq",
		.data		= शून्य,
		.maxlen		= माप (पूर्णांक),
		.mode		= 0644,
		.proc_handler	= sysrq_sysctl_handler,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PROC_SYSCTL
	अणु
		.procname	= "cad_pid",
		.data		= शून्य,
		.maxlen		= माप (पूर्णांक),
		.mode		= 0600,
		.proc_handler	= proc_करो_cad_pid,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.procname	= "threads-max",
		.data		= शून्य,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= sysctl_max_thपढ़ोs,
	पूर्ण,
	अणु
		.procname	= "random",
		.mode		= 0555,
		.child		= अक्रमom_table,
	पूर्ण,
	अणु
		.procname	= "usermodehelper",
		.mode		= 0555,
		.child		= usermodehelper_table,
	पूर्ण,
#अगर_घोषित CONFIG_FW_LOADER_USER_HELPER
	अणु
		.procname	= "firmware_config",
		.mode		= 0555,
		.child		= firmware_config_table,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.procname	= "overflowuid",
		.data		= &overflowuid,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &minolduid,
		.extra2		= &maxolduid,
	पूर्ण,
	अणु
		.procname	= "overflowgid",
		.data		= &overflowgid,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &minolduid,
		.extra2		= &maxolduid,
	पूर्ण,
#अगर_घोषित CONFIG_S390
	अणु
		.procname	= "userprocess_debug",
		.data		= &show_unhandled_संकेतs,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SMP
	अणु
		.procname	= "oops_all_cpu_backtrace",
		.data		= &sysctl_oops_all_cpu_backtrace,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_SMP */
	अणु
		.procname	= "pid_max",
		.data		= &pid_max,
		.maxlen		= माप (पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &pid_max_min,
		.extra2		= &pid_max_max,
	पूर्ण,
	अणु
		.procname	= "panic_on_oops",
		.data		= &panic_on_oops,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "panic_print",
		.data		= &panic_prपूर्णांक,
		.maxlen		= माप(अचिन्हित दीर्घ),
		.mode		= 0644,
		.proc_handler	= proc_करोuदीर्घvec_minmax,
	पूर्ण,
#अगर defined CONFIG_PRINTK
	अणु
		.procname	= "printk",
		.data		= &console_loglevel,
		.maxlen		= 4*माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "printk_ratelimit",
		.data		= &prपूर्णांकk_ratelimit_state.पूर्णांकerval,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "printk_ratelimit_burst",
		.data		= &prपूर्णांकk_ratelimit_state.burst,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "printk_delay",
		.data		= &prपूर्णांकk_delay_msec,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &ten_thousand,
	पूर्ण,
	अणु
		.procname	= "printk_devkmsg",
		.data		= devkmsg_log_str,
		.maxlen		= DEVKMSG_STR_MAX_SIZE,
		.mode		= 0644,
		.proc_handler	= devkmsg_sysctl_set_loglvl,
	पूर्ण,
	अणु
		.procname	= "dmesg_restrict",
		.data		= &dmesg_restrict,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax_sysadmin,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
	अणु
		.procname	= "kptr_restrict",
		.data		= &kptr_restrict,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax_sysadmin,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &two,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.procname	= "ngroups_max",
		.data		= &ngroups_max,
		.maxlen		= माप (पूर्णांक),
		.mode		= 0444,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "cap_last_cap",
		.data		= (व्योम *)&cap_last_cap,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0444,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#अगर defined(CONFIG_LOCKUP_DETECTOR)
	अणु
		.procname       = "watchdog",
		.data		= &watchकरोg_user_enabled,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler   = proc_watchकरोg,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
	अणु
		.procname	= "watchdog_thresh",
		.data		= &watchकरोg_thresh,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_watchकरोg_thresh,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &sixty,
	पूर्ण,
	अणु
		.procname       = "nmi_watchdog",
		.data		= &nmi_watchकरोg_user_enabled,
		.maxlen		= माप(पूर्णांक),
		.mode		= NMI_WATCHDOG_SYSCTL_PERM,
		.proc_handler   = proc_nmi_watchकरोg,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
	अणु
		.procname	= "watchdog_cpumask",
		.data		= &watchकरोg_cpumask_bits,
		.maxlen		= NR_CPUS,
		.mode		= 0644,
		.proc_handler	= proc_watchकरोg_cpumask,
	पूर्ण,
#अगर_घोषित CONFIG_SOFTLOCKUP_DETECTOR
	अणु
		.procname       = "soft_watchdog",
		.data		= &soft_watchकरोg_user_enabled,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler   = proc_soft_watchकरोg,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
	अणु
		.procname	= "softlockup_panic",
		.data		= &softlockup_panic,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
#अगर_घोषित CONFIG_SMP
	अणु
		.procname	= "softlockup_all_cpu_backtrace",
		.data		= &sysctl_softlockup_all_cpu_backtrace,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_SMP */
#पूर्ण_अगर
#अगर_घोषित CONFIG_HARDLOCKUP_DETECTOR
	अणु
		.procname	= "hardlockup_panic",
		.data		= &hardlockup_panic,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
#अगर_घोषित CONFIG_SMP
	अणु
		.procname	= "hardlockup_all_cpu_backtrace",
		.data		= &sysctl_hardlockup_all_cpu_backtrace,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_SMP */
#पूर्ण_अगर
#पूर्ण_अगर

#अगर defined(CONFIG_X86_LOCAL_APIC) && defined(CONFIG_X86)
	अणु
		.procname       = "unknown_nmi_panic",
		.data           = &unknown_nmi_panic,
		.maxlen         = माप (पूर्णांक),
		.mode           = 0644,
		.proc_handler   = proc_करोपूर्णांकvec,
	पूर्ण,
#पूर्ण_अगर

#अगर (defined(CONFIG_X86_32) || defined(CONFIG_PARISC)) && \
	defined(CONFIG_DEBUG_STACKOVERFLOW)
	अणु
		.procname	= "panic_on_stackoverflow",
		.data		= &sysctl_panic_on_stackoverflow,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#पूर्ण_अगर
#अगर defined(CONFIG_X86)
	अणु
		.procname	= "panic_on_unrecovered_nmi",
		.data		= &panic_on_unrecovered_nmi,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "panic_on_io_nmi",
		.data		= &panic_on_io_nmi,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "bootloader_type",
		.data		= &bootloader_type,
		.maxlen		= माप (पूर्णांक),
		.mode		= 0444,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "bootloader_version",
		.data		= &bootloader_version,
		.maxlen		= माप (पूर्णांक),
		.mode		= 0444,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "io_delay_type",
		.data		= &io_delay_type,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#पूर्ण_अगर
#अगर defined(CONFIG_MMU)
	अणु
		.procname	= "randomize_va_space",
		.data		= &अक्रमomize_va_space,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#पूर्ण_अगर
#अगर defined(CONFIG_S390) && defined(CONFIG_SMP)
	अणु
		.procname	= "spin_retry",
		.data		= &spin_retry,
		.maxlen		= माप (पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#पूर्ण_अगर
#अगर	defined(CONFIG_ACPI_SLEEP) && defined(CONFIG_X86)
	अणु
		.procname	= "acpi_video_flags",
		.data		= &acpi_realmode_flags,
		.maxlen		= माप (अचिन्हित दीर्घ),
		.mode		= 0644,
		.proc_handler	= proc_करोuदीर्घvec_minmax,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SYSCTL_ARCH_UNALIGN_NO_WARN
	अणु
		.procname	= "ignore-unaligned-usertrap",
		.data		= &no_unaligned_warning,
		.maxlen		= माप (पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_IA64
	अणु
		.procname	= "unaligned-dump-stack",
		.data		= &unaligned_dump_stack,
		.maxlen		= माप (पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_DETECT_HUNG_TASK
#अगर_घोषित CONFIG_SMP
	अणु
		.procname	= "hung_task_all_cpu_backtrace",
		.data		= &sysctl_hung_task_all_cpu_backtrace,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_SMP */
	अणु
		.procname	= "hung_task_panic",
		.data		= &sysctl_hung_task_panic,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
	अणु
		.procname	= "hung_task_check_count",
		.data		= &sysctl_hung_task_check_count,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
	पूर्ण,
	अणु
		.procname	= "hung_task_timeout_secs",
		.data		= &sysctl_hung_task_समयout_secs,
		.maxlen		= माप(अचिन्हित दीर्घ),
		.mode		= 0644,
		.proc_handler	= proc_करोhung_task_समयout_secs,
		.extra2		= &hung_task_समयout_max,
	पूर्ण,
	अणु
		.procname	= "hung_task_check_interval_secs",
		.data		= &sysctl_hung_task_check_पूर्णांकerval_secs,
		.maxlen		= माप(अचिन्हित दीर्घ),
		.mode		= 0644,
		.proc_handler	= proc_करोhung_task_समयout_secs,
		.extra2		= &hung_task_समयout_max,
	पूर्ण,
	अणु
		.procname	= "hung_task_warnings",
		.data		= &sysctl_hung_task_warnings,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &neg_one,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_RT_MUTEXES
	अणु
		.procname	= "max_lock_depth",
		.data		= &max_lock_depth,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.procname	= "poweroff_cmd",
		.data		= &घातeroff_cmd,
		.maxlen		= POWEROFF_CMD_PATH_LEN,
		.mode		= 0644,
		.proc_handler	= proc_करोstring,
	पूर्ण,
#अगर_घोषित CONFIG_KEYS
	अणु
		.procname	= "keys",
		.mode		= 0555,
		.child		= key_sysctls,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_PERF_EVENTS
	/*
	 * User-space scripts rely on the existence of this file
	 * as a feature check क्रम perf_events being enabled.
	 *
	 * So it's an ABI, करो not हटाओ!
	 */
	अणु
		.procname	= "perf_event_paranoid",
		.data		= &sysctl_perf_event_paranoid,
		.maxlen		= माप(sysctl_perf_event_paranoid),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "perf_event_mlock_kb",
		.data		= &sysctl_perf_event_mlock,
		.maxlen		= माप(sysctl_perf_event_mlock),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "perf_event_max_sample_rate",
		.data		= &sysctl_perf_event_sample_rate,
		.maxlen		= माप(sysctl_perf_event_sample_rate),
		.mode		= 0644,
		.proc_handler	= perf_proc_update_handler,
		.extra1		= SYSCTL_ONE,
	पूर्ण,
	अणु
		.procname	= "perf_cpu_time_max_percent",
		.data		= &sysctl_perf_cpu_समय_max_percent,
		.maxlen		= माप(sysctl_perf_cpu_समय_max_percent),
		.mode		= 0644,
		.proc_handler	= perf_cpu_समय_max_percent_handler,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &one_hundred,
	पूर्ण,
	अणु
		.procname	= "perf_event_max_stack",
		.data		= &sysctl_perf_event_max_stack,
		.maxlen		= माप(sysctl_perf_event_max_stack),
		.mode		= 0644,
		.proc_handler	= perf_event_max_stack_handler,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &six_hundred_क्रमty_kb,
	पूर्ण,
	अणु
		.procname	= "perf_event_max_contexts_per_stack",
		.data		= &sysctl_perf_event_max_contexts_per_stack,
		.maxlen		= माप(sysctl_perf_event_max_contexts_per_stack),
		.mode		= 0644,
		.proc_handler	= perf_event_max_stack_handler,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &one_thousand,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.procname	= "panic_on_warn",
		.data		= &panic_on_warn,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
#अगर defined(CONFIG_SMP) && defined(CONFIG_NO_HZ_COMMON)
	अणु
		.procname	= "timer_migration",
		.data		= &sysctl_समयr_migration,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= समयr_migration_handler,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_BPF_SYSCALL
	अणु
		.procname	= "unprivileged_bpf_disabled",
		.data		= &sysctl_unprivileged_bpf_disabled,
		.maxlen		= माप(sysctl_unprivileged_bpf_disabled),
		.mode		= 0644,
		.proc_handler	= bpf_unpriv_handler,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &two,
	पूर्ण,
	अणु
		.procname	= "bpf_stats_enabled",
		.data		= &bpf_stats_enabled_key.key,
		.maxlen		= माप(bpf_stats_enabled_key),
		.mode		= 0644,
		.proc_handler	= bpf_stats_handler,
	पूर्ण,
#पूर्ण_अगर
#अगर defined(CONFIG_TREE_RCU)
	अणु
		.procname	= "panic_on_rcu_stall",
		.data		= &sysctl_panic_on_rcu_stall,
		.maxlen		= माप(sysctl_panic_on_rcu_stall),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
#पूर्ण_अगर
#अगर defined(CONFIG_TREE_RCU)
	अणु
		.procname	= "max_rcu_stall_to_panic",
		.data		= &sysctl_max_rcu_stall_to_panic,
		.maxlen		= माप(sysctl_max_rcu_stall_to_panic),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ONE,
		.extra2		= SYSCTL_पूर्णांक_उच्च,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_STACKLEAK_RUNTIME_DISABLE
	अणु
		.procname	= "stack_erasing",
		.data		= शून्य,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0600,
		.proc_handler	= stack_erasing_sysctl,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table vm_table[] = अणु
	अणु
		.procname	= "overcommit_memory",
		.data		= &sysctl_overcommit_memory,
		.maxlen		= माप(sysctl_overcommit_memory),
		.mode		= 0644,
		.proc_handler	= overcommit_policy_handler,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &two,
	पूर्ण,
	अणु
		.procname	= "panic_on_oom",
		.data		= &sysctl_panic_on_oom,
		.maxlen		= माप(sysctl_panic_on_oom),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &two,
	पूर्ण,
	अणु
		.procname	= "oom_kill_allocating_task",
		.data		= &sysctl_oom_समाप्त_allocating_task,
		.maxlen		= माप(sysctl_oom_समाप्त_allocating_task),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "oom_dump_tasks",
		.data		= &sysctl_oom_dump_tasks,
		.maxlen		= माप(sysctl_oom_dump_tasks),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
	अणु
		.procname	= "overcommit_ratio",
		.data		= &sysctl_overcommit_ratio,
		.maxlen		= माप(sysctl_overcommit_ratio),
		.mode		= 0644,
		.proc_handler	= overcommit_ratio_handler,
	पूर्ण,
	अणु
		.procname	= "overcommit_kbytes",
		.data		= &sysctl_overcommit_kbytes,
		.maxlen		= माप(sysctl_overcommit_kbytes),
		.mode		= 0644,
		.proc_handler	= overcommit_kbytes_handler,
	पूर्ण,
	अणु
		.procname	= "page-cluster",
		.data		= &page_cluster,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
	पूर्ण,
	अणु
		.procname	= "dirty_background_ratio",
		.data		= &dirty_background_ratio,
		.maxlen		= माप(dirty_background_ratio),
		.mode		= 0644,
		.proc_handler	= dirty_background_ratio_handler,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &one_hundred,
	पूर्ण,
	अणु
		.procname	= "dirty_background_bytes",
		.data		= &dirty_background_bytes,
		.maxlen		= माप(dirty_background_bytes),
		.mode		= 0644,
		.proc_handler	= dirty_background_bytes_handler,
		.extra1		= &one_ul,
	पूर्ण,
	अणु
		.procname	= "dirty_ratio",
		.data		= &vm_dirty_ratio,
		.maxlen		= माप(vm_dirty_ratio),
		.mode		= 0644,
		.proc_handler	= dirty_ratio_handler,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &one_hundred,
	पूर्ण,
	अणु
		.procname	= "dirty_bytes",
		.data		= &vm_dirty_bytes,
		.maxlen		= माप(vm_dirty_bytes),
		.mode		= 0644,
		.proc_handler	= dirty_bytes_handler,
		.extra1		= &dirty_bytes_min,
	पूर्ण,
	अणु
		.procname	= "dirty_writeback_centisecs",
		.data		= &dirty_ग_लिखोback_पूर्णांकerval,
		.maxlen		= माप(dirty_ग_लिखोback_पूर्णांकerval),
		.mode		= 0644,
		.proc_handler	= dirty_ग_लिखोback_centisecs_handler,
	पूर्ण,
	अणु
		.procname	= "dirty_expire_centisecs",
		.data		= &dirty_expire_पूर्णांकerval,
		.maxlen		= माप(dirty_expire_पूर्णांकerval),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
	पूर्ण,
	अणु
		.procname	= "dirtytime_expire_seconds",
		.data		= &dirtyसमय_expire_पूर्णांकerval,
		.maxlen		= माप(dirtyसमय_expire_पूर्णांकerval),
		.mode		= 0644,
		.proc_handler	= dirtyसमय_पूर्णांकerval_handler,
		.extra1		= SYSCTL_ZERO,
	पूर्ण,
	अणु
		.procname	= "swappiness",
		.data		= &vm_swappiness,
		.maxlen		= माप(vm_swappiness),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &two_hundred,
	पूर्ण,
#अगर_घोषित CONFIG_HUGETLB_PAGE
	अणु
		.procname	= "nr_hugepages",
		.data		= शून्य,
		.maxlen		= माप(अचिन्हित दीर्घ),
		.mode		= 0644,
		.proc_handler	= hugetlb_sysctl_handler,
	पूर्ण,
#अगर_घोषित CONFIG_NUMA
	अणु
		.procname       = "nr_hugepages_mempolicy",
		.data           = शून्य,
		.maxlen         = माप(अचिन्हित दीर्घ),
		.mode           = 0644,
		.proc_handler   = &hugetlb_mempolicy_sysctl_handler,
	पूर्ण,
	अणु
		.procname		= "numa_stat",
		.data			= &sysctl_vm_numa_stat,
		.maxlen			= माप(पूर्णांक),
		.mode			= 0644,
		.proc_handler	= sysctl_vm_numa_stat_handler,
		.extra1			= SYSCTL_ZERO,
		.extra2			= SYSCTL_ONE,
	पूर्ण,
#पूर्ण_अगर
	 अणु
		.procname	= "hugetlb_shm_group",
		.data		= &sysctl_hugetlb_shm_group,
		.maxlen		= माप(gid_t),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	 पूर्ण,
	अणु
		.procname	= "nr_overcommit_hugepages",
		.data		= शून्य,
		.maxlen		= माप(अचिन्हित दीर्घ),
		.mode		= 0644,
		.proc_handler	= hugetlb_overcommit_handler,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.procname	= "lowmem_reserve_ratio",
		.data		= &sysctl_lowmem_reserve_ratio,
		.maxlen		= माप(sysctl_lowmem_reserve_ratio),
		.mode		= 0644,
		.proc_handler	= lowmem_reserve_ratio_sysctl_handler,
	पूर्ण,
	अणु
		.procname	= "drop_caches",
		.data		= &sysctl_drop_caches,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0200,
		.proc_handler	= drop_caches_sysctl_handler,
		.extra1		= SYSCTL_ONE,
		.extra2		= &four,
	पूर्ण,
#अगर_घोषित CONFIG_COMPACTION
	अणु
		.procname	= "compact_memory",
		.data		= शून्य,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0200,
		.proc_handler	= sysctl_compaction_handler,
	पूर्ण,
	अणु
		.procname	= "compaction_proactiveness",
		.data		= &sysctl_compaction_proactiveness,
		.maxlen		= माप(sysctl_compaction_proactiveness),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &one_hundred,
	पूर्ण,
	अणु
		.procname	= "extfrag_threshold",
		.data		= &sysctl_extfrag_threshold,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &min_extfrag_threshold,
		.extra2		= &max_extfrag_threshold,
	पूर्ण,
	अणु
		.procname	= "compact_unevictable_allowed",
		.data		= &sysctl_compact_unevictable_allowed,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax_warn_RT_change,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,

#पूर्ण_अगर /* CONFIG_COMPACTION */
	अणु
		.procname	= "min_free_kbytes",
		.data		= &min_मुक्त_kbytes,
		.maxlen		= माप(min_मुक्त_kbytes),
		.mode		= 0644,
		.proc_handler	= min_मुक्त_kbytes_sysctl_handler,
		.extra1		= SYSCTL_ZERO,
	पूर्ण,
	अणु
		.procname	= "watermark_boost_factor",
		.data		= &watermark_boost_factor,
		.maxlen		= माप(watermark_boost_factor),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
	पूर्ण,
	अणु
		.procname	= "watermark_scale_factor",
		.data		= &watermark_scale_factor,
		.maxlen		= माप(watermark_scale_factor),
		.mode		= 0644,
		.proc_handler	= watermark_scale_factor_sysctl_handler,
		.extra1		= SYSCTL_ONE,
		.extra2		= &one_thousand,
	पूर्ण,
	अणु
		.procname	= "percpu_pagelist_fraction",
		.data		= &percpu_pagelist_fraction,
		.maxlen		= माप(percpu_pagelist_fraction),
		.mode		= 0644,
		.proc_handler	= percpu_pagelist_fraction_sysctl_handler,
		.extra1		= SYSCTL_ZERO,
	पूर्ण,
	अणु
		.procname	= "page_lock_unfairness",
		.data		= &sysctl_page_lock_unfairness,
		.maxlen		= माप(sysctl_page_lock_unfairness),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
	पूर्ण,
#अगर_घोषित CONFIG_MMU
	अणु
		.procname	= "max_map_count",
		.data		= &sysctl_max_map_count,
		.maxlen		= माप(sysctl_max_map_count),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
	पूर्ण,
#अन्यथा
	अणु
		.procname	= "nr_trim_pages",
		.data		= &sysctl_nr_trim_pages,
		.maxlen		= माप(sysctl_nr_trim_pages),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.procname	= "laptop_mode",
		.data		= &laptop_mode,
		.maxlen		= माप(laptop_mode),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "block_dump",
		.data		= &block_dump,
		.maxlen		= माप(block_dump),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
	पूर्ण,
	अणु
		.procname	= "vfs_cache_pressure",
		.data		= &sysctl_vfs_cache_pressure,
		.maxlen		= माप(sysctl_vfs_cache_pressure),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
	पूर्ण,
#अगर defined(HAVE_ARCH_PICK_MMAP_LAYOUT) || \
    defined(CONFIG_ARCH_WANT_DEFAULT_TOPDOWN_MMAP_LAYOUT)
	अणु
		.procname	= "legacy_va_layout",
		.data		= &sysctl_legacy_va_layout,
		.maxlen		= माप(sysctl_legacy_va_layout),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_NUMA
	अणु
		.procname	= "zone_reclaim_mode",
		.data		= &node_reclaim_mode,
		.maxlen		= माप(node_reclaim_mode),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
	पूर्ण,
	अणु
		.procname	= "min_unmapped_ratio",
		.data		= &sysctl_min_unmapped_ratio,
		.maxlen		= माप(sysctl_min_unmapped_ratio),
		.mode		= 0644,
		.proc_handler	= sysctl_min_unmapped_ratio_sysctl_handler,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &one_hundred,
	पूर्ण,
	अणु
		.procname	= "min_slab_ratio",
		.data		= &sysctl_min_slab_ratio,
		.maxlen		= माप(sysctl_min_slab_ratio),
		.mode		= 0644,
		.proc_handler	= sysctl_min_slab_ratio_sysctl_handler,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &one_hundred,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SMP
	अणु
		.procname	= "stat_interval",
		.data		= &sysctl_stat_पूर्णांकerval,
		.maxlen		= माप(sysctl_stat_पूर्णांकerval),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_jअगरfies,
	पूर्ण,
	अणु
		.procname	= "stat_refresh",
		.data		= शून्य,
		.maxlen		= 0,
		.mode		= 0600,
		.proc_handler	= vmstat_refresh,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_MMU
	अणु
		.procname	= "mmap_min_addr",
		.data		= &dac_mmap_min_addr,
		.maxlen		= माप(अचिन्हित दीर्घ),
		.mode		= 0644,
		.proc_handler	= mmap_min_addr_handler,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_NUMA
	अणु
		.procname	= "numa_zonelist_order",
		.data		= &numa_zonelist_order,
		.maxlen		= NUMA_ZONELIST_ORDER_LEN,
		.mode		= 0644,
		.proc_handler	= numa_zonelist_order_handler,
	पूर्ण,
#पूर्ण_अगर
#अगर (defined(CONFIG_X86_32) && !defined(CONFIG_UML))|| \
   (defined(CONFIG_SUPERH) && defined(CONFIG_VSYSCALL))
	अणु
		.procname	= "vdso_enabled",
#अगर_घोषित CONFIG_X86_32
		.data		= &vdso32_enabled,
		.maxlen		= माप(vdso32_enabled),
#अन्यथा
		.data		= &vdso_enabled,
		.maxlen		= माप(vdso_enabled),
#पूर्ण_अगर
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
		.extra1		= SYSCTL_ZERO,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_HIGHMEM
	अणु
		.procname	= "highmem_is_dirtyable",
		.data		= &vm_highmem_is_dirtyable,
		.maxlen		= माप(vm_highmem_is_dirtyable),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_MEMORY_FAILURE
	अणु
		.procname	= "memory_failure_early_kill",
		.data		= &sysctl_memory_failure_early_समाप्त,
		.maxlen		= माप(sysctl_memory_failure_early_समाप्त),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
	अणु
		.procname	= "memory_failure_recovery",
		.data		= &sysctl_memory_failure_recovery,
		.maxlen		= माप(sysctl_memory_failure_recovery),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.procname	= "user_reserve_kbytes",
		.data		= &sysctl_user_reserve_kbytes,
		.maxlen		= माप(sysctl_user_reserve_kbytes),
		.mode		= 0644,
		.proc_handler	= proc_करोuदीर्घvec_minmax,
	पूर्ण,
	अणु
		.procname	= "admin_reserve_kbytes",
		.data		= &sysctl_admin_reserve_kbytes,
		.maxlen		= माप(sysctl_admin_reserve_kbytes),
		.mode		= 0644,
		.proc_handler	= proc_करोuदीर्घvec_minmax,
	पूर्ण,
#अगर_घोषित CONFIG_HAVE_ARCH_MMAP_RND_BITS
	अणु
		.procname	= "mmap_rnd_bits",
		.data		= &mmap_rnd_bits,
		.maxlen		= माप(mmap_rnd_bits),
		.mode		= 0600,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= (व्योम *)&mmap_rnd_bits_min,
		.extra2		= (व्योम *)&mmap_rnd_bits_max,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_HAVE_ARCH_MMAP_RND_COMPAT_BITS
	अणु
		.procname	= "mmap_rnd_compat_bits",
		.data		= &mmap_rnd_compat_bits,
		.maxlen		= माप(mmap_rnd_compat_bits),
		.mode		= 0600,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= (व्योम *)&mmap_rnd_compat_bits_min,
		.extra2		= (व्योम *)&mmap_rnd_compat_bits_max,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_USERFAULTFD
	अणु
		.procname	= "unprivileged_userfaultfd",
		.data		= &sysctl_unprivileged_userfaultfd,
		.maxlen		= माप(sysctl_unprivileged_userfaultfd),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table fs_table[] = अणु
	अणु
		.procname	= "inode-nr",
		.data		= &inodes_stat,
		.maxlen		= 2*माप(दीर्घ),
		.mode		= 0444,
		.proc_handler	= proc_nr_inodes,
	पूर्ण,
	अणु
		.procname	= "inode-state",
		.data		= &inodes_stat,
		.maxlen		= 7*माप(दीर्घ),
		.mode		= 0444,
		.proc_handler	= proc_nr_inodes,
	पूर्ण,
	अणु
		.procname	= "file-nr",
		.data		= &files_stat,
		.maxlen		= माप(files_stat),
		.mode		= 0444,
		.proc_handler	= proc_nr_files,
	पूर्ण,
	अणु
		.procname	= "file-max",
		.data		= &files_stat.max_files,
		.maxlen		= माप(files_stat.max_files),
		.mode		= 0644,
		.proc_handler	= proc_करोuदीर्घvec_minmax,
		.extra1		= &zero_ul,
		.extra2		= &दीर्घ_max,
	पूर्ण,
	अणु
		.procname	= "nr_open",
		.data		= &sysctl_nr_खोलो,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &sysctl_nr_खोलो_min,
		.extra2		= &sysctl_nr_खोलो_max,
	पूर्ण,
	अणु
		.procname	= "dentry-state",
		.data		= &dentry_stat,
		.maxlen		= 6*माप(दीर्घ),
		.mode		= 0444,
		.proc_handler	= proc_nr_dentry,
	पूर्ण,
	अणु
		.procname	= "overflowuid",
		.data		= &fs_overflowuid,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &minolduid,
		.extra2		= &maxolduid,
	पूर्ण,
	अणु
		.procname	= "overflowgid",
		.data		= &fs_overflowgid,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= &minolduid,
		.extra2		= &maxolduid,
	पूर्ण,
#अगर_घोषित CONFIG_खाता_LOCKING
	अणु
		.procname	= "leases-enable",
		.data		= &leases_enable,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_DNOTIFY
	अणु
		.procname	= "dir-notify-enable",
		.data		= &dir_notअगरy_enable,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_MMU
#अगर_घोषित CONFIG_खाता_LOCKING
	अणु
		.procname	= "lease-break-time",
		.data		= &lease_अवरोध_समय,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_AIO
	अणु
		.procname	= "aio-nr",
		.data		= &aio_nr,
		.maxlen		= माप(aio_nr),
		.mode		= 0444,
		.proc_handler	= proc_करोuदीर्घvec_minmax,
	पूर्ण,
	अणु
		.procname	= "aio-max-nr",
		.data		= &aio_max_nr,
		.maxlen		= माप(aio_max_nr),
		.mode		= 0644,
		.proc_handler	= proc_करोuदीर्घvec_minmax,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_AIO */
#अगर_घोषित CONFIG_INOTIFY_USER
	अणु
		.procname	= "inotify",
		.mode		= 0555,
		.child		= inotअगरy_table,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_FANOTIFY
	अणु
		.procname	= "fanotify",
		.mode		= 0555,
		.child		= fanotअगरy_table,
	पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_EPOLL
	अणु
		.procname	= "epoll",
		.mode		= 0555,
		.child		= epoll_table,
	पूर्ण,
#पूर्ण_अगर
#पूर्ण_अगर
	अणु
		.procname	= "protected_symlinks",
		.data		= &sysctl_रक्षित_symlinks,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0600,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
	अणु
		.procname	= "protected_hardlinks",
		.data		= &sysctl_रक्षित_hardlinks,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0600,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
	अणु
		.procname	= "protected_fifos",
		.data		= &sysctl_रक्षित_fअगरos,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0600,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &two,
	पूर्ण,
	अणु
		.procname	= "protected_regular",
		.data		= &sysctl_रक्षित_regular,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0600,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &two,
	पूर्ण,
	अणु
		.procname	= "suid_dumpable",
		.data		= &suid_dumpable,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax_coredump,
		.extra1		= SYSCTL_ZERO,
		.extra2		= &two,
	पूर्ण,
#अगर defined(CONFIG_BINFMT_MISC) || defined(CONFIG_BINFMT_MISC_MODULE)
	अणु
		.procname	= "binfmt_misc",
		.mode		= 0555,
		.child		= sysctl_mount_poपूर्णांक,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.procname	= "pipe-max-size",
		.data		= &pipe_max_size,
		.maxlen		= माप(pipe_max_size),
		.mode		= 0644,
		.proc_handler	= proc_करोpipe_max_size,
	पूर्ण,
	अणु
		.procname	= "pipe-user-pages-hard",
		.data		= &pipe_user_pages_hard,
		.maxlen		= माप(pipe_user_pages_hard),
		.mode		= 0644,
		.proc_handler	= proc_करोuदीर्घvec_minmax,
	पूर्ण,
	अणु
		.procname	= "pipe-user-pages-soft",
		.data		= &pipe_user_pages_soft,
		.maxlen		= माप(pipe_user_pages_soft),
		.mode		= 0644,
		.proc_handler	= proc_करोuदीर्घvec_minmax,
	पूर्ण,
	अणु
		.procname	= "mount-max",
		.data		= &sysctl_mount_max,
		.maxlen		= माप(अचिन्हित पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ONE,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table debug_table[] = अणु
#अगर_घोषित CONFIG_SYSCTL_EXCEPTION_TRACE
	अणु
		.procname	= "exception-trace",
		.data		= &show_unhandled_संकेतs,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec
	पूर्ण,
#पूर्ण_अगर
#अगर defined(CONFIG_OPTPROBES)
	अणु
		.procname	= "kprobes-optimization",
		.data		= &sysctl_kprobes_optimization,
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= proc_kprobes_optimization_handler,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table dev_table[] = अणु
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table sysctl_base_table[] = अणु
	अणु
		.procname	= "kernel",
		.mode		= 0555,
		.child		= kern_table,
	पूर्ण,
	अणु
		.procname	= "vm",
		.mode		= 0555,
		.child		= vm_table,
	पूर्ण,
	अणु
		.procname	= "fs",
		.mode		= 0555,
		.child		= fs_table,
	पूर्ण,
	अणु
		.procname	= "debug",
		.mode		= 0555,
		.child		= debug_table,
	पूर्ण,
	अणु
		.procname	= "dev",
		.mode		= 0555,
		.child		= dev_table,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

पूर्णांक __init sysctl_init(व्योम)
अणु
	काष्ठा ctl_table_header *hdr;

	hdr = रेजिस्टर_sysctl_table(sysctl_base_table);
	kmemleak_not_leak(hdr);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SYSCTL */
/*
 * No sense putting this after each symbol definition, twice,
 * exception granted :-)
 */
EXPORT_SYMBOL(proc_करोपूर्णांकvec);
EXPORT_SYMBOL(proc_करोuपूर्णांकvec);
EXPORT_SYMBOL(proc_करोपूर्णांकvec_jअगरfies);
EXPORT_SYMBOL(proc_करोपूर्णांकvec_minmax);
EXPORT_SYMBOL_GPL(proc_करोuपूर्णांकvec_minmax);
EXPORT_SYMBOL(proc_करोपूर्णांकvec_userhz_jअगरfies);
EXPORT_SYMBOL(proc_करोपूर्णांकvec_ms_jअगरfies);
EXPORT_SYMBOL(proc_करोstring);
EXPORT_SYMBOL(proc_करोuदीर्घvec_minmax);
EXPORT_SYMBOL(proc_करोuदीर्घvec_ms_jअगरfies_minmax);
EXPORT_SYMBOL(proc_करो_large_biपंचांगap);
