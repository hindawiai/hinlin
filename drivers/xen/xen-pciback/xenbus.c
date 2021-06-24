<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCI Backend Xenbus Setup - handles setup with frontend and xend
 *
 *   Author: Ryan Wilson <hap9@epoch.ncsc.mil>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/workqueue.h>
#समावेश <xen/xenbus.h>
#समावेश <xen/events.h>
#समावेश <यंत्र/xen/pci.h>
#समावेश "pciback.h"

#घोषणा INVALID_EVTCHN_IRQ  (-1)

अटल bool __पढ़ो_mostly passthrough;
module_param(passthrough, bool, S_IRUGO);
MODULE_PARM_DESC(passthrough,
	"Option to specify how to export PCI topology to guest:\n"\
	" 0 - (default) Hide the true PCI topology and makes the frontend\n"\
	"   there is a single PCI bus with only the exported devices on it.\n"\
	"   For example, a device at 03:05.0 will be re-assigned to 00:00.0\n"\
	"   while second device at 02:1a.1 will be re-assigned to 00:01.1.\n"\
	" 1 - Passthrough provides a real view of the PCI topology to the\n"\
	"   frontend (for example, a device at 06:01.b will still appear at\n"\
	"   06:01.b to the frontend). This is similar to how Xen 2.0.x\n"\
	"   exposed PCI devices to its driver domains. This may be required\n"\
	"   for drivers which depend on finding their hardward in certain\n"\
	"   bus/slot locations.");

अटल काष्ठा xen_pcibk_device *alloc_pdev(काष्ठा xenbus_device *xdev)
अणु
	काष्ठा xen_pcibk_device *pdev;

	pdev = kzalloc(माप(काष्ठा xen_pcibk_device), GFP_KERNEL);
	अगर (pdev == शून्य)
		जाओ out;
	dev_dbg(&xdev->dev, "allocated pdev @ 0x%p\n", pdev);

	pdev->xdev = xdev;

	mutex_init(&pdev->dev_lock);

	pdev->sh_info = शून्य;
	pdev->evtchn_irq = INVALID_EVTCHN_IRQ;
	pdev->be_watching = 0;

	INIT_WORK(&pdev->op_work, xen_pcibk_करो_op);

	अगर (xen_pcibk_init_devices(pdev)) अणु
		kमुक्त(pdev);
		pdev = शून्य;
	पूर्ण

	dev_set_drvdata(&xdev->dev, pdev);

out:
	वापस pdev;
पूर्ण

अटल व्योम xen_pcibk_disconnect(काष्ठा xen_pcibk_device *pdev)
अणु
	mutex_lock(&pdev->dev_lock);
	/* Ensure the guest can't trigger our handler beक्रमe removing devices */
	अगर (pdev->evtchn_irq != INVALID_EVTCHN_IRQ) अणु
		unbind_from_irqhandler(pdev->evtchn_irq, pdev);
		pdev->evtchn_irq = INVALID_EVTCHN_IRQ;
	पूर्ण

	/* If the driver करोमुख्य started an op, make sure we complete it
	 * beक्रमe releasing the shared memory */

	flush_work(&pdev->op_work);

	अगर (pdev->sh_info != शून्य) अणु
		xenbus_unmap_ring_vमुक्त(pdev->xdev, pdev->sh_info);
		pdev->sh_info = शून्य;
	पूर्ण
	mutex_unlock(&pdev->dev_lock);
पूर्ण

अटल व्योम मुक्त_pdev(काष्ठा xen_pcibk_device *pdev)
अणु
	अगर (pdev->be_watching) अणु
		unरेजिस्टर_xenbus_watch(&pdev->be_watch);
		pdev->be_watching = 0;
	पूर्ण

	xen_pcibk_disconnect(pdev);

	/* N.B. This calls pcistub_put_pci_dev which करोes the FLR on all
	 * of the PCIe devices. */
	xen_pcibk_release_devices(pdev);

	dev_set_drvdata(&pdev->xdev->dev, शून्य);
	pdev->xdev = शून्य;

	kमुक्त(pdev);
पूर्ण

अटल पूर्णांक xen_pcibk_करो_attach(काष्ठा xen_pcibk_device *pdev, पूर्णांक gnt_ref,
			     evtchn_port_t remote_evtchn)
अणु
	पूर्णांक err = 0;
	व्योम *vaddr;

	dev_dbg(&pdev->xdev->dev,
		"Attaching to frontend resources - gnt_ref=%d evtchn=%u\n",
		gnt_ref, remote_evtchn);

	err = xenbus_map_ring_valloc(pdev->xdev, &gnt_ref, 1, &vaddr);
	अगर (err < 0) अणु
		xenbus_dev_fatal(pdev->xdev, err,
				"Error mapping other domain page in ours.");
		जाओ out;
	पूर्ण

	pdev->sh_info = vaddr;

	err = bind_पूर्णांकerकरोमुख्य_evtchn_to_irqhandler_lateeoi(
		pdev->xdev, remote_evtchn, xen_pcibk_handle_event,
		0, DRV_NAME, pdev);
	अगर (err < 0) अणु
		xenbus_dev_fatal(pdev->xdev, err,
				 "Error binding event channel to IRQ");
		जाओ out;
	पूर्ण
	pdev->evtchn_irq = err;
	err = 0;

	dev_dbg(&pdev->xdev->dev, "Attached!\n");
out:
	वापस err;
पूर्ण

अटल पूर्णांक xen_pcibk_attach(काष्ठा xen_pcibk_device *pdev)
अणु
	पूर्णांक err = 0;
	पूर्णांक gnt_ref;
	evtchn_port_t remote_evtchn;
	अक्षर *magic = शून्य;


	mutex_lock(&pdev->dev_lock);
	/* Make sure we only करो this setup once */
	अगर (xenbus_पढ़ो_driver_state(pdev->xdev->nodename) !=
	    XenbusStateInitialised)
		जाओ out;

	/* Wait क्रम frontend to state that it has published the configuration */
	अगर (xenbus_पढ़ो_driver_state(pdev->xdev->otherend) !=
	    XenbusStateInitialised)
		जाओ out;

	dev_dbg(&pdev->xdev->dev, "Reading frontend config\n");

	err = xenbus_gather(XBT_NIL, pdev->xdev->otherend,
			    "pci-op-ref", "%u", &gnt_ref,
			    "event-channel", "%u", &remote_evtchn,
			    "magic", शून्य, &magic, शून्य);
	अगर (err) अणु
		/* If configuration didn't get पढ़ो correctly, रुको दीर्घer */
		xenbus_dev_fatal(pdev->xdev, err,
				 "Error reading configuration from frontend");
		जाओ out;
	पूर्ण

	अगर (magic == शून्य || म_भेद(magic, XEN_PCI_MAGIC) != 0) अणु
		xenbus_dev_fatal(pdev->xdev, -EFAULT,
				 "version mismatch (%s/%s) with pcifront - "
				 "halting " DRV_NAME,
				 magic, XEN_PCI_MAGIC);
		err = -EFAULT;
		जाओ out;
	पूर्ण

	err = xen_pcibk_करो_attach(pdev, gnt_ref, remote_evtchn);
	अगर (err)
		जाओ out;

	dev_dbg(&pdev->xdev->dev, "Connecting...\n");

	err = xenbus_चयन_state(pdev->xdev, XenbusStateConnected);
	अगर (err)
		xenbus_dev_fatal(pdev->xdev, err,
				 "Error switching to connected state!");

	dev_dbg(&pdev->xdev->dev, "Connected? %d\n", err);
out:
	mutex_unlock(&pdev->dev_lock);

	kमुक्त(magic);

	वापस err;
पूर्ण

अटल पूर्णांक xen_pcibk_publish_pci_dev(काष्ठा xen_pcibk_device *pdev,
				   अचिन्हित पूर्णांक करोमुख्य, अचिन्हित पूर्णांक bus,
				   अचिन्हित पूर्णांक devfn, अचिन्हित पूर्णांक devid)
अणु
	पूर्णांक err;
	पूर्णांक len;
	अक्षर str[64];

	len = snम_लिखो(str, माप(str), "vdev-%d", devid);
	अगर (unlikely(len >= (माप(str) - 1))) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Note: The PV protocol uses %02x, करोn't change it */
	err = xenbus_म_लिखो(XBT_NIL, pdev->xdev->nodename, str,
			    "%04x:%02x:%02x.%02x", करोमुख्य, bus,
			    PCI_SLOT(devfn), PCI_FUNC(devfn));

out:
	वापस err;
पूर्ण

अटल पूर्णांक xen_pcibk_export_device(काष्ठा xen_pcibk_device *pdev,
				 पूर्णांक करोमुख्य, पूर्णांक bus, पूर्णांक slot, पूर्णांक func,
				 पूर्णांक devid)
अणु
	काष्ठा pci_dev *dev;
	पूर्णांक err = 0;

	dev_dbg(&pdev->xdev->dev, "exporting dom %x bus %x slot %x func %x\n",
		करोमुख्य, bus, slot, func);

	dev = pcistub_get_pci_dev_by_slot(pdev, करोमुख्य, bus, slot, func);
	अगर (!dev) अणु
		err = -EINVAL;
		xenbus_dev_fatal(pdev->xdev, err,
				 "Couldn't locate PCI device "
				 "(%04x:%02x:%02x.%d)! "
				 "perhaps already in-use?",
				 करोमुख्य, bus, slot, func);
		जाओ out;
	पूर्ण

	err = xen_pcibk_add_pci_dev(pdev, dev, devid,
				    xen_pcibk_publish_pci_dev);
	अगर (err)
		जाओ out;

	dev_info(&dev->dev, "registering for %d\n", pdev->xdev->otherend_id);
	अगर (xen_रेजिस्टर_device_करोमुख्य_owner(dev,
					     pdev->xdev->otherend_id) != 0) अणु
		dev_err(&dev->dev, "Stealing ownership from dom%d.\n",
			xen_find_device_करोमुख्य_owner(dev));
		xen_unरेजिस्टर_device_करोमुख्य_owner(dev);
		xen_रेजिस्टर_device_करोमुख्य_owner(dev, pdev->xdev->otherend_id);
	पूर्ण

	/* TODO: It'd be nice to export a bridge and have all of its children
	 * get exported with it. This may be best करोne in xend (which will
	 * have to calculate resource usage anyway) but we probably want to
	 * put something in here to ensure that अगर a bridge माला_लो given to a
	 * driver करोमुख्य, that all devices under that bridge are not given
	 * to other driver करोमुख्यs (as he who controls the bridge can disable
	 * it and stop the other devices from working).
	 */
out:
	वापस err;
पूर्ण

अटल पूर्णांक xen_pcibk_हटाओ_device(काष्ठा xen_pcibk_device *pdev,
				 पूर्णांक करोमुख्य, पूर्णांक bus, पूर्णांक slot, पूर्णांक func)
अणु
	पूर्णांक err = 0;
	काष्ठा pci_dev *dev;

	dev_dbg(&pdev->xdev->dev, "removing dom %x bus %x slot %x func %x\n",
		करोमुख्य, bus, slot, func);

	dev = xen_pcibk_get_pci_dev(pdev, करोमुख्य, bus, PCI_DEVFN(slot, func));
	अगर (!dev) अणु
		err = -EINVAL;
		dev_dbg(&pdev->xdev->dev, "Couldn't locate PCI device "
			"(%04x:%02x:%02x.%d)! not owned by this domain\n",
			करोमुख्य, bus, slot, func);
		जाओ out;
	पूर्ण

	dev_dbg(&dev->dev, "unregistering for %d\n", pdev->xdev->otherend_id);
	xen_unरेजिस्टर_device_करोमुख्य_owner(dev);

	/* N.B. This ends up calling pcistub_put_pci_dev which ends up
	 * करोing the FLR. */
	xen_pcibk_release_pci_dev(pdev, dev, true /* use the lock. */);

out:
	वापस err;
पूर्ण

अटल पूर्णांक xen_pcibk_publish_pci_root(काष्ठा xen_pcibk_device *pdev,
				    अचिन्हित पूर्णांक करोमुख्य, अचिन्हित पूर्णांक bus)
अणु
	अचिन्हित पूर्णांक d, b;
	पूर्णांक i, root_num, len, err;
	अक्षर str[64];

	dev_dbg(&pdev->xdev->dev, "Publishing pci roots\n");

	err = xenbus_म_पूछो(XBT_NIL, pdev->xdev->nodename,
			   "root_num", "%d", &root_num);
	अगर (err == 0 || err == -ENOENT)
		root_num = 0;
	अन्यथा अगर (err < 0)
		जाओ out;

	/* Verअगरy that we haven't alपढ़ोy published this pci root */
	क्रम (i = 0; i < root_num; i++) अणु
		len = snम_लिखो(str, माप(str), "root-%d", i);
		अगर (unlikely(len >= (माप(str) - 1))) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण

		err = xenbus_म_पूछो(XBT_NIL, pdev->xdev->nodename,
				   str, "%x:%x", &d, &b);
		अगर (err < 0)
			जाओ out;
		अगर (err != 2) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (d == करोमुख्य && b == bus) अणु
			err = 0;
			जाओ out;
		पूर्ण
	पूर्ण

	len = snम_लिखो(str, माप(str), "root-%d", root_num);
	अगर (unlikely(len >= (माप(str) - 1))) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	dev_dbg(&pdev->xdev->dev, "writing root %d at %04x:%02x\n",
		root_num, करोमुख्य, bus);

	err = xenbus_म_लिखो(XBT_NIL, pdev->xdev->nodename, str,
			    "%04x:%02x", करोमुख्य, bus);
	अगर (err)
		जाओ out;

	err = xenbus_म_लिखो(XBT_NIL, pdev->xdev->nodename,
			    "root_num", "%d", (root_num + 1));

out:
	वापस err;
पूर्ण

अटल पूर्णांक xen_pcibk_reconfigure(काष्ठा xen_pcibk_device *pdev,
				 क्रमागत xenbus_state state)
अणु
	पूर्णांक err = 0;
	पूर्णांक num_devs;
	पूर्णांक करोमुख्य, bus, slot, func;
	अचिन्हित पूर्णांक substate;
	पूर्णांक i, len;
	अक्षर state_str[64];
	अक्षर dev_str[64];


	dev_dbg(&pdev->xdev->dev, "Reconfiguring device ...\n");

	mutex_lock(&pdev->dev_lock);
	अगर (xenbus_पढ़ो_driver_state(pdev->xdev->nodename) != state)
		जाओ out;

	err = xenbus_म_पूछो(XBT_NIL, pdev->xdev->nodename, "num_devs", "%d",
			   &num_devs);
	अगर (err != 1) अणु
		अगर (err >= 0)
			err = -EINVAL;
		xenbus_dev_fatal(pdev->xdev, err,
				 "Error reading number of devices");
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < num_devs; i++) अणु
		len = snम_लिखो(state_str, माप(state_str), "state-%d", i);
		अगर (unlikely(len >= (माप(state_str) - 1))) अणु
			err = -ENOMEM;
			xenbus_dev_fatal(pdev->xdev, err,
					 "String overflow while reading "
					 "configuration");
			जाओ out;
		पूर्ण
		substate = xenbus_पढ़ो_अचिन्हित(pdev->xdev->nodename, state_str,
						XenbusStateUnknown);

		चयन (substate) अणु
		हाल XenbusStateInitialising:
			dev_dbg(&pdev->xdev->dev, "Attaching dev-%d ...\n", i);

			len = snम_लिखो(dev_str, माप(dev_str), "dev-%d", i);
			अगर (unlikely(len >= (माप(dev_str) - 1))) अणु
				err = -ENOMEM;
				xenbus_dev_fatal(pdev->xdev, err,
						 "String overflow while "
						 "reading configuration");
				जाओ out;
			पूर्ण
			err = xenbus_म_पूछो(XBT_NIL, pdev->xdev->nodename,
					   dev_str, "%x:%x:%x.%x",
					   &करोमुख्य, &bus, &slot, &func);
			अगर (err < 0) अणु
				xenbus_dev_fatal(pdev->xdev, err,
						 "Error reading device "
						 "configuration");
				जाओ out;
			पूर्ण
			अगर (err != 4) अणु
				err = -EINVAL;
				xenbus_dev_fatal(pdev->xdev, err,
						 "Error parsing pci device "
						 "configuration");
				जाओ out;
			पूर्ण

			err = xen_pcibk_export_device(pdev, करोमुख्य, bus, slot,
						    func, i);
			अगर (err)
				जाओ out;

			/* Publish pci roots. */
			err = xen_pcibk_publish_pci_roots(pdev,
						xen_pcibk_publish_pci_root);
			अगर (err) अणु
				xenbus_dev_fatal(pdev->xdev, err,
						 "Error while publish PCI root"
						 "buses for frontend");
				जाओ out;
			पूर्ण

			err = xenbus_म_लिखो(XBT_NIL, pdev->xdev->nodename,
					    state_str, "%d",
					    XenbusStateInitialised);
			अगर (err) अणु
				xenbus_dev_fatal(pdev->xdev, err,
						 "Error switching substate of "
						 "dev-%d\n", i);
				जाओ out;
			पूर्ण
			अवरोध;

		हाल XenbusStateClosing:
			dev_dbg(&pdev->xdev->dev, "Detaching dev-%d ...\n", i);

			len = snम_लिखो(dev_str, माप(dev_str), "vdev-%d", i);
			अगर (unlikely(len >= (माप(dev_str) - 1))) अणु
				err = -ENOMEM;
				xenbus_dev_fatal(pdev->xdev, err,
						 "String overflow while "
						 "reading configuration");
				जाओ out;
			पूर्ण
			err = xenbus_म_पूछो(XBT_NIL, pdev->xdev->nodename,
					   dev_str, "%x:%x:%x.%x",
					   &करोमुख्य, &bus, &slot, &func);
			अगर (err < 0) अणु
				xenbus_dev_fatal(pdev->xdev, err,
						 "Error reading device "
						 "configuration");
				जाओ out;
			पूर्ण
			अगर (err != 4) अणु
				err = -EINVAL;
				xenbus_dev_fatal(pdev->xdev, err,
						 "Error parsing pci device "
						 "configuration");
				जाओ out;
			पूर्ण

			err = xen_pcibk_हटाओ_device(pdev, करोमुख्य, bus, slot,
						    func);
			अगर (err)
				जाओ out;

			/* TODO: If at some poपूर्णांक we implement support क्रम pci
			 * root hot-हटाओ on pcअगरront side, we'll need to
			 * हटाओ unnecessary xenstore nodes of pci roots here.
			 */

			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (state != XenbusStateReconfiguring)
		/* Make sure we only reconfigure once. */
		जाओ out;

	err = xenbus_चयन_state(pdev->xdev, XenbusStateReconfigured);
	अगर (err) अणु
		xenbus_dev_fatal(pdev->xdev, err,
				 "Error switching to reconfigured state!");
		जाओ out;
	पूर्ण

out:
	mutex_unlock(&pdev->dev_lock);
	वापस 0;
पूर्ण

अटल व्योम xen_pcibk_frontend_changed(काष्ठा xenbus_device *xdev,
				     क्रमागत xenbus_state fe_state)
अणु
	काष्ठा xen_pcibk_device *pdev = dev_get_drvdata(&xdev->dev);

	dev_dbg(&xdev->dev, "fe state changed %d\n", fe_state);

	चयन (fe_state) अणु
	हाल XenbusStateInitialised:
		xen_pcibk_attach(pdev);
		अवरोध;

	हाल XenbusStateReconfiguring:
		xen_pcibk_reconfigure(pdev, XenbusStateReconfiguring);
		अवरोध;

	हाल XenbusStateConnected:
		/* pcअगरront चयनed its state from reconfiguring to connected.
		 * Then चयन to connected state.
		 */
		xenbus_चयन_state(xdev, XenbusStateConnected);
		अवरोध;

	हाल XenbusStateClosing:
		xen_pcibk_disconnect(pdev);
		xenbus_चयन_state(xdev, XenbusStateClosing);
		अवरोध;

	हाल XenbusStateClosed:
		xen_pcibk_disconnect(pdev);
		xenbus_चयन_state(xdev, XenbusStateClosed);
		अगर (xenbus_dev_is_online(xdev))
			अवरोध;
		fallthrough;	/* अगर not online */
	हाल XenbusStateUnknown:
		dev_dbg(&xdev->dev, "frontend is gone! unregister device\n");
		device_unरेजिस्टर(&xdev->dev);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक xen_pcibk_setup_backend(काष्ठा xen_pcibk_device *pdev)
अणु
	/* Get configuration from xend (अगर available now) */
	पूर्णांक करोमुख्य, bus, slot, func;
	पूर्णांक err = 0;
	पूर्णांक i, num_devs;
	अक्षर dev_str[64];
	अक्षर state_str[64];

	mutex_lock(&pdev->dev_lock);
	/* It's possible we could get the call to setup twice, so make sure
	 * we're not alपढ़ोy connected.
	 */
	अगर (xenbus_पढ़ो_driver_state(pdev->xdev->nodename) !=
	    XenbusStateInitWait)
		जाओ out;

	dev_dbg(&pdev->xdev->dev, "getting be setup\n");

	err = xenbus_म_पूछो(XBT_NIL, pdev->xdev->nodename, "num_devs", "%d",
			   &num_devs);
	अगर (err != 1) अणु
		अगर (err >= 0)
			err = -EINVAL;
		xenbus_dev_fatal(pdev->xdev, err,
				 "Error reading number of devices");
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < num_devs; i++) अणु
		पूर्णांक l = snम_लिखो(dev_str, माप(dev_str), "dev-%d", i);
		अगर (unlikely(l >= (माप(dev_str) - 1))) अणु
			err = -ENOMEM;
			xenbus_dev_fatal(pdev->xdev, err,
					 "String overflow while reading "
					 "configuration");
			जाओ out;
		पूर्ण

		err = xenbus_म_पूछो(XBT_NIL, pdev->xdev->nodename, dev_str,
				   "%x:%x:%x.%x", &करोमुख्य, &bus, &slot, &func);
		अगर (err < 0) अणु
			xenbus_dev_fatal(pdev->xdev, err,
					 "Error reading device configuration");
			जाओ out;
		पूर्ण
		अगर (err != 4) अणु
			err = -EINVAL;
			xenbus_dev_fatal(pdev->xdev, err,
					 "Error parsing pci device "
					 "configuration");
			जाओ out;
		पूर्ण

		err = xen_pcibk_export_device(pdev, करोमुख्य, bus, slot, func, i);
		अगर (err)
			जाओ out;

		/* Switch substate of this device. */
		l = snम_लिखो(state_str, माप(state_str), "state-%d", i);
		अगर (unlikely(l >= (माप(state_str) - 1))) अणु
			err = -ENOMEM;
			xenbus_dev_fatal(pdev->xdev, err,
					 "String overflow while reading "
					 "configuration");
			जाओ out;
		पूर्ण
		err = xenbus_म_लिखो(XBT_NIL, pdev->xdev->nodename, state_str,
				    "%d", XenbusStateInitialised);
		अगर (err) अणु
			xenbus_dev_fatal(pdev->xdev, err, "Error switching "
					 "substate of dev-%d\n", i);
			जाओ out;
		पूर्ण
	पूर्ण

	err = xen_pcibk_publish_pci_roots(pdev, xen_pcibk_publish_pci_root);
	अगर (err) अणु
		xenbus_dev_fatal(pdev->xdev, err,
				 "Error while publish PCI root buses "
				 "for frontend");
		जाओ out;
	पूर्ण

	err = xenbus_चयन_state(pdev->xdev, XenbusStateInitialised);
	अगर (err)
		xenbus_dev_fatal(pdev->xdev, err,
				 "Error switching to initialised state!");

out:
	mutex_unlock(&pdev->dev_lock);
	अगर (!err)
		/* see अगर pcअगरront is alपढ़ोy configured (अगर not, we'll रुको) */
		xen_pcibk_attach(pdev);
	वापस err;
पूर्ण

अटल व्योम xen_pcibk_be_watch(काष्ठा xenbus_watch *watch,
			       स्थिर अक्षर *path, स्थिर अक्षर *token)
अणु
	काष्ठा xen_pcibk_device *pdev =
	    container_of(watch, काष्ठा xen_pcibk_device, be_watch);

	चयन (xenbus_पढ़ो_driver_state(pdev->xdev->nodename)) अणु
	हाल XenbusStateInitWait:
		xen_pcibk_setup_backend(pdev);
		अवरोध;

	हाल XenbusStateInitialised:
		/*
		 * We typically move to Initialised when the first device was
		 * added. Hence subsequent devices getting added may need
		 * reconfiguring.
		 */
		xen_pcibk_reconfigure(pdev, XenbusStateInitialised);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक xen_pcibk_xenbus_probe(काष्ठा xenbus_device *dev,
				स्थिर काष्ठा xenbus_device_id *id)
अणु
	पूर्णांक err = 0;
	काष्ठा xen_pcibk_device *pdev = alloc_pdev(dev);

	अगर (pdev == शून्य) अणु
		err = -ENOMEM;
		xenbus_dev_fatal(dev, err,
				 "Error allocating xen_pcibk_device struct");
		जाओ out;
	पूर्ण

	/* रुको क्रम xend to configure us */
	err = xenbus_चयन_state(dev, XenbusStateInitWait);
	अगर (err)
		जाओ out;

	/* watch the backend node क्रम backend configuration inक्रमmation */
	err = xenbus_watch_path(dev, dev->nodename, &pdev->be_watch,
				शून्य, xen_pcibk_be_watch);
	अगर (err)
		जाओ out;

	pdev->be_watching = 1;

	/* We need to क्रमce a call to our callback here in हाल
	 * xend alपढ़ोy configured us!
	 */
	xen_pcibk_be_watch(&pdev->be_watch, शून्य, शून्य);

out:
	वापस err;
पूर्ण

अटल पूर्णांक xen_pcibk_xenbus_हटाओ(काष्ठा xenbus_device *dev)
अणु
	काष्ठा xen_pcibk_device *pdev = dev_get_drvdata(&dev->dev);

	अगर (pdev != शून्य)
		मुक्त_pdev(pdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा xenbus_device_id xen_pcibk_ids[] = अणु
	अणु"pci"पूर्ण,
	अणु""पूर्ण,
पूर्ण;

अटल काष्ठा xenbus_driver xen_pcibk_driver = अणु
	.name                   = DRV_NAME,
	.ids                    = xen_pcibk_ids,
	.probe			= xen_pcibk_xenbus_probe,
	.हटाओ			= xen_pcibk_xenbus_हटाओ,
	.otherend_changed	= xen_pcibk_frontend_changed,
पूर्ण;

स्थिर काष्ठा xen_pcibk_backend *__पढ़ो_mostly xen_pcibk_backend;

पूर्णांक __init xen_pcibk_xenbus_रेजिस्टर(व्योम)
अणु
	xen_pcibk_backend = &xen_pcibk_vpci_backend;
	अगर (passthrough)
		xen_pcibk_backend = &xen_pcibk_passthrough_backend;
	pr_info("backend is %s\n", xen_pcibk_backend->name);
	वापस xenbus_रेजिस्टर_backend(&xen_pcibk_driver);
पूर्ण

व्योम __निकास xen_pcibk_xenbus_unरेजिस्टर(व्योम)
अणु
	xenbus_unरेजिस्टर_driver(&xen_pcibk_driver);
पूर्ण
