<शैली गुरु>
/*
 * (C) 2005, 2006 Linux Networx (http://lnxi.com)
 * This file may be distributed under the terms of the
 * GNU General Public License.
 *
 * Written Doug Thompson <norsk5@xmission.com>
 *
 */
#समावेश <linux/module.h>
#समावेश <linux/edac.h>
#समावेश <linux/slab.h>
#समावेश <linux/प्रकार.स>

#समावेश "edac_pci.h"
#समावेश "edac_module.h"

#घोषणा EDAC_PCI_SYMLINK	"device"

/* data variables exported via sysfs */
अटल पूर्णांक check_pci_errors;		/* शेष NO check PCI parity */
अटल पूर्णांक edac_pci_panic_on_pe;	/* शेष NO panic on PCI Parity */
अटल पूर्णांक edac_pci_log_pe = 1;		/* log PCI parity errors */
अटल पूर्णांक edac_pci_log_npe = 1;	/* log PCI non-parity error errors */
अटल पूर्णांक edac_pci_poll_msec = 1000;	/* one second workq period */

अटल atomic_t pci_parity_count = ATOMIC_INIT(0);
अटल atomic_t pci_nonparity_count = ATOMIC_INIT(0);

अटल काष्ठा kobject *edac_pci_top_मुख्य_kobj;
अटल atomic_t edac_pci_sysfs_refcount = ATOMIC_INIT(0);

/* getter functions क्रम the data variables */
पूर्णांक edac_pci_get_check_errors(व्योम)
अणु
	वापस check_pci_errors;
पूर्ण

अटल पूर्णांक edac_pci_get_log_pe(व्योम)
अणु
	वापस edac_pci_log_pe;
पूर्ण

अटल पूर्णांक edac_pci_get_log_npe(व्योम)
अणु
	वापस edac_pci_log_npe;
पूर्ण

अटल पूर्णांक edac_pci_get_panic_on_pe(व्योम)
अणु
	वापस edac_pci_panic_on_pe;
पूर्ण

पूर्णांक edac_pci_get_poll_msec(व्योम)
अणु
	वापस edac_pci_poll_msec;
पूर्ण

/**************************** EDAC PCI sysfs instance *******************/
अटल sमाप_प्रकार instance_pe_count_show(काष्ठा edac_pci_ctl_info *pci, अक्षर *data)
अणु
	वापस प्र_लिखो(data, "%u\n", atomic_पढ़ो(&pci->counters.pe_count));
पूर्ण

अटल sमाप_प्रकार instance_npe_count_show(काष्ठा edac_pci_ctl_info *pci,
				अक्षर *data)
अणु
	वापस प्र_लिखो(data, "%u\n", atomic_पढ़ो(&pci->counters.npe_count));
पूर्ण

#घोषणा to_instance(k) container_of(k, काष्ठा edac_pci_ctl_info, kobj)
#घोषणा to_instance_attr(a) container_of(a, काष्ठा instance_attribute, attr)

/* DEVICE instance kobject release() function */
अटल व्योम edac_pci_instance_release(काष्ठा kobject *kobj)
अणु
	काष्ठा edac_pci_ctl_info *pci;

	edac_dbg(0, "\n");

	/* Form poपूर्णांकer to containing काष्ठा, the pci control काष्ठा */
	pci = to_instance(kobj);

	/* decrement reference count on top मुख्य kobj */
	kobject_put(edac_pci_top_मुख्य_kobj);

	kमुक्त(pci);	/* Free the control काष्ठा */
पूर्ण

/* instance specअगरic attribute काष्ठाure */
काष्ठा instance_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार(*show) (काष्ठा edac_pci_ctl_info *, अक्षर *);
	sमाप_प्रकार(*store) (काष्ठा edac_pci_ctl_info *, स्थिर अक्षर *, माप_प्रकार);
पूर्ण;

/* Function to 'show' fields from the edac_pci 'instance' काष्ठाure */
अटल sमाप_प्रकार edac_pci_instance_show(काष्ठा kobject *kobj,
				काष्ठा attribute *attr, अक्षर *buffer)
अणु
	काष्ठा edac_pci_ctl_info *pci = to_instance(kobj);
	काष्ठा instance_attribute *instance_attr = to_instance_attr(attr);

	अगर (instance_attr->show)
		वापस instance_attr->show(pci, buffer);
	वापस -EIO;
पूर्ण

/* Function to 'store' fields into the edac_pci 'instance' काष्ठाure */
अटल sमाप_प्रकार edac_pci_instance_store(काष्ठा kobject *kobj,
				काष्ठा attribute *attr,
				स्थिर अक्षर *buffer, माप_प्रकार count)
अणु
	काष्ठा edac_pci_ctl_info *pci = to_instance(kobj);
	काष्ठा instance_attribute *instance_attr = to_instance_attr(attr);

	अगर (instance_attr->store)
		वापस instance_attr->store(pci, buffer, count);
	वापस -EIO;
पूर्ण

/* fs_ops table */
अटल स्थिर काष्ठा sysfs_ops pci_instance_ops = अणु
	.show = edac_pci_instance_show,
	.store = edac_pci_instance_store
पूर्ण;

#घोषणा INSTANCE_ATTR(_name, _mode, _show, _store)	\
अटल काष्ठा instance_attribute attr_instance_##_name = अणु	\
	.attr	= अणु.name = __stringअगरy(_name), .mode = _mode पूर्ण,	\
	.show	= _show,					\
	.store	= _store,					\
पूर्ण;

INSTANCE_ATTR(pe_count, S_IRUGO, instance_pe_count_show, शून्य);
INSTANCE_ATTR(npe_count, S_IRUGO, instance_npe_count_show, शून्य);

/* pci instance attributes */
अटल काष्ठा instance_attribute *pci_instance_attr[] = अणु
	&attr_instance_pe_count,
	&attr_instance_npe_count,
	शून्य
पूर्ण;

/* the ktype क्रम a pci instance */
अटल काष्ठा kobj_type ktype_pci_instance = अणु
	.release = edac_pci_instance_release,
	.sysfs_ops = &pci_instance_ops,
	.शेष_attrs = (काष्ठा attribute **)pci_instance_attr,
पूर्ण;

/*
 * edac_pci_create_instance_kobj
 *
 *	स्थिरruct one EDAC PCI instance's kobject क्रम use
 */
अटल पूर्णांक edac_pci_create_instance_kobj(काष्ठा edac_pci_ctl_info *pci, पूर्णांक idx)
अणु
	काष्ठा kobject *मुख्य_kobj;
	पूर्णांक err;

	edac_dbg(0, "\n");

	/* First bump the ref count on the top मुख्य kobj, which will
	 * track the number of PCI instances we have, and thus nest
	 * properly on keeping the module loaded
	 */
	मुख्य_kobj = kobject_get(edac_pci_top_मुख्य_kobj);
	अगर (!मुख्य_kobj) अणु
		err = -ENODEV;
		जाओ error_out;
	पूर्ण

	/* And now रेजिस्टर this new kobject under the मुख्य kobj */
	err = kobject_init_and_add(&pci->kobj, &ktype_pci_instance,
				   edac_pci_top_मुख्य_kobj, "pci%d", idx);
	अगर (err != 0) अणु
		edac_dbg(2, "failed to register instance pci%d\n", idx);
		kobject_put(edac_pci_top_मुख्य_kobj);
		जाओ error_out;
	पूर्ण

	kobject_uevent(&pci->kobj, KOBJ_ADD);
	edac_dbg(1, "Register instance 'pci%d' kobject\n", idx);

	वापस 0;

	/* Error unwind statck */
error_out:
	वापस err;
पूर्ण

/*
 * edac_pci_unरेजिस्टर_sysfs_instance_kobj
 *
 *	unरेजिस्टर the kobj क्रम the EDAC PCI instance
 */
अटल व्योम edac_pci_unरेजिस्टर_sysfs_instance_kobj(
			काष्ठा edac_pci_ctl_info *pci)
अणु
	edac_dbg(0, "\n");

	/* Unरेजिस्टर the instance kobject and allow its release
	 * function release the मुख्य reference count and then
	 * kमुक्त the memory
	 */
	kobject_put(&pci->kobj);
पूर्ण

/***************************** EDAC PCI sysfs root **********************/
#घोषणा to_edacpci(k) container_of(k, काष्ठा edac_pci_ctl_info, kobj)
#घोषणा to_edacpci_attr(a) container_of(a, काष्ठा edac_pci_attr, attr)

/* simple show/store functions क्रम attributes */
अटल sमाप_प्रकार edac_pci_पूर्णांक_show(व्योम *ptr, अक्षर *buffer)
अणु
	पूर्णांक *value = ptr;
	वापस प्र_लिखो(buffer, "%d\n", *value);
पूर्ण

अटल sमाप_प्रकार edac_pci_पूर्णांक_store(व्योम *ptr, स्थिर अक्षर *buffer, माप_प्रकार count)
अणु
	पूर्णांक *value = ptr;

	अगर (है_अंक(*buffer))
		*value = simple_म_से_अदीर्घ(buffer, शून्य, 0);

	वापस count;
पूर्ण

काष्ठा edac_pci_dev_attribute अणु
	काष्ठा attribute attr;
	व्योम *value;
	 sमाप_प्रकार(*show) (व्योम *, अक्षर *);
	 sमाप_प्रकार(*store) (व्योम *, स्थिर अक्षर *, माप_प्रकार);
पूर्ण;

/* Set of show/store असलtract level functions क्रम PCI Parity object */
अटल sमाप_प्रकार edac_pci_dev_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
				 अक्षर *buffer)
अणु
	काष्ठा edac_pci_dev_attribute *edac_pci_dev;
	edac_pci_dev = (काष्ठा edac_pci_dev_attribute *)attr;

	अगर (edac_pci_dev->show)
		वापस edac_pci_dev->show(edac_pci_dev->value, buffer);
	वापस -EIO;
पूर्ण

अटल sमाप_प्रकार edac_pci_dev_store(काष्ठा kobject *kobj,
				काष्ठा attribute *attr, स्थिर अक्षर *buffer,
				माप_प्रकार count)
अणु
	काष्ठा edac_pci_dev_attribute *edac_pci_dev;
	edac_pci_dev = (काष्ठा edac_pci_dev_attribute *)attr;

	अगर (edac_pci_dev->store)
		वापस edac_pci_dev->store(edac_pci_dev->value, buffer, count);
	वापस -EIO;
पूर्ण

अटल स्थिर काष्ठा sysfs_ops edac_pci_sysfs_ops = अणु
	.show = edac_pci_dev_show,
	.store = edac_pci_dev_store
पूर्ण;

#घोषणा EDAC_PCI_ATTR(_name,_mode,_show,_store)			\
अटल काष्ठा edac_pci_dev_attribute edac_pci_attr_##_name = अणु		\
	.attr = अणु.name = __stringअगरy(_name), .mode = _mode पूर्ण,	\
	.value  = &_name,					\
	.show   = _show,					\
	.store  = _store,					\
पूर्ण;

#घोषणा EDAC_PCI_STRING_ATTR(_name,_data,_mode,_show,_store)	\
अटल काष्ठा edac_pci_dev_attribute edac_pci_attr_##_name = अणु		\
	.attr = अणु.name = __stringअगरy(_name), .mode = _mode पूर्ण,	\
	.value  = _data,					\
	.show   = _show,					\
	.store  = _store,					\
पूर्ण;

/* PCI Parity control files */
EDAC_PCI_ATTR(check_pci_errors, S_IRUGO | S_IWUSR, edac_pci_पूर्णांक_show,
	edac_pci_पूर्णांक_store);
EDAC_PCI_ATTR(edac_pci_log_pe, S_IRUGO | S_IWUSR, edac_pci_पूर्णांक_show,
	edac_pci_पूर्णांक_store);
EDAC_PCI_ATTR(edac_pci_log_npe, S_IRUGO | S_IWUSR, edac_pci_पूर्णांक_show,
	edac_pci_पूर्णांक_store);
EDAC_PCI_ATTR(edac_pci_panic_on_pe, S_IRUGO | S_IWUSR, edac_pci_पूर्णांक_show,
	edac_pci_पूर्णांक_store);
EDAC_PCI_ATTR(pci_parity_count, S_IRUGO, edac_pci_पूर्णांक_show, शून्य);
EDAC_PCI_ATTR(pci_nonparity_count, S_IRUGO, edac_pci_पूर्णांक_show, शून्य);

/* Base Attributes of the memory ECC object */
अटल काष्ठा edac_pci_dev_attribute *edac_pci_attr[] = अणु
	&edac_pci_attr_check_pci_errors,
	&edac_pci_attr_edac_pci_log_pe,
	&edac_pci_attr_edac_pci_log_npe,
	&edac_pci_attr_edac_pci_panic_on_pe,
	&edac_pci_attr_pci_parity_count,
	&edac_pci_attr_pci_nonparity_count,
	शून्य,
पूर्ण;

/*
 * edac_pci_release_मुख्य_kobj
 *
 *	This release function is called when the reference count to the
 *	passed kobj goes to zero.
 *
 *	This kobj is the 'main' kobject that EDAC PCI instances
 *	link to, and thus provide क्रम proper nesting counts
 */
अटल व्योम edac_pci_release_मुख्य_kobj(काष्ठा kobject *kobj)
अणु
	edac_dbg(0, "here to module_put(THIS_MODULE)\n");

	kमुक्त(kobj);

	/* last reference to top EDAC PCI kobject has been हटाओd,
	 * NOW release our ref count on the core module
	 */
	module_put(THIS_MODULE);
पूर्ण

/* ktype काष्ठा क्रम the EDAC PCI मुख्य kobj */
अटल काष्ठा kobj_type ktype_edac_pci_मुख्य_kobj = अणु
	.release = edac_pci_release_मुख्य_kobj,
	.sysfs_ops = &edac_pci_sysfs_ops,
	.शेष_attrs = (काष्ठा attribute **)edac_pci_attr,
पूर्ण;

/**
 * edac_pci_मुख्य_kobj_setup: Setup the sysfs क्रम EDAC PCI attributes.
 */
अटल पूर्णांक edac_pci_मुख्य_kobj_setup(व्योम)
अणु
	पूर्णांक err;
	काष्ठा bus_type *edac_subsys;

	edac_dbg(0, "\n");

	/* check and count अगर we have alपढ़ोy created the मुख्य kobject */
	अगर (atomic_inc_वापस(&edac_pci_sysfs_refcount) != 1)
		वापस 0;

	/* First समय, so create the मुख्य kobject and its
	 * controls and attributes
	 */
	edac_subsys = edac_get_sysfs_subsys();

	/* Bump the reference count on this module to ensure the
	 * modules isn't unloaded until we deस्थिरruct the top
	 * level मुख्य kobj क्रम EDAC PCI
	 */
	अगर (!try_module_get(THIS_MODULE)) अणु
		edac_dbg(1, "try_module_get() failed\n");
		err = -ENODEV;
		जाओ decrement_count_fail;
	पूर्ण

	edac_pci_top_मुख्य_kobj = kzalloc(माप(काष्ठा kobject), GFP_KERNEL);
	अगर (!edac_pci_top_मुख्य_kobj) अणु
		edac_dbg(1, "Failed to allocate\n");
		err = -ENOMEM;
		जाओ kzalloc_fail;
	पूर्ण

	/* Instanstiate the pci object */
	err = kobject_init_and_add(edac_pci_top_मुख्य_kobj,
				   &ktype_edac_pci_मुख्य_kobj,
				   &edac_subsys->dev_root->kobj, "pci");
	अगर (err) अणु
		edac_dbg(1, "Failed to register '.../edac/pci'\n");
		जाओ kobject_init_and_add_fail;
	पूर्ण

	/* At this poपूर्णांक, to 'release' the top level kobject
	 * क्रम EDAC PCI, then edac_pci_मुख्य_kobj_tearकरोwn()
	 * must be used, क्रम resources to be cleaned up properly
	 */
	kobject_uevent(edac_pci_top_मुख्य_kobj, KOBJ_ADD);
	edac_dbg(1, "Registered '.../edac/pci' kobject\n");

	वापस 0;

	/* Error unwind statck */
kobject_init_and_add_fail:
	kobject_put(edac_pci_top_मुख्य_kobj);

kzalloc_fail:
	module_put(THIS_MODULE);

decrement_count_fail:
	/* अगर are on this error निकास, nothing to tear करोwn */
	atomic_dec(&edac_pci_sysfs_refcount);

	वापस err;
पूर्ण

/*
 * edac_pci_मुख्य_kobj_tearकरोwn()
 *
 *	अगर no दीर्घer linked (needed) हटाओ the top level EDAC PCI
 *	kobject with its controls and attributes
 */
अटल व्योम edac_pci_मुख्य_kobj_tearकरोwn(व्योम)
अणु
	edac_dbg(0, "\n");

	/* Decrement the count and only अगर no more controller instances
	 * are connected perक्रमm the unरेजिस्टरation of the top level
	 * मुख्य kobj
	 */
	अगर (atomic_dec_वापस(&edac_pci_sysfs_refcount) == 0) अणु
		edac_dbg(0, "called kobject_put on main kobj\n");
		kobject_put(edac_pci_top_मुख्य_kobj);
	पूर्ण
पूर्ण

पूर्णांक edac_pci_create_sysfs(काष्ठा edac_pci_ctl_info *pci)
अणु
	पूर्णांक err;
	काष्ठा kobject *edac_kobj = &pci->kobj;

	edac_dbg(0, "idx=%d\n", pci->pci_idx);

	/* create the top मुख्य EDAC PCI kobject, IF needed */
	err = edac_pci_मुख्य_kobj_setup();
	अगर (err)
		वापस err;

	/* Create this instance's kobject under the MAIN kobject */
	err = edac_pci_create_instance_kobj(pci, pci->pci_idx);
	अगर (err)
		जाओ unरेजिस्टर_cleanup;

	err = sysfs_create_link(edac_kobj, &pci->dev->kobj, EDAC_PCI_SYMLINK);
	अगर (err) अणु
		edac_dbg(0, "sysfs_create_link() returned err= %d\n", err);
		जाओ symlink_fail;
	पूर्ण

	वापस 0;

	/* Error unwind stack */
symlink_fail:
	edac_pci_unरेजिस्टर_sysfs_instance_kobj(pci);

unरेजिस्टर_cleanup:
	edac_pci_मुख्य_kobj_tearकरोwn();

	वापस err;
पूर्ण

व्योम edac_pci_हटाओ_sysfs(काष्ठा edac_pci_ctl_info *pci)
अणु
	edac_dbg(0, "index=%d\n", pci->pci_idx);

	/* Remove the symlink */
	sysfs_हटाओ_link(&pci->kobj, EDAC_PCI_SYMLINK);

	/* हटाओ this PCI instance's sysfs entries */
	edac_pci_unरेजिस्टर_sysfs_instance_kobj(pci);

	/* Call the मुख्य unरेजिस्टर function, which will determine
	 * अगर this 'pci' is the last instance.
	 * If it is, the मुख्य kobject will be unरेजिस्टरed as a result
	 */
	edac_dbg(0, "calling edac_pci_main_kobj_teardown()\n");
	edac_pci_मुख्य_kobj_tearकरोwn();
पूर्ण

/************************ PCI error handling *************************/
अटल u16 get_pci_parity_status(काष्ठा pci_dev *dev, पूर्णांक secondary)
अणु
	पूर्णांक where;
	u16 status;

	where = secondary ? PCI_SEC_STATUS : PCI_STATUS;
	pci_पढ़ो_config_word(dev, where, &status);

	/* If we get back 0xFFFF then we must suspect that the card has been
	 * pulled but the Linux PCI layer has not yet finished cleaning up.
	 * We करोn't want to report on such devices
	 */

	अगर (status == 0xFFFF) अणु
		u32 sanity;

		pci_पढ़ो_config_dword(dev, 0, &sanity);

		अगर (sanity == 0xFFFFFFFF)
			वापस 0;
	पूर्ण

	status &= PCI_STATUS_DETECTED_PARITY | PCI_STATUS_SIG_SYSTEM_ERROR |
		PCI_STATUS_PARITY;

	अगर (status)
		/* reset only the bits we are पूर्णांकerested in */
		pci_ग_लिखो_config_word(dev, where, status);

	वापस status;
पूर्ण


/* Clear any PCI parity errors logged by this device. */
अटल व्योम edac_pci_dev_parity_clear(काष्ठा pci_dev *dev)
अणु
	u8 header_type;

	get_pci_parity_status(dev, 0);

	/* पढ़ो the device TYPE, looking क्रम bridges */
	pci_पढ़ो_config_byte(dev, PCI_HEADER_TYPE, &header_type);

	अगर ((header_type & 0x7F) == PCI_HEADER_TYPE_BRIDGE)
		get_pci_parity_status(dev, 1);
पूर्ण

/*
 *  PCI Parity polling
 *
 *	Function to retrieve the current parity status
 *	and decode it
 *
 */
अटल व्योम edac_pci_dev_parity_test(काष्ठा pci_dev *dev)
अणु
	अचिन्हित दीर्घ flags;
	u16 status;
	u8 header_type;

	/* stop any पूर्णांकerrupts until we can acquire the status */
	local_irq_save(flags);

	/* पढ़ो the STATUS रेजिस्टर on this device */
	status = get_pci_parity_status(dev, 0);

	/* पढ़ो the device TYPE, looking क्रम bridges */
	pci_पढ़ो_config_byte(dev, PCI_HEADER_TYPE, &header_type);

	local_irq_restore(flags);

	edac_dbg(4, "PCI STATUS= 0x%04x %s\n", status, dev_name(&dev->dev));

	/* check the status reg क्रम errors on boards NOT marked as broken
	 * अगर broken, we cannot trust any of the status bits
	 */
	अगर (status && !dev->broken_parity_status) अणु
		अगर (status & (PCI_STATUS_SIG_SYSTEM_ERROR)) अणु
			edac_prपूर्णांकk(KERN_CRIT, EDAC_PCI,
				"Signaled System Error on %s\n",
				pci_name(dev));
			atomic_inc(&pci_nonparity_count);
		पूर्ण

		अगर (status & (PCI_STATUS_PARITY)) अणु
			edac_prपूर्णांकk(KERN_CRIT, EDAC_PCI,
				"Master Data Parity Error on %s\n",
				pci_name(dev));

			atomic_inc(&pci_parity_count);
		पूर्ण

		अगर (status & (PCI_STATUS_DETECTED_PARITY)) अणु
			edac_prपूर्णांकk(KERN_CRIT, EDAC_PCI,
				"Detected Parity Error on %s\n",
				pci_name(dev));

			atomic_inc(&pci_parity_count);
		पूर्ण
	पूर्ण


	edac_dbg(4, "PCI HEADER TYPE= 0x%02x %s\n",
		 header_type, dev_name(&dev->dev));

	अगर ((header_type & 0x7F) == PCI_HEADER_TYPE_BRIDGE) अणु
		/* On bridges, need to examine secondary status रेजिस्टर  */
		status = get_pci_parity_status(dev, 1);

		edac_dbg(4, "PCI SEC_STATUS= 0x%04x %s\n",
			 status, dev_name(&dev->dev));

		/* check the secondary status reg क्रम errors,
		 * on NOT broken boards
		 */
		अगर (status && !dev->broken_parity_status) अणु
			अगर (status & (PCI_STATUS_SIG_SYSTEM_ERROR)) अणु
				edac_prपूर्णांकk(KERN_CRIT, EDAC_PCI, "Bridge "
					"Signaled System Error on %s\n",
					pci_name(dev));
				atomic_inc(&pci_nonparity_count);
			पूर्ण

			अगर (status & (PCI_STATUS_PARITY)) अणु
				edac_prपूर्णांकk(KERN_CRIT, EDAC_PCI, "Bridge "
					"Master Data Parity Error on "
					"%s\n", pci_name(dev));

				atomic_inc(&pci_parity_count);
			पूर्ण

			अगर (status & (PCI_STATUS_DETECTED_PARITY)) अणु
				edac_prपूर्णांकk(KERN_CRIT, EDAC_PCI, "Bridge "
					"Detected Parity Error on %s\n",
					pci_name(dev));

				atomic_inc(&pci_parity_count);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* reduce some complनिकासy in definition of the iterator */
प्रकार व्योम (*pci_parity_check_fn_t) (काष्ठा pci_dev *dev);

/*
 * pci_dev parity list iterator
 *
 *	Scan the PCI device list looking क्रम SERRORs, Master Parity ERRORS or
 *	Parity ERRORs on primary or secondary devices.
 */
अटल अंतरभूत व्योम edac_pci_dev_parity_iterator(pci_parity_check_fn_t fn)
अणु
	काष्ठा pci_dev *dev = शून्य;

	क्रम_each_pci_dev(dev)
		fn(dev);
पूर्ण

/*
 * edac_pci_करो_parity_check
 *
 *	perक्रमms the actual PCI parity check operation
 */
व्योम edac_pci_करो_parity_check(व्योम)
अणु
	पूर्णांक beक्रमe_count;

	edac_dbg(3, "\n");

	/* अगर policy has PCI check off, leave now */
	अगर (!check_pci_errors)
		वापस;

	beक्रमe_count = atomic_पढ़ो(&pci_parity_count);

	/* scan all PCI devices looking क्रम a Parity Error on devices and
	 * bridges.
	 * The iterator calls pci_get_device() which might sleep, thus
	 * we cannot disable पूर्णांकerrupts in this scan.
	 */
	edac_pci_dev_parity_iterator(edac_pci_dev_parity_test);

	/* Only अगर चालक has selected panic on PCI Error */
	अगर (edac_pci_get_panic_on_pe()) अणु
		/* If the count is dअगरferent 'after' from 'before' */
		अगर (beक्रमe_count != atomic_पढ़ो(&pci_parity_count))
			panic("EDAC: PCI Parity Error");
	पूर्ण
पूर्ण

/*
 * edac_pci_clear_parity_errors
 *
 *	function to perक्रमm an iteration over the PCI devices
 *	and clearn their current status
 */
व्योम edac_pci_clear_parity_errors(व्योम)
अणु
	/* Clear any PCI bus parity errors that devices initially have logged
	 * in their रेजिस्टरs.
	 */
	edac_pci_dev_parity_iterator(edac_pci_dev_parity_clear);
पूर्ण

/*
 * edac_pci_handle_pe
 *
 *	Called to handle a PARITY ERROR event
 */
व्योम edac_pci_handle_pe(काष्ठा edac_pci_ctl_info *pci, स्थिर अक्षर *msg)
अणु

	/* global PE counter incremented by edac_pci_करो_parity_check() */
	atomic_inc(&pci->counters.pe_count);

	अगर (edac_pci_get_log_pe())
		edac_pci_prपूर्णांकk(pci, KERN_WARNING,
				"Parity Error ctl: %s %d: %s\n",
				pci->ctl_name, pci->pci_idx, msg);

	/*
	 * poke all PCI devices and see which one is the troublemaker
	 * panic() is called अगर set
	 */
	edac_pci_करो_parity_check();
पूर्ण
EXPORT_SYMBOL_GPL(edac_pci_handle_pe);


/*
 * edac_pci_handle_npe
 *
 *	Called to handle a NON-PARITY ERROR event
 */
व्योम edac_pci_handle_npe(काष्ठा edac_pci_ctl_info *pci, स्थिर अक्षर *msg)
अणु

	/* global NPE counter incremented by edac_pci_करो_parity_check() */
	atomic_inc(&pci->counters.npe_count);

	अगर (edac_pci_get_log_npe())
		edac_pci_prपूर्णांकk(pci, KERN_WARNING,
				"Non-Parity Error ctl: %s %d: %s\n",
				pci->ctl_name, pci->pci_idx, msg);

	/*
	 * poke all PCI devices and see which one is the troublemaker
	 * panic() is called अगर set
	 */
	edac_pci_करो_parity_check();
पूर्ण
EXPORT_SYMBOL_GPL(edac_pci_handle_npe);

/*
 * Define the PCI parameter to the module
 */
module_param(check_pci_errors, पूर्णांक, 0644);
MODULE_PARM_DESC(check_pci_errors,
		 "Check for PCI bus parity errors: 0=off 1=on");
module_param(edac_pci_panic_on_pe, पूर्णांक, 0644);
MODULE_PARM_DESC(edac_pci_panic_on_pe,
		 "Panic on PCI Bus Parity error: 0=off 1=on");
