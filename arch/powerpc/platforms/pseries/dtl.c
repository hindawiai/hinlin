<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Virtual Processor Dispatch Trace Log
 *
 * (C) Copyright IBM Corporation 2009
 *
 * Author: Jeremy Kerr <jk@ozद_असल.org>
 */

#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <यंत्र/smp.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/dtl.h>
#समावेश <यंत्र/lppaca.h>
#समावेश <यंत्र/debugfs.h>
#समावेश <यंत्र/plpar_wrappers.h>
#समावेश <यंत्र/machdep.h>

काष्ठा dtl अणु
	काष्ठा dtl_entry	*buf;
	पूर्णांक			cpu;
	पूर्णांक			buf_entries;
	u64			last_idx;
	spinlock_t		lock;
पूर्ण;
अटल DEFINE_PER_CPU(काष्ठा dtl, cpu_dtl);

अटल u8 dtl_event_mask = DTL_LOG_ALL;


/*
 * Size of per-cpu log buffers. Firmware requires that the buffer करोes
 * not cross a 4k boundary.
 */
अटल पूर्णांक dtl_buf_entries = N_DISPATCH_LOG;

#अगर_घोषित CONFIG_VIRT_CPU_ACCOUNTING_NATIVE
काष्ठा dtl_ring अणु
	u64	ग_लिखो_index;
	काष्ठा dtl_entry *ग_लिखो_ptr;
	काष्ठा dtl_entry *buf;
	काष्ठा dtl_entry *buf_end;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा dtl_ring, dtl_rings);

अटल atomic_t dtl_count;

/*
 * The cpu accounting code controls the DTL ring buffer, and we get
 * given entries as they are processed.
 */
अटल व्योम consume_dtle(काष्ठा dtl_entry *dtle, u64 index)
अणु
	काष्ठा dtl_ring *dtlr = this_cpu_ptr(&dtl_rings);
	काष्ठा dtl_entry *wp = dtlr->ग_लिखो_ptr;
	काष्ठा lppaca *vpa = local_paca->lppaca_ptr;

	अगर (!wp)
		वापस;

	*wp = *dtle;
	barrier();

	/* check क्रम hypervisor ring buffer overflow, ignore this entry अगर so */
	अगर (index + N_DISPATCH_LOG < be64_to_cpu(vpa->dtl_idx))
		वापस;

	++wp;
	अगर (wp == dtlr->buf_end)
		wp = dtlr->buf;
	dtlr->ग_लिखो_ptr = wp;

	/* incrementing ग_लिखो_index makes the new entry visible */
	smp_wmb();
	++dtlr->ग_लिखो_index;
पूर्ण

अटल पूर्णांक dtl_start(काष्ठा dtl *dtl)
अणु
	काष्ठा dtl_ring *dtlr = &per_cpu(dtl_rings, dtl->cpu);

	dtlr->buf = dtl->buf;
	dtlr->buf_end = dtl->buf + dtl->buf_entries;
	dtlr->ग_लिखो_index = 0;

	/* setting ग_लिखो_ptr enables logging पूर्णांकo our buffer */
	smp_wmb();
	dtlr->ग_लिखो_ptr = dtl->buf;

	/* enable event logging */
	lppaca_of(dtl->cpu).dtl_enable_mask |= dtl_event_mask;

	dtl_consumer = consume_dtle;
	atomic_inc(&dtl_count);
	वापस 0;
पूर्ण

अटल व्योम dtl_stop(काष्ठा dtl *dtl)
अणु
	काष्ठा dtl_ring *dtlr = &per_cpu(dtl_rings, dtl->cpu);

	dtlr->ग_लिखो_ptr = शून्य;
	smp_wmb();

	dtlr->buf = शून्य;

	/* restore dtl_enable_mask */
	lppaca_of(dtl->cpu).dtl_enable_mask = DTL_LOG_PREEMPT;

	अगर (atomic_dec_and_test(&dtl_count))
		dtl_consumer = शून्य;
पूर्ण

अटल u64 dtl_current_index(काष्ठा dtl *dtl)
अणु
	वापस per_cpu(dtl_rings, dtl->cpu).ग_लिखो_index;
पूर्ण

#अन्यथा /* CONFIG_VIRT_CPU_ACCOUNTING_NATIVE */

अटल पूर्णांक dtl_start(काष्ठा dtl *dtl)
अणु
	अचिन्हित दीर्घ addr;
	पूर्णांक ret, hwcpu;

	/* Register our dtl buffer with the hypervisor. The HV expects the
	 * buffer size to be passed in the second word of the buffer */
	((u32 *)dtl->buf)[1] = cpu_to_be32(DISPATCH_LOG_BYTES);

	hwcpu = get_hard_smp_processor_id(dtl->cpu);
	addr = __pa(dtl->buf);
	ret = रेजिस्टर_dtl(hwcpu, addr);
	अगर (ret) अणु
		prपूर्णांकk(KERN_WARNING "%s: DTL registration for cpu %d (hw %d) "
		       "failed with %d\n", __func__, dtl->cpu, hwcpu, ret);
		वापस -EIO;
	पूर्ण

	/* set our initial buffer indices */
	lppaca_of(dtl->cpu).dtl_idx = 0;

	/* ensure that our updates to the lppaca fields have occurred beक्रमe
	 * we actually enable the logging */
	smp_wmb();

	/* enable event logging */
	lppaca_of(dtl->cpu).dtl_enable_mask = dtl_event_mask;

	वापस 0;
पूर्ण

अटल व्योम dtl_stop(काष्ठा dtl *dtl)
अणु
	पूर्णांक hwcpu = get_hard_smp_processor_id(dtl->cpu);

	lppaca_of(dtl->cpu).dtl_enable_mask = 0x0;

	unरेजिस्टर_dtl(hwcpu);
पूर्ण

अटल u64 dtl_current_index(काष्ठा dtl *dtl)
अणु
	वापस be64_to_cpu(lppaca_of(dtl->cpu).dtl_idx);
पूर्ण
#पूर्ण_अगर /* CONFIG_VIRT_CPU_ACCOUNTING_NATIVE */

अटल पूर्णांक dtl_enable(काष्ठा dtl *dtl)
अणु
	दीर्घ पूर्णांक n_entries;
	दीर्घ पूर्णांक rc;
	काष्ठा dtl_entry *buf = शून्य;

	अगर (!dtl_cache)
		वापस -ENOMEM;

	/* only allow one पढ़ोer */
	अगर (dtl->buf)
		वापस -EBUSY;

	/* ensure there are no other conflicting dtl users */
	अगर (!पढ़ो_trylock(&dtl_access_lock))
		वापस -EBUSY;

	n_entries = dtl_buf_entries;
	buf = kmem_cache_alloc_node(dtl_cache, GFP_KERNEL, cpu_to_node(dtl->cpu));
	अगर (!buf) अणु
		prपूर्णांकk(KERN_WARNING "%s: buffer alloc failed for cpu %d\n",
				__func__, dtl->cpu);
		पढ़ो_unlock(&dtl_access_lock);
		वापस -ENOMEM;
	पूर्ण

	spin_lock(&dtl->lock);
	rc = -EBUSY;
	अगर (!dtl->buf) अणु
		/* store the original allocation size क्रम use during पढ़ो */
		dtl->buf_entries = n_entries;
		dtl->buf = buf;
		dtl->last_idx = 0;
		rc = dtl_start(dtl);
		अगर (rc)
			dtl->buf = शून्य;
	पूर्ण
	spin_unlock(&dtl->lock);

	अगर (rc) अणु
		पढ़ो_unlock(&dtl_access_lock);
		kmem_cache_मुक्त(dtl_cache, buf);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम dtl_disable(काष्ठा dtl *dtl)
अणु
	spin_lock(&dtl->lock);
	dtl_stop(dtl);
	kmem_cache_मुक्त(dtl_cache, dtl->buf);
	dtl->buf = शून्य;
	dtl->buf_entries = 0;
	spin_unlock(&dtl->lock);
	पढ़ो_unlock(&dtl_access_lock);
पूर्ण

/* file पूर्णांकerface */

अटल पूर्णांक dtl_file_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा dtl *dtl = inode->i_निजी;
	पूर्णांक rc;

	rc = dtl_enable(dtl);
	अगर (rc)
		वापस rc;

	filp->निजी_data = dtl;
	वापस 0;
पूर्ण

अटल पूर्णांक dtl_file_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा dtl *dtl = inode->i_निजी;
	dtl_disable(dtl);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार dtl_file_पढ़ो(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार len,
		loff_t *pos)
अणु
	दीर्घ पूर्णांक rc, n_पढ़ो, n_req, पढ़ो_size;
	काष्ठा dtl *dtl;
	u64 cur_idx, last_idx, i;

	अगर ((len % माप(काष्ठा dtl_entry)) != 0)
		वापस -EINVAL;

	dtl = filp->निजी_data;

	/* requested number of entries to पढ़ो */
	n_req = len / माप(काष्ठा dtl_entry);

	/* actual number of entries पढ़ो */
	n_पढ़ो = 0;

	spin_lock(&dtl->lock);

	cur_idx = dtl_current_index(dtl);
	last_idx = dtl->last_idx;

	अगर (last_idx + dtl->buf_entries <= cur_idx)
		last_idx = cur_idx - dtl->buf_entries + 1;

	अगर (last_idx + n_req > cur_idx)
		n_req = cur_idx - last_idx;

	अगर (n_req > 0)
		dtl->last_idx = last_idx + n_req;

	spin_unlock(&dtl->lock);

	अगर (n_req <= 0)
		वापस 0;

	i = last_idx % dtl->buf_entries;

	/* पढ़ो the tail of the buffer अगर we've wrapped */
	अगर (i + n_req > dtl->buf_entries) अणु
		पढ़ो_size = dtl->buf_entries - i;

		rc = copy_to_user(buf, &dtl->buf[i],
				पढ़ो_size * माप(काष्ठा dtl_entry));
		अगर (rc)
			वापस -EFAULT;

		i = 0;
		n_req -= पढ़ो_size;
		n_पढ़ो += पढ़ो_size;
		buf += पढ़ो_size * माप(काष्ठा dtl_entry);
	पूर्ण

	/* .. and now the head */
	rc = copy_to_user(buf, &dtl->buf[i], n_req * माप(काष्ठा dtl_entry));
	अगर (rc)
		वापस -EFAULT;

	n_पढ़ो += n_req;

	वापस n_पढ़ो * माप(काष्ठा dtl_entry);
पूर्ण

अटल स्थिर काष्ठा file_operations dtl_fops = अणु
	.खोलो		= dtl_file_खोलो,
	.release	= dtl_file_release,
	.पढ़ो		= dtl_file_पढ़ो,
	.llseek		= no_llseek,
पूर्ण;

अटल काष्ठा dentry *dtl_dir;

अटल व्योम dtl_setup_file(काष्ठा dtl *dtl)
अणु
	अक्षर name[10];

	प्र_लिखो(name, "cpu-%d", dtl->cpu);

	debugfs_create_file(name, 0400, dtl_dir, dtl, &dtl_fops);
पूर्ण

अटल पूर्णांक dtl_init(व्योम)
अणु
	पूर्णांक i;

	अगर (!firmware_has_feature(FW_FEATURE_SPLPAR))
		वापस -ENODEV;

	/* set up common debugfs काष्ठाure */

	dtl_dir = debugfs_create_dir("dtl", घातerpc_debugfs_root);

	debugfs_create_x8("dtl_event_mask", 0600, dtl_dir, &dtl_event_mask);
	debugfs_create_u32("dtl_buf_entries", 0400, dtl_dir, &dtl_buf_entries);

	/* set up the per-cpu log काष्ठाures */
	क्रम_each_possible_cpu(i) अणु
		काष्ठा dtl *dtl = &per_cpu(cpu_dtl, i);
		spin_lock_init(&dtl->lock);
		dtl->cpu = i;

		dtl_setup_file(dtl);
	पूर्ण

	वापस 0;
पूर्ण
machine_arch_initcall(pseries, dtl_init);
