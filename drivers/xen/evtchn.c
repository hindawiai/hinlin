<शैली गुरु>
/******************************************************************************
 * evtchn.c
 *
 * Driver क्रम receiving and demuxing event-channel संकेतs.
 *
 * Copyright (c) 2004-2005, K A Fraser
 * Multi-process extensions Copyright (c) 2004, Steven Smith
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation; or, when distributed
 * separately from the Linux kernel or incorporated पूर्णांकo other
 * software packages, subject to the following license:
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this source file (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modअगरy,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#घोषणा pr_fmt(fmt) "xen:" KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/major.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/poll.h>
#समावेश <linux/irq.h>
#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <linux/cpu.h>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <xen/xen.h>
#समावेश <xen/events.h>
#समावेश <xen/evtchn.h>
#समावेश <xen/xen-ops.h>
#समावेश <यंत्र/xen/hypervisor.h>

काष्ठा per_user_data अणु
	काष्ठा mutex bind_mutex; /* serialize bind/unbind operations */
	काष्ठा rb_root evtchns;
	अचिन्हित पूर्णांक nr_evtchns;

	/* Notअगरication ring, accessed via /dev/xen/evtchn. */
	अचिन्हित पूर्णांक ring_size;
	evtchn_port_t *ring;
	अचिन्हित पूर्णांक ring_cons, ring_prod, ring_overflow;
	काष्ठा mutex ring_cons_mutex; /* protect against concurrent पढ़ोers */
	spinlock_t ring_prod_lock; /* product against concurrent पूर्णांकerrupts */

	/* Processes रुको on this queue when ring is empty. */
	रुको_queue_head_t evtchn_रुको;
	काष्ठा fasync_काष्ठा *evtchn_async_queue;
	स्थिर अक्षर *name;

	करोmid_t restrict_करोmid;
पूर्ण;

#घोषणा UNRESTRICTED_DOMID ((करोmid_t)-1)

काष्ठा user_evtchn अणु
	काष्ठा rb_node node;
	काष्ठा per_user_data *user;
	evtchn_port_t port;
	bool enabled;
पूर्ण;

अटल व्योम evtchn_मुक्त_ring(evtchn_port_t *ring)
अणु
	kvमुक्त(ring);
पूर्ण

अटल अचिन्हित पूर्णांक evtchn_ring_offset(काष्ठा per_user_data *u,
				       अचिन्हित पूर्णांक idx)
अणु
	वापस idx & (u->ring_size - 1);
पूर्ण

अटल evtchn_port_t *evtchn_ring_entry(काष्ठा per_user_data *u,
					अचिन्हित पूर्णांक idx)
अणु
	वापस u->ring + evtchn_ring_offset(u, idx);
पूर्ण

अटल पूर्णांक add_evtchn(काष्ठा per_user_data *u, काष्ठा user_evtchn *evtchn)
अणु
	काष्ठा rb_node **new = &(u->evtchns.rb_node), *parent = शून्य;

	u->nr_evtchns++;

	जबतक (*new) अणु
		काष्ठा user_evtchn *this;

		this = rb_entry(*new, काष्ठा user_evtchn, node);

		parent = *new;
		अगर (this->port < evtchn->port)
			new = &((*new)->rb_left);
		अन्यथा अगर (this->port > evtchn->port)
			new = &((*new)->rb_right);
		अन्यथा
			वापस -EEXIST;
	पूर्ण

	/* Add new node and rebalance tree. */
	rb_link_node(&evtchn->node, parent, new);
	rb_insert_color(&evtchn->node, &u->evtchns);

	वापस 0;
पूर्ण

अटल व्योम del_evtchn(काष्ठा per_user_data *u, काष्ठा user_evtchn *evtchn)
अणु
	u->nr_evtchns--;
	rb_erase(&evtchn->node, &u->evtchns);
	kमुक्त(evtchn);
पूर्ण

अटल काष्ठा user_evtchn *find_evtchn(काष्ठा per_user_data *u,
				       evtchn_port_t port)
अणु
	काष्ठा rb_node *node = u->evtchns.rb_node;

	जबतक (node) अणु
		काष्ठा user_evtchn *evtchn;

		evtchn = rb_entry(node, काष्ठा user_evtchn, node);

		अगर (evtchn->port < port)
			node = node->rb_left;
		अन्यथा अगर (evtchn->port > port)
			node = node->rb_right;
		अन्यथा
			वापस evtchn;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल irqवापस_t evtchn_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा user_evtchn *evtchn = data;
	काष्ठा per_user_data *u = evtchn->user;
	अचिन्हित पूर्णांक prod, cons;

	WARN(!evtchn->enabled,
	     "Interrupt for port %u, but apparently not enabled; per-user %p\n",
	     evtchn->port, u);

	evtchn->enabled = false;

	spin_lock(&u->ring_prod_lock);

	prod = READ_ONCE(u->ring_prod);
	cons = READ_ONCE(u->ring_cons);

	अगर ((prod - cons) < u->ring_size) अणु
		*evtchn_ring_entry(u, prod) = evtchn->port;
		smp_wmb(); /* Ensure ring contents visible */
		WRITE_ONCE(u->ring_prod, prod + 1);
		अगर (cons == prod) अणु
			wake_up_पूर्णांकerruptible(&u->evtchn_रुको);
			समाप्त_fasync(&u->evtchn_async_queue,
				    SIGIO, POLL_IN);
		पूर्ण
	पूर्ण अन्यथा
		u->ring_overflow = 1;

	spin_unlock(&u->ring_prod_lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल sमाप_प्रकार evtchn_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			   माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक c, p, bytes1 = 0, bytes2 = 0;
	काष्ठा per_user_data *u = file->निजी_data;

	/* Whole number of ports. */
	count &= ~(माप(evtchn_port_t)-1);

	अगर (count == 0)
		वापस 0;

	अगर (count > PAGE_SIZE)
		count = PAGE_SIZE;

	क्रम (;;) अणु
		mutex_lock(&u->ring_cons_mutex);

		rc = -EFBIG;
		अगर (u->ring_overflow)
			जाओ unlock_out;

		c = READ_ONCE(u->ring_cons);
		p = READ_ONCE(u->ring_prod);
		अगर (c != p)
			अवरोध;

		mutex_unlock(&u->ring_cons_mutex);

		अगर (file->f_flags & O_NONBLOCK)
			वापस -EAGAIN;

		rc = रुको_event_पूर्णांकerruptible(u->evtchn_रुको,
			READ_ONCE(u->ring_cons) != READ_ONCE(u->ring_prod));
		अगर (rc)
			वापस rc;
	पूर्ण

	/* Byte lengths of two chunks. Chunk split (अगर any) is at ring wrap. */
	अगर (((c ^ p) & u->ring_size) != 0) अणु
		bytes1 = (u->ring_size - evtchn_ring_offset(u, c)) *
			माप(evtchn_port_t);
		bytes2 = evtchn_ring_offset(u, p) * माप(evtchn_port_t);
	पूर्ण अन्यथा अणु
		bytes1 = (p - c) * माप(evtchn_port_t);
		bytes2 = 0;
	पूर्ण

	/* Truncate chunks according to caller's maximum byte count. */
	अगर (bytes1 > count) अणु
		bytes1 = count;
		bytes2 = 0;
	पूर्ण अन्यथा अगर ((bytes1 + bytes2) > count) अणु
		bytes2 = count - bytes1;
	पूर्ण

	rc = -EFAULT;
	smp_rmb(); /* Ensure that we see the port beक्रमe we copy it. */
	अगर (copy_to_user(buf, evtchn_ring_entry(u, c), bytes1) ||
	    ((bytes2 != 0) &&
	     copy_to_user(&buf[bytes1], &u->ring[0], bytes2)))
		जाओ unlock_out;

	WRITE_ONCE(u->ring_cons, c + (bytes1 + bytes2) / माप(evtchn_port_t));
	rc = bytes1 + bytes2;

 unlock_out:
	mutex_unlock(&u->ring_cons_mutex);
	वापस rc;
पूर्ण

अटल sमाप_प्रकार evtchn_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			    माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक rc, i;
	evtchn_port_t *kbuf = (evtchn_port_t *)__get_मुक्त_page(GFP_KERNEL);
	काष्ठा per_user_data *u = file->निजी_data;

	अगर (kbuf == शून्य)
		वापस -ENOMEM;

	/* Whole number of ports. */
	count &= ~(माप(evtchn_port_t)-1);

	rc = 0;
	अगर (count == 0)
		जाओ out;

	अगर (count > PAGE_SIZE)
		count = PAGE_SIZE;

	rc = -EFAULT;
	अगर (copy_from_user(kbuf, buf, count) != 0)
		जाओ out;

	mutex_lock(&u->bind_mutex);

	क्रम (i = 0; i < (count/माप(evtchn_port_t)); i++) अणु
		evtchn_port_t port = kbuf[i];
		काष्ठा user_evtchn *evtchn;

		evtchn = find_evtchn(u, port);
		अगर (evtchn && !evtchn->enabled) अणु
			evtchn->enabled = true;
			xen_irq_lateeoi(irq_from_evtchn(port), 0);
		पूर्ण
	पूर्ण

	mutex_unlock(&u->bind_mutex);

	rc = count;

 out:
	मुक्त_page((अचिन्हित दीर्घ)kbuf);
	वापस rc;
पूर्ण

अटल पूर्णांक evtchn_resize_ring(काष्ठा per_user_data *u)
अणु
	अचिन्हित पूर्णांक new_size;
	evtchn_port_t *new_ring, *old_ring;

	/*
	 * Ensure the ring is large enough to capture all possible
	 * events. i.e., one मुक्त slot क्रम each bound event.
	 */
	अगर (u->nr_evtchns <= u->ring_size)
		वापस 0;

	अगर (u->ring_size == 0)
		new_size = 64;
	अन्यथा
		new_size = 2 * u->ring_size;

	new_ring = kvदो_स्मृति_array(new_size, माप(*new_ring), GFP_KERNEL);
	अगर (!new_ring)
		वापस -ENOMEM;

	old_ring = u->ring;

	/*
	 * Access to the ring contents is serialized by either the
	 * prod /or/ cons lock so take both when resizing.
	 */
	mutex_lock(&u->ring_cons_mutex);
	spin_lock_irq(&u->ring_prod_lock);

	/*
	 * Copy the old ring contents to the new ring.
	 *
	 * To take care of wrapping, a full ring, and the new index
	 * poपूर्णांकing पूर्णांकo the second half, simply copy the old contents
	 * twice.
	 *
	 * +---------+    +------------------+
	 * |34567  12| -> |34567  1234567  12|
	 * +-----p-c-+    +-------c------p---+
	 */
	स_नकल(new_ring, old_ring, u->ring_size * माप(*u->ring));
	स_नकल(new_ring + u->ring_size, old_ring,
	       u->ring_size * माप(*u->ring));

	u->ring = new_ring;
	u->ring_size = new_size;

	spin_unlock_irq(&u->ring_prod_lock);
	mutex_unlock(&u->ring_cons_mutex);

	evtchn_मुक्त_ring(old_ring);

	वापस 0;
पूर्ण

अटल पूर्णांक evtchn_bind_to_user(काष्ठा per_user_data *u, evtchn_port_t port)
अणु
	काष्ठा user_evtchn *evtchn;
	काष्ठा evtchn_बंद बंद;
	पूर्णांक rc = 0;

	/*
	 * Ports are never reused, so every caller should pass in a
	 * unique port.
	 *
	 * (Locking not necessary because we haven't रेजिस्टरed the
	 * पूर्णांकerrupt handler yet, and our caller has alपढ़ोy
	 * serialized bind operations.)
	 */

	evtchn = kzalloc(माप(*evtchn), GFP_KERNEL);
	अगर (!evtchn)
		वापस -ENOMEM;

	evtchn->user = u;
	evtchn->port = port;
	evtchn->enabled = true; /* start enabled */

	rc = add_evtchn(u, evtchn);
	अगर (rc < 0)
		जाओ err;

	rc = evtchn_resize_ring(u);
	अगर (rc < 0)
		जाओ err;

	rc = bind_evtchn_to_irqhandler_lateeoi(port, evtchn_पूर्णांकerrupt, 0,
					       u->name, evtchn);
	अगर (rc < 0)
		जाओ err;

	rc = evtchn_make_refcounted(port);
	वापस rc;

err:
	/* bind failed, should बंद the port now */
	बंद.port = port;
	अगर (HYPERVISOR_event_channel_op(EVTCHNOP_बंद, &बंद) != 0)
		BUG();
	del_evtchn(u, evtchn);
	वापस rc;
पूर्ण

अटल व्योम evtchn_unbind_from_user(काष्ठा per_user_data *u,
				    काष्ठा user_evtchn *evtchn)
अणु
	पूर्णांक irq = irq_from_evtchn(evtchn->port);

	BUG_ON(irq < 0);

	unbind_from_irqhandler(irq, evtchn);

	del_evtchn(u, evtchn);
पूर्ण

अटल दीर्घ evtchn_ioctl(काष्ठा file *file,
			 अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक rc;
	काष्ठा per_user_data *u = file->निजी_data;
	व्योम __user *uarg = (व्योम __user *) arg;

	/* Prevent bind from racing with unbind */
	mutex_lock(&u->bind_mutex);

	चयन (cmd) अणु
	हाल IOCTL_EVTCHN_BIND_VIRQ: अणु
		काष्ठा ioctl_evtchn_bind_virq bind;
		काष्ठा evtchn_bind_virq bind_virq;

		rc = -EACCES;
		अगर (u->restrict_करोmid != UNRESTRICTED_DOMID)
			अवरोध;

		rc = -EFAULT;
		अगर (copy_from_user(&bind, uarg, माप(bind)))
			अवरोध;

		bind_virq.virq = bind.virq;
		bind_virq.vcpu = xen_vcpu_nr(0);
		rc = HYPERVISOR_event_channel_op(EVTCHNOP_bind_virq,
						 &bind_virq);
		अगर (rc != 0)
			अवरोध;

		rc = evtchn_bind_to_user(u, bind_virq.port);
		अगर (rc == 0)
			rc = bind_virq.port;
		अवरोध;
	पूर्ण

	हाल IOCTL_EVTCHN_BIND_INTERDOMAIN: अणु
		काष्ठा ioctl_evtchn_bind_पूर्णांकerकरोमुख्य bind;
		काष्ठा evtchn_bind_पूर्णांकerकरोमुख्य bind_पूर्णांकerकरोमुख्य;

		rc = -EFAULT;
		अगर (copy_from_user(&bind, uarg, माप(bind)))
			अवरोध;

		rc = -EACCES;
		अगर (u->restrict_करोmid != UNRESTRICTED_DOMID &&
		    u->restrict_करोmid != bind.remote_करोमुख्य)
			अवरोध;

		bind_पूर्णांकerकरोमुख्य.remote_करोm  = bind.remote_करोमुख्य;
		bind_पूर्णांकerकरोमुख्य.remote_port = bind.remote_port;
		rc = HYPERVISOR_event_channel_op(EVTCHNOP_bind_पूर्णांकerकरोमुख्य,
						 &bind_पूर्णांकerकरोमुख्य);
		अगर (rc != 0)
			अवरोध;

		rc = evtchn_bind_to_user(u, bind_पूर्णांकerकरोमुख्य.local_port);
		अगर (rc == 0)
			rc = bind_पूर्णांकerकरोमुख्य.local_port;
		अवरोध;
	पूर्ण

	हाल IOCTL_EVTCHN_BIND_UNBOUND_PORT: अणु
		काष्ठा ioctl_evtchn_bind_unbound_port bind;
		काष्ठा evtchn_alloc_unbound alloc_unbound;

		rc = -EACCES;
		अगर (u->restrict_करोmid != UNRESTRICTED_DOMID)
			अवरोध;

		rc = -EFAULT;
		अगर (copy_from_user(&bind, uarg, माप(bind)))
			अवरोध;

		alloc_unbound.करोm        = DOMID_SELF;
		alloc_unbound.remote_करोm = bind.remote_करोमुख्य;
		rc = HYPERVISOR_event_channel_op(EVTCHNOP_alloc_unbound,
						 &alloc_unbound);
		अगर (rc != 0)
			अवरोध;

		rc = evtchn_bind_to_user(u, alloc_unbound.port);
		अगर (rc == 0)
			rc = alloc_unbound.port;
		अवरोध;
	पूर्ण

	हाल IOCTL_EVTCHN_UNBIND: अणु
		काष्ठा ioctl_evtchn_unbind unbind;
		काष्ठा user_evtchn *evtchn;

		rc = -EFAULT;
		अगर (copy_from_user(&unbind, uarg, माप(unbind)))
			अवरोध;

		rc = -EINVAL;
		अगर (unbind.port >= xen_evtchn_nr_channels())
			अवरोध;

		rc = -ENOTCONN;
		evtchn = find_evtchn(u, unbind.port);
		अगर (!evtchn)
			अवरोध;

		disable_irq(irq_from_evtchn(unbind.port));
		evtchn_unbind_from_user(u, evtchn);
		rc = 0;
		अवरोध;
	पूर्ण

	हाल IOCTL_EVTCHN_NOTIFY: अणु
		काष्ठा ioctl_evtchn_notअगरy notअगरy;
		काष्ठा user_evtchn *evtchn;

		rc = -EFAULT;
		अगर (copy_from_user(&notअगरy, uarg, माप(notअगरy)))
			अवरोध;

		rc = -ENOTCONN;
		evtchn = find_evtchn(u, notअगरy.port);
		अगर (evtchn) अणु
			notअगरy_remote_via_evtchn(notअगरy.port);
			rc = 0;
		पूर्ण
		अवरोध;
	पूर्ण

	हाल IOCTL_EVTCHN_RESET: अणु
		/* Initialise the ring to empty. Clear errors. */
		mutex_lock(&u->ring_cons_mutex);
		spin_lock_irq(&u->ring_prod_lock);
		WRITE_ONCE(u->ring_cons, 0);
		WRITE_ONCE(u->ring_prod, 0);
		u->ring_overflow = 0;
		spin_unlock_irq(&u->ring_prod_lock);
		mutex_unlock(&u->ring_cons_mutex);
		rc = 0;
		अवरोध;
	पूर्ण

	हाल IOCTL_EVTCHN_RESTRICT_DOMID: अणु
		काष्ठा ioctl_evtchn_restrict_करोmid ierd;

		rc = -EACCES;
		अगर (u->restrict_करोmid != UNRESTRICTED_DOMID)
			अवरोध;

		rc = -EFAULT;
		अगर (copy_from_user(&ierd, uarg, माप(ierd)))
		    अवरोध;

		rc = -EINVAL;
		अगर (ierd.करोmid == 0 || ierd.करोmid >= DOMID_FIRST_RESERVED)
			अवरोध;

		u->restrict_करोmid = ierd.करोmid;
		rc = 0;

		अवरोध;
	पूर्ण

	शेष:
		rc = -ENOSYS;
		अवरोध;
	पूर्ण
	mutex_unlock(&u->bind_mutex);

	वापस rc;
पूर्ण

अटल __poll_t evtchn_poll(काष्ठा file *file, poll_table *रुको)
अणु
	__poll_t mask = EPOLLOUT | EPOLLWRNORM;
	काष्ठा per_user_data *u = file->निजी_data;

	poll_रुको(file, &u->evtchn_रुको, रुको);
	अगर (READ_ONCE(u->ring_cons) != READ_ONCE(u->ring_prod))
		mask |= EPOLLIN | EPOLLRDNORM;
	अगर (u->ring_overflow)
		mask = EPOLLERR;
	वापस mask;
पूर्ण

अटल पूर्णांक evtchn_fasync(पूर्णांक fd, काष्ठा file *filp, पूर्णांक on)
अणु
	काष्ठा per_user_data *u = filp->निजी_data;
	वापस fasync_helper(fd, filp, on, &u->evtchn_async_queue);
पूर्ण

अटल पूर्णांक evtchn_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा per_user_data *u;

	u = kzalloc(माप(*u), GFP_KERNEL);
	अगर (u == शून्य)
		वापस -ENOMEM;

	u->name = kaप्र_लिखो(GFP_KERNEL, "evtchn:%s", current->comm);
	अगर (u->name == शून्य) अणु
		kमुक्त(u);
		वापस -ENOMEM;
	पूर्ण

	init_रुकोqueue_head(&u->evtchn_रुको);

	mutex_init(&u->bind_mutex);
	mutex_init(&u->ring_cons_mutex);
	spin_lock_init(&u->ring_prod_lock);

	u->restrict_करोmid = UNRESTRICTED_DOMID;

	filp->निजी_data = u;

	वापस stream_खोलो(inode, filp);
पूर्ण

अटल पूर्णांक evtchn_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा per_user_data *u = filp->निजी_data;
	काष्ठा rb_node *node;

	जबतक ((node = u->evtchns.rb_node)) अणु
		काष्ठा user_evtchn *evtchn;

		evtchn = rb_entry(node, काष्ठा user_evtchn, node);
		disable_irq(irq_from_evtchn(evtchn->port));
		evtchn_unbind_from_user(u, evtchn);
	पूर्ण

	evtchn_मुक्त_ring(u->ring);
	kमुक्त(u->name);
	kमुक्त(u);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations evtchn_fops = अणु
	.owner   = THIS_MODULE,
	.पढ़ो    = evtchn_पढ़ो,
	.ग_लिखो   = evtchn_ग_लिखो,
	.unlocked_ioctl = evtchn_ioctl,
	.poll    = evtchn_poll,
	.fasync  = evtchn_fasync,
	.खोलो    = evtchn_खोलो,
	.release = evtchn_release,
	.llseek	 = no_llseek,
पूर्ण;

अटल काष्ठा miscdevice evtchn_miscdev = अणु
	.minor        = MISC_DYNAMIC_MINOR,
	.name         = "xen/evtchn",
	.fops         = &evtchn_fops,
पूर्ण;
अटल पूर्णांक __init evtchn_init(व्योम)
अणु
	पूर्णांक err;

	अगर (!xen_करोमुख्य())
		वापस -ENODEV;

	/* Create '/dev/xen/evtchn'. */
	err = misc_रेजिस्टर(&evtchn_miscdev);
	अगर (err != 0) अणु
		pr_err("Could not register /dev/xen/evtchn\n");
		वापस err;
	पूर्ण

	pr_info("Event-channel device installed\n");

	वापस 0;
पूर्ण

अटल व्योम __निकास evtchn_cleanup(व्योम)
अणु
	misc_deरेजिस्टर(&evtchn_miscdev);
पूर्ण

module_init(evtchn_init);
module_निकास(evtchn_cleanup);

MODULE_LICENSE("GPL");
