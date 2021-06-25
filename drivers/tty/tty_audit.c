<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Creating audit events from TTY input.
 *
 * Copyright (C) 2007 Red Hat, Inc.  All rights reserved.
 *
 * Authors: Miloslav Trmac <mitr@redhat.com>
 */

#समावेश <linux/audit.h>
#समावेश <linux/slab.h>
#समावेश <linux/tty.h>
#समावेश "tty.h"

काष्ठा tty_audit_buf अणु
	काष्ठा mutex mutex;	/* Protects all data below */
	dev_t dev;		/* The TTY which the data is from */
	अचिन्हित icanon:1;
	माप_प्रकार valid;
	अचिन्हित अक्षर *data;	/* Allocated size N_TTY_BUF_SIZE */
पूर्ण;

अटल काष्ठा tty_audit_buf *tty_audit_buf_ref(व्योम)
अणु
	काष्ठा tty_audit_buf *buf;

	buf = current->संकेत->tty_audit_buf;
	WARN_ON(buf == ERR_PTR(-ESRCH));
	वापस buf;
पूर्ण

अटल काष्ठा tty_audit_buf *tty_audit_buf_alloc(व्योम)
अणु
	काष्ठा tty_audit_buf *buf;

	buf = kदो_स्मृति(माप(*buf), GFP_KERNEL);
	अगर (!buf)
		जाओ err;
	buf->data = kदो_स्मृति(N_TTY_BUF_SIZE, GFP_KERNEL);
	अगर (!buf->data)
		जाओ err_buf;
	mutex_init(&buf->mutex);
	buf->dev = MKDEV(0, 0);
	buf->icanon = 0;
	buf->valid = 0;
	वापस buf;

err_buf:
	kमुक्त(buf);
err:
	वापस शून्य;
पूर्ण

अटल व्योम tty_audit_buf_मुक्त(काष्ठा tty_audit_buf *buf)
अणु
	WARN_ON(buf->valid != 0);
	kमुक्त(buf->data);
	kमुक्त(buf);
पूर्ण

अटल व्योम tty_audit_log(स्थिर अक्षर *description, dev_t dev,
			  अचिन्हित अक्षर *data, माप_प्रकार size)
अणु
	काष्ठा audit_buffer *ab;
	pid_t pid = task_pid_nr(current);
	uid_t uid = from_kuid(&init_user_ns, task_uid(current));
	uid_t loginuid = from_kuid(&init_user_ns, audit_get_loginuid(current));
	अचिन्हित पूर्णांक sessionid = audit_get_sessionid(current);

	ab = audit_log_start(audit_context(), GFP_KERNEL, AUDIT_TTY);
	अगर (ab) अणु
		अक्षर name[माप(current->comm)];

		audit_log_क्रमmat(ab, "%s pid=%u uid=%u auid=%u ses=%u major=%d"
				 " minor=%d comm=", description, pid, uid,
				 loginuid, sessionid, MAJOR(dev), MINOR(dev));
		get_task_comm(name, current);
		audit_log_untrustedstring(ab, name);
		audit_log_क्रमmat(ab, " data=");
		audit_log_n_hex(ab, data, size);
		audit_log_end(ab);
	पूर्ण
पूर्ण

/*
 *	tty_audit_buf_push	-	Push buffered data out
 *
 *	Generate an audit message from the contents of @buf, which is owned by
 *	the current task.  @buf->mutex must be locked.
 */
अटल व्योम tty_audit_buf_push(काष्ठा tty_audit_buf *buf)
अणु
	अगर (buf->valid == 0)
		वापस;
	अगर (audit_enabled == AUDIT_OFF) अणु
		buf->valid = 0;
		वापस;
	पूर्ण
	tty_audit_log("tty", buf->dev, buf->data, buf->valid);
	buf->valid = 0;
पूर्ण

/**
 *	tty_audit_निकास	-	Handle a task निकास
 *
 *	Make sure all buffered data is written out and deallocate the buffer.
 *	Only needs to be called अगर current->संकेत->tty_audit_buf != %शून्य.
 *
 *	The process is single-thपढ़ोed at this poपूर्णांक; no other thपढ़ोs share
 *	current->संकेत.
 */
व्योम tty_audit_निकास(व्योम)
अणु
	काष्ठा tty_audit_buf *buf;

	buf = xchg(&current->संकेत->tty_audit_buf, ERR_PTR(-ESRCH));
	अगर (!buf)
		वापस;

	tty_audit_buf_push(buf);
	tty_audit_buf_मुक्त(buf);
पूर्ण

/*
 *	tty_audit_विभाजन	-	Copy TTY audit state क्रम a new task
 *
 *	Set up TTY audit state in @sig from current.  @sig needs no locking.
 */
व्योम tty_audit_विभाजन(काष्ठा संकेत_काष्ठा *sig)
अणु
	sig->audit_tty = current->संकेत->audit_tty;
पूर्ण

/*
 *	tty_audit_tiocsti	-	Log TIOCSTI
 */
व्योम tty_audit_tiocsti(काष्ठा tty_काष्ठा *tty, अक्षर ch)
अणु
	dev_t dev;

	dev = MKDEV(tty->driver->major, tty->driver->minor_start) + tty->index;
	अगर (tty_audit_push())
		वापस;

	अगर (audit_enabled)
		tty_audit_log("ioctl=TIOCSTI", dev, &ch, 1);
पूर्ण

/*
 *	tty_audit_push	-	Flush current's pending audit data
 *
 *	Returns 0 अगर success, -EPERM अगर tty audit is disabled
 */
पूर्णांक tty_audit_push(व्योम)
अणु
	काष्ठा tty_audit_buf *buf;

	अगर (~current->संकेत->audit_tty & AUDIT_TTY_ENABLE)
		वापस -EPERM;

	buf = tty_audit_buf_ref();
	अगर (!IS_ERR_OR_शून्य(buf)) अणु
		mutex_lock(&buf->mutex);
		tty_audit_buf_push(buf);
		mutex_unlock(&buf->mutex);
	पूर्ण
	वापस 0;
पूर्ण

/*
 *	tty_audit_buf_get	-	Get an audit buffer.
 *
 *	Get an audit buffer, allocate it अगर necessary.  Return %शून्य
 *	अगर out of memory or ERR_PTR(-ESRCH) अगर tty_audit_निकास() has alपढ़ोy
 *	occurred.  Otherwise, वापस a new reference to the buffer.
 */
अटल काष्ठा tty_audit_buf *tty_audit_buf_get(व्योम)
अणु
	काष्ठा tty_audit_buf *buf;

	buf = tty_audit_buf_ref();
	अगर (buf)
		वापस buf;

	buf = tty_audit_buf_alloc();
	अगर (buf == शून्य) अणु
		audit_log_lost("out of memory in TTY auditing");
		वापस शून्य;
	पूर्ण

	/* Race to use this buffer, मुक्त it अगर another wins */
	अगर (cmpxchg(&current->संकेत->tty_audit_buf, शून्य, buf) != शून्य)
		tty_audit_buf_मुक्त(buf);
	वापस tty_audit_buf_ref();
पूर्ण

/*
 *	tty_audit_add_data	-	Add data क्रम TTY auditing.
 *
 *	Audit @data of @size from @tty, अगर necessary.
 */
व्योम tty_audit_add_data(काष्ठा tty_काष्ठा *tty, स्थिर व्योम *data, माप_प्रकार size)
अणु
	काष्ठा tty_audit_buf *buf;
	अचिन्हित पूर्णांक icanon = !!L_ICANON(tty);
	अचिन्हित पूर्णांक audit_tty;
	dev_t dev;

	audit_tty = READ_ONCE(current->संकेत->audit_tty);
	अगर (~audit_tty & AUDIT_TTY_ENABLE)
		वापस;

	अगर (unlikely(size == 0))
		वापस;

	अगर (tty->driver->type == TTY_DRIVER_TYPE_PTY
	    && tty->driver->subtype == PTY_TYPE_MASTER)
		वापस;

	अगर ((~audit_tty & AUDIT_TTY_LOG_PASSWD) && icanon && !L_ECHO(tty))
		वापस;

	buf = tty_audit_buf_get();
	अगर (IS_ERR_OR_शून्य(buf))
		वापस;

	mutex_lock(&buf->mutex);
	dev = MKDEV(tty->driver->major, tty->driver->minor_start) + tty->index;
	अगर (buf->dev != dev || buf->icanon != icanon) अणु
		tty_audit_buf_push(buf);
		buf->dev = dev;
		buf->icanon = icanon;
	पूर्ण
	करो अणु
		माप_प्रकार run;

		run = N_TTY_BUF_SIZE - buf->valid;
		अगर (run > size)
			run = size;
		स_नकल(buf->data + buf->valid, data, run);
		buf->valid += run;
		data += run;
		size -= run;
		अगर (buf->valid == N_TTY_BUF_SIZE)
			tty_audit_buf_push(buf);
	पूर्ण जबतक (size != 0);
	mutex_unlock(&buf->mutex);
पूर्ण
