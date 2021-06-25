<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/user.h>
#समावेश <linux/regset.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/nospec.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/ldt.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/proto.h>

#समावेश "tls.h"

/*
 * sys_alloc_thपढ़ो_area: get a yet unused TLS descriptor index.
 */
अटल पूर्णांक get_मुक्त_idx(व्योम)
अणु
	काष्ठा thपढ़ो_काष्ठा *t = &current->thपढ़ो;
	पूर्णांक idx;

	क्रम (idx = 0; idx < GDT_ENTRY_TLS_ENTRIES; idx++)
		अगर (desc_empty(&t->tls_array[idx]))
			वापस idx + GDT_ENTRY_TLS_MIN;
	वापस -ESRCH;
पूर्ण

अटल bool tls_desc_okay(स्थिर काष्ठा user_desc *info)
अणु
	/*
	 * For historical reasons (i.e. no one ever करोcumented how any
	 * of the segmentation APIs work), user programs can and करो
	 * assume that a काष्ठा user_desc that's all zeros except क्रम
	 * entry_number means "no segment at all".  This never actually
	 * worked.  In fact, up to Linux 3.19, a काष्ठा user_desc like
	 * this would create a 16-bit पढ़ो-ग_लिखो segment with base and
	 * limit both equal to zero.
	 *
	 * That was बंद enough to "no segment at all" until we
	 * hardened this function to disallow 16-bit TLS segments.  Fix
	 * it up by पूर्णांकerpreting these zeroed segments the way that they
	 * were almost certainly पूर्णांकended to be पूर्णांकerpreted.
	 *
	 * The correct way to ask क्रम "no segment at all" is to specअगरy
	 * a user_desc that satisfies LDT_empty.  To keep everything
	 * working, we accept both.
	 *
	 * Note that there's a similar kludge in modअगरy_ldt -- look at
	 * the distinction between modes 1 and 0x11.
	 */
	अगर (LDT_empty(info) || LDT_zero(info))
		वापस true;

	/*
	 * espfix is required क्रम 16-bit data segments, but espfix
	 * only works क्रम LDT segments.
	 */
	अगर (!info->seg_32bit)
		वापस false;

	/* Only allow data segments in the TLS array. */
	अगर (info->contents > 1)
		वापस false;

	/*
	 * Non-present segments with DPL 3 present an पूर्णांकeresting attack
	 * surface.  The kernel should handle such segments correctly,
	 * but TLS is very dअगरficult to protect in a sandbox, so prevent
	 * such segments from being created.
	 *
	 * If userspace needs to हटाओ a TLS entry, it can still delete
	 * it outright.
	 */
	अगर (info->seg_not_present)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम set_tls_desc(काष्ठा task_काष्ठा *p, पूर्णांक idx,
			 स्थिर काष्ठा user_desc *info, पूर्णांक n)
अणु
	काष्ठा thपढ़ो_काष्ठा *t = &p->thपढ़ो;
	काष्ठा desc_काष्ठा *desc = &t->tls_array[idx - GDT_ENTRY_TLS_MIN];
	पूर्णांक cpu;

	/*
	 * We must not get preempted जबतक modअगरying the TLS.
	 */
	cpu = get_cpu();

	जबतक (n-- > 0) अणु
		अगर (LDT_empty(info) || LDT_zero(info))
			स_रखो(desc, 0, माप(*desc));
		अन्यथा
			fill_ldt(desc, info);
		++info;
		++desc;
	पूर्ण

	अगर (t == &current->thपढ़ो)
		load_TLS(t, cpu);

	put_cpu();
पूर्ण

/*
 * Set a given TLS descriptor:
 */
पूर्णांक करो_set_thपढ़ो_area(काष्ठा task_काष्ठा *p, पूर्णांक idx,
		       काष्ठा user_desc __user *u_info,
		       पूर्णांक can_allocate)
अणु
	काष्ठा user_desc info;
	अचिन्हित लघु __maybe_unused sel, modअगरied_sel;

	अगर (copy_from_user(&info, u_info, माप(info)))
		वापस -EFAULT;

	अगर (!tls_desc_okay(&info))
		वापस -EINVAL;

	अगर (idx == -1)
		idx = info.entry_number;

	/*
	 * index -1 means the kernel should try to find and
	 * allocate an empty descriptor:
	 */
	अगर (idx == -1 && can_allocate) अणु
		idx = get_मुक्त_idx();
		अगर (idx < 0)
			वापस idx;
		अगर (put_user(idx, &u_info->entry_number))
			वापस -EFAULT;
	पूर्ण

	अगर (idx < GDT_ENTRY_TLS_MIN || idx > GDT_ENTRY_TLS_MAX)
		वापस -EINVAL;

	set_tls_desc(p, idx, &info, 1);

	/*
	 * If DS, ES, FS, or GS poपूर्णांकs to the modअगरied segment, क्रमcibly
	 * refresh it.  Only needed on x86_64 because x86_32 reloads them
	 * on वापस to user mode.
	 */
	modअगरied_sel = (idx << 3) | 3;

	अगर (p == current) अणु
#अगर_घोषित CONFIG_X86_64
		savesegment(ds, sel);
		अगर (sel == modअगरied_sel)
			loadsegment(ds, sel);

		savesegment(es, sel);
		अगर (sel == modअगरied_sel)
			loadsegment(es, sel);

		savesegment(fs, sel);
		अगर (sel == modअगरied_sel)
			loadsegment(fs, sel);
#पूर्ण_अगर

		savesegment(gs, sel);
		अगर (sel == modअगरied_sel)
			load_gs_index(sel);
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_X86_64
		अगर (p->thपढ़ो.fsindex == modअगरied_sel)
			p->thपढ़ो.fsbase = info.base_addr;

		अगर (p->thपढ़ो.gsindex == modअगरied_sel)
			p->thपढ़ो.gsbase = info.base_addr;
#पूर्ण_अगर
	पूर्ण

	वापस 0;
पूर्ण

SYSCALL_DEFINE1(set_thपढ़ो_area, काष्ठा user_desc __user *, u_info)
अणु
	वापस करो_set_thपढ़ो_area(current, -1, u_info, 1);
पूर्ण


/*
 * Get the current Thपढ़ो-Local Storage area:
 */

अटल व्योम fill_user_desc(काष्ठा user_desc *info, पूर्णांक idx,
			   स्थिर काष्ठा desc_काष्ठा *desc)

अणु
	स_रखो(info, 0, माप(*info));
	info->entry_number = idx;
	info->base_addr = get_desc_base(desc);
	info->limit = get_desc_limit(desc);
	info->seg_32bit = desc->d;
	info->contents = desc->type >> 2;
	info->पढ़ो_exec_only = !(desc->type & 2);
	info->limit_in_pages = desc->g;
	info->seg_not_present = !desc->p;
	info->useable = desc->avl;
#अगर_घोषित CONFIG_X86_64
	info->lm = desc->l;
#पूर्ण_अगर
पूर्ण

पूर्णांक करो_get_thपढ़ो_area(काष्ठा task_काष्ठा *p, पूर्णांक idx,
		       काष्ठा user_desc __user *u_info)
अणु
	काष्ठा user_desc info;
	पूर्णांक index;

	अगर (idx == -1 && get_user(idx, &u_info->entry_number))
		वापस -EFAULT;

	अगर (idx < GDT_ENTRY_TLS_MIN || idx > GDT_ENTRY_TLS_MAX)
		वापस -EINVAL;

	index = idx - GDT_ENTRY_TLS_MIN;
	index = array_index_nospec(index,
			GDT_ENTRY_TLS_MAX - GDT_ENTRY_TLS_MIN + 1);

	fill_user_desc(&info, idx, &p->thपढ़ो.tls_array[index]);

	अगर (copy_to_user(u_info, &info, माप(info)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

SYSCALL_DEFINE1(get_thपढ़ो_area, काष्ठा user_desc __user *, u_info)
अणु
	वापस करो_get_thपढ़ो_area(current, -1, u_info);
पूर्ण

पूर्णांक regset_tls_active(काष्ठा task_काष्ठा *target,
		      स्थिर काष्ठा user_regset *regset)
अणु
	काष्ठा thपढ़ो_काष्ठा *t = &target->thपढ़ो;
	पूर्णांक n = GDT_ENTRY_TLS_ENTRIES;
	जबतक (n > 0 && desc_empty(&t->tls_array[n - 1]))
		--n;
	वापस n;
पूर्ण

पूर्णांक regset_tls_get(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		   काष्ठा membuf to)
अणु
	स्थिर काष्ठा desc_काष्ठा *tls;
	काष्ठा user_desc v;
	पूर्णांक pos;

	क्रम (pos = 0, tls = target->thपढ़ो.tls_array; to.left; pos++, tls++) अणु
		fill_user_desc(&v, GDT_ENTRY_TLS_MIN + pos, tls);
		membuf_ग_लिखो(&to, &v, माप(v));
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक regset_tls_set(काष्ठा task_काष्ठा *target, स्थिर काष्ठा user_regset *regset,
		   अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
		   स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	काष्ठा user_desc infobuf[GDT_ENTRY_TLS_ENTRIES];
	स्थिर काष्ठा user_desc *info;
	पूर्णांक i;

	अगर (pos >= GDT_ENTRY_TLS_ENTRIES * माप(काष्ठा user_desc) ||
	    (pos % माप(काष्ठा user_desc)) != 0 ||
	    (count % माप(काष्ठा user_desc)) != 0)
		वापस -EINVAL;

	अगर (kbuf)
		info = kbuf;
	अन्यथा अगर (__copy_from_user(infobuf, ubuf, count))
		वापस -EFAULT;
	अन्यथा
		info = infobuf;

	क्रम (i = 0; i < count / माप(काष्ठा user_desc); i++)
		अगर (!tls_desc_okay(info + i))
			वापस -EINVAL;

	set_tls_desc(target,
		     GDT_ENTRY_TLS_MIN + (pos / माप(काष्ठा user_desc)),
		     info, count / माप(काष्ठा user_desc));

	वापस 0;
पूर्ण
