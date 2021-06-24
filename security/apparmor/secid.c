<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AppArmor security module
 *
 * This file contains AppArmor security identअगरier (secid) manipulation fns
 *
 * Copyright 2009-2017 Canonical Ltd.
 *
 * AppArmor allocates a unique secid क्रम every label used. If a label
 * is replaced it receives the secid of the label it is replacing.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/gfp.h>
#समावेश <linux/idr.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश "include/cred.h"
#समावेश "include/lib.h"
#समावेश "include/secid.h"
#समावेश "include/label.h"
#समावेश "include/policy_ns.h"

/*
 * secids - करो not pin labels with a refcount. They rely on the label
 * properly updating/मुक्तing them
 */
#घोषणा AA_FIRST_SECID 2

अटल DEFINE_IDR(aa_secids);
अटल DEFINE_SPINLOCK(secid_lock);

/*
 * TODO: allow policy to reserve a secid range?
 * TODO: add secid pinning
 * TODO: use secid_update in label replace
 */

/**
 * aa_secid_update - update a secid mapping to a new label
 * @secid: secid to update
 * @label: label the secid will now map to
 */
व्योम aa_secid_update(u32 secid, काष्ठा aa_label *label)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&secid_lock, flags);
	idr_replace(&aa_secids, label, secid);
	spin_unlock_irqrestore(&secid_lock, flags);
पूर्ण

/**
 *
 * see label क्रम inverse aa_label_to_secid
 */
काष्ठा aa_label *aa_secid_to_label(u32 secid)
अणु
	काष्ठा aa_label *label;

	rcu_पढ़ो_lock();
	label = idr_find(&aa_secids, secid);
	rcu_पढ़ो_unlock();

	वापस label;
पूर्ण

पूर्णांक apparmor_secid_to_secctx(u32 secid, अक्षर **secdata, u32 *seclen)
अणु
	/* TODO: cache secctx and ref count so we करोn't have to recreate */
	काष्ठा aa_label *label = aa_secid_to_label(secid);
	पूर्णांक len;

	AA_BUG(!seclen);

	अगर (!label)
		वापस -EINVAL;

	अगर (secdata)
		len = aa_label_asxprपूर्णांक(secdata, root_ns, label,
					FLAG_SHOW_MODE | FLAG_VIEW_SUBNS |
					FLAG_HIDDEN_UNCONFINED | FLAG_ABS_ROOT,
					GFP_ATOMIC);
	अन्यथा
		len = aa_label_snxprपूर्णांक(शून्य, 0, root_ns, label,
					FLAG_SHOW_MODE | FLAG_VIEW_SUBNS |
					FLAG_HIDDEN_UNCONFINED | FLAG_ABS_ROOT);
	अगर (len < 0)
		वापस -ENOMEM;

	*seclen = len;

	वापस 0;
पूर्ण

पूर्णांक apparmor_secctx_to_secid(स्थिर अक्षर *secdata, u32 seclen, u32 *secid)
अणु
	काष्ठा aa_label *label;

	label = aa_label_strn_parse(&root_ns->unconfined->label, secdata,
				    seclen, GFP_KERNEL, false, false);
	अगर (IS_ERR(label))
		वापस PTR_ERR(label);
	*secid = label->secid;

	वापस 0;
पूर्ण

व्योम apparmor_release_secctx(अक्षर *secdata, u32 seclen)
अणु
	kमुक्त(secdata);
पूर्ण

/**
 * aa_alloc_secid - allocate a new secid क्रम a profile
 * @label: the label to allocate a secid क्रम
 * @gfp: memory allocation flags
 *
 * Returns: 0 with @label->secid initialized
 *          <0 वापसs error with @label->secid set to AA_SECID_INVALID
 */
पूर्णांक aa_alloc_secid(काष्ठा aa_label *label, gfp_t gfp)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	idr_preload(gfp);
	spin_lock_irqsave(&secid_lock, flags);
	ret = idr_alloc(&aa_secids, label, AA_FIRST_SECID, 0, GFP_ATOMIC);
	spin_unlock_irqrestore(&secid_lock, flags);
	idr_preload_end();

	अगर (ret < 0) अणु
		label->secid = AA_SECID_INVALID;
		वापस ret;
	पूर्ण

	AA_BUG(ret == AA_SECID_INVALID);
	label->secid = ret;
	वापस 0;
पूर्ण

/**
 * aa_मुक्त_secid - मुक्त a secid
 * @secid: secid to मुक्त
 */
व्योम aa_मुक्त_secid(u32 secid)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&secid_lock, flags);
	idr_हटाओ(&aa_secids, secid);
	spin_unlock_irqrestore(&secid_lock, flags);
पूर्ण

व्योम aa_secids_init(व्योम)
अणु
	idr_init_base(&aa_secids, AA_FIRST_SECID);
पूर्ण
