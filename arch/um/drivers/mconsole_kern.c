<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2001 Lennert Buytenhek (buytenh@gnu.org)
 * Copyright (C) 2001 - 2008 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <linux/console.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/माला.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/reboot.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/utsname.h>
#समावेश <linux/socket.h>
#समावेश <linux/un.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/mutex.h>
#समावेश <linux/fs.h>
#समावेश <linux/mount.h>
#समावेश <linux/file.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/चयन_to.h>

#समावेश <init.h>
#समावेश <irq_kern.h>
#समावेश <irq_user.h>
#समावेश <kern_util.h>
#समावेश "mconsole.h"
#समावेश "mconsole_kern.h"
#समावेश <os.h>

अटल काष्ठा vfsmount *proc_mnt = शून्य;

अटल पूर्णांक करो_unlink_socket(काष्ठा notअगरier_block *notअगरier,
			    अचिन्हित दीर्घ what, व्योम *data)
अणु
	वापस mconsole_unlink_socket();
पूर्ण


अटल काष्ठा notअगरier_block reboot_notअगरier = अणु
	.notअगरier_call		= करो_unlink_socket,
	.priority		= 0,
पूर्ण;

/* Safe without explicit locking क्रम now.  Tasklets provide their own
 * locking, and the पूर्णांकerrupt handler is safe because it can't पूर्णांकerrupt
 * itself and it can only happen on CPU 0.
 */

अटल LIST_HEAD(mc_requests);

अटल व्योम mc_work_proc(काष्ठा work_काष्ठा *unused)
अणु
	काष्ठा mconsole_entry *req;
	अचिन्हित दीर्घ flags;

	जबतक (!list_empty(&mc_requests)) अणु
		local_irq_save(flags);
		req = list_entry(mc_requests.next, काष्ठा mconsole_entry, list);
		list_del(&req->list);
		local_irq_restore(flags);
		req->request.cmd->handler(&req->request);
		kमुक्त(req);
	पूर्ण
पूर्ण

अटल DECLARE_WORK(mconsole_work, mc_work_proc);

अटल irqवापस_t mconsole_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	/* दीर्घ to aव्योम size mismatch warnings from gcc */
	दीर्घ fd;
	काष्ठा mconsole_entry *new;
	अटल काष्ठा mc_request req;	/* that's OK */

	fd = (दीर्घ) dev_id;
	जबतक (mconsole_get_request(fd, &req)) अणु
		अगर (req.cmd->context == MCONSOLE_INTR)
			(*req.cmd->handler)(&req);
		अन्यथा अणु
			new = kदो_स्मृति(माप(*new), GFP_NOWAIT);
			अगर (new == शून्य)
				mconsole_reply(&req, "Out of memory", 1, 0);
			अन्यथा अणु
				new->request = req;
				new->request.regs = get_irq_regs()->regs;
				list_add(&new->list, &mc_requests);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (!list_empty(&mc_requests))
		schedule_work(&mconsole_work);
	वापस IRQ_HANDLED;
पूर्ण

व्योम mconsole_version(काष्ठा mc_request *req)
अणु
	अक्षर version[256];

	प्र_लिखो(version, "%s %s %s %s %s", utsname()->sysname,
		utsname()->nodename, utsname()->release, utsname()->version,
		utsname()->machine);
	mconsole_reply(req, version, 0, 0);
पूर्ण

व्योम mconsole_log(काष्ठा mc_request *req)
अणु
	पूर्णांक len;
	अक्षर *ptr = req->request.data;

	ptr += म_माप("log ");

	len = req->len - (ptr - req->request.data);
	prपूर्णांकk(KERN_WARNING "%.*s", len, ptr);
	mconsole_reply(req, "", 0, 0);
पूर्ण

व्योम mconsole_proc(काष्ठा mc_request *req)
अणु
	काष्ठा vfsmount *mnt = proc_mnt;
	अक्षर *buf;
	पूर्णांक len;
	काष्ठा file *file;
	पूर्णांक first_chunk = 1;
	अक्षर *ptr = req->request.data;
	loff_t pos = 0;

	ptr += म_माप("proc");
	ptr = skip_spaces(ptr);

	अगर (!mnt) अणु
		mconsole_reply(req, "Proc not available", 1, 0);
		जाओ out;
	पूर्ण
	file = file_खोलो_root(mnt->mnt_root, mnt, ptr, O_RDONLY, 0);
	अगर (IS_ERR(file)) अणु
		mconsole_reply(req, "Failed to open file", 1, 0);
		prपूर्णांकk(KERN_ERR "open /proc/%s: %ld\n", ptr, PTR_ERR(file));
		जाओ out;
	पूर्ण

	buf = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (buf == शून्य) अणु
		mconsole_reply(req, "Failed to allocate buffer", 1, 0);
		जाओ out_fput;
	पूर्ण

	करो अणु
		len = kernel_पढ़ो(file, buf, PAGE_SIZE - 1, &pos);
		अगर (len < 0) अणु
			mconsole_reply(req, "Read of file failed", 1, 0);
			जाओ out_मुक्त;
		पूर्ण
		/* Begin the file content on his own line. */
		अगर (first_chunk) अणु
			mconsole_reply(req, "\n", 0, 1);
			first_chunk = 0;
		पूर्ण
		buf[len] = '\0';
		mconsole_reply(req, buf, 0, (len > 0));
	पूर्ण जबतक (len > 0);
 out_मुक्त:
	kमुक्त(buf);
 out_fput:
	fput(file);
 out: ;
पूर्ण

#घोषणा UML_MCONSOLE_HELPTEXT \
"Commands: \न\
    version - Get kernel version \न\
    help - Prपूर्णांक this message \न\
    halt - Halt UML \न\
    reboot - Reboot UML \न\
    config <dev>=<config> - Add a new device to UML;  \न\
	same syntax as command line \न\
    config <dev> - Query the configuration of a device \न\
    हटाओ <dev> - Remove a device from UML \न\
    sysrq <letter> - Perक्रमms the SysRq action controlled by the letter \न\
    cad - invoke the Ctrl-Alt-Del handler \न\
    stop - छोड़ो the UML; it will करो nothing until it receives a 'go' \न\
    go - जारी the UML after a 'stop' \न\
    log <string> - make UML enter <string> पूर्णांकo the kernel log\न\
    proc <file> - वापसs the contents of the UML's /proc/<file>\न\
    stack <pid> - वापसs the stack of the specअगरied pid\न\
"

व्योम mconsole_help(काष्ठा mc_request *req)
अणु
	mconsole_reply(req, UML_MCONSOLE_HELPTEXT, 0, 0);
पूर्ण

व्योम mconsole_halt(काष्ठा mc_request *req)
अणु
	mconsole_reply(req, "", 0, 0);
	machine_halt();
पूर्ण

व्योम mconsole_reboot(काष्ठा mc_request *req)
अणु
	mconsole_reply(req, "", 0, 0);
	machine_restart(शून्य);
पूर्ण

व्योम mconsole_cad(काष्ठा mc_request *req)
अणु
	mconsole_reply(req, "", 0, 0);
	ctrl_alt_del();
पूर्ण

व्योम mconsole_go(काष्ठा mc_request *req)
अणु
	mconsole_reply(req, "Not stopped", 1, 0);
पूर्ण

व्योम mconsole_stop(काष्ठा mc_request *req)
अणु
	deactivate_fd(req->originating_fd, MCONSOLE_IRQ);
	os_set_fd_block(req->originating_fd, 1);
	mconsole_reply(req, "stopped", 0, 0);
	क्रम (;;) अणु
		अगर (!mconsole_get_request(req->originating_fd, req))
			जारी;
		अगर (req->cmd->handler == mconsole_go)
			अवरोध;
		अगर (req->cmd->handler == mconsole_stop) अणु
			mconsole_reply(req, "Already stopped", 1, 0);
			जारी;
		पूर्ण
		अगर (req->cmd->handler == mconsole_sysrq) अणु
			काष्ठा pt_regs *old_regs;
			old_regs = set_irq_regs((काष्ठा pt_regs *)&req->regs);
			mconsole_sysrq(req);
			set_irq_regs(old_regs);
			जारी;
		पूर्ण
		(*req->cmd->handler)(req);
	पूर्ण
	os_set_fd_block(req->originating_fd, 0);
	mconsole_reply(req, "", 0, 0);
पूर्ण

अटल DEFINE_SPINLOCK(mc_devices_lock);
अटल LIST_HEAD(mconsole_devices);

व्योम mconsole_रेजिस्टर_dev(काष्ठा mc_device *new)
अणु
	spin_lock(&mc_devices_lock);
	BUG_ON(!list_empty(&new->list));
	list_add(&new->list, &mconsole_devices);
	spin_unlock(&mc_devices_lock);
पूर्ण

अटल काष्ठा mc_device *mconsole_find_dev(अक्षर *name)
अणु
	काष्ठा list_head *ele;
	काष्ठा mc_device *dev;

	list_क्रम_each(ele, &mconsole_devices) अणु
		dev = list_entry(ele, काष्ठा mc_device, list);
		अगर (!म_भेदन(name, dev->name, म_माप(dev->name)))
			वापस dev;
	पूर्ण
	वापस शून्य;
पूर्ण

#घोषणा UNPLUGGED_PER_PAGE \
	((PAGE_SIZE - माप(काष्ठा list_head)) / माप(अचिन्हित दीर्घ))

काष्ठा unplugged_pages अणु
	काष्ठा list_head list;
	व्योम *pages[UNPLUGGED_PER_PAGE];
पूर्ण;

अटल DEFINE_MUTEX(plug_mem_mutex);
अटल अचिन्हित दीर्घ दीर्घ unplugged_pages_count = 0;
अटल LIST_HEAD(unplugged_pages);
अटल पूर्णांक unplug_index = UNPLUGGED_PER_PAGE;

अटल पूर्णांक mem_config(अक्षर *str, अक्षर **error_out)
अणु
	अचिन्हित दीर्घ दीर्घ dअगरf;
	पूर्णांक err = -EINVAL, i, add;
	अक्षर *ret;

	अगर (str[0] != '=') अणु
		*error_out = "Expected '=' after 'mem'";
		जाओ out;
	पूर्ण

	str++;
	अगर (str[0] == '-')
		add = 0;
	अन्यथा अगर (str[0] == '+') अणु
		add = 1;
	पूर्ण
	अन्यथा अणु
		*error_out = "Expected increment to start with '-' or '+'";
		जाओ out;
	पूर्ण

	str++;
	dअगरf = memparse(str, &ret);
	अगर (*ret != '\0') अणु
		*error_out = "Failed to parse memory increment";
		जाओ out;
	पूर्ण

	dअगरf /= PAGE_SIZE;

	mutex_lock(&plug_mem_mutex);
	क्रम (i = 0; i < dअगरf; i++) अणु
		काष्ठा unplugged_pages *unplugged;
		व्योम *addr;

		अगर (add) अणु
			अगर (list_empty(&unplugged_pages))
				अवरोध;

			unplugged = list_entry(unplugged_pages.next,
					       काष्ठा unplugged_pages, list);
			अगर (unplug_index > 0)
				addr = unplugged->pages[--unplug_index];
			अन्यथा अणु
				list_del(&unplugged->list);
				addr = unplugged;
				unplug_index = UNPLUGGED_PER_PAGE;
			पूर्ण

			मुक्त_page((अचिन्हित दीर्घ) addr);
			unplugged_pages_count--;
		पूर्ण
		अन्यथा अणु
			काष्ठा page *page;

			page = alloc_page(GFP_ATOMIC);
			अगर (page == शून्य)
				अवरोध;

			unplugged = page_address(page);
			अगर (unplug_index == UNPLUGGED_PER_PAGE) अणु
				list_add(&unplugged->list, &unplugged_pages);
				unplug_index = 0;
			पूर्ण
			अन्यथा अणु
				काष्ठा list_head *entry = unplugged_pages.next;
				addr = unplugged;

				unplugged = list_entry(entry,
						       काष्ठा unplugged_pages,
						       list);
				err = os_drop_memory(addr, PAGE_SIZE);
				अगर (err) अणु
					prपूर्णांकk(KERN_ERR "Failed to release "
					       "memory - errno = %d\n", err);
					*error_out = "Failed to release memory";
					जाओ out_unlock;
				पूर्ण
				unplugged->pages[unplug_index++] = addr;
			पूर्ण

			unplugged_pages_count++;
		पूर्ण
	पूर्ण

	err = 0;
out_unlock:
	mutex_unlock(&plug_mem_mutex);
out:
	वापस err;
पूर्ण

अटल पूर्णांक mem_get_config(अक्षर *name, अक्षर *str, पूर्णांक size, अक्षर **error_out)
अणु
	अक्षर buf[माप("18446744073709551615")];
	पूर्णांक len = 0;

	प्र_लिखो(buf, "%ld", uml_physmem);
	CONFIG_CHUNK(str, size, len, buf, 1);

	वापस len;
पूर्ण

अटल पूर्णांक mem_id(अक्षर **str, पूर्णांक *start_out, पूर्णांक *end_out)
अणु
	*start_out = 0;
	*end_out = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक mem_हटाओ(पूर्णांक n, अक्षर **error_out)
अणु
	*error_out = "Memory doesn't support the remove operation";
	वापस -EBUSY;
पूर्ण

अटल काष्ठा mc_device mem_mc = अणु
	.list		= LIST_HEAD_INIT(mem_mc.list),
	.name		= "mem",
	.config		= mem_config,
	.get_config	= mem_get_config,
	.id		= mem_id,
	.हटाओ		= mem_हटाओ,
पूर्ण;

अटल पूर्णांक __init mem_mc_init(व्योम)
अणु
	अगर (can_drop_memory())
		mconsole_रेजिस्टर_dev(&mem_mc);
	अन्यथा prपूर्णांकk(KERN_ERR "Can't release memory to the host - memory "
		    "hotplug won't be supported\n");
	वापस 0;
पूर्ण

__initcall(mem_mc_init);

#घोषणा CONFIG_BUF_SIZE 64

अटल व्योम mconsole_get_config(पूर्णांक (*get_config)(अक्षर *, अक्षर *, पूर्णांक,
						  अक्षर **),
				काष्ठा mc_request *req, अक्षर *name)
अणु
	अक्षर शेष_buf[CONFIG_BUF_SIZE], *error, *buf;
	पूर्णांक n, size;

	अगर (get_config == शून्य) अणु
		mconsole_reply(req, "No get_config routine defined", 1, 0);
		वापस;
	पूर्ण

	error = शून्य;
	size = ARRAY_SIZE(शेष_buf);
	buf = शेष_buf;

	जबतक (1) अणु
		n = (*get_config)(name, buf, size, &error);
		अगर (error != शून्य) अणु
			mconsole_reply(req, error, 1, 0);
			जाओ out;
		पूर्ण

		अगर (n <= size) अणु
			mconsole_reply(req, buf, 0, 0);
			जाओ out;
		पूर्ण

		अगर (buf != शेष_buf)
			kमुक्त(buf);

		size = n;
		buf = kदो_स्मृति(size, GFP_KERNEL);
		अगर (buf == शून्य) अणु
			mconsole_reply(req, "Failed to allocate buffer", 1, 0);
			वापस;
		पूर्ण
	पूर्ण
 out:
	अगर (buf != शेष_buf)
		kमुक्त(buf);
पूर्ण

व्योम mconsole_config(काष्ठा mc_request *req)
अणु
	काष्ठा mc_device *dev;
	अक्षर *ptr = req->request.data, *name, *error_string = "";
	पूर्णांक err;

	ptr += म_माप("config");
	ptr = skip_spaces(ptr);
	dev = mconsole_find_dev(ptr);
	अगर (dev == शून्य) अणु
		mconsole_reply(req, "Bad configuration option", 1, 0);
		वापस;
	पूर्ण

	name = &ptr[म_माप(dev->name)];
	ptr = name;
	जबतक ((*ptr != '=') && (*ptr != '\0'))
		ptr++;

	अगर (*ptr == '=') अणु
		err = (*dev->config)(name, &error_string);
		mconsole_reply(req, error_string, err, 0);
	पूर्ण
	अन्यथा mconsole_get_config(dev->get_config, req, name);
पूर्ण

व्योम mconsole_हटाओ(काष्ठा mc_request *req)
अणु
	काष्ठा mc_device *dev;
	अक्षर *ptr = req->request.data, *err_msg = "";
	अक्षर error[256];
	पूर्णांक err, start, end, n;

	ptr += म_माप("remove");
	ptr = skip_spaces(ptr);
	dev = mconsole_find_dev(ptr);
	अगर (dev == शून्य) अणु
		mconsole_reply(req, "Bad remove option", 1, 0);
		वापस;
	पूर्ण

	ptr = &ptr[म_माप(dev->name)];

	err = 1;
	n = (*dev->id)(&ptr, &start, &end);
	अगर (n < 0) अणु
		err_msg = "Couldn't parse device number";
		जाओ out;
	पूर्ण
	अन्यथा अगर ((n < start) || (n > end)) अणु
		प्र_लिखो(error, "Invalid device number - must be between "
			"%d and %d", start, end);
		err_msg = error;
		जाओ out;
	पूर्ण

	err_msg = शून्य;
	err = (*dev->हटाओ)(n, &err_msg);
	चयन(err) अणु
	हाल 0:
		err_msg = "";
		अवरोध;
	हाल -ENODEV:
		अगर (err_msg == शून्य)
			err_msg = "Device doesn't exist";
		अवरोध;
	हाल -EBUSY:
		अगर (err_msg == शून्य)
			err_msg = "Device is currently open";
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
out:
	mconsole_reply(req, err_msg, err, 0);
पूर्ण

काष्ठा mconsole_output अणु
	काष्ठा list_head list;
	काष्ठा mc_request *req;
पूर्ण;

अटल DEFINE_SPINLOCK(client_lock);
अटल LIST_HEAD(clients);
अटल अक्षर console_buf[MCONSOLE_MAX_DATA];

अटल व्योम console_ग_लिखो(काष्ठा console *console, स्थिर अक्षर *string,
			  अचिन्हित पूर्णांक len)
अणु
	काष्ठा list_head *ele;
	पूर्णांक n;

	अगर (list_empty(&clients))
		वापस;

	जबतक (len > 0) अणु
		n = min((माप_प्रकार) len, ARRAY_SIZE(console_buf));
		म_नकलन(console_buf, string, n);
		string += n;
		len -= n;

		list_क्रम_each(ele, &clients) अणु
			काष्ठा mconsole_output *entry;

			entry = list_entry(ele, काष्ठा mconsole_output, list);
			mconsole_reply_len(entry->req, console_buf, n, 0, 1);
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा console mc_console = अणु .name	= "mc",
				     .ग_लिखो	= console_ग_लिखो,
				     .flags	= CON_ENABLED,
				     .index	= -1 पूर्ण;

अटल पूर्णांक mc_add_console(व्योम)
अणु
	रेजिस्टर_console(&mc_console);
	वापस 0;
पूर्ण

late_initcall(mc_add_console);

अटल व्योम with_console(काष्ठा mc_request *req, व्योम (*proc)(व्योम *),
			 व्योम *arg)
अणु
	काष्ठा mconsole_output entry;
	अचिन्हित दीर्घ flags;

	entry.req = req;
	spin_lock_irqsave(&client_lock, flags);
	list_add(&entry.list, &clients);
	spin_unlock_irqrestore(&client_lock, flags);

	(*proc)(arg);

	mconsole_reply_len(req, "", 0, 0, 0);

	spin_lock_irqsave(&client_lock, flags);
	list_del(&entry.list);
	spin_unlock_irqrestore(&client_lock, flags);
पूर्ण

#अगर_घोषित CONFIG_MAGIC_SYSRQ

#समावेश <linux/sysrq.h>

अटल व्योम sysrq_proc(व्योम *arg)
अणु
	अक्षर *op = arg;
	handle_sysrq(*op);
पूर्ण

व्योम mconsole_sysrq(काष्ठा mc_request *req)
अणु
	अक्षर *ptr = req->request.data;

	ptr += म_माप("sysrq");
	ptr = skip_spaces(ptr);

	/*
	 * With 'b', the प्रणाली will shut करोwn without a chance to reply,
	 * so in this हाल, we reply first.
	 */
	अगर (*ptr == 'b')
		mconsole_reply(req, "", 0, 0);

	with_console(req, sysrq_proc, ptr);
पूर्ण
#अन्यथा
व्योम mconsole_sysrq(काष्ठा mc_request *req)
अणु
	mconsole_reply(req, "Sysrq not compiled in", 1, 0);
पूर्ण
#पूर्ण_अगर

अटल व्योम stack_proc(व्योम *arg)
अणु
	काष्ठा task_काष्ठा *task = arg;

	show_stack(task, शून्य, KERN_INFO);
पूर्ण

/*
 * Mconsole stack trace
 *  Added by Allan Graves, Jeff Dike
 *  Dumps a stacks रेजिस्टरs to the linux console.
 *  Usage stack <pid>.
 */
व्योम mconsole_stack(काष्ठा mc_request *req)
अणु
	अक्षर *ptr = req->request.data;
	पूर्णांक pid_requested= -1;
	काष्ठा task_काष्ठा *to = शून्य;

	/*
	 * Would be nice:
	 * 1) Send showregs output to mconsole.
	 * 2) Add a way to stack dump all pids.
	 */

	ptr += म_माप("stack");
	ptr = skip_spaces(ptr);

	/*
	 * Should really check क्रम multiple pids or reject bad args here
	 */
	/* What करो the arguments in mconsole_reply mean? */
	अगर (माला_पूछो(ptr, "%d", &pid_requested) == 0) अणु
		mconsole_reply(req, "Please specify a pid", 1, 0);
		वापस;
	पूर्ण

	to = find_task_by_pid_ns(pid_requested, &init_pid_ns);
	अगर ((to == शून्य) || (pid_requested == 0)) अणु
		mconsole_reply(req, "Couldn't find that pid", 1, 0);
		वापस;
	पूर्ण
	with_console(req, stack_proc, to);
पूर्ण

अटल पूर्णांक __init mount_proc(व्योम)
अणु
	काष्ठा file_प्रणाली_type *proc_fs_type;
	काष्ठा vfsmount *mnt;

	proc_fs_type = get_fs_type("proc");
	अगर (!proc_fs_type)
		वापस -ENODEV;

	mnt = kern_mount(proc_fs_type);
	put_fileप्रणाली(proc_fs_type);
	अगर (IS_ERR(mnt))
		वापस PTR_ERR(mnt);

	proc_mnt = mnt;
	वापस 0;
पूर्ण

/*
 * Changed by mconsole_setup, which is __setup, and called beक्रमe SMP is
 * active.
 */
अटल अक्षर *notअगरy_socket = शून्य;

अटल पूर्णांक __init mconsole_init(व्योम)
अणु
	/* दीर्घ to aव्योम size mismatch warnings from gcc */
	दीर्घ sock;
	पूर्णांक err;
	अक्षर file[UNIX_PATH_MAX];

	mount_proc();

	अगर (umid_file_name("mconsole", file, माप(file)))
		वापस -1;
	snम_लिखो(mconsole_socket_name, माप(file), "%s", file);

	sock = os_create_unix_socket(file, माप(file), 1);
	अगर (sock < 0) अणु
		prपूर्णांकk(KERN_ERR "Failed to initialize management console\n");
		वापस 1;
	पूर्ण
	अगर (os_set_fd_block(sock, 0))
		जाओ out;

	रेजिस्टर_reboot_notअगरier(&reboot_notअगरier);

	err = um_request_irq(MCONSOLE_IRQ, sock, IRQ_READ, mconsole_पूर्णांकerrupt,
			     IRQF_SHARED, "mconsole", (व्योम *)sock);
	अगर (err < 0) अणु
		prपूर्णांकk(KERN_ERR "Failed to get IRQ for management console\n");
		जाओ out;
	पूर्ण

	अगर (notअगरy_socket != शून्य) अणु
		notअगरy_socket = kstrdup(notअगरy_socket, GFP_KERNEL);
		अगर (notअगरy_socket != शून्य)
			mconsole_notअगरy(notअगरy_socket, MCONSOLE_SOCKET,
					mconsole_socket_name,
					म_माप(mconsole_socket_name) + 1);
		अन्यथा prपूर्णांकk(KERN_ERR "mconsole_setup failed to strdup "
			    "string\n");
	पूर्ण

	prपूर्णांकk(KERN_INFO "mconsole (version %d) initialized on %s\n",
	       MCONSOLE_VERSION, mconsole_socket_name);
	वापस 0;

 out:
	os_बंद_file(sock);
	वापस 1;
पूर्ण

__initcall(mconsole_init);

अटल sमाप_प्रकार mconsole_proc_ग_लिखो(काष्ठा file *file,
		स्थिर अक्षर __user *buffer, माप_प्रकार count, loff_t *pos)
अणु
	अक्षर *buf;

	buf = memdup_user_nul(buffer, count);
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	mconsole_notअगरy(notअगरy_socket, MCONSOLE_USER_NOTIFY, buf, count);
	kमुक्त(buf);
	वापस count;
पूर्ण

अटल स्थिर काष्ठा proc_ops mconsole_proc_ops = अणु
	.proc_ग_लिखो	= mconsole_proc_ग_लिखो,
	.proc_lseek	= noop_llseek,
पूर्ण;

अटल पूर्णांक create_proc_mconsole(व्योम)
अणु
	काष्ठा proc_dir_entry *ent;

	अगर (notअगरy_socket == शून्य)
		वापस 0;

	ent = proc_create("mconsole", 0200, शून्य, &mconsole_proc_ops);
	अगर (ent == शून्य) अणु
		prपूर्णांकk(KERN_INFO "create_proc_mconsole : proc_create failed\n");
		वापस 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल DEFINE_SPINLOCK(notअगरy_spinlock);

व्योम lock_notअगरy(व्योम)
अणु
	spin_lock(&notअगरy_spinlock);
पूर्ण

व्योम unlock_notअगरy(व्योम)
अणु
	spin_unlock(&notअगरy_spinlock);
पूर्ण

__initcall(create_proc_mconsole);

#घोषणा NOTIFY "notify:"

अटल पूर्णांक mconsole_setup(अक्षर *str)
अणु
	अगर (!म_भेदन(str, NOTIFY, म_माप(NOTIFY))) अणु
		str += म_माप(NOTIFY);
		notअगरy_socket = str;
	पूर्ण
	अन्यथा prपूर्णांकk(KERN_ERR "mconsole_setup : Unknown option - '%s'\n", str);
	वापस 1;
पूर्ण

__setup("mconsole=", mconsole_setup);

__uml_help(mconsole_setup,
"mconsole=notify:<socket>\n"
"    Requests that the mconsole driver send a message to the named Unix\n"
"    socket containing the name of the mconsole socket.  This also serves\n"
"    to notify outside processes when UML has booted far enough to respond\n"
"    to mconsole requests.\n\n"
);

अटल पूर्णांक notअगरy_panic(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ unused1,
			व्योम *ptr)
अणु
	अक्षर *message = ptr;

	अगर (notअगरy_socket == शून्य)
		वापस 0;

	mconsole_notअगरy(notअगरy_socket, MCONSOLE_PANIC, message,
			म_माप(message) + 1);
	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block panic_निकास_notअगरier = अणु
	.notअगरier_call 		= notअगरy_panic,
	.next 			= शून्य,
	.priority 		= 1
पूर्ण;

अटल पूर्णांक add_notअगरier(व्योम)
अणु
	atomic_notअगरier_chain_रेजिस्टर(&panic_notअगरier_list,
			&panic_निकास_notअगरier);
	वापस 0;
पूर्ण

__initcall(add_notअगरier);

अक्षर *mconsole_notअगरy_socket(व्योम)
अणु
	वापस notअगरy_socket;
पूर्ण

EXPORT_SYMBOL(mconsole_notअगरy_socket);
