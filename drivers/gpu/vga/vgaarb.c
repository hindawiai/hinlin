<शैली गुरु>
/*
 * vgaarb.c: Implements the VGA arbitration. For details refer to
 * Documentation/gpu/vgaarbiter.rst
 *
 *
 * (C) Copyright 2005 Benjamin Herrenschmidt <benh@kernel.crashing.org>
 * (C) Copyright 2007 Paulo R. Zanoni <przanoni@gmail.com>
 * (C) Copyright 2007, 2009 Tiago Vignatti <vignatti@मुक्तdesktop.org>
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS
 * IN THE SOFTWARE.
 *
 */

#घोषणा pr_fmt(fmt) "vgaarb: " fmt

#घोषणा vgaarb_dbg(dev, fmt, arg...)	dev_dbg(dev, "vgaarb: " fmt, ##arg)
#घोषणा vgaarb_info(dev, fmt, arg...)	dev_info(dev, "vgaarb: " fmt, ##arg)
#घोषणा vgaarb_err(dev, fmt, arg...)	dev_err(dev, "vgaarb: " fmt, ##arg)

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/रुको.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/poll.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/screen_info.h>
#समावेश <linux/vt.h>
#समावेश <linux/console.h>

#समावेश <linux/uaccess.h>

#समावेश <linux/vgaarb.h>

अटल व्योम vga_arbiter_notअगरy_clients(व्योम);
/*
 * We keep a list of all vga devices in the प्रणाली to speed
 * up the various operations of the arbiter
 */
काष्ठा vga_device अणु
	काष्ठा list_head list;
	काष्ठा pci_dev *pdev;
	अचिन्हित पूर्णांक decodes;	/* what करोes it decodes */
	अचिन्हित पूर्णांक owns;	/* what करोes it owns */
	अचिन्हित पूर्णांक locks;	/* what करोes it locks */
	अचिन्हित पूर्णांक io_lock_cnt;	/* legacy IO lock count */
	अचिन्हित पूर्णांक mem_lock_cnt;	/* legacy MEM lock count */
	अचिन्हित पूर्णांक io_norm_cnt;	/* normal IO count */
	अचिन्हित पूर्णांक mem_norm_cnt;	/* normal MEM count */
	bool bridge_has_one_vga;
	/* allow IRQ enable/disable hook */
	व्योम *cookie;
	व्योम (*irq_set_state)(व्योम *cookie, bool enable);
	अचिन्हित पूर्णांक (*set_vga_decode)(व्योम *cookie, bool decode);
पूर्ण;

अटल LIST_HEAD(vga_list);
अटल पूर्णांक vga_count, vga_decode_count;
अटल bool vga_arbiter_used;
अटल DEFINE_SPINLOCK(vga_lock);
अटल DECLARE_WAIT_QUEUE_HEAD(vga_रुको_queue);


अटल स्थिर अक्षर *vga_iostate_to_str(अचिन्हित पूर्णांक iostate)
अणु
	/* Ignore VGA_RSRC_IO and VGA_RSRC_MEM */
	iostate &= VGA_RSRC_LEGACY_IO | VGA_RSRC_LEGACY_MEM;
	चयन (iostate) अणु
	हाल VGA_RSRC_LEGACY_IO | VGA_RSRC_LEGACY_MEM:
		वापस "io+mem";
	हाल VGA_RSRC_LEGACY_IO:
		वापस "io";
	हाल VGA_RSRC_LEGACY_MEM:
		वापस "mem";
	पूर्ण
	वापस "none";
पूर्ण

अटल पूर्णांक vga_str_to_iostate(अक्षर *buf, पूर्णांक str_size, पूर्णांक *io_state)
अणु
	/* we could in theory hand out locks on IO and mem
	 * separately to userspace but it can cause deadlocks */
	अगर (म_भेदन(buf, "none", 4) == 0) अणु
		*io_state = VGA_RSRC_NONE;
		वापस 1;
	पूर्ण

	/* XXX We're not chekcing the str_size! */
	अगर (म_भेदन(buf, "io+mem", 6) == 0)
		जाओ both;
	अन्यथा अगर (म_भेदन(buf, "io", 2) == 0)
		जाओ both;
	अन्यथा अगर (म_भेदन(buf, "mem", 3) == 0)
		जाओ both;
	वापस 0;
both:
	*io_state = VGA_RSRC_LEGACY_IO | VGA_RSRC_LEGACY_MEM;
	वापस 1;
पूर्ण

/* this is only used a cookie - it should not be dereferenced */
अटल काष्ठा pci_dev *vga_शेष;

अटल व्योम vga_arb_device_card_gone(काष्ठा pci_dev *pdev);

/* Find somebody in our list */
अटल काष्ठा vga_device *vgadev_find(काष्ठा pci_dev *pdev)
अणु
	काष्ठा vga_device *vgadev;

	list_क्रम_each_entry(vgadev, &vga_list, list)
		अगर (pdev == vgadev->pdev)
			वापस vgadev;
	वापस शून्य;
पूर्ण

/**
 * vga_शेष_device - वापस the शेष VGA device, क्रम vgacon
 *
 * This can be defined by the platक्रमm. The शेष implementation
 * is rather dumb and will probably only work properly on single
 * vga card setups and/or x86 platक्रमms.
 *
 * If your VGA शेष device is not PCI, you'll have to वापस
 * शून्य here. In this हाल, I assume it will not conflict with
 * any PCI card. If this is not true, I'll have to define two archs
 * hooks क्रम enabling/disabling the VGA शेष device अगर that is
 * possible. This may be a problem with real _ISA_ VGA cards, in
 * addition to a PCI one. I करोn't know at this poपूर्णांक how to deal
 * with that card. Can theirs IOs be disabled at all ? If not, then
 * I suppose it's a matter of having the proper arch hook telling
 * us about it, so we basically never allow anybody to succeed a
 * vga_get()...
 */
काष्ठा pci_dev *vga_शेष_device(व्योम)
अणु
	वापस vga_शेष;
पूर्ण
EXPORT_SYMBOL_GPL(vga_शेष_device);

व्योम vga_set_शेष_device(काष्ठा pci_dev *pdev)
अणु
	अगर (vga_शेष == pdev)
		वापस;

	pci_dev_put(vga_शेष);
	vga_शेष = pci_dev_get(pdev);
पूर्ण

/**
 * vga_हटाओ_vgacon - deactivete vga console
 *
 * Unbind and unरेजिस्टर vgacon in हाल pdev is the शेष vga
 * device.  Can be called by gpu drivers on initialization to make
 * sure vga रेजिस्टर access करोne by vgacon will not disturb the
 * device.
 *
 * @pdev: pci device.
 */
#अगर !defined(CONFIG_VGA_CONSOLE)
पूर्णांक vga_हटाओ_vgacon(काष्ठा pci_dev *pdev)
अणु
	वापस 0;
पूर्ण
#या_अगर !defined(CONFIG_DUMMY_CONSOLE)
पूर्णांक vga_हटाओ_vgacon(काष्ठा pci_dev *pdev)
अणु
	वापस -ENODEV;
पूर्ण
#अन्यथा
पूर्णांक vga_हटाओ_vgacon(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक ret = 0;

	अगर (pdev != vga_शेष)
		वापस 0;
	vgaarb_info(&pdev->dev, "deactivate vga console\n");

	console_lock();
	अगर (con_is_bound(&vga_con))
		ret = करो_take_over_console(&dummy_con, 0,
					   MAX_NR_CONSOLES - 1, 1);
	अगर (ret == 0) अणु
		ret = करो_unरेजिस्टर_con_driver(&vga_con);

		/* Ignore "already unregistered". */
		अगर (ret == -ENODEV)
			ret = 0;
	पूर्ण
	console_unlock();

	वापस ret;
पूर्ण
#पूर्ण_अगर
EXPORT_SYMBOL(vga_हटाओ_vgacon);

अटल अंतरभूत व्योम vga_irq_set_state(काष्ठा vga_device *vgadev, bool state)
अणु
	अगर (vgadev->irq_set_state)
		vgadev->irq_set_state(vgadev->cookie, state);
पूर्ण


/* If we करोn't ever use VGA arb we should aव्योम
   turning off anything anywhere due to old X servers getting
   confused about the boot device not being VGA */
अटल व्योम vga_check_first_use(व्योम)
अणु
	/* we should inक्रमm all GPUs in the प्रणाली that
	 * VGA arb has occurred and to try and disable resources
	 * अगर they can */
	अगर (!vga_arbiter_used) अणु
		vga_arbiter_used = true;
		vga_arbiter_notअगरy_clients();
	पूर्ण
पूर्ण

अटल काष्ठा vga_device *__vga_tryget(काष्ठा vga_device *vgadev,
				       अचिन्हित पूर्णांक rsrc)
अणु
	काष्ठा device *dev = &vgadev->pdev->dev;
	अचिन्हित पूर्णांक wants, legacy_wants, match;
	काष्ठा vga_device *conflict;
	अचिन्हित पूर्णांक pci_bits;
	u32 flags = 0;

	/* Account क्रम "normal" resources to lock. If we decode the legacy,
	 * counterpart, we need to request it as well
	 */
	अगर ((rsrc & VGA_RSRC_NORMAL_IO) &&
	    (vgadev->decodes & VGA_RSRC_LEGACY_IO))
		rsrc |= VGA_RSRC_LEGACY_IO;
	अगर ((rsrc & VGA_RSRC_NORMAL_MEM) &&
	    (vgadev->decodes & VGA_RSRC_LEGACY_MEM))
		rsrc |= VGA_RSRC_LEGACY_MEM;

	vgaarb_dbg(dev, "%s: %d\n", __func__, rsrc);
	vgaarb_dbg(dev, "%s: owns: %d\n", __func__, vgadev->owns);

	/* Check what resources we need to acquire */
	wants = rsrc & ~vgadev->owns;

	/* We alपढ़ोy own everything, just mark locked & bye bye */
	अगर (wants == 0)
		जाओ lock_them;

	/* We करोn't need to request a legacy resource, we just enable
	 * appropriate decoding and go
	 */
	legacy_wants = wants & VGA_RSRC_LEGACY_MASK;
	अगर (legacy_wants == 0)
		जाओ enable_them;

	/* Ok, we करोn't, let's find out how we need to kick off */
	list_क्रम_each_entry(conflict, &vga_list, list) अणु
		अचिन्हित पूर्णांक lwants = legacy_wants;
		अचिन्हित पूर्णांक change_bridge = 0;

		/* Don't conflict with myself */
		अगर (vgadev == conflict)
			जारी;

		/* Check अगर the architecture allows a conflict between those
		 * 2 devices or अगर they are on separate करोमुख्यs
		 */
		अगर (!vga_conflicts(vgadev->pdev, conflict->pdev))
			जारी;

		/* We have a possible conflict. beक्रमe we go further, we must
		 * check अगर we sit on the same bus as the conflicting device.
		 * अगर we करोn't, then we must tie both IO and MEM resources
		 * together since there is only a single bit controlling
		 * VGA क्रमwarding on P2P bridges
		 */
		अगर (vgadev->pdev->bus != conflict->pdev->bus) अणु
			change_bridge = 1;
			lwants = VGA_RSRC_LEGACY_IO | VGA_RSRC_LEGACY_MEM;
		पूर्ण

		/* Check अगर the guy has a lock on the resource. If he करोes,
		 * वापस the conflicting entry
		 */
		अगर (conflict->locks & lwants)
			वापस conflict;

		/* Ok, now check अगर it owns the resource we want.  We can
		 * lock resources that are not decoded, thereक्रमe a device
		 * can own resources it करोesn't decode.
		 */
		match = lwants & conflict->owns;
		अगर (!match)
			जारी;

		/* looks like he करोesn't have a lock, we can steal
		 * them from him
		 */

		flags = 0;
		pci_bits = 0;

		/* If we can't control legacy resources via the bridge, we
		 * also need to disable normal decoding.
		 */
		अगर (!conflict->bridge_has_one_vga) अणु
			अगर ((match & conflict->decodes) & VGA_RSRC_LEGACY_MEM)
				pci_bits |= PCI_COMMAND_MEMORY;
			अगर ((match & conflict->decodes) & VGA_RSRC_LEGACY_IO)
				pci_bits |= PCI_COMMAND_IO;

			अगर (pci_bits) अणु
				vga_irq_set_state(conflict, false);
				flags |= PCI_VGA_STATE_CHANGE_DECODES;
			पूर्ण
		पूर्ण

		अगर (change_bridge)
			flags |= PCI_VGA_STATE_CHANGE_BRIDGE;

		pci_set_vga_state(conflict->pdev, false, pci_bits, flags);
		conflict->owns &= ~match;

		/* If we disabled normal decoding, reflect it in owns */
		अगर (pci_bits & PCI_COMMAND_MEMORY)
			conflict->owns &= ~VGA_RSRC_NORMAL_MEM;
		अगर (pci_bits & PCI_COMMAND_IO)
			conflict->owns &= ~VGA_RSRC_NORMAL_IO;
	पूर्ण

enable_them:
	/* ok dude, we got it, everybody conflicting has been disabled, let's
	 * enable us.  Mark any bits in "owns" regardless of whether we
	 * decoded them.  We can lock resources we करोn't decode, thereक्रमe
	 * we must track them via "owns".
	 */
	flags = 0;
	pci_bits = 0;

	अगर (!vgadev->bridge_has_one_vga) अणु
		flags |= PCI_VGA_STATE_CHANGE_DECODES;
		अगर (wants & (VGA_RSRC_LEGACY_MEM|VGA_RSRC_NORMAL_MEM))
			pci_bits |= PCI_COMMAND_MEMORY;
		अगर (wants & (VGA_RSRC_LEGACY_IO|VGA_RSRC_NORMAL_IO))
			pci_bits |= PCI_COMMAND_IO;
	पूर्ण
	अगर (wants & VGA_RSRC_LEGACY_MASK)
		flags |= PCI_VGA_STATE_CHANGE_BRIDGE;

	pci_set_vga_state(vgadev->pdev, true, pci_bits, flags);

	अगर (!vgadev->bridge_has_one_vga)
		vga_irq_set_state(vgadev, true);

	vgadev->owns |= wants;
lock_them:
	vgadev->locks |= (rsrc & VGA_RSRC_LEGACY_MASK);
	अगर (rsrc & VGA_RSRC_LEGACY_IO)
		vgadev->io_lock_cnt++;
	अगर (rsrc & VGA_RSRC_LEGACY_MEM)
		vgadev->mem_lock_cnt++;
	अगर (rsrc & VGA_RSRC_NORMAL_IO)
		vgadev->io_norm_cnt++;
	अगर (rsrc & VGA_RSRC_NORMAL_MEM)
		vgadev->mem_norm_cnt++;

	वापस शून्य;
पूर्ण

अटल व्योम __vga_put(काष्ठा vga_device *vgadev, अचिन्हित पूर्णांक rsrc)
अणु
	काष्ठा device *dev = &vgadev->pdev->dev;
	अचिन्हित पूर्णांक old_locks = vgadev->locks;

	vgaarb_dbg(dev, "%s\n", __func__);

	/* Update our counters, and account क्रम equivalent legacy resources
	 * अगर we decode them
	 */
	अगर ((rsrc & VGA_RSRC_NORMAL_IO) && vgadev->io_norm_cnt > 0) अणु
		vgadev->io_norm_cnt--;
		अगर (vgadev->decodes & VGA_RSRC_LEGACY_IO)
			rsrc |= VGA_RSRC_LEGACY_IO;
	पूर्ण
	अगर ((rsrc & VGA_RSRC_NORMAL_MEM) && vgadev->mem_norm_cnt > 0) अणु
		vgadev->mem_norm_cnt--;
		अगर (vgadev->decodes & VGA_RSRC_LEGACY_MEM)
			rsrc |= VGA_RSRC_LEGACY_MEM;
	पूर्ण
	अगर ((rsrc & VGA_RSRC_LEGACY_IO) && vgadev->io_lock_cnt > 0)
		vgadev->io_lock_cnt--;
	अगर ((rsrc & VGA_RSRC_LEGACY_MEM) && vgadev->mem_lock_cnt > 0)
		vgadev->mem_lock_cnt--;

	/* Just clear lock bits, we करो lazy operations so we करोn't really
	 * have to bother about anything अन्यथा at this poपूर्णांक
	 */
	अगर (vgadev->io_lock_cnt == 0)
		vgadev->locks &= ~VGA_RSRC_LEGACY_IO;
	अगर (vgadev->mem_lock_cnt == 0)
		vgadev->locks &= ~VGA_RSRC_LEGACY_MEM;

	/* Kick the रुको queue in हाल somebody was रुकोing अगर we actually
	 * released something
	 */
	अगर (old_locks != vgadev->locks)
		wake_up_all(&vga_रुको_queue);
पूर्ण

/**
 * vga_get - acquire & locks VGA resources
 * @pdev: pci device of the VGA card or शून्य क्रम the प्रणाली शेष
 * @rsrc: bit mask of resources to acquire and lock
 * @पूर्णांकerruptible: blocking should be पूर्णांकerruptible by संकेतs ?
 *
 * This function acquires VGA resources क्रम the given card and mark those
 * resources locked. If the resource requested are "normal" (and not legacy)
 * resources, the arbiter will first check whether the card is करोing legacy
 * decoding क्रम that type of resource. If yes, the lock is "converted" पूर्णांकo a
 * legacy resource lock.
 *
 * The arbiter will first look क्रम all VGA cards that might conflict and disable
 * their IOs and/or Memory access, including VGA क्रमwarding on P2P bridges अगर
 * necessary, so that the requested resources can be used. Then, the card is
 * marked as locking these resources and the IO and/or Memory accesses are
 * enabled on the card (including VGA क्रमwarding on parent P2P bridges अगर any).
 *
 * This function will block अगर some conflicting card is alपढ़ोy locking one of
 * the required resources (or any resource on a dअगरferent bus segment, since P2P
 * bridges करोn't dअगरferentiate VGA memory and IO afaik). You can indicate
 * whether this blocking should be पूर्णांकerruptible by a संकेत (क्रम userland
 * पूर्णांकerface) or not.
 *
 * Must not be called at पूर्णांकerrupt समय or in atomic context.  If the card
 * alपढ़ोy owns the resources, the function succeeds.  Nested calls are
 * supported (a per-resource counter is मुख्यtained)
 *
 * On success, release the VGA resource again with vga_put().
 *
 * Returns:
 *
 * 0 on success, negative error code on failure.
 */
पूर्णांक vga_get(काष्ठा pci_dev *pdev, अचिन्हित पूर्णांक rsrc, पूर्णांक पूर्णांकerruptible)
अणु
	काष्ठा vga_device *vgadev, *conflict;
	अचिन्हित दीर्घ flags;
	रुको_queue_entry_t रुको;
	पूर्णांक rc = 0;

	vga_check_first_use();
	/* The one who calls us should check क्रम this, but lets be sure... */
	अगर (pdev == शून्य)
		pdev = vga_शेष_device();
	अगर (pdev == शून्य)
		वापस 0;

	क्रम (;;) अणु
		spin_lock_irqsave(&vga_lock, flags);
		vgadev = vgadev_find(pdev);
		अगर (vgadev == शून्य) अणु
			spin_unlock_irqrestore(&vga_lock, flags);
			rc = -ENODEV;
			अवरोध;
		पूर्ण
		conflict = __vga_tryget(vgadev, rsrc);
		spin_unlock_irqrestore(&vga_lock, flags);
		अगर (conflict == शून्य)
			अवरोध;


		/* We have a conflict, we रुको until somebody kicks the
		 * work queue. Currently we have one work queue that we
		 * kick each समय some resources are released, but it would
		 * be fairly easy to have a per device one so that we only
		 * need to attach to the conflicting device
		 */
		init_रुकोqueue_entry(&रुको, current);
		add_रुको_queue(&vga_रुको_queue, &रुको);
		set_current_state(पूर्णांकerruptible ?
				  TASK_INTERRUPTIBLE :
				  TASK_UNINTERRUPTIBLE);
		अगर (पूर्णांकerruptible && संकेत_pending(current)) अणु
			__set_current_state(TASK_RUNNING);
			हटाओ_रुको_queue(&vga_रुको_queue, &रुको);
			rc = -ERESTARTSYS;
			अवरोध;
		पूर्ण
		schedule();
		हटाओ_रुको_queue(&vga_रुको_queue, &रुको);
	पूर्ण
	वापस rc;
पूर्ण
EXPORT_SYMBOL(vga_get);

/**
 * vga_tryget - try to acquire & lock legacy VGA resources
 * @pdev: pci devivce of VGA card or शून्य क्रम प्रणाली शेष
 * @rsrc: bit mask of resources to acquire and lock
 *
 * This function perक्रमms the same operation as vga_get(), but will वापस an
 * error (-EBUSY) instead of blocking अगर the resources are alपढ़ोy locked by
 * another card. It can be called in any context
 *
 * On success, release the VGA resource again with vga_put().
 *
 * Returns:
 *
 * 0 on success, negative error code on failure.
 */
अटल पूर्णांक vga_tryget(काष्ठा pci_dev *pdev, अचिन्हित पूर्णांक rsrc)
अणु
	काष्ठा vga_device *vgadev;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;

	vga_check_first_use();

	/* The one who calls us should check क्रम this, but lets be sure... */
	अगर (pdev == शून्य)
		pdev = vga_शेष_device();
	अगर (pdev == शून्य)
		वापस 0;
	spin_lock_irqsave(&vga_lock, flags);
	vgadev = vgadev_find(pdev);
	अगर (vgadev == शून्य) अणु
		rc = -ENODEV;
		जाओ bail;
	पूर्ण
	अगर (__vga_tryget(vgadev, rsrc))
		rc = -EBUSY;
bail:
	spin_unlock_irqrestore(&vga_lock, flags);
	वापस rc;
पूर्ण

/**
 * vga_put - release lock on legacy VGA resources
 * @pdev: pci device of VGA card or शून्य क्रम प्रणाली शेष
 * @rsrc: but mask of resource to release
 *
 * This fuction releases resources previously locked by vga_get() or
 * vga_tryget(). The resources aren't disabled right away, so that a subsequence
 * vga_get() on the same card will succeed immediately. Resources have a
 * counter, so locks are only released अगर the counter reaches 0.
 */
व्योम vga_put(काष्ठा pci_dev *pdev, अचिन्हित पूर्णांक rsrc)
अणु
	काष्ठा vga_device *vgadev;
	अचिन्हित दीर्घ flags;

	/* The one who calls us should check क्रम this, but lets be sure... */
	अगर (pdev == शून्य)
		pdev = vga_शेष_device();
	अगर (pdev == शून्य)
		वापस;
	spin_lock_irqsave(&vga_lock, flags);
	vgadev = vgadev_find(pdev);
	अगर (vgadev == शून्य)
		जाओ bail;
	__vga_put(vgadev, rsrc);
bail:
	spin_unlock_irqrestore(&vga_lock, flags);
पूर्ण
EXPORT_SYMBOL(vga_put);

/*
 * Rules क्रम using a bridge to control a VGA descendant decoding: अगर a bridge
 * has only one VGA descendant then it can be used to control the VGA routing
 * क्रम that device. It should always use the bridge बंदst to the device to
 * control it. If a bridge has a direct VGA descendant, but also have a sub-
 * bridge VGA descendant then we cannot use that bridge to control the direct
 * VGA descendant. So क्रम every device we रेजिस्टर, we need to iterate all
 * its parent bridges so we can invalidate any devices using them properly.
 */
अटल व्योम vga_arbiter_check_bridge_sharing(काष्ठा vga_device *vgadev)
अणु
	काष्ठा vga_device *same_bridge_vgadev;
	काष्ठा pci_bus *new_bus, *bus;
	काष्ठा pci_dev *new_bridge, *bridge;

	vgadev->bridge_has_one_vga = true;

	अगर (list_empty(&vga_list))
		वापस;

	/* okay iterate the new devices bridge hierarachy */
	new_bus = vgadev->pdev->bus;
	जबतक (new_bus) अणु
		new_bridge = new_bus->self;

		/* go through list of devices alपढ़ोy रेजिस्टरed */
		list_क्रम_each_entry(same_bridge_vgadev, &vga_list, list) अणु
			bus = same_bridge_vgadev->pdev->bus;
			bridge = bus->self;

			/* see अगर the share a bridge with this device */
			अगर (new_bridge == bridge) अणु
				/*
				 * If their direct parent bridge is the same
				 * as any bridge of this device then it can't
				 * be used क्रम that device.
				 */
				same_bridge_vgadev->bridge_has_one_vga = false;
			पूर्ण

			/*
			 * Now iterate the previous devices bridge hierarchy.
			 * If the new devices parent bridge is in the other
			 * devices hierarchy then we can't use it to control
			 * this device
			 */
			जबतक (bus) अणु
				bridge = bus->self;

				अगर (bridge && bridge == vgadev->pdev->bus->self)
					vgadev->bridge_has_one_vga = false;

				bus = bus->parent;
			पूर्ण
		पूर्ण
		new_bus = new_bus->parent;
	पूर्ण
पूर्ण

/*
 * Currently, we assume that the "initial" setup of the प्रणाली is
 * not sane, that is we come up with conflicting devices and let
 * the arbiter's client decides अगर devices decodes or not legacy
 * things.
 */
अटल bool vga_arbiter_add_pci_device(काष्ठा pci_dev *pdev)
अणु
	काष्ठा vga_device *vgadev;
	अचिन्हित दीर्घ flags;
	काष्ठा pci_bus *bus;
	काष्ठा pci_dev *bridge;
	u16 cmd;

	/* Only deal with VGA class devices */
	अगर ((pdev->class >> 8) != PCI_CLASS_DISPLAY_VGA)
		वापस false;

	/* Allocate काष्ठाure */
	vgadev = kzalloc(माप(काष्ठा vga_device), GFP_KERNEL);
	अगर (vgadev == शून्य) अणु
		vgaarb_err(&pdev->dev, "failed to allocate VGA arbiter data\n");
		/*
		 * What to करो on allocation failure ? For now, let's just करो
		 * nothing, I'm not sure there is anything saner to be करोne.
		 */
		वापस false;
	पूर्ण

	/* Take lock & check क्रम duplicates */
	spin_lock_irqsave(&vga_lock, flags);
	अगर (vgadev_find(pdev) != शून्य) अणु
		BUG_ON(1);
		जाओ fail;
	पूर्ण
	vgadev->pdev = pdev;

	/* By शेष, assume we decode everything */
	vgadev->decodes = VGA_RSRC_LEGACY_IO | VGA_RSRC_LEGACY_MEM |
			  VGA_RSRC_NORMAL_IO | VGA_RSRC_NORMAL_MEM;

	/* by शेष mark it as decoding */
	vga_decode_count++;
	/* Mark that we "own" resources based on our enables, we will
	 * clear that below अगर the bridge isn't क्रमwarding
	 */
	pci_पढ़ो_config_word(pdev, PCI_COMMAND, &cmd);
	अगर (cmd & PCI_COMMAND_IO)
		vgadev->owns |= VGA_RSRC_LEGACY_IO;
	अगर (cmd & PCI_COMMAND_MEMORY)
		vgadev->owns |= VGA_RSRC_LEGACY_MEM;

	/* Check अगर VGA cycles can get करोwn to us */
	bus = pdev->bus;
	जबतक (bus) अणु
		bridge = bus->self;
		अगर (bridge) अणु
			u16 l;

			pci_पढ़ो_config_word(bridge, PCI_BRIDGE_CONTROL, &l);
			अगर (!(l & PCI_BRIDGE_CTL_VGA)) अणु
				vgadev->owns = 0;
				अवरोध;
			पूर्ण
		पूर्ण
		bus = bus->parent;
	पूर्ण

	/* Deal with VGA शेष device. Use first enabled one
	 * by शेष अगर arch करोesn't have it's own hook
	 */
	अगर (vga_शेष == शून्य &&
	    ((vgadev->owns & VGA_RSRC_LEGACY_MASK) == VGA_RSRC_LEGACY_MASK)) अणु
		vgaarb_info(&pdev->dev, "setting as boot VGA device\n");
		vga_set_शेष_device(pdev);
	पूर्ण

	vga_arbiter_check_bridge_sharing(vgadev);

	/* Add to the list */
	list_add_tail(&vgadev->list, &vga_list);
	vga_count++;
	vgaarb_info(&pdev->dev, "VGA device added: decodes=%s,owns=%s,locks=%s\n",
		vga_iostate_to_str(vgadev->decodes),
		vga_iostate_to_str(vgadev->owns),
		vga_iostate_to_str(vgadev->locks));

	spin_unlock_irqrestore(&vga_lock, flags);
	वापस true;
fail:
	spin_unlock_irqrestore(&vga_lock, flags);
	kमुक्त(vgadev);
	वापस false;
पूर्ण

अटल bool vga_arbiter_del_pci_device(काष्ठा pci_dev *pdev)
अणु
	काष्ठा vga_device *vgadev;
	अचिन्हित दीर्घ flags;
	bool ret = true;

	spin_lock_irqsave(&vga_lock, flags);
	vgadev = vgadev_find(pdev);
	अगर (vgadev == शून्य) अणु
		ret = false;
		जाओ bail;
	पूर्ण

	अगर (vga_शेष == pdev)
		vga_set_शेष_device(शून्य);

	अगर (vgadev->decodes & (VGA_RSRC_LEGACY_IO | VGA_RSRC_LEGACY_MEM))
		vga_decode_count--;

	/* Remove entry from list */
	list_del(&vgadev->list);
	vga_count--;
	/* Notअगरy userland driver that the device is gone so it discards
	 * it's copies of the pci_dev poपूर्णांकer
	 */
	vga_arb_device_card_gone(pdev);

	/* Wake up all possible रुकोers */
	wake_up_all(&vga_रुको_queue);
bail:
	spin_unlock_irqrestore(&vga_lock, flags);
	kमुक्त(vgadev);
	वापस ret;
पूर्ण

/* this is called with the lock */
अटल अंतरभूत व्योम vga_update_device_decodes(काष्ठा vga_device *vgadev,
					     पूर्णांक new_decodes)
अणु
	काष्ठा device *dev = &vgadev->pdev->dev;
	पूर्णांक old_decodes, decodes_हटाओd, decodes_unlocked;

	old_decodes = vgadev->decodes;
	decodes_हटाओd = ~new_decodes & old_decodes;
	decodes_unlocked = vgadev->locks & decodes_हटाओd;
	vgadev->decodes = new_decodes;

	vgaarb_info(dev, "changed VGA decodes: olddecodes=%s,decodes=%s:owns=%s\n",
		vga_iostate_to_str(old_decodes),
		vga_iostate_to_str(vgadev->decodes),
		vga_iostate_to_str(vgadev->owns));

	/* अगर we हटाओd locked decodes, lock count goes to zero, and release */
	अगर (decodes_unlocked) अणु
		अगर (decodes_unlocked & VGA_RSRC_LEGACY_IO)
			vgadev->io_lock_cnt = 0;
		अगर (decodes_unlocked & VGA_RSRC_LEGACY_MEM)
			vgadev->mem_lock_cnt = 0;
		__vga_put(vgadev, decodes_unlocked);
	पूर्ण

	/* change decodes counter */
	अगर (old_decodes & VGA_RSRC_LEGACY_MASK &&
	    !(new_decodes & VGA_RSRC_LEGACY_MASK))
		vga_decode_count--;
	अगर (!(old_decodes & VGA_RSRC_LEGACY_MASK) &&
	    new_decodes & VGA_RSRC_LEGACY_MASK)
		vga_decode_count++;
	vgaarb_dbg(dev, "decoding count now is: %d\n", vga_decode_count);
पूर्ण

अटल व्योम __vga_set_legacy_decoding(काष्ठा pci_dev *pdev,
				      अचिन्हित पूर्णांक decodes,
				      bool userspace)
अणु
	काष्ठा vga_device *vgadev;
	अचिन्हित दीर्घ flags;

	decodes &= VGA_RSRC_LEGACY_MASK;

	spin_lock_irqsave(&vga_lock, flags);
	vgadev = vgadev_find(pdev);
	अगर (vgadev == शून्य)
		जाओ bail;

	/* करोn't let userspace futz with kernel driver decodes */
	अगर (userspace && vgadev->set_vga_decode)
		जाओ bail;

	/* update the device decodes + counter */
	vga_update_device_decodes(vgadev, decodes);

	/* XXX अगर somebody is going from "doesn't decode" to "decodes" state
	 * here, additional care must be taken as we may have pending owner
	 * ship of non-legacy region ...
	 */
bail:
	spin_unlock_irqrestore(&vga_lock, flags);
पूर्ण

व्योम vga_set_legacy_decoding(काष्ठा pci_dev *pdev, अचिन्हित पूर्णांक decodes)
अणु
	__vga_set_legacy_decoding(pdev, decodes, false);
पूर्ण
EXPORT_SYMBOL(vga_set_legacy_decoding);

/**
 * vga_client_रेजिस्टर - रेजिस्टर or unरेजिस्टर a VGA arbitration client
 * @pdev: pci device of the VGA client
 * @cookie: client cookie to be used in callbacks
 * @irq_set_state: irq state change callback
 * @set_vga_decode: vga decode change callback
 *
 * Clients have two callback mechanisms they can use.
 *
 * @irq_set_state callback: If a client can't disable its GPUs VGA
 * resources, then we need to be able to ask it to turn off its irqs when we
 * turn off its mem and io decoding.
 *
 * @set_vga_decode callback: If a client can disable its GPU VGA resource, it
 * will get a callback from this to set the encode/decode state.
 *
 * Rationale: we cannot disable VGA decode resources unconditionally some single
 * GPU laptops seem to require ACPI or BIOS access to the VGA रेजिस्टरs to
 * control things like backlights etc.  Hopefully newer multi-GPU laptops करो
 * something saner, and desktops won't have any special ACPI क्रम this. The
 * driver will get a callback when VGA arbitration is first used by userspace
 * since some older X servers have issues.
 *
 * This function करोes not check whether a client क्रम @pdev has been रेजिस्टरed
 * alपढ़ोy.
 *
 * To unरेजिस्टर just call this function with @irq_set_state and @set_vga_decode
 * both set to शून्य क्रम the same @pdev as originally used to रेजिस्टर them.
 *
 * Returns: 0 on success, -1 on failure
 */
पूर्णांक vga_client_रेजिस्टर(काष्ठा pci_dev *pdev, व्योम *cookie,
			व्योम (*irq_set_state)(व्योम *cookie, bool state),
			अचिन्हित पूर्णांक (*set_vga_decode)(व्योम *cookie,
						       bool decode))
अणु
	पूर्णांक ret = -ENODEV;
	काष्ठा vga_device *vgadev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vga_lock, flags);
	vgadev = vgadev_find(pdev);
	अगर (!vgadev)
		जाओ bail;

	vgadev->irq_set_state = irq_set_state;
	vgadev->set_vga_decode = set_vga_decode;
	vgadev->cookie = cookie;
	ret = 0;

bail:
	spin_unlock_irqrestore(&vga_lock, flags);
	वापस ret;

पूर्ण
EXPORT_SYMBOL(vga_client_रेजिस्टर);

/*
 * Char driver implementation
 *
 * Semantics is:
 *
 *  खोलो       : खोलो user instance of the arbitrer. by शेष, it's
 *                attached to the शेष VGA device of the प्रणाली.
 *
 *  बंद      : बंद user instance, release locks
 *
 *  पढ़ो       : वापस a string indicating the status of the target.
 *                an IO state string is of the क्रमm अणुio,mem,io+mem,noneपूर्ण,
 *                mc and ic are respectively mem and io lock counts (क्रम
 *                debugging/diagnostic only). "decodes" indicate what the
 *                card currently decodes, "owns" indicates what is currently
 *                enabled on it, and "locks" indicates what is locked by this
 *                card. If the card is unplugged, we get "invalid" then क्रम
 *                card_ID and an -ENODEV error is वापसed क्रम any command
 *                until a new card is targeted
 *
 *   "<card_ID>,decodes=<io_state>,owns=<io_state>,locks=<io_state> (ic,mc)"
 *
 * ग_लिखो       : ग_लिखो a command to the arbiter. List of commands is:
 *
 *   target <card_ID>   : चयन target to card <card_ID> (see below)
 *   lock <io_state>    : acquires locks on target ("none" is invalid io_state)
 *   trylock <io_state> : non-blocking acquire locks on target
 *   unlock <io_state>  : release locks on target
 *   unlock all         : release all locks on target held by this user
 *   decodes <io_state> : set the legacy decoding attributes क्रम the card
 *
 * poll         : event अगर something change on any card (not just the target)
 *
 * card_ID is of the क्रमm "PCI:domain:bus:dev.fn". It can be set to "default"
 * to go back to the प्रणाली शेष card (TODO: not implemented yet).
 * Currently, only PCI is supported as a prefix, but the userland API may
 * support other bus types in the future, even अगर the current kernel
 * implementation करोesn't.
 *
 * Note about locks:
 *
 * The driver keeps track of which user has what locks on which card. It
 * supports stacking, like the kernel one. This complexअगरies the implementation
 * a bit, but makes the arbiter more tolerant to userspace problems and able
 * to properly cleanup in all हालs when a process dies.
 * Currently, a max of 16 cards simultaneously can have locks issued from
 * userspace क्रम a given user (file descriptor instance) of the arbiter.
 *
 * If the device is hot-unplugged, there is a hook inside the module to notअगरy
 * they being added/हटाओd in the प्रणाली and स्वतःmatically added/हटाओd in
 * the arbiter.
 */

#घोषणा MAX_USER_CARDS         CONFIG_VGA_ARB_MAX_GPUS
#घोषणा PCI_INVALID_CARD       ((काष्ठा pci_dev *)-1UL)

/*
 * Each user has an array of these, tracking which cards have locks
 */
काष्ठा vga_arb_user_card अणु
	काष्ठा pci_dev *pdev;
	अचिन्हित पूर्णांक mem_cnt;
	अचिन्हित पूर्णांक io_cnt;
पूर्ण;

काष्ठा vga_arb_निजी अणु
	काष्ठा list_head list;
	काष्ठा pci_dev *target;
	काष्ठा vga_arb_user_card cards[MAX_USER_CARDS];
	spinlock_t lock;
पूर्ण;

अटल LIST_HEAD(vga_user_list);
अटल DEFINE_SPINLOCK(vga_user_lock);


/*
 * This function माला_लो a string in the क्रमmat: "PCI:domain:bus:dev.fn" and
 * वापसs the respective values. If the string is not in this क्रमmat,
 * it वापसs 0.
 */
अटल पूर्णांक vga_pci_str_to_vars(अक्षर *buf, पूर्णांक count, अचिन्हित पूर्णांक *करोमुख्य,
			       अचिन्हित पूर्णांक *bus, अचिन्हित पूर्णांक *devfn)
अणु
	पूर्णांक n;
	अचिन्हित पूर्णांक slot, func;


	n = माला_पूछो(buf, "PCI:%x:%x:%x.%x", करोमुख्य, bus, &slot, &func);
	अगर (n != 4)
		वापस 0;

	*devfn = PCI_DEVFN(slot, func);

	वापस 1;
पूर्ण

अटल sमाप_प्रकार vga_arb_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा vga_arb_निजी *priv = file->निजी_data;
	काष्ठा vga_device *vgadev;
	काष्ठा pci_dev *pdev;
	अचिन्हित दीर्घ flags;
	माप_प्रकार len;
	पूर्णांक rc;
	अक्षर *lbuf;

	lbuf = kदो_स्मृति(1024, GFP_KERNEL);
	अगर (lbuf == शून्य)
		वापस -ENOMEM;

	/* Shields against vga_arb_device_card_gone (pci_dev going
	 * away), and allows access to vga list
	 */
	spin_lock_irqsave(&vga_lock, flags);

	/* If we are targeting the शेष, use it */
	pdev = priv->target;
	अगर (pdev == शून्य || pdev == PCI_INVALID_CARD) अणु
		spin_unlock_irqrestore(&vga_lock, flags);
		len = प्र_लिखो(lbuf, "invalid");
		जाओ करोne;
	पूर्ण

	/* Find card vgadev काष्ठाure */
	vgadev = vgadev_find(pdev);
	अगर (vgadev == शून्य) अणु
		/* Wow, it's not in the list, that shouldn't happen,
		 * let's fix us up and वापस invalid card
		 */
		अगर (pdev == priv->target)
			vga_arb_device_card_gone(pdev);
		spin_unlock_irqrestore(&vga_lock, flags);
		len = प्र_लिखो(lbuf, "invalid");
		जाओ करोne;
	पूर्ण

	/* Fill the buffer with infos */
	len = snम_लिखो(lbuf, 1024,
		       "count:%d,PCI:%s,decodes=%s,owns=%s,locks=%s(%d:%d)\n",
		       vga_decode_count, pci_name(pdev),
		       vga_iostate_to_str(vgadev->decodes),
		       vga_iostate_to_str(vgadev->owns),
		       vga_iostate_to_str(vgadev->locks),
		       vgadev->io_lock_cnt, vgadev->mem_lock_cnt);

	spin_unlock_irqrestore(&vga_lock, flags);
करोne:

	/* Copy that to user */
	अगर (len > count)
		len = count;
	rc = copy_to_user(buf, lbuf, len);
	kमुक्त(lbuf);
	अगर (rc)
		वापस -EFAULT;
	वापस len;
पूर्ण

/*
 * TODO: To aव्योम parsing inside kernel and to improve the speed we may
 * consider use ioctl here
 */
अटल sमाप_प्रकार vga_arb_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा vga_arb_निजी *priv = file->निजी_data;
	काष्ठा vga_arb_user_card *uc = शून्य;
	काष्ठा pci_dev *pdev;

	अचिन्हित पूर्णांक io_state;

	अक्षर kbuf[64], *curr_pos;
	माप_प्रकार reमुख्यing = count;

	पूर्णांक ret_val;
	पूर्णांक i;

	अगर (count >= माप(kbuf))
		वापस -EINVAL;
	अगर (copy_from_user(kbuf, buf, count))
		वापस -EFAULT;
	curr_pos = kbuf;
	kbuf[count] = '\0';	/* Just to make sure... */

	अगर (म_भेदन(curr_pos, "lock ", 5) == 0) अणु
		curr_pos += 5;
		reमुख्यing -= 5;

		pr_debug("client 0x%p called 'lock'\n", priv);

		अगर (!vga_str_to_iostate(curr_pos, reमुख्यing, &io_state)) अणु
			ret_val = -EPROTO;
			जाओ करोne;
		पूर्ण
		अगर (io_state == VGA_RSRC_NONE) अणु
			ret_val = -EPROTO;
			जाओ करोne;
		पूर्ण

		pdev = priv->target;
		अगर (priv->target == शून्य) अणु
			ret_val = -ENODEV;
			जाओ करोne;
		पूर्ण

		vga_get_unपूर्णांकerruptible(pdev, io_state);

		/* Update the client's locks lists... */
		क्रम (i = 0; i < MAX_USER_CARDS; i++) अणु
			अगर (priv->cards[i].pdev == pdev) अणु
				अगर (io_state & VGA_RSRC_LEGACY_IO)
					priv->cards[i].io_cnt++;
				अगर (io_state & VGA_RSRC_LEGACY_MEM)
					priv->cards[i].mem_cnt++;
				अवरोध;
			पूर्ण
		पूर्ण

		ret_val = count;
		जाओ करोne;
	पूर्ण अन्यथा अगर (म_भेदन(curr_pos, "unlock ", 7) == 0) अणु
		curr_pos += 7;
		reमुख्यing -= 7;

		pr_debug("client 0x%p called 'unlock'\n", priv);

		अगर (म_भेदन(curr_pos, "all", 3) == 0)
			io_state = VGA_RSRC_LEGACY_IO | VGA_RSRC_LEGACY_MEM;
		अन्यथा अणु
			अगर (!vga_str_to_iostate
			    (curr_pos, reमुख्यing, &io_state)) अणु
				ret_val = -EPROTO;
				जाओ करोne;
			पूर्ण
			/* TODO: Add this?
			   अगर (io_state == VGA_RSRC_NONE) अणु
			   ret_val = -EPROTO;
			   जाओ करोne;
			   पूर्ण
			  */
		पूर्ण

		pdev = priv->target;
		अगर (priv->target == शून्य) अणु
			ret_val = -ENODEV;
			जाओ करोne;
		पूर्ण
		क्रम (i = 0; i < MAX_USER_CARDS; i++) अणु
			अगर (priv->cards[i].pdev == pdev)
				uc = &priv->cards[i];
		पूर्ण

		अगर (!uc) अणु
			ret_val = -EINVAL;
			जाओ करोne;
		पूर्ण

		अगर (io_state & VGA_RSRC_LEGACY_IO && uc->io_cnt == 0) अणु
			ret_val = -EINVAL;
			जाओ करोne;
		पूर्ण

		अगर (io_state & VGA_RSRC_LEGACY_MEM && uc->mem_cnt == 0) अणु
			ret_val = -EINVAL;
			जाओ करोne;
		पूर्ण

		vga_put(pdev, io_state);

		अगर (io_state & VGA_RSRC_LEGACY_IO)
			uc->io_cnt--;
		अगर (io_state & VGA_RSRC_LEGACY_MEM)
			uc->mem_cnt--;

		ret_val = count;
		जाओ करोne;
	पूर्ण अन्यथा अगर (म_भेदन(curr_pos, "trylock ", 8) == 0) अणु
		curr_pos += 8;
		reमुख्यing -= 8;

		pr_debug("client 0x%p called 'trylock'\n", priv);

		अगर (!vga_str_to_iostate(curr_pos, reमुख्यing, &io_state)) अणु
			ret_val = -EPROTO;
			जाओ करोne;
		पूर्ण
		/* TODO: Add this?
		   अगर (io_state == VGA_RSRC_NONE) अणु
		   ret_val = -EPROTO;
		   जाओ करोne;
		   पूर्ण
		 */

		pdev = priv->target;
		अगर (priv->target == शून्य) अणु
			ret_val = -ENODEV;
			जाओ करोne;
		पूर्ण

		अगर (vga_tryget(pdev, io_state)) अणु
			/* Update the client's locks lists... */
			क्रम (i = 0; i < MAX_USER_CARDS; i++) अणु
				अगर (priv->cards[i].pdev == pdev) अणु
					अगर (io_state & VGA_RSRC_LEGACY_IO)
						priv->cards[i].io_cnt++;
					अगर (io_state & VGA_RSRC_LEGACY_MEM)
						priv->cards[i].mem_cnt++;
					अवरोध;
				पूर्ण
			पूर्ण
			ret_val = count;
			जाओ करोne;
		पूर्ण अन्यथा अणु
			ret_val = -EBUSY;
			जाओ करोne;
		पूर्ण

	पूर्ण अन्यथा अगर (म_भेदन(curr_pos, "target ", 7) == 0) अणु
		अचिन्हित पूर्णांक करोमुख्य, bus, devfn;
		काष्ठा vga_device *vgadev;

		curr_pos += 7;
		reमुख्यing -= 7;
		pr_debug("client 0x%p called 'target'\n", priv);
		/* अगर target is शेष */
		अगर (!म_भेदन(curr_pos, "default", 7))
			pdev = pci_dev_get(vga_शेष_device());
		अन्यथा अणु
			अगर (!vga_pci_str_to_vars(curr_pos, reमुख्यing,
						 &करोमुख्य, &bus, &devfn)) अणु
				ret_val = -EPROTO;
				जाओ करोne;
			पूर्ण
			pdev = pci_get_करोमुख्य_bus_and_slot(करोमुख्य, bus, devfn);
			अगर (!pdev) अणु
				pr_debug("invalid PCI address %04x:%02x:%02x.%x\n",
					 करोमुख्य, bus, PCI_SLOT(devfn),
					 PCI_FUNC(devfn));
				ret_val = -ENODEV;
				जाओ करोne;
			पूर्ण

			pr_debug("%s ==> %04x:%02x:%02x.%x pdev %p\n", curr_pos,
				करोमुख्य, bus, PCI_SLOT(devfn), PCI_FUNC(devfn),
				pdev);
		पूर्ण

		vgadev = vgadev_find(pdev);
		pr_debug("vgadev %p\n", vgadev);
		अगर (vgadev == शून्य) अणु
			अगर (pdev) अणु
				vgaarb_dbg(&pdev->dev, "not a VGA device\n");
				pci_dev_put(pdev);
			पूर्ण

			ret_val = -ENODEV;
			जाओ करोne;
		पूर्ण

		priv->target = pdev;
		क्रम (i = 0; i < MAX_USER_CARDS; i++) अणु
			अगर (priv->cards[i].pdev == pdev)
				अवरोध;
			अगर (priv->cards[i].pdev == शून्य) अणु
				priv->cards[i].pdev = pdev;
				priv->cards[i].io_cnt = 0;
				priv->cards[i].mem_cnt = 0;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i == MAX_USER_CARDS) अणु
			vgaarb_dbg(&pdev->dev, "maximum user cards (%d) number reached, ignoring this one!\n",
				MAX_USER_CARDS);
			pci_dev_put(pdev);
			/* XXX: which value to वापस? */
			ret_val =  -ENOMEM;
			जाओ करोne;
		पूर्ण

		ret_val = count;
		pci_dev_put(pdev);
		जाओ करोne;


	पूर्ण अन्यथा अगर (म_भेदन(curr_pos, "decodes ", 8) == 0) अणु
		curr_pos += 8;
		reमुख्यing -= 8;
		pr_debug("client 0x%p called 'decodes'\n", priv);

		अगर (!vga_str_to_iostate(curr_pos, reमुख्यing, &io_state)) अणु
			ret_val = -EPROTO;
			जाओ करोne;
		पूर्ण
		pdev = priv->target;
		अगर (priv->target == शून्य) अणु
			ret_val = -ENODEV;
			जाओ करोne;
		पूर्ण

		__vga_set_legacy_decoding(pdev, io_state, true);
		ret_val = count;
		जाओ करोne;
	पूर्ण
	/* If we got here, the message written is not part of the protocol! */
	वापस -EPROTO;

करोne:
	वापस ret_val;
पूर्ण

अटल __poll_t vga_arb_fpoll(काष्ठा file *file, poll_table *रुको)
अणु
	pr_debug("%s\n", __func__);

	poll_रुको(file, &vga_रुको_queue, रुको);
	वापस EPOLLIN;
पूर्ण

अटल पूर्णांक vga_arb_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा vga_arb_निजी *priv;
	अचिन्हित दीर्घ flags;

	pr_debug("%s\n", __func__);

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (priv == शून्य)
		वापस -ENOMEM;
	spin_lock_init(&priv->lock);
	file->निजी_data = priv;

	spin_lock_irqsave(&vga_user_lock, flags);
	list_add(&priv->list, &vga_user_list);
	spin_unlock_irqrestore(&vga_user_lock, flags);

	/* Set the client' lists of locks */
	priv->target = vga_शेष_device(); /* Maybe this is still null! */
	priv->cards[0].pdev = priv->target;
	priv->cards[0].io_cnt = 0;
	priv->cards[0].mem_cnt = 0;


	वापस 0;
पूर्ण

अटल पूर्णांक vga_arb_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा vga_arb_निजी *priv = file->निजी_data;
	काष्ठा vga_arb_user_card *uc;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	pr_debug("%s\n", __func__);

	spin_lock_irqsave(&vga_user_lock, flags);
	list_del(&priv->list);
	क्रम (i = 0; i < MAX_USER_CARDS; i++) अणु
		uc = &priv->cards[i];
		अगर (uc->pdev == शून्य)
			जारी;
		vgaarb_dbg(&uc->pdev->dev, "uc->io_cnt == %d, uc->mem_cnt == %d\n",
			uc->io_cnt, uc->mem_cnt);
		जबतक (uc->io_cnt--)
			vga_put(uc->pdev, VGA_RSRC_LEGACY_IO);
		जबतक (uc->mem_cnt--)
			vga_put(uc->pdev, VGA_RSRC_LEGACY_MEM);
	पूर्ण
	spin_unlock_irqrestore(&vga_user_lock, flags);

	kमुक्त(priv);

	वापस 0;
पूर्ण

अटल व्योम vga_arb_device_card_gone(काष्ठा pci_dev *pdev)
अणु
पूर्ण

/*
 * callback any रेजिस्टरed clients to let them know we have a
 * change in VGA cards
 */
अटल व्योम vga_arbiter_notअगरy_clients(व्योम)
अणु
	काष्ठा vga_device *vgadev;
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t new_decodes;
	bool new_state;

	अगर (!vga_arbiter_used)
		वापस;

	spin_lock_irqsave(&vga_lock, flags);
	list_क्रम_each_entry(vgadev, &vga_list, list) अणु
		अगर (vga_count > 1)
			new_state = false;
		अन्यथा
			new_state = true;
		अगर (vgadev->set_vga_decode) अणु
			new_decodes = vgadev->set_vga_decode(vgadev->cookie,
							     new_state);
			vga_update_device_decodes(vgadev, new_decodes);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&vga_lock, flags);
पूर्ण

अटल पूर्णांक pci_notअगरy(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ action,
		      व्योम *data)
अणु
	काष्ठा device *dev = data;
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	bool notअगरy = false;

	vgaarb_dbg(dev, "%s\n", __func__);

	/* For now we're only intereted in devices added and removed. I didn't
	 * test this thing here, so someone needs to द्विगुन check क्रम the
	 * हालs of hotplugable vga cards. */
	अगर (action == BUS_NOTIFY_ADD_DEVICE)
		notअगरy = vga_arbiter_add_pci_device(pdev);
	अन्यथा अगर (action == BUS_NOTIFY_DEL_DEVICE)
		notअगरy = vga_arbiter_del_pci_device(pdev);

	अगर (notअगरy)
		vga_arbiter_notअगरy_clients();
	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block pci_notअगरier = अणु
	.notअगरier_call = pci_notअगरy,
पूर्ण;

अटल स्थिर काष्ठा file_operations vga_arb_device_fops = अणु
	.पढ़ो = vga_arb_पढ़ो,
	.ग_लिखो = vga_arb_ग_लिखो,
	.poll = vga_arb_fpoll,
	.खोलो = vga_arb_खोलो,
	.release = vga_arb_release,
	.llseek = noop_llseek,
पूर्ण;

अटल काष्ठा miscdevice vga_arb_device = अणु
	MISC_DYNAMIC_MINOR, "vga_arbiter", &vga_arb_device_fops
पूर्ण;

अटल व्योम __init vga_arb_select_शेष_device(व्योम)
अणु
	काष्ठा pci_dev *pdev;
	काष्ठा vga_device *vgadev;

#अगर defined(CONFIG_X86) || defined(CONFIG_IA64)
	u64 base = screen_info.lfb_base;
	u64 size = screen_info.lfb_size;
	u64 limit;
	resource_माप_प्रकार start, end;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	अगर (screen_info.capabilities & VIDEO_CAPABILITY_64BIT_BASE)
		base |= (u64)screen_info.ext_lfb_base << 32;

	limit = base + size;

	list_क्रम_each_entry(vgadev, &vga_list, list) अणु
		काष्ठा device *dev = &vgadev->pdev->dev;
		/*
		 * Override vga_arbiter_add_pci_device()'s I/O based detection
		 * as it may take the wrong device (e.g. on Apple प्रणाली under
		 * EFI).
		 *
		 * Select the device owning the boot framebuffer अगर there is
		 * one.
		 */

		/* Does firmware framebuffer beदीर्घ to us? */
		क्रम (i = 0; i < DEVICE_COUNT_RESOURCE; i++) अणु
			flags = pci_resource_flags(vgadev->pdev, i);

			अगर ((flags & IORESOURCE_MEM) == 0)
				जारी;

			start = pci_resource_start(vgadev->pdev, i);
			end  = pci_resource_end(vgadev->pdev, i);

			अगर (!start || !end)
				जारी;

			अगर (base < start || limit >= end)
				जारी;

			अगर (!vga_शेष_device())
				vgaarb_info(dev, "setting as boot device\n");
			अन्यथा अगर (vgadev->pdev != vga_शेष_device())
				vgaarb_info(dev, "overriding boot device\n");
			vga_set_शेष_device(vgadev->pdev);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	अगर (!vga_शेष_device()) अणु
		list_क्रम_each_entry(vgadev, &vga_list, list) अणु
			काष्ठा device *dev = &vgadev->pdev->dev;
			u16 cmd;

			pdev = vgadev->pdev;
			pci_पढ़ो_config_word(pdev, PCI_COMMAND, &cmd);
			अगर (cmd & (PCI_COMMAND_IO | PCI_COMMAND_MEMORY)) अणु
				vgaarb_info(dev, "setting as boot device (VGA legacy resources not available)\n");
				vga_set_शेष_device(pdev);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!vga_शेष_device()) अणु
		vgadev = list_first_entry_or_null(&vga_list,
						  काष्ठा vga_device, list);
		अगर (vgadev) अणु
			काष्ठा device *dev = &vgadev->pdev->dev;
			vgaarb_info(dev, "setting as boot device (VGA legacy resources not available)\n");
			vga_set_शेष_device(vgadev->pdev);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक __init vga_arb_device_init(व्योम)
अणु
	पूर्णांक rc;
	काष्ठा pci_dev *pdev;
	काष्ठा vga_device *vgadev;

	rc = misc_रेजिस्टर(&vga_arb_device);
	अगर (rc < 0)
		pr_err("error %d registering device\n", rc);

	bus_रेजिस्टर_notअगरier(&pci_bus_type, &pci_notअगरier);

	/* We add all PCI devices satisfying VGA class in the arbiter by
	 * शेष */
	pdev = शून्य;
	जबतक ((pdev =
		pci_get_subsys(PCI_ANY_ID, PCI_ANY_ID, PCI_ANY_ID,
			       PCI_ANY_ID, pdev)) != शून्य)
		vga_arbiter_add_pci_device(pdev);

	list_क्रम_each_entry(vgadev, &vga_list, list) अणु
		काष्ठा device *dev = &vgadev->pdev->dev;

		अगर (vgadev->bridge_has_one_vga)
			vgaarb_info(dev, "bridge control possible\n");
		अन्यथा
			vgaarb_info(dev, "no bridge control possible\n");
	पूर्ण

	vga_arb_select_शेष_device();

	pr_info("loaded\n");
	वापस rc;
पूर्ण
subsys_initcall(vga_arb_device_init);
