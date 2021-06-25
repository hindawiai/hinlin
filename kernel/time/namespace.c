<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Author: Andrei Vagin <avagin@खोलोvz.org>
 * Author: Dmitry Safonov <dima@arista.com>
 */

#समावेश <linux/समय_namespace.h>
#समावेश <linux/user_namespace.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/task.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/proc_ns.h>
#समावेश <linux/export.h>
#समावेश <linux/समय.स>
#समावेश <linux/slab.h>
#समावेश <linux/cred.h>
#समावेश <linux/err.h>
#समावेश <linux/mm.h>

#समावेश <vdso/datapage.h>

kसमय_प्रकार करो_समयns_kसमय_प्रकारo_host(घड़ीid_t घड़ीid, kसमय_प्रकार tim,
				काष्ठा समयns_offsets *ns_offsets)
अणु
	kसमय_प्रकार offset;

	चयन (घड़ीid) अणु
	हाल CLOCK_MONOTONIC:
		offset = बारpec64_to_kसमय(ns_offsets->monotonic);
		अवरोध;
	हाल CLOCK_BOOTTIME:
	हाल CLOCK_BOOTTIME_ALARM:
		offset = बारpec64_to_kसमय(ns_offsets->bootसमय);
		अवरोध;
	शेष:
		वापस tim;
	पूर्ण

	/*
	 * Check that @tim value is in [offset, KTIME_MAX + offset]
	 * and subtract offset.
	 */
	अगर (tim < offset) अणु
		/*
		 * User can specअगरy @tim *असलolute* value - अगर it's lesser than
		 * the समय namespace's offset - it's alपढ़ोy expired.
		 */
		tim = 0;
	पूर्ण अन्यथा अणु
		tim = kसमय_sub(tim, offset);
		अगर (unlikely(tim > KTIME_MAX))
			tim = KTIME_MAX;
	पूर्ण

	वापस tim;
पूर्ण

अटल काष्ठा ucounts *inc_समय_namespaces(काष्ठा user_namespace *ns)
अणु
	वापस inc_ucount(ns, current_euid(), UCOUNT_TIME_NAMESPACES);
पूर्ण

अटल व्योम dec_समय_namespaces(काष्ठा ucounts *ucounts)
अणु
	dec_ucount(ucounts, UCOUNT_TIME_NAMESPACES);
पूर्ण

/**
 * clone_समय_ns - Clone a समय namespace
 * @user_ns:	User namespace which owns a new namespace.
 * @old_ns:	Namespace to clone
 *
 * Clone @old_ns and set the clone refcount to 1
 *
 * Return: The new namespace or ERR_PTR.
 */
अटल काष्ठा समय_namespace *clone_समय_ns(काष्ठा user_namespace *user_ns,
					  काष्ठा समय_namespace *old_ns)
अणु
	काष्ठा समय_namespace *ns;
	काष्ठा ucounts *ucounts;
	पूर्णांक err;

	err = -ENOSPC;
	ucounts = inc_समय_namespaces(user_ns);
	अगर (!ucounts)
		जाओ fail;

	err = -ENOMEM;
	ns = kदो_स्मृति(माप(*ns), GFP_KERNEL);
	अगर (!ns)
		जाओ fail_dec;

	refcount_set(&ns->ns.count, 1);

	ns->vvar_page = alloc_page(GFP_KERNEL | __GFP_ZERO);
	अगर (!ns->vvar_page)
		जाओ fail_मुक्त;

	err = ns_alloc_inum(&ns->ns);
	अगर (err)
		जाओ fail_मुक्त_page;

	ns->ucounts = ucounts;
	ns->ns.ops = &समयns_operations;
	ns->user_ns = get_user_ns(user_ns);
	ns->offsets = old_ns->offsets;
	ns->frozen_offsets = false;
	वापस ns;

fail_मुक्त_page:
	__मुक्त_page(ns->vvar_page);
fail_मुक्त:
	kमुक्त(ns);
fail_dec:
	dec_समय_namespaces(ucounts);
fail:
	वापस ERR_PTR(err);
पूर्ण

/**
 * copy_समय_ns - Create समयns_क्रम_children from @old_ns
 * @flags:	Cloning flags
 * @user_ns:	User namespace which owns a new namespace.
 * @old_ns:	Namespace to clone
 *
 * If CLONE_NEWTIME specअगरied in @flags, creates a new समयns_क्रम_children;
 * adds a refcounter to @old_ns otherwise.
 *
 * Return: समयns_क्रम_children namespace or ERR_PTR.
 */
काष्ठा समय_namespace *copy_समय_ns(अचिन्हित दीर्घ flags,
	काष्ठा user_namespace *user_ns, काष्ठा समय_namespace *old_ns)
अणु
	अगर (!(flags & CLONE_NEWTIME))
		वापस get_समय_ns(old_ns);

	वापस clone_समय_ns(user_ns, old_ns);
पूर्ण

अटल काष्ठा समयns_offset offset_from_ts(काष्ठा बारpec64 off)
अणु
	काष्ठा समयns_offset ret;

	ret.sec = off.tv_sec;
	ret.nsec = off.tv_nsec;

	वापस ret;
पूर्ण

/*
 * A समय namespace VVAR page has the same layout as the VVAR page which
 * contains the प्रणाली wide VDSO data.
 *
 * For a normal task the VVAR pages are installed in the normal ordering:
 *     VVAR
 *     PVCLOCK
 *     HVCLOCK
 *     TIMENS   <- Not really required
 *
 * Now क्रम a समयns task the pages are installed in the following order:
 *     TIMENS
 *     PVCLOCK
 *     HVCLOCK
 *     VVAR
 *
 * The check क्रम vdso_data->घड़ी_mode is in the unlikely path of
 * the seq begin magic. So क्रम the non-समयns हाल most of the समय
 * 'seq' is even, so the branch is not taken.
 *
 * If 'seq' is odd, i.e. a concurrent update is in progress, the extra check
 * क्रम vdso_data->घड़ी_mode is a non-issue. The task is spin रुकोing क्रम the
 * update to finish and क्रम 'seq' to become even anyway.
 *
 * Timens page has vdso_data->घड़ी_mode set to VDSO_CLOCKMODE_TIMENS which
 * enक्रमces the समय namespace handling path.
 */
अटल व्योम समयns_setup_vdso_data(काष्ठा vdso_data *vdata,
				   काष्ठा समय_namespace *ns)
अणु
	काष्ठा समयns_offset *offset = vdata->offset;
	काष्ठा समयns_offset monotonic = offset_from_ts(ns->offsets.monotonic);
	काष्ठा समयns_offset bootसमय = offset_from_ts(ns->offsets.bootसमय);

	vdata->seq			= 1;
	vdata->घड़ी_mode		= VDSO_CLOCKMODE_TIMENS;
	offset[CLOCK_MONOTONIC]		= monotonic;
	offset[CLOCK_MONOTONIC_RAW]	= monotonic;
	offset[CLOCK_MONOTONIC_COARSE]	= monotonic;
	offset[CLOCK_BOOTTIME]		= bootसमय;
	offset[CLOCK_BOOTTIME_ALARM]	= bootसमय;
पूर्ण

/*
 * Protects possibly multiple offsets ग_लिखोrs racing each other
 * and tasks entering the namespace.
 */
अटल DEFINE_MUTEX(offset_lock);

अटल व्योम समयns_set_vvar_page(काष्ठा task_काष्ठा *task,
				काष्ठा समय_namespace *ns)
अणु
	काष्ठा vdso_data *vdata;
	अचिन्हित पूर्णांक i;

	अगर (ns == &init_समय_ns)
		वापस;

	/* Fast-path, taken by every task in namespace except the first. */
	अगर (likely(ns->frozen_offsets))
		वापस;

	mutex_lock(&offset_lock);
	/* Nothing to-करो: vvar_page has been alपढ़ोy initialized. */
	अगर (ns->frozen_offsets)
		जाओ out;

	ns->frozen_offsets = true;
	vdata = arch_get_vdso_data(page_address(ns->vvar_page));

	क्रम (i = 0; i < CS_BASES; i++)
		समयns_setup_vdso_data(&vdata[i], ns);

out:
	mutex_unlock(&offset_lock);
पूर्ण

व्योम मुक्त_समय_ns(काष्ठा समय_namespace *ns)
अणु
	dec_समय_namespaces(ns->ucounts);
	put_user_ns(ns->user_ns);
	ns_मुक्त_inum(&ns->ns);
	__मुक्त_page(ns->vvar_page);
	kमुक्त(ns);
पूर्ण

अटल काष्ठा समय_namespace *to_समय_ns(काष्ठा ns_common *ns)
अणु
	वापस container_of(ns, काष्ठा समय_namespace, ns);
पूर्ण

अटल काष्ठा ns_common *समयns_get(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा समय_namespace *ns = शून्य;
	काष्ठा nsproxy *nsproxy;

	task_lock(task);
	nsproxy = task->nsproxy;
	अगर (nsproxy) अणु
		ns = nsproxy->समय_ns;
		get_समय_ns(ns);
	पूर्ण
	task_unlock(task);

	वापस ns ? &ns->ns : शून्य;
पूर्ण

अटल काष्ठा ns_common *समयns_क्रम_children_get(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा समय_namespace *ns = शून्य;
	काष्ठा nsproxy *nsproxy;

	task_lock(task);
	nsproxy = task->nsproxy;
	अगर (nsproxy) अणु
		ns = nsproxy->समय_ns_क्रम_children;
		get_समय_ns(ns);
	पूर्ण
	task_unlock(task);

	वापस ns ? &ns->ns : शून्य;
पूर्ण

अटल व्योम समयns_put(काष्ठा ns_common *ns)
अणु
	put_समय_ns(to_समय_ns(ns));
पूर्ण

व्योम समयns_commit(काष्ठा task_काष्ठा *tsk, काष्ठा समय_namespace *ns)
अणु
	समयns_set_vvar_page(tsk, ns);
	vdso_join_समयns(tsk, ns);
पूर्ण

अटल पूर्णांक समयns_install(काष्ठा nsset *nsset, काष्ठा ns_common *new)
अणु
	काष्ठा nsproxy *nsproxy = nsset->nsproxy;
	काष्ठा समय_namespace *ns = to_समय_ns(new);

	अगर (!current_is_single_thपढ़ोed())
		वापस -EUSERS;

	अगर (!ns_capable(ns->user_ns, CAP_SYS_ADMIN) ||
	    !ns_capable(nsset->cred->user_ns, CAP_SYS_ADMIN))
		वापस -EPERM;

	get_समय_ns(ns);
	put_समय_ns(nsproxy->समय_ns);
	nsproxy->समय_ns = ns;

	get_समय_ns(ns);
	put_समय_ns(nsproxy->समय_ns_क्रम_children);
	nsproxy->समय_ns_क्रम_children = ns;
	वापस 0;
पूर्ण

व्योम समयns_on_विभाजन(काष्ठा nsproxy *nsproxy, काष्ठा task_काष्ठा *tsk)
अणु
	काष्ठा ns_common *nsc = &nsproxy->समय_ns_क्रम_children->ns;
	काष्ठा समय_namespace *ns = to_समय_ns(nsc);

	/* create_new_namespaces() alपढ़ोy incremented the ref counter */
	अगर (nsproxy->समय_ns == nsproxy->समय_ns_क्रम_children)
		वापस;

	get_समय_ns(ns);
	put_समय_ns(nsproxy->समय_ns);
	nsproxy->समय_ns = ns;

	समयns_commit(tsk, ns);
पूर्ण

अटल काष्ठा user_namespace *समयns_owner(काष्ठा ns_common *ns)
अणु
	वापस to_समय_ns(ns)->user_ns;
पूर्ण

अटल व्योम show_offset(काष्ठा seq_file *m, पूर्णांक घड़ीid, काष्ठा बारpec64 *ts)
अणु
	अक्षर *घड़ी;

	चयन (घड़ीid) अणु
	हाल CLOCK_BOOTTIME:
		घड़ी = "boottime";
		अवरोध;
	हाल CLOCK_MONOTONIC:
		घड़ी = "monotonic";
		अवरोध;
	शेष:
		घड़ी = "unknown";
		अवरोध;
	पूर्ण
	seq_म_लिखो(m, "%-10s %10lld %9ld\n", घड़ी, ts->tv_sec, ts->tv_nsec);
पूर्ण

व्योम proc_समयns_show_offsets(काष्ठा task_काष्ठा *p, काष्ठा seq_file *m)
अणु
	काष्ठा ns_common *ns;
	काष्ठा समय_namespace *समय_ns;

	ns = समयns_क्रम_children_get(p);
	अगर (!ns)
		वापस;
	समय_ns = to_समय_ns(ns);

	show_offset(m, CLOCK_MONOTONIC, &समय_ns->offsets.monotonic);
	show_offset(m, CLOCK_BOOTTIME, &समय_ns->offsets.bootसमय);
	put_समय_ns(समय_ns);
पूर्ण

पूर्णांक proc_समयns_set_offset(काष्ठा file *file, काष्ठा task_काष्ठा *p,
			   काष्ठा proc_समयns_offset *offsets, पूर्णांक noffsets)
अणु
	काष्ठा ns_common *ns;
	काष्ठा समय_namespace *समय_ns;
	काष्ठा बारpec64 tp;
	पूर्णांक i, err;

	ns = समयns_क्रम_children_get(p);
	अगर (!ns)
		वापस -ESRCH;
	समय_ns = to_समय_ns(ns);

	अगर (!file_ns_capable(file, समय_ns->user_ns, CAP_SYS_TIME)) अणु
		put_समय_ns(समय_ns);
		वापस -EPERM;
	पूर्ण

	क्रम (i = 0; i < noffsets; i++) अणु
		काष्ठा proc_समयns_offset *off = &offsets[i];

		चयन (off->घड़ीid) अणु
		हाल CLOCK_MONOTONIC:
			kसमय_get_ts64(&tp);
			अवरोध;
		हाल CLOCK_BOOTTIME:
			kसमय_get_bootसमय_प्रकारs64(&tp);
			अवरोध;
		शेष:
			err = -EINVAL;
			जाओ out;
		पूर्ण

		err = -दुस्फल;

		अगर (off->val.tv_sec > KTIME_SEC_MAX ||
		    off->val.tv_sec < -KTIME_SEC_MAX)
			जाओ out;

		tp = बारpec64_add(tp, off->val);
		/*
		 * KTIME_SEC_MAX is भागided by 2 to be sure that KTIME_MAX is
		 * still unreachable.
		 */
		अगर (tp.tv_sec < 0 || tp.tv_sec > KTIME_SEC_MAX / 2)
			जाओ out;
	पूर्ण

	mutex_lock(&offset_lock);
	अगर (समय_ns->frozen_offsets) अणु
		err = -EACCES;
		जाओ out_unlock;
	पूर्ण

	err = 0;
	/* Don't report errors after this line */
	क्रम (i = 0; i < noffsets; i++) अणु
		काष्ठा proc_समयns_offset *off = &offsets[i];
		काष्ठा बारpec64 *offset = शून्य;

		चयन (off->घड़ीid) अणु
		हाल CLOCK_MONOTONIC:
			offset = &समय_ns->offsets.monotonic;
			अवरोध;
		हाल CLOCK_BOOTTIME:
			offset = &समय_ns->offsets.bootसमय;
			अवरोध;
		पूर्ण

		*offset = off->val;
	पूर्ण

out_unlock:
	mutex_unlock(&offset_lock);
out:
	put_समय_ns(समय_ns);

	वापस err;
पूर्ण

स्थिर काष्ठा proc_ns_operations समयns_operations = अणु
	.name		= "time",
	.type		= CLONE_NEWTIME,
	.get		= समयns_get,
	.put		= समयns_put,
	.install	= समयns_install,
	.owner		= समयns_owner,
पूर्ण;

स्थिर काष्ठा proc_ns_operations समयns_क्रम_children_operations = अणु
	.name		= "time_for_children",
	.real_ns_name	= "time",
	.type		= CLONE_NEWTIME,
	.get		= समयns_क्रम_children_get,
	.put		= समयns_put,
	.install	= समयns_install,
	.owner		= समयns_owner,
पूर्ण;

काष्ठा समय_namespace init_समय_ns = अणु
	.ns.count	= REFCOUNT_INIT(3),
	.user_ns	= &init_user_ns,
	.ns.inum	= PROC_TIME_INIT_INO,
	.ns.ops		= &समयns_operations,
	.frozen_offsets	= true,
पूर्ण;
