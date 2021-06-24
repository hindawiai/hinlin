<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright IBM Corp. 2004, 2010
 * Interface implementation क्रम communication with the z/VM control program
 *
 * Author(s): Christian Borntraeger <borntraeger@de.ibm.com>
 *
 * z/VMs CP offers the possibility to issue commands via the diagnose code 8
 * this driver implements a अक्षरacter device that issues these commands and
 * वापसs the answer of CP.
 *
 * The idea of this driver is based on cpपूर्णांक from Neale Ferguson and #CP in CMS
 */

#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/compat.h>
#समावेश <linux/kernel.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/export.h>
#समावेश <linux/mutex.h>
#समावेश <linux/cma.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/cpcmd.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/vmcp.h>

काष्ठा vmcp_session अणु
	अक्षर *response;
	अचिन्हित पूर्णांक bufsize;
	अचिन्हित पूर्णांक cma_alloc : 1;
	पूर्णांक resp_size;
	पूर्णांक resp_code;
	काष्ठा mutex mutex;
पूर्ण;

अटल debug_info_t *vmcp_debug;

अटल अचिन्हित दीर्घ vmcp_cma_size __initdata = CONFIG_VMCP_CMA_SIZE * 1024 * 1024;
अटल काष्ठा cma *vmcp_cma;

अटल पूर्णांक __init early_parse_vmcp_cma(अक्षर *p)
अणु
	अगर (!p)
		वापस 1;
	vmcp_cma_size = ALIGN(memparse(p, शून्य), PAGE_SIZE);
	वापस 0;
पूर्ण
early_param("vmcp_cma", early_parse_vmcp_cma);

व्योम __init vmcp_cma_reserve(व्योम)
अणु
	अगर (!MACHINE_IS_VM)
		वापस;
	cma_declare_contiguous(0, vmcp_cma_size, 0, 0, 0, false, "vmcp", &vmcp_cma);
पूर्ण

अटल व्योम vmcp_response_alloc(काष्ठा vmcp_session *session)
अणु
	काष्ठा page *page = शून्य;
	पूर्णांक nr_pages, order;

	order = get_order(session->bufsize);
	nr_pages = ALIGN(session->bufsize, PAGE_SIZE) >> PAGE_SHIFT;
	/*
	 * For anything below order 3 allocations rely on the buddy
	 * allocator. If such low-order allocations can't be handled
	 * anymore the प्रणाली won't work anyway.
	 */
	अगर (order > 2)
		page = cma_alloc(vmcp_cma, nr_pages, 0, false);
	अगर (page) अणु
		session->response = (अक्षर *)page_to_phys(page);
		session->cma_alloc = 1;
		वापस;
	पूर्ण
	session->response = (अक्षर *)__get_मुक्त_pages(GFP_KERNEL | __GFP_RETRY_MAYFAIL, order);
पूर्ण

अटल व्योम vmcp_response_मुक्त(काष्ठा vmcp_session *session)
अणु
	पूर्णांक nr_pages, order;
	काष्ठा page *page;

	अगर (!session->response)
		वापस;
	order = get_order(session->bufsize);
	nr_pages = ALIGN(session->bufsize, PAGE_SIZE) >> PAGE_SHIFT;
	अगर (session->cma_alloc) अणु
		page = phys_to_page((अचिन्हित दीर्घ)session->response);
		cma_release(vmcp_cma, page, nr_pages);
		session->cma_alloc = 0;
	पूर्ण अन्यथा अणु
		मुक्त_pages((अचिन्हित दीर्घ)session->response, order);
	पूर्ण
	session->response = शून्य;
पूर्ण

अटल पूर्णांक vmcp_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा vmcp_session *session;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	session = kदो_स्मृति(माप(*session), GFP_KERNEL);
	अगर (!session)
		वापस -ENOMEM;

	session->bufsize = PAGE_SIZE;
	session->response = शून्य;
	session->resp_size = 0;
	mutex_init(&session->mutex);
	file->निजी_data = session;
	वापस nonseekable_खोलो(inode, file);
पूर्ण

अटल पूर्णांक vmcp_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा vmcp_session *session;

	session = file->निजी_data;
	file->निजी_data = शून्य;
	vmcp_response_मुक्त(session);
	kमुक्त(session);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार
vmcp_पढ़ो(काष्ठा file *file, अक्षर __user *buff, माप_प्रकार count, loff_t *ppos)
अणु
	sमाप_प्रकार ret;
	माप_प्रकार size;
	काष्ठा vmcp_session *session;

	session = file->निजी_data;
	अगर (mutex_lock_पूर्णांकerruptible(&session->mutex))
		वापस -ERESTARTSYS;
	अगर (!session->response) अणु
		mutex_unlock(&session->mutex);
		वापस 0;
	पूर्ण
	size = min_t(माप_प्रकार, session->resp_size, session->bufsize);
	ret = simple_पढ़ो_from_buffer(buff, count, ppos,
					session->response, size);

	mutex_unlock(&session->mutex);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार
vmcp_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buff, माप_प्रकार count,
	   loff_t *ppos)
अणु
	अक्षर *cmd;
	काष्ठा vmcp_session *session;

	अगर (count > 240)
		वापस -EINVAL;
	cmd = memdup_user_nul(buff, count);
	अगर (IS_ERR(cmd))
		वापस PTR_ERR(cmd);
	session = file->निजी_data;
	अगर (mutex_lock_पूर्णांकerruptible(&session->mutex)) अणु
		kमुक्त(cmd);
		वापस -ERESTARTSYS;
	पूर्ण
	अगर (!session->response)
		vmcp_response_alloc(session);
	अगर (!session->response) अणु
		mutex_unlock(&session->mutex);
		kमुक्त(cmd);
		वापस -ENOMEM;
	पूर्ण
	debug_text_event(vmcp_debug, 1, cmd);
	session->resp_size = cpcmd(cmd, session->response, session->bufsize,
				   &session->resp_code);
	mutex_unlock(&session->mutex);
	kमुक्त(cmd);
	*ppos = 0;		/* reset the file poपूर्णांकer after a command */
	वापस count;
पूर्ण


/*
 * These ioctls are available, as the semantics of the diagnose 8 call
 * करोes not fit very well पूर्णांकo a Linux call. Diagnose X'08' is described in
 * CP Programming Services SC24-6084-00
 *
 * VMCP_GETCODE: gives the CP वापस code back to user space
 * VMCP_SETBUF: sets the response buffer क्रम the next ग_लिखो call. diagnose 8
 * expects adjacent pages in real storage and to make matters worse, we
 * करोnt know the size of the response. Thereक्रमe we शेष to PAGESIZE and
 * let userspace to change the response size, अगर userspace expects a bigger
 * response
 */
अटल दीर्घ vmcp_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा vmcp_session *session;
	पूर्णांक ret = -ENOTTY;
	पूर्णांक __user *argp;

	session = file->निजी_data;
	अगर (is_compat_task())
		argp = compat_ptr(arg);
	अन्यथा
		argp = (पूर्णांक __user *)arg;
	अगर (mutex_lock_पूर्णांकerruptible(&session->mutex))
		वापस -ERESTARTSYS;
	चयन (cmd) अणु
	हाल VMCP_GETCODE:
		ret = put_user(session->resp_code, argp);
		अवरोध;
	हाल VMCP_SETBUF:
		vmcp_response_मुक्त(session);
		ret = get_user(session->bufsize, argp);
		अगर (ret)
			session->bufsize = PAGE_SIZE;
		अगर (!session->bufsize || get_order(session->bufsize) > 8) अणु
			session->bufsize = PAGE_SIZE;
			ret = -EINVAL;
		पूर्ण
		अवरोध;
	हाल VMCP_GETSIZE:
		ret = put_user(session->resp_size, argp);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	mutex_unlock(&session->mutex);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations vmcp_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= vmcp_खोलो,
	.release	= vmcp_release,
	.पढ़ो		= vmcp_पढ़ो,
	.ग_लिखो		= vmcp_ग_लिखो,
	.unlocked_ioctl	= vmcp_ioctl,
	.compat_ioctl	= vmcp_ioctl,
	.llseek		= no_llseek,
पूर्ण;

अटल काष्ठा miscdevice vmcp_dev = अणु
	.name	= "vmcp",
	.minor	= MISC_DYNAMIC_MINOR,
	.fops	= &vmcp_fops,
पूर्ण;

अटल पूर्णांक __init vmcp_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!MACHINE_IS_VM)
		वापस 0;

	vmcp_debug = debug_रेजिस्टर("vmcp", 1, 1, 240);
	अगर (!vmcp_debug)
		वापस -ENOMEM;

	ret = debug_रेजिस्टर_view(vmcp_debug, &debug_hex_ascii_view);
	अगर (ret) अणु
		debug_unरेजिस्टर(vmcp_debug);
		वापस ret;
	पूर्ण

	ret = misc_रेजिस्टर(&vmcp_dev);
	अगर (ret)
		debug_unरेजिस्टर(vmcp_debug);
	वापस ret;
पूर्ण
device_initcall(vmcp_init);
