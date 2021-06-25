<शैली गुरु>
// SPDX-License-Identअगरier: GPL-1.0+
/*
 * n_tty.c --- implements the N_TTY line discipline.
 *
 * This code used to be in tty_io.c, but things are getting hairy
 * enough that it made sense to split things off.  (The N_TTY
 * processing has changed so much that it's hardly recognizable,
 * anyway...)
 *
 * Note that the खोलो routine क्रम N_TTY is guaranteed never to वापस
 * an error.  This is because Linux will fall back to setting a line
 * to N_TTY अगर it can not चयन to any other line discipline.
 *
 * Written by Theoकरोre Ts'o, Copyright 1994.
 *
 * This file also contains code originally written by Linus Torvalds,
 * Copyright 1991, 1992, 1993, and by Julian Cowley, Copyright 1994.
 *
 * Reduced memory usage क्रम older ARM प्रणालीs  - Russell King.
 *
 * 2000/01/20   Fixed SMP locking on put_tty_queue using bits of
 *		the patch by Andrew J. Kroll <ag784@मुक्तnet.buffalo.edu>
 *		who actually finally proved there really was a race.
 *
 * 2002/03/18   Implemented n_tty_wakeup to send SIGIO POLL_OUTs to
 *		रुकोing writing processes-Sapan Bhatia <sapan@corewars.org>.
 *		Also fixed a bug in BLOCKING mode where n_tty_ग_लिखो वापसs
 *		EAGAIN
 */

#समावेश <linux/types.h>
#समावेश <linux/major.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/fcntl.h>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/tty.h>
#समावेश <linux/समयr.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/poll.h>
#समावेश <linux/bitops.h>
#समावेश <linux/audit.h>
#समावेश <linux/file.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/module.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश "tty.h"

/*
 * Until this number of अक्षरacters is queued in the xmit buffer, select will
 * वापस "we have room for writes".
 */
#घोषणा WAKEUP_CHARS 256

/*
 * This defines the low- and high-watermarks क्रम throttling and
 * unthrottling the TTY driver.  These watermarks are used क्रम
 * controlling the space in the पढ़ो buffer.
 */
#घोषणा TTY_THRESHOLD_THROTTLE		128 /* now based on reमुख्यing room */
#घोषणा TTY_THRESHOLD_UNTHROTTLE	128

/*
 * Special byte codes used in the echo buffer to represent operations
 * or special handling of अक्षरacters.  Bytes in the echo buffer that
 * are not part of such special blocks are treated as normal अक्षरacter
 * codes.
 */
#घोषणा ECHO_OP_START 0xff
#घोषणा ECHO_OP_MOVE_BACK_COL 0x80
#घोषणा ECHO_OP_SET_CANON_COL 0x81
#घोषणा ECHO_OP_ERASE_TAB 0x82

#घोषणा ECHO_COMMIT_WATERMARK	256
#घोषणा ECHO_BLOCK		256
#घोषणा ECHO_DISCARD_WATERMARK	N_TTY_BUF_SIZE - (ECHO_BLOCK + 32)


#अघोषित N_TTY_TRACE
#अगर_घोषित N_TTY_TRACE
# define n_tty_trace(f, args...)	trace_prपूर्णांकk(f, ##args)
#अन्यथा
# define n_tty_trace(f, args...)	no_prपूर्णांकk(f, ##args)
#पूर्ण_अगर

काष्ठा n_tty_data अणु
	/* producer-published */
	माप_प्रकार पढ़ो_head;
	माप_प्रकार commit_head;
	माप_प्रकार canon_head;
	माप_प्रकार echo_head;
	माप_प्रकार echo_commit;
	माप_प्रकार echo_mark;
	DECLARE_BITMAP(अक्षर_map, 256);

	/* निजी to n_tty_receive_overrun (single-thपढ़ोed) */
	अचिन्हित दीर्घ overrun_समय;
	पूर्णांक num_overrun;

	/* non-atomic */
	bool no_room;

	/* must hold exclusive termios_rwsem to reset these */
	अचिन्हित अक्षर lnext:1, erasing:1, raw:1, real_raw:1, icanon:1;
	अचिन्हित अक्षर push:1;

	/* shared by producer and consumer */
	अक्षर पढ़ो_buf[N_TTY_BUF_SIZE];
	DECLARE_BITMAP(पढ़ो_flags, N_TTY_BUF_SIZE);
	अचिन्हित अक्षर echo_buf[N_TTY_BUF_SIZE];

	/* consumer-published */
	माप_प्रकार पढ़ो_tail;
	माप_प्रकार line_start;

	/* रक्षित by output lock */
	अचिन्हित पूर्णांक column;
	अचिन्हित पूर्णांक canon_column;
	माप_प्रकार echo_tail;

	काष्ठा mutex atomic_पढ़ो_lock;
	काष्ठा mutex output_lock;
पूर्ण;

#घोषणा MASK(x) ((x) & (N_TTY_BUF_SIZE - 1))

अटल अंतरभूत माप_प्रकार पढ़ो_cnt(काष्ठा n_tty_data *ldata)
अणु
	वापस ldata->पढ़ो_head - ldata->पढ़ो_tail;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर पढ़ो_buf(काष्ठा n_tty_data *ldata, माप_प्रकार i)
अणु
	वापस ldata->पढ़ो_buf[i & (N_TTY_BUF_SIZE - 1)];
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर *पढ़ो_buf_addr(काष्ठा n_tty_data *ldata, माप_प्रकार i)
अणु
	वापस &ldata->पढ़ो_buf[i & (N_TTY_BUF_SIZE - 1)];
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर echo_buf(काष्ठा n_tty_data *ldata, माप_प्रकार i)
अणु
	smp_rmb(); /* Matches smp_wmb() in add_echo_byte(). */
	वापस ldata->echo_buf[i & (N_TTY_BUF_SIZE - 1)];
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर *echo_buf_addr(काष्ठा n_tty_data *ldata, माप_प्रकार i)
अणु
	वापस &ldata->echo_buf[i & (N_TTY_BUF_SIZE - 1)];
पूर्ण

/* If we are not echoing the data, perhaps this is a secret so erase it */
अटल व्योम zero_buffer(काष्ठा tty_काष्ठा *tty, u8 *buffer, पूर्णांक size)
अणु
	bool icanon = !!L_ICANON(tty);
	bool no_echo = !L_ECHO(tty);

	अगर (icanon && no_echo)
		स_रखो(buffer, 0x00, size);
पूर्ण

अटल व्योम tty_copy(काष्ठा tty_काष्ठा *tty, व्योम *to, माप_प्रकार tail, माप_प्रकार n)
अणु
	काष्ठा n_tty_data *ldata = tty->disc_data;
	माप_प्रकार size = N_TTY_BUF_SIZE - tail;
	व्योम *from = पढ़ो_buf_addr(ldata, tail);

	अगर (n > size) अणु
		tty_audit_add_data(tty, from, size);
		स_नकल(to, from, size);
		zero_buffer(tty, from, size);
		to += size;
		n -= size;
		from = ldata->पढ़ो_buf;
	पूर्ण

	tty_audit_add_data(tty, from, n);
	स_नकल(to, from, n);
	zero_buffer(tty, from, n);
पूर्ण

/**
 *	n_tty_kick_worker - start input worker (अगर required)
 *	@tty: terminal
 *
 *	Re-schedules the flip buffer work अगर it may have stopped
 *
 *	Caller holds exclusive termios_rwsem
 *	   or
 *	n_tty_पढ़ो()/consumer path:
 *		holds non-exclusive termios_rwsem
 */

अटल व्योम n_tty_kick_worker(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा n_tty_data *ldata = tty->disc_data;

	/* Did the input worker stop? Restart it */
	अगर (unlikely(ldata->no_room)) अणु
		ldata->no_room = 0;

		WARN_RATELIMIT(tty->port->itty == शून्य,
				"scheduling with invalid itty\n");
		/* see अगर ldisc has been समाप्तed - अगर so, this means that
		 * even though the ldisc has been halted and ->buf.work
		 * cancelled, ->buf.work is about to be rescheduled
		 */
		WARN_RATELIMIT(test_bit(TTY_LDISC_HALTED, &tty->flags),
			       "scheduling buffer work for halted ldisc\n");
		tty_buffer_restart_work(tty->port);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा n_tty_data *ldata = tty->disc_data;
	sमाप_प्रकार n = 0;

	अगर (!ldata->icanon)
		n = ldata->commit_head - ldata->पढ़ो_tail;
	अन्यथा
		n = ldata->canon_head - ldata->पढ़ो_tail;
	वापस n;
पूर्ण

/**
 *	n_tty_ग_लिखो_wakeup	-	asynchronous I/O notअगरier
 *	@tty: tty device
 *
 *	Required क्रम the ptys, serial driver etc. since processes
 *	that attach themselves to the master and rely on ASYNC
 *	IO must be woken up
 */

अटल व्योम n_tty_ग_लिखो_wakeup(काष्ठा tty_काष्ठा *tty)
अणु
	clear_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);
	समाप्त_fasync(&tty->fasync, SIGIO, POLL_OUT);
पूर्ण

अटल व्योम n_tty_check_throttle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा n_tty_data *ldata = tty->disc_data;

	/*
	 * Check the reमुख्यing room क्रम the input canonicalization
	 * mode.  We करोn't want to throttle the driver if we're in
	 * canonical mode and करोn't have a newline yet!
	 */
	अगर (ldata->icanon && ldata->canon_head == ldata->पढ़ो_tail)
		वापस;

	जबतक (1) अणु
		पूर्णांक throttled;
		tty_set_flow_change(tty, TTY_THROTTLE_SAFE);
		अगर (N_TTY_BUF_SIZE - पढ़ो_cnt(ldata) >= TTY_THRESHOLD_THROTTLE)
			अवरोध;
		throttled = tty_throttle_safe(tty);
		अगर (!throttled)
			अवरोध;
	पूर्ण
	__tty_set_flow_change(tty, 0);
पूर्ण

अटल व्योम n_tty_check_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	अगर (tty->driver->type == TTY_DRIVER_TYPE_PTY) अणु
		अगर (अक्षरs_in_buffer(tty) > TTY_THRESHOLD_UNTHROTTLE)
			वापस;
		n_tty_kick_worker(tty);
		tty_wakeup(tty->link);
		वापस;
	पूर्ण

	/* If there is enough space in the पढ़ो buffer now, let the
	 * low-level driver know. We use अक्षरs_in_buffer() to
	 * check the buffer, as it now knows about canonical mode.
	 * Otherwise, अगर the driver is throttled and the line is
	 * दीर्घer than TTY_THRESHOLD_UNTHROTTLE in canonical mode,
	 * we won't get any more अक्षरacters.
	 */

	जबतक (1) अणु
		पूर्णांक unthrottled;
		tty_set_flow_change(tty, TTY_UNTHROTTLE_SAFE);
		अगर (अक्षरs_in_buffer(tty) > TTY_THRESHOLD_UNTHROTTLE)
			अवरोध;
		n_tty_kick_worker(tty);
		unthrottled = tty_unthrottle_safe(tty);
		अगर (!unthrottled)
			अवरोध;
	पूर्ण
	__tty_set_flow_change(tty, 0);
पूर्ण

/**
 *	put_tty_queue		-	add अक्षरacter to tty
 *	@c: अक्षरacter
 *	@ldata: n_tty data
 *
 *	Add a अक्षरacter to the tty पढ़ो_buf queue.
 *
 *	n_tty_receive_buf()/producer path:
 *		caller holds non-exclusive termios_rwsem
 */

अटल अंतरभूत व्योम put_tty_queue(अचिन्हित अक्षर c, काष्ठा n_tty_data *ldata)
अणु
	*पढ़ो_buf_addr(ldata, ldata->पढ़ो_head) = c;
	ldata->पढ़ो_head++;
पूर्ण

/**
 *	reset_buffer_flags	-	reset buffer state
 *	@ldata: line disc data to reset
 *
 *	Reset the पढ़ो buffer counters and clear the flags.
 *	Called from n_tty_खोलो() and n_tty_flush_buffer().
 *
 *	Locking: caller holds exclusive termios_rwsem
 *		 (or locking is not required)
 */

अटल व्योम reset_buffer_flags(काष्ठा n_tty_data *ldata)
अणु
	ldata->पढ़ो_head = ldata->canon_head = ldata->पढ़ो_tail = 0;
	ldata->commit_head = 0;
	ldata->line_start = 0;

	ldata->erasing = 0;
	biपंचांगap_zero(ldata->पढ़ो_flags, N_TTY_BUF_SIZE);
	ldata->push = 0;
पूर्ण

अटल व्योम n_tty_packet_mode_flush(काष्ठा tty_काष्ठा *tty)
अणु
	अचिन्हित दीर्घ flags;

	अगर (tty->link->packet) अणु
		spin_lock_irqsave(&tty->ctrl_lock, flags);
		tty->ctrl_status |= TIOCPKT_FLUSHREAD;
		spin_unlock_irqrestore(&tty->ctrl_lock, flags);
		wake_up_पूर्णांकerruptible(&tty->link->पढ़ो_रुको);
	पूर्ण
पूर्ण

/**
 *	n_tty_flush_buffer	-	clean input queue
 *	@tty:	terminal device
 *
 *	Flush the input buffer. Called when the tty layer wants the
 *	buffer flushed (eg at hangup) or when the N_TTY line discipline
 *	पूर्णांकernally has to clean the pending queue (क्रम example some संकेतs).
 *
 *	Holds termios_rwsem to exclude producer/consumer जबतक
 *	buffer indices are reset.
 *
 *	Locking: ctrl_lock, exclusive termios_rwsem
 */

अटल व्योम n_tty_flush_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	करोwn_ग_लिखो(&tty->termios_rwsem);
	reset_buffer_flags(tty->disc_data);
	n_tty_kick_worker(tty);

	अगर (tty->link)
		n_tty_packet_mode_flush(tty);
	up_ग_लिखो(&tty->termios_rwsem);
पूर्ण

/**
 *	is_utf8_continuation	-	utf8 multibyte check
 *	@c: byte to check
 *
 *	Returns true अगर the utf8 अक्षरacter 'c' is a multibyte continuation
 *	अक्षरacter. We use this to correctly compute the on screen size
 *	of the अक्षरacter when prपूर्णांकing
 */

अटल अंतरभूत पूर्णांक is_utf8_continuation(अचिन्हित अक्षर c)
अणु
	वापस (c & 0xc0) == 0x80;
पूर्ण

/**
 *	is_continuation		-	multibyte check
 *	@c: byte to check
 *	@tty: terminal device
 *
 *	Returns true अगर the utf8 अक्षरacter 'c' is a multibyte continuation
 *	अक्षरacter and the terminal is in unicode mode.
 */

अटल अंतरभूत पूर्णांक is_continuation(अचिन्हित अक्षर c, काष्ठा tty_काष्ठा *tty)
अणु
	वापस I_IUTF8(tty) && is_utf8_continuation(c);
पूर्ण

/**
 *	करो_output_अक्षर			-	output one अक्षरacter
 *	@c: अक्षरacter (or partial unicode symbol)
 *	@tty: terminal device
 *	@space: space available in tty driver ग_लिखो buffer
 *
 *	This is a helper function that handles one output अक्षरacter
 *	(including special अक्षरacters like TAB, CR, LF, etc.),
 *	करोing OPOST processing and putting the results in the
 *	tty driver's ग_लिखो buffer.
 *
 *	Note that Linux currently ignores TABDLY, CRDLY, VTDLY, FFDLY
 *	and NLDLY.  They simply aren't relevant in the world today.
 *	If you ever need them, add them here.
 *
 *	Returns the number of bytes of buffer space used or -1 अगर
 *	no space left.
 *
 *	Locking: should be called under the output_lock to protect
 *		 the column state and space left in the buffer
 */

अटल पूर्णांक करो_output_अक्षर(अचिन्हित अक्षर c, काष्ठा tty_काष्ठा *tty, पूर्णांक space)
अणु
	काष्ठा n_tty_data *ldata = tty->disc_data;
	पूर्णांक	spaces;

	अगर (!space)
		वापस -1;

	चयन (c) अणु
	हाल '\n':
		अगर (O_ONLRET(tty))
			ldata->column = 0;
		अगर (O_ONLCR(tty)) अणु
			अगर (space < 2)
				वापस -1;
			ldata->canon_column = ldata->column = 0;
			tty->ops->ग_लिखो(tty, "\r\n", 2);
			वापस 2;
		पूर्ण
		ldata->canon_column = ldata->column;
		अवरोध;
	हाल '\r':
		अगर (O_ONOCR(tty) && ldata->column == 0)
			वापस 0;
		अगर (O_OCRNL(tty)) अणु
			c = '\n';
			अगर (O_ONLRET(tty))
				ldata->canon_column = ldata->column = 0;
			अवरोध;
		पूर्ण
		ldata->canon_column = ldata->column = 0;
		अवरोध;
	हाल '\t':
		spaces = 8 - (ldata->column & 7);
		अगर (O_TABDLY(tty) == XTABS) अणु
			अगर (space < spaces)
				वापस -1;
			ldata->column += spaces;
			tty->ops->ग_लिखो(tty, "        ", spaces);
			वापस spaces;
		पूर्ण
		ldata->column += spaces;
		अवरोध;
	हाल '\b':
		अगर (ldata->column > 0)
			ldata->column--;
		अवरोध;
	शेष:
		अगर (!है_नियंत्रण(c)) अणु
			अगर (O_OLCUC(tty))
				c = बड़े(c);
			अगर (!is_continuation(c, tty))
				ldata->column++;
		पूर्ण
		अवरोध;
	पूर्ण

	tty_put_अक्षर(tty, c);
	वापस 1;
पूर्ण

/**
 *	process_output			-	output post processor
 *	@c: अक्षरacter (or partial unicode symbol)
 *	@tty: terminal device
 *
 *	Output one अक्षरacter with OPOST processing.
 *	Returns -1 when the output device is full and the अक्षरacter
 *	must be retried.
 *
 *	Locking: output_lock to protect column state and space left
 *		 (also, this is called from n_tty_ग_लिखो under the
 *		  tty layer ग_लिखो lock)
 */

अटल पूर्णांक process_output(अचिन्हित अक्षर c, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा n_tty_data *ldata = tty->disc_data;
	पूर्णांक	space, retval;

	mutex_lock(&ldata->output_lock);

	space = tty_ग_लिखो_room(tty);
	retval = करो_output_अक्षर(c, tty, space);

	mutex_unlock(&ldata->output_lock);
	अगर (retval < 0)
		वापस -1;
	अन्यथा
		वापस 0;
पूर्ण

/**
 *	process_output_block		-	block post processor
 *	@tty: terminal device
 *	@buf: अक्षरacter buffer
 *	@nr: number of bytes to output
 *
 *	Output a block of अक्षरacters with OPOST processing.
 *	Returns the number of अक्षरacters output.
 *
 *	This path is used to speed up block console ग_लिखोs, among other
 *	things when processing blocks of output data. It handles only
 *	the simple हालs normally found and helps to generate blocks of
 *	symbols क्रम the console driver and thus improve perक्रमmance.
 *
 *	Locking: output_lock to protect column state and space left
 *		 (also, this is called from n_tty_ग_लिखो under the
 *		  tty layer ग_लिखो lock)
 */

अटल sमाप_प्रकार process_output_block(काष्ठा tty_काष्ठा *tty,
				    स्थिर अचिन्हित अक्षर *buf, अचिन्हित पूर्णांक nr)
अणु
	काष्ठा n_tty_data *ldata = tty->disc_data;
	पूर्णांक	space;
	पूर्णांक	i;
	स्थिर अचिन्हित अक्षर *cp;

	mutex_lock(&ldata->output_lock);

	space = tty_ग_लिखो_room(tty);
	अगर (space <= 0) अणु
		mutex_unlock(&ldata->output_lock);
		वापस space;
	पूर्ण
	अगर (nr > space)
		nr = space;

	क्रम (i = 0, cp = buf; i < nr; i++, cp++) अणु
		अचिन्हित अक्षर c = *cp;

		चयन (c) अणु
		हाल '\n':
			अगर (O_ONLRET(tty))
				ldata->column = 0;
			अगर (O_ONLCR(tty))
				जाओ अवरोध_out;
			ldata->canon_column = ldata->column;
			अवरोध;
		हाल '\r':
			अगर (O_ONOCR(tty) && ldata->column == 0)
				जाओ अवरोध_out;
			अगर (O_OCRNL(tty))
				जाओ अवरोध_out;
			ldata->canon_column = ldata->column = 0;
			अवरोध;
		हाल '\t':
			जाओ अवरोध_out;
		हाल '\b':
			अगर (ldata->column > 0)
				ldata->column--;
			अवरोध;
		शेष:
			अगर (!है_नियंत्रण(c)) अणु
				अगर (O_OLCUC(tty))
					जाओ अवरोध_out;
				अगर (!is_continuation(c, tty))
					ldata->column++;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
अवरोध_out:
	i = tty->ops->ग_लिखो(tty, buf, i);

	mutex_unlock(&ldata->output_lock);
	वापस i;
पूर्ण

/**
 *	process_echoes	-	ग_लिखो pending echo अक्षरacters
 *	@tty: terminal device
 *
 *	Write previously buffered echo (and other ldisc-generated)
 *	अक्षरacters to the tty.
 *
 *	Characters generated by the ldisc (including echoes) need to
 *	be buffered because the driver's ग_लिखो buffer can fill during
 *	heavy program output.  Echoing straight to the driver will
 *	often fail under these conditions, causing lost अक्षरacters and
 *	resulting mismatches of ldisc state inक्रमmation.
 *
 *	Since the ldisc state must represent the अक्षरacters actually sent
 *	to the driver at the समय of the ग_लिखो, operations like certain
 *	changes in column state are also saved in the buffer and executed
 *	here.
 *
 *	A circular fअगरo buffer is used so that the most recent अक्षरacters
 *	are prioritized.  Also, when control अक्षरacters are echoed with a
 *	prefixed "^", the pair is treated atomically and thus not separated.
 *
 *	Locking: callers must hold output_lock
 */

अटल माप_प्रकार __process_echoes(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा n_tty_data *ldata = tty->disc_data;
	पूर्णांक	space, old_space;
	माप_प्रकार tail;
	अचिन्हित अक्षर c;

	old_space = space = tty_ग_लिखो_room(tty);

	tail = ldata->echo_tail;
	जबतक (MASK(ldata->echo_commit) != MASK(tail)) अणु
		c = echo_buf(ldata, tail);
		अगर (c == ECHO_OP_START) अणु
			अचिन्हित अक्षर op;
			पूर्णांक no_space_left = 0;

			/*
			 * Since add_echo_byte() is called without holding
			 * output_lock, we might see only portion of multi-byte
			 * operation.
			 */
			अगर (MASK(ldata->echo_commit) == MASK(tail + 1))
				जाओ not_yet_stored;
			/*
			 * If the buffer byte is the start of a multi-byte
			 * operation, get the next byte, which is either the
			 * op code or a control अक्षरacter value.
			 */
			op = echo_buf(ldata, tail + 1);

			चयन (op) अणु
			हाल ECHO_OP_ERASE_TAB: अणु
				अचिन्हित पूर्णांक num_अक्षरs, num_bs;

				अगर (MASK(ldata->echo_commit) == MASK(tail + 2))
					जाओ not_yet_stored;
				num_अक्षरs = echo_buf(ldata, tail + 2);

				/*
				 * Determine how many columns to go back
				 * in order to erase the tab.
				 * This depends on the number of columns
				 * used by other अक्षरacters within the tab
				 * area.  If this (modulo 8) count is from
				 * the start of input rather than from a
				 * previous tab, we offset by canon column.
				 * Otherwise, tab spacing is normal.
				 */
				अगर (!(num_अक्षरs & 0x80))
					num_अक्षरs += ldata->canon_column;
				num_bs = 8 - (num_अक्षरs & 7);

				अगर (num_bs > space) अणु
					no_space_left = 1;
					अवरोध;
				पूर्ण
				space -= num_bs;
				जबतक (num_bs--) अणु
					tty_put_अक्षर(tty, '\b');
					अगर (ldata->column > 0)
						ldata->column--;
				पूर्ण
				tail += 3;
				अवरोध;
			पूर्ण
			हाल ECHO_OP_SET_CANON_COL:
				ldata->canon_column = ldata->column;
				tail += 2;
				अवरोध;

			हाल ECHO_OP_MOVE_BACK_COL:
				अगर (ldata->column > 0)
					ldata->column--;
				tail += 2;
				अवरोध;

			हाल ECHO_OP_START:
				/* This is an escaped echo op start code */
				अगर (!space) अणु
					no_space_left = 1;
					अवरोध;
				पूर्ण
				tty_put_अक्षर(tty, ECHO_OP_START);
				ldata->column++;
				space--;
				tail += 2;
				अवरोध;

			शेष:
				/*
				 * If the op is not a special byte code,
				 * it is a ctrl अक्षर tagged to be echoed
				 * as "^X" (where X is the letter
				 * representing the control अक्षर).
				 * Note that we must ensure there is
				 * enough space क्रम the whole ctrl pair.
				 *
				 */
				अगर (space < 2) अणु
					no_space_left = 1;
					अवरोध;
				पूर्ण
				tty_put_अक्षर(tty, '^');
				tty_put_अक्षर(tty, op ^ 0100);
				ldata->column += 2;
				space -= 2;
				tail += 2;
			पूर्ण

			अगर (no_space_left)
				अवरोध;
		पूर्ण अन्यथा अणु
			अगर (O_OPOST(tty)) अणु
				पूर्णांक retval = करो_output_अक्षर(c, tty, space);
				अगर (retval < 0)
					अवरोध;
				space -= retval;
			पूर्ण अन्यथा अणु
				अगर (!space)
					अवरोध;
				tty_put_अक्षर(tty, c);
				space -= 1;
			पूर्ण
			tail += 1;
		पूर्ण
	पूर्ण

	/* If the echo buffer is nearly full (so that the possibility exists
	 * of echo overrun beक्रमe the next commit), then discard enough
	 * data at the tail to prevent a subsequent overrun */
	जबतक (ldata->echo_commit > tail &&
	       ldata->echo_commit - tail >= ECHO_DISCARD_WATERMARK) अणु
		अगर (echo_buf(ldata, tail) == ECHO_OP_START) अणु
			अगर (echo_buf(ldata, tail + 1) == ECHO_OP_ERASE_TAB)
				tail += 3;
			अन्यथा
				tail += 2;
		पूर्ण अन्यथा
			tail++;
	पूर्ण

 not_yet_stored:
	ldata->echo_tail = tail;
	वापस old_space - space;
पूर्ण

अटल व्योम commit_echoes(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा n_tty_data *ldata = tty->disc_data;
	माप_प्रकार nr, old, echoed;
	माप_प्रकार head;

	mutex_lock(&ldata->output_lock);
	head = ldata->echo_head;
	ldata->echo_mark = head;
	old = ldata->echo_commit - ldata->echo_tail;

	/* Process committed echoes अगर the accumulated # of bytes
	 * is over the threshold (and try again each समय another
	 * block is accumulated) */
	nr = head - ldata->echo_tail;
	अगर (nr < ECHO_COMMIT_WATERMARK ||
	    (nr % ECHO_BLOCK > old % ECHO_BLOCK)) अणु
		mutex_unlock(&ldata->output_lock);
		वापस;
	पूर्ण

	ldata->echo_commit = head;
	echoed = __process_echoes(tty);
	mutex_unlock(&ldata->output_lock);

	अगर (echoed && tty->ops->flush_अक्षरs)
		tty->ops->flush_अक्षरs(tty);
पूर्ण

अटल व्योम process_echoes(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा n_tty_data *ldata = tty->disc_data;
	माप_प्रकार echoed;

	अगर (ldata->echo_mark == ldata->echo_tail)
		वापस;

	mutex_lock(&ldata->output_lock);
	ldata->echo_commit = ldata->echo_mark;
	echoed = __process_echoes(tty);
	mutex_unlock(&ldata->output_lock);

	अगर (echoed && tty->ops->flush_अक्षरs)
		tty->ops->flush_अक्षरs(tty);
पूर्ण

/* NB: echo_mark and echo_head should be equivalent here */
अटल व्योम flush_echoes(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा n_tty_data *ldata = tty->disc_data;

	अगर ((!L_ECHO(tty) && !L_ECHONL(tty)) ||
	    ldata->echo_commit == ldata->echo_head)
		वापस;

	mutex_lock(&ldata->output_lock);
	ldata->echo_commit = ldata->echo_head;
	__process_echoes(tty);
	mutex_unlock(&ldata->output_lock);
पूर्ण

/**
 *	add_echo_byte	-	add a byte to the echo buffer
 *	@c: unicode byte to echo
 *	@ldata: n_tty data
 *
 *	Add a अक्षरacter or operation byte to the echo buffer.
 */

अटल अंतरभूत व्योम add_echo_byte(अचिन्हित अक्षर c, काष्ठा n_tty_data *ldata)
अणु
	*echo_buf_addr(ldata, ldata->echo_head) = c;
	smp_wmb(); /* Matches smp_rmb() in echo_buf(). */
	ldata->echo_head++;
पूर्ण

/**
 *	echo_move_back_col	-	add operation to move back a column
 *	@ldata: n_tty data
 *
 *	Add an operation to the echo buffer to move back one column.
 */

अटल व्योम echo_move_back_col(काष्ठा n_tty_data *ldata)
अणु
	add_echo_byte(ECHO_OP_START, ldata);
	add_echo_byte(ECHO_OP_MOVE_BACK_COL, ldata);
पूर्ण

/**
 *	echo_set_canon_col	-	add operation to set the canon column
 *	@ldata: n_tty data
 *
 *	Add an operation to the echo buffer to set the canon column
 *	to the current column.
 */

अटल व्योम echo_set_canon_col(काष्ठा n_tty_data *ldata)
अणु
	add_echo_byte(ECHO_OP_START, ldata);
	add_echo_byte(ECHO_OP_SET_CANON_COL, ldata);
पूर्ण

/**
 *	echo_erase_tab	-	add operation to erase a tab
 *	@num_अक्षरs: number of अक्षरacter columns alपढ़ोy used
 *	@after_tab: true अगर num_अक्षरs starts after a previous tab
 *	@ldata: n_tty data
 *
 *	Add an operation to the echo buffer to erase a tab.
 *
 *	Called by the eraser function, which knows how many अक्षरacter
 *	columns have been used since either a previous tab or the start
 *	of input.  This inक्रमmation will be used later, aदीर्घ with
 *	canon column (अगर applicable), to go back the correct number
 *	of columns.
 */

अटल व्योम echo_erase_tab(अचिन्हित पूर्णांक num_अक्षरs, पूर्णांक after_tab,
			   काष्ठा n_tty_data *ldata)
अणु
	add_echo_byte(ECHO_OP_START, ldata);
	add_echo_byte(ECHO_OP_ERASE_TAB, ldata);

	/* We only need to know this modulo 8 (tab spacing) */
	num_अक्षरs &= 7;

	/* Set the high bit as a flag अगर num_अक्षरs is after a previous tab */
	अगर (after_tab)
		num_अक्षरs |= 0x80;

	add_echo_byte(num_अक्षरs, ldata);
पूर्ण

/**
 *	echo_अक्षर_raw	-	echo a अक्षरacter raw
 *	@c: unicode byte to echo
 *	@ldata: line disc data
 *
 *	Echo user input back onto the screen. This must be called only when
 *	L_ECHO(tty) is true. Called from the driver receive_buf path.
 *
 *	This variant करोes not treat control अक्षरacters specially.
 */

अटल व्योम echo_अक्षर_raw(अचिन्हित अक्षर c, काष्ठा n_tty_data *ldata)
अणु
	अगर (c == ECHO_OP_START) अणु
		add_echo_byte(ECHO_OP_START, ldata);
		add_echo_byte(ECHO_OP_START, ldata);
	पूर्ण अन्यथा अणु
		add_echo_byte(c, ldata);
	पूर्ण
पूर्ण

/**
 *	echo_अक्षर	-	echo a अक्षरacter
 *	@c: unicode byte to echo
 *	@tty: terminal device
 *
 *	Echo user input back onto the screen. This must be called only when
 *	L_ECHO(tty) is true. Called from the driver receive_buf path.
 *
 *	This variant tags control अक्षरacters to be echoed as "^X"
 *	(where X is the letter representing the control अक्षर).
 */

अटल व्योम echo_अक्षर(अचिन्हित अक्षर c, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा n_tty_data *ldata = tty->disc_data;

	अगर (c == ECHO_OP_START) अणु
		add_echo_byte(ECHO_OP_START, ldata);
		add_echo_byte(ECHO_OP_START, ldata);
	पूर्ण अन्यथा अणु
		अगर (L_ECHOCTL(tty) && है_नियंत्रण(c) && c != '\t')
			add_echo_byte(ECHO_OP_START, ldata);
		add_echo_byte(c, ldata);
	पूर्ण
पूर्ण

/**
 *	finish_erasing		-	complete erase
 *	@ldata: n_tty data
 */

अटल अंतरभूत व्योम finish_erasing(काष्ठा n_tty_data *ldata)
अणु
	अगर (ldata->erasing) अणु
		echo_अक्षर_raw('/', ldata);
		ldata->erasing = 0;
	पूर्ण
पूर्ण

/**
 *	eraser		-	handle erase function
 *	@c: अक्षरacter input
 *	@tty: terminal device
 *
 *	Perक्रमm erase and necessary output when an erase अक्षरacter is
 *	present in the stream from the driver layer. Handles the complनिकासies
 *	of UTF-8 multibyte symbols.
 *
 *	n_tty_receive_buf()/producer path:
 *		caller holds non-exclusive termios_rwsem
 */

अटल व्योम eraser(अचिन्हित अक्षर c, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा n_tty_data *ldata = tty->disc_data;
	क्रमागत अणु ERASE, WERASE, KILL पूर्ण समाप्त_type;
	माप_प्रकार head;
	माप_प्रकार cnt;
	पूर्णांक seen_alnums;

	अगर (ldata->पढ़ो_head == ldata->canon_head) अणु
		/* process_output('\a', tty); */ /* what करो you think? */
		वापस;
	पूर्ण
	अगर (c == ERASE_CHAR(tty))
		समाप्त_type = ERASE;
	अन्यथा अगर (c == WERASE_CHAR(tty))
		समाप्त_type = WERASE;
	अन्यथा अणु
		अगर (!L_ECHO(tty)) अणु
			ldata->पढ़ो_head = ldata->canon_head;
			वापस;
		पूर्ण
		अगर (!L_ECHOK(tty) || !L_ECHOKE(tty) || !L_ECHOE(tty)) अणु
			ldata->पढ़ो_head = ldata->canon_head;
			finish_erasing(ldata);
			echo_अक्षर(KILL_CHAR(tty), tty);
			/* Add a newline अगर ECHOK is on and ECHOKE is off. */
			अगर (L_ECHOK(tty))
				echo_अक्षर_raw('\n', ldata);
			वापस;
		पूर्ण
		समाप्त_type = KILL;
	पूर्ण

	seen_alnums = 0;
	जबतक (MASK(ldata->पढ़ो_head) != MASK(ldata->canon_head)) अणु
		head = ldata->पढ़ो_head;

		/* erase a single possibly multibyte अक्षरacter */
		करो अणु
			head--;
			c = पढ़ो_buf(ldata, head);
		पूर्ण जबतक (is_continuation(c, tty) &&
			 MASK(head) != MASK(ldata->canon_head));

		/* करो not partially erase */
		अगर (is_continuation(c, tty))
			अवरोध;

		अगर (समाप्त_type == WERASE) अणु
			/* Equivalent to BSD's ALTWERASE. */
			अगर (है_अक्षर_अंक(c) || c == '_')
				seen_alnums++;
			अन्यथा अगर (seen_alnums)
				अवरोध;
		पूर्ण
		cnt = ldata->पढ़ो_head - head;
		ldata->पढ़ो_head = head;
		अगर (L_ECHO(tty)) अणु
			अगर (L_ECHOPRT(tty)) अणु
				अगर (!ldata->erasing) अणु
					echo_अक्षर_raw('\\', ldata);
					ldata->erasing = 1;
				पूर्ण
				/* अगर cnt > 1, output a multi-byte अक्षरacter */
				echo_अक्षर(c, tty);
				जबतक (--cnt > 0) अणु
					head++;
					echo_अक्षर_raw(पढ़ो_buf(ldata, head), ldata);
					echo_move_back_col(ldata);
				पूर्ण
			पूर्ण अन्यथा अगर (समाप्त_type == ERASE && !L_ECHOE(tty)) अणु
				echo_अक्षर(ERASE_CHAR(tty), tty);
			पूर्ण अन्यथा अगर (c == '\t') अणु
				अचिन्हित पूर्णांक num_अक्षरs = 0;
				पूर्णांक after_tab = 0;
				माप_प्रकार tail = ldata->पढ़ो_head;

				/*
				 * Count the columns used क्रम अक्षरacters
				 * since the start of input or after a
				 * previous tab.
				 * This info is used to go back the correct
				 * number of columns.
				 */
				जबतक (MASK(tail) != MASK(ldata->canon_head)) अणु
					tail--;
					c = पढ़ो_buf(ldata, tail);
					अगर (c == '\t') अणु
						after_tab = 1;
						अवरोध;
					पूर्ण अन्यथा अगर (है_नियंत्रण(c)) अणु
						अगर (L_ECHOCTL(tty))
							num_अक्षरs += 2;
					पूर्ण अन्यथा अगर (!is_continuation(c, tty)) अणु
						num_अक्षरs++;
					पूर्ण
				पूर्ण
				echo_erase_tab(num_अक्षरs, after_tab, ldata);
			पूर्ण अन्यथा अणु
				अगर (है_नियंत्रण(c) && L_ECHOCTL(tty)) अणु
					echo_अक्षर_raw('\b', ldata);
					echo_अक्षर_raw(' ', ldata);
					echo_अक्षर_raw('\b', ldata);
				पूर्ण
				अगर (!है_नियंत्रण(c) || L_ECHOCTL(tty)) अणु
					echo_अक्षर_raw('\b', ldata);
					echo_अक्षर_raw(' ', ldata);
					echo_अक्षर_raw('\b', ldata);
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (समाप्त_type == ERASE)
			अवरोध;
	पूर्ण
	अगर (ldata->पढ़ो_head == ldata->canon_head && L_ECHO(tty))
		finish_erasing(ldata);
पूर्ण

/**
 *	isig		-	handle the ISIG optio
 *	@sig: संकेत
 *	@tty: terminal
 *
 *	Called when a संकेत is being sent due to terminal input.
 *	Called from the driver receive_buf path so serialized.
 *
 *	Perक्रमms input and output flush अगर !NOFLSH. In this context, the echo
 *	buffer is 'output'. The संकेत is processed first to alert any current
 *	पढ़ोers or ग_लिखोrs to disजारी and निकास their i/o loops.
 *
 *	Locking: ctrl_lock
 */

अटल व्योम __isig(पूर्णांक sig, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा pid *tty_pgrp = tty_get_pgrp(tty);
	अगर (tty_pgrp) अणु
		समाप्त_pgrp(tty_pgrp, sig, 1);
		put_pid(tty_pgrp);
	पूर्ण
पूर्ण

अटल व्योम isig(पूर्णांक sig, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा n_tty_data *ldata = tty->disc_data;

	अगर (L_NOFLSH(tty)) अणु
		/* संकेत only */
		__isig(sig, tty);

	पूर्ण अन्यथा अणु /* संकेत and flush */
		up_पढ़ो(&tty->termios_rwsem);
		करोwn_ग_लिखो(&tty->termios_rwsem);

		__isig(sig, tty);

		/* clear echo buffer */
		mutex_lock(&ldata->output_lock);
		ldata->echo_head = ldata->echo_tail = 0;
		ldata->echo_mark = ldata->echo_commit = 0;
		mutex_unlock(&ldata->output_lock);

		/* clear output buffer */
		tty_driver_flush_buffer(tty);

		/* clear input buffer */
		reset_buffer_flags(tty->disc_data);

		/* notअगरy pty master of flush */
		अगर (tty->link)
			n_tty_packet_mode_flush(tty);

		up_ग_लिखो(&tty->termios_rwsem);
		करोwn_पढ़ो(&tty->termios_rwsem);
	पूर्ण
पूर्ण

/**
 *	n_tty_receive_अवरोध	-	handle अवरोध
 *	@tty: terminal
 *
 *	An RS232 अवरोध event has been hit in the incoming bitstream. This
 *	can cause a variety of events depending upon the termios settings.
 *
 *	n_tty_receive_buf()/producer path:
 *		caller holds non-exclusive termios_rwsem
 *
 *	Note: may get exclusive termios_rwsem अगर flushing input buffer
 */

अटल व्योम n_tty_receive_अवरोध(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा n_tty_data *ldata = tty->disc_data;

	अगर (I_IGNBRK(tty))
		वापस;
	अगर (I_BRKINT(tty)) अणु
		isig(संक_विघ्न, tty);
		वापस;
	पूर्ण
	अगर (I_PARMRK(tty)) अणु
		put_tty_queue('\377', ldata);
		put_tty_queue('\0', ldata);
	पूर्ण
	put_tty_queue('\0', ldata);
पूर्ण

/**
 *	n_tty_receive_overrun	-	handle overrun reporting
 *	@tty: terminal
 *
 *	Data arrived faster than we could process it. While the tty
 *	driver has flagged this the bits that were missed are gone
 *	क्रमever.
 *
 *	Called from the receive_buf path so single thपढ़ोed. Does not
 *	need locking as num_overrun and overrun_समय are function
 *	निजी.
 */

अटल व्योम n_tty_receive_overrun(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा n_tty_data *ldata = tty->disc_data;

	ldata->num_overrun++;
	अगर (समय_after(jअगरfies, ldata->overrun_समय + HZ) ||
			समय_after(ldata->overrun_समय, jअगरfies)) अणु
		tty_warn(tty, "%d input overrun(s)\n", ldata->num_overrun);
		ldata->overrun_समय = jअगरfies;
		ldata->num_overrun = 0;
	पूर्ण
पूर्ण

/**
 *	n_tty_receive_parity_error	-	error notअगरier
 *	@tty: terminal device
 *	@c: अक्षरacter
 *
 *	Process a parity error and queue the right data to indicate
 *	the error हाल अगर necessary.
 *
 *	n_tty_receive_buf()/producer path:
 *		caller holds non-exclusive termios_rwsem
 */
अटल व्योम n_tty_receive_parity_error(काष्ठा tty_काष्ठा *tty, अचिन्हित अक्षर c)
अणु
	काष्ठा n_tty_data *ldata = tty->disc_data;

	अगर (I_INPCK(tty)) अणु
		अगर (I_IGNPAR(tty))
			वापस;
		अगर (I_PARMRK(tty)) अणु
			put_tty_queue('\377', ldata);
			put_tty_queue('\0', ldata);
			put_tty_queue(c, ldata);
		पूर्ण अन्यथा
			put_tty_queue('\0', ldata);
	पूर्ण अन्यथा
		put_tty_queue(c, ldata);
पूर्ण

अटल व्योम
n_tty_receive_संकेत_अक्षर(काष्ठा tty_काष्ठा *tty, पूर्णांक संकेत, अचिन्हित अक्षर c)
अणु
	isig(संकेत, tty);
	अगर (I_IXON(tty))
		start_tty(tty);
	अगर (L_ECHO(tty)) अणु
		echo_अक्षर(c, tty);
		commit_echoes(tty);
	पूर्ण अन्यथा
		process_echoes(tty);
	वापस;
पूर्ण

/**
 *	n_tty_receive_अक्षर	-	perक्रमm processing
 *	@tty: terminal device
 *	@c: अक्षरacter
 *
 *	Process an inभागidual अक्षरacter of input received from the driver.
 *	This is serialized with respect to itself by the rules क्रम the
 *	driver above.
 *
 *	n_tty_receive_buf()/producer path:
 *		caller holds non-exclusive termios_rwsem
 *		publishes canon_head अगर canonical mode is active
 *
 *	Returns 1 अगर LNEXT was received, अन्यथा वापसs 0
 */

अटल पूर्णांक
n_tty_receive_अक्षर_special(काष्ठा tty_काष्ठा *tty, अचिन्हित अक्षर c)
अणु
	काष्ठा n_tty_data *ldata = tty->disc_data;

	अगर (I_IXON(tty)) अणु
		अगर (c == START_CHAR(tty)) अणु
			start_tty(tty);
			process_echoes(tty);
			वापस 0;
		पूर्ण
		अगर (c == STOP_CHAR(tty)) अणु
			stop_tty(tty);
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (L_ISIG(tty)) अणु
		अगर (c == INTR_CHAR(tty)) अणु
			n_tty_receive_संकेत_अक्षर(tty, संक_विघ्न, c);
			वापस 0;
		पूर्ण अन्यथा अगर (c == QUIT_CHAR(tty)) अणु
			n_tty_receive_संकेत_अक्षर(tty, SIGQUIT, c);
			वापस 0;
		पूर्ण अन्यथा अगर (c == SUSP_CHAR(tty)) अणु
			n_tty_receive_संकेत_अक्षर(tty, SIGTSTP, c);
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (tty->stopped && !tty->flow_stopped && I_IXON(tty) && I_IXANY(tty)) अणु
		start_tty(tty);
		process_echoes(tty);
	पूर्ण

	अगर (c == '\r') अणु
		अगर (I_IGNCR(tty))
			वापस 0;
		अगर (I_ICRNL(tty))
			c = '\n';
	पूर्ण अन्यथा अगर (c == '\n' && I_INLCR(tty))
		c = '\r';

	अगर (ldata->icanon) अणु
		अगर (c == ERASE_CHAR(tty) || c == KILL_CHAR(tty) ||
		    (c == WERASE_CHAR(tty) && L_IEXTEN(tty))) अणु
			eraser(c, tty);
			commit_echoes(tty);
			वापस 0;
		पूर्ण
		अगर (c == LNEXT_CHAR(tty) && L_IEXTEN(tty)) अणु
			ldata->lnext = 1;
			अगर (L_ECHO(tty)) अणु
				finish_erasing(ldata);
				अगर (L_ECHOCTL(tty)) अणु
					echo_अक्षर_raw('^', ldata);
					echo_अक्षर_raw('\b', ldata);
					commit_echoes(tty);
				पूर्ण
			पूर्ण
			वापस 1;
		पूर्ण
		अगर (c == REPRINT_CHAR(tty) && L_ECHO(tty) && L_IEXTEN(tty)) अणु
			माप_प्रकार tail = ldata->canon_head;

			finish_erasing(ldata);
			echo_अक्षर(c, tty);
			echo_अक्षर_raw('\n', ldata);
			जबतक (MASK(tail) != MASK(ldata->पढ़ो_head)) अणु
				echo_अक्षर(पढ़ो_buf(ldata, tail), tty);
				tail++;
			पूर्ण
			commit_echoes(tty);
			वापस 0;
		पूर्ण
		अगर (c == '\n') अणु
			अगर (L_ECHO(tty) || L_ECHONL(tty)) अणु
				echo_अक्षर_raw('\n', ldata);
				commit_echoes(tty);
			पूर्ण
			जाओ handle_newline;
		पूर्ण
		अगर (c == खातापूर्ण_CHAR(tty)) अणु
			c = __DISABLED_CHAR;
			जाओ handle_newline;
		पूर्ण
		अगर ((c == EOL_CHAR(tty)) ||
		    (c == EOL2_CHAR(tty) && L_IEXTEN(tty))) अणु
			/*
			 * XXX are EOL_CHAR and EOL2_CHAR echoed?!?
			 */
			अगर (L_ECHO(tty)) अणु
				/* Record the column of first canon अक्षर. */
				अगर (ldata->canon_head == ldata->पढ़ो_head)
					echo_set_canon_col(ldata);
				echo_अक्षर(c, tty);
				commit_echoes(tty);
			पूर्ण
			/*
			 * XXX करोes PARMRK करोubling happen क्रम
			 * EOL_CHAR and EOL2_CHAR?
			 */
			अगर (c == (अचिन्हित अक्षर) '\377' && I_PARMRK(tty))
				put_tty_queue(c, ldata);

handle_newline:
			set_bit(ldata->पढ़ो_head & (N_TTY_BUF_SIZE - 1), ldata->पढ़ो_flags);
			put_tty_queue(c, ldata);
			smp_store_release(&ldata->canon_head, ldata->पढ़ो_head);
			समाप्त_fasync(&tty->fasync, SIGIO, POLL_IN);
			wake_up_पूर्णांकerruptible_poll(&tty->पढ़ो_रुको, EPOLLIN);
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (L_ECHO(tty)) अणु
		finish_erasing(ldata);
		अगर (c == '\n')
			echo_अक्षर_raw('\n', ldata);
		अन्यथा अणु
			/* Record the column of first canon अक्षर. */
			अगर (ldata->canon_head == ldata->पढ़ो_head)
				echo_set_canon_col(ldata);
			echo_अक्षर(c, tty);
		पूर्ण
		commit_echoes(tty);
	पूर्ण

	/* PARMRK करोubling check */
	अगर (c == (अचिन्हित अक्षर) '\377' && I_PARMRK(tty))
		put_tty_queue(c, ldata);

	put_tty_queue(c, ldata);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
n_tty_receive_अक्षर_अंतरभूत(काष्ठा tty_काष्ठा *tty, अचिन्हित अक्षर c)
अणु
	काष्ठा n_tty_data *ldata = tty->disc_data;

	अगर (tty->stopped && !tty->flow_stopped && I_IXON(tty) && I_IXANY(tty)) अणु
		start_tty(tty);
		process_echoes(tty);
	पूर्ण
	अगर (L_ECHO(tty)) अणु
		finish_erasing(ldata);
		/* Record the column of first canon अक्षर. */
		अगर (ldata->canon_head == ldata->पढ़ो_head)
			echo_set_canon_col(ldata);
		echo_अक्षर(c, tty);
		commit_echoes(tty);
	पूर्ण
	/* PARMRK करोubling check */
	अगर (c == (अचिन्हित अक्षर) '\377' && I_PARMRK(tty))
		put_tty_queue(c, ldata);
	put_tty_queue(c, ldata);
पूर्ण

अटल व्योम n_tty_receive_अक्षर(काष्ठा tty_काष्ठा *tty, अचिन्हित अक्षर c)
अणु
	n_tty_receive_अक्षर_अंतरभूत(tty, c);
पूर्ण

अटल अंतरभूत व्योम
n_tty_receive_अक्षर_fast(काष्ठा tty_काष्ठा *tty, अचिन्हित अक्षर c)
अणु
	काष्ठा n_tty_data *ldata = tty->disc_data;

	अगर (tty->stopped && !tty->flow_stopped && I_IXON(tty) && I_IXANY(tty)) अणु
		start_tty(tty);
		process_echoes(tty);
	पूर्ण
	अगर (L_ECHO(tty)) अणु
		finish_erasing(ldata);
		/* Record the column of first canon अक्षर. */
		अगर (ldata->canon_head == ldata->पढ़ो_head)
			echo_set_canon_col(ldata);
		echo_अक्षर(c, tty);
		commit_echoes(tty);
	पूर्ण
	put_tty_queue(c, ldata);
पूर्ण

अटल व्योम n_tty_receive_अक्षर_closing(काष्ठा tty_काष्ठा *tty, अचिन्हित अक्षर c)
अणु
	अगर (I_ISTRIP(tty))
		c &= 0x7f;
	अगर (I_IUCLC(tty) && L_IEXTEN(tty))
		c = छोटे(c);

	अगर (I_IXON(tty)) अणु
		अगर (c == STOP_CHAR(tty))
			stop_tty(tty);
		अन्यथा अगर (c == START_CHAR(tty) ||
			 (tty->stopped && !tty->flow_stopped && I_IXANY(tty) &&
			  c != INTR_CHAR(tty) && c != QUIT_CHAR(tty) &&
			  c != SUSP_CHAR(tty))) अणु
			start_tty(tty);
			process_echoes(tty);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
n_tty_receive_अक्षर_flagged(काष्ठा tty_काष्ठा *tty, अचिन्हित अक्षर c, अक्षर flag)
अणु
	चयन (flag) अणु
	हाल TTY_BREAK:
		n_tty_receive_अवरोध(tty);
		अवरोध;
	हाल TTY_PARITY:
	हाल TTY_FRAME:
		n_tty_receive_parity_error(tty, c);
		अवरोध;
	हाल TTY_OVERRUN:
		n_tty_receive_overrun(tty);
		अवरोध;
	शेष:
		tty_err(tty, "unknown flag %d\n", flag);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
n_tty_receive_अक्षर_lnext(काष्ठा tty_काष्ठा *tty, अचिन्हित अक्षर c, अक्षर flag)
अणु
	काष्ठा n_tty_data *ldata = tty->disc_data;

	ldata->lnext = 0;
	अगर (likely(flag == TTY_NORMAL)) अणु
		अगर (I_ISTRIP(tty))
			c &= 0x7f;
		अगर (I_IUCLC(tty) && L_IEXTEN(tty))
			c = छोटे(c);
		n_tty_receive_अक्षर(tty, c);
	पूर्ण अन्यथा
		n_tty_receive_अक्षर_flagged(tty, c, flag);
पूर्ण

अटल व्योम
n_tty_receive_buf_real_raw(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *cp,
			   अक्षर *fp, पूर्णांक count)
अणु
	काष्ठा n_tty_data *ldata = tty->disc_data;
	माप_प्रकार n, head;

	head = ldata->पढ़ो_head & (N_TTY_BUF_SIZE - 1);
	n = min_t(माप_प्रकार, count, N_TTY_BUF_SIZE - head);
	स_नकल(पढ़ो_buf_addr(ldata, head), cp, n);
	ldata->पढ़ो_head += n;
	cp += n;
	count -= n;

	head = ldata->पढ़ो_head & (N_TTY_BUF_SIZE - 1);
	n = min_t(माप_प्रकार, count, N_TTY_BUF_SIZE - head);
	स_नकल(पढ़ो_buf_addr(ldata, head), cp, n);
	ldata->पढ़ो_head += n;
पूर्ण

अटल व्योम
n_tty_receive_buf_raw(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *cp,
		      अक्षर *fp, पूर्णांक count)
अणु
	काष्ठा n_tty_data *ldata = tty->disc_data;
	अक्षर flag = TTY_NORMAL;

	जबतक (count--) अणु
		अगर (fp)
			flag = *fp++;
		अगर (likely(flag == TTY_NORMAL))
			put_tty_queue(*cp++, ldata);
		अन्यथा
			n_tty_receive_अक्षर_flagged(tty, *cp++, flag);
	पूर्ण
पूर्ण

अटल व्योम
n_tty_receive_buf_closing(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *cp,
			  अक्षर *fp, पूर्णांक count)
अणु
	अक्षर flag = TTY_NORMAL;

	जबतक (count--) अणु
		अगर (fp)
			flag = *fp++;
		अगर (likely(flag == TTY_NORMAL))
			n_tty_receive_अक्षर_closing(tty, *cp++);
	पूर्ण
पूर्ण

अटल व्योम
n_tty_receive_buf_standard(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *cp,
			  अक्षर *fp, पूर्णांक count)
अणु
	काष्ठा n_tty_data *ldata = tty->disc_data;
	अक्षर flag = TTY_NORMAL;

	जबतक (count--) अणु
		अगर (fp)
			flag = *fp++;
		अगर (likely(flag == TTY_NORMAL)) अणु
			अचिन्हित अक्षर c = *cp++;

			अगर (I_ISTRIP(tty))
				c &= 0x7f;
			अगर (I_IUCLC(tty) && L_IEXTEN(tty))
				c = छोटे(c);
			अगर (L_EXTPROC(tty)) अणु
				put_tty_queue(c, ldata);
				जारी;
			पूर्ण
			अगर (!test_bit(c, ldata->अक्षर_map))
				n_tty_receive_अक्षर_अंतरभूत(tty, c);
			अन्यथा अगर (n_tty_receive_अक्षर_special(tty, c) && count) अणु
				अगर (fp)
					flag = *fp++;
				n_tty_receive_अक्षर_lnext(tty, *cp++, flag);
				count--;
			पूर्ण
		पूर्ण अन्यथा
			n_tty_receive_अक्षर_flagged(tty, *cp++, flag);
	पूर्ण
पूर्ण

अटल व्योम
n_tty_receive_buf_fast(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *cp,
		       अक्षर *fp, पूर्णांक count)
अणु
	काष्ठा n_tty_data *ldata = tty->disc_data;
	अक्षर flag = TTY_NORMAL;

	जबतक (count--) अणु
		अगर (fp)
			flag = *fp++;
		अगर (likely(flag == TTY_NORMAL)) अणु
			अचिन्हित अक्षर c = *cp++;

			अगर (!test_bit(c, ldata->अक्षर_map))
				n_tty_receive_अक्षर_fast(tty, c);
			अन्यथा अगर (n_tty_receive_अक्षर_special(tty, c) && count) अणु
				अगर (fp)
					flag = *fp++;
				n_tty_receive_अक्षर_lnext(tty, *cp++, flag);
				count--;
			पूर्ण
		पूर्ण अन्यथा
			n_tty_receive_अक्षर_flagged(tty, *cp++, flag);
	पूर्ण
पूर्ण

अटल व्योम __receive_buf(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *cp,
			  अक्षर *fp, पूर्णांक count)
अणु
	काष्ठा n_tty_data *ldata = tty->disc_data;
	bool preops = I_ISTRIP(tty) || (I_IUCLC(tty) && L_IEXTEN(tty));

	अगर (ldata->real_raw)
		n_tty_receive_buf_real_raw(tty, cp, fp, count);
	अन्यथा अगर (ldata->raw || (L_EXTPROC(tty) && !preops))
		n_tty_receive_buf_raw(tty, cp, fp, count);
	अन्यथा अगर (tty->closing && !L_EXTPROC(tty))
		n_tty_receive_buf_closing(tty, cp, fp, count);
	अन्यथा अणु
		अगर (ldata->lnext) अणु
			अक्षर flag = TTY_NORMAL;

			अगर (fp)
				flag = *fp++;
			n_tty_receive_अक्षर_lnext(tty, *cp++, flag);
			count--;
		पूर्ण

		अगर (!preops && !I_PARMRK(tty))
			n_tty_receive_buf_fast(tty, cp, fp, count);
		अन्यथा
			n_tty_receive_buf_standard(tty, cp, fp, count);

		flush_echoes(tty);
		अगर (tty->ops->flush_अक्षरs)
			tty->ops->flush_अक्षरs(tty);
	पूर्ण

	अगर (ldata->icanon && !L_EXTPROC(tty))
		वापस;

	/* publish पढ़ो_head to consumer */
	smp_store_release(&ldata->commit_head, ldata->पढ़ो_head);

	अगर (पढ़ो_cnt(ldata)) अणु
		समाप्त_fasync(&tty->fasync, SIGIO, POLL_IN);
		wake_up_पूर्णांकerruptible_poll(&tty->पढ़ो_रुको, EPOLLIN);
	पूर्ण
पूर्ण

/**
 *	n_tty_receive_buf_common	-	process input
 *	@tty: device to receive input
 *	@cp: input अक्षरs
 *	@fp: flags क्रम each अक्षर (अगर शून्य, all अक्षरs are TTY_NORMAL)
 *	@count: number of input अक्षरs in @cp
 *	@flow: enable flow control
 *
 *	Called by the terminal driver when a block of अक्षरacters has
 *	been received. This function must be called from soft contexts
 *	not from पूर्णांकerrupt context. The driver is responsible क्रम making
 *	calls one at a समय and in order (or using flush_to_ldisc)
 *
 *	Returns the # of input अक्षरs from @cp which were processed.
 *
 *	In canonical mode, the maximum line length is 4096 अक्षरs (including
 *	the line termination अक्षर); lines दीर्घer than 4096 अक्षरs are
 *	truncated. After 4095 अक्षरs, input data is still processed but
 *	not stored. Overflow processing ensures the tty can always
 *	receive more input until at least one line can be पढ़ो.
 *
 *	In non-canonical mode, the पढ़ो buffer will only accept 4095 अक्षरs;
 *	this provides the necessary space क्रम a newline अक्षर अगर the input
 *	mode is चयनed to canonical.
 *
 *	Note it is possible क्रम the पढ़ो buffer to _contain_ 4096 अक्षरs
 *	in non-canonical mode: the पढ़ो buffer could alपढ़ोy contain the
 *	maximum canon line of 4096 अक्षरs when the mode is चयनed to
 *	non-canonical.
 *
 *	n_tty_receive_buf()/producer path:
 *		claims non-exclusive termios_rwsem
 *		publishes commit_head or canon_head
 */
अटल पूर्णांक
n_tty_receive_buf_common(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *cp,
			 अक्षर *fp, पूर्णांक count, पूर्णांक flow)
अणु
	काष्ठा n_tty_data *ldata = tty->disc_data;
	पूर्णांक room, n, rcvd = 0, overflow;

	करोwn_पढ़ो(&tty->termios_rwsem);

	करो अणु
		/*
		 * When PARMRK is set, each input अक्षर may take up to 3 अक्षरs
		 * in the पढ़ो buf; reduce the buffer space avail by 3x
		 *
		 * If we are करोing input canonicalization, and there are no
		 * pending newlines, let अक्षरacters through without limit, so
		 * that erase अक्षरacters will be handled.  Other excess
		 * अक्षरacters will be beeped.
		 *
		 * paired with store in *_copy_from_पढ़ो_buf() -- guarantees
		 * the consumer has loaded the data in पढ़ो_buf up to the new
		 * पढ़ो_tail (so this producer will not overग_लिखो unपढ़ो data)
		 */
		माप_प्रकार tail = smp_load_acquire(&ldata->पढ़ो_tail);

		room = N_TTY_BUF_SIZE - (ldata->पढ़ो_head - tail);
		अगर (I_PARMRK(tty))
			room = (room + 2) / 3;
		room--;
		अगर (room <= 0) अणु
			overflow = ldata->icanon && ldata->canon_head == tail;
			अगर (overflow && room < 0)
				ldata->पढ़ो_head--;
			room = overflow;
			ldata->no_room = flow && !room;
		पूर्ण अन्यथा
			overflow = 0;

		n = min(count, room);
		अगर (!n)
			अवरोध;

		/* ignore parity errors अगर handling overflow */
		अगर (!overflow || !fp || *fp != TTY_PARITY)
			__receive_buf(tty, cp, fp, n);

		cp += n;
		अगर (fp)
			fp += n;
		count -= n;
		rcvd += n;
	पूर्ण जबतक (!test_bit(TTY_LDISC_CHANGING, &tty->flags));

	tty->receive_room = room;

	/* Unthrottle अगर handling overflow on pty */
	अगर (tty->driver->type == TTY_DRIVER_TYPE_PTY) अणु
		अगर (overflow) अणु
			tty_set_flow_change(tty, TTY_UNTHROTTLE_SAFE);
			tty_unthrottle_safe(tty);
			__tty_set_flow_change(tty, 0);
		पूर्ण
	पूर्ण अन्यथा
		n_tty_check_throttle(tty);

	up_पढ़ो(&tty->termios_rwsem);

	वापस rcvd;
पूर्ण

अटल व्योम n_tty_receive_buf(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *cp,
			      अक्षर *fp, पूर्णांक count)
अणु
	n_tty_receive_buf_common(tty, cp, fp, count, 0);
पूर्ण

अटल पूर्णांक n_tty_receive_buf2(काष्ठा tty_काष्ठा *tty, स्थिर अचिन्हित अक्षर *cp,
			      अक्षर *fp, पूर्णांक count)
अणु
	वापस n_tty_receive_buf_common(tty, cp, fp, count, 1);
पूर्ण

/**
 *	n_tty_set_termios	-	termios data changed
 *	@tty: terminal
 *	@old: previous data
 *
 *	Called by the tty layer when the user changes termios flags so
 *	that the line discipline can plan ahead. This function cannot sleep
 *	and is रक्षित from re-entry by the tty layer. The user is
 *	guaranteed that this function will not be re-entered or in progress
 *	when the ldisc is बंदd.
 *
 *	Locking: Caller holds tty->termios_rwsem
 */

अटल व्योम n_tty_set_termios(काष्ठा tty_काष्ठा *tty, काष्ठा ktermios *old)
अणु
	काष्ठा n_tty_data *ldata = tty->disc_data;

	अगर (!old || (old->c_lflag ^ tty->termios.c_lflag) & (ICANON | EXTPROC)) अणु
		biपंचांगap_zero(ldata->पढ़ो_flags, N_TTY_BUF_SIZE);
		ldata->line_start = ldata->पढ़ो_tail;
		अगर (!L_ICANON(tty) || !पढ़ो_cnt(ldata)) अणु
			ldata->canon_head = ldata->पढ़ो_tail;
			ldata->push = 0;
		पूर्ण अन्यथा अणु
			set_bit((ldata->पढ़ो_head - 1) & (N_TTY_BUF_SIZE - 1),
				ldata->पढ़ो_flags);
			ldata->canon_head = ldata->पढ़ो_head;
			ldata->push = 1;
		पूर्ण
		ldata->commit_head = ldata->पढ़ो_head;
		ldata->erasing = 0;
		ldata->lnext = 0;
	पूर्ण

	ldata->icanon = (L_ICANON(tty) != 0);

	अगर (I_ISTRIP(tty) || I_IUCLC(tty) || I_IGNCR(tty) ||
	    I_ICRNL(tty) || I_INLCR(tty) || L_ICANON(tty) ||
	    I_IXON(tty) || L_ISIG(tty) || L_ECHO(tty) ||
	    I_PARMRK(tty)) अणु
		biपंचांगap_zero(ldata->अक्षर_map, 256);

		अगर (I_IGNCR(tty) || I_ICRNL(tty))
			set_bit('\r', ldata->अक्षर_map);
		अगर (I_INLCR(tty))
			set_bit('\n', ldata->अक्षर_map);

		अगर (L_ICANON(tty)) अणु
			set_bit(ERASE_CHAR(tty), ldata->अक्षर_map);
			set_bit(KILL_CHAR(tty), ldata->अक्षर_map);
			set_bit(खातापूर्ण_CHAR(tty), ldata->अक्षर_map);
			set_bit('\n', ldata->अक्षर_map);
			set_bit(EOL_CHAR(tty), ldata->अक्षर_map);
			अगर (L_IEXTEN(tty)) अणु
				set_bit(WERASE_CHAR(tty), ldata->अक्षर_map);
				set_bit(LNEXT_CHAR(tty), ldata->अक्षर_map);
				set_bit(EOL2_CHAR(tty), ldata->अक्षर_map);
				अगर (L_ECHO(tty))
					set_bit(REPRINT_CHAR(tty),
						ldata->अक्षर_map);
			पूर्ण
		पूर्ण
		अगर (I_IXON(tty)) अणु
			set_bit(START_CHAR(tty), ldata->अक्षर_map);
			set_bit(STOP_CHAR(tty), ldata->अक्षर_map);
		पूर्ण
		अगर (L_ISIG(tty)) अणु
			set_bit(INTR_CHAR(tty), ldata->अक्षर_map);
			set_bit(QUIT_CHAR(tty), ldata->अक्षर_map);
			set_bit(SUSP_CHAR(tty), ldata->अक्षर_map);
		पूर्ण
		clear_bit(__DISABLED_CHAR, ldata->अक्षर_map);
		ldata->raw = 0;
		ldata->real_raw = 0;
	पूर्ण अन्यथा अणु
		ldata->raw = 1;
		अगर ((I_IGNBRK(tty) || (!I_BRKINT(tty) && !I_PARMRK(tty))) &&
		    (I_IGNPAR(tty) || !I_INPCK(tty)) &&
		    (tty->driver->flags & TTY_DRIVER_REAL_RAW))
			ldata->real_raw = 1;
		अन्यथा
			ldata->real_raw = 0;
	पूर्ण
	/*
	 * Fix tty hang when I_IXON(tty) is cleared, but the tty
	 * been stopped by STOP_CHAR(tty) beक्रमe it.
	 */
	अगर (!I_IXON(tty) && old && (old->c_अगरlag & IXON) && !tty->flow_stopped) अणु
		start_tty(tty);
		process_echoes(tty);
	पूर्ण

	/* The termios change make the tty पढ़ोy क्रम I/O */
	wake_up_पूर्णांकerruptible(&tty->ग_लिखो_रुको);
	wake_up_पूर्णांकerruptible(&tty->पढ़ो_रुको);
पूर्ण

/**
 *	n_tty_बंद		-	बंद the ldisc क्रम this tty
 *	@tty: device
 *
 *	Called from the terminal layer when this line discipline is
 *	being shut करोwn, either because of a बंद or becsuse of a
 *	discipline change. The function will not be called जबतक other
 *	ldisc methods are in progress.
 */

अटल व्योम n_tty_बंद(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा n_tty_data *ldata = tty->disc_data;

	अगर (tty->link)
		n_tty_packet_mode_flush(tty);

	करोwn_ग_लिखो(&tty->termios_rwsem);
	vमुक्त(ldata);
	tty->disc_data = शून्य;
	up_ग_लिखो(&tty->termios_rwsem);
पूर्ण

/**
 *	n_tty_खोलो		-	खोलो an ldisc
 *	@tty: terminal to खोलो
 *
 *	Called when this line discipline is being attached to the
 *	terminal device. Can sleep. Called serialized so that no
 *	other events will occur in parallel. No further खोलो will occur
 *	until a बंद.
 */

अटल पूर्णांक n_tty_खोलो(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा n_tty_data *ldata;

	/* Currently a दो_स्मृति failure here can panic */
	ldata = vzalloc(माप(*ldata));
	अगर (!ldata)
		वापस -ENOMEM;

	ldata->overrun_समय = jअगरfies;
	mutex_init(&ldata->atomic_पढ़ो_lock);
	mutex_init(&ldata->output_lock);

	tty->disc_data = ldata;
	tty->closing = 0;
	/* indicate buffer work may resume */
	clear_bit(TTY_LDISC_HALTED, &tty->flags);
	n_tty_set_termios(tty, शून्य);
	tty_unthrottle(tty);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक input_available_p(काष्ठा tty_काष्ठा *tty, पूर्णांक poll)
अणु
	काष्ठा n_tty_data *ldata = tty->disc_data;
	पूर्णांक amt = poll && !TIME_CHAR(tty) && MIN_CHAR(tty) ? MIN_CHAR(tty) : 1;

	अगर (ldata->icanon && !L_EXTPROC(tty))
		वापस ldata->canon_head != ldata->पढ़ो_tail;
	अन्यथा
		वापस ldata->commit_head - ldata->पढ़ो_tail >= amt;
पूर्ण

/**
 *	copy_from_पढ़ो_buf	-	copy पढ़ो data directly
 *	@tty: terminal device
 *	@kbp: data
 *	@nr: size of data
 *
 *	Helper function to speed up n_tty_पढ़ो.  It is only called when
 *	ICANON is off; it copies अक्षरacters straight from the tty queue.
 *
 *	Called under the ldata->atomic_पढ़ो_lock sem
 *
 *	Returns true अगर it successfully copied data, but there is still
 *	more data to be had.
 *
 *	n_tty_पढ़ो()/consumer path:
 *		caller holds non-exclusive termios_rwsem
 *		पढ़ो_tail published
 */

अटल bool copy_from_पढ़ो_buf(काष्ठा tty_काष्ठा *tty,
				      अचिन्हित अक्षर **kbp,
				      माप_प्रकार *nr)

अणु
	काष्ठा n_tty_data *ldata = tty->disc_data;
	माप_प्रकार n;
	bool is_eof;
	माप_प्रकार head = smp_load_acquire(&ldata->commit_head);
	माप_प्रकार tail = ldata->पढ़ो_tail & (N_TTY_BUF_SIZE - 1);

	n = min(head - ldata->पढ़ो_tail, N_TTY_BUF_SIZE - tail);
	n = min(*nr, n);
	अगर (n) अणु
		अचिन्हित अक्षर *from = पढ़ो_buf_addr(ldata, tail);
		स_नकल(*kbp, from, n);
		is_eof = n == 1 && *from == खातापूर्ण_CHAR(tty);
		tty_audit_add_data(tty, from, n);
		zero_buffer(tty, from, n);
		smp_store_release(&ldata->पढ़ो_tail, ldata->पढ़ो_tail + n);
		/* Turn single खातापूर्ण पूर्णांकo zero-length पढ़ो */
		अगर (L_EXTPROC(tty) && ldata->icanon && is_eof &&
		    (head == ldata->पढ़ो_tail))
			वापस false;
		*kbp += n;
		*nr -= n;

		/* If we have more to copy, let the caller know */
		वापस head != ldata->पढ़ो_tail;
	पूर्ण
	वापस false;
पूर्ण

/**
 *	canon_copy_from_पढ़ो_buf	-	copy पढ़ो data in canonical mode
 *	@tty: terminal device
 *	@kbp: data
 *	@nr: size of data
 *
 *	Helper function क्रम n_tty_पढ़ो.  It is only called when ICANON is on;
 *	it copies one line of input up to and including the line-delimiting
 *	अक्षरacter पूर्णांकo the result buffer.
 *
 *	NB: When termios is changed from non-canonical to canonical mode and
 *	the पढ़ो buffer contains data, n_tty_set_termios() simulates an खातापूर्ण
 *	push (as अगर C-d were input) _without_ the DISABLED_CHAR in the buffer.
 *	This causes data alपढ़ोy processed as input to be immediately available
 *	as input although a newline has not been received.
 *
 *	Called under the atomic_पढ़ो_lock mutex
 *
 *	n_tty_पढ़ो()/consumer path:
 *		caller holds non-exclusive termios_rwsem
 *		पढ़ो_tail published
 */

अटल bool canon_copy_from_पढ़ो_buf(काष्ठा tty_काष्ठा *tty,
				     अचिन्हित अक्षर **kbp,
				     माप_प्रकार *nr)
अणु
	काष्ठा n_tty_data *ldata = tty->disc_data;
	माप_प्रकार n, size, more, c;
	माप_प्रकार eol;
	माप_प्रकार tail, canon_head;
	पूर्णांक found = 0;

	/* N.B. aव्योम overrun अगर nr == 0 */
	अगर (!*nr)
		वापस false;

	canon_head = smp_load_acquire(&ldata->canon_head);
	n = min(*nr + 1, canon_head - ldata->पढ़ो_tail);

	tail = ldata->पढ़ो_tail & (N_TTY_BUF_SIZE - 1);
	size = min_t(माप_प्रकार, tail + n, N_TTY_BUF_SIZE);

	n_tty_trace("%s: nr:%zu tail:%zu n:%zu size:%zu\n",
		    __func__, *nr, tail, n, size);

	eol = find_next_bit(ldata->पढ़ो_flags, size, tail);
	more = n - (size - tail);
	अगर (eol == N_TTY_BUF_SIZE && more) अणु
		/* scan wrapped without finding set bit */
		eol = find_next_bit(ldata->पढ़ो_flags, more, 0);
		found = eol != more;
	पूर्ण अन्यथा
		found = eol != size;

	n = eol - tail;
	अगर (n > N_TTY_BUF_SIZE)
		n += N_TTY_BUF_SIZE;
	c = n + found;

	अगर (!found || पढ़ो_buf(ldata, eol) != __DISABLED_CHAR) अणु
		c = min(*nr, c);
		n = c;
	पूर्ण

	n_tty_trace("%s: eol:%zu found:%d n:%zu c:%zu tail:%zu more:%zu\n",
		    __func__, eol, found, n, c, tail, more);

	tty_copy(tty, *kbp, tail, n);
	*kbp += n;
	*nr -= n;

	अगर (found)
		clear_bit(eol, ldata->पढ़ो_flags);
	smp_store_release(&ldata->पढ़ो_tail, ldata->पढ़ो_tail + c);

	अगर (found) अणु
		अगर (!ldata->push)
			ldata->line_start = ldata->पढ़ो_tail;
		अन्यथा
			ldata->push = 0;
		tty_audit_push();
		वापस false;
	पूर्ण

	/* No EOL found - करो a continuation retry अगर there is more data */
	वापस ldata->पढ़ो_tail != canon_head;
पूर्ण

/**
 *	job_control		-	check job control
 *	@tty: tty
 *	@file: file handle
 *
 *	Perक्रमm job control management checks on this file/tty descriptor
 *	and अगर appropriate send any needed संकेतs and वापस a negative
 *	error code अगर action should be taken.
 *
 *	Locking: redirected ग_लिखो test is safe
 *		 current->संकेत->tty check is safe
 *		 ctrl_lock to safely reference tty->pgrp
 */

अटल पूर्णांक job_control(काष्ठा tty_काष्ठा *tty, काष्ठा file *file)
अणु
	/* Job control check -- must be करोne at start and after
	   every sleep (POSIX.1 7.1.1.4). */
	/* NOTE: not yet करोne after every sleep pending a thorough
	   check of the logic of this change. -- jlc */
	/* करोn't stop on /dev/console */
	अगर (file->f_op->ग_लिखो_iter == redirected_tty_ग_लिखो)
		वापस 0;

	वापस __tty_check_change(tty, SIGTTIN);
पूर्ण


/**
 *	n_tty_पढ़ो		-	पढ़ो function क्रम tty
 *	@tty: tty device
 *	@file: file object
 *	@buf: userspace buffer poपूर्णांकer
 *	@nr: size of I/O
 *
 *	Perक्रमm पढ़ोs क्रम the line discipline. We are guaranteed that the
 *	line discipline will not be बंदd under us but we may get multiple
 *	parallel पढ़ोers and must handle this ourselves. We may also get
 *	a hangup. Always called in user context, may sleep.
 *
 *	This code must be sure never to sleep through a hangup.
 *
 *	n_tty_पढ़ो()/consumer path:
 *		claims non-exclusive termios_rwsem
 *		publishes पढ़ो_tail
 */

अटल sमाप_प्रकार n_tty_पढ़ो(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
			  अचिन्हित अक्षर *kbuf, माप_प्रकार nr,
			  व्योम **cookie, अचिन्हित दीर्घ offset)
अणु
	काष्ठा n_tty_data *ldata = tty->disc_data;
	अचिन्हित अक्षर *kb = kbuf;
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);
	पूर्णांक c;
	पूर्णांक minimum, समय;
	sमाप_प्रकार retval = 0;
	दीर्घ समयout;
	पूर्णांक packet;
	माप_प्रकार tail;

	/*
	 * Is this a continuation of a पढ़ो started earler?
	 *
	 * If so, we still hold the atomic_पढ़ो_lock and the
	 * termios_rwsem, and can just जारी to copy data.
	 */
	अगर (*cookie) अणु
		अगर (ldata->icanon && !L_EXTPROC(tty)) अणु
			अगर (canon_copy_from_पढ़ो_buf(tty, &kb, &nr))
				वापस kb - kbuf;
		पूर्ण अन्यथा अणु
			अगर (copy_from_पढ़ो_buf(tty, &kb, &nr))
				वापस kb - kbuf;
		पूर्ण

		/* No more data - release locks and stop retries */
		n_tty_kick_worker(tty);
		n_tty_check_unthrottle(tty);
		up_पढ़ो(&tty->termios_rwsem);
		mutex_unlock(&ldata->atomic_पढ़ो_lock);
		*cookie = शून्य;
		वापस kb - kbuf;
	पूर्ण

	c = job_control(tty, file);
	अगर (c < 0)
		वापस c;

	/*
	 *	Internal serialization of पढ़ोs.
	 */
	अगर (file->f_flags & O_NONBLOCK) अणु
		अगर (!mutex_trylock(&ldata->atomic_पढ़ो_lock))
			वापस -EAGAIN;
	पूर्ण अन्यथा अणु
		अगर (mutex_lock_पूर्णांकerruptible(&ldata->atomic_पढ़ो_lock))
			वापस -ERESTARTSYS;
	पूर्ण

	करोwn_पढ़ो(&tty->termios_rwsem);

	minimum = समय = 0;
	समयout = MAX_SCHEDULE_TIMEOUT;
	अगर (!ldata->icanon) अणु
		minimum = MIN_CHAR(tty);
		अगर (minimum) अणु
			समय = (HZ / 10) * TIME_CHAR(tty);
		पूर्ण अन्यथा अणु
			समयout = (HZ / 10) * TIME_CHAR(tty);
			minimum = 1;
		पूर्ण
	पूर्ण

	packet = tty->packet;
	tail = ldata->पढ़ो_tail;

	add_रुको_queue(&tty->पढ़ो_रुको, &रुको);
	जबतक (nr) अणु
		/* First test क्रम status change. */
		अगर (packet && tty->link->ctrl_status) अणु
			अचिन्हित अक्षर cs;
			अगर (kb != kbuf)
				अवरोध;
			spin_lock_irq(&tty->link->ctrl_lock);
			cs = tty->link->ctrl_status;
			tty->link->ctrl_status = 0;
			spin_unlock_irq(&tty->link->ctrl_lock);
			*kb++ = cs;
			nr--;
			अवरोध;
		पूर्ण

		अगर (!input_available_p(tty, 0)) अणु
			up_पढ़ो(&tty->termios_rwsem);
			tty_buffer_flush_work(tty->port);
			करोwn_पढ़ो(&tty->termios_rwsem);
			अगर (!input_available_p(tty, 0)) अणु
				अगर (test_bit(TTY_OTHER_CLOSED, &tty->flags)) अणु
					retval = -EIO;
					अवरोध;
				पूर्ण
				अगर (tty_hung_up_p(file))
					अवरोध;
				/*
				 * Abort पढ़ोers क्रम ttys which never actually
				 * get hung up.  See __tty_hangup().
				 */
				अगर (test_bit(TTY_HUPPING, &tty->flags))
					अवरोध;
				अगर (!समयout)
					अवरोध;
				अगर (tty_io_nonblock(tty, file)) अणु
					retval = -EAGAIN;
					अवरोध;
				पूर्ण
				अगर (संकेत_pending(current)) अणु
					retval = -ERESTARTSYS;
					अवरोध;
				पूर्ण
				up_पढ़ो(&tty->termios_rwsem);

				समयout = रुको_woken(&रुको, TASK_INTERRUPTIBLE,
						समयout);

				करोwn_पढ़ो(&tty->termios_rwsem);
				जारी;
			पूर्ण
		पूर्ण

		अगर (ldata->icanon && !L_EXTPROC(tty)) अणु
			अगर (canon_copy_from_पढ़ो_buf(tty, &kb, &nr))
				जाओ more_to_be_पढ़ो;
		पूर्ण अन्यथा अणु
			/* Deal with packet mode. */
			अगर (packet && kb == kbuf) अणु
				*kb++ = TIOCPKT_DATA;
				nr--;
			पूर्ण

			/*
			 * Copy data, and अगर there is more to be had
			 * and we have nothing more to रुको क्रम, then
			 * let's mark us क्रम retries.
			 *
			 * NOTE! We वापस here with both the termios_sem
			 * and atomic_पढ़ो_lock still held, the retries
			 * will release them when करोne.
			 */
			अगर (copy_from_पढ़ो_buf(tty, &kb, &nr) && kb - kbuf >= minimum) अणु
more_to_be_पढ़ो:
				हटाओ_रुको_queue(&tty->पढ़ो_रुको, &रुको);
				*cookie = cookie;
				वापस kb - kbuf;
			पूर्ण
		पूर्ण

		n_tty_check_unthrottle(tty);

		अगर (kb - kbuf >= minimum)
			अवरोध;
		अगर (समय)
			समयout = समय;
	पूर्ण
	अगर (tail != ldata->पढ़ो_tail)
		n_tty_kick_worker(tty);
	up_पढ़ो(&tty->termios_rwsem);

	हटाओ_रुको_queue(&tty->पढ़ो_रुको, &रुको);
	mutex_unlock(&ldata->atomic_पढ़ो_lock);

	अगर (kb - kbuf)
		retval = kb - kbuf;

	वापस retval;
पूर्ण

/**
 *	n_tty_ग_लिखो		-	ग_लिखो function क्रम tty
 *	@tty: tty device
 *	@file: file object
 *	@buf: userspace buffer poपूर्णांकer
 *	@nr: size of I/O
 *
 *	Write function of the terminal device.  This is serialized with
 *	respect to other ग_लिखो callers but not to termios changes, पढ़ोs
 *	and other such events.  Since the receive code will echo अक्षरacters,
 *	thus calling driver ग_लिखो methods, the output_lock is used in
 *	the output processing functions called here as well as in the
 *	echo processing function to protect the column state and space
 *	left in the buffer.
 *
 *	This code must be sure never to sleep through a hangup.
 *
 *	Locking: output_lock to protect column state and space left
 *		 (note that the process_output*() functions take this
 *		  lock themselves)
 */

अटल sमाप_प्रकार n_tty_ग_लिखो(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
			   स्थिर अचिन्हित अक्षर *buf, माप_प्रकार nr)
अणु
	स्थिर अचिन्हित अक्षर *b = buf;
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);
	पूर्णांक c;
	sमाप_प्रकार retval = 0;

	/* Job control check -- must be करोne at start (POSIX.1 7.1.1.4). */
	अगर (L_TOSTOP(tty) && file->f_op->ग_लिखो_iter != redirected_tty_ग_लिखो) अणु
		retval = tty_check_change(tty);
		अगर (retval)
			वापस retval;
	पूर्ण

	करोwn_पढ़ो(&tty->termios_rwsem);

	/* Write out any echoed अक्षरacters that are still pending */
	process_echoes(tty);

	add_रुको_queue(&tty->ग_लिखो_रुको, &रुको);
	जबतक (1) अणु
		अगर (संकेत_pending(current)) अणु
			retval = -ERESTARTSYS;
			अवरोध;
		पूर्ण
		अगर (tty_hung_up_p(file) || (tty->link && !tty->link->count)) अणु
			retval = -EIO;
			अवरोध;
		पूर्ण
		अगर (O_OPOST(tty)) अणु
			जबतक (nr > 0) अणु
				sमाप_प्रकार num = process_output_block(tty, b, nr);
				अगर (num < 0) अणु
					अगर (num == -EAGAIN)
						अवरोध;
					retval = num;
					जाओ अवरोध_out;
				पूर्ण
				b += num;
				nr -= num;
				अगर (nr == 0)
					अवरोध;
				c = *b;
				अगर (process_output(c, tty) < 0)
					अवरोध;
				b++; nr--;
			पूर्ण
			अगर (tty->ops->flush_अक्षरs)
				tty->ops->flush_अक्षरs(tty);
		पूर्ण अन्यथा अणु
			काष्ठा n_tty_data *ldata = tty->disc_data;

			जबतक (nr > 0) अणु
				mutex_lock(&ldata->output_lock);
				c = tty->ops->ग_लिखो(tty, b, nr);
				mutex_unlock(&ldata->output_lock);
				अगर (c < 0) अणु
					retval = c;
					जाओ अवरोध_out;
				पूर्ण
				अगर (!c)
					अवरोध;
				b += c;
				nr -= c;
			पूर्ण
		पूर्ण
		अगर (!nr)
			अवरोध;
		अगर (tty_io_nonblock(tty, file)) अणु
			retval = -EAGAIN;
			अवरोध;
		पूर्ण
		up_पढ़ो(&tty->termios_rwsem);

		रुको_woken(&रुको, TASK_INTERRUPTIBLE, MAX_SCHEDULE_TIMEOUT);

		करोwn_पढ़ो(&tty->termios_rwsem);
	पूर्ण
अवरोध_out:
	हटाओ_रुको_queue(&tty->ग_लिखो_रुको, &रुको);
	अगर (nr && tty->fasync)
		set_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);
	up_पढ़ो(&tty->termios_rwsem);
	वापस (b - buf) ? b - buf : retval;
पूर्ण

/**
 *	n_tty_poll		-	poll method क्रम N_TTY
 *	@tty: terminal device
 *	@file: file accessing it
 *	@रुको: poll table
 *
 *	Called when the line discipline is asked to poll() क्रम data or
 *	क्रम special events. This code is not serialized with respect to
 *	other events save खोलो/बंद.
 *
 *	This code must be sure never to sleep through a hangup.
 *	Called without the kernel lock held - fine
 */

अटल __poll_t n_tty_poll(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
							poll_table *रुको)
अणु
	__poll_t mask = 0;

	poll_रुको(file, &tty->पढ़ो_रुको, रुको);
	poll_रुको(file, &tty->ग_लिखो_रुको, रुको);
	अगर (input_available_p(tty, 1))
		mask |= EPOLLIN | EPOLLRDNORM;
	अन्यथा अणु
		tty_buffer_flush_work(tty->port);
		अगर (input_available_p(tty, 1))
			mask |= EPOLLIN | EPOLLRDNORM;
	पूर्ण
	अगर (tty->packet && tty->link->ctrl_status)
		mask |= EPOLLPRI | EPOLLIN | EPOLLRDNORM;
	अगर (test_bit(TTY_OTHER_CLOSED, &tty->flags))
		mask |= EPOLLHUP;
	अगर (tty_hung_up_p(file))
		mask |= EPOLLHUP;
	अगर (tty->ops->ग_लिखो && !tty_is_ग_लिखोlocked(tty) &&
			tty_अक्षरs_in_buffer(tty) < WAKEUP_CHARS &&
			tty_ग_लिखो_room(tty) > 0)
		mask |= EPOLLOUT | EPOLLWRNORM;
	वापस mask;
पूर्ण

अटल अचिन्हित दीर्घ inq_canon(काष्ठा n_tty_data *ldata)
अणु
	माप_प्रकार nr, head, tail;

	अगर (ldata->canon_head == ldata->पढ़ो_tail)
		वापस 0;
	head = ldata->canon_head;
	tail = ldata->पढ़ो_tail;
	nr = head - tail;
	/* Skip खातापूर्ण-अक्षरs.. */
	जबतक (MASK(head) != MASK(tail)) अणु
		अगर (test_bit(tail & (N_TTY_BUF_SIZE - 1), ldata->पढ़ो_flags) &&
		    पढ़ो_buf(ldata, tail) == __DISABLED_CHAR)
			nr--;
		tail++;
	पूर्ण
	वापस nr;
पूर्ण

अटल पूर्णांक n_tty_ioctl(काष्ठा tty_काष्ठा *tty, काष्ठा file *file,
		       अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा n_tty_data *ldata = tty->disc_data;
	पूर्णांक retval;

	चयन (cmd) अणु
	हाल TIOCOUTQ:
		वापस put_user(tty_अक्षरs_in_buffer(tty), (पूर्णांक __user *) arg);
	हाल TIOCINQ:
		करोwn_ग_लिखो(&tty->termios_rwsem);
		अगर (L_ICANON(tty) && !L_EXTPROC(tty))
			retval = inq_canon(ldata);
		अन्यथा
			retval = पढ़ो_cnt(ldata);
		up_ग_लिखो(&tty->termios_rwsem);
		वापस put_user(retval, (अचिन्हित पूर्णांक __user *) arg);
	शेष:
		वापस n_tty_ioctl_helper(tty, file, cmd, arg);
	पूर्ण
पूर्ण

अटल काष्ठा tty_ldisc_ops n_tty_ops = अणु
	.owner		 = THIS_MODULE,
	.name            = "n_tty",
	.खोलो            = n_tty_खोलो,
	.बंद           = n_tty_बंद,
	.flush_buffer    = n_tty_flush_buffer,
	.पढ़ो            = n_tty_पढ़ो,
	.ग_लिखो           = n_tty_ग_लिखो,
	.ioctl           = n_tty_ioctl,
	.set_termios     = n_tty_set_termios,
	.poll            = n_tty_poll,
	.receive_buf     = n_tty_receive_buf,
	.ग_लिखो_wakeup    = n_tty_ग_लिखो_wakeup,
	.receive_buf2	 = n_tty_receive_buf2,
पूर्ण;

/**
 *	n_tty_inherit_ops	-	inherit N_TTY methods
 *	@ops: काष्ठा tty_ldisc_ops where to save N_TTY methods
 *
 *	Enables a 'subclass' line discipline to 'inherit' N_TTY methods.
 */

व्योम n_tty_inherit_ops(काष्ठा tty_ldisc_ops *ops)
अणु
	*ops = n_tty_ops;
	ops->owner = शून्य;
	ops->refcount = ops->flags = 0;
पूर्ण
EXPORT_SYMBOL_GPL(n_tty_inherit_ops);

व्योम __init n_tty_init(व्योम)
अणु
	tty_रेजिस्टर_ldisc(N_TTY, &n_tty_ops);
पूर्ण
