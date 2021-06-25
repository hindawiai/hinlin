<शैली गुरु>
/*
 * Copyright (C) 2001 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 * Licensed under the GPL
 */

#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unistd.h>
#समावेश <os.h>
#समावेश <skas.h>
#समावेश <sysdep/tls.h>

अटल अंतरभूत पूर्णांक modअगरy_ldt (पूर्णांक func, व्योम *ptr, अचिन्हित दीर्घ bytecount)
अणु
	वापस syscall(__NR_modअगरy_ldt, func, ptr, bytecount);
पूर्ण

अटल दीर्घ ग_लिखो_ldt_entry(काष्ठा mm_id *mm_idp, पूर्णांक func,
		     काष्ठा user_desc *desc, व्योम **addr, पूर्णांक करोne)
अणु
	दीर्घ res;
	व्योम *stub_addr;
	res = syscall_stub_data(mm_idp, (अचिन्हित दीर्घ *)desc,
				(माप(*desc) + माप(दीर्घ) - 1) &
				    ~(माप(दीर्घ) - 1),
				addr, &stub_addr);
	अगर (!res) अणु
		अचिन्हित दीर्घ args[] = अणु func,
					 (अचिन्हित दीर्घ)stub_addr,
					 माप(*desc),
					 0, 0, 0 पूर्ण;
		res = run_syscall_stub(mm_idp, __NR_modअगरy_ldt, args,
				       0, addr, करोne);
	पूर्ण

	वापस res;
पूर्ण

/*
 * In skas mode, we hold our own ldt data in UML.
 * Thus, the code implementing sys_modअगरy_ldt_skas
 * is very similar to (and mostly stolen from) sys_modअगरy_ldt
 * क्रम arch/i386/kernel/ldt.c
 * The routines copied and modअगरied in part are:
 * - पढ़ो_ldt
 * - पढ़ो_शेष_ldt
 * - ग_लिखो_ldt
 * - sys_modअगरy_ldt_skas
 */

अटल पूर्णांक पढ़ो_ldt(व्योम __user * ptr, अचिन्हित दीर्घ bytecount)
अणु
	पूर्णांक i, err = 0;
	अचिन्हित दीर्घ size;
	uml_ldt_t *ldt = &current->mm->context.arch.ldt;

	अगर (!ldt->entry_count)
		जाओ out;
	अगर (bytecount > LDT_ENTRY_SIZE*LDT_ENTRIES)
		bytecount = LDT_ENTRY_SIZE*LDT_ENTRIES;
	err = bytecount;

	mutex_lock(&ldt->lock);
	अगर (ldt->entry_count <= LDT_सूचीECT_ENTRIES) अणु
		size = LDT_ENTRY_SIZE*LDT_सूचीECT_ENTRIES;
		अगर (size > bytecount)
			size = bytecount;
		अगर (copy_to_user(ptr, ldt->u.entries, size))
			err = -EFAULT;
		bytecount -= size;
		ptr += size;
	पूर्ण
	अन्यथा अणु
		क्रम (i=0; i<ldt->entry_count/LDT_ENTRIES_PER_PAGE && bytecount;
		     i++) अणु
			size = PAGE_SIZE;
			अगर (size > bytecount)
				size = bytecount;
			अगर (copy_to_user(ptr, ldt->u.pages[i], size)) अणु
				err = -EFAULT;
				अवरोध;
			पूर्ण
			bytecount -= size;
			ptr += size;
		पूर्ण
	पूर्ण
	mutex_unlock(&ldt->lock);

	अगर (bytecount == 0 || err == -EFAULT)
		जाओ out;

	अगर (clear_user(ptr, bytecount))
		err = -EFAULT;

out:
	वापस err;
पूर्ण

अटल पूर्णांक पढ़ो_शेष_ldt(व्योम __user * ptr, अचिन्हित दीर्घ bytecount)
अणु
	पूर्णांक err;

	अगर (bytecount > 5*LDT_ENTRY_SIZE)
		bytecount = 5*LDT_ENTRY_SIZE;

	err = bytecount;
	/*
	 * UML करोesn't support lcall7 and lcall27.
	 * So, we करोn't really have a शेष ldt, but emulate
	 * an empty ldt of common host शेष ldt size.
	 */
	अगर (clear_user(ptr, bytecount))
		err = -EFAULT;

	वापस err;
पूर्ण

अटल पूर्णांक ग_लिखो_ldt(व्योम __user * ptr, अचिन्हित दीर्घ bytecount, पूर्णांक func)
अणु
	uml_ldt_t *ldt = &current->mm->context.arch.ldt;
	काष्ठा mm_id * mm_idp = &current->mm->context.id;
	पूर्णांक i, err;
	काष्ठा user_desc ldt_info;
	काष्ठा ldt_entry entry0, *ldt_p;
	व्योम *addr = शून्य;

	err = -EINVAL;
	अगर (bytecount != माप(ldt_info))
		जाओ out;
	err = -EFAULT;
	अगर (copy_from_user(&ldt_info, ptr, माप(ldt_info)))
		जाओ out;

	err = -EINVAL;
	अगर (ldt_info.entry_number >= LDT_ENTRIES)
		जाओ out;
	अगर (ldt_info.contents == 3) अणु
		अगर (func == 1)
			जाओ out;
		अगर (ldt_info.seg_not_present == 0)
			जाओ out;
	पूर्ण

	mutex_lock(&ldt->lock);

	err = ग_लिखो_ldt_entry(mm_idp, func, &ldt_info, &addr, 1);
	अगर (err)
		जाओ out_unlock;

	अगर (ldt_info.entry_number >= ldt->entry_count &&
	    ldt_info.entry_number >= LDT_सूचीECT_ENTRIES) अणु
		क्रम (i=ldt->entry_count/LDT_ENTRIES_PER_PAGE;
		     i*LDT_ENTRIES_PER_PAGE <= ldt_info.entry_number;
		     i++) अणु
			अगर (i == 0)
				स_नकल(&entry0, ldt->u.entries,
				       माप(entry0));
			ldt->u.pages[i] = (काष्ठा ldt_entry *)
				__get_मुक्त_page(GFP_KERNEL|__GFP_ZERO);
			अगर (!ldt->u.pages[i]) अणु
				err = -ENOMEM;
				/* Unकरो the change in host */
				स_रखो(&ldt_info, 0, माप(ldt_info));
				ग_लिखो_ldt_entry(mm_idp, 1, &ldt_info, &addr, 1);
				जाओ out_unlock;
			पूर्ण
			अगर (i == 0) अणु
				स_नकल(ldt->u.pages[0], &entry0,
				       माप(entry0));
				स_नकल(ldt->u.pages[0]+1, ldt->u.entries+1,
				       माप(entry0)*(LDT_सूचीECT_ENTRIES-1));
			पूर्ण
			ldt->entry_count = (i + 1) * LDT_ENTRIES_PER_PAGE;
		पूर्ण
	पूर्ण
	अगर (ldt->entry_count <= ldt_info.entry_number)
		ldt->entry_count = ldt_info.entry_number + 1;

	अगर (ldt->entry_count <= LDT_सूचीECT_ENTRIES)
		ldt_p = ldt->u.entries + ldt_info.entry_number;
	अन्यथा
		ldt_p = ldt->u.pages[ldt_info.entry_number/LDT_ENTRIES_PER_PAGE] +
			ldt_info.entry_number%LDT_ENTRIES_PER_PAGE;

	अगर (ldt_info.base_addr == 0 && ldt_info.limit == 0 &&
	   (func == 1 || LDT_empty(&ldt_info))) अणु
		ldt_p->a = 0;
		ldt_p->b = 0;
	पूर्ण
	अन्यथाअणु
		अगर (func == 1)
			ldt_info.useable = 0;
		ldt_p->a = LDT_entry_a(&ldt_info);
		ldt_p->b = LDT_entry_b(&ldt_info);
	पूर्ण
	err = 0;

out_unlock:
	mutex_unlock(&ldt->lock);
out:
	वापस err;
पूर्ण

अटल दीर्घ करो_modअगरy_ldt_skas(पूर्णांक func, व्योम __user *ptr,
			       अचिन्हित दीर्घ bytecount)
अणु
	पूर्णांक ret = -ENOSYS;

	चयन (func) अणु
		हाल 0:
			ret = पढ़ो_ldt(ptr, bytecount);
			अवरोध;
		हाल 1:
		हाल 0x11:
			ret = ग_लिखो_ldt(ptr, bytecount, func);
			अवरोध;
		हाल 2:
			ret = पढ़ो_शेष_ldt(ptr, bytecount);
			अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल DEFINE_SPINLOCK(host_ldt_lock);
अटल लघु dummy_list[9] = अणु0, -1पूर्ण;
अटल लघु * host_ldt_entries = शून्य;

अटल व्योम ldt_get_host_info(व्योम)
अणु
	दीर्घ ret;
	काष्ठा ldt_entry * ldt;
	लघु *पंचांगp;
	पूर्णांक i, size, k, order;

	spin_lock(&host_ldt_lock);

	अगर (host_ldt_entries != शून्य) अणु
		spin_unlock(&host_ldt_lock);
		वापस;
	पूर्ण
	host_ldt_entries = dummy_list+1;

	spin_unlock(&host_ldt_lock);

	क्रम (i = LDT_PAGES_MAX-1, order=0; i; i>>=1, order++)
		;

	ldt = (काष्ठा ldt_entry *)
	      __get_मुक्त_pages(GFP_KERNEL|__GFP_ZERO, order);
	अगर (ldt == शून्य) अणु
		prपूर्णांकk(KERN_ERR "ldt_get_host_info: couldn't allocate buffer "
		       "for host ldt\n");
		वापस;
	पूर्ण

	ret = modअगरy_ldt(0, ldt, (1<<order)*PAGE_SIZE);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "ldt_get_host_info: couldn't read host ldt\n");
		जाओ out_मुक्त;
	पूर्ण
	अगर (ret == 0) अणु
		/* शेष_ldt is active, simply ग_लिखो an empty entry 0 */
		host_ldt_entries = dummy_list;
		जाओ out_मुक्त;
	पूर्ण

	क्रम (i=0, size=0; i<ret/LDT_ENTRY_SIZE; i++) अणु
		अगर (ldt[i].a != 0 || ldt[i].b != 0)
			size++;
	पूर्ण

	अगर (size < ARRAY_SIZE(dummy_list))
		host_ldt_entries = dummy_list;
	अन्यथा अणु
		size = (size + 1) * माप(dummy_list[0]);
		पंचांगp = kदो_स्मृति(size, GFP_KERNEL);
		अगर (पंचांगp == शून्य) अणु
			prपूर्णांकk(KERN_ERR "ldt_get_host_info: couldn't allocate "
			       "host ldt list\n");
			जाओ out_मुक्त;
		पूर्ण
		host_ldt_entries = पंचांगp;
	पूर्ण

	क्रम (i=0, k=0; i<ret/LDT_ENTRY_SIZE; i++) अणु
		अगर (ldt[i].a != 0 || ldt[i].b != 0)
			host_ldt_entries[k++] = i;
	पूर्ण
	host_ldt_entries[k] = -1;

out_मुक्त:
	मुक्त_pages((अचिन्हित दीर्घ)ldt, order);
पूर्ण

दीर्घ init_new_ldt(काष्ठा mm_context *new_mm, काष्ठा mm_context *from_mm)
अणु
	काष्ठा user_desc desc;
	लघु * num_p;
	पूर्णांक i;
	दीर्घ page, err=0;
	व्योम *addr = शून्य;


	mutex_init(&new_mm->arch.ldt.lock);

	अगर (!from_mm) अणु
		स_रखो(&desc, 0, माप(desc));
		/*
		 * Now we try to retrieve info about the ldt, we
		 * inherited from the host. All ldt-entries found
		 * will be reset in the following loop
		 */
		ldt_get_host_info();
		क्रम (num_p=host_ldt_entries; *num_p != -1; num_p++) अणु
			desc.entry_number = *num_p;
			err = ग_लिखो_ldt_entry(&new_mm->id, 1, &desc,
					      &addr, *(num_p + 1) == -1);
			अगर (err)
				अवरोध;
		पूर्ण
		new_mm->arch.ldt.entry_count = 0;

		जाओ out;
	पूर्ण

	/*
	 * Our local LDT is used to supply the data क्रम
	 * modअगरy_ldt(READLDT), अगर PTRACE_LDT isn't available,
	 * i.e., we have to use the stub क्रम modअगरy_ldt, which
	 * can't handle the big पढ़ो buffer of up to 64kB.
	 */
	mutex_lock(&from_mm->arch.ldt.lock);
	अगर (from_mm->arch.ldt.entry_count <= LDT_सूचीECT_ENTRIES)
		स_नकल(new_mm->arch.ldt.u.entries, from_mm->arch.ldt.u.entries,
		       माप(new_mm->arch.ldt.u.entries));
	अन्यथा अणु
		i = from_mm->arch.ldt.entry_count / LDT_ENTRIES_PER_PAGE;
		जबतक (i-->0) अणु
			page = __get_मुक्त_page(GFP_KERNEL|__GFP_ZERO);
			अगर (!page) अणु
				err = -ENOMEM;
				अवरोध;
			पूर्ण
			new_mm->arch.ldt.u.pages[i] =
				(काष्ठा ldt_entry *) page;
			स_नकल(new_mm->arch.ldt.u.pages[i],
			       from_mm->arch.ldt.u.pages[i], PAGE_SIZE);
		पूर्ण
	पूर्ण
	new_mm->arch.ldt.entry_count = from_mm->arch.ldt.entry_count;
	mutex_unlock(&from_mm->arch.ldt.lock);

    out:
	वापस err;
पूर्ण


व्योम मुक्त_ldt(काष्ठा mm_context *mm)
अणु
	पूर्णांक i;

	अगर (mm->arch.ldt.entry_count > LDT_सूचीECT_ENTRIES) अणु
		i = mm->arch.ldt.entry_count / LDT_ENTRIES_PER_PAGE;
		जबतक (i-- > 0)
			मुक्त_page((दीर्घ) mm->arch.ldt.u.pages[i]);
	पूर्ण
	mm->arch.ldt.entry_count = 0;
पूर्ण

SYSCALL_DEFINE3(modअगरy_ldt, पूर्णांक , func , व्योम __user * , ptr ,
		अचिन्हित दीर्घ , bytecount)
अणु
	/* See non-um modअगरy_ldt() क्रम why we करो this cast */
	वापस (अचिन्हित पूर्णांक)करो_modअगरy_ldt_skas(func, ptr, bytecount);
पूर्ण
