<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * shaकरोw.c - Shaकरोw Variables
 *
 * Copyright (C) 2014 Josh Poimboeuf <jpoimboe@redhat.com>
 * Copyright (C) 2014 Seth Jennings <sjenning@redhat.com>
 * Copyright (C) 2017 Joe Lawrence <joe.lawrence@redhat.com>
 */

/**
 * DOC: Shaकरोw variable API concurrency notes:
 *
 * The shaकरोw variable API provides a simple relationship between an
 * <obj, id> pair and a poपूर्णांकer value.  It is the responsibility of the
 * caller to provide any mutual exclusion required of the shaकरोw data.
 *
 * Once a shaकरोw variable is attached to its parent object via the
 * klp_shaकरोw_*alloc() API calls, it is considered live: any subsequent
 * call to klp_shaकरोw_get() may then वापस the shaकरोw variable's data
 * poपूर्णांकer.  Callers of klp_shaकरोw_*alloc() should prepare shaकरोw data
 * accordingly.
 *
 * The klp_shaकरोw_*alloc() API calls may allocate memory क्रम new shaकरोw
 * variable काष्ठाures.  Their implementation करोes not call kदो_स्मृति
 * inside any spinlocks, but API callers should pass GFP flags according
 * to their specअगरic needs.
 *
 * The klp_shaकरोw_hash is an RCU-enabled hashtable and is safe against
 * concurrent klp_shaकरोw_मुक्त() and klp_shaकरोw_get() operations.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/hashtable.h>
#समावेश <linux/slab.h>
#समावेश <linux/livepatch.h>

अटल DEFINE_HASHTABLE(klp_shaकरोw_hash, 12);

/*
 * klp_shaकरोw_lock provides exclusive access to the klp_shaकरोw_hash and
 * the shaकरोw variables it references.
 */
अटल DEFINE_SPINLOCK(klp_shaकरोw_lock);

/**
 * काष्ठा klp_shaकरोw - shaकरोw variable काष्ठाure
 * @node:	klp_shaकरोw_hash hash table node
 * @rcu_head:	RCU is used to safely मुक्त this काष्ठाure
 * @obj:	poपूर्णांकer to parent object
 * @id:		data identअगरier
 * @data:	data area
 */
काष्ठा klp_shaकरोw अणु
	काष्ठा hlist_node node;
	काष्ठा rcu_head rcu_head;
	व्योम *obj;
	अचिन्हित दीर्घ id;
	अक्षर data[];
पूर्ण;

/**
 * klp_shaकरोw_match() - verअगरy a shaकरोw variable matches given <obj, id>
 * @shaकरोw:	shaकरोw variable to match
 * @obj:	poपूर्णांकer to parent object
 * @id:		data identअगरier
 *
 * Return: true अगर the shaकरोw variable matches.
 */
अटल अंतरभूत bool klp_shaकरोw_match(काष्ठा klp_shaकरोw *shaकरोw, व्योम *obj,
				अचिन्हित दीर्घ id)
अणु
	वापस shaकरोw->obj == obj && shaकरोw->id == id;
पूर्ण

/**
 * klp_shaकरोw_get() - retrieve a shaकरोw variable data poपूर्णांकer
 * @obj:	poपूर्णांकer to parent object
 * @id:		data identअगरier
 *
 * Return: the shaकरोw variable data element, शून्य on failure.
 */
व्योम *klp_shaकरोw_get(व्योम *obj, अचिन्हित दीर्घ id)
अणु
	काष्ठा klp_shaकरोw *shaकरोw;

	rcu_पढ़ो_lock();

	hash_क्रम_each_possible_rcu(klp_shaकरोw_hash, shaकरोw, node,
				   (अचिन्हित दीर्घ)obj) अणु

		अगर (klp_shaकरोw_match(shaकरोw, obj, id)) अणु
			rcu_पढ़ो_unlock();
			वापस shaकरोw->data;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(klp_shaकरोw_get);

अटल व्योम *__klp_shaकरोw_get_or_alloc(व्योम *obj, अचिन्हित दीर्घ id,
				       माप_प्रकार size, gfp_t gfp_flags,
				       klp_shaकरोw_ctor_t ctor, व्योम *ctor_data,
				       bool warn_on_exist)
अणु
	काष्ठा klp_shaकरोw *new_shaकरोw;
	व्योम *shaकरोw_data;
	अचिन्हित दीर्घ flags;

	/* Check अगर the shaकरोw variable alपढ़ोy exists */
	shaकरोw_data = klp_shaकरोw_get(obj, id);
	अगर (shaकरोw_data)
		जाओ exists;

	/*
	 * Allocate a new shaकरोw variable.  Fill it with zeroes by शेष.
	 * More complex setting can be करोne by @ctor function.  But it is
	 * called only when the buffer is really used (under klp_shaकरोw_lock).
	 */
	new_shaकरोw = kzalloc(size + माप(*new_shaकरोw), gfp_flags);
	अगर (!new_shaकरोw)
		वापस शून्य;

	/* Look क्रम <obj, id> again under the lock */
	spin_lock_irqsave(&klp_shaकरोw_lock, flags);
	shaकरोw_data = klp_shaकरोw_get(obj, id);
	अगर (unlikely(shaकरोw_data)) अणु
		/*
		 * Shaकरोw variable was found, throw away speculative
		 * allocation.
		 */
		spin_unlock_irqrestore(&klp_shaकरोw_lock, flags);
		kमुक्त(new_shaकरोw);
		जाओ exists;
	पूर्ण

	new_shaकरोw->obj = obj;
	new_shaकरोw->id = id;

	अगर (ctor) अणु
		पूर्णांक err;

		err = ctor(obj, new_shaकरोw->data, ctor_data);
		अगर (err) अणु
			spin_unlock_irqrestore(&klp_shaकरोw_lock, flags);
			kमुक्त(new_shaकरोw);
			pr_err("Failed to construct shadow variable <%p, %lx> (%d)\n",
			       obj, id, err);
			वापस शून्य;
		पूर्ण
	पूर्ण

	/* No <obj, id> found, so attach the newly allocated one */
	hash_add_rcu(klp_shaकरोw_hash, &new_shaकरोw->node,
		     (अचिन्हित दीर्घ)new_shaकरोw->obj);
	spin_unlock_irqrestore(&klp_shaकरोw_lock, flags);

	वापस new_shaकरोw->data;

exists:
	अगर (warn_on_exist) अणु
		WARN(1, "Duplicate shadow variable <%p, %lx>\n", obj, id);
		वापस शून्य;
	पूर्ण

	वापस shaकरोw_data;
पूर्ण

/**
 * klp_shaकरोw_alloc() - allocate and add a new shaकरोw variable
 * @obj:	poपूर्णांकer to parent object
 * @id:		data identअगरier
 * @size:	size of attached data
 * @gfp_flags:	GFP mask क्रम allocation
 * @ctor:	custom स्थिरructor to initialize the shaकरोw data (optional)
 * @ctor_data:	poपूर्णांकer to any data needed by @ctor (optional)
 *
 * Allocates @size bytes क्रम new shaकरोw variable data using @gfp_flags.
 * The data are zeroed by शेष.  They are further initialized by @ctor
 * function अगर it is not शून्य.  The new shaकरोw variable is then added
 * to the global hashtable.
 *
 * If an existing <obj, id> shaकरोw variable can be found, this routine will
 * issue a WARN, निकास early and वापस शून्य.
 *
 * This function guarantees that the स्थिरructor function is called only when
 * the variable did not exist beक्रमe.  The cost is that @ctor is called
 * in atomic context under a spin lock.
 *
 * Return: the shaकरोw variable data element, शून्य on duplicate or
 * failure.
 */
व्योम *klp_shaकरोw_alloc(व्योम *obj, अचिन्हित दीर्घ id,
		       माप_प्रकार size, gfp_t gfp_flags,
		       klp_shaकरोw_ctor_t ctor, व्योम *ctor_data)
अणु
	वापस __klp_shaकरोw_get_or_alloc(obj, id, size, gfp_flags,
					 ctor, ctor_data, true);
पूर्ण
EXPORT_SYMBOL_GPL(klp_shaकरोw_alloc);

/**
 * klp_shaकरोw_get_or_alloc() - get existing or allocate a new shaकरोw variable
 * @obj:	poपूर्णांकer to parent object
 * @id:		data identअगरier
 * @size:	size of attached data
 * @gfp_flags:	GFP mask क्रम allocation
 * @ctor:	custom स्थिरructor to initialize the shaकरोw data (optional)
 * @ctor_data:	poपूर्णांकer to any data needed by @ctor (optional)
 *
 * Returns a poपूर्णांकer to existing shaकरोw data अगर an <obj, id> shaकरोw
 * variable is alपढ़ोy present.  Otherwise, it creates a new shaकरोw
 * variable like klp_shaकरोw_alloc().
 *
 * This function guarantees that only one shaकरोw variable exists with the given
 * @id क्रम the given @obj.  It also guarantees that the स्थिरructor function
 * will be called only when the variable did not exist beक्रमe.  The cost is
 * that @ctor is called in atomic context under a spin lock.
 *
 * Return: the shaकरोw variable data element, शून्य on failure.
 */
व्योम *klp_shaकरोw_get_or_alloc(व्योम *obj, अचिन्हित दीर्घ id,
			      माप_प्रकार size, gfp_t gfp_flags,
			      klp_shaकरोw_ctor_t ctor, व्योम *ctor_data)
अणु
	वापस __klp_shaकरोw_get_or_alloc(obj, id, size, gfp_flags,
					 ctor, ctor_data, false);
पूर्ण
EXPORT_SYMBOL_GPL(klp_shaकरोw_get_or_alloc);

अटल व्योम klp_shaकरोw_मुक्त_काष्ठा(काष्ठा klp_shaकरोw *shaकरोw,
				   klp_shaकरोw_dtor_t dtor)
अणु
	hash_del_rcu(&shaकरोw->node);
	अगर (dtor)
		dtor(shaकरोw->obj, shaकरोw->data);
	kमुक्त_rcu(shaकरोw, rcu_head);
पूर्ण

/**
 * klp_shaकरोw_मुक्त() - detach and मुक्त a <obj, id> shaकरोw variable
 * @obj:	poपूर्णांकer to parent object
 * @id:		data identअगरier
 * @dtor:	custom callback that can be used to unरेजिस्टर the variable
 *		and/or मुक्त data that the shaकरोw variable poपूर्णांकs to (optional)
 *
 * This function releases the memory क्रम this <obj, id> shaकरोw variable
 * instance, callers should stop referencing it accordingly.
 */
व्योम klp_shaकरोw_मुक्त(व्योम *obj, अचिन्हित दीर्घ id, klp_shaकरोw_dtor_t dtor)
अणु
	काष्ठा klp_shaकरोw *shaकरोw;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&klp_shaकरोw_lock, flags);

	/* Delete <obj, id> from hash */
	hash_क्रम_each_possible(klp_shaकरोw_hash, shaकरोw, node,
			       (अचिन्हित दीर्घ)obj) अणु

		अगर (klp_shaकरोw_match(shaकरोw, obj, id)) अणु
			klp_shaकरोw_मुक्त_काष्ठा(shaकरोw, dtor);
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&klp_shaकरोw_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(klp_shaकरोw_मुक्त);

/**
 * klp_shaकरोw_मुक्त_all() - detach and मुक्त all <*, id> shaकरोw variables
 * @id:		data identअगरier
 * @dtor:	custom callback that can be used to unरेजिस्टर the variable
 *		and/or मुक्त data that the shaकरोw variable poपूर्णांकs to (optional)
 *
 * This function releases the memory क्रम all <*, id> shaकरोw variable
 * instances, callers should stop referencing them accordingly.
 */
व्योम klp_shaकरोw_मुक्त_all(अचिन्हित दीर्घ id, klp_shaकरोw_dtor_t dtor)
अणु
	काष्ठा klp_shaकरोw *shaकरोw;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	spin_lock_irqsave(&klp_shaकरोw_lock, flags);

	/* Delete all <*, id> from hash */
	hash_क्रम_each(klp_shaकरोw_hash, i, shaकरोw, node) अणु
		अगर (klp_shaकरोw_match(shaकरोw, shaकरोw->obj, id))
			klp_shaकरोw_मुक्त_काष्ठा(shaकरोw, dtor);
	पूर्ण

	spin_unlock_irqrestore(&klp_shaकरोw_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(klp_shaकरोw_मुक्त_all);
