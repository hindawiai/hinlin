<शैली गुरु>
/*
 * Public API and common code क्रम kernel->userspace relay file support.
 *
 * See Documentation/fileप्रणालीs/relay.rst क्रम an overview.
 *
 * Copyright (C) 2002-2005 - Tom Zanussi (zanussi@us.ibm.com), IBM Corp
 * Copyright (C) 1999-2005 - Karim Yaghmour (karim@opersys.com)
 *
 * Moved to kernel/relay.c by Paul Mundt, 2006.
 * November 2006 - CPU hotplug support by Mathieu Desnoyers
 * 	(mathieu.desnoyers@polymtl.ca)
 *
 * This file is released under the GPL.
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/माला.स>
#समावेश <linux/relay.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mm.h>
#समावेश <linux/cpu.h>
#समावेश <linux/splice.h>

/* list of खोलो channels, क्रम cpu hotplug */
अटल DEFINE_MUTEX(relay_channels_mutex);
अटल LIST_HEAD(relay_channels);

/*
 * fault() vm_op implementation क्रम relay file mapping.
 */
अटल vm_fault_t relay_buf_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा page *page;
	काष्ठा rchan_buf *buf = vmf->vma->vm_निजी_data;
	pgoff_t pgoff = vmf->pgoff;

	अगर (!buf)
		वापस VM_FAULT_OOM;

	page = vदो_स्मृति_to_page(buf->start + (pgoff << PAGE_SHIFT));
	अगर (!page)
		वापस VM_FAULT_SIGBUS;
	get_page(page);
	vmf->page = page;

	वापस 0;
पूर्ण

/*
 * vm_ops क्रम relay file mappings.
 */
अटल स्थिर काष्ठा vm_operations_काष्ठा relay_file_mmap_ops = अणु
	.fault = relay_buf_fault,
पूर्ण;

/*
 * allocate an array of poपूर्णांकers of काष्ठा page
 */
अटल काष्ठा page **relay_alloc_page_array(अचिन्हित पूर्णांक n_pages)
अणु
	स्थिर माप_प्रकार pa_size = n_pages * माप(काष्ठा page *);
	अगर (pa_size > PAGE_SIZE)
		वापस vzalloc(pa_size);
	वापस kzalloc(pa_size, GFP_KERNEL);
पूर्ण

/*
 * मुक्त an array of poपूर्णांकers of काष्ठा page
 */
अटल व्योम relay_मुक्त_page_array(काष्ठा page **array)
अणु
	kvमुक्त(array);
पूर्ण

/**
 *	relay_mmap_buf: - mmap channel buffer to process address space
 *	@buf: relay channel buffer
 *	@vma: vm_area_काष्ठा describing memory to be mapped
 *
 *	Returns 0 अगर ok, negative on error
 *
 *	Caller should alपढ़ोy have grabbed mmap_lock.
 */
अटल पूर्णांक relay_mmap_buf(काष्ठा rchan_buf *buf, काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित दीर्घ length = vma->vm_end - vma->vm_start;

	अगर (!buf)
		वापस -EBADF;

	अगर (length != (अचिन्हित दीर्घ)buf->chan->alloc_size)
		वापस -EINVAL;

	vma->vm_ops = &relay_file_mmap_ops;
	vma->vm_flags |= VM_DONTEXPAND;
	vma->vm_निजी_data = buf;

	वापस 0;
पूर्ण

/**
 *	relay_alloc_buf - allocate a channel buffer
 *	@buf: the buffer काष्ठा
 *	@size: total size of the buffer
 *
 *	Returns a poपूर्णांकer to the resulting buffer, %शून्य अगर unsuccessful. The
 *	passed in size will get page aligned, अगर it isn't alपढ़ोy.
 */
अटल व्योम *relay_alloc_buf(काष्ठा rchan_buf *buf, माप_प्रकार *size)
अणु
	व्योम *mem;
	अचिन्हित पूर्णांक i, j, n_pages;

	*size = PAGE_ALIGN(*size);
	n_pages = *size >> PAGE_SHIFT;

	buf->page_array = relay_alloc_page_array(n_pages);
	अगर (!buf->page_array)
		वापस शून्य;

	क्रम (i = 0; i < n_pages; i++) अणु
		buf->page_array[i] = alloc_page(GFP_KERNEL);
		अगर (unlikely(!buf->page_array[i]))
			जाओ depopulate;
		set_page_निजी(buf->page_array[i], (अचिन्हित दीर्घ)buf);
	पूर्ण
	mem = vmap(buf->page_array, n_pages, VM_MAP, PAGE_KERNEL);
	अगर (!mem)
		जाओ depopulate;

	स_रखो(mem, 0, *size);
	buf->page_count = n_pages;
	वापस mem;

depopulate:
	क्रम (j = 0; j < i; j++)
		__मुक्त_page(buf->page_array[j]);
	relay_मुक्त_page_array(buf->page_array);
	वापस शून्य;
पूर्ण

/**
 *	relay_create_buf - allocate and initialize a channel buffer
 *	@chan: the relay channel
 *
 *	Returns channel buffer अगर successful, %शून्य otherwise.
 */
अटल काष्ठा rchan_buf *relay_create_buf(काष्ठा rchan *chan)
अणु
	काष्ठा rchan_buf *buf;

	अगर (chan->n_subbufs > KMALLOC_MAX_SIZE / माप(माप_प्रकार *))
		वापस शून्य;

	buf = kzalloc(माप(काष्ठा rchan_buf), GFP_KERNEL);
	अगर (!buf)
		वापस शून्य;
	buf->padding = kदो_स्मृति_array(chan->n_subbufs, माप(माप_प्रकार *),
				     GFP_KERNEL);
	अगर (!buf->padding)
		जाओ मुक्त_buf;

	buf->start = relay_alloc_buf(buf, &chan->alloc_size);
	अगर (!buf->start)
		जाओ मुक्त_buf;

	buf->chan = chan;
	kref_get(&buf->chan->kref);
	वापस buf;

मुक्त_buf:
	kमुक्त(buf->padding);
	kमुक्त(buf);
	वापस शून्य;
पूर्ण

/**
 *	relay_destroy_channel - मुक्त the channel काष्ठा
 *	@kref: target kernel reference that contains the relay channel
 *
 *	Should only be called from kref_put().
 */
अटल व्योम relay_destroy_channel(काष्ठा kref *kref)
अणु
	काष्ठा rchan *chan = container_of(kref, काष्ठा rchan, kref);
	मुक्त_percpu(chan->buf);
	kमुक्त(chan);
पूर्ण

/**
 *	relay_destroy_buf - destroy an rchan_buf काष्ठा and associated buffer
 *	@buf: the buffer काष्ठा
 */
अटल व्योम relay_destroy_buf(काष्ठा rchan_buf *buf)
अणु
	काष्ठा rchan *chan = buf->chan;
	अचिन्हित पूर्णांक i;

	अगर (likely(buf->start)) अणु
		vunmap(buf->start);
		क्रम (i = 0; i < buf->page_count; i++)
			__मुक्त_page(buf->page_array[i]);
		relay_मुक्त_page_array(buf->page_array);
	पूर्ण
	*per_cpu_ptr(chan->buf, buf->cpu) = शून्य;
	kमुक्त(buf->padding);
	kमुक्त(buf);
	kref_put(&chan->kref, relay_destroy_channel);
पूर्ण

/**
 *	relay_हटाओ_buf - हटाओ a channel buffer
 *	@kref: target kernel reference that contains the relay buffer
 *
 *	Removes the file from the fileप्रणाली, which also मुक्तs the
 *	rchan_buf_काष्ठा and the channel buffer.  Should only be called from
 *	kref_put().
 */
अटल व्योम relay_हटाओ_buf(काष्ठा kref *kref)
अणु
	काष्ठा rchan_buf *buf = container_of(kref, काष्ठा rchan_buf, kref);
	relay_destroy_buf(buf);
पूर्ण

/**
 *	relay_buf_empty - boolean, is the channel buffer empty?
 *	@buf: channel buffer
 *
 *	Returns 1 अगर the buffer is empty, 0 otherwise.
 */
अटल पूर्णांक relay_buf_empty(काष्ठा rchan_buf *buf)
अणु
	वापस (buf->subbufs_produced - buf->subbufs_consumed) ? 0 : 1;
पूर्ण

/**
 *	relay_buf_full - boolean, is the channel buffer full?
 *	@buf: channel buffer
 *
 *	Returns 1 अगर the buffer is full, 0 otherwise.
 */
पूर्णांक relay_buf_full(काष्ठा rchan_buf *buf)
अणु
	माप_प्रकार पढ़ोy = buf->subbufs_produced - buf->subbufs_consumed;
	वापस (पढ़ोy >= buf->chan->n_subbufs) ? 1 : 0;
पूर्ण
EXPORT_SYMBOL_GPL(relay_buf_full);

/*
 * High-level relay kernel API and associated functions.
 */

अटल पूर्णांक relay_subbuf_start(काष्ठा rchan_buf *buf, व्योम *subbuf,
			      व्योम *prev_subbuf, माप_प्रकार prev_padding)
अणु
	अगर (!buf->chan->cb->subbuf_start)
		वापस !relay_buf_full(buf);

	वापस buf->chan->cb->subbuf_start(buf, subbuf,
					   prev_subbuf, prev_padding);
पूर्ण

/**
 *	wakeup_पढ़ोers - wake up पढ़ोers रुकोing on a channel
 *	@work: contains the channel buffer
 *
 *	This is the function used to defer पढ़ोer waking
 */
अटल व्योम wakeup_पढ़ोers(काष्ठा irq_work *work)
अणु
	काष्ठा rchan_buf *buf;

	buf = container_of(work, काष्ठा rchan_buf, wakeup_work);
	wake_up_पूर्णांकerruptible(&buf->पढ़ो_रुको);
पूर्ण

/**
 *	__relay_reset - reset a channel buffer
 *	@buf: the channel buffer
 *	@init: 1 अगर this is a first-समय initialization
 *
 *	See relay_reset() क्रम description of effect.
 */
अटल व्योम __relay_reset(काष्ठा rchan_buf *buf, अचिन्हित पूर्णांक init)
अणु
	माप_प्रकार i;

	अगर (init) अणु
		init_रुकोqueue_head(&buf->पढ़ो_रुको);
		kref_init(&buf->kref);
		init_irq_work(&buf->wakeup_work, wakeup_पढ़ोers);
	पूर्ण अन्यथा अणु
		irq_work_sync(&buf->wakeup_work);
	पूर्ण

	buf->subbufs_produced = 0;
	buf->subbufs_consumed = 0;
	buf->bytes_consumed = 0;
	buf->finalized = 0;
	buf->data = buf->start;
	buf->offset = 0;

	क्रम (i = 0; i < buf->chan->n_subbufs; i++)
		buf->padding[i] = 0;

	relay_subbuf_start(buf, buf->data, शून्य, 0);
पूर्ण

/**
 *	relay_reset - reset the channel
 *	@chan: the channel
 *
 *	This has the effect of erasing all data from all channel buffers
 *	and restarting the channel in its initial state.  The buffers
 *	are not मुक्तd, so any mappings are still in effect.
 *
 *	NOTE. Care should be taken that the channel isn't actually
 *	being used by anything when this call is made.
 */
व्योम relay_reset(काष्ठा rchan *chan)
अणु
	काष्ठा rchan_buf *buf;
	अचिन्हित पूर्णांक i;

	अगर (!chan)
		वापस;

	अगर (chan->is_global && (buf = *per_cpu_ptr(chan->buf, 0))) अणु
		__relay_reset(buf, 0);
		वापस;
	पूर्ण

	mutex_lock(&relay_channels_mutex);
	क्रम_each_possible_cpu(i)
		अगर ((buf = *per_cpu_ptr(chan->buf, i)))
			__relay_reset(buf, 0);
	mutex_unlock(&relay_channels_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(relay_reset);

अटल अंतरभूत व्योम relay_set_buf_dentry(काष्ठा rchan_buf *buf,
					काष्ठा dentry *dentry)
अणु
	buf->dentry = dentry;
	d_inode(buf->dentry)->i_size = buf->early_bytes;
पूर्ण

अटल काष्ठा dentry *relay_create_buf_file(काष्ठा rchan *chan,
					    काष्ठा rchan_buf *buf,
					    अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा dentry *dentry;
	अक्षर *क्षणिकe;

	क्षणिकe = kzalloc(NAME_MAX + 1, GFP_KERNEL);
	अगर (!क्षणिकe)
		वापस शून्य;
	snम_लिखो(क्षणिकe, NAME_MAX, "%s%d", chan->base_filename, cpu);

	/* Create file in fs */
	dentry = chan->cb->create_buf_file(क्षणिकe, chan->parent,
					   S_IRUSR, buf,
					   &chan->is_global);
	अगर (IS_ERR(dentry))
		dentry = शून्य;

	kमुक्त(क्षणिकe);

	वापस dentry;
पूर्ण

/*
 *	relay_खोलो_buf - create a new relay channel buffer
 *
 *	used by relay_खोलो() and CPU hotplug.
 */
अटल काष्ठा rchan_buf *relay_खोलो_buf(काष्ठा rchan *chan, अचिन्हित पूर्णांक cpu)
अणु
 	काष्ठा rchan_buf *buf = शून्य;
	काष्ठा dentry *dentry;

 	अगर (chan->is_global)
		वापस *per_cpu_ptr(chan->buf, 0);

	buf = relay_create_buf(chan);
	अगर (!buf)
		वापस शून्य;

	अगर (chan->has_base_filename) अणु
		dentry = relay_create_buf_file(chan, buf, cpu);
		अगर (!dentry)
			जाओ मुक्त_buf;
		relay_set_buf_dentry(buf, dentry);
	पूर्ण अन्यथा अणु
		/* Only retrieve global info, nothing more, nothing less */
		dentry = chan->cb->create_buf_file(शून्य, शून्य,
						   S_IRUSR, buf,
						   &chan->is_global);
		अगर (IS_ERR_OR_शून्य(dentry))
			जाओ मुक्त_buf;
	पूर्ण

 	buf->cpu = cpu;
 	__relay_reset(buf, 1);

 	अगर(chan->is_global) अणु
		*per_cpu_ptr(chan->buf, 0) = buf;
 		buf->cpu = 0;
  	पूर्ण

	वापस buf;

मुक्त_buf:
 	relay_destroy_buf(buf);
	वापस शून्य;
पूर्ण

/**
 *	relay_बंद_buf - बंद a channel buffer
 *	@buf: channel buffer
 *
 *	Marks the buffer finalized and restores the शेष callbacks.
 *	The channel buffer and channel buffer data काष्ठाure are then मुक्तd
 *	स्वतःmatically when the last reference is given up.
 */
अटल व्योम relay_बंद_buf(काष्ठा rchan_buf *buf)
अणु
	buf->finalized = 1;
	irq_work_sync(&buf->wakeup_work);
	buf->chan->cb->हटाओ_buf_file(buf->dentry);
	kref_put(&buf->kref, relay_हटाओ_buf);
पूर्ण

पूर्णांक relay_prepare_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा rchan *chan;
	काष्ठा rchan_buf *buf;

	mutex_lock(&relay_channels_mutex);
	list_क्रम_each_entry(chan, &relay_channels, list) अणु
		अगर ((buf = *per_cpu_ptr(chan->buf, cpu)))
			जारी;
		buf = relay_खोलो_buf(chan, cpu);
		अगर (!buf) अणु
			pr_err("relay: cpu %d buffer creation failed\n", cpu);
			mutex_unlock(&relay_channels_mutex);
			वापस -ENOMEM;
		पूर्ण
		*per_cpu_ptr(chan->buf, cpu) = buf;
	पूर्ण
	mutex_unlock(&relay_channels_mutex);
	वापस 0;
पूर्ण

/**
 *	relay_खोलो - create a new relay channel
 *	@base_filename: base name of files to create, %शून्य क्रम buffering only
 *	@parent: dentry of parent directory, %शून्य क्रम root directory or buffer
 *	@subbuf_size: size of sub-buffers
 *	@n_subbufs: number of sub-buffers
 *	@cb: client callback functions
 *	@निजी_data: user-defined data
 *
 *	Returns channel poपूर्णांकer अगर successful, %शून्य otherwise.
 *
 *	Creates a channel buffer क्रम each cpu using the sizes and
 *	attributes specअगरied.  The created channel buffer files
 *	will be named base_filename0...base_filenameN-1.  File
 *	permissions will be %S_IRUSR.
 *
 *	If खोलोing a buffer (@parent = शून्य) that you later wish to रेजिस्टर
 *	in a fileप्रणाली, call relay_late_setup_files() once the @parent dentry
 *	is available.
 */
काष्ठा rchan *relay_खोलो(स्थिर अक्षर *base_filename,
			 काष्ठा dentry *parent,
			 माप_प्रकार subbuf_size,
			 माप_प्रकार n_subbufs,
			 स्थिर काष्ठा rchan_callbacks *cb,
			 व्योम *निजी_data)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा rchan *chan;
	काष्ठा rchan_buf *buf;

	अगर (!(subbuf_size && n_subbufs))
		वापस शून्य;
	अगर (subbuf_size > अच_पूर्णांक_उच्च / n_subbufs)
		वापस शून्य;
	अगर (!cb || !cb->create_buf_file || !cb->हटाओ_buf_file)
		वापस शून्य;

	chan = kzalloc(माप(काष्ठा rchan), GFP_KERNEL);
	अगर (!chan)
		वापस शून्य;

	chan->buf = alloc_percpu(काष्ठा rchan_buf *);
	अगर (!chan->buf) अणु
		kमुक्त(chan);
		वापस शून्य;
	पूर्ण

	chan->version = RELAYFS_CHANNEL_VERSION;
	chan->n_subbufs = n_subbufs;
	chan->subbuf_size = subbuf_size;
	chan->alloc_size = PAGE_ALIGN(subbuf_size * n_subbufs);
	chan->parent = parent;
	chan->निजी_data = निजी_data;
	अगर (base_filename) अणु
		chan->has_base_filename = 1;
		strlcpy(chan->base_filename, base_filename, NAME_MAX);
	पूर्ण
	chan->cb = cb;
	kref_init(&chan->kref);

	mutex_lock(&relay_channels_mutex);
	क्रम_each_online_cpu(i) अणु
		buf = relay_खोलो_buf(chan, i);
		अगर (!buf)
			जाओ मुक्त_bufs;
		*per_cpu_ptr(chan->buf, i) = buf;
	पूर्ण
	list_add(&chan->list, &relay_channels);
	mutex_unlock(&relay_channels_mutex);

	वापस chan;

मुक्त_bufs:
	क्रम_each_possible_cpu(i) अणु
		अगर ((buf = *per_cpu_ptr(chan->buf, i)))
			relay_बंद_buf(buf);
	पूर्ण

	kref_put(&chan->kref, relay_destroy_channel);
	mutex_unlock(&relay_channels_mutex);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(relay_खोलो);

काष्ठा rchan_percpu_buf_dispatcher अणु
	काष्ठा rchan_buf *buf;
	काष्ठा dentry *dentry;
पूर्ण;

/* Called in atomic context. */
अटल व्योम __relay_set_buf_dentry(व्योम *info)
अणु
	काष्ठा rchan_percpu_buf_dispatcher *p = info;

	relay_set_buf_dentry(p->buf, p->dentry);
पूर्ण

/**
 *	relay_late_setup_files - triggers file creation
 *	@chan: channel to operate on
 *	@base_filename: base name of files to create
 *	@parent: dentry of parent directory, %शून्य क्रम root directory
 *
 *	Returns 0 अगर successful, non-zero otherwise.
 *
 *	Use to setup files क्रम a previously buffer-only channel created
 *	by relay_खोलो() with a शून्य parent dentry.
 *
 *	For example, this is useful क्रम perfomring early tracing in kernel,
 *	beक्रमe VFS is up and then exposing the early results once the dentry
 *	is available.
 */
पूर्णांक relay_late_setup_files(काष्ठा rchan *chan,
			   स्थिर अक्षर *base_filename,
			   काष्ठा dentry *parent)
अणु
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक i, curr_cpu;
	अचिन्हित दीर्घ flags;
	काष्ठा dentry *dentry;
	काष्ठा rchan_buf *buf;
	काष्ठा rchan_percpu_buf_dispatcher disp;

	अगर (!chan || !base_filename)
		वापस -EINVAL;

	strlcpy(chan->base_filename, base_filename, NAME_MAX);

	mutex_lock(&relay_channels_mutex);
	/* Is chan alपढ़ोy set up? */
	अगर (unlikely(chan->has_base_filename)) अणु
		mutex_unlock(&relay_channels_mutex);
		वापस -EEXIST;
	पूर्ण
	chan->has_base_filename = 1;
	chan->parent = parent;

	अगर (chan->is_global) अणु
		err = -EINVAL;
		buf = *per_cpu_ptr(chan->buf, 0);
		अगर (!WARN_ON_ONCE(!buf)) अणु
			dentry = relay_create_buf_file(chan, buf, 0);
			अगर (dentry && !WARN_ON_ONCE(!chan->is_global)) अणु
				relay_set_buf_dentry(buf, dentry);
				err = 0;
			पूर्ण
		पूर्ण
		mutex_unlock(&relay_channels_mutex);
		वापस err;
	पूर्ण

	curr_cpu = get_cpu();
	/*
	 * The CPU hotplug notअगरier ran beक्रमe us and created buffers with
	 * no files associated. So it's safe to call relay_setup_buf_file()
	 * on all currently online CPUs.
	 */
	क्रम_each_online_cpu(i) अणु
		buf = *per_cpu_ptr(chan->buf, i);
		अगर (unlikely(!buf)) अणु
			WARN_ONCE(1, KERN_ERR "CPU has no buffer!\n");
			err = -EINVAL;
			अवरोध;
		पूर्ण

		dentry = relay_create_buf_file(chan, buf, i);
		अगर (unlikely(!dentry)) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (curr_cpu == i) अणु
			local_irq_save(flags);
			relay_set_buf_dentry(buf, dentry);
			local_irq_restore(flags);
		पूर्ण अन्यथा अणु
			disp.buf = buf;
			disp.dentry = dentry;
			smp_mb();
			/* relay_channels_mutex must be held, so रुको. */
			err = smp_call_function_single(i,
						       __relay_set_buf_dentry,
						       &disp, 1);
		पूर्ण
		अगर (unlikely(err))
			अवरोध;
	पूर्ण
	put_cpu();
	mutex_unlock(&relay_channels_mutex);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(relay_late_setup_files);

/**
 *	relay_चयन_subbuf - चयन to a new sub-buffer
 *	@buf: channel buffer
 *	@length: size of current event
 *
 *	Returns either the length passed in or 0 अगर full.
 *
 *	Perक्रमms sub-buffer-चयन tasks such as invoking callbacks,
 *	updating padding counts, waking up पढ़ोers, etc.
 */
माप_प्रकार relay_चयन_subbuf(काष्ठा rchan_buf *buf, माप_प्रकार length)
अणु
	व्योम *old, *new;
	माप_प्रकार old_subbuf, new_subbuf;

	अगर (unlikely(length > buf->chan->subbuf_size))
		जाओ toobig;

	अगर (buf->offset != buf->chan->subbuf_size + 1) अणु
		buf->prev_padding = buf->chan->subbuf_size - buf->offset;
		old_subbuf = buf->subbufs_produced % buf->chan->n_subbufs;
		buf->padding[old_subbuf] = buf->prev_padding;
		buf->subbufs_produced++;
		अगर (buf->dentry)
			d_inode(buf->dentry)->i_size +=
				buf->chan->subbuf_size -
				buf->padding[old_subbuf];
		अन्यथा
			buf->early_bytes += buf->chan->subbuf_size -
					    buf->padding[old_subbuf];
		smp_mb();
		अगर (रुकोqueue_active(&buf->पढ़ो_रुको)) अणु
			/*
			 * Calling wake_up_पूर्णांकerruptible() from here
			 * will deadlock अगर we happen to be logging
			 * from the scheduler (trying to re-grab
			 * rq->lock), so defer it.
			 */
			irq_work_queue(&buf->wakeup_work);
		पूर्ण
	पूर्ण

	old = buf->data;
	new_subbuf = buf->subbufs_produced % buf->chan->n_subbufs;
	new = buf->start + new_subbuf * buf->chan->subbuf_size;
	buf->offset = 0;
	अगर (!relay_subbuf_start(buf, new, old, buf->prev_padding)) अणु
		buf->offset = buf->chan->subbuf_size + 1;
		वापस 0;
	पूर्ण
	buf->data = new;
	buf->padding[new_subbuf] = 0;

	अगर (unlikely(length + buf->offset > buf->chan->subbuf_size))
		जाओ toobig;

	वापस length;

toobig:
	buf->chan->last_toobig = length;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(relay_चयन_subbuf);

/**
 *	relay_subbufs_consumed - update the buffer's sub-buffers-consumed count
 *	@chan: the channel
 *	@cpu: the cpu associated with the channel buffer to update
 *	@subbufs_consumed: number of sub-buffers to add to current buf's count
 *
 *	Adds to the channel buffer's consumed sub-buffer count.
 *	subbufs_consumed should be the number of sub-buffers newly consumed,
 *	not the total consumed.
 *
 *	NOTE. Kernel clients करोn't need to call this function अगर the channel
 *	mode is 'overwrite'.
 */
व्योम relay_subbufs_consumed(काष्ठा rchan *chan,
			    अचिन्हित पूर्णांक cpu,
			    माप_प्रकार subbufs_consumed)
अणु
	काष्ठा rchan_buf *buf;

	अगर (!chan || cpu >= NR_CPUS)
		वापस;

	buf = *per_cpu_ptr(chan->buf, cpu);
	अगर (!buf || subbufs_consumed > chan->n_subbufs)
		वापस;

	अगर (subbufs_consumed > buf->subbufs_produced - buf->subbufs_consumed)
		buf->subbufs_consumed = buf->subbufs_produced;
	अन्यथा
		buf->subbufs_consumed += subbufs_consumed;
पूर्ण
EXPORT_SYMBOL_GPL(relay_subbufs_consumed);

/**
 *	relay_बंद - बंद the channel
 *	@chan: the channel
 *
 *	Closes all channel buffers and मुक्तs the channel.
 */
व्योम relay_बंद(काष्ठा rchan *chan)
अणु
	काष्ठा rchan_buf *buf;
	अचिन्हित पूर्णांक i;

	अगर (!chan)
		वापस;

	mutex_lock(&relay_channels_mutex);
	अगर (chan->is_global && (buf = *per_cpu_ptr(chan->buf, 0)))
		relay_बंद_buf(buf);
	अन्यथा
		क्रम_each_possible_cpu(i)
			अगर ((buf = *per_cpu_ptr(chan->buf, i)))
				relay_बंद_buf(buf);

	अगर (chan->last_toobig)
		prपूर्णांकk(KERN_WARNING "relay: one or more items not logged "
		       "[item size (%zd) > sub-buffer size (%zd)]\n",
		       chan->last_toobig, chan->subbuf_size);

	list_del(&chan->list);
	kref_put(&chan->kref, relay_destroy_channel);
	mutex_unlock(&relay_channels_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(relay_बंद);

/**
 *	relay_flush - बंद the channel
 *	@chan: the channel
 *
 *	Flushes all channel buffers, i.e. क्रमces buffer चयन.
 */
व्योम relay_flush(काष्ठा rchan *chan)
अणु
	काष्ठा rchan_buf *buf;
	अचिन्हित पूर्णांक i;

	अगर (!chan)
		वापस;

	अगर (chan->is_global && (buf = *per_cpu_ptr(chan->buf, 0))) अणु
		relay_चयन_subbuf(buf, 0);
		वापस;
	पूर्ण

	mutex_lock(&relay_channels_mutex);
	क्रम_each_possible_cpu(i)
		अगर ((buf = *per_cpu_ptr(chan->buf, i)))
			relay_चयन_subbuf(buf, 0);
	mutex_unlock(&relay_channels_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(relay_flush);

/**
 *	relay_file_खोलो - खोलो file op क्रम relay files
 *	@inode: the inode
 *	@filp: the file
 *
 *	Increments the channel buffer refcount.
 */
अटल पूर्णांक relay_file_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा rchan_buf *buf = inode->i_निजी;
	kref_get(&buf->kref);
	filp->निजी_data = buf;

	वापस nonseekable_खोलो(inode, filp);
पूर्ण

/**
 *	relay_file_mmap - mmap file op क्रम relay files
 *	@filp: the file
 *	@vma: the vma describing what to map
 *
 *	Calls upon relay_mmap_buf() to map the file पूर्णांकo user space.
 */
अटल पूर्णांक relay_file_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा rchan_buf *buf = filp->निजी_data;
	वापस relay_mmap_buf(buf, vma);
पूर्ण

/**
 *	relay_file_poll - poll file op क्रम relay files
 *	@filp: the file
 *	@रुको: poll table
 *
 *	Poll implemention.
 */
अटल __poll_t relay_file_poll(काष्ठा file *filp, poll_table *रुको)
अणु
	__poll_t mask = 0;
	काष्ठा rchan_buf *buf = filp->निजी_data;

	अगर (buf->finalized)
		वापस EPOLLERR;

	अगर (filp->f_mode & FMODE_READ) अणु
		poll_रुको(filp, &buf->पढ़ो_रुको, रुको);
		अगर (!relay_buf_empty(buf))
			mask |= EPOLLIN | EPOLLRDNORM;
	पूर्ण

	वापस mask;
पूर्ण

/**
 *	relay_file_release - release file op क्रम relay files
 *	@inode: the inode
 *	@filp: the file
 *
 *	Decrements the channel refcount, as the fileप्रणाली is
 *	no दीर्घer using it.
 */
अटल पूर्णांक relay_file_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा rchan_buf *buf = filp->निजी_data;
	kref_put(&buf->kref, relay_हटाओ_buf);

	वापस 0;
पूर्ण

/*
 *	relay_file_पढ़ो_consume - update the consumed count क्रम the buffer
 */
अटल व्योम relay_file_पढ़ो_consume(काष्ठा rchan_buf *buf,
				    माप_प्रकार पढ़ो_pos,
				    माप_प्रकार bytes_consumed)
अणु
	माप_प्रकार subbuf_size = buf->chan->subbuf_size;
	माप_प्रकार n_subbufs = buf->chan->n_subbufs;
	माप_प्रकार पढ़ो_subbuf;

	अगर (buf->subbufs_produced == buf->subbufs_consumed &&
	    buf->offset == buf->bytes_consumed)
		वापस;

	अगर (buf->bytes_consumed + bytes_consumed > subbuf_size) अणु
		relay_subbufs_consumed(buf->chan, buf->cpu, 1);
		buf->bytes_consumed = 0;
	पूर्ण

	buf->bytes_consumed += bytes_consumed;
	अगर (!पढ़ो_pos)
		पढ़ो_subbuf = buf->subbufs_consumed % n_subbufs;
	अन्यथा
		पढ़ो_subbuf = पढ़ो_pos / buf->chan->subbuf_size;
	अगर (buf->bytes_consumed + buf->padding[पढ़ो_subbuf] == subbuf_size) अणु
		अगर ((पढ़ो_subbuf == buf->subbufs_produced % n_subbufs) &&
		    (buf->offset == subbuf_size))
			वापस;
		relay_subbufs_consumed(buf->chan, buf->cpu, 1);
		buf->bytes_consumed = 0;
	पूर्ण
पूर्ण

/*
 *	relay_file_पढ़ो_avail - boolean, are there unconsumed bytes available?
 */
अटल पूर्णांक relay_file_पढ़ो_avail(काष्ठा rchan_buf *buf)
अणु
	माप_प्रकार subbuf_size = buf->chan->subbuf_size;
	माप_प्रकार n_subbufs = buf->chan->n_subbufs;
	माप_प्रकार produced = buf->subbufs_produced;
	माप_प्रकार consumed;

	relay_file_पढ़ो_consume(buf, 0, 0);

	consumed = buf->subbufs_consumed;

	अगर (unlikely(buf->offset > subbuf_size)) अणु
		अगर (produced == consumed)
			वापस 0;
		वापस 1;
	पूर्ण

	अगर (unlikely(produced - consumed >= n_subbufs)) अणु
		consumed = produced - n_subbufs + 1;
		buf->subbufs_consumed = consumed;
		buf->bytes_consumed = 0;
	पूर्ण

	produced = (produced % n_subbufs) * subbuf_size + buf->offset;
	consumed = (consumed % n_subbufs) * subbuf_size + buf->bytes_consumed;

	अगर (consumed > produced)
		produced += n_subbufs * subbuf_size;

	अगर (consumed == produced) अणु
		अगर (buf->offset == subbuf_size &&
		    buf->subbufs_produced > buf->subbufs_consumed)
			वापस 1;
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/**
 *	relay_file_पढ़ो_subbuf_avail - वापस bytes available in sub-buffer
 *	@पढ़ो_pos: file पढ़ो position
 *	@buf: relay channel buffer
 */
अटल माप_प्रकार relay_file_पढ़ो_subbuf_avail(माप_प्रकार पढ़ो_pos,
					   काष्ठा rchan_buf *buf)
अणु
	माप_प्रकार padding, avail = 0;
	माप_प्रकार पढ़ो_subbuf, पढ़ो_offset, ग_लिखो_subbuf, ग_लिखो_offset;
	माप_प्रकार subbuf_size = buf->chan->subbuf_size;

	ग_लिखो_subbuf = (buf->data - buf->start) / subbuf_size;
	ग_लिखो_offset = buf->offset > subbuf_size ? subbuf_size : buf->offset;
	पढ़ो_subbuf = पढ़ो_pos / subbuf_size;
	पढ़ो_offset = पढ़ो_pos % subbuf_size;
	padding = buf->padding[पढ़ो_subbuf];

	अगर (पढ़ो_subbuf == ग_लिखो_subbuf) अणु
		अगर (पढ़ो_offset + padding < ग_लिखो_offset)
			avail = ग_लिखो_offset - (पढ़ो_offset + padding);
	पूर्ण अन्यथा
		avail = (subbuf_size - padding) - पढ़ो_offset;

	वापस avail;
पूर्ण

/**
 *	relay_file_पढ़ो_start_pos - find the first available byte to पढ़ो
 *	@buf: relay channel buffer
 *
 *	If the पढ़ो_pos is in the middle of padding, वापस the
 *	position of the first actually available byte, otherwise
 *	वापस the original value.
 */
अटल माप_प्रकार relay_file_पढ़ो_start_pos(काष्ठा rchan_buf *buf)
अणु
	माप_प्रकार पढ़ो_subbuf, padding, padding_start, padding_end;
	माप_प्रकार subbuf_size = buf->chan->subbuf_size;
	माप_प्रकार n_subbufs = buf->chan->n_subbufs;
	माप_प्रकार consumed = buf->subbufs_consumed % n_subbufs;
	माप_प्रकार पढ़ो_pos = consumed * subbuf_size + buf->bytes_consumed;

	पढ़ो_subbuf = पढ़ो_pos / subbuf_size;
	padding = buf->padding[पढ़ो_subbuf];
	padding_start = (पढ़ो_subbuf + 1) * subbuf_size - padding;
	padding_end = (पढ़ो_subbuf + 1) * subbuf_size;
	अगर (पढ़ो_pos >= padding_start && पढ़ो_pos < padding_end) अणु
		पढ़ो_subbuf = (पढ़ो_subbuf + 1) % n_subbufs;
		पढ़ो_pos = पढ़ो_subbuf * subbuf_size;
	पूर्ण

	वापस पढ़ो_pos;
पूर्ण

/**
 *	relay_file_पढ़ो_end_pos - वापस the new पढ़ो position
 *	@पढ़ो_pos: file पढ़ो position
 *	@buf: relay channel buffer
 *	@count: number of bytes to be पढ़ो
 */
अटल माप_प्रकार relay_file_पढ़ो_end_pos(काष्ठा rchan_buf *buf,
				      माप_प्रकार पढ़ो_pos,
				      माप_प्रकार count)
अणु
	माप_प्रकार पढ़ो_subbuf, padding, end_pos;
	माप_प्रकार subbuf_size = buf->chan->subbuf_size;
	माप_प्रकार n_subbufs = buf->chan->n_subbufs;

	पढ़ो_subbuf = पढ़ो_pos / subbuf_size;
	padding = buf->padding[पढ़ो_subbuf];
	अगर (पढ़ो_pos % subbuf_size + count + padding == subbuf_size)
		end_pos = (पढ़ो_subbuf + 1) * subbuf_size;
	अन्यथा
		end_pos = पढ़ो_pos + count;
	अगर (end_pos >= subbuf_size * n_subbufs)
		end_pos = 0;

	वापस end_pos;
पूर्ण

अटल sमाप_प्रकार relay_file_पढ़ो(काष्ठा file *filp,
			       अक्षर __user *buffer,
			       माप_प्रकार count,
			       loff_t *ppos)
अणु
	काष्ठा rchan_buf *buf = filp->निजी_data;
	माप_प्रकार पढ़ो_start, avail;
	माप_प्रकार written = 0;
	पूर्णांक ret;

	अगर (!count)
		वापस 0;

	inode_lock(file_inode(filp));
	करो अणु
		व्योम *from;

		अगर (!relay_file_पढ़ो_avail(buf))
			अवरोध;

		पढ़ो_start = relay_file_पढ़ो_start_pos(buf);
		avail = relay_file_पढ़ो_subbuf_avail(पढ़ो_start, buf);
		अगर (!avail)
			अवरोध;

		avail = min(count, avail);
		from = buf->start + पढ़ो_start;
		ret = avail;
		अगर (copy_to_user(buffer, from, avail))
			अवरोध;

		buffer += ret;
		written += ret;
		count -= ret;

		relay_file_पढ़ो_consume(buf, पढ़ो_start, ret);
		*ppos = relay_file_पढ़ो_end_pos(buf, पढ़ो_start, ret);
	पूर्ण जबतक (count);
	inode_unlock(file_inode(filp));

	वापस written;
पूर्ण

अटल व्योम relay_consume_bytes(काष्ठा rchan_buf *rbuf, पूर्णांक bytes_consumed)
अणु
	rbuf->bytes_consumed += bytes_consumed;

	अगर (rbuf->bytes_consumed >= rbuf->chan->subbuf_size) अणु
		relay_subbufs_consumed(rbuf->chan, rbuf->cpu, 1);
		rbuf->bytes_consumed %= rbuf->chan->subbuf_size;
	पूर्ण
पूर्ण

अटल व्योम relay_pipe_buf_release(काष्ठा pipe_inode_info *pipe,
				   काष्ठा pipe_buffer *buf)
अणु
	काष्ठा rchan_buf *rbuf;

	rbuf = (काष्ठा rchan_buf *)page_निजी(buf->page);
	relay_consume_bytes(rbuf, buf->निजी);
पूर्ण

अटल स्थिर काष्ठा pipe_buf_operations relay_pipe_buf_ops = अणु
	.release	= relay_pipe_buf_release,
	.try_steal	= generic_pipe_buf_try_steal,
	.get		= generic_pipe_buf_get,
पूर्ण;

अटल व्योम relay_page_release(काष्ठा splice_pipe_desc *spd, अचिन्हित पूर्णांक i)
अणु
पूर्ण

/*
 *	subbuf_splice_actor - splice up to one subbuf's worth of data
 */
अटल sमाप_प्रकार subbuf_splice_actor(काष्ठा file *in,
			       loff_t *ppos,
			       काष्ठा pipe_inode_info *pipe,
			       माप_प्रकार len,
			       अचिन्हित पूर्णांक flags,
			       पूर्णांक *nonpad_ret)
अणु
	अचिन्हित पूर्णांक pidx, poff, total_len, subbuf_pages, nr_pages;
	काष्ठा rchan_buf *rbuf = in->निजी_data;
	अचिन्हित पूर्णांक subbuf_size = rbuf->chan->subbuf_size;
	uपूर्णांक64_t pos = (uपूर्णांक64_t) *ppos;
	uपूर्णांक32_t alloc_size = (uपूर्णांक32_t) rbuf->chan->alloc_size;
	माप_प्रकार पढ़ो_start = (माप_प्रकार) करो_भाग(pos, alloc_size);
	माप_प्रकार पढ़ो_subbuf = पढ़ो_start / subbuf_size;
	माप_प्रकार padding = rbuf->padding[पढ़ो_subbuf];
	माप_प्रकार nonpad_end = पढ़ो_subbuf * subbuf_size + subbuf_size - padding;
	काष्ठा page *pages[PIPE_DEF_BUFFERS];
	काष्ठा partial_page partial[PIPE_DEF_BUFFERS];
	काष्ठा splice_pipe_desc spd = अणु
		.pages = pages,
		.nr_pages = 0,
		.nr_pages_max = PIPE_DEF_BUFFERS,
		.partial = partial,
		.ops = &relay_pipe_buf_ops,
		.spd_release = relay_page_release,
	पूर्ण;
	sमाप_प्रकार ret;

	अगर (rbuf->subbufs_produced == rbuf->subbufs_consumed)
		वापस 0;
	अगर (splice_grow_spd(pipe, &spd))
		वापस -ENOMEM;

	/*
	 * Adjust पढ़ो len, अगर दीर्घer than what is available
	 */
	अगर (len > (subbuf_size - पढ़ो_start % subbuf_size))
		len = subbuf_size - पढ़ो_start % subbuf_size;

	subbuf_pages = rbuf->chan->alloc_size >> PAGE_SHIFT;
	pidx = (पढ़ो_start / PAGE_SIZE) % subbuf_pages;
	poff = पढ़ो_start & ~PAGE_MASK;
	nr_pages = min_t(अचिन्हित पूर्णांक, subbuf_pages, spd.nr_pages_max);

	क्रम (total_len = 0; spd.nr_pages < nr_pages; spd.nr_pages++) अणु
		अचिन्हित पूर्णांक this_len, this_end, निजी;
		अचिन्हित पूर्णांक cur_pos = पढ़ो_start + total_len;

		अगर (!len)
			अवरोध;

		this_len = min_t(अचिन्हित दीर्घ, len, PAGE_SIZE - poff);
		निजी = this_len;

		spd.pages[spd.nr_pages] = rbuf->page_array[pidx];
		spd.partial[spd.nr_pages].offset = poff;

		this_end = cur_pos + this_len;
		अगर (this_end >= nonpad_end) अणु
			this_len = nonpad_end - cur_pos;
			निजी = this_len + padding;
		पूर्ण
		spd.partial[spd.nr_pages].len = this_len;
		spd.partial[spd.nr_pages].निजी = निजी;

		len -= this_len;
		total_len += this_len;
		poff = 0;
		pidx = (pidx + 1) % subbuf_pages;

		अगर (this_end >= nonpad_end) अणु
			spd.nr_pages++;
			अवरोध;
		पूर्ण
	पूर्ण

	ret = 0;
	अगर (!spd.nr_pages)
		जाओ out;

	ret = *nonpad_ret = splice_to_pipe(pipe, &spd);
	अगर (ret < 0 || ret < total_len)
		जाओ out;

        अगर (पढ़ो_start + ret == nonpad_end)
                ret += padding;

out:
	splice_shrink_spd(&spd);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार relay_file_splice_पढ़ो(काष्ठा file *in,
				      loff_t *ppos,
				      काष्ठा pipe_inode_info *pipe,
				      माप_प्रकार len,
				      अचिन्हित पूर्णांक flags)
अणु
	sमाप_प्रकार spliced;
	पूर्णांक ret;
	पूर्णांक nonpad_ret = 0;

	ret = 0;
	spliced = 0;

	जबतक (len && !spliced) अणु
		ret = subbuf_splice_actor(in, ppos, pipe, len, flags, &nonpad_ret);
		अगर (ret < 0)
			अवरोध;
		अन्यथा अगर (!ret) अणु
			अगर (flags & SPLICE_F_NONBLOCK)
				ret = -EAGAIN;
			अवरोध;
		पूर्ण

		*ppos += ret;
		अगर (ret > len)
			len = 0;
		अन्यथा
			len -= ret;
		spliced += nonpad_ret;
		nonpad_ret = 0;
	पूर्ण

	अगर (spliced)
		वापस spliced;

	वापस ret;
पूर्ण

स्थिर काष्ठा file_operations relay_file_operations = अणु
	.खोलो		= relay_file_खोलो,
	.poll		= relay_file_poll,
	.mmap		= relay_file_mmap,
	.पढ़ो		= relay_file_पढ़ो,
	.llseek		= no_llseek,
	.release	= relay_file_release,
	.splice_पढ़ो	= relay_file_splice_पढ़ो,
पूर्ण;
EXPORT_SYMBOL_GPL(relay_file_operations);
