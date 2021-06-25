<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/kdebug.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/export.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/reboot.h>

/*
 *	Notअगरier list क्रम kernel code which wants to be called
 *	at shutकरोwn. This is used to stop any idling DMA operations
 *	and the like.
 */
BLOCKING_NOTIFIER_HEAD(reboot_notअगरier_list);

/*
 *	Notअगरier chain core routines.  The exported routines below
 *	are layered on top of these, with appropriate locking added.
 */

अटल पूर्णांक notअगरier_chain_रेजिस्टर(काष्ठा notअगरier_block **nl,
		काष्ठा notअगरier_block *n)
अणु
	जबतक ((*nl) != शून्य) अणु
		अगर (unlikely((*nl) == n)) अणु
			WARN(1, "double register detected");
			वापस 0;
		पूर्ण
		अगर (n->priority > (*nl)->priority)
			अवरोध;
		nl = &((*nl)->next);
	पूर्ण
	n->next = *nl;
	rcu_assign_poपूर्णांकer(*nl, n);
	वापस 0;
पूर्ण

अटल पूर्णांक notअगरier_chain_unरेजिस्टर(काष्ठा notअगरier_block **nl,
		काष्ठा notअगरier_block *n)
अणु
	जबतक ((*nl) != शून्य) अणु
		अगर ((*nl) == n) अणु
			rcu_assign_poपूर्णांकer(*nl, n->next);
			वापस 0;
		पूर्ण
		nl = &((*nl)->next);
	पूर्ण
	वापस -ENOENT;
पूर्ण

/**
 * notअगरier_call_chain - Inक्रमms the रेजिस्टरed notअगरiers about an event.
 *	@nl:		Poपूर्णांकer to head of the blocking notअगरier chain
 *	@val:		Value passed unmodअगरied to notअगरier function
 *	@v:		Poपूर्णांकer passed unmodअगरied to notअगरier function
 *	@nr_to_call:	Number of notअगरier functions to be called. Don't care
 *			value of this parameter is -1.
 *	@nr_calls:	Records the number of notअगरications sent. Don't care
 *			value of this field is शून्य.
 *	@वापसs:	notअगरier_call_chain वापसs the value वापसed by the
 *			last notअगरier function called.
 */
अटल पूर्णांक notअगरier_call_chain(काष्ठा notअगरier_block **nl,
			       अचिन्हित दीर्घ val, व्योम *v,
			       पूर्णांक nr_to_call, पूर्णांक *nr_calls)
अणु
	पूर्णांक ret = NOTIFY_DONE;
	काष्ठा notअगरier_block *nb, *next_nb;

	nb = rcu_dereference_raw(*nl);

	जबतक (nb && nr_to_call) अणु
		next_nb = rcu_dereference_raw(nb->next);

#अगर_घोषित CONFIG_DEBUG_NOTIFIERS
		अगर (unlikely(!func_ptr_is_kernel_text(nb->notअगरier_call))) अणु
			WARN(1, "Invalid notifier called!");
			nb = next_nb;
			जारी;
		पूर्ण
#पूर्ण_अगर
		ret = nb->notअगरier_call(nb, val, v);

		अगर (nr_calls)
			(*nr_calls)++;

		अगर (ret & NOTIFY_STOP_MASK)
			अवरोध;
		nb = next_nb;
		nr_to_call--;
	पूर्ण
	वापस ret;
पूर्ण
NOKPROBE_SYMBOL(notअगरier_call_chain);

/**
 * notअगरier_call_chain_robust - Inक्रमm the रेजिस्टरed notअगरiers about an event
 *                              and rollback on error.
 * @nl:		Poपूर्णांकer to head of the blocking notअगरier chain
 * @val_up:	Value passed unmodअगरied to the notअगरier function
 * @val_करोwn:	Value passed unmodअगरied to the notअगरier function when recovering
 *              from an error on @val_up
 * @v		Poपूर्णांकer passed unmodअगरied to the notअगरier function
 *
 * NOTE:	It is important the @nl chain करोesn't change between the two
 *		invocations of notअगरier_call_chain() such that we visit the
 *		exact same notअगरier callbacks; this rules out any RCU usage.
 *
 * Returns:	the वापस value of the @val_up call.
 */
अटल पूर्णांक notअगरier_call_chain_robust(काष्ठा notअगरier_block **nl,
				     अचिन्हित दीर्घ val_up, अचिन्हित दीर्घ val_करोwn,
				     व्योम *v)
अणु
	पूर्णांक ret, nr = 0;

	ret = notअगरier_call_chain(nl, val_up, v, -1, &nr);
	अगर (ret & NOTIFY_STOP_MASK)
		notअगरier_call_chain(nl, val_करोwn, v, nr-1, शून्य);

	वापस ret;
पूर्ण

/*
 *	Atomic notअगरier chain routines.  Registration and unregistration
 *	use a spinlock, and call_chain is synchronized by RCU (no locks).
 */

/**
 *	atomic_notअगरier_chain_रेजिस्टर - Add notअगरier to an atomic notअगरier chain
 *	@nh: Poपूर्णांकer to head of the atomic notअगरier chain
 *	@n: New entry in notअगरier chain
 *
 *	Adds a notअगरier to an atomic notअगरier chain.
 *
 *	Currently always वापसs zero.
 */
पूर्णांक atomic_notअगरier_chain_रेजिस्टर(काष्ठा atomic_notअगरier_head *nh,
		काष्ठा notअगरier_block *n)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&nh->lock, flags);
	ret = notअगरier_chain_रेजिस्टर(&nh->head, n);
	spin_unlock_irqrestore(&nh->lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(atomic_notअगरier_chain_रेजिस्टर);

/**
 *	atomic_notअगरier_chain_unरेजिस्टर - Remove notअगरier from an atomic notअगरier chain
 *	@nh: Poपूर्णांकer to head of the atomic notअगरier chain
 *	@n: Entry to हटाओ from notअगरier chain
 *
 *	Removes a notअगरier from an atomic notअगरier chain.
 *
 *	Returns zero on success or %-ENOENT on failure.
 */
पूर्णांक atomic_notअगरier_chain_unरेजिस्टर(काष्ठा atomic_notअगरier_head *nh,
		काष्ठा notअगरier_block *n)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&nh->lock, flags);
	ret = notअगरier_chain_unरेजिस्टर(&nh->head, n);
	spin_unlock_irqrestore(&nh->lock, flags);
	synchronize_rcu();
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(atomic_notअगरier_chain_unरेजिस्टर);

पूर्णांक atomic_notअगरier_call_chain_robust(काष्ठा atomic_notअगरier_head *nh,
		अचिन्हित दीर्घ val_up, अचिन्हित दीर्घ val_करोwn, व्योम *v)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/*
	 * Musn't use RCU; because then the notअगरier list can
	 * change between the up and करोwn traversal.
	 */
	spin_lock_irqsave(&nh->lock, flags);
	ret = notअगरier_call_chain_robust(&nh->head, val_up, val_करोwn, v);
	spin_unlock_irqrestore(&nh->lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(atomic_notअगरier_call_chain_robust);
NOKPROBE_SYMBOL(atomic_notअगरier_call_chain_robust);

/**
 *	atomic_notअगरier_call_chain - Call functions in an atomic notअगरier chain
 *	@nh: Poपूर्णांकer to head of the atomic notअगरier chain
 *	@val: Value passed unmodअगरied to notअगरier function
 *	@v: Poपूर्णांकer passed unmodअगरied to notअगरier function
 *
 *	Calls each function in a notअगरier chain in turn.  The functions
 *	run in an atomic context, so they must not block.
 *	This routine uses RCU to synchronize with changes to the chain.
 *
 *	If the वापस value of the notअगरier can be and'ed
 *	with %NOTIFY_STOP_MASK then atomic_notअगरier_call_chain()
 *	will वापस immediately, with the वापस value of
 *	the notअगरier function which halted execution.
 *	Otherwise the वापस value is the वापस value
 *	of the last notअगरier function called.
 */
पूर्णांक atomic_notअगरier_call_chain(काष्ठा atomic_notअगरier_head *nh,
			       अचिन्हित दीर्घ val, व्योम *v)
अणु
	पूर्णांक ret;

	rcu_पढ़ो_lock();
	ret = notअगरier_call_chain(&nh->head, val, v, -1, शून्य);
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(atomic_notअगरier_call_chain);
NOKPROBE_SYMBOL(atomic_notअगरier_call_chain);

/*
 *	Blocking notअगरier chain routines.  All access to the chain is
 *	synchronized by an rwsem.
 */

/**
 *	blocking_notअगरier_chain_रेजिस्टर - Add notअगरier to a blocking notअगरier chain
 *	@nh: Poपूर्णांकer to head of the blocking notअगरier chain
 *	@n: New entry in notअगरier chain
 *
 *	Adds a notअगरier to a blocking notअगरier chain.
 *	Must be called in process context.
 *
 *	Currently always वापसs zero.
 */
पूर्णांक blocking_notअगरier_chain_रेजिस्टर(काष्ठा blocking_notअगरier_head *nh,
		काष्ठा notअगरier_block *n)
अणु
	पूर्णांक ret;

	/*
	 * This code माला_लो used during boot-up, when task चयनing is
	 * not yet working and पूर्णांकerrupts must reमुख्य disabled.  At
	 * such बार we must not call करोwn_ग_लिखो().
	 */
	अगर (unlikely(प्रणाली_state == SYSTEM_BOOTING))
		वापस notअगरier_chain_रेजिस्टर(&nh->head, n);

	करोwn_ग_लिखो(&nh->rwsem);
	ret = notअगरier_chain_रेजिस्टर(&nh->head, n);
	up_ग_लिखो(&nh->rwsem);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(blocking_notअगरier_chain_रेजिस्टर);

/**
 *	blocking_notअगरier_chain_unरेजिस्टर - Remove notअगरier from a blocking notअगरier chain
 *	@nh: Poपूर्णांकer to head of the blocking notअगरier chain
 *	@n: Entry to हटाओ from notअगरier chain
 *
 *	Removes a notअगरier from a blocking notअगरier chain.
 *	Must be called from process context.
 *
 *	Returns zero on success or %-ENOENT on failure.
 */
पूर्णांक blocking_notअगरier_chain_unरेजिस्टर(काष्ठा blocking_notअगरier_head *nh,
		काष्ठा notअगरier_block *n)
अणु
	पूर्णांक ret;

	/*
	 * This code माला_लो used during boot-up, when task चयनing is
	 * not yet working and पूर्णांकerrupts must reमुख्य disabled.  At
	 * such बार we must not call करोwn_ग_लिखो().
	 */
	अगर (unlikely(प्रणाली_state == SYSTEM_BOOTING))
		वापस notअगरier_chain_unरेजिस्टर(&nh->head, n);

	करोwn_ग_लिखो(&nh->rwsem);
	ret = notअगरier_chain_unरेजिस्टर(&nh->head, n);
	up_ग_लिखो(&nh->rwsem);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(blocking_notअगरier_chain_unरेजिस्टर);

पूर्णांक blocking_notअगरier_call_chain_robust(काष्ठा blocking_notअगरier_head *nh,
		अचिन्हित दीर्घ val_up, अचिन्हित दीर्घ val_करोwn, व्योम *v)
अणु
	पूर्णांक ret = NOTIFY_DONE;

	/*
	 * We check the head outside the lock, but अगर this access is
	 * racy then it करोes not matter what the result of the test
	 * is, we re-check the list after having taken the lock anyway:
	 */
	अगर (rcu_access_poपूर्णांकer(nh->head)) अणु
		करोwn_पढ़ो(&nh->rwsem);
		ret = notअगरier_call_chain_robust(&nh->head, val_up, val_करोwn, v);
		up_पढ़ो(&nh->rwsem);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(blocking_notअगरier_call_chain_robust);

/**
 *	blocking_notअगरier_call_chain - Call functions in a blocking notअगरier chain
 *	@nh: Poपूर्णांकer to head of the blocking notअगरier chain
 *	@val: Value passed unmodअगरied to notअगरier function
 *	@v: Poपूर्णांकer passed unmodअगरied to notअगरier function
 *
 *	Calls each function in a notअगरier chain in turn.  The functions
 *	run in a process context, so they are allowed to block.
 *
 *	If the वापस value of the notअगरier can be and'ed
 *	with %NOTIFY_STOP_MASK then blocking_notअगरier_call_chain()
 *	will वापस immediately, with the वापस value of
 *	the notअगरier function which halted execution.
 *	Otherwise the वापस value is the वापस value
 *	of the last notअगरier function called.
 */
पूर्णांक blocking_notअगरier_call_chain(काष्ठा blocking_notअगरier_head *nh,
		अचिन्हित दीर्घ val, व्योम *v)
अणु
	पूर्णांक ret = NOTIFY_DONE;

	/*
	 * We check the head outside the lock, but अगर this access is
	 * racy then it करोes not matter what the result of the test
	 * is, we re-check the list after having taken the lock anyway:
	 */
	अगर (rcu_access_poपूर्णांकer(nh->head)) अणु
		करोwn_पढ़ो(&nh->rwsem);
		ret = notअगरier_call_chain(&nh->head, val, v, -1, शून्य);
		up_पढ़ो(&nh->rwsem);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(blocking_notअगरier_call_chain);

/*
 *	Raw notअगरier chain routines.  There is no protection;
 *	the caller must provide it.  Use at your own risk!
 */

/**
 *	raw_notअगरier_chain_रेजिस्टर - Add notअगरier to a raw notअगरier chain
 *	@nh: Poपूर्णांकer to head of the raw notअगरier chain
 *	@n: New entry in notअगरier chain
 *
 *	Adds a notअगरier to a raw notअगरier chain.
 *	All locking must be provided by the caller.
 *
 *	Currently always वापसs zero.
 */
पूर्णांक raw_notअगरier_chain_रेजिस्टर(काष्ठा raw_notअगरier_head *nh,
		काष्ठा notअगरier_block *n)
अणु
	वापस notअगरier_chain_रेजिस्टर(&nh->head, n);
पूर्ण
EXPORT_SYMBOL_GPL(raw_notअगरier_chain_रेजिस्टर);

/**
 *	raw_notअगरier_chain_unरेजिस्टर - Remove notअगरier from a raw notअगरier chain
 *	@nh: Poपूर्णांकer to head of the raw notअगरier chain
 *	@n: Entry to हटाओ from notअगरier chain
 *
 *	Removes a notअगरier from a raw notअगरier chain.
 *	All locking must be provided by the caller.
 *
 *	Returns zero on success or %-ENOENT on failure.
 */
पूर्णांक raw_notअगरier_chain_unरेजिस्टर(काष्ठा raw_notअगरier_head *nh,
		काष्ठा notअगरier_block *n)
अणु
	वापस notअगरier_chain_unरेजिस्टर(&nh->head, n);
पूर्ण
EXPORT_SYMBOL_GPL(raw_notअगरier_chain_unरेजिस्टर);

पूर्णांक raw_notअगरier_call_chain_robust(काष्ठा raw_notअगरier_head *nh,
		अचिन्हित दीर्घ val_up, अचिन्हित दीर्घ val_करोwn, व्योम *v)
अणु
	वापस notअगरier_call_chain_robust(&nh->head, val_up, val_करोwn, v);
पूर्ण
EXPORT_SYMBOL_GPL(raw_notअगरier_call_chain_robust);

/**
 *	raw_notअगरier_call_chain - Call functions in a raw notअगरier chain
 *	@nh: Poपूर्णांकer to head of the raw notअगरier chain
 *	@val: Value passed unmodअगरied to notअगरier function
 *	@v: Poपूर्णांकer passed unmodअगरied to notअगरier function
 *
 *	Calls each function in a notअगरier chain in turn.  The functions
 *	run in an undefined context.
 *	All locking must be provided by the caller.
 *
 *	If the वापस value of the notअगरier can be and'ed
 *	with %NOTIFY_STOP_MASK then raw_notअगरier_call_chain()
 *	will वापस immediately, with the वापस value of
 *	the notअगरier function which halted execution.
 *	Otherwise the वापस value is the वापस value
 *	of the last notअगरier function called.
 */
पूर्णांक raw_notअगरier_call_chain(काष्ठा raw_notअगरier_head *nh,
		अचिन्हित दीर्घ val, व्योम *v)
अणु
	वापस notअगरier_call_chain(&nh->head, val, v, -1, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(raw_notअगरier_call_chain);

#अगर_घोषित CONFIG_SRCU
/*
 *	SRCU notअगरier chain routines.    Registration and unregistration
 *	use a mutex, and call_chain is synchronized by SRCU (no locks).
 */

/**
 *	srcu_notअगरier_chain_रेजिस्टर - Add notअगरier to an SRCU notअगरier chain
 *	@nh: Poपूर्णांकer to head of the SRCU notअगरier chain
 *	@n: New entry in notअगरier chain
 *
 *	Adds a notअगरier to an SRCU notअगरier chain.
 *	Must be called in process context.
 *
 *	Currently always वापसs zero.
 */
पूर्णांक srcu_notअगरier_chain_रेजिस्टर(काष्ठा srcu_notअगरier_head *nh,
		काष्ठा notअगरier_block *n)
अणु
	पूर्णांक ret;

	/*
	 * This code माला_लो used during boot-up, when task चयनing is
	 * not yet working and पूर्णांकerrupts must reमुख्य disabled.  At
	 * such बार we must not call mutex_lock().
	 */
	अगर (unlikely(प्रणाली_state == SYSTEM_BOOTING))
		वापस notअगरier_chain_रेजिस्टर(&nh->head, n);

	mutex_lock(&nh->mutex);
	ret = notअगरier_chain_रेजिस्टर(&nh->head, n);
	mutex_unlock(&nh->mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(srcu_notअगरier_chain_रेजिस्टर);

/**
 *	srcu_notअगरier_chain_unरेजिस्टर - Remove notअगरier from an SRCU notअगरier chain
 *	@nh: Poपूर्णांकer to head of the SRCU notअगरier chain
 *	@n: Entry to हटाओ from notअगरier chain
 *
 *	Removes a notअगरier from an SRCU notअगरier chain.
 *	Must be called from process context.
 *
 *	Returns zero on success or %-ENOENT on failure.
 */
पूर्णांक srcu_notअगरier_chain_unरेजिस्टर(काष्ठा srcu_notअगरier_head *nh,
		काष्ठा notअगरier_block *n)
अणु
	पूर्णांक ret;

	/*
	 * This code माला_लो used during boot-up, when task चयनing is
	 * not yet working and पूर्णांकerrupts must reमुख्य disabled.  At
	 * such बार we must not call mutex_lock().
	 */
	अगर (unlikely(प्रणाली_state == SYSTEM_BOOTING))
		वापस notअगरier_chain_unरेजिस्टर(&nh->head, n);

	mutex_lock(&nh->mutex);
	ret = notअगरier_chain_unरेजिस्टर(&nh->head, n);
	mutex_unlock(&nh->mutex);
	synchronize_srcu(&nh->srcu);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(srcu_notअगरier_chain_unरेजिस्टर);

/**
 *	srcu_notअगरier_call_chain - Call functions in an SRCU notअगरier chain
 *	@nh: Poपूर्णांकer to head of the SRCU notअगरier chain
 *	@val: Value passed unmodअगरied to notअगरier function
 *	@v: Poपूर्णांकer passed unmodअगरied to notअगरier function
 *
 *	Calls each function in a notअगरier chain in turn.  The functions
 *	run in a process context, so they are allowed to block.
 *
 *	If the वापस value of the notअगरier can be and'ed
 *	with %NOTIFY_STOP_MASK then srcu_notअगरier_call_chain()
 *	will वापस immediately, with the वापस value of
 *	the notअगरier function which halted execution.
 *	Otherwise the वापस value is the वापस value
 *	of the last notअगरier function called.
 */
पूर्णांक srcu_notअगरier_call_chain(काष्ठा srcu_notअगरier_head *nh,
		अचिन्हित दीर्घ val, व्योम *v)
अणु
	पूर्णांक ret;
	पूर्णांक idx;

	idx = srcu_पढ़ो_lock(&nh->srcu);
	ret = notअगरier_call_chain(&nh->head, val, v, -1, शून्य);
	srcu_पढ़ो_unlock(&nh->srcu, idx);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(srcu_notअगरier_call_chain);

/**
 *	srcu_init_notअगरier_head - Initialize an SRCU notअगरier head
 *	@nh: Poपूर्णांकer to head of the srcu notअगरier chain
 *
 *	Unlike other sorts of notअगरier heads, SRCU notअगरier heads require
 *	dynamic initialization.  Be sure to call this routine beक्रमe
 *	calling any of the other SRCU notअगरier routines क्रम this head.
 *
 *	If an SRCU notअगरier head is deallocated, it must first be cleaned
 *	up by calling srcu_cleanup_notअगरier_head().  Otherwise the head's
 *	per-cpu data (used by the SRCU mechanism) will leak.
 */
व्योम srcu_init_notअगरier_head(काष्ठा srcu_notअगरier_head *nh)
अणु
	mutex_init(&nh->mutex);
	अगर (init_srcu_काष्ठा(&nh->srcu) < 0)
		BUG();
	nh->head = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(srcu_init_notअगरier_head);

#पूर्ण_अगर /* CONFIG_SRCU */

अटल ATOMIC_NOTIFIER_HEAD(die_chain);

पूर्णांक notrace notअगरy_die(क्रमागत die_val val, स्थिर अक्षर *str,
	       काष्ठा pt_regs *regs, दीर्घ err, पूर्णांक trap, पूर्णांक sig)
अणु
	काष्ठा die_args args = अणु
		.regs	= regs,
		.str	= str,
		.err	= err,
		.trapnr	= trap,
		.signr	= sig,

	पूर्ण;
	RCU_LOCKDEP_WARN(!rcu_is_watching(),
			   "notify_die called but RCU thinks we're quiescent");
	वापस atomic_notअगरier_call_chain(&die_chain, val, &args);
पूर्ण
NOKPROBE_SYMBOL(notअगरy_die);

पूर्णांक रेजिस्टर_die_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस atomic_notअगरier_chain_रेजिस्टर(&die_chain, nb);
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_die_notअगरier);

पूर्णांक unरेजिस्टर_die_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस atomic_notअगरier_chain_unरेजिस्टर(&die_chain, nb);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_die_notअगरier);
