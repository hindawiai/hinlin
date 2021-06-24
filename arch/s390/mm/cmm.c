<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Collaborative memory management पूर्णांकerface.
 *
 *    Copyright IBM Corp 2003, 2010
 *    Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>,
 *
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/gfp.h>
#समावेश <linux/sched.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/swap.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/oom.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/diag.h>

#अगर_घोषित CONFIG_CMM_IUCV
अटल अक्षर *cmm_शेष_sender = "VMRMSVM";
#पूर्ण_अगर
अटल अक्षर *sender;
module_param(sender, अक्षरp, 0400);
MODULE_PARM_DESC(sender,
		 "Guest name that may send SMSG messages (default VMRMSVM)");

#समावेश "../../../drivers/s390/net/smsgiucv.h"

#घोषणा CMM_NR_PAGES ((PAGE_SIZE / माप(अचिन्हित दीर्घ)) - 2)

काष्ठा cmm_page_array अणु
	काष्ठा cmm_page_array *next;
	अचिन्हित दीर्घ index;
	अचिन्हित दीर्घ pages[CMM_NR_PAGES];
पूर्ण;

अटल दीर्घ cmm_pages;
अटल दीर्घ cmm_समयd_pages;
अटल अस्थिर दीर्घ cmm_pages_target;
अटल अस्थिर दीर्घ cmm_समयd_pages_target;
अटल दीर्घ cmm_समयout_pages;
अटल दीर्घ cmm_समयout_seconds;

अटल काष्ठा cmm_page_array *cmm_page_list;
अटल काष्ठा cmm_page_array *cmm_समयd_page_list;
अटल DEFINE_SPINLOCK(cmm_lock);

अटल काष्ठा task_काष्ठा *cmm_thपढ़ो_ptr;
अटल DECLARE_WAIT_QUEUE_HEAD(cmm_thपढ़ो_रुको);

अटल व्योम cmm_समयr_fn(काष्ठा समयr_list *);
अटल व्योम cmm_set_समयr(व्योम);
अटल DEFINE_TIMER(cmm_समयr, cmm_समयr_fn);

अटल दीर्घ cmm_alloc_pages(दीर्घ nr, दीर्घ *counter,
			    काष्ठा cmm_page_array **list)
अणु
	काष्ठा cmm_page_array *pa, *npa;
	अचिन्हित दीर्घ addr;

	जबतक (nr) अणु
		addr = __get_मुक्त_page(GFP_NOIO);
		अगर (!addr)
			अवरोध;
		spin_lock(&cmm_lock);
		pa = *list;
		अगर (!pa || pa->index >= CMM_NR_PAGES) अणु
			/* Need a new page क्रम the page list. */
			spin_unlock(&cmm_lock);
			npa = (काष्ठा cmm_page_array *)
				__get_मुक्त_page(GFP_NOIO);
			अगर (!npa) अणु
				मुक्त_page(addr);
				अवरोध;
			पूर्ण
			spin_lock(&cmm_lock);
			pa = *list;
			अगर (!pa || pa->index >= CMM_NR_PAGES) अणु
				npa->next = pa;
				npa->index = 0;
				pa = npa;
				*list = pa;
			पूर्ण अन्यथा
				मुक्त_page((अचिन्हित दीर्घ) npa);
		पूर्ण
		diag10_range(addr >> PAGE_SHIFT, 1);
		pa->pages[pa->index++] = addr;
		(*counter)++;
		spin_unlock(&cmm_lock);
		nr--;
	पूर्ण
	वापस nr;
पूर्ण

अटल दीर्घ cmm_मुक्त_pages(दीर्घ nr, दीर्घ *counter, काष्ठा cmm_page_array **list)
अणु
	काष्ठा cmm_page_array *pa;
	अचिन्हित दीर्घ addr;

	spin_lock(&cmm_lock);
	pa = *list;
	जबतक (nr) अणु
		अगर (!pa || pa->index <= 0)
			अवरोध;
		addr = pa->pages[--pa->index];
		अगर (pa->index == 0) अणु
			pa = pa->next;
			मुक्त_page((अचिन्हित दीर्घ) *list);
			*list = pa;
		पूर्ण
		मुक्त_page(addr);
		(*counter)--;
		nr--;
	पूर्ण
	spin_unlock(&cmm_lock);
	वापस nr;
पूर्ण

अटल पूर्णांक cmm_oom_notअगरy(काष्ठा notअगरier_block *self,
			  अचिन्हित दीर्घ dummy, व्योम *parm)
अणु
	अचिन्हित दीर्घ *मुक्तd = parm;
	दीर्घ nr = 256;

	nr = cmm_मुक्त_pages(nr, &cmm_समयd_pages, &cmm_समयd_page_list);
	अगर (nr > 0)
		nr = cmm_मुक्त_pages(nr, &cmm_pages, &cmm_page_list);
	cmm_pages_target = cmm_pages;
	cmm_समयd_pages_target = cmm_समयd_pages;
	*मुक्तd += 256 - nr;
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block cmm_oom_nb = अणु
	.notअगरier_call = cmm_oom_notअगरy,
पूर्ण;

अटल पूर्णांक cmm_thपढ़ो(व्योम *dummy)
अणु
	पूर्णांक rc;

	जबतक (1) अणु
		rc = रुको_event_पूर्णांकerruptible(cmm_thपढ़ो_रुको,
			cmm_pages != cmm_pages_target ||
			cmm_समयd_pages != cmm_समयd_pages_target ||
			kthपढ़ो_should_stop());
		अगर (kthपढ़ो_should_stop() || rc == -ERESTARTSYS) अणु
			cmm_pages_target = cmm_pages;
			cmm_समयd_pages_target = cmm_समयd_pages;
			अवरोध;
		पूर्ण
		अगर (cmm_pages_target > cmm_pages) अणु
			अगर (cmm_alloc_pages(1, &cmm_pages, &cmm_page_list))
				cmm_pages_target = cmm_pages;
		पूर्ण अन्यथा अगर (cmm_pages_target < cmm_pages) अणु
			cmm_मुक्त_pages(1, &cmm_pages, &cmm_page_list);
		पूर्ण
		अगर (cmm_समयd_pages_target > cmm_समयd_pages) अणु
			अगर (cmm_alloc_pages(1, &cmm_समयd_pages,
					   &cmm_समयd_page_list))
				cmm_समयd_pages_target = cmm_समयd_pages;
		पूर्ण अन्यथा अगर (cmm_समयd_pages_target < cmm_समयd_pages) अणु
			cmm_मुक्त_pages(1, &cmm_समयd_pages,
				       &cmm_समयd_page_list);
		पूर्ण
		अगर (cmm_समयd_pages > 0 && !समयr_pending(&cmm_समयr))
			cmm_set_समयr();
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम cmm_kick_thपढ़ो(व्योम)
अणु
	wake_up(&cmm_thपढ़ो_रुको);
पूर्ण

अटल व्योम cmm_set_समयr(व्योम)
अणु
	अगर (cmm_समयd_pages_target <= 0 || cmm_समयout_seconds <= 0) अणु
		अगर (समयr_pending(&cmm_समयr))
			del_समयr(&cmm_समयr);
		वापस;
	पूर्ण
	mod_समयr(&cmm_समयr, jअगरfies + msecs_to_jअगरfies(cmm_समयout_seconds * MSEC_PER_SEC));
पूर्ण

अटल व्योम cmm_समयr_fn(काष्ठा समयr_list *unused)
अणु
	दीर्घ nr;

	nr = cmm_समयd_pages_target - cmm_समयout_pages;
	अगर (nr < 0)
		cmm_समयd_pages_target = 0;
	अन्यथा
		cmm_समयd_pages_target = nr;
	cmm_kick_thपढ़ो();
	cmm_set_समयr();
पूर्ण

अटल व्योम cmm_set_pages(दीर्घ nr)
अणु
	cmm_pages_target = nr;
	cmm_kick_thपढ़ो();
पूर्ण

अटल दीर्घ cmm_get_pages(व्योम)
अणु
	वापस cmm_pages;
पूर्ण

अटल व्योम cmm_add_समयd_pages(दीर्घ nr)
अणु
	cmm_समयd_pages_target += nr;
	cmm_kick_thपढ़ो();
पूर्ण

अटल दीर्घ cmm_get_समयd_pages(व्योम)
अणु
	वापस cmm_समयd_pages;
पूर्ण

अटल व्योम cmm_set_समयout(दीर्घ nr, दीर्घ seconds)
अणु
	cmm_समयout_pages = nr;
	cmm_समयout_seconds = seconds;
	cmm_set_समयr();
पूर्ण

अटल पूर्णांक cmm_skip_blanks(अक्षर *cp, अक्षर **endp)
अणु
	अक्षर *str;

	क्रम (str = cp; *str == ' ' || *str == '\t'; str++)
		;
	*endp = str;
	वापस str != cp;
पूर्ण

अटल पूर्णांक cmm_pages_handler(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
			     व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	दीर्घ nr = cmm_get_pages();
	काष्ठा ctl_table ctl_entry = अणु
		.procname	= ctl->procname,
		.data		= &nr,
		.maxlen		= माप(दीर्घ),
	पूर्ण;
	पूर्णांक rc;

	rc = proc_करोuदीर्घvec_minmax(&ctl_entry, ग_लिखो, buffer, lenp, ppos);
	अगर (rc < 0 || !ग_लिखो)
		वापस rc;

	cmm_set_pages(nr);
	वापस 0;
पूर्ण

अटल पूर्णांक cmm_समयd_pages_handler(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
				   व्योम *buffer, माप_प्रकार *lenp,
				   loff_t *ppos)
अणु
	दीर्घ nr = cmm_get_समयd_pages();
	काष्ठा ctl_table ctl_entry = अणु
		.procname	= ctl->procname,
		.data		= &nr,
		.maxlen		= माप(दीर्घ),
	पूर्ण;
	पूर्णांक rc;

	rc = proc_करोuदीर्घvec_minmax(&ctl_entry, ग_लिखो, buffer, lenp, ppos);
	अगर (rc < 0 || !ग_लिखो)
		वापस rc;

	cmm_add_समयd_pages(nr);
	वापस 0;
पूर्ण

अटल पूर्णांक cmm_समयout_handler(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
			       व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	अक्षर buf[64], *p;
	दीर्घ nr, seconds;
	अचिन्हित पूर्णांक len;

	अगर (!*lenp || (*ppos && !ग_लिखो)) अणु
		*lenp = 0;
		वापस 0;
	पूर्ण

	अगर (ग_लिखो) अणु
		len = min(*lenp, माप(buf));
		स_नकल(buf, buffer, len);
		buf[len - 1] = '\0';
		cmm_skip_blanks(buf, &p);
		nr = simple_म_से_अदीर्घ(p, &p, 0);
		cmm_skip_blanks(p, &p);
		seconds = simple_म_से_अदीर्घ(p, &p, 0);
		cmm_set_समयout(nr, seconds);
		*ppos += *lenp;
	पूर्ण अन्यथा अणु
		len = प्र_लिखो(buf, "%ld %ld\n",
			      cmm_समयout_pages, cmm_समयout_seconds);
		अगर (len > *lenp)
			len = *lenp;
		स_नकल(buffer, buf, len);
		*lenp = len;
		*ppos += len;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा ctl_table cmm_table[] = अणु
	अणु
		.procname	= "cmm_pages",
		.mode		= 0644,
		.proc_handler	= cmm_pages_handler,
	पूर्ण,
	अणु
		.procname	= "cmm_timed_pages",
		.mode		= 0644,
		.proc_handler	= cmm_समयd_pages_handler,
	पूर्ण,
	अणु
		.procname	= "cmm_timeout",
		.mode		= 0644,
		.proc_handler	= cmm_समयout_handler,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table cmm_dir_table[] = अणु
	अणु
		.procname	= "vm",
		.maxlen		= 0,
		.mode		= 0555,
		.child		= cmm_table,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

#अगर_घोषित CONFIG_CMM_IUCV
#घोषणा SMSG_PREFIX "CMM"
अटल व्योम cmm_smsg_target(स्थिर अक्षर *from, अक्षर *msg)
अणु
	दीर्घ nr, seconds;

	अगर (म_माप(sender) > 0 && म_भेद(from, sender) != 0)
		वापस;
	अगर (!cmm_skip_blanks(msg + म_माप(SMSG_PREFIX), &msg))
		वापस;
	अगर (म_भेदन(msg, "SHRINK", 6) == 0) अणु
		अगर (!cmm_skip_blanks(msg + 6, &msg))
			वापस;
		nr = simple_म_से_अदीर्घ(msg, &msg, 0);
		cmm_skip_blanks(msg, &msg);
		अगर (*msg == '\0')
			cmm_set_pages(nr);
	पूर्ण अन्यथा अगर (म_भेदन(msg, "RELEASE", 7) == 0) अणु
		अगर (!cmm_skip_blanks(msg + 7, &msg))
			वापस;
		nr = simple_म_से_अदीर्घ(msg, &msg, 0);
		cmm_skip_blanks(msg, &msg);
		अगर (*msg == '\0')
			cmm_add_समयd_pages(nr);
	पूर्ण अन्यथा अगर (म_भेदन(msg, "REUSE", 5) == 0) अणु
		अगर (!cmm_skip_blanks(msg + 5, &msg))
			वापस;
		nr = simple_म_से_अदीर्घ(msg, &msg, 0);
		अगर (!cmm_skip_blanks(msg, &msg))
			वापस;
		seconds = simple_म_से_अदीर्घ(msg, &msg, 0);
		cmm_skip_blanks(msg, &msg);
		अगर (*msg == '\0')
			cmm_set_समयout(nr, seconds);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल काष्ठा ctl_table_header *cmm_sysctl_header;

अटल पूर्णांक __init cmm_init(व्योम)
अणु
	पूर्णांक rc = -ENOMEM;

	cmm_sysctl_header = रेजिस्टर_sysctl_table(cmm_dir_table);
	अगर (!cmm_sysctl_header)
		जाओ out_sysctl;
#अगर_घोषित CONFIG_CMM_IUCV
	/* convert sender to upperहाल अक्षरacters */
	अगर (sender) अणु
		पूर्णांक len = म_माप(sender);
		जबतक (len--)
			sender[len] = बड़े(sender[len]);
	पूर्ण अन्यथा अणु
		sender = cmm_शेष_sender;
	पूर्ण

	rc = smsg_रेजिस्टर_callback(SMSG_PREFIX, cmm_smsg_target);
	अगर (rc < 0)
		जाओ out_smsg;
#पूर्ण_अगर
	rc = रेजिस्टर_oom_notअगरier(&cmm_oom_nb);
	अगर (rc < 0)
		जाओ out_oom_notअगरy;
	cmm_thपढ़ो_ptr = kthपढ़ो_run(cmm_thपढ़ो, शून्य, "cmmthread");
	अगर (!IS_ERR(cmm_thपढ़ो_ptr))
		वापस 0;

	rc = PTR_ERR(cmm_thपढ़ो_ptr);
	unरेजिस्टर_oom_notअगरier(&cmm_oom_nb);
out_oom_notअगरy:
#अगर_घोषित CONFIG_CMM_IUCV
	smsg_unरेजिस्टर_callback(SMSG_PREFIX, cmm_smsg_target);
out_smsg:
#पूर्ण_अगर
	unरेजिस्टर_sysctl_table(cmm_sysctl_header);
out_sysctl:
	del_समयr_sync(&cmm_समयr);
	वापस rc;
पूर्ण
module_init(cmm_init);

अटल व्योम __निकास cmm_निकास(व्योम)
अणु
	unरेजिस्टर_sysctl_table(cmm_sysctl_header);
#अगर_घोषित CONFIG_CMM_IUCV
	smsg_unरेजिस्टर_callback(SMSG_PREFIX, cmm_smsg_target);
#पूर्ण_अगर
	unरेजिस्टर_oom_notअगरier(&cmm_oom_nb);
	kthपढ़ो_stop(cmm_thपढ़ो_ptr);
	del_समयr_sync(&cmm_समयr);
	cmm_मुक्त_pages(cmm_pages, &cmm_pages, &cmm_page_list);
	cmm_मुक्त_pages(cmm_समयd_pages, &cmm_समयd_pages, &cmm_समयd_page_list);
पूर्ण
module_निकास(cmm_निकास);

MODULE_LICENSE("GPL");
