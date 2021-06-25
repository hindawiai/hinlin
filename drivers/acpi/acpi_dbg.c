<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ACPI AML पूर्णांकerfacing support
 *
 * Copyright (C) 2015, Intel Corporation
 * Authors: Lv Zheng <lv.zheng@पूर्णांकel.com>
 */

/* #घोषणा DEBUG */
#घोषणा pr_fmt(fmt) "ACPI: AML: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/रुको.h>
#समावेश <linux/poll.h>
#समावेश <linux/sched.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/circ_buf.h>
#समावेश <linux/acpi.h>
#समावेश "internal.h"

#घोषणा ACPI_AML_BUF_ALIGN	(माप (acpi_size))
#घोषणा ACPI_AML_BUF_SIZE	PAGE_SIZE

#घोषणा circ_count(circ) \
	(CIRC_CNT((circ)->head, (circ)->tail, ACPI_AML_BUF_SIZE))
#घोषणा circ_count_to_end(circ) \
	(CIRC_CNT_TO_END((circ)->head, (circ)->tail, ACPI_AML_BUF_SIZE))
#घोषणा circ_space(circ) \
	(CIRC_SPACE((circ)->head, (circ)->tail, ACPI_AML_BUF_SIZE))
#घोषणा circ_space_to_end(circ) \
	(CIRC_SPACE_TO_END((circ)->head, (circ)->tail, ACPI_AML_BUF_SIZE))

#घोषणा ACPI_AML_OPENED		0x0001
#घोषणा ACPI_AML_CLOSED		0x0002
#घोषणा ACPI_AML_IN_USER	0x0004 /* user space is writing cmd */
#घोषणा ACPI_AML_IN_KERN	0x0008 /* kernel space is पढ़ोing cmd */
#घोषणा ACPI_AML_OUT_USER	0x0010 /* user space is पढ़ोing log */
#घोषणा ACPI_AML_OUT_KERN	0x0020 /* kernel space is writing log */
#घोषणा ACPI_AML_USER		(ACPI_AML_IN_USER | ACPI_AML_OUT_USER)
#घोषणा ACPI_AML_KERN		(ACPI_AML_IN_KERN | ACPI_AML_OUT_KERN)
#घोषणा ACPI_AML_BUSY		(ACPI_AML_USER | ACPI_AML_KERN)
#घोषणा ACPI_AML_OPEN		(ACPI_AML_OPENED | ACPI_AML_CLOSED)

काष्ठा acpi_aml_io अणु
	रुको_queue_head_t रुको;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ users;
	काष्ठा mutex lock;
	काष्ठा task_काष्ठा *thपढ़ो;
	अक्षर out_buf[ACPI_AML_BUF_SIZE] __aligned(ACPI_AML_BUF_ALIGN);
	काष्ठा circ_buf out_crc;
	अक्षर in_buf[ACPI_AML_BUF_SIZE] __aligned(ACPI_AML_BUF_ALIGN);
	काष्ठा circ_buf in_crc;
	acpi_osd_exec_callback function;
	व्योम *context;
	अचिन्हित दीर्घ usages;
पूर्ण;

अटल काष्ठा acpi_aml_io acpi_aml_io;
अटल bool acpi_aml_initialized;
अटल काष्ठा file *acpi_aml_active_पढ़ोer;
अटल काष्ठा dentry *acpi_aml_dentry;

अटल अंतरभूत bool __acpi_aml_running(व्योम)
अणु
	वापस acpi_aml_io.thपढ़ो ? true : false;
पूर्ण

अटल अंतरभूत bool __acpi_aml_access_ok(अचिन्हित दीर्घ flag)
अणु
	/*
	 * The debugger पूर्णांकerface is in खोलोed state (OPENED && !CLOSED),
	 * then it is allowed to access the debugger buffers from either
	 * user space or the kernel space.
	 * In addition, क्रम the kernel space, only the debugger thपढ़ो
	 * (thपढ़ो ID matched) is allowed to access.
	 */
	अगर (!(acpi_aml_io.flags & ACPI_AML_OPENED) ||
	    (acpi_aml_io.flags & ACPI_AML_CLOSED) ||
	    !__acpi_aml_running())
		वापस false;
	अगर ((flag & ACPI_AML_KERN) &&
	    current != acpi_aml_io.thपढ़ो)
		वापस false;
	वापस true;
पूर्ण

अटल अंतरभूत bool __acpi_aml_पढ़ोable(काष्ठा circ_buf *circ, अचिन्हित दीर्घ flag)
अणु
	/*
	 * Another पढ़ो is not in progress and there is data in buffer
	 * available क्रम पढ़ो.
	 */
	अगर (!(acpi_aml_io.flags & flag) && circ_count(circ))
		वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत bool __acpi_aml_writable(काष्ठा circ_buf *circ, अचिन्हित दीर्घ flag)
अणु
	/*
	 * Another ग_लिखो is not in progress and there is buffer space
	 * available क्रम ग_लिखो.
	 */
	अगर (!(acpi_aml_io.flags & flag) && circ_space(circ))
		वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत bool __acpi_aml_busy(व्योम)
अणु
	अगर (acpi_aml_io.flags & ACPI_AML_BUSY)
		वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत bool __acpi_aml_used(व्योम)
अणु
	वापस acpi_aml_io.usages ? true : false;
पूर्ण

अटल अंतरभूत bool acpi_aml_running(व्योम)
अणु
	bool ret;

	mutex_lock(&acpi_aml_io.lock);
	ret = __acpi_aml_running();
	mutex_unlock(&acpi_aml_io.lock);
	वापस ret;
पूर्ण

अटल bool acpi_aml_busy(व्योम)
अणु
	bool ret;

	mutex_lock(&acpi_aml_io.lock);
	ret = __acpi_aml_busy();
	mutex_unlock(&acpi_aml_io.lock);
	वापस ret;
पूर्ण

अटल bool acpi_aml_used(व्योम)
अणु
	bool ret;

	/*
	 * The usage count is prepared to aव्योम race conditions between the
	 * starts and the stops of the debugger thपढ़ो.
	 */
	mutex_lock(&acpi_aml_io.lock);
	ret = __acpi_aml_used();
	mutex_unlock(&acpi_aml_io.lock);
	वापस ret;
पूर्ण

अटल bool acpi_aml_kern_पढ़ोable(व्योम)
अणु
	bool ret;

	mutex_lock(&acpi_aml_io.lock);
	ret = !__acpi_aml_access_ok(ACPI_AML_IN_KERN) ||
	      __acpi_aml_पढ़ोable(&acpi_aml_io.in_crc, ACPI_AML_IN_KERN);
	mutex_unlock(&acpi_aml_io.lock);
	वापस ret;
पूर्ण

अटल bool acpi_aml_kern_writable(व्योम)
अणु
	bool ret;

	mutex_lock(&acpi_aml_io.lock);
	ret = !__acpi_aml_access_ok(ACPI_AML_OUT_KERN) ||
	      __acpi_aml_writable(&acpi_aml_io.out_crc, ACPI_AML_OUT_KERN);
	mutex_unlock(&acpi_aml_io.lock);
	वापस ret;
पूर्ण

अटल bool acpi_aml_user_पढ़ोable(व्योम)
अणु
	bool ret;

	mutex_lock(&acpi_aml_io.lock);
	ret = !__acpi_aml_access_ok(ACPI_AML_OUT_USER) ||
	      __acpi_aml_पढ़ोable(&acpi_aml_io.out_crc, ACPI_AML_OUT_USER);
	mutex_unlock(&acpi_aml_io.lock);
	वापस ret;
पूर्ण

अटल bool acpi_aml_user_writable(व्योम)
अणु
	bool ret;

	mutex_lock(&acpi_aml_io.lock);
	ret = !__acpi_aml_access_ok(ACPI_AML_IN_USER) ||
	      __acpi_aml_writable(&acpi_aml_io.in_crc, ACPI_AML_IN_USER);
	mutex_unlock(&acpi_aml_io.lock);
	वापस ret;
पूर्ण

अटल पूर्णांक acpi_aml_lock_ग_लिखो(काष्ठा circ_buf *circ, अचिन्हित दीर्घ flag)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&acpi_aml_io.lock);
	अगर (!__acpi_aml_access_ok(flag)) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण
	अगर (!__acpi_aml_writable(circ, flag)) अणु
		ret = -EAGAIN;
		जाओ out;
	पूर्ण
	acpi_aml_io.flags |= flag;
out:
	mutex_unlock(&acpi_aml_io.lock);
	वापस ret;
पूर्ण

अटल पूर्णांक acpi_aml_lock_पढ़ो(काष्ठा circ_buf *circ, अचिन्हित दीर्घ flag)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&acpi_aml_io.lock);
	अगर (!__acpi_aml_access_ok(flag)) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण
	अगर (!__acpi_aml_पढ़ोable(circ, flag)) अणु
		ret = -EAGAIN;
		जाओ out;
	पूर्ण
	acpi_aml_io.flags |= flag;
out:
	mutex_unlock(&acpi_aml_io.lock);
	वापस ret;
पूर्ण

अटल व्योम acpi_aml_unlock_fअगरo(अचिन्हित दीर्घ flag, bool wakeup)
अणु
	mutex_lock(&acpi_aml_io.lock);
	acpi_aml_io.flags &= ~flag;
	अगर (wakeup)
		wake_up_पूर्णांकerruptible(&acpi_aml_io.रुको);
	mutex_unlock(&acpi_aml_io.lock);
पूर्ण

अटल पूर्णांक acpi_aml_ग_लिखो_kern(स्थिर अक्षर *buf, पूर्णांक len)
अणु
	पूर्णांक ret;
	काष्ठा circ_buf *crc = &acpi_aml_io.out_crc;
	पूर्णांक n;
	अक्षर *p;

	ret = acpi_aml_lock_ग_लिखो(crc, ACPI_AML_OUT_KERN);
	अगर (ret < 0)
		वापस ret;
	/* sync tail beक्रमe inserting logs */
	smp_mb();
	p = &crc->buf[crc->head];
	n = min(len, circ_space_to_end(crc));
	स_नकल(p, buf, n);
	/* sync head after inserting logs */
	smp_wmb();
	crc->head = (crc->head + n) & (ACPI_AML_BUF_SIZE - 1);
	acpi_aml_unlock_fअगरo(ACPI_AML_OUT_KERN, true);
	वापस n;
पूर्ण

अटल पूर्णांक acpi_aml_पढ़ोb_kern(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा circ_buf *crc = &acpi_aml_io.in_crc;
	अक्षर *p;

	ret = acpi_aml_lock_पढ़ो(crc, ACPI_AML_IN_KERN);
	अगर (ret < 0)
		वापस ret;
	/* sync head beक्रमe removing cmds */
	smp_rmb();
	p = &crc->buf[crc->tail];
	ret = (पूर्णांक)*p;
	/* sync tail beक्रमe inserting cmds */
	smp_mb();
	crc->tail = (crc->tail + 1) & (ACPI_AML_BUF_SIZE - 1);
	acpi_aml_unlock_fअगरo(ACPI_AML_IN_KERN, true);
	वापस ret;
पूर्ण

/*
 * acpi_aml_ग_लिखो_log() - Capture debugger output
 * @msg: the debugger output
 *
 * This function should be used to implement acpi_os_म_लिखो() to filter out
 * the debugger output and store the output पूर्णांकo the debugger पूर्णांकerface
 * buffer. Return the size of stored logs or त्रुटि_सं.
 */
अटल sमाप_प्रकार acpi_aml_ग_लिखो_log(स्थिर अक्षर *msg)
अणु
	पूर्णांक ret = 0;
	पूर्णांक count = 0, size = 0;

	अगर (!acpi_aml_initialized)
		वापस -ENODEV;
	अगर (msg)
		count = म_माप(msg);
	जबतक (count > 0) अणु
again:
		ret = acpi_aml_ग_लिखो_kern(msg + size, count);
		अगर (ret == -EAGAIN) अणु
			ret = रुको_event_पूर्णांकerruptible(acpi_aml_io.रुको,
				acpi_aml_kern_writable());
			/*
			 * We need to retry when the condition
			 * becomes true.
			 */
			अगर (ret == 0)
				जाओ again;
			अवरोध;
		पूर्ण
		अगर (ret < 0)
			अवरोध;
		size += ret;
		count -= ret;
	पूर्ण
	वापस size > 0 ? size : ret;
पूर्ण

/*
 * acpi_aml_पढ़ो_cmd() - Capture debugger input
 * @msg: the debugger input
 * @size: the size of the debugger input
 *
 * This function should be used to implement acpi_os_get_line() to capture
 * the debugger input commands and store the input commands पूर्णांकo the
 * debugger पूर्णांकerface buffer. Return the size of stored commands or त्रुटि_सं.
 */
अटल sमाप_प्रकार acpi_aml_पढ़ो_cmd(अक्षर *msg, माप_प्रकार count)
अणु
	पूर्णांक ret = 0;
	पूर्णांक size = 0;

	/*
	 * This is ensured by the running fact of the debugger thपढ़ो
	 * unless a bug is पूर्णांकroduced.
	 */
	BUG_ON(!acpi_aml_initialized);
	जबतक (count > 0) अणु
again:
		/*
		 * Check each input byte to find the end of the command.
		 */
		ret = acpi_aml_पढ़ोb_kern();
		अगर (ret == -EAGAIN) अणु
			ret = रुको_event_पूर्णांकerruptible(acpi_aml_io.रुको,
				acpi_aml_kern_पढ़ोable());
			/*
			 * We need to retry when the condition becomes
			 * true.
			 */
			अगर (ret == 0)
				जाओ again;
		पूर्ण
		अगर (ret < 0)
			अवरोध;
		*(msg + size) = (अक्षर)ret;
		size++;
		count--;
		अगर (ret == '\n') अणु
			/*
			 * acpi_os_get_line() requires a zero terminated command
			 * string.
			 */
			*(msg + size - 1) = '\0';
			अवरोध;
		पूर्ण
	पूर्ण
	वापस size > 0 ? size : ret;
पूर्ण

अटल पूर्णांक acpi_aml_thपढ़ो(व्योम *unused)
अणु
	acpi_osd_exec_callback function = शून्य;
	व्योम *context;

	mutex_lock(&acpi_aml_io.lock);
	अगर (acpi_aml_io.function) अणु
		acpi_aml_io.usages++;
		function = acpi_aml_io.function;
		context = acpi_aml_io.context;
	पूर्ण
	mutex_unlock(&acpi_aml_io.lock);

	अगर (function)
		function(context);

	mutex_lock(&acpi_aml_io.lock);
	acpi_aml_io.usages--;
	अगर (!__acpi_aml_used()) अणु
		acpi_aml_io.thपढ़ो = शून्य;
		wake_up(&acpi_aml_io.रुको);
	पूर्ण
	mutex_unlock(&acpi_aml_io.lock);

	वापस 0;
पूर्ण

/*
 * acpi_aml_create_thपढ़ो() - Create AML debugger thपढ़ो
 * @function: the debugger thपढ़ो callback
 * @context: the context to be passed to the debugger thपढ़ो
 *
 * This function should be used to implement acpi_os_execute() which is
 * used by the ACPICA debugger to create the debugger thपढ़ो.
 */
अटल पूर्णांक acpi_aml_create_thपढ़ो(acpi_osd_exec_callback function, व्योम *context)
अणु
	काष्ठा task_काष्ठा *t;

	mutex_lock(&acpi_aml_io.lock);
	acpi_aml_io.function = function;
	acpi_aml_io.context = context;
	mutex_unlock(&acpi_aml_io.lock);

	t = kthपढ़ो_create(acpi_aml_thपढ़ो, शून्य, "aml");
	अगर (IS_ERR(t)) अणु
		pr_err("Failed to create AML debugger thread.\n");
		वापस PTR_ERR(t);
	पूर्ण

	mutex_lock(&acpi_aml_io.lock);
	acpi_aml_io.thपढ़ो = t;
	acpi_set_debugger_thपढ़ो_id((acpi_thपढ़ो_id)(अचिन्हित दीर्घ)t);
	wake_up_process(t);
	mutex_unlock(&acpi_aml_io.lock);
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_aml_रुको_command_पढ़ोy(bool single_step,
				       अक्षर *buffer, माप_प्रकार length)
अणु
	acpi_status status;

	अगर (single_step)
		acpi_os_म_लिखो("\n%1c ", ACPI_DEBUGGER_EXECUTE_PROMPT);
	अन्यथा
		acpi_os_म_लिखो("\n%1c ", ACPI_DEBUGGER_COMMAND_PROMPT);

	status = acpi_os_get_line(buffer, length, शून्य);
	अगर (ACPI_FAILURE(status))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_aml_notअगरy_command_complete(व्योम)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_aml_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret = 0;
	acpi_status status;

	mutex_lock(&acpi_aml_io.lock);
	/*
	 * The debugger पूर्णांकerface is being बंदd, no new user is allowed
	 * during this period.
	 */
	अगर (acpi_aml_io.flags & ACPI_AML_CLOSED) अणु
		ret = -EBUSY;
		जाओ err_lock;
	पूर्ण
	अगर ((file->f_flags & O_ACCMODE) != O_WRONLY) अणु
		/*
		 * Only one पढ़ोer is allowed to initiate the debugger
		 * thपढ़ो.
		 */
		अगर (acpi_aml_active_पढ़ोer) अणु
			ret = -EBUSY;
			जाओ err_lock;
		पूर्ण अन्यथा अणु
			pr_debug("Opening debugger reader.\n");
			acpi_aml_active_पढ़ोer = file;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * No ग_लिखोr is allowed unless the debugger thपढ़ो is
		 * पढ़ोy.
		 */
		अगर (!(acpi_aml_io.flags & ACPI_AML_OPENED)) अणु
			ret = -ENODEV;
			जाओ err_lock;
		पूर्ण
	पूर्ण
	अगर (acpi_aml_active_पढ़ोer == file) अणु
		pr_debug("Opening debugger interface.\n");
		mutex_unlock(&acpi_aml_io.lock);

		pr_debug("Initializing debugger thread.\n");
		status = acpi_initialize_debugger();
		अगर (ACPI_FAILURE(status)) अणु
			pr_err("Failed to initialize debugger.\n");
			ret = -EINVAL;
			जाओ err_निकास;
		पूर्ण
		pr_debug("Debugger thread initialized.\n");

		mutex_lock(&acpi_aml_io.lock);
		acpi_aml_io.flags |= ACPI_AML_OPENED;
		acpi_aml_io.out_crc.head = acpi_aml_io.out_crc.tail = 0;
		acpi_aml_io.in_crc.head = acpi_aml_io.in_crc.tail = 0;
		pr_debug("Debugger interface opened.\n");
	पूर्ण
	acpi_aml_io.users++;
err_lock:
	अगर (ret < 0) अणु
		अगर (acpi_aml_active_पढ़ोer == file)
			acpi_aml_active_पढ़ोer = शून्य;
	पूर्ण
	mutex_unlock(&acpi_aml_io.lock);
err_निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक acpi_aml_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	mutex_lock(&acpi_aml_io.lock);
	acpi_aml_io.users--;
	अगर (file == acpi_aml_active_पढ़ोer) अणु
		pr_debug("Closing debugger reader.\n");
		acpi_aml_active_पढ़ोer = शून्य;

		pr_debug("Closing debugger interface.\n");
		acpi_aml_io.flags |= ACPI_AML_CLOSED;

		/*
		 * Wake up all user space/kernel space blocked
		 * पढ़ोers/ग_लिखोrs.
		 */
		wake_up_पूर्णांकerruptible(&acpi_aml_io.रुको);
		mutex_unlock(&acpi_aml_io.lock);
		/*
		 * Wait all user space/kernel space पढ़ोers/ग_लिखोrs to
		 * stop so that ACPICA command loop of the debugger thपढ़ो
		 * should fail all its command line पढ़ोs after this poपूर्णांक.
		 */
		रुको_event(acpi_aml_io.रुको, !acpi_aml_busy());

		/*
		 * Then we try to terminate the debugger thपढ़ो अगर it is
		 * not terminated.
		 */
		pr_debug("Terminating debugger thread.\n");
		acpi_terminate_debugger();
		रुको_event(acpi_aml_io.रुको, !acpi_aml_used());
		pr_debug("Debugger thread terminated.\n");

		mutex_lock(&acpi_aml_io.lock);
		acpi_aml_io.flags &= ~ACPI_AML_OPENED;
	पूर्ण
	अगर (acpi_aml_io.users == 0) अणु
		pr_debug("Debugger interface closed.\n");
		acpi_aml_io.flags &= ~ACPI_AML_CLOSED;
	पूर्ण
	mutex_unlock(&acpi_aml_io.lock);
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_aml_पढ़ो_user(अक्षर __user *buf, पूर्णांक len)
अणु
	पूर्णांक ret;
	काष्ठा circ_buf *crc = &acpi_aml_io.out_crc;
	पूर्णांक n;
	अक्षर *p;

	ret = acpi_aml_lock_पढ़ो(crc, ACPI_AML_OUT_USER);
	अगर (ret < 0)
		वापस ret;
	/* sync head beक्रमe removing logs */
	smp_rmb();
	p = &crc->buf[crc->tail];
	n = min(len, circ_count_to_end(crc));
	अगर (copy_to_user(buf, p, n)) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण
	/* sync tail after removing logs */
	smp_mb();
	crc->tail = (crc->tail + n) & (ACPI_AML_BUF_SIZE - 1);
	ret = n;
out:
	acpi_aml_unlock_fअगरo(ACPI_AML_OUT_USER, ret >= 0);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार acpi_aml_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक ret = 0;
	पूर्णांक size = 0;

	अगर (!count)
		वापस 0;
	अगर (!access_ok(buf, count))
		वापस -EFAULT;

	जबतक (count > 0) अणु
again:
		ret = acpi_aml_पढ़ो_user(buf + size, count);
		अगर (ret == -EAGAIN) अणु
			अगर (file->f_flags & O_NONBLOCK)
				अवरोध;
			अन्यथा अणु
				ret = रुको_event_पूर्णांकerruptible(acpi_aml_io.रुको,
					acpi_aml_user_पढ़ोable());
				/*
				 * We need to retry when the condition
				 * becomes true.
				 */
				अगर (ret == 0)
					जाओ again;
			पूर्ण
		पूर्ण
		अगर (ret < 0) अणु
			अगर (!acpi_aml_running())
				ret = 0;
			अवरोध;
		पूर्ण
		अगर (ret) अणु
			size += ret;
			count -= ret;
			*ppos += ret;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस size > 0 ? size : ret;
पूर्ण

अटल पूर्णांक acpi_aml_ग_लिखो_user(स्थिर अक्षर __user *buf, पूर्णांक len)
अणु
	पूर्णांक ret;
	काष्ठा circ_buf *crc = &acpi_aml_io.in_crc;
	पूर्णांक n;
	अक्षर *p;

	ret = acpi_aml_lock_ग_लिखो(crc, ACPI_AML_IN_USER);
	अगर (ret < 0)
		वापस ret;
	/* sync tail beक्रमe inserting cmds */
	smp_mb();
	p = &crc->buf[crc->head];
	n = min(len, circ_space_to_end(crc));
	अगर (copy_from_user(p, buf, n)) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण
	/* sync head after inserting cmds */
	smp_wmb();
	crc->head = (crc->head + n) & (ACPI_AML_BUF_SIZE - 1);
	ret = n;
out:
	acpi_aml_unlock_fअगरo(ACPI_AML_IN_USER, ret >= 0);
	वापस n;
पूर्ण

अटल sमाप_प्रकार acpi_aml_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक ret = 0;
	पूर्णांक size = 0;

	अगर (!count)
		वापस 0;
	अगर (!access_ok(buf, count))
		वापस -EFAULT;

	जबतक (count > 0) अणु
again:
		ret = acpi_aml_ग_लिखो_user(buf + size, count);
		अगर (ret == -EAGAIN) अणु
			अगर (file->f_flags & O_NONBLOCK)
				अवरोध;
			अन्यथा अणु
				ret = रुको_event_पूर्णांकerruptible(acpi_aml_io.रुको,
					acpi_aml_user_writable());
				/*
				 * We need to retry when the condition
				 * becomes true.
				 */
				अगर (ret == 0)
					जाओ again;
			पूर्ण
		पूर्ण
		अगर (ret < 0) अणु
			अगर (!acpi_aml_running())
				ret = 0;
			अवरोध;
		पूर्ण
		अगर (ret) अणु
			size += ret;
			count -= ret;
			*ppos += ret;
		पूर्ण
	पूर्ण
	वापस size > 0 ? size : ret;
पूर्ण

अटल __poll_t acpi_aml_poll(काष्ठा file *file, poll_table *रुको)
अणु
	__poll_t masks = 0;

	poll_रुको(file, &acpi_aml_io.रुको, रुको);
	अगर (acpi_aml_user_पढ़ोable())
		masks |= EPOLLIN | EPOLLRDNORM;
	अगर (acpi_aml_user_writable())
		masks |= EPOLLOUT | EPOLLWRNORM;

	वापस masks;
पूर्ण

अटल स्थिर काष्ठा file_operations acpi_aml_operations = अणु
	.पढ़ो		= acpi_aml_पढ़ो,
	.ग_लिखो		= acpi_aml_ग_लिखो,
	.poll		= acpi_aml_poll,
	.खोलो		= acpi_aml_खोलो,
	.release	= acpi_aml_release,
	.llseek		= generic_file_llseek,
पूर्ण;

अटल स्थिर काष्ठा acpi_debugger_ops acpi_aml_debugger = अणु
	.create_thपढ़ो		 = acpi_aml_create_thपढ़ो,
	.पढ़ो_cmd		 = acpi_aml_पढ़ो_cmd,
	.ग_लिखो_log		 = acpi_aml_ग_लिखो_log,
	.रुको_command_पढ़ोy	 = acpi_aml_रुको_command_पढ़ोy,
	.notअगरy_command_complete = acpi_aml_notअगरy_command_complete,
पूर्ण;

अटल पूर्णांक __init acpi_aml_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (acpi_disabled)
		वापस -ENODEV;

	/* Initialize AML IO पूर्णांकerface */
	mutex_init(&acpi_aml_io.lock);
	init_रुकोqueue_head(&acpi_aml_io.रुको);
	acpi_aml_io.out_crc.buf = acpi_aml_io.out_buf;
	acpi_aml_io.in_crc.buf = acpi_aml_io.in_buf;

	acpi_aml_dentry = debugfs_create_file("acpidbg",
					      S_IFREG | S_IRUGO | S_IWUSR,
					      acpi_debugfs_dir, शून्य,
					      &acpi_aml_operations);

	ret = acpi_रेजिस्टर_debugger(THIS_MODULE, &acpi_aml_debugger);
	अगर (ret) अणु
		debugfs_हटाओ(acpi_aml_dentry);
		acpi_aml_dentry = शून्य;
		वापस ret;
	पूर्ण

	acpi_aml_initialized = true;
	वापस 0;
पूर्ण

अटल व्योम __निकास acpi_aml_निकास(व्योम)
अणु
	अगर (acpi_aml_initialized) अणु
		acpi_unरेजिस्टर_debugger(&acpi_aml_debugger);
		debugfs_हटाओ(acpi_aml_dentry);
		acpi_aml_dentry = शून्य;
		acpi_aml_initialized = false;
	पूर्ण
पूर्ण

module_init(acpi_aml_init);
module_निकास(acpi_aml_निकास);

MODULE_AUTHOR("Lv Zheng");
MODULE_DESCRIPTION("ACPI debugger userspace IO driver");
MODULE_LICENSE("GPL");
