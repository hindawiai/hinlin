<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * IBM eServer Hypervisor Virtual Console Server Device Driver
 * Copyright (C) 2003, 2004 IBM Corp.
 *  Ryan S. Arnold (rsa@us.ibm.com)
 *
 * Author(s) :  Ryan S. Arnold <rsa@us.ibm.com>
 *
 * This is the device driver क्रम the IBM Hypervisor Virtual Console Server,
 * "hvcs".  The IBM hvcs provides a tty driver पूर्णांकerface to allow Linux
 * user space applications access to the प्रणाली consoles of logically
 * partitioned operating प्रणालीs, e.g. Linux, running on the same partitioned
 * Power5 ppc64 प्रणाली.  Physical hardware consoles per partition are not
 * practical on this hardware so प्रणाली consoles are accessed by this driver
 * using पूर्णांकer-partition firmware पूर्णांकerfaces to भव terminal devices.
 *
 * A vty is known to the HMC as a "virtual serial server adapter".  It is a
 * भव terminal device that is created by firmware upon partition creation
 * to act as a partitioned OS's console device.
 *
 * Firmware dynamically (via hotplug) exposes vty-servers to a running ppc64
 * Linux प्रणाली upon their creation by the HMC or their exposure during boot.
 * The non-user पूर्णांकeractive backend of this driver is implemented as a vio
 * device driver so that it can receive notअगरication of vty-server lअगरeबार
 * after it रेजिस्टरs with the vio bus to handle vty-server probe and हटाओ
 * callbacks.
 *
 * Many vty-servers can be configured to connect to one vty, but a vty can
 * only be actively connected to by a single vty-server, in any manner, at one
 * समय.  If the HMC is currently hosting the console क्रम a target Linux
 * partition; attempts to खोलो the tty device to the partition's console using
 * the hvcs on any partition will वापस -EBUSY with every खोलो attempt until
 * the HMC मुक्तs the connection between its vty-server and the desired
 * partition's vty device.  Conversely, a vty-server may only be connected to
 * a single vty at one समय even though it may have several configured vty
 * partner possibilities.
 *
 * Firmware करोes not provide notअगरication of vty partner changes to this
 * driver.  This means that an HMC Super Admin may add or हटाओ partner vtys
 * from a vty-server's partner list but the changes will not be संकेतed to
 * the vty-server.  Firmware only notअगरies the driver when a vty-server is
 * added or हटाओd from the प्रणाली.  To compensate क्रम this deficiency, this
 * driver implements a sysfs update attribute which provides a method क्रम
 * rescanning partner inक्रमmation upon a user's request.
 *
 * Each vty-server, prior to being exposed to this driver is reference counted
 * using the 2.6 Linux kernel kref स्थिरruct.
 *
 * For direction on installation and usage of this driver please reference
 * Documentation/घातerpc/hvcs.rst.
 */

#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kref.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/list.h>
#समावेश <linux/major.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <यंत्र/hvconsole.h>
#समावेश <यंत्र/hvcserver.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/vपन.स>

/*
 * 1.3.0 -> 1.3.1 In hvcs_खोलो स_रखो(..,0x00,..) instead of स_रखो(..,0x3F,00).
 * Removed braces around single statements following conditionals.  Removed '=
 * 0' after अटल पूर्णांक declarations since these शेष to zero.  Removed
 * list_क्रम_each_safe() and replaced with list_क्रम_each_entry() in
 * hvcs_get_by_index().  The 'safe' version is un-needed now that the driver is
 * using spinlocks.  Changed spin_lock_irqsave() to spin_lock() when locking
 * hvcs_काष्ठाs_lock and hvcs_pi_lock since these are not touched in an पूर्णांक
 * handler.  Initialized hvcs_काष्ठाs_lock and hvcs_pi_lock to
 * SPIN_LOCK_UNLOCKED at declaration समय rather than in hvcs_module_init().
 * Added spin_lock around list_del() in destroy_hvcs_काष्ठा() to protect the
 * list traversals from a deletion.  Removed '= NULL' from poपूर्णांकer declaration
 * statements since they are initialized शून्य by शेष.  Removed wmb()
 * instances from hvcs_try_ग_लिखो().  They probably aren't needed with locking in
 * place.  Added check and cleanup क्रम hvcs_pi_buff = kदो_स्मृति() in
 * hvcs_module_init().  Exposed hvcs_काष्ठा.index via a sysfs attribute so that
 * the coupling between /dev/hvcs* and a vty-server can be स्वतःmatically
 * determined.  Moved kobject_put() in hvcs_खोलो outside of the
 * spin_unlock_irqrestore().
 *
 * 1.3.1 -> 1.3.2 Changed method क्रम determining hvcs_काष्ठा->index and had it
 * align with how the tty layer always assigns the lowest index available.  This
 * change resulted in a list of पूर्णांकs that denotes which indexes are available.
 * Device additions and removals use the new hvcs_get_index() and
 * hvcs_वापस_index() helper functions.  The list is created with
 * hvsc_alloc_index_list() and it is destroyed with hvcs_मुक्त_index_list().
 * Without these fixes hotplug vty-server adapter support goes crazy with this
 * driver अगर the user हटाओs a vty-server adapter.  Moved मुक्त_irq() outside of
 * the hvcs_final_बंद() function in order to get it out of the spinlock.
 * Rearranged hvcs_बंद().  Cleaned up some prपूर्णांकks and did some housekeeping
 * on the changelog.  Removed local CLC_LENGTH and used HVCS_CLC_LENGTH from
 * arch/घातerepc/include/यंत्र/hvcserver.h
 *
 * 1.3.2 -> 1.3.3 Replaced yield() in hvcs_बंद() with tty_रुको_until_sent() to
 * prevent possible lockup with realसमय scheduling as similarly poपूर्णांकed out by
 * akpm in hvc_console.  Changed resulted in the removal of hvcs_final_बंद()
 * to reorder cleanup operations and prevent discarding of pending data during
 * an hvcs_बंद().  Removed spinlock protection of hvcs_काष्ठा data members in
 * hvcs_ग_लिखो_room() and hvcs_अक्षरs_in_buffer() because they aren't needed.
 */

#घोषणा HVCS_DRIVER_VERSION "1.3.3"

MODULE_AUTHOR("Ryan S. Arnold <rsa@us.ibm.com>");
MODULE_DESCRIPTION("IBM hvcs (Hypervisor Virtual Console Server) Driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(HVCS_DRIVER_VERSION);

/*
 * Wait this दीर्घ per iteration जबतक trying to push buffered data to the
 * hypervisor beक्रमe allowing the tty to complete a बंद operation.
 */
#घोषणा HVCS_CLOSE_WAIT (HZ/100) /* 1/10 of a second */

/*
 * Since the Linux TTY code करोes not currently (2-04-2004) support dynamic
 * addition of tty derived devices and we shouldn't allocate thousands of
 * tty_device poपूर्णांकers when the number of vty-server & vty partner connections
 * will most often be much lower than this, we'll arbitrarily allocate
 * HVCS_DEFAULT_SERVER_ADAPTERS tty_काष्ठाs and cdev's by शेष when we
 * रेजिस्टर the tty_driver. This can be overridden using an insmod parameter.
 */
#घोषणा HVCS_DEFAULT_SERVER_ADAPTERS	64

/*
 * The user can't insmod with more than HVCS_MAX_SERVER_ADAPTERS hvcs device
 * nodes as a sanity check.  Theoretically there can be over 1 Billion
 * vty-server & vty partner connections.
 */
#घोषणा HVCS_MAX_SERVER_ADAPTERS	1024

/*
 * We let Linux assign us a major number and we start the minors at zero.  There
 * is no पूर्णांकuitive mapping between minor number and the target vty-server
 * adapter except that each new vty-server adapter is always asचिन्हित to the
 * smallest minor number available.
 */
#घोषणा HVCS_MINOR_START	0

/*
 * The hcall पूर्णांकerface involves putting 8 अक्षरs पूर्णांकo each of two रेजिस्टरs.
 * We load up those 2 रेजिस्टरs (in arch/घातerpc/platक्रमms/pseries/hvconsole.c)
 * by casting अक्षर[16] to दीर्घ[2].  It would work without __ALIGNED__, but a 
 * little (tiny) bit slower because an unaligned load is slower than aligned 
 * load.
 */
#घोषणा __ALIGNED__	__attribute__((__aligned__(8)))

/*
 * How much data can firmware send with each hvc_put_अक्षरs()?  Maybe this
 * should be moved पूर्णांकo an architecture specअगरic area.
 */
#घोषणा HVCS_BUFF_LEN	16

/*
 * This is the maximum amount of data we'll let the user send us (hvcs_ग_लिखो) at
 * once in a chunk as a sanity check.
 */
#घोषणा HVCS_MAX_FROM_USER	4096

/*
 * Be careful when adding flags to this line discipline.  Don't add anything
 * that will cause echoing or we'll go पूर्णांकo recursive loop echoing अक्षरs back
 * and क्रमth with the console drivers.
 */
अटल स्थिर काष्ठा ktermios hvcs_tty_termios = अणु
	.c_अगरlag = IGNBRK | IGNPAR,
	.c_oflag = OPOST,
	.c_cflag = B38400 | CS8 | CREAD | HUPCL,
	.c_cc = INIT_C_CC,
	.c_ispeed = 38400,
	.c_ospeed = 38400
पूर्ण;

/*
 * This value is used to take the place of a command line parameter when the
 * module is inserted.  It starts as -1 and stays as such अगर the user करोesn't
 * specअगरy a module insmod parameter.  If they DO specअगरy one then it is set to
 * the value of the पूर्णांकeger passed in.
 */
अटल पूर्णांक hvcs_parm_num_devs = -1;
module_param(hvcs_parm_num_devs, पूर्णांक, 0);

अटल स्थिर अक्षर hvcs_driver_name[] = "hvcs";
अटल स्थिर अक्षर hvcs_device_node[] = "hvcs";

/* Status of partner info rescan triggered via sysfs. */
अटल पूर्णांक hvcs_rescan_status;

अटल काष्ठा tty_driver *hvcs_tty_driver;

/*
 * In order to be somewhat sane this driver always associates the hvcs_काष्ठा
 * index element with the numerically equal tty->index.  This means that a
 * hotplugged vty-server adapter will always map to the lowest index valued
 * device node.  If vty-servers were hotplug हटाओd from the प्रणाली and then
 * new ones added the new vty-server may have the largest slot number of all
 * the vty-server adapters in the partition but it may have the lowest dev node
 * index of all the adapters due to the hole left by the hotplug हटाओd
 * adapter.  There are a set of functions provided to get the lowest index क्रम
 * a new device as well as वापस the index to the list.  This list is allocated
 * with a number of elements equal to the number of device nodes requested when
 * the module was inserted.
 */
अटल पूर्णांक *hvcs_index_list;

/*
 * How large is the list?  This is kept क्रम traversal since the list is
 * dynamically created.
 */
अटल पूर्णांक hvcs_index_count;

/*
 * Used by the khvcsd to pick up I/O operations when the kernel_thपढ़ो is
 * alपढ़ोy awake but potentially shअगरted to TASK_INTERRUPTIBLE state.
 */
अटल पूर्णांक hvcs_kicked;

/*
 * Use by the kthपढ़ो स्थिरruct क्रम task operations like waking the sleeping
 * thपढ़ो and stopping the kthपढ़ो.
 */
अटल काष्ठा task_काष्ठा *hvcs_task;

/*
 * We allocate this क्रम the use of all of the hvcs_काष्ठाs when they fetch
 * partner info.
 */
अटल अचिन्हित दीर्घ *hvcs_pi_buff;

/* Only allow one hvcs_काष्ठा to use the hvcs_pi_buff at a समय. */
अटल DEFINE_SPINLOCK(hvcs_pi_lock);

/* One vty-server per hvcs_काष्ठा */
काष्ठा hvcs_काष्ठा अणु
	काष्ठा tty_port port;
	spinlock_t lock;

	/*
	 * This index identअगरies this hvcs device as the complement to a
	 * specअगरic tty index.
	 */
	अचिन्हित पूर्णांक index;

	/*
	 * Used to tell the driver kernel_thपढ़ो what operations need to take
	 * place upon this hvcs_काष्ठा instance.
	 */
	पूर्णांक toकरो_mask;

	/*
	 * This buffer is required so that when hvcs_ग_लिखो_room() reports that
	 * it can send HVCS_BUFF_LEN अक्षरacters that it will buffer the full
	 * HVCS_BUFF_LEN अक्षरacters अगर need be.  This is essential क्रम opost
	 * ग_लिखोs since they करो not करो high level buffering and expect to be
	 * able to send what the driver commits to sending buffering
	 * [e.g. tab to space conversions in n_tty.c opost()].
	 */
	अक्षर buffer[HVCS_BUFF_LEN];
	पूर्णांक अक्षरs_in_buffer;

	/*
	 * Any variable below is valid beक्रमe a tty is connected and
	 * stays valid after the tty is disconnected.  These shouldn't be
	 * whacked until the kobject refcount reaches zero though some entries
	 * may be changed via sysfs initiatives.
	 */
	पूर्णांक connected; /* is the vty-server currently connected to a vty? */
	uपूर्णांक32_t p_unit_address; /* partner unit address */
	uपूर्णांक32_t p_partition_ID; /* partner partition ID */
	अक्षर p_location_code[HVCS_CLC_LENGTH + 1]; /* CLC + Null Term */
	काष्ठा list_head next; /* list management */
	काष्ठा vio_dev *vdev;
पूर्ण;

अटल LIST_HEAD(hvcs_काष्ठाs);
अटल DEFINE_SPINLOCK(hvcs_काष्ठाs_lock);
अटल DEFINE_MUTEX(hvcs_init_mutex);

अटल पूर्णांक hvcs_get_pi(काष्ठा hvcs_काष्ठा *hvcsd);
अटल पूर्णांक hvcs_rescan_devices_list(व्योम);

अटल व्योम hvcs_partner_मुक्त(काष्ठा hvcs_काष्ठा *hvcsd);

अटल पूर्णांक hvcs_initialize(व्योम);

#घोषणा HVCS_SCHED_READ	0x00000001
#घोषणा HVCS_QUICK_READ	0x00000002
#घोषणा HVCS_TRY_WRITE	0x00000004
#घोषणा HVCS_READ_MASK	(HVCS_SCHED_READ | HVCS_QUICK_READ)

अटल अंतरभूत काष्ठा hvcs_काष्ठा *from_vio_dev(काष्ठा vio_dev *viod)
अणु
	वापस dev_get_drvdata(&viod->dev);
पूर्ण
/* The sysfs पूर्णांकerface क्रम the driver and devices */

अटल sमाप_प्रकार hvcs_partner_vtys_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा vio_dev *viod = to_vio_dev(dev);
	काष्ठा hvcs_काष्ठा *hvcsd = from_vio_dev(viod);
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;

	spin_lock_irqsave(&hvcsd->lock, flags);
	retval = प्र_लिखो(buf, "%X\n", hvcsd->p_unit_address);
	spin_unlock_irqrestore(&hvcsd->lock, flags);
	वापस retval;
पूर्ण
अटल DEVICE_ATTR(partner_vtys, S_IRUGO, hvcs_partner_vtys_show, शून्य);

अटल sमाप_प्रकार hvcs_partner_clcs_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा vio_dev *viod = to_vio_dev(dev);
	काष्ठा hvcs_काष्ठा *hvcsd = from_vio_dev(viod);
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;

	spin_lock_irqsave(&hvcsd->lock, flags);
	retval = प्र_लिखो(buf, "%s\n", &hvcsd->p_location_code[0]);
	spin_unlock_irqrestore(&hvcsd->lock, flags);
	वापस retval;
पूर्ण
अटल DEVICE_ATTR(partner_clcs, S_IRUGO, hvcs_partner_clcs_show, शून्य);

अटल sमाप_प्रकार hvcs_current_vty_store(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर * buf,
		माप_प्रकार count)
अणु
	/*
	 * Don't need this feature at the present time because firmware doesn't
	 * yet support multiple partners.
	 */
	prपूर्णांकk(KERN_INFO "HVCS: Denied current_vty change: -EPERM.\n");
	वापस -EPERM;
पूर्ण

अटल sमाप_प्रकार hvcs_current_vty_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा vio_dev *viod = to_vio_dev(dev);
	काष्ठा hvcs_काष्ठा *hvcsd = from_vio_dev(viod);
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;

	spin_lock_irqsave(&hvcsd->lock, flags);
	retval = प्र_लिखो(buf, "%s\n", &hvcsd->p_location_code[0]);
	spin_unlock_irqrestore(&hvcsd->lock, flags);
	वापस retval;
पूर्ण

अटल DEVICE_ATTR(current_vty,
	S_IRUGO | S_IWUSR, hvcs_current_vty_show, hvcs_current_vty_store);

अटल sमाप_प्रकार hvcs_vterm_state_store(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	काष्ठा vio_dev *viod = to_vio_dev(dev);
	काष्ठा hvcs_काष्ठा *hvcsd = from_vio_dev(viod);
	अचिन्हित दीर्घ flags;

	/* writing a '0' to this sysfs entry will result in the disconnect. */
	अगर (simple_म_से_दीर्घ(buf, शून्य, 0) != 0)
		वापस -EINVAL;

	spin_lock_irqsave(&hvcsd->lock, flags);

	अगर (hvcsd->port.count > 0) अणु
		spin_unlock_irqrestore(&hvcsd->lock, flags);
		prपूर्णांकk(KERN_INFO "HVCS: vterm state unchanged.  "
				"The hvcs device node is still in use.\n");
		वापस -EPERM;
	पूर्ण

	अगर (hvcsd->connected == 0) अणु
		spin_unlock_irqrestore(&hvcsd->lock, flags);
		prपूर्णांकk(KERN_INFO "HVCS: vterm state unchanged. The"
				" vty-server is not connected to a vty.\n");
		वापस -EPERM;
	पूर्ण

	hvcs_partner_मुक्त(hvcsd);
	prपूर्णांकk(KERN_INFO "HVCS: Closed vty-server@%X and"
			" partner vty@%X:%d connection.\n",
			hvcsd->vdev->unit_address,
			hvcsd->p_unit_address,
			(uपूर्णांक32_t)hvcsd->p_partition_ID);

	spin_unlock_irqrestore(&hvcsd->lock, flags);
	वापस count;
पूर्ण

अटल sमाप_प्रकार hvcs_vterm_state_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा vio_dev *viod = to_vio_dev(dev);
	काष्ठा hvcs_काष्ठा *hvcsd = from_vio_dev(viod);
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;

	spin_lock_irqsave(&hvcsd->lock, flags);
	retval = प्र_लिखो(buf, "%d\n", hvcsd->connected);
	spin_unlock_irqrestore(&hvcsd->lock, flags);
	वापस retval;
पूर्ण
अटल DEVICE_ATTR(vterm_state, S_IRUGO | S_IWUSR,
		hvcs_vterm_state_show, hvcs_vterm_state_store);

अटल sमाप_प्रकार hvcs_index_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा vio_dev *viod = to_vio_dev(dev);
	काष्ठा hvcs_काष्ठा *hvcsd = from_vio_dev(viod);
	अचिन्हित दीर्घ flags;
	पूर्णांक retval;

	spin_lock_irqsave(&hvcsd->lock, flags);
	retval = प्र_लिखो(buf, "%d\n", hvcsd->index);
	spin_unlock_irqrestore(&hvcsd->lock, flags);
	वापस retval;
पूर्ण

अटल DEVICE_ATTR(index, S_IRUGO, hvcs_index_show, शून्य);

अटल काष्ठा attribute *hvcs_attrs[] = अणु
	&dev_attr_partner_vtys.attr,
	&dev_attr_partner_clcs.attr,
	&dev_attr_current_vty.attr,
	&dev_attr_vterm_state.attr,
	&dev_attr_index.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group hvcs_attr_group = अणु
	.attrs = hvcs_attrs,
पूर्ण;

अटल sमाप_प्रकार rescan_show(काष्ठा device_driver *ddp, अक्षर *buf)
अणु
	/* A 1 means it is updating, a 0 means it is करोne updating */
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", hvcs_rescan_status);
पूर्ण

अटल sमाप_प्रकार rescan_store(काष्ठा device_driver *ddp, स्थिर अक्षर * buf,
		माप_प्रकार count)
अणु
	अगर ((simple_म_से_दीर्घ(buf, शून्य, 0) != 1)
		&& (hvcs_rescan_status != 0))
		वापस -EINVAL;

	hvcs_rescan_status = 1;
	prपूर्णांकk(KERN_INFO "HVCS: rescanning partner info for all"
		" vty-servers.\n");
	hvcs_rescan_devices_list();
	hvcs_rescan_status = 0;
	वापस count;
पूर्ण

अटल DRIVER_ATTR_RW(rescan);

अटल व्योम hvcs_kick(व्योम)
अणु
	hvcs_kicked = 1;
	wmb();
	wake_up_process(hvcs_task);
पूर्ण

अटल व्योम hvcs_unthrottle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा hvcs_काष्ठा *hvcsd = tty->driver_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hvcsd->lock, flags);
	hvcsd->toकरो_mask |= HVCS_SCHED_READ;
	spin_unlock_irqrestore(&hvcsd->lock, flags);
	hvcs_kick();
पूर्ण

अटल व्योम hvcs_throttle(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा hvcs_काष्ठा *hvcsd = tty->driver_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hvcsd->lock, flags);
	vio_disable_पूर्णांकerrupts(hvcsd->vdev);
	spin_unlock_irqrestore(&hvcsd->lock, flags);
पूर्ण

/*
 * If the device is being हटाओd we करोn't have to worry about this पूर्णांकerrupt
 * handler taking any further पूर्णांकerrupts because they are disabled which means
 * the hvcs_काष्ठा will always be valid in this handler.
 */
अटल irqवापस_t hvcs_handle_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा hvcs_काष्ठा *hvcsd = dev_instance;

	spin_lock(&hvcsd->lock);
	vio_disable_पूर्णांकerrupts(hvcsd->vdev);
	hvcsd->toकरो_mask |= HVCS_SCHED_READ;
	spin_unlock(&hvcsd->lock);
	hvcs_kick();

	वापस IRQ_HANDLED;
पूर्ण

/* This function must be called with the hvcsd->lock held */
अटल व्योम hvcs_try_ग_लिखो(काष्ठा hvcs_काष्ठा *hvcsd)
अणु
	uपूर्णांक32_t unit_address = hvcsd->vdev->unit_address;
	काष्ठा tty_काष्ठा *tty = hvcsd->port.tty;
	पूर्णांक sent;

	अगर (hvcsd->toकरो_mask & HVCS_TRY_WRITE) अणु
		/* won't send partial ग_लिखोs */
		sent = hvc_put_अक्षरs(unit_address,
				&hvcsd->buffer[0],
				hvcsd->अक्षरs_in_buffer );
		अगर (sent > 0) अणु
			hvcsd->अक्षरs_in_buffer = 0;
			/* wmb(); */
			hvcsd->toकरो_mask &= ~(HVCS_TRY_WRITE);
			/* wmb(); */

			/*
			 * We are still obligated to deliver the data to the
			 * hypervisor even अगर the tty has been बंदd because
			 * we committed to delivering it.  But करोn't try to wake
			 * a non-existent tty.
			 */
			अगर (tty) अणु
				tty_wakeup(tty);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक hvcs_io(काष्ठा hvcs_काष्ठा *hvcsd)
अणु
	uपूर्णांक32_t unit_address;
	काष्ठा tty_काष्ठा *tty;
	अक्षर buf[HVCS_BUFF_LEN] __ALIGNED__;
	अचिन्हित दीर्घ flags;
	पूर्णांक got = 0;

	spin_lock_irqsave(&hvcsd->lock, flags);

	unit_address = hvcsd->vdev->unit_address;
	tty = hvcsd->port.tty;

	hvcs_try_ग_लिखो(hvcsd);

	अगर (!tty || tty_throttled(tty)) अणु
		hvcsd->toकरो_mask &= ~(HVCS_READ_MASK);
		जाओ bail;
	पूर्ण अन्यथा अगर (!(hvcsd->toकरो_mask & (HVCS_READ_MASK)))
		जाओ bail;

	/* हटाओ the पढ़ो masks */
	hvcsd->toकरो_mask &= ~(HVCS_READ_MASK);

	अगर (tty_buffer_request_room(&hvcsd->port, HVCS_BUFF_LEN) >= HVCS_BUFF_LEN) अणु
		got = hvc_get_अक्षरs(unit_address,
				&buf[0],
				HVCS_BUFF_LEN);
		tty_insert_flip_string(&hvcsd->port, buf, got);
	पूर्ण

	/* Give the TTY समय to process the data we just sent. */
	अगर (got)
		hvcsd->toकरो_mask |= HVCS_QUICK_READ;

	spin_unlock_irqrestore(&hvcsd->lock, flags);
	/* This is synch -- FIXME :js: it is not! */
	अगर(got)
		tty_flip_buffer_push(&hvcsd->port);

	अगर (!got) अणु
		/* Do this _after_ the flip_buffer_push */
		spin_lock_irqsave(&hvcsd->lock, flags);
		vio_enable_पूर्णांकerrupts(hvcsd->vdev);
		spin_unlock_irqrestore(&hvcsd->lock, flags);
	पूर्ण

	वापस hvcsd->toकरो_mask;

 bail:
	spin_unlock_irqrestore(&hvcsd->lock, flags);
	वापस hvcsd->toकरो_mask;
पूर्ण

अटल पूर्णांक khvcsd(व्योम *unused)
अणु
	काष्ठा hvcs_काष्ठा *hvcsd;
	पूर्णांक hvcs_toकरो_mask;

	__set_current_state(TASK_RUNNING);

	करो अणु
		hvcs_toकरो_mask = 0;
		hvcs_kicked = 0;
		wmb();

		spin_lock(&hvcs_काष्ठाs_lock);
		list_क्रम_each_entry(hvcsd, &hvcs_काष्ठाs, next) अणु
			hvcs_toकरो_mask |= hvcs_io(hvcsd);
		पूर्ण
		spin_unlock(&hvcs_काष्ठाs_lock);

		/*
		 * If any of the hvcs adapters want to try a ग_लिखो or quick पढ़ो
		 * करोn't schedule(), yield a smidgen then execute the hvcs_io
		 * thपढ़ो again क्रम those that want the ग_लिखो.
		 */
		 अगर (hvcs_toकरो_mask & (HVCS_TRY_WRITE | HVCS_QUICK_READ)) अणु
			yield();
			जारी;
		पूर्ण

		set_current_state(TASK_INTERRUPTIBLE);
		अगर (!hvcs_kicked)
			schedule();
		__set_current_state(TASK_RUNNING);
	पूर्ण जबतक (!kthपढ़ो_should_stop());

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vio_device_id hvcs_driver_table[] = अणु
	अणु"serial-server", "hvterm2"पूर्ण,
	अणु "", "" पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(vio, hvcs_driver_table);

अटल व्योम hvcs_वापस_index(पूर्णांक index)
अणु
	/* Paranoia check */
	अगर (!hvcs_index_list)
		वापस;
	अगर (index < 0 || index >= hvcs_index_count)
		वापस;
	अगर (hvcs_index_list[index] == -1)
		वापस;
	अन्यथा
		hvcs_index_list[index] = -1;
पूर्ण

अटल व्योम hvcs_deकाष्ठा_port(काष्ठा tty_port *p)
अणु
	काष्ठा hvcs_काष्ठा *hvcsd = container_of(p, काष्ठा hvcs_काष्ठा, port);
	काष्ठा vio_dev *vdev;
	अचिन्हित दीर्घ flags;

	spin_lock(&hvcs_काष्ठाs_lock);
	spin_lock_irqsave(&hvcsd->lock, flags);

	/* the list_del poisons the poपूर्णांकers */
	list_del(&(hvcsd->next));

	अगर (hvcsd->connected == 1) अणु
		hvcs_partner_मुक्त(hvcsd);
		prपूर्णांकk(KERN_INFO "HVCS: Closed vty-server@%X and"
				" partner vty@%X:%d connection.\n",
				hvcsd->vdev->unit_address,
				hvcsd->p_unit_address,
				(uपूर्णांक32_t)hvcsd->p_partition_ID);
	पूर्ण
	prपूर्णांकk(KERN_INFO "HVCS: Destroyed hvcs_struct for vty-server@%X.\n",
			hvcsd->vdev->unit_address);

	vdev = hvcsd->vdev;
	hvcsd->vdev = शून्य;

	hvcsd->p_unit_address = 0;
	hvcsd->p_partition_ID = 0;
	hvcs_वापस_index(hvcsd->index);
	स_रखो(&hvcsd->p_location_code[0], 0x00, HVCS_CLC_LENGTH + 1);

	spin_unlock_irqrestore(&hvcsd->lock, flags);
	spin_unlock(&hvcs_काष्ठाs_lock);

	sysfs_हटाओ_group(&vdev->dev.kobj, &hvcs_attr_group);

	kमुक्त(hvcsd);
पूर्ण

अटल स्थिर काष्ठा tty_port_operations hvcs_port_ops = अणु
	.deकाष्ठा = hvcs_deकाष्ठा_port,
पूर्ण;

अटल पूर्णांक hvcs_get_index(व्योम)
अणु
	पूर्णांक i;
	/* Paranoia check */
	अगर (!hvcs_index_list) अणु
		prपूर्णांकk(KERN_ERR "HVCS: hvcs_index_list NOT valid!.\n");
		वापस -EFAULT;
	पूर्ण
	/* Find the numerically lowest first मुक्त index. */
	क्रम(i = 0; i < hvcs_index_count; i++) अणु
		अगर (hvcs_index_list[i] == -1) अणु
			hvcs_index_list[i] = 0;
			वापस i;
		पूर्ण
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक hvcs_probe(
	काष्ठा vio_dev *dev,
	स्थिर काष्ठा vio_device_id *id)
अणु
	काष्ठा hvcs_काष्ठा *hvcsd;
	पूर्णांक index, rc;
	पूर्णांक retval;

	अगर (!dev || !id) अणु
		prपूर्णांकk(KERN_ERR "HVCS: probed with invalid parameter.\n");
		वापस -EPERM;
	पूर्ण

	/* Make sure we are properly initialized */
	rc = hvcs_initialize();
	अगर (rc) अणु
		pr_err("HVCS: Failed to initialize core driver.\n");
		वापस rc;
	पूर्ण

	/* early to aव्योम cleanup on failure */
	index = hvcs_get_index();
	अगर (index < 0) अणु
		वापस -EFAULT;
	पूर्ण

	hvcsd = kzalloc(माप(*hvcsd), GFP_KERNEL);
	अगर (!hvcsd)
		वापस -ENODEV;

	tty_port_init(&hvcsd->port);
	hvcsd->port.ops = &hvcs_port_ops;
	spin_lock_init(&hvcsd->lock);

	hvcsd->vdev = dev;
	dev_set_drvdata(&dev->dev, hvcsd);

	hvcsd->index = index;

	/* hvcsd->index = ++hvcs_काष्ठा_count; */
	hvcsd->अक्षरs_in_buffer = 0;
	hvcsd->toकरो_mask = 0;
	hvcsd->connected = 0;

	/*
	 * This will populate the hvcs_काष्ठा's partner info fields क्रम the
	 * first समय.
	 */
	अगर (hvcs_get_pi(hvcsd)) अणु
		prपूर्णांकk(KERN_ERR "HVCS: Failed to fetch partner"
			" info for vty-server@%X on device probe.\n",
			hvcsd->vdev->unit_address);
	पूर्ण

	/*
	 * If a user app खोलोs a tty that corresponds to this vty-server beक्रमe
	 * the hvcs_काष्ठा has been added to the devices list then the user app
	 * will get -ENODEV.
	 */
	spin_lock(&hvcs_काष्ठाs_lock);
	list_add_tail(&(hvcsd->next), &hvcs_काष्ठाs);
	spin_unlock(&hvcs_काष्ठाs_lock);

	retval = sysfs_create_group(&dev->dev.kobj, &hvcs_attr_group);
	अगर (retval) अणु
		prपूर्णांकk(KERN_ERR "HVCS: Can't create sysfs attrs for vty-server@%X\n",
		       hvcsd->vdev->unit_address);
		वापस retval;
	पूर्ण

	prपूर्णांकk(KERN_INFO "HVCS: vty-server@%X added to the vio bus.\n", dev->unit_address);

	/*
	 * DON'T enable पूर्णांकerrupts here because there is no user to receive the
	 * data.
	 */
	वापस 0;
पूर्ण

अटल व्योम hvcs_हटाओ(काष्ठा vio_dev *dev)
अणु
	काष्ठा hvcs_काष्ठा *hvcsd = dev_get_drvdata(&dev->dev);
	अचिन्हित दीर्घ flags;
	काष्ठा tty_काष्ठा *tty;

	/* By this समय the vty-server won't be getting any more पूर्णांकerrupts */

	spin_lock_irqsave(&hvcsd->lock, flags);

	tty = hvcsd->port.tty;

	spin_unlock_irqrestore(&hvcsd->lock, flags);

	/*
	 * Let the last holder of this object cause it to be हटाओd, which
	 * would probably be tty_hangup below.
	 */
	tty_port_put(&hvcsd->port);

	/*
	 * The hangup is a scheduled function which will स्वतः chain call
	 * hvcs_hangup.  The tty should always be valid at this समय unless a
	 * simultaneous tty बंद alपढ़ोy cleaned up the hvcs_काष्ठा.
	 */
	अगर (tty)
		tty_hangup(tty);

	prपूर्णांकk(KERN_INFO "HVCS: vty-server@%X removed from the"
			" vio bus.\n", dev->unit_address);
पूर्ण;

अटल काष्ठा vio_driver hvcs_vio_driver = अणु
	.id_table	= hvcs_driver_table,
	.probe		= hvcs_probe,
	.हटाओ		= hvcs_हटाओ,
	.name		= hvcs_driver_name,
पूर्ण;

/* Only called from hvcs_get_pi please */
अटल व्योम hvcs_set_pi(काष्ठा hvcs_partner_info *pi, काष्ठा hvcs_काष्ठा *hvcsd)
अणु
	hvcsd->p_unit_address = pi->unit_address;
	hvcsd->p_partition_ID  = pi->partition_ID;

	/* copy the null-term अक्षर too */
	strlcpy(hvcsd->p_location_code, pi->location_code,
		माप(hvcsd->p_location_code));
पूर्ण

/*
 * Traverse the list and add the partner info that is found to the hvcs_काष्ठा
 * काष्ठा entry. NOTE: At this समय I know that partner info will वापस a
 * single entry but in the future there may be multiple partner info entries per
 * vty-server and you'll want to zero out that list and reset it.  If क्रम some
 * reason you have an old version of this driver but there IS more than one
 * partner info then hvcsd->p_* will hold the last partner info data from the
 * firmware query.  A good way to update this code would be to replace the three
 * partner info fields in hvcs_काष्ठा with a list of hvcs_partner_info
 * instances.
 *
 * This function must be called with the hvcsd->lock held.
 */
अटल पूर्णांक hvcs_get_pi(काष्ठा hvcs_काष्ठा *hvcsd)
अणु
	काष्ठा hvcs_partner_info *pi;
	uपूर्णांक32_t unit_address = hvcsd->vdev->unit_address;
	काष्ठा list_head head;
	पूर्णांक retval;

	spin_lock(&hvcs_pi_lock);
	अगर (!hvcs_pi_buff) अणु
		spin_unlock(&hvcs_pi_lock);
		वापस -EFAULT;
	पूर्ण
	retval = hvcs_get_partner_info(unit_address, &head, hvcs_pi_buff);
	spin_unlock(&hvcs_pi_lock);
	अगर (retval) अणु
		prपूर्णांकk(KERN_ERR "HVCS: Failed to fetch partner"
			" info for vty-server@%x.\n", unit_address);
		वापस retval;
	पूर्ण

	/* nixes the values अगर the partner vty went away */
	hvcsd->p_unit_address = 0;
	hvcsd->p_partition_ID = 0;

	list_क्रम_each_entry(pi, &head, node)
		hvcs_set_pi(pi, hvcsd);

	hvcs_मुक्त_partner_info(&head);
	वापस 0;
पूर्ण

/*
 * This function is executed by the driver "rescan" sysfs entry.  It shouldn't
 * be executed अन्यथाwhere, in order to prevent deadlock issues.
 */
अटल पूर्णांक hvcs_rescan_devices_list(व्योम)
अणु
	काष्ठा hvcs_काष्ठा *hvcsd;
	अचिन्हित दीर्घ flags;

	spin_lock(&hvcs_काष्ठाs_lock);

	list_क्रम_each_entry(hvcsd, &hvcs_काष्ठाs, next) अणु
		spin_lock_irqsave(&hvcsd->lock, flags);
		hvcs_get_pi(hvcsd);
		spin_unlock_irqrestore(&hvcsd->lock, flags);
	पूर्ण

	spin_unlock(&hvcs_काष्ठाs_lock);

	वापस 0;
पूर्ण

/*
 * Farm this off पूर्णांकo its own function because it could be more complex once
 * multiple partners support is added. This function should be called with
 * the hvcsd->lock held.
 */
अटल पूर्णांक hvcs_has_pi(काष्ठा hvcs_काष्ठा *hvcsd)
अणु
	अगर ((!hvcsd->p_unit_address) || (!hvcsd->p_partition_ID))
		वापस 0;
	वापस 1;
पूर्ण

/*
 * NOTE: It is possible that the super admin हटाओd a partner vty and then
 * added a dअगरferent vty as the new partner.
 *
 * This function must be called with the hvcsd->lock held.
 */
अटल पूर्णांक hvcs_partner_connect(काष्ठा hvcs_काष्ठा *hvcsd)
अणु
	पूर्णांक retval;
	अचिन्हित पूर्णांक unit_address = hvcsd->vdev->unit_address;

	/*
	 * If there wasn't any pi when the device was added it doesn't meant
	 * there isn't any now.  This driver isn't notअगरied when a new partner
	 * vty is added to a vty-server so we discover changes on our own.
	 * Please see comments in hvcs_रेजिस्टर_connection() क्रम justअगरication
	 * of this bizarre code.
	 */
	retval = hvcs_रेजिस्टर_connection(unit_address,
			hvcsd->p_partition_ID,
			hvcsd->p_unit_address);
	अगर (!retval) अणु
		hvcsd->connected = 1;
		वापस 0;
	पूर्ण अन्यथा अगर (retval != -EINVAL)
		वापस retval;

	/*
	 * As per the spec re-get the pi and try again अगर -EINVAL after the
	 * first connection attempt.
	 */
	अगर (hvcs_get_pi(hvcsd))
		वापस -ENOMEM;

	अगर (!hvcs_has_pi(hvcsd))
		वापस -ENODEV;

	retval = hvcs_रेजिस्टर_connection(unit_address,
			hvcsd->p_partition_ID,
			hvcsd->p_unit_address);
	अगर (retval != -EINVAL) अणु
		hvcsd->connected = 1;
		वापस retval;
	पूर्ण

	/*
	 * EBUSY is the most likely scenario though the vty could have been
	 * हटाओd or there really could be an hcall error due to the parameter
	 * data but thanks to ambiguous firmware वापस codes we can't really
	 * tell.
	 */
	prपूर्णांकk(KERN_INFO "HVCS: vty-server or partner"
			" vty is busy.  Try again later.\n");
	वापस -EBUSY;
पूर्ण

/* This function must be called with the hvcsd->lock held */
अटल व्योम hvcs_partner_मुक्त(काष्ठा hvcs_काष्ठा *hvcsd)
अणु
	पूर्णांक retval;
	करो अणु
		retval = hvcs_मुक्त_connection(hvcsd->vdev->unit_address);
	पूर्ण जबतक (retval == -EBUSY);
	hvcsd->connected = 0;
पूर्ण

/* This helper function must be called WITHOUT the hvcsd->lock held */
अटल पूर्णांक hvcs_enable_device(काष्ठा hvcs_काष्ठा *hvcsd, uपूर्णांक32_t unit_address,
		अचिन्हित पूर्णांक irq, काष्ठा vio_dev *vdev)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	/*
	 * It is possible that the vty-server was हटाओd between the समय that
	 * the conn was रेजिस्टरed and now.
	 */
	rc = request_irq(irq, &hvcs_handle_पूर्णांकerrupt, 0, "ibmhvcs", hvcsd);
	अगर (!rc) अणु
		/*
		 * It is possible the vty-server was हटाओd after the irq was
		 * requested but beक्रमe we have समय to enable पूर्णांकerrupts.
		 */
		अगर (vio_enable_पूर्णांकerrupts(vdev) == H_SUCCESS)
			वापस 0;
		अन्यथा अणु
			prपूर्णांकk(KERN_ERR "HVCS: int enable failed for"
					" vty-server@%X.\n", unit_address);
			मुक्त_irq(irq, hvcsd);
		पूर्ण
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_ERR "HVCS: irq req failed for"
				" vty-server@%X.\n", unit_address);

	spin_lock_irqsave(&hvcsd->lock, flags);
	hvcs_partner_मुक्त(hvcsd);
	spin_unlock_irqrestore(&hvcsd->lock, flags);

	वापस rc;

पूर्ण

/*
 * This always increments the kref ref count अगर the call is successful.
 * Please remember to dec when you are करोne with the instance.
 *
 * NOTICE: Do NOT hold either the hvcs_काष्ठा.lock or hvcs_काष्ठाs_lock when
 * calling this function or you will get deadlock.
 */
अटल काष्ठा hvcs_काष्ठा *hvcs_get_by_index(पूर्णांक index)
अणु
	काष्ठा hvcs_काष्ठा *hvcsd;
	अचिन्हित दीर्घ flags;

	spin_lock(&hvcs_काष्ठाs_lock);
	list_क्रम_each_entry(hvcsd, &hvcs_काष्ठाs, next) अणु
		spin_lock_irqsave(&hvcsd->lock, flags);
		अगर (hvcsd->index == index) अणु
			tty_port_get(&hvcsd->port);
			spin_unlock_irqrestore(&hvcsd->lock, flags);
			spin_unlock(&hvcs_काष्ठाs_lock);
			वापस hvcsd;
		पूर्ण
		spin_unlock_irqrestore(&hvcsd->lock, flags);
	पूर्ण
	spin_unlock(&hvcs_काष्ठाs_lock);

	वापस शून्य;
पूर्ण

अटल पूर्णांक hvcs_install(काष्ठा tty_driver *driver, काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा hvcs_काष्ठा *hvcsd;
	काष्ठा vio_dev *vdev;
	अचिन्हित दीर्घ unit_address, flags;
	अचिन्हित पूर्णांक irq;
	पूर्णांक retval;

	/*
	 * Is there a vty-server that shares the same index?
	 * This function increments the kref index.
	 */
	hvcsd = hvcs_get_by_index(tty->index);
	अगर (!hvcsd) अणु
		prपूर्णांकk(KERN_WARNING "HVCS: open failed, no device associated"
				" with tty->index %d.\n", tty->index);
		वापस -ENODEV;
	पूर्ण

	spin_lock_irqsave(&hvcsd->lock, flags);

	अगर (hvcsd->connected == 0) अणु
		retval = hvcs_partner_connect(hvcsd);
		अगर (retval) अणु
			spin_unlock_irqrestore(&hvcsd->lock, flags);
			prपूर्णांकk(KERN_WARNING "HVCS: partner connect failed.\n");
			जाओ err_put;
		पूर्ण
	पूर्ण

	hvcsd->port.count = 0;
	hvcsd->port.tty = tty;
	tty->driver_data = hvcsd;

	स_रखो(&hvcsd->buffer[0], 0x00, HVCS_BUFF_LEN);

	/*
	 * Save these in the spinlock क्रम the enable operations that need them
	 * outside of the spinlock.
	 */
	irq = hvcsd->vdev->irq;
	vdev = hvcsd->vdev;
	unit_address = hvcsd->vdev->unit_address;

	hvcsd->toकरो_mask |= HVCS_SCHED_READ;
	spin_unlock_irqrestore(&hvcsd->lock, flags);

	/*
	 * This must be करोne outside of the spinlock because it requests irqs
	 * and will grab the spinlock and मुक्त the connection अगर it fails.
	 */
	retval = hvcs_enable_device(hvcsd, unit_address, irq, vdev);
	अगर (retval) अणु
		prपूर्णांकk(KERN_WARNING "HVCS: enable device failed.\n");
		जाओ err_put;
	पूर्ण

	retval = tty_port_install(&hvcsd->port, driver, tty);
	अगर (retval)
		जाओ err_irq;

	वापस 0;
err_irq:
	spin_lock_irqsave(&hvcsd->lock, flags);
	vio_disable_पूर्णांकerrupts(hvcsd->vdev);
	spin_unlock_irqrestore(&hvcsd->lock, flags);
	मुक्त_irq(irq, hvcsd);
err_put:
	tty_port_put(&hvcsd->port);

	वापस retval;
पूर्ण

/*
 * This is invoked via the tty_खोलो पूर्णांकerface when a user app connects to the
 * /dev node.
 */
अटल पूर्णांक hvcs_खोलो(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा hvcs_काष्ठा *hvcsd = tty->driver_data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hvcsd->lock, flags);
	hvcsd->port.count++;
	hvcsd->toकरो_mask |= HVCS_SCHED_READ;
	spin_unlock_irqrestore(&hvcsd->lock, flags);

	hvcs_kick();

	prपूर्णांकk(KERN_INFO "HVCS: vty-server@%X connection opened.\n",
		hvcsd->vdev->unit_address );

	वापस 0;
पूर्ण

अटल व्योम hvcs_बंद(काष्ठा tty_काष्ठा *tty, काष्ठा file *filp)
अणु
	काष्ठा hvcs_काष्ठा *hvcsd;
	अचिन्हित दीर्घ flags;
	पूर्णांक irq;

	/*
	 * Is someone trying to बंद the file associated with this device after
	 * we have hung up?  If so tty->driver_data wouldn't be valid.
	 */
	अगर (tty_hung_up_p(filp))
		वापस;

	/*
	 * No driver_data means that this बंद was probably issued after a
	 * failed hvcs_खोलो by the tty layer's release_dev() api and we can just
	 * निकास cleanly.
	 */
	अगर (!tty->driver_data)
		वापस;

	hvcsd = tty->driver_data;

	spin_lock_irqsave(&hvcsd->lock, flags);
	अगर (--hvcsd->port.count == 0) अणु

		vio_disable_पूर्णांकerrupts(hvcsd->vdev);

		/*
		 * शून्य this early so that the kernel_thपढ़ो करोesn't try to
		 * execute any operations on the TTY even though it is obligated
		 * to deliver any pending I/O to the hypervisor.
		 */
		hvcsd->port.tty = शून्य;

		irq = hvcsd->vdev->irq;
		spin_unlock_irqrestore(&hvcsd->lock, flags);

		tty_रुको_until_sent(tty, HVCS_CLOSE_WAIT);

		मुक्त_irq(irq, hvcsd);
		वापस;
	पूर्ण अन्यथा अगर (hvcsd->port.count < 0) अणु
		prपूर्णांकk(KERN_ERR "HVCS: vty-server@%X open_count: %d is mismanaged.\n",
		hvcsd->vdev->unit_address, hvcsd->port.count);
	पूर्ण

	spin_unlock_irqrestore(&hvcsd->lock, flags);
पूर्ण

अटल व्योम hvcs_cleanup(काष्ठा tty_काष्ठा * tty)
अणु
	काष्ठा hvcs_काष्ठा *hvcsd = tty->driver_data;

	/*
	 * This line is important because it tells hvcs_खोलो that this
	 * device needs to be re-configured the next समय hvcs_खोलो is
	 * called.
	 */
	tty->driver_data = शून्य;

	tty_port_put(&hvcsd->port);
पूर्ण

अटल व्योम hvcs_hangup(काष्ठा tty_काष्ठा * tty)
अणु
	काष्ठा hvcs_काष्ठा *hvcsd = tty->driver_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक temp_खोलो_count;
	पूर्णांक irq;

	spin_lock_irqsave(&hvcsd->lock, flags);
	/* Preserve this so that we know how many kref refs to put */
	temp_खोलो_count = hvcsd->port.count;

	/*
	 * Don't kref put inside the spinlock because the deकाष्ठाion
	 * callback may use the spinlock and it may get called beक्रमe the
	 * spinlock has been released.
	 */
	vio_disable_पूर्णांकerrupts(hvcsd->vdev);

	hvcsd->toकरो_mask = 0;

	/* I करोn't think the tty needs the hvcs_काष्ठा poपूर्णांकer after a hangup */
	tty->driver_data = शून्य;
	hvcsd->port.tty = शून्य;

	hvcsd->port.count = 0;

	/* This will drop any buffered data on the न्यूनमान which is OK in a hangup
	 * scenario. */
	स_रखो(&hvcsd->buffer[0], 0x00, HVCS_BUFF_LEN);
	hvcsd->अक्षरs_in_buffer = 0;

	irq = hvcsd->vdev->irq;

	spin_unlock_irqrestore(&hvcsd->lock, flags);

	मुक्त_irq(irq, hvcsd);

	/*
	 * We need to kref_put() क्रम every खोलो_count we have since the
	 * tty_hangup() function करोesn't invoke a बंद per खोलो connection on a
	 * non-console device.
	 */
	जबतक(temp_खोलो_count) अणु
		--temp_खोलो_count;
		/*
		 * The final put will trigger deकाष्ठाion of the hvcs_काष्ठा.
		 * NOTE:  If this hangup was संकेतed from user space then the
		 * final put will never happen.
		 */
		tty_port_put(&hvcsd->port);
	पूर्ण
पूर्ण

/*
 * NOTE: This is almost always from_user since user level apps पूर्णांकeract with the
 * /dev nodes. I'm trusting that अगर hvcs_ग_लिखो माला_लो called and पूर्णांकerrupted by
 * hvcs_हटाओ (which हटाओs the target device and executes tty_hangup()) that
 * tty_hangup will allow hvcs_ग_लिखो समय to complete execution beक्रमe it
 * terminates our device.
 */
अटल पूर्णांक hvcs_ग_लिखो(काष्ठा tty_काष्ठा *tty,
		स्थिर अचिन्हित अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा hvcs_काष्ठा *hvcsd = tty->driver_data;
	अचिन्हित पूर्णांक unit_address;
	स्थिर अचिन्हित अक्षर *अक्षरbuf;
	अचिन्हित दीर्घ flags;
	पूर्णांक total_sent = 0;
	पूर्णांक tosend = 0;
	पूर्णांक result = 0;

	/*
	 * If they करोn't check the वापस code off of their खोलो they may
	 * attempt this even अगर there is no connected device.
	 */
	अगर (!hvcsd)
		वापस -ENODEV;

	/* Reasonable size to prevent user level flooding */
	अगर (count > HVCS_MAX_FROM_USER) अणु
		prपूर्णांकk(KERN_WARNING "HVCS write: count being truncated to"
				" HVCS_MAX_FROM_USER.\n");
		count = HVCS_MAX_FROM_USER;
	पूर्ण

	अक्षरbuf = buf;

	spin_lock_irqsave(&hvcsd->lock, flags);

	/*
	 * Somehow an खोलो succeeded but the device was हटाओd or the
	 * connection terminated between the vty-server and partner vty during
	 * the middle of a ग_लिखो operation?  This is a crummy place to करो this
	 * but we want to keep it all in the spinlock.
	 */
	अगर (hvcsd->port.count <= 0) अणु
		spin_unlock_irqrestore(&hvcsd->lock, flags);
		वापस -ENODEV;
	पूर्ण

	unit_address = hvcsd->vdev->unit_address;

	जबतक (count > 0) अणु
		tosend = min(count, (HVCS_BUFF_LEN - hvcsd->अक्षरs_in_buffer));
		/*
		 * No more space, this probably means that the last call to
		 * hvcs_ग_लिखो() didn't succeed and the buffer was filled up.
		 */
		अगर (!tosend)
			अवरोध;

		स_नकल(&hvcsd->buffer[hvcsd->अक्षरs_in_buffer],
				&अक्षरbuf[total_sent],
				tosend);

		hvcsd->अक्षरs_in_buffer += tosend;

		result = 0;

		/*
		 * If this is true then we करोn't want to try writing to the
		 * hypervisor because that is the kernel_thपढ़ोs job now.  We'll
		 * just add to the buffer.
		 */
		अगर (!(hvcsd->toकरो_mask & HVCS_TRY_WRITE))
			/* won't send partial ग_लिखोs */
			result = hvc_put_अक्षरs(unit_address,
					&hvcsd->buffer[0],
					hvcsd->अक्षरs_in_buffer);

		/*
		 * Since we know we have enough room in hvcsd->buffer क्रम
		 * tosend we record that it was sent regardless of whether the
		 * hypervisor actually took it because we have it buffered.
		 */
		total_sent+=tosend;
		count-=tosend;
		अगर (result == 0) अणु
			hvcsd->toकरो_mask |= HVCS_TRY_WRITE;
			hvcs_kick();
			अवरोध;
		पूर्ण

		hvcsd->अक्षरs_in_buffer = 0;
		/*
		 * Test after the अक्षरs_in_buffer reset otherwise this could
		 * deadlock our ग_लिखोs अगर hvc_put_अक्षरs fails.
		 */
		अगर (result < 0)
			अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&hvcsd->lock, flags);

	अगर (result == -1)
		वापस -EIO;
	अन्यथा
		वापस total_sent;
पूर्ण

/*
 * This is really asking how much can we guarantee that we can send or that we
 * असलolutely WILL BUFFER अगर we can't send it.  This driver MUST honor the
 * वापस value, hence the reason क्रम hvcs_काष्ठा buffering.
 */
अटल पूर्णांक hvcs_ग_लिखो_room(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा hvcs_काष्ठा *hvcsd = tty->driver_data;

	अगर (!hvcsd || hvcsd->port.count <= 0)
		वापस 0;

	वापस HVCS_BUFF_LEN - hvcsd->अक्षरs_in_buffer;
पूर्ण

अटल पूर्णांक hvcs_अक्षरs_in_buffer(काष्ठा tty_काष्ठा *tty)
अणु
	काष्ठा hvcs_काष्ठा *hvcsd = tty->driver_data;

	वापस hvcsd->अक्षरs_in_buffer;
पूर्ण

अटल स्थिर काष्ठा tty_operations hvcs_ops = अणु
	.install = hvcs_install,
	.खोलो = hvcs_खोलो,
	.बंद = hvcs_बंद,
	.cleanup = hvcs_cleanup,
	.hangup = hvcs_hangup,
	.ग_लिखो = hvcs_ग_लिखो,
	.ग_लिखो_room = hvcs_ग_लिखो_room,
	.अक्षरs_in_buffer = hvcs_अक्षरs_in_buffer,
	.unthrottle = hvcs_unthrottle,
	.throttle = hvcs_throttle,
पूर्ण;

अटल पूर्णांक hvcs_alloc_index_list(पूर्णांक n)
अणु
	पूर्णांक i;

	hvcs_index_list = kदो_स्मृति_array(n, माप(hvcs_index_count),
					GFP_KERNEL);
	अगर (!hvcs_index_list)
		वापस -ENOMEM;
	hvcs_index_count = n;
	क्रम (i = 0; i < hvcs_index_count; i++)
		hvcs_index_list[i] = -1;
	वापस 0;
पूर्ण

अटल व्योम hvcs_मुक्त_index_list(व्योम)
अणु
	/* Paranoia check to be thorough. */
	kमुक्त(hvcs_index_list);
	hvcs_index_list = शून्य;
	hvcs_index_count = 0;
पूर्ण

अटल पूर्णांक hvcs_initialize(व्योम)
अणु
	पूर्णांक rc, num_ttys_to_alloc;

	mutex_lock(&hvcs_init_mutex);
	अगर (hvcs_task) अणु
		mutex_unlock(&hvcs_init_mutex);
		वापस 0;
	पूर्ण

	/* Has the user specअगरied an overload with an insmod param? */
	अगर (hvcs_parm_num_devs <= 0 ||
		(hvcs_parm_num_devs > HVCS_MAX_SERVER_ADAPTERS)) अणु
		num_ttys_to_alloc = HVCS_DEFAULT_SERVER_ADAPTERS;
	पूर्ण अन्यथा
		num_ttys_to_alloc = hvcs_parm_num_devs;

	hvcs_tty_driver = alloc_tty_driver(num_ttys_to_alloc);
	अगर (!hvcs_tty_driver) अणु
		mutex_unlock(&hvcs_init_mutex);
		वापस -ENOMEM;
	पूर्ण

	अगर (hvcs_alloc_index_list(num_ttys_to_alloc)) अणु
		rc = -ENOMEM;
		जाओ index_fail;
	पूर्ण

	hvcs_tty_driver->driver_name = hvcs_driver_name;
	hvcs_tty_driver->name = hvcs_device_node;

	/*
	 * We'll let the प्रणाली assign us a major number, indicated by leaving
	 * it blank.
	 */

	hvcs_tty_driver->minor_start = HVCS_MINOR_START;
	hvcs_tty_driver->type = TTY_DRIVER_TYPE_SYSTEM;

	/*
	 * We role our own so that we DONT ECHO.  We can't echo because the
	 * device we are connecting to alपढ़ोy echoes by शेष and this would
	 * throw us पूर्णांकo a horrible recursive echo-echo-echo loop.
	 */
	hvcs_tty_driver->init_termios = hvcs_tty_termios;
	hvcs_tty_driver->flags = TTY_DRIVER_REAL_RAW;

	tty_set_operations(hvcs_tty_driver, &hvcs_ops);

	/*
	 * The following call will result in sysfs entries that denote the
	 * dynamically asचिन्हित major and minor numbers क्रम our devices.
	 */
	अगर (tty_रेजिस्टर_driver(hvcs_tty_driver)) अणु
		prपूर्णांकk(KERN_ERR "HVCS: registration as a tty driver failed.\n");
		rc = -EIO;
		जाओ रेजिस्टर_fail;
	पूर्ण

	hvcs_pi_buff = (अचिन्हित दीर्घ *) __get_मुक्त_page(GFP_KERNEL);
	अगर (!hvcs_pi_buff) अणु
		rc = -ENOMEM;
		जाओ buff_alloc_fail;
	पूर्ण

	hvcs_task = kthपढ़ो_run(khvcsd, शून्य, "khvcsd");
	अगर (IS_ERR(hvcs_task)) अणु
		prपूर्णांकk(KERN_ERR "HVCS: khvcsd creation failed.\n");
		rc = -EIO;
		जाओ kthपढ़ो_fail;
	पूर्ण
	mutex_unlock(&hvcs_init_mutex);
	वापस 0;

kthपढ़ो_fail:
	मुक्त_page((अचिन्हित दीर्घ)hvcs_pi_buff);
buff_alloc_fail:
	tty_unरेजिस्टर_driver(hvcs_tty_driver);
रेजिस्टर_fail:
	hvcs_मुक्त_index_list();
index_fail:
	put_tty_driver(hvcs_tty_driver);
	hvcs_tty_driver = शून्य;
	mutex_unlock(&hvcs_init_mutex);
	वापस rc;
पूर्ण

अटल पूर्णांक __init hvcs_module_init(व्योम)
अणु
	पूर्णांक rc = vio_रेजिस्टर_driver(&hvcs_vio_driver);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "HVCS: can't register vio driver\n");
		वापस rc;
	पूर्ण

	pr_info("HVCS: Driver registered.\n");

	/* This needs to be करोne AFTER the vio_रेजिस्टर_driver() call or अन्यथा
	 * the kobjects won't be initialized properly.
	 */
	rc = driver_create_file(&(hvcs_vio_driver.driver), &driver_attr_rescan);
	अगर (rc)
		pr_warn("HVCS: Failed to create rescan file (err %d)\n", rc);

	वापस 0;
पूर्ण

अटल व्योम __निकास hvcs_module_निकास(व्योम)
अणु
	/*
	 * This driver receives hvcs_हटाओ callbacks क्रम each device upon
	 * module removal.
	 */
	vio_unरेजिस्टर_driver(&hvcs_vio_driver);
	अगर (!hvcs_task)
		वापस;

	/*
	 * This synchronous operation  will wake the khvcsd kthपढ़ो अगर it is
	 * asleep and will वापस when khvcsd has terminated.
	 */
	kthपढ़ो_stop(hvcs_task);

	spin_lock(&hvcs_pi_lock);
	मुक्त_page((अचिन्हित दीर्घ)hvcs_pi_buff);
	hvcs_pi_buff = शून्य;
	spin_unlock(&hvcs_pi_lock);

	driver_हटाओ_file(&hvcs_vio_driver.driver, &driver_attr_rescan);

	tty_unरेजिस्टर_driver(hvcs_tty_driver);

	hvcs_मुक्त_index_list();

	put_tty_driver(hvcs_tty_driver);

	prपूर्णांकk(KERN_INFO "HVCS: driver module removed.\n");
पूर्ण

module_init(hvcs_module_init);
module_निकास(hvcs_module_निकास);
